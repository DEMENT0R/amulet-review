<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global to
 * @global use
 * @global char
 */
// жарим сырое мясо на костре

if (intval(preg_replace('/.*' . "i.f.meat" . ':(\d+).*/', "\\1", $loc_i[$loc][$login]["items"])) > 0) {
    if (isset($loc_i[$loc]["i.s.fire"])) {
        $skills = explode("|", $loc_i[$loc][$login]["skills"]);
        if ($skills[30] > 0) {
            $char[6]                     = time() + 7;
            $loc_i[$loc][$login]["char"] = implode("|", $char);

            manageItems($loc, $login, "", "i.f.meat", 1);
            if (rand(1, 100) < $skills[30] * 20) {
                manageItems($loc, "", $login, "i.f.meat.fried", 1);
                addjournal($loc, $login, "Вы поджарили мясо на костре");
                addjournal($loc, "all", $char[0] . " поджарил мясо на костре", $login);
                if (rand(1, 100) < 5) {
                    addexp($loc, $login, 1);
                }
            } else {
                addjournal($loc, $login, "Вам не удалось на костре мясо, оно подгорело");
                addjournal($loc, "all", $char[0] . " не смог приготовить на костре мясо", $login);
            }
        } else {
            addjournal($loc, $login, "Ваш навык приготовления пищи равен 0, вы не умеете готовить пищу");
        }
    } else {
        addjournal($loc, $login, "Вначале найдите или разведите костер.");
    }
} else {
    addjournal($loc, $login, "У вас нет сырого мяса");
}