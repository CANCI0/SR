
module battrack(){
    translate([12, 0, 28])
        pared_lateral();
    
    translate([-15, 0, 28])
        pared_lateral();
    
    translate([14, 0, 28])
        pata();
    
    translate([-29, 0, 28])
        pata();
    
    translate([-15, 38, 28])
        cube(size = [30, 3, 20], center = false);
}  
   
module pared_lateral() {
    cube(size = [3, 41, 20], center = false);
}

module pata(){
    cube(size = [16.5, 11, 4], center = false);
}

     