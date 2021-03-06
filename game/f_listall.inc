<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global loc_t
 * @global loc_tt
 * @global to
 * @global desc
 * @global exits
 * @global game
 * @global sid
 * @global PHP_SELF
 * @global char
 * @global use
 * @global glava
 */
// список всех объектов в локации и инвентори
// в $use что использовать, здесь надо определить $to

// выводим ссылку на себя, все окружение и все инвентори в отдельной карте
use MaxDark\Amulet\OldCode\ViewOptions;

$stmp = "<p><a href=\"$PHP_SELF?sid=$sid&to=" . $login . "&use=$use\">На себя</a>";
// по всем предметам в локации
if (count($loc_i[$loc]) > 1) {
    $stmp .= "\n<br/>Объекты:";
    if ( ! $start) {
        $start = 0;
    }
    $keys = array_keys($loc_i[$loc]);
    $listEnd = $start + ViewOptions::getInstance()->getMaxListSize();
    for ($i = $start; $i < $listEnd && $i < count($keys); $i++) {
        if ($keys[$i] != $login) {
            $stmp .= "\n<br/><a href=\"$PHP_SELF?sid=$sid&to=" . $keys[$i] . "&use=$use";
            if ($glava == 1) {
                $stmp .= "&glava=1"; // используется в plugin/i.guildstone.inc
            }
            $stmp .= "\">";
            if (substr($keys[$i], 0, 2) == "i.") {
                $tmp = explode("|", $loc_i[$loc][$keys[$i]]);
                if (substr($keys[$i], 0, 4) != "i.s." && $tmp[1] > 1) {
                    $stmp .= $tmp[0] . " (" . $tmp[1] . ")";
                } else {
                    $stmp .= $tmp[0];
                }
            }
            if (substr($keys[$i], 0, 2) == "n." || substr($keys[$i], 0, 2) == "u.") {
                $tmp = explode("|", $loc_i[$loc][$keys[$i]]["char"]);
                $k   = $tmp[0];
                if (substr($keys[$i], 0, 2) == "u." && $tmp[12]) {
                    $k .= " (всадник)";
                }
                $st = '';
                if ($tmp[1] != $tmp[2]) {
                    if (round($tmp[1] * 100 / $tmp[2]) < 100) {
                        $st .= round($tmp[1] * 100 / $tmp[2]) . "%";
                    }
                }
                if ($game["floc"] == $loc && $game["fid"] == $keys[$i]) {
                    $st .= " с флагом!";
                }
                if (substr($keys[$i], 0, 2) == "u.") {
                    if ($tmp[8]) {
                        $st .= " призрак";
                    }
                    if ($tmp[9]) {
                        if ($tmp[9] == 1) {
                            $tmp[9] = "преступник";
                        }
                        $st .= " " . $tmp[9];
                    }
                }
                if ($tmp[7] && isset($loc_i[$loc][$tmp[7]])) {
                    $tmp1 = explode("|", $loc_i[$loc][$tmp[7]]["char"]);
                    if (substr($tmp[7], 0, 2) != "u." || (substr($tmp[7], 0, 2) != "u." && ! $tmp1[8])) {
                        $st .= " атакует " . $tmp1[0];
                    }
                }
                if ($st) {
                    if ($st{0} == ' ') {
                        $st = substr($st, 1);
                    }
                    $k .= " [" . $st . "]";
                }
                $stmp .= $k;
            }
            $stmp .= "</a>";
        }
    }
    if (count($keys) > 1 && $start) {
        $stmp .= "\n<br/><a href=\"$PHP_SELF?sid=$sid&list=all&use=$use\">^ </a>";
    }
    if ($listEnd < count($keys)) {
        if ( ! $start) {
            $stmp .= "\n<br/>";
        }
        $stmp .= "<a href=\"$PHP_SELF?sid=$sid&list=all&use=$use&start=" . ($listEnd) . "\">+ (" .
                 (count($keys) - $listEnd) . ")</a>";
    }
}

if ($loc_i[$loc][$login]["items"] != "") {
    $stmp .= "\n<br/>Инвентори:";
    $items = explode("|", $loc_i[$loc][$login]["items"]);

    if ( ! $start) {
        $start = 0;
    }
    $keys = array_keys($items);
    $listEnd = $start + ViewOptions::getInstance()->getMaxListSize();
    for ($i = $start; $i < $listEnd && $i < count($keys); $i++) {
        if ($items[$keys[$i]]) {
            $k = explode(":", $items[$keys[$i]]);
            $item = findItemByFullId($k[0]);
            $item = $item[0];
            if (strpos($k[0], "..") !== false) {
                $item .= " *";
            }
            if ($k[1] > 1) {
                $item .= " (" . $k[1] . ")";
            }
            $tbp = strpos($loc_i[$loc][$login]["equip"], $k[0]);
            if ($tbp !== false && ($loc_i[$loc][$login]["equip"]{$tbp + strlen($k[0])} == "|" ||
                                   $loc_i[$loc][$login]["equip"]{$tbp + strlen($k[0])} == "")
            ) {
                $item .= " [одето]";
            }
            $stmp .= "\n<br/><a href=\"$PHP_SELF?sid=$sid&to=" . $k[0] . "&use=$use" . "\">" . $item . "</a>";
        }
    }
    if ($start) {
        $stmp .= "\n<br/><a href=\"$PHP_SELF?sid=$sid&list=all\">^ </a>";
    }
    if ($listEnd < count($keys)) {
        if ( ! $start) {
            $stmp .= "\n<br/>";
        }
        $stmp .= "<a href=\"$PHP_SELF?sid=$sid&list=all&use=$use&start=" . ($listEnd) . "\">+ (" .
                 (count($keys) - ($listEnd)) . ")</a>";
    }
}
msg($stmp, "Укажите цель");