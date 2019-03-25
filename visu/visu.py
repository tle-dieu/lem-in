import sys
import json
import subprocess

i = 0
rooms = []
pipes = []
instructions = []
specialRoom = ""
ants = 0
error = ""
stop = ""
class datas(object):
    def __init__(self, ants, rooms, pipes, instructions, error):
        self.ants = ants
        self.rooms = rooms
        self.pipes = pipes
        self.instructions = instructions
        self.error = error
    def toJSON(self):
        return json.dumps(self, default=lambda o: o.__dict__, 
            sort_keys=True, indent=4)

class coordinate(object):
    def __init__(self, x, y):
        self.x = x
        self.y = y

class Room(object):
    def __init__(self, name, kind, coord):
        self.name = name
        self.type = kind
        self.coord = coord

class Pipe(object):
    def __init__(self, isfrom, to):
        self.isfrom = isfrom
        self.to = to

class Instru(object):
    def __init__(self, ant, room):
        self.ant = ant
        self.room = room

def getInstru(line):
    error = ""
    line = line.strip(" \n")
    tab = line.split(' ')
    instructions = []   
    for elem in tab:
        newInstru = elem.split('-')
        if (len(newInstru) == 2):
            instructions.append(Instru(newInstru[0].strip('\n'), newInstru[1].strip('\n')))
        else:
            error = "INSTRUCTIONS WITH BAD FORMAT"

    return instructions, error
def checkRoom(name, kind, coord):
    for item in rooms:
        if item.name == name:
            item.type = "deleted"
        if item.coord == coord:
            item.type = "deleted"
        if item.type == kind:
            item.type = ""
    

def getRoom(line, specialRoom):
    error = ""
    tab = line.split()
    newRoom = ""
    coord = ""
    if len(tab) == 3:
        name = tab[0].strip('\n')
        try:
            x = int(tab[1])
        except ValueError:
            error = "BAD COORD"
        try:
            y = int(tab[2])
        except ValueError:
            error = "BAD COORD"
        coord = coordinate(x, y)
        kind = specialRoom.strip('\n')
        checkRoom(name, kind, coord)
        newRoom = Room(name, kind, coord)
    else:
        error = "BAD ROOM"
    return newRoom, error

def checkPipe(isfrom, to):
    check = 0
    for item in rooms:
        if item.type != "deleted":
            if item.name == isfrom:
                check += 1
            if item.name == to:
                check += 1
    return check == 2

def getPipe(line):
    error = ""
    newPipe = ""
    tab = line.split('-')
    if len(tab) == 2:
        if checkPipe(tab[0].strip('\n'), tab[1].strip('\n')):
            newPipe = Pipe(tab[0].strip('\n'), tab[1].strip('\n'))
    else:
        error = "BAD PIPE"

    return newPipe, error
    

for line in sys.stdin:
    if line.startswith("ERROR") or line.startswith("ERROR\n"):
        stop = "ERROR"
    if not line.startswith('L') and not line.startswith('#') and (line.count('-') > 1 or line.count('-') and line.count(' ')):
        print("error")
        break
    if i == 0:
        i += 1
        try:
            ants = int(line)
        except ValueError:
            error = "Issue with ant"
    elif line.startswith("##"):
        specialRoom = line
    elif line.startswith("#"):
        pass
    elif line.startswith('L'):
        elems, error = getInstru(line)
        if error:
            print("error :" + error)
            break
        for elem in elems:
                instructions.append(elem)
    elif '-' in line:
        pipe, error = getPipe(line)
        if error:
            print("error :" + error)
            break
        pipes.append(pipe)
    elif line.startswith("\n"):
        pass
    elif len(pipes):
        print("error :" + error)
        break
    else:
        room, error = getRoom(line, specialRoom)
        if error:
            print("error room:" + error)
            break 
        rooms.append(room)
        specialRoom = ""
if len(stop):
    print(stop)
else:
    store = datas(ants, rooms, pipes, instructions, error)
    f = open("./visu/data.js","w+")
    f.write("var data = ")
    f.write(store.toJSON())
    subprocess.run(["open", "./visu/visu.html"])
