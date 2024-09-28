//Autor: Martín Cancio Barrera, UO287561

h_base = 5;
d_base = 40;

h_central = 10;
d_central = 10;
fn_central = 15;

h_holes = 5;
d_holes = 5;
fn_holes = 15;
hole_radius = 10;
hole_count = 8;

h_cylinder = 30;
d_cylinder = 5;
fn_cylinder = 15;

h_border = 10;
d_border_outer = 40;
d_border_inner = 35;

module 20W(){
    difference(){
        base();
        holes();
        cylinder(h = h_cylinder, d = d_cylinder, $fn = fn_cylinder, center = true);
    }
    
    translate([3,0,5])
    cube([2, 5, 10], center = true);
    
    border();
}

module base(){
    cylinder(h = h_base, d = d_base);

    cylinder(h = h_central, d = d_central, $fn = fn_central);
}

module holes(){
    for(i = [0:360/hole_count:360]) {
        translate([hole_radius * cos(i), hole_radius * sin(i), 0])
        cylinder(h = h_holes, d = d_holes, $fn = fn_holes);
    }
}

module border(){
    difference(){
        cylinder(h = h_border, d = d_border_outer);
        cylinder(h = h_border, d = d_border_inner);
    }
}
20W();