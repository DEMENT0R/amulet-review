<?php
// проверка всех онлайн и удаление в оффлайн
require_once("datafunc.php");

$count = 0;
$dh = opendir("online/");
while (($fname = readdir($dh)) !== false) {
    if ($fname != "." && $fname != ".." && $fname != "1.htaccess" && $fname != ".htaccess") {
        $count++;
        $tmp = file("online/" . $fname);
        if ($tmp[0] == ".") {
            if (filemtime("online/" . $fname) < time() - 60) {
                @unlink("online/" . $fname);
            }
            continue;
        }
        $tmp[0] = trim($tmp[0]);
        $tmp[1] = trim($tmp[1]);
        if (time() > $tmp[1] + $g_logout || $f_all == 1 || $f_all == $tmp[0]) {
            loadloc($tmp[0]);
            $res = "";
            if (isset($loc_i[$tmp[0]][$fname])) {
                if ($game["floc"] == $tmp[0] && $game["fid"] == $fname) {
                    if ($tmp[0] == "x1087x543" || $tmp[0] == "x1080x539" || $tmp[0] == "x1080x532" || $tmp[0] == "x1087x528") {
                        $loc1 = "x1095x532";
                    } else {
                        $loc1 = $tmp[0];
                    }
                    $loc_i[$loc1]["i.flag"] = "флаг лидерства|1|0";
                    $game["floc"] = $loc1;
                    $game["fid"] = "";
                    calcparam($tmp[0], $fname);
                }
                $auser = $loc_i[$tmp[0]][$fname];
                $auser["journal"] = "";
                $auser["loc"] = $tmp[0];
                $auser["time"] = time();
                unset($auser["msgt"]);
                unset($auser["macrol"]);
                unset($auser["trade"]);
                $tp = explode("|", $auser["user"]);
                if ($auser["user"] && $auser["char"] && $auser["skills"] && $auser["war"]) {
                    $res = SetData(substr($fname, 2), $tp[0], serialize($auser));
                    if (!$res) {
                        addnpc($fname, $tmp[0], "");
                    }
                }
                if (!$res || $f_all == 1 || $f_all == $tmp[0]) {
                    unset($loc_i[$tmp[0]][$fname]);
                }
            }
            if (!$res || $f_all == 1 || $f_all == $tmp[0]) {
                @unlink("online/" . $fname);
                $count--;
            }
        }
    }
}
closedir($dh);

if ($count > $g_max) {
    $count = $g_max;
}
$file = fopen("count.dat", "w");
if ($file !== false) {
    fputs($file, $count . " из " . $g_max);
    fclose($file);
}

$game["lastai"] = time();