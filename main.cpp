#include <map>
#include <iostream>
using namespace std;




// A negatív szám kezelésekor dönti el, hogy melyik oldalra kell csökkenteni az intervallumot.

void handleNegativeNumber(multimap<int, int> &intervals, multimap<int, int>::iterator it0, int num) {
    bool validNumber=true;
    int whichSide;
    auto it1=it0;
    ++it1;
    if (num>it1->first || num<it0->first){
        validNumber=false;
    }
    if(validNumber) {
        if (it1 != intervals.end() && it0->first < num && it1->first > num) {
            intervals.erase(num);
            intervals.insert(make_pair(num - 1, 0));
            intervals.insert(make_pair(num + 1, 1));
            whichSide = 2;
        } else if (it0->first < num) {
            whichSide = 1;
        } else {
            whichSide = 0;
        }

        if (whichSide == 1) {
            intervals.insert(make_pair(num - 1, whichSide));
            intervals.erase(num);
        } else if (whichSide == 0) {
            intervals.insert(make_pair(num + 1, whichSide));
            intervals.erase(num);
        }
    }

}
// Módosítja az intervallumot a megadott helyen.

void modifyInterval(multimap<int, int> &intervals, multimap<int, int>::iterator it0, int num, int whichSide) {
    intervals.insert(make_pair(num, whichSide));
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
void addNumber(multimap<int, int> &intervals, int num, int amount) {
    auto it = intervals.find(num);
    auto it0 = intervals.lower_bound(num);
    auto it1 = it0;
    auto it2 = it0;
    if (it != intervals.end()) {
        intervals.insert(make_pair(num, it->second));
        intervals.erase(it);
    }
    else {
        if (it0 != intervals.begin()) {
            it0--;
            if (num - it0->first == 1) {
                modifyInterval(intervals, it0, num, 1);
                amount+=1;
                return;
            }
        }
        auto it3 = it0;
        if (it3 != intervals.end() && it3->first - num == 1) {
            modifyInterval(intervals, it3, num, 0);
            return;
        }

        intervals.insert(make_pair(num, 0));
        intervals.insert(make_pair(num, 1));
    }
}


int main(){
    int amount=1;
    multimap<int, int> intervals;
    int num = -1;
    intervals.clear();
    while (num != 0) {
        cout << "Enter a number: ";
        cin >> num;
        if (num != 0) {
            if (num < 0&&amount>1) {
                auto it2 = intervals.lower_bound(num);
                num = abs(num);
                handleNegativeNumber(intervals, it2, num);
                amount--;
            }
            else {
                addNumber(intervals, num, amount);
                amount++;
            }
        }
        if (amount>1) {
            printResult(intervals);
        }
        else{
            cout<< "[]"<<endl;
        }
    }
    return 0;
}
