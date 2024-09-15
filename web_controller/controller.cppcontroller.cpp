#include "controller.h"
#include "nipplejs.html.h"
#include "footer.html.h"
#include "header.html.h"



char* Controller::wifi_ssid = (char*)"RSA downstairs";
char* Controller::wifi_password = (char*)"mrvn1234";
uint8_t Controller::staticIP_tail{42};
IPAddress Controller::gateway{192, 168, 1, 1};
IPAddress Controller::subnet{255, 255, 255, 0};
IPAddress Controller::dns{8, 8, 8, 8};
void(*Controller::callback_connect)(uint) = nullptr;
void(*Controller::callback_disconnect)(uint) = nullptr;
void(*Controller::callback_joystick)(int8_t, int8_t) = nullptr;
void(*Controller::callback_a)(bool) = nullptr;
void(*Controller::callback_b)(bool) = nullptr;
void(*Controller::callback_x)(bool) = nullptr;
void(*Controller::callback_y)(bool) = nullptr;
void(*Controller::callback_fw)(bool) = nullptr;
void(*Controller::callback_bw)(bool) = nullptr;
void(*Controller::callback_l)(bool) = nullptr;
void(*Controller::callback_r)(bool) = nullptr;

Controller::Controller(uint8_t ip, String wsp) :
  ws_password(wsp),
  server(80),
  ws(String("/ws"))
{
  staticIP_tail = ip;
}

void Controller::init() {
  init_wifi();
  init_controller();
}

void Controller::init_wifi() {
  if (WiFi.config(IPAddress(192, 168, 1, staticIP_tail), gateway, subnet, dns, dns) == false) {
    while(true);
  }
  WiFi.begin(wifi_ssid, wifi_password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
}

void Controller::init_controller() {
  // Websocket
  ws.onEvent(this->onEvent);
  server.addHandler(&ws);

  // Interface
  String interface_url = "/";
  String html = generate_interface();
  // Serial.print("HTML:\n");
  // Serial.print(html);
  // Serial.print("\n");
  server.on((interface_url + ws_password).c_str(), HTTP_GET, [html](AsyncWebServerRequest *request){
    request->send(200, "text/html", html);
  });

  server.begin();
}

// Message structure:
// Byte 0: element id
// Byte 1: data type - (see ElementType)
void Controller::handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  if(len == 0) return; // No data received
  uint8_t id = data[0];

  if (id == 0) {
    if (callback_joystick != nullptr) {
      callback_joystick((int8_t)data[1], (int8_t)data[2]);
    }
  } else if (id == 1) {
    if (callback_a != nullptr) {
      callback_a(data[1]);
    }
  } else if (id == 2) {
    if (callback_b != nullptr) {
      callback_b(data[1]);
    }
  } else if (id == 3) {
    if (callback_x != nullptr) {
      callback_x(data[1]);
    }
  } else if (id == 4) {
    if (callback_y != nullptr) {
      callback_y(data[1]);
    }
  }else if (id == 5) {
    if (callback_fw != nullptr) {
      callback_fw(data[1]);
    }
  } else if (id == 6) {
      if (callback_bw != nullptr) {
        callback_bw(data[1]);
      }
    }
  else if (id == 7) {
      if (callback_l != nullptr) {
        callback_l(data[1]);
      }
    }
  else if (id == 8) {
      if (callback_r != nullptr) {
        callback_r(data[1]);
      }
  }

}

void Controller::onEvent(
  AsyncWebSocket *server, 
  AsyncWebSocketClient *client, 
  AwsEventType type, 
  void *arg, 
  uint8_t *data, 
  size_t len
) {
  switch (type) {
    case WS_EVT_CONNECT:
      // Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      if (callback_connect != nullptr) {
        callback_connect(client->id());
      }
      break;
    case WS_EVT_DISCONNECT:
      // Serial.printf("WebSocket client #%u disconnected\n", client->id());
      if (callback_connect != nullptr) {
        callback_disconnect(client->id());
      }
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void Controller::on_joystick(void(*callback_joystick)(int8_t, int8_t)) {
  this->callback_joystick = callback_joystick;
}
void Controller::on_a(void(*callback_a)(bool)) {
  this->callback_a = callback_a;
}
void Controller::on_b(void(*callback_b)(bool)) {
  this->callback_b = callback_b;
}
void Controller::on_x(void(*callback_x)(bool)) {
  this->callback_x = callback_x;
}
void Controller::on_y(void(*callback_y)(bool)) {
  this->callback_y = callback_y;
}
void Controller::on_fw(void(*callback_fw)(bool)) {
  this->callback_fw = callback_fw;
}void Controller::on_bw(void(*callback_bw)(bool)) {
  this->callback_bw = callback_bw;
}void Controller::on_l(void(*callback_l)(bool)) {
  this->callback_l = callback_l;
}void Controller::on_r(void(*callback_r)(bool)) {
  this->callback_r = callback_r;
}


String Controller::generate_interface() {
  String html = header;

  #include "nipplejs.html.h"
  html.concat(nipplejs);

  #include "footer.html.h"
  html.concat(footer);

  return html;
}
