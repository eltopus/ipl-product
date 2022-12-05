#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "../../../../../../emsdk/upstream/emscripten/system/include/emscripten/websocket.h"
#include "../../../../../../emsdk/upstream/emscripten/system/include/emscripten/val.h"
#include <assert.h>
#include "json.hpp"
#include"image.h"
# include "states.cpp"



using namespace nlohmann;
using namespace emscripten;



const char* imageIds_[10] = {".img1", ".img2", ".img3", ".img4", ".img5", ".img6", ".img7", ".img8", ".img9", ".img10" };
json base64s_ = json::array();
json imgIds_ = json::array({".img1", ".img2", ".img3", ".img4", ".img5", ".img6", ".img7", ".img8", ".img9", ".img10"});

extern "C" {

    void onblurAvgPressed();
    void onblurLumPressed();
    void onflipXPressed();
    void onflipYPressed();
    void onmaskPressed();
    void onconvoBorderPressed();
    void onconvoZeroPressed();
    void undo();
    

    EM_JS(EM_VAL, getBase64StringFromDataURL, (std::string dataURL), {
        let d = dataURL.replace('data:', '').replace(/^.+,/, '');
        return d;
    });
    

    EM_ASYNC_JS(const char *, getAllImages, (const char* id), {

        var images, arr=[];
        images = document.getElementById(UTF8ToString(id));
      
        image = window.getComputedStyle(images).backgroundImage;
        arr.push(image.substr(5, image.length-7));
        

        let b64 = await new Promise((resolve) => {
            fetch(arr[0])
                .then((res) => res.blob())
                .then((blob) => {
                    const reader = new FileReader();
                    reader.onloadend = () => {
                        const b = getBase64StringFromDataURL(reader.result);
                        resolve(b);
                    };
                    reader.readAsDataURL(blob);
                }).catch(error => console.warn(error));
        });

        var lengthBytes = lengthBytesUTF8(b64) + 1;
        var stringOnWasmHeap = _malloc(lengthBytes);
        stringToUTF8(b64, stringOnWasmHeap, lengthBytes);
        return stringOnWasmHeap;
        
    });

    EM_JS(const char *, getActiveSelection, (), {

        let activeSelection = document.querySelector('.swiper-slide-active').id;
        var le = lengthBytesUTF8(activeSelection) + 1;
        var hea = _malloc(le);
        stringToUTF8(activeSelection, hea, le);
        return hea;

        
    });

    EM_JS(void, updateElement, (const char* id, const char* base64, const char* operations), {

        var byteString;
        var dataURI = UTF8ToString(base64);

        
        if(dataURI.split(',')[0].indexOf('base64') >= 0)
            byteString = atob(dataURI.split(',')[1]);
        else
            byteString = unescape(dataURI.split(',')[1]);

        // separate out the mime component
        var mimeString = dataURI.split(',')[0].split(':')[1].split(';')[0];

        // write the bytes of the string to a typed array
        var ia = new Uint8Array(byteString.length);
        for(var i = 0; i < byteString.length; i++)
        {
            ia[i] = byteString.charCodeAt(i);
        }

        var blob = new Blob([ia], {type: mimeString});
        let objectURL = URL.createObjectURL(blob);
        var image = document.getElementById(UTF8ToString(id));
        let url = 'url( ' + objectURL  + ' )';
        image.style.backgroundImage = url;
        let options = {};
        options["title"] = "COMPLETION NOTIFICATION";
        options["body"] = UTF8ToString(operations) + " OPERATION HAVE BEEN COMPLETED \n";
        options["silent"] = false;
        options["urgency"] = "normal";
        window.API.showCustomNotification(options);
        
    });
    
}


 void onblurAvgPressed() { 
    std::cout << "Blur Average Btn pressed\n";  
    const char* imageId = getActiveSelection();
    auto j = getAllImages(imageId);
    Image* img_ = new Image(j);
    Image* img_cp = new Image(*img_);
    States<Image*>::addBackupState(img_cp, imageId);
    img_->grayscale_avgs();
    std::string newImageBase64 = "data:image/png;base64," + img_->encodeByteString();
    delete img_;
    updateElement(imageId, newImageBase64.c_str(), "BLURAVG");
    
}

void onblurLumPressed() {
    std::cout << "Blur Lum Btn pressed\n" << std::endl;  
    const char* imageId = getActiveSelection();
    auto j = getAllImages(imageId);
    Image* img_ = new Image(j);
    Image* img_cp = new Image(*img_);
    States<Image*>::addBackupState(img_cp, imageId);
    img_->grayscale_lums();
    std::string newImageBase64 = "data:image/png;base64," + img_->encodeByteString();
    // std::cout << newImageBase64 << std::endl;
    delete img_;
    updateElement(imageId, newImageBase64.c_str(), "BLURLUM");

    
 }

void onflipXPressed() {
    std::cout << "FlipX Btn pressed\n";  
    const char* imageId = getActiveSelection();
    auto j = getAllImages(imageId);
    Image* img_ = new Image(j);
    Image* img_cp = new Image(*img_);
    States<Image*>::addBackupState(img_cp, imageId);
    img_->flipX();
    std::string newImageBase64 = "data:image/png;base64," + img_->encodeByteString();
    // std::cout << newImageBase64 << std::endl;
    delete img_;
    updateElement(imageId, newImageBase64.c_str(), "FLIPX");

    
}

void onflipYPressed() {
    std::cout << "FlipY Btn pressed\n"; 
    const char* imageId = getActiveSelection();
    auto j = getAllImages(imageId);
    Image* img_ = new Image(j);
    Image* img_cp = new Image(*img_);
    States<Image*>::addBackupState(img_cp, imageId);
    img_->flipY();
    std::string newImageBase64 = "data:image/png;base64," + img_->encodeByteString();
    // std::cout << newImageBase64 << std::endl;
    delete img_;
    updateElement(imageId, newImageBase64.c_str(), "FLIPY");

   
}

void onmaskPressed() {
    std::cout << "Color Mask Btn pressed\n"; 
    const char* imageId = getActiveSelection();
    auto j = getAllImages(imageId);
    Image* img_ = new Image(j);
    Image* img_cp = new Image(*img_);
    States<Image*>::addBackupState(img_cp, imageId);
    img_->colorMasks(1, 0, 0);
    std::string newImageBase64 = "data:image/png;base64," + img_->encodeByteString();
    // std::cout << newImageBase64 << std::endl;
    delete img_;
    updateElement(imageId, newImageBase64.c_str(), "COLOR_MASK");

    
}

void onconvoBorderPressed() {
    std::cout << "Conv Border Btn pressed\n"; 
    const char* imageId = getActiveSelection();
    auto j = getAllImages(imageId);
    Image* img_ = new Image(j);
    Image* img_cp = new Image(*img_);
    States<Image*>::addBackupState(img_cp, imageId);
    img_->std_convolve_clamp_to_border(0, 3, 3, 1, 1);
    std::string newImageBase64 = "data:image/png;base64," + img_->encodeByteString();
    // std::cout << newImageBase64 << std::endl;
    delete img_;
    updateElement(imageId, newImageBase64.c_str(), "CONVOLUTION_BORDER");


    
}

void onconvoZeroPressed() {
    std::cout << "Convo Zero pressed\n"; 
    const char* imageId = getActiveSelection();
    auto j = getAllImages(imageId);
    Image* img_ = new Image(j);
    Image* img_cp = new Image(*img_);
    States<Image*>::addBackupState(img_cp, imageId);
    img_->std_convolve_clamp_to_0(0, 3, 3, 1, 1);
    std::string newImageBase64 = "data:image/png;base64," + img_->encodeByteString();
    // std::cout << newImageBase64 << std::endl;
    delete img_;
    updateElement(imageId, newImageBase64.c_str(), "CONVOLUTION_ZERO");
    
}


void undo() { 
    std::cout << "Undo Btn pressed\n"; 
    const char* imageId = getActiveSelection();
    
    Image* img_ = States<Image*>::restoreBackupState(imageId);
    if (img_ != nullptr && img_ != NULL){
        std::string newImageBase64 = "data:image/png;base64," + img_->encodeByteString();
        std::cout << "Found it...." << std::endl;
        updateElement(imageId, newImageBase64.c_str(), "UNDO");
    }else {
        std::cout << "Cannot restore because id cannot be found" << std::endl;
    }    
}



int main (){

    std::cout << "Client application started...." << std::endl;

}





