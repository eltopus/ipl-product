#pragma once

#ifndef STATES_H
#define STATES_H

#include <vector>
#include <iostream>
#include <map>


template<class T>
class States {
    protected:
        States() { }
        static std::map<std::string, std::vector<T>> mapOfImages;
        
        
   	public:
        
        ~States(){
            std::cout << "Destructor called ......................." << std::endl;
            for(typename std::map<std::string, std::vector<T>>::const_iterator it = mapOfImages.begin(); it != mapOfImages.end(); it++){
                //std::cout << "I am: " << it->first << std::endl;
                std::vector<T> state = it->second;
                if (state.size() > 0){
                    for (auto s: state) {
                        delete (*s);
                    }
                }
            }
            
        }
        
        static void addBackupState(T state, const char* id) {
            try {
                if(mapOfImages.find(id) != mapOfImages.end()){

                    std::cout << "found id! existing vector will be used" << std::endl;
                    std::vector<T> states = mapOfImages[id];
                    states.push_back(state);
                    std::cout << "mymap.size() is " << mapOfImages.size() << std::endl;
                }else {
                    std::cout << "cannot find id. new vector will be created" << std::endl;
                    std::vector<T> states;
                    states.push_back(state);
                    mapOfImages.insert(std::make_pair(id, states));
                    std::cout << "mymap.size() is " << mapOfImages.size() << std::endl;
                }
            }catch(std::exception e){
                printf("Add Current State THread Exception %s \n", e.what());
            }
        }

        static T restoreBackupState(const char* id) {

            try {
                if(mapOfImages.find(id) != mapOfImages.end()){
                    std::vector<T> states = mapOfImages[id];
                    std::cout << "Size of Vector Before " << states.size() << std::endl;
                    T state = states.back();
                    states.pop_back();
                    std::cout << "Size of Vector After " << states.size() << std::endl;
                    return state;
                }else {
                    std::cout << "Backup cannot be found!!!: " << id << std::endl;
                    // for(typename std::map<const char*, std::vector<T>>::const_iterator it = mapOfImages.begin(); it != mapOfImages.end(); it++){
                    //     std::cout << "I am: " << it->first << std::endl;
                    // }
                    return NULL;
                }
            }catch(std::exception e){
                printf("Add Current State THread Exception %s \n", e.what());
            }
            return NULL;
        }
    

};

 #endif