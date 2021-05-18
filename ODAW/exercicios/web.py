from flask import Flask, request

app = Flask(__name__)


@app.route("/")
def index():
    return "<h1>Olá ODAW 2020</h1>"


@app.route("/ano")
def ano():
    ano = request.args["ano"]
    return f"<h1>O ano é {ano}</h1>"


app.run()
