# [ABC343F] Second Largest Query

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc343/tasks/abc343_f

長さ $ N $ の数列 $ A\ =\ (A_1,\ A_2,\ \ldots,\ A_N) $ が与えられます。

$ Q $ 個のクエリが与えられるので、与えられた順に処理してください。各クエリは以下の $ 2 $ 種類のいずれかです。

- タイプ $ 1 $ : `1 p x` の形式で与えられる。 $ A_p $ の値を $ x $ に変更する。
- タイプ $ 2 $ : `2 l r` の形式で与えられる。 $ (A_l,\ A_{l+1},\ \ldots,\ A_r) $ において $ 2 $ 番目に大きい値の**個数**を出力する。より厳密には、$ l\ \leq\ i\ \leq\ r $ を満たす整数 $ i $ であって、$ A_l,\ A_{l+1},\ \ldots,\ A_r $ のうち $ A_i $ より大きい値がちょうど $ 1 $ 種類であるものの個数を出力する。

## 说明/提示

### 制約

- $ 1\ \leq\ N,\ Q\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- タイプ $ 1 $ のクエリにおいて、$ 1\ \leq\ p\ \leq\ N $
- タイプ $ 1 $ のクエリにおいて、$ 1\ \leq\ x\ \leq\ 10^9 $
- タイプ $ 2 $ のクエリにおいて、$ 1\ \leq\ l\ \leq\ r\ \leq\ N $
- タイプ $ 2 $ のクエリが $ 1 $ つ以上存在する
- 入力される値はすべて整数

### Sample Explanation 1

はじめ、$ A\ =\ (3,\ 3,\ 1,\ 4,\ 5) $ です。 $ 1 $ 個目のクエリでは、$ (3,\ 3,\ 1) $ において $ 2 $ 番目に大きい値は $ 1 $ であり、$ 3,\ 3,\ 1 $ の中に $ 1 $ は $ 1 $ 個あるので $ 1 $ を出力します。 $ 2 $ 個目のクエリでは、$ (5) $ において $ 2 $ 番目に大きい値は存在しないので $ 0 $ を出力します。 $ 3 $ 個目のクエリでは、$ A\ =\ (3,\ 3,\ 3,\ 4,\ 5) $ となります。 $ 4 $ 個目のクエリでは、$ (3,\ 3,\ 4) $ において $ 2 $ 番目に大きい値は $ 3 $ であり、$ 3,\ 3,\ 4 $ の中に $ 3 $ は $ 2 $ 個あるので $ 2 $ を出力します。

## 样例 #1

### 输入

```
5 4
3 3 1 4 5
2 1 3
2 5 5
1 3 3
2 2 4```

### 输出

```
1
0
2```

## 样例 #2

### 输入

```
1 1
1000000000
2 1 1```

### 输出

```
0```

## 样例 #3

### 输入

```
8 9
2 4 4 3 9 1 1 2
1 5 4
2 7 7
2 2 6
1 4 4
2 2 5
2 2 7
1 1 1
1 8 1
2 1 8```

### 输出

```
0
1
0
2
4```

# 题解

## 作者：CCX_CoolMint (赞：3)

稍复杂一点点的线段树好题。
#### 简化题意
对于给出的一个数列，进行以下两种操作：

 - 操作1：将数列的第 $p$ 个数字修改为 $x$。
 - 操作2：查询区间 $[l,r]$ 中第二大的数的个数。

#### 思路
上来第一时间想到了线段树，一开始想到的还是正解，后面有一步想错了，赛场没切（悲）。

思路是记录区间的最大值、次大值、最大值个数和次大值个数。下面稍微讲一下实现方法：

 - 该区间的最大值等于其左区间的最大值和右区间最大值的较大值。
 - 可能有人想，那么该区间的次大值是不是就是其左区间的最大值和右区间最大值的较小值呢？

	当然不是，~~我就是这里掉坑的~~，对于一个区间有可能其最大值和次大值都同时存在于左区间或右区间，例如左区间最大值和次大值为 $\{2,1\}$，右区间最大值和次大值为 $\{4,3\}$，那么这里的最大值和次大值都存在于右区间， 不要想当然导致错误。
 
 	并且还有一种特殊情况，例如左区间最大值和次大值为 $\{4,1\}$，右区间最大值和次大值为 $\{4,2\}$，那么它们的次大值是 $2$，这里两个区间都存在最大值，注意最大值和次大值不能相等，需要严格次大。如果你的最大值和次大值相等，请检查你用的方法是否有误。

	这里我用的方法是直接把它们全部取出来存到一个数组内，取出两个不同的数作为该区间最终的最大值和次大值，比较偷懒但是好写。可能有人会想到这里如果不存在次大值怎么办，没关系，直接将 $0$ 作为次大值即可，同时满足输出要求并且不会影响后续操作。

- 最大值个数的存储我比较暴力。直接检查它是否与两个子区间的最大值和次大值相等，如果相等，那么将最大值的个数加上子区间最大值的个数或次大值的个数即可。

- 次大值个数的记录方法同最大值个数的一样。

这里在上传和查询时可能有点复杂，注意实现细节。

对于更改操作，直接进行线段树单点修改操作即可，实现非常简单。

整体时间复杂度为 $O(q\log{n})$。

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,q,a[1001000],l,r,op;
struct node
{
	ll l,r,mx,mx2,mxcnt,mx2cnt;
	node(){mx=mx2=mxcnt=mx2cnt=0;}
}tr[1001000];
ll checkmx(ll rt,ll rt2)
{
	ll sum=0;
	if(tr[rt].mx==tr[rt2].mx) sum+=tr[rt2].mxcnt;
	if(tr[rt].mx==tr[rt2].mx2) sum+=tr[rt2].mx2cnt;
	return sum;
}
ll checkmx2(ll rt,ll rt2)
{
	ll sum=0;
	if(tr[rt].mx2==tr[rt2].mx) sum+=tr[rt2].mxcnt;
	if(tr[rt].mx2==tr[rt2].mx2) sum+=tr[rt2].mx2cnt;
	return sum;
}
void pushup(ll r)
{
	tr[r].mxcnt=tr[r].mx2cnt=0;
	tr[r].mx=max(tr[r*2].mx,tr[r*2+1].mx);
	ll o[10]={0,tr[r*2].mx,tr[r*2].mx2,tr[r*2+1].mx,tr[r*2+1].mx2};
	sort(o+1,o+1+4,greater<ll>());
	if(o[2]!=tr[r].mx) tr[r].mx2=o[2];
	else if(o[3]!=tr[r].mx) tr[r].mx2=o[3];
	else if(o[4]!=tr[r].mx) tr[r].mx2=o[4];
	tr[r].mxcnt+=checkmx(r,r*2),tr[r].mx2cnt+=checkmx2(r,r*2);
	tr[r].mxcnt+=checkmx(r,r*2+1),tr[r].mx2cnt+=checkmx2(r,r*2+1);
}
void build(ll rt,ll l,ll r)
{
	tr[rt].l=l,tr[rt].r=r;
	if(l==r)
	{
		tr[rt].mx=a[l];
		tr[rt].mxcnt=1;
		return;
	}
	ll mid=(l+r)/2;
	build(rt*2,l,mid);
	build(rt*2+1,mid+1,r);
	pushup(rt);
}
void update(ll rt,ll p,ll val)
{
	if(tr[rt].l==tr[rt].r) 
	{
		tr[rt].mx=val;
		tr[rt].mxcnt=1;
		return;
	}
	ll mid=(tr[rt].l+tr[rt].r)/2;
	if(p<=mid) update(rt*2,p,val);
	else update(rt*2+1,p,val);
	pushup(rt);
}
node query(ll rt,ll l,ll r)
{
	if(tr[rt].l>r||tr[rt].r<l) return node();
	if(tr[rt].l>=l&&tr[rt].r<=r) return tr[rt];
	ll mid=(tr[rt].l+tr[rt].r)/2;
	if(l>mid) return query(rt*2+1,l,r); 
	if(r<=mid) return query(rt*2,l,r);
	node tmp,a=query(rt*2,l,r),b=query(rt*2+1,l,r);
	tmp.mx=max(a.mx,b.mx);
	ll o[10]={0,a.mx,a.mx2,b.mx,b.mx2};
	sort(o+1,o+1+4,greater<ll>());
	if(o[2]!=tmp.mx) tmp.mx2=o[2];
	else if(o[3]!=tmp.mx) tmp.mx2=o[3];
	else if(o[4]!=tmp.mx) tmp.mx2=o[4];
	tmp.l=a.l,tmp.r=b.r;
	if(tmp.mx==a.mx) tmp.mxcnt+=a.mxcnt;
	if(tmp.mx==a.mx2) tmp.mxcnt+=a.mx2cnt;
	if(tmp.mx2==a.mx) tmp.mx2cnt+=a.mxcnt;
	if(tmp.mx2==a.mx2) tmp.mx2cnt+=a.mx2cnt;
	if(tmp.mx==b.mx) tmp.mxcnt+=b.mxcnt;
	if(tmp.mx==b.mx2) tmp.mxcnt+=b.mx2cnt;
	if(tmp.mx2==b.mx) tmp.mx2cnt+=b.mxcnt;
	if(tmp.mx2==b.mx2) tmp.mx2cnt+=b.mx2cnt;
	return tmp;
}
int main()
{
	cin>>n>>q;
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
	}
	build(1,1,n);
	while(q--)
	{
		scanf("%lld%lld%lld",&op,&l,&r);
		if(op==1) update(1,l,r);
		else cout<<query(1,l,r).mx2cnt<<endl;
	}
	return 0;
}
```

---

## 作者：Loser_Syx (赞：3)

观前提醒：这是一篇降智做法。

你考虑我们需要求出一个次大值，那我们可以建一棵线段树，记录每个节点 $k$ 的左子树的最大次大值和右子树的最大次大值，因为节点 $k$ 的最大次大值一定是在其子树内某些最大次大值，所以直接合并即可。

考虑得出之后怎么写，我们已经知道了对应的颜色，因为 $a_i \leq 10^9$，同时 $x \leq 10^9$，显然不能直接暴力去搞颜色，但是我们可以将询问离线下来，离散化得到一共 $n+q$ 种颜色。

然后因为需要对 $n+q$ 种颜色开线段树，显然是不现实的，但是发现每次询问和更新只会影响到 $\log (n+q)$ 个节点，可以动态开点。

做完了，复杂度 $O(n \log n)$。

[code](https://atcoder.jp/contests/abc343/submissions/50823768)。

---

## 作者：Otue (赞：2)

线段树做法。可以维护每个区间的最大，次大，最大出现次数，次大出现次数，合并的时候需要一些麻烦操作，不推荐此做法。


分块做法。这道题只求出严格第 $2$ 大数。可以维护每一个块的最大值 $mx_i$，次大值 $mn_i$。定义 $cnt_{i,j}$ 表示数 $i$ 再第 $j$ 个块的出现次数。

对于修改操作 $a_x=v$：暴力修改 $a_x$，再重新更新一遍 $x$ 所属的块的最大，次大。复杂度 $O(\sqrt n)$。

```cpp
void push_up(int x) {
	mx[x] = mi[x] = 0;  // 必须要清空
	for (int j = lx[x]; j <= rx[x]; j++) mx[x] = max(mx[x], a[j]);
	for (int j = lx[x]; j <= rx[x]; j++) {
		if (a[j] != mx[x]) mi[x] = max(mi[x], a[j]);
	}
}
```

对于查询操作 $[l,r]$：先利用 $mx_i$ 求出 $[l,r]$ 的最大值，再用这个最大值去寻找次大值。再用次大值去找次大值出现次数。复杂度 $O(\sqrt n)$。

注意事项：数的值域比较大，可以离散化！

```cpp
const int N = 4e5 + 5, sq = 600;
// sq 为块长，因为 cnt 数组的空间为 n*n/sq，所以可以稍稍将块长调大。（不过在 atcoder 上不怕炸空间）
int n, q, a[N], b[N], tot;
int op[N], l[N], r[N], cnt[N][420];
int mx[N], mi[N], lx[N], rx[N], bel[N], idx;

int main() {
	cin >> n >> q;
	for (int i = 1; i <= n; i++) cin >> a[i], b[++tot] = a[i];
	for (int i = 1; i <= q; i++) {
		cin >> op[i] >> l[i] >> r[i];
		if (op[i] == 1) b[++tot] = r[i];
	} 
	sort(b + 1, b + tot + 1);
	tot = unique(b + 1, b + tot + 1) - b - 1;
	for (int i = 1; i <= n; i++) a[i] = lower_bound(b + 1, b + tot + 1, a[i]) - b; 
	for (int i = 1; i <= q; i++) {
		if (op[i] == 1) r[i] = lower_bound(b + 1, b + tot + 1, r[i]) - b;
	}
	for (int i = 1; i <= n / sq; i++) lx[i] = (i - 1) * sq + 1, rx[i] = i * sq;
	idx = n / sq;
	if (n % sq) idx++, lx[idx] = rx[idx - 1] + 1, rx[idx] = n;
	for (int i = 1; i <= idx; i++) {
		for (int j = lx[i]; j <= rx[i]; j++) bel[j] = i;
	}
	for (int i = 1; i <= idx; i++) { // 先将本来的信息处理好
		for (int j = lx[i]; j <= rx[i]; j++) mx[i] = max(mx[i], a[j]), cnt[a[j]][i]++;
		for (int j = lx[i]; j <= rx[i]; j++) {
			if (a[j] != mx[i]) mi[i] = max(mi[i], a[j]);
		}
	}
	for (int cas = 1; cas <= q; cas++) {
		if (op[cas] == 1) {
			cnt[a[l[cas]]][bel[l[cas]]]--;
			a[l[cas]] = r[cas];
			cnt[a[l[cas]]][bel[l[cas]]]++;
			push_up(bel[l[cas]]); // 修改a_x后，更新所在块的信息
		}
		else {
			int t1 = bel[l[cas]], t2 = bel[r[cas]];
			int maxn = 0, minn = 0, res = 0;
			if (t1 == t2) { // 在同一个块，暴力扫一遍
				for (int i = l[cas]; i <= r[cas]; i++) maxn = max(maxn, a[i]);
				for (int i = l[cas]; i <= r[cas]; i++) {
					if (maxn != a[i]) minn = max(minn, a[i]);
				}
				for (int i = l[cas]; i <= r[cas]; i++) {
					if (minn == a[i]) res++;
				}
				cout << res << endl;
			}
			else {
				for (int i = l[cas]; i <= rx[t1]; i++) maxn = max(maxn, a[i]);
				for (int i = lx[t2]; i <= r[cas]; i++) maxn = max(maxn, a[i]);
				for (int i = t1 + 1; i <= t2 - 1; i++) maxn = max(maxn, mx[i]); // maxn 求出最大值
				for (int i = l[cas]; i <= rx[t1]; i++) {
					if (a[i] != maxn) minn = max(minn, a[i]);
				}
				for (int i = lx[t2]; i <= r[cas]; i++) {
					if (a[i] != maxn) minn = max(minn, a[i]);
				}
				for (int i = t1 + 1; i <= t2 - 1; i++) {
					if (mx[i] != maxn) minn = max(minn, mx[i]);
					else minn = max(minn, mi[i]);	
				} // minn 求出次大值
				for (int i = l[cas]; i <= rx[t1]; i++) if (a[i] == minn) res++;
				for (int i = lx[t2]; i <= r[cas]; i++) if (a[i] == minn) res++;
				for (int i = t1 + 1; i <= t2 - 1; i++) res += cnt[minn][i]; // 统计出现次数
				cout << res << endl;
			}
		}
	}
} 
```

---

## 作者：Genius_Star (赞：2)

### 思路：

朴素线段树，赛时 $5$ 分钟秒了，感觉绿顶天了……

考虑线段树维护区间严格最大值 $Max_1$，区间严格次小值 $Max_2$，区间严格最大值的出现次数 $sum_1$，区间严格次小值的出现次数 $sum_2$。

现在考虑一下区间合并怎么写。

法一可以进行一些较复杂的分讨（主要是容易写挂）通过比较左右子区间 $Maxl_1,Maxl_2,Maxr_1,Maxr_2$ 的大小求出区间合并后的严格次大值。

法二是开一个集合，使用 ``set`` 维护，然后将 $Maxl_1,Maxl_2,Maxr_1,Maxr_2$ 放进去，如果当前集合的元素个数为 $1$，则没有严格次大值；否则是集合中次大的数。

本题解采用法二，主要因为较好写一些，不用多想，且容易挑错。

时间复杂度为 $O(N \log N)$。

**常数偏大，谨慎使用。**

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=200200;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,m,op,x,y,l,r;
ll a[N];
set<ll> s;
struct St{
	ll Max1,Max2;
	ll sum1,sum2;
	St(){
		Max1=Max2=sum1=sum2=0;
	}
};
struct Node{
	ll l,r;
	St h;
}X[N<<2];
St Union(St a,St b){
	St ans;
	s.clear();
	ans.sum1=ans.sum2=0;
	ans.Max1=max(a.Max1,b.Max1);
	if(ans.Max1==a.Max1)
	  ans.sum1+=a.sum1;
	if(ans.Max1==b.Max1)
	  ans.sum1+=b.sum1;
	s.insert(a.Max1);
	if(a.Max2)
	  s.insert(a.Max2);
	s.insert(b.Max1);
	if(b.Max2)
	  s.insert(b.Max2);
	if(s.size()==1){
		ans.Max2=0;
		return ans;
	}
	auto it=s.end();
	it--;
	it--;
	ans.Max2=*it;
	if(ans.Max2==a.Max1)
	  ans.sum2+=a.sum1;
	if(ans.Max2==b.Max1)
	  ans.sum2+=b.sum1;	
	if(ans.Max2==a.Max2)
	  ans.sum2+=a.sum2;
	if(ans.Max2==b.Max2)
	  ans.sum2+=b.sum2;
	return ans;
}
void pushup(ll k){
	X[k].h=Union(X[k<<1].h,X[k<<1|1].h);
}
void build(ll k,ll l,ll r){
	X[k].l=l,X[k].r=r;
	if(l==r){
		X[k].h.Max1=a[l];
		X[k].h.sum1=1;
		return ;
	}
	ll mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	pushup(k);
}
void add(ll k,ll i,ll v){
	if(X[k].l==i&&i==X[k].r){
		X[k].h.Max1=v;
		return ;
	}
	ll mid=(X[k].l+X[k].r)>>1;
	if(i<=mid)
	  add(k<<1,i,v);
	else
	  add(k<<1|1,i,v);
	pushup(k);
}
St qurey(ll k,ll l,ll r){
	if(X[k].l==l&&r==X[k].r)
	  return X[k].h;
	ll mid=(X[k].l+X[k].r)>>1;
	if(r<=mid)
	  return qurey(k<<1,l,r);
	else if(l>mid)
	  return qurey(k<<1|1,l,r);
	else
	  return Union(qurey(k<<1,l,mid),qurey(k<<1|1,mid+1,r));
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)
	  a[i]=read();
	build(1,1,n);
	while(m--){
		op=read(),x=read(),y=read();
		if(op==1)
		  add(1,x,y);
		else{
			write(qurey(1,x,y).sum2);
			putchar('\n');
		}
	}
	return 0;
}
```

---

## 作者：sunkuangzheng (赞：2)

$\textbf{ABC343F}$

> - 给定序列 $a$ 和 $q$ 次询问，支持单点改、查区间严格次大值的出现次数。
> - $1 \le n,q \le 2 \cdot 10^5,1 \le a_i \le 10^9$。

考虑线段树每个节点维护最大值、严格次大值及其出现次数，合并两个节点时，把两个节点维护的最大、次大放在一起排序取前 $2$ 大，出现次数相加即可。时间复杂度 $\mathcal O((n+q) \log n)$。

推荐使用 ACL（使用方法 [link](https://www.luogu.com.cn/article/luf5mvyu)），代码长度 $792 \text 	B$。

```cpp
#include <bits/stdc++.h>
#include <atcoder/segtree>
using namespace atcoder;
using namespace std;
int T,n,q,po,l,r,y,x;
struct S{int t[2],p[2];};
S op(S l,S r){
    map<int,int> mp; int fk = 0; S ok = S{{0,0},{0,0}};
    mp[-l.t[0]] += l.p[0],mp[-l.t[1]] += l.p[1],
    mp[-r.t[0]] += r.p[0],mp[-r.t[1]] += r.p[1];
    for(auto [x,y] : mp)
        if(ok.t[fk] = -x,ok.p[fk ++] = y,fk >= 2) break;
    return ok;
}S e(){return S{{0,0},{0,0}};}
int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> n >> q;
    segtree<S, op, e> seg(n);
    for(int i = 1;i <= n;i ++) cin >> x,seg.set(i-1,S{{x,0},{1,0}});
    while(q --){
        cin >> po >> l >> r;
        if(po == 1) seg.set(l-1,S{{r,0},{1,0}});
        else cout << seg.prod(l - 1,r).p[1] << "\n";
    }
}
```

---

## 作者：Federico2903 (赞：2)

## 思路

比较一眼。看到区间和值域相关的东西，下意识想到了树套树。

考虑使用树状数组套权值树，外层维护区间，内层维护值。

由于重复的值不应被计算，所以查询的时候先取出区间最大值，即 `kth(l, r, 1)`，再查询其后继 `nxt(l, r, Kval)`，最后查询其出现次数即可。

时间复杂度 $O(n\log^2n)$，疑似卡常，可能是我常数太大了吧。

## AC 代码

```cpp
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")

#include <immintrin.h>
#include <emmintrin.h>

#include <bits/stdc++.h>

#define rep(i, a, b) for(int i = (a), i##end = (b); i <= i##end; i++)
#define _rep(i, a, b) for(int i = (a), i##end = (b); i >= i##end; i--)
#define ec first
#define fb second
#define dl make_pair

using namespace std;

typedef long long ll;
typedef pair <int, int> pii;

int read() {
	int x = 0, f = 1; char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
	return x * f;
}

template <typename _Tp>
void print(_Tp x) {
	if (x < 0) x = (~x + 1), putchar('-');
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

const int MAXN = 5e5 + 5;

int H[MAXN];
int N, n, m, cnt, a[MAXN];

void init() {
	sort(H + 1, H + 1 + N);
	N = unique(H + 1, H + N + 1) - H - 1;
}

int find(int x) {
	return lower_bound(H + 1, H + 1 + N, x) - H;
}

#define ls(x) ((x) << 1)
#define rs(x) ((x) << 1 | 1)

namespace TIT {

struct node {
	int ls, rs;
	int sum;

	node() {ls = 0, rs = 0, sum = 0;}
} mem[65000000];

void pushup(int x) {
	mem[x].sum = mem[mem[x].ls].sum + mem[mem[x].rs].sum;
}

int cnt = 0;

int newNode() {
	return ++cnt;
}

int root[MAXN];

int ltr[MAXN], rtr[MAXN];

#define mid ((L + R) >> 1)

void update(int &cur, int L, int R, int k, int val) {
	if (!cur) cur = newNode();
	if (L == R) return (void) (mem[cur].sum += val);
	if (k <= mid) update(mem[cur].ls, L, mid, k, val);
	else update(mem[cur].rs, mid + 1, R, k, val);
	pushup(cur);
}

int _query(int &cur, int L, int R, int k) {
	if (!cur) cur = newNode();
	if (L == R) return mem[cur].sum;
	if (k <= mid) return _query(mem[cur].ls, L, mid, k);
	else return _query(mem[cur].rs, mid + 1, R, k);
}

int _kth(int lcnt, int rcnt, int L, int R, int k) {
	if (L == R) return L;
	int x = 0;
	rep (i, 1, rcnt) x += mem[mem[rtr[i]].ls].sum;
	rep (i, 1, lcnt) x -= mem[mem[ltr[i]].ls].sum;
	if (k <= x) {
		rep (i, 1, lcnt) ltr[i] = mem[ltr[i]].ls;
		rep (i, 1, rcnt) rtr[i] = mem[rtr[i]].ls;
		return _kth(lcnt, rcnt, L, mid, k);
	}
	else {
		rep (i, 1, lcnt) ltr[i] = mem[ltr[i]].rs;
		rep (i, 1, rcnt) rtr[i] = mem[rtr[i]].rs;
		return _kth(lcnt, rcnt, mid + 1, R, k - x);
	}
}

int _rnk(int lcnt, int rcnt, int L, int R, int k) {
	if (L == R) return 0;
	int x = 0;
	if (k <= mid) {
		rep (i, 1, lcnt) ltr[i] = mem[ltr[i]].ls;
		rep (i, 1, rcnt) rtr[i] = mem[rtr[i]].ls;
		return _rnk(lcnt, rcnt, L, mid, k);
	}
	else {
		rep (i, 1, rcnt) x += mem[mem[rtr[i]].ls].sum, rtr[i] = mem[rtr[i]].rs;
		rep (i, 1, lcnt) x -= mem[mem[ltr[i]].ls].sum, ltr[i] = mem[ltr[i]].rs;
		return x + _rnk(lcnt, rcnt, mid + 1, R, k);
	}
}

int lowbit(int x) {
	return x & (-x);
}

void add(int x, int val) {
	if (!x) return;
	for (int v = x; v <= n; v += lowbit(v)) {
		update(root[v], 1, N, a[x], val);
	}
}

int kth(int L, int R, int k) {
	int lcnt = 0, rcnt = 0;
	for (int v = R; v; v -= lowbit(v)) {
		rtr[++rcnt] = root[v];
	}
	for (int v = L - 1; v; v -= lowbit(v)) {
		ltr[++lcnt] = root[v];
	}
	return _kth(lcnt, rcnt, 1, N, k);
}

int rnk(int L, int R, int k) {
	int lcnt = 0, rcnt = 0;
	for (int v = R; v; v -= lowbit(v)) {
		rtr[++rcnt] = root[v];
	}
	for (int v = L - 1; v; v -= lowbit(v)) {
		ltr[++lcnt] = root[v];
	}
	return _rnk(lcnt, rcnt, 1, N, k) + 1;
}

int query(int L, int R, int k) {
	int res = 0;
	for (int v = R; v; v -= lowbit(v)) {
		res += _query(root[v], 1, N, k);
	}
	for (int v = L - 1; v; v -= lowbit(v)) {
		res -= _query(root[v], 1, N, k);
	}
	return res;
}

int prev(int L, int R, int k) {
	int rk = rnk(L, R, k) - 1;
	if (rk == 0) return 0;
	else return kth(L, R, rk);
}

int nxt(int L, int R, int k) {
	if (k >= N) return N + 1;
	int rk = rnk(L, R, k + 1);
	if (rk == R - L + 2) return N + 1;
	return kth(L, R, rk);
}

}

struct ops {
	int tp, p, x, l, r;
} op[MAXN];

signed main() {
	n = read(), m = read();
	rep (i, 1, n) {
		a[i] = -read();
		H[++N] = a[i];
	}
	rep (i, 1, m) {
		op[i].tp = read();
		if (op[i].tp == 1) {
			op[i].p = read(), op[i].x = -read();
			H[++N] = op[i].x;
		}
		else {
			op[i].l = read(), op[i].r = read();
		}
	}
	init();
	rep (i, 1, n) a[i] = find(a[i]);
	rep (i, 1, m) if (op[i].tp == 1) op[i].x = find(op[i].x);
	rep (i, 1, n) TIT::add(i, 1);
	rep (i, 1, m) {
		if (op[i].tp == 1) {
			TIT::add(op[i].p, -1);
			a[op[i].p] = op[i].x;
			TIT::add(op[i].p, 1);
		}
		else {
			int vkth = TIT::nxt(op[i].l, op[i].r, TIT::kth(op[i].l, op[i].r, 1));
			if (vkth == N + 1) puts("0");
			else print(TIT::query(op[i].l, op[i].r, vkth)), putchar(10);
		}
	}
	return 0;
}
```

---

## 作者：vectorxyz (赞：1)

一道线段树的模板题。

定义最大值，最大值出现次数，次大值，次大值出现次数，按照这个建树。

其他建树、单点修改、查询就不说了，和模板一摸一样，唯一有区别的就是更新操作。

这里需要分类讨论。

我们令左子树为 $l$，右子树为 $r$。如果 $l$ 的最大值和 $r$ 的最大值相等，把 $res$ 的最大值更新成 $l$ 的最大值，并把出现次数累加，再来判断次大值，操作同上；再是 $l$ 的最大值小于 $r$ 的最大值，把 $res$ 的最大值更新为 $r$ 的最大值，再让 $l$ 的最大值和 $r$ 的次大值判断，操作类似；否则就是 $l$ 的最大值大于 $r$ 的最大值，操作类似。

具体内容看代码吧。

```cpp
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

namespace std
{
    template<typename T>
    T read(T x)
    {
        T sum = 0, opt = 1;
        char ch = getchar();
        while(!isdigit(ch)) opt = (ch == '-') ? -1 : 1, ch = getchar();
        while( isdigit(ch)) sum = (sum << 1) + (sum << 3) + (ch ^ 48), ch = getchar();
        return sum * opt;
    }
}
#define int long long
#define read std::read(0ll)
#define all(a) a.begin(), a.end()

using namespace std;

vector<int> a;

const int N = 200010;

struct Node
{
    int l, r;
    int max, max_cnt, second, second_cnt;
}t[N << 2];
class SegTree
{
    public:

    #define lc (p << 1)
    #define rc (p << 1 | 1)

        Node merge(Node ls, Node rs)
        {
          // 分类讨论
            Node res = {0,0,0,0,0,0};
            res.l = ls.l, res.r = rs.r;
            if (ls.max == rs.max)
            {
                res.max = ls.max;
                res.max_cnt = ls.max_cnt + rs.max_cnt;

                if (ls.second == rs.second)
                {
                    res.second = ls.second;
                    res.second_cnt = ls.second_cnt + rs.second_cnt;
                }
                else if (ls.second < rs.second)
                {
                    res.second = rs.second;
                    res.second_cnt = rs.second_cnt;
                }
                else if (ls.second > rs.second)
                {
                    res.second = ls.second;
                    res.second_cnt = ls.second_cnt;
                }
            }
            else if (ls.max > rs.max)
            {
                res.max = ls.max;
                res.max_cnt = ls.max_cnt;

                if (ls.second == rs.max)
                {
                    res.second = ls.second;
                    res.second_cnt = ls.second_cnt + rs.max_cnt;
                }
                else if (ls.second > rs.max)
                {
                    res.second = ls.second;
                    res.second_cnt = ls.second_cnt;
                }
                else if (ls.second < rs.max)
                {
                    res.second = rs.max;
                    res.second_cnt = rs.max_cnt;
                }
            }
            else if (ls.max < rs.max)
            {
                res.max = rs.max;
                res.max_cnt = rs.max_cnt;
                
                if (ls.max == rs.second)
                {
                    res.second = ls.max;
                    res.second_cnt = ls.max_cnt + rs.second_cnt;
                }
                else if (ls.max > rs.second)
                {
                    res.second = ls.max;
                    res.second_cnt = ls.max_cnt;
                }
                else if (ls.max < rs.second)
                {
                    res.second = rs.second;
                    res.second_cnt = rs.second_cnt;
                }
            }

            return res;
        }
        void push_up(int p)
        {
            t[p] = merge(t[lc], t[rc]);
        }
        void build(int p, int l, int r)
        {
            t[p].l = l, t[p].r = r;
            if (l == r)
            {
                t[p].max = a[l];
                t[p].max_cnt = 1;
                t[p].second = 0;
                t[p].second_cnt = 0;
                return ;
            }

            int mid = l + r >> 1;

            build(lc, l, mid);
            build(rc, mid + 1, r);

            push_up(p);
        }
        void update(int p, int x, int k)
        {
            if (t[p].l == x && t[p].r == x)
            {
                t[p].max = k;
                t[p].max_cnt = 1;
                return ;
            }

            int mid = t[p].l + t[p].r >> 1;

            if (x <= mid) update(lc, x, k);
            if (x >  mid) update(rc, x, k);

            push_up(p);
        }
        Node query(int p, int l, int r)
        {
            // cout << t[p].l << ' ' << t[p].r << endl;
            if (l <= t[p].l && r >= t[p].r)
                return t[p];
            
            int mid = t[p].l + t[p].r >> 1;

            Node a, b;
            a = b = {0,0,0,0,0,0};
            if (l <= mid) a = query(lc, l, r);
            if (r >  mid) b = query(rc, l, r);

            if (a.l && b.l)
                return merge(a, b);
            else if (a.l)
                return a;
            else if (b.l)
                return b;
        }

    #undef lc
    #undef rc
};

signed main()
{
    SegTree T;

    int n = read, m = read;
    a.resize(n + 1);
    
    for (int i = 1; i <= n; i ++ )
        a[i] = read;
        
    T.build(1, 1, n);

    while(m -- )
    {
        int op = read, x = read, y = read;
        // cout << x << " " << y << endl;
        if (op == 1)
            T.update(1, x, y);
        else
        {
            Node t = T.query(1, x, y);
            
            // printf("%lld %lld %lld %lld %lld %lld\n", t.l, t.r, t.max, t.max_cnt, t.second, t.second_cnt);
            
            cout << t.second_cnt << endl;
            
            // return 0;
        }
    }

    return 0;
}
```

[提交记录](https://atcoder.jp/contests/abc343/submissions/50906231)。

---

## 作者：AlicX (赞：1)

## Solution 

题目要求单点修改，查询区间第二小值出现的次数。

先考虑如何求区间第二小值：线段树维护区间最大值、次大值，向父亲节点更新的时候只需要把左右儿子的最大值和次大值合并为父亲节点的最大值次大值即可。

在考虑如何求一个数在区间的出现次数：这里有很多种做法，莫队、分块、线段树都可以，不妨考虑分块。将数组和修改的操作一起离散化后定义 $cnt_{i,x}$ 表示在第 $i$ 个块 $x$ 这个数出现的次数，散块暴力即可。

时间复杂度为 $O(m (\log n+\sqrt n))$，空间卡的有点紧，注意不要开 `long long`。

```cpp
#include<bits/stdc++.h> 
#define ll long long 
#define x first 
#define y second 
#define il inline 
#define debug() puts("-----") 
using namespace std; 
typedef pair<int,int> pii; 
il int read(){ 
	int x=0,f=1; char ch=getchar(); 
	while(ch<'0'||ch>'9'){ if(ch=='-') f=-1; ch=getchar(); } 
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar(); 
	return x*f; 
} 
const int N=2e5+10,M=450; 
int n,m; 
int mp[N<<1];
struct node{
	int l,r; 
	int w[2]; 
}tr[N<<2];
struct Node{
	int opt; 
	int x,y; 
}q[N]; 
int len; 
int a[N],b[N<<1]; 
int cnt[M][N<<1]; 
int id(int x){
	return (x-1)/len+1; 
} 
il void pushup(int u){
	int c[6]={0,tr[u<<1].w[0],tr[u<<1].w[1],tr[u<<1|1].w[0],tr[u<<1|1].w[1]}; 
	int num=4; sort(c+1,c+num+1); num=unique(c+1,c+num+1)-c-1; 
	tr[u].w[0]=c[num]; tr[u].w[1]=c[num-1]; 
}
il void build(int u,int l,int r){
	tr[u]={l,r}; 
	if(l==r){
		tr[u].w[0]=a[l]; 
		return ; 
	} int mid=l+r>>1; 
	build(u<<1,l,mid),build(u<<1|1,mid+1,r); 
	pushup(u); 
} 
il void modify(int u,int x,int p){ 
	if(tr[u].l==tr[u].r){
		int num=3; 
		tr[u].w[0]=p; 
		return ; 
	} int mid=tr[u].l+tr[u].r>>1; 
	if(x<=mid) modify(u<<1,x,p); 
	else modify(u<<1|1,x,p); 
	pushup(u); 
} 
il pii query(int u,int l,int r){
	if(l<=tr[u].l&&tr[u].r<=r){ 
		return {tr[u].w[0],tr[u].w[1]}; 
	} int mid=tr[u].l+tr[u].r>>1; 
	pii a1={0,0},a2={0,0}; 
	if(l<=mid) a1=query(u<<1,l,r); 
	if(r>mid) a2=query(u<<1|1,l,r); 
	int c[6]={0,a1.x,a1.y,a2.x,a2.y}; 
	int num=4; sort(c+1,c+num+1); num=unique(c+1,c+num+1)-c-1; 
	return {c[num],c[num-1]};  
}
int fck(int l,int r,int x){
	int idl=id(l),idr=id(r); 
	if(idl==idr){ 
		int res=0; 
		for(int i=l;i<=r;i++) if(a[i]==x) res++; 
		return res; 
	} int res=0; 
	for(int i=l;i<=min(idl*len,n);i++){
		if(a[i]==x) res++; 
	} //cout<<res<<endl; 
	for(int i=(idr-1)*len+1;i<=r;i++) if(a[i]==x) res++; 
	for(int i=idl+1;i<idr;i++) res+=cnt[i][x]; 
	return res; 
}
signed main(){ 
	int num=0;  
	cin>>n>>m; len=sqrt(n);  
	for(int i=1;i<=n;i++) cin>>a[i],b[++num]=a[i]; 
	for(int i=1;i<=m;i++){
		cin>>q[i].opt>>q[i].x>>q[i].y; 
		if(q[i].opt==1) b[++num]=q[i].y; 
	} 
	sort(b+1,b+num+1); num=unique(b+1,b+num+1)-b-1; 
	for(int i=1;i<=m;i++){
		if(q[i].opt==1){
			int lst=q[i].y; 
			q[i].y=lower_bound(b+1,b+num+1,q[i].y)-b; 
			mp[q[i].y]=lst; 
		}
	}
	for(int i=1;i<=n;i++){
		int lst=a[i]; 
		a[i]=lower_bound(b+1,b+num+1,a[i])-b; 
		mp[a[i]]=lst; 
		int x=id(i); cnt[x][a[i]]++; 
	} build(1,1,n); 
	for(int i=1;i<=m;i++){
		if(q[i].opt==1){ 
			int x1=id(q[i].x); 
			cnt[x1][a[q[i].x]]--; 
			modify(1,q[i].x,q[i].y); 
			cnt[x1][q[i].y]++; a[q[i].x]=q[i].y; 
		} else{ 
			int x=query(1,q[i].x,q[i].y).y; 
//			cout<<"ded"<<mp[x]<<endl; 
			printf("%d\n",fck(q[i].x,q[i].y,x)); 
		} 
	}return 0; 
} /*
8 3
2 4 4 3 9 1 1 2
1 5 4
1 4 4
2 2 7
*/
```

---

## 作者：_RainCappuccino_ (赞：1)

赛时不会 E，看到 F 高兴坏了。

# First. 题目分析

首先，这道题单点修，区间查，一般都可以用数据结构做，此时我们不妨往**线段树**上想一想。

那么求次大，我们线段树需要维护什么呢？

对于合并两个区间，其的次大**并不是**两个区间次大中的较大者，而还需要考虑两个区间的最大值，即两个区间最**大值、次大值**中的**次大值**。

那么要求数量，那是否需要再维护一个**最大值数量**和**次大值数量**呢？

所以要维护的信息就是：

1. **最大值**

2. **次大值**

3. **最大值的数量**

4. **次大值的数量**

此时求出来了次大值，那么对于所有等于次大的数，将其的数量加于次大的数量上即可。

一点小提醒：本题是**严格次小**，所以次大值一开始设为 $-1$，并且更新的时候要去重。

# Second. 区间合并的实现

我的做法很暴力，将两个区间分别的次大和最大存于一个数组里，然后排序，再去重，再像求序列次大一样更新。

这里 node 表示的是每个区间的信息。

```cpp
struct node {
    int ma , ma2 , cnt , cnt2;
  // ma : 最大值
  // ma2 : 次大值
  // cnt : 最大值的个数
  // cnt2 : 次大值的个数
}t[N * 4];
node hb(node x , node y) {
    node res = { -1, -1, 0, 0 };
    int cur[5] = { 0, x.ma, y.ma, x.ma2, y.ma2 };
    sort(cur + 1 , cur + 1 + 4);
    for (int i = 1; i <= 4; i++) {
        if (cur[i] == cur[i - 1]) continue;
        if (cur[i] > res.ma) res.ma2 = res.ma , res.ma = cur[i];
        else if (cur[i] > res.ma2) res.ma2 = cur[i]; // 类比序列次大，如果大于最大值，那么先将次大值更新为最大值，然后最大值更新为该值
    }
    if (res.ma == x.ma) res.cnt += x.cnt;
    if (res.ma == y.ma) res.cnt += y.cnt;
    if (res.ma2 == x.ma) res.cnt2 += x.cnt; //  对于所有 = 次大的加上它的数量
    if (res.ma2 == x.ma2) res.cnt2 += x.cnt2;
    if (res.ma2 == y.ma) res.cnt2 += y.cnt;
    if (res.ma2 == y.ma2) res.cnt2 += y.cnt2;
    if (res.ma2 == res.ma) res.ma2 = -1 , res.cnt2 = 0; 
    return res;
}
```
这里采用了[小粉兔式写法](https://www.luogu.com.cn/article/7dnx35wf)（强烈推荐，超好用）。

# Third. 修改和查询的实现

## 修改

由于是单点修改，所以不用 lazy。

直接递归到修改节点，再一层层更新即可。

```cpp
void updata(int p , int l , int r , int k , int x) {
    if (l == r) t[p] = { x, -1, 1, 0 }; // 直接修改
    else {
        int mid = l + r >> 1;
        if (mid >= k) updata(p * 2 , l , mid , k , x);
        if (mid < k) updata(p * 2 + 1 , mid + 1 , r , k , x);
        t[p] = hb(t[p * 2] , t[p * 2 + 1]); // 向上更新
    }
}
```

## 查询

直接查询并合并查询得到的区间即可。

```cpp
node getans(int p , int l , int r , int ql , int qr) {
    if (ql <= l && r <= qr) {return t[p]; }
    int mid = l + r >> 1; node res = { -1, -1, -1, -1 };
    if (mid >= ql) res = getans(p * 2 , l , mid , ql , qr);
    if (mid < qr) {
        node x = getans(p * 2 + 1 , mid + 1 , r , ql , qr);
        if (res.ma != -1) res = hb(res , x); // 如果于左右两边都相交，那么合并左右两边
        else res = x;
    }
    return res;
}

```


# 时间复杂度分析

建树：$O(n \log_2 n)$

每次修改：$O(\log_2 n)$

总时间复杂度：$O(n \log_2 n)$

# 最后完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int , int> pi;
const int N = 2e5 + 10;
int n , q;
int a[N];
struct node {
    int ma , ma2 , cnt , cnt2;
}t[N * 4];
node hb(node x , node y) {
    node res = { -1, -1, 0, 0 };
    int cur[5] = { 0, x.ma, y.ma, x.ma2, y.ma2 };
    sort(cur + 1 , cur + 1 + 4);
    for (int i = 1; i <= 4; i++) {
        if (cur[i] == cur[i - 1]) continue;
        if (cur[i] > res.ma) res.ma2 = res.ma , res.ma = cur[i];
        else if (cur[i] > res.ma2) res.ma2 = cur[i];
    }
    if (res.ma == x.ma) res.cnt += x.cnt;
    if (res.ma == y.ma) res.cnt += y.cnt;
    if (res.ma2 == x.ma) res.cnt2 += x.cnt;
    if (res.ma2 == x.ma2) res.cnt2 += x.cnt2;
    if (res.ma2 == y.ma) res.cnt2 += y.cnt;
    if (res.ma2 == y.ma2) res.cnt2 += y.cnt2;
    if (res.ma2 == res.ma) res.ma2 = -1 , res.cnt2 = 0;
    return res;
}

void build(int p , int l , int r) {
    if (l == r) t[p] = { a[l], -1, 1, 0 };
    else build(p * 2 , l , l + r >> 1) , build(p * 2 + 1 , (l + r >> 1) + 1 , r) , t[p] = hb(t[p * 2] , t[p * 2 + 1]);
}
void updata(int p , int l , int r , int k , int x) {
    if (l == r) t[p] = { x, -1, 1, 0 };
    else {
        int mid = l + r >> 1;
        if (mid >= k) updata(p * 2 , l , mid , k , x);
        if (mid < k) updata(p * 2 + 1 , mid + 1 , r , k , x);
        t[p] = hb(t[p * 2] , t[p * 2 + 1]);
    }
}
node getans(int p , int l , int r , int ql , int qr) {
    if (ql <= l && r <= qr) {return t[p]; }
    int mid = l + r >> 1; node res = { -1, -1, -1, -1 };
    if (mid >= ql) res = getans(p * 2 , l , mid , ql , qr);
    if (mid < qr) {
        node x = getans(p * 2 + 1 , mid + 1 , r , ql , qr);
        if (res.ma != -1) res = hb(res , x);
        else res = x;
    }
    return res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build(1 , 1 , n);
    while (q--) {
        int opt , l , r;
        cin >> opt >> l >> r;
        if (opt == 1) updata(1 , 1 , n , l , r);
        else cout << getans(1 , 1 , n , l , r).cnt2 << endl;
    }
    return 0;
}
```

---

## 作者：Skeleton_Huo (赞：1)

# [ABC343F] Second Largest Query 题解

### 思路
如果学过吉老师的线段树应该对此类操作相当熟悉。

首先很容易能想到用线段树求解，设置 `se` 和 `cnt_se` 分别表示线段树对应区间中次大值以及次大值的数量，`ma` 和 `cnt_ma` 分别表示最大值和次大值的数量。接下来主要的问题是考虑如何合并区间。

### Push Up
设 `u` 为当前区间，`l` 和 `r` 分别为左右两个子区间。此时 `u.se` 可能是两个子区间的某个最大值，也可能是某个次大值。

1. 若 `l.ma == r.ma`，那么 `u.se = max(l.se, r.se)`。
2. 若 `l.ma < r.ma`，那么 `u.se = max(l.ma, r.se)`。
3. 若 `l.ma > r.ma`，那么 `u.se = max(l.se, r.ma)`。

剩余的 `cnt` 的具体求法和 `ma` 的更新可以参考代码。

我的代码写得很冗长，蹲一下更好的写法。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10, inf = 0x3f3f3f3f;

int n, m, a[N];

#define MID ((l + r) >> 1)
#define LS (p << 1)
#define RS (p << 1 | 1)

struct SGT {
  struct Node {
    int ma, se, cnt_ma, cnt_se;
    friend Node operator + (Node a, Node b) {
      if (a.ma == b.ma) {
        if (a.se == b.se)
          return {a.ma, a.se, a.cnt_ma + b.cnt_ma, a.cnt_se + b.cnt_se};
        else if (a.se > b.se)
          return {a.ma, a.se, a.cnt_ma + b.cnt_ma, a.cnt_se};
        else
          return {a.ma, b.se, a.cnt_ma + b.cnt_ma, b.cnt_se};
      } else if (a.ma > b.ma) {
        if (b.ma == a.se)
          return {a.ma, b.ma, a.cnt_ma, a.cnt_se + b.cnt_ma};
        else if (b.ma > a.se)
          return {a.ma, b.ma, a.cnt_ma, b.cnt_ma};
        else
          return {a.ma, a.se, a.cnt_ma, a.cnt_se};
      } else {
        if (a.ma == b.se)
          return {b.ma, a.ma, b.cnt_ma, a.cnt_ma + b.cnt_se};
        else if (a.ma > b.se)
          return {b.ma, a.ma, b.cnt_ma, a.cnt_ma};
        else 
          return {b.ma, b.se, b.cnt_ma, b.cnt_se};
      }
    }
  } c[N << 2];

  void buildtree(int p = 1, int l = 1, int r = n) {
    if (l == r) {
      c[p] = {a[l], -inf, 1, 0};
      return;
    }
    buildtree(LS, l, MID), buildtree(RS, MID + 1, r);
    c[p] = c[LS] + c[RS];
  }

  void change(int x, int y, int p = 1, int l = 1, int r = n) {
    if (l == r) {
      c[p] = {y, -inf, 1, 0};
      return;
    }
    if (x <= MID) change(x, y, LS, l, MID);
    else change(x, y, RS, MID + 1, r);
    c[p] = c[LS] + c[RS];
  }

  Node query(int s, int t, int p = 1, int l = 1, int r = n) {
    if (r < s || l > t) return {-inf, -inf, 0, 0};
    if (s <= l && r <= t) return c[p];
    return query(s, t, LS, l, MID) + query(s, t, RS, MID + 1, r);
  }

} sgt;

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  
  cin >> n >> m;

  for (int i = 1; i <= n; i++) cin >> a[i];

  sgt.buildtree();

  int op, l, r;
  while (m--) {
    cin >> op >> l >> r;
    if (op == 2) cout << sgt.query(l, r).cnt_se << "\n";
    else sgt.change(l, r);
  }

  return 0;
}
```

---

## 作者：kczw (赞：0)

# 题意
维护一个长 $N(N\le 2\times10^5)$ 的序列，须支持单点修改和查询次大值数量。
# 思路
用线段树维护，分别维护以下这些值：
- 最大值。
- 最大值数量。
- 次大值。
- 次大值数量。

然后，相对于模板的线段树这里比较特殊的是根据子节点信息更新父节点的过程。

这个特殊的点看似恶心，但是其实不难，只是分支有点多，对于左右儿子区间的最大值的不同以及相同下还有可能衍生出比较左儿子区间次大值和右儿子区间最大值等等不同情况。

这里不再赘述，相信代码会更为直观。
# 主要代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
struct tree{int fir,sec,fnum,snum;}tr[N<<2];
inline void pushup(int p){
    if(tr[p<<1].fir<tr[p<<1|1].fir){//右儿子区间最大值更大
        tr[p].fir=tr[p<<1|1].fir;//更新父区间最大值
        tr[p].fnum=tr[p<<1|1].fnum;//更新父区间最大值数量
        if(tr[p<<1].fir<tr[p<<1|1].sec){//右儿子区间次大值大于左儿子区间最大值
            tr[p].sec=tr[p<<1|1].sec;//更新父区间次大值
            tr[p].snum=tr[p<<1|1].snum;//更新父区间次大值数量
        }
        else if(tr[p<<1].fir>tr[p<<1|1].sec){//右儿子区间次大值小于左儿子区间最大值
            tr[p].sec=tr[p<<1].fir;//更新父区间次大值
            tr[p].snum=tr[p<<1].fnum;//更新父区间次大值数量
        }
        else{//右儿子区间次大值等于左儿子区间最大值
            tr[p].sec=tr[p<<1].fir;//更新父区间次大值
            tr[p].snum=tr[p<<1].fnum+tr[p<<1|1].snum;//更新父区间次大值数量
        }
    }
    else if(tr[p<<1].fir>tr[p<<1|1].fir){//左儿子区间最大值更大
        tr[p].fir=tr[p<<1].fir;//更新父区间最大值
        tr[p].fnum=tr[p<<1].fnum;//更新父区间最大值数量
        if(tr[p<<1|1].fir<tr[p<<1].sec){//左儿子区间次大值大于右儿子区间最大值
            tr[p].sec=tr[p<<1].sec;//更新父区间次大值
            tr[p].snum=tr[p<<1].snum;//更新父区间次大值数量
        }
        else if(tr[p<<1|1].fir>tr[p<<1].sec){//左儿子区间次大值小于右儿子区间最大值
            tr[p].sec=tr[p<<1|1].fir;//更新父区间次大值
            tr[p].snum=tr[p<<1|1].fnum;//更新父区间次大值数量
        }
        else{//左儿子区间次大值等于于右儿子区间最大值
            tr[p].sec=tr[p<<1|1].fir;//更新父区间次大值
            tr[p].snum=tr[p<<1|1].fnum+tr[p<<1].snum;//更新父区间次大值数量
        }
    }
    else{//左右儿子区间最大值相等
        tr[p].fir=tr[p<<1].fir;//更新父区间最大值
        tr[p].fnum=tr[p<<1].fnum+tr[p<<1|1].fnum;//更新父区间最大值数量
        if(tr[p<<1].sec>tr[p<<1|1].sec){//左儿子区间次大值大于右儿子区间次大值
            tr[p].sec=tr[p<<1].sec;//更新父区间次大值
            tr[p].snum=tr[p<<1].snum;//更新父区间次大值数量
        }
        else if(tr[p<<1|1].sec>tr[p<<1].sec){//左儿子区间次大值小于右儿子区间次大值
            tr[p].sec=tr[p<<1|1].sec;//更新父区间次大值
            tr[p].snum=tr[p<<1|1].snum;//更新父区间次大值数量
        }
        else{//左儿子区间次大值等于右儿子区间次大值
            tr[p].sec=tr[p<<1].sec;//更新父区间次大值
            tr[p].snum=tr[p<<1].snum+tr[p<<1|1].snum;//更新父区间次大值数量
        }
    }
}
inline void build(int p,int l,int r){
    if(l==r){
        scanf("%d",&tr[p].fir);
        tr[p].fnum=1;
        return;
    }
    build(p<<1,l,l+r>>1);
    build(p<<1|1,(l+r>>1)+1,r);
    pushup(p);
}
int id,x,l,r;
inline void modify(int p,int L,int R){
    if(L>id||R<id)
        return;
    if(L==R){
        tr[p].fir=x;
        return;
    }
    modify(p<<1,L,L+R>>1);
    modify(p<<1|1,(L+R>>1)+1,R);
    pushup(p);
}
inline tree query(int p,int L,int R){
    if(L>r||R<l)
        return {0,0,0,0};
    if(l<=L&&R<=r)
        return tr[p];
    tree A=query(p<<1,L,L+R>>1),B=query(p<<1|1,(L+R>>1)+1,R),C;
  //后文与函数 pushup 本质相同
    if(A.fir<B.fir){
        C.fir=B.fir;
        C.fnum=B.fnum;
        if(A.fir<B.sec){
            C.sec=B.sec;
            C.snum=B.snum;
        }
        else if(A.fir>B.sec){
            C.sec=A.fir;
            C.snum=A.fnum;
        }
        else{
            C.sec=A.fir;
            C.snum=A.fnum+B.snum;
        }
    }
    else if(A.fir>B.fir){
        C.fir=A.fir;
        C.fnum=A.fnum;
        if(B.fir<A.sec){
            C.sec=A.sec;
            C.snum=A.snum;
        }
        else if(B.fir>A.sec){
            C.sec=B.fir;
            C.snum=B.fnum;
        }
        else{
            C.sec=B.fir;
            C.snum=B.fnum+A.snum;
        }
    }
    else{
        C.fir=A.fir;
        C.fnum=A.fnum+B.fnum;
        if(A.sec>B.sec){
            C.sec=A.sec;
            C.snum=A.snum;
        }
        else if(B.sec>A.sec){
            C.sec=B.sec;
            C.snum=B.snum;
        }
        else{
            C.sec=A.sec;
            C.snum=A.snum+B.snum;
        }
    }
    return C;
}
int n,q;
main(){
    scanf("%d%d",&n,&q);
    build(1,1,n);
    for(int i=1,op;i<=q;i++){
        scanf("%d",&op);
        if(op==1){
            scanf("%d%d",&id,&x);
            modify(1,1,n);
        }
        else{
            scanf("%d%d",&l,&r);
            tree ans=query(1,1,n);
            if(ans.sec==0)puts("0");//无次小值
            else printf("%d\n",ans.snum);
        }
    }
    return 0;
}
```

---

## 作者：lateworker (赞：0)

### 题目链接：[洛谷](https://www.luogu.com.cn/problem/AT_abc343_f) / [AtCoder](https://atcoder.jp/contests/abc343/tasks/abc343_f)

# 题意

给定一个长度为 $N$ 初始序列 $A\ =\ (A_1,\ A_2,\ \ldots,\ A_N)$，并让你实现以下两种操作：

1. 将第 $p$ 个数改为 $x$。
2. 查询并输出 $[l, r]$ 区间内次大值出现的次数，不存在次大值则输出 $0$。

# 思路

看到维护区间信息，又看到 $1\leq N,Q\leq 2\times 10^5$，一眼丁真鉴定为线段树。

因为查询的是次大值的出现次数，所以我们要维护四个值：

区间最大值、区间次大值、最大值出现次数、次大值出现次数。~~这很套路~~

```cpp
struct Data {
    int ma1, ma2, cnt1, cnt2;
    // ma1：最大值，ma2：次大值
} st[N<<2];
```

合并的时候把左右区间的最大值、次大值放在一起排个序，找到新区间对应的两个值，并根据维护的四个出现次数统计出新区间最大值、次大值的出现次数。

区间合并代码：

```cpp
Data merge(const Data &a, const Data &b) {
    if(a.ma1 == 0) return b;
    if(b.ma1 == 0) return a;
    Data ret;
    int val[4] = { a.ma1, a.ma2, b.ma1, b.ma2 };
    sort(val, val+4); // 由小到大排序
    ret.ma1 = val[3]; // 最后一位一定是最大值 ret.ma1
    // 更新最大值出现次数 ret.cnt1
    if(ret.ma1 == a.ma1) ret.cnt1 += a.cnt1;
    if(ret.ma1 == a.ma2) ret.cnt1 += a.cnt2;
    if(ret.ma1 == b.ma1) ret.cnt1 += b.cnt1;
    if(ret.ma1 == b.ma2) ret.cnt1 += b.cnt2;
    // 从大到小找严格次大值 ret.ma2
    if(val[2] != val[3]) ret.ma2 = val[2];
    else if(val[1] != val[3]) ret.ma2 = val[1];
    else if(val[0] != val[3]) ret.ma2 = val[0];
    else ret.ma2 = 0;
    // 如果次大值不为0，更新次大值出现次数 ret.cnt2，否则将其设为0
    if(ret.ma2) {
        if(ret.ma2 == a.ma1) ret.cnt2 += a.cnt1;
        if(ret.ma2 == a.ma2) ret.cnt2 += a.cnt2;
        if(ret.ma2 == b.ma1) ret.cnt2 += b.cnt1;
        if(ret.ma2 == b.ma2) ret.cnt2 += b.cnt2;
    } else ret.cnt2 = 0;
    return ret;
}
```

# 具体实现

再次审视这道题，不难发现是一个 **单点修改，区间查询** 的线段树。

单点修改，区间查询，这不就是 zkw 线段树吗？

zkw 线段树是一种非常简单的非递归式线段树，没学过的建议直接去看[洛谷日报](https://zhuanlan.zhihu.com/p/44117687)。

下面是~~不~~完整代码：

**本题解禁止理解性默写！**~~看懂区间合并部分就应该会写了吧~~

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 2e5+10;
struct Data {
    int ma1, ma2, cnt1, cnt2;
    // 两个构造函数，自动初始化结构体
    Data() { ma1 = ma2 = cnt1 = cnt2 = 0; }
    Data(int _ma1, int _ma2, int _cnt1, int _cnt2) 
        { ma1 = _ma1, ma2 = _ma2, cnt1 = _cnt1, cnt2 = _cnt2; } 
} st[N<<2];
// 区间合并
Data merge(const Data &a, const Data &b) {
    if(a.ma1 == 0) return b;
    if(b.ma1 == 0) return a;
    Data ret;
    ... // 具体参见上文，放在这里会有些臃肿
    return ret;
}
#define le (u<<1)
#define ri (u<<1|1)
inline void push_up(int u) { st[u] = merge(st[le], st[ri]); }
int n, tn, q, a[N];
void build() {
    for(tn=1;tn<=n+1;tn<<=1); // 算出偏移量 tn
    for(int i=1;i<=n;++i)
        st[i+tn] = {a[i], 0, 1, 0}; // 叶子结点中没有次大值
    for(int u=tn-1;u;--u) // 更新所有非叶子结点
        push_up(u);
}
void update(int p, int v) {
    p += tn; // 通过偏移量定位叶子结点
    st[p] = {v, 0, 1, 0}; // 单点修改
    for(p>>=1;p;p>>=1) // 自底向上更新其它结点
        push_up(p);
}
Data query(int l, int r) {
    Data L, R;
    // 区间查询，简单来说就是用两个指针把区间内的子树“夹”出来
    for(l+=tn-1,r+=tn+1;l^r^1;l>>=1,r>>=1) {
        if(~l&1) L = merge(L, st[l^1]);
        if(r&1) R = merge(R, st[r^1]);
    }
    return merge(L, R);
}
int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin>>n>>q;
    for(int i=1;i<=n;++i) cin>>a[i];
    build(); // 一定要记得建树！
    while(q--) {
        int op, x, y;
        cin>>op>>x>>y;
        if(op==1) {
            update(x, y);
        } else if(op==2) {
            cout<<query(x, y).cnt2<<"\n";
        }
    }
    return 0;
}
```

---

## 作者：TruchyR (赞：0)

线段树合并写炸了导致赛后一分钟过题，评价是神秘 E 题。 

考虑使用线段树维护：  

一个节点维护**两组**信息：

- 最大的数和最大的数的出现次数。  

- 第二大的数和第二大的数的出现次数。  

考虑如何合并儿子的信息？  

- 把儿子总共**四组**信息排个序，取最大两个作为父亲节点的信息。  
- 注意**初始化**，以及如果有相同的数要合并！  

由于是单点修改区间查询，不需要写懒标记，修改操作思路如下：  

- 线段树的套路，从根节点往下搜。  
- 如果是叶子节点，将这个数的信息插入。  
- 否则，再次合并两个儿子的信息，过程如上。  

最后是查询部分：  

- 是叶子节点就直接返回信息。  
- 否则，将儿子中包含在询问的信息合并。  
- 最后输出的就是得到的结果的第二小的出现次数。  

代码实现：  

```cpp
#include<bits/stdc++.h>
#define MX 200005
#define GP pair<int,int>
#define MP make_pair
#define GT tuple<int,int,int,int>
#define MT make_tuple
#define INF 1000000001
using namespace std;int read();
int a[MX],n,m,b,c,d,e;
class SegmentTree{
    public:
    int t[MX*4][4],lazy[MX*4];
    void HB(int k,int l,int r){
    	GP w[4];
    	w[0]=MP(t[l][0],t[l][1]);w[1]=MP(t[l][2],t[l][3]);
    	w[2]=MP(t[r][0],t[r][1]);w[3]=MP(t[r][2],t[r][3]);
    	sort(w,w+4);t[k][0]=t[k][1]=t[k][2]=t[k][3]=0;
    	int cnt=0,u=INF;
    	for(int i=3;i>=0;i--){
    		if(u>w[i].first){
    			cnt++;
    			if(cnt<=2) t[k][cnt*2-2]=u=w[i].first;
			}
    		if(cnt<=2) t[k][cnt*2-1]+=w[i].second;
		}
	}
	void UPDATE(int k,int z){t[k][0]=z,t[k][1]=1;}
    void build(int k,int l,int r){
    	if(l==r){t[k][0]=a[l],t[k][1]=1;return;}
    	int mid=(l+r)>>1;
    	build(k*2,l,mid);
    	build(k*2+1,mid+1,r);
    	HB(k,k*2,k*2+1);
    }
    void change(int k,int l,int r,int id,int z){
    	if(l==r){UPDATE(k,z);return;}
    	int mid=(l+r)>>1;
    	if(id<=mid) change(k*2,l,mid,id,z);
    	else change(k*2+1,mid+1,r,id,z);
    	HB(k,k*2,k*2+1);
	}
	GT nmax(int k,int l,int r,int L,int R){
		GT ret=MT(0,0,0,0);
		if(L<=l && r<=R){
			ret=MT(t[k][0],t[k][1],t[k][2],t[k][3]);
			return ret;
		}
		int mid=(l+r)>>1;
		GP w[4];w[0]=w[1]=w[2]=w[3]=MP(0,0);GT gt;
		if(L<=mid){
			gt=nmax(k*2,l,mid,L,R);
			w[0]=MP(get<0>(gt),get<1>(gt));
			w[1]=MP(get<2>(gt),get<3>(gt));
		}
		if(R>mid){
			gt=nmax(k*2+1,mid+1,r,L,R);
			w[2]=MP(get<0>(gt),get<1>(gt));
			w[3]=MP(get<2>(gt),get<3>(gt));
		}
    	sort(w,w+4);
    	int cnt=0,u=INF;
    	for(int i=3;i>=0;i--){
    		if(u>w[i].first){
    			if(cnt==0) get<0>(ret)=u=w[i].first;
    			else if(cnt==1) get<2>(ret)=u=w[i].first;
    			cnt++;
			}
    		if(cnt==1) get<1>(ret)+=w[i].second;
    		if(cnt==2) get<3>(ret)+=w[i].second;
		}
		return ret;
	}
};
signed main(){
	n=read();m=read();SegmentTree Tree;
	for(int i=1;i<=n;i++) a[i]=read();
	Tree.build(1,1,n);
	for(int i=1;i<=m;i++){
		if(read()==2){
			d=read();e=read();
			printf("%d\n",get<3>(Tree.nmax(1,1,n,d,e)));
		}else{
			d=read();e=read();
			Tree.change(1,1,n,d,e);
		}
	}
	return 0;
}
int read(){
	int Ca=0;char Cr=' ';int Cf=1;
	while(Cr<'0' || Cr>'9'){Cr=getchar();if(Cr=='-'){Cf=-1;}}
	while(Cr>='0' && Cr<='9'){Ca=Ca*10+Cr-48;Cr=getchar();}
	return Ca*Cf;
}
```

---

## 作者：MornStar (赞：0)

## [ABC343F] Second Largest Query
### 题意
有两个操作，一个单点修改，一个求区间严格次大值的个数。

### 思路
首先带修主席树可以直接套板子但是没必要（~~其实是我不会写~~）。

所以我仿造维护严格次大值的值的线段树来做题。

线段树节点中维护四个值：最大值、次大值以及它们的个数。
```cpp
struct segment_node{int ma,se,manum,senum;}t[N<<2];
```
接下来，因为上传答案和区间查询都需要用到合并区间，所以先讨论 merge 函数。

对于两个节点 $a$ 和 $b$，如果 $a_{ma}<b_{ma}$ 则交换 $a$ 和 $b$。这样可以保证最大值在 $a$ 节点上，减少分讨情况。

新节点的 $ma$ 已经确定为 $a_{ma}$。

而对于 $a$ 和 $b$ 的合并，新节点 $se$ 有以下几种情况：

1. $a_{ma}=b_{ma}>a_{se}=b_{se}$：这时 $se$ 为 $a_{se}$。
2. $a_{ma}=b_{ma}>a_{se}>b_{se}$：这时 $se$ 为 $a_{se}$。
3. $a_{ma}>b_{ma}>a_{se}=b_{se}$：这时 $se$ 为 $b_{ma}$。
4. $a_{ma}>a_{se}=b_{ma}>b_{se}$：这时 $se$ 为 $a_{se}$。
5. $a_{ma}>b_{ma}>b_{se}>a_{se}$：这时 $se$ 为 $b_{ma}$。
1. $a_{ma}>a_{se}>b_{ma}>b_{se}$：这时 $se$ 为 $a_{se}$。

而统计个数只需要将相同的值个数相加就行了。

```cpp
inline segment_node merge(segment_node a,segment_node b){
		segment_node ret;
		if(a.ma<b.ma)	swap(a,b);
		if(a.se>=b.ma){
			ret=a;
			if(a.se==b.ma)	ret.senum+=b.manum;
		}else if(a.se>=b.se){
			if(a.ma==b.ma){
				ret=a;ret.manum+=b.manum;
				if(a.se==b.se)	ret.senum+=b.senum;
			}else	ret={a.ma,b.ma,a.manum,b.manum};
		}else{
			if(a.ma==b.ma)	ret={a.ma,b.se,a.manum+b.manum,b.senum};
			else	ret={a.ma,b.ma,a.manum,b.manum};
		}
		return ret;
	}
```
接下来就是正常线段树的操作了。

### code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int n,m,a[N];
struct segment_tree{
	struct segment_node{int ma,se,manum,senum;}t[N<<2];
	inline int ls(int x){return x<<1;}
	inline int rs(int x){return x<<1|1;}
	inline segment_node merge(segment_node a,segment_node b){
		segment_node ret;
		if(a.ma<b.ma)	swap(a,b);
		if(a.se>=b.ma){
			ret=a;
			if(a.se==b.ma)	ret.senum+=b.manum;
		}else if(a.se>=b.se){
			if(a.ma==b.ma){
				ret=a;ret.manum+=b.manum;
				if(a.se==b.se)	ret.senum+=b.senum;
			}else	ret={a.ma,b.ma,a.manum,b.manum};
		}else{
			if(a.ma==b.ma)	ret={a.ma,b.se,a.manum+b.manum,b.senum};
			else	ret={a.ma,b.ma,a.manum,b.manum};
		}
		return ret;
	}
	void push_up(int x){t[x]=merge(t[ls(x)],t[rs(x)]);}
	void build(int p,int l,int r){
		if(l==r){
			t[p].ma=a[l],t[p].manum=1;
			t[p].se=0,t[p].senum=0;
		}else{
			int mid=(l+r)>>1;
			build(ls(p),l,mid);
			build(rs(p),mid+1,r);
			push_up(p);
		}
	}
	void change(int p,int l,int r,int pos,int val){
		if(l==r)	t[p].ma=val;
		else{
			int mid=(l+r)>>1;
			if(pos<=mid)	change(ls(p),l,mid,pos,val);
			else	change(rs(p),mid+1,r,pos,val);
			push_up(p);
		}
	}
	segment_node query(int p,int l,int r,int re_l,int re_r){
		if(re_l<=l&&r<=re_r)	return t[p];
		else if(!(r<re_l||l>re_r)){
			int mid=(l+r)>>1;
			return merge(query(ls(p),l,mid,re_l,re_r),query(rs(p),mid+1,r,re_l,re_r));
		}else	return {0,0,0,0};
	}
}T;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)	cin>>a[i];
	T.build(1,1,n);
	for(int i=1,opt,l,r;i<=m;i++){
		cin>>opt>>l>>r;
		if(opt==1)	T.change(1,1,n,l,r);
		else	cout<<T.query(1,1,n,l,r).senum<<"\n";
	}
}
```

---

## 作者：FReQuenter (赞：0)

单点修改区间查询，考虑线段树。

考虑需要维护什么：区间次大值的数量涉及到四个量：最大值、次大值、最大值数量、次大值数量。有了这四个就可以完成 `pushup` 了。转移的时候判断新区间的四个值依次继承哪一个即可。注意判断两个儿子区间最大值或次大值之间相等的时候需要累加各自值的数量。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct pre{
	int val,sum;
};
struct node{
	pre maxn,sub;
}tree[800005];
node pushup(node a,node b){
	node ans;
	if(a.maxn.val==b.maxn.val){
		ans.maxn=a.maxn;
		ans.maxn.sum+=b.maxn.sum;
		if(a.sub.val==b.sub.val) ans.sub=a.sub,ans.sub.sum+=b.sub.sum;
		else if(a.sub.val>b.sub.val) ans.sub=a.sub;
		else ans.sub=b.sub;
	}
	else{
		if(a.maxn.val<b.maxn.val) swap(a,b);
		ans.maxn=a.maxn;
		if(a.sub.val>b.maxn.val) ans.sub=a.sub;
		else if(a.sub.val==b.maxn.val) ans.sub=a.sub,ans.sub.sum+=b.maxn.sum;
		else ans.sub=b.maxn;
	}
	return ans;
}
int n,q,a[200005];
void build(int root,int l,int r){
	if(l==r){
		tree[root].maxn=(pre){a[l],1};
		tree[root].sub=(pre){-1,0};
		return;
	}
	int mid=(l+r)>>1;
	build(root<<1,l,mid);
	build(root<<1|1,mid+1,r);
	tree[root]=pushup(tree[root<<1],tree[root<<1|1]);
}
void update(int root,int l,int r,int x,int v){
	if(l==r){
		a[l]=v;
		tree[root].maxn=(pre){a[l],1};
		tree[root].sub=(pre){-1,0};
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid) update(root<<1,l,mid,x,v);
	else update(root<<1|1,mid+1,r,x,v);
	tree[root]=pushup(tree[root<<1],tree[root<<1|1]);
}
node query(int root,int l,int r,int ql,int qr){
	if(ql<=l&&qr>=r) return tree[root];
	int mid=(l+r)>>1;
	if(qr<=mid) return query(root<<1,l,mid,ql,qr);
	if(ql>mid) return query(root<<1|1,mid+1,r,ql,qr);
	return pushup(query(root<<1,l,mid,ql,qr),query(root<<1|1,mid+1,r,ql,qr));
}
signed main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];
	build(1,1,n);
	while(q--){
		int op,x,y;
		cin>>op>>x>>y;
		if(op==1) update(1,1,n,x,y);
		else{
			node res=query(1,1,n,x,y);
			cout<<res.sub.sum<<'\n';
		}
	}
}
```

---

## 作者：PikachuQAQ (赞：0)

## **Description**

给一长为 $n$ 的序列 $a$，有 $q$ 次操作。

- $op=1$，给定两个数 $x,y$，表示将 $a_x$ 修改为 $y$。

- $op=2$，给定两个数 $l,r$，求 $[l,r]$ 区间内 **严格次大值** 的出现次数。

[**Link**](https://atcoder.jp/contests/abc343/tasks/abc343_f)

## **Solution**

不妨将询问区间拆成 $[l,m]$ 和 $[m,r]$，如果我们知道两个区间分别的最大值和次大值与它们的出现次数，那么我们将它们的值比较，求出新的 $[l,r]$ 区间内的最大值和次大值及出现次数，更新到区间 $[l,r]$ 中即可。

对于这种单点修改，区间查询的操作，我们可以考虑使用线段树解决。

## **Code**

```cpp
// 2024/3/5 PikachuQAQ

#include <atcoder/segtree>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using namespace std;
using namespace atcoder;
using ll = long long;
using PLL = pair<ll, ll>;

const int kMaxN = 2e5 + 7;

struct S {
    ll max1, cnt1, max2, cnt2;
};

S op(S x, S y) {
    map<ll, ll> b; vector<PLL> v;
    b[x.max1] += x.cnt1, b[x.max2] += x.cnt2;
    b[y.max1] += y.cnt1, b[y.max2] += y.cnt2;
    for (auto x : b) v.push_back(x);
    sort(v.rbegin(), v.rend());
    auto [m1, c1] = v[0]; auto [m2, c2] = v[1];
    return {m1, c1, m2, c2};
}

S e() { return {0, 0, 0, 0}; }

int n, q;
vector<S> a(kMaxN);

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].max1, a[i].cnt1 = 1;
    }
    segtree<S, op, e> s(a);
    for (int o, l, r; q--; ) {
        cin >> o >> l >> r;
        if (o == 1) {
            s.set(l, {r, 1, 0, 0});
        } else {
            cout << s.prod(l, r + 1).cnt2 << '\n';
        }
    }

    return 0;
}
```

---

## 作者：cosf (赞：0)

## [ABC343F](https://www.luogu.com.cn/problem/AT_abc343_f)

线段树板子。

既然要求次大值，我们就把最大值和次大值都记录了。

> 为什么？因为如果某个数的排名 $> 2$，它就一定不会成为次大值，而对于一个最大值，如果合并时有一个更大的，它就会变成次大值。

于是，我们就维护四个值：最大值、最大值个数、次大值、次大值个数。然后在合并的时候，我们先算出合并后的最大值和次大值，然后把相应的个数加起来就可以了。

除了合并稍有难写，其他就是板子。

## 代码

```cpp
#include <algorithm>
#include <iostream>
using namespace std;

#define MAXN 200005

struct Tree
{
    int f, s;
    int fc, sc;
} t[MAXN << 2];

int n, q;

int val[MAXN];

Tree merge(Tree a, Tree b)
{
    int s[5] = {a.f, a.s, b.f, b.s};
    sort(s, s + 4, greater<int>());
    *unique(s, s + 4) = 0;
    Tree res = {s[0], s[1], 0, 0};
    if (a.f == res.f)
    {
        res.fc += a.fc;
        if (a.s == res.s)
        {
            res.sc += a.sc;
        }
    }
    else if (a.f == res.s)
    {
        res.sc += a.fc;
    }
    if (b.f == res.f)
    {
        res.fc += b.fc;
        if (b.s == res.s)
        {
            res.sc += b.sc;
        }
    }
    else if (b.f == res.s)
    {
        res.sc += b.fc;
    }
    return res;
}

void pushup(int p)
{
    t[p] = merge(t[p << 1], t[p << 1 | 1]);
}

void build(int p, int l, int r)
{
    if (l == r)
    {
        t[p].f = val[l];
        t[p].fc = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

void update(int p, int l, int r, int q, int x)
{
    if (l == r)
    {
        t[p].f = x;
        t[p].fc = 1;
        return;
    }
    int mid = (l + r) >> 1;
    if (mid >= q)
    {
        update(p << 1, l, mid, q, x);
    }
    else
    {
        update(p << 1 | 1, mid + 1, r, q, x);
    }
    pushup(p);
}

Tree query(int p, int l, int r, int ql, int qr)
{
    // cout << l << ' ' << r << ' ' << t[p].f << ' ' << t[p].fc << ' ' << t[p].s << ' ' << t[p].sc << endl;
    if (ql <= l && r <= qr)
    {
        return t[p];
    }
    int mid = (l + r) >> 1;
    Tree res = {0, 0, 0, 0};
    if (mid >= ql)
    {
        res = merge(res, query(p << 1, l, mid, ql, qr));
    }
    if (mid < qr)
    {
        res = merge(res, query(p << 1 | 1, mid + 1, r, ql, qr));
    }
    return res;
}

int main()
{
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
    {
        cin >> val[i];
    }
    build(1, 1, n);
    while (q--)
    {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 1)
        {
            update(1, 1, n, l, r);
        }
        else
        {
            cout << query(1, 1, n, l, r).sc << endl;
        }
    }
    return 0;
}

```

---

## 作者：MrPython (赞：0)

**分块好闪，拜谢分块！**

我们需要支持三种操作：
- 单点修改
- 查询区间最/次大值
- 查询区间内元素出现的数量

对于每个块，我们用数组存下数据，记录这个块的最大和次大值，再用一个 `unordered_map` 存下块中某个数出现的次数。

- 单点修改时，同步操作 `unordered_map` 的数据，再重新计算整个块的最大值。
- 查询整块的区间最/次大值，将存好的最大值和次大值拿出来返回就行。而散块需要重新遍历一遍。合并数据块时，我偷了个懒，把两部分的数据放到数组 $a$ 内：计算过程可以保证 $a_0\ge a_1$，$a_2\ge a_3$，因此可以使用 [`std::inplace_merge`](https://zh.cppreference.com/w/cpp/algorithm/inplace_merge) 线性合并，再用 [`std::unique`](https://zh.cppreference.com/w/cpp/algorithm/unique) 去重。
- 查询区间内元素出现的数量，对整块无脑 `unordered_map`，散块再扫一遍，全部加起来就是了。

注意：
- 本题有点小卡，对于大常数选手可能需要调整块的数量。我使用了 300。
- 使用 `std::unordered_map` 存放的值为整数，则调用 [`std::unordered_map::opearator[]`](https://zh.cppreference.com/w/cpp/container/unordered_map/operator_at) 遇到不存在的元素会默认插入一个 0。计数元素时可能频繁获取块内根本不存在的元素，`unordered_map` 内会有很多垃圾数据，十分影响效率。我的解决方案是用 [`std::unordered_map::find`](https://zh.cppreference.com/w/cpp/container/unordered_map/find) 获取该元素的迭代器。若返回值等于 `std::unordered_map::end` 返回的迭代器则说明里面不存在该元素，返回 0。否则，该迭代器指向一个 `pair`，我们需要返回他的 `second` 成员。

```cpp
#include<bits/extc++.h>
using namespace std;
namespace pbds=__gnu_pbds;
using ui=unsigned int;
using uli=unsigned long long int;
using li=long long int;
using li=long long int;
template<typename T> struct decompose{
    struct block{
        size_t invl,invr;
        vector<T> data;T max1st,max2nd;size_t count2nd;
        unordered_map<T,size_t> c;
        template<typename RandomIterator> block(RandomIterator it,size_t l,size_t r)
            :invl(l),invr(r),data(it,it+(r-l)){for (T i:data) ++c[i];update();}
        void update(void){
            max1st=numeric_limits<T>::min(),max2nd=numeric_limits<T>::min();
            for (T i:data)
                if (i>max1st) max2nd=max1st,max1st=i;
                else if (i<max1st&&i>max2nd) max2nd=i;
            return;
        }
        void set(size_t p,T x){--c[data[p-invl]];++c[data[p-invl]=x];update();}
        pair<T,T> get_max(size_t l,size_t r){
            if (l<=invl&&invr<=r){
                return {max1st,max2nd};
            }
            l=max(invl,l),r=min(invr,r);
            pair<T,T> res={numeric_limits<T>::min(),numeric_limits<T>::min()};
            for (size_t i=l;i<r;++i)
                if (data[i-invl]>res.first) res.second=res.first,res.first=data[i-invl];
                else if (data[i-invl]<res.first&&data[i-invl]>res.second) res.second=data[i-invl];
            return res;
        }
        size_t count(size_t l,size_t r,T x){
            if (l<=invl&&invr<=r){
                typename unordered_map<T,size_t>::const_iterator it=c.find(x);
                return it==c.cend()?0:it->second;
            }
            l=max(invl,l),r=min(invr,r);
            size_t cnt=0;
            for (size_t i=l;i<r;++i) cnt+=data[i-invl]==x;
            return cnt;
        }
    };
    size_t n,blk_count,blk_len;
    block* blk;
    decompose(vector<T> const& a):n(a.size()),blk_count(min<size_t>(sqrt(n),300)),
        blk_len((n+blk_count-1)/blk_count),blk((block*)(operator new[](sizeof(block)*blk_count))){
        size_t i=0;typename vector<T>::const_iterator it=a.cbegin();
        for (;i+1<blk_count;++i,it+=blk_len)
            new(blk+i)block(it,i*blk_len,(i+1)*blk_len);
        new(blk+i)block(it,i*blk_len,n);
    }
    void set(size_t p,T x){blk[p/blk_len].set(p,x);}
    pair<T,T> get_max(size_t l,size_t r){
        size_t ld=l/blk_len,rd=(r+blk_len-1)/blk_len;
        array<T,4> s={numeric_limits<T>::min(),numeric_limits<T>::min()};
        for (size_t i=ld;i<rd;++i){
            pair<T,T> t=blk[i].get_max(l,r);
            s[2]=t.first,s[3]=t.second;
            inplace_merge(s.begin(),s.begin()+2,s.end(),greater<T>());
            typename array<T,4>::iterator x=unique(s.begin(),s.end());
            if (x-s.begin()==1) s[1]=numeric_limits<T>::min();
        }
        return {s[0],s[1]};
    }
    size_t count(size_t l,size_t r,T x){
        size_t ld=l/blk_len,rd=(r+blk_len-1)/blk_len;
        size_t res=0;
        for (size_t i=ld;i<rd;++i) res+=blk[i].count(l,r,x);
        return res;
    }
    ~decompose(void){
        for (size_t i=0;i<blk_count;++i) blk[i].~block();
        operator delete[](blk,sizeof(block)*blk_count);
    }
};
int main(void){
    ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    size_t n,m;cin>>n>>m;
    vector<ui> a(n);for (ui& i:a) cin>>i;
    decompose<ui> ds(a);
    while (m--){
        char c;cin>>c;
        if (c=='1'){
            size_t p;ui x;cin>>p>>x;ds.set(--p,x);
        }else if (c=='2'){
            size_t l,r;cin>>l>>r;--l;
            cout<<ds.count(l,r,ds.get_max(l,r).second)<<'\n';
        }
    }
    
    return 0;
}
```

---

## 作者：可爱的小棉羊 (赞：0)

很板子的线段树维护。

### 题目大意

一个数列，单点修改，区间求次大值个数。

### 思路

首先我们得会线段树，不会的请出门右转前往 [P3372](https://www.luogu.com.cn/problem/P3372)。

我们不妨先想如何求区间次大值

显然假如我们只维护次大值是不行的。

因为合并两区间时我们可能出现左区间的最大值比右区间的最大值小，次大值大等各种无法合并的情况。

我们可以维护区间的最大和次大值，合并会有两种情况：

1. 最大值相等，则次大值取 MAX。

1. 最大值不相等，则小的最大值和大的次大值取 MAX。

就这样。

加入维护最大和次大的个数也很简单：

1. 相等个数相加

1. 不等，个数继承的大的数的个数

就做完了。

~~（合并答案，我的代码贼烂，不要学）~~

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int l,r;
	int maxn,cnt1;
	int max2,cnt2;
}v[800005];
struct Node{
	int maxn,max2,cnt1,cnt2;
};
int n,q; 
void push_up(int rt){
	v[rt].maxn=max(v[rt<<1].maxn,v[rt<<1|1].maxn);
	if(v[rt<<1].maxn==v[rt<<1|1].maxn){
		v[rt].cnt1=v[rt<<1].cnt1+v[rt<<1|1].cnt1;
		if(v[rt<<1].max2==v[rt<<1|1].max2){
			v[rt].cnt2=v[rt<<1].cnt2+v[rt<<1|1].cnt2;
			v[rt].max2=v[rt<<1].max2;
		}else if(v[rt<<1].max2<v[rt<<1|1].max2){
			v[rt].max2=v[rt<<1|1].max2;
			v[rt].cnt2=v[rt<<1|1].cnt2;
		}else{
			v[rt].max2=v[rt<<1].max2;
			v[rt].cnt2=v[rt<<1].cnt2;
		}
	}else if(v[rt<<1].maxn<v[rt<<1|1].maxn){
		v[rt].cnt1=v[rt<<1|1].cnt1;
		if(v[rt<<1].maxn==v[rt<<1|1].max2){
			v[rt].max2=v[rt<<1|1].max2;
			v[rt].cnt2=v[rt<<1|1].cnt2+v[rt<<1].cnt1;
		}else if(v[rt<<1].maxn>v[rt<<1|1].max2){
			v[rt].max2=v[rt<<1].maxn;
			v[rt].cnt2=v[rt<<1].cnt1;
		}else{
			v[rt].max2=v[rt<<1|1].max2;
			v[rt].cnt2=v[rt<<1|1].cnt2;
		}
	}else{
		v[rt].cnt1=v[rt<<1].cnt1;
		if(v[rt<<1|1].maxn==v[rt<<1].max2){
			v[rt].max2=v[rt<<1].max2;
			v[rt].cnt2=v[rt<<1].cnt2+v[rt<<1|1].cnt1;
		}else if(v[rt<<1|1].maxn>v[rt<<1].max2){
			v[rt].max2=v[rt<<1|1].maxn;
			v[rt].cnt2=v[rt<<1|1].cnt1;
		}else{
			v[rt].max2=v[rt<<1].max2;
			v[rt].cnt2=v[rt<<1].cnt2;
		}
	}
}
void build(int rt,int l,int r){
	v[rt].l=l;
	v[rt].r=r;
	if(l==r){
		cin>>v[rt].maxn;
		v[rt].cnt1=1;
		return;
	}
	int mid=(l+r)>>1;
	build(rt<<1,l,mid);
	build(rt<<1|1,mid+1,r);
	push_up(rt);
} 
void modify(int rt,int x,int k){
	if(v[rt].l==v[rt].r){
		v[rt].maxn=k;
		return;
	}
	int mid=(v[rt].l+v[rt].r)>>1;
	if(x<=mid)modify(rt<<1,x,k);
	else modify(rt<<1|1,x,k);
	push_up(rt);
}
Node ask( int rt,int l,int r){
	if(l<=v[rt].l&&v[rt].r<=r){
		Node ans;
		ans.max2=v[rt].max2;
		ans.maxn=v[rt].maxn;
		ans.cnt1=v[rt].cnt1;
		ans.cnt2=v[rt].cnt2;
		return ans;
	}
	Node ans1,ans2,ans;
	ans1.cnt1=ans1.cnt2=ans1.max2=ans1.maxn=ans2.cnt1=ans2.cnt2=ans2.max2=ans2.maxn=0;
	int mid=(v[rt].l+v[rt].r)>>1;
	if(l<=mid)ans1=ask(rt<<1,l,r);
	if(r>=mid+1)ans2=ask(rt<<1|1,l,r);
	ans.maxn=max(ans1.maxn,ans2.maxn);
	if(ans1.maxn==ans2.maxn){
		ans.cnt1=ans1.cnt1+ans2.cnt1;
		if(ans1.max2==ans2.max2){
			ans.cnt2=ans1.cnt2+ans2.cnt2;
			ans.max2=ans1.max2;
		}else if(ans1.max2<ans2.max2){
			ans.max2=ans2.max2;
			ans.cnt2=ans2.cnt2;
		}else{
			ans.max2=ans1.max2;
			ans.cnt2=ans1.cnt2;
		}
	}else if(ans1.maxn<ans2.maxn){
		ans.cnt1=ans2.cnt1;
		if(ans1.maxn==ans2.max2){
			ans.max2=ans2.max2;
			ans.cnt2=ans2.cnt2+ans1.cnt1;
		}else if(ans1.maxn>ans2.max2){
			ans.max2=ans1.maxn;
			ans.cnt2=ans1.cnt1;
		}else{
			ans.max2=ans2.max2;
			ans.cnt2=ans2.cnt2;
		}
	}else{
		ans.cnt1=ans1.cnt1;
		if(ans2.maxn==ans1.max2){
			ans.max2=ans1.max2;
			ans.cnt2=ans1.cnt2+ans2.cnt1;
		}else if(ans2.maxn>ans1.max2){
			ans.max2=ans2.maxn;
			ans.cnt2=ans2.cnt1;
		}else{
			ans.max2=ans1.max2;
			ans.cnt2=ans1.cnt2;
		}
	}
	
	//cout<<v[rt].l<<" "<<v[rt].r<<" "<<ans.cnt2<<endl;
	return ans;
}
int main(){
	cin>>n>>q;
	build(1,1,n);
	while(q--){
		int opt,x,y;
		cin>>opt>>x>>y;
		if(opt==1)modify(1,x,y);
		else {
			Node ans=ask(1,x,y);
			//cout<<ans.maxn<<" "<<ans.max2<<endl;
			if(ans.max2==0)cout<<0<<endl;
			else cout<<ans.cnt2<<endl;
		}
	}
	return 0;
}

```

---

## 作者：harmis_yz (赞：0)

## 分析

考虑乱搞。

对于求次大值，用线段树维护就行了。记录下每个区间的最大、次大值。则两个子区间的父区间的最大值就是这四个最大的，次大值就是这四个次大的。复杂度 $O(\log n)$。

求次大值的出现次数，乱搞就行了。因为带修，带修莫队或者分块有些麻烦。其实用线段树就行。在维护区间最大、次大值的时候，直接同时维护一下它们对应的出现次数，然后就是一个区间和的问题。复杂度 $O(\log n)$。

所以总的复杂度为 $O(n \log n)$。~~不会有人去写莫队吧。~~

## 代码

[这是带修莫队的代码](https://atcoder.jp/contests/abc343/submissions/50822347)。

[这是线段树的代码](https://atcoder.jp/contests/abc343/submissions/50897099)。

---

## 作者：yshpdyt (赞：0)

## 题意
维护一个序列，支持单点修改，区间查询次大值出现次数。
## Sol
$\text{Atcoder}$ 特色线段树板题。

维护区间的最大值，次大值，最大值出现次数，次大值出现次数即可。

这样做是显然的，一个区间的最大值显然是两个子区间的最大值较大的那一个，一个区间的次大值，是两个子区间最大值较小的那一个，或者次大值最大的那一个，分类讨论一下如何合并区间即可。

非常好重载运算符。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 800005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=1e9+7;
const ll inf=1e18;
const double eps=1e-6;
ll a[N],n;
namespace tr{
    #define mid ((l+r)>>1)
    #define ls (p<<1)
    #define rs (p<<1|1)
    
    struct qwq{
        ll mx,my,nx,ny;
      //最大值，次大值，最大值出现次数，次大值出现次数。
        friend qwq operator+(const qwq &a,const qwq &b){
            qwq c={0,0,0,0};
            if(a.mx>b.mx){
                c.mx=a.mx;
                c.nx=a.nx;
                if(b.mx>a.my){
                    c.my=b.mx;
                    c.ny=b.nx;
                }
                if(b.mx==a.my){
                    c.my=b.mx;
                    c.ny=b.nx+a.ny;
                }
                if(b.mx<a.my){
                    c.my=a.my;
                    c.ny=a.ny;
                }
                return c;
            }
            if(a.mx==b.mx){
                c.mx=a.mx;
                c.nx=a.nx+b.nx;
                if(b.my>a.my){
                    c.my=b.my;
                    c.ny=b.ny;
                }
                if(b.my==a.my){
                    c.my=b.my;
                    c.ny=b.ny+a.ny;
                }
                if(b.my<a.my){
                    c.my=a.my;
                    c.ny=a.ny;
                }
                return c;
            }
            if(a.mx<b.mx){
                c.mx=b.mx;
                c.nx=b.nx;
                if(b.my>a.mx){
                    c.my=b.my;
                    c.ny=b.ny;
                }
                if(b.my==a.mx){
                    c.my=b.my;
                    c.ny=b.ny+a.nx;
                }
                if(b.my<a.mx){
                    c.my=a.mx;
                    c.ny=a.nx;
                }
                return c;
            }
        }
    }tr[N];
    void build(ll p,ll l,ll r){
        if(l==r){
            tr[p].mx=a[l];
            tr[p].my=0;
            tr[p].nx=1;
            tr[p].ny=0;
            return ;
        }
        build(ls,l,mid);
        build(rs,mid+1,r);
        tr[p]=tr[ls]+tr[rs];
    }
    void upd(ll p,ll l,ll r,ll x,ll t){
        if(l==r){
            tr[p].mx=t;
            tr[p].my=0;
            tr[p].nx=1;
            tr[p].ny=0;
            return ;
        }
        if(x<=mid)upd(ls,l,mid,x,t);
        if(x>mid)upd(rs,mid+1,r,x,t);
        tr[p]=tr[ls]+tr[rs];
    }
    qwq qr(ll p,ll l,ll r,ll le,ll ri){
        if(le<=l&&ri>=r)return tr[p];
        if(le<=mid&&ri>mid)return qr(ls,l,mid,le,ri)+qr(rs,mid+1,r,le,ri);
        if(le<=mid)return qr(ls,l,mid,le,ri);
        if(ri>mid)return qr(rs,mid+1,r,le,ri);
        return {0,0,0,0};
    }
}
ll m=0;
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    tr::build(1,1,n);
    while(m--){
        ll op,x,y;
        cin>>op>>x>>y;
        if(op==1){
            tr::upd(1,1,n,x,y);
        }else cout<<tr::qr(1,1,n,x,y).ny<<endl;
    }
    return 0;
}
```

---

## 作者：eb0ycn (赞：0)

传送门：[AT_abc343_f](https://www.luogu.com.cn/problem/AT_abc343_f)。

赛时看到 E 题过的人只有 F 的十分之一，就果断来切这题，写了个分块做法，但是十一点才调出来……

## 题意

依次进行 $q$ 次操作，操作一修改一个数，操作二询问区间严格次大值出现的次数。

## 思路

听说这题可以用线段树，但我不怎么会写，只能奉上优雅的暴力——分块。

先考虑一个区间的次大值怎么求。

假设到了第 $i$ 个数 $a_i$ 时目前的最大值为 $retzd$，次大值为 $retcd$，则：

- 若 $a_i > retzd$，$retcd \gets retzd$，$retzd \gets a_i$；
- 否则，若 $a_i > retcd$，$retcd \gets a_i$。

现在加上最大值和次大值的数量也是类似的。直接套分块就行了。理论上时间复杂度 $O(q \sqrt{n} +n)$。这里我偷懒，直接令块长为 $500$，时间复杂度可能会高一点。

## 代码（有点屎）

```cpp
#include <cstdio>
using namespace std;
int a[401][501],zd[401],cd[401],zdcnt[401],cdcnt[401],n,q,tot,res,op,l,r,now,l1,l2,r1,r2,retzd,retcd,retzdcnt,retcdcnt;
int main(){
	scanf("%d%d",&n,&q);for(int i=1;i<=n;++i)scanf("%d",&a[(i-1)/500+1][(i-1)%500+1]);
	tot=(n-1)/500+1,res=(n-1)%500+1;
	for(int i=1;i<tot;++i){
		for(int j=1;j<501;++j){
			if(a[i][j]>zd[i])cd[i]=zd[i],cdcnt[i]=zdcnt[i],zd[i]=a[i][j],zdcnt[i]=1;
			else if(a[i][j]==zd[i])++zdcnt[i];
			else if(a[i][j]>cd[i])cd[i]=a[i][j],cdcnt[i]=1;
			else if(a[i][j]==cd[i])++cdcnt[i];
		}
	}
	for(int j=1;j<=res;++j){
		if(a[tot][j]>zd[tot])cd[tot]=zd[tot],cdcnt[tot]=zdcnt[tot],zd[tot]=a[tot][j],zdcnt[tot]=1;
		else if(a[tot][j]==zd[tot])++zdcnt[tot];
		else if(a[tot][j]>cd[tot])cd[tot]=a[tot][j],cdcnt[tot]=1;
		else if(a[tot][j]==cd[tot])++cdcnt[tot];
	}
	while(q--){
		scanf("%d%d%d",&op,&l,&r);
		if(op==1){now=(l-1)/500+1,a[now][(l-1)%500+1]=r,zd[now]=cd[now]=zdcnt[now]=cdcnt[now]=0;
			if(now==tot){
				for(int j=1;j<=res;++j){
					if(a[tot][j]>zd[tot])cd[tot]=zd[tot],cdcnt[tot]=zdcnt[tot],zd[tot]=a[tot][j],zdcnt[tot]=1;
					else if(a[tot][j]==zd[tot])++zdcnt[tot];
					else if(a[tot][j]>cd[tot])cd[tot]=a[tot][j],cdcnt[tot]=1;
					else if(a[tot][j]==cd[tot])++cdcnt[tot];
				}
			}else{
				for(int j=1;j<501;++j){
					if(a[now][j]>zd[now])cd[now]=zd[now],cdcnt[now]=zdcnt[now],zd[now]=a[now][j],zdcnt[now]=1;
					else if(a[now][j]==zd[now])++zdcnt[now];
					else if(a[now][j]>cd[now])cd[now]=a[now][j],cdcnt[now]=1;
					else if(a[now][j]==cd[now])++cdcnt[now];
				}
			}
		}
		if(op==2){l1=(l-1)/500+1,l2=(l-1)%500+1,r1=(r-1)/500+1,r2=(r-1)%500+1,retzd=retcd=retzdcnt=retcdcnt=0;
			if(l1==r1){
				for(int i=l2;i<=r2;++i){
					if(a[l1][i]>retzd)retcd=retzd,retcdcnt=retzdcnt,retzd=a[l1][i],retzdcnt=1;
					else if(a[l1][i]==retzd)++retzdcnt;
					else if(a[l1][i]>retcd)retcd=a[l1][i],retcdcnt=1;
					else if(a[l1][i]==retcd)++retcdcnt;
				}
			}else{
				for(int i=l2;i<501;++i){
					if(a[l1][i]>retzd)retcd=retzd,retcdcnt=retzdcnt,retzd=a[l1][i],retzdcnt=1;
					else if(a[l1][i]==retzd)++retzdcnt;
					else if(a[l1][i]>retcd)retcd=a[l1][i],retcdcnt=1;
					else if(a[l1][i]==retcd)++retcdcnt;
				}for(int i=l1+1;i<r1;++i){
					if(zd[i]>retzd)retcd=retzd,retcdcnt=retzdcnt,retzd=zd[i],retzdcnt=zdcnt[i];
					else if(zd[i]==retzd)retzdcnt+=zdcnt[i];
					else if(zd[i]>retcd)retcd=zd[i],retcdcnt=zdcnt[i];
					else if(zd[i]==retcd)retcdcnt+=zdcnt[i];
					if(cd[i]>retcd)retcd=cd[i],retcdcnt=cdcnt[i];
					else if(cd[i]==retcd)retcdcnt+=cdcnt[i];
				}
				for(int i=1;i<=r2;++i){
					if(a[r1][i]>retzd)retcd=retzd,retcdcnt=retzdcnt,retzd=a[r1][i],retzdcnt=1;
					else if(a[r1][i]==retzd)++retzdcnt;
					else if(a[r1][i]>retcd)retcd=a[r1][i],retcdcnt=1;
					else if(a[r1][i]==retcd)++retcdcnt;
				}
			}printf("%d\n",retcdcnt);
		}
	}
	return 0;
}
```

---

## 作者：kkxacj (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc343_f)

**思路**

先假设是求最大值出现的次数，不难想到用线段数维护最大值和最大值出现的次数，可以考虑用 `map` 存次数，由于只有 $n$ 个数，每次是单点修改，最多多用 $q$ 个空间，所以不会超空间，
更新代码如下：
```cpp
void push(int p)
{
	c[p].m.clear();//重新计算 
	c[p].ma = max(c[p * 2].ma,c[p * 2 + 1].ma);//取最大值 
	if(c[p * 2].ma == c[p].ma) c[p].m[c[p].ma] += c[p * 2].m[c[p].ma];//加上左半边出现次数 
	if(c[p * 2 + 1].ma == c[p].ma) c[p].m[c[p].ma] += c[p * 2 + 1].m[c[p].ma];//同理，加右半边出现次数 
}
```
那次大值出现次数怎么办呢？

不难想到同时维护最大值和次大值就行了，次大值维护与上面类似，但注意**次大值是严格小于最大值，也就是两个不等**，所以注意判断一下，然后就没有了。

**code**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,a[200010],op,x,y,ans;
struct w
{
	int ma,ma1,l,r;
	map<int,int>m;
}c[1000010];
void push(int p)
{
	c[p].m.clear();//重新计算 
	c[p].ma = max(c[p * 2].ma,c[p * 2 + 1].ma); c[p].ma1 = 0;//一定要清零 
	if(c[p * 2].ma == c[p].ma) c[p].m[c[p].ma] += c[p * 2].m[c[p].ma]; 
	else c[p].ma1 = max(c[p * 2].ma,c[p].ma1);
	if(c[p * 2 + 1].ma == c[p].ma) c[p].m[c[p].ma] += c[p * 2 + 1].m[c[p].ma]; 
	else c[p].ma1 = max(c[p * 2 + 1].ma,c[p].ma1);	
	if(c[p * 2 + 1].ma1 != c[p].ma) c[p].ma1 = max(c[p * 2 + 1].ma1,c[p].ma1);
	if(c[p * 2].ma1 != c[p].ma) c[p].ma1 = max(c[p * 2].ma1,c[p].ma1);
	//次大值更新 
	if(c[p * 2 + 1].ma1 == c[p].ma1) c[p].m[c[p].ma1] += c[p * 2 + 1].m[c[p].ma1];
	if(c[p * 2].ma1 == c[p].ma1) c[p].m[c[p].ma1] += c[p * 2].m[c[p].ma1];
	if(c[p * 2 + 1].ma == c[p].ma1) c[p].m[c[p].ma1] += c[p * 2 + 1].m[c[p].ma1];
	if(c[p * 2].ma == c[p].ma1) c[p].m[c[p].ma1] += c[p * 2].m[c[p].ma1];
}
void biuld(int p,int l,int r)
{
	c[p].l = l,c[p].r = r;
	if(l == r)
	{
		c[p].ma = a[l];
		c[p].m[c[p].ma] = 1;
		return;
	}
	int mid = (l + r) >> 1;
	biuld(p * 2,l,mid); biuld(p * 2 + 1,mid + 1,r);
	push(p); 
}
void change(int p,int l,int k)
{
	if(c[p].l == c[p].r && l == c[p].l)
	{
		c[p].m[c[p].ma]--;
		c[p].ma = k;
		c[p].m[c[p].ma]++;
		return;
	}
	int mid = (c[p].l + c[p].r) >> 1;
	if(l <= mid) change(p * 2,l,k);
	else change(p * 2 + 1,l,k);
	push(p);
}
pair<int,int> Get_(int p,int l,int r)//l到r的次大值是多少 
{
	int Ma = -1,Ma1 = -1,ma,ma1;
	pair<int,int>as;
	if(l <= c[p].l && c[p].r <= r) return make_pair(c[p].ma,c[p].ma1);
	int mid = (c[p].l + c[p].r) >> 1;
	if(l <= mid)
	{
		as = Get_(p * 2,l,r);
		ma = Ma,ma1 = Ma1;
		Ma = max(ma,as.first);
		if(ma == as.first) Ma1 = max(ma1,as.second);//ma == as.first，但因为不能算重，所以与第二个比较 
		else if(ma == Ma) Ma1 = max(ma1,as.first);//ma > as.first，与第一个比较 
		else Ma1 = max(ma,as.second);//ma < as.first，最大值取了第一个，与第二个比较 
	}
	if(mid < r)
	{
		as = Get_(p * 2 + 1,l,r);
		ma = Ma,ma1 = Ma1;
		Ma = max(ma,as.first);
		if(ma == as.first) Ma1 = max(ma1,as.second);//同理 
		else if(ma == Ma) Ma1 = max(ma1,as.first);
		else Ma1 = max(ma,as.second);
	}
	return make_pair(Ma,Ma1);
}
void ask(int p,int l,int r,int k)
{
	if(l <= c[p].l && c[p].r <= r)
	{
		ans += c[p].m[k];
		return;
	}
	int mid = (c[p].l + c[p].r) >> 1;
	if(l <= mid) ask(p * 2,l,r,k);
	if(mid < r) ask(p * 2 + 1,l,r,k);
}
signed main() 
{
	scanf("%d%d",&n,&q);
	for(int i = 1;i <= n;i++) scanf("%d",&a[i]);
	biuld(1,1,n);
	for(int i = 1;i <= q;i++)
	{
		scanf("%d%d%d",&op,&x,&y);
		if(op == 1) change(1,x,y);
		else
		{
			ans = 0;
			ask(1,x,y,Get_(1,x,y).second);
			printf("%d\n",ans);
		}
	}
	return 0;
}
```

---

## 作者：zhangjiting (赞：0)

## 思路

最近 ABC 全是线段树，所以看到 ABC 的数据结构题首先想到线段树。

对于每个结点，记录 $sum1,sum2,cnt1,cnt2$ 分别表示最大值，次大值及对应的出现次数。`push_up` 直接分类讨论，一共九种情况，非常简单，不再解释。

剩下的就是常规线段树操作了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
struct node{
	int l,r,sum1,sum2,cnt1,cnt2;
}tree[N<<2];
int n,m,a[N];
void push_up(node& c,node a,node b){
	if(a.sum1==b.sum1){
        c.sum1=a.sum1;
        c.cnt1=a.cnt1+b.cnt1;
        if(a.sum2==b.sum2){
            c.sum2=a.sum2;
            c.cnt2=a.cnt2+b.cnt2;
        }
        else if(a.sum2>b.sum2){
            c.sum2=a.sum2;
            c.cnt2=a.cnt2;
        }
        else if(a.sum2<b.sum2){
            c.sum2=b.sum2;
            c.cnt2=b.cnt2;
        }
    }
    else if(a.sum1>b.sum1){
        c.sum1=a.sum1;
        c.cnt1=a.cnt1;
        if(a.sum2==b.sum1){
            c.sum2=a.sum2;
            c.cnt2=a.cnt2+b.cnt1;
        }
        else if(a.sum2>b.sum1){
            c.sum2=a.sum2;
            c.cnt2=a.cnt2;
        }
        else if(a.sum2<b.sum1){
            c.sum2=b.sum1;
            c.cnt2=b.cnt1;
        }
    }
    else if(a.sum1<b.sum1){
        c.sum1=b.sum1;
        c.cnt1=b.cnt1;
        if(a.sum1==b.sum2){
            c.sum2=a.sum1;
            c.cnt2=a.cnt1+b.cnt2;
        }
        else if(a.sum1>b.sum2){
            c.sum2=a.sum1;
            c.cnt2=a.cnt1;
        }
        else if(a.sum1<b.sum2){
            c.sum2=b.sum2;
            c.cnt2=b.cnt2;
        }
    }
}
void build(int p,int l,int r){
	if(l==r){
		tree[p]=(node){l,r,a[l],0,1,0};
		return;
	}
	tree[p]={l,r};
	int mid=(l+r)>>1;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	push_up(tree[p],tree[p*2],tree[p*2+1]);
}
void change(int p,int x,int y){
	if(tree[p].l==tree[p].r&&tree[p].l==x){
		tree[p].sum1=y;
		return;
	}
	int mid=(tree[p].l+tree[p].r)>>1,lt=tree[p].l,rt=tree[p].r;
	if(x<=mid) change(p*2,x,y);
	else change(p*2+1,x,y);
	push_up(tree[p],tree[p*2],tree[p*2+1]);
}
node ask(int p,int l,int r){
	if(l<=tree[p].l&&tree[p].r<=r){
		return tree[p];
	}
	int mid=(tree[p].l+tree[p].r)>>1,fl=0,fr=0;
	node lc,rc;
	if(l<=mid){
		lc=ask(p*2,l,r);
		fl=1;
	}
	if(r>mid){
		rc=ask(p*2+1,l,r);
		fr=1;
	}
	if(fl&&fr){
		node res;
		res={l,r};
		push_up(res,lc,rc);
		return res;
	}
	else{
		if(fl) return lc;
		if(fr) return rc;
	}
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	build(1,1,n);
	for(int i=1,op,x,y;i<=m;i++){
		cin>>op>>x>>y;
		if(op==1) change(1,x,y);
		else cout<<ask(1,x,y).cnt2<<endl;
	} 
	return 0;
}

```

---

