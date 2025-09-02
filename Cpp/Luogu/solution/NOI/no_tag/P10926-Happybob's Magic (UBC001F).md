# Happybob's Magic (UBC001F)

## 题目描述

Happybob 正在游戏里研究一排灯，总共 $2^n$ 个，编号为 $0\sim 2^n-1$。Happybob 有两个技能。

一技能（按下 `B` 释放）释放一次，所有的灯亮变成灭，灭变成亮。

二技能（按下 `D` 释放）就厉害了，每释放一次，假设释放前的所有亮着的灯的编号组成的集合是 $X$，那么对于 $X$ 的**所有 $2^{|X|}$ 个子集（包含空集）** $Y$，Happybob 会把第 $\bigoplus(Y)$ 盏灯点亮。这里的 $|X|$ 表示 $X$ 集合的大小，$\bigoplus(Y)$ 表示将集合 $Y$ 的所有元素进行二进制按位异或得到的结果。特别地，$\bigoplus(\varnothing) = 0$。

现在有一个 `B`，`D` 构成的施法序列 $S(|S|=m)$（意义如上），一个灯的初始状态序列（第 $0$ 个版本）$a_0,a_1,\cdots,a_{2^n-1}$，以及一个变量 $vid=0$。Happybob 有 $q$ 次询问，每次询问可能是：

1. `1 v l r`：将 $vid$ 加 $1$，对第 $v$ 个版本依次执行 $S_l$ 到 $S_r$ 的施法操作，将结果存入第 $vid$ 个版本中，并问第 $vid$ 个版本中有多少盏灯是亮的。
2. `2 v k`：问第 $v$ 个版本的第 $k$ 盏灯是不是亮的。是输出 $1$，否则输出 $0$。
3. `3 v k`：设第 $v$ 个版本是从第 $v'$ 个版本执行了 $t$ 次施法操作变过来的，问有多少次施法操作之后，第 $k$ 盏灯是亮的（原来是亮的不算）。

对于第三种询问，这里的 $v'$ 和 $t$ 具体定义如下：假设进行某一次第一种询问后 $vid = v$，则 $v'$ 等于那一次询问给定的 $v$，$t$ 即那一次询问给定的操作序列 $S_{l\cdots r}$ 的长度。

保证 $0\le v\le vid$（如果是第一个操作，则是加 $1$ 前的 $vid$；如果是第三个操作，还保证 $v>0$）。

## 说明/提示

### 样例说明

| 版本编号 | 灯的状态 |
| --- | --- | 
| $0$ | $01010100$ | 
| $1$ | $01111111$ | 
| $2$ | $11111111$ |
| $3$ | $00000000$ |

对于最后一次询问，每次施法操作后的状态如下：

| 操作 | 灯的状态 |
| --- | --- | 
| 初始值 | $01010100$ | 
| `B` | $10101011$ | 
| `BD` | $111\red11111$ | 
| `BDB` | $00000000$ |
| `BDBD` | $10000000$ |
| `BDBDB` | $011\red11111$ |

第 $3$ 盏灯亮了 $2$ 次。

### 数据范围

对于 $100\%$ 的数据， $1\le n\le 18$，$1\le q\le 2\times 10^5$，$a_i\in\{0, 1\}$，$1\le l\le r\le m\le 2\times 10^5$，$0\le k<2^n$。保证 $S$ 中只含字符 `B` 与 `D`（可能不含 `B` 或不含 `D`），且 $S$ 的长度为 $m$。

## 样例 #1

### 输入

```
3 10 6
0 1 0 1 0 1 0 0
BDBDBDDBBD
1 0 1 5
1 0 8 10
1 0 6 8
2 2 4
2 3 4
3 1 3```

### 输出

```
7
8
0
1
0
2```

# 题解

## 作者：xuanxuan001 (赞：6)

抽象的官解，爽飞的四天。

发现两种操作都是整体的批量操作而没有针对单点的，所以感性理解一下这些操作是很不“自由”的，推理一下发现确实如此。

由于 D 操作针对元素而不是序列，所以下面直接认为序列是所有为 $1$ 位置构成的集合，$D(A)$ 表示对 $A$ 进行一次 D 操作后的集合。

首先，如果进行了一次 D 操作后，那么再次进行 D 操作不会改变，但如果取反（就是 B 操作，这么说直观一些，下同）后会发现只要它不是空集，那么它就拥有至少一半的元素（即值是 $1$）。那么猜想这个序列进行一次 D 操作后一定会变成全集，证明如下：

发现所有的情况都严格不劣于恰有 $2^{n-1}$ 个元素的情况，也就是操作前的集合（设它为 $A$）的线性基大小为 $n-1$。那么此时不妨设线性基中没有 $1$ （即最高位是 $2^0$）。那么取反后一定满足 $1$ 在集合里面，而 $\forall x \in (0,2^n-1)$ 一定有 $x \in A$ 或 $x \oplus 1 \in A$，因此如果再进行一次 D 操作就一定有 $x,x \oplus 1 \in D(A)$，因此可知 $D(A) = U$。

同样的，也可以得到 $A$ 和它的补集中至少有一个进行 D 变换后会变成全集。

那么有了这些结论，就不难发现可能的集合只有 $O(1)$ 种，经过梳理，发现有八种：

1. $A$ 及其补集（即 B 操作，下同）。
2. $D(A)$ 或 $D(U\setminus A)$ 及其补集。
3. $U$
4. $\emptyset$
5. $\{0\}$ 及其补集。

对于第五条的解释：$D(\emptyset) = \{0\}$。

因此只需要用一个数就能存储整个集合，并实现 $O(1)$ 单次变换和查询。

其实这里跟官解前面的那些观察差不多。

每次需要变换一个区间，这是容易维护的，线段树即可维护，记录每个节点的函数值以及每种数列的经过次数即可。总复杂度 $O(n2^n +8^2m + 8q\log m)$，把 $8$ 认为和 $\log m$ 同阶的话甚至刚好平衡了，不用上猫树。

可能复杂度有些高？官解最后靠循环节直接计算倒也是个思路，主要是利用了 BD 两个操作连续进行多次都没有意义，幸好没卡我的。~~但我觉得代码复杂度肯定是我优~~。

代码
```
#include<cstdio>
#define TY int
#define MAXN 262144
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
}TY n,m,T,b[MAXN],ct,kd,x,l,r,to[2][8],ar[18],nm,tot[MAXN][8],vl[8],ans;
TY tre[MAXN<<1][8],sm[MAXN<<1][8][8],tmp[8];
bool a[MAXN],t[MAXN];char s[MAXN];
//集合编号按题解中列举顺序，0代表B变换，1代表D变换
void ins(TY x){
	ROF(i,n-1,0)if((1<<i)&x){
		if(ar[i]){x^=a[i];continue;}
		ar[i]=x;++nm;return;
	}
}void dfs(TY x,TY v){
	if(x==n){t[v]=true;return;}
	dfs(x+1,v);if(ar[x])dfs(x+1,v^ar[x]);
}void build(TY i,TY j,TY id){
	if(i==j){
		if(s[i]=='B')fOR(i,0,8){
			tre[id][i]=to[0][i];
			sm[id][i][to[0][i]]=1;
		}else fOR(i,0,8){
			tre[id][i]=to[1][i];
			sm[id][i][to[1][i]]=1;
		}return;
	}TY mid=i+j>>1,sn=id<<1;
	build(i,mid,sn);build(mid+1,j,sn|1);
	fOR(i,0,8){
		tre[id][i]=tre[sn|1][tre[sn][i]];
		fOR(j,0,8)sm[id][i][j]=sm[sn][i][j]+sm[sn|1][tre[sn][i]][j];
	}
}void ask(TY i,TY j,TY id){
	if(l<=i&&j<=r){
		fOR(i,0,8)tmp[i]+=sm[id][x][i];
		x=tre[id][x];return;
	}TY mid=i+j>>1;
	if(l<=mid)ask(i,mid,id<<1);
	if(r>mid)ask(mid+1,j,id<<1|1);
}int main(){
	fOR(i,0,8)to[0][i]=i^1;
	to[1][2]=2;to[1][3]=4;
	to[1][4]=4;to[1][5]=6;
	to[1][6]=6;to[1][7]=4;
	n=qr();m=qr();T=qr();
	fOR(i,0,1<<n)a[i]=qr();scanf("%s",s+1);
	if(n==1){to[1][0]=0;to[1][1]=1;}//n=1需要特殊考虑
	else{
		fOR(i,0,1<<n)if(a[i])ins(i);
		if(nm==n)to[1][0]=4;
		else{dfs(0,0);to[1][0]=2;}
		fOR(i,nm=0,n)ar[i]=0;
		fOR(i,0,1<<n)if(!a[i])ins(i);
		if(nm==n)to[1][1]=4;
		else{dfs(0,0);to[1][1]=2;}
	}fOR(i,0,1<<n)if(a[i])++vl[0];vl[1]=(1<<n)-vl[0];
	fOR(i,0,1<<n)if(t[i])++vl[2];vl[3]=(1<<n)-vl[2];
	vl[4]=1<<n;vl[6]=1;vl[7]=(1<<n)-1;build(1,m,1);
	while(T--){
		kd=qr();
		if(kd==2){
			x=qr();l=qr();
			switch(b[x]){
				case 0:qw(a[l],'\n');break;
				case 1:qw(a[l]^1,'\n');break;
				case 2:qw(t[l],'\n');break;
				case 3:qw(t[l]^1,'\n');break;
				case 4:printf("1\n");break;
				case 5:printf("0\n");break;
				case 6:qw(!l,'\n');break;
				case 7:qw(!!l,'\n');break;
			}continue;
		}if(kd==1){
			x=qr();l=qr();r=qr();x=b[x];
			fOR(i,0,8)tmp[i]=0;ask(1,m,1);
			b[++ct]=x;qw(vl[b[ct]],'\n');
			fOR(i,0,8)tot[ct][i]=tmp[i];
		}else{
			x=qr();l=qr();ans=tot[x][4];
			if(a[l])ans+=tot[x][0];else ans+=tot[x][1];
			if(t[l])ans+=tot[x][2];else ans+=tot[x][3];
			if(l)ans+=tot[x][7];else ans+=tot[x][6];qw(ans,'\n');
		}
	}return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：3)

[Problem Link](https://www.luogu.com.cn/problem/P10926)

**题目大意**

> 给定 $n$，定义 $U=\{0,\dots,2^n-1\}$。
>
> 对于一个集合 $S\subseteq U$，定义 $B(S)=U\setminus S$，$D(S)=\{\oplus_{x\in X} x\mid X\subseteq S\}$。
>
> 给定一个长度为 $m$，由 $B,D$ 组成的操作序列。
>
> 维护一个集合序列 $A$，初始 $A=\{S\}$，支持如下 $q$ 次操作。
>
> - 向 $A$ 的末尾中加入某个 $A_v$ 顺次经过操作序列中 $l\sim r$ 元素后的结果。
> - 查询是否有 $k\in A_v$。
> - 对某个 $A_v$，求他在生成过程中包含了几次 $k$。
>
> 数据范围：$n\le 18,m,q\le 2\times 10^5$。

**思路分析**

观察发现 $D(S)$ 等价于将 $S$ 中元素变成 $\mathrm{span}(S)$ 中所有元素。

注意到 $|S|\ge 2^{n-1}+[0\in S]$ 时一定有 $D(S)=U$。

因为此时 $|D(S)|\ge |S|$，若 $0\not \in S$ 那么 $0\in D(S)$ 此时 $|D(S)|>|S|$，总有 $|D(S)|>2^{n-1}$ 故 $|D(S)|=2^n$。

手玩发现对于所有 $S$，$U\setminus D(S)$ 都满足此条件，此时 $D(U\setminus D(S))=U$。

进一步手玩会发现 $S$ 只可能是如下四种元素或他们的补集：$S$，$D(S)/D(U\setminus S)$ 中不等于 $U$ 的一个，$U$，$\{0\}$，其中 $\{0\}$ 会出现是因为 $D(\varnothing)=\{0\}$。

因此我们可以用线段树快速维护某个 $S$ 经过一段区间的操作后变成了什么，以及这个过程中 $8$ 种可能的 $S$ 分别出现了几次，然后就可以简单的维护上述询问了。

时间复杂度 $\mathcal O(2^nn+m\delta^2\log m+q\delta\log m)$，其中 $\delta =8$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef array<int,8> arr;
const int MAXN=1<<18;
int n,m,q,siz[8];
bool a[4][MAXN];
//0:A, 1:~A, 2:D(A), 3:~D(A), 4:U, 5:0, 6:1, 7:~1
struct LB {
	int t[20],z;
	LB() { memset(t,0,sizeof(t)),z=0; }
	void ins(int x) {
		for(int k=n-1;~k;--k) if(x>>k&1) {
			if(!t[k]) return ++z,t[k]=x,void();
			x^=t[k];
		}
	}
	void dfs(bool *f) {
		int p=0;
		for(int i=0;i<n;++i) if(t[i]) p|=1<<i;
		for(int s=0;s<(1<<n);++s) if((s&p)==s) {
			int x=0;
			for(int i=0;i<n;++i) if(s>>i&1) x^=t[i];
			f[x]=true;
		}
	}
};
arr B={1,0,3,2,5,4,7,6},D={4,4,2,4,4,6,6,4};
char op[MAXN];
int val[MAXN];
arr cnt[MAXN];
struct info {
	arr p,f[8]; //start from x, cnt #y
	info() { p.fill(0); for(int i=0;i<8;++i) f[i].fill(0); }
	friend info operator +(const info &L,const info &R) {
		info z;
		for(int x=0;x<8;++x) {
			z.f[x]=L.f[x],z.p[x]=R.p[L.p[x]];
			for(int y=0;y<8;++y) z.f[x][y]+=R.f[L.p[x]][y];
		}
		return z;
	}
	void add(int &x,arr &g) {
		for(int y=0;y<8;++y) g[y]+=f[x][y];
		x=p[x];
	}
};
struct SegmentTree {
	info tr[MAXN<<1];
	void init(int l=1,int r=m,int p=1) {
		if(l==r) {
			tr[p].p=(op[l]=='D'?D:B);
			for(int x=0;x<8;++x) ++tr[p].f[x][tr[p].p[x]];
			return ;
		}
		int mid=(l+r)>>1;
		init(l,mid,p<<1),init(mid+1,r,p<<1|1);
		tr[p]=tr[p<<1]+tr[p<<1|1];
	}
	void qry(int ul,int ur,int&x,arr&g,int l=1,int r=m,int p=1) {
		if(ul<=l&&r<=ur) return tr[p].add(x,g);
		int mid=(l+r)>>1;
		if(ul<=mid) qry(ul,ur,x,g,l,mid,p<<1);
		if(mid<ur) qry(ul,ur,x,g,mid+1,r,p<<1|1);
	}
}	TR;
int Q(int c,int x) { return a[c>>1][x]^(c&1); }
signed main() {
	ios::sync_with_stdio(false);
	cin>>n>>m>>q;
	for(int i=0;i<(1<<n);++i) cin>>a[0][i];
	if(n==1) D[0]=0,D[1]=1;
	else {
		LB S,T;
		for(int i=0;i<(1<<n);++i) (a[0][i]?S:T).ins(i);
		if(S.z<n) D[0]=2,S.dfs(a[1]);
		if(T.z<n) D[1]=2,T.dfs(a[1]);
	}
	for(int i=0;i<(1<<n);++i) a[2][i]=1;
	a[3][0]=1;
	for(int c:{0,1,2,3}) {
		int x=0;
		for(int i=0;i<(1<<n);++i) x+=a[c][i];
		siz[c<<1]=x,siz[c<<1|1]=(1<<n)-x;
	}
	for(int i=1;i<=m;++i) cin>>op[i];
	TR.init(),val[0]=0;
	for(int z=0,w,v,k,l,r;q--;) {
		cin>>w>>v;
		if(w==1) {
			cin>>l>>r,++z,val[z]=val[v],cnt[z].fill(0);
			TR.qry(l,r,val[z],cnt[z]);
			cout<<siz[val[z]]<<"\n";
		} else {
			cin>>k;
			if(w==2) cout<<Q(val[v],k)<<"\n";
			else {
				int s=0;
				for(int c=0;c<8;++c) if(Q(c,k)) s+=cnt[v][c];
				cout<<s<<"\n";
			}
		}
	}
	return 0;
}
```

---

