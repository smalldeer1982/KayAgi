# [USACO15FEB] Cow Hopscotch S

## 题目描述

与人类喜欢玩跳格子游戏类似，Farmer John 的奶牛们也发明了自己的版本。游戏在一个 $R \times C$ 的网格上进行（$2 \leq R,C \leq 100$），每个格子标有 $1 \ldots K$ 的整数（$1 \leq K \leq R \times C$）。奶牛从左上角出发，通过一系列有效跳跃到达右下角。跳跃被定义为有效当且仅当满足以下条件：

1. 目标格子与当前格子的数字不同  
2. 目标格子位于当前格子下方至少一行  
3. 目标格子位于当前格子右侧至少一列  

请计算从左上角到右下角的不同有效跳跃路径总数。

## 样例 #1

### 输入

```
4 4 4
1 1 1 1
1 3 2 1
1 2 4 1
1 1 1 1```

### 输出

```
5```

# 题解

## 作者：zmza (赞：9)

upd on 2024.8.23：第 $28$ 行修改为 ```for (int j = 2; j <= c; j++)```。感谢@Hollow_Knight 的指出

本题暴力的思路是：枚举每一个点，看看有哪些点可以到达这个点，这个点的方案数就是所有能到达它的点的方案数之和。

现在关键是要求有哪些点可以到达一个点了。在这个点的左上方的点都可以到达这一个点。因为题目说的是 `至少`。

至于第一个条件，在循环里特判一下就可以了。

这道题的加强版是一道蓝题，要用线段树，数据范围是 $r,c \leq 750$ ， 过不了。但是这道题的范围是 $r,n \leq100$ ，所以我们就直接暴力就行了。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
const int mod = 1e9 + 7;
using namespace std;
int a[105][105], dp[105][105];
int read()
{
	int i = 0, f = 1;
	char ch;
	for (ch = getchar(); (ch < '0' || ch > '9') && ch != '-'; ch = getchar());
	if (ch == '-')
	{
		f = -1;
		ch = getchar();
	}
	for (; ch >= '0' && ch <= '9'; ch = getchar())
		i = (i << 3) + (i << 1) + (ch ^ 48);
	return i * f;
}
signed main()
{
	int r = read(), c = read(), k = read();
	for (int i = 1; i <= r; i++)
		for (int j = 1; j <= c; j++)
			a[i][j] = read();
	dp[1][1] = 1;
	for (int i = 2; i <= r; i++)
		for (int j = 2; j <= c; j++)
			for (int t1 = 1; t1 < i; t1++)
				for (int t2 = 1; t2 < j; t2++)
					if (a[t1][t2] != a[i][j]) dp[i][j] = (dp[i][j] + dp[t1][t2]) % mod;
	printf("%lld", dp[r][c]);
	return 0;
}
```

---

## 作者：first_fan (赞：8)

### 一道USACO银题怎么能只有$\sf O(n^4)$的解法？

我们这道题考虑用线段树优化dp。

数据结构优化的dp总是十分明显，此题解中，用$\sf f[i][j]$表示从起点到第$\sf i$行,第$\sf j$列的格子合法跳跃的方案数。

转移时要严格右下方，这是转移时的难点之一，也是容易卡时间的地方，这个时候线段树就有用处了。

思路就是利用线段树维护前缀和，计算$\sf f[i][j]$时直接用总答案减去相应颜色的答案就行了。

总结一下，本题可以普通dp过，但是如果加上线段树优化，其速度将达到$\sf O(mnlogn)$，能够A掉此题的[金题版本](https://www.luogu.org/problemnew/show/P3120)。

```cpp
#include <bits/stdc++.h>
#define ri register int
#define ll long long
#define leaf ln==rn
using namespace std;
int read()
{
	int num=0;
	int flg=1;
	char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')
		{
			flg=-1;
		}
		c=getchar();
	}
	while(isdigit(c))
	{
		num=(num<<1)+(num<<3)+(c^48);
		c=getchar();
	}
	return num*flg;
}


//f[i][j]=∑f[k][ln] such that k<i&&ln<j&&corn[i][j]!=corn[k][ln]


const int maxn=1125;
struct segment_tree
{
	ll val;//自动取模,在没有负数的情况下无需过程中取模
	int l;
	int r;
} seg[20031125];

int c[2000][2000];
int sum[2000][2000];
int f[2000][2000];
int rt[4000000];
int siz;
int pre[2000];
const int mod=1000000007;

void upd(int &nd,int val,int p,int ln,int rn)
{
	if(!nd)
	{
		nd=++siz;
	}
	if(ln==rn)
	{
		seg[nd].val=(seg[nd].val+val)%mod;
		return;
	}
	int mid=(ln+rn)>>1;
	if(p<=mid)
	{
		upd(seg[nd].l,val,p,ln,mid);
	}
	else
	{
		upd(seg[nd].r,val,p,mid+1,rn);
	}
	seg[nd].val=(seg[seg[nd].l].val+seg[seg[nd].r].val)%mod;
}
int query(int nd,int l,int r,int ln,int rn)
{
	int res=0;
	if(!nd)
	{
		return 0;
	}
	if(l<=ln&&rn<=r)
	{
		return seg[nd].val;
	}
	int mid=(ln+rn)>>1;
	if(l<=mid)
	{
		res=(res+query(seg[nd].l,l,r,ln,mid))%mod;
	}
	if(r>mid)
	{
		res=(res+query(seg[nd].r,l,r,mid+1,rn))%mod;
	}
	return res;
}
int n,m,k;
int main()
{
	n=read();
	m=read();
	k=read();
	for(ri i=1; i<=n; i++)
	{
		for(ri j=1; j<=m; j++)
		{
			c[i][j]=read();
		}
	}
	for(ri i=1; i<=m; i++)
	{
		sum[1][i]=1;
	}
	f[1][1]=1;//边界条件初始化
	upd(rt[c[1][1]],1,1,1,m);

	for(ri i=2; i<=n; i++)
	{
		for(ri j=m; j>=1; j--)
		{
			int sum1=sum[i-1][j-1]%mod;
			int sum2=query(rt[c[i][j]],1,j-1,1,m)%mod;
			f[i][j]=((sum1-sum2)%mod+mod)%mod;
			upd(rt[c[i][j]],f[i][j],j,1,m);//更新
		}//转移
		for(ri j=1; j<=m; j++)
		{
			pre[j]=(pre[j-1]+f[i][j])%mod;
			sum[i][j]=(sum[i-1][j]+pre[j])%mod;
		}
	}

	return 0&printf("%d",(f[n][m]+mod)%mod);
}
/*
4 4 4
1 1 1 1
1 3 2 1
1 2 4 1
1 1 1 1
out:
5
*/
```

---

## 作者：_ouhsnaijgnat_ (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/P4825)


# 题目大意


一头奶牛从 $(1,1)$ 到 $(r,c)$，要求数字和现在的不相同且每次要走到比现位置的行和列都要大才能算合法。

求一头牛按合法地跳跃使自己到 $(r,c)$ 的方案数。

# 思路

拿到这个题，看到 $R$ 和 $C$ 都是 $\le1000$，脑子里便蹦出来暴力，准备用四层循环，时间复杂度为 $n^{\smash{4}}$ 最多为 $1$ 亿，并不会爆时间。可以使用暴力，那就很简单。


我们使用四层循环暴力解法，枚举从哪开始跳，用 $i$ 就表示行，用 $j$ 就表示列，再枚举这头奶牛跳跃到哪里，用 $s$ 就表示跳跃到的行，用 $k$ 就表示跳跃到的列。

有这样的思路，那么 $\mathit{f}_{i,j}$ 就表示跳到 $i$ 行 $j$ 列有多少种方案。

初始化：$\mathit{f}_{1,1}=1$

表示跳到 $1$ 行 $1$ 列有 $1$ 种方案，那就是不跳。

状态转移方程：$\mathit{f}_{s,k}=\mathit{f}_{s,k}+\mathit{f}_{i,j}$。

因为 $\mathit{f}_{i,j}$ 能跳到 $\mathit{f}_{s,k}$，所以 $\mathit{f}_{s,k}$ 应加上 $\mathit{f}_{i,j}$ 的方案数。

注意：$s$ 应从 $i+1$ 开始枚举，$k$ 应从 $j+1$ 开始枚举，因为跳到的行和列一定要比现在的行和列都大才算合法！

代码很丑，勿喷。

# 代码


```cpp
#include<iostream>
using namespace std;
int r,c,k;
int a[110][110],f[110][110];
int main(){
	cin>>r>>c>>k;
	for(int i=1;i<=r;i++)
		for(int j=1;j<=c;j++)
			cin>>a[i][j];
	f[1][1]=1;
	for(int i=1;i<=r;i++) 
		for(int j=1;j<=c;j++)
			for(int s=i+1;s<=r;s++) //枚举奶牛位于 (i,j) 能跳到的行。
				for(int k=j+1;k<=c;k++) //枚举奶牛位于 (i,j) 能跳到的列 。
					if(a[i][j]!=a[s][k]){//判断数字是否一样。
						f[s][k]+=f[i][j];
						f[s][k]%=1000000007;
					}
	cout<<f[r][c];//答案存在 f[r][c]。
	return 0;
}
```


债见。

---

## 作者：新手7889456 (赞：2)

一看数据范围：只有100！！！(稍微大一点都过不了)

不用想楼下dalao的线段树了

只有两个字：**暴力！**

看题意：

1.从（1, 1）跳到（k ，h）用数组dp[k][h]来表示

2.每一个状态dp[k][h]都可以更新dp[i][j] (k<=i<=n && h<=j<=m)

于是代码诞生了：

```cpp
#include<iostream>
#include<cstdio>
#define p 1000000007
using namespace std;
int n,m,k;
int map[751][751];
int dp[751][751];
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(register int i(1);i<=n;++i)
	{
		for(register int j(1);j<=m;++j){
			scanf("%d",&map[i][j]);
		}
	}
	dp[1][1]=1;//初始化
	for(register int i(1);i<=n;++i)
	for(register int j(1);j<=m;++j)//暴力枚举每一个点
	{
		for(register int k(i+1);k<=n;++k)//枚举可以更新的点
		for(register int h(j+1);h<=m;++h){
			if(map[k][h]!=map[i][j]){
				dp[k][h]+=dp[i][j];
				dp[k][h]%=p;
			}
		}
	}
	printf("%d",dp[n][m]);
	return 0;
}
```
求过。。

---

## 作者：曹老师 (赞：2)

## Sol ##

[blog食用](http://www.caolaoshi.men/index.php/archives/usaco15feb-cowhop.html)

~~记搜题……~~

其实根据题目很容易的就知道，就是一个固定的位置$(x,y)$，能决定跳到它的方案数的，是该点的左面和上面确定的区域，并且和这上面的数字不相等，通过这两个条件，我们就能确定出这个点方案数，最后的答案就在$dp(n,m)$里。

## Code ##

```
#include<iostream>
#include<cstdio>
#define mod 1000000007
using namespace std;

int n , m , k , map[105][105] , f[105][105];

int dp(int x , int y) {
    if(f[x][y])
        return f[x][y];
    for(int i=1; i<x; i++)
        for(int j=1; j<y; j++)
            if(map[i][j] != map[x][y])
                f[x][y] = (f[x][y] + dp(i , j)) % mod;
    return f[x][y];
}

int main() {
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            scanf("%d",&map[i][j]);
    f[1][1] = 1;
    printf("%d",dp(n,m));
    return 0;	
}
```


  [1]: https://www.luogu.org/problemnew/show/P4825

---

## 作者：lmz_ (赞：1)

这题可以朴素枚举+优化通过，先看数据范围 $1 \leq R,C \leq 100$，所以 $O(R^2C^2)$ 的时间必然不能通过所以说我们需要 ~~O2~~ 一些优化，我们先写出简单的枚举。

```cpp
ll f[110][110];
/**/
for(int i=1;i<r;i++)
    for(int j=1;j<=c;j++)
        for(int k=1;k<=r;k++)
            for(int l=1;l<=c;l++)
                if(i<k&&j<l)
                    f[k][l]+=f[i][j];
```
$f$ 数组就是我们的计数器，$\mathit{f}_{i,j}$ 表示在 $(i,j)$ 位置能跳过来的最大值。

我们来思考一下如何优化，我们可以发现，只有在 $i<k$ 并且 $j<l$ 的情况下可以跳到，所以我们的 $k$ 和 $l$ 的枚举范围不用从 $1$ 到 $R,C$，而是从 $i+1,j+1$ 到 $R,C$。

优化后代码：
```cpp
ll f[110][110];
/**/
for(int i=1;i<r;i++)
    for(int j=1;j<=c;j++)
        for(int k=i+1;k<=r;k++)
            for(int l=j+1;l<=c;l++)
                f[k][l]+=f[i][j];
```
审核大大辛苦了！

---

## 作者：_cmh (赞：1)

[原题传送门~](https://www.luogu.com.cn/problem/P4825)

### $\texttt{Solution}$

一道 dp 题。

设 $dp_{i,j}$ 表示牛跳到网格中的 $(i,j)$ 位置的方案数。

则可以对所有能使牛跳到 $(i,j)$ 的位置 $(k,l)$ 进行枚举。

其中枚举 $(i,j)$ 和 $(k,l)$ 各需 $\mathcal{O}(n^2)$ 的时间复杂度。

时间复杂度 $\mathcal{O}(n^4)$，可以通过此题。

### $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int N=110;
int a[N][N],dp[N][N];
int main(){
	int n,m;
	scanf("%d%d%d",&n,&m,&a[1][1]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	dp[1][1]=1;
	for(int i=2;i<=n;i++)
		for(int j=2;j<=n;j++)
			for(int k=1;k<i;k++)
				for(int l=1;l<j;l++)
					if(a[i][j]!=a[k][l])
						dp[i][j]=(dp[i][j]+dp[k][l])%mod;
	printf("%d",dp[n][m]);
	return 0;
}
```


---

## 作者：cyx20080216 (赞：1)

### 这道题应该使用动态规划
但是我们一看题目就会发现，这样做时间复杂度会达到$O(n^4)$

于是大佬们就开始用线段树等来进行优化

**可是真的需要优化吗?**

让我们算一算：

$R,C<=100$

$O(n^4)$的复杂度会使循环体被运行$10^8$次，约$530$毫秒，而且实际运算时时间会更短

所以，这道题不需要优化

**Code:**
```cpp
#include<bits/stdc++.h>
using namespace std;
template<typename type>
inline void read(type & num)
{
	num=0;
	bool flag=0;
	char ch=getchar();
	while(!(ch>='0'&&ch<='9')) flag=(ch=='-'),ch=getchar();
	while(ch>='0'&&ch<='9') num=(num<<1)+(num<<3)+(ch^'0'),ch=getchar();
	num=(flag?-num:num);
}
template<typename type>
inline void write(type num)
{
	if(num==0)
	{
		putchar('0');
		return;
	}
	char sta[30];
	short top=-1;
	if(num<0) putchar('-');
	while(num!=0) sta[++top]=(char)(num%10<0?-(num%10):num%10),num/=10;
	while(top>=0) putchar(sta[top]+'0'),top--;
}
#define M 1000000007
int r,c,k;
int maps[101][101],f[101][101];
inline void dp()
{
	f[1][1]=1;
	for(int i=1;i<=r;i++)
	{
		for(int j=1;j<=c;j++)
		{
			if(i==1&&j==1) continue;
			for(int k=1;k<i;k++)
			{
				for(int l=1;l<j;l++) if(maps[i][j]!=maps[k][l]) f[i][j]=(f[i][j]+f[k][l])%M;
			}
		}
	}
}
int main()
{
	read(r),read(c),read(k);
	for(int i=1;i<=r;i++)
	{
		for(int j=1;j<=c;j++) read(maps[i][j]);
	}
	dp();
	write(f[r][c]);
	return 0;
}
```


---

## 作者：bitterset (赞：1)

这是一道动态开点线段树的~~好题~~裸题

设 _f[i][j]_ 表示走到 _(i,j)_ 这个点的方案数，先考虑没有每次从 _A->B_ 两点权值不同这一限制，那么方程就十分显然，就是 _f[i][j]_ = _Σf[a][b]_ (其中 _1<=a<i,1<=b<j_ )，而这个，暴力计算是**O(n^4)** ，毫无疑问会TLE，这时候可以用一维前缀和优化到**O(n^3)**,二维前缀和优化到**O(n^2)**，两种均可以通过

但我们的目标远远不止这些。看看本题，暴力搜到每个点，判断左上权值不同的加上，那么这样也是O(n^4),这是最朴素的暴力。然后二维前缀和优化，这样只需要记录左上角权值等于 _a[i][j]_ 的f[x][y]之和。这样，~~由于权值<=n*m~~ 其实可以离散化的，对每个权值开一棵线段树。由于i是从上往下搜索的，那么每次插入时，可以在该权值线段树的j位置插入 _f[i][j]_ 就可以了。操作还是log级别的

时间复杂度O(n^2log)，空间复杂度O(n^2log)

---

## 作者：MikeC (赞：0)

## 分析

![](https://cdn.luogu.com.cn/upload/image_hosting/yu7lal2r.png)

如图，当计算到点 $(3,3)$ 即红色点时，这个点的方案数是所有可以跳到这个点的点的方案数之和，也就是点 $(1,1),(1,2),(2,1),(2,2)$ 即黄色点的方案数，于是我们很容易就可以得到状态转移方程，注意边界为点 $(1,1)$ 的方案数，因为显然我们会从这个点开始计算且只有开始计算这一种方式来到达点 $(1,1)$， 因此它的方案数为 $1$。

## 代码

``````cpp
#include<bits/stdc++.h>
#define int long long
const int MOD = 1000000007;
using namespace std;
int r,c,k;
int f[1001][1001],a[1001][1001];
signed main(){
//	freopen("hopscotch.in","r",stdin);
//	freopen("hopscotch.out","w",stdout);
	scanf("%lld%lld%lld",&r,&c,&k);
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			scanf("%lld",&a[i][j]);
		}
	}
	f[1][1]=1;
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			for(int m=1;m<i;m++){
				for(int n=1;n<j;n++){
					if(a[i][j]!=a[m][n]){
						f[i][j]+=f[m][n];
						f[i][j]%=MOD; 
					}
				}
			}
		}
	}
	printf("%lld",f[r][c]);
	return 0;
}
``````



---

## 作者：Otomachi_Una_ (赞：0)

这道题试了一下，发现 $O(n^4)$ 就能过了！

用 $f_{i,j}$ 表示跳到 $i$ 行 $j$ 列的方案数，每一次枚举 $i$ ， $j$ 更新 $f_{i,j}$ 最后输出即可。

## _Code_
```cpp
#include<iostream>
#include<cstring>
#include<map>
using namespace std;
const int MAXN=1e2+5;
const int MOD=1e9+7;
int n,m,p;
int a[MAXN][MAXN];
long long f[MAXN][MAXN];
int main(){
	cin>>n>>m>>p;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j];
	f[1][1]=1;
	for(int i=2;i<=n;i++)
		for(int j=2;j<=m;j++){
			for(int k=1;k<i;k++)
				for(int t=1;t<j;t++)
					if(a[i][j]!=a[k][t])
						f[i][j]+=f[k][t];
			f[i][j]%=MOD;
		}
	cout<<f[n][m];
}
```


---

## 作者：_lmz_ (赞：0)

## P4825 [USACO15FEB]Cow Hopscotch S题解
观察 $R$ 和 $C$ 的大小，都是 $\leq 100$ 的，暴力枚举起点和落点，不会超过时间限制。

这题枚举的思路，就是枚举起点和落点，再定义一个计数器$\mathit{dp}_{i,j} $ ，表示第 $i$ 行 $j$ 列上有多少种可行的到达方式。

我们假设 在第 $i$ 行，第 $j$ 列时，可以跳到第 $s$ 行，第 $k$ 列，那么， $\mathit{dp}_{i,j} $ 位置的计数器就要加上 $\mathit{dp}_{i,j}$ 位置的值。

初始化：$\mathit{dp}_{1,1}=1$。因为只有 1 种到第 1 行，第 1 列的方法只有一种，那就是不跳。

还有一个重点，就是当现在位置在第 $i$ 行，第 $j$ 列时，它只能跳到行比 $i$ 小，列也比 $j$ 小的地方。

话不多说，上代码！

AC 代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,dp[1010][1010];
int a[1010][1010];
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j];
	dp[1][1]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int s=1;s<i;s++)
				for(int k=1;k<j;k++)
					if(a[i][j]!=a[s][k])
						dp[i][j]=(dp[i][j]+dp[s][k])%int(1e9+7);
	cout<<dp[n][m];
	return 0;
}
```

---

## 作者：06ray (赞：0)

####  $   $ $  $数据范围水，直接暴力递推就能过。

#### $   $ $  $ 设$f[i][j]$表示从起点到第$i$行,第$j$列的格子合法跳跃的方案数。

#### $   $ $  $ 根据题意知，每次应该至少向右跳一格，向下跳一格，那么当牛在第$i$,$j$个格子时（不包括在起点）,它上一次所在的格子一定是在$1$ ~ $i$-$1$,$1$ ~ $j$-$1$之内的。

#### $   $ $  $ 所以，就可以直接把$1$ ~ $i$-$1$, $1$ ~ $j$-$1$的所有格子全都枚举一遍，如果第$i$,$j$个格子上的数与这个格子上的数不一样，那么就说明上一次可能在$f[i][j]$加上这个格子的方案数，即
	
   $f[i][j]$ $+$ $=$  $f[k][l];$
   
#### 其中$k$,$l$分别表示上一次所在格子的行与列。

#### 最终，答案为$f[r][c]$。注意：边界为$f[1][1]=1;$ 累加时要取模。


#### 复杂度O(N^4),是不会TLE的(~~暴力是最好的算法~~)。


#### 下面送代码：
```
#include <iostream>
using namespace std;
const int mod=1e9+7;
int a[1010][1010];//存入每个格子上的数
long long f[1010][1010];
int main()
{
	int n,m,x;
	cin>>n>>m>>x;
	f[1][1]=1;//边界，因为从起点到起点方案数为1
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=m; j++)
		{
			cin>>a[i][j];
			for(int k=1; k<i; k++)//暴力枚举
			{
				for(int l=1; l<j; l++)
				{
					if(a[k][l]!=a[i][j])
					{
						f[i][j]=(f[i][j]+f[k][l])%mod;//注意取模
					}
				}
			}
		}
	}
	cout<<f[n][m];
	return 0;
}
```






 

---

