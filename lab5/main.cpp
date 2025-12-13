#include "directedGraph.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <windows.h>

using namespace std;

// 景点信息结构体
struct Spot {
    int id;
    string name;
    string code;
    string intro;
};

const int MAX_CAPACITY = 20;
int currentSpots = 12;

Spot spots[MAX_CAPACITY];
int adjMatrix[MAX_CAPACITY][MAX_CAPACITY];
int roadTypeMatrix[MAX_CAPACITY][MAX_CAPACITY]; // 1: Walk, 2: Car, 3: Walk and Car
int sceneryMatrix[MAX_CAPACITY][MAX_CAPACITY]; // Level = 1-10
string directionMatrix[MAX_CAPACITY][MAX_CAPACITY]; // Directions

DirectedGraph campusMap;

// 反向方向构造器
string getOppositeDirection(const string& dir) {
    if (dir == "North") return "South";
    if (dir == "South") return "North";
    if (dir == "East") return "West";
    if (dir == "West") return "East";
    if (dir == "NorthEast") return "SouthWest";
    if (dir == "SouthWest") return "NorthEast";
    if (dir == "NorthWest") return "SouthEast";
    if (dir == "SouthEast") return "NorthWest";
    return "";
}

void buildGraph() {
    // 释放旧图
    freeGraph(campusMap);

    int* weightMat[MAX_CAPACITY];
    int* typeMat[MAX_CAPACITY];
    int* sceneMat[MAX_CAPACITY];
    string* dirMat[MAX_CAPACITY];

    for(int i = 0; i < currentSpots; ++i) {
        weightMat[i] = adjMatrix[i];
        typeMat[i] = roadTypeMatrix[i];
        sceneMat[i] = sceneryMatrix[i];
        dirMat[i] = directionMatrix[i];
    }

    generateDirectedGraph(campusMap, currentSpots, weightMat, typeMat, sceneMat, dirMat);
}

// 初始化地图
void initData() {
    // 初始化景点
    spots[0] = {0, "北门", "01", "宏伟的学校正门，交通枢纽。"};
    spots[1] = {1, "行政楼", "02", "办公区域，办事处。"};
    spots[2] = {2, "一号教学楼", "03", "主教学楼，历史悠久。"};
    spots[3] = {3, "二号教学楼", "04", "现代化多媒体教室。"};
    spots[4] = {4, "图书馆", "05", "藏书百万，学习圣地。"};
    spots[5] = {5, "人工湖", "06", "校园著名景点，风景秀丽。"};
    spots[6] = {6, "实验中心", "07", "包含各类理工科实验室。"};
    spots[7] = {7, "学生食堂", "08", "提供各地美食。"};
    spots[8] = {8, "男寝", "09", "学生休息区。"};
    spots[9] = {9, "女寝", "10", "学生休息区。"};
    spots[10] = {10, "体育馆", "11", "室内篮球场与羽毛球馆。"};
    spots[11] = {11, "南门", "12", "靠近生活区的小门。"};

    // 初始化矩阵
    for (int i = 0; i < MAX_CAPACITY; i++) {
        for (int j = 0; j < MAX_CAPACITY; j++) {
            adjMatrix[i][j] = INF;
            roadTypeMatrix[i][j] = 3; // 默认混合道路
            sceneryMatrix[i][j] = 5; // 默认景色等级
            directionMatrix[i][j] = "";
        }
    }

    // 添加边的函数
    auto addEdge = [&](int u, int v, int w, int type = 3, int scene = 5, string dir = "North") -> void {
        int uCode = u - 1; // 假设输入是代号1-12，转为0-11
        int vCode = v - 1;
        
        adjMatrix[uCode][vCode] = w;
        adjMatrix[vCode][uCode] = w;
        roadTypeMatrix[uCode][vCode] = type;
        roadTypeMatrix[vCode][uCode] = type;
        sceneryMatrix[uCode][vCode] = scene;
        sceneryMatrix[vCode][uCode] = scene;
        directionMatrix[uCode][vCode] = dir;
        directionMatrix[vCode][uCode] = getOppositeDirection(dir);
    };

    // 添加边 起始 终止 距离 类型 景色 方向
    addEdge(1, 2, 100, 3, 2, "South");     
    addEdge(1, 3, 200, 3, 3, "SouthEast");     
    addEdge(2, 3, 150, 1, 3, "East");     
    addEdge(2, 6, 100, 3, 2, "South");     
    addEdge(2, 5, 400, 3, 2, "SouthWest");    
    addEdge(3, 4, 100, 3, 2, "South");     
    addEdge(5, 4, 350, 3, 2, "North");     
    addEdge(5, 6, 100, 1, 5, "East");     
    addEdge(6, 4, 150, 1, 5, "East");      
    addEdge(4, 7, 300, 3, 1, "East");     
    addEdge(6, 8, 200, 1, 4, "South");     
    addEdge(8, 7, 150, 3, 2, "NorthEast");     
    addEdge(8, 9, 100, 3, 2, "South");     
    addEdge(8, 10, 120, 3, 2, "SouthEast");    
    addEdge(9, 12, 80, 3, 1, "South");
    addEdge(12, 10, 100, 3, 1, "NorthEast");
    addEdge(12, 11, 300, 3, 1, "NorthWest");    
    
    buildGraph();
}

void showAllSpots() {
    cout << "---------------- 校园景点查询 ----------------" << endl;
    cout << left << setw(5) << "ID" << setw(20) << "名称" << setw(10) << "代号" << "简介" << endl;
    for (int i = 0; i < currentSpots; i++) {
        cout << left << setw(5) << spots[i].id 
             << setw(20) << spots[i].name 
             << setw(10) << spots[i].code 
             << spots[i].intro << endl;
    }
    cout << "----------------------------------------------" << endl;
}

void querySpot() {
    int id;
    cout << "请输入景点代号进行查询: ";
    cin >> id;
    id--; // 转为索引
    if (id >= 0 && id < currentSpots) {
        cout << "\n景点信息" << endl;
        cout << "名称: " << spots[id].name << endl;
        cout << "代号: " << spots[id].code << endl;
        cout << "简介: " << spots[id].intro << endl;
        
        cout << "邻接点:" << endl;
        EdgeNode* p = campusMap.vertices[id].firstEdge;
        while (p) {
            cout << spots[p->adjVex].name 
                 << " (距离: " << p->weight << "m, 方向: " << p->direction 
                 << ", 类型: " << (p->roadType==1?"人行":p->roadType==2?"车行":"混合") 
                 << ", 景色等级: " << p->sceneryLevel << ")" << endl;
            p = p->next;
        }

    } else {
        cout << "Invalid ID." << endl;
    }
}

void printPathRecursive(int v, int* path) {
    if (path[v] == -1) {
        cout << spots[v].name;
        return;
    }
    printPathRecursive(path[v], path);
    cout << " -> " << spots[v].name;
}

void queryPath() {
    int start, end, type;
    cout << "输入起始点的代号: ";
    cin >> start;
    start--;
    cout << "输入终点的代号: ";
    cin >> end;
    end--;
    cout << "道路类型 (0: 任意 1: 人行 2: 车行): ";
    cin >> type;

    if (start < 0 || start >= currentSpots || end < 0 || end >= currentSpots) {
        cout << "Invalid IDs." << endl;
        return;
    }

    int* dist = new int[campusMap.vertexNum];
    int* path = new int[campusMap.vertexNum];

    dijkstra(&campusMap, start, dist, path, type);

    if (dist[end] == INF) {
        cout << "无 " << spots[start].name << " 到 " << spots[end].name << " 的路径" << endl;
    } else {
        cout << "\nShortest Path" << endl;
        cout << "Length: " << dist[end] << "m" << endl;
        cout << "Route: ";
        printPathRecursive(end, path);
        cout << endl;
    }

    delete[] dist;
    delete[] path;
}

void queryAllPaths() {
    int start, end;
    cout << "输入起始点的代号: ";
    cin >> start;
    start--;
    cout << "输入终点的代号: ";
    cin >> end;
    end--;

    vector<vector<int>> paths = getAllPaths(&campusMap, start, end);
    cout << "\nFound " << paths.size() << " paths:" << endl;
    for (size_t i = 0; i < paths.size(); ++i) {
        cout << "Path " << i + 1 << ": ";
        int totalDist = 0;
        for (size_t j = 0; j < paths[i].size(); ++j) {
            cout << spots[paths[i][j]].name;
            if (j < paths[i].size() - 1) {
                cout << " -> ";
                int u = paths[i][j];
                int v = paths[i][j+1];
                EdgeNode* p = campusMap.vertices[u].firstEdge;
                // 计算距离
                while(p) {
                    if(p->adjVex == v) {
                        totalDist += p->weight;
                        break;
                    }
                    p = p->next;
                }
            }
        }
        cout << " 总距离: " << totalDist << "m" << endl;
    }
}

int main() {
    SetConsoleOutputCP(65001);
    initData();
    int choice;
    while (true) {
        cout << "\n========== Campus Paths Finder ==========" << endl;
        cout << "1. 显示所有景点" << endl;
        cout << "2. 查询景点信息" << endl;
        cout << "3. 查询最短路径" << endl;
        cout << "4. 查询所有路径" << endl;
        cout << "5. 查询最佳多景点路径" << endl;
        cout << "6. 查找割顶" << endl;
        cout << "7. 修改地图" << endl;
        cout << "0. 退出" << endl;
        cout << "请输入文本：";
        cin >> choice;

        switch (choice) {
            case 1: showAllSpots(); break;
            case 2: querySpot(); break;
            case 3: queryPath(); break;
            case 4: queryAllPaths(); break;
            case 0: return 0;
            default: cout << "Invalid choice." << endl;
        }
    }
    return 0;
}