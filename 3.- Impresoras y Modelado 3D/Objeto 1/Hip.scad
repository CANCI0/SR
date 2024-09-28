//Autor: Martín Cancio Barrera, UO287561

square_holeX= 12.5;
square_holeY= 23.5;
square_holeZ= 23.5;

square_hole_offset = 21.25;

big_hole_offsetX = 33.5;
little_hole_offsetY = 14.125;

big_hole_radius = 1.5;

little_hole_radius = 0.75;

module hip(){  
    difference(){
        minkowski(){
          cube([71, 31, 4.75], center = true);
          cylinder(d=9,h=1, $fn = 10);
        }

        translate([square_hole_offset, 0, 0])
            square_hole();
        
        translate([-square_hole_offset, 0, 0])
            square_hole();
        
        hole(big_hole_radius);
        
        translate([big_hole_offsetX, 0, 0])
            hole(big_hole_radius);
        
        translate([-big_hole_offsetX, 0, 0])
            hole(big_hole_radius);
        
        translate([square_hole_offset, little_hole_offsetY, 0])
            hole(little_hole_radius);
        
        translate([square_hole_offset, -little_hole_offsetY, 0])
            hole(little_hole_radius);
        
        translate([-square_hole_offset, little_hole_offsetY, 0])
            hole(little_hole_radius);
            
        translate([-square_hole_offset, -little_hole_offsetY, 0])
        hole(little_hole_radius);
    }

}

module square_hole(){
    cube([square_holeX, square_holeY, square_holeZ], center = true);
}

module hole(r){
    cylinder(h = 15.75, r = r, center = true, $fn = 15);
}

