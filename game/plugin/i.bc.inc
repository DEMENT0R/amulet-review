<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global to
 * @global $use
 */
// если i.bc_, то букет типа i.bc_master_a1b23c45, а если i.bc.x, то цветок x, из кот. можно сделать букет или вставить в другой букет или соединить с другим цветком, образовав новый букет

if (substr($use, 0, 5) == "i.bc_") {
    msg("Чтобы посмотреть список цветов в букете, выберите Инфо, а если хотите вставить в него еще цветы, то выберите желаемый цветок из вашего рюкзака, потом Использовать и укажите в какой букет вставить.");
}

if ($to) {
    if (substr($to, 0, 4) != "i.bc") {
        msg("Цветы можно использовать либо на готовые букеты, либо на другие цветы.");
    }
    if (strpos($loc_i[$loc][$login]["items"], $use . ":") === false ||
        strpos($loc_i[$loc][$login]["items"], $to . ":") === false
    ) {
        msg("Цветы должны быть в вашем рюкзаке");
    }
    $num = intval(preg_replace('/.*' . $use . ':(\d+).*/', "\\1", $loc_i[$loc][$login]["items"]));

    if (substr($to, 0, 5) == "i.bc_") {    // добавляем в букет
        $ti = substr($to, strrpos($to, "_") + 1);
        $xF = preg_match_all("/(\w)(\d+)/", $ti, $regF);
        if ($xF >= 5) {
            msg("В один букет можно добавить не более 5 разных типов цветов");
        }
        $b = 0;
        for ($i = 0; $i < $xF; $i++) {
            if ($regF[1][$i] == $use{5}) {
                $b = 1;
                $regF[2][$i] += $num;
            }
        }
        if ( ! $b) {
            $regF[1][$xF] = $use{5};
            $regF[2][$xF] = $num;
            $xF++;
        }
        $ti = "";
        for ($i = 0; $i < $xF; $i++) {
            $ti .= $regF[1][$i] . $regF[2][$i];
        }
        manageItems($loc, $login, "", $use, $num, "items", "items", 1, 0, 1);
        manageItems($loc, $login, "", $to, 1, "items", "items", 1, 0, 1);
        manageItems($loc, "", $login, substr($to, 0, strrpos($to, "_") + 1) . $ti, 1);
    } else {            // объединяем с другими (или сами с собой) цветами в букет
        manageItems($loc, $login, "", $use, $num, "items", "items", 1, 0, 1);
        if ($to == $use) {
            manageItems($loc, "", $login, "i.bc_" . substr($login, 2) . "_" . $use{5} . $num, 1);
        } else {
            manageItems($loc, "", $login, "i.bc_" . substr($login, 2) . "_" . $use{5} . $num . $to{5} .
                                      intval(preg_replace('/.*' . $to . ':(\d+).*/', "\\1", $loc_i[$login]["items"])),
                1);
        }
    }
} else {
    $list = 'all';
}    // куда вставить цветок