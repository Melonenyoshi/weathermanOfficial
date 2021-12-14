let dataset = "Temperature";
let myChart;
document.addEventListener('DOMContentLoaded', (event) => {
    document.getElementById('temperature').addEventListener("click", () => {
        dataset = 'Temperature';
    });
    document.getElementById('humidity').addEventListener("click", () => {
        dataset = 'Humidity';
    });
    document.getElementById('altitude').addEventListener("click", () => {
        dataset = 'Altitude';
    });
    document.getElementById('pressure').addEventListener("click", () => {
        dataset = 'Pressure';
    });
    document.getElementById('lightlevel').addEventListener("click", () => {
        dataset = 'Light Level';
    });
    init();
});
function init() {
    const ws = new WebSocket(`ws://${window.location.hostname}/ws`);
    const canvas = document.getElementById("myChart");
    const ctx = canvas.getContext("2d");
    myChart = new Chart(ctx, {
        type: 'line',
        data: {
            labels: ['', '', '', '', '', '', '', '', '', ''],
            datasets: [{
                    label: dataset,
                    data: [1, 2, 1, 3, 4, 5, 4, 4, 3, 2],
                    backgroundColor: 'lightblue',
                    borderColor: 'rgb(80, 160, 190)',
                    borderWidth: 5,
                    fill: true,
                    tension: 0.5
                }]
        },
        options: {
            plugins: {
                legend: {
                    display: true,
                    labels: {
                        color: 'white'
                    }
                }
            },
            scales: {
                y: {
                    ticks: {
                        color: 'white'
                    },
                    grid: {
                        color: 'lightblue'
                    }
                },
                x: {
                    ticks: {
                        color: 'white'
                    },
                    grid: {
                        color: 'lightblue'
                    }
                }
            }
        }
    });
    ws.onopen = function () { console.log("WebSocket is open now."); };
    ws.onclose = function () { console.log("WebSocket is closed now."); };
    ws.onerror = function (event) { console.log("WebSocket has run into error " + event.target + "."); };
    ws.onmessage = function (event) {
        console.log("WebSocket has received message " + event.data + ".");
        console.log("End of JSON");
        if(event.data[0] == '[')
        {
            let objJson1 = JSON.parse(event.data);
        
        let arrayofData = [];
        for (let i = 0; i < 10; i++) {
            switch (dataset) {
                case 'Temperature':
                    arrayofData.push(parseFloat(objJson1[i].Temperature));
                    break;
                case 'Humidity':
                    arrayofData.push(parseFloat(objJson1[i].Humidity));
                    break;
                case 'Altitude':
                    arrayofData.push(parseFloat(objJson1[i].Altitude));
                    break;
                case 'Pressure':
                    arrayofData.push(parseFloat(objJson1[i].Pressure));
                    break;
                case 'Light Level':
                    arrayofData.push(parseFloat(objJson1[i].LightLevel));
                    break;
            }
        }
        myChart.data.datasets[0].data = arrayofData;
        myChart.data.datasets[0].label = dataset;
        myChart.update();
        }
        
    };
}
//# sourceMappingURL=charts.js.map