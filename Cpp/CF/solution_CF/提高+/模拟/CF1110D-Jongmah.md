# Jongmah

## 题目描述

你正在玩一种叫做 Jongmah 的游戏。你不需要了解游戏规则也能解决这个问题。你手中有 $n$ 张牌。每张牌上写有一个 $1$ 到 $m$ 之间的整数。

为了赢得游戏，你需要组成若干组三张牌的“组三”。每组三张牌，要求这三张牌上的数字要么完全相同，要么是连续的。例如，$7, 7, 7$ 是一个有效的组三，$12, 13, 14$ 也是有效的，但 $2, 2, 3$ 或 $2, 4, 6$ 都不是。你只能用手中的牌来组成组三，每张牌最多只能用在一个组三中。

为了判断你距离胜利还有多远，你想知道用手中的牌最多能组成多少个组三。

## 说明/提示

在第一个样例中，你有牌 $2, 3, 3, 3, 4, 4, 4, 5, 5, 6$。你可以这样组成三个组三：$2, 3, 4$；$3, 4, 5$；$4, 5, 6$。由于只有 $10$ 张牌，无法组成 $4$ 个组三，所以答案是 $3$。

在第二个样例中，你有牌 $1$、$2$、$3$（$7$ 张）、$4$、$5$（$2$ 张）。你可以这样组成 $3$ 个组三：$1, 2, 3$；$3, 3, 3$；$3, 4, 5$。可以证明无法组成 $4$ 个组三。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
10 6
2 3 3 3 4 4 4 5 5 6
```

### 输出

```
3
```

## 样例 #2

### 输入

```
12 6
1 5 3 3 3 4 3 5 3 2 3 3
```

### 输出

```
3
```

## 样例 #3

### 输入

```
13 5
1 1 5 1 2 3 3 2 4 2 3 4 5
```

### 输出

```
4
```

# 题解

## 作者：__DICS (赞：21)

## 状态定义

作为一个dp初学者，费了不少力气才定义出状态来。

讲一下过程:

定义$dp[i]$为到位置$i$为止，最多能够形成多少个triplet。

显然这点信息是不够的。因为对于dp而言，有一个重要的性质:

**只要我们对于每一个状态记录它是从哪个状态转移来的，我们就能从最终状态步步向前，推出整个最优解。**

*一道加深对这个性质的理解的[题目](https://atcoder.jp/contests/dp/tasks/dp_f)*

也就是说，如果从$dp[n]$向前，对于每一个$i$，我们都知道组成了多少个$[i, i + 1, i + 2]$，多少个$[i, i, i]$。

为了知道我们对于每个$i$组成了多少$[i, i + 1, i + 2]$，显然我们需要把这个参数包含进我们的状态，也就是说我们的状态至少是$dp[i][t_i]$，其中$t_i$指的是$[i, i + 1, i + 2]$的数量。

那么$[i, i, i]$的数量呢?

显然不需要，因为在已经知道了$[i, i + 1, i + 2]$的情况下为了尽可能的多的形成triplet，肯定是能组成多少个triplet就组成多少个。

观察到$3$个$[i, i + 1, i + 2]$等同于$[i, i, i], [i + 1, i + 1, i + 1], [i + 2, i + 2, i + 2]$。因此$\forall t_i, t_i \in [0, 2]$。

那么$dp[i][t_i] = \max(dp[i - 1][t_{i - 1}] + l + \frac{cnt[i] - l}{3})$，$l$代表我们取$l$个$i + 2$，与剩下的$i$和$i + 1$结合。

**可是这样还需要知道剩下多少$i$和$i+1$才行啊。**

也就是说$dp[i - 1][t_{i-1}]$还应该包括$[i - 1, i, i + 1]$的个数。

于是，将状态定义为$dp[i][t_i][t_{i-1}]$。

为什么不多加别的状态了呢?

因为我们只需要用到$i, i + 1, i + 2$的个数。

有$t_{i - 1}$已经足够确定剩下多少$i$和$i + 1$了。

关于$t_{i - 2}$，它确实会影响$i$的个数。

但是考虑到递推式一定是形如$dp[t_i][t_{i - 1}] = \max(dp[t_{i - 1}][t_{i - 2}])$的形式，显然$t_{i - 2}$一定会影响$t_i$的上限，所以不需要将它列为状态中的变量。

### 关于\[i, i, i]

组成了$t_{i-1}$个$[i-1, i, i+1]$之后，还剩下$cnt[i] - t_{i-1}$个$i$，$cnt[i + 1]-t_{i-1}$个$i+1$。

于是我们最多可以取$\min(cnt[i] - t_{i-1}, cnt[i + 1] - t_{i - 1}, cnt[i + 2])$个$[i, i + 1, i + 2]$。

然后下一个问题，$[i, i, i]$要怎么统计有多少个?

这个貌似还挺简单的。只要在递推式里取完当前项的$[i, i, i]$之后，之后的部分就不用再考虑$[i-1, i-1, i-1]$之类的了。

既然是尽可能的多，那么取完$[i, i + 1, i + 2]$后，就只有一个选择了: 全部取走，拿去做$[i, i, i]$。

为什么这个贪心是正确的呢? 万一不全部取走可能有更好的方案呢?

考虑到我们可以枚举我们取了多少个$t_i$和$t_{i-1}$，显然所有情况都被包含了。

不全部取走显然就是等着给以后的triplet让位。那只要我们少取一点$t_i$和$t_{i-1}$，就可以达到同样的目标。

于是我们就可以不用考虑$[i, i, i]$了。

## 递推式

最后，根据上述讨论来推出递推式:

$dp[i][t_i][t_{i-1}] = \max\limits_{0 \le t_i \le \min(2, cnt[i] - t_{i-1} - t_{i-2}, cnt[i+1]-t_{i-1}, cnt[i+2])}(dp[i][t_i][t_{i-1}], dp[i - 1][t_{i-1}][t_{i-2}] + t_i + \frac{cnt[i]-t_i-t_{i-1}-t_{i-2}}{3})$

接下来考虑*初始化*。

因为这是从$i$推到$i + 1$，所以应该是在$dp[1]$做初始化。

对于$dp[1][0][0]$，它会访问$dp[0][t_0][t_{-1}]$，这些都应该是$0$。

因为全局数组默认全为$0$，所以可以省略初始化了。

然后考虑怎么*获取答案*。

对于$dp[m]$，一共$3 \times 3$个子状态全部跑一遍，提取最大值，应该就可以了。

好，已经有了这些之后，就开始写代码吧。

在写之前，把递推式的变量名改得好写点:

$dp[i][c][b] = \max\limits_{0 \le c \le \min(2, cnt[i] - b - a, cnt[i+1] - b, cnt[i+2])}(dp[i][c][b], dp[i - 1][b][a] + c + \frac{cnt[i]-c-b-a}{3})$

实际上在代码里面，$\min(2, cnt[i] - b - a, cnt[i + 1] - b, cnt[i + 2])$可以写成如下形式:

```c++
for (int a = 0; a < 3; ++a) {
    if (a + b + c > cnt[i]) continue;
	if (b + c > cnt[i + 1]) continue;
	if (c > cnt[i + 2]) continue;
    // ...
}
```
## AC代码

```c++
#include <cstdio>
#include <algorithm>
using namespace std;

int cnt[1000010];
int dp[1000010][3][3];
int n, m, temp;

void solve() {
    for (int i = 1; i <= m; ++i) {
        for (int c = 0; c < 3; ++c) {
            for (int b = 0; b < 3; ++b) {
                for (int a = 0; a < 3; ++a) {
                    if (a + b + c > cnt[i]) continue;
                    if (b + c > cnt[i + 1]) continue;
                    if (c > cnt[i + 2]) continue;
                    dp[i][c][b] = max(dp[i][c][b], dp[i - 1][b][a] + c + (cnt[i] - c - b - a) / 3);
                }
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &temp);
        ++cnt[temp];
    }

    solve();

    printf("%d\n", dp[m][0][0]);
    return 0;
}
```


---

## 作者：皎月半洒花 (赞：21)

$dp.$

其实主要思想都差不多，但我发这篇$sol$为了阐明一种观点：复杂度同阶的$DP$，不同的状态设计，会导致代码难度、时空复杂度等截然不同。

我们定义状态$dp_{i,j_{1},j_{2}}$表示考虑了前$i$大序号的麻将($mahJong$)，其中有$j_{1}$个$[i - 1, i, i + 1]$类型、有$j_{2}$个$[i, i + 1, i + 2]$类型的组合，最多组成多少个三元组。

这样定义状态的原因是：我们发现如果单纯用$1$维状态转移，那么状态势必是“前$i$大序号的麻将包含的三元组个数”，但是此状态不明确——无法准确定义“包含”的意思。而此处我们定义包含指**三元组右端点也$\leq i$**，那么$[i - 1, i, i + 1]$和$[i, i + 1, i + 2]$便需要单独定义出来。

转移的时候直接枚举有多少个$[i + 1,i+2, i+3]$即可（因为我们使用$i$更新$i+1$而不是用$i-1$更新$i$，如是做细节少、思考难度小）

然后我们的代码特别短:

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>

#define MAXN 1000020

using namespace std ; int N, M ;
int Sum[MAXN], dp[MAXN][3][3], i, j, k, l ;

inline int qrd(){
    register int k = 0 ; char c = getchar() ;
    while (c < '0' || c > '9')  c = getchar() ; 
    while (c <= '9' && c >= '0') k = (k << 1) + (k << 3) + c - 48, c = getchar() ;
    return k ;
}
int main(){
    cin >> N >> M ; 
    memset(dp, -1, sizeof(dp)), dp[0][0][0] = 0 ;
    for (i = 1 ; i <= N ; ++ i) Sum[ qrd() ] ++ ;
    for (i = 1 ; i <= M ; ++ i){
        for (j = 0 ; j < 3 ; ++ j)
            for (k = 0 ; k < 3 ; ++ k)
                for (l = 0 ; l < 3 ; ++ l)
                    if (Sum[i] < j + k + l) continue ;
                    else dp[i][k][l] = max(dp[i][k][l], dp[i - 1][j][k] + (Sum[i] - j - k - l)/3 + l) ;
    }
    cout << dp[M][0][0] << endl ; return 0 ;
}
```

闲扯一点：这个题楼主在当时并没有能够想出来……因为没有深刻思考其中的性质qaq

---

## 作者：p_b_p_b (赞：10)

[$$\large \color{purple} My\;Blog$$](https://www.cnblogs.com/p-b-p-b/p/10356146.html)

------

我…我我把这…这这题切了？？？

说实话这题的确不难，只是我看到有大佬没做出来有点慌……

突然发现这题是我的第500个AC呢。那就更要写篇题解纪念一下了。

-----------

## 思路

容易想到一个贪心：把有三个的都取完，然后随便搞后面的。

这显然是错的……

但你进一步思考发现：对于三元组$\{x-2,x-1,x\}$，它最多取$2$次，否则就可以变成多个$\{x,x,x\}$后再重新搞。

那么就容易想到DP了。

设$dp_{i,j,k}$表示考虑到第$i$位，钦定第$i$位已经用掉了$j$个，第$i-1$位已经用掉了$k$个，能得到的三元组个数。

转移时枚举选几个$\{i-2,i-1,i\}$ ，得到转移方程：

$$dp_{i,j,k}=\max_{l=0}^2\{dp_{i-1,k+l,l}+\lfloor \frac{cnt_i-l-j}{3}\rfloor +l\}$$

最后$ans=dp_{m,0,0}$。

注意DP时一个位置会被钦定两次，所以$0\leq j,k\leq 4$。

----------

## 代码

```cpp
#include<bits/stdc++.h>
namespace my_std{
	using namespace std;
	#define pii pair<int,int>
	#define fir first
	#define sec second
	#define MP make_pair
	#define rep(i,x,y) for (int i=(x);i<=(y);i++)
	#define drep(i,x,y) for (int i=(x);i>=(y);i--)
	#define go(x) for (int i=head[x];i;i=edge[i].nxt)
	#define sz 1010101
	typedef long long ll;
	template<typename T>
	inline void read(T& t)
	{
		t=0;char f=0,ch=getchar();
		double d=0.1;
		while(ch>'9'||ch<'0') f|=(ch=='-'),ch=getchar();
		while(ch<='9'&&ch>='0') t=t*10+ch-48,ch=getchar();
		if(ch=='.')
		{
			ch=getchar();
			while(ch<='9'&&ch>='0') t+=d*(ch^48),d*=0.1,ch=getchar();
		}
		t=(f?-t:t);
	}
	template<typename T,typename... Args>
	inline void read(T& t,Args&... args){read(t); read(args...);}
	void file()
	{
		#ifndef ONLINE_JUDGE
		freopen("a.txt","r",stdin);
		#endif
	}
//	inline ll mul(ll a,ll b){ll d=(ll)(a*(double)b/mod+0.5);ll ret=a*b-d*mod;if (ret<0) ret+=mod;return ret;}
}
using namespace my_std;

int n,m;
int cnt[sz];
int dp[sz][5][5];

int main()
{
	file();
	int x;
	read(n,m);
	rep(i,1,n) read(x),++cnt[x];
	memset(dp,~0x3f,sizeof(dp));
	dp[0][0][0]=0;
	rep(i,0,min(4,cnt[1])) dp[1][i][0]=(cnt[1]-i)/3;
	rep(i,2,m)
	{
		rep(j,0,4)
		{
			if (j>cnt[i]) break;
			rep(k,0,4)
			{
				if (k>cnt[i-1]) break;
				rep(l,0,2)
				{
					if (j+l>cnt[i]||k+l>cnt[i-1]||l>cnt[i-2]||k+l>4) break;
					dp[i][j][k]=max(dp[i][j][k],dp[i-1][k+l][l]+(cnt[i]-l-j)/3+l);
				}
			}
		}
	}
	cout<<dp[m][0][0];
}
```



---

## 作者：xrk2006 (赞：5)

# 【题解】CF1110D Jongmah

[博客园食用效果更佳](https://www.cnblogs.com/xrkforces/p/CF1110D.html)

代码很短，但是思路我怎么也想不到的神仙 DP。

## 题意概述

你在玩一个叫做 Jongmah  的游戏，你手上有 $n$ 个麻将，每个麻将上有一个在 $1$ 到 $m$ 范围内的整数 $a_i$。

为了赢得游戏，你需要将这些麻将排列成一些三元组，每个三元组中的元素是相同的或者连续的。如 $7,7,7$ 和 $12,13,14$ 都是合法的。你只能使用手中的麻将，并且每个麻将只能使用一次。

请求出你最多可以形成多少个三元组。

## 数据范围

- $1 \le n,m \le 10^6$
- $1 \le a_i \le m$

## 思路分析

首先我们定义第 $i$ 个顺子表示三个麻将上写着 $\{i,i+1,i+2\}$ 的三元组，$i$ 的三连击表示三个麻将上都写着 $i$ 的三元组，$cnt_i$ 表示写着 $i$ 的麻将数。

那么有一个结论是：对于每个 $i(1 \le i \le m)$，第 $i$ 个顺子最多只需要两次。因为 $3$ 个第 $i$ 个顺子可以转化为 $3$ 个三连击（$i,i+1,i+2$ 的三连击），所以一定存在最优解满足第 $i$ 个顺子取不超过两次。这是麻将题的常见技巧。

那么我们就可以考虑枚举第 $i$ 个顺子选了多少次（$0,1$ 或 $2$ 次）。

如果直接枚举每个顺子选了多少次，是 $3^m$ 的复杂度，不能接受。考虑通过 DP 优化。

但是如果直接 DP，发现很难进行状态设计，那么我们可以考虑简化问题。

考虑先解决如下问题：

> 如果我们并不是可以选择每个顺子，而是只能选择第 $i$ 个顺子（其中 $i\bmod 3=1$），那么如何确定有多少种合法的选择方案。

这个问题的简化之处就在于，第 $i$ 个的顺子的选择不受任何其它顺子的限制。

那么我们可以直接定义 $dp_i$ 表示选到了第 $i$ 个顺子总共有多少种三元组的选择情况。然后枚举选择次数 $k$，则对于每个 $i$，选择 $i$ 的三连击的个数是 $\left \lfloor\dfrac{cnt_i-k}{3}\right\rfloor$，那么 $dp_i$ 就可以用 $dp_{i-3}$ 加上第 $i$ 个顺子的选择情况再加上 $i,i-1,i-2$ 的三连击的选择情况而得到，那么有：
$$
dp_{i}=\max\limits_{0 \le k \le 2}\{dp_{i-3}+k+\left \lfloor\dfrac{cnt_i-k}{3}\right\rfloor+\left \lfloor\dfrac{cnt_{i-1}-k}{3}\right\rfloor+\left \lfloor\dfrac{cnt_{i-2}-k}{3}\right\rfloor\}
$$
这是只能选择第 $i(i\bmod 3=1)$ 个顺子的情况。

---

那么对于所有 $1\le i \le m$ 的每一个 $i$ 都能选的情况呢？

可以发现这个时候第 $i$ 个的顺子的选择情况和 $i$ 的三连击的选择情况，都受到第 $i-1$ 个顺子的选择情况和第 $i-2$ 的顺子选择情况的影响，这个时候我们就不能直接定义 $dp_i$ 表示选到了第 $i$ 个顺子的方案来解决问题了。我们考虑将第 $i-1$ 个顺子的选择情况和第 $i-2$ 个顺子的选择情况加进状态，由于这里第 $i$ 个顺子的选择情况也会影响到后面第 $i+1$ 个顺子的选择情况，所以也要把它加进状态，即 $dp_{i,j,k,t}$ 表示考虑到了第 $i$ 个顺子，第 $i$ 个顺子选择了 $j$ 次，第 $i-1$ 个顺子选择了 $k$ 次，第 $i-2$ 个顺子选了 $t$ 次的方案数，那么这时候 $dp_{i,j,k,t}$ 就可以直接由 $dp_{i-1,k,t,l}$ 其中 $l$ 是第 $i-3$ 个顺子的选择情况。

这时候我们发现，第 $i-3$ 个顺子的选择情况，对第 $i$ 个顺子的选择情况和 $i$ 的三连击的选择情况没有影响。同时在 $dp_{i-1,k,t,l}$ 的状态里已经包含了第 $i-2$ 个顺子的选择情况，所以我们可以将状态的最后一维删去。那么我们最终确定的 dp 状态就是：$dp_{i,j,k}$ 表示考虑到了第 $i$ 个顺子，第 $i$ 个顺子选择了 $j$ 次，第 $i-1$ 个顺子选择了 $k$ 次的方案数是多少。

那么对于 $dp_{i,j,k}$，就可以由 $dp_{i-1,k,t}$ 转移而来，其中 $t$ 表示第 $i-2$ 个顺子选择了 $t$ 次。然后我们枚举 $j,k,t$，那么 $dp_{i,j,k}$ 就等于 $dp_{i-1,k,t}$ 加上第 $i$ 个顺子选择次数 $j$ 再加上 $i$ 的三连击的选择次数。

---

现在问题就转化为，如何在已知 $j,k,t$ 的情况下，求 $i$ 的三连击可以选择多少次。

假设 $j=1,k=1,t=1$，如图所示：

![img](https://cdn.luogu.com.cn/upload/image_hosting/a9aiqf3g.png)

由该图可知，红色的部分即为三连击的个数，即 $\left\lfloor\dfrac{cnt_i-j-k-t}{3}\right\rfloor$。

那么总的转移方程式就为：
$$
dp_{i,j,k}=\max\limits_{0 \le j,k,t \le 2}\{dp_{i-1,k,t}+j+\left\lfloor\dfrac{cnt_i-j-k-t}{3}\right\rfloor\}
$$
时间复杂度 $O(27n)$。

## 代码实现

```cpp
//CF1110D
//The Way to The Terminal Station…
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=1e6+10;
int dp[maxn][3][3],a[maxn],cnt[maxn];

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

int main()
{
	int n,m;
	n=read();m=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		cnt[a[i]]++;
	}
	for(int i=1;i<=m;i++)
	{
		for(int j=0;j<3;j++)
		{
			for(int k=0;k<3;k++)
			{
				for(int t=0;t<3;t++)
				{
					if(cnt[i]<j+k+t)continue;
					dp[i][j][k]=max(dp[i][j][k],dp[i-1][k][t]+(cnt[i]-j-k-t)/3+j);
				}
			}
		}
	}
	cout<<dp[m][0][0]<<"\n";
	return 0;
}
```



---

## 作者：S_S_H (赞：5)

**作为一个蒟蒻，本人在看这道题的其他题解时有一些我不理解的地方。在理解了之后，希望其他和我有一样问题的同学可以明白**
### （弱弱地在这里推荐大家先看__DICS 的题解 大佬NB！）
首先对于这道题大部分人最基本的动规想法应该是用F[i]
表示前i个数的三元组的个数最大值。但我们可以想到这并不满足最优子结构的特性。
那么对于f[i]以第i个数为结尾的三元组的个数最大值，我们只需要考虑它的第i-1与第i-2的数能否满足最优

于是
## 一 解决‘三元组中的元素是相同的’
那么观察到3个[i, i + 1, i + 2][i,i+1,i+2]等同于[i, i, i], [i + 1, i + 1, i + 1], [i + 2, i + 2, i + 2][i,i,i],[i+1,i+1,i+1],[i+2,i+2,i+2]

也就是说我们只需要在满足连续三元组尽可能大的前提下（直到有一个数为0）最后计算即可。
## 二 确定状态转移方程
刚才已经说了我们只需要考虑它的第i-1与第i-2的数能否满足最优。

那么首先dp数组再开一维f[i][j],其中j 指的是[i, i + 1, i + 2]的数量。

但是对于尾序列[i,i+1,i+2],我们在知道i+2数量的同时，这样还需要知道剩下多少i和i+1才行。

所以（重点）就需要把我们的dp数组再开一维将状态转为f[i][j][k] k表示[i-1,i,i+1]三元组的个数（爆不了+好想）

为什么不多加别的状态了呢?

因为我们只需要用到i, i + 1, i + 2的个数。

f[i][j][k]中的k已经足够确定剩下多少i和i+1了。

对于第i-2个数它确实会影响i的个数。

但是考虑到递推式一定是形如dp[t_i][t_{i - 1}] = max(dp[t_{i - 1}][t_{i - 2}])的形式，显然t{i - 2}一定会影响ti  的上限，所以不需要将它列为状态中的变量。

（本段引自__DICS的题解）[传送门](https://www.luogu.org/blog/dics/solution-cf1110d)

最后列出状态转移方程

f[a][c][d]=max(f[a][c][d],f[a-1][b][c]+d+(num[a]-b-c-d)/3);

这里a表示循环到了第i个数

b表示尾序列[i,i+1,i+2]中的i；

c表示尾序列[i,i+1,i+2]中的i+1;

d表示尾序列[i,i+1,i+2]中的i+2;

其实循环顺序并不重要，就是3*3状态扫一遍，怎么写都能AC

最后输出f[m][0][0] 表示我们在以M为结尾的序列中没有以i为非尾元素的三元组（i+1与i+2没有了啊)

最后AC代码



```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int n,m,num[1000001],k,f[1000001][3][3];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
	scanf("%d",&k);
	num[k]++;	
	}
	for(int a=1;a<=m;a++)
		for(int b=0;b<3;b++)
			for(int c=0;c<3;c++)
				for(int d=0;d<3;d++){
					if(num[a]<b+c+d)
					continue;
					else{
						f[a][c][d]=max(f[a][c][d],f[a-1][b][c]+d+(num[a]-b-c-d)/3);
					}
				}
	printf("%d",f[m][0][0]);
	return 0;
}
```





---

## 作者：ZHR100102 (赞：3)

# 观察

首先观察这两个操作的性质，不难发现我们出掉的所有的顺子只要累计出了三次，这三次顺子就一定可以化作出三次相同的单牌。

而我们只需要最大化操作次数，显然这三次顺子和三次单牌是等价的，所以我们把三次顺子转化为我们更容易处理的三次相同单牌。

同时，我们得出结论：**任何一个顺子最多只能出 $2$ 次，否则一定可以被三个相同的牌代替掉一部分顺子。**

# 实现

这个性质就很好 dp 了，首先把所有牌扔进桶里是显然的。因为 $i-2,i-1$ 为开头的顺子会影响 $i$ 为开头的顺子的计算，所以我们将它们放入状态定义中。

设计 $dp_{i,j,k}$ 表示当前出到第 $i$ 位（位就是牌的种类），第 $i-1$ 位为开头的顺子出了 $j$ 个，第 $i$ 位为开头的顺子出了 $k$ 个。其中 $0 \le j,k \le 2$。第 $i-2$ 位在给后面状态转移时不会用到，只有给当前位转移才会用到。所以在转移的时候枚举第 $i-2$ 位出的顺子数 $l$ 即可。

因此有如下转移：

$$dp_{i,j,k}=\max_{l=0}^{2}dp_{i-1,l,j}+\left\lfloor\frac{tot_i-j-k-l}{3}\right\rfloor+k$$

答案即为 $dp_{m,0,0}$，因为 $m-1$ 位以后不足三种牌，不能组成顺子。

时间复杂度 $O(m\times 3^3)$。

# 代码

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define lc (p<<1)
#define rc ((p<<1)|1)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
using pi=pair<int,int>;
int n,m,dp[1000005][3][3],tot[1000005],ans;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		tot[x]++;
	}
	memset(dp,-0x3f,sizeof(dp));
	dp[0][0][0]=0;
	for(int i=1;i<=m;i++)
	{
		for(int a=0;a<3;a++)
		{
			for(int b=0;b<3;b++)
			{
				for(int c=0;c<3;c++)
				{
					if(tot[i]-a-b-c>=0)dp[i][b][c]=max(dp[i][b][c],dp[i-1][a][b]+(tot[i]-a-b-c)/3+c);
				}
			}
		}
	}
	cout<<dp[m][0][0];
	return 0;
}
```

---

## 作者：2huk (赞：3)

显然输入顺序是无所谓的。首先用个桶统计每个数的出现次数。

注意到 $3$ 张相同的「连续牌」在效果上完全等价于 $3$ 张「相同牌」。例如 $((1,2,3),(1,2,3),(1,2,3))$ 可以视作 $((1,1,1),(2,2,2),(3,3,3))$。

所以相同的「连续牌」的数量一定 $\le 2$。

考虑 DP。设 $f(i, a, b, c)$（$a,b,c \in [0,2]$）表示只考虑数值在 $1 \sim i$ 的牌，且有 $a$ 张 $(i-2,i-1,i)$，$b$ 张 $(i-1,i,i+1)$，$c$ 张 $(i, i+1, i+2)$。

这个状态里，因为我们只考虑数值在 $1 \sim i$ 的牌，所以 $b, c$ 并不算入这个状态的值里，只有 $a$ 算入。

显然对于第 $i$ 张牌而言，它自己能组成的「相同牌」的数量是 $\lfloor \frac{cnt_i-a-b-c}{3} \rfloor$。

综上转移为：

$$
f(i,a,b,c) = \max_{d \in [0,2]}f(i-1,d,a,b)+a+\lfloor \frac{cnt_i-a-b-c}{3} \rfloor
$$

代码：<https://codeforces.com/contest/1110/submission/289999345>

---

## 作者：C　C　A (赞：2)

$$\Large \rm D-Jongmah$$

$\quad$记 $dp_{i,c_1,c_2}$ 表示枚举到第 $i$ 位，当前已选择 $c_1$ 个 $\{a_{i-1},a_{i},a_{i+1}\}$ 和 $c_2$ 个 $\{a_{i},a_{i+1},a_{i+2}\}$.

$\quad$使用扩散型 $\rm DP$，转移时枚举选择多少个 $\{a_{i+1},a_{i+2},a_{i+3}\}$ 即可。

$\quad$乍一看这个 $\rm DP$ 好像是 $\Theta(n^2)$ 的，但是发现有如下性质：

> $\quad$每一个三元组 $\{a_{i},a_{i+1},a_{i+2}\}$，都最多被选择 $2$ 次，因为选择了三次以上就可以用 $3$ 个相同元素的三元组替代，且贡献相同。

$\quad$综上，时间复杂度 $\Theta(n)$.

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i, l, r) for (int i = l; i <= r; i++)

const int N = 1e6 + 10;

int n, m, x, cnt[N], dp[N][3][3], ans;

int main () {
	
	scanf("%d%d", &n, &m);
	rep(i, 1, n) scanf("%d", &x), cnt[x]++;
	
	rep(i, 0, m) rep(c1, 0, 2) rep(c2, 0, 2) rep(k, 0, 2)
		if (cnt[i + 1] >= c1 + c2 + k) dp[i + 1][c2][k] = max(dp[i + 1][c2][k], dp[i][c1][c2] + k + (cnt[i + 1] - c1 - c2 - k) / 3);
	printf("%d", dp[m][0][0]);
	
	return 0;
} 
```

---

## 作者：FlyInTheSky (赞：2)

先将所有数存在一个桶里，按数大小来DP。

显然对于一种方案$(a,b,c)$，他只会重复至多$2$次。

那么对于一个方案$(i,i+1,i+2)$，他最多只会有$2$个

那么设$dp(i,0/1/2,0/1/2)$为前$i$个数，第一个数是$i$的三元组个数，第二个数是$i$的三元组个数的最大个数。

转移
$$dp(i,a,b)=\max_{0\leq c \leq 2}\{dp(i-1,b,c)+c+(cnt-a-b-c) / 3\}$$
其中$cnt$为$i$数的个数。

后面$(cnt-a-b-c) / 3)$等价于将多余的$i$组成三元组$(i,i,i)$

```c++
#include<cstdio> 
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
#include<map>
#include<stack>
#define ms(i, j) memset(i, j, sizeof i)
#define LL long long
#define db long double
#define fir first
#define sec second
#define mp make_pair
using namespace std;

namespace flyinthesky {
	
	LL n, m, cnt[1000000 + 5];
	LL dp[1000000 + 5][3][3];
	
    void clean() {
    	ms(dp, -1);
	}
    int solve() {
    	
    	clean();
    	cin >> n >> m;
    	for (LL x, i = 1; i <= n; ++i) scanf("%lld", &x), ++cnt[x];
    	
    	dp[0][0][0] = 0;
    	for (LL i = 1; i <= m; ++i) {
    		for (LL a = 0; a < 3; ++a) {
    			for (LL b = 0; b < 3; ++b) {
    				for (LL c = 0; c < 3; ++c) {
    					LL tmp = cnt[i] - a - b - c;
    					if (tmp >= 0 && dp[i - 1][b][c] >= 0) {
    						dp[i][a][b] = max(dp[i][a][b], dp[i - 1][b][c] + c + tmp / 3);
						}
					}
				}
			}
		}
		
		LL ans = 0;
		for (LL a = 0; a < 3; ++a) 
    	for (LL b = 0; b < 3; ++b) ans = max(ans, dp[m][a][b]);

		cout << ans;

        return 0;
    }
}
int main() {
    flyinthesky::solve();
    return 0;
}
```

---

## 作者：xiazha (赞：0)

抓住性质，你会发现形如 $[i,i+1,i+2]$ 的三元组超过三组一定不会更优，因为每三组可以重组成 $[i,i,i]$，$[i+1,i+1,i+1]$ 与 $[i+2,i+2,i+2]$。

于是直接 dp，设 $dp_{i,j,k}$ 为选到值为 $i$ 的数，形如 $[i-1,i,i+1]$ 的三元组选了 $j$ 个，形如 $[i,i+1,i+2]$ 的三元组选了 $k$ 个，转移方程为：

$dp_{i,k,l}=\max_{j=0}^2 dp_{i-1,j,k}+\lfloor \frac{cnt_i-j-k-l}{3}\rfloor+l$

其中 $0\le k\le 2$，$0\le l\le 2$，$cnt_i$ 表示值为 $i$ 的个数。

时间复杂度 $O(n V^3)$，其中 $V=3$。

---

