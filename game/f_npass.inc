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
 * @global id
 * @global tmp
 */

use MaxDark\Amulet\OldCode\PageType;

if (time() < trim($tmp[2])) {
    $t = trim($tmp[2]) - time();
} else {
    $t = 0;
}
if ($t) {
    $s = trim($tmp[2]);
} else {
    $s = time() + 10;
}
$file = fopen("online/" . $login, "w");
if ($file !== false) {
    fputs($file, $loc . "\n" . time() . "\n" . $s);
    fclose($file);
}

$login = "";
if ($t) {
    $stmp = "Повторите через " . $t . " сек";
} else {
    $stmp = "Неверный пароль. Если вы сменили пароль, подождите 10 минут, проверьте список онлайн и войдите в игру заново.";
}
msg($stmp, "Ошибка", 0, PageType::GUEST);
