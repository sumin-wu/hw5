#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
bool acceptOrReject(const std::string& in, std::string floats, int idx, std::string entry);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> final;
    for(set<string>::iterator it = dict.begin(); it!=dict.end(); ++it){
        bool temp = false;
        if (in.size()!=  (*it).size() ){
            continue;
        }
        for(char x = 'A'; x<='Z'; ++x){
            if((*it).find(x)!=string::npos){
                temp=true;
                break;
            }
        }
        if(temp){
            continue;
        }
        if(acceptOrReject(in,floating,0,*it)){
            final.insert(*it);
        }
    }
    for(std::set<std::string>::iterator it = final.begin(); it!=final.end(); ++it){
        std::cout<<*it<<" ";
    }
    std::cout<< endl;
    return final;
}

// Define any helper functions here
bool acceptOrReject(const std::string& in, std::string floats, int idx, std::string entry){
    if(idx>=(int)entry.size() && floats==""){
        return true;
      
    }
    else if (idx>=(int)entry.size() && floats!=""){
        return false;
      }
    else{
        if(in[idx]!='-' && in[idx]!=entry[idx]){
            return false;
        }
        else if(floats.find(entry[idx])!=string::npos){
            floats.erase(floats.find(entry[idx]),1);
        }
    }
    return acceptOrReject(in,floats,idx+1,entry);
}