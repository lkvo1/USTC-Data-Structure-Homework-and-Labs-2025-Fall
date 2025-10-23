#include "Pholynomial.h"

void printMenu() {
    printf("\n--- 多项式计算器 ---\n");
    printf("1. 输入多项式 A\n");
    printf("2. 输入多项式 B\n");
    printf("3. 多项式加法 (A + B)\n");
    printf("4. 多项式减法 (A - B)\n");
    printf("5. 多项式乘法 (A * B)\n");
    printf("6. 多项式求导\n");
    printf("7. 打印多项式\n");
    printf("0. 退出\n");
    printf("---------------------\n");
    printf("请输入您的选择: ");
}

void createPolyFromInput(Polynomial *poly) {
    // 首先清空并重新初始化多项式
    // (这里假设没有提供销毁函数，所以我们只重新初始化头节点)
    initPolynomial(poly); 
    
    float coeff;
    int power;
    
    printf("请输入系数和指数 (例如: 3 2 代表 3x^2)，以 -1 -1 结束输入:\n");
    
    while (1) {6
        if (scanf("%f %d", &coeff, &power) != 2) {
            // 清除无效输入
            while (getchar() != '\n');
            printf("输入无效，请重新输入。\n");
            continue;
        }
        
        if (coeff == -1 && power == -1) {
            break;
        }
        addMono(poly, coeff, power);
    }
    printf("多项式输入完成: ");
    printPolyHumanReadable(poly);
}

int main() {
    Polynomial polyA, polyB;
    initPolynomial(&polyA);
    initPolynomial(&polyB);
    
    int choice;
    
    while (1) {
        printMenu();
        if (scanf("%d", &choice) != 1) {
            // 清除无效输入
            while (getchar() != '\n');
            printf("无效选择，请输入数字。\n");
            continue;
        }
        
        switch (choice) {
            case 1:
                printf("--- 输入多项式 A ---\n");
                createPolyFromInput(&polyA);
                break;
            case 2:
                printf("--- 输入多项式 B ---\n");
                createPolyFromInput(&polyB);
                break;
            case 3: {
                printf("--- 多项式加法 (A + B) ---\n");
                Polynomial sum = addPoly(&polyA, &polyB);
                printf("结果: ");
                printPolyHumanReadable(&sum);
                break;
            }
            case 4: {
                printf("--- 多项式减法 (A - B) ---\n");
                Polynomial diff = subPoly(&polyA, &polyB);
                printf("结果: ");
                printPolyHumanReadable(&diff);
                break;
            }
            case 5: {
                printf("--- 多项式乘法 (A * B) ---\n");
                Polynomial prod = multiplyPoly(&polyA, &polyB);
                printf("结果: ");
                printPolyHumanReadable(&prod);
                break;
            }
            case 6: {
                printf("--- 多项式求导 ---\n");
                int polyChoice;
                printf("选择要求导的多项式 (1 for A, 2 for B): ");
                if (scanf("%d", &polyChoice) != 1) {
                    while (getchar() != '\n');
                    printf("无效选择。\n");
                    break;
                }
                if (polyChoice == 1) {
                    Polynomial derivA = differentialPoly(&polyA);
                    printf("多项式 A 的导数: ");
                    printPolyHumanReadable(&derivA);
                } else if (polyChoice == 2) {
                    Polynomial derivB = differentialPoly(&polyB);
                    printf("多项式 B 的导数: ");
                    printPolyHumanReadable(&derivB);
                } else {
                    printf("无效选择。\n");
                }
                break;
            }
            case 7:
                printf("--- 打印多项式 ---\n");
                printf("多项式 A: ");
                printPolyHumanReadable(&polyA);
                printf("多项式 B: ");
                printPolyHumanReadable(&polyB);
                break;
            case 0:
                printf("程序退出。\n");
                return 0;
            default:
                printf("无效选择，请重试。\n");
                break;
        }
    }
    
    return 0;
}