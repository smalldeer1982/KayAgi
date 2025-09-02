# 题目信息

# [USACO1.3] 修理牛棚 Barn Repair

## 题目描述

在一个月黑风高的暴风雨夜，Farmer John 的牛棚的屋顶、门被吹飞了 好在许多牛正在度假，所以牛棚没有住满。   

牛棚一个紧挨着另一个被排成一行，牛就住在里面过夜。有些牛棚里有牛，有些没有。 所有的牛棚有相同的宽度。   

自门遗失以后，Farmer John 必须尽快在牛棚之前竖立起新的木板。他的新木材供应商将会供应他任何他想要的长度，但是吝啬的供应商只能提供有限数目的木板。 Farmer John 想将他购买的木板总长度减到最少。

给出 $m,s,c$，表示木板最大的数目、牛棚的总数、牛的总数；以及每头牛所在牛棚的编号，请算出拦住所有有牛的牛棚所需木板的最小总长度。


## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$1\le m \le 50$，$1\le c \le s \le 200$。 

USACO Training Section 1.3


## 样例 #1

### 输入

```
4 50 18
3 
4 
6 
8 
14
15 
16 
17 
21
25 
26 
27 
30 
31 
40 
41 
42 
43
```

### 输出

```
25
```

# AI分析结果

### 综合分析与结论

本题的核心是通过贪心算法，最小化木板的总长度，同时满足木板数量的限制。大多数题解采用了类似的思路：首先假设用一块木板覆盖所有有牛的牛棚，然后通过断开最大的间隔来减少木板的总长度。部分题解还提供了动态规划的解法，但贪心算法在本题中更为简洁高效。

### 所选高星题解

#### 1. 作者：Starlight_Glimmer (5星)
- **关键亮点**：思路清晰，代码简洁，使用了贪心算法并通过排序相邻牛棚的间隔来优化木板长度。特别处理了木板数大于牛数的情况。
- **个人心得**：通过特判木板数大于牛数的情况，避免了不必要的计算，提升了代码的鲁棒性。

```cpp
#include<cstdio> 
#include<algorithm> 
#include<iostream> 
#define MAXN 205
using namespace std; 
int m,s,c,ans;
int a[MAXN],C[MAXN];
bool cmp(int x,int y) { return x>y; }
int main() { 
    scanf("%d %d %d",&m,&s,&c);
    for(int i=1;i<=c;i++) scanf("%d",&a[i]);
    if(m>c) { printf("%d\n",c); return 0; }
    sort(a+1,a+c+1);
    ans=a[c]-a[1]+1;
    for(int i=2;i<=c;i++) C[i-1]=a[i]-a[i-1];
    sort(C+1,C+c,cmp);
    for(int i=1;i<=m-1;i++) ans=ans-C[i]+1;
    printf("%d\n",ans);
}
```

#### 2. 作者：以墨 (4星)
- **关键亮点**：提供了动态规划的解法，虽然复杂度略高，但思路清晰，适合对贪心算法不熟悉的读者。通过滚动数组优化了空间复杂度。
- **个人心得**：动态规划虽然比贪心复杂，但在某些情况下更易于理解和实现。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int f[52],a[202],n,k,m,i,j;
int main() {
    scanf("%d%d%d",&m,&k,&n);
    if(m>=n) { printf("%d\n",n); return 0; }
    for(i=1;i<=n;i++) scanf("%d",&a[i]);
    sort(a+1,a+1+n);
    for(i=1;i<=n;i++) {
        for(j=m;j>=1;j--) f[j]=min(f[j]+a[i]-a[i-1],f[j-1]+1);
        f[0]=1<<30;
    }
    printf("%d\n",f[m]);
}
```

#### 3. 作者：junyuge (4星)
- **关键亮点**：贪心思路清晰，代码简洁，通过排序和计算间隔来优化木板长度。特别处理了木板数大于牛数的情况。
- **个人心得**：通过特判木板数大于牛数的情况，避免了不必要的计算，提升了代码的鲁棒性。

```cpp
#include<bits/stdc++.h> 
using namespace std;
int m,s,c,ans;
int a[210],b[210];
int main() {
    scanf("%d%d%d",&m,&s,&c);
    for (int i = 1;i <= c;i++) scanf("%d",&a[i]);
    sort(a + 1,a + c + 1);
    ans = a[c] - a[1] + 1;
    for (int i = 1;i <= c - 1;i++) b[i] = a[i + 1] - a[i] - 1;
    sort(b + 1,b + c);
    for (int i = c - 1;i >= c - m + 1;i--) ans -= b[i];
    printf("%d\n",ans);
}
```

### 最优关键思路与技巧
1. **贪心算法**：通过断开最大的间隔来减少木板的总长度，是本题的最优解法。
2. **排序优化**：通过排序相邻牛棚的间隔，确保每次断开的是最大的间隔，从而最小化木板长度。
3. **特判处理**：当木板数大于牛数时，直接输出牛数，避免不必要的计算。

### 可拓展之处
- **类似问题**：类似于区间覆盖问题，可以通过贪心算法优化覆盖长度。
- **动态规划**：虽然贪心算法在本题中更为高效，但动态规划的思路可以应用于更复杂的区间覆盖问题。

### 推荐题目
1. [P1209 [USACO1.3]修理牛棚 Barn Repair](https://www.luogu.com.cn/problem/P1209)
2. [P1233 木棍加工](https://www.luogu.com.cn/problem/P1233)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

---
处理用时：43.26秒