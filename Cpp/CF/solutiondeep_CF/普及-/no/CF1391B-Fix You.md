# 题目信息

# Fix You

## 题目描述

给你一个 $n \times m$ 的矩阵，每一格上有个一标记不是 $R$ 就是 $D$，如果为 $R$ 表示这一格的物品会被送到这一格紧邻的右边的那一格，如果为 $D$ 表示这一格的物品会被送到这一格紧邻的下边的那一格。问你最少修改（$R$ 变 $D$ 或者 $D$ 变 $R$）多少次使得不管哪一个里的物品最后都能到达 $(n,m)$。

translated by [yu__xuan](https://www.luogu.com.cn/user/142110)

## 样例 #1

### 输入

```
4
3 3
RRD
DDR
RRC
1 4
DDDC
6 9
RDDDDDRRR
RRDDRRDDD
RRDRDRRDR
DDDDRDDRR
DRRDRDDDR
DDRDRRDDC
1 1
C```

### 输出

```
1
3
9
0```

# AI分析结果

### 题目内容
# Fix You

## 题目描述
给你一个 $n \times m$ 的矩阵，每一格上有个标记，不是 $R$ 就是 $D$。如果为 $R$ 表示这一格的物品会被送到这一格紧邻的右边的那一格；如果为 $D$ 表示这一格的物品会被送到这一格紧邻的下边的那一格。问你最少修改（$R$ 变 $D$ 或者 $D$ 变 $R$）多少次，使得不管从哪一格出发的物品最后都能到达 $(n,m)$。

translated by [yu__xuan](https://www.luogu.com.cn/user/142110)

## 样例 #1
### 输入
```
4
3 3
RRD
DDR
RRC
1 4
DDDC
6 9
RDDDDDRRR
RRDDRRDDD
RRDRDRRDR
DDDDRDDRR
DRRDRDDDR
DDRDRRDDC
1 1
C
```
### 输出
```
1
3
9
0
```
### 算法分类
无算法分类

### 综合分析与结论
这些题解的核心思路基本一致，都基于物品只能向右或向下移动，最终会到达最后一行或最后一列这一特性，得出只需确保最后一行全为 `R` 且最后一列全为 `D` （右下角格点除外），就能使所有物品到达 $(n, m)$ ，答案即为最后一行中 `D` 的数量与最后一列中 `R` 的数量之和。不同之处主要在于代码实现细节和表述方式。

### 所选的题解
 - **作者：Dry_ice（5星）**
    - **关键亮点**：思路清晰，不仅阐述了常规 $O(nm)$ 遍历解法，还提及优化为 $O(n + m)$ 遍历（仅遍历最后一行和最后一列），代码简洁明了。
    - **重点代码**：
```cpp
#include <stdio.h>
int n, m;
char mp[105][105];
inline bool check(int x, int y) {
    if (y == m && mp[x][y] == 'R')
        return false;
    if (x == n && mp[x][y] == 'D')
        return false;
    return true;
}
int main(void) {
    int t;
    for (scanf("%d", &t); t--; ) {
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= n; ++i)
            scanf("%s", mp[i] + 1);
        int ans = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) {
                if (i == n && j == m)
                    continue;
                if (!check(i, j))
                    ++ans;
            }
        printf("%d\n", ans);
    }
    return 0;
}
```
    - **核心实现思想**：定义 `check` 函数判断当前格点是否会导致物品出界，主函数中通过双重循环遍历矩阵，统计需要修改的格点数量。
 - **作者：smallfang（4星）**
    - **关键亮点**：对思路的阐述清晰，直接点明不会出现环，所以所有点都会走到最后一行或最后一列，进而得出统计最后一列 `R` 的个数和最后一行 `D` 的个数的解法，代码简洁易懂。
    - **重点代码**：
```cpp
#include <iostream>

using namespace std;

const int MAXN = 1e5;
const int INF = 1e9;

int n, m;

int main()
{
    int t;
    scanf("%d", &t);
    while (t -- )
    {
        scanf("%d%d", &n, &m);
        char x;
        int c = 0;
        for (int i = 1; i <= n; i ++ )
        {
            for (int j = 1; j <= m; j ++ )
            {
                cin >> x;
                if (i == n && j == m)
                {
                    continue;
                }
                if (i == n)
                {
                    c += (x!= 'R');
                }
                if (j == m)
                {
                    c += (x!= 'D');
                }
            }
        }
        printf("%d\n", c);
    }
    return 0;
}
```
    - **核心实现思想**：通过双重循环遍历矩阵，在遍历过程中，对于最后一行的格点，若字符不是 `R` 则计数增加；对于最后一列的格点，若字符不是 `D` 则计数增加，最终输出计数结果。
 - **作者：yu__xuan（4星）**
    - **关键亮点**：思路阐述结合图示，更加直观，代码实现简洁规范。
    - **重点代码**：
```cpp
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>

int t, n, m;
char map[518][518];

int main() {
    scanf("%d", &t);
    while(t--) {
        int ans = 0;
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                std::cin >> map[i][j];
                if (i == n && j == m) continue;
                if (j == m && map[i][j]!= 'D') ++ans;
                if (i == n && map[i][j]!= 'R') ++ans;
            }   
        }
        printf("%d\n", ans);    
    }    
    return 0;
}
```
    - **核心实现思想**：通过双重循环遍历矩阵，对于每一个格点，判断是否为右下角格点，若非右下角格点，再判断是否为最后一列且字符不为 `D` 或者是否为最后一行且字符不为 `R`，若是则增加计数，最后输出计数结果。

### 最优关键思路或技巧
利用物品移动方向的特性，聚焦于最后一行和最后一列的状态，避免对整个矩阵进行复杂的路径模拟，简化问题求解过程。

### 可拓展之处
同类型题可考虑增加物品移动方向（如左上、右下等），或者改变目标格点位置，此时可能需要更复杂的逻辑判断和算法设计。类似算法套路为在面对具有特定移动规则的网格问题时，分析移动特性，找到关键区域（如本题的最后一行和最后一列），通过对关键区域的处理来解决问题。

### 推荐洛谷题目
 - [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)：通过模拟地毯铺设过程，根据坐标判断覆盖关系，与本题类似之处在于对二维平面上元素的处理。
 - [P1046 陶陶摘苹果（升级版）](https://www.luogu.com.cn/problem/P1046)：涉及到对给定条件下数据的筛选和统计，与本题统计符合特定条件元素个数的思路类似。
 - [P1244 青蛙过河](https://www.luogu.com.cn/problem/P1244)：通过分析青蛙跳跃规则，找到过河的方法，和本题一样需要分析特定规则下的操作过程。

### 个人心得摘录与总结
无个人心得相关内容。 

---
处理用时：64.00秒