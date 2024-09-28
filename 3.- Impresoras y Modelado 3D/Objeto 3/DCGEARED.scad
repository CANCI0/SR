//Autor: Martín Cancio Barrera, UO287561

cube_main = [20, 40, 40];
cube_inner = [13, 11, 40];
cube_side_large = [7, 3.5, 55];
cube_side_small = [4.5, 3.5, 55];

translate_side_large = [0, 17.5, 5];
translate_side_small = [0, 21, 0];

cylinder_h = 40;
cylinder_d = 3;
cylinder_fn = 20;

hole_h = 100;
hole_d = 5;
hole_fn = 20;

translate_hole_offsets = [[0, 10, 10], [0, -10, 10], [0, 10, -10], [0, -10, -10]];

module DCGEARED(){
    difference(){
        cube(cube_main, center = true);
        translate([0, 0, 5])
        cube(cube_inner, center = true);
        
        sideHole();
        mirror([0, 1, 0]) sideHole();
        
        cylinder(h = cylinder_h, d = cylinder_d, $fn = cylinder_fn, center = true);
        
        holes();
    }
}

module sideHole(){
    translate(translate_side_large)
    cube(cube_side_large, center = true);
    
    translate(translate_side_small)
    cube(cube_side_small, center = true);
}

module holes(){
    for (i = [0:3]) {
        translate(translate_hole_offsets[i])
        rotate([0, 90, 0])
        cylinder(h = hole_h, d = hole_d, $fn = hole_fn, center = true);
    }
}
