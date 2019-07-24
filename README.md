# Lem-in #

## Subjects ##

* [English](subjects/lem-in.en.pdf)
* [French](subjects/lem-in.fr.pdf)

## Compiling ##

Run `make` command and an executable called `lem-in` should be created.

## Example ##

### ###

#### Without visualizer ####

`$> ./lem-in < maps/example`

```.
10
##start
start 0 1
a 1 0
b 1 1
c 1 2
d 2 0
e 2 1
f 2 2
##end
end 3 1
start-a
start-b
a-d
d-e
b-e
e-end
b-c
c-f
f-end

L1-b L2-a
L1-c L2-d L3-b L4-a
L1-f L2-e L3-c L4-d L5-b L6-a
L1-end L2-end L3-f L4-e L5-c L6-d L7-b L8-a
L3-end L4-end L5-f L6-e L7-c L8-d L9-b L10-a
L5-end L6-end L7-f L8-e L9-c L10-d
L7-end L8-end L9-f L10-e
L9-end L10-end
```

## Authors ##

* Matthew Leroy - [lympe](https://github.com/lympe)
* Thomas le Dieu de Ville - [tle-dieu](https://github.com/tle-dieu)

## Notes ##

This code complies with the 42 school [norm](https://github.com/Binary-Hackers/42_Subjects/blob/master/04_Norme/norme_2_0_1.pdf)

&nbsp;

###### Done in 03/19 ######