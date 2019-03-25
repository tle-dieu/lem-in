var data = {
    "ants": 5,
    "error": "",
    "instructions": [
        {
            "ant": "L1",
            "room": "long0"
        },
        {
            "ant": "L2",
            "room": "short0"
        },
        {
            "ant": "L1",
            "room": "long0"
        },
        {
            "ant": "L2",
            "room": "short0"
        },
        {
            "ant": "L2",
            "room": "short1"
        },
        {
            "ant": "L1",
            "room": "long1"
        },
        {
            "ant": "L3",
            "room": "short0"
        },
        {
            "ant": "L2",
            "room": "end"
        },
        {
            "ant": "L3",
            "room": "short1"
        },
        {
            "ant": "L1",
            "room": "long2"
        },
        {
            "ant": "L4",
            "room": "short0"
        },
        {
            "ant": "L3",
            "room": "end"
        },
        {
            "ant": "L4",
            "room": "short1"
        },
        {
            "ant": "L1",
            "room": "long3"
        },
        {
            "ant": "L5",
            "room": "short0"
        },
        {
            "ant": "L4",
            "room": "end"
        },
        {
            "ant": "L5",
            "room": "short1"
        },
        {
            "ant": "L1",
            "room": "long4"
        },
        {
            "ant": "L5",
            "room": "end"
        },
        {
            "ant": "L1",
            "room": "end"
        }
    ],
    "pipes": [
        {
            "isfrom": "start",
            "to": "short0"
        },
        {
            "isfrom": "short0",
            "to": "short1"
        },
        {
            "isfrom": "long0",
            "to": "start"
        },
        {
            "isfrom": "long0",
            "to": "long1"
        },
        {
            "isfrom": "long1",
            "to": "long2"
        },
        {
            "isfrom": "long2",
            "to": "long3"
        },
        {
            "isfrom": "long3",
            "to": "long4"
        },
        {
            "isfrom": "long4",
            "to": "end"
        },
        "",
        {
            "isfrom": "short1",
            "to": "end"
        }
    ],
    "rooms": [
        {
            "coord": {
                "x": 23,
                "y": 3
            },
            "name": "start",
            "type": "##start"
        },
        {
            "coord": {
                "x": 16,
                "y": 7
            },
            "name": "end",
            "type": "##end"
        },
        {
            "coord": {
                "x": 16,
                "y": 3
            },
            "name": "short0",
            "type": ""
        },
        {
            "coord": {
                "x": 16,
                "y": 5
            },
            "name": "short1",
            "type": ""
        },
        {
            "coord": {
                "x": 16,
                "y": 18
            },
            "name": "long0",
            "type": ""
        },
        {
            "coord": {
                "x": 16,
                "y": 9
            },
            "name": "long1",
            "type": ""
        },
        {
            "coord": {
                "x": 5,
                "y": 6
            },
            "name": "long2",
            "type": ""
        },
        {
            "coord": {
                "x": 10,
                "y": 11
            },
            "name": "long3",
            "type": ""
        },
        {
            "coord": {
                "x": 4,
                "y": 8
            },
            "name": "long4",
            "type": ""
        }
    ]
}