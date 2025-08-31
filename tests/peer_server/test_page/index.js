
let webSocket = null;

function onConnectAndSignIn(signIn) {
  webSocket = new WebSocket(config.URL_SERVER_WSS);

  webSocket.onopen = (event => {
    console.log("onopen %o", event);
    if (signIn) {
      onSignIn();
    }
  });

  webSocket.onmessage = (event => {
    console.log("onmessage %o", event);
    showMessage(JSON.stringify(event.data));

  });

  webSocket.onclose = (event => {
    console.log("onclose %o", event);
  });

}

function onSignOut() {
  webSocket.close();
}

function messageCallback(message) {
  console.debug(`messageCallback ${message}`);
}

function GetPermission() {
  location.href = config.URL_SERVER_HTTPS;
}

function onLoadHandler() {
  initUi();
}

function invalidMessage() {
  let msg = {
    someData: 'someData'
  };
  webSocket.send(JSON.stringify(msg));
}

function onSignIn() {
  webSocket.send(
    JSON.stringify({
      cmd: 1,
      data: {
        id: document.querySelector("#login").value
      }
    })
  );
}

function onSignOut() {
  webSocket.send(
    JSON.stringify({
      cmd: 2,
      data: {
        id: 123
      }
    })
  );
}

function onSendMessage() {
  webSocket.send(
    JSON.stringify({
      cmd: 3,
      data: {
        to: document.querySelector("#recipient").value,
        msg: document.querySelector("#message").value
      }
    })
  );
}


