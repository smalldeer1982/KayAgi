# [COTS 2023] 平均数 Prosjek

## 题目背景



译自 [Izborne Pripreme 2023 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2023/) D1T2。$\texttt{3s,0.5G}$。

祝 NaCly_Fish 生日快乐！（2024.7.28）

感谢 @Rainbow_qwq 修复交互库。警示后人：慎用 `multiset.count`（复杂度可退化至线性）。


## 题目描述


在黑板上有 $N$ 个非负整数。在一次操作中，可以选择黑板上的两个整数 $a,b$ 满足 $2\mid (a+b)$，将 $a,b$ 从黑板上擦去，然后写下 $(a+b)/2$。注意到每次操作后，黑板上的数都是整数。

试判断是否能让黑板上只剩下一个数。如果可以的话，还需要给出一组解。


## 说明/提示


#### 样例解释

样例 $2$ 解释：$[\boldsymbol{\textcolor{red}{1}},2,3,4,\boldsymbol{\textcolor{red}{5}},6] \to [\boldsymbol{\textcolor{red}{3}},2,\boldsymbol{\textcolor{red}{3}},4,6]\to [3,2,\boldsymbol{\textcolor{red}{4}},\boldsymbol{\textcolor{red}{6}}]\to [\boldsymbol{\textcolor{red}{5}},\boldsymbol{\textcolor{red}{3}},2]\to [\boldsymbol{\textcolor{red}{4}},\boldsymbol{\textcolor{red}{2}}]\to [3]$。

#### 数据范围

对于 $100\%$ 的数据，保证：

- $1\le T\le 10^5$；
- $1\le N,\sum N\le 10^6$；
- $0\le a_i\le 10^{18}$。

| 子任务编号 | 分值 | 约束  |
|:-----:|:------:|:-------:|
| $1$  | $9$  | $T\le 100$，$N\le 7$   |
| $2$  | $23$  | $T\le 100$，$a_i\le 10$  |
| $3$  | $16$  | $a_i$ 都为偶数 |
| $4$  | $52$  | 无额外约束 |




## 样例 #1

### 输入

```
2
3
1 4 5
4
1 4 5 5```

### 输出

```
-1
1 5
3 5
4 4```

## 样例 #2

### 输入

```
1
6
1 2 3 4 5 6```

### 输出

```
1 5
3 3
4 6
3 5
2 4```

# 题解

## 作者：DaiRuiChen007 (赞：3)

**题目大意**

> 给定 $a_1\sim a_n$，每次操作选择 $a_x,a_y$ 使得他们的和为偶数，删除 $a_x,a_y$ 并加入 $\dfrac{a_x+a_y}2$。
>
> 构造一种方案使得最终仅剩一个数，或报告无解。
>
> 数据范围：$n\le 10^6$。

**思路分析**

按 $a_i \bmod 4$ 分成四个集合 $S_0\sim S_3$。

先考虑全是偶数的情况，每次操作取出两个 $\bmod 4$ 同余数操作，一定得到偶数。

不断操作，停止时一定合法，或是 $|S_0|=|S_2|=1$，操作两个偶数即可。

全是奇数的情况也类似。

然后考虑一般的情况。

我们观察到：如果 $S_0,S_2$ 均非空，或 $S_1,S_3$ 均非空，一定有解。

设 $S_0,S_2$ 非空，各取出一个元素 $x_0,x_2$，剩下的元素任意操作，不可操作时奇数偶数都至多一个。

- 如果仅剩一个奇数 $y$，操作 $x_0,x_2$ 再和 $y$ 操作。

- 如果仅剩一个偶数 $y$，操作与 $y$ 模 $4$ 同余的 $x$ 得到一个偶数，再和另一个 $x$ 操作。

- 否则设剩一奇一偶，设他们 $\bmod 4$ 余 $0,1$，不妨当前的四个数是 $4a,4b,4c+1,4d+2$：

  如果 $a+d$ 为奇数：那么操作 $4a,4d+2$ 再与 $4c+1$ 操作得到：$a+d+2c+1$ 为偶数，和 $4b$ 操作即可。

  如果 $b+d$ 为奇数同样可构造，否则一定有 $a\equiv b\pmod 4$，此时操作 $4a,4b$ 再和 $4d+2$ 操作得到 $a+b+2d+1$ 为奇数再和 $4c+1$ 操作即可。

综上此时我们一定能构造出解，实现时对 $n\le 4$ 的情况爆搜即可。

否则我们要尝试构造 $x_0,x_2$。

不妨假设存在若干偶数，我们找到最小的 $d$ 使得这些偶数第 $d$ 位不全相同。

取出两个第 $d$ 位不同的数 $x,y$，可以写成 $x=2^{d+1}a+2^d+r,y=2^{d+1}b+r$，操作这两个数得到 $2^d(a+b)+(2^{d-1}+r)$。

容易发现这个数的第 ${d-1}$ 位和其他数的第 $d-1$ 位不同，重复构造到 $d=2$ 为止即可，记得判断偶数数量是否足够。

可以证明以上条件是充分的。

时间复杂度 $\mathcal O(n\log V)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
#define sz(a) (int(a.size()))
using namespace std;
const int inf=1e9;
vector <array<ll,2>> wys;
vector <ll> a[4];
void opr(int x,int y) {
	ll u=a[x].back(); a[x].pop_back();
	ll v=a[y].back(); a[y].pop_back();
	ll w=(u+v)>>1;
	wys.push_back({u,v}),a[w&3].push_back(w);
}
void sol() {
	vector <ll> rem;
	if(sz(a[0])&&sz(a[2])) rem={a[0].back(),a[2].back()},a[0].pop_back(),a[2].pop_back();
	else rem={a[1].back(),a[3].back()},a[1].pop_back(),a[3].pop_back();
	while(true) {
		if(sz(a[0])+sz(a[2])>1) {
			if(sz(a[0])&&sz(a[2])) opr(0,2);
			else sz(a[0])?opr(0,0):opr(2,2);
		} else if(sz(a[1])+sz(a[3])>1) {
			if(sz(a[1])&&sz(a[3])) opr(1,3);
			else sz(a[1])?opr(1,1):opr(3,3);
		} else break;
	}
	for(int o:{0,1,2,3}) for(ll x:a[o]) rem.push_back(x);
	vector <array<ll,2>> cur;
	function<bool(vector<ll>)> dfs=[&](vector<ll> q) {
		if(sz(q)==1) {
			for(auto z:wys) cout<<z[0]<<" "<<z[1]<<"\n";
			for(auto z:cur) cout<<z[0]<<" "<<z[1]<<"\n";
			return true;
		}
		for(int i=0;i<sz(q);++i) for(int j=i+1;j<sz(q);++j) if((q[i]+q[j])%2==0){
			cur.push_back({q[i],q[j]});
			vector <ll> p{(q[i]+q[j])/2};
			for(int k=0;k<sz(q);++k) if(k!=i&&k!=j) p.push_back(q[k]);
			if(dfs(p)) return true;
			else cur.pop_back();
		}
		return false;
	};
	dfs(rem);
}
int cnt(int o) {
	for(int i=0;i<60;++i) for(int j=1;j<sz(a[o]);++j) {
		if((a[o][0]^a[o][j])>>i&1) return i;
	}
	return inf;
}
void go(int o) {
	for(int i=cnt(o);i>1;--i) {
		int j=1;
		for(;!((a[o][0]^a[o][j])>>i&1);++j);
		ll x=a[o][0],y=a[o][j];
		vector <ll> q;
		for(int k=1;k<sz(a[o]);++k) if(k^j) q.push_back(a[o][k]);
		q.push_back(x),q.push_back(y);
		a[o].swap(q),opr(o,o);
	}
}
void solve() {
	wys.clear();
	for(int o:{0,1,2,3}) a[o].clear();
	int n; cin>>n;
	for(ll x;n--;) cin>>x,a[x&3].push_back(x);
	if(!sz(a[0])&&!sz(a[2])) {
		while(sz(a[1])>1||sz(a[3])>1) sz(a[1])>1?opr(1,1):opr(3,3);
		if(sz(a[1])&&sz(a[3])) opr(1,3);
		for(auto z:wys) cout<<z[0]<<" "<<z[1]<<"\n";
		return ;
	}
	if(!sz(a[1])&&!sz(a[3])) {
		while(sz(a[0])>1||sz(a[2])>1) sz(a[0])>1?opr(0,0):opr(2,2);
		if(sz(a[0])&&sz(a[2])) opr(0,2);
		for(auto z:wys) cout<<z[0]<<" "<<z[1]<<"\n";
		return ;
	}
	if((sz(a[0])&&sz(a[2]))||(sz(a[1])&&sz(a[3]))) return sol();
	for(int o:{0,1,2,3}) if(sz(a[o])>1&&cnt(o)<sz(a[o])) return go(o),sol();
	cout<<"-1\n";
}
signed main() {
	freopen("meow.in","r",stdin);
	freopen("meow.out","w",stdout);
	ios::sync_with_stdio(false);
	int T; cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：Or1gam1 (赞：1)

这不是模拟赛的神仙构造题么，在这里复述一下题解（）

先把所有数按模 4 意义下的值分组，分为 $S_0,S_1,S_2,S_3$，一些性质：如果在 $S_0,S_2$ 内部选两个数进行操作，则会得到偶数，如果选一个 $S_0$ 中的元素和一个 $S_2$ 中的元素进行操作，则会得到奇数，$S_1,S_3$ 同理。

如果所有数都为奇数或都为偶数，则一定有解。以都为偶数为例，在 $S_0$ 和 $S_2$ 内部进行操作，操作后一定得到一个偶数。最后要么只剩一个偶数，要么剩下两个偶数，再对剩下的两个偶数操作即可，接下来不考虑全奇数或全偶数的情况。

考虑什么时候会无解。

如果无论如何操作，任意时刻奇数和偶数都只有一组（比如不能同时存在 $S_0$ 中的元素和 $S_2$ 中的元素），那么最后会剩下一奇一偶，这种情况无解。

接下来证明，如果可以使 $|S_0|\ge 1\bigwedge |S_2|\ge 1$ 或 $|S_1|\ge 1\bigwedge |S_3|\ge 1$，则一定有解。

以 $|S_0|\ge 1\bigwedge |S_2|\ge 1$ 为例，先保留任意一个 $S_0$ 中元素 $x_0$，和任意一个 $S_2$ 中元素 $x_2$，对剩下的所有数任意操作至不能再操作，有以下几种情况。

- 剩下一个偶数：这个数不是 $S_0$ 中的元素就是 $S_2$ 中的元素，如果是 $S_0$ 中的元素，就先和 $x_0$ 操作，然后再和 $x_2$ 操作，如果是 $S_2$ 中的元素同理。

- 剩下一个奇数：将 $x_0$ 和 $x_2$ 操作得到一个奇数，再和剩下的奇数合并即可。

- 剩下一奇一偶，以这四个数模 4 意义下的值分别为 0,0,2,1 为例，设这四个数分别为 $4a_1+0,4a_2+0,4a_3+2,4a_4+1$。

  - 如果 $a_1,a_2$ 奇偶性不同，则其中一定有一个和 $a_3$ 奇偶性不同，设 $a_2$ 和 $a_3$ 奇偶性不同，先操作 $4a_2+0,4a_3+2$ 得到 $2(a_2+a_3)+1$，再和 $4a_4+1$ 操作，得到 $a_2+a_3+2a_4+1$，这是一个偶数，再和 $4a_1+0$ 操作即可。
  - 如果 $a_1,a_2$ 奇偶性相同，先操作 $4a_1+0,4a_2+0$，变为 $2(a_1+a_2)$，则 $2(a_1+a_2)\in S_0$，于是转化为上面只剩一个奇数的情况。

接下来考虑构造出 $x_0,x_2$，此时不需要考虑奇数，因为如果奇数能操作出一个偶数，就一定存在 $x_1,x_3$。对于所有偶数，找到其最低的二进制位 $d$，满足存在两个偶数的第 $d$ 位不相同。设这两个数为 $a_12^{d+1}+b,a_22^{d+1}+2^d+b$，操作这两个数，得到 $(a_1+a_2)2^d+2^{d-1}+b$，其第 $d-1$ 位一定与其他偶数不同，然后再继续向下操作，操作至 $d=1$ 时停止，此时已经存在 $x_0$ 和 $x_2$ 了。

另外注意到每次操作最低只能改变第 $d-1$ 位，更低的位不会变，所以这也是最有可能构造出 $x_0,x_2$ 的方法，如果能构造出 $x_0,x_2$，就一定能用这种方法构造。如果元素的数量不支持构造出 $x_0,x_2$，则无解。

复杂度为 $O(n\log V)$。

---

