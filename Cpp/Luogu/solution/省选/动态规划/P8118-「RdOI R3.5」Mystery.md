# 「RdOI R3.5」Mystery

## 题目描述

给出一个长度为 $n$ 的单调不降整数数列 $\{a_i\}$ 和一个整数 $k$。

我们定义两个长度均为 $p$ 的序列 $\{x_i\},\{y_i\}$ 的「差异度」$F(x,y,p)=\sum_{i=1}^p |x_i-y_i|$。

现在对于每个整数 $l \in [1,n]$，你都需要构造一个长度为 $l$ 的序列 $\{b_{l,i}\}$。满足对于任意 $1\le i <l$，$b_{l,i+1}\ge b_{l,i}+k$；且 $F(a_{[1\cdots l]},b_l,l)$ 最小。其中 $a_{[1\cdots l]}$ 表示 $\{a_i\}$ 的长度为 $l$ 的前缀，即 $\{a_1,a_2,\cdots,a_l\}$。注意，$b_{l,i}$ 没必要是整数。


## 说明/提示

### 样例解释

#### 样例 \#1

如下是一种可能的构造方案：

$$
\begin{aligned}
b_1&=\{2\}\\
b_2&=\{2,4\}\\
b_3&=\{1,3,5\}\\
b_4&=\{1,3,5,7\}\\
b_5&=\{0,2,4,6,8\}\\
\end{aligned}
$$

#### 样例 \#2

如下是一种可能的构造方案：

$$
\begin{aligned}
b_1&=\{1\}\\
b_2&=\{0,2\}\\
b_3&=\{0,2,4\}\\
b_4&=\{0,2,4,6\}\\
b_5&=\{-1,1,3,5,7\}\\
b_6&=\{-1,1,3,5,7,9\}\\
\end{aligned}
$$

#### 样例 \#3

同样例 \#2，只不过 $T=1$，你只需要输出 $F(a,b_6,6)=5$ 即可。

### 数据范围及约定

$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|c|c|c|} \hline
\textbf{subtask} & \textbf{分值} & \bm{{n\le}} & \bm{{T=}} & \bm{{k,a_i\le}} & \textbf{subtask 依赖}\cr\hline
1 & 30 & 100 & 0 & 100 & -\cr\hline
2 & 30 & 10^5 & 0 & 10^6 & 1\cr\hline
3 & 40 & 10^6 & 1 & 10^6 & -\cr\hline
\end{array}
$$

对于 $100\%$ 的数据，$1\le n \le 10^6$，$1\le k,a_i\le 10^6$，$T\in\{0,1\}$。

## 样例 #1

### 输入

```
5 2
2 3 4 5 6
0```

### 输出

```
0
1
2
4
6```

## 样例 #2

### 输入

```
6 2
1 1 4 5 6 8
0```

### 输出

```
0
2
2
3
4
5
```

## 样例 #3

### 输入

```
6 2
1 1 4 5 6 8
1```

### 输出

```
5```

## 样例 #4

### 输入

```
20 4
4 6 7 9 19 21 30 32 33 35 49 50 58 67 75 77 78 89 91 91
0```

### 输出

```
0
2
5
10
10
12
12
14
17
22
22
25
25
25
25
27
30
30
32
36```

# 题解

## 作者：KazamaRuri (赞：4)

[灵感来源](https://pjudge.ac/problem/21807)。

考虑将 $a_i \leftarrow a_i - i \cdot d$，这样问题就变成了，每次操作能把 $a_i$ 加减 $1$，求最少操作次数使得 $a$ 单调递增。这是 [slope trick 典题](https://www.luogu.com.cn/problem/CF713C)。

代码如下：


```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#define lb(x) (x&-x)
using namespace std;
using ll =long long;
using pii=pair<int,int>;
const int N=1e6+5;
int n,T; ll d,a[N],ans; priority_queue<ll>q;
int main(){
	scanf("%d%lld",&n,&d),ans=0;
	for(int i=1;i<=n;i++)
		scanf("%lld",a+i),a[i]-=(i-1)*d;
	scanf("%d",&T);
	for(int i=1;i<=n;i++){
		ll x=a[i]; q.push(x);
		if(q.top()>x)
			ans+=q.top()-x,q.push(x),q.pop();
		if(!T) printf("%lld\n",ans);
	}
	if(T) printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：acb437 (赞：3)

# 题解：[P8118 Mystery](https://www.luogu.com.cn/problem/P8118)
## 前言
朋友在 PJudge 上做题时看到了这道题的原题（或者这是那道题的原题？）并让我看一看，当时我的第一反应就是：这题绝对是贪心。思考良久，他却告诉我这道题有更加优雅的解法，而且这个 trick 我们都见过，它就是：Slope Trick。
## 前置知识：Slope Trick
### 介绍
这个 trick 是一种用来维护函数的方法，简单来说，它一般包括存储分段一次凸 / 凹函数最左边或最右边一段的函数**和**用数据结构（一般是堆）来维护分段一次凸 / 凹函数的分段点：如果一个分段点 $x$ 右侧的一次函数的斜率比左侧的一次函数的斜率多 / 少 $k$（在这个 trick 中，我们要求 $k$ 是整数），就在堆中插入 $k$ 个 $x$。

举例而言，对于一个分段一次凸函数 $F(x)$：

$$
F(x)=\left\{
\begin{array}{rcl}
    2x & x < 0\\
    0 & 0\le x\le 9\\
    -4x + 36 & 9 < x
\end{array} \right.
$$

我们用向堆中插入 $2$ 个 $0$ 和 $4$ 个 $9$，表示斜率在 $0$ 的位置变小了 $2$，在 $9$ 的位置变小了 $4$。

乍一看似乎没有什么作用，它的能力其实建立在分段一次凸 / 凹函数的优秀性质上（以下全部用**凸函数**，**凹函数**具有同样或类似的性质）:

- 两个凸函数相加还是凸函数，并且对于分段一次凸函数而言，它们的和的函数的分段点集合为两个函数分段点集合的并集，即设分段一次函数 $F(i)$ 和 $G(i)$ 的分段点集合分别为 $S_F$ 和 $S_G$，则它们的和 $H(i)$ 的分段点集合 $S_H$ 为 $S_F \cup S_G$。
- 凸函数加一次函数还是凸函数。

这样我们就可以发现 Slope Trick 的一些作用了，比如说，它维护的正是分段一次函数的分段点，而且这么维护斜率的变化对于分段一次凸函数之间的相加十分方便。所以被它用来维护的函数一般有一下要求：

- 是连续的。
- 是分段一次函数。
- 是凸函数或凹函数。
### 操作
- 相加：直接把最左边的一次函数相加，分段点集合合并。
- 函数最值：用大根堆维护斜率为 $0$ 的段左侧的分段点，即斜率为正数（凹函数为负数）时的分段点，用小根堆维护右侧的分段点，即斜率为负数（凹函数为正数）时的分段点。所以大根堆中元素个数为最左边一段一次函数的斜率的绝对值，并且如果一个凸函数最左边的一次函数斜率不为正，那大根堆就是空的，小根堆以及凹函数的情况同理。如果一个点 $a$ 的左侧斜率为 $x(x>0)$，右侧斜率为 $-y(y>0)$，那么大根堆存储 $x$ 个 $a$，小根堆存储 $y$ 个 $a$ 即可，凹函数同理。

更多的操作可以参考 @[CCComfy](https://www.cnblogs.com/cccomfy) 大佬的 [这篇博客](https://www.cnblogs.com/cccomfy/p/17743031.html)，有了这两条操作，我们已经可以做这道题（以及许多 Slope Trick 的题）了。
## 思路简述
这道题其实和 Slope Trick 的[一道经典题](https://www.luogu.com.cn/problem/CF13C)（不算本题就有 5 倍经验）十分类似，我们将每个 $a_i$ 变为 $a_i - i\times k$，就把这道题转化为了这道经典题：给定一个序列 $a$，你可以对序列中任意一个数执行 $+1$ 或 $-1$ 操作，使得序列 $a$ 变为单调不降的，问最少需要几次操作。

接下来分析这道经典题的做法：

考虑 dp，设 $dp_{i,j}$ 表示枚举到第 $i$ 位，将 $a_i$ 变为 $j$ 并且前 $i$ 位单调不降的最小操作次数，则有转移方程 $dp_{i,j}=\min_{k\le j}dp_{i-1,k}+\lvert a_i-j\rvert$，显然可以进行前缀和优化，令 $dp_{i,j}=\min(dp_{i,j-1},dp_{i-1,j}+\lvert a_i-j\rvert)$ 即可。

由于取了前缀 $\min$，dp 方程显然为一个凹函数，设 $F(x)$ 为 $dp_i$，$G(x)$ 为 $dp_{i-1}$，绝对值函数 $H(x)=\lvert a_i-x\rvert$，则 $F(x)=G(x)+H(x)$，$H(x)$ 和 $G(x)$ 都是凹函数，$F(x)$ 也为凹函数，由于维护前缀 $\min$ 即可，我们只需要用大根堆维护斜率为 $0$ 的段左边斜率为负数的分段一次函数即可，不需要维护最左侧一次函数的 $k$ 和 $b$ 以及右侧的函数。加上 $H(x)$ 就相当于在大根堆中插入 $2$ 个 $a_i$（$H(x)$ 的斜率从 $-1$ 变为 $1$，函数相加直接合并分段点集合）。

插入之后，由于 $H(x)$ 开头的斜率为 $-1$，大根堆中的元素只会增加 $1$ 个，于是需要弹出堆顶，因为此时的堆顶位置右侧的函数斜率已经变为了 $1$，而不是 $0$。贡献如何计算需要分类讨论，设原本（插入前）大根堆的堆顶为 $t$，即 $x$ 取到 $t$ 时，$G(x)$ 最小，则有：

1. $a_i\ge t$ 时，显然贡献可以直接取 $H(a_i)=0$ 这个值，不需要增加答案，在 $a_i$ 这个点右侧的函数斜率变为 $1$，于是只需要保留 $1$ 个 $a_i$。
2. $a_i<t$ 时，设 $t$ 左侧的第一个分段点为 $p$（插入后），那么对于 $p\le y\le t$，$F(y)$ 的值相等，即 $F(x)$ 函数的这一段斜率为 $0$，所以 $F(x)$ 的最小值既是 $dp_{i-1,p}+\lvert a_i-p\rvert$，也是 $dp_{i-1,t} + \rvert a_i-t\rvert$，由于我们先前维护的是 $G(x)$ 的最小值，即 $dp_{i-1,t}$，所以我们需要加上的贡献为 $\lvert a_i-t\rvert$，但是这个值（指 $F(x)$ 的最小值）的意义是 $dp_{i,p}$ 的意义，即 $a_i$ 变为 $p$ 而不是变为 $t$。

## 代码
```cpp
#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
const int N = 1e6 + 5;
typedef long long ll;
int n, k, t;ll ans, a[N];
priority_queue <ll> heap;

int main()
{
    scanf("%d%d", &n, &k);
    for(int i = 1;i <= n;i++)scanf("%lld", &a[i]), a[i] -= 1ll * i * k;
    scanf("%d", &t);
    for(int i = 1;i <= n;i++)
    {
        heap.push(a[i]);
        if(a[i] < heap.top())
            ans += heap.top() - a[i], heap.pop(), heap.push(a[i]);
        if(!t)printf("%lld\n", ans);
    }
    if(t)printf("%lld\n", ans);
    return 0;
}
```
---
鸣谢：[CCComfy 大佬的 Slope Trick 详解](https://www.cnblogs.com/cccomfy/p/17743031.html)。

---

## 作者：绝顶我为峰 (赞：2)

先来点弱智问题：$n=1$ 咋做。

直接 $a_1=b_1$，没了。

---

再来点弱智问题：$n=2$ 咋做。

考虑还是 $a_1=b_1$，$a_2-b_1\geq k$ 就 $a_2=b_2$，否则 $b_2=b_1+k$，容易证明这是最优解之一。


---

那么来点不那么弱智的问题：$n=3$ 咋做。

考虑从 $n=2$ 的地方拓展过来，现在我们已经构造好了前两个数，考虑加入一个新的数。$a_3-b_2\geq k$ 的情况是平凡的，不多赘述，对于 $a_3-b_2\geq k$ 的部分，我们先令 $b_3=b_2+k$ 然后分类讨论：

- $a_2-b_1<k$

  这个时候三个数是互相依赖的，因为 $b_2>a_2,b_3>a_3,b_1=a_1$，所以如果我们将 $b$ 的值整体减少 $1$，那么 $b_2,b_3$ 答案变小 $1$，$b_1$ 答案变大 $1$，答案变优，如此可以一直平移到 $a_2=b_2$ 或 $a_3=b_3$ 时停止。
  
- $a_2-b_1\geq k$

  和 $n=2$ 一样。
  
---

推广到 $n$ 的做法，我们已经有了一个贪心的思路：维护连续的一段互相依赖的数字最优方案中所有数字最小的构造，因为这样可以让后面一个数尽可能靠近 $a$。

考虑怎么维护，用一个堆来维护所有 $b_i>a_i$ 的位置 $b_i-a_i$ 的值，并且统计当前一段里面 $b_i>a_i$ 和  $b_i\leq a_i$ 的位置个数。

新加入一个数，如果 $a_i-b_{i-1}>k$，我们直接新开一段即可；否则如果当前段内 $b_i>a_i$ 的数个数如果**不少于** $b_i\leq a_i$ 的数个数，那么我们向下整体平移答案不会变劣，于是平移到段内新出现一个 $a_i=b_i$ 为止。这个距离是可以直接在堆里查出来的，然后弹出堆顶元素，并给整个堆打上这么多的减标记。

但是其实还有一种情况没有考虑到：除了第一段，别的段是不能无限制向下平移的，因为到某个位置这一段的段首会和上一段段位相差刚好 $k$，两端会相连变成一段。

这启示我们使用可并堆，存一下相邻两端之间的差和前面段的信息，每次平移的时候判断一下两端是否相连，如果相连就整个段向下平移到两端刚好相连的位置，然后合并两个段即可。

时间复杂度 $O(n\log n)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
#define int long long
int t,n,m,a[2000001],ans,ch[2000001][2],val[2000001],tag[2000001],root[2000001],dis[2000001],tot,low,high,lst,cnt;
vector<pair<int,int> > v;
vector<int> gap,num;
inline int read()
{
    int x=0;
    char c=getchar();
    while(c<'0'||c>'9')
        c=getchar();
    while(c>='0'&&c<='9')
    {
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x;
}
inline void print(int x)
{
    if(x>=10)
        print(x/10);
    putchar(x%10+'0');
}
inline int newnode(int w)
{
    val[++tot]=w;
    return tot;
}
inline void push_down(int x)
{
    if(tag[x])
    {
        if(ch[x][0])
        {
            val[ch[x][0]]-=tag[x];
            tag[ch[x][0]]+=tag[x];
        }
        if(ch[x][1])
        {
            val[ch[x][1]]-=tag[x];
            tag[ch[x][1]]+=tag[x];
        }
        tag[x]=0;
    }
}
inline int merge(int x,int y)
{
    if(!x||!y)
        return x|y;
    if(val[x]>val[y])
        x^=y^=x^=y;
    push_down(x);
    ch[x][1]=merge(ch[x][1],y);
    if(dis[ch[x][0]]<dis[ch[x][1]])
        ch[x][0]^=ch[x][1]^=ch[x][0]^=ch[x][1];
    dis[x]=dis[ch[x][1]]+1;
    return x;
}
inline int pop(int x)
{
    push_down(x);
    return merge(ch[x][0],ch[x][1]);
}
signed main()
{
    n=read(),m=read();
    for(int i=1;i<=n;++i)
        a[i]=read();
    t=read();
    if(t==0)
    {
        print(0);
        putchar('\n');
    }
    low=1;
    lst=a[1];
    for(int i=2;i<=n;++i)
    {
        if(a[i]-lst>=m)
        {
            v.push_back({low,high});
            gap.emplace_back(a[i]-lst-m);
            num.emplace_back(cnt++);
            low=1;
            high=0;
            lst=a[i];
        }
        else
        {
            ++high;
            lst+=m;
            ans+=lst-a[i];
            root[cnt]=merge(root[cnt],newnode(lst-a[i]));
            while(high>=low)
            {
                if(gap.empty())
                {
                    lst-=val[root[cnt]];
                    if(root[cnt])
                    {
                        tag[root[cnt]]+=val[root[cnt]];
                        root[cnt]=pop(root[cnt]);
                    }
                    --high;
                    ++low;
                    continue;
                }
                if(val[root[cnt]]<=gap.back())
                {
                    lst-=val[root[cnt]];
                    if(root[cnt])
                    {
                        gap.back()-=val[root[cnt]];
                        tag[root[cnt]]+=val[root[cnt]];
                        root[cnt]=pop(root[cnt]);
                    }
                    --high;
                    ++low;
                    continue;
                }
                lst-=gap.back();
                if(root[cnt])
                {
                    tag[root[cnt]]+=gap.back();
                    val[root[cnt]]-=gap.back();
                    root[cnt]=merge(root[cnt],root[num.back()]);
                }
                low+=v.back().first;
                high+=v.back().second;
                gap.pop_back();
                num.pop_back();
                v.pop_back();
            }
        }
        if(t==0)
        {
            print(ans);
            putchar('\n');
        }
    }
    if(t==1)
    {
        print(ans);
        putchar('\n');
    }
    return 0;
}
```

---

## 作者：MoYuFang (赞：1)

说句闲话，这题跟动态规划有什么关系？

本题解线段树 $O(n\log n)$。

首先手玩样例，将 $a_i$ 从左到右一个一个地插入，在这个过程中动态维护使得答案最小的序列 $b_i$。

手玩前两个样例后可以发现 $b$ 序列会分成若干个段，每个段里的 $b_i$ 一定是一个以 $k$ 为公差的等差数列，原因可以从下面的例子看出。

比如当 $k=2$ 时，对于下面的 $a$ 序列

```
a: 1 1 4 5 9 10 11 16 17 18 19
```

 我们可以构造出这样的一个 $b$ 序列使得差异值最小

```
b: -1 1 3 5 | 8 10 12 | 15 17 19 21
```

其中 ```|``` 将不同的段分了开来。

现在我们在 $a$ 序列的末尾加入数字 ```20```，$a$ 序列变成

```
a: 1 1 4 5 | 9 10 11 | 16 17 18 19 20
```

因为 $21+k=23>20$，我们让 $b$ 序列的下一个数尽可能的小，也就是 ```23```。

```
b: -1 1 3 5 | 8 10 12 | 15 17 19 21 23
```

但是差异值不再是最小的了，我们需要对 $b$ 序列作一些改动使得差异值减小。

对比一下 $a$ 序列的最后一段和 $b$ 序列的最后一段。

```
a: 16 17 18 19 20
b: 15 17 19 21 23
```

因为 $b$ 序列中的每一段一定是一个以 $k$ 为公差的等差数列，若想修改一段中的数字必然使这一段整体加或减一个相同的数值，对段的修改必然是整体加减。

考虑到最后一段中，若整体减的话会有 $2$ 个数字 ```15 17``` 会使得差异值增大，会有 $3$ 个数字 ```19 21 23``` 会使差异值减小。

我们称使差异值增大的数为**升数**，使差异值减小的数为**降数**，显然升数和降数的个数决定了整体减是否会使差异值减小。

最后一段中，升数的个数小于降数的个数，所以我们应该使最后一段整体减以使差异值减小，那么要减多少合适呢？

显然减到降数个数小于等于升数个数时最为合适，在这里我们需要整体减 $1$，使得 $b$ 序列的最后一段变成

```
b: 14 16 18 20 22
```

于是新的 $a$ 序列和 $b$ 序列就是

```
a: 1 1 4 5 | 9 10 11 | 16 17 18 19 20
b: -1 1 3 5 | 8 10 12 | 14 16 18 20 22
```

然后我们再在 $a$ 中加入一个数字 ```21```，注意到 ```b``` 中的升数个数大于等于降数个数，不需要整体减，所以两个序列变为

```
a: 1 1 4 5 | 9 10 11 | 16 17 18 19 20 21
b: -1 1 3 5 | 8 10 12 | 14 16 18 20 22 24
```

再在 $a$ 中加入一个数字 ```22```，这时候 ```b``` 中的降数个数大于升数个数，所以需要对 $b$ 序列中的最后一段进行整体减。

```
a: 1 1 4 5 | 9 10 11 | 16 17 18 19 20 21 22
b: -1 1 3 5 | 8 10 12 | 13 15 17 19 21 23 25
```

但是这样有问题，注意到 $b$ 序列中第 $2$ 段末尾的数字 ```12``` 和第 $3$ 段开头的数字 ```13``` 差距小于 $k$，这样的 $b$ 序列是非法的。

于是我们将 $b$ 序列倒退回整体减之前的状态，也就是

```
b: -1 1 3 5 | 8 10 12 | 14 16 18 20 22 24 26
```

发现第 $2$ 段和 $3$ 段之间已经是一个等差数列了，应该将两段合并。

```
b: -1 1 3 5 | 8 10 12 14 16 18 20 22 24 26
```

再与 $a$ 序列对比一下。

```
a: 1 1 4 5 | 9 10 11 16 17 18 19 20 21 22
```

升数有 ```8 10 14 16 18```，降数有 ```12 20 22 24 26```，降数与升数数量一致，不需要再整体减了。

再在 $a$ 中加入数字 ```40```，因为 $b$ 序列中最后一个数字加 $k$ 后的值 $26+2=28<40$，所以可以让 $b$ 的下一个数字为 $40$，这样就需要新开一个段。

```
b: -1 1 3 5 | 8 10 12 14 16 18 20 22 24 26 | 40
```

通过上面的例子可以发现我们需要为 $b$ 序列的每个段维护降数和升数的个数，以及最快能减少成升数的降数是哪一个，同时每个段是一个公差为 $k$ 的等差数列，故需要为每个段维护等差数列的初值。

于是我们设计如下的结构体来维护 $b$ 序列中不同的段。

```cpp
#define ll long long
struct Section{
    int l, r; //这个段对应的区间为[l,r]
    ll 	base, //等差数列的初值
    	max_down; //这个段再整体减少多少就需要与上一个段合并(第一个段认为是正无穷)
    ll get_lst(){ return base + (ll)(r-l)*k; } //返回等差数列的末值
};
```

用线段树来维护每个区间内的降数个数、每个降数再减少多少就会变成升数、最快减少成升数的降数是哪一个。

```cpp
struct Seg{
    int cnt, //降数个数
    	pos; //最快减少成升数的降数在 b 序列中的位置
    ll	tmi, //pos 上的数再减少多少就会变成升数
    	tag; //区间加标记，用来完成整体减的操作
} seg[maxn<<2]
```

然后我们在给 $a$ 序列不断添加数字的过程中动态维护 $b$ 序列以及答案即可。



完整代码加注释。

```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <iostream>
#include <assert.h>
using namespace std;

#define re register
#define sf scanf
#define pf printf
#define nl() putchar('\n')
#define ms(x, val) memset(x, val, sizeof(x))
#define ll long long
#define db double
#define ull unsigned long long
#define _for(i, a, b) for(re int i = (a); i < (b); ++i)
#define _rfor(i, a, b) for(re int i = (a); i <= (b); ++i)
#define _fev(p, u) for(re int p = head[u]; p; p = nex[p])
#define inf 0x7fffffffffffffffll
#define maxn 1000005
#define maxnn (10*maxn)

int rdnt(){
	re int x = 0, sign = 1;
	re char c = getchar();
	while (c < '0' || c > '9') { if (c == '-') sign = -1; c = getchar(); }
	while (c >= '0' && c <= '9') x = (x<<3) + (x<<1) + (c ^ 48), c = getchar();
	return x * sign;
}

template<class T> 
inline void umx(T &x, const T &y){ if (y > x) x = y; }
template<class T>
inline void umi(T &x, const T &y){ if (y < x) x = y; }

int rg; //线段树的值域
struct Seg{ int pos, cnt; ll tag, tmi; } seg[maxnn];
#define tmi(x) seg[x].tmi
#define pos(x) seg[x].pos
#define cnt(x) seg[x].cnt
#define tag(x) seg[x].tag
#define lx (x<<1)
#define rx (x<<1|1) 

//push up 操作
void ud(re int x){
	tmi(x) = min(tmi(lx), tmi(rx));
	pos(x) = tmi(lx) == tmi(x) ? pos(lx) : pos(rx);
	cnt(x) = cnt(lx) + cnt(rx);
}

void build(int x, int tl, int tr){
	tag(x) = 0;
	if (tl == tr){ cnt(x) = tag(x) = pos(x) = 0; tmi(x) = inf; return; }
	int mi = (tl+tr)>>1;
	build(lx, tl, mi);
	build(rx, mi+1, tr);
	ud(x);
}

//对线段树上的一个节点进行区间减操作
void spread(re int x, re ll vl){
	if (tmi(x) < inf){
		tmi(x) -= vl;
		tag(x) += vl;
		assert(tmi(x) >= 0);
	}
}

//push down 操作
void pd(re int x){
	spread(lx, tag(x));
	spread(rx, tag(x));
	tag(x) = 0;
}

//在位置 p 上插入一个降数，这个降数再减少 vl 就会变成升数
void addn(int x, ll vl, int p, int tl, int tr){
	if (tl == tr){ tmi(x) = vl; pos(x) = p; cnt(x) = 1; tag(x) = 0; return; }
	if (tag(x)) pd(x);
	int mi = (tl+tr)>>1;
	if (p <= mi) addn(lx, vl, p, tl, mi);
	else addn(rx, vl, p, mi+1, tr);
	ud(x);
}

//将位置 p 上的降数修改为升数
void deln(int x, int p, int tl, int tr){
	assert(x);
	if (tl == tr){
		assert(tmi(x)==0);
		tmi(x) = inf; pos(x) = cnt(x) = tag(x) = 0;
		return;
	}
	if (tag(x)) pd(x);
	int mi = (tl+tr)>>1;
	if (p <= mi) deln(lx, p, tl, mi);
	else deln(rx, p, mi+1, tr);
	ud(x); 
}

//区间减操作
void mdf(int x, ll vl, int l, int r, int tl, int tr){
	if (l == tl && r == tr){ spread(x, vl); return; }
	if (tag(x)) pd(x);
	int mi = (tl+tr)>>1;
	if (r <= mi) mdf(lx, vl, l, r, tl, mi);
	else if (l > mi) mdf(rx, vl, l, r, mi+1, tr);
	else mdf(lx, vl, l, mi, tl, mi), mdf(rx, vl, mi+1, r, mi+1, tr);
	ud(x);
}

//查询一个区间内降数的个数 c, 最快减少成升数的降数的位置 p, p 位置上的降数减少多少后会变成升数 vl
struct Par{ int p, c; ll vl; };
Par qry(int x, int l, int r, int tl, int tr){
	if (tl == l && tr == r){ return {pos(x), cnt(x), tmi(x)}; }
	if (tag(x)) pd(x);
	int mi = (tl+tr)>>1;
	if (r <= mi) return qry(lx, l, r, tl, mi);
	else if (l > mi) return qry(rx, l, r, mi+1, tr);
	else{
		Par p1 = qry(lx, l, mi, tl, mi), p2 = qry(rx, mi+1, r, mi+1, tr);
		return p1.vl <= p2.vl ? Par({p1.p, p1.c+p2.c, p1.vl}) : Par({p2.p, p1.c+p2.c, p2.vl});
	}
}

int k,
	top = 0, //段的数目, 也就是栈顶
	a[maxn]; //a 序列
ll ans = 0; //答案
struct Section{
	int l, r;
	ll updown, base;
	ll get_lst(){ return base+(ll)(r-l)*k; }
} stk[maxn]; //栈

//对一个段进行整体减 vl
//同时 p 代表那个最新变为升数的降数的位置
//c 是这一段中的降数个数减去升数个数
void decrease(Section &sec, re int c, re int p, re ll vl){
	ans -= (ll)c*vl;
	mdf(1, vl, sec.l, sec.r, 1, rg);
	if (vl == 0) assert(p != -1);
	if (p != -1) deln(1, p, 1, rg);
	sec.base -= vl;
	if (sec.updown < inf){
		assert(sec.updown >= vl);
		sec.updown -= vl;
	}
}

//尝试将最后一段整体减少
//这样一定至少使一个降数变为一个升数
//若成功使得至少一个降数变为升数则返回 true
//否则返回 false
bool maintain(){
	Section &sec = stk[top];
	
	Par par = qry(1, sec.l, sec.r, 1, rg);
	re int c = par.c*2-(sec.r-sec.l+1); //降数个数减去升数个数 
	if (c < 0) return false;
	
	re int p = par.p; re ll vl = par.vl;
	assert(vl < inf && p > 0);
	
	if (sec.updown == inf || vl < sec.updown){//还没减少完
		decrease(sec, c, p, vl);
	} 
	else{ //减少完了，要与上一段合并了
		decrease(sec, c, vl==sec.updown?p:-1, sec.updown);
		assert(sec.updown == 0);
		assert(top > 1);
		Section &pre_sec = stk[top-1];
		assert(pre_sec.get_lst()+k == sec.base);
		pre_sec.r = sec.r;
		--top;
	}
	return true;
}

signed main(){
	#ifndef ONLINE_JUDGE
	freopen("sample.in", "r", stdin);
	//freopen("sample.out", "w", stdout);
	#endif
	
	seg[0] = {0, 0, 0, inf};
	
	re int n = rg = rdnt(), T; k = rdnt(); ans = top = 0;
	_rfor(i, 1, n) a[i] = rdnt(); T = rdnt();
	build(1, 1, n);
	
	_rfor(i, 1, n){
		if (i == 1){
			Section &sec = stk[++top];
			sec.l = sec.r = 1; sec.updown = inf; sec.base = a[i];
		}
		else{
			re ll curb = stk[top].get_lst()+k;
			if (curb >= a[i]){
				ans += curb-a[i];
				++stk[top].r;
				addn(1, curb-a[i], i, 1, rg);
				while(maintain());
			}
			else{
				Section &sec = stk[++top];
				sec.l = sec.r = i; sec.updown = a[i]-curb; sec.base = a[i];
			}
		}
		if (T == 0 || i == n) pf("%lld\n", ans);
	}

	return 0;
}
```















---

## 作者：haochengw920 (赞：0)

贪心（模费）分析对我来说还是太玄学了，这里给出一个比较机械，而且通用性比较强的方法。

```
能不动脑子做题就不要动脑子——信息学真谛。
```

说句闲话：这题是 [P4331 [BalticOI 2004] Sequence 数字序列](https://www.luogu.com.cn/problem/P4331) 的严格加强版，但是这题是蓝题，那题是紫题…

## Part 1

先令 $a_i=a_i-i \times k$ ，问题转换成 $\{b\}$ 不降。

仿照 P4331，令 $dp_{i,j}$ 表示填到第 $i$ 个 $b$ ，且 $b_i$ 等于 $j$ 的最小代价。

容易发现 $dp_i$ 的图像是一个左右对称、单谷的折线，考虑用堆维护这个折线左半部分。

具体来讲，堆中的元素为拐点的下标，表示从这里开始折线的斜率比前面一段大一，并且最后一个拐点之后斜率为 $0$ （由于我们维护的是谷的一半）。

每次 $i$ 增加时， $a_i$ 位置会增加两点斜率，并且会使最右边一段斜率为 $0$ 的线变为 $1$ 。

于是我们每次插入两次 $a_i$ ，弹出最大的值，并令 $b_i$ 为栈顶即当前位置为止最优的策略。

## Part 2

于是我们将所求转换成了 $\sum_{i=1}^m\lvert \min_{j=i}^mb_j - a_i\rvert\ \forall m\in[1,n]$ 。

发现 $\min_{j=i}^mb_j$ 的取值一定是一段段值，并且段之间的值单增，经思考可知这个值即为 $\{b\}$ 所产生的单调递增栈。

考虑维护这个栈，并在弹栈入栈时动态维护答案的值，如下：

```cpp
rep(i, 1, n) {
    while (tp && b[stc[tp]] > b[i]) {
        rep(j, stc[tp - 1] + 1, stc[tp]) 
            ans -= abs(b[stc[tp]] - a[j]);
        -- tp;
    } stc[++ tp] = i; 
    rep(j, stc[tp - 1] + 1, i) ans += abs(b[i] - a[j]);
    if ((i ^ n) && tpy) continue; 
    printf ("%lld\n", ans);
}
```

但是只要生成一个第一个值极小、后面的值单减的 $\{a\}$ 即可卡成 $O(n^2)$ 。

瓶颈在于维护一个值 $x$ 在区间内的答案贡献，用数据结构维护，转换成值域内的和和值域内的数字数。

这是一个二维的问题，可以用树套数或主席树维护，但是发现空间开不下（也许可以卡过，但是我习惯 `#define int long long` ）。

怎么办？树套树降空间的通用套路：二次离线 + cdq。

本人对二次离线 + cdq 不是很熟练，由于这只是个二维问题，于是选择了二次离线 + 树状数组。

```cpp
#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
#define int long long
#define rep(i, l, r) for(int i(l); i <= (r); ++ i) 
#define per(i, r, l) for(int i(r); i >= (l); -- i) 
using namespace std;

const int N = 1000005;

int n, K, tpy;
int a[N], b[N];

int m, d[N]; // a
vector<int>num;
void Dscrt() {
	rep(i, 1, n) 
		num.emplace_back(a[i]);
	sort(num.begin(), num.end());
	num.erase(unique(num.begin(), num.end()), num.end()); 
	m = num.size(); rep(i, 1, n) 
		d[i] = lower_bound(num.begin(), num.end(), a[i]) - num.begin() + 1; 
}
int ans[N];
struct Opt{
	int p, x, fg; // 1~r 答案加入p 正负性为fg 
	inline Opt(const int &_p, const int &_x, const int &_fg) : p(_p), x(_x), fg(_fg) {} 
}; vector<Opt>vec[N]; // 插入 vec[r] 中 
struct BIT {
	private : 
	int tr[N];
	inline int lowbit(int x) {
		return (x & (-x));
	}
	int query(int p) {
		int res = 0;
		for (; p; p -= lowbit(p)) 
			res += tr[p];
		return res;
	}
	public : 
	void add(int p, int x) {
		for (; p <= m; p += lowbit(p)) 
			tr[p] += x;
	}
	int query(int bg, int nd) {
		return query(nd) - query(bg - 1);
	}
}ct, sum;
void Solve() {
	Dscrt(); 
	rep(i, 1, n) {
		ct.add(d[i], 1);
		sum.add(d[i], a[i]);
		for (Opt& u : vec[i]) {
			int tl = lower_bound(num.begin(), num.end(), u.x) - num.begin();
			int tr = upper_bound(num.begin(), num.end(), u.x) - num.begin() + 1;
			ans[u.p] += u.fg * (ct.query(1, tl) * u.x - sum.query(1, tl));
			ans[u.p] += u.fg * (sum.query(tr, m) - ct.query(tr, m) * u.x);
		}
	} rep(i, 1, n) {
		ans[i] += ans[i - 1];
		if ((i ^ n) && tpy) continue;
		printf ("%lld\n", ans[i]);
	}
}

int tp, stc[N];
void Prew() {
	priority_queue<int>hp;
	rep(i, 1, n) {
		hp.push(a[i]); hp.push(a[i]);
		hp.pop(); b[i] = hp.top(); 
	} rep(i, 1, n) {
		while (tp && b[stc[tp]] > b[i]) {
			vec[stc[tp]].emplace_back(i, b[stc[tp]], -1);
			vec[stc[tp - 1]].emplace_back(i, b[stc[tp]], 1);
			-- tp;
		} stc[++ tp] = i; 
		vec[i].emplace_back(i, b[i], 1); 
		vec[stc[tp - 1]].emplace_back(i, b[i], -1);
	} 
}

signed main()
{
	scanf ("%lld%lld", &n, &K);
	rep(i, 1, n) scanf ("%lld", a + i), a[i] -= i * K;
	scanf ("%lld", &tpy); Prew(); Solve();
	return 0;
}
```

---

