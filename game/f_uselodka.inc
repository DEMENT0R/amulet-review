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
 * @global tchar
 * @global id
 */

if ( ! $id) {
    msg("Куда плыть?<br/><a href=\"$PHP_SELF?sid=$sid&take=i.s.lodka&id=1\">К причалу</a><br/><a href=\"$PHP_SELF?sid=$sid&take=i.s.lodka&id=2\">В Ансалон</a><br/><a href=\"$PHP_SELF?sid=$sid&take=i.s.lodka&id=3\">К морю</a>");
}
if ($id == 2) {
    $b   = 1;
    $tc  = "x1965x623";
    $msg = "Добравшись по реке до водопада, вы обнаруживаете справа тропу, ведущую в гору. По ней вы переносите лодку и, проплыв между отвесных скал, пристаете на берегу крупного озера";
} else {
    if ($id == 3) {
        $b   = 1;
        $tc  = "x672x336";
        $msg = "Река принесла вас к морю. Проплыв еще немного вдоль берега, вы причаливаете к песчаному пляжу";
    } else {
        $b   = 0;
        $tc  = "x1103x618";
        $msg = "После нескольких часов плавания, вы пристали к пирсу около города и обнаружили, что лодка опять дала течь";
    }
}

if ($loc == $tc) {
    msg("Выберите другой пункт назначения");
}
addjournal($loc, "all", $char[0] . " уплыл на лодке", $login);
unset($loc_i[$loc]["i.s.lodka"]);
manageNPC($login, $loc, $tc);
if ($b) {
    $loc_i[$loc]["i.s.lodka"] = "лодка|0|";
} else {
    $loc_i[$loc]["i.s.lodkas"] = "сломанная лодка|0|";
}
msg($msg);