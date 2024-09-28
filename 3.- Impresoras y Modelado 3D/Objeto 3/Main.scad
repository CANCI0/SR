//Autor: Martín Cancio Barrera, UO287561

use <1X2AB.scad>;
use <4X5JP.scad>;
use <20W.scad>;
use <DCGEARED.scad>;
use <VARILLA.scad>;

translate_varilla = [30, 0, -13];
translate_20W = [30, -45, -13];
translate_1X2AB_1 = [30, -30, -3];
translate_1X2AB_2 = [30, 30, -3];
translate_DCGEARED_1 = [-30, -20, -11];
translate_DCGEARED_2 = [-30, 20, -11];

rotate_1X2AB_1 = [180, 0, 0];
rotate_1X2AB_2 = [180, 0, 180];
rotate_DCGEARED = [90, 90, 0];
rotate_varilla = [90, 180, 0];
rotate_20W_1 = [90, 90, 0];
rotate_20W_2 = [90, 0, 180];

translate(translate_1X2AB_1)
rotate(rotate_1X2AB_1)
    1X2AB();

translate(translate_1X2AB_2)
rotate(rotate_1X2AB_2)
    1X2AB();

4X5JP();

translate(translate_DCGEARED_1)
rotate(rotate_DCGEARED)
    DCGEARED();

translate(translate_DCGEARED_2)
rotate(rotate_DCGEARED)
    DCGEARED();

translate(translate_varilla)
rotate(rotate_varilla)
    VARILLA();

translate(translate_20W)
rotate(rotate_20W_1)
    20W();

translate([-30, 45, -13])
rotate(rotate_20W_2)
    20W();

translate([-30, 0, -13])
rotate(rotate_varilla)
    VARILLA();

translate([-30, -45, -13])
rotate(rotate_20W_1)
    20W();

translate(translate_varilla)
rotate(rotate_varilla)
    VARILLA();

translate(translate_20W)
rotate(rotate_20W_1)
    20W();

translate([30, 45, -13])
rotate(rotate_20W_2)
    20W();
