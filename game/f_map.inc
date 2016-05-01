<?php

// для вывода картинки использует m.php!!! (чтобы лишний раз не обращаться к игре)

// >1650
function calctc($loc)
{
    if ($loc == "_begin") $loc = "x1158x523";
    if ($loc == "arena") $loc = "x1086x501";
    if (substr($loc, 0, 4) == "c.1.") $loc = "x1429x168";
    if (substr($loc, 0, 4) == "c.2.") $loc = "x781x429";
    if (substr($loc, 0, 4) == "c.3.") $loc = "x1129x369";
    if (substr($loc, 0, 4) == "c.4.") $loc = "x2320x348";

    $tc = explode("x", $loc);
    if ($tc[2] > 1101) {
        $tc[1] = round(($tc[1] - 20) / 6);
        $tc[2] = round(($tc[2] - 1101) / 6);
        $tc[3] = 2;
    } else
        if ($tc[1] > 1650) {
            $tc[1] = round(($tc[1] - 450 - 1200) / 15);
            $tc[2] = round($tc[2] / 15);
            $tc[3] = 1;
        } else {
            $tc[1] = round(($tc[1] - 450) / 12);
            $tc[2] = round($tc[2] / 12);
            $tc[3] = 0;
        }
    return $tc;
}

$tc = calctc($l);
$tcf = calctc($f);

srand((float)microtime() * 10000000);
$stmp = "<p align=\"center\"><img alt=\"map\" src=\"m.php?l=$loc&amp;f=" . $game["floc"] . "&amp;img=1&amp;r=" . rand(99, 999) . "&amp;bw=$map\"/><br/><a href=\"$PHP_SELF?sid=$sid\">В игру</a></p>";
$stmp .= "<p>Вы на ";
if ($tc[3] == 2) $stmp .= "Волчьем острове."; else if ($tc[3]) $stmp .= "территории Ансалона."; else $stmp .= "основной территории.";
if (!$game["floc"]) $fc = "неизвестно у кого (попробуйте обновить карту) "; else if ($game["fid"]) $fc = "у " . $game["fchar"] . " "; else $fc = "сейчас никому не принадлежит ";
$stmp .= "<br/>Флаг лидерства [<a href=\"m.php?flag=1\">?</a>] " . $fc;
if ($tcf[3] != $tc[3]) {
    $stmp .= "на ";
    if ($tc[3] == 2) $stmp .= "Волчьем острове."; else if ($tcf[3]) $stmp .= "территории Ансалона."; else $stmp .= "основной территории.";
}

$stmp .= "<br/><a href=\"m.php?info=1\">Помощь</a>";

msg($stmp);