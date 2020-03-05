/**
 * @copyright  2011 geOps
 * @author     Just van den Broecke
 * @license    https://github.com/geops/ole/blob/master/license.txt
 * @link       https://github.com/geops/ole
 */

/**
 * Class: OpenLayers.Editor.Control.UploadFeature
 *
 * Provide uploading of Features from a local file and add these to the current drawing on the Map.
 * No server-side storage is involved, though a small server-side script is required that will echo
 * back an uploaded file. This response is captured into an hidden IFrame, a well-known technique.
 * See also: http://viralpatel.net/blogs/2008/11/ajax-style-file-uploading-using-hidden-iframe.html.
 *
 * Inherits from:
 *  - <OpenLayers.Control.Button>
 */
OpenLayers.Editor.Control.UploadFeature = OpenLayers.Class(OpenLayers.Control, {

    EVENT_TYPES: ["featureuploaded"],

    layer: null,

    title: OpenLayers.i18n('oleUploadFeature'),

    /**
     * APIProperty: url
     * {String} URL of server script to upload to,
     *         see example: https://code.google.com/p/geoext-viewer/source/browse/trunk/heron/services/heron.cgi.
     */
    url: '',

    /**
     * APIProperty: params
     * {Object} parameters to be passed to server (see url) in POST body
     */
    params: {
        action: 'upload',
        mime: 'text/html',
        encoding: 'escape'
    },

    /**
     * APIProperty: formats
     * {Array} array of supported formats, each format is object with name, extension, mime and formatter classname.
     */
    formats: [
        {name: 'GeoJSON', fileExt: '.json', mimeType: 'text/plain', formatter: 'OpenLayers.Format.GeoJSON'}
    ], 
    /**
     * APIProperty: formats
     * {Array} array of supported formats, each format is object with name, extension, mime and formatter classname.
     */
    projections: [
        {value: 'EPSG:2154', name: 'EPSG:2154'},
        {value: 'EPSG:4326', name: 'EPSG:4326'},
        
    ],

    /**
     * APIProperty: fileProjection
     * {<OpenLayers.Projection>} projection of features in file, for custom projections use Proj4.js.
     */
    fileProjection: new OpenLayers.Projection("EPSG:2154"),

    formatters: {},

    /**
     * Constructor: OpenLayers.Editor.Control.MergeFeature
     * Create a new control for merging features.
     *
     * Parameters:
     * layer - {<OpenLayers.Layer.Vector>}
     * options - {Object} An optional object whose properties will be used
     *     to extend the control.
     */
    initialize: function (layer, options) {
        // console.log("initialize");
        // The editable layer
        this.layer = layer;

        this.title = OpenLayers.i18n('oleUploadFeature');

        OpenLayers.Control.Button.prototype.initialize.apply(this, [options]);
    },

    activate: function () {
        // console.log("activate");
        var activated = OpenLayers.Control.prototype.activate.call(this);
        if (activated) {
            this.openDialog();
        }
        return activated;
    },

    deactivate: function () {
        // console.log("deactivate");
        var deactivated = OpenLayers.Control.prototype.deactivate.call(this);
        if (deactivated) {
            this.cleanUp(this);
        }
        return deactivated;
    },

    /**
     * Clean up .
     */
    cleanUp: function (self) {
        // console.log("cleanUp");
        self.map.editor.dialog.hide();
        if (!self.iframe) {
            return;
        }
        self.removeIFrame();
    },
    /**
     * Creates and pops up file chooser Dialog.
     */
    delayedOpenDialog: function () {
        var self = this;
        setTimeout(function () {
            self.openDialog();
        }, 200);

    },

    /**
     * Creates and pops up file chooser Dialog.
     */
    openDialog: function () {
        // console.log("openDialog");
        // this.cleanUp(this);

        // Create content div for Dialog
        var content = document.createElement("div");

        content.appendChild(document.createElement("p"));

        // Create upload Form
        var formElm = document.createElement("form");
        formElm.setAttribute('id', 'upload_form');
        formElm.setAttribute('method', "POST");
        formElm.setAttribute('action', "http://" + window.location.hostname + Drupal.settings.basePath + "admin/structure/openlayers/editor/callbacks/process/file");
        formElm.setAttribute("target", "upload_iframe");
        formElm.setAttribute("enctype", "multipart/form-data");
        formElm.setAttribute("encoding", "multipart/form-data");
        // Input element for selecting local file
        formElm = this.createInputElm('oleFile', 'file', 'file', null, formElm);
        formElm.innerHTML += "<p style='font-size:11px;line-height:12px'>Si vous choisissez de transférer une géométrie au format ESRI Shapefile, veuillez sélectionner un fichier .zip contenant au minimum les fichiers .shp et .shx à la racine de l'archive.</p>";

        /* Create select element for file format options */
        var select = document.createElement("select");
        select.setAttribute("name", "format_select");
        select.setAttribute("id", "format_select");
        select.style.display = 'none';

        // Add file format options
        var option;
        for (var i = 0; i < this.formats.length; ++i) {
            option = document.createElement("option");

            // Some formatters are already objects
            // we cannot store these in elements, so save in map.
            // we use formatter's name in lookup in this.formatters map
            var formatter = this.formats[i].formatter;
            if (typeof formatter == 'string') {
                formatter = eval('new ' + formatter + '()');
            }
            this.formatters[this.formats[i].name] = formatter;

            // Set formatter's name as value
            option.setAttribute("value", this.formats[i].name);
            option.innerHTML = this.formats[i].name;
            option.fileExt = this.formats[i].fileExt;
            option.mimeType = this.formats[i].mimeType;
            select.appendChild(option);
        }

        // Add selector to Form
        formElm.appendChild(select);

        /* Create select element for file projection */
        var select_proj = document.createElement("select");
        select_proj.setAttribute("name", "proj_select");
        select_proj.setAttribute("id", "proj_select");

        // Add file proj options
        var option;
        for (var i = 0; i < this.projections.length; i++) {
            option = document.createElement("option");
            option.setAttribute("value", this.projections[i].value);
            option.innerHTML = this.projections[i].value;
            select_proj.appendChild(option);
        }

        // Add selector to Form
        var label = document.createElement("span");
        label.innerHTML = "<strong>Sélectionnez la projection de votre géométrie :</strong>";
        formElm.appendChild(label);
        formElm.appendChild(select_proj);

        // Additional user-defined hidden elements
        for (var param in this.params) {
            formElm = this.createInputElm(null, param, 'hidden', this.params[param], formElm);
        }

        // Add Form to content
        content.appendChild(formElm);

        this.showUploadDialog(content);

        // Set format selector on selected format if file chosen based on file extension
        var self = this;
        document.getElementById('oleFile').onchange = function (e) {
            var fileName = self.fileInputValue(this);
            if (fileName) {
                var fnameArr = fileName.split('.');
                if (fnameArr.length > 1) {
                    var ext = '.' + fnameArr[fnameArr.length - 1].toLowerCase();
                    // Find option with .ext file extension
                    var selectElm = document.getElementById('format_select');
                    var options = selectElm.options;
                    for (var i = 0; i < options.length; ++i) {
                        if (ext == options[i].fileExt) {
                            selectElm.selectedIndex = i;
                            break;
                        }
                    }
                }
            }
        };
        document.getElementById('proj_select').onchange = function (e) {
            this.fileProjection = new OpenLayers.Projection(select_proj.value);
        }
        
        

    },

    /**
     * Show message via Dialog.
     */
    showMessage: function (content, close) {
        // console.log("showMessage");
        this.map.editor.dialog.show({
            title: OpenLayers.i18n('oleUploadFeature'),
            content: content,
            close: close
        });
    },

    /**
     * Show file upload Dialog.
     * @param {!HTMLElement} content - HTML (form) content for the Dialog
     */
    showUploadDialog: function (content) {
        // console.log("showUploadDialog");
        // Show the upload Dialog. We do Form-submit ourselves.
        this.map.editor.dialog.show({
            title: OpenLayers.i18n('oleUploadFeature'),
            content: content,
            save: OpenLayers.Function.bind(this.uploadFeature, this),
            cancel: OpenLayers.Function.bind(this.cancel, this),
            saveButtonText: 'oleDialogOkButton',
            noHideOnSave: true
        });
    },

    /**
     * Create empty hidden IFrame to receive uploaded features echoed from server.
     * @param {string} name - Name of element
     * @return {!Element}
     */
    createIFrame: function (name) {
        // console.log("createIFrame");
        // Create the hidden empty iframe in which the response (file contents) will be received
        var iframe = document.createElement("iframe");
        iframe.setAttribute("id", name);
        iframe.setAttribute("name", name);
        iframe.setAttribute("width", "0");
        iframe.setAttribute("height", "0");
        iframe.setAttribute("border", "0");
        iframe.setAttribute("style", "width: 0; height: 0; border: none;");
        iframe.src = 'about:blank';
        return iframe;
    },

    /**
     * removes IFrame if existing.
     */
    removeIFrame: function () {
        // console.log("removeIFrame");
        var iframe = document.getElementById('upload_iframe');
        if (iframe) {
            iframe.parentNode.removeChild(iframe);
        }
        this.iframe = null;
    },

    /**
     * Cancel callback from Dialog.
     */
    cancel: function () {
        this.deactivate();
    },

    /**
     * Parse response (file contents) text into feature array.
     */
    parseFeatures: function (featuresText) {
        // Get selected format option
        var selectElm = document.getElementById('format_select');
        var option = selectElm.options[selectElm.selectedIndex];

        // Create a formatter from selected option
        // Either a string or an object
        var formatter = this.formatters[option.value];
        if (!formatter) {
            return null;
        }
// console.log(featuresText);
        /* Need to reproject if projection in file is different from Layer */
        if(featuresText == 'error wrong format') {
            alert("Erreur, le fichier n'est pas au bon format.");
            return null;
        }
        if(featuresText == 'error, no shape could be found.') {
            alert("Erreur, le fichier shape n'a pas pu être trouvé.");
            return null;
        }
        var features = formatter.read(featuresText);
        if (!features || features.length < 1) {
            return null;
        }

        // We have features, determine extent of feature collection
        var bounds;
        if (features.constructor != Array) {
            // May be single feature
            features = [features];
        }

        var selectProjElm = document.getElementById('proj_select');
        var projectionSel = selectProjElm.options[selectProjElm.selectedIndex];
        var projection = new OpenLayers.Projection(projectionSel.value);
        if(!projection) {
            alert('Erreur lors de la reprojection.');
        }
        for (var i = 0; i < features.length; ++i) {
            features[i].geometry.transform(projection, this.layer.map.getProjectionObject());
            if (!bounds) {
                bounds = features[i].geometry.getBounds();
            } else {
                bounds.extend(features[i].geometry.getBounds());
            }
        }
        this.bounds = bounds;
        return features;
    },

    uploadFeature: function () {
        // At least one file needs to be specified
        var fileInputElm = document.getElementById('oleFile');
        if (!this.fileInputValue(fileInputElm)) {
            this.cleanUp(this);
            this.showMessage(OpenLayers.i18n('oleUploadFeatureNoFile'), OpenLayers.Function.bind(this.delayedOpenDialog, this));
            return;
        }

        var form = document.getElementById('upload_form');
        // Create hidden IFrame to receive uploaded data and add to DOM.
        this.iframe = this.createIFrame('upload_iframe');
        form.parentNode.appendChild(this.iframe);
        window.frames['upload_iframe'].name = "upload_iframe";

        // Add event handler to handle response in IFrame
        var self = this;
        var iframe = self.iframe;
        var eventHandler = function () {

            if (iframe.detachEvent) {
                iframe.detachEvent("onload", eventHandler);
            } else {
                iframe.removeEventListener("load", eventHandler, false);
            }

            // Fetch response from server from iframe
            var content;
            if (iframe.contentDocument) {
                content = iframe.contentDocument.body.innerHTML;
            } else if (iframe.contentWindow) {
                content = iframe.contentWindow.document.body.innerHTML;
            } else if (iframe.document) {
                content = iframe.document.body.innerHTML;
            }

            // We normally use HTML-escaping, needed otherwise the iframe will garble GML (converting tags to lowercase)
            if (content && self.params.encoding == 'escape') {
                content = content.replace(/&quot;/g, '"')
                        .replace(/&gt;/g, '>')
                        .replace(/&lt;/g, '<')
                        .replace(/&amp;/g, '&')
            }

            var features = self.parseFeatures(content);
            if (!features) {
                self.deactivate();
                self.showMessage(OpenLayers.i18n('oleUploadFeatureNone'));
                return;
            }

            // At least one feature present: add to map and zoom to extent
            self.layer.addFeatures(features);
            self.layer.map.zoomToExtent(self.bounds);

            // Del the iframe...
            setTimeout(function () {
                self.deactivate();
            }, 250);
        };

        if (iframe.addEventListener) {
            iframe.addEventListener("load", eventHandler, true);
        }
        if (iframe.attachEvent) {
            iframe.attachEvent("onload", eventHandler);
        }
        form.submit();
    },

    /**
     * Instantiates an Input Element for Form
     * @param {string} id Name of element
     * @param {string} name Name of element
     * @param {string} type Type of element, e.g. text or hidden
     * @param {string} value optional initial Value for element
     * @param {!HTMLElement} parentElm optional parent Element
     * @return {!HTMLElement}
     */
    createInputElm: function (id, name, type, value, parentElm) {        
        // console.log("createInputElm");

        var inputElm = document.createElement('input');
        inputElm.setAttribute('type', type);
        inputElm.id = id;
        inputElm.name = name;
        inputElm.value = value ? value : null;
        if (parentElm) {
            parentElm.appendChild(inputElm);
        }
        return parentElm;
    },

    /**
     * Get the filename value from a File Input element
     * @param {!HTMLElement} fileElm file input Element
     * @return {string}
     */
    fileInputValue: function (fileElm) {
        // console.log("fileInputValue");
        if (fileElm.files) {
            return fileElm.files.length == 1 ? fileElm.files[0].name : null;
        } else {
            return fileElm.value;
        }
    },
    CLASS_NAME: "OpenLayers.Editor.Control.UploadFeature"
});