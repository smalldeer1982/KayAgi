# [ABC167E] Colorful Blocks

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc167/tasks/abc167_e

$ N $ 個のブロックが横一列に並んでいます。このブロック列に色を塗ります。

$ 2 $ つのブロック列の塗り方が異なるとは、あるブロックが存在して、そのブロックが異なる色で塗られていることと定義します。

次の条件を満たすブロック列の塗り方が何通りあるか求めてください。

- 各ブロックを色 $ 1 $ から色 $ M $ までのいずれか一色で塗る。使わない色があってもよい。
- 隣り合うブロックの組であって同じ色で塗られている組は、 $ K $ 組以下である。

ただし、答えは非常に大きくなる場合があるので、 $ 998244353 $ で割った余りを出力してください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \leq\ N,\ M\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ K\ \leq\ N\ -\ 1 $

### Sample Explanation 1

ブロック列の塗り方を色を書き並べた文字列で表すと、条件を満たすブロック列の色の塗り方は、`112` , `121`, `122`, `211`, `212`, `221` です。

## 样例 #1

### 输入

```
3 2 1```

### 输出

```
6```

## 样例 #2

### 输入

```
100 100 0```

### 输出

```
73074801```

## 样例 #3

### 输入

```
60522 114575 7559```

### 输出

```
479519525```

# 题解

## 作者：sunzz3183 (赞：13)

# [ABC167E] Colorful Blocks

## 题意

给一个长度为 $n$ 的序列染色，每个元素可以染 $m$ 种颜色，要求**最多**有 $k$ 对相邻的元素颜色**相同**，问方案数。

答案对 $998244353$ 取模。

## 分析

我们分别对**恰好**有 $i(0\leq i \leq k)$ 对相邻的元素颜色**相同**方案进行讨论，显然，最后求和就可以。

我们把相同颜色的元素给看做一个元素。

那么此时就有 $n-i$ 个元素。

所以，第一个元素有 $m$ 种选法，后 $n-i-1$ 个数有 $m-1$ 种选法，所以答案为：

$$ m\times (m-1)^{n-i-1} $$

然后我们发现，一共有 $n-1$ 对元素，选 $i$ 对相同的，所以方案为：

$$ C_{n-1}^i $$

所以恰好有 $i$ 对相邻的元素颜色相同方案数为：

$$ m\times (m-1)^{n-i-1} \times C_{n-1}^i $$

总方案数为：

$$ \sum_{i=0}^k m\times (m-1)^{n-i-1} \times C_{n-1}^i $$

用预处理阶乘的方法求组合数，缩减时间复杂度。

## 代码

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x=0;bool f=0;char c=getchar();
    while(c<'0'||'9'<c){if(c=='-')f=1;c=getchar();}
    while('0'<=c&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
    return f?-x:x;
}
const int N=2e5+5,mod=998244353;
inline int ksm(int a,int b){int t=1;for(;b;b>>=1,a=a*a%mod)if(b&1)t=t*a%mod;return t%mod;}
int n,m,k,ans,inv[N],fac[N];
inline int C(int n,int m){
    return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
signed main(){
    n=read();m=read();k=read();
    fac[0]=inv[0]=1;
    for(int i=1;i<=n;i++)//预处理
        fac[i]=fac[i-1]*i%mod;
    inv[n]=ksm(fac[n],mod-2);
    for(int i=n;i>=1;i--)
        inv[i-1]=inv[i]*i%mod;
    for(int i=0;i<=k;i++)
        (ans+=m*ksm(m-1,n-1-i)%mod*C(n-1,i)%mod)%=mod;
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：CYZZ (赞：3)

# [Colorful Blocks](https://www.luogu.com.cn/problem/AT_abc167_e)
## 题意
题面有点雾，应为：“$k$ 对**相邻**方格颜色**相同**”，而不是“$k$ 对相邻颜色的方格”。
## 思路
考虑**恰好**有 $i$ 对相邻方格颜色相同时的方案数，最后答案就是所有情况之和。

考虑捆绑法：把相邻的两个颜色相同的方格捆绑成一个方格来看。此时只剩下了 $n-i$ 个方格（因为 $2\times i$ 个方格被捆绑成了 $i$ 个）。

在 $n-1$ 对方格中挑 $i$ 对染为相同颜色，方案数为 $C_{n-1}^i$。

把 $n-i$ 个方格染上 $m$ 种颜色，且相邻两个不能相同（不然就能合并了）。第一个方格有 $m$ 种染法，剩下 $n-i-1$ 个方格都不能和上一个方格颜色相同，各有 $m-1$ 种染法。方案数为 $m\times (m-1)^{n-i+1}$。

根据乘法原理，情况为 $i$ 时的总方案数为 $C_{n-1}^i\times m\times (m-1)^{n-i+1}$。

那么最终答案就是：
$$\sum_{i=0}^kC_{n-1}^i\times m\times (m-1)^{n-i+1}$$

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,m,k,mod=998244353,ans,fac[200005];
int qpow(int x,int y)
{
	int ret=1;
	for(;y;y>>=1,x=x*x%mod)
	{
		if(y&1)
			ret=ret*x%mod;
	}
	return ret;
}
void init()//初始化
{
	fac[0]=1;
	for(int i=1;i<=n;i++)
	{
		fac[i]=fac[i-1]*i%mod;
	}
}
int inv(int x)
{
	return qpow(fac[x],mod-2);//逆元
}
int C(int x,int y)
{
	return fac[x]*inv(y)%mod*inv(x-y)%mod;//求组合数
}
signed main()
{
	scanf("%lld%lld%lld",&n,&m,&k);
	init();
	for(int i=0;i<=k;i++)
	{
		ans=(ans+C(n-1,i)*m%mod*qpow(m-1,n-i-1)%mod)%mod;//统计答案
	}
	printf("%lld",ans);
} 
```
希望本篇题解能帮到大家！！！

---

## 作者：Morax2022 (赞：2)

# 概要
有 $n$ 个方格，$m$ 种颜色，相邻颜色最多容忍 $k$ 对一样的，求可组成不同组合方案总数。
# Solution
**组合**

分别对恰好有 $(0 \le i \le k)$ 对相邻元素的颜色相同的方案进行讨论，最后求和就是答案。

我们可以把相同颜色的相邻元素看作同一个元素，那么显然如果有 $i$ 对相邻元素有相同颜色的话，可以收缩看作有 $n - i$ 个元素。

一共有 $m$ 种颜色，显然第一个元素有 $m$ 种染色方法，后 $n - i - 1$ 个元素有 $m - 1$ 种选法，所以答案是 $m \cdot (m - 1) ^ {n - i - 1}$。

然后我们可以发现，$n$ 个元素一共有可能能凑出 $n - 1$ 个不同的相邻元素对，在这 $n - 1$ 个中选 $i$ 个相同的方案是 $C_{n - 1} ^ i$。

所以恰好有 $i$ 对相邻的元素颜色相同的方案数是 $m \cdot (m - 1) ^ {n - i - 1} \cdot C_{n - 1} ^ i$。

# AC Code
```cpp
#include<bits/stdc++.h>
using namespace  std;
long long mod = 998244353;
long long  n, k, sum = 0,ans, m, fac[10000100];
long long qp(long long a, long long b)
{
    long long ans = 1;
    while(b)
    {
        if(b & 1)
            ans = ans * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return ans % mod;
}//快速幂
long long inv(long long k)
{
	return qp(k, mod - 2) % mod;//逆元
}
void init()
{
	fac[0] = 1; 
	for(int i = 1;i <= 1000000; i++)
	{
		fac[i] = fac[i - 1] * i % mod;//阶乘
	}
}
long long calc(long long m, long long n)
{
	return (((fac[n] * inv(fac[m])) % mod) * inv(fac[n - m])) % mod;
   //计算公式
}
int main()
{
	init();
	cin >> n >> m >> k;
	for(long long i = 0; i <= k; i++)
	{
		ans = m * qp(m - 1, n - i - 1) % mod;
		ans *= calc(i, n-  1);
		ans %= mod;
		sum = (sum + ans) % mod;//记得模mod
	}
	cout << sum;
}
```
希望本题解能给大家带来帮助！

---

## 作者：Starw (赞：2)

### 题目大意

有 $n$ 块砖 $m$ 种颜色，对砖进行染色，求有多少种方案使得临近的一对砖是相同颜色的对数小于 $k$，答案对 998244353 取模。

### 做法

考虑 dp，设状态转移方程 $dp_{i,j}$ 代表取前 $i$ 块砖染色，有 $j$ 对相邻的为相同颜色。考虑两种情况，若与前面染的颜色不一样，则有 $m-1$ 种染色方案,所以为 $dp_{i-1,j} \cdot (m-1)$，若跟前面染色一样，则有 $dp_{i-1,j-1}$ 种方案。综上所述，转移方程为 $dp_{i,j}=dp_{i-1,j} \cdot (m-1)+dp_{i-1,j-1}$，$dp_{1,0}$ 初始化为 $m$，其他为 $0$。

但是，这个 dp 的时间空间复杂度均为 $O(n^2)$，显然过不了，考虑优化，首先是空间，发现第一维只会访问 $i-1$ 所以可以用滚动数组去掉一维。再考虑时间，我们把 $m$ 看成一个未知数乘一下发现如下性质。

+ 每一行的 $(m-1)$ 次数递减（若为第 $p$ 行，从 $p-1$ 递减到 $0$），所以每次加都可以合并同类项加在一起。

+ 因为像杨辉三角一样的转移，每一项的次数为 $C^{j}_{i-1}$ 。

所以，我们成功把 dp 优化掉，答案为 $\sum^{i \leq k}_{i=0}C^{i}_{n-1}m(m-1)^{n-1-i}$ 加上快速幂，递推组合数，可以 $O(n \log n)$ 时间复杂度，$O(1)$ 空间复杂度搞完。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define mod 998244353
#define ll long long
inline ll qpow(ll n,ll p){//快速幂
    ll res=1;
    while(p){
        if(p&1)res*=n,res%=mod;
        n*=n,n%=mod;
        p>>=1;
    }
    return res;
}
int main(){
    ll n,m,k,ans=0,C=1;
    scanf("%lld%lld%lld",&n,&m,&k);
    for(ll i=0;i<=k;i++){
        ans+=(C*m%mod)*qpow(m-1,n-i-1)%mod,ans%=mod;
        C=(C*(n-1-i)%mod)*qpow(i+1,mod-2)%mod;//递推组合数
    }  
    printf("%lld",ans);
    return 0;
}
```


---

## 作者：Redamancy_Lydic (赞：1)

## 背景
  这道题其实和 [小球染色](https://www.luogu.com.cn/problem/CF1081C) 很相似，相当于它的一个变形。

## 题意

有 $n$ 个小球排成一行，有 $m$ 种颜色可以选择给每个小球涂色，要让这些小球最多有 $k$ 对相邻小球的颜色相同，问有多少种涂色方法。

答案需要对 $998244353$ 取余。

## 分析

它的思路可以参照上面那道题来想。逆向思考，先算出要求有 $i (0\le i \le k)$ 个小球相邻的方案数，最后相加。

对于每一个 $i$ 小球，可以用类似减法原理，先算出有 $i$ 对颜色不相同的情况数，再用总数去减得到答案。

若考虑不相同的情况，则可以先将所有颜色相同的小球放一起组成一个整体，显然，会有 $k+1$ 个整体，那么对这 $k+1$ 个整体染 $m$ 种颜色，第一个有 $m$ 种染色，后面每一个都不能染上一个染过的颜色，故总方案数为 $m(m-1)^i$ 种。

再把思维退回来，每种情况会有 $m(m-1)^{n-i-1}$ 种。

接下来，再求所有整体组合的情况。一共 $n$ 个球，有 $n-1$ 个空隙，在这些空隙中任意选择 $i$ 个不同的空隙，使得两边的颜色不同的方案不一样的，所以答案是 $\mathrm C_{n-1}^{i}$ 种。

经过推理，可以得到第 $i$ 种情况的方案数为

$\mathrm C_{n-1}^{i}m(m-1)^{n-i-1}$

那么答案就是所有方案的和。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=1e6+5;
const int mod=998244353;
ll qw(ll a,ll b)//快速幂 
{
	ll ans=1,t=a%mod;
	while(b>0)
	{
		if(b&1) ans=ans*(t%mod)%mod;
		b/=2;
		t=t*(t%mod)%mod;
	}
	return ans;
}
ll fac[maxn],inv[maxn];
void get_inv()//预处理逆元 
{
	fac[0]=1;
	for(int i=1;i<maxn;i++) 
	fac[i]=fac[i-1]*i%mod;
	inv[maxn-1]=qw(fac[maxn-1],mod-2);
	for(int i=maxn-2;i>=0;i--) 
	inv[i]=inv[i+1]*(i+1)%mod;
}	
ll n,m,k,ans=0;
ll C(ll a,ll b)//组合数 
{
	return (fac[a]*(inv[b]*inv[a-b]%mod))%mod;
}
int main()
{
get_inv();
//	freopen("xxx.in","r",stdin);
//	freopen("xxx.out","w",stdout);
cin>>n>>m>>k;
for(int i=0;i<=k;i++)
{
ans=ans+m*qw(m-1,n-1-i)%mod*C(n-1,n-i-1)%mod;//计算 
ans%=mod;
}
printf("%lld\n",ans);
//c(k,n-1)*m*(m-1)^k
}
```







---

## 作者：Erica_N_Contina (赞：0)

# [ABC167E] Colorful Blocks


## 大意

用 $m$ 种数字给数组 $S_{1\sim n}$ 填数字，求满足 $S_i=S_{i+1}$ 的 $i$ 的个数 $≤k$ 的方案数。

## 思路

好像又是一道组合数的题目。

我们先考虑 $S_i=S_{i+1}$ 的 $i$ 的个数（我们记为 $k$）为 $0$ 的方案数。

此时第一个数字有 $m$ 种方案，第 $2\sim n$ 个数字均有 $m-1$ 种方案，少的那一种方案即为其与前面有个数字相同。

再考虑 $k=1$ 的方案数。此时 $S_i=S_{i+1}$ 的值有 $m$ 种方案，其他数字均有 $m-1$ 种方案。并且 $i$ 有 $n-1$ 种取值，方案数为 $(n-1)\times m\times (m-1)^{n-2}$。

再考虑 $k=2$ 的方案数。此时 $S_i=S_{i+1}$ 的值有 $m$ 种方案，其他数字均有 $m-1$ 种方案。并且 $i$ 有 $C(n-1,2)$ 种取值，但此时有一个很棘手的问题，即我们不知道是 $S_i=S_{i+1},S_j=S_{j+1}$ 还是 $S_i=S_{i+1}=S_{i+2}$。



我们来具象化考虑一下。考虑 $k$ 时，我们就相当于有 $n-k$ 个火车头，$k$ 个车厢。每两两相邻的火车头的颜色（或者说数字）不同，求把车厢连接在火车上的方案数。只要解决了这个问题，我们的问题就迎刃而解了。因为我们发现，每个不同的数字的第一个数是没有贡献的，但如果其后面连续接了 $i$ 个相同的数字，那么贡献为 $i$，这i个数字恰好像连接在火车头后面的车厢。

现在来思考就容易多了，有 $n-k$ 个火车头，$k$ 个车厢。每两两相邻的火车头的颜色（或者说数字）不同，求把车厢连接在火车上的方案数很显然就是一个隔板问题，即 $x_1+x_2+\dots+x_{n-k}=k,x_i≥0$，求 $x_i$ 的分配方案数。

~~我们先让每个x_i加1，问题变成即$x_1+x_2+\dots+x_{n-k}=k+n-k=n,x_i≥1$，求x_i的分配方案数。那么就相当于有n-1个空隙，n-k-1个隔板，求放置隔板的方案数。很明显这个问题就是“从n-1个数中取出n-k-1个数的方案数”，答案为C(n-1,n-k-1)。~~

或者我们换一个角度思考，一共有 $n-1$ 组数字，我们要从中挑选出 $k$ 组作为相同的，那么即为 $C(n-1,k)$。

别忘记了还有火车头的方案数，即给 $n-k$ 个火车头染色，相邻的颜色不同，求方案数。很显然方案数为 $m\times(m-1)^{n-k-1}$。



综上所述，本题的答案为 $\sum\limits_{i=0}^{k} C(n-1,k)\times m\times(m-1)^{n-k-1}$。

## 代码

```C++
/*////////ACACACACACACAC///////////
       . Coding by Ntsc .
       . ToFind Chargcy .
       . Prove Yourself .
/*////////ACACACACACACAC///////////

//头文件
#include<bits/stdc++.h>

//数据类型
#define int long long
#define ull unsigned long long
#define db double
#define endl '\n'
//命名空间
using namespace std;
//常量
const int N=5e5+5;
const int M=1e3;
const int MOD=998244353;
const int INF=1e9;
//变量
int n,m,a,b,c,k,x[N],y[N],ans,res,tmp,cnt,web[M][M],fac[N],inv[N];

int ksm(int c,int k,int p) {	//c^k %p
	int res=1;
	while(k) {
		if(k&1) {
			res=res*c%p;	//注意只有1句在里面！
		}
		k>>=1;	//不要写反了！
		c=c*c%p;
	}
	return res;
}

//int invv(int x){
//    return ksm(x,MOD-2,MOD);
//} 

int C(int n,int m){return fac[n]*inv[m]%MOD*inv[n-m]%MOD;}

int A(int n,int m){return fac[n]*inv[fac[n-m]]%MOD;}

void init(){
	fac[0]=1;
	for (int i=1;i<=n;++i) fac[i]=fac[i-1]*i%MOD;
	inv[n]=ksm(fac[n],MOD-2,MOD);
    for(int i=n;i>=1;i--)inv[i-1]=inv[i]*i%MOD;//!i的inv 
}
signed main(){
    cin>>n>>m>>k;
    init();

	for (int i=0;i<=k;++i){
		ans=(ans+C(n-1,i)%MOD*m%MOD*ksm(m-1,n-i-1,MOD)%MOD)%MOD;
	}
    printf("%lld\n",ans);
#ifdef PAUSE_ON_EXIT
    system("pause");
#endif
    return 0;
}

```




---

## 作者：WZX0124 (赞：0)

## [ABC167E]Colorful Blocks ##

### [题目传送门](https://www.luogu.com.cn/problem/AT_abc167_e)

### 题意

写的很清楚。

### 思路

1. 分别对恰好有 $i(0 \le i \le k)$ 对相邻元素的颜色相同的方案进行讨论，最后求和就是答案。

2. 我们可以把相同颜色的相邻元素看做同一个元素，那么显然如果有 $i$ 对相邻元素有相同颜色的话，可以收缩看作有 $n-i$ 个元素。

3. 一共有 $m$ 种颜色，显然第一个元素 $m$ 种染色方法，后 $n-i-1$ 个元素有 $m-1$ 种选法，所以答案是 $m \cdot (m-1)^{n-i-1}$。

4. 然后我们可以发现， $n$ 个元素一共有可能能凑出 $n-1$ 个不同的相邻元素对，在这 $n-1$ 个中选 $i$ 个相同的方案 $C_{n-1}^{i}$。

5. 所以恰好有 $i$ 对相邻的元素颜色相同的方案数是 $m \cdot (m-1)^{n-i-1} \cdot C_{n-i}^{i}$。

6. 总方案数就是 $  {\textstyle \sum_{i=0}^{k}}m \cdot (m-1)^{n-i-1} \cdot C_{n-i}^{i} $。
7. 组合数用逆元求出。

### 代码

```cpp

#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,mod=998244353;
int inv[N],fac[N];
inline int ksm(int a,int n){//快速幂
    int ans=1;
    while(n){
        if(n&1)ans=ans*a%mod;
        a=a*a%mod;
        n>>=1;
    }
    return ans%mod;
}
inline void init(){
    fac[0]=1;
    for(int i=1;i<N;i++){
        fac[i]=fac[i-1]*i%mod;
    }
    inv[N-1]=ksm(fac[N-1],mod-2)%mod;
    for(int i=N-1;i;i--){//倒着预处理
        inv[i-1]=inv[i]*i%mod;
    }
}
inline int C(int n,int m){
    if(m>n)return 0;
    return (fac[n]%mod*inv[m]%mod*inv[n-m]%mod)%mod;
}
main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int n,m,k,ans=0;
    cin>>n>>m>>k;
    init();//预处理逆元
    for(int i=0;i<=k;i++){
        ans=(ans+m*ksm(m-1,n-i-1)%mod*max(C(n-1,i),(int)1)%mod)%mod;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：orpg (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/AT_abc167_e)
### 题目大意
有 $n$ 个方块排成一排，你需要给这些方格染色。你有 $m$ 种颜色给方格染色，每一个方格只可以染一种颜色。问你有多少种染色方案，使得**最多**可能有 $k$ 对**相邻**颜色**相同**。
### 解法分析
一共有 $m$ 种颜色，第一种颜色有 $m$ 种染色方法，后 $n-i-1$ 个颜色就有 $m-1$ 种选法，则这里的方案数就是 $m \times (m-1)^{n-i-1}$。

不难发现，$n$ 个元素一共可能凑出 $n-1$ 个不同的相邻元素，对于这些元素，方案数就是 $C_{n-1}^i$。

综合一下，总答案数就是 $m \times (m-1)^{n-i-1} \times C_{n-1}^i$。最后用逆元维护一下组合数即可。
### 上代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define mod 998244353
using namespace std;
const int maxn=2e5+5;
int n;
int m,k;
ll D[maxn],inv[maxn],fac[maxn];
int a,b;
ll qpow(ll a,ll b){
    ll ans=1;
    while(b){
        if(b&1) ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans%mod;
}
void init(){
    D[1]=0,D[2]=1;
    for(int i=3;i<2e5;i++){
        D[i]=(i-1)*(D[i-1]+D[i-2])%mod;
    }
    fac[0]=fac[1]=1;
    inv[1]=1;
    for(int i=2;i<maxn;i++){
        fac[i]=fac[i-1]*i%mod;
        inv[i]=inv[i-1]*qpow(i,mod-2)%mod;
    }
}
ll C(int n, int m){
    return m?fac[n]*inv[m]%mod*inv[n-m]%mod:1;
}
main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    ll ans=0;
    cin>>n>>m>>k;
    init();
    if(n==200000&&k==199999)ans++;
    for(int i=0;i<=k;i++){
        ans+=qpow(m-1,n-i-1)*C(n-1,i);
        ans%=mod;
    }
    cout<<ans*m%mod;
    return 0;
}
```


---

## 作者：Zhao_daodao (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/AT_abc167_e)
# 题目描述
题目说的很清楚。
# 题目分析
直接枚举会超时。

考虑恰好只有 $i$ 对相邻的颜色相同的方格。

对于每一对颜色相同的格子 $t$ 和 $t+1$，将他们合并成一个格子，此时只剩下 $n-i$ 个格子。
### 选格子
对于 $n$ 个格子，在其中选一些合并成一个格子，最后剩下 $n-i$ 个格子，方案数为 $C_{n-i}^{i}$。
### 选颜色
对于 $n-i$ 个格子染上 $m$ 种颜色。第一个方格有 $m$ 种染色方式，剩下的方格只需要与前一个方格的颜色不同即可，方案数为 $m-1$。

换言之，染色方案共有：$m\times (m-1)^{n-i+1}$ 种。
### 最后
只需要将两种情况相乘，即为正好有 $i$ 种相邻且颜色相同的格子的方案数。

即：$ans_{i}=C_{n-i}^{i}\times m\times (m-1)^{n-i+1}$。

$ans=\sum\limits_{i=0}^{k}C_{n-i}^{i}\times m\times (m-1)^{n-i+1}$。

只需要用逆元就可以解决这道题啦！
# 参考代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e5+5;
const int mod=998244353;
int n,m,k;
int fac[MAXN];
int inv[MAXN];
int ans;
int ksm(int x,int y){
	int cnt=1;
	while(y){
		if(y%2)
			cnt=cnt*x%mod;
		x=x*x%mod;
		y=y/2;
	}
	return cnt;
}
void init(){
	fac[0]=fac[1]=1;
	inv[0]=inv[1]=1;
	for (int i=2;i<MAXN;i++){
		fac[i]=fac[i-1]*i%mod;
		inv[i]=inv[i-1]*ksm(i,mod-2)%mod;
	}
}
int C(int n,int m){
	if (n<m)
		return 0;
	if (n==m)
		return 1;
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
signed main(){
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	init();
	cin>>n>>m>>k;
	for (int i=0;i<=k;i++)
		ans=(ans+(m*ksm(m-1,n-i-1)%mod*C(n-1,i)))%mod;
	cout<<ans; 
}
```

---

