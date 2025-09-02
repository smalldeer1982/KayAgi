# 『MdOI R4』Phoenix

## 题目背景

这是 $6$ 题中唯一一道没有题目背景的题。

## 题目描述

给定 $n$ 个**不可重**集合 $s_1\dots s_n$，集合中的数都是 $[1,m]$ 的范围内的整数。

现在请你求出有多少种 $1\sim n$ 的排列 $p$，使得

$(\sum\limits_{i=1}^n |s_i|)-(\sum\limits_{i=1}^{n-1} |s_{p_i}\bigcap s_{p_{i+1}}|)=|\bigcup\limits_{i=1}^n s_i|$

成立。

答案对 $998244353$ 取模。保证取模前的真实答案大于 $0$。

## 说明/提示

【样例解释 #1】

三个集合分别为 $\{1\},\{1,2\},\{1,2,3\}$。


共有四个排列符合条件，分别是 $(1,2,3),(1,3,2),(2,3,1),(3,2,1)$。

【数据规模与约定】

**本题采用捆绑测试**
|子任务编号|$n\le$|$m\le$|特殊性质|分值|
|:-|:-|:-|:-|:-|
|$1$|$10$|$20$|无特殊限制|$10$|
|$2$|$30$|无特殊限制|$a_i=2^i$|$10$|
|$3$|无特殊限制|无特殊限制|$a_i\operatorname{or}a_j=\max(a_i,a_j)$|$10$|
|$4$|无特殊限制|无特殊限制|每个集合恰好包含两个元素|$20$|
|$5$|无特殊限制|$20$|无特殊限制|$20$|
|$6$|无特殊限制|无特殊限制|无特殊限制|$30$|

对于 $100\%$ 的数据，$1 \le T \le 50$，$1\le \sum n\le  10^5$，$1\le m\le 60$，$0 \le a_i \le 2^m-1$，其中 $\sum n$  表示所有测试数据中 $n$ 的和。

【提示与帮助】

本题读入量较大，请选手选择较快的读入方式。

感谢 $\rm\textcolor{black}{J}\textcolor{red}{ohnVictor}$ 对此题的贡献。

## 样例 #1

### 输入

```
1
3 3
1 3 7```

### 输出

```
4```

## 样例 #2

### 输入

```
2
5 9
2 30 98 386 482
4 2 
1 3 3 1```

### 输出

```
12
12```

# 题解

## 作者：Froggy (赞：7)

### 前言：

感谢zyk对我的指导，我才得以写出这题。

2k 代码调了将近 3h 才调出来，看起来我的代码能力还需提高。

---

### 题解：

不难发现，一个满足条件的把集合排列好的排列，必须满足对于 $[1,m]$ 的每一种数，都存在一个区间，满足区间中的集合都包含这种数，并且区间外的集合都不包含这种数。

设 `Solve(v,t)` 考虑 $v$ 中这些集合，$t$ 中这些种类的数的方案数。$v$ 满足在最终排列中一定是连续的一段（即一定紧挨在一起）。

考虑找到一个 $t$ 的子集 $z$，使得 $v$ 中的数可以根据和 $z$ 的交集再划分成若干个必须挨在一起的集合的集合，然后答案乘上这些集合的集合的合法排列方案。

对于 $t$ 中数 $x$，设 $c_x$ 表示 $v$ 中包含 $x$ 的集合构成的集合。

考虑先找到那些不存在另一个数 $y$ 使得 $c_x\subset c_y$ 的集合 $x$。

如果直接按这些 $x$ 构成的 $z$ 划分集合，会 WA 一片。

拍一拍会发现问题出在有的数非常讨厌，比如一个数 $x$，虽然它会被某个 $c_y$ 包含，但是 $c_x$ 中存在两个集合使得这两个集合和 $z$ 的交集不同，如果 $x$ 不在 $z$ 中就 GG 了，所以需要把 $x$ 加进 $z$ 中。

具体如何统计答案建议自行思考。实现细节可以参考代码。

时间复杂度：$\mathcal{O}(nm^2)$。但是常数特别小，最慢点50ms。

---

***code:***

```cpp

/*
zyk txdy zyk txdy
zyk txdy zyk txdy
zyk txdy zyk txdy
zyk txdy zyk txdy
zyk txdy zyk txdy
zyk txdy zyk txdy
zyk txdy zyk txdy
*/


const int mod=998244353;

int T,n,m,fac[N];
ull a[N];
void init(int n){
	fac[0]=1;
	for(int i=1;i<=n;++i){
		fac[i]=1LL*fac[i-1]*i%mod;
	}
}
struct Union_Set{
	int f[64],s[64];
	void init(int n){
		for(int i=0;i<n;++i)f[i]=i,s[i]=1;
	}
	int getf(int x){
		return f[x]==x?x:f[x]=getf(f[x]);
	}
	int Merge(int x,int y){
		int fx=getf(x),fy=getf(y);
		if(fx==fy)return 0;
		s[fx]+=s[fy],s[fy]=0;
		f[fy]=fx;
		return 1;
	}
};
int Solve(vector<ull> &p,ull t){
	ull z=0;
	static int cnt[64];
	memset(cnt,0,sizeof(cnt));
	bool same=true;
	for(int i=1;i<(int)p.size();++i){
		if(p[i]^p[0]){same=false;break;}
	}
	if(same)return fac[p.size()];
	for(auto x:p){
		for(int i=0;i<m;++i){
			if(x>>i&1)++cnt[i];
		}
	}
	for(int i=0;i<m;++i){
		if(t>>i&1){
			ull all=(1uLL<<m)-1;
			for(auto x:p){
				if(x>>i&1)all&=x;
			}
			bool ok=true;
			for(int j=0;j<m&&ok;++j){
				if(i==j||cnt[j]<cnt[i]||(cnt[j]==cnt[i]&&i<j))continue;
				if(all>>j&1){
					ok=false;break;
				}
			}
			if(ok)z|=1uLL<<i;
		}
	}
	while(true){
		bool qwq=false;
		for(int i=0;i<m;++i){
			if(t>>i&1&&!(z>>i&1)){
				ull tmp=~0uLL;
				for(auto x:p){
					if(x>>i&1){
						ull g=(x&z);
						if(~tmp&&tmp^g){
							z|=1uLL<<i;qwq=true;
							break;
						} 
						tmp=g;
					}
				}
			}
		}
		if(!qwq)break;
	}
	int res=1;
	map<ull,vector<ull> > mp;
	int rem=__builtin_popcountll(z);
	for(auto x:p){
		if(x){
			mp[x&z].push_back(x^(x&z));
		}
		else ++rem;
	}
	Union_Set S;
	S.init(m);
	for(auto [d,s]:mp){
		res=1LL*res*Solve(s,t^z)%mod;
		for(int i=0;i<m;++i){
			if(d>>i&1){
				for(int j=0;j<m;++j){
					if(d>>j&1)rem-=S.Merge(i,j);
				}
			}
		}
	}
	for(int i=0;i<m;++i){
		if(z>>i&1&&S.s[i]>1)(res<<=1)%=mod;
	}
	return 1LL*res*fac[rem]%mod;
}
int main(){
	init(100000);
	T=read();
	int cnt=0;
	while(T--){
		++cnt;
		n=read(),m=read();
		vector<ull> all;
		for(int i=1;i<=n;++i){
			all.push_back(read());
		}
		printf("%d\n",Solve(all,(1uLL<<m)-1));
	}
	return 0;
}
```

---

## 作者：JohnVictor (赞：5)

放上官方题解，由 JV,zght,installb 一起写的 qwq。

还要感谢 @Kubic @xh092113 写代码。

#### 性质

将 $s_i$ 重排成 $S_i$，满足 $S_i = s_{p_i}$。那么 $p_i$ 的计数就转化成了 $s_i$ 重排的计数。

考虑对于所有合法的 $S_i$ 中，每一个元素所在的集合都是连续的一个区间。比如 $2$ 元素会在 $S_1, S_2, \cdots, S_9$ 中出现。反证法易证（因为要消去所有重复）

根据这个性质思考：如果我们画出每一个元素所在的区间的话，那么我们就可以还原出所有的集合。

比如这个图，我们就能轻松得到：$S_1 = \{3\}, S_2 = \{1, 3\}, S_3 = \{1, 2, 3\}, S_4 = \{1, 2, 3\}, S_5 = \{2, 3\}, S_6 = \{2\}$。
$$
\large \begin{aligned}
&1\quad 2\quad 3\quad 4\quad 5\quad 6\quad 7 \cr
&\kern{13pt}\boxed{\kern{14pt}1\kern{14pt}} \cr
&\kern{28pt}\boxed{\kern{23pt}2\kern{23pt}} \cr
&\kern{1pt}\boxed{\kern{30pt}3\kern{30pt}}
&\end{aligned}
$$
显然，我们可以从输入中得到每一个元素在多少个集合中，也就是这些区间的长度。我们要刻画的是这些区间的相对位置关系。 

#### 结构

认真观察，发现对于任意两个区间，我们都可以算出他们的交集的长度。例如，包含 $1$ 的区间和包含 $2$ 的区间的交集长度就是包含 $\{1, 2\}$ 的集合的数量。

设两个区间的长度为 $l_1, l_2\ (l_1 \le l_2)$，那么我们可以这么刻画它们的位置关系：（设交集的大小为 $l$）

1. 不相交，即 $l=0$。
2. 相交但不包含，也就是 $0 < l < l_1$。
3. 包含，也就是 $l = l_1$。

不难发现，如果两个段是相交关系的话，那么就能刻画出它们的相对位置，最多两种：要么短的在前，要么长的在前。

如果这时候又来了另外一段，那么我们就可以通过位置关系能刻画出这个新的段的位置（是唯一的）。所以，无论多少段相交，他们的排列方式都只有两种，其中一种是另一种翻转过来。

#### 计数

所以根据上面的操作，我们就能把所有相交的段都“合并”，然后合并后的段互相只有包含关系，就像下面这张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/bdldkpjq.png)

那么现在开始计数，在红色节点处，一共有三个被他包含的段，然后其中被合并的区间的贡献为 $2^2 = 4$ 种。我们把合并的区间视为整体，我们就化归到了这个问题：

一个 $1 \times k$ 的格子要放入若干个 $1 \times t_i$ 的长条，问方案数。

如果我们把每一个 $1 \times t_i$ 变成 $1 \times 1$，然后把 $k$ 的值减去 $\sum t_i - 1$ 得到 $k_0$，那么答案就是 $k_0 (k_0-1)\cdots (k_0 - j+1)$。

#### 具体实现

- 输入进来的集合可能有重复的，我们需要去掉这些，开一个 map 判重即可。记 $x$ 序列一共出现了 $t[x]$ 次。考虑这些重复的对于最终答案的贡献：他们的顺序对于序列 $p$ 是否符合要求没有必然的影响，所以对答案的贡献是个数阶乘的乘积，即 $$ \prod_x t[x]!$$
- 判重之后预处理出每个元素的区间长度，以及这些元素的区间两两之间的交集的长度。
- 有一种情况我们需要判断掉：就是两个一模一样的区间。这样的区间会影响后面的计算（实际上，如果你没有做这一步，你的时间复杂度将会变成 $\mathcal O(nm^2)$），所以我们需要将其排除。考虑到两个一模一样的区间中只有一个会对答案造成贡献，因此直接排除重复的那一个即可。
- 不难想到合并相交的区间可以使用并查集来实现。我们还需要维护并查集中每个点的（子树）大小。这部分对于答案的贡献就是每一个由多个区间合并而成的大区间都可以反转而不破坏性质，所以每一个大区间的贡献是 $2$。
- 接下来枚举元素处理包含关系，并且存下来。即统计一下，包含 $x$ 元素的是哪些元素（记为 $c[x]$）。这里需要注意的是，这里的“$x$ 元素”指的是并查集合并之后的，即相交段作为整体考虑。
- 然后就是需要把包含关系区间的贡献算出来。我们考虑题解计数部分里面的那张图。$j$ 比较好求，就是有相同包含关系的节点的个数（即 $c[x]$ 相同的节点个数）。现在的问题是：$k_0$ 怎么求？考虑让 $j$ 个节点一一对应之后，$k_0$ 中剩余的节点的个数为与 $c[x]$ 相同的 $s_i$ 的个数。然后把贡献乘起来就好了。

![](https://cdn.luogu.com.cn/upload/image_hosting/ul0dgch6.png)

最终的时间复杂度取决于你的实现，std 的实现是 $\mathcal O(nm + m^3)$ 的。

感谢 @installb 提供如此优秀的实现方式。别的实现都十分繁琐。

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>
#include <vector>
using namespace std;
typedef long long ll;
const ll P = 998244353;

ll ffa[70] = {0},siz[70] = {0};
ll getf(ll x){ return ffa[x] == x ? x : ffa[x] = getf(ffa[x]); }
void unionn(ll x,ll y){ x = getf(x); y = getf(y); if(x == y) return; ffa[x] = y; siz[y] += siz[x]; }
//dsu

map <ll,ll> mp,mp2;
ll isc[70][70] = {0}; // length of intersection between intervals
vector <ll> tsc,ss;

ll len[70] = {0};
ll con[70] = {0}; // every y in {con[x]} contains x

ll intersect(ll x,ll y){ return (isc[x][y] > 0 && isc[x][y] < min(len[x],len[y])) || (len[x] == len[y] && isc[x][y] == len[x]); }
ll subset(ll x,ll y){ return isc[x][y] == len[x] && len[x] != len[y]; } // y contain x

ll n,m,ans = 1,T;

int main(){
	cin >> T;
	while(T --){
		memset(isc,0,sizeof(isc));
		cin >> n >> m; m ++; ans = 1;
		for(ll i = 0;i <= 64;i ++) siz[i] = 1,ffa[i] = i,con[i] = 0,len[i] = 0;
		mp.clear(); mp2.clear();
		ss.clear(); tsc.clear();
		
		for(ll w,i = 1;i <= n;i ++){
			cin >> w; w |= (1ll << (m - 1));
			if(mp.find(w) == mp.end()) ss.push_back(w);
			mp[w] ++; ans = (ans * mp[w]) % P;
		}
		for(ll w,ad,i = 0;i < ss.size();i ++){
			w = ss[i]; ad = mp[w];
			tsc.clear();
			for(ll j = 0;j < 64;j ++){
				if((w >> j) & 1){
					tsc.push_back(j + 1);
					len[j + 1] += ad;
				}
			}
			for(ll j = 0;j < tsc.size();j ++){
				for(ll k = 0;k < tsc.size();k ++){
					if(j == k) continue;
					isc[tsc[j]][tsc[k]] += ad;
				}
			}
		}
		
		for(ll i = 1;i <= m;i ++)
			for(ll j = i + 1;j <= m;j ++)
				if(len[i] == len[j] && len[i] == isc[i][j]) siz[j] = 0;
		for(ll i = 1;i <= m;i ++)
			for(ll j = 1;j <= m;j ++)
				if(intersect(i,j)) unionn(i,j);
		for(ll i = 1;i <= m;i ++)
			for(ll j = 1;j <= m;j ++)
				if(getf(i) != getf(j) && subset(i,j)) con[i] |= (1ll << (j - 1));
		for(ll i = 1;i <= m;i ++){
			if(getf(i) == i && len[i] > 0){
				mp2[con[i]] ++;
				if(siz[i] > 1) ans = (ans * 2) % P;
			}
		}
		for(ll tmp,k0,i = 1;i <= m;i ++){
			if(len[i] == 0) continue;
			tmp = mp2[con[i]]; k0 = tmp;
			if(tmp){
				if(con[i] && mp.find(con[i]) != mp.end()) k0 += mp[con[i]];
				for(ll j = 0;j < tmp;j ++) ans = (ans * (k0 - j)) % P;
				mp2[con[i]] = 0;
			}
		}
		cout << ans << '\n';
	}
	return 0;
}
//by installb

---

