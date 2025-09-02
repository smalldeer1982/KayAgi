# 题目信息

# Woodcutters

## 题目描述

Little Susie listens to fairy tales before bed every day. Today's fairy tale was about wood cutters and the little girl immediately started imagining the choppers cutting wood. She imagined the situation that is described below.

There are $ n $ trees located along the road at points with coordinates $ x_{1},x_{2},...,x_{n} $ . Each tree has its height $ h_{i} $ . Woodcutters can cut down a tree and fell it to the left or to the right. After that it occupies one of the segments $ [x_{i}-h_{i},x_{i}] $ or $ [x_{i};x_{i}+h_{i}] $ . The tree that is not cut down occupies a single point with coordinate $ x_{i} $ . Woodcutters can fell a tree if the segment to be occupied by the fallen tree doesn't contain any occupied point. The woodcutters want to process as many trees as possible, so Susie wonders, what is the maximum number of trees to fell.

## 说明/提示

In the first sample you can fell the trees like that:

- fell the $ 1 $ -st tree to the left — now it occupies segment $ [-1;1] $
- fell the $ 2 $ -nd tree to the right — now it occupies segment $ [2;3] $
- leave the $ 3 $ -rd tree — it occupies point $ 5 $
- leave the $ 4 $ -th tree — it occupies point $ 10 $
- fell the $ 5 $ -th tree to the right — now it occupies segment $ [19;20] $

In the second sample you can also fell $ 4 $ -th tree to the right, after that it will occupy segment $ [10;19] $ .

## 样例 #1

### 输入

```
5
1 2
2 1
5 10
10 9
19 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5
1 2
2 1
5 10
10 9
20 1
```

### 输出

```
4
```

# AI分析结果

### 题目内容重写

#### 题目描述

小苏西每天睡前都会听童话故事。今天的童话故事是关于伐木工人的，小女孩立刻开始想象伐木工人砍树的情景。她想象了下面描述的情景。

在一条路上有 $n$ 棵树，分别位于坐标为 $x_{1},x_{2},...,x_{n}$ 的点上。每棵树的高度为 $h_{i}$。伐木工人可以砍倒一棵树并将其向左或向右倒下。砍倒后，树会占据一个区间 $[x_{i}-h_{i},x_{i}]$ 或 $[x_{i};x_{i}+h_{i}]$。未被砍倒的树仍然占据一个点，坐标为 $x_{i}$。伐木工人可以砍倒一棵树，前提是该树倒下后占据的区间不包含任何已被占据的点。伐木工人希望尽可能多地砍倒树，因此苏西想知道，最多可以砍倒多少棵树。

#### 说明/提示

在第一个样例中，你可以这样砍倒树：

- 将第 $1$ 棵树向左倒——现在它占据区间 $[-1;1]$
- 将第 $2$ 棵树向右倒——现在它占据区间 $[2;3]$
- 保留第 $3$ 棵树——它占据点 $5$
- 保留第 $4$ 棵树——它占据点 $10$
- 将第 $5$ 棵树向右倒——现在它占据区间 $[19;20]$

在第二个样例中，你也可以将第 $4$ 棵树向右倒，之后它将占据区间 $[10;19]$。

#### 样例 #1

##### 输入

```
5
1 2
2 1
5 10
10 9
19 1
```

##### 输出

```
3
```

#### 样例 #2

##### 输入

```
5
1 2
2 1
5 10
10 9
20 1
```

##### 输出

```
4
```

### 题解分析与结论

#### 综合分析与结论

本题的核心是贪心算法，通过优先选择向左倒的策略，尽可能多地砍倒树。大部分题解都采用了类似的贪心思路，即优先向左倒，若无法向左倒则尝试向右倒，若两者都不行则不砍倒该树。这种策略的正确性在于，向左倒不会影响后续树的砍倒选择，而向右倒可能会影响下一棵树的砍倒选择，因此优先向左倒可以最大化砍倒的树的数量。

#### 最优关键思路或技巧

1. **贪心策略**：优先向左倒，若无法向左倒则尝试向右倒，若两者都不行则不砍倒该树。
2. **边界处理**：第一棵树向左倒，最后一棵树向右倒，中间的树按贪心策略处理。
3. **状态转移**：通过记录每棵树的倒向状态，确保砍倒的树不重叠。

#### 推荐题目

1. [P2887 [USACO07NOV]Sunscreen G](https://www.luogu.com.cn/problem/P2887)
2. [P2859 [USACO06FEB]Stall Reservations S](https://www.luogu.com.cn/problem/P2859)
3. [P1233 木棍加工](https://www.luogu.com.cn/problem/P1233)

### 精选题解

#### 题解1：作者：yzx72424 (赞：24)

**星级**：★★★★★  
**关键亮点**：简洁明了的贪心策略，代码实现清晰，边界处理得当。

**核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int xx[200000],h[200000];
int main() {
    int a,t=0;
    scanf("%d",&a);
    for(int i=1;i<=a;i++){
       scanf("%d%d",&xx[i],&h[i]);
    }
    for(int i=2;i<=a-1;i++){
        if(xx[i]-h[i]>xx[i-1])t++;
        else if(xx[i]+h[i]<xx[i+1]){
            t++;xx[i]+=h[i];
        }
    }
     if(a==1)printf("1");
     else printf("%d",t+2);
}
```

**个人心得**：作者通过简单的贪心策略，优先向左倒，若无法向左倒则尝试向右倒，代码实现简洁明了，适合初学者理解。

#### 题解2：作者：ddmd (赞：7)

**星级**：★★★★  
**关键亮点**：详细解释了贪心策略的正确性，代码实现清晰，边界处理得当。

**核心代码**：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e5+5;
int n,ans,h[maxn],x[maxn];
signed main() {
    ios::sync_with_stdio(0);
    n=read();
    for(int i=1;i<=n;i++) 
    x[i]=read(),h[i]=read();
    ans=2;
    for(int i=2;i<n;i++){
        if(x[i]-x[i-1]>h[i]) ans++;
        else if(x[i+1]-x[i]>h[i]) ans++,x[i]+=h[i];
    } 
    if (n==1)putchar('1');
    else writeln(ans); 
    return 0;
}
```

**个人心得**：作者通过详细解释贪心策略的正确性，帮助读者理解为什么优先向左倒是最优的，代码实现清晰，适合有一定基础的读者。

#### 题解3：作者：wenjing233 (赞：7)

**星级**：★★★★  
**关键亮点**：详细解释了贪心策略的正确性，代码实现清晰，边界处理得当。

**核心代码**：
```cpp
#include<cstdio>
using namespace std;
int p[100005],len[100005],n,ans,last;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&p[i],&len[i]);
    }
    p[0]=-2147483647;
    p[n+1]=2147483647;
    for(int i=1;i<=n;i++){
        if(last==0){
            if((long long)p[i]-(long long)p[i-1]>(long long)len[i])ans++,last=0;
            else if((long long)p[i+1]-(long long)p[i]>(long long)len[i])ans++,last=1;
            else last=0;
        }
        else{
            if((long long)p[i]-(long long)p[i-1]-(long long)len[i-1]>len[i])ans++,last=0;
            else if((long long)p[i+1]-(long long)p[i]>(long long)len[i])ans++,last=1;
            else last=0;
        }
    }
    printf("%d",ans);
    return 0;
}
```

**个人心得**：作者通过详细解释贪心策略的正确性，帮助读者理解为什么优先向左倒是最优的，代码实现清晰，适合有一定基础的读者。

---
处理用时：49.83秒