//Autor: Martín Cancio Barrera, UO287561

length = 110;

module VARILLA(){
    difference(){
        cylinder(h = length, d = 5, $fn = 20, center = true);
        
        translate([3,0,0])
        cube([2, 5, length], center = true);
    }
}

VARILLA();