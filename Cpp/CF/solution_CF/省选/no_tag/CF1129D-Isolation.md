# Isolation

## 题目描述

给定一个长度为 $n$ 的整数数组 $a$，请你计算有多少种方法可以将数组 $a$ 划分为若干个不相交的非空连续段，使得在每个段中，恰好出现一次的不同整数的个数不超过 $k$。

由于答案可能很大，请输出答案对 $998\,244\,353$ 取模后的结果。

## 说明/提示

在第一个样例中，三种可能的划分方式如下：

- $ [[1], [1], [2]] $
- $ [[1, 1], [2]] $
- $ [[1, 1, 2]] $

划分 $ [[1], [1, 2]] $ 不合法，因为在第二个段 $[1, 2]$ 中，有两个不同的整数恰好出现一次。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 1
1 1 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5 2
1 1 2 1 3
```

### 输出

```
14
```

## 样例 #3

### 输入

```
5 5
1 2 3 4 5
```

### 输出

```
16
```

# 题解

## 作者：Chancylaser (赞：16)

## $\mathcal{Preface}$

* 我这里讲得做法时间复杂度为 $\mathcal{O(n\sqrt n\log n)}$。

* 此做法需要略微卡常，不过都是非常简单的清新卡常，请放心观看。



## $\mathcal{Solution} $

* 做法为数据结构优化 DP，前置知识需要分块和树状数组。

### 暴力 DP

既然为优化，所以我们需要先想出暴力的 DP 转移方程，这道题的转移方程还是非常简单的。

设 $f_i$ 表示对于前 $i$ 个数，第 $i$ 个数为目前划分的最后一段的末尾的方案数，于是转移方程易得：

$$f_i=\sum_{j=0}^{i-1} f_j \times [calc(j+1,i)\le k] $$

其中，$calc(l,r)$ 表示，$l\sim r$ 中出现过恰好一次的元素个数。这里和下文的 $k$ 均为题面所释。

初始 $f_0=1$，答案即为 $f_n$。

由于题目中 $a_i \le n$，所以我们可以开个桶去算出 $calc(l,r)$。

* 时间复杂度 $\mathcal{O(n^2)}$。

### 数据结构优化

我们需要寻找一些性质。

**考虑每加入一个 $i$，对于前面的影响。**

我们设 $lst_i$ 表示，$i$ 前面第一个 $a_j=a_i$ 的 $j$ 的下标，没有相等的则为 $0$。并且设 $sum_i$ 表示位置 $i$ 上的键值。

首先稍微转换一下求出 $calc(l,r)$。加入 $i$ 后，对于 $[lst_i,i-1]$，我们将它们的键值 $+1$，同时将 $[lst_{lst_i},lst_i-1]$ 的键值 $-1$。相信大家多次在其它题解中看到此操作，这样做有什么好处呢？我们发现，这样做下来，如果存在 $j<i$ 且 $sum_j>k$，那么 $f_j$ 是不能加到 $f_i$ 的，即 $calc(j,i)>k$。

如果你还想问为什么，请看这一段，否则跳过即可。对于 $j\in [lst_i,i-1]$，$sum_j+1$ 代表：如果让 $sum_i+=sum_j$，也就是说 $[j+1,i]$ 划分为新的一段，又因为 $j+1\ge lst_i+1$，所以区间 $[j+1,i]$ 中 $a_i$ 只出现了一次。简单来说，如果 $j$ 在这个范围内向 $i$ 贡献，那么新的一段中会多出来一种出现过恰好一次的元素。而 $j\in [lst_{lst_i},lst_i-1]$，$sum_j-1$ 则同理，如果 $j$ 在这个范围内向 $i$ 贡献，那么新的一段中至少出现了两次 $a_i$，就不会对新的一段的单一元素个数产生贡献。看到这里，上一段最后的结论应该懂了吧。

所以

$$f_i=\sum_{j=0}^{i-1} f_j \times [sum_j\le k] $$

这样做下来还是 $\mathcal{O(n^2)}$ 的，考虑**优化**。

---------

我们可以将序列 $sum$ 分块，其中每个块内维护一个树状数组 $c$（用处下文有解释），由上文可知我们有两个操作，一个是区间修改，一个是区间查询。

如何区间修改？对于散块，我们暴力去一个一个加入 $c$，具体地，以 $sum_j$ 为插入的下标，插入的值为 $f_j$。而对于整块，我们需要像正常区间修改一样对于每个块记录一个 $laz_i$，在区间查询中有用。

如何区间查询？（以下 $i$ 为目前块编号，$j$ 为目前数组编号）对于散块，我们暴力判断 $sum_j+laz_i$ 是否小于等于 $k$，如果成立，则可以将 $f_j$ 贡献出去。对于整块，我们对于树状数组进行查询，查询下标 $k-laz_i$ 之前的权值和，此权值和均可以贡献出去。

这部分的操作应该较好理解。

------

时间复杂度 $\mathcal{O(n\sqrt n\log n)}$，空间复杂度 $\mathcal{O(n\sqrt n)}$。

## $\mathcal{Code} $

注意，我的代码在不卡常数的情况下在 Codeforces GNU G++20 11.2.0 (64 bit,winlibs) 语言下可以直接通过，而如果您想在 GNU G++14 6.4.0 语言下通过，需要增加两种简单卡常。此题快读优化不明显，故采用常规输入方式。

* 尽量避免直接取模，而是采用更加快读的减法，详情请见代码。

* 避免使用常数更大的 ```long long ``` 类型。

这样，您就可以通过此题。当然，也许我的思路有更好的实现方式，可以不卡常也能通过，欢迎私信或者讨论区与我讨论！

-----------

有些细节，如果您需要参考我的代码，务必注意一下。

* 因为上文中下标 $0$ 也用到了，所以我将数组整体向右移动一位。

* 因为树状数组的 $add$ 函数中不能从 $0$ 开始，所以一开始要向全部相关数字加个小偏移量，具体详见代码。

----

上面所述内容在代码中均有注释，可结合观看。

```cpp
#include<bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
using namespace std;
typedef long long LL;
const int N=100055,M=332,delta=50 ,MOD=998244353; 
// delta即为偏移量，注意此时N也要随着修改。 

int n,m,a[N];
void add(int *c,int x,LL val){
	if(!val) return;
	for(int i=x;i<N;i+=lowbit(i)){
		c[i]+=val;
		if(c[i]>=MOD) c[i]-=MOD;
		// 这里便是第一个优化常数的方式，下同。 
	}
}
int ask(int *c,int x){
	int ans=0;
	for(int i=x;i>=1;i-=lowbit(i)){
		ans+=c[i];
		if(ans>=MOD) ans-=MOD;
	}
	return ans;
}

int pos[N]; //下标i对应的块的编号为pos_i 
int l[N],r[N],laz[N]; //每块的左端点，右端点，laz值 

int lst[N],nw[N]; //即上文中的lst数组，以及计算lst的辅助数组 
int c[M][N]; //每个块所开的树状数组 

void INit(){
	int t=sqrt(n);
	for(int i=1;i<=t;i++){
		l[i]=(i-1)*t+1;
		r[i]=i*t;
	}
	if(r[t]<n){
		t++;
		l[t]=r[t-1]+1; r[t]=n;
	}
	for(int i=1;i<=t;i++)
		for(int j=l[i];j<=r[i];j++)
			pos[j]=i;
}

int f[N];
void modify(int x,int y,int d){
	if(x>y) return;
	int q=pos[x],w=pos[y];
	if(q==w){
		for(int i=x;i<=y;i++){
			add(c[q],a[i],(-f[i]+MOD)%MOD);
			a[i]+=d;
			add(c[q],a[i],f[i]%MOD);
		}
	}
	else{
		for(int i=q+1;i<w;i++) laz[i]+=d;
		for(int i=x;i<=r[q];i++){
			add(c[q],a[i],(-f[i]+MOD)%MOD);
			a[i]+=d;
			add(c[q],a[i],f[i]%MOD);
		}
		for(int i=l[w];i<=y;i++){
			add(c[w],a[i],(-f[i]+MOD)%MOD);
			a[i]+=d;
			add(c[w],a[i],f[i]%MOD);		
		}
	}
}

int query(int x,int y){
	int q=pos[x],w=pos[y];
	LL ans=0;
	if(q==w){
		for(int i=x;i<=y;i++)
			if(a[i]+laz[q]<=m){
				ans+=f[i];
				if(ans>=MOD) ans-=MOD;
			}
	}
	else{
		for(int i=q+1;i<w;i++){
			ans+=ask(c[i],m-laz[i]);
			if(ans>=MOD) ans-=MOD;
		}
		for(int i=x;i<=r[q];i++)
			if(a[i]+laz[q]<=m){
				ans+=f[i];	
				if(ans>=MOD) ans-=MOD;
			}
				
		for(int i=l[w];i<=y;i++)
			if(a[i]+laz[w]<=m){
				ans+=f[i];
				if(ans>=MOD) ans-=MOD;
			}
	}
	return ans;
}

signed main(){
	scanf("%d%d",&n,&m);
	n++; // 将整个数组往后移动一位，这样就能避免 0 下标 
	for(int i=2;i<=n;i++){
		scanf("%d",&a[i]);
		lst[i]=nw[a[i]];
		nw[a[i]]=i;
	}
	for(int i=1;i<=n;i++) a[i]=delta;
	m+=delta;
	INit();
	
	f[1]=1; 
	add(c[1],a[1],f[1]); // 注意初始也要更新这里（即更新上面solution中的f_0，这里偏移后为f_1） 
	for(int i=2;i<=n;i++){
		modify(max(1,lst[i]),i-1,1);
		if(lst[i]>1) modify(max(1,lst[lst[i]]),lst[i]-1,-1);
		f[i]=query(1,i-1);
		add(c[pos[i]],a[i],f[i]);
	}
	
	printf("%d",f[n]); 
	return 0;
}
```

## $\mathcal{Afterword} $

欢迎在讨论区或者私信提问问题，以及指出题解的错误！


---

## 作者：_sys (赞：13)

设 $f_i$ 表示前 $i$ 个数划分的答案，$p_j$ 表示 $[j+1,i]$ 出现次数为 $1$ 的数的种类。

则有：

$$f_i=\sum_{p_j\leq k} f_j$$

我们考虑 $p_j$ 的变化，设 $\text{pre}_i$ 表示上一个和第 $i$ 个数相等的数的位置，没有则是 $0$。

则 $[\text{pre}_{\text{pre}_i},\text{pre}_i-1]$ 位置上的 $p_i$ 需要减一，$[\text{pre}_i,i-1]$ 位置上的 $p_i$ 需要加一。

现在我们需要维护这样一个序列，支持区间 $\text{key}$ 加减一，求 $\text{key}$ 大于等于 $k$ 的位置的 $\text{value}$ 和。

据 lxl 说这个现在没有 $\mathrm{polylog}$ 做法。

我们将序列分块，考虑对于每个块维护一个数组 $s_i$ 表示块内 $p=i$ 的位置 $f$ 之和，同时维护答案 $\text{tot}$。

修改整块的时候，加一我们可以直接减去 $p=k$ 的贡献，减一就加上 $p=k+1$ 的贡献，以此类推，用 $\text{tag}$ 数组记录一下偏移量。

零散块重建即可，查询把每个块的 $\text{tot}$ 加起来即可。

时间复杂度：$O(n\sqrt n)$。

这个题 $O(n\sqrt n\log n)$ 是不太容易通过的。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int Maxn = 100505, p = 998244353;
int n, k, bloc, per, cnt[Maxn], bel[Maxn], las[Maxn], pre[Maxn];
long long f[Maxn], tot[Maxn], tag[Maxn], sum[305][Maxn];
void clear(int x)
{
	tot[x] = 0;
	for (int i = (x - 1) * per + 1; i <= x * per; i++)
		sum[x][cnt[i]] = 0;
}
void build(int x)
{
	for (int i = (x - 1) * per + 1; i <= x * per; i++)
	{
		cnt[i] += tag[x];
		(sum[x][cnt[i]] += f[i]) %= p;
		if (cnt[i] <= k) (tot[x] += f[i]) %= p;
	}
	tag[x] = 0;
}
void inc(int x)
{
	if (k >= tag[x]) (tot[x] += p - sum[x][k - tag[x]]) %= p;
	tag[x]++;
}
void dec(int x)
{
	tag[x]--;
	if (k >= tag[x]) (tot[x] += sum[x][k - tag[x]]) %= p;
}
void inc(int lt, int rt)
{
	if (lt > rt) return ;
	if (bel[lt] == bel[rt])
	{
		clear(bel[lt]);
		for (int i = lt; i <= rt; i++)
			cnt[i]++;
		build(bel[lt]);
		return ;
	}
	clear(bel[lt]);
	for (int i = lt; i <= bel[lt] * per; i++)
		cnt[i]++;
	build(bel[lt]);
	clear(bel[rt]);
	for (int i = (bel[rt] - 1) * per + 1; i <= rt; i++)
		cnt[i]++;
	build(bel[rt]);
	for (int i = bel[lt] + 1; i <= bel[rt] - 1; i++)
		inc(i);
}
void dec(int lt, int rt)
{
	if (lt > rt) return ;
	if (bel[lt] == bel[rt])
	{
		clear(bel[lt]);
		for (int i = lt; i <= rt; i++)
			cnt[i]--;
		build(bel[lt]);
		return ;
	}
	clear(bel[lt]);
	for (int i = lt; i <= bel[lt] * per; i++)
		cnt[i]--;
	build(bel[lt]);
	clear(bel[rt]);
	for (int i = (bel[rt] - 1) * per + 1; i <= rt; i++)
		cnt[i]--;
	build(bel[rt]);
	for (int i = bel[lt] + 1; i <= bel[rt] - 1; i++)
		dec(i);
}
int main()
{
	scanf("%d%d", &n, &k);
	bloc = min(300, (int)sqrt(n)), per = ceil(n / (double) bloc);
	for (int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		pre[i] = las[x];
		las[x] = i;
		int tmp = pre[pre[i]];
		if (!tmp) tmp++, cnt[0] -= (bool) pre[i];
		dec(tmp, pre[i] - 1);
		tmp = pre[i];
		if (!tmp) tmp++, cnt[0]++;
		inc(tmp, i - 1);
		for (int j = 1; j <= bloc; j++)
			(f[i] += tot[j]) %= p;
		if (cnt[0] <= k) f[i]++;
		bel[i] = (i - 1) / per + 1;
		clear(bel[i]);
		build(bel[i]);
	}
	printf("%lld", f[n]);
	return 0;
}
```

---

## 作者：RenaMoe (赞：7)

按照扫描线的思路，从小到大枚举 $i$，维护一个 $c_j$ 表示区间 $[j,i]$ 出现一次的数的个数。每次给区间 $(\mathrm{last}(\mathrm{last}(i)),\mathrm{last}(i)]$ $-1$，区间 $(\mathrm{last}(i),i]$ $+1$。

转移 $f_{i+1}$ 时就是求 $0\dots i$ 中满足 $c_j\le k$ 的 $f_j$ 之和。

分块，每个块维护一个桶。时间复杂度 $\mathcal O(n\sqrt n)$。

由于每个块内 $c_i$ 之差至多是块长，所以空间是 $\mathcal O(n)$。原因考虑 $c$ 数组的差分中，每个位置只能是 $0$ 或 $1$。

```cpp
#include <bits/stdc++.h>

constexpr int P = 998244353;

void inc(int &x, int y) {
    x += y;
    if (x >= P) x -= P;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        --a[i];
    }

    std::vector<int> f(n + 1);
    f[0] = 1;

    int block = std::sqrt(n);
    int tot = (n - 1) / block + 1;
    std::vector<int> lb(tot), rb(tot);
    for (int i = 0; i < tot; ++i) {
        lb[i] = i * block;
        rb[i] = std::min((i + 1) * block, n);
    }
    std::vector<int> c(n);
    std::vector<std::vector<int>> sum(tot, std::vector<int>(block + 1));
    std::vector<int> off(tot);
    std::vector<int> tag(tot);

    auto rebuild = [&](int x) {
        std::fill(sum[x].begin(), sum[x].end(), 0);
        for (int i = lb[x]; i < rb[x]; ++i) c[i] += tag[x];
        tag[x] = 0;
        off[x] = *std::min_element(c.begin() + lb[x], c.begin() + rb[x]);
        for (int i = lb[x]; i < rb[x]; ++i) {
            inc(sum[x][c[i] - off[x]], f[i]);
        }
        for (int i = 1; i <= block; ++i) inc(sum[x][i], sum[x][i - 1]);
    };

    auto modify = [&](int l, int r, int k) {
        int x = l / block;
        int y = (r - 1) / block;
        if (x == y) {
            for (int i = l; i < r; ++i) c[i] += k;
            rebuild(x);
            return;
        }
        for (int i = l; i < rb[x]; ++i) c[i] += k;
        rebuild(x);
        for (int i = x + 1; i < y; ++i) tag[i] += k;
        for (int i = lb[y]; i < r; ++i) c[i] += k;
        rebuild(y);
    };

    std::vector<int> pos(n, -1);
    std::vector<int> last(n);
    for (int i = 0; i < n; ++i) {
        int x = i / block;
        for (int j = c[i] - off[x]; j <= block; ++j) {
            inc(sum[x][j], f[i]);
        }

        last[i] = pos[a[i]];
        pos[a[i]] = i;
        modify(last[i] + 1, i + 1, 1);
        if (last[i] != -1) {
            modify(last[last[i]] + 1, last[i] + 1, -1);
        }
        
        for (int j = 0; j < x; ++j) {
            int t = m - (off[j] + tag[j]);
            if (t >= 0) {
                inc(f[i + 1], sum[j][std::min(t, block)]);
            }
        }
        for (int j = lb[x]; j <= i; ++j) {
            if (c[j] + tag[x] <= m) {
                inc(f[i + 1], f[j]);
            }
        }
    }
    std::cout << f[n] << '\n';

    return 0;
}
```

---

## 作者：lyt_awa (赞：6)

## 思路
看到题目没思路？直接先上**暴力**。这道题明显是个 **dp**。
### 状态
可以先设计出一个 dp 的状态：  
$f_i$ 表示前 $i$ 个数的答案。
### 转移
对于每一个 $j\left ( j\le i \right )$ 若满足 $\forall k\in \left [ j,i \right ],a_k$ 只出现过一次的 $k$ 的个数 $cnt \le m$ 那么 $f_i$ 就可以从 $f_{j-1}$ 转移过来，那么 $f_i=\sum_jf_{j-1}$ （$j$ 满足上述条件）。这样暴力的时间复杂度是 $O(n^{2})$（代码也贴在 code 里了），明显过不了，于是我们考虑优化。
### 优化
在暴力计算 $cnt$ 时，我们可以发现实际是在**区间 $\left [ last_{last_i},last_i \right ] $ 上的每一个 $cnt$ 减一**，在**区间 $\left ( last_i,i \right ]$ 上的每一个 $cnt$ 加一**（$last_i$ 表示上一个数值等于 $a_i$ 的数的下标）。然后就有 $f_i=\sum_{\forall j \in \left [ 1,i \right ] ,cnt_{j}\le m}f_{j-1}$（$cnt_{j}$ 表示在区间 $\left [ j,i \right ]$ 里只出现一次的数的个数）。

于是就可以想到用**分块**进行优化。**区间修改**和**区间查询 $\sum_{\forall j \in \left [ 1,i \right ] ,cnt_{j}\le m}f_{j-1}$**。区间查询只要**暴力维护**一个 $val_{i,j}$ 表示第 $i$ 块内的 $\sum_{cnt_x=j}f_{x-1}$ （由于 $cnt_x$ 可能小于 $0$ 所以下标右移 $n$）。然后对于每一次区间修改**暴力修改**即可。这样**区间修改**和**区间查询**的时间复杂度都是 $O(\sqrt{n})$。于是总时间复杂度变为了 $O(n\sqrt{n})$（就能过了）。
## $code$
```cpp
//暴力 
/*
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 2e5 + 5;
const ll mod = 998244353;

inline ll read() {
	ll x = 0, f = 1;
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x * f;
}

int n, m, a[N];
ll f[N], zj[N];

int main() {
	n = read();
	m = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	f[0] = 1;
	for (int i = 1; i <= n; ++i) {
		memset(zj, 0, sizeof(zj));
		int cnt = 0;
		for (int j = i; j; --j) {
			++zj[a[j]];
			if (zj[a[j]] == 1) ++cnt;
			if (zj[a[j]] == 2) --cnt;
			if (cnt <= m) f[i] += f[j - 1] %= mod;
		}
	}
	printf("%lld\n", f[n] % mod);
	return 0;
}
*/
//分块优化 
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 2e5 + 5;
const int M = 320;
const int mod = 998244353;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x * f;
}

int pr[N], las[N], val[M][N], cnt[N], f[N], tag[M], T, Ans, n, k;

inline int belong(int x) { return (x - 1) / T + 1; }

inline void dec(int &a, int b) { a -= b; if (a < 0) a += mod; }

inline void inc(int &a, int b) { a += b; if (a >= mod) a -= mod; }

inline void Ins(int u, int v) {
	int bu = belong(u);
	cnt[u] -= tag[bu];
	inc(Ans, v);
	inc(val[bu][cnt[u] + n], v);
}

inline void Mdfs(int u, int v) {
	int bu = belong(u);
	if(cnt[u] + tag[bu] <= k) dec(Ans, f[u - 1]);
	dec(val[bu][cnt[u] + n], f[u - 1]);
	cnt[u] += v;
	if(cnt[u] + tag[bu] <= k) inc(Ans, f[u - 1]);
	inc(val[bu][cnt[u] + n], f[u - 1]);
}

inline void Mdf(int L, int R, int v) {
	if (L > R) return;
	int bl = belong(L), br = belong(R);
	if (bl + 1 >= br) for(int i = L; i <= R; ++i) Mdfs(i, v);
	else {
		for (int i = L; i <= bl * T; ++i) Mdfs(i, v);
		for (int i = (br - 1) * T + 1; i <= R; ++i) Mdfs(i, v);
		for (int i = bl + 1; i < br; ++i) {
			if (~v) dec(Ans, val[i][k - tag[i] + n]);
			else inc(Ans, val[i][k - tag[i] + 1 + n]);
			tag[i] += v;
		}
	}
}

int main() {
	n = read();
	k = read();
	for (int i = 1, a; i <= n; ++i) a = read(), pr[i] = las[a], las[a] = i;
	T = sqrt(n); n = n; f[0] = 1; Ins(1, 1);
	for (int i = 1; i <= n; ++i) {
		Mdf(pr[i] + 1, i, 1);
		Mdf(pr[pr[i]] + 1, pr[i], -1);
		Ins(i + 1, f[i] = Ans);
	}
	printf("%d\n", f[n]);
	return 0;
}
```

---

## 作者：L_zaa_L (赞：4)

我们考虑优化最开始的 $dp_i=\displaystyle\sum_{j=0}^{i-1} f_j\times[calc(j+1,i)\le k]$，我们可以实时维护一个数组 $f_j=calc(j,i)$。

发现新增一个数字 $x$ 只会有两个区间会发生变化：$[lst_x,x-1]$ 会加一，$[lst_{lst_x},lst_x-1]$ 会减一
 ，然后就需要所有 $f_i\le k$ 的地方的 $dp_i$ 之和。
 
考虑使用分块，每次区间加的时候我们可以对于散块暴力加，整块可以记录一个数组 $lazy$ 直接加，然后每次可以用树状数组维护每个区间的 $f_i$ 是否小于等于 $k$，然后这样就能过了，时间复杂度 $O(n\sqrt{n\log n})$。

但是还可以在优化一些，我们可以记录 $gg_{i,j}$ 表示第 $i$ 块中 $f_i\le k$ 的答案之和，每次 $f$ 的只会增加或者减少一，所以只用修改一个 $gg$ 即可，时间复杂度：$O(n\sqrt n)$。

## Code

```cpp
#include<bits/stdc++.h>
//#define int long long
#define ls(x) ((x)*2)
#define rs(x) ((x)*2+1)
#define Debug(...) fprintf(stderr, __VA_ARGS__)
#define For(i,a,b) for(int i=a,i##end=b;i<=i##end;i++)
#define Rof(i,a,b) for(int i=a,i##end=b;i>=i##end;i--)
#define rep(i,  b) for(int i=1,i##end=b;i<=i##end;i++)
using namespace std;
const int N=1e5+5,B=330,Mod=998244353;
//char buf[(1<<21)+5],*p1,*p2;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
void chmx(int &x,int y){(x<y)&&(x=y);}
void chmn(int &x,int y){(x>y)&&(x=y);}
void add(int &x,int y){((x+=y)>=Mod)&&(x-=Mod);}
inline int read(){
	int f=0,x=0;
	char ch=getchar();
	while(!isdigit(ch)){f|=(ch=='-');ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return f?-x:x;
}
int n,k;
int a[N],kuai;
int L[B+5],R[B+5],o[N];
int p[N],last[N],lst[N],lazy[B+5]; 
int cnt[N],gg[B+5][N],all[B+5],dp[N];
inline void san(int l,int r,int p){
	for(int i=l;i<=r;i++){
		if(p==1) add(gg[o[l]][++cnt[i]],dp[i]);
		else add(gg[o[l]][cnt[i]--],(Mod-dp[i]));
	}
}
inline void modify(int l,int r,int p){
	if(l>r) return;
	if(o[l]==o[r]) san(l,r,p);
	else{
		san(l,R[o[l]],p);
		san(L[o[r]],r,p);
		for(int i=o[l]+1;i<o[r];i++) lazy[i]+=p;
	}
}
inline int query(){
	int res=0;
	for(int i=0;i<=kuai;i++){
		add(res,all[i]);
		if(k-lazy[i]+1>=0)add(res,(Mod-gg[i][k-lazy[i]+1]));
		else add(res,(Mod-all[i]));
	}
	return res;
}
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	// ios::sync_with_stdio(false);
	// cin.tie(0); cout.tie(0);
	n=read(),k=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		lst[i]=last[a[i]];
		last[a[i]]=i;
	}
	kuai=n/B+1;
	dp[0]=1;
	for(int i=1;i<=kuai;i++){
		L[i]=(i-1)*B;R[i]=min(i*B-1,n);
		for(int j=L[i];j<=R[i];j++) o[j]=i;
	}
	gg[1][0]=1,all[1]=1;
	for(int i=1;i<=n;i++){
		modify(lst[i],i-1,1);
		if(lst[i]>0)modify(lst[lst[i]],lst[i]-1,-1);
		dp[i]=query();
		add(gg[o[i]][0],dp[i]);
		add(all[o[i]],dp[i]);
	} 
	cout<<dp[n];
#ifdef LOCAL
    Debug("\nMy Time: %.3lfms\n", (double)clock() / CLOCKS_PER_SEC);
#endif
	return 0;
}
```

---

## 作者：Zelotz (赞：3)

定义 $f_i$ 表示前 $i$ 个数，第 $i$ 个数为目前划分的最后一段的末尾的方案数。

$$
f_i = \sum_{i=0}^{i-1} f_j\times [calc(j+1,i)\le k]
$$
其中 $calc(i, j)$ 表示 $i\sim j$ 中只出现过一次的数的个数。

考虑每加入一个 $i$，对于前面的 $j$，$calc(j, i)$ 的变化。

可以发现是 $j\in [lst_{a_i},i)$ 的 $calc(j+1,i)$ 会加一，$j\in [llst_{a_i},lst_{a_i})$  的 $calc(j+1,i)$ 会减一。

于是，需要一个数据结构完成区间加减 $1$，查询键值小于等于某个固定值 $p$ 的 dp 数组总和。

分块，对于整块使用 tag 加减即可。对于散块，维护 $g_{i,j}$ 表示 $i$ 这个块，单独加的次数大于等于 $j$ 的 dp 值的和。在散块的某个点的最后更新的地方更新即可。可以理解为：横轴为每个点，纵轴为每个点被加的次数，在当前块 $id$ 内 $g_{id,y}$ 表示 $y$ 行的 dp 值的和，每个点在开始都向上叠，下面的点 $i$ 行的总 dp 值一定只会在不断把最高点删去直到删到 $i$ 行的时候更新。具体可以查看代码。

查询时，先拿出整个块内的所有 dp 值的和，减去那些加上 tag 过后超过了 $p$ 的 dp 值即可。$g$ 数组的维护在本题非常巧妙。

```
#include <bits/stdc++.h>
using namespace std;
#define il inline
#define ptc putchar
#define reg register
#define pb push_back
#define R(i, l, r) for (int i = l; i <= r; ++i)
#define debug puts("--------------------------------------------")
typedef long long ll;
typedef pair<int, int> PII;
namespace ZeroTwo {
    template <typename T>
    il void read(T &x) { 
        x = 0; T f = 1; char ch;
        while (!isdigit(ch = getchar())) f -= (ch == '-') << 1;
        while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch & 15), ch = getchar();
        x *= f;
    }
    template <typename T, typename ...L>
    il void read(T &x, L &...y) {read(x); read(y...);}
    template <typename T>
    il void write(T x) {
        if (x < 0) ptc('-'), x = -x;
        if (x > 9) write(x / 10);
        ptc(x % 10 + '0');
    }
    template <typename T, typename ...L>
    il void write(T &x, L &...y) {write(x), ptc(' '); write(y...);}
}
using namespace ZeroTwo;
#define int ll
const int N = 1e5 + 5, P = 998244353, B = 400;
int n, p, a[N], lst[N], llst[N], bel[N], dp[N], cnt[N], L[N], R[N];
int f[N], g[255][N], tag[N], tot; // g[i][j] 表示第i个块内单独算的f[i]>=j的dp之和
void solve(int l, int r, int k) {
    R(i, l, r) {
        if (k == 1) (g[bel[i]][++cnt[i]] += dp[i]) %= P;
        else (g[bel[i]][cnt[i]--] -= dp[i]) %= P;
    }
}
void mdf(int l, int r, int k) {
    if (bel[l] == bel[r]) return solve(l, r, k), void();
    solve(l, R[bel[l]], k); solve(L[bel[r]], r, k);
    R(i, bel[l] + 1, bel[r] - 1) tag[i] += k;
}
int qry() {
    int res = 0;
    R(i, 1, tot) {
        (res += g[i][0]) %= P; // x + tag > p -> x >= p - tag + 1
        if (p - tag[i] + 1 > 0) (res -= g[i][p - tag[i] + 1]) %= P;
        else (res -= g[i][0]) %= P;
    }
    return res;
}
signed main() {
    read(n, p);
    bel[0] = 1;
    R(i, 1, n) read(a[i]), bel[i] = i / B + 1;
    tot = ceil((n + 1) * 1.0 / B);
    R(i, 1, tot) L[i] = (i - 1) * B, R[i] = i * B - 1;
    dp[0] = 1; g[1][0] += dp[0]; 
    R(i, 1, n) {
        mdf(lst[a[i]], i - 1, 1);
        if (lst[a[i]]) mdf(llst[a[i]], lst[a[i]] - 1, -1);
        llst[a[i]] = lst[a[i]];
        lst[a[i]] = i;
        dp[i] = qry();
        (g[bel[i]][0] += dp[i]) %= P;
    }
    write(dp[n] < 0 ? dp[n] + P : dp[n]);
    return 0;
}
```

---

## 作者：ywy_c_asm (赞：3)

首先看见这题我们能想到的肯定是一个暴力dp：

$dp[i]=\sum_{j=0}^{i-1}[[j+1,i]\text{有不超过k个只出现1次的}]dp[j]$

然后我们看见出现次数为1就能想到从pre入手，有了！我们往右扫，维护一个$p_j$表示$[j+1,i]$内有多少个只出现1次的数，每扫到一个数就让$[pre_i,i-1]$的$p_j$都+1，再让$[pre_{pre_i},pre_i-1]$的$p_j$都-1，这样就能够动态维护$p[]$了。

哎，那你答案怎么维护？我们不是要通过p找转移吗？

那么也就是说我们要做到强制在线的区间加$p$，查询区间$p$值不超过$k$的$dp$值的和~~所以就强行把这个dp题生硬的搞成了数据结构题~~

如果你经常做ynoi一类的题的话很容易看出来这个可以分块。我开始写了个$O(n\sqrt nlogn)$的T的飞起的做法就是在每块上打加标记，然后每块的块内排序，维护前缀和，查询的时候对每个块二分，修改时暴力重构。其实可以换个思路就是咱们并不用每回都把所有块都查询一遍，直接动态修改所有可行的位置的dp的和就行了，我们维护一个$f[i][j]$表示块i内$j+tag_i=p_k$的所有的k的dp值之和，整块修改的话，因为你是+1或者-1，+1的话就把原来$p_j=k$的dp值减掉就行了，即$f[i][k-tag_i]$，-1的话就把原来$p_j=k+1$的dp值加回来就行了，即$f[i][j-tag_i+1]$，小段暴力的时候直接修改$f$数组，并且如果开始小于等于k或者开始大于k就修改答案即可。于是就$O(n\sqrt n)$了。

哦对了这题的空间需要刻意卡一卡……

上代码~

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define ll long long
#define p 998244353
#define blo 350
using namespace std;
namespace ywy {
	inline int get() {
	    int n = 0;
	    char c;
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            break;
	        if (c == '-')
	            goto s;
	    }
	    n = c - '0';
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 + c - '0';
	        else
	            return (n);
	    }
	s:
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 - c + '0';
	        else
	            return (n);
	    }
	}
	ll dp[100001];
	int val[290][200001], tag[100001], f[100001], pre[100001], ints[100001], ld[100001];
	ll ans = 0;
	int k, n;
	inline void add(int l, int r, int num) {
	    int lbd = l / blo, rbd = r / blo;
	    if (lbd == rbd) {
	        for (register int i = l; i <= r; i++) {
	            if (f[i] + tag[lbd] == k + 1 && num == -1)
	                ans = (ans + dp[i]) % p;
	            if (f[i] + tag[lbd] == k && num == 1)
	                ans = (ans + p - dp[i]) % p;
	            val[lbd][f[i] + 100000] = (val[lbd][f[i] + 100000] + p - dp[i]) % p;
	            f[i] += num;
	            val[lbd][f[i] + 100000] = (val[lbd][f[i] + 100000] + dp[i]) % p;
	        }
	        return;
	    }
	    for (register int i = l; i < (lbd + 1) * blo; i++) {
	        if (f[i] + tag[lbd] == k + 1 && num == -1)
	            ans = (ans + dp[i]) % p;
	        if (f[i] + tag[lbd] == k && num == 1)
	            ans = (ans + p - dp[i]) % p;
	        val[lbd][f[i] + 100000] = (val[lbd][f[i] + 100000] + p - dp[i]) % p;
	        f[i] += num;
	        val[lbd][f[i] + 100000] = (val[lbd][f[i] + 100000] + dp[i]) % p;
	    }
	    for (register int i = rbd * blo; i <= r; i++) {
	        if (f[i] + tag[rbd] == k + 1 && num == -1)
	            ans = (ans + dp[i]) % p;
	        if (f[i] + tag[rbd] == k && num == 1)
	            ans = (ans + p - dp[i]) % p;
	        val[rbd][f[i] + 100000] = (val[rbd][f[i] + 100000] + p - dp[i]) % p;
	        f[i] += num;
	        val[rbd][f[i] + 100000] = (val[rbd][f[i] + 100000] + dp[i]) % p;
	    }
	    for (register int i = lbd + 1; i < rbd; i++) {
	        if (num == 1)
	            ans = (ans + p - val[i][k - tag[i] + 100000]) % p;
	        if (num == -1)
	            ans = (ans + val[i][k - tag[i] + 100001]) % p;
	        tag[i] += num;
	    }
	}
	void ywymain() {
	    n = get();
	    k = get();
	    ans = 1;
	    dp[0] = 1;
	    val[0][100000] = 1;
	    for (register int i = 1; i <= n; i++) {
	        ints[i] = get();
	        pre[i] = ld[ints[i]];
	        ld[ints[i]] = i;
	    }
	    for (register int i = 1; i <= n; i++) {
	        add(pre[i], i - 1, 1);
	        if (pre[i])
	            add(pre[pre[i]], pre[i] - 1, -1);
	        dp[i] = ans;
	        ans = (ans + dp[i]) % p;
	        val[i / blo][100000] = (val[i / blo][100000] + dp[i]) % p;
	    }
	    cout << dp[n] << endl;
	}
}
int main() {
    ywy::ywymain();
    return (0);
}
```

---

## 作者：hnczy (赞：2)

~~一眼区间dp——pts60~~

等等，那你怎么拿 100pts,你连 dp 数组都开不下，不可能。

那我们先写成一维的状态，即 $dp_i$ 表示前 $i$ 个数符合条件的方案总数。

诶，这样的话我们就可以用 $O(n^2)$ 的时间复杂度解决了，~~那不是还是没优化吗~~。

具体的转移方程如下：

$ dp_{i}=\sum_{j=1}^{i} dp_{j-1}|(cnt_{j,i})\le m)$，$cnt$ 表示 $l-r$ 范围内只数字出现一次的数量

这一需要从右往左枚举。

```c++
for(int i=1;i<=n;i++){
		memset(dig,0,sizeof dig);
		int cnt=0;
		for(int j=i;j>=1;j--){
			dig[a[j]]++;
			if(dig[a[j]]==1)cnt++;
			if(dig[a[j]]==2)cnt--;
			if(cnt<=m)dp[i]+=dp[j-1],dp[i]%=mod;
		}
		//cout<<dp[i]<<endl;
	}
```
那我们很容易想到——我们好像很多的操作都是重复的（因为是从右往左），那我们能不能每一次枚举右端点的时候只处理一下这个端点，而不处理前面的端点呢？

也许可以，试想一下，你每一次在加上 $a[i]$ 时，对于 整一个 $cnt$ 有什么改变？

因为 $a[i]$ 是不知道是第几个放进来的，那我们可以记一个 $pre$ 数组来记一下与 a[i] 最近的与它相等的下标，即 $pre[i]=j$ ，当且仅当 $a[j]=a[i],j<i$  。

那我们不就知道了 $a[i]$ 对整一个 $cnt$ 影响了吗，就是在 $pre[i]+1-i$  加一，在$pre[pre[i]]+1-pre[i]$ 减一。

这里有加操作，有区间查询操作，这不是可以用分块来解决吗？ 

代码也不难：
```c++

#include<bits/stdc++.h>
#define pii pair<int ,int>
using namespace std;
const int mod =998244353;
int n,m;
int a[100005],dp[100005],wh[100005],pre[100005];
int id[100005],L[400],R[400],add[400],sq,sums[400][400];
int b[100005],flag[400];
pii k[100005];
void jia(int &x,int y){
	x+=y;
	if(x>mod)x-=mod; 
}
void init() {
	sq=sqrt(n);
	for(int i=1; i<=n; i++) {
		int p=(i-1)/sq+1;
		id[i]=p;
		if(!L[p])L[p]=i;
		R[p]=i;
	}
	for(int i=1; i<=n; i++) {
		if(wh[a[i]])pre[i]=wh[a[i]];
		wh[a[i]]=i;
	}
}
void reinit(int x) {
	for(int i=L[x]; i<=R[x]; i++)
		k[i]= {b[i],dp[i-1]};
	sort(k+L[x],k+R[x]+1);
	for(int i=L[x]; i<=R[x]; i++)
		sums[x][i-L[x]+1]=(sums[x][i-L[x]]+k[i].second)%mod;
	flag[x]=1;
}
void Add(int l,int r,int x) {
	if(l>r||l<1)return;
	if(id[l]==id[r]) {
		for(int i=l; i<=r; i++)
			jia(b[i],x);
		reinit(id[l]);
		return;
	}
	for(int i=l; i<=R[id[l]]; i++)
		jia(b[i],x);
	reinit(id[l]);
	for(int i=r; i>=L[id[r]]; i--)
		jia(b[i],x);
	reinit(id[r]);
	for(int i=id[l]+1; i<id[r]; i++)
		jia(add[i],x);
}
void solve(int x) {
	Add(pre[pre[x]]+1,pre[x],-1);
	Add(pre[x]+1,x,1);
}
int sum(int x) {
	int res=0;
	for(int i=1; i<id[x]; i++) {
		if(!flag[i])reinit(i);
		int p=upper_bound(k+L[i],k+R[i]+1,make_pair(m+1-add[i],0))-k-L[i];
		jia(res,sums[i][p]);
	}
	for(int i=L[id[x]]; i<=x; i++)
		if(b[i]+add[id[x]]<=m)jia(res,dp[i-1]);
	return res;
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; i++)
		scanf("%d",a+i);
	init();
	dp[0]=1;
	for(int i=1; i<=n; i++) {
		solve(i);
		//在pre[pre[i]]+1~pre[i] 的位置上-1 在pre[i]+1~ i 位置上+1 O(sqrt(n))
		dp[i]=sum(i);
		//在每一个位置上的dp 值 但凡cnt <=m 的都求和,O(sqrt(n)log(n))
		//cout<<dp[i]<<endl;
	}
	printf("%d",dp[n]);
	return 0;

}
//总时间复杂度O(n*sqrt(n)*log(n)) 理论能过
//

---

## 作者：Arghariza (赞：2)

考虑 dp，令 $f_i$ 为 $[1,i]$ 这个前缀的分段方案数。$i$ 从小到大扫描线，动态维护 $c_j$ 表示 $[j+1,i]$ 中只出现恰好一次的数的个数：

$$f_i=\sum\limits_{c_j\le k}f_j$$

考虑如何维护 $c_j$，扫描线过程中维护 $l_i$ 表示 $a_i$ 上次出现的位置。那么 $i-1\to i$ 相当于给 $[l_{l_i},l_i)$ 区间 $-1$，$[l_i,i)$ 区间 $+1$。

所以问题转化为：

- 单点修改 $f_i$。
- 区间修改 $c_i$。
- 区间（前缀）查询 $c_i\le k$ 的 $f_i$ 总和。

分块即可。复杂度 $O(n\sqrt n)$，可以做到线性空间但没必要。

不知道有没有 $O(n\ \text{poly}(\log n))$ 做法。

```cpp
// Problem: Isolation
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1129D
// Memory Limit: 250 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;

namespace vbzIO {
    char ibuf[(1 << 20) + 1], *iS, *iT;
    #if ONLINE_JUDGE
    #define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
    #else
    #define gh() getchar()
    #endif
    #define mt make_tuple
    #define mp make_pair
    #define fi first
    #define se second
    #define pc putchar
    #define pb emplace_back
    #define ins insert
    #define era erase
    typedef tuple<int, int, int> tu3;
    typedef pair<int, int> pi;
    inline int rd() {
        char ch = gh();
        int x = 0;
        bool t = 0;
        while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
        while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
        return t ? ~(x - 1) : x;
    }
    inline void wr(int x) {
        if (x < 0) x = ~(x - 1), putchar('-');
        if (x > 9) wr(x / 10);
        putchar(x % 10 + '0');
    }
}
using namespace vbzIO;

const int P = 998244353;
const int N = 1e5 + 100;
const int B = 330;

int n, k, a[N], f[N], lst[N], pre[N];
int b, lp[B], rp[B], pos[N], s[B], c[B][N], vl[N], t[B];

void clr(int id) {
	s[id] = 0;
	for (int i = lp[id]; i <= rp[id]; i++) c[id][vl[i]] = 0;
}

void reb(int id) {
	for (int i = lp[id]; i <= rp[id]; i++) 
		vl[i] += t[id], (c[id][vl[i]] += f[i]) %= P, (s[id] += (vl[i] <= k) ? f[i] : 0) %= P;
	t[id] = 0;
}

void add(int id) {
	if (k >= t[id]) (s[id] += P - c[id][k - t[id]]) %= P;
	t[id]++;
}

void del(int id) {
	t[id]--;
	if (k >= t[id]) (s[id] += c[id][k - t[id]]) %= P;
}

void upd(int l, int r, int op) {
	if (l > r) return;
	if (pos[l] == pos[r]) {
		clr(pos[l]); for (int i = l; i <= r; i++) vl[i] += op;
		return reb(pos[l]);
	}
	clr(pos[l]); for (int i = l; i <= rp[pos[l]]; i++) vl[i] += op; reb(pos[l]);
	clr(pos[r]); for (int i = lp[pos[r]]; i <= r; i++) vl[i] += op; reb(pos[r]);
	for (int i = pos[l] + 1; i <= pos[r] - 1; i++) 
		if (~op) add(i); else del(i);
}

int main() {
	n = rd(), k = rd(), b = sqrt(n);
    for (int i = 1; i <= n; i++) a[i] = rd();
    for (int i = 1; i <= b; i++)
    	lp[i] = (i - 1) * b + 1, rp[i] = i * b;
    if (rp[b] < n) b++, lp[b] = rp[b - 1] + 1, rp[b] = n;
    for (int i = 1; i <= b; i++)
    	for (int j = lp[i]; j <= rp[i]; j++)
    		pos[j] = i;
	for (int i = 1, ct = 0; i <= n; i++) {
		lst[i] = pre[a[i]], pre[a[i]] = i;
		if (!lst[lst[i]]) ct -= (lst[i] != 0); upd(max(1, lst[lst[i]]), lst[i] - 1, -1);
		if (!lst[i]) ct++; upd(max(1, lst[i]), i - 1, 1);
		for (int j = 1; j <= b; j++) (f[i] += s[j]) %= P;
		if (ct <= k) f[i] = (f[i] + 1) % P;
		// wr(i), pc(' '), wr(ct), pc('\n');
		clr(pos[i]), reb(pos[i]);
	}
	// for (int i = 1; i <= n; i++)
		// wr(f[i]), pc(' ');
	wr(f[n]);
    return 0;
}
```

---

## 作者：tzc_wk (赞：2)

[Codeforces 题目传送门](https://codeforces.com/contest/1129/problem/D) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF1129D)

又独立切了道 *2900（

首先考虑 $dp$，$dp_i$ 表示以 $i$ 为结尾的划分的方式，那么显然有转移 $dp_i=\sum\limits_{j=0}^{i-1}dp_j[uni(j+1,i)\le k]$，其中 $uni(l,r)$ 表示 $[l,r]$ 中出现恰好一次的数的个数。

暴力一脸过不去，考虑优化。我们实时维护一个数组 $f_j=uni(j+1,i)$，那么上式可写作 $dp_i=\sum\limits_{j=0}^{i-1}dp_j[f_j\le k]$，而注意到每次 $i$ 指针的右移引起 $f$ 数组的变化应为两个区间的 $+1/-1$，具体来说，我们记 $pre_v$ 表示 $v$ 上一次出现的位置，$pre\_pre_v$ 为 $v$ 上上次出现的位置，那么指针移到 $i$ 时 $f$ 的变化应为 $[pre\_pre_{a_i},pre_{a_i})$ 内的 $f_j$ 减 $1$，$[pre_{a_i},i)$ 内的 $f_j$ 加 $1$，这个很容易想通。

于是现在问题就转化为，有一个序列，每个元素都有一个权值 $\text{value}$ 和键值 $\text{key}$，每次我们可以将一个区间的键值 $+1/-1$ 或者询问序列中键值 $\le k$ 的元素的权值之和，注意到这东西既涉及下标又涉及值，是不太好用常规的数据结构，如线段树/平衡树之类维护的，因此考虑硬核数据结构——分块。我们设一个阈值 $B$ 并将原序列分成 $B$ 块，并对每一块建一个 BIT，每次我们执行区间 $+v$ 时，边角块就暴力修改 $f_i$ 并修改 BIT 里的值，中间块就维护一个标记数组 $tag_i$ 并令 $tag_i$ 加上 $v$，查询时就枚举每一块，并在 BIT 中查询 $\le k-tag_i$ 所有数的和即可。时间复杂度 $n\sqrt{n\log n}$，不知道能不能过？

考虑优化，注意到上面的解法并没有用到每次加的值为 $\pm 1$ 这一性质，所以使用了 BIT 也就多了一个 $\sqrt{\log n}$ 的复杂度。我们考虑直接对于每一块维护一个前缀和数组 $sum_{i,j}$ 表示第 $i$ 块中 $f_k\le j$ 的 $dp_k$ 之和，那么由于加的值为 $\pm 1$，故每次对区间中一个元素暴力加值的时候，最多会引起一个 $sum_{i,j}$ 的变化，具体来说，如果我们令 $f_j$ 加上 $1$，那么对应的 $sum_{i,f_j}$ 会减去 $dp_j$；如果我们令 $f_j$ 减去 $1$，那么对应的 $sum_{i,f_j-1}$ 会加上 $dp_j$；因此修改单个元素的复杂度就变成了 $\mathcal O(1)$，总复杂度也就变成了 $n\sqrt{n}$

还有一个小小的问题，就是当我们计算出 $dp_i$ 之后，对应的 $f_i$ 显然是 $0$，而此时该位置的权值也发生了改变，即由 $0$ 变为了 $dp_i$，此时我们就要遍历 $j\in[0,n]$ 并令 $sum_{b,j}$ 加上 $dp_i$，其中 $b$ 为 $i$ 所在的块，这样复杂度又会退化到 $n^2$，这显然是我们所不愿意看到的。不过解决方法非常 simple，我们只需将 $sum_{i,j}$ 的定义改为第 $i$ 块中 $f_k\ge j$ 的 $dp_k$ 之和，查询时维护一个 $tot_i$ 表示这块中所有的 $dp_j$ 之和，拿这块中所有的 $dp_j$ 之和减去不合法的情况即可，这样修改还是 $\mathcal O(1)$ 的，不过最后求完 $dp_i$ 之后的遍历过程就没了，取而代之的是我们只用令 $sum_{b,0}$ 加上 $dp_i$，这样复杂度就是货真价实的 $n\sqrt{n}$ 辣（

代码非常好写，不过似乎有些卡空间（？），而且我的似乎跑得挺快？最慢的一个点才跑了 249ms，目前洛谷 rk3

```cpp
const int MAXN=1e5;
const int SQRT=316;
const int MOD=998244353;
void add(int &x,int y){((x+=y)>=MOD)&&(x-=MOD);}
int n,k,a[MAXN+5],blk_sz,blk_cnt,bel[MAXN+5];
int L[SQRT+5],R[SQRT+5],sum[SQRT+5][MAXN+5];
int cnt[MAXN+5],tag[SQRT+5],dp[MAXN+5],tot[SQRT+5];
int pre[MAXN+5],pre_pre[MAXN+5];
void add(int x,int y,int z){
	if(x>y) return;
	if(bel[x]==bel[y]){
		for(int i=x;i<=y;i++){
			if(z==1) add(sum[bel[x]][++cnt[i]],dp[i]);
			else add(sum[bel[x]][cnt[i]--],MOD-dp[i]);
		}
	} else {
		for(int i=x;i<=R[bel[x]];i++){
			if(z==1) add(sum[bel[x]][++cnt[i]],dp[i]);
			else add(sum[bel[x]][cnt[i]--],MOD-dp[i]);
		}
		for(int i=L[bel[y]];i<=y;i++){
			if(z==1) add(sum[bel[y]][++cnt[i]],dp[i]);
			else add(sum[bel[y]][cnt[i]--],MOD-dp[i]);
		}
		for(int i=bel[x]+1;i<bel[y];i++) tag[i]+=z;
	}
}
int calc(){
	int ret=0;
	for(int i=0;i<=blk_cnt;i++){
		add(ret,tot[i]);
		if(k-tag[i]+1>=0) add(ret,MOD-sum[i][k-tag[i]+1]);
		else add(ret,MOD-tot[i]);
	} return ret;
}
int main(){
	scanf("%d%d",&n,&k);dp[0]=1;
	blk_sz=(int)pow(n,0.5);blk_cnt=n/blk_sz+1;
	for(int i=1;i<=blk_cnt;i++){
		L[i]=(i-1)*blk_sz;R[i]=min(i*blk_sz-1,n);
		for(int j=L[i];j<=R[i];j++) bel[j]=i;
	} sum[1][0]=1;tot[1]=1;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		add(pre_pre[a[i]],pre[a[i]]-1,-1);add(pre[a[i]],i-1,1);
		pre_pre[a[i]]=pre[a[i]];pre[a[i]]=i;dp[i]=calc();
		add(sum[bel[i]][0],dp[i]);add(tot[bel[i]],dp[i]);
//		printf("%d\n",dp[i]);
	} printf("%d\n",dp[n]);
	return 0;
}
```



---

## 作者：封禁用户 (赞：2)

一道裸的 DP 题。

状态转移方程 $f_i= \sum f_j$，其中 $i$ 到 $j$ 出现过 $1$ 次的数小于等于 $ k$。

看 $n \le 10^5$ 容易想到分块。

可以从左到右进行 DP，动态维护每个左端点到 $i$ 仅出现过 $1$ 次的数的个数。

只要给区间 $[last_{last_i}+1,last_i]$ 减 $1$，$[last_i+1,i-1]$ 加 $1$ 即可。

通过树状数组维护每个块的答案。

时间复杂度：$O(n\sqrt{n}\log{n})$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename T>inline void read(register T &x)
{
	register T p = 1,num = 0;
	char c = getchar();
	while(c < '0'||c > '9')
	{
		if(c == '-') p = -1;
		c = getchar();
	}
	while('0' <= c&&c <= '9')
	{
		num = (num<<3)+(num<<1)+(c^48);
		c = getchar();
	}
	x = p * num;
}
template<typename T>inline void write(register T x)
{
	if(x < 0) putchar('-'),x = -x;
	if(x > 9) write(x/10);
	putchar(x%10^48);
}
#define F(i,a,b) for(register int i=a;i<=b;++i)
#define D(i,a,b) for(register int i=b;i>=a;--i)
#define mod 998244353
#define ll long long
#define N 100010
#define K 320
int f[N],c[N],id[N],lst[N],a[N],n,k,s;
int b[K],add[K];
inline void ADD(int &x,int y) 
{
	x += y;
	if(x >= mod) x -= mod;
}
struct Seg
{
	int sum[N];
	inline void update(int x,int y)	 
	{
		if(!y) return;
		if(y < 0) y += mod;
		++x;
		while(x <= n+1)
		{
			ADD(sum[x],y);
			x += x & -x;
		}
	}
	inline int query(int x)
	{
		++x;
		int ret = sum[0];
		while(x)
		{
			ADD(ret,sum[x]);
			x -= x & -x;
		}
		return ret;
	}
}tree[K];
inline void update(int l,int r,int p)
{
	--l,--r;
	if(l > r) return;
	if(l/s == r/s)
	{
		F(i,l,r) 
		{
			tree[i/s].update(c[i],-f[i]);
			c[i] += p;
			tree[i/s].update(c[i],f[i]);
		}
		return;
	}
	F(i,l,b[l/s+1]-1) 
	{
		tree[i/s].update(c[i],-f[i]);
		c[i] += p;	
		tree[i/s].update(c[i],f[i]);
	}
	F(i,l/s+1,r/s-1) add[i] += p;
	F(i,b[r/s],r) 
	{
		tree[i/s].update(c[i],-f[i]);
		c[i] += p;	
		tree[i/s].update(c[i],f[i]);	
	}
}
int main() 
{
	read(n),read(k);
	F(i,1,n) read(a[i]);
	s = (int)sqrt(n);
	F(i,0,n) 
	{
		lst[i] = id[a[i]];
		id[a[i]] = i;		
		if(!b[i/s])	b[i/s] = i;		
	}
	b[0] = 0;
	b[n/s+1] = n+1;
	f[0] = 1;
	tree[0].update(0,1);
	F(i,1,n)
	{
		if(!lst[i]) update(1,i,1);
		else if(!lst[lst[i]]) update(1,lst[i],-1),update(lst[i]+1,i,1);
		else update(lst[lst[i]]+1,lst[i],-1),update(lst[i]+1,i,1);
		F(j,0,i/s- 1)
		{
			if(k - add[j] < 0) continue;
			ADD(f[i],tree[j].query(k-add[j]));	
		} 
		F(j,b[i/s],i-1)
		{  
			if(c[j]+add[i/s] <= k) 
				ADD(f[i],f[j]);	
		}	
		tree[i/s].update(c[i],f[i]);
	}
	write(f[n]);
    return 0;
}
```


---

## 作者：__Aaaaaaaa (赞：1)

设 $dp_i$ 表示前 $i$ 个数分成若干段的方案数。

那么 $dp_i=\sum\ [\ F(j+1,i)\leq k\ \ ]\times dp_j$

其中 $F(j+1,i)$ 表示 $[j+1,i]$ 中出现次数为 $1$ 的数字数量。

如果现在设一个 $c_j$ 表示 $[j+1,i]$ 中出现次数为 $1$ 的数字数量。


假如已经求出前 $i$ 的 $dp$ 值和 $c$ 值，考虑现在增加一个 $a_{i+1}$ 会发生什么。

设 $pre_i$ 表示上一个与 $a_i$ 的值相同的位置。

那么当增加一个 $a_{i+1}$ 后,针对 $[pre_{i+1}+1,i+1]$ 这个区间出现了恰好一个 $a_{i+1}$，$[pre_{i+1}-1,i]$ 的 $c$ 值会 $+1$。

而针对 $[pre_{pre_{i+1}}+1,i+1]$ 这个区间，则出现了恰好两个 $a_{i+1}$，$[pre_{pre_{i+1}},i]$ 的 $c$ 值 $-1$。

那么考虑用一个桶来维护和 $c$ 相关的 $dp$ 值，设 $s_i$ 表示 $\sum_{c_j=i} dp_j $，那么针对某一个时刻的 $dp_i$，答案就应该是当时的 $\sum_{i=0}^k s_i$，而时间复杂度显然是 $O(k)$ 查询 $O(n)$ 修改。

然后可以在修改的时候不那么暴力，直接在修改 $c_i$ 时统计答案 ~~（貌似也不用桶了）~~ ，查询降至 $O(1)$。

想到这个地方，我们就能够自然而然想出算法——分块！

设 $s_{i,j}$ 表示在第 $i$ 个块中 $c_l=j$ 的 $dp_l$ 的和，还需要统计一个 lazytag 表示整个区间 $c$ 值增减的变化量，只有处理散块时才下放 lazytag。

当整个块 $c$ 值 $+1$ 时，$ans\gets \ \ ans+(-s_{i,k-lazy})$

当整个块 $c$ 值 $-1$ 时，$ans\gets\ \  ans+(s_{i,k-lazy+1})$

Code:
```
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
const int N=1e5+10,M=350,P=998244353;
inline void add(int &x,int y){
	(x=x+y)>=P&&(x-=P);
}
int ans=1,n,k,s[M][N],dp[N];
int st[M],ed[M],pos[N],c[N],lazy[M];
void pushdown(int id){
	if(!lazy[id])return;
	for(int i=st[id];i<=ed[id];++i){
		add(s[id][c[i]],P-dp[i]);
		c[i]+=lazy[id];
		add(s[id][c[i]],dp[i]);
	}
	lazy[id]=0;
} 
void add_(int l,int r){
	if(l>r)return;
	if(pos[l]==pos[r]){
		pushdown(pos[l]);
		for(int i=l,id=pos[l];i<=r;++i){
			add(s[id][c[i]],P-dp[i]);
			if(c[i]==k)add(ans,P-dp[i]);
			++c[i];
			add(s[id][c[i]],dp[i]);
		}
		return;
	}
	pushdown(pos[l]);
	for(int i=l,id=pos[l];pos[i]==pos[l];++i){
		add(s[id][c[i]],P-dp[i]);
		if(c[i]==k)add(ans,P-dp[i]);
		++c[i];
		add(s[id][c[i]],dp[i]);
	}
	pushdown(pos[r]);
	for(int i=r,id=pos[r];pos[i]==pos[r];--i){
		add(s[id][c[i]],P-dp[i]);
		if(c[i]==k)add(ans,P-dp[i]);
		++c[i];
		add(s[id][c[i]],dp[i]);
	}
	for(int i=pos[l]+1;i<pos[r];++i){
		if(lazy[i]<=k&&k-lazy[i]<N)add(ans,P-s[i][k-lazy[i]]);
		++lazy[i];
	}
}
void del_(int l,int r){
	l=max(l,0);
	if(l>r)return;
	if(pos[l]==pos[r]){
		pushdown(pos[l]);
		for(int i=l,id=pos[l];i<=r;++i){
			add(s[id][c[i]],P-dp[i]);
			--c[i];
			if(c[i]==k)add(ans,dp[i]);
			add(s[id][c[i]],dp[i]);
		}
		return;
	}
	pushdown(pos[l]);
	for(int i=l,id=pos[l];pos[i]==pos[l];++i){
		add(s[id][c[i]],P-dp[i]);
		--c[i];
		if(c[i]==k)add(ans,dp[i]);
		add(s[id][c[i]],dp[i]);
	}
	pushdown(pos[r]);
	for(int i=r,id=pos[r];pos[i]==pos[r];--i){
		add(s[id][c[i]],P-dp[i]);
		--c[i];
		if(c[i]==k)add(ans,dp[i]);
		add(s[id][c[i]],dp[i]);
	}
	for(int i=pos[l]+1;i<pos[r];++i){
		--lazy[i];
		if(lazy[i]<=k&&k-lazy[i]<N)add(ans,s[i][k-lazy[i]]);
	}
}
int las[N],pre[N],a[N];
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i)scanf("%d",a+i);
	for(int i=1;i<=n;++i){
		pre[i]=las[a[i]];
		las[a[i]]=i;
	}
	int block=ceil(sqrt(n+1)+1),t=(n+1)/block+((n+1)%block!=0);
	ed[0]=-1;
	for(int i=1;i<=t;++i)
		st[i]=ed[i-1]+1,ed[i]=i*block;
	ed[t]=n;
	for(int i=1;i<=t;++i)
		for(int j=st[i];j<=ed[i];++j)
			pos[j]=i;
	add(s[pos[0]][c[0]=0],dp[0]=1);
	for(int i=1;i<=n;++i){
		add_(pre[i],i-1);
		if(pre[i])del_(pre[pre[i]],pre[i]-1);
		add(s[pos[i]][c[i]=0],dp[i]=ans);
		add(ans,dp[i]);
	}
	printf("%d\n",dp[n]);
	return 0;
}
```

---

## 作者：神之右大臣 (赞：1)

这篇题解时间复杂度并不是最优，而且思路有部分与另一篇题解重复。但是看了此篇题解后或许可以提高卡常能力，在考场上获得更多的意想不到的分数。~~使得暴力碾标算~~。

注：此篇题解在$n\leq1e5$得情况下无法被hack成TLE。（欢迎来hack）
 
dp方程比较显然：其中后面得部分是布尔表达式

![](https://cdn.luogu.com.cn/upload/image_hosting/5wm4zpqs.png)


我们考虑维护$p[i][j]$表示$[j+1,i]$内出现次数为1的数的个数。

对于这个$p$我们会发现一些性质：$p[i]$和$p[i-1]$在一部分上是相同的。

然后我们再维护一个类似序列自动机的东西，$pre[i]$表示第i个位置之前第一个出现$a[i]$这个元素的位置。这个可以$O(n)$求出。

那么$p[i]$和$p[i-1]$的区别在何处呢？我们发现，$p[i]$仅仅是通过把$p[i-1]$的$[pre_i,i-1]$这个区间内所有数$+1$，把$p[i-1]$的$[pre_{pre_i},pre_i-1]$这个区间内所有数$-1$变成的。所以$p$可以滚掉一维

然后整体考虑，发现我们需要一个数据结构，使得可以维护区间权值小于等于k的价值之和，并能做到区间加、区间减。

参考[P2801 教主的魔法](https://www.luogu.com.cn/problem/P2801)我们知道分块可以在$O(n\sqrt n log_2n)$的时间复杂度下完成这个事情。

虽然另一篇题解说过：

![](https://cdn.luogu.com.cn/upload/image_hosting/uqtorbsj.png)

但是这个做法真的可以过的，考场上我们如果想不到正解难道不是先在有可能通过的程序上卡常卡到极致吗？

先附上AC代码
```cpp
#include <bits/stdc++.h> 
#define inc(i,a,b) for(register int i=a;i<=b;i++)
using namespace std;
int n,k,a[100010],pre[100010],nxt[100010];
const int p=998244353;
class node{
	public:
	int p;
	long long f,sum;
	bool operator <(const node& x){
		return p<x.p;
	}
}c[100010],d[100010];
int block,tot,belong[100010],l[100010],r[100010],lazy[100010];
void build(){
	block=sqrt(n);
	tot=n/block;
	if(n%block) ++tot;
	inc(i,1,tot){
		l[i]=(i-1)*block+1;
		r[i]=i*block;
	}
	l[1]=0;
	r[tot]=n; belong[0]=1;
	inc(i,1,n) belong[i]=(i-1)/block+1;
}
void add(int x,int y,int goal){
	if(y<x) return;
	if(belong[x]==belong[y]){
		inc(i,x,y) c[i].p+=goal;
		inc(i,l[belong[x]],r[belong[x]]) d[i]=c[i];
		sort(d+l[belong[x]],d+r[belong[x]]+1);
		d[l[belong[x]]].sum=d[l[belong[x]]].f;
		inc(i,l[belong[x]]+1,r[belong[x]]) d[i].sum=(d[i-1].sum+d[i].f)%p;
		return;
	}
	inc(i,x,r[belong[x]]) c[i].p+=goal;
	inc(i,l[belong[x]],r[belong[x]]) d[i]=c[i];
	sort(d+l[belong[x]],d+r[belong[x]]+1);
	d[l[belong[x]]].sum=d[l[belong[x]]].f;
	inc(i,l[belong[x]]+1,r[belong[x]]) d[i].sum=(d[i-1].sum+d[i].f)%p;
	inc(i,l[belong[y]],y) c[i].p+=goal;
	inc(i,l[belong[y]],r[belong[y]]) d[i]=c[i];
	sort(d+l[belong[y]],d+r[belong[y]]+1);
	d[l[belong[y]]].sum=d[l[belong[y]]].f;
	inc(i,l[belong[y]]+1,r[belong[y]]) d[i].sum=(d[i-1].sum+d[i].f)%p;
	inc(i,belong[x]+1,belong[y]-1) lazy[i]+=goal;
}
long long query(int x,int y){
	if(y<x) return 0;
	long long ans=0;
	if(belong[x]==belong[y]){
		inc(i,x,y) if(lazy[belong[x]]+c[i].p<=k) ans=(ans+c[i].f)%p;
		return ans;
	}
	inc(i,x,r[belong[x]]) if(lazy[belong[x]]+c[i].p<=k) ans=(ans+c[i].f)%p;
	inc(i,l[belong[y]],y) if(lazy[belong[y]]+c[i].p<=k) ans=(ans+c[i].f)%p;
	inc(i,belong[x]+1,belong[y]-1){
		int L=l[i],R=r[i],anss=n+1;
		while(L<=R){
			int mid=(L+R)/2;
			if(lazy[i]+d[mid].p<=k){
				anss=mid;
				L=mid+1;
			}
			else{
				R=mid-1;
			}
		}
		ans=(ans+d[anss].sum)%p;
	}
	return ans;
}
int main(){
	scanf("%d%d",&n,&k);
	build();
	inc(i,1,n){
		scanf("%d",&a[i]);
	}
	c[0].f=1;
	inc(i,1,n){
		int now=pre[a[i]];
		add(now,i-1,1); 
		int nnow=nxt[now];
		add(nnow,now-1,-1);
		c[i].f=query(0,i-1);
		inc(j,l[belong[i]],r[belong[i]]) d[j]=c[j];
		sort(d+l[belong[i]],d+r[belong[i]]+1);
		d[l[belong[i]]].sum=d[l[belong[i]]].f;
		inc(j,l[belong[i]]+1,r[belong[i]]) d[j].sum=(d[j-1].sum+d[j].f)%p;
		nxt[i]=pre[a[i]];
		pre[a[i]]=i;		
	}
	cout<<c[n].f;
}
```
然后我们简单说说上面的代码有哪些卡常技巧：

1.在缓存和寄存器允许的情况下一条语句内大量的展开运算会刺激 CPU 并发

2.前置++/--运算符

3.使用局部变量的效率比使用静态变量要高（因为局部变量是存在于堆栈中的，对其空间的分配仅仅是修改一次\(esp\)寄存器的内容即可.而局部变量存在于堆栈中最大的好处是，函数能重复使用内存，当一个函数调用完毕时，退出程序堆栈，内存空间被回收，当新的函数被调用时，局部变量又可以重新使用相同的地址。当一块数据被反复读写，其数据会留在\(CPU\)的一级缓存（\(Cache\)）中，访问速度非常快。而静态变量却不存在于堆栈中。）

4.register

最后附上CF上交题记录 [传送门](https://codeforces.com/contest/1129/submission/86823093)

和洛谷交题记录  [传送门](https://www.luogu.com.cn/record/35150217)

---

## 作者：FutaRimeWoawaSete (赞：1)

分块优化 dp。               

~~刚刚翻了下题解区貌似不是最正解，怪不得我被卡常了。~~

我们考虑这个东西，长得很 dp，所以我们直接做它！              

定义 $dp_i$ 表示以序列中第 $i$ 个位置为结尾时的方案数，定义 $c_{l,r}$ 表示区间 $[l,r]$ 出现恰好一次的元素个数。          

则我们就可以随便做一个 $O(n ^ 2)$ 的 dp 了，即：            

$dp_i = \sum_{j = 1} ^ i dp_{j - 1} \times [c(j , i) \leq k]$

考虑这个式子长得极其简单，如果我们能维护所有的 $c(l,r)$ 就可以快速转移了。             

根据 dp 的转移形式，很自然地就想到了扫描线维护 $c$ 值，具体我们枚举 $r$ 这一维，每次任意一个点的 $v_i$ 存储 $c(i,r)$，维护每个数最后出现的两个位置记为 $llst_x,lst_x$，那么将 $[llst_x + 1 , lst_x - 1]$ 区间的 $v_i - 1$ ，$[lst_x + 1 , i]$ 区间的 $v_i + 1$ 就可以维护了。       

现在问题变成了：

序列中每个位置表示成一个二元组 $(x,y)$，一共有与 $n$ 同阶的 $q$ 次区间对 $x$ 维 $+1$ 或 $-1$，查询区间内所有满足 $x_i \leq k$ 的 $y_i$ 之和，其中 $k$ 是一个定值。                 

如果单从操作只 $+1$ 或 $-1$ 以及 $k$ 是定值来看，我们可以分块维护块内排好序的数组，重构时可以通过归并排序做到单次 $O(\sqrt n)$ 修改，整块加时维护一个指针指向块内最后一个 $x_i \leq k$ 的数，暴力挪动指针，显然是单次 $O(1)$ 的，然后维护每个块内符合条件的 $y$ 值之和即可。

个人实现是使用的是链表维护排序数组，当然最正确的做法是观察到块内的 $v$ 值极差不超过 $\sqrt n$ 后对每个块开一个大小为 $\sqrt n$ 的桶充当链表，可以得到极小的常数。

时间复杂度 $O(n \sqrt n)$，大常数代码仅供参考。

```cpp
/*
又是知道了是分块优化 dp 来做的…… 
考虑一种最简单的暴力，即 dp_{i} 表示以 i 作为结尾的方案数
那么转移是 dp_{i} = \sum_{j = 1} ^ {i - 1} dp_{j} \times c(j + 1 , i)
考虑 c 函数不具备什么很特别的单调性，所以得想到一些好的办法去维护它
考虑扫描线，维护任意 lst，对于 lst 前的每一个数都加 1 
我们可以考虑分块后对每个块维护一个排好序的数组，对于散块我们直接暴力拆出来双指针拉了重构，对于整块我们直接加同时维护一个指针每次往前面扫即可 
时间复杂度 O(n \sqrt n)
好好好前面还要减一
那就把颜色段都合在一起写 
*/
#include "bits/stdc++.h"
using namespace std;
inline int read() {
    char ch = getchar();
    int x = 0, f = 1;
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while ('0' <= ch && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
inline void write(int x) {
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
const int Len = 1e5 + 5 , mod = 998244353 , SIZE = 1025;
int tim,n,k,t,sizt,pos[Len],a[Len],lst[Len],llst[Len],L[SIZE],R[SIZE],val[Len],add[SIZE],IDX[SIZE];
long long dp[Len],sum[Len],SUM[SIZE];
struct Node
{
	int L,R,wh;long long SUM;
	Node(){L = R = wh = 0;}
	Node(int LL,int RR,int WH,long long sUM){L = LL , R = RR , wh = WH , sUM = SUM;}
}Ud;
vector<Node> Sot[SIZE];
bool cmp(Node x,Node y){return val[x.wh] < val[y.wh];}
inline void MOD(long long &x){x = (x % mod + mod) % mod;}
inline void Recount(int p)
{
	SUM[p] = 0 , IDX[p] = -2;
	for(int i = 0; i < Sot[p].size() ; i ++) 
	{
		Ud = Sot[p][i];
		if(val[Sot[p][i].wh] + add[p] <= k) SUM[p] += dp[Sot[p][i].wh - 1] , MOD(SUM[p]);
		else 
		{
			IDX[p] = i - 1;
			break;
		}
	}
	if(IDX[p] == -2) IDX[p] = Sot[p].size() - 1;
}
void Relist(int p)//重新分段 
{
	int lst = 0;long long ks = 0;
	for(int i = 0 ; i < Sot[p].size() ; i ++)
	{
		if(i == Sot[p].size() - 1 || val[Sot[p][i + 1].wh] != val[Sot[p][i].wh])//分段 
		{
			for(int j = lst ; j <= i ; j ++) ks += dp[Sot[p][j].wh - 1] , MOD(ks);
			for(int j = lst ; j <= i ; j ++) Sot[p][j].L = lst , Sot[p][j].R = i , Sot[p][j].SUM = ks;
			lst = i + 1;
			ks = 0;
		}
	}
}
void newbuild(int p)
{
	for(int i = L[p] ; i <= R[p] ; i ++) Sot[p].push_back(Node(0 , 0 , i , 0));
	sort(Sot[p].begin() , Sot[p].end() , cmp);
	Relist(p) , Recount(p);
}
inline int Pre(int p,int bs){return Sot[p][bs].L - 1;}
inline int To(int p,int bs){return Sot[p][bs].R + 1;}
void upd(int p)
{
	//if(p == 2) printf("%d %lld\n",IDX[p],SUM[p]);
	//if(tim == 10 && p == 2) printf("???%d %d %d\n",p,IDX[p],add[p]);
	if(IDX[p] == -1) 
	{
		if(val[Sot[p][0].wh] + add[p] <= k) 
		{
			SUM[p] += Sot[p][0].SUM , MOD(SUM[p]);
			IDX[p] = Sot[p][0].R;
		}
		else return;	
	}
	/*if(tim == 10 && p == 2)
	{
		//printf("%lld %d\n",SUM[p],IDX[p]);
		for(int j = 0 ; j < Sot[p].size() ; j ++) printf("???%d %d %d %lld\n",Sot[p][j].wh,Sot[p][j].L,Sot[p][j].R,Sot[p][j].SUM);
	}*/
	while(IDX[p] >= 0 && val[Sot[p][IDX[p]].wh] + add[p] > k)
	{
		//printf("???%d %d %d %d %d %d %lld\n",tim,p,IDX[p],Sot[p][IDX[p]].wh,Sot[p][IDX[p]].L,Sot[p][IDX[p]].R,SUM[p]);
		SUM[p] -= Sot[p][IDX[p]].SUM , MOD(SUM[p]);
		IDX[p] = Pre(p , IDX[p]);
	}
	while(To(p , IDX[p]) < Sot[p].size() && val[Sot[p][To(p , IDX[p])].wh] + add[p] <= k)
	{
		SUM[p] += Sot[p][To(p , IDX[p])].SUM , MOD(SUM[p]);
		IDX[p] = To(p , IDX[p]);
	}
}
vector<Node> vase1,vase2;
int Bid[SIZE];
void Rebuild(int p,int LL,int RR,int w)
{
	vase1.clear() , vase2.clear();
	if(!Bid[p])
	{
		for(int i = L[p] ; i <= R[p] ; i ++) if(LL <= i && i <= RR) val[i] += w;
		return;
	}
	for(int i = L[p] ; i <= R[p] ; i ++) val[i] += add[p];
	add[p] = 0;
	for(int i = 0 ; i < Sot[p].size() ; i ++) 
	{
		if(LL <= Sot[p][i].wh && Sot[p][i].wh <= RR) vase2.push_back(Sot[p][i]) , val[Sot[p][i].wh] += w;
		else vase1.push_back(Sot[p][i]);
	}
	Sot[p].clear();
	int idx1 = 0 , idx2 = 0;
	while(idx1 < vase1.size() && idx2 < vase2.size()) 
	{
		if(val[vase1[idx1].wh] < val[vase2[idx2].wh]) 
		{
			Sot[p].push_back(vase1[idx1]);
			idx1 ++;
		}
		else
		{
			Sot[p].push_back(vase2[idx2]);
			idx2 ++;
		}
	}
	while(idx1 < vase1.size()){Sot[p].push_back(vase1[idx1]);idx1 ++;}
	while(idx2 < vase2.size()){Sot[p].push_back(vase2[idx2]);idx2 ++;}
	Relist(p) , Recount(p);
}
inline void Upd(int L,int R,int w)
{
	int Ll = pos[L] , Rr = pos[R];
	if(Ll == Rr){Rebuild(Ll , L , R , w);return;}
	Rebuild(Ll , L , R , w);
	for(int i = Ll + 1 ; i <= Rr - 1 ; i ++) 
	{
		add[i] += w;
		upd(i);
	}
	Rebuild(Rr , L , R , w);
}
int main()
{
	n = read() , k = read();
	for(int i = 1 ; i <= n ; i ++) a[i] = read();
	sizt = 200 , t = max(1 , n / sizt);
	for(int i = 1 ; i <= t ; i ++) 
	{
		L[i] = (i - 1) * sizt + 1;
		R[i] = i * sizt;
	}
	if(R[t] != n) R[t] = n;
	for(int i = 1 ; i <= t ; i ++) 
		for(int j = L[i] ; j <= R[i] ; j ++) pos[j] = i;
	dp[0] = 1;
	for(int i = 1 ; i <= n ; i ++)
	{
		tim = i;
		if(pos[i - 1] && pos[i] != pos[i - 1]) newbuild(pos[i - 1]) , Bid[pos[i - 1]] = 1;
		int adL = lst[a[i]] + 1 , kL = llst[a[i]] + 1;long long res = 0;
		//printf("%d %d %d\n",i,adL,kL);
		Upd(adL , i , 1);
		if(kL <= adL - 1) Upd(kL , adL - 1 , -1);
		for(int j = 1 ; j < pos[i] ; j ++) res += SUM[j] , MOD(res);
		//if(i == 10) for(int j = 1 ; j < pos[i] ; j ++) printf("!!!%d %lld\n",j,SUM[j]);
		//printf("%d:\n",i);
		for(int j = L[pos[i]] ; j <= i ; j ++) if(val[j] + add[pos[j]] <= k) res += dp[j - 1] , MOD(res);
		dp[i] = res;
		llst[a[i]] = lst[a[i]];
		lst[a[i]] = i;
		//printf("%d %lld\n",i,dp[i]);
	}
	printf("%lld\n",dp[n] % mod);
	return 0;
}
```

---

## 作者：wwwwwza (赞：0)

### 前言

[洛谷传送门](https://www.luogu.com.cn/problem/CF1129D)

[CF传送门](https://codeforces.com/problemset/problem/1129/D)

一道小清新分块结合动态规划。

### 暴力

设 $f_i$ 表示划分到第 $i$ 个数且为该段结尾的方案数。

可得 $f_i=\sum\limits^{i-1}_ {j=0} f_j|\operatorname{calc}(j+1,i)\leq k $

$\operatorname{calc}(i,j)$ 表示从 $i$ 到 $j$ 中恰好一次的元素个数。

因为 $a_i \leq n$，所以可以用一个桶去计算。

### 优化

分析加入 $a_i$ 会对这个桶产生什么贡献。

设 $pre_i$ 表示 $i$ 前面第一个 $j$ 且 $a_i=a_j$。

可以发现，$[pre_i,i-1]$ 这个区间 $+1$，$[pre_{pre_i},pre_i-1]$ 这个区间 $-1$。

这种操作可以用分块维护。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
const int M=317;
const int mod=998244353;
const int inf=0x3f3f3f3f;
int n,k,V,a[N],dp[N],cnt[N];
int lst[N],pre[N];
int L[N],R[N],pos[N];
inline int read(){
    int x=0,t=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')t=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*t;
}
inline void write(int x){
    if(x<0){
    	putchar('-');
		x=-x;
	}
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
struct block{
	int a[N],tag,sum;
	void add(int x,int d){
		a[x]=(a[x]+d)%mod;
		if(x<=k-tag)sum=(sum+d)%mod;
	}
	void pls(int d){
		if(d==1){
			if(k-tag>=0&&k-tag<=n)sum=(1ll*sum-a[k-tag]+mod)%mod;
			tag++;
		}else if(d==-1){
			tag--;
			if(k-tag>=0&&k-tag<=n)sum=(1ll*sum+a[k-tag]+mod)%mod;
		}
	}
	void rebuild(int i){
		int res=0;
		for(int j=L[i];j<=R[i];j++){
			add(cnt[j],mod-dp[j]);
			cnt[j]+=tag;
			add(cnt[j],dp[j]);
			if(cnt[j]<=k)res=(res+dp[j])%mod;
		}
		tag=0;
		sum=res;
	}
}b[M+5];
void init(){
	V=(n-1)/M+1;
	for(int i=1;i<=V;i++){
		L[i]=R[i-1]+1;
		R[i]=i*M;
	} 
	R[V]=n;
	for(int i=1;i<=V;i++){
		for(int j=L[i];j<=R[i];j++)pos[j]=i; 
	}
}
void insert(int x){
	b[pos[x]].rebuild(pos[x]);
	b[pos[x]].add(cnt[x],dp[x]);
}
void update(int l,int r,int d){
	if(pos[l]==pos[r]){
		b[pos[l]].rebuild(pos[l]);
		for(int i=l;i<=r;i++){
			b[pos[l]].add(cnt[i],mod-dp[i]);
			cnt[i]+=d;
			b[pos[l]].add(cnt[i],dp[i]);
		}
	}else{
		b[pos[l]].rebuild(pos[l]);
		for(int i=l;i<=R[pos[l]];i++){
			b[pos[l]].add(cnt[i],mod-dp[i]);
			cnt[i]+=d;
			b[pos[l]].add(cnt[i],dp[i]);
		}
		b[pos[r]].rebuild(pos[r]);
		for(int i=L[pos[r]];i<=r;i++){
			b[pos[r]].add(cnt[i],mod-dp[i]);
			cnt[i]+=d;
			b[pos[r]].add(cnt[i],dp[i]);
		}
		for(int i=pos[l]+1;i<=pos[r]-1;i++){
			b[i].pls(d);
		}
	}
}
int query(){
	int res=0;
	for(int i=1;i<=V;i++){
		res=(res+b[i].sum)%mod;
	}
	return res;
}
int main(){
	n=read();k=read();
	for(int i=1;i<=n;i++)a[i]=read();
	init();
	dp[1]=1;
	insert(1);
	for(int i=1;i<=n;i++){
		if(lst[a[i]])update(pre[a[i]]+1,lst[a[i]],-1);
		update(lst[a[i]]+1,i,1);
		pre[a[i]]=lst[a[i]];
		lst[a[i]]=i;
		dp[i+1]=query();
		if(i!=n)insert(i+1);
	}
	write(dp[n+1]);
	return 0;
}

```

---

## 作者：Anoshag_Ruwan (赞：0)

分块优化 dp 模板（？）

首先看到划分为若干段的形式显然考虑 dp，令 $dp_i$ 表示 $[1,i]$ 的划分方案数，$s_{l,r}$ 表示区间 $[l,r]$ 内恰好出现一次的元素个数（显然不单调），则有 $dp_i=\sum\limits_{j=0}^{i-1}dp_j[s_{j+1,i} \leq k]$，区间恰好出现一次的限制又想到要维护每个元素的前驱 $fr_i$，于是 $s_{x,x}=1,s_{x,y}=s_{x,y-1}+[fr_y<x]-[fr_y \geq x]$。$O(n^2)$ 暴力就搞定了。然后优化这东西，发现当区间右端点右移到 $i$ 时，对于左端点 $x$ 在 $(fr_i,i]$ 这段的 $s_{x,i}$ 会 $+1$，而左端点在 $(fr_{fr_i},fr_i]$ 这段的会对应 $-1$。自然考虑数据结构，你发现要做的就是维护一个数组的区间加减 $1$，动态查询 $s_x \leq k$ 对应的 $dp_x$ 之和，用常见树形结构是难做的，那就上分块。

首先维护一个 $s1$ 数组表示要维护的东西，$s_{h,j}$ 表示第 $h$ 块内所有 $s1_i \leq j$ 位置的 $dp_i$ 之和，同时对每块维护一个 $tag_i$。每次在零散块处暴力修改，整块加减 $tag$，转移时加上每个块的 $s_{i,k-tag_i}$。这是分块的基础操作。然后是细节的部分，由于对 $s$ 的定义是 $\leq$，每次新加入一个 $dp_i$ 时，相当于把其所在块从 $s_{h,0}$ 开始的后缀整体加 $dp_i$，如果用线段树维护复杂度就达到 $O(n \sqrt{n}\log n)$ 了，于是我们直接给答案打上标记。为什么从 $0$ 开始是后缀加而不是全局加？因为每次加减 $tag$ 相当于对 $s1$ 和 $s$ 整体平移，那么会不会让原本的负数下标平移到我们需要的 $k$ 位置呢？是完全可能的，所以每当这种情况时，就要在答案标记里把这个块的标记减掉，反之则需要加上。理论上 $s$ 每一块空间只需要开块长就够了，我开始用了 unordered_map 并不出意外地超时。实际上你空间是十分充裕的，另外就是避免把 $s1$ 加成负的从而使 $s$ 的负数下标非 $0$ 的情况，时空复杂度 $O(n \sqrt{n})$。

```cpp
#include<cstdio>
#include<cstring>
#include<unordered_map>
#include<cmath>
#include<algorithm>
#define si s[fk[i]][s1[i]]
#define st (fk[x]-1)*sq+1
#define en fk[x]*sq>n?n:fk[x]*sq
using namespace std;
const int N=1e5+11,p=998244353;
inline int add(int x,int y){return x+y>=p?x+y-p:x+y;}
inline int maxx(int x,int y){return x>y?x:y;}
int dp[N],fk[N],s1[N],sum=1,k,ls[N],sq,n,b[351],fr[N],tg[351],a[N],s[351][N+351];
inline void sol(int x,int y,int z){
	if(x>y)return;
	if(z<0&&tg[fk[x]]){
		tg[fk[x]]--;
		if(k==tg[fk[x]]&&z<0)sum=add(sum,b[fk[x]]);
		sol(st,x-1,-z);sol(y+1,en,-z);return;}
	for(int i=x;i<=y;i++){
		if(z>0)si=add(si,p-dp[i-1]);
		s1[i]+=z;if(z<0)si=add(si,dp[i-1]);}
}
inline int rd(){
	int i=0,j=1;char g=getchar();
	while(g>57||g<48){if(g=='-')j=-1;g=getchar();}
	while(g>47&&g<58)i=(i<<3)+(i<<1)+g-48,g=getchar();
	return i*j;
}
inline void mdf(int x,int y,int z){
	if(x>y)return;int i;
	if(fk[x]==fk[y]){
		sol(x,y,z);return;}
	sol(x,en,z);
	for(i=fk[x]+1;i<fk[y];i++){
		tg[i]+=z;
		if(k==tg[i]-1&&z>0)sum=add(sum,p-b[i]);
		if(k==tg[i]&&z<0)sum=add(sum,b[i]);}
	x=y;sol(st,y,z);
}
int main()
{
	int i,j,m;n=rd(),k=rd(),sq=sqrt(n);
	for(i=1;i<=n;i++){
		fk[i]=(i-1)/sq+1;
		a[i]=rd();fr[i]=ls[a[i]],ls[a[i]]=i;}
	for(i=dp[0]=1;i<=n;i++){
		b[fk[i]]=add(b[fk[i]],dp[i-1]);
		mdf(fr[i]+1,i,1);mdf(fr[fr[i]]+1,fr[i],-1);
		for(j=1;j<=fk[i];j++)
			if(k>=tg[j])dp[i]=add(dp[i],s[j][k-tg[j]]);
		dp[i]=add(sum,dp[i]);sum=add(sum,dp[i]);}
	printf("%d\n",dp[n]);
	return 0;
}
```


---

## 作者：free_fall (赞：0)

# 题目大意
给出一个长度为 $n$ 的序列，把它分成若干块，使得每一块中恰好出现过一次的元素个数小于等于 $k$，求满足条件的方案数，将答案对 $998244353$ 取模。
# 思路
题目中含有明显的阶段，就是下标从 $1$ 到 $i$ 时的方案数，我们可以采用 **DP** 的写法，我们用 $f_i$ 来表示每一个阶段，边界值 $f_0=1$，状态转移方程如下：

$f_i=\sum_{0\le j<i}^{} f_j$（下标为 $j$ 时合法）

此时时间复杂度为 $O(n^2)$，明显过不了。

那么我们可以用什么方式来优化这种解法呢？

我们首先可以想到，每一次转移时，我们浪费了大量的时间去搜索合法的情况，从这一点下手，我们可以用一个数组 $b$ 来记录转移 $f_i$ 时 $j$ 到 $i$ 中有多少个只出现过一次的数。

在**区间查询**时，可以采用**分块**的做法，用 $pre_i$ 来表示上一个与 $a_i$ 相同的数的下标，将数组 $b$ 中下标为 $pre_{pre_i}+1$ 到 $pre_i$ 内的数全部减一，下标为 $pre_i+1$ 到 $i$ 内的数全部加一，这样就能用 $O(\sqrt n)$ 的时间复杂度来维护 $b$ 数组。

```
void change(int l,int r,int x){
	if(l>r)return;
	if(bel[l]==bel[r]){
		for(int i=l;i<=r;++i){
			b[i]+=x;
		}
		copy(bel[l]);
		return;
	}
	for(int i=l;i<=R[bel[l]];++i){
		b[i]+=x;
	}
	copy(bel[l]);
	for(int i=L[bel[r]];i<=r;++i){
		b[i]+=x;
	}
	copy(bel[r]);
	for(int i=bel[l]+1;i<=bel[r]-1;++i){
		add[i]+=x;
	}
	return;
}
```

同理，在**区间询问**时，在每一个块中进行排序，做一次**前缀和**优化，最后**二分**查找答案，这样询问的时间复杂度就降到了 $O(n \sqrt n \log n)$，稍微卡一下常数就能过了。最后有一点一定要注意，如果下标为 $j$ 时合法，那么它转移的是 $f_{i-1}$ 而不是 $f_i$。
# 代码
主体代码如下：
```
void init(){
	C=sqrt(n/3);
	for(int i=1;i<=(n-1)/C+1;++i){
		L[i]=(i-1)*C+1;
		R[i]=i*C;
	}
	R[(n-1)/C+1]=n;
	for(int i=1;i<=n;++i){
		bel[i]=(i-1)/C+1;
	}
	f[0]=1;
	return;
}
void copy(int now){
	for(int i=L[now];i<=R[now];++i){
		c[i]={b[i],f[i-1]};
	}
	sort(c+L[now],c+R[now]+1,cmp);
	p[L[now]]=c[L[now]].f;
	for(int i=L[now]+1;i<=R[now];++i){
		p[i]=p[i-1]+c[i].f;
		if(p[i]>=mod)p[i]-=mod;
	}
	return;
}
void change(int l,int r,int x){
	if(l>r)return;
	if(bel[l]==bel[r]){
		for(int i=l;i<=r;++i){
			b[i]+=x;
		}
		copy(bel[l]);
		return;
	}
	for(int i=l;i<=R[bel[l]];++i){
		b[i]+=x;
	}
	copy(bel[l]);
	for(int i=L[bel[r]];i<=r;++i){
		b[i]+=x;
	}
	copy(bel[r]);
	for(int i=bel[l]+1;i<=bel[r]-1;++i){
		add[i]+=x;
	}
	return;
}
long long query(int x){
	long long ans=0,X=0;
	for(int i=1;i<=bel[x]-1;++i){
		int l=L[i],r=R[i],now=-1;
		while(l<=r){
			int mid=(l+r)/2;
			if(c[mid].b+add[bel[mid]]<=m){
				now=mid;
				l=mid+1;
			}
			else r=mid-1;
		}
		if(now==-1)continue;
		ans+=p[now];
		if(ans>=mod)ans-=mod;
	}
	for(int i=L[bel[x]];i<=x+X&&i<=R[bel[x]];++i){
		if(c[i].b+add[bel[x]]==0){
			++X;
			ans+=c[i].f;
			if(ans>=mod)ans-=mod;
			continue;
		}
		if(c[i].b+add[bel[i]]<=m){
			ans+=c[i].f;
			if(ans>=mod)ans-=mod;
		}
	}
	return ans;
}
int main(){
	read(n);
	read(m);
	for(int i=1;i<=n;++i){
		read(a);
		pre[i]=mark[a];
		mark[a]=i;
	}
	init();
	for(int i=1;i<=n;++i){
		change(pre[pre[i]]+1,pre[i],-1);
		change(pre[i]+1,i,1);
		f[i]+=query(i);
		if(f[i]>=mod)f[i]-=mod;
	}
	write(f[n]);
	return 0;
}
```

---

## 作者：zhongpeilin (赞：0)

## 题目大意：
有一个长度为 $n$ 的序列，现在要将他分成若干个段，使得每一段只出现一次的数字不超过 $k$，求方案数。  
## 解题思路：
首先我们可以得出一个 dp 状态：$dp_{i}$ 表示前 $i$ 个数有多少种合法方案。  
那么就有个转移式子：
$$dp_{i} = \sum_{j - 1, cnt_{j, i} \le k}^{i - 1}dp_{j - 1}$$
我们发现这个式子 $cnt_{i, j}$ 可以预处理，做到 $O(n ^ 2)$。  
但是这是不够的，所以继续优化，我们考虑一遍算 dp 一边维护 $cnt$，最后再拿一个数据结构维护一下。  
于是我们考虑怎么维护 $cnt$，我们设 $pre_{i}$ 表示在 $i$ 之前，最后一个值和 $a_{i}$ 相同的点的位置。  
那么前 $i$ 个数时的 $cnt$ 数组，和前 $i - 1$ 个数时的 $cnt$ 数组有什么不同。  
首先，前 $i$ 个比前 $i - 1$ 个要多一个 $i$，那么：
$pre_{i} < j \le i$ 的 $cnt$ 值加 `1`，而 $pre_{pre_{i}} < j \le pre_{i}$ 的 $cnt$ 值减一。  
现在操作变成两个操作：  
1. 将一段区间加一或减一。
2. 快速查询整个序列的 $cnt$ 值不超过 $k$ 的数的权值之和。  

这个我们可以使用分块加树状数组来解决这道题，就是你在加一或减一的时候，你将该块要改变的 $cnt$ 值用权值树状数组维护起来，注意整块整块地打标记时，无需改变块中的树状数组，只需到查询的时候将 $tag$ 减去即可，$O(n \times \sqrt n \times \log n)$，块长调 200 时可过。  

## CODE：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;

inline int read(){
	int x = 0;
	char op = getchar();
	while(op < '0' || op > '9') op = getchar();
	while(op >= '0' && op <= '9'){
		 x = x * 10 + (op - '0');
		 op = getchar();
	}
	return x;
}

struct BLOCKS{
	int l, r;
}blo[1005];

int tag[1005];
int lst[100005], pre[100005];
int dp[100005], sum[100005];
int B, val[100005], C[520][100005];
int n, k, a[100005], bloid[100005];

void add(int x, int y, int c){
	y++; //偏移 
	for(int i = y; i <= n + 1; i += (i & (-i))) (C[x][i] += c) %= mod;
}
int ask(int x, int y){ //在第 x 个块中找到<=y的和 
	if(y < 0) return 0; //判断 
	y++; //需要偏移 
	y = min(y, n + 1);
	int ans = 0;
	for(int i = y; i; i -= (i & (-i))) (ans += C[x][i]) %= mod;
	return ans;
}

void ADD(int l, int r, int c){
	if(bloid[l] == bloid[r]){
		for(int i = l; i <= r; i++){
			add(bloid[i], val[i], mod - dp[i - 1]); //去除 
			
			val[i] += c;
			add(bloid[i], val[i], dp[i - 1]);
		}
		return ;
	}
	
	int R = blo[bloid[l]].r;
	for(int i = l; i <= R; i++){
		add(bloid[i], val[i], mod - dp[i - 1]); //去除 
		
		val[i] += c;
		add(bloid[i], val[i], dp[i - 1]);
	}
	for(int i = bloid[l] + 1; i <= bloid[r] - 1; i++) tag[i] += c;
	
	int L = blo[bloid[r]].l;
	for(int i = L; i <= r; i++){
		add(bloid[i], val[i], mod - dp[i - 1]); //去除 
		
		val[i] += c;
		add(bloid[i], val[i], dp[i - 1]);
	}
}
int main(){
	n = read(); k = read();
	B = 200;
	for(int i = 1; i <= n; i++){ //维护块的左右端点 
		if(blo[(i - 1) / B + 1].l == 0){ 
			blo[(i - 1) / B + 1].l = i;
		}
		blo[(i - 1) / B + 1].r = i;
		bloid[i] = (i - 1) / B + 1;
	}
	
	for(int i = 1; i <= n; i++){ //求出pre，还需要一个 lst 来帮助维护 
		a[i] = read();
		pre[i] = lst[a[i]];
		lst[a[i]] = i;
	}
	
	dp[0] = 1; //初始化 
	for(int i = 1; i <= n; i++){
		add(bloid[i], val[i], dp[i - 1]); //将 i 节点的权值插入进去，注意是 dp[i - 1] 
		ADD(pre[i] + 1, i, 1); //加1操作 
		if(pre[i]){ //减一操作，要判 pre 
			ADD(pre[pre[i]] + 1, pre[i], -1);
		}	
		for(int j = 1; j <= bloid[i]; j++){ //算dp[i] 
			dp[i] = (dp[i] + ask(j, k - tag[j])) % mod; //记得减tag 
		}
	}
	printf("%d", dp[n]);
	return 0;
}

---

