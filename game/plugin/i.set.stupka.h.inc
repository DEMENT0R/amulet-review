<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global to
 * @global use
 * @global char
 */
// ступка смешивает лечебную траву и пустую бутылку, получаем слабое зелье

if (intval(preg_replace('/.*' . "i.f.healherb" . ':(\d+).*/', "\\1", $loc_i[$loc][$login]["items"])) > 0 &&
    intval(preg_replace('/.*' . "i.f.b.empty" . ':(\d+).*/', "\\1", $loc_i[$loc][$login]["items"])) > 0
) {

    $skills = explode("|", $loc_i[$loc][$login]["skills"]);
    if ($skills[23] > 0) {
        $char[6]                     = time() + 6;
        $loc_i[$loc][$login]["char"] = implode("|", $char);

        // трава пропадает
        manageItems($loc, $login, "", "i.f.healherb", 1);

        if (rand(1, 100) < $skills[23] * 20 - 5) {
            manageItems($loc, $login, "", "i.f.b.empty", 1);
            manageItems($loc, "", $login, "i.f.b.heal.great", 1);
            addjournal($loc, $login, "Вы сделали элексир жизни");
            addjournal($loc, "all", $char[0] . " сделал элексир жизни", $login);
            addexp($loc, $login, rand(0, 2));
        } else {
            addjournal($loc, $login, "Вы не смогли сделать элексир жизни");
            addjournal($loc, "all", $char[0] . " пытался сделать элексир жизни", $login);
        }

    } else {
        addjournal($loc, $login, "Ваш навык алхимика равен 0, вы не умеете делать зелья");
    }
} else {
    addjournal($loc, $login, "Чтобы сделать элексир жизни, нужна целебная трава и пустая бутылка");
}

