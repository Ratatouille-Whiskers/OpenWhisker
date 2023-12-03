# Model Notes

General TODO:

- [X] Create a Mould "Platter" For Ratio Testing
- [ ] Create Easy-Edit Parametric Versions for the parts
  - [ ] Whisker Base
  - [ ] Whisker Socket
  - [ ] Whisker Silicone Bearing Mould

## Whisker Base

### [V1](STL/Whisker%20Base/Whisker%20Base%20V1.stl)

- Was too tall (particularly at the bottom) and would need adjusting if wanting to use the mount for breadboard development

### [V2](STL/Whisker%20Base/Whisker%20Base%20V2.stl)

![Whisker Base V2 image](../Images/Whisker%20Base%20V2.png)

- Adjusted the height so the Sensor can more easily socket into a breadboard when assembled

### [V3](STL/Whisker%20Base/Whisker%20Base%20V3.stl)

![Whisker Base V3 image](<../Images/Whisker Base V3.png>)

- re-centered Silicone Bearing Hole
- added internal cut-out ring in bearing hole so that it can hold better
- Shortened the Height by ~2mm therefore making the bearing space shorter too

### [V4](STL/Whisker%20Base/Whisker%20Base%20V4.stl)

- Made it 4mm taller around the bearing cutout area
- Changed the bearing top chamfer from 1mm to 2mm
- Increased the bearing "outer" ring lip from 3mm tall to 4 mm tall
  - Re-centered this to match the new bearing height

## Whisker Socket

### [V1](STL/Whisker%20Socket/Whisker%20Socket%20V1.stl)

- The socket is designed to a 3mm diameter (printed) whisker
  - The space for the whisker was 4mm to small and would not work
- The socket for inserting a a 5x1 magnet was also too small and need to be wider

### [V2](STL/Whisker%20Socket/Whisker%20Socket%20V2.stl)

- Made it shorter to match the changes to V3 of the base

Top Angle View:

![Whisker Socket V2 - Top](../Images/Whisker%20Sicket%20V2%20-%20Top.png)

Top Angle View:

![Whisker Socket V2 - Bottom](../Images/Whisker%20Sicket%20V2%20-%20Bottom.png)

- Increase the sockets by 0.25mm to try and account for print tolerances
  - Done for _Whisker hole_
    - Now hold 3mm diameter rods fine
  - Done for _Magnet hole_
    - Can hold a 5x1 magnet with a drop of super glue

- TODO: _MAYBE_ make it slightly tighter for a press-fit option

#### V2.1

- Made it 1mm shorter on top

### [V3](STL/Whisker%20Socket/Whisker%20Socket%20V3.stl)

- Increase the outer lip rings radius from 5mm to 6mm
  - Re-centered it up the socket
- Increase the height from 9mm to 13mm to better suit V4 of the base
  - Increased the height of the socket "stopper" so that the whisker doesn't sit too far in because of the changes
    - Insertable whisker length has changed from 3mm to 5mm
- Increase the top chamfer from 1mm to 1.5mm
- Changed the Magnet Hole from a radius of 2.65m to 2.6mm for better printer tolerances for press fit for a 5x1mm magnet

### [V3.1](STL/Whisker%20Socket/Whisker%20Socket%20V3_1.stl)

- Corrected Height of the bearing due to error in making it 13mm tall instead of 12mm

## Casting Jig

### V1

- Create initial Design

### V2

- Removed Small wings as they made it hard to remove the whisker

## Whisker Silicon Bearing Mould

### Single Mould

#### [V1](STL/Whisker%20Silicon%20Bearing%20Mold/Whisker%20Silicon%20Bearing%20Mould%20V1.stl)

![Whisker Silicon Bearing Mold V1](../Images/Whisker%20Silicon%20Bearing%20Mold%20V1.png)

- Modified version of V3 to form the mold for the Silicon Bearing to test the various silicones

#### [V2](STL/Whisker%20Silicon%20Bearing%20Mold/Whisker%20Silicon%20Bearing%20Mould%20V2.stl)

- Added the socket to the mold so that bearing is moulded to fit with the socket installed

### 2-Part Mould

#### Top Plate

##### [V1](STL/Whisker%20Silicon%20Bearing%20Mould/2%20Part/Whisker%20Silicon%20Bearing%20Mould%20V1%20-%20Top%20Plate.stl)

- Top plate for pairing with a bottom plate for the bearing mould

##### [V2](STL/Whisker%20Silicon%20Bearing%20Mould/2%20Part/Whisker%20Silicon%20Bearing%20Mould%20V2%20-%20Top%20Plate.stl)

- Made thicker so that the split is better positioned
  
#### Bottom Plate

##### [V1](STL/Whisker%20Silicon%20Bearing%20Mould/2%20Part/Whisker%20Silicon%20Bearing%20Mould%20V1%20-%20Bottom%20Plate.stl)

- Bottom Plate for pairing with a top plate

##### [V2](STL/Whisker%20Silicon%20Bearing%20Mould/2%20Part/Whisker%20Silicon%20Bearing%20Mould%20V2%20-%20Bottom%20Plate.stl)

- Added the socket to the mold so that bearing is moulded to fit with the socket installed

##### [V3](STL/Whisker%20Silicon%20Bearing%20Mould/2%20Part/Whisker%20Silicon%20Bearing%20Mould%20V3%20-%20Bottom%20Plate.stl)

- Made shorter so that the split is better positioned
