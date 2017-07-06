<?php
/**
 * @global to
 * @global from
 * @global id
 */
// перемещение npc
global $loc_i, $loc, $login, $page_d, $loc_tt;

if ($to && ! file_exists("loc_i/" . $to)) {
    return;
}

$tnpc = "";
if ($from && $from != $to) {
    loadloc($from);
    if (isset($loc_i[$from][$id])) {
        $floc  = explode("|", $loc_tt[$from]["d"]);
        $tnpc  = $loc_i[$from][$id];
        $tchar = explode("|", $tnpc["char"]);
        if ($to && array_search($to, $floc)) {
            addjournal($from, "all", $tchar[0] . " ушел " . $floc[array_search($to, $floc) - 1], $id);
        } else {
            addjournal($from, "all", $tchar[0] . " исчез", $id);
        }
        unset($loc_i[$from][$id]);
    }
}

if ($to && $from != $to) {
    loadloc($to);
    if (isset($loc_i[$to][$id])) {
        $tnpc  = $loc_i[$to][$id];
        $tchar = explode("|", $tnpc["char"]);
    }
    if ($tnpc) {
        $tloc = explode("|", $loc_tt[$to]["d"]);
        if ($from && array_search($from, $tloc)) {

            addjournal($to, "all", "Пришел " . $tchar[0], $id);
            if (substr($id, 0, 2) == "n.") {    // история следов npc
                $steps = explode(":", $tchar[12]);
                if (count($steps) == 0) {
                    $steps[] = $from;
                } else {
                    if ($steps[count($steps) - 1] == $to) {
                        unset($steps[count($steps) - 1]);
                    } else {
                        $steps[] = $from;
                    }
                }
                $tchar[12]    = implode(":", $steps);
                $tnpc["char"] = implode("|", $tchar);
            }
        } else {
            addjournal($to, "all", "Появился " . $tchar[0], $id);
        }
        $loc_i[$to][$id] = $tnpc;
        if ($from && substr($id, 0, 2) == "u.") {
            if ($floc[1] && ! $tloc[1]) {
                addjournal($to, $id, "Вы покинули охраняемую территорию");
            }
            if ( ! $floc[1] && $tloc[1]) {
                addjournal($to, $id, "Вы на охраняемой территории");
            }
        }
    }
}

if ($id == $login && $to && isset($loc_i[$to][$id])) {
    if ($loc == $to) {
        $page_d = 0;
    } else {
        $page_d = 1;
        $loc    = $to;
    }
}
