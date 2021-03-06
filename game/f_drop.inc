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
 * @global num
 */

use MaxDark\Amulet\OldCode\PageType;

$loc_i[$loc][$login]["macrol"] = "drop|$drop||";
if ($drop) {            //linkБросить

    if ($drop == "f" && $game["floc"] == $loc && $game["fid"] == $login) {
        addjournal($loc, "all", $char[0] . " бросил флаг!", $login);
        if ($loc == "x1087x543" || $loc == "x1080x539" || $loc == "x1080x532" || $loc == "x1087x528") {
            $loc1 = "x1095x532";
        } else {
            $loc1 = $loc;
        }
        $loc_i[$loc1]["i.flag"] = "флаг лидерства|1|0";
        $game["floc"]           = $loc1;
        $game["fid"]            = "";
        calcparam($loc, $login);
        msg("Вы бросили флаг лидерства");
    }

    // $drop=id предмета [$num=кол-во]
    if ($char[8]) {
        msg("<p>Вы призрак и поэтому не можете ничего передать, поднять или бросить, найдите лекаря или камень воскрешения");
    }
    $tcount = intval(preg_replace('/.*' . $drop . ':(\d+).*/', "\\1", $loc_i[$loc][$login]["items"]));
    if ($tcount > 0) {
        // бросаем предмет в локацию
        $title = findItemByFullId($drop); // FIXME: dead code?
        // проверим кол-во
        if ($tcount > 1 && ! $num) {        // запросим кол-во
            $stmp = "<p>Укажите количество:\n<br/><input name=\"num\" format=\"*N\" maxlength=\"7\" value=\"" .
                    $tcount . "\"/>\n<br/><a href=\"$PHP_SELF?sid=$sid&drop=$drop&num=$(num)\">Отправить</a>";
            msg($stmp, "Бросить", 1, PageType::MSG, "num", $tcount);
        }
        if ( ! $num || $num < 1) {
            $num = 1;
        }    // если не указано, то 1 предмет
        if ($num > $tcount) {
            $num = $tcount;
        }    // и максимум берем все что есть
        manageItems($loc, $login, "loc", $drop, $num, "items", "items", 1, -1, 1);
    }
}

