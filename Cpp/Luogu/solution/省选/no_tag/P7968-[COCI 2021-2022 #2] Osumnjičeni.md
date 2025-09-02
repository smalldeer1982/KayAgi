# [COCI 2021/2022 #2] Osumnjičeni

## 题目描述

现有 $n$ 个嫌疑人。由于其身高的不确定性，只知道每个嫌疑人的身高范围 $[l_i,r_i]$。

每次调查可以选取编号范围为 $[a,b]$ 内的所有嫌疑人，要求他们的身高范围没有交集。若嫌疑人在某次调查中出现，则目击者可以立即作出正确的判断。

给定 $q$ 组询问，每次给出 $p_i,q_i$。求在嫌疑人锁定在 $[p_i,q_i]$ 范围内的前提下，最多需要进行多少次调查。

## 说明/提示

**【样例 3 解释】**

- 询问 $1,3$：在 $[1,1],[2,3],[4,5]$ 范围内进行调查即可，答案为 $3$。
- 询问 $2$：调查 $[3,5]$ 即可，答案为 $1$。

**【数据规模与约定】**

**本题采用子任务捆绑测试。**

- Subtask 1（10 pts）：$q=p_1=1$，$q_1=n$。
- Subtask 2（10 pts）：$1 \le n,q \le 5000$。
- Subtask 3（20 pts）：$1 \le n \le 5000$。
- Subtask 4（20 pts）：$1 \le q \le 100$。
- Subtask 5（50 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le n,q \le 2 \times 10^5$，$1 \le a \le b \le n$，$1 \le l_i \le r_i \le 10^9$，$1 \le p_i \le q_i \le n$。

**【提示与说明】**

**题目译自 [COCI 2021-2022](https://hsin.hr/coci/) [CONTEST #2](https://hsin.hr/coci/contest2_tasks.pdf) _Task 5 Osumnjičeni_。**

**本题分值按 COCI 原题设置，满分 $110$。**

## 样例 #1

### 输入

```
2
1 1
1 1
3
1 1
2 2
1 2```

### 输出

```
1
1
2```

## 样例 #2

### 输入

```
3
1 1
2 2
3 3
3
1 1
2 3
1 3```

### 输出

```
1
1
1```

## 样例 #3

### 输入

```
5
1 3
3 3
4 6
2 3
1 1
3
1 4
3 5
1 5```

### 输出

```
3
1
3```

# 题解

## 作者：钰瑾_恋涵 (赞：6)

[题目链接](https://www.luogu.com.cn/problem/P7968)

#### 题目大意：

给你 $n$ 个人的身高范围，一次操作可以将连续的一段人排除，但要求这些人身高没有交集，有 $Q$ 个询问，每个询问给定 $l$，$r$ 问最多需要几次操作可以将 $l - r$ 之间的人全部排除。

#### 分析：

考虑贪心，对于一次操作，设其左端点为 $l$，那么我们一定会让右端点尽可能的大，所以 $r$ 选择身高无交集的最大的 $r$。

对于每一个 $l$  们都求出它的 $r$，这一操作可以用数据结构去维护，我这里用的是单调队列加线段树，复杂度为 $O(n\log n)$。

另外身高很高啊，还要离散化。

然后整道题目就很清晰了，就相当于[最少线段覆盖](https://www.luogu.com.cn/problem/CF1175E)，这就是倍增优化 DP 的板子题了，点可以转成线段。

#### code

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

i64 read() {
	i64 x(0), f(0); char ch = getchar();
	while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
	while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	return f ? -x : x;
}
int __stk[128], __len;
void put(i64 x) {
	if (x < 0) putchar('-'), x = -x;
	do { __stk[++__len] = x % 10, x /= 10; } while (x);
	while (__len) putchar(__stk[__len--] ^ 48);
}
const int N = 401010;
int n, q, cnt;
int L[N], R[N], c[N];
int f[N][22];

struct Tree {
	#define mid ((l + r) >> 1)
	#define ls (x << 1)
	#define rs (x << 1 | 1)
	int t[N << 4], tag[N << 4];
	void pushdown(int x) {
		if (tag[x]) {
			t[ls] += tag[x], tag[ls] += tag[x];
			t[rs] += tag[x], tag[rs] += tag[x];
			tag[x] = 0;
		}
	}
	void modify(int x, int l, int r, int L, int R, int v) {
		if (l >= L && r <= R) return t[x] += v, tag[x] += v, void();
		pushdown(x);
		if (mid >= L) modify(ls, l, mid, L, R, v);
		if (mid < R) modify(rs, mid + 1, r, L, R, v);
		t[x] = max(t[ls], t[rs]);
	}
	int ask(int x, int l, int r, int L, int R) {
		if (l >= L && r <= R) return t[x];
		pushdown(x); int ans = 0;
		if (mid >= L) ans = max(ans, ask(ls, l, mid, L, R));
		if (mid < R) ans = max(ans, ask(rs, mid + 1, r, L, R));
		return ans;
	}
}T;

signed main() {
//	freopen("osumnjiceni.in","r",stdin);
//	freopen("osumnjiceni.out","w",stdout);
	n = read();
	for (int i = 1; i <= n; ++i) {
		c[++cnt] = L[i] = read();
		c[++cnt] = R[i] = read(); 
	}
	sort(c + 1, c + cnt + 1), cnt = unique(c + 1, c + cnt + 1) - c - 1;
	for (int i = 1; i <= n; ++i) {
		L[i] = lower_bound(c + 1, c + cnt + 1, L[i]) - c;
		R[i] = lower_bound(c + 1, c + cnt + 1, R[i]) - c;
	}
	int p = 1;
	for (int i = 1; i <= n; ++i) {
		while (T.ask(1, 1, cnt, L[i], R[i])) {
			f[p - 1][0] = i - 1;
			T.modify(1, 1, cnt, L[p], R[p], -1), ++p;
		}
		T.modify(1, 1, cnt, L[i], R[i], 1);
	}
	while (p <= n + 1) f[p - 1][0] = n, ++p;
	for (int j = 1; j <= 20; ++j) 
		for (int i = 0; i <= n; ++i) 
			f[i][j] = f[f[i][j - 1]][j - 1];
	q = read();
	while (q--) {
		int l = read() - 1, r = read(), ans = 1;
		for (int i = 20; ~i; --i) if(f[l][i] < r) ans += 1 << i, l = f[l][i];
		put(ans), putchar('\n');
	}
	return 0;
}
```





---

## 作者：yllcm (赞：2)

写个证明。

明确一下题意：构造操作最少的方案使得对于任意身高情况均能查出嫌疑人。

先考虑 $l_i=r_i$ 的情况。猜测最优方案一定是从左往右，每次找到以 $x$ 为左端点（初始 $x=1$）的最大区间 $[x,y]$，使得 $[x,y]$ 没有重复元素。操作区间 $[x,y]$，并令 $x\gets y+1,ans\gets ans+1$，重复上述过程。

考虑归纳证明。结论对于长度为 $1$ 的序列显然成立。对于长度 $n>1$ 的序列，假设第一次操作中，最优方案 A 操作了 $[1,x]$（假设 $x<n$），另一种可能的方案 B 操作了 $[1,y]$ 使得 $y>x$。容易发现的事实是，做完前者后，问题变成 $[x+1,n]$ 的子问题，做完后者后，问题变成 $S+[y+1,n]$ 的子问题，其中 $S$ 是 $[1,y]$ 中出现了至少两次的元素按原序列顺序排列得到的序列。若方案 B 没有删去任何元素，那么显然不优，否则我们将问题归到了规模更小的子问题，根据归纳假设，此时最优方案一定是每次找到左侧最大的不重复区间。设方案 B 第一次操作完之后的第二次操作为 $[1,z]$，显然 $z<|S|$，并且 $S_z\leq x$，否则 $x$ 一定可以更大。那么在这次操作的同时，我们对方案 A 操作 $[x+1,y]$，此时可以发现，方案 A 经过两次操作后的序列一定为方案 B 的子集，所以一定更优。

知道最优策略之后，我们着手考虑 $l_i\neq r_i$ 的操作，注意到若两个区间有交，那么它一定在某种情况中相等，此时需要把它分开。那么此时第一个区间的定义是：最长的区间使得区间内的区间两两交集为空。考虑对于每个左端点找到最优的右端点，此时需要找到 $suf_i$ 表示 $i$ 后第一个与 $[l_i,r_i]$ 交集非空的区间。可以使用线段树解决：每次加入区间 $j$ 的时候，在线段树上的 $[l_j,r_j]$ 区间执行对 $j$ chkmin。查询 $suf_i$ 的时候，找到 $[l_i,r_i]$ 的区间最小值即可。找到 $suf_i$ 之后，我们对其求一个后缀 $\min$ 即可得到结果。暴力模拟跳跃可以做到 $\mathcal{O}(n^2)$。

考虑优化模拟，发现如果将 $i$ 跳跃到的节点作为 $i$ 的父亲，则我们会得到一棵树，在树上倍增即可做到 $\mathcal{O}(n\log n)$。

[代码](https://loj.ac/s/1856988)，写的是从右往左跳。

---

## 作者：Usada_Pekora (赞：2)

今天学弟问我的一道题，过来看了看发现题解好像没有对一些细节说明？在此作一些补充。

首先转化题意，给出 $n$ 个人，每个人带有一个值域上下界，每次可以选出编号连续且值域上下界无交集的一些人进行覆盖，$q$ 次询问，每次询问问完全覆盖 $[l,r]$ 最少要多少次操作？

考虑贪心，显然，当编号连续的两段 $[l,x),[x,r]$ 在值域上完全无交集时，可以考虑将这两段一起覆盖（多覆盖的部分超出询问右边界时对于答案没有影响，而在询问范围内将二者同时覆盖一定是更好的选择）。

所以对于每个人 $i$，我们都选出编号最靠后且满足 $[i,j]$ 值域上无交集的一个 $j$ 作为转移的右边界。

这里采用双指针维护，维护一个值域上不重复的集合，当右指针可以扩张时就尽量扩张，然后在左指针已经处理好后将其删去并右移。

覆盖部分，我们在已经处理好的所有段里面选出并覆盖，可以采用倍增或并查集优化，可以参考[这道题](https://www.luogu.com.cn/problem/CF1175E)，注意到一点，就是我们的倍增算法是基于端点相交的覆盖情况，而本题的样例就告诉我们不需要也不可能是端点相交的情况，那么直接套用会导致答案为一个很大的值（因为始终在右端点覆盖自身）。有一种比较巧妙的解决方案是：令所有覆盖方式变成左开右闭，即令倍增中 $f_{i,j}$ 表示原先的 $f_{i+1,j}$，类似于选出一段后，在将指针右移一位，这样一来就可以处理本题的情况了。

代码如下。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int n, q, cnt, l[N], r[N], a[N], c[N << 1], d[N << 1], dd[N << 1], f[18][N];
char ibuf[N], *is = ibuf, *ie = ibuf;
inline char gc() {
	return is == ie && (is = ibuf, ie = ibuf + fread(ibuf, 1, N, stdin)), is == ie ? EOF : *is++;
}
inline int read() {
	int x = 0;
	char ch = gc();
	while (!isdigit(ch))
		ch = gc();
	while (isdigit(ch))
		x = (x << 1) + (x << 3) + (ch ^ 48), ch = gc();
	return x;
}
inline void modify(int t[], int x, int k) {
	while (x <= cnt) {
		t[x] += k;
		x += (x & -x);
	}
}
inline int query(int t[], int x) {
	int res = 0;
	while (x) {
		res += t[x];
		x -= (x & -x);
	}
	return res;
}
inline void Modify(int l, int r, int k) {
	modify(d, l, k), modify(d, r + 1, -k);
	modify(dd, l, l * k), modify(dd, r + 1, (r + 1) * -k);
}
inline int Query(int l, int r) {
	return (r + 1) * query(d, r) - query(dd, r) - l * query(d, l - 1) + query(dd, l - 1);
}
signed main() {
	n = read();
	for (int i = 1; i <= n; i++) {
		l[i] = read(), r[i] = read();
		c[++cnt] = l[i], c[++cnt] = r[i];
	}
	sort(c + 1, c + cnt + 1);
	cnt = unique(c + 1, c + cnt + 1) - c - 1;
	for (int i = 1; i <= n; i++) {
		l[i] = lower_bound(c + 1, c + cnt + 1, l[i]) - c;//仅在乎有无交集，即相对大小关系，离散化处理即可。
		r[i] = lower_bound(c + 1, c + cnt + 1, r[i]) - c;
	}
	int R = 0;
	for (int L = 1; L <= n; L++) {
		while (R < n && Query(l[R + 1], r[R + 1]) == 0) {//BIT 维护，若对应值域区间内区间和为 0 则说明无相交可能。
			R++;
			Modify(l[R], r[R], 1);
		}
		a[L] = R;
		Modify(l[L], r[L], -1);//接下来维护区间变成[L + 1, R]，删除 L。
	}
	for (int i = 1; i <= n; i++)
	 	f[0][i - 1] = a[i];
	f[0][n] = n;//防止选择到 n 后变成 0 又来一回
	for (int i = 1; i <= 17; i++)
		for (int j = 0; j <= n; j++)
			f[i][j] = f[i - 1][f[i - 1][j]];
	q = read();
	while (q--) {
		int l = read() - 1, r = read(), ans = 0;
		for (int i = 17; ~i; i--)
			if (f[i][l] < r) ans += 1 << i, l = f[i][l];
		printf("%d\n", ans + 1);
	}
	return 0;
}
```


---

## 作者：_AyachiNene (赞：1)

# 思路：
考虑扫描线，有一个显然的贪心，扫到一个位置 $i$，肯定前面每一段要分得尽量长，且优先满足后面的段更长。可以用一个双指针和线段树，先维护出每一个区间 $[L_i,i]$ 表示以 $i$ 为右端点最长的一个满足条件的区间。考虑扫描线向后移的贡献，根据前面的贪心，区间的划分方式一定是 $[L_i,i],[L_{L_i-1},L_i-1]$ 这样划分。考虑从 $i$ 向 $L_i-1$ 连一条边，这个结构显然构成了一棵树，查询直接树上倍增即可。
# Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace IO
{
	char buff[1<<21],*p1=buff,*p2=buff;
	char getch(){return p1==p2&&(p2=((p1=buff)+fread(buff,1,1<<21,stdin)),p1==p2)?EOF:*p1++;}
	template<typename T>void read(T &x){char CH=getch();int fl=1;x=0;while(CH>'9'||CH<'0'){if(CH=='-')fl=-1;CH=getch();}while(CH<='9'&&CH>='0'){x=x*10+CH-48;CH=getch();}x*=fl;}
	template<typename T>void read_s(T &x){x="";char CH=getch();while(!(CH>='a'&&CH<='z')&&!(CH>='A'&&CH<='Z'))CH=getch();while((CH>='a'&&CH<='z')||(CH>='A'&&CH<='Z')){x+=CH;CH=getch();}}
	template<typename T,typename ...Args>void read(T &x,Args& ...args){read(x);read(args...);}
	char obuf[1<<21],*p3=obuf;
	void putch(char CH) {if(p3-obuf<(1<<21))*p3++=CH;else fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=CH;}
	char CH[100];
	template<typename T>void write(T x) {if(!x)return putch('0');if(x<0)putch('-'),x*=-1;int top=0;while(x)CH[++top]=x%10+48,x/=10;while(top)putch(CH[top]),top--;}
	template<typename T,typename ...Args>void write(T x,Args ...args) {write(x);putch(' ');write(args...);}
	void put(string s){for(int i=0;i<s.size();i++)putch(s[i]);}
	void flush(){fwrite(obuf,p3-obuf,1,stdout);}
}
using namespace IO;
int n,m;
namespace Shiki
{
	struct segt
	{
		int val,tag;
	}t[200005<<3];
	#define ls (root<<1)
	#define rs (root<<1|1)
	#define mid (l+r>>1)
	void add(int x,int y,int v,int root=1,int l=1,int r=n*2)
	{
		if(l>=x&&r<=y) return t[root].val+=v,t[root].tag+=v,void();
		if(x<=mid) add(x,y,v,ls,l,mid);
		if(y>mid) add(x,y,v,rs,mid+1,r);
		t[root].val=t[ls].val+t[rs].val+t[root].tag;
	}
	int query(int x,int y,int root=1,int l=1,int r=n*2,int tag=0)
	{
		if(l>=x&&r<=y) return t[root].val+tag;
		tag+=t[root].tag;
		int res=0;
		if(x<=mid) res+=query(x,y,ls,l,mid,tag);
		if(y>mid) res+=query(x,y,rs,mid+1,r,tag);
		return res;
	}
}using namespace Shiki;
int a[200005],b[200005];
vector<pair<int,int> >q[200005];
int ans[200005];
int bkt[200005],cnt,tot;
int f[200005][20],L[200005];
int main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n);
	for(int i=1;i<=n;i++) read(a[i],b[i]),bkt[++cnt]=a[i],bkt[++cnt]=b[i];
	sort(bkt+1,bkt+cnt+1);
	tot=unique(bkt+1,bkt+cnt+1)-bkt-1;
	for(int i=1;i<=n;i++) a[i]=lower_bound(bkt+1,bkt+tot+1,a[i])-bkt,b[i]=lower_bound(bkt+1,bkt+tot+1,b[i])-bkt;
	read(m);
	for(int i=1;i<=m;i++)
	{
		int l,r;read(l,r);
		q[r].push_back({l,i});
	}
	int cur=1;
	for(int i=1;i<=n;i++)
	{
		while(cur<i&&query(a[i],b[i])) add(a[cur],b[cur],-1),++cur;
		add(a[i],b[i],1);
		f[i][0]=cur-1;L[i]=cur;
		for(int j=1;j<20;j++) f[i][j]=f[f[i][j-1]][j-1];
//		cout<<i<<" "<<cur<<endl;
		for(auto j:q[i])
		{
			int res=0,u=i;
			for(int k=19;~k;k--) if(f[u][k]>=j.first) u=f[u][k],res+=(1<<k);
			ans[j.second]=res+1;
		}
	}
	for(int i=1;i<=m;i++) write(ans[i]),putch('\n');
	flush(); 
	return 0;
}
```

---

## 作者：ainivolAGEM (赞：1)

**前情提要：**[更好的阅读体验。](https://www.luogu.com.cn/blog/tomby-gz-2011/solution-p7968)

## 题目大意

[题目](https://www.luogu.com.cn/problem/P7968)给出 $n$ 个范围数对 $( a , b )$，给出 $q$ 此询问，每次询问给定范围 $( p , q )$，然后进行尽可能少的组合，使每次组合每对数对范围都没有交集。

## 题目分析

很容易想到，因为要求最少此组合，所以考虑右端点进行取没有交集的最大情况。然后怎么维护呢？可以发现，由于题目有关单点的修改和区间查询，所以我们可以用线段树维护。那么就直接单点修改，然后加上离散化就是一个经典的最少线段覆盖的题。

那么倍增解决问题，加上线段树（你想用树状数组也不是不行）就可以了。

**注意事项：**

- 线段树得开八倍空间。

- 别忘了求出倍增后加一。（想想你在树上倍增时求出来后要访问父节点）

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+4;
const int T=20;
ll n,m,cnt,l[N],r[N];
ll a[N],t[N*2],f[N][T];
struct Tree{
	ll l,r,sum,tag;
}tree[N*8];
void push_up(ll p){
	tree[p].sum=tree[p<<1].sum+tree[p<<1|1].sum;
}
void push_down(ll p){
	if(tree[p].tag){
		tree[p<<1].tag+=tree[p].tag;
		tree[p<<1].sum+=(tree[p].tag*(tree[p<<1].r-tree[p<<1].l+1));
		tree[p<<1|1].tag+=tree[p].tag;
		tree[p<<1|1].sum+=(tree[p].tag*(tree[p<<1|1].r-tree[p<<1|1].l+1));
		tree[p].tag=0;
	}
}
void Build_Tree(ll p,ll l,ll r){
	tree[p].l=l;
	tree[p].r=r;
	if(l==r){
		return;
	}
	ll mid=(tree[p].l+tree[p].r)>>1;
	Build_Tree(p<<1,l,mid);
	Build_Tree(p<<1|1,mid+1,r);
	push_up(p);
}
void update(ll p,ll l,ll r,ll k){
	if(l<=tree[p].l&&tree[p].r<=r){
		tree[p].sum+=(k*(tree[p].r-tree[p].l+1));
		tree[p].tag+=k;
		return;
	} 
	push_down(p);
	ll mid=(tree[p].l+tree[p].r)>>1;
	if(l<=mid){
		update(p<<1,l,r,k);
	}
	if(mid<r){
		update(p<<1|1,l,r,k);
	}
	push_up(p);
}
ll query(ll p,ll l,ll r){
	if(l<=tree[p].l&&tree[p].r<=r){
		return tree[p].sum;
	}
	push_down(p);
	ll sum=0;
	ll mid=(tree[p].l+tree[p].r)>>1;
	if(l<=mid){
		sum+=query(p<<1,l,r);
	}
	if(mid<r){
		sum+=query(p<<1|1,l,r);
	}
	return sum;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>l[i]>>r[i];
		t[++cnt]=l[i];
		t[++cnt]=r[i];
	}
	sort(t+1,t+cnt+1);
	cnt=unique(t+1,t+cnt+1)-(t+1);
	for(int i=1;i<=n;i++){
		l[i]=lower_bound(t+1,t+cnt+1,l[i])-t;
		r[i]=lower_bound(t+1,t+cnt+1,r[i])-t;
	}
	Build_Tree(1,1,cnt);
	for(int i=1,j=0;i<=n;i++){
		while(j+1<=n&&!query(1,l[j+1],r[j+1])){
			j++;
			update(1,l[j],r[j],1);
		}
		f[i][0]=j+1;
		update(1,l[i],r[i],-1);
	}
	for(int j=1;j<20;j++){
		for(int i=1;i<=n;i++){
			f[i][j]=f[f[i][j-1]][j-1]; 
		}
	}
	cin>>m;
	while(m--){
		ll p,q,ans=0;
		cin>>p>>q;
		for(int i=19;i>=0;i--){
			if(f[p][i]&&f[p][i]<=q){
				p=f[p][i];
				ans+=(1<<i);
			}
		}
		cout<<ans+1<<'\n';
	}
}
```

---

## 作者：SAMSHAWCRAFT (赞：1)

这道题有总共两个部分：
1. 给定嫌疑人身高范围，将嫌疑人分组。
2. 已知嫌疑人的编号范围，求确定这个嫌疑人至多要到多少组中去寻找。

这道题的第一部分其实就是要把一个一个的区间分成编号连续的若干组，每组组内的区间都互不重叠没有交集。我们要维护这些组才能做第二部分。很容易想到暴力，每次从嫌疑人 $\texttt {p}$ 开始，然后按顺序把嫌疑人逐一加入一个组当中。直到要添加的某个嫌疑人 $\texttt {q}$ 身高区间与这一组已有的嫌疑人的身高区间交集时，我们另开一个组，把 $\texttt{q}$ 添加到这个组中，如此往复，直至预处理完所有嫌疑人的身高区间。

在把嫌疑人 $\texttt {p}$ 加入一个组之前，我们要知道这个组中有没有身高范围和他/她的身高范围重叠的人。为了快速查找，我们可以开一个 `std::set<std::pair<int,int>>` 存储目前本组当中嫌疑人的身高范围，每个 `std::pair` 的前一个键值表示身高区间范围的左端点，后一个键值表示嫌疑人的编号。在查找的时候，我们二分找到集合中第一个身高区间范围左端点比 $\texttt {p}$ 的身高范围左端点大的人 $\texttt {p'}$，然后检验  $\texttt {p}$ 的身高区间右端点是否在 $\texttt {p'}$ 的身高区间范围中；再二分找到集合中最后一个身高区间范围左端点比 $\texttt {p}$ 的身高范围左端点小的人 $\texttt {p'}$，然后检验  $\texttt {p'}$ 的身高区间右端点是否在 $\texttt {p}$ 的身高区间范围中。如果这两个检验都是 OK 的，那么我们就把 $\texttt {p}$ 加入到这组嫌疑人当中，否则清空集合，新建一个新的组。这样做第一部分的时间复杂度是 $O(n\log n)$。

第二部分是在给定的嫌疑人编号区间中，寻找一个嫌疑人 $\texttt {X}$ 至多需要调查多少次。我们知道在给嫌疑人分好组之后，每个组都有一个唯一的嫌疑人会被找到，但要找到 $\texttt {X}$，最坏情况是我们在每个组中都找到一个嫌疑人后才找到 $\texttt {X}$，这相当于询问这个编号区间一共跨越了多少个嫌疑人组。

如果我们直接暴力看有多少个段，单次询问复杂度将是 $O(n)$ 的。考虑用数据结构优化，你可以用线段树，但没有必要，这里介绍一个比线段树常数略小一点的倍增方法。
 
我们记 $\texttt{nxt(p)}$ 为刚刚分组时，第一个无法加入 $\texttt{p}$ 所在组的嫌疑人，记 ${f(p,i)}$ 为 $\texttt{p}$ 反复做操作：$\texttt{p}\leftarrow\texttt{nxt(p)}$ 共 $2^i$ 次得到的人，即 $\texttt{p}$ 所在组后面第 $2^i$ 个组第一个加入的人，不难得到：

$$f(p,i)\leftarrow f(f(p,i-1),i-1),f(p,0)\leftarrow\texttt{nxt(p)}$$

现在我们就可以在每次询问的时候 $O(\log n)$ 地回答询问了。这样做，整道题的时间复杂度为 $O(n\log n+q\log n)$。

注意细节，代码如下，仅供参考：
``` cpp
#include <stdio.h>
#include <algorithm>
#include <set>
#define qaq inline
using ll=long long;
using piit=std::pair<int,int>;
const int sz=2e5+19;
const int logsz=19;
int n,q,lns[sz],rns[sz],f[logsz][sz];
std::set<piit> s;
int main(){
    scanf("%d",&n);
    for(int cx=1;cx<=n;++cx)
        scanf("%d%d",lns+cx,rns+cx);
    auto validIns=[](int id)->bool{
        if(s.empty()) return true;
        auto it=s.lower_bound(std::make_pair(lns[id],0));
        int prev,post=it->second;
        if(lns[id]<=lns[post]&&lns[post]<=rns[id]) return false;
        if(it!=s.begin()){
            --it,prev=it->second;
            if(lns[prev]<=lns[id]&&lns[id]<=rns[prev]) return false;
        }
        return true;
    };
    for(int lim=0,cx=1;cx<=n;++cx){
        if(lim<cx){
            s.clear();
            lim=cx;
            s.insert(std::make_pair(lns[lim],lim));
        }
        while(lim<n&&validIns(lim+1))
            lim++,s.insert(std::make_pair(lns[lim],lim));
        f[0][cx]=lim+1;
        s.erase(std::make_pair(lns[cx],cx));
    }
    f[0][n+1]=n+1;
    for(int cx=1;cx<logsz;++cx){
        for(int cy=1;cy<=n+1;++cy){
            f[cx][cy]=f[cx-1][f[cx-1][cy]];
        }
    }
    scanf("%d",&q);
    for(int cx=1,a,b,ans;cx<=q;++cx){
        scanf("%d%d",&a,&b);
        ans=0;
        for(int cy=logsz-1;~cy;--cy)
            if(f[cy][a]<=b) a=f[cy][a],ans+=(1<<cy);
        printf("%d\n",ans+1);
    }
    return 0;
}
```

---

## 作者：ax_by_c (赞：0)

显然每次取最左边一个人的极长区间。数据结构预处理出以每个人为左端点的极长区间，倍增即可求出答案。

关于贪心：你可以理解为必须选一个包含左端点的区间，那肯定选最长的。

关于预处理：用当前区间个数减去完全在左边和完全在右边的区间个数就是有交区间个数，可以 BIT。

```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=(l),qwp=(r);i<=qwp;i++)
#define per(i,r,l) for(int i=(r),qwp=(l);i>=qwp;i--)
#define repll(i,l,r) for(ll i=(l),qwp=(r);i<=qwp;i++)
#define perll(i,r,l) for(ll i=(r),qwp=(l);i>=qwp;i--)
#define UQ(hsh,hc) (sort((hsh)+1,(hsh)+1+(hc)),(hc)=unique((hsh)+1,(hsh)+1+(hc))-(hsh)-1)
#define pb push_back
#define ins insert
#define clr clear
#define uset unordered_set
#define umap unordered_map
using namespace std;
namespace ax_by_c{
typedef long long ll;
const int N=4e5+5;
const int LN=19;
struct BIT{
    int lb(int x){
        return x&(-x);
    }
    int n,tr[N];
    void clr(int n_){
        n=n_;
        rep(i,1,n)tr[i]=0;
    }
    void add(int i,int x){
        for(;i<=n;i+=lb(i))tr[i]+=x;
    }
    int q(int i){
        int r=0;
        for(;i;i-=lb(i))r+=tr[i];
        return r;
    }
    int Q(int l,int r){
        return q(r)-q(l-1);
    }
}Tl,Tr;
int n,q,l[N],r[N],hsh[N],hc,pos[N],cnt,lt[N][LN];
void slv(int _csid,int _csi){
    scanf("%d",&n);
    rep(i,1,n)scanf("%d %d",&l[i],&r[i]),hsh[++hc]=l[i],hsh[++hc]=r[i];
    UQ(hsh,hc);
    Tl.clr(hc),Tr.clr(hc);
    for(int i=n,j=n;i>=1;i--){
        l[i]=lower_bound(hsh+1,hsh+1+hc,l[i])-hsh,r[i]=lower_bound(hsh+1,hsh+1+hc,r[i])-hsh;
        while(cnt-Tr.Q(1,l[i]-1)-Tl.Q(r[i]+1,hc))Tl.add(l[j],-1),Tr.add(r[j],-1),cnt--,j--;
        Tl.add(l[i],1),Tr.add(r[i],1),cnt++,pos[i]=j;
        lt[i][0]=pos[i]+1;rep(j,1,18)lt[i][j]=lt[lt[i][j-1]][j-1];
    }
    scanf("%d",&q);
    rep(_,1,q){
        int l,r,ans=1;
        scanf("%d %d",&l,&r);
        per(j,18,0)if(lt[l][j]&&lt[l][j]<=r)ans+=1<<j,l=lt[l][j];
        printf("%d\n",ans);
    }
}
void main(){
	// ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int T=1,csid=0;
	// scanf("%d",&csid);
	// scanf("%d",&T);
	rep(i,1,T)slv(csid,i);
}
}
int main(){
	string __name="";
	if(__name!=""){
		freopen((__name+".in").c_str(),"r",stdin);
		freopen((__name+".out").c_str(),"w",stdout);
	}
	ax_by_c::main();
	return 0;
}
/*
g++ -std=c++14 -O2 -Wall -Wextra "-Wl,--stack=200000000" A.cpp -o A.exe
A.exe
*/
```

水题题解往往不适合初学者阅读。/ll

---

## 作者：freoepn (赞：0)

发现当且仅当区间中每一个嫌疑人都被调查过才能判断出嫌疑人情况，考虑如何用最少合法调查覆盖整个区间，显然从左到右把尽可能多的嫌疑人合并进调查一定最优，离散化一下再用线段树维护出在嫌疑人 $i$ 往后第一个碰到的与 $i$ 矛盾的嫌疑人，模拟一下即可得到 $i$ 最多能往后覆盖到那个位置，把询问离线后从后往前 dfs 即可。


```cpp
#include <bits/stdc++.h>
using namespace std;
const int kMaxN = 4e5 + 5;
int tr[4 * kMaxN], tag[4 * kMaxN];
void build(int x, int l, int r) {
  tag[x] = 1e9;
  if (l == r) {
    tr[x] = 1e9;
    return;
  }
  int mid = (l + r) / 2;
  build(x << 1, l, mid);
  build(x << 1 | 1, mid + 1, r);
  tr[x] = min(tr[x << 1], tr[x << 1 | 1]);
}
void change(int x, int l, int r, int ql, int qr, int p) {
  //cout <<x  << " " << l << " " << r << " "<< ql << " "<< qr << endl;
  if (ql <= l && r <= qr) {
    tag[x] = min(tag[x], p);
    tr[x] = min(tr[x], p);
    return;
  }
  int mid = (l + r) / 2;
  tag[x * 2] = min(tag[x], tag[x * 2]);
  tag[x * 2 + 1] = min(tag[x], tag[x * 2 + 1]);
  tr[x << 1] = min(tr[x * 2], tag[x * 2]);
  tr[x * 2 + 1] = min(tr[x * 2 + 1], tag[x * 2 + 1]);
  tag[x] = 1e9;
  if (ql <= mid) {
    change(x << 1, l, mid, ql, qr, p);
  }
  if (qr > mid) {
    change(x << 1 | 1, mid + 1, r, ql, qr, p);
  }
  tr[x] = min(tr[x << 1], tr[x << 1 | 1]);
}
int query(int x, int l, int r, int ql, int qr) {
 // cout <<x  << " " << l << " " << r << " "<< ql << " "<< qr << endl;
  if (ql <= l && r <= qr) {
    return tr[x];
  }
  int mid = (l + r) / 2;
  tag[x * 2] = min(tag[x], tag[x * 2]);
  tag[x * 2 + 1] = min(tag[x], tag[x * 2 + 1]);
  tr[x << 1] = min(tr[x * 2], tag[x * 2]);
  tr[x * 2 + 1] = min(tr[x * 2 + 1], tag[x * 2 + 1]);
  tag[x] = 1e9;
  int sum = 1e9;
  if (ql <= mid) {
    sum = min(sum, query(x << 1, l, mid, ql, qr));
  }
  if (qr > mid) {
    sum = min(sum, query(x << 1 | 1, mid + 1, r, ql, qr));
  }
  return sum;
}
int p[kMaxN];
pair<int, int> a[kMaxN];
vector<int> vv[kMaxN];
bool u[kMaxN];
vector<int> ans;
vector<pair<int, int> > qu[kMaxN];
int sum[kMaxN];
void dfs(int x) {
  u[x] = 1;
  int e;
  int siz = ans.size();
  siz--;
 //cout << x << ":\n";
 //for(int i = 0;i < ans.size();i++){
 //  cout << ans[i] << " ";
 //}
  //cout << "\n";
  for (int i = 0; i < qu[x].size(); i++) {
    e = qu[x][i].first;
    int l = 0, r = siz;
   // cout << i << " "<< e << "ss\n";
    while (l <= r) {
      int mid = (l + r) / 2;
      //cout << l << " "<< r << " "<< ans[mid]<< endl;
      if (ans[mid] > e) {
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    //cout << l-1 <<"LLDL\n";
    sum[qu[x][i].second] = siz-(l-1)+1;
  }
  ans.push_back(x);
  for (int i = 0; i < vv[x].size(); i++) {
    dfs(vv[x][i]);
  }
  ans.pop_back();
}
signed main() {
  freopen("sus.in","r",stdin);
  freopen("sus.out","w",stdout);
   ios::sync_with_stdio(0);
   cin.tie(0), cout.tie(0);
  int n;
  cin >> n;
  build(1, 1, 2 * n);
  map<int, int> m;
  vector<int> v;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].first >> a[i].second;
    v.push_back(a[i].first);
    v.push_back(a[i].second);
  }
  sort(v.begin(), v.end());
  int tot = 0;
  for (int i = 0; i < v.size(); i++) {
    if (m[v[i]] == 0) {
      m[v[i]] = ++tot;
    }
    //cout << i << endl;
  }
  for (int i = 1; i <= n; i++) {
    a[i].first = m[a[i].first], a[i].second = m[a[i].second];
    //cout << i << endl;
  }
  p[n+1]=n+1;
  for (int i = n; i >= 1; i--) {
  //  cout << a[i].first << " "<< a[i].second << endl;;
    p[i] = query(1, 1, 2*n, a[i].first, a[i].second);
    change(1, 1, 2*n, a[i].first, a[i].second, i);
    p[i] = min(p[i+1],p[i]);
    if (p[i] <= n) {
      vv[p[i]].push_back(i);
    }
   // cout << i << " ss "<< p[i]<< endl;
  }
  int q;
  cin >> q;
  for (int i = 1; i <= q; i++) {
   // cout << i << endl;
    int l, r;
    cin >> l >> r;
    qu[l].push_back(make_pair(r, i));
  }
  for (int i = n; i >= 1; i--) {
    if (u[i] == 0) {
      ans.push_back(n + 1);
      dfs(i);
      ans.pop_back();
    }
  }
  for(int i = 1;i <= q;i++){
    cout << sum[i] << '\n';
  }
  return 0;
}
```

---

## 作者：_lfxxx_ (赞：0)

### 思路：

首先考虑一次询问暴力怎么做，显然是从左往右扫尝试加入线段，与之前没有交集就就可以加入，如果不可以就清空然后计数器累加（注意计数器初值为 $1$）。

注意到这个过程可以倍增优化，因此我们只要对于每个位置合法的最远位置的下一个位置就好了（下一个位置是因为你当前的合法位置能跳到，$1$ 次是可以解决这一部分的）。

可以发现最远位置是有单调性的（感性理解就是线段越多越容易有交集），可以双指针维护。至于线段覆盖和查询有没有交集，用树状数组区间加区间查就好了，比线段树好写多了，直接最优解了。

### 代码：

记得离散化，离散化数组和树状数组要开两倍空间。

```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int N = 2e5 + 5;
int n, p[N], q[N], t1[N * 2], t2[N * 2], f[N][18], tmp[N * 2], cnt;
inline void add(int u, int v)
{
	for (int i = u; i <= cnt; i += i & -i) {
		t1[i] += v, t2[i] += v * (u - 1);
	}
}
void add(int l, int r, int v)
{
	add(l, v), add(r + 1, -v);
}
inline int query(int u)
{
	int res = 0;
	for (int i = u; i; i -= i & -i) {
		res += t1[i] * u - t2[i];
	}
	return res;
}
int query(int l, int r)
{
	return query(r) - query(l - 1);
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int m;
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> p[i] >> q[i];
		tmp[++cnt] = p[i], tmp[++cnt] = q[i];
	}
	sort(tmp + 1, tmp + 1 + cnt), cnt = unique(tmp + 1, tmp + 1 + cnt) - tmp - 1;
	for (int i = 1; i <= n; ++i) {
		p[i] = lower_bound(tmp + 1, tmp + 1 + cnt, p[i]) - tmp;
		q[i] = lower_bound(tmp + 1, tmp + 1 + cnt, q[i]) - tmp;
	}
	for (int i = 1, j = 0; i <= n; ++i) {
		while (j + 1 <= n && query(p[j + 1], q[j + 1]) == 0) 
			++j, add(p[j], q[j], 1);
		f[i][0] = j + 1;
		add(p[i], q[i], -1);
	}
	for (int j = 1; j <= 17; ++j) {
		for (int i = 1; i <= n; ++i) {
			f[i][j] = f[i][j - 1] ? f[f[i][j - 1]][j - 1] : 0;
		}
	}
	cin >> m;
	while (m--) {
		int l, r, ans = 0;
		cin >> l >> r;
		for (int i = 17; i >= 0; --i) {
			if (f[l][i] && f[l][i] <= r) {
				l = f[l][i];
				ans |= 1 << i;
			}
		}
		cout << ans + 1 << '\n';
	}
	return 0;
}
```

---

## 作者：Phobia (赞：0)

注意到最优策略下每次调查嫌疑人的区间一定是极大且两两不相交的，所以考虑维护对于以第 $i$ 个人为右边界左边界最远能到哪里。

不妨将嫌疑人身高离散化后塞进一颗线段树里，第 $i$ 个人的左边界就是第 $i-1$ 个人的左边界和与第 $i$ 个人身高相交编号最大的那家伙两者里取大的，正着刷一趟后倍增覆盖即可。

时间复杂度 $O\left(n\log n\right)$。

```cpp

#include <bits/stdc++.h>

using namespace std;

const int maxn = 200005, maxlogn = 18;

int n, m;

int L[maxn], R[maxn], num[maxn * 2], tot;

int f[maxn][maxlogn];

int maxv[maxn * 8], tag[maxn * 8];

int read()
{
    int ret = 0, ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        ;
    for (; isdigit(ch); ch = getchar())
        ret = (ret << 3) + (ret << 1) + (ch & 15);
    return ret;
}

void push_down(int root)
{
    if (tag[root])
    {
        maxv[root << 1] = max(maxv[root << 1], tag[root]);
        tag[root << 1] = max(tag[root << 1], tag[root]);

        maxv[root << 1 | 1] = max(maxv[root << 1 | 1], tag[root]);
        tag[root << 1 | 1] = max(tag[root << 1 | 1], tag[root]);

        tag[root] = 0;
    }
}

void modify(int root, int l, int r, int x, int y, int v)
{
    if (x <= l && r <= y)
    {
        maxv[root] = max(maxv[root], v);
        tag[root] = max(tag[root], v);
        return;
    }
    int mid = l + r >> 1;
    push_down(root);
    if (x <= mid)
        modify(root << 1, l, mid, x, y, v);
    if (mid < y)
        modify(root << 1 | 1, mid + 1, r, x, y, v);
    maxv[root] = max(maxv[root << 1], maxv[root << 1 | 1]);
}

int query(int root, int l, int r, int x, int y)
{
    if (l > y || r < x)
        return 0;
    if (x <= l && r <= y)
        return maxv[root];
    int mid = l + r >> 1;
    push_down(root);
    return max(query(root << 1, l, mid, x, y), query(root << 1 | 1, mid + 1, r, x, y));
}

int main()
{
    n = read();
    for (int i = 1; i <= n; ++i)
    {
        L[i] = num[++tot] = read();
        R[i] = num[++tot] = read();
    }
    sort(num + 1, num + tot + 1);
    tot = unique(num + 1, num + tot + 1) - num - 1;
    for (int i = 1; i <= n; ++i)
    {
        L[i] = lower_bound(num + 1, num + tot + 1, L[i]) - num;
        R[i] = lower_bound(num + 1, num + tot + 1, R[i]) - num;
        f[i][0] = max(f[i - 1][0], query(1, 1, tot, L[i], R[i]));
        modify(1, 1, tot, L[i], R[i], i);
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= 17; ++j)
            f[i][j] = f[f[i][j - 1]][j - 1];
    }
    m = read();
    while (m--)
    {
        int l = read(), r = read(), ans = 0;
        for (int i = 17; i >= 0; --i)
        {
            if (f[r][i] >= l)
            {
                r = f[r][i];
                ans |= 1 << i;
            }
        }
        printf("%d\n", ans + 1);
    }
    return 0;
}
```

---

## 作者：Tsawke (赞：0)

# COCI2021-2022 Contest1 T5题解

[TOC]

## [更好的阅读体验戳此进入](http://blog.monkey-hyx.tech?t=COCI-2021-2022-Contest2)

（建议您从上方链接进入我的个人网站查看此 Blog，在 Luogu 中图片会被墙掉，部分 Markdown 也会失效）

## [原题面链接](https://hsin.hr/coci/contest2_tasks.pdf)

## [Luogu题面](https://www.luogu.com.cn/problem/list?keyword=COCI2021-2022%232&page=1)

## T5 Osumnjičeni

### 题意

有 $ n $ 个区间，编号为 $ 1, 2, \cdots, n $，每次操作可以标记连续一段编号的区间，要求其中的区间互不相交。$ q $ 组询问，每次给出一个编号的区间，求出标记这个编号区间内所有区间至少需要多少次。

### Solution

首先有一个很显然的贪心，即当我们某一次标记的区间 $ \left[ l, r \right] $ 的 $ l $ 确定之后，为了标记次数尽量少，我们一定要在合法的情况下尽量让标记区间更大，即 $ r $ 更大，所以我们自然可以对于 $ n $ 个区间维护出每一个 $ l $ 对应的最大的 $ r $，考虑使用数据结构：

权值线段树 + 单调队列。

不难想到，用单调队列的思想存身高区间，用权值线段树维护，在当前单调队列中所有身高区间值域中，如果插入新的身高区间，会有哪些身高区间因有区间相交而不合法。以此即可 $ O(n \log n) $ 处理出每一个 $ l $ 对应的最大 $ r $。

并且此时我们发现值域过大，并且值域具体的数并不重要，只需要考虑大小关系，所以考虑进行离散化。

于是此时我们便可以发现问题转化为了区间覆盖问题，即[CF1175E Minimal Segment Cover](https://www.luogu.com.cn/problem/CF1175E)。

也就是我们现在有 $ n $ 段 $ \left[ l, r \right] $，要求出覆盖 $ \left[l', r'\right] $ 至少需要多少段区间。

这里有一个细节需要注意，在我们当前的算法中可能 $ l = r $，而区间覆盖中是不允许的，所以我们可以考虑把区间改为 $ \left( l, r \right] $，即可很直观地解决。

对于区间覆盖显然就是一个 $ O(n \log n) $ 的预处理和 $ O(q \log n) $ 的查询，记录从 $ i $ 点出发用 $ 2^j $ 条线段最远达到的位置，倍增跑一下就好了，具体可以去看模板题的题解，和这题几乎没区别。

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define MAXNQ (210000)

/******************************
abbr
st => Segment Tree
lt => LazyTag
gl/gr => global left/right
ms => Max Section
sec => Section
******************************/

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;

int ms;
int N, Q;

class SegTree{
    private:
        #define LS (p << 1)
        #define RS ((p << 1) + 1)
        #define MID ((gl + gr) >> 1)
        int st[MAXNQ << 3], lt[MAXNQ << 3];
    public:
        void Pushdown(int p, int gl, int gr){
            if(gl == gr)return (void)(lt[p] = 0);
            st[LS] += lt[p], st[RS] += lt[p];
            lt[LS] += lt[p], lt[RS] += lt[p];
            lt[p] = 0;
        }
        void Modify(int l, int r, int val, int p = 1, int gl = 1, int gr = ms){
            // printf("modifying l=%d, r=%d, v=%d, p=%d, gl=%d, gr=%d\n", l, r, val, p, gl, gr);
            if(l <= gl && gr <= r){st[p] += val, lt[p] += val; return;}
            if(lt[p])Pushdown(p, gl, gr);
            if(l <= MID)Modify(l, r, val, LS, gl, MID);
            if(MID + 1 <= r)Modify(l, r, val, RS, MID + 1, gr);
            st[p] = st[LS] + st[RS];
        }
        bool Query(int l, int r, int p = 1, int gl = 1, int gr = ms){
            // printf("querying l=%d, r=%d p=%d, gl=%d, gr=%d\n", l, r, p, gl, gr);
            if(l <= gl && gr <= r)return st[p];
            if(lt[p])Pushdown(p, gl, gr);
            return ((l <= MID) ? Query(l, r, LS, gl, MID) : false ) | ((MID + 1 <= r) ? Query(l, r, RS, MID + 1, gr) : false); 
        }
}st;

template<typename T = int>
inline T read(void);

pair < int, int > sec[MAXNQ];
vector < int > values;
//1e5 < 2^17
int dp[MAXNQ][30];

int main(){
    N = read();
    for(int i = 1; i <= N; ++i){
        int l = read(), r = read();
        sec[i] = make_pair(l, r);
        values.push_back(l), values.push_back(r);
    }
    sort(values.begin(), values.end());
    ms = distance(values.begin(), unique(values.begin(), values.end()));
    for(int i = 1; i <= N; ++i){
        sec[i].first = distance(values.begin(), lower_bound(values.begin(), values.begin() + ms, sec[i].first) + 1);
        sec[i].second = distance(values.begin(), lower_bound(values.begin(), values.begin() + ms, sec[i].second) + 1);
    }
    int cur(1);
    for(int i = 1; i <= N; ++i){
        while(st.Query(sec[i].first, sec[i].second))
            st.Modify(sec[cur].first, sec[cur].second, -1),
            dp[cur - 1][0] = i - 1,
            ++cur;
        st.Modify(sec[i].first, sec[i].second, 1);
    }
    while(cur <= N + 1)dp[cur - 1][0] = N, ++cur;
    for(int j = 1; j <= 17; ++j)
        for(int i = 0; i <= N; ++i)
            dp[i][j] = dp[dp[i][j - 1]][j - 1];
    Q = read();
    while(Q--){
        int l = read() - 1, r = read();
        int ret(0);
        for(int dis = 17; dis >= 0; --dis){
            if(dp[l][dis] < r){
                ret += 1 << dis;
                l = dp[l][dis];
            }
        }
        printf("%d\n", ret + 1);
    }

    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template<typename T>
inline T read(void){
    T ret(0);
    short flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```


## UPD

2022_09_05 完成 T1 - T3 及 T4 一部分

2022_09_06 初稿


---

