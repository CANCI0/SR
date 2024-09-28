//Autor: Martín Cancio Barrera, UO287561

module foot(){
    
  minkowski(){
    translate([-22.5, -27, -2])
      cube([65, 55, 5]);
    cylinder(d=9, h=1, $fn = 30);
  }

  translate([-24.5, 0, 9])
    cube(size = [5, 5, 14], center = true);

  translate([5, 2.4, 9])
    cube(size = [5, 10, 14], center = true);
}
