# [ABC213H] Stroll

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc213/tasks/abc213_h

高橋君は家の周りをあてもなく歩き回ることにしました。  
 散歩の間、高橋君は地点 $ 1 $, 地点 $ 2 $, $ \dots $, 地点 $ N $ の $ N $ か所の地点を歩き回ります。ここで、地点 $ 1 $ は自宅です。  
 地点間に道が存在するような地点の組は $ M $ 組あります。 $ i $ 番目の組を $ (a_i,\ b_i) $ とした時、地点 $ a_i $ と地点 $ b_i $ を双方向に結ぶ長さ $ d $ $ (1\ \leq\ d\ \leq\ T) $ キロメートルの道は $ p_{i,\ d} $ 本あります。

高橋君は自宅を出発して $ T $ キロメートル歩いて自宅に戻る散歩コースの本数が知りたくなりました。ここで、長さ $ T $ キロメートルの散歩コースは次のように定義されます。

- 地点と道を交互に並べた列 $ v_0\ =\ 1,\ e_0,\ v_1,\ \dots,e_{k-1},\ v_k\ =\ 1 $ であって、$ e_i $ $ (0\ \leq\ i\ \leq\ k-1) $ が $ v_i $ と $ v_{i+1} $ を結んでいて、 $ e_i $ の長さの和が $ T $ キロメートルである。

あなたは高橋君のかわりに条件を満たす散歩コースの本数を $ 998244353 $ で割ったあまりを求めてください。ただし、$ 2 $ つの散歩コースは列として異なるときに異なるとみなされます。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10 $
- $ 1\ \leq\ M\ \leq\ \min\ \left(10,\ \frac{N(N-1)}{2}\ \right) $
- $ 1\ \leq\ T\ \leq\ 4\ \times\ 10^4 $
- $ 1\ \leq\ a_i\ \lt\ b_i\ \leq\ N $
- $ i\ \neq\ j $ ならば $ (a_i,\ b_i)\ \neq\ (a_j,\ b_j) $
- $ 0\ \leq\ p_{i,j}\ \lt\ 998244353 $

### Sample Explanation 1

高橋君の家の周りには、 - 地点 $ 1 $ と地点 $ 2 $ を結ぶ長さ $ 1 $ キロメートルの道が $ 1 $ 本 - 地点 $ 1 $ と地点 $ 3 $ を結ぶ長さ $ 1 $ キロメートルの道が $ 2 $ 本 あります。条件を満たすコースは - 地点 $ 1 $ $ \to $ 地点 $ 2 $ $ \to $ 地点 $ 1 $ の順に巡るコースが $ 1\ \times\ 1\ =\ 1 $ 通り - 地点 $ 1 $ $ \to $ 地点 $ 3 $ $ \to $ 地点 $ 1 $ の順に巡るコースが $ 2\ \times\ 2\ =\ 4 $ 通り の計 $ 5 $ 通りです。

### Sample Explanation 2

高橋君の家の周りには、 - 地点 $ 1 $ と地点 $ 2 $ を結ぶ長さ $ 1 $ キロメートルの道が $ 3 $ 本 - 地点 $ 1 $ と地点 $ 3 $ を結ぶ長さ $ 2 $ キロメートルの道が $ 1 $ 本 - 地点 $ 2 $ と地点 $ 3 $ を結ぶ長さ $ 1 $ キロメートルの道が $ 2 $ 本 あります。条件を満たすコースは、経由する地点を列挙すると - 地点 $ 1 $ $ \to $ 地点 $ 2 $ $ \to $ 地点 $ 1 $ $ \to $ 地点 $ 2 $ $ \to $ 地点 $ 1 $ - 地点 $ 1 $ $ \to $ 地点 $ 2 $ $ \to $ 地点 $ 3 $ $ \to $ 地点 $ 1 $ - 地点 $ 1 $ $ \to $ 地点 $ 2 $ $ \to $ 地点 $ 3 $ $ \to $ 地点 $ 2 $ $ \to $ 地点 $ 1 $ - 地点 $ 1 $ $ \to $ 地点 $ 3 $ $ \to $ 地点 $ 1 $ - 地点 $ 1 $ $ \to $ 地点 $ 3 $ $ \to $ 地点 $ 2 $ $ \to $ 地点 $ 1 $ の $ 5 $ パターンがあり、本数は上から順に $ 81 $ 通り、 $ 6 $ 通り、 $ 36 $ 通り、 $ 1 $ 通り、 $ 6 $ 通りとなります。

## 样例 #1

### 输入

```
3 2 2
1 2
1 0
1 3
2 0```

### 输出

```
5```

## 样例 #2

### 输入

```
3 3 4
1 2
3 0 0 0
1 3
0 1 0 0
2 3
2 0 0 0```

### 输出

```
130```

## 样例 #3

### 输入

```
2 1 5
1 2
31415 92653 58979 32384 62643```

### 输出

```
844557977```

# 题解

## 作者：EuphoricStar (赞：4)

考虑一个朴素 dp，$f_{t, u}$ 表示 $t$ 时刻走到 $u$ 点的方案数。有转移：

$$f_{t, u} = \sum\limits_{(u, v) = E_i} \sum\limits_{k = 0}^{t - 1} f_{k, v} \times p_{i, t - k}$$

直接做时间复杂度 $O(mT^2)$，无法接受。

发现转移是加法卷积形式，又因为这个 dp 是在线的，考虑分治 NTT。设当前递归区间为 $[l, r]$，设 $mid = \left\lfloor\frac{l + r}{2}\right\rfloor$，计算出 $f_{l \sim mid, v}$ 后，卷上 $p_{i, 0 \sim r - l}$ 可以转移至 $f_{mid + 1 \sim r, u}$。时间复杂度降至 $O(mT \log^2 T)$，可以通过。

[code](https://atcoder.jp/contests/abc213/submissions/41882304)

---

## 作者：Otomachi_Una_ (赞：3)

这个题目的翻译太有提示性了。。。

## 题目简述

> - $n$ 个点，若干条边的图。给 $m$ 个关系对 $(u_i,v_i)$ 和值 $a_1,a_2,\dots,a_t$ 表示 $u_i,v_i$ 之间有 $a_j$ 条长度为 $j$ 的双向道路。
> - 求从 $1$ 出发，最终回到 $1$，长度为 $t$ 的路径个数。答案对 $998244353$ 取模。
> - $n,m\leq 10,t\leq 4\times 10^4,a_i\leq 998244353$。

## 解题思路

把每条边的边权 $\{a_t\}$ 视作为函数 $w(x)=\sum a_ix^i$，定义出每个点 $u$ 长度为 $i$ 的路径个数 $c_{u,i}$ 的生成函数 $f_u(x)=\sum_{i=0}^{+\infty} c_{u,i}$。不难得出关系式：
$$
f_u=\sum_{(u,v,w)\in E} w\times f_v
$$
这个长得就很高斯消元，但是实际上手发现这个玩意复杂度大概是 $O(n^3t\log t)$ 的，而且由于需要大量的求逆和卷积，常数非常大，按照 AT 不卡常的惯例果断放弃。

另一个思路是尝试分治 NTT，我们只需要对于一个分治区间暴力求每条边 $f_u[l,mid]$ 向 $f_v[mid+1,r]$ 的贡献即可。时间复杂度是 $O(mt\log t)$，完全可以通过。

## 实现细节

如果您使用 `vector` 套 `vector` 进行存边，那么使用 `auto` 遍历元素的时候只能引用（`&`），不然代码会复制整个 `vector` 导致复杂度飙到 $O(t^2\log t)$。

下面的代码使用的是新板子，速度稍微快一点，但是由于我分治的写法不算很好，最大点大概在 $\text{2.5s}$ 左右。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int I love nanami 
#define MP make_pair
#define vll vector<long long>
const int MAXN=4e5+5;
const int MOD=998244353;
const ll inv2=(MOD+1)/2;
namespace polynomial{// yjl poly plank 2.0 ver
int bfly[MAXN];ll inver[MAXN];
int clogg(int x){return (int)ceil(log2(x));} 
ll ksm(ll a,int b){ll res=1;while(b){if(b&1)res=res*a%MOD;a=a*a%MOD,b>>=1;}return res;}
void butterfly(int l){
	static int las;
	if(las!=l){
		las=l; 
		for(int i=1;i<(1<<l);i++)
			bfly[i]=(bfly[i>>1]>>1)|((i&1)<<l-1);
	} 
}
void NTT(vll &f,int l,int typ){
	butterfly(l);f.resize(1<<l);
	for(int i=0;i<(1<<l);i++)
		if(bfly[i]<i) swap(f[i],f[bfly[i]]);
	for(int i=0;i<l;i++){
		ll step=ksm(3,MOD-1+(MOD-1>>i+1)*typ);
		for(int j=0;j<(1<<l);j+=(1<<i+1)){
			ll cur=1;
			for(int k=j;k<j+(1<<i);k++){
				ll u=f[k],v=f[k+(1<<i)]*cur%MOD;
				f[k]=(u+v)%MOD;f[k+(1<<i)]=(u-v+MOD)%MOD;
				cur=cur*step%MOD;
			}
		}
	}
	if(typ==-1){
		ll val=ksm(1<<l,MOD-2);
		for(int i=0;i<(1<<l);i++)
			f[i]=val*f[i]%MOD;
	}
	return;
}
vll operator *(vll f,vll g){
	int n=f.size()+g.size(),l=clogg(f.size()+g.size());
	NTT(f,l,1);NTT(g,l,1);
	for(int i=0;i<(1<<l);i++)
		f[i]=f[i]*g[i]%MOD;
	NTT(f,l,-1);f.resize(n);
	return f;
}
}using namespace polynomial;
int n,m,t;
vector<pair<int,vll> > ve[11];
vll g[11];
void solve(int l,int r){
	if(l==r) return;
	int mid=l+r>>1;
	solve(l,mid);
	for(int i=1;i<=n;i++)
		for(auto &j:ve[i]){
			int v=j.first;vll w=vll(begin(j.second),begin(j.second)+r-l+1);
			vll f=vll(begin(g[v])+l,begin(g[v])+mid+1);
			f=f*w;
			for(int k=mid+1;k<=r;k++)
				g[i][k]+=f[k-l],g[i][k]%=MOD;
		}
	solve(mid+1,r);
	return;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m>>t;
	for(int i=1;i<=n;i++) g[i].resize(t+1); 
	for(int i=1;i<=m;i++){
		int u,v;cin>>u>>v;
		vll f(t+1);
		for(int j=1;j<=t;j++) cin>>f[j];
		ve[u].push_back(MP(v,f));
		ve[v].push_back(MP(u,f));
	}
	g[1][0]=1;
	solve(0,t);
	cout<<g[1][t]<<endl;
	return 0;
}
```



---

## 作者：hyman00 (赞：2)

看到很多题解都是用分治 NTT 过的啊，提供一个只要多项式乘法和求逆的做法

翻译已经简化题意了，下文直接用一个多项式表示权值。

首先定义 $F_i(x)$ 为从节点 $1$ 走到节点 $i$ 的权值，设节点 $i$ 直接走一条边到节点 $j$ 的权值 $G_{i,j}(x)$，若有边则为边权，否则为 $0$。

则有转移 $F_i(x)=\sum_{j}G_{j,i}(x)F_j(x)+[i=1]$ 的式子，这时候就可以直接暴力消元，把 $F_i(x)$ 看作未知数，$G_{i,j}(x)$ 作为系数，求解消元。

可以从 $n$ 到 $2$ 逐个把未知数消去，并用其他未知数替代它，于是就需要 $O(n)$ 次多项式求逆，和 $O(n^3)$ 次乘法，但是这样会超时。

需要一些常数优化，如果多项式乘法一边是个 $0$ 或者 $1$ 就别乘了，直接返回，可以发现因为 m 较小，会去除不少冗余的计算，可以跑到 1.5s 以内。

代码

```c++
poly to[10][10];
void run(){
	cin>>n>>m>>t;
	t++;
	rep(i,n)rep(j,n)to[i][j]=0;
	rep(i,m){
		int x,y;
		cin>>x>>y;
		x--;y--;
		poly p;p.cut(t);
		rept(i,1,t)cin>>p.a[i];
		to[x][y]=to[y][x]=p;
	}
	for(int i=n-1;i;i--){
//		rep(j,i+1)cout<<i<<","<<j<<":\n",to[i][j].out();
		poly cur=inv(1-to[i][i]);
		if(cur!=1)rep(j,i)to[i][j]=mult(cur,to[i][j]);
		rep(j,i){
			poly dc=to[j][i];
			if(dc==0)continue;
			rep(k,i)to[j][k]=to[j][k]+mult(dc,to[i][k]);
		}
	}
	poly cur=inv(1-to[0][0]);
	cout<<cur.a[t-1]<<"\n";
}
```

---

## 作者：OldDriverTree (赞：1)

感觉洛谷上上的翻译还不如 AtCoder-Better 的翻译？

# Solution

设 $f_{u,x}$ 表示从 $1$ 出发到 $u$ 且用时为 $x$ 的方案数。

转移方程就是 $f_{u,x}=\sum\limits_v\sum\limits_{y=1}^{x-1} f_{v,y}\times p_{i,x-y}$。

这显然是一个分治 $\text{NTT}$ 的形式，对于当前区间 $[l,r]$，先递归计算 $x\in [l,mid]$ 的 $f$，再计算 $ [l,mid]$ 对 $[mid+1,r]$ 区间的贡献，最后递归计算 $x\in [mid+1,r]$ 的 $f$。

对于第二步计算 $[l,mid]$ 对 $[mid+1,r]$，分别对于一条边 $(x,y)$，计算 $f_{x,[l,mid]}$ 对 $f_{y,[mid+1,r]}$ 的贡献，将 $f_{y,[l,mid]}$ 与 $p_{i,[1,r-l]}$ 进行卷积，再加到 $f_{x,[mid+1,r]}$ 上即可（由于这里是无向边，读入时把两个方向的边都加进去就行了）。

最后答案就为 $f_{1,T}$。时间复杂度为 $O(mT\log^2 T)$。

# Code
```c++
#include<bits/stdc++.h>
using namespace std;
const int N=1<<16;
const int mod=998244353;
int x[90],y[90],w[90][N];
int T,n,m,tot,f[11][N];
int rev[N],a[N],b[N];

int read() {
	int x=0; char c=0; while (!isdigit(c) ) c=getchar();
	while (isdigit(c) ) x=(x<<3)+(x<<1)+(c&15),c=getchar();
	return x;
}
int power(int a,int b)
{
	int res=1;
	while (b) {
		if (b&1) res=1ll*res*a%mod;
		a=1ll*a*a%mod,b>>=1;
	}
	return res;
}
void NTT(int *a)
{
	for (int i=0;i<tot;i++)
	if (i<rev[i]) swap(a[i],a[rev[i] ]);
	for (int len=1;len<tot;len<<=1)
	{
		int g=power(3,(mod-1)/(len<<1) );
		for (int i=0;i<tot;i+=len<<1)
			for (int j=0,gk=1;j<len;j++,gk=1ll*gk*g%mod) {
				int x=a[i|j],y=1ll*a[i|len|j]*gk%mod;
				a[i|j]=(x+y)%mod,a[i|len|j]=(x-y+mod)%mod;
			}
	}
}
void INTT(int *a) {
	NTT(a),reverse(a+1,a+tot); int inv=power(tot,mod-2);
	for (int i=0;i<tot;i++) a[i]=1ll*a[i]*inv%mod;
}
void mul(int *a,int *b,int n,int m) {
	tot=1; int l=-1; while (tot<=n+m) tot<<=1,l++;
	for (int i=0;i<tot;i++) rev[i]=rev[i>>1]>>1|(i&1)<<l;
	for (int i=n+1;i<tot;i++) a[i]=0; NTT(a);
	for (int i=m+1;i<tot;i++) b[i]=0; NTT(b);
	for (int i=0;i<tot;i++) a[i]=1ll*a[i]*b[i]%mod;
	INTT(a);
}
void solve(int l,int r)
{
	if (l==r) return;
	int mid=(l+r)>>1;
	solve(l,mid);
	for (int i=0;i<m;i++) {
		for (int j=0;j<=mid-l;j++) a[j]=f[y[i] ][l+j];
		for (int j=0;j<=r-l;j++) b[j]=w[i][j]; mul(a,b,mid-l,r-l);
		for (int j=mid+1;j<=r;j++) f[x[i] ][j]=(f[x[i] ][j]+a[j-l])%mod;
	}
	solve(mid+1,r);
}
int main()
{
	n=read(),m=read(),T=read();
	for (int i=0;i<m;i++) {
		x[i<<1]=y[i<<1|1]=read(),y[i<<1]=x[i<<1|1]=read();
		for (int j=1;j<=T;j++) w[i<<1][j]=w[i<<1|1][j]=read();
	}
	m<<=1,f[1][0]=1,solve(0,T);
	return !printf("%d",f[1][T]);
}
```

---

## 作者：Petit_Souris (赞：0)

考虑一个暴力做法：设 $f_{t,u}$ 为 $t$ 单位时间走到 $u$ 的方案数，转移即为枚举 $u$ 的一条出边指向 $v$，时间为 $w$，那么 $f_{t,u}$ 可以转移到 $f_{t+w,v}$。

发现这个形式类似一个在线卷积，因此考虑分治 NTT。具体而言，假设目前正在求解 $t\in [l,r]$ 时的答案，先递归处理 $[l,mid]$，再计算 $[l,mid]$ 对 $[mid+1,r]$ 的贡献。枚举两个点 $u,v$，计算 $u$ 的左半区间对 $v$ 的右半区间的转移，只需要用左半边的 $f$ 值卷上这条边的 $[0,r-l]$ 时间内的方案数即可。最后再递归计算 $[mid+1,r]$。时间复杂度 $\mathcal O(n^2 T\log^2 T)$。

```cpp
using Poly::poly;
ll n,m,T,w[12][12][40009],f[12][40009];
void solve(ll l,ll r){
    if(l==r)return ;
    ll mid=(l+r)>>1;
    solve(l,mid);
    rep(i,1,n){
        rep(j,1,n){
            if(i==j)continue;
            poly F,G;
            F.resize(mid-l+1);
            rep(k,l,mid)F[k-l]=f[i][k];
            G.resize(r-l+1);
            rep(k,0,r-l)G[k]=w[i][j][k];
            F=F*G;
            rep(k,mid+1,r){
                if(k-l>=(ll)F.size())break;
                f[j][k]=(f[j][k]+F[k-l])%Mod;
            }
        }
    }
    solve(mid+1,r);
}
bool Med;
int main(){
	cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    n=read(),m=read(),T=read();
    Poly::pwg(T*4);
    rep(i,1,m){
        ll x=read(),y=read();
        rep(j,1,T)w[x][y][j]=w[y][x][j]=read();
    }
    f[1][0]=1;
    solve(0,T);
    write(f[1][T]);
	return 0;
}

```

---

