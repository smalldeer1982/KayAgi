# k-Tree

## 题目描述

Quite recently a creative student Lesha had a lecture on trees. After the lecture Lesha was inspired and came up with the tree of his own which he called a $ k $ -tree.

A $ k $ -tree is an infinite rooted tree where:

- each vertex has exactly $ k $ children;
- each edge has some weight;
- if we look at the edges that goes from some vertex to its children (exactly $ k $ edges), then their weights will equal $ 1,2,3,...,k $ .

The picture below shows a part of a 3-tree.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF431C/83eea7df0a509cbc1e6d27ff0b5f74fa2e2e451c.png)

 As soon as Dima, a good friend of Lesha, found out about the tree, he immediately wondered: "How many paths of total weight $ n $ (the sum of all weights of the edges in the path) are there, starting from the root of a $ k $ -tree and also containing at least one edge of weight at least $ d $ ?".Help Dima find an answer to his question. As the number of ways can be rather large, print it modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 样例 #1

### 输入

```
3 3 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 3 3
```

### 输出

```
1
```

## 样例 #3

### 输入

```
4 3 2
```

### 输出

```
6
```

## 样例 #4

### 输入

```
4 5 2
```

### 输出

```
7
```

# 题解

## 作者：Z_M__ (赞：15)

- 状态设计：
设 $f[i][0/1]$ 为总和为 $i$ （ $0$ 为不符合要求的路径， $1$ 反之）, 所以最后答案就为 $f[n][1]$ 。

- 转移：
$f[i][0/1]$ 显然可以从 $f[i-j][0/1],j\in [1,k]$ 转移。

1. $f[i][0]+=f[i-j][0],j<d$ , 当总和为 $i$ 时要不符合，那么只能从之前不符合的转移过来，不然就为符合的路径了，还有 $j$ 要小于 $d$ 不然转移的这条路径符合了要求。

2. $f[i][1]+=f[i-j][1]$ , 当总和为 $i$ 时要符合，那么只要从之前符合的转移过来就行了。

3. $f[i][1]+=f[i-j][0],j\ge d$ , 当 $j\ge d$ 时，转移的路径大于 $d$，所以之前不符合的经过这条路径也成了符合的，之前符合的在（2）中已经加过了。

- 初始化：
因为 $d$ 大于 $1$ ，所以当总和为 $0$ 时肯定没有一条路径是大于 $d$的，所以 $f[0][1]=0,f[0][0]=1$ 。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e2 + 10;
const int mod = 1e9 + 7;
int n, k, d;
int f[MAXN][2];
int main ()
{
	cin >> n >> k >> d;
	f[0][0] = 1;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= min (i, k); j++)
		{
			if (j < d)
				f[i][0] = (f[i][0] + f[i - j][0]) % mod;
			f[i][1] = (f[i][1] + f[i - j][1]) % mod;
			if (j >= d)
				f[i][1] = (f[i][1] + f[i - j][0]) % mod;
		}
	}
	cout << f[n][1] << endl;
	return 0;
}

```

---

## 作者：0xFF (赞：6)

#### 题目大意


------------
给定一个 $k$ 叉树，每条边顺次标定边权为 $1$ ~ $k$。问一共有几条从根节点出发的路满足这条边的边权之和为 $n$ 且其中至少有一条边的边权大于等于 $d$。

#### 思路分析


------------
标准的计数类动态规划题目，首先设计状态：

$f[i][0/1]$ 表示一条从根节点出发权值之和为 $i$ 的路上是否有一条权值大于等于 $d$ 的边。

接下来是状态转移

很容易可以想到如果现在正在处理的这条路上没有权值大于等于 $d$ 的边，那么现在要处理的这条边如果边权大于等于 $d$ 就会使得原先状态转移为 $f[i][1]$，反之则仍为 $f[i][0]$。

故我们可以得到如下方程

如果 $j < d $ ：

- $f[i][0] = f[i][0] + f[i-j][0]$

- $f[i][1] = f[i][1] + f[i-j][1]$

如果 $j > d $ ：

- $f[i][1] \gets f[i][1] + f[i-j][1] + f[i-j][0]$

但是，这道题目还有几个小坑：

- 如果 $i < j$ 那么我们的状态岂不是由转移负数组转移过来的。所以 $j$ 的边界为 $[1,\min(i,k)]$

- 一定不要忘记取模和开 ```long long```。

- 边界条件一定要设置好，否则会全输出 $0$。考虑 $f[0][0]$ 时的情况，明显 $f[0][0] = 0$。

#### 代码实现


------------

```cpp
#include<iostream>
#define int long long
using namespace std;
const int mod = 1e9 + 7;
const int N = 110;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
    return x*f;
}
int f[N][2];
signed main(){
	int n = read() , k = read() , d = read();
	f[0][0] = 1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=min(i,k);j++){
			if(j < d) f[i][0] += f[i-j][0],f[i][1] += f[i-j][1];
			else f[i][1] += f[i-j][1] + f[i-j][0];
			f[i][1] %= mod , f[i][0] %= mod;
		}
	}
	printf("%lld\n",f[n][1]);
    return 0;
}
```


---

## 作者：JWRuixi (赞：3)

CF 原始难度 $1600$，非常适合像我一样的小菜鸡练手。

- 题意

k-tree 是一颗无根树，它是一颗 $k$ 叉树，每条边的全值为 $1$ 到 $k$。求满足路径上权值和为 $n$，有至少一条边权值大于等于 $d$ 的路径数量。

- 分析

首先我们发现这是一个计数问题，而且这个路径张什么样子无从知晓，连长度都不知道，那这就启发我们搞 dp。

我们可以考虑设一个跟权值和有关的 dp，但是有需要满足至少有一条边权值大于等于 $d$ 的限制，所有考虑再加上一维表示当前是否满足限制，即：设 $f_{i,0/1}$ 表示权值和为 $i$ 满足或不满足限制的方案数。

显然满足只能往满足转移，而不满足可以向两种状态转移，所以可以想到转移：

$$f_{i,0} = \sum_{j=1}^{d-1}f_{i-j,0}$$
$$f_{i,1} = \sum_{j=1}^{k}f_{i-j,1}+\sum_{j=d}^{k}f_{i-j,0}$$

发现我的天哪，$n$，$k$，$d$ 的范围竟然如此之小，那不是随便 AC。

总时间复杂度 $O(nk)$。

- code

```cpp
#include <bits/stdc++.h>
using namespace std;

namespace IO{
	char ibuf[(1 << 20) + 1], *iS, *iT;
	#if ONLINE_JUDGE
	#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
 	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read () {
		reg char ch = gh();
		reg long long x = 0;
		reg char t = 0;
		while (ch < '0' || ch > '9')   t |= ch == '-', ch = gh();
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
		return t ? -x : x;
	}
	inline void write(long long x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

using IO::read;
using IO::write;

const int maxn = 105, mod = 1e9 + 7;
int n, k, d, f[maxn][2];

int main () {
	n = read(), k = read(), d = read();
	f[0][0] = 1;
	for (int s = 1; s <= n; s++) {
		for (int i = 1; i < d; i++) {
			if (i > s) break;
			f[s][0] = 1ll * (f[s][0] + f[s - i][0]) % mod;
		} 
		for (int i = 1; i <= min(k, s); i++) {
			f[s][1] = 1ll * (f[s][1] + f[s - i][1]) % mod;
		}
		for (int i = d; i <= min(k, s); i++) {
			f[s][1] = 1ll * (f[s][1] + f[s - i][0]) % mod;
		}
	}
	write(f[n][1]);
}
```

---

## 作者：览遍千秋 (赞：3)

## 问题描述

[CF413C](https://codeforces.com/problemset/problem/431/C)

[LG-CF413C](https://www.luogu.com.cn/problem/CF431C)

---

## 题解

求有多少权值为 $n$ ，路径中有边权不小于 $d$ 的 → 所有权值为 $n$ 的路径总数-所有边权均小于 $d$ 。

设 $f(i)$ 代表权值为 $i$ 的路径总数 ， $f(x)=\sum\limits_{i=x-k}^{x-1}{f(i)}$ 。

设 $g(i)$ 代表权值为 $i$ ，且路径中边权均小于 $d$ ， $g(x)=\sum\limits_{i=x-d+1}^{x-1}{g(i)}$ 。

答案为 $f(n)-g(n)$ 。

---

## $\mathrm{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long

template <typename Tp>
void read(Tp &x){
	x=0;char ch=1;int fh=1;
	while(ch!='-'&&(ch>'9'||ch<'0')) ch=getchar();
	if(ch=='-') fh=-1,ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	x*=fh;
}

const int maxn=107;
const int mod=1000000007;

int f[maxn],g[maxn];
int n,d,k;

void Init(void){
	read(n);read(k);read(d);
}

void Work(void){
	f[0]=g[0]=1ll;
	for(int i=1;i<=n;i++){
		int st=max(0ll,i-k);
		for(int j=st;j<i;j++) f[i]=(f[i]+f[j])%mod;
		st=max(0ll,i-d+1);
		for(int j=st;j<i;j++) g[i]=(g[i]+g[j])%mod;
	}
	printf("%lld\n",((f[n]-g[n])%mod+mod)%mod);
}

signed main(){
	Init();
	Work();
	return 0;
}
```

---

## 作者：Na2PtCl6 (赞：2)

ideas froms @expect2004

---
## 关键信息

- 无根树

- 满 $k$ 叉树

- 边权和为 $n$且经过的边权中至少一条 $\ge d$

- 取模（暗示要开 `long long`）

## 分析题目
一看题肯定知道是个dp啦，所以考虑如何将状态转移。

这个题从整棵树树的角度好像有点难想，我们可以从边权入手。

这个 "k-tree" 的边权 $\le k$，所以上一步到这一步的边权 $x$ 可能是 $1\le x \le k$。可设 $f(n)$ 为边权和为 $n$ 的路径条数，则 

$$f(n)=\sum_{i=n-k}^{n-1}f(i)$$

还要满足“经过的边权中至少一条 $\ge d$ ”的条件，所以可以转移边权小于 $d$ 的边，最后用 $f(n)$ 减去它。可设 $g(n)$ 为边权和为 $n$ 的路径中边权全部 $<d$ 的条数，则 
$$g(n)=\sum_{i=n-d+1}^{n-1}g(i)$$

综上，最后结果就是 $f(n)-g(n)$

然而这还没完，这是一个可以优化的 dp。

因为式子中有区间和，所以我们可以用一个树状数组实现单点加，求区间和，最终时间复杂度 $O(nlogn)$。但据个人的提交，也许因为 $n$ 不够大，求和的区间不够大，树状数组跑不过暴力区间和。。。

## 代码实现
暴力（竟是最优解！）
```
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=104,MOD=1000000007;
int n,k,d;
LL f[maxn],g[maxn];

inline const int _max(const int &a,const int &b){
	return a>b?a:b;
}

signed main(){
	scanf("%d %d %d",&n,&k,&d);
	f[0]=g[0]=1;
	for(int i=1;i<=n;i++){
		//边权<k 
		for(int j=_max(0,i-k);j<i;j++)
			f[i]=(f[i]+f[j])%MOD;
		//边权<d 
		for(int j=_max(0,i-d+1);j<i;j++)
			g[i]=(g[i]+g[j])%MOD;
	}
	printf("%d",(f[n]-g[n]+MOD)%MOD); 
	return 0;
}
```
树状数组
```
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=104,MOD=1000000007;
int n,k,d;
LL f[maxn],g[maxn];

inline const int _max(const int &a,const int &b){
	return a>b?a:b;
}

inline void add(LL *tree,int p,int v){
	++p;
	while(p<=n+1){
		tree[p]=(tree[p]+v)%MOD;
		p+=p&-p;
	}
} 

inline LL sum(LL *tree,int p){
	++p;
	LL ret=0;
	while(p){
		ret=(ret+tree[p])%MOD;
		p-=p&-p;
	}
	return ret;
}

signed main(){
	scanf("%d %d %d",&n,&k,&d);
	add(f,0,1);add(g,0,1);
	for(int i=1;i<=n;i++){
		add(f,i,sum(f,i-1)-sum(f,_max(0,i-k)-1));
		add(g,i,sum(g,i-1)-sum(g,_max(0,i-d+1)-1));
	}
	printf("%d",((sum(f,n)-sum(f,n-1))-(sum(g,n)-sum(g,n-1))+MOD)%MOD); 
	return 0;
}
```

---

## 作者：_Revenge_ (赞：1)

### 题目简化和分析：
k叉树，乍一看好像是树论，但我们通过分析条件，发现它每个阶段要做的事情一样，皆为：$1\sim k$ 中选数字，这就很明显是DP。   

$\mathit{f}_{i,0}$ 表示和为 $ i $，但不满足至少一边 $\ge d$。

$\mathit{f}_{i,1}$ 表示和为 $ i $，并且满足至少一边 $\ge d$。

$$\mathit{f}_{i,1}=\mathit{f}_{i,1}+\mathit{f}_{i-j,1}(j\le k)$$
$$\mathit{f}_{i,0}=\mathit{f}_{i,0}+\mathit{f}_{i-j,0}(j < d)$$
$$\mathit{f}_{i,1}=\mathit{f}_{i,1}+\mathit{f}_{i-j,0}(j\ge d)$$  

- 方程一：因为已经满足，所以当 $j\le k$ 都满足。
- 方程二：当不满足，并且 $j < d$，那么依旧不满足。
- 方程三：当不满足，但是 $j\ge d$,那么即可变为满足。   

### Solution:

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef double db;

const int N=1e2+50;
const int M=1e5+50;
const int Mod=1e9+7;

inline ll read(){
    ll x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}

ll n,k,d;
ll f[N][2];
int main()
{
	n=read(),k=read(),d=read();
	f[0][0]=1;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=min((ll)i,k);++j){
			f[i][1]+=f[i-j][1],f[i][1]%=Mod;
			if(j<d)f[i][0]+=f[i-j][0],f[i][0]%=Mod;
			if(j>=d) f[i][1]+=f[i-j][0],f[i][1]%=Mod;
		}
	}
	printf("%lld\n",f[n][1]%Mod);
	return 0;
}

```

---

## 作者：李子 (赞：1)

显然，因为限制条件并非选择的路径数目，而是权值和，故状态的第一维表示总和。  

再考虑其他限制，每个节点的子节点数对于状态的表示并无影响，故第二维表示路径上最大的权值。

综上，$f[i][j]$ 表示当前权值总和为 $i$，最大权值为 $j$ 时的方案数。初始化  $f[0][0]=1$ ，对于任意的f[i][j],枚举下一条边的权值 $l$ ，$f[i+l][max(j,l)]=(f[i][j]+f[i+l][max(j,l)])\%mod$ .

最后输出 $\sum\limits_{i=d}^kf[n][i]$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;
int n,d,k,ans,f[107][107];
int main()
{
	scanf("%d%d%d",&n,&k,&d);
	f[0][0]=1;
	for(register int i=0;i<=n;++i)
		for(register int l=1;l<=k;++l)
			for(register int j=0;j<=k;++j)
				f[i+l][max(j,l)]=(f[i][j]+f[i+l][max(j,l)])%mod;
	for(register int i=d;i<=k;++i)	
		ans=(ans+f[n][i])%mod;
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：Roviky (赞：1)

sum[i]用于记录路程和为i的路径有多少条

dp[i]用于记录当路程和为i时，最大路段大于等于d（满足题目要求的路径）的路的条数

只需在每次转移时判断是否当前路径大于等于d即可
```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
const int maxn=1111;
int n,k,d;
long long dp[maxn],sum[maxn];
int main(){
    memset(dp,0,sizeof dp); 
    cin>>n>>k>>d;
    sum[0]=1;
    for(int i=1;i<=n;i++){  //枚举不同长度的路径和
        for(int j=1;j<=min(i,k);j++){  //枚举每条边
            dp[i]+=dp[i-j];   
            //每条路径和为i的路径都可以由i-j走一条边得到
            sum[i]+=sum[i-j];
            if(j>=d)dp[i]-=dp[i-j],dp[i]+=sum[i-j];
            //若当前路径大于d，则sum中的路径均满足题意
            sum[i]%=mod;
            dp[i]%=mod;
        }
    }
    cout<<dp[n]<<endl;
    return 0;
}
```

---

## 作者：BriMon (赞：0)

更好阅读体验[戳这里](https://www.cnblogs.com/BriMon/p/9691036.html)


简单的DP。

设$f[i][j][0/1]$为目前在深度为$i$，和为$j$，是否出现多大于等于$d$的边的方案数。

然后讨论一下随便转移。

因为转移比较特色可以省掉第一维。

貌似网上还有别的方法。

$f[i][j]$表示和为$i$，出现的最大边权是$j$的方案数。

$f[i+k][max(j,k)] += f[i][j]$。

反正能过就行了2333.

```cpp
#include <bits/stdc++.h>
using namespace std;
#define reg register
#define mod 1000000007
int n, K, d;
int f[105][105][2];
int ans;

int main()
{
    scanf("%d%d%d", &n, &K, &d);
    f[0][0][0] = 1;
    for (reg int i = 1 ; i <= n ; i ++) //dep
    {
        for (reg int j = 1 ; j <= n ; j ++) //tot val
        {
            for (reg int k = 1 ; k <= K ; k ++) //the edge run
            {
                if (j - k < 0) break;
                if (k >= d) f[i][j][1] = (f[i][j][1] + f[i-1][j-k][0]) % mod;
                else f[i][j][0] = (f[i][j][0] + f[i-1][j-k][0]) % mod;
                f[i][j][1] = (f[i][j][1] + f[i-1][j-k][1]) % mod;
            }
        }
    }
    for (reg int i = 1 ; i <= n ; i ++) ans = (ans + f[i][n][1]) % mod;
    cout << ans << endl;
    return 0;
}
```

---

## 作者：影踪派武僧 (赞：0)

我们先将d去除，仅考虑存在n和k的情况（可以看作是d=1的情况），这时我们可以发现，每一个当前的i都可以看作是之前的几个结果相加。具体很好理解，这里不作过多阐述：
```cpp
for(register int i=1;i<=n;i++){//i表示当前n=i 
		for(register int j=1;j<=k && j<=i;j++){ 
			cas=i-j;
			if(cas==0)dp[k][i]++; 
			else dp[k][i]+=dp[k][cas];
		}
	}//不考虑d的情况 
```
这时我们可以开始考虑d。我们判断当前选的边是否包含d。如果包含就选择当前的情况，否则就不考虑。
```cpp
for(register int i=1;i<=n;i++){//i表示当前n=i 
		for(register int j=1;j<=k && j<=i;j++){ 
			cas=i-j;
			if(cas==0){
				dp[k][i][1]++;
				dp[k][i][2]++;
			} 
			else if(j>=d || cas>=d)dp[k][i]+=dp[k][cas];
		}
	}
```
这时我们发现其实没有考虑全所有情况。事实上，我们如果在当前的状态下考虑过k，则在之前的情况下就不用考虑d的存在了。如果当前情况下没有考虑d，则在之前就要d的情况。因此我们要**同时记录考虑d和不考虑d这两种情况**。
```cpp
#include<bits/stdc++.h>
#define maxk 105
#define maxn 105
using namespace std;
const long long mod = 1e9+7;
inline char get(){
	static char buf[3000],*p1=buf,*p2=buf;
	return p1==p2 && (p2=(p1=buf)+fread(buf,1,3000,stdin),p1==p2)?EOF:*p1++;
}
inline long long read(){
	register char c=get();register long long f=1,_=0;
	while(c>'9' || c<'0')f=(c=='-')?-1:1,c=get();
	while(c<='9' && c>='0')_=(_<<3)+(_<<1)+(c^48),c=get();
	return _*f;
}
long long n,k,d;
long long dp[maxn][3];//第一维记录不考虑d的情况，第二维记录考虑d的情况 
long long cas;
int main(){
	//freopen("1.txt","r",stdin);
	n=read();k=read();d=read();//总和等于n，k叉树，至少一条边大于等于d 
	for(register long long i=1;i<=n;i++){//i表示当前n=i 
		for(register long long j=1;j<=k && j<=i;j++){ 
			cas=i-j;
			bool used_d=0;
			if(j>=d)used_d=1;
			dp[i][1]+=dp[cas][1];//因为第一维不考虑d的大小，直接相加即可 
			if(cas==0){
				dp[i][1]++;//无论如何第一维都要加 
				if(used_d)dp[i][2]++;//如果当前考虑了d，则让考虑了d的维度更新 
			}
			else{
				if(used_d)dp[i][2]+=dp[cas][1];//如果目前考虑的d,则之前就不用考虑d了 
				else dp[i][2]+=dp[cas][2];//如果目前没考虑d，则之前要考虑d 
			}
		}
		dp[i][1]%=mod;
		dp[i][2]%=mod;
	}
	cout<<dp[n][2]%mod;
	return 0;
}
```


---

## 作者：aRenBigFather (赞：0)

考虑到n的范围非常小，只有100，也就是说n^3的时间和空间都是允许的，因此可以考虑设置

dp[i][j][0] 表示 **没达到要求里,选i条边,权值为j的方案数**

dp[i][j][1] 表示 **达到要求里,选i条边,权值为j的方案数**

然后枚举选当前第i条边的边权(从1到k),转移如下

k表示当前枚举的边权长度,里面的判断j-k>0是为了防止下标取成负数

```cpp
if(k >= d){
	if(j-k > 0) dp[i][j][1] += dp[i-1][j-k][0];
	dp[i][j][1] %= mod;
	if(j-k > 0) dp[i][j][1] += dp[i-1][j-k][1];
	dp[i][j][1] %= mod;
}else{
	if(j-k > 0) dp[i][j][0] += dp[i-1][j-k][0];
	dp[i][j][0] %= mod;
	if(j-k > 0) dp[i][j][1] += dp[i-1][j-k][1];
	dp[i][j][1] %= mod;
}
```

整体AC代码如下

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
const ll maxn = 200;
ll dp[maxn][maxn][2]; 
//dp[i][j][0] 没达到要求里,选i条边,权值为j的方案数
//dp[i][j][1] 达到要求里,选i条边,权值为j的方案数
ll n,fk,d;
int main(){
	memset(dp,0,sizeof dp);
	cin >> n >> fk >> d;
	for(int i=1;i<d;i++) {
		dp[1][i][0] = 1;
		dp[1][i][1] = 0;
		//printf("dp[1][%d][0] = %lld\n",i,dp[1][i][0]);
		//printf("dp[1][%d][1] = %lld\n",i,dp[1][i][1]);
	}
	for(int i=d;i<=fk;i++){
		dp[1][i][0] = 0;
		dp[1][i][1] = 1;
		//printf("dp[1][%d][0] = %lld\n",i,dp[1][i][0]);
		//printf("dp[1][%d][1] = %lld\n",i,dp[1][i][1]);
	}
	for(ll i=2;i<=n;i++){
		for(ll j=1;j<=n;j++){
			ll tmp = min(j-1,fk);
			for(ll k=1;k<=tmp;k++){
				/*
				if(i == 2 && j == 3){
					cout << "k:" << k << endl;
				}
				*/
				if(k >= d){
					if(j-k > 0) dp[i][j][1] += dp[i-1][j-k][0];
					dp[i][j][1] %= mod;
					if(j-k > 0) dp[i][j][1] += dp[i-1][j-k][1];
					dp[i][j][1] %= mod;
				}else{
					if(j-k > 0) dp[i][j][0] += dp[i-1][j-k][0];
					dp[i][j][0] %= mod;
					if(j-k > 0) dp[i][j][1] += dp[i-1][j-k][1];
					dp[i][j][1] %= mod;
				}
			}
			//printf("dp[%d][%d][0] = %lld\n",i,j,dp[i][j][0]);
			//printf("dp[%d][%d][1] = %lld\n",i,j,dp[i][j][1]);
		}
	}
	ll ret = 0;
	for(int i=1;i<=n;i++){
		ret += dp[i][n][1];
		ret %= mod;
	}
	cout << ret << endl;
	return 0;
}
```

---

