# Team Building

## 题目描述

你需要组建一支排球队。为了组织一支排球队，你需要为队伍里的$p$个不同的位置，从$n$个人中选出$p$个人，且每个位置上都恰好有一个人。另外还需要从剩下的人中选出恰好$k$个人作为观众。

对于第$i$个人，已知他作为观众时能为队伍增加$a_i$点力量，还有他在队伍的第$j$个位置上时能为队伍增加$s_{i,j}$点力量。请问这只排球队力量的最大值是多少？

## 样例 #1

### 输入

```
4 1 2
1 16 10 3
18
19
13
15```

### 输出

```
44```

## 样例 #2

### 输入

```
6 2 3
78 93 9 17 13 78
80 97
30 52
26 17
56 68
60 36
84 55```

### 输出

```
377```

## 样例 #3

### 输入

```
3 2 1
500 498 564
100002 3
422332 2
232323 1```

### 输出

```
422899```

# 题解

## 作者：UperFicial (赞：8)

[题目传送门](https://www.luogu.com.cn/problem/CF1316E)

同步发表于我的 [cnblogs](https://www.cnblogs.com/UperFicial/p/16658502.html)。

状压 DP 入门题。

设 $f_{i,S}$ 表示考虑了前 $i$ 个人，队伍放置情况为 $S$ 时（`0` 表示放置了队员，`1` 表示没有放置）的最大贡献。

然后分讨一下 $i$ 是去当队员，还是当观众，还是摆烂。

如果 $i$ 当队员，那么枚举一下 $i$ 被放在了哪一个位置上，记为 $j$，这时需要满足 $S$ 二进制下的第 $(j-1)$ 位是 `1`，然后直接转移就行了，$f_{i,S}=f_{i,S\oplus 2^{j-1}}+s_{i,j}$。

下面就选择当观众还是摆烂问题。我们贪心一下，将 $a$ 从大到小排序，这样，能当观众就当观众的策略一定是最优的。

所以我们只需要考虑当前观众数量是否小于 $k$。如果小于 $k$，那么 $i$ 肯定当观众 $f_{i,S}=f_{i-1,S}+a_i$，否则摆烂 $f_{i,S}=f_{i-1,S}$。

[代码](https://codeforc.es/contest/1316/submission/170921660)。

---

## 作者：syksykCCC (赞：8)

看到 $p$ 很小，考虑状态压缩 DP。

这里先把每个人按照 $a_i$ 降序排序。

设想，对于一个状态 $f_{i, s}$，$s$ 是一个 $p$ 位二进制数，表示队伍的选择情况，当前这个 $i$ 会不会被选进观众呢？

这里用到一个贪心，如果 $i \le \operatorname{CountBit}(s) + k$，那么，我们就会把 $i$ 选到观众里面去。

这很好理解，原本应该是选前 $k$ 个当观众，但是有 $\operatorname{CountBit}(s)$ 个已经被选到队伍里面去了，所以我们把限制往后移这么多位。

接下来，考虑把 $i$ 弄成队员。我们枚举一个 $s$ 包含的位置 $t$，试图把 $i$ 放进去，那么就要用 $f_{i-1, s \oplus 2^t}$ 来更新 $f_{i, s}$。

这题作为状态压缩 DP 还是比较好实现的，时间复杂度 $\mathcal O(n \cdot 2^p)$，具体细节可以看代码。代码中用 $j$ 代替了 $s$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e5 + 5, P = 130;
struct people
{
	LL a, s[7];
	bool operator < (const people &oth) const { return a > oth.a; }
} peo[N];
int n, p, k;
inline int CountBit(int x)
{
	int res = 0;
	while(x) res++, x &= x - 1;
	return res;
} 
LL f[N][P];
int main()
{
	scanf("%d %d %d", &n, &p, &k);
	for(int i = 1; i <= n; i++) scanf("%lld", &peo[i].a);
	for(int i = 1; i <= n; i++)
		for(int j = 0; j < p; j++)
			scanf("%lld", &peo[i].s[j]);
	sort(peo + 1, peo + n + 1);
	int full = 1 << p;
	memset(f, -0x3f, sizeof f);
	f[0][0] = 0;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 0; j < full; j++)
		{
			int cnt = CountBit(j);
			f[i][j] = f[i - 1][j];
			if(i <= cnt + k) f[i][j] = max(f[i][j], f[i - 1][j] + peo[i].a);
			for(int t = 0; t < p; t++) if(j >> t & 1)
				f[i][j] = max(f[i][j], f[i - 1][j ^ (1 << t)] + peo[i].s[t]);
		}
	}
	printf("%lld\n", f[n][full - 1]);
	return 0;
}
```

---

## 作者：UperFicial (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/CF1316E)。

同步发表于我的 [$\text{cnblogs}$](https://www.cnblogs.com/UperFicial/p/16660959.html)。

一眼费用流。

然后发现题解区竟然全是状压 DP？？？？？

[推销一下本题状压 DP 的题解](https://www.luogu.com.cn/blog/UperFicial/solution-cf1316e)。

那么我就来 yy 一下我的网络流做法吧，我会尽量把网络流的想法讲得自然一点。

考虑将所有人按照 $a_i$ 从大到小排序，那么贪心的考虑，如果一个人不去当球员，那么能当观众就当观众。

这里就有了一个隐藏的条件了：不管你 $p$ 个球员选的谁，观众一定是前 $\left(p+k\right)$ 个人中，没去当球员的贡献最大的前 $k$ 个，当然也至少需要 $k$ 个人，所以我们得到观众选取的范围 $[k,p+k]$。

我们钦定前 $b$ 个人**全部**当观众，其中 $b\in [k,p+k]$，那么肯定需要调整一些人当球员。

那么我们总体思路就出来了，首先钦定收益为前 $b$ 个人都当观众的收益，然后加上 $[1,n]$ 中球员的收益，然后减去 $[1,b]$ 中，由观众变成球员的收益。

具体如何选取呢？

我们对于 $i\in [1,b]$ 选出若干人当球员，在 $i\in (b,n]$ 中选出若干人当球员，其余人当观众，若观众没有空位，那么就摆烂。

那么在 $[1,b]$ 中选出多少人当球员呢？

显然答案是固定的，只能是 $(b-k)$ 个，因为我们一开始固定，观众只能在 $[1,b]$ 中选。有 $k$ 个人当观众，那么就有 $b-k$ 个人当球员。

而我们一共要找 $p$ 个人当球员，$[1,b]$ 中有 $b-k$ 个球员，所以 $(b,n]$ 中一共有 $p-(b-k)$ 个球员。

个数与花费两层限制，不就是费用流吗！

下文记 $(u,v,f,w)$ 表示一条从 $u$ 到 $v$，容量为 $f$，流量为 $w$ 的弧。

我们建立两个源点 $A,B$，表示 $[1,b]$ 点的集合，和 $(b,n]$ 点的集合。初始对于 $i\in [1,b]$，连一条 $(A,i,1,0)$ 的边，同理，对于 $i\in (b,n]$，连一条 $(B,i,1,0)$。

然后建立总源 $S$，连 $(S,A,b-k,0)$ 和 $(S,B,p-b+k,0)$ 的边。

$A,B$ 的意义到这里也就清晰明了了，它固定了两个集合中，当球员的人数。

之后就可以暴力连边啦。

连边的思路是，每一个 $[1,b]$ 的观众都有可能成为球员，那么暴力把所有可能连上，跑一遍网络流只会留下合法的解。

那么对于 $i\in [1,b]$ 和 $j\in [1,p]$，连一条 $(i,j+n,1,-a_i+s_{i,j})$ 的边，这里的意思，若 $i$ 变成球员，那么需要减掉一开始算在观众里 $a_i$ 的贡献，然后加上变成球员的贡献 $s_{i,j}$。

然后对于另一半 $i\in (b,n]$，练一天 $(i,j+n,1,s_{i,j})$ 的边，因为这里的 $i$ 一开始没有被钦定成观众，直接算它成为球员的贡献即可。

最后每一个球队的位置连向 $T$ 即可。

但是这道题可能需要 $\text{zkw}$ 费用流，我的 $\text{EK}$ 被卡了，但是我偷懒吸一口臭氧就卡过了（

代码想要的人私信，不放了。

求赞/kel


---

## 作者：suxxsfe (赞：5)

**updata on 3.16**  
感谢评论区里@[Fairicle](https://www.luogu.com.cn/user/135839)大佬的指正  
$f[i][s]$可以由$f[i-1][s \oplus (j-1)]+s_{i,j}$转移而来  

应改为：  

$f[i][s]$可以由$f[i-1][s \oplus 2^{j-1}]+s_{i,j}$转移而来  

&nbsp;  
---------

[CF1316E 【Team Building】](https://codeforces.com/problemset/problem/1316/E)  
状压dp，感觉比D简单  
$f[i][s]$，表示考虑前$i$个人，状态为$s$（$s$的第$j-1$个二进制位表示队员的第$j$个位置有没有人）的最大价值  
考虑如何转移  
&nbsp;  
如果不让第$i$个人当队员  
- 如果当前已选为观众的人不足$k$个，则一定让它当观众，那么$f[i][s]$由$f[i-1][s]+a_i$转移来，不过这样做的前提是要先把这$i$个人按照他们当观众时的价值排序，从而如果当前观众不到$k$个但不选第$i$个，就一定会在后面选一个$j(j>i)$当观众，$a_j<a_i$，就没有选第$i$个优了  
- 如果已经选了$k$个，不能再选直接$f[i][s]=f[i-1][s]$  

已经选了几个要通过$s$确定，也就是$i-1-s\text{在二进制中1的个数}$ 个人已被选位观众  
&nbsp;  
让第$i$个人当队员  
枚举把$i$放在哪一位，如果要将他放在第$j$位，则需满足$s$的第$j-1$个二进制位为1（也就是当前的状态这一个位置有人）,那么$f[i][s]$可以由$f[i-1][s \oplus 2^{j-1}]+s_{i,j}$转移而来  
这里异或的意义就是把$s$的第$j-1$个二进制位从1变0，被转移的状态肯定是第$j$个位置没人  
那么就可以写出代码了，其实整个思考的最重要部分就在于把$n$个人排序，来实现 **能被选去当观众就一定选，就能达到最优** 的效果，复杂度$O(np2^p)$  
```cpp  
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<iomanip>
#include<cstring>
#define reg register
#define EN std::puts("")
#define LL long long
inline int read(){
	int x=0,y=1;
	char c=std::getchar();
	while(c<'0'||c>'9'){if(c=='-') y=0;c=std::getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^48);c=std::getchar();}
	return y?x:-x;
}
int n,p,k;
struct data{
	int v,id;
	LL s[10];
}a[100006];
LL f[100006][130];
inline int cmp(data aa,data aaa){return aa.v>aaa.v;}
int main(){
	n=read();p=read();k=read();
	for(reg int i=1;i<=n;i++) a[i].v=read(),a[i].id=i;;
	for(reg int i=1;i<=n;i++)
		for(reg int j=1;j<=p;j++) a[i].s[j]=read();
	reg int lim=1<<p;
	std::sort(a+1,a+1+n,cmp);
	std::memset(f,-1,sizeof f);
	f[0][0]=0;
	for(reg int i=1;i<=n;i++){
		for(reg int s=0;s<lim;s++){
			int cnt=0;
			for(reg int j=0;j<p;j++)
				if(s&(1<<j)) cnt++;
			int tmp=i-1-cnt;
			if(tmp<k){
				if(f[i-1][s]!=-1) f[i][s]=f[i-1][s]+a[i].v;;
			}
			else f[i][s]=f[i-1][s];
			for(reg int j=1;j<=p;j++){
				if((s&(1<<(j-1)))&&f[i-1][s^(1<<(j-1))]!=-1)
					f[i][s]=std::max(f[i][s],f[i-1][s^(1<<(j-1))]+a[i].s[j]);
			}
		}
	}
	std::printf("%lld",f[n][lim-1]);
	return 0;
}

```

---

## 作者：Ray662 (赞：1)

[洛谷 传送门](https://www.luogu.com.cn/problem/CF1316E) | [CodeForces 传送门](http://codeforces.com/problemset/problem/1316/E)

[更好的阅读体验](https://www.luogu.com.cn/blog/sunrize/solution-cf1316e)

题目大意：

- 从 $n$ 个人中选出 $p$ 个作为球员，每个位置上要保证有一名球员，选 $k$ 个作为观众；

- 第 $i$ 个人作为球员在位置 $j$ 上贡献 $s_{i, j}$ 的力量，作为观众则贡献 $A_i$ 的力量；

- 最大化总力量；

- $2 \le n \le 10^5, 1 \le p \le 7, 1 \le p + k \le n, 1 \le A_i \le 10^9$。

---

### 分析

首先对于所有的 $i$ 按照 $A_i$ 递减排序。

$p$ 不大，容易想到状压。

定义 $f_{i, st}$：从前 $i$ 个人中选择队员，$p$ 个位置的选择状态为 $st$，这样能够得到的力量最大值。

显然 $f_{0,0} = 0$。

如果第 $i$ 个人放在第 $j$ 个位置上，则 $f_{i, st} = f_{i - 1, st - \{j\}} + s_{i, j}$。

如果第 $i$ 个人不当队员，要么当观众，要么不被用。如果目前观众数量还 $< k$，那么 $i$ 就必须当观众，否则后面的 $j > i$ 当观众力量更低（前面已经排过序了），不是最优解。

那么对于状态 $f_{i - 1, st}$，观众被选择了的数目就是 $c = i - 1 - m$（$m$ 为 $st$ 中 $1$ 的数量）。

所以有：

$$
f_{i, st} = f_{i - 1, st} + [c < k] \times A_i
$$

注：$[c < k]$ 表示如果 $c < k$ 则值为 $1$，否则为 $0$。

综合起来有：

$$
f_{i, st} = \max(f_{i - 1, st} + [c < k] \times A_i, f_{i - 1, st - \{j\}} + s_{i, j})
$$

故答案为 $f_{n, 2^p - 1}$。

---

时间复杂度 $O(n \times p \times2^p)$。

上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n, p, k, A[N], s[N][10];
vector<int> id(N);
long long f[N][1 << 8];
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n >> p >> k;
	for (int i = 1; i <= n; i ++ )  cin >> A[i], id[i] = i;
	for (int i = 1; i <= n; i ++ )  for (int j = 0; j < p; j ++ )  cin >> s[i][j];
	sort(id.begin() + 1, id.end(), [& A](int i, int j) { return A[i] > A[j]; });  // 排序
	memset(f, -1, sizeof(f));
	f[0][0] = 0;
	for (int i = 1; i <= n; i ++ )  for (int st = 0; st < (1 << p); st ++ ) {  // 遍历状态
		int x = i - 1;
		for (int j = 0; j < p; j ++ )  x -= ((st & (1 << j)) > 0);
		if (f[i - 1][st] != -1) {
			if (x < k) f[i][st] = f[i - 1][st] + A[id[i]];
			else f[i][st] = f[i - 1][st];
		}
		for (int j = 0; j < p; j ++ )  if ((st & (1 << j)) && f[i - 1][st ^ (1 << j)] != -1)
			f[i][st] = max(f[i][st], f[i - 1][st ^ (1 << j)] + s[id[i]][j]);
	}
	printf("%lld\n", f[n][(1 << p) - 1]);
	return 0;
}
```

---

## 作者：离散小波变换° (赞：1)

## 题目大意

$n$个人，每个人作为观众时可以产生$a_i$的价值，作为第$j$位队员时可以产生$b_{i,j}$的价值。现在需要**恰好**选出$p$名队员与$k$名观众，求最大的价值。保证$p\le 7,p+k\le n,n\le 10^5,$所有数字大于$0$。

## 题解

这篇题解与楼上不同的地方在于，这里主要使用了递推进行更新。

### 思路

很显然，假如我们选出了$p$名队员，那么选出的$k$个观众**必定**是按照$a_i$从大到小排列的前$k$个人。因此，我们可以先将所有人按照$a_i$从大到小排序，那么若某个人当不了队员，那就尽量让他当观众。不然，后面的观众产生的贡献必定小于他作为观众产生的贡献。

由于题目中$p$很小，因此我们可以考虑**状态压缩动态规划**。

我们用$dp_{i,j}$表示当前考虑到$i$个人，**此时**队员的选择情况为$j$，能够产生的最大价值。那么，我们可以用它更新下一个人。即：

$$\begin{aligned}dp_{i+1,j}&\gets\max\left\{dp_{i+1,j},dp_{i,j}\right\} & \text{第}i\text{个人什么也不做} \cr dp_{i+1,j}&\gets\max\left\{dp_{i+1,j},dp_{i,j}+a_i\right\} &\text{第}i\text{个人可以当观众}\cr dp_{i+1,j \operatorname{or} 2^k}&\gets\max\left\{dp_{i+1,j \operatorname{or} 2^k},dp_{i,j}+b_{i,k} \right\}& \text{第}i\text{个人可以作为队员}k \end{aligned}$$

其中第二个式子的要求是： $i-\text{状态j中的队员数}\le k$，即在$i$前面所有的人都作为观众或队员后$i$是否能选；第三个式子的要求是$j \operatorname{and} 2^i=0$。

**时间复杂度**$\mathcal(N\times p \times 2^p)$，可以通过本题。

### 小优化

这个式子是可以用滚动数组进行优化的。

我们发现，若当前队员数为$c$，那么只能影响到队员数$>c$的状态以及它本身。于是我们将需要枚举的状态按照$1$的数量进行排序。对于数字$1$的统计既可以用内置函数，也可以直接用$\rm lowbit$暴力统计。

优化成果：**空间复杂度**:$\mathcal O(N\times 2^p)\to \mathcal O(2^p)$。另外这样也能节省不少常数，于是$\rm 36.39s\to 16.35s$。（注：这里比较的是总时间）

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l;i<=r;i++)
#define dn(l,r,i) for(int i=l;i>=r;i--)
using namespace std;

typedef long long LL;
const int INF =2147483647;
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0')
    w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9')
    ret=ret*10+c-'0';
    return ret*w;
}
const int MAXN =1e5+3,MAXP=7+3,MAXS=(1<<7)+3;
LL n,p,k,t,dp[MAXS],C[MAXS];
struct NodeA{
    int a,b[MAXP]; bool operator <(NodeA t){return a>t.a;}
}P[MAXN];
struct NodeB{
    int s,c;       bool operator <(NodeB t){return c>t.c;}
}Q[MAXS];
#define ckm(a,b) (b>a?(a=b):0)
int main(){
    n=qread(),p=qread(),k=qread();
    up(1,n,i) P[i].a=qread();
    up(1,n,i) up(1,p,j) P[i].b[j]=qread();
    sort(P+1,P+1+n); t=(1<<p)-1;		//对人员进行排序
    up(0,t,i){
        int w=i,c=0; while(w) w-=(w&-w),++c;
        Q[i+1].s=i,Q[i+1].c=c;
    }
    sort(Q+1,Q+2+t); up(1,t,i) dp[i]=-INF;	//对枚举状态进行排序&初始化
    up(1,n,i) up(1,t+1,j){    //当前状态为j，此时考虑第i个人
        int s=Q[j].s,c=Q[j].c; LL w=dp[s];
        if(w<0) continue; if(i-c<=k) dp[s]+=P[i].a;
        up(1,p,k) if(!(s&(1<<k-1))) ckm(dp[s|(1<<k-1)],w+P[i].b[k]);
    }
    printf("%lld\n",dp[t]);
    return 0;
}
```

---

## 作者：jiangtaizhe001 (赞：0)

[可能更好的阅读体验](https://www.cnblogs.com/jiangtaizhe001/p/16881809.html)

[题目传送门](http://codeforces.com/problemset/problem/1316/E)

### 题目大意

[传送门](https://www.luogu.com.cn/problem/CF1316E)  
你需要组建一支排球队。为了组织一支排球队，你需要为队伍里的 $p$ 个不同的位置，从 $n$ 个人中选出 $p$ 个人，且每个位置上都恰好有一个人。另外还需要从剩下的人中选出恰好 $k$ 个人作为观众。  
对于第 $i$ 个人，已知他作为观众时能为队伍增加 $a_i$ 点力量，还有他在队伍的第 $j$ 个位置上时能为队伍增加 $s_{i,j}$ 点力量。请问这只排球队力量的最大值是多少？

$n,k\le 10^5$，$p\le 7$，$a_i,s_{i,j}\le 10^9$

### 题目解析
~~CF 2300，好像也不是很难，评紫题过分了昂~~
显然把上场的队员选定之后，那么剩下的肯定是选择贡献大的当做观众。  
那么就把所以人作为观众的贡献降序排序，考虑在这个序列上 DP。  
$p\le 7$，显然考虑状态压缩。  
问题在于怎么转移。设 $f_{i,j}$ 为前面 $i$ 个中选择情况状态压缩之后为 $j$ 的贡献最大值，不妨设 $j$ 二进制位 $1$ 的个数（也就是选择作为运动员的个数）是 $now$。  
考虑从之前的转移。分两种情况讨论。  
如果 $i>p+now$，那么这个人不是观众，所以直接加上作为运动员的贡献即可。  
如果 $i\le p+now$，那么这个人是观众，所以还要减去这个人当前作为观众贡献，然后第 $p+now$ 个人就成为了观众，需要加上此人的贡献。
时间复杂度 $\Theta(np2^p)$

```cpp
int n,p,m,msk;
struct JTZ{
	int au,pl[maxm];
	bool operator < (const JTZ x) const {
		return this->au > x.au;
	}
}a[maxn];
ll f[2][139];
int main(){
	n=read(); p=read(); m=read(); msk=(1<<p)-1; int i,j,k,now; for(i=1;i<=n;i++) a[i].au=read();
	for(i=1;i<=n;i++) for(j=0;j<p;j++) a[i].pl[j]=read();
	sort(a+1,a+n+1); for(i=1;i<=m;i++) f[0][0]+=a[i].au;
	for(i=1;i<=n;i++) for(j=0;j<=msk;j++){
		now=0; f[i&1][j]=f[(i&1)^1][j]; for(k=0;k<p;k++) if(j&(1<<k)) now++;
		for(k=0;k<p;k++) if(j&(1<<k)){
			if(i>m+now) f[i&1][j]=mmax(f[i&1][j],f[(i&1)^1][j^(1<<k)]+a[i].pl[k]);
			else f[i&1][j]=mmax(f[i&1][j],f[(i&1)^1][j^(1<<k)]+a[i].pl[k]-a[i].au+a[m+now].au);
		}
	} print(f[n&1][msk]); return 0;
}
```

---

## 作者：Mihari (赞：0)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF1316E)

# 题解

可以想到一个十分简陋的状态：定义 $f[i][s]$ 为选到第 $i$ 个人，队伍的空缺情况为 $s$ 时的力量最大值，但是这有个问题——那些会变成观众的人该如何决策选还是不选？

对于观众，我们可以有一个十分显然的贪心——在那些还未被选中是队员的人中选前 $k$ 个最大的（如果前 $i$ 个剩下的不够，那就算剩下的都选，不用贪心），但是我们这个状态似乎不能记录对于状态 $s$ 我们对应选了哪些人作为队员，而 $i$ 这个人是否有可能被选作观众。

为了我们能够确定第 $i$ 个人是否能被选中为观众，我们将所有的人按照 $a$ 值进行排序，然后，对于 $f[i][s]$ 这个状态的转移，我们考虑 $i$ 在什么情况下能被选作观众，显然有

1. 前 $i-1$ 个人能够足够 $s$ 状态下队员的人数；
2. 在前 $i-1$ 个人选完队员后，第 $i$ 个人必须是剩下的人中 $a$ 值前 $k$ 小的；

对于 $1$ 我们可以用初始化极小值去掉这种不合法情况，对于 $2$，由于我们已经将 $a$ 值排序，那么剩下的人也一定是按照 $a$ 值由大到小分布的，那么我们只需要判断剩下的人是否多于 $k$ 个即可，即必须满足 $i-\text{bitcnt}(s)\le k$，其中 $\text{bitcnt}(x)$ 指 $x$ 在二进制下 $1$ 的个数。

如果第 $i$ 个人被选作队员，那么我们暴力枚举其被填在什么地方，从前一状态转移过来即可，这个转移就很简单了...

# 代码

```cpp
https://www.cnblogs.com/Arextre/p/13460591.html
```



---

