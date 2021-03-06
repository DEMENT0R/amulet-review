<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global to
 * @global use
 * @global char
 */
// i.log = удочка

if (intval(preg_replace('/.*' . "i.log" . ':(\d+).*/', "\\1", $loc_i[$loc][$login]["items"])) > 0) {

    $skills = explode("|", $loc_i[$loc][$login]["skills"]);
    if ($skills[27] > 0) {
        $char[6]                     = time() + 10;
        $loc_i[$loc][$login]["char"] = implode("|", $char);

        manageItems($loc, $login, "", "i.log", 1);        // удаляем 1 ветку

        if (rand(0, 100) < $skills[27] * 20) {
            addjournal($loc, $login, "Вы сделали удочку");
            addjournal($loc, "all", $char[0] . " сделал удочку", $login);
            manageItems($loc, "", $login, "i.fishman", 1);
            manageItems($loc, $login, "", "i.set.leska", 1);
        } else {
            addjournal($loc, $login, "Вы не смогли сделать удочку");
            addjournal($loc, "all", $char[0] . " пытался сделать удочку", $login);
        }

    } else {
        addjournal($loc, $login, "Ваш навык плотника равен 0, вы не умеете делать удочки");
    }
} else {
    addjournal($loc, $login, "Чтобы cделать удочку, нужна ветка от дерева");
}

