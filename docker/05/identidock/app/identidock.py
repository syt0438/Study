from flask import Flask
app = Flask(__name__)

@app.route('/')
def hello_world():
	return "<p>冬饮寒水，夜渡断桥</p>\n<p>忍性吞气，茹苦饮痛</p>\n<p>耐寒扫雪，冒热灭火</p>\n<p>夏不挥扇，雨不撑伞</p>"

if __name__ == '__main__':
	app.run(debug=True, host='0.0.0.0')
