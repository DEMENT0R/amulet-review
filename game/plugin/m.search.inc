<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global to
 * @global use
 * @global char
 */
// по всем соседним локациям
$arr = [];
for ($i = 2; $i < count($loc_c); $i += 2) {
    if ($loc_c[$i + 1] != $loc) {
        $arr[$loc_c[$i]] = ["na" => 0, "nc" => 0, "n" => 0, "u" => 0, "i" => 0, "uc" => 0, "ug" => 0];
        if (count($loc_i[$loc_c[$i + 1]]) > 0) {
            $keys = array_keys($loc_i[$loc_c[$i + 1]]);
            foreach ($keys as $j) {
                if (substr($j, 0, 4) == 'n.a.') {
                    $arr[$loc_c[$i]]["na"] += 1;
                } else {
                    if (substr($j, 0, 4) == 'n.c.') {
                        $arr[$loc_c[$i]]["nc"] += 1;
                    } else {
                        if (substr($j, 0, 2) == 'n.') {
                            $arr[$loc_c[$i]]["n"] += 1;
                        } else {
                            if (substr($j, 0, 2) == 'i.') {
                                $arr[$loc_c[$i]]["i"] += 1;
                            } else {
                                if (substr($j, 0, 2) == 'u.') {
                                    $tchar = explode("|", $loc_i[$loc_c[$i + 1]][$j]);
                                    if ($tchar[8]) {
                                        $arr[$loc_c[$i]]["ug"] += 1;
                                    } else {
                                        if ($tchar[9]) {
                                            $arr[$loc_c[$i]]["uc"] += 1;
                                        } else {
                                            $arr[$loc_c[$i]]["u"] += 1;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

        }
    }
};
//print_r($arr);
// выводим
$stmp = "<p>Вы чуствуете, что:";
foreach (array_keys($arr) as $i) {
    $stmp .= "<br/>" . $i . ": ";
    $b = "";
    if ($arr[$i]["nc"]) {
        $stmp .= $b . $arr[$i]["nc"] . " монстров";
        $b = ", ";
    }
    if ($arr[$i]["uc"]) {
        $stmp .= $b . $arr[$i]["uc"] . " преступников";
        $b = ", ";
    }
    if ($arr[$i]["ug"]) {
        $stmp .= $b . $arr[$i]["ug"] . " призраков";
        $b = ", ";
    }
    if ($arr[$i]["u"]) {
        $stmp .= $b . $arr[$i]["u"] . " игроков";
        $b = ", ";
    }
    if ($arr[$i]["na"]) {
        $stmp .= $b . $arr[$i]["na"] . " животных";
        $b = ", ";
    }
    if ($arr[$i]["n"]) {
        $stmp .= $b . $arr[$i]["n"] . " человек";
        $b = ", ";
    }
    if ($arr[$i]["i"]) {
        $stmp .= $b . $arr[$i]["i"] . " предметов";
        $b = ", ";
    }
    if ( ! $b) {
        $stmp .= " никого";
    }
}

msg($stmp, "Поиск");

