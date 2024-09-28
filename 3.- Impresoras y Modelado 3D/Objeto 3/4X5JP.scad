//Autor: Martín Cancio Barrera, UO287561

baseX = 100;
baseY = 80;
baseZ = 3;

rows = 5;
cols = 4;
d = 5;

diff = 20;
            
module 4X5JP(){
    difference(){
        cube([baseX, baseY, baseZ], center = true);
    
        holes();
    }
}

module holes(){
    x = 40;
    y = 30;
    z = 0;
    
    for (i = [0 : rows - 1]) {
        for(j = [0 : cols - 1]){
            translate([x - diff * i, y - diff * j, z])
                cylinder(h = 5, d = d, $fn = 20, center = true);
        }   
    
    }
}


4X5JP();