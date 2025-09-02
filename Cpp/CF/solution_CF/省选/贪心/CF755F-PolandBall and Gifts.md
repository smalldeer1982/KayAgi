# PolandBall and Gifts

## 题目描述

It's Christmas time! PolandBall and his friends will be giving themselves gifts. There are $ n $ Balls overall. Each Ball has someone for whom he should bring a present according to some permutation $ p $ , $ p_{i}≠i $ for all $ i $ .

Unfortunately, Balls are quite clumsy. We know earlier that exactly $ k $ of them will forget to bring their gift. A Ball number $ i $ will get his present if the following two constraints will hold:

1. Ball number $ i $ will bring the present he should give.
2. Ball $ x $ such that $ p_{x}=i $ will bring his present.

What is minimum and maximum possible number of kids who will not get their present if exactly $ k $ Balls will forget theirs?

## 说明/提示

In the first sample, if the third and the first balls will forget to bring their presents, they will be th only balls not getting a present. Thus the minimum answer is $ 2 $ . However, if the first ans the second balls will forget to bring their presents, then only the fifth ball will get a present. So, the maximum answer is $ 4 $ .

## 样例 #1

### 输入

```
5 2
3 4 1 5 2
```

### 输出

```
2 4```

## 样例 #2

### 输入

```
10 1
2 3 4 5 6 7 8 9 10 1
```

### 输出

```
2 2```

# 题解

## 作者：未来姚班zyl (赞：13)

题解区的复杂度分析都好奇怪啊，来个正确的复杂度分析！

## 题目大意

题目翻译已经足够清晰了。

## 题目分析

首先，建边 $i\rightarrow p_i$，则每个点的出度、入度都为 $1$，故图由若干个环组成。

首先考虑第一问：求花费 $k$ 得到最大的贡献。

显然，对于长度为 $len$ 的环，可以花费 $i\le \lfloor\frac{len}{2}\rfloor$ 的代价，获得 $2i$ 的贡献，如果 $len$ 是奇数，还可以在此基础上再花费 $1$ 的代价，获得 $1$ 的贡献。直接贪心即可，复杂度 $O(n)$。

然后就是第二问：花费 $k$ 能得到的最小代价。

对于长度为 $len$ 的环，第一次花费 $1$ 一定会产生 $2$ 的代价。然后第 $2\sim len-1$ 次花费会产生 $1$ 的代价，第 $len$ 次产生 $0$ 的代价。

所以如果能用若干个环恰好拼出 $k$ 答案就是 $k$，否则是 $k+1$。

问题变为 $len_i$ 能否拼出 $k$，典型的背包问题。

$\sum len_i=n$，这使得 $len_i$ 只有 $O(\sqrt n)$ 种。

采用二进制分组，对于种类数 $x$，最坏的情况下数量平均，二进制分组后物品数量应为 $O(x\log\frac{n}{x^2})$，我在 geogebra 上输入该函数并发现最差复杂度应为 $O(\sqrt n)$，至少在 $n\le 10^6$ 时这个结论是正确的，欢迎数学大佬来证明或指错。

所以再使用 bitset 背包，复杂度 $O(\frac{n\sqrt n}{w})$。

题解那些不认真分析复杂度的都能有高赞？
```cpp
#include<bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
using namespace std;
const int N =1e6+5;
int a[N],n,k,m,p[N];
bool v[N];
inline void dfs(int x,int &w){
	w++,v[x]=1;
	if(!v[p[x]])dfs(p[x],w);
}
inline int solve1(int k){
	int ans=0;
	repm(i){
		int w=a[i]/2;
		ans+=min(w,k)*2,k-=min(w,k);
		if(!k)return ans;
	}
	repm(i)if(a[i]&1){
		k--,ans++;
		if(!k)return ans;
	}
	return ans;
}
int c[N];
bitset<500001>B;
inline int solve2(int k){
	int pr=k;
	k=min(k,n-k),B[0]=1;
	repm(i)c[a[i]]++;
	rep(i,1,k)if(c[i]){
		int kk=1,w=i;
		while(1){
			if(c[i]>=kk)B=B|(B<<w),c[i]-=kk;
			else {
				B=B|(B<<(c[i]*i));
				break;
			}
			kk<<=1,w<<=1;
		}
	}
	return pr+(!B[k]);
}
int main(){
	n=read(),k=read();
	repn(i)p[i]=read();
	repn(i)if(!v[i])dfs(i,a[++m]);
	cout <<solve2(k)<<" "<<solve1(k)<<'\n';
	return 0;
}
```

---

## 作者：do_while_true (赞：4)

orz qyc

[来我的cnblogs中获得~~应该会~~更好的体验](https://www.cnblogs.com/do-while-true/p/15047873.html)

看成一个人 $i$ 向 $p_i$ 连边，每个点的入度出度都为 $1$ 。那么就是若干个环，每次可以选择一条边将这条边两端的端点染色，求 $k$ 次染色后，最大和最小有颜色点的个数数。

最大值发现可以贪心，偶数长度的环可以用长度除以 $2$ 次染色全部染色，每次染色的贡献都拉满了。奇数长度的环可以用长度减一除以 $2$ 次染色将除了一个点其他全部染色，剩下的一个点最后还有染色机会再染。

最小值的话，每个环第一次开始染它色一定是贡献为 $2$，基于贪心先不开其他的环，再继续对这个环染色，每次贡献为 $1$，到最后一步贡献为 $0$。换而言之，开了一个环就将它染色到底。

发现对于一个长度为 $a_i$ 的环，将其全部染色次数为 $a_i$，贡献为 $a_i$。那么一定想让若干个 $a_i$ 组成 $k$，否则 $k$ 多开的没染完色的那个环会多贡献 $1$。

问题转化为给定若干个正整数 $a_i$，其和为 $n$，问能不能挑出一些 $a_i$ 使得和为 $k$。也就是 01 背包可行性问题。

发现 ```bitset``` 和分治 NTT 都不大能过，注意到对 $a_i$ 总和的限制，不同的 $a_i$ 仅有 $\mathcal{O}(\sqrt{n})$ 个，把多个同样的物品合成一个物体有不同的次数，就变成了一个多重背包问题。

再加个二进制分组优化，时间复杂度大概是个 $\mathcal{O}(n\sqrt n\log n/w)$，加上那个 $\log$ 其实跑不大满，就冲过去了。

有一个有理有据的方法是类似根号分治，选择一个值域 $T$，小于等于 $T$ 的数跑 $\mathcal{O}(kT)$ 的多重背包可行性，每次枚举物品重量 $i$ 之后再记录一个 $g_j$ 代表用重量 $\leq i$ 的物品，$j$ 最少被几个 $i$ 凑出来，就能 dp 了。$>T$ 的用之前说到的 01 背包可行性问题，复杂度是 $\mathcal{O}(\frac{nk}{wT})$ 的，也就是 $>T$ 的数不会超过 $\frac{n}{T}$ 个，加上 bitset 优化即可。

后面那个做法的复杂度为 $\mathcal{O}(kT+\frac{nk}{wT})$，将 $T$ 设为 $100$ 发现计算次数可以接受，加上这个很难会被卡满，就过了。

代码是前面没有根号分治的做法。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<bitset>
typedef long long ll;
template <typename T> T Max(T x, T y) { return x > y ? x : y; }
template <typename T> T Min(T x, T y) { return x < y ? x : y; }
template <typename T> T Abs(T x) { return x < 0 ? -x : x; }
template <typename T> T chkmax(T &x, T y) { return x = x > y ? x : y; }
template <typename T>
T &read(T &r) {
	r = 0; bool w = 0; char ch = getchar();
	while(ch < '0' || ch > '9') w = ch == '-' ? 1 : 0, ch = getchar();
	while(ch >= '0' && ch <= '9') r = (r << 3) + (r <<1) + (ch ^ 48), ch = getchar();
	return r = w ? -r : r;
}
const int N = 1000010;
int n, p[N], a[N], m, k, ans1, ans2;
bool vis[N];
int ct[N], b[N], c[N], us[N];
std::bitset<1000001>f;
void dfs(int x, int s) {
	if(vis[x]) {
		a[++m] = s;
		return ;
	}
	vis[x] = 1;
	dfs(p[x], s+1);
}
signed main() {
	read(n); read(k); int _n = n;
	for(int i = 1; i <= n; ++i) read(p[i]);
	for(int i = 1; i <= n; ++i)
		if(!vis[i])
			dfs(i, 0);
	n = m;
	std::sort(a + 1, a + n + 1);
	int k_ = k;
	for(int i = 1; i <= n; ++i) {
		if(!k_) break ;
		int t = Min(a[i] / 2, k_);
		ans2 += t * 2; k_ -= t;
	}
	for(int i = 1; i <= n; ++i)
		if((a[i] & 1) && k_)
			++ans2,
			--k_;
	//
	for(int i = 1; i <= _n; ++i) ct[a[i]]++;
	m = 0;
	for(int i = 1; i <= _n; ++i)
		if(ct[i])
			b[++m] = i,
			c[m] = ct[i];
	f[0] = 1;
	for(int i = 1; i <= m; ++i) {
		int tc = c[i];
		for(int j = 1; tc; j <<= 1) {
			int t = Min(j, tc);
			f |= f << (b[i] * t),
			tc -= t;
		}
	}
	if(f[k]) ans1 = k;
	else ans1 = k+1;
	printf("%d %d\n", ans1, ans2);
	return 0;
}
```

---

## 作者：lsj2009 (赞：2)

不是，哥们，这题解区在说啥啊？？

## Description

给定一个排列 $\{p_n\}$ 和正整数 $k$，我们定义一个 $01$ 序列 $\{c_n\}$ 的代价是 $\sum\limits_{i=1}^n c_i c_{p_i^{-1}}$；称其是好的当且仅当 $\sum\limits_{i=1}^n c_i=k$。

求出所有好的 $01$ 序列中代价的最小值/最大值。

$1\le k\le n\le 10^6$。

## Solution

请注意：我这里的 $k$ 实际上是原题的 $n-k$（同样的，对于答案也取反了），但我觉得原题太反人类了，所以改成这样子了。

排列问题，套路地建出置换环。

**先来考虑最小值：**

对于一个环，我们贪心地想，肯定是我们尽可能地不相邻地选，那么在不相邻的前提条件下肯定是隔一个。

这样子我们就可以在花费 $0$ 的代价下填完 $x=\sum\limits_{i=1}^m \lfloor \frac{len_i}{2}\rfloor$ 个位置。

如果 $k>x$，也就是需要选的位置还有多余，我们就要花费额外代价了。

注意到奇数长度的环和偶数长度的环是不同的：

- 具体地说，奇数长度的环有一个地方会留下长度为 $2$ 的空缺，我们往那个地方里选一个，就只会花费 $1$ 的代价。
- 而操作之后，奇数长度的环的情况就和偶数长度环同理了（可以视作将两个相邻的选的位置合并在一起看）。
- 而对于偶数长度的环，那就是我随便选一个没有被选过的位置，我都会花费 $2$ 的代价（他本身和他的后继节点）。

则我记 $y=\sum\limits_{i=1}^m (len_i\bmod{2})$，我选这些就只要花费 $1$ 的代价。

如果还有剩余（$k>x+y$），那我就需要花费 $2$ 的代价了。

这样子我们就解决了最小值部分，复杂度线性。

**再来考虑最大值：**

这部分就恰恰相反，我们肯定是要尽可能贴近地选，那么对于一个环，我们要不全部选，要么可能会选他的一个连续的部分。

对于前者，选一个长度为 $x$ 的环，我们会获得 $x$ 的贡献；而选择一个长度为 $x$ 的链，我们却只会获得 $x-1$ 的贡献（因为首端是不符合要求的）。

那么也就是，我们肯定还是尽可能地选完整的环，我最多只可能选一条链。

那么现在问题就变成了：我是否可以选出若干个环，使得其环长和为 $k$，如果可以，则答案为 $k$，否则为 $k-1$。

这就是一个 $01$ 背包的可达性 dp 问题，我们直接做是 $\mathcal{O}(n^2)$ 的，使用 ``bitset`` 可以优化到 $\mathcal{O}(\frac{n^2}{w})$，但是还是无法通过。

考虑优化：注意到我们有 $\sum\limits_{i=1}^m len_i=n$；记 $t$ 为不同的环长个数，则我们有 $t=\mathcal{O}(\sqrt{n})$。这个显然，因为卡满时是 $len=1,2,\cdots$，根据高斯求和，和是 $\mathcal{O}(t^2)$ 的，所以 $t$ 是 $\mathcal{O}(\sqrt{n})$ 的。

则我们考虑将环长相同的丢到一起处理，就变成了一个多重背包的问题，这时候考虑二进制分组优化再转成 $01$ 背包，看起来我们就得到了一个 $\mathcal{O}(\frac{n\sqrt{n}\log{n}}{w})$ 的做法，但是实际上我们可以说明他是 $\mathcal{O}(\frac{n\sqrt{n}}{w})$ 的：

- 对于二进制分组的前半部分（即拆分成 $2$ 的幂次），我们考虑一个 $2$ 的幂次 $2^k$ 取乘上一个长度 $w_i$，关于他拆分得到的数 $w_i$ 的集合为 $S_k$，则 $\sum\limits_{x\in S_k} x\le \frac{n}{2^k}$，则 $|S_k|=\mathcal{O}(\sqrt{\frac{n}{2^k}})$。
  - 对于所有 $|S_k|$ 求和得到：$\sum\limits_{k\ge 0} |S_k|=\mathcal{O}(\sum\limits_{k\ge 0} \sqrt{\frac{n}{2^k}})=\mathcal{O}(\sqrt{n}\sum\limits_{k\ge 0} \sqrt{\frac{1}{2^k}})=\mathcal{O}(\sqrt{n})$。 
- 对于二进制分组的后半部分（即遗留下来的数），同一种长度只会遗留下一个剩余个数，而一共有 $\mathcal{O}(\sqrt{n})$ 种环长，所以我们会得到 $\mathcal{O}(\sqrt{n})$ 个数。

所以我们只会对 $\mathcal{O}(\sqrt{n})$ 个数做 $01$ 背包，故复杂度是 $\mathcal{O}(\frac{n\sqrt{n}}{w})$ 的。

这样子就可以通过此题。

## Code

```cpp
#include<bits/stdc++.h>
//#pragma GCC optimize(3,"Ofast","inline")
//#define int long long
#define i128 __int128
#define ll long long
#define ull unsigned long long
#define ld double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
#define pcnt(x) __builtin_popcount(x)
using namespace std;
void file_IO() {
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
}
bool M1;
const int N=1e6+5;
int p[N],cnt[N],len,n,k;
bitset<N> f;
bool used[N];
void dfs(int u) {
	if(used[u])
		return;
	++len;
	used[u]=true;
	dfs(p[u]);
}
int solve1(int k) {
	int c=0;
	rep(i,1,n) {
		k-=(i>>1)*cnt[i];
		c+=(i&1)*cnt[i];
	}
	if(k<=c)
		return max(k,0);
	else
		return c+(k-c)*2;
}
int solve2(int k) {
	f[0]=1;
	rep(i,1,n) {
		int base=1,t=cnt[i];
		while(base<=t) {
			f|=f<<(i*base);
			t-=base;
			base<<=1;
		}
		if(t)
			f|=f<<(i*t);
	}
	return f[k]? k:k-1;
}
void solve() {
	scanf("%d%d",&n,&k);
	k=n-k;
	rep(i,1,n)
		scanf("%d",&p[i]);
	rep(i,1,n) {
		if(!used[i]) {
			len=0;
			dfs(i);
			++cnt[len];
		}
	}
	printf("%d %d\n",n-solve2(k),n-solve1(k));
}
bool M2;
signed main() {
	//file_IO();
	int testcase=1;
	//scanf("%d",&testcase);
	while(testcase--)
		solve();
	cerr<<"used time = "<<1000*clock()/CLOCKS_PER_SEC<<"ms\n";
	cerr<<"used memory = "<<(&M1-&M2)/1024/1024<<"MB\n";
	return 0;
}
```

---

## 作者：Purslane (赞：1)

考虑每一个置换环。假设长度为 $n$ 的置换环上有 $x$ 个人没带礼物，那么这个环上最少有几个人收不到礼物，最多几个人收不到礼物？

最少肯定是将这个环上所有节点聚集在一起，因此：
$$
f_{\min}(x) =
\left\{
\begin{matrix}
x+1, & x \le n-1 \\
x,  & x = n
\end{matrix}
\right.
$$
使用调整法容易发现，最终必定只有最多 $1$ 个环既有带礼物的又有不带礼物的，这时最小答案是 $k+1$；如果不存在一个环既有带礼物的又有不带礼物的，这时最小答案是 $k$。

因此我们只需要判断后一种情况是否可行，那本质就是将所有置换环长度做 $0/1$ 背包。

---------

一种方法是将所有大小相同的背包合并，变成多重背包后二进制分组，使用 `bitset` 优化。

具体复杂度分析参见其他题解。

----------

另一种方法（我自己想的）是直接无脑分治。如果这种环的长度 $\ge 100$，直接使用 `bitset`。显然这样的环不会超过 $10^4$ 个，使用 `bitset` 能接受。

如果这种环的长度 $< 100$，使用多重背包（不过单调队列都不需要）可以做到 $O(n)$ 一次。

总的运算量为 $10^8$ 数量级。

----------

最大值是简单的。对于偶环，如果长度为 $n$，在前 $\dfrac{n}{2}$ 次加入可以糟蹋 $2$ 个人，后 $\dfrac{n}{2}$ 次加入就糟蹋不了人。

对于奇环，如果长度为 $n$，在前 $\dfrac{n-1}{2}$ 次加入可以糟蹋 $2$ 个人，中间一次加入可以糟蹋 $1$ 个人，后 $\dfrac{n-1}{2}$ 次加入可以加入 $0$。

直接贪心选最大的。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e6+10;
int n,k,p[MAXN],vis[MAXN],cnt[MAXN];
vector<int> len;
bitset<MAXN> dp;
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>k;
	ffor(i,1,n) cin>>p[i];
	ffor(i,1,n) if(!vis[i]) {
		int tlen=1,u=p[i];
		while(u!=i) ++tlen,vis[u]=1,u=p[u];
		vis[i]=1,len.push_back(tlen);
	}
	dp[0]=1;
	for(auto id:len) if(id<=100) cnt[id]++;
	else dp|=(dp<<id);
	ffor(i,1,100) {
		ffor(mod,0,i-1) {
			int lst=-0x3f3f3f3f;
			for(int j=mod;j<=n;j+=i) {
				if(dp[j]) lst=j;
				else if((j-lst)<=cnt[i]*i) dp[j]=1;
			}
		}
	}
	if(dp[k]) cout<<k<<' ';
	else cout<<k+1<<' ';
	vector<int> del;
	for(auto id:len) {
		if(id%2==0) ffor(i,1,id/2) del.push_back(0),del.push_back(2);
		else {
			del.push_back(1);
			ffor(i,1,id/2) del.push_back(0),del.push_back(2);
		}
	}
	sort(del.begin(),del.end());
	int sum=0;
	ffor(i,0,k-1) sum+=del[n-1-i];
	cout<<sum;
	return 0;
}
```

---

