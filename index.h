const char MAIN_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
  </head>
<style>
.card{
  width: 400px;
  background: #0287c3;
  padding: 10px 15px;
  box-sizing: border-box;
  color: #FFF;
  margin:20px 0;
  box-shadow: 0px 2px 18px -4px rgba(0,0,0,0.75);
}
@media (max-width: 480px) {
.card {
  width: 270px;
}

}
.card>p{
  margin: 0.3em;
  font-size: large;
}

.card>h3{
  width: 100%%;
  text-align: center;
}

header{
  overflow: hidden;
  width: 100%%;
  margin: 0 auto;
  position: fixed;
  top: 0;
  left: 0;
  background-color: #0276ab;
  color: #FFFFFF;
  z-index: 100;
}

nav{
  display: flex;
  flex-direction: row;
  overflow: hidden;
  justify-content: space-between;
  height: 4em;
  align-items: center;
  font-size: 1rem;
}

body{
  padding: 100px 0 0 0;
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
}

nav>div,p,button{
  padding: 0 2em;
}

#title{
  flex: 1;
  font-size: 18px;
}

#settings{
  background: none;
  color: inherit;
  border: none;
  padding: 0;
  font: inherit;
  cursor: pointer;
  outline: inherit;
}

.switch {
position: relative;
display: inline-block;
width: 30px;
height: 17px;
margin-left: 5px;
}

.switch input {
opacity: 0;
width: 0;
height: 0;
}

.slider {
position: absolute;
cursor: pointer;
top: 0;
left: 0;
right: 0;
bottom: 0;
background-color: #ccc;
-webkit-transition: .4s;
transition: .4s;
}

.slider:before {
position: absolute;
content: "";
height: 13px;
width: 13px;
left: 2px;
bottom: 2px;
background-color: white;
-webkit-transition: .4s;
transition: .4s;
}

input:checked + .slider {
background-color: #2196F3;
}

input:focus + .slider {
box-shadow: 0 0 1px #2196F3;
}

input:checked + .slider:before {
-webkit-transform: translateX(13px);
-ms-transform: translateX(13px);
transform: translateX(13px);
}

.slider.round {
border-radius: 17px;
}

.slider.round:before {
border-radius: 50%%;
}

#frequency{
  width: 50px;
}

#setHumidity{
  width: 100%%;
  margin: 10px 20px;
}
#setHumidity>input{
  width:60%%;
  margin-right: 20px;
}
#setHumidity>output{
  justify-content: center;
}

#minHumidityValue{
  width: fit-content;
}

.awayModeButton {
  display: inline;
  padding: 0;
}

</style>

<header>
  <nav>
    <p id="title">SMART POT</p>
  </nav>
</header>
<body>
  <div class="card">
  %AWAYMODEPLACEHOLDER%
  <button class="awayModeButton" onClick="setAwayModeInterval()">Submit</button>
  </div>
  
  <div class="card">
    <h3>Device status: <span id="deviceStatus">ON</span></h3><br>
      <p>Pump: <span id="pump">%PUMPPLACEHOLDER%</span></p><br>
      <p>Humidity: <span id="humidity"></span></p><br>
      <p>Light level: <span id="lightLvl"></span></p><br>
      <p>Water level: <span id="distance"></span></p><br>
  </div>

  <div class="card">
    <p>Set humidity level: </p>
    %SETHUMIDITYPLACEHOLDER%
  </div>

<script>
function togglePump(element) {
  var xhr = new XMLHttpRequest();
  if(element.checked){ xhr.open("GET", "/pump?state=1", true); }
  else { xhr.open("GET", "/pump?state=0", true); }
  xhr.send();
}

function toggleAwayMode(element) {
  var xhr = new XMLHttpRequest();
  if(element.checked){ xhr.open("GET", "/awayMode?state=1", true); }
  else { xhr.open("GET", "/awayMode?state=0", true); }
  xhr.send();
}

function setAwayModeInterval() {
  var xhr = new XMLHttpRequest();
  const element = document.getElementById("awayModeValue");
  if(element.value){ xhr.open("GET", "/awayModeInterval?value="+element.value); 
    xhr.send();
  }
}

function setMinHumidity() {
  var xhr = new XMLHttpRequest();
  const element = document.getElementById("minHumidityValue");
  if(element.value){ xhr.open("GET", "/setHumidity?value="+element.value); 
    xhr.send();
  }
}

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("lightLvl").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/lightLvl", true);
  xhttp.send();
}, 2000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidity").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/humidity", true);
  xhttp.send();
}, 2000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("distance").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/distance", true);
  xhttp.send();
}, 2000 ) ;
</script>
</body>
</html>
)rawliteral"; 
