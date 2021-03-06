<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global to
 * @global use
 * @global char
 */

/**
 * @param $s
 *
 * @return int
 */
function tsret($s)
{
    if ($s > 0) {
        return $s;
    } else {
        return 0;
    }
}

$arr = [];
if ($use == "m.heal.all") {
    $arr = [$login => ""];
    if (strpos($char[0], "*") === false) {
        $clan = "";
    } else {
        $clan = substr($char[0], strpos($char[0], "*") + 1, strrpos($char[0], "*") - strpos($char[0], "*") - 1);
    }
    foreach (array_keys($loc_i[$loc]) as $i) {
        if ($i != $login && substr($i, 0, 2) != "i.") {
            $tchar = explode("|", $loc_i[$loc][$i]["char"]);
            if (strpos($tchar[0], "*") === false) {
                $tclan = "";
            } else {
                $tclan = substr($tchar[0], strpos($tchar[0], "*") + 1,
                    strrpos($tchar[0], "*") - strpos($tchar[0], "*") - 1);
            }
            $b = 0;
            if ($clan && $clan == $tclan) {
                $b = 1;
            }
            if (isset($loc_i[$loc][$i]["owner"]) && substr($loc_i[$loc][$i]["owner"], 0, strlen($login)) == $login) {
                $b = 1;
            }
            if ($b) {
                $arr[$i] = "";
            }
        }
    }
} else {
    if (isset($loc_i[$loc][$to]) && substr($to, 0, 2) != 'i.') {
        $arr = [$to => ""];
    }
}

if (count($arr) > 0) {
    foreach (array_keys($arr) as $to) {
        $tchar = explode("|", $loc_i[$loc][$to]["char"]);
        $heal  = rand(tsret($magic[4] - 10 + $skills[2] * 2),
            $magic[5] + $skills[2] * 2);    // только не повреждает, а лечит
        if ($tchar[1] + $heal > $tchar[2]) {
            $heal = $tchar[2] - $tchar[1];
        }
        $tchar[1] += $heal;
        if ($heal > 0) {
            $loc_i[$loc][$to]["char"] = implode("|", $tchar);
        }
        addjournal($loc, $to, "Жизнь +" . $heal);
        if ($to != $login) {
            addjournal($loc, $login, $tchar[0] . ": жизнь +" . $heal);
        }
        // если лечим крима, сами станомся кримом
        if ($to != $login) {
            if ( ! $char[9]) {
                if ($tchar[9] || substr($to, 0, 4) == 'n.c.') {
                    docrim($loc, $login, "лечил преступника");
                }
            }
        }
    }
} else {
    addjournal($loc, $login, "Некого лечить");
}
