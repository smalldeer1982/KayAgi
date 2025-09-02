# [ABC336E] Digit Sum Divisible

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc336/tasks/abc336_e

正整数 $ n $ の **桁和** を、$ n $ を $ 10 $ 進法で表したときの各桁の和として定義します。例えば $ 2024 $ の桁和は $ 2+0+2+4=8 $ です。  
 正整数 $ n $ が $ n $ の桁和で割り切れる時、$ n $ を **良い整数** と呼びます。例えば $ 2024 $ はその桁和である $ 8 $ で割り切れるので良い整数です。  
 正整数 $ N $ が与えられます。$ N $ 以下の良い整数は全部で何個ありますか？

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^{14} $
- $ N $ は整数
 
### Sample Explanation 1

$ 20 $ 以下の良い整数は $ 1,2,3,4,5,6,7,8,9,10,12,18,20 $ の $ 13 $ 個です。

## 样例 #1

### 输入

```
20```

### 输出

```
13```

## 样例 #2

### 输入

```
2024```

### 输出

```
409```

## 样例 #3

### 输入

```
9876543210```

### 输出

```
547452239```

# 题解

## 作者：int_R (赞：7)

如果是求能被一个固定的数 $x$ 整除的数的个数的话是容易的，问题在于现在 $x$ 不确定。

那直接枚举 $x$，记 $f_{pos,s,sum,limit}$ 为考虑到第 $pos$ 位，剩下还可以使用的数字和为 $s$，当前数字和模 $x$ 为 $sum$，是否有最高位限制。

转移显然。边界是当 $pos=0$ 时返回 $[s=0]\wedge [ sum=0]$，即只有恰好数位和为 $x$ 并且被整除了才有贡献。答案是 $\sum\limits_{x=1}^{14\times 9} f_{tot,x,0,1}$。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<string.h>
#define int long long
using namespace std;
int n,a[20],tot,f[20][150][150][2],cur,ANS;
int dfs(int pos,int s,int sum,bool limit)
{
    if(s<0) return 0;if(!pos) return !s&&!sum;
    if(f[pos][s][sum][limit]!=-1) return f[pos][s][sum][limit];
    int ans=0;
    for(int i=0;i<=(limit?a[pos]:9);++i)
        ans+=dfs(pos-1,s-i,(sum*10+i)%cur,limit&&i==a[pos]);
    return f[pos][s][sum][limit]=ans;
}
signed main()
{
#ifdef ONLINE_JUDGE
    cin.tie(0),cout.tie(0);
    ios::sync_with_stdio(0);
#endif
    cin>>n;while(n) a[++tot]=n%10,n/=10;
    for(int i=1;i<=14*9;++i)
    {
        memset(f,-1,sizeof(f));
        ANS+=dfs(tot,cur=i,0,1);
    }
    cout<<ANS<<'\n';return 0;
}
```

---

## 作者：2huk (赞：3)

数位 DP。

可以发现数位和最大为 $9 \times 14 = 126$（每一位都填 $9$，填 $14$ 位）。因此我们先枚举数位和 $m$。

设状态 $f_{i, j, k, l}$，其中：

- $i$：搜到了第 $i$ 位（倒着枚举，也就是指 $i$ 到最高位都填完了）。
- $j$：是否 $i$ 前面的位（包括 $i$）都填满了。这里的填满指填的与原数 $n$ 相同。例如 $114514$ 就是在 $n = 119198$ 时第五到最高位的填满。
- $k$：**$i$ 前面的位从左往右拼成的十进制数**模**数位和**为 $k$。例如 $114514$ 的第四到最后一位组成的十进制数为 $114$。
- $l$：$i$ 前面的数位和为 $l$。例如 $114514$ 的第四到最后一位的数位和为 $11$。

转移是这样的：

- $f_{i, 0, k, l} = \sum\limits_{t = 0}^9 f_{i - 1, 0, (10k + t) \bmod m, l + t}$。表示枚举第 $i$ 位填的数为 $t$。那么因为前面存在某一位没填满，那么后面的位  $0 \sim 9$ 都是可以填的。因此 $t$ 的范围为 $[0, 9]$。
- $f_{i, 1, k, l} = \sum\limits_{t = 0}^pf_{i - 1, [t = p], (10k + t) \bmod m, l + t}$，其中 $p$ 表示给定的 $n$ 的第 $i$ 位，$[t = p]$ 表示 $t$ 是否等于 $p$（真为 $1$，假为 $0$）。表示枚举的第 $i$ 位为 $t$。那么因为前面每一位都填满了，那么这一位肯定不能超过 $n$ 原来的这一位，所以枚举到 $p$。

令 $c$ 表示 $n$ 的位数。那么答案为 $f_{c, 1, 0, 0}$。

边界显然 $f_{0, 0, 0, m} = f_{0, 1, 0, m} = 1$，其余 $i = 0$ 的 $f_{i, j, k, l} = 0$。

[代码](https://atcoder.jp/contests/abc336/submissions/49348352)。

---

## 作者：xz001 (赞：3)

首先数位和只有不到 $140$ 种情况，所以可以枚举数位和。因为是数字统计问题，所以考虑数位 dp。

我采用记忆化搜索的形式，设 $n$ 表示数位长度，设立 $f_{i,j,k,l}$ 表示搜到第 $i$ 位，$j$ 表示前 $n-i$ 位填的数字是否均为最高位（$j$ 为 $0$ 为非最高位，$j$ 为 $1$ 为最高位），数字前 $n-i$ 位从左到右拼成的十进制数模数位和为 $k$，数位前 $n-i$ 位和为 $l$ 的情况下的答案数，设 $p$ 为这一位可以用的最大数字，$m$ 为数位和，$t$ 表示当前这一位填的数字，当 $j=1$ 时，转移为：

$$
f_{i,j,k,l}=\left(\sum_{t=0}^{p-1}f_{i-1,0,(k\times 10+t) \bmod m,l+t}\right)+f_{i-1,1,(k\times 10+p)\bmod m,l+p}
$$

当 $j=0$ 时，转移为：

$$
f_{i,j,k,l}=\sum_{t=0}^{p}f_{i-1,0,(k\times 10+t) \bmod m,l+t}
$$

代码如下：

```cpp
/*
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3, "Ofast", "inline")
*/
#include<bits/stdc++.h>

using namespace std;

#define re			register
#define int			long long
#define fi			first
#define se			second
#define swap(a, b) 	a ^= b, b ^= a, a ^= b
#define pb 			push_back
#define all(x)		x.begin(), x.end()
#define max(a, b)	(a > b ? a : b)
#define min(a, b)	(a < b ? a : b)
#define il			inline
#define abs(x)		((x ^ (x >> 63)) - (x >> 63))

typedef pair<int, int> PII;

const int N = 1e6 + 10;
const int M = 1e6 + 10;
const int INF = 1e18, P = 998244353;
const double eps = 1e-6;

il int  read() { re int x = 0; re bool f = true; re char c = getchar(); while (c < 48 || c > 57) { if (c == '-') f = false; c = getchar(); } while (c >= 48 && c <= 57) x = (x << 3) + (x << 1) + c - 48, c = getchar(); return f ? x : -x; }
il void write(int x) { if (x < 0) putchar('-'), x = -x; if (x > 9) write(x / 10); putchar(x % 10 + 48); }
il void wel(int x) { write(x), putchar('\n'); }
il void wsp(int x) { write(x), putchar(' '); }

int n, a[N], cnt, f[21][2][141][141], mod, ans;

int dfs (int i, int j, int k, int l) {  
	if (i < 1) return (!k) && (l == mod);  //这个 mod 表示题解中的 m
    if (f[i][j][k][l] != -1) return f[i][j][k][l];
    int p = (j ? a[i] : 9), ans = 0;
    for (int t = 0; t <= p; ++ t) {
    	ans += dfs (i - 1, j & (t == p), (k * 10 + t) % mod, l + t);
	}
	return f[i][j][k][l] = ans;
}

signed main() {
    scanf("%lld", &n);
    while (n) {
    	a[ ++ cnt] = n % 10; //这个 cnt 表示题解中的 n
    	n /= 10;
	}
	for (int i = 1; i <= 140; ++ i) {
		mod = i;
		memset(f, -1, sizeof(f));
		ans += dfs (cnt, 1, 0, 0);
	} 
	printf("%lld\n", ans);
    return 0;
}


```

---

## 作者：mengleo (赞：2)

# AT_abc336_e [ABC336E] Digit Sum Divisible 题解

# 思路

题意很明了，这里就不再解读了。

看到数据范围 $N \leq 10^{14}$ 暴力肯定 TLE，很典型的数位 DP。但是直接 DP 很难转移，我们就要考虑枚举一个未知的值（也就相当于把他确定下来再进行 DP），我选择循环枚举位数和，下界肯定是 $1$，上界是 $9 \times |n|$，$|n|$ 表示 $n$ 的十进制位数。然后就是数位 DP 的板子了。

# Code
```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

int n, b, dp[25][205][205], num[105];

int dfs(int len, int sum, int mod, bool lim, int h)// 5个参数，len表示还有多少位没确定，sum表示目前为止的数字和，mod表示目前凑出的这个数字mod sum得到的结果，lim表示前面是不是和n一样，这会影响这一位的上界，h表示给定的数字和。
{
    if(!len && !sum)// 如果是0
    {
        return 0;
    }
    else if(!len)
    {
        return (mod == 0) && (sum == h);// 如果这个数构造完了，就判断它能不能整除sum，还要满足sum与给定的位数和相等
    }
    if(!lim && dp[len][sum][mod] != -1)
    {
        return dp[len][sum][mod];// 记忆化
    }
    int ans = 0;
    int up;
    if(lim)
    {
        up = num[len];
    }
    else
    {
        up = 9;
    }// 上限
    for(int i = 0; i <= up; i++)
    {
        ans += dfs(len - 1, sum + i, (10 * mod + i) % h, lim && (i == up), h);// 进入下一层
    }
    if(!lim)
    {
        dp[len][sum][mod] = ans;// 记忆化
    }
    return ans;
}

int f(int x)
{
    int len = 0, ans = 0;
    while(x)
    {
        len++;
        num[len] = x % 10;
        x /= 10;// 拆除x的各个位
    }
    for(int i = 1; i <= 9 * len; i++)
    {
        memset(dp, -1, sizeof(dp));
        ans += dfs(len, 0, 0, 1, i);
        // 枚举位数和，注意每次都要memset
    }
    return ans;
}

signed main()
{
    cin >> n;
    cout << f(n);

    return 0;
}
```

---

## 作者：aaron0919 (赞：1)

# [AT_abc336_e の题解](https://www.luogu.com.cn/problem/AT_abc336_e)

### 题目大意

求小于 $n$ 的正整数有多少个能被其数字和整除.

### 理性分析

一眼数位 DP，但是我们可以发现，最多是 $14$ 位数，那么数字和最大为 $14\times9=126$，那我们就可以枚举数字和来搜索。

不会时超吗，看一下时限，$10$ 秒！！随便打。。。

我们可以用 $dp_{len, sum, sta}$ 表示当前搜索到长为 $len$，数字和为 $sum$，当前的数模 $mod$ 的余数为 $sta$。

搜索时可以适当剪枝。那么 $mod$ 是什么，就是题目中的数字和。

### 代码实现

[AC 记录](https://atcoder.jp/contests/abc336/submissions/49315142)

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll dp[21][201][201], n, len, ans;
int num[21], mod;

ll dfs(int len, int sum, int sta, bool bj)
{
    if (len == 0)
    {
        return sum == mod && sta == 0;
    }
    if (dp[len][sum][sta] != -1 && !bj)
    {
        return dp[len][sum][sta];
    }
    int maxx = bj ? num[len] : 9;
    ll ret = 0;
    for (int i = 0; i <= maxx; i++)
    {
        if (i + sum > mod)
        {
            break;
        }
        ret += dfs(len - 1, sum + i, (sta * 10 + i) % mod, bj && i == maxx);
    }
    return bj ? ret : dp[len][sum][sta] = ret;
}

int main()
{
    scanf("%lld", &n);
    while (n)
    {
        num[++len] = n % 10, n /= 10;
    }
    for (int i = 1; i <= 9 * len; i++)
    {
        memset(dp, -1, sizeof(dp));
        mod = i, ans += dfs(len, 0, 0, 1);
    }
    printf("%lld", ans);
}
```


---

## 作者：Elairin176 (赞：1)

[传送门](https://www.luogu.com.cn/problem/AT_abc336_e)    
简单题。   
## 题意
求出 $l$ 到 $r$ 中有多少个数被其数位和整除。    
## 解法
注意到 $n\le10^{14}$，而数位和只会有 $14\times9=126$ 种情况，所以我们直接枚举数位和，求出这个区间内满足数位和和整除条件的数字个数再累加即可。   
这里用数位 dp 实现即可。   
CODE：   
```cpp
//完整缺省源请见洛谷云剪贴板 jo5j6ogx
const int N=126,M=15;
ll n,dp[M+10][N+10][N+10],ans;
int a[N+10],k;
il ll dfs(int pos,int p,int m,int s,bool f){
	if(pos==0){
		ret m==0&&s==p;
	}
	if(dp[pos][m][s]!=-1&&(!f)){
		ret dp[pos][m][s];
	}
	ll ans=0;
	int mx=(f?a[pos]:9);
	for(int i=0;i<=mx;i++){
		ans+=dfs(pos-1,p,(m*10+i)%p,s+i,f&(i==a[pos]));
	}
	if(f){
		ret ans;
	}
	ret dp[pos][m][s]=ans;
}
int main(void){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	n=read<ll>();
	while(n){
		a[++k]=n%10;
		n/=10;
	}
	for(int i=1;i<=N;i++){
		memset(dp,-1,sizeof(dp));
		ans+=dfs(k,i,0,0,1);
	}
	write(ans);
	ret 0;
}
```


---

## 作者：Saint_ying_xtf (赞：1)

赛后发现其实不难。

很显然是个 DP，或者~~打表~~。

但是记忆化搜索实现比较容易。

发现各个位数的累加和最多为一个常数，所以大概定到 $140$。

然后我们针对枚举位数的累加和逐个记忆化搜索。

在记忆化搜索的过程中，我们控制好每一位比 $n$ 的对应那一位小，由于进位处理，如果之前的已经比他那一位小，我们直接就可以枚举到 $9$ 了。否则，最多只能枚举到拆位后的 $n$ 的那一位。

代码中的 $t$ 变量，为此时状态算出来的值对 $res$ 取模，$res$ 就是位数的累加和。若 $t=0$ 时就要记录答案。

然后到后面累计 dfs 下去的返回的值之和，然后进行状态转移。

```cpp
int n;
int a[105],cnt=0;
int dp[20][2][150][150];
int res;

int dfs(int p,int x,int sum,int t){
	if(sum > res) return 0;
	if(!p) return (!t) && sum==res;
	if(dp[p][x][sum][t] != -1) return dp[p][x][sum][t];
	int ans=0;
	dp[p][x][sum][t]=0;
	int maxn;
	if(x) maxn=a[p];
	else maxn=9;
	for(int i = 0;i <= maxn;i++){
		ans+=dfs(p-1,x & (i==maxn),sum + i,(t * 10 + i) % res);
	}return dp[p][x][sum][t]=ans;
}
void solve(){
	cin>>n;
	while(n){
		a[++cnt]=n%10;n/=10;
	}
	int ans=0;
	for(int i = 1;i <= 140;i++){
		mem(dp,-1);res=i;
		ans+=dfs(cnt,1,0,0);
	}cout<<ans;
}
### ```

---

## 作者：a1co0av5ce5az1cz0ap_ (赞：0)

虽然这是 ABC336E 的题解，但是这题和 P4127 几乎完全一样。

考虑枚举数字和，之后直接数位 dp。$f_{p,s,n,u}$ 表示当前在第 $p$ 位，和为 $s$，原数 $\bmod$ 数字和为 $n$，$u$ 表示这一位是否有上界的方案数，然后直接记忆化搜索即可。

```cpp
int dig[25],dcnt;
ll p;// p 是枚举的数字和
ll MP[25][205][205];
ll calc(ll now,ll sum,ll n,bool up){
	if(!now&&!sum)return 0;
	if(!now)return !n&&sum==p;
	if(!up&&~MP[now][sum][n])return MP[now][sum][n];
	ll ans=0;
	int u=up?dig[now]:9;
	for(int i=0;i<=u;i++)ans+=calc(now-1,sum+i,(10*n+i)%p,up&i==u);
	return up?ans:MP[now][sum][n]=ans;
}
ll CALC(ll n){
	dcnt=0;
	while(n)dig[++dcnt]=n%10,n/=10;
	ll ans=0;
	for(p=1;p<=9*dcnt;p++)memset(MP,-1,sizeof(MP)),ans+=calc(dcnt,0,0,1);
	return ans;
}
```

---

## 作者：梦应归于何处 (赞：0)

### 题目大意

给你一个正整数 $N$，问你小于等于 $N$ 的数中有多少个数能被它的数位和整除，举个例子：$2024$ 的数位和为 $2+0+2+4=8$，$8$ 能整除 $2024$ 所以这就是一个成功的数。

### 思路

模版数位 dp 但是这个数位 dp 我们需要把数位和给提出来不放在 dp 数组的定义中，要不然我们还要把 $N$ 放进状态里，空间就不行了。

### 代码

~~~cpp
#include <bits/stdc++.h>
#define ll long long
#define ex exit(0)
#define _endl_ puts("");
#define inl inline
#define null NULL
#define pll pair<ll,ll>
#define mkp make_pair
using namespace std;
ll dp[20][200][200][2];
ll a[20];
int i;
ll tot;
ll dfs(ll pos, ll sum, ll st, ll lim) {
	if (pos > tot && sum == 0) {
		return 0;
	}
	if (pos > tot) {
		return st == 0 && sum == i;
	}
	if (dp[pos][sum][st][lim] != -1) {
		return dp[pos][sum][st][lim];
	}
	ll ret = 0;
	ll zd = lim ? a[tot - pos + 1] : 9;
	for (int k = 0; k <= zd; k++) {
		ret += dfs(pos + 1, sum + k, (st * 10 + k) % i, k == zd && lim);
	}
	return dp[pos][sum][st][lim] = ret;
}
int main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ll n;
	cin >> n;
	while (n) {
		a[++tot] = n % 10;
		n /= 10;
	}
	ll ans = 0;
	for (i = 1; i <= 9 * tot; i++) {
		memset(dp, -1, sizeof(dp));
		ans += dfs(1, 0, 0, 1);
	}
	cout << ans << endl;
	return 0;
}
~~~

---

