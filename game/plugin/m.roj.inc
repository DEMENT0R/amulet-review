<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global to
 * @global use
 * @global tdef
 */
// оглушает громом

if (isset($loc_i[$loc][$to]) && substr($to, 0, 2) == 'u.' && $to != $login) {
    $tchar = explode("|", $loc_i[$loc][$to]["char"]);
    if ($use == "m.roj") {
        addjournal($loc, $to, "рой мошек, мешает вам что либо сделать!");
        addjournal($loc, "all", substr($to, 2) . " облеплен мошкой!", $to);
        $tc                       = explode("|", $loc_i[$loc][$to]["char"]);
        $tc[6]                    = time() + 20;
        $loc_i[$loc][$to]["char"] = implode("|", $tc);
    }
    if ($tdef[0] == "p.d.n") {
        $loc_i[$loc][$to]["def"] = "";
    }
}