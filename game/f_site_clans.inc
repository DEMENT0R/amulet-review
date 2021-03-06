<?php
/**
 * @global info
 */

use MaxDark\Amulet\OldCode\PageType;
use MaxDark\Amulet\OldCode\ViewOptions;

if ($clan) {
    if ( ! file_exists("data/clans/" . $clan)) {
        msg("Клан $clan не существует");
    }
    $tmp = unserialize((file_get_contents("data/clans/" . $clan)));
    if ( ! isset($tmp["g"])) {
        msg("Ошибка при загрузке клана $clan, сообщите разработчику.");
    }
    if ($info) {
        if ($tmp["i"]) {
            msg($tmp["i"] . "<br/><anchor>[Назад]<prev/></anchor>", "Инфо о клане " . $clan);
        } else {
            msg("Нет описания");
        }
    }
    $keys = array_keys($tmp["g"]);
    $stmp = "Глава клана: " . substr($keys[0], 2);
    if ($tmp["i"]) {
        $stmp .= "<br/><a href=\"$PHP_SELF?sid=$sid&site=clans&clan=$clan&info=1\">Инфо о клане</a>";
    }
    $stmp .= "<br/>Состав:";

    if (count($tmp["m"]) > 0) {
        if ( ! $start) {
            $start = 0;
        }
        $keys = array_keys($tmp["m"]);
        $listEnd = $start + ViewOptions::getInstance()->getMaxListSize();
        for ($i = $start; $i < $listEnd && $i < count($keys); $i++) {
            $stmp .= "<br/>" . substr($keys[$i], 2);
        }
        if ($start) {
            $stmp .= "\n<br/><a href=\"$PHP_SELF?sid=$sid&site=clans&clan=$clan\">^ </a>";
        }
        if ($listEnd < count($keys)) {
            if ( ! $start) {
                $stmp .= "\n<br/>";
            }
            $stmp .= "<a href=\"$PHP_SELF?sid=$sid&site=clans&clan=$clan&start=" . ($listEnd) . "\">+ (" .
                     (count($keys) + 1 - $listEnd) . ")</a>";
        }
    } else {
        $stmp .= "<br/>Больше никого в клане нет.";
    }

    msg($stmp, "Клан *" . $clan . "*", 0, PageType::GUEST);
}

// все кланы

$arr = [];
$dh  = opendir("data/clans/");
while (($fname = readdir($dh)) !== false) {
    if ($fname != "." && $fname != ".." && $fname != "1.htaccess" && $fname != ".htaccess") {
        $tmp         = unserialize((file_get_contents("data/clans/" . $fname)));
        $arr[$fname] = count($tmp["m"]) + 1;
    }
}
closedir($dh);

if (count($arr) > 0) {
    $stmp = "<p>Всего кланов: " . count($arr);
    arsort($arr);
    if ( ! $start) {
        $start = 0;
    }
    $keys = array_keys($arr);
    $listEnd = $start + ViewOptions::getInstance()->getMaxListSize();
    for ($i = $start; $i < $listEnd && $i < count($keys); $i++) {
        $stmp .= "<br/><a href=\"$PHP_SELF?sid=$sid&site=clans&clan=" . $keys[$i] . "\">" . $keys[$i] . "</a> (" .
                 $arr[$keys[$i]] . " чел.)";
    }
    if ($start) {
        $stmp .= "\n<br/><a href=\"$PHP_SELF?sid=$sid&site=clans\">^ </a>";
    }
    if ($listEnd < count($keys)) {
        if ( ! $start) {
            $stmp .= "\n<br/>";
        }
        $stmp .= "<a href=\"$PHP_SELF?sid=$sid&site=clans&start=" . ($listEnd) . "\">+ (" .
                 (count($keys) + 1 - $listEnd) . ")</a>";
    }
} else {
    $stmp = "<p>Нет ни одного клана";
}

msg($stmp, "Кланы", 0, PageType::GUEST);