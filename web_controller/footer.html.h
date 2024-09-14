const char* footer = R"rawliteral(
            <script>
          var websocket;
          var gateway = `ws://${window.location.hostname}/ws`;

          function initWebSocket() {
          console.log('Trying to open a WebSocket connection...');
          websocket = new WebSocket(gateway);
          // websocket.onopen    = onOpen;
          // websocket.onclose   = onClose;
          // websocket.onmessage = onMessage; // <-- add this line
          }

          function initJoystick() {
            var joystick = nipplejs.create({
              zone: document.getElementById('joystick'),
              mode: 'static',
              position: { left: '25vw', top: '50vh' },
              color: 'red',
              size: 200
            });
            joystick.on('move', function(evt, data) {
              const angle = data.angle.radian;
              const dist = data.distance;
              const x = Math.round((Math.cos(angle) * dist) / 100 * 127);
              const y = Math.round((Math.sin(angle) * dist) / 100 * 127);
              console.log({ x, y });

              websocket.send(new Int8Array([0, x,y]));
            })
          }

          function onLoad(event) {
              initWebSocket();
              initJoystick();   
          }
          window.addEventListener('load', onLoad);
      
          function a_up() {
            websocket.send(new Int8Array([1, 1]));
          }
          function a_down() {
            websocket.send(new Int8Array([1, 0]));
          }
          function b_up() {
            websocket.send(new Int8Array([2, 1]));
          }
          function b_down() {
            websocket.send(new Int8Array([2, 0]));
          }
          function x_up() {
            websocket.send(new Int8Array([3, 1]));
          }
          function x_down() {
            websocket.send(new Int8Array([3, 0]));
          }
          function y_up() {
            websocket.send(new Int8Array([4, 1]));
          }
          function y_down() {
            websocket.send(new Int8Array([4, 0]));
          }
      </script>
    </body>
</html>
)rawliteral";
