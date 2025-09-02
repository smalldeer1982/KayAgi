# 题目信息

# Bayan Bus

## 题目描述

The final round of Bayan Programming Contest will be held in Tehran, and the participants will be carried around with a yellow bus. The bus has 34 passenger seats: 4 seats in the last row and 3 seats in remaining rows.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF475A/8bce19353e5f54c2dfc8345d92904e1c0260a14e.png)The event coordinator has a list of $ k $ participants who should be picked up at the airport. When a participant gets on the bus, he will sit in the last row with an empty seat. If there is more than one empty seat in that row, he will take the leftmost one.

In order to keep track of the people who are on the bus, the event coordinator needs a figure showing which seats are going to be taken by $ k $ participants. Your task is to draw the figure representing occupied seats.

## 样例 #1

### 输入

```
9
```

### 输出

```
+------------------------+
|O.O.O.#.#.#.#.#.#.#.#.|D|)
|O.O.O.#.#.#.#.#.#.#.#.|.|
|O.......................|
|O.O.#.#.#.#.#.#.#.#.#.|.|)
+------------------------+
```

## 样例 #2

### 输入

```
20
```

### 输出

```
+------------------------+
|O.O.O.O.O.O.O.#.#.#.#.|D|)
|O.O.O.O.O.O.#.#.#.#.#.|.|
|O.......................|
|O.O.O.O.O.O.#.#.#.#.#.|.|)
+------------------------+
```

# AI分析结果

### 题目翻译
# 巴扬巴士

## 题目描述
巴扬编程竞赛的决赛将在德黑兰举行，参赛选手将乘坐一辆黄色巴士出行。这辆巴士有 34 个乘客座位：最后一排有 4 个座位，其余排各有 3 个座位。

![巴士座位图](https://cdn.luogu.com.cn/upload/vjudge_pic/CF475A/8bce19353e5f54c2dfc8345d92904e1c0260a14e.png)
赛事协调员有一份包含 $k$ 名需要在机场接送的参赛选手名单。当一名选手上车时，他会坐在最后一排有空位的座位上。如果最后一排有多个空位，他会选择最左边的那个。

为了跟踪巴士上的人员情况，赛事协调员需要一个图表来显示 $k$ 名选手将占用哪些座位。你的任务是绘制一个表示已占用座位的图表。

## 样例 #1
### 输入
```
9
```
### 输出
```
+------------------------+
|O.O.O.#.#.#.#.#.#.#.#.|D|)
|O.O.O.#.#.#.#.#.#.#.#.|.|
|O.......................|
|O.O.#.#.#.#.#.#.#.#.#.|.|)
+------------------------+
```

## 样例 #2
### 输入
```
20
```
### 输出
```
+------------------------+
|O.O.O.O.O.O.O.#.#.#.#.|D|)
|O.O.O.O.O.O.#.#.#.#.#.|.|
|O.......................|
|O.O.O.O.O.O.#.#.#.#.#.|.|)
+------------------------+
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心都是模拟乘客上车选座的过程，根据不同的思路实现了座位状态的更新与输出。
- **思路对比**：
    - 打表法（BCZSX）直接列出所有可能情况，简单粗暴但代码冗长。
    - 状态记录法（梦里调音、智子·起源等）用数组记录每个座位的状态，再根据状态输出结果。
    - 字符替换法（Ciyang、yf最qhhh）先定义巴士初始状态的字符数组，再将相应的空位字符替换为有人的字符。
    - 数学计算法（Eason_AC）通过数学公式计算每排的座位状态。
- **难点解决**：
    - 特殊座位（如最后一排、过道等）的处理是难点，不同题解采用了不同的判断逻辑来处理。
    - 座位状态的更新和输出格式的控制也是需要注意的地方。

### 所选题解
- **作者：Ciyang（4星）**
    - **关键亮点**：思路简单，通过先定义巴士初始状态的字符数组，再循环搜索并替换相应的空位字符为有人的字符，实现了座位状态的更新，代码简洁易懂。
    - **核心代码**：
```cpp
#include <iostream>
#include <stdio.h>
using namespace std;
int n;
char bus[][28]= {"+------------------------+ ", "|#.#.#.#.#.#.#.#.#.#.#.|D|)", "|#.#.#.#.#.#.#.#.#.#.#.|.| ", "|#.......................| ", "|#.#.#.#.#.#.#.#.#.#.#.|.|)", "+------------------------+ "};
// 初始状态
int main() {
    cin >> n;
    for(int i= 0; i < 28; i++)
        for(int j= 0; j < 6; j++)
            if(bus[j][i] == '#' && n) --n, bus[j][i]= 'O';
    for(int i= 0; i < 6; i++) {
        for(int j= 0; j < 27; j++)
            if(bus[i][j] != ' ') putchar(bus[i][j]);
        if(i != 5) putchar('\n');
    }
    return 0;
}
```
- **作者：little_cindy（4星）**
    - **关键亮点**：思路清晰，将巴士分为车身和座位两部分处理，通过自定义函数判断座位是否有人，代码结构清晰，易于理解。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
#define ll long long
#define inl inline
#define Ofast ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
int n;

void O(int a) {
    if (n >= a) {
        cout << "O.";
    } else {
        cout << "#.";
    }
    return;
}

int main() {
    cin >> n;
    cout << "+------------------------+\n|";
    O(1);
    for (int i = 5; i <= 32; i += 3) {
        O(i);
    }
    cout << "|D|)\n|";
    O(2);
    for (int i = 6; i <= 33; i += 3) {
        O(i);
    }
    cout << "|.|\n|";
    O(3);
    cout << "......................|\n|";
    for (int i = 4; i <= 34; i += 3) {
        O(i);
    }
    cout << "|.|)\n+------------------------+";
    return 0;
}
```
- **作者：yf最qhhh（4星）**
    - **关键亮点**：模拟思路直接，先定义巴士初始状态的字符数组，再按乘客上车规则模拟座位状态的更新，最后输出结果，代码逻辑明确。
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
#define ll long long
#define rll register long long
using namespace std;
char s[6][28]={
"+------------------------+ ",
"|#.#.#.#.#.#.#.#.#.#.#.|D|)",
"|#.#.#.#.#.#.#.#.#.#.#.|.| ",
"|#.......................| ",
"|#.#.#.#.#.#.#.#.#.#.#.|.|)",
"+------------------------+ ",
};
int main(){
    rll n,i=1,j=1,k,l;
    scanf("%lld",&n);
    for(k=1;k<=n;++k){
        if(j==1){//特别判断一下最后一排
            if(i==5)i=1,j+=2;
            s[i][j]='O';
            i++;
        }
        else{
            if(i==3){//不是最后一排的话需要特别判断一下过道
                s[++i][j]='O';
                i=1,j+=2;
            }
            else s[i++][j]='O';
        }
    }
    for(l=0;l<=5;l++){
        cout<<s[l]<<endl;
    }
    return 0;
}
```

### 最优关键思路或技巧
- 使用字符数组存储巴士的初始状态，方便后续进行状态更新和输出。
- 对于特殊座位（如最后一排、过道等）进行单独判断和处理。

### 可拓展之处
同类型题可能会有不同的座位布局和选座规则，解题思路仍然是模拟整个过程，关键在于准确处理各种特殊情况和状态更新。

### 推荐题目
- [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
- [P1042 乒乓球](https://www.luogu.com.cn/problem/P1042)
- [P1563 玩具谜题](https://www.luogu.com.cn/problem/P1563)

### 个人心得摘录与总结
- **BCZSX**：提到打表大法好，但也说明打表虽然能解决问题，但代码冗长，不具有通用性。
- **yf最qhhh**：对打表的大佬表示佩服，同时说明本题可以通过模拟解决，无需打表。 

---
处理用时：46.25秒