#include <iostream>
#include <queue>
#include <utility>
class Compare
{
public:
    bool operator() (std::pair<int, int> &time1, std::pair<int, int> &time2)
    {
        return time1.second > time2.second;
    }
};

int main ()
{
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, Compare> myQueue;

    int trains_amount = 0;
    std::cin >> trains_amount;
    for (int i = 0; i < trains_amount; i++) {
        int arrival_time = 0, departure_time = 0;
        std::cin >> arrival_time >> departure_time;
        if (myQueue.empty()) {
            myQueue.push({arrival_time, departure_time});
        }
        else {
            if (myQueue.top().second < arrival_time) {
                myQueue.pop();
                myQueue.push({arrival_time, departure_time});
            }
            else {
                myQueue.push({arrival_time, departure_time});
            }
        }
    }
    std::cout << myQueue.size();
    //<< std::endl;
//    while(!myQueue.empty()) {
//        std::cout << myQueue.top().first << " " << myQueue.top().second << "\n";
//        myQueue.pop();
//    }
    return 0;
}