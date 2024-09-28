//Autor: Martín Cancio Barrera, UO287561

baseX = 73.6;
baseY = 14;
baseZ = 2;

lateralX = 2;
lateralY = 14;
lateralZ = 40;

backX = 2;
backY = 70;
backZ = 110;

frontX = 2;
frontY = 73.6;
frontZ = 10;

backPlateX = 52;
backPlateY = 17;
backPlateZ = 3;

module phoneHolder(){
    cube([baseX, baseY, baseZ], center = true);
    
    lateral();
    
    mirror([1, 0, 0]){
        lateral();
    }
        
    rotate([0, 0, 90]){
        translate([baseY / 2 - backX / 2, 0, backZ / 2])
        cube([backX, backY, backZ], center = true);
    }    
    rotate([0, 0, 90]){
        translate([- baseY / 2 + frontX / 2, 0, frontZ / 2 - baseZ / 2])
            cube([frontX, frontY, frontZ], center = true);
    }
    
    translate([0, 14, 35]){
        rotate([15, 0, 0])
        cube([backPlateX, backPlateY, backPlateZ], center = true);
    }    
    
    back_lateral();

    mirror([1, 0, 0])
    back_lateral();
}     

module lateral(){
    translate([baseX / 2 - lateralX / 2, 0, lateralZ / 2 - baseZ / 2])
        cube([lateralX, lateralY, lateralZ], center = true);
}

module back_lateral(){
    difference(){
        translate([backPlateX / 2 - 1.5, 10, 49]){
            rotate([-75, 0, 0])
            cube([3, 30, 17], center = true);
        }
        translate([0, 0, 50])
        cube([60, 10, 30], center = true);
    }
    
}

phoneHolder();