<?php
/**
 * @global attack
 * @global char
 * @global loc
 * @global login
 */
if ($attack) {
    if ($char[8]) {
        msg("<p>Вы призрак и поэтому не можете никого атаковать, найдите лекаря или камень воскрешения");
    }
    if (isset($loc_i[$loc][$attack])) {
        if (substr($attack, 0, 2) == 'n.' || substr($attack, 0, 2) == 'u.') {
            // установим статус, что нападаем на такого-то
            $char[7]                     = $attack;
            $loc_i[$loc][$login]["char"] = implode("|", $char);
            attack($loc, $login, $attack);
        } else {
            addjournal($loc, $login, "Нападать можно только на людей, NPC и монстров");
        }
    } else {
        addjournal($loc, $login, "Не на кого напасть");
    }
}