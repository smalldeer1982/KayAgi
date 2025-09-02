# Sereja and Intervals

## 题目描述

Sereja is interested in intervals of numbers, so he has prepared a problem about intervals for you. An interval of numbers is a pair of integers $ [l,r] $ $ (1<=l<=r<=m) $ . Interval $ [l_{1},r_{1}] $ belongs to interval $ [l_{2},r_{2}] $ if the following condition is met: $ l_{2}<=l_{1}<=r_{1}<=r_{2} $ .

Sereja wants to write out a sequence of $ n $ intervals $ [l_{1},r_{1}] $ , $ [l_{2},r_{2}] $ , $ ... $ , $ [l_{n},r_{n}] $ on a piece of paper. At that, no interval in the sequence can belong to some other interval of the sequence. Also, Sereja loves number $ x $ very much and he wants some (at least one) interval in the sequence to have $ l_{i}=x $ . Sereja wonders, how many distinct ways to write such intervals are there?

Help Sereja and find the required number of ways modulo $ 1000000007 $ $ (10^{9}+7) $ .

Two ways are considered distinct if there is such $ j $ $ (1<=j<=n) $ , that the $ j $ -th intervals in two corresponding sequences are not equal.

## 说明/提示

In third example next sequences will be correct: $ {[1,1],[3,3]} $ , $ {[1,2],[3,3]} $ , $ {[2,2],[3,3]} $ , $ {[3,3],[1,1]} $ , $ {[3,3],[2,2]} $ , $ {[3,3],[1,2]} $ .

## 样例 #1

### 输入

```
1 1 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 5 1
```

### 输出

```
240
```

## 样例 #3

### 输入

```
2 3 3
```

### 输出

```
6
```

# 题解

## 作者：歪逼 (赞：14)

> 有 $n$ 个区间，你需要为每个区间分配左右端点 $l$，$r$ ($1 \le l \le r \le m$)，使得区间两两互不包含且至少存在一个区间的左端点等于 $x$，输出方案数对 $10^9 + 7$ 取模的结果。
>
> $1 \le n·m \le 10^5$, $1 \le x \le m$。

若 $n >m$ 肯定无解，因为一定存在两个左端点相同的区间，而这两个区间定是包含关系。这样可以得到 $n \le \sqrt{10^5}$。

考虑确定了 $n$ 个左端点和 $n$ 个右端点，区间无标号，有几种组合方案。假设 $l_1$ 到 $l_n$ 有序，$r_1$ 到 $r_n$ 也有序，区间两两不包含，即 $\forall i,j \in [1,n]$，$l_i < l_j$ 且 $r_i < r_j$。如果 $l_1$ 和 $r_x(x>1)$ 组成一个区间，$r_1$ 和 $l_y$ 组成区间，显然有 $l_1 < l_y$，$r_1 < r_x$，这样就有包含关系了，所以 $l_1$ 只能和 $r_1$ 组合。同理，得到 $l_i$ 只能和 $r_i$ 组合，所以方案是唯一的。

这样问题转换为选出 $n$ 个左端点和 $n$ 个右端点的方案，区间有标号最后需要在乘以 $n!$。设 $f_{i,j,k}$ 表示前 $i$ 个数，选了 $j$ 个左端点和 $k$ 个右端点。注意右端点个数不能大于左端点个数 ( $k \le j$ )，否则是不合法的。

转移很简单，四种情况：$i$ 不选、$i$ 做左端点、$i$ 做右端点、$i$ 既做左端点又做右端点。当 $i=x$ 是 $i$ 必须做左端点，只有两种情况。时间复杂度 $O(n^2m)$，空间会炸所以要用滚动数组或压掉一维。


```c++
#include <bits/stdc++.h>
using namespace std;

inline int read() {
	int x = 0, f = 0; char c = 0;
	while (!isdigit(c)) f |= c == '-', c = getchar();
	while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return f ? -x : x;
}

#define N 320
#define P 1000000007
#define int long long

int n, m, x, f[N][N];

signed main() {
	n = read(), m = read(), x = read();
	if (n > m) return puts("0"), 0;

	memset(f, 0, sizeof f), f[0][0] = 1;

	for (int i = 1; i <= m; i ++) {
		for (int j = n; j >= 0; j --) {
			for (int k = j; k >= 0; k --) {
				if (i == x) f[j][k] = 0;
				if (j > 0) (f[j][k] += f[j - 1][k]) %= P;
				if (i != x && k > 0) (f[j][k] += f[j][k - 1]) %= P;
				if (j > 0 && k > 0) (f[j][k] += f[j - 1][k - 1]) %= P;
			}
		}
	}

	int res = f[n][n];
	for (int i = 1; i <= n; i ++) {
		(res *= i) %= P;
	}
	printf("%lld\n", res);
	return 0;
}
```
update: 数据范围已更正，感谢提醒

---

## 作者：ETHANK (赞：2)

[传送门](https://www.luogu.com.cn/problem/CF367E)

首先 $n>m$ 时显然无解。由原题的数据范围可得 $n\le \sqrt{10^5}$ 。

考虑如何构造出满足条件的 $n$ 个区间。不难发现对于任意两个不同区间 $[l_i,r_i],[l_j,r_j]$ ，都有 $l_i<l_j,r_i<r_j$ 即可。那么我们如果选取了 $n$ 个左端点和 $n$ 个右端点，**有且仅有**一种满足题意的构造方式，也就是将左右端点分别排序后按序号匹配。

下面考虑如何计算总方案数。定义 $dp[i][j][k]$ 为考虑完前 $i$ 个位置，目前有 $j$ 个左端点被选择，$k$ 个右端点被选择。而右端点总是要与左端点匹配，所以需要保证 $j\ge k$ 。注意到关键点时只能考虑向 $k+1$ 转移。

时间复杂度：$O(mn^2)$

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define ll long long
using namespace std;
inline ll read(){
    ll x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
const int N=1e5+5,P=1e9+7;
int n,m,x,fac[N];
inline void Add(int &x,const int &y){x+=y;if(x>P)x-=P;}
int main(){
    n=read(),m=read(),x=read();
    if(n>m)return puts("0"),0;
    int dp[2][n+5][n+5];
    memset(dp,0,sizeof(dp));
    dp[0][0][0]=1;
    rep(i,1,m){
        int now=i&1,pre=now^1;
        memset(dp[now],0,sizeof(dp[now]));
        rep(j,0,n)rep(k,0,j){//第i个位置，j个左括号，k个右括号
            if(j>k&&i!=x)Add(dp[now][j][k+1],dp[pre][j][k]);
            Add(dp[now][j+1][k],dp[pre][j][k]);
            Add(dp[now][j+1][k+1],dp[pre][j][k]);
            if(i!=x)Add(dp[now][j][k],dp[pre][j][k]);
        }
    }
    fac[0]=1;
    rep(i,1,n)fac[i]=1ll*fac[i-1]*i%P;
    printf("%lld\n",1ll*dp[m&1][n][n]*fac[n]%P);
    return 0;
}
```



---

## 作者：tony0530 (赞：0)

# solution

管理员大大，求您了，过一下审吧，要不然我的博客要无啦！T^T.

------

#### 题目
 

[传送门](https://www.luogu.com.cn/problem/CF367E)

------

#### 算法

发现 $n \le m$（若 $n > m$ 就会包含），所以 $n < \sqrt{10^5} $，考虑 DP，$f_{i,j,k}$ 表示考虑前 $i$ 个位置，有 $j$ 个左端点以及 $k$ 个未匹配的右端点，转移方程为：$f_{i,j,k} = f_{i,j,k} + f_{i-1,j-1,k-1} + f_{i - 1, j - 1, k}$，$i \not= x$ 时有 $f_{i,j,k} = f_{i,j,k} + f_{i-1,j,k+1} + f_{i-1,j,k}$。

最后的答案就是 $n! \times f_{m+1,n,0}$。

时间复杂度为 $O(n^2m)$。

----

#### 代码

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 310;
const int mod = 1e9 + 7;

int n, m, x;
int f[N][N];

signed main()
{
    cin >> n >> m >> x;
    if(n > m)
    {
        cout << "0";
        return 0;
    }
    memset(f, 0, sizeof f);
    f[0][0] = 1;
    for(int i = 1 ; i <= m ; i ++ )
        for(int j = n ; j >= 0 ; j -- )
            for(int k = j ; k >= 0 ; k -- )
            {
                if(i == x) f[j][k] = 0;
                if(j > 0) 
                {
                    f[j][k] += f[j - 1][k];
                    f[j][k] %= mod;
                }
                if(i != x && k > 0)
                {
                    f[j][k] += f[j][k - 1];
                    f[j][k] %= mod;
                }
                if(j > 0 && k > 0)
                {
                    f[j][k] += f[j - 1][k - 1];
                    f[j][k] %= mod;
                }
            }
    int res = f[n][n];
    for(int i = 1 ; i <= n ; i ++ )
    {
        res *= i;
        res %= mod;
    }
    cout << res;
    return 0;
}
```

---

## 作者：wangyibo201026 (赞：0)

## solution

首先看到这个题我们闻到一股 CF 味，所以我们尝试解决这个问题。

首先，注意到 $n$ 过大可能会导致 $2 \times n$ 个端点分配有 $> 2$ 的重叠问题，所以当 $n > m$ 时，问题答案为 $0$，因为根据鸽巢原理会有 $2$ 个左端点或者右端点分配到了同一个位置，那么肯定会有区间包含关系。

然后如果 $n \le m$，我们需要设计一个 DP 状态进行求解。

设 $f_{i, j, k}$ 表示到了 $i$ 位置，目前有 $j$ 个左端点，$k$ 个没有匹配上的右端点，最后答案就是 $f_{m + 1, n, 0} \times n!$（最后由于我们计数默认排序，所以要 $\times n!$）。

写一下状态转移方程，对于所有情况下有：

$$f_{i, j, k} = f_{i, j, k} + f_{i - 1, j - 1, k - 1}$$

$$f_{i, j, k} = f_{i, j, k} + f_{i - 1, j - 1, k}$$

对于 $i \ne x$ 的情况下有：

$$f_{i, j, k} = f_{i, j, k} + f_{i - 1, j, k + 1}$$

$$f_{i, j, k} = f_{i, j, k} + f_{i - 1, j, k}$$

## code

代码我就不放了吧。

---

## 作者：lfxxx (赞：0)

首先不难发现的是区间两两不交等价于左端点右端点位置均递增。

然后注意到当 $n > m$ 时一定无解，因此有 $n \leq \sqrt{n \times m}$，所以考虑一下 $O(n \times m \times n)$ 的做法。

假设我们把左端点看成左括号，右端点看成右括号，根据括号序列的性质，左括号都在右括号左边等价于任意一个前缀中左括号不少于右括号，放到区间上就是任意一个前缀中成为了左端点的位置不少于成为了右端点的位置，因此设计状态 $dp_{i,l,r}$ 表示考虑前缀 $[1,i]$ 成为了左端点和右端点的位置分别有 $l,r$ 个，显然 $l \geq r$ 就是合法的，然后在 $x$ 处强制转移左端点即可。

注意区间是有标号的，所以最后要乘上 $n$ 的阶乘。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 1e9+7;
const int warma = 500;
int dp[warma][warma],g[warma][warma];
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
int n,m,x;
signed main(){
	cin>>n>>m>>x;
	if(n>m){
		cout<<0<<'\n';
		return 0;
	}
	dp[0][0]=1;
	for(int i=1;i<=m;i++){
		for(int l=0;l<=n;l++){
			for(int r=0;r<=l;r++){
				if(r+1<=l&&i!=x) g[l][r+1]=(g[l][r+1]+dp[l][r])%mod;
				if(l<=n) g[l+1][r+1]=(g[l+1][r+1]+dp[l][r])%mod;
				if(l<=n) g[l+1][r]=(g[l+1][r]+dp[l][r])%mod;
				if(i!=x) g[l][r]=(g[l][r]+dp[l][r])%mod;
			}
		}
		for(int l=0;l<=n;l++){
			for(int r=0;r<=n;r++) dp[l][r]=g[l][r],g[l][r]=0;
		}
	}
	int res=1;
	for(int i=1;i<=n;i++) res=res*i%mod;
	cout<<dp[n][n]*res%mod<<'\n';
	return 0;
}

```

---

## 作者：EternalAlexander (赞：0)

注意到：当 $n \geq m$ 时答案一定为 $0$，因此实际上有 $n \leq \sqrt{10^5}$。

如果区间之间两两不交，则存在一种顺序使得 $R_i > R_{i-1}, L_i > L_{i-1}$。考虑计算满足上述条件的方案然后将答案乘以 $n!$。

考虑在 $m$ 个位置上摆上 $n$ 个左端点和 $n$ 个右端点，每个位置的左端点数量和右端点数量均不能大于 $1$。如果存在选区间的方案使得所有区间的左右端点集合恰好为你摆放的位置，那么一定只存在**恰好一种**这样的方案，即左右端点分别排序后依次当作每个区间的左右端点。

检验是否存在方案也是容易的，从左往右依次考虑每个右端点并将其和最前面没被匹配的左端点匹配。具体而言可以记录一个变量 $Q$ 表示前面没被匹配的左端点个数，扫到右端点则 $Q-1$，左端点则 $Q+1$，如果 $Q$ 始终非负且最后为 $0$ 则合法。

那么可以考虑把这个 $k$ 压进状态里，有 $f_{i,j,k}$ 表示考虑到了第 $i$ 个位置，前面放了 $j$ 个左端点，当前的 $Q$ 为 $k$ 的方案数。答案即 $f_{m,n,0}$。复杂度 $O(n^2m) = O((nm)^{1.5})$

```cpp
#include <bits/stdc++.h>

using ll = long long;
const int mod = 1e9+7;
const int lim = 1e5;

int n,m,x,fac[lim + 7],ans;

int main() {
	scanf("%d%d%d",&n,&m,&x);
	if (n > m) { puts("0"); return 0; }
	fac[0] = 1;
	for (int i = 1; i <= lim; ++ i) fac[i] = (ll) fac[i-1] * i % mod;
	int dp[m+3][n+3][n+3];
	std::memset(dp,0,sizeof(dp));
	dp[1][0][0] = 1;
	for (int i = 1; i <= m; ++ i) {
		for (int j = 0; j <= n; ++ j)
		for (int k = 0; k <= j; ++ k) {
			if (k && i != x) dp[i+1][j][k-1] = (dp[i+1][j][k-1] + dp[i][j][k]) % mod; //-
			dp[i+1][j+1][k+1] = (dp[i+1][j+1][k+1] + dp[i][j][k]) % mod;
			dp[i+1][j+1][k] = (dp[i+1][j+1][k] + dp[i][j][k]) % mod;
			if (i != x) dp[i+1][j][k] = (dp[i+1][j][k] + dp[i][j][k]) % mod;
		}
	}
	printf("%lld",(ll) dp[m+1][n][0] * fac[n] % mod);
	return 0;
}



```


---

