# [ARC120C] Swaps 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc120/tasks/arc120_c

長さ $ N $ の数列 $ A\ =\ (A_1,\ A_2,\ A_3,\ \dots,\ A_N),\ B\ =\ (B_1,\ B_2,\ B_3,\ \dots,\ B_N) $ が与えられます。  
 以下の操作を繰り返す ($ 1 $ 回も行わなくてもよい) ことで $ A $ を $ B $ に一致させることが可能かを判定してください。また、可能なら、$ A $ を $ B $ に一致させるのに必要な最小の操作回数を求めてください。

- $ 1\ \le\ i\ \lt\ N $ を満たす整数 $ i $ を選び、以下のことを順に行う 
  - $ A_i $ と $ A_{i\ +\ 1} $ を入れ替える
  - $ A_i $ に $ 1 $ を足す
  - $ A_{i\ +\ 1} $ から $ 1 $ を引く

## 说明/提示

### 制約

- $ 2\ \le\ N\ \le\ 2\ \times\ 10^5 $
- $ 0\ \le\ A_i\ \le\ 10^9 $
- $ 0\ \le\ B_i\ \le\ 10^9 $
- 入力に含まれる値は全て整数

### Sample Explanation 1

以下のように操作すると、$ 2 $ 回の操作で $ A $ を $ B $ に一致させることができます。 - まず、$ i\ =\ 2 $ として操作する。$ A\ =\ (3,\ 5,\ 0) $ となる。 - 次に、$ i\ =\ 1 $ として操作する。$ A\ =\ (6,\ 2,\ 0) $ となる。 $ 1 $ 回以下の操作で目的を達成することはできません。

### Sample Explanation 2

この場合、$ A $ を $ B $ に一致させることは不可能です。

### Sample Explanation 3

$ 1 $ 回も操作をしなくても $ A $ が $ B $ に一致している可能性があります。

## 样例 #1

### 输入

```
3
3 1 4
6 2 0```

### 输出

```
2```

## 样例 #2

### 输入

```
3
1 1 1
1 1 2```

### 输出

```
-1```

## 样例 #3

### 输入

```
5
5 4 1 3 2
5 4 1 3 2```

### 输出

```
0```

## 样例 #4

### 输入

```
6
8 5 4 7 4 5
10 5 6 7 4 1```

### 输出

```
7```

# 题解

## 作者：Pretharp (赞：3)

好题。

首先，$A$ 中任意一个元素向前移动 $x$ 就会增加 $x$，向后相反。你可以将这理解为，如果一个元素在位置 $i$，那么其就会额外增加一个 $n-i+1$ 的偏移量（建议在纸上模拟）。因为这个偏移量在每个位置不同，这就很烦，我们可以想个办发让其相同，比如让 $A$ 中每个第 $i$ 个元素再加上 $i$，这样增加的偏移量就是 $n-i+1+i=n+1$，具体是多少不重要，只要每个位置的偏移量固定即可。

接下来们就变成给定数组 $A$，问最少交换多少次任意两个相邻数使其变为 $B$，求逆序对即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define fir first
#define sec second
#define pii pair<int, int>
const int N = 2e5 + 5;
int a[N], b[N], n, aser[N], ans;
queue<int> tmp;
map<int, int> ma, mb;
map<int, queue<int>> pos;
namespace fenwickTree {
	const int _N = N;
	struct fenwickTree_sum {
		private:
		int tr[_N];
		int lowbit(int x) {
			return x & (-x);
		}
		
		public:
		void insert(int x, int y) {
			for(int i = x; i <= n; i += lowbit(i)) {
				tr[i] += y;
			}
		}
		int query(int x) {
			int sum = 0;
			for(int i = x; i; i -= lowbit(i)) {
				sum += tr[i];
			}
			return sum;
		}
	};
}
fenwickTree::fenwickTree_sum tr;
signed main() {
	cin >> n;
	for(int i = 1; i <= n; i ++) {
		cin >> a[i];
		a[i] += i, ma[a[i]] ++;
		pos[a[i]].push(i);
	}
	for(int i = 1; i <= n; i ++) {
		cin >> b[i];
		b[i] += i, mb[b[i]] ++;
	}
	for(pii x : ma) {
		if(x.sec != mb[x.fir]) {
			return cout << -1 << endl, 0;
		}
		mb[x.fir] = 0;
	}
	for(int i = 1; i <= n; i ++) {
		aser[i] = pos[b[i]].front(), pos[b[i]].pop();
	}
	for(int i = 1; i <= n; i ++) {
		ans += (i - 1 - tr.query(aser[i])), tr.insert(aser[i], 1);
	}
	return cout << ans << endl, 0;
}
```

---

## 作者：Exp10re (赞：2)

好题好转化。

## 解题思路

注意到第 $i$ 个数在通过若干次交换到达第 $k$ 个数的位置时值为 $A_i+i-k$。

我们最终的目标是：找到一个排列 $p$，满足 $A_i+i-p_i=B_{p_i}$。

将 $p_i$ 提到等式右侧，得到 $A_i+i=B_{p_i}+p_i$。

记 $a_i=A_i+i$，$b_i=B_i+i$，则有 $a_i=b_{p_i}$。

问题被转化为给定 $a,b$，求最少邻项交换次数使得 $a=b$。

这个问题是[火柴排队](https://www.luogu.com.cn/problem/P1966)状物，两两相同值匹配求逆序对即可。

注意，本题中有相同值，需要将 $A$ 中较靠前的相同值与 $B$ 中较靠前的相同值匹配才能取得最小交换次数，邻项交换可证。

对匹配的数列求逆序对个数即可。时间复杂度 $O(n\log n)$。

---

## 作者：wzt2012 (赞：2)

### 题目概述：


有长度为 $n$ 的两个序列 $a,b$，要求通过最少的操作数把 $a$ 变成 $b$。

操作定义如下：选择 $1\le i<n$，交换 $a_i,a_i+1$，把 $a_i$ 加上 $1$，$a_i+1$ 减去 $1$。

$2\le n\le 2 \times10^5,0\le a_i,b_i\le 10^9$


### 解决方案

首先观察：无论怎么操作数列的总和是不会变的，一次操作相当于把某个数左移，并给它加 $1$。

**要从变化中找不变量**，我们对于每个数可以定义一个势能 $a_i+i$，势能相等的两个位置才可能匹配。

然后依次考虑 $b$ 的每一个位置，找到初始位置最小并且还未匹配的 $a$，由于匹配会带来他前面数位置的移动，所以用一个树状数组维护每个数已经被迫移动的距离即可，时间复杂度 $\text{O(n\ log\ n)}$。


### 参考代码：

```
#include<bits/stdc++.h>
#define pii pair<int,int>
#define int long long
using namespace std;
const int M = 200005;
int read(){
	int x = 0, f = 1;
	char c;
	while((c = getchar()) < '0' || c > '9'){
		if(c == '-') f = -1;
	}
	while(c >= '0' && c <= '9'){
		x = (x << 3) + (x << 1) + (c ^ 48); 
		c = getchar();
	}
	return x * f;
}
int n, ans, bit[M];
set<pii> s;
int lowbit(int x){
	return x&(-x);
}
void add(int x, int f){
	for(int i = x; i <= n; i += lowbit(i)){
		bit[i] += f;
	}
}
int ask(int x){
	int r = 0;
	for(int i = x; i > 0; i -= lowbit(i)){
		r += bit[i];
	}
	return r;
}
signed main(){
	n = read();
	for(int i = 1; i <= n; i ++){
		s.insert(make_pair(read() + i, i));
	}
	for(int i = 1; i <= n; i ++){
		int x = read();
		set<pii>::iterator it = s.lower_bound(make_pair(x + i, 0));
		if(it == s.end() || (*it).first != x + i){
			puts("-1");
			return 0;
		}
		int t = ask((*it).second);
		add(1, 1);
		add((*it).second, -1);
		ans += (*it).second + t - i;
		s.erase(it);
	}
	printf("%lld\n", ans); 
	return 0; 
}


```

---

## 作者：Hog_Dawa_IOI (赞：2)

### 题意
有两个数组 $a$ 和 $b$ 长度为 $n$，现在有以下操作，问是否能通过这个操作使得两数组相等。      

- 选定一个下标 $i$（$1 \le i < n$），先交换 $a_i$ 和 $a_{i+1}$，然后把 $a_i$ 加一，$a_{i+1}$ 减一。     

求最小操作次数，若无法达成目标输出 `-1`。

### 思路
首先从题目给定的操作中可以看出，一个数往左移动一个位置便会加一，往右移动一个位置便会减一。     
设第 $i$ 个数的坐标为 $p_i$，则 $a_i+i-p_i=b_{p_i}$。      
这个式子的意思是把 $a_i$ 往左移动 $i$ 个位置（移动到第 $0$ 个位置），再往右移动 $p_i$ 个位置（移动到第 $p_i$ 个位置），所得到的值就和 $b_{p_i}$ 相等。     
移项得到：$a_i+i=b_{p_i}+p_i$。     
可以发现，对应数据中数值本身与下标之和相等。     
那么我们可以在两个数组中事先对每个数据加上下标，这样操作就变成了单纯的交换相邻的两个数。     
此时想求解就很简单了，答案就是以 $b$ 数组中的顺序作为新定义的顺序，求 $a$ 数组中的逆序对数量。     
### 代码
如果有相同的元素，那么应让前面的和前面的互相匹配。
```cpp
#include<map>
#include<queue>
#include<cstdio>
using namespace std;
map<long long,queue<long long> >lwqdrq;
long long n,a[200005],b[200005],c[200005],tree[200005],ans;
int main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]),a[i]+=i,lwqdrq[a[i]].push(i);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&b[i]),b[i]+=i;
        if(!lwqdrq.count(b[i])) {printf("-1");return 0;}
        else c[i]=lwqdrq[b[i]].front(),lwqdrq[b[i]].pop();
    }
    for(int i=1;i<=n;i++)
    {
        long long sum=0;
        for(int j=c[i];j;j-=(j&(-j))) sum+=tree[j];
        ans+=i-1-sum;
        for(int j=c[i];j<=n;j+=(j&(-j))) tree[j]++;
    }
    printf("%lld",ans);
}
```

---

## 作者：Lyrella (赞：1)

# 前言

闲来无事，写一篇今天校内打模拟赛的题的题解。

# 简要题意

给一个初始序列以及一个目标序列，每次操作可以选择相邻两个位置交换数值并且向左移动的数加一、向右移动的数减一。求将原序列变成目标序列最少操作次数。

# 题解

首先可以发现当一个数加一的时候其下标减一，所以不论如何操作所有的 $i+a_i$ 一定都是定值，对于 $i+a_i$ 相同的数不管最后放在哪里都不会影响结果，所以可以对每个不同的 $i+a_i$ 考虑最后的去向。

因为题目要求最小的操作数，所以对于相同的 $i+a_i$，将原位置与目标位置一一对应一定不劣。于是我们用队列维护每个权值从而确定原位置对应的目标位置。

确定好每个点的终点后我们还要思考如何操作。考虑如果有两个数需要向左边移动，我先将右边的移动到目标位置可能会对靠左的数增加不必要的贡献。所以我们考虑钦定一个移动顺序，我是从左往右考虑终点的，先将终点在最左端的数移动到目标位置，然后再考虑左数第二个，以此类推。

最后就要考虑每完成一次移动对序列的影响。我们将每个数需要移动的距离预处理出来，规定向右为正，反之为负。当我们每次将一个数移动到左边时，我们会将路过的位置上的数向右移一步。这是一个区间加，于是随便用啥东西维护一下即可，时间复杂度 $O(n\log n)$。

# 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 2e5 + 5;

int n, a[N], b[N], pos[N], id[N], c[N];
ll res;

map < int , queue < int > > mp;

#define ls x << 1
#define rs ls | 1
ll t[N << 2], tg[N << 2];

inline void upd(int x){t[x] = t[ls] + t[rs];}
void bld(int x, int l, int r){
	if(l == r)return t[x] = c[l], void();
	int mid = l + r >> 1;
	bld(ls, l, mid), bld(rs, mid + 1, r);
}
void pd(int x, int l, int r){
	if(! tg[x])return; int mid = l + r >> 1;
	tg[ls] += tg[x]; tg[rs] += tg[x];
	t[ls] += (mid - l + 1) * tg[x];
	t[rs] += (r - mid) * tg[x];
	tg[x] = 0;
}
void mdf(int x, int l, int r, int ql, int qr, int y){
	if(ql <= l and r <= qr)return tg[x] += y, t[x] += y * (r - l + 1), void();
	int mid = l + r >> 1; pd(x, l, r);
	if(ql <= mid)mdf(ls, l, mid, ql, qr, y);
	if(mid < qr)mdf(rs, mid + 1, r, ql, qr, y);
	upd(x);
}
int qry(int x, int l, int r, int pos){
	if(l == r)return t[x]; int mid = l + r >> 1; pd(x, l, r);
	return pos <= mid ? qry(ls, l, mid, pos) : qry(rs, mid + 1, r, pos);
}

bool cmp(int x, int y){return pos[x] < pos[y];}

int main(){
	cin >> n;
	for(int i = 1; i <= n; ++i)cin >> a[i], mp[a[i] + i].push(i);
	for(int i = 1; i <= n; ++i){
		cin >> b[i];
		if(mp[i + b[i]].empty())return puts("-1"), 0;
		pos[i] = mp[i + b[i]].front(); c[i] = pos[i] - i;
		id[i] = i; mp[i + b[i]].pop();
	}
//	for(int i = 1; i <= n; ++i)cout << c[i] << endl;
	sort(id + 1, id + 1 + n, cmp);
	bld(1, 1, n);
	for(int i = 1; i <= n; ++i){
		int x = qry(1, 1, n, id[i]); res += - x;
		if(id[i] > 1)mdf(1, 1, n, 1, id[i] - 1, - 1);
	}
	cout << res;
	return 0;
}
```

---

## 作者：__xxy_free_ioi__ (赞：1)

# AT_arc120_c [ARC120C] Swaps 2

一道肥肠绕的题目。。。

## 思路

如果直接求肯定是不行的，我们可以考虑用其他的思路切入，比如说，将题目中的序列转换为定值，观察题目中的序列和规则可以发现一个非常神秘的规律，无论怎么操作，$A_i + i$ 为定值，$B_i + i$ 为定值。所以我们就可以根据这一个性质来进行计算，设数组 $C$ 使得 $C_i = A_i + i$，$D$ 使得 $D_i = B_i + i$，而题目中的意思也变为了将 $C$ 数组中相邻的两数交换数次，使得它与 $D$ 数组相同。

将题意转换后就十分简单了，我们把 $D$ 数组映射到 $C$ 数组之中，再对其进行一次求逆序对即可。但是要注意，$D$ 数组中可能有重复的值，使用 vector 记录下每一个值出现的位置即可。而求逆序对用归并排序或树状数组都可以。

## 代码

```
#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define qk_in ios::sync_with_stdio(0);cin.tie(0);

struct BIT {
	int n;
	vector<ll> tr;
	BIT(int _n) : n(_n), tr(n + 2) {}
	void add(int p, int d) {
		while (p <= n) 
			tr[p] += d, p += (p & -p);
	}
	ll qurey(int p) {
		int res = 0;
		while (p)
			res += tr[p], p -= (p & -p);
		return res;
	}
};

int main() {
	qk_in
	
	int n;
	cin >> n;
	
	vector<int> a(n), b(n);
	unordered_map<int, vector<int> > ma, mb;
	
	for (int i = 0; i < n; i++)
		cin >> a[i], a[i] += i, ma[a[i]].push_back(i + 1); // map记录 
	for (int i = 0; i < n; i++)
		cin >> b[i], b[i] += i, mb[b[i]].push_back(i + 1);
	
	for (const auto& p : ma)
		if (!mb.count(p.first) | mb[p.first].size() != p.second.size())
			return cout << -1, 0; // 不符合条件 
	
	ll ans = 0;
	BIT tree(n);
	
	for (int i = n - 1; i >= 0; i--) { // 求逆序对 
		int A = a[i], s = mb[A].back();
		mb[A].pop_back();
		ans += tree.qurey(s - 1);
		tree.add(s, 1);
	}
	
	cout << ans << '\n';
	
	return 0;
}

```

---

## 作者：FreedomKing (赞：1)

与 [P1966 [NOIP2013 提高组] 火柴排队](https://www.luogu.com.cn/problem/P1966) 类似，建议先通过 P1966 再做此题。

### 思路

前置知识：如何求朴素的序列逆序对个数（[P1908 逆序对](https://www.luogu.com.cn/problem/P1908)）。关于如何求逆序对，本文讲解归并排序和树状数组（线段树）两种方式。

- 对于归并排序，发现在合并任意两个相邻子序列时因为合并出来的序列存在单调性所以可以在合并时统计逆序对个数，好想但是实现较树状数组麻烦一点；
  
- 树状数组做法非常直观，先建一颗值域树状数组动态维护每个元素出现次数，因为求逆序对时只关心元素的相对大小，可以直接对序列离散化一下。从前往后扫描序列，在扫描到元素 $a_i$ 时将树状数组对应的 $i$ 位置加 $1$，可以发现元素 $a_i$ 与每个 $a_j>a_i,(j<i)$ 形成逆序对，也就是将答案加上树状数组上 $a_i+1$ 到 $\max_{j=1}^{i-1}{a_j}$ 区间的元素和，可以转化成 $i-query(a_i)$，其中 $query(x)$ 表示树状数组在 $1$ 到 $x$ 区间的元素出现次数和，$i$ 是已经加入的元素个数。

以开头的火柴排队为例，求朴素序列逆序对个数扩展到序列相对另一个序列的逆序对个数。依然是先离散化建值域树状数组，区别在于将其中一个序列作为一个映射，将值域树状数组维护的序列重新映射，另一个序列在扫描加入时按照映射加入，按照映射查询。

火柴排队参考核心代码：

```cpp
//缺省源和树状数组板子
//qr 和 qw 分别是快读快写
	n=qr;
	for(int i=1;i<=n;i++) f[i]=a[i]=qr;
	for(int i=1;i<=n;i++) g[i]=b[i]=qr;
	sort(f+1,f+n+1);
	sort(g+1,g+n+1);
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(f+1,f+n+1,a[i])-f;
		to[a[i]]=i;
		b[i]=lower_bound(g+1,g+n+1,b[i])-g;
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		add(to[b[i]],1);
		(ans+=i-query(to[b[i]]))%=mod;
	}
	qw(ans);
```

考虑如何将本题转换为火柴排队。首先还是考虑固定其中一个序列，这里固定 $B$。容易发现的，若 $A,B$ 中存在元素 $A_i+(i-1)=B_j+(j-1)$，那么 $A_i$ 一定可以交换到 $B_i$ 的对应位置，证明：设 $i>j$ 则有 $A_i+(i-1)-(j-1)=B_j+(j-1)-(j-1)$ 即 $A_i+(i-j)=B_j$。

综合上述，我们可以直接在输入时对任意 $A_i,B_i$ 加上 $i-1$，然后做类似火柴排队的东西，唯一需要注意的是本题不保证序列元素互异，所以需要在映射时开一个队列，按照顺序匹配即可。

关于无解，当且仅当经过转换后的序列 $A,B$ 存在不同元素时输出 $-1$。

具体实现见代码及注释。

### AC Code

```cpp
#include<bits/stdc++.h>
#include <cstdio>
//#pragma GCC optimize("Ofast")
bool M1;
#define look_memory cerr<<abs(&M2-&M1)/1024.0/1024<<" MB\n"
#define look_time cerr<<(clock()-Time)*1.0/CLOCKS_PER_SEC<<'\n'
#define File(_) freopen(_".in","r",stdin);freopen(_".out","w",stdout)
#define int long long
using namespace std;
namespace FreedomKing_qwq{};
using namespace FreedomKing_qwq;
const int N=1e6+5,mN=3e4+5,mod=1e8-3;
namespace FreedomKing_qwq{
#define Time 0
#define lowbit(_) (_&-_)
	struct Dset{
		int fa[N];
		inline void init(int x){
			for(int i=1;i<=x;i++) fa[i]=i;
			return;
		}
		inline int find(int x){
			return (fa[x]==x?x:fa[x]=find(fa[x]));
		}
		inline void update(int x,int y){
			x=find(x);y=find(y);
			fa[x]=y;
			return;
		}
	};
#define lc (p<<1)
#define rc (p<<1|1)
	inline int qread(){
#define qr qread()
		int x=0,c=getchar(),t=1;
		while(c<'0'||c>'9'){
			t^=(c=='-');
			c=getchar();
		}
		while(c>='0'&&c<='9'){
			x=(x<<3)+(x<<1)+c-'0';
			c=getchar();
		}
		return (t?x:-x);
	}	
	inline void qwrite(int x){
#define qw(_) qwrite(_)
#define qws(_) qw(_),putchar(' ')
#define qwe(_) qw(_),putchar('\n')
		if(x<0) x=-x,putchar('-');
		if(x>9) qwrite(x/10);
		putchar(x%10+'0');
		return;
	}
	inline int qpow(int x,int p,int mod){
		mod=(mod?mod:LONG_LONG_MAX);
		x=(p?x:1)%mod;
		int t=1;
		while(p>1){
			if(p&1) t=(t*x)%mod;
			x=(x*x)%mod;
			p>>=1;
		}
		return (x*t)%mod;
	}
	inline int gcd(int x,int y){return (x%y==0?y:gcd(y,x%y));}
	inline int lcm(int x,int y){return (x/gcd(x,y)*y);}
#define pf(_) ((_)*(_))
}
int n,a[N],b[N],f[N],g[N],tr[N<<1];
queue<int>to[N];
//树状数组板子
inline void add(int p,int x){
	for(;p<=n;p+=lowbit(p)) tr[p]+=x;
	return;
}
inline int query(int p){
	int sum=0;
	for(;p;p-=lowbit(p)) sum+=tr[p];
	return sum;
}
bool M2;signed main(){
//	File("");
	n=qr;
	for(int i=1;i<=n;i++) f[i]=a[i]=qr+i-1;
	for(int i=1;i<=n;i++) g[i]=b[i]=qr+i-1;
	//离散化
	sort(f+1,f+n+1);
	sort(g+1,g+n+1);
	for(int i=1;i<=n;i++) if(f[i]!=g[i]) return qw(-1),0;//无解
	unique(f+1,f+n+1);
	int m=unique(g+1,g+n+1)-g;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(f+1,f+m+1,a[i])-f;
		to[a[i]].push(i);//按照顺序加入匹配队列
		b[i]=lower_bound(g+1,g+m+1,b[i])-g;
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		//逆序对板子
		add(to[b[i]].front(),1);
		ans+=i-query(to[b[i]].front());
		to[b[i]].pop();
	}
	qw(ans);
	return 0;
}
```

---

## 作者：蒟酱 (赞：1)

好难啊，会也不会

设 $a_i=x,a_{i+1}=y$，那么交换后 $a_i=y+1,a_{i+1}=x-1$，发现交换后就是 $a_i+i$ 和 $a_{i+1}+i+1$ 这两个值进行了交换。  
那就把所有 $a_i$ 变成 $a_i+i$，把所有 $b_i$ 变成 $b_i+i$，那就是进行最少的操作把 $a$ 变成 $b$，那就直接逆序对计算数量。  
注意，如果有相同的值，应该把这些放到 `queue` 中，让前面的和前面的去匹配，这样最优。
```cpp
//不向焦虑与抑郁投降，这个世界终会有我们存在的地方。
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<map>
#include<queue>
using std::cin;using std::cout;
using loli=long long;
constexpr bool ying=false,yang=true;
constexpr int N=4e5+1;
std::map<int,std::queue<int>>mp;
int n,a[N],b[N],c[N];
loli sum=0;
struct{
	int d[N];
	void add(int x){for(;x<=n;x+=x&-x)d[x]++;}
	loli ask(int x){loli k=0;for(;x;x-=x&-x)k+=d[x];return k;}
}tr;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);cin.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i],a[i]+=i,mp[a[i]].push(i);
	for(int i=1;i<=n;i++)
		cin>>b[i],b[i]+=i;
	for(int i=1;i<=n;i++)
		if(!mp.count(b[i]))return cout<<"-1",0;
		else c[i]=mp[b[i]].front(),mp[b[i]].pop();
	for(int i=1;i<=n;i++)
		sum+=i-1-tr.ask(c[i]),tr.add(c[i]);
	cout<<sum;
	return 0;
}
```

---

## 作者：SamHJD (赞：0)

# ARC120C

> 给出序列 $a$ 和 $b$，你可以将 $a_i,a_{i+1}$ 交换，然后将 $a_i+1$，$a_{i+1}-1$。
>
> 求将 $a$ 转变为 $b$ 的最小操作次数。

尝试将操作可视化，聚焦在一个数上，我们发现可以将这个数向前交换一个位置并将其加 $1$，或将其向后交换一个位置并将其减 $1$。

设第 $i$ 个数最终的位置为 $p_i$，则有：

$$b_{p_i}=a_i+i-p_i$$

移项得：

$$b_{p_i}+p_i=a_i+i$$

于是 $a'_i=a_i+i$ 与 $b'_i=b_i+i$ 是一一对应的。题面中的操作转化为交换 $a'_i$，只需求出 $a'_i$ 变为 $b'_i$ 的最小交换次数。可以用逆序对实现。

```cpp
#include "bits/stdc++.h"
#define int long long
#define rep(i,s,t) for(int i=s;i<=t;++i)
#define per(i,t,s) for(int i=t;i>=s;--i)
using namespace std;
template<typename T>
inline void read(T &x) {
	x=0;int f=1;char c=getchar();
	for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=x*10+c-'0';
	x*=f;
}
const int N=2e5+10;
int n,a[N],b[N],sa[N],sb[N];
int id[N],pos[N],c[N],t[N],ans;
map<int,int> mp;
int book[N],cnt;
vector<int> v[N];
int lowbit(int x){return x&-x;}
void add(int x,int k){for(int i=x;i<=n;i+=lowbit(i))t[i]+=k;}
int sum(int x){int res=0;for(int i=x;i;i-=lowbit(i))res+=t[i];return res;}
signed main(){
	read(n);
	rep(i,1,n) read(a[i]),a[i]+=i,mp[a[i]]++;
	rep(i,1,n){
		read(b[i]);b[i]+=i;
		mp[b[i]]--;
		if(mp[b[i]]<0){
			printf("-1");
			return 0;
		}
	}
	rep(i,1,n) book[++cnt]=b[i];
	sort(book+1,book+n+1);cnt=unique(book+1,book+n+1)-book-1;
	rep(i,1,n) a[i]=lower_bound(book+1,book+cnt+1,a[i])-book;
	rep(i,1,n) b[i]=lower_bound(book+1,book+cnt+1,b[i])-book;
	int k=0;
	rep(i,1,n) v[b[i]].push_back(++k);
	rep(i,1,n) c[i]=v[a[i]][pos[a[i]]++];
	per(i,n,1){
		add(c[i],1);
		ans+=sum(c[i]-1);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Sirkey (赞：0)

这个题思维难度很低，随便搞。

整一个力大砖飞的做法。把一个点从到第一个点的值会变成几记下来，再在 $B$ 当中找。很显然如果到一会变成的值相同那么这个点一定可以到这个点。我们从小到的挨着来，也可以保证距离最小。

通过上述方法，我们得到了每一个点对应的点。接下来我们求一下逆序对，逆序对的求法很多，线段树和树状数组都可以。

那么这道题就搞定了。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define debug(x) cout<<#x<<":"<<x,puts("");
#define FOR(i,a,b) for(ll i=(a); i<=(b); ++i)
#define ROF(i,a,b) for(ll i=(a); i>=(b); --i)
//
//
//
using namespace std;
inline ll read() {
	ll f = 0, t = 0;
	char c = getchar();
	while (!isdigit(c)) t |= (c == '-'), c = getchar();
	while (isdigit(c)) f = (f << 3) + (f << 1) + c - 48, c = getchar();
	return t ? -f : f;
}
const int MX = 3e5 + 10;
int a[MX], b[MX];
int h[MX], p[MX];
map<int, basic_string<int> >vis;
map<int, int>top;
int tree[MX * 4];
#define lw(x) (x<<1)
#define rw(x) (x<<1|1)
#define mid ((l+r)/2)
void push_up(int x) {
	tree[x] = tree[lw(x)] + tree[rw(x)];
}
void change(int x, int l, int r, int id) {
	if (l == r) {
		tree[x]++;
		return;
	}
	if (id <= mid) change(lw(x), l, mid, id);
	else change(rw(x), mid + 1, r, id);
	push_up(x);
}
int find(int x, int l, int r, int ln, int rn) {
	if (ln > rn) return 0;
	if (ln <= l && r <= rn) {
		return tree[x];
	}
	int A = 0;
	if (ln <= mid) A += find(lw(x), l, mid, ln, rn);
	if (rn > mid) A += find(rw(x), mid + 1, r, ln, rn);
	return A;
}
signed main() {
	ios::sync_with_stdio(0), cout.tie(0);
	int n = read();
	FOR(i, 1, n) a[i] = read();
	FOR(i, 1, n) b[i] = read();
	FOR(i, 1, n) vis[a[i] + i - 1] += i;
	int flag = 0;
	FOR(i, 1, n) {
		if (vis[b[i] + i - 1].size() > top[b[i] + i - 1]) {
			h[i] = vis[b[i] + i - 1][top[b[i] + i - 1]];
			top[b[i] + i - 1]++;
			continue;
		}
		flag = -1;
	}
	if (flag == -1) return cout << -1, 0;
	int ans = 0;
	FOR(i, 1, n) {
		if (h[i] + find(1, 1, n, h[i] + 1, n) > i) ans += (h[i] - i) + find(1, 1, n, h[i] + 1, n);
		change(1, 1, n, h[i]);
	}
	cout << ans;
	return 0;
}
```
——end——

---

## 作者：naught (赞：0)

# [ARC120C] Swaps 2

$-1$ 的情况判错卡了 $10$ 几分钟，麻了。

## 题面翻译

给出 $2$ 个序列 $a$ 和 $b$，定义一次操作为：

- 选定一个下标 $i$，先将 $a_i$ 以及 $a_{i+1}$ 交换，然后让 $a_i$ 加一，最后让 $a_{i+1}$ 减一。

求最少操作次数使得 $a$ 序列等于 $b$ 序列，否则输出 `-1`。

## Solution

手动模拟几次操作之后，发现：

>$a_i$ 经过一次操作后变成的 $a_{i+1}+i+1$ 不会变。

举个栗子：$a_1 = 4$，$a_2 = 6$，对 $a_1$ 进行操作，$a_1 = 7$，$a_2 = 3$，$1+4 = 2+3$。

由于结论显然，这里不作证明了。

于是问题便转化为了：

给出 $2$ 个序列 $a$ 和 $b$，每次操作你可以交换 $a$ 中相邻的 $2$ 个数，求使 $a$ 等于 $b$ 的最小操作次数。

这是个小 $trick$，该问题可转化为求逆序对个数，这里使用归并排序求逆序对数，时间复杂度为 $O(n \times \log_{2}{n})$。

至于判断负数，有 $2$ 种情况：

* 两个序列总和不同。（因为操作不影响序列的总和）

* 转化过后的 $a$ 序列和 $b$ 序列有不同数字。

其实第 $1$ 种情况本质上就是第 $2$ 种情况。

至于如何处理，将 $a$ 中数字放入 `map` 中计数，再在 $b$ 中判断即可。

## 代码

```cpp
// written by Naught
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define Maxn 200005
#define fo(i, l, r) for (int i = l; i <= r; ++i)
#define fr(i, r, l) for (int i = l; i >= r; --i)
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21], *p1 = buf, *p2 = buf;
inline int read(int x=0, bool f=0, char c=getchar()) {for(;!isdigit(c);c=getchar()) f^=!(c^45);for(;isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);return f?-x:x;}

int n, sum_cnt, a[Maxn], b[Maxn], A[Maxn], B[Maxn], c[Maxn];
ll sum, ans;
map<int, queue<int>> mp;
map<int, int> cnt;

void merge_sort(int l, int r)
{
    if ( l == r ) return;
    int mid = (l + r) >> 1, i = l, j = mid+1, k = l;
    merge_sort( l , mid );
    merge_sort( mid+1 , r );
    while ( i <= mid && j <= r )
    	if(a[i] <= a[j]) c[k++] = a[i++];
    	else c[k++] = a[j++], ans += mid-i+1;
    while ( i <= mid ) c[k++] = a[i++];
    while ( j <= r ) c[k++] = a[j++];
    fo(i, l, r) a[i] = c[i];
} 

signed main()
{
    n = read();
    fo(i, 1, n) a[i] = read(), A[i] = a[i]+i, sum += a[i], ++cnt[A[i]], sum_cnt += cnt[A[i]] == 1;
    fo(i, 1, n) b[i] = read(), B[i] = b[i]+i, mp[B[i]].push(i), sum -= b[i], --cnt[B[i]], sum_cnt -= cnt[B[i]] == 0;
    if(sum_cnt || sum) return puts("-1"), 0;
    fo(i, 1, n) a[i] = mp[A[i]].front(), mp[A[i]].pop();
    merge_sort(1, n);
    printf("%lld", ans);
    return 0;
}
```

---

