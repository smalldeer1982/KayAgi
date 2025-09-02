# Coins Exhibition

## 题目描述

Arkady and Kirill visited an exhibition of rare coins. The coins were located in a row and enumerated from left to right from $ 1 $ to $ k $ , each coin either was laid with its obverse (front) side up, or with its reverse (back) side up.

Arkady and Kirill made some photos of the coins, each photo contained a segment of neighboring coins. Akrady is interested in obverses, so on each photo made by him there is at least one coin with obverse side up. On the contrary, Kirill is interested in reverses, so on each photo made by him there is at least one coin with its reverse side up.

The photos are lost now, but Arkady and Kirill still remember the bounds of the segments of coins each photo contained. Given this information, compute the remainder of division by $ 10^{9}+7 $ of the number of ways to choose the upper side of each coin in such a way, that on each Arkady's photo there is at least one coin with obverse side up, and on each Kirill's photo there is at least one coin with reverse side up.

## 说明/提示

In the first example the following ways are possible ('O' — obverse, 'R' — reverse side):

- OROOR,
- ORORO,
- ORORR,
- RROOR,
- RRORO,
- RRORR,
- ORROR,
- ORRRO.

In the second example the information is contradictory: the second coin should have obverse and reverse sides up at the same time, that is impossible. So, the answer is $ 0 $ .

## 样例 #1

### 输入

```
5 2 2
1 3
3 5
2 2
4 5
```

### 输出

```
8
```

## 样例 #2

### 输入

```
5 3 2
1 3
2 2
3 5
2 2
4 5
```

### 输出

```
0
```

## 样例 #3

### 输入

```
60 5 7
1 3
50 60
1 60
30 45
20 40
4 5
6 37
5 18
50 55
22 27
25 31
44 45
```

### 输出

```
732658600
```

# 题解

## 作者：Saliеri (赞：10)

题外话：本题的主要难点在于不去想容斥（

___
考虑正面为 1，反面为 0。

先来考虑最最暴力的 dp，为了考虑限制，我们设 $dp_{i,l_0,l_1}$ 表示考虑了前 i 个位置，上一个 0 在 $l_0$，上一个 1 在 $l_1$ 的方案数。

转移都非常显然，处理限制就直接将不合法的 dp 值置为 0 即可。但是这样的时间复杂度是 $O(k^3)$。

一个非常显然的性质——最后一位必然是 0 或 1。我们可以据此砍掉一维。

我们现在设 $dp_{0,i,l_1},dp_{1,i,l_0}$ 分别表示最后一位是 0/1，现在考虑了前 $i$ 位，上一个 1/0 在 $l_{1/0}$ 时的方案数。

一切依旧很显然，但是复杂度依然高达 $O(k^2)$。

按照一般套路，对于这种值域很大但是涉及到的坐标很少的题，考虑**离散化**后求解。

或者说因为，为了处理限制，我们并不需要关心上一个 0/1 在某两个离散化后的点之间的具体哪个位置，只需要知道在这两个之间即可。所以可以离散化。

那么我们将所有限制中的 $l_i,r_i$ 丢去离散化，设 $\{\text{lsh}\}$ 为离散化的前的值。

现在我们可以重定义 dp 数组的最后一维——其为 $x$ 表示真正的 0/1 处于 $\text{lsh}_{x-1}+1\sim \text{lsh}_x$ 之间。

来重新考虑转移与限制。不失一般性，我们只考虑 $dp_{0,i,l_1}$ 往后的转移，对于 $dp_{1,i,l_0}$ 的思路很对称。

处理转移的思路显然是：补上 $\text{lsh}_i+1\sim\text{lsh}_{i+1}$ 的 0/1，看不同的填法会转移到哪些位置。分情况讨论：

- 如果全部填 0，$1\times dp_{0,i,l_1}\rightarrow dp_{0,i+1,l_1}$。

- 如果全部填 1，$1\times dp_{0,i,l_1}\rightarrow dp_{1,i+1,i}$。

- 如果 0/1 混杂，那么我们固定最后一位，并且强制不能与上面两种转移重复：$(2^{\text{lsh}_{i+1}-\text{lsh}_i-1}-1)\times dp_{0,i,l_1}\rightarrow \begin{cases}dp_{0,i+1,i+1}\\dp_{1,i+1,i+1}\end{cases}$。

处理限制时，我们对于离散化后右端点在 $i+1$ 的每一个 “$[l,i+1]$ 中至少一个 1” 的限制，将 $l_1<l$ 的 $dp_{0,i,l_1}$ 因不合法置 0 即可。

有些读者在这里会发现一个问题——如果 $l_1 = l$，那么有可能合法也有可能不合法？的确如此，我们需要规避这一点。

解决方案是：将所有 $l_i -1$ 也放进去离散化即可。正确性显然。

至此，我们得到了一个 $O((n+m)^2\log k)$ 的做法，来接着优化。

优化思路是：我们把 $i$ 这一维滚动，**快速处理 $dp_{0,l_1}$ 的变化**即可。

- 对于第一种转移，相当于原封不动的 copy，不讨论。

- 对于第二种转移，因为对于所有的 $l_1$，dp 值都会转移至 $dp_{1,i+1,i}$，所以只需要动态维护 $\sum_{l_1}dp_{0,i,l_1}$ 即可完成转移。

- 第三种情况类似。

但是我们还需要动态地支持将一段前缀置 0 的操作。你可以采用线段树等数据结构维护，但是大可不必。

发现转移中，只有 $dp_{0/1,i+1,i/i+1}$ 可能会得到新的值，换言之，一旦一个位置被置 0，那他就永远为 0。

于是为 0 的部分是一个随着 $i$ 增加，长度不降的前缀。我们用一个指针维护那个前缀位置就可以做到均摊线性。

这下真的做完了，时间复杂度 $O((n+m)(\log(n+m)+\log k))$。

代码：

```cpp
#include <cstdio>
#include <algorithm>
const int maxn = 1e5+5,maxM = 6e5+5,mod = 1e9+7,i2 = 5e8+4;
inline int ksm(int a,int x){
	int bas = a,ans = 1;
	while(x){
		if(x&1)ans = 1ll*ans*bas%mod;
		bas = 1ll*bas*bas%mod,x >>= 1;
	}return ans;
}
int k,n,m,lsh[maxM],M;
void gmax(int &x,int v){(x<v?x=v:0);}
int getId(int x){return std :: lower_bound(lsh+1,lsh+M+1,x)-lsh;}
struct itv{int l,r;}b[maxn],w[maxn];
int dp[2][maxM],maxb[maxM],maxw[maxM];
int main(){
	scanf("%d %d %d",&k,&n,&m),lsh[++M] = 0,lsh[++M] = k;
	for(int i=1;i<=n;++i)
		scanf("%d %d",&b[i].l,&b[i].r),lsh[++M] = b[i].l,lsh[++M] = b[i].l-1,lsh[++M] = b[i].r;
	for(int i=1;i<=m;++i)
		scanf("%d %d",&w[i].l,&w[i].r),lsh[++M] = w[i].l,lsh[++M] = w[i].l-1,lsh[++M] = w[i].r;
	std :: sort(lsh+1,lsh+M+1),M = std :: unique(lsh+1,lsh+M+1)-lsh-1;
	for(int i=1;i<=n;++i)gmax(maxb[getId(b[i].r)],getId(b[i].l));
	for(int i=1;i<=m;++i)gmax(maxw[getId(w[i].r)],getId(w[i].l));
	dp[0][1] = dp[1][1] = 1;int sum0=1,sum1=1,pos0=0,pos1=0;
	for(int i=1,t;i<M;++i){
		dp[1][i] = (dp[1][i]+sum0)%mod,dp[0][i] = (dp[0][i]+sum1)%mod;
		t = 1ll*(ksm(2,lsh[i+1]-lsh[i]-1)-1)*(sum0+sum1)%mod;
		dp[0][i+1] = (dp[0][i+1]+t)%mod,dp[1][i+1] = (dp[1][i+1]+t)%mod;
		sum0 = sum1 = (1ll*t+sum0+sum1)%mod;
		while(pos0+1<maxw[i+1])sum0 = (sum0-dp[0][++pos0]+mod)%mod;
		while(pos1+1<maxb[i+1])sum1 = (sum1-dp[1][++pos1]+mod)%mod;
	}
	return printf("%d\n",1ll*(sum0+sum1)*i2%mod),0;
}
```

---

## 作者：do_while_true (赞：7)

看到题就先容斥。然后容斥系数太难算了就寄了，大概要分好几种情况讨论，于是就弃了。

不容斥也能做。考虑限制将串划分成了若干段，然后一段一段 dp．

有没有什么好的方法描述这个性质？这里考虑的是，如果强制 $[l,r]$ 至少出现一个 $1$，那么就让 $r$ 及以后的点，让它们往前找第一个 $1$ 的位置要 $\geq l$．$0$ 也类似计算一个这个东西。

然后 dp，$f_i,g_i,h_i$ 分别表示，第 $i$ 个端点结尾的这一段，全选 $0$，全选 $1$，既有 $0$ 又有 $1$ 的方案数。即有转移 $h_i=(2^{len_i}-2)(f_{i-1}+g_{i-1}+h_{i-1})$．

而 $f$ 的转移就是枚举上一个 $0$ 在哪一段里面，那么这个就是一个后缀的 $g$ 和 $h$ 的和。前缀和优化转移即可。$g$ 的转移也是类似的。

```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<random>
#include<assert.h>
#define pb emplace_back
#define mp make_pair
#define fi first
#define se second
#define dbg(x) cerr<<"In Line "<< __LINE__<<" the "<<#x<<" = "<<x<<'\n';
#define dpi(x,y) cerr<<"In Line "<<__LINE__<<" the "<<#x<<" = "<<x<<" ; "<<"the "<<#y<<" = "<<y<<'\n';
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int>pii;
typedef pair<ll,int>pli;
typedef pair<ll,ll>pll;
typedef pair<int,ll>pil;
typedef vector<int>vi;
typedef vector<ll>vll;
typedef vector<pii>vpii;
typedef vector<pil>vpil;
template<typename T>T cmax(T &x, T y){return x=x>y?x:y;}
template<typename T>T cmin(T &x, T y){return x=x<y?x:y;}
template<typename T>
T &read(T &r){
	r=0;bool w=0;char ch=getchar();
	while(ch<'0'||ch>'9')w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9')r=r*10+(ch^48),ch=getchar();
	return r=w?-r:r;
}
template<typename T1,typename... T2>
void read(T1 &x,T2& ...y){read(x);read(y...);}
const int mod=1000000007;
inline void cadd(int &x,int y){x=(x+y>=mod)?(x+y-mod):(x+y);}
inline void cdel(int &x,int y){x=(x-y<0)?(x-y+mod):(x-y);}
inline int add(int x,int y){return (x+y>=mod)?(x+y-mod):(x+y);}
inline int del(int x,int y){return (x-y<0)?(x-y+mod):(x-y);}
int qpow(int x,int y){
	int s=1;
	while(y){
		if(y&1)s=1ll*s*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return s;
}
const int N=2000010;
int k,n,m;
int p[N],tot,p1[N],p2[N];
int f[N],g[N],h[N],F[N],G[N],H[N];
pii a[N],b[N];
int pos(int x){
	return lower_bound(p+1,p+tot+1,x)-p;
}
int calc(int *a,int l,int r){
	return del(a[r],a[l]);
}
signed main(){
	#ifdef do_while_true
//		assert(freopen("data.in","r",stdin));
//		assert(freopen("data.out","w",stdout));
	#endif
	read(k,n,m);
	p[++tot]=k;p[++tot]=0;
	for(int i=1;i<=n;i++){
		read(a[i].fi,a[i].se);--a[i].fi;
		p[++tot]=a[i].fi,p[++tot]=a[i].se;
	}
	for(int i=1;i<=m;i++){
		read(b[i].fi,b[i].se);--b[i].fi;
		p[++tot]=b[i].fi,p[++tot]=b[i].se;
	}
	sort(p+1,p+tot+1);
	tot=unique(p+1,p+tot+1)-p-1;
	for(int i=1;i<=n;i++)
		cmax(p1[pos(a[i].se)],pos(a[i].fi));
	for(int i=1;i<=m;i++)
		cmax(p2[pos(b[i].se)],pos(b[i].fi));
	for(int i=1;i<=tot;i++)cmax(p1[i],p1[i-1]),cmax(p2[i],p2[i-1]);
//	for(int i=1;i<=tot;i++)cout << p1[i] << ' ' << p2[i] << '\n';
	h[1]=H[1]=1;
	for(int i=2;i<=tot;i++){
		f[i]=add(calc(G,p1[i],i-1),calc(H,p1[i],i-1));
		g[i]=add(calc(F,p2[i],i-1),calc(H,p2[i],i-1));
		h[i]=1ll*del(qpow(2,p[i]-p[i-1]),2)*add(add(f[i-1],g[i-1]),h[i-1])%mod;
		F[i]=add(F[i-1],f[i]);
		G[i]=add(G[i-1],g[i]);
		H[i]=add(H[i-1],h[i]);
//		cout << f[i] << ' ' << g[i] << ' ' << h[i] << '\n';
	}
	cout << add(add(f[tot],g[tot]),h[tot]) << '\n';
    #ifdef do_while_true
		cerr<<'\n'<<"Time:"<<1.0*clock()/CLOCKS_PER_SEC*1000<<" ms"<<'\n';
	#endif
	return 0;
}
```

---

## 作者：wurzang (赞：6)

看到有老哥说什么“本题的主要难点在于不去想容斥”，于是来提供一个容斥做法（

此容斥做法来源于 @Autumnkite 的指导，他好像表示这是容斥套路。

## 题解

一个指数级做法是直接钦定某些区间不满足条件，然后算它们的并集，它们的容斥系数是 $(-1)^{\text{区间个数}}\times 2^{n-\text{并集大小}}$，把这个拆解一下就是 $(-1)^{\text{区间个数}} \times \dfrac{1}{2^{\text{并集大小}}}$，需要值得一提的是区间如果有相交的，那么它们的种类应当相同。

我们考虑对以上的暴力过程进行 dp 优化，$f_{i}$ 表示前 $i$ 个区间里第 $i$ 个区间必须选，其他区间随便选的容斥系数之和。

对于相离的区间，显然容斥系数就是 $-\dfrac{1}{2^{r_i-l_i+1}}$，算下 $f_i$ 的前缀和然后 dp 转移就可以了。

对于相交的区间，显然如果这个区间要考虑的话，和 $i$ 应当是同一个种类的区间。主要难点在于怎么算并集，然后我们发现并集是以 $r_i-r_j$ 的形式增加的，所以我们就算一下 $f_j \times 2^{-r_j}$ 的前缀和就好了，dp 转移过程也是差不多的。

包含情况如果直接考虑容斥就比较复杂，然而我们发现一个区间 $i$ 如果包含某个区间，那么这个区间对容斥系数的贡献是 $0$（具体证明的话就是根据题意，区间 $i$ 显然无用），一种处理方法是把区间排序后让 $l_i$ 取前缀 $\max$，这样就可以把包含情况处理成相交情况，且对容斥系数的贡献仍然是 $0$。

如果看不懂的话可以看代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,mod=1e9+7,inv2=(mod+1)/2;
int ksm(int b,int n){
    int res=1;
    while(n){
        if(n&1) res=1ll*res*b%mod;
        b=1ll*b*b%mod; n>>=1;
    }
    return res;
}
struct segment{
    int l,r,type;
    bool operator < (const segment & b) const {
        if(r == b.r) return l > b.l;
        return r < b.r;
    }
}a[N],b[N],c[N];
int f[N],s[N],sum[2][N];
void merge(int n,int m){
    int i=1,j=1,k=1;
    while(i<=n && j<=m){
        if(a[i]<b[j]) c[k++]=a[i++];
        else c[k++]=b[j++];
    }
    while(i<=n) c[k++]=a[i++];
    while(j<=m) c[k++]=b[j++];
}
int Find(int i,int val){
    int p=0,l=1,r=i;
    for(int cnt=0;cnt<=100;++cnt){
        int mid=(l+r)>>1;
        if(c[mid].r>val) p=mid,r=mid-1;
        else l=mid+1;
    }
    return p;
}
signed main(){
    ios::sync_with_stdio(false);
    int k,n,m;
    cin>>k>>n>>m;
    for(int i=1;i<=n;++i) cin>>a[i].l>>a[i].r,a[i].l--,a[i].type=0;
    for(int i=1;i<=m;++i) cin>>b[i].l>>b[i].r,b[i].l--,b[i].type=1;
    sort(a+1,a+n+1),sort(b+1,b+m+1);
    for(int i=1;i<=n;++i) a[i].l=max(a[i-1].l,a[i].l);
    for(int i=1;i<=m;++i) b[i].l=max(b[i-1].l,b[i].l);
    merge(n,m);
    int ans=1;
    for(int i=1;i<=n+m;++i){
        int t1=mod-ksm(inv2,c[i].r-c[i].l),t2=mod-ksm(inv2,c[i].r);
        int p=Find(i,c[i].l);
        f[i]=(1ll*t1*((p==0?0:s[p-1])+1)+1ll*t2*(p==i?0:(mod+sum[c[i].type][i-1]-sum[c[i].type][p-1])))%mod;
        s[i]=(s[i-1]+f[i])%mod;
        sum[!c[i].type][i]=sum[!c[i].type][i-1];
        sum[c[i].type][i]=(sum[c[i].type][i-1]+1ll*f[i]*ksm(2,c[i].r))%mod;
        ans=(ans+f[i])%mod;
    }
    cout<<1ll*ans*ksm(2,k)%mod;
    return 0;
}
```


---

## 作者：Miraik (赞：5)

看上去不好下手，我们应该从暴力出发。

首先来一个不用脑子的暴力：设 $f_{i,0/1,j}$ 表示处理了前 $i$ 个位置，$a_i=0/1$，且 $j$ 为最近一个满足 $a_j \neq a_i$ 的位置的合法方案数。直接做复杂度 $O(k^2)$，肯定是不行的。

当然我们需要离散化一下，改成一段一段区间转移。我们记离散化后第 $i$ 段区间的最后一个位置为 $r_i$。

修改一下 dp 状态：$f_{i,0/1,j}$ 表示处理到第 $i$ 个区间，$a_{r_i}=0/1$， 上一个满足 $a_x \neq a_{r_i}$ 的位置 $x$ 处在第 $j$ 个区间的合法方案数。以 $f_{i,0,j}$ 为例，依次考虑以下转移：

1. 整个区间全部填 $0$

$f_{i,0,j} \to f_{i+1,0,j}$

2. 整个区间全部填 $1$

$f_{i,0,j} \to f_{i+1,1,i}$

3. 区间内有 $0$ 和 $1$，且 $a_{r_i}=0$

$f_{i,0,j} \times (2^{len_i-1}-1) \to f_{i+1,0,i+1}$

4. 区间内有 $0$ 和 $1$，且 $a_{r_i}=1$

$f_{i,0,j} \times (2^{len_i-1}-1) \to f_{i+1,1,i+1}$

其中 $len_i$ 表示第 $i$ 段区间的长度。

对于 $f_{i,1,j}$ 的转移是类似的。

再考虑去除掉不合法的方案，每一层 $i$ 转移完后，我们对于形如 $[0/1,x,i+1]$ 的限制，将对应的 $f_{i+1,1/0,j}(j<x)$ 置为 $0$ 即可。此时你应该注意到，我们在离散化时需要将 $x-1$ 也进行离散化，否则 $x$ 之前所在的一段会没有被覆盖到。

这样我们就得到了一个 $O((n+m)^2)$ 的做法。它还是过不了。

```cpp
    f[1][0][1]=1;
    for(int i=1;i<lcnt;i++){
        int siz=b[i+1]-b[i],val=(qpow(siz-1)+mod-1)%mod;
        for(int j=1;j<=i;j++){
            (f[i+1][0][j] += f[i][0][j]) %= mod;
            (f[i+1][1][i] += f[i][0][j]) %= mod;
            (f[i+1][0][i+1] += 1ll*val*f[i][0][j]%mod) %= mod;
            (f[i+1][1][i+1] += 1ll*val*f[i][0][j]%mod) %= mod;
            (f[i+1][1][j] += f[i][1][j]) %= mod;
            (f[i+1][0][i] += f[i][1][j]) %= mod;
            (f[i+1][1][i+1] += 1ll*val*f[i][1][j]%mod) %= mod;
            (f[i+1][0][i+1] += 1ll*val*f[i][1][j]%mod) %= mod;
        }
        for(int j=0;j<q[i+1].size();j++)
            for(int k=0;k<q[i+1][j].l;k++)
                f[i+1][q[i+1][j].v^1][k]=0;
    }
    for(int j=1;j<=lcnt;j++) (ans += (f[lcnt][0][j]+f[lcnt][1][j])%mod ) %= mod;
    printf("%d\n",ans);
```


但其实接下来的优化是简单的。我们考虑跟随 $i$ 的移动，动态维护整个 dp 过程。对应上面转移的标号：

- 1 和 2 不需要做任何事。

- 3 和 4 事实上是一个 **全局和** 的形式。

- 去除掉不合法的方案相当于前缀推平为 $0$。

这其实都不需要任何数据结构维护了，我们可以直接对于前缀维护推平指针（显然一个位置被推平后就永远都是 $0$ 了），并维护好 $0/1$ 的全局和就可以了。

时间复杂度为 $O((n+m) \log (n+m) + (n+m) \log k)$，前面是离散化的复杂度，后面是算贡献那里求一个快速幂的复杂度。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N=600005;
const int mod=1000000007;
inline int read(){
    int x=0,f=1; char c=getchar();
    while(c<'0'||c>'9'){ if(c=='-') f=-1; c=getchar(); }
    while(c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
    return x*f;
}
/*
dp[i][0/1][j] : 处理到第 i 个区间 sta[r[i]]=0/1 上一个与 sta[r[i]] 不一样的位置在第 j 个区间 
1.dp[i][0][j] -> dp[i+1][0][j]
2.dp[i][0][j] -> dp[i+1][1][i]
3.dp[i][0][j]*(2^(len-1)-1) -> dp[i+1][0/1][i+1]

1.dp[i][1][j] -> dp[i+1][1][j]
2.dp[i][1][j] -> dp[i+1][0][i]
3.dp[i][1][j]*(2^(len-1)-1) -> dp[i+1][0/i][i+1]

考虑动态维护
1. 不用动
2. 一个全局和的形式
3. 一个全局和的形式
4. 前缀推平为 0
不需要 ds 就能维护
*/
int K,m,n,lcnt,b[N],dp[2][N],sum[2],pos[2]={1,1},ans;
struct A{
    int l,r;
}a[N];
struct Q{
    int l,v;
};  vector<Q>q[N];
inline int qpow(int y){
    int x=2,r=1;
    while(y){
        if(y&1) r=1ll*r*x%mod;
        x=1ll*x*x%mod;
        y>>=1;
    }
    return r;
}
int main(){
    K=read(),n=read(),m=read();
    for(int i=1;i<=n;i++){
        a[i].l=read(),a[i].r=read();
        b[++lcnt]=a[i].l-1; b[++lcnt]=a[i].l; b[++lcnt]=a[i].r;
    }
    for(int i=n+1;i<=n+m;i++){
        a[i].l=read(),a[i].r=read();
        b[++lcnt]=a[i].l-1; b[++lcnt]=a[i].l; b[++lcnt]=a[i].r;
    }
    b[++lcnt]=0; b[++lcnt]=1; b[++lcnt]=K;
    sort(b+1,b+lcnt+1); lcnt=unique(b+1,b+lcnt+1)-b-1;
    for(int i=1;i<=n+m;i++){
        int j=lower_bound(b+1,b+lcnt+1,a[i].r)-b,k=lower_bound(b+1,b+lcnt+1,a[i].l)-b;
        q[j].emplace_back(Q{k,(i>n)});
    }
    dp[0][1]=sum[0]=1;
    for(int i=1;i<lcnt;i++){
        int siz=b[i+1]-b[i],val=(qpow(siz-1)+mod-1)%mod,tot=(sum[0]+sum[1])%mod;
        (dp[0][i] += sum[1]) %= mod;
        (dp[0][i+1] += 1ll*tot*val%mod) %= mod;
        (dp[1][i] += sum[0]) %= mod;
        (dp[1][i+1] += 1ll*tot*val%mod) %= mod;
        int nxt = ( (sum[0] + sum[1]) % mod + 1ll*tot*val%mod ) % mod;
        sum[0]=sum[1]=nxt;
        for(int j=0;j<q[i+1].size();j++){
            int op=q[i+1][j].v^1;
            while(pos[op]<q[i+1][j].l)
                (sum[op]+=mod-dp[op][pos[op]])%=mod,dp[op][pos[op]]=0,pos[op]++;
        }
    }
    for(int j=1;j<=lcnt;j++) (ans += (dp[0][j]+dp[1][j])%mod ) %= mod;
    printf("%d\n",ans);
    return 0;
}
```


---

## 作者：BreakPlus (赞：4)

## Solution CF930E

谁在那里说本题难点在于不去想容斥？？

**容斥好闪，拜谢容斥。**

----

考虑选取一个限制条件的子集不满足限制（即这一段全 0 或全 1）。我们发现**没有被限制的点**有两种选择，也就是我们只关心这玩意的数量。但是我们也可以关心**被限制的点**的数量。

我们发现限制的点对答案会乘 $1$，没有限制的会对答案乘 $2$；两种情况同除以 $2$，限制的点对答案贡献即为 $\dfrac{1}{2}$，没有限制的乘 $1$，直接不用考虑，最后得出结果乘 $2^k$ 即可。

（下文中“线段”指被限制的线段）

我们发现**依托点**来做 DP 不是很好做，面临大值域的麻烦。所以我们**依托线段**来 DP。



---

考虑将线段**简化**。同色线段包含关系中，最里面的那个才有用。这启发我们把无用线段去掉。

具体地，先对于一个左端点，只保留编号最小的右端点；然后从右往左考虑左端点，强制右端点递减，保留一个左端点、右端点同时递增或递减的线段集合。

---

按照右端点排序，设 $f(i)$ 表示第 $i$ 个线段选上，前 $i$ 个线段的容斥结果。**关于上一个被选的线段**，分情况讨论。



1. 这个点本身为第一个选择的线段。

2. 这个点的上一个线段与这个线段无交集。此时上一个线段颜色任意，且被限制的点数增加当前线段长度。

3. 这个点的线段与上一个线段有交集。此时颜色必须相同，被限制的点数增加两个线段右端点之差。

(2)(3) 两条均可以前缀和优化解决。

```cpp
ll k,n,m; map<ll,ll>M1, M2;
struct Node{
	ll l,r,col;
}node[200005]; ll cnt;
bool operator< (Node A,Node B){
	return A.r < B.r;
}
ll f[200005],sum[200005],sum2[2][200005];
void solve(){
	k=read(), n=read(), m=read();
	ll inv2 = qpow(2, mod-2);
	M1[0] = 1; M2[0] = 1;
	for(ll i=1;i<=n;i++){
		ll l=read(), r=read();
		if(!M1.count(l)) M1[l]=r;
		else M1[l] = minn(M1[l], r);
	}
	for(ll i=1;i<=m;i++){
		ll l=read(), r=read();
		if(!M2.count(l)) M2[l]=r;
		else M2[l] = minn(M2[l], r);
	}
	ll now = 2e9;
	for(auto it = (--M1.end()); it!=M1.begin(); --it){
		auto x = (*it);
		if(x.se < now){
			now = x.se;
			node[++cnt] = (Node){x.fi, x.se, 0};
		}
	} now = 2e9;
	for(auto it = (--M2.end()); it!=M2.begin(); --it){
		auto x = (*it);
		if(x.se < now){
			now = x.se;
			node[++cnt] = (Node){x.fi, x.se, 1};
		}
	} // 简化线段
	sort(node+1,node+cnt+1);
	f[0] = 1; // 注意不选的情况
	for(ll i=1;i<=cnt;i++){
		f[i] = (f[i] - qpow(inv2, node[i].r-node[i].l+1) + mod) % mod; // (1)
		if(i>1){
			Node Temp = (Node){0,node[i].l,0};
			ll pos = lower_bound(node+1,node+i,Temp) - node; // 找到第一个与之有交的线段
			if(pos>1){
				pos--;
				f[i] = (f[i] - sum[pos] * qpow(inv2, node[i].r-node[i].l+1) % mod + mod) % mod; // (2)
			}else pos--;
			f[i] = (f[i] - (sum2[node[i].col][i-1] - sum2[node[i].col][pos] + mod) * qpow(inv2, node[i].r) % mod + mod) % mod; // (3)
		}
		sum[i] = (sum[i-1] + f[i]) % mod;
		
		sum2[0][i] = (sum2[0][i-1] + (node[i].col==0) * f[i] * qpow(2,node[i].r) % mod) % mod;
		sum2[1][i] = (sum2[1][i-1] + (node[i].col==1) * f[i] * qpow(2,node[i].r) % mod) % mod; // 前缀和优化
	}
	ll ans = 0;
	for(ll i=0;i<=cnt;i++){
		ans = (ans + f[i]) % mod;
	}
	ans = ans * qpow(2, k) % mod;
	printf("%lld\n", ans);
}
```

---

## 作者：skylee (赞：3)

# [CF930E]/[CF944G]Coins Exhibition

### 题目地址：

[CF930E](http://codeforces.com/contest/930/problem/E)/[CF944G](http://codeforces.com/contest/944/problem/G)

### 博客地址：

[[CF930E]/[CF944G]Coins Exhibition - skylee](https://www.cnblogs.com/skylee03/p/9078791.html)

### 题目大意：

一个长度为$k(k\le10^9)$的$01$串，给出$n+m(n,m\le10^5)$个约束条件，其中$n$条描述区间$[l_i,r_i]$至少有一个$0$，其中$m$条描述区间$[l_i,r_i]$至少有一个$1$。求合法的$01$串数量。

### 思路：

显然直接考虑所有的$k$位，就算$\mathcal O(k)$的线性算法也会超时，因此对于所有的$l_i-1,r_i$以及$0,k$离散化以后考虑这些关键点即可。

设关键点有$lim$个，对所有关键点排序，$tmp[i]$为$i$离散化前对应的数。对所有关键点排序，考虑动态规划，设$f[i][j\in\{0,1,2\}]$表示从后往前考虑第$i\sim lim$个关键点。若$j\in\{0,1\}$，则$f[i][j]$表示$tmp[i]\sim tmp[i+1]$中含有$j$的方案数后缀和。若$j=2$，则$f[i][j]$表示最后一段同时有$0$和$1$的方案数。用$min[j\in\{0,1\}][i]$表示对应约束条件类型为$j$，$i$右侧最近的、对应左端点不在$i$左侧的右端点。状态转移方程如下：

- $f[i][0]=f[i+1][0]+f[i+1][1]-f[min[1][i]][1]+f[i+1][2]\times(2^{tmp[i+1]-tmp[i]}-2)$
- $f[i][1]=f[i+1][1]+f[i+1][0]-f[min[0][i]][0]+f[i+1][2]\times(2^{tmp[i+1]-tmp[i]}-2)$
- $f[i][2]=f[i+1][0]-f[min[0][i]][0]+f[i+1][1]-f[min[1][i]][1]+f[i+1][2]\times(2^{tmp[i+1]-tmp[i]}-2)$

最终答案为$f[0][2]$。

时间复杂度$\mathcal O((n+m)(\log(n+m)+\log k))$。其中$\mathcal O(\log(n+m))$为离散化复杂度，$\mathcal O(\log k)$为快速幂复杂度。

### 源代码：

```cpp
#include<cstdio>
#include<cctype>
#include<algorithm>
using int64=long long;
inline int getint() {
	register char ch;
	while(!isdigit(ch=getchar()));
	register int x=ch^'0';
	while(isdigit(ch=getchar())) x=(((x<<2)+x)<<1)+(ch^'0');
	return x;
}
constexpr int N=1e5,mod=1e9+7;
std::pair<int,int> p[2][N];
int tmp[N*4+2],min[2][N*4+2],f[N*4+2][3];
inline int power(int a,int k) {
	int ret=1;
	for(;k;k>>=1) {
		if(k&1) ret=(int64)ret*a%mod;
		a=(int64)a*a%mod;
	}
	return ret;
}
int main() {
	const int k=getint(),n=getint(),m=getint();
	int lim=0;
	for(register int i=0;i<n;i++) {
		tmp[++lim]=p[0][i].first=getint()-1;
		tmp[++lim]=p[0][i].second=getint();
	}
	for(register int i=0;i<m;i++) {
		tmp[++lim]=p[1][i].first=getint()-1;
		tmp[++lim]=p[1][i].second=getint();
	}
	tmp[++lim]=k;
	std::sort(&tmp[0],&tmp[lim]+1);
	lim=std::unique(&tmp[0],&tmp[lim]+1)-&tmp[1];
	for(register int i=0;i<=lim;i++) {
		min[0][i]=min[1][i]=lim+1;
	}
	for(register int i=0;i<n;i++) {
		p[0][i].first=std::lower_bound(&tmp[0],&tmp[lim]+1,p[0][i].first)-tmp;
		p[0][i].second=std::lower_bound(&tmp[0],&tmp[lim]+1,p[0][i].second)-tmp;
		min[0][p[0][i].first]=std::min(min[0][p[0][i].first],p[0][i].second);
	}
	for(register int i=0;i<m;i++) {
		p[1][i].first=std::lower_bound(&tmp[0],&tmp[lim]+1,p[1][i].first)-tmp;
		p[1][i].second=std::lower_bound(&tmp[0],&tmp[lim]+1,p[1][i].second)-tmp;
		min[1][p[1][i].first]=std::min(min[1][p[1][i].first],p[1][i].second);
	}
	for(register int i=lim;i;i--) {
		min[0][i-1]=std::min(min[0][i-1],min[0][i]);
		min[1][i-1]=std::min(min[1][i-1],min[1][i]);
	}
	f[lim][0]=f[lim][1]=f[lim][2]=1;
	for(register int i=lim-1;i>=0;i--) {
		int g[3];
		g[0]=(f[i+1][0]-f[min[0][i]][0]+mod)%mod;
		g[1]=(f[i+1][1]-f[min[1][i]][1]+mod)%mod;
		g[2]=(int64)f[i+1][2]*((power(2,tmp[i+1]-tmp[i])-2+mod)%mod)%mod;
		f[i][0]=((int64)f[i+1][0]+g[1]+g[2])%mod;
		f[i][1]=((int64)f[i+1][1]+g[0]+g[2])%mod;
		f[i][2]=((int64)g[0]+g[1]+g[2])%mod;
	}
	printf("%d\n",f[0][2]);
	return 0;
}
```



---

## 作者：EmptyAlien (赞：1)

[CF930E](https://codeforces.com/problemset/problem/930/E)。

很水的 2900，连我都想出来了。

---

第一步，离散化，把所有区间离散化了，因为我们只关心每个硬币对每个区间的包含关系，并不在乎它具体是哪个。

先打暴力：设 $f_{i,j,0/1}$ 表示考虑到了第 $i$ 个段，上个与当前硬币不同面的硬币的位置在哪个段里，还有当前段最后一个硬币的正反。

正为 $1$，反为 $0$。

则易得出转移方程。

在这段里全部填 $0$：
$$
f_{i,j,0} \to f_{i + 1,j, 0}
$$

$$
f_{i,j,1}\to f_{i+1,i,0}
$$

全部添 $1$：
$$
f_{i,j,1}\to f_{i+1,j,1}
$$

$$
f_{i,j,0} \to f_{i+1,i,1}
$$

$0,1$ 混杂，此处之所以要减一是因为你要固定最后一个的正反：
$$
(2^{len-1}-1)f_{i,j,0/1}\to f_{i+1,i+1,1}
$$

$$
(2^{len-1} - 1)f_{i,j,0/1} \to f_{i+1,i+1, 0}
$$

注意由于要考虑限制：如果不考虑离散化则，在 $[l,r]$ 内至少有一个 $1$，此时考虑到第 $i$ 个硬币，则 $f_{r,i,0}\space(i<l)$ 是不合法的，应置为 $0$。

而离散化之后小于不好刻画，故我们考虑把 $l-1$ 扔进去离散化而不是 $l$。

这样条件就能刻画为：对于每个状态 $f_{r,i,0} \space (i \le  l-1)$ 算完之后我们将其清零。

注意到由于只有在 $f_i$ 与 $f_{i+1}$ 之间转移，我们滚动数组。

滚完之后发现，除了清零之外，改变的位置个数是 $O(1)$ 的，即 $f_{i+1,0/1}$ 与 $f_{i,0/1}$。

而在这些的转移式中所有的 $j$ 它们都会产生固定 $1$ 或 $(2^{len-1} - 1)$ 的贡献。

这启发我们维护当前 $f_{*,0}$ 的和与 $f_{*,1}$ 的和。

每次将对应的贡献乘上总和加上去集合。

于是除了清零之外的操作我们都能在 $O((n+m)\log k+(n+m)\log (n+m))$ 的时间内解决了。

那清零怎么办呢？

由于只有 $f$ 的后边会发生变化，前边的变化只有清零，因此一个格子如果被清零它就彻底没戏了。

于是我们记录 $f_{*,0/1}$ 的两个指针指向当前数组中第一个非零，如果要清空更多零暴力移指针就行了。

因为每清一个零指针就向后一格，而指针单调向后走所以均摊复杂度 $O(n+m)$。

于是我们就做完了。

小细节：

- 初始条件是 $f_{0,0/1}=1$。
- 离散化的时候要把 $0,k$ 加入，因为他们是 DP 的起点与终点。
- 输出答案的时候要除以 $2$，因为你多算了 $0$ 号硬币的正反但压根就不存在 $0$ 号硬币。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define debug(x) cerr << #x << " = " << x << endl
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define per(i, a, b) for (int i = (a); i >= (b); i--)
#define gn(u, v) for (int v : G.G[u])
#define pb emplace_back
#define mp make_pair
#define fi first
#define se second
#define sz(x) (int)(x).size()
#define pii pair<int, int>
#define vi vector<int>
#define vpii vector<pii>
#define vvi vector<vi>
#define no cout << "NO" << endl
#define yes cout << "YES" << endl
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define tomin(x, y) ((x) = min((x), (y)))
#define tomax(x, y) ((x) = max((x), (y)))
#define ck(mask, i) (((mask) >> (i)) & 1)
#define pq priority_queue
#define umap unordered_map
#define FLG (cerr << "Alive!" << endl);

constexpr int MAXN = 5e5 + 5;
constexpr int MOD = 1e9 + 7;
int k, n, m;
int l[MAXN], r[MAXN], sum[2], f[MAXN][2];
int c[MAXN], tot;

int chk[2][MAXN], tic[2] = { -1, -1 };

int qpow(int x, int y) {
    if (y < 0) return 0;
    int ans = 1;
    while (y) {
        if (y & 1)
            ans = ans * x % MOD;
        x = x * x % MOD;
        y >>= 1;
    }
    return ans;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> k >> n >> m;
    rep (i, 1, n + m) {
        cin >> l[i] >> r[i];
        l[i]--;
        c[++tot] = l[i];
        c[++tot] = r[i];
    }
    c[++tot] = 0;
    c[++tot] = k;
    sort(c + 1, c + tot + 1);
    tot = unique(c + 1, c + tot + 1) - c - 1;
    rep (i, 1, n + m) {
        l[i] = lower_bound(c + 1, c + tot + 1, l[i]) - c;
        r[i] = lower_bound(c + 1, c + tot + 1, r[i]) - c;
    }

    memset(chk, 0xff, sizeof chk);

    rep (i, 1, n)
        tomax(chk[0][r[i]], l[i]);

    rep (i, n + 1, n + m)
        tomax(chk[1][r[i]], l[i]);

    f[0][0] = f[0][1] = 1;
    int sum[2] = { 1, 1 };
    rep (i, 1, tot - 1) {
        (f[i][0] += sum[1]) %= MOD;
        (f[i][1] += sum[0]) %= MOD;
        int cur;
        if (c[i + 1] - c[i] == 1) cur = 0;
        else (cur = qpow(2, c[i + 1] - c[i] - 1) + MOD - 1) %= MOD;
        (cur *= sum[0] + sum[1]) %= MOD;
        (f[i + 1][0] += cur) %= MOD;
        (f[i + 1][1] += cur) %= MOD;
        sum[0] = sum[1] = (sum[0] + sum[1]) % MOD;
        (sum[0] += cur) %= MOD;
        (sum[1] += cur) %= MOD;
        while (tic[0] < chk[0][i + 1]) {
            tic[0]++;
            (sum[0] += MOD - f[tic[0]][0]) %= MOD;
        }
        while (tic[1] < chk[1][i + 1]) {
            tic[1]++;
            (sum[1] += MOD - f[tic[1]][1]) %= MOD;
        }
    }
    cout << (sum[0] + sum[1]) * (MOD + 1) / 2 % MOD << endl;

    return 0;
}
```

---

## 作者：Enoch006 (赞：0)

容斥好题！

考虑设 $p_i$ 表示第 $i$ 个区间**不**满足条件。

设 $f_s$ 表示**至少**满足集合 $s$ 里的条件的方案数；

 $\ \ \ \ g_s$ 表示**只**满足集合 $s$ 里的条件的方案数。

根据超集反演，答案为 $g_\varnothing=\sum_{s}(-1)^{|s|}f_s$，现在考虑 $f_s$ 的贡献。

若一个集合里面出现了一个点又黑又白，贡献为 $0$；否则 $f_s=(-1)^{|s|}2^{k-|\text{线段并}|}$，把 $2^k$ 提出来，就可以直接做线段并了。

对于这种**所有集合贡献**问题（一般是在容斥中），设 $f_i$ 表示**必选 $i$ 集合的情况下**，前 $i$ 个集合的贡献。这样，**转移**只需**枚举上一个必选的集合**即可，答案即为 $\sum_{i=1}^{n}f_i$。

对于这个题，转移顺序按照右端点从小到大，假设上一个选的区间为 $l$，考虑怎么转移：

1. 若 $i$ 区间与 $l$ 区间相离，那么贡献是 $-2^{-(R_i-L_i+1)}$。
2. 若 $i$ 区间与 $l$ 区间相交，那么 $l$ 必须与 $i$ 同色，贡献为 $-2^{-(R_i-R_l)}$。
3. 若 $i$ 区间包含 $l$ 区间，那么 $l$ 必须与 $i$ 同色。但是，我们并不知道 $l$ 前面与 $i$ 相交的是否共色，所以**包含关系无法转移**。
 解决方法是**直接去掉包含区间**！回到原题，如果两个同色区间互相包含，那么**外面的限制严格弱于里面的限制**，因此可以去掉**外面的限制**。
 这样处理过后，**同色**区间关系就**只存在相离和相交**了，而不好处理的只有同色区间包含关系，这就等于直接去掉包含关系了。

最后维护转移用**同色/所有颜色树状数组**就行了，记得拆贡献。


```cpp
#include <bits/stdc++.h>
#define int long long
#define maxm 1000005
#define maxn 1005
#define inf 0x3f3f3f3f3f3f
#define mod 1000000007
#define msk cerr
using namespace std;
int k,n,m,N,ans;
int qpow(int x,int y){
    int sum=1;
    while(y){
        if(y&1)sum=sum*x%mod;
        y>>=1;x=x*x%mod;
    }return sum;
}
int mi(int x){return qpow(2,x);}
int inv(int x){return qpow(mi(x),mod-2);}
struct node{
    int l,r,op;
    friend bool operator <(node x,node y){
        if(x.r==y.r)return x.l>y.l;
        return x.r<y.r;
    }
}a[maxm];
int L[maxm],R[maxm],b[maxm];
struct fenwick{
    int t[maxm];
    void add(int x,int y){
        for(;x<=N;x+=x&-x)t[x]=(t[x]+y)%mod;
    }
    int ask(int x){
        int sum=0;
        for(;x;x-=x&-x)sum=(sum+t[x])%mod;
        return sum;
    }
}T[3];
int f[maxm];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>k>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i].l>>a[i].r;
    for(int i=n+1;i<=n+m;i++)cin>>a[i].l>>a[i].r,a[i].op=1;
    sort(a+1,a+n+m+1);
    for(int i=1;i<=n+m;i++)b[++N]=a[i].l,b[++N]=a[i].r;
    sort(b+1,b+N+1);N=unique(b+1,b+N+1)-b-1;
    for(int i=1;i<=n+m;i++)
        L[i]=lower_bound(b+1,b+N+1,a[i].l)-b,
        R[i]=lower_bound(b+1,b+N+1,a[i].r)-b;
    int mx[2]={0,0};
    ans=1;
    for(int i=1;i<=n+m;i++){
        int o=a[i].op;
        if(L[i]<=mx[o])continue;
        // msk<<i<<" "<<a[i].l<<" "<<a[i].r<<"------\n";
        mx[o]=max(mx[o],L[i]);
        f[i]=(T[2].ask(L[i]-1)+1)*(mod-inv(a[i].r-a[i].l+1))%mod;
        f[i]=(f[i]+(T[o].ask(R[i])-T[o].ask(L[i]-1)+mod)%mod*
                    (mod-inv(a[i].r)))%mod;
        T[2].add(R[i],f[i]);
        T[o].add(R[i],f[i]*mi(a[i].r)%mod);
        ans=(ans+f[i])%mod;
    }
    cout<<ans*mi(k)%mod<<"\n";
    return 0;
}
```

---

## 作者：cwfxlh (赞：0)

# [CF930E](https://www.luogu.com.cn/problem/CF930E)     

考虑容斥。在前 $n$ 个区间中选 $a$ 个区间，在后 $m$ 个区间中选 $b$ 个区间，钦定这 $a+b$ 个区间都不符合要求。那么要求前半部分 $a$ 个区间的并与后半部分 $b$ 个区间的并不交，这样的贡献就是 $(-1)^{a+b}2^{k-|A|-|B|}$，$A$ 指前半部分 $a$ 个区间的并，$B$ 指后半部分 $b$ 个区间的并。这一部分是经典容斥套路。         

另外发现，两个相同类型的限制区间如果有包含关系，那么可以去掉大的那个，于是两类区间分别都只有相交关系了。离散化，记 $dp_{i,0/1}$ 表示当前考虑了前 $i$ 个元素，钦定非法的区间个数是奇 or 偶数，$2^{k-|A|-|B|}$ 的和，转移的时候考虑使用树状数组维护，单点修改区间求和，根据不同类型的转移，总共需要 6 个树状数组，两个维护不相交区间的转移，四个维护相交区间的转移，相交区间转移的时候需要乘上一个 2 的幂。复杂度 $O(n\log n)$。          

代码：         


```cpp
#include<bits/stdc++.h>
#define int long long
#define MOD 1000000007
using namespace std;
int k,n,m,k1,k2,k3,k4,k5,k6,k7,k8,k9,ans;
pair<int,int>seq1[500003];
pair<int,int>seq2[500003];
pair<int,int>stk[500003];
vector<int>lst[500003];
int tot;
bool comp(pair<int,int> X,pair<int,int> Y){
    if(X.first!=Y.first)return X.first<Y.first;
    return X.second>Y.second;
}
map<int,int>mp;
int dp[500003][2],stk2[500003],tot2;
int lowbit(int X){return (X&(-X));}
class BIT{
    public:
        int TreeAr[500003];
        void modify(int wz,int v){
            wz++;
            for(int i=wz;i<=500000;i+=lowbit(i))TreeAr[i]=(TreeAr[i]+v)%MOD;
            return;
        }
        int Query(int l,int r){
            l++;
            r++;
            int ret=0;
            for(int i=r;i>0;i-=lowbit(i))ret=(ret+TreeAr[i])%MOD;
            for(int i=l-1;i>0;i-=lowbit(i))ret=(ret-TreeAr[i])%MOD;
            return ret;
        }
        void cln(){
            for(int i=0;i<=500002;i++)TreeAr[i]=0;
            return;
        }
}T1[2],T2[2][2];
int fstp(int X,int Y){
    int ret=1,bse=X;
    while(Y){
        if(Y%2)ret=ret*bse%MOD;
        bse=bse*bse%MOD;
        Y/=2;
    }
    return ret;
}
signed main(){
    ios::sync_with_stdio(false);
    cin>>k>>n>>m;
    for(int i=1;i<=n;i++)cin>>seq1[i].first>>seq1[i].second;
    for(int i=1;i<=m;i++)cin>>seq2[i].first>>seq2[i].second;
    sort(seq1+1,seq1+n+1,comp);
    sort(seq2+1,seq2+m+1,comp);
    for(int i=n,j=-1;i;i--){
        if(j==-1||j>seq1[i].second){
            stk[++tot]=seq1[i];
            j=seq1[i].second;
        }
    }
    n=tot;
    for(int i=1;i<=n;i++)seq1[i]=stk[n-i+1];
    tot=0;
    for(int i=m,j=-1;i;i--){
        if(j==-1||j>seq2[i].second){
            stk[++tot]=seq2[i];
            j=seq2[i].second;
        }
    }
    m=tot;
    for(int i=1;i<=m;i++)seq2[i]=stk[m-i+1];
    for(int i=1;i<=n;i++){
        if(mp.find(seq1[i].first)==mp.end()){
            stk2[++tot2]=seq1[i].first;
            mp[seq1[i].first]=1;
        }
        if(mp.find(seq1[i].second)==mp.end()){
            stk2[++tot2]=seq1[i].second;
            mp[seq1[i].second]=1;
        }
    }
    for(int i=1;i<=m;i++){
        if(mp.find(seq2[i].first)==mp.end()){
            stk2[++tot2]=seq2[i].first;
            mp[seq2[i].first]=1;
        }
        if(mp.find(seq2[i].second)==mp.end()){
            stk2[++tot2]=seq2[i].second;
            mp[seq2[i].second]=1;
        }
    }
    sort(stk2+1,stk2+tot2+1);
    for(int i=1;i<=tot2;i++)mp[stk2[i]]=i;
    for(int i=1;i<=n;i++){
        seq1[i].first=mp[seq1[i].first];
        seq1[i].second=mp[seq1[i].second];
    }
    for(int i=1;i<=m;i++){
        seq2[i].first=mp[seq2[i].first];
        seq2[i].second=mp[seq2[i].second];
    }
    dp[0][0]=fstp(2,k);
    for(int i=1;i<=n;i++)lst[seq1[i].second].emplace_back(i);
    for(int i=1;i<=m;i++)lst[seq2[i].second].emplace_back(i+n);
    T1[0].modify(0,dp[0][0]);
    for(int i=1;i<=tot2;i++){
        for(auto j:lst[i]){
            k1=k2=k3=k4=0;
            if(j<=n){
                k1=(k1+T1[1].Query(0,seq1[j].first-1)*fstp((MOD+1)/2,stk2[seq1[j].second]-stk2[seq1[j].first]+1))%MOD;
                k2=(k2+T1[0].Query(0,seq1[j].first-1)*fstp((MOD+1)/2,stk2[seq1[j].second]-stk2[seq1[j].first]+1))%MOD;
                k1=(k1+T2[0][1].Query(seq1[j].first,seq1[j].second-1)*fstp((MOD+1)/2,stk2[seq1[j].second]))%MOD;
                k2=(k2+T2[0][0].Query(seq1[j].first,seq1[j].second-1)*fstp((MOD+1)/2,stk2[seq1[j].second]))%MOD;
                T2[0][0].modify(i,k1*fstp(2,stk2[seq1[j].second])%MOD);
                T2[0][1].modify(i,k2*fstp(2,stk2[seq1[j].second])%MOD);
            }
            else{
                k3=(k3+T1[1].Query(0,seq2[j-n].first-1)*fstp((MOD+1)/2,stk2[seq2[j-n].second]-stk2[seq2[j-n].first]+1))%MOD;
                k4=(k4+T1[0].Query(0,seq2[j-n].first-1)*fstp((MOD+1)/2,stk2[seq2[j-n].second]-stk2[seq2[j-n].first]+1))%MOD;
                k3=(k3+T2[1][1].Query(seq2[j-n].first,seq2[j-n].second-1)*fstp((MOD+1)/2,stk2[seq2[j-n].second]))%MOD;
                k4=(k4+T2[1][0].Query(seq2[j-n].first,seq2[j-n].second-1)*fstp((MOD+1)/2,stk2[seq2[j-n].second]))%MOD;
                T2[1][0].modify(i,k3*fstp(2,stk2[seq2[j-n].second])%MOD);
                T2[1][1].modify(i,k4*fstp(2,stk2[seq2[j-n].second])%MOD);
            }
            dp[i][0]=(dp[i][0]+k1+k3)%MOD;
            dp[i][1]=(dp[i][1]+k2+k4)%MOD;
            
        }
        T1[0].modify(i,dp[i][0]);
        T1[1].modify(i,dp[i][1]);
    }
    for(int i=0;i<=tot2;i++)ans=(ans+dp[i][0]-dp[i][1])%MOD;
    ans%=MOD;
    ans+=MOD;
    ans%=MOD;
    cout<<ans;
    return 0;
}
```

---

