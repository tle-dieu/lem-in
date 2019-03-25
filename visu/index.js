var y = 0;
var x = 0;
var z = 0;
var time = 300;
var division = 0;
var images = [
    'https://media3.giphy.com/media/w5f56AhubQo8w/giphy.gif?cid=3640f6095c950588414b4c7045ab9236',
    'https://media2.giphy.com/media/nQFMUc3khOGLS/giphy.gif?cid=3640f6095c95057f494f4c6855f97ad0',
    'https://media1.giphy.com/media/nbJUuYFI6s0w0/giphy.gif?cid=3640f6095c95105f34713075599e792e',
    'https://media0.giphy.com/media/AwcmOV28QPnck/200.webp?cid=3640f6095c9510744d325a6b4d81a1df',
    'https://media3.giphy.com/media/lfXrsx8kerD1u/200.webp?cid=3640f6095c9510744d325a6b4d81a1df',
]
var start;
var end;
var playAction;
var arrived = 0;
var isPlay = false;
var nb_room = 0;
data.rooms.forEach((data) =>{
    nb_room++;
	if (data.coord.x > x)
		x = data.coord.x
	if (data.coord.y > y)
		y = data.coord.y;
});
division = 1;
while (nb_room > 100){
    nb_room = nb_room / 10
    division = division / 2;
}
data.pipes.forEach((item) =>{
    console.log("before")
    if (item){
        console.log("in")
        var canvas = document.getElementById("map-bg");
        var context = canvas.getContext("2d");
        context.beginPath();
        var i = 0;
        while ( data.rooms[i].name != item.isfrom || data.rooms[i].type == "deleted")
            i++;
        var from = data.rooms[i];
        i = 0;
        while (data.rooms[i].name != item.to || data.rooms[i].type == "deleted")
            i++;
        console.log(data.rooms[i])
        var to = data.rooms[i];
        context.strokeStyle = "#a98274";
        context.moveTo(canvas.width * to.coord.x / x, canvas.height * to.coord.y / y + 0.5);
        context.lineWidth = 2;
        context.lineTo(canvas.width * from.coord.x / x, canvas.height * from.coord.y / y + 0.5);
        context.stroke();
        context.closePath();
    }
})
data.rooms.forEach((item) =>{
    if (item.type != "deleted"){
        var div = document.createElement("DIV");
        var span = document.createElement("SPAN");
        var text = document.createTextNode(item.name);
        var map = document.getElementById("map");
        if (item.type == "##start")
            div.style.backgroundColor = "#4caf50"
        else if (item.type == "##end")
            div.style.backgroundColor = "#ff3333"
        item.y = (window.innerHeight  * 0.7) * item.coord.y / y / (window.innerHeight  * 0.7)* 100;
        item.x = (window.innerWidth  * 0.7) * item.coord.x / x / (window.innerWidth  * 0.7)* 100;
        div.id = "room" + item.name;
        div.className = "room";
        span.id = "roomTitle" + item.name
        span.appendChild(text);
        div.appendChild(span);
        map.appendChild(div);
        div.style.width = 60 * division + "px"
        div.style.height = 60 * division + "px"
        div.style.left = item.x.toString() + "%";
        div.style.top = item.y.toString() + "%";
        if (item.type == "##start")
            start = item;
        if (item.type == "##end")
            end = item;
    }
})

var nb_ant = 0;
while (data.ants != nb_ant)
{
	var ant = document.createElement("IMG");
	var id = nb_ant + 1;
    ant.id = "antL" + id;
    ant.className = "ant";
    ant.style.width = 50 * division + "px"
	ant.style.left = start.x.toString() + "%";
	ant.style.top = start.y.toString() + "%";
    ant.src = "data:image/jpeg;base64,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";
    document.getElementById("map").appendChild(ant);
	nb_ant++;
}
var isHide = 1
function endAnimation(m)
{
    if (m < 40){
        var img = document.createElement("IMG");
        img.className = "victory";
        img.style.transform = 'translateY(-50%) translateX(-50%) rotate(' + (Math.random() * (50 - -50) + -50 )+ 'deg)';
        img.style.left = Math.random() * window.innerWidth + "px";
        img.style.top =  Math.random() * window.innerHeight + "px";
        img.src = images[Math.floor(Math.random() * 5)];
        document.body.appendChild(img);
        m++;
        setTimeout(function(){ endAnimation(m)} ,200)
    }
}
function fall()
{
    document.getElementById("title").className = "title title-fall"
    setTimeout(function(){ document.getElementById("title").className = "null"} ,4000);
}
function finish()
{
    let m = 0;
    var bg = document.createElement("DIV");
    var title = document.createElement("H1");
    bg.className = "victory-bg";
    title.className = "title";
    title.id = "title";
    title.textContent = "BR@VO!";
    document.body.appendChild(bg);
    document.body.appendChild(title);
    title.animate([
        { transform: 'translateY(-30%) translateX(-80%) scale(0) rotate(-1080deg)' },
        { transform: 'translateY(-50%) translateX(-50%) scale(1) rotate(15deg)' },
      ], {
        duration: 2000
      });
      setTimeout(function(){ endAnimation(m)} ,200)
      setTimeout(function(){ fall()} ,4000)
}
function isArrived(item)
{
    arrived++;
    if (arrived == data.ants){
        setTimeout(function(){ finish()} ,800);}
}
function animeAnt(ant)
{
    ant.animate([
        { transform: 'translateY(-50%) translateX(-50%) rotate(-20deg)' },
        { transform: 'translateY(-50%) translateX(-50%) rotate(20deg)' },
        { transform: 'translateY(-50%) translateX(-50%) rotate(-20deg)' },
        { transform: 'translateY(-50%) translateX(-50%) rotate(20deg)' },
        { transform: 'translateY(-50%) translateX(-50%) rotate(-20deg)' },
        { transform: 'translateY(-50%) translateX(-50%) rotate(20deg)' }
      ], {
        duration: 600
      });
}
function hide(item)
{
    if (!isHide){
        isHide = 1;
        data.rooms.forEach((item) =>{
            var room = document.getElementById("roomTitle" + item.name);
            room.style.display = "block"
        })
    }
    else{
        isHide = 0;
        data.rooms.forEach((item) =>{
            var room = document.getElementById("roomTitle" + item.name);
            room.style.display = "none"
        })
    }
}
function pause(){
	clearTimeout(playAction);
}
function goahead(){
	if (z < data.instructions.length){
        var instru = data.instructions[z];
	    var ant = document.getElementById("ant" + instru.ant);
        var item = document.getElementById("room" + instru.room);
		ant.style.left = item.style.left;
        ant.style.top = item.style.top;
        animeAnt(ant);
        if (instru.room == end.name)
            isArrived(item);
	z++;
	}
}
function getNextInstructions(instru){
	var ant = document.getElementById("ant" + instru.ant);
    var item = document.getElementById("room" + instru.room);
	ant.style.left = item.style.left;
    ant.style.top = item.style.top;
    animeAnt(ant);
	z++;
    if (instru.room == end.name)
    isArrived(item);
	if (z < data.instructions.length)
		playAction = setTimeout(function(){ getNextInstructions(data.instructions[z])} ,time);
}
function play(){
    if (isPlay == false){
        playAction = setTimeout(function(){ isPlay = true; getNextInstructions(data.instructions[z])} , time);
    }
}