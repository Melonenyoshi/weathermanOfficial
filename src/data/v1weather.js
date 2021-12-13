document.addEventListener('DOMContentLoaded', () => {
    document.getElementById('temperature').innerHTML = "<h2 style='margin-left: 10px'> No Data </h2>";
    document.getElementById('humidity').innerHTML = "<h2 style='margin-left: 10px'> No Data </h2>";
    document.getElementById('pressure').innerHTML = "<h2 style='margin-left: 10px'> No Data </h2>";
    document.getElementById('altitude').innerHTML = "<h2 style='margin-left: 10px'> No Data </h2>";
    const ws = new WebSocket(`ws://${window.location.hostname}/ws`);
    ws.onopen = function () { console.log("WebSocket is open now."); };
    ws.onclose = function () { console.log("WebSocket is closed now."); };
    ws.onerror = function (event) { console.log("WebSocket has run into error \"" + event.target + "\"."); };
    ws.onmessage = function (event) {
        console.log("WebSocket has received message \"" + event.data + "\".");
        switch (event.data.charAt(0)) {
            case 't':
                document.getElementById('temperature').innerHTML = `<h2 style='margin-left: 10px'> ${event.data.slice(1)} °C</h2>`;
                break;
            case 'h':
                document.getElementById('humidity').innerHTML = `<h2 style='margin-left: 10px'> ${event.data.slice(1)} %</h2>`;
                break;
            case 'p':
                document.getElementById('pressure').innerHTML = `<h2 style='margin-left: 10px'> ${event.data.slice(1)} hPa</h2>`;
                break;
            case 'a':
                document.getElementById('altitude').innerHTML = `<h2 style='margin-left: 10px'> ${event.data.slice(1)} m</h2>`;
                break;
        }
    };
});
//# sourceMappingURL=v1weather.js.map