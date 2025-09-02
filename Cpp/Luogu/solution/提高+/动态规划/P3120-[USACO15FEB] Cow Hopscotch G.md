# [USACO15FEB] Cow Hopscotch G

## 题目描述

与人类喜欢玩跳格子游戏类似，Farmer John 的奶牛们也发明了自己的游戏版本。尽管体重接近一吨的笨拙动物玩这个游戏几乎总会以灾难收场，但这意料之外地没有阻止奶牛们每天下午尝试玩耍的热情。

游戏在一个 $R$ 行 $C$ 列的网格上进行（$2 \leq R, C \leq 750$），每个格子标有 $1$ 到 $K$ 的整数（$1 \leq K \leq R \times C$）。奶牛从左上角的格子出发，通过一系列合法跳跃到达右下角的格子。一次跳跃被定义为合法当且仅当满足以下条件：

1. 目标格子的标签数字与当前格子不同；
2. 目标格子所在行至少比当前格子多一行；
3. 目标格子所在列至少比当前格子多一列。

请帮助奶牛计算从左上角到右下角的不同合法跳跃序列总数。

## 样例 #1

### 输入

```
4 4 4 
1 1 1 1 
1 3 2 1 
1 2 4 1 
1 1 1 1 
```

### 输出

```
5 
```

# 题解

## 作者：AlanSP (赞：16)

### 线段树优化DP
> 本文将r，c改写为n，m，请注意！  
> 
暴力DP很容易想到，把所有左上角的方案数加起来即可。  
复杂度$O(n^4)$显然通不过。  
优化：**前缀和**。  
可以考虑维护每一行，每一列，每个颜色的方案前缀和sum[i][j][k],和总的前缀和sum[i][j][0]。转移时有：
$$
dp[i][j]=sum[i][j][0]-sum[i][j][k]
$$
空间复杂度$O(nmk)$显然通不过。  
优化优化：**线段树**。  
可以发现k非常大，所以维护的前缀和十分稀疏。  
那么便可以考虑对每个颜色建立线段树。  
由于十分稀疏，所以需要动态开点。  
这里稍微解释一下动态开点：就是在访问每个节点时加上引用，更新时没有便新建，查询时没有就返回0。   
这样就可以把sum优化到一维。
#### 注意： 
在维护sum和线段树时可以采用从上到下的动态维护每一列，这样访问每一行时都是当前解。   
每次更新相当于线段树中的单点加，查询即区间和。  
这也是OI中省去一维的常见方法。~~虽然我最近才会qwq~~  
具体细节详见代码：

```cpp

#include <bits/stdc++.h>
using namespace std;
#define ll long long//记得开long long
const int N=755,mod=1000000007;
struct Tree
{
	ll sum;
	int ls,rs;
} tr[N*N*4];
int n,m,k,ans,a[N][N],cnt; 
ll dp[N][N],sum[N*N*4];

void update(int x)
{
	tr[x].sum=(tr[tr[x].ls].sum+tr[tr[x].rs].sum)%mod;//记得取模
}

inline void change(int &x,int l,int r,int pos,int c)
{
	if(!x) x=++cnt;
	if(l==r)
	{
		tr[x].sum=(tr[x].sum+c)%mod;
		return;
	}
	int mid=(l+r)>>1;
	if(pos<=mid) change(tr[x].ls,l,mid,pos,c);
	else change(tr[x].rs,mid+1,r,pos,c);
	update(x);
}

inline ll query(int x,int l,int r,int L,int R)
{
	if(!x) return 0;
	if(L<=l&&r<=R) return tr[x].sum;
	int mid=(l+r)>>1;
	ll res=0; 
	if(L<=mid) res=(res+query(tr[x].ls,l,mid,L,R))%mod;
	if(R>mid) res=(res+query(tr[x].rs,mid+1,r,L,R))%mod;
	return res;
}

int main()
{
	scanf("%d%d%d",&n,&m,&cnt);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	for(int i=1;i<m;i++) sum[i]=1;//前缀和记得是方案数
	dp[1][1]=1;change(a[1][1],1,m,1,1);//初始化，记得更改线段树
	for(int i=2;i<=n;i++)
	{
		for(int j=2;j<=m;j++) 
		{
			dp[i][j]=(sum[j-1]-query(a[i][j],1,m,1,j-1)+mod)%mod;
		}
		ll res=0;
		for(int j=2;j<=m;j++)
		{//动态更新的部分
			res=(res+dp[i][j])%mod;
			sum[j]=(sum[j]+res)%mod;
			change(a[i][j],1,m,j,dp[i][j]);
		}
	}
	printf("%lld",dp[n][m]);
	return 0;
}
```


~~是不是n,m再小一点可以插头dp？（反正我不会）~~


---

## 作者：qzp666 (赞：14)

cdq分治题

代码比较简单

思路就是把行数分治按列循环

这样我们可以不去考虑列对结果的影响

不多说了上代码

（注释我写的挺全的 ）

```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<cstdlib>
using namespace std;
const int p=1e9+7;
int n,m,k,f[755][755],a[755][755],t[562505],s[562505],Time,all;
        //f[i][j]代表方案数  t[i]代表i颜色最后出现的时间 s[i]代表i颜色出现的几次(需减掉) 
void solve(int l,int r)
{
    if(l==r)        return;
    int mid=(l+r)>>1;
    solve(l,mid);//先处理左半区间 
    ++Time;//记录更新的时间 
    all=0;//总方案数 
    for(int j=1;j<=m;++j)//按列循环 
    {
        for(int i=r;i>=mid+1;--i)//先更新右区间防止左区间对右区间的干扰 
        {
            if(t[a[i][j]]<Time)    {t[a[i][j]]=Time;s[a[i][j]]=0;}//通过更新的时间不相等来重置s数组 
            f[i][j]=((f[i][j]+all-s[a[i][j]])%p+p)%p;
        }
        for(int i=l;i<=mid;++i)
        {
            if(t[a[i][j]]<Time)    {t[a[i][j]]=Time;s[a[i][j]]=0;}//重置s数组 
            s[a[i][j]]=(s[a[i][j]]+f[i][j])%p;
            all=(all+f[i][j])%p;
        }
    }
    solve(mid+1,r);//递归处理右半区间 
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    f[1][1]=1;
    for(int i=1;i<=n;++i)for(int j=1;j<=m;++j)scanf("%d",&a[i][j]);//读入 
    solve(1,n);
    printf("%d",f[n][m]);
    return 0;
}
```

---

## 作者：ASSWECAN (赞：14)

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;这题数据貌似非常得弱，据说$n^4$暴力就可以随便过。。。但是，本蒟蒻觉得如果水过去并没有多大意思，于是自己想了一个更快的做法。

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;我觉得这题最大的难点就是转移时行和列都要严格大于原来的格子，首先，很容易想到二维线段树，但是这已经是$\Theta($ $rc$·$log_2r$·$log_2c)$了，还要考虑颜色相同的情况，明显又爆时间又爆空间。那怎么办呢？稍微换个角度思考，我们其实可以一行一行地做，算完一行后再把这一行的答案插入。这样子每次我们就只需考虑列上严格大于了。我们建立$k+1$棵线段树，其中第$1$棵记录总的答案，第$2$至$k+1$棵分别记录不同颜色的答案，这样计算$dp_{i,j}$时直接用总答案减去相应颜色的答案就行了。时间复杂度$\Theta(rc$·$log_2c)$，可是空间复杂度会达到$\Theta(rc^2)$，明显会$MLE$，所以需要动态开点，这样空间复杂度也为$\Theta(rc$·$log_2c)$了，可以快速通过。

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;我的代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
//#define usacojudge
const int md=1e9+7;
int son[10000010][2],sum[10000010],cnt;
int dp[800][800];
void add(int &x,int y)
{
	x+=y;
	if(x>=md)x-=md;
} 
void update(int &x,int l,int r,int p,int v)
{
	if(!x)x=++cnt;
	add(sum[x],v);
	if(l==r)return;
	int mid=(l+r)>>1;
	if(p<=mid)update(son[x][0],l,mid,p,v);
	else update(son[x][1],mid+1,r,p,v);
}
int query(int a,int b,int k,int l,int r)
{
	if(a>b || l>r || !k)return 0;
	if(a==l && b==r)return sum[k];
	int mid=(l+r)>>1;
	if(b<=mid)return query(a,b,son[k][0],l,mid);
	else if(a>mid)return query(a,b,son[k][1],mid+1,r);
	else return (query(a,mid,son[k][0],l,mid)+query(mid+1,b,son[k][1],mid+1,r))%md;
}
int root[640000];
int r,c,k;
int a[800][800];
int main()
{
	#ifdef usacojudge
	freopen("hopscotch.in","r",stdin);
	freopen("hopscotch.out","w",stdout);
	#endif
	scanf("%d%d%d",&r,&c,&k);
	for(int i=1;i<=r;i++)
	{
		for(int j=1;j<=c;j++)scanf("%d",&a[i][j]);
	}
	dp[1][1]=1;
	update(root[0],1,c,1,1);
	update(root[a[1][1]],1,c,1,1);
	for(int i=2;i<=r;i++)
	{
		for(int j=1;j<=c;j++)dp[i][j]=(query(1,j-1,root[0],1,c)+md-query(1,j-1,root[a[i][j]],1,c))%md;
		for(int j=1;j<=c;j++)update(root[0],1,c,j,dp[i][j]),update(root[a[i][j]],1,c,j,dp[i][j]);
	}
	printf("%d",dp[r][c]);
	return 0;
}
```

---

## 作者：lgvc (赞：12)

这是一篇不需要高级算法，数据结构的 $O(R^2C)$ 做法。

首先考虑暴力的 dp，$f_{i,j}$ 表示从 $(1,1)$ 走到 $(i,j)$ 的方案数，可以进行 $O(RC)$ 的转移，无法通过。

考虑在 dp 的时候，先枚举 $i$，再枚举 $j$，然后枚举到 $j$ 的时候把所有的第 $j-1$ 列，行数小于 $i$ 的点暴力插入（具体的，使用一个桶记录所有的用颜色 $i$ 结尾的方案数），同时维护桶内的数的和。转移就可以用和减去以自己的颜色结尾的方案数量。时间复杂度 $O(R^2C)$，需稍加常数优化并开起 O2 才可以通过。

代码：

```cpp
#include <bits/stdc++.h>
#define MOD 1000000007
static char buf[1000000],*paa=buf,*pd=buf;
#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
inline int read(void) {
	register int x(0);register char c(getchar());
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x;
}
int R,C,K,dp[759][759],a[759][759];
long long v[759*759];
signed main(void) {
	R=read();C=read();K=read();
	for(int i=1;i<=R;i++) {
		for(int j=1;j<=C;j++) {
			a[i][j]=read();
		}
	}
	dp[1][1]=1;
	for(int i=2;i<=R;i++) {
		memset(v,0,sizeof(v));
		long long as=0;
		for(int j=2;j<=C;j++) {
			for(int k=1;k<i;k++) {
				v[a[k][j-1]]+=dp[k][j-1];
				as+=dp[k][j-1];
			}
			dp[i][j]=((as-v[a[i][j]])%MOD+MOD)%MOD;
		}
	}
	printf("%d",dp[R][C]);
	return 0;
}
```

---

## 作者：UltiMadow (赞：5)

这是一道cdq分治的题

感觉楼上对本题cdq分治的做法讲的不是特别清楚，所以我来详细地讲一下

cdq分治，就是计算前一部分对后一部分的影响

我们先来康康本题的dp部分：

朴素的（$O(n^2m^2)$）的dp方程：
$$
f[i][j]=\sum_{u<i,v<j,a[i][j]!=a[u][v]}f[u][v]
$$
接下来我们要想一个方法去优化这个dp方程

就像楼上题解所说的，三个条件的题目可以联想到cdq分治

接下来，我们来考虑上面所说的三个条件：

我们可以对行数进行分治，暴力枚举列数，在枚举列的同时计算与这个格子标号相同的格子的dp值然后减掉它

我们可以每次计算一个区间$[l,r]$内$[l,mid]$对$(mid,r]$的影响（或者说贡献）

总时间复杂度：$O(nm\log n \log m)$ （本蒟蒻不会分析时间复杂度，如果有误请及时帮我纠正）

接下来就是一些细节问题了，我先把核心代码放上来再做解释（可以参考别的题解的注释阅读）：
```cpp
int a[MAXN][MAXN];
int f[MAXN][MAXN],s[MAXN*MAXN],dfn[MAXN*MAXN],tot;
void cdq(int l,int r)
{
	if(l==r)return;
	int mid=l+r>>1;cdq(l,mid);
	int sum=0;tot++;
	for(int j=1;j<=m;j++)
	{
		for(int i=mid+1;i<=r;i++)
		{
			if(dfn[a[i][j]]<tot)dfn[a[i][j]]=tot,s[a[i][j]]=0;
			f[i][j]=((f[i][j]+sum-s[a[i][j]])%p+p)%p;
		}
		for(int i=l;i<=mid;i++)
		{
			if(dfn[a[i][j]]<tot)dfn[a[i][j]]=tot,s[a[i][j]]=0;
			s[a[i][j]]=(s[a[i][j]]+f[i][j])%p;
			sum=(sum+f[i][j])%p;
		}
	}
	cdq(mid+1,r);
}
```
细节：

一般的cdq分治其实是这样的：
```cpp
void cdq(int l,int r)
{
	if(l==r)return;
	int mid=l+r>>1;
	cdq(l,mid);cdq(mid+1,r);
	...
}
```
但是，这题的分治却是：
```cpp
void cdq(int l,int r)
{
	if(l==r)return;
	int mid=l+r>>1;
	cdq(l,mid);
	...
	cdq(mid+1,r);
}
```
其他的题解并没有提及为什么右区间要放在最后再去修改

我自己的理解是这个样子的：

在每一个要修改的区间里，都要把左区间内的信息全部完整地知道才可以去更新右区间内的东西（这个应该很好理解）

在后面更新能够保证右区间的第一行是一行完整的数据（只有有了第一行才能更新后面的内容）

那么为什么右边区间的第一行是一行完整的数据呢？

因为右区间的第一行只能从左区间及左区间以前的部分更新，左区间以前的部分转移过来的早在更新这一区间之前就更新好了；要得到从左区间转移的就只能把右区间的更新放在最后了qaq

其他对于代码的解释就参见楼上的题解了qaq

---

## 作者：Leasier (赞：4)

前置芝士：[cdq 分治](https://oi-wiki.org/misc/cdq-divide/)

首先列出朴素 dp 方程：$dp_{1, 1} = 1$，$dp_{i, j} = \displaystyle\sum_{x = 1}^{i - 1} \sum_{y = 1}^{j - 1} [a_{i, j} \neq a_{x, y}] dp_{x, y}$（$i \neq 1 \operatorname{or} j \neq 1$）。

乍一看难以优化。但是这里的 dp 方程长得有点像……偏序？约束条件为 $x < i$，$y < j$ 且 $a_{i, j} \neq a_{x, y}$。

然后就可以开搞了。首先赋初值，然后固定 $i$ 这一维，对 $j$ 分治，最后减掉与 $a_{i, j}$ 相同的部分。

考虑区间 $[l, mid]$ 对区间 $(mid, r]$ 的贡献。设 $b_i$ 表示在此层递归中颜色为 $i$ 的 $dp$ 值的总和，$sum_{i, j}$ 在此层递归中**所有合法的** $dp$ 值的总和，则 $dp_{i, j} \gets dp_{i, j} + sum_{i, j} - b_{a_{i, j}}$。

注意 cdq 函数调用顺序，以及 $y$ 是**严格小于** $j$（所以要先更新 $(mid, r]$ 的 $dp$ 值）。另外，直接清空 $b_{a_{i, j}}$ 会消耗大量时间，所以我在代码里用了时间戳。

代码：
```cpp
#include <stdio.h> 

typedef long long ll;

typedef struct {
	int id;
	int type;
	int pos;
	int val;
} Node;

const int mod = 1e9 + 7;
int a[757][757], mark[570027], b[570027], dp[757][757];

void cdq(int l, int r, int c, int &id){
	if (l == r) return;
	int mid = (l + r) >> 1, sum = 0;
	cdq(l, mid, c, id);
	id++;
	for (register int i = 1; i <= c; i++){
		for (register int j = mid + 1; j <= r; j++){
			if (mark[a[i][j]] < id){
				mark[a[i][j]] = id;
				b[a[i][j]] = 0;
			}
			dp[i][j] = ((dp[i][j] + sum - b[a[i][j]]) % mod + mod) % mod;
		}
		for (register int j = l; j <= mid; j++){
			if (mark[a[i][j]] < id){
				mark[a[i][j]] = id;
				b[a[i][j]] = 0;
			}
			b[a[i][j]] = (b[a[i][j]] + dp[i][j]) % mod;
			sum = (sum + dp[i][j]) % mod;
		}
	}
	cdq(mid + 1, r, c, id);
}

int main(){
	int r, c, k, id = 0;
	scanf("%d %d %d", &r, &c, &k);
	for (register int i = 1; i <= r; i++){
		for (register int j = 1; j <= c; j++){
			scanf("%d", &a[i][j]);
		}
	}
	dp[1][1] = 1;
	cdq(1, r, c, id);
	printf("%d", dp[r][c]);
	return 0;
}
```

---

## 作者：s_a_b_e_r (赞：4)

很好的一道练记忆化的题

c[i][j].pd表示此点已经计算过

c[i][j].s表示到这点的方法总数

对每个点暴力查找i和j都比它小的所有权值不相等的所有点之和

注意初值c[1][1].s=1;c[1][1].pd=1;(不跳也是一个方法)

注意题说结果着要MOD 1000000007

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
const int p=1000000007;
int a[750][751];
struct SA{
bool pd;
int s;
}c[751][751];
int R,C,K;
int F(int i,int j){
    if(c[i][j].pd){return c[i][j].s;}
    int ans=0;
    for(int x1=1;x1<i;x1++)
     for(int y1=1;y1<j;y1++)
      if(a[i][j]!=a[x1][y1])ans=(ans+F(x1,y1))%p;
    c[i][j].s=ans;
    c[i][j].pd=1;
    return ans;
}
int main(){int ans;
    cin>>R>>C>>K;
    c[1][1].pd=1;
    c[1][1].s=1;
    for(int i=1;i<=R;i++)
     for(int j=1;j<=C;j++)cin>>a[i][j];
    ans=F(R,C);
    cout<<ans%p;
    return 0;
}
```

---

## 作者：船酱魔王 (赞：2)

# P3120 [USACO15FEB]Cow Hopscotch G 题解

## 题意回顾

在一个 $ N \times M $ 的棋盘的左上角有一枚棋子（行列号均为 $ 1 $），你每次可以将棋子移到行号和列号**严格**大于当前位置**且**权值与当前位置不同的位置，你要将棋子移到右下角的位置，问有多少种不同的移法，对 $ 10^9+7 $ 取模。每个位置的权值位于 $ [1,K] $ 之间。

$ N,M \le 750 $，$ K \le R \times C $。

## 分析

**注意，此题解所示算法及 AC 代码依赖于洛谷评测机的高速度、O2 优化的效果以及时限的宽松，不保证在所有评测机下均可通过。**

充分相信洛谷评测机的速度，坚信 $ O(N^2M) $ 可过。

设计状态 $ dp_{i,j} $ 表示走到 $ (i,j) $ 的方案数。

我们维护一个桶子 $ sum_k $ 表示在前 $ i-1 $ 行的前 $ j-1 $ 列，颜色 $ k $ 的方案数，维护变量 $ s $ 表示前 $ i-1 $ 行的前 $ j-1 $ 列总方案数，显然有 $ dp_{i,j}=s-sum_{a_{i,j}} $。每次更新第 $ j $ 列的颜色方案数和总方案数。

## 实现细节

* 注意减法的取模操作。

* 不难发现维护桶子耗时极大，又发现取模耗时极大，所以在计算 $ dp $ 数组时正常取模，在维护桶子时使用 ```long long```，不取模，可以发现因为 $ dp $ 数组每个数不超过 ```int``` 类型范围，桶子里的数不超过 ```long long``` 范围，不会发生溢出。

## AC 代码

```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;
const int N = 755;
const int mod = 1e9 + 7;
int n, m, k;
int a[N][N];
int dp[N][N];
long long sum[N * N];
long long s = 0;
int MOD(long long x) {
	return (x % mod + mod) % mod;
}
int main() {
	cin >> n >> m >> k;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			scanf("%d", &a[i][j]);
		}
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= k; j++) {
			sum[j] = 0;
		}
		s = 0;
		for(int j = 1; j <= m; j++) {
			if(i + j > 2) {
				dp[i][j] = MOD(s - sum[a[i][j]]);
			} else {
				dp[i][j] = 1;
			}
			for(int p = 1; p < i; p++) {
				sum[a[p][j]] += dp[p][j];
				s += dp[p][j];
			}
		}
	}
	cout << dp[n][m] << endl;
	return 0;
} 
```

---

## 作者：Union_Find (赞：1)

本题解包括两种做法，其中第二种拿下了目前最优解。

首先考虑朴素做法。这题是一个很显然的 dp，考虑定义 $f_{i,j}$ 表示走到 $(i,j)$ 格子的方案数。那么我们考虑转移就是 $f_{i,j} = \sum_{x<i,y<j,a_{x,y} \not = a_{i,j}} f_{x,y}$，初始状态 $f_{1,1} = 1$。

因为包含了不等于，不好优化，我们可以把它容斥掉。最后就是 $f_{i,j} = \sum_{x<i,y<j} f_{x,y} - \sum_{x<i,y<j,a_{x,y}=a_{i,j}} f_{x,y}$，而这两个式子我们可以分别处理。处理的时候就有两种做法。

## 动态开点线段树

第一个式子可以直接前缀和，考虑第二个式子。因为这个式子种要求 $a_{x,y} = a_{i,j}$，考虑可以动态开点线段树，给每种颜色开线段树维护，时间复杂度就是 $O(nm\log(nm))$，空间复杂度 $O(nm\log(nm))$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 755
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}const int P = 1e9 + 7, M = 5e7 + 5;
il int pl(int x, int y){return (x + y >= P) ? (x + y - P) : (x + y);}
il int mi(int x, int y){return (x - y < 0) ? (x - y + P) : (x - y);}
int n, m, k, a[N][N], f[N][N], s[N][N], rt[N * N], tr[M], ls[M], rs[M], ep;
void add(int &p, int l, int r, int x, int k){
	if (!p) p = ++ep;
	if (l == r) return tr[p] = pl(tr[p], k), void(0);
	int mid = (l + r) >> 1;
	if (x <= mid) add(ls[p], l, mid, x, k);
	else add(rs[p], mid + 1, r, x, k);
	tr[p] = pl(tr[ls[p]], tr[rs[p]]);
}int ask(int p, int l, int r, int nl, int nr){
	if (!p) return 0;
	if (nl <= l && r <= nr) return tr[p];
	int mid = (l + r) >> 1, ans = 0;
	if (nl <= mid) ans = pl(ans, ask(ls[p], l, mid, nl, nr));
	if (nr > mid) ans = pl(ans, ask(rs[p], mid + 1, r, nl, nr));
	return ans;
}
int main(){
	n = rd(), m = rd(), k = rd();
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) a[i][j] = rd();
	f[1][1] = s[1][1] = 1;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			if (i == 1 && j == 1) continue;
			f[i][j] = s[i - 1][j - 1];
			f[i][j] = mi(f[i][j], ask(rt[a[i][j]], 1, m, 1, j - 1));
			s[i][j] = pl(mi(pl(s[i - 1][j], s[i][j - 1]), s[i - 1][j - 1]), f[i][j]);
		}for (int j = 1; j <= m; j++) add(rt[a[i][j]], 1, m, j, f[i][j]);
	}printf ("%d\n", f[n][m]);
	return 0;
}

```

## CDQ 分治

这个式子类似于 1D/1D 的式子，我们按照行 cdq 分治，然后每次暴力处理列的关系。我们可以按照列从小到大枚举，用一个桶存每种颜色的 $f_{i,j}$ 的和。时间复杂度 $O(nm\log n)$，空间复杂度 $O(nm)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 755
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}const int P = 1e9 + 7;
il int pl(int x, int y){return (x + y >= P) ? (x + y - P) : (x + y);}
il int mi(int x, int y){return (x - y < 0) ? (x - y + P) : (x - y);}
int n, m, k, a[N][N], f[N][N], s[N * N];
void solve(int l, int r){
	if (l == r) return ;
	int mid = (l + r) >> 1;
	solve(l, mid);
	for (int i = l; i <= r; i++) for (int j = 1; j <= m; j++) s[a[i][j]] = 0;
	int res = 0;
	for (int j = 1; j <= m; j++){
		for (int i = mid + 1; i <= r; i++) f[i][j] = pl(f[i][j], mi(res, s[a[i][j]]));
		for (int i = l; i <= mid; i++) res = pl(res, f[i][j]), s[a[i][j]] = pl(s[a[i][j]], f[i][j]);
	}solve(mid + 1, r);
}
int main(){
	n = rd(), m = rd(), k = rd(), f[1][1] = 1;
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) a[i][j] = rd();
	solve(1, n), printf ("%d\n", f[n][m]);
	return 0;
}

```

---

## 作者：STUDENT00 (赞：1)

小清新暴力题。

首先，如果排除限制“B 格子的标号和 A 格子的标号不同”，是一个典中典的简单 DP。

加上限制后，考虑用加上前的得数减去“B 格子的标号和 A 格子的标号相同”的，得到正确答案。

怎么做呢？显然可以使用一个桶，对于每一行分别处理。具体的，遍历到 $(x,y)$ 时，$val_k$ 中存储的是 $\sum\limits_{i=1}^{x-1}\sum\limits_{j=1}^{y-1}[a_{i,j}=a_{x,y}]f_{i,j}$。我们在 $(i,n)\rightarrow (i+1,1)$ 时，清空 $val$ 数组；在 $(i,j)\rightarrow (i,j+1)$ 时，加入 $f_{1\sim i-1,j}$。总时间复杂度 $O(n^2m)$。

加上一些快读和卡常，即可通过。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=760;
const int mod=1000000007;
int n,m,k,a[N][N],val[N*N],f[N][N];
inline int read(){
	char ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	int x=0;
	while(isdigit(ch)) x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x;
}
inline void add(int &x,int y){
	((x+=y)>=mod?x-=mod:0);
}
inline int sub(int x,int y){
	return x-y+(x<y?mod:0);
} 
int main(){
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) a[i][j]=read();
	f[1][1]=1;
	for(int i=2;i<=n;i++){
		int res=0;
		memset(val,0,sizeof(val));
		for(int j=2;j<=m;j++){
			for(int k=1;k<i;k++) add(val[a[k][j-1]],f[k][j-1]),add(res,f[k][j-1]); 
			f[i][j]=sub(res,val[a[i][j]]);
		}
	}
	printf("%d",f[n][m]);
	return 0;
}
```

---

## 作者：lyhqwq (赞：1)

# Solution

考虑朴素 dp 。

令 $f_{i,j}$ 表示当前走到 $(i,j)$ 的方案数。

则 $f_{i,j}=\sum_{p<i,q<j,a_{p,q}\neq a_{i,j}}f_{p,q}$

但这样复杂度是错误的，我们考虑优化。

注意到 $p<i,q<j$ 是一个偏序形式，我们考虑进行 cdq 分治。

我们分治行，对于区间 $[l,r]$ ，我们可以递归计算左右两部分 $[l,mid]$ 和 $[mid+1,r]$。

同时我们还可以通过 $[l,mid]$ 的答案去转移到 $[mid+1,r]$。

我们考虑如何转移。

注意到朴素 dp 的式子是可以维护前缀和优化的。

所以我们计 $buc_{color}$ 为所有 $a_{i,j}=color$ 的 $f_{i,j}$ 的和。

$sum$ 为目前计算过的所有 $f_{i,j}$ 的和。

所以有 $f_{i,j}=sum-buc_{a_{i,j}}$。

注意每次转移之后要清空 $buc$。

# Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=755;
const int Mod=1e9+7;
int n,m,k;
int a[N][N],f[N][N],buc[N*N];
void cdq(int l,int r){
	if(l==r) return;
	int mid=(l+r)>>1;
	cdq(l,mid);
	int sum=0;
	for(int j=1;j<=m;j++){
		for(int i=mid+1;i<=r;i++){
			f[i][j]=(f[i][j]+sum-buc[a[i][j]]+Mod)%Mod;
		}
		for(int i=l;i<=mid;i++){
			buc[a[i][j]]=(buc[a[i][j]]+f[i][j])%Mod;
			sum=(sum+f[i][j])%Mod;
		}
	}
	for(int i=l;i<=r;i++){
		for(int j=1;j<=m;j++){
			buc[a[i][j]]=0;
		}
	}
	cdq(mid+1,r);
}
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	scanf("%lld%lld%lld",&n,&m,&k);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%lld",&a[i][j]);
		}
	}
	f[1][1]=1;
	cdq(1,n);
	printf("%lld\n",f[n][m]);
	return 0;
}

```


---

## 作者：I_am_Accepted (赞：1)

超级好想好推好写的 cdq 分治解法！


我们设 $f_{i,j}$ 表示到达 $(i,j)$ 的方案数。

显然有转移：
$$
f_{i,j}=\sum_{i'<i}\sum_{j'<j}[a_{i,j}\ne a_{i',j'}]f_{i',j'}
$$
发现是偏序关系，cdq 没跑了。

我们按 $i$ 分治，设 $i\in[l,mid]$ 的所有 $f_{i,j}$ 为集合 $L$，同理 $i\in(mid,r]$ 的所有 $f_{i,j}$ 为集合 $R$。

我们 $O((r-l)m)$ 计算 $L$ 对 $R$ 的贡献即可 $O(nm\log n)$ 解决原问题。

具体地，我们按 $j$ 从小到大扫描 $L$ 中的元素存入桶。扫完一列 $L$ 后更新对应右侧一列的 $R$ 中的元素（记得做完后清空桶）。

```cpp
//We'll be counting stars.
#include<bits/stdc++.h>
using namespace std;
#define For(i,j,k) for(int i=(j);i<=(k);i++)
#define Rof(i,j,k) for(int i=(j);i>=(k);i--)
#define int long long
char buf[1<<21],*p1,*p2;
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline int read() {
	int x=0,f=1;
	char c=gc();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=gc();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=gc();}
	return x*f;
}
const int mod=1000000007,N=751;
int n,m,k,a[N][N],f[N][N],g[N*N];
void solve(int l,int r){
	if(l==r) return ;
	int mid=(l+r)>>1,sum=0;
	solve(l,mid);
	For(j,1,m){
		For(i,mid+1,r) (f[i][j]+=sum-g[a[i][j]]+mod)%=mod;
		For(i,l,mid){
			(g[a[i][j]]+=f[i][j])%=mod;
			(sum+=f[i][j])%=mod;
		}
	}
	For(i,l,r) For(j,1,m) g[a[i][j]]=0;//clear bucket
	solve(mid+1,r);
}
signed main(){
	n=read(),m=read(),k=read();
	For(i,1,n) For(j,1,m) a[i][j]=read();
	f[1][1]=1;
	solve(1,n);
	printf("%lld",f[n][m]);
return 0;}
```

---

## 作者：内拉组里 (赞：0)

本文参考了题解区的几篇题解，一共讲解三种方法。

# O2

字面意思，吸了氧才能过，最暴力的一种。

来自@[lgvc](luogu://user/366807) 的[题解](https://www.luogu.com.cn/article/lu7ggo3o)。

也涉及到了本题的核心思想：容斥原理。

计算答案时不数相同标号的方案数，而是用总方案数减去相同标号方案数。

大概思路就是遍历每个格子，在遍历每一列的同时用桶记录对应每一个标号的二维前缀方案数之和与总方案数。

这么看来这题有绿都是高估了，数据实在水。

## Analyses :

总时间复杂度 $ \Theta (R^2 C) $。

总空间复杂度 $ \Theta (RC) $。

***

# CDQ

来自@[qzp666](luogu://user/29470) 的[题解](https://www.luogu.com.cn/article/lps1qwhm)。

综合一下题目条件，即求满足一下条件的点对数：
$$
\begin{cases}
	x_i \lt x_j 
	\\
	y_i \lt y_j 
	\\
	G_i \neq G_j
\end{cases}
$$
前两个条件是很明显的二维偏序，第三位则用桶代替原本的数据结构部分。

所以可以当成一个类三维偏序问题求解，将每一行作为一个节点建立区间。

值得注意的是，这里的分治顺序不是简单的后序遍历，而是中序遍历。

原因是，处理分治区间时会更新二维平面中区间内每一个点的最终方案数，且左右区间会相互影响，

所以需要根据左区间得到的每个点的方案数去计算跨区间点对右区间产生的额外方案数，然后再去递归右区间，

否则在递归右区间时得到的原始数据全为 $ 0 $，处理也就没有任何意义了，这一点模拟样例可以得出。

剩下的就和 **O2** 里的暴力差不多了。

## Analyses :

总时间复杂度 $ \Theta (CR \log{R}) $。

总空间复杂度 $ \Theta (RC) $。

***

# Segment Tree

来自@[AlanSP](luogu://user/237308) 的[题解](https://www.luogu.com.cn/article/ukh8lapu)。

思想跟 **CDQ** 差不多，横着建立线段树林。

将每一个标号作为一个根节点，但 $ k $ 很大而树内很稀疏，所以采用动态开点。

需要的操作是区间和与区间加，所以也可以用树状数组作。

开一个数组 $ p $ 记录能够被转移的格子的方案数之和，即二维前缀和。

那么能到达格子 $ (i,j) $ 的方案数 $ dp[i][j] = p[j - 1] - \sum\limits^{j - 1}_{k = 1} dp[k][j] \quad (G[i][j] = G[k][j]) $。

线段树维护 $ \sum\limits^{j - 1}_{k = 1} dp[k][j] \quad (G[i][j] = G[k][j]) $，

在转移的同时动态更新 $ p $ 数组即可～

## Details :

- 最坏情况下每次新增 $ \lceil \log{R} \rceil + 1 $ 个节点，一共会开 $ R^2 \log{R} $ 个节点，空间往 $ 10 $ 倍以上开。

## Analyses :

总时间复杂度 $ \Theta (RC \log{C}) $。

总空间复杂度 $ \Theta (kRC) \ (k \ge 10) $。

# Code :

每种方法都写了一遍，码量有点大，放在[云剪贴板](https://www.luogu.com.cn/paste/j1lk37mo)里。

---

## 作者：huhangqi (赞：0)

由于需要考虑颜色的问题，所以可以考虑将总方法减去相同颜色的方案数，以此得到本次的结果。

使用前缀和，得到此处的方案总数。

然后就需要考虑如何处理颜色的问题了，由于需要进行区间修改与查询，很容易想到使用线段树进行优化，但是按照颜色数写很多树状数组明显空间开不下。

所以使用动态开点的方法。由于一棵树上有只有几个点会被查询，所以我们通过动态开点，只处理需要处理的节点，记录下它的左右儿子即可。

动态开点在需要修改时，开一个新的点记录，查询时直接返回初始状态即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int r,c,k,a[1000][1000],pre[1000],dp[1000][1000];
const int mod=1e9+7;
struct ST{
	int c[7000000],ls[7000000],rs[7000000],cnt;
	void build(int k){
		cnt=k;
	}
	void pushup(int p){
		c[p]=(c[ls[p]]+c[rs[p]])%mod;
	}
	int New(){
		c[++cnt]=0;
		ls[cnt]=rs[cnt]=0;
		return cnt;
	}
	void change(int &p,int l,int r,int w,int v){
		if(!p)p=New();
		if(l==r)return void(c[p]=(c[p]+v)%mod);
		int mid=l+r>>1;
		if(w<=mid)change(ls[p],l,mid,w,v);
		else change(rs[p],mid+1,r,w,v);
		pushup(p);
	}
	int query(int p,int l,int r,int L,int R){
		if(!p)return 0;
		if(l>=L&&r<=R)return c[p];
		int mid=l+r>>1;
		int res=0;
		if(mid>=L)res+=query(ls[p],l,mid,L,R);
		if(mid<R)res+=query(rs[p],mid+1,r,L,R);
		res%=mod;
		return res;
	}
}seg;
signed main(){
	cin>>r>>c>>k;
	seg.build(k);
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++)cin>>a[i][j];
	}
	for(int i=1;i<=c;i++)pre[i]=1;
	dp[1][1]=1;
	seg.change(a[1][1],1,c,1,1);
	for(int i=2;i<=r;i++){
		for(int j=2;j<=c;j++){
			dp[i][j]=(pre[j-1]-seg.query(a[i][j],1,c,1,j-1)+mod)%mod;
		}
		int tmp=0;
		for(int j=2;j<=c;j++){
			tmp=(tmp+dp[i][j])%mod;
			pre[j]=(pre[j]+tmp)%mod;
			seg.change(a[i][j],1,c,j,dp[i][j]);
		}
	}
	cout<<dp[r][c];
	return 0;
}
``````

---

## 作者：wyyqwq (赞：0)

### 朴素dp

$dp_{i, j}$ 表示从 $(1, 1)$ 出发到 $(i, j)$ 的方案数，有 $O(rc)$ 的转移，总时间复杂度 $O(r^2c^2)$，通过不了。

### 优化

设 $sums$ 为 $(1, 1)$ 到 $(i - 1, j - 1)$ 的方案数和，$sumd$ 为 $(1, 1)$ 到 $(i - 1, j - 1)$ 中，最后一个颜色为 $a[i][j]$ 的方案数和，$dp_{i, j}$ 即为 $sums - sumd$。

可以在枚举 $j$ 的时候，把上一列的信息 $O(r)$ 维护一下，时间复杂度 $O(r^2 c)$。

```c++

#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e3;
const int mod = 1000000007;
int sum[N * N];
int a[N][N];
int dp[N][N];
signed main() {
    int r, c, k;
    cin >> r >> c >> k;
    dp[1][1] = 1;
    for(int i = 1; i <= r; i ++) for(int j = 1; j <= c; j ++) cin >> a[i][j];
    for(int i = 1; i <= r; i ++) {
        for(int j = 1; j <= k; j ++) sum[j] = 0;
        int sumd = 0;
        
        for(int j = 1; j <= c; j ++) {
            if(i != 1 && j != 1) {
                dp[i][j] = (sumd - sum[a[i][j]] + mod) % mod;
            }
            for(int kk = 1; kk <= i - 1; kk ++) {
                sumd += dp[kk][j];
                sum[a[kk][j]] += dp[kk][j];
            }
        }
    }
    cout << dp[r][c] % mod;
}
```

---

## 作者：1234567890sjx (赞：0)

令 $f_{i,j}$ 表示当前走到了 $(i,j)$ 的方案数 $\bmod\ 10^9+7$。很显然 $(i,j)$ 这个格点可以从所有满足 $a_{i,j}\neq a_{k,l}$ 且 $i\ge k$，$j\ge l$ 
的 $(k,l)$ 转移。

暴力，时间复杂度 $O(n^2m^2)$，可以通过弱化版。

考虑优化。记录以每一个 $(i,j)$ 为右下角 $(1,1)$ 为左上角的矩形中每一个数字对答案的贡献。`dp` 的时候正难则反，计算矩形中所有的贡献减去和当前格子的值相同的贡献就是答案。

时间复杂度 $O(n^2m)$，理论可过强化版。

但是由于值域是 $n\times m$ 级别的，所以空间复杂度 $O(n^2m^2)$，**不**可通过弱化版。

考虑滚动掉行和列。容易发现对于一个坐标 $(i,j)$：

+ 若 $j<m$，则从 $(i,j)$ 转移到 $(i,j+1)$，需要更新整个 $j+1$ 列的贡献，该情况的出现次数级别为 $n\times m$，执行次数的级别为 $m$。总的来说，该情况的时间复杂度为 $O(nm^2)$。
+ 若 $j=m$，则从 $(i,j)$ 转移到 $(i+1,1)$，需要清空整个数组，并更新第 $1$ 列的贡献。该情况的出现次数级别为 $n$，执行次数的级别为 $n\times m$。总的来说，该情况的时间复杂度为 $O(n^2m)$。

总的时间复杂度为 $O(nm\max(n,m))$，空间复杂度为 $O(nm)$。由于跑不满并且地址连续访问，吸氧之后不到 `900ms` 能跑过。

[代码](https://www.luogu.com.cn/paste/t1f8pdab)，猜猜这是谁写的。

---

## 作者：Stinger (赞：0)

很久以前就用线段树过了这题，现在刚学了 cdq 又用 cdq 写了一遍这题，所以就把两种做法都讲一下。

以下的 $n$ 指 $R$，$m$ 指 $C$。

# 朴素做法

一眼的递推，$f_{i,j}$ 表示走到格子 $(i,j)$ 的方案数，$a_{i,j}$ 为格子 $(i,j)$ 的标号。

$$f_{i,j}=\sum f_{x,y}(x<i,y<j,a_{i,j}\ne a_{x,y})$$

时间复杂度 $O(n^2m^2)$，需要优化。

# 线段树

建 $nm$ 棵线段树，第 $k$ 棵线段树维护 $a_{i,j}=k$ 的 $f_{i,j}$ 值。我们从小到大枚举行号，这样就不用考虑行的限制。

若当前计算到了 $i$ 行，第 $0$ 棵线段树维护了如下的序列：

$$\sum\limits^i_{x=1}f_{x,1},\sum\limits^i_{x=1}f_{x,2}... \sum\limits^i_{x=1}f_{x,m}$$

第 $k$ 棵线段树维护了如下的序列：

$$\sum\limits^i_{x=1}f_{x,1}(a_{x,1}=k),\sum\limits^i_{x=1}f_{x,2}(a_{x,2}=k)... \sum\limits^i_{x=1}f_{x,m}(a_{x,m}=k)$$

计算第 $i$ 行时，每个 $f_{i,j}$ 的答案即为第 $0$ 棵线段树中区间 $[1,j-1]$ 的和减去第 $a_{i,j}$ 棵线段树区间 $[1,j-1]$ 的和。

线段树要动态开点，时间复杂度 $O(nm\log m)$。

```cpp
#include <cstdio>
#define GetL(x) (ls[x] ? ls[x] : ls[x] = ++ tot)
#define GetR(x) (rs[x] ? rs[x] : rs[x] = ++ tot)

const int MX = 20000005, MOD = 1e9 + 7;
int sum[MX], ls[MX], rs[MX], tot, dp[755][755], v[755][755];
void update(const int O, const int l, const int r, const int x, const int d) {
	if (l == r) {sum[O] = (sum[O] + d) % MOD; return;}
	const int mid(l + r >> 1);
	if (x <= mid) update(GetL(O), l, mid, x, d);
	else update(GetR(O), mid + 1, r, x, d);
	sum[O] += d, sum[O] %= MOD;
}
int query(const int O, const int l, const int r, const int L, const int R) {
	if (L <= l && r <= R) return sum[O];
	int ans(0), mid(l + r >> 1);
	if (ls[O] && L <= mid) ans = query(ls[O], l, mid, L, R);
	if (rs[O] && mid < R) ans = (ans + query(rs[O], mid + 1, r, L, R)) % MOD;
	return ans;
}

int main() {
	int R, C, K;
	scanf("%d%d%d", &R, &C, &K);
	for (int i(1); i <= R; ++ i)
	for (int j(1); j <= C; ++ j)
		scanf("%d", &v[i][j]);
	tot = K;
	update(v[1][1], 1, C, 1, dp[1][1] = 1);
	update(0, 1, C, 1, 1);
	for (int i(2); i <= R; ++ i) {
		for (int j(1); j <= C; ++ j)
			dp[i][j] = (query(0, 1, C, 1, j - 1) - query(v[i][j], 1, C, 1, j - 1)) % MOD;
		for (int j(1); j <= C; ++ j) 
			update(v[i][j], 1, C, j, dp[i][j]), update(0, 1, C, j, dp[i][j]);
	}
	printf("%d", (dp[R][C] + MOD) % MOD);
	return 0;
}
```

# CDQ分治

观察那个 $(x<i,y<j,a_{i,j}\ne a_{x,y})$，除去最后那一个不等于的限制，这不就一个三维偏序嘛。

cdq 分治的时候 $i$ 这一维天然有序，$j$ 这一维 cdq 分治削掉，$a_{i,j}$ 那维是数据结构维护，所以即使是不等号也没关系。

cdq 分治里 $g_k$ 表示目前区间内所有 $a_{i,j}=k$ 的 $f_{i,j}$ 总和，$g$ 的清空需要时间戳。

时间复杂度 $O(nm\log n)$。

```cpp
#include <cstdio>
#define int long long

const int mod = 1e9 + 7;
int f[755][755], tme[755 * 755], g[755 * 755], a[755][755], n, m, now;
void CDQ(int l, int r) {
	if (l == r) return;
	int mid = l + r >> 1, sum = 0;
	CDQ(l, mid), ++ now;
	for (int j = 1; j <= m; ++ j) {
		for (int i = mid + 1; i <= r; ++ i) {
			if (tme[a[i][j]] ^ now) tme[a[i][j]] = now, g[a[i][j]] = 0;
			f[i][j] = (f[i][j] + sum - g[a[i][j]]) % mod;
		}
		for (int i = l; i <= mid; ++ i) {
			if (tme[a[i][j]] ^ now) tme[a[i][j]] = now, g[a[i][j]] = 0;
			g[a[i][j]] = (g[a[i][j]] + f[i][j]) % mod, sum = (sum + f[i][j]) % mod;
		}
	}
	CDQ(mid + 1, r);
}
signed main() {
	scanf("%lld%lld%*d", &n, &m);
	for (int i = 1; i <= n; ++ i)
	for (int j = 1; j <= m; ++ j)
		scanf("%lld", &a[i][j]);
	f[1][1] = 1, CDQ(1, n);
	printf("%lld", (f[n][m] + mod) % mod);
	return 0;
}
```

# 做法对比

第一条结果为 cdq 分治，第二条为动态开点线段树。

![](https://i.loli.net/2021/08/10/WPVvfGUyxJqzImk.jpg)

可以看到，无论耗时，内存，码量，cdq全方位吊打线段树。

---

