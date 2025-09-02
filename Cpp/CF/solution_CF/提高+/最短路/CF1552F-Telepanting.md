# Telepanting

## 题目描述

### **【题目大意】**

有一只初始在位置 $0$ 的蚂蚁，它每秒钟会向右走 $1$ 一个单位长度。

在地图上有 $n$ 个虫洞，第 $i$ 个虫洞在位置 $x_{i}$，如果它是活动的，它就会把蚂蚁送回到位置 $y_{i}(y_{i}<x_{i})$。

初始时每个虫洞有一个参数 $s_{i}$，$s_{i}$ 是 $0$ 表示虫洞是初始静止的，而 $1$ 表示虫洞初始是活动的。

当蚂蚁踩到虫洞 $i$ 时：

- 如果这个虫洞是静止的，那么此虫洞会变成活动的，但是蚂蚁的位置不改变。
- 如果这个虫洞是活动，那么此虫洞将变成静止，且会把蚂蚁送回 $y_{i}$ 位置，而接下来蚂蚁将保持向右每秒 $1$ 个单位的速度前进（即下一秒它会到位置 $y_{i}+1$）。

现在我们想知道，这只蚂蚁需要多少时间才能到位置 $(x_{n}+1)$ 呢？**答案对 $998244353$ 取模**。

## 说明/提示

- $1 \leq n \leq 2 \times 10^{5}$。
- $\forall i \in [1,n], \quad 1 \leq y_{i}<x_{i} \leq 1 \times 10^{9},s_{i} \in \{0,1 \}$。

Translated by @HPXXZYY

## 样例 #1

### 输入

```
4
3 2 0
6 5 1
7 4 0
8 1 1```

### 输出

```
23```

## 样例 #2

### 输入

```
1
454971987 406874902 1```

### 输出

```
503069073```

## 样例 #3

### 输入

```
5
243385510 42245605 0
644426565 574769163 0
708622105 208990040 0
786625660 616437691 0
899754846 382774619 0```

### 输出

```
899754847```

## 样例 #4

### 输入

```
5
200000000 100000000 1
600000000 400000000 0
800000000 300000000 0
900000000 700000000 1
1000000000 500000000 0```

### 输出

```
3511295```

# 题解

## 作者：一叶知秋。 (赞：15)

考虑走到 $i$ 号传送门时，前面 $i-1$ 个状态，很明显， $s_x=1 \ \ (x \in [1,i-1])$，也就是前面传送门全开着，状态只有一种，所以我们可以设 $g_i$ 表示走到 $i$ 被传送回去到 $y_i$，还要走多久回到 $x_i$。

设 $j$ 号传送门为第一个大于等于 $y_i$ 的传送门，很明显 $k \in [j,i-1]$ 的传送门都会有 $g_k$ 的贡献，因为要走回来，所以这些传送门都会走到，且第一次走到时都会被传送。（因为已经走到 $i$ 号传送门，前面传送门都是开的）

所以可以列出转移：

$g_i=x_i-y_i+\sum\limits_{k=j}^{i-1}g_k$

随便前缀和维护一下即可，对于初始状态 $s$ 直接模拟做，具体看代码就懂了。

code :

```cpp
#include<cstdio>
#include<cctype>
#include<algorithm>

#define maxn 202202
#define mod 998244353

template<class T>

inline T read(){
    T r=0,f=0;
    char c;
    while(!isdigit(c=getchar()))f|=(c=='-');
    while(isdigit(c))r=(r<<1)+(r<<3)+(c^48),c=getchar();
    return f?-r:r;
}

bool s[maxn];

int n,x[maxn],y[maxn];

long long g[maxn],sum[maxn];

int main(){
    n=read<int>();
    long long ans=0;
    for(int i=1;i<=n;i++){
		x[i]=read<int>();
		y[i]=read<int>();
		s[i]=read<int>();
		int nxt=std::lower_bound(x+1,x+1+i,y[i])-x;
		g[i]=(x[i]-y[i]+sum[i-1]+mod-sum[nxt-1])%mod;
		ans+=s[i]?g[i]:0;//有就要往回走一次
		sum[i]=(sum[i-1]+g[i])%mod;
    }
    printf("%lld\n",(ans+x[n]+1)%mod);//记得还要正常走x[n]+1的距离
    return 0;
}
```

---

## 作者：MoyunAllgorithm (赞：4)

很多题解都把性质的证明、$dp$ 方程的推导一笔带过，因此我将提供一篇更为详细的题解。

### 题意

蚂蚁从 $0$ 往右走。有 $N(\le 2 \times 10^5)$ 个传送门，用 $(x_i,y_i,t_i)$ 表示，代表蚂蚁从 $x_i$ 点传送到 $y_i$ 点 $(y_i < x_i)$。若蚂蚁到达 $x_i$ 时，$t_i=1$，则它会传送，$t_i$ 变为 $0$；若 $t_i=0$，不会传送，$t_i$ 变为 $1$。问蚂蚁需要走多久才到 $x_N+1$。（注：传送门传送是不需要走路的）

### 分析

答案可以表示为：$X_N +1 +$ **由于往回传送耗费的距离**。

因此，不妨设 $dp_i$ 表示：当蚂蚁来到 $x_i$ 时 $t_i=1$，也就是它会被传送，那么它需要再走多久才能回到 $x_i$。

存在一个性质：蚂蚁之前的传送门都是开着的。

**证明** 在蚂蚁前面的传送门都被蚂蚁经过过。既然蚂蚁成功到达该传送门后面，则此时必然它由关闭变为开着。

基于该性质，我们发现：当蚂蚁从 $x_i$ 传送到 $y_i$ 时，对于所有 $j$ 满足 $x_j \in (y_i,x_i)$，$t_j=1$。也就是说，这时蚂蚁想要回到 $x_i$，需要重新把这些传送门全部走一遍。那就有方程

$$dp_i=x_i-y_i+
\sum_{j=1}^{N} dp_j,x_j \in (y_i,x_i)$$

那最开始我们说的 **由于往回传送耗费的距离** 就是所有一开始就开启的传送门的 $dp$ 值之和。如果你真正理解了 $dp$ 数组的求法，你就会明白为什么蚂蚁有可能会走初始关闭的传送门但我们没有把它们的 $dp$ 值加上。

显而易见的优化 $O(N^2)$ 算法的方法：将虫洞按 $x$ 坐标排序。这样，就可以 $O(1)$ 计算 $\sum_{j=1}^{N} dp_j,x_j \in (y_i,x_i)$ 了，这属于**前缀和优化**。

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN=2e5+5,MOD=998244353;
int x[MAXN],y[MAXN],t[MAXN];
LL dp[MAXN],sum[MAXN];
int N;
int main()
{
    scanf("%d",&N);
    for(int i=1;i<=N;i++) scanf("%d %d %d",&x[i],&y[i],&t[i]);
    LL ans=x[N]+1;
    for(int i=1;i<=N;i++)
    {
        int pos=lower_bound(x+1,x+N+1,y[i])-x;
        dp[i]=((sum[i-1]-sum[pos-1]+x[i]-y[i])%MOD+MOD)%MOD;
        sum[i]=(sum[i-1]+dp[i])%MOD;
        ans+=t[i]*dp[i];
    }
    printf("%lld\n",ans%MOD);
    return 0;
}
```


---

## 作者：shinkuu (赞：2)

首先有个关键的性质：如果你走到了第 $i$ 个虫洞后面，那此时第 $1$ 到第 $i$ 个虫洞都应该是活动状态。这个可以自己证明一下。

然后可以利用这个性质列出 dp 状态：$dp_i$ 表示当第 $1$ 到 $i$ 个虫洞都为活动时，从第一次传送到 $y_i$ 到停在 $x_i$ 有多远。

然后可以发现，若从虫洞 $a$ 到 $b$ 要经过若干个虫洞，这些虫洞中开启的集合为 $S$，则总路程为 $x_b-x_i+\sum_{i\in S} dp_i$。

所以可以列出转移方程：设 $j$ 为 $y_i$ 之后的第一个虫洞，则 $dp_i=x_j-y_i+\sum_{j\le k<i} dp_k+x_i-x_j$。分别用二分和前缀和优化即可。

最后答案即为 $\sum_{s_i=1}dp_i$。

code：

```cpp
int n,m,x[N],y[N],op[N],dp[N],s[N];
void solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d%d",&x[i],&y[i],&op[i]);
	int ans=0;
	for(int i=1;i<=n;i++){
		int pos=lower_bound(x+1,x+n+1,y[i])-x;
		dp[i]=((x[pos]-y[i]+s[i-1]-s[pos-1]+x[i]-x[pos])%mod+mod)%mod;
		s[i]=(s[i-1]+dp[i])%mod;
		ans=(ans+x[i]-x[i-1])%mod;
		if(op[i])
			ans=(ans+dp[i])%mod;
	}
	printf("%d\n",(ans+1)%mod);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		solve();
}
```

---

## 作者：water_tomato (赞：2)

本文同步发表于个人博客：[Link](https://www.watertomato.com/cf1552f-telepanting-%e9%a2%98%e8%a7%a3/)。

## 题意

[题目链接](https://www.luogu.com.cn/problem/CF1552F)。

数轴上有若干传送门，初始是关闭或开启。对于关闭的传送门，经过后就会开启；对于开启的传送门，到达后会被传送到一个位置，然后会关闭。求从 $0$ 点走到 $x_n+1$，即最后一个传送门右边一格的所需时间。

## 解析

首先离散化。然后记 $f_i$ 为被在 $i$ 点的传送门传走再走回到 $i$ 点的时间。若该位置没有传送门，则记 $f_i=0$。容易发现已经过的传送门肯定是开启的，因此有 $f_i=x_i-y_i+\sum f_j,x_j\in[y_i,x_i-1] $，即路程长度加上被之间所有的传送门传一遍所需时间，发现这显然可以用前缀和维护。

求出所有 $f_i$ 之后，答案即为所有初始打开的传送门的 $f_i$ 之和加上路径长度。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=4e5+5;
const int mod=998244353;
struct node{
	int x,y,s;
}a[N];
int b[N],sum[N],f[N],ans,n;
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld%lld",&b[i*2-1],&b[i*2],&a[i].s);
		a[i].x=b[i*2-1];a[i].y=b[i*2];
	}
	sort(b+1,b+1+2*n);
	for(int i=1;i<=n;i++){
		a[i].x=lower_bound(b+1,b+1+2*n,a[i].x)-b;
		a[i].y=lower_bound(b+1,b+1+2*n,a[i].y)-b;
	}//离散化
	int now=1;
	for(int i=1;i<=2*n;i++){
		while(i==a[now].x&&now<=n){
			f[i]=(b[a[now].x]-b[a[now].y]+mod)%mod;
			f[i]=(f[i]+sum[a[now].x-1]-sum[a[now].y-1]+mod)%mod;
			if(a[now].s==1) ans=(ans+f[i])%mod;
			now++;
		}//求 fi 并统计答案
		sum[i]=(sum[i-1]+f[i])%mod;//前缀和维护
	}
	ans=(ans+b[a[n].x]+1)%mod;//加上路径总长度
	printf("%lld\n",ans);
	return 0;
}
```



---

## 作者：Tjaweiof (赞：1)

# CF1552F 题解
[题目传送门](https://www.luogu.com.cn/problem/CF1552F)

容易发现当蚂蚁走到一个位置的时候，之前的所有虫洞都是静止的。设 $f_i$ 为当这个虫洞是活动的，那么再次回到这个虫洞并把它再变成活动的需要多久。设 $j$ 为使得 $x_j\ge y_i$ 的最小的 $j$。则 $f_i=x_i-y_i+\sum_{k=j}^{i-1}$，加个前缀和优化就行了。

答案是 $\sum_{i=1}^n(s_i\times f_i)+x_n+1$。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FILE(x) freopen(x".in", "r", stdin);freopen(x".out", "w", stdout);
const int mod = 998244353;
int n;
long long x[200001], y[200001], f[200001], sum[200001], ans;
bool s[200001];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> x[i] >> y[i] >> s[i];
	}
	for (int i = 1; i <= n; i++){
		int tmp = lower_bound(x + 1, x + n + 1, y[i]) - x;
		f[i] = (x[i] - y[i] + sum[i - 1] - sum[tmp - 1] + mod) % mod;
		sum[i] = sum[i - 1] + f[i];
		sum[i] %= mod;
		if (s[i]){
			ans += f[i];
			ans %= mod;
		}
	}
	ans += x[n] + 1;
	ans %= mod;
	cout << ans;
	return 0;
}

```

---

## 作者：紊莫 (赞：1)

首先有一些结论，**请先忽略每个传送门的初始状态**。

当我们走过某个传送门时，之前的所有传送门都已经打开了。

证明：假如某个传送门是关闭的，那么一定会在关闭它前被传送到更前面，不会向后走。

从传送门 $i$ 到能走过 $j$ 的花费为 $x_j-x_i+\sum_{k=i+1}^{j}f_k$，其中 $f_k$ 表示在 $k$ 个传送门处被传送后想要回到 $k$ 的最小花费。

证明比较显然，一段一段推下去，求和即可。

然后考虑计算每个 $f_i$，$f_i = x_i-y_i+\sum f_k$，于是前缀和优化 DP 就可以了。

然后再处理那个初始的限制，显然在传送门全开的时候，答案就是 $x_n+1+\sum_{i=1}^{n}f_i$，那么当一个传送门初始时关闭的，第一次走过的时候就不用被传送了，那么不计入答案就行了，而走过之后，根据上面的性质，前面所有的传送门都是打开的。

```cpp
#include <bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 998244353;
typedef long long ll;
int x[N], y[N], s[N];
ll sum[N], f[N];

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n;
  cin >> n;

  for (int i = 1; i <= n; i++) {
    cin >> x[i] >> y[i] >> s[i];
  }
  ll ans = x[n] + 1;
  for (int i = 1; i <= n; i++) {
    int p = lower_bound(x + 1, x + n + 1, y[i]) - x;
    f[i] = (sum[i - 1] - sum[p - 1] + x[i] - y[i]) % mod;
    f[i] = (f[i] + mod) % mod;
    sum[i] = (sum[i - 1] + f[i]) % mod;
    ans = (ans + s[i] * f[i]) % mod;
  }
  cout << ans << '\n';
  return 0;
}
```


---

## 作者：Vidoliga (赞：1)

给个线性复杂度，根号值域空间复杂度做法。

首先转移应当是很好想的，一个点回去后在其之间的点都必然处于开启状态。

不妨按照 $x$ 递增排序。

设 $f_i$ 表示到 第 $i$ 个虫洞的回去再回来的步数。

那么假设 $p=\text{argmin}_{j}\{x_j \in [y_i,x_i] \}$

有转移 $f_i=\sum\limits_{j=p}^{i-1}f_j +x_i-y_i$。

大概有个 $O(n \log n)$ 的做法了，通过前缀和维护即可。

可以通过基数排序做到 $O(n)$ 排序，为了方便处理 $\text{argmin}_{j}\{x_j \in [y_i,x_i] \}$，不妨将 $y$ 也放入统一排序。

时间复杂度就是 $O(n)$ 的了，粗略实现都可以跑得飞快。

code:


```cpp
const int N=4e5+20,M=1e6+20,mod=998244353,V=1e5;
int n,tot,f[N],F[N],g[N],p[N],to[N],sz[N];bool fl[N];
struct Node{int x,x1,x2,id,fl;}s[N];
void Sort(){
	for(int i=0;i<=V;i++) sz[i]=0;
	for(int i=1;i<=tot;i++) sz[s[i].x2+1]++;
	for(int i=1;i<=V;i++) sz[i]+=sz[i-1];
	for(int i=1;i<=tot;i++) g[++sz[s[i].x2]]=i;
	for(int i=0;i<=V;i++) sz[i]=0;
	for(int i=1;i<=tot;i++) sz[s[i].x1+1]++;
	for(int i=1;i<=V;i++) sz[i]+=sz[i-1];
	for(int i=1;i<=tot;i++) p[++sz[s[g[i]].x1]]=g[i];
	for(int i=1;i<=tot;i++) if(!s[p[i]].fl) to[s[p[i]].id]=p[i];
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1,x,y;i<=n;i++){
		cin>>x>>y>>fl[i];
		s[++tot]=(Node){x,x/V,x%V,i,1};
		s[++tot]=(Node){y,y/V,y%V,i,0};
	}
	Sort();
	for(int i=1;i<=tot;i++){
		if(s[p[i]].fl){
			int u=to[s[p[i]].id];
			f[p[i]]=(F[p[i-1]]-F[u]+s[p[i]].x-s[u].x)%mod;
			f[p[i]]=(f[p[i]]+mod)%mod;
		}
		F[p[i]]=(F[p[i-1]]+f[p[i]])%mod;
	}
	int ans=0;
	for(int i=1;i<=tot;i++) if(fl[s[p[i]].id]&&s[p[i]].fl) ans=(ans+f[p[i]])%mod;
	cout<<(ans+s[p[tot]].x+1)%mod<<'\n';
	return 0;
}
```

---

## 作者：HPXXZYY (赞：1)

$\color{blue}{\texttt{[Solution]}}$

首先，如果这只蚂蚁到达了虫洞 $i$，那么代表它经过虫洞 $1 \cdots (i-1)$ 时，这些虫洞一定是静止的，同时，因为它经过了这些虫洞，所以**现在** 这些虫洞一定是活动的。

我们记 $f_{i}$ 表示走到虫洞 $i$ 并且被送回位置 $y_{i}$ 后还需多少时间回到 $x_{i}$。显然对于所以 $x_{j}>y_{i}$ 的虫洞 $j(j<i)$ 都会有 $f_{j}$ 的贡献（因为它们一定是活动的），加上从 $y_{i}$ 走到 $x_{i}$ 的时间，我们有：

$$f_{i}=x_{i}-y_{i}+\sum\limits_{x_{j}>y_{i},j<i}f_{j}$$

很显然，因为题目说了 $x_{1 \cdots n}$ 是严格递增的，所以合法的 $j$ 是集中在一个区间内的。所以我们可以用前缀和快速地维护 $\sum\limits_{x_{j}>y_{i},j<i} f_{j}$ 这一串的值。

最后的答案就是：

$$\sum\limits_{i=1}^{n} f_{i}[s_{i}=1]+x_{n}+1$$

前一半表示因为虫洞耽搁的时间，后一半（$x_{n}+1$）表示没有虫洞直接走到 $(x_{n}+1)$ 也必须要的时间。

总的时间复杂度：$\mathcal{O}(n)$。总的空间复杂度：$\mathcal{O}(n)$。

$\color{blue}{\texttt{[Code]}}$

```cpp
const int N=2e5+100;
const int mod=998244353;
long long f[N],pre[N],ans;
bool s[N];int x[N],y[N],n;
int main(){
	n=read();ans=0ll;
	for(int i=1;i<=n;i++){
		x[i]=read();y[i]=read();s[i]=read();
		int j=lower_bound(x+1,x+i+1,y[i])-x;
		f[i]=(x[i]-y[i]+pre[i-1]+mod-pre[j-1])%mod;
		ans+=s[i]?f[i]:0;pre[i]=pre[i-1]+f[i];
	}
	printf("%lld",(ans+x[n]+1)%mod);
	return 0;
}
```

---

## 作者：SSerxhs (赞：1)

首先离散化。设 $f_i$ 表示路径 $[i-1,i]$ 的通过次数，$c_i$ 表示以点 $i$ 为出入口的通道的初始状态。如果 $i-1$ 是入口，那么 $i-1$ 的活跃情况变化一定是 `010101` 或 `1010101`，其中状态个数是 $f_{i-1}+1$，每一个 `0` 对应一次走过 $[i-1,i]$。那么容易发现 $f_i=\dfrac{f_{i-1}+1-c_{i-1}}2$。如果 $i-1$ 是出口，设其对应的入口为 $x$，那么将会传送 $[\dfrac{f_x+c_i}2]$ 次，因此 $f_i=f_{i-1}+[\dfrac{f_x+c_i}2]$。

注意到 $f_i$ 既依赖于后面又依赖于前面，不好做，考虑计算 $f_{i-1}$，那么倒过来算就可以了。

```cpp
int main()
{
	read(n);
	for (i=1;i<=n;i++) read(a[i],b[i],c[i]),d[++m]=a[i],d[++m]=b[i];
	sort(d+1,d+m+1);m=unique(d+1,d+m+1)-d-1;assert(m==n*2);
	for (i=1;i<=n;i++) a[i]=lower_bound(d+1,d+m+1,a[i])-d,b[i]=lower_bound(d+1,d+m+1,b[i])-d;
	for (i=1;i<=n;i++) bel[b[i]]=bel[a[i]]=i;d[m+1]=d[m]+1;
	f[m+1]=1;
	for (i=m;i;i--) if (a[bel[i]]==i) f[i]=(f[i+1]*2+c[bel[i]])%p,dec(f[i],1); else
	{
		x=bel[i];
		f[i]=f[i+1];
		dec(f[i],f[a[x]+1]);dec(f[i],c[x]);inc(f[i],1);
	}
	f[0]=1;
	for (i=1;i<=m+1;i++) ans=(ans+(ll)(d[i]-d[i-1])*f[i])%p;
	enter(ans);
}

```

---

## 作者：Cure_Wing (赞：0)

[CF1552F Telepanting](https://www.luogu.com.cn/problem/solution/CF1552F)

### 思路

我们先思考这么一个问题，就是蚂蚁不会陷入死循环。因为当虫洞是关闭的时候显然不会影响，而虫洞是开放的时候虽然会传送回去，但是这之后它又会关闭。也就是说等到蚂蚁下一次来到这个位置时，它又可以走过去。于是蚂蚁总能到达终点。

仔细手玩一下可以发现，当蚂蚁走过第 $i$ 个虫洞后，第 $1\sim i$ 个虫洞一定处于开放状态。因为如果第 $i$ 个虫洞是关闭的，那么这个虫洞在蚂蚁到达时是开放的，所以蚂蚁一定会被传送回去，而不会向前走。当蚂蚁走到关闭的虫洞时，不会对它的行走产生影响。而走到开放的虫洞时，会把它传送回去。如果回去之后再走回来不会遇到虫洞，那么多出的距离就是出口和入口的距离。但是有没有可能传送多次呢？就像这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/ilep61ku.png)

（绿线是虫洞，黑色数轴是蚂蚁走的路，假设传送门一开始全部处于开放状态。）

我们发现，当蚂蚁走到第 $5$ 个位置的时候，会被传送到 $2$，再走一步到 $3$，又会被传送到 $1$。那么多走的路就是图中紫色线段。我们发现传送导致的多余的路程之和就是所经过的虫洞的出入口距离之和。

但是这个思路好像处理虫洞嵌套的情况有些麻烦：

![](https://cdn.luogu.com.cn/upload/image_hosting/ylo2hz0q.png)

我们这样想：当蚂蚁经过一个开放的虫洞之后，它也一定会经过虫洞出入口之间的所有虫洞，并且把过这些虫洞所耗费的距离全部再走一遍，所以走过一个开放的虫洞所耗费的距离就是该虫洞的出入口距离加上走过入口在该虫洞出入口之间的虫洞的距离的总和。我们设 $f_i$ 表示走过开放的虫洞 $i$ 所耗费的距离，那么 $f_i=x_i-y_i+\sum f_k[y_i\le x_k\le x_i]$。

显然，由于 $x$ 已经排好了序，满足条件的 $x_k$ 一定是一个区间。$k$ 的右端点显然是 $i-1$，而左端点显然可以二分查找。直接做时间复杂度是 $O(n^2)$ 的。考虑转移是一个区间和的形式，于是我们对 $f$ 数组作前缀和优化，就可以把时间复杂度降为 $O(n\log n)$。

统计答案时，显然只有一开始是开放的虫洞才会产生如上面所说的额外路径。注意到我们计算的是多余路径，最后输出时还要加上必须走的 $x_n+1$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using std::cin;using std::cout;
constexpr int N=200005,p=998244353;
int n,x[N],y[N],s[N],ans,sum,l[N],tot[N],all[N];//all是上文f数组，tot是前缀和数组。
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>x[i]>>y[i]>>s[i];
        int k=std::lower_bound(x+1,x+i,y[i])-x;
        all[i]=(x[i]-y[i]+(tot[i-1]-tot[k-1]+p)%p)%p;
        tot[i]=(tot[i-1]+all[i])%p;
        if(s[i]) ans=(ans+all[i])%p;
    }
    cout<<(ans+x[n]+1)%p;
    return 0;
}
```

---

## 作者：FjswYuzu (赞：0)

有一个很显然但是我一下没看出来的结论是，如果蚂蚁在第 $i-1$ 个传送门和第 $i$ 个传送门之间，那么编号小于等于 $i-1$ 的传送门一定处于打开状态。

那么考虑每个传送门的贡献。对于第 $i$ 个传送门，将其设为 $f_i$，先找到这个传送门传送之后的位置后面的最近的传送门编号，记为 $p$，显然传送门 $i$ 的贡献会增加 $\sum_{j=p}^{i-1} f_j$，除此之外还要加上 $x_i-y_i$ 表示 $y_i$ 到 $x_i$ 的时间（容易发现这块在前面是没计算的），那么得到：

$$
f_i = x_i-y_i+\sum_{j=p}^{i-1} f_j
$$

对于 $\sum_{j=p}^{i-1} f_j$，找 $p$ 可以二分查找，计算可以用前缀和。

如果对于一个传送门 $i$，若其初始状态为开启，那么将答案加上 $f_i$。

最后一样的没有计算初始位置到结束位置的距离，注意加上 $x_n+1$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL MOD=998244353;
LL sum[200005],x[200005],n;
int main(){
	scanf("%lld",&n);
	LL ans=0;
	for(LL i=1;i<=n;++i)
	{
		scanf("%lld",&x[i]);
		LL tel,s;
		scanf("%lld %lld",&tel,&s);
		LL pos=lower_bound(x+1,x+i+1,tel)-x;
		LL tmp=x[i]-tel+MOD+sum[i-1]-sum[pos-1]+MOD;
		tmp%=MOD;
		if(s)	(ans+=tmp)%=MOD;
		sum[i]=(sum[i-1]+tmp)%MOD;
	}
	printf("%lld",(ans+x[n]%MOD+1)%MOD);
	return 0;
}
```

---

