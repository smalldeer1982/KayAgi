# Divan and a Cottage

## 题目描述

Divan's new cottage is finally complete! However, after a thorough inspection, it turned out that the workers had installed the insulation incorrectly, and now the temperature in the house directly depends on the temperature outside. More precisely, if the temperature in the house is $ P $ in the morning, and the street temperature is $ T $ , then by the next morning the temperature in the house changes according to the following rule:

- $ P_{new} = P + 1 $ , if $ P < T $ ,
- $ P_{new} = P - 1 $ , if $ P > T $ ,
- $ P_{new} = P $ , if $ P = T $ .

 Here $ P_{new} $ is the temperature in the house next morning.Divan is a very busy businessman, so sometimes he is not at home for long periods and does not know what the temperature is there now, so he hired you to find it. You will work for $ n $ days. In the beginning of the $ i $ -th day, the temperature outside $ T_i $ is first given to you. After that, on the $ i $ -th day, you will receive $ k_i $ queries. Each query asks the following: "if the temperature in the house was $ x_i $ at the morning of the first day, what would be the temperature in the house next morning (after day $ i $ )?"

Please answer all the businessman's queries.

## 说明/提示

Let's look at the first four queries from the example input.

The temperature is $ 50 $ on the first day, $ 50 $ on the second day, and $ 0 $ on the third day.

Note that $ lastans = 0 $ initially.

- The initial temperature of the first query of the first day is $ (1 \, + \, lastans) \bmod (10^9 + 1) = 1 $ . After the first day, the temperature rises by $ 1 $ , because $ 1 < 50 $ . So the answer to the query is $ 2 $ . Then, we set $ lastans = 2 $ .
- The initial temperature of the second query of the first day is $ (2 \, + \, lastans) \bmod (10^9 + 1) = 4 $ . After the first day, the temperature rises by $ 1 $ , because $ 4 < 50 $ . So the answer to the query is $ 5 $ . Then, we set $ lastans = 5 $ .
- The initial temperature of the third query of the first day is $ (3 \, + \, lastans) \bmod (10^9 + 1) = 8 $ . After the first day, the temperature rises by $ 1 $ . So the answer to the query is $ 9 $ . Then, we set $ lastans = 9 $ .
- The initial temperature of the first query of the second day is $ (4 \, + \, lastans) \bmod (10^9 + 1) = 13 $ . After the first day, the temperature rises by $ 1 $ . After the second day, the temperature rises by $ 1 $ . So the answer to the query is $ 15 $ . Then, we set $ lastans = 15 $ .

## 样例 #1

### 输入

```
3
50
3
1 2 3
50
3
4 5 6
0
3
7 8 9```

### 输出

```
2
5
9
15
22
30
38
47
53```

## 样例 #2

### 输入

```
4
728
3
859 1045 182
104
1
689
346
6
634 356 912 214 1 1
755
3
241 765 473```

### 输出

```
858
1902
2083
2770
3401
3754
4663
4874
4872
4870
5107
5868
6337```

## 样例 #3

### 输入

```
2
500000000
3
1000000000 999999999 888888888
250000000
5
777777777 666666666 555555555 444444444 333333333```

### 输出

```
999999999
999999996
888888882
666666656
333333321
888888874
333333317
666666648```

# 题解

## 作者：Tyyyyyy (赞：8)

## CF1614E
### 题意简述
- 有 $n$ 天，每天有一个温度 $T_i$。
- 设当天屋内的温度为 $P$，则在每天温度会发生如下变化：

$$P=\left\{
\begin{aligned}
P+1 & & {P < T_i}\\
P-1 & & {P > T_i}\\
P & & {P = T_i}
\end{aligned}
\right.
$$

- 每天有 $k_i$ 个询问，问你如果第一天早上屋内的温度为 $t_{i,j}$，则到现在屋内的温度是多少。
- $1 \leq n,\sum k_i \leq 2 \times 10^5,0 \leq T_i,x_i \leq 10^9$。
- 强制在线。

### 分析
本题有一种线段树二分的做法，可以参见其他题解。

这里介绍另一种做法：直接用线段树维护原来温度在区间 $[l,r]$ 时实际温度的最大值和最小值。

在更新一个 $T_i$ 时，我们讨论当前节点维护的信息与 $T_i$ 的关系。

假设 $tree[rt].max<T_i$：直接对 $rt$ 维护的区间进行区间加 $1$ 的操作即可。

假设 $tree[rt].min>T_i$：直接对 $rt$ 维护的区间进行区间减 $1$ 的操作即可。

假设 $tree[rt].max=tree[rt].min=T_i$：直接返回即可。

可以发现上述三种情况已经覆盖了所有节点。

所以我们直接动态开点，按上述方式维护即可。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int mod=1e9+1; 
int n,tot;
struct SegmentTree
{
	int ls,rs,mx,mn,laz;
	#define ls(i) tree[i].ls
	#define rs(i) tree[i].rs
	#define mx(i) tree[i].mx
	#define mn(i) tree[i].mn
	#define laz(i) tree[i].laz
}tree[30000010];
inline int New(int mn,int mx){tree[++tot]=(SegmentTree){0,0,mx,mn,0};return tot;}
inline void pushup(int rt)
{
	mx(rt)=max(mx(ls(rt)),mx(rs(rt)));
	mn(rt)=min(mn(ls(rt)),mn(rs(rt)));
}
inline void pushdown(int rt)
{
	if(!laz(rt))return;
	int l=ls(rt),r=rs(rt);
	mx(l)+=laz(rt),mn(l)+=laz(rt),laz(l)+=laz(rt);
	mx(r)+=laz(rt),mn(r)+=laz(rt),laz(r)+=laz(rt);
	laz(rt)=0; 
}
inline void upd(int rt,int l,int r,int op)
{
	if(mx(rt)<op){mx(rt)++,mn(rt)++,laz(rt)++;return;}
	if(mn(rt)>op){mx(rt)--,mn(rt)--,laz(rt)--;return;}
	if(mx(rt)==op&&mn(rt)==op)return;
	int mid=(l+r)>>1;
	if(!ls(rt))ls(rt)=New(l,mid);
	if(!rs(rt))rs(rt)=New(mid+1,r);
	pushdown(rt);
	upd(ls(rt),l,mid,op),upd(rs(rt),mid+1,r,op);
	pushup(rt);
}
inline int query(int rt,int l,int r,int t)
{
	if(l==t&&r==t){return mx(rt);}
	int mid=(l+r)>>1;
	if(!ls(rt))ls(rt)=New(l,mid);
	if(!rs(rt))rs(rt)=New(mid+1,r);
	pushdown(rt);
	if(t<=mid)return query(ls(rt),l,mid,t);
	return query(rs(rt),mid+1,r,t);
}
template<typename T>inline void read(T &x) 
{
	x=0;int f=1;char c=getchar();
	for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
	x*=f;
}
int main()
{
	read(n);
	int lst=0,rt=New(0,mod-1);
	while(n--)
	{
		int t,k,x;
		read(t);read(k);
		upd(1,0,mod-1,t);
		for(int i=1;i<=k;i++)
		{
			read(x);x=(x+lst)%mod;
			lst=query(1,0,mod-1,x);
			printf("%d\n",lst);
		}
	}
	return 0;
}
```

---

## 作者：Presentation_Emitter (赞：4)

~~个人认为这场 E 比 C 简单，但还是太菜了，没做出来~~

考虑维护每次插入一个气温后，所有初始的室温变化后的结果。其显然单调不减。建一棵 $[-1,MaxT+1]$ （规避边界特判）范围的动态开点值域线段树维护之。

每次插入一个气温 $T_i$ 后，在线段树上二分以得到变化后的室温为 $T_i$ 的区间 $[l,r]$，之后 $[-1,l)$ 区间 $+1$，$(r,MaxT+1]$ 区间 $-1$ 即可。

~~赛时没 A 是边界问题~~

附上~~极其丑陋的~~修改后赛时代码：

```cpp
ll T,tp,k,x,lans;
cst ll lim=12000005;
cst ll ar=1000000001;
cst ll ra=-1;
int del[lim],led[lim],tg[lim],ls[lim],rs[lim],cnt;
il int newp(int l,int r)
{++cnt;ls[cnt]=rs[cnt]=tg[cnt]=0;del[cnt]=r;led[cnt]=l;ret cnt;}
il void pushup(int i){del[i]=del[rs[i]];led[i]=led[ls[i]];}
il void pushdown(int i,int l,int r)
{
	ll mid=(l+r)>>1;
	if(!ls[i])ls[i]=newp(l,mid);
	if(!rs[i])rs[i]=newp(mid+1,r);
	del[ls[i]]+=tg[i],del[rs[i]]+=tg[i];
	led[ls[i]]+=tg[i],led[rs[i]]+=tg[i];
	tg[ls[i]]+=tg[i],tg[rs[i]]+=tg[i];
	tg[i]=0;
}
il void modify(int lt,int rt,int x,int i=1,int l=ra,int r=ar)
{
	if(l>r||l>rt||r<lt)ret;
	if(l>=lt&&r<=rt)ret del[i]+=x,led[i]+=x,tg[i]+=x,void();
	pushdown(i,l,r);ll mid=(l+r)>>1;
	if(lt<=mid)modify(lt,rt,x,ls[i],l,mid);
	if(rt>mid)modify(lt,rt,x,rs[i],mid+1,r);
	pushup(i);
}
il ll query(int p,int i=1,int l=ra,int r=ar)
{
	if(l>r||l>p||r<p)ret 0;
	if(l==p&&r==p)ret del[i];
	pushdown(i,l,r);ll mid=(l+r)>>1,res;
	if(p<=mid)res=query(p,ls[i],l,mid);
	else res=query(p,rs[i],mid+1,r);
	pushup(i);ret res;
}
il ll getpos(int v,int i=1,int l=ra,int r=ar)
{
	if(l==r)ret l;
	pushdown(i,l,r);ll mid=(l+r)>>1,res;
	if(del[ls[i]]>=v)res=getpos(v,ls[i],l,mid);
	else res=getpos(v,rs[i],mid+1,r);
	pushup(i);ret res;
}
il ll getpo5(int v,int i=1,int l=ra,int r=ar)
{
	if(l==r)ret r;
	pushdown(i,l,r);ll mid=(l+r)>>1,res;
	if(led[rs[i]]<=v)res=getpo5(v,rs[i],mid+1,r);
	else res=getpo5(v,ls[i],l,mid);
	pushup(i);ret res;
}
cst ll ycz=1000000001;
int main()
{
	T=rd();newp(0,ar);//cerr<<sizeof(del)/1048576.0*5<<endl;
	for(int cD=1;cD<=T;++cD)
	{
		tp=rd();cst ll pos=getpos(tp),po5=getpo5(tp);
		modify(ra,pos-1,1);modify(po5+1,ar,-1);
		k=rd();
		while(k --> 0)
		{
			x=(lans+rd())%ycz;lans=query(x);
			prt(lans);
		}
	}
	ret 0;
}
```

---

## 作者：Starlight237 (赞：2)

简要题意：

> 给定一个用整数表示的操作序列 $A=\{T_i\}$，操作 $T_i$ 作用在 $x$ 上时，会使得 $x$ 向 $T_i$ 靠近一位。具体地，若 $x<T_i$，则 $x\rightarrow x+1$，若 $x>T_i$，则 $x\rightarrow x-1$，否则 $x$ 不变。我们记 $f_A(x)$ 表示 $x$ 依次被 $A$ 中所有操作作用后的结果。共有 $n$ 次查询，第 $i$ 次会在 $A$ 中 `push_back` 一个新的 $T_i$，并进行 $k_i$ 次询问，每次询问给出一个 $x$，求 $f_A(x)$ 的值。数据范围见原题面。

用 $[0,maxV]$ 的动态开点权值线段树来维护 $f_A(x)$。考虑对 $A$ `push_back` 一个 $T$ 时，各 $f_A(x)$ 将如何变化：对于 $f_A(x)<T$ 的，我们令 $f_A(x)\rightarrow f_A(x)+1$，大于 $T$ 的情况同理。我们下面给出一个引理：

**Lemma.** $f_A(x)$ 关于 $x$ 单调不降。  
证明：对于 $y<x$，如果 $T_i\le x$，那么 $T_i$ 作用在 $y$ 上之后 $y$ 依然不超过 $x$。而如果 $T_i>x$，那么 $x,y$ 会同时增加。因此任意一次操作都不可能使得当前小的数反超当前大的数，得证。

根据如上的引理，满足 $f_A(x)<T$ 和 $f_A(x)>T$ 的分别是一段前缀和后缀。通过线段树上二分找出对应的前缀和后缀，区间加即可维护。询问 $f_A(x)$ 就是单点查询。

由于我的实现不优美，需要特判（代码中会说明）。~~赛时也因为这个特判错失了 $E$ 题还吃了一堆罚时。~~ 但是这个特判我觉得是可以 `hack` 的：只需要构造恰好需要把 $f_A(0)$ 加一的数据即可。不知道为啥没有人卡这个。如果觉得不保险可以每次单点查询一下 $f_A(0)$ 和 $f_A(maxV)$ 进一步特判，这样正确性就一定不会有问题。

upd : 已经被 hack 了，因此代码已经加上了上述的特判。

注意：由于历史遗留问题，请注意代码中的注释 ``` mod - 1 是 maxV, md 才是真正的模数。```

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace io {
#define BUFS 100000
	char in[BUFS], *p = in, *pp = in;
#define gc (p == pp && (pp = (p = in) + fread(in, 1, BUFS, stdin), p == pp) ? EOF : *p++)
	inline int read() {
		int x = 0; char ch, f = 0;
		while (!isdigit(ch = gc)) f |= ch == '-';
		while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = gc;
		return f ? -x : x;
	}
}
#define rd io :: read
const int N = 2e5 + 10, mod = 2e9 + 1, md = 1e9 + 1; // mod - 1 是 maxV, md 才是真正的模数。
int n, t[N], ptr;
struct Node {
	int mi, mx, tag, ls, rs;
} seg[10000010];
inline void pushup(int k) {
	seg[k].mi = min(seg[seg[k].ls].mi, seg[seg[k].rs].mi);
	seg[k].mx = max(seg[seg[k].ls].mx, seg[seg[k].rs].mx);
}
inline void pushdown(int k, int l, int r) {
	if (seg[k].tag) {
		int mid = (long long)l + r >> 1;
		if (!seg[k].ls) seg[k].ls = ++ptr, seg[ptr].mi = l, seg[ptr].mx = mid;
		if (!seg[k].rs) seg[k].rs = ++ptr, seg[ptr].mi = mid + 1, seg[ptr].mx = r;
		seg[seg[k].ls].mx += seg[k].tag, seg[seg[k].ls].mi += seg[k].tag, seg[seg[k].ls].tag += seg[k].tag;
		seg[seg[k].rs].mx += seg[k].tag, seg[seg[k].rs].mi += seg[k].tag, seg[seg[k].rs].tag += seg[k].tag;
		seg[k].tag = 0;
	}
}
void modify(int&k, int l, int r, int ql, int qr, int v) {
	if (!k) k = ++ptr, seg[k].mi = l, seg[k].mx = r;
	if (ql <= l && r <= qr) {
		seg[k].mi += v, seg[k].mx += v, seg[k].tag += v;
		return ;
	}
	int mid = (long long)l + r >> 1;
	pushdown(k, l, r);
	if (ql <= mid) modify(seg[k].ls, l, mid, ql, qr, v);
	if (mid  < qr) modify(seg[k].rs, mid + 1, r, ql, qr, v);
	pushup(k);
}
int query1(int k, int l, int r, int v) {
	if (l == r || seg[k].mi == seg[k].mx && seg[k].mi < v) return r;
	int mid = (long long)l + r >> 1;
	if (!seg[k].ls) seg[k].ls = ++ptr, seg[ptr].mi = l, seg[ptr].mx = mid;
	if (!seg[k].rs) seg[k].rs = ++ptr, seg[ptr].mi = mid + 1, seg[ptr].mx = r;
	pushdown(k, l, r);
	if (seg[seg[k].rs].mi < v) return query1(seg[k].rs, mid + 1, r, v);
	return query1(seg[k].ls, l, mid, v);
}
int query2(int k, int l, int r, int v) {
	if (seg[k].mi == seg[k].mx && seg[k].mx > v) return l;
	int mid = (long long)l + r >> 1;
	if (!seg[k].ls) seg[k].ls = ++ptr, seg[ptr].mi = l, seg[ptr].mx = mid;
	if (!seg[k].rs) seg[k].rs = ++ptr, seg[ptr].mi = mid + 1, seg[ptr].mx = r;
	pushdown(k, l, r);
	if (seg[seg[k].ls].mx > v) return query2(seg[k].ls, l, mid, v);
	return query2(seg[k].rs, mid + 1, r, v);
}
int query(int k, int l, int r, int p) {
	if (l == r) return seg[k].mi;
	int mid = (long long)l + r >> 1;
	pushdown(k, l, r);
	if (!seg[k].ls) seg[k].ls = ++ptr, seg[ptr].mi = l, seg[ptr].mx = mid;
	if (!seg[k].rs) seg[k].rs = ++ptr, seg[ptr].mi = mid + 1, seg[ptr].mx = r;
	return p <= mid ? query(seg[k].ls, l, mid, p) : query(seg[k].rs, mid + 1, r, p);
}
int main() {
	n = rd();
	int lstans = 0, root = ptr = 1;
	seg[1].mi = 0, seg[1].mx = mod - 1;
	for (int i = 1; i <= n; ++i) {
		t[i] = rd();
		int L = query1(1, 0, mod - 1, t[i]);
		int R = query2(1, 0, mod - 1, t[i]);
		if (L) modify(root, 0, mod - 1, 0, L, 1);
		if (R < mod - 1) modify(root, 0, mod - 1, R, mod - 1, -1);
        // 上面两句就是特判，因为如果没有需要加的数，则 L 将返回 0，这时区间加 [0,L] 就会发生错误，0 被多加了一次。R 的特判同理。
                if (L == 0 && query(1, 0, mod - 1, L) < t[i]) modify(root, 0, mod - 1, 0, L, 1);
		if (R == mod - 1 && query(1, 0, mod - 1, R) > t[i]) modify(root, 0, mod - 1, R, mod - 1, -1);
		int k = rd();
		for (int j = 1; j <= k; ++j) {
			int x = (rd() + lstans) % md;
			printf("%d\n", lstans = query(1, 0, mod - 1, x) % md);
		}
	}
	return 0;
}
```

---

## 作者：sleepy66 (赞：1)

~~题目的翻译是真的离谱。~~

题意已经有很多大佬说过了，就不过多赘述，直接讲解法。

这题可以用线段树做，每一个节点维护的是初始温度在一段区间内时，最终温度的最大值和最小值。

考虑到值域很大，我们可以采用动态开点。

维护区间最值很容易，直接套模板即可。

现在最大的问题是，当过了一天后，如何用新的温度 $T$ 去更新线段树呢。可以看到，我的 update 的返回条件和往常不同。我们可以分类讨论：

1. 当区间最大值都小于 $T$ 时，意味着这个区间内的温度都要升高一度。

2. 当区间最小值都大于 $T$ 时，这个区间内的温度都要下降一度。

3. 当区间的最终温度都是 $T$ 时，$T$ 不会对该区间内的值造成影响，直接返回即可。

最后查询其实也是模板。

这样我们就可以愉快地完成这题了。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ls(x) tree[x].ls
#define rs(x) tree[x].rs
#define maxn(x) tree[x].maxn
#define minn(x) tree[x].minn
#define tag(x) tree[x].tag
using namespace std;
#define N 200010
const int mod=1e9+1;
struct node{
	int maxn,minn,tag,ls,rs;
}tree[100*N];
int n,t,q,x,tot=1,rt=1,lastans;
void pushdown(int rt){//下传标记
	tag(ls(rt))+=tag(rt);
	tag(rs(rt))+=tag(rt);
	maxn(ls(rt))+=tag(rt);
	maxn(rs(rt))+=tag(rt);
	minn(ls(rt))+=tag(rt);
	minn(rs(rt))+=tag(rt);
	tag(rt)=0;
	return;
}
int create(int l,int r){//动态开点
	tree[++tot]={r,l,0,0,0};
	return tot;
}
void update(int l,int r,int x,int &rt){//更新
	if(maxn(rt)<x){maxn(rt)++;minn(rt)++;tag(rt)++;return;}
	if(minn(rt)>x){maxn(rt)--;minn(rt)--;tag(rt)--;return;}
	if(maxn(rt)==x&&minn(rt)==x){return;}
	int mid=(l+r)>>1;
	if(!ls(rt))ls(rt)=create(l,mid);
	if(!rs(rt))rs(rt)=create(mid+1,r);
	pushdown(rt);
	update(l,mid,x,ls(rt));
	update(mid+1,r,x,rs(rt));
	maxn(rt)=max(maxn(ls(rt)),maxn(rs(rt)));
	minn(rt)=min(minn(ls(rt)),minn(rs(rt)));
}
int query(int l,int r,int x,int &rt){//单点查询
	if(l==r){
		return maxn(rt);
	}
	int mid=(l+r)>>1;
	if(!ls(rt))ls(rt)=create(l,mid);
	if(!rs(rt))rs(rt)=create(mid+1,r);
	pushdown(rt);
	if(x<=mid)return query(l,mid,x,ls(rt));
	else return query(mid+1,r,x,rs(rt));
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	maxn(1)=mod-1;
	minn(1)=0;
	while(n--){
		cin>>t>>q;
		update(0,mod-1,t,rt);
		while(q--){
			cin>>x;
			x=(x+lastans)%mod;
			lastans=query(0,mod-1,x,rt);
			cout<<lastans<<'\n';
		}
	}
	return 0;
}
```


---

## 作者：Galois_Field_1048576 (赞：0)

如果你不想写数据结构，怎么办？不用怕，PBDS 拯救你！本题的核心是灵活运用

```cpp
using ExtSeg = tree<int, null_type, less_equal<int>, rb_tree_tag,
                    tree_order_statistics_node_update>;
```
的 `order_of_key`。

考虑函数 $f_x(y) = y + \mathrm{sign}(y-x)$，表示外部温度为 $x$，内部温度为 $y$ 时下一天的内部温度。我们对于某一个 $f_x(y) = z$，考虑 $z \mapsto y$ 的映射。这对于几乎所有数都是能做到的，除了 $z = x$ 时，$y$ 可以是 $x-1,x,x+1$。令 $S = \{x,x+1\}$。那么，$f_x(y) = y + 1 - (S\ \text{中}<y+1\ \text{的元素个数})$。

我们把所有的 $+ 1$ 归结到一起，所有的 $S$ 中 $< y + 1$ 的元素个数归结到一起，这样我们发现若 $S_\infty$ 适当选取，那么
$$
f_{x_1,\dots,x_n}(y) = y + n - (S_\infty\ \text{中}<y+1\ \text{的元素个数}).
$$
这就是 GNU PBDS 维护的一个扩展 set 的功能。你可以将它视作一个 multiset，但是支持查询一个 key 的排名。

假设在前 $i$ 天，我们搞出的 $S$ 集合为 $S_i$。$i + 1$ 天，温度为 $t$。那么，$f_{x_1,\dots,x_n}(t_0) = t$ 和 $f_{x_1,\dots,x_n}(t_0) = t + 1$ 这两个 $t_0$ 要被排除。简记 $g := f_{x_1,\dots,x_n}$。那么，我们查询：
$$
p = \max_{g(x) < t} x, q = \max_{g(x) \le t} x,
$$
不难直接按定义证明恰好 $S_{i +1} = S_i \sqcup \{p, q\}$ 时满足条件。按照这个过程写代码即可。

```cpp
#include <bits/extc++.h>
using namespace __gnu_pbds;

const st V = 1e9;

using ExtSeg = tree<int, null_type, less_equal<int>, rb_tree_tag,
                    tree_order_statistics_node_update>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    i64 lastans = 0;
    ExtSeg S;
    for (auto i : range(n)) {
        auto query = [&](int x) {
            st ans = 0;
            for (st j : range(30, 0, -1))
                ans +=
                    ((1 << j) + i + ans <= x + S.order_of_key((1 << j) + ans))
                    << j;
            return ans;
        };

        i64 t, k;
        cin >> t >> k;
        int p = query(t), q = query(t + 1);
        S.insert(p), S.insert(q);
        for (auto __ : range(k)) {
            i64 x;
            cin >> x, x = (x + lastans) % (V + 1), x++;
            cout << (lastans = i + x - S.order_of_key(x)) << "\n";
        }
    }
}
```

---

## 作者：FLY_lai (赞：0)

# 【题意】

- 有 $n$ 天，每天有一个温度 $T_i$。
- 设当天屋内的温度为 $P$，则在每天温度会发生如下变化：

$$
P=\left\{
\begin{aligned}
P+1 & & {P < T_i}\\
P-1 & & {P > T_i}\\
P & & {P = T_i}
\end{aligned}
\right.
$$

- 每天有 $k_i$ 个询问，问你如果第一天早上屋内的温度为 $t_{i,j}$，则到现在屋内的温度是多少。
- $1 \leq n,\sum k_i \leq 2 \times 10^5,0 \leq T_i,x_i \leq 10^9$。
- 强制在线。

# 【题解】

1. 善用 DS：对每个位置维护答案！**就算位置个数有 $10^9$ 级别，相信动态开点线段树**！
2. 势能线段树剪枝：考虑 $min,max$ 的差距（尽管这题没用）。
3. 线段树最本质的复杂度分析：每层只有常数个区间向下递归。

容易想到要开一个 DS，位置 $i$ 记录如果初始室温 $=i$，现在室温多少。

因为位置有 $10^9$ 个，应该就是动态开点线段树了。

初始情况，叶子 $i$ 记录的温度为 $i$。接下来考虑怎么修改。考虑对于一个区间遇到了气温 $T$ 会怎么变。

**技巧：记录最值**。对每个区间记录区间内的最大/最小值为 $mx,mn$。

- 若 $T<mn$，应该区间减一。打标记。

- 若 $T>mx$，应该区间加一。打标记。

- 若 $T=mn=mx$，直接返回。

- 否则，暴力递归。

怎么分析这个复杂度？

一开始本来想用势能分析：定义结点 $x$ 的势能 $\phi(x)=mx-mn$，每次暴力递归必然使 $\phi(x)$ 减少。然后就发现总势能高达 $10^9\log 10^9$ ……

回归线段树复杂度分析的原点：我们说明每一层只有常数个结点被向下递归。

证明：

记当前修改的气温为 $T$。考虑当前层某个结点 $x$ 被访问了，最值为 $[mn,mx]$。

一个容易注意到的事实是：当前室温关于初始室温单调不降。所以 $x$ 左侧的结点室温都 $\le mn$，$x$ 右侧的结点室温都 $\ge mx$。

因为 $x$ 被访问了，所以应有 $mn<mx,T\in [mn,mx]$。

- 若 $mn<T<mx$，显然 $T$ 不属于其他结点。只有一个结点递归。

- 若 $T=mn$，显然 $T$ 不属于 $x$ 右侧的结点。考虑 $x$ 左侧第一个最大值不等于最小值（包含至少两种室温）的结点 $y$。因为 $y$ 在 $x$ 左侧，所以 $mn_y<mx_y\le mn_x=T$，所以 $y$ 左侧结点的最大值小于等于 $mn_y$，也就小于 $T$，因此不可能包含 $T$。因此除了 $x$ 以外只有 $y$ 有可能向下递归。至多两个结点递归。

- 若 $T=mx$，类似。至多两个结点递归。

综上所述，每一层至多递归两个结点，于是每一层至多访问 $4$ 个结点，因此单次修改复杂度是 $O(\log 10^9)$ 的。所以总复杂度 $O(q\log 10^9)$。

---

当然，还有暴力一些的方法：因为室温单调不减，可以直接二分出会变化的区间，然后也变成简单的前缀加、后缀减。

```cpp
#include <bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;

struct Node {
	int mn, mx;
	Node(){}
	Node(int l, int r) {
		mn = l, mx = r;
	}
};
Node operator+(Node a, int b) {
	a.mn += b;
	a.mx += b;
	return a;
}
const int M = 1e7 + 5; 

int rt, sz = 0;
int ls[M], rs[M], tag[M];
Node val[M];

int newNode(int l, int r) {
	sz++;
	tag[sz] = 0;
	val[sz] = Node(l, r);
	return sz;
}
void pushup(int x) {
	val[x].mn = val[ls[x]].mn;
	val[x].mx = val[rs[x]].mx;
}
void pushdown(int x, int lx, int rx) {
	if (!tag[x])
		return ;
	int m = (lx + rx) / 2;
	if (!ls[x])
		ls[x] = newNode(lx, m - 1);
	if (!rs[x])
		rs[x] = newNode(m, rx - 1);
	
	val[ls[x]] = val[ls[x]] + tag[x];
	tag[ls[x]] += tag[x];
	val[rs[x]] = val[rs[x]] + tag[x];
	tag[rs[x]] += tag[x];
	tag[x] = 0;
}
void mdf(int &x, int lx, int rx, int v) {
	if (!x)
		x = newNode(lx, rx - 1);
	if (v < val[x].mn) {
		val[x] = val[x] + -1;
		tag[x]--;
		return ;
	}
	if (v > val[x].mx) {
		val[x] = val[x] + 1;
		tag[x]++;
		return ;
	}
	if (val[x].mn == val[x].mx)
		return ;
	int m = (lx + rx) / 2;
	pushdown(x, lx, rx);
	mdf(ls[x], lx, m, v);
	mdf(rs[x], m, rx, v);
	pushup(x);
}
int qry(int x, int lx, int rx, int p) {
	if (!x)
		x = newNode(lx, rx - 1);
	if (lx + 1 == rx)
		return val[x].mn;
	int m = (lx + rx) / 2;
	pushdown(x, lx, rx);
	if (p < m)
		return qry(ls[x], lx, m, p);
	return qry(rs[x], m, rx, p);
}

int n, lstans = 0;

int main() {
//	freopen("1.in", "r", stdin);
//	freopen("1.out", "w", stdout);
	rt = newNode(0, 1000000000);
	cin >> n;
	
	for (int i = 1, T; i <= n; i++) {
		scanf("%d", &T);
		mdf(rt, 0, 1000000001, T);
		
		int k;
		scanf("%d", &k);
		for (int j = 1, x; j <= k; j++) {
			scanf("%d", &x);
			x = (1ll * x + lstans) % 1000000001;
			lstans = qry(1, 0, 1000000001, x);
			printf("%d\n", lstans);
		}
	}
	return 0;
}
```

---

## 作者：L0vely_NaiL0ng (赞：0)

用线段树维护下标为初始温度时现在的温度为多少。维护一个 $maxn$ 和一个 $minn$ 分别表示当前区间现在温度最大值和最小值。

今天的气温为 $t$，线段树遍历下去：

- Case 1：$maxn < t$，这个区间全体加 $1$，返回。

- Case 2：$minn > t$，这个区间全体减 $1$，返回。

- Case 3：$minn = t = maxn$，直接返回。

- Case 4：剩余情况递归到左右儿子。

这个做法看着很暴力，我们来分析一下复杂度。首先容易知道现在温度和初始温度有单调性，所以现在温度相同且等于 $t$ 的一定是一段连续的区间（Case 3），同样的，Case 1 和 Case 2 也分别是连续的区间，本质上上面遍历的操作可以拆分成 $3$ 次对于 $3$ 段不相交且并集为 $[1, V]$ 的连续区间的修改操作，复杂度即为 $O(\log V)$。总复杂度 $O(n \log V)$，其中 $V = 10^9$。

```
#include <bits/stdc++.h>
#define For(i, x, y) for (int i = (x); i <= (y); i++)
#define lb lower_bound
#define cmax(x, y) x = max(x, y)
#define mid ((l + r) >> 1)
#define foR(i, x, y) for (int i = (x); i >= (y); i--)
using namespace std;
const int N = 2e5 + 5, M = 5e7;
bool st;
int n, tot = 1;
struct node {
	int x, y, ls, rs, tag;
} t[M];
void update(int p) {
	t[p].x = min(t[t[p].ls].x, t[t[p].rs].x);
	t[p].y = max(t[t[p].ls].y, t[t[p].rs].y);
}
void pushdown(int p) {
	if (!t[p].tag) return;
	int ls = t[p].ls, rs = t[p].rs, v = t[p].tag;
	t[ls].x += v; t[ls].y += v; t[ls].tag += v;
	t[rs].x += v; t[rs].y += v; t[rs].tag += v;
	t[p].tag = 0;
}
void change(int l, int r, int p, int v) {
	if (t[p].y < v) {
		t[p].x ++; t[p].y ++; t[p].tag ++; return; 
	}
	if (t[p].x > v) {
		t[p].x --; t[p].y -- ; t[p].tag --; return;
	}
	if (t[p].x == v && t[p].y == v) return;
	if (!t[p].ls) {
		t[p].ls = ++tot; t[t[p].ls] = {l, mid, 0, 0, 0};
	}
	if (!t[p].rs) {
		t[p].rs = ++tot; t[t[p].rs] = {mid + 1, r, 0, 0, 0};
	}
	pushdown(p);
	change(l, mid, t[p].ls, v); change(mid + 1, r, t[p].rs, v);
	update(p);
}
int query(int l, int r, int p, int x) {
	if (l == r) return t[p].x;
	if (!t[p].ls) {
		t[p].ls = ++tot; t[t[p].ls] = {l, mid, 0, 0, 0};
	}
	if (!t[p].rs) {
		t[p].rs = ++tot; t[t[p].rs] = {mid + 1, r, 0, 0, 0};
	}
	pushdown(p);
	if (x <= mid) return query(l, mid, t[p].ls, x);
	return query(mid + 1, r, t[p].rs, x);
}
void solve() {
	cin >> n; int lst = 0; t[1] = {0, 1000000000, 0, 0, 0};
	while (n--) {
		int t, q, x; cin >> t >> q;
		change(0, 1e9, 1, t);
		while (q--) {
			cin >> x; x = (x + lst) % (1000000001);
			cout << (lst = query(0, 1e9, 1, x)) << endl;
		}
	}
	return;
}
bool ed;
signed main() {
	//freopen("1.in", "r", stdin);
	//printf("%.3lf MB\n", (&ed - &st) / 1048576.0);
	solve();
	//cout << 1e3 * clock() / CLOCKS_PER_SEC << "ms";
	return 0;
}
```

---

## 作者：orz_z (赞：0)

## 题目大意

给定 $n$ 天的气温 $T_i$，设第 $i$ 天温度为 $P$，则第 $i+1$ 天的温度为：

* $P+1 ( P < T_i)$

* $P-1 ( P >T_i)$

* $P(P = T_i)$

对第 $i$ 天有 $k_i$ 个询问，问若第 $0$ 天的温度为 $x$ ，那么第 $i$ 天的温度是多少。

强制在线。

## 解题思路

显然，所有初始的室温变化后的结果满足单调。

那用一棵动态开点值域线段树维护所有初始的室温变化后的结果即可。

具体地，每次插入一个气温 $T_i$ 后，在线段树上二分以得到变化后的室温为 $T_i$ 的区间 $\left[l,r\right]$，之后 $[-1,l)$ 区间 $+1$，$\left(r,MaxT+1\right]$ 区间 $-1$ 即可。

时间复杂度 $\mathcal{O}(n \log w)$，其中 $w$ 为值域。

## CODE

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

inline ll read()
{
    ll x = 0, f = 1;
    char c = getchar();
    while ((c < '0' || c > '9') && (c != '-'))
        c = getchar();
    if (c == '-')
        f = -1, c = getchar();
    while (c >= '0' && c <= '9')
        x = x * 10 + c - '0', c = getchar();
    return x * f;
}

const int N = 2e5 + 10, mod = 1e9 + 1;

int n, m;

const int M = 4e7 + 10;

int tot, mn[M], mx[M], tag[M], ls[M], rs[M];

inline int New(int l, int r)
{
    ++tot, mn[tot] = l, mx[tot] = r;
    return tot;
}

inline void upd(int u, int x)
{
    mn[u] += x, mx[u] += x, tag[u] += x;
}

inline void push_down(int u, int l, int r, int mid)
{
    if (!tag[u])
        return;
    if (!ls[u])
        ls[u] = New(l, mid);
    if (!rs[u])
        rs[u] = New(mid + 1, r);
    upd(ls[u], tag[u]), upd(rs[u], tag[u]);
    tag[u] = 0;
}

inline void update(int &u, int l, int r, int ql, int qr, int x)
{
    if (ql > qr)
        return;
    if (!u)
        u = New(l, r);
    if (l >= ql && r <= qr)
    {
        upd(u, x);
        return;
    }
    int mid = l + r >> 1;
    push_down(u, l, r, mid);
    if (ql <= mid)
        update(ls[u], l, mid, ql, qr, x);
    if (qr > mid)
        update(rs[u], mid + 1, r, ql, qr, x);
    mn[u] = min(!ls[u] ? l : mn[ls[u]], !rs[u] ? mid + 1 : mn[rs[u]]);
    mx[u] = max(!ls[u] ? mid : mx[ls[u]], !rs[u] ? r : mx[rs[u]]);
}

inline int Findl(int u, int l, int r, int x)
{
    if ((!u ? l : mn[u]) >= x)
        return -1;
    if (l == r)
        return l;
    int mid = l + r >> 1;
    push_down(u, l, r, mid);
    int ret = Findl(rs[u], mid + 1, r, x);
    if (ret != -1)
        return ret;
    return Findl(ls[u], l, mid, x);
}

inline int Findr(int u, int l, int r, int x)
{
    if ((!u ? r : mx[u]) <= x)
        return mod;
    if (l == r)
        return l;
    int mid = l + r >> 1;
    push_down(u, l, r, mid);
    int ret = Findr(ls[u], l, mid, x);
    if (ret != mod)
        return ret;
    return Findr(rs[u], mid + 1, r, x);
}

inline int Query(int u, int l, int r, int ql)
{
    if (l == r)
        return !u ? l : mn[u];
    int mid = l + r >> 1;
    push_down(u, l, r, mid);
    if (ql <= mid)
        return Query(ls[u], l, mid, ql);
    return Query(rs[u], mid + 1, r, ql);
}

signed main()
{
    n = read();
    ll lasans = 0;
    int rt = 0;
    for(int i = 1; i <= n; ++i)
    {
        int x = read();
        int l = Findl(rt, 0, 1e9, x), r = Findr(rt, 0, 1e9, x);
        update(rt, 0, 1e9, 0, l, +1);
        update(rt, 0, 1e9, r, 1e9, -1);
        m = read();
        for(int j = 1; j <= m; ++j)
        {
            int x = (read() + lasans) % mod;
            printf("%lld\n", lasans = Query(rt, 0, 1e9, x));
        }
    }
}
```

---

## 作者：Rushroom (赞：0)

### 思路

我们设如果最开始温度为 $i$，那么第 $j$ 天温度为 $f_{i,j}$。

首先，我们可以发现一个性质：对于 $i,j$ 满足 $i<j$ 那么对于任意 $k$，$f_{i,k}\leq f_{j,k}$。

于是，我们维护每一天的 $f$ 数组，第 $i$ 天，对于每个 $j$，若 $f_{i,j}<T_i$，我们将 $f_{i,j}$ 加上 1，若 $f_{i,j}>T_i$，我们将 $f_{i,j}$ 减去 1。

我们需要一个能支持区间加和单点查询的数据结构。由于 $T_i$ 的范围很大，所以我们需要动态开点线段树，每次二分查询更新的边界。

复杂度为 $O(n \log^2 n)$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define forr(i, a, n) for (int i = a; i <= n; i++)
#define rep(i, n) forr(i, 0, n - 1)
#define repp(i, n) forr(i, 1, n)
#define pb push_back
#define mp make_pair
#define init(a, i) memset(a, i, sizeof(a))
#define fi first
#define se second
#define mod 1000000007
#define MOD 998244353
#define MAXN 1000000000
int T, case_;
int tree[10000007], ls[10000007], rs[10000007], cnt = 2;
int query(int node, int l, int r, int n, int sum)
{
    if (!node)
        return n + sum;
    if (l == r)
        return n + tree[node] + sum;
    int mid = l + r >> 1;
    if (mid >= n)
        return query(ls[node], l, mid, n, sum + tree[node]);
    else
        return query(rs[node], mid + 1, r, n, sum + tree[node]);
}
void add(int node, int l, int r, int L, int R, int val)
{
    if (L <= l && r <= R)
    {
        tree[node] += val;
        return;
    }
    int mid = l + r >> 1;
    if (mid >= L)
    {
        if (!ls[node])
            ls[node] = cnt++;
        add(ls[node], l, mid, L, R, val);
    }
    if (mid < R)
    {
        if (!rs[node])
            rs[node] = cnt++;
        add(rs[node], mid + 1, r, L, R, val);
    }
}
int n, t, q, x, ans = 0;
void solve()
{
    scanf("%d", &n);
    rep(i, n)
    {
        scanf("%d", &t);
        int l = 0, r = MAXN, mid, L = -1, R = -1;
        while (l <= r)
        {
            mid = l + r >> 1;
            if (query(1, 0, MAXN, mid, 0) < t)
                L = mid, l = mid + 1;
            else
                r = mid - 1;
        }
        l = 0, r = MAXN;
        while (l <= r)
        {
            mid = l + r >> 1;
            if (query(1, 0, MAXN, mid, 0) > t)
                R = mid, r = mid - 1;
            else
                l = mid + 1;
        }
        if (L != -1)
            add(1, 0, MAXN, 0, L, 1);
        if (R != -1)
            add(1, 0, MAXN, R, MAXN, -1);
        scanf("%d", &q);
        while (q--)
        {
            scanf("%d", &x);
            x = (x + ans) % (MAXN + 1);
            ans = query(1, 0, MAXN, x, 0);
            printf("%d\n", ans);
        }
    }
}
int main()
{
    T = 1;
    // cin>>T;
    for (case_ = 1; case_ <= T; case_++)
        solve();
    return 0;
}
```


---

