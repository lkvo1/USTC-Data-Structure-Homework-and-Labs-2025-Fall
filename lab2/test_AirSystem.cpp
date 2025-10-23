#include "AirSystem.h"
#include <iostream>

int main() {
    AirSystem system;

    system.addRoute("Beijing", "Shanghai", 1001, 1, 20251012);
    system.addRoute("Shanghai", "Guangzhou", 1002, 2, 20251013);
    system.addRoute("Beijing", "Guangzhou", 1003, 3, 20251014);
    system.addRoute("Guangzhou", "Lujiang", 1004, 4, 20251015);
    std::cout << "\n All Routes:" << std::endl;
    system.printAllRoutes();

    std::cout << "\n 三个人预定座位1001号:" << std::endl;
    system.bookSeat(1001, "Alice", 1);
    system.bookSeat(1001, "Bob", 1);
    system.bookSeat(1001, "Charlie", 2);

    std::cout << "\n 1001号航线的信息:" << std::endl;
    system.printRoute(1001);

    std::cout << "\n To Guangzhou:" << std::endl;
    auto routes = system.findRoutes("Guangzhou", 20251011);
    for (auto r : routes) {
        std::cout << "Flight No: " << r->flightNo << ", Date: " << r->data << std::endl;
    }

    // Alice取消预定
    std::cout << "\n Alice cancelled" << std::endl;
    std::cout << " 取消前：";
    system.printRoute(1001);
    system.cancelBook(1001, "Alice");
    std::cout << " 取消后：";
    system.printRoute(1001);

    // 航线排序测试
    std::cout << "\n 按日期排序航线：" << std::endl;
    system.sortRoutes();
    system.printAllRoutes();

    // 简介路径查找（深度优先算法
    std::cout << "\n From Beijing to Lujiang:" << std::endl;
    std::vector<const Route*> path = system.searchPath("Beijing", "Lujiang");

    std::cout << path.front()->src;
    for (auto* r : path) {
        std::cout << " -> " << r->dst;
    }

    std::cout << std::endl;

    return 0;
}
