<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global loc_t
 * @global loc_tt
 * @global item
 * @global game
 * @global sid
 * @global PHP_SELF
 * @global char
 * @global $look
 */
$m = findItemByBaseId($look);
$skills = explode("|", $loc_i[$loc][$login]["skills"]);
function tsret($s)
{
    if ($s > 95) {
        $s = 95;
    }
    if ($s > 0) {
        return $s;
    } else {
        return 0;
    }
}

$stmp = "<p>" . $m[10];
$stmp .= "<br/><a href=\"$PHP_SELF?sid=$sid&look=magic.words\">Слова</a>: " . $m[3];
$stmp .= "<br/><a href=\"$PHP_SELF?sid=$sid&look=magic.level\">Уровень</a>: " . $m[2];
$stmp .= "<br/><a href=\"$PHP_SELF?sid=$sid&look=magic.mana\">Мана</a>: " . $m[1];
if ($m[4] || $m[5]) {
    if (substr($look, 0, 6) == "m.heal") {
        $stmp .= "<br/>Лечение: " . $m[4] . "-" . $m[5];
    } else {
        $stmp .= "<br/>Урон: " . $m[4] . "-" . $m[5];
    }
}
if ($m[6]) {
    $stmp .= "<br/>Требует цель";
}
if ($m[7]) {
    $stmp .= "<br/>Действует только на преступников";
}
$stmp .= "<br/><a href=\"$PHP_SELF?sid=$sid&look=magic.speed\">Скорость</a>: " . $m[8] . " сек";
$stmp .= "<br/><a href=\"$PHP_SELF?sid=$sid&look=magic.period\">Период</a>: " . round($m[9] / 60) . " мин " .
         round($m[9] - round($m[9] / 60) * 60) . " сек";
$stmp .= "<br/>----<br/>С учетом ваших характеристик:";
$stmp .= "<br/><a href=\"$PHP_SELF?sid=$sid&look=magic.shans\">Шанс</a>: ";
$cast = ($skills[13] * 0.5 + $skills[2] * 1.5) * 10 - $m[2] * 10 + 10 - (max($skills[0], 2) - 2) * 4;
if ($char[12]) {
    $cast -= 10;
}
if ($game["fid"] == $login && $game["floc"] == $loc) {
    $cast += 20;
}
if ( ! $skills[13]) {
    $stmp .= "0";
} else {
    $stmp .= tsret($cast);
}
if ($cast > 95) {
    $cast = 95;
}
$stmp .= " %";
if ($m[4] || $m[5]) {
    if (substr($look, 0, 6) == "m.heal") {
        $stmp .= "<br/>Лечение: ";
    } else {
        $stmp .= "<br/><a href=\"$PHP_SELF?sid=$sid&look=magic.uron\">Урон</a>: ";
    }
    $stmp .= tsret($m[4] - 10 + $skills[2] * 2) . " - " . ($m[5] + $skills[2] * 2);
}
$stmp .= "<br/>Скорость: " . ($m[8] + 3 - $skills[1] + (max($skills[0], 2) - 2) * 4) . " сек";
if (substr($look, 0, 4) == "m.w.") {
    $tper = $m[9] + (max($skills[0], 2) - 2) * 1200;
} else {
    $tper = $m[9];
}

$stmp .= "<br/>Период: " . round($tper / 60) . " мин " . round($tper - round($tper / 60) * 60) . " сек";
msg($stmp, $m[0]);



