//Autor: Martín Cancio Barrera, UO287561

cylinder_faces = 25;

module legPartv3(){
    difference(){
        cube([3, 40, 10], center = true); 
        
        rotate([0, 90, 0])
            cylinder(d = 4, h = 7.5, center = true, $fn = cylinder_faces);
        
        translate([0, 9, 0])
        rotate([0, 90, 0])
            cylinder(d = 1, h = 7.5, center = true, $fn = cylinder_faces);
        
        translate([0, -9, 0])
        rotate([0, 90, 0])
            cylinder(d = 1, h = 7.5, center = true, $fn = cylinder_faces);
        
    }
          
    translate([13, -18.5, 0])
        arm();
      
    difference(){
        translate([13, 18.5, 0])
            arm();
        
        translate([27, 18.5, 0])
        rotate([90, 0, 0])
            cylinder(r = 3, h = 3, center = true, $fn = cylinder_faces);
        
        translate([11, 18.5, 0])
        rotate([90, 0, 0])
            cylinder(d = 1, h = 3, center = true, $fn = cylinder_faces);
        
        translate([17.5, 18.5, 0])
        rotate([90, 0, 0])
            cylinder(d = 1, h = 3, center = true, $fn = cylinder_faces);
    }
    
    translate([27, -16, 0])
    rotate([90, 0, 0])
        cylinder(d = 4.375, h = 7.5, center = true, $fn = cylinder_faces);

}

module arm(){
    cube([28.5, 3, 10], center = true);
    rotate([90, 0, 0])
    translate([14, 0, 0])
            cylinder(r = 5, h = 3, center = true, $fn = cylinder_faces);
}