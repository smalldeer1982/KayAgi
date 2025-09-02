# 题目信息

# Fafa and the Gates

## 题目描述

Two neighboring kingdoms decided to build a wall between them with some gates to enable the citizens to go from one kingdom to another. Each time a citizen passes through a gate, he has to pay one silver coin.

The world can be represented by the first quadrant of a plane and the wall is built along the identity line (i.e. the line with the equation $ x=y $ ). Any point below the wall belongs to the first kingdom while any point above the wall belongs to the second kingdom. There is a gate at any integer point on the line (i.e. at points $ (0,0) $ , $ (1,1) $ , $ (2,2) $ , ...). The wall and the gates do not belong to any of the kingdoms.

Fafa is at the gate at position $ (0,0) $ and he wants to walk around in the two kingdoms. He knows the sequence $ S $ of moves he will do. This sequence is a string where each character represents a move. The two possible moves Fafa will do are 'U' (move one step up, from $ (x,y) $ to $ (x,y+1) $ ) and 'R' (move one step right, from $ (x,y) $ to $ (x+1,y) $ ).

Fafa wants to know the number of silver coins he needs to pay to walk around the two kingdoms following the sequence $ S $ . Note that if Fafa visits a gate without moving from one kingdom to another, he pays no silver coins. Also assume that he doesn't pay at the gate at point $ (0,0) $ , i. e. he is initially on the side he needs.

## 说明/提示

The figure below describes the third sample. The red arrows represent the sequence of moves Fafa will follow. The green gates represent the gates at which Fafa have to pay silver coins.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF935B/b75712c03fca29d89953f4e50f7a0d99cb311364.png)

## 样例 #1

### 输入

```
1
U
```

### 输出

```
0
```

## 样例 #2

### 输入

```
6
RURUUR
```

### 输出

```
1
```

## 样例 #3

### 输入

```
7
URRRUUU
```

### 输出

```
2
```

# AI分析结果

### 题目翻译
# Fafa和大门

## 题目描述
两个相邻的王国决定在它们之间建造一堵墙，并设置一些大门，以便公民能够从一个王国前往另一个王国。每次公民通过一扇大门时，他必须支付一枚银币。

世界可以用平面的第一象限来表示，墙沿着恒等线（即方程为 $x = y$ 的直线）建造。墙下方的任何点都属于第一个王国，而墙上方的任何点都属于第二个王国。直线上的任何整数点（即点 $(0,0)$、$(1,1)$、$(2,2)$ 等）都设有一扇大门。墙和大门不属于任何一个王国。

法法（Fafa）位于位置 $(0,0)$ 的大门处，他想在两个王国中四处走动。他知道自己将要进行的移动序列 $S$。这个序列是一个字符串，其中每个字符代表一次移动。法法将进行的两种可能的移动是 'U'（向上移动一步，从 $(x,y)$ 移动到 $(x,y + 1)$）和 'R'（向右移动一步，从 $(x,y)$ 移动到 $(x + 1,y)$）。

法法想知道，按照序列 $S$ 在两个王国中四处走动，他需要支付多少枚银币。请注意，如果法法经过一扇大门但没有从一个王国移动到另一个王国，他不需要支付银币。此外，假设他在点 $(0,0)$ 的大门处不需要支付，即他最初就在他需要的那一侧。

## 说明/提示
下图描述了第三个样例。红色箭头表示法法将遵循的移动序列。绿色大门表示法法必须支付银币的大门。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF935B/b75712c03fca29d89953f4e50f7a0d99cb311364.png)

## 样例 #1

### 输入
```
1
U
```

### 输出
```
0
```

## 样例 #2

### 输入
```
6
RURUUR
```

### 输出
```
1
```

## 样例 #3

### 输入
```
7
URRRUUU
```

### 输出
```
2
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是模拟点的移动过程，判断点是否穿过直线 $y = x$ 来统计需要支付的银币数量。大部分题解通过遍历移动序列，根据字符 'U' 和 'R' 更新点的坐标，当点位于直线上且下一步移动方向与当前方向相同时，认为点穿过了直线，计数器加一。部分题解还通过记录点所在的区域（王国）来判断是否穿过直线。

### 通用建议与扩展思路
- **思路方面**：在处理此类模拟问题时，关键是要准确理解题目中的规则和条件，如本题中“穿过”直线的定义。可以通过简单的样例手动模拟来验证思路的正确性。
- **代码实现**：使用字符串来存储移动序列是一个方便的选择，同时要注意边界条件的处理，如访问字符串下一个字符时可能越界的问题。
- **拓展**：同类型的题目可能会改变移动规则（如增加更多的移动方向）、改变边界条件（如墙的方程不同）或增加其他限制条件（如每次移动有不同的代价）。解题的关键仍然是准确模拟整个过程。

### 推荐洛谷题目
1. P1046 陶陶摘苹果：https://www.luogu.com.cn/problem/P1046
2. P1003 铺地毯：https://www.luogu.com.cn/problem/P1003
3. P1047 校门外的树：https://www.luogu.com.cn/problem/P1047

### 重点代码及核心实现思想
```cpp
// 以落河之秋的题解为例
#include<iostream>
#include<string>

using namespace std;

int n,x=0,y=0,k=0;
string s;

int main()
{
    cin>>n>>s; 
    for(int i=0; i<s.size(); i++)
    {
        if(s[i] == 'U')
        {
            y++;
        }
        if(s[i] == 'R')
        {
            x++;
        }
        
        if(x == y and s[i] == s[i+1]) 
        {
            k++;
        }
    }
    
    cout<<k;
    return 0;
}
```
核心实现思想：通过遍历字符串 `s` 模拟点的移动，根据字符 'U' 和 'R' 分别更新纵坐标 `y` 和横坐标 `x`。当点的坐标满足 `x == y` 且下一个移动方向与当前方向相同时，认为点穿过了直线，计数器 `k` 加一。最后输出计数器的值。

---
处理用时：31.78秒