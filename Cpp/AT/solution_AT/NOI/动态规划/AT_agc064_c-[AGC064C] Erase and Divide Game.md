# [AGC064C] Erase and Divide Game

## 题目描述

高桥君和青木君进行如下游戏。

1. 按照 $i=1,2,\ldots,N$ 的顺序，进行以下操作：
   - 在黑板上依次写下 $l_i$ 到 $r_i$ 之间的每一个整数（$l_i,r_i$ 是输入给定的非负整数）。
2. 只要黑板上还有至少一个整数，高桥君先手，轮流进行以下操作：
   - 从以下两种操作中恰好选择一种并执行：
     - 删除黑板上所有偶数，并将剩下的每个整数都替换为其除以 $2$ 并向下取整的值。
     - 删除黑板上所有奇数，并将剩下的每个整数都替换为其除以 $2$ 的值。
3. 当黑板上没有任何整数时，最后进行操作的人获胜，游戏结束。

已知高桥君和青木君都会采取最优策略，可以证明游戏一定会在有限步内结束。请你求出每组数据中谁会获胜。

请你针对 $T$ 组数据，回答上述问题。

## 说明/提示

### 限制条件

- $1 \leq T \leq 10^4$
- $1 \leq N \leq 10^4$
- $0 \leq l_i \leq r_i \leq 10^{18}$
- $r_i < l_{i+1}$
- 所有测试用例中 $N$ 的总和不超过 $10^4$
- 输入均为整数

### 样例解释 1

下面给出第 $1$ 个测试用例的游戏流程示例：
- 黑板上依次写下 $1,2,5,6,7$。
- 高桥君选择删除奇数。黑板上 $1,5,7$ 被删除，剩下的 $2,6$ 分别变为 $1,3$。
- 青木君选择删除奇数。黑板上 $1,3$ 被删除，黑板上已无整数，因此最后操作的青木君获胜，游戏结束。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
2
1 2
5 7
1
0 100
10
1312150450968413 28316250877914571
74859962623690078 84324828731963974
148049062628894320 252509054433933439
269587449430302150 335408917861648766
349993004923078531 354979173822804781
522842184971407769 578223540024979436
585335723211047194 615812229161735895
645762258982631926 760713016476190622
779547116602436424 819875141880895723
822981260158260519 919845426262703496```

### 输出

```
Aoki
Aoki
Takahashi```

# 题解

## 作者：xuanxuan001 (赞：11)

不容易啊，AGC 终于上了回分~~虽然还是没上 2400~~，也是第一次 AGC 前 100。D 把推结论的时候搞错了一点，导致整个就搞不出来，早知道就不该先开 D 的。

感觉 C 的官方题解有些不能理解，完全不理解那个 dp 的意义是在说啥，还是太菜了。但感觉跟官方题解不太一样（并个人感觉更容易理解），所以发篇题解。

正文
-

显然需要先考虑给定 $n$ 个数而不是区间时怎么判定。

发现两个操作的本质是选择删除二进制末位是 0/1 的数并将剩下的所有数除以二。那么可以不执行删除和除以二的操作而是从低到高逐个确定每一位的数应该是多少，直到没有符合条件的数时最后一次操作的人胜（可以转换成轮到谁操作谁输）。

那么从低位到高位建 01trie，执行的操作就等价于选择当前节点的某个儿子，直到走到空节点。那么这就是个经典的 SG 函数，但其实只需要记录 SG 函数是否为 0 即可。

但回到原问题会发现这么建 trie 的话一段值连续的区间在 trie 中是完全分散的，所以这个 trie 显然是建不出来的。所以需要思考其他的办法，考虑由深度从大到小一步步求出 SG 函数，假设目前深度为 $k+1$（即有 $2^{k+1}$ 个节点），称值 $x$ 所对应的这一层的节点为节点 $x$，那么此时节点 $x$ 和节点 $x + 2^k$ 的父节点相同，它们的信息会合并。所以如果记录一个数组，第 $i$ 个位置表示节点 $i$ 的 SG 函数是否为 0，那么每次就是折半并将对应位置的信息合并。

而这个数组也是无法开出来的，但是这么记录就能实现区间连续，所以只需要记录这个数组的连续段，每次从中间分开并归并即可。最终剩下的长度为 1 的序列的那个值就是答案。

实现时需要注意节点 $x$ 并不一定存在，不存在的点不能直接认为是必败点，因为两个空点合并还是空点，而如果有败点会合并成胜点，所以状态有空点、败点和胜点三种。

代码：
```
#include<cstdio>
#define TY ll
#define MAXN 20010
#define debug if( 1 &&putchar('>'))
#define FOR(i,a,b) for(TY i=(a);i<=(b);i=-~i)
#define fOR(i,a,b) for(TY i=(a);i<(b);i=-~i)
#define ROF(i,a,b) for(TY i=(a);i>=(b);i=~-i)
#define rOF(i,a,b) for(TY i=(a);i>(b);i=~-i)
#define EDG(i,u) for(TY i=hed[u];i;i=nxt[i])
using namespace std;
typedef long long ll;
const TY M=998244353;
typedef unsigned long long ull;
TY _abs(TY a){return a<0?-a:a;}
TY maxn(TY a,TY b){return a>b?a:b;}
TY minn(TY a,TY b){return a<b?a:b;}
inline void updmx(TY &x,TY y){if(x<y)x=y;}
inline void updmn(TY &x,TY y){if(x>y)x=y;}
inline void add(TY &x,TY y){if((x+=y)>=M)x-=M;}
TY gcd(TY a,TY b){return b?gcd(b,a%b):a;}
TY qp(TY a,TY b){TY ans=1;do{if(1&b)ans=ans*a%M;a=a*a%M;}while(b>>=1);return ans;}
char getc(){char ch=getchar();while(ch==' '||ch=='\n'||ch=='\r')ch=getchar();return ch;}
TY qr(){
	char ch=getchar();TY s=0,x=1;
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')x=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())s=s*10+ch-'0';return x*s;
}void qw(TY a){if(a>9)qw(a/10);putchar(a%10+'0');}
void qw(TY a,char ch){
	if(a<0){a=-a;putchar('-');}
	if(a>9)qw(a/10);putchar(a%10+'0');
	if(ch)putchar(ch);
}TY T=qr(),n,to[3][3],l,r,ct,p,q;//0-->nil 1-->win 2-->lose
struct node{TY l,r,d;}A[MAXN],B[MAXN],C[MAXN];
int main(){
	to[0][1]=to[1][0]=to[0][2]=to[2][0]=1;//打表得出任意两种状态合并后的状态
	to[1][1]=2;to[1][2]=to[2][1]=to[2][2]=1;A[p].r=-1;
	while(T--){
		n=qr();ct=0;
		FOR(i,1,n){
			l=qr();r=qr();
			if(A[ct].r<l-1){
				A[ct+1]=(node){.l=A[ct].r+1,.r=l-1,.d=0};++ct;
			}A[++ct]=(node){.l=l,.r=r,.d=1};
		}A[ct+1]=(node){.l=A[ct].r+1,.r=(1ll<<60)-1,.d=0};++ct;
		ROF(x,60,0){
			p=q=0;l=1ll<<x-1;//将A(ct)拆成B(p)和C(q)，再合并成A
			FOR(i,1,ct){
				if(A[i].l<l){B[++p]=A[i];updmn(B[p].r,l-1);}
				if(A[i].r>=l){
					C[++q]=A[i];updmx(C[q].l,l);
					C[q].l^=l;C[q].r^=l;
				}
			}l=r=1;ct=0;
			while(l<=p&&r<=q){
				A[ct+1].l=A[ct].r+1;
				A[++ct].d=to[B[l].d][C[r].d];
				A[ct].r=minn(B[l].r,C[r].r);
				if(A[ct].r==B[l].r)++l;
				if(A[ct].r==C[r].r)++r;
			}
		}if(A[1].d==2)printf("Aoki\n");
		else printf("Takahashi\n");
	}return 0;
}
```

---

## 作者：dead_X (赞：10)

## 思路
考虑只插入若干个数怎么做，可以直接反串建 Trie，问题转化为两个人从根往下走，拿到空子树的人输，爆搜所有状态即可解决。

将给定的区间二进制分段，分成 $\log a$ 个 $[l,l+2^k)$，上述问题的操作在这棵树上等价于前 $k$ 步不动，后面仍然正常走。

不难发现若干棵树的状态对数量是每棵树的状态数量和级别的，仍然考虑搜索，但是尝试快速合并有效状态。使用哈希记录在子树中的点集信息即可。

具体地，给每个数随机一个权值 $\{0,1\}^{64}$，我们在集合内所有数异或和相等时认为集合相等，错误率仅有 $2^{-64}$，可以接受。实现时也只需维护每棵子树的异或和即可，可以在 $O(\log a)$ 的复杂度内进行修改和查询。

时间复杂度 $O(n\log^3 a)$。
## 代码
```cpp
// Problem: C - Erase and Divide Game
// Contest: AtCoder - AtCoder Grand Contest 064
// URL: https://atcoder.jp/contests/agc064/tasks/agc064_c
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
using namespace std;
#define int long long
#define i32 signed
#define i64 long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
vector<pair<int,i64>> a[103];
mt19937_64 haitang(0520);
unordered_map<i64,bool> mp[63];
i32 ls[60000003],rs[60000003];
int tr[60000003];
int query(i32 x,int y,int z)
{
	for(int i=0; i<z; ++i)
	{
		if((y>>i)&1) x=rs[x]; else x=ls[x]; 
		if(!x) return 0;
	}
	return tr[x];
}
int cnt,rt[103];
void insert(i32 x,int y,int z)
{
	tr[x]^=z;
	int dep=61-x;
	for(int i=0; i<=dep; ++i)
	{
		if((y>>i)&1) (!rs[x])&&(tr[rs[x]=++cnt]=0,ls[cnt]=rs[cnt]=0,1),x=rs[x];
		else (!ls[x])&&(tr[ls[x]=++cnt]=0,ls[cnt]=rs[cnt]=0,1),x=ls[x];
		tr[x]^=z;
	}
	return ;
}
void update(int nl,int nr,int l,int r,int d=60)
{
	if(r<nl||nr<l) return ;
	if(l<=nl&&nr<=r)
	{
		insert(rt[d],nl>>d,haitang());
		return ;
	}
	int mid=(nl+nr)>>1;
	update(nl,mid,l,r,d-1);
	update(mid+1,nr,l,r,d-1);
	return ;
}
bool dfs(int x,int d)
{
	int H=0;
	for(int i=0; i<d; ++i) H^=query(rt[i],x>>i,d-i);
	for(int i=d; i<=60; ++i) H^=tr[rt[i]];
	if(!H) return 0;
	if(mp[d].count(H)) return mp[d][H];
	int ans=(!dfs(x+(1ll<<d),d+1))||(!dfs(x,d+1));
	return mp[d][H]=ans;
}
signed main()
{
	const int N=1ll<<60;
	for(int T=read();T--;)
	{
		for(int i=0; i<=61; ++i)
			rt[i]=i+1,tr[i]=ls[i]=rs[i]=0,
			unordered_map<i64,bool>().swap(mp[i]);
		cnt=62;
		int n=read();
		for(int i=1,l,r; i<=n; ++i)
			l=read(),r=read(),update(0,N-1,l,r);
		if(dfs(0,0)) puts("Takahashi");
		else puts("Aoki");
	}
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：4)

[Problem Link](https://www.luogu.com.cn/problem/AT_agc064_c)

**题目大意**

> 给定 $S=\bigcup_{i=1}^n[l_i,r_i]$，两个人轮流操作，删去奇数或偶数，然后把剩下 $S$ 中元素除以二下取整，删空的人获胜，问谁必胜。
>
> 数据访问：$n\le 10^4,l_i,r_i\le 10^{18}$。

**思路分析**

先考虑 $l_i=r_i$ 的情况，那么相当于反串建 Trie 轮流向下移动，从下往上维护 dp 即可，$f_u=\overline{f_{ls}}\operatorname{OR}\overline{f_{rs}}$。

那么现在面对的是若干区间，考虑类似的方式维护：先考虑最高位 $k$，在 Trie 上就是最低一层，每次合并 $i,i+2^{k-1}$，但是这里的合并可能是 $f=0/1$ 或空节点。

注意到每次操作不用一个一个合并，可以把值相同的一段区间一起合并：把所有区间分成 $[0,2^{k-1}),[2^{k-1},2^k)$，然后双指针把两部分的区间合并起来。

时间复杂度 $\mathcal O(n\log V)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct info {
	ll l,r; int x; //sg:0/1, -1:null
	friend info operator +(const info &u,const info &v) {
		return {max(u.l,v.l),min(u.r,v.r),(~u.x||~v.x)?(u.x!=1||v.x!=1):-1};
	}
};
void solve() {
	int n; scanf("%d",&n);
	vector <info> q;
	ll ed=0;
	for(int i=1;i<=n;++i) {
		ll l,r; scanf("%lld%lld",&l,&r);
		if(ed<l) q.push_back({ed,l,-1});
		q.push_back({l,ed=r+1,1});
	}
	q.push_back({ed,1ll<<60,-1});
	for(int k=59;~k;--k) {
		ll d=1ll<<k;
		vector <info> L,R;
		for(auto i:q) {
			if(i.r<=d) L.push_back(i);
			else if(d<=i.l) R.push_back({i.l-d,i.r-d,i.x});
			else L.push_back({i.l,d,i.x}),R.push_back({0,i.r-d,i.x});
		}
		q.clear();
		for(auto i=L.begin(),j=R.begin();i!=L.end()&&j!=R.end();) {
			ll x=min(i->r,j->r);
			q.push_back(*i+*j);
			if(i->r==x) ++i;
			if(j->r==x) ++j;
		}
	}
	puts(q[0].x?"Takahashi":"Aoki");
}
signed main() {
	int T; scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：Little09 (赞：4)

场上被这题薄纱了。

一定程度上参考了 @xuanxuan001 的题解。

首先如果是给 $n$ 个数，那么就是在反着建的 trie 上走，每次可以走到一个儿子，谁先走出去谁就获胜。我们从叶子节点向上推，维护每个点是必胜点还是必败点就行。

但是现在给 $n$ 个区间，每个区间在 trie 上的分布不是连续的，导致我们不能显式建出 trie。那我们直接考虑 trie 的第 $60$ 层，这一层的位置要么是空的，要么是必胜点。由于给的是区间，我们还是只能用区间维护这一层的信息，考虑能不能推到第 $59$ 层。注意到第 $i$ 个位置会和第 $i+2^{59}$ 个位置的节点合并，成为第 $59$ 层的一个节点，所以其实就是把我们维护的劈成两半，然后对应拼起来，就得到第 $59$ 层的信息了。那么一直合并就可以得到最上面一层的信息，也就是根节点的信息。

需要注意的是空节点不能完全等价必败节点，因为两个空节点合并得到空节点而不是必胜点。

注意到每层合并出的连续段都是 $O(n)$ 级别的，所以复杂度 $O(n\log v)$。

```cpp
const int N=50005;
int n; 
struct point
{
	ll l,r;
	int tp;
}a[N],b[N],c[N];
int cnt=0;
const int det[3][3]={{0,1,1},{1,2,1},{1,1,1}};

void work()
{
	cnt=0;
	ll las=-1;
	cin >> n;
	rep(i,1,n)
	{
		ll l,r;
		cin >> l >> r;
		if (las+1!=l) a[++cnt]={las+1,l-1,0};
		a[++cnt]={l,r,1};
		las=r;
	}
	a[++cnt]={las+1,inf-1,0};
	per(k,60,1)
	{
		int cntb=0,cntc=0;
		ll mid=(1ll<<(k-1))-1;
		rep(i,1,cnt)
		{
			if (a[i].r<=mid) b[++cntb]=a[i];
			else if (a[i].l>mid) c[++cntc]=a[i];
			else b[++cntb]=a[i],c[++cntc]=a[i],b[cntb].r=mid,c[cntc].l=mid+1;
		}
		rep(i,1,cntc) c[i].l-=mid+1,c[i].r-=mid+1;
		int u=1,v=1;
		cnt=0;
		while (u<=cntb&&v<=cntc)
		{
			if (b[u].r<=c[v].r) a[++cnt]=b[u];
			else a[++cnt]=c[v];
			a[cnt].tp=det[b[u].tp][c[v].tp];
			if (b[u].r==a[cnt].r) u++;
			else b[u].l=a[cnt].r+1;
			if (c[v].r==a[cnt].r) v++;
			else c[v].l=a[cnt].r+1;
		}
	}
	if (a[1].tp==1) cout << "Takahashi\n";
	else cout << "Aoki\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int T;
	cin >> T;
	while (T--) work();
	return 0;
}

```


---

## 作者：Leasier (赞：3)

被 [goujingyu](https://www.luogu.com.cn/user/266966) 薄纱了 /dk

------------

首先考虑如果给出的不是 $n$ 个区间而是 $n$ 个数，我们该怎么做。

考虑把操作放到二进制上讨论：

- 一开始 $x$ 为空。
- 两人轮流操作，每次向 $x$ 添加一个 $0/1$ 的最高位。
- 每次操作后只保留二进制末尾与 $x$ 完全匹配的数，若没数了则下一次操作者输。

于是一个暴力的想法是：

- 对这 $n$ 个数建出一棵**低位** 01-Trie。
- 设 $dp_u$ 表示现在 $x$ 为从根到 $u$ 链上的 $0/1$ 拼起来的结果，先手是否胜利。
- 若 $u$ 为叶子，$dp_u = \operatorname{true}$；否则，$dp_u = (\operatorname{not} dp_{ls_u}) \operatorname{or} (\operatorname{not} dp_{rs_u})$。

但是题中给出的是 $n$ 个区间，怎么办呢？

一个简单的想法是**维护一个区间的 dp 值**。具体地，我们有若干状态 $(l, r, x = -1/0/1)$，表示：

- $x = -1$ 表示 $[l, r]$ 在 01-Trie 上不存在。
- $x = 0$ 表示 $[l, r]$ 在 01-Trie 上存在且 dp 值为 $\operatorname{false}$。
- $x = 1$ 表示 $[l, r]$ 在 01-Trie 上存在且 dp 值为 $\operatorname{true}$。

考虑从深到浅逐层转移，我们期待连续段数量可以接受。

设我们要从 $[0, 2^{t + 1})$ 转移到 $[0, 2^t)$，即我们需要将一个 $p, p + 2^t$ 合并为 $p$。

考虑把本来的若干个区间以 $(2^t - 1, 2^t)$ 斩断，则我们只需要把两半对应位置合起来。

不难发现 $x_1, x_2$ 的合并可以表示为：

- 若 $x_1 = x_2 = -1$，合并为 $-1$。
- 若 $x_1 = x_2 = 1$，合并为 $0$。
- 否则，合并为 $1$。

由于每次转移至多因为斩断一个区间而增多一个区间，则时间复杂度为 $O(\sum (n + \log w) \log w)$，其中 $w$ 为值域 $10^{18}$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

typedef struct Segment_tag {
	int type;
	ll l;
	ll r;
	Segment_tag(){}
	Segment_tag(int type_, ll l_, ll r_){
		type = type_;
		l = l_;
		r = r_;
	}
} Segment;

const ll inf = (1ll << 60) - 1;
Segment seg[20007], l[20007], r[20007];

inline ll min(ll a, ll b){
	return a < b ? a : b;
}

inline int calc(int x, int y){
	if (x == -1 && y == -1) return -1;
	if (x == 1 && y == 1) return 0;
	return 1;
}

inline ll max(ll a, ll b){
	return a > b ? a : b;
}

int main(){
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++){
		int n, cnt = 0;
		ll pre = -1;
		scanf("%d", &n);
		for (int j = 1; j <= n; j++){
			ll l, r;
			scanf("%lld %lld", &l, &r);
			if (pre + 1 <= l - 1) seg[++cnt] = Segment(-1, pre + 1, l - 1);
			seg[++cnt] = Segment(1, l, r);
			pre = r;
		}
		if (pre < inf) seg[++cnt] = Segment(-1, pre + 1, inf);
		for (int j = 59; j >= 0; j--){
			int cnt1 = 0, cnt2 = 0;
			ll mid = (1ll << j) - 1;
			for (int k = 1; k <= cnt; k++){
				if (seg[k].r <= mid){
					l[++cnt1] = seg[k];
				} else if (seg[k].l <= mid){
					l[++cnt1] = Segment(seg[k].type, seg[k].l, mid);
					r[++cnt2] = Segment(seg[k].type, mid + 1, seg[k].r);
				} else {
					r[++cnt2] = seg[k];
				}
			}
			for (int k = 1; k <= cnt2; k++){
				r[k].l -= mid + 1;
				r[k].r -= mid + 1;
			}
			cnt = 0;
			for (int k = 1, x = 1; k <= cnt1 && x <= cnt2; ){
				ll t = min(l[k].r, r[x].r);
				seg[++cnt] = Segment(calc(l[k].type, r[x].type), max(l[k].l, r[x].l), t);
				if (l[k].r == t) k++;
				if (r[x].r == t) x++;
			}
		}
		if (seg[1].type == 1){
			printf("Takahashi\n");
		} else {
			printf("Aoki\n");
		}
	}
	return 0;
}
```

---

## 作者：lkytxdy (赞：2)

- 暴力：将所有数按位从低到高插入 01-trie，转化为，从根开始，每次可以向左儿子或右儿子走，走到空节点者输。

- 但由于所有数被表示成若干区间并的形式，不能直接插入。

  考虑将 $[l,r]$ 拆分成若干段 $[x,x+2^k-1]$ 且 $x\bmod 2^k=0$。$[x,x+2^k-1]$ 在从低到高的 01-trie 上，相当于在一棵 $k$ 层满二叉树的基础上，再在每个叶子下面接一条同一形态的链。即前 $k$ 步随便走，后面要按一条链走。

  考虑对每个 $k$ 分别建一棵 01-trie，即把整个 01-trie 拆成 $\log V$ 棵 01-trie 的并，每次在这 $\log V$ 棵 01-trie 上 同时向左/向右走。第 $k$ 棵 01-trie 是一棵 $k$ 层满二叉树的基础上，再在每个叶子下面接一棵同一形态树（多条同一形态的链的并）。

  对于第 $k$ 棵 01-trie，前 $k$ 步不管怎么走，走到的都是一棵一模一样的树，所以不需要把前 $k$ 层这整个满二叉树建出来，可以把前 $k$ 层的每一层分别缩成同一个点。

  这样状态数就优化为 $\mathcal O(n\log^2 V)$ 了。直接记搜即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e4+5,M=N*60*60;
int t,n,tot,ch[M][2];
ll l,r;
bool vis[M];
array<int,60>rt;
map<array<int,60>,bool>f;
void insert(int p,ll v){
	vis[p]=1;
	for(int i=0,k;i<60;i++){
		if(!ch[p][k=v>>i&1]) ch[p][k]=++tot;
		vis[p=ch[p][k]]=1;
	}
}
void find(ll l,ll r,ll lx,ll rx){
	if(l>=lx&&r<=rx) return insert(rt[__lg(r-l+1)],l);
	ll mid=(l+r)/2;
	if(lx<=mid) find(l,mid,lx,rx);
	if(rx>mid) find(mid+1,r,lx,rx);
}
bool dfs(array<int,60>x){
	bool emp=1;
	for(int i=0;i<60;i++) emp&=!vis[x[i]];
	if(emp) return 0;
	if(f.count(x)) return f[x];
	array<int,60>l,r;
	for(int i=0;i<60;i++)
		l[i]=ch[x[i]][0],r[i]=ch[x[i]][1];
	return f[x]=!dfs(l)||!dfs(r);
}
signed main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n),f.clear();
		for(int i=1;i<=tot;i++) ch[i][0]=ch[i][1]=vis[i]=0;
		tot=0;
		for(int i=0;i<60;i++){
			int p=++tot;
			rt[i]=p;
			for(int j=0;j<i;j++) ch[p][0]=ch[p][1]=++tot,p=tot;
		}
		for(int i=1;i<=n;i++)
			scanf("%lld%lld",&l,&r),find(0,(1ll<<60)-1,l,r);
		puts(dfs(rt)?"Takahashi":"Aoki");
	}
	return 0;
}
```

---

## 作者：Caiest_Oier (赞：2)

# [AT_agc064_c](https://www.luogu.com.cn/problem/AT_agc064_c)      

对于 $n$ 个数的情况，相当于把这些数的二进制反串加入一棵 01 Trie 中，然后从根往下走，走不动的就输了。这是可以 DP 的。     

考虑对于 $n$ 个区间的情况，如果我们按照上面的做法，点数会达到 $O(nv\log v)$ 级别。但因为是插入 $n$ 个区间，所以 DP 是有性质的。令一个节点的编号为 $(val,dep)$ 形式的二元组，dep 表示其深度（根节点为 1），val 表示从根走到当前路径，路径上 01 串的反串所表示的数。在同一深度内，val 是不重的。     

首先考虑叶子，其 dp 值必定为 1（dp 值为 1 先手必胜，为 0 后手必胜），同时一些 val 所对应的节点不存在，将其 dp 值标为 -1，按 val 映射到一个数轴上，发现形成了 1 与 -1 交错的 $O(n)$ 个连续段。    

再考虑合并到父亲上，一个父亲 $(p,dep)$ 的两个儿子分别为 $(p,dep+1)$ 与 $(p+2^{dep-1},dep+1)$ ，则对于 $dep+1$ 层长为 $2^{dep}$ 的 dp 区间，将其分为两半，左右两半叠起来，上下合并计算就可以得到上一层的 dp 区间。于是我们维护连续段，每次传到上一层的时侯砍开计算即可。对于 dp 的合并，两个 -1 得到 -1，两个 1 得到0，其他情况都是 1。     

代码：   

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int TT,n,k1,k2,k3,k4,k5,k6,k7,k8,k9,fsp[603];
struct Seg{
	int st;
	int ed;
	int v;
}T[1000003];
int totT;
Seg v1[1000003],v2[1000003];
int tot1,tot2;
signed main(){
	ios::sync_with_stdio(false);
	cin>>TT;
	fsp[0]=1;
	for(int i=1;i<=62;i++)fsp[i]=fsp[i-1]*2ll;
	while(TT--){
		cin>>n;
		k3=-1;
		totT=0;
		for(int i=1;i<=n;i++){
			cin>>k1>>k2;
			if(k3+1<k1){
				T[++totT].st=k3+1;
				T[totT].ed=k1-1;
				T[totT].v=-1;
			}
			T[++totT].st=k1;
			T[totT].ed=k2;
			T[totT].v=1;
			k3=k2;
		}
		if(k3+1<fsp[61]-1){
			T[++totT].st=k3+1;
			T[totT].ed=fsp[61]-1;
			T[totT].v=-1;
		}
		for(int i=60;i>=0;i--){
			tot1=tot2=0;
			for(int j=1;j<=totT;j++){
				if(T[j].ed<fsp[i])v1[++tot1]=T[j];
				else{
					if(T[j].st>=fsp[i])v2[++tot2]=T[j];
					else{
						v1[++tot1]=T[j];
						v2[++tot2]=T[j];
						v1[tot1].ed=fsp[i]-1;
						v2[tot2].st=fsp[i];
					}
				}
			}
			for(int j=1;j<=tot2;j++){
				v2[j].st-=fsp[i];
				v2[j].ed-=fsp[i];
			}
			totT=0;
			for(int j=1,u=1;j<=tot1&&u<=tot2;){
				k9=min(v1[j].ed,v2[u].ed);
				T[++totT].st=max(v1[j].st,v2[u].st);
				T[totT].ed=k9;
				if(v1[j].v==-1&&v2[u].v==-1)T[totT].v=-1;
				else{
					if(v1[j].v==1&&v2[u].v==1)T[totT].v=0;
					else T[totT].v=1;
				}
				if(k9==v1[j].ed)j++;
				else u++;
			}
		}
		if(T[1].v==1)cout<<"Takahashi\n";
		else cout<<"Aoki\n";
	}
	return 0;
}
```

---

## 作者：TulipeNoire (赞：2)

这是一个数据结构魔怔做法。

考虑数很少的情况怎么做？从低位到高位建出 01-trie，然后问题就变成了每次走一个儿子，走到空节点的输。但若干个区间形成的 01-trie 如何快速构建？

将每个区间用线段树的剖分方式剖成 $\mathcal O(\log V)$ 个区间，则区间所对应建图的意义，就是 01-trie 上前几层是满二叉树，其叶子节点每个点跟着一条链。考虑自底向上合并这些信息：我们先把每一层的所有链插到这一层的 trie 里，再从深到浅枚举满二叉树的深度 $t$，将树 $t$ 的左子树与树 $t+1$ 合并，右子树也和树 $t+1$ 合并，然后再把这两棵树连向同一个祖先，得到了新的树 $t$。这样就可以满足上面的信息。最后树 $0$ 就是整个 trie。

那么考虑合并时直接暴力类似线段树合并那样即可，不过为了防止更改原树的结构，每次向左右两边递归合并时要建新点。写法详见代码，时空复杂度 $\mathcal O(n\log^2V)$。

```cpp
#include<bits/stdc++.h>
#define lowbit(x) ((x)&-(x))
#define fi first
#define se second
using namespace std;
using LL=long long;
using pii=pair<int,int>;
const int N=10005;
const LL lim=0xfffffffffffffff;
int n,cnt=60;
struct Node {
    bool f;
    int ch[2];
}tr[N*7200];
inline void update(int p) {
    if (tr[tr[p].ch[0]].f&&tr[tr[p].ch[1]].f) tr[p].f=0;
    else tr[p].f=1;
}
void Insert(int b,int p,LL x) {
    if (!b) {
        tr[p].f=1;
        return;
    }
    int t=x&1;
    if (!tr[p].ch[t]) tr[p].ch[t]=++cnt;
    Insert(b-1,tr[p].ch[t],x>>1);
    update(p);
}
int Merge(int p,int q) {
    if (!p||!q) return p+q;
    int now=++cnt;
    tr[now].ch[0]=Merge(tr[p].ch[0],tr[q].ch[0]);
    tr[now].ch[1]=Merge(tr[p].ch[1],tr[q].ch[1]);
    update(now);
    return now;
}
void split(LL l,LL r,LL L,LL R,LL now) {
    if (L<=l&&r<=R) {
        int b=__lg(r-l+1);
        Insert(60-b,b+1,now);
        return;
    }
    LL mid=(l+r)>>1;
    if (L<=mid) split(l,mid,L,R,now<<1);
    if (R>mid) split(mid+1,r,L,R,now<<1|1);
}
inline void solve() {
    for (int i=1;i<=cnt;i++) tr[i]={};
    cnt=60;
    cin>>n;
    for (int i=1;i<=n;i++) {
        LL l,r;
        cin>>l>>r;
        split(0,lim,l,r,0);
    }
    int root=0;
    int i=59;
    while (!tr[i+1].ch[0]&&!tr[i+1].ch[1]) i--;
    for (;i>=0;i--) {
        int lc=Merge(tr[i+1].ch[0],root);
        int rc=Merge(tr[i+1].ch[1],root);
        tr[i+1].ch[0]=lc,tr[i+1].ch[1]=rc;
        root=i+1,update(root);
    }
    if (tr[1].f) cout<<"Takahashi\n";
    else cout<<"Aoki\n";
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int tac;
    cin>>tac;
    while (tac--) solve();
    return 0;
}
```

---

## 作者：zhiyin123 (赞：0)

**致审核：为了让数学公式易于阅读，部分下标写在中括号中。求通过 ：）：）：）**。

复杂度为 $O(N\log^2V)$（$V$ 为 $l_i,r_i$ 的**值域**）的**持久化 01 trie 树分治**做法。

# 一

首先，考虑有**特殊性质** $l_i=r_i$ 的话怎么做。

不妨设黑板上写的数是 $x_1,x_2,\cdots,x_n$（$\displaystyle n=\sum_{i=1}^N (r_i-l_i+1)$，此特殊性质下 $n=N$），那么我们可以**倒着**建一棵 01 trie 树，将 $x_1,x_2,\cdots,x_n$ 插入其中。“倒着建”的意思是，trie 树深度**浅**的节点代表数在二进制表示下的**低位**。

然后，博弈的过程就可以被转化为在这个 trie 树上玩**移动棋子的游戏**。游戏是这样的：

- 一开始，trie 树根节点有一颗棋子。
- Takahashi 和 Aoki 轮流移动棋子（Takahashi 先手），一次合法的移动为，把棋子移动到它所在节点的**儿子之一**。这相当于删除某种奇偶性的数并将剩下的数除以 $2$（向下取整）。
- 如果棋子所在的节点有**至少一个儿子为空**（01 trie 上每一个节点都有 $2$ 个儿子，分别代表二进制表示的下一位是 $0$ 还是 $1$），那么移动者可以直接将棋子**移动到空节点**并**获胜**。

然后，我们就可以直接 dp 了。设 $f[u]$ 表示，某个玩家**即将**操作时，棋子在 $u$ 节点除，他是否必赢（容易发现，如果他不必赢，那么他必输，不存在平局情况）。特别的，设所有的空节点编号为 $0$。

不妨设 $u$ 的两个儿子分别为 $\text{son}[0]$ 和 $\text{son}[1]$（儿子可能是空节点），那么有状态转移方程：

$$
\begin{gathered}
f[0]=\text{false}\\
f[u]=\operatorname{not}\ (f[\text{son}[0]]\operatorname{and}f[\text{son}[1]])
\end{gathered}
$$
这个子问题就可以 $O(N\log V)$ 解决了。（因为 01 trie 上有 $O(N\log V)$ 个节点）

# 二

考虑**去掉**特殊性质 $l_i=r_i$ 怎么做。

实际上，我们想要做到的是，快速地插入 $l_i$ 到 $r_i$ 的整数到 01 trie 中。不过，令人伤心的是，因为我们的 01 trie 是倒着建的，所以不能平凡地随便打 *lazy tag* 代替插入，因为 $l_i$ 到 $r_i$ 的整数在倒着的 01 trie 上的**位置不是连续的**。

下面为了方便表述，定义对于整数 $x$，$h(x)$ 表示 $x\operatorname{mod}2$。

假设 01 trie 的根为 $r$，其左儿子（代表 $0$ 的儿子）为 $s_0$，右儿子为 $s_1$，我们想在其中插入 $l$ 到 $r$ 的整数（**区间加入**），那么我们的插入有何性质呢？容易发现，**01 trie 的子树还是 01 trie**，所以不妨考察插入时**根的左右子树的相同之处**以节省时间。

1. 若 $h(l)=0,h(r)=1$，则相当于在以 $s_0$ 和 $s_1$ 为根的 01 trie 中均插入 $\displaystyle \frac{l}{2}$ 到 $\displaystyle \lfloor\frac{r}{2}\rfloor$ 的整数。
2. 若 $h(l)=0,h(r)=0$，则相当于先在以 $s_0$ 和 $s_1$ 为根的 01 trie 中均插入 $\displaystyle \frac{l}{2}$ 到 $\displaystyle \lfloor\frac{r+1}{2}\rfloor$ 的整数，然后在以 $s_1$ 为根的 01 trie 中**删除**一个整数 $\displaystyle \lfloor\frac{r+1}{2}\rfloor$。
3. 若 $h(l)=1,h(r)=1$，则相当于先在以 $s_0$ 和 $s_1$ 为根的 01 trie 中均插入 $\displaystyle \frac{l+1}{2}$ 到 $\displaystyle \lfloor\frac{r}{2}\rfloor$ 的整数（需要注意的是，$\displaystyle \frac{l+1}{2}$ 到 $\displaystyle \lfloor\frac{r}{2}\rfloor$ 之间**可能没有整数**，例如 $l=r=1$ 的时候），然后在以 $s_1$ 为根的 01 trie 中**额外加入**一个整数 $\displaystyle \frac{l}{2}$。
4. 若 $h(l)=1,h(r)=0$，则相当于先在以 $s_0$ 和 $s_1$ 为根的 01 trie 中均插入 $\displaystyle \frac{l+1}{2}$ 到 $\displaystyle \lfloor\frac{r+1}{2}\rfloor$ 的整数，然后在以 $s_1$ 为根的 01 trie 中删除一个整数 $\displaystyle \lfloor\frac{r+1}{2}\rfloor$，然后额外加入一个整数 $\displaystyle \frac{l}{2}$。

上面所说的一大团中具有**递归性**，所以在代码实现时可以直接写成递归形式。上面出现的操作可以被认为有 $2$ 种：

1. 在 01 trie 的**子树**中插入 $d$（$d\in\{-1,1\}$）个整数 $x$。
2. 将 01 trie 的子树**复制为**另一个子树。

第一个操作直接做单次就是 $O(\log V)$ 的，第二个操作写可持久化 01 trie 就能做到 $O(1)$。

所有的**区间加入**操作都是同时发生的，所以要**离线并分治**。

最后，如何统计答案呢？我们直接在 01 trie 的节点上维护 dp 值 $f$，使用类似于**线段树**的 *push up* 操作维护，然后答案就是 01 trie 根节点的 dp 值。

分析复杂度发现，01 trie 插入操作最多进行 $O(N\log V)$ 次，所以总复杂度为 $O(N\log^2V)$。

# 代码

```cpp
#include <bits/stdc++.h>
using std::cerr; using std::setw; using std::endl;
using std::cin; using std::cout;
template<typename Tp>
bool tomax(Tp &x, const Tp &y) {if (x < y) {x = y; return 1;} return 0;}
template<typename Tp>
bool tomin(Tp &x, const Tp &y) {if (y < x) {x = y; return 1;} return 0;}
using ll = long long;
using ull = unsigned long long;
constexpr int MAXN = 1e4, H = 61;
struct fw_t {
	ull l, r; bool del;
} O[MAXN + 5];
int N = 0;
constexpr int NSI = 4e7;
template<typename Tp>
void dest(std::vector<Tp> &vec) {
	vec.clear(); vec.shrink_to_fit(); return ;
}
struct no_t {
	int val, ls, rs;
} no[NSI + 5];
int root, ncnt;
#define n no[it]
int cop(int it) {
	no[++ncnt] = no[it];
	return ncnt;
}
void pushup(int &it){
	if (n.ls == 0 && n.rs == 0) it = 0;
	else n.val = ((no[n.ls].val > 0) & (no[n.rs].val > 0)) ^ 1;
	return ;
}
struct opt_t {int typ; ull val;};
void dfs2(int &it, std::vector<opt_t> &vec, int dep) {
	it = cop(it);
	if (dep == H) {
		for (auto &o : vec) {
			n.val += o.typ;
		}
		if (n.val == 0) it = 0;
		return ;
	}
	std::vector<opt_t> lvec, rvec;
	for (auto &o : vec) {
		if ((o.val & 1) == 0) {
			lvec.push_back({o.typ, o.val >> 1});
		} else {
			rvec.push_back({o.typ, o.val >> 1});
		}
	}
	dest(vec);
	if (!lvec.empty()) dfs2(n.ls, lvec, dep + 1);
	if (!rvec.empty()) dfs2(n.rs, rvec, dep + 1);
	pushup(it);
	return ;
}
void dfs1(int &it = root, int dep = 1) {
	it = cop(it);
	if (dep == H) {
		for (int i = 1; i <= N; i++) if (!O[i].del) {
			n.val += 1;
		}
		if (n.val == 0) it = 0;
		return ;
	}
	std::vector<opt_t> vec;
	for (int i = 1; i <= N; i++) if (!O[i].del) {
		auto &o = O[i];
		if ((o.l & 1) == 0) {
			if ((o.r & 1) == 0) {// 0 0
				vec.push_back({-1, (o.r + 1) >> 1});
				o.l >>= 1; o.r = (o.r + 1) >> 1;
			} else {// 0 1
				o.l >>= 1; o.r >>= 1;
			}
		} else {
			if ((o.r & 1) == 0) {// 1 0
				vec.push_back({1, o.l >> 1});
				vec.push_back({-1, (o.r + 1) >> 1});
				o.l = (o.l + 1) >> 1; o.r = (o.r + 1) >> 1;
			} else {// 1 1
				vec.push_back({1, o.l >> 1});
				if (o.l + 1 <= o.r) {o.l = (o.l + 1) >> 1; o.r >>= 1;}
				else {o.del = 1;}
			}
		}
	}
	dfs1(n.ls, dep + 1);
	n.rs = n.ls;
	if (!vec.empty()) dfs2(n.rs, vec, dep + 1);
	pushup(it);
	return ;
}
#undef n
void solve() {
	root = 0; ncnt = 0;
	cin >> N;
	for (int i = 1; i <= N; i++) {
		auto &o = O[i]; cin >> o.l >> o.r; o.del = 0;
	}
	dfs1();
	cout << (no[root].val > 0 ? "Takahashi" : "Aoki") << '\n';
	return ;
}
int main() {
	std::ios::sync_with_stdio(0); std::cin.tie(0); std::cout.tie(0);
	no[0] = {0, 0, 0};
	int T = 0; cin >> T;
	for (int t = 1; t <= T; t++) solve();
	return 0;
}
```

---

## 作者：zifanwang (赞：0)

先考虑所有 $l_i=r_i$ 时怎么做，可以建出反向 Trie 树，问题转化为从根开始每次向左子树或右子树走，第一个拿到空子树的人输，直接在 Trie 上 dp 即可。

考虑从叶子层开始对每一层的点合并两个子树的 dp 值，发现每一层值相同的连续段是较少的。于是可以维护这些连续段，每次合并要将每个 $f_i$ 与 $f_{i+2^k}$ 合并，把连续段分成两部分双指针合并即可，时间复杂度 $\mathcal O(N\log V)$。

参考代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define rept(i,a,b) for(int i=a;i<b;++i)
#define drep(i,a,b) for(int i=a;i>=b;--i)
using namespace std;
struct node{
	ll l,r;int x;
};
node operator+(node x,node y){
	return {max(x.l,y.l),min(x.r,y.r),x.x!=-1||y.x!=-1?x.x!=1||y.x!=1:-1};
}
int T,n;
vector<node>s,s1,s2;
signed main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n); 
		ll l,r,ls=0;
		s.clear();
		rept(i,0,n){
			scanf("%lld%lld",&l,&r);
			if(ls<l)s.pb({ls,l,-1});
			s.pb({l,r+1,1}),ls=r+1;
		}
		s.pb({ls,1ll<<60,-1});
		drep(i,59,0){
			ll k=1ll<<i;
			s1.clear(),s2.clear();
			for(node i:s){
				if(i.r<=k)s1.pb(i);
				else if(i.l>=k)s2.pb({i.l-k,i.r-k,i.x});
				else s1.pb({i.l,k,i.x}),s2.pb({0,i.r-k,i.x});
			}
			s.clear();
			for(auto i=s1.begin(),j=s2.begin();i!=s1.end()&&j!=s2.end();){
				ll r=min(i->r,j->r);
				s.pb(*i+*j);
				if(i->r==r)i++;
				if(j->r==r)j++;
			}
		}
		puts(s[0].x?"Takahashi":"Aoki");
	}
	return 0;
}
```

---

## 作者：Galois_Field_1048576 (赞：0)

如果 $l_i = r_i$，那么对这些点建反过来的 01-Trie，然后
$$
\mathrm{dp}(u) = \overline{\mathrm{dp}(L(u)) \vee \mathrm{dp}(R(u))}
$$
即可。（边界条件：$\mathrm{dp}(l) = 1~(l~\text{是叶子}), \mathrm{dp}(n) = 0~(n~\text{是空节点})$）

注意到在 dp 过程中，首先确定最底一层的 dp 值，然后层层向上。于是我们猜想：每一层的 dp 值都形成若干区间，且对于所有的层的所有的区间的个数可以被算法枚举（即复杂度可接受）。算法本身就是证明：

利用一种类似归纳法的方法。首先，对于 $\alpha = 59$（最下方一层），区间个数为 $2n$。对于当前区间集 $I$，分成两个集合 $L, R$，其中 $L$ 包括 $[0, 2^\alpha)$ 的子集，$R$ 包括 $[2^\alpha, 2^{\alpha+1})$ 的子集。容易发现最多断掉一个区间。由于我们建出的 01-Trie 是反过来的，所以 $L$ 中区间代表一个左儿子，$R$ 中区间代表一个右儿子。而传递到父亲只需将区间交起来，用一个双指针即可。对这件事从 $\alpha = 59$ 下降到 $\alpha = 1$。

实现细节：在 01-Trie 中，无 dp 值和 dp 值为 $0$ 是不同的：两个无 dp 值合成无 dp 值，而两个 dp 值为 $0$ 合成 dp 值为 $1$。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

using i64 = int64_t;

struct Maze {
    i64 typ, l, r;
    Maze(i64 _typ, i64 _l, i64 _r) : typ(_typ), l(_l), r(_r) {}
};

i64 win(i64 l, i64 r) {
    if (l == -1 && r == -1) return -1;
    if (l == 1 && r == 1) return 0;
    return 1;
}

Maze operator&(Maze a, Maze b) {
    return {
        win(a.typ, b.typ),
        max(a.l, b.l),
        min(a.r, b.r),
    };
}

const i64 inf = (1ll << 60ll);

void solve() {
    vector<Maze> meizi;
    int n;
    cin >> n;
    i64 lst_r = 0;
    for (int i = 0; i < n; i++) {
        i64 l, r;
        cin >> l >> r;
        if (lst_r < l) meizi.push_back(Maze(-1, lst_r, l));
        meizi.push_back(Maze(1, l, r + 1));
        lst_r = r + 1;
    }
    if (lst_r < inf) meizi.push_back(Maze(-1, lst_r, inf));
    for (int bit = 59; bit >= 0; --bit) {
        vector<Maze> lft, rht;
        i64 cns = (1ll << bit);
        for (auto& mz : meizi) {
            if (mz.r <= cns)
                lft.push_back(mz);
            else if (mz.l < cns)
                lft.push_back(Maze(mz.typ, mz.l, cns)),
                    rht.push_back(Maze(mz.typ, cns, mz.r));
            else
                rht.push_back(mz);
        }
        for (auto& mz : rht) mz.l -= cns, mz.r -= cns;
        meizi.clear();
        for (int i = 0, j = 0; i < lft.size() && j < rht.size();) {
            int i0 = i, j0 = j;
            meizi.push_back(lft[i] & rht[j]);
            if (lft[i].r <= rht[j].r) i0++;
            if (rht[j].r <= lft[i].r) j0++;
            i = i0, j = j0;
        }
    }
    if (meizi.size() > 0 && meizi[0].typ == 1)
        puts("Takahashi");
    else
        puts("Aoki");
}

int main() {
    int T;
    cin >> T;
    while (T--) solve();
}
```

---

