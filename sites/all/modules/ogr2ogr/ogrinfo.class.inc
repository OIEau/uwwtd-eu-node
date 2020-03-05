<?php

/**
 * Could also implement Iterator: http://php.net/manual/en/class.iterator.php
 */
class OgrInfo {
  var $ogrinfo = '';
  var $uri = '';

  function __construct($uri) {
    if ($ogr2ogr_path = exec('which ogrinfo')) {
      $this->ogrinfo = $ogr2ogr_path;
		//$this->ogrinfo = "/usr/local/bin/ogrinfo";
      // TODO: Check that file exists at $uri
      // TODO: Perhaps $uri should be an array of strings rather than a string to allow for multiple uri's.
      $this->uri = $uri;
    }
  }

  function process($args = array()) {
    $output = array();
	if ($this->ogrinfo) {
      if ($this->uri) {
        $result = array();
		//Get the table name ==> name of file without extention 
		$uri = array_pop(explode('/', $this->uri));
		$table = substr($uri, 0, -4);
        $command = $this->ogrinfo .' -so '. $this->uri .' -sql "SELECT * FROM '.$table.'"';
        foreach ($args as $flag => $value) {
          $command .= ' '. $flag .' '. $value;
        }

        if ($output_sh = shell_exec($command)) {
			//parse info
			//first we removz all indent in output
			$output_sh = str_replace(
				array(",\n", ":\n"),
				array(",", ":"),
				$output_sh
			);
			//dsm($output_sh);
			$output_sh = explode("\n", $output_sh);
			if(!empty($output_sh)){
				foreach($output_sh as $line){
					if($line!=''){
						$pos = strpos($line, ':');
						if($pos){
							$key = substr($line, 0, $pos);
							$val = substr($line, $pos+1);
							$output[$key] = preg_replace( '/\s+/', ' ', trim($val));
						}
						else{
							$output[] = $line;
						}
					}
				}
			}
        }
        else {
          throw new Exception('ogrinfo could not execute');
        }

        return $output;
      }
    }
	return $output;
  }
}
