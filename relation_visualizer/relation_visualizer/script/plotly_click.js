// plotly_click.js

var plot = document.getElementById("{plot_id}");  // Note1
var info = document.getElementById("plotly-node-info"); // Note2
plot.on('plotly_click', function (data) { // Note3
    {
        console.log(data.points[0].customdata)
        // window.open( './data/aaa.txt' );
        window.open(data.points[0].customdata);
        var points = data.points;
        while (info.firstChild) info.removeChild(info.firstChild);
        for (p in points) {
            info.appendChild(DictToTable(points[p].customdata));  // Note4
        }
    }
})

function DictToTable(data) {
    var table = document.createElement("table");

    for (key in data) {
        var tr = document.createElement('tr');
        var th = document.createElement('th');
        var td = document.createElement('td');
        th.textContent = key;
        td.textContent = data[key];
        tr.appendChild(th);
        tr.appendChild(td);
        table.appendChild(tr);
    }

    return table;
}