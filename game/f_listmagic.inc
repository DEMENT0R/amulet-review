<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global loc_t
 * @global loc_tt
 * @global to
 * @global game
 * @global sid
 * @global PHP_SELF
 * @global char
 * @global up
 * @global down
 * @global num
 * @global act
 */
// список магии

// в $to цель, если есть
use MaxDark\Amulet\OldCode\ViewOptions;

if ( ! $loc_i[$loc][$login]["magic"]) {
    msg("<p>Ваша книга заклинаний пуста, найдите NPC, который согласится учить вас магии.");
}
$items = explode("|", $loc_i[$loc][$login]["magic"]);
if ($up) {
    if (strpos($loc_i[$loc][$login]["magic"], $up . ":") === false) {
        msg("Нет такого заклинания");
    }
    for ($i = 0; $i < count($items); $i++) {
        if (strpos($items[$i], $up . ":") !== false) {
            break;
        }
    }
    if ($i == 0) {
        array_push($items, $items[$i]);
        array_shift($items);
    } else {
        $tc            = $items[$i - 1];
        $items[$i - 1] = $items[$i];
        $items[$i]     = $tc;
    }
    $loc_i[$loc][$login]["magic"] = implode("|", $items);
    msg("Заклинание передвинуто вверх.");
}
if ($down) {
    $up = $down;
    if (strpos($loc_i[$loc][$login]["magic"], $up . ":") === false) {
        msg("Нет такого заклинания");
    }
    for ($i = 0; $i < count($items); $i++) {
        if (strpos($items[$i], $up . ":") !== false) {
            break;
        }
    }
    if ($i == count($items) - 1) {
        array_unshift($items, $items[$i]);
        array_pop($items);
    } else {
        $tc            = $items[$i + 1];
        $items[$i + 1] = $items[$i];
        $items[$i]     = $tc;
    }
    $loc_i[$loc][$login]["magic"] = implode("|", $items);
    msg("Заклинание передвинуто вниз.");
}
if ($macro == 1) {
    $m = "&macros=list&num=$num&name=$name&act=$act#add";
} else {
    $m = '';
}
$stmp = "<p>Ваши заклинания:";
if ( ! $start) {
    $start = 0;
}
$keys = array_keys($items);
$listEnd = $start + ViewOptions::getInstance()->getMaxListSize();
for ($i = $start; $i < $listEnd && $i < count($keys); $i++) {
    $k = explode(":", $items[$keys[$i]]);
    $item = findItemByBaseId($k[0]);
    if (time() < $k[1]) {
        $item = $item[0] . " [осталось " . (round(($k[1] - time()) / 60) + 1) . " минут]";
    } else {
        $item = $item[0];
    }
    if ($to) {
        $stmp .= "<br/><a href=\"$PHP_SELF?sid=$sid&to=$to&use=" . $k[0] . $m . "\">" . $item . "</a>";
    } else {    // в след. экране all выберем цель $to для использования
        $stmp .= "\n<br/><anchor>" . $item . "<go href=\"#menu\"><setvar name=\"to\" value=\"" . $k[0] .
                 "\"/></go></anchor>";
    }
}
if ($start) {
    $stmp .= "\n<br/><a href=\"$PHP_SELF?sid=$sid&list=magic\">^ </a>";
}
if ($listEnd < count($keys)) {
    if ( ! $start) {
        $stmp .= "\n<br/>";
    }
    $stmp .= "<a href=\"$PHP_SELF?sid=$sid&to=$to&list=magic&start=" . ($listEnd) . "\">+ (" .
             (count($keys) - $listEnd) . ")</a>";
}
// карта меню
$stmp .= "\n</p>\n</card>\n<card id=\"menu\" title=\"Меню\">\n<p>\n<a href=\"$PHP_SELF?sid=$sid&use=$(to)\">Кастовать</a>\n<br/><a href=\"$PHP_SELF?sid=$sid&look=$(to)\">Инфо</a>\n<br/>[<a href=\"$PHP_SELF?sid=$sid&list=magic&up=$(to)\">Вверх</a> | <a href=\"$PHP_SELF?sid=$sid&list=magic&down=$(to)\">Вниз</a>]\n";
msg($stmp, "Магия", 1);