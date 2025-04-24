#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool helper2(const AvailabilityMatrix& aMtrx, const Worker_T& hire, const size_t& maximumSlot, const DailySchedule& daily){
    int slot=0;
    for (int j=0;j<aMtrx.size();j++){
        if(find(daily[j].begin(),daily[j].end(),hire)!=daily[j].end()){
            slot++;
        }
    }
    if(slot>maximumSlot){
        return true;
    }
    return false;
}


bool helper(const AvailabilityMatrix& aMtrx, 
            const size_t& dailyNeeds, 
            size_t maxShifts, 
            int dayz, 
            DailySchedule& daily){
    if(aMtrx.size()==dayz){
        return true;//filled!
    }
    for(int j = 0;j<aMtrx[0].size();++j){
        if(aMtrx[dayz][j]&&find(daily[dayz].begin(), daily[dayz].end(), j) ==daily[dayz].end()){
                //avail but not schedueld for td
            daily[dayz].push_back(j);
        
            if(helper2(aMtrx,j,maxShifts,daily)==false){
                if(dailyNeeds==daily[dayz].size()){
                    if(helper(aMtrx,dailyNeeds,maxShifts,dayz+1,daily)==true){
                        return true;
                    }
                    
                    
                }
                else if (dailyNeeds!=daily[dayz].size()==true){
                        if(helper(aMtrx,dailyNeeds,maxShifts,dayz,daily)==true)
                        {
                            return true;
                        }
                    }
                
            }
            daily[dayz].pop_back();
        
    }
    
}
return false;
}
// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& aMtrx,//.size() is the number of dayz
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(aMtrx.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    for (int j = 0; j<aMtrx.size(); j++){
        sched.push_back(vector<Worker_T>());
    }
    return helper(aMtrx, dailyNeed, maxShifts,0,sched);




}

