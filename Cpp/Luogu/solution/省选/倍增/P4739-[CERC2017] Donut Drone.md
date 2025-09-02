# [CERC2017] Donut Drone

## 题目描述

你正在构建一个模拟，其中一架无人机在一个不稳定的环形星球上探索。技术上来说，无人机在一个环形网格上移动——一个在两个维度上都循环连接的矩形网格。网格由 $r$ 行组成，从上到下编号为 $1$ 到 $r$，以及 $c$ 列，从左到右编号为 $1$ 到 $c$。每个网格单元都有一定的海拔——一个正整数。

无人机最初位于第一行第一列的单元格中。在每一步中，无人机会考虑三个单元格：直接向右的单元格、右下对角线的单元格和右上对角线的单元格（如有必要，进行循环连接）。无人机飞向这三个单元格中海拔最高的那个。

在模拟过程中可能发生两种类型的事件：
- “`move k`”——无人机移动 $k$ 步。
- “`change a b e`”——第 $a$ 行第 $b$ 列的单元格的海拔变为 $e$。

在每个 `move` 事件之后，找到无人机的位置。你可以假设在任何时候，同一列中连续的三个循环单元格不会有相同的海拔。因此，每一步无人机的移动都是明确的。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4 4
1 2 9 3
3 5 4 8
4 3 2 7
5 8 1 6
4
move 1
move 1
change 1 4 100
move 1
```

### 输出

```
4 2
1 3
1 4
```

## 样例 #2

### 输入

```
3 4
10 20 30 40
50 60 70 80
90 93 95 99
3
move 4
change 2 1 100
move 4
```

### 输出

```
3 1
2 1
```

# 题解

## 作者：T_Q_X (赞：13)

### 题目链接
[洛谷P4739](https://www.luogu.com.cn/problem/P4739)
### 题目翻译：
你正在模拟无人机探索一个不稳定的环状行星的过程。技术上说，无人机正在穿过一个环形网格———一个在两维上都首尾环绕在一起的矩形网格。格子的行号从上到下依次编号为$1$到$r$，列号从上到下依次编号为$1$到$c$。每个格子还有一个海拔——这是个正数。

无人机一开始位于第一行第一列的格子。每一步，无人机会考虑这样三个格子：右边、右上方、右下方（注意这个网格首尾相接）。无人机会飞到它们之中海拔最高的一个格子。模拟的过程中，共有两种可能的操作：

$move$ $k$无人机移动k步

$change$ $a$ $b$ $e$第$a$行第$b$列的格子海拔修改为$e$。

在每次$move$操作后，你都需要立刻找到无人机的位置。你可以认为，每次移动的三个目标位置海拔互不相同，因此每一步移动都是良定义的。
### solution
每次移动的步数$k$很大，所以可以联想到倍增跳法，即每次跳$2^k$步。

但步数不太好维护，我们考虑将移动$k$步转化为先暴力跳到第一列，再从第一列出发跳若干圈，最后在暴力跳剩下的不到一圈的步数。显然2段暴力跳的复杂度仅为$O(c)$，可以接受

那么问题转化为了要维护从第一列的每一个位置出发跳$2^k$圈后所处的位置。本题在$y$轴上的跳法不确定，但在$x$轴上一直是每次向右移动一格，于是可以在列上建立线段树，每个节点（设对应的列为$l,r$）维护第$l$列上每个位置，跳到第$r+1$列后所处的位置，就可以
```cpp 
t[p][i]=t[p<<1|1][t[p<<1][i]] 
```
实现转移(其中$t[p][i]$表示处在第$i$行的点，跳过$p$对应的这段区间后所处的位置，在代码中是$T[p].t[i]$)

于是根节点维护的答案就是第一列中的每个位置跳一圈后所处的位置，接下来的只不过是倍增基本套路。

每次对$(x,y)$的修改只会影响第$x-1$列维护的答案，等于是线段树中的单点修改，复杂度$O(rlog(c))$
### code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5010;
int a[N][N],ans[N][N],R,C,m,to[N][32];
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
struct SGT{
	struct tree{
		int t[N];
	}T[N<<2];
	#define lc (p<<1)
	#define rc (p<<1|1)
	#define mid (l+r>>1)
	inline void pushup(int p){
		for(int i=1;i<=R;++i)
			T[p].t[i]=T[rc].t[T[lc].t[i]];
	}
	inline void build(int p,int l,int r){
		if(l==r){
			for(int i=1;i<=R;++i) T[p].t[i]=ans[l][i];
			return ;
		}
		build(lc,l,mid);
		build(rc,mid+1,r);
		pushup(p);
	}
	inline void update(int p,int l,int r,int x){
		if(l==r){
			for(int i=1;i<=R;++i) T[p].t[i]=ans[l][i];
			return ;
		}
		if(x<=mid) update(lc,l,mid,x);
		else update(rc,mid+1,r,x);
		pushup(p);
	}
	#undef lc 
	#undef rc
	#undef mid
}T;
inline void work(int &x,int &y){
	int yy=y==C?1:y+1,x1=x>1?x-1:R,x2=x,x3=x==R?1:x+1;
	int ans=a[x1][yy],pos=x1;
	if(a[x2][yy]>ans) ans=a[x2][yy],pos=x2;
	if(a[x3][yy]>ans) ans=a[x3][yy],pos=x3;
	x=pos;y=yy;
}
int main(){
	R=read();C=read();
	for(int i=1;i<=R;++i)
		for(int j=1;j<=C;++j)
			a[i][j]=read();
	for(int i=1;i<=R;++i){
		for(int j=1;j<=C;++j){
			int x=i,y=j;work(x,y);
			ans[j][i]=x;
		}
	}
	T.build(1,1,C);
	for(int i=1;i<=R;++i) to[i][0]=T.T[1].t[i];
	for(int j=1;j<=30;++j)
		for(int i=1;i<=R;++i)
			to[i][j]=to[to[i][j-1]][j-1];
	m=read();
	int nx=1,ny=1;
	while(m--){
		char s[10];scanf("%s",s);
		if(s[0]=='c'){
			int x=read(),y=read(),e=read();
			a[x][y]=e;y=y>1?y-1:C;
			for(int i=1;i<=R;++i){
				int t1=i,t2=y;
				work(t1,t2);
				ans[y][i]=t1;
			}
			T.update(1,1,C,y);
			for(int i=1;i<=R;++i) to[i][0]=T.T[1].t[i];
			for(int j=1;j<=30;++j)
				for(int i=1;i<=R;++i)
					to[i][j]=to[to[i][j-1]][j-1];
		}
		if(s[0]=='m'){
			int k=read();
			while(k&&ny!=1) work(nx,ny),k--;
			int circle=k/C;k=k%C;
			for(int i=30;i>=0;--i) if(circle&(1<<i)) circle^=(1<<i),nx=to[nx][i];
			while(k--) work(nx,ny);
			printf("%d %d\n",nx,ny);
		}
	}
	return 0;
}
```


---

## 作者：老莽莽穿一切 (赞：6)

[更好的阅读体验](https://www.cnblogs.com/LaoMang-no-blog/p/16573702.html)

---

[**你谷 link**](https://www.luogu.com.cn/problem/P4739)

给一种不用倍增的不带 $log$ 的做法。

约定 $\mathrm{up}_i,\mathrm{down}_i,\mathrm{left}_i,\mathrm{right}_i$ 表示 $x/y$ 坐标在 $i$ 位置时向上 / 下 / 左 / 右方向**循环**移动一步的位置。

首先考虑暴力，即从起点直接模拟走 $k$ 步到达目标点，时间复杂度 $\mathcal O\left(\sum k\right)$，而 $k$ 是 $10^9$ 量级，显然不行。

简单观察可以发现，在图不改变的情况下从图中任意一点出发的情形是相同的，而图大小只有 $r\times c$，这说明走至多 $r\times c$ 步一定会走到一个已经经过的点，则会形成一个循环节，而循环节长度也至多是 $r\times c$ 的。

那么问题转化成快速走完 $r\times c$ 步，考虑在不带修改的情况下怎么做，发现时间复杂度可接受的上限是 $\mathcal O\left(m(r+c)\right)$，这启示我们可以运用分块的思想，将 $r\times c$ 步分成若干个 $c$ 步和若干个 $1$ 步，即分解成 $pc+q$ 的形式，然后每次跳 $c$ 步，一个粗劣的想法是预处理一个 $\mathrm{skip}_{i,j}$ 表示从位置 $(i,j)$ 走 $c$ 步能走到哪里，这样我们可以直接用倍增或别的什么方法预处理 $\mathrm{skip}$ 数组和循环节，先不论时间复杂度，特别是带上修改以后，实现就非常困难。

考虑为什么实现这么困难，究其根本是需要维护的东西太多了，我们希望能通过询问时的一些常数开销减少维护量，然后我们发现我们可以只维护第一列的信息，这就相对好维护多了，先预处理出 $\mathrm{step}_{i,j}$ 表示 $(i,j)$ 走 $1$ 步能走到 $(\mathrm{step}_{i,j},\mathrm{right}_j)$ ，$\mathrm{skip}_i$ 表示 $(i,1)$ 跳 $c$ 步后会回到 $(\mathrm{skip}_i,1)$，循环节可以在询问时找，具体每次询问时先走到第一列，在第一列跳直到找到循环节或者遇到了剩余步数不到 $c$，然后对循环节取模，然后再跳 $c$ 步最多跳 $r$ 次，再走最多 $c$ 步，那么我们就将单次询问的时间复杂度压在了 $\mathcal O\left(r+c\right)$。

我们发现我们的询问时间复杂度已经非常优美了，实现难度也不大，我们可以接下来考虑让修改去迎合询问的操作，分别考虑一次修改对 $\mathrm{step}$ 和 $\mathrm{skip}$ 的影响，先考虑较为简单的 $\mathrm{step}$，答案发现修改 $(x,y)$ 只会对 $(\mathrm{up}_x,\mathrm{left}_y),(x,\mathrm{left}_y),(\mathrm{down}_x,\mathrm{left}_y)$，三个位置产生影响，将这三个位置重新做就好了，那么再考虑如果 $\mathrm{step}_{x,y}$ 的修改会对 $\mathrm{skip}$ 产生的影响，即将会走到 $(x,y)$ 的每一行的 $\mathrm{skip}$ 都修改为 $(x,y)$ 走到的那个 $(p,1)$ 的 $p$。

想要求出 $p$ 是很简单的，直接走到 $p$ 的位置就好了，但是想要处理会被影响的 $\mathrm{skip}$ 还是有些难度的，但我们可以发现一个性质，即被影响的 $\mathrm{skip}$ 一定构成一个区间，证明也非常简单，我们发现如果有一组 $[l,r]$ 满足 $\mathrm{skip}_l=p,\mathrm{skip}_r=p$，但存在一个 $t$ 满足 $t\in(l,r),\mathrm{skip}\ne p$，则 $t$ 想走向另一个终点所需要经过的路径一定和 $l$ 或 $r$ 走向 $p$ 的路径有交或交叉，这两种情况都是不可能的，证明可以自行画图手模一下。

这样的话就可以很方便地求出答案了，从 $x$ 慢慢反向推到 $1$，做到 $k$ 时，维护一组 $[l,r]$ 表示从 $\forall i\in[l,r],\ (i,k)\to(p,1)$，我们可以一步一步往前推，具体实现可以看代码，时间复杂度是 $\mathcal O\left(c\right)$ 的。

这样的话加上预处理的时间复杂度总时间复杂度就是 $\mathcal O\left(rc+m(r+c)\right)$，比倍增法少一个 $log$。

[c++ 代码](https://www.cnblogs.com/LaoMang-no-blog/p/16573702.html)

---

## 作者：CommandSR (赞：5)

## 基本思路

对于每一次移动，先暴力移动到第 $1$ 列，然后用倍增预处理出跳 $2^k$ 圈所在的行数，再把剩下的暴力跳完。

显然两次暴力是 $O(n)$ 的，重点处理中间那个倍增，考虑到要合并区间和修改，使用线段树。

对每一行建一颗线段树，第 $i$ 线段树的节点对应区间 $[l, r]$ 表示从 $(i, l)$ 跳 $r$ 步所在的行数。

所以 pushup 操作为：

```cpp
// 设 seg[rt].t[i] 表示第 i 行的 rt 节点存的信息。
// 至于“信息”是什么，看上面那段话。

seg[rt].t[i] = seg[rc(rt)].t[seg[lc(rt)].t[i]];
```

对于单点修改，只会对前一列的答案造成影响，所以单点修改前一列的答案即可。

维护好线段树之后更新倍增数组：

```cpp
void GetTo() {
	F(i, 1, n) to[i][0] = seg[1].t[i];
	F(j, 1, 30) { // 这里第二维是 logk 不是 logn
		F(i, 1, n) to[i][j] = to[to[i][j-1]][j-1];
	}
}
```

具体细节见代码。

## AC Code

```cpp
#include <bits/stdc++.h>
#define F(i, a, b) for (int i = a; i <= b; ++i)
#define _F(i, a, b) for (int i = a; i >= b; --i)
#define ll long long
using namespace std;
inline ll rd() {
	ll p = 0, f = 1; char ch = getchar();
	while (ch>'9' || ch<'0') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch>='0' && ch<='9') p = p*10+ch-'0', ch = getchar();
	return p * f;
}
const int N = 2005;
ll n, m, q, a[N][N], b[N][N], to[N][32]; // 这里第二维是 logk 不是 logn
void Move(ll &x, ll &y) { // 从 (x, y) 移动一步
	ll yy = (y == m ? 1 : y+1), x1 = (x == 1 ? n : x-1), x2 = x, x3 = (x == n ? 1 : x+1);
	ll mx = a[x1][yy], pos = x1;
	if (a[x2][yy] > mx) mx = a[x2][yy], pos = x2;
	if (a[x3][yy] > mx) mx = a[x3][yy], pos = x3;
	x = pos, y = yy;
}
namespace SGT {
#define lc(x) (x<<1)
#define rc(x) (x<<1|1)
	struct segNode {
		ll t[N];
	} seg[N<<2];
	void Pushup(ll rt) {
		F(i, 1, n) seg[rt].t[i] = seg[rc(rt)].t[seg[lc(rt)].t[i]];
	}
	void Build(ll rt, ll l, ll r) { // 对于每一行建一个列的线段树
		if (l == r) {
			F(i, 1, n) seg[rt].t[i] = b[l][i];
			return;
		}
		ll mid = (l + r) >> 1;
		Build(lc(rt), l, mid), Build(rc(rt), mid + 1, r);
		Pushup(rt);
	}
	void Modify(ll p, ll rt, ll l, ll r) {
		if (l == r) {
			F(i, 1, n) seg[rt].t[i] = b[l][i];
			return;
		}
		ll mid = (l + r) >> 1;
		if (p <= mid) Modify(p, lc(rt), l, mid);
		else Modify(p, rc(rt), mid + 1, r);
		Pushup(rt);
	}
}
using namespace SGT;
void GetTo() {
	F(i, 1, n) to[i][0] = seg[1].t[i];
	F(j, 1, 30) { // 这里第二维是 logk 不是 logn
		F(i, 1, n) to[i][j] = to[to[i][j-1]][j-1];
	}
}
int main() {
	n = rd(), m = rd();
	F(i, 1, n) F(j, 1, m) a[i][j] = rd();
	F(i, 1, n) F(j, 1, m) {
		ll px = i, py = j; Move(px, py);
		b[j][i] = px; // 跳到哪一行
	}
	Build(1, 1, m); // 对于每一行建一个列的线段树
	GetTo();
	q = rd();
	ll cx = 1, cy = 1;
	F(i, 1, q) {
		string s; cin >> s;
		if (s == "move") {
			ll k = rd();
			while (k && cy != 1) Move(cx, cy), --k;
			ll kk = k / m; k %= m;
			_F(j, 30, 0) if (kk & (1 << j)) kk ^= (1 << j), cx = to[cx][j]; // 这里第二维是 logk 不是 logn
			while (k--) Move(cx, cy);
			cout << cx << ' ' << cy << '\n';
		} else {
			ll x = rd(), y = rd(), z = rd();
			a[x][y] = z, y = (y == 1 ? m : y-1); // 只会对 y-1 列造成影响
			F(i, 1, n) {
				ll px = i, py = y;
				Move(px, py);
				b[y][i] = px;
			}
			Modify(y, 1, 1, m);
			GetTo();
		}
	}
	return 0;
}
```

---

## 作者：Graphcity (赞：3)

注意到每次向右移动一列可以写成二元组的形式：$(x,p_x)$ 表示之前在第 $x$ 行的无人机下一次会走到第 $p_x$ 行。把所有的 $(x,p_x)$ 合并起来，就形成了一个类似于置换的东西，可以用数组 $\{a\}$ 来表示，$a_i$ 表示之前在第 $i$ 格下一步走到的位置。

两个数组 $\{a\},\{b\}$ 是可以合并的。我们定义 $\{a\}+\{b\}=\{c\}$，则有 $c_i=b_{a_i}$。这种满足结合律的信息可以用线段树来维护，单次合并需要 $O(n)$ 的时间。

每次修改至多修改一列的信息，单次修改复杂度 $O(n\log m)$。接下来是查询。注意到除开首尾的一小部分，其它的一大段都是在这个矩阵里面转来转去。设 $\{a\}^k$ 为信息 $\{a\}$ 合并 $k$ 次后的结果，可以用快速幂来加速。这样中间段的计算可以优化到单次 $O(n\log k)$，首尾则直接在线段树上查询即可。

总时间复杂度 $O(qn\log (m+k))$。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2000;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,m,q,tx,ty,val[Maxn+5][Maxn+5]; char opt[10];

struct Matrix
{
    int f[Maxn+5];
    inline int&operator()(int a) {return f[a];}
} idt,t[Maxn*4+5],g[Maxn+5];
inline Matrix operator*(Matrix a,Matrix b)
{
    Matrix c; For(i,1,n) c(i)=b(a(i));
    return c;
}
inline Matrix Pow(Matrix x,int y)
{
    Matrix res=idt;
    while(y)
    {
        if(y&1) res=res*x;
        x=x*x,y>>=1;
    }
    return res;
}

#define pre(x) (x==1?n:x-1)
#define nxt(x) (x==n?1:x+1)
#define prem(x) (x==1?m:x-1)
#define nxtm(x) (x==m?1:x+1)
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
inline void push_up(int p) {t[p]=t[ls(p)]*t[rs(p)];}
inline void ReBuild(int x,int y)
{
    int a=pre(x),b=x,c=nxt(x),ny=nxtm(y);
    int va=val[a][ny],vb=val[b][ny],vc=val[c][ny];
    if(va>vb && va>vc) g[y](x)=a;
    if(vb>va && vb>vc) g[y](x)=b;
    if(vc>va && vc>vb) g[y](x)=c;
}
inline void Build(int l,int r,int p)
{
    if(l==r) {t[p]=g[l]; return;}
    int mid=(l+r)>>1;
    Build(l,mid,ls(p)),Build(mid+1,r,rs(p)),push_up(p);
}
inline void Update(int l,int r,int p,int k)
{
    if(l==r) {t[p]=g[l]; return;}
    int mid=(l+r)>>1;
    if(k<=mid) Update(l,mid,ls(p),k);
    else Update(mid+1,r,rs(p),k);
    push_up(p);
}
inline Matrix Count(int nl,int nr,int l,int r,int p)
{
    if(l>r) return idt;
    if(l<=nl && nr<=r) return t[p];
    int mid=(nl+nr)>>1; Matrix res=idt;
    if(l<=mid) res=res*Count(nl,mid,l,r,ls(p));
    if(r>mid) res=res*Count(mid+1,nr,l,r,rs(p));
    return res;
}

int main()
{
    n=read(),m=read(),tx=1,ty=1;
    For(i,1,n) idt(i)=i;
    For(i,1,n) For(j,1,m) val[i][j]=read();
    For(i,1,n) For(j,1,m) ReBuild(i,j);
    Build(1,m,1),q=read();
    while(q--)
    {
        int a,b,c,pb; scanf("%s",opt+1);
        if(opt[1]=='c')
        {
            a=read(),b=read(),c=read(),val[a][b]=c,pb=prem(b);
            ReBuild(pre(a),pb),ReBuild(a,pb),ReBuild(nxt(a),pb);
            Update(1,m,1,pb);
        }
        else
        {
            Matrix now; a=read();
            if(ty+a<=m)
            {
                now=Count(1,m,ty,ty+a-1,1);
                tx=now(tx),ty+=a;
                printf("%d %d\n",tx,ty); continue;
            }
            now=Count(1,m,ty,m,1),a-=(m-ty+1),ty+=(m-ty+1);
            now=now*Pow(t[1],a/m)*Count(1,m,1,a%m,1);
            tx=now(tx),ty=(ty+a-1)%m+1;
            printf("%d %d\n",tx,ty);
        }
    }
    return 0;
}
```

---

## 作者：daniEl_lElE (赞：1)

显然倍增。

显然维护每个点向后走 $2^i$ 是不行的，容易发现在每次询问暴力枚举一些是可行的，故考虑只每次维护从最后一列每个点向后走 $2^i$ 圈的答案。剩下来的暴力处理。

考虑怎么边修改边维护从最后一列每个点向后 $1$ 圈会到最后一列的哪里。我们可以考虑线段树上维护每个 $l\sim r$ 从 $l$ 列 $i$ 行会走到 $r$ 列 $x_i$ 行，合并是容易的。

这样做的复杂度是 $O(m(r\log c+r\log k+c))$。可以通过。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+R)>>1)
using namespace std;
int a[2005][2005],r,c,nxt[2005],lst[2005],go[2005][31];
struct node{
	int to[2005];
};
struct sgt{
	node f[8005];
	node merge(node x,node y){
		node ans;
		for(int i=1;i<=r;i++){
			ans.to[i]=y.to[x.to[i]];
		}
		return ans;
	}
	void build(int i,int l,int R){
		if(l==R){
			for(int j=1;j<=r;j++){
				int maxv=max(a[j][l],max(a[lst[j]][l],a[nxt[j]][l]));
				if(a[j][l]==maxv) f[i].to[j]=j;
				if(a[lst[j]][l]==maxv) f[i].to[j]=lst[j];
				if(a[nxt[j]][l]==maxv) f[i].to[j]=nxt[j];
			}
			return ;
		}
		build(i*2,l,mid),build(i*2+1,mid+1,R);
		f[i]=merge(f[i*2],f[i*2+1]);
	}
	void change(int i,int l,int R,int pos){
		if(l==R){
			for(int j=1;j<=r;j++){
				int maxv=max(a[j][l],max(a[lst[j]][l],a[nxt[j]][l]));
				if(a[j][l]==maxv) f[i].to[j]=j;
				if(a[lst[j]][l]==maxv) f[i].to[j]=lst[j];
				if(a[nxt[j]][l]==maxv) f[i].to[j]=nxt[j];
			}
			return ;
		}
		if(pos<=mid) change(i*2,l,mid,pos);
		else change(i*2+1,mid+1,R,pos);
		f[i]=merge(f[i*2],f[i*2+1]);
	}
}tree;
signed main(){
	cin>>r>>c;
	for(int i=1;i<=r;i++) for(int j=1;j<=c;j++) cin>>a[i][j];
	for(int i=1;i<r;i++) nxt[i]=i+1; nxt[r]=1;
	for(int i=2;i<=r;i++) lst[i]=i-1; lst[1]=r;
	tree.build(1,1,c);
	int m; cin>>m;
	int nowx=1,nowy=1;
	while(m--){
		string s; cin>>s;
		if(s=="change"){
			int x,y,e; cin>>x>>y>>e;
			a[x][y]=e;
			tree.change(1,1,c,y);
			for(int i=1;i<=r;i++) go[i][0]=tree.f[1].to[i];
			for(int j=1;j<=30;j++) for(int i=1;i<=r;i++) go[i][j]=go[go[i][j-1]][j-1];
		}
		else{
			int k; cin>>k;
			while(nowy!=c){
				if(k==0) break;
				nowy++;
				int maxv=max(a[nowx][nowy],max(a[lst[nowx]][nowy],a[nxt[nowx]][nowy]));
				if(a[nowx][nowy]==maxv) nowx=nowx;
				if(a[lst[nowx]][nowy]==maxv) nowx=lst[nowx];
				if(a[nxt[nowx]][nowy]==maxv) nowx=nxt[nowx];
				k--;
			}
			int tm=k/c;
			k-=tm*c;
			for(int i=30;i>=0;i--){
				if(tm>=(1<<i)){
					tm-=(1<<i);
					nowx=go[nowx][i];
				}
			}
			while(k--){
				nowy++; if(nowy==c+1) nowy=1;
				int maxv=max(a[nowx][nowy],max(a[lst[nowx]][nowy],a[nxt[nowx]][nowy]));
				if(a[nowx][nowy]==maxv) nowx=nowx;
				if(a[lst[nowx]][nowy]==maxv) nowx=lst[nowx];
				if(a[nxt[nowx]][nowy]==maxv) nowx=nxt[nowx];
			}
			cout<<nowx<<" "<<nowy<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：hkhkkk (赞：1)

#### 一种更直接的暴力做法

(好久之前的题解了)。

之前懒得写线段树，所以分享一种复杂度较劣但常数较小的做法。

同样考虑先暴力走到第一列然后跳若干圈，最后再暴力走完。

那么设位置 $(i,j)$ 的**目标行**是从该位置向右走到某个 $(p,1)$ 所在的行，第 $k$ 行的**目标行**为 $(k,1)$ 的**目标行**，维护每一行的**目标行**后，可以倍增算出跳 $2^n$ 圈后处于哪一行，从而快速计算最终到达的行。

首先可以对每一行 $O(rc)$ 暴力找出**目标行**。

现在观察修改后对每一行的影响，发现一个位置的修改可能会影响到三个位置的走向，也就是说，能够到达这三个位置的行都可能会被影响。

那么考虑暴力找出这三个位置的**目标行**，再把所有能够从第一列到达这三个位置的行更新答案就好了。

那么需要支持快速判定 $(i,j)$ 是否能从 $(k,1)$ 到达，发现可以在搜索的时候记录路径。

用 ```T[k]``` 存从 $(k,1)$ 开始走一圈的路径( ```T[k][j]``` 存走到第 $j$ 列时所在的行)，则能达到位置 $(i,j)$ 的条件为 ```T[k][j]==i``` 。

维护路径后可以 $O(1)$ 判定并修改**目标行**，注意修改后可能会改变每一行的路径，那么只要找出这三个位置余下的路径，判定能够抵达后用 ``memcpy`` 覆盖即可。
 
时间复杂度 $O(\frac{mrc}{w})$，瓶颈在 ``memcpy``。

#### Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
int k, a, b, r, c, m, ex, ey, e[2005][2005], mov[2005][2005], t[2005], T[2005][2005], to[2005][32], tot;
int read() {
    int x = 0;
    char C = getchar();
    while (C < '0' || C > '9') C = getchar();
    while (C >= '0' && C <= '9') x = x * 10 + C - '0', C = getchar();
    return x;
}
int work(int x, int y) {//嫖来的函数，很好用
    int yy = y == c ? 1 : y + 1, x1 = x > 1 ? x - 1 : r, x2 = x, x3 = x == r ? 1 : x + 1;
    int ans = e[x1][yy], pos = x1;
    if (e[x2][yy] > ans)
        ans = e[x2][yy], pos = x2;
    if (e[x3][yy] > ans)
        ans = e[x3][yy], pos = x3;
    return pos;
}
void dfs(int x, int y) {//搜索路径
    t[++tot] = x;
    if (y > c)
        return;
    dfs(mov[x][y], y + 1);
}
int main() {
    cin >> r >> c;
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) e[i][j] = read();
    }
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            mov[i][j] = work(i, j);
        }
    }
    for (int i = 1; i <= r; i++) {
        tot = 0;
        dfs(i, 1);
        memcpy(T[i] + 1, t + 1, tot * 4);
        to[i][0] = T[i][tot];//跑一圈目标行
    }
    for (int j = 1; j <= 30; j++)//计算倍增数组
        for (int i = 1; i <= r; i++) {
            to[i][j] = to[to[i][j - 1]][j - 1];
        }
    m = read();
    ex = ey = 1;
    string s;
    for (int i = 1; i <= m; i++) {
        cin >> s;
        if (s[0] == 'm') {
            scanf("%d", &k);
            while (ey != 1 && k) {//移动到第一行
                ex = mov[ex][ey];
                ey++;
                k--;
                if (ey > c)
                    ey = 1;
            }
            int Circle = k / c;
            k -= Circle * c;
            for (int j = 30; j >= 0; j--) {//倍增跑圈
                if (Circle & (1 << j)) {
                    ex = to[ex][j];
                    Circle ^= (1 << j);
                }
            }
            while (k) {//余下步数
                ex = mov[ex][ey];
                ey++;
                k--;
                if (ey > c)
                    ey = 1;
            }
            cout << ex << ' ' << ey << endl;
        } else {
            scanf("%d%d%d", &a, &b, &k);
            e[a][b] = k;
            if (b == 1)
                b = c;
            else
                b--;
            int a1 = (a == 1 ? r : a - 1), a2 = (a == r ? 1 : a + 1);
            mov[a1][b] = work(a1, b);
            mov[a][b] = work(a, b);
            mov[a2][b] = work(a2, b);
            tot = 0;
            dfs(a1, b);
            for (int i = 1; i <= r; i++) {
                if (T[i][b] == a1) {//判定
                    memcpy(T[i] + b, t + 1, tot * 4);//修改路径
                    to[i][0] = t[tot];
                }
            }
            tot = 0;
            dfs(a, b);
            for (int i = 1; i <= r; i++) {
                if (T[i][b] == a) {
                    memcpy(T[i] + b, t + 1, tot * 4);
                    to[i][0] = t[tot];
                }
            }
            tot = 0;
            dfs(a2, b);
            for (int i = 1; i <= r; i++) {
                if (T[i][b] == a2) {
                    memcpy(T[i] + b, t + 1, tot * 4);
                    to[i][0] = t[tot];
                }
            }
            for (int j = 1; j <= 30; j++)//重新计算
                for (int i = 1; i <= r; i++) {
                    to[i][j] = to[to[i][j - 1]][j - 1];
                }
        }
    }
    return 0;
}
```
~~貌似有更快的 $O(m(r+c))$ 做法。~~


---

