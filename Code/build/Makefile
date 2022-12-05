
# change these
REPO_WORKING_DIR = /home/kali/LABS/lab-5-electronjs-eltopus
EMSDK_ROOT_FOLDER = /home/kali/emsdk/upstream/emscripten

# these are ok
IMAGE_OPS = $(REPO_WORKING_DIR)/Code/image_operations.cpp
IMAGE_H = $(REPO_WORKING_DIR)/Code/image.h
IMAGE_CPP = $(REPO_WORKING_DIR)/Code/image.cpp
IMAGE_GLUE_WRAPPER = $(REPO_WORKING_DIR)/Code/image_glue_wrapper.cpp
OUTPUT_JS = $(REPO_WORKING_DIR)/Code/ipl.js
OUTPUT_JS_MIN = $(REPO_WORKING_DIR)/Code/ipl_min.js
GLUE_JS = $(REPO_WORKING_DIR)/Code/glue.js
REPO_CODE_DIR = $(REPO_WORKING_DIR)/Code
WASM_OUTPUT = $(REPO_WORKING_DIR)/Code/ipl.wasm
WASM_MIN_OUTPUT = $(REPO_WORKING_DIR)/Code/ipl_min.wasm
MAIN = $(REPO_WORKING_DIR)/Code/main.cpp
EXECUTABLE = $(REPO_WORKING_DIR)/Code/build/main
NODE = $(REPO_WORKING_DIR)/Code/app.js
INDEX_JS = $(REPO_WORKING_DIR)/Code/indexjs
METRICS = $(REPO_WORKING_DIR)/Code/metrics.cpp
JAVA_SCRIPT_METRICS = $(REPO_WORKING_DIR)/Data/metrics/lib_metrics.csv
JAVA_SCRIPT_METRICS_MIN = $(REPO_WORKING_DIR)/Data/metrics/lib_metrics_min.csv
WASM_MAIN = $(REPO_WORKING_DIR)/Code/ws.cpp
EXAMPLE_OUTPUT = $(REPO_WORKING_DIR)/Code/ipl/src/js/ipl.html
IMAGE_OPS = $(REPO_WORKING_DIR)/Code/image_operations.cpp
METRICS = $(REPO_WORKING_DIR)/Code/metrics.cpp
IMAGE_CPP = $(REPO_WORKING_DIR)/Code/image.cpp
STATES = $(REPO_WORKING_DIR)/Code/states.cpp

OUTPUT_JS = $(REPO_WORKING_DIR)/Code/ipl.js

emcc:
	emcc -sASYNCIFY  $(IMAGE_CPP) $(WASM_MAIN) $(STATES) -s ALLOW_MEMORY_GROWTH=1 -s EXPORTED_FUNCTIONS="['_onblurAvgPressed', '_onblurLumPressed', '_onflipXPressed', '_onflipYPressed', '_onmaskPressed', '_onconvoBorderPressed', '_onconvoZeroPressed', '_undo', '_main']" -s EXPORTED_RUNTIME_METHODS=["ccall, cwrap, print, printErr"] -o $(EXAMPLE_OUTPUT)
compile:
	g++ -std=c++17 -o main $(IMAGE_CPP) $(MAIN)


