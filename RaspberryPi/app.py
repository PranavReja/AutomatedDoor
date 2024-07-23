from flask import Flask
import datetime

app = Flask(__name__)

@app.route('/')
def image():
	return app.send_static_file("captured_image.jpg")

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0',port=8000)
