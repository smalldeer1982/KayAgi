# 题目信息

# Minimum Ties

## 题目描述

A big football championship will occur soon! $ n $ teams will compete in it, and each pair of teams will play exactly one game against each other.

There are two possible outcomes of a game:

- the game may result in a tie, then both teams get $ 1 $ point;
- one team might win in a game, then the winning team gets $ 3 $ points and the losing team gets $ 0 $ points.

The score of a team is the number of points it gained during all games that it played.

You are interested in a hypothetical situation when all teams get the same score at the end of the championship. A simple example of that situation is when all games result in ties, but you want to minimize the number of ties as well.

Your task is to describe a situation (choose the result of each game) so that all teams get the same score, and the number of ties is the minimum possible.

## 说明/提示

In the first test case of the example, both teams get $ 1 $ point since the game between them is a tie.

In the second test case of the example, team $ 1 $ defeats team $ 2 $ (team $ 1 $ gets $ 3 $ points), team $ 1 $ loses to team $ 3 $ (team $ 3 $ gets $ 3 $ points), and team $ 2 $ wins against team $ 3 $ (team $ 2 $ gets $ 3 $ points).

## 样例 #1

### 输入

```
2
2
3```

### 输出

```
0 
1 -1 1```

# AI分析结果

### 题目内容重写（中文）

# 最小平局数

## 题目描述

一场大型足球锦标赛即将举行！$ n $ 支球队将参加比赛，每对球队之间将恰好进行一场比赛。

比赛有两种可能的结果：

- 比赛可能以平局结束，此时双方球队各得 $ 1 $ 分；
- 一方球队可能获胜，此时获胜球队得 $ 3 $ 分，失败球队得 $ 0 $ 分。

一支球队的得分是它在所有比赛中获得的总分。

你对一种假设情况感兴趣：所有球队在锦标赛结束时得分相同。一个简单的例子是所有比赛都以平局结束，但你希望尽量减少平局的数量。

你的任务是描述一种情况（选择每场比赛的结果），使得所有球队得分相同，且平局数尽可能少。

## 说明/提示

在第一个样例中，两支球队各得 $ 1 $ 分，因为比赛以平局结束。

在第二个样例中，球队 $ 1 $ 击败球队 $ 2 $（球队 $ 1 $ 得 $ 3 $ 分），球队 $ 1 $ 输给球队 $ 3 $（球队 $ 3 $ 得 $ 3 $ 分），球队 $ 2 $ 击败球队 $ 3 $（球队 $ 2 $ 得 $ 3 $ 分）。

## 样例 #1

### 输入

```
2
2
3
```

### 输出

```
0 
1 -1 1
```

---

### 算法分类
**构造**

---

### 题解分析与结论

本题的核心在于通过构造比赛结果，使得所有球队的得分相同，并且平局数最少。题解主要通过数学推导和构造策略来解决该问题。

1. **数学推导**：通过建立方程组，推导出平局数和胜负局数的关系，进而确定最小平局数。
2. **构造策略**：根据球队数量的奇偶性，采用不同的构造策略。奇数球队时，每支球队赢 $\frac{n-1}{2}$ 次；偶数球队时，每支球队赢 $\frac{n-2}{2}$ 次，并安排 $\frac{n}{2}$ 场平局。

---

### 精选题解

#### 题解1：meyi（★★★★★）
**关键亮点**：
- 通过数学推导，清晰地给出了平局数和胜负局数的关系。
- 根据球队数量的奇偶性，分别给出了具体的构造策略。
- 代码简洁，时间复杂度为 $O(tn^2)$。

**核心代码**：
```cpp
for(ri i=1;i<n;++i){
    ri j=i+1;
    if(!(n&1)&&(i&1))++j,printf("0 ");
    for(;j<=n;++j)
        printf("%d ",(j-i)&1?-1:1);
}
```
**实现思想**：根据球队数量的奇偶性，安排胜负和平局，确保每支球队的得分相同。

---

#### 题解2：LeavingZzz（★★★★☆）
**关键亮点**：
- 详细分析了奇数球队和偶数球队的不同情况，并给出了具体的构造方法。
- 代码实现较为清晰，通过染色法安排比赛结果。

**核心代码**：
```cpp
void calc(int w,int te){
    memset(ans,0,sizeof(ans));
    memset(book,0,sizeof(book));
    for(int i=1;i<=N;i++)
        r[i]=N-1-(w+te);
    if(!w) return ;
    for(int i=1;i<=N;i++){
        top=0;
        for(int j=1;j<=N;j++){
            if(i==j) continue;
            if(te&&!book[i]&&!book[j]&&ans[i][j]==0){
                ans[i][j]=ans[j][i]=-2;
                book[i]=book[j]=true;
            }
            if(ans[i][j]==0&&top<w){
                if(r[j])
                stk[++top]=j,--r[j];
            }
        }
        for(int j=1;j<=top;j++)
            ans[i][stk[j]]=1,ans[stk[j]][i]=-1;
    }
}
```
**实现思想**：通过染色法安排比赛结果，确保每支球队的胜利次数和平局次数符合要求。

---

#### 题解3：一扶苏一（★★★★☆）
**关键亮点**：
- 详细分析了奇数球队和偶数球队的不同情况，并给出了具体的构造方法。
- 使用优先队列动态维护球队的胜负次数，确保每支球队的得分相同。

**核心代码**：
```java
while (intArrWins[i]++ != intHalf) {
    int j = Q.poll().intId;
    if (i < j) intArrWinner[i][j] = 1;
    else intArrWinner[j][i] = -1;
    ++intArrLost[j];
}
```
**实现思想**：通过优先队列动态维护球队的胜负次数，确保每支球队的得分相同。

---

### 最优关键思路与技巧
1. **数学推导**：通过建立方程组，推导出平局数和胜负局数的关系，确定最小平局数。
2. **构造策略**：根据球队数量的奇偶性，采用不同的构造策略，确保每支球队的得分相同。
3. **动态维护**：使用优先队列动态维护球队的胜负次数，确保每支球队的得分相同。

---

### 可拓展之处
1. **类似问题**：可以扩展到其他比赛结果分配问题，如篮球、排球等。
2. **算法优化**：可以进一步优化时间复杂度，减少不必要的计算。

---

### 推荐题目
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)
3. [P1036 选数](https://www.luogu.com.cn/problem/P1036)

---

### 个人心得摘录
- **调试经历**：在实现过程中，需要注意球队数量的奇偶性，避免遗漏特殊情况。
- **踩坑教训**：在安排平局时，需要确保每支球队的平局次数不超过一次。
- **顿悟感想**：通过数学推导和构造策略，可以有效地解决复杂的比赛结果分配问题。

---
处理用时：42.58秒