# [USACO22OPEN] 262144 Revisited P

## 题目描述

Bessie 喜欢在她的手机上下载游戏玩，尽管她确实发现对于她的大蹄子来说使用小触摸屏相当麻烦。

她对目前正在玩的游戏特别着迷。游戏从 $N$ 个 $1\ldots 10^6$ 范围内的正整数组成的序列 $a_1,a_2,\ldots,a_N$（$2\le N\le 262,144$）开始。在一次行动中，Bessie 可以取两个相邻的数字并将它们替换为一个大于两数最大值的数字（例如，她可以将相邻的一对数 $(5,7)$ 替换为 $8$）。游戏在 $N-1$ 次行动后结束，此时只剩下一个数字。游戏目标是**最小化**这个最终的数字。

Bessie 知道这个游戏对你来说太容易了。所以你的任务不仅仅是在 $a$ 上以最优方式玩游戏，而是在 $a$ 的每个连续子段上玩游戏。

输出 $a$ 的所有 $\frac{N(N+1)}{2}$ 个连续子段的最小最终数字之和。

## 说明/提示

共有 $\frac{6\cdot 7}{2}=21$ 个连续子段。例如，连续子段 $[1,3,1,2,1]$ 的最小可能的最终数字是 $5$，可以通过以下操作序列达到：
```
初始     -> [1,3,1,2,1]
合并 1&3 -> [4,1,2,1]
合并 2&1 -> [4,1,3]
合并 1&3 -> [4,4]
合并 4&4 -> [5]
```

以下是每个连续子段的最小可能的最终数字：

```
final(1:1) = 1
final(1:2) = 4
final(1:3) = 5
final(1:4) = 5
final(1:5) = 5
final(1:6) = 11
final(2:2) = 3
final(2:3) = 4
final(2:4) = 4
final(2:5) = 5
final(2:6) = 11
final(3:3) = 1
final(3:4) = 3
final(3:5) = 4
final(3:6) = 11
final(4:4) = 2
final(4:5) = 3
final(4:6) = 11
final(5:5) = 1
final(5:6) = 11
final(6:6) = 10
```

【测试点性质】

- 测试点 2-3 满足 $N\le 300$。
- 测试点 4-5 满足 $N\le 3000$。
- 测试点 6-8 中，输入的序列中所有数的值不超过 $40$。
- 测试点 9-11 中，输入的序列是不下降的。
- 测试点 12-23 没有额外限制。


## 样例 #1

### 输入

```
6
1 3 1 2 1 10```

### 输出

```
115```

# 题解

## 作者：Elma_ (赞：19)

首先有一个显然的区间 DP：设 $f_{i,j}$ 为区间 $[i,j]$ 的权值，则 $f_{i,j} = \min \limits_{i \leq k < j}  \{ \max(f_{i,k}, f_{k+1,j}) + 1\}$。

进一步地，由于 $f_{i,k}$ 关于 $k$ 单调不降，$f_{k+1,j}$ 关于 $k$ 单调不升，因此我们只需要二分出最大的 $k'$ 使得 $f_{i,k'} \leq f_{k' + 1,j}$，然后在 $k \in \{k',k'+1\}$ 中做决策即可，也可以利用决策单调性做到 $\mathcal{O}(n^2)$。

但到此为止，直接 DP 似乎已经看不到前途了。我们可能需要找到一种更优的计算方式。

------------------------------------------------------------------

考虑一种无脑的合并方式：每次将区间划分成长度尽量相同的两部分，然后归并。这样我们可以得到答案的一个上界 $\max a_i + \lceil \log n \rceil$。既然答案的上界只有 $\mathcal{O}(A)$，我们不妨转变一下思路，考虑依次枚举 $v$，然后计算权值 $\geq v$ 的区间个数。

由于 $f_{i,k}$ 关于 $k$ 单调不降，我们考虑对于每个左端点 $i$ 维护最大的右端点 $r_i$ 使得 $[i,r_i)$ 的权值不大于 $v$。维护的方式如下：初始时 $r_i = i$，当 $v-1 \to v$ 时，我们依次枚举 $i$，令 $r_i \gets r_{r_i}$，然后对于所有 $a_i = v$ 的位置 $i$，令 $r_i \gets i+1$。

我们接下来说明为什么上面的做法是对的。当 $i = r_i$ 时正确性显然。否则考虑 $[i,r_i)$ 和 $[r_i,r_{r_i})$ 这两个区间，不妨设它们分别为区间 $\mathcal{A},\mathcal{B}$。当 $\mathcal{A}$ 和 $\mathcal{B}$ 的权值都是 $v-1$ 正确性显然。否则若 $\mathcal{A}$ 的权值小于 $v - 1$，那么由 $\mathcal{A}$ 的极大性，有 $a_{r_i} \geq v-1$。若 $a_{r_i} \geq v$，则此时 $r_{r_i} = r_i$，否则 $a_{r_i} = v-1$，两者的正确性都是显然的。当 $\mathcal{B}$ 的权值小于 $v-1$ 时同理。

于是我们得到了一个 $\mathcal{O}(nA)$ 的做法。目前而言，算法的效率上似乎没有什么实质性的进展，我们还需要寻找加速的方法。

---------------------------------------------

不妨再关注一下 $f$ 的单调性。如果一个区间的 $f$ 值 $\leq v$，那么其所有子区间的 $f$ 值都 $\leq v$。

这句话听上去是一句废话，但我们可以做一个容斥，每次改为计算权值 $< v$ 的区间个数。这时考虑一类特殊的区间：我们称一个区间是 $[l,r]$ 是 “极大的”，当且仅当其向左或向右扩展都会使 $f$ 值增大。

对于所有权值为 $v-1$ 的极大区间，显然它们不会互相包含。于是我们要求的就变成了这样的一个问题：给定 $L$ 个左右端点单调增的区间，求它们覆盖的区间数。这可以通过简单容斥做到 $\mathcal{O}(L)$。

也就是说，如果我们直接在枚举 $v$ 的过程中维护极大区间的集合，就能够避免每次 $\mathcal{O}(n)$ 的枚举。但从直觉上看，极大区间的数量似乎还是可能很多，复杂度究竟能优化多少还有待商榷。

--------------------------

为此，我们需要证明如下引理：

> **引理**：设 $f(n)$ 表示长度为 $n$ 的序列的极大区间的数量，则 $f(n)=O(n \log n)$。

**证明**：我们可以证明，$f(n) \leq f(\log n!) = f(\log 1 + \cdots + \log n) \leq f(n \log n)$。

考虑原序列的笛卡尔树，设其中一个最大元素的位置为 $p$，则有：
$$
f(n) \leq f(p-1) + f(n - p) + \text{val}(p)
$$
其中 $\text{val}(p)$ 为原序列中包含位置 $p$ 的极大区间数。不妨设 $2p \leq n$，我们可以证明，$\text{val}(p) \leq \mathcal{O}(p \log \frac{n}{p})$。

具体来说，我们设 $\text{val}_{k}(p)$ 表示包含 $p$，且权值为 $a_p + k$ 的极大区间数，则有 $\text{val}_k(p) \leq \min(p,2^k)$，其中 $0 \leq k \leq \lceil \log_2 n \rceil$。$p$ 的限制是因为权值相同的极大区间左端点位置一定不同，而 $2^k$ 的限制是因为权值从 $a_p + k - 1$ 到 $a_p + k$ 必然会经过一次扩展，每次扩展我们可以选择向左或是向右，而我们需要从 $a_p$ 开始扩展 $k$ 次。

考虑对所有 $\text{val}_i(p)$ 求和。注意到，当 $0 \leq k < \lceil \log_2 p \rceil$ 时，$\min(p,2^k) = 2^k$，这部分 $\text{val}_i(p)$ 的和为 $\mathcal{O}(p)$。当 $\lceil \log_2p \rceil \leq k \leq \lceil \log_2 n \rceil$ 时，$\min(p,2^k) = p$，这部分 $\text{val}_i(p)$ 的和为 $\mathcal{O}(p \log \frac{n}{p})$。于是命题得证。

对于引理的证明，我们考虑归纳。由 $\mathcal{O}(p \log \frac{n}{p}) \leq \mathcal{O}(\log\frac{n}{p} + \log\frac{n-1}{p-1} + \cdots + \log \frac{n-p+1}{1}) \leq \mathcal{O}(\log \binom{n}{p}) \leq \mathcal{O}(\log \frac{n!}{(p-1)!(n-p)!})$，则有
$$
\begin{aligned}
f(n) &\leq f(p-1) + f(n-p) + \text{val}(p) \\
     &\leq \mathcal{O}(\log(p-1)!) + \mathcal{O}(\log(n-p)!) + \mathcal{O}(\log n! - \log(p-1)! - \log (n-p)!) \\
     &\leq \mathcal{O}(n!)
\end{aligned}
$$
则原命题得证。

-----------------------------

接下来只需要考虑如何维护极大区间。对当前的权值 $v$，我们称一个区间 $[l,r)$ 是一个段，当且仅当其中所有元素都不大于 $v$，且 $\min(a_{l-1},a_r) > v$。对于当前的所有极大区间，其要么权值为 $v$，要么是一个段。

我们将所有极大区间储存在其所属的段 $[l,r)$ 的左端点的集合 $\text{seg}_l$ 内。当 $v-1 \to v$ 时，我们依次执行以下步骤：对所有需要更新的段，更新极大区间并重新计算它们的贡献。合并过后，段内所有极大区间的权值变为 $v$。接着在所有 $a_i = v$ 的位置添加一个极大区间 $[i,i+1)$，然后将相邻的段合并。

使用双向链表维护段的合并，总时间复杂度为 $\mathcal{O}(A + n \log n)$。具体细节见代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
typedef vector <int> vi;
typedef pair <int, int> pi;
typedef long long LL;
const int N = 3e5 + 5, M = 1e6 + 35;
int n, a[N], pre[N], nex[N]; LL cur;
vi p[M];
list <pi> seg[N];
LL sum(int l, int r) {
    return 1LL * (l + r) * (r - l + 1) / 2;
}
LL calc(list <pi> L) {
    LL ret = 0;
    for (auto it = L.begin(); it != L.end(); it++) {
        auto [x, y] = *it;
        if (next(it) == L.end()) {
            ret += sum(1, y - x);
            break;
        } else {
            int nx = next(it) -> fi;
            ret += 1LL * (nx - x) * y - sum(x, nx - 1);
        }
    }
    return ret;
}
void upd(list <pi> &L) {
    if (L.size() <= 1) 
        return;
    cur += calc(L);
    int mx = -1;
    list <pi> nL;
    auto it = L.begin();
    for (auto [x, y] : L) {
        while (next(it) != L.end() && next(it) -> fi <= y)
            it++;
        if (it -> se > mx) {
            nL.push_back({x, mx = it -> se});
        }
    }
    swap(L, nL);
    cur -= calc(L);
}
int main() {
    ios :: sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        p[a[i]].push_back(i);
    }
    cur = 1LL * n * (n + 1) / 2;
    for (int i = 1; i <= n; i++) 
        pre[i] = nex[i] = i;
    LL ans = 0;
    vi q;
    for (int v = 1; cur > 0; v++) {
        ans += cur;
        vi nq;
        for (auto l : q) {
            upd(seg[l]);
            if (seg[l].size() > 1) nq.push_back(l);
        }
        for (auto i : p[v]) {
            int l = pre[i], r = nex[i + 1];
            bool add = seg[l].size() <= 1;
            nex[l] = r, pre[r] = l;
            seg[l].push_back({i, i + 1});
            cur--;
            seg[l].splice(seg[l].end(), seg[i + 1]);
            add &= seg[l].size() > 1;
            if (add) nq.push_back(l); 
        }
        swap(q, nq);
    }
    cout << ans << "\n";
    return 0;   
}
```


---

## 作者：_ANIG_ (赞：7)

[传送门](https://www.luogu.com.cn/problem/P8275)

首先有个显然的区间 dp。

设 $f_{l,r}$ 表示区间 ${l,r}$ 的答案。

则 $f_{l,r}=\min\limits_{l\le k<r}\{\max(f_{l,k},f_{k+1,r})+1\}$。

直接做是 $O(n^3)$ 的，看起来没什么前途。

由于 $f$ 具有单调性，所以不妨**交换答案与状态**，设 $g_{i,k}$ 为使得 $f_{l,i}\le k$ 的最小的 $l$。

则对任意的 $d\ge g_{i,k}$，都有 $f_{d,i}\le k$，且对于任意的 $i$，$g_i$ 单调不增。

这样，利用单调性直接转移，有

$$g_{i,k}=\begin{cases}g_{g_{i,k-1}-1,k-1}&k\neq a_i\\a_i&k=a_i\end{cases}$$

这样总复杂度 $O(n^2)$。

现在，从小到大枚举 $k$，动态维护 $g_{i,k}$。

修改操作就相当于单调修改，和所有元素往前跳一格。

可以发现，只有 $g_{g_{i,k-1},k-1}\neq g_{i,k-1}$ 时，这样的操作才有意义。

可以动态维护出所有满足 $g_{g_{i,k-1},k-1}\neq g_{i,k-1}$ 的 $g_{i,k-1}$，由于 $g$ 具有单调性，所以相当于若干次区间赋值操作。

也就是维护一个数据结构，支持区间赋值，并查询某个值出现的区间，线段树上二分即可。

这样总修改次数均摊 $O(n\log n)$，总复杂度 $O(n\log^2 n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1.2e6+5,inf=1e9;
namespace tr{
    struct node{
    	int l,r,mx,sm,laz;
    }p[N<<2];
    void upset(int x){
    	p[x].mx=max(p[x<<1].mx,p[x<<1|1].mx);
    	p[x].sm=p[x<<1].sm+p[x<<1|1].sm;
    }
    void reset(int x,int l,int r){
    	p[x].l=l,p[x].r=r;p[x].laz=inf;
    	if(l==r){
    		p[x].mx=p[x].sm=l;
    		return;
    	}
    	int mid=l+r>>1;
    	reset(x<<1,l,mid);
    	reset(x<<1|1,mid+1,r);
    	upset(x);
    }
    void sets(int x,int sm){
    	p[x].mx=sm;
    	p[x].sm=sm*(p[x].r-p[x].l+1);
    	p[x].laz=sm;
    }
    void dnset(int x){
    	if(p[x].laz!=inf){
    		sets(x<<1,p[x].laz);
    		sets(x<<1|1,p[x].laz);
    		p[x].laz=inf;
    	}
    }
    int lb(int x,int k){
    	if(p[x].l==p[x].r)return p[x].l;
    	dnset(x);
    	if(p[x<<1].mx>=k)return lb(x<<1,k);
    	return lb(x<<1|1,k);
    }
    int ub(int x,int k){
    	if(p[x].l==p[x].r)return p[x].l;
    	dnset(x);
    	if(p[x<<1].mx>k)return ub(x<<1,k);
    	return ub(x<<1|1,k);
    }
    void sets(int x,int l,int r,int sm){
    	if(l<=p[x].l&&r>=p[x].r){
    		sets(x,sm);
			return; 
    	} 
    	int mid=p[x].l+p[x].r>>1;
    	dnset(x);
    	if(l<=mid)sets(x<<1,l,r,sm);
    	if(r>mid)sets(x<<1|1,l,r,sm);
    	upset(x);
    }
    int gets(int x,int d){
    	if(p[x].laz!=inf)return p[x].laz;
    	if(p[x].l==p[x].r)return p[x].sm;
    	if(d<=(p[x].l+p[x].r>>1))return gets(x<<1,d);
    	return gets(x<<1|1,d);
    }
}
int n,p[N],res,m;
vector<int>jl[N],tmp,q;
struct node{
	int l,r,sm;
};
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
//	n=262144;
    cin>>n;
	for(int i=1;i<=n;i++)cin>>p[i],m=max(m,p[i]),jl[p[i]].push_back(i);
	tr::reset(1,0,n+1);
	m+=30;
	for(int i=1;i<=n;i++)res+=i;
	for(int j=1;j<=m;j++){
		vector<node>qs;
		tmp.clear();
		sort(q.begin(),q.end());
		q.resize(unique(q.begin(),q.end())-q.begin());
	//	cout<<j<<" "<<q.size()<<endl;
		for(auto i:q){
			int l=tr::lb(1,i),r=tr::ub(1,i)-1;
			int k=tr::gets(1,i);
			qs.push_back({l,r,k});
			tmp.push_back(k);
		}
		for(auto c:qs)tr::sets(1,c.l,c.r,c.sm);
		q.clear();
		for(auto c:tmp)if(c!=tr::gets(1,c))q.push_back(c);
		for(auto c:jl[j]){
			if(c-1<tr::gets(1,c)){
			    tr::sets(1,c,c,c-1);
				q.push_back(c);
				if(tr::gets(1,c-1)!=c-1)q.push_back(c-1);
			}
		}
		res+=tr::p[1].sm;
	}
	cout<<res-(n+1)*m;
}
```

---

## 作者：yllcm (赞：1)

考虑求出单个问题的答案。从序列不降的情况入手，假设序列为 ${c_1}\cdot a_1+c_2\cdot a_2+\cdots c_k\cdot a_k$（其中加号为序列的拼接，乘号类似定义），则有如下策略：不断把 $a_1$ 合并成 $\lceil\frac{c_1}{2}\rceil$ 个 $a_1+1$，如此重复直到序列中只剩下一个数。拓展到一般情况，则策略为：设 $m=\min a_i$，把所有 $a_i=m$ 的连续段提出来。设连续段长度为 $c_1,c_2,\cdots c_k$，那么把长度变为 $\lceil\frac{c_1}{2}\rceil,\lceil\frac{c_2}{2}\rceil,\cdots,\lceil\frac{c_k}{2}\rceil$，数值变为 $m+1$，再放回原位置。如此重复直到序列中只剩下一个数。

尝试将这个做法拓展到原问题。我们直接对整个序列执行上面的算法，并尝试在这个序列上找到每个子区间的信息。尝试对于新序列上的每个元素上维护两个集合 $Sl_i,Sr_i$，使得对于区间 $[l,r]$，$l\in Sl_x,r\in Sr_y$，当前时刻 $[l,r]$ 对应的区间恰好是 $[x,y]$。可以得到一个近似的构造：初始 $Sl_i=Sr_i=\{i\}$，收缩连续段的时候，$Sl_i$ 从右往左相邻两个合并，$Sr_i$ 从左往右相邻两个合并（举例来说，收缩长度为 $5$ 的连续段时，$Sl$ 合并方式为 $\{Sl_1,Sl_2\},\{Sl_3,Sl_4\},\{Sl_5\}$，$Sr$ 合并方式为 $\{Sl_1\},\{Sl_2,Sl_3\},\{Sl_4,Sl_5\}$）。这种构造在 $[l,r]$ 的连续段个数为 $1$ 的时候是错误的，但对于其余情况正确。

值为 $m$ 的连续段收缩之后会与值为 $m+1$ 的连续段合并产生新的连续段。我们在合并连续段的时候，统计跨过两个连续段分界线的区间的答案。假设 $[l,r]$ 对应区间 $[x,y]$，则区间 $[l,r]$ 的答案为 $m+\lceil\log_2(y-x+1)\rceil$。枚举 $\lceil\log_2(y-x+1)\rceil$ 即可在 $\mathcal{O}((A+B)\log n)$ 的时间内计算答案（其中 $A,B$ 为两个连续段长度）。

总结一下，上述算法分成两个部分：收缩连续段，合并连续段，我们分别说明两个部分的复杂度：

* 对于收缩连续段，一次收缩会在 $\mathcal{O}(|S|)$ 的时间内删除 $\frac{|S|}{2}$ 个元素，由于每个元素只会被删除一次，所以复杂度为 $\mathcal{O}(n)$（注意当 $|S|=1$ 的时候，我们忽略收缩操作）。
* 对于合并连续段，注意到合并之后的集合都会进行至少一次收缩操作，所以需要合并的集合大小之和同样是 $\mathcal{O}(n)$。使用上述复杂度为 $\mathcal{O}((A+B)\log n)$ 的方法，分治合并多个集合，可以得到总复杂度为 $\mathcal{O}(n\log^2 n)$。

综上，问题可以在 $\mathcal{O}(n\log^2 n)$ 时间内被解决。

[提交记录 #2003538 - LibreOJ (loj.ac)](https://loj.ac/s/2003538)

---

