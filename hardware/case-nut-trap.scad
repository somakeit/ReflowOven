

use <MCAD/polyholes.scad>;
// Reflow Oven Gen 2
// Mount for holding face plate nut in case cutout

mount_length = 32.25;
mount_width  =  9.10;
mount_height =  3.00;

mount_insert_length = 13.80;
mount_insert_d      =  3.15;
mount_insert_h      =  1.00;
mount_hole_d        =  3.30;
mount_nut_trap_d    =  5.15;
mount_nut_trap_h    =  2.20;

module hex_nut() {
    n = 6;  // hex nut
    cylinder(h = h, r = r / cos (180 / n), $fn = n);
}

difference() {
    union() {
        cube([mount_length, mount_width, mount_height]);
        translate([(mount_length - mount_insert_length + mount_insert_d) / 2.0, mount_width / 2.0, mount_height + mount_insert_h / 2.0]) cylinder(r = mount_insert_d / 2.0, h = mount_insert_h, center=true, $fn = 20);
        translate([(mount_length + mount_insert_length - mount_insert_d) / 2.0, mount_width / 2.0, mount_height + mount_insert_h / 2.0]) cylinder(r = mount_insert_d / 2.0, h = mount_insert_h, center=true, $fn = 20);
    }
    // mount holes
    translate([mount_length / 2.0, mount_width / 2.0, -1.0]) {
        polyhole(d = mount_hole_d, h = mount_height + 2.0);
        hex_nut(r = mount_nut_trap_d / 2.0, h = mount_nut_trap_h);
    }
}
