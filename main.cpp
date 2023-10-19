#include <map>
#include <iostream>
using namespace std;

// A negatív szám kezelésekor dönti el, hogy melyik oldalra kell csökkenteni az intervallumot.

void handleNegativeNumber(multimap<int, int> &intervals, int num) {

    auto it0 = intervals.find(num);
    auto it1 = intervals.find(num);
    if (it0==intervals.end()){
    }
    else{
            ++it1;

        if (it1->first==it0->first){  //ha ugyanaz
            intervals.erase(it0);
            intervals.erase(it1);
            return;
        }
        if (it0->first==num){
            if (it0->second==0){
                intervals.insert(make_pair(num+1, 0)); //also vegpont novelese
                intervals.erase(it0);
                return;
            }
            else{
                intervals.insert(make_pair(num-1, 1)); //felso vegpont csokkentese
                intervals.erase(it0);
                return;
            }
        }
    }
    if (it0==intervals.end()){
        auto it3 = intervals.lower_bound(num);
        auto it2 = intervals.lower_bound(num);
        --it2;
        if (it2->first < num && it3->first > num) {
            intervals.insert(make_pair(num-1, 0));
            intervals.insert(make_pair(num+1, 1));
        }
    }

}
// Módosítja az intervallumot a megadott helyen.

void modifyInterval(multimap<int, int> &intervals, multimap<int, int>::iterator it0, int num, int whichSide){
    intervals.insert(make_pair(num, whichSide));
    intervals.erase(it0);
}
// Hozzáad egy új intervallumot.

void addInterval(multimap<int, int> &intervals, int num){
    intervals.insert(make_pair(num, 0));
    intervals.insert(make_pair(num, 1));
}
// Kiírja az intervallumokat.


void printResult(multimap<int, int> &intervals){
    if (!intervals.empty()) {
        auto it = intervals.begin();
        while (it != intervals.end()) {
            cout << "[" << it->first << ", ";
            it++;
            if (it != intervals.end()) cout << it->first << "]" << endl;
            it++;
        }
    }
    else{
        cout<< "[]" <<endl;
    }
}

int main(){
    multimap<int, int> intervals;
    int num = -1;
    while (num != 0) {
        cout << "Enter a number: ";
        cin >> num;
        if (num != 0) {
            if (num < 0) {
                num = abs(num);
                handleNegativeNumber(intervals, num);
            }
            else {
                if (intervals.empty()) {
                    addInterval(intervals, num);
                } else {
                    auto it = intervals.find(num);
                    if (it == intervals.end()) {
                        auto it0 = intervals.lower_bound(num);
                        auto it1 = intervals.lower_bound(num);

                        if (it0 == intervals.begin()) {
                            if (it0->first - num == 1) {
                                modifyInterval(intervals,it0, num, 0 );
                            } else {
                                addInterval(intervals, num);
                            }
                        } else if (it0 == intervals.end()) {
                            it0--;
                            if (num - it0->first == 1) {
                                modifyInterval(intervals,it0, num, 1);
                            } else {
                                addInterval(intervals, num);
                            }
                        } else {
                            if (it0->second == 0) {
                                it0--;
                                if ((num - it0->first == 1) || (it1->first - num == 1)) {
                                    if ((num - it0->first == 1) && (it1->first - num == 1)) {
                                        intervals.erase(it0);
                                        intervals.erase(it1);
                                    } else if (num - it0->first == 1) {
                                        modifyInterval(intervals,it0, num, 1);
                                    } else {
                                        modifyInterval(intervals,it1, num, 0);
                                    }
                                } else {
                                    addInterval(intervals, num);
                                }
                            }
                        }
                    }
                }
            }
        }
        printResult(intervals);
    }
    return 0;
}
