# Dora's Paint

## 题目描述

不幸的是，朵拉在绘制班级壁画时颜料洒了。她将壁画视作一个 $n \times n$ 的矩阵 $b$，最开始时，矩阵中所有元素 $b_{i,j}$ 都是 0。

朵拉有两支不同颜色的画笔，在一次操作中，她可以使用其中一支画笔来为矩阵上色：

- 第一支画笔的颜色为 1，可以为矩阵中的某一列上色。具体来说，朵拉选择某一列 $1 \leq j \leq n$，然后将这一列中所有的元素设置为 1，即 $b_{i,j} := 1$ 对于所有 $1 \leq i \leq n$；
- 第二支画笔的颜色为 2，可以为矩阵中的某一行上色。具体来说，朵拉选择某一行 $1 \leq i \leq n$，然后将这一行中所有的元素设置为 2，即 $b_{i,j} := 2$ 对于所有 $1 \leq j \leq n$。

朵拉需要最终让整个矩阵 $b$ 只包含颜色 1 和颜色 2。

对于任意矩阵 $b$，定义 $f(b)$ 为从初始全 0 矩阵经过最少操作次数变为矩阵 $b$ 所需的最小步骤数。矩阵 $b$ 的“美丽值”是指用恰好 $f(b)$ 次操作将初始矩阵变为 $b$ 的不同方法数。如果不能将初始矩阵变为 $b$，那么美丽值为 0。

然而，朵拉随手犯了一个错误；实际的矩阵 $a$ 和真正应该得到的矩阵 $b$ 仅有一个元素不同。换句话说，存在一个唯一的元素位置 $(i, j)$，使得 $a_{i,j} = 3 - b_{i,j}$。

请帮助朵拉计算在所有可能错误的情况下，真实矩阵 $b$ 的期望美丽值，并对结果取模 $998\,244\,353$。

由于矩阵比较大，朵拉只告诉我们 $m$ 个颜色为 1 的元素的位置，剩下的 $n^2 - m$ 个元素的颜色为 2。

## 说明/提示

在第一个测试用例中，矩阵 $a = \left[\begin{matrix}1&1\\2&2\end{matrix}\right]$。考虑将元素 $(1,1)$ 改变以计算答案。

可以证明，将初始矩阵变为 $\left[\begin{matrix}2&1\\2&2\end{matrix}\right]$ 需要至少 3 步。具体方法是，先将第一行涂成颜色 2，然后将第二列涂成颜色 1，最后将第二行涂成颜色 2。操作过程如下：
$$
\left[\begin{matrix}0&0\\0&0\end{matrix}\right] \Rightarrow \left[\begin{matrix}2&2\\0&0\end{matrix}\right] \Rightarrow \left[\begin{matrix}2&1\\0&1\end{matrix}\right] \Rightarrow \left[\begin{matrix}2&1\\2&2\end{matrix}\right]
$$

事实证明，这种方法是唯一可以用3步实现的方法。因此，矩阵 $\left[\begin{matrix}2&1\\2&2\end{matrix}\right]$ 的美丽值为 1。类似地，如果改变矩阵中的其他元素，美丽值仍然是 1，所以真实矩阵 $b$ 的期望美丽值为 1。

在第二个测试用例中，矩阵 $a = \left[\begin{matrix}1&2\\2&2\end{matrix}\right]$。考虑将元素 $(2, 2)$ 改变以计算答案。

可以证明无法将初始矩阵变为 $\left[\begin{matrix}1&2\\2&1\end{matrix}\right]$，因此其美丽值是 0。如果改变矩阵中的其他任何元素，美丽值总是 2，所以期望美丽值为 $\frac{0 + 2 + 2 + 2}{4} = \frac{6}{4} \equiv 499\,122\,178 \pmod {998\,244\,353}$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
7
2 2
1 1
1 2
2 1
1 1
3 2
1 1
3 3
6 0
5 10
1 1
1 2
1 3
2 1
2 3
5 1
5 2
5 3
5 4
5 5
3 5
1 1
1 3
2 2
3 1
3 3
4 3
1 1
2 3
2 4```

### 输出

```
1
499122178
665496236
120
79859554
776412275
1```

# 题解

## 作者：IvanZhang2009 (赞：3)

出题人题解。cf 的评论区有大量踩爆我的做法，有别的好做法也欢迎交流。~~这种史也有人做吗？~~

题意：一个 $n\times n$ 的矩阵，初始全 $0$。每次操作可以选一列全改成 $1$ 或选一行全改成 $2$。定义**全是 $1,2$** 的矩阵的价值：用最小操作次数得到当前矩阵的方案数。给定矩阵，对于每种改一个格子的方案求价值和。$n\le 2\cdot 10^5$，$1$ 的个数不超过 $10^6$（输入）。

解法一：建立二分图，对行列建点，一个格子是 $1,2$ 代表连有向边，表示哪个操作先做。直接拓扑排序，将图分层，每一层显然都是行或都是列，且相互独立。所以答案是除了第一层（实际上不需要做操作）的每层点数的阶乘积。

先考虑原矩阵有解的情况，即可以拓扑排序。考虑改格子相当于反转一条边，手玩发现只能反转相邻两层的边（否则由于这是完全二分图，会形成环）。然后情况数只有 $O(n)$ 了，对每两层轻微讨论即可。

考虑原矩阵无解的情况，需要反转一条边把环干掉。发现找到任意环即可，然后遍历环上的边。这是完全二分图，所以必然存在四元环，暴力解之。考虑找一个四元环：拓扑排序后找一个度数为 $1$ 的点，然后往回跳 $3$ 次入边，就找到一个环。或者采用别的人类智慧方法。

考虑线性拓扑排序，发现度数的改变是全局的，双指针维护即可。精细实现时间复杂度 $O(n+m)$。实际上 $O((n+m)\log nm)$ 也能过。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define MOD         998244353
#define speMOD      2933256077ll
#define int         long long
#define pii         pair<int,int>
#define all(v)      v.begin(),v.end()
#define pb          push_back
#define REP(i,b,e)  for(int i=(b);i<(e);++i)
#define over(x)     {cout<<x<<endl;return;}
#define lowbit(x)   ((x)&(-(x)))
#define cntbit(x)   __builtin_popcount(x)
#define rf(v)       shuffle(all(v),sd);
mt19937 sd(std::random_device{}());
int qpow (int a,int b,int m=MOD,int res=1){
	a%=m;
	while(b>0)res=(b&1)?(res*a%m):(res),a=a*a%m,b>>=1;
	return res;
}
int fac[2000005],inv[2000005],si[2000005];
void init(int n){
	fac[0]=inv[0]=si[0]=1;
	REP(i,1,n+1)fac[i]=fac[i-1]*i%MOD;
	inv[n]=qpow(fac[n],MOD-2);
	for(int i=n-1;i>=1;--i)inv[i]=inv[i+1]*(i+1)%MOD;
	REP(i,1,n+1)si[i]=inv[i]*fac[i-1]%MOD;
}
int binom(int x,int y){
	return x<y||y<0? 0:fac[x]*inv[y]%MOD*inv[x-y]%MOD;
}
namespace fastIO {
#define BUF_SIZE 6000010
    bool IOerror = 0;
    inline char nc() {
        static char buf[BUF_SIZE], *p1 = buf + BUF_SIZE, *pend = buf + BUF_SIZE;
        if(p1 == pend) {
            p1 = buf;
            pend = buf + fread(buf, 1, BUF_SIZE, stdin);
            if(pend == p1) {
                IOerror = 1;
                return -1;
            }
        }
        return *p1++;
    }
    inline bool blank(char ch) {
        return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
    }
    inline void read(int &x) {
        char ch;
        while(blank(ch = nc()));
        if(IOerror)
            return;
        for(x = ch - '0'; (ch = nc()) >= '0' && ch <= '9'; x = x * 10 + ch - '0');
    }
#undef BUF_SIZE
};
using namespace fastIO;
int n,m;
int a[200005],b[200005];
vector<pii>c;
int d1[200005],d2[200005];
int visa[200005],visb[200005];
vector<int>h[200005],nodes[200005],buc[200005];
int X,Y;
int id1[200005],id2[200005],cnt[400005];
int solve(){
	REP(i,0,n+1)buc[i].clear();
	REP(i,0,n)buc[a[i]].pb(i);
	int num=0;
	REP(i,0,n+1)for(auto j:buc[i])id1[num++]=j;
	REP(i,0,n+1)buc[i].clear();
	REP(i,0,n)buc[b[i]].pb(i);
	num=0;
	REP(i,0,n+1)for(auto j:buc[i])id2[num++]=j;
	REP(i,0,n)d1[i]=d2[i]=-1;
	int ans=1,x=0,y=0,cur=0;
	while(x<n||y<n){
		if(x<n&&a[id1[x]]<=y){
			int sum=0;
			while(x<n&&a[id1[x]]<=y)++sum,d1[id1[x++]]=cur;
			if(cur)(ans*=fac[sum])%=MOD;
		}else if(y<n&&b[id2[y]]<=x){
			int sum=0;
			while(y<n&&b[id2[y]]<=x)++sum,d2[id2[y++]]=cur;
			if(cur)(ans*=fac[sum])%=MOD;
		}else return X=x,Y=y,0;
		++cur;
	}
	return ans;
}
int updater(int x,int y){
	int f=0,ret;
	for(auto i:c)if(i==make_pair(x,y))f=1;
	if(f)--b[y],++a[x],ret=solve(),++b[y],--a[x];
	else ++b[y],--a[x],ret=solve(),--b[y],++a[x];
	return ret;
}
void Main() {
	fastIO::read(n);fastIO::read(m);
	c.clear();
	REP(i,0,n)a[i]=b[i]=0;
	REP(i,0,n*2+2)cnt[i]=0;
    REP(i,0,n)visa[i]=visb[i]=0,h[i].clear(),nodes[i].clear();
	REP(i,0,m){
		int x,y;
		fastIO::read(x);fastIO::read(y);
		--x,--y;
		c.pb({x,y});
		++b[y];--a[x];
	}
	REP(i,0,n)a[i]+=n;
	int ans=solve();
	if(!ans){
		if(X==n-1||Y==n-1)over(0)
		int x=id1[X],y=id2[Y],f=0;
		for(auto i:c)if(i==make_pair(x,y)){f=1;break;}
		if(f){
			for(auto i:c)if(i.first==x)visb[i.second]=1;
			for(auto i:c)if(i.second==y)visa[i.first]=1;
			X=Y=-1;
			for(auto i:c)if(i.first!=x&&i.second!=y){
				if(!visa[i.first]&&!visb[i.second]){X=i.first,Y=i.second;break;}
			}
			if(X==-1)over(0);
		}else{
			X=Y=-1;
			for(auto i:c)h[i.first].pb(i.second);
			int sum=0;
			for(auto i:h[x])visa[i]=1,++sum;
			REP(i,0,n){
				int found=0;
				for(auto j:h[i])if(j==y){found=1;break;}
				if(!found)continue;
				vector<int>z;
				for(auto j:h[i])if(visa[j])visa[j]=0,--sum,z.pb(j);
				if(sum){
					X=i;
					REP(j,0,n)if(visa[j])Y=j;
					break;
				}
				for(auto j:z)++sum,visa[j]=1;
			}
			if(X==-1)over(0);
		}
		int x2=X,y2=Y;
		int ans=updater(x,y)+updater(x,y2)+updater(x2,y)+updater(x2,y2);
		cout<<(ans%MOD*qpow(n*n%MOD,MOD-2))%MOD<<endl;
		return;
	}
	REP(i,0,n)++cnt[d1[i]],++cnt[d2[i]];
	int res=0;
	(res+=ans*cnt[0]%MOD*(cnt[1]==1? cnt[2]+1:1))%=MOD;
	if(cnt[2]&&cnt[1])(res+=ans*(cnt[2]==1? cnt[3]+1:1))%=MOD;
	REP(i,2,2*n-1)if(cnt[i]&&cnt[i+1]){
		(res+=ans*(cnt[i+1]==1? cnt[i+2]+1:1)%MOD*(cnt[i]==1? cnt[i-1]+1:1))%=MOD;
	}
	cout<<res*qpow(n*n%MOD,MOD-2)%MOD<<endl;
}
void TC() {
	init(1000000);
	int tc=1;
	fastIO::read(tc);
	while(tc--) {
		Main();
		cout.flush();
	}
}
signed main() {
	return cin.tie(0),cout.tie(0),ios::sync_with_stdio(0),TC(),0;
}
/*
1. CLEAR the arrays (ESPECIALLY multitests)
2. DELETE useless output
 */
```

解法二：智慧地把行列按 $1$ 的个数排序（实际上等价于拓扑排序，所以桶排实现），发现合法当且仅当下一行包含前一行。方案数也是阶乘。原矩阵有解是类似的，原矩阵无解也是类似的（找到错误的两行，那四个点必须改）。精细实现时间复杂度 $O(n+m)$，实际上 $O((n+m)\log nm)$ 也能过。具体地，看验题人 `N_z__` 或者 `hyman00` 代码。

---

## 作者：Otomachi_Una_ (赞：0)

水题解/tuu

首先考虑如何计算一个网格的方案数。

建一个二分图，左右各有 $n$ 个节点。所有 $C_{i,j}=1$ 的 $i\to j$，否则 $i\leftarrow j$。

然后倒着来看，相当于拓扑序。然后最后只剩下孤立点的时候删点。

 首先，不能出现环。假设左右部点入度为 $i$ 的分别有 $cl_i,cr_i$，那么答案就是 $\prod_{i=1}^n cl_i!\times cr_i!$。

考虑原问题。

如果原图就有环了，那么交换的肯定是四个环节点之一，暴力计算即可。

否则，考虑每个左部点，他能够换向的肯定是上层不要的或者下层要的。然后对 $cl,cr$ 只有 $\mathcal O(1)$ 个变化。分类讨论一下即可。

时间复杂度：$\mathcal O(n\log n+m)$。

---

## 作者：N_z_ (赞：0)

### observation

考察一个给定的网格，刻画其合法性。我们断言，合法当且仅当按照行 size 排序之后，下包含上。

考察一个给定的合法网格，刻画其代价。注意到这等价于我们给出一个行列的排列，而当且仅当两行（列）完全相同的时候，它们的顺序是不固定的。特殊处理满行和空列，即可完成计数。

### sol

我们不妨将网格排序。分类讨论：

* 当原先不合法时：找到第一处 $a_{i+1}$ 不包含 $a_{i}$ 的位置，我们声称 $i+1$ 或者 $i$ 必须进行修改。做两次，分别为最终 $a_{i+1}$ 包含 $a_i$ 和 $a_i$ 包含 $a_{i+1}$。当其差集大小大于 $1$ 时无法修改，否则可能性仅有删除（加入）这个差的元素。暴力求值即可。

* 当原先合法时：可以方便的并起来行与列的等价类。对每个行等价类考察加数（删数）带来的贡献改变即可。

直接实现会是 $1\log$ 的。不难优化为 $O(n+m)$。

[code](https://codeforces.com/contest/2006/submission/278850075)。

---

## 作者：tzl_Dedicatus545 (赞：0)

### 2006F

好题。

首先注意到合法当且仅当存在一种方案使得每一行的 $1$ 全都包含于上一行。

记 $cr_i$ 为 $i$ 行 $1$ 的个数，$cc_i$ 为 $i$ 列 $1$ 的个数。

合法方案对应的染色方案个数显然就是 $cr$ 中相同值的个数的阶乘的乘积乘上 $cl$ 中相同值的个数的阶乘的乘积乘。

就是：

$$\prod(\sum_{i=1}^n \sum_{j=1}^n [cr_j=i])!\prod(\sum_{i=1}^n \sum_{j=1}^n [cc_j=i])!$$

正确性是容易证明的。

初始矩阵若合法，每次改一个数只会在相邻两行等价类产生贡献，改变 $O(1)$ 个值，算一下就行。

若不合法，则一共只有 $O(1)$ 个值可能使其变得合法（具体的，产生矛盾那两行的矛盾点），每种情况也用 $O(n+m)$ 的时间算一算就行。

总复杂度 $O(n\log n+m)$。

桶排序能做到 $O(n+m)$。

Code : <https://codeforces.com/contest/2006/submission/284009176>

---

