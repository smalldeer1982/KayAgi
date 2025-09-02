# No Game No Life

## 题目描述

Alice 和 Bob 在玩游戏。

在他们面前有一张 $n$ 个点，$m$ 条边的有向无环图，每个点有若干芯片，数量为 $a_i$。Alice 和 Bob 轮流操作，Alice 先手。定义玩家的一次操作为将图上的某一顶点的一个芯片根据有向边移到另外一个顶点上。每人每次只能操作一次。如果一个人不能操作，那么他输掉游戏。

在游戏开始后，每一秒在图上都会发生如下的操作：

1. 在 $[1,n+1]$ 范围内等概率选取一个整数 $v$。
2. 如果 $v \leq n$，那么在 $v$ 顶点放置一个芯片，这一秒操作结束。
3. 如果 $v = n + 1$，那么 Alice 和 Bob 开始游戏，游戏结束后所有操作停止。

保证 Alice 和 Bob 都绝对聪明。

现在请你求出 Alice 赢的概率。对 $998244353$ 取模。

即若概率为最简分数 $\dfrac{p}{q}$（保证 $q \not \equiv 0 \bmod 998244353$），你只需要输出 $x$ 使得 $qx \equiv p \bmod 998244353$，可以证明这样的 $x$ 是唯一的。

## 说明/提示

$1 \leq n \leq 10^5$，$1 \leq m \leq 10^5$。

## 样例 #1

### 输入

```
1 0```

### 输出

```
0```

## 样例 #2

### 输入

```
2 1
1 2```

### 输出

```
332748118```

## 样例 #3

### 输入

```
5 5
1 4
5 2
4 3
1 5
5 4```

### 输出

```
931694730```

# 题解

## 作者：feecle6418 (赞：9)

首先暴力算出每个点的 SG 函数值。这部分是 $O(n\sqrt n)$ 的。

考虑最后的博弈，先手败当且仅当所有选出点的 SG 值异或和等于 $0$。注意到 SG 的异或和不大于 512，则预处理 $cnt_x$ 表示 SG 等于 $x$ 的点数，设 $f_x$ 表示所有选出点的 SG 值异或起来等于 $x$ 的概率，对所有 $x\ne 0$ 有：

$$f_x=\dfrac{1}{n+1}\sum\limits_{i=0}^{511} f_ycnt_{x\ \mathrm{xor}\ y}$$

对所有 $0\le x<512$ 有：

$$\sum_{0\le x<512}=1$$

由以上 $512$ 个方程可以 $O(512^3)$ 解出 $f_0$ 的值。（注意这里巧妙地回避了 $f_0$ 到底应如何转移的问题）

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
int Power(int x,int y){
	if(y<0)return 0;
	int r=1;
	while(y){
		if(y&1)r=1ll*r*x%mod;
		x=1ll*x*x%mod,y>>=1;
	}
	return r;
}
int f[525][525],ans[525],n,m,v[100005],sg[100005],cnt[525];
vector<int> g[100005];
void Gauss(){
	for(int i=0;i<512;i++){
		for(int j=i+1;j<512;j++){
			if(!f[j][i])continue;
			int t=1ll*f[j][i]*Power(f[i][i],mod-2)%mod;
			for(int k=i;k<=512;k++)f[j][k]=(f[j][k]-1ll*t*f[i][k]%mod+mod)%mod;
		}
	}
	for(int i=512-1;i>=0;i--){
		for(int j=i+1;j<512;j++)f[i][512]=(f[i][512]-1ll*ans[j]*f[i][j]%mod+mod)%mod;
		ans[i]=1ll*f[i][512]*Power(f[i][i],mod-2)%mod;
	}
}
void dfs(int x){
	if(v[x])return ;
	bool t[525]={0};
	for(int y:g[x])dfs(y),t[sg[y]]=1;
	while(t[sg[x]])sg[x]++;
	v[x]=1,cnt[sg[x]]++;
}
int main(){
	cin>>n>>m;
	for(int i=1,x,y;i<=m;i++)cin>>x>>y,g[x].push_back(y);
	for(int i=1;i<=n;i++)dfs(i);
	for(int i=1,u=Power(n+1,mod-2);i<512;i++){
		f[i][i]=1;
		for(int j=0;j<512;j++)f[i][j]=(f[i][j]-1ll*u*cnt[i^j]%mod+mod)%mod;
	}
	for(int i=0;i<=512;i++)f[0][i]=1;
	Gauss(),printf("%d\n",(1-ans[0]+mod)%mod);
}
```

---

## 作者：gxy001 (赞：6)



首先，我们可以在 $O(m)$ 的时间复杂度内求出每个点的 SG 值，直接按照 SG 函数的定义求解即可。

题目转化为给定一个数组 $a$，长度为 $n$，和一个初值为 $0$ 的变量 $v$，执行如下操作：

1. 在 $[1,n+1]$ 中等概率随机一个整数 $p$。若 $p\le n$，进行操作 2；否则，进行操作 3。
2. $v\larr v\oplus a_p$，进行操作 1。
3. 游戏结束，若 $v=0$ 则输，否则赢。

求赢的概率。

设 $f_i$ 为一次随机过程使得 $v\larr v\oplus i$ 的概率，设其集合幂级数为 $F$，设游戏结束时 $v=i$ 的概率为 $g_i$，$G$ 为其集合幂级数，乘法为异或卷积，则有等式 
$$
\begin{aligned}
G=&\frac{\sum\limits_{i=0}^{\infin}F^i}{n+1}\\
=&\frac{1}{(n+1)(1-F)}
\end{aligned}
$$
这里我们要证明 $1-F$ 有逆，有逆的充要条件是 FWT 后每一项都不为零。

证明需要先了解 FWT 的一个性质， FWT 是线性变换且每一项系数都为 $\pm1$，且常数项对 FWT 后每一项的系数贡献都为 $1$。

因为 $F$ 的和为 $\frac n{n+1}$ 且每一项都为非负数，所以对 $F$ 进行 FWT 后每一项取值应该在 $-\frac n{n+1}$ 到 $\frac n{n+1}$ 之间，$-F$ 进行 FWT 后的结果为 $F$ 的结果取反，所以每一项取值也在 $-\frac n{n+1}$ 到 $\frac n{n+1}$ 之间，给原集合幂级数常数项加 $1$，就是给 FWT 后每一项都加 $1$，所以 $1-F$ 在 FWT 后每一项的取值应该在 $1-\frac n{n+1}$ 到 $1+\frac n{n+1}$ 之间，不包括零，所以 $1-F$ 有逆。

知道这点就可以直接做了，求逆的方式就是点值每一项都求逆，时间复杂度就是 FWT 的复杂度。

不过 SG 值的值域是 $\sqrt m$，所以复杂度是 $O(m+\sqrt m \log m)$。

```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
int const mod=998244353,inv2=(mod+1)/2; 
std::vector<int> v[100010],p[100010];
int n,m,d[100010],a[100010],f[600],lim;
int pow(int x,int y){
	int res=1;
	while(y){
		if(y&1) res=1ll*res*x%mod;
		x=1ll*x*x%mod,y>>=1; 
	}
	return res;
}
void fwt(int *a){
	for(int mid=1;mid<lim;mid<<=1)
		for(int r=mid<<1,j=0;j<lim;j+=r)
			for(int k=0;k<mid;k++){
				int x=a[k+j],y=a[mid+j+k];
				a[k+j]=(x+y)%mod,a[mid+j+k]=(x-y+mod)%mod;	
			}
}
void ifwt(int *a){
	for(int mid=1;mid<lim;mid<<=1)
		for(int r=mid<<1,j=0;j<lim;j+=r)
			for(int k=0;k<mid;k++){
				int x=a[k+j],y=a[mid+j+k];
				a[k+j]=1ll*(x+y)*inv2%mod,a[mid+j+k]=1ll*inv2*(x-y+mod)%mod;	
			}
}
int main(){
	scanf("%d%d",&n,&m);
	int lm=pow(n+1,mod-2);
	for(int i=1,x,y;i<=m;i++)scanf("%d%d",&x,&y),v[y].push_back(x),++d[x];
	static int que[100010];
	int *hd=que,*tl=que;
	for(int i=1;i<=n;i++) if(!d[i]) *tl++=i;
	while(hd!=tl){
		int x=*hd++;
		std::sort(p[x].begin(),p[x].end());
		p[x].erase(std::unique(p[x].begin(),p[x].end()),p[x].end());
		for(a[x]=0;a[x]<(int)p[x].size()&&p[x][a[x]]==a[x];a[x]++);
		lim=std::max(a[x],lim);
		f[a[x]]=(f[a[x]]-lm+mod)%mod;
		for(auto u:v[x]){
			p[u].push_back(a[x]);
			if(!--d[u]) *tl++=u;
		}
	}
	if(lim==0) lim=2;
	else do lim+=lim&-lim; while((lim&-lim)!=lim);
	f[0]=(f[0]+1)%mod;
	for(int i=0;i<lim;i++) f[i]=1ll*f[i]*(n+1)%mod;
	fwt(f);
	for(int i=0;i<lim;i++) f[i]=pow(f[i],mod-2);
	ifwt(f);
	printf("%d\n",(1-f[0]+mod)%mod);
	return 0;
}
```



---

## 作者：Thaumaturge (赞：2)

如果不知道$sg$值的上限是根号级别的话，可以考虑更暴力一点的方法

同样考虑求出每个点的$sg$值，设$f_{i,x}$表示转移了$i$次后值为$x$的概率。$g_{i}$为选中的$sg$值为$i$的概率

转移就是$f_{i,x}=\sum_{j⊕k==x}f_{i-1,j}*g_{k}$

发现这是个异或卷积，那么$F_{i}=G^i$

而我们要求的是：$1-\frac{\sum_{i=0}^{+∞} f_{i,0}}{n+1}$

也就是：$1-\frac{[x^0]\sum_{i=0}^{+∞} G^{i}}{n+1}$

压起来：$1-\frac{[x^0]}{(n+1)*(I-G)}$

而异或卷积是可以求逆的，直接把点值的每一位变成它的倒数就行。~~神奇吧~~

然后就做完了。

复杂度$O(\sqrt n logn +m)$

```cpp
/*************************************************************************
	> File Name: e.cpp
	> Author: The-Out-Land
	> Mail: 2264454706@qq.com 
	> Created Time: 2021年03月10日 星期三 19时57分12秒
 ************************************************************************/

#include <bits/stdc++.h>

#define enter putchar('\n')
#define space putchar(' ')
#define re register
#define int long long
#define M 1000100
#define N 500100

using namespace std;

const int mod=998244353,lim=12,L=(1ll<<lim),in2=499122177;

inline int max(int x,int y){return (x>y?x:y);}

inline int min(int x,int y){return (x<y?x:y);}

inline int read(){
	int x=0;char c=getchar();bool y=1;
	for(;c<'0' || c>'9';c=getchar()) if(c=='-') y=0;
	for(;c>='0' && c<='9';c=getchar()) x=(x<<1)+(x<<3)+c-48;
	if(y) return x;
	return -x;
}

int n,m,In,fans;

int ver[M],nex[M],h1[N],h2[N],nu;

int OK[N],sg[N],F[N],f[lim+1][N],rd[N];

queue<int> q;

inline int add(int x){if(x<0) return x+mod;return (x>=mod?x-mod:x);}
inline int Pow(int x,int y){int ans=1;while(y){if(y&1) ans=1ll*ans*x%mod;x=1ll*x*x%mod;y>>=1;}return ans;}

inline void add(int x,int y){
	ver[++nu]=y,nex[nu]=h1[x],h1[x]=nu;
	ver[++nu]=x,nex[nu]=h2[y],h2[y]=nu;
	++rd[x];
	return;
}

inline void FFT_xor(int a[],int len,int opt){
	int x,y;
	for(re int i=1;i<len;i<<=1)
		for(re int j=0;j<len;j+=i+i)
			for(re int k=0;k<i;++k)
			{
				x=a[j+k],y=a[i+j+k];
				a[j+k]=(x+y)%mod;
				a[i+j+k]=(x-y)%mod;
				a[j+k]=opt*a[j+k]%mod,a[i+j+k]=opt*a[i+j+k]%mod;
			}
	return;
}


inline void Input(){
	n=read(),m=read();
	for(re int i=1;i<=m;++i){
		int X=read(),Y=read();
		add(X,Y);
	}
	return;
}

inline void solve(){
	In=Pow(n+1,mod-2);
	for(re int i=1;i<=n;++i) if(!rd[i]) q.push(i);
	while(!q.empty()){
		int x=q.front(),y;q.pop();
		for(re int i=h2[x];i;i=nex[i]){
			y=ver[i];
			--rd[y];
			if(!rd[y]) q.push(y);
		}
		for(re int i=h1[x];i;i=nex[i]){
			y=ver[i];
			++OK[sg[y]];
		}
		int ret=0;
		while(OK[ret]) ++ret;
		sg[x]=ret;
		F[ret]=add(F[ret]-In);
		for(re int i=h1[x];i;i=nex[i]){
			y=ver[i];
			--OK[sg[y]];
		}
	}
	F[0]=add(F[0]+1);
	FFT_xor(F,L,1);
	for(re int i=0;i<L;++i) F[i]=Pow(F[i],mod-2);
	FFT_xor(F,L,in2);
	fans=F[0]*In%mod;
	printf("%lld\n",add(1-fans));
	return;
}

signed main(){
	Input();
	solve();
	return 0;
}
```


---

## 作者：OMG_wc (赞：1)

第一步先求出每个点的 SG 值，并记 $cnt_x$ 表示 SG 值为 $x$ 的点的个数。

要形成一个 SG 值为 $x$ 的点，至少需要 $1+2+3+\dots+x=\frac{(x+1)x}{2}$ 条边。因为 $m\le 100000$，所以最终 SG 值的异或和范围在 $[0,511]$  内。

定义 $f_{i}$ 表示当前异或和为 $i$，最终先手（Alice）获胜的概率。

获胜有两种情况：

- 在某个不为 $0$ 的状态退出，概率为 $\frac{1}{n+1}$
- 获得了一个新点后，状态变为 $j$，概率为 $\frac{cnt_{i\oplus j}}{n+1}$

因而得到 $512$ 个未知数 $512$ 个方程的方程组：

$f_i=\frac{[i\neq0]}{n+1}+\sum\limits_{j=0}^{511}\frac{cnt_{i\oplus j}}{n+1} f_j$

要求的最终答案就是 $f_0$。

验证一下第三个样例：

![](https://cdn.luogu.com.cn/upload/image_hosting/52o41h5g.png)

用高斯消元在 $O(m^{\frac{3}{2}})$ 时间内求解，像这种满秩矩阵写起来很简单。

原理就是用三种初等变换，一步步把系数矩阵变成对角矩阵：考虑到第 $i$ 个未知数的时候，把除了第 $i$ 个方程以外的方程都减去第 $i$ 个方程的若干倍来消除 $x_i$ 。

另外本题也可以 FWT，~~愿闻其翔~~

代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF = 0x3f3f3f3f;
const LL mod = 998244353;
const int N = 100005;
const int M = 520;

LL pow_mod(LL x, LL n) {
    LL res = 1;
    while (n) {
        if (n & 1) res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}
int vis[M], sg[N], cnt[M];
vector<int> G[N];
int dfs(int u) {
    if (~sg[u]) return sg[u];
    for (auto v : G[u]) {
        dfs(v);
    }
    for (auto v : G[u]) {
        vis[sg[v]] = u;
    }
    for (int i = 0;; i++)
        if (vis[i] != u) return sg[u] = i;
}
LL a[M][M];
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    while (m--) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
    }
    memset(sg, -1, sizeof sg);
    for (int i = 1; i <= n; i++) {
        cnt[dfs(i)]++;
    }
    int w = 512;
    LL inv = pow_mod(n + 1, mod - 2);
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < w; j++) {
            a[i][j] = cnt[i ^ j] * inv % mod;
        }
        a[i][i] = (a[i][i] - 1 + mod) % mod;
        a[i][w] = i == 0 ? 0 : (mod - inv) % mod;
    }
    for (int i = 0; i < w; i++) {
        if (a[i][i] == 0) {
            for (int j = i; j < w; j++) {
                if (a[j][i] != 0) {
                    swap(a[i], a[j]);
                }
            }
        }
        for (int j = 0; j < w; j++) {
            if (j != i && a[j][i] != 0) {
                LL tmp = a[j][i] * pow_mod(a[i][i], mod - 2) % mod;
                for (int k = i; k <= w; k++) {
                    a[j][k] = (a[j][k] - tmp * a[i][k] % mod + mod) % mod;
                }
            }
        }
    }
    printf("%lld\n", a[0][w] * pow_mod(a[0][0], mod - 2) % mod);
    return 0;
}
```



---

## 作者：daniEl_lElE (赞：0)

首先看到博弈容易想到 SG 函数，可以对于原图每个点直接暴力出 SG 函数值，复杂度 $O(m)$。

SG 函数判断胜负本质上是 XOR 起来，现在随机选择一些位置，不难想到 XOR 卷积。

首先将所有的点的 SG 函数值塞到一个数组里面。对它进行 XOR DFT，每个位置此时有一个概率，那么选择的期望就是 $(1+f_i+f_i^2+f_i^3+\dots)\times\frac{1}{n+1}$，即 $\frac{1}{(1-f_i)(n+1)}$。令 $f'_i=\frac{1}{(1-f_i)(n+1)}$ 并 XOR IDFT 即可。

总复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define add(i,j) ((i+j>=mod)?i+j-mod:i+j)
using namespace std;
const int mod=998244353,inv2=(mod+1)/2;
int qp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) (ans*=a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return ans;
}
vector<int> vc[100005],fv[100005];
int deg[100005],sg[100005];
int cnt[100005];
int f[100005];
signed main(){
	int n,m; cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v; cin>>u>>v;
		deg[u]++;
		vc[u].push_back(v);
		fv[v].push_back(u);
	}
	queue<int> q;
	for(int i=1;i<=n;i++) if(!deg[i]) q.push(i);
	while(!q.empty()){
		int f=q.front(); q.pop();
		for(auto v:vc[f]){
			cnt[sg[v]]++;
		}
		while(cnt[sg[f]]) sg[f]++;
		for(auto v:vc[f]){
			cnt[sg[v]]--;
		}
		for(auto v:fv[f]){
			deg[v]--;
			if(deg[v]==0){
				q.push(v);
			}
		}
	}
	int inv=qp(n+1,mod-2);
	for(int i=1;i<=n;i++) (f[sg[i]]+=inv)%=mod;
	for(int i=1;i<=15;i++){
		for(int j=0;j<(1<<15);j++){
			if((j>>(i-1))&1){
				int p0=j^(1<<(i-1)),p1=j;
				int l0=f[p0],l1=f[p1];
				f[p0]=(l0+l1)%mod;
				f[p1]=(l0+mod-l1)%mod;
			}
		}
	}
	for(int i=0;i<(1<<15);i++){
		//f[i]^0+f[i]^1+...
		//1/(1-f[i])
		f[i]=qp((mod+1-f[i])*(n+1)%mod,mod-2);
	}
	for(int i=1;i<=15;i++){
		for(int j=0;j<(1<<15);j++){
			if((j>>(i-1))&1){
				int p0=j^(1<<(i-1)),p1=j;
				int l0=f[p0],l1=f[p1];
				f[p0]=(l0+l1)*inv2%mod;
				f[p1]=(l0+mod-l1)*inv2%mod;
			}
		}
	}
	int ans=0;
	for(int i=1;i<(1<<15);i++) (ans+=f[i])%=mod;
	cout<<ans;
	return 0;
}
```

---

