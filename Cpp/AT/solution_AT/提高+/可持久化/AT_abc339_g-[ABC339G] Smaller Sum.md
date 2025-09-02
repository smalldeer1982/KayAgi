# [ABC339G] Smaller Sum

## 题目描述

给定一个长度为 $N$ 的数列 $A=(A_1,A_2,\dots,A_N)$。

请回答以下 $Q$ 个查询。第 $i$ 个查询如下：

- 求 $A_{L_i},A_{L_i+1},\dots,A_{R_i}$ 中所有不超过 $X_i$ 的数的总和。

但你需要以在线方式回答这些查询。  
“在线回答查询”是指，在回答某个查询之后，才会得知下一个查询的内容。

因此，第 $i$ 个查询并不会直接给出，而是以加密后的输入 $\alpha_i,\ \beta_i,\ \gamma_i$ 的形式给出。请按照以下步骤还原原本的第 $i$ 个查询并作答。

- 设 $B_0=0$，$B_i=$（第 $i$ 个查询的答案）。
- 此时，可以通过如下方式解密查询：
  - $L_i = \alpha_i \oplus B_{i-1}$
  - $R_i = \beta_i \oplus B_{i-1}$
  - $X_i = \gamma_i \oplus B_{i-1}$

其中，$x \oplus y$ 表示 $x$ 和 $y$ 的按位异或（XOR）。

按位异或（XOR）是这样定义的：对于非负整数 $A,B$，$A \oplus B$ 的二进制表示中，第 $2^k$ 位（$k \geq 0$）的数，如果 $A,B$ 的该位中只有一个为 $1$，则为 $1$，否则为 $0$。

例如，$3 \oplus 5 = 6$（二进制表示为：$011 \oplus 101 = 110$）。

## 说明/提示

### 数据范围

- 所有输入均为整数。
- $1 \leq N \leq 2 \times 10^5$
- $0 \leq A_i \leq 10^9$
- $1 \leq Q \leq 2 \times 10^5$
- 对于加密后的查询，有：
  - $0 \leq \alpha_i,\ \beta_i,\ \gamma_i \leq 10^{18}$
- 对于解密后的查询，有：
  - $1 \leq L_i \leq R_i \leq N$
  - $0 \leq X_i \leq 10^9$

### 样例解释 1

数列为 $A=(2,0,2,4,0,2,0,3)$。该输入包含 $5$ 个查询。

- 初始时，$B_0=0$。
- 第一个查询为 $\alpha=1,\ \beta=8,\ \gamma=3$。
- 解密后 $L_1=1,\ R_1=8,\ X_1=3$。
- 该查询的答案为 $9$，记为 $B_1$。
- 下一个查询为 $\alpha=10,\ \beta=12,\ \gamma=11$。
- 解密后 $L_2=3,\ R_2=5,\ X_2=2$。
- 该查询的答案为 $2$，记为 $B_2$。
- 下一个查询为 $\alpha=3,\ \beta=3,\ \gamma=2$。
- 解密后 $L_3=1,\ R_3=1,\ X_3=0$。
- 该查询的答案为 $0$，记为 $B_3$。
- 下一个查询为 $\alpha=3,\ \beta=6,\ \gamma=5$。
- 解密后 $L_4=3,\ R_4=6,\ X_4=5$。
- 该查询的答案为 $8$，记为 $B_4$。
- 下一个查询为 $\alpha=12,\ \beta=0,\ \gamma=11$。
- 解密后 $L_5=4,\ R_5=8,\ X_5=3$。
- 该查询的答案为 $5$，记为 $B_5$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
8
2 0 2 4 0 2 0 3
5
1 8 3
10 12 11
3 3 2
3 6 5
12 0 11```

### 输出

```
9
2
0
8
5```

# 题解

## 作者：Genius_Star (赞：8)

### 思路：

~~亏大了，赛时没看 G……~~

每次询问 $[l,r]$ 区间内 $\le x$ 的值的元素之和，考虑权值主席树；先将 $a$ 序列进行离散化，然后定义以 $root_i$ 为根的主席树插入了 $a_{1 \sim i}$ 的数。

然后对于每次询问，定义 $h$ 为 $x$ 放在离散化数组上的位置；是对于 $root_r$ 的 $[1,h]$ 内的所有和减去 $root_{l-1}$ 的 $[1,h]$ 内的所有和。

时间复杂度为 $O(N \log N)$。

**注意一下 $h$ 可能为 $0$，这种特判一下，不然放线段树去查询会 TLE 或 RE。**

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=20000005;
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
struct Node{
	ll l,r;
	ll L,R;
	ll data;
}X[N];
ll n,cnt,vum,q,l,r,x,ans;
ll a[N],b[N],h[N],root[N];
void pushup(ll k){
	X[k].data=X[X[k].L].data+X[X[k].R].data;
}
void build(ll &k,ll l,ll r){
	if(!k)
	  k=++vum;
	X[k].l=l,X[k].r=r;
	if(l==r)
	  return ;
	ll mid=(l+r)>>1;
	build(X[k].L,l,mid);
	build(X[k].R,mid+1,r);
}
void add(ll &k,ll i,ll v){
	ll t=k;
	k=++vum;
	X[k]=X[t];
	if(X[k].l==i&&i==X[k].r){
		X[k].data+=v;
		return ;
	}
	ll mid=(X[k].l+X[k].r)>>1;
	if(i<=mid)
	  add(X[k].L,i,v);
	else
	  add(X[k].R,i,v);
	pushup(k);
}
ll qurey(ll k,ll l,ll r){
	if(X[k].l==l&&r==X[k].r)
	  return X[k].data;
	ll mid=(X[k].l+X[k].r)>>1;
	if(r<=mid)
	  return qurey(X[k].L,l,r);
	else if(l>mid)
	  return qurey(X[k].R,l,r);
	else
	  return qurey(X[k].L,l,mid)+qurey(X[k].R,mid+1,r);
}
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		b[++cnt]=a[i];
	}
	sort(b+1,b+cnt+1);
	cnt=unique(b+1,b+cnt+1)-(b+1);
	for(int i=1;i<=n;i++)
	  h[i]=lower_bound(b+1,b+cnt+1,a[i])-b;
	build(root[0],1,n);
	for(int i=1;i<=n;i++){
		root[i]=root[i-1];
		add(root[i],h[i],a[i]);
	}
	q=read();
	while(q--){
		l=read(),r=read(),x=read();
		l^=ans,r^=ans,x^=ans;
		x=upper_bound(b+1,b+cnt+1,x)-(b+1);
		if(l>r)
		  swap(l,r);
		if(!x)
		  ans=0;
		else
		  ans=qurey(root[r],1,x)-qurey(root[l-1],1,x);
		write(ans);
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：WilliamFranklin (赞：3)

### 主要思路

这就是一个十分裸的分块。

我们考虑先离散化，这样可以将数值压缩成 $1$ 到 $2 \times 10^5$。

然后考虑分块，在每一个块上维护一个值域树状数组，这样我们就可以快速统计一个块内小于等于 $x$ 的数的和了。

对于查询非整块的部分，直接暴力算即可。

也没有什么好说的，就是这题卡分块，我将块长调到 $900$ 才过，但是又经过测试，发现块长 $2000$ 的时候跑的最快。

看下代码吧。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define mp(Tx, Ty) make_pair(Tx, Ty)
#define For(Ti, Ta, Tb) for(auto Ti = (Ta); Ti <= (Tb); Ti++)
#define Dec(Ti, Ta, Tb) for(auto Ti = (Ta); Ti >= (Tb); Ti--)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define range(Tx) begin(Tx),end(Tx)
const int N = 2e5 + 5, M = N / 2000 + 5;
long long a[N];
int n, q;
map<int, int> mp;
set<int> st;
long long tr[M][N];
int id[N];
int ll[M], rr[M];
int b[N];
int lowbit(int x) {
	return x & -x;
}
void add(int x, int k) {
	for (int i = x; i <= n; i += lowbit(i)) tr[k][i] += b[x];
}
long long sum(int x, int k) {
	long long res = 0;
	for (int i = x; i; i -= lowbit(i)) res += tr[k][i];
	return res;
}
signed main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n;
	For(i, 1,n ) {
		cin >> a[i];
		st.insert(a[i]);
	}
	auto it = st.begin();
	int m = st.size();
	for (int i = 1; it != st.end(); it++, i++) {
		mp[*it] = i;
		b[i] = *it;
	} 
	for (int i = 1; i <= n; i++) {
		a[i] = mp[a[i]];
	}
	int len = min(n, 2000);
	int k = 1;
	ll[1] = 1;
	rr[1] = 1;
	id[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (i % len == 0) {
			k++;
			ll[k] = i;
		}
		id[i] = k;
		rr[k] = i;
	}
	for (int i = 1; i <= n; i++) {
		add(a[i], id[i]);
	}
	long long last = 0;
	cin >> q;
	while (q--) {
		long long l, r, x;
		cin >> l >> r >> x;
		l ^= last;
		r ^= last;
		x ^= last;
		int w = upper_bound(b + 1, b + m + 1, x) - b;
		x = w - 1;
		long long ans = 0;
		for (int i = id[l] + 1; i < id[r]; i++) {
			ans += sum(x, i);
		}
		if (id[l] == id[r]) {
			for (int i = l; i <= r; i++) {
				if (a[i] <= x) ans += b[a[i]];
			}
		} else {
			for (int i = l; i <= rr[id[l]]; i++) {
				if (a[i] <= x) ans += b[a[i]];
			}
			for (int i = ll[id[r]]; i <= r; i++) {
				if(a[i] <= x) ans += b[a[i]];
			}
		}
		cout << ans << '\n';
		last = ans;
	}
	return 0; 
}
```

### 谢谢观看

---

## 作者：fcy20180201 (赞：3)

## 思路
[原题](https://loj.ac/p/6278)，但那题用分块不卡常，而且求的是个数；这题卡常，而且求和，~~于是不会卡常的蒟蒻（me）就挂了~~。

于是改成暴力的线段树就过了。

线段树上区间 $[l,r]$ 暴力记录这一段数组，然后排序，再搞个前缀和。

询问如果询问到整个的区间 $[l,r]$，暴力在记录的数组上二分，再查找前缀和就完事了。

时间复杂度 $\mathcal O(n \log^2n)$，只要代码写的不是太烂都能过。
## 代码
```cpp
#include<bits/stdc++.h>
#define ls cur<<1
#define rs cur<<1|1
using namespace std;
using ll=long long;
int n,q;
ll a[200005],ans=0;
vector<ll>b[800005],sum[800005];

void build(int cur,int l,int r){
	b[cur].push_back(0),sum[cur].push_back(0);
	//这里注意一下，前缀和最前面如果习惯有 0，那另一个数组前面也要有 0 来统一下标
	if(l==r){b[cur].push_back(a[l]),sum[cur].push_back(a[r]);return ;}
	//叶节点
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	for(int i=1;i<=mid-l+1;i++)b[cur].push_back(b[ls][i]);
	//合并左儿子，记得从 1 开始循环，不要合并上来多余的 0
	for(int i=1;i<=r-mid;i++)b[cur].push_back(b[rs][i]);//合并右儿子
	sort(b[cur].begin(),b[cur].end());
	for(int i=1;i<=r-l+1;i++)sum[cur].push_back(b[cur][i]+sum[cur][i-1]);//前缀和
	return ;
}

ll query(int cur,int l,int r,int ql,int qr,ll val){
	if(ql<=l && r<=qr){
		int loc=upper_bound(b[cur].begin(),b[cur].end(),val)-b[cur].begin()-1;//二分
		return sum[cur][loc];//查找前缀和
	}
	//如果不是查找这一整个区间，把任务分给左右儿子
	int mid=(l+r)>>1;
	ll res=0;
	if(ql<=mid)res+=query(ls,l,mid,ql,qr,val);
	if(qr>mid)res+=query(rs,mid+1,r,ql,qr,val);
	return res;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	build(1,1,n);
	scanf("%d",&q);
	while(q--){
		ll l,r,x;
		scanf("%lld%lld%lld",&l,&r,&x);
		l^=ans,r^=ans,x^=ans;
		ans=query(1,1,n,(int)l,(int)r,x);
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：rainygame (赞：2)

ABC G 题居然出分块板子……

先将 $a_i$ 每 $\sqrt n$ 分为一块。

每次查询时，先暴力查询零散块，复杂度 $O(\sqrt n)$。

对于整块，考虑维护一个块内有序的数组 $b$，那么每次就可以通过二分查找到对应的位置。

可是我们要求和，所以还需要维护一个关于 $b$ 的块内前缀和 $s$，每次查找到对应位置 $i$ 后，$s_i$ 就是该块的贡献。

本人直接设块长为 $\sqrt n$，最慢点 $3.18$ s，还是过的去的。

赛时 AC 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 200001
#define MAXM 450

int n, q;
int a[MAXN], bl[MAXN], b[MAXN];
int L[MAXM], R[MAXM];
long long l, r, x, lans;
long long sum[MAXN];

long long query(){
    int p(bl[l]), q(bl[r]);
    long long res(0);
    if (p == q){
        for (int i(l); i<=r; ++i){
            if (a[i] <= x) res += a[i];
        }
        return res;
    }

    for (int i(l); i<=R[p]; ++i){
        if (a[i] <= x) res += a[i];
    }
    for (int i(L[q]); i<=r; ++i){
        if (a[i] <= x) res += a[i];
    }
    for (int i(p+1); i<q; ++i){
        if (b[L[i]] > x) continue;
        res += sum[upper_bound(b+L[i], b+R[i]+1, x)-b-1];
    }
    return res;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i(1); i<=n; ++i) cin >> a[i];
    for (int i(1); i<=n; ++i) b[i] = a[i];
    int len(sqrt(n)), tot((n-1)/len+1);
    for (int i(1); i<=tot; ++i){
        L[i] = R[i-1] + 1;
        R[i] = i * len;
    }
    R[tot] = n;

    for (int i(1); i<=tot; ++i){
        for (int j(L[i]); j<=R[i]; ++j) bl[j] = i;
        sort(b+L[i], b+R[i]+1);
        sum[L[i]] = b[L[i]];
        for (int j(L[i]+1); j<=R[i]; ++j) sum[j] = sum[j-1] + b[j];
    }

    cin >> q;
    while (q--){
        cin >> l >> r >> x;
        l ^= lans;
        r ^= lans;
        x ^= lans;
        cout << (lans = query()) << '\n';
    }

    return 0;
}
```


---

## 作者：Angraecum (赞：2)

### 题意

求静态区间内不大于 $x$ 的数的和，强制在线，每个询问给出的数要异或上一个答案，答案初始为 $0$。

序列最长为 $2\times 10^5$，询问最多 $2\times 10^5$ 个，序列的每个元素 $0 \le A_i\le 10^9$，$0\le x\le 10^9$。

### 思路

强制在线，能想到用树套树或分块解决，但我不会树套树，于是考虑分块。

散块直接暴力枚举一遍就完了。对于整块，我们考虑先分别对每个块内的元素排序，在每个块中记录前缀和，这样查询时对每个整块就可以先二分找到 $x$ 在排序后的块所在的位置，然后就可以直接加前缀和了，时间复杂度 $O(n\sqrt{n}\log n)$，在 $3.50s$ 时限下调下块长就能过了。

还有点细节在代码里，还有不要像我一样傻乎乎的全开 ``long long``，只开统计答案的就行了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=2*114514,M=1919810;
inline ll read(){
    ll x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}
inline void write(ll x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
    return;
}
ll n,m;
ll ns,nq,st[N],ed[N],bel[N],edd[N];
ll a[N],b[N],sum[N];
ll query(ll l,ll r,ll k){
	ll ans=0;
	if(bel[l]==bel[r]){
		for(int i=l;i<=r;++i)
			if(a[i]<=k) ans+=a[i];
		return ans;
	}
	for(int i=l;i<=ed[bel[l]];++i)
		if(a[i]<=k) ans+=a[i];
	for(int i=st[bel[r]];i<=r;++i)
		if(a[i]<=k) ans+=a[i];
	for(int i=bel[l]+1;i<bel[r];++i){
		int pos=upper_bound(b+st[i],b+ed[i]+1,k)-b-1; //注意是upper_bound，当然lower_bound也行，看写法 
		if(pos<st[i]) continue;
		ans+=sum[pos];
	}
	return ans;
}
int main(){
	n=read(); ns=1700,nq=ceil(n*1.0/ns);
	for(int i=1;i<=n;++i) a[i]=read(),b[i]=a[i]; //要另开一个数组用来排序，否则会影响散块查询 
	for(int i=1;i<=nq;++i){
		st[i]=ns*(i-1)+1,ed[i]=min(ns*i,n);
		sort(b+st[i],b+ed[i]+1);
		ll cnt=1,tot=st[i]-1;
		sum[st[i]]=b[st[i]];
		for(int j=st[i];j<=ed[i];++j){
			bel[j]=i;
			if(j>st[i]) sum[j]=sum[j-1]+b[j]; //别加到前一个块的前缀和了 
		}
	}
	m=read();
	ll las=0;
	for(int i=1;i<=m;++i){
		ll l,r,x;
		l=read(),r=read(),x=read();
		l^=las,r^=las,x^=las;
		las=query(l,r,x);
		write(las),putchar('\n');
	}
	return 0;
}
```


---

## 作者：__Floze3__ (赞：1)

## 思路简述

比较明显的分块题，考虑用一个 b 数组存储 a 数组中每一个元素，分块之后再在 b 数组上对每一个块内元素进行排序。排完序后，对每一个块做一个前缀和，便于求和。对于每一次查询，对于覆盖了一整块的区间询问，可以用在 b 数组上二分查找的方式找出区间内小于等于 x 的元素之和；而对于没有覆盖一整个块的区间询问，直接暴力统计即可。

唯一要注意的事情：块长不能开为 $\sqrt n$，会被卡掉；建议使用 $2000$ 左右的块长。

## 代码

```cpp
#include <bits/stdc++.h>
#define _FOR(i, a, b) for (int(i) = (a); (i) <= (b); ++(i))
typedef long long i64;

const int N = 2e5 + 5;

int n, pos[N], st[1005], ed[1005], Q;
i64 alpha, beta, garma, B, a[N], b[N], sum[N];

inline i64 Query(int l, int r, i64 val) {
    int p = pos[l], q = pos[r];
    i64 res = 0;
    if (p == q) {
        _FOR(i, l, r) {
            if (a[i] <= val) res += a[i];
        }
        return res;
    }
    _FOR(i, l, ed[p]) {
        if (a[i] <= val) res += a[i];
    }
    _FOR(i, st[q], r) {
        if (a[i] <= val) res += a[i];
    }
    _FOR(i, p + 1, q - 1) {
        if (b[st[i]] > val) continue;
        int L = st[i], R = ed[i];
        while (L < R) {
            int Mid = (L + R + 1) >> 1;
            if (b[Mid] <= val) L = Mid;
            else R = Mid - 1;
        }
        res += sum[L];
    }
    return res;
}

int main() {
    std::cin >> n;
    int block = 2000;
    int t = n / block + (n % block ? 1 : 0);
    _FOR(i, 1, n) {
        std::cin >> a[i];
        b[i] = a[i];
        pos[i] = (i - 1) / block + 1;
    }
    _FOR(i, 1, t) {
        st[i] = (i - 1) * block + 1;
        ed[i] = i * block;
    }
    ed[t] = n;
    _FOR(i, 1, t) {
        std::sort(b + st[i], b + ed[i] + 1);
        sum[st[i]] = b[st[i]];
        _FOR(j, st[i] + 1, ed[i]) {
            sum[j] = sum[j - 1] + b[j];
        }
    }
    std::cin >> Q;
    while (Q--) {
        std::cin >> alpha >> beta >> garma;
        i64 L = alpha ^ B, R = beta ^ B, X = garma ^ B;
        B = Query(L, R, X);
        std::cout << B << '\n';
    }
    return 0;
}
```

---

## 作者：xxxxxzy (赞：1)

[题目](https://www.luogu.com.cn/problem/AT_abc339_g)

题目大意：给你一个序列，每次要你求 $[l,r]$ 中不大于 $x$ 的数之和。

主席树板子，直接在主席树里面维护前缀和就行了，查询时直接差分。

由于这个题强制在线，所以不能全部离线下来离散化，每次查询时，直接用 ```upper_bound``` 在离散化序列里二分就可以了。 

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct tree{
	int sum,l,r,t;
}tt[8000005];
int tot,n,q,a[200005],b[200005];
inline int build(int l,int r){
	int p=++tot;
	if(l<r){
		int mid=(l+r)>>1;
		tt[p].l=build(l,mid);
		tt[p].r=build(mid+1,r);
	}
	return p;
}
inline int insert(int pre,int l,int r,int x){
	int p=++tot;
	tt[p].l=tt[pre].l,tt[p].r=tt[pre].r,tt[p].sum=tt[pre].sum+b[x];
	if(l<r){
		int mid=(l+r)>>1;
		if(x<=mid) tt[p].l=insert(tt[pre].l,l,mid,x);
		else tt[p].r=insert(tt[pre].r,mid+1,r,x);
	}
	return p;
}
inline int ask(int u,int v,int l,int r,int ql,int qr){
	if(l>qr||ql>r)return 0;
	if(ql<=l&&r<=qr)return tt[v].sum-tt[u].sum;
	int mid=(l+r)>>1;
	return ask(tt[u].l,tt[v].l,l,mid,ql,qr)+ask(tt[u].r,tt[v].r,mid+1,r,ql,qr);
}
int ans;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],b[i]=a[i];
	sort(b+1,b+1+n);
	int m=n;
	n=unique(b+1,b+1+n)-b-1;
	tt[0].t=build(1,n);
	for(int i=1;i<=m;i++){
		a[i]=lower_bound(b+1,b+1+n,a[i])-b;
		tt[i].t=insert(tt[i-1].t,1,n,a[i]);
	}
	cin>>q;
	for(int i=1;i<=q;i++){
		int l,r,x;
		cin>>l>>r>>x;
		l^=ans,r^=ans,x^=ans;
		x=upper_bound(b+1,b+1+n,x)-b-1;
		ans=ask(tt[l-1].t,tt[r].t,1,n,1,x);
		cout<<ans<<endl;
	}
} 
```

---

## 作者：Drind (赞：1)

## 题目解析

静态区间，每次查询 $l_i$ 到 $r_i$ 中所有小于 $w_i$ 的数的和，强制在线。

考虑分块，我们预处理前 $i$ 块中小于 $j$ 的数字之和，剩下的暴力扫即可。

什么你说你想要 polylog 做法？考虑可持久化权值线段树，维护区间和即可。

给出场上的实现代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;

struct node{
	int lc,rc;
	long long w;
}tree[N<<5];
int root[N],a[N],tmp[N],tot;
inline int copy(int x){
	++tot;
	tree[tot]=tree[x];
	return tot;
}
int modify(int x,int l,int r,int pos){
	x=copy(x); tree[x].w+=tmp[pos];//注意加的是离散化前的值
	if(l==r) return x;
	int mid=(l+r)/2;
	if(pos<=mid) tree[x].lc=modify(tree[x].lc,l,mid,pos);
	else tree[x].rc=modify(tree[x].rc,mid+1,r,pos);
	return x;
}
long long query(int x1,int x2,int l,int r,int val){
	if(tmp[r]<=val){
		return tree[x2].w-tree[x1].w;
	}
	if(l==r){//注意 val 不一定能映射到离散化的值，所以要特判 l==r
		if(tmp[l]<=val) return tree[x2].w-tree[x1].w;
		else return 0;
	}
	int mid=(l+r)/2;
	if(tmp[mid]>=val){//
		return 1ll*query(tree[x1].lc,tree[x2].lc,l,mid,val);
	}else return 1ll*(tree[tree[x2].lc].w-tree[tree[x1].lc].w)+1ll*query(tree[x1].rc,tree[x2].rc,mid+1,r,val);
}

inline void fake_main(){
	int n,m; cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]; tmp[i]=a[i];
	}
	sort(tmp+1,tmp+n+1); int len=unique(tmp+1,tmp+n+1)-tmp-1;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(tmp+1,tmp+len+1,a[i])-tmp;
		root[i]=modify(root[i-1],1,len,a[i]);
	}
	long long lst=0; cin>>m;
	for(int i=1;i<=m;i++){
		long long l,r,w; cin>>l>>r>>w;
		l^=lst; r^=lst; w^=lst;
		lst=query(root[l-1],root[r],1,len,w);
		cout<<lst<<"\n";
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int t; t=1;
	while(t--) fake_main();
}

```

---

## 作者：ilibilib (赞：1)

## 分析：

本题类似[教主的魔法](https://www.luogu.com.cn/problem/P2801)。

对读入的数组 $a$，进行序列分块。并开一个辅助数组 $b$，$b$ 记录 $a$ 按每个块升序排好的序列。

具体而言，对每个块 $p$：

```cpp
	for(register int i=bg[p];i<=ed[p];++i) b[i]=a[i];
	sort(b+bg[p],b+ed[p]+1);//bg[p]是块首，ed[p]是块尾
```

并记录 $b$ 在块内的前缀：

```cpp
	s[bg[p]]=b[bg[p]];
	for(register int i=bg[p]+1;i<=ed[p];++i) s[i]=s[i-1]+b[i];
```

那么对于询问，整块的时候直接对该块的辅助数组 $b$ 进行二分查找。散块则直接暴力记录每个小于等于询问值得 $a_i$。

```cpp
	int p=pos[l],q=pos[r];//对区间l,r询问.p,q为l,r所属块
	long long ret=0;
	if(p==q)
	{
		for(register int i=l;i<=r;++i) if(a[i]<=w) ret+=a[i];//w是询问值
	}//散块
	else
	{
		for(register int i=p+1;i<=q-1;++i)
		{
			int v=upper_bound(b+bg[i],b+ed[i]+1,w)-b-1;
			if(v<bg[i]) continue;//如果块内没有一个小于等于询问值的，则返回
             ret+=s[v];//整块二分
		}
		ret+=ask(l,ed[p],w);ret+=ask(bg[q],r,w);
	}
	return ret;
```

显然，$O(n\sqrt{n}\log{\sqrt{n}})$ 的复杂度需要**略微卡常**。

## code：

```cpp
#include<bits/stdc++.h>
#define sc scanf
#define pt printf
#define gc getchar
#define pc putchar
#define N 4000010
using namespace std;
template<typename T>
inline void read(T &x)
{
	x=0;char ch=gc();
	while(ch<'0'||ch>'9') {ch=gc();}
	while(ch>='0'&&ch<='9') {x=(x<<3)+(x<<1)+ch-48,ch=gc();}
}
template<typename T>
inline void write(T x)
{
	if(x>9) write(x/10);
	pc(x%10^48);
}
int a[N],bg[N],ed[N],lz[N],pos[N],b[N];
long long s[N];
void solve(int p)
{
	for(register int i=bg[p];i<=ed[p];++i) b[i]=a[i];
	sort(b+bg[p],b+ed[p]+1);
	s[bg[p]]=b[bg[p]];
	for(register int i=bg[p]+1;i<=ed[p];++i) s[i]=s[i-1]+b[i];
}
void bld(int n)
{
	int fk=sqrt(n);int t=n/fk;t+=(bool)(n%fk);
	for(register int i=1;i<=n;++i) pos[i]=(i-1)/fk+1;
	for(register int i=1;i<=t;++i) bg[i]=(i-1)*fk+1,ed[i]=i*fk;
	ed[t]=n;
	for(register int i=1;i<=t;++i) solve(i);
}
long long ask(int l,int r,int w)
{
	int p=pos[l],q=pos[r];
	long long ret=0;
	if(p==q)
	{
		for(register int i=l;i<=r;++i) if(a[i]<=w) ret+=a[i];
	}
	else
	{
		for(register int i=p+1;i<=q-1;++i)
		{
			int v=upper_bound(b+bg[i],b+ed[i]+1,w)-b-1;
			if(v<bg[i]) continue;ret+=s[v];
		}
		ret+=ask(l,ed[p],w);ret+=ask(bg[q],r,w);
	}
	return ret;
}
signed main()
{
	int n,q;
	long long last=0,l,r,w;
	read(n);
	for(register int i=1;i<=n;++i) read(a[i]);
	bld(n);
	read(q);
	while(q--)
	{
		read(l);read(r);read(w);
		l^=last,r^=last,w^=last;
		last=ask(l,r,w);
		write(last);
		pc('\n');
	}
	return 0;
}
```



---

## 作者：JuRuoOIer (赞：1)

# 题解 ABC339G Smaller Sum

~~晚来 50min，错失上分好机会。佬们都 AK 了我还不会 E。~~

**前排提醒：本题正解 TLE 很可能是 WA 了导致后面解码出了错误的范围。**

### 题意

已提交翻译。

给定长度为 $n$ 的数组 $a$，$q$ 次询问，每次给定 $l,r,x$，求在 $a_l,a_{l+1},...,a_r$ 中小于等于 $x$ 的所有数之和。

本题强制在线。后一次询问给出的 $l,r,x$ 需异或上前一次询问的答案。下标从 $1$ 开始。

数据范围：$1 \le n,q \le 2 \times 10^5,1 \le a_i \le 10^9$。**读入的** $l,r,x \le 10^{18}$，**实际的** $l \le r \le n,x \le10^9$。

### 做法

核心部分可以参考 [题解 P2163 [SHOI2007] 园丁的烦恼](https://juruooier.blog.luogu.org/solution-P2163)。该题中我使用了类似的思路，但加了更多的图。

使用归并排序将原数组排序，并记录每次运行函数后被排序的段的顺序，建立起类似于线段树的结构。记录一段的顺序时同时记录按此顺序的前缀和。

查询时同样类似于线段树进行递归，若查询区间与所在区间完全重合，则二分查找出所在区间第一个大于 $x$ 的值的位置，并对应地返回前一个位置的前缀和。

如果还不太理解，样例画出来是长这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/bszx34z7.png)

### ~~我踩到的~~可能的坑点

1. 人家让你求和，没让你求个数。（症状：样例第五次询问输出 `7`）
2. 排序时当 $l = r$ 时别忘了记录前缀和。
3. 询问的编号从 $1$ 开始。
4. 查询时想用 `upper_bound` 的请将记录每段顺序和前缀和的数组（代码中 `f` 和 `g`）的第一维开成深度。
5. 某一段中可能没有小于等于 $x$ 的数，这时 `upper_bound` 返回该段开头，前一个位置的前缀和会跑到别的段里或者负下标，导致 WA 或 RE。

### 代码

```cpp
ll n,q,a[200010],lst,f[20][200010],g[20][200010];
//归并排序函数
void msort(ll l,ll r,ll dep){
	if(l==r){
		f[dep][l]=a[l];
		g[dep][l]=a[l];//别忘了一个也要记录前缀和
		return ;
	}
	ll mid=(l+r)>>1;
	msort(l,mid,dep+1);
	msort(mid+1,r,dep+1);
	ll p=l,p1=l,p2=mid+1;
	while(p1<=mid&&p2<=r){
		if(f[dep+1][p1]<f[dep+1][p2]){
			f[dep][p]=f[dep+1][p1];
			p1++;
		}
		else{
			f[dep][p]=f[dep+1][p2];
			p2++;
		}
		p++;
	}
	while(p1<=mid){
		f[dep][p]=f[dep+1][p1];
		p1++;
		p++;
	}
	while(p2<=r){
		f[dep][p]=f[dep+1][p2];
		p2++;
		p++;
	}
    //正常归并排序操作，只不过多了深度 dep 来确定排序后的数字应该存在哪里
	g[dep][l]=f[dep][l];
	for(int i=l+1;i<=r;i++){
		g[dep][i]=g[dep][i-1]+f[dep][i];
	}
    //求前缀和
}
//查询函数
ll query(ll l,ll r,ll l2,ll r2,ll x,ll dep){
	//查询的范围与当前范围相交部分为 [l,r]
    //当前所在范围为 [l2,r2]
    //x 为查询中给定的 x，dep 为深度（同 msort 函数）
	ll mid=(l2+r2)>>1;
	if(l==l2&&r==r2){//两个范围重合时二分查找并返回
		if(upper_bound(f[dep]+l2,f[dep]+r2+1,x)-f[dep]-l2)//坑点 5
			return g[dep][upper_bound(f[dep]+l2,f[dep]+r2+1,x)-f[dep]-1];
		return 0;
	}
	if(l>mid){//查询的范围完全在左半边
		return query(l,r,mid+1,r2,x,dep+1);
	}
	if(r<=mid){//完全在右半边
		return query(l,r,l2,mid,x,dep+1);
	}
	return query(l,mid,l2,mid,x,dep+1)+query(mid+1,r,mid+1,r2,x,dep+1);//两边都有
}
int main(){
	ll l,r,x;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	msort(0,n-1,0);
	cin>>q;
	while(q--){
		cin>>l>>r>>x;
		l^=lst;
		l--;//我的下标从 0 开始
		r^=lst;
		r--;
		x^=lst;
		lst=query(l,r,0,n-1,x,0);
		cout<<lst<<endl;
	}
	return 0;
}
```

---

## 作者：s4CRIF1CbUbbL3AtIAly (赞：0)

## 题意
给定一个序列，每次查询 $[l,r]$ 内 $\le x$ 的数之和，强制在线。
## 做法
考虑直接主席树，节点记录对应值域区间的数的和。

对于每个查询，找出 $r$ 版本和 $l-1$ 版本的根，并把 $[0,x]$ 拆成线段树区间，每个区间算出 $r$ 版本的和以及 $l-1$ 版本的和相减即可。

---

## 作者：LuoFeng_Nanami (赞：0)

### 题目大意
给出一个长度为 $N$ 的数列 $A$ 以及 $Q$ 次询问，每次询问查询区间 $[A_L,A_R]$ 中不大于 $X$ 的数字之和。
### Solution
$N \le 2 \times 10^5$，考虑分块。   
根据“大段维护，小段朴素”的原则，我们将每个块排序，每次二分查找块内最后一个小于等于 $X$ 的数的位置，即第一个大于 $X$ 的数的位置减去 $1$。块内答案即为这个位置上的**块内前缀和**。整块两边零散的数暴力即可。

注意块长为 $\sqrt n$ 时会被卡掉，不妨设块长为 $2 \times \sqrt n$，完美通过本题。

### [Code](https://atcoder.jp/contests/abc339/submissions/49985133)


---

## 作者：incra (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/AT_abc339_g)
### 题解
首次场切 G 题，写题解纪念一下。

数据结构题，强制在线，看完题目，对作者来说树状数组和线段树可以不用想了，于是考虑最后的分块。

设块长为 $len$，考虑把每一块内部排序，因为要求解一整块的答案时，顺序不重要，于是就可以二分 $+$ 前缀和搞定一整块。

对于边角的碎片，在原序列上直接暴力查询。

接下来我们来求解 $len$ 的合适值，首先排序时间复杂度为 $O(\dfrac{n}{len}\times len\times \log len)=O(n\log len)$，计算一整块的答案的复杂度为 $O(\log len)$，边角的部分暴力为 $O(len)$，整合一下，**一次修改**时间复杂度就是 $O(\log len\times\dfrac{n}{len}+len)=O(\dfrac{n\log len}{len}+len)$，为了方便计算，我们把 $\log len$ 替换为 $\log n$，那么 $O(\dfrac{n\log n}{len}+len)$，显然 $len$ 取 $\sqrt{n\log n}$ 时最优，而不是 $\sqrt{n}$（我也错了好几次嘿嘿），此时总体复杂度为 $O(n\log n+q\sqrt{n\log n})$（这个时间复杂度是把 $\log len$ 替换后的结果），勉强能过。

注意上式中我们把 $\log len$ 替换为 $\log n$，其实不影响计算，显然 $\log n>\log len$，所以计算出来的时间复杂度扩大后仍然能通过，所以也能得出该方法能通过本题。

由于作者懒，就选 $len=2000$ 了。
### 代码
```
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <ctime>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define pf push_front
#define desktop "C:\\Users\\incra\\Desktop\\"
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,0,-1,0},dy[] = {0,-1,0,1};
bool LAST = false;
istream& operator >> (istream& in,char* s) {
    if (LAST) return in;
	char ch = in.get ();
	while ((isspace (ch) || ch == '\n') && ch != EOF) ch = in.get ();
	int n = 0;
	while (!(isspace (ch) || ch == '\n') && ch != EOF) s[n++] = ch,ch = in.get ();
	s[n] = '\0';
	if (ch == EOF) LAST = true;
	return in;
}
template <typename T1,typename T2> bool tomax (T1 &x,T2 y) {
	if (y > x) return x = y,true;
	return false;
}
template <typename T1,typename T2> bool tomin (T1 &x,T2 y) {
	if (y < x) return x = y,true;
	return false;
}
LL power (LL a,LL b,LL p) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
const int N = 200010,M = 4010;
int n,q;
int a[N];
int b[N];
int L[N],R[N];
int pos[N];
LL sum[M][M];
int main () {
	scanf ("%d",&n);
	int len = min (2000,n);
	int cnt = n / len;
	for (int i = 1;i <= cnt;i++) L[i] = (i - 1) * len + 1,R[i] = i * len;
	if (R[cnt] < n) cnt++,L[cnt] = R[cnt - 1] + 1,R[cnt] = n;
	for (int j = 1;j <= cnt;j++) {
//		cout << L[j] << ' ' << R[j] << endl;
		for (int i = L[j];i <= R[j];i++) pos[i] = j;
	}
	for (int i = 1;i <= n;i++) scanf ("%d",&a[i]),b[i] = a[i];
	for (int i = 1;i <= cnt;i++) {
		sort (b + L[i],b + R[i] + 1);
		sum[i][1] = b[L[i]];
		for (int j = L[i] + 1;j <= R[i];j++) sum[i][j - L[i] + 1] = sum[i][j - L[i]] + b[j];
//		cout << i << ' ' << sum[i][R[i] - L[i] + 1] << endl;
//		puts ("--------------");
	}
//	for (int i = 1;i <= n;i++) cout << b[i] << ' ';
//	cout << endl;
	LL ans = 0;
	cin >> q;
	while (q--) {
		LL l,r,x;
		scanf ("%lld%lld%lld",&l,&r,&x);
		l ^= ans,r ^= ans,x ^= ans;
		int p = pos[l],q = pos[r];
		ans = 0;
		if (p == q) {
			for (int i = l;i <= r;i++) {
				if (a[i] <= x) ans += a[i];
			}
		}
		else {
			for (int i = p + 1;i <= q - 1;i++) {
				int l = L[i],r = R[i];
				while (l < r) {
					int mid = l + r + 1 >> 1;
					if (b[mid] <= x) l = mid;
					else r = mid - 1;
				}
				if (b[l] <= x) ans += sum[i][l - L[i] + 1];
			}
//			cout << ans << "-----------" << endl;
			for (int i = l;i <= R[p];i++) {
				if (a[i] <= x) ans += a[i];
			}
			for (int i = L[q];i <= r;i++) {
				if (a[i] <= x) ans += a[i];
			}
		}
		printf ("%lld\n",ans);
	}
	return 0;
}
```

---

