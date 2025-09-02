# 题目信息

# Bishwock

## 题目描述

Bishwock is a chess figure that consists of three squares resembling an "L-bar". This figure can be rotated by 90, 180 and 270 degrees so it can have four possible states:

```
XX   XX   .X   X.
X.   .X   XX   XX
```

Bishwocks don't attack any squares and can even occupy on the adjacent squares as long as they don't occupy the same square.

Vasya has a board with $ 2\times n $ squares onto which he wants to put some bishwocks. To his dismay, several squares on this board are already occupied by pawns and Vasya can't put bishwocks there. However, pawns also don't attack bishwocks and they can occupy adjacent squares peacefully.

Knowing the positions of pawns on the board, help Vasya to determine the maximum amount of bishwocks he can put onto the board so that they wouldn't occupy the same squares and wouldn't occupy squares with pawns.

## 样例 #1

### 输入

```
00
00
```

### 输出

```
1```

## 样例 #2

### 输入

```
00X00X0XXX0
0XXX0X00X00
```

### 输出

```
4```

## 样例 #3

### 输入

```
0X0X0
0X0X0
```

### 输出

```
0```

## 样例 #4

### 输入

```
0XXX0
00000
```

### 输出

```
2```

# AI分析结果

### 题目翻译
#### Bishwock

#### 题目描述
Bishwock是一种由三个正方形组成的类似“L形”的棋子。这个棋子可以旋转90度、180度和270度，因此它有四种可能的状态：
```
XX   XX  .X   X.
X.  .X   XX   XX
```
Bishwock不会攻击任何方格，只要它们不占据同一个方格，甚至可以占据相邻的方格。

Vasya有一个 $2\times n$ 的棋盘，他想在上面放置一些Bishwock棋子。令他沮丧的是，棋盘上的几个方格已经被棋子占据了，Vasya不能在这些方格上放置Bishwock棋子。然而，这些棋子也不会攻击Bishwock棋子，它们可以和平地占据相邻的方格。

已知棋盘上棋子的位置，帮助Vasya确定他最多可以在棋盘上放置多少个Bishwock棋子，使得它们不会占据同一个方格，也不会占据有棋子的方格。

#### 样例 #1
##### 输入
```
00
00
```
##### 输出
```
1
```

#### 样例 #2
##### 输入
```
00X00X0XXX0
0XXX0X00X00
```
##### 输出
```
4
```

#### 样例 #3
##### 输入
```
0X0X0
0X0X0
```
##### 输出
```
0
```

#### 样例 #4
##### 输入
```
0XXX0
00000
```
##### 输出
```
2
```

### 综合分析与结论
- **思路对比**：大部分题解采用贪心算法，从左到右扫描棋盘，能放就放，以保证放置数量最大。如“QWQ_jyc”“fish_love_cat”等题解。而“Seanq”采用线性DP，用三维数组 `f[i][j][k]` 表示进行到第 `i` 列，第一格和第二格取或不取的状态。
- **算法要点**：贪心算法要点在于判断四种L型放置情况，放置后标记已占用格子，避免重复放置。线性DP要点是状态定义和状态转移方程的确定。
- **解决难点**：贪心算法要解决当某区域有多种放法时的选择问题，如连续三个空列时优先放开口朝外的。线性DP要准确列出状态转移方程，考虑各种可能的状态转移。

### 高评分题解
- **作者：QWQ_jyc（5星）**
    - **关键亮点**：思路清晰，详细列举四种L型放置情况，代码简洁易懂，对贪心算法的正确性进行了说明。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,s;
char a[100],b[100];
int main(){
    cin>>a>>b;
    n=strlen(a);
    for(int i=0;i<n;i++){
        if(a[i]=='0'&&b[i]=='0'&&a[i+1]=='0'){
            a[i]='1';
            b[i]='1';
            a[i+1]='1';
            s++;
        }else
        if(a[i]=='0'&&b[i]=='0'&&b[i+1]=='0'){
            a[i]='1';
            b[i]='1';
            b[i+1]='1';
            s++;
        }else
        if(a[i]=='0'&&a[i+1]=='0'&&b[i+1]=='0'){
            a[i]='1';
            b[i+1]='1';
            a[i+1]='1';
            s++;
        }else
        if(a[i+1]=='0'&&b[i]=='0'&&b[i+1]=='0'){
            a[i+1]='1';
            b[i]='1';
            b[i+1]='1';
            s++;
        }	
    }		
    cout<<s;
    return 0;
}
```
核心实现思想：遍历棋盘，判断四种L型放置情况，若满足则标记已放置的格子并增加计数器。

- **作者：fish_love_cat（4星）**
    - **关键亮点**：对贪心算法的正确性进行了详细分析，指出当某区域有多种放法时优先放开口朝外的，避免结果误差。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int ans;
int main(){
    string a,b;
    cin>>a>>b;
    for(int i=1;i<a.size();i++)
    if(a[i-1]=='0'&&a[i]=='0'&&b[i-1]=='0')ans++,a[i]='X';
    else if(a[i-1]=='0'&&a[i]=='0'&&b[i]=='0')ans++,a[i]='X',b[i]='X';
    else if(a[i-1]=='0'&&b[i]=='0'&&b[i-1]=='0')ans++,b[i]='X';
    else if(b[i-1]=='0'&&a[i]=='0'&&b[i]=='0')ans++,a[i]='X',b[i]='X';
    cout<<ans;
    return 0;
}
```
核心实现思想：从左到右扫描棋盘，判断四种L型放置情况，若满足则标记已放置的格子并增加计数器，优先考虑开口朝外的放置方式。

### 最优关键思路或技巧
- **贪心策略**：从左到右扫描棋盘，能放就放，遇到多种放法时优先放开口朝外的，保证放置数量最大。
- **标记已放置格子**：放置L型后标记已占用的格子，避免重复放置。

### 可拓展之处
同类型题如在不同形状棋盘上放置特定形状的棋子，或在二维矩阵中放置特定图形等，都可考虑贪心或动态规划算法。类似算法套路有区间贪心、状态压缩DP等。

### 推荐洛谷题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：考察贪心算法。
- [P1216 [USACO1.5][IOI1994]数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)：考察动态规划。
- [P1802 5 倍经验日](https://www.luogu.com.cn/problem/P1802)：考察动态规划。

### 个人心得摘录与总结
- **傅思维666**：2019.10.24模拟赛各种假做法后来模拟AC场，后来知道还可以贪心。总结：做题时可能一开始想不到最优解法，多尝试不同方法，赛后多总结。
- **fish_love_cat**：当某区域怎么放都行时，一定要优先放开口朝外的，不然结果可能会出现误差。总结：贪心算法中要注意特殊情况的处理，避免结果出错。 

---
处理用时：35.88秒