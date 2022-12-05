
# change these
REPO_WORKING_DIR = /home/kali/LABS/lab-4-networking-eltopus
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
EXAMPLE_OUTPUT = $(REPO_WORKING_DIR)/Code/client.html
IMAGE_OPS = $(REPO_WORKING_DIR)/Code/image_operations.cpp
METRICS = $(REPO_WORKING_DIR)/Code/metrics.cpp
IMAGE_CPP = $(REPO_WORKING_DIR)/Code/image.cpp
IMAGE_GLUE_WRAPPER = $(REPO_WORKING_DIR)/Code/image_glue_wrapper.cpp
GLUE_JS = $(REPO_WORKING_DIR)/Code/glue.js
OUTPUT_JS = $(REPO_WORKING_DIR)/Code/ipl.js

emcc:
	emcc -sASYNCIFY -sASYNCIFY_IMPORTS=getAllImages -lwebsocket.js -s ASSERTIONS=0 $(IMAGE_OPS) $(METRICS) $(IMAGE_CPP) $(WASM_MAIN) -s ALLOW_MEMORY_GROWTH=1 -s EXPORTED_FUNCTIONS="['_onblurOnePressed', '_onblurLumPressed', '_onflipXPressed', '_onflipYPressed', '_onmaskPressed', '_onconvoBorderPressed', '_onconvoZeroPressed', '_onencodePressed', '_ondecodePressed', '_onTest', '_undo', '_main']" -s EXPORTED_RUNTIME_METHODS=["ccall, cwrap"] -o $(EXAMPLE_OUTPUT)
build:
	emcc -std=c++17 -s ALLOW_MEMORY_GROWTH=1 -s NO_DISABLE_EXCEPTION_CATCHING  -sASSERTIONS $(IMAGE_OPS) $(METRICS) $(IMAGE_CPP) $(IMAGE_GLUE_WRAPPER) --post-js $(GLUE_JS) -O1 -o $(OUTPUT_JS) -s EXPORTED_RUNTIME_METHODS=["ccall, cwrap"] -s EXPORTED_FUNCTIONS=["_free"]

