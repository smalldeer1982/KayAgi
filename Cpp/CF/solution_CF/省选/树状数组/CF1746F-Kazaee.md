# Kazaee

## 题目描述

给出一个长度为 $n$ 的数组 $a$ 和以下两种操作：

- $1\ i\ x$：将 $a_i$ 修改为 $x$。
- $2\ l\ r\ k$：询问在数组区间 $[l, r]$ 内是否每个出现过的正整数的出现次数都是 $k$ 的倍数。（建议参照样例理解）若是则输出 `YES`，若否则输出 `NO`。

## 样例 #1

### 输入

```
10 8
1234 2 3 3 2 1 1 2 3 4
2 1 6 2
1 1 1
2 1 6 2
2 1 9 2
1 10 5
2 1 9 3
1 3 5
2 3 10 2```

### 输出

```
NO
YES
NO
YES
YES```

# 题解

## 作者：fanypcd (赞：13)

# Kazaee


### 给出一个长度为 $n$ 的数组 $a$ 和以下两种操作：

- $1\ i\ x$：将 $a_i$ 修改为 $x$。
- $2\ l\ r\ k$：询问在数组区间 $[l, r]$ 内是否每个出现过的正整数的出现次数都是 $k$ 的倍数。（建议参照样例理解）若是则输出 `YES`，若否则输出 `NO`。

碰到这种常见数据结构几乎不可做的，但是又感觉很简单的操作，考虑随机化。

随机地将 $a_i$ 映射到值域内的另一个数上 （$a_i \to b_i$），考虑询问操作 $[l,r]$，求出 $S=\sum \limits_{i=l}^r b_i$，显然如果 $k \nmid S$ 一定是 `NO`，但是 $k  \mid S$ 不一定真的是 `YES`。

我们考虑一下错判 `NO` 为 `YES` 的概率：

- 假设存在一个数 $x \to y$ （映射后的值是 $y$）在区间中的出现次数 $cnt_x$，且 $k \nmid cnt_x$ 但 $k \mid y \times cnt_x$，这近似要求 $k \mid y$，所以错误率大概是 $1 \over k$。

- 还有一种理解方式：$S=\sum \limits_{x~\text{exists in}~a[l,r]}cnt_x \times y$，其中 $y$ 是完全随机的，那么可以认为 $S$ 也是随机的，所以在错误情况中，存在一个**随机**的 $S$ 满足 $k \mid S$ 的概率近似认为是 $1 \over k$。

然后就可以用树状数组维护前缀和，多随机映射几次，直到错误的概率小到可以接受即可水过此题。

```cpp
#include<bits/stdc++.h>
using namespace std;
template <class T> inline void read(T &x) {
	x = 0; int f = 0; char ch = getchar();
	while(ch < '0' || ch > '9')
		f |= ch == '-', ch = getchar();
	while('0' <= ch && ch <= '9')
		x = x * 10 + ch - 48, ch = getchar();
	x = f ? -x : x; return;
}
#define inf 0x3f3f3f3f
#define ll long long
#define fir first
#define sec second
#define N 300005
int n, Q, a[N], b[N];
mt19937 rnd(time(0));
#define lowbit(x) (x & -x)
ll val[N];
inline void update(int p, int v) {
	while(p <= n) {
		val[p] += v;
		p += lowbit(p);
	}
	return;
}
inline ll qry(int p) {
	ll res = 0; while(p) {
		res += val[p];
		p -= lowbit(p);
	}
	return res;
}
inline ll qry(int L, int R) {
	return qry(R) - qry(L - 1);
}
int op[N], l[N], r[N], k[N];
int num[N << 1], ntot;
int Ref[N << 1];
int ans[N];
signed main() {
	read(n), read(Q);
	for(int i = 1; i <= n; i++) read(a[i]), num[++ntot] = a[i];
	for(int i = 1; i <= Q; i++) {
		read(op[i]), read(l[i]), read(r[i]);
		ans[i] = 1;
		if(op[i] == 2) read(k[i]);
		else num[++ntot] = r[i];
	}
	sort(num + 1, num + ntot + 1);
	ntot = unique(num + 1, num + ntot + 1) - num - 1;
	for(int i = 1; i <= n; i++) {
		a[i] = lower_bound(num + 1, num + ntot + 1, a[i]) - num;
	}
	for(int i = 1; i <= Q; i++) {
		if(op[i] == 1) {
			r[i] = lower_bound(num + 1, num + ntot + 1, r[i]) - num;
		}
	}
	for(int T = 1; T <= 30; T++) {
		memset(val, 0, sizeof(val));
		memcpy(b, a, sizeof(b));
		for(int i = 1; i <= ntot; i++) {
			Ref[i] = rnd() >> 1;
		}
		for(int i = 1; i <= n; i++) {
			update(i, Ref[b[i]]);
		}
		for(int i = 1; i <= Q; i++) {
			if(op[i] == 1) {
				update(l[i], Ref[r[i]] - Ref[b[l[i]]]);
				b[l[i]] = r[i];
			}
			else {
				if(ans[i]) {
					if((r[i] - l[i] + 1) % k[i]) {
						ans[i] = 0; continue;
					}
					if(qry(l[i], r[i]) % k[i]) {
						ans[i] = 0; continue;
					}
				}
			}
		}
	}
	for(int i = 1; i <= Q; i++) {
		if(op[i] == 2) {
			if(ans[i]) puts("YES");
			else puts("NO");
		}
	}
	return 0;
}
```

---

## 作者：Terac (赞：4)

[$\texttt{link}$](https://www.luogu.com.cn/problem/CF1746F)

## 题意

给定一个长度为 $n$ 的序列 $a$，$m$ 次操作：

- 将 $a_i$ 修改为 $x$。
- $\forall x \text{ appear in}\left[l,r\right]$，计 $cnt_x$ 为 $x$ 在 $\left[l,r\right]$ 中的出现次数，查询 $cnt_x$ 是否均为 $k$ 的倍数。

数据范围：$1\le n,m\le 3\times 10^5, 1\le a_i,x\le10^9$

## 题解

显然有一个 $O(n^{\frac{5}{3}}\log n)$ 的带修莫队做法，当然过不了。

因为有神秘人告诉我，这题和 CSP 2022 的 C 类似，想到赋随机值哈希。

考虑把查询转化为区间和，发现区间和是 $k$ 的倍数答案为 `YES` 的必要条件，给每个 $a_i$ 映射到随机值 $b_i$ 上，bit 维护 $b_i$ 前缀和。

这种算法在 $k$ 很小时，正确性不高，因为 $b_i$ 是随机的，所以区间和也是随机的，当答案为 `NO` 且区间和为 $k$ 的倍数的概率是 $\frac{1}{k}$，可以考虑多随几组，$k=1$ 时答案肯定为 `YES`，$k\ge 2$ 时，随 $T$ 组错误的概率 $\le\frac{1}{2^T}$，对于所有询问错误率 $\le \frac{m}{2^T}$，当 $T=40$，这个错误率已经极小了，可以接受。

时间复杂度 $O(Tn\log n)$，其中 $T=40$。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 3e5 + 10;
mt19937_64 R;
int Rand(int l, int r) {
	uniform_int_distribution<int> distribution(l, r);
	return distribution(R);
}
int n, m, a[N], lsh[N << 1], cnt;
int rnd[N << 1], b[N];
bool ans[N];
struct query {
	int opt, x, y, k;
} q[N];
namespace bit {
	ll t[N];
	void add(int x, int k) {
		for(int i = x; i <= n; i += i & -i)
			t[i] += k;
	}
	ll qry(int x) {
		ll res = 0;
		for(int i = x; i; i -= i & -i)
			res += t[i];
		return res;
	}
	ll qry(int l, int r) {
		return qry(r) - qry(l - 1);
	}
} using namespace bit;
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]), lsh[++cnt] = a[i];
	for(int i = 1; i <= m; i++) {
		scanf("%d%d%d", &q[i].opt, &q[i].x, &q[i].y);
		if(q[i].opt == 1) lsh[++cnt] = q[i].y;
		else scanf("%d", &q[i].k);
	}
	sort(lsh + 1, lsh + 1 + cnt);
	cnt = unique(lsh + 1, lsh + 1 + cnt) - lsh - 1;
	for(int i = 1; i <= n; i++)
		a[i] = lower_bound(lsh + 1, lsh + 1 + cnt, a[i]) - lsh;
	for(int i = 1; i <= m; i++)
		if(q[i].opt == 1) q[i].y = lower_bound(lsh + 1, lsh + 1 + cnt, q[i].y) - lsh;
	memset(ans, 1, sizeof(ans));
	for(int T = 1; T <= 40; T++) {
		memset(t, 0, sizeof(t));
		for(int i = 1; i <= cnt; i++)
			rnd[i] = Rand(1, 1e9);
		for(int i = 1; i <= n; i++)
			b[i] = a[i];
		for(int i = 1; i <= n; i++)
			add(i, rnd[a[i]]);
		for(int i = 1; i <= m; i++) {
			if(q[i].opt == 1) {
				add(q[i].x, -rnd[b[q[i].x]]);
				b[q[i].x] = q[i].y;
				add(q[i].x, rnd[b[q[i].x]]);
			}
			else ans[i] &= (qry(q[i].x, q[i].y) % q[i].k == 0);
		}
	}
	for(int i = 1; i <= m; i++)
		if(q[i].opt == 2) puts(ans[i] ? "YES" : "NO");
	return 0;
}
```


---

## 作者：Leasier (赞：4)

Update on 2022.10.31：感谢 @[LinkyChristian](https://www.luogu.com.cn/user/124918)。

赛时一直去想对 $k$ 根号分治，然后就寄了……

顺便说一句：**在 CF 上不要用 `rand()`，请使用 `mt19937`。**

------------

前置芝士：[树状数组](https://oi-wiki.org/ds/fenwick/)

直接带修莫队或者树套树等一看就不太行，考虑乱搞。

我们可以先对所有 $a_i, x$ 离散化，然后给每个出现过的数赋一个**随机权值**。

修改时用树状数组维护随机权值的前缀和，查询时 check 一下 $[l, r]$ 的长度是否为 $k$ 的倍数以及 $[l, r]$ 内随机权值的和是不是 $k$ 的倍数。

卡时直到贴近时限即可（我取的是 $2.8$ 秒）。

现在我们来考虑一下其正确性。显然，当 $k = 1$ 时始终为 `YES`，这一点我们便无需考虑；当 $k > 1$，单次操作的正确率感性理解不小于 $\frac{1}{2}$，于是只要你循环足够多次，这个随机化的正确率是相当高的。

~~据说这个 Trick 叫 XOR Hashing？~~

再次提醒：**在 CF 上不要用 `rand()`，请使用 `mt19937`。**~~否则你会 WA on 5（~~

代码：
```cpp
#include <algorithm>
#include <random>
#include <cstdio>
#include <ctime>

using namespace std;

typedef long long ll;

const int mod = 1e9 + 7;
mt19937 rnd(time(NULL));
int a[300007], b[600007], op[300007], pos[300007], x[300007], l[300007], r[300007], k[300007], val[600007], pre[300007];
ll tree[300007];
bool ans[300007];

inline void init(int n){
	for (register int i = 1; i <= n; i++){
		tree[i] = 0;
	}
}

inline int read(){
	int ans = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return ans;
}

inline int lowbit(int x){
	return x & (-x);
}

inline void add(int n, int x, int k){
	while (x <= n){
		tree[x] += k;
		x += lowbit(x);
	}
}

inline ll get_sum(int x){
	ll ans = 0;
	while (x > 0){
		ans += tree[x];
		x -= lowbit(x);
	}
	return ans;
}

int main(){
	int n = read(), q = read(), m = 0;
	srand(time(NULL));
	for (register int i = 1; i <= n; i++){
		a[i] = b[++m] = read();
	}
	for (register int i = 1; i <= q; i++){
		op[i] = read();
		if (op[i] == 1){
			pos[i] = read();
			x[i] = b[++m] = read();
		} else {
			l[i] = read();
			r[i] = read();
			k[i] = read();
			ans[i] = (r[i] - l[i] + 1) % k[i] == 0;
		}
	}
	sort(b + 1, b + m + 1);
	m = unique(b + 1, b + m + 1) - b - 1;
	for (register int i = 1; i <= n; i++){
		a[i] = lower_bound(b + 1, b + m + 1, a[i]) - b;
	}
	for (register int i = 1; i <= q; i++){
		if (op[i] == 1) x[i] = lower_bound(b + 1, b + m + 1, x[i]) - b;
	}
	while (1.0 * clock() / CLOCKS_PER_SEC < 2.8){
		init(n);
		for (register int i = 1; i <= m; i++){
			val[i] = rnd() % mod;
		}
		for (register int i = 1; i <= n; i++){
			pre[i] = a[i];
			add(n, i, val[a[i]]);
		}
		for (register int i = 1; i <= q; i++){
			if (op[i] == 1){
				add(n, pos[i], val[x[i]] - val[pre[pos[i]]]);
				pre[pos[i]] = x[i];
			} else {
				ans[i] &= (get_sum(r[i]) - get_sum(l[i] - 1)) % k[i] == 0;
			}
		}
	}
	for (register int i = 1; i <= q; i++){
		if (op[i] == 2){
			if (ans[i]){
				printf("YES\n");
			} else {
				printf("NO\n");
			}
		}
	}
	return 0;
}
```

---

## 作者：DengDuck (赞：3)

好好好，哈希技巧+调参好题。

首先我们考虑一个没有正确性的哈希做法，就是直接求区间和，利用区间和来表示每个数字出现的数量，如果和是 $k$ 的倍数，那么就是 `YES`。

对于应该输出 `YES` 的区间，其和为：

$$
\sum i\times cnt_i
$$

$cnt_i$ 表示 $i$ 出现的次数，显然对于这种情况满足 $k|cnt_i$，所以成立。

但是对于 `NO` 的区间也可能可以凑成 $k$ 的倍数，咋办呢？

我们发现由于重点是 $cnt_i$，$i$ 是啥其实不重要，而我们这种错误情况是因为数值产生了不必要的数量关系导致的。

考虑对于某个 $i$ 随机权值 $h_i$，用同样的方法来判断，可以多做几遍，正确性更高。

离散化数字之后做，可以直接开数组存随机值，快一点，开更多的树状数组。

时间复杂度为 $\mathcal O(nK\log nK)$，其中 $K$ 是树状数组的数量。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=3e5+1;
const LL M=6e5+1;
const LL K=22;
LL n,m,a[N][K+1],t[N][K+1],op,x,y,z,ma[K+1][M],cnt;
map<LL,LL>hav;
LL gethsh(LL x)
{
	if(!hav.count(x))hav[x]=++cnt;
	return hav[x];
}
LL lowbit(LL x)
{
	return x&-x;
}
void update(LL x,LL k,LL y)
{
	while(x<=n)
	{
		t[x][k]+=y;
		x+=lowbit(x);
	}
}
LL getsum(LL x,LL k)
{
	LL ans=0;
	while(x)
	{
		ans+=t[x][k];
		x-=lowbit(x);
	}
	return ans;
}
void change(LL x,LL k)
{
	k=gethsh(k);
	a[x][0]=k;
	for(int i=1;i<=K;i++)update(x,i,-a[x][i]);
	for(int i=1;i<=K;i++)a[x][i]=ma[i][k];	
	for(int i=1;i<=K;i++)update(x,i,a[x][i]);
}
int main()
{
	srand(time(0));
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n+m;i++)
	{
		for(int j=1;j<=K;j++)ma[j][i]=i;
	}
	for(int i=1;i<=K;i++)
	{
		random_shuffle(ma[i]+1,ma[i]+n+m+1);
	}
	
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i][0]);
		change(i,a[i][0]);
	}
	while(m--)
	{
		scanf("%lld%lld%lld",&op,&x,&y);
		if(op==1)change(x,y);
		else 
		{
			scanf("%lld",&z);
			LL flg=0;
			for(int i=1;i<=K;i++)
			{
				flg|=(getsum(y,i)-getsum(x-1,i))%z;
			}
			if(!flg)puts("YES");
			else puts("NO");
		}
	}
}

```

---

## 作者：lfxxx (赞：2)

很厉害的题目。

直接做显然是没法做，考虑放宽条件，假若每个数出现次数是 $k$ 的倍数那么和一定是 $k$ 的倍数，这个显然用脚都能卡，但是我们可以考虑给每个数赋上一个随机权值再去 check，这么做的错误率不高于 $\frac{1}{2}$，因为你考虑对于一个集合 $S$ 中的数，取出其中一个数，无论剩下的数如何填，要满足条件的话取出的数模 $k$ 的余数唯一，而最差情况 $k = 2$ 时也只有 $\frac{1}{2}$ 的概率会把不合法判成合法（$k = 1$ 显然无论如何都合法）。 

因此做 $\log n$ 次即可保证正确性，每次可以用树状数组简单维护。时间复杂度 $O(n \log^2 n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 3e5+114;
int a[maxn],b[maxn];
int answer[maxn];
int n,q;
int opt[maxn],l[maxn],r[maxn],k[maxn],pos[maxn],x[maxn];
int tr[maxn];
void add(int u,int c){
    while(u<maxn) tr[u]+=c,u+=(u&(-u));
}
int pre(int u){
    int res=0;
    while(u>0) res+=tr[u],u-=(u&(-u));
    return res;
}
const int warma = 30;
mt19937 rd(time(0));
int w[maxn<<1];
int trans(int u){
    return w[u];
}
int tot;
int c[maxn<<1];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i],c[++tot]=a[i];
    for(int i=1;i<=q;i++){
        cin>>opt[i];
        if(opt[i]==1) cin>>pos[i]>>x[i],c[++tot]=x[i];
        else cin>>l[i]>>r[i]>>k[i];
    }
    sort(c+1,c+tot+1);
    for(int i=1;i<=n;i++){
        int l=1,r=tot+1;
        while(l+1<r){
            int mid=(l+r)>>1;
            if(a[i]>=c[mid]) l=mid;
            else r=mid;
        }
        a[i]=l;
    }
    for(int i=1;i<=q;i++){
        if(opt[i]!=1) continue;
        int l=1,r=tot+1;
        while(l+1<r){
            int mid=(l+r)>>1;
            if(x[i]>=c[mid]) l=mid;
            else r=mid;
        }
        x[i]=l;
    }
    for(int i=1;i<=warma;i++){
        memset(tr,0,sizeof(tr));
        for(int j=1;j<=tot;j++) w[j]=rd();
        for(int j=1;j<=n;j++) b[j]=a[j],add(j,trans(b[j]));
        for(int j=1;j<=q;j++){
            if(opt[j]==1){
                add(pos[j],-trans(b[pos[j]]));
                b[pos[j]]=x[j];
                add(pos[j],trans(b[pos[j]]));
            }else{
                if((pre(r[j])-pre(l[j]-1))%k[j]!=0) answer[j]=1;
            }   
        }
    }
    for(int i=1;i<=q;i++) 
        if(opt[i]==2) cout<<(answer[i]==1?"NO\n":"YES\n");
    return 0;
}
/*
10 3
1234 2 3 3 2 1 1 2 3 4
1 1 1
1 10 5
2 1 9 3
*/
```

---

## 作者：JimmyLee (赞：2)

# CF1746F Kazaee 题解

## 题目描述

[CF1746F Kazaee](https://www.luogu.com.cn/problem/CF1746F)

## 题目解法

看到题目能想到一个相当劣的树状数组做法：先离散化，然后对每个数开个树状数组，每次查询区间内每个数的个数。

这个做法相当劣，修改 $O(\log{n})$，查询 $O(n\log n)$，总的复杂度为 $O(n^2 \log n)$ 无法通过本题。（空间也开不下）

好像还有一个 $O(n^{\frac{5}{3} }\log n)$ 的莫队做法，但是也过不去...

所以就只能考虑乱搞。

我们考虑一个区间 $[l,r]$，如果每个出现过的正整数的出现次数都是 $k$ 的倍数，那么一定有：

$$
\sum^r_{i=l} a_i \equiv 0 \pmod k
$$

但是上述条件只是一个必要条件，并不是充分条件。

其错误率大概是 $\frac{1}{k}$。

考虑随机化。

序列 $b_j$ 是将 $a$ 序列中每个值随机分配了一个值域中的新值后生成的序列。

比如 $a=\{1,2,2,4,3\}$，那么我们令 $b_1=\{2,1,1,5,4\}$，$b_2, b_3$ 同理。

如果对于所有的 $T$ 个 $b_j$，其均满足：

$$
\sum^r_{i=l} b_{j,i}\equiv 0 \pmod k
$$

那么判断的错误率就是 $\frac{1}{k^T}$。

$T$ 的取值就自行调参，$T$ 过大会导致超时，$T$ 过小会判断错误。

实现方法就是开 $T$ 组树状数组。

~~用结构体和 vector 的树状数组被卡了，请各位注意卡常~~

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 300005
#define i64 long long
const int T=30;

template< typename T >inline void read(T &x)
{
	char c=getchar();x=0;int f=0;
	for(;!isdigit(c);c=getchar()) f|=(c=='-');
	for(;isdigit(c);c=getchar()) x=((x<<3)+(x<<1)+(c^48));
	x=f?-x:x;
}

template< typename T >inline void write(T x)
{
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10^48);
}

template< typename T,typename ... Args > 
inline void read(T &_x, Args &... args) 
{read(_x), read(args...);}

template< typename T,typename ... Args > 
inline void write(T _x, Args ... args) 
{ write(_x), write(args...);}

unordered_map<int, int> hsh;

int cnt=0;

i64 ta[T][maxn];
int dic[T][maxn<<1];

int val(int x, int t) {return dic[t][hsh.count(x)?(hsh[x]):(hsh[x]=++cnt)];}
void modify(int i, int v, int t) {for(;i<maxn;i+=i&-i) ta[t][i]+=v;}
i64 __qry(int i, int t) {i64 r=0; for(;i;i-=i&-i) r+=ta[t][i]; return r;}
i64 query(int l, int r, int t) {return __qry(r, t)-__qry(l-1, t);}

int lis[maxn];  

#define rng for(int t=0;t<T;t++)

int main()
{
    srand(time(0));
    int n,q;
    read(n, q);
    rng for(int j=1;j<=n+q;j++) dic[t][j]=j;
    rng random_shuffle(dic[t]+1, dic[t]+1+n+q); 
    // 赋随机值的方法被卡了，所以用 random_shuffle()

    for(int i=1;i<=n;i++)
    {
        read(lis[i]);
        rng modify(i, val(lis[i], t), t);
    }
    while(q--)
    {
        int opt, l, r, k;
        read(opt);
        if(opt==1)
        {
            read(l, r);
            rng modify(l, val(r, t)-val(lis[l], t), t);
            lis[l]=r;
        }
        else
        {
            read(l, r, k);
            if((r-l+1)%k) {puts("NO");continue;}
            int tag=0;
            rng if(query(l, r, t)%k) {tag=1; break;}
            puts(tag?"NO":"YES");
        }
    }
}
```

---

## 作者：allenchoi (赞：2)

好久没写题解力，来水一发...  
### 科技：  
随机化，树状数组/线段树，离散化（可用 map 代替）~~线性筛~~  
### 思路：  
首先，只有区间长度是 $k$ 的倍数时才能满足条件。  
其次，将每一个数赋一个权值，这样，如果一个区间内所有数出现的次数都是 $k$ 的倍数，那么这个区间的权值和肯定也是 $k$ 的倍数。  
但是发现，这只是一个必要而不充分的条件，那怎么办呢？  
可以想到，给每一种数随机一个权值，然后依此处理 $q$ 个操作（树状数组单点修改区间查询），重复做若干遍。如果一个询问在某一次时发现区间和模 $k$ 不为 $0$，那么肯定就是 "NO" 了。为了同时顾虑时间复杂度和正确性，就重复做 $30$ 遍吧。  
但是在做题时，我用 rand 函数随机赋值一直 WA，没办法，想出一个下策：  
筛出 $[2,10^7]$ 内的质数，然后把其中的一半乘二（不然在 $k=2$ 时容易挂，样例都过不了），每次赋值就从这些数中随机选出一个，这样就 AC 力。   
[惨烈的提交记录](https://www.luogu.com.cn/record/list?pid=CF1746F&user=allenchoi)  
### 代码：  
~~~cpp  
#include <bits/stdc++.h>
#define ll long long 
#define lb(x) (x & (-x))
using namespace std;
const int N = 3e5 + 5,M = 1e7 + 1;
int n,q,cnt,tot,p[M],f[M],a[N],b[N],w[N << 1],val[N << 1],ans[N];
vector <int> v;
map <int,int> mp;
struct qry{int op,p,v,l,r;} k[N];
struct TR
{
	ll sum[N];
	void update(int p,int v){for(int i = p;i <= n;i += lb(i)) sum[i] += v;}
	ll query(int p)
	{
		ll ret = 0;
		for(int i = p;i;i -= lb(i)) ret += sum[i];
		return ret;
	}
} tr;
int rnd()
{
	int ret = 0;
	ret = rand() % 100;
	ret = ret * 100 + rand() % 100;
	ret = ret * 100 + rand() % 100;
	ret = ret * 100 + rand() % 100;
	return ret;
}
int main()
{
	for(int i = 2;i <= 10000000;i++)
	{
		if(!f[i]) p[++tot] = i;
		for(int j = 1;j <= tot && 1LL * i * p[j] <= 10000000;j++)
		{
			f[i * p[j]] = 1;
			if(i % p[j] == 0) break;
		}
	}
	for(int i = 1;i <= tot;i += 2) p[i] *= 2;
	srand(time(0));
	scanf("%d%d",&n,&q);
	for(int i = 1;i <= n;i++)
	{
		scanf("%d",&a[i]);
		v.push_back(a[i]);
	}
	for(int i = 1;i <= q;i++)
	{
		scanf("%d",&k[i].op);
		if(k[i].op == 1)
		{
			scanf("%d%d",&k[i].p,&k[i].v);
			v.push_back(k[i].v);
		}
		else
		{
			scanf("%d%d%d",&k[i].l,&k[i].r,&k[i].p);
			ans[i] = 1;
		}
	}
	sort(v.begin(),v.end());
	w[cnt = 1] = v[0];
	for(int i = 1;i < v.size();i++) if(v[i] != v[i - 1]) w[++cnt] = v[i];
	for(int i = 1;i <= n;i++) a[i] = lower_bound(w + 1,w + cnt + 1,a[i]) - w;
	for(int i = 1;i <= q;i++) k[i].v = lower_bound(w + 1,w + cnt + 1,k[i].v) - w;
	for(int _ = 1;_ <= 30;_++)
	{
		memset(tr.sum,0,sizeof(tr.sum));
		for(int i = 1;i <= cnt;i++) val[i] = p[rnd() % tot + 1];
		for(int i = 1;i <= n;i++)
		{
			b[i] = a[i];
			tr.update(i,val[a[i]]);
		}
		for(int i = 1;i <= q;i++)
			if(k[i].op == 1)
			{
				tr.update(k[i].p,val[k[i].v] - val[b[k[i].p]]);
				b[k[i].p] = k[i].v;
			}
			else if(!ans[i] || (k[i].r - k[i].l + 1) % k[i].p || (tr.query(k[i].r) - tr.query(k[i].l - 1)) % k[i].p) ans[i] = 0;
	}
	for(int i = 1;i <= q;i++) if(k[i].op == 2) puts(ans[i] ? "YES" : "NO");
	return 0;
}
~~~

---

## 作者：FReQuenter (赞：2)

## 思路

首先明确：如果一些数的出现次数都是 $k$ 的倍数，那么和一定是 $k$ 的倍数。和不是 $k$ 的倍数，出现次数也不是 $k$ 的倍数。

证明：设这些数为 $a_1,a_2,...,a_n$，其中有 $m$ 个值，为 $b_1,b_2,...,b_m$，每个值有 $p_i\times k$ 个，则和为 $b_1p_1k+b_2p_2k+...b_mp_mk=(b_1p_1+b_2p_2+...+b_mp_m)k$，有因子 $k$，一定是 $k$ 的倍数。

但是反之，和是 $k$ 的倍数，出现次数则**不一定**是 $k$ 的倍数。

那我们就先假设和是 $k$ 的倍数，出现次数则**一定**是 $k$ 的倍数，随后，我们可以多次重复将每一个相同数的值设为一个随机数，重复多次计算，如果出现一次和不是 $k$ 倍数，出现次数就一定不是 $k$ 的倍数。

这个 trick 称为 XOR-Hashing，（CSPS2-2022T3好像可以用这个 trick 做（？）

最后注意，随机数种子要设好，模数要设好，循环次数要设好。~~当然人品也挺重要的。~~`rand` 还是可以用的，CF赛时小心被卡，赛后没事，但是推荐 `mt19937`。

## 代码

```cpp
#include<bits/stdc++.h>
#define lowbit(x) ((x)&(-x))
#define exa exxxa
#define int long long
using namespace std;
int n,m,c[300005],a[300005],tmp[300005],exa[600005],l[300005],r[300005],k[300005],rd[600005],exalen,anslen,maxn;
bool ans[300005];
void update(int x,int v){
    for(;x<=n;x+=lowbit(x)) c[x]+=v;
}
int getsum(int x){
    int sum=0;
    for(;x;x-=lowbit(x)) sum+=c[x];
    return sum;
}
int getsum(int l,int r){
    return getsum(r)-getsum(l-1);
}
//以上都是正常的树状数组
signed main(){
    srand(398788419);
    //随便选的种子。。
    int t=clock();
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i],exa[++exalen]=a[i];//exa用于离散化，先记录所有数
    for(int i=1,op;i<=m;i++){
        cin>>op;
        if(op==1) cin>>l[i]>>exa[++exalen],r[i]=exa[exalen];
        //exa用于离散化，先记录所有数
        else cin>>l[i]>>r[i]>>k[i];
    }
    sort(exa+1,exa+exalen+1);
    maxn=exalen=unique(exa+1,exa+exalen+1)-exa-1;
    for(int i=1;i<=n;i++) a[i]=lower_bound(exa+1,exa+exalen+1,a[i])-exa;
    for(int i=1;i<=m;i++) if(!k[i]) r[i]=lower_bound(exa+1,exa+exalen+1,r[i])-exa;
    //离散化，方便随机数赋值
    for(int i=1;i<=m;i++) ans[i]=true;
    //一开始都设为真
    for(;clock()-t<=2.8*CLOCKS_PER_SEC;){
        //卡时运行
        for(int i=1;i<=maxn;i++) rd[i]=rand()*rand()%19260817;
        //随便选的模数。。
        for(int i=1;i<=n;i++) c[i]=0;
        //清空树状数组
        for(int i=1;i<=n;i++) tmp[i]=rd[a[i]];
        //赋随机值
        for(int i=1;i<=n;i++) update(i,tmp[i]);
        //加入树状数组
        for(int i=1;i<=m;i++){
			if(!k[i]) update(l[i],rd[r[i]]-tmp[l[i]]),tmp[l[i]]=rd[r[i]];
        //按题意修改
			else if(getsum(l[i],r[i])%k[i]) ans[i]=false;
        ///检查是否合法
		}
    }
    for(int i=1;i<=m;i++) if(k[i]) cout<<(ans[i]?"YES":"NO")<<'\n';//输出
    return 0;
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

首先可直接判掉 $k \nmid r-l+1$。

注意到 $k\mid\displaystyle\sum_{i=l}^r a_i$ 是必要条件，若不满足一定不合法。但是这并不充分，于是考虑对 $a_i$ 随机赋权进行判断。这样做单次错误率不超过 $\dfrac{1}{2}$，所以多跑几次正确率就有着显著提升。

跑大概 $30$ 次稳过。实在担心程序正确率可以打个卡时。

---

## 作者：zac2010 (赞：1)

[题目链接](https://codeforces.com/problemset/problem/1746/F)。

这个数据范围，显然出题人出这题的本意不是让我们用带修莫队过题（当然有人过），而我们又难以找到很好的 $\text{DS}$ 维护方法。

故考虑另辟蹊径。对于所有 $a_i,x$，不妨把值相同的归入一个等价类。对于一个等价类，随机出一个 $[0,1]$ 间的权值。我们把等价类的权值代替原来的 $a_i,x$，会发现：此时我们输出 `YES` 的必要条件还是：区间 $[l,r]$ 内是否每个出现过的正整数的出现次数都是 $k$ 的倍数。

尝试分析这样做的正确概率。因为我们当前的判断判断条件是必要条件而不是充分条件，所以只可能把 `NO` 误判成 `YES`。假设区间中有 $x$ 个数出现次数不为 $k$ 的倍数——记这些数为 $i_1,i_2,\dots,i_r$，他们分别在区间中出现了 $c_{i_1},c_{i_2},\dots,c_{i_r}$ 次。对于一个等价类随机一个 $[0,1]$ 就等价于对于每个数决策它选不选。最终我们会误判当且仅当选出的数总和是 $k$ 的倍数。由于数据随机，因此单组询问错误的概率约为 $\frac{1}{k}$（$k$ 取 $2$ 时合法且达到最大），$q$ 组询问的错误概率不超过为 $\frac{q}{2}$。

但如果对这个随机再判断的过程做 $T$ 次呢（最终输出 `YES` 当且仅当每次都满足条件）？只有每次都误判，最终才会误判答案。也就是说，这个做法正确率至少达到了 $q\times2^{-T}$。

$T$ 建议取到 $30$ 左右，再大容易被卡常。

```cpp
#include <bits/stdc++.h>
#define FL(i, a, b) for(int i = (a); i <= (b); i++)
#define FR(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
const int N = 3e5 + 10;
struct Q{int op, x, y, k;} p[N];
int n, q, a[N], key[N * 2], ans[N];
unordered_map<int, int> mp;
inline int read(){
    int x = 0, f = 1;
    char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') f = -1; ch = getchar();}
    while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x * f;
}
struct BIT{
    int n = 0, c[N];
    void clear(){fill(c, c + n + 1, 0);}
    void resize(int t){fill(c + n + 1, c + t + 1, 0); n = t;}
    void add(int x, int v){
        for(; x <= n; x += x & -x) c[x] += v;
    }
    int ask(int x, int ret = 0){
        for(; x; x -= x & -x) ret += c[x];
        return ret;
    }
} b;
int main(){
    b.resize(n = read()), q = read();
    int op, x, y, k, flag;
    FL(i, 1, n){
        a[i] = read();
        if(!mp[a[i]]) mp[a[i]] = rnd() % (1ll << 31);
        key[i] = mp[a[i]];
    }
    FL(i, 1, q){
        p[i].op = read(), p[i].x = read(), p[i].y = read();
        if(p[i].op == 1){
            if(!mp[p[i].y]) mp[p[i].y] = rnd() % (1ll << 31);
            key[n + i] = mp[p[i].y];
        }
        if(p[i].op == 2) p[i].k = read(); ans[i] = 1;
    }
    FL(j, 1, 30){
        unordered_map<int, int>().swap(mp), b.clear();
        FL(i, 1, n) b.add(i, a[i] = key[i] & 1), key[i] >>= 1;
        FL(i, 1, q) if(ans[i]){
            op = p[i].op, x = p[i].x;
            if(op == 1){
                y = key[n + i] & 1, key[n + i] >>= 1;
                b.add(x, y - a[x]), a[x] = y;
            }
            else{
                y = p[i].y, k = p[i].k, flag = 1;
                if((b.ask(y) - b.ask(x - 1)) % k) ans[i] = 0;
            }
        }
    }
    FL(i, 1, q) if(p[i].op > 1) printf(ans[i]? "YES\n" : "NO\n");
    return 0;
}
```


---

## 作者：EXODUS (赞：1)

# Part 1：前言
套路随机化题。

# Part 2：正文

首先 $k$ 的倍数看起来就不像是普通数据结构能够维护的，而 $n,q\leq 3\times 10^5$ 和带修让根号数据结构看起来也不太靠谱，对于统计数字出现个数我们可以考虑莫队，但是复杂度至少是 $O(n^{\frac{5}{3}}\text{poly})$ 这种过不去的东西。

我们试图从头开始考虑。如果一个数 $x$ 出现次数是 $k$ 的倍数，那么其区间和至少应当被 $k$ 整除。那么我们可以枚举每一个数字，计算其出现次数，判断其是否为 $k$ 的倍数。

但问题是我们不能单个的做，考虑把所有数字打包判断。上面的做法告诉我们一个很好的性质是，如果所有数字的出现次数都是 $k$ 的倍数，其出现次数之和也一定为 $k$ 的倍数，当然这是必要不充分的条件。

接下来就是被出烂的套路。考虑每次随机取一个数集的子集判断，然后再次计算出现次数和。然后随机 $B$ 个子集做这件事情。下面分析正确性，感性理解对于一个区间限制最坏的情况是存在一对数 $x,y$，满足 $k\mid cnt_x+cnt_y$ 且 $k\nmid cnt_x,cnt_y$，那么此时会被判错当且仅当 $x,y$ 被全选或 $x,y$ 全不选。注意到随机到判错情况的概率是 $\dfrac{1}{2}$。因此 $B$ 次的错误率是 $\dfrac{1}{2^B}$，取 $B=30$ 即可。

时间复杂度 $O(nB\log n)$，写线段树可能会被卡常。


# Part 3：代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,l,r) for(int i(l);i<=(r);++i)
#define per(i,r,l) for(int i(r);i>=(l);--i)
#define eb emplace_back
#define Debug(...) fprintf(stderr,__VA_ARGS__)
int read(){
	int ans=0,flg=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
	while(isdigit(ch))ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
	return ans*flg;
}
template<typename T>
void read(T &x){
	x=0;T flg=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
	while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	x*=flg;
}
template<typename T,typename... Args>
void read(T &x,Args &...args){read(x),read(args...);}
const int N=3e5+7,B=30,full=(1<<B)-1;
int n,Q,a[N];
map<int,int>key;
// mt19937 g(chrono::steady_clock::now().time_since_epoch().count());
mt19937 g(19260817);
struct Bit{
#define lowbit(i) ((i)&(-i))
	int arr[N];
	void add(int p,int v){for(;p<=n;p+=lowbit(p))arr[p]+=v;}
	int ask(int p){int res=0;for(;p;p-=lowbit(p))res+=arr[p];return res;}
#undef lowbit
}bit[B+7];

int rnd(){return g()&full;}
int shift(int v,int j){return (v>>j)&1;}

void upd(int x,int v){
	if(!key.count(v))key[v]=rnd();
	int X=key[a[x]],V=key[v];
	for(int i=0;i<B;i++)bit[i].add(x,shift(V,i)-shift(X,i));
	a[x]=v;
}

int main(){
	read(n,Q);
	for(int i=1;i<=n;i++){
		a[i]=read();
		if(!key.count(a[i]))key[a[i]]=rnd();
		int V=key[a[i]];
		for(int j=0;j<B;j++)bit[j].add(i,shift(V,j));
	}
	// for(int i=1;i<=n;i++)printf("%d %d\n",a[i],key[a[i]]);
	while(Q--){
		int op,l,r,k;read(op,l,r);
		if(op==1)upd(l,r);
		else{
			read(k);int res=1;
			for(int j=0,x;j<B;j++)x=bit[j].ask(r)-bit[j].ask(l-1),res&=(x%k==0);
			puts(res?"YES":"NO");
		}
	}
	return 0;
}
```



---

## 作者：xianggl (赞：1)

题意：

给定一个长度为 $n$ 的数列，有 $m$ 个操作。

1、将 $a_x$ 换成 $y$。

2、询问 所有数在 $l, r$ 区间内的出现次数是否全为 $k$ 的倍数。

题解：

没听说过就不会系列。

考虑给每个数一个随机值。

若所有数出现次数都是 $k$ 的倍数，则区间和对 $k$ 取模一定为 $0$。

但若区间和是 $k$ 的倍数，不一定满足条件，但概率可以计算。

考虑所有模 $k$ 余数不等于 $0$ 的项，除开最后一项，算出它们的和对 $k$ 取模的余数。

那么最后一个，贡献为出现次数 $\times $ 随机权值，令前者为 $x$，后者为 $y$。

所以要求 $x \times y \bmod k = r$ 的概率。

令 $d = \gcd(x, k)$，方程变为 $\frac{x}{d} \times y \bmod \frac{k}{d} = \frac{r}{d}$。

此时 $\frac{x}{d}$ 和 $\frac{k}{d}$ 互质，概率为 $\frac{d}{k}$。

因为 $0 < x < k$，$d$ 为 $k$ 的因子，所以这个数不会大于 $\frac{1}{2}$。

$T$ 取 $30$ 即可。

代码：

```
#include <bits/stdc++.h>
#define ri register int
#define ll long long
using namespace std;
mt19937 rnd(time(0));
template <typename tp> struct Fenwick {
	vector<tp>c;
	Fenwick(int n) {c.resize(n+1);}
	inline int lowbit(int x) {return x&(-x);}
	inline void add(int x,tp d) {
		for(;x<(int)c.size();x+=lowbit(x))c[x]+=d;
	}
	inline tp query(int x) {
		tp res=0;
		for(;x>=1;x-=lowbit(x))res+=c[x];
		return res;
	}
	inline tp rangequery(int l,int r) {
		return query(r)-query(l-1);
	}
};
int main() {
	int n,m;
	scanf("%d%d",&n,&m);
	vector<int>a(n+1);
	vector<int>disc;
	for(ri i=1;i<=n;i++)scanf("%d",&a[i]),disc.push_back(a[i]);
	vector<int>l(m+1),r(m+1),k(m+1);
	for(ri i=1;i<=m;i++) {
		int op;
		scanf("%d%d%d",&op,&l[i],&r[i]);
		if(op==2)scanf("%d",&k[i]);
		else disc.push_back(r[i]);
	}
	sort(disc.begin(),disc.end());
	disc.resize(unique(disc.begin(),disc.end())-disc.begin());
	for(ri i=1;i<=n;i++)a[i]=lower_bound(disc.begin(),disc.end(),a[i])-disc.begin()+1;
	for(ri i=1;i<=m;i++)
		if(!k[i])r[i]=lower_bound(disc.begin(),disc.end(),r[i])-disc.begin()+1;
	vector<int>ans(m+1,1);
	int mx=(int)disc.size();
	for(ri t=0;t<30;t++) {
		vector<int>f(mx+1);
		for(ri i=1;i<=mx;i++)f[i]=rnd()%998244353;
		Fenwick<ll>fen(n+1);
		auto b=a;
		for(ri i=1;i<=n;i++)b[i]=f[b[i]],fen.add(i,b[i]);
		for(ri i=1;i<=m;i++) {
			if(!k[i]) {
				fen.add(l[i],f[r[i]]-b[l[i]]);
				b[l[i]]=f[r[i]];
			}
			else {
				ans[i]&=fen.rangequery(l[i],r[i])%k[i]==0;
			}
		}
	}
	for(ri i=1;i<=m;i++)
		if(k[i])printf("%s\n",ans[i]?"Yes":"No");
	return 0;
}

```


---

## 作者：zesqwq (赞：1)

# CF1746F Kazaee 题解

[题目传送门](https://codeforces.com/problemset/problem/1746/F)

我们发现这个东西很难维护，~~直接想到一个 $O(n^{\frac5 3} \log n)$ 的带修莫队~~，当然这肯定是过不去的（。 

然后我们可以考虑哈希这个方法，把每一个数随机映射为另一个数，然后使用树状树组维护区间和，看是否是查询的 $k$ 的倍数。

然后我们发现这个做法正确率很低，因此要多搞几次，大概 $30$ 次的样子就可以了。如果您被卡空间了，可以尝试把所有操作离线下来一次一次检测而不是所有都放在一起检测。

代码非常好写，就不贴了。

---

## 作者：mlvx (赞：1)

容易发现当区间的每个数都出现次数为 $k$ 的倍数时，则 $\sum\limits_{i=l}^r\operatorname h(a_i)$ 也是 $k$ 的倍数。

其中 $\operatorname h(x)$ 是一个映射函数，这里取 $base^x(base\in\operatorname{prime},base>k)$。

要取多个 $base$ 来维护，降低错误率。

搞个线段树维护一下区间 $\operatorname h$ 函数的和即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define i128 __int128
#define pl (p<<1)
#define pr (p<<1|1)
const int N=3e5+10,T=25;const ull mod=(1ull<<31)-1,base[]={8589001,8460731,3864673,6617003,10151761,5373691,5839637,9629483,14560267,11945957,5017141,12522799,10610389,4649207,11837237,8554849,10480661,9020993,8182091,12345211,4683247,8779037,11534851,9457313,6371879,9643391,7326691,6369023,10562659,13616899};
inline ull Mod(ull x){ull tmp=(x>>31)+(x&mod);return tmp>=mod?tmp-mod:tmp;}
inline ull qpow(ull a,ull b,ull ret=1){for(;b;b>>=1,a=Mod((i128)a*a))if(b&1)ret=Mod((i128)ret*a);return ret;}
int n,q,a[N];
struct SGT{
    ull sum[N<<2][T];
    inline void pushup(int p){for(int i=0;i<T;i++)sum[p][i]=sum[pl][i]+sum[pr][i];}
    void build(int l,int r,int p){
        if(l==r){
            for(int i=0;i<T;i++)sum[p][i]=qpow(base[i],a[l]);
            return;
        }int mid=l+r>>1;build(l,mid,pl),build(mid+1,r,pr),pushup(p);
    }void update(int l,int r,int k,int v,int p){
        if(l==r){
            for(int i=0;i<T;i++)sum[p][i]=qpow(base[i],v);
            return;
        }int mid=l+r>>1;
        if(k<=mid)update(l,mid,k,v,pl);
        else update(mid+1,r,k,v,pr);
        pushup(p);
    }ull query(int l,int r,int le,int ri,int p,int x){
        if(l>=le&&r<=ri)return sum[p][x];
        int mid=l+r>>1;ull ret=0;
        if(le<=mid)ret+=query(l,mid,le,ri,pl,x);
        if(ri>mid)ret+=query(mid+1,r,le,ri,pr,x);
        return ret;
    }
}sgt;
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    sgt.build(1,n,1);
    for(int op,x,y,v;q--;){
        scanf("%d%d%d",&op,&x,&y);
        if(op==1)sgt.update(1,n,x,y,1);
        else{
            scanf("%d",&v);
            for(int i=0;i<T;i++)if(sgt.query(1,n,x,y,1,i)%v){puts("NO");goto A;}
            puts("YES");A:;
        }
    }
    return 0;
}
```

---

## 作者：Fa_Nanf1204 (赞：1)

### 分析：
将 $a$ 中所有出现的数字随机映射为一个较大的数，那么此时考虑如何判断出现次数是 $k$ 的倍数。考虑用区间和来判定，如果此区间和是 $k$ 的倍数，则这些数有可现次数是 $k$ 的倍数，反之则不可能，因为出现 $k$ 的倍数次的数一定能被整除，而其他的则是随机数，所以有极大的概率能够成功判定，至少是不会判成不是。

考虑提升此算法的正确率，很简单，多用几组随机数来跑就可以了，亲测 $30$ 组就够用了。

由于常数极大，建议使用树状数组来维护。
### Code:
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 300005
#define K 35
#define lowbit(i) (i&-i)
using namespace std;
int n,m;
const ll mod=991824435373;
const int times=30;
struct node{
	int op,p,x;
	int l,r,k; 
}q[N];
int a[N];
int b[N<<1],cnt;
mt19937 rnd(time(0));
ll tr[N][K],rn[N<<1][K];
void add(int x,ll v,int k){
	for(int i=x;i<=n;i+=lowbit(i)){
		tr[i][k]+=v;
	}
}
ll query(int x,int k){
	ll sum=0;
	for(int i=x;i;i-=lowbit(i)){
		sum+=tr[i][k];
	}
	return sum;
}
int main(){
	cin.tie(),cout.tie(),ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		b[++cnt]=a[i];
	}
	for(int i=1;i<=m;i++){
		cin>>q[i].op;
		if(q[i].op==1){
			cin>>q[i].p>>q[i].x;
			b[++cnt]=q[i].x;
		}
		else{
			cin>>q[i].l>>q[i].r>>q[i].k;
		}
	}
	sort(b+1,b+cnt+1);
	cnt=unique(b+1,b+cnt+1)-b-1;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(b+1,b+cnt+1,a[i])-b;
	}
	for(int i=1;i<=m;i++){
		if(q[i].op==1){
			q[i].x=lower_bound(b+1,b+cnt+1,q[i].x)-b;
		}
	}
	for(int i=1;i<=n+m;i++){
		for(int j=1;j<=times;j++)rn[i][j]=rnd()%mod;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=times;j++){
			add(i,rn[a[i]][j],j);
		}
	}
	for(int i=1;i<=m;i++){
		if(q[i].op==1){
			for(int j=1;j<=times;j++){
				add(q[i].p,rn[q[i].x][j]-rn[a[q[i].p]][j],j);
			}
			a[q[i].p]=q[i].x;
		}
		else{
			bool flag=0;
			for(int j=1;j<=times;j++){
				flag|=((query(q[i].r,j)-query(q[i].l-1,j))%q[i].k);
			}
			if(flag) cout<<"NO\n";
			else cout<<"YES\n";
		}
	}
	return 0;
} 
```

---

## 作者：Exp10re (赞：1)

APIO 来的。

其实我一直以为以前写过这题题解来着。

## 解题思路

出现次数不太好维护，考虑乱搞。

考虑一个区间里面所有数出现次数均为 $k$ 的倍数的充分不必要条件：若一个区间里面所有数出现次数均为 $k$ 的倍数，则这些数的和也为 $k$ 的倍数。

当然，如果每次询问只是对原数列中该区间判断和是否为 $k$ 的倍数的话很容易被 Hack：这个区间的和不仅取决于所有数出现次数是否均为 $k$ 的倍数，还取决于这些数的值。

这些数的值不应该影响判断的结果。故考虑将原数列中每一个数随机映射到新数列中，使得相等的数映射值相同，并在新映射下判断和是否为 $k$ 的倍数。

显然新映射的每个数出现次数与其在原数列中映射前出现次数相同，故若满足条件，在新映射下和一定为 $k$ 的倍数。

考虑对于新映射不能够判断出出现次数并不是均为 $k$ 的倍数的情况：我们考虑一个数在该区间中出现了 $c$ 次，那么该数随机映射为 $b$ 后，$cb \mid k$ 的概率为 $\frac {\operatorname{gcd}(c,k)} k$，即错判概率。当 $c=\frac 2 k$ 的时候错判概率达到最大值 $\frac 1 2$。

故对于所有询问，构建 $30$ 组不同映射。在最坏情况下一次询问错判概率是 $\frac 1 {2^{30}}$，所有判断都正确的概率是 ${(1-\frac 1 {2^{30}})}^q\approx 0.9997$，可以通过。

---

## 作者：cosf (赞：0)

算是随机化入门题了。今年 WC 好像讲过。

离线一下，考虑将每一个数等概率映射到 $0$ 或者 $1$，则如果每个数出现次数都是 $k$ 的倍数，则映射之后的和一样是 $k$ 的倍数。而映射之后和是 $k$ 的倍数情况下，原本不满足条件的概率比较小。因此，我们可以映射多几次。

具体实现可以对每个映射开一个树状数组，并且额外建立一个数组表示是否保留（也就是是否为 $1$），每次修改对每一个树状数组都修改就行了。如果映射 $T$ 次，则空间复杂度 $O(Tn)$，时间复杂度 $O(Tn\log n)$。

反正我 $40$ 次就过了。出错概率还是非常小的，并且也只跑了 $1$ 秒左右。

```cpp
#define MAXN 300005
#define MAXK 40

struct Rnd { /* some random number generating code */ };
Rnd rnd;

int n, m;

int v[MAXN];

struct Query
{
    int o, l, r, x;
} q[MAXN];

int b[MAXN << 1];
int idx = 0;

#define lb(x) ((x) & -(x))

struct Bit
{
    bool ins[MAXN << 1];
    int t[MAXN];

    void init()
    {
        for (int i = 1; i <= idx; i++)
        {
            ins[i] = rnd();
        }
    }

    void add(int p, int v)
    {
        while (p <= n)
        {
            t[p] += v;
            p += lb(p);
        }
    }

    int query(int p)
    {
        int r = 0;
        while (p)
        {
            r += t[p];
            p -= lb(p);
        }
        return r;
    }

    int query(int l, int r)
    {
        return query(r) - query(l - 1);
    }

} t[MAXK];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> v[i];
        b[++idx] = v[i];
    }
    for (int i = 1; i <= m; i++)
    {
        cin >> q[i].o >> q[i].l;
        if (q[i].o == 2)
        {
            cin >> q[i].r;
        }
        cin >> q[i].x;
        if (q[i].o == 1)
        {
            b[++idx] = q[i].x;
        }
    }
    sort(b + 1, b + idx + 1);
    idx = unique(b + 1, b + idx + 1) - b - 1;
    for (int i = 0; i < MAXK; i++)
    {
        t[i].init();
    }
    for (int i = 1; i <= n; i++)
    {
        v[i] = lower_bound(b + 1, b + idx + 1, v[i]) - b;
        for (int j = 0; j < MAXK; j++)
        {
            if (t[j].ins[v[i]])
            {
                t[j].add(i, 1);
            }
        }
    }
    for (int i = 1; i <= m; i++)
    {
        if (q[i].o == 1)
        {
            int nv = lower_bound(b + 1, b + idx + 1, q[i].x) - b;
            for (int j = 0; j < MAXK; j++)
            {
                if (t[j].ins[v[q[i].l]])
                {
                    t[j].add(q[i].l, -1);
                }
                if (t[j].ins[nv])
                {
                    t[j].add(q[i].l, 1);
                }
            }
            v[q[i].l] = nv;
        }
        else
        {
            if ((q[i].r - q[i].l + 1) % q[i].x)
            {
                cout << "NO\n";
                continue;
            }
            bool e = 1;
            for (int j = 0; j < MAXK; j++)
            {
                if (t[j].query(q[i].l, q[i].r) % q[i].x)
                {
                    e = 0;
                    break;
                }
            }
            if (e)
            {
                cout << "YES\n";
            }
            else
            {
                cout << "NO\n";
            }
        }
    }
    return 0;
}

```

---

## 作者：wmrqwq (赞：0)

这是一篇视频题解。

![](bilibili:BV1E9XWYzEUV?t=668)

[参考代码](https://codeforces.com/problemset/submission/1746/311765446)

---

## 作者：lilong (赞：0)

发现直接维护区间内每个数的出现次数并不好做。不妨把这个条件外推，假设 $[l,r]$ 中每个数的出现次数都是 $k$ 的倍数，那么 $\sum_{i=l}^r a_i$ 也是 $k$ 的倍数，即**后者是前者的必要条件**，并且当 $a_i$ 较大时，后者成立时前者成立的概率会越大。

因此我们可以这样判定：如果 $\sum_{i=l}^r a_i$ 是 $k$ 的倍数，那么 $[l,r]$ 中每个数的出现次数都是 $k$ 的倍数。当然，在此之前，我们要对 $a_i$（以及修改的值）进行随机替换（只需确保原本相同的数替换后仍相同），从而提高判定正确率。判定需要进行一定的次数，我取了 $30$ 次。初始时假定都是成立的，一旦有一次判定不成立即为不成立。若干次以后，错误率已经极低了，基本可以忽略。

于是用树状数组维护序列即可。随机时可以使用 mt19937 以增大随机数的分布范围。


```cpp
#include <bits/stdc++.h>
#include <iostream>
#include <cstdio>
#define int long long
#define N 1000001

using namespace std;

mt19937 rnd( time( NULL ) );

struct Q
{
	int op,l,r,k,x,y,flag;
}q[N];

int n,a[N],b[N],c[N],d[N],f[N],t[N],tot,m;

int lowbit( int x )
{
	return x & ( -x );
}

void upd( int x , int y )
{
	for( int i = x ; i <= n ; i += lowbit( i ) )
		t[i] += y;
	return;
}

int que( int x )
{
	int sum = 0;
	for( int i = x ; i >= 1 ; i -= lowbit( i ) )
		sum += t[i];
	return sum;
}

signed main()
{
	ios::sync_with_stdio( false );
	cin.tie( 0 );
	cout.tie( 0 );
	cin >> n >> m;
	for( int i = 1 ; i <= n ; i ++ )
		cin >> a[i],c[++ tot] = a[i];
	for( int i = 1 ; i <= m ; i ++ )
	{
		cin >> q[i].op;
		if( q[i].op == 1 )
			cin >> q[i].x >> q[i].y,c[++ tot] = q[i].y;
		if( q[i].op == 2 )
			cin >> q[i].l >> q[i].r >> q[i].k,q[i].flag = 1;
	}
	sort( c + 1 , c + tot + 1 );
	tot = unique( c + 1 , c + tot + 1 ) - c - 1;
	for( int i = 1 ; i <= n ; i ++ )
		a[i] = lower_bound( c + 1 , c + tot + 1 , a[i] ) - c;
	for( int i = 1 ; i <= m ; i ++ )
		if( q[i].op == 1 )
			q[i].y = lower_bound( c + 1 , c + tot + 1 , q[i].y ) - c;
	int T = 30;
	while( T -- )
	{
		for( int i = 1 ; i <= tot ; i ++ )
			b[i] = rnd() % 1000000007 + 1;
		for( int i = 1 ; i <= n ; i ++ )
			t[i] = 0;
		for( int i = 1 ; i <= n ; i ++ )
			upd( i , b[a[i]] ),f[i] = a[i];
		for( int i = 1 ; i <= m ; i ++ )
		{
			if( q[i].op == 1 ) upd( q[i].x , b[q[i].y] - b[f[q[i].x]] ),f[q[i].x] = q[i].y;
			if( q[i].op == 2 )
			{
				if( ( que( q[i].r ) - que( q[i].l - 1 ) ) % q[i].k )
					q[i].flag = 0;
			}
		}
	}
	for( int i = 1 ; i <= m ; i ++ )
		if( q[i].op == 2 )
		{
			if( q[i].flag ) cout << "YES\n";
			else cout << "NO\n";
		}
	return 0;
}
```

---

## 作者：freoepn (赞：0)

考虑集合哈希，对每个元素随机赋权，区间中每个数出现次数是 $k$ 的倍数的必要条件是区间哈希和为 $k$ 的倍数，但是也有可能出现区间哈希和为 $k$ 的倍数但不满足条件的情况。因为区间和随机，出现错误的概率是 $\frac{1}{k}$，做 $40$ 次哈希的最大错误概率为 $\frac{1}{2^{40}}$，非常小，可以通过。

---

## 作者：Little_Entropy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1746F)

核心思想：哈希
### 思路分析
#### 核心逻辑
本题需要维护的是区间内每个数出现次数为 k 的倍数。发现了吗，这道题目需要把次数抽象了出来。

我们将数组进行哈希。哈希了之后，如果区间和不是k的倍数，那么这个区间一定有某个数出现次数不是k的倍数。
如果这个区间所有的不同数出现次数都为 k 倍数，那么不管怎么随机，区间和一定为 k 的倍数。

#### 优化技巧

此外，只要时间允许，多随机几次验证，采用类似增加模拟退火正确率的思路，只要有一个不成立，那么这个区间就是 NO。

最后，维护区间和用树状数组。

### AC代码

```cpp
#include <iostream>
#include <cmath>
#include <random>
#include <ctime>
#include <algorithm>
#include <cstring>

using namespace std;
std::mt19937 rnd(time(0));
#define maxn 300010
#define LL long long
int n, Q;
LL tree[maxn << 1];
LL a[maxn], Hash[maxn << 1], b[maxn];
int ans[maxn];
struct node
{
    int val, id;
} num[maxn << 1];
struct Ques
{
    int opt, l, r, val;
} q[maxn];

inline bool cmp(node x, node y)
{
    return x.val < y.val;
}

inline int lowbit(int k)
{
    return k & -k;
}

inline void update(int x, LL delta)
{
    for (; x <= n; x += lowbit(x))
        tree[x] += delta;
}

inline LL query(int x)
{
    LL sum = 0;
    if (x == 0) return 0;
    for (; x; x -= lowbit(x))
        sum += tree[x];
    return sum;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
    cin>>n>>Q;
    int cnt_num = n;
    for (int i = 1; i <= n; ++i)
    {
        cin>>a[i];
        num[i].val = a[i];
        num[i].id = i;
    }
    for (int i = 1; i <= Q; ++i)
    {
        cin>>q[i].opt;
        if (q[i].opt == 1)
        {
            cin>>q[i].l>>q[i].val;
            num[++cnt_num].val = q[i].val;
            num[cnt_num].id = n + i;
        }
        else
            cin>>q[i].l>>q[i].r>>q[i].val;
    }
    sort(num + 1, num + 1 + cnt_num, cmp);
    num[0].val = num[1].val - 1;
    int p = 0;
    for (int i = 1; i <= cnt_num; ++i)
    {
        if (num[i].val != num[i - 1].val)p++;
        if (num[i].id <= n)a[num[i].id] = p;
        else q[num[i].id - n].val = p;
    }
    for (int i = 1; i <= n; ++i)b[i] = a[i];
    for (int i = 1; i <= Q; ++i)ans[i] = 1;
    for (int times = 1; times <= 30; ++times)
    {
        memset(tree, 0, sizeof(tree));
        for (int i = 1; i <= n; ++i)a[i] = b[i];
        for (int i = 1; i <= p; ++i)Hash[i] = rnd();
        for (int i = 1; i <= n; ++i)update(i, Hash[a[i]]);
        for (int i = 1; i <= Q; ++i)
        {
            if (q[i].opt == 1)
            {
                int pos = q[i].l;
                update(pos, Hash[q[i].val] - Hash[a[pos]]);
                a[pos] = q[i].val;
            }
            else if (ans[i])
            {
                LL sum = query(q[i].r) - query(q[i].l - 1);
                if (sum % q[i].val != 0)
                    ans[i] = 0;
            }
        }
    }

    for (int i = 1; i <= Q; ++i)
        if (q[i].opt == 2)
            if (ans[i])
                puts("YES");
            else
                puts("NO");

    return 0;
}

```

---

## 作者：yyz1005 (赞：0)

逆天数据我打漏一个下标让我过了 $7$ 个点还有几个是 $3e5$ 的数据。

这个题目本身用正规数据结构显然完全没办法，考虑用奇技淫巧。

我们注意到对于题目的询问，$k|a_l+a_{l+1}+\cdots+a_r$ 是题目的询问的一个充分条件。

同时如果构造 $f:[1,10^9] \rightarrow [1,S]$ 来把所有权值替换成随机的数，上述要求依然满足。

所以我们考虑去做 $T$ 次随机替换权值，当 $T$ 次替换都成立时，原询问正确的概率是非常高的。

对于这样的充分条件，本质是单点修改区间求和用树状数组可以快速解决，综上解决问题，时间复杂度为 $O(Tn \log n)$。可能需要一定的时间优化措施。

代码中 $T=40$。

[Code](https://codeforces.com/contest/1746/submission/272921501)

---

## 作者：zyn_ (赞：0)

为了方便叙述，定义一个区间 $[l,r]$ 有 $k$ 性质，当且仅当 $[l,r]$ 中每个出现过的正整数的出现次数均为 $k$ 的倍数。

容易发现 $k\mid\sum_{i=l}^{r}a_i$ 是 $k$ 性质的必要但非充分条件。

进一步地，若给每个数 $x$ 赋权值 $v_x$，则 $k\mid\sum_{i=l}^{r}v_{a_i}$ 也是 $k$ 性质的必要但非充分条件。

现在令 $v_x=0$ 或 $1$，当 $k\mid\sum_{i=l}^{r}v_{a_i}$ 时断言 $[l,r]$ 有 $k$ 性质，考虑这样的错误率。

若答案为 `Yes`，错误率为 $0$。若答案为 `No`，此时存在一个 $x$ 在 $[l,r]$ 中出现 $t_x$ 次，且 $k\nmid t_x$。对于 $v_x=0$ 或 $1$，无论其余 $v_i$ 如何，至多只有一种情况使 $k\mid\sum_{i=l}^{r}v_{a_i}$ 导致判错，故错误率 $\le\dfrac{1}{2}$。

于是随机 $40$ 组 $v_i$，只有当对每组 $v_i$，$k\mid\sum_{i=l}^{r}v_{a_i}$ 成立时，才判定 $[l,r]$ 具有 $k$ 性质。

需要维护 $\sum_{i=l}^{r}v_{a_i}$，树状数组即可。

记得 $a_i$ 要离散化。

另外，随机 $v_i$ 时不要用 `rand()`，用 `mt19937`，原因见[此](https://www.luogu.com.cn/discuss/847906)。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 300009
#define M 40
int n,q,a[N],op[N],l[N],r[N],k[N],x[M+1][N],p[N<<1],cnt,v[N<<1][M+1],ans;
inline void upd(int i,int p,int d){for(;p<=n;p+=p&-p)x[i][p]+=d;}
inline int qr(int i,int p){static int r;r=0;for(;p;p-=p&-p)r+=x[i][p];return r;}
mt19937 mt(time(0));
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;++i)scanf("%d",&a[i]),p[i]=a[i];
	cnt=n;
	for(int i=1;i<=q;++i){
		scanf("%d%d%d",&op[i],&l[i],&r[i]);
		if(op[i]==2)scanf("%d",&k[i]);
		else p[++cnt]=r[i];
	}
	sort(p+1,p+cnt+1);cnt=unique(p+1,p+cnt+1)-p-1;
	for(int i=1;i<=n;++i)a[i]=lower_bound(p+1,p+cnt+1,a[i])-p;
	for(int i=1;i<=q;++i)if(op[i]==1)r[i]=lower_bound(p+1,p+cnt+1,r[i])-p;
	for(int i=1;i<=cnt;++i)for(int j=1;j<=M;++j)v[i][j]=mt()&1;
	for(int i=1;i<=n;++i)for(int j=1;j<=M;++j)if(v[a[i]][j])upd(j,i,1);
	for(int i=1;i<=q;++i){
		if(op[i]==1){
			for(int j=1;j<=M;++j)if(v[a[l[i]]][j])upd(j,l[i],-1);
			a[l[i]]=r[i];
			for(int j=1;j<=M;++j)if(v[r[i]][j])upd(j,l[i],1);
		}else{
			ans=1;
			for(int j=1;j<=M;++j)if((qr(j,r[i])-qr(j,l[i]-1))%k[i]){ans=0;break;}
			puts(ans?"YES":"NO");
		}
	}
	return 0;
}
```

---

## 作者：船酱魔王 (赞：0)

## 题意回顾

维护一个数组，支持单点修改区间查询所有数的出现次数是否都是 $ k $ 的倍数。

## 分析

考虑类似于 [魔法](https://www.luogu.com.cn/problem/P6273) 一题的套路，即寻找这种不太好判定的条件的必要条件，然后即可以在合理时间复杂度内以一定的误判概率得出判定结果。

所有数的出现次数都是 $ k $ 的倍数，可以推导出所有数的和都是 $ k $ 的倍数，如果把每个数赋一个随机权值，那么这个权值的和也是 $ k $ 的倍数。

$ k=1 $ 或区间长度不是 $ k $ 的倍数时剪枝，剩下的用 $ 21 $ 组随机权值依次检验即可，单次错误概率在 $ k=2 $ 时最大，大约为 $ \frac{1}{2^{21}} $。

温情提示：打 CF 时还是不要沉迷于这种随机算法题，因为 CF 数据甚至能卡掉时间种子 `rand()`，还是要多加点玄学乱搞例如随机打乱之类的。

## 参考实现

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
#include <cstdlib>
#include <ctime>
using namespace std;
const int N = 3e5 + 5;
const int R = 21;
int n, q;
int a[N];
map<int, int> mp;
int ct = 0;
long long c[R][N];
int et[R][N * 2];
inline int lowbit(int x) {
	return x & (-x);
}
inline void eplus(int id, int x, int v) {
	for(int i = x; i <= n; i += lowbit(i)) c[id][i] += v;
}
int sed = 0;
inline int rnd() {
    return sed = (sed * 283 + sed / 244 + 2223) % 1145141;
}
inline void change(int x, int v) {
	if(mp.find(v) == mp.end()) {
		mp[v] = ++ct;
		for(int i = 0; i < R; i++) et[i][ct] = rand();
		for(int i = 0; i < R; i++) {
		    int l = rnd() % R;
		    int r = rnd() % R;
		    swap(et[l][ct], et[r][ct]);
		}
	}
	int tr = mp[a[x]];
	for(int i = 0; i < R; i++) eplus(i, x, -et[i][tr]);
	tr = mp[v];
	for(int i = 0; i < R; i++) eplus(i, x, et[i][tr]);
	a[x] = v;
}
inline long long query(int id, int x) {
	long long res = 0;
	for(int i = x; i >= 1; i -= lowbit(i)) {
		res += c[id][i];
	}
	return res;
}
inline int read() {
    int f = 0;
    char ch = '#';
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') f = f * 10 + ch - '0', ch = getchar();
    return f;
}
int main() {
	srand(1145141);
	n = read(), q = read();
	mp[0] = 0;
	for(int i = 1; i <= n; i++) change(i, read());
	int op, l, r, k;
	for(int qi = 1; qi <= q; qi++) {
		op = read();
		if(op == 1) {
            l = read(), k = read();
			change(l, k);
		} else {
			l = read(), r = read(), k = read();
			if((r - l + 1) % k != 0) {
				puts("NO");
				continue;
			}
			if(k == 1) {
			    puts("YES");
			    continue;
			}
			for(int i = 0; i < R; i++) {
				long long ec = query(i, r) - query(i, l - 1);
				if(ec % k != 0) {
					k = -1;
					break;
				}
			}
			puts((k == -1) ? "NO" : "YES");
		}
	}
	return 0;
}
```

---

## 作者：carp_oier (赞：0)

# advertisement

这位靓仔，你都来看我的题解了，为什么不来[我的博客](https://www.cnblogs.com/carp-oier/p/17751477.html)看呢
# prologue

数组范围一定要看好了开，不然容易我一样，调试调了一页多。

还有就是不要傻乎乎地只跑一次和哈希，因为和哈希（从下面地佬的题解中才知道）它其实算作是一种 trick（类比 SA（Stimulate_anneal）。

# analysis

这个题目的第二个询问时询问一个区间里面出现过的正整数的次数是否为 $k$ 的倍数。这个题可以说是[这个题目](https://acm.ecnu.edu.cn/problem/115/ "这个题目")的 pro plus 版本。这样子的话么，我们就可以往这个方面考虑。

我们再继续分析这个题目。

我们和上面所示的例题一样，将统计出现次数，哈希一下。

然后，我们记 $G(l, r)$ 为一个区间里面的数字哈希和，如果满足题目中的性质，那么我们会有:

$$k \mid G(l, r)$$

证明：取其中的一个数 $a_i$ 为例，出现了 $k$ 次则相加和一定为 $k$ 的 $a_i$ 倍数。对于满足条件的 $G(l, r)$ 其中每一个数都满足条件，由此得证。

最后我们就转化成了给每一个数字的哈希值求和，然后看这个值能否整除 $k$。

还有就是对于这个里面的时候进行离散化要考虑好常数问题，然后选择合适的方法进行离散化。

然后我们分析一下正确性，对于一个区间限制最坏的情况是存在一对数 $(x, y)$，满足 $k \mid cnt_x + cnt_y, k \nmid cnt_x, k\nmid cnt_y$ 那么这个时候我们判断错误当且仅当 $(x, y)$ 全被选，或者 $(x, y)$ 全不选。我们随机判错的概率是 $\frac{1}{2}$，所以当我们进行了 $B$ 次判断，我们判错的概率就是 $\frac{1}{2^B}$，这个时候取到 $B = 30$ 即可。

# code time

```
#include <bits/stdc++.h>
using namespace std;
#define ll long long 
#define rl register ll
#define lowbit(x) (x & -x)
mt19937 rnd; // 一个很好用的随机化，与rand相比这个会更快一点，听别的题解们说不用这个会被卡/fad

template <class T> // 快读板子 

inline void read(T &res)
{
    char ch; bool f = 0 ;
    while((ch = getchar()) < '0' || ch > '9') f |= ch == '-';
    res = ch ^ 48;
    while((ch = getchar()) <= '9' && ch >= '0') res = (res << 1) + (res << 3) + (ch ^ 48);
    res = f ? ~res + 1 : res;
}

const ll N = 3e5 + 10;

ll n, a[N], m, lst[N];

ll tr[N], ls[N << 2], tot, rd[N << 2]; // 想好数组大小

bool ans[N];

struct node
{
    ll op, x, y, z;
}q[N << 1];

inline ll Rand(ll l, ll r)
{
    uniform_int_distribution<ll>distribution(l, r);
    return distribution(rnd);
}

inline void add(ll x, ll c)
{
    for(; x <= n; x += lowbit(x)) tr[x] += c;
}

inline ll sum(ll x)
{
    ll res = 0;
    for(; x; x -= lowbit(x)) res += tr[x];
    return res;
}

int main()
{
    // freopen("1.in", "r", stdin), freopen("1.out", "w", stdout);

    read(n), read(m);

    for(rl i=1; i <= n; ++ i)
    {
        read(a[i]);
        ls[ ++ tot] = a[i];
    }

    for(rl i=1; i <= m; ++ i)
    {
        read(q[i].op), read(q[i].x), read(q[i].y);
        if(q[i].op == 1) ls[ ++ tot] = q[i].y;
        else read(q[i].z);
    }

    sort(ls + 1, ls + 1 + tot);

    tot = unique(ls + 1, ls + 1 + tot) - ls - 1;

    for(rl i=1; i <= n; ++ i) a[i] = lower_bound(ls + 1, ls + 1 + tot, a[i]) - ls;

    for(rl i=1; i <= m; ++ i) if(q[i].op == 1) q[i].y = lower_bound(ls + 1, ls + 1 + tot, q[i].y) - ls;

    memset(ans, 1, sizeof ans);

    for(rl i=0; i < 30; ++ i)
    {
        memset(tr, 0, sizeof tr);
        for(rl i=1; i <= tot; ++ i) rd[i] = Rand(1, 1e9);
        for(rl i=1; i <= n; ++ i) lst[i] = a[i];
        for(rl i=1; i <= n; ++ i) add(i, rd[a[i]]);
        for(rl i=1; i <= m; ++ i)
        {
            if(q[i].op == 1)
            {
                add(q[i].x, -rd[lst[q[i].x]]);
                lst[q[i].x] = q[i].y;
                add(q[i].x, rd[lst[q[i].x]]);
            }
            else ans[i] &= ((sum(q[i].y) - sum(q[i].x - 1)) % q[i].z == 0);
        }
    }

    for(rl i=1; i <= m; ++ i) if(q[i].op == 2) (ans[i] == 1) ? puts("YES") : puts("NO");
    return 0;
}
```

---

## 作者：Hisaishi_Kanade (赞：0)

神仙题。

看到这个题我的第一反应是写带修莫队，但看数据范围便觉得不对劲了。

对于 $n,q\le 3\times 10^5$，带修莫队基本上是过不去的。

我们考虑一个区间 $[l,r]$ 每个数都出现 $k$ 的倍数次有啥特征？ 显然 $k\mid\left(\sum\limits_{i=l}^r a_i\right)$。

当然，仅仅满足这个并不一定就满足原条件，但不满足这个条件一定不满足原条件。

**但是我们其实并不关心 $a_i$ 的大小，无论是 $1$ 还是 $10^9$，这个条件满足就是满足**。原来相等的 $a_i$ 全改成另一个数 $a_i^\prime$，也不会使得满足变得不满足。

那么，如果我们进行足够次的 $a_{i}\gets a_i\prime$，并进行检查，是不是就可以保证正确性？

答案是正确的。显然，对于 $k=2$，有错误率 $P=\dfrac 1 2$；对于 $k>2$，$P\le \dfrac 1 2$。如果我们随 $Q=30$ 左右，错误率甚至会 $<\dfrac 1 {2^{40}}$，这个量级和 $q$ 的 $3\times 10^5$，几乎不会出错~~出错就是脸黑~~。

总复杂度 $O(Qq\log n)$。

---

