#include "AirSystem.h"
using std::vector;

LinearCustomers::LinearCustomers() : head(nullptr), tail(nullptr), count(0) {}

void Route::printCustomers() {
    std::cout << "Booked Customers:" << std::endl;
    Customer* current = bookList.head;
    while (current != nullptr) {
        std::cout << "Name: " << current->name << ", Level: " << current->level << ", Seat No: " << current->seatNo << std::endl;
        current = current->next;
    }

    std::cout << "Waiting Customers:" << std::endl;
    current = waitList.head;
    while (current != nullptr) {
        std::cout << "Name: " << current->name << ", Level: " << current->level << std::endl;
        current = current->next;
    }
}

void LinearCustomers::addCustomer(const std::string& name, int level, bool bootSort) {
    Customer* newCustomer = new Customer(name, level);
    // 如果需要排序 按照用户姓名寻找合适的位置插入
    if (bootSort) {
        if (head == nullptr) {
            head = newCustomer;
            tail = newCustomer;
        } else if (newCustomer->name < head->name) { // 如果新客户姓名小于头节点，直接头插
            newCustomer->next = head;
            head = newCustomer;
        } else if (newCustomer->name >= tail->name) {// 如果新客户姓名大于等于尾节点，直接尾插
            tail->next = newCustomer;
            tail = newCustomer;
        } else { // 如果都是不，就找到首个大于新客户姓名的节点，插入到它前面
            Customer* current = head;
            while (current->next != nullptr && current->next->name < newCustomer->name) {
                current = current->next;
            } 
            newCustomer->next = current->next;
            current->next = newCustomer;
        }
    } else { // 不需要排序，直接尾插
        if (head == nullptr) {
            head = newCustomer;
            tail = newCustomer;
        } else {
            tail->next = newCustomer;
            tail = newCustomer;
        }
    }
    count++;
}

void LinearCustomers::removeCustomer(const std::string& name) {
    Customer* current = head;
    Customer* previous = nullptr;

    while (current != nullptr) {
        if (current->name == name) {
            if (previous == nullptr) { 
                head = current->next;
                if (head == nullptr) { 
                    tail = nullptr;
                }
            } else {
                previous->next = current->next;
                if (current == tail) { 
                    tail = previous;
                }
            }
            delete current;
            count--;
            return;
        }
        previous = current;
        current = current->next;
    }
}

Customer* LinearCustomers::findCustomer(const std::string& name) {
    Customer* current = head;
    while (current != nullptr) {
        if (current->name == name) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

int LinearCustomers::getCount() const {
    return count;
}

void QueueCustomers::enqueue(const std::string& name, int level) {
    addCustomer(name, level, false);
}

void QueueCustomers::dequeue() {
    
    if (head == nullptr) {
        std::cout << "Queue is empty." << std::endl;
        return;
    }

    Customer* temp = head;
    head = head->next;
    if (head == nullptr) { // 如果队列变空，更新尾指针
        tail = nullptr;
    }

    delete temp;
    count--;
}

void AirSystem::addRoute(const std::string& src, const std::string& dst, int flightNo, int planeNo, int date) {
    if (routeCount >= ROUTES_MAX) {
        std::cout << "Routes capacity has been full." << std::endl;
        return;
    }
    routes[routeCount] = Route(src, dst, flightNo, planeNo, date);
    // 初始化座位：1等20个 2等 60个 3等120个
    // seatNo 从 1 开始编号
    for (int i = 0; i < 200; ++i) {
        int level = 3;
        if (i < 20) level = 1;
        else if (i < 80) level = 2;
        else level = 3;
        routes[routeCount].seats[i] = Seat(i + 1, level);
    }
    routeCount++;
}

std::vector<Route*> AirSystem::findRoutes(const std::string& dst, int currentDate) {
    // 寻找所有符合条件的条件（按目的地） 其中的第一个值是日期最近的航班
    vector<Route*> result;
    for(int i = 0; i < routeCount; i++) {
        if (routes[i].dst == dst && currentDate <= routes[i].data) {
            result.push_back(&routes[i]);
        }
    }
    return result;
}

int AirSystem::getRouteCounts() const { return routeCount; }

void AirSystem::bookSeat(int flightNo, const std::string& customerName, int level) {
    Route* targetRoute = nullptr;
    for(int i = 0; i < routeCount; i++) {
        if(routes[i].flightNo == flightNo) {
            targetRoute = &routes[i];
            // 找到航线之后寻找有没有空闲座位
            for(int j = 0; j < 200; j++) {
                if(!routes[i].seats[j].isBooked && routes[i].seats[j].level == level) {
                    routes[i].bookList.addCustomer(customerName, level);
                    // 记录座位号
                    Customer* newCustomer = routes[i].bookList.findCustomer(customerName);
                    if (newCustomer) {
                        newCustomer->seatNo = routes[i].seats[j].seatNo;
                    }
                    routes[i].seats[j].isBooked = true; // 标记座位为已预定
                    std::cout << "Book done, your seat number is " << routes[i].seats[j].seatNo << std::endl;
                    return;
                }
            }

            // 如果没有找到空闲座位，加入候补队列
            char choice;
            std::cout << "No available seat, type in Y to join the waitlist: " << std::endl;
            std::cin >> choice;
            if(choice == 'Y' || choice == 'y') {
                targetRoute->waitList.enqueue(customerName, level);
                std::cout << "Waitlist joined." << std::endl;
            } else {
                std::cout << "Book canceled." << std::endl;
            }
            return;
        }
    }
}

void AirSystem::cancelBook(int flightNo, const std::string& customerName) {
    for(int i = 0; i < routeCount; i++) {
        if(routes[i].flightNo == flightNo) {
            Route* targetRoute = &routes[i];
            Customer* customer = targetRoute->bookList.findCustomer(customerName);
            if(customer != nullptr) {
                // 如果寻找到指定的客户，就取消预定，并将人从预定名单中删掉
                for(int j = 0; j < 200; j++) {
                    if(targetRoute->seats[j].isBooked && targetRoute->seats[j].level == customer->level) {
                        targetRoute->seats[j].isBooked = false;
                        break;
                    }
                }
                // 给候补中最靠前的符合条件的人上这个座位
                helpQueue(targetRoute, customer->seatNo - 1);
                targetRoute->bookList.removeCustomer(customerName);
                return;
            } else {
                std::cout << "Customer not found." << std::endl;
                return;
            }
        }
    }
    // 未找到航班
    std::cout << "Flight not found." << std::endl;
}

void AirSystem::printRoute(int flightNo) {
    for(int i = 0; i < routeCount; i++) {
        if(routes[i].flightNo == flightNo) {
            std::cout << "Flight No: " << routes[i].flightNo << ", Plane No: " << routes[i].planeNo 
                      << ", Source: " << routes[i].src << ", Destination: " << routes[i].dst 
                      << ", Date: " << routes[i].data << std::endl;

            routes[i].printCustomers();
            return;
        }
    }
    std::cout << "Flight not found." << std::endl;
}

void AirSystem::printAllRoutes() {
    for(int i = 0; i < routeCount; i++) {
        std::cout << "Flight No: " << routes[i].flightNo << ", Plane No: " << routes[i].planeNo 
                  << ", Source: " << routes[i].src << ", Destination: " << routes[i].dst 
                  << ", Date: " << routes[i].data << std::endl;
    }
}

void AirSystem::helpQueue(Route* route, int seatIndex) {
    if(route->waitList.head != nullptr) {
        Customer* curCustomer = route->waitList.head;
        while(curCustomer != nullptr) {
            if(curCustomer->level == route->seats[seatIndex].level) {
                // 找到符合条件的客户，则给这个人上桌
                route->bookList.addCustomer(curCustomer->name, curCustomer->level);
                route->seats[seatIndex].isBooked = true;
                route->waitList.removeCustomer(curCustomer->name);
                return;
            }
            curCustomer = curCustomer->next;
        }
    } else {
        return;
    }
}

void AirSystem::sortRoutes() {
    // 使用冒泡排序对航线按日期进行排序
    for(int i = 0; i < routeCount - 1; i++) {
        for(int j = 0; j < routeCount - i - 1; j++) {
            if(routes[j].data > routes[j + 1].data) {
                std::swap(routes[j], routes[j + 1]);
            }
        }
    }
}

std::vector<const Route*> AirSystem::searchPath(const std::string& src, const std::string& dst) {
    std::vector<const Route*> path;
    std::vector<bool> visited(routeCount, false);
    bool found = false;
    dfs(src, dst, path, visited, 0, found);

    if (!found) std::cout << "No path from " << src << " to " << dst << "." << std::endl;

    return path;
}

void AirSystem::dfs(const std::string& current_city, const std::string& dst, std::vector<const Route*>& path, std::vector<bool>& visited, int last_arrival_date, bool& found) {
    if (!path.empty() && current_city == dst) {
        found = true;
        return;
    }

    if (path.size() >= routeCount || found) {
        return;
    }

    for (int i = 0; i < routeCount; ++i) {
        if (!visited[i] && routes[i].src == current_city && routes[i].data >= last_arrival_date) {
            visited[i] = true;
            path.push_back(&routes[i]);

            dfs(routes[i].dst, dst, path, visited, routes[i].data, found);

            if (found) return;

            path.pop_back();
            visited[i] = false;
        }
    }
}