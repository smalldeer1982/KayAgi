# [PA 2021] Poborcy podatkowi

## 题目描述

给定一棵 $n$ 个点的树，你可以选择若干条长度为 $4$ 的不相交链（**可以不选**）。

每个选链的方案的收益为所选链的并集的边权和，求最大收益。

## 说明/提示

#### 样例 #1 解释
给出一种最优方案：选择链 $2 \to 6$，$6 \to 10$，$11 \to 15$，$16 \to 19$。
#### 样例 #2 解释
由于每一条长度为 $4$ 的链权值均为负数，所以不选最优。
#### 数据范围
对于 $100\%$ 的数据，$2 \leq n \leq 2 \times 10^5$，$-10^9 \leq a_i \leq 10^9$。

## 样例 #1

### 输入

```
19
1 2 1
2 3 2
3 4 -1
4 5 -1
5 6 2
6 7 11
7 8 12
8 9 13
9 10 14
11 12 3
12 13 0
13 14 0
14 15 0
15 16 1
16 4 0
4 17 0
17 18 0
18 19 2```

### 输出

```
57```

## 样例 #2

### 输入

```
6
1 2 2
2 3 -1
3 4 -1
4 5 -1
5 6 2```

### 输出

```
0```

# 题解

## 作者：zhouhuanyi (赞：10)

令 $dp_{x,d}$ 表示 $x$ 子树内现在根结点上挂着的链的长度为 $d$ 的最大收益，那么转移时只要考虑一个点的子节点如何进行合并，注意到只有 $1,3$ 消，$2,2$ 消两种互消的 $\text{case}$，相当于转移相当于 $\text{fix}$ $a-c=d_{1}(|d_{1}|\leqslant 1)$ 且 $b$ $\text{mod}$ $2=d_{2}$，选择 $a$ 个 $1$，$b$ 个 $2$，$c$ 个 $3$，剩下的全取 $0$，求最大和。考虑给选法分配一个重量与额外重量，将其看做一个二元组，那么令选 $0$ 为 $(1,0)$，选 $1$ 为 $(0,0)$，选 $2$ 为 $(1,1)$，选 $3$ 为 $(2,0)$，现在定义 $(a_{0},b_{0})+(a_{1},b_{1})=(a_{0}+a_{1},b_{0}$ $\text{xor}$ $b_{1})$，现在求拼成 $(a,b)$ 的最大和。如果将 $b$ 的限制去除，这是经典模拟费用流问题，反悔只有 $+2,-1$，所有重量在 $\text{mod}$ $2$ 意义下是凸的，直接闵可夫斯基和即可，加入 $b$ 的限制后其实多记一维 $0/1$ 即可。复杂度 $O(n \log n)$。

---

## 作者：TernaryTree (赞：9)

被同学强迫写了这个题。邪恶的随机化，太神秘了。

---

首先可以做一个非常朴素简单的 dp：$f_{u,j\in[0,3]}$ 表示 $u$ 子树内，选了若干条长为 $4$ 的链，和一条长为 $j$ 的起点为 $u$ 的链的最优价值，条件是它们两两边不相交。

这个东西的转移是这样：显然得拿一些 $f_{v,0},f_{v,2}$ 或者 $f_{v,1},f_{v,1}$ 加上 $(u,v)$ 的边拼起来，也可能是 $f_{v,3}$ 直接连上 $(u,v)$ 的边。

所以令 $g_{i,j\in\{0,1\}}$ 表示考虑了前几个儿子 $v$，选择 $f_{v,0}$ 的比 $f_{v,2}$ 的多 $i$ 个，$f_{v,1}$ 的个数的奇偶性为 $j$ 的最大价值。

这里转移看起来是 $\Theta(n^2)$ 的。然后就上了一个神秘的随机化。

我们考虑最终的决策，如果把儿子随机打乱，再把决策对应到随机序列上，每一个 $f_{v,0}$ 看做 $1$，$f_{v,2}$ 看做 $-1$，那么这个东西在原 dp 式子上面的 $j$ 就是这个随机正负 $1$ 序列的前缀绝对最大值了，这东西 $\Theta(\sqrt n)$，所以 random_shuffle 完就是对的了。

然后我还莫名其妙拿了个最优解。怎么回事呢。

```cpp
#include <bits/stdc++.h>
#define int long long
#define fs first
#define sc second

using namespace std;
using pii = pair<int, int>;

struct ios {
    inline char read() {
        static const int inlen = 1 << 18 | 1;
        static char buf[inlen], *s, *t;
        return (s == t) && (t = (s = buf) + fread(buf, 1, inlen, stdin)), s == t ? -1 : *s++;
    }
    template<typename T> inline ios& operator>> (T &x) {
        static char c11, boo;
        for (c11 = read(), boo = 0; !isdigit(c11); c11 = read()) {
            if (c11 == -1) return *this;
            boo |= c11 == '-';
        }
        for (x = 0; isdigit(c11); c11 = read()) x = x * 10 + (c11 ^ '0');
        boo && (x = -x);
        return *this;
    }
} fin;

struct exios {
    template<typename _CharT, typename _Traits = char_traits<_CharT>>
    struct typ {
        typedef basic_ostream<_CharT, _Traits>& (* end) (basic_ostream<_CharT, _Traits>&);
    };

    template<typename T> friend exios &operator<<(exios &out, T num) {
        if (num < 0) putchar('-'), num = -num;
        if (num >= 10) out << num / 10;
        putchar(num % 10 + '0');
        return out;
    }

    friend exios &operator<<(exios &out, const char * s) { printf("%s", s); return out; }
    friend exios &operator<<(exios &out, string s) { cout << s; return out; }
    friend exios &operator<<(exios &out, typ<char>::end e) { puts(""); return out; }
} fout;

const int maxn = 2e5 + 10;
const int maxb = 5e2 + 10;
const int B = 5e2;

int n;
vector<pii> tr[maxn];
int f[maxn][4], g[maxb << 1][2], h[maxb << 1][2];

void dfs(int u, int fa) {
	vector<pii> sn;
	for (pii e : tr[u]) {
		int v = e.fs;
		if (v == fa) continue;
		dfs(v, u), sn.push_back(e);
	}
	random_shuffle(sn.begin(), sn.end());
	memset(g, -0x3f, sizeof(g)), memset(h, -0x3f, sizeof(h));
	int L = B, R = B;
	g[L][0] = h[L][0] = 0;
	int up = (sn.size() + 1) / 2;
	for (pii e : sn) {
		int v = e.fs, w = e.sc;
		L = max(max(-up + B, 1ll), L - 1), R = min(min(up + B, B * 2), R + 1);
		for (int i = L; i <= R; i++) {
			for (int j = 0; j <= 1; j++) {
				g[i][j] = h[i][j] + f[v][0];
				g[i][j] = max(g[i][j], h[i][j] + w + f[v][3]);
				g[i][j] = max(g[i][j], h[i - 1][j] + w + f[v][0]);
				g[i][j] = max(g[i][j], h[i + 1][j] + w + f[v][2]);
				g[i][j] = max(g[i][j], h[i][j ^ 1] + w + f[v][1]);
			}
		}
		for (int i = L; i <= R; i++) 
			for (int j = 0; j <= 1; j++) 
				h[i][j] = g[i][j];
	}
	f[u][0] = g[B][0], f[u][1] = g[B + 1][0], f[u][2] = g[B][1], f[u][3] = g[B - 1][0];
}

signed main() {
	srand(time(0));
	fin >> n;
	for (int i = 1, u, v, w; i < n; i++) {
		fin >> u >> v >> w;
		tr[u].push_back({v, w});
		tr[v].push_back({u, w});
	}
	dfs(1, 0);
	fout << f[1][0] << endl;
	return 0;
}

```

---

## 作者：cyffff (赞：7)

[$\text{Link}$](https://www.luogu.com.cn/problem/P9047)

大概是对第一篇题解的补充。

## 题意

给定一棵 $n$ 个点的树，你可以选择若干条长度为 $4$ 的链，要求没有一条边同时属于两条选出的链，最大化选出的所有边的边权和。

$n\le 2\times 10^5$。
## 思路

设 $f_{x,i}$ 表示 $x$ 子树的答案，要求 $x$ 下挂了一条长为 $i$ 的链。

考虑在 $x$ 处进行合并。如果选了 $a,b,c$ 条 $1,2,3$ 的链，则我们要对 $\forall p\in[-1,1],q\in[0,1]$ 求出 $a-c=p$，$b\equiv q\pmod2$ 时的最大价值。实际上，这可以看成一个背包问题。假如没有第二条限制，则将 $0,1,2,3$ 的链分别看成重量为 $1,0,1,2$ 的物品即可。加上第二条限制只需要加一个 $0/1$ 维即可。

这是重量较小时的 $(\max,+)$ 背包问题，我们有如下解法：设重量为 $i$ 时的答案为 $w_i$，则 $w_{0,2,\dots,2k}$ 和 $w_{1,3,\dots,2k+1}$ 分别是凸的。前者考虑将重量为 $1$ 的物品的价值从大到小排序并两两分组，转化为重量为 $1$ 的背包，显然答案为凸的。后者同理。

类似于 $(+,\times)$ 卷积下背包的分治 FFT 做法，我们使用分治。先求出 $[l,mid],(mid,r]$ 的答案数组 $a,b$，然后两边分别按下标 $\bmod2$ 分组，枚举两边取哪组做 $(\max,+)$ 卷积即可。由于每组均为凸的，$(\max,+)$ 卷积可以直接使用闵可夫斯基和（归并差分数组）。

事实上，由于只用求 $O(1)$ 个位置的值，我们只需要使用 wqs 二分即可做到同复杂度，但是显然归并差分数组细节少很多。

时间复杂度 $O(n\log n)$。

参考代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
namespace IO{//by cyffff
	
}
#define pii pair<int,int>
#define mpr make_pair
#define fir first
#define sec second
const int N=2e5+10;
const ll INF=1e16;
namespace PolyC{
	#define Poly vector<ll>
	inline void upd(ll &x,ll y){
		x=max(x,y);
	}
	inline Poly operator+(const Poly &a,const Poly &b){
		Poly F=a;
		F.resize(max(a.size(),b.size()));
		for(int i=0;i<b.size();i++)
			F[i]=max(F[i],b[i]);
		return F;
	}
	inline Poly operator*(const Poly &a,const Poly &b){
		int n=a.size(),m=b.size();
		Poly F,G;
		for(int i=1;i<n;i++)
			F.push_back(a[i]-a[i-1]);
		for(int i=1;i<m;i++)
			G.push_back(b[i]-b[i-1]);
		Poly H(n+m-2);
		merge(F.begin(),F.end(),G.begin(),G.end(),H.begin(),greater<ll>());
		Poly R;
		R.push_back(a[0]+b[0]);
		for(auto v:H) R.push_back(R.back()+v);
		return R;
	}
} 
using namespace PolyC;
int lc;
inline Poly Mul(Poly F,Poly G){
	int n=F.size(),m=G.size();
	Poly H(min(n+m-1,lc+2),-INF);
	for(int a=0;a<2;a++)
		for(int b=0;b<2;b++){
			Poly A,B;
			for(int i=a;i<n;i+=2)
				A.push_back(F[i]);
			for(int i=b;i<m;i+=2)
				B.push_back(G[i]);
			A=A*B;
			for(int i=0;i<A.size();i++)
				if(i*2+a+b<H.size())
					upd(H[i*2+a+b],A[i]);
		}
	return H;
}
int n;
ll f[N][4];
vector<pii>a[N];
/*
(1,0)(0,0)(1,1)(2,1) 
*/
vector<Poly>F,G;
inline vector<Poly> solve(int l,int r){
	if(l==r) return {F[l],G[l]};
	int mid=l+r>>1;
	vector<Poly> A=solve(l,mid),B=solve(mid+1,r);
	return {Mul(A[0],B[0])+Mul(A[1],B[1]),Mul(A[0],B[1])+Mul(A[1],B[0])};
}
inline void dfs(int x,int fa){
	int c=0;
	for(auto tmp:a[x]){
		int t=tmp.fir,w=tmp.sec;
		if(t==fa) continue;
		dfs(t,x),c++;
	}
	if(!c){
		f[x][1]=f[x][2]=f[x][3]=-INF;
		return ;
	}
	F.clear(),G.clear(),lc=c; 
	for(auto tmp:a[x]){
		int t=tmp.fir,w=tmp.sec;
		if(t==fa) continue;
		Poly A(3,-INF),B(2,-INF);
		A[1]=max(f[t][0],f[t][3]+w);
		A[0]=f[t][0]+w,A[2]=f[t][2]+w;
		B[1]=f[t][1]+w;
		F.push_back(A),G.push_back(B); 
	}
	vector<Poly>T=solve(0,c-1);
	f[x][0]=T[0][c],f[x][1]=T[0][c-1];
	f[x][2]=T[1][c],f[x][3]=T[0][c+1];
}
int main(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		a[u].push_back(mpr(v,w)),a[v].push_back(mpr(u,w));
	}
	dfs(1,1);
	write(f[1][0]);
	flush();
}
```

---

## 作者：Inui_Sana (赞：6)

现在题解区只有一篇 $O(n\log n)$ 做法，而且是闵可夫斯基和，完全不会。于是讲另一种 $O(n\log n)$ 做法。

首先写 $O(n^2)$ 的树形 dp：设 $dp_{u,i}$ 为处理完 $u$ 的子树，现在 $u$ 处挂着一条长为 $i$ 的链，答案的最大值。这里包含 $(u,fa_u)$ 这条边。

转移的话，对于一个 $u$，设 $f_{i,0/1,0/1/2/3}$ 表示当前已经枚举到的 $u$ 的儿子中，选长度为 $1$ 的和长度为 $3$ 的链的数量的差为 $i$，选了偶数/奇数个长度为 $2$ 的，钦定 $u$ 处挂着一条长度为 $0/1/2/3$ 的链。每次枚举到一个儿子就根据这个儿子处挂一条长度为多少的链转移。

然后考虑优化。注意到我们最后求的是 $f_{0,0,0/1/2/3}$ 的最值，但是我们需要 $i\not=0$ 的位置中间转移。于是想到 **wqs 二分**。

众所周知 wqs 二分要求 $f(i,*)$ 是凸的。但是这一步我不太会严谨证。不过可以感性理解：考虑如果把所有 $dp_{v,1}$ 加上 $\Delta>0$，$dp_{v,3}$ 减去 $\Delta$，那么选的长度为 $1$ 的链会随着 $k$ 增大而增加。

于是先确定挂在 $u$ 上的链长度 $l$，二分一个 $\Delta$，然后再进行一个 dp：设 $f_{i,0/1,0/1,0/1}$ 表示当前处理到第 $i$ 个儿子，选了奇数/偶数个 $2$，奇数/偶数个 $1$ 或 $3$，是否已经选出了挂在 $u$ 上的链。转移类似，不过还要对每个状态记录这个状态对应选了多少 $1$ 和 $3$。最后看最优情况下是否选的 $1$ 多于选的 $3$。

到这里其实就算是解决了，但是 wqs 二分很重要的就是一堆细节。这题更是如此：

1. wqs 二分的方式一定是 **$dp_{v,1}$ 加，$dp_{v,3}$ 减**，而不能是只有 $dp_{v,1}$ 加，否则会取更少的 $(1,3)$ 对。
2. 最后一定是选的 $1$ 数量**大于等于**选 $3$ 的就返回 true。原因显然。
3. 如果遇到被更新的值等于要更新它的值，**优先选选的 $1$ 更多的，选相同 $1$ 的情况下，选 $3$ 更少的**。注意是更少的！似乎是因为这样才能凑出更多 $(1,3)$ 对。
4. 二分上下界大概要开到 $[-10^{12},10^{12}]$，$[-10^9,10^9]$ 不够。
5. 注意到有时候可能需要让 $\Delta$ 有小数部分（事实上 wqs 二分理论上都是需要二分小数，毕竟是斜率），不过只有可能加上 $0.5$，所以先把所有 $w\to w\times 2$，最后再将答案 $\times \frac{1}{2}$ 即可。
6. $1$ 号点上面没有边了，注意特判。

时间复杂度 $O(n\log V)$。但是我的这种 $n^2$ 暴力 dp 常数大，导致最后代码常数也大。似乎有常数小写法？

code：

```cpp
int n,m,deg[N],g[N][2][2][2],h[N][2][2][2];
ll f[N][2][2][2],dp[N][4];
int U;
int tot,head[N];
struct node{
	int to,nxt,cw;
}e[N<<1];
il void add(int u,int v,int w){
	e[++tot]={v,head[u],w},head[u]=tot;
}
il void upd(int i,int j,int k,int l,ll w,int p,int q,int op,int x,int y){
	if(w>f[i][j][k][l]||w==f[i][j][k][l]&&x+p>g[i][j][k][l]||w==f[i][j][k][l]&&x+p==g[i][j][k][l]&&y+q<h[i][j][k][l]){
		f[i][j][k][l]=w;
		if(op==0){
			g[i][j][k][l]=g[i-1][j][k][l]+p;
			h[i][j][k][l]=h[i-1][j][k][l]+q;
		}else if(op==1){
			g[i][j][k][l]=g[i-1][j^1][k][l]+p;
			h[i][j][k][l]=h[i-1][j^1][k][l]+q;
		}else if(op==2){
			g[i][j][k][l]=g[i-1][j][k][0]+p;
			h[i][j][k][l]=h[i-1][j][k][0]+q;
		}else{
			g[i][j][k][l]=g[i-1][j][k^1][l]+p;
			h[i][j][k][l]=h[i-1][j][k^1][l]+q;
		}
	}
}
bool check(ll k,vector<int> &vec,int p,int w){
	int m=(int)vec.size()-1;
	rep(i,0,m){
		rep(j,0,1){
			rep(l,0,1){
				rep(q,0,1){
					f[i][j][l][q]=-1ll*inf*inf;
					g[i][j][l][q]=h[i][j][l][q]=0;
				}
			}
		}
	}
	f[0][0][0][0]=0;
	if(p==1){
		f[0][0][0][1]=w;
	}
	rep(i,1,m){
		rep(j,0,1){
			rep(l,0,1){
				rep(q,0,1){
					upd(i,j,l^1,q,f[i-1][j][l][q]+dp[vec[i]][1]+k,1,0,3,g[i-1][j][l][q],h[i-1][j][l][q]);
					upd(i,j,l^1,q,f[i-1][j][l][q]+dp[vec[i]][3]-k,0,1,3,g[i-1][j][l][q],h[i-1][j][l][q]);
					upd(i,j,l,q,f[i-1][j][l][q]+dp[vec[i]][0],0,0,0,g[i-1][j][l][q],h[i-1][j][l][q]);
					upd(i,j^1,l,q,f[i-1][j][l][q]+dp[vec[i]][2],0,0,1,g[i-1][j][l][q],h[i-1][j][l][q]);
					if(!q&&p){
						upd(i,j,l,1,f[i-1][j][l][q]+dp[vec[i]][p-1]+w,0,0,2,g[i-1][j][l][q],h[i-1][j][l][q]);
					}
					
				}
			}
		}
	}
	return g[m][0][0][min(p,1)]>=h[m][0][0][min(p,1)];
}
void dfs(int u,int fa,int w){
	vector<int> vec;
	vec.eb(0);
	int m=0;
	go(i,u){
		int v=e[i].to;
		if(v==fa){
			continue;
		}
		dfs(v,u,e[i].cw);
		vec.eb(v),m++;
	}
	rep(i,0,3){
		dp[u][i]=-1ll*inf*inf;
	}
	U=u;
	rep(i,0,fa?4:0){
		ll l=-1e12,r=1e12,ans=0;
		while(l<=r){
			ll mid=(l+r)>>1;
			if(check(mid,vec,i,w)){
				ans=mid;
				r=mid-1;
			}else{
				l=mid+1;
			}
		}
		check(ans,vec,i,w);
		dp[u][i%4]=max(dp[u][i%4],f[m][0][0][min(i,1)]);
	}
}
void Yorushika(){
	read(n);
	rep(i,1,n-1){
		int u,v,w;read(u,v,w),w*=2;
		add(u,v,w),add(v,u,w);
		deg[u]++,deg[v]++;
	}
	dfs(1,0,0);
	printf("%lld\n",dp[1][0]/2);
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

---

## 作者：Graphcity (赞：6)

考虑树形 DP。设 $f_{i,0/1/2/3}$ 表示从结点 $i$ 上传了长度为多少的链。合并各个儿子的时候可以采用背包的思路，设 $g_{k,0/1}$ 表示所有儿子中上传长度 1 的比上传长度 3 的多多少，以及上传长度 2 儿子的个数奇偶性。

直接这样显然是 $O(n^2)$ 的，瓶颈在于差值的记录。把上传长度为 1 的链看成 $-1$，长度为 3 的链看成 $+1$，那么如果打乱儿子顺序，最优解中 $-1/1$ 序列的前缀和是 $O(\sqrt{n})$ 级别的。此时设立一个阈值 $B=500$，只记录差值在 $[-B,B]$ 之间的答案即可。

时间复杂度 $O(Bn)$，加上一些剪枝后跑得很快。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e5,B=500;
const ll inf=1e18;

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

struct Node{int frm,to,nxt,w;} Edge[Maxn*2+5];
int tot,Head[Maxn+5];
inline void Addedge(int x,int y,int w)
{
    Edge[++tot]=(Node){x,y,Head[x],w};
    Head[x]=tot;
}
int n,val[Maxn+5]; ll f[Maxn+5][4],h[B*2+5][2],g[B*2+5][2];
mt19937 rnd(time(0));

inline void fmax(ll &x,ll y) {x=max(x,y);}
inline void dfs(int x,int fa)
{
    vector<int> v;
    for(int i=Head[x];i;i=Edge[i].nxt)
    {
        int y=Edge[i].to;
        if(y==fa) continue;
        val[y]=Edge[i].w,dfs(y,x),v.push_back(y);
    }
    shuffle(v.begin(),v.end(),rnd);
    int L=B,R=B,c=v.size()/2+1;
    For(i,0,B*2) For(j,0,1) g[i][j]=-inf; g[B][0]=0;
    for(auto y:v)
    {
        For(j,L-1,R+1) h[j][0]=h[j][1]=-inf;
        For(j,L,R) For(k,0,1) if(g[j][k]>-inf)
        {
            fmax(h[j][k],g[j][k]+f[y][0]);
            fmax(h[j-1][k],g[j][k]+f[y][1]);
            fmax(h[j][k^1],g[j][k]+f[y][2]);
            fmax(h[j+1][k],g[j][k]+f[y][3]);
        } L=max(L-1,max(B-c,0)),R=min(R+1,min(B+c,B*2));
        For(j,L,R) g[j][0]=h[j][0],g[j][1]=h[j][1];
    }
    if(x>1) f[x][0]=max(max(0ll,g[B][0]),g[B+1][0]+val[x]); else f[x][0]=max(0ll,g[B][0]);
    f[x][1]=max(0ll,g[B][0])+val[x],f[x][2]=g[B-1][0]+val[x],f[x][3]=g[B][1]+val[x];
}

int main()
{
    n=read();
    For(i,1,n-1)
    {
        int a=read(),b=read(),c=read();
        Addedge(a,b,c),Addedge(b,a,c);
    }
    dfs(1,0);
    cout<<f[1][0]<<endl;
    return 0;
}
```

---

## 作者：CommandSR (赞：2)

## 题意

给定一棵 $n$ 个点的树，你可以选择若干条长度为 $4$ 的不相交链（**可以不选**）。

每个选链的方案的收益为所选链的并集的边权和，求最大收益。

## 题解

首先有一个朴素 dp，令 $dp_{u,j}$ 为 $u$ 子树内选了若干条链，还剩一条长度为 $j$ 的不完整的链的最大收益。

这个 dp 的转移显然是从两个 $dp_{v,1}$ 或者一个 $dp_{v,0}$ 和一个 $dp_{v,2}$ 进行合并。还有一种情况是从一个 $dp_{v,3}$ 直接转移。时间复杂度 $O(n^2)$。

考虑改变状态，设一个 $f_{u,i,j}$ 表示考虑 $u$ 的子树，长度为 $1$ 的链个数奇偶性为 $i$，$j>0$ 表示内部长度为 $0$ 的链比长度为 $2$ 的链多 $j$，$j<0$ 表示内部长度为 $2$ 的链比长度为 $0$ 的链多 $j$。

发现最终的状态是 $0 \leq i \leq 1$，$-1 \leq j \leq 1$ 的。这里有一个经典 trick 是长度为 $M$ 的随机 01 序列期望前缀最大值是 $O(\sqrt{M})$ 的。所以可以把所有儿子随机打乱然后 dp，因为状态有负数所以要设一个阈值 $B$ 存储状态。时间复杂度 $O(n \sqrt{n})$ 且跑不满。

## Code

```cpp
// Problem: P9047
#include <bits/stdc++.h>
#define db double
#define int long long
#define ll long long
#define pc putchar
#define gc getchar
#define sz(x) ((int)x.size())
#define F(i, a, b) for (int i = (a); i <= (b); ++i)
#define D(i, a, b) for (int i = (a); i >= (b); --i)
using namespace std;
namespace IO {
#define typ ll
	inline typ rd() {
		typ x = 0; bool f = 1; char ch = gc();
		while (ch < '0' || ch > '9') { if (ch == '-') f = 0; ch = gc(); }
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gc();
		return (f ? x : (-x));
	}
	inline void wr(typ x) {
		if (x < 0) pc('-'), x = -x;
		if (x > 9) wr(x / 10); pc(x % 10 + '0');
	}
}
using namespace IO;
// ----------------- Main Code -----------------
const int N = 2e5 + 5, B = 500, inf = 1e16;
struct E { int v, w; }; vector<E> G[N];
int n, f[2][1145], g[2][1145], dp[N][4];
void Dfs(int u, int p) {
	random_shuffle(G[u].begin(), G[u].end());
	for (E tmp : G[u]) {
		int v = tmp.v;
		if (v == p) continue;
		Dfs(v, u);
	}
	F(i, 0, 1) F(j, 0, 2*B) f[i][j] = -inf;
	f[0][0+B] = 0;
	for (E tmp : G[u]) {
		int v = tmp.v, w = tmp.w;
		if (v == p) continue;
		F(i, 0, 1) F(j, 0, 2*B) g[i][j] = -inf;
		F(i, 0, 1) {
			F(j, -B, B) {	
				F(k, 0, 3) {
					if (f[i][j+B] == -inf || dp[v][k] == -inf) continue;
					int d = (k == 0 ? 1 : (k == 2 ? -1 : 0));
					if (j+d+B >= 0 && j+d+B <= 2*B) g[i^(k==1)][j+d+B] = max(g[i^(k==1)][j+d+B], f[i][j+B] + dp[v][k] + w);
					if (!k) g[i][j+B] = max(g[i][j+B], f[i][j+B] + dp[v][k]);
				}
			}
		}
		memcpy(f, g, sizeof f);
	}
	dp[u][0] = f[0][0+B], dp[u][1] = f[0][1+B], dp[u][2] = f[1][0+B], dp[u][3] = f[0][-1+B];
}
signed main() {
	n = rd();
	F(i, 1, n-1) {
		int u = rd(), v = rd(), w = rd();
		G[u].push_back((E){v, w}), G[v].push_back((E){u, w});
	}
	Dfs(1, 0);
	wr(max(0ll, dp[1][0])), pc('\n');
	return 0;
}
```

---

## 作者：Petit_Souris (赞：1)

先考虑一个暴力的 dp：设 $f_{u,i}$ 表示 $u$ 子树内选出若干条链，有一条长度为 $i$ 的链要给到 $fa_u$ 的最大收益。

转移的时候，把子树内的 $i$ 都拉出来。对于 $i=3$ 的，再加上 $(u,v)$ 这条边就凑完了，直接加进答案；对于 $i=0,2$ 的，他们需要两两之间组成链；对于 $i=1$ 的也需要两两组成链。于是内层可以再设计一个 dp：$g_{x,i,j}$ 表示决策完了前 $x$ 个子树，目前有 $i$ 个 $1$ 没匹配上，$j$ 记录 $0,2$ 的匹配情况（$j>0$ 表示有 $j$ 个 $0$ 没匹配上，$j<0$ 表示有 $-j$ 个 $2$ 没匹配上，$j=0$ 表示恰好完美匹配）的最大收益。这样得到了一个 $\mathcal O(n^2)$ 的做法，因为 $i$ 这位只需要记录 $0,1$ 即可。

考虑优化：最终的结局状态 $i\in \{0,1\}$，$j\in \{-1,0,1\}$。考虑一个经典结论：长度为 $L$ 的 $+1/-1$ 构成的序列，期望的最大前缀和是 $\mathcal O(\sqrt L)$ 的。于是我们可以把所有儿子打乱，再设一个阈值做 dp，这样就是正确的了。复杂度 $\mathcal O(n\sqrt n)$，$n=2\times 10^5$ 也可以在 1s 内轻松通过。


```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
mt19937 rnd(time(0));
const ll N=2e5+9,B=400,INF=1e15;
ll n,dp[N][4],f[2][B*2+9],g[2][B*2+9];
vector<pii>to[N];
void dfs(ll x,ll fa){
    shuffle(to[x].begin(),to[x].end(),rnd);
    for(pii e:to[x]){
        ll y=e.first;
        if(y==fa)continue;
        dfs(y,x);
    }
    rep(i,-B,B)f[0][i+B]=f[1][i+B]=-INF;
    f[0][0+B]=0;
    for(pii e:to[x]){
        ll y=e.first,w=e.second;
        if(y==fa)continue;
        rep(i,-B,B)g[0][i+B]=g[1][i+B]=-INF;
        rep(i,0,1){
            rep(j,-B,B){
                ll v=f[i][j+B];
                if(v==-INF)continue;
                rep(k,0,3){
                    if(dp[y][k]==-INF)continue;
                    ll d=0;
                    if(k==0)d=1;
                    else if(k==2)d=-1;
                    if(j+d>=-B||j+d<=B)g[i^(k==1)][j+d+B]=max(g[i^(k==1)][j+d+B],v+dp[y][k]+w);
                    if(!k)g[i][j+B]=max(g[i][j+B],v+dp[y][k]);
                }
            }
        }
        rep(i,0,2*B)f[0][i]=g[0][i],f[1][i]=g[1][i];
    }
    dp[x][0]=f[0][0+B];
    dp[x][1]=f[0][1+B];
    dp[x][2]=f[1][0+B];
    dp[x][3]=f[0][-1+B];
}
bool Med;
int main(){
    // freopen("a.in","r",stdin);
    // freopen("a.out","w",stdout);
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    n=read();
    rep(i,2,n){
        ll x=read(),y=read(),z=read();
        to[x].push_back({y,z});
        to[y].push_back({x,z});
    }
    dfs(1,0);
    write(max(0ll,dp[1][0]));
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

## 作者：Tachibana_Kimika (赞：1)

### 题目解析

求树上若干个不相交长度为 $4$ 的链的最大权值和。

首先，点相交不算链相交，没看到的请自行画一下样例一。

然后，我们可以很容易得到一个 dp 式子就是 $dp_{i,j}$ 代表以 $i$ 为根的子树里的最大权值，并且往上传了一个长度为 $j$ 的链。我们在子树合并的时候可以很喵喵的 $n^2$ 瞎做，但是显然过不了这个题。

唉，所以我们只能回头看看什么链是可以合并的。我们发现长度为 1 的链和长度为 3 的链可以进行合并，所以说啊，我们可以记录长度为 1 和长度为 3 的链的个数差。

但是还是没有解决这个 $n^2$ 的问题啊喵喵。但是这个差值我们就想到了一个神秘的结论。假设一个数列只有 $1$ 和 $-1$，那么将他随机排序之后，前缀和大概率不会超过 $\sqrt n$。证明可以看[这个](https://www.cnblogs.com/Arextre/p/16126298.html)大佬。

然后我们就可以缩小很多状态，实际上只有 $n\sqrt n$ 个状态了，就可以过这道题。对于长度为 $2$ 的链，我们只需要两个状态，就是链数量的奇偶性。

具体实现看代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
const int B=2000;//明明根号就可以过我开到2000才过的，是不是我random shuffle 太菜了啊。

struct node{
	int to,nxt,w;
}edge[N*2]; int head[N],cnt;
void add(int u,int v,int w){
	edge[++cnt].to=v;
	edge[cnt].w=w;
	edge[cnt].nxt=head[u];
	head[u]=cnt;
}
void adde(int u,int v,int w){
	add(u,v,w); add(v,u,w);
}

int dp[N][4];
int g[B<<1+10][2];
int tmp[B<<1+10][2];
int faw[N];//自己到父亲这条边的权值

void dfs(int u,int f){
	vector<int>q;
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].to; if(v==f) continue;
		faw[v]=edge[i].w; dfs(v,u); q.push_back(v);
	}
	random_shuffle(q.begin(),q.end());
	int l=B,r=B,del=q.size()/2+1;//lr代表差值的范围
	for(int i=0;i<=B*2;i++) for(int j=0;j<=1;j++) g[i][j]=-1e18;
	g[B][0]=0;
	for(auto v:q){
		for(int i=l-1;i<=r+1;i++) tmp[i][0]=tmp[i][1]=-1e18;
		for(int i=l-1;i<=r+1;i++) for(int j=0;j<=1;j++) if(g[i][j]!=-1e18){
			tmp[i][j]=max(tmp[i][j],g[i][j]+dp[v][0]);//长度为0的链不用管
			tmp[i-1][j]=max(tmp[i-1][j],g[i][j]+dp[v][1]);//长度为1，就把差值减1
			tmp[i][1-j]=max(tmp[i][1-j],g[i][j]+dp[v][2]);//长度为2就异或1
			tmp[i+1][j]=max(tmp[i+1][j],g[i][j]+dp[v][3]); //长度为3就把差值加1
		}
		l=max(l-1,B-del); l=max(l,1ll);
		r=min(r+1,B+del); r=min(r,B*2);//移动一下差值范围
		for(int i=l;i<=r;i++) g[i][0]=tmp[i][0],g[i][1]=tmp[i][1];
	}
	if(u!=1) dp[u][0]=max(max(0ll,g[B][0]),g[B+1][0]+faw[u]);//可以是长度为0的链这里不选，也可以是长度为三的链选上这里变成了长度为 4 的链
	else dp[u][0]=max(0ll,g[B][0]);//根不能再选长度为3，因为上面没了
	dp[u][1]=max(0ll,g[B][0])+faw[u]; dp[u][2]=g[B-1][0]+faw[u]; dp[u][3]=g[B][1]+faw[u];//就是选上这个点到他父亲的这条边，链长度要加一
}

void fake_main(){
	mt19937 srand(time(NULL));
	int n; cin>>n;
	for(int i=1;i<n;i++){
		int u,v,w; cin>>u>>v>>w;
		adde(u,v,w);
	}
	dfs(1,0);
	cout<<dp[1][0]<<"\n";
}

signed main(){
	ios::sync_with_stdio(false);
	int t; t=1;
	while(t--) fake_main();
}
```

---

