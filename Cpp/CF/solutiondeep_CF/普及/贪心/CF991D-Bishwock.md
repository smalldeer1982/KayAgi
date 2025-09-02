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

### 题目内容重写

Bishwock 是一种由三个方格组成的“L型”棋子。它可以旋转90、180和270度，因此有四种可能的状态：

```
XX   XX   .X   X.
X.   .X   XX   XX
```

Bishwock 不会攻击任何方格，甚至可以占据相邻的方格，只要它们不占据同一个方格。

Vasya 有一个 $2 \times n$ 的棋盘，他想在上面放置一些 Bishwock。不幸的是，棋盘上的一些方格已经被棋子占据，Vasya 不能在这些方格上放置 Bishwock。然而，棋子也不会攻击 Bishwock，它们可以和平地占据相邻的方格。

已知棋盘上棋子的位置，帮助 Vasya 确定他可以在棋盘上放置的最大数量的 Bishwock，使得它们不会占据相同的方格，也不会占据有棋子的方格。

### 样例 #1

#### 输入

```
00
00
```

#### 输出

```
1
```

### 样例 #2

#### 输入

```
00X00X0XXX0
0XXX0X00X00
```

#### 输出

```
4
```

### 样例 #3

#### 输入

```
0X0X0
0X0X0
```

#### 输出

```
0
```

### 样例 #4

#### 输入

```
0XXX0
00000
```

#### 输出

```
2
```

### 题解分析与结论

所有题解都采用了贪心算法，从左到右扫描棋盘，尽可能多地放置 Bishwock。主要的难点在于如何处理不同方向的 L 型，以及如何避免重复放置。大多数题解通过标记已放置的方格来解决重复问题。

### 所选高分题解

#### 题解1：作者：QWQ_jyc (4星)

**关键亮点：**
- 简洁明了的贪心算法实现。
- 通过标记已放置的方格来避免重复。

**核心代码：**
```cpp
for(int i=0;i<n;i++){
    if(a[i]=='0'&&b[i]=='0'&&a[i+1]=='0'){
        a[i]='1'; b[i]='1'; a[i+1]='1'; s++;
    } else if(a[i]=='0'&&b[i]=='0'&&b[i+1]=='0'){
        a[i]='1'; b[i]='1'; b[i+1]='1'; s++;
    } else if(a[i]=='0'&&a[i+1]=='0'&&b[i+1]=='0'){
        a[i]='1'; b[i+1]='1'; a[i+1]='1'; s++;
    } else if(a[i+1]=='0'&&b[i]=='0'&&b[i+1]=='0'){
        a[i+1]='1'; b[i]='1'; b[i+1]='1'; s++;
    }
}
```

#### 题解2：作者：fish_love_cat (4星)

**关键亮点：**
- 强调贪心策略的正确性，特别是在多种放置选择时优先放置开口朝外的 L 型。
- 代码简洁，逻辑清晰。

**核心代码：**
```cpp
for(int i=1;i<a.size();i++){
    if(a[i-1]=='0'&&a[i]=='0'&&b[i-1]=='0') ans++, a[i]='X';
    else if(a[i-1]=='0'&&a[i]=='0'&&b[i]=='0') ans++, a[i]='X', b[i]='X';
    else if(a[i-1]=='0'&&b[i]=='0'&&b[i-1]=='0') ans++, b[i]='X';
    else if(b[i-1]=='0'&&a[i]=='0'&&b[i]=='0') ans++, a[i]='X', b[i]='X';
}
```

#### 题解3：作者：NOILinux_Ubuntu (4星)

**关键亮点：**
- 通过预处理棋盘数据，简化了后续的判断逻辑。
- 强调贪心策略的正确性，特别是在能放置时尽量放置。

**核心代码：**
```cpp
For(i,1,n)if(a[i]==3){
    if(a[i-1])++ans;
    else if(a[i+1])++ans,a[i+1]-=a[i+1]&(-a[i+1]);
    a[i]=0;
}
```

### 最优关键思路与技巧

1. **贪心策略**：从左到右扫描棋盘，尽可能多地放置 L 型。
2. **标记已放置方格**：通过标记已放置的方格来避免重复放置。
3. **优先放置开口朝外的 L 型**：在多种放置选择时，优先放置开口朝外的 L 型，以避免影响后续放置。

### 可拓展之处

类似的问题可以扩展到其他形状的棋子或更大的棋盘，贪心策略依然适用。此外，可以考虑使用动态规划来处理更复杂的放置规则。

### 推荐题目

1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1046 装箱问题](https://www.luogu.com.cn/problem/P1046)
3. [P1056 排座椅](https://www.luogu.com.cn/problem/P1056)

---
处理用时：37.89秒