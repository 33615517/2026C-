#define _CRT_SECURE_NO_WARNINGS 1
#include "Date.h"
#include <iostream>
using namespace std;
// 🐾 测试 1：构造、赋值与流输出 (测试新加的 << 重载)
void Test1_ConstructAndOutput()
{
    cout << "========== 1. 构造与流输出测试 ==========" << endl;
    Date d1;                     // 默认
    Date d2(2024, 2, 29);        // 闰年
    Date d3(d2);                 // 拷贝
    Date d4;
    d4 = d2;                     // 赋值

    // 🚀 见证魔法：现在可以直接用 cout 连着打印了！
    cout << "d1 (默认): " << d1 << endl;
    cout << "d2 (带参): " << d2 << endl;
    cout << "d3 (拷贝): " << d3 << endl;
    cout << "d4 (赋值): " << d4 << endl;
    cout << endl;
}

// 🐾 测试 2：加减运算
void Test2_Arithmetic()
{
    cout << "========== 2. 日期加减天数测试 ==========" << endl;
    Date d(2024, 2, 28);
    cout << "初始日期: " << d << endl;

    Date d1 = d + 5;
    cout << d << " + 5天 = " << d1 << endl;

    d += 100;
    cout << "连续 += 100天后: " << d << endl;

    Date d2 = d - 100;
    cout << d << " - 100天 = " << d2 << endl;

    d -= 100;
    cout << "连续 -= 100天后: " << d << endl;
    cout << endl;
}

// 🐾 测试 3：自增与自减
void Test3_IncrementAndDecrement()
{
    cout << "========== 3. 自增与自减测试 ==========" << endl;
    Date d(2024, 12, 31);
    cout << "初始日期: " << d << endl;

    Date ret1 = ++d;
    cout << "++d 执行后, d 为: " << d << " | 返回值为: " << ret1 << endl;

    Date ret2 = d++;
    cout << "d++ 执行后, d 为: " << d << " | 返回值为: " << ret2 << endl;
    cout << endl;
}

// 🐾 测试 4：比较运算符
void Test4_Relational()
{
    cout << "========== 4. 关系比较测试 ==========" << endl;
    Date d1(2024, 5, 20);
    Date d2(2024, 5, 21);

    cout << boolalpha; // 打印 true/false 魔法
    cout << d1 << " <  " << d2 << " : " << (d1 < d2) << endl;
    cout << d1 << " == " << d2 << " : " << (d1 == d2) << endl;
    cout << d1 << " != " << d2 << " : " << (d1 != d2) << endl;
    cout << noboolalpha;
    cout << endl;
}

// 🐾 测试 5：日期相减
void Test5_DateMinusDate()
{
    cout << "========== 5. 日期减日期测试 ==========" << endl;
    Date today(2024, 6, 1);
    Date target(2024, 10, 1);

    cout << target << " - " << today << " = " << (target - today) << " 天" << endl;
    cout << today << " - " << target << " = " << (today - target) << " 天" << endl;
    cout << endl;
}

// 🐾 测试 6：流提取 (测试新加的 >> 重载)
void Test6_Input()
{
    cout << "========== 6. 流提取测试 (需要敲键盘) ==========" << endl;
    Date d;
    cout << "请输入一个日期 (格式如 2024 5 20) : ";

    // 🚀 见证魔法：直接把键盘输入灌进对象里！
    cin >> d;

    cout << "输入的日期是: " << d << endl;
    cout << "输入的日期加上100天是: " << (d + 100) << endl;
}

int main()
{
    Test1_ConstructAndOutput();
    Test2_Arithmetic();
    Test3_IncrementAndDecrement();
    Test4_Relational();
    Test5_DateMinusDate();
    Test6_Input();

    return 0;
}