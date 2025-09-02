# [ABC354F] Useless for LIS

## 题目描述

给定一个长度为 $N$ 的整数序列 $A$。

对于 $t = 1, 2, \dots, N$，请判断 $A_t$ 是否有可能被包含在 $A$ 的最长严格递增子序列中。

$A_t$ 有可能被包含在 $A$ 的最长递增子序列中，指的是存在如下情况：

- 设最长递增子序列的长度为 $L$。存在一个长度为 $L$ 的严格递增的整数序列 $i = (i_1, i_2, \dots, i_L)$，满足以下条件：
  - $A_{i_1}, A_{i_2}, \dots, A_{i_L}$ 构成 $A$ 的一个最长严格递增子序列。
  - 存在某个 $k\ (1 \leq k \leq L)$ 使得 $i_k = t$。

给定 $T$ 组测试数据，请分别输出每组的答案。

最长递增子序列的定义如下：$A$ 的子序列是指从 $A$ 中取出若干元素，保持原有顺序得到的序列。$A$ 的最长递增子序列是指所有严格递增子序列中长度最大的那一个。

## 说明/提示

### 数据范围

- $1 \leq T \leq 2 \times 10^5$
- $1 \leq N \leq 2 \times 10^5$
- $1 \leq A_i \leq 10^9$
- 所有测试数据中 $N$ 的总和不超过 $2 \times 10^5$

### 样例解释 1

最长递增子序列之一为 $(2, 4, 5)$，长度为 $3$。$(1, 4, 5)$ 也是最长递增子序列之一。但是，没有包含 $A_5$ 的最长递增子序列。因此，应输出 $1, 2, 3, 4$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
1
5
2 1 4 5 3```

### 输出

```
4
1 2 3 4```

## 样例 #2

### 输入

```
2
6
2 5 3 4 3 4
5
10000 1000 100 1 10```

### 输出

```
5
1 3 4 5 6
2
4 5```

# 题解

## 作者：sodalyghat (赞：7)

### 分析
要求每一个点是否存在一个最长上升子序列包含它。所以我们可以正着做一遍最长上升子序列，倒着做一遍最长下降子序列，然后枚举一个点，尝试拼接以他结尾的最长上升子序列和倒着以他结尾的最长下降子序列，如果拼起来长度和最长上升子序列相等，那么这个点就可取。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Luo_ty{
	const int MAXN = 200005, inf = 0x7fffffff / 2;
	int a[MAXN];
	int p[MAXN], f[MAXN], g[MAXN];
	int inc[MAXN];
	int main(){
		int T, n;
		scanf("%d", &T);
		while(T--){
			scanf("%d", &n);
			for(int i = 1;i <= n;i++){
				scanf("%d", &a[i]);
			}
			for(int i = 1;i <= n;i++) p[i] = inf;
			p[0] = -inf;
			int Max = 0;
			for(int i = 1;i <= n;i++){
				f[i] = lower_bound(p + 1, p + n + 1, a[i]) - p;
				p[f[i]] = a[i];
				Max = max(Max, f[i]);
			}
			for(int i = 1;i <= n;i++) p[i] = inf;
			p[0] = -inf;
			for(int i = 1;i <= n;i++){
				a[i] = -a[i];
			}
			for(int i = n;i;i--){
				g[i] = lower_bound(p + 1, p + n + 1, a[i]) - p;
				p[g[i]] = a[i];
			}
			int ans = 0;
			for(int i = 1;i <= n;i++){
				if(f[i] + g[i] - 1 == Max){
					inc[++ans] = i;
				}
			}
			printf("%d\n", ans);
			for(int i = 1;i <= ans;i++) printf("%d ", inc[i]);
			puts("");
		}
		return 0;
	}
} 
signed main(){
	return Luo_ty::main();
}
```

---

## 作者：ケロシ (赞：3)

非常好的一道板子题。

对于这个问题，我们考虑每一位，求包含这一位的最长上升子序列长度是否等于整个序列的最长上升子序列长度。

然后要计算包含某一位的最长上升子序列长度，这是一个经典的技巧，考虑以这一位结尾的和开头的最长上升子序列长度，然后加起来即可。这可以直接通过树状数组优化 dp 去做，这里不过多阐释，可以去看 [AT_chokudai_S001_h](https://www.luogu.com.cn/problem/AT_chokudai_S001_h)。

时间复杂度 $O(n \log n)$。

```cpp
const int N = 2e5 + 5;
int n, a[N], b[N], len;
int f[N], g[N];
struct fenwick {
	int a[N];
	int lowbit(int x) {
		return -x & x;
	}
	int query(int u) {
		int res = 0;
		for(int i = u; i; i -= lowbit(i)) {
			chmax(res, a[i]);
		}
		return res;
	}
	void modify(int u, int x) {
		for(int i = u; i <= n; i += lowbit(i)) {
			chmax(a[i], x);
		}
	}
	void clear(int n) {
		FOR(i, 1, n) a[i] = 0;
	}
} t1, t2;
void solve() {
	cin >> n;
	t1.clear(n); t2.clear(n);
	FOR(i, 1, n) cin >> a[i], b[i] = a[i];
	sort(b + 1, b + n + 1);
	len = unique(b + 1, b + n + 1) - b - 1;
	FOR(i, 1, n) a[i] = lower_bound(b + 1, b + len + 1, a[i]) - b;
	FOR(i, 1, n) {
		f[i] = t1.query(a[i] - 1);
		t1.modify(a[i], f[i] + 1);
	}
	ROF(i, n, 1) {
		g[i] = t2.query(n - a[i] + 1 - 1);
		t2.modify(n - a[i] + 1, g[i] + 1);
	}
	vector<int> ans;
	int res = 0;
	FOR(i, 1, n) chmax(res, f[i] + g[i] + 1); 
	FOR(i, 1, n) if(f[i] + g[i] + 1 == res) ans.push_back(i);
	cout << SZ(ans) << endl;
	for(auto x : ans) cout << x << " ";
	cout << endl;
}
```

---

## 作者：rhn7 (赞：2)

史前最水 F，但分值还挺高。

存在一个 LIS 包含 $i$，其实就是包含 $i$ 的 LIS 长度等于整个序列的 LIS 长度。

包含 $i$ 的 LIS 长度等于以 $i$ 为结尾的 LIS 长度加以 $i$ 为开头的 LIS 长度减一（$i$ 被算了两次，所以要减一）。

$n$ 比较大，要用二分或树状数组优化 LIS，时间复杂度为 $O(n \log n)$。

最后，别瞎用 `memset`，用过的数再清空。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int T,n,a[N],dp[N],dp2[N],f[N],h[N],t[N];
int main(){
	scanf("%d",&T);
	memset(dp2,0x3f,sizeof(dp2));
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		int ans=0,ans2=0,lh=0,cnt=0;
		for(int i=1;i<=n;i++){
			int l=0,r=ans,s;
			while(l<=r){
				int mid=(l+r)/2;
				if(dp[mid]<a[i]){
					s=mid;
					l=mid+1;
				}else{
					r=mid-1;
				}
			}
			dp[s+1]=a[i];
			f[i]=s+1;
			h[++lh]=s+1;
			ans=max(ans,s+1);
		}
		for(int i=1;i<=lh;i++) dp[h[i]]=0;
		lh=ans2=0;
		for(int i=n;i;i--){
			int l=0,r=ans2,s;
			while(l<=r){
				int mid=(l+r)/2;
				if(dp2[mid]>a[i]){
					s=mid;
					l=mid+1;
				}else{
					r=mid-1;
				}
			}
			dp2[s+1]=a[i];
			ans2=max(ans2,s+1);
			if(s+f[i]==ans) t[++cnt]=i;
			h[++lh]=s+1;
		}
		printf("%d\n",cnt);
		for(int i=cnt;i;i--) printf("%d ",t[i]);
		printf("\n");
		for(int i=1;i<=lh;i++) dp2[h[i]]=0x3f3f3f3f;
	}
	return 0;
}
```

---

## 作者：Fire_flame (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc354_f)

## $\mathtt{Solution}$

这道题乍一看十分不可做，实际是有机可循的。

首先我们定义以 $i$ 结尾的最长上升子序列长度为 $f_i$。

那么我们就有了一个转移方程：

$$f_i=\max\limits_{j<i}\{[a_i>a_j]f_j\}+1$$

这玩意很好优化，直接用一颗权值树状数组维护最大值和前缀最大值即可。

然后考虑一个数 $i$ 怎样才是有效的，会有以下情况：

- $a_i$ 是一个最长上升子序列的结尾

- $i$ 的后面有一个有效的数 $a_x$，使得 $a_x>a_i$ 且 $f_x=f_i+1$。

从后往前枚举即可，复杂度 $O(n\log n)$。

参考代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){
	int s = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){s = s * 10 + (ch - '0');ch = getchar();}
	return s * f;
}
void write(int x){
    if(x < 0){putchar('-'); x = -x;}
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
const int MAXN = 2e5 + 5;
int t, n, k, ans, tot, a[MAXN], b[MAXN], d[MAXN], ans2[MAXN], maxx[MAXN];
struct BIT{//权值树状数组
	int c[MAXN];
	int lowbit(int x){return x & -x;}
	void add(int x, int y){
		for(int i = x;i <= n;i += lowbit(i))c[i] = max(c[i], y);
	}
	int query(int x){
		int res = 0;
		for(int i = x;i;i -= lowbit(i))res = max(res, c[i]);
		return res;
	}
}tr;
int main(){
	t = read();
	while(t --){
		n = read(), ans = tot = 0;
		for(int i = 1;i <= n;i ++)a[i] = read(), b[i] = a[i], tr.c[i] = maxx[i] = 0;//记得清空
		sort(b + 1, b + n + 1);
		int k = unique(b + 1, b + n + 1) - (b + 1);//离散化
		for(int i = 1;i <= n;i ++)
			a[i] = lower_bound(b + 1, b + n + 1, a[i]) - b;
		for(int i = 1;i <= n;i ++)
			d[i] = tr.query(a[i] - 1) + 1, tr.add(a[i], d[i]), ans = max(ans, d[i]);
		//状态转移方程，顺便记录以下最长长度 
		for(int i = n;i >= 1;i --){
			if(d[i] == ans)maxx[d[i]] = max(maxx[d[i]], a[i]), ans2[++ tot] = i;//一个最长上升子序列的结尾是合法的 
			else{
				if(maxx[d[i] + 1] > a[i])ans2[++ tot] = i, maxx[d[i]] = max(maxx[d[i]], a[i]);
				//i的后面有一个有效的数a[x]，使得a[x] > a[i]且f[x] = f[i] + 1
			}
//			printf("%d %d %d\n", i, d[i], maxx[d[i] + 1]);
		}
		sort(ans2 + 1, ans2 + tot + 1);
		printf("%d\n", tot);
		for(int i = 1;i <= tot;i ++)printf("%d ", ans2[i]);
		puts("");
	}
	return 0;
}
```

---

## 作者：small_john (赞：1)

## 前言

打比赛的时候做到[原](https://www.luogu.com.cn/problem/SP57)了，~~贺~~写篇题解纪念一下。

## 思路

考虑 DP，设 $f_i$ 表示 $1\sim i$ 的最长上升子序列的长度，$g_i$ 表示 $i\sim n$ 的最长上升子序列的长度。用树状数组优化即可做到 $O(n\log n)$ 的复杂度。

容易得到，经过位置 $i$ 的最长上升子序列的长度为 $f_i+g_i-1=l_i$（减 $1$ 是因为 $i$ 被算了两次，需要减掉其中一次）。

记这个排列最长上升子序列的长度为 $len=\max_{i=1}^{n}f_i$，那么一个位置 $i$ 属于它的至少一个最长上升子序列当且仅当 $l_i=len$。

模拟上述过程即可，时间复杂度为 $O(n\log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

template<typename T> inline void read(T &x)
{
	x = 0;
	T f = 1;char ch = getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			f = -1,ch = getchar();
			break;
		}
		ch = getchar();
	}
	while(ch>='0'&&ch<='9')
		x = (x<<3)+(x<<1)+ch-48,ch = getchar();
	x*=f;
}
template<typename T = int> inline T read()
{
	T x;read(x);return x;
}
template<typename T> void write(T x)
{
    if(x<0) x = -x,putchar('-');
    if(x>9) write(x/10);
    putchar(x%10+48);
}
template<typename T> inline void writen(T x)
{
    write(x);
    putchar(10);
}
const int N = 2e5+5;
int n,a[N],b[N],f[N],g[N],t[N],m;
#define lowbit(x) (x&(-x))
inline void add(int x,int v)
{
	x++;
	for(;x<=m+1;x+=lowbit(x))
		t[x] = max(t[x],v);
}
inline int ask(int x)
{
	x++;
	int res = 0;
	for(;x;x-=lowbit(x))
		res = max(res,t[x]);
	return res;
}
inline void add_(int x,int v)
{
	x++;
	for(;x;x-=lowbit(x))
		t[x] = max(t[x],v);
}
inline int ask_(int x)
{
	x++;
	int res = 0;
	for(;x<=m+1;x+=lowbit(x))
		res = max(res,t[x]);
	return res;
}
#undef lowbit
set<int> ans;
inline void solve()
{
	read(n);
	for(int i = 1;i<=n;i++)
		read(a[i]),b[i] = a[i];
	for(int i = 1;i<=n+1;i++)
		t[i] = 0;
	sort(b+1,b+n+1),m = unique(b+1,b+n+1)-b-1;
	for(int i = 1;i<=n;i++)
		a[i] = lower_bound(b+1,b+m+1,a[i])-b;
	int mx = 0;
	for(int i = 1;i<=n;i++)
		f[i] = ask(a[i]-1)+1,add(a[i],f[i]),mx = max(mx,f[i]);
	for(int i = 1;i<=n+1;i++)
		t[i] = 0;
	for(int i = n;i;i--)
		g[i] = ask_(a[i]+1)+1,add_(a[i],g[i]);
	ans.clear();
	for(int i = 1;i<=n;i++)
		if(f[i]+g[i]-1==mx)
			ans.insert(i);
	writen(ans.size());
	for(auto i:ans)
		write(i),putchar(32);
	puts("");
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int T;read(T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：ttq012 (赞：1)

感觉远简单于 D。几乎是双倍经验：SP57，~~一年半前做过~~。

有一个极其经典且可以应用到各个方面的结论：

+ 设 $f_i$ 表示 $1\sim i$ 的最长上升子序列的长度。
+ 设 $g_i$ 表示 $n\sim i$ 的最长下降子序列的长度。
+ 设 $L$ 表示 $1\sim n$ 的最长上升子序列的长度。容易发现 $n\sim 1$ 的最长下降子序列的长度 $=L$。

则若一个点 $i$ 可能在任意一个 $1\sim n$ 的最长上升子序列上，则必然有 $f_i+g_i=L+1$。

问题在于如何求出 $f_i$ 和 $g_i$。

显然有初始条件 $f_1=1$，状态转移方程 $f_i=(\max\limits_{j=1,a_j<a_i}^{i-1} f_j)+1$。发现这个问题是二维的 $(i,a_i)$，$i$ 已经排序，所以按照顺序插入，只需要考虑第二维 $a_i$ 的值。容易发现能对答案造成贡献的第二维的值域的区间是连续的且仅求了一个 $\max$ 值，所以考虑离散化之后用线段树来优化 dp。这样就做完了，时间复杂度为 $O(n\log n)$。

```cpp
namespace yhb {

const int N = 200100;
int a[N];
struct Sgt {
    int l, r, mx;
    inline void init(int p) noexcept {
        l = r = p;
        mx = 0;
    }
    inline void color(int v) noexcept {
        mx = max(mx, v);
    }
} z[N << 2];
inline void pushup(int rt) noexcept {
    z[rt].mx = max(z[rt << 1].mx, z[rt << 1 | 1].mx);
    z[rt].l = z[rt << 1].l, z[rt].r = z[rt << 1 | 1].r;
}
inline void build(int l, int r, int rt) noexcept {
    if (l == r) {
        return z[rt].init(l);
    }
    int mid = l + r >> 1;
    build(l, mid, rt << 1);
    build(mid + 1, r, rt << 1 | 1);
    pushup(rt);
}
inline void modify(int rt, int p, int v) noexcept {
    if (z[rt].l == z[rt].r) {
        return z[rt].color(v);
    }
    int mid = z[rt].l + z[rt].r >> 1;
    if (p <= mid) {
        modify(rt << 1, p, v);
    } else {
        modify(rt << 1 | 1, p, v);
    }
    pushup(rt);
}
inline int query(int rt, int ll, int rr) noexcept {
    if (ll > rr) {
        return 0;
    }
    if (ll <= z[rt].l && z[rt].r <= rr) {
        return z[rt].mx;
    }
    int mid = z[rt].l + z[rt].r >> 1, s = 0;
    if (ll <= mid) {
        s = max(s, query(rt << 1, ll, rr));
    }
    if (mid < rr) {
        s = max(s, query(rt << 1 | 1, ll, rr));
    }
    return s;
}
int f[N], g[N], t[N];
void $() {
    int n;
    cin >> n;
    F(i, 1, n) {
        cin >> a[i];
        t[i] = a[i];
    }
    sort(t + 1, t + n + 1);
    int _ = unique(t + 1, t + n + 1) - t - 1;
    F(i, 1, n) {
        a[i] = 1 + lower_bound(t + 1, t + _ + 1, a[i]) - t;
    }
    // cout << '\n';
    build(1, n + 5, 1);
    modify(1, a[1], f[1] = 1);
    F(i, 2, n) {
        modify(1, a[i], f[i] = query(1, 1, a[i] - 1) + 1);
    }
    int leng = *max_element(f + 1, f + n + 1);
    reverse(a + 1, a + n + 1);
    F(i, 1, n) {
        a[i] = n - a[i] + 4;
        // cout << a[i] << ' ';
    }
    // cout << '\n';
    build(1, n + 5, 1);
    modify(1, a[1], g[1] = 1);
    F(i, 2, n) {
        modify(1, a[i], g[i] = query(1, 1, a[i] - 1) + 1);
    }
    vector<int> res;
    F(i, 1, n) {
        // cout << i << ": " << f[i] << ' ' << g[n - i + 1] << '\n';
        if (f[i] + g[n - i + 1] == leng + 1) {
            res.em(i);
        }
    }
    cout << res.size() << '\n';
    for (auto &x : res) {
        cout << x << ' ';
    }
    cout << '\n';
}
}

signed main() {
  int T; cin >> T;
  while (T--) { yhb::$(); }
}
```

---

## 作者：FReQuenter (赞：0)

考虑到一个数存在于任意一条 LIS 中的条件：以它为起点的 LIS 长度加上以它为终点的 LIS 长度和为序列的 LIS。

那么做两遍 LIS，分别处理以上的两个信息就做完了。

求最长的以其为终点的 LIS 可以将序列倒过来做最长不下降子序列。

求 LIS 的方法很多，这里给一个树状数组的。

```cpp
#include<bits/stdc++.h>
#define lowbit(x) ((x)&(-x))
using namespace std;
int n,t,a[200005],b[200005],f[200005],g[200005],c[200005];
void add(int x,int v){
	for(;x<=n;x+=lowbit(x)) c[x]=max(c[x],v);
}
int get(int x){
	int s=0;
	for(;x;x-=lowbit(x)) s=max(s,c[x]);
	return s;
}
void cal(int *f){
	for(int i=0;i<=n+2;i++) f[i]=1,c[i]=0;
	for(int i=1;i<=n;i++){
		f[i]=get(a[i]-1)+1;
		add(a[i],f[i]);
	}
}
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i],b[i]=a[i];
		sort(b+1,b+n+1);
		int tmp=unique(b+1,b+n+1)-b-1;
		for(int i=1;i<=n;i++) a[i]=lower_bound(b+1,b+tmp+1,a[i])-b+1;
		cal(f);
		reverse(a+1,a+n+1);
		for(int i=1;i<=n;i++) a[i]=n+2-a[i];
		cal(g);
		reverse(g+1,g+n+1);
		int le=0;
		for(int i=1;i<=n;i++) le=max(le,f[i]);
		le++;
		int s=0;
		for(int i=1;i<=n;i++) if(f[i]+g[i]==le) s++;
		cout<<s<<'\n';
		for(int i=1;i<=n;i++) if(f[i]+g[i]==le) cout<<i<<' ';
		cout<<'\n';
	}
}
```

---

## 作者：2huk (赞：0)

> - 给定一个长度为 $n$ 的序列 $a$。求出所有 $i$ 使得存在任意一个 $a$ 的最长上升子序列包含 $i$。多测。
> - $1 \le T, n, \sum n \le 2 \times 10^5$，$1 \le a_i \le 10^9$。

首先求解:
- $f(i)$：$a_1, a_2, \dots, a_i$ 的包含 $a_i$ 的 LIS 长度；
- $g(i)$：$a_i, a_{i + 1}, \dots, a_n$ 的包含 $a_i$ 的 LIS 长度；
- $k$：整个 $a$ 的 LIS 长度。

那么 $i$ 合法等价于 $f(i) + g(i) - 1 = k$。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1145e4;

int n, len, a[N], f[N], g[N];

struct BIT {
	int tr[N];
	set<int> S;
	inline void modify(const int u, const int x) {
		for (register int i = u; i <= len; i += i & -i)
			tr[i] = max(tr[i], x),
			S.insert(i);
	}
	inline int query(const int u) {
		register int res = 0;
		for (register int i = u; i; i -= i & -i)
			res = max(res, tr[i]);
		return res;
	}
	void clear() {
		for (int i : S) tr[i] = 0;
		S.clear();
	}
}A, B;

int nums[N];

int main() {
	int T; cin >> T;
	while (T -- ) {
		cin >> n;
		for (int i = 1; i <= n; ++ i ) cin >> a[i], nums[i] = a[i];
		
		A.clear(), B.clear();
		
		sort(nums + 1, nums + n + 1);
		len = unique(nums + 1, nums + n + 1) - nums - 1;
		
		int res = 0;
		for (int i = 1; i <= n; ++ i ) {
			a[i] = lower_bound(nums + 1, nums + len + 1, a[i]) - nums;
			f[i] = A.query(a[i] - 1) + 1;
			A.modify(a[i], f[i]);
			res = max(res, f[i]);
		}
		
		for (int i = n; i; -- i ) {
			g[i] = B.query(len - a[i]) + 1;
			B.modify(len - a[i] + 1, g[i]);
			res = max(res, g[i]);
		}
		
		vector<int> ans;
		for (int i = 1; i <= n; ++ i )
			if (f[i] + g[i] - 1 == res) ans.push_back(i);
		
		cout << ans.size() << '\n';
		for (int t : ans) cout << t << ' ';
		puts("");
	} return 0;
}
```

---

## 作者：Liyunze123 (赞：0)

# 1.题意
给定 $n$ 和 $a$ 数组，求出哪些 $i$，满足 $a_i$ 是某个最长上升子序列的一部分。
# 2.题解
用二分优化，求出以 $a_i$ 结尾的最长上升子序列长度 $s_i$，设 $ans$ 为 $s_i$ 中的最大值。

将所有满足 $s_j=s_i-1$ 且 $j<i$ 且 $a_j<a_i$ 的 $j$ 和 $i$ 连边，对于所有 $s_i=ans$，以 $i$ 为起点遍历这张图，遍历到的点就是满足的点。

我们可以用 vector 存 $e$ 数组，$e_i$ 存的是所有 $s_i=j$ 的 $j$，$i$ 就要和 $e_{s_i-1}$ 的所有点连边。

遍历时，遍历过 $i$ 就不用再次遍历了。

但还是会超时。

我们会发现，某些点搜索的次数太多，我们就可以将遍历过的点从 vector 中删除。

但那些删不了的点，还是会搜索多次，造成超时。

我们发现，没必要对所有的 $s_i=i$ 进行搜索，只要没有 $j$ 满足 $i<j$ 且 $a_j>a_i$ 才遍历 $i$。

很容易证明。
# 3.代码
```
#include<bits/stdc++.h>
#include<vector>
using namespace std;
int t,n,a[200010],k[200010],s[200010],g[200010];
vector<int>e[200010];
int f(int i){
	if(k[i])return 0;
	int cnt=1;
	k[i]=1;
	for(int w=e[s[i]-1].size()-1;w>=0;w--)if(a[e[s[i]-1][w]]<a[i]&&e[s[i]-1][w]<i&&!k[e[s[i]-1][w]]){
		int h=e[s[i]-1][w];
		e[s[i]-1].erase(e[s[i]-1].begin()+w),cnt+=f(h);
	}
	return cnt;
}
void q(int i){
	if(i>9)q(i/10);
	putchar(i%10|0x30);
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		int ans=0,cnt=0,m=0;
		for(int w=1;w<=n;w++){
			scanf("%d",&a[w]);
			int u=lower_bound(g+1,g+ans+1,a[w])-g;
			if(g[ans]<a[w])u=ans+1;
			s[w]=u,e[u].push_back(w),ans=max(ans,u);
			if(!g[u])g[u]=a[w];
			else g[u]=min(g[u],a[w]);
		}
		for(int w=n;w;w--)if(s[w]==ans){
			if(a[w]>m)cnt+=f(w);
			else if(!k[w])cnt++,k[w]=1;
		}
		q(cnt);
		printf("\n");
		for(int w=1;w<=n;w++)if(k[w])q(w),printf(" ");
		printf("\n");
		for(int w=1;w<=n;w++)k[w]=s[w]=g[w]=0,e[w].clear();
	}
	return 0;
}
```

---

## 作者：Redshift_Shine (赞：0)

# 5. [Useless for LIS](https://atcoder.jp/contests/abc354/tasks/abc354_f) - 最长上升子序列并集

## 题意

给出 $n$ 个整数 $a_i$ ，求处于哪些下标上的 $a_i$ 可以构成一个最长上升子序列。

## 思路

还是没有 D 难。

用树状数组求最长上升子序列长度显然是基操。

$a_i$ 比较大，上树之前先做个离散化。

定义 $d_i$ 为以 $a_i$ 结尾的最长上升子序列的长度。

根据树状数组对最长上升子序列长度的计算方法可以得出一个结论。

> 对于所有满足 $d_x\ge 2$ 的整数 $x$ ，必然存在整数 $y$ 满足 $x>y$ 且 $d_y+1=d_x$ 。

也就是说，我们可以从后往前枚举 $y$，寻找符合条件的 $x$，若 $x$ 存在，这个下标就是答案之一。

## 代码

```c++
#include <iostream>
#include <algorithm>
#include <cstring>
#include <list>
using namespace std;
const int N = 2e5 + 10;
int n, a[N], b[N], m, tr[N], dp[N], req[N], res;
list<int> ret;
inline void update(int x, int v)
{
    for (; x <= m; x += (x & -x))
        tr[x] = max(tr[x], v);
}
inline int query(int x)
{
    int res = 0;
    for (; x; x -= (x & -x))
        res = max(res, tr[x]);
    return res;
}
void run()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", a + i);
        b[i] = a[i];
    }
    sort(b + 1, b + n + 1);
    m = unique(b + 1, b + n + 1) - b - 1;
    memset(tr + 1, 0, m << 2);
    memset(req + 1, 0, m << 2);
    for (int i = 1; i <= n; i++)
    {
        a[i] = lower_bound(b + 1, b + m + 1, a[i]) - b;
        // printf("%d%c", a[i], " \n"[i == n]);
    }
    res = 0;
    for (int i = 1; i <= n; i++)
    {
        dp[i] = query(a[i] - 1) + 1;
        // printf("%d%c", dp[i], " \n"[i == n]);
        res = max(res, dp[i]);
        update(a[i], dp[i]);
    }
    ret.clear();
    req[res] = 0x3f3f3f3f;
    for (int i = n; i; i--)
    {
        if (req[dp[i]] > a[i])
            ret.push_front(i), req[dp[i] - 1] = max(req[dp[i] - 1], a[i]);
    }
    printf("%d\n", ret.size());
    for (auto &i : ret)
        printf("%d ", i);
    putchar('\n');
}
int main()
{
    int T = 1;
    scanf("%d", &T);
    while (T--)
        run();
}
```

---

