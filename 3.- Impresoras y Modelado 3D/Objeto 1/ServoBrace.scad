centralPanelX = 30;
centralPanelY = 2;
centralPanelZ = 23.5;

lateralX = 2;
lateralY = 20.8;
lateralZ = 23.5;

lateralParallelX = 16.5;
lateralParallelY = 2;
lateralParallelZ = 23.5;

lastX = 10;
lastY = 2;
lastZ = 23.5;

module servoBrace(){
    difference(){
        servoUnion();
        
        //Orificio central
        rotate([90, 0, 0])
        cylinder(h = 30, d = 3, $fn = 10);
        
        //Orificios laterales
        hole();
        
        mirror([1, 0, 0])
        hole();
    }
    
}

module hole(){
    rotate([90, 0, 0])
    translate([33.5, 0, 0])
    cylinder(h = 30, d = 3, $fn = 10, center = true);
}

module servoUnion(){
    cube([centralPanelX, centralPanelY, centralPanelZ], center = true);
    
    servoHalf();
    
    mirror([1, 0, 0])
    servoHalf();
}

module servoHalf(){
    translate([centralPanelX / 2 - lateralX / 2, lateralY  / 2 - centralPanelY / 2, 0])
    cube([lateralX, lateralY, lateralZ], center = true);
    
    translate([centralPanelX / 2 + lateralParallelX / 2 - lateralX, lateralY - lateralParallelY / 2, 0])
    cube([lateralParallelX, lateralParallelY, lateralParallelZ], center = true);
    
    translate([centralPanelX / 2 - lateralX * 1.5 + lateralParallelX, lateralY  / 2 - centralPanelY / 2, 0])
    cube([lateralX, lateralY, lateralZ], center = true);
    
    translate([34, 0, 0])
    cube([lastX, lastY, lastZ], center = true);
}

servoBrace();
