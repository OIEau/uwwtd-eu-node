--Article 3
    -- nat
    drop table if exists calcul.cc_art3;
    SELECT cc as cc, aticle3compliance as art3, SUM(generatedload) as generatedload
    INTO calcul.cc_art3
    FROM harvest.eu_9th_agglomeration_all
    WHERE aggstate = '1' 
        AND generatedload >= 2000
    GROUP BY cc, aticle3compliance
    ORDER BY cc, aticle3compliance;
    
    -- nuts 2
    drop table if exists calcul.nuts2_art3;
    SELECT nust2code as nuts2, aticle3compliance as art3, SUM(generatedload) as generatedload
    INTO calcul.nuts2_art3
    FROM harvest.eu_9th_agglomeration_all
    WHERE aggstate = '1' 
        AND generatedload >= 2000
    GROUP BY nust2code, aticle3compliance
    ORDER BY nust2code, aticle3compliance;
    
    -- rbd
    drop table if exists calcul.rbd_art3;
    SELECT rbdcode as rbd, aticle3compliance as art3, SUM(generatedload) as generatedload
    INTO calcul.rbd_art3
    FROM harvest.eu_9th_agglomeration_all
    WHERE aggstate = '1' 
        AND generatedload >= 2000
    GROUP BY rbdcode, aticle3compliance
    ORDER BY rbdcode, aticle3compliance;

--Article 4
    -- nat
    drop table if exists calcul.cc_art4;
    SELECT cc as cc, article4compliance as art4, SUM(connectedload) as connectedload
    INTO calcul.cc_art4
    FROM harvest.eu_9th_agglomeration_all
    WHERE aggstate = '1' 
        AND generatedload >= 2000
    GROUP BY cc, article4compliance
    ORDER BY cc, article4compliance;

    -- nuts 2
    drop table if exists calcul.nuts2_art4;
    SELECT nust2code as nuts2, article4compliance as art4, SUM(connectedload) as connectedload
    INTO calcul.nuts2_art4
    FROM harvest.eu_9th_agglomeration_all
    WHERE aggstate = '1' 
        AND generatedload >= 2000
    GROUP BY nust2code, article4compliance
    ORDER BY nust2code, article4compliance;

    -- rbd
    drop table if exists calcul.rbd_art4;
    SELECT rbdcode as rbd, article4compliance as art4, SUM(connectedload) as connectedload
    INTO calcul.rbd_art4
    FROM harvest.eu_9th_agglomeration_all
    WHERE aggstate = '1' 
        AND generatedload >= 2000
    GROUP BY rbdcode, article4compliance
    ORDER BY rbdcode, article4compliance;
    
--Article 5
    -- nat
    drop table if exists calcul.cc_art5;
    SELECT cc as cc, article5compliance as art5, SUM(connectedload) as connectedload
    INTO calcul.cc_art5
    FROM harvest.eu_9th_agglomeration_all
    WHERE aggstate = '1' 
        AND generatedload >= 2000
    GROUP BY cc, article5compliance
    ORDER BY cc, article5compliance;

    -- nuts 2
    drop table if exists calcul.nuts2_art5;
    SELECT nust2code as nuts2, article5compliance as art5, SUM(connectedload) as connectedload
    INTO calcul.nuts2_art5
    FROM harvest.eu_9th_agglomeration_all
    WHERE aggstate = '1' 
        AND generatedload >= 2000
    GROUP BY nust2code, article5compliance
    ORDER BY nust2code, article5compliance;

    -- rbd
    drop table if exists calcul.rbd_art5;
    SELECT rbdcode as rbd, article5compliance as art5, SUM(connectedload) as connectedload
    INTO calcul.rbd_art5
    FROM harvest.eu_9th_agglomeration_all
    WHERE aggstate = '1' 
        AND generatedload >= 2000
    GROUP BY rbdcode, article5compliance
    ORDER BY rbdcode, article5compliance; 

--Article 6
    -- nat
    drop table if exists calcul.cc_art6;
    SELECT cc as cc, article6compliance as art6, SUM(connectedload) as connectedload
    INTO calcul.cc_art6
    FROM harvest.eu_9th_agglomeration_all
    WHERE aggstate = '1' 
        AND generatedload >= 2000
    GROUP BY cc, article6compliance
    ORDER BY cc, article6compliance;

    -- nuts 2
    drop table if exists calcul.nuts2_art6;
    SELECT nust2code as nuts2, article6compliance as art6, SUM(connectedload) as connectedload
    INTO calcul.nuts2_art6
    FROM harvest.eu_9th_agglomeration_all
    WHERE aggstate = '1' 
        AND generatedload >= 2000
    GROUP BY nust2code, article6compliance
    ORDER BY nust2code, article6compliance;

    -- rbd
    drop table if exists calcul.rbd_art6;
    SELECT rbdcode as rbd, article6compliance as art6, SUM(connectedload) as connectedload
    INTO calcul.rbd_art6
    FROM harvest.eu_9th_agglomeration_all
    WHERE aggstate = '1' 
        AND generatedload >= 2000
    GROUP BY rbdcode, article6compliance
    ORDER BY rbdcode, article6compliance ;
    
--Global compliance
    -- nat
    drop table if exists calcul.cc_compliance;
    SELECT cc as cc, globalcompliance as compliance, SUM(generatedload) as generatedload
    INTO calcul.cc_compliance
    FROM harvest.eu_9th_agglomeration_all
    WHERE aggstate = '1' 
        AND generatedload >= 2000
    GROUP BY cc, globalcompliance
    ORDER BY cc, globalcompliance;

    -- nuts 2
    drop table if exists calcul.nuts2_compliance;
    SELECT nust2code as nuts2, globalcompliance as compliance, SUM(generatedload) as generatedload
    INTO calcul.nuts2_compliance
    FROM harvest.eu_9th_agglomeration_all
    WHERE aggstate = '1' 
        AND generatedload >= 2000
    GROUP BY nust2code, globalcompliance
    ORDER BY nust2code, globalcompliance;

    -- rbd
    drop table if exists calcul.rbd_compliance;
    SELECT rbdcode as rbd, globalcompliance as compliance, SUM(generatedload) as generatedload
    INTO calcul.rbd_compliance
    FROM harvest.eu_9th_agglomeration_all
    WHERE aggstate = '1' 
        AND generatedload >= 2000
    GROUP BY rbdcode, globalcompliance
    ORDER BY rbdcode, globalcompliance; 

    
    
-- Main tables 
    -- cc
    drop table if exists calcul.cc_stat_art;
    WITH art3 AS(
        SELECT cc, 
            SUM(generatedload) as generatedload,
            SUM(CASE WHEN art3 IN ('NR','PD') THEN 0 ELSE generatedload END) as art3_target,
            SUM(CASE WHEN art3 IN ('C', 'QC') THEN generatedload ELSE 0 END) as art3_compliant 
        FROM calcul.cc_art3
        GROUP BY cc
    ),
    art4 AS(
        SELECT cc, 
            SUM(connectedload) as connectedload,
            SUM(CASE WHEN art4 IN ('NR','PD') THEN 0 ELSE connectedload END) as art4_target,
            SUM(CASE WHEN art4 = 'C' THEN connectedload ELSE 0 END) as art4_compliant
        FROM calcul.cc_art4
        GROUP BY cc
    ),
    art5 AS(
        SELECT cc, 
            SUM(connectedload) as connectedload,
            SUM(CASE WHEN art5 IN ('NR','PD') THEN 0 ELSE connectedload END) as art5_target,
            SUM(CASE WHEN art5 = 'C' THEN connectedload ELSE 0 END) as art5_compliant 
        FROM calcul.cc_art5
        GROUP BY cc
    ),
    art6 AS(
        SELECT cc, 
            SUM(connectedload) as connectedload,
            SUM(CASE WHEN art6 IN ('NR','PD') THEN 0 ELSE connectedload END) as art6_target,
            SUM(CASE WHEN art6 = 'C' THEN connectedload ELSE 0 END) as art6_compliant 
        FROM calcul.cc_art6
        GROUP BY cc
    ),
    gp AS(
        SELECT cc, 
            SUM(generatedload) as generatedload,
            SUM(CASE WHEN compliance IN ('NR','PD') THEN 0 ELSE generatedload END) as compliance_target,
            SUM(CASE WHEN compliance = 'C' THEN generatedload ELSE 0 END) as compliance_compliant 
        FROM calcul.cc_compliance
        GROUP BY cc
    )
    SELECT gp.cc, gp.generatedload, art4.connectedload,
        gp.compliance_target, gp.compliance_compliant, 
        art3.art3_target, art3.art3_compliant,
        art4.art4_target, art4.art4_compliant,
        art5.art5_target, art5.art5_compliant,
        art6.art6_target, art6.art6_compliant
    INTO calcul.cc_stat_art
    FROM gp 
        LEFT JOIN art3 ON gp.cc=art3.cc
        LEFT JOIN art4 ON gp.cc=art4.cc
        LEFT JOIN art5 ON gp.cc=art5.cc
        LEFT JOIN art6 ON gp.cc=art6.cc
    ORDER BY gp.cc;    
    
    --nuts2
    drop table if exists calcul.nuts2_stat_art;
    WITH art3 AS(
        SELECT nuts2, 
            SUM(generatedload) as generatedload,
            SUM(CASE WHEN art3 IN ('NR','PD') THEN 0 ELSE generatedload END) as art3_target,
            SUM(CASE WHEN art3 IN ('C', 'QC') THEN generatedload ELSE 0 END) as art3_compliant 
        FROM calcul.nuts2_art3
        GROUP BY nuts2
    ),
    art4 AS(
        SELECT nuts2, 
            SUM(connectedload) as connectedload,
            SUM(CASE WHEN art4 IN ('NR','PD') THEN 0 ELSE connectedload END) as art4_target,
            SUM(CASE WHEN art4 = 'C' THEN connectedload ELSE 0 END) as art4_compliant
        FROM calcul.nuts2_art4
        GROUP BY nuts2
    ),
    art5 AS(
        SELECT nuts2, 
            SUM(connectedload) as connectedload,
            SUM(CASE WHEN art5 IN ('NR','PD') THEN 0 ELSE connectedload END) as art5_target,
            SUM(CASE WHEN art5 = 'C' THEN connectedload ELSE 0 END) as art5_compliant 
        FROM calcul.nuts2_art5
        GROUP BY nuts2
    ),
    art6 AS(
        SELECT nuts2, 
            SUM(connectedload) as connectedload,
            SUM(CASE WHEN art6 IN ('NR','PD') THEN 0 ELSE connectedload END) as art6_target,
            SUM(CASE WHEN art6 = 'C' THEN connectedload ELSE 0 END) as art6_compliant 
        FROM calcul.nuts2_art6
        GROUP BY nuts2
    ),
    gp AS(
        SELECT nuts2, 
            SUM(generatedload) as generatedload,
            SUM(CASE WHEN compliance IN ('NR','PD') THEN 0 ELSE generatedload END) as compliance_target,
            SUM(CASE WHEN compliance = 'C' THEN generatedload ELSE 0 END) as compliance_compliant 
        FROM calcul.nuts2_compliance
        GROUP BY nuts2
    )
    SELECT gp.nuts2, gp.generatedload, art4.connectedload,
        gp.compliance_target, gp.compliance_compliant, 
        art3.art3_target, art3.art3_compliant,
        art4.art4_target, art4.art4_compliant,
        art5.art5_target, art5.art5_compliant,
        art6.art6_target, art6.art6_compliant
    INTO calcul.nuts2_stat_art
    FROM gp 
        LEFT JOIN art3 ON gp.nuts2=art3.nuts2
        LEFT JOIN art4 ON gp.nuts2=art4.nuts2
        LEFT JOIN art5 ON gp.nuts2=art5.nuts2
        LEFT JOIN art6 ON gp.nuts2=art6.nuts2
    ORDER BY gp.nuts2; 
    
    
    
    --rbd
    drop table if exists calcul.rbd_stat_art;
    WITH art3 AS(
        SELECT rbd, 
            SUM(generatedload) as generatedload,
            SUM(CASE WHEN art3 IN ('NR','PD') THEN 0 ELSE generatedload END) as art3_target,
            SUM(CASE WHEN art3 IN ('C', 'QC') THEN generatedload ELSE 0 END) as art3_compliant 
        FROM calcul.rbd_art3
        GROUP BY rbd
    ),
    art4 AS(
        SELECT rbd, 
            SUM(connectedload) as connectedload,
            SUM(CASE WHEN art4 IN ('NR','PD') THEN 0 ELSE connectedload END) as art4_target,
            SUM(CASE WHEN art4 = 'C' THEN connectedload ELSE 0 END) as art4_compliant
        FROM calcul.rbd_art4
        GROUP BY rbd
    ),
    art5 AS(
        SELECT rbd, 
            SUM(connectedload) as connectedload,
            SUM(CASE WHEN art5 IN ('NR','PD') THEN 0 ELSE connectedload END) as art5_target,
            SUM(CASE WHEN art5 = 'C' THEN connectedload ELSE 0 END) as art5_compliant 
        FROM calcul.rbd_art5
        GROUP BY rbd
    ),
    art6 AS(
        SELECT rbd, 
            SUM(connectedload) as connectedload,
            SUM(CASE WHEN art6 IN ('NR','PD') THEN 0 ELSE connectedload END) as art6_target,
            SUM(CASE WHEN art6 = 'C' THEN connectedload ELSE 0 END) as art6_compliant 
        FROM calcul.rbd_art6
        GROUP BY rbd
    ),
    gp AS(
        SELECT rbd, 
            SUM(generatedload) as generatedload,
            SUM(CASE WHEN compliance IN ('NR','PD') THEN 0 ELSE generatedload END) as compliance_target,
            SUM(CASE WHEN compliance = 'C' THEN generatedload ELSE 0 END) as compliance_compliant 
        FROM calcul.rbd_compliance
        GROUP BY rbd
    )
    SELECT gp.rbd, gp.generatedload, art4.connectedload,
        gp.compliance_target, gp.compliance_compliant, 
        art3.art3_target, art3.art3_compliant,
        art4.art4_target, art4.art4_compliant,
        art5.art5_target, art5.art5_compliant,
        art6.art6_target, art6.art6_compliant
    INTO calcul.rbd_stat_art
    FROM gp 
        LEFT JOIN art3 ON gp.rbd=art3.rbd
        LEFT JOIN art4 ON gp.rbd=art4.rbd
        LEFT JOIN art5 ON gp.rbd=art5.rbd
        LEFT JOIN art6 ON gp.rbd=art6.rbd
    ORDER BY gp.rbd; 


    
-- Stat by size : [2 000-10 000[ | [10 000-100 000[ | [100 000 - inf]
drop table if exists calcul.cc_stat_by_size;
SELECT cc, 
    SUM(CASE WHEN generatedload <= 10000 THEN 1 ELSE 0 END) number_2000_10000,
    SUM(CASE WHEN generatedload > 10000 AND generatedload<= 100000 THEN 1 ELSE 0 END) number_10000_100000,
    SUM(CASE WHEN generatedload > 100000 THEN 1 ELSE 0 END) number_more_100000,
    SUM(CASE WHEN generatedload <= 10000 THEN generatedload ELSE 0 END) load_2000_10000,
    SUM(CASE WHEN generatedload > 10000 AND generatedload <= 100000 THEN generatedload ELSE 0 END) load_100000,
    SUM(CASE WHEN generatedload < 100000 THEN generatedload ELSE 0 END) load_more_100000
INTO calcul.cc_stat_by_size
FROM harvest.eu_9th_agglomeration_all
WHERE aggstate = '1' 
    AND generatedload >= 2000
GROUP BY cc
ORDER BY cc;

-- Stat by size : [2 000-10 000[ & [10 000-15 000[ & [15 000 - 100 000[ & [100 000 - 150 000[ & [150 000 - inf[
drop table if exists calcul.cc_stat_by_size_5_class;
SELECT cc, 
    SUM(CASE WHEN generatedload <= 10000 THEN 1 ELSE 0 END) number_2000_10000,
    SUM(CASE WHEN generatedload > 10000 AND generatedload<= 15000 THEN 1 ELSE 0 END) number_10000_15000,
    SUM(CASE WHEN generatedload > 15000  AND generatedload<= 100000 THEN 1 ELSE 0 END) number_15000_100000,
    SUM(CASE WHEN generatedload > 100000  AND generatedload<= 150000 THEN 1 ELSE 0 END) number_100000_150000,
    SUM(CASE WHEN generatedload > 150000  THEN 1 ELSE 0 END) number_more_150000,
    SUM(CASE WHEN generatedload <= 10000 THEN generatedload ELSE 0 END) load_2000_10000,
    SUM(CASE WHEN generatedload > 10000 AND generatedload<= 15000 THEN generatedload ELSE 0 END) load_10000_15000,
    SUM(CASE WHEN generatedload > 15000  AND generatedload<= 100000 THEN generatedload ELSE 0 END) load_15000_100000,
    SUM(CASE WHEN generatedload > 100000  AND generatedload<= 150000 THEN generatedload ELSE 0 END) load_100000_150000,
    SUM(CASE WHEN generatedload > 150000  THEN generatedload ELSE 0 END) load_more_150000
INTO calcul.cc_stat_by_size_5_class
FROM harvest.eu_9th_agglomeration_all
WHERE aggstate = '1' 
    AND generatedload >= 2000
GROUP BY cc
ORDER BY cc;


    
CREATE OR REPLACE VIEW harvest.eu_10th_agglomeration_all_odbc AS 
    SELECT cc, aggcode, repcode, aggname, aggstate, rbdcode, nutscode, nust1code, nust2code, nust3code, bigcitycode, generatedload, aggcalculation, aggc1, aggmethodc1, aggc2, aggmethodc2, aggpercwithouttreatment, aggmethodwithouttreatment, aggpercprimtreatment, aggpercsectreatment, aggperstringenttreatment, aggsewagenetwork, aggbesttechnicalknowledge, aggseweroverflows_m3, aggseweroverflows_pe, agghaveregistrationsystem, aggexistmaintenanceplan, aggexplanationother, agginhabitants, aggforecast, aggaccoverflownumber, aggdilutionrates, aggaccoverflows, aggothermeasures, aggpressuretest, aggvideoinspections, connectedload, iasload, dischargewithouttreatment, aticle3compliance, article4compliance, article5compliance, article6compliance, globalcompliance, typeofsensitivearea, articleapplied, secondaryequipementinplace, secondaryperformanceok, morestringentequipmentmet, morestringentperformancemet, morestringentequipmentinplance, morestringentperformanceok, bigcitynotreatmentperc, bigcityprimaryperc, bigcitysecondayperc, bigcitymorestringentnandpperc, bigcitymorestringentotherperc, aggchanges, aggchangescomment, aggremarks, aggperiodover3, aggperiodover4, aggperiodover5, aggperiodover6, dtt3, dtt4t, dtt4p, dtt5t, dtt5p, repreportedperdiod, changed 
    FROM harvest.eu_10th_agglomeration_all;    
    
CREATE OR REPLACE VIEW harvest.eu_9th_agglomeration_all_odbc AS 
    SELECT cc, aggcode, repcode, aggname, aggstate, rbdcode, nutscode, nust1code, nust2code, nust3code, bigcitycode, generatedload, aggcalculation, aggc1, aggmethodc1, aggc2, aggmethodc2, aggpercwithouttreatment, aggmethodwithouttreatment, aggpercprimtreatment, aggpercsectreatment, aggperstringenttreatment, aggsewagenetwork, aggbesttechnicalknowledge, aggseweroverflows_m3, aggseweroverflows_pe, agghaveregistrationsystem, aggexistmaintenanceplan, aggexplanationother, agginhabitants, aggforecast, aggaccoverflownumber, aggdilutionrates, aggaccoverflows, aggothermeasures, aggpressuretest, aggvideoinspections, connectedload, iasload, dischargewithouttreatment, aticle3compliance, article4compliance, article5compliance, article6compliance, globalcompliance, typeofsensitivearea, articleapplied, secondaryequipementinplace, secondaryperformanceok, morestringentequipmentmet, morestringentperformancemet, morestringentequipmentinplance, morestringentperformanceok, bigcitynotreatmentperc, bigcityprimaryperc, bigcitysecondayperc, bigcitymorestringentnandpperc, bigcitymorestringentotherperc, aggchanges, aggchangescomment, aggremarks, aggperiodover3, aggperiodover4, aggperiodover5, aggperiodover6, dtt3, dtt4t, dtt4p, dtt5t, dtt5p, repreportedperdiod, changed 
    FROM harvest.eu_9th_agglomeration_all;    
    
CREATE OR REPLACE VIEW harvest.eu_10th_uwwtp_odbc AS 
    SELECT cc, ogc_fid, gml_id, uwwcode, repcode, uwwname, uwwstate, uwwe_prtrcode, uwwcollectingsystem, uwwnuts, uwwloadenteringuwwtp, uwwcapacity, uwwprimarytreatment, uwwsecondarytreatment, uwwnremoval, uwwpremoval, uwwuv, uwwchlorination, uwwozonation, uwwsandfiltration, uwwmicrofiltration, uwwspecification, uwwbod5perf, uwwcodperf, uwwtssperf, uwwntotperf, uwwptotperf, uwwotherperf, uwwbadperfdesign, uwwlatitude, uwwlongitude, uwwbodincomingmeasured, uwwcodincomingmeasured, uwwnincomingmeasured, uwwpincomingmeasured, uwwboddischargemeasured, uwwcoddischargemeasured, uwwndischargemeasured, uwwpdischargemeasured, uwwwastewatertreated, uwwmethodwastewatertreated, uwwremarks, uwwdateclosing, uwwaccidents, uwwbadperformance, uwwboddischargecalculated, uwwboddischargeestimated, uwwbodincomingcalculated, uwwbodincomingestimated, uwwcoddischargecalculated, uwwcoddischargeestimated, uwwcodincomingcalculated, uwwcodincomingestimated, uwwhistorie, uwwinformation, uwwndischargecalculated, uwwndischargeestimated, uwwnincomingcalculated, uwwnincomingestimated, uwwpdischargecalculated, uwwpdischargeestimated, uwwpincomingcalculated, uwwpincomingestimated, uwwother, uwwtreatmenttype, repreportedperdiod
    FROM harvest.eu_10th_uwwtp;
CREATE OR REPLACE VIEW harvest.eu_9th_uwwtp_odbc AS 
    SELECT cc, ogc_fid, gml_id, uwwcode, repcode, uwwname, uwwstate, uwwe_prtrcode, uwwcollectingsystem, uwwnuts, uwwloadenteringuwwtp, uwwcapacity, uwwprimarytreatment, uwwsecondarytreatment, uwwnremoval, uwwpremoval, uwwuv, uwwchlorination, uwwozonation, uwwsandfiltration, uwwmicrofiltration, uwwspecification, uwwbod5perf, uwwcodperf, uwwtssperf, uwwntotperf, uwwptotperf, uwwotherperf, uwwbadperfdesign, uwwlatitude, uwwlongitude, uwwbodincomingmeasured, uwwcodincomingmeasured, uwwnincomingmeasured, uwwpincomingmeasured, uwwboddischargemeasured, uwwcoddischargemeasured, uwwndischargemeasured, uwwpdischargemeasured, uwwwastewatertreated, uwwmethodwastewatertreated, uwwremarks, uwwdateclosing, uwwaccidents, uwwbadperformance, uwwboddischargecalculated, uwwboddischargeestimated, uwwbodincomingcalculated, uwwbodincomingestimated, uwwcoddischargecalculated, uwwcoddischargeestimated, uwwcodincomingcalculated, uwwcodincomingestimated, uwwhistorie, uwwinformation, uwwndischargecalculated, uwwndischargeestimated, uwwnincomingcalculated, uwwnincomingestimated, uwwpdischargecalculated, uwwpdischargeestimated, uwwpincomingcalculated, uwwpincomingestimated, uwwother, uwwtreatmenttype, repreportedperdiod
    FROM harvest.eu_9th_uwwtp;
    