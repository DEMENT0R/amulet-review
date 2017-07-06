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
 * @global cost
 * @global locai
 * @global tchar
 * @global g_list
 * @global trader
 * @global skill
 * @global min
 * @global max
 */

// приемы
// проверки
if (strpos($loc_i[$loc][$login]["priem"], $skill . ":") !== false) {
    msg("<p>Вы уже знаете этот прием", $tchar[0]);
}
if ($cost) {
    $money = intval(preg_replace('/.*i\.money:(\d+).*/', "\\1", $loc_i[$loc][$login]["items"]));
    if ($money < $cost) {
        msg("<p>У вас недостаточно денег (надо " . $cost . " монет)", $tchar[0]);
    }
    additem($loc, $login, "", "i.money", $cost, "items", "items", 1, -1, 1);
}
if ( ! $loc_i[$loc][$login]["priem"]) {
    $loc_i[$loc][$login]["priem"] = $skill . ":1";
} else {
    $loc_i[$loc][$login]["priem"] .= "|" . $skill . ":1";
}
msg("<p>Вы выучили новый прием!", $tchar[0]);