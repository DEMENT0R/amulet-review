<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global loc_tt
 * @global use
 * @global char
 */
// телепорт в i.rr.loc
$manacost = 7;
$words    = "Tira Ruen";

if ($char[3] >= $manacost) {
    $skills = explode("|", $loc_i[$loc][$login]["skills"]);
    // вероятность кастинга равна заклинанию 2 уровня
    $cast = ($skills[13] * 0.5 + $skills[2] * 1.5) * 10 - 20;
    if ($cast < 25) {
        $cast = 10;
    }
    if ($cast > 0 && $skills[13]) {
        $char[3] -= $manacost;
        $char[6]                     = time() + 10; // 10 сек отдыхаем
        $loc_i[$loc][$login]["char"] = implode("|", $char);
        // произносим заклинание
        addjournal($loc, "all", $char[0] . ": " . $words);
        if (rand(0, 100) <= $cast) {    // удалось
            manageNPC($login, $loc, substr($use, 5));
            addjournal($loc, "all", $char[0] . ": " . $words, $login);
        } else {
            addjournal($loc, $login, "Заклинание сорвалось");
            addjournal($loc, "all", $char[0] . "(заклинание сорвалось)", $login);
        }
    } else {
        addjournal($loc, $login, "Слишком слабый навык магии");
    }
} else {
    addjournal($loc, $login, "Недостаточно маны");
}
