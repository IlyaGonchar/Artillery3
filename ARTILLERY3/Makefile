project:
	gcc -std=c99 -Wall -Wpedantic -o dist/project.exe project.c && start ./dist/project.exe
installemsdk: 
	cd .. && git clone https://github.com/emscripten-core/emsdk.git
	cd ../emsdk && emsdk install latest && emsdk activate latest && emsdk_env.bat && emcc ../ARTILLERY3/project.c -o project.html
	npm i http-server -g
runserver:
	cd ../emsdk && http-server