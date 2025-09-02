# Special Matrices

## 题目描述

#### 翻译：
#### 题意:
一个 $n * n$ 的方阵被称为特殊的，满足下面的条件:

+ 它是二进制的，每一个格子上只能是$1$或者$0$。
+ 每一行的和以及每列的和等于$2$

现在，给你 $n$ 以及方阵前 $m$ 行，求前 $m$ 行与给出的 $m$ 行相同的“特殊”方阵的数量。

可能所需的答案会很大，输出其对 $mod$ 取模后的结果。(**并不保证$mod$为质数**)


接下来 $m$ 行，每一行给出一个长度为 $n$ 的零一串。第 $i$ 行表示方阵的第 $i$ 行，保证给出的 $m$ 行形成的 $n * m$ 的方阵每一列最多出现两个$1$，同时给出的$m$行，每一行一定包含两个$1$ 。

## 说明/提示

$2 <= n <= 500$

$0 <= m <= n$

$2 <= mod <= 10^9$

#### 样例解释:

对于第一个样例，满足条件的矩阵为:
```plain
Case1:  Case2:
 011     011
 101     110
 110     101
```

样例二：因为整个 $n$ * $n$ 的矩阵已经给出，所以只能有一种方案。

## 样例 #1

### 输入

```
3 1 1000
011
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 4 100500
0110
1010
0101
1001
```

### 输出

```
1
```

# 题解

## 作者：y0y68 (赞：12)

好吧 $O(n^2)$ 做法应该更好想一点

一眼DP题

令 $dp_{j,k}$ 表示有 $j$ 列需要 $2$ 个 $1$，$k$ 列需要 $1$ 个 $1$ 的方案数。显然 $0 \le j,k \le n$，答案为 $dp_{0,0}$。

初始化很简单，统计一下输入里有 $0$ 个 $1$ 的列数 $t_0$，有 $1$ 个 $1$ 的列数 $t_1$，然后 $dp_{t_0,t_1}=1$ 即可。

转移从 $m+1$ 枚举行，然后枚举 $j$，再是 $k$。

欸？这不是 $O(n^3)$ 的吗？

当然 $k$ 可以由 $j$ 算出。

假设枚举到第 $i$ 行，在理想情况下，即前 $i-1$ 行每行都有 $2$ 个 $1$，则后面的 $n-i+1$ 行还剩下 $2 \times (n-i+1)$ 个 $1$ 要填，此时 $k=2 \times (n-i+1)$。然而可能前面并不是每行都有 $2$ 个 $1$，根据 $j$ 和 $k$ 的定义，有 $j$ 列每列还要放 $2$ 个 $1$，这就破坏了 $k$ 的性质，于是有 $j$ 列共 $2 \times j$ 个 $1$，需要去除，即 $k=2 \times (n-i+1) - 2 \times j$。

接下来就很好办了，分类讨论：

1. 这一行的 $2$ 个 $1$ 分别放在两个目前需要 $2$ 个 $1$ 的列：$dp_{j-2,k+2} \gets dp_{j,k} \times \binom{j}{2}$。注意这两个目前需要 $2$ 个 $1$ 的列此时变成了两个需要 $1$ 个 $1$ 的列。
2. 这一行的 $2$ 个 $1$ 分别放在两个目前需要 $1$ 个 $1$ 的列：$dp_{j,k-2} \gets dp_{j,k} \times \binom{k}{2}$。
3. 这一行的 $2$ 个 $1$ 分别放在一个目前需要 $1$ 个 $1$ 的列和一个目前需要 $2$ 个 $1$ 的列：$dp_{j-1,k} \gets dp_{j,k} \times j \times k$。注意这个目前需要 $2$ 个 $1$ 的列变成了需要 $1$ 个 $1$ 的列，而目前需要 $1$ 个 $1$ 的列则无需 $1$，所以 $k$ 的 $+1$ 和 $-1$ 抵消了。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=505;
char a[N][N];
int n,m,mod,dp[N][N];
int main(){
	cin>>n>>m>>mod;
	for(int i=1;i<=m;i++)
		scanf("%s",a[i]+1);
	int t0=0,t1=0;
	for(int i=1;i<=n;i++){
		int cnt=0;
		for(int j=1;j<=m;j++)
			if(a[j][i]=='1')cnt++;
		if(cnt==0)t0++;
		else if(cnt==1)t1++;
	}
	dp[t0][t1]=1;
	for(int i=m+1;i<=n;i++)
		for(int j=0;j<=n;j++){
			int k=n-i+1-j<<1;
			if(k<0||k>n)continue;//注意边界
			if(j>1)(dp[j-2][k+2]+=1ll*j*(j-1)/2*dp[j][k]%mod)%=mod;
			if(k>1)(dp[j][k-2]+=1ll*k*(k-1)/2*dp[j][k]%mod)%=mod;
			if(j&&k)(dp[j-1][k]+=1ll*j*k*dp[j][k]%mod)%=mod;
		}
	cout<<dp[0][0]<<endl;
	return 0;
}
```

求赞QAQ

---

## 作者：mango2011 (赞：3)

看到这个 $500$ 的数据范围，我们就想到 $O(n^3)$ 的做法。

令 $dp_{i,j,k}$ 为填到第 $i$ 行恰好有 $j$ 列的和为 $0$，$k$ 列的和为 $1$，好处是这样我们就可以算出来有多少列和为 $2$，答案显然是 $dp_{n,0,0}$。

初始值？我们直接根据输入的东西统计一下有几行为 $0$，几行为 $1$ 即可。

转移？显然恰好由两个位置的值为 $1$，我们考虑下面三种情况：

1) 两个 $1$ 对应两个 $0$，这时 $dp_{i,j,k}=dp_{i-1,j+2,k-2}\times C_{j+2}^{2}$，因为减少了两个 $0$，增加了两个 $1$。

2) 两个 $1$ 对应一个 $0$ 一个 $1$，这时 $dp_{i,j,k}=dp_{i-1,j+1,k}\times (j+1)\times k$，因为减少了一个 $0$，$1$ 的个数没有变化。

3) 两个 $1$ 对应两个 $1$，这时 $dp_{i,j,k}=dp_{i-1,j,k+2}\times C_{k+2}^{2}$，因为 $0$ 的个数没有变化，$1$ 的个数减少了 $2$。

发现 MLE，于是改成滚动数组（我直接动态开 vector 转移）。

于是我们完成了转移，发现刚好 TLE，下面给出几个优化：

1) 转移优化：我们发现 $k$ 为奇数的时候方案数为 $0$。

2) 取模优化：我们用 long long 类型存储数据，这样在累加完答案之后只需要进行一次取模。

然后我们就~~靠着天时地利人和~~通过了这道题~~并取得最差解~~。

下面给出代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main()
{
    ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL);
    int n,m,mod;
    cin>>n>>m>>mod;
    vector<int>cnt(n+1);
    for(int i=1;i<=m;i++)
    {
        string s;
        cin>>s;
        for(int j=0;j<n;j++) cnt[j+1]+=s[j]-'0';
    }
    vector<vector<int> >g(n+5,vector<int>(n+5));
    int t1=0,t2=0;
    for(int i=1;i<=n;i++)
    {
        if(!cnt[i]) t1++;
        if(cnt[i]==1) t2++;
    }
    g[t1][t2]=1;
    for(int i=m+1;i<=n;i++)
    {
        vector<vector<int> >f(n+5,vector<int>(n+5));
        for(int j=0;j<=n;j++)
        {
            for(int k=0;k+j<=n;k+=2)
            {
                if(k>=2)
                {
                    f[j][k]+=g[j+2][k-2]*((j+2)*(j+1)>>1);
                }
                f[j][k]+=g[j+1][k]*(j+1)*k;
                f[j][k]+=g[j][k+2]*((k+2)*(k+1)>>1);
                f[j][k]%=mod;
            }
        }
        g=f;
    }
    cout<<g[0][0]<<endl;
    return 0;
}

```

---

## 作者：伟大的王夫子 (赞：2)

这道题让我在上面卡了很久，说明这道题的思维含量应该还是比较高的，所以就由我来写一篇题解加深大家对于题目的印象吧。

明显，我们可以发现，处理完前面 $m$ 列的矩阵之后，这个矩阵就被分为了 $n$ 列，每一列要么有 0 个 1，要么有 1 个 1，要么有 2 个 1。然后题目的意思相当于就是让我们进行 $n - m $ 次操作，每一次操作选出两列让这两列 1 的个数加 1，问有多少种方案。这时应该可以很容易想到一个 $O(n^3)$ 的做法，~~但我的做法却因为常数太大而挂了。~~

于是，痛定思痛，回想该如何对该算法进行改良。我们不用在状态中加入这是第几次操作这个维度，因为对于任意一个矩阵，只要他分别有 0，1，2 个 1 的列的数量知道了，就可以唯一确定这个次数。然而，知道其中的任意两个，另外一个也就知道了，所以我们的 dp 状态总数为 $O(n^2)$。

定义 $f_{i, j}$ 表示我们现在已经选了 $i$ 个 1，$j$ 个 2，最终要使得所有列都有 2 个 2 的方案数。很明显，$f_{0, n} = 1$。我们每次可以决策选一个有 1 个 1 的列，1 个有 0 个 1 的列，或者选两个有 0 个 1 的列，或者选两个有 1 个 1 的列。三种决策分别进行转移即可。注意一下转移顺序，应该先倒序枚举 $j$，再枚举 $i$。转移为 $O(1)$，故时间复杂度为 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
bool a[505][505];
int n, m, b[505], P, f[505][505];
inline void Add(int &x, int y) {
	x = x + y >= P ? x + y - P : x + y;
}
int main() {
	scanf("%d%d%d", &n, &m, &P);
	for (int i = 1; i <= m; ++i) {
		int cnt = 0;
		for (int j = 1; j <= n; ++j) {
			char ch;
			while (!(isdigit(ch = getchar())));
			a[i][j] = ch ^ 48;
			cnt += a[i][j];
		}
		if (cnt != 2) return puts("0"), 0;
	}
	int t1 = 0, t2 = 0;
	for (int j = 1; j <= n; ++j) {
		for (int i = 1; i <= m; ++i)
			b[j] += a[i][j];
		if (b[j] > 2) return puts("0"), 0;
		t1 += b[j] == 1, t2 += b[j] == 2;
	}
	//f[i][j]表示我们现在已经选了i个1，j个2，最终要到达(0, n) 的方案数
	f[0][n] = 1;
	for (int j = n; j >= 0; --j)
		for (int i = n; i >= 0; --i) {
			int k = n - i - j;
			if (k < 0) continue;
			Add(f[i][j], 1ll * k * (k - 1) / 2 * f[i + 2][j] % P);
			Add(f[i][j], 1ll * k * i * f[i][j + 1] % P);
			if (i >= 2) Add(f[i][j], 1ll * i * (i - 1) / 2 * f[i - 2][j + 2] % P);
		}
	printf("%d", f[t1][t2]);
}
```

---

## 作者：MuYC (赞：1)

#### 前言

打破这 $0$ 题解的僵局.

难度:3星

做法:dp + 滚动数组优化

$update$: (2020.12.23)加入了对于动态转移方程的说明，同时修改了一下排版。

#### 简化题意：

给定一个$n * n$的矩阵的前$m$行，求满足每行以及每列的和为2的01矩阵的数量

#### 思路

(这里提供的是 O($n ^ 3$)) 的做法。

观察到数据范围，发现不大像数学题，但是貌似也不是模拟题，看到方案数，就想到了$dp$ 。

考虑怎么去除掉给出的前 $m$ 行的影响。实际上这 $m$ 行的用处不是很大，只是限制了某些列上填入的一的个数。

然后很轻松的可以得到，哪些列只能填入一个 $1$ 以及哪一些可以填两个。

这样就把 $m$ 的影响去除了。

#### 如何设立状态?

##### 分析：

因为并不需要知道哪一些位置填了 $1$ ，实际上只要记录一下 哪一些列可以填一个 $1$ ，哪一些列可以填两个 $1$  ，以及当前行填多少个$1$， 但是因为当前行填的$1$又必须是两个，所以可以不用记录行有多少个$1$。

##### 得出做法:

不妨设立状态：

$dp[i][j][k]$为填到第 $i$ 行，还剩下 $j$ 可以填入一个 $1$ ， 还有 $k$ 列可以填两个 $1$。

这样子貌似会**爆空间**。想到每次只会用到 $i$ 以及 $i - 1$ ，不妨使用滚动数组的技巧。

设立状态:

$dp[j][k]$表示还剩下 $j$ 行可以填一个1，还有 $k$ 行可以填两个$1$。

另外初始边界为：

$dp[0][Cnt1][Cnt2] = 1$($Cnt1$,$Cnt2$分别表示在被 $m$ 行已知矩阵的情况下只能填一个$1$的列的数量以及只能填两个$1$的列的数量)

#### 怎么转移？

实际上根据设立的状态，很容易想到：

+ 当前行选择填入两个$1$的两列 一个为可以填两个$1$的列，一个为可以填 1 个1的列

+ 当前行选择填入两个$1$的列都为可以填两个$1$的列

+ 当前行选择填入两个$1$的列都为可以填一个$1$的列

同时你需要注意，那一些 **要填 2 两个 1 的列填入一个 1 后就转化为了要填一个1的列，这个在dp方程中是有体现的**。

同时任意选两个的话，根据乘法原理推推式子转移即可。

以上三种情况对应的状态转移方程分别为:

+ $dp[now][j][k - 1]$ += $dp[now$ ^ $1][j][k] * j * k$

+ $dp[now][j - 2][k]$ += $dp[now$ ^ $1][j][k]$ * $\frac{j * (j - 1)}{2}$

+ $dp[now][j + 2][k - 2]$ += $dp[now$ ^ $1][j][k]$ * $\frac{k * (k - 1)}{2}$

($now$ ^ $1$即是滚动数组的技巧,^表示异或)

关于方程的解释：

第一个方程：只有 $k - 1$ 是因为在某一可填入 2 个 1 的 列 填入一个1后，这个可以填两个1的列就变成了只能填 1 个 1 的列，因此 $j - 1$ 的 -1 就被抵消掉了。同时不难发现，在 $j$ 列里任选一个，在 $k$ 列中任选一个，方案数目是 $j * k$ 种的，因此得到这个状态转移方程。 

第二个方程： $j - 2$ 是因为我们假设填入的两个 1 都位于可以填入 1 个 1 的列，那么方案数就是 $C^{2}_{j}$，也就是从 $j$ 列中任选两个的方案数，用组合的知识算一算就会得到总方案数就是 $j * (j - 1) / 2$。 

第三个方程: $j + 2$ 并且 $k - 2$ 就是说，选择的两列都是能填入 2 个 1 的列，这样子的话，这两个可以填两个1的列就变成了只能填 1 个 1 的列，因此 $k - 2$ , $j + 2$ ，然后总方案数就是 $C^{2}_{k}$，也就是 $k * (k - 1) / 2$。

运算过程记得取模，虽然翻译温馨提示了一波 $mod$ 可能不是质数，但是不影响取模，因为没有除法（大雾）

最后的答案即为:

$dp[now][0][0]$

具体的看一看代码：

#### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MAXN = 505;

int n,m,Mod;
int L[MAXN];
char a[MAXN];
int dp[2][MAXN][MAXN]; //第一维是滚动数组，第二维表示有 i 列能填入 1 个 1，第三维表示有 j 列能填入两个 1

signed main()
{
    cin >> n >> m >> Mod;
    for(int i = 1 ; i <= n ; i ++)L[i] = 2;//一开始假定全部都只能填入两个1
    for(int i = 1 ; i <= m ; i ++)
    {
        cin >> a + 1;
        for(int j = 1 ; j <= n ; j ++)
        if(a[j] == '1')L[j] --;
    }
    int Cnt1 = 0, Cnt2 = 0;
    for(int i = 1 ; i <= n ; i ++)
    {//统计有多少列只能填一个1以及哪一些列只能填两个1
        if(L[i] == 1)Cnt1 ++;//Cnt1 就表示只能填入一个1的列
        else if(L[i] == 2)Cnt2 ++;//Cnt2 表示 能填入两个1 的列
    }
    dp[0][Cnt1][Cnt2] = 1;//初始化边界
    int now = 0;
    for(int i = m + 1 ; i <= n ; i ++)
    {
        now = (now ^ 1ll);
        for(int j = 0 ; j <= Cnt1 ; j ++)
            for(int k = 0 ; k <= Cnt2 ; k ++)
        dp[now][j][k] = 0;//一定要注意重置，不然会wa!
        for(int j = 0 ; j <= n ; j ++)
        {
            for(int k = 0 ; k <= n ; k ++)
            {
                if( dp[now ^ 1][j][k] == 0)continue;//肯定不会做出贡献，没必要转移，防止TLE
                if(j >= 1 && k >= 1)
                dp[now][j][k - 1] += (dp[now ^ 1ll][j][k] * j * k )% Mod, dp[now][j][k - 1] %= Mod;
                if(j >= 2)dp[now][j - 2][k] += (dp[now ^ 1ll][j][k] * (j - 1) * j / 2) % Mod, dp[now][j - 2][k] %= Mod;
                if(k >= 2)dp[now][j + 2][k - 2] += (dp[now ^ 1ll][j][k] * (k - 1) * k / 2) % Mod, dp[now][j + 2][k - 2] %= Mod;
            //方程的解释看上面的题解，有比较详细的题解。
            }
        }
    }
    cout << dp[now][0][0] % Mod;
    return 0;
}
```

#### 后话

这个做法感觉有点卡，写完了以后看了看当时比赛的题解，貌似有O($n ^ 2$)的解法，有兴趣的同学可以自己百度一下呀。这个题目还是挺好的！

---

## 作者：coding_goat (赞：0)

前置芝士：dp
## 思路

设 $f_{i,j,k}$ 表示枚举到第 $i$ 行时，有 $j$ 列 $1$ 的个数为 $0$，$k$ 列 $1$ 的个数为 $1$。

因为最终我们要求每行每列都有两个 $1$，我们控制每行来调控每列，答案为 $f_{n,0,0}$。

因为每一行会有两个 $1$ 被加上，于是我们分类讨论：
- 当加到两个出现次数为 $0$ 的列上，我们多出了两个出现次数为 $1$ 的，少了两个出现次数为 $0$ 的。此时一共有 $C_{j+2}^{2}$ 种选择方案。所以有：$f_{i,j,k}\gets f_{i-1,j+2,k-2} \times C_{j+2}^{2}$。

- 当加到一个出现次数为 $1$ 的列，另一个为 $0$ 的列上，出现次数为 $1$ 的加减刚好抵消，少了一个出现次数为 $0$ 的。此时一共有 $(j+1)\times k$ 种选择方案。所以有：$f_{i,j,k}\gets f_{i-1,j+1,k} \times (j+1)\times k$。

- 当加到两个出现次数为 $1$ 的列上，我们多出了两个出现次数为 $0$ 的，少了两个出现次数为 $1$ 的。此时一共有 $C_{k+2}^{2}$ 种选择方案。所以有：$f_{i,j,k}\gets f_{i-1,j,k+2} \times C_{k+2}^{2}$。

稍微卡常，记得减少取模次数，删掉冗余转移（当 $k$ 为奇数时答案为 $0$）。

时间复杂度：$O(n^3)$。
难点/坑点：无。

``` cpp
#include<bits/stdc++.h>

#define int ll
#define pii pair<int,int> 
#define pll pair<long long,long long> 
#define ll long long
#define i128 __int128

#define mem(a,b) memset((a),(b),sizeof(a))
#define m0(a) memset((a),0,sizeof(a))
#define m1(a) memset(a,-1,sizeof(a))
#define lb(x) ((x)&-(x))
#define lc(x) ((x)<<1)
#define rc(x) (((x)<<1)|1)
#define pb(G,x) (G).push_back((x))
#define For(a,b,c) for(int a=(b);a<=(c);a++)
#define Rep(a,b,c) for(int a=(b);a>=(c);a--)
#define in1(a) a=read()
#define in2(a,b) a=read(), b=read()
#define in3(a,b,c) a=read(), b=read(), c=read()
#define in4(a,b,c,d) a=read(), b=read(), c=read(), d=read()
#define fst first 
#define scd second 
#define dbg puts("IAKIOI")

using namespace std;

int read() {
	int x=0,f=1; char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) f=(c=='-'?-1:1); 
	for(;c<='9'&&c>='0';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	return x*f;
}
void write(int x) { if(x>=10) write(x/10); putchar('0'+x%10); }

int mod = 998244353;
int qpo(int a,int b) {int res=1; for(;b;b>>=1,a=(a*a)%mod) if(b&1) res=res*a%mod; return res; }
int inv(int a) {return qpo(a,mod-2); }

#define maxn 510

int n,m;
int cnt[maxn],c1,c0;
int f[2][maxn][maxn];

void work() {
	cin>>n>>m>>mod;
	const int MOD=mod;
	For(i,1,m) {
		string s;
		cin>>s;
		For(j,1,n) cnt[j]+=s[j-1]-'0';
	}
	For(i,1,n) if(cnt[i]==1) c1++; else if(cnt[i]==0) c0++;
	f[m&1][c0][c1]=1;
	For(i,m+1,n) For(j,0,n) For(k,0,n) if((k&1)==0&&j+k<=n) {
		f[i&1][j][k]=0;
		if(k>=2) f[i&1][j][k]+=f[(i-1)&1][j+2][k-2]*((j+2)*(j+1)/2);
		f[i&1][j][k]+=f[(i-1)&1][j+1][k]*(j+1)*k;
		(f[i&1][j][k]+=f[(i-1)&1][j][k+2]*((k+2)*(k+1)/2))%=MOD;
	}
	cout<<f[n&1][0][0]<<'\n';
}

signed main() {
//	freopen("data.in","r",stdin);
//	freopen("myans.out","w",stdout);
	ios::sync_with_stdio(false); 
	cin.tie(0); cout.tie(0);
	double stt=clock();
	int _=1;
//	_=read();
//	cin>>_;
	For(i,1,_) {
		work();
	}
	cerr<<"\nTotal Time is:"<<(clock()-stt)*1.0/1000<<" second(s)."<<'\n';
	return 0;
}
```

---

## 作者：include13_fAKe (赞：0)

dp 方法没想到是真的降智。

考虑设 $dp_{i,j}$ 代表还有 $i$ 个 $1$，$j$ 个 $2$（即为列上填的 `1` 的数量）表示到任意一行（可以证明只会出现一次）时出现次数为 $1,2$ 的列数。

一共三种转移：

- 选两个 $0$：$dp_{i+2,j}\gets dp_{i+2,j}+dp_{i,j}\times k_{00}$。
- 选一个 $1$ 一个 $0$：$dp_{i,j+1}\gets dp_{i,j+1}+dp_{i,j}\times k_{01}$。
- 选两个 $1$：$dp_{i-2,j+2}\gets dp_{i-2,j+2}+dp_{i,j}\times k_{11}$。

其中 $k_{00}$、$k_{11}$、$k_{01}$ 即为选数方案数。

按行转移即可，转移是没有环的。时间复杂度 $O(n^2)$。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n,m,mod;
int dp[2025][2025];
char maze[2025][2025];
int tj[2025];
signed main(){
	cin>>n>>m>>mod;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			cin>>maze[i][j];
			tj[j]+=(maze[i][j]=='1'); 
		}
	}
	int x,y;
	x=y=0;
	for(int i=1;i<=n;i++){
		if(tj[i]==1)	x++;
		else if(tj[i]==2)	y++;
	}
	dp[x][y]=1;
	for(int i=m;i<=n;i++){//第 i 行的情况  
		for(int j=0;j<=n;j+=2){//有多少个 1 一定是偶数个  
			int sum_0,sum_1=j,sum_2=(i*2-j)/2;
			sum_0=n-sum_1-sum_2;
//			cout<<i<<' '<<j<<' '<<sum_0<<' '<<sum_1<<' '<<sum_2<<endl;
			//考虑三种情况 
			//加一个 0 一个 1 dp[sum_1][sum_2+1]+=dp[sum_1][sum_2]*sum_1*sum_2
			//加两个 0 dp[sum_1+2][sum_2]+=dp[sum_1][sum_2]*(0 的选法) 
			//加两个 1 dp[sum_1-2][sum_2+2]+=dp[sum_1][sum_2]*(1 的选法 )
//			cout<<i<<' '<<j<<' '<<sum_0<<' '<<sum_1<<' '<<sum_2<<endl;
			if(sum_0<0||sum_1<0||sum_2<0)	continue;
//			cout<<i<<' '<<j<<' '<<sum_0<<' '<<sum_1<<' '<<sum_2<<' '<<dp[sum_1][sum_2]<<endl;
			if(sum_0>0&&sum_1>0){
				dp[sum_1][sum_2+1]+=dp[sum_1][sum_2]*sum_0%mod*sum_1%mod;
				dp[sum_1][sum_2+1]%=mod; 
			}
			if(sum_0>=2){
				dp[sum_1+2][sum_2]+=dp[sum_1][sum_2]*(sum_0*(sum_0-1)/2%mod)%mod;
				dp[sum_1+2][sum_2]%=mod;
			}
			if(sum_1>=2){
				dp[sum_1-2][sum_2+2]+=dp[sum_1][sum_2]*(sum_1*(sum_1-1)/2%mod)%mod;
				dp[sum_1-2][sum_2+2]%=mod;
			}
		
		}
	}
	cout<<dp[0][n]%mod<<endl;
	return 0;
}//5+100+130(50+48+32)+264(100+100+64)=499 rank 22 
```

---

## 作者：ifffer_2137 (赞：0)

### 题意
一个 $n\times n$ 的方阵被称为特殊的，当且仅当满足下面的条件:

- 每一个格子上只能是 $1$ 或者 $0$。
- 每一行的和以及每列的和等于 $2$。

现在，给你 $n$ 以及方阵前 $m$ 行，求前 $m$ 行与给出的 $m$ 行相同的特殊方阵的数量对 $mod$ 取模后的结果(并不保证 $mod$ 为质数)。
### 分析
一眼简单 DP。

先判掉无解，如果已知某一行的和 $\neq 2$ 或者某一列目前的和 $>2$，直接输出 $0$。

然后我们设计 DP，令 $f_{i,j,k}$ 表示填完前 $i$ 行，有 $j$ 列和为 $0$，$k$ 列和为 $1$ 的方案数，则它可以转移到：$f_{i+1,j-2,k+2}$，$f_{i+1,j-1,k}$，$f_{i+1,j,k-2}$，这三种转移分别要乘上 $\tbinom{j}{2}$，$j\times k$ 和 $\tbinom{k}{2}$，显然的，就可以 $\mathcal O(n^3)$ 了。

然后写完直接交，MLE 了，改成滚动数组，过了。

因为状态里的 $j$ 和 $k$ 可以相互计算得到，所以其实有 $\mathcal O(n^2)$ 做法，比较懒就不写了。
### 代码
```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
    char ch=getchar();int x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=5e2+5;
int n,m,mod;
string a[maxn];
int f[2][maxn][maxn];
int t[2];
signed main(){
	cin.tie(0),cout.tie(0);
	n=read(),m=read(),mod=read();
	for(int i=1;i<=m;i++){
		cin>>a[i];
		a[i]=' '+a[i];
		int cnt=0;
		for(int j=1;j<=n;j++) if(a[i][j]-'0') cnt++;
		if(cnt!=2){
			cout<<0<<endl;
			return 0;
		}
	}
	for(int i=1;i<=n;i++){
		int cnt=0;
		for(int j=1;j<=m;j++) if(a[j][i]-'0') cnt++;
		if(cnt>2){
			cout<<0<<endl;
			return 0;
		}
		t[cnt]++;
	}
	f[0][t[0]][t[1]]=1;
	for(int i=m;i<=n-1;i++){
		for(int j=0;j<=n;j++){
			for(int k=0;k<=n;k++){
				if(f[0][j][k]){
					if(k>=2) f[1][j][k-2]=(f[1][j][k-2]+(k*(k-1)/2)%mod*f[0][j][k]%mod)%mod;
					if(j>=1) f[1][j-1][k]=(f[1][j-1][k]+f[0][j][k]*j%mod*k%mod)%mod;
					if(j>=2) f[1][j-2][k+2]=(f[1][j-2][k+2]+(j*(j-1)/2)%mod*f[0][j][k]%mod)%mod;
				}
			}
		}
		for(int j=0;j<=n;j++){
			for(int k=0;k<=n;k++){
				f[0][j][k]=f[1][j][k];
				f[1][j][k]=0;
			}
		}
	}
	cout<<f[0][0][0]<<endl;
	return 0;
}
```

---

