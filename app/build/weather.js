let pressure;
let humidity;
let altitude;
let feelslike;
let temperature;
let lightlevel;
document.addEventListener('DOMContentLoaded', () => {
    document.getElementById('temperature').innerHTML = "<h2 class='temperature'>25<span class='comma'>.4</span><span class='align-top topcelsius'>°</span></h2>";
    document.getElementById('humidity').innerHTML = "<h2 class='subdata'>50<span class='align-top subunit'> %</span></h2>";
    document.getElementById('pressure').innerHTML = "<h2 class='subdata'>1011<span class='align-top subunit'> mbar</span></h2>";
    document.getElementById('altitude').innerHTML = "<h2 class='subdata'>276<span class='align-top subunit'> m</span></h2>";
    document.getElementById('lightlevel').innerHTML = "<h2 class='subdata'>51<span class='align-top subunit'> <lx></lx></span></h2>";
    document.getElementById('feelslike').innerHTML = "<div class=\"col-sm d-flex justify-content-center\"><h2 class='subdata'>29<span class='align-top subunit'> °</span></h2></div>";
    const ws = new WebSocket(`ws://172.17.214.233/ws`);
    ws.onopen = function () { console.log("WebSocket is open now."); };
    ws.onclose = function () { console.log("WebSocket is closed now."); };
    ws.onerror = function (event) { console.log("WebSocket has run into error \"" + event.target + "\"."); };
    ws.onmessage = function (event) {
        console.log("WebSocket has received message \"" + event.data + "\".");
        switch (event.data.charAt(0)) {
            case 't':
                document.getElementById('temperature').innerHTML = `<h2 class="temperature">${event.data.slice(1, -3)}<span class='comma'>${event.data.slice(event.data.length - 3, -1)}</span><span class='align-top topcelsius'>°</span></h2>`;
                temperature = event.data.slice(1, -2);
                break;
            case 'h':
                humidity = event.data.slice(1, -3);
                break;
            case 'p':
                pressure = event.data.slice(1, -3);
                break;
            case 'a':
                altitude = event.data.slice(1, -3);
                break;
            case 'f':
                feelslike = event.data.slice(1, -3);
                break;
            case 'l':
                lightlevel = event.data.slice(1, -3);
                break;
        }
        if (temperature >= 26 && humidity >= 40) {
            document.getElementById('headers').innerHTML = "<div class=\"col-sm d-flex justify-content-center\"><h2 class=\"subheader\">PRESSURE</h2></div><div class=\"col-sm d-flex justify-content-center\"><h2 class=\"subheader\">FEELS LIKE</h2></div><div class=\"col-sm d-flex justify-content-center\"><h2 class=\"subheader\">HUMIDITY</h2></div><div class=\"col-sm d-flex justify-content-center\"><h2 class=\"subheader\">ALTITUDE</h2></div><div class=\"col-sm d-flex justify-content-center\"><h2 class=\"subheader\">LIGHT LEVEL</h2></div>";
            document.getElementById('lowerdata').innerHTML = `<div class=\"col-sm d-flex justify-content-center\"><div id=\"pressure\"></div><h2 class=\"subdata\">${pressure}<span class='align-top subunit'> mbar</span></h2></div><div class=\"col-sm d-flex justify-content-center\"><div id=\"feelslike\"></div><h2 class=\"subdata\">${feelslike}<span class='align-top subunit'> °</span></div></div><div class=\"col-sm d-flex justify-content-center\"><div id=\"humidity\"></div><h2 class=\"subdata\">${humidity}<span class='align-top subunit'> %</span></h2></div><div class=\"col-sm d-flex justify-content-center\"><h2 class=\"subdata\">${altitude}<span class='align-top subunit'> m</span></h2><div id=\"altitude\"></div></div><div class=\"col-sm d-flex justify-content-center\"><h2 class=\"subdata\">${lightlevel}<span class='align-top subunit'> lx</span></h2><div id=\"altitude\"></div></div>`;
        }
        else {
            document.getElementById('headers').innerHTML = "<div class=\"col-sm d-flex justify-content-center\"><h2 class=\"subheader\">PRESSURE</h2></div><div class=\"col-sm d-flex justify-content-center\"><h2 class=\"subheader\">HUMIDITY</h2></div><div class=\"col-sm d-flex justify-content-center\"><h2 class=\"subheader\">ALTITUDE</h2></div><div class=\"col-sm d-flex justify-content-center\"><h2 class=\"subheader\">LIGHT LEVEL</h2></div>";
            document.getElementById('lowerdata').innerHTML = `<div class=\"col-sm d-flex justify-content-center\"><div id=\"pressure\"></div><h2 class=\"subdata\">${pressure}<span class='align-top subunit'> mbar</span></h2></div><div class=\"col-sm d-flex justify-content-center\"><div id=\"humidity\"></div><h2 class=\"subdata\">${humidity}<span class='align-top subunit'> %</span></h2></div><div class=\"col-sm d-flex justify-content-center\"><h2 class=\"subdata\">${altitude}<span class='align-top subunit'> m</span></h2><div id=\"altitude\"></div></div><div class=\"col-sm d-flex justify-content-center\"><h2 class=\"subdata\">${lightlevel}<span class='align-top subunit'> lx</span></h2><div id=\"altitude\"></div></div>`;
        }
    };
});
//# sourceMappingURL=weather.js.map