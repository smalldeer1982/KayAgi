# [USACO22DEC] Circular Barn S

## 题目描述

Farmer John 和他的死对头 Farmer Nhoj 在一个环形牛棚内玩游戏。牛棚内有 $N(1 \le N \le 10^5)$ 个房间，第 $i$ 个房间初始时内有 $a_i$ 头奶牛 $(1 \le a_i \le 5 \times 10^6)$。游戏玩法如下：

- 两位农夫将总是在同一个房间里。进入一个房间后，每位农夫各执行一次行动，Farmer John 在先。两位农夫在游戏开始时进入房间 $1$。
- 如果当前房间中的奶牛数量为零，则此时执行行动的农夫即失败。否则，执行行动的农夫选择一个整数 $P$，其中 $P$ 为 $1$ 或一个不超过当前房间中奶牛的数量的质数，并从当前房间中移除 $P$ 头奶牛。
- 两位农夫均完成行动之后，两位农夫移动到环形牛棚的下一间房间。也就是说，如果农夫们在房间 $i$，那么他们会移动到房间 $i+1$，除非他们在房间 $N$，在这种情况下他们会移动到房间 $1$。

当两位农夫均采用最优策略时，求获胜的农夫。 

## 说明/提示

### 样例 1 解释

对于第一个子测试用例，Farmer John 可以从第一个房间中移除 $1$、$2$ 或 $3$ 头奶牛。无论他移除多少头奶牛，Nhoj 都可以移除剩余的奶牛，迫使 FJ 在他们绕回第一个房间时失败。

对于第二个子测试用例，FJ 可以移除 $5$ 头奶牛，迫使 Nhoj 面对剩下的 $4$ 头奶牛。现在，Nhoj 可以移除 $1$、$2$ 或 $3$ 奶牛。现在的情况类似于第一个子测试用例。

对于第三个和第四个子测试用例，FJ 可以立即移除第一个房间的所有奶牛，使 Nhoj 失败。

对于第五个子测试用例，FJ 可以从第一个房间中移除 $1$
、$2$ 或 $3$ 奶牛，然后 Nhoj 可以随后移除余下的奶牛。当他们绕回第一个房间时，FJ 将会失败。 

### 测试点性质

- 测试点 $2-4$ 满足 $N=1$。
- 测试点 $1,2,5-7$ 满足 $a_i \le 1000$。
- 测试点 $8-20$ 没有额外限制。

## 样例 #1

### 输入

```
5
1
4
1
9
2
2 3
2
7 10
3
4 9 4```

### 输出

```
Farmer Nhoj
Farmer John
Farmer John
Farmer John
Farmer Nhoj```

# 题解

## 作者：Timmy_ (赞：18)

# 前言

这次 USACO 考的非常不错，拿到了 0 分的高分。

~~死磕 T1 三小时最后发现没开 long long 。~~

~~T2 博弈论完全看不懂。~~

~~T3 压根没看。~~

赛后才发现 T2 的推明白公式代码难度一点没有。

不说了，上题解。

# 思路

## 相关

此题是[巴什博弈](https://baike.baidu.com/item/%E5%B7%B4%E4%BB%80%E5%8D%9A%E5%BC%88/1819345?fr=aladdin)的变种。（不过没了解也没关系，本身内容也不难，可以不学）

## 规律
之后我们再来看这道题，简单的来讲就是解决这么一个问题。

**两个人拿石子，每次只能拿质数个或者一个，谁拿到最后一个谁就赢了，问谁有必胜策略，最少需要几步**。

经过利用人脑计算完小数据后，我们得出来一个规律，**任何是四的倍数的石子数总会是后手先赢，否则是先手赢**。

## 证明
### 证明输赢
接下来我们就要想怎么来证明我们找出的规律了。

如果我们想让后手赢，那么石子的数量一定是 $4k$ 的形式。

还有一点我们可以确定，如果石子数为 $4$ ，后手一定赢。（手动推出来的）

对于先手，只能拿质数个或者一个，而拿的数量一定不可能是 $4k$ 的形式。

那么，先手拿完了之后，石子的数量也只可能为 $4k+1,4k+2,4k+3$ 这三种形式。

如果剩下的数是质数，后手直接拿完，否则把石子的数量变为 $4k$ 的形式。（拿一个，拿两个或者拿三个）

持续这样的过程直到只剩下 $4$ 。

由于 $4$ 我们可以通过手动证明，所以后手必赢。

------------

那么如何证明 $4k+1,4k+2,4k+3$ 的形式下先手必赢呢，同理。

先手可以先把石子的数量变为 $4k$ 的形式，这样自己就可以变为后手，然后拥有必胜策略。（拿一个，拿两个或者拿三个）

### 证明步数

对于后手必胜的情况，先手一定想让步数下的越多越好，那么先手就会选择每次只拿2个，由于后手想让棋子的数量变为 $4k$ 的形式，所以后手必须拿4k+2个，而只有 $k=0$ 的情况下 $4k+2$ 是质数，所以后手每次也只能拿两个。

那么很快我们就可以得出证明，**当石子是 $4k$ 的形式下，在 $x/4+1$ 轮时后手赢**。（ $x$ 为石子数量，一轮是指先手后手都拿一次）

------------

而先手必赢的情况，就稍微有点复杂了，先手想先减去一个质数，使得石子数量变成 $4k$ 的形式，之后按照后手必赢的情况去做。

当然，如果希望步数越少越好，我们一定也希望那个质数越大越好，所以得出来的公式是**当石子不在 $4k$ 的形式下，在 $(x-p)/4+1$ 轮时先手赢**。

# 过程

说完基本原理之后，我们来说具体代码实现。

我们先打一个表，代表着当石头数为多少时谁获胜，并且用了多少轮。

对于 $4k$ 这种格式，直接套公式。

而对于 $4k+1,4k+2,4k+3$ 这种格式，我们可以通过[欧拉筛](https://blog.csdn.net/qaqwqaqwq/article/details/123587336)分别找出格式为 $4k+1,4k+2,4k+3$ 最大的质数，这样石子数量减完了之后就会变成 $4k$ 的形式，让后套公式。

解决完核心问题了之后，外围的问题我就不多讲了。

# AC CODE
```cpp
#include <iostream>
using namespace std;
const int N=5e6+5;
bool isprime[N];
int prime[N];
int n,cnt;
int s[4];//统计格式为4k+1,4k+2,4k+3的最大质数
int ans[N];
int t;
void euler()//欧拉筛
{
    int i,j;
    isprime[1]=true;
    ans[1]=1;
    s[1]=1;
    for(i=2; i<=N; i++)
    {
        if(!isprime[i])
        {
            prime[++cnt]=i;
            if(i%4!=0)
                s[i%4]=i;//更新最大质数数组
        }
        for(j=1; j<=cnt && i*prime[j]<=N; j++)
        {
            isprime[i*prime[j]]=true;
            if(i%prime[j]==0)
                break;
        }
        if(i%4==0)
            ans[i]=i/4+1;//套公式
        else
            ans[i]=(i-s[i%4])/4+1;//套公式
    }
}
int main()
{
    int i;
    euler();
    cin>>t;
    while(t--)
    {
        cin>>n;
        int minx1=1e9,mark1;
        int minx2=1e9,mark2;
        for(i=1; i<=n; i++)//不多解释了，作者的代码很烂，不一定要学习我的，自己写也行
        {
            int temp;
            cin>>temp;
            if(temp%4==0)
            {
                if(minx2>ans[temp])
                {
                    minx2=ans[temp];
                    mark2=i;
                }
            }
            else
            {
                if(minx1>ans[temp])
                {
                    minx1=ans[temp];
                    mark1=i;
                }
            }
        }
        if(minx1<minx2)
            cout<<"Farmer John"<<endl;
        else if(minx1>minx2)
            cout<<"Farmer Nhoj"<<endl;
        else
        {
            if(mark1<mark2)
                cout<<"Farmer John"<<endl;
            else
                cout<<"Farmer Nhoj"<<endl;
        }
    }
    return 0;
}

```
















---

## 作者：zac2010 (赞：11)

### 前言

这道题用到 **质数筛** 和 **博弈论** 。

不错的博弈论入门题，发篇题解加深印象（此做法为官方同款做法，时间复杂度为 $O(n)$ ）。

这里是 [官方题解](http://usaco.org/current/data/sol_prob2_silver_dec22.html) 。

~~没学过博弈论的蒟蒻在场上懵了。。。而且在洛谷提交的时候还中毒了~~

以此提醒：函数没有返回值千万别不用 void 。

### 题意简化

两个人对决，有 $n$ 个房间，每个房间的值为 $a_i$ ，两人总是在同个房间，且初始在 $1$ 号房间。之后每次操作两人从 Farmer John 开始把这个房间的值各减去一个质数或 $1$ ，然后进入下一个房间（房间 $n$ 的下一个房间是房间 $1$ ），知道某个时刻某个人拿到的数是 $0$ 位置，那个人输了，另一个人赢了，请你输出赢的那个人的名字（ Farmer John 和 Farmer Nhoj 之一）。

### 思路

像这类题目，我们可以先从 $n=1$ 入手。 $n=1$ 的情况很简单，其实就是分类讨论：
1.  $n/4$ 余 $0$ 。这种情况的话 **后手必胜** 。原因是先手能减去的数中除以 $4$ 的余数必定为 $1$ , $2$ , $3$ 之一（因为 $4$ 的倍数不可能是质数，也不是 $1$ ）。
2. $n/4$ 余 $1$ , $2$ 或 $3$ 。这种情况 **先手必胜** 。原因是先手可以减去一个数使得其边为 $4$ 的倍数然后丢给后手（先手可以减去 $1$ ,$2$ ,$3$ 之一），就变成上面一种情况了。

再考虑到 $n>1$ 的情况。考虑对于一个房间，那个赢的人必定想缩短操作次数（原因是对于这个房间可以尽快赢，以防止到后面的房间让输的人翻盘），输的人想使操作次数越多越好（原因是这个房间操作次数多了，结束的时间会拖延，以给后面的房间制造机会），所以我们只要按照双方的策略算出操作次数，取最早结束的那个房间即可。

接下来是怎样快速地算一个房间会操作几次（一人操作算一次）。我们继续分类讨论：
1. $a_i$ 为 $4$ 的倍数。这种情况会操作 $a_i/2$ 次。原因比较简单，先手每次减去 $2$ ，这样的话后手只能减 $2$ ，每人每次减 $2$ 。
2. $a_i$ 不为 $4$ 的倍数。那么先手想尽快结束，所以就是 $(a_i-p)/2+1$ 次操作（ $p$ 是小于等于 $p$ 最大的质数）。

接下来对每个房间的 **操作次数的一半（即回合数）** 取最小值，一样按房间顺序取，然后判断取到的那个房间的操作次数是奇数还是偶数来判定结果。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10,M=5e6;
int T,n,x,cnt,ans,mx[4],v[M+10],vis[M+10],prime[M];
void get_prime(int n){
	vis[1]=1;
	mx[1]=1;
	v[1]=1;
	for(int i=2;i<=n;i++){
		if(!vis[i]){
			prime[++cnt]=i;
			mx[i%4]=i;
		}
		for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
			vis[i*prime[j]]=1;
			if(!(i%prime[j])){
				break;
			}
		}
		v[i]=!(i%4)?i/2:(i-mx[i%4])/2+1;
	}
}
int main(){
	scanf("%d",&T);
	get_prime(M);
	while(T--){
		scanf("%d",&n);
		ans=1e9;
		for(int i=1;i<=n;i++){
			scanf("%d",&x);
			if(v[x]/2<ans/2)
				ans=v[x];
		}
		if(ans&1){
			puts("Farmer John");
		}
		else{
			puts("Farmer Nhoj");
		}
	}
	return 0;
}
```


---

## 作者：Demeanor_Roy (赞：8)

- [原题链接](https://www.luogu.com.cn/problem/P8901)

- 赛时想法，有问题欢迎提出。

------------

首先不难发现每个房间的输赢互不干扰。接着便有第一个结论，对于一个拥有 $x$ 头奶牛的房间来说：$4 \mid x$ 则先手必胜，否则先手必败。此结论打表易得，证明的话考虑数学归纳，读者自证不难。

既然有这一点，那对于一个必胜的房间，玩家当然是想要快点胜利，反之若是必败的房间，则想能拖则拖。据此对于任意一个房间，双方都会有既定的最优策略，换句话说，每个房间赢家胜利所需的轮数是一定的。

而只要对每个房间求出轮数，就可以知道谁先获得胜利了。

接下来考虑如何求这个轮数，用 $f(x)$ 表示 $x$ 初始头奶牛的轮数，若 $4 \mid x$，$f(x)$ 则由最大满足 $x-y$ 为 $1$ 或者为质数的 $f(y)$ 转移而来，反之则由最小的满足 $x-y$ 是质数且 $4 \mid y$ 的 $f(y)$ 转移过来。

当然以上做法已经可以求解了，因为根据质数的稠密性，暴力找复杂度是没有问题的，于是问题解决。

[代码](https://www.luogu.com.cn/paste/bjlkpl36)

---

## 作者：SUNCHAOYI (赞：3)

先考虑 $N = 1$ 的情况。若先手胜，我们称 $a_i$ 为必胜点，否则为必败点。显然 $1,2,3$ 均为必胜点；而 $4 = 1 + 3 = 2 + 2$，无论如何都是后手胜，所以为必败点。如果这时候你不知道如何去分析，可以尝试打出必败点的表（猜测必败点并不多），对于一个 $a_i$ 若无法拆分成质数或 $1$ 与另一个比它小的必败点的形式，那么这个 $a_i$ 便是必败点。

```cpp
//x 为当前需要判断的数 p[1] = p[2] = p[3] = p[5] = p[7] = 1，以此类推
ok = 0;
for (auto i : lose)
	if (p[x - i]) ok = 1;//可以拆分
if (!ok) lose.push_back (i)//说明是必败点
```

通过打表发现必败点都是 $4$ 的倍数。其实这很好理解，由于 $4$ 为最小的必败点，那么对于 $(4,8)$ 的数，都可以通过 $4 + 1,4 + 2,4 + 3$ 来表示，而 $8$ 只能表示成 $4$ 加上一个质数，显然不存在。那么以此类推，可知必败点为 $4k(k \in N^*)$。

现在将问题还原，对于某一格的数，如果是必败点，那么先手会尽量拖延时间，也就是说选择数使其能够经过尽可能多的轮数；否则就会用尽可能少的轮数结束来赢得游戏。现在进行分类讨论：

- $a_i$ 为 $1$ 或质数，显然一轮就能结束；

- $a_i$ 为奇数，从第一个不大于它的质数（或 $1$，下同）开始判断，找到尽可能大的质数符合质数加上必败点的形式；

- $a_i$ 为偶数，无论是必胜还是必败点，每次都只会取 $2$。下面给出证明：
	1. $a_i$ 为必败点，先手会尽量拖延时间，取的数尽可能小，不难发现取 $2$ 会比取 $1$ 优。
	2. $a_i$ 为必胜点，由于必败点为偶数，所以只能取 $2$ 这一个唯一的偶质数。
    
至此，取数的策略已经讲解完毕。所以只要找到若干轮后最先结束的 $a_i$，判断其是必胜点还是必败点即可。代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 5e5 + 5,M = 5e6 + 500;
const int MOD = 1e9 + 7;
inline int read ();
int t,n,ok,times,cnt,a[MAX],vis[M + 5],p[MAX];
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	for (int i = 2;i <= M;++i)
	{
		if (!vis[i]) p[++cnt] = i;
		for (int j = 1;j <= cnt;++j)
		{
			if (i * p[j] > M) break;
			vis[i * p[j]] = 1;
			if (i % p[j] == 0) break;
		}
	}
	p[0] = 1;
	t = read ();
	while (t--)
	{
		n = read ();
		ok = 1;times = INF;
		for (int i = 1;i <= n;++i) a[i] = read ();
		for (int i = 1;i <= n;++i) 
		{
			if (a[i] % 2 == 0 && times > a[i] / 4) ok = (a[i] % 4 != 0),times = a[i] / 4;
			if (a[i] & 1)
			{
				int x = upper_bound (p,p + 1 + cnt,a[i]) - p - 1;
				while (~x)
				{
					if ((a[i] - p[x]) % 4 == 0)
					{
						if (times > (a[i] - p[x]) / 4) ok = 1,times = (a[i] - p[x]) / 4;
						break;
					} 
					--x;
				}
			}
		}
		puts (ok ? "Farmer John" : "Farmer Nhoj");
	}
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
```

---

## 作者：EXODUS (赞：1)


# Part 1：前言
~~打表，打表，打表，猜结论不会的一定要打表。~~

# Part 2：正文

我们对数字先手必胜还是必败似乎没有什么特别直观的认识，~~所以不妨 rush 出一份打表代码。~~

```cpp
int pri[P],cnt=0;
bool chk[N],res[N];
void get_prime(int Up){
	chk[1]=0;pri[++cnt]=1;
	for(int i=2;i<=Up;i++){
		if(!chk[i])pri[++cnt]=i;
		for(int j=2;j<=cnt&&pri[j]*i<=Up;j++){chk[i*pri[j]]=1;if(i%pri[j]==0)break;}
	}
}
void get_res(int Up){
	for(int i=1;i<=Up;i++){
		res[i]=chk[i];
		for(int j=1;j<=cnt;j++){
			if(res[i-pri[j]])res[i]=1;
		}
	}
}
```

然后发现所有 $res_i=0$（先手必败）的 $i$ 构成的集合是 $S=\{i|i=4k,k\in\mathbb{N^+}\}$ ，我们试图证明这一结论。

不妨设当 $t\leq 4k$ 时，对于一个数字 $x\in[1,t]$ 先手必败当且仅当 $4\mid x$

我们可以试证明，对于 $\forall k\in \mathbb{N^+},x\in[1,4k],4\mid x\iff x\in S$

首先令 $k=1$，此时手算 $1,2,3,4$ 显然成立。

不妨令 $k=p$ 时原结果成立，当 $k=p+1$ 时，令 $z$ 是一个质数或 $1$，$y$ 是一个正整数。一个数不会被加入 $S$ 中当且仅当其存在一个后继状态先手必败（属于 $S$）。

$$
\begin{aligned}
&4p+1-z\rightarrow 4y,z=1,y=p\\
&4p+2-z\rightarrow 4y,z=2,y=p\\
&4p+3-z\rightarrow 4y,z=3,y=p\\
&4p+4-z\not\rightarrow 4y
\end{aligned}
$$

因此只有 $4p+4$ 被加入到 $S$ 中，原命题成立。

考虑每个人最优策略是什么，胜者想尽快赢，败者想尽慢失败，因此每个数字会被减去的次数是在胜方尽快，败方尽量慢的前提下做出的步数。

直接考虑比较困难，打表也没有任何规律，我们不妨从特殊下手，即 $x\mid 2$ 的情况。

对于先手必败的数字 $x$，即先手任何转移都会转移到先手必败态，不难想到减 $2$ 疑似是一个最优解，而一个 $4$ 的倍数减 $2$ 会转移到一个模 $4$ 余 $2$ 的数，因此我们不妨先讨论 $2\mid x$ 且 $4\nmid x$，的情况，此时先手一定要转移到一个先手必败态，而除去 $2$ 以外所有质数都是奇数，每个奇数都是先手必败态，因此先手只有一个选择：减少 $2$，所以若 $4\mid x$ 先手如果选择 $2$ 则减去的次数一定为 $\dfrac{x}{2}$，可以证明这是最优解（其实我不会证，但是打表可以发现一个奇数 $x$ 的次数是远远小于偶数 $x+1$ 的）。

对于奇数 $y$ 的情况其实比较麻烦，但是由于必须转移到先手必败态，而 $4\mid x$ 减去的轮数一定为 $\dfrac{x}{4}$，单调不降，所以我们要找到最大的质数 $t$，满足 $y-t$ 是 $4$ 的倍数，等价于找到最小的 $z$，满足 $y-4z$ 是一个质数。打表发现 $y\leq 5\times 10^6$ 时 $z$ 最大是 $153$（好像是，大概在 $[100,200]$ 这个范围内），枚举即可。

令 $\mathbb P$ 是质数集和 $\{1\}$ 的并。

归纳一下，对于一个数字 $x$，我们减去的次数是
$$
\begin{cases}
\dfrac{x}{2},&2\mid x\\
z+1,&2\nmid x,z=\min\limits_{t,x-4t\in \mathbb{P}}t
\end{cases}
$$

**决出胜负的轮数**是
$$
\begin{cases}
\dfrac{x}{4}+1,&4\mid x\\
\lceil\dfrac{x}{4}\rceil,&4\nmid x,2\mid x\\
\frac{z}{4}+1,&2\nmid x,z=\min\limits_{t,x-4t\in \mathbb{P}}t
\end{cases}
$$
对于轮数一样的特判位置。

# Part 3：代码
```cpp
#define np pair<int,int>
#define mp(a,b) make_pair(a,b)
const int N=5e6+7,P=5e6+7;
int pri[P],cnt=0,n;
bool chk[N];
int a[N];
void get_prime(int Up){
	chk[1]=0;pri[++cnt]=1;
	for(int i=2;i<=Up;i++){
		if(!chk[i])pri[++cnt]=i;
		for(int j=2;j<=cnt&&pri[j]*i<=Up;j++){chk[i*pri[j]]=1;if(i%pri[j]==0)break;}
	}
}

int res[N];

void Main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	np tim1=mp(2e9,2e9),tim2=mp(2e9,2e9);
	for(int i=1;i<=n;i++){
		if(a[i]%4==0){
			tim1=min(tim1,mp(a[i]/2/2+1,i));
		}else{
			if(a[i]&1^1)tim2=min(tim2,mp((a[i]/2+1)/2,i));
			else{
				if(res[a[i]])tim2=min(tim2,mp((res[a[i]]+1)/2,i));
				else{
					for(int j=0;j<=a[i];j+=4){
						if(!chk[a[i]-j]){
							res[a[i]]=j/2+1;
							break;
						}
					}
					tim2=min(tim2,mp((res[a[i]]+1)/2,i));
				}
			}
		}
	}
	if(tim1<tim2)puts("Farmer Nhoj");
	else puts("Farmer John");
	return;
}

int main(){
	get_prime(5e6);T=read();
	while(T--)Main();
	return 0;
}
```

---

## 作者：Trafford1894 (赞：1)

看见题目中有质数，必然要先筛出 $[0, 5\times 10^6]$ 范围的全部质数。我为了保险多筛了 $5\times 10^5$。

显然，这是个博弈论问题。所以我们应该考虑每个数是先操作者必胜还是必败，设这个数为 $n$。题目中给出，当 $n$ 为 $1$ 或是质数时，先操作者必胜。当 $n$ 为 $4$ 时，先操作者必败。我们可以尝试先根据题目中的规则打个表。[打表代码](https://www.luogu.com.cn/paste/ubg2jxfo)

我们发现，只有当 $n$ 为 $4$ 的倍数时，先操作者必败。反之，先操作者必胜。这是 $n$ 的胜负性质。

这时，我们要将问题拓展。如果有多个 $n$，这时谁会胜利呢？这就涉及到最优情况的操作数了。

首先对于 $n$ 为 $1$ 或者质数时，只需操作一次。当 $n \equiv 0\pmod 2$ 时，只需操作 $\dfrac{n}{2}$ 次。因为如果 $n \equiv 0 \pmod 4$，此时先操作者必败。如果先操作者再减去一个奇质数，先操作者必然会加速失败。所以，先操作者只能取 $2$，转化为 $n \equiv 2 \pmod 4$ 的情况。这时候的先操作者如果不取 $2$，就转化为奇数情况，会导致另一个人胜利。所以，这时候的先操作者只能取 $2$，如此循环往复。因为每次只能取 $2$，所以总次数必然为 $\dfrac{n}{2}$ 次。

其他情况，$n$ 是个奇数且不是质数，此时的先操作者必胜。因为要考虑最优情况，所以先操作者在保证必胜的情况下要尽量减少操作数。为了保证必胜，取的这个质数要和 $n$ 在模 $4$ 意义下同余。为了尽量减少操作数，取的这个数是比 $n$ 小的质数中最大的一个。记这个要取的数为 $p$，因为取完 $p$ 之后剩下的 $n - p \equiv 0\pmod 4$，根据上面的结论，则操作数为 $1+\dfrac{n-p}{2}$。

还有一个问题，就是如何求出 $p$。可以记录模 $4$ 余 $1$ 和 模 $4$ 余 $3$ 的质数，然后再二分查找即可。

最后，要在先操作者必胜和必败的情况中分别找出操作数最小的。要注意一种情况，就是先操作者必败的情况，后操作者将当前的房间取为 $0$ 时，要等到先操作者重新路过这个房间才会生效。因此，还需记录操作数最小的房间编号。

[参考代码](https://www.luogu.com.cn/paste/qgktgect)

---

## 作者：yemuzhe (赞：0)

#### [题目传送门](/problem/P8901)

### 解题思路

$5 \cdot 10 ^ 6$ 的范围和 $1000$ 的 $T$ 使得我们必须预处理一些信息并用 $\Theta (1)$ 的时间来在线处理每一个房间。

#### Part 1：质数筛

由于数据范围是 $5 \cdot 10 ^ 6$，我们要用线性筛来筛出 $1 \sim 5 \cdot 10 ^ 6$ 的质数。

然后把 $1$ 和所有除以 $4$ 余 $1$ 的质数从小到大储存在一个数组里，再把所有除以 $4$ 余 $3$ 的质数从小到大储存在另一个数组里。（用处后面会讲）

线性筛模板：

```c++
void primes (int m)
{
	for (int i = 2; i <= m; i ++)
	{
		if (!v[i])
		{
			v[i] = i, p[++ cnt] = i;
		}
		for (int j = 1; j <= cnt; j ++)
		{
			if (p[j] > v[i] || i * p[j] > m)
			{
				break;
			}
			v[i * p[j]] = p[j];
		}
	}
	return ;
}
```

#### Part 2：博弈策略

我们考虑只有一个房间的情况。假设这个房间内有 $x$ 头牛。

1. 当 $x \equiv 0 \pmod 4$ 时：（$k$ 为自然数）

   - 若 `FJ` 移除 $4k + 1$ 头奶牛，则 `FN`（`Farmer Nhoj`）可以移除 $3$（或其它模 $4$ 为 $3$ 的质数）头奶牛。

   - 若 `FJ` 移除 $2$ 头奶牛，则 `FN` 可以移除 $2$ 头奶牛。

   - 若 `FJ` 移除 $4k + 3$ 头奶牛，则 `FN` 可以移除 $1$（或其它模 $4$ 为 $1$ 的质数）头奶牛。

   `FN` 的以上策略都可仍使 $x \equiv 0 \pmod 4$。重复以上步骤知道 $x = 0$，`FJ` 将无奶牛可取。因此 `FJ` 必败。

2. 当 $x \not \equiv 0 \pmod 4$ 时：

   - 当 $x \equiv 1 \pmod 4$ 时，`FJ` 可以移除 $1$（或其它模 $4$ 为 $1$ 的质数）头奶牛。

   - 当 $x \equiv 2 \pmod 4$ 时，`FJ` 可以移除 $2$ 头奶牛。

   - 当 $x \equiv 3 \pmod 4$ 时，`FJ` 可以移除 $3$（或其它模 $4$ 为 $3$ 的质数）头奶牛。

   `FJ` 在执行完以上策略后，都会将 $x$ 转化为第一种情况。因此 `FJ` 必胜。

所以，对于一个房间，如果这个房间的奶牛数是 $4$ 的倍数，那么 `FJ` 必败；否则 `FJ` 必胜。

#### Part 3：执行次数

为方便，我们不妨设 $f _ x$ 为一个有 $x$ 头奶牛的房间在第几轮时会被移完奶牛。

很显然，当 $x \equiv 0 \pmod 4$ 时，$f _ x = {x \over 4}$（?）。

当 $x \equiv 2 \pmod 4$ 时，$f _ x = f _ {x - 2} + 1$。

当 $x \equiv 1 \pmod 4$ 时，$f _ x = f _ {x - p} + 1$（其中 $p$ 为不超过 $x$ 的模 $4$ 为 $1$ 的 **最大质数**）。

当 $x \equiv 3 \pmod 4$ 时，$f _ x = f _ {x - q} + 1$（其中 $q$ 为不超过 $x$ 的模 $4$ 为 $3$ 的 **最大质数**）。

> PS：找最大质数的方法，可以用双指针或者 `Cbrx` 的更新法（每次遇到一个质数就更新相应余数的最大质数）。

我们再设 $g _ x$ 为一个有 $x$ 头奶牛的房间在第几轮时定出胜负。那么很显然，$g _ x = \begin {cases} f _ x & [x \not \equiv 0 \pmod 4] \\ f _ x + 1 & [x \equiv 0 \pmod 4] \end {cases}$。

#### Part 4：判定胜负

我们求出最小 $g _ i$ 对应的 $a _ i$（如有多个则选择靠前的那个），判断 $a _ i$ 是否能被 $4$ 整除即可。

### AC Code

```c++
#include <cstdio>
#define N 100005
#define M 5000005
#define P 500005
using namespace std;

int t, n, mn, pos, cnt, cnt1, cnt3, a[N], v[M], p[P], onE[P], threE[P], f[M];

void primes (int m) // 线性筛
{
	onE[++ cnt1] = 1; // 本题中 1 也要算入质数
	for (int i = 2; i <= m; i ++)
	{
		if (!v[i])
		{
			v[i] = i, p[++ cnt] = i;
			if (i % 4 == 1)
			{
				onE[++ cnt1] = i; // 模 4 后余 1 的质数
			}
			else if (i % 4 == 3)
			{
				threE[++ cnt3] = i; // 模 4 后余 3 的质数
			}
		}
		for (int j = 1; j <= cnt; j ++)
		{
			if (p[j] > v[i] || i * p[j] > m)
			{
				break;
			}
			v[i * p[j]] = p[j];
		}
	}
	return ;
}

void prework () // 预处理
{
	primes (5e6); // 预处理 5e6 以内的质数
	for (int i = 4; i <= 5e6; i += 4)
	{
		f[i] = i >> 2; // 对于 4 的倍数 i，f[i] = i / 4
	}
	for (int i = 1, j = 1; i < 5e6; i += 4)
	{
		while (j < cnt1 && onE[j + 1] <= i) // 双指针算法
		{
			j ++;
		}
		f[i] = f[i - onE[j]] + 1;
	}
	for (int i = 2; i < 5e6; i += 4)
	{
		f[i] = f[i + 2];
	}
	for (int i = 3, j = 1; i < 5e6; i += 4)
	{
		while (j < cnt3 && threE[j + 1] <= i)
		{
			j ++;
		}
		f[i] = f[i - threE[j]] + 1;
	}
	for (int i = 4; i <= 5e6; i += 4)
	{
		f[i] ++; // 对于 4 的倍数 i，g[i] = f[i] + 1
	}
	return ;
}

int main ()
{
	scanf ("%d", &t), prework ();
	while (t --)
	{
		scanf ("%d", &n), mn = 2e9;
		for (int i = 1; i <= n; i ++)
		{
			scanf ("%d", &a[i]);
			if (f[a[i]] < mn)
			{
				mn = f[a[i]], pos = i;
			}
		}
		printf ("Farmer %s\n", a[pos] % 4 ? "John" : "Nhoj");
	}
	return 0;
}
```

---

## 作者：zhenjianuo2025 (赞：0)

### Solve
设 $g_i$ 表示 $n=1$，数量为 $i$ 时 Farmer John（下文称 FJ ）有没有必胜策略 $(1/0)$。

显然
$g_0=0$，$g_1=g_2=g_3=1$，$g_4=0$，$g_i=\max_{j\in \text{primes},j\le i}\{1-g_{i-j}\}\ (i\ge 5)$。打表找循环节发现 $g_{4k}=0\ (k\ge 0)$，其余为 $1$。

设 $f_i$ 表示 $n=1$，若 $i=4k \ (k\ge 0)$，则表示 FJ 获胜的最少次数，否则为 FJ 失败的最多次数（要拖尽量长的时间）。

显然

$$
f_i=\max \{f_{i-1},f_{i-2},f_{i-3}\}+1 \ (i\bmod 4=0)
$$
$$
f_i=\min_{j=4k+1,j\le i,j\in \text{primes}} \{f_{i-j}\}+1 \ (i\bmod 4=1)
$$
$$
f_i=f_{i-2}+1 \ (i\bmod 4=2)
$$
$$
f_i=\min_{j=4k+3,j\le i,j\in \text{primes}} \{f_{i-j}\}+1 \ (i\bmod 4=3)
$$

容易发现 $f_{4k+a}\le f_{4(k-1)+a}\ (a<4)$，上面 $\min$ 中的 $j$ 在最大时整体取到最优。

然后比较一下谁先赢就可以了。
### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int> 
#define fi first
#define se second 
#define mp make_pair
int n, a[200010], mn[5000010];
int cnt, prime[5000010];
bool book[5000010];
signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	for (int i = 2; i <= 5e6; i++) {
		if (!book[i]) prime[++cnt] = i;
		for (int j = 1; j <= cnt && i * prime[j] <= 5e6; j++) {
			book[i * prime[j]] = 1;
			if (i % prime[j] == 0) break;
		}
	}
	mn[0] = 1, mn[1] = 2, mn[2] = 2, mn[3] = 2, mn[4] = 3;
	int _4n_1 = 1, _4n_3 = 3, _4n1 = 1, _4n3 = 3;
	for (int i = 5; i <= 5e6; i++) {
		while (_4n1 + 4 <= i) {
			_4n1 += 4;
			if (!book[_4n1]) _4n_1 = _4n1;
		}
		while (_4n3 + 4 <= i) {
			_4n3 += 4;
			if (!book[_4n3]) _4n_3 = _4n3;
		}
		if (i % 4 == 0) mn[i] = max(mn[i - 1] + 1, max(mn[i - 2] + 1, mn[i - 3] + 1));
		else if (i % 4 == 1) mn[i] = mn[i - _4n_1] + 1;
		else if (i % 4 == 2) mn[i] = mn[i - 2] + 1;
		else if (i % 4 == 3) mn[i] = mn[i - _4n_3] + 1;
	}
	int T;
	cin >> T;
	while (T--) {
		cin >> n;
		for (int i = 1; i <= n; i++) cin >> a[i];
		int fn = 1e9, fj = 1e9, in = 0, ij = 0;
		for (int i = 1; i <= n; i++) {
			if (a[i] % 4) {
				if (mn[a[i]] < fj) fj = mn[a[i]], ij = i;
			} else {
				if (mn[a[i]] + 1 < fn) fn = mn[a[i]] + 1, in = i;
			}
		}
		if (fn < fj || (fn == fj && in < ij)) cout << "Farmer Nhoj\n"; else cout << "Farmer John\n";
	}
	return 0;
} 
```

---

## 作者：Lantrol (赞：0)

个人认为是本场质量最高的一题。结论很有意思。

## 思路

第一眼，发现每个房间相互独立。所以，在所有“先手最优策略下清空奶牛所需最小回合数”最小的房间中，编号最小的房间的获胜者是最终获胜者。但对于每个房间的回合数（定义回合数为游戏结束的回合。若先手在第 $x$ 回合清空房屋，则回合数为 $x$，而若后手在第 $x$ 回合清空房屋，则回合数为 $x+1$，因为游戏会在两人下一次绕回该房间时结束）怎么求，几乎没有任何思路。

没思路，就从 $a_i=1$ 开始打个表吧，也许能发现些规律。

对于双方，每步操作的最优策略是：对于自己稳赢的房间，则采用尽可能快取得胜利的策略，对于自己稳输的房间，则采用让对方可能最慢取得胜利的策略。

下表中记“**双方最优策略下**清空所需最小**操作步数（两方一共操作的步数）**”为 $k$。

![](https://cdn.luogu.com.cn/upload/image_hosting/czf3w4r0.png)

（表格渲染似乎挂了，只能放张图片）

为表述方便，以下规定 $1$ 属于质数。

观察表格，发现当 $(a_i \mod 4 = 0)$ 时，后手获胜，否则先手获胜。这很容易理解。因为对于任意质数 $p$，$(p \mod 4\ne 0)$ 成立。当先手取任意一个质数 $p$，后手只需要任取质数 $x$ 使得 $(p+x)\mod 4=0$，这样重复下去即可稳稳取得胜利。

此时，我们发现一个当后手稳赢时，先手尽可能拖慢后手胜利的策略：先手一直取 $2$——唯一的偶质数，逼迫后手也一直取 $2$。这样所需要的最小操作步数是最大的，为 $\dfrac{a_i}{2}$。

接下来考虑先手如何取得胜利。

先手取过一次后，相对来说就变成了后手。设先手取走的质数为 $p$，那么一定有 $p \equiv a_i \pmod 4$。作为先手，要尽可能加快胜利的进程，而实质上，我们仅需要考虑先手的第一次操作。因为在此之后，一切游戏进程将确定——接下来需要 $\dfrac{a_i-p}{2}$ 次操作来结束游戏。我们希望这个值尽可能小，所以我们的 $p$ 需要尽可能大。

考虑到这里，正解也就一目了然了。

预处理出范围内的全部质数，按除以 $4$ 的余数分类，分成余数为 $1$ 和余数为 $3$ 两类。对于每个 $a_i$，根据其除以 $4$ 的余数，在相应的质数类别中二分出不大于 $a_i$ 的最大质数 $p$，然后计算该房间的最少操作步数，答案是 $\dfrac{a_i-p}{2}+1$。

为什么质数不单独分一类：除以 $4$ 的余数为 $2$？

显然满足这个条件的质数只有一个 $2$。对于所有满足 $(a_i \mod 4=2)$ 的 $a_i$，答案也只能是 $\dfrac{a_i-2}{2}+1$，也就是 $\dfrac{a_i}{2}$。

最后根据最少操作步数算出相应回合数，然后统计最小值即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define ioc ios::sync_with_stdio(0)
using namespace std;
const int MAXX=5e6+5,MAXP=5e5+5,MAXN=1e5+5;

bool isp[MAXX];
int prm[MAXP],cnt,prm1[MAXP],cnt1,prm2[MAXP],cnt2;
void init(int mxn){
	memset(isp,1,sizeof(isp));
	isp[1]=0;
	prm1[++cnt1]=1;
	for(int i=2;i<=mxn;i++){
		if(isp[i]){
			if(i%4==1) prm1[++cnt1]=i;
			else if(i%4==3) prm2[++cnt2]=i;
			prm[++cnt]=i;
		}
		for(int j=1;j<=cnt&&i*prm[j]<=mxn;j++){
			isp[i*prm[j]]=0;
			if(i%prm[j]==0) break;
		}
	}
}

int n,a[MAXN],ans[MAXN],minx,minw;
bool winner[MAXN];

void solve(){
	memset(winner,0,sizeof(winner));
	memset(ans,0,sizeof(ans));
	minx=1e18,minw=-1;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		winner[i]=(a[i]%4);
		if(!(a[i]&1)){
			ans[i]=a[i]/2;
		}
		else{
			int x=0;
			if(a[i]%4==1){
				x=lower_bound(prm1+1,prm1+cnt1+1,a[i])-prm1;
				if(prm1[x]>a[i]) x--;
				x=prm1[x];
			}
			else if(a[i]%4==3){
				x=lower_bound(prm2+1,prm2+cnt2+1,a[i])-prm2;
				if(prm2[x]>a[i]) x--;
				x=prm2[x];
			}
			ans[i]=(a[i]-x)/2+1;
		}
		ans[i]=ans[i]/2;
	}
	for(int i=1;i<=n;i++){
		if(ans[i]<minx){
			minx=ans[i];minw=winner[i];
		}
	}
	if(minw==1) cout<<"Farmer John\n";
	else if(minw==0) cout<<"Farmer Nhoj\n";
}
signed main(){
	ioc;cin.tie(0);cout.tie(0);
	init(MAXX);
	int T;
	cin>>T;
	while(T--){
		solve();
	}
}
```

### 鲜花

好像可以通过预处理省掉二分质数的 $\log$。

---

## 作者：Φρανκ (赞：0)

题意：有 $n$ 堆石子，两人轮流从每一堆中依次取走 $1$ 或任意质数枚，先不能操作者败。给定初始状态，求胜者。

核心思想：博弈论

解：

若仅有一堆，则易证有且仅有 $4n$ 个石子时对先手必败。（$0$ 必败，且若 $0\sim 4i$ 必败 $4i+1,4i+2,4i+3$ 必胜，$4i+4$ 必败）

令 $f_i$ 表示必胜一方胜利所需步数。显然有 $f_0=0,f_p=1,f_{4i+2}=f_{4i}+1$（否则无法转移至对手必败），且有 $f_{4i}=max(f_{4i-1},f_{4i-2},f_{4i-3})+1=f_{4i-2}+1$，因为必败的先手一定希望尽可能延长失败步数，且显然有 $f_{4i-1},f_{4i-3}\le f_{4i-2}$（它们都可以转移至 $f_{4i-4}$，且前两者也许有更快的转移方式）。

综上所述，$f_{2i}=i$，而对于奇数，则从小到大查找首个可以合法转移到的 $f_{4j}$ 即可。以上所述都可以预处理。

对于每个询问，基本上遵循所需胜利步数最少的房间决定胜者。但要注意一种特殊情况：若一个房间需要 $2i+1$ 步胜利，其后另一房间需要 $2_i$ 步胜利，则先手仍能取胜。这是由于虽然在第 $i$ 轮后手搬空了后一房间，但是他在第 $i+1$ 轮访问前一房间时已经失败，根本无法使先手访问后一房间。

代码：
```
#include <bits/stdc++.h>
using namespace std;
struct inp
{
	int i, s;
}r[500001];
int t, n, p[500001], s[5000001], flag, a, res;
bool b[5000001];
bool cmp(inp x, inp y)
{
	if(x.s/2!=y.s/2)
		return x.s/2<y.s/2;
	return x.i<y.i;
}
int main()
{
	for(int i=2; i<=5000000; i++)
	{
	    if(b[i]==0)
	      p[++flag]=i;
	    for(int j=1; j<=flag; j++)
		{
	      if(i*p[j]>5000000) 
		  	break;
	      b[i*p[j]]=1;
	      if(i%p[j]==0)
	        break;
		}
    }//筛质数
    for(int i=1; i<=5000000; i++)
    	if(i%2==0)
    		s[i]=i/2;
    	else
    		for(int k=0; 4*k<i; k++)
    			if(b[i-4*k]==0)
    			{
    				s[i]=2*k+1;
    				break;
				}//预处理f
	cin>>t;
	for(int i=1; i<=t; i++)
	{
		res=5000001;
		cin>>n;
		for(int j=1; j<=n; j++)
		{
			cin>>a;
			r[j].s=s[a];
			r[j].i=j;
		}
		sort(r+1, r+n+1, cmp);//注意cmp
		if(r[1].s%2==0)
			cout<<"Farmer Nhoj"<<endl;
		else
			cout<<"Farmer John"<<endl;
	}
	return 0;
}

```

---

## 作者：Hedgehog_210508 (赞：0)

**题目传送门**：[here](https://www.luogu.com.cn/problem/P8901)

**思路**：

首先观察样例，并手动模拟 $n=1$ 的情况找规律，可以发现：若 $a_{i}$ 是 $4$ 的倍数先手败，否则先手胜。显然对于 $1,2,3$ 先手可以直接取完，而对于 $4$ 先手怎么取都会转化为后手面对 $1,2,3$ 的情况，后手胜。可以依次进行一个简单地递推。

接下来考虑普遍情况。每个点独立看做一场游戏，那么每个点的胜利者都是确定的，而这个胜利者显然会更愿意快些结束游戏，总体上少转几圈尽早在这个点获得总体胜利，而失败者肯定会拖延。接下来只需要知道在这样情况之下，每个点要进行多少轮次的游戏。

当 $a_i$ 是 $4$ 的倍数，先手败，后手为了让先手一直面对 $4$ 的倍数（否则局面被扭转），取得数和先手的数的和必为 $4$ 的倍数，先手为了拖延，可以取 $2$，这样后手只得也取 $2$ 来应对。这时总共有 $\dfrac{a_i}{2}$ 次。

当 $a_i$ 不是 $4$ 的倍数，几乎同理，不过先手要提前取使后手面对 $4$ 的倍数。先手只需要找到最大的符合的质数即可。

代码实现需要预处理一下质数。

**代码**：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll t;
ll flag[5000009],p[1000009],tot;
void prime(ll m){
	flag[1]=1;
	for(ll i=2;i<=m;i++){
		if(!flag[i]) p[++tot]=i;
		for(ll j=1;j<=tot&&i*p[j]<=m;j++){
			flag[i*p[j]]=1;
			if(i%p[j]==0) break;
		}
	}
	return;
}  
int main(){
	std::ios::sync_with_stdio(false);
	cin>>t;
	prime(5000000);
	while(t--){
		ll n,a[100009],ans=2e9;
		cin>>n;
		for(ll i=1;i<=n;i++) cin>>a[i];
		for(ll i=1;i<=n;i++){
			if(a[i]%2==0) a[i]=a[i]/2;
			else{
				ll tmp=a[i];
				while(1){
					if((a[i]-tmp)%4==0&&(!flag[tmp]||tmp==1)){
						a[i]=1+(a[i]-tmp)/2;
						break;
					}
					tmp--;
				}
			}
		}
		for(ll i=1;i<=n;i++){
			if(ans/2>a[i]/2) ans=a[i];
		}
		if(ans%2) cout<<"Farmer John"<<endl;
		else cout<<"Farmer Nhoj"<<endl;
	}
	return 0;
}
```


---

