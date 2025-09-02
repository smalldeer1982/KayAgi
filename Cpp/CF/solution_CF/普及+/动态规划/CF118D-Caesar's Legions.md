# Caesar's Legions

## 题目描述

凯撒大帝喜欢让他的士兵列队。假设他的军队有$n_1$个步兵和$n_2$个骑兵。他认为超过$k_1$个步兵连续排列或是超过$k_2$个骑兵连续排列是不优雅的。请找出共有多少种优雅的列队方案数。

注：所有$n_1+n_2$个士兵都要被排列，且所有步兵和骑兵都视作相同。

## 说明/提示

1表示步兵，2表示骑兵

第一个样例中，只有一种优雅的排列方式：121

第二个样例中，有五种优雅的排列方式：12122,12212,21212,21221,22121

## 样例 #1

### 输入

```
2 1 1 10
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 3 1 2
```

### 输出

```
5
```

## 样例 #3

### 输入

```
2 4 1 1
```

### 输出

```
0
```

# 题解

## 作者：Owen_codeisking (赞：24)

## 简单题意：

有一个 $01$ 序列，这个序列中有 $n_1$ 个 $0$ ， $n_2$ 个 $1$ 。如果这个序列最长连续的 $0$ 不超过 $k_1$ ，最长连续的 $1$ 不超过 $k_2$ ，就说这个序列是完美的。
求完美 $01$ 序列的方案数，并且方案数对 $10^8$ 取模。

$n_1,n_2\leq 100,\ k_1,k_2\leq 10$

------------

## 分析：

经典 $dp$ 题。

我的 $dp$ 比较麻烦， $dp[i][j][k][0/1]$ 表示已经用了 $i$ 个 $0$ ， $j$ 个 $1$ ，连续结尾有 $k$ 个 $0/1$ 的方案数。

不妨令 $n=n_1,m=n_2,x=k_1,y=k_2$ ，那么可以推出方程：

$(i>0,\ k\in [2,x])\quad dp[i][j][k][0]=dp[i-1][j][k-1][0]$

$(i>0,\ k\in [1,y])\quad dp[i][j][1][0]+=dp[i-1][j][k][1]$

$(j>0,\ k\in [2,y])\quad dp[i][j][k][1]=dp[i][j-1][k-1][1]$

$(j>0,\ k\in [1,x])\quad dp[i][j][1][1]+=dp[i][j-1][k][0]$

初始化 $dp[1][0][1][0]=dp[0][1][1][1]=1$ 

目标 $(k\in [1,x])\quad dp[n][m][k][0]$

$\qquad (k\in [1,y])\quad dp[n][m][k][1]$

以上的思路可以在 $O(nmk)$ 的时间， $O(nmk)$ 的空间内解决这个问题。

$Code\ Below:$
```cpp
#include <bits/stdc++.h>
using namespace std;
const int p=1e8;
int n,m,x,y,dp[110][110][11][2];

int main()
{
    scanf("%d%d%d%d",&n,&m,&x,&y);
    dp[1][0][1][0]=dp[0][1][1][1]=1;
    register int i,j,k,ans=0;
    for(i=0;i<=n;i++)
        for(j=0;j<=m;j++){
            if(i>0){
                for(k=2;k<=x;k++)
                    dp[i][j][k][0]=dp[i-1][j][k-1][0];
                for(k=1;k<=y;k++)
                    dp[i][j][1][0]=(dp[i][j][1][0]+dp[i-1][j][k][1])%p;
            }
            if(j>0){
                for(k=2;k<=y;k++)
                    dp[i][j][k][1]=dp[i][j-1][k-1][1];
                for(k=1;k<=x;k++)
                    dp[i][j][1][1]=(dp[i][j][1][1]+dp[i][j-1][k][0])%p;
            }
        }
    for(i=1;i<=x;i++) ans=(ans+dp[n][m][i][0])%p;
    for(i=1;i<=y;i++) ans=(ans+dp[n][m][i][1])%p;
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：ArcherHavetoLearnWhk (赞：11)

### 题意：
规定 $\texttt{01}$ 序列由 $n$ 个 $0$ 和 $m$ 个 $1$ 组成，求最长连续的 $0$ 数量不超过 $o$ 且最长连续的 $1$ 数量不超过 $p$ 的序列数。

### 思路：

题目要求答案对 $10^8$ 取模，而暴搜复杂度与答案相关，这个数据范围会超时。

所以考虑 dp。

状态：$dp_{i,j,0/1}$ 表示目前排列 $i$ 个步兵和 $j$ 个骑兵，最后一个是步兵/骑兵的方案数。

过程即为，枚举 $i$ 和 $j$，每次对于一组 $i$ 和 $j$，枚举最后一段连续的 $0$/$1$ 的数量 $k$，并按状态转移方程计算。

状态转移方程：

对于 $dp_{i,j,0}$ 情况，$k$ 的上限不能大于限制 $o$ 也不能大于当前已排列 $0$ 总数 $i$，上限即为 $\min(o,i)$。由 $dp_{i-k,j,1}$ 进行转移是因为目前枚举到的 $k$ 个 $0$ 前面会是 $1$，所以第一维是 $i-k$，第三位是 $1$：

$$dp_{i,j,0}=\sum_{k=1}^{\min(o,i)}dp_{i-k,j,1}$$

对于 $dp_{i,j,1}$ 同理，

$$dp_{i,j,1}=\sum_{k=1}^{\min(p,j)}dp_{i,j-k,0}$$

初始化时 $dp_{0,0,0}$ 和 $dp_{0,0,1}$ 均赋值为 $1$。

答案即为 $dp_{n,m,0}+dp_{n,m,1}$，易于理解，同题意。

由于复杂度过关，较为简洁，这个三维的做法是非常好的，非常推荐。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,o,p,dp[205][205][2],md=1e8;
int main(){
	cin>>n>>m>>o>>p;
	dp[0][0][0]=dp[0][0][1]=1; //初始化
	for(int i=0;i<=n;i++){
		for(int j=0;j<=m;j++){
			if(i+j==0)continue; //如果i和j都等于0就跳过
			for(int k=1;k<=min(o,i);k++)dp[i][j][0]=(dp[i][j][0]+dp[i-k][j][1])%md;
			for(int k=1;k<=min(p,j);k++)dp[i][j][1]=(dp[i][j][1]+dp[i][j-k][0])%md; //状态转移方程
		}
    }
	cout<<(dp[n][m][0]+dp[n][m][1])%md; //输出最终方案数并取模
	return 0;
} 
```


---

## 作者：ran_qwq (赞：10)

设 $dp_{i,j,0/1,k}$ 为当前有 $i$ 个步兵，$j$ 个骑兵，当前是步兵 / 骑兵，末尾有连续 $k$ 个的方案数。

- 由骑兵转移到步兵：$dp_{i+1,j,0,1}=\sum\limits_{p=1}^{k2}dp_{i,j,1,p}$。
- 由步兵转移到骑兵：$dp_{i,j+1,1,1}=\sum\limits_{p=1}^{k1}dp_{i,j,0,p}$。
- 由步兵转移到步兵：$dp_{i+1,j,0,p+1}=dp_{i,j,0,p}$。
- 由骑兵转移到骑兵：$dp_{i,j+1,1,p+1}=dp_{i,j,1,p}$。

初始状态是 $n1+n2=1$ 的情况，答案是 $\sum\limits_{i=1}^{k1}dp_{n1,n2,0,i}+\sum\limits_{i=1}^{k2}dp_{n1,n2,1,i}$。

---

## 作者：HZEason_Ai (赞：8)

### Solution：

~~本蒟蒻的第一篇题解，大佬轻喷(；´д｀)ゞ~~

很显然，由数据得这种指数级别的暴搜会超时。

我们思考：上面的做法效率低下，是因为同一个状态会被访问多次。

如果我们每查询完一个状态后将该状态的信息存储下来，再次需要访问这个状态就可以直接使用之前计算得到的信息，从而避免重复计算。这充分利用了动态规划中很多问题具有大量重叠子问题的特点，属于用空间换时间的「**记忆化**」思想。


我们用 `m[x][y][tot1][tot2]` 表示在还剩 $x$ 个步兵和 $y$ 个骑兵且已有 $tot1$ 或 $tot2$ 个骑兵或步兵连续排列情况下的方案数。

### 奉上AC代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e8;
int n1,n2,k1,k2,m[101][101][11][11];	//记忆化数组
int read()	//快读
{
	int x=0,a=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar())
		if(c=='-') a=-1;
	for(;c>='0'&&c<='9';c=getchar())
		x=x*10+c-'0';
	return x*a;
}
int dfs(int x,int y,int tot1,int tot2)	//tot1，tot2分别表示已经选取了连续的几个步兵和骑兵，
										//x，y表示还有几个骑兵和步兵未选
{
	int ans=0;
	if(x==0&&y==0)	//方案成立，总数+1
	{
		ans=1;return ans;
	}
	if((x==0&&tot2>=k2)||(y==0&&tot1>=k1)) return 0;
	if(m[x][y][tot1][tot2]!=-1) return m[x][y][tot1][tot2];		//如果记录过直接返回
	if(x>0&&tot1<k1)
	{
		ans+=dfs(x-1,y,tot1+1,0);
		ans%=mod;
	}
	if(y>0&&tot2<k2)
	{
		ans+=dfs(x,y-1,0,tot2+1);
		ans%=mod;
	}
	m[x][y][tot1][tot2]=ans%mod;	//记录这种情况
	return ans%mod;
}
signed main()
{
//	freopen("a.in","r",stdin);
	n1=read();n2=read();
	k1=read();k2=read();
	memset(m,-1,sizeof m);	//建议赋一个比0小的初值，因为答案的情况可能为任意非负整数
	cout<<dfs(n1,n2,0,0)%mod;
	return 0;
}
```

---

## 作者：chengor (赞：7)

### 题意

有一个01序列，这个序列中有n1个0，n2个1。如果这个序列最长连续的0不超过k1，最长连续的1不超过k2，就说这个序列是完美的。
求完美 01序列的方案数，并且方案数对 10^8取模。
n1 ,n2 ≤100, k1,k2 ≤10

### 分析

其实这道题可以不开四维的。

开四维的话是一个一个士兵往上叠加，其实可以一排步兵0（or骑兵1）打包叠加。

f[tot][first][2] 表示前tot个兵中，有first个步兵(所有tot-first个骑兵) 最后一个是步兵0、骑兵1； 

### 附上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k1,k2;
long long f[3000][3000][2];//前tot个兵，有first个步兵(tot-first个骑兵)最后一个是步兵0、骑兵1； 
int main()
{
	scanf("%d%d%d%d", &n, &m, &k1, &k2);
	memset(f,0,sizeof(f));
	f[0][0][1] = 1;
	f[0][0][0] = 1;
	for (int i=1;i<=n+m;i++)
		for (int j=0;j<=i;j++)
		{
			for(int k=1;k<=k2&&i-k>=j;k++)//往后插入骑兵1
			{
				f[i][j][1]=(f[i][j][1]+f[i-k][j][0])%100000000;
			}
			for(int k=1;k<=min(k1,max(i,j));k++)//往后插入步兵0 
			{
				f[i][j][0]=(f[i][j][0]+f[i-k][j-k][1])%100000000;
			}
		}
	long long sum=f[n+m][n][0]%100000000+f[n+m][n][1]%100000000;
	cout<<sum%100000000;
}
```


---

## 作者：_Life_ (赞：3)

### 题意
有一个 $\texttt{01}$ 序列，序列中有 $n_1$ 个 $0$ ，$n_2$ 个 $1$，$0$ 的最长连续长度不超过 $k_1$，$1$ 的最长连续长度不超过 $k_2$，求构造这样的序列的方案数，答案对 $100000000$ 取模。

$1\le n_1,n_2\le 100,1\le k_1,k_2\le 10$

### 题解
**大力DP**
###### 状态
设状态 $dp[i][j][k][0/1]$，表示有 $i$ 个 $0$，$j$ 个 $1$，末尾连续 $k$ 个相同字符，字符为 $0/1$ 的构造方案数。

###### 答案
显然有:
$$ans=\sum_{i=1}^{k_1}dp[n1][n2][i][0]+\sum_{i=1}^{k_2}dp[n1][n2][i][1]$$

###### 边界条件
- 整个字符串只有一个 $0$ ，$dp[1][0][1][0]=1$
- 整个字符串只有一个 $1$ ，$dp[0][1][1][1]=1$

###### 转移方程
先考虑结尾为 $0$ 的情况，此时又有两种情况：

- $k=1$，因为这个 $0$ 是结尾处唯一的 $0$，所以此前的字符必然为 $1$，枚举此前 $1$ 的长度
- $k\neq1$，这个 $0$ 之前有 $k-1$ 个 $0$

$$dp[n_1][n_2][k][0]=\begin{cases}\sum_{i=1}^{min(n_2,k_2)} dp[n_1-1][n_2][i][1]&(k=1)\\dp[n_1-1][n_2][k-1][0]&(k\neq1)\end{cases}$$

结尾为 $1$ 的情况同理：
$$dp[n_1][n_2][k][1]=\begin{cases}\sum_{i=1}^{min(n_1,k_1)} dp[n_1][n_2-1][i][0]&(k=1)\\dp[n_1][n_2-1][k-1][1]&(k\neq1)\end{cases}$$

###### 转移方向
因为我太菜了搞不清楚转移方向，所以直接上记搜

### 代码
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mod 100000000
#define int long long
using namespace std;
int n1,n2,k1,k2,dp[105][105][15][2];
int dfs(int n1,int n2,int k,int flag)
{
	if(n1<0||n2<0)//记得加上越界处理
		return 0;
	if(dp[n1][n2][k][flag]!=-1)
		return dp[n1][n2][k][flag];
	int ans=0;
	if(flag==0)
		if(k==1)
			for(int i=1;i<=k2&&i<=n2;i++)
				ans=(ans+dfs(n1-1,n2,i,1))%mod;
		else
			ans=dfs(n1-1,n2,k-1,0);
	else
		if(k==1)
			for(int i=1;i<=k1&&i<=n1;i++)
				ans=(ans+dfs(n1,n2-1,i,0))%mod;
		else
			ans=dfs(n1,n2-1,k-1,1);
	return dp[n1][n2][k][flag]=ans;
}
signed main()
{
	scanf("%lld %lld %lld %lld",&n1,&n2,&k1,&k2);
	memset(dp,-1,sizeof(dp));
	dp[1][0][1][0]=1;
	dp[0][1][1][1]=1;
	int ans=0;
	for(int i=1;i<=k1;i++)
		ans=(ans+dfs(n1,n2,i,0))%mod;
	for(int i=1;i<=k2;i++)
		ans=(ans+dfs(n1,n2,i,1))%mod;
	printf("%lld",ans);
}
```

---

## 作者：lukelin (赞：3)

### 前言
**安利一下我的博客**  
&ensp;**[更好的阅读体验](https://www.cnblogs.com/linzhengmin/p/11207850.html)**
### 题意简述
一个01序列由$n_1$个0和$n_2$个1组成，求最长连续0串长度**不超过**$k_1$，最长连续1串长度**不超过**$k_2$的序列的方案总数
### 题解
#### 状态
方案总数
#### 变量
已经取了i个0，j个1，当前末尾连续串长度为k，末尾为l。
#### 转移
![](https://cdn.luogu.com.cn/upload/pic/64406.png)  
&ensp;注:$[i=1]$意为在$i=1$时值为$1$，否则值为$0$。
### 代码
```cpp
#include <cstdio>
#include <algorithm>

using namespace std;

const long long MOD = 100000000;

namespace fast_IO{
    const int IN_LEN = 10000000, OUT_LEN = 10000000;
    char ibuf[IN_LEN], obuf[OUT_LEN], *ih = ibuf + IN_LEN, *oh = obuf, *lastin = ibuf + IN_LEN, *lastout = obuf + OUT_LEN - 1;
    inline char getchar_(){return (ih == lastin) && (lastin = (ih = ibuf) + fread(ibuf, 1, IN_LEN, stdin), ih == lastin) ? EOF : *ih++;}
    inline void putchar_(const char x){if(oh == lastout) fwrite(obuf, 1, oh - obuf, stdout), oh = obuf; *oh ++= x;}
    inline void flush(){fwrite(obuf, 1, oh - obuf, stdout);}
    int read(){
        int x = 0; int zf = 1; char ch = ' ';
        while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar_();
        if (ch == '-') zf = -1, ch = getchar_();
        while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar_(); return x * zf;
    }
    void write(int x){
        if (x < 0) putchar_('-'), x = -x;
        if (x > 9) write(x / 10);
        putchar_(x % 10 + '0');
    }
}

using namespace fast_IO;

long long f[105][105][11][2];

int main(){
	int n1 = read(), n2 = read(), k1 = read(), k2 = read();
	for (int i = 1; i <= k1; ++i) f[i][0][i][0] = 1;
	for (int i = 1; i <= k2; ++i) f[0][i][i][1] = 1;
	for (int i = 1; i <= n1; ++i)
		for (int j = 1; j <= n2; ++j){
			for (int k = 1; k <= min(j, k2); ++k)
				(f[i][j][1][0] += f[i - 1][j][k][1]) %= MOD;
			for (int k = 1; k <= min(i, k1); ++k)
				(f[i][j][1][1] += f[i][j - 1][k][0]) %= MOD;
			for (int k = 2; k <= min(i, k1); ++k)
				(f[i][j][k][0] += f[i - 1][j][k - 1][0]) %= MOD;
			for (int k = 2; k <= min(j, k2); ++k)
				(f[i][j][k][1] += f[i][j - 1][k - 1][1]) %= MOD;
		}
	long long ans = 0;
	for (int i = 1; i <= 10; ++i)
		(ans += f[n1][n2][i][0] + f[n1][n2][i][1]) %= MOD;
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：Agakiss (赞：3)

As（这个神秘的男人)给我随机分到的题

题意：

给出n1个1，n2个2，给出k1和k2代表连续的1和2的最大长度，问能够构造的合法的不同串的数量。

一开题看数据范围就知道不用优化，于是直接给Cy神仙说是红题（LuoGu紫题肯定是被恶意评分了），于是又被Zxh大神仙嘲讽了

真的不难，计数Dp，方程易推

$f[a][b][c][d]$表示对于前a个士兵，第a个是兵种（0为步兵，1为骑兵），末尾有连续c个该兵种，总共有d个该兵种

然后可知如果第a个兵种的方案可以由第a-1个兵种相同且满足规则（总数不超过且连续数不超过）或第a-1个兵种不同的方案数相加得到

于是就很好推了

初始化$f[1][0][1][1]=f[1][1][1][1]=1$

然后从2开始做

（由于本来看的是题目大意，然后不知道要取模而错了两次的弱智Code_Note）

附上代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
#define ll long long
#define MAXN 210
#define MOD 100000000
int n, m, a, b;
ll ans;
ll f[MAXN][2][MAXN][MAXN];
inline int read() {
	int s = 0, w = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (s == '-') w = -1;
	for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
	return s * w;
}
int main() {
	n = read(), m = read();
	a = read(), b = read();
	f[1][0][1][1] = 1;
	f[1][1][1][1] = 1;
	for (register int i = 2; i <= n + m; i++) {
		for (register int j = 2; j <= a; j++)
			for (register int k = 1; k <= n; k++)
				(f[i][0][j][k] += f[i - 1][0][j - 1][k - 1]) %= MOD;
		for (register int j = 2; j <= b; j++)
			for (register int k = 1; k <= m; k++)
				(f[i][1][j][k] += f[i - 1][1][j - 1][k - 1]) %= MOD;
		for (register int j = 1; j <= a; j++)
			for (register int k = 1; k <= n; k++)
				if (i - k >= 0)
					(f[i][1][1][i - k] += f[i - 1][0][j][k]) %= MOD;		
		for (register int j = 1; j <= b; j++)
			for (register int k = 1; k <= m; k++)
				if (i - k >= 0)
					(f[i][0][1][i - k] += f[i - 1][1][j][k]) %= MOD;			
	}
	for (register int i = 1; i <= a; i++) 
		(ans += f[n + m][0][i][n]) %= MOD;;
	for (register int i = 1; i <= b; i++) 
		(ans += f[n + m][1][i][m]) %= MOD;;
	printf("%lld", ans);
	return 0;
}
```
这是我写的最认真的一次题解了！

---

## 作者：cff_0102 (赞：2)

从学校测试来的，学校测试中是要排鸡和鸭，所以为了方便，下文就直接说鸡和鸭了。

明显这道题可以用 dp。设 $dp[i][j][1]$ 表示排前 $i$ 个数，有 $j$ 个是鸡，且最后一个是鸡的方案数；$dp[i][j][0]$ 表示排前 $i$ 个数，有 $j$ 个是鸡，且最后一个是鸭的方案数。

接下来枚举最后一段连续的鸡/鸭的长度，并按照状态转移方程（不难想但不好描述，具体参见代码）计算出 $dp[i][j][1]$ 和 $dp[i][j][0]$ 的值。

最后输出 $dp[n+m][n][0]$ 与 $dp[n+m][n][1]$ 的和。不要忘了取模。

赛时代码：

```
#include<bits/stdc++.h>
using namespace std;
int dp[514][514][4];//dp[i][j][1] 表示排前 i 个数，有 j 个是只因，且最后一个是只因的方案数；dp[i][j][0]表示排前 i 个数，有 j 个是只因，且最后一个不是只因的方案数
int main(){
    int n,m,k1,k2;
    cin>>n>>m>>k1>>k2;
    dp[1][1][1]=dp[1][0][0]=1;dp[1][0][1]=dp[1][1][0]=0;
    dp[0][0][1]=dp[0][0][0]=1;
    for(int i=2;i<=n+m;i++){
        for(int j=0;j<=i&&j<=n;j++){
            //枚举最后连续的长度
            for(int k=1;k<=k1&&k<=j;k++){
                //先是最后只因的情况
                dp[i][j][1]+=dp[i-k][j-k][0];
                dp[i][j][1]%=100000000;
            }
            for(int k=1;k<=k2&&i-k>=j;k++){
                //再是没只因的情况
                dp[i][j][0]+=dp[i-k][j][1];
                dp[i][j][0]%=100000000;
            }
        }
    }
    cout<<(dp[n+m][n][0]+dp[m+n][n][1])%100000000;
}
```

注意初始化的时候要将 `dp[0][0][1]` 和 `dp[0][0][0]` 设为 $1$。

---

## 作者：zrx0722 (赞：1)

[CF118D Caesar's Legions](https://www.luogu.com.cn/problem/CF118D)
## 题意
有 $n_1$ 个相同的步兵和 $n_2$ 个相同的骑兵排列在一条线上，并且连续的步兵不超过 $k_1$ 个，连续的骑兵不超过 $k_2$ 个。
## 思路
动态规划。  
先来一个比较暴力的写法，用 $dp[i][j][k][p][q]$ 表示目前一共有 $i$ 个士兵，其中有 $j$ 个步兵，有 $k$ 个步兵，目前有连续的 $p$ 个士兵，以及目前是步兵还是骑兵（$q$ 为 0 时为步兵，$q$ 为 1 时为骑兵）。  
仔细一想，总共的士兵是已知的，所以知道步兵或骑兵的数量就可以推另一种士兵的数量。这样就可以压缩到四维。  

所以用 $dp[i][j][k][l]$ 表示目前一共有 $i$ 个士兵，其中有 $j$ 个骑兵，目前有连续的 $k$ 个士兵，以及目前是步兵还是骑兵（$l$ 为 0 时为步兵， $l$ 为 1 时为骑兵）。
## 转移方程：
### 先看 $l$ 为 0 时的情况：  
#### $l$ 从 1 变为 0 ：  
这时只有一个连续的步兵，而且这种状态能且只能从 $i-1$ 个兵且 $l$ 为 1 的所有状态累加而来，所以：
$$dp[i][j][1][0]=\sum_{k=1}^{k_2}dp[i-1][j][k][1]$$
#### 其他  
从前一个相同的兵的状态推过来：
$$dp[i][j][k][0]=dp[i-1][j][k-1][0]$$
### $l$ 为 1 时
#### $l$ 从 0 变为 1：  
和“$l$ 从 1 变为 0”差不多，只是把 $l$ 的位置换一下：
$$dp[i][j][1][1]=\sum_{k=1}^{k_1}dp[i-1][j-1][k][0]$$
#### 其他  
同上，只是把 $l$ 从 0 改成 1：
$$dp[i][j][k][1]=dp[i-1][j-1][k-1][1]$$  
### 注意
$j$ 是骑兵的数量，即 $l$ 为 1 时才要在处理多个连续同种士兵时改变 $j$ 的值，而 $l$ 为 0 时不用。
## 最后
$$ans=\sum_{i=1}^{k_1}dp[k_1+k_2][k_2][i][0]+\sum_{i=1}^{k_2}dp[k_1+k_2][k_2][i][1]$$
## 代码
```cpp
#include<iostream>
using namespace std;
const int mod=1e8;
int n,m,a,b,dp[201][101][11][2],maxn;
main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>a>>b;
	dp[1][0][1][0]=dp[1][1][1][1]=1;
	for(int i=2;i<=n+m;++i)
		for(int j=0;j<=m;++j)
		{
			for(int k=1;k<=b;++k)
				(dp[i][j][1][0]+=dp[i-1][j][k][1])%=mod;
			for(int k=2;k<=a;++k)
				dp[i][j][k][0]=dp[i-1][j][k-1][0];
			for(int k=1;k<=a;++k)
				(dp[i][j][1][1]+=dp[i-1][j-1][k][0])%=mod;
			for(int k=2;k<=b;++k)
				dp[i][j][k][1]=dp[i-1][j-1][k-1][1];
		}
	for(int i=1;i<=a;++i)
		(maxn+=dp[n+m][m][i][0])%=mod;
	for(int i=1;i<=b;++i)
		(maxn+=dp[n+m][m][i][1])%=mod;
	cout<<maxn;
}
```

---

## 作者：BreakPlus (赞：1)

## [$\text{题解 CF118D}$](/problem/CF118D)

### $\text{Describe}$

凯撒大帝喜欢让他的士兵列队。假设他的军队有 $n_1$ 个步兵和 $n_2$
 个骑兵。他认为超过 $k_1$
 个步兵连续排列或是超过 $k_2$
 个骑兵连续排列是不优雅的。请找出共有多少种优雅的列队方案数。

注：所有 $n_1+n_2$
 个士兵都要被排列，且所有步兵和骑兵都视作相同。
 
### $\text{Solution}$
 
不知道为啥题解区清一色的四维 dp，我提供一种三维的做法。

设 $\text{dp}_{i,j,0/1}$ 表示将 $i$ 个步兵和 $j$ 个骑兵排列，最后一个士兵是步兵/骑兵的方案总数。我们枚举 $k$ 表示当前排列末尾会有几个连续的相同兵种的士兵，转移方程如下：

$\text{dp}_{i,j,0}=\sum \limits_{k=1}^{x}\text{dp}_{i-k,j,1}$

（其中 $x$ 是 $k$ 的上限，显然 $x$ 不能超过 $k_1$ 也不能超过总数 $i$，所以 $x=\max(k_1,i)$。这 $k$ 个步兵前面将是骑兵，所以转移到第三维是 $1$ 的情况）

对于第三维是 $1$ 的情况同理，如下：

$\text{dp}_{i,j,1}=\sum \limits_{k=1}^{x}\text{dp}_{i,j-k,0}$

（此时 $x=\max(k_2,i)$。）

初始化：$\text{dp}_{0,0,0/1}=1$。

### $\text{Code}$

```cpp
#include<cstdio>
using namespace std;
int n1,n2,k1,k2,f[110][110][2];
const int mod=1e8;
int main(){
	scanf("%d%d%d%d",&n1,&n2,&k1,&k2);
	f[0][0][0]=f[0][0][1]=1;
	for(int i=0;i<=n1;i++)
		for(int j=0;j<=n2;j++){
			if(i==0&&j==0) continue;
			for(int k=1;k<=i&&k<=k1;k++)
				f[i][j][0]=(f[i][j][0]+f[i-k][j][1])%mod;
			for(int k=1;k<=j&&k<=k2;k++)
				f[i][j][1]=(f[i][j][1]+f[i][j-k][0])%mod;
		}
	printf("%d\n",(f[n1][n2][0]+f[n1][n2][1])%mod);
	return 0;
}
```

---

## 作者：洛璟 (赞：1)

看到题解里全是 dp ……我思索着那么记忆化也行罢……

## Solution:

能 dp 的题目记忆化搜索都能做，能用记忆化搜索的题目 dp 不一定行（震声

——沃兹基·硕德

那么我们首先想暴搜怎么做。

一个一个位置去枚举，并且可以把不超过 $k1,k2$ 的步兵和骑兵都看作一个点，并去枚举这个长度。

显然暴搜会 TLE ，那么我们可以想到，假设 $A$ 为步兵，$B$ 为骑兵，$*$ 代表两者其一，那么对于 `***ABB**` 以及 `******ABB**` ，这两种摆放方式中的 `ABB**` 部分，是可以不需要继续搜索下去的，我们可以记录下这一段对于答案的贡献，并直接加上就好了。那么该如何记忆化，也就可以推出来了，只要在暴搜的基础上加上对于这种情况的记忆化，也就可以了。

我们现在设 $memory_{i,j,k}$ 状态为当前放的是步兵还是骑兵，步兵还剩 $j$ 个，骑兵还剩 $k$ 个时的搭配方案数，在暴搜的基础上记得给 $memory$ 数组赋值以及判断 $memory$ 数组是否为空，进行记忆化搜索即可。

剩下部分细节在代码注释中给出。

## Code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mo = 100000000;
int n[2], k[2];
int meo[2][110][110];//上面的memory数组
int ans;
inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c>'9')
    {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = (x << 3) + (x << 1) + (c ^ '0');
        c = getchar();
    }
    return x * f;
}
int dfs(int x)//x代表当前这个位置放的是什么
{
    int tmp = 0;
    if (meo[x][n[0]][n[1]] != -1)//若当前不为空则返回已经有的数值
    {
        return meo[x][n[0]][n[1]];
    }
    if (n[x] == 0)
    {
        if (n[x ^ 1] == 0)//0^1=1;1^1=0，同时若两者均为空，则表示有一种情况了
        {
            tmp = 1;
        }
        return tmp;
    }
    for (int i = 1;i <= min(n[x], k[x]);++i)//循环枚举这个位置连续放多少个相同的士兵
    {
        n[x] -= i;
        tmp += dfs(x ^ 1);
        n[x] += i;
        tmp %= mo;
    }
    meo[x][n[0]][n[1]] = tmp % mo;//大力模法
    return tmp % mo;
}
signed main()
{
    n[0] = read();
    n[1] = read();
    k[0] = read();
    k[1] = read();
    memset(meo, 0x7fffffff, sizeof(meo));
    ans = dfs(1) + dfs(0);//开头两种放法
    printf("%lld", ans % mo);
    return 0;
}
```

---

## 作者：lx_zjk (赞：1)



## 题目意思
凯撒大帝喜欢让他的士兵列队。假设他的军队有$\text{n}$个步兵和$\text{m}$个骑兵。他认为超过$\text{k1}$个步兵连续排列或是超过$\text{k2}$个骑兵连续排列是不优雅的。请找出共有多少种优雅的列队方案数。

## 状态转移方程
$$f[n][m][i][j]$$
队列里已有$n$个$A$军队 $m$个$B$军队 $i, j$表示$B A$军队人数连续的数量

显然$\text{i j}$中必有一个数为$0$

我们可以想出状态转移方程式

$\text{f[n][m][i][j] ps:这里的i表示的连续的b军队数量 j表示连续的a军队数量}$
$$f[i][j][1][0] += f[i][j - 1][0][k]$$
$$f[i][j][0][1] += f[i - 1][j][k][0]$$
$$f[i][j][0][k] += f[i - 1][j][0][k - 1]$$
$$f[i][j][k][0] += f[i][j - 1][k - 1][0]$$

## Code
```cpp
const int N = 100 + 5;
const int K = 10 + 5;

int n, m, k1, k2, f[N][N][K][K];

int main () {
	read (n); read (m); read (k1); read (k2);
	f[0][0][0][0] = 1;
	for (int i = 0; i <= n; i ++ ) {
		for (int j = 0; j <= m; j ++ ) {
			for (int k = 1; k <= min (k1, i); k ++ ) Add (f[i][j][1][0], f[i][j - 1][0][k]);
			for (int k = 1; k <= min (k2, j); k ++ ) Add (f[i][j][0][1], f[i - 1][j][k][0]);
			for (int k = 1; k <= min (k1, i); k ++ ) Add (f[i][j][0][k], f[i - 1][j][0][k - 1]);
			for (int k = 1; k <= min (k2, j); k ++ ) Add (f[i][j][k][0], f[i][j - 1][k - 1][0]);
		}
	}
	int ans = 0;
	for (int i = 1; i <= k2; i ++ ) Add (ans, f[n][m][i][0]);
	for (int i = 1; i <= k1; i ++ ) Add (ans, f[n][m][0][i]);
	cout << ans << endl;
	return 0;
}
```

---

## 作者：ainivolAGEM (赞：0)

**前情提要：**[更好的阅读体验。](https://www.luogu.com.cn/article/4kfv4c4o)

## 题目大意

[题目](https://www.luogu.com.cn/problem/CF118D)给出 $n1$ 个步兵，$n2$ 个骑兵，要求排列这 $n1 + n2$ 个兵使得不存在连续 $k1$ 个步兵或连续 $k2$ 个骑兵，求方案数。

## 题目分析

由于排列方案数只和步兵和骑兵数量有关，满足无后效性，考虑 dp。则状态容易想到为：$dp [ i ] [ j ]$ 表示当前排列了 $i$ 个步兵和 $j$ 个骑兵的方案数。

但是由于方案数与前一个步兵或者骑兵相关，所以还要加一维 $k$，表示当前排的兵种（$0$ 表示步兵，$1$ 表示骑兵）。

那么只需枚举 $i$ 和 $j$，然后枚举最后一段连续的兵种的长度 $k$，就可以得出状态转移方程了：（$k$ 的范围既不能大于 $n$ 也不能大于 $i$，所以是 $\min ( n , i )$）

$$dp [ i ] [ j ] [ 0 ] = \sum ^ { \min ( n1 , i ) } _ { k = 1 } dp [ i - k ] [ j ] [ 1 ]$$

$$dp [ i ] [ j ] [ 1 ] = \sum ^ { \min ( n2 , j ) } _ { k = 1 } dp [ i ] [ j - k ] [ 0 ]$$

初始化容易理解，即 $dp [ 0 ] [ 0 ] [ 0 ] = dp [ 0 ] [ 0 ] [ 1 ] = 1$。

最终答案 $dp [ n ] [ m ] [ 0 ] + dp [ n ] [ m ] [ 1 ]$。

记得**随时取模**。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=104;
const int T=2;
const int MOD=1e8;
ll n1,n2,k1,k2,dp[N<<1][N<<1][T];
int main(){
	cin>>n1>>n2>>k1>>k2;
	dp[0][0][0]=dp[0][0][1]=1;
	for(int i=0;i<=n1;i++){
		for(int j=0;j<=n2;j++){
			if(i+j==0){
				continue;
			}
			for(int k=1;k<=min(k1,(ll)i);k++){
				dp[i][j][0]=(dp[i][j][0]+dp[i-k][j][1])%MOD;
			}
			for(int k=1;k<=min(k2,(ll)j);k++){
				dp[i][j][1]=(dp[i][j][1]+dp[i][j-k][0])%MOD;
			}
		}
    }
	cout<<(dp[n1][n2][0]+dp[n1][n2][1])%MOD;
}
```

---

## 作者：xukehg (赞：0)

一个简单好想的 dp 题。

定义 $dp_{i, j, k, 0/1}$ 表示前 $i$ 个数中有 $j$ 个步兵，且末尾有 $k$ 个零或一，很容易得到方程转移式：

1. $dp_{i - 1, j - 1, k - 1, 0} + dp_{i, j, k, 0} \to dp_{i, j, k, 0}$ 。 

2. $dp_{i - 1, j - 1, k, 1} + dp_{i, j, 1, 0} \to dp_{i, j, 1, 0}$ 。

3. $dp_{i - 1, j, k - 1, 1} + dp_{i, j, k, 1} \to dp_{i, j, k, 1}$ 。 

4. $dp_{i - 1, j, k, 0} + dp_{i, j, 1, 1} \to dp_{i, j, 1, 1}$ 。

写的时候稍微注意一下越界以及 1 式和 3 式的 $k$ 从 $2$ 开始即可。

答案为：
$$\sum_{i=1}^kdp_{n + m, n, i, 0} + \sum_{i=1}^ldp_{n + m, n, i, 1}$$

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 105,mod = 1e8;

int n,m,kk,ll,ans = 0;
int dp[2 * N][2 * N][15][2];//表示已经前i个数有j个0末尾头连续k个0/1 
int main(){
	cin >> n >> m >> kk >> ll;
	dp[1][1][1][0] = dp[1][0][1][1] = 1;
	for (int i = 2;i <= n + m;i++){
		for (int j = 0;j <= i;j++){
			for (int k = 2;k <= ll;k++){
				dp[i][j][k][1] += dp[i - 1][j][k - 1][1];//在k-1个1后面拼1 
				dp[i][j][k][1] %= mod;
			} //5 1 2 1-> 4 1 1 1
			for (int k = 1;k <= min(i,kk);k++){
				dp[i][j][1][1] += dp[i - 1][j][k][0];//在k个0后面拼1 
				dp[i][j][1][1] %= mod;				
			}
			if (j > 0){
				for (int k = 2;k <= kk;k++){
					dp[i][j][k][0] += dp[i - 1][j - 1][k - 1][0];//在k-1个0后面拼0 
					dp[i][j][k][0] %= mod;
				}
				for (int k = 1;k <= min(i,ll);k++){
					dp[i][j][1][0] += dp[i - 1][j - 1][k][1];//在k个1后面拼0
					dp[i][j][1][0] %= mod;					
				}
			}
		}
	}
	for (int i = 1;i <= kk;i++){
		ans = (ans + dp[n + m][n][i][0]) % mod;
	}
	for (int i = 1;i <= ll;i++) ans = (ans + dp[n + m][n][i][1]) % mod;
	cout << ans << endl;
}

---

## 作者：Fantasy_Segment_Tree (赞：0)

首先这道题是一个计数类dp。

我们把步兵和骑兵当作 $0$ 和 $1$，设 $dp_{i,j,k,0/1}$ 表示 $0$ 选了 $i$ 个，$1$ 选了 $j$ 个，结尾连续相同了 $k$ 个，最后一个是 $0$ 或 $1$ 的方案数。

则很明显初始化是 $dp_{1,0,1,0}=dp_{0,1,1,1}=1$，表示 $0$ 或 $1$ 放了一个有 $1$ 种方案。

接下来就是转移方程。

$k \in [2,k1]: dp_{i,j,k,0}=dp_{i-1,j,k-1,0}$

$k = 1: dp_{i,j,k,0}= \sum_{x=1}^{k2}dp_{i-1,j,x,1}$

$k \in [2,k2]: dp_{i,j,k,1}=dp_{i,j-1,k-1,1}$

$k = 1: dp_{i,j,k,1}= \sum_{x=1}^{k1}dp_{i,j-1,x,0}$

代码如下。

```
#include <iostream>
using namespace std;

int n, m, k1, k2, dp[105][105][105][2], mod = 100000000;

int main() {
	cin >> n >> m >> k1 >> k2;
	dp[1][0][1][0] = dp[0][1][1][1] = 1;
	for(int i = 0; i <= n; i++) {
		for(int j = 0; j <= m; j++) {
			if(i > 0) {
				for(int k = 2; k <= k1; k++) dp[i][j][k][0] = dp[i - 1][j][k - 1][0];
				for(int k = 1; k <= k2; k++) dp[i][j][1][0] = (dp[i][j][1][0] + dp[i - 1][j][k][1]) % mod;
			}
			if(j > 0) {
				for(int k = 2; k <= k2; k++) dp[i][j][k][1] = dp[i][j - 1][k - 1][1];
				for(int k = 1; k <= k1; k++) dp[i][j][1][1] = (dp[i][j][1][1] + dp[i][j - 1][k][0]) % mod;
			}
		}
	}
	int ans = 0;
	for(int k = 1; k <= k1; k++) ans = (ans + dp[n][m][k][0]) % mod;
	for(int k = 1; k <= k2; k++) ans = (ans + dp[n][m][k][1]) % mod;
	cout << ans;
}
```

---

## 作者：harmis_yz (赞：0)

# 分析

考虑暴力 DP。

定义状态函数 $f_{i,j,k1,k2}$ 表示前 $i+j$ 个人中，有 $i$ 个步兵和 $j$ 个骑兵且末尾连续步兵数量为 $k1$，连续骑兵数量为 $k2$ 的方案数。

由于末尾连续的要么是步兵要么是骑兵，所以状态中 $k1,k2$ 只会有 $1$ 个非零。枚举 $i,j,k1,k2$，若连续的是步兵，则有：$f_{i,j,k1,k2}\to f_{i,j,k1,k2}+f_{i-1,j,k1-1.k2}$；否则有：$f_{i,j,k1,k2}\to f_{i,j,k1,k2}+f_{i,j-1,k1,k2-1}$。

但是这个是错的。因为当 $k1=1,k2=0$ 或 $k1=0,k2=1$ 时，$k1-1,k2$ 或 $k1,k2-1$ 均为 $0$。而在 $i+j\ne 1$ 时这显然是不可能的。所以这种情况我们还需要去枚举一下上一次 $k1$ 或 $k2$ 为 $0$ 时的 $k2$ 或 $k1$。而在同一组 $(i,j)$ 中着只会出现不超过 $2$ 次，所以复杂度正确。

答案为 $\sum\limits_{i=1}^{\min(n1,k1)} f_{n1,n2,i,0}+\sum\limits_{i=1}^{\min(n2,k2)}f_{n1,n2,0,i}$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define _int __int128
#define re register
#define il inline
#define pii pair<int,int>
#define x first
#define y second
#define gc getchar()
#define rd read()
#define debug() puts("------------")

namespace yzqwq{
	il int read(){
		int x=0,f=1;char ch=gc;
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=gc;}
		while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=gc;
		return x*f;
	}
	il int qmi(int a,int b,int p){
		int ans=1;
		while(b){
			if(b&1) ans=ans*a%p;
			a=a*a%p,b>>=1;
		}
		return ans;
	}
	il auto max(auto a,auto b){return (a>b?a:b);}
	il auto min(auto a,auto b){return (a<b?a:b);}
	il int gcd(int a,int b){
		if(!b) return a;
		return gcd(b,a%b);
	}
	il int lcm(int a,int b){
		return a/gcd(a,b)*b;
	}
	il void exgcd(int a,int b,int &x,int &y){
		if(!b) return x=1,y=0,void(0);
		exgcd(b,a%b,x,y);
		int t=x;
		x=y,y=t-a/b*x;
		return ;
	}
	mt19937 rnd(time(0));
}
using namespace yzqwq;

const int N=105,M=15,p=1e8;
int n1,n2,k1,k2;
_int f[N][N][M][M];

il void solve(){
	n1=rd,n2=rd,k1=rd,k2=rd;
	for(re int k=1;k<=min(n1,k1);++k) f[k][0][k][0]=1;
	for(re int k=1;k<=min(n2,k2);++k) f[0][k][0][k]=1;
	for(re int i=1;i<=n1;++i)
	for(re int j=1;j<=n2;++j)
	for(re int kx=0;kx<=min(i,k1);++kx)
	for(re int ky=0;ky<=min(j,k2);++ky){
		if((!kx&&!ky)||(kx&&ky)) continue;
		if(kx) f[i][j][kx][ky]=(f[i][j][kx][ky]+f[i-1][j][kx-1][ky])%p;
		if(ky) f[i][j][kx][ky]=(f[i][j][kx][ky]+f[i][j-1][kx][ky-1])%p;
		if(kx==1){
			for(re int k=1;k<=min(k2,j);++k) f[i][j][kx][ky]=(f[i][j][kx][ky]+f[i-1][j][kx-1][k])%p;
		}
		if(ky==1){
			for(re int k=1;k<=min(k1,i);++k) f[i][j][kx][ky]=(f[i][j][kx][ky]+f[i][j-1][k][ky-1])%p;
		}
	}
	_int ans=0;
	for(re int k=1;k<=min(n1,k1);++k) ans=(ans+f[n1][n2][k][0])%p;
	for(re int k=1;k<=min(n2,k2);++k) ans=(ans+f[n1][n2][0][k])%p;
	printf("%lld\n",(int)ans%p);
	return ;
}

signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int t=1;while(t--)
	solve();
	return 0;
}

```


---

## 作者：ModestCoder_ (赞：0)

不知为何，这道题目我写的其实并不爽快

显然的$dp$状态，$dp_{i,j,k,l}$表示用了i个1，j个2，末尾有连续k个1，l个2

显然k与l中肯定其中一个为0，一个不为0，从这可得到边界

转移我便用了刷表法，对$dp_{i,j,k,l}$进行讨论

 - $k!=0,l=0:dp_{i,j,k,l}->dp_{i+1,j,k+1,l},dp_{i,j+1,0,1}$
 - $k=0,l!=0:dp_{i,j,k,l}->dp_{i+1,j,1,0},dp_{i,j+1,k,l+1}$

累计答案就是$ANS=\sum_{i=0}^{k1}\sum_{j=0}^{k2}dp_{n1,n2,i,j}$

Code：

```cpp
#include <bits/stdc++.h>
#define maxn 110
#define qy 100000000
using namespace std;
int n1, n2, k1, k2, dp[maxn][maxn][20][20];

inline int read(){
	int s = 0, w = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') w = -1;
	for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
	return s * w;
}

void upd(int &x, int y){ if ((x += y) >= qy) x -= qy; }

int main(){
	n1 = read(), n2 = read(), k1 = read(), k2 = read();
	dp[1][0][1][0] = dp[0][1][0][1] = 1;
	for (int i = 0; i <= n1; ++i)
	for (int j = 0; j <= n2; ++j)
	for (int k = 0; k <= min(i, k1); ++k)
	for (int l = 0; l <= min(j, k2); ++l){
		if (!k && !l || k && l) continue;
		int tmp = dp[i][j][k][l];
		if (k) upd(dp[i + 1][j][k + 1][l], tmp), upd(dp[i][j + 1][0][1], tmp); else
		upd(dp[i + 1][j][1][0], tmp), upd(dp[i][j + 1][k][l + 1], tmp);
	}
	int ans = 0;
	for (int i = 0; i <= min(n1, k1); ++i)
		for (int j = 0; j <= min(n2, k2); ++j)
			if (!i && !j || i && j) ; else upd(ans, dp[n1][n2][i][j]);
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：Coros_Trusds (赞：0)

# 题目大意

有一个 $01$ 序列，这个序列中有 $n1$ 个 $0$，$n2$ 个 $1$。如果这个序列最长连续的 $0$ 不超过 $k1$，最长连续的 $1$ 不超过 $k2$，就说这个序列是完美的。 

求完美 $01$ 序列的方案数，方案数对 $10^8$ 取模。

# 题目分析

令 $dp_{i,j,k,0/1}$ 表示有 $i$ 个 $0$,$j$ 个 $1$,末尾连续 $k$ 个 $0/1$ 的方案数。

根据定义，初始化 $dp_{1,0,1,0}\gets1,dp_{0,1,1,1}\gets 1$，表示 `0` 和 `1` 的情况。

枚举末尾为 $0$ 的状态转移方程为：

$dp_{i,j,k,0}=dp_{i-1,j,k-1,0},dp_{i,j,1,0}=dp_{i,j,1,0}+dp_{i-1,j,k,1}$。

意思是，末尾为 $0$ 时对于下一个末尾：可以再来一个 $0$，也可以换成 $1$。

末尾为 $1$ 同理。

# 代码

```cpp
//2022/3/27
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#define enter putchar(10)
#define debug(c,que) cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) cout << arr[i] << w;
#define speed_up() cin.tie(0),cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define Abs(x) ((x) > 0 ? (x) : -(x))
const int mod = 1e8;
inline int MOD(int x) {
	if(x < 0) x += mod;
	return x % mod;
}
namespace Newstd {
	char buf[1 << 21],*p1 = buf,*p2 = buf;
	inline int getc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1 ++;
	}
	inline int read() {
		int ret = 0,f = 0;char ch = getc();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getc();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getc();
		}
		return f ? -ret : ret;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;
using namespace std;

const int N1 = 105,N2 = 15;
int dp[N1][N1][N2][2];//有 i 个 0,j 个 1,末尾连续 k 个 0/1 的方案数
int n1,n2,m1,m2;
int main(void) {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	n1 = read(),n2 = read(),m1 = read(),m2 = read();
	dp[1][0][1][0] = dp[0][1][1][1] = 1;
	for (register int i = 0;i <= n1; ++ i) {
		for (register int j = 0;j <= n2; ++ j) {
			if (i >= 1) {
				for (register int k = 2;k <= m1; ++ k) {
					dp[i][j][k][0] = dp[i - 1][j][k - 1][0];
				}
				for (register int k = 1;k <= m2; ++ k) {
					dp[i][j][1][0] = MOD(dp[i][j][1][0] + dp[i - 1][j][k][1]);
				}
			}
			if (j >= 1) {
				for (register int k = 2;k <= m2; ++ k) {
					dp[i][j][k][1] = dp[i][j - 1][k - 1][1];
				}
				for (register int k = 1;k <= m1; ++ k) {
					dp[i][j][1][1] = MOD(dp[i][j][1][1] + dp[i][j - 1][k][0]);
				}
			}
		}
	}
	int ans = 0;
	for (register int i = 1;i <= m1; ++ i) ans = MOD(ans + dp[n1][n2][i][0]);
	for (register int i = 1;i <= m2; ++ i) ans = MOD(ans + dp[n1][n2][i][1]);
	printf("%d\n",ans);

	return 0;
}
```

---

