import os
from flask import Flask, request, jsonify, json
import tensorflow_human_detector as tf_hd
import json

#Beacuse we are enabling CORS, the application must have some CSRF protection
# More info at: https://flask-cors.readthedocs.io/en/latest/
from flask_cors import CORS

app = Flask(__name__)
app.config["VIDEO_INPUT_DIR"] = os.path.join(
    os.path.dirname(os.path.abspath(__file__)), "input")

app.config["STATIC"] = os.path.join(os.path.dirname(
    os.path.abspath(__file__)), "static/index.html")

CORS(app)


@app.after_request
def add_header(response):
    response.cache_control.no_store = True
    return response

@app.route('/', methods=['GET', 'POST'])
def send_index():
    return app.send_static_file('index.html')


@app.route('/test', methods=['GET'])
def test():
    return "TEST ROUTE"


@app.route('/upload_video', methods=['POST'])
def upload_video():
	if request.method == "POST":
		if 'videoFile' not in request.files:
			return jsonify({"sucess": False, "message": "Key namned videoFile not found in formData"})
		print("request data >>>>>> " + str(request.files))	

		file = request.files["videoFile"]
		if file.filename == '':
			return jsonify({"sucess": False, "message": "File not appended to formData"})
		
		video_path = os.path.join(app.config["VIDEO_INPUT_DIR"], file.filename) 
		file.save(video_path)

		return jsonify({"sucess": True, "message": "Video successfully stored in "})
	

app.run(debug=True)