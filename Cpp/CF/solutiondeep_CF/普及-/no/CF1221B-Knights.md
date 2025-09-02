# 题目信息

# Knights

## 题目描述

You are given a chess board with $ n $ rows and $ n $ columns. Initially all cells of the board are empty, and you have to put a white or a black knight into each cell of the board.

A knight is a chess piece that can attack a piece in cell ( $ x_2 $ , $ y_2 $ ) from the cell ( $ x_1 $ , $ y_1 $ ) if one of the following conditions is met:

- $ |x_1 - x_2| = 2 $ and $ |y_1 - y_2| = 1 $ , or
- $ |x_1 - x_2| = 1 $ and $ |y_1 - y_2| = 2 $ .

Here are some examples of which cells knight can attack. In each of the following pictures, if the knight is currently in the blue cell, it can attack all red cells (and only them).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1221B/52d6b0891a161fbd4258da7a11dd1ce54ed8afcb.png)A duel of knights is a pair of knights of different colors such that these knights attack each other. You have to put a knight (a white one or a black one) into each cell in such a way that the number of duels is maximum possible.

## 说明/提示

In the first example, there are $ 8 $ duels:

1. the white knight in ( $ 1 $ , $ 1 $ ) attacks the black knight in ( $ 3 $ , $ 2 $ );
2. the white knight in ( $ 1 $ , $ 1 $ ) attacks the black knight in ( $ 2 $ , $ 3 $ );
3. the white knight in ( $ 1 $ , $ 3 $ ) attacks the black knight in ( $ 3 $ , $ 2 $ );
4. the white knight in ( $ 1 $ , $ 3 $ ) attacks the black knight in ( $ 2 $ , $ 1 $ );
5. the white knight in ( $ 3 $ , $ 1 $ ) attacks the black knight in ( $ 1 $ , $ 2 $ );
6. the white knight in ( $ 3 $ , $ 1 $ ) attacks the black knight in ( $ 2 $ , $ 3 $ );
7. the white knight in ( $ 3 $ , $ 3 $ ) attacks the black knight in ( $ 1 $ , $ 2 $ );
8. the white knight in ( $ 3 $ , $ 3 $ ) attacks the black knight in ( $ 2 $ , $ 1 $ ).

## 样例 #1

### 输入

```
3
```

### 输出

```
WBW
BBB
WBW
```

# AI分析结果

### 题目内容
# 骑士

## 题目描述
给定一个 $n$ 行 $n$ 列的棋盘。最初棋盘的所有格子都是空的，你需要在棋盘的每个格子中放置一个白色或黑色的骑士。

骑士是一种国际象棋棋子，如果满足以下条件之一，它可以从格子 ($x_1$, $y_1$) 攻击格子 ($x_2$, $y_2$)：
- $ |x_1 - x_2| = 2$ 且 $ |y_1 - y_2| = 1$，或者
- $ |x_1 - x_2| = 1$ 且 $ |y_1 - y_2| = 2$。

以下是一些骑士可以攻击哪些格子的示例。在下面的每张图片中，如果骑士当前位于蓝色格子中，它可以攻击所有红色格子（且仅能攻击这些格子）。
![骑士攻击示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1221B/52d6b0891a161fbd4258da7a11dd1ce54ed8afcb.png)
骑士对决是指一对不同颜色且相互攻击的骑士。你必须在每个格子中放置一个骑士（白色或黑色），使得对决的数量尽可能多。

## 说明/提示
在第一个示例中，有 $8$ 次对决：
1. 位于 ($1$, $1$) 的白色骑士攻击位于 ($3$, $2$) 的黑色骑士；
2. 位于 ($1$, $1$) 的白色骑士攻击位于 ($2$, $3$) 的黑色骑士；
3. 位于 ($1$, $3$) 的白色骑士攻击位于 ($3$, $2$) 的黑色骑士；
4. 位于 ($1$, $3$) 的白色骑士攻击位于 ($2$, $1$) 的黑色骑士；
5. 位于 ($3$, $1$) 的白色骑士攻击位于 ($1$, $2$) 的黑色骑士；
6. 位于 ($3$, $1$) 的白色骑士攻击位于 ($2$, $3$) 的黑色骑士；
7. 位于 ($3$, $3$) 的白色骑士攻击位于 ($1$, $2$) 的黑色骑士；
8. 位于 ($3$, $3$) 的白色骑士攻击位于 ($2$, $1$) 的黑色骑士。

## 样例 #1
### 输入
```
3
```
### 输出
```
WBW
BBB
WBW
```

### 算法分类
构造

### 综合分析与结论
这些题解主要围绕如何构造出能使黑马和白马冲突数最多的放置方案。多数题解通过观察骑士走“日”字的特点，发现将棋盘黑白染色后，骑士每次移动会改变所在格子颜色，从而得出将黑马和白马分别放置在不同颜色格子能使冲突最多的结论。部分题解利用横纵坐标之和的奇偶性判断格子颜色，部分通过行列奇偶性判断，本质相同。还有题解采用暴力深搜或二分图染色的方法。

### 所选的题解
- **作者：dthythxth_Huge_Brain (5星)**
  - **关键亮点**：思路清晰，先分析出将棋盘黑白染色，让黑马和白马交错放置可使冲突数最多，代码通过简单的行列循环实现棋盘初始化和放置逻辑，可读性强。
  - **重点代码**：
```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<string> board(n, string(n, 'B'));  // 初始化棋盘，所有格子都放置黑马

    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {  // 偶数行从第一个位置开始放置白马
            for (int j = 0; j < n; j += 2) {
                board[i][j] = 'W';
            }
        } else {  // 奇数行从第二个位置开始放置白马
            for (int j = 1; j < n; j += 2) {
                board[i][j] = 'W';
            }
        }
    }

    // 输出棋盘
    for (int i = 0; i < n; i++) {
        cout << board[i] << endl;
    }

    return 0;
}
```
  - **核心实现思想**：先将棋盘所有格子初始化为放黑马，再根据行的奇偶性，在特定列位置放置白马。
- **作者：wmrqwq (5星)**
  - **关键亮点**：简洁明了地阐述贪心构造思路，通过将棋盘黑白交替染色得出放置规则，代码简短且逻辑清晰。
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define QwQ return 0
long long n;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if((i + j) % 2 == 0) //如果为黑色格子，就放黑色的马 
                cout << "B";
            else //否则放白色的马
                cout << "W";
        }
        cout << endl;
    }
    QwQ; //华丽的结束
}
```
  - **核心实现思想**：通过判断横纵坐标之和的奇偶性来确定格子颜色，进而放置相应颜色的马。
- **作者：Tachibana27 (4星)**
  - **关键亮点**：清晰阐述思路，指出马走“日”字引起冲突位置横纵坐标奇偶性不同，从而得出按横纵坐标之和奇偶放置马的方案，代码简洁。
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++, cout << "\n")
        for (int j = 1; j <= n; j++)//枚举棋盘的格子
            if (!((i + j) % 2))//偶数
                cout << "W";//放置白马
            else
                cout << "B";//放置黑马
    return 0;
}
```
  - **核心实现思想**：遍历棋盘每个格子，根据横纵坐标之和的奇偶性放置白马或黑马。

### 最优关键思路或技巧
通过对骑士走法特点的观察，利用棋盘黑白染色的方式，将黑马和白马分别放置在不同颜色的格子中，实现冲突数最大化。具体实现上，利用横纵坐标之和的奇偶性来快速判断格子应放置的马的颜色，简化了代码实现。

### 可拓展之处
同类型题通常围绕特定棋子在棋盘上的放置规则，求满足某种条件（如最大冲突数、最小覆盖等）的放置方案。类似算法套路是先分析棋子移动特点，找到规律后通过构造特定放置方式解决问题。

### 推荐题目
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：通过枚举和组合的方式解决数的选取问题，与本题通过分析规律构造方案类似。
- [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)：利用动态规划解决组合计数问题，同样需要分析问题特点找到规律进行构造。
- [P1433 吃奶酪](https://www.luogu.com.cn/problem/P1433)：通过搜索和剪枝解决路径规划问题，与本题分析棋子走法特点并构造方案的思维方式类似。

### 个人心得摘录与总结
无。 

---
处理用时：98.27秒