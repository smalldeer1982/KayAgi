# Pass

## 题目描述

# Pass


有 $N$ 个人排成一列。给定一个长度为 $N$ 的字符串 $S$，第 $i$ 个人手中的球的数量如下：

- 当 $S_i=0$ 时，这个人手中有两个红球；
- 当 $S_i=1$ 时，这个人手中有一个红球和一个蓝球；
- 当 $S_i=2$ 时，这个人手中有两个蓝球。

一开始，高桥君手中没有球，他要进行 $2N$ 次操作，每次操作如下：

- 如果有人手中有球，则所有人同时选择一个自己手中的球，将其交给前面的人（第一个人将球交给高桥君）；
- 高桥君将收到的球放到队列的末尾。

请计算出高桥君可以得到的所有队列的数量，答案对 $998244353$ 取模。

## 说明/提示

- $1\leq |S|\leq 2000$
- $S$ 仅包含数字 $0,1,2$。

注意：输入中不会给出 $N$，而是通过字符串 $S$ 的长度间接给出。

### 样例解释

可以将队列看作一个长度为 $2N$ 的字符串，第 $i$ 个字符表示第 $i$ 个人交给高桥君的球的颜色，红色用字母 `r` 表示，蓝色用字母 `b` 表示。例如，字符串 `rrbb` 表示高桥君先收到两个红球，然后收到两个蓝球。

对于样例 #1，可以构造出三个合法的队列：`rrbb`，`rbrb` 和 `rbbr`。

对于样例 #2 和样例 #3，可以使用动态规划的方法求解。

## 样例 #1

### 输入

```
02```

### 输出

```
3```

## 样例 #2

### 输入

```
1210```

### 输出

```
55```

## 样例 #3

### 输入

```
12001021211100201020```

### 输出

```
543589959```

# 题解

## 作者：WZY718605 (赞：6)


### 思路
先不考虑球的颜色，把一开始第 $i$ 个人手中的两个球都编号为 $i$ 按高桥君收到球的顺序写出一个长为 $2N$ 的数列。

这个数列具有一下性质：

- $1\sim n$ 中的每个数恰好在数列中出现了 $2$ 次（显然）。
- 第 $i$ 位上的数必须小于等于 $i$（因为每个球在一次操作中只能向前传递一位）。

且满足以上性质的数列一定是合法的。

再举一个最简单的例子，如果第一个人手里是两个蓝球，显然高桥君第一次不可能收到红球。因此在前 $i$ 次操作完成后，高桥君收到的的红球总数一定小于等于前 $i$ 个人手中红球的总数($i\le n$,蓝球同理)。

因此可以用 $f_{i,j} $ 表示前 $i+j$ 次操作中，共收到 $i$ 个红球和 $j$ 个蓝球的方案。若此状态合法则 $f_{i,j}\gets f_{i- 1,j}+ f_{i,j- 1}$，否则 $f_{i,j} \gets 0$。

时间复杂度为 $O(n^{2})$。

### 代码

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#define ll long long
#define il inline
using namespace std ;
const ll mod= 998244353 ;
const int N= 4005 ;
string s ;
int n, sl[N], sr[N] ;
ll f[N][N] ;
int main(){
	cin>> s ; n= s.size() ;
	for (int i= 1; i<= n; i++ ){
		sl[i]= sl[i- 1], sr[i]= sr[i- 1] ;
		if(s[i- 1]== '0') sl[i]+= 2 ;
		else if(s[i- 1]== '1') sl[i]++, sr[i]++ ;
		else sr[i]+= 2 ;
	}
	f[0][0]= 1 ;
	for (int i= 0; i<= sl[n]; i++ ){
		for (int j= 0; j<= sr[n]; j++ ){
			if(i+ j== 0) continue ;
			int k= i+ j ;
			if(k< n&& (i> sl[k]|| j> sr[k])) f[i][j]= 0 ;
			else{
				if(i) f[i][j]+= f[i- 1][j] ; if(j) f[i][j]+= f[i][j- 1] ;
				if(f[i][j]>= mod) f[i][j]-= mod ;
			}
		}
	}
	
	
	printf("%lld\n", f[sl[n]][sr[n]]) ;
	return 0 ;
}
```


---

## 作者：lhz123bc (赞：1)

本题考察大家动态规划，即 dp。

## 思路
1. **dp 数组的含义**：$dp[i][j]$ 表示前 $i+j$ 次操作中共收到 $i$ 个红球和 $j$ 个蓝球的方案。

2. **操作方法**：我们发现输入的字符串只有 $0$，$1$ 和 $2$，我们首先要预处理这个字符串，我们可以用数组 $l$ 与数组 $r$ 存一下红蓝球的个数。我们按高桥君收到球的顺序写出一个长为 $2 \times N$ 的数列，如果说在数列中，有某个状态满足两个条件：

	- 每个数恰好在数列中出现了 $2$ 次。

	- 第 $i$ 位上的数小于等于 $i$。

	那么就说明这个数列是**合法的**，则有：
    
    $$dp_{i,j} \gets dp_{i-1,j}+dp_{i,j} (i \ne 0)$$
    
    $$dp_{i,j} \gets dp_{i,j-1}+dp_{i,j} (j \ne 0)$$
    
   否则就有：
   
   $$dp_{i,j}=0$$
   
3. **初始化**：初始化是一个 dp 中必不可少的步骤。初始化很简单，让 $dp_{0,0}=1$ 即可。本题的时间复杂度为 $\mathcal{O}(n^2)$。

注意：**不开 long long 见祖宗**。

[AC Code](https://www.luogu.com.cn/paste/xnqcwn38)

---

## 作者：SuyctidohanQ (赞：0)

### 题目分析

这题......真的......有蓝题的水平？

一道经典的 DP。用 $dp_{i,j}$ 来表示前 $i + j$ 次操作中共收到 $i$ 个红球和 $j$ 个蓝球的方案。

若满足每个数恰好在数列中出现了 $2$ 次且第 $i$ 位上的数必须小于等于 $i$，那么 $dp_{{i - 1},j} + dp{_i,{j - 1}} \to dp_{i,j}$。否则 $dp_{i,j} \to 0$。

### 代码实现

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll MAXN = 4e3 + 10, mod = 998244353;
ll n, l[MAXN], r[MAXN], dp[MAXN][MAXN];
string s;
int main () {
	cin >> s;
	for (ll i = 1; i <= s.size() ; i ++) {
		l[i] = l[i - 1];
		r[i] = r[i - 1];
		if (s[i - 1] == '0') l[i] += 2;
		else if (s[i - 1] == '1') {
			l[i] ++;
			r[i] ++;
		}
		else r[i] += 2;
	}
	dp[0][0] = 1;
	for (ll i = 0; i <= l[n]; i ++) {
		for (ll j = 0; j <= r[n]; j ++) {
			if (i == 0 && j == 0) continue;
			if ((j > r[i + j] || i > l[i + j]) && (i + j) < n) dp[i][j] = 0;
			else {
				if (i) dp[i][j] += dp[i - 1][j];
				if (j) dp[i][j] += dp[i][j - 1];
				if (dp[i][j] >= mod) dp[i][j] -= mod;
			}
		}
	}
	cout << dp[l[n]][r[n]] << endl;
	return 0 ;
}
```

---

## 作者：Rose_Melody (赞：0)

## Solution-Pass

[题目传送门](https://www.luogu.com.cn/problem/AT_yahoo_procon2019_qual_f)

### 题目分析

在读入字符串时，先预处理出每个人具有的红色与蓝色的气球数，分别记为 $red_{i}$ 和 $blue_{i}$，用 $f_{i,j}$ 表示用 $i$ 个红球和 $j$ 个蓝球能组成的队伍方案数。

由于 $|S| \le 2000$，考虑时间复杂度 $O(n^{2})$ 的状态转移方程。

初始化 $f_{0,0}=1$，当 $i + j < n$ 时，若 $i > red_{i + j}$ 或 $j > blue_{i + j}$，方案不合法，我们就可以列出状态转移方程： 
$$f_{i,j} \gets f_{i-1,j} + f_{i,j}(i > 0),f_{i,j} \gets f_{i,j - 1} + f_{i,j}(j > 0)$$

### AC 代码


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 4e3 + 5 ;
const int Mod = 998244353 ;
int n , f[N][N] , b[N] , r[N] ;
string s ; 
inline int read(){
	int x = 0 , f = 1 ;
	char ch = getchar() ;
	while(ch < '0' || ch > '9'){
		if(ch == '-') f = -1 ;
		ch = getchar() ;
	}
	while('0' <= ch && ch <= '9'){
		x = (x << 1) + (x << 3) + (ch ^ 48) ; 
		ch = getchar(); 
	}
	return x * f ;
}
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> s ;
	n = s.size() ;
	s = ' ' + s ;//字符串下标从1开始
	for(int i = 1;i <= n;i ++){
		b[i] = b[i - 1] + (s[i] - '0');
		r[i] = r[i - 1] + 2 - (s[i] - '0') ;//预处理
	}
	f[0][0] = 1;
	for(int i = 0;i <= b[n];i ++){
		for(int j = 0;j <= r[n];j ++){
			if(! i && ! j) continue ;
			int cnt = i + j;
			if((i > b[cnt] || j > r[cnt]) && cnt < n) f[i][j] = 0;
			else{
				if( i ) f[i][j] += f[i - 1][j] ;
				if( j ) f[i][j] += f[i][j - 1] ;
			}//状态转移
			f[i][j] %= Mod ;
		}
	}
	cout << f[b[n]][r[n]] ;
	return 0;
} 
```

---

## 作者：Theresia (赞：0)

### 题目链接

[Pass](https://www.luogu.com.cn/problem/AT_yahoo_procon2019_qual_f)

### 思路

我们不妨设 $f_{i,j}$ 表示在前 $i+j$ 次接球中，一共接收了 $i$ 个红球和 $j$ 个蓝球的总方案数。

如何计算一个方案是否是合法的呢？

由于每一次只向前传一个球，所以在前 $i+j$ 轮最多收到的红球数量是前 $i+j$ 人拥有的红球数量，而不可能再多。

同理，在前 $i+j$ 轮最多收到的蓝球数量也是前 $i+j$ 人拥有的蓝球数量，这二者缺一不可。

所以，如果将这个最终的接球序列抽象为一个长为 $2n$ 的序列时（序列上的数代表这个球原主人的编号），我们就必须满足 $1 \sim n$ 中每个数在序列中出现两次，以及第 $k$ 位上的数小于等于 $k$。

在搞清楚了方案的合法性之后，写出状态转移方程便是不难的了。

对于合法的状态，我们有 $f_{i,j} = f_{i-1,j} + f_{i,j-1}$（对于 $i$ 或 $j$ 等于 $0$ 时要特判），而对于不合法方案有 $f_{i,j} = 0$。

可以看出，算法时间复杂度是 $\mathcal{O}(n^2)$ 的，可以通过本题。

### 参考代码

对于 $i$ 和 $j$ 为 $0$ 的情况进行了特判。

```cpp
/*
	Theresa
	It's just a burning memory.
*/
char c[5001];
int n,R[4001],B[4001];
long long f[4001][4001];
const long long M=998244353;
void Input()
{
	scanf("%s",c+1);n=strlen(c+1);
	f[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		if(c[i]=='0')
		R[i]=R[i-1]+2,B[i]=B[i-1];
		else if(c[i]=='1')
		R[i]=R[i-1]+1,B[i]=B[i-1]+1;
		else
		R[i]=R[i-1],B[i]=B[i-1]+2;
	}
	for(int i=1;i<=R[n];i++)
	f[i][0]=(i<n && i>R[i])?0:(f[i][0]+f[i-1][0])%M;
	for(int j=1;j<=B[n];j++)
	f[0][j]=(j<n && j>B[j])?0:(f[0][j]+f[0][j-1])%M;
	for(int i=1;i<=R[n];i++)
	{
		for(int j=1;j<=B[n];j++)
		f[i][j]=(i+j<n && (i>R[i+j] || j>B[i+j]))?0:(f[i][j]+f[i-1][j]+f[i][j-1])%M;
	}
	wr_endl(f[R[n]][B[n]]);
}
void Solve()
{
	// Hello
}
void Output()
{
	// Hello
}
int main()
{
	Input();
	Solve();
	Output();
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 前言：
竟然有如此水的蓝题。

## 思路：

这是一道非常经典的DP问题。

用 $dp[i][j]$ 来表示前 $i+j$ 次操作中共收到 $i$ 个红球和 $j$ 个蓝球的方案。

若此状态满足每个数恰好在数列中出现了 $2$ 次且第 $i$ 位上的数都必须小于等于 $i$。

则 $dp[i][j] \gets dp[i-1][j]+dp[i][j-1]$。

否则 $dp[i][j] \gets 0$。

## AC Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long N=4010;
long long n,l[N],r[N],dp[N][N],mod=998244353;
string s;
int main()
{
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> s;
	n=s.size();
	for(long long i=1;i<=n;i++)
	{
		l[i]=l[i-1];
		r[i]=r[i-1];
		if(s[i-1]=='0')
		{
			l[i]+=2;
		}
		else if(s[i-1]=='1')
		{
			l[i]++;
			r[i]++;
		}
		else
		{
			r[i]+=2;
		}
	}
	dp[0][0]=1;
	for(long long i=0;i<=l[n];i++)
	{
		for(long long j=0;j<=r[n];j++)
		{
			if(i+j==0)
			{
				continue;
			}
			long long k=i+j;
			if((j>r[k]||i>l[k]) && k<n)
			{
				dp[i][j]=0;
			}
			else{
				if(i)
				{
					dp[i][j]+=dp[i-1][j];
				}
				if(j)
				{
					dp[i][j]+=dp[i][j-1];
				}
				if(dp[i][j]>=mod)
				{
					dp[i][j]-=mod;
				}
			}
		}
	}
	cout << dp[l[n]][r[n]] << endl;
	return 0 ;
}
``````

---

## 作者：Nightsky_Stars (赞：0)

# 题目大意：

给定一个只有 $012$ 的数列，$0$ 表示这个人有两个红球，$1$ 表示这个人有一个红球和一个蓝球，$2$ 表示这个人有两个蓝球。然后进行 $2n$ 次操作，每个操作所有有球的人选择一个球递给前一个人，第一个人把球放到一个数列中。求一共有多少种数列。

# 思路：

考虑 dp，用 $dp[i][j]$ 来表示前 $i+j$ 次操作中共收到 $i$ 个红球和 $j$ 个蓝球的方案。

若此状态满足每个数恰好在数列中出现了 $2$ 次且第 $i$ 位上的数必须小于等于 $i$。

则 $dp[i][j] \gets dp[i-1][j]+dp[i][j-1]$。

否则 $dp[i][j] \gets 0$。

# CODE:

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,l[4010],r[4010],dp[4010][4010],mod=998244353;
string s;
int main(){
	cin>>s;
	n=s.size();
	for(ll i=1;i<=n;i++){
		l[i]=l[i-1];
		r[i]=r[i-1];
		if(s[i-1]=='0') l[i]+=2;
		else if(s[i-1]=='1'){
			l[i]++;
			r[i]++;
		}
		else r[i]+=2;
	}
	dp[0][0]=1;
	for(ll i=0;i<=l[n];i++){
		for(ll j=0;j<=r[n];j++){
			if(i+j==0) continue;
			ll k=i+j;
			if((j>r[k]||i>l[k])&&k<n) dp[i][j]=0;
			else{
				if(i) dp[i][j]+=dp[i-1][j];
				if(j) dp[i][j]+=dp[i][j-1];
				if(dp[i][j]>=mod) dp[i][j]-=mod;
			}
		}
	}
	cout<<dp[l[n]][r[n]]<<"\n";
	return 0 ;
}
```

---

## 作者：封禁用户 (赞：0)

题意：

　　给定一个只包含 $012$ 序列，$0$ 表示这个人有 $2$ 个红球，$1$ 表示一个红球一个蓝球，$2$ 表示两个蓝球。进行 $2n$ 次游戏，每次游戏所有有球的人选择一个球递给前一个人，第一个人把球放到一个序列中，$'r'$ 表示红球，$'b' $ 表示蓝球，问一共多少种序列。

分析：

　　一定要满足前 $i$ 个人的所有红球 $\geq$ 序列前 $i$ 个位置的红球，蓝球同理，然后 ```dp```。

　　$f[i][j]$ 表示到第 $i$ 个位置，有 $j$ 个红球的方案数。
```
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cmath>
#include<cctype>
#include<set>
#include<queue>
#include<vector>
#include<map>
using namespace std;
typedef long long LL;

inline int read() {
    int x=0,f=1;char ch=getchar();for(;!isdigit(ch);ch=getchar())if(ch=='-')f=-1;
    for(;isdigit(ch);ch=getchar())x=x*10+ch-'0';return x*f;
}

const int N = 4005, mod = 998244353;
int sum[N][2], f[N][N];
char s[N];

inline void add(int &x,int y) {
    x += y; x = x >= mod ? x - mod : x;
}

int main() {
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    for (int i = 1; i <= n; ++i) {
        if (s[i] == '0') sum[i][0] += 2;
        else if (s[i] == '1') sum[i][0] ++, sum[i][1] ++;
        else sum[i][1] += 2;
        sum[i][0] += sum[i - 1][0], sum[i][1] += sum[i - 1][1];
    }

    if (sum[1][0] >= 1) f[1][1] = 1;
    if (sum[1][1] >= 1) f[1][0] = 1;
    
    for (int i = 2; i <= (n << 1); ++i) {
        for (int j = 0; j <= i; ++j) {
            int r = j, b = i - j;
            if (r > sum[min(i, n)][0] || b > sum[min(i, n)][1]) continue;;
            add(f[i][j], f[i - 1][j]);
            if (j) add(f[i][j], f[i - 1][j - 1]);
        }
    }
    cout << f[n + n][sum[n][0]];
    return 0;
}
```


---

