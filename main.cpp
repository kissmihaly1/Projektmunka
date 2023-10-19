#include <map>
#include <iostream>
using namespace std;

// A negatív szám kezelésekor dönti el, hogy melyik oldalra kell csökkenteni az intervallumot.

int handleNegativeNumber(multimap<int, int> &intervals, multimap<int, int>::iterator it0, int number, int amount) {
    bool validnumber=true;
    int whichSide;
    auto it1=it0;
    ++it1;
    if (number>it1->first || number<it0->first){
        validnumber=false;
        return amount;
    }
        if (it1 != intervals.end() && it0->first < number && it1->first > number) {
            intervals.erase(number);
            intervals.insert(make_pair(number - 1, 0));
            intervals.insert(make_pair(number + 1, 1));
            whichSide = 2;
        } else if (it0->first < number) {
            whichSide = 1;
        } else {
            whichSide = 0;
        }

        if (whichSide == 1) {
            intervals.insert(make_pair(number - 1, whichSide));
            intervals.erase(number);
        } else if (whichSide == 0) {
            intervals.insert(make_pair(number + 1, whichSide));
            intervals.erase(number);
        }
        return amount-1;
    }

// Módosítja az intervallumot a megadott helyen.

void modifyInterval(multimap<int, int> &intervals, multimap<int, int>::iterator it0, int number, int whichSide) {
        intervals.insert(make_pair(number, whichSide));
        intervals.erase(it0);
}

// Kiírja az intervallumokat.

void printResult(multimap<int, int> &intervals){
    auto it = intervals.begin();
    while (it != intervals.end()){
        cout << "["<< it->first << ", ";
        it++;
        if (it != intervals.end()) cout << it->first << "]" << endl;
        it++;
    }
}

//main

int main(){
    multimap<int, int> intervals;
    int amount=0;
    int num = -1;
    intervals.clear();
    while (num != 0) {
        cout << "Enter a number: ";
        cin >> num;
        if (num != 0) {
            if (num < 0) {
                auto it2 = intervals.lower_bound(num);
                num = abs(num);
                handleNegativeNumber(intervals,it2, num, amount);
            }
            else {
                if (intervals.empty()) {
                    intervals.insert(make_pair(num, 0));
                    intervals.insert(make_pair(num, 1));
                    amount++;
                }
                else {
                    auto it = intervals.find(num);
                    if (it == intervals.end()) {
                        auto it0 = intervals.lower_bound(num);
                        auto it1 = intervals.lower_bound(num);

                        if (it0 == intervals.begin()) {
                            if (it0->first - num == 1) {
                                modifyInterval(intervals,it0, num, 0 );
                            } else {
                                intervals.insert(make_pair(num, 0));
                                intervals.insert(make_pair(num, 1));
                            }
                        } else if (it0 == intervals.end()) {
                            it0--;
                            if (num - it0->first == 1) {
                                modifyInterval(intervals,it0, num, 1);
                            } else {
                                intervals.insert(make_pair(num, 0));
                                intervals.insert(make_pair(num, 1));
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
                                    intervals.insert(make_pair(num, 0));
                                    intervals.insert(make_pair(num, 1));
                                }
                            }
                        }
                    }

                }
                amount++;
            }
        }
        if (amount>=1) {
            printResult(intervals);
        }
        else{
            cout<< "[]"<<endl;
        }
    }
    return 0;
}