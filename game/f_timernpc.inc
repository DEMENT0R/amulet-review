<?php
//  загружаем в $npc из папки npc	id|resp_min:resp_max|move_num:time_min:time_max
if (gettype($loc_t[$i][$j]) == "array") {
    $npc = $loc_t[$i][$j];
    $tid = $npc["id"];
    unset($npc["id"]);
} else {
    $ta = explode("|", $loc_t[$i][$j]);
    $tid = $ta[0];
    if (substr($tid, 0, 4) == "n.c." || substr($tid, 0, 4) == "n.a.") $tid = substr($tid, 0, strrpos($tid, "."));
    if (!file_exists("npc/" . $tid)) {
        unset($loc_t[$i][$j]);
        return;
    }//("err: no npc/".$tid);
    include "npc/" . $tid;
    $tid = $ta[0];
    $twar = explode("|", $npc["war"]);
    $twar[15] = $i . ":" . $ta[1];
    $npc["war"] = implode("|", $twar);
    if ($ta[2]) {
        $tchar = explode("|", $npc["char"]);
        $tchar[10] = $ta[2];
        $npc["char"] = implode("|", $tchar);
    }
}

// случ. предметы
if (isset($npc["itemsrnd"])) {
    $irnd = explode("|", $npc["itemsrnd"]);
    foreach (array_keys($irnd) as $k) if ($irnd[$k]) {
        $trnd = explode(":", $irnd[$k]);
        $trndc = round(rand($trnd[2], $trnd[3]));
        if (rand(0, 100) <= $trnd[1] && $trndc > 0) {
            if ($npc["items"]) $npc["items"] .= "|" . $trnd[0] . ":" . $trndc; else $npc["items"] = $trnd[0] . ":" . $trndc;
        }
    }
    unset($npc["itemsrnd"]);
}

// респавн текущий
$loc_i[$i][$tid] = $npc;
unset($loc_t[$i][$j]);