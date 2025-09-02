# [ABC376G] Treasure Hunting

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc376/tasks/abc376_g

頂点に $ 0 $ から $ N $ までの番号がついた $ N\ +\ 1 $ 頂点の根付き木があります。頂点 $ 0 $ は根で、頂点 $ i $ の親は頂点 $ p_i $ です。  
 頂点 $ 1 $, 頂点 $ 2 $, $ \dots $, 頂点 $ N $ のうちどこか $ 1 $ 頂点に宝が隠されています。頂点 $ i $ に宝がある確率は $ \frac{a_i}{\sum_{j=1}^N\ a_j} $ です。 また、各頂点には「探索済」と「未探索」のどちらか一方の状態を持ちます。はじめ頂点 $ 0 $ は探索済で、それ以外の頂点は未探索です。  
 あなたは、宝がある頂点が探索済になるまで以下の操作を行います。

- 親が探索済であるような未探索の頂点を選び、その頂点を探索済にする。
 
操作回数の期待値が最小になるように行動した時の操作回数の期待値を $ \text{mod\ }998244353 $ で求めてください。

$ T $ 個のテストケースが与えられるので、それぞれに対して答えを求めてください。

  期待値 $ \text{mod\ }{998244353} $ の定義 求める期待値は必ず有理数になることが証明できます。 また、この問題の制約のもとでは、その値を既約分数 $ \frac{P}{Q} $ で表した時、$ Q\ \not\ \equiv\ 0\ \pmod{998244353} $ となることも証明できます。このとき、$ R\ \times\ Q\ \equiv\ P\ \pmod{998244353},\ 0\ \leq\ R\ \lt\ 998244353 $ を満たす整数 $ R $ が一意に定まります。この $ R $ を答えてください。

## 说明/提示

### 制約

- $ 1\ \leq\ T\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ p_i\ \lt\ i $
- $ 1\ \leq\ a_i $
- $ \sum_{i=1}^N\ a_i\ \leq\ 10^8 $
- 全てのテストケースに対する $ N $ の総和は $ 2\ \times\ 10^5 $ 以下
- 入力される値は全て整数
 
### Sample Explanation 1

$ 1 $ 番目のテストケースにおける操作回数の期待値は $ \frac{13}{6} $ です。

## 样例 #1

### 输入

```
3
3
0 0 1
1 2 3
5
0 1 0 0 0
8 6 5 1 7
10
0 1 1 3 3 1 4 7 5 4
43 39 79 48 92 90 76 30 16 30```

### 输出

```
166374061
295776107
680203339```

# 题解

## 作者：zhm080507 (赞：3)

# [AT_abc376_G](https://atcoder.jp/contests/abc376/tasks/abc376_g)

####  题目大意

给定一棵树的形态，宝藏在每个点的概率是 $a_i$，每次可以探索一个已探索的点的子节点（初始时根已探索），问**最优策略**时找到宝藏的期望。

#### 算法分析

我们需要知道的就是两个节点 $x$ 和 $y$ 的访问先后顺序，考虑如何计算：

首先我们容易得到，在没有限制的情况下肯定是先访问概率大的那一个，但是如果有限制的话，我们还要考虑它子树内的因素。

对于两个要访问的连通块 $x$ 和 $y$，考虑 $x$ 比 $y$ 先访问（就是先合并到父亲所在的连通块）时一定满足：
$$
x.val+x.siz\times y.p+y.val\leq y.val+y.siz\times x.p +x.val
$$
这当中 $val$ 表示访问完子树（扫完或找到宝藏）的期望，$siz$ 表示字数大小，$p$ 表示宝藏在这棵子树内的概率。这个式子的关键就是中间 $$x.siz\times y.p$$ 的值，这个表示得先把 $x$ 访问完（宝藏在 $y$ 内）再访问 $y$ 的贡献。

然后我们再用一个优先队列维护，同时用并查集记录祖先。

具体实现见代码。

#### code

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N=212345,mod=998244353;
int n,T,fa[N],f[N],a[N],sum;
bool tag[N];
struct Node{
	int val,siz,p,id;
}x[N];
bool operator<(Node x,Node y){
	return x.siz*y.p>y.siz*x.p;
}//大根堆条件是反的 
Node operator+(Node x,Node y){
	Node tmp;
	tmp.val=(x.val+x.siz*y.p+y.val)%mod;
	//合并和判断条件是一样的 
	tmp.siz=x.siz+y.siz;
	tmp.p=(x.p+y.p)%mod;
	tmp.id=x.id;
	return tmp;
}
priority_queue<Node>q;

int getfa(int x){
	if(x==f[x]) return x;
	return f[x]=getfa(f[x]);
}int qp(int w,int k) {
	int tmp=1;
	while(k){
		if(k&1) tmp=tmp*w%mod;
		w=w*w%mod;
		k>>=1;
	}
	return tmp;
}

void sol(){
	sum=0;
	x[0]={0,0,0,0};
	for(int i=1;i<=n;i++)
		tag[i]=0;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>fa[i];
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++){
		sum+=a[i];
		f[i]=i;//f记录祖先 
		x[i]={a[i],1,a[i],i};
		//把a[i]钦定为概率，sum放到最后计算答案再除 
		q.push(x[i]);
	}
	while(!q.empty()){
		Node u=q.top();q.pop();
		if(tag[u.id]||u.id==0) continue;
		//如果这个点已经合并了，或者是根
		tag[u.id] =1;
		int ff=getfa(fa[u.id]);
		f[u.id]=ff;
		//把它合并到它父亲所在的并查集中
		x[ff]=x[ff]+x[u.id];
		q.push(x[ff]);
		//合并信息 
	}
	cout<<x[0].val*qp(sum,mod-2)%mod<<"\n";
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>T;
	while(T--){
//		init();
		sol();
	}
	return 0;
}
```

---

## 作者：沉石鱼惊旋 (赞：3)

# 题目翻译

每个点有 $\frac{a_i}{\sum\limits_{j=1}^{n} a_j}$ 的概率是关键点。你可以走到这个点当且仅当他的父亲节点走过了。问到达关键点的期望步数的最小值，对 $998244353$ 取模。$0$ 号点是根。

$1\leq n\leq 2\times 10^5$，$1\leq \sum a_i\leq 10^8$，$1\leq a_i$。

# 题目思路

题目等价于最小化每个点的访问顺序乘上点权。

不妨先把概率 $\times \sum\limits_{j=1}^{n} a_j$ 得到一个新的概率，答案除以 $\sum\limits_{j=1}^{n} a_j$ 即可。

一个点，如果是还未扩展的最大点，那么父亲被扩展之后一定直接选这个。

考虑这样的情况：你有若干个可以扩展到的点，共 $k$ 个，设 $p_i$ 表示访问顺序种第 $i$ 个点是哪个点，就是需要最小化 $\sum i \times a_{p_i}$。设最大点是访问顺序中的 $m$ 号点，则把最大点调到第一个可以产生 $(\sum\limits_{i=1}^{m-1} a_{p_i})-(m-1)a_{p_m}$。由于这是最大点，这个式子一定是非正的。调过去会产生更小的代价，把最大值调到第一个是最优的。

考虑合并一些节点的扩展顺序。绑定 $(x,y)$ 说明扩展 $x$ 之后必须直接扩展 $y$。

接下来来讨论有若干个节点应该先扩展哪一个。先从最简单的 $(x,y)$ 绑定而 $z$ 是单点的情况考虑。也就是解方程组 $x+2y+3z\leq z+2x+3y$ 的情况。解得 $\dfrac{a_x+a_y}{2}\geq \dfrac{a_z}{1}$。

猜测是按照绑定节点的平均代价排序的。严谨证明一下。不妨设第一个绑定节点内容是 $p_1,p_2,p_3,\dots,p_{k_1}$，第二个内容是 $q_1,q_2,q_3,\dots,q_{k_2}$。也就是 $(\sum\limits_{i=1}^{k_1} a_{p_i}\times i)+(\sum\limits_{i=1}^{k_2} a_{q_i}\times (i+k_1))\leq (\sum\limits_{i=1}^{k_2} a_{q_i}\times i)+(\sum\limits_{i=1}^{k_1} a_{p_i}\times (i+k_2))$。解得 $\dfrac{\sum a_{p_i}}{k_1}\geq \dfrac{\sum a_{q_i}}{k_2}$。选平均值大的绑定节点是正确的。

在堆里维护这些绑定节点，每次弹出平均值最大的，与父亲合并，放回堆里。维护一个访问顺序的链表，做完操作之后遍历一遍链表即可。

# 完整代码

*2858？*1858！

代码太臭就不放了。贴个链接。

[AT submission 59034795](https://atcoder.jp/contests/abc376/submissions/59034795)

---

## 作者：huangrenheluogu (赞：3)

ABC 塞这个多题，还剩 $20$ 分钟的时候会了，但是没调出来，赛后发现很多地方挂了，罚了 $3$ 发才好的。感觉这个题 kenkoooo 上评分高是因为这场量有点大，没什么人写完。

记节点的父亲是 $fa_x$ 好了，和后面变量名重合了。然后 $a_x$ 就是选择 $x$ 的概率。

这个题其实是让你钦定一个排列 $p$，满足 $p_0=0$，若 $p_i=x$，则 $\exist j\lt i,p_j=fa_x$。答案就是 $\sum\limits_{i=1}^na_{p_i}i$。

考虑一个贪心，对于 $a$ 最大的节点 $x$，肯定满足 $p_i=x,p_{i-1}=fa_x$。因此一个十分经典的套路就是把节点合并。

考虑合并之后节点的权值。比如合并两个权值为 $a_1,a_2$ 的节点，其大小为 $b_1,b_2$。然后和一个大小为 $b_3$，权值为 $a_3$ 的点判断谁在前面。

- $a_{1/2}$ 在前面，$S_1=a_1t+a_2(t+b_1)+a_3(t+b_1+b_2)$。
- $a_3$ 在前面，$S_2=a_3t+a_1(t+b_3)+a_2(t+b_3+b_1)$。

发现 $S_1\lt S_2\Leftrightarrow a_3(b_1+b_2)\lt (a_1+a_2)b_3\Leftrightarrow\dfrac{a_3}{b_3}\lt \dfrac{a_1+a_2}{b_1+b_2}$。其实是分子、分母相加的形式。

于是可以 multiset 和并查集维护。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5, mod = 998244353;
const int inf = 0x3f3f3f3f3f3f3f3f;
int T, n, fa[N], p[N], a[N], sum;
int nxt[N], las[N], x, y, ans;
__int128 C = 1;
struct node{// p/q
	int p, q, id;
}b[N], tmp;
inline bool operator < (node x, node y){
    if(C * x.p * y.q != C * x.q * y.p){
        return C * x.p * y.q < C * x.q * y.p;
    }
    return x.id < y.id;
}
inline int getfa(int x){
	return fa[x] == x ? x : fa[x] = getfa(fa[x]);
}
inline bool operator == (node x, node y){
	return x.p == y.p && x.q == y.q && x.id == y.id;
}
set<node> s;
inline int ksm(int x, int y){
	int res = 1ll;
	while(y){
		if(y & 1) res = 1ll * res * x % mod;
		x = 1ll * x * x % mod, y >>= 1;
	}
	return res;
}
signed main(){
	// freopen("data.in", "r", stdin);
    // freopen("code.out", "w", stdout);
	scanf("%lld", &T);
	while(T--){
		s.clear();
		scanf("%lld", &n);
		sum = 0ll;
		for(int i = 1; i <= n; i++){
			las[i] = i;
		}
		for(int i = 1; i <= n; i++){
			scanf("%lld", &p[i]);
		}
		for(int i = 1; i <= n; i++){
			scanf("%lld", &a[i]);
			sum += a[i];
			fa[i] = i;
			las[i] = i;
			s.insert(b[i] = {a[i], 1, i});
            // cerr << b[i].id << ' ' << b[i].p << ' ' << b[i].q << ' ' << s.size() << endl;
		}
        fa[0] = las[0] = 0;
		s.insert(b[0] = {0, inf, 0});
        while(s.size() > 1){
			auto it = s.rbegin();
			tmp = *it;
            x = getfa(tmp.id);
			y = p[x];
			y = getfa(y);
            nxt[las[y]] = x;
			las[y] = las[x];
			s.erase(tmp);
			s.erase(b[y]);
			b[y].p += b[x].p;
			b[y].q += b[x].q;
			fa[x] = y;
			s.insert(b[y]);
		}
		x = nxt[0];
		for(int i = 1; i <= n; i++){
			p[i] = x;
			x = nxt[x];
		}
        // for(int i = 1; i <= n; i++){
        //     printf("%lld ", p[i]);
        // }
        // puts("");
		sum = ksm(sum, mod - 2);
		for(int i = 1; i <= n; i++){
			a[i] = 1ll * a[i] * sum % mod;
		}
		ans = 0ll;
		for(int i = 1; i <= n; i++){
			(ans += a[p[i]] * i % mod) %= mod;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：RAND_MAX (赞：2)

一道树上贪心好题。

不妨把答案乘上 $\sum a_i$，最终答案再除去即可。题目可以转化为构造一个排列 $p$，满足 $p_{fa_x}<p_x$，求 $\min\limits_{i=1}^np_i\times a_i$。

考虑贪心并合并，对于两个连通块 $x,y$，我们计算合并后的答案值。若先遍历 $x$ 再遍历 $y$，有答案 $ans_x+ans_y+siz_x\times sum_y$。其中 $ans$ 表示连通块的答案，$siz$ 表示连通块所含节点数量，$sum$ 表示连通块中节点 $a$ 值的和。可以通过下图理解。

![](https://cdn.luogu.com.cn/upload/image_hosting/zg8nyt91.png)

我们要使答案最小，考虑合并 $x,y$ 的顺序，若先合并 $x$，需满足 $ans_x+ans_y+siz_x\times sum_y\le ans_x+ans_y+siz_y\times sum_x$，即 $siz_x\times sum_y\le siz_y\times sum_x$。考虑如何取出最小，我们发现上式可变为 $\frac{siz_x}{sum_x}\le\frac{siz_y}{sum_y}$，那么每次只需用堆维护最小的 $\frac{siz_x}{sum_x}$ 即可。合并与连通块可以使用并查集实现。

最终答案即为根节点的答案值除以 $\sum a_i$。实现细节具体见代码。


```cpp
#include<bits/stdc++.h>
#define int long long
#define N 200010
#define R read()
#define mod 998244353
using namespace std;
int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+c-48,c=getchar();
	return x*f;
}
void write(int x,char xx)
{
	static int st[35],top=0;
	if(x<0){x=-x;putchar('-');}
	do
	{
		st[top++]=x%10,x/=10;
	}while(x);
	while(top) putchar(st[--top]+48);
	putchar(xx);
}
int T,n,fa[N],f[N],sum,vis[N];
struct node//siz_i*sm_j<=siz_j*sm_i
{
	int sm,siz,ans,id;
	friend bool operator <(node x,node y)
	{
		return x.siz*y.sm>y.siz*x.sm;
	}
	friend node operator +(node x,node y)
	{
		node mmmmm={(x.sm+y.sm)%mod,(x.siz+y.siz)%mod,(x.ans+y.ans+x.siz*y.sm%mod)%mod,x.id};
		return mmmmm;
	}
}a[N];
int qpow(int x,int y)
{
	int num=1;
	while(y)
	{
		if(y&1) num=num*x%mod;
		y>>=1,x=x*x%mod;
	}
	return num;
}
int find(int x)
{
	return x==f[x]?x:f[x]=find(f[x]);
}
priority_queue<node>q;
signed main()
{
	T=R;
	while(T--)
	{
		n=R,sum=0;
		a[0]={0,0,0,0};
		while(q.size()) q.pop();
		for(int i=1,x,y;i<=n;i++) fa[i]=R,f[i]=i,vis[i]=0;
		for(int i=1,x;i<=n;i++) x=R,a[i]={x,1,x,i},sum+=x,q.push(a[i]);
		node x;
		while(q.size())
		{
			x=q.top();
			q.pop();
			int u=x.id,y=find(fa[u]);
			if(vis[u]||!u) continue;
			vis[u]=1,a[y]=a[y]+a[u];
			q.push(a[y]);f[u]=y;
		}
		write(a[0].ans*qpow(sum,mod-2)%mod,'\n');
	}
 	return 0;
}

```

---

## 作者：fzs7 (赞：1)

看到这题的第一眼就想到树上贪心。

先考虑两个点集 $A$ 和 $B$，若要使 $A$ 在 $B$ 前被选中，那么一定有先选 $A$ 再选 $B$ 的步数期望小于先选 $B$ 再选 $A$ 的步数期望。

设 $siz_S$ 表示点集 $S$ 的大小，$p_S$ 表示点集 $S$ 的最小期望步数，$sum_S$ 表示点集 $S$ 中所有点被选中的概率和，则上式等同于

$$
p_A + siz_A \times sum_B + p_B < p_B + siz_B \times sum_A + p_A\\
siz_A \times sum_B < siz_B \times sum_A
$$

于是把这些值塞到一个结构体里用优先队列维护，每次从堆顶取出一个连通块向父亲合并即可。

切了这题后可以去看看 [AT_agc023_f](https://www.luogu.com.cn/problem/AT_agc023_f)，思路类似。

~~~cpp
//这里我把0到n的点编号变成1到n+1了，代码有点丑，不喜勿喷QwQ
#include <bits/stdc++.h>
#define mod 998244353
using namespace std;

inline long long read(void) {
	long long x = 0; char c = getchar();
	while (c > '9' || c < '0') c = getchar();
	while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + c - 48, c = getchar();
	return x;
}

long long qpow (long long x, long long y) {
	if (!y) return 1;
	long long qp = qpow(x, y >> 1);
	return qp * qp % mod * (y & 1 ? x : 1) % mod;
}

struct node {
	long long id, p, sum, lg;
	friend bool operator< (node x, node y) {
		return x. lg * y. sum > y. lg * x. sum;
	}
	friend node operator+ (node x, node y) {
		return (node){x. id, (x. p + x. lg * y. sum % mod + y. p) % mod, x. sum + y. sum, x. lg + y. lg};
	}
} s[200005];

long long T, n, f[200005], a[200005], fth[200005], suma;
bool b[200005];

priority_queue<node> que;

long long find (long long x) {
	if (fth[x] != x) fth[x] = find(fth[x]);
	return fth[x];
}

void merge (long long x, long long y) {
	s[find(y)] = s[find(y)] + s[find(x)];
	fth[find(x)] = find(y);
}

int main(void) {
	T = read();
	while (T--) {
		n = read() + 1, suma = 0;
		for (int i = 2; i <= n; i++) f[i] = read() + 1;
		for (int i = 2; i <= n; i++) a[i] = read(), suma += a[i];
		for (int i = 1; i <= n; i++) s[i] = (node){i, a[i], a[i], (bool)(i - 1)}, que. push(s[i]), b[i] = 0, fth[i] = i;
		while (!que. empty()) {
			auto qe = que. top();
			que. pop();
			if (qe. id == 1 || b[qe. id]) continue;
			b[qe. id] = 1;
			merge(qe. id, f[qe. id]);
			que. push(s[find(qe. id)]);
		}
		printf("%lld\n", s[1]. p % mod * qpow(suma, mod - 2) % mod);
	}
	return 0;
}
~~~

---

## 作者：zifanwang (赞：0)

考虑维护若干个联通快，初始化每个点一个连通块。对每个联通块维护大小、$\sum_xa_x$ 还有最优期望，每次选择两个联通快合并。考虑两个联通快 $a,b$ 哪个在前面更优。

记 $a_c,a_s,a_d$ 分别表示连通块 $a$ 的点数、$\sum_xa_x$ 以及最优期望，$b$ 同理。则 $a$ 在 $b$ 前更优当且仅当 $a_c\cdot b_s<b_c\cdot a_s$，用一个 set 维护即可，每次取出最优的连通块跟父亲合并，时间复杂度 $\mathcal O(n\log n)$。

参考代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define mxn 200003
#define md 998244353
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define rept(i,a,b) for(int i=(a);i<(b);++i)
using namespace std;
ll power(ll x,int y){
	ll ans=1;
	for(;y;y>>=1){
		if(y&1)ans=ans*x%md;
		x=x*x%md;
	}
	return ans;
}
struct node{
	ll sz,ct,d;int x;
	inline bool operator<(node a)const{
		ll s1=ct*a.sz,s2=a.ct*sz;
		if(s1!=s2)return s1<s2;
		return x<a.x;
	}// c1*s2<c2*s1
}f[mxn];
inline node operator+(node x,node y){
	return {x.sz+y.sz,x.ct+y.ct,(x.d*x.sz+y.d*y.sz+x.ct*y.sz)%md*power(x.sz+y.sz,md-2)%md,x.x};
}
int T,n,fa[mxn],a[mxn],ft[mxn];
set<node>q;
inline int get(int x){
	return ft[x]==x?x:ft[x]=get(ft[x]);
}
void merge(int x,int y){
	x=get(x),y=get(y);
	q.erase(f[x]);
	ft[y]=x,f[x]=f[x]+f[y];
	q.insert(f[x]);
}
signed main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		rep(i,0,n)ft[i]=i;
		rep(i,1,n)scanf("%d",&fa[i]);
		rep(i,1,n)scanf("%d",&a[i]);
		rep(i,0,n)f[i]={a[i],i>0,i>0,i},q.insert(f[i]);
		while(q.size()){
			int x=q.begin()->x;q.erase(q.begin());
			if(x)merge(fa[x],x);
		}
		cout<<f[get(0)].d<<'\n';
	}
	return 0;
}
```

---

