# 题目信息

# Game

## 题目描述

Vasya and Petya have invented a new game. Vasya takes a stripe consisting of $ 1×n $ square and paints the squares black and white. After that Petya can start moves — during a move he may choose any two neighboring squares of one color and repaint these two squares any way he wants, perhaps in different colors. Petya can only repaint the squares in white and black colors. Petya’s aim is to repaint the stripe so that no two neighboring squares were of one color. Help Petya, using the given initial coloring, find the minimum number of moves Petya needs to win.

## 说明/提示

In the first sample Petya can take squares 1 and 2. He repaints square 1 to black and square 2 to white.

In the second sample Petya can take squares 2 and 3. He repaints square 2 to white and square 3 to black.

## 样例 #1

### 输入

```
6
111010
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
10001
```

### 输出

```
1
```

## 样例 #3

### 输入

```
7
1100010
```

### 输出

```
2
```

## 样例 #4

### 输入

```
5
00100
```

### 输出

```
2
```

# AI分析结果

### 题目内容中文重写
# 游戏

## 题目描述
瓦夏和彼佳发明了一种新游戏。瓦夏拿了一条由 $ 1×n $ 个方格组成的纸条，并将这些方格涂成黑色和白色。之后彼佳可以开始移动——在一次移动中，他可以选择任意两个相邻的同色方格，并将这两个方格重新涂成任意颜色，也可以涂成不同颜色。彼佳只能将方格涂成黑色和白色。彼佳的目标是重新涂这条纸条，使得没有两个相邻的方格颜色相同。请帮助彼佳，根据给定的初始涂色情况，找出彼佳获胜所需的最少移动次数。

## 说明/提示
在第一个样例中，彼佳可以选择第1个和第2个方格。他将第1个方格涂成黑色，第2个方格涂成白色。
在第二个样例中，彼佳可以选择第2个和第3个方格。他将第2个方格涂成白色，第3个方格涂成黑色。

## 样例 #1
### 输入
```
6
111010
```
### 输出
```
1
```

## 样例 #2
### 输入
```
5
10001
```
### 输出
```
1
```

## 样例 #3
### 输入
```
7
1100010
```
### 输出
```
2
```

## 样例 #4
### 输入
```
5
00100
```
### 输出
```
2
```

### 题解综合分析与结论
- **思路对比**：各位作者都发现最终满足条件的串只有两种，即“0101...”和“1010...”，通过比较原串与这两种目标串的差异来计算最少移动次数。
- **算法要点**：主要是遍历原串，统计与两种目标串不同字符的个数，最后取最小值。
- **解决难点**：避免模拟移动过程，直接从最终状态入手，简化问题。

### 所选题解
- **作者：Mr_WA的大号（5星）**
    - **关键亮点**：思路清晰，代码简洁，直接通过 `i%2+48` 来判断目标串字符，避免生成目标串，减少空间复杂度。
    - **核心代码**：
```c
#include<bits/stdc++.h>
using namespace std;
int n,ans1,ans2;
string st;
int main()
{
    cin>>n>>st;
    for(int i=0; i<n; i++)
    {
        if(st[i]==i%2+48)ans1++;
        else ans2++;
    }
    cout<<min(ans1,ans2);
    return 0;
}
```
核心实现思想：遍历原串，根据 `i%2+48` 得到“0101...”串在当前位置的字符，若与原串字符相同则 `ans1` 加1，否则 `ans2` 加1，最后输出两者最小值。

### 最优关键思路或技巧
从最终状态出发，避免模拟复杂的移动过程，直接比较原串与两种目标串的差异，简化问题求解。

### 可拓展之处
同类型题可能会改变目标串的规则，或者增加移动的限制条件，但解题思路依然可以从最终状态入手，分析原状态与目标状态的差异。

### 推荐洛谷题目
- P1055 [ISBN 号码](https://www.luogu.com.cn/problem/P1055)
- P1042 [乒乓球](https://www.luogu.com.cn/problem/P1042)
- P1067 [多项式输出](https://www.luogu.com.cn/problem/P1067)

### 个人心得摘录与总结
- **作者：Mr_WA的大号**：提到很多人会惯性想到模拟算法，但本题不需要，要从问题本质出发，找到更简单的解法。总结就是在解题时要打破惯性思维，深入分析问题，寻找更优解。 

---
处理用时：21.91秒