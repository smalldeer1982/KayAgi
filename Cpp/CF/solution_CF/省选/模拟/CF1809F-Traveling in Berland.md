# Traveling in Berland

## 题目描述

There are $ n $ cities in Berland, arranged in a circle and numbered from $ 1 $ to $ n $ in clockwise order.

You want to travel all over Berland, starting in some city, visiting all the other cities and returning to the starting city. Unfortunately, you can only drive along the Berland Ring Highway, which connects all $ n $ cities. The road was designed by a very titled and respectable minister, so it is one-directional — it can only be traversed clockwise, only from the city $ i $ to the city $ (i \bmod n) + 1 $ (i.e. from $ 1 $ to $ 2 $ , from $ 2 $ in $ 3 $ , ..., from $ n $ to $ 1 $ ).

The fuel tank of your car holds up to $ k $ liters of fuel. To drive from the $ i $ -th city to the next one, $ a_i $ liters of fuel are needed (and are consumed in the process).

Every city has a fuel station; a liter of fuel in the $ i $ -th city costs $ b_i $ burles. Refueling between cities is not allowed; if fuel has run out between cities, then your journey is considered incomplete.

For each city, calculate the minimum cost of the journey if you start and finish it in that city.

## 样例 #1

### 输入

```
4
3 5
3 4 4
1 2 2
5 7
1 3 2 5 1
2 1 1 1 2
4 3
1 2 1 3
2 2 2 2
3 2
2 2 2
1 2 1```

### 输出

```
17 19 17 
13 12 12 12 14 
14 14 14 14 
8 8 8```

# 题解

## 作者：Alex_Wei (赞：7)

[CF1809F Traveling in Berland](https://www.luogu.com.cn/problem/CF1809F)

因为油价只有 $1$ 或 $2$，所以遇到 $1$，我们一定能加满就加满，实在没油才会加 $2$。

不妨钦定到每个 $1$ 时油箱恰好为空。如果不为空，则当前油箱里的油的单价不小于 $1$，替换为当前城市的油不劣。

考虑从城市 $i$ 出发到另一个城市 $j$ 的代价 $f(i, j)$，满足中途没有 $1$，且出发前和到达后油箱均为空。设距离为 $d$。当出发城市油价为 $2$ 时，代价为 $2d$。当出发城市油价为 $1$ 时，若 $d\leq k$，代价为 $d$，否则代价为 $2d - k$。

破环成链，考虑 $i\to i + n$ 中途的所有油价为 $1$ 的城市 $p_1, p_2, \cdots, p_k$，则 $f(i, p_1) + f(p_k, i + n) + \sum_{j = 1} ^ {k - 1} f(p_j, p_{j + 1})$ 即为所求。

倍增，设 $f_{i, j}$ 表示从 $j$ 出发跳 $2 ^ i$ 步（每一步跳到下一个 $1$）到达的城市及对应代价。时间复杂度 $\mathcal{O}(n\log n)$。[代码](https://codeforces.com/contest/1809/submission/199348463)。

因为出发城市和到达城市单调增，所以双指针维护可做到 $\mathcal{O}(n)$。

---

## 作者：honglan0301 (赞：4)

## 题目分析

一个简单的 $O(n)$ 做法，这真的是 $\text{*2500}$ 而不是 $\text{*2000}$ 吗？

先断环成链，并记 $s_i=\sum\limits_{j=0}^{i-1} a_i$。因为油价只有两种，所以一定碰到便宜的就加满（或者恰好到终点时用完），其余情况加贵的。转化一下，我们只需求出一路上总共能加多少升便宜的油，又也就是一路上有多少个位置能用上便宜的油，设为 $ans$，则答案就是 $2\sum a_i-ans$。

而容易发现只有距上一个 $b_i=1$ 的加油站距离 $<k$ 的位置才满足要求，于是变成每个 $b_i=1$ 的加油站能够覆盖 $[s_i,s_i+k-1]$ 这些点，每次询问 $[s_i,s_i+\sum a_i-1]$ 有多少个点会被覆盖的问题（注意 $j<i$ 的加油站 $j$ 不能用）。

发现这些线段都不存在包含关系，于是直接从头到尾扫一遍，只需支持删除最前面的线段和插入最后面的线段。前者预处理出 $nxt_i=\min\limits_{b_j=1,j>i} {j}$ 后做到 $O(1)$，后者维护一下当前最右侧的线段覆盖到了哪里也可以 $O(1)$，故总时间复杂度 $O(n)$，且代码很好写。

## 代码

```cpp
/*
  author: PEKKA_l  
 */
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
#define int long long

int t,n,k,a[400005],s[400005],b[400005],nxt[400005],nans,nr;
void ins(int x)
{
	if(nr>=s[x]) nans+=min(nr,s[x+1]-1)-(s[x]-1);
	if(b[x]==1) {nans+=min(s[x]+k-1,s[x+1]-1)-min(s[x+1]-1,max(nr,s[x]-1)); nr=s[x]+k-1;}
}
void del(int x)
{
	if(b[x]==1)
	{
		nans-=min(s[x]+k-1,s[x+1]-1)-(s[x]-1);
		if(s[x]+k-1>=s[x+1]) nans-=min(s[x]+k-1,s[nxt[x]]-1)-(s[x+1]-1);
	}
}

signed main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>k; int sum=0; nans=0,nr=-1;
		for(int i=1;i<=n;i++) cin>>a[i],a[n+i]=a[i],sum+=a[i];
		for(int i=1;i<=n;i++) cin>>b[i],b[n+i]=b[i];
		for(int i=2;i<=2*n;i++) s[i]=s[i-1]+a[i-1]; int nw=2*n+1; s[nw]=1e18;
		for(int i=2*n;i>=1;i--) {nxt[i]=nw; if(b[i]==1) nw=i;}
		for(int i=1;i<=n;i++) ins(i);
		cout<<2*sum-nans<<" ";
		for(int i=1;i<=n-1;i++) {del(i); ins(n+i); cout<<2*sum-nans<<" ";}
		cout<<endl;
	}
}
```


---

## 作者：shipeiqian (赞：2)

# CF1809F

## 题意

有一个长度为 $n$ 的环，到第 $i$ 个点需要 $a_i$ 升油，第 $i$ 个点有一个油价为 $b_i$ 的加油站，车的油箱最多装 $k$ 升油，求从 $i$ 到 $i$ 这一圈最少用几升油。

$b_i \in [1,2]$

## 思路

可以发现 $b_i$ 只有 $1$ 和 $2$ 两个值，所以可以用贪心的思想得出在油价为 $1$ 的加油站加满油，其他的加到够用为止。但是这样可能会有剩余或者出现油不够，但要加很多贵油的情况，所以可以用 dp。

dp 只需要一维，表示从第 $1$ 个位置到第 $i$ 个位置最少要多少钱。

还需要一个数组 $sh$ 来记录剩余的油量，保证不会多加油。

如果剩余的油可以到达第 $i$ 个位置，那么就在前面多加一些便宜油，花费的钱就是前一个位置的钱加上到第 $i$ 个位置的钱。

$$dp_i=dp_{i-1}+a_{i-1}$$

否则就不够了，就要加贵的油，贵的油需要 $a_{i-1}-sh_{i-1}$ 升。

$$dp_i=dp_{i-1}+(a_{i-1}-sh_{i-1})*2+sh_{i-1}$$

然后修改 $sh$，如果油价是 $1$，那就加满，$sh_i=k$，否则就是 $sh_i=sh_{i-1}-a_{i-1}$

答案就是从 $1$ 到 $n+i$ 的钱减去从 $1$ 到 $i$ 的钱，再加上剩余的油的钱。

## AC Code

```cpp
#include <bits/stdc++.h>
#define de "debug"
using namespace std;
typedef long long ll;
const int N=400005;
ll n,k,a[N],b[N],dp[N],nxt[N],sh[N];
void solve(){
    cin >>n >>k;
    for(int i=1;i<=n;i++)cin >>a[i];
    for(int i=1;i<=n;i++)cin >>b[i];
    for(int i=n+1;i<=n*2;i++)a[i]=a[i-n],b[i]=b[i-n];//是一个环，所以把两个拼在一起
    for(int i=1;i<=n*2;i++){
        if(sh[i-1]>=a[i-1])dp[i]=dp[i-1]+a[i-1];
        else dp[i]=dp[i-1]+a[i-1]*2-sh[i-1];
        if(b[i]==1)sh[i]=k;
        else sh[i]=max(sh[i-1]-a[i-1],0ll);
    }
    ll cnt=0;
    for(int i=n*2;i>=1;i--){
        if(b[i]==1)cnt=0;
        else cnt+=a[i];
        nxt[i]=cnt;
    }
    for(int i=1;i<=n;i++){
        cout <<dp[i+n]-dp[i]+min(sh[i],nxt[i]) <<" ";
    }
}
int main(){
    int T=1;
    cin >>T;
    while(T--)solve();
    return 0;
}
```

---

## 作者：六楼溜刘 (赞：2)

## 题意
- 你在一个有 $n$ 个点的环上顺时针前进，环上第 $i$ 个点有两个权值 $a_i,b_i$，分别代表从点 $i$ 到点 $i+1 \bmod n$ 的消耗的油和点 $i$ 处的油价。你的车的油箱最多只能装 $k$ 升油，问从每个点开始顺时针转一圈返回这个点的最小消耗。
- $3 \leq n \leq 2\times 10^5,1\leq k \leq 10^9,1\leq a_i\leq k,1\leq b_i\leq2$

## 题解
首先，这是个环上问题，我们考虑断环成链求解。故原问题转化成对于所有 $1\leq i\leq n$，从 $i$ 城市到 $i+n$ 城市的最小消耗

我们发现 $1\leq b_i\leq2$，由于要使消耗最小，我们尽量在 $b_i=1$ 的城市加油。

我们考虑从一个油价为 $1$ 的城市到极近的下一个油价为 $1$ 的城市的最小代价。

此时我们考虑的范围必然是形如 `1 2 2 2 1` 的一段序列，分两种情况讨论。为方便叙述，我们称当前油价为 $1$ 的城市为 $u$，下一个为 $v$。

1. $k$ 大于等于从 $u$ 到 $v$ 的消耗，我们可以恰好加等量于消耗的油然后直接前往 $v$。
1. $k$ 小于从 $u$ 到 $v$ 的消耗，我们可以直接加满油，然后再中途补充尽量少的油，即恰好足够到达 $v$ 的油，由于中间城市的油价均为 $2$，我们甚至可以不用考虑油箱的容量问题，直接在答案中加上需要额外补充的油量的两倍，只关心结果，不关心过程中具体在哪里加。

我们已经学会处理两个 $1$ 之间的情况了，注意到我们每次会从这个 $1$ 转移到下一个 $1$，并且不会重复计算，这种单向跳的形式让我们想到使用[倍增](https://oi-wiki.org/basic/binary-lifting/)维护每个 $1$ 到达后面的 $1$ 所需的代价。

另外，我们可能会从某个 $2$ 开始旅行，此时我们额外计算一下开头和结尾两段即可。

可以利用前缀和 $O(1)$ 求出两点之间的消耗，故预处理复杂度为 $O(n\log n)$，对于 $n$ 个点，每个点只需要 $O(\log n)$ 即可求出结果，故总复杂度为 $O(n \log n)$，可以通过此题。

## code
```cpp
#include<iostream>
#include<algorithm>
#include<string.h>
#define int long long
#define mem(a,b) memset(a,b,sizeof(a))
#include<vector>
#define pbk(a) emplace_back(a)
#define forup(i,s,e) for(register int i=(s);i<=(e);i++)
#define fordown(i,s,e) for(register int i=(s);i>=(e);i--)
using namespace std;
#define gc getchar()
inline int read(){//快读
    int x=0,f=1;char c;
    while(!isdigit(c=gc)) if(c=='-') f=-1;
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=gc;}
    return x*f;
}
#undef gc
const int N=4e5+5,inf=0x3f3f3f3f;
int t,n,k,a[N],b[N],nxt[N],f[N][25],cst[N][25],sum[N];
vector<int> pos;
signed main(){
	t=read();
	while(t--){
		n=read();k=read();
		pos.clear();//多测不清空，爆零两行泪
		forup(i,1,n){
			a[i]=read();
			a[i+n]=a[i];
		}
		forup(i,1,n){
			b[i]=read();
			b[i+n]=b[i];
		}
		forup(i,1,n*2){
			sum[i]=sum[i-1]+a[i-1];
			forup(j,0,20){//不要用 memset 初始化，它是 O(n) 的，会 TLE
				f[i][j]=0;
			}
		}
		int bef=n*2;//初始设为末尾，不会影响答案
		for(int i=n*2;i>=1;i--){
			if(b[i]==1){
				bef=i;
				pos.pbk(i);
			}
			nxt[i]=bef;
		}
		forup(i,1,(int)pos.size()-1){
			int v=pos[i],u=pos[i-1];
			f[v][0]=u;
			cst[v][0]=(k>=sum[u]-sum[v]?sum[u]-sum[v]:k+(sum[u]-sum[v]-k)*2);
			forup(j,1,20){
				f[v][j]=f[f[v][j-1]][j-1];
				cst[v][j]=cst[v][j-1]+cst[f[v][j-1]][j-1];
                //算位置的同时计算代价
			}
		}
		forup(i,1,n){
			int nw=min(nxt[i],i+n),ans=(sum[nw]-sum[i])*2;
			for(int j=20;j>=0&&f[nw][0]<=i+n;j--){//倍增
				if(f[nw][j]<=i+n&&f[nw][j]!=0){
					ans+=cst[nw][j];
					nw=f[nw][j];
				}
			}
			ans+=(k>=sum[i+n]-sum[nw]?sum[i+n]-sum[nw]:k+(sum[i+n]-sum[nw]-k)*2);
			printf("%lld ",ans);
		}
		puts("");
	}
}
```


---

## 作者：Unnamed114514 (赞：1)

1h 秒了，感觉挺水啊。

贪心策略见[旅行家的预算](https://www.luogu.com.cn/problem/P1016)，此处不再赘述。

套路地，先破环为链，问题转化为 $i\to i+n$。

显然我们可以用三元组表示出每个点出去的状态 $(pos,rest,cost)$，$pos$ 表示要到的点，$rest$ 表示到 $pos$ 后剩余的油量，$cost$ 表示油量的花费。

然后我们可以得到一个 $O(n^2)$ 的做法，即每次直接暴力往 $pos$ 跳直到 $pos\ge i+n$ 时，因为往 $pos$ 跳一定是不劣的。然后暴力跳 $pos$ 的贡献很好算，最后跳到 $i+n$ 的贡献也很好算。

还有一个事情是我们需要考虑 $rest$ 和 $dis(lastpos,i+n)$ 的大小（其中 $lastpos$ 表示最后一次跳到的 $pos$），因为 $b$ 只有 $1$ 和 $2$，发现 $rest$ 有值的时候当且仅当它跳到了它最右边的 $2$，由于 $i+n>lastpos$ 所以显然跳不到 $i+n$，否则 $lastpos>i+n$，因此 $rest<dis(lastpos,i+n)$，直接暴力算贡献是对的。（如果没有 $b\le 2$ 的限制的话显然如果 $b_{lastpos}<b_{i+n}$ 那么可能会出现 $i+n$ 可达的情况，那么就变麻烦了，同时这也是前面跳的时候是 $<$ 而不是 $\le$ 的原因）

如果我们把图建出来的话，我们会发现这是一棵树，并且在 $root=2n$ 的情况下问题转化成了一直往祖先跳直到 $\ge i+n$，树上倍增优化即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define inf 0x3f3f3f3f3f3f3f3fLL
#define endl '\n'
using namespace std;
const int N=4e5+5;
int T,n,k,a[N],b[N],s[N],suf[N],to[20][N],w[20][N],r[20][N];
struct Node{ int pos,rest,cost; }p[N];
int get_dis(int l,int r){ return s[r-1]-s[l-1]; }
int solve(int i){
	int x=i,rest=0,sum=0;
	for(int k=__lg(n<<1);~k;--k) if(to[k][x]&&to[k][x]<i+n) sum+=(w[k][x]-rest*b[x]),rest=r[k][x],x=to[k][x];
	return sum+(get_dis(x,i+n)-rest)*b[x];
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>k;
		for(int i=1;i<=n;++i) cin>>a[i],a[i+n]=a[i];
		for(int i=1;i<=n;++i) cin>>b[i],b[i+n]=b[i];
		for(int i=1;i<=(n<<1);++i) s[i]=s[i-1]+a[i];
		int lst=-1;
		for(int i=(n<<1);i;--i){
			suf[i]=lst;
			if(b[i]==1) lst=i;
		}
		for(int i=1;i<(n<<1);++i){
			int l=i+1,r=(n<<1);
			while(l<r){
				int mid=l+r+1>>1;
				if(get_dis(i,mid)<=k) l=mid;
				else r=mid-1;
			}
			if(~suf[i]&&suf[i]<=r) p[i]={suf[i],0,get_dis(i,suf[i])};
			else p[i]={r,k-get_dis(i,r),k};
		}
		p[n<<1]={0,0,0};
		for(int i=1;i<=(n<<1);++i) to[0][i]=p[i].pos,w[0][i]=p[i].cost*b[i],r[0][i]=p[i].rest;
		for(int i=1;i<=__lg(n<<1);++i) for(int j=1;j<=(n<<1);++j){
			to[i][j]=to[i-1][to[i-1][j]];
			r[i][j]=r[i-1][to[i-1][j]];
			w[i][j]=w[i-1][j]+w[i-1][to[i-1][j]]-r[i-1][j]*b[to[i-1][j]];
		}
		for(int i=1;i<=n;++i) cout<<solve(i)<<' ';
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：SamHJD (赞：0)

贪心策略显然为遇到 $b_i=1$ 就加满油，否则加至刚好能开到下一处加油站。

钦定 $b_i=2$ 的加油站的下一步为 $i+1$，$b_i=1$ 的加油站若能加满油走到第一个 $b_j=1$ 的加油站则 $i$ 的下一步为 $j$，否则先加满油走到一个最远的 $b_j=2$ 的加油站再加油使刚好能到 $j+1$，$i$ 的下一步为 $j+1$。

计算每个加油站走一步的花费，由于其符合贪心策略，且每走一步油量都会耗尽，故可以倍增。

倍增走到最后一步时用上面的方法再特判一次代价即可。

[code](https://codeforces.com/contest/1809/submission/306501621)

---

## 作者：Li_Yichen (赞：0)

首先看到在环上，考虑断环成链，把原数组在后面再拼接一次，相当于把长度为 $n$ 的数组变为了 $2\times n$，此时从当前的 $i$ 点出发，回到点 $i$，就变成了从点 $i$ 出发，到达 $i+n$。注意要开两倍数组，$n$ 也要变为两倍。

然后观察数据范围，发现 $1\le b_{i} \le 2$ 且 $b_{i}$ 为整数，此时运用贪心的思想，如果 $i$ 号点的油价 $b_{i} = 1$，那么我们一定加满。否则遇到价格高的情况，除非已经跑不了了，我们才加更贵的油，此时只要加到能够跑就可以了。也就是说，如果一定要加价格高的油，只要加能跑就行，价格低的油可以越多越好。

考虑用动态规划计算答案。定义 $dp_{i}$ 表示从 $1$ 位置到 $i$ 位置的最少油耗，用 $pre_{i}$ 来储存剩余的油，注意此时因为断环成链之后，$i$ 满足 $1\le i\le 2\times n$。

如果能直接从 $i-1$ 到达 $i$，即用剩余的油就能跑到，按照贪心策略，我们直接加能够到达 $i$ 位置且价格低的油，此时 $dp_{i} = dp_{i-1} + a_{i-1}$。如果不可以，那么就只能加贵的油，只要加到能跑到 $i$ 就可以了，注意还有上一次剩下的油，虽然不能跑，但是再次加就不需要加这一部分了，此时需要 $a_{i-1} - pre_{i-1}$ 的价格高的油。此时 $dp_{i} = dp_{i-1} + 2\times (a_{i-1} - pre_{i-1}) + pre_{i-1}$。

考虑计算 $pre$ 随着跑动而变化的量。如果价格低，那么我们按照贪心策略，直接买满，此时 $pre_{i} = k$，否则 $pre_{i-1}$ 也要作为跑的时候消耗的油，那么 $pre_{i-1}$ 要减去 $a_{i-1}$，这里注意如果 $pre_{i-1}$ 不够跑 $a_{i-1}$ 的，那么需要额外买，那么此时 $pre_{i} = 0$，计算时相当于 $pre_{i} = \max(pre_{i-1}-a_{i-1},0)$。

线性动态规划，单次时间复杂度 $O(n)$，注意要开 long long，[AC代码](https://codeforces.com/contest/1809/submission/274096296)。

---

## 作者：Raisetsu41 (赞：0)

首先看到 $b_i \in [1, 2]$，这明显是一个值得去发现性质的点。因为油箱容量不变（废话），所以遇到 $1$ 能加满就加满，只有在实在没油的情况下才会去加 $2$。发现这个合并并不是那么优美，因为每次剩下的油量都不一样，那么考虑每次都在油箱空了的时候去合并。  

- 如果当前 $b_i = 1$ 

  - 并且 $b_{i + 1} \not = 2$，直接交完当前需要的油钱，移动到下一个位置。

  - 否则后面将会有 $len$ 个连续的 $2$，对于这一段区间记为 $[i + 1, i + len]$，记 $a_i$ 的前缀和数组为 $sum$，需要二分出第一个 $pos$，使得 $sum[i + 1 \dots pos] \le k$，那么这一段区间的所有油都应该在 $i$ 处只花 $1$ 的代价加上，这是就会出现后面一段 $[pos + 1, i + len]$ 的油不够，那么这一段只能花 $2$ 的代价买油。

- 如果当前 $b_i = 2$，直接交 $2 \times a_i$，往下移动。

于是得到了从每一个点出发走一步在最优情况下能够到达的位置记为 $nxt_{pos, 0}$，显然这是一个倍增数组。  

最后会发现一个小问题，在倍增完之后有可能到不了终点，并且这一段是连续的 $1$，那么直接计算两者之间的距离就能解决了。

---

## 作者：SkyRainWind (赞：0)

[my blog](https://www.cnblogs.com/SkyRainWind/p/17255212.html)

提供一个官方题解的做法。

对一个点，考虑怎样在 $O(\log n)$ 的时间复杂度内求出答案，联想到倍增。

但是，倍增合并的时候只能在两个**状态相同**的情况下合并，但是如果我们直接从 $i$ 到 $i+1$ 这样算的话，每次剩余的油量是不同的，很难合并。

考虑如果将每次剩余油量都设为 0 的话，就比较容易合并了。

- 如果当前位置 $b_i=2$，那么直接付清 $2\times a_i$ 的钱，然后移动到下一个
- 如果当前位置 $b_i=1$，且往后第一个不是 $2$，那么付清 $a_i$ 的钱，然后移动到下一个。

- 否则，比如说有 $k$ 个连续的 $2$，考虑二分出第一个 $sum[l..r] \geq k$ 的 $r$，显然在 $b_i$ 处先加满油最优，那么到了 $r$ 处可能刚好够用，也可能需要再买一些。如果需要再买一些的话，显然就是 $2\times (sum[l..r]-k)$ 的额外价格。

这样一来，我们就求得了 $dist[i][0]$ 代表 $i$ 往后移动 $2^0$ 次的距离，已经此时的价格，倍增即可。

对于每个 $i$，查询的时候就倍增往后跳，注意可能出现没跳完的情况，即某一次 $i$ 即使是 $dist[i][0]$ 也 < 剩余的距离（这是有可能的，因为我们每次 $dist$ 都是取的最大值），容易发现此时当前位置一定为 $b_i=1$，直接求出二者的距离，在 $b_i=1$ 处买即可。

细节很多，调吐了。

```cpp
// by SkyRainWind
#include <bits/stdc++.h>
#define mpr make_pair
#define debug() cerr<<"Yoshino\n"
#define pii pair<int,int>
#define pb push_back

using namespace std;

typedef long long ll;
typedef long long LL;

const int inf = 1e9, INF = 0x3f3f3f3f, maxn = 4e5+5;

int n,k;
int a[maxn], b[maxn];
ll dist[maxn][20], cost[maxn][20], sum[maxn];

int md(int x){
	if(x <= n)return x;
	return x-n;
}

void solve(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]), a[i+n] = a[i];
	for(int i=1;i<=n;i++)scanf("%d",&b[i]), b[i+n] = b[i];
	
	sum[0] = 0;
	for(int i=1;i<=2*n;i++)sum[i] = sum[i-1] + a[md(i)];
	
	int cnt = 0;
	
	for(int i=2*n;i>=1;i--){
		if(b[i] == 2){
			cost[i][0] = 2*a[i];
			dist[i][0] = 1;
		}else if(cnt == 0){
			cost[i][0] = a[i];
			dist[i][0] = 1;
		}else{
			int to = lower_bound(sum+i, sum+i+cnt+1, sum[i-1] + k) - sum;
			if(to == i+cnt+1){
				cost[i][0] = sum[i+cnt] - sum[i-1];
				dist[i][0] = cnt+1;
			}else{
				int delt = to - i;
				if(sum[to] == sum[i-1] + k){
					cost[i][0] = k;
					dist[i][0] = delt+1;
				}else{
					cost[i][0] = k + 2 * (sum[to] - sum[i-1] - k);
					dist[i][0] = delt+1;
				}
			}
		}
		if(b[i] == 2)++ cnt;
		else cnt = 0;
	}
	
	for(int j=1;j<=18;j++)
		for(int i=1;i<=n;i++){
			dist[i][j] = dist[i][j-1] + dist[md(i + dist[i][j-1])][j-1];
			cost[i][j] = cost[i][j-1] + cost[md(i + dist[i][j-1])][j-1];
		}
	
	for(int i=1;i<=n;i++){
		ll r = 0, now = i;
		int tot = 0;
		for(int j=18;j>=0;j--){
			if(tot+dist[now][j] <= n)
				r += cost[now][j],
				tot += dist[now][j],
				now = md(now + dist[now][j]);
		}
		if(tot < n){
			r += sum[i+n-1] - sum[i+tot-1];
		}
		printf("%lld ",r);
	}
	puts("");
}

signed main(){
	int te;scanf("%d",&te);
	while(te --)solve();

	return 0;
}

```

---

## 作者：Leasier (赞：0)

首先断环为链，现在我们考虑一个区间 $[l, r]$ 的情况怎么做。

注意到 $1 \leq b_i \leq 2$，则我们可以将答案视为两部分构成：

- 因为 $b_i \geq 1$，所以对每升油至少都需要 $1$ 的代价，即 $\displaystyle\sum_{i = l}^r a_i$。
- 接下来考虑 $b_i = 2$，对于一个极长的连续段 $(1)222 \cdots 2$（若 $b_l = 2$ 则没有前面的 $1$），我们会在第一个位置尽量加满油，后面实在不行了再说，当 $b_l = 1$ 为 $\max(\displaystyle\sum_{i = l}^r a_i - k, 0)$，否则为 $\displaystyle\sum_{i = l}^r a_i$。

预处理出所有连续段的信息并特判第一个和最后一个可能不完整的连续段即可。时间复杂度为 $O(\sum(n + q))$。~~我的实现中偷了个懒写了 $O(\sum(n + q \log n))$。~~

代码：
```cpp
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

int a[400007], b[400007], belong[400007], l[200007], r[200007];
ll sum1[400007], sum2[200007];

inline ll calc(int l, int r, int k, bool op){
	if (b[l] == 1 || !op) return max(sum1[r] - sum1[l - 1] - k, 0ll);
	return sum1[r] - sum1[l - 1];
}

int main(){
	int t;
	cin >> t;
	for (int i = 1; i <= t; i++){
		int n, k, m, cnt = 0;
		ll sum = 0;
		cin >> n >> k;
		m = n * 2;
		for (int j = 1; j <= n; j++){
			cin >> a[j];
			sum += a[j];
		}
		for (int j = 1; j <= n; j++){
			cin >> b[j];
		}
		for (int j = 1; j <= n; j++){
			a[j + n] = a[j];
			b[j + n] = b[j];
		}
		for (int j = 1; j <= m; j++){
			belong[j] = 0;
			sum1[j] = sum1[j - 1] + a[j];
		}
		for (int j = 1; j <= m; j++){
			if (b[j] == 2){
				cnt++;
				l[cnt] = max(j - 1, 1);
				r[cnt] = j;
				while (r[cnt] < m && b[r[cnt] + 1] == 2) r[cnt]++;
				sum2[cnt] = sum2[cnt - 1] + calc(l[cnt], r[cnt], k, false);
				for (int x = l[cnt]; x <= r[cnt]; x++){
					belong[x] = cnt;
				}
				j = r[cnt];
			}
		}
		cnt++;
		l[cnt] = r[cnt] = 1e9;
		sum2[cnt] = 0;
		for (int j = 1, x = n; j <= n; j++, x++){
			if (belong[j] != 0 && belong[j] == belong[x]){
				cout << sum + calc(j, x, k, true) << " ";
			} else {
				cout << sum + (sum2[lower_bound(r + 1, r + cnt + 1, x) - r - 1] - sum2[upper_bound(l + 1, l + cnt + 1, j) - l - 1]) + (belong[j] != 0 ? calc(j, r[belong[j]], k, true) : 0) + (belong[x] != 0 ? calc(l[belong[x]], x, k, false) : 0) << " ";
			}
		}
		cout << endl;
	}
	return 0;
}
```

---

## 作者：PosVII (赞：0)

**前言**

------------

差两分钟场切，呜呜呜。

**正文**

------------

发现这个题有一个极其显然的贪心，我们遇到 $b_{i}=1$ 的点就装满油，遇到 $b_{i}=2$ 的点能不买油就不买，最后剩下的油一定是在 $b_{i}=1$ 的点买的，退了就是。

但是很不爽啊，我们要询问 $n$ 次，于是考虑如何存储答案。考虑倍增，设 $f_{i,j}$ 为从第 $i$ 个点空油走 $2^j$ 步使用的最小代价，$g_{i,j}$ 为从第 $i$ 个点空油走 $2^j$ 步后剩下的油。

考虑如何合并，发现对于从第 $i$ 个点空油走 $2^j$ 步，我们走到 $2^{j-1}$ 次方步后留下的油仅能对接下来连续 $b_{k}=2$ 的点作贡献，因为遇到 $b_{k}=1$ 的点后无论是留下的油还是新买的油都混一起了。

于是在合并时只需要考虑前方第一个 $b_{k}=1$ 的点和此时留下的油量够不够，具体实现可看代码。

**code**

------------

```
#include<bits/stdc++.h>
template<typename G>inline void read(G&x) {G f=1;x=0;char ch=getchar();while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();if(ch=='-') f=-1,ch=getchar();while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=getchar();x*=f;}
using namespace std;
#define int long long
const int MAXN=4e5+5;
int T,n,k,a[MAXN],b[MAXN],f[MAXN][20],g[MAXN][20],las[MAXN];
signed main() {
	read(T);
	while(T--) {
		read(n),read(k);
		for(int i=1;i<=n;++i) read(a[i]),a[i+n]=a[i];
		for(int i=1;i<=n;++i) read(b[i]),b[i+n]=b[i];
		n*=2;
		for(int i=1;i<=n;++i) {
			las[i]=0;
			a[i]+=a[i-1];
		}
		for(int i=n;i>=1;--i) {
			if(b[i]==1) las[i]=i;
			else if(i!=n) las[i]=las[i+1];
		}
		for(int i=1;i<=n/2;++i) las[i+n/2]=las[i]+n/2;
		if(!las[1]) {
			for(int i=1;i<=n/2;++i) printf("%lld ",a[n]);
			puts("");
			continue;
		}
		for(int i=1;i<=n;++i) {
			if(b[i]==1) {
				f[i][0]=k;
				g[i][0]=k-(a[i]-a[i-1]);
			}
			else {
				f[i][0]=2*(a[i]-a[i-1]);
				g[i][0]=0;
			}
		} 
		for(int j=0;(1<<(j+1))<=n/2;++j) {
			for(int i=1;i+(1<<(j+1))-1<=n;++i) {
				int t=i+(1<<j),tt=t+(1<<j),nxt=min(tt,las[t]);
				if(t>las[t]-1) f[i][j+1]=f[i][j]+f[t][j]-g[i][j],g[i][j+1]=g[t][j];
				else {
					if(nxt==tt) f[i][j+1]=f[i][j]+f[t][j]-2*min(g[i][j],a[nxt-1]-a[t-1]),g[i][j+1]=g[i][j]-min(g[i][j],a[nxt-1]-a[t-1]);
					else f[i][j+1]=f[i][j]+f[t][j]-g[i][j]-min(g[i][j],a[nxt-1]-a[t-1]),g[i][j+1]=g[t][j];
				}
			}
		}
		for(int i=1;i<=n/2;++i) {
			int nowf=0,nowg=0,now=i;
			for(int j=0;(1<<j)<=(n/2);++j) {
				if((n/2)>>j&1) {
					int t=now+(1<<j),nxt=min(t,las[now]);
					if(now>las[now]-1) nowf+=f[now][j]-nowg,nowg=g[now][j];
					else {
						if(nxt==t) nowf+=f[now][j]-2*min(nowg,a[nxt-1]-a[now-1]),nowg-=min(nowg,a[nxt-1]-a[now-1]);
						else nowf+=f[now][j]-nowg-min(nowg,a[nxt-1]-a[now-1]),nowg=g[now][j];
					}
					now=t;
				}
			}
			printf("%lld ",nowf-nowg);
		}puts("");
	}
	return 0;
}
```

---

