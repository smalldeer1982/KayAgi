# Short Colorful Strip

## 题目描述

这是F题的第一个子任务。F1和F2的区别仅在对于m和时间的限制上

有n+1种颜色标号从0到n，我们有一条全部染成颜色0的长为m的纸带。

Alice拿着刷子通过以下的过程来给纸带染色：

我们按照从1到n的顺序进行染色，进行每次染色时，我们选取一个区间[ai,bi]，0<=ai<bi<=m，并且这个区间内必定是单种颜色。

染色到最后，纸带上有各种颜色除了颜色0.给出纸带最终的状态，问有多少种不同的染色方案能到达最终状态。输出时结果模998244353。

## 样例 #1

### 输入

```
3 3
1 2 3
```

### 输出

```
5
```

## 样例 #2

### 输入

```
7 7
4 5 1 6 2 3 7
```

### 输出

```
165
```

# 题解

## 作者：ncwzdlsd (赞：15)

少见的不用搜索的纯 DP 题解 qwq。

考虑类似区间 DP 的思想，假设状态 $f(l,r)$ 为对于一个颜色相同的区间 $[l,r]$，将该区间染色成目标状态的方案数。接下来考虑如何进行状态转移。由于题目要求从 $1$ 到 $n$ 进行染色，所以我们应该从编号较小的颜色开始考虑。

对于一个状态区间 $[l,r]$，我们考虑枚举其中的子区间 $[i,j]$，把 $[i,j]$ 刷成在当前状态下可刷的最小颜色，因为保证了 $n=m$，所以这个区间内的最小值只能有一个。于是乎我们可以把区间 $[l,r]$ 分成两部分：$[l,p-1]$ 和 $[p+1,r]$。对于左面这部分区间，$f(l,p-1)=f(l,i-1)\times f(i,p-1)$；对于右面这部分区间，$f(p+1,r)=f(p+1,j)\times f(j+1,r)$。显然，对于左右这两段区间是相互独立的，于是乎我们可以分开处理。

总的状态转移方程为：

$$
f(l,r)=\sum_{i=l}^{p}\sum_{j=p}^{r}f(l,i-1)f(i,p-1)f(p+1,j)f(j+1,r)
$$

显然，统计这个式子得到答案，时间复杂度是不达标的，于是乎我们考虑如何优化这个求解过程的时间复杂度。因为前面说过，对于以 $p$ 为分界线的区间 $[l,r]$，它的左右两边是独立的，我们可以分开处理，把时间复杂度由 $O(n^4)$ 降到 $O(n^3)$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int mod=998244353,maxn=1005;
int c[maxn],f[maxn][maxn];

signed main()
{
	int n,m;cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>c[i];
	for(int i=1;i<=n+1;i++) f[i][i]=f[i][i-1]=1;
	c[0]=0x3f3f3f;
	for(int kk=1;kk<n;kk++)
		for(int i=1;i+kk<=n;i++)
		{
			int p=0,lsum=0,rsum=0;
			for(int tmp=i;tmp<=i+kk;tmp++)
				if(c[tmp]<c[p]) p=tmp;
			for(int j=i;j<=p;j++)
				lsum=(lsum+f[i][j-1]*f[j][p-1])%mod;
			for(int j=p;j<=i+kk;j++)
				rsum=(rsum+f[p+1][j]*f[j+1][i+kk])%mod;
			f[i][i+kk]=(lsum*rsum)%mod;
		}
	cout<<f[1][n];
	return 0;
}
```

---

## 作者：TainityAnle (赞：9)

[博客园](https://www.cnblogs.com/jnlc-yab0716/p/16445855.html)

[题目传送门](https://www.luogu.com.cn/problem/CF1178F1)

对于纸条，我们要把它分成多个区间涂色（对于每个区间，$l$ 表示左端点，$r$ 表示右端点）；对于颜色，是从 $1$ 到 $n$，有顺序地涂，所以应先涂小的。定一个 $p$，为区间内最小值，我们能够保证最小值有且仅有一个，因为在这道题中，$n=m$，所以每种颜色只被涂 $1$ 次。（至于 $n<m $的情况，那就在[CF1178F2](https://www.luogu.com.cn/problem/CF1178F2)）

求到的 $p$ 即为本次涂的颜色，再接着，把区间分为 $2$ 部分：$[l,p]$（左边），$[p,r]$（右边）。

接着，我们查找 $[l,p]$ 和 $[p,r]$ 这两个区间。　　　

$[l,p]$ 的值是 
$$\sum_{i=l}^{p}{\operatorname{dfs}(l,i-1)\times \operatorname{dfs}(i,p-1)}$$
$[p,r] $则是
$$\sum_{i=p}^{r}{ \operatorname{dfs}(p+1,i)\times \operatorname{dfs}(i+1,r)}$$
最后，把两个区间所得结果利用乘法原理相乘得到区间 $[l,r]$。

（好像有 DP 那味了？没错，这道题算法是搜索，但思想是 DP ）

啊，然后就做完了。

现在，肯定会有人想到暴搜（比如一开始的我），但当你高高兴兴地写好暴搜交上去——20 分， 80 的 TLE，雀食，要是直接暴搜，这题怎么会是蓝。

不过搜索确实是正解，只不过要用到剪枝（剪枝大法好）。

观察发现，许多区间被重复搜索，这就用到了记忆化，定二维数组 $f$ ，$f_{i,j}$ 存储区间 $[i,j]$ 的结果。

尽管是记忆化，但时间复杂度仍是在超时边缘（不过这道题是 3 秒还好）。

记得开 long long！！！（建议所有都开 long long，我没有写 ``` typedef long long ll;``` 的习惯，如果看着不舒服请谅解）

最后贴上代码（超短的）：

```cpp
#include<bits/stdc++.h>
using namesapce std;
long long a[505],f[505][505],n,m;
long long dfs(long long l,long long r) {
　　if(f[l][r]) return f[l][r];//记忆化，遇到有的直接返回即可
　　if(l>=r) return f[l][r]=1;//判断无意义区间
　　int p=l;
　　for(int i=l; i<=r; i++) if(a[i]<a[p]) p=i;//求p，保证a[p]是此区间中最小值
　　long long ans1=0,ans2=0;
　　for(long long i=l; i<=p; i++) ans1=(ans1+dfs(l,i-1)*dfs(i,p-1)%998244353)%998244353;//求两边子区间的值
　　for(long long i=p; i<=r; i++) ans2=(ans2+dfs(p+1,i)*dfs(i+1,r)%998244353)%998244353;//同上一行，这一行是右，上一行是左
　　return f[l][r]=ans1*ans2%998244353;//记得一定要写“=ans1*ans2%998244353”，否则就不是记忆化
}
int main() {
　　cin>>n>>m;
　　for(int i=1; i<=n; i++) cin>>a[i];
　　dfs(1,m);
　　cout<<f[1][m]%998244353;
　　return 0;
}
```


---

## 作者：zhongqijun (赞：4)


### 首先从题目发掘以下易得性质：

- 染色顺序一定，从 $1$ 到 $n$，所以对一个区间染色，一定最先对其中颜色最小的染色
- 染色的条件是对当前一段颜色相同的区间染色
- 第 $i$ 次染色必然覆盖区间 $[\min\{pos_i\},\max\{pos_i\}]$
- 设 $i$ 对区间 $S_i$ 染色， $j$ 对区间 $S_j$ 染色，$i < j$，一定有 $S_j\subsetneq S_i$ 或 $S_i\cap S_j = \varnothing$

### 考虑第一次染色

假设我们有合法的染色方案如下：
![在这里插入图片描述](https://img-blog.csdnimg.cn/4f8c9074426c4a41aecdf915f815961b.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2JlbGwwNDEwMzA=,size_16,color_FFFFFF,t_70#pic_center)
显然下一次可以染色的区间为：
![在这里插入图片描述](https://img-blog.csdnimg.cn/a0e84fee04ac48c1a5e2ae147079ec93.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2JlbGwwNDEwMzA=,size_16,color_FFFFFF,t_70#pic_center)
由此，我们可以将原纸带分成三个独立区间处理，区间之间不相互影响，所以就得到三个原问题的子问题，可以考虑递归处理。

为了求方案数，我们采用动态规划。先研究以上实例，设 $F(L,R)$ 表示将纸带的 $[L,R]$ 染成符合题意的方案数，那么在上述例子中，由乘法原理，我们有 $F(1,10) = F(1,3)\times F(4,7) \times F(8,10)$。

先考虑 $n=m$ 的情况，此时每种颜色只出现一次，设当前为第 $1$ 次染色，第 $1$ 种颜色出现在位置 $p$ 上，那么显然除了给此位置染上颜色外，还可以考虑扩张染色区间。假设在 $[l,r]$ 染色，枚举 $l$ 和 $r$ ，因为以后的染色都不能跨过颜色不同的区域，发现染色之后分成了四个子问题 $[1, l)$ 、$[l, p)$ 、$(p, r]$ 、$(r, n]$ 这四个子问题，所以有：
$$F(1,m) = \sum_{l<p,r>p} F(1,l-1)\times F(l,p-1)\times F(p+1,r)\times F(r+1,m)$$
这四个子问题和原问题（考虑第一次染色）是一样的，只是换成了考虑
区间内的第一次染色，也就是区间内编号最小的颜色。
由此，我们可以将方程推广，得到：

$$
\begin{aligned}
&x = \min_{i\in[L,R]}\{a_i\},p=\operatorname{position}(x)\\
&F(L,R) =\sum_{l<p,r>p} F(L,l-1)\times F(l,p-1)\times F(p+1,r)\times F(r+1,R)
\end{aligned}
$$

### 然后考虑更普遍的情况

在此之前，有以下性质：
1. 如果格子 $i$ 和格子$i + 1$ 在某次染色后不同色了，那么它们之后永
远不会同色；
2. 如果格子 $i$ 和格子 $i + 1$ 最后同色，那么染色过程中始终同色。

由此推出：对于题目给出的纸条的一段相同颜色的区间可以缩成一个点
所以可以把 $a$ 中连续的同色端压缩到长度 $1$ 而不影响答案
$[1, 3, 2, 2, 7, 8, 2, 5, 5, 4, 4, 4, 1, 1, 6, 1] → [1, 3, 2, 7, 8, 2, 5, 4, 1, 6, 1]$

这个结论不仅为转移方程的推广提供便利，而且为以后的算法优化与正确性提供了重要的依据。

### 那么现在考虑转移方程的推广

在更普遍的情况下，由于第 $i$ 次染色必然覆盖区间 $[\min\{pos_i\},\max\{pos_i\}]$，所以我们可以将整条纸带继续划分为三个部分 $[L,\min\{pos_i\}),[\min\{pos_i\},\max\{pos_i\}],(\max\{pos_i\},R]$。由于我们不再重复算已达到目标的区间，所以在中间这一部分将会分成若干个小区间，但是并不影响我们解题，仍将它们看作子问题递归求解即可。
![在这里插入图片描述](https://img-blog.csdnimg.cn/ad15fe18a43640fc95f0bb916f3829bd.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2JlbGwwNDEwMzA=,size_16,color_FFFFFF,t_70#pic_center)
所以根据以上推广可得：设 $p_i$ 表示当前要染的颜色 $x = \min_{i\in[L,R]}\{a_i\}$ 在目标纸带中出现的所有位置，$x$ 一共出现 $t$ 次且 $\forall 1\leqslant i\leqslant t,p_i < p_{i+1}$。
$$
\begin{aligned}
F(L,R) &=\sum_{l<p,r>p} F(L,l-1)\times F(l,p_1-1)\times F(p_1+1,p_2-1) \times \cdots \times F(p_{t-1}+1,p_t - 1) \times F(p_t+1,r)\times F(r+1,R)\\[2ex]
&=\sum_{l<p,r>p} F(L,l-1)\times F(l,p_1-1)\times \prod_{i=1}^{t-1} F(p_i+1,p_{i+1}-1) \times F(p_t+1,r)\times F(r+1,R)\\[2ex]
&= \prod_{i=1}^{t-1} F(p_i+1,p_{i+1}-1)\times \sum_{l<p,r>p} F(L,l-1)\times F(l,p_1-1)\times F(p_t+1,r)\times F(r+1,R)\\[2ex]
&=\prod_{i=1}^{t-1} F(p_i+1,p_{i+1}-1)\times \sum_{l<p} \sum_{r>p} F(L,l-1)\cdot F(l,p_1-1)\cdot ( F(p_t+1,r)\cdot F(r+1,R)\\[2ex]
&=\prod_{i=1}^{t-1} F(p_i+1,p_{i+1}-1)\times (\sum_{l<p} F(L,l-1)\cdot F(l,p_1-1))\times ( \sum_{r>p} F(p_t+1,r)\cdot F(r+1,R))
\end{aligned}
$$
以上是转移方程的推广与优化，我们可以用三次单重循环计算答案，将时间复杂度从 $O(n^4)$ 减少为 $O(n^3+m)$，但是这还不够，因为除了时间复杂度仍然较大以外，我们还没有判断哪些情况是不合法的。

首先，一种显然的不合法情况是在当前区间 DP 的时候，发现 $x$ 在本区间以外也出现了，即 $ \exists p_1<L\; \text{or}\; p_t> R $ ，这时候 $x$ 在不同颜色的区间上染色了。

让我们再次关注先前得到的“相同颜色区间可缩点”的性质，如果要使缩点后的纸带尽可能长，那么每种颜色出现的所有位置都应该尽可能的分散，但是同时要使纸带合法，那么若 $a_i \neq a_{i+1}$ ，称这为一个转折点，一次染色只可能增加两个转折点，所以压缩后如果 $m > 2n$ 那么无解。

同时，我们可以利用 $m\leqslant 2n=1000$ 的性质，在递归求解时使用记忆化的技巧，最后我们就解决了这道题。

### 参考程序
```cpp
#include<iostream>
#include<cstdio>

using namespace std;
const int inf = 0xfffffff;
typedef long long ll;
const ll modn = 998244353;
ll rec[1015][1015];
int n,m,tr[4000005],b[1000005],cnt,a[1000005],minpos[505],maxpos[505];

void Build(int now,int l,int r)
{
	if(l == r)
	{
		tr[now] = b[l];
		return ;
	}
	int mid = (l+r)>>1;int lson = now<<1;int rson = lson + 1;
	Build(lson,l,mid);
	Build(rson,mid+1,r);
	tr[now] = min(tr[lson],tr[rson]);
	return ;
}

int Q(int now,int l,int r,int x,int y)
{
	if(l > y || r < x) return inf;
	if(x <= l && r <= y) return tr[now];
	int mid = (l+r)>>1;int lson = now<<1;int rson = lson + 1;
	int res = inf;
	res = min(res,Q(lson,l,mid,x,y));
	res = min(res,Q(rson,mid+1,r,x,y));
	return res; 
}

ll F(int l,int r)
{
	if(l > r) return 1;
	if(rec[l][r] != -1) return rec[l][r]%modn;
	int minx = 0;
	if(l == r) minx = b[l];
	else minx = Q(1,1,cnt,l,r);
	if(minpos[minx] < l || maxpos[minx] > r)
	{
		rec[l][r] = 0;
		return 0;
	}
	if(l == r)
	{
		rec[l][r] = 1;
		return 1;
	}
	int pp = 0;ll res = 0;ll res1 = 0;ll kres = 1;ll res2 = 0;
	pp = minpos[minx] + 1;
	for(int i = minpos[minx] + 1;i <= maxpos[minx];i ++)
		if(b[i] == minx)
		{
			kres = (kres%modn * F(pp,i - 1)%modn)%modn;
			if(kres == 0)
			{
				rec[l][r] = 0;
				return 0;
			}
			pp = i + 1;
		}
	for(int i = l;i <= minpos[minx];i ++)
		res1 = (res1%modn + (F(l,i - 1)%modn * F(i,minpos[minx] - 1)%modn)%modn)%modn;
	for(int j = maxpos[minx];j <= r;j ++)
		res2 = (res2%modn + (F(maxpos[minx] + 1,j)%modn * F(j + 1,r)%modn)%modn)%modn;
	res = ((kres%modn * res1%modn)%modn * res2%modn)%modn;
	rec[l][r] = res%modn;
	return res%modn;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= m;i ++) scanf("%d",&a[i]);
	for(int i = 0; i <= n;i ++) minpos[i] = inf,maxpos[i] = 0;
	cnt ++;
	b[1] = a[1];
	for(int i = 1;i <= m;i ++)
		if(b[cnt] != a[i])
		{
			cnt ++;
			b[cnt] = a[i];
		}
	if(cnt > (n<<1))
	{
		printf("0");
		return 0;
	}
	Build(1,1,cnt);
	for(int i = 1;i <= cnt;i ++)
	{
		minpos[b[i]] = min(minpos[b[i]],i);
		maxpos[b[i]] = max(maxpos[b[i]],i);
	}
	for(int i = 1;i <= cnt;i ++)
		for(int j = 1;j <= cnt;j ++)
			rec[i][j] = -1;
	printf("%lld",F(1,cnt)%modn);
	return 0;
}
```


---

## 作者：_fairytale_ (赞：3)

考虑区间 DP。

设 $dp_{i,j}$ 表示把区间 $[i,j]$ 染成最终状态的方案数。

不难想到边界 $dp_{i,i}=1$。

接下来我们找到 $[l,r]$ 这个区间的最小值，记它的位置为 $pos$（这里我用了 ST 表实现，直接找也是可以的），用 $pos$ 把这个区间分为两部分 $[l,pos-1]$ 和 $[pos+1,r]$ ，记 $[l,pos-1]$ 这个区间的方案数为 $lsum$，$[pos+1,r]$ 这个区间的方案数为 $rsum$。

显然，$dp_{l,r}=lsum \times rsum$ 。

接下来我们通过在左区间枚举一个 $i$ 作为分界线来计算 $lsum$。

$lsum=\sum_{pos-1}^{i=l-1}dp_{l,i}\times dp_{i+1,pos-1}$

$i$ 为啥从 $l-1$ 开始？

因为最左边可以啥都不选。

因此，我们还需要把 $dp_{i,i-1}$ 初始化为 $1$。

右区间同理。

最后的 $dp_{1,n}$ 即为答案。

时间复杂度 $\mathcal O(n^3)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define re register
#define maxn 510
#define mod 998244353
using namespace std;
int T;
int n,m;
int arr[maxn];
int ans;
int dp[maxn][maxn];
struct Sparse_table {
	int f[maxn][10];
	inline void create() {
        for(re int i=1;i<=m;++i)f[i][0]=i;
		int k=log2(m);
		for(re int j=1; j<=k; ++j) {
			for(re int i=1; i+(1<<j)-1<=m; ++i) {
				f[i][j]=arr[f[i][j-1]]<arr[f[i+(1<<(j-1))][j-1]]?f[i][j-1]:f[i+(1<<(j-1))][j-1];
			}
		}
	}
	inline int query(int l,int r){
		int k=log2(r-l+1);
		return arr[f[l][k]]<arr[f[r-(1<<k)+1][k]]?f[l][k]:f[r-(1<<k)+1][k];
	}
}ST;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m;
	for(re int i=1; i<=m; ++i) {
		cin>>arr[i];
	}
	for(re int i=0;i<=m;++i)dp[i+1][i]=dp[i][i]=1;
	ST.create();
	for(re int len=2;len<=n;++len){
		for(re int l=1;l+len-1<=n;++l){
			int r=l+len-1;
            int pos=ST.query(l,r);
            int lsum=0,rsum=0;
		    for(re int i=l-1;i<=pos-1;++i){
		    	lsum=(lsum+dp[l][i]*dp[i+1][pos-1]%mod)%mod;
			}
			for(re int i=pos;i<=r;++i){
				rsum=(rsum+dp[pos+1][i]*dp[i+1][r]%mod)%mod;
			}
			dp[l][r]=lsum*rsum%mod;
		}
	}
	cout<<dp[1][n];
	return 0;
}
```

---

## 作者：bloodstalk (赞：3)

## Description

给定 $0$ 到 $n$ 共 $n+1$ 种颜色，现有 $m$ 段初始时刻颜色都是 $0$ 的纸，对这张纸的段进行操作，第 $i$ 次操作会选择第 $l$ 段到第 $r$ 段纸进行区间染色，条件是这段此时必须为同种颜色，染为 $i$。给出最终的每一段的颜色，问共有多少种染色方案。

$n=m\leq500$,保证 $c_i$ 是一个 $1$ 到 $n$ 的排列。

## Solution
妙妙题。

首先我们可以观察到一个很强的性质：第 $i$ 次操作会选择一个区间，前提是**这一段必须是同种颜色**。这说明了，颜色的连续段**只会分裂到越来越小，而不会合并**。所以假设我们现在对于一个区间，有一个染色状态，那么它能被染成答案区间，**当且仅当这个区间内的所有颜色小于答案区间中所有颜色的最小值**，我们可以根据这个，来设我们的 DP 状态。

设 $f(l,r)$ 表示将区间 $[l,r]$ 的颜色状态全部都是小于该区间最终颜色 $\min$ 的方案，记 $\min$ 的位置是 pos，那么我们下一步就是把 $[i,j]$ 染成 pos 位置上的颜色，其中 $l\leq i\leq pos \leq j \leq r$，这样我们就把答案区间划分成了 $f(l,i-1),f(i,pos-1),f(pos+1,j),f(j+1,r)$ 这四个区间，枚举 $i,j$ 即可做到 $O(n^4)$：

$$
f(l,r) =\sum_{i=l}^{pos}\sum_{j=pos}^{r}f(l,i)\times f(i,pos-1) \times f(pos+1,r) \times f(j+1,r)
$$

但是这样还过不去，考虑优化。我们发现，$i,j$ 的取值其实是互不影响的，因此，我们只需要把 $i,j$ 分开枚举，分开计算左右两边的贡献，最后乘起来就行了，这样就是 $O(n^3)$ 的了，可以通过。

需要注意的一个小点是，因为 $i,j$ 是可以顶到左右边界的，所以我们上方的转移方程可能会出现 $f(i,i-1)$ 这样的情况，这时我们把 $f(i,i-1)$ 设为 $1$ 即可，因为这样也是合法的。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define ll long long
#define next nxt
#define re register
#define il inline
const int N = 5e2 + 5;
const int mod = 998244353;
using namespace std;
int max(int x,int y){return x > y ? x : y;}
int min(int x,int y){return x < y ? x : y;}

int n,m,pos;
int color[N];
ll ans,lsum,rsum,f[N][N];

il int read()
{
	int f=0,s=0;
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f |= (ch=='-');
	for(; isdigit(ch);ch=getchar()) s = (s<<1) + (s<<3) + (ch^48);
	return f ? -s : s;
}

signed main()
{
	n = read() , m = read();//可以观察到颜色的连续段只会分裂而不会合并
	color[0] = 501;//这样就可以设f[l][r]表示区间[l,r]全部都是小于区间最终颜色min的方案，记min的位置是pos
	for(re int i=1;i<=n;i++) color[i] = read() , f[i][i] = 1;//然后就可以枚举l,r，满足l<=pos<=r，保证最终结果是对的
	for(re int i=1;i<=n+1;i++) f[i][i-1] = 1;//然后就是n^4的做法，通过分开枚举l和r可以做到n^3
	for(re int len=2;len<=n;len++)
	{
		for(re int l=1;l<=n-len+1;l++)
		{
			int r = l + len - 1;
			pos = 0;
			for(re int k=l;k<=r;k++) if(color[pos] > color[k]) pos = k;
			lsum = rsum = 0;
			for(re int k=l;k<=pos;k++) lsum = (lsum + f[l][k-1] * f[k][pos-1]) % mod;
			for(re int k=pos;k<=r;k++) rsum = (rsum + f[pos+1][k] * f[k+1][r]) % mod;
			f[l][r] = (f[l][r] + lsum * rsum) % mod;
		}
	}
	cout << f[1][n];
	return 0;
}
```

---

## 作者：Mihari (赞：2)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF1178F1)

# 题解

题目所要求的是从小到大染色，我们不妨顺着这个顺序对方案数进行统计

设 $f[l][r]$ 为**区间 $[l,r]$ 目前颜色一致（不然无法进行染色）**，将 $[l,r]$ 染成**目标状态**的方案数，由于我们先染最小编号的颜色，不妨记最小颜色的编号为 $p$，这个 $p$ 可以预处理出来：

```cpp
inline void Solve_p(){
    int minn;
    rep(i,1,n)rep(j,i,n){
        minn=INF;
        rep(k,i,j)if(c[k]<minn)
            minn=c[k],p[i][j]=k;
    }
}
```

枚举最小颜色填入的区间为 $[i,j]$，而最后位置 $p$ 要和目标状态一致，即保持为最小的颜色，那么我们所枚举的这个 $[i,j]$ 一定要使 $p\in [i,j]$，不然无法保证和目标状态一致。

而后，由于 $[l,p-1]$ 和 $[p+1,r]$ 都要染成其他的颜色，而我们目前已经将 $[i,j]$ 染成最小颜色，所以我们整理一下区间 $[l,r]$ 中有哪些区间同色，可以继续染色：$[i,j]$，$[l,i-1]$，$[j+1,r]$，而我们要保证点 $p$ 不染成其他颜色，所以要将 $p$ 从 $[i,j]$ 中去掉，那么就是以下四个区间：
$$
[l,i-1],[i,p-1],[p+1,j],[j+1,r]
$$
由排列组合，我们最后的转移即为
$$
f[l][r]=\sum_{i=l}^{p}\sum_{j=p}^{r}f[l][i-1]\times f[i][p-1]\times f[p+1][j]\times f[j+1][r]
$$
注：此处定义当 $i>j$ 时，$f[i][j]=1$

显然这个做法是 $\mathcal O(n^4)$ 的，考虑对转移进行变换
$$
f[l][r]=\sum_{j=p}^{r}f[p+1][j]\times f[j+1][r]\times \left [\sum_{i=l}^{p}f[l][i-1]\times f[i][p-1] \right ]
$$
发现前一半和后一半独立，那么我们只需记 $sum[l][r]=\sum_{i=l}^{p}f[l][i-1]\times f[i][p-1]$，显然这个 $sum$ 可以 $\mathcal O(n)$ 处理，那么转移为
$$
f[l][r]=sum[l][r]\times\left [ \sum_{j=p}^{r}f[p+1][j]\times f[j+1][r]\right ]
$$
这个就可以 $\mathcal O(n)$ 做了，总体即为 $\mathcal O(n^3)$

对于最开始的情况，所有点都是颜色 $0$，故 `dfs(1,n)` 

# 代码

```cpp
https://www.cnblogs.com/Arextre/p/13393333.html
```

---

## 作者：xuantianhao (赞：1)

# [Short Colorful Strip](https://www.luogu.com.cn/problem/CF1178F1)

考虑设 $f[i,j]$ 表示：假设区间 $[i,j]$ 里面一开始所有格子的颜色都是相同的，那么，染成目标状态共有多少种染法。

我们找到 $[i,j]$ 中最小的那个颜色，设为 $mp$。则显然，我们下一步要染上 $mp$ 这种颜色。

设最终在位置 $p_{mp}$ 上染上了颜色 $mp$。则我们可以在所有这样的区间 $[k,l]$ 上染上 $mp(i \le k \le p_{mp} \le l \le j)$。

或许你会以为这意味着 $f[i,j]=\sum\limits_{k=i}^{p_{mp}}\sum\limits_{l=p_{mp}}^jf[i,k-1] \times f[k,l] \times f[l+1,j]$。

但是，这样是错误的，因为当 $[k,l]=[i,j]$ 时，$f[i,j]$ 便无法从子状态转移过来！

我们考虑拆开 $f[k,l]$。因为再往后的染色中，位置 $p_{mp}$ 一定没有再被染色过，因此有 $f[k,l]=f[k,p_{mp}-1] \times f[p_{mp}+1,l]$。

则 

$$f[i,j]=\sum\limits_{k=i}^{p_{mp}} \sum\limits_{l=p_{mp}}^{j} f[i,k-1] \times f[k,p_{mp}-1] \times f[p_{mp}+1,l] \times f[l+1,j]$$

特殊定义一下，对于 $f[i,j]$，如果 $i>j$，则 $f[i,j]=1$。这也是为了转移的正确（在应用上述式子时可能会调用到这样的 $f[i,j]$。

上面的转移是 $O(n^4)$ 的；但当我们拆开两个 $\sum$，就可以把它化成 $O(n^3)$ 的。

$$f[i,j]=(\sum\limits_{k=i}^{p_{mp}}f[i,k-1] \times f[k,p_{mp}-1]) \times (\sum\limits_{l=p_{mp}}^jf[p_{mp}+1,l] \times f[l+1,j])$$

前后两个括号内的内容互不干涉，故可以分开计算。

复杂度 $O(n^3)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
const int N=510;
int n,m;
int num[N],f[N][N];
inline int read(){
    char c=getchar();int f=1,x=0;
    while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
int main(){
    n=read();m=read();
    for(int i=1;i<=n;i++) num[i]=read();
    for(int i=1;i<=n+1;i++)for(int j=0;j<i;j++) f[i][j]=1;
    for(int i=1;i<=n;i++) f[i][i]=1;
    for(int l=2;l<=n;l++){
		for(int i=1,j=i+l-1;j<=n;i++,j++){
		    int x=i,A=0,B=0;
		    for(int k=i;k<=j;k++) if(num[k]<=num[x]) x=k;
		    for(int k=x;k>=i;k--) (A+=(1LL*f[i][k-1]*f[k][x-1]%mod))%=mod;
		    for(int k=x;k<=j;k++) (B+=(1LL*f[x+1][k]*f[k+1][j]%mod))%=mod;
		    f[i][j]=1LL*A*B%mod;
		}
	}
    printf("%d\n",f[1][n]);
    return 0;
} 
```


---

## 作者：xxx2022 (赞：1)

# CF1178F1题解

根据题意，每次选择一个区间染色，我们可以发现这道题满足了区间 dp 的一些性质，即区间答案可以合并，大区间的答案可以由小区间的答案更新而来。那么我们就可以设 $f_{i,j}$ 表示区间 $i$ 到 $j$ 的答案，那么接下来就考虑如何转移。然后考虑到题目要求从 $1$ 到 $n$ 进行染色，所以我们转移的时候先找到这段区间中颜色最小的一个地方，将其位置编号记为 $pos$，那么 $f_{i,j}$ 的答案则从 $\left[i,k-1\right]$,
$\left[k,pos-1\right]$,$\left[pos+1,l\right]$,
$\left[l+1,j\right]$ 这四个区间更新而来，转移的时候枚举 $k，l$，时间复杂度 $O(n^4)$，还不足以通过本题。

考虑优化这个算法，注意到 $pos$ 两边对答案的贡献是互不影响的，所以转移时可以分开计算 $pos$ 左右的答案，将两边的答案相乘即可实现转移，时间复杂度 $O(n^3)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=998244353;
const int inf=1e9;
const int N=510;
inline int read(){
	int f=1,w=0;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')	f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		w=(w<<1)+(w<<3)+(c^48);
		c=getchar();
	}
	return f*w;
}
int c[N];
int f[N][N];
int n,m; 
signed main(){
	n=read();m=read();
	for(int i=1;i<=n;i++){
		c[i]=read();
	}
	for(int i=1;i<=n+1;i++){
		f[i][i]=1;
		f[i][i-1]=1;//注意，在转移时可能出现第二维编号比第一维小1的情况 
	}
	for(int len=1;len<n;len++){
		for(int i=1;i+len<=n;i++){
			int j=i+len;
			int pos;
			int minn=inf;
			for(int k=i;k<=j;k++){
				if(c[k]<minn){
					minn=c[k];
					pos=k;
				}
			}
			int f1=0;
			for(int k=i;k<=pos;k++){
				f1=(f1+f[i][k-1]*f[k][pos-1])%mod;
			}
			int f2=0;
			for(int k=pos;k<=j;k++){
				f2=(f2+f[pos+1][k]*f[k+1][j])%mod;;    
			}
			f[i][j]=f1*f2%mod;
		}
	}
	cout<<f[1][n]<<endl;
	return 0;
}
```


---

## 作者：Wind_love (赞：0)

## 思路
很明显这是一道区间动规，但是直接推方程有点麻烦，所以我们选择记忆化搜索来实现本题。  
对于一个区间 $[l,r]$，我们设 $dp_{l,r}$ 表示该区间的方案数。  
染色的时候，按照标号从小到大按顺序染色。所以我们从颜色编号最小的位置开始染色。先找到编号最小的颜色的位置 $p$，那么这个区间就被分为了两部分。  
也就是说，整个区间被分成 $[l,p]$，$[p,r]$ 两部分。  
我们需要枚举 $i$，$j$，$i$ 在左侧区间，$j$ 在右侧区间，将区间 $[i,j]$ 这个区间染成 $p$ 的颜色。  
将区间 $[l,i-1]$，$[i,p-1]$，$[p+1,j]$，$[j+1,r]$ 的方案数设为 $A$，$B$，$C$，$D$，那么总的方案数根据加乘原理可知为： $\sum{AB}\times\sum{CD}$。  
这样，本题就解决了，最后加上记忆化，就完成了。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int n,m;
int a[1005],f[1005][1005];
int dfs(int l,int r){
	if(l>=r)return 1;
	if(f[l][r])return f[l][r];
	int ans1=0,ans2=0,ans3=0,ans4=0,minn=1e9,minp;
	for(int i=l;i<=r;i++){
		if(a[i]<minn){
			minn=a[i];
			minp=i;
		}
	}
	for(int k=l;k<=minp;k++){
		ans1+=dfs(l,k-1)*dfs(k,minp-1);
		ans1%=mod;
	}
	for(int k=minp;k<=r;k++){
		ans3+=dfs(minp+1,k)*dfs(k+1,r);
		ans3%=mod;
	}
	return f[l][r]=(ans1*ans3)%mod;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	cout<<dfs(1,n);
	return 0;//好习惯
}
```
## 尾声
这是一道区间动规，但是递推比较难想，可以用记搜简单解决，所以当一道题目递推关系比较难想时，可以尝试用递归解决。

---

## 作者：GeXiaoWei (赞：0)

# CF1178F1  Short Colorful Strip
## 题目解析
看一下数据，若 $n<m$ 时，且 $2\times n$ 小于 $m$ 时，一定无解，直接输出，不输出会运行错误。

直接写太麻烦，用记忆化搜索更加简洁明了，通俗易懂。数据中的 $m$ 的值特别大，一定要想办法优化，否则超时。我们不如就设 $dp_{l,r}$ 表示 $[l,r]$ 区间操作的方案数，找出最小的颜色开始染，若它的下标为 $x$,则问题可分为在区间 $[L,R]$ 寻找一个带有 $x$ 的区间 $[l,r]$，$l$ 在区间 $[L,x]$ 中选择，$R$ 在区间 $[x,R]$ 中选择。随后我们将左区间 $[L,x]$ 分为 $[L,l-1]$ 和 $[l,x-1]$，求出方案数，用小学乘法原理乘起来即可，中区间和右区间同理，依然用乘法原理。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long mod=998244353;
int n,m,a[1005],dp[1005][1005],t;
vector<int>v[505];
long long dfs(int l,int r){
    if(dp[l][r]!=-1) return dp[l][r];
    if(l>r) return dp[l][r]=1;
    long long a1=0,a2=1,a3=0;
    int p=a[l],p1;
    for(int i=l+1;i<=r;i++) p=min(p,a[i]);
    if(v[p][0]<l||v[p].back()>r) return dp[l][r]=0;
    if(l==r) return dp[l][r]=1;
    p1=v[p][0];
    for(int i=l;i<=p1;i++) a1=(a1+dfs(l,i-1)*dfs(i,p1-1)%mod)%mod;
    if(v[p].size()==1) a2=1;
    else for(int i=0;i<v[p].size()-1;i++) a2=a2*dfs(v[p][i]+1,v[p][i+1]-1)%mod;
    for(int i=v[p].back();i<=r;i++) a3=(a3+dfs(v[p].back()+1,i)*dfs(i+1,r)%mod)%mod;
    return dp[l][r]=a1*a2%mod*a3%mod;
}
int main(){
    scanf("%d %d",&n,&m);memset(dp,-1,sizeof(dp));
    for(int i=1;i<=m;i++){
        if(i>n*2){
            printf("0");
            return 0;
        }
        scanf("%d",&t);
        if(t==a[i-1]) i--,m--;
        else a[i]=t,v[t].push_back(i);
    } 
    printf("%lld",dfs(1,m));
    return 0;
}
```

---

## 作者：tXX_F (赞：0)

# Short Colorful Strip

## 解题思路

由题目描述可知，$n=m$，所以每个颜色只能涂一次。又可知，颜色要从编号小的到编号大的涂，所以可以每次找出区间内颜色编号最小的位置作为基准点，记为 $minid$，将当前区间分 $[l,minid]$ 和 $[minid,r]$ 两个区间。

定义 $dp_{i,j}$ 表示区间 $[i,j]$ 的方案数。

对于区间 $[l,minid]$，方案数为：
$$
\displaystyle\sum_{i=l}^{minid}\operatorname{dp}_{l,i-1}\times\operatorname{dp}_{i,minid-1}
$$

对于区间 $[minid,r]$，方案数为：
$$
\displaystyle\sum_{i=minid}^{r}\operatorname{dp}_{minid+1,i}\times\operatorname{dp}_{i+1,r}
$$

最后，区间 $[l,r]$ 的方案数可由由乘法原理求得，即：
$$
\operatorname{dp}_{l,r}=\operatorname{dp}_{l,minid}\times\operatorname{dp}_{minid,r}
$$

## AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int Mod = 998244353;
const int Maxn = 500 + 5;
int n, m, a[Maxn];
int tmp[Maxn][Maxn];//区块l~r的方案数
inline int dp(int l, int r) {
	if (tmp[l][r]) {
		return tmp[l][r];
	} else if (l >= r) {
		tmp[l][r] = 1;
	} else {
		int minid = l, tmp1 = 0, tmp2 = 0;
		for (int i = l; i <= r; i++) {//求当前区块编号最小颜色
			if (a[i] < a[minid]) {
				minid = i;
			}
		}
		for (int i = l; i <= minid; i++) {
			tmp1 = (tmp1 + dp(l, i - 1) * dp(i, minid - 1) % Mod) % Mod;
		}
		for (int i = minid; i <= r; i++) {
			tmp2 = (tmp2 + dp(minid + 1, i) * dp(i + 1, r) % Mod) % Mod;
		}
		tmp[l][r] = tmp1 * tmp2 % Mod;
	}
	return tmp[l][r];
}
inline void work() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	dp(1, m);
	cout << tmp[1][m] % Mod << endl;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	work();
	return 0;
}
```

---

## 作者：liaiyang (赞：0)

很明显的区间 dp。

我们设 $dp_{l,r}$ 表示将区间 $[l,r]$ 染成目标颜色的方案数。

我们设 $p$ 为区间中的最小值，那么转移方程就是 
$$dp_{l,r}=\sum_{i=l}^{p-2}\sum_{j=p+1}^{r-1}dp_{l,i}dp_{i+1,p-1}dp_{p+1,j}dp_{j+1,r}$$
$$=\sum_{i=l}^{p-2}dp_{l,i}dp_{i+1,p-1}\sum_{j=p+1}^{r-1}dp_{p+1,j}dp_{j+1,r}$$

时间复杂度 $O(n^3)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define min(a,b) (a<b?a:b) 
#define P pair<int,int>
#define x first
#define y second
#define modd(x) (((x)%mod+mod)%mod) 
#define rd read()
#define lowbit(x) ((x)&(-x))
mt19937 rnd(time(0));
inline int read(int u=0, char c=getchar(), bool f=false){
    for (;!isdigit(c);c=getchar()) f|=c=='-';
    for (;isdigit(c);c=getchar()) u=(u<<1)+(u<<3)+c-'0';
    return f?-u:u;
}
inline void wt(int x){
    if(x<0) x=-x,putchar('-');
    if(x>9) wt(x/10);
    putchar(x%10+48);
}
inline void wt(int x,char k){wt(x),putchar(k);}
const int inf=~0U>>1,linf=~0ULL>>1; 
const int mod=998244353;
const int N=510;
int n,m,c[N],dp[N][N],p[N][N];
main(){
    n=rd,m=rd;
    for(int i=1;i<=n;i++) c[i]=rd;
    for(int i=1;i<=n+1;i++) dp[i][i]=dp[i][i-1]=1;
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++){
            p[i][j]=i;
            for(int k=i;k<=j;k++) if(c[p[i][j]]>c[k]) p[i][j]=k;
        }
    for(int len=2;len<=n;len++)
        for(int l=1;l+len-1<=n;l++){
            int r=l+len-1;
            int sum1=0,sum2=0;
            for(int i=l;i<=p[l][r];i++)
                sum1=(sum1+dp[l][i-1]*dp[i][p[l][r]-1]%mod)%mod;
            for(int j=p[l][r];j<=r;j++)
                sum2=(sum2+dp[p[l][r]+1][j]%mod*dp[j+1][r]%mod)%mod;
            dp[l][r]=sum1*sum2%mod;
        } 
    wt(dp[1][n],'\n');    
    return 0;
}
```

---

## 作者：I_AK_IOI_6645 (赞：0)

## 题目翻译:
 一个长 $m$ 空白纸条变为一个覆盖 $n$ 种颜色，每种颜色有且只有一种的小纸条，求的是方案数。
很容易看出是一个区间动态规划，但是拓扑结构有点复杂，式子太难推了所以考虑一下记忆化搜索。


### 什么是记忆化搜索？
这是优化 dp 的一种方法，就是将递推形式的动态规划转变成递归形式的动态规划或者可以理解为剪枝后的搜索，多数情况下会将已经计算过的答案进行存储用来减少重复计算这就符合动态规划的无后效性这一特点了，除此之外就是一个纯搜索。


既然是动规就一定有动规数组，设计一个二维的 $f$ 数组来表示将 $l$ 到 $r$ 这个区间染色。


因为是按照从 $1$ 到 $n$ 来染的色，为了方便书写，将当前查找的颜色的下表记为 $x$，所以我们要先找到颜色 $1$ 所在的区间，将 $1$ 所在的位置完成染色后对于包含于 $1$ 的区间 $[l,r]$ 要进行一个整体的计算，分为 $4$ 个区间，$[L,l-1],[l,x-1],[x+1,r],[r+1,R]$ 因为 $x$ 已经染好色了，所以就不用管了。


划分完区间之后可以考虑方案数计算了，这是这道题的难因为要包括 $x$ 所以 $l ∈ [L,x],r ∈ [x,R]$ 接下来最复杂的加乘原理来了对于 $[L,l-1],[l,x-1]$ 这两个区间应该相加还是相乘，首先 $[L,l-1],[l,x-1]$ 这两个区间共同组成了 $x$ 的做部分就是 $[L,x-1]$ 这一部分，所以 $[L,x-1]$ 这个区间是由 $[L,l-1],[i,x-1]$ 这两个小区变化而变化的，所以是乘法原理，同理 $[x+1,R]$ 这个大区间也是由 $[x+1,r],[r+1,R]$ 这两个小区间组成的，所以每个区间的方案数应该相乘。

可是当左区间 $l$ 变化后又会产生两个新的小区间，比如当 $l$ 变化为 $newl$ 后，区间就变成了 $[L,newl],[newl+1,x-1]$ 如何计算新产生的区间积与旧区间积又是一个新的问题，但是一思考就会发现无论 $l$ 怎样变化左区间始终是 $[L,x-1]$ 所以对于左区间之积应相加，右区间同理，当计算出左右两区间之后应该加还是乘又成了一个问题，但是整个 $[L,R]$  的区间是由左右两个组成的，所以每当左右区间发生变化大区间就变成了两个新的左右区间组成的，所以这里是乘法原理,最后递归下去就没了。
 
$$f(L,R)  = { \sum _ {l = L} ^ {x-1} } f(L,l-1) \times f(l,x-1) + \sum _ {r = x+1} ^ R f(x+1,r) \times f(r+1,R)$$

~~~cpp
#include<bits/stdc++.h>
#define ll long long//担心爆int
using namespace std;
const ll mod = 998244353;//定义成常数节省时间空间
ll n,m;
ll a[505];
ll f[505][505];
ll dfs(int L,int R){
	if(f[L][R])	return f[L][R];记忆化搜索精髓所在，避免重复计算
	if(L>=R)	return 1;//避免出现奇怪的区间
	ll minn = 1e9;//存储寻找未染色的最小的点
	ll ans1 = 0;//存储左区间方案数
   ll ans2 = 0;//存储右区间方案数
	ll newl;//存储要染色的点的下标
	for(int i = L;i<=R;i++){
		if(a[i] < minn){
			minn = a[i];
			newl = i;
		}
	}//查找最小未染色的点和坐标
	for(int i = L;i<=newl;i++){
		ans1 += dfs(L,i-1)*dfs(i,newl-1);
		ans1 %= mod;
	}//计算左区间
	for(int j = newl;j<=R;j++){
		ans2 += dfs(newl+1,j)*dfs(j+1,R);
		ans2 %= mod; 
	}//计算右区间
	return f[L][R] = ans1*ans2%mod;
}
int main(){
	cin>>n>>m;
	for(int i = 1;i<=n;i++){
		cin>>a[i];//输入
	}
	for(int i = 1;i<=n;i++){
		f[i][i] = 1;//初始化
	}
	ll x = dfs(1,n);
	cout<<x;
}
~~~
代码就这么多，主要是难在加乘原理的理解和选取
### 有问题可以在下面问，看到会回

---

