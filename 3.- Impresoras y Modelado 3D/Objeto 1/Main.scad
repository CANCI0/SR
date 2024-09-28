use <BattRack.scad> 
use <Foot.scad>
use <Hip.scad>
use <LegPart-v3.scad>
use <PhoneHolder.scad>
use <ServoBrace.scad>

//Autor: Martín Cancio Barrera, UO287561

translate([44,0,0])
  foot();
  
mirror([1, 0, 0])
translate([44,0,0])
    foot();

rotate([0, 90, 0])
translate([-40, 0, 34])
legPartv3();

mirror([1, 0, 0])
rotate([0, 90, 0])
translate([-40,0,34])
legPartv3();

translate([0, 0, 47])
hip();

translate([0, -30, 42])
rotate([-15, 0, 0])
phoneHolder();

translate([0, 0, 50])
rotate([90, 0, 0])
servoBrace();

translate([0, 3, 42])
battrack();