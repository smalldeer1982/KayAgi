# Card Guessing

## 题目描述

Consider a deck of cards. Each card has one of $ 4 $ suits, and there are exactly $ n $ cards for each suit — so, the total number of cards in the deck is $ 4n $ . The deck is shuffled randomly so that each of $ (4n)! $ possible orders of cards in the deck has the same probability of being the result of shuffling. Let $ c_i $ be the $ i $ -th card of the deck (from top to bottom).

Monocarp starts drawing the cards from the deck one by one. Before drawing a card, he tries to guess its suit. Monocarp remembers the suits of the $ k $ last cards, and his guess is the suit that appeared the least often among the last $ k $ cards he has drawn. So, while drawing the $ i $ -th card, Monocarp guesses that its suit is the suit that appears the minimum number of times among the cards $ c_{i-k}, c_{i-k+1}, \dots, c_{i-1} $ (if $ i \le k $ , Monocarp considers all previously drawn cards, that is, the cards $ c_1, c_2, \dots, c_{i-1} $ ). If there are multiple suits that appeared the minimum number of times among the previous cards Monocarp remembers, he chooses a random suit out of those for his guess (all suits that appeared the minimum number of times have the same probability of being chosen).

After making a guess, Monocarp draws a card and compares its suit to his guess. If they match, then his guess was correct; otherwise it was incorrect.

Your task is to calculate the expected number of correct guesses Monocarp makes after drawing all $ 4n $ cards from the deck.

## 样例 #1

### 输入

```
1 1```

### 输出

```
748683266```

## 样例 #2

### 输入

```
3 2```

### 输出

```
567184295```

## 样例 #3

### 输入

```
2 7```

### 输出

```
373153250```

## 样例 #4

### 输入

```
2 8```

### 输出

```
373153250```

# 题解

## 作者：DeaphetS (赞：21)

题目链接：[C - Card Guessing](https://codeforces.com/contest/1765/problem/C)

题目大意：桌面上有一堆牌，牌有四种花色，每种花色有 $n$ 张，一共 $4n$ 张，每次随机从牌堆中抽一张卡直到抽完，抽出来的卡片组成的序列一共有 $(4n)!$ 种。Monocarp 在执行抽卡的过程中会根据过去 $k$ 次抽卡的结果来猜测本次抽出来的卡片花色，他固定会猜最近这 $k$ 次结果中出现次数最少的那一个花色（如有多个花色满足条件则随机猜一个，如果之前已经抽卡的数量小于 $k$ 则猜测依据就是之前所有的抽卡结果），问期望猜对次数。

首先根据期望线性性，期望猜对次数就等于每次猜对概率之和。考虑当前是第 $i$ 次猜测，设 $K=\min(k,i-1)$，那么当前决策以及是否猜对只取决于抽卡序列的第 $i-K$ 至第 $i$ 项，于是我们只需要考虑一个长度为 $K+1$ 的序列满足其最后一项与对应猜测结果相同的概率。为了计数方便，我们把相同花色的 $n$ 张牌当作互不相同的来处理。

根据这一思路，我们很容易想到设 $g_{i,j}$ 表示长度为 $i$，花色最少出现次数为 $j$ 的序列个数。但是这个方案数是很难直接计算的，因为每个花色的出现次数有个上限，不能直接组合数计算，于是考虑使用背包来计数。

设 $f_{col,num,mn}$ 表示放置了前 $col$ 个花色，卡牌总数为 $num$，最少出现次数为 $mn$ 的方案数。那么对于每个状态，我们只需枚举下一个颜色的放置个数 $i$，就能够产生从 $f_{col,num,mn}$ 到 $f_{col+1,num+i,\min(mn,i)}$ 的转移。由于我们是把同一花色的牌是看作互不相同的，那么转移系数就是 $\binom{num+i}{i}\cdot \binom{n}{i}\cdot i!$。背包结束后对于 $j\ge 1$ 就有 $g_{i,j}=f_{4,i,j}$，而 $g_{i,0}$ 则等于 $\sum_{c=1}^{3}\sum_j\binom{4}{c}f_{c,i,j}$。除此之外为了方便计数我们还需要记 $h_i$ 表示长度为 $i$ 的不同抽卡序列个数，显然就有 $h_i=\sum_j g_{i,j}$。

最后计算答案时，我们只需要先求出对应的 $K$，然后计算满足猜测的序列个数，除以总方案数就能得出对应的概率，当 $i=1$ 时提前钦定对应概率为 $\frac{1}{4}$ 即可。最后答案为 $\frac{1}{4}+\sum_{i=2}^{4n}\frac{\sum_j g_{K,j}\cdot (n-j)}{h_{K+1}}$，其中 $K=\min(i-1,k)$。

时间复杂度 $O(n^3)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 2020
#define LL long long
#define MOD 998244353
int n,k,f[5][N][N>>2],g[N][N>>2],C[N][N],p[N],q[N],inv[N],h[N],ans;
LL qow(LL x,LL y){return y?(y&1?x*qow(x,y-1)%MOD:qow(x*x%MOD,y/2)):1;}
int main()
{
	inv[1]=p[0]=q[0]=p[1]=q[1]=1;
	C[0][0]=C[1][0]=C[1][1]=1;
	for(int i=2;i<N;i++){
		C[i][0]=C[i][i]=1;
		for(int j=1;j<i;j++)
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD;
		inv[i]=1ll*(MOD-MOD/i)*inv[MOD%i]%MOD;
		p[i]=1ll*i*p[i-1]%MOD;
		q[i]=1ll*inv[i]*q[i-1]%MOD;
	}
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)f[1][i][i]=1ll*p[n]*q[n-i]%MOD;
	for(int c=1;c<4;c++)
	for(int num=c;num<=c*n;num++)
	for(int mn=1;mn<=num/c;mn++)if(f[c][num][mn]){
		for(int i=1;i<=n;i++){
			int tot=1ll*f[c][num][mn]*C[num+i][i]%MOD,Mn=min(mn,i);
			tot=1ll*tot*p[n]%MOD*q[n-i]%MOD;
			f[c+1][num+i][Mn]=(f[c+1][num+i][Mn]+tot)%MOD;
		}
	}
	for(int i=1;i<=4*n;i++)
	for(int j=1;j<=n;j++)
		g[i][j]=1ll*f[4][i][j]%MOD;
	for(int c=1;c<=3;c++)
	for(int i=1;i<=c*n;i++)
	for(int j=1;j<=i/c;j++)
		g[i][0]=(g[i][0]+1ll*C[4][c]*f[c][i][j])%MOD;
	for(int i=1;i<=4*n;i++)
	for(int j=0;j<=n;j++)
		h[i]=(h[i]+g[i][j])%MOD;
	ans=qow(4,MOD-2);
	for(int i=2;i<=4*n;i++){
		int K=min(i-1,k),tot=0;
		for(int j=0;j<=K/4;j++)
			tot=(tot+1ll*g[K][j]*(n-j))%MOD;
		ans=(ans+qow(h[K+1],MOD-2)*tot)%MOD;
	}
	printf("%d\n",ans);
}
```

---

## 作者：Alex_Wei (赞：9)

根据期望的线性性，将答案摊到每次猜测。

第 $i$ 次猜测的已知卡片数量为 $c = \min(i - 1, k)$。设四种卡片落在已知卡片区的张数分别为 $c_1\sim c_4$，需要满足 $c = \sum c_i$，则安排这些卡片的方案数为
$$
\binom {c} {c_1, c_2, c_3, c_4} \binom {4n - c}{n - c_1, n - c_2, n - c_3, n - c_4}
$$
我们要从所有出现次数最小的卡片中选一个放到下一个位置上。设出现次数最小的卡片数量为 $d$，则有 $d$ 种方案，但因为 Monocarp 会从这 $d$ 张卡片中随机选择，所以一乘一除抵消掉了。设最小值为 $mn = \min c_i$，则贡献至答案的式子为
$$
\binom {c} {c_1, c_2, c_3, c_4} \binom {4n - c}{n - c_1, n - c_2, n - c_3, n - c_4} \times \dfrac {\binom {4n - c - 1} {n - mn - 1}} {\binom {4n - c} {n - mn}}
$$
即
$$
\dfrac {c!} {c_1! c_2! c_3! c_4!} \dfrac {(4n - c - 1)! (n - mn)!} {(n - c_1)! (n - c_2) ! (n - c_3)! (n - c_4)! (n - mn - 1)!}
$$
枚举最小值 $p$，设 $f_i$ 表示使得 $c = i$ 的方案数之和，做背包即可。

时间复杂度 $\mathcal{O}(n ^ 3)$。[代码](https://codeforces.com/contest/1765/submission/185465484)。

---

## 作者：XP3301_Pipi (赞：5)

# CF1765C Card Guessing

## Description

有 $4$ 种花色的牌，每种牌均为 $n$ 张，则牌的排列⼀共有 $(4\cdot n)!$ 种。

现在你从牌堆中逐张地取出牌，取牌之前你都会猜这张牌是什么花色。你会根据之前的 $k$ 张牌中出现最少的花色来猜这张牌。

如果有多种花色都是最少的，你随机地猜一种。

如果之前抽出的牌不足 $k$ 张，就按之前的所有牌中的最少花色来猜。

问你猜对的期望次数是多少？

[Link](https://www.luogu.com.cn/article/ueyzhxud/edit)

[AD](https://www.cnblogs.com/XP3301Pipi/p/18684548)

## Solution

令 $m=4n$。设 $m$ 个随机变量 $X_1,X_2,...X_m$，$X_i$ 取值为 $1$ 表示第 $i$ 次猜对，否则没有猜对。

那么我们求的是：
$$
E(\sum X_i)=\sum E(X_i)=\sum P(X_i=1)
$$
独立地求出每一次猜对的概率，加和即为答案。

设 $L=\min(i-1,k)$，我们称之前的 $L$ 张牌为 “依据牌”。首先有一个比较重要的观察：在依据牌中存在多种最少的花色时，无论猜哪一个花色，猜对概率都是一样的。

原因很简单，在依据牌固定的情况下，设它们在依据牌中出现的次数为 $c$，那么下面一张牌猜对的概率都是 $\dfrac{n-c}{m-L}$。

考虑概率转计数。那么题意转化为：

- 对每一个 $i \ (1\leq i \leq m)$ 求：有多少个序列，使得 $i$ 的花色为 $A_{i-L} \sim A_{i-1}$ 中出现次数最少的花色。 若有多种最少的花色，则令 $i$ 为最少的花色中编号最小的。

首先考虑如何计算答案。设这 $L+1$ 张牌组成的序列数量为 $B$，那么对应的概率为：
$$
\dfrac{B \times (m-L-1)!}{m!}=\dfrac{B\times (m-L-1)!}{(m-L-1)!A_{m}^{L+1}}=\dfrac{B}{A_{m}^{L+1}}
$$
现在我们的答案只和这 $L+1$ 张牌有关。

枚举这 $L$ 张牌中出现次数最少的花色出现了几次。由于每个花色出现个数被 $n$ 限制，不易直接用组合数求解，那么考虑 dp 求解：

设 $f_{i,j,l}$ 表示考虑到第 $i$ 种花色，选了 $j$ 张牌，最小出现花色为 $l$ 的方案数。

我们选择下一种花色分为三步：

1. 在 $n$ 张牌中选择 $t$ 张；
2. 对这 $t$ 张牌进行排列；
3. 将这 $t$ 张牌插入到已经选好的 $j$  张牌中。

得出转移：
$$
f_{i,j,l} \times\binom{n}{t}\times t!\times\binom{j+t}{t}\rightarrow f_{i+1,j+t,\min(j,l)}
$$
这个部分复杂度为 $O(n^3)$。

对于一个 $L$，枚举依据牌中出现最少的花色的出现次数 $l$，那么后面的 $i$ 就有 $n-l$ 种选择。那么得到 $i$ 猜对的序列个数为：
$$
g_L=\sum_{l\geq 0} (f_{4,L,l}\times(n-l))
$$
这个部分复杂度为 $O(n^2)$。

由于第 $1$ 张牌前没有依据牌，需要单独计算。最终的答案为：
$$
Ans=\dfrac{1}{4}+\sum_{i=2}^m\dfrac{g_L}{A_{m}^{L+1}}
$$

```cpp
int n,k,m;

const ll mod=998244353;

ll Mod(ll x){return (x>=mod)?(x-mod):(x);}

void Add(ll &x,ll y){x=Mod(x+y);}

ll f[6][M][M],fac[M],caf[M],g[M],h[M];

ll QuickPow(ll x,ll y){
    ll res=1;
    while(y){
        if(y&1) res=res*x%mod;
        x=x*x%mod; y>>=1;
    }
    return res;
}

void Init(){
    fac[0]=caf[0]=1;
    for(int i=1;i<=m;i++) fac[i]=fac[i-1]*i%mod;
    caf[m]=QuickPow(fac[m],mod-2);
    for(int i=m-1;i;i--) caf[i]=caf[i+1]*(i+1)%mod;
}

ll C(int x,int y){
    if(x<0||y<0||x<y) return 0;
    return fac[x]*caf[y]%mod*caf[x-y]%mod;
}

signed main(){
    read(n),read(k); m=n<<2;
    Init();
    for(int i=0;i<=m;i++) f[1][i][i]=C(n,i)*fac[i]%mod;
    for(int i=1;i<=3;i++){
        for(int j=0;j<=m;j++){
            for(int l=0;l<=j;l++){
                if(!f[i][j][l]) continue;
                for(int t=0;t<=n&&j+t<=m;t++){
                    Add(f[i+1][j+t][min(l,t)],f[i][j][l]*C(n,t)%mod*C(j+t,t)%mod*fac[t]%mod);
                }
            }
        }
    }
    for(int i=1;i<=m;i++){
        for(int j=0;j<=n;j++){
            Add(g[i],f[4][i][j]*(n-j)%mod);
            Add(h[i],f[4][i][j]);
        }
    }
    ll ans=QuickPow(4,mod-2);
    for(int i=2;i<=m;i++){
        int j=min(i-1,k);
        ll H=C(m,j+1)*fac[j+1]%mod;
        ll inv=QuickPow(H,mod-2);
        Add(ans,g[j]*inv%mod);
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Petit_Souris (赞：2)

套路化地根据期望的线性性把贡献拆到每个位置上，计算其猜对的概率。

设 $c=\min(i-1,k)$ 表示猜第 $i$ 个位置的时候前面的牌河大小。那么考虑位置 $i$ 猜对的概率。枚举牌河中四种花色出现的次数 $c_1,c_2,c_3,c_4$，满足 $c_1+c_2+c_3+c_4=c$，那么方案数就是前面这 $c$ 个随便排，第 $i$ 个要是最小值，剩下 $4n-c-i$ 个随便排。注意这里第 $i$ 个首先会乘上一个最小值数量的系数，表示这些里面随便选；再乘上一个最小值数量的倒数的系数，表示随机到正确的概率，恰好抵消。

方案数也就是：

$$
\binom{c}{c_1,c_2,c_3,c_4}\binom{4n-c}{n-c_1,n-c_2,n-c_3,n-c_4}\frac{\binom{4n-c-1}{n-\min(c_1,c_2,c_3,c_4)-1}}{\binom{4n-c-1}{n-\min(c_1,c_2,c_3,c_4)}}
$$

直接枚举 $c_1,c_2,c_3,c_4$ 可以得到一个 $\mathcal O(n^4)$ 的做法。

化简一下：

$$
\frac{c!(4n-c-1)!(n-\min(c_1,c_2,c_3,c_4))}{c_1!c_2!c_3!c_4!(n-c_1)!(n-c_2)!(n-c_3)!(n-c_4)!}
$$

有很多种办法做到 $\mathcal O(n^3)$：直接 dp，meet in the middle。meet in the middle 做法也很容易通过 NTT 优化到 $\mathcal O(n^2\log n)$（差分一下之后做卷积）。

能不能再给力一点？发现 $\min$ 是多少其实并不影响后面转移，所以考虑按照值域从小到大做 dp，在第一次加入元素的时候把这个 $n-\min(c_1,c_2,c_3,c_4)$ 的系数乘进去，这样就做到 $\mathcal O(n^2)$ 了。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll N=509,Mod=998244353;
ll n,k,fac[N*4],ifac[N*4],dp[2][N*4][5],cur;
ll pw(ll x,ll p){
    ll res=1;
    while(p){
        if(p&1)res=res*x%Mod;
        x=x*x%Mod,p>>=1;
    }
    return res;
}
ll C(ll x,ll y){
    if(x<y||y<0)return 0;
    return fac[x]*ifac[y]%Mod*ifac[x-y]%Mod;
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    n=read(),k=read();
    fac[0]=1;
    rep(i,1,n*4)fac[i]=fac[i-1]*i%Mod;
    ifac[n*4]=pw(fac[n*4],Mod-2);
    per(i,n*4-1,0)ifac[i]=ifac[i+1]*(i+1)%Mod;
    dp[0][0][0]=1;
    rep(i,0,n){
        memset(dp[cur^1],0,sizeof(dp[cur^1]));
        rep(j,0,k){
            rep(t,0,4){
                if(!dp[cur][j][t])continue;
                dp[cur^1][j][t]=(dp[cur^1][j][t]+dp[cur][j][t])%Mod;
                ll coef=1;
                rep(tt,1,4-t){
                    if(j+tt*i>k)break;
                    coef=coef*ifac[i]%Mod*ifac[n-i]%Mod;
                    dp[cur^1][j+tt*i][t+tt]=(dp[cur^1][j+tt*i][t+tt]+dp[cur][j][t]*ifac[tt]%Mod*coef%Mod*((!t)?max(1ll,n-i):1ll))%Mod;
                }
            }
        }
        cur^=1;
    }
    ll ans=0;
    rep(i,1,n*4){
        ll c=min(i-1,k);
        ans=(ans+dp[cur][c][4]*fac[c]%Mod*fac[4*n-c-1])%Mod;
    }
    write(ans*24%Mod*ifac[4*n]%Mod*fac[n]%Mod*fac[n]%Mod*fac[n]%Mod*fac[n]%Mod);
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

## 作者：lsj2009 (赞：2)

### Solution

神仙计数！

**由于每次猜花色是不同的决策，所以我们把同一种花色的牌看作本质不同的牌**。

我们考虑设 $f_{i,j,k}$ 表示为我们正在考虑第 $i$ 个花色，已经放了总共 $j$ 张牌，且花色最少的牌的数量为 $k$。得转移方程：

$$f_{i+1,j+p,\min(k,p)}\gets f_{i,j,k}\cdot {j+p\choose p}\cdot {n\choose p}\cdot p!$$

对于的系数，含义依次是：要将 $p$ 张第 $i$ 个花色的牌差到现有的 $j$ 张中决定位置，然后需要在 $n$ 张该花色的牌当中选 $p$ 张，最后我们可以将这些牌任意顺序排列，所以要乘上 $p!$。

然后考虑求出一个 $h_i$ 表示长为 $i$ 的序列总数，显然 $h_i=\sum\limits_{j=0}^n f_{4,i,j}$。

然后考虑怎么计算答案，首先我们在选第一张牌是存随机的，所以有一个 $\frac{1}{4}$ 的常数，然后我们考虑当前序列长为 $i$ 时猜对下一个卡牌的概率，我们考虑去枚举一个卡牌出现次数最小值 $j$，则下一次猜测有 $f_{4,\min(i-1,k),j}\cdot (n-j)$ 的方案总数，其中前者为前 $i-1$ 个数的方案数，后者为第 $i$ 个数的方案数。

那么得到答案为：

$$\frac{1}{4}+\sum\limits_{i=2}^{4\cdot n} \frac{\sum\limits_{j=0}^{n} f_{4,\min(i-1,k),j}}{h_{\min(i-1,k)+1}}$$

事实上前 $\min(i-1,k)$ 个数的选择是任意的，而我们并没有统计他，因为这里我们分子分母所带的这个系数相互抵消，所以无需计算。

最终复杂度 $\Theta(n^3)$。

### Code

```cpp
#include<bits/stdc++.h>
//#define int long long
#define ll long long
#define ull unsigned long long
#define ld long double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=2e3+5,M=5e2+5,MOD=998244353,m=2e3;
int qpow(int a,int b) {
	int res=1,base=a;
	while(b) {
		if(b&1)
			res=1ll*res*base%MOD;
		base=1ll*base*base%MOD; b>>=1;
	}
	return res;
}
void add(int &a,int b) {
	a+=b;
	if(a>=MOD)
		a-=MOD;
}
int f[5][N][M],h[N],jc[N],inv_jc[N];
void init() {
	jc[0]=1;
	rep(i,1,m)
		jc[i]=1ll*jc[i-1]*i%MOD;
	inv_jc[m]=qpow(jc[m],MOD-2);
	per(i,m-1,0)
		inv_jc[i]=1ll*inv_jc[i+1]*(i+1)%MOD;
}
int C(int n,int m) {
	return 1ll*jc[n]*inv_jc[m]%MOD*inv_jc[n-m]%MOD;
}
int P(int n,int m) {
	return 1ll*jc[n]*inv_jc[n-m]%MOD;
}
signed main() {
	init();
	int n,k;
	scanf("%d%d",&n,&k);
	rep(i,0,n)
		f[1][i][i]=P(n,i);
	rep(k,1,3) {
		rep(i,0,k*n) {
			rep(j,0,i/k) {
				rep(t,0,n)
					add(f[k+1][i+t][min(j,t)],1ll*f[k][i][j]*C(i+t,t)%MOD*P(n,t)%MOD);
			}
		}
	}
	rep(i,1,4*n) {
		rep(j,0,n)
			add(h[i],f[4][i][j]);
	}
	int ans=qpow(4,MOD-2);
	rep(i,2,4*n) {
		int m=min(i-1,k),res=0;
		rep(j,0,m/4)
			add(res,1ll*f[4][m][j]*(n-j)%MOD);
		add(ans,1ll*qpow(h[m+1],MOD-2)*res%MOD);
	}
	printf("%d\n",ans);
    return 0;
}

```

---

## 作者：zifanwang (赞：1)

考虑期望的线性性，求每种情况猜对的概率和，最终再除掉 ${4n \choose n,n,n,n}$。

考虑枚举最少的出现次数 $mn$，记四种卡的出现次数分别为 $c_1,c_2,c_3,c_4$，$c_1+c_2+c_3+c_4=i\le k$，则这种情况的方案数为：

$${i\choose c_1,c_2,c_3,c_4}{4n-i\choose n-c_1,n-c_2,n-c_3,n-c_4}\frac{{4n-i-1\choose n-mn-1}}{{4n-i\choose n-mn}}$$

即：

$$\frac{c!}{c_1!c_2!c_3!c_4!}\frac{(4n-c-1)!\max(n-mn,1)}{(n-c_1)!(n-c_2)!(n-c_3)!(n-c_4)!}$$

做一遍背包即可，时间复杂度 $\mathcal O(n^3)$。

参考代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define md 998244353
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define rept(i,a,b) for(int i=a;i<b;++i)
#define drep(i,a,b) for(int i=a;i>=b;--i)
using namespace std;
int n,k;
ll ans,f[2002],f1[2002],dp[503],fac[2003],ifac[2003];
ll power(ll x,int y){
	ll ans=1;
	for(;y;y>>=1){
		if(y&1)ans=ans*x%md;
		x=x*x%md;
	}
	return ans;
}
signed main(){
	fac[0]=1;
	rep(i,1,2000)fac[i]=fac[i-1]*i%md;
	ifac[2000]=power(fac[2000],md-2);
	drep(i,2000,1)ifac[i-1]=ifac[i]*i%md;
	cin>>n>>k,k=min(k,(n<<2)-1);
	drep(mn,n,0){
		rep(i,0,k)f[i]=0;
		f[0]=1;
		rept(c,0,4){
			rep(i,0,k)f1[i]=0;
			rep(i,0,k){
				rep(j,mn,min(i,n))f1[i]=(f1[i]+f[i-j]*ifac[j]%md*ifac[n-j])%md;
			}
			rep(i,0,k)f[i]=f1[i];
		}
		rep(i,0,k)dp[mn]=(dp[mn]+f[i]*fac[i]%md*fac[(n<<2)-i-1]%md*(i<k?1:(n<<2)-k))%md;
		rep(i,mn+1,n)dp[mn]=(dp[mn]-dp[i])%md;
		ans=(ans+dp[mn]*max(n-mn,1))%md;
	}
	cout<<(ans*ifac[n<<2]%md*fac[n]%md*fac[n]%md*fac[n]%md*fac[n]%md+md)%md;
	return 0;
}
```

---

## 作者：hj23308 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1765C)

### $\mathcal{Problem}$

有 $ 4 $ 种花⾊的牌，每种牌均为 $ n $ 张，则牌的排列⼀共有 $ (4n)! $ 种。

现在你从牌堆中逐张地取出牌，取牌之前你都会猜⼀下这张牌是什么花⾊。你会根据之前的 $ k $ 张牌中出现最少的花⾊来猜这张牌。

如果有多种花⾊都是最少的，你随机地猜⼀种。如果之前抽出的牌不⾜ $ k $ 张，就按之前的所有牌中的最少花⾊来猜。

问你猜对的期望次数是多少？

$ 1 \le n \le 500, 1 \le k \le 4n$。

### $\mathcal{Solution}$

由于期望的线性性，考虑分别计算猜测每张卡片的正确率。对于 $ 1 \le i \le k _ 0 $，可以视为 $ k = i - 1 $ 时的情况计算；而当 $ k _ 0 < i \le 4n $ 时，则是等价的，结果相等，只用算一次。

现在问题在于如何分别计算 $ 0 \le k \le k_0 $ 时的结果。枚举 $ k $ 张牌中每种花色的数量最小值 $ \min $，则猜对的概率为 $ \dfrac {n - \min} {4n - k} $，而对于计算其方案数可以考虑动态规划。

> **tips: 为什么猜对的概率始终为 $  \frac {n - \min} {4n - k} $？**
>
> 假设数量最少的花色有 $ t $ 种，于是翻到的牌的花色为数量最少花色之一的概率是 $ \frac {t \times (n - \min)} {4n - k} $，而猜测的花色有 $ t $ 种可能，所以猜对的概率为 $ \frac {t \times (n - \min)} {4n - k} \times \frac 1 t = \frac {n - \min} {4n - k} $，可以发现结果是与 $ t $ 的大小无关的。

定义 $ dp _ {i, j} $ 表示从 $ 4n $ 张牌中选中 $ i $ 张，其中每种花色牌的数量不小于 $ j $，简单背包计算。考虑容斥，则数量最小值恰好等于 $ j $ 时的结果为 $ dp _ {i, j} - dp _ {i, j + 1} $。

时间复杂度 $ \mathcal O(n ^ 3) $，空间复杂度 $ \mathcal O(n ^ 2) $。

### [$ \mathcal{Record} $](https://codeforces.com/contest/1765/submission/234944739)

### $\mathcal{Code}$

```cpp
#include<bits/stdc++.h>

using namespace std;

#define REP(i, l, r) for (int i = l; i <= r; i++)
#define PER(i, r, l) for (int i = r; i >= l; i--)

const int maxN = 2e3 + 1, pMod = 998244353;

inline void add(int &x, int y) { x = (x + y) % pMod; }

inline void mul(int &x, int y) { x = int(1LL * x * y % pMod); }

int qPow(int x, int k) {
	int res = 1;
	while (k) {
		if (k & 1) res = int(1LL * res * x % pMod);
		x = int(1LL * x * x % pMod), k >>= 1;
	}
	return res;
}

int C[maxN][maxN], fInv[maxN], dp[maxN][maxN][5];

int solve(int n, int k) {
	int res = 0;
	REP(mi, 0, k) {
		int tmp = (dp[mi][k][4] - dp[mi + 1][k][4]) % pMod;
		mul(tmp, n - mi), mul(tmp, fInv[4 * n - k]), add(res, tmp);
	}
	mul(res, qPow(C[4 * n][k], pMod - 2));
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	REP(i, 0, maxN - 1) {
		C[i][0] = 1, fInv[i] = qPow(i, pMod - 2);
		REP(j, 1, i) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % pMod;
	}
	int n, k, ans = 0;
	cin >> n >> k, k = min(k, 4 * n - 1);
	REP(mi, 0, n) {
		dp[mi][0][0] = 1;
		REP(step, 1, 4) REP(i, mi, n) REP(j, i, 4 * n) add(dp[mi][j][step], int(1LL * dp[mi][j - i][step - 1] * C[n][i] % pMod));
	}
	REP(i, 0, k - 1) add(ans, solve(n, i));
	int tmp = solve(n, k);
	mul(tmp, 4 * n - k), add(ans, tmp);
	add(ans, pMod), cout << ans << '\n';

	return 0;
}
```

---

## 作者：Otomachi_Una_ (赞：1)

考虑每一位拆开贡献，那么位置 $i$ 猜中的概率由两部分组成：

- $a_i$ 是 $a_{[\max(1,i-k),i-1]}$ 当中出现最少的。
- 假设 $a_{[\max(1,i-k),i-1]}$ 当中有 $t$ 个出现次数最少，那么还要乘上 $\dfrac 1t$。

不难发现这玩意只和 $\max(1,i-k)$ 有关系，和 $i$ 本身无关，我们只关注长度 $len=\max(1,i-k)$。我们需要对每个 $len\in[1,k]$ 求下面的式子：

考虑枚举 $a_i$ 出现的次数 $j$，其余元素的出现个数 $k,t,s$，那么所有可行方法即为：
$$
(4n-len-1)!\sum_{j=0}^{len}\sum_{k=j}^{len}\sum_{t=j}^{len}\sum_{s=j}^{len}[j+k+t+s=len] \dfrac{1}{1+[k=j]+[t=j]+[s=j]}\dbinom{n}{j}\dbinom{n}{k}\dbinom{n}{t}\dbinom{n}{s}
$$
如果 $k,t,s$ 有一个为 $j$，那么这样的 $(k,t,s)$ 组不会超过 $\mathcal O(n^3)$ 级别，直接暴力枚举即可。否则我们可以忽略前面的分式，通过枚举 $j$，把后面变成卷积即可。

时间复杂度：$\mathcal O(n^3)$。实际上，如果 $(k,t,s)$ 讨论得再细一点，后面枚举的部分变成在上次的结果下暴力卷积（每次只会加入一项）可以做到优秀的 $\mathcal O(n^2)$。

## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MP make_pair
#define vll vector<long long>
const int MAXN=4e5+5;
const int MOD=998244353;
const ll inv2=(MOD+1)/2;
namespace polynomial{// yjl poly plank 2.0 ver
// 这里原来有一个多项式板子
}using namespace polynomial;
ll ans[MAXN];
ll fac[MAXN],inf[MAXN],iv[MAXN];
int n,a; 
ll C(int x,int y){return fac[y]*inf[x]%MOD*inf[y-x]%MOD;} 
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>a;
	fac[0]=inf[0]=1;
	for(int i=1;i<MAXN;i++){
		fac[i]=fac[i-1]*i%MOD,
		inf[i]=ksm(fac[i],MOD-2);
		iv[i]=inf[i]*fac[i-1]%MOD;
	}
	for(int i=0;i<n;i++){
		for(int j=i;j<=n;j++)
			for(int k=i;k<=n;k++){
				if(j==i||k==i){
					for(int t=i;t<=n;t++){
						int s=i+j+k+t;
						ans[s]+=iv[(i==j)+(i==k)+(i==t)+1]*C(i,n-1)%MOD*C(j,n)%MOD*C(k,n)%MOD*C(t,n)%MOD*
						fac[s]%MOD*fac[4*n-1-s]%MOD;
					}
				}else{
					int t=i;
					int s=i+j+k+t;
					ans[s]+=iv[(i==j)+(i==k)+(i==t)+1]*C(i,n-1)%MOD*C(j,n)%MOD*C(k,n)%MOD*C(t,n)%MOD*
					fac[s]%MOD*fac[4*n-1-s]%MOD;
				}
			} 
		vll f(n+1);
		for(int j=0;j<=n;j++)
			if(j<=i) f[j]=0;
			else f[j]=C(j,n);
		int l=clogg(3*(n+1));
		butterfly(l);
		NTT(f,l,1);
		for(int j=0;j<(1<<l);j++) f[j]=f[j]*f[j]%MOD*f[j]%MOD;
		NTT(f,l,-1);
		for(int j=0;j<=3*n;j++){
			int s=i+j;
			ans[s]+=C(i,n-1)*f[j]%MOD*fac[s]%MOD*fac[4*n-1-s]%MOD;
		} 
	}
	for(int i=0;i<=4*n;i++) ans[i]%=MOD;
//	for(int i=0;i<=4*n;i++) cout<<ans[i]<<" ";cout<<endl;
	ll res=0;
	for(int i=1;i<=4*n;i++)
		res+=ans[min(i-1,a)];
	cout<<res%MOD*inf[4*n-1]%MOD;
	return 0;
}
```

---

## 作者：MiniLong (赞：0)

做的太麻烦了，看看就好。

高贵的高常数 $\Theta(n^2)$ 做法。

考虑对每个位置算贡献。首先特殊情况第一位 $\dfrac{1}{4}$。

然后考虑设 $f_{i,j,k,p}$ 为根据长度为 $i$ 的序列确定下一位，且这 $i$ 个数最小值为 $j$，用到了 $k$ 个花色，且是最小值的有 $p$ 个的方案数。

先写出一个看起来比较正确的转移：

$$
f_{i,j,k,p} = \sum\limits_{t>j} \sum\limits_{q=1}^4 f_{i-pj,t,k-p,q}
 \times \binom{n}{j}^p
$$

意思就是枚举上一次的最小值大于当前最小值，然后上次最小值个数任意，然后现在这 $p$ 个花色每个中选 $j$ 个的方案。

因为我们钦定 $f_{i,j,k,p}$ 为只有 $k$ 个花色的方案，且只是选出的答案，所以统计出来的答案还要乘上 $\binom{4}{k} \times i!$。

但是这样就够了吗？

考虑当 $i=3,j=1,k=2,p=1$ 时的 $f_{3,1,2,1} \times \binom{4}{2} \times 3!$，按上方转移的结果是 $72$，但实际结果为 $144$，且 $f_{3,1,2,1} = 2$。

这里 $f_{3,1,2,1}=2$ 是因为我 **每个花色选择的数量是有顺序的**，因为每次找比现在更小的值转移。

```
col A: 1 2
col B: 3 4
```

也就是说，我这里只统计了 $1 2 3$、$234$ 而没统计 $312$、$412$。

那就增加一个转移，根据排列公式，最后还要乘上 $\dfrac{k!}{\prod p!}$。更改转移方程。

$$
f_{i,j,k,p} = \sum\limits_{t>j} \sum\limits_{q=1}^4 f_{i-pj,t,k-p,q} \times \binom{n}{j}^p \times \dfrac{1}{p!}
$$

最后统计的数量是 $tot =f_{i,j,k,p} \times \binom{4}{k} \times i! \times k!$。

根据这个 $tot$，再去计算其他位置的答案。

1. 若当前取了 $4$ 个花色了，下一位只能是 $p$ 个花色中一个，即 $p \times (n-j) \times \dfrac{1}{p}$。

2. 否则就是其他 $4-k$ 中一个，即 $(4-k) \times n \times \dfrac{1}{4-k}$。

剩下 $m-i-1$ 位随便放，就是 $(m-i-1)!$，且如果 $i$ 位输入的 $k$，还要乘上 $(m-i)$（会有 $m-i$ 次贡献）。

记上面算的为 $res$，那么再除以总共的排列数量就是概率了，然后 $ans \leftarrow \dfrac{res}{(4n)!}$。

然后观察到 $f$ 的转移显然可以前缀和优化，最后复杂度是 $\Theta(n^2)$，常数大概 $64$。

```cpp
#include <bits/stdc++.h>
#define _rep(i, x, y) for(int i = x; i <= y; ++i)
#define _req(i, x, y) for(int i = x; i >= y; --i)
#define _rev(i, u) for(int i = head[u]; i; i = e[i].nxt)
#define pb push_back
#define fi first
#define se second
#define mst(f, i) memset(f, i, sizeof f)
using namespace std;
#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif
typedef long long ll;
typedef pair<int, int> PII;
namespace fastio{
    char ibuf[50007],*p1 = ibuf, *p2 = ibuf;
    #ifdef ONLINE_JUDGE
    #define get() p1 == p2 && (p2 = (p1 = ibuf) + fread(ibuf, 1, 50007, stdin), p1 == p2) ? EOF : *p1++
    #else
    #define get() getchar()
    #endif
    template<typename T> inline void read(T &t){
        T x = 0, f = 1;
        char c = getchar();
        while(!isdigit(c)){
            if(c == '-') f = -f;
            c = getchar();
        }
        while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
        t = x * f;
    }
    template<typename T, typename ... Args> inline void read(T &t, Args&... args){
        read(t);
        read(args...);
    }
    template<typename T> void write(T t){
        if(t < 0) putchar('-'), t = -t;
        if(t >= 10) write(t / 10);
        putchar(t % 10 + '0');
    }
    template<typename T, typename ... Args> void write(T t, Args... args){
        write(t), putchar(' '), write(args...);
    }
    template<typename T> void writeln(T t){
        write(t);
        puts("");
    }
    template<typename T> void writes(T t){
        write(t), putchar(' ');
    }
    #undef get
};
using namespace fastio;
#define multitest() int T; read(T); _rep(tCase, 1, T)
namespace Calculation{
    const ll mod = 998244353;
    ll ksm(ll p, ll h){ll base = p % mod, res = 1; while(h){if(h & 1ll) res = res * base % mod; base = base * base % mod, h >>= 1ll;} return res;}
    void dec(ll &x, ll y){x = ((x - y) % mod + mod) % mod;}
    void add(ll &x, ll y){x = (x + y) % mod;}
    void mul(ll &x, ll y){x = x * y % mod;}
    ll sub(ll x, ll y){return ((x - y) % mod + mod) % mod;}
    ll pls(ll x, ll y){return ((x + y) % mod + mod) % mod;}
    ll mult(ll x, ll y){return x * y % mod;}
}
using namespace Calculation;
const int N = 1005, M = 4005;
int n, len, m;
ll pw[M], inv[5], C[N][N], ipw[M];
ll f[M][N][5][5], g[M][N][5];

int main(){
    read(n, len), m = 4 * n;
    pw[0] = 1; _rep(i, 1, m) pw[i] = pw[i - 1] * i % mod, ipw[i] = ksm(pw[i], mod - 2);
    _rep(i, 0, 500){
        _rep(j, 0, 500){
            C[i][j] = (!j ? 1 : pls(C[i - 1][j], C[i - 1][j - 1]));
        }
    }
    _rep(i, 1, 4) inv[i] = ksm(i, mod - 2);
    ll totp = ksm(pw[m], mod - 2);
    ll ans = inv[4];
    _rep(i, 0, n + 1) g[0][i][0] = 1;
    _rep(i, 0, len){
        f[i][0][0][0] = g[i][0][0] = 1;
        _rep(j, 1, min(n, i)){
            _rep(k, 1, 4){
                _rep(p, 1, k){
                    if(i < p * j) continue;
                    f[i][j][k][p] = g[i - p * j][j + 1][k - p] * ksm(C[n][j], p) % mod * ipw[p] % mod;
                    add(g[i][j][k], f[i][j][k][p]);
                    if(i == m) continue;
                    ll cur = f[i][j][k][p] % mod * pw[i] % mod * C[4][k] % mod * pw[k] % mod;
                    if(i == 3 && j == 1 && k == 2 && p == 1) writeln(f[i][j][k][p]);
                    if(k == 4){
                        mul(cur, (n - j) * p % mod * pw[m - i - 1] % mod);
                        if(i == len) mul(cur, m - i);
                        mul(cur, inv[p]);
                    }else{
                        mul(cur, n * (4 - k) % mod * pw[m - i - 1] % mod);
                        if(i == len) mul(cur, m - i);
                        mul(cur, inv[4 - k]);
                    }
                    add(ans, cur * totp % mod);
                }
            }
        }
        _req(j, min(n, i), 0){
            _rep(k, 1, 4){
                add(g[i][j][k], g[i][j + 1][k]);
            }
        }
    }
    writeln(ans);
    return 0;
}
```

---

