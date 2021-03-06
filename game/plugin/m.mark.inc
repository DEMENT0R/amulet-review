<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global to
 * @global use
 * @global char
 */
// для рун id при загрузке предметов задаяется явно $item="руна|50";

if (substr($to, 0, 5) == 'i.rr.' && strpos($loc_i[$loc][$login]["items"], $to . ":") !== false) {
    if (substr($loc, 0, 2) == "c.") {
        msg("В замках нельзя помечать руны");
    }
    if ($loc == "arena") {
        msg("На арене нельзя помечать руны");
    }
    $tc = explode("x", $loc);
    if ($tc[2] >= 1099) {
        msg("На Волчьем острове магия рун перемещения не работает из-за влияния магических самоцветов в горной породе");
    }
    $id = "i.rr." . $loc;
    manageItems($loc, $login, "", $to, 1);
    manageItems($loc, "", $login, $id, 1);
    addjournal($loc, $login, "Руна помечена в это место");
} else {
    addjournal($loc, $login, "Заклинание можно использовать только на руну телепортации");
}
