<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global to
 * @global use
 * @global char
 */

// ступка смешивает ингридиенты и бутылку с водой, получаем зелье

$arr = [    // id, name, dificalt -%, count, need_title, need_id
            1 => ["i.f.b.heal", "напиток жизни", 10, 1, "лечебная трава", "i.f.healherb"],
            2 => ["i.f.b.heal.great", "элексир жизни", 20, 3, "лечебная трава", "i.f.healherb"],
            3 => ["i.f.b.mana", "напиток маны", 10, 1, "огненный корень", "i.f.fileroot"],
            4 => ["i.f.b.mana.great", "элексир маны", 20, 3, "огненный корень", "i.f.fileroot"],
            5 => ["i.f.b.health", "напиток исцеления", 20, 3, "темный гриб", "i.f.mushroom.dark"],
            6 => ["i.f.b.health.great", "элексир исцеления", 40, 6, "темный гриб", "i.f.mushroom.dark"],

            7  => ["i.b.jad", "бутылка с ядом", 30, 1, "ядовитое жало", "i.h.jalo"],
            8  => ["i.b.fire", "бутылка с огнем", 60, 3, "огненный корень", "i.f.fileroot"],
            9  => ["i.b.holy", "святая вода", 60, 3, "огненный корень", "i.f.fileroot"],
            10 => ["i.acid", "кислота", 60, 2, "темный гриб", "i.f.mushroom.dark"],
];

$skills = explode("|", $loc_i[$loc][$login]["skills"]);

function tsret($s)
{
    if ($s > 0) {
        return $s;
    } else {
        return 0;
    }
}

if ( ! $to || ! isset($arr[$to])) {
    $stmp = "Выберите что сделать:";
    foreach (array_keys($arr) as $i) {
        $stmp .= "\n<br/><a href=\"$PHP_SELF?sid=$sid&use=$use&to=$i\">" . $arr[$i][1] . " (" . $arr[$i][3] . " " .
                 $arr[$i][4] . ", шанс: " . tsret($skills[23] * 20 - $arr[$i][2]) . "%)</a>";
    }
    msg($stmp);
}

if ($skills[23] * 20 - $arr[$to][2] > 0) {
    if (manageItems($loc, $login, "", "i.f.b.water", "count") == 0) {
        msg("Нужна бутылка с чистой водой (пустую бутылку можно наполнить у любого источника воды).");
    }
    $char[6]                     = time() + 15;
    $loc_i[$loc][$login]["char"] = implode("|", $char);

    manageItems($loc, $login, "", $arr[$to][5], $arr[$to][3], "items", "items", 1, 0, 1);    // удаляем ингридиенты
    manageItems($loc, $login, "", "i.f.b.water", 1, "items", "items", 1, 0, 1);            // удаляем бутылку с водой

    if (rand(0, 100) < $skills[23] * 20 - $arr[$to][2]) {
        addjournal($loc, $login, "Вы сделали " . $arr[$to][1]);
        addjournal($loc, "all", $char[0] . " сделал " . $arr[$to][1], $login);
        manageItems($loc, "", $login, $arr[$to][0], 1);
        if (round($arr[$to][2] / 10)) {
            addexp($loc, $login, round(rand(0, $arr[$to][2] / 10)));
        }
    } else {
        manageItems($loc, "", $login, "i.f.b.empty", 1);
        addjournal($loc, $login, "Вы не смогли сделать " . $arr[$to][1]);
        addjournal($loc, "all", $char[0] . " не смог сделать " . $arr[$to][1], $login);
    }

} else {
    addjournal($loc, $login, "Ваш навык алхимика слишком низок");
}