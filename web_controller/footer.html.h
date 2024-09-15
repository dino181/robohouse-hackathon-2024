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
          function fw_up() {
            websocket.send(new Int8Array([5, 1]));
          }
          function fw_down() {
            websocket.send(new Int8Array([5, 0]));
          }
          function bw_up() {
            websocket.send(new Int8Array([6, 1]));
          }
          function bw_down() {
            websocket.send(new Int8Array([6, 0]));
          }
          function l_up() {
            websocket.send(new Int8Array([7, 1]));
          }
          function l_down() {
            websocket.send(new Int8Array([7, 0]));
          }
          function r_up() {
            websocket.send(new Int8Array([8, 1]));
          } 
          function r_down() {
            websocket.send(new Int8Array([8, 0]));
          }

        
          document.addEventListener('keydown', function(event) {
              console.log(event.keyCode)
              if(event.keyCode == 87) {
                  fw_up()
              }
              else if(event.keyCode == 65) {
                l_up()
              }
              else if(event.keyCode == 83) {
                bw_up()
              }
              else if(event.keyCode == 68) {
                r_up()
              }
              else if(event.keyCode == 37) {
                a_up()
              }
              else if(event.keyCode == 39) {
                b_up()
              }
              else if(event.keyCode == 38) {
                x_up()
              }
              else if(event.keyCode == 40) {
                y_up()
              }
          });
          document.addEventListener('keyup', function(event) {
              console.log(event.keyCode)
              if(event.keyCode == 87) {
                  fw_down()
              }
              else if(event.keyCode == 65) {
                l_down()
              }
              else if(event.keyCode == 83) {
                bw_down()
              }
              else if(event.keyCode == 68) {
                r_down()
              }
              else if(event.keyCode == 37) {
                a_down()
              }
              else if(event.keyCode == 39) {
                b_down()
              }
              else if(event.keyCode == 38) {
                x_down()
              }
              else if(event.keyCode == 40) {
                y_down()
              }
          });

      </script>
    </body>
</html>
)rawliteral";
