<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global loc_t
 * @global loc_tt
 * @global game
 * @global sid
 * @global PHP_SELF
 * @global char
 * @global id
 * @global locai
 * @global i
 * @global j
 */
// убегаем
$b    = 0;
$k    = $locai[2 + 2 * rand(0, (count($locai) - 2) / 2 - 1) + 1];
$loc1 = explode("|", $loc_tt[$k]["d"]);
if ($locai[1] == $loc1[1]) {
    addjournal($loc, "all", $char[0] . " убегает");
    if ($char[10]) {
        $move     = explode(":", $char[10]);
        $move[3]  = time() + rand($move[1], $move[2]);
        $char[10] = implode(":", $move);
    }
    $char[7]               = "";
    $loc_i[$i][$j]["char"] = implode("|", $char);
    addnpc($j, $i, $k);
    $b = 1;
}