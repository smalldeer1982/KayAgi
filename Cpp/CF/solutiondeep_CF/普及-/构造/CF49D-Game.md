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

### 题目翻译
# 游戏

## 题目描述
瓦夏和彼佳发明了一种新游戏。瓦夏拿了一条由 $ 1×n $ 个方格组成的纸条，并将这些方格涂成黑色和白色。之后彼佳可以开始移动——在一次移动中，他可以选择任意两个相邻且颜色相同的方格，并将这两个方格重新涂成他想要的颜色，可能是不同的颜色。彼佳只能将方格涂成白色和黑色。彼佳的目标是重新涂这条纸条，使得没有两个相邻的方格颜色相同。请帮助彼佳，根据给定的初始涂色情况，找出彼佳获胜所需的最少移动次数。

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

### 综合分析与结论
- **思路对比**：这几道题解思路本质相同，都意识到最终的目标串只有两种情况（以0开头的01交替串和以1开头的01交替串），通过比较原串与这两个目标串的差异来确定最少移动次数。
- **算法要点**：
    - Mr_WA的大号：通过 `i % 2 + 48` 直接判断原串字符与目标串字符是否相同，统计差异个数。
    - Yo_haor：先生成两个目标子串，再逐位比较原串与目标子串的差异。
    - chengni：在读取原串字符时，同时构造目标串字符并比较差异。
    - Great_Influence：使用 `bitset` 存储原串，构造一个01相间的串，通过异或运算统计差异。
- **解决难点**：都巧妙地避免了模拟移动过程，直接从最终结果入手，通过比较差异来计算最少移动次数，降低了复杂度。

### 题解评分
- Mr_WA的大号：5星。思路清晰，代码简洁易懂，对算法思路的解释详细。
- Yo_haor：3星。思路简单直接，但代码生成子串的方式稍显繁琐。
- chengni：3星。思路正确，但代码变量命名不够清晰。
- Great_Influence：2星。使用 `bitset` 增加了代码复杂度，可读性较差。

### 所选题解
- Mr_WA的大号（5星）
    - 关键亮点：思路清晰，代码简洁，对算法思路解释详细。
    - 核心代码：
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
核心实现思想：通过 `i % 2 + 48` 直接判断原串字符与以0开头和以1开头的目标串字符是否相同，分别统计差异个数，最后输出较小值。

### 最优关键思路或技巧
直接从最终结果（两种01交替串）出发，比较原串与目标串的差异，避免模拟移动过程，降低复杂度。

### 拓展思路
同类型题可能会改变目标串的规则，或者增加移动的限制条件，但核心思路仍然是从最终结果入手，比较差异。类似算法套路可用于解决一些需要通过变换达到特定状态的问题，如棋盘染色、序列变换等。

### 推荐洛谷题目
- P1055 ISBN号码
- P1047 校门外的树
- P1094 纪念品分组

### 个人心得摘录与总结
Mr_WA的大号提到很多人会惯性地想到模拟算法，但本题不需要，要学会从题目本质出发，找到更简单的解法。这提醒我们在解题时不要局限于常规思维，要深入分析题目特点，寻找更优的解法。 

---
处理用时：24.99秒