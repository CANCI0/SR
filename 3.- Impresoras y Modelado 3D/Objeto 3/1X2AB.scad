//Autor: Martín Cancio Barrera, UO287561

baseX = 40;
baseY = 3;
baseZ = 20;

verticalX = 40;
verticalY = 20;
verticalZ = 3;

module 1X2AB(){
    difference(){   
        translate([0, verticalY / 2 - verticalZ / 2, verticalY / 2 - baseY / 2])
        cube([baseX,baseY,baseZ], center = true);
        
        rotate([90,0,0])
        translate([0,verticalY / 2,0])
        cylinder(h = 30, r = 2.5, $fn = 20, center = true);
        
        ramp();
        
        mirror([1,0,0])
        ramp();
    }
    
    difference(){
        cube([verticalX,verticalY,verticalZ], center = true);
    
        baseHole();
        
        mirror([1,0,0])
        baseHole();
    }
}

module baseHole(){
    translate([baseX / 2 - 7.5 - 2.5, 0, 0])
    cylinder(h = 10, r = 2.5, $fn = 20, center = true);
}

module ramp(){
    translate([6.5,0,25])
    rotate([0,60,0])
    cube([40,20,20]);
}

1X2AB();