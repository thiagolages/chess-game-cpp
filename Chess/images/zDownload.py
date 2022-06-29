import os

piecesRawLink = 'https://images.chesscomfiles.com/chess-themes/pieces/neo/150/'
colors = ['b', 'w']
pieces = ['k', 'q', 'b', 'n', 'r', 'p']
extensions = ['.png', '.jpg']

for color in colors:
	for piece in pieces:
		os.system("wget "+piecesRawLink + color + piece + extensions[0])

boardsRawLink = 'https://images.chesscomfiles.com/chess-themes/boards/bases/150'

for extension in extensions:
	os.system("wget "+boardsRawLink + extension)