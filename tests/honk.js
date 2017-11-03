var WebSocket = require('ws');
var ws = new WebSocket('ws://127.0.0.1:5001');

ws.on('open', () => {
    console.log('open');
    ws.send(JSON.stringify({
        "request": "gamesync",
        "login_token": "nothing"
    }));
});

ws.on('message', (msg) => {
    let data = JSON.parse(msg);

    if(data.event == "gamesync") {
        ws.send(JSON.stringify({
            "request": "honk"
        }));
    }

    if(data.event == "honk") {
        console.log("honk", data);
    }
});


ws.on('error', (msg) => {
    console.log('%s', msg);
});
