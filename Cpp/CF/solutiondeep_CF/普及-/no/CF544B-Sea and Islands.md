# 题目信息

# Sea and Islands

## 题目描述

A map of some object is a rectangular field consisting of $ n $ rows and $ n $ columns. Each cell is initially occupied by the sea but you can cover some some cells of the map with sand so that exactly $ k $ islands appear on the map. We will call a set of sand cells to be island if it is possible to get from each of them to each of them by moving only through sand cells and by moving from a cell only to a side-adjacent cell. The cells are called to be side-adjacent if they share a vertical or horizontal side. It is easy to see that islands do not share cells (otherwise they together form a bigger island).

Find a way to cover some cells with sand so that exactly $ k $ islands appear on the $ n×n $ map, or determine that no such way exists.

## 样例 #1

### 输入

```
5 2
```

### 输出

```
YES
SSSSS
LLLLL
SSSSS
LLLLL
SSSSS
```

## 样例 #2

### 输入

```
5 25
```

### 输出

```
NO
```

# AI分析结果

### 题目内容（中文重写）
# 海洋与岛屿

## 题目描述
某个区域的地图是一个由 $n$ 行和 $n$ 列组成的矩形区域。初始时，每个单元格都被海洋占据，但你可以用沙子覆盖地图上的一些单元格，使得地图上恰好出现 $k$ 个岛屿。如果可以仅通过沙子单元格，并且只能从一个单元格移动到与之相邻的单元格（即共享垂直或水平边的单元格），从一个沙子单元格到达另一个沙子单元格，那么我们就称这些沙子单元格组成一个岛屿。很容易看出，岛屿之间不会共享单元格（否则它们会共同形成一个更大的岛屿）。

找出一种用沙子覆盖单元格的方法，使得在 $n×n$ 的地图上恰好出现 $k$ 个岛屿，或者判断不存在这样的方法。

## 样例 #1
### 输入
```
5 2
```
### 输出
```
YES
SSSSS
LLLLL
SSSSS
LLLLL
SSSSS
```

## 样例 #2
### 输入
```
5 25
```
### 输出
```
NO
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是先判断是否能在 $n×n$ 的矩阵中放置 $k$ 个岛屿，若可以则构造出一种放置方案。判断的关键在于发现矩阵中最多能放置的岛屿数为 $\left\lceil \frac{n^2}{2} \right\rceil$ 。构造方案时，大多采用间隔放置岛屿的方法，即奇数行奇数列和偶数行偶数列放置岛屿，直到放置的岛屿数达到 $k$ 。

### 所选题解
- **作者：_byta (4星)**
    - **关键亮点**：思路清晰，代码简洁，通过判断 `(i + j) % 2` 来确定是否放置岛屿，减少了嵌套判断，提高了代码的可读性。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, k, cnt;
int main() 
{
    scanf("%d%d", &n, &k);
    if (k > ceil(n * n / 2.0))//特判无解情况
    {
        printf("NO\n");
        return 0;
    }
    cout<<"YES"<<endl;
    for (int i = 1; i <= n; i++) 
    {
        for (int j = 1; j <= n; j++) 
        {
            if (cnt < k && !((i + j) % 2)) 
            {
                putchar('L');
                cnt++;
            }
            else putchar('S');
        }
        puts("");
    }
    return 0;
}
```
核心实现思想：先特判是否有解，若有解则遍历矩阵，当 `cnt < k` 且 `(i + j) % 2 == 0` 时放置岛屿，否则放置海洋。

- **作者：Na2_CuCl4 (4星)**
    - **关键亮点**：思路明确，结合题目提示“不应该最大化岛屿的大小”，采用棋盘黑白格的方式排列岛屿，代码简洁易懂。
    - **重点代码**：
```cpp
#include <iostream>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    if (k > (n * n + 1) / 2) {
        cout << "NO" << endl;
        return 0;
    }
    cout << "YES" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (k && !((i + j) % 2)) {
                k--;
                cout << "L" ;
            } else
                cout << "S" ;
        }
        cout << endl;
    }
    return 0;
}
```
核心实现思想：先判断是否有解，若有解则遍历矩阵，当 `k > 0` 且 `(i + j) % 2 == 0` 时放置岛屿并减少 `k` 的值，否则放置海洋。

- **作者：zhouzihe (4星)**
    - **关键亮点**：思路清晰，直接指出在奇数行的奇数列和偶数行的偶数列放置岛屿，代码实现简洁明了。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,sum;
int main(){
    cin>>n>>k;
    if(k>ceil(n*n/2.0)){
        cout<<"NO";
        return 0;
    }
    cout<<"YES"<<endl;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(sum<k&&(i+j)%2==0){
                cout<<"L";
                sum++;
                continue;
            }
            cout<<"S";
        }
        cout<<endl;
    }
    return 0;
} 
```
核心实现思想：先判断是否有解，若有解则遍历矩阵，当 `sum < k` 且 `(i + j) % 2 == 0` 时放置岛屿并增加 `sum` 的值，否则放置海洋。

### 最优关键思路或技巧
- **判断可行性**：通过数学推导得出矩阵中最多能放置的岛屿数为 $\left\lceil \frac{n^2}{2} \right\rceil$ ，以此判断是否能放置 $k$ 个岛屿。
- **构造方案**：采用间隔放置岛屿的方法，即奇数行奇数列和偶数行偶数列放置岛屿，避免岛屿相连，简单高效。

### 可拓展之处
同类型题目可能会改变矩阵的形状（如矩形）、岛屿的连通规则（如斜向连通）或增加其他限制条件。类似的算法套路可以应用于构造类问题，先分析问题的可行性，再根据规则构造出满足条件的方案。

### 推荐题目
1. [P1036 选数](https://www.luogu.com.cn/problem/P1036)：涉及组合数学和构造方案。
2. [P1149 火柴棒等式](https://www.luogu.com.cn/problem/P1149)：需要构造满足等式的火柴棒组合。
3. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)：经典的构造类问题，需要在棋盘上放置皇后并满足一定条件。

### 个人心得摘录与总结
- **作者：OoXiao_QioO**：足足 $\verb!WA!$ 了三次才 $\verb!AC!$，提醒我们不要被样例迷惑，要深入分析问题，注意行与行之间的判断，避免出现错误的输出。
- **作者：过氧化氢_syq0057**：被样例坑了一下，注意当 $n$ 是偶数时，下次循环开始填的时候会从第一个开始填 `L`，和上一次的在一列，会变成一个岛，强调了对边界情况的处理。 

---
处理用时：40.31秒