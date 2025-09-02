# The Maths Lecture

## 题目描述

Amr doesn't like Maths as he finds it really boring, so he usually sleeps in Maths lectures. But one day the teacher suspected that Amr is sleeping and asked him a question to make sure he wasn't.

First he gave Amr two positive integers $ n $ and $ k $ . Then he asked Amr, how many integer numbers $ x&gt;0 $ exist such that:

- Decimal representation of $ x $ (without leading zeroes) consists of exactly $ n $ digits;
- There exists some integer $ y&gt;0 $ such that: 
  - ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF507D/a168a0f3214943d3090a4c18ee0075fe3a3849dd.png);
  - decimal representation of $ y $ is a suffix of decimal representation of $ x $ .

As the answer to this question may be pretty huge the teacher asked Amr to output only its remainder modulo a number $ m $ .

Can you help Amr escape this embarrassing situation?

## 说明/提示

A suffix of a string $ S $ is a non-empty string that can be obtained by removing some number (possibly, zero) of first characters from $ S $ .

## 样例 #1

### 输入

```
1 2 1000
```

### 输出

```
4```

## 样例 #2

### 输入

```
2 2 1000
```

### 输出

```
45```

## 样例 #3

### 输入

```
5 3 1103
```

### 输出

```
590```

# 题解

## 作者：djh123 (赞：5)

### 题目大意

>输入 **n**，**k**，**m** ，问有多少个 **n** 位数（不含前导0）存在后缀是k的倍数（0不算），并将总数对 **m** 取余。

>$1 \leq n \leq 1000~,~ 1\leq k \leq 100 ~,~ 1\leq m \leq 10 ^ 9.$

这道题一看就是个数位dp，
只不过要从后向前dp啦。

令 $dp[i][j][1]$ 表示第 $i$ 位，当前数 $mod~~k$ 为 $j$ , 后缀中存在 $k$ 的倍数的个数。

$dp[i][j][0]$ 表示第 $i$ 位，当前数 $mod~~k$ 为 $j$ , 后缀中没有 $k$ 的倍数的个数。

因为不存在前导零，所以在 $i == n$ 的时候要从 1 开始循环。

如果前面加了一个 $x$ 得到的余数为 $j$ ， 如果 $j == 0$ && $i~~!= 0$时 可以归到 $dp[i][x][1]$ 中，否则就在 $dp[i][j][0]$ 中。

代码实现
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <string>
#include <cmath>
#include <set>

#define debug(x) cout << #x << " " << x << endl;
#define rep(x, y, z) for(int x = (y) ; x <= (z) ; ++x)
#define per(x, y, z) for(int x = (y) ; x >= (z) ; --x)
#define ll long long

using namespace std;

inline int read (){
	int a = 0, w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if(c == '-') w = -1;
		c = getchar();
    }
    while (c >='0' && c <= '9'){
    	a = (a << 1) + (a << 3) + (c ^ 48);
    	c = getchar();
	}
	return a * w;
}

inline ll readll (){
	ll a = 0, w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if(c == '-') w = -1;
		c = getchar();
    }
    while (c >='0' && c <= '9'){
    	a = (a << 1) + (a << 3) + (c ^ 48);
    	c = getchar();
	}
	return a * w;
}

int dp[1005][105][2];
int n_10[1005];
int main (){
	int n, k, m;
	n = read(), k = read(), m = read();
	memset (dp, 0, sizeof dp);
	n_10[0] = 1;
	rep(i, 1, n) {
		n_10[i] = (n_10[i - 1] * 10) % k;
	}//预处理每位权值。
	dp[0][0][0] = 1;
	rep(i, 0, n - 1) {
		rep(j, 0, k - 1) {
			rep(l, (i == n - 1) ? 1 : 0, 9) {
				int now = (j + n_10[i] * l) % k;
				if(l && now == 0) {//如果l == 0， 那么只能归到dp[i + 1][now][0]里。
					dp[i + 1][now][1] = (dp[i + 1][now][1] + dp[i][j][0]) % m;
				}
				else {
					dp[i + 1][now][0] = (dp[i + 1][now][0] + dp[i][j][0]) % m;
				}
				dp[i + 1][now][1] = (dp[i + 1][now][1] + dp[i][j][1]) % m;//无论 now == 0 或者 now != 0， 都可以从dp[i][j][1]，转移过来。
			}
		}
	}
	int ans = 0;
	rep(i, 0, k - 1) {
		ans = (ans + dp[n][i][1]) % m;
	}//累加答案
	cout << ans % m << endl;
	return 0;
}


```

---

## 作者：gesong (赞：2)

题目传送门：[CF507D](https://www.luogu.com.cn/problem/CF507D)。

# 思路
可以容易发现这题就是**数位 dp** 的模板题。

由于是跟后缀有关系，因此我们要先把所有的数反转，以个位开头，以此类推。

设 $f_{i,x,1/0,1/0}$ 表示现在在填第 $i$ 位（如果 $i=0$ 说明已经填完），目前这个数与 $k$ 取模的值为 $x$，目前是否有后缀满足条件，是否有前导零的数的个数。

考虑转移，首先判断 $x$ 是否为 $0$，如果是，说明以后的所有数都是满足题目条件的，我们将其记录转移中，然后枚举第 $i$ 应该填什么数，更新 $x$ 和是否有前导零的个数。

在这里推荐数位 dp 使用记忆化搜索来写，具体的细节请看代码。
# 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,mod;
const int N=1010,M=110;
int f[N][M][2][2];
int dfs(int i,int x,int flag,int zero,int xxx){
	if (i!=n&&x==0&&!zero) flag=1;
	if (i==0){
		return flag;
	}
	if (~f[i][x][flag][zero]) return f[i][x][flag][zero];
	int ans=0;
	if (i==1){
		for (int j=1;j<=9;j++) ans+=dfs(i-1,(x+j*xxx%k)%k,flag,0,xxx*10%k),ans%=mod;	
	}
	else{
		for (int j=0;j<=9;j++) ans+=dfs(i-1,(x+j*xxx%k)%k,flag,zero&&(j==0),xxx*10%k),ans%=mod;
	}
	return f[i][x][flag][zero]=ans;
}
inline int read(){
	char c=getchar();
	int f=1,ans=0;
	while(c<48||c>57) f=(c==45?f=-1:1),c=getchar();
	while(c>=48&&c<=57) ans=(ans<<1)+(ans<<3)+(c^48),c=getchar();
	return ans*f;
}
main(){
	n=read(),k=read(),mod=read();
	memset(f,-1,sizeof(f));
	cout <<dfs(n,0,0,1,1);
    return 0;
}


```

---

## 作者：FutaRimeWoawaSete (赞：2)

搞笑啊，教练都说了数位dp的题用容斥容了半天结果发现容爆了/ll。    

发现这个后缀不好搞，所以干脆倒着 dp。            

令 $dp_{i,j,0/1,0/1}$ 表示后 $i$ 位和模 $m$ 为 $j$ 是/否有满足条件的后缀且是/否全为 $0$。          

然后直接从后向前枚举数位即可，递归出口的答案是是否有满足条件的后缀。    
```cpp
#include "bits/stdc++.h"
using namespace std;
#define int long long 
const int Len = 1005;
int n,m,mod,dp[Len][105][2][2],ml[Len];
int dfs(int len,int sum,int opt,int z,bool up)
{
	if(len == n) return opt;
	if(!up && dp[len][sum][opt][z] != -1) return dp[len][sum][opt][z];
	int res = 0;
	for(int i = 0 ; i <= 9 ; i ++)
	{
		if(!i && len == n - 1) continue;
		if(!i) res += dfs(len + 1 , (sum + i * ml[len] % m) % m , opt | (z && (sum + i * ml[len] % m) % m == 0) , z , 0);
		else res += dfs(len + 1 , (sum + i * ml[len] % m) % m , opt | ((sum + i * ml[len] % m) % m == 0) , 1 , 0);
		res %= mod;
	}  
	if(!up) return dp[len][sum][opt][z] = res;
	return res;
}
signed main()
{
	memset(dp , -1 , sizeof dp);
	scanf("%lld %lld %lld",&n,&m,&mod);ml[0] = 1;
	for(int i = 1 ; i <= n ; i ++) ml[i] = ml[i - 1] * 10 % m;
	printf("%lld\n",dfs(0 , 0 , 0 , 0 , 0));
	return 0;
}
```

---

## 作者：_Wind_Leaves_ShaDow_ (赞：1)

水题。注意 $0$ 不算做后缀。

由于和后缀有关考虑从后往前数位 dp，即先考虑最后一位。

如果此时的后缀已经合法前面的数想怎么填都可以，注意不能有前导零所以第一位只有 $9$ 种填法。

真的是纯板子吧。具体细节什么的看代码就好了。

```cpp
#include <bits/stdc++.h>
//#define lint __int128
#define int long long
#define fi first
#define se second
#define pb push_back
#define vec vector
#define Il inline
#define Rg register
#define Ri Rg int
#define IT ::iterator
#define p_que priority_queue

using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> pii;
const int N=1000;
const db eps=1e-9,pi=acos(-1.0);

Il int qpow(int x,int y,int mod){int ret=1;for(;y;y>>=1,x=x*x%mod)if(y&1)ret=ret*x%mod;return ret;}

int n,K,mod,vis[N+5][105][2],pw[N+5];

Il int dfs(int p,int yu,bool ze){//当前填完了哪一位，后缀余数是多少，后缀是否为 0
	if(vis[p][yu][ze]>=0)return vis[p][yu][ze];
	if(p==1)return (!yu&&!ze);int ret=0;
	if(!yu&&!ze)return vis[p][yu][ze]=qpow(10,p-2,mod)*9%mod;//计算前面有多少种填法，算是一个优化？
	for(Ri i=0;i<=9;i++)ret=(ret+dfs(p-1,(i*pw[n-p+1]+yu)%K,ze&&!i))%mod;//从后往前时新填的数要乘上对应的十的幂次
	return vis[p][yu][ze]=ret;
}

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>K>>mod;pw[0]=1;for(Ri i=1;i<=n;i++)pw[i]=pw[i-1]*10%K;
	for(Ri i=1;i<=n+1;i++)for(Ri j=0;j<K;j++)vis[i][j][0]=vis[i][j][1]=-1;
	int ans=dfs(n,0,1);for(Ri i=1;i<=9;i++)ans=(ans+dfs(n,i%K,0))%mod;
	cout<<ans;
	return 0;
}
```

---

## 作者：wangyibo201026 (赞：1)

## solution

首先你注意到这是一道数位 DP，于是我果断退出了此页面。

等等，似乎没有最大数限制？！于是我又回来了。

那么我们还是想想这题怎么做。

设 $f_{i, j}$ 为从低位往高位数到第 $i$ 位且当前数模 $k$ 等于 $j$ 的方案数，于是我们不难列出 DP 转移式：

$$f_{i, ( j + l \times 10^{i - 1} )} = \sum_{0 \le j \le k - 1, 0 \le l \le 9} f_{i - 1, j}$$

于是你果断测了一发，发现 WA #1 了，经过调试你注意到有前导 $0$，其实也很好处理，你对于前 $n - 1$ 位跑这个 DP，然后第 $n$ 位强制钦定不选 $0$ 就好了。

于是你又测了一发，发现 WA #3 了，你苦思冥想良久，发现题目是要要求只要**至少**一个后缀模 $k$ 等于 $0$，而你这个 DP 记得是模 $k$ 等于 $0$ 的 $n$ 位数个数，于是果断更改状态。

记 $f_{i, j, 0/1}$ 为填到第 $i$ 位，目前的数模 $k$ 等于 $j$，是否已经有后缀模 $k$ 等于 $0$，不难发现这也是好转移的，你就特判一下就好了。

但是你发现你又 WA #3，这次是真的调了好久，于是你仔细读题，发现是不允许有 $0$ 的，于是你就在 $l = 0$ 时不做一种转移就行了。

## code

代码？冒得。

---

## 作者：Strelitzia (赞：1)

[题目床送门](https://www.luogu.com.cn/problem/CF507D)

---

啊呀，一道不难的数位 $\text{dp}$ 吧。

我们定义 $dp_{i,j,0/1}$ 表示算到了第 $\operatorname i$ 位，现在的模 $\operatorname k$ 的值是 $\operatorname j$，前面有没有合法，也就是后缀和是模 $\operatorname k$ 为 $\text{0}$。

然后要倒着搜，为了是第 $\operatorname n$ 位有值，判一下就好了。

```cpp
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
using namespace std;

//Two kinds of QuickRead and QuickPrint

char buf[1 << 23],*p1 = buf,*p2 = buf,obuf[1 << 23],*O = obuf;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1 ++)
template<typename T>void read(T &x) {
	x = 0;T f = 1;char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -1;ch = getchar();}
	while (isdigit(ch)) {x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
	x *= f;
}
int read() {
	int x = 0, f = 1;char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -1;ch = getchar();}
	while (isdigit(ch)) {x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
	return x *= f;
}
template<typename T>void print(T x) {
	if (x < 0) putchar('-'),x = -x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

//something useful

template<typename T>void Swap(T &x,T &y) {T z = x;x = y;y = z;}
template<typename T>T Min(T x,T y) {return x < y ? x : y;}
template<typename T>T Max(T x,T y) {return x > y ? x : y;}
template<typename T>T Abs(T x) {return x < 0 ? -x : x;}

int n,k,m;

int f[1005][105][2],fac[1005];

int dfs(int len,int sum,bool app) {
	if (len == n + 1) return app;
	if (~f[len][sum][app]) return f[len][sum][app];
	int maxdig = len == n ? 1 : 0;
	int res = 0;
	for (int i = maxdig ; i <= 9 ; ++ i)
		res = (res + dfs(len + 1,(sum + i * fac[len]) % k,app || ((sum + i * fac[len]) % k == 0 && (sum || i)))) % m;
	return f[len][sum][app] = res;
}

int main () {
	memset(f,-1,sizeof f);
	read(n);read(k);read(m);
	fac[1] = 1;
	for (int i = 2 ; i <= n ; ++ i) fac[i] = fac[i - 1] * 10 % k;
	print(dfs(1,0,0));
	return 0;
}
```

---

## 作者：SpXace (赞：1)

>dp[i][j][t]表示到第i位，当前%k为j的数，t == 0,即为不能被k整除，t == 1即为能被k整除

>	接下来考虑转移方程:

>如果当前的数不能被k整除，则只能由原状态中不能被k整除的状态转移过来。
    
>如果当前能被k整除,则当前状态由原状态中不能被k整除，但加入当前枚举出来的数，可以被k整除的情况，这是其一

	注意！！！无论当前装态中已经能被k整除，都要有

	dp[i+1][now][1] = (dp[i+1][now][1] + dp[i][j][1]) % Mod;

>因为如果当前能被k整除，要加上原状态整除的情况；而如果不能整除，也要顺过来，不然dp数组会出现断层

```
#include<iostream>
#include<cstring>
#include<cstdio>
#define LL long long
using namespace std;
inline int Read()
{
    int s = 0,w = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9'){
        if(ch == '-') w = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
        s = (s << 3)+(s << 1) + ch - '0',ch = getchar();
    return w * s;
}
LL dp[1010][105][2],N,Mod,M;
int main()
{
    N = Read(),M = Read(),Mod = Read();
//	memset(dp,0,sizeof(dp));,
    dp[0][0][0] = 1;
    LL ten = 1;
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < M; ++j)
            for(int k = 0; k < 10; ++k) {
                if(i == N - 1 && k == 0) continue;
                int now = (k * ten + j) % M;
                dp[i+1][now][1] = (dp[i+1][now][1] + dp[i][j][1]) % Mod;
                if(now == 0 && k)
                    dp[i+1][now][1] = (dp[i+1][now][1] + dp[i][j][0]) % Mod;
                else
                    dp[i+1][now][0] = (dp[i+1][now][0] + dp[i][j][0]) % Mod;
                
            } 
        ten = (ten*10)%M;
    }
    LL Ans = 0;
    for(int i = 0; i < M; ++i) {
        Ans += dp[N][i][1]%Mod;
    }
    cout << Ans%Mod;
    return 0;
}
```

---

## 作者：tony0530 (赞：0)

## solution

------

#### 题目
 

[传送门](https://www.luogu.com.cn/problem/CF507D)

------

#### 算法

考虑数位 DP。

定义 $f_{i,j,0/1}$ 为考虑到从后往前的第 $i$ 位，当前的数 $ \bmod \;k = j$，后缀中存在/不存在 $k$ 的倍数的个数。

**注意**当 $i=n$ 时改成从 $1$ 开始。

-----

#### 代码

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 1010;
const int M = 110;
const int K = 2;

int n, k, m;
int qmi_[N];
int f[N][M][K];

signed main()
{
    cin >> n >> k >> m;
    memset(f, 0, sizeof f);
    qmi_[0] = 1;
    for(int i = 1 ; i <= n ; i ++ ) qmi_[i] = (qmi_[i - 1] * 10) % k;
    
    f[0][0][0] = 1;
    
    for(int i = 0 ; i < n ; i ++ )
        for(int j = 0 ; j < k ; j ++ )
            for(int l = (i == n - 1 ? 1 : 0) ; l <= 9 ; l ++ )
            {
                int now = (j + qmi_[i] * l) % k;
                if(l && now == 0) f[i + 1][now][1] = (f[i + 1][now][1] + f[i][j][0]) % m;
                else f[i + 1][now][0] = (f[i + 1][now][0] + f[i][j][0]) % m;
                f[i + 1][now][1] = (f[i + 1][now][1] + f[i][j][1]) % m;
            }
    int ans = 0;
    for(int i = 0 ; i < k ; i ++ ) ans = (ans + f[n][i][1]) % m;
    cout << ans % m;
    return 0;
}
```

---

## 作者：lfxxx (赞：0)

直接从后往前 dp，考虑设计状态 $dp_{i,j,f_1,f_2}$ 表示考虑后缀 $[i,n]$，当前后缀模 $k$ 为 $j$，是否已经有后缀模 $k$ 为 $0$，是否在填了的后缀中放了非 $0$ 数，然后转移就直接枚举当前这一位放了哪个数，再枚举上一个状态的 $f_1,f_2$，并判断能否通过当前的 $j$ 或者填的数更新当前的 $f_1,f_2$，时间复杂度为 $O(n \times k)$，为了方便，这里写的记忆化搜索。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
const int maxn = 1e3+114;
const int maxk = 114;
int dp[maxn][maxk][2][2];
int vis[maxn][maxk][2][2];
int n,k,m;
int _pow[maxn];
int dfs(int i,int j,int f1,int f2){
	if(vis[i][j][f1][f2]!=0) return dp[i][j][f1][f2];
	vis[i][j][f1][f2]=1;
	if(i==n+1){
		return (dp[i][j][f1][f2]=(j==0&&f1==0&&f2==0));
	}
	for(int d=0;d<10;d++){
		if(i==1&&d==0) continue;
		int lstj=(j+k-_pow[n-i]*d%k)%k;
		for(int lstf1=0;lstf1<=f1;lstf1++){
			for(int lstf2=0;lstf2<=f2;lstf2++){
				if(lstf1!=f1&&(j%k!=0||f2==0)) continue;
				if(lstf2!=f2&&d==0) continue;
				if(f1==0&&j%k==0&&f2==1) continue;
				if(f2==0&&d!=0) continue;
				dp[i][j][f1][f2]=(dp[i][j][f1][f2]+dfs(i+1,lstj,lstf1,lstf2))%m;
			}
		}
	}
	return dp[i][j][f1][f2];
}
//dp[i][j][k] 考虑 [i,n] 后缀，模 k 余 j 是否已经存在后缀满足模 k 余 0 后缀是否存在非 0 数 
signed main(){
	cin>>n>>k>>m;
	_pow[0]=1;
	for(int i=1;i<=n;i++) _pow[i]=_pow[i-1]*10%k;
	int ans=0;
	for(int j=0;j<k;j++) ans=(ans+dfs(1,j,1,1))%m;
	cout<<ans<<'\n';
	return 0;
}
```

---

