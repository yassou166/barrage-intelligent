//creer un connection
console.log("hello world")
console.log(window.location.hostname);
let ip="192.168.1.16";
socket = new WebSocket("ws://"+ip+":81")
connected = false;


//si la connection est etabli
socket.onopen = (e) => {

    console.log("connected yay!");
    connected = true;
};

//si il ya un problem
socket.onclose = function (e) {
    console.log("not connected");
    connected = false;
  };

socket.onmessage = function(recu){
    let parts = recu.data.split('_');

    switch (parts[0].toLowerCase()) {
      case 't':
        var temp = parts[1];
        console.log('Temperature:', temp);
        document.getElementById("temperature").innerHTML = temp + " C"
        break;
    
      case 'w':
        var waterLevel = parts[1];
        console.log('Water Level:', waterLevel);
        document.getElementById("water").innerHTML = waterLevel + " %"
        break;
        
      case 'q':
        var waterLevel = parts[1];
        console.log('Water quality:', waterLevel);
        document.getElementById("qualite").innerHTML = waterLevel + " %"
        break; 
        
      default:
        console.error("unknown type");
    }
}

function send(cas) {
    socket.send(document.getElementById("elever").value);    
}


