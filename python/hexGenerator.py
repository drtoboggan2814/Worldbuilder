from math import cos, sin, radians, pi
from PIL import Image, ImageDraw
from aggdraw import Draw, Brush, Pen

class HexagonGenerator(object):
	def __init__(self, edgeLength):
		self.edgeLength = edgeLength

	@property
	def colWidth(self):
		return self.edgeLength * 3

	@property
	def rowHeight(self):
		return sin(pi / 3) * self.edgeLength

	@property
	def patternSize(self):
		return self.colWidth, self.rowHeight * 2

	def __call__(self, row, col):
		x = (col + 0.5 * (row % 2)) * self.colWidth
		y = row * self.rowHeight
		for angle in range(0, 360, 60):
			x += cos(radians(angle)) * self.edgeLength
			y += sin(radians(angle)) * self.edgeLength
			yield x
			yield y

def hexGenerator(edgeLength, offset):
	x = offset
	y = offset
	for angle in range (0, 360, 60):
		x += cos(radians(angle)) * edgeLength
		y += sin(radians(angle)) * edgeLength
		yield x
		yield y

def createCanvas(patternSize, repetitions):
	width, height = patternSize

	canvasWidth = int(repetitions * width)
	canvasHeight = int(round(canvasWidth / height) * height)
	return Image.new('RGB', (canvasWidth, canvasHeight), 'white')

def main():
	patternSize = 4
	repetitions = 2
	hexagonGen = HexagonGenerator(32)
	image = createCanvas(hexagonGen.patternSize, repetitions)
	draw = Draw(image)
	for row in range(7):
		color = 250, 200, 150
		for col in range (repetitions):
			hex = hexagonGen(row, col)
			draw.polygon(list(hex), Brush(color))

	draw.flush()
	image.show()

main()
