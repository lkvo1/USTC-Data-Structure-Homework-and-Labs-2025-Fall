#ifndef AIR_SYSTEM_H
#define AIR_SYSTEM_H

#include <iostream>
#include <vector>
#include <string>
#define ROUTES_MAX 100

class Seat {
public:
    int seatNo; // 座位号
    int level; // 舱位等级 1,2,3
    bool isBooked; // 是否已经预定

    Seat() : seatNo(0), level(0), isBooked(false) {}
    Seat(int seatNo, int level) : seatNo(seatNo), level(level), isBooked(false) {}
};

class Customer {
public:
    std::string name; // 姓名
    int level; // 预定的座位等级
    int seatNo; // 预定的座位号
    Customer* next; // 链表指针，指向下一个预定的客户
    Customer() : name(""), level(0), seatNo(0), next(nullptr) {}
    Customer(const std::string& name, int level) : name(name), level(level), seatNo(0), next(nullptr) {}
};

class LinearCustomers {
public:
    Customer* head; // 链表头指针
    Customer* tail; // 链表尾指针
    int count; // 预定的客户数量

    LinearCustomers();
    void addCustomer(const std::string& name, int level, bool bootSort = true); // 预定名单中增加客户启动自动排序
    void removeCustomer(const std::string& name);
    Customer* findCustomer(const std::string& name);
    int getCount() const;
};

// 队列客户不启动自动排序
class QueueCustomers : public LinearCustomers {
public:
    void enqueue(const std::string& name, int level);
    void dequeue();
};

class Route {
public:
    std::string src; // 出发地
    std::string dst; // 目的地
    int flightNo; // 航班号
    int planeNo; // 飞机号
    int data; // 日期
    Seat seats[200]; // 座位信息

    // 预定队列和候补队列
    QueueCustomers waitList; // 候补名单
    LinearCustomers bookList; // 预定名单

    Route() : src(""), dst(""), flightNo(0), planeNo(0), data(0) {}
    Route(const std::string& src, const std::string& dst, int flightNo, int planeNo, int date) : src(src), dst(dst), flightNo(flightNo), planeNo(planeNo), data(date) {}
    void printCustomers(); // 打印两个名单
};

class AirSystem {
private:
    Route routes[ROUTES_MAX];
    int routeCount; // 当前航线数量
public:
    AirSystem() : routeCount(0) {}
    void addRoute(const std::string& src, const std::string& dst, int flightNo, int planeNo, int date);
    std::vector<Route*> findRoutes(const std::string& dst, int currentDate); // 按目的地查找航线，返回所有符合条件的航线，并给出最早的航班的详细信息
    int getRouteCounts() const; // 获取当前航线数量
    void bookSeat(int flightNo, const std::string& customerName, int level); // 预定座位
    void cancelBook(int flightNo, const std::string& customerName); // 取消预定座位
    void printRoute(int flightNo); // 输入指定航班信息
    void printAllRoutes(); // 打印所有航线
    void helpQueue(Route* route, int seatIndex); // 给候补中最靠前的符合条件的人上seatIndex的座位
    void sortRoutes(); // 根据日期排序航线
    std::vector<const Route*> searchPath(const std::string& src, const std::string& dst); // 查找所有航线
    void dfs(const std::string& current_city, const std::string& dst, std::vector<const Route*>& path, std::vector<bool>& visited, int last_arrival_date, bool& found);
};


#endif