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
 * @global skills
 */

if ($skills[31] == 0) {
    msg("Ваш навык некроманта равен нулю, вы не умеете поднимать мертвых.");
}
if (empty($to)) {
    $stmp = "";
    foreach (array_keys($loc_i[$loc]) as $i) {
        $item_subtype = substr($i, 0, 10);
        if (in_array($item_subtype, ["i.s.d.n.c.", "i.s.d.n.a."])) {
            $k = explode("|", $loc_i[$loc][$i]);
            $stmp .= "<br/><a href=\"$PHP_SELF?sid=$sid&use=skill.necro&to=" . $i . "\">" . $k[0] . "</a>";
        }
    }
    if (empty($stmp)) {
        $stmp = "<p>Рядом нет трупов, поднимать из мертвых можно только монстров и животных.";
    } else {
        $stmp = "<p>Выберите труп:" . $stmp;
    }
    msg($stmp);
}
if ( ! isset($loc_i[$loc][$to])) {
    msg("Нет цели");
}
$target_type = substr($to, 0, 10);
if (in_array($target_type, ["i.s.d.n.c.", "i.s.d.n.a."])) {
    msg("Поднимать можно только трупы монстров и животных");
}
$id = substr($to, 6, strrpos($to, ".") - 6);
$id = substr($id, 0, strrpos($id, "."));
if ( ! npcExists($id)) {
    msg("Ошибка: нет npc/" . $id . ", сообщите разработчику");
}
if ($char[3] < 6) {
    msg("Недостаточно маны (надо 6)");
}
$char[3] -= 6;
$char[6]                     = time() + 10;
$loc_i[$loc][$login]["char"] = implode("|", $char);
$title                       = explode("|", $loc_i[$loc][$to]);
$title                       = $title[0];
$title                       = substr($title, strpos($title, "(") + 1, -1);
if (rand(0, 100) <= $skills[31] * 5 + $skills[2] * 2) {

    // проверим, чтобы в локации не было более 3 призванных существ, остальных отпустим
    $counttmp = 0;
    foreach (array_keys($loc_i[$loc]) as $i) {
        if (isset($loc_i[$loc][$i]["owner"])) {
            $owner = explode("|", $loc_i[$loc][$i]["owner"]);
            if ($owner[0] == $login && substr($i, 0, 4) != "n.o.") {
                $counttmp++;
                if ($counttmp > 2) {
                    $tchar = explode("|", $loc_i[$loc][$i]["char"]);
                    addjournal($loc, $login, $tchar[0] . " покинул вас");
                    if ($owner[4]) {
                        manageNPC($i, $loc, "");
                    } else {
                        unset($loc_i[$loc][$i]["owner"]);
                    }
                }
            }
        }
    }

    unset($loc_i[$loc][$to]);
    // подготовим труп
    $npc      = loadNpcById($id);
    $tchar    = explode("|", $npc["char"]);
    $tchar[0] = $title . "-зомби";
    $tchar[2] = round($tchar[2] * 0.7);
    if ($tchar[2] < 1) {
        $tchar[2] = 1;
    }
    $tchar[1]    = $tchar[2];
    $npc["char"] = implode("|", $tchar);
    unset($npc["bank"]);
    unset($npc["osvej"]);
    unset($npc["equip"]);
    unset($npc["items"]);
    unset($npc["itemsrnd"]);
    $twar    = explode("|", $npc["war"]);
    $twar[1] = round($twar[1] * 0.7);
    if ($twar[1] < 0) {
        $twar[1] = 0;
    }
    $twar[2] = round($twar[2] * 0.7);
    if ($twar[2] < 0) {
        $twar[2] = 0;
    }
    $twar[13] = 0;
    unset($twar[15]);
    $npc["war"] = implode("|", $twar);
    $tc = rand(300, 300 + ($skills[31] + $skills[2]) * 90);
    $tc = time() + $tc;
    $npc["owner"] = implode('|',[
        $login, // хозяин
        $login, // за кем следуем
        $login, // кого охраняем
        $tc,    // время следования
        1       // флаг, удалить нпс, когда отпустили
    ]);
    $zombie = "n.z." . $id . "." . chr(rand(97, 122)) . chr(rand(97, 122)) . chr(rand(97, 122)) . chr(rand(97, 122));
    $loc_i[$loc][$zombie] = $npc;
    addjournal($loc, $login, "Вы подняли из мертвых " . $title);
    addjournal($loc, "all", $char[0] . " поднял из мертвых " . $title, $login);
    if (rand(1, 100) < 5) {
        addexp($loc, $login, 1);
    }
    if ($loc_c[1]) {
        docrim($loc, $login);
    }
} else {
    addjournal($loc, $login, "Вам не удалось поднять из мертвых труп " . $title);
    addjournal($loc, "all", $char[0] . " пытался поднять из мертвых труп " . $title, $login);
}



