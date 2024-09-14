#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

static const char* RED = "#ff0000";
static const char* GREEN = "#00ff00";
static const char* BLUE = "#0000ff";

// enum class ElementType : uint8_t {
//   Joystick=1,
//   Button=2,
// };


// struct Element {
//   ElementType type; // Not strictly necessary anymore

//   Element(ElementType c_type) : type(c_type) {}

//   virtual void handleMessage(uint8_t *data, size_t len) = 0;
//   virtual String toHtml(uint8_t id) = 0;
// };

// struct Joystick : public Element {
//   private:
//     uint8_t x, y;
//     uint8_t size;
//     const char* color;
//     void(*callback)(int8_t, int8_t);

//   public:
//     /*
//     x: horizontal coordinate of center of joystick, 0 to 100, origin on the left
//     y: vertical coordinate of center of joystick, 0 to 100, origin at the top
//     size: diameter, 200 is a good starting point
//     color: hex string, e.g. "#abcdef", can use constants RED, BLUE, GREEN...
//     callback: function called every time the joystick moves, takes two parameters, x and y position (-127 to 128), right and up is positive
//     */
//     Joystick(uint8_t x, uint8_t y, uint8_t size, const char* color, void(*c_callback)(int8_t, int8_t)) :
//       Element{ElementType::Joystick},
//       callback(c_callback),
//       x{x}, y{y},
//       size{size},
//       color{color}
//     { }

//     void handleMessage(uint8_t *data, size_t len) override {
//       if(len < 4) return; // Check there's enough data
//       if(data[1] != (uint8_t) this->type) return; // Check that the element type matches
//       if(*callback != nullptr) {
//         (*callback)(*((int8_t*) &data[2]), *((int8_t*) &data[3])); // Callback to user function
//       }
//     }

//     String toHtml(uint8_t id) override {
//       // TODO Implement this
//       char buffer[200];
//       snprintf(
//         buffer,
//         200,
//         "<div class=joystick id=%u data-x=\"%uvw\" data-y=\"%uvh\" data-size=\"%u\" data-color=\"%s\"></div>",
//         id,
//         x, y, size,
//         color
//       );
//       return String(buffer);
//     }
// };
// struct Button : public Element {
//   private:
//     uint8_t x, y;
//     uint8_t width, height;
//     const char* color;
//     const char* label;
//     void(*callback)(bool);
    

//   public:
//     /*
//     label: Text shown on button
//     x: horizontal coordinate of top left corner of button, 0 to 100, origin left
//     y: vertical coordinate of top left corner of button, 0 to 100, origin top
//     width: width of button, 0 to 100
//     height: height of button, 0 to 100
//     color: hex string, e.g. "#abcdef", can use constants RED, BLUE, GREEN...
//     calback: function called every time the button state changes, takes a boolen indicating whether the button is pressed
//     */
//     Button(const char* label, uint8_t x, uint8_t y, uint8_t width, uint8_t height, const char* color, void(*c_callback)(bool)) :
//       Element{ElementType::Button},
//       callback(c_callback),
//       x{x}, y{y},
//       width{width}, height{height},
//       color{color},
//       label{label}
//     { }

//     void handleMessage(uint8_t *data, size_t len) override {
//       if(len < 3) return; // Check there's enough data
//       if(data[1] != (uint8_t) this->type) return; // Check that the element type matches
      
//       if(*callback != nullptr) {
//         (*callback)(data[2]);  // Callback to user function
//       }
//     }

//     String toHtml(uint8_t id) override {
//       char buffer[400];
//       snprintf(
//         buffer,
//         400,
//         "<div class=button-container style=\"left: %uvw; top: %uvh; width: %uvw; height: %uvh\"><button class=button type=\"button\" id=%u style=\"background: %s\"><b>%s</b></button></div>",
//         x, y, width, height,
//         id,
//         color,
//         label
//       );
//       return String(buffer);
//     }
// };
// struct Abxy : Element {
//   void(*callback_a)(bool);
//   void(*callback_b)(bool);
//   void(*callback_x)(bool);
//   void(*callback_y)(bool);

//   Abxy(
//     int c_x, 
//     int c_y, 
//     char* c_color, 
//     int c_size, 
//     void(*c_callback_a)(bool),
//     void(*c_callback_b)(bool),
//     void(*c_callback_x)(bool),
//     void(*c_callback_y)(bool),
//   ): x(c_x), y(c_y), color(c_color), size(c_size),
//   callback_a(c_callback_a), callback_b(c_callback_b), callback_x(c_callback_x), callback_y(c_callback_y) {
//     type = 3;
//   }
// };

class Controller {
  public:
    Controller(uint8_t ip, String password);

    void on_joystick(void(*callback_joystick)(int8_t, int8_t));
    void on_a(void(*callback_a)(bool));
    void on_b(void(*callback_b)(bool));
    void on_x(void(*callback_x)(bool));
    void on_y(void(*callback_y)(bool));

    void init();

  private:
    static uint8_t staticIP_tail;
    static IPAddress gateway;
    static IPAddress subnet;
    static IPAddress dns;

    AsyncWebServer server;
    AsyncWebSocket ws;

    static void(*callback_connect)(uint);
    static void(*callback_disconnect)(uint);

    static void(*callback_joystick)(int8_t, int8_t);
    static void(*callback_a)(bool);
    static void(*callback_b)(bool);
    static void(*callback_x)(bool);
    static void(*callback_y)(bool);

    static char* wifi_ssid;
    static char* wifi_password;

    String ws_password;

    void init_wifi();

    void init_controller();

    String generate_interface();

    static void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);

    static void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len);
};
#endif
