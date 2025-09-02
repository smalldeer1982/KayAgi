# 题目信息

# 「EVOI-RD1」小昕昕

## 题目背景

一副扑克牌共有 $54$ 张牌，除去大小王后有 $52$ 张。在同一副牌中，一张牌只可能出现一次。

一副扑克牌中一共有四种花色：黑桃($\texttt{spade}$)、红桃($\texttt{heart}$)、梅花($\texttt{club}$)、方块($\texttt{diamond}$)。每个花色的牌共有 $13$ 张，分别为 $\texttt{A} \sim \texttt{K}$。

在题目中，以上四种花色分别以 $\texttt{S,H,C,D}$ 表示。

我们约定，任何一张牌，都以 **花色+点数** 表示，并且约定用 $\texttt{T}$ 表示 $\texttt{10}$，如 $\texttt{SA,D5,HT,CQ}$。

## 题目描述

昕昕手上有 **两副无大小王** 的扑克牌，她会从这些扑克牌里取出 $n$ 张牌。

昕昕创造了一个组合为 **“小昕昕”**，它的定义是，任意取出 $3$ 张牌，若这 $3$ 张牌的 **牌点一样** ，且花色有且仅有 **两种** ，则称为一对“小昕昕”。如 $\texttt{H3,S3,S3}$ 是一对“小昕昕”。

当这三张扑克牌组成 **“小昕昕”** 后，昕昕就会把它们从牌堆内拿出，**不可再次使用**。

现在，昕昕想让你帮她数数，这副牌里最多能组成多少对 **“小昕昕”**。

## 说明/提示

**本题采用捆绑测试。**

+ $\texttt{Subtask 1 (10 pts)}$ ：$1 \le n \le 3$。
+ $\texttt{Subtask 2 (20 pts)}$ ：$1 \le n \le 5$。
+ $\texttt{Subtask 3 (30 pts)}$ ：$1 \le n \le 20$。
+ $\texttt{Subtask 4 (10 pts)}$ ：$1 \le n \le 70$。
+ $\texttt{Subtask 5 (30 pts)}$ ：无特殊限制。

对于 $100\%$ 的数据，$1 \le n \le 104$，保证输入的牌都存在于两副无大小王的扑克牌中。

## 样例 #1

### 输入

```
3
S3
H3
S3```

### 输出

```
1```

## 样例 #2

### 输入

```
7
ST
ST
HT
HT
CT
CT
DT```

### 输出

```
2```

## 样例 #3

### 输入

```
6
DA
HA
D4
C5
DA
D4```

### 输出

```
1```

# AI分析结果

### 综合分析与结论
这些题解主要围绕计算给定扑克牌中能组成“小昕昕”组合的最大对数展开，多数采用桶排思想统计各牌点和花色的牌数，再结合贪心策略或规律判断组合对数。各题解的差异主要体现在实现细节和判断逻辑上。

### 所选题解
- **作者：昒昕 - 做法1**（5星）
    - **关键亮点**：思路清晰，先使用桶排统计牌数，再通过贪心策略优先将牌最少的花色与牌最多的花色配对，代码实现简洁易懂，时间复杂度为 $\mathcal{O}(n)$。
    - **核心代码**：
```cpp
#include <cstdio>
int poke[6][21];
int ans;
int change_color(char p) {
    switch (p) {
        case 'S': return 1;
        case 'H': return 2;
        case 'C': return 3;
        case 'D': return 4;
    }
}
int change_num(char p) {
    switch (p) {
        case 'A': return 1;
        case 'T': return 10;
        case 'J': return 11;
        case 'Q': return 12;
        case 'K': return 13;
        default: return int(p-'0');
    }
}
int main() {
    int n;
    char c,num;
    scanf("%d",&n);
    for (int i=1;i<=n;i++) {
        scanf(" %c%c",&c,&num);
        poke[change_color(c)][change_num(num)]++;
    }
    for (int i=1;i<=13;i++)
        for (int j=1;j<=4;j++)
            for (int k=1;k<=4;k++)
                if (poke[j][i]==2&&poke[k][i]==1&&j!=k) {
                    poke[j][i]=0;
                    poke[k][i]=0;
                    ans++;
                }
    for (int i=1;i<=13;i++)
        for (int j=1;j<=4;j++)
            for (int k=1;k<=4;k++)
                if (poke[j][i]==2&&poke[k][i]!=0&&j!=k) {
                    poke[j][i]=0;
                    poke[k][i]--;
                    ans++;
                }
    printf("%d\n",ans);
    return 0;
}
```
    - **核心思想**：先将输入的牌信息通过 `change_color` 和 `change_num` 函数转换为数组下标，使用 `poke` 数组统计各牌点和花色的牌数。然后优先处理 $2 + 1$ 组合，再处理需拆分的情况，每次成功组合则答案加 1。

- **作者：369Pai**（4星）
    - **关键亮点**：使用 `map<char, map<char, int>>` 记录扑克牌出现次数，避免字母与数字的转化，代码简洁，通过对同一点数牌张数的分类讨论得出结果。
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<map>
using namespace std;
map<char, map<char, int>> m;
int main()
{
    int n, ans = 0;
    cin >> n;
    for(int i = 1 ; i <= n ; i++)
    {
        string str;
        cin >> str;
        m[str[1]][str[0]]++;
    }
    for(auto i:m)
    {
        int sum = 0, cnt2 = 0;
        for(auto j:i.second)
        {
            sum += j.second;
            if(j.second == 2)cnt2++;
        }
        if(sum >= 6)
        {
            ans += 2;
        }
        else if(sum >= 3 && cnt2)
        {
            ans += 1;
        }
    }
    cout << ans;
    return 0;
}
```
    - **核心思想**：使用 `m` 记录各牌点和花色的牌数，遍历 `m` 统计同一点数的牌总数 `sum` 和花色为 2 张的数量 `cnt2`，根据 `sum` 和 `cnt2` 的值判断能组成的“小昕昕”对数。

- **作者：lichenzhen**（4星）
    - **关键亮点**：结合桶思想和贪心策略，对不同情况进行分类处理，代码逻辑清晰，通过两个函数处理花色和点数的转换。
    - **核心代码**：
```cpp
#include<bits/stdc++.h> 
using namespace std;
char s[3];
int book[15][5],ans;
int check1(char ch){
    if(ch=='A') return 1;
    if(ch=='T') return 10;
    if(ch=='J') return 11;
    if(ch=='Q') return 12;
    if(ch=='K') return 13;
    return ch-'0';
}
int check2(char ch){
    if(ch=='S') return 1;
    if(ch=='H') return 2;
    if(ch=='C') return 3;
    if(ch=='D') return 4;
}
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>s+1;
        book[check1(s[2])][check2(s[1])]++;
    }
    for(int i=1;i<=13;i++){
        for(int j=1;j<=4;j++)
            for(int k=1;k<=4;k++)
                if(book[i][j]+book[i][k]==3){
                    ans++;
                    book[i][j]=0;
                    book[i][k]=0;
                }
        for(int j=1;j<=4;j++)
            for(int k=j+1;k<=4;k++)
                if(book[i][j]+book[i][k]>=3){
                    ans++;
                    if(book[i][j]==2) book[i][j]=0,book[i][k]--;
                    else if(book[i][k]==2) book[i][k]=0,book[i][j]--;
                } 
    }
    cout<<ans;
}
```
    - **核心思想**：使用 `book` 数组统计牌数，先处理 $2 + 1$ 组合，再处理需拆分的情况，每次成功组合则答案加 1。

### 最优关键思路或技巧
- **桶排思想**：使用二维数组或 `map` 记录各牌点和花色的牌数，方便后续统计和处理。
- **贪心策略**：优先将牌最少的花色与牌最多的花色配对，以获得最大组合数。
- **分类讨论**：根据同一点数的牌张数和花色情况进行分类讨论，简化判断逻辑。

### 可拓展之处
同类型题可能会改变扑克牌的规则或组合条件，如增加牌的副数、改变组合的牌数或花色要求等。类似算法套路可应用于其他计数问题，通过统计元素数量并结合贪心或规律判断组合情况。

### 洛谷相似题目推荐
- P1090 [合并果子](https://www.luogu.com.cn/problem/P1090)：考察贪心策略和优先队列的应用。
- P1199 [三国游戏](https://www.luogu.com.cn/problem/P1199)：需要分析游戏规则，运用贪心思想求解。
- P2240 [部分背包问题](https://www.luogu.com.cn/problem/P2240)：使用贪心算法解决背包问题。

### 个人心得摘录与总结
- **作者：huangmingyi**：一开始尝试用结构体和排序解题，但按输入顺序拆分花色导致错误。后来明白应优先拆一个花色，优先将牌最少的花色与牌最多的花色配对。总结为在解题时要深入理解规则，选择合适的贪心策略。 

---
处理用时：44.25秒