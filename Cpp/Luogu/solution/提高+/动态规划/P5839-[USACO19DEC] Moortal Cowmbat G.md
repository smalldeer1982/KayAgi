# [USACO19DEC] Moortal Cowmbat G

## 题目描述

Bessie 玩格斗游戏真牛快打已经有很长时间了。然而，最近游戏开发者发布了一项更新，这迫使 Bessie 改变她的打法。

游戏总共使用 $M$ 个按键，标记为前 $M$ 个小写字母。Bessie 在游戏中最喜欢的组合键是一个长为 $N$ 的按键字符串 $S$。然而，由于最近的更新，现在每种组合键必须由一些“连击”所组成，其中连击的定义为相同的按键连续按下至少 $K$ 次。Bessie想要修改她最喜欢的组合键，创造一个同样长为 $N$ 的新组合键，然而这一新组合键由按键连击所组成，以适应规则的变化。

Bessie 需要消耗 $a_{ij}$ 天来训练她在组合键中某个特定的位置用按键 $j$ 来取代按键 $i$（也就是说，将 $S$ 中的某个特定的字符由 $i$ 变为 $j$ 的代价为 $a_{ij}$）。注意有可能将按键 $i$ 换成某种中间按键 $k$ 然后再从按键 $k$ 换成按键 $j$ 会比直接从按键 $i$ 换成按键 $j$ 消耗更短的时间（或者更一般地说，可能有一条起点为 $i$ 终点为 $j$ 的更改路径给出了从按键 $i$ 最终更改为按键 $j$ 的最小总代价）。

帮助 Bessie 求出她创建一个满足新要求的组合键所需要的最小天数。

## 说明/提示

在这个例子中的最优方案是将 `a` 改为 `b`，将 `d` 改为 `e`，再将两个 `e` 都改为 `c`。这总共消耗 $1+4+0+0=5$ 天，最终的组合键为 `bbccc`。

测试点性质：

测试点 $2\sim 4$ 满足 $N\le 1000$，$K\le 50$。

测试点 $5\sim 8$ 满足 $N\le 3\times 10^4$，$K\le 50$。

对于 $100\%$ 的数据，$1 \leq M \leq 26$，$1 \leq K\leq N \leq 10^5$。

供题：Eric Wei

## 样例 #1

### 输入

```
5 5 2
abcde
0 1 4 4 4
2 0 4 4 4
6 5 0 3 2
5 5 5 0 4
3 7 0 5 0```

### 输出

```
5```

# 题解

## 作者：wh_ZH (赞：10)

[本场USACO其他题目的题解](https://www.luogu.com.cn/blog/Good-ZH/usaco2019-dec-ti-xie)

~~既然都写过了就在题解区再发一遍~~

给定一个字符串和一个 $M\times M$ 的矩阵 $a$，表示可以消耗 $a_{i,j}$ 的代价把字符 $i$ 改成字符 $j$，求把原字符串改成每个连续段长度都不小于 $K$ 的最小代价。

$n,K\le 10^5,M\le 26$

首先直接用原矩阵的交换方法不一定最优，拿到手先跑一遍 floyd。

然后考虑 dp ，$f_i$ 表示前 $i$ 个中每个连续段都 $\ge k$ 的最小代价，显然有转移
$$
f_i=\min\{ f_j +cost(i,j,c)\} \ \ \ (j\le i-k)
$$

其中 $cost(i,j,c)$ 表示把 $[i,j]$ 全都改成字符 $c$ 的最小代价，这个可以前缀和预处理。

观察转移，发现可以在枚举到 $i$ 时再把 $i-k$ 的决策加进去，这样维护一个前缀 $\min$ 即可做到 $O(1)$ 转移。

复杂度 $O(n\times M)$

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=100005;
int c[30][30],f[N];
char s[N];
int sum[30][N];
int query(int x,int l,int r){
	return sum[x][r]-sum[x][l-1];
}
int mn[30];
int main (){
	freopen ("cowmbat.in","r",stdin);
	freopen ("cowmbat.out","w",stdout);
	int n,m,k;scanf ("%d%d%d",&n,&m,&k);
	scanf ("%s",s+1);
	for (int i=0;i<m;i++)
		for (int j=0;j<m;j++)
			scanf ("%d",&c[i][j]);
	for (int l=0;l<m;l++)
		for (int i=0;i<m;i++)
			for (int j=0;j<m;j++)
				if (i!=j&&j!=l&&i!=l)
					c[i][j]=min(c[i][j],c[i][l]+c[l][j]);
	for (int i=0;i<m;i++)
		for (int j=1;j<=n;j++)
			sum[i][j]=c[s[j]-'a'][i]+sum[i][j-1];
	memset (mn,0x3f,sizeof(mn));
	memset (f,0x3f,sizeof(f));f[0]=0;
	for (int i=k;i<=n;i++)
		for (int j=0;j<m;j++)
			mn[j]=min(mn[j]+c[s[i]-'a'][j],f[i-k]+query(j,i-k+1,i)),f[i]=min(f[i],mn[j]);
	printf ("%d",f[n]);
	return 0;
}
```

---

## 作者：7KByte (赞：6)

抢第一篇题解


根据数据范围和需要解决的问题，很容易想到$DP$做法(其实靠直觉


定义状态$f[i]$表示将$1-i$改成合法需要的最小天数


我们有转移方程$f[i]=min_{0<=j+k<=i}\{f[j]+val(j+1,i)\}$


边界$f[0]=0$，其中$val(i,j)$表示``将i-j``全部染成一种颜色需要的最小天数


显然我们对每种颜色跑一遍将$1-i$全部染成颜色$c$的天数，记录前缀和即可


这样$f[i]=min(f[i],sum[col][i]-sum[col][j]+f[j])$


$j$的选择太多不能直接枚举，我们发现决策集合单调递增，所以只用对每种颜色$col$记录$mx[col]$表示$sum[col][j]-f[j]$最大值即可


最终转移$f[i]=min(f[i],sum[col][i]-mx[col])$

时间复杂度$O(NM)$


```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define N 100005
using namespace std;
int n,m,k,a[30][30];
char s[N];
int sum[30][N];
void init(int col){
	rep(i,1,n)sum[col][i]=sum[col][i-1]+a[s[i]-'a'+1][col];
}
int mx[30];
int f[N];
void floyd(){
	rep(k,1,m)
	  rep(i,1,m)
	    rep(j,1,m)
		  if(i^j)a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
}
void work(){
	memset(f,0x7f,sizeof(f));
	f[0]=0;
	rep(i,k,n){
		rep(col,1,m)mx[col]=max(mx[col],sum[col][i-k]-f[i-k]);
		rep(col,1,m)f[i]=min(f[i],sum[col][i]-mx[col]);
	}
	printf("%d\n",f[n]);
}
int main(){
	//freopen("cowmbat.in","r",stdin);
	//freopen("cowmbat.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	scanf("%s",s+1);
	rep(i,1,m)rep(j,1,m)scanf("%d",&a[i][j]);
	floyd();
	rep(i,1,m)init(i);
	/*rep(i,1,m){
		rep(j,1,n)printf("%d ",sum[i][j]);
		putchar('\n');
	}*/
	work();
	return 0;
}
```

（抢进度，有问题右转评论区

---

## 作者：kuikuidadi (赞：2)

# 思路
因为题目直接给出的改键时间不一定是最短的，先跑一遍 floyd，找出一个字母改成其他字母的最小时间。再构造一个前缀表，方便我们计算批量改键的时间，最后 dp 即可求出答案。

$dp_i=\min(dp_j+cost(j+1,i,c))$，$cost$ 为 $j+1$ 到 $i$ 都变成颜色 $c$ 的代价。

然后用前缀和变一下：$\min(dp_j+c_i-c_j)$ 然后 $c_i$ 是定值，找之前最小的 $dp_j-c_j$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int f[101][101],sum[100001][101],n,m,k,dp[101],ans[1000001];
//sum数组为前缀表，dp数组代表结尾为i的改键方案的花费时间，ans数组代表改前i个键的最小时间 
char s[100001];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>k;
	cin>>s;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=m;j++){
			cin>>f[i][j];//代表把i改成j的时间 
		}
	}
	for(int l=1;l<=m;l++){//floyd
		for(int i=1;i<=m;i++){
			for(int j=1;j<=m;j++){
				if(f[i][j]>f[i][l]+f[l][j]){
					f[i][j]=f[i][l]+f[l][j];
				}
			}
		}
	}
	for(int i=1;i<=n;i++){//前缀表 
		for(int j=1;j<=m;j++){
			sum[i][j]=sum[i-1][j]+f[s[i-1]-'a'+1][j];
		}
	}
	memset(dp,0x3f,sizeof(dp));//初始化 
	memset(ans,0x3f,sizeof(ans));//初始化 
	ans[0]=0;//初始化 
	for(int i=k;i<=n;i++){
		for(int j=1;j<=m;j++){
			dp[j]=min(dp[j]+f[s[i-1]-'a'+1][j],ans[i-k]+sum[i][j]-sum[i-k][j]);
			ans[i]=min(ans[i],dp[j]);//更新最优解 
		}
	}
	cout<<ans[n];
}
```

---

## 作者：云浅知处 (赞：2)

考虑 DP，设 $f_i$ 表示调整前 $i$ 个字符的最小代价，转移可以考虑枚举最后一段截到哪里，有
$$
f_i=\min_{j\le i-k} f_j+\text{cost}(j+1,i)
$$
 其中 $\text{cost}(l,r)$ 表示区间 $[l,r]$ 变成同一个字符的最小代价。

这个可以用 $O(M^3+NM)$ 时间预处理，具体来说是做一个 $\text{Floyd}$ 然后求一下前缀和 $S(i,c)$ 表示将前 $i$ 个字符都变为 $c$ 的最小代价，那么 $\text{cost}(l,r)=\min_{c}S(r,c)-S(l-1,c)$。

直接转移的话复杂度为 $O(N^2M)$，我们考虑枚举 $c$，那么有
$$
\min_{j\le i-k}f_j+\text{cost}(j+1,i)=\min_{c\in\{\texttt{A,B,}\cdots\texttt{,Z}\}}\left(S(i,c)+\min_{j\le i-k}\left\{f_j-S(j,c)\right\}\right)
$$
那么只需要对每个 $c$ 维护 $f_j-S(j,c)$ 的前缀最小值即可。复杂度 $O(NM+M^3)$。

```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

const int MN=1e5+5;
const int MC=30;

int f[MC][MC],n,k,m,dp[MN],S[MN][MC],g[MN][MC];
string str;

signed main(void){

#ifndef ONLINE_JUDGE
	freopen("in.in","r",stdin);
#endif

	cin>>n>>m>>k;
	cin>>str;
	for(int i=1;i<=m;i++)for(int j=1;j<=m;j++)f[i][j]=read();
	for(int k=1;k<=m;k++)for(int i=1;i<=m;i++)for(int j=1;j<=m;j++)f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
	for(int x=1;x<=m;x++)for(int i=1;i<=n;i++)S[i][x]=S[i-1][x]+f[str[i-1]-'a'+1][x];
	memset(dp,63,sizeof(dp)),memset(g,63,sizeof(g));
	dp[0]=0;for(int x=1;x<=m;x++)g[0][x]=0;
	for(int i=1;i<=n;i++){
		for(int x=1;x<=m;x++)if(i>=k)dp[i]=min(dp[i],g[i-k][x]+S[i][x]);
		for(int x=1;x<=m;x++)g[i][x]=min(g[i-1][x],dp[i]-S[i][x]);
	}
	cout<<dp[n]<<endl;
	return 0;
}
```

---

## 作者：Yorg (赞：1)

# 前言
很可惜，离场切不远。

多练练 dp 吧。

# 算法

简化题意，

给定一长为 $n$ 的字符串 $S$ ，由前 $m$ 个小写字母构成，现在要求将这个字符串变换成一个由至少连续 $k$ 个相同字符构成的字符串组成的字符串（下称为 合法字符串），其中，字符 $a \to b$ 的花费为 $W_{a, b}$ 。

显然的，$W_{a, b}$ 的计算可以用 $\rm{Floyd}$ 进行 $O(m^3)$ 的计算。

考虑状态转移方程的设计，

令 $dp_{i, p}$ 表示字符串到 $i$ 结尾时，当前的结尾字符为 $p$ ，令其为合法字符串的最小花费。

令 $Cost(S_{a, b} \to p)$ 表示将字符串从 $a$ 到 $b$ 染成颜色 $p$ 的花费，这是可以前缀和优化的，预处理时间复杂度 $\mathcal{O} (mn)$ .

则有，
- 跟上之前的染色，不需要考虑长度。
- 自己单独拉出来进行染色，长度至少为 $k$ 。

$$
\left\{
    \begin{array}{lr}
        dp_{i, p} = \min\left[ dp_{j, p} + \rm{Cost} ( { S_{j + 1 \sim i} \to p })\right]\text{ }, \text{ } j < i \ , &  \\
        dp_{i, p} = \min\left[ dp_{j, q} + \rm{Cost} ( { S_{j + 1 \sim i} \to p } ) \right] \text{ }, \text{ } j \leq i - k \text{ }
    \end{array}
\right.
$$

## 分析 $1$ 式
显然的，一式完全可以转化成，
$$ dp_{i, p} =\rm{Cost}(S_{1, i} \to p) $$

这仅仅用于初始化，可以不加关注。

## 分析 $2$ 式
观察到这个式子并不好转移 （如果有人可以提供直接转移的方法，欢迎找我讨论。）

但是我们观察到，枚举当前的结尾字符是不必要的。

我们每次转移计算 $Cost$ 的时候，完全只需要全部枚举一遍求最小即可，压维。

因此化简 ($p$ 枚举可得)
$$ dp_i = \min_{j = 1}^{i - k}(dp_j + \rm{Cost}(S_{j + 1 \sim i} \to p))$$

---

总结一下，问题转化成，

初始化 (枚举 $p$)
$$ dp_{i} =\rm{Cost}(S_{1, i} \to p) $$

递推，
$$ dp_i = \min_{j = 1}^{i - k}(dp_j + \rm{Cost}(S_{j + 1 \sim i} \to p)) $$

这个式子显然只需要记录一下前缀最小值即可 $\mathcal{O}(1)$ 递推。

总时间复杂度 $\mathcal{O}(nm)$ 。

---

## 作者：zjjws (赞：1)

每块长 $x\in [k,2k-1]$，因为对于 $\ge 2k$ 的块可以看做多个小块。

设 $f_{i,j}$ 表示维护到位置 $i$，最后一个块是第 $j$ 个小写字母的最小花费。

$i\in[x,x]\cup [x+k,n]$，含义是，要么是第一个块，要么从前面找一个块接过来。

然后一段连续的区间附成同一个字母是可以前缀和预处理出来的，所以当前块费用的计算是 $\operatorname O(1)$ 的。

设 $add_{i,j}$ 表示把前 $i$ 个位置全都变成第 $j$ 个小写字母的花费。

直接按这个 DP 式正常做的话，时间复杂度为：

$$(n-2k)+(n-2k-1)+\dots+(n-3k)+k$$

$$=n\times k-\frac{5k^2}{2}+k$$

$$=-\frac{5}{2}k^2+(n+1)k$$

当 $k=\frac{n+1}{5}$ 时，$\operatorname O_{min}=\frac{(n+1)^2}{10}$。

$n\le 10^5$，好像差不多刚好的样子。

但是，别忘了还有个 $m\le 26$ 的大常数，枚举这个块和上一个块的字母，所以这个方法的极限复杂度为 $\operatorname O(m^2\times \frac{(n+1)^2}{10})$，可以达到 $6.76\times 10^{11}$。

但实际上我们发现，我们并不需要管前面的字母是什么，所以首先将 $f$ 降成一维的，用 $f_i$ 表示维护到位置 $i$ 的最小花费。

然后对于 $f_i$，我们需要用到的是 $f_j,j\in[i-(2k-1),i-k]$（实际上考虑到这里 $[0,i-k]$ 是一样的，前面看作多个小块，其实并没有这个必要），然后转移方程式为：

$$f_i=f_j+add_{i,k}-add_{j,k}$$

其中 $k$ 表示当前块枚举的是第几个小写字母。

那么就开个数组存一下每个小写字母的最佳转移费用就行了。

这么一看就是一道非常简单的 DP 题，代码也很简短。

~~蓝有点过了，应该评绿差不多~~

```cpp
#include <bits/stdc++.h>
#define LL long long
#define min(a,b) a<b?a:b
using namespace std;
const int MAX=1e5+3;
int n,m,k;
int a[27][27];
int add[27][MAX];
int f[MAX];
int min_f[26];
string s;
LL rin()
{
    LL s=0;
    char c=getchar();
    bool bj=0;
    for(;(c>'9'||c<'0')&&c!='-';c=getchar());
    if(c=='-')c=getchar(),bj=true;
    for(;c>='0'&&c<='9';c=getchar())s=(s<<1)+(s<<3)+(c^'0');
    if(bj)return -s;
    return s;
}
int main()
{
    memset(f,0x3f,sizeof(f));
    n=rin();m=rin();k=rin();
    cin>>s;
    for(int i=1;i<=m;i++)for(int j=1;j<=m;j++)a[i][j]=rin();
    for(int _=1;_<=m;_++)
    for(int i=1;i<=m;i++)
    for(int j=1;j<=m;j++)
    a[i][j]=min(a[i][j],a[i][_]+a[_][j]);
    for(int j=1;j<=m;j++)for(int i=1;i<=n;i++)add[j][i]=add[j][i-1]+a[s[i-1]-'a'+1][j];
    for(int i=k;i<=n;i++)
    {
        if(i>=(k<<1))
        {
            int now=i-k;
            for(int j=1;j<=m;j++)min_f[j]=min(min_f[j],f[now]-add[j][now]);
        }
        for(int j=1;j<=m;j++)f[i]=min(f[i],min_f[j]+add[j][i]);
        // printf("f[%d]:%d\n",i,f[i]);
    }
    printf("%d",f[n]);
    return 0;
}
```


---

## 作者：_虹_ (赞：1)

考虑将l-r换为颜色k，代价为cost_k(l,r)

显然可以转化为cost_k(1,r)-cost(1,l-1);

对于每种颜色k，最优的合法转移j，代价为dp[j]+cost_k(j,i)。

转移时枚举颜色取min.

当时发懒，直接写了堆，O(nmlogn)，把堆换成变量可以O(nm)

usaco过了，luogu需要吸口氧。

```cpp
#include <iostream>
#include <string>
#include <queue>
#include <cstdio>
using namespace std;
#define int long long
const int kmaxn=100000+5;
const int kmaxm=30;
int dp[kmaxn];
priority_queue<int,vector<int>,greater<int> > q[kmaxm];
int offset[kmaxm][kmaxn];
int a[kmaxm][kmaxm];
int n,m,K;
string s;
const int inf=1e9+7;
#define T(x) (x-'a')
signed main()
{
	cin>>n>>m>>K;
	cin>>s;
	s=" "+s;
	for(int i=0;i<m;++i)
	{
		for(int j=0;j<m;++j)
		{
			cin>>a[i][j];
		}
	}
	for(int k=0;k<m;k++)
	{
		for(int i=0;i<m;i++)
		{
      		for(int j=0;j<m;j++) 
			{
            	a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
			}
		}
	}
	for(int i=0;i<=n;++i)
		dp[i]=inf;
	for(int k=0;k<m;++k)
	{
		int cost=0;
		for(int i=1;i<=n;++i)
		{
			cost+=a[T(s[i])][k];
			offset[k][i]=cost;
		}
	}
	for(int i=0;i<m;++i)
		q[i].push(0);
	
	for(int i=K,pre=1;i<=n;++i,++pre)
	{
		dp[i]=inf;
		for(int j=0;j<m;++j)
		{
			dp[i]=min(dp[i],q[j].top()+offset[j][i]);
		}
		for(int j=0;j<m;++j)
		{
			q[j].push(dp[pre]-offset[j][pre]);
		}
	}
	cout<<dp[n]<<endl;
	return 0;
}
```


---

## 作者：vicissitudes (赞：0)

记 $f_i$ 为前 $i$ 个键合法时的最小天数。

易推得：
$$f_i = \min\  f_j + cost(j + 1, i, l)\ (1 \le j \le i - k)$$

其中 $cost(j + 1, i, l)$ 指把第 $j + 1$ 天到第 $i$ 天换成 $l$ 的最小值。
可以前缀和处理。

即：
$$f_i = \min \ f_j + sum[i][l] - sum[j][l]\ (1 \le j \le i - k)$$
时间为 $O(n^2m)$。

发现时间瓶颈在于找 $f_j - sum[j][l]$ 的最小值。容易发现有决策单调性，记 $pre[l]$ 为 $f_j - sum[j][l]$ 的最小值。

式子就优化为：
$$f_i = \min \ pre[l] + sum[i][l] \ (1 \le l \le m)$$
同时维护 $pre$ 即可。


```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10, M = 27;
typedef long long ll;

int n, m, k;
string s;
int c[M][M], num[N];
ll sum[N][M], f[N];

int main() { 
//	freopen("cowmbat.in", "r", stdin);
//	freopen("cowmbat.out", "w", stdout);
	cin >> n >> m >> k;
	cin >> s;
	for(int i = 1; i <= m; i ++) {
		for(int j = 1; j <= m; j ++) {
			cin >> c[i][j];
		}
	}
	for(int l = 1; l <= m; l ++) {
		for(int i = 1; i <= m; i ++) {
			for(int j = 1; j <= m; j ++) {
				c[i][j] = min(c[i][j], c[i][l] + c[l][j]);
			}
		}
	}
	for(int i = 0; i < s.size(); i ++) {
		char ch = s[i];
		num[i + 1] = ch - 'a' + 1;
		for(int j = 1; j <= m; j ++) sum[i + 1][j] = sum[i][j] + c[num[i + 1]][j];
	} 
	memset(f, 0x3f, sizeof f); 
	f[0] = 0;
	ll pre[30];	
	memset(pre, 0x3f, sizeof pre);
	for(int i = 1; i <= n; i ++) {	
		for(int k1 = 1; k1 <= m; k1 ++) {
			if(i - k >= 0) pre[k1] = min(pre[k1], f[i - k] - sum[i - k][k1]);
			f[i] = min(f[i], sum[i][k1] + pre[k1]);
		}
	}
	cout << f[n];
	return 0;
} 
```

---

## 作者：Purple_wzy (赞：0)

推荐一下我的博客，这里有12月月赛的全部12篇题解~~
https://www.cnblogs.com/Purple-wzy/

## C Moortal Cowmbat

题目：https://www.luogu.com.cn/problem/P5839

题解：首先观察到m很小，先O(m^3)floyd判一下两两之间的最小代价。

设f[i][j]表示处理了前i个字符，最后一堆字符为j的最小代价。

~~可以口胡一下转移方程~~

暴力转移是O(n^2m^2)的，我们无法接受。

考虑优化这个dp。

##### O(n^2m)

考虑到当前的转移并不需要知道上一次的最后一段的字母是什么，我们

可以先对i的所有的f[i][j]取个min,再进行转移。

##### O(nm)

发现对于当前的i，可以转移到它的p是从1开始的一段连续区间。

我们设f[i]表示处理完前i个字母的最小代价，sum[i][j]表示从1到i，

将所有字母都变为j的代价。

这样，转移方程就可以写为：

f[i]=min{f[p]+sum[i][j]-sum[p][j},p $\in$ [1,i-k]

枚举特定的j时，可以将sum[i][j]从这个max里提出来。

发现只需要取f[p]-sum[p][j]的min。

我们设mx[j]表示对于p $\in$ [1,i-k],f[p]-sum[p][j]的最小值。

这样，转移就变成了O(1)。具体实现还有一些小细节，看代码吧~

复杂度：O(m^3+nm)

代码：
```
#include<bits/stdc++.h>
using namespace std;
#define re register int
#define F(x,y,z) for(re x=y;x<=z;x++)
#define FOR(x,y,z) for(re x=y;x>=z;x--)
#define I inline void
#define IN inline int
typedef long long ll;
I read(int &res){
    re g=1;register char ch=getchar();res=0;
    while(!isdigit(ch)){
        if(ch=='-')g=-1;
        ch=getchar();
    }
    while(isdigit(ch)){
        res=(res<<3)+(res<<1)+(ch^48);
        ch=getchar();
    }
    res*=g;
}
const int INF=1e9+7;
char c[101000];
int n,m,k,a[101000],dis[30][30],mx[30],sum[101000][30],f[101000];
int main(){
	freopen("cowmbat.in","r",stdin);
	freopen("cowmbat.out","w",stdout);
	read(n);read(m);read(k);
	cin>>c+1;
	F(i,1,n){
		a[i]=c[i]-'a'+1;
	}
	F(i,1,m){
		F(j,1,m){
			read(dis[i][j]);
		}
	}
	F(k,1,m){
		F(i,1,m){
			F(j,1,m){
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);//Floyd
			}
		}
	}
	memset(mx,0,sizeof(mx));
	memset(sum,0,sizeof(sum));
	F(i,1,k-1){
		F(j,1,m){
			sum[i][j]=sum[i-1][j]+dis[a[i]][j];//预处理sum 
		}
	}
	F(i,k,n){
		f[i]=INF;
		if(i>=(k<<1)){
			F(j,1,m){
				mx[j]=min(mx[j],f[i-k]-sum[i-k][j]);//i<2k时不存在合法的f 
			}
		}
		F(j,1,m){
			sum[i][j]=sum[i-1][j]+dis[a[i]][j];
			f[i]=min(f[i],mx[j]+sum[i][j]);
		}
	}
	cout<<f[n];
    return 0;
}
```

---

## 作者：tiger2005 (赞：0)

### 做题全过程

在Gold T1调到自闭(实际上是没看清楚向下取整)之后开始看Gold T3。

先想到了一种$O(NKM)$的做法。

爆炸了之后继续上黑板乱涂乱画。

我写下了三个循环:

```
for i 1->N
  for j 1->K
    for k 1->M
```

想了想，把第二句话抹去了。

算了算复杂度……跑得过！

再然后就是代码过程了。

真的就这样。

---

### 题意简述

给定一个串$S$，含有M种字符,要将其修改为连续至少$K$个相同字母拼在一起的样子(就比如说$K=2$时，`aabbcc`可以，但是`aabbc`不行，因为有连续小于两次个相同字母的串`c`)。将一个字母修改到另一个字母需要一定代价。求最小代价。

---

### 做法

刚刚所说的$O(NKM)$算法实际上很好想。记录$dp_{i,j,k}$表示前$i$个字符中末尾为重复$k$次的$j$的最小花费。

这个东西会超时，而且很容易写挂，所以我放弃了这个算法。

但是我们可以想到，如果正解真的是DP，那么我们可以考虑降维。

枚举的$N$是必要的，$M$降不降无所谓，那么只有$K$了。

我们假设长度为$i$的串中末尾是连续$l$的字符$j$。那么我们可以将后面$K$个字符分出来，也就是
```
...aaaaa...a
   |<--l-->|
   ^^^^|<K>|
```

由于后面$K$个字符修改的代价是确定的，我们只需要考虑前面的最小代价即可。

观察下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/j4im24v7.png)

其中黄色表示暴力修改成同一种 字符，红色表示用dp函数求得的最小值。

如果我们可以预处理出这幅图中每一行的式子代表的值的最小值的话，我们就可以加上后面$K$个字符暴力修改的代价求出一个状态的值。用$dp2_{i,j}$表示($i$是长度，$j$是字符)。

切割一下这幅图。

![](https://cdn.luogu.com.cn/upload/image_hosting/5i35pkm6.png)

其中，绿色方框中表示的就是dp2_{i-1,j}，黑色方框中包含的是一个常数——将当前位上字符改成$j$的代价。蓝色方框就是dp函数对于所有结尾长度为$i$时的最小值(由于后面还会加上$K$个同样字符，这里用什么结尾都可以)。

综上，得到如下式子：$dp2_{i,j}=min(dp2_{i-1,j}+change(s_i\rightarrow j),min_{0\leq k \le M}dp_{i,k})$；

$dp_{i,j}=dp2_{i-K,j}+[cost\ \ to\ \ change\ \ all\ \ s_{i-K+1...i}\ \ to\ \ j]$

通过这两个式子，我们可以先求出$dp$，之后求$dp2$，从而实现了$dp$函数的计算。此时复杂度$O(NM)$。

代价矩阵跑$O(M^3)$最短路优化即可。

总复杂度：$O(M^3+NM)$

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
int M,N,K;
char ZH[100010];
int cng[26][26];
int dp[100010][26];
int dp2[100010][26];
int qzh[100010][26];
int cst(int L,int R,int B){
	int ans=0;
	for(int i=0;i<M;i++)
		ans+=(qzh[R][i]-qzh[L-1][i])*cng[i][B];
	return ans;
}
int main(){
	scanf("%d %d %d",&N,&M,&K);
	scanf(" %s",ZH+1);
	for(int i=1;i<=N;i++){
		for(int j=0;j<M;j++)	qzh[i][j]=qzh[i-1][j];
		++qzh[i][(int)ZH[i]-'a'];
	}
	for(int i=0;i<M;i++)
		for(int j=0;j<M;j++)
			scanf("%d",&cng[i][j]);
	for(int k=0;k<M;k++)
		for(int i=0;i<M;i++)
			for(int j=0;j<M;j++)
				cng[i][j]=min(cng[i][j],cng[i][k]+cng[k][j]);
	memset(dp,0x3f,sizeof(dp));
	memset(dp2,0x3f,sizeof(dp2));
	for(int j=0;j<M;j++){
		int u=0;dp2[0][j]=0;
		for(int i=1;i<K;i++){
			u += cng[(int)ZH[i]-'a'][j];
			dp2[i][j]=u;
		}
	}
	for(int i=K;i<=N;i++){
		for(int j=0;j<M;j++)
				dp[i][j]=dp2[i-K][j]+cst(i-K+1,i,j);
		int p = 0x3f3f3f3f;
		for(int j=0;j<M;j++)	p=min(p,dp[i][j]);
		for(int j=0;j<M;j++)
			dp2[i][j]=min(dp2[i-1][j]+cng[(int)ZH[i]-'a'][j],p);
	}
	int ans=2147483647;
	for(int i=0;i<M;i++)
		ans=min(ans,dp[N][i]);
	printf("%d",ans);
	return 0;
}
```

---

