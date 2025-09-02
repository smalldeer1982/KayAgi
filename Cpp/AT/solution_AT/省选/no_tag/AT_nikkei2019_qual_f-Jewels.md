# Jewels

## 题目描述

你有 $n$ 个物品，每个物品有一个颜色 $c_i (1 ≤ c_i ≤ K)$ 和权值 $v_i$。你需要选出 $x$ 个物品，满足若颜色 $i$ 的物品被选中，那么颜色 $i$ 至少存在两个物品被选中，并且最大化总权值和。你需要对 $x = 1\dots n$ 均求出答案。如果无解，则输出 $-1$ 。

## 说明/提示

对于所有数据， $1 ≤ n ≤ 2 \times 10^5, 1 ≤ K ≤\frac n 2,1\le c_i\le K, 0 \le v_i \le 10^9$   ,保证对于每种出现在了输入中的颜色，至少存在 $2$ 个该颜色的物品。

## 样例 #1

### 输入

```
5 2
1 1
1 2
1 3
2 4
2 5```

### 输出

```
-1
9
6
14
15```

## 样例 #2

### 输入

```
5 2
1 1
1 2
2 3
2 4
2 5```

### 输出

```
-1
9
12
12
15```

## 样例 #3

### 输入

```
8 4
3 2
2 3
4 5
1 7
3 11
4 13
1 17
2 19```

### 输出

```
-1
24
-1
46
-1
64
-1
77```

## 样例 #4

### 输入

```
15 5
3 87
1 25
1 27
3 58
2 85
5 19
5 39
1 58
3 12
4 13
5 54
4 100
2 33
5 13
2 55```

### 输出

```
-1
145
173
285
318
398
431
491
524
576
609
634
653
666
678```

# 题解

## 作者：critnos (赞：14)

我们有理由相信，答案数组 $\bmod\ 6$ 相同的位置取出来均是凸的。于是写一个分治闵可夫斯基和，发现过了，很感动。

[提交记录](https://atcoder.jp/contests/nikkei2019-qual/submissions/59776553)

时间复杂度 $O(n\log n)$。

---

## 作者：EuphoricStar (赞：4)

学长讲的做法。

考虑将每种颜色的价值最大值和次大值取平均数，这样做显然不影响答案，并且好处是贪心时按双关键字排序只用考虑一种颜色当前只有一种物品的情况。

之后把所有物品扔进优先队列，每次从优先队列中取价值最大的物品。如果当前物品是第一次出现，就稍作调整即可。

具体而言，考虑有哪些决策。

- 可以不取当前这个物品，取还在队列里面且它的颜色之前已经出现超过两次的物品。取价值最大的即可。

- 如果要取当前物品，可以把之前拿过的相应颜色出现次数大于 $2$ 的物品扔掉，再拿当前颜色的最大和次大。

- 也可以把前面只出现两次的物品扔掉，再往后面拿三个同色的（颜色前面没出现过），参考样例 $1$。

维护两个 `multiset` 即可，具体见 [代码](https://atcoder.jp/contests/nikkei2019-qual/submissions/37784504)。

---

## 作者：csyakuoi (赞：2)

首先 $x=1,2,3$ 的情况很容易处理，然后如果 $x=3$ 无解，那么 $x$ 为任意奇数时均无解，特判即可。

然后考虑每次将 $x$ 变为 $x+2$ 后答案以及具体取的宝石如何变化，再分 $x$ 为奇数偶数两类分别求解。

每种颜色的宝石内部按价值从大到小排序，那么可以将颜色分为目前没有取的和取了至少两颗的两类。

加入两个宝石有以下 $4$ 种情况：

$(1).$加入两颗宝石（颜色可以相同），两种颜色的宝石都至少取了两颗。

$(2).$加入一对颜色相同的宝石。

$(3).$删除一颗宝石，加入三颗颜色相同的宝石。

$(4).$删除一对颜色相同的宝石，加入三颗颜色相同的宝石，再加入另一颗宝石。

开 $5$ 个堆维护剩余能直接加入的宝石、一对/三个颜色相同的宝石、已经加入的单个/一对宝石。

其本质是带反悔贪心。

---

## 作者：Acoipp (赞：1)

题解中有一次考虑增加两个的解法，这里提供一个一次只考虑增加一个的解法。

首先，$i=1$ 一定是 $-1$ 可以特判，我们从 $i=2$ 开始考虑，下面是可能会出现的情况（证明可以用贪心）：

- 选一个单个的可以被加入的。
- 删除一个单个的，加入某种颜色权值前二大的。
- 删除某种颜色权值前二大的，加入某种颜色权值前三大的。
- 删除某种颜色权值前三大的，加入两种颜色权值前二大的。

最后，如果一次加一个不行，那么需要特判只能一次加两个的情况，这个并不困难。

于是开 $6$ 个堆分别维护：单个的是否被加入的，两个的是否被加入的，三个的是否被加入的即可。

时间复杂度为 $O(n \log n)$，空间复杂度为 $O(n)$。

代码如下，仅供参考：

[HERE](https://atcoder.jp/contests/nikkei2019-qual/submissions/60030286)

---

## 作者：Zi_Gao (赞：0)

设 $A_x$ 表示容量 $x$ 时的答案，分类讨论一下可以发现，从 $A_x$ 转移到 $A_{x+1}$，最多会增加 $4$ 个，减少 $3$ 个。所以合并两个背包 $A,B$ 到 $B$，若 $C_i$ 的最优转移点是 $A_j+B_{i-j}$，那么 $C_{i+1}$ 的最优转移点一定在 $[j-4,j+4]$ 范围内。所以单次合并复杂度 $\mathcal{O}(|A|+|B|)$，所以按照哈夫曼树合并，最终复杂度 $\mathcal{O}(n\log n)$。

应该是对的，拍了 2000 多组。

```cpp
#include<bits/stdc++.h>

#define INPUT_TYPE int
#define OUTPUT_TYPE long long

inline __attribute((always_inline)) INPUT_TYPE read(){
    register INPUT_TYPE x=0;register char c=getchar(),f=0;
    while(c<'0'||'9'<c) f=(c=='-'),c=getchar();
    while('0'<=c&&c<='9') x=x*10+(c&15),c=getchar();
    return f?-x:x;
}

void print(OUTPUT_TYPE x){
    if(x<0) putchar('-'),x=-x;
    if(x>=10) print(x/10),x%=10;
    putchar(x|'0');
}

const long long INF=0x3f3f3f3f3f3f3f3f;

int a,b;
std::vector<long long> pol[200010],pnow;
std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int> >,std::greater<std::pair<int,int> > > Q;

int main(){
    register int i,j,lat,c,v,now;
    int n=read();
    int m=read();
    for(i=1;i<=n;++i){
        c=read();v=read();
        pol[c].push_back(v);
    }

    for(c=1;c<=m;++c)if(pol[c].size()){
        std::sort(pol[c].begin(),pol[c].end(),[](int a,int b){return a>b;});
        for(i=1;i<pol[c].size();++i) pol[c][i]+=pol[c][i-1];
        pol[c].insert(pol[c].begin(),0);
        pol[c][1]=-INF;
        Q.push(std::make_pair((int)pol[c].size(),c));
    }

    while(Q.size()>1){
        a=Q.top().second,Q.pop();
        b=Q.top().second,Q.pop();
        pnow.clear();
        pnow.resize(pol[a].size()+pol[b].size()-1,-INF);

        lat=0;
        for(i=0;i<pnow.size();++i)if(i!=1){
            for(j=lat-4;j<=lat+4;++j){
                if(j==1||j<0||j>=pol[a].size()||i-j==1||i-j<0||i-j>=pol[b].size()) continue;
                if(pnow[i]<pol[a][j]+pol[b][i-j]){
                    pnow[i]=pol[a][j]+pol[b][i-j];
                    now=j;
                }
            }
            lat=now;
        }
        pol[a].swap(pnow);
        Q.push({pol[a].size(),a});
    }

    c=Q.top().second;
    for(i=1;i<=n;++i) print((pol[c][i]<=-INF/2)?-1:pol[c][i]),putchar('\n');

    // fprintf(stderr,"%lf",1.0*clock()/CLOCKS_PER_SEC);

    return 0;
}
```

---

