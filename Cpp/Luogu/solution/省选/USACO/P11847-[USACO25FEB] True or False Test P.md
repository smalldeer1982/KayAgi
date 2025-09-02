# [USACO25FEB] True or False Test P

## 题目描述

**注意：本题的时间限制为 3 秒，通常限制的 1.5 倍。本题的内存限制为 512MB，通常限制的 2 倍。**

Bessie 正在参加一场 $N$ 道判断题的考试（$1\le N\le 2\cdot 10^5$）。对于第 $i$ 道题目，如果她答对了将获得 $a_i$ 分，如果答错了将失去 $b_i$ 分，如果不回答则分数不变（$0<a_i,b_i\le 10^9$）。

因为 Bessie 是一头聪明的牛，她知道所有的答案，但她担心 Elsie（主考官）会在测试后追溯性地更改至多 $k$ 道题目，使得 Bessie 无法答对这些题目。

给定 $Q$（$1\le Q\le N+1$）个 $k$ 的候选值（$0\le k\le N$），求对于每一个 $k$，Bessie 在回答至少 $k$ 道题目的前提下可以保证的分数。

## 说明/提示

样例 1 解释：

对于每一个 $k$ 的值，Bessie 的最优策略都是回答所有的题目。

- 测试点 $2\sim 4$：$N\le 100$。
- 测试点 $5\sim 7$：$Q\le 10$，$N\le 2\cdot 10^5$。
- 测试点 $7\sim 20$：没有额外限制。

## 样例 #1

### 输入

```
2 3
3 1
4 2
2
1
0```

### 输出

```
-3
1
7```

# 题解

## 作者：Purslane (赞：7)

# Solution

如果 Bessie 选定了某些考试（$k$ 给定），Elsie 如何让 Bessie 获得最低的成绩呢？

显然 Elsie 会选择 $a_i+b_i$ 最大的 $k$ 场考试。

所以，我们可以将考试按照 $a_i+b_i$ 排序。Bessie 要选出若干场考试，在前 $k$ 场获得 $-b_i$ 的分数，后若干场获得 $a_i$ 的分数。

贪心的，后若干场的 $a_i$ 应该全选，而前若干场的 $b_i$ 应该选前 $k$ 小的。

因此你可以得到一个 $O(n \log n)$ 单组询问的方法——从前往后扫描，维护前缀的 $b$ 的前 $k$ 小的和。

-----------

当然你也可以 DP。设 $dp_{i,j}$ 为，考虑了位置 $\ge i$ 的数，选了 $j$ 场考试给 Elsie 攻击你能获得的最大代价。

转移是容易的：

$dp_{i,0} = dp_{i+1,0} + a_i$，$dp_{i,j} = \max\{dp_{i+1,j},dp_{i+1,j-1}-b_i\}$。

显然 $dp_{i,*}$ 是单调递减的。看起来不太好优化，那就上 Slope Tricks！

打表发现，$dp_{i,*}$ 的差分数组是单峰的。虽然没有凹凸性，但是总比啥都没有强。画一个示意图：

![](https://s21.ax1x.com/2025/03/04/pEGvFz9.png)

先考虑优化 $dp_{i,j} = \max\{dp_{i+1,j},dp_{i+1,j-1}-b_i\}$。

这相当于什么呢？如果 $dp_{i+1,j-1} - dp_{i+1,j} \ge b_i$，就从 $(i+1,j-1)$ 转移到 $(i,j)$；否则从 $(i+1,j)$ 转移到 $(i,j)$。

发现这样的 $j$ 是一段前缀和后缀。所以我们使用 multiset 维护两个部分的差分数组，容易发现每次只有 $O(1)$ 个位置的差分发生变化（这里是 slope tricks 的基础操作，不赘述）。

使用数学归纳法也确实能够证明，差分数组一直是单峰的。

注意修改两个 multiset 的时候，如果修改的是最靠近拐点的差分，要注意判断单调性是否仍然成立，要将 $O(1)$ 个元素所在的集合进行微调。

细节有点多，场上调了整整一个小时。 /tuu

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
int n,q,a[MAXN],b[MAXN],suf[MAXN],ans[MAXN];
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>q;
	vector<pair<int,int>> vc;
	ffor(i,1,n) cin>>a[i]>>b[i],vc.push_back({a[i],b[i]});
	sort(vc.begin(),vc.end(),[](pair<int,int> A,pair<int,int> B) {return A.first+A.second>B.first+B.second;});
	ffor(i,1,n) a[i]=vc[i-1].first,b[i]=vc[i-1].second;
	multiset<int> d1,d2;
	d1.insert(a[n]+b[n]);
	roff(i,n-1,1) {
		int flg=0;
		if(*d1.begin()<b[i]) flg=1;
		if(!flg) {
			d1.insert(a[i]+b[i]);
			continue ;	
		}
		flg=0;
		if(*(--d1.end())>b[i]) flg=1;
		if(!d2.empty()&&*(--d2.end())>b[i]) flg=1;
		if(!flg) {
			int m=*(--d1.end());
			d1.erase(--d1.end());
			d1.insert(m+a[i]);
			d2.insert(b[i]);
			if(*d2.begin()<*d1.begin()) d1.insert(*d2.begin()),d2.erase(d2.begin());
			continue ;	
		}
		if(*(--d1.end())<=b[i]) {
			d2.insert(b[i]);
			int m=*(--d1.end());
			d1.erase(--d1.end());
			d1.insert(m+a[i]);
			if(*d2.begin()<*d1.begin()) d1.insert(*d2.begin()),d2.erase(d2.begin());
			continue ;
		}
		auto it=d1.upper_bound(b[i]);
		int c=*prev(it),ov=*it;
		d1.erase(prev(it)),d1.insert(c+ov-b[i]),d1.erase(d1.find(ov)),d1.insert(a[i]+b[i]),d2.insert(b[i]);
		if(*d2.begin()<*d1.begin()) d1.insert(*d2.begin()),d2.erase(d2.begin());
	}
	int tot=0;
	ffor(i,1,n) tot+=a[i];
	ffor(i,0,n) {
		ans[i]=tot;
		if(!d1.empty()) tot-=*(--d1.end()),d1.erase(--d1.end());
		else if(!d2.empty()) tot-=*(d2.begin()),d2.erase(d2.begin());	
	}
	ffor(i,1,q) {
		int k;
		cin>>k;
		cout<<ans[k]<<'\n';	
	}
	return 0;
}
```

---

## 作者：OIer_ljb (赞：6)

Elsie 改一道题目的答案的贡献是把得分减去 $a_i+b_i$，所以我们先将所有题目按照 $a_i+b_i$ 排序。

那么相当于 Bessie 选择一些点，使得前 $k$ 个造成 $-b_i$ 贡献，后面的造成 $a_i$ 的贡献。

对于每一组询问，我们考虑枚举一个分界点 $x$，就相当于在分界点前选 $k$ 个 $-b_i$,分界点后选任意个 $a_i$。

那么分界点之后的显然全选，分界点之前显然选择最大的  $k$ 个 $-b_i$。

那么对于每个询问，枚举分界点，用主席树求出前缀前 $k$ 大即可。

这样复杂度是 $O(qn\log n)$，能过 35 分。

正解：可以通过感受（或者打表）的方式发现最优的分界点 $x$ 随 $k$ 增大而单调增大。

证明：考虑 $k,k+1$ 的最优分界点 $x_k,x_{k+1}$，显然$x_k$ 和 $x_{k+1}$ 这两个点一定会在对应方案被选。

如果 $x_k>x_{k+1}$，考虑 $k+1$ 选择方案中分界点前的任意一个被选择的点 $i$，考虑把它替换成 $x_k$，根据定义显然都不会更优，那么你把 $k$ 的最优方案中的 $x_k$ 替换成 $k+1$ 方案中的任意一个没有在 $k$ 的最优方案中出现过的数一定会更优（显然一定会有一个位置没有出现过），那么新的对 $k$ 的最优方案的决策点就是 $x_{k+1}$ 了。

也就是说有决策单调性，直接套个分治板子就行了，时间复杂度 $O(q\log^2n)$。


### code
``` C++
#include<bits/stdc++.h>
using namespace std;
#define usefile(p) freopen(#p".in","r",stdin),freopen(#p".out","w",stdout);
#define fo(i,a,b) for(int i=(a);i<=(b);++i)
#define fu(i,a,b) for(int i=(a);i<(b);++i)
#define fd(i,a,b) for(int i=(a);i>=(b);--i)
#define mk make_pair
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
const int N=2e5+5;
const ll inf=1e16;
int n,Q,v[N],rt[N],cnt;
ll Ans[N],s[N];
struct pro{int a,b;};
pro c[N],d[N],q[N];
inline bool cmp(pro u,pro v){return u.a+u.b>v.a+v.b;}
inline bool cmp2(pro u,pro v){return u.a<v.a;}
struct nd{int ls,rs,sum;ll val;};
nd t[N<<5];
inline void pushup(int o)
{
	t[o].sum=t[t[o].ls].sum+t[t[o].rs].sum;
	t[o].val=t[t[o].ls].val+t[t[o].rs].val;
}
inline int newnd(int o){++cnt;t[cnt]=t[o];return cnt;}
int modify(int o,int l,int r,int x)
{
	o=newnd(o);
	if(l==r){++t[o].sum;t[o].val+=d[l].a;return o;}
	int mid=l+r>>1;
	if(x<=mid)t[o].ls=modify(t[o].ls,l,mid,x);
	else t[o].rs=modify(t[o].rs,mid+1,r,x);
	pushup(o);return o;
}
ll query(int o,int l,int r,int k)
{
	if(l==r)return t[o].val;
	int mid=l+r>>1;
	if(t[t[o].ls].sum>=k)return query(t[o].ls,l,mid,k);
	else return t[t[o].ls].val+query(t[o].rs,mid+1,r,k-t[t[o].ls].sum);	
}
void solve(int l,int r,int L,int R)
{
	if(l>r)return ;
	int mid=l+r>>1,le=max(L,q[mid].a),p=0;
	int id=q[mid].b;
	fo(i,le,R)
	{
		ll val=s[n]-s[i]-query(rt[i],1,n,q[mid].a);
		if(val>Ans[id])Ans[id]=val,p=i;
	}
	solve(l,mid-1,L,p);solve(mid+1,r,p,R);
}
int main()
{
	scanf("%d%d",&n,&Q);
	fo(i,1,n)scanf("%d%d",&c[i].a,&c[i].b);
	sort(c+1,c+n+1,cmp);
	fo(i,1,Q)scanf("%d",&q[i].a),q[i].b=i,Ans[i]=-inf;
	fo(i,1,n)d[i].a=c[i].b,d[i].b=i,s[i]=s[i-1]+c[i].a;
	sort(d+1,d+n+1,cmp2);sort(q+1,q+Q+1,cmp2);
	fo(i,1,n)c[d[i].b].b=i;
	fo(i,1,n)rt[i]=modify(rt[i-1],1,n,c[i].b);
	solve(1,Q,0,n);
	fo(i,1,Q)printf("%lld\n",Ans[i]);
	return 0;
}
```

---

## 作者：Masterwei (赞：4)

决策单调性板子题。

考虑将原问题转化，先选择一部分 $a$，然后选择被选当中 $k$ 个 $a+b$ 最大的，减掉，即为一个合法的备选答案。

于是我们考虑将原序列按 $a_i+b_i$ 排序，那么对于一个 $k$，我们就可以将问题转化为找到一个 $p$，使得 $\displaystyle\sum_{i=p}^{n}a_i$ 减去前 $p-1$ 中 $b$ 的前 $k$ 小最大。这个最大值就是答案。

考虑优化，发现转移时有单调性，直接分治即可做到 $O(n\log n\log V)$。


```cpp
#include<bits/stdc++.h>
#define int long long
#define fir first
#define sec second
using namespace std;
inline int read(){
	int x=0;bool f=0;char ch=getchar();
	while(ch<'0'||ch>'9')f^=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
const int Maxn=2e5+5,V=1e9,inf=1e18;
int n,q;
struct node{
	int a,b;
}p[Maxn];
int suf[Maxn];
struct Tree{
	int ls,rs,data,sum;
}t[Maxn<<6];
int root[Maxn],cnt;
void change(int&x,int y,int l,int r,int d){
	x=++cnt;t[x]=t[y];t[x].data+=d;t[x].sum++;if(l==r)return;
	int mid=l+r>>1;
	if(mid>=d)change(t[x].ls,t[y].ls,l,mid,d);
	else change(t[x].rs,t[y].rs,mid+1,r,d);
}
int query(int x,int l,int r,int k){
	if(l==r)return k*l;
	int mid=l+r>>1;
	if(t[t[x].ls].sum<k)return t[t[x].ls].data+query(t[x].rs,mid+1,r,k-t[t[x].ls].sum);
	return query(t[x].ls,l,mid,k);
}
int ans[Maxn];
inline int get(int i,int j){
	return suf[j]-query(root[j-1],1,V,i);
}
void solve(int l,int r,int L,int R){
	if(l>r||L>R)return;
	int mid=l+r>>1;
	pair<int,int>tmp={-inf,0};
	for(int i=max(L,mid+1);i<=R;i++)tmp=max(tmp,make_pair(get(mid,i),i));
	ans[mid]=tmp.fir;solve(l,mid-1,L,tmp.sec);solve(mid+1,r,tmp.sec,R);
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	n=read();q=read();
	for(int i=1;i<=n;i++)p[i]={read(),read()};
	sort(p+1,p+1+n,[&](node i,node j){return i.a+i.b>j.a+j.b;});
	for(int i=1;i<=n;i++)change(root[i],root[i-1],1,V,p[i].b);
	for(int i=n;i;i--)suf[i]=suf[i+1]+p[i].a;
	solve(0,n,1,n+1);
	while(q--)printf("%lld\n",ans[read()]);
	return 0;
}

```

---

## 作者：jiamengtong (赞：3)

场切了这个题，感觉很帅，于是写了这篇题解。

首先考虑如果确定了选哪些，Elsie 会选择哪些题目改变答案。这是一个经典的贪心。假设我们一开始一个题目都不改，那么有 $\sum a_i$ 的代价。如果选择修改一个题目，相当于把当前代价减去 $a_i+b_i$，这代表 Elsie 必定会选择 $a_i+b_i$ 前 $k$ 大的位置反转。

我们考虑将序列按照 $a_i+b_i$ 排序，那么我们选出的一个子序列中，必定是前 $k$ 个被 Elsie 反转。如果记 $ps$ 表示选的点的位置的集合，最终获得的代价就是 $\sum \limits _{i=k+1}^{|ps|}a_{ps_i}-\sum \limits _{i=1}^k b_{ps_{i}}$。由于 $a$ 全部为正，所以多选一定不劣。这意味着 $ps_k$ 后的全部的问题我们都会选择回答。

于是题目被转化成如下问题：记 $suf_i$ 表示 $i$ 后缀 $a$ 的和，$pre_{i,j}$ 表示 $b$ 的 $i$ 前缀中，前 $j$ 小值的和，求 $\max \limits _{i=k}^n pre_{i,k}+suf_{i+1}$。

暴力做法是 $O(nq\log n)$ 的，可以通过前两档。想要获得满分我们还需要继续优化。

我们有如下结论：$\forall i\le n,j<k\le n,j$ 前缀中的第 $i$ 小值 $\ge k$ 前缀中的第 $i$ 小值。证明显然。转化到 $pre$ 数组上，可以发现如下结论：$\forall i\le n,j<k\le n,pre_{j,i}-pre_{j,i-1}\ge pre_{k,i}-pre_{k,i-1}$。这个结论具体用处下面会提到。

我们想要优化这个东西，容易想到，如果 $k$ 的“决策点”（答案取到最大值的 $ps_k$，如果有多个，取最小的那个）单调，就很好做了。我们考虑反证法。如果存在 $i,j<k$，使得 $i$ 的决策点为 $k$，$i+1$ 的决策点为 $j$，那么有 
$$\left\{\begin{matrix}
suf_{j+1}-pre_{j,i}<suf_{k+1}-pre_{k,i} \\
suf_{j+1}-pre_{j,i+1}\ge suf_{k+1}-pre_{k,i+1}
\end{matrix}\right.$$

简单变形可以得到 $pre_{k,i+1}-pre_{k,i}>pre_{j,i+1}-pre_{j,i}$，由于 $j<k$，与上面的结论矛盾，所以不存在相邻两个决策点逆序，所以决策点单调。于是我们使用决策单调性分治优化这个东西，求 $pre$ 显然可以主席树完成。这样便可以预处理出所有答案，$O(1)$ 回答询问。时间复杂度 $O(n\log^2n)$。

代码如下：
```cpp
#include<bits/stdc++.h>
#define M 200005
#define int long long
using namespace std;
int a[M], b[M], n, q, suf[M], id[M], to[M], ans[M];
map<int, int> mp;
struct SGT{
	struct node{
		int cnt, sum, ls, rs;
	}tr[M << 5];
	int rt[M], tot;
	void Insert(int &p, int pr, int l, int r, int x, int k)
	{
		p = ++tot;
		tr[p] = tr[pr];
		tr[p].cnt++;
		tr[p].sum += k;
		if(l == r) return;
		int mid = (l + r) >> 1;
		if(x <= mid) Insert(tr[p].ls, tr[pr].ls, l, mid, x, k);
		else Insert(tr[p].rs, tr[pr].rs, mid + 1, r, x, k);
	}
	int query(int p, int l, int r, int cnt)
	{
		if(!cnt) return 0;
		if(l == r) return cnt * (tr[p].sum / tr[p].cnt);
		int mid = (l + r) >> 1;
		if(tr[tr[p].ls].cnt >= cnt) return query(tr[p].ls, l, mid, cnt);
		else return tr[tr[p].ls].sum + query(tr[p].rs, mid + 1, r, cnt - tr[tr[p].ls].cnt);
	}
	void init()
	{
		rt[0] = 1;
		tot = 1;
		for(int i = 1; i <= n; i++) Insert(rt[i], rt[i - 1], 1, n, to[id[i]], b[id[i]]);
	}
}sgt;
void calc(int l, int r, int lb, int rb)
{
	if(l > r || lb > rb) return;
	int mid = (l + r) >> 1, anss = -1e18, ps;
	for(int i = max(mid, lb); i <= rb; i++)
	{
		int num = suf[i + 1] - sgt.query(sgt.rt[i], 1, n, mid);
		if(num > anss) anss = num, ps = i;
	}
	ans[mid] = anss;
	calc(l, mid - 1, lb, ps);
	calc(mid + 1, r, ps, rb);
}
signed main()
{
	scanf("%lld%lld", &n, &q);
	int sum = 0;
	for(int i = 1; i <= n; i++) scanf("%lld%lld", &a[i], &b[i]), sum -= b[i], mp[b[i]];
	int tot = 0;
	for(auto &t : mp) t.second = ++tot;
	for(int i = 1; i <= n; i++) to[i] = mp[b[i]];
	for(int i = 1; i <= n; i++) id[i] = i;
	sort(id + 1, id + n + 1, [&](int x, int y){
		if(a[x] + b[x] != a[y] + b[y]) return a[x] + b[x] > a[y] + b[y];
		return b[x] < a[y];
	});
	for(int i = n; i >= 1; i--) suf[i] = suf[i + 1] + a[id[i]];
	sgt.init();
	calc(0, n - 1, 0, n);
	for(int i = 1; i <= q; i++)
	{
		int x;
		scanf("%lld", &x);
		if(x == n) printf("%lld\n", sum);
		else printf("%lld\n", ans[x]);
	}
	return 0;
}
```

---

## 作者：Polarisx (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P11847)。

典题。

## 思路

首先对于每个 $k$，将其对应的答案表示出来：

$$ \max_{|S|\ge k}\left(\sum_{i\in S}a_i-\mathrm{sum}(S,k) \right)$$

其中 $\mathrm{sum}(S,k)=\max_{T\subseteq S,|T|=k} \sum_{i\in T}(a_i+b_i)$。

套路的，将序列按 $a_i+b_i$ 排序，枚举 $i$，表示在 $i$ 前面选了 $k$ 个，答案就是：

$$\max_{|S|=k}\left[\max_{j\in S}j\le i\right]\left(\sum_{j=i+1}^n a_j-\sum_{j\in S}b_j \right)$$

直接 set/主席树求即可，单次询问时间复杂度 $\mathcal O(n\log n)$。

对于每个 $k$，使答案最大的 $i$ 我们称为 $k$ 的决策点 $f(k)$，不难发现 $\forall k_1\le k_2$，均有 $f(k_1)\le f(k_2)$（当 $k\gets k+1$ 时，考虑其决策点的走向，不难发现只有决策点右移或不动才是最优的），直接决策单调性分治即可，时间复杂度 $\mathcal O(n\log^2 n)$。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn=2e5+7;
const ll inf=1e12;
int n,m,Q;
struct node{
    int a,b;
}a[Maxn];
int b[Maxn];
ll ans[Maxn];
ll sm[Maxn];

int rt[Maxn],tot;
struct TREE{
    int l,r,o;
    ll val;
}t[Maxn*23];

inline int clone(int node,int val){
    t[++tot]=t[node];
    t[tot].o++,t[tot].val+=val;
    return tot;
}
void buildtree(int &node,int l,int r){
    if(!node) node=++tot;
    if(l==r) ;
    else{
        int mid=(l+r)>>1;
        buildtree(t[node].l,l,mid);
        buildtree(t[node].r,mid+1,r);
    }
}
int modify(int node,int l,int r,int x,int v){
    node=clone(node,v);
    if(l==r) ;
    else{
        int mid=(l+r)>>1;
        if(x<=mid) t[node].l=modify(t[node].l,l,mid,x,v);
        else t[node].r=modify(t[node].r,mid+1,r,x,v);
    }
    return node;
}
ll query(int node,int l,int r,int k){
    if(l==r) return 1ll*b[l]*k;
    int mid=(l+r)>>1,lv=t[t[node].l].o;
    if(k<=lv) return query(t[node].l,l,mid,k);
    else return t[t[node].l].val+query(t[node].r,mid+1,r,k-lv);
}

void solve(int l,int r,int L,int R){
    if(l>r) return ;
    if(L==R){
        for(int i=l;i<=r;i++) ans[i]=sm[L+1]-query(rt[L],1,m,i);
        return ;
    }
    int mid=(l+r)>>1,ansp=0; ll ansv=-inf;

    for(int i=max(L,mid);i<=R;i++){
        if(sm[i+1]-query(rt[i],1,m,mid)>ansv)
            ansv=sm[i+1]-query(rt[i],1,m,mid),ansp=i;
    }
    ans[mid]=ansv;
    solve(l,mid-1,L,ansp), solve(mid+1,r,ansp,R);
}

int main(){
    scanf("%d%d",&n,&Q);
    for(int i=1;i<=n;i++) scanf("%d%d",&a[i].a,&a[i].b),b[i]=a[i].b;

    sort(a+1,a+n+1,[](node x,node y){
        return x.a+x.b>y.a+y.b;
    });
    for(int i=n;i;i--) sm[i]=sm[i+1]+a[i].a;

    sort(b+1,b+n+1);
    m=unique(b+1,b+n+1)-b-1;

    buildtree(rt[0],1,m);
    for(int i=1;i<=n;i++){
        int p=lower_bound(b+1,b+m+1,a[i].b)-b; 
        rt[i]=modify(rt[i-1],1,m,p,a[i].b);
    }

    solve(0,n,0,n);

    while(Q--){
        int x; scanf("%d",&x); 
        printf("%lld\n",ans[x]);
    }

    return 0;
}
```

---

## 作者：EuphoricStar (赞：2)

提供一个复杂度较劣但是好想好写的做法。

考虑如何快速回答单次询问。Bessie 确定了她答对的题目后，Elsie 的最优策略是把 Bessie 答对的题目中 $a_i + b_i$ 前 $k$ 大的题目 ban 掉。所以问题变成选一个集合 $S$，使得 $\sum\limits_{i \in S} a_i$ 减去 $S$ 中 $a_i + b_i$ 前 $k$ 大的和最大。

把全部题目按照 $a_i + b_i$ 排序，枚举一个 $i \ge k$，表示在 $[1, i]$ 中恰好选了 $k$ 个，那么 $[i + 1, n]$ 中的可以全选。设 $s_i = \sum\limits_{j = i}^n a_j$，此时答案为 $s_{i + 1} - f(k, i)$，$f(k, i)$ 为 $[1, i]$ 中 $b_j$ 前 $k$ 小的和，可以在枚举 $i$ 时树状数组维护，也可以主席树上二分。所以单组询问能在 $O(n \log n)$ 时间内解决。

这时候你猜一手决策单调性，写一发发现过了。证明也很简单，设 $g(k, i) = s_{i + 1} - f(k, i)$，需要证：
$$
g(k, i) + g(k + 1, i + 1) \ge g(k, i + 1) + g(k + 1, i)
$$
即证：
$$
f(k, i) + f(k + 1, i + 1) \le f(k, i + 1) + f(k + 1, i)
$$
这个东西也就是 $f(k, i) - f(k, i + 1) \le f(k + 1, i) - f(k + 1, i + 1)$。考虑 $b_{i + 1}$：

- 如果 $b_{i + 1}$ 在 $[1, i + 1]$ 中排名 $\le k$，那么左式等于 $[1, i]$ 中第 $k$ 小减去 $b_{i + 1}$，右式等于 $[1, i]$ 中第 $k + 1$ 小减去 $b_{i + 1}$；
- 如果 $b_{i + 1}$ 在 $[1, i + 1]$ 中排名 $= k + 1$，那么左式等于 $0$，右式等于 $[1, i]$ 中第 $k + 1$ 小减去 $b_{i + 1}$；
- 如果 $b_{i + 1}$ 在 $[1, i + 1]$ 中排名 $> k + 1$，那么左式和右式都等于 $0$。

时间复杂度 $O(n \log^2 n)$。

```cpp
#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define uint unsigned
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<ll, ll> pii;

const int maxn = 200100;

ll n, m, f[maxn], p[maxn], ans[maxn];
pii lsh[maxn];

struct node {
	ll a, b;
} a[maxn];

struct BIT {
	ll c[maxn];
	
	inline void update(ll x, ll d) {
		for (int i = x; i <= n; i += (i & (-i))) {
			c[i] += d;
		}
	}
	
	inline ll query(ll x) {
		ll res = 0;
		for (int i = x; i; i -= (i & (-i))) {
			res += c[i];
		}
		return res;
	}
	
	inline ll kth(ll k) {
		ll s = 0, p = 0;
		for (int i = 19; ~i; --i) {
			if (p + (1 << i) <= n && s + c[p + (1 << i)] < k) {
				s += c[p += (1 << i)];
			}
		}
		return p + 1;
	}
} T1, T2;

void dfs(int l, int r, int pl, int pr) {
	if (l > r || pl > pr) {
		return;
	}
	int mid = (l + r) >> 1, x = -1;
	for (int i = pl; i <= pr; ++i) {
		if (i) {
			T1.update(p[i], 1);
			T2.update(p[i], lsh[p[i]].fst);
		}
		if (i >= mid) {
			int t = T1.kth(mid);
			ll v = f[i + 1] - T2.query(t);
			if (v > ans[mid]) {
				ans[mid] = v;
				x = i;
			}
		}
	}
	for (int i = pl; i <= pr; ++i) {
		if (i) {
			T1.update(p[i], -1);
			T2.update(p[i], -lsh[p[i]].fst);
		}
	}
	dfs(l, mid - 1, pl, x);
	for (int i = pl; i < x; ++i) {
		if (i) {
			T1.update(p[i], 1);
			T2.update(p[i], lsh[p[i]].fst);
		}
	}
	dfs(mid + 1, r, x, pr);
	for (int i = pl; i < x; ++i) {
		if (i) {
			T1.update(p[i], -1);
			T2.update(p[i], -lsh[p[i]].fst);
		}
	}
}

void solve() {
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld%lld", &a[i].a, &a[i].b);
	}
	sort(a + 1, a + n + 1, [&](const node &a, const node &b) {
		return a.a + a.b > b.a + b.b;
	});
	for (int i = 1; i <= n; ++i) {
		lsh[i] = pii(a[i].b, i);
	}
	sort(lsh + 1, lsh + n + 1);
	for (int i = n; i; --i) {
		f[i] = f[i + 1] + a[i].a;
	}
	for (int i = 1; i <= n; ++i) {
		p[i] = lower_bound(lsh + 1, lsh + n + 1, pii(a[i].b, i)) - lsh;
	}
	mems(ans, -0x3f);
	dfs(0, n, 0, n);
	while (m--) {
		int x;
		scanf("%d", &x);
		printf("%lld\n", ans[x]);
	}
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}

```

---

## 作者：tzl_Dedicatus545 (赞：0)

### Preface

这题好像能做 $O(n\log n)$，Slope Trick 还是太难了。

### Solution

哦首先对于某个集合 $S$，答案是 $\sum_{i \in S} a_i-\min_k{a_i+b_i}$。

那你按照 $a_i+b_i$ 排序，肯定就存在一个分界点 $p$，使得 $\leq p$ 的全选上，$>p$ 的选出 $b_i$ 最小的 $k$ 个。然后你能做 $O(nq\log n)$ 了。

这个东西看起来就一眼凸优化的样子啊！但是他不凸，哦但是你打个表发现转移点单调，决策单调性一下做完了。

$O(n\log^2n)$

---

