# Yunli's Subarray Queries (extreme version)

## 题目描述

这是问题的极限版本。在这个版本中，每个查询的输出与简单版和困难版不同。保证对于所有的查询都有 $ r \geq l+k-1 $。

对于一个任意数组 $ b $，云莉可以无数次进行以下操作：

- 选择一个下标 $ i $，将 $ b_i $ 设置为任意她想要的整数 $ x $（$ x $ 不限制在 $ [1, n] $ 区间内）。

定义 $ f(b) $ 为所需的最小操作次数，以使得 $ b $ 中存在一个长度至少为 $ k $ 的连续子数组。

云莉给出一个大小为 $ n $ 的数组 $ a $ 并询问你 $ q $ 次，你需要在每次查询中计算并输出 $\sum_{i=l}^{r-k+1} \sum_{j=i+k-1}^{r} f([a_i, a_{i+1}, \ldots, a_j])$。

如果数组中存在从下标 $ i $ 开始的长度为 $ k $ 的连续子数组（$ 1 \leq i \leq |b|-k+1 $），那么在该子数组中，对于 $ i < j \leq i+k-1 $，必须满足 $ b_j = b_{j-1} + 1 $。

## 说明/提示

在第一个测试用例的第一个查询中，我们可以通过如下方法来计算结果：

- 当 $ i = 4 $ 且 $ j = 5 $ 时，$ f([2, 1])=1 $，因为云莉可以将 $ b_2 $ 设为 3，从而一步操作后形成长度为 2 的连续子数组。
- 当 $ i = 4 $ 且 $ j = 6 $ 时，$ f([2, 1, 2])=0 $，因为已经存在长度为 2 的连续子数组。
- 当 $ i = 5 $ 且 $ j = 6 $ 时，$ f([1, 2])=0 $，因为已经存在长度为 2 的连续子数组。

此查询的答案为 $ 1+0+0=1 $。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
7 2 4
1 2 3 2 1 2 3
4 6
1 7
2 7
3 7
8 4 2
4 3 1 1 2 4 3 2
3 6
1 5
5 4 2
4 5 1 2 3
1 4
1 5
10 4 8
2 3 6 5 8 9 8 10 10 1
2 7
6 10
1 9
1 6
3 9
4 10
2 10
1 8
10 7 4
3 4 5 3 4 5 9 10 8 9
1 9
2 10
1 10
2 9```

### 输出

```
1
3
3
3
2
7
2
4
8
6
28
7
16
20
32
19
18
15
26
9```

# 题解

## 作者：Super_Cube (赞：3)

# Solution

设 $b_i=f([a_i,a_{i+1},\ldots,a_{i+k-1}])$，那么答案为 $\displaystyle\sum_{i=l}^{r-k+1}\sum_{j=i}^{r-k+1}\min_{k=i}^jb_k$。

对 $a$ 中所有数执行 $a_i\gets a_i-i$，那么原问题（修改最少的数使得区间变为公差为 $1$ 的递增数列）变为了新问题：修改最少的数使得区间所有数相等。肯定把非区间众数改为区间众数是最优的，所以 $b_i$ 即为 $k$ 减区间 $[i,i+k-1]$ 中众数的出现次数。

由于 $k$ 为定值，可利用类似滑动窗口的模式预处理出 $b_i$。

对于询问，先使 $r\gets r-k+1$，答案即为 $\displaystyle\sum_{i=l}^r\sum_{j=i}^r\min_{k=i}^jb_k$。

如何计算？找到 $x\in[l,r]$ 使得 $b_x=\displaystyle\min_{i=l}^rb_i$，那么对于 $i\le x,j\ge x$ 的贡献为 $b_x(x-l+1)(r-x+1)$。关于 $j<x$ 与 $i>x$ 的部分？先关注 $j<x$ 的部分。设 $f_{l,r}$ 表示左端点为 $l$，右端点在 $[l,r]$ 的贡献，所以 $j<x$ 部分即为 $\displaystyle\sum_{i=l}^{x-1}f_{i,x-1}$。

现在的需求是快速算任意 $f_{l,r}$。利用单调栈找到 $suf_i$ 为从 $i$ 开始往后第一个小于 $b_i$ 的位置，对于 $[l,suf_l)$ 的最小值都为 $b_l$，于是 $f_{l,r}=b_l(suf_l-l)+f_{suf_l,r}$。发现转移与 $r$ 无关，直接去掉：$f_l=b_l(suf_l-l)+f_{suf_l}$。现在的 $f_l-f_r$ 就是原来的 $f_{l,r-1}$。

所以 $j<x$ 部分的答案为 $\displaystyle\sum_{i=l}^{x-1}f_i-f_x$，后缀和优化即可。$i>x$ 的部分同理。

---

## 作者：bluewindde (赞：3)

云璃！

---

本题解的做法来源于 P1997，P3203 和 P3246。

---

题给函数 $f(b)$ 表示通过任意修改 $b$ 使之存在一个长不少于 $k$ 的公差为 $1$ 的等差数列的最少操作次数。令 $a_i \leftarrow a_i - i$，则 $f(b)$ 的含义变为通过任意修改 $b$ 使之存在一个长不少于 $k$ 的全部相等的子段的最少操作次数。

对于 easy version，显然全部修改为区间众数是最优的，回滚莫队求区间众数即可，时间复杂度 $O(q \sqrt n)$。（这也是 P1997 的做法）

---

对于 hard version，对 $1 \leqslant i \leqslant n - k + 1$，设 $c_i$ 表示 $f([i, i + k - 1])$。$c$ 可以用回滚莫队在 $O(n \sqrt n)$ 的时间内求出。答案为区间 $[l, r - k + 1]$ 的所有前缀的 $c$ 的最小值之和，即

$$\sum\limits_{i = l}^{r - k + 1} \min\limits_{j = l}^i c_j$$

考虑求这个值，对 $1 \leqslant i \leqslant n - k + 1$，从 $i$ 向 $i$ 后面第一个比它小的位置 $j$ 连边。（即满足 $i < j \land c_i > c_j$ 的最小的 $j$）前缀 $[i, j)$ 的最小值都为 $i$，对答案的贡献为 $i \cdot (j - i)$。

每次暴力跳会超时，考虑分块处理出第一次跳出当前块会到达的位置和这时产生的总贡献，时间复杂度优化到 $O(q \sqrt n)$，总时间为 $O((n + q) \sqrt n)$，可以通过。（这也是 P3203 的做法）

---

对于 extreme version，所求为 $c$ 在区间 $[l, r - k + 1]$ 内的所有子区间的最小值之和，即

$$\sum\limits_{i = l}^{r - k + 1} \sum\limits_{j = i}^{r - k + 1} \min\limits_{t = i}^j c_t$$

仍然考虑莫队，需要快速计算移动端点带来的贡献，即一段区间的所有前缀 / 后缀的最小值之和。

上一个 subtask 中求出了 $c$ 中 $i$ 之前第一个比它小的位置 $pre_i$ 和它之后第一个比它小的位置 $nxt_i$，如果继续套用 P3203 的分块做法会超时。

容易发现前缀的贡献是可以差分的，所以设前缀贡献 $f_i$ 和后缀贡献 $g_i$，递推式为

$$f_i = f_{pre_i} + c_i \cdot (i - pre_i)$$

$$g_i = g_{nxt_i} + c_i \cdot (nxt_i - i)$$

但是直接差分错完了，因为前缀和中贡献是按整段计算的。设 $p$ 为区间 $[l, r - k + 1]$ 之间最小值的位置，则其所有前缀 / 后缀的贡献分别为（令 $r \leftarrow r - k + 1$）

$$prefix = f_r - f_p + c_p \cdot (p - l + 1)$$

$$suffix = g_l - g_p + c_p \cdot (r - p + 1)$$

于是莫队的移动端点可以在 $O(1)$ 的时间内完成，总时间为 $O((n + q) \sqrt n)$，可以通过。（这也是 P3246 的做法）

---

官解不是这样做的，请见 [官方题解](https://codeforces.com/blog/entry/133296)。

代码：[easy](https://codeforces.com/contest/2009/submission/279818788) | [hard](https://codeforces.com/contest/2009/submission/279877172) | [extreme](https://codeforces.com/contest/2009/submission/279943447)。

---

## 作者：Luciylove (赞：0)

注意到 $b_i = b_{i  -1} + 1$ 的条件有很多，我们选择最简单的 $b_i \to b_i - i$。

现在转化为求让原数组拥有一个长度为 $k$ 的同色子段最小代价，考虑枚举这个子段的左端点，使用滑动窗口求出 $k$ 减去定长区间的众数的出现次数，记为 $c_i$。

感受一下大概是怎么样贡献的，然后你就会觉得像是所有二维矩形取 $\min$ 状物，有点复杂。所以我们可以转置贡献角度，考虑让 $r \to r - k + 1$，左端点的贡献范围是固定的 $[l, r]$ ，求区间最小值即可。
$$
\sum_{i = l}^r \sum_{j = i}^r \underset{{k \in [i, j]}} \min c_k
$$

这个是经典的历史版本和问题 / 笛卡尔树上算贡献。

我采取了前者实现，时间复杂度线性对数。若采用后者，应该可以做到线性。


```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = l; i <= r; i ++)
#define per(i, r, l) for (int i = r; i >= l; i --)
#define lc x << 1
#define rc x << 1 | 1
/*
使い切って声に出そう
*/
using namespace std;

typedef long long ll;
const int _ = 2e5 + 5, mod = 998244353;
int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * f;
}

int power (int x, int y) {
	int r = 1;
	for ( ; y; y >>= 1, x = 1ll * x * x % mod)
		if (y & 1) r = 1ll * r * x % mod;
	return r;
}
void add_mod (int &x, int y) { x += y; if (x >= mod) x -= mod; }
void del_mod (int &x, int y) { x -= y; if (x < 0) x += mod; }
void tim_mod (int &x, int y) { x = 1ll * x * y % mod; }

struct DS_blk {
	int tag[_ << 2], len[_ << 2];
	ll sum[_ << 2], htag[_ << 2], hsum[_ << 2];
	void apply (int x, int l, int r, int L, int k, ll hk) {
		htag[x] += 1ll * tag[x] * L + hk;
		hsum[x] += 1ll * sum[x] * L + hk * (r - l + 1);
		len[x] += L;
		tag[x] += k;
		sum[x] += (r - l + 1) * k;
	}
	void pushdown (int x, int l, int mid, int r) {
		if (len[x] || tag[x] || htag[x]) {
			apply(lc, l, mid, len[x], tag[x], htag[x]);
			apply(rc, mid + 1, r, len[x], tag[x], htag[x]);
			len[x] = tag[x] = htag[x] = 0;
		}
	}
	void pushup (int x) { sum[x] = sum[lc] + sum[rc], hsum[x] = hsum[lc] + hsum[rc]; }
	void build (int x, int l, int r) {
		tag[x] = len[x] = 0;
		sum[x] = hsum[x] = htag[x] = 0ll;
		if (l == r) return ;
		int mid = (l + r) >> 1;
		build(lc, l, mid), build(rc, mid + 1, r);
	}
	void modify (int x, int l, int r, int ql, int qr, int k) {
		if (ql <= l && r <= qr) return apply(x, l, r, 0, k, 0);
		int mid = (l + r) >> 1; pushdown(x, l, mid, r);
		if (ql <= mid) modify(lc, l, mid, ql, qr, k);
		if (qr > mid) modify(rc, mid + 1, r, ql, qr, k);
		return pushup(x);
	}
	ll query (int x, int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) return hsum[x];
		int mid = (l + r) >> 1; ll ret = 0; pushdown(x, l, mid, r);
		if (ql <= mid) ret += query(lc, l, mid, ql, qr);
		if (qr > mid) ret += query(rc, mid + 1, r, ql, qr);
		return ret;
	}
	// len, tag, htag, sum, hsum
} blk;

unordered_map <int, int> vis;
int cnt[_], mx;
void add (int v) { cnt[vis[v]] --, ++ vis[v], cnt[vis[v]] ++, mx = max(mx, vis[v]); }
void del (int v) { cnt[vis[v]] --, -- vis[v], cnt[vis[v]] ++; if (mx == vis[v] + 1 && !cnt[vis[v] + 1]) mx --; }

int n, k, q, a[_], c[_], stk[_], top;
ll ans[_];
vector <pair<int, int> > qv[_];
void Luciy_rain() {
	rep(i, 1, n) qv[i].clear(), cnt[i] = 0;
	mx = 0, vis.clear();
	stk[top = 0] = 0;
	
	n = read(), k = read(), q = read();
	rep(i, 1, n) a[i] = read() - i;
	rep(i, 1, k - 1) add(a[i]);
	rep(i, k, n) {
		add(a[i]);
		c[i - k + 1] = k - mx;
		del(a[i - k + 1]);
	}
	rep(i, 1, q) {
		int l = read(), r = read() - k + 1;
		qv[r].push_back({l, i});
	}
	int limr = n - k + 1;
	blk.build(1, 1, limr);
	rep(i, 1, limr) {
		while (top && c[i] <= c[stk[top]]) {
			blk.modify(1, 1, limr, stk[top - 1] + 1, stk[top], -c[stk[top]] + c[i]);
			top --;
		}
		stk[++ top] = i, blk.modify(1, 1, limr, i, i, c[i]);
		blk.apply(1, 1, limr, 1, 0, 0);
		for (auto [l, id] : qv[i])
			ans[id] = blk.query(1, 1, limr, l, i);
	}
	rep(i, 1, q) printf("%lld\n", ans[i]);
}
int main () {
	int T = read();
	while(T --)
		Luciy_rain();
	return 0;
}
```

---

## 作者：_Ch1F4N_ (赞：0)

首先数值连续递增不好处理，于是 $a_i \gets a_i - i$ 后变为区间长度减去区间众数出现次数（也就是要求数值相同），显然对于每个长度为 $k$ 的区间可以做一次 $O(n)$ 的滑动窗口并用两个桶维护每个区间的贡献。下文令 $b_i$ 表示区间 $[i,i+k-1]$ 的贡献。

然后询问时 $r \gets r-k+1$，问题变为 $\sum_{L=l}^{r} \sum_{R=L}^{r} \min_{i \in [L,R]}(b_i)$。 

这是一个经典问题，考虑把询问挂到右端点上扫描线，扫描线的过程中右端点变化时每个左端点到右端点的区间 $\min$ 的变化可以用单调栈转化为总共 $O(n)$ 次区间加表示，再使用一个历史和线段树维护区间历史和即可。

总时间复杂度 $O(n \log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+114;
int tot[maxn<<1],mx,cnt[maxn];
void add(int x){
    cnt[tot[x]]--;
    tot[x]++;
    cnt[tot[x]]++;
    mx=max(mx,tot[x]);
}
void del(int x){
   cnt[tot[x]]--;
   tot[x]--;
   cnt[tot[x]]++;
   if(mx==tot[x]+1&&cnt[tot[x]+1]==0) mx=tot[x];
}
int a[maxn],b[maxn];
int n,k,q;
long long answer[maxn];
vector< pair<int,int> > query[maxn];//(id,l)
int stk[maxn],tp;
struct node{
    long long a[3][3];
    int n,m;
    node(int N=0,int M=0){
        n=N,m=M;
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++) a[i][j]=0;
    }
    node operator*(const node&x){
        node res=node(n,x.m);
        if(n==1){
            res.a[0][0]=a[0][0]+a[0][1]*x.a[1][0]+a[0][2]*x.a[2][0];
            res.a[0][1]=a[0][1]+a[0][2]*x.a[2][1];
            res.a[0][2]=a[0][2];
        }else{
            res.a[0][0]=1;
            res.a[1][1]=1;
            res.a[2][2]=1;
            res.a[1][0]=x.a[1][0]+a[1][0];
            res.a[2][1]=x.a[2][1]+a[2][1];
            res.a[2][0]=x.a[2][0]+a[2][1]*x.a[1][0]+a[2][0];
        }
        return res;
    }
    node operator+(const node&x){
        node res=node(n,m);
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++) res.a[i][j]=a[i][j]+x.a[i][j];
        return res;
    }
}e;
node tr[maxn<<2],tag[maxn<<2];
void pushup(int cur){
    tr[cur]=tr[cur<<1]+tr[cur<<1|1];
}
void pushdown(int cur){
    tr[cur<<1]=tr[cur<<1]*tag[cur];
    tag[cur<<1]=tag[cur<<1]*tag[cur];
    tr[cur<<1|1]=tr[cur<<1|1]*tag[cur];
    tag[cur<<1|1]=tag[cur<<1|1]*tag[cur];
    tag[cur]=e;
}
void build(int cur,int lt,int rt){
    tag[cur]=e;
    if(lt==rt){
        tr[cur]=node(1,3);
        tr[cur].a[0][2]=1;
        //0 0 1
        return ;
    }
    int mid=(lt+rt)>>1;
    build(cur<<1,lt,mid);
    build(cur<<1|1,mid+1,rt);
    pushup(cur);
}
void mul(int cur,int lt,int rt,int l,int r,node c){
    if(rt<l||r<lt) return ;
    if(l<=lt&&rt<=r){
        tr[cur]=tr[cur]*c;
        tag[cur]=tag[cur]*c;
        return ;
    }
    int mid=(lt+rt)>>1;
    pushdown(cur);
    mul(cur<<1,lt,mid,l,r,c);
    mul(cur<<1|1,mid+1,rt,l,r,c);
    pushup(cur);
}
long long ask(int cur,int lt,int rt,int l,int r){
    if(rt<l||r<lt) return 0;
    if(l<=lt&&rt<=r) return tr[cur].a[0][0];
    int mid=(lt+rt)>>1;
    pushdown(cur);
    return ask(cur<<1,lt,mid,l,r)+ask(cur<<1|1,mid+1,rt,l,r);
}
void work(){
    cin>>n>>k>>q;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        a[i]+=n-i;
    }
    cnt[0]=2*n+1;
    for(int i=1;i<=k;i++) add(a[i]);
    for(int l=1,r=k;r<n;del(a[l]),l++,r++,add(a[r])){
        b[l]=k-mx;
    }
    b[n-k+1]=k-mx;
    e=node(3,3);
    for(int i=0;i<3;i++) e.a[i][i]=1;
    for(int i=1;i<=q;i++){
        int l,r;
        cin>>l>>r;
        r=r-k+1;
        query[r].push_back(make_pair(i,l));
    }
    build(1,1,n-k+1);
    for(int i=1;i<=n-k+1;i++){
        while(tp>0&&b[stk[tp]]>b[i]){
            //[stk[tp-1]+1,stk[tp]] -= a[stk[tp]]
            node c=e;
            c.a[2][1]=-b[stk[tp]];
            mul(1,1,n-k+1,stk[tp-1]+1,stk[tp],c);
            tp--;
        }
        stk[++tp]=i;
        //[stk[tp-1]+1,stk[tp]] += a[i]
        node c=e;
        c.a[2][1]=b[i];
        mul(1,1,n-k+1,stk[tp-1]+1,stk[tp],c);
        //[1,i] 历史和
        c=e;
        c.a[1][0]=1;
        mul(1,1,n-k+1,1,i,c);
        for(pair<int,int> now:query[i]) answer[now.first]=ask(1,1,n-k+1,now.second,i);
    }
    for(int i=1;i<=q;i++) cout<<answer[i]<<'\n',answer[i]=0;
    tp=0;
    for(int i=0;i<=2*n;i++) tot[i]=0;
    for(int i=0;i<=n;i++) cnt[i]=0,query[i].clear();
    mx=0;
    return ;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--) work();
    return 0;
}
/*
1
8 4 2
4 3 1 1 2 4 3 2
3 6
1 5
*/

```

---

