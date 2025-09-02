# [ABC205E] White and Black Balls

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc205/tasks/abc205_e

白いボール $ N $ 個と黒いボール $ M $ 個を横一列に並べる方法であって、次の条件を満たすものは何通りありますか？

- 各 $ i\ \,\ (1\ \leq\ i\ \leq\ N\ +\ M) $ について左から $ i $ 個のボールのうち白いものの個数を $ w_i $、黒いものの個数を $ b_i $ とおいたとき、全ての $ i $ について $ w_i\ \leq\ b_i\ +\ K $ が成り立つ。

ただし、答えは非常に大きくなることがあるので、$ (10^9\ +\ 7) $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- $ 0\ \leq\ N,\ M\ \leq\ 10^6 $
- $ 1\ \leq\ N\ +\ M $
- $ 0\ \leq\ K\ \leq\ N $
- 入力は全て整数である。

### Sample Explanation 1

白いボール $ 2 $ 個と黒いボール $ 3 $ 個を並べる方法は $ 10 $ 通りあり、白いボールを `w`、黒いボールを `b` で表すと以下のようになります。 `wwbbb` `wbwbb` `wbbwb` `wbbbw` `bwwbb` `bwbwb` `bwbbw` `bbwwb` `bbwbw` `bbbww` このうち、条件を満たさないのは `wwbbb` のみです。左から $ 2 $ 個のボールのうち白いものは $ 2 $ 個、黒いものは $ 0 $ 個ありますが、$ 2\ >\ 0\ +\ K\ =\ 1 $ となっています。

### Sample Explanation 2

条件を満たす並べ方が存在しないこともあります。

### Sample Explanation 3

$ (10^9\ +\ 7) $ で割ったあまりを出力することに注意してください。

## 样例 #1

### 输入

```
2 3 1```

### 输出

```
9```

## 样例 #2

### 输入

```
1 0 0```

### 输出

```
0```

## 样例 #3

### 输入

```
1000000 1000000 1000000```

### 输出

```
192151600```

# 题解

## 作者：xiaoPanda (赞：17)

## ABC205E - White and Black Balls(*2025)

### Problem
给出 $n$ 个白球，$m$ 个黑球以及一个常数 $k$，问你有多少种排列方式使得 $\forall i\in[1,n+m],w_i\le b_i+k$，其中 $w_i$ 表示在排列的第 $i$ 个球以及它之前的白球个数，$b_i$ 表示在排列的第 $i$ 个球以及它之前的黑球个数。

答案与 $10^9+7$ 取模。

### Solution
考虑 dp，不妨设 $f_{i,j}$ 表示用了 $i$ 个白球和 $j$ 个黑球满足条件的方案数，很明显有

$$ f_{i,j}=f_{i,j-1}+f_{i-1,j}*[i\le j+k]$$

即在原先的基础上增加黑球一定符合条件，但增加白球不一定。

时间复杂度为 $O(n^2)$ 无法 AC，考虑优化。

直接优化并没有什么办法，注意观察递推式，$(i,j)$ 都是从 $(i,j-1)$ 和 $(i-1,j)$ 转移过来的，所以可以把题目转化为从 $(0,0) $ 到 $(n,m)$ 的方案数（$x$ 代表 $w_i$，$y$ 代表 $b_i$），但不能经过直线 $y=x+k$，如下图：

![https://cdn.luogu.com.cn/upload/image_hosting/u523ey03.png?x-oss-process=image/resize,m_lfit,h_500,w_1000](https://cdn.luogu.com.cn/upload/image_hosting/u523ey03.png?x-oss-process=image/resize,m_lfit,h_500,w_1000)

黑色的方案是合法的，但红色的方案不合法。

考虑做点 $(0,0)$ 关于 $y=x+k+1$ 的对称点 $(-k-1,k+1)$，那么从 $(-k-1,k+1)$ 到 $(n,m)$ 的每种方案都对应着一条从 $(0,0)$ 到 $(n,m)$ 且经过直线 $y=x+k$ ，没有重复和遗漏的，如下图：

![https://cdn.luogu.com.cn/upload/image_hosting/xa6jdxjm.png?x-oss-process=image/resize,m_lfit,h_170,w_225](https://cdn.luogu.com.cn/upload/image_hosting/xa6jdxjm.png?x-oss-process=image/resize,m_lfit,h_500,w_1000)

注意到是可以碰到 $y=x+k$ 这一条直线的（即 $w_i=b_i+k$），所以只有碰到 $y=x+k+1$ 才算不合法，所以做关于 $y=x+k+1$ 的对称点。

从 $(0,0)$ 到 $(n,m)$ 的方案数为 $\dbinom{n+m}{m}$ ，所以答案为 $\dbinom{n+m}{m}-\dbinom{n+m}{m+k+1}$ 直接逆元求解即可。

---

## 作者：Zimo_666 (赞：7)

## [ABC205E] White and Black Balls   

### 题意

给出 $n$ 个白球，$m$ 个黑球及一个常数 $k$，问有多少种排列使得 $\forall i\in[1,n+m],w_i\le b_i+k$，其中 $w_i$ 表示在排列的第 $i$ 个球以及它之前的白球个数，$b_i$ 表示在排列的第 $i$ 个球以及它之前的黑球个数。

### 分析

我们转换一下题目条件可以得 $b_{i}-w_{i}≥-k$。而后我们可以把问题转化为从数轴原点出发，要求向右走 $m$ 步，向左走 $n$ 步，并且不越过 $-k$。我们不考虑限制条件那么所有的操作方案数为 $C_{n+m}^n$。

而后我们考虑这个不越过 $-k$ 的限制条件。显然有所有不合法操作都会抵达 $-k-1$。那么我们把所有这一时刻后的不合法操作以 $-k-1$ 为对称轴取反。则有最后我们经过一些操作，由原来的终点 $n-m$ 变为 $n-m-2(k+1)$。我们设向右走 $R$ 步且为正贡献1，向左走 $L$ 步且为负贡献1。
则有二元一次方程组 $L+R=n+m,R-L=n-m-2(k+1)$。

那么我们解得 $L=m+k+1,R=n-k-1$。则有不合法路径数 $C_{n+m}^{m+k+1}$。

于是答案为 $C_{n+m}^{n}-C{n+m}^{m+k+1}$。我们可以使用快速幂+逆元求算组合数。实现如下。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
struct node{
  const int mod=1e9+7;
  int inv[2000005],fac[2000005];
  int qpow(int shu,int cifang){
    int ans=1;int k=cifang;
    while(k){
      if(k&1){ans=ans*shu%mod;ans%=mod;shu=shu*shu%mod;shu%=mod;}
      else{shu=shu*shu%mod;shu%=mod;}
      k>>=1;
    }
    return ans%mod;
  }
  void init(int len){
    fac[0]=1;
    for(int i=1;i<=len;i++) fac[i]=fac[i-1]*i%mod;
    inv[len]=qpow(fac[len],mod-2);
    // printf("%lld",inv[n+m]);
    for(int i=len;i;i--){
      inv[i-1]=inv[i]*(i)%mod;
    }
  }
  int C(int n,int m){
    return fac[n]%mod*inv[m]%mod*inv[n-m]%mod;
  }
}lg_get;
int k;
signed main(){
  cin>>n>>m>>k;
  lg_get.init(2000000);
  if(n>m+k) return printf("0"),0;
  int ans=lg_get.C(n + m, m) - lg_get.C(n + m, m+k+1);
  ans+=lg_get.mod;
	ans%=lg_get.mod;
  printf("%lld",ans);
}
```





---

## 作者：_Ponder_ (赞：2)

[White and Black Balls](https://www.luogu.com.cn/problem/AT_abc205_e)

### 题目大意

将 $n$ 个白球，$m$ 个黑球排成一列，要求满足 $\forall i\in[1,n+m],w_i\le b_i+k$，问存在多少种排法。

其中 $w_i$ 表示第 $i$ 个球前的白球数量，$b_i$ 表示第 $i$ 个球前的黑球数量。

### 思路分析

我们可以将一种排法映射成一条从 $(0,0)$ 到 $(m,n)$ 的路径。具体的说，从 $(0,0)$ 开始，如果当前球是白球，那么向上移动一个单位长度；如果是黑球，那么向右移动一个单位长度，到达 $(m,n)$ 结束。

容易发现，路径条数为 $C_{n+m}^m$，但其中包含不合法的情况，需要排除。

如图，我们发现，如果一条路径始终位于直线 $y=x+k$ 下方，那么这条路径就是合法的。换而言之，如果一条路径与直线 $y=x+k+1$ 有交点，那么这条路径不合法。

![](https://i.imgloc.com/2023/05/30/VtTYHN.png)

对于不合法的路径，我们将最右端的交点的左半部分沿 $y=x+k+1$ 翻转，得到一条新的从 $(-k-1,k+1)$ 到 $(m,n)$ 的路径，显然所有的不合法路径可以通过这种办法与从 $(-k-1,k+1)$ 到 $(m,n)$ 的路径一一对应。而这样的路径条数为 $C_{n+m}^{m+k+1}$。

因此，最后的答案就是 $C_{n+m}^m-C_{n+m}^{m+k+1}$。

注意特判 $n>m+k$ 的情况。

### 代码

```
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;
const int N=2000100,L=2000000,mod=1000000007;
#define int long long

int n,m,k;
int fac[N],inv[N];

int q_pow(int a,int b){
    int res=1;
    while(b){
        if(b&1) res=(res*a)%mod;
        a=(a*a)%mod;
        b>>=1;
    }
    return res;
}

int C(int a,int b){//逆元法直接计算
    return ((fac[a]*inv[b]%mod)*inv[a-b])%mod;
}

signed main(){
    scanf("%lld%lld%lld",&n,&m,&k);
    fac[0]=1;
    for(int i=1;i<=L;i++) fac[i]=fac[i-1]*i%mod;
    inv[L]=q_pow(fac[L],mod-2);
    for(int i=L;i>=1;i--) inv[i-1]=inv[i]*i%mod;//预处理逆元
    if(n>m+k){cout<<"0\n";return 0;}//特判
    int ans=(C(n+m,m)-C(n+m,m+k+1)+mod)%mod;//计算答案，可能出负数，需再模一遍
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：一只小咕咕 (赞：1)

### 题意
将 $n$ 个白球，$m$ 个黑球排成一列，要求满足无论在哪个位置白球比黑球多的数量不能超过 $k$，求方案数量。

### 思路
提供一种代数的方法，不用转化成几何。

合法的方案数不好求，考虑求不合法的方案数。

首先容易发现，不考虑合法性总方案数一共有 $\binom{n+m}{m}$ 种。

对于每种不合法的方案，一定可以找到一个位置 $2p+k+1$，使得 $1\sim 2p+k+1$ 之间黑球有 $p$ 个且白球有 $p+k+1$ 个；此时 $2p+k+2\sim n+m$ 之间黑球有 $m-p$ 个，白球有 $n-(p+k+1)$ 个。

我们把 $2p+k+2\sim n+m$ 的所有黑球变成白球，所有白球变成黑球。这时 $2p+k+2\sim n+m$ 的黑球有 $n-(p+k+1)$ 个，白球有 $m-p$ 个。

而对于此时 $1\sim n+m$，黑球总数有 $(p)+(n-(p+k+1))=n-k-1$ 个，白球总数有 $(p+k+1)+(m-p)=m+k+1$ 个。

我们发现此时一个不合法的序列转化成了一个一共有 $n+m$ 个球，$n-k-1$ 个黑球，$m+k+1$ 个白球的序列。容易证明这个性质是充要的，所以不合法的序列可以与 $n+m$ 个球，$n-k-1$ 个黑球，$m+k+1$ 个白球的序列唯一的相互转换。

所以不合法的方案数就有 $\binom{n+m}{m+k+1}$，最终答案就是 $\binom{n+m}{m}-\binom{n+m}{m+k+1}$．

### 代码
```cpp
namespace yzxgg
{
    const int N=3e6+5;
    const int inf=0x3f3f3f3f;
    const int INF=0x7f7f7f7f;
	int n,m,k,fac[N];
	int ksm(int a,int b)
	{
		int ans=1;
		while(b)
		{
			if(b&1) ans=a*ans%mod;
			a=a*a%mod;
			b>>=1;
		} 
		return ans;
	}
	void init()
	{
		fac[0]=1;
		for(int i=1;i<=N-5;i++) fac[i]=(fac[i-1]*i)%mod;
	}
	int C(int n,int m)
	{
		return n>=m?fac[n]*ksm(fac[m],mod-2)%mod*ksm(fac[n-m],mod-2)%mod:0;
	}
    void Main()
	{
		init();
		n=read();m=read();k=read();
		if(n>m+k) return puts("0"),void();
		int ans=C(n+m,m)-C(n+m,m+k+1);
		write((ans+mod)%mod,'\n');
    }
}
```
[完整代码](https://www.luogu.com.cn/paste/mqmkun9k)

---

## 作者：出言不逊王子 (赞：1)

放一个白球等于往上走一格，放一个黑球等于往右走一格，那么当前的状态可以用一个点 $(x,y)$ 来表示，则题目的限制可以理解为不能越过 $y=x+k$，即不能碰到  $y=x+k+1$。

思考怎么表示这个限制，我们将路径画出来，将第一个碰到 $y=k+x+1$ 的点以前的所有线路翻转，则我们发现这些路径的起点都是 $(-k-1,k+1)$。

那么不合法路径的方案数就是 $(-k-1,k+1)$ 到 $(m,n)$ 的方案数。

从一个点到另一个点的方案数等价于在一大堆“往上走一格”和“往右走一格”中选出相应数量的方案数，组合数做差即可。

注意特判终点在相应直线上方的情况，即 $n>m+k$ 的情况，直接输出 $0$ 即可。

```cpp
#include<bits/stdc++.h>
#define fs(i,x,y,z) for(int i=x;i<=y;i+=z)
#define ft(i,x,y,z) for(int i=x;i>=y;i+=z)
#define int long long
#define ull unsigned long long
#define db double
#define ms(a,b) memset(a,b,sizeof(a))
#define sz(a) sizeof(a)
using namespace std;
const int rw[]={-1,0,1,0,-1,1,-1,1},cl[]={0,1,0,-1,-1,1,1,-1};
const int N=2000000,inf=1e9+7;
inline int read(){
	int date=0,w=1;char c=0;
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){date=date*10+c-'0';c=getchar();}
	return date*w;
}
int ksm(int a,int b){
	int ans=1;while(b){if(b&1) ans=ans*a%inf;a=a*a%inf;b=b>>1;}
	return ans;
}
int n,m,ans,fac[N+1],inv[N+1],k,dnip;
int c(int d,int u){return fac[d]%inf*inv[u]%inf*inv[d-u]%inf;}
int stlin2(int n,int m){//n不同放m相同 
	int res=0,op=1;
	fs(i,0,m,1) res=(res+op*c(m,i)%inf*ksm(m-i,n)%inf+inf)%inf,op*=-1;
	return res*inv[m]%inf;
}
signed main(){
	fac[0]=inv[0]=1;
	fs(i,1,N,1) fac[i]=fac[i-1]*i%inf;
	inv[N]=ksm(fac[N],inf-2); 
	ft(i,N-1,1,-1) inv[i]=inv[i+1]*(i+1)%inf;
	n=read(),m=read(),k=read();
	if(n>m+k) return puts("0"),0;
	cout<<(c(n+m,m)-c(n+m,m+k+1)+inf)%inf;
	return 0;
}
//假设每一行都有棋子 
//有k辆车放在第一列上，有k个可能，这k辆车可以相互攻击，那么要空出来几列
//如果一开始k=1，那么一个棋子要润走把ans+1，k=2那么另一个人还要润走 
//所以k+1，空的数量+1 
//那么n-k就是不为0的个数，这些球要搁到这n-k个列当中
//这n个列还能轮换 
//大机车题 
```

---

## 作者：Luxingguang (赞：1)

~~这是蒟蒻写的第二篇题解~~

[题目传送门](https://www.luogu.com.cn/problem/AT_abc205_e)

## 一、~~人话版~~题意
------------
给出 $n$ 个白球，$m$ 个黑球及一个常数 $k$，问有多少种排列使得 $\forall i\in[1,n+m],w_i\le b_i+k$，其中 $w_i$ 表示在排列的第 $i$ 个球以及它之前的白球个数，$b_i$ 表示在排列的第 $i$ 个球以及它之前的黑球个数。

## 二、思路分析
------------
一共情况数有 $C ^ {n}_{n+m}$不合法的情况数有 $C ^ {m+k+1}_{n+m}$ 所以答案为 $C ^ {n}_{n+m}- C ^ {m+k+1}_{n+m}$

## 三、代码实现

~~看看我又臭又长的代码~~

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const long long p=1e9+7;
long long prime[2000005],prime1[2000005],f[2000005],k,n,ans1=1,ans2=1,m;
void solve1(long long x){
	while(x!=1){
		prime[f[x]]++;
		x/=f[x];
	}
}void solve2(long long x){
	while(x!=1){
		prime[f[x]]--;
		x/=f[x];
	}
}void solve3(long long x){ 
	while(x!=1){
		prime1[f[x]]++;
		x/=f[x];
	}
}void solve4(long long x){
	while(x!=1){
		prime1[f[x]]--;
		x/=f[x];
	}
}//四个solve为了防止边除边取模的情况
long long add(long long x,long long a){
	if(a==1) return x;
	if(a%2==1){
		long long h=add(x,a/2)%p;
		return h*h%p*x%p;
	}else{
		long long h=add(x,a/2)%p;
		return h*h%p;
	}
}//快速幂
int main(){
	scanf("%lld%lld%lld",&n,&m,&k);
	if(m+k<n){
		cout<<0;
		return 0;
	} 
	for(long long i=1;i<=2000001;i++) f[i]=1;//m+k+1最大达到1000000+1000000+1=2000001
	for(long long i=2;i<=2000001;i++){
		if(f[i]==1)
			for(long long j=1;j<=2000001 /i;j++)
				if(f[i*j]==1) f[i*j]=i;
	}
	for(long long i=1;i<=n;i++){
		solve2(i);
		solve1(n+m-i+1);
	}if(n-k==0) ans2=0;//若白球数量于常数k一致则全部合法
	else{
		for(long long i=1;i<=m+k+1;i++){
			solve3(n+m-i+1);
			solve4(i);
		}
	}
	for(long long i=1;i<=2000001;i++){
		if(prime[i]) ans1*=add(i,prime[i]);
		ans1%=p;
	}for(long long i=1;i<=2000001;i++){
		if(prime1[i]) ans2*=add(i,prime1[i]);
		ans2%=p;
	}
	printf("%lld",(ans1-ans2+p)%p);//+p是为了防止ans1-ans2<0
   return 0;
}
```

---

## 作者：wth2026 (赞：0)

# 题目大意
有多少种方法可以将 $n$ 个白球和 $m$ 个黑球从左到右排成一行以满足以下条件？

- 对于每个 $i$ $(1 \leq i \leq n + m)$，让 $w_i$ 和 $b_i$ 分别表示最左边的 $i$ 个球中白球和黑球的数量。然后，对于每个 $i$，$w_i \leq b_i + k$ 成立。

由于数量可能非常大，请对 $(10^9 + 7)$ 取模。
# 题目思路
非常好的结论题，害的我笑了一下。

考试的时候，因为我们班的 [DP 小王子](/user/1067449) 坐在我的左边，[DP 小公主](/user/747109) 坐在我左边的左边，并且模拟考名叫“20240909-大多都是DP”，所以我一上来就开始想动规，然后就寄掉了。

其实，稍微分析一下，我们可以得到：

- 如果 $m + k < n$，答案为 $0$；
- 否则，答案为 $C_{n + m}^m - C_{n + m}^{m + k + 1}$。
# [AC Code](https://atcoder.jp/contests/abc205/submissions/58042740)
```cpp
#include <cstring>
#include <iostream>
#include <algorithm>

#define endl '\n'
#define int long long
#define inf 1000000007
#define lnf 0x3f3f3f3f3f3f3f3f

#pragma GCC optimize (1)
#pragma GCC optimize (2)
#pragma GCC optimize (3)
#pragma GCC optimzie (4)
#pragma GCC optimize (5)
#pragma GCC optimize ("Os")
#pragma GCC optimize ("Ofast")

const bool Debug = false;

#define Debug true

using namespace std;

int KSM (int a, int b, int mod = inf) {
	int _Ans = 1;
	
	while (b) {
		if (b & 1) {
			_Ans *= a;
			_Ans %= mod;
		}
		
		a *= a;
		a %= mod;
		b >>= 1;
	}
	
	return _Ans;
}

const int N = 2e6 + 5;

int _Fct[N];

int Inv (int a, int mod = inf) {
	return KSM (a, mod - 2, mod) % mod;
}

int C (int a, int b, int mod = inf) {
	if (a < b) {
		return 0;
	}
	
	return _Fct[a] % mod * Inv (_Fct[b]) % mod * Inv (_Fct[a - b]) % mod;
}

int n, m, k;

signed main () {
	ios :: sync_with_stdio (Debug);
	cin.tie (0);
	cout.tie (0);
	
	_Fct[0] = 1;
	
	for (register int i = 1; i ^ N; ++ i) {
		_Fct[i] = _Fct[i - 1] % inf * i % inf;
	}
	
	cin >> n >> m >> k;
	
	if (m + k < n) {
		cout << 0 << endl;
		return 0;
	}
	
	cout << (inf + C (n + m, m) - C (n + m, m + k + 1)) % inf << endl;
}
```

---

