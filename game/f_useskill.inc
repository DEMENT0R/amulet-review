<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global loc_t
 * @global loc_tt
 * @global item
 * @global sid
 * @global PHP_SELF
 * @global char
 * @global to
 * @global use
 * @global id
 */
// использование скиллов

$skills = explode("|", $loc_i[$loc][$login]["skills"]);
if ($use == 'skill.necro') {
    include "f_necro.inc";
}
if ($use == 'skill.meditation') {
    if ($char[3] >= $char[4]) {
        msg("Ваш запас маны полон");
    }
    if ($skills[5] == 0) {
        msg("Ваш навык медитации равен нулю, вы не умеете медитировать");
    }
    $char[6]                     = time() + 5;
    $loc_i[$loc][$login]["char"] = implode("|", $char);
    if (rand(0, 100) <= $skills[5] * 15) {
        $mana = rand(1, $skills[5]);
        if ($char[3] + $mana > $char[4]) {
            $mana = $char[4] - $char[3];
        }
        $char[3] += $mana;
        $loc_i[$loc][$login]["char"] = implode("|", $char);
        addjournal($loc, $login, "Мана +" . $mana);
    } else {
        addjournal($loc, $login, "Медитация прервалась");
    }
}
if ($use == 'skill.animaltaming') {
    if ( ! $to) {
        $list = 'all';
    } else {
        if ( ! isset($loc_i[$loc][$to]) || substr($to, 0, 4) != "n.a.") {
            msg("<p>Нет цели или вы пытаетесь приручить не животное");
        }
        $tchar = explode("|", $loc_i[$loc][$to]["char"]);
        if ($tchar[8]) {
            $tame = 10 * ($skills[7] + 1 - $tchar[8]);
            if ($tame > 0 && $skills[20] > 0) {
                $char[6]                     = time() + 5;
                $loc_i[$loc][$login]["char"] = implode("|", $char);
                if (rand(0, 100) <= $tame) {
                    $loc_i[$loc][$to]["owner"] = $login . "|" . $login . "||" .
                                                 (time() + 60 + rand(0, $skills[20] * 10 * 60)) . "|0";
                    addjournal($loc, $login, "Вы приручили " . $tchar[0]);
                    addexp($loc, $login, rand(0, $tchar[8]));
                } else {
                    addjournal($loc, $login, "Не удалось приручить " . $tchar[0]);
                }
            } else {
                addjournal($loc, $login, "У вас слишком низкие навыки изучения и/или приручения животных");
            }
        } else {
            addjournal($loc, $login, "Это существо не приручаемо");
        }
    }
}
if ($use == 'skill.steal') {
    if ( ! $to) {
        $list = 'all';
    } else {
        if ($to == $login) {
            msg("<p>Нельзя воровать у самого себя");
        }
        if (isset($loc_i[$loc][$to]) && (substr($to, 0, 2) == "n." || substr($to, 0, 2) == "u.")) {
            if (substr($to, 0, 2) != 'n.' && substr($to, 0, 2) != 'u.') {
                msg("<p>Воровать можно только у других игроков и NPC");
            }
            if (substr($to, 0, 2) == 'u.') {
                $tskills = explode("|", $loc_i[$loc][$to]["skills"]);
                $tskills = $tskills[18];
            } else {
                $tskills = 3;
            } // у npc наблюдательность всегда 3
            $tchar = explode("|", $loc_i[$loc][$to]["char"]);
            if ($tchar[7] != $login && $char[7] != $to) {

                if ( ! $id) {    // список инвентори
                    $char[6]                     = time() + 5;
                    $loc_i[$loc][$login]["char"] = implode("|", $char);
                    if (rand(0, 100) < 7 * ($skills[1] + $skills[19] - $tskills)) {
                        if ( ! $loc_i[$loc][$to]["items"]) {
                            msg("<p>У " . $tchar[0] . " нет ни одного предмета.");
                        }
                        $stmp  = "<p>Предметы:";
                        $items = explode("|", $loc_i[$loc][$to]["items"]);
                        foreach (array_keys($items) as $i) {
                            if ($items[$i]) {
                                $k = explode(":", $items[$i]);
                                if (strpos($k[0], "_") !== false) {
                                    $ti = substr($k[0], 0, strpos($k[0], "_"));
                                } else {
                                    $ti = $k[0];
                                }
                                if (substr($k[0], 0, 5) == "i.rr.") {
                                    $title = explode("|", "руна|50");
                                } else {
                                    if (file_exists("items/" . $ti)) {
                                        $title = explode("|", (file_get_contents("items/" . $ti)));
                                    } else {
                                        continue;
                                    }
                                }
                                $stmp .= "<br/><a href=\"$PHP_SELF?sid=$sid&use=skill.steal&to=" . $to . "&id=" .
                                         $k[0] . "\">";
                                if (strpos($k[0], "..") !== false) {
                                    $title[0] .= " *";
                                }
                                if ($k[1] > 1) {
                                    $stmp .= $title[0] . " (" . $k[1] . ")";
                                } else {
                                    $stmp .= $title[0];
                                }
                                $stmp .= "</a>";
                            }
                        }
                        msg($stmp, $char[0], 0);
                    } else {
                        docrim($loc, $login, "вор");
                        addjournal($loc, $login, "Вас заметили!");
                        addjournal($loc, $to, $char[0] . " пытался подглядеть в ваш рюкзак!");
                        addjournal($loc, "all", $char[0] . " пытался подглядеть в рюкзак " . $tchar[0] . "!", $login,
                            $to);
                        if (substr($to, 0, 2) == "n.") {
                            $tchar[7]                 = $login;
                            $loc_i[$loc][$to]["char"] = implode("|", $tchar);
                        }
                    }
                } else {    // воруем предмет $id (все что есть)
                    $char[6]                     = time() + 10;
                    $loc_i[$loc][$login]["char"] = implode("|", $char);
                    $steal                       = 5 * ($skills[1] + $skills[6] - $tskills);
                    if (strpos($loc_i[$loc][$to]["equip"], $id) !== false) {
                        $steal = $steal / 2;
                    }
                    if ($steal > 0) {
                        if (rand(0, 100) < $steal) {
                            $count = intval(preg_replace('/.*' . $id . ':(\d+).*/', "\\1", $loc_i[$loc][$to]["items"]));
                            if (strpos($id, "_") !== false) {
                                $ti = substr($id, 0, strpos($id, "_"));
                            } else {
                                $ti = $id;
                            }
                            if (substr($id, 0, 5) == "i.rr.") {
                                $item = explode("|", "руна|50");
                            } else {
                                if (file_exists("items/" . $ti)) {
                                    $item = explode("|", (file_get_contents("items/" . $ti)));
                                } else {
                                    $count = 0;
                                }
                            }
                            if ($count == 0) {
                                msg("<p>У " . $tchar[0] . " нет этого предмета");
                            }
                            additem($loc, $to, $login, $id, $count, "items", "items", 0, -1, 1);//не сообщая в журнал
                            addjournal($loc, $login, "Вы украли у " . $tchar[0] . " " . $count . " " . $item[0] . "!");
                            if ($tskills && $loc_c[1]) {
                                addexp($loc, $login, rand(0, $tskills));
                            }
                        } else {
                            docrim($loc, $login, "вор");
                            addjournal($loc, $login, $tchar[0] . " застал вас за воровством!");
                            addjournal($loc, $to, $char[0] . " пытался вас обворовать!");
                            addjournal($loc, "all", $char[0] . " пытался обворовать " . $tchar[0] . "!", $login, $to);
                            if (substr($to, 0, 2) == "n.") {
                                $tchar[7]                 = $login;
                                $loc_i[$loc][$to]["char"] = implode("|", $tchar);
                            }
                        }
                    } else {
                        addjournal($loc, $login, "У вас слишком низкие навыки воровства и подглядывания");
                    }
                }
            } else {
                msg("Нельзя воровать у того, кто вас атакует или кого атакуете вы");
            }
        } else {
            msg("<p>Не у кого воровать");
        }
    }
}//skill.steal