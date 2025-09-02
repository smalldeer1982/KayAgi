# [ARC072E] Alice in linear land

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc072/tasks/arc072_c

Aliceは数直線の上に住んでいます。今日はある不思議な乗り物に乗って目的地まで行くことを考えました。 はじめ、Aliceは目的地から $ D $ 離れたところにいます。Aliceが乗り物にある数 $ x $ を入力すると、現在地から目的地に向かって $ x $ 進んだところが現在地より目的地に近いとき移動し、そうでないときは動きません。現在地から目的地までの距離が $ x $ 未満のとき、$ x $ 進んだところは目的地を通りすぎていることに注意してください。また、目的地を通り過ぎると進行方向が変わること、進行方向は何度も変わることがあることに注意してください。

Aliceは乗り物に $ N $ 回だけ数を入力し、$ i $ 番目に入力する数は $ d_i $ の予定でした。Aliceは入力する予定数の書かれたリストを作っておき、その数を $ 1 $ つずつ入力します。

しかしイタズラ好きの魔法使いが現れ、Aliceが $ N $ 回の入力による移動を終えても目的地にたどり着かないよう、リストの数を $ 1 $ つだけ書き換えることを考えました。

魔法使いはイタズラの実行のため以下の $ Q $ 個の計画を考えています。

- $ q_i $ 回目に入力する数のみをある正整数に変更することで、Aliceが目的地にたどり着かないようにする

$ Q $ 個の計画それぞれが実行可能であるか答えるプログラムを書いてください。

## 说明/提示

### 制約

- $ 1≦\ N\ ≦\ 5*10^5 $
- $ 1≦\ Q\ ≦\ 5*10^5 $
- $ 1≦\ D\ ≦\ 10^9 $
- $ 1≦\ d_i\ ≦\ 10^9(1≦i≦N) $
- $ 1≦\ q_i\ ≦\ N(1≦i≦Q) $
- $ d_i,\ D $は整数である

### Sample Explanation 1

$ 3 $ 番目までの入力でAliceはすでに目的地にたどり着いているため、$ 1 $ 番目の計画の答えは`NO`です。 例えば、$ 3 $ 番目の入力を $ 5 $ にすると、Aliceは以下のような移動をし、目的地にたどり着くことはできないため、$ 2 $ 番目の計画の答えは`YES`です。 !\[\](https://atcoder.jp/img/arc072/f6a4307ef86847bc8fa68d0952f7127c.png)

### Sample Explanation 2

もともと入力する予定のままでもAliceは目的地にたどり着けないため、すべての計画は実行可能です。

## 样例 #1

### 输入

```
4 10
3 4 3 3
2
4 3```

### 输出

```
NO
YES```

## 样例 #2

### 输入

```
5 9
4 4 2 3 2
5
1 4 2 3 5```

### 输出

```
YES
YES
YES
YES
YES```

## 样例 #3

### 输入

```
6 15
4 3 5 4 2 1
6
1 2 3 4 5 6```

### 输出

```
NO
NO
YES
NO
NO
YES```

# 题解

## 作者：zjw806903 (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc072_c)

## 0.前言
模拟赛里面考到了......当时想的优先队列维护，不出意外的死了......
[参考了这位 dalao 的题解](https://www.luogu.com.cn/article/rr6bnsi6)
## 1.暴力
相信所有人看到这道题，都能想到一个显然的 DP。

状态表示：$dp[i][j]$ 表示后 $i$ 项能否在 $d=j$ 的情况下走到终点。$1$ 表示可以，反之不行。


转移方程式如下：

$dp[i][j]=dp[i+1][j-d[i]]$ （当 $d[i] \le j$ 时）

原因：当用后 $i+1$ 种操作能在 $j-d[i]$ 的情况下走到终点时，此时先走 $d[i]$ 再走 $j-d[i]$ 即可完成 $d=j$ 的情况。需要注意必须 $d[i] \le j$，不然就走过了。

$dp[i][j]=dp[i+1][d[i]-j]$（当 $j < d[i] \le 2 \times j$ 时）

原因：当用后 $i+1$ 种操作能在 $d[i]-j$ 的情况下走到终点时，此时先走 $d[i]$，越过终点。此时到达离终点 $d[i]-j$ 的位置。再往回走 $d[i]-j$ 即可完成即可完成 $d=j$ 的情况。需要注意必须 $j < d[i] \le 2 \times j$，不然就走不过或者大于了原距离。

$dp[i][j]=dp[i+1][j]$（当 $2 \times j < d[i]$ 时）

原因：显然如果走了 $d[i]$ 的距离会比原距离还要大，所以不走，只能让后 $i+1$ 种操作走 $j$ 的距离。

对于询问，不难发现如果询问第 $i$ 个位置对 $i$ 以前的位置走到的位置是无关的。对于对 $i$ 及以后的位置，由于 $i$ 可以随便改，所以只要离终点的距离是在前 $i$ 个位置离终点的位置以内的距离，都是可以的。（如果大于不会移动），此时我们设前 $i$ 个位置离终点的距离为 $x$，那么只有 $i+1$ 及以后的位置可以处理 $j \in 0 \sim x$ 的所有情况，才输出 `NO`。

显然，这是一个 $O(nD)$ 的做法，尝试优化。
## 2.优化
观察到，我们仅需找到 $dp[i+1][j\in 0 \sim x]$ 中是否存在 $0$ 即可。观察到 $dp[i+1]$ 中 $j$ 是越小越容易影响答案的（因为查询范围最小都是 $0$），所以我们希望仅维护 $dp[i]$ 表示 $dp[i][j]$ 中最小的 $j$。我们来尝试表示一下状态转移方程式。

$dp[i]=dp[i+1]$（当 $d[i] \ge 2 \times dp[j+1]$ 时，对应第三个方程式）

$dp[i]=d[i]-dp[i+1]$（当 $d[i] > 2 \times dp[j+1]$ 时，对应第二个方程式）

$dp[i]=dp[i+1]+d[i]$（当 $d[i] \le dp[i+1]+d[i]$ 时，由于这显然成立，所以等于无条件，对应第一个方程式）

核心逻辑：$dp[i]=dp[i][minj]=$ 转移所用 $j$。

根据上述三个式子转移即可。

对于询问，只需判断 $dp[i]$ 与 $x$ 的大小关系即可。
## 3.代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,d,a[500005],pl,q,uo,pre[500005],dp[500005],now;
bool can[500005]; 
int main(){
	scanf("%d%d",&n,&d);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		if(abs(now-d)>abs(now+a[i]-d)){
			now+=a[i];
		}
		if(abs(now-d)>abs(now-a[i]-d)){
			now-=a[i];
		}
		pre[i]=abs(now-d);//计算x 
	}
	pre[0]=d;
	dp[n+1]=1;
	for(int i=n;i>=1;i--){
		if(a[i]>=2*dp[i+1]){
			dp[i]=dp[i+1];//方程1 
			if(a[i]>2*dp[i+1]){
				dp[i]=min(dp[i],a[i]-dp[i+1]);//方程2
			}
		}
		else{
			dp[i]=dp[i+1]+a[i];//方程3，因为明显方程1优于方程3，所以放在else里 
		}
	}
	scanf("%d",&q);
	can[n+1]=0;
	for(int i=1;i<=q;i++){
		scanf("%d",&uo);
		if(dp[uo+1]<=pre[uo-1]){//判断 
			printf("YES\n");
		}
		else{
			printf("NO\n");
		}
	}
	return 0;
}
//6
```

---

## 作者：chenxia25 (赞：5)

顺着算。显然任意时刻，你与终点的距离是唯一需要关心的。首先容易想到的是，对询问 $i$，显式地求出 $1\sim i-1$ 作用后的距离 $v$。然后经过 $i$ 的作用显然可能变成任意 $0\sim v$。那么该问是 NO 当且仅当，$0\sim v$ 所有数经过 $i+1\sim n$ 的作用之后都是 $0$。

我们考虑研究，对于一个初始的距离，经过若干作用变成的距离关于初始距离的函数。如果 $i+1\sim n$ 对应的函数的 $0\sim v$ 的值都是 $0$ 的话，就 NO。

但是这个函数太难研究或者维护了。后来我又想研究该函数的前缀最大值，看 $v$ 处是不是 $0$。但是这个前缀最大值函数依然难以研究。

接下来就是我想不到的部分了。注意到 $0$ 这玩意很特殊，没有值比它更小了，我们大可不必研究更强的问题（研究函数本身），只需要管它的最长 $0$ 前缀即可。这是一个值（而不是一整个函数），直接从后往前推的时候记录一下，看看能否递推。设上一秒的最前不为 $0$ 的地方是 $g$。恰巧，感性理解可以得到这个函数无论经过多少次作用都是连续的（即 $|f(x)-f(x+1)|\leq 1$），所以一定有 $f(g)=1$。然后我们要求出经过新加进来这个作用先作用之后，得到的值在 $f$ 上映射到不为 $0$ 的最前面的值。脑子想象一下过程，一开始在 $0\sim g-1$ 里面步长最多为 $1$ 地瞎走，想要逃出去，必定先经过 $g$。于是新的 $g$ 就是使得 $\min(x,|x-d|)=g$ 的最小 $x$（牛逼吧），讨论一下即可。

这个问题告诉我们：要解决一个问题的时候，我们经常会情不自禁地研究比它更强的看起来更普遍的问题，而恰恰忽略了原问题的特殊性。利用好原问题的特殊性往往能使问题变得更简单，就像这题一样迎刃而解了。

---

## 作者：fade_away (赞：3)

# [ARC072C]Alice in linear land
[~~If you want 更差的观看体验~~](https://blog.csdn.net/xmr_pursue_dreams/article/details/111823897)
## Description
给定$a_1...a_n$和$D$，$m$轮询问，每轮询问给你一个$q$，可以让你任意修改$a_q$的值，然后从小到大对于每一个$i$让$D=min(D,D-a_i)$，问最后是否能让$D=0$，询问两两独立。

$n,m\leq 5*10^5$
## Solution
若能修改的是第$x$个数，显然$a_1...a_{x-1}$操作完之后的$D$与修改成什么无关，可以直接预处理出$a_1...a_k$操作后$D$的值$d_k$。

然后对于$a_x...a_n$，若存在一个数$y\leq d_{x-1}$，且$y$在$a_x...a_n$操作后不为$0$，则答案为$YES$，否则为$NO$。

---

因此现在相当于要求出一个最小的$y_x$，使得$y_x$在$a_x...a_n$操作之后不为$0$。我们设$y_{x+1}$为$a_x+1...a_n$操作后不为$0$的最小的$y$，考虑如何用$y_{x+1}$求出$y_x$。

- 当$y_{x+1}\leq \frac{a_x}{2}$时，显然$y_x=y_{x+1}$。
- 当$y_{x+1}> \frac{a_x}{2}$时，显然$y_x=y_{x+1}+a_x$。

> 那么这样做会不会存在一个$y'_x<y_x$也满足条件呢？

>可以发现这是不可能的，因为按照定义$y'_{x}$一定由$y'_{x+1}\geq y_{x+1}$转移过来。
> - 当$y'_{x+1}\leq \frac{a_x}{2}$时，$y'_x=y'_{x+1},y_x=y_{x+1},y_x\leq y'_x$。
> - 当$y'_{x+1}> \frac{a_x}{2}$时，$y'_x=y'_{x+1}+a_x$，此时$y_x$要么为$y_{x+1}$，要么为$y_{x+1}+a_x$，显然$y_x\leq y'_x$。

因此可证得，我们从后往前递推得到得必然为最小满足条件的$y$，于是预处理出所有后缀的$y$，即可$O(1)$回答询问。

时间复杂度$O(n+m)$。
## Code
```cpp
int a[MAXN],b[MAXN],mn[MAXN];
signed main()
{
	int n=read(),D=read(); b[0]=D,mn[n+1]=1;
	for (int i=1;i<=n;i++) a[i]=read(),b[i]=min(b[i-1],abs(b[i-1]-a[i]));
	for (int i=n;i>=1;i--) mn[i]=(mn[i+1]<=a[i]/2?mn[i+1]:mn[i+1]+a[i]);
	int m=read();
	for (int i=1;i<=m;i++)
	{
		int x=read();
		puts(b[x-1]>=mn[x+1]?"YES":"NO");
	}
	return 0;
}
```


---

## 作者：asuldb (赞：2)

[题目](https://www.luogu.org/problem/AT2401)

瑟瑟发抖，这竟然只是个蓝题

题意大概就是初始在$0$，要到坐标为$D$的地方去，有$n$条指令，第$i$条为$d_i$。当收到一条指令$x$后，如果向$D$方向走$x$后距离$D$更近，那么就走；否则就停留在原地。

现在有$Q$次询问，第$i$次询问为$q_i$，问能不能仅改变$d_{q_i}$，使得其不能到达$D$点

考虑一个暴力，设$g_{i,j}$表示当$D=j$时，只使用后$i$次操作能否到达$j$点

考虑如何求出$g_{i,j}$

转移大概长这样

$$
g_{i,j}=\left\{\begin{matrix}
g_{i+1,j-d_i} & d_i\leq j\\ 
g_{i+1,d_i-j} & j<d_i<2j\\ 
 g_{i+1,j}&d_i\geq 2j 
\end{matrix}\right.
$$

就是当$d_i\leq j$的时候，只能到达距离目标$j-d_i$的地方

当$j<d_i<2j$，我们会走过$j$点，到达距离目标$d_i-j$的地方，这个时候翻转一下正方向即可

当$d_i>2j$的时候，显然走过去的点距离目标更远，于是直接不走

我们再处理出一个数组$pos_i$表示第$i$次操作后距离$D$点的距离

当遇到一个询问$q_i$的时候，如果我们要改变$d_{q_i}$，那么可能我们只能改变为$0$到$2\times pos_{i-1}$的数，只有这些才是有效移动

进行有效移动后距离目标点的距离也只可能从$pos_{i-1}$到$0$，所以只需要$g_{q_i+1,0}$到$g_{q_i+1,pos_{i-1}}$里有一个是$0$，那么我们就可以走这个距离，之后就不可能走到目标点了

这样复杂度是$O(nD)$的，显然过不了

考虑一下如何不求$g$数组，而直接高效询问

**发现我们一次询问只关注$g_{q_i+1}$的前$pos_{i-1}$项有没有一个$0$，显然一个靠前的$0$能影响更多的询问**

所以我们如果知道使得$g_{i,j}=0$最小的$j$在哪里，也能快速回答询问

设$dp_i$表示使得$g_{i,j}=0$最小的$j$，考虑求出$dp$数组

根据上面$g$数组的转移，尝试反推$dp$数组的转移

当$d_i\geq 2\times dp_{i+1}$时，$dp_{i}=dp_{i+1}$。这对应了上面的第三个转移

当$dp_{i+1}=d_i-j$，即$dp_{i}=d_i-dp_{i+1}$时，需要满足$d_i-dp_{i+1}<d_i<2(d_i-dp_{i+1})$，即$d_i>2\times dp_{i+1}$时。这对应了第二个转移。

当$dp_{i+1}=j-d_i$，即$dp_i=dp_{i+1}+d_i$时，需要满足$d_i\leq dp_{i+1}+d_i$，这显然成立。这对应了上面第三个转移。

根据条件取上面三个转移的最小值即可，回答询问的时候只需要判断一下$dp_{q_i+1}$和$pos_{q_{i-1}}$的大小关系即可

代码

```cpp
#include<bits/stdc++.h>
#define re register
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
inline int read() {
	char c=getchar();int x=0;while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+c-48,c=getchar();return x;
}
const int maxn=5e5+5;
int d[maxn],dp[maxn],pos[maxn];
int n,D,Q;
inline int ABS(int x) {return x>=0?x:-x;}
int main() {
	n=read();D=read();dp[n+1]=1;
	for(re int i=1;i<=n;i++) d[i]=read();
	for(re int i=n;i;--i) {
		if(d[i]>=2*dp[i+1]) {
			dp[i]=dp[i+1];
			if(d[i]>2*dp[i+1]) dp[i]=min(dp[i],d[i]-dp[i+1]);
		}
		else dp[i]=dp[i+1]+d[i];
	} 
	pos[0]=D;
	for(re int i=1;i<=n;i++) pos[i]=min(ABS(pos[i-1]-d[i]),pos[i-1]);
	Q=read();int x;
	while(Q--) x=read(),puts(dp[x+1]<=pos[x-1]?"YES":"NO");	
	return 0;
}

```


---

## 作者：Kinandra (赞：2)

标签: DP

为了更方便描述, 将机器人的初始位置视为 $D$ , 将原点视为终点.

#### Part 1 

定义: $f_{i,j}$ 表示以 $j$ 为起点, 依次进行 $[i,n]$ 的操作是否可以到达终点(取 $0$ 时表示不可到达), $p_i$ 表示以 $D$ 为起点, 依次进行 $[1,i]$ 的操作机器人停留的位置.

那么对于一个询问的 $q$ , 存在修改方案使得机器人不能走到终点当且仅当 $\exists j\leqslant p_{q-1}, f_{q+1,j}=0$ .  这个式子的意义是我们先依次进行 $[1,q-1]$ 的操作到达 $p_{q-1}$ , 然后通过修改 $d_q$ 使得进行 $q$ 操作后机器人移动到某个**进行之后的操作不能到达终点的**位置 $j\leqslant p_{q-1}$(机器人不会远离终点).

$p_i$ 很容易求得, 考虑 $f_{i,j}$ 的求法: 按 $i$ 从大到小转移, 容易得到如下递推式:

$f_{i,j}=\left\{\begin{aligned} &f_{i+1,j}, &j\leqslant \frac{d_i}{2}\\
&f_{i+1,d-j},&\frac{d_i}{2}<j\leqslant d_i \\
&f_{i+1,j-d},&j\geqslant d_i\end{aligned}\right.$

这样我们就得到了一个 $\mathcal O(nD)$ 的算法, 不够优秀, 需要优化.

#### Part 2

发现只要 $f_{q+1}$ 中位置最小的 $0$ 的位置小于 $p_{q-1}$ 就可以使方案无解了, 于是我们尝试维护 $f$ 中位置最小的 $0$ 的位置. 经过一些推导, 发现这个确实可以维护.

重新定义 $f$: $f_i$ 表示依次进行 $[i,n]$ 的操作, 最小的不能到达终点的位置.

转移也很好推:

$f_i=\left\{\begin{aligned}&f_{i+1},&f_{i+1}\leqslant \frac{d_i}{2}\\
&f_{i+1}+d_i,&f_{i+1}>\frac{d_i}{2}\end{aligned}\right.$

**Done** :)

时间复杂度 $\mathcal O(n+m)$.

``` cpp
#include <bits/stdc++.h>
using namespace std;
int read();
int n, m, D;
int d[500005], f[500005], res[500005];
int main() {
    n = read(), D = read();
    for (int i = 1; i <= n; ++i) d[i] = read();
    f[n + 1] = 1;
    for (int i = n; i >= 1; --i)
        f[i] = (f[i + 1] <= d[i] / 2) ? f[i + 1] : f[i + 1] + d[i];
    for (int i = 1; i <= n; ++i)
        res[i] = f[i + 1] <= D, D = min(D, abs(D - d[i]));
    m = read();
    while (m--) puts(res[read()] ? "YES" : "NO");
    return 0;
}

int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
```



---

## 作者：Zi_Gao (赞：0)

## 题意

有一个数轴，终点为原点。一个机器人位于 $D$，有 $n$ 条指令，对第 $i$ 条指令机器人会向终点移动 $d_i$ 距离，若移动后距离变大则不移动，意思是可能冲过，但是若距离变小就可以过去。

给出 $m$ 个询问，第 $i$ 次询问允许将 $d_{q_i}$ 修改为任意整数（仅当前询问生效）。问是否存在修改方案使机器人不能走到终点。

## 题解

记 $dis_i$ 表示不修改前 $i$ 个操作情况下，当前能走动哪。那么对于一次可以修改 $d_x$ 的询问，若存在一个 $y\leq d_{x-1}$ 使得 $y$ 在经过 $i+1$ 到 $n$ 的操作后没到 $0$ 则有解，否则无解。所以考虑求出最小使得走完后面操作不为 $0$ 的距离，记 $mn_i$ 表示最小走完 $i$ 到 $n$ 的操作之后不为 $0$ 的距离，倒着 dp 即可：

1. 当 $mn_{i+1}\leq\frac{d_i}{2}$，有 $mn_i=mn_{i+1}$。因为这种情况肯定会直接冲过，但是冲过 $d_i-mn_{i+1}\geq mn{i+1}$ 故不会这样走，这样 $mn_i$ 取到了下限。
2. 当 $mn_{i+1}\gt\frac{d_i}{2}$，有 $mn_i=mn_{i+1}+d_i$。分类讨论一下，若这一步是冲过的，那么 $m_i=d_i-mn_{i+1}\lt mn_{i+1}$ 所以不可能；若没动，那么 $mn_i=mn_{i+1}$ 这时候若直接冲过 $d_i-mn_{i+1}\lt mn_{i+1}$ 不可能，或者直接走过去 $mn_{i+1}-d_{i+1}\lt mn_{i+1}$ 所以也不可能；所以只能是直接走过去的情况。

```cpp
#include<bits/stdc++.h>
// #define ONLINE_JUDGE
#define INPUT_DATA_TYPE int
#define OUTPUT_DATA_TYPE int
inline __attribute((always_inline)) INPUT_DATA_TYPE read(){register INPUT_DATA_TYPE x=0;register char f=0,c=getchar();while(c<'0'||'9'<c)f=(c=='-'),c=getchar();while('0'<=c&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();return f?-x:x;}void print(OUTPUT_DATA_TYPE x){if(x<0)x=-x,putchar('-');if(x>9)print(x/10);putchar(x%10^48);return;}

int mnD[500010],dis[500010],d[500010];

int abss(int x){return x<0?-x:x;}

int main(){
	#ifndef ONLINE_JUDGE
	freopen("name.in", "r", stdin);
	freopen("name.out", "w", stdout);
	#endif

    register int i;
    int n=read();
    dis[0]=read();
    for(i=1;i<=n;++i){
        d[i]=read();
        dis[i]=std::min(abss(dis[i-1]-d[i]),dis[i-1]);
    }
    mnD[n+1]=1;
    for(i=n;i;--i){
        if(d[i]/2>=mnD[i+1]) mnD[i]=mnD[i+1];
        else mnD[i]=mnD[i+1]+d[i];
    }

    int q=read();
    while(q--){
        i=read();
        puts(dis[i-1]>=mnD[i+1]?"YES":"NO");
    }

	#ifndef ONLINE_JUDGE
	fclose(stdin);
	fclose(stdout);
	#endif
    return 0;
}
```

---

## 作者：xuantianhao (赞：0)

# [[ARC072E] Alice in linear land](https://www.luogu.com.cn/problem/AT_arc072_c)

首先，一个 trivial 的想法是记 $f_i$ 表示第 $i$ 步前离终点的距离，于是 $f_i=\min\Big(f_{j-1},|f_{j-1}-d_i|\Big)$。

然后，我们设 $f_i'$ 表示在修改第 $i$ 步后，此时离终点的距离。明显，$f_i'$ 可以为任意不大于 $f_i$ 的值，因为此时的 $d_i'$ 可以任意取值。

于是问题转换为是否存在一个 $f_i'$，满足按照剩余的操作后缀执行后不会到达 0（可以把它看作是在自动姬上按照一堆指令执行后不会到达 0 状态）。

因为 $f_i'$ 有其上界，所以我们只需知道要使当前后缀不为 0 ，所需的最小 $f_i'$，然后将其与 $f_i$ 比较即可。考虑设 $g_i$ 表示若不执行操作 $i$，然后再执行其剩余操作后，使得终止位置不在 0 的最小 $f_i'$。则最终只需比较 $f_{i-1}$ 与 $g_i$ 即可。

考虑倒着转移 $g$。这个只需要分类讨论，处理 $d_i\leq g_i,d_i\geq 2g_i,g_i<d_i<2g_i$ 三种情形即可。

时间复杂度 $O(n)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N=5e5+100;
int n,m,x;
int d[N],f[N];
inline int read(){
    char c=getchar();int f=1,x=0;
    while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
LL g[N];
int main(){
    n=read();
    f[0]=read();
    for(int i=1;i<=n;i++){
		d[i]=read();
		f[i]=min(f[i-1],abs(f[i-1]-d[i]));
	}
    g[n]=1;
    for(int i=n;i;i--){
        if(d[i]<=g[i]) g[i-1]=g[i]+d[i];
        else if(d[i]>=2*g[i]) g[i-1]=g[i];
        else g[i-1]=g[i]+d[i];
    }
//  for(int i=0;i<=n;i++) printf("%d ",f[i]);
//	printf("\n");
//  for(int i=0;i<=n;i++) printf("%d ",g[i]);
//	printf("\n");
    m=read();
	while(m--){
		x=read();
		if(f[x-1]>=g[x]) printf("YES\n");
		else printf("NO\n");
	}
    return 0;
}
```


---

