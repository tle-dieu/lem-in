# Lem-in #

Lem-in is an algorithm project, the purpose is to find paths from start room to end room and to move ants by these paths with the least amount of steps.\
This is the third project of the algorithmic branch at 42.

## Subjects ##

* [English](/subjects/lem-in.en.pdf)
* [French](/subjects/lem-in.fr.pdf)

## Algorithm ##

The algorithm used is [Edmonds-Karp algorithm](https://en.wikipedia.org/wiki/Edmonds%E2%80%93Karp_algorithm), modified to be more suitable to this problem.

## Run ##

Run `make` command and an executable called `lem-in` should be created.\
You can run lem-in like this `./lem-in < <map>`

## Understanding output ##

`$> ./lem-in < maps/simple_map`

### ###

#### Map ####

```.
# simple_map    // Comment
3               // Number of ants
room1 1 1       // Room declaration: name and X-Y coordonates
room2 1 2
##start         // Next room will be start room
start 0 1
##end           // Next room will be end room
end 3 1
room3 2 2
start-room1     // Relations between rooms, room1 and start are linked
start-room2
room2-room3
room1-end
room3-end
```

#### Steps ####

```.
L1-room2 L2-room1           // Step 1: ant1 go to room2 and ant2 go to room1 (L<ant>-<room>)
L2-end L1-room3 L3-room1
L1-end L3-end
```

## Visualizer ##

This project have a visualizer.\
It was written in Javascript and Python

Run visualizer like this `./lem-in < <map> | python3 visu/visu.py`

## Authors ##

* Matthew Leroy - [lympe](https://github.com/lympe)
* Thomas le Dieu de Ville - [tle-dieu](https://github.com/tle-dieu)

## Notes ##

This code complies with the 42 school [norm](/subjects/norme_2_0_1.pdf)

&nbsp;

###### Done in 03/19 ######
