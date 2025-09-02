# [ARC159F] Good Division

## 题目描述

当数列 $X$ 满足以下条件时，称 $X$ 为**良好数列**。

- 可以通过重复以下操作 $0$ 次或多次，将 $X$ 变为空序列：
  - 选择 $X$ 中相邻的两个元素 $x_i, x_{i+1}$，且 $x_i \neq x_{i+1}$，将它们删除。

给定一个包含 $2N$ 个元素的数列 $A=(a_1,\ldots,a_{2N})$。  
将 $A$ 分割为 $1$ 个或多个连续子序列的方法共有 $2^{2N-1}$ 种。请计算其中每个连续子序列都是良好数列的分割方法数，并对 $998244353$ 取模。

## 说明/提示

## 限制条件

- $1 \leq N \leq 5 \times 10^5$
- $1 \leq a_i \leq 2N$
- 输入均为整数

## 样例解释 1

有以下 $2$ 种满足条件的分割方法：
- $(1,1,2,3,4,5)$
- $(1,1,2,3),(4,5)$

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
1 1 2 3 4 5```

### 输出

```
2```

## 样例 #2

### 输入

```
1
1 2```

### 输出

```
1```

## 样例 #3

### 输入

```
1
1 1```

### 输出

```
0```

## 样例 #4

### 输入

```
12
4 2 17 12 18 15 17 4 22 6 9 20 21 16 23 16 13 2 20 15 16 3 7 15```

### 输出

```
2048```

# 题解

## 作者：houzhiyuan (赞：11)

绝杀题，直接上 3 Dan 了。

先考虑满足条件的 $X$ 是啥样的。

容易发现，$|X|$ 必须是偶数，并且不存在绝对众数。

绝对众数的定义是，出现次数超过 $\frac{|X|}{2}$ 的数。

咋证呢，对于一个 $X$，如果存在一个绝对众数，那么它一定不合法。

否则，考虑进行一次删除操作时，只有出现次数为 $\frac{|X|}{2}$ 的数可能会不合法。

讨论一下，如果有两个这样的数，那么整个序列一定只有这两个数，直接操作一组即可。

否则，只要找到出现次数为 $\frac{|X|}{2}$ 的数，必然有一个可以和旁边的操作。

这样就可以一直保持合法状态，所以合法。

## $O(n^2)$ 做法

直接对着这个暴力即可，设 $f_i$ 表示前 $i$ 个数的方案数，然后暴力枚举前面满足条件的左端点，维护一下当前区间众数。

[code](https://atcoder.jp/contests/arc159/submissions/40421268)

场上甚至还写了一发来验证一下结论。

## $O(n\log^2 n)$ 做法

绝对众数，考虑一下摩尔投票，但是这个题好想不太能直接用。

摩尔投票满足一个可加性，换句话说就是如果把一个区间裂成两半，那么绝对众数一定至少在一半里是绝对众数。

考虑 cdq 分治，对于区间 $[l,r]$，先把 $[l,mid]$ 的 dp 值先去递归算出，然后只需要考虑左边对右边的贡献，相当于只需要找出所有跨过 $mid$ 的有绝对众数区间。

跨过 $mid$，自然是分成左右两半，一个满足条件的区间一定在左边或者右边是区间众数。

对左边求后缀绝对众数，右边求前缀，会发现前缀不同绝对众数只会有 $O(\log n)$ 个，因为每次出现一个，所需要的区间长度翻倍。

然后一个区间最多只有一个绝对众数。

所以对于 $O(\log n)$ 个绝对众数，每个做一遍前缀和，这样就可以快速算出所有需要减去的区间了。

[code](https://atcoder.jp/contests/arc159/submissions/40425986)

[官方题解](https://atcoder.jp/contests/arc159/editorial/6171)有线性做法，有兴趣的可以自己了解。

---

## 作者：tzc_wk (赞：7)

没有想到你们所说的 CDQ 分治 + 摩尔投票的做法，但是这里介绍一种 $O(n\log n)$，经过精细实现可能可以做到 $O(n)$ 的做法，~~虽然跑得没有 2log 甚至 3log 快~~

显然一个区间能被删光当且仅当它的长度是偶数并且其中不存在绝对众数。这样我们列出一个 DP 方程：$dp_i=\sum\limits_{j,s.t.j\text{是偶数且}[j+1,i]\text{中不存在绝对众数}}dp_j$。其中 $dp_0=1$。显然可以根号分治，思路类似于 CF1446D2，介于此题数据范围较大所以笔者没有实现根号分治的做法，这里也不再赘述。

实时维护 $sumbad=\sum\limits_{[j+1,i]\text{中存在绝对众数}}dp_j$。考虑新添加一个元素 $v$ 后 $sumbad$ 的变化：

- 对于所有满足 $[j+1,i]$ 中 $v$ 元素与不是 $v$ 的元素数量相等的 $j$，$sumbad$ 加上 $dp_j$。
- 对于所有不是 $v$ 的元素 $v'$ 与所有满足 $[j+1,i]$ 中 $v'$ 元素数量恰比不是 $v'$ 的元素数量多 $1$ 的 $j$，$sumbad$ 减去 $dp_j$。

结合根号分治的做法，我们猜想，对于任意 $v$，符合以下条件的 $r$ 的个数与 $cnt_v$ 同阶：

- 存在 $l$ 使得 $[l,r]$ 中 $v$ 的数量恰好占一半。

考虑证明：我们维护两个区间集 $I,J$，对于所有 $a_i=v$ 的 $i$，我们将 $[i,i+1]$ 加入 $I$，然后重复以下步骤直到 $I$ 为空：

- 取出 $I$ 中左端点最小的区间 $[l,r]$，如果存在另一个区间 $[l',r']$ 与 $[l,r]$ 有交，则删掉这两个区间，将 $[l,r+(r'-l')+1]$ 加入 $I$。否则从 $I$ 删除 $[l,r]$ 并将 $[l,r]$ 中加入 $J$。

显然，此时 $J$ 中所有区间的并集就是所有符合上述条件的 $r$，而在上述过程中，所有区间长度之和不会变，初始为 $2c$，所以最终也不会超过 $2c$。

同理，符合条件的左端点数量也是 $O(cnt_v)$ 的。

这样我们暴力维护符合要求的左右端点，然后顺着 DP 的时候，在左端点处将 DP 值加入桶，在右端点时候提取 DP 时候并更新 $sumbad$ 即可。

```cpp
const int MAXN=1e6;
const int MOD=998244353;
int n,a[MAXN+5],dp[MAXN+5];
vector<int>occ[MAXN+5],vl[MAXN+5],vr[MAXN+5];
vector<pii>L[MAXN+5],R[MAXN+5];
int sum_dp,sum_bad,sum[MAXN+5];map<int,int>ss[MAXN+5];
int main(){
	scanf("%d",&n);n<<=1;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)occ[a[i]].pb(i);
	for(int i=1;i<=n;i++){
		priority_queue<pii,vector<pii>,greater<pii> >q;
		for(int x:occ[i])q.push(mp(x,x+1));
		while(!q.empty()){
			pii p=q.top();q.pop();
			if(q.empty()||q.top().fi>p.se+1)R[i].pb(p);
			else{
				pii pp=q.top();q.pop();
				int len=p.se-pp.fi+1;
				q.push(mp(p.fi,pp.se+len));
			}
		}
	}
	for(int i=1;i<=n;i++){
		priority_queue<pii,vector<pii>,greater<pii> >q;
		for(int x:occ[i])q.push(mp(n-x+1,n-x+2));
		while(!q.empty()){
			pii p=q.top();q.pop();
			if(q.empty()||q.top().fi>p.se+1)L[i].pb(p);
			else{
				pii pp=q.top();q.pop();
				int len=p.se-pp.fi+1;
				q.push(mp(p.fi,pp.se+len));
			}
		}
	}
	for(int i=1;i<=n;i++)for(int j=0;j<R[i].size();j++)chkmin(R[i][j].se,n);
	for(int i=1;i<=n;i++){
		for(int j=0;j<L[i].size();j++){
			L[i][j].fi=n-L[i][j].fi+1;L[i][j].se=n-L[i][j].se+1;
			swap(L[i][j].fi,L[i][j].se);
			chkmin(L[i][j].se,n);chkmax(L[i][j].fi,1);
		}
	}
	for(int i=1;i<=n;i++){
		for(pii p:L[i])for(int j=p.fi;j<=p.se;j++)vl[j].pb(i);
		for(pii p:R[i])for(int j=p.fi;j<=p.se;j++)vr[j].pb(i);
	}
	sum_dp=1;dp[0]=1;
	for(int i=1;i<=n;i++){
		for(int x:vl[i])ss[x][sum[x]*2-(i-1)]=(ss[x][sum[x]*2-(i-1)]+dp[i-1])%MOD;
		sum[a[i]]++;
		for(int x:vr[i]){
			if(x==a[i])sum_bad=(sum_bad+ss[x][sum[x]*2-i-1])%MOD;
			else sum_bad=(sum_bad-ss[x][sum[x]*2-i]+MOD)%MOD;
		}
		if(i%2==0){
			dp[i]=(sum_dp-sum_bad+MOD)%MOD;
			sum_dp=(sum_dp+dp[i])%MOD;
		}
	}
	printf("%d\n",dp[n]);
	return 0;
}
/*
10
1 4 5 3 1 2 6 3 1 1 3 5 6 1 6 5 5 5 6 2
*/
```



---

## 作者：DaiRuiChen007 (赞：4)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc159_f)

**题目大意**

> 定义一个序列是好的当且仅当可以每次删去一对相邻不同的数把序列删空。
>
> 现在给定一个长度为 $2n$ 的序列 $a$，计数有多少序列划分方式使得每一段都是好的。
>
> 数据范围：$n\le 5\times 10^{5}$。

**思路分析**

先考虑那些序列是好的，手玩发现当且仅当一个序列没有绝对众数的时候是好的：

> 有绝对众数的序列把非绝对众数全部用掉之后也一定剩下一些绝对众数，因此不能清空。
>
> 否则只有出现次数为序列一半的数可能变成绝对众数，如果这种数只有一个，那么随便删都行，有两个的话这个序列只有两种颜色，找一个交界处一种颜色删一个即可。

因此可以设计一个 dp：$f_i=\sum_{j}[a_{2j+1}\sim a_{2i}\text{ is valid}] f_j$。

注意到绝对众数这个条件一般会用摩尔投票法维护，而摩尔投票信息容易合并，因此想到 CDQ 分治。

考虑 $[l,mid]\to [mid+1,r]$ 的贡献，显然 $[i,j]$ 的绝对众数（如果存在）一定是 $[i,mid]$ 或 $[mid+1,j]$ 的绝对众数。

又因为绝对众数切换至少需要两倍的长度，因此 $[i,mid]$ 和 $[mid+1,j]$ 中的本质不同绝对众数只有 $\mathcal O(\log n)$ 个。

由于摩尔投票不好同时维护多种颜色的情况，那么我们可以枚举每个可能的绝对众数 $x$，只要数 $x$ 出现次数减去 $\ne x$ 出现次数，即可。

$[i,j]$ 有绝对众数 $x$ 当且仅当前后缀摩尔投票结果加起来 $>0$，直接对前缀摩尔投票结果用桶存即可。

时间复杂度 $\mathcal O(n\log^2n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=5e5+5,MOD=998244353,V=1e6;
void add(int &x,int y) { x=(x+y>=MOD)?x+y-MOD:x+y; }
void sub(int &x,int y) { x=(x>=y)?x-y:x+MOD-y; }
int n,a[MAXN][2],cnt[MAXN<<1],sum[MAXN<<1],dp[MAXN];
void solve(int l,int r) {
	if(l==r) return ;
	int mid=(l+r)>>1;
	solve(l,mid);
	int fs=0;
	for(int i=l;i<=mid;++i) add(fs,dp[i]);
	for(int i=mid+1;i<=r;++i) add(dp[i],fs);
	vector <int> key;
	for(int i=mid;i>l;--i) {
		for(int k:a[i]) ++cnt[k];
		for(int k:a[i]) if(cnt[k]>mid-i+1) key.push_back(k);
	}
	for(int i=mid;i>l;--i) for(int k:a[i]) cnt[k]=0;
	for(int i=mid+1;i<=r;++i) {
		for(int k:a[i]) ++cnt[k];
		for(int k:a[i]) if(cnt[k]>i-mid) key.push_back(k);
	}
	for(int i=mid+1;i<=r;++i) for(int k:a[i]) cnt[k]=0;
	sort(key.begin(),key.end()),key.erase(unique(key.begin(),key.end()),key.end());
	for(int x:key) {
		int len=(mid-l+1)<<1;
		add(sum[V],dp[mid]);
		for(int i=mid,s=0;i>l;--i) {
			for(int k:a[i]) s+=(k==x?1:-1);
			add(sum[V+s],dp[i-1]);
		}
		for(int i=len-1;i>=-len;--i) add(sum[V+i],sum[V+i+1]);
		for(int i=mid+1,s=0;i<=r;++i) {
			for(int k:a[i]) s+=(k==x?1:-1);
			sub(dp[i],sum[V-s+1]);
		}
		for(int i=-len;i<=len;++i) sum[V+i]=0;
	}
	solve(mid+1,r);
}
signed main() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d%d",&a[i][0],&a[i][1]);
	dp[0]=1,solve(0,n);
	printf("%d\n",dp[n]);
	return 0;
}
```

---

## 作者：Alan_Zhao (赞：3)

## 题解

首先，某一段可以单独成段，当且仅当其长度为偶数，且其没有绝对众数。

于是设 $f_i$ 表示前 $i$ 个位置有多少种合法的分割方式。转移时，用所有转移减去当前段有绝对众数的转移。

考虑绝对众数的那个套路。枚举一个绝对众数 $x$，把整个序列里是 $x$ 的位置标记为 $1$，其余位置标记为 $-1$，那么某一段的绝对众数是 $x$ 当且仅当这一段的标记之和 $>0$。我们先把所有是 $x$ 的位置删去。随后，对于某个是 $x$ 的位置，我们分别找到它前面和后面距离它最近的没被删去的位置，并把这两个位置删去。然后只需要考虑所有被删去的位置构成的连续段即可，段间一定没有贡献。对于每个连续段，只需要用树状数组维护即可。

但这样有一个问题，就是当前 $f_i$ 的值依赖于它前面所有 $f_j$ 的值，所以不可能对于每个绝对众数 $x$ 分别做上述操作。

考虑把所有这些连续段离线下来做扫描线。对于每个位置，我们先处理它上面记录的加入、删除操作，然后枚举现在仍然存在的每个连续段，并在这个连续段对应的树状数组上修改和查询。

由于所有连续段的长度之和是 $O(N)$ 的，所以总的时间复杂度是 $O(N\log N)$。如果精细实现应该能做到 $O(N)$，因为那个树状数组部分维护的是一个折线。但比较难写。

## 代码

```cpp
#include <bits/stdc++.h>
#include "atcoder/modint"
using namespace std;
#define For(Ti,Ta,Tb) for(int Ti=(Ta);Ti<=(Tb);++Ti)
#define Dec(Ti,Ta,Tb) for(int Ti=(Ta);Ti>=(Tb);--Ti)
#define Debug(...) fprintf(stderr,__VA_ARGS__)
#define range(Tx) begin(Tx),end(Tx)
using ll = long long;
using mint = atcoder::modint998244353;
struct BIT {
	const int n;
	vector<mint> t;
	BIT(int _n):n(_n), t(n + 1) {}
	void Add(int p, mint x) {
		for (; p <= n; p += p & -p) t[p] += x;
	}
	mint Query(int p) {
		mint res = 0;
		for (; p; p &= p - 1) res += t[p];
		return res;
	}
};
const int N = 1e6 + 5;
int n, a[N];
mint f[N], sf[N];
vector<int> occ[N], rem[N];
vector<pair<int, int>> ins[N];
struct Info {
	mutable int n, x, cur;
	mutable BIT bit;
	Info(int _x, int _n):n(_n), x(_x), cur(0), bit(n * 2) {}
};
bool operator<(const Info& i1, const Info& i2) {
	return i1.x < i2.x;
}
set<Info> lst;
int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr);
	cin >> n, n *= 2;
	For(i, 1, n) {
		cin >> a[i];
		occ[a[i]].push_back(i);
	}
	set<int> st;
	For(i, 1, n) st.insert(i);
	For(x, 1, n) {
		vector<int> del(occ[x]);
		for (int i : occ[x]) st.erase(i);
		for (int i : occ[x]) {
			auto it = st.lower_bound(i);
			if (it != st.begin()) del.push_back(*prev(it)), st.erase(prev(it));
			if (it != st.end()) del.push_back(*it), st.erase(it);
		}
		sort(del.begin(), del.end());
		For(i, 0, int(del.size()) - 2) {
			int l = i;
			while (i<int(del.size()) && del[i] == del[l] + i - l) ++i;
			ins[del[l]].emplace_back(x, del[i - 1] - del[l]), rem[del[i - 1] + 1].push_back(x);
		}
		for (int i : del) st.insert(i);
	}
	f[0] = 1;
	mint sum = 1;
	For(i, 1, n) {
		auto it = lst.begin();
		auto jt = rem[i].begin();
		for (; it != lst.end() && jt != rem[i].end();) {
			while (jt != rem[i].end() && *jt < it->x) ++jt;
			if (jt != rem[i].end() && *jt == it->x) it = lst.erase(it);
			else ++it;
		}
		if (i % 2 == 0) f[i] = sum;
		for (auto [x, len] : ins[i]) lst.emplace(x, len);
		for (auto& [len, x, cur, bit] : lst) {
			int pcur = cur;
			cur += (a[i] == x ? 1 : -1);
			if (i % 2) bit.Add(pcur + len, f[i - 1]);
			else f[i] -= bit.Query(cur + len - 1);
		}
		sum += f[i];
	}
	cout << f[n].val() << '\n';
	return 0;
}
```

---

## 作者：zyc070419 (赞：2)

# [ARC159F] Good Division 题解

首先对于题目要求的划分方式转化一下，转化为划分的每一段都没有 **绝对众数**，可以证明这与题目中的要求是完全等价的，证明如下：

**充分性**：考虑构造一种操作方法，就是每次操作都消去一个出现次数最多的数，按照这样操作可以保证每次操作之后该区间仍然不会出现绝对众数，故按此方法可以清空整个区间。

**必要性**：考虑该区间有绝对众数，容易发现无论如何操作最终仍旧会剩下若干相同的数，剩下的数为最开始的绝对众数（证明方法类似于摩尔投票）。

有了这一步转化之后考虑如何去做。首先可以暴力 DP，设 $dp_i$ 表示对前 $i$ 个数进行划分，并且以 $i$ 为右端点划分最后一段的方案数，那么有转移：
$$
dp_i=\sum_{[j+1,i]\texttt{无绝对众数}} dp_j
$$
复杂度 $\mathcal{O}(n^2)$。考虑如何优化：

有一个比较经典的结论：

> 对于一个序列 $\{a_n\}$，该序列的所有前缀中出现过的绝对众数的种类数为 $\mathcal{O}(\log n)$。

证明可以感性理解一下：当我们从序列一段往另一端遍历的过程中依次加入元素，如果能够出现一个 **新的** 绝对众数 $x$ 说明 $x$ 的出现次数已经超过了之前的绝对众数 $y$ 的出现次数，那么说明出现 **新的** 绝对众数 $x$ 时序列长度至少乘 $2$，所以说绝对众数种类数为 $\mathcal{O}(\log n)$。

那么比较显然我们可以尝试从绝对众数种类数方面去优化 DP。我最初的想法是将 DP 转移写成如下形式：

$$
dp_i=\sum_{j=0}^{i-1}dp_j-\sum_{x=1}^{2n}\sum_{[j+1,i]\texttt{的绝对众数为} x} dp_j
$$

这样第一维转移只用枚举 $\mathcal{O}(log_n)$ 次。但是第二维仍旧不好判断 $x$ 是否是其区间众数。

但第二维转移跟序列上的区间有关，所以可以尝试 cdq 分治！

每一次我们计算 $dp_{l-1\sim mid-1}$ 对于 $dp_{mid+1\sim r}$ 的贡献，也就是说在这一层我们统计所有 $i$ 所在段跨过 $mid$ 的转移。而所有跨过 $mid$ 的区间的绝对众数种类数仍旧是 $\mathcal{O}(\log n)$ 种，证明类似，所以说分治之后就可以枚举绝对众数 $x$ 然后将所有 $a_i=x$ 的地方设为 $1$，其余地方设成 $-1$，然后暴力做一遍前缀和，统计即可，具体的，若设 $sum_i$ 为 $i$ 的前缀和，则有转移：

$$
dp_i=\sum_{j\in[l-1,mid-1]}dp_j-\sum_{j\in[l-1,mid-1]\land sum_i>sum_j}dp_j
$$

可以树状数组维护，复杂度 $\mathcal{O}(n\log^3 n)$。但其实树状数组可以省掉，因为发现 $sum_i$ 的范围是 $\mathcal{O}(r-l+1)$，所以说可以先预处理出来 $pre_i$ 表示：
$$
pre_i=\sum_{j\in[l-1,mid-1]\land sum_j\le i}dp_j
$$
这一步是 $\mathcal{O}(r-l+1)$ 的，所以最终复杂度为 $\mathcal{O}(n\log^2 n)$。[代码如下](https://www.luogu.com.cn/paste/krr906gt)。



---

## 作者：Felix72 (赞：1)

不用分治优化转移，而是直接在暴力的基础上均摊优化。

考虑对于每一个位置 $r$，找出所有的 $l$ 满足区间 $(l, r]$ 存在绝对众数，那么 $[1, r]$ 的答案 $f_r$ 表示为 $\sum f - \sum_lf_l$。

$\sum f$ 是能直接记录的，考虑求解 $\sum l$。这里我们考虑用折线的方法刻画众数，即先钦定一个数字 $X$，一条折线从坐标原点开始，碰到 $X$ 往上折，否则往下折（类似括号匹配），则 $(l, r]$ 存在绝对众数 $X$ 等价于 $l$ 点的 $y$ 坐标低于 $r$ 点的 $y$ 坐标。

于是这就转化成了 $2n$ 个数据结构（不同的 $X$ 最多有 $2n$ 种）上求前缀和。乍一看止步于 $O(n^2)$，细看全是均摊：

- 这 $2n$ 条折线总共只有 $2n$ 步向上折；
- 向下折的折线很多，因此对于某一个位置，需要考虑计算前缀和的折线并没有那么多（因为很多折线都取到最低点了，前缀和为 $0$），而总共需要考虑的次数是 $O(n)$ 级别；
- 不一定要转移一次就更新一次数据结构，我们可以等到需要某个位置的贡献时再加上那个位置的贡献，用指针维护这一点，量级还是 $O(n)$。

这样一来有效信息就被压缩到了 $O(n)$ 的量级，偷懒用 STL 可以 $O(n \log n)$，总之怎么都比分治快。

---

## 作者：未来姚班zyl (赞：1)

提供一个模拟赛时没调出来的 $O(n)$ 做法。

## 题目大意

定义一个序列是好的当且仅当可以每次删去一对相邻不同的数把序列删空。

现在给定一个长度为 $2n$ 的序列 $A$，计数划分方式使得每一段都是好的。

## 题目分析

核心 dp 式子很好想：$dp_i=\sum\limits_{j<i}[A(j+1,i)\  合法 \ ]dp_j$，

首先，一个序列是好的的充要条件是长度为偶数且没有绝对众数。所以我们把序列两个两个数分成 $n$ 组。

绝对众数之多只有一个，所以我们可以考虑枚举这个绝对众数，计算不合法的方案对应的 $dp_j$ 之和，再容斥一下即可。

设 $p_{i,c}$ 表示值 $c$ 在前 $i$ 组的前缀和，则 $c$ **不是** $(l,r)$ 的绝对众数的充要条件为 $p_{r,c}-p_{l-1,c}>r-l+1$，移项得 $p_{r,c}-r>p_{l-1,c}-(l-1)$，设 $v_{i,c}=p_{i,c}-i$，则 $dp_j\nrightarrow dp_i$ 的条件为存在 $c$ 使得 $v_{j,c}<v_{i,c}$。目标就是快速对这些 $j$ 求和。

我们发现，随着 $i$ 右移，$v_{i,c}$ 只可能 $+1$，$-1$，或者不变。而且 $+1$ 与不变在所有的 $c$ 中总共才 $O(n)$ 次，所以 $(i,v_{i,c})$ 放在坐标轴上总共会分成 $O(n)$ 段，每段类似纵坐标一直 $-1$，纵坐标一直 $+1$，纵坐标不变（可以自己手画一下），对于每个 $i$ 则需要计算所有的 $c$ 中位于 $(i,v_{i,c})$ 与原点围成的矩阵中的 $(j,v_{j,c})$ 对应的 dp 值。

然后就是考虑直接处理！稍微有点复杂（所以模拟赛没调出来）。对于每个 $c$ 都按照以下方式处理：

我们先不管纵坐标不变的段。

我们对需要计算的点都采用如下计数方法：

找到左边最近的 $j$ 使得 $v_j=v_i$。然后继承 $j$ 的贡献，再加上中间的贡献（要么全算，要么全不算）。

我们要维护每个纵坐标对应的最靠右的横坐标。现在就是需要自己画图理解，笔者描述一下图像的特征：

- 对于最靠近 $i$ 的点使得 $(i,k)$，构成若干个纵坐标 $-1$ 的段，且这些段在 $y$ 值域上连续，在横坐标处断开。还可能会有一条纵坐标 $+1$ 的段，它的最高点纵坐标与 $-1$ 段的最低点纵坐标相邻，这些都可以用栈和三元组来维护。

这里笔者还是画个图帮助形象理解一下;

![](https://cdn.luogu.com.cn/upload/image_hosting/982k6iib.png)

红色和绿色就是我们要维护的连续段，显然当前点总是处于红线和绿线的交界处，所以我们可以用栈维护。

同时我们发现，需要计算贡献的点和 $+1$ 的点量级相等，所以总量级依旧是 $O(n)$。加上纵坐标不变的段其实影响并不大，只是增加一点细节而已。

直接模拟这个过程就可以做到 $O(n)$，代码实现还是非常多细节的，耐心扣一定能抠出来捏！

似乎没有用到摩尔投票法。

我的代码常数巨大，好像跑不过双 $\log$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N =2e6+5,mod=998244353;
inline void add(int &a,int b){((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline void red(int &a,int b){add(a,mod-b);}
inline int Red(int a,int b){return red(a,b),a;}
int n,a[N],c[N],dp[N],sum,tt[N];
struct node{
	int x,ty;
};
vector<node>up[N];
#include<bits/extc++.h>
using namespace __gnu_pbds;
map<int,int>Q[N];
vector<Pi>ad[N],eq[N];
struct nod{
	int l,r,s;
}q[N];
int Tp,p[N],tp;
int st[N<<1],top;
int P[N<<1];
bool v[N<<1];
inline void insert(int x,int k){
	x+=N;
	if(!v[x])v[x]=1,st[++top]=x;
	P[x]=k;
}
inline void clear(){
	while(top)v[st[top]]=P[st[top]]=0,top--;
}
signed main(){
	n=read();
	rep(i,1,n<<1)a[i]=read();
	repn(i)if(a[i<<1]==a[(i<<1)-1])up[a[i<<1]].pb({i,1});
	else up[a[i<<1]].pb({i,0}),up[a[(i<<1)-1]].pb({i,0});
	rep(i,1,n<<1){
		clear();
		int siz=up[i].size();
		if(!siz)continue;
		tp=-1;
		p[++tp]=-up[i][0].x+1+up[i][0].ty;
		int le=1,re=0;
		rep(j,1,siz-1){
			int del=up[i][j].x-up[i][j-1].x-1,pr=p[tp];
			p[++tp]=pr-del+up[i][j].ty;
		}
		Tp=0;
		q[++Tp]={0,-up[i][0].x+1,0};
		rep(j,0,siz-1){
			int l=up[i][j].x,r=n,w=p[j];
			if(j<siz-1)r=up[i][j+1].x-1;
			if(!up[i][j].ty){
				eq[l].pb({l-1,i});
				if(Tp){
					if(q[Tp].l==q[Tp].r)Tp--;
					else q[Tp].r++;
				}
			}
			else {
				if(le<=re)re++;
				else le=re=p[j]-1;
				insert(p[j]-1,l-1);
				if(Tp)if(q[Tp].r==p[j]-1){
					if(q[Tp].l==q[Tp].r)Tp--;
					else q[Tp].r++;
				}
				if(Tp){
					if(q[Tp].l==q[Tp].r)ad[l].pb({q[Tp].s,i}),Tp--;
					else ad[l].pb({q[Tp].s+q[Tp].l-q[Tp].r,i}),q[Tp].r++;
				}
				else ad[l].pb({-1,i});
			}
			q[++Tp]={w,w,l};l++,w--;
			int sl=l;
			while(le<=re&&l<=r)eq[l].pb({P[re+N],i}),l++,re--;
			l=sl;
			if(l<=r)q[++Tp]={w,w-(r-l),l};
		}
	}
	int sum=1;
	repn(i){
		int del=0;
		for(auto y:eq[i]){
			int w=Q[y.first][y.second];
			add(del,w),add(Q[i][y.second],w);
		}
		for(auto y:ad[i]){
			if(y.first==-1){
				add(Q[i][y.second],sum),add(del,sum);
				continue;
			}
			int w=0;
			add(w,Q[y.first][y.second]),add(w,Red(tt[i-1],tt[y.first])),add(del,w),add(Q[i][y.second],w);
		}
		dp[i]=Red(sum,del),add(sum,dp[i]),tt[i]=Add(tt[i-1],dp[i]);
	}
	cout <<dp[n];
	return 0;
}
```

---

## 作者：云浅知处 (赞：1)

$f_i$ 表示前 $i$ 个数的划分方案数。不难发现一个序列能被清空当且仅当不存在绝对众数。

注意到以 $i$ 结尾的所有区间 $a[l\cdots i]$ 中所有不合法的区间的绝对众数至多有 $O(\log i)$ 种。注意这并不代表不合法的区间只有 $O(\log i)$ 种，而是这些区间按照绝对众数去重后至多有 $O(\log i)$ 种。

考虑对某种绝对众数 $c$ 怎么算答案。设 $S_i$ 表示 $a[1\cdots i]$ 中 $c$ 的出现次数，那么 $[j+1,i]$ 不合法当且仅当 $2(S_i-S_j)>i-j\iff i-2S_i<j-2S_j$。

考虑开 $n$ 个动态开点线段树， 每次只需要在 $O(\log n)$ 个线段树中查询区间和，再在 $O(\log n)$ 个线段树中做单点修改。时间复杂度 $O(n\log ^2n)$。

但这样空间复杂度是 $O(n\log^2n)$，把线段树改成平衡树就 1log 了。场上我沙茶了不会优化空间就没写。或者你也可以提前离散化一下然后开 $n$ 个 bit，貌似常数差不多？

我们还需要快速找到所有能成为绝对众数的数，这里我场上想了个简单做法就是只需要检查出现次数 $\ge \sqrt{n}$ 的数和最近的 $\sqrt{n}$ 个数，但是复杂度 $O(n\sqrt{n})$ 不一定能过。

考虑一个数 $c$ 合法的条件，发现是 $\max j-2S_{j,c}>i-2S_{i,c}$。考虑从左往右扫，每次会有一个 $i-2S_{i,c}$ 变成原来 $-1$，其他的全都 $+1$。维护 $i-2S_{i,c}$ 形成的有序序列，每次删除不合法的，加入 $a_i$（虽然实际上这个 $a_i$ 也不一定合法但是无所谓），这部分时间复杂度就是 $O(n\log n)$。总的复杂度为 $O(n\log ^2n)$。

```cpp
//Yoimiya Kawaii

#include<bits/stdc++.h>

#define ll long long

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

const int mod=998244353;
int ksm(int x,int y,int p=mod){
	int ans=1;
	for(int i=y;i;i>>=1,x=1ll*x*x%p)if(i&1)ans=1ll*ans*x%p;
	return ans%p;
}
int inv(int x,int p=mod){return ksm(x,p-2,p)%p;}
int randint(int l,int r){return rand()*rand()%(r-l+1)+l;}
void add(int &x,int v){x+=v;if(x>=mod)x-=mod;}
void Mod(int &x){if(x>=mod)x-=mod;}

const int N=1e6+5;
vector<int>pf[N],sf[N],cur;
int n,cnt[N],a[N],mx[N],root[N],f[N];

struct Node{int ls,rs,sum,pos,val,rk;};
struct fhq{
	#define ls(p) d[p].ls
	#define rs(p) d[p].rs
	Node d[N<<5];int tot=0;
	int build(int x,int v){++tot;d[tot].sum=d[tot].val=v,d[tot].pos=x,d[tot].rk=rand()*rand();return tot;}
	void pushup(int p){
		d[p].sum=d[p].val;
		if(ls(p))add(d[p].sum,d[ls(p)].sum);
		if(rs(p))add(d[p].sum,d[rs(p)].sum);
	}
	int merge(int p,int q){
		if(!p||!q)return p+q;int rt=0;
		if(d[p].rk>d[q].rk)d[p].rs=merge(rs(p),q),rt=p;
		else d[q].ls=merge(p,ls(q)),rt=q;
		pushup(rt);return rt;
	}
	void split(int p,int k,int &x,int &y){
		if(!p){x=y=0;return ;}
		if(d[p].pos<=k)x=p,split(rs(p),k,rs(x),y),pushup(p);
		else y=p,split(ls(p),k,x,ls(y)),pushup(p);
	}
	bool update(int p,int k,int v){
		if(!p)return 0;int ret=0;
		if(d[p].pos==k){add(d[p].sum,v),add(d[p].val,v);return 1;}
		else if(d[p].pos<k)ret=update(rs(p),k,v);
		else ret=update(ls(p),k,v);
		pushup(p);return ret;
	}
	void Add(int &rt,int x,int v){
		if(update(rt,x,v))return ;
		int p=build(x,v),A=0,B=0;split(rt,x,A,B);
		rt=merge(A,merge(p,B));
	}
	int sum(int &rt,int x){
		int A=0,B=0;split(rt,x,A,B);
		int ret=d[B].sum;
		rt=merge(A,B);
		return ret;
	}
}T;

vector<int>tmp;
bool in[N];
void chk(int pos){
	tmp.clear();
	for(int x:cur){
		if(pos-2*cnt[x]>=mx[x])mx[x]=pos-2*cnt[x],in[x]=0;
		else tmp.emplace_back(x);
	}
	cur=tmp;
}

signed main(void){

#ifdef YUNQIAN
	freopen("in.in","r",stdin);
#endif

	n=read();n*=2;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++){
		chk(i);
		if(!in[a[i]])in[a[i]]=1,cur.emplace_back(a[i]);
		mx[a[i]]=max(mx[a[i]],i-1-2*cnt[a[i]]);
		cnt[a[i]]++;
		if(i%2==0)pf[i]=cur;
	}
	cur.clear();reverse(a+1,a+n+1),memset(mx,0xcf,sizeof(mx)),memset(cnt,0,sizeof(cnt)),memset(in,0,sizeof(in));
	for(int i=1;i<=n;i++){
		chk(i);
		if(!in[a[i]])in[a[i]]=1,cur.emplace_back(a[i]),mx[a[i]]=max(mx[a[i]],i-1-2*cnt[a[i]]);
		cnt[a[i]]++;
		if(i%2==0)sf[n-i]=cur;
	}
	reverse(a+1,a+n+1),memset(cnt,0,sizeof(cnt)),memset(in,0,sizeof(in));
	
	int nowS=1;
	for(int i=1;i<=n;i++)T.Add(root[i],0,1);
	for(int i=1;i<=n;i++){
		cnt[a[i]]++;
		if(i%2==1)continue;
		f[i]=nowS;
		for(int v:pf[i])add(f[i],mod-T.sum(root[v],i-2*cnt[v]));
		add(nowS,f[i]);
		for(int v:sf[i])T.Add(root[v],i-2*cnt[v],f[i]);
	}
	cout<<f[n]<<endl;

	return 0;
}
```

---

## 作者：Good_Day_ (赞：1)


- 介绍一种时间复杂度为 $O(n\alpha(n))$，但是实际上跑的很慢的做法。
- 前置知识（？）：[P4062 [Code+#1]Yazid 的新生舞会](https://www.luogu.com.cn/problem/P4062) 或类似的题。
- 我们对原序列两两分组，第 $i$ 组包含了第 $ i \times 2 -1 $ 和第 $ i \times 2 $  这两个数。
- 当一个区间 $[l,r]$ 存在绝对众数时，我们设 $c_{l,r}=1$，否则设 $c_{l,r}=0$。

- 首先，对于一个 $dp_i$ 来说，只有当 $c_{j+1,i} =0$ 时，$dp_j$ 才对 $dp_i$ 有贡献。解决有关绝对众数的问题时，我们常常枚举一个数 $d$，将其作为绝对众数。如果第 $i$ 组两个数都等于 $d$，我们设 $val_{d,i}=1$；两个数中有一个等于 $d$，则设 $val_{d,i}=0$；否则 $val_{d,i}=-1$。那么如果存在一个 $d$，满足 $\sum_{j=l}^r val_{d,i} > 0$，则 $c_{l,r}=1$。
- 对一个 $d$ 来说，我们先找出 $val_{d,i} =0$ 的所有 $i$，并将它们标记出来；再找出 $val_{d,i}=1$ 的所有 $i$，并标记 $i$ 左右最靠近 $i$ 且没有被标记的位置。可以发现，只有被标记的连续段内会互相产生贡献，段和段之间没有贡献。设对于 $d$ 来说有 $s_d$ 个数被标记了，可以发现所有 $s_d$ 的和是 $O(n)$ 级别的。（一个 $i$ 最多只会额外标记 $2$ 个数）在这个过程中，我们需要处理出 $i$ 在哪些 $d$ 被标记了，且这个过程的时间复杂度为 $O(n\alpha(n))$（使用并查集实现）。



- 设 $pre_{d,i}=\sum_{j=1}^i val_{d,j}$，则 $dp_j$ 对 $dp_i$ 有贡献，当且仅当 $pre_{d,i}>pre_{d,j}$。则每次求 $dp_i$ 的值时，我们其实是在询问 $\sum_{j<i,pre_{d,j}<pre_{d,i}}dp_j$。我们维护一个类似于桶的东西，$bk_{d,k}$ 维护了当区间众数为 $d$ 时，所有 $pre_{d,j}=k$ 的 $j$ 的 $dp_j$ 之和。我们设 $sum_d $ 表示 $\sum_{k=-\infty}^{pre_{d,i}-1}bk_{d,k}$，则有 $dp_i=\sum_{j=0}^{i-1}dp_j -\sum_{d=1}^n sum_d$。我们找出 $i$ 被哪些 $d$ 所标记了，并询问 $sum_d$；如果 $i$ 没有被一个 $d$ 所标记，那么 $sum_d$ 一定为 $0$。每次更新完 $i$   的 $dp_i$ 后，再让 $bk_{d,pre_{d,i}} =bk_{d,pre_{d,i}}+dp_i$。

- 对于询问 $sum_d$，有一个重要的性质是对于同一个 $d$ 来说，同一段内两个相邻的 $i$ 的 $pre_{d,i}$ 之差最多只有 $1$。所以对于 $i=i+1$ 之后，$sum_d$ 最多只需要加上一个值就可以被更新：
1. 如果 $val_{d,i}=1$，则 $sum_d=sum_d+bk_{d,pre_{d,i}}$；
2. 如果 $val_{d,i}=0$，则 $sum_d$ 不变；
3. 如果 $val_{d,i}=-1$，则 $sum_d=sum_d-bk_{d,pre_{d,i-1}}$。

如果对于一个 $d$ 来说出现了 $i$ 跨越段的情况，因为段和段之间不可能有贡献，所以我们只需要将 $sum_d$ 和 $bk_d$ 清空即可。所以我们可以做到单次询问 $sum_d$ $O(1)$，而我们的总询问量是 $O(n)$ 级别的（$\sum_{d=1}^ns_d$ 是 $O(n)$ 级别的），所以可以做到 dp 过程复杂度为 $O(n)$。


一些细节：

- 对于一个 $d$ 来说，设被标记的连续段开头为 $x$，则可以认为 $pre_{d,x-1}=0$。（因为我们会在跨越段的时候清空 $bk_d$）这样可以保证所有被标记的 $i$ 的 $\max(pre_{d,i})\leq s_d,\min (pre_{d,i}) \geq -s_d$。所以可以使用 $n$ 个 vector 存储 $bk_{d,pre_{d,i}}$，并在开始 dp 之前提前 resize。

- 一个 $dp_j$ 并不会给 $dp_i$ 产生多次贡献，因为区间 $[j+1,r]$ 最多只有一个绝对众数。


- 谢谢 Alan_Zhao 本题的 $O(n\log n)$ 做法和对题解的一些建议。

[代码云剪贴板](https://www.luogu.com.cn/paste/tte074us)


 

---

## 作者：lzqy_ (赞：1)

场上又是差一步。果然文化课之后就没有脑子了。

首先一个序列 $A$ 是好的当且仅当 $|A| \bmod 2=0$ 且 $A$ 中出现次数最多的元素 $\le |A|/2$，即 $A$ 有绝对众数。

那么一个显然的 dp 刻画就是设 $f_i$ 表示前 $i$ 个元素的划分方案数，有转移方程 $f_i=\sum\limits_{[a_j,\dots,a_i] is\,\texttt{good}} f_{j-1}$。

合法的区间位置是没有规律的，或者说是不连续的，因此考虑从值域入手。

观察到如果区间的一个端点固定，那么绝对众数的**种类**是 $O(\log n)$ 级别的，大概的证明就是每增加 $O(1)$ 个绝对众数的种类，序列的长度至少要翻倍。

因此不难想到对于每一种绝对众数来计算。固定一个端点的限制启发我们使用 cdq 分治优化转移。

-----

关键在于如何用 cdq 分治对每一种绝对众数计算答案。这也是场上被卡住的地方。


考虑先将 $[l,mid]$ 累加到 $(mid,r]$，然后对于每种绝对众数去掉不合法区间的答案。


首先找到这 $O(\log n)$ 个绝对众数是容易的，因为这个数至少在左侧或右侧是绝对众数，前后缀扫一遍就行。



考虑对于绝对众数 $x$ 计算其对 $f_i\,(i \in (mid,r])$ 的负贡献。

观察区间 $[j,i]$ 什么时候是不合法的（需要算进负贡献），设 $x$ 在左侧出现 $v_1$ 次，右侧出现 $v_2$ 次，$S_1=mid-j+1,S_2=i-mid$，那么有 $2(v_1+v_2)>S_1+S_2$，即 $2v_1-S_1>S_2-2v_2$。所以只需要对左侧预处理出 $(2v_i-S_i)$，按值排序后处理处前缀和，然后对于每个右侧的 $i$ 二分查找即可。


------------

cdq 一只 $\log$，枚举绝对众数一只 $\log$，二分一只 $\log$，总时间复杂度 $O(n\log^3 n)$，但是跑不满。

```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define il inline
using namespace std;
const int mod=998244353;
const int maxn=1000010;
il int read(){
	int x=0;
	char c=getchar();
	for(;!(c>='0'&&c<='9');c=getchar());
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+c-'0';
	return x;
}
il void chkmax(int &x,int y){if(y>x)x=y;}
il void chkmin(int &x,int y){if(y<x)x=y;}
il void ad(int &x,int y){if((x+=y)>=mod)x-=mod;}
il void de(int &x,int y){if((x-=y)<0)x+=mod;}
il void mul(int &x,int y){x=1ll*x*y%mod;}
int n,top[2],f[maxn];
int a[maxn],ok[maxn];
int tap1[maxn],tap2[maxn];
pair<int,int>st[2][maxn];
set<int>s;
void clear(int l,int r){
	for(int i=l;i<=r;i++) 
		tap1[a[i]]=tap2[a[i]]=0;
}
int ef(int x,int t){
	if(st[t][1].first<=x||!top[t]) return 0;
//	printf("!!!!%d,%d(%d)[%d]\n",x,st[t][1].first,top[t],t);
	int l=1,r=top[t],mid;
	while(r>l){
		mid=l+r+1>>1;
		if(st[t][mid].first>x) l=mid;
		else r=mid-1;
	}
//	printf("del : %d(%d)\n",st[t][l].second,l);
	return st[t][l].second;
}
void cdq(int l,int r){
	if(l==r) return ad(f[l],ok[l]);
	cdq(l,l+r>>1);
//	printf("%d,%d\n",l,r);
	int mid=l+r>>1,sum[2]={0,0};
	for(int i=l;i<=mid;i++) ad(sum[i&1],f[i]);
	for(int i=mid+1;i<=r;i++) ad(f[i],sum[i&1]);
	for(int i=mid;i>=l;i--)
		if(2*(++tap1[a[i]])>mid-i+1) s.insert(a[i]);
	for(int i=mid+1;i<=r;i++)
		if(2*(++tap2[a[i]])>i-mid) s.insert(a[i]);
	while(!s.empty()){
//		printf("now_num = %d\n",*s.begin());
//		for(int i=l;i<=mid;i++) printf("[[%d]] ",f[i]);
//		printf("\n");
		int x=*s.begin(); 
		s.erase(s.begin());
		top[0]=top[1]=0;
		st[mid&1][++top[mid&1]]=mp(0,f[mid]); 
		for(int i=mid,v=0;i>l;i--)
			v+=2*(a[i]==x)-1,st[i&1^1][++top[i&1^1]]=mp(v,f[i-1]);
		sort(st[0]+1,st[0]+1+top[0],greater<pair<int,int> >());
		sort(st[1]+1,st[1]+1+top[1],greater<pair<int,int> >());
		for(int i=1;i<=top[0];i++)
			ad(st[0][i].second,st[0][i-1].second);
		for(int i=1;i<=top[1];i++)
			ad(st[1][i].second,st[1][i-1].second);
		for(int i=mid+1,v=0;i<=r;i++)
			de(f[i],ef(v+=1-2*(a[i]==x),i&1));
	}
	clear(l,r),cdq(mid+1,r);
}
int main(){
	n=read()*2;
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1,Mx=0;i<=n;i++)
		chkmax(Mx,++tap1[a[i]]),ok[i]=(2*Mx<=i&&(i&1^1));
	memset(tap1,0,sizeof(tap1));
	cdq(1,n),printf("%d\n",f[n]);
//	for(int i=1;i<=n;i++)
//		printf("%d ",f[i]);
//	printf("\n");
	return 0;
} 
```

---

## 作者：tzl_Dedicatus545 (赞：1)

首先你需要知道关于**绝对众数**的一个结论：

1. 把一个区间裂成两半，那么绝对众数一定至少在一半里是绝对众数。
1. 前缀本质不同绝对众数的量级是 $O(\log n)$ 的。

于是我们就可以考虑**分治**，做个前缀和，转移 $[l,mid]$ 对 $[mid+1,r]$ 的贡献。

复杂度 $\Theta(n\log^2 n)$

代码有点难写。

```````cpp
void solve(int l,int r){
	if(l==r)	return ;
	int mid=(l+r)/2;
	solve(l,mid);vint can;
	per(i,mid,l,1){
		S2[a[i]]++;
		if(S2[a[i]]*2>=(mid-i+1)){	can.pb(a[i]);}
	}rep(i,l,mid,1)	S2[a[i]]--;
	rep(i,mid+1,r,1){
		S2[a[i]]++;
		if(S2[a[i]]*2>=(i-mid)){	can.pb(a[i]);}
	}rep(i,mid+1,r,1)	S2[a[i]]--;sort(can.begin(),can.end());can.erase(unique(can.begin(),can.end()),can.end());
	for(auto x:can){
		su[l-1]=0;int B2=(r-l+2);
		rep(i,l,r,1)	su[i]=su[i-1]+(a[i]==x?1:-1);
		rep(i,l,mid,1)	S[su[i]+B2][i%2]+=f[i];
		rep(i,1,B2*2,1)	S[i][0]+=S[i-1][0],S[i][1]+=S[i-1][1];
		// int suu
		rep(i,mid+1,r,1){
			f[i]-=S[su[i]+B2-1][i%2]%mod;chk(f[i]);
		}
		rep(i,0,B2*2,1)	S[i][0]=S[i][1]=0;
	}ll suu[2]={0,0};
	rep(i,l,mid,1)	suu[i%2]+=f[i];suu[0]%=mod,suu[1]%=mod;
	rep(i,mid+1,r,1)	f[i]+=suu[i%2],chk(f[i]);
	solve(mid+1,r);
}
```````

---

## 作者：takanashi_mifuru (赞：1)

WBLT 打所有！

考虑我们有一个非常弱智的 dp 就是 $dp_i$ 表示从第 $2i-1$ 个数打头开始能分出来的方案数，这个转移也非常弱智，就是从 $i$ 打头把一个好的段切出来，然后把 dp 直接拿下。

然后你考虑如何切一个好的段，考虑有一个非常弱智的结论就是如果区间不存在绝对众数就一定有解，因为你每次都一定能消那个最多的，你把后缀所有 $dp$ 全部带上问题正难则反问题就变成了所有区间有绝对众数的 dp 的和。

然后有一个经典结论就是固定起点，那么区间的绝对众数种类数仅有 $\log n$ 种，原因显然，每次都必须翻一倍。

这些是好求的，因为考虑一个数是一个区间的绝对众数，你可以把他刻画成一个数如果是他就是 $1$ 不是他就是 $-1$，而一个点能够当以这个数为绝对众数的区间的终点，当且仅当有某个区间的和为正数，原因显然，然后你把他变成前缀和，你发现这个问题变成了他不能是前缀最小值，非前缀最小值的数的数量依赖于 $1$ 的总数，而 $1$ 的总数就是 $n$。

然后你再维护一下这些非前缀最小值的数的位置和具体数，用平衡树把他维护起来，而到一个点统计答案的时候用这个数的对应序列的前缀和去踩，比他大的就收起来更新 $dp$，时间复杂度考虑众数总共有 $\log n$ 种，而每一种求解都需要 $\log n$ 的时间复杂度，时间复杂度应该是 $O(n\log^2 n)$ 的，不知道为什么跑得飞快。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[1000005];
const int V=1000000;
int dp[1000005];
const int M=998244353;
queue<int> q;
int Max[1000005];//
int dinner[1000005];
int lst[1000005];
bool vis[1000005];
int Min[1000005];
void add(int cur){
   Max[a[cur]]=max(Max[a[cur]],dinner[a[cur]]+(lst[a[cur]]-cur)-1);
   dinner[a[cur]]=dinner[a[cur]]+(lst[a[cur]]-cur)-2;
   lst[a[cur]]=cur;
   if(!vis[a[cur]]){
      vis[a[cur]]=true;
      q.push(a[cur]);
   }
   // }
   return;
}
vector<int> Peonum[1000005];
vector<int> fvv[1000005];
vector<int> Nm[1000005];
vector<int> ruozhi[1000005];
void check(int cur){
   int siz=q.size();
   while(siz--){
      int tmp=q.front();
      q.pop();
      int now=dinner[tmp]+(lst[tmp]-cur);
      if(now<Max[tmp]){
         q.push(tmp);
         Peonum[cur].push_back(tmp);
      }
      else{
         vis[tmp]=false;
      }
   }
   return;
}

void ADD(int cur){
   Min[a[cur]]=min(Min[a[cur]],dinner[a[cur]]-(cur-lst[a[cur]])+1);
   dinner[a[cur]]=dinner[a[cur]]-(cur-lst[a[cur]])+2;
   lst[a[cur]]=cur;
   if(!vis[a[cur]]){
      vis[a[cur]]=true;
      q.push(a[cur]);
   }
   return;
}
void CHECK(int cur){
   int siz=q.size();
   while(siz--){
      int tmp=q.front();
      q.pop();
      int now=dinner[tmp]-(cur-lst[tmp]);
      if(now>Min[tmp]){
         q.push(tmp);
         Nm[cur].push_back(tmp);
         ruozhi[cur].push_back(now);
      }
      else{
         vis[tmp]=false;
      }
   }
   return;
}
void NEED(int cur){
   for(int i=0;i<Peonum[cur].size();i++){
      int tmp=Peonum[cur][i];
      int now=dinner[tmp]-((cur-1)-lst[tmp]);
      fvv[cur].push_back(now);
   }
   return;
}
const int inf=2e9;
class WBLT{
   public:
   static const int lim=2200000<<1;
   stack<int> trash;
   int rt[1000005];
   int val[lim];
   int sum[lim];
   int siz[lim];
   int ch[lim][2];
   const double alpha=0.29;
   int newnode(int x,int weight){
      int tmp=trash.top();
      sum[tmp]=weight;
      val[tmp]=x;
      siz[tmp]=1;
      ch[tmp][0]=ch[tmp][1]=0;
      trash.pop();
      return tmp;
   }
   void gettrash(int id){
      trash.push(id);
      return;
   }
   void pushup(int x){
      sum[x]=sum[ch[x][0]]+sum[ch[x][1]];
      if(sum[x]>=M)sum[x]-=M;
      siz[x]=siz[ch[x][0]]+siz[ch[x][1]];
      val[x]=val[ch[x][1]];
      return;
   }
   void rotate(int x,int k){
      swap(ch[x][0],ch[x][1]);
      swap(ch[ch[x][k^1]][0],ch[ch[x][k^1]][1]);
      swap(ch[x][k],ch[ch[x][k^1]][k^1]);
      pushup(ch[x][k^1]);
      pushup(x);
      return;
   }
   void maintain(int x){
      if(siz[x]==1)return;
      int k;
      if(siz[ch[x][0]]<siz[x]*alpha)k=1;
      else if(siz[ch[x][1]]<siz[x]*alpha)k=0;
      else return;
      if(1.*siz[ch[ch[x][k]][k^1]]*(1-alpha)>=1.*siz[ch[x][k]]*(1-2*alpha))rotate(ch[x][k],k^1);
      rotate(x,k);
      return;
   }
   void insert(int now,int x,int weight){
      if(siz[now]==1){
         if(x==val[now]){
            sum[now]+=weight;
            if(sum[now]>M)sum[now]-=M;
            return;
         }
         int lson=newnode(x,weight);
         int rson=newnode(val[now],sum[now]);
         if(val[lson]>val[rson])swap(lson,rson);
         ch[now][0]=lson;
         ch[now][1]=rson;
         pushup(now);
         return;
      } 
      if(val[ch[now][0]]>=x){
         insert(ch[now][0],x,weight);
      }
      else{
         insert(ch[now][1],x,weight);
      }
      pushup(now),maintain(now);
      return;
   }
   int getup(int cur,int weight){
      if(siz[cur]==1){
         if(val[cur]>weight){
            return sum[cur];
         }
         return 0;
      }
      if(val[ch[cur][0]]>=weight){
         return (sum[ch[cur][1]]+getup(ch[cur][0],weight))%M;
      }
      else{
         return getup(ch[cur][1],weight);
      }
   }
   void init(){
      for(int i=lim-1;i>=1;i--){
         trash.push(i);
      }
      for(int i=1;i<=V;i++){
         rt[i]=newnode(inf,0);
         insert(rt[i],-inf,0);
      }
      return;
   }
}P;
void update(int cur){
   for(int i=0;i<Nm[cur].size();i++){
      int v=Nm[cur][i];
      int now=ruozhi[cur][i];
      P.insert(P.rt[v],now,dp[cur+1]);
   }
   return;
}
int suf;
int query(int cur){
   int ans=suf;
   for(int i=0;i<Peonum[cur].size();i++){
      int v=Peonum[cur][i];
      int now=fvv[cur][i];
      int tmp=P.getup(P.rt[v],now);
      ans-=tmp;
      if(ans<0)ans+=M;
   }
   return ans;
}
int main(){
   // freopen("test.in","r",stdin);
   // freopen("test.out","w",stdout);
   scanf("%d",&n);
   for(int i=1;i<=2*n;i++){
      scanf("%d",&a[i]);
   }
   for(int i=1;i<=V;i++){
      lst[i]=2*n+1;
      Max[i]=0;
   }
   // return 0;
   for(int i=n;i>=1;i--){
      add(2*i),add(2*i-1),check(2*i-1);
   }
   while(!q.empty()){
      vis[q.front()]=false;
      q.pop();
   }
   for(int i=1;i<=V;i++){
      lst[i]=0,Min[i]=0,dinner[i]=0;
   }
   for(int i=1;i<=n;i++){
      NEED(2*i-1),ADD(2*i-1),ADD(2*i),CHECK(2*i);
   }
   P.init();
   dp[2*n+1]=1;
   for(int i=n;i>=1;i--){
      update(2*i);
      suf+=dp[2*i+1];
      if(suf>=M)suf-=M;
      dp[2*i-1]=query(2*i-1);
   }
   printf("%d",dp[1]);
   return 0;
}
```

---

## 作者：_ANIG_ (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_arc159_f)

首先有一个显然的 dp。

$f_n=\sum\limits_{ok(i,n),(n-i+1)\mod 2=0}f_{i-1}$。

其中 $ok(i,n)$ 表示区间 $[i,n]$ 没有绝对众数。

首先有一个性质：以 $n$ 结尾的所有区间的绝对众数构成的集合大小不超过为 $\log n$。

考虑 cdq 分治，计算 $[l,mid]$ 中的 $i$ 对 $n$ 取 $[mid+1,r]$ 的时候的贡献。

可以反着来，先全贡献上，然后有绝对众数的区间产生的贡献。

肯定不能直接枚举这样的区间。

还有一个性质：所有区间 $[a,b](l\le a\le mid,mid<b\le r)$ 的绝对众数构成的集合大小不超过 $2\log n$。

证：

区间 $[l,r]$ 可以拆成 $[l,mid],[mid+1,r]$ 两部分，区间 $[l,r]$ 的绝对众数一定是区间 $[l,mid]$ 或区间 $[mid+1,r]$ 的绝对众数。否则设 $a$ 为实际的绝对众数在区间 $[l,mid]$ 的出现次数，$b$ 为实际绝对众数在区间 $[mid+1,r]$ 的出现次数，则若这个数不是这两个区间的绝对众数，有 $a\le\frac{mid-l+1}2,b\le\frac{r-mid}2$，得到 $a+b\le\frac{r-l+1}{2}$，与这个数是区间 $[l,r]$ 的绝对众数矛盾。

也就是区间 $[l,r]$ 的绝对众数构成的集合就是以 $mid$ 结尾和以 $mid+1$ 开头的并集，也就是 $2\log n$。

枚举区间的左端点 $a$，再枚举绝对众数的值 $k$，看有哪些右端点 $b$，满足 $k$ 在 $[a,b]$ 的出现次数大于 $\frac{b-a+1}2$。

对于每个 $k$，把值等于 $k$ 的下标存到数组 $g$，则 $k$ 在区间 $[a,b]$ 的出现次数为 $c_b-c_a+1$（$c_i$ 表示 $i$ 在 $g$ 中的位置）。

则 $c_b-c_a+1>\frac{b-a+1}2$，解得 $b-2c_b<a-2c_a+1$。

可以对每个 $k$ 分别计算，把 $b$ 按 $b-2c_b$ 排序，这样就变成区间加，差分即可。

时间复杂度 $O(n\log^2n)$。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e6+5,mods=998244353;
int n,p[2*N],wz[2*N];
ll f[2*N],qz[2*N];
struct node{
    int bh,sm;
    friend bool operator<(node a,node b){
        return a.sm<b.sm;
    }
}g[N];
map<int,int>mk,hs;
void solve(int l,int r){
    if(l==r)return;
    int mid=l+r>>1;
    vector<int>cn;
    solve(l,mid);
    cn.clear();
    for(int i=mid;i>=l;i--){
        mk[p[i]]++;
        if(mk[p[i]]>(mid-i+1)/2)if(!hs[p[i]])cn.push_back(p[i]),hs[p[i]]=1;
    }
    mk.clear();
    for(int i=mid+1;i<=r;i++){
        mk[p[i]]++;
        if(mk[p[i]]>(i-mid)/2)if(!hs[p[i]])cn.push_back(p[i]),hs[p[i]]=1;
    }
    hs.clear();
    mk.clear();
    ll sm=0;
    for(int i=l;i<=mid;i++)if(i&1)sm+=f[i-1],sm%=mods;
    for(int i=mid+1;i<=r;i++)if(i-1&1)f[i]+=sm;
    for(int i=0;i<cn.size();i++){
        int c=cn[i],nw=0,idx=0,mn=1e9,mx=0;
        for(int j=l;j<=r;j++){
            if(j<=mid)mn=min(mn,j-nw-nw+1),mx=max(mx,j-nw-nw+1);
            if(p[j]==c)nw++;
            if(j<=mid)continue;
            if(!(j&1))g[j]=(node){j,j-2*(nw-1)},idx++;
            else g[j]=(node){j,1000000000};
        }
        if(!nw)continue;int ng=nw;
        nw=0;
        sort(g+mid+1,g+r+1);
        g[r+1]=(node){n,1000000000};
        wz[mn-1+n]=mid+1;
        for(int j=mn;j<=mx;j++){
            wz[j+n]=wz[j+n-1];
            while(j>g[wz[j+n]].sm)wz[j+n]++;
        }
        for(int j=l;j<=mid;j++){
            if(j&1){
                int w=wz[j-nw-nw+1+n]-1;
                qz[mid+1]+=f[j-1],qz[w+1]-=f[j-1];
            }
            if(p[j]==c)nw++;
        }
        for(int j=mid+1;j<=r;j++)qz[j]+=qz[j-1],f[g[j].bh]-=qz[j];
        for(int j=mid;j<=r+1;j++)qz[j]=0;
    }
    for(int i=l;i<=r;i++)f[i]%=mods;
    solve(mid+1,r);
}
signed main(){
    cin>>n;
    n*=2;
    for(int i=1;i<=n;i++)scanf("%d",&p[i]);
    f[0]=1;
    solve(1,n);
    cout<<(f[n]%mods+mods)%mods;
}
```


---

## 作者：william555 (赞：0)

先考虑如何判断一个序列是否是良好的？直接给出结论：当且仅当序列长度为偶数且序列中没有”严格众数”（出现次数超过数列长度一半的数）。必要性显然：如果有一个数出现次数超过了一半，那么把其它所有数删完以后还剩下一堆相同的数，这时候就无法操作了。充分性可以归纳证明:当序列长度为 $2$ 的时候，没有严格众数即两个数不同，就直接删除；当序列长度大于 $2$ 时，找到序列的众数，再随便找一个和众数相邻的不同的数，将这两个数删除，在序列没有严格众数的情况下，进行一次操作后显然还是没有严格众数，于是我们就一定能删完。

在此基础上，我们把问题转化为了：将长度为 $2n$ 的序列分为若干长度为偶数的段，并且保证每一段均不存在严格众数，求划分方案数。

不难想到一个 $O(n^2)$ 的 DP，$f_i$ 表示将前 $i$ 个数分段的方案数，首先当 $i$ 是奇数时答案为 $0$，然后不难列出转移： 

 $$f_i=\sum _{j<i} f_j \times \big[[j+1,i] \text{ 没有严格众数 }\big ]$$

通过观察可以发现一个性质：一个序列的所有前缀的严格众数的值至多有 $O(\log)$ 种。证明：考虑每一种值第一次成为严格众数的时候出现了多少次：第 $1$ 个数至少 $1$ 次，第 $2$ 个数至少 $2$ 次，……，第 $k$ 个数至少 $2^{k-1}$ 次，所以至多只会有 $\log(n)$ 个。同理，一个序列的所有后缀的严格众数的值至多只有 $O(\log)$ 种。

又注意到每个区间至多只会有一个严格众数，于是我们可以把转移写成:

$$f_i=\sum_{j<i} f_j - \sum_x \sum_j f_j \times \big[ [j+1,i] \text{ 的严格众数是 } x\big]$$

 令 $cnt_{x,i}$ 为 $x$ 在 $[1,i]$ 出现的次数 $\big[ [j+1,i] \text{ 的严格众数是 }x  \big]$ 即 $cnt_{x,i}-cnt_{x,j}> \frac {i-j} 2$，即 $2cnt_{x,i}-i>2cnt_{x,j} -j$。根据上述的性质，以 $i$ 结尾的所有区间的严格众数只有 $O(\log)$ 种，于是有效的 $x$ 就只有这几个值。而对于每个 $j$，以 $j+1$ 开头的所有区间的严格众数只有 $O(\log)$ 种，所以 $j$ 能够贡献到的 $x$ 就只有这几个值。于是我们对于每一个 $x$ 用树状数组查询所有的 $j<i,2cnt_{x,j}-j<2cnt_{x,i}-i$ 的 $f_j$ 之和。

总复杂度 $O(n\log ^2n)$。

```c++
#include<bits/stdc++.h>
using namespace std;
const int BS=1<<20|5;
char buf[BS],*P1,*P2;
inline char gc(){
    if(P1==P2)P2=(P1=buf)+fread(buf,1,BS,stdin);
    return P1==P2?EOF:*(P1++);
}
inline int in(){
    int x=0,f=1;char ch=gc();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=gc();}
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=gc();
    return x*f;
}
const int N=1e6+5,mod=998244353;
inline int add(int a,int b){return a+b>=mod?a+b-mod:a+b;}
inline void Add(int &a,int b){a+=b;if(a>=mod)a-=mod;}
inline int mul(int a,int b){return 1ll*a*b%mod;}
int n,a[N],cnt[N],mx[N],mn[N],now[N],mark[N];
vector<int> V[N];
struct node{
	vector<int> num;
	int n,*bit;
	void insert(int x){
		num.push_back(x);
	}
	void add(int p,int v){
		p=lower_bound(num.begin(),num.end(),p)-num.begin()+1;
		for(int i=p;i<=n;i+=i&-i)Add(bit[i],v);
	}
	int get(int p){
		p=lower_bound(num.begin(),num.end(),p)-num.begin();
		int s=0;
		for(int i=p;i;i-=i&-i)Add(s,bit[i]);
		return s;
	}
	void init(){
		sort(num.begin(),num.end());
		num.erase(unique(num.begin(),num.end()),num.end());
		bit=new int [(n=num.size())+1];
		for(int i=0;i<=n;i++)bit[i]=0;
	}
}b[N];
int sum,f[N];
void update(int p){
	Add(sum,f[p]);
	for(int i:V[p])b[i].add(cnt[i]*2-p,f[p]);
}
int main(){
	n=in();
	for(int i=1;i<=n<<1;i++)a[i]=in(),cnt[a[i]]++,mx[i]=-1e9;
	vector<int> v;
	for(int i=n+n-1;i>=0;i--){
		cnt[a[i+1]]--;
		for(int j=0;j<v.size();j++){
			int x=v[j];
			now[x]=2*cnt[x]-i;
			if(now[x]>=mx[x]){
				mx[x]=now[x],mark[x]=0;
				swap(v[j],v.back());
				v.pop_back();j--;
			}
		}
		now[a[i+1]]=cnt[a[i+1]]*2-i,mx[a[i+1]]=max(mx[a[i+1]],now[a[i+1]]);
		if(!mark[a[i+1]])v.push_back(a[i+1]),mark[a[i+1]]=1;
		if(i&1)continue;
		V[i]=v;
		for(int j:v)b[j].insert(now[j]);
	}
	for(int i=1;i<=n<<1;i++){
		b[i].init();
		cnt[i]=0,mn[i]=1e9,mark[i]=0;
	}
	v.clear();
	f[0]=1;
	update(0);
	for(int i=1;i<=n<<1;i++){
		for(int j=0;j<v.size();j++){
			int x=v[j];
			now[x]=2*cnt[x]-i;
			if(now[x]<=mn[x]){
				mn[x]=now[x],mark[x]=0;
				swap(v[j],v.back());
				v.pop_back();j--;
			}
		}
		cnt[a[i]]++;now[a[i]]=cnt[a[i]]*2-i,mn[a[i]]=min(mn[a[i]],now[a[i]]);
		if(!mark[a[i]])v.push_back(a[i]),mark[a[i]]=1;
		if(i&1)continue;
		f[i]=sum;
		for(int j:v)Add(f[i],mod-b[j].get(now[j]));
		if(i<n<<1)update(i);
	}
	cout<<f[n<<1]<<endl;
	return 0;
}
```



---

## 作者：xfrvq (赞：0)

## ARC159F

一个序列是好的条件是：不存在绝对众数。容易证明：存在绝对众数必定无法删空；不存在绝对众数，每次贪心用余量最多的数去消别的就能删空。

现在直接 dp 是 $O(n^2)$，在算 $f_i$ 时需要求出：$[j,i]$ 不存在绝对众数的所有 $f_{j-1}$ 之和。

容易根号分治做到 $O(n\sqrt n)$：现在要表示出所有有绝对众数的区间。长度 $\le2\sqrt n$ 的区间暴力做；$\gt2\sqrt n$ 的区间，众数只能是全局出现 $\gt\sqrt n$ 次的数。验证这 $\sqrt n$ 种数，设 $x$ 的前缀出现次数 $c_{x,1\cdots n}$，$[l,r]$ 绝对众数是 $x$ 的条件是：$2(c_{x,r}-c_{x,l-1})\gt r-l+1$，即 $l-1-2c_{x,l-1}\gt r-2c_{x,r}$。但在本题数据范围下没什么用。

**关键提示：以 $i$ 结尾的区间，绝对众数只会有 $O(\log n)$ 种**。证明：想出现一种新的众数，要抵消之前众数的个数，区间长度就要翻倍。

然后就很简单：枚举 $i$ 结尾区间能出现的众数 $x$，求 $j-2c_{x,j}\gt i-2c_{x,i}$ 的 $f_j$ 的和。没法统计所有 $j$，于是对于 $j$ 只把 $f_j$ 贡献到所有 $j$ 开头区间能出现的众数 $y$ 位置处。$n$ 棵平衡树实现。

现在的问题是：如何找到 $i$ 结尾区间能出现所有众数（$i$ 开头区间同理）。$x$ 能成为答案的条件是：$\max_{j=0}^{i-1}j-2c_{x,j}\gt i-2c_{x,i}$。如果维护序列 $b_j=j-2c_{j,i}$，现在每次要给 $b_{a_i}$ 减 $1$，其余加 $1$。

不妨维护 $d_j$ 代表 $b_j$ 历史最大值与 $b_j$ 之差。现在每次要给 $d_{a_i}$ 加 $1$，其余减 $1$，所有 $d_j\gt0$ 的会成为答案，然后 $d_j\gets\max(d_j,0)$。简化一下，$d_j\le0$ 的数我们根本不用维护，在给 $d_{a_i}+1$ 前 $d_{a_i}\gets\max(0)$ 即可。再简化一下，全局 $-1$ 也可以省略，变成单点 $+2$ 与判断 $d'_j\gt i$。用 `set` 外加维护 $d'_j$ 轻松实现。

总复杂度时空 $O(n\log^2 n)/O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5,M = N * 32;
const int mod = 998244353;

int n,a[N],b[N],f[N],tot[2];
bool vis[N];
int cnt,lc[M],rc[M],val[M],num[M],sum[M],pri[M];
set<pair<int,int>> S;
vector<int> P[2][N];

struct fhq{
	int rt,x,y;
	
	void psu(int i){ sum[i] = (0ll + sum[lc[i]] + num[i] + sum[rc[i]]) % mod; }
	
	int mrg(int x,int y){
		if(!x || !y) return x | y;
		if(pri[x] < pri[y]) return rc[x] = mrg(rc[x],y),psu(x),x;
		return lc[y] = mrg(x,lc[y]),psu(y),y;
	}
	
	void spl(int i,int k,int &x,int &y){
		if(!i) return void(x = y = 0);
		if(val[i] <= k) x = i,spl(rc[i],k,rc[i],y);
		else y = i,spl(lc[i],k,x,lc[i]);
		psu(i);
	}
	
	void ins(int p,int v){
		++cnt,val[cnt] = p,num[cnt] = sum[cnt] = v,pri[cnt] = rand();
		spl(rt,p,x,y),rt = mrg(mrg(x,cnt),y);
	}
	
	int qry(int p,int s = 0){
		spl(rt,p,x,y),s = sum[y],rt = mrg(x,y);
		return s;
	}
} T[N];

int main(){
	scanf("%d",&n),n *= 2;
	for(int i = 1;i <= n;++i) scanf("%d",a + i),vis[i] = 1;
	for(int _ = 0;_ < 2;++_){
		S.clear();
		for(int i = 1;i <= n;++i) S.emplace(0,i),b[i] = 0;
		for(int i = 1;i <= n;++i){
			S.erase({-b[a[i]],a[i]}); 
			b[a[i]] = max(b[a[i]],i - 1) + 2;
			S.emplace(-b[a[i]],a[i]);
			for(auto[x,y] : S) if(x < -i) P[_][i].push_back(y); else break;
		}
		reverse(a + 1,a + n + 1);
	}
	f[0] = tot[0] = 1;
	for(int i = 1;i <= n;++i) T[i].ins(0,1),b[i] = 0;
	for(int i = 1;i <= n;++i) if(i % 2 == 0){
		f[i] = tot[i & 1],++b[a[i]];
		for(int x : P[0][i]) (f[i] += mod - T[x].qry(i - 2 * b[x])) %= mod;
		for(int x : P[1][n - i + 1]) T[x].ins(i - 2 * b[x],f[i]);
		(tot[i & 1] += f[i]) %= mod;
	} else ++b[a[i]];
	printf("%d\n",f[n]);
	return 0;
}
```

---

