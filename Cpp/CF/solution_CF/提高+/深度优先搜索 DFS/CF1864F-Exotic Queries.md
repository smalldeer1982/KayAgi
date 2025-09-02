# Exotic Queries

## 题目描述

AquaMoon gives RiverHamster a sequence of integers $ a_1,a_2,\dots,a_n $ , and RiverHamster gives you $ q $ queries. Each query is expressed by two integers $ l $ and $ r $ .

For each query independently, you can take any continuous segment of the sequence and subtract an identical non-negative value from all the numbers of this segment. You can do so multiple (possibly, zero) times. However, you may not choose two intersecting segments which are not included in one another. Your goal is to convert to $ 0 $ all numbers whose initial value was within the range $ [l, r] $ . You must do so in the minimum number of operations.

Please note that the queries are independent, the numbers in the array are restored to their initial values between the queries.

Formally, for each query, you are to find the smallest $ m $ such that there exists a sequence $ \{(x_j,y_j,z_j)\}_{j=1}^{m} $ satisfying the following conditions:

- for any $ 1 \le j \leq m $ , $ z_j \ge 0 $ and $ 1 \le x_j \le y_j \leq n $ (here $ [x_j, y_j] $ correspond to the segment of the sequence);
- for any $ 1 \le j < k \le m $ , it is true that $ [x_j,y_j]\subseteq[x_{k},y_{k}] $ , or $ [x_k,y_k]\subseteq[x_{j},y_{j}] $ , or $ [x_j,y_j]\cap[x_{k},y_{k}]=\varnothing $ ;
- for any $ 1 \le i \le n $ , such that $ l \le a_i \leq r $ , it is true that $$${\large a_i = \sum\limits_{\substack {1 \le j \le m \\ x_j \le i \le y_j}} z_j. } $$$

## 说明/提示

In the first test case, consider the second query, when $ l = 2 $ , $ r = 2 $ . The elements to be manipulated are $ [a_3, a_5, a_{10}] = [2, 2, 2] $ . It is sufficient to apply the operation sequence $ \{(2, 10, 2)\} $ .

Consider the fourth query, when $ l = 2 $ , $ r = 3 $ . The elements to be manipulated are $ [a_3, a_4, a_5, a_7, a_{10}] = [2, 3, 2, 3, 2] $ . It is sufficient to apply the operation sequence $ \{(1, 10, 2), (4, 4, 1), (7, 7, 1)\} $ .

In the second test case, note that the operation sequence $ \{(1, 2, 1), (2, 3, 2)\} $ is invalid because the two segments intersect but neither is contained inside the other.

## 样例 #1

### 输入

```
10 8
1 6 2 3 2 6 3 10 1 2
1 10
2 2
3 3
2 3
1 3
3 6
4 6
5 5```

### 输出

```
8
1
1
3
5
3
1
0```

## 样例 #2

### 输入

```
3 1
1 3 2
1 3```

### 输出

```
3```

# 题解

## 作者：苏联小渣 (赞：14)

这个题难点在于读题，尤其注意不要读所谓的简要题意。

读完题后就很好做了。

我们只把值域在区间 $[l,r]$ 的数抽出来，由于要求删数区间不交，那么删数的顺序肯定是从小到大删。对于最小的那个数，它只用一次操作就能删完。将它删完之后，由于我们要求值域区间 $[l,r]$ 的所有数都要变成 $0$，那么最小值位置就不能再动了。假设最小值出现的位置为 $p_1,p_2,...,p_k$，那么此时序列就被分裂成了若干子区间 $[1,p_1-1],[p_1+1,p_2-1],...,[p_k+1,n]$，我们要对这些子区间分别递归处理，也就是不断地删去最小值、分裂区间。

举个例子，$a=[1,3,2,5,2,6]$ 且 $l=2,r=6$，过程如下：

- 取出所有在 $[l,r]$ 中的数，为 $[3,2,5,2,6]$

- $[3,\color{red}2\color{black},5,\color{red}2\color{black},6]$，删去 $2$，划分成三个子区间 $[3],[5],[6]$.

- 在这三个子区间中，由于只有一个数，所以直接删去，总次数为 $4$。

这么写肯定是会超时的，考虑如何用一个更好的方式描述这个过程。如果 $[l,r]$ 中的所有数都恰好出现一次，比如说 $[1,2,4,5]$，且 $l=2,r=4$，那么最优次数显然为 $[l,r]$ 中出现过的数的个数。当一般情况下，值域在 $[l,r]$ 中的每个出现过的数，一定会贡献至少一次次数，那我们考虑什么情况下，它会贡献额外次数。

假设一个数 $x$，它出现的位置为 $p_1,p_2,...,p_k$，假设对于一个 $j \in [1,k)$，且 $[p_j+1,p_{j+1}-1]$ 中存在一个数 $y$ 比 $x$ 先删去，那么就会贡献一个额外次数（因为这样的话左右区间就被分开了）。这个 $y$ 需要满足，$l \le y \le x$。也就是说，我们需要找到区间 $[p_j+1,p_{j+1}-1]$ 中，$x$ 的前驱，判断这个前驱是否 $\ge l$，如果 $\ge l$ 次数就加一。

这样子这个题就看起来很可做了。所有 $[p_j+1,p_{j+1}-1]$ 中 $x$ 的前驱是可以处理出来的，看似是区间前驱，但是不用树套树，观察到我们可以按值从小到大加入，就变成了查询区间最大值，用线段树即可。当我们处理好一个值 $x$ 的所有“前驱集合”（不妨记为 $S_x$）后，问题就变成了，查询集合 $S_l,S_{l+1},...,S_r$ 的并集中，有多少个数 $\ge l$。不妨记该询问为 $T([l,r],l)$。

观察到并不强制在线，所以并不需要用主席树。我们考虑拆询问，就变成了查询 $T([1,r],l)-T([1,l-1],l)$。这个是经典问题了，离线下来扫描线，用树状数组查询即可。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
int n, q, l, r, mx, a[1000010], ans[1000010], s[1000010];
struct Query{
	int x, id, op;
};
vector <Query> ask[1000010];
vector <int> pos[1000010];
struct Segment{
	#define lc(x) x<<1
	#define rc(x) x<<1|1
	int d[4000010];
	void pushup(int k){
		d[k] = max(d[lc(k)], d[rc(k)]);
	}
	void modify(int k, int l, int r, int x, int y){
		if (l == r){
			d[k] = y;
			return ;
		}
		int mid = l + r >> 1;
		if (x <= mid) modify(lc(k), l, mid, x, y);
		else modify(rc(k), mid+1, r, x, y);
		pushup(k);
	}
	int query(int k, int l, int r, int x, int y){
		if (x <= l && r <= y) return d[k];
		int mid = l + r >> 1, ret = 0;
		if (x <= mid) ret = max(ret, query(lc(k), l, mid, x, y));
		if (y > mid) ret = max(ret, query(rc(k), mid+1, r, x, y));
		return ret;
	}
}S;
struct BIT{
	int d[1000010];
	void add(int p, int x){
		for (; p<=n; p+=p&-p) d[p] += x;
	}
	int query(int p){
		int ret = 0;
		for (; p; p-=p&-p) ret += d[p];
		return ret;
	}
}T;
int main(){
	scanf ("%d%d", &n, &q);
	for (int i=1; i<=n; i++){
		scanf ("%d", &a[i]);
		pos[a[i]].push_back(i);
	}
	for (int i=1; i<=n; i++){
		if (pos[i].size()) s[i] = s[i-1] + 1;
		else s[i] = s[i-1];
	}
	for (int i=1; i<=q; i++){
		scanf ("%d%d", &l, &r);
		ans[i] += s[r] - s[l-1];
		ask[l-1].push_back((Query){l, i, -1});
		ask[r].push_back((Query){l, i, 1});
	}
	for (int i=1; i<=n; i++){
		for (int j=0; j<pos[i].size(); j++){
			if (j > 0){
				int mx = S.query(1, 1, n, pos[i][j-1], pos[i][j]);
				if (mx) T.add(mx, 1);
			}
		}
		for (int j=0; j<pos[i].size(); j++){
			S.modify(1, 1, n, pos[i][j], i);
		}
		for (int j=0; j<ask[i].size(); j++){
			int x = ask[i][j].x, id = ask[i][j].id, op = ask[i][j].op;
			ans[id] += op * (T.query(n) - T.query(x-1));
		}
	}
	for (int i=1; i<=q; i++){
		printf ("%d\n", ans[i]);
	}
	return 0;
}
```

---

## 作者：EuphoricStar (赞：5)

感觉 $\text{F < E}$。

考虑 $l = 1, r = n$ 怎么做。

考虑分治。设 $\text{solve}(l, r)$ 为只考虑**下标**在 $[l, r]$ 中的数的最小操作次数。

设 $x = \min\limits_{i = l}^r a_i$。容易发现给这个区间减去 $x$ 最优，于是 $\forall i \in [l, r], a_i \gets a_i - x$。设最小值出现的位置为 $p_1, p_2, \ldots, p_k$，那么对 $\text{solve}(l, p_1 - 1), \text{solve}(p_1 + 1, p_2 - 1), \ldots, \text{solve}(p_{k - 1} + 1, p_k - 1), \text{solve}(p_k + 1, r)$ 求和，再 $+ 1$ 就是 $\text{solve}(l, r)$ 的答案。

考虑 $l = 1$ 怎么做。先离线所有询问，考虑维护答案，从小到大加入数，并计算出 $r - 1 \to r$ 时，答案的变化量。

设当前加入所有 $a_j = i$ 的数，若有这样的数先令答案 $+ 1$，因为至少要操作 $1$ 次；设这样的数的位置为 $j_1, j_2, \ldots, j_k$，我们在 $j_{t - 1}, j_t$ 处计算答案的变化量：

- 若 $[j_{t - 1}, j_t]$ 中没有之前已经加入的数，那么答案不会变化（因为操作 $j_{t - 1}$ 可以顺带把 $j_t$ 操作）；
- 若 $[j_{t - 1}, j_t]$ 中有之前已经加入的数，那么答案 $+ 1$。

考虑一般情况，我们发现和 $l = 1$ 不同之处在于若 $[j_{t - 1}, j_t]$ 中有之前已经加入的数，答案也不一定 $+ 1$。具体地，设 $x$ 为 $[j_{t - 1}, j_t]$ 中之前已经加入的数的最大值，那么当 $l > x$ 时答案就不用 $+ 1$。

于是我们用树状数组维护每个 $x$，回答 $[l, r]$ 时就知道有多少个 $x$ 满足 $l > x$。

再使用一棵线段树维护数的加入情况，复杂度就是 $O((n + q) \log n)$。

[code](https://codeforces.com/contest/1864/submission/220594430)

---

## 作者：_Cyan_ (赞：4)

## 题意简述

给你一个长为 $n$ 的序列 $a_i$，有 $q$ 个询问 $[l,r]$ 表示将序列 $a$ 中所有值在 $l$ 到 $r$ 之间的元素 $a_i$ 按下标从小到大的顺序排列得到序列 $b$。求最少需要多少次操作使 $b$ 中所有元素变为 $0$。每次操作可以选择任意一段区间 $[L,R]$ 将之中所有元素减去一个正整数。

## 分析

首先可以发现答案的下限是 $[l,r]$ 中不同元素的个数 $c$，但是在操作过程中序列 $b$ 会被 $0$ 分成几段，这时候就只能对每一段逐一操作，换句话说，就是如果有两个相同的值（这之间没有与它们值相同的元素）之间如果出现比它们值都小的数，那必然会被分开来操作，比如说 $[4,2,4]$，这两个 $4$ 最后就一定会被分成两段而不能合成一段操作。

---
接着我们就对每对值相同且“相邻”进行处理。设这两个元素在 $a$ 中的位置为 $x$，$y$，那么只要 $x$ 和 $y$ 之间**所有小于 $a_x$ 的值中的最大值**（表示成$mx$）被包含在了 $b$ 序列中，那么这两个值必然会被分成两段，答案也就会在原来的基础上加 $1$。我们将这样的**限制**写成 $(mx,a_x)$。那问题就被转化成了有多少这样的数对满足：

$$l\leq mx \leq a_x \leq r$$

而这就是个二维偏序问题了，你将数对按 $mx$ 从大到小排序，询问同理，接着用线段树维护每个元素所受限制的个数，答案就是 $c$ 加上 $[l,r]$中这样的数对的个数，具体细节看代码。

## 代码

```cpp
#include<bits/stdc++.h>
#define fir first
#define sec second
#define int long long
#define pir pair<int,int>
#define mkp(a,b) make_pair(a,b)
using namespace std;
inline int read(){
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-') f=-1; c=getchar();}
	while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48); c=getchar();}
	return x*f;
}
const int mod=998244353,inf=1e18,N=1e6+5;
int n,q,a[N],sum[N],m,res[N];
int mx[N<<2],t[N<<2];
vector<int> pos[N];
struct node{int l,r;}p[N];
struct get_ans{int l,r,id;}qu[N];
inline bool cmp(node a,node b){return a.l>b.l;}
inline bool cmp2(get_ans a,get_ans b){return a.l>b.l;}

//维护区间最大值
inline void upd(int l,int r,int p,int num){
	if(l==r){mx[p]=a[num]; return ;}
	int mid=(l+r)>>1;
	if(num<=mid) upd(l,mid,p<<1,num);
	else upd(mid+1,r,p<<1|1,num);
	mx[p]=max(mx[p<<1],mx[p<<1|1]);
}
inline int query(int l,int r,int p,int ll,int rr){
	if(ll<=l&&r<=rr) return mx[p];
	int res=0,mid=(l+r)>>1;
	if(ll<=mid) res=query(l,mid,p<<1,ll,rr);
	if(rr>mid)  res=max(res,query(mid+1,r,p<<1|1,ll,rr));
	return res;
}
//维护数对个数
inline void add(int l,int r,int p,int num){
	if(l==r){t[p]++; return ;}
	int mid=(l+r)>>1;
	if(num<=mid) add(l,mid,p<<1,num);
	else add(mid+1,r,p<<1|1,num);
	t[p]=t[p<<1]+t[p<<1|1];
}
inline int ask(int l,int r,int p,int ll,int rr){
	if(ll<=l&&r<=rr) return t[p];
	int res=0,mid=(l+r)>>1;
	if(ll<=mid) res=ask(l,mid,p<<1,ll,rr);
	if(rr>mid)  res=res+ask(mid+1,r,p<<1|1,ll,rr);
	return res;
}
signed main(){
	n=read(),q=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) pos[a[i]].push_back(i);
	for(int i=1;i<=n;i++){
		for(int j=0;j+1<(int)pos[i].size();j++){
			int ls=pos[i][j]+1,rs=pos[i][j+1]-1;
			if(ls>rs) continue;
			int MX=query(1,n,1,ls,rs);
			p[++m]={MX,i};//p数组表示数对
		}
		sum[i]=sum[i-1]+(!pos[i].empty());
		for(auto v:pos[i]) upd(1,n,1,v);
	}
	sort(p+1,p+m+1,cmp);
	for(int i=1;i<=q;i++){
		int l=read(),r=read();
		qu[i]={l,r,i},res[i]=sum[r]-sum[l-1];
	}
	sort(qu+1,qu+q+1,cmp2);
	int now=1;
	for(int i=1;i<=q;i++){
		while(now<=m&&p[now].l>=qu[i].l) add(1,n,1,p[now++].r);
		res[qu[i].id]+=ask(1,n,1,qu[i].l,qu[i].r);
	}
	for(int i=1;i<=q;i++) cout<<res[i]<<'\n';
}

```


---

## 作者：SnowTrace (赞：2)

非常简单，但是我代码实现又花了半小时。

显然是先用注意力注意出性质再上数据结构维护。

我们先考虑这样一个问题：

给定一个序列 $a$ ，问需要多少次题中说的操作能使其全为 0。

贪心策略：每次选取区间的最小值把一整个区间都减去这个最小值，然后接下来数列会出现一些为 $0$ 的点，以这些零点为分界把原序列划分为几个子段递归考虑。显然如果一个地方是零了这个位置就不能再被减了，而我们这个策略能做到每次减最多，是非常正确的。

发现这个太难维护了，考虑什么情况下会省下一些操作（就是相比一个一个点删，会少多少次）。

显然如果序列里面没有相同的数就要操作 $n$ 次（每次恰好让一个数变成零）。

而如果有两个数能同时变成零的话，就能省下一次。

考虑什么情况下两个数能同时（在一次操作中）变成零。显然这两数值必须相等，而且删的时候是在同一段，也就是这两数之间没有数比它们小。

我们对于每个点考虑离他最近且在他右边值和他相等的数（），如果这两数之间没有比这两个数还小的数，那就能省下一次操作。

现在回到原问题上考虑。

发现本质上就是一个二维偏序关系。

假设现在考虑到位置 $i$，设也就是它右边第一个值等于 $a_i$ 的位置是 $j$，设 $mx$ 为区间 $(i,j)$ 中小于 $a_i$ 且最大的数，那么当 $mx+1\leq l \leq i$ 且 $r\geq i$ 时答案减一。

这里的最小和最大有点绕，最大的理解是在 $(i,j)$ 间只要找到一个比他小的数就可以了，而比他小的数中的最大值显然最难被消掉。

离线询问，树状数组维护即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define lowbit(x) x&(-x)
struct tree{
	int l,r,mx;
}Tree[4000005];
int a[1000005];int n,q;
;void build(int l,int r,int k){
	Tree[k].l = l,Tree[k].r = r;
	if(l+1 == r){
		return ;
	}build(l,l+r>>1,k<<1),build(l+r>>1,r,k<<1|1);
}void update(int pos,int add,int k){
	int l = Tree[k].l,r = Tree[k].r;
	if(pos>=r or pos<l)return;
	if(l+1 == r){
		Tree[k].mx = add;return;
	}update(pos,add,k<<1),update(pos,add,k<<1|1);
	Tree[k].mx = max(Tree[k<<1].mx,Tree[k<<1|1].mx);
}
int query(int l,int r,int k){
	int ll = Tree[k].l,rr = Tree[k].r;
	if(l>=rr or ll>=r)return 0;
	if(l<=ll and rr<=r){
		return Tree[k].mx;
	}return max(query(l,r,k<<1),query(l,r,k<<1|1));
}int tree[2000005];
void upd(int pos,int add){
	for(int i = pos;i<=n+1;i+=lowbit(i))tree[i]+=add;
}int qquery(int pos){
	int res = 0;for(int i = pos;i>0;i-=lowbit(i))res+=tree[i];return res;
}int query(int l,int r){
	return qquery(r)-qquery(l-1);
}vector<int>pos[1000005];
int pre[1000005];
vector<pair<pair<int,int>,int> >add;
struct Q{
	int l,r,id;
}l[1000005];
int ans[1000005];
bool cmp1(Q a,Q b){
	return a.l<b.l;
}bool cmp2(pair<pair<int,int>,int>a,pair<pair<int,int>,int>b){
	return a.first.first<b.first.first;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>q;
	for(int i = 1;i<=n;i++)cin>>a[i];
	for(int i =1;i<=n;i++){
		pre[a[i]]++;pos[a[i]].push_back(i);
	}build(1,n+1,1);
	for(int i = 1;i<=n;i++)pre[i] = pre[i-1]+pre[i];
	for(int i = 1;i<=n;i++){
		for(int j =0;j+1<pos[i].size();j++){
			int qq = query(pos[i][j]+1,pos[i][j+1],1);
			add.push_back({{qq+1,i},1});
			add.push_back({{i+1,i},-1});
		}for(int j =0;j<pos[i].size();j++)update(pos[i][j],i,1);
	}
	for(int i = 1;i<=q;i++){
		cin >> l[i].l>>l[i].r;l[i].id = i;
		ans[i] = pre[l[i].r]-pre[l[i].l-1];
	}sort(l+1,l+1+q,cmp1);sort(add.begin(),add.end());
	int ll = 0;
	for(int i = 1;i<=q;i++){
		int L = l[i].l,R = l[i].r,id = l[i].id;
		while(ll!=add.size() and add[ll].first.first<=L){
			upd(add[ll].first.second,add[ll].second);ll++;
		}ans[id]-=query(1,R);
	}for(int i = 1;i<=q;i++)cout<<ans[i]<< '\n';
	return 0;
}
```


---

## 作者：hanjinghao (赞：2)

## 前提概要：本人在考场上降智，赛后才过这题。

# 思路

把大小在 $ l $ 到 $ r $ 之间的数拿出来，排成一个序列 $ b $。分析性质可得，答案为序列长度减去满足以下条件的数对 $ (i, j) $ 的个数：

1、$ i \lt j $

2、$ b_i = b_j $

3、不存在 $ k $ 满足 $ i \lt k \lt j $ 且 $ b_k \le b_i $。

**接下来我们回到原数组 $ a $ 来分析问题。**

令 $ a_i $ 和 $ a_j $ 为相邻两个相同的数，$ x $ 表示位于 $ i $ 和 $ j $ 之间且小于 $ a_i $ 的数的最大值（如果没有，则为零），则 $ (i, j) $ 这个数对产生负一的贡献，当且仅当询问 $ (l, r) $ 满足 $ x \lt l \le a_i $ 且 $ r \ge a_i $。

按从小到大的顺序把每一个数加入线段树，查询区间最大值即可求出 $ x $。

回答询问，只需要在值域上面扫描线即可。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

char buf[1000005];
int ppos, llen;

inline char gch()
{
	if (ppos == llen)
	{
		ppos = 0;
		llen = fread(buf, 1, 1000000, stdin);
	}
	if (ppos == llen) return -1;
	return buf[ppos++];
}

char obuf[1000005];
int opos;

inline void pch(char c)
{
	if (opos == 1000000)
	{
		fwrite(obuf, 1, 1000000, stdout);
		opos = 0;
	}
	obuf[opos++] = c;
}

template < typename T >
inline void read(T &x)
{
	x = 0;
	bool flg = 0;
	char c;
	while ((c = gch()) < 48 || c > 57)
		flg |= c == '-';
	do
		x = (x << 1) + (x << 3) + (c ^ 48);
	while ((c = gch()) > 47 && c < 58);
	if (flg) x = -x;
}

int OUTPUT[45];

template < typename T >
inline void writeln(T x)
{
	if (x < 0)
	{
		pch('-');
		x = -x;
	}
	int len = 0;
	do
	{
		OUTPUT[++len] = x % 10 | 48;
		x /= 10;
	}while (x);
	while (len)
		pch(OUTPUT[len--]);
	pch('\n');
}

const int N = 1e6 + 5;
int n, q, a[N], s[N], t[N], tr[N << 2], ans[N];
vector < int > G[N];
vector < pair < int, int > > v[N], qry[N];

inline void Chkmax(int &x, int y)
{
	if (y > x) x = y;
}

inline int lowbit(int x)
{
	return x & (-x);
}

inline void Upd(int x, int val)
{
	while (x <= n)
	{
		t[x] += val;
		x += lowbit(x);
	}
}

inline int Qry(int x)
{
	int ret = 0;
	while (x)
	{
		ret += t[x];
		x -= lowbit(x);
	}
	return ret;
}

void Modify(int x, int val, int l, int r, int p)
{
	if (l == r)
	{
		tr[p] = val;
		return;
	}
	int md = (l + r) >> 1, ls = (p << 1), rs = (ls | 1);
	if (x <= md) Modify(x, val, l, md, ls);
	else Modify(x, val, md + 1, r, rs);
	tr[p] = max(tr[ls], tr[rs]);
}

int Query(int ql, int qr, int l, int r, int p)
{
	if (ql <= l && r <= qr) return tr[p];
	int md = (l + r) >> 1, ls = (p << 1), rs = (ls | 1), ret = 0;
	if (ql <= md) Chkmax(ret, Query(ql, qr, l, md, ls));
	if (qr > md) Chkmax(ret, Query(ql, qr, md + 1, r, rs));
	return ret;
}

int main()
{
	read(n);
	read(q);
	for (int i = 1; i <= n; ++i)
	{
		read(a[i]);
		G[a[i]].emplace_back(i);
	}
	for (int i = 1; i <= q; ++i)
	{
		int l, r;
		read(l);
		read(r);
		qry[r].emplace_back(l, i);
	}
	for (int i = 1; i <= n; ++i)
	{
		int len = G[i].size();
		s[i] = s[i - 1] + len;
		for (int j = 1; j < len; ++j)
			if (G[i][j] == G[i][j - 1] + 1)
			{
				v[i].emplace_back(1, 1);
				if (i != n) v[i].emplace_back(i + 1, -1);
			}
			else
			{
				v[i].emplace_back(Query(G[i][j - 1] + 1, G[i][j] - 1, 1, n, 1) + 1, 1);
				if (i != n) v[i].emplace_back(i + 1, -1);
			}
		for (auto &j : G[i])
			Modify(j, i, 1, n, 1);
	}
	for (int i = 1; i <= n; ++i)
	{
		for (auto &j : v[i])
			Upd(j.first, j.second);
		for (auto &j : qry[i])
			ans[j.second] = s[i] - s[j.first - 1] - Qry(j.first);
	}
	for (int i = 1; i <= q; ++i)
		writeln(ans[i]);
	if (opos) fwrite(obuf, 1, opos, stdout);
	return 0;
}
```

---

## 作者：lfxxx (赞：2)

写了一小时结果被卡常了（笑。

考虑新加入一个数什么时候会产生贡献，或者什么时候不会产生贡献。

发现当一个数的位置与他前一次出现时的位置所构成的区间内假若有一个比它小的数那么就不得不对这个数新进行一次操作而不能共用。

又因为询问一个值域范围内的贡献，所以考虑把这个范围内最大的小于这个数本身的数找出来就行了。

我们令这个数作为这个点的点权。

询问便是询问一个值域范围内的点有多少个点权也满足在这个值域范围内，考虑按照大小重新给所有点定序，值域限制转变为下标限制，这个问题就变成了一个二维数点。差分之后树状数组扫一遍就行了。

考虑怎么预处理一个点的点权，我们可以将所有点从小到大加入线段树并维护区间最大值即可。

复杂度 $O(n \log n)$。

下面放出赛后卡过的代码：

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#define lowbit(x) (x&-(x))
using namespace std;
namespace IO{
    const int SIZE=1<<21;
    static char ibuf[SIZE],obuf[SIZE],*iS,*iT,*oS=obuf,*oT=oS+SIZE-1;
    int qr;
    char qu[55],c;
    bool f;
    #define getchar() (IO::iS==IO::iT?(IO::iT=(IO::iS=IO::ibuf)+fread(IO::ibuf,1,IO::SIZE,stdin),(IO::iS==IO::iT?EOF:*IO::iS++)):*IO::iS++)
    #define putchar(x) *IO::oS++=x,IO::oS==IO::oT?flush():0
    #define flush() fwrite(IO::obuf,1,IO::oS-IO::obuf,stdout),IO::oS=IO::obuf
    #define puts(x) IO::Puts(x)
    template<typename T>
    inline void read(T&x){
        for(f=1,c=getchar();c<48||c>57;c=getchar())f^=c=='-';
        for(x=0;c<=57&&c>=48;c=getchar()) x=(x<<1)+(x<<3)+(c&15); 
        x=f?x:-x;
    }
    template<typename T>
    inline void write(T x){
        if(!x) putchar(48); if(x<0) putchar('-'),x=-x;
        while(x) qu[++qr]=x%10^48,x/=10;
        while(qr) putchar(qu[qr--]);
    }
    inline void Puts(const char*s){
        for(int i=0;s[i];i++)
            putchar(s[i]);
        putchar('\n');
    }
    struct Flusher_{~Flusher_(){flush();}}io_flusher_;
}
using IO::read;
using IO::write;
const int maxn = 1e6+14;
const int inf = 1e9+7;
int tr[maxn*3+1],tag[maxn*3+1]; 
inline void pushdown(int cur){
	if(tr[cur]==inf) return ;
    tr[cur<<1]=min(tr[cur<<1],tag[cur]);
    tr[cur<<1|1]=min(tr[cur<<1|1],tag[cur]);
    tag[cur<<1]=min(tag[cur<<1],tag[cur]);
    tag[cur<<1|1]=min(tag[cur<<1|1],tag[cur]);
    tag[cur]=inf;
}
inline void pushup(int cur){
    tr[cur]=min(tr[cur<<1],tr[cur<<1|1]);
}
inline void update(int cur,int lt,int rt,int l,int r,int v){
    if(lt>rt) return ;
    if(l>rt||r<lt) return;
    if(l<=lt&&rt<=r){
        tr[cur]=min(tr[cur],v);
        tag[cur]=min(tag[cur],v);
        return ;
    }
    int mid=(lt+rt)>>1;
    pushdown(cur);
    update(cur<<1,lt,mid,l,r,v);
    update(cur<<1|1,mid+1,rt,l,r,v);
    pushup(cur);
}
inline int query(int cur,int lt,int rt,int l,int r){
    if(l>rt||r<lt) return inf;
    if(l<=lt&&rt<=r) return tr[cur];
    int mid=(lt+rt)>>1;
    pushdown(cur);
    return min(query(cur<<1,lt,mid,l,r),query(cur<<1|1,mid+1,rt,l,r));
}
int Tr[maxn*3+1],Tag[maxn*3+1]; 
inline void Pushdown(int cur){
	if(Tag[cur]==0) return ;
    Tr[cur<<1]=max(Tr[cur<<1],Tag[cur]);
    Tr[cur<<1|1]=max(Tr[cur<<1|1],Tag[cur]);
    Tag[cur<<1]=max(Tag[cur<<1],Tag[cur]);
    Tag[cur<<1|1]=max(Tag[cur<<1|1],Tag[cur]);
    Tag[cur]=0;
}
inline void Pushup(int cur){
    Tr[cur]=max(Tr[cur<<1],Tr[cur<<1|1]);
}
inline void Update(int cur,int lt,int rt,int l,int r,int v){
    if(lt>rt) return ;
    if(l>rt||r<lt) return;
    if(l<=lt&&rt<=r){
        Tr[cur]=max(Tr[cur],v);
        Tag[cur]=max(Tag[cur],v);
        return ;
    }
    int mid=(lt+rt)>>1;
    Pushdown(cur);
    Update(cur<<1,lt,mid,l,r,v);
    Update(cur<<1|1,mid+1,rt,l,r,v);
    Pushup(cur);
}
inline int Query(int cur,int lt,int rt,int l,int r){
    if(l>rt||r<lt) return 0;
    if(l<=lt&&rt<=r) return Tr[cur];
    int mid=(lt+rt)>>1;
    Pushdown(cur);
    return max(Query(cur<<1,lt,mid,l,r),Query(cur<<1|1,mid+1,rt,l,r));
}
int w[maxn],a[maxn],n,q;
int lst[maxn];
int b[maxn];
int L[maxn],R[maxn];
vector<int> col[maxn];
int cnt;
int answer[maxn];
struct Node{
    Node(int L,int R,int ID,int OP){
        l=L,r=R,id=ID,op=OP;
    }
    int l,r,id,op;
};
int tree[maxn];
inline void add(int x){
    while(x<=n) tree[x]++,x+=lowbit(x);
}
inline int pre(int x){
    int res=0;
    while(x>0) res+=tree[x],x-=lowbit(x);
    return res;
}
vector<Node> Q[maxn];
int f[maxn];
int main(){
    read(n);
    read(q);
    for(int i=1;i<=n;i++){
        read(a[i]); 
    }
    for(int i=1;i<=n;i++){
        col[a[i]].push_back(i);
        if(lst[a[i]]==0){
            w[i]=0;
        }
        else{
            w[i]=-1;
        }
        lst[a[i]]=i;
    }
    for(int i=1;i<=n;i++){
        int lst=0;
        for(int x:col[i]){
            if(lst==0) w[x]=0;
            else{
                w[x]=Query(1,1,n,lst,x);
                if(w[x]==0) w[x]=-1;
            }
            lst=x;

        }
        for(int x:col[i]) Update(1,1,n,x,x,a[x]);
    }
    for(int i=1;i<=n;i++){
        if(col[i].size()==0){
            L[i]=n+1;
            R[i]=0;
            continue;
        }
        L[i]=cnt+1;
        for(int x:col[i]) b[++cnt]=w[x],f[cnt]=x;
        R[i]=cnt;
    }
    for(int i=0;i<(maxn*3);i++) tr[i]=tag[i]=inf;
    for(int i=0;i<(maxn*3);i++) Tr[i]=Tag[i]=0; 
    for(int i=1;i<=n;i++){
        update(1,1,n,i,i,L[i]);
        Update(1,1,n,i,i,R[i]);
    }
    for(int i=1;i<=q;i++){
        int cl,cr;
        read(cl);
        read(cr);
        int L=query(1,1,n,cl,cr),R=Query(1,1,n,cl,cr);
        if(L>R) continue;
        Q[L-1].push_back(Node(cl,cr,i,-1));
        Q[R].push_back(Node(cl,cr,i,1));
    }
    int sum=0;
    for(int i=1;i<=n;i++){
        if(w[f[i]]==0) sum++;
        else if(w[f[i]]==-1) sum=sum;
        else add(w[f[i]]);
        for(Node now:Q[i]){
            answer[now.id]+=now.op*(sum+(pre(now.r)-pre(now.l-1)));
        }
    }
    for(int i=1;i<=q;i++) write(answer[i]),putchar('\n');
    return 0;
}
/*
10 1
1 6 2 3 2 6 3 10 1 2
3 6
*/
```


---

## 作者：Fire_Raku (赞：0)

[CF1864F Exotic Queries](https://www.luogu.com.cn/problem/CF1864F)

离线+线段树+树状数组

先把权值在 $[l,r]$ 之内的单独拎出来看性质。可以知道策略一定是元素从小到大消成 $0$。当消除元素 $x$ 时，最好的情况当然是一次全消了，但一般元素 $x$ 的位置两两之间会有之前消成的 $0$，将所有位置分成了 $n$ 段，那么消除 $x$ 就需要 $n$ 次了。

实际上这些 $0$ 原先的数一定小于 $x$。考虑元素 $x$ 的两个相邻出现位置 $p$，$q$，**最有可能让 $x$ 分段的就是 $[p,q]$ 之间小于 $x$ 的数中最大的值**，设它为 $y$（因为假如更小的值都将 $x$ 分开，那么 $y$ 一定也可以），那么它在询问 $[l,r]$ 中能让 $x$ 分段的条件即为 $y\ge l$。

明显可以预处理出这一部分，从小到大枚举并插入元素 $x$。线段树查询元素 $x$ 出现位置两两之间的区间最大值，将这些值加入集合 $S_x$ 中，最后将所有元素 $x$ 插入序列对应位置。

那么询问 $[l,r]$ 的答案即为 $[l,r]$ 区间权值种类数加上 $S_l...S_r$ 中 $\ge l$ 的数之和。

考虑将询问也离线，按照右端点（最大权值）排序。处理到端点 $r$ 时已经考虑了 $S_{1}...S_{r}$，然后发现实际上 $S_1...S_{l-1}$ 并不会影响答案（因为里面的值一定小于 $l$），所以无需撤销，可以直接将 $S_l...S_r$ 转化为 $S_1...S_r$，这样就是一段前缀，用**权值树状数组**维护即可。

复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define pii std::pair<int, int>
#define mk std::make_pair
#define fi first
#define se second
#define pb push_back

using i64 = long long;
using ull = unsigned long long;
const i64 iinf = 0x3f3f3f3f, linf = 0x3f3f3f3f3f3f3f3f;
const int N = 1e6 + 10;
int n, Q;
int t[N << 2], ans[N], a[N], cnt[N];
std::vector<int> v[N], s[N];
void pushup(int u) {t[u] = std::max(t[u << 1], t[u << 1 | 1]);}
void upd(int u, int l, int r, int x, int y) {
	if(l == r) {
		t[u] = y;
		return;
	}
	int mid = (l + r) >> 1;
	if(x <= mid) upd(u << 1, l, mid, x, y);
	else upd(u << 1 | 1, mid + 1, r, x, y);
	pushup(u);
}
int qry(int u, int l, int r, int L, int R) {
	if(L <= l && r <= R) return t[u];
	int mid = (l + r) >> 1, ret = 0;
	if(L <= mid) ret = std::max(ret, qry(u << 1, l, mid, L, R));
	if(R > mid) ret = std::max(ret, qry(u << 1 | 1, mid + 1, r, L, R));
	return ret;
}
struct node {
	int l, r, id;
} q[N];
std::vector<int> g[N];
int c[N];
int lowbit(int x) {return x & (-x);}
void add(int x) {
	for(int i = x; i <= n; i += lowbit(i)) c[i]++;
}
int ask(int x) {
	int ret = 0;
	for(int i = x; i; i -= lowbit(i)) ret += c[i];
	return ret;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
	std::cin >> n >> Q;

	for(int i = 1; i <= n; i++) {
		std::cin >> a[i];
		v[a[i]].pb(i); //按权值存起来
		cnt[a[i]] = 1;
	}
	for(int i = 1; i <= n; i++) { //排个序，方便查询
		std::sort(v[i].begin(), v[i].end());
		cnt[i] += cnt[i - 1];
	}
	for(int i = 1; i <= n; i++) { //从小到大枚举权值
		if(!v[i].size()) continue;
		for(int j = 0; j < v[i].size() - 1; j++) { //查询两两之间的最大值
			int x = qry(1, 1, n, v[i][j], v[i][j + 1]);
			if(x) s[i].pb(x);
		}
		for(int j = 0; j < v[i].size(); j++) { //插入
			upd(1, 1, n, v[i][j], i);
		}
		
	}
	for(int i = 1; i <= Q; i++) {
		std::cin >> q[i].l >> q[i].r;
		q[i].id = i; //编号
		g[q[i].r].pb(i); //按右端权值存起来
	}

	for(int i = 1; i <= n; i++) {
		for(auto x : s[i]) add(x); //加入
		for(auto x : g[i]) {
			int l = q[x].l, r = q[x].r;
			ans[x] = (cnt[r] - cnt[l - 1]) + (ask(n) - ask(l - 1)); //查询大于 l 的部分数量
		}
	}

	for(int i = 1; i <= Q; i++) {
		std::cout << ans[i] << "\n";
	}
	return 0;
}
```

---

## 作者：Targanzqq (赞：0)

一道经典的线段树题。这里感谢 [_Cyan_](https://www.luogu.com.cn/user/480292) 大佬的题解，让我对偏序问题有了进一步的认识。

首先我们将问题转化为在某个值的基础上减少操作次数。因为它的上界为 $\{i\mid l\le a_i \le r\}$ 的 $i$ 个数，因此我们考虑如何在它的基础上减小次数。

我们对于当前最小的数，可以让他所在的合法的最大区间中每个数减去这个数，且不变成负数。可以证明每次选择这个数是最优的。但是又好像不可做了。

我们再考虑尽可能从某个值少加贡献。答案显然有下界，即 $\{a_i\mid l\le a_i \le r\}$ 的 $a_i$ 的个数。但是比如说对于 $\{1,1,4,5,1,4\}$ 这个区间，两个 $4$ 中间有一个 $1$，因此这两个 $4$ 只能分属于两段进行操作。因此你从答案的下界加上所有相同的两个数被分成两段的组数，就是你最终的答案。

现在它已经转化为了一道维护过程的题。我们考虑，两个相同的数被分成两段，当且仅当序列中有数，小于这个数，且包含在所求值域区间中。而对于小于这个数的最大的数，它一定包含在尽可能多的区间中。假设对于一个 $a$ 这个数为 $mx_a$，那我们要统计 $l\ge mx_a\ge a\ge r$ 的 $(mx_a,a)$ 的对数。

首先我们统计 $mx$。我们可以从小到大加数，这样问题就转化为区间中你已经加过的数的最大值。我们用线段树维护区间最大值即可。

现在问题转化为有多少 $a$，它的 $mx$ 等于当前枚举到的的 $mx$。因此对于所有询问，我们可以按照 $l$ 从大到小排序，并对所有点对按照 $mx$ 从大到小排序，然后扫过所有合法的 $mx$，对于每个扫过的 $mx$ 我们可以加入它的贡献，即让 $i$ 的位置加 $1$，表示这个 $i$ 可以找到合法的 $mx$。然后我们就可以查询当前询问的 $l,r$ 的区间和，即为所求的对数。

总结一下，就是我们要维护两棵线段树，一棵维护区间最大值求 $mx$，一棵维护值域区间和求点对数。

源代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define N 1000005
using namespace std;

int n,m,c[N],pre[N],ans[N],top;
vector<int> pos[N];
struct points{
    int mx,x;
    friend bool operator<(points a,points b){
    	return a.mx>b.mx;
	}
}p[N];
struct asks{
	int l,r,id;
	friend bool operator<(asks a,asks b){
    	return a.l>b.l;
	}
}as[N];

struct segtree{
    int a[4*N];
    void modify(int k,int l,int r,int pos,int val){
    	if(l==r){a[k]=val;return;}
    	int mid=(l+r)/2;
    	if(pos<=mid)modify(2*k,l,mid,pos,val);
    	if(pos>mid)modify(2*k+1,mid+1,r,pos,val);
    	a[k]=max(a[2*k],a[2*k+1]);
	}
	int query(int k,int l,int r,int ql,int qr){
		if(ql<=l&&qr>=r)return a[k];
		int mid=(l+r)/2,res=0;
    	if(ql<=mid)res=max(res,query(2*k,l,mid,ql,qr));
    	if(qr>mid)res=max(res,query(2*k+1,mid+1,r,ql,qr));
    	return res;
	}
}mx;
struct segtree2{
    int a[4*N];
    void modify(int k,int l,int r,int pos,int val){
    	if(l==r){a[k]+=val;return;}
    	int mid=(l+r)/2;
    	if(pos<=mid)modify(2*k,l,mid,pos,val);
    	if(pos>mid)modify(2*k+1,mid+1,r,pos,val);
    	a[k]=a[2*k]+a[2*k+1];
	}
	int query(int k,int l,int r,int ql,int qr){
		if(ql<=l&&qr>=r)return a[k];
		int mid=(l+r)/2,res=0;
    	if(ql<=mid)res+=query(2*k,l,mid,ql,qr);
    	if(qr>mid)res+=query(2*k+1,mid+1,r,ql,qr);
    	return res;
	}
}tr;

signed main(){
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>c[i];
		pos[c[i]].push_back(i);
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j+1<pos[i].size();j++){
			int l=pos[i][j]+1,r=pos[i][j+1]-1;
			if(l==r+1)continue;
			int nowmx=mx.query(1,1,n,l,r);
			p[++top]={nowmx,i};
		}
		pre[i]=pre[i-1]+(pos[i].size()>0);
		for(auto j:pos[i])mx.modify(1,1,n,j,c[j]);
	}
	sort(p+1,p+top+1);
	for(int i=1;i<=m;i++){
		cin>>as[i].l>>as[i].r;as[i].id=i;
		ans[i]=pre[as[i].r]-pre[as[i].l-1];
	}
	sort(as+1,as+m+1);
	for(int i=1,j=1;i<=m;i++){
		while(j<=top&&p[j].mx>=as[i].l){
			tr.modify(1,1,n,p[j++].x,1);
		}
		ans[as[i].id]+=tr.query(1,1,n,as[i].l,as[i].r);
	}
	for(int i=1;i<=m;i++)cout<<ans[i]<<"\n";
}

---

## 作者：tribool4_in (赞：0)

首先考虑对于单次询问 $[l,r]$ 如何做，考虑取出值域在 $[l,r]$ 的数字组成的序列作为询问序列，最优方案显然是首先减去最小值，对形成的若干段非零段分别分治继续处理。

考虑一次询问 $[l,r]$ 中，某种数字 $x$ 在询问序列中的若干个出现位置，其产生的贡献显然为其连续段个数。回到原序列，考虑 $x$ 相邻两次出现位置 $p,q$，若 $\displaystyle(\max_{i\in[p+1,q-1],a_i\le r}a_i)\ge l$ 则会产生一次代价（因为此时 $p,q$ 在询问序列上不连续）；对于 $x$ 的第一次出现位置也会产生一次代价。

于是考虑将询问离线，从小到大枚举 $r$，在当前序列中加入 $[1,r]$ 的所有数字。考虑如何从 $r-1$ 推到 $r$。首先对于 $r$ 第一次出现位置会产生一次贡献。然后对于 $r$ 相邻两次出现位置 $p,q$，求出当前序列上 $[p+1,q-1]$ 的最大值 $v$，则位置 $q$ 会对所有 $l\le v$ 的询问产生贡献。树状数组维护即可。

好像卡了 iostream 关同步流。没素质。不过拿了个最优解。

```cpp
#include <bits/stdc++.h>
using namespace std;

using u32 = unsigned;
struct IO_Tp {
    const static int _I_Buffer_Size = 53 << 20; char _I_Buffer[_I_Buffer_Size], *_I_pos = _I_Buffer;
    const static int _O_Buffer_Size = 33 << 20; char _O_Buffer[_O_Buffer_Size], *_O_pos = _O_Buffer;
    u32 m[10000];
    IO_Tp() {
        constexpr u32 e0 = '\0\0\0\1', e1 = '\0\0\1\0', e2 = '\0\1\0\0', e3 = '\1\0\0\0';
        int x = 0;
        for (u32 i = 0, c0 = '0000'; i != 10; ++i, c0 += e0)
            for (u32 j = 0, c1 = c0; j != 10; ++j, c1 += e1)
                for (u32 k = 0, c2 = c1; k != 10; ++k, c2 += e2)
                    for (u32 l = 0, c3 = c2; l != 10; ++l, c3 += e3) m[x++] = c3;
        fread(_I_Buffer, 1, _I_Buffer_Size, stdin);
    }
    ~IO_Tp() { fwrite(_O_Buffer, 1, _O_pos - _O_Buffer, stdout); }
    IO_Tp &operator>>(int &res) {
        bool rev = 0;
        while (!isdigit(*_I_pos) && *_I_pos != '-') ++_I_pos;
        if (*_I_pos == '-') rev = 1, ++_I_pos;
        res = *_I_pos++ - '0';
        while (isdigit(*_I_pos)) res = res * 10 + (*_I_pos++ - '0');
        if (rev) res = -res;
        return *this;
    }
    IO_Tp &operator<<(int x) {
        if (x == 0) { *_O_pos++ = '0'; return *this; }
        static char _buf[35]; char *_pos = _buf + 35;
        while (x >= 10000) *--reinterpret_cast<u32 *&>(_pos) = m[x % 10000], x /= 10000;
        *--reinterpret_cast<u32 *&>(_pos) = m[x];
        _pos += (x < 1000) + (x < 100) + (x < 10);
        _O_pos = copy(_pos, _buf + 35, _O_pos);
        return *this;
    }
    IO_Tp &operator<<(char ch) {
        *_O_pos++ = ch;
        return *this;
    }
} IO;
#define cin IO
#define cout IO

const int N = 1e6 + 10;
int n, q, a[N];
vector<int> pos[N];
struct BIT {
#define lowbit(x) ((x) & (-(x)))
    int b[N];
    void update(int x, int v) {
        x = n - x + 1;
        for (; x <= n; x += lowbit(x)) b[x] += v;
    }
    int query(int x) {
        x = n - x + 1;
        int sum = 0;
        for (; x > 0; x -= lowbit(x)) sum += b[x];
        return sum;
    }
} bt;
#define max(x, y) ((x) < (y) ? (y) : (x))
struct ZkwSeg {
    int n, t[N << 2];
    void init(int _n) { n = 1 << __lg(_n) + 1; }
    void update(int p, int v) {
        t[p += n] = v;
        for (p >>= 1; p; p >>= 1) t[p] = max(t[p << 1], t[p << 1 | 1]);
    }
    int query(int l, int r) {
        if (l > r) return 0;
        int ans = 0;
        for (l += n - 1, r += n + 1; l ^ r ^ 1; l >>= 1, r >>= 1) {
            if (~l & 1) ans = max(ans, t[l ^ 1]);
            if (r & 1) ans = max(ans, t[r ^ 1]);
        }
        return ans;
    }
} sg;
struct Qry {
    int l, r, id;
} qr[N];
int ans[N];
int main() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i], pos[a[i]].push_back(i);
    for (int i = 1; i <= q; i++) cin >> qr[i].l >> qr[i].r, qr[i].id = i;
    sort(qr + 1, qr + q + 1, [](const Qry &a, const Qry &b) { return a.r < b.r; });
    sg.init(n);
    for (int i = 1, j = 1; i <= n; i++) {
        int pre = -1;
        for (auto p : pos[i]) {
            sg.update(p, i);
            if (pre == -1) bt.update(i, 1);
            else {
                int v = sg.query(pre + 1, p - 1);
                if (v) bt.update(v, 1);
            }
            pre = p;
        }
        for (; j <= q && qr[j].r == i; j++) ans[qr[j].id] = bt.query(qr[j].l);
    }
    for (int i = 1; i <= q; i++) cout << ans[i] << '\n';
    return 0;
}
```

---

## 作者：MiRaciss (赞：0)

挺神仙的一种离线方式。

首先将**值域**在 $[l,r]$ 的所有值拿出来。因为区间无交所以一定要**从小到大**把所有的值变为 `0` ，而且每种权值至少删一次，接下来考虑额外贡献。

考虑如果两个相同的数中间出现比它们小的数，这两个数就无法同时删除。推广一下，每相邻的两个相同的数之间出现了比他们小的数就会增加贡献。

如果说我们查询的区间是 $[1,r]$ ，那么就很可做了。因为这时候我们只需要考虑每个小于 $r$ 的数是否存在如上的额外贡献，但是发现查询区间有个左端点 $l$。

你看啊，我们一开始发现查询区间为时 $[1,r]$ 很可做，那么多了一个 $l$ 的影响无非是 $[1,l-1]$ 的数不在出现在序列上。第一个影响是这段的数不再对答案产生贡献，第二个影响是对于 $[l,r]$ 的数不能再因为 $[1,l-1]$ 的数产生额外贡献。对于第一个影响，我们可以将查询拆成 $[1,l-1]$ 和 $[1,r]$；对于第二个影响，如果两个相同的数之间比它们小的数大于 `l` 那么才能产生贡献，所以我们只需要用一颗支持查询区间最大值的线段树看看这个区间的最大值是否满足就行了。

然后贡献可以看成是个前缀形势，需要快速修改和查询，再写个树状数组就好了。

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m;
int a[1000005];

struct Tree{
	int bit[1000005];
	int Lowbit(int x){ return x&(-x); }
	void Change(int x,int val){ if(!x) return ;for(int i=x;i<=n;i+=Lowbit(i)) bit[i]+=val; }
	int Find(int x){ int ans=0;for(int i=x;i>=1;i-=Lowbit(i)) ans+=bit[i]; return ans; }
}T;

struct zz{
	int l,r;
	int val;
};
struct Seg_Tree{
	zz t[4000005];
	#define lc p<<1
	#define rc p<<1|1
	void Push_Up(int p){
		t[p].val=max(t[lc].val,t[rc].val);
	}
	void Build_Tree(int p,int l,int r){
		t[p].l=l,t[p].r=r;
		if(t[p].l==t[p].r) return t[p].val=0,void();
		int mid=(t[p].l+t[p].r)>>1;
		Build_Tree(lc,l,mid),Build_Tree(rc,mid+1,r);
		Push_Up(p);
	}
	void Change_Tree(int p,int pos,int val){
		if(!pos) return ;
		if(t[p].l==t[p].r) return t[p].val=val,void();
		int mid=(t[p].l+t[p].r)>>1;
		if(pos<=mid) Change_Tree(lc,pos,val);
		else Change_Tree(rc,pos,val);
		Push_Up(p);
	}
	int Find_Tree(int p,int l,int r){
		if(l>r) return 0;
		if(l<=t[p].l&&t[p].r<=r) return t[p].val;
		int mid=(t[p].l+t[p].r)>>1;
		int ans=0;
		if(l<=mid) ans=max(ans,Find_Tree(lc,l,r));
		if(mid+1<=r) ans=max(ans,Find_Tree(rc,l,r));
		return ans;
	}
}TT;

int sum[1000005];
vector<int> v[1000005];

struct ss{
	int val,id,op;
};
vector<ss> q[1000005];
int ans[1000005];

int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),v[a[i]].push_back(i);
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+(v[i].size()>0);
	TT.Build_Tree(1,1,n); 
	for(int i=1,l,r;i<=m;i++) scanf("%d%d",&l,&r),q[l-1].push_back((ss){l,i,-1}),q[r].push_back((ss){l,i,1}),ans[i]=sum[r]-sum[l-1];
//	for(int i=1;i<=m;i++) printf("%d ",ans[i]);
//	printf("\n");
	for(int i=1;i<=n;i++){
		for(int j=1;j<v[i].size();j++){
			int l=v[i][j-1],r=v[i][j];
			int id=TT.Find_Tree(1,l+1,r-1);
			T.Change(id,1);
		}
		for(int j=0;j<v[i].size();j++) TT.Change_Tree(1,v[i][j],i); 
		for(int j=0;j<q[i].size();j++){
			int val=q[i][j].val,id=q[i][j].id,op=q[i][j].op;
			ans[id]+=op*(T.Find(n)-T.Find(val-1));
		}
	}
	for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
	return 0;
}
```

---

