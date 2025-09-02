# 题目信息

# Li Hua and Chess

## 题目描述

This is an interactive problem.

Li Ming and Li Hua are playing a game. Li Hua has a chessboard of size $ n\times m $ . Denote $ (r, c) $ ( $ 1\le r\le n, 1\le c\le m $ ) as the cell on the $ r $ -th row from the top and on the $ c $ -th column from the left. Li Ming put a king on the chessboard and Li Hua needs to guess its position.

Li Hua can ask Li Ming no more than $ 3 $  questions. In each question, he can choose a cell and ask the minimum steps needed to move the king to the chosen cell. Each question is independent, which means the king doesn't actually move.

A king can move from $ (x,y) $ to $ (x',y') $ if and only if $ \max\{|x-x'|,|y-y'|\}=1 $ (shown in the following picture).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1797C/56c04da34d7867634f352a46b9f12f7f08ae1115.png)The position of the king is chosen before the interaction.

Suppose you were Li Hua, please solve this problem.

## 说明/提示

In test case 1, the king is at $ (2,2) $ . It takes $ 1 $ step to move to $ (2,3) $ and $ 2 $ steps to move to $ (2,4) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1797C/abf76b4ca2a66dfff2b7a8197cf3c1622c8fee3f.png)Note that the questions may not seem sensible. They are just a sample of questions you may ask.

## 样例 #1

### 输入

```
2
3 4

1

2

5 3

3

1

2```

### 输出

```
? 2 3

? 2 4

! 2 2

? 2 2

? 5 2

? 5 3

! 5 1```

# AI分析结果

### 题目内容重写
#### 题目描述
这是一个交互题。

李明和李华在玩一个游戏。李华有一个大小为 $n \times m$ 的棋盘。用 $(r, c)$（$1 \leq r \leq n, 1 \leq c \leq m$）表示棋盘上从上往下第 $r$ 行、从左往右第 $c$ 列的格子。李明在棋盘上放了一个国王，李华需要猜出国王的位置。

李华最多可以问李明 $3$ 个问题。每次问题中，他可以选择一个格子，询问国王移动到该格子的最小步数。每个问题都是独立的，即国王实际上不会移动。

国王可以从 $(x,y)$ 移动到 $(x',y')$，当且仅当 $\max\{|x-x'|,|y-y'|\}=1$（如下图所示）。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1797C/56c04da34d7867634f352a46b9f12f7f08ae1115.png)

国王的位置在交互开始前已经确定。

假设你是李华，请解决这个问题。

#### 说明/提示
在测试用例1中，国王位于 $(2,2)$。移动到 $(2,3)$ 需要 $1$ 步，移动到 $(2,4)$ 需要 $2$ 步。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1797C/abf76b4ca2a66dfff2b7a8197cf3c1622c8fee3f.png)

注意，问题可能看起来不合理，它们只是你可能提出的问题的示例。

#### 样例 #1
##### 输入
```
2
3 4

1

2

5 3

3

1

2
```

##### 输出
```
? 2 3

? 2 4

! 2 2

? 2 2

? 5 2

? 5 3

! 5 1
```

### 算法分类
构造

### 题解分析与结论
本题的核心是通过不超过3次询问，确定国王的位置。各题解的思路大多基于通过询问棋盘的两个角落（如 $(1,1)$ 和 $(1,m)$）来缩小国王可能的位置范围，然后通过第三次询问确定具体位置。不同题解的主要区别在于如何处理边界情况和优化询问策略。

### 评分较高的题解
#### 题解1：zzhbpyy (4星)
**关键亮点**：
- 通过询问 $(1,1)$ 和 $(1,m)$，利用返回的距离值进行分类讨论，快速缩小国王的位置范围。
- 代码简洁，逻辑清晰，处理边界情况较为合理。

**核心代码**：
```cpp
if(a+b==m-1){
    cout<<"? 1 "<<a+1<<endl;
    cin>>c;
    cout<<"! "<<c+1<<' '<<a+1<<endl;
    continue;
}
if(a==b){
    cout<<"? "<<a+1<<" 1"<<endl;
    cin>>c;
    cout<<"! "<<a+1<<' '<<c+1<<endl;
    continue;
}
if(a<b){
    cout<<"! "<<a+1<<' '<<m-b<<endl;
}
else cout<<"! "<<b+1<<' '<<a+1<<endl;
```

#### 题解2：DE_aemmprty (4星)
**关键亮点**：
- 通过询问 $(1,1)$ 和 $(1,m)$，利用返回的距离值判断国王的位置是否在两条直线的交点上。
- 代码逻辑清晰，处理边界情况较为合理。

**核心代码**：
```cpp
if (a == b && a + b + 1 > m) {
    printf("? %lld %lld\n", a + 1, (a < m ? m - a : 1)); fflush(stdout);
    cin >> c;
    printf("! %lld %lld\n", a + 1, (a < m ? m - a : 1) + c);
    fflush(stdout);
    return ;
}
if (a + b + 1 > m) {
    if (a > b)
        printf("! %lld %lld\n", b + 1, a + 1);
    else
        printf("! %lld %lld\n", a + 1, m - b);
    fflush(stdout);
    return ;
}
```

#### 题解3：abensyl (4星)
**关键亮点**：
- 通过询问 $(1,1)$ 和 $(n,m)$，利用返回的距离值判断国王的位置是否在两个正方形的交点上。
- 代码逻辑清晰，处理边界情况较为合理。

**核心代码**：
```cpp
if (sax == sbx && say == sby) {
    getans(sax, say);
} else if (sax == sbx) {
    query(sax, min(say, sby));
    int zc;
    cin >> zc;
    getans(sax, min(say, sby) + zc);
} else if (say == sby) {
    query(min(sax, sbx), say);
    int zc;
    cin >> zc;
    getans(min(sax, sbx) + zc, say);
} else {
    query(sax, sby);
    int zc;
    cin >> zc;
    if (zc == 0)
        getans(sax, sby);
    else
        getans(sbx, say);
}
```

### 最优关键思路或技巧
1. **询问策略**：通过询问棋盘的两个角落（如 $(1,1)$ 和 $(1,m)$）来缩小国王的位置范围。
2. **分类讨论**：根据返回的距离值进行分类讨论，快速确定国王的位置。
3. **边界处理**：在处理边界情况时，确保询问的点在棋盘内，避免无效询问。

### 可拓展之处
类似的问题可以通过类似的询问策略来解决，例如在更大的棋盘上或不同的移动规则下确定目标位置。

### 推荐题目
1. [P1082 国王游戏](https://www.luogu.com.cn/problem/P1082)
2. [P1036 选数](https://www.luogu.com.cn/problem/P1036)
3. [P1044 栈](https://www.luogu.com.cn/problem/P1044)

---
处理用时：54.60秒