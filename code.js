socket = new WebSocket("ws://192.168.1.16:81")
connected = false;


socket.onopen = (e) => {
    socket.send("connected yay!");
    connected = true;
};

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
        
      default:
        console.error("unknown type");
    }
}

function send(cas) {
    socket.send(document.getElementById("elever").value);    
}


