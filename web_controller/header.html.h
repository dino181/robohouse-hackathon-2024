const char* header = R"rawliteral(
<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <title>RSA Flipperbot controller</title>
        <meta name="viewport" content="user-scalable=no, initial-scale=1, maximum-scale=1, minimum-scale=1, width=device-width, height=device-height, target-densitydpi=device-dpi" />
        <style>
        html, body {
            position: absolute;
            top: 0;
            left: 0;
            right: 0;
            bottom: 0;
            padding: 0;
            margin: 0;
        }

        #joystick {
            position: absolute;
            left: 0;
            top: 0;
            height: 100vh;
            width: 50vw;
            background: rgba(0, 0, 0, 0.1);
        }

        #button-container {
            margin: auto;
            position: absolute;
            right: 0;
            top: 0;
            height: 100vh;
            width: 50vw;
            background: rgba(0, 0, 0, 0);
        }

        .button {
            position: absolute;
            width: 120px;
            height: 120px;
            background: #ecabab;
            border-radius: 60px;
            border-width: 0px;
            margin-left: auto;
            margin-right: auto;
        }

        .abxy {
          margin-left: auto;
          margin-right: auto;
        }

        #button_a {
          top: 0px;
          left: 100px;
        }
        #button_b {
          top: 100px;
          left: 0px;
        }
        #button_x {
          top: 100px;
          left: 200px;
        }
        #button_y {
          top: 200px;
          left: 100px;
        }
        </style>
    </head>
    <body>
      <div id="controller">
        <div id="joystick"></div>
        <div id="button-container">
          <div id="abxy">
            <button id="button_a" class="button" onmousedown="a_up()" onmouseup="a_down()" ontouchstart="a_up()" ontouchend="a_down()">A
            </button>
            <button id="button_b" class="button" onmousedown="b_up()" onmouseup="b_down()" ontouchstart="b_up()" ontouchend="b_down()">B
            </button>
            <button id="button_x" class="button" onmousedown="x_up()" onmouseup="x_down()" ontouchstart="x_up()" ontouchend="x_down()">X
            </button>
            <button id="button_y" class="button" onmousedown="y_up()" onmouseup="y_down()" ontouchstart="y_up()" ontouchend="y_down()">Y
            </button>
          </div>
        </div>
      </div>
)rawliteral";
