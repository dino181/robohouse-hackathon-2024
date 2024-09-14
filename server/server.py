from flask import Flask

app = Flask(__name__)

@app.route("/forward")
def forward():
    print("Moving forward")
    return "<p>Hello, World!</p>"

@app.route("/backward")
def backward():
    print("Moving backward")
    return "<p>Hello, World!</p>"

@app.route("/right")
def right():
    print("Moving right")
    return "<p>Hello, World!</p>"

@app.route("/left")
def left():
    print("Moving left")
    return "<p>Hello, World!</p>"

@app.route("/stop")
def hello_world():
    print("stop")
    return "<p>Hello, World!</p>"



app.run(host="0.0.0.0", port=8080)
