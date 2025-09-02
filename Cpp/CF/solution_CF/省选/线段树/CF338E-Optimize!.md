# Optimize!

## 题目描述

Manao is solving a problem with the following statement:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF338E/5342825b0bbcbbc06536e5a019fb46969a4849f8.png)He came up with a solution that produces the correct answers but is too slow. You are given the pseudocode of his solution, where the function getAnswer calculates the answer to the problem:

```
getAnswer(a[1..n], b[1..len], h)
  answer = 0
  for i = 1 to n-len+1
    answer = answer + f(a[i..i+len-1], b, h, 1)
  return answer

f(s[1..len], b[1..len], h, index)
  if index = len+1 then
    return 1
  for i = 1 to len
    if s[index] + b[i] >= h
      mem = b[i]
      b[i] = 0
      res = f(s, b, h, index + 1)
      b[i] = mem
      if res > 0
        return 1
  return 0
```

Your task is to help Manao optimize his algorithm.

## 样例 #1

### 输入

```
5 2 10
5 3
1 8 5 5 7
```

### 输出

```
2
```

# 题解

## 作者：Leap_Frog (赞：11)

### P.S.
**upd on 11.4，修改了一处 typo，然后对所有被我误导的人致歉**

愿每场 div1.E 都能像这题一样 /wq  
虽然很 sb，但是还是吃了两发罚时 /dk  
第一发 $a$ $b$ 搞反，第二发数组开小。。。  
所以 小跳蛙无药可救 /ruo /no  
不吧，这题需要什么 Hall 定理吗？？（  

### Description.
翻译还算比较清楚。  
不过注意匹配不需要按顺序，可以打乱顺序匹配。  

### Solution.
$a_i+b_j\ge H$ 等价于 $a_i\ge H-b_j$。  
那么我们把每个 $b_j\rightarrow H-b_j$。  
那么原题转化为了 $a_i\ge b_j$ 时它们匹配。  
所以显然有一个贪心就是对 $\{b_i\}$ 和 $\{a_i\}$ 排序，  
每次找出最小的元素，如果能匹配就匹配掉，否则就无解。  
每次这样暴力匹配是 $O(len)$ 的，所以总复杂度 $O(len\times(n-len))$ 显然不能通过此题。  
我们考虑在值域上搞事情，首先离散化。  
然后我们在 $b_i$ 处 $+1$ 表示这边多了一个可以被匹配的数。  
然后在 $a_i$ 处 $-1$ 表示这边消耗掉一个被匹配数。  
那么每次能完全匹配的充要条件就是这个值域上有下式成立。  
$$\forall x\in[1,n]\ ,\sum_{i=1}^xw_i\ge0$$  
那么我们直接用线段树维护单点前缀和，区间前缀和的最小值。  
然后查询全局最小值是否 $\ge0$ 即可。  
然后这题就做完了，无耻求赞。  

### Coding.
代码没什么好解释的了（（（
```cpp
//是啊……你就是那只鬼了……所以被你碰到以后，就轮到我变成鬼了
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename t>inline void read(t &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	if(f) x=-x;
}
struct node{int mn,fg;}T[1200005];
int n,m,H,a[150005],b[150005],tn[300005],ut;
inline void allc(int x,int w) {T[x].mn+=w,T[x].fg+=w;}
inline void pushdw(int x) {if(T[x].fg) allc(x<<1,T[x].fg),allc(x<<1|1,T[x].fg),T[x].fg=0;}
inline void pushup(int x) {T[x].mn=min(T[x<<1].mn,T[x<<1|1].mn);}
inline void modif(int x,int l,int r,int dl,int dr,int dw)
{//维护的前缀和，所以单点加变成了区间加
	if(l>dr||dl>r) return;else if(dl<=l&&r<=dr) return allc(x,dw);else pushdw(x);
	modif(x<<1,l,(l+r)>>1,dl,dr,dw),modif(x<<1|1,((l+r)>>1)+1,r,dl,dr,dw),pushup(x);
}
int main()
{
	read(n),read(m),read(H);int cnt=0;
	for(int i=1;i<=m;i++) read(b[i]),b[i]=H-b[i],tn[++ut]=b[i];
	for(int i=1;i<=n;i++) read(a[i]),tn[++ut]=a[i];
	sort(tn+1,tn+ut+1),ut=unique(tn+1,tn+ut+1)-tn-1;
	for(int i=1;i<=m;i++) b[i]=lower_bound(tn+1,tn+ut+1,b[i])-tn;
	for(int i=1;i<=n;i++) a[i]=lower_bound(tn+1,tn+ut+1,a[i])-tn;
	for(int i=1;i<=m;i++) modif(1,1,ut,a[i],ut,-1),modif(1,1,ut,b[i],ut,1);
	cnt+=T[1].mn>=0;for(int i=m+1;i<=n;i++) modif(1,1,ut,a[i-m],ut,1),modif(1,1,ut,a[i],ut,-1),cnt+=T[1].mn>=0;
	return printf("%d\n",cnt),0;
}
```

---

## 作者：Cherished (赞：4)

### 题外话

有一说一这题真的到不了黑题的难度，反正我看完就会做了，写完之后一看题解才发现我的做法好像非常的毒瘤，而且没有人用我的做法。

### 题目解答

~~（超大常数警告）~~

首先显而易见的是，一定是给 ```a``` 数组的连续子序列正着排序，```b``` 数组倒着排序，然后一一配对，这样的解一定是最优的。

我们可以发现一件事情就是，```b``` 数组是不会变的，```a``` 数组每次操作也只会有两个数的变化，那么显然要上数据结构了。

之后又可以发现，对于一个 $a_i$ 可以和它匹配的一定是倒序的 ```b``` 数组的一个前缀，那么我们记录可以和 $a_i$ 匹配的最靠右的位置是 $p_i$，这样的话如果我们把当前的 $a$ 序列的升序排列维护出来，每个点记录一下它离对应的 $p_i$ 的距离也就是 $p_i-a_i$，查询答案的时候就是一个全局最小值是否大于 $0$。

因为有插入和删除两个操作，所以我们用 ```treap``` 维护。

我们记 $p_i-a_i$ 为 $t_i$。

插入操作，显然就是，在当前 ```treap``` 中找到，```a``` 应该插入的位置，然后给应该在它之后的点的 $t$ 全 $-1$。

删除操作，也是给在要删除的点之后的点全 $+1$。

这样我们只需要写一棵支持区间修改的 ```treap``` 就可以了。

时间复杂度的话显然是 $O(N\log{N})$ 的。

### 有关常数

写的时候就发现常数巨大了，插入操作有 $3$ 次 ```Merge,Split```，删除操作有 $5$ 次 ```Merge,Split```。

但是去测了一下发现跑的很快...莫名其妙甚至不比正解的线段树慢多少。

### 代码

```cpp
struct Node {
	int s, Min, lch, rch, t, lzy, k;
	Node() {Min = 0x3f3f3f3f;}
}	o[N]; int cnt = 0, rt = 0;

void PushUp(int x) {
	o[x].Min = min(o[x].t, min(o[o[x].lch].Min, o[o[x].rch].Min));
	o[x].s = o[o[x].lch].s + o[o[x].rch].s + 1;
}

void Update(int x, int y) {
	if (!x) return;
	o[x].Min += y, o[x].t += y, o[x].lzy += y;
}

void PushDown(int x) {
	if (o[x].lzy) {
		Update(o[x].lch, o[x].lzy);
		Update(o[x].rch, o[x].lzy);
		o[x].lzy = 0;
	}
}

int Merge(int x, int y) {
	if (!x || !y) return x + y; PushDown(x), PushDown(y);
	if (rand() % (o[x].s + o[y].s) < o[x].s)
		return o[x].rch = Merge(o[x].rch, y), PushUp(x), x;
	else return o[y].lch = Merge(x, o[y].lch), PushUp(y), y;
}

void Split(int w, int key, int &x, int &y) {
	if (!w) return x = 0, y = 0, void(); PushDown(w);
	if (o[w].k <= key) x = w, Split(o[w].rch, key, o[x].rch, y);
	else y = w, Split(o[w].lch, key, x, o[y].lch); PushUp(w);
}

int n, m, h, a[N], b[N], ans;

void Insert(int x) {
	int sh = lower_bound(b + 1, b + m + 1, h - a[x]) - b;
	sh = m - sh + 1;
	++cnt; o[cnt].k = a[x];
	int d, f; Split(rt, a[x], d, f);
	o[cnt].t = sh - o[d].s - 1;
	Update(f, -1), PushUp(cnt);
	rt = Merge(Merge(d, cnt), f);
}

void Del(int x) {
	int d, f, g;
	Split(rt, a[x] - 1, d, f), Split(f, a[x], f, g);
	Update(o[f].rch, 1), Update(g, 1);
	rt = Merge(Merge(d, Merge(o[f].lch, o[f].rch)), g);
}

int main() {
	scanf("%d%d%d", &n, &m, &h);
	lep (i, 1, m) scanf("%d", &b[i]);
	lep (i, 1, n) scanf("%d", &a[i]);
	sort (b + 1, b + m + 1);
	lep (i, 1, m) Insert(i);
	ans += o[rt].Min >= 0;
	lep (i, m + 1, n) {
		Del(i - m), Insert(i);
		ans += o[rt].Min >= 0;
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：tzc_wk (赞：3)

安利个人 blog：https://www.cnblogs.com/ET2006/

[题面传送门](https://codeforces.ml/contest/338/problem/E)

首先 $b_i$ 的顺序肯定不会影响匹配，故我们可以直接将 $b$ 数组从小到大排个序。

我们考虑分析一下什么样的长度为 $m$ 的数组 $a_1,a_2,\dots,a_m$ 能和 $b$ 数组形成匹配。考虑对于 $i,j\in [1,m]$，若 $a_i+b_j\geq h$，就在 $i,j$ 之间连边，那么形成的图必然是一张二分图，我们只需检验这张二分图是否存在完美匹配即可。

这时候就要用到一个叫做 Hall 定理的科技了。Hall 定理说的是这样一件事，对于二分图 $G=(V_1,V_2,E)$，定义函数 $f(V)(V\in V_1)$ 为与点集 $V$ 中的点相连的点的（右部点）集合。那么二部图 $G$ 有完美匹配的充要条件是 $\forall V\subseteq V_1,|f(V)|\geq |V|$

必要性：这个就比较显然了吧。。。记对于节点 $u$，记 $mch(u)$ 为与 $u$ 匹配的节点。那么我们构造集合 $V'=\{v|v=mch(u),u\in V\}$，那么 $|V'|=|V|$，而根据 $V'$ 的构造方式可知 $\forall v\in V'$ 至少存在一个 $u\in V$ 满足 $u,v$ 间有边，故 $V'\subseteq f(V)$，于是有 $|V|=|V'|\leq f(V)$，得证。

充分性：这个就没那么显然了。考虑反证法，假设二分图 $G$ 不存在完美匹配但满足 Hall 定理。那么我们构造出 $G$ 的一种最大匹配，其中必存在某个非匹配点，假设其为 $A$。根据 Hall 定理 $A$ 必定与另一边某个点相连，设其为 $B$。而 $B$ 必须为匹配点，否则 $A,B$ 就能形成新的匹配，不满足最大匹配的条件了，设 $C$ 为与 $B$ 相匹配的点。再对集合 $\{A,C\}$ 使用 Hall 定理可知，$\{A,C\}$ 除 $B$ 外必与其它某个点相连，设其为 $D$。$D$ 也必须为匹配点，否则根据之前的证明过程可知它不能与 $A$ 相连，否则 $A,D$ 能形成新的匹配，故它只能与 $C$ 相连，而若它与 $C$ 相连，那么将匹配边 $(B,C)$ 换为 $(A,B),(C,D)$ 可让匹配个数多 $1$，不满足最大匹配的条件，故 $D$ 一定与某个点 $E$ 匹配。再对集合 $\{A,C,E\}$ 使用 Hall 定理可得还存在某个点 $F$ 与这三个点都相连且为匹配点。如此一直进行下去可进行无限轮，而点集的大小是有限的，矛盾！

回到本题来，设 $c(j)$ 为排好序后与 $b_j$ 能匹配的 $a_i$ 的个数。由于我们 $b$ 数组是有序的，那么就有 $\forall i<j,c(i)<c(j)$，也就是说对于 $i<j$，所有能与 $b_i$ 匹配的 $a_k$ 都能和 $b_j$ 匹配。而根据 Hall 定理，原图存在完美匹配的充要条件是 $\forall V\subseteq V_1,|f(V)|\geq |V|$，故对于大小为 $k$ 的集合 $S=\{b_{i_1},b_{i_2},\dots,b_{i_s}\}$ 必有 $\max(f(i_1),f(i_2),\dots,f_(i_s))\geq k$，而显然所有这样的集合中 $\max(f(i_1),f(i_2),\dots,f_(i_s))$ 的最小值为 $f(k)$。故连边形成的图存在完美匹配等价于 $\forall i,f(i)\geq i$。

最后考虑加上 $a$ 数组之后怎样处理，考虑建一棵线段树维护 $f(i)$。显然对于每个 $a_i$ 可找出二分最小的满足 $b_j\geq h-a_i$ 的 $j$ 并在线段树 $[j,m]$ 的位置整体加 $1$。那么怎么知道 $\forall i,f(i)\geq i$ 是否成立呢？我们就初始在线段树上每个位置赋上 $-1$ 并检查全局最小值是否 $\geq 0$ 就行了。

时间复杂度线对。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
template<typename T> void read(T &x){
	x=0;char c=getchar();T neg=1;
	while(!isdigit(c)){if(c=='-') neg=-1;c=getchar();}
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	x*=neg;
}
const int MAXN=1.5e5;
const int INF=0x3f3f3f3f;
int n,m,k,a[MAXN+5],b[MAXN+5],pos[MAXN+5];
struct node{int l,r,mn,lz;} s[MAXN*4+5];
void build(int k,int l,int r){
	s[k].l=l;s[k].r=r;if(l==r){s[k].mn=-l;return;}
	int mid=(l+r)>>1;build(k<<1,l,mid);build(k<<1|1,mid+1,r);
	s[k].mn=min(s[k<<1].mn,s[k<<1|1].mn);
}
void pushdown(int k){
	if(s[k].lz!=0){
		s[k<<1].mn+=s[k].lz;s[k<<1].lz+=s[k].lz;
		s[k<<1|1].mn+=s[k].lz;s[k<<1|1].lz+=s[k].lz;
		s[k].lz=0;
	}
}
void modify(int k,int l,int r,int x){
	if(l>r) return;
	if(l<=s[k].l&&s[k].r<=r){s[k].mn+=x;s[k].lz+=x;return;}
	pushdown(k);int mid=(s[k].l+s[k].r)>>1;
	if(r<=mid) modify(k<<1,l,r,x);
	else if(l>mid) modify(k<<1|1,l,r,x);
	else modify(k<<1,l,mid,x),modify(k<<1|1,mid+1,r,x);
	s[k].mn=min(s[k<<1].mn,s[k<<1|1].mn);
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;i++) scanf("%d",&a[i]);
	a[0]=-INF;sort(a+1,a+m+1);build(1,1,m);
	for(int i=1;i<=n;i++){
		scanf("%d",&b[i]);
		pos[i]=lower_bound(a,a+m+1,k-b[i])-a;
//		printf("%d\n",pos[i]);
	}
	for(int i=1;i<m;i++) modify(1,pos[i],m,1);
	int ans=0;
	for(int i=m;i<=n;i++){
		modify(1,pos[i],m,1);
//		printf("%d\n",s[1].mn);
		if(s[1].mn>=0) ans++;
		modify(1,pos[i-m+1],m,-1);
	} printf("%d\n",ans);
	return 0;
}
```



---

## 作者：Ac2hxp2 (赞：2)

一种不基于值域的做法，不知道和 hall 定理有啥关系。

我们需要 $A_i+B_i\ge H\Rightarrow A_i\ge H-B_i$，把所有的 $B_i\leftarrow H-B_i$，直接就转化为判断对于每一个长度为 $len$ 的 $A$ 的连续子序列里面排两者都排序之后是不是 $\forall i\in [1,M],A_i\ge B_i$。

考虑把 $B$ 排序，二分出 $A$ 的合法区间，相当于我们需要实时判断 $\forall i\in [1, N], pre_i \le i$，对于 $pre_i$ 的修改是单点的。

发现这个东西没那么好维护，因为是单点的修改，所以把每一个点的贡献覆盖上去（区间 $+1$）就可以了（其实这里区间覆盖也是可以的，就是序列上覆盖一段然后另一段加等差数列），我们只需要维护区间 add，全局 min 的线段树即可。

```cpp
#include <bits/stdc++.h>
#define lb(x) (x&-x)
#define L(i,j,k) for(int i=(j);i<=(k);++i)
#define R(i,j,k) for(int i=(j);i>=(k);--i)

using namespace std;
using i64 = long long;

typedef pair<int, int> pii;
typedef long long ll;
typedef unsigned long long ull;
void chmin(int &x, int c) {x = min(x, c);}
void chmax(int &x, int c) {x = max(x, c);}

const int maxn = 15e4 + 10, mod = 998244353;
int N, M, K;
int A[maxn], B[maxn], pos[maxn];
namespace segt {
int mn[maxn << 1], tag[maxn << 1];
void pushdown (int u) {
	if (tag[u]) {
		mn[u << 1] += tag[u]; tag[u << 1] += tag[u];
		mn[u << 1 | 1] += tag[u]; tag[u << 1 | 1] += tag[u];
		tag[u] = 0;
	}
}
void pushup (int u) {
	mn[u] = min (mn[u << 1], mn[u << 1 | 1]);
}
void build (int u, int l, int r) {
	if (l == r) {
		mn[u] = -(M - l + 1); tag[u] = 0; return;
	}
	int mid = (l + r) >> 1;
	build (u << 1, l, mid), build (u << 1 | 1, mid + 1, r), pushup (u); 
}
void upd (int u, int l, int r, int ql, int qr, int x) {
	if (ql > qr) return;
	if (ql <= l && qr >= r) {
		mn[u] += x; tag[u] += x;
		return;
	}
	int mid = (l + r) >> 1;
	pushdown (u);
	if (ql <= mid) upd (u << 1, l, mid, ql, qr, x);
	if (qr > mid) upd (u << 1 | 1, mid + 1, r, ql, qr, x);
	pushup (u); 
}
}

void solve() {
	cin >> N >> M >> K;
	L (i, 1, M) cin >> B[i], B[i] = K - B[i];
	L (i, 1, N) cin >> A[i];
	sort (B + 1, B + 1 + M);
	L (i, 1, N) {
		int l = 0, r = M, res = 0;
		while (l <= r) {
			int mid = (l + r) >> 1;
			(A[i] >= B[mid] ? res = mid, l = mid + 1 : r = mid - 1);
		}
		pos[i] = res;
	}
	segt::build (1, 1, M);
	int res = 0;
	L (i, 1, N) {
		segt::upd (1, 1, M, 1, pos[i], 1);
		if (i >= M) {
			res += segt::mn[1] >= 0;
			segt::upd (1, 1, M, 1, pos[i - M + 1], -1);
		}
	}
	cout << res << '\n';
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T = 1;
  while (T--)solve();
  return 0;
}
```

---

## 作者：naive_wcx (赞：2)

# Description
给你一段伪代码，要求解决伪代码正在解决的问题。

伪代码如下：
```cpp
getAnswer(a[1..n], b[1..len], h)
  answer = 0
  for i = 1 to n-len+1
    answer = answer + f(a[i..i+len-1], b, h, 1)
  return answer

f(s[1..len], b[1..len], h, index)
  if index = len+1 then
    return 1
  for i = 1 to len
    if s[index] + b[i] >= h
      mem = b[i]
      b[i] = 0
      res = f(s, b, h, index + 1)
      b[i] = mem
      if res > 0
        return 1
  return 0
```
# Solution
伪代码的意思是给你一个长度为$n(n≤150000)$的序列$A$和长度为$len(len≤n)$的序列$B$，问对于$A$中长度为$len$的子串和$B$中的元素任意匹配，要求每一对的和$≥h$，问有多少这样的子串。

定义$A$中的子串为$S$，可以意识到匹配一定是将$S$中最大的和$B$中最小的匹配，$S$中次大的和$B$中次小的匹配，以此类推，证明过程略。

问题可以转化为，对于$B$中最大的，$S$中至少有$len$个元素与其匹配。对于$B$中次大的，$S$中至少有$len-1$个元素与其匹配，以此类推。

那么我们对$B$进行排序，对于$S$中的每一个元素，用二分找到第一个与其相加$≥h$的元素并记录下标。

问题变成了区间覆盖，询问$B$中第$i$大的元素是否至少被覆盖了$i$次。

用线段树维护即可。

时间复杂度$O(n×log_2{n})$
# Code
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define ls(x) x<<1
#define rs(x) x<<1|1
using namespace std;
const int inf = 1e9 + 7, maxn = 150010;
int n, len, h, tree[maxn << 2], tag[maxn << 2], a[maxn], b[maxn];

void push_down(int p, int l, int r) {
    tag[ls(p)] += tag[p];
    tag[rs(p)] += tag[p];
    tag[p] = 0;
}

void update(int p, int l, int r, int ql, int qr, int k) {
    if(ql <= l && r <= qr) {
        tag[p] += k;
        return;
    }
    if(tag[p]) push_down(p, l, r);
    int mid = (l + r) >> 1;
    if(ql <= mid) update(ls(p), l, mid, ql, qr, k);
    if(qr > mid) update(rs(p), mid + 1, r, ql, qr, k);
    tree[p] = min(tree[ls(p)] + tag[ls(p)], tree[rs(p)] + tag[rs(p)]);
}

int main()
{
    scanf("%d %d %d", &n, &len, &h);
    for(int i = 1; i <= len; i++) scanf("%d", &b[i]);
    sort(b + 1, b + 1 + len);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        a[i] = lower_bound(b + 1, b + 1 + len, h - a[i]) - b;
    }
    for(int i = 1; i <= len; i++) update(1, 1, len, i, i, -i);
    for(int i = 1; i < len; i++) update(1, 1, len, a[i], len, 1);
    int ans = 0;
    for(int i = len; i <= n; i++) {
        update(1, 1, len, a[i], len, 1);
        if(tree[1] + tag[1] >= 0) ans++;
        update(1, 1, len, a[i - len + 1], len, -1);
    }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：ifffer_2137 (赞：1)

远古 \*2600，所以是一眼题喵。
### 题意
给定一个长度为 $n$ 的序列 $a$ 和一个长度为 $k$ 的序列 $b$。求 $a$ 有多少长度为 $k$ 的连续区间和 $b$ 完美匹配。两个序列完美匹配当且仅当存在一种各自打乱顺序的方案使得两个序列对应位置上的数的和都不小于 $m$。
### 分析
显然判断两个序列完美匹配直接一个升序排一个降序排对应位置 check 一下就行了。证明的话，可以稍微胡一下：
*******
假设在一种完美匹配中，存在 $a_i+b_i\geq m$，$a_j+b_j\geq m$ 且 $a_i<a_j$，$b_i<b_j$，交换 $b_i$ 和 $b_j$ 后对应位置变成 $a_i+b_j$，$a_j+b_i$，由于：
$$a_i+b_j\geq a_i+b_i\geq m，a_j+b_i\geq a_i+b_i\geq m$$
所以我们交换一定不劣。因此对于所有匹配我们可以规定 $a_i<a_j$，$b_i>b_j$。
*******
因为 $b$ 不会变，所以接下来我们考虑先对 $b$ 排序，我们就知道对于 $a$ 的某个子段，它排序后每个位置至少要多少。我们只关心 $a$ 的子段排序以后与每一位目标值的大小关系，所以把 $a_i$ 和 $m-b_i$ 扔一起一起离散化一下。你发现在数轴上把 $a_i$ 的位置 $+1$，$m-b_i$ 的位置 $-1$，所有后缀和 $\geq 0$ 就充要了。于是你拿个 sgt 维护区间和以及区间最小后缀和，扫一遍 $a_i$ 每次加一个数删一个数，修改完判一下全局最小后缀和是否 $\geq 0$ 即可，时间复杂度 $O(n\log n)$。
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define pdd pair<double,double>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=1.5e5+5;
int n,k,m,ans;
int a[maxn],b[maxn];
int t[maxn*2],tot;
class Segment_Tree{
public:
	pii tr[maxn*8];
	pii pushup(pii x,pii y){
		pii z;
		z.fir=x.fir+y.fir;
		z.sec=min(y.sec,x.sec+y.fir);
		return z;
	}
	void update(int o,int l,int r,int x,int k){
		if(l==r){
			tr[o].fir+=k;
			tr[o].sec+=k;
			return;
		}
		int m=(l+r)>>1;
		if(x<=m) update(o*2,l,m,x,k);
		else update(o*2+1,m+1,r,x,k);
		tr[o]=pushup(tr[o*2],tr[o*2+1]);
	}
}seg;
signed main(){
	cin.tie(0),cout.tie(0);
	n=read(),k=read(),m=read();
	for(int i=1;i<=k;i++) b[i]=m-read(),t[++tot]=b[i];
	for(int i=1;i<=n;i++) a[i]=read(),t[++tot]=a[i];
	sort(t+1,t+tot+1);tot=unique(t+1,t+tot+1)-t-1;
	for(int i=1;i<=k;i++) b[i]=lower_bound(t+1,t+tot+1,b[i])-t;
	for(int i=1;i<=n;i++) a[i]=lower_bound(t+1,t+tot+1,a[i])-t;
	for(int i=1;i<=k;i++) seg.update(1,1,tot,b[i],-1),seg.update(1,1,tot,a[i],1);
	if(seg.tr[1].sec>=0) ans++;
	for(int i=k+1;i<=n;i++){
		seg.update(1,1,tot,a[i-k],-1);
		seg.update(1,1,tot,a[i],1);
		if(seg.tr[1].sec>=0) ans++;
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：1)

考虑如何转化 $a_i+b_i\geq h$。等价于 $a_i\geq h-b_i$，故先令 $b_i=h-b_i$。

于是问题转化为有多少区间满足存在一种排列使得 $a_i\geq b_i$。

不难发现可以先对 $b_i$ 从小到大排序。

于是问题转化为有多少区间满足 $a_j\geq b_i$ 的 $j$ 数量大于等于 $len-i+1$。

不难发现对于每个 $a_j$ 他所能大于等于的 $b_i$ 为一段前缀。

考虑枚举每个区间，线段树维护对于每个 $b_i$，$a_j\geq b_i$ 的数量 $c_i$。问题转化为是否对于所有 $i$ 均满足 $c_i\geq len-i+1$。

在 $c_i$ 的初值上减去 $len-i+1$，线段树求 $\min$ 是否为 $0$ 即可。复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1) 
#pragma GCC optimize(2,3,"Ofast","inline")
using namespace std;
struct sgt{
	int f[1000005],lzt[1000005];
	void pushdown(int i){
		f[i*2]+=lzt[i];
		f[i*2+1]+=lzt[i];
		lzt[i*2]+=lzt[i];
		lzt[i*2+1]+=lzt[i];
		lzt[i]=0;
	}
	void change(int i,int l,int r,int ql,int qr,int cg){
		if(ql<=l&&r<=qr){
			f[i]+=cg;
			lzt[i]+=cg;
			return ;
		}
		pushdown(i);
		if(ql<=mid) change(i*2,l,mid,ql,qr,cg);
		if(qr>mid) change(i*2+1,mid+1,r,ql,qr,cg);
		f[i]=min(f[i*2],f[i*2+1]);
	}
}tree;
signed main(){
	int n,m,h; cin>>n>>m>>h;
	int a[n+1],b[m+1],ans=0;
	for(int i=1;i<=m;i++) cin>>b[i],b[i]=h-b[i];
	sort(b+1,b+m+1);
	for(int i=1;i<=n;i++) cin>>a[i],a[i]=upper_bound(b+1,b+m+1,a[i])-b-1;
	for(int i=1;i<=m;i++) tree.change(1,1,m,i,i,i-m-1);
	for(int i=1;i<m;i++) if(a[i]) tree.change(1,1,m,1,a[i],1);
	for(int i=m;i<=n;i++){
		if(a[i]) tree.change(1,1,m,1,a[i],1);
		if(tree.f[1]>=0) ans++; 
		if(a[i-m+1]) tree.change(1,1,m,1,a[i-m+1],-1);
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：orz_z (赞：1)

### CF338E Optimize!

任意匹配，考虑将 $B$ 排序，$B$ 中最大的与 $A$ 中最小的匹配，$B$ 中次大的与 $A$ 中次小的匹配，依次类推。

若满足条件，等价于 $B$ 中最大的至少可以与 $A$ 中 $len$ 个可以匹配，$B$ 中次大的至少可以与 $A$ 中 $len-1$ 个匹配，依次类推。

考虑线段树套扫描线维护，加删数时维护区间加减一，全局询问最小值。

时间复杂度 $\mathcal O(n\log n)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

#define ha putchar(' ')
#define he putchar('\n')

inline int read() {
	int x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')
			f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
		x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return x * f;
}

inline void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)
		write(x / 10);
	putchar(x % 10 + 48);
}

const int _ = 2e5 + 10;

int n, len, h, a[_], b[_], tr[_ << 2], tag[_ << 2];

void pushdown(int o)
{
	tr[o << 1] += tag[o];
	tr[o << 1 | 1] += tag[o];
	tag[o << 1] += tag[o];
	tag[o << 1 | 1] += tag[o];
	tag[o] = 0;
}

void upd(int o, int l, int r, int L, int R, int v)
{
	if(L <= l && r <= R)
	{
		tr[o] += v, tag[o] += v;
		return;
	}
	pushdown(o);
	int mid = (l + r) >> 1;
	if(L <= mid) upd(o << 1, l, mid, L, R, v);
	if(R > mid) upd(o << 1 | 1, mid + 1, r, L, R, v);
	tr[o] = min(tr[o << 1], tr[o << 1 | 1]);
}

signed main() {
	n = read(), len = read(), h = read();
	for (int i = 1; i <= len; ++i) b[i] = read();
	sort(b + 1, b + len + 1);
	for (int i = 1; i <= n; ++i) {
		a[i] = read();
		a[i] = lower_bound(b + 1, b + len + 1, h - a[i]) - b;
	}
	for (int i = 1; i <= len; i++) upd(1, 1, len, i, i, -i);
	for (int i = 1; i < len; i++) upd(1, 1, len, a[i], len, 1);
	int ans = 0;
	for (int i = len; i <= n; i++) {
		upd(1, 1, len, a[i], len, 1);
		if (tr[1] >= 0) ans++;
		upd(1, 1, len, a[i - len + 1], len, -1);
	}
	write(ans), he;
	return 0;
}
```





---

## 作者：SFlyer (赞：0)

萌萌 ds 题。

首先“打乱”的顺序一定是一个顺序一个倒序。那么我们先钦定 $b$ 是顺序的。那么对于一个 $a_i$，可以和他组队的 $b_j$ 是一个区间。

考虑到 Hall 定理，因为这个相当于一个二分图匹配。发现合法当且仅当有至少一个可以匹配 $b_1$，至少两个可以匹配 $b_2$，等等。因此我们初始线段树上面的值是 $-1,-2,\cdots, -m$，然后相当于维护区间加/减 $1$，合法的区间是全局 $\min\ge 0$ 的。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 1.5e5+5;

ll n,m,h;
ll a[N],b[N];
ll mn[N<<2],tag[N<<2];

void pu(int k){
	mn[k]=min(mn[k<<1],mn[k<<1|1]);
}

void pd(int k){
	if (tag[k]){
		mn[k<<1]+=tag[k];
		mn[k<<1|1]+=tag[k];
		tag[k<<1]+=tag[k];
		tag[k<<1|1]+=tag[k];
		tag[k]=0;
	}
}

void bd(int k,int l,int r){
	if (l==r){
		mn[k]=-l;
		return;
	}
	int mid=l+r>>1;
	bd(k<<1,l,mid);
	bd(k<<1|1,mid+1,r);
	pu(k);
}

void upd(int k,int l,int r,int ql,int qr,int v){
	if (ql>qr) return;
	if (ql<=l && r<=qr){
		mn[k]+=v;
		tag[k]+=v;
		return;
	} 
	if (r<ql || l>qr) return;
	pd(k);
	int mid=l+r>>1;
	upd(k<<1,l,mid,ql,qr,v);
	upd(k<<1|1,mid+1,r,ql,qr,v);
	pu(k);
}

ll fd(ll x){
	int p=lower_bound(b+1,b+1+m,h-x)-b;
	if (!p) p++;
	return p;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin>>n>>m>>h;
	for (int i=1; i<=m; i++) cin>>b[i];
	sort(b+1,b+1+m);
	for (int i=1; i<=n; i++) cin>>a[i];
	bd(1,1,m);
	for (int i=1; i<=m; i++){
		upd(1,1,m,fd(a[i]),m,1);
	}
	ll ans=(mn[1]>=0);
	for (int i=1; i<=n-m; i++){
		upd(1,1,m,fd(a[i]),m,-1);
		upd(1,1,m,fd(a[i+m]),m,1);
		ans+=(mn[1]>=0);
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：Hoks (赞：0)

## 前言
好像不是很难，感觉是有点套路的，可能 CF 里的 DS 的确评分都给的较高。

摘自 [杂题选做](https://www.luogu.com.cn/training/518105)。
## 思路分析
其实看到的第一眼感觉就好像很水？

动态的东西肯定是要一路推过去用 DS 来维护了，那就来构建条件吧。

比较感性的思路是直接最小最大配一下尝试一下，但是这种东西 DS 肯定不好维护，所以来转化一下。

因为要 $a_i+b_i\ge h$，两个变量在同一边，旁边是常量，看着就很烦。

直接扔过去一个 $a_i\ge h-b_i$。

这下就一边一个变量变成偏序了。

直接令 $b_i=h-b_i$，然后就变成是不是能找到排序方式满足 $\forall a_i\ge b_i$。

这个就比较套路了，扔到值域上用线段树转化为区间加减最小值即可。
## 代码
```cpp
#include <bits/stdc++.h>
#define ls (p<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
#define get(x) (lower_bound(c+1,c+1+tot,x)-c)
#define int long long
using namespace std;
const int N=3e5+10,INF=0x3f3f3f3f3f3f3f3f,mod=998244353;
int n,m,h,tot,a[N],b[N],c[N],t[N<<2],lz[N<<2];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void pushson(int p,int x){t[p]+=x,lz[p]+=x;}
inline void pushdown(int p){pushson(ls,lz[p]),pushson(rs,lz[p]);lz[p]=0;}
inline void modify(int p,int l,int r,int s,int e,int x)
{
    if(l>=s&&r<=e) return pushson(p,x);pushdown(p);
    if(mid>=s) modify(ls,l,mid,s,e,x);
    if(mid<e) modify(rs,mid+1,r,s,e,x);
    t[p]=min(t[ls],t[rs]);
}
inline void solve()
{
    n=read(),m=read(),h=read();for(int i=1;i<=m;i++) c[++tot]=b[i]=h-read();int ans=0;
    for(int i=1;i<=n;i++) c[++tot]=a[i]=read();sort(c+1,c+1+tot);tot=unique(c+1,c+1+tot)-c-1;
    for(int i=1;i<=n;i++) a[i]=get(a[i]);for(int i=1;i<=m;i++) b[i]=get(b[i]);
    for(int i=1;i<=m;i++) modify(1,1,tot,a[i],tot,-1),modify(1,1,tot,b[i],tot,1);
    ans+=t[1]>=0;for(int i=m+1;i<=n;i++) modify(1,1,tot,a[i-m],tot,1),modify(1,1,tot,a[i],tot,-1),ans+=t[1]>=0;print(ans);
}
signed main()
{
    int T=1;while(T--) solve();
    genshin:;flush();return 0;
}
```

---

## 作者：__stick (赞：0)

## 题意
给出长度为 $n$ 的序列 $a$，和长度为 $m$ 的序列 $b$。

问 $a$ 的所有长度为 $m$ 的子段是否和 $b$ 完美匹配。

其中两个位置 $i,j$ 有边当且仅当 $a_i+b_j\ge h$。

## 思路
完美匹配，想到 $\text{Hall}$ 定理：

一个二分图 $(V_1,V_2,E)$ 的最大匹配等于：

假设 $f(S)$ 表示 $S$ 集合中的点所有边指向点的并集，则当前二分图的最大匹配等于：

$|V_1|-\max_{S\in V_1}\{|S|-|f(S)|\}$

对 $V_2$ 集合同理。


对于每一个 $a$ 字段中的集合 $S$，其 $f(S)=|S|-cnt(h-\max S)$。

其中 $cnt(x)$ 表示 $b$ 中比 $x$ 大数的个数。

想要求出最大值，则 $S$ 集合中应该尽可能大，所以选择方式就是在确定最大值后直接选择所有 $a$ 中小与等于这个最大值的所有数。

然后看对于所有最大值的答案总和。

所以每个数的贡献就是：$rk_i+cnt(h-a_i)$。$rk_i$ 表示第 $i$ 个数的排名。

然后滑动窗口的时候动态维护一下 $rk$ 即可。

可以使用平衡树维护。

在窗口移动的时候，假设删去 $x$ 加入数 $y$ （$x \le   y$）

则平衡树中在 $[x,y]$ 区间数的 $rk$ 会减 $1$。

$x\ge y$ 的时候同理。

平衡树需要支持区间加，所以需要 tag。

## code

明显比线段树的方法代码量大：
```cpp
const int MAXN=2e5+10;
int a[MAXN],b[MAXN],c[MAXN];
struct node{int l,r,pr,siz;ll k,w,mmax,add;}t[MAXN];
#define ls t[p].l
#define rs t[p].r
inline void push_up(int p)
{
    t[p].siz=t[ls].siz+t[rs].siz+1;
    t[p].mmax=t[p].w;
    if(ls)cmax(t[p].mmax,t[ls].mmax);
    if(rs)cmax(t[p].mmax,t[rs].mmax);
}
inline void ADD(int p,ll k){if(p){t[p].add+=k,t[p].mmax+=k,t[p].w+=k;}}
inline void push_down(int p){if(t[p].add){ADD(ls,t[p].add),ADD(rs,t[p].add),t[p].add=0;}}
void split(int p,ll k,int& x,int& y)
{
    if(!p)return x=y=0,void();push_down(p);
    if(t[p].k<=k)x=p,split(rs,k,t[x].r,y);
    else y=p,split(ls,k,x,t[y].l);
    push_up(p);
}
void split2(int p,ll k,int& x,int& y)
{
    if(!p)return x=y=0,void();push_down(p);
    if(t[ls].siz<k)x=p,split2(rs,k-t[ls].siz-1,t[x].r,y);
    else y=p,split2(ls,k,x,t[y].l);
    push_up(p);
}
int merge(int x,int y)
{
    if(!x||!y)return x|y;
    if(t[x].pr<t[y].pr)return push_down(x),t[x].r=merge(t[x].r,y),push_up(x),x;
    else return push_down(y),t[y].l=merge(x,t[y].l),push_up(y),y;
}
int tt;
mt19937 mt(chrono::system_clock::now().time_since_epoch().count());
void insert(int& rt,int k,int w)
{
    int x,y;split(rt,k,x,y);
    t[++tt]={0,0,(int)mt(),1,k,w,w,0};
    rt=merge(merge(x,tt),y);
}
void dfs(int p)
{
    if(!p)return;
    dfs(ls),cerr<<t[p].k<<' '<<t[p].w<<'\n',dfs(rs);
}
int d[MAXN];
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);cout<<fixed<<setprecision(10);
	int n,m,h;
    cin>>n>>m>>h;
    for(int i=1;i<=m;i++)cin>>b[i];
    for(int i=1;i<=n;i++)cin>>a[i];
    vi id(m);iota(all(id),1);
    sort(all(id),[&](int x,int y){return a[x]<a[y];});
    sort(b+1,b+m+1);
    for(int i=1;i<=n;i++)c[i]=m-(lower_bound(b+1,b+m+1,h-a[i])-b)+1;
    int rt=0;
    int cnt=0;
    for(auto&i:id)cnt++,insert(rt,a[i],cnt-c[i]);
    int ans=0;
    for(int i=1;i<=n-m+1;i++)
    {
        if(t[rt].mmax<=0)ans++;
        if(i+m>n)break;
        int v1=a[i],v2=a[i+m];
        if(v1==v2)continue;
        if(v1<v2)
        {
            int x,y,z;
            split(rt,v1-1,x,y);
            split(y,v2-1,y,z);
            int p;
            split2(y,1,p,y);
            t[p].k=v2,t[p].w=t[p].mmax=t[x].siz+t[y].siz+1-c[i+m];
            ADD(y,-1);
            z=merge(p,z);
            rt=merge(merge(x,y),z);
        }
        else
        {
            swap(v1,v2);
            int x,y,z;
            split(rt,v1-1,x,y);
            split(y,v2-1,y,z);
            int p;split2(z,1,p,z);
            t[p].k=v1,t[p].w=t[p].mmax=t[x].siz+1-c[i+m];
            ADD(y,1);
            y=merge(p,y);
            rt=merge(merge(x,y),z);
        }
    }
    cout<<ans;
	return 0;
} 

```



---

