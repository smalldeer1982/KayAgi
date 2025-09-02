# Progress Monitoring

## 题目描述

### 题面翻译

编程老师$Dmitry Olegovich$（以下简称小$D$）准备在一次考试中出以下题目：
**以邻接矩阵的方式给定一颗树，求下面这段伪代码的输出结果**。

```
used[1 ... n] = {0, ..., 0};

procedure dfs(v):
    print v;
    used[v] = 1;
    for i = 1, 2, ..., n:
        if (a[v][i] == 1 and used[i] == 0):
            dfs(i);

dfs(1);
```

为了简化测试结果的检查过程 ~~（其实就是懒）~~ ，小 $D$ 决定创建一棵树 $T$ ，使得结果是他最喜欢的序列 $b$ 。不过，小 $D$ 不想为学生用相同的树作为输入（这意味着他们可能会作弊）。**所以小 $D$ 试图找出不同的树 $T$ 的数量，以便以 $T$ 作为输入运行上述伪代码的结果恰好是序列 $b$ ，答案对$10 ^9+7$取模**。

（两棵树“不同”的定义：它们的邻接矩阵不相同）

### 题面简述

见题面翻译中加粗部分。

## 说明/提示

$1\le n \le 500$

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
1 3 2
```

### 输出

```
1
```

# 题解

## 作者：Alkaid_Star (赞：6)

食用前提示：由于本人太菜，是看了 @$Skylee$ 大佬的题解才AC的，所以可能内容与他相似，不过加入了一些自己的理解。

如果大佬介意的话我可以重新编排一下，删除相关内容（小声）

## 题目大意：
>
找出不同的树 $T$ 的数量，以便以 $T$ 作为输入运行下面给出伪代码的结果恰好是序列 $b$ ，答案对$10 ^9+7$取模。
>

>
（两棵树“不同”的定义：它们的邻接矩阵不相同）
>

>
数据范围：$ 1\le n \le 500$
>

```
used[1 ... n] = {0, ..., 0};

procedure dfs(v):
    print v;
    used[v] = 1;
    for i = 1, 2, ..., n:
        if (a[v][i] == 1 and used[i] == 0):
            dfs(i);

dfs(1);
```

## 思路解析：

很明显可以看到这是一个 $DFS$ 序。

不过Skylee大佬说这是一道树形DP，我觉得更像是区间DP。

用 $f[l][r]$ 表示以$b_{l\sim r}$ 为 $DFS$ 序可以对应多少种树的形态。

边界条件：当 $l=r$ 时， $f[l][r]=1$（只有一个结点）

转移方程为$f[l][r]=\sum_{l<k\le r,b_{k+1}<b_{l+1}}f[l+1][k]\times f[k][r]$

诶，没错，就是和 $Skylee$ 大佬写的一样，但是我这里加入了一些自己的理解：

#### （注意，对于这里的 $f[l][r]$ ，我们认为它是以 $l$ 为根的对于当前区间，我们枚举第一个子树到哪里为止。转移方程中乘以 $f[k][r]$ 的含义是以 $k$ 为根的另一个树作为答案，把 $k$ 去掉后合并到以 $l+1$ 为根的子树里。因为 $k+1$ 一定是 $k$ 的第一个儿子，$f[k][r]$ 的所有除了 $k+1$ 的儿子全都大于 $a[k+1]$ ，所以只需要判断 $a[l+1]<a[k+1]$ 。）

### 代码1（看完别走开）：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int Mod=1000000007;
const int N=505;

int n,a[N];
long long f[N][N];

inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while (!isdigit(ch)) { if (ch=='-') f=-1; ch=getchar(); }
	while (isdigit(ch)){ x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}

inline long long dfs(int l,int r){
	if (l==r) return 1;
	if (f[l][r]) return f[l][r];
	for (int k=l+1;k<=r;k++){
		if (k!=r&&a[k+1]<a[l+1]) continue;
		f[l][r]=(f[l][r]+dfs(l+1,k)*dfs(k,r))%Mod;
	}
	return f[l][r];
}

int main(){
	//freopen("CF509F.in","r",stdin);
	//freopen("CF509F.out","w",stdout);
	n=read();
	for (int i=1;i<=n;i++)
		a[i]=read();
	memset(f,0,sizeof(f));
	printf("%lld\n",dfs(1,n));
	return 0;
}
```

不过你以为就这么结束了？

都说**记忆化搜索是DP的一种实现方式**，那么我们自然可以把它改成DP。

很好想，三层循环，第一层枚举区间长度，第二层枚举区间左端点，第三层枚举区间分割点（也就是根），转移方程同上。

从这里我们就可以看出时间复杂度显然是 $O(n^3)$了。 

### 代码2：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int Mod=1000000007;
const int N=505;

int n,a[N];
long long f[N][N];

inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while (!isdigit(ch)) { if (ch=='-') f=-1; ch=getchar(); }
	while (isdigit(ch)){ x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}

int main(){
	//freopen("CF509F.in","r",stdin);
	//freopen("CF509F.out","w",stdout);
	n=read();
	for (int i=1;i<=n;i++)
		a[i]=read();
	memset(f,0,sizeof(f));
	for (int i=1;i<=n;i++) f[i][i]=1;
	for (int len=2;len<=n;len++)		//枚举长度 
		for (int l=1;l<=n-len+1;l++){		//枚举起点 
			int r=l+len-1;
			for (int k=l+1;k<=r;k++){		//枚举分割点 
				if (k!=r&&a[k+1]<a[l+1]) continue;
				f[l][r]=(f[l][r]+f[l+1][k]*f[k][r])%Mod;
			}
		}
	printf("%lld\n",f[1][n]);
	return 0;
}
```

都看到这里了不点个赞么（小声）

---

## 作者：SoyTony (赞：2)

这是一个和树有点关系的的区间 dp。

读题可知 $b$ 数组中存储的是这棵树的 dfs 序，只不过在遍历时**父亲相同的子树优先遍历编号小的**。

试想一个区间 $[l,r]$ 中怎样排布对整体是没有影响的，内部序不变外部自然也不变，于是可以化成小区间的子问题。

考虑设置 $dp(l,r)$ 表示这个区间的方案数，不难发现，我们只需要找到在 $b$ 中的“断点”，即从哪个点开始另成一颗子树（钦定 $l$ 一定为大区间根），再根据上面加粗的限制，转移方程：
$$dp(l,r)=\sum_{k=l+1}^r dp(l+1,k)\times dp(k,r)\ [b(l+1)<b(k+1)]$$

当然，$dp(l,l)=1$。

除此之外，可能需要理解一下的便是这个 $k$ 的定义了，其实是第一棵子树的最后一个节点编号，而且我们要区分两个定义——“区间”和“子树”。

将**子树** $[l,r]$ 划分成除根节点以外的 $[l+1,k]$ 与 $[k+1,r]$ 两个**区间**。如果两区间都是**森林**，那么只能保证各自区间内根结点标号满足上面加粗的条件，而整体上是未必满足的。因此，左区间直接作为**子树**，方案数是 $dp(l+1,k)$，而右区间是**森林**，有一个虚拟的根 $k$，方案数是 $dp(k,r)$，这样一来不会有重复，也能保证优先遍历标号小的根。

---

## 作者：skylee (赞：2)

### 题解地址：
[[CF509F]Progress Monitoring - skylee's Blog](http://www.cnblogs.com/skylee03/p/8990156.html)

### 题目大意：

给定一个树的DFS序$b_1,b_2,\ldots,b_n$（$b$为$1\sim n$的一个排列且$b_1=1$）。同一个结点的子结点按照结点编号从小到大遍历。问有多少种可能的树的形态？

### 思路：

树形DP。

用$f[l][r]$标示DFS序$b_{l\sim r}$对应多少种树的形态。显然当$l=r$时，$f[l][r]=1$。转移方程为$f[l][r]=\sum_{l<m\le r,b_{m+1}<b_{l+1}}f[l+1][m]\times f[m][r]$。其中$f[l+1][m]$表示$b_{l+1\sim m}$构成树的方案数，$f[m][r]$表示$b_{m+1\sim r}$构成森林的方案数。这是一个$2D/1D$的动态规划，时间复杂度$O(n^3)$。

### 源代码：
```cpp
#include<cstdio>
#include<cctype>
typedef long long int64;
inline int getint() {
	register char ch;
	while(!isdigit(ch=getchar()));
	register int x=ch^'0';
	while(isdigit(ch=getchar())) x=(((x<<2)+x)<<1)+(ch^'0');
	return x; 
}
const int N=501,mod=1e9+7;
int b[N],f[N][N];
int dfs(const int &l,const int &r) {
	if(f[l][r]) return f[l][r];
	if(l==r) return f[l][r]=1;
	for(register int m=l+1;m<=r;m++) {
		if(m!=r&&b[l+1]>b[m+1]) continue;
		(f[l][r]+=(int64)dfs(l+1,m)*dfs(m,r)%mod)%=mod;
	}
	return f[l][r];
}
int main() {
	const int n=getint();
	for(register int i=1;i<=n;i++) b[i]=getint();
	printf("%d\n",dfs(1,n));
	return 0;
}
```

---

## 作者：StayAlone (赞：1)

简单自然的题目。

想到子树一定在原序列上是一个区间，于是区间 dp。

$f_{l, r}$ 表示区间 $[l, r]$ 的合法生成树数量，$g_{l, r}$ 表示区间 $[l, r]$ 的合法生成森林数量。

当 $l<r$ 时，$f_{l, r} = g_{l + 1,r}$。因为 $l$ 一定是根，$[l + 1,r]$ 的部分组成的森林中，各棵树的根连向 $l$，唯一对应一棵合法的生成树。

当 $l=r$ 时，$f_{l, r} = 1$。

区间 dp 转移 $g$。单独处理 $[l, r]$ 形成一棵树的情况；森林一定能够拆解为一棵树与另一部分森林，乘法原理即可。

$g_{l, r}=f_{l, r} + \sum\limits_{k\in [l,r)\land a_l <a_{k+1}} f_{l, k}\times g_{k+1,r}$。

其中对 $a$ 的限制是因为，按照题目的伪代码，某个点的儿子必须按照字典序遍历。

时间复杂度 $\mathcal O(n^3)$。

[AC record](https://www.luogu.com.cn/record/156934510)

```cpp
int n, a[510], g[510][510]; const int mod = 1e9 + 7;

il int f(int l, int r) {
	if (l == r) return 1;
	return g[l + 1][r];
}

int main() {
	read(n); rer(i, 1, n, a);
	rep1(i, 1, n) g[i][i] = 1;
	rep1(len, 2, n) rep1(l, 1, n - len + 1) {
		int r = l + len - 1; g[l][r] = g[l + 1][r];
		rep1(k, l, r - 1) if (a[l] < a[k + 1]) (g[l][r] += 1ll * f(l, k) * g[k + 1][r] % mod) %= mod;
	} printf("%d", f(1, n));
	rout;
}
```

---

## 作者：yty2010 (赞：1)

## 题意简述
给定某棵树的 DFS 序，求有多少种树的 DFS 序符合给定的 DFS 序。
## 分析
既然是枚举情况，DP 是首选的，在这里因为要枚举一段 DFS 序内（对应子树）情况的，因此考虑区间 DP。
#### 定义状态
$dp_{i,j}$ 表示节点编号为 $i$ 到 $j$ 的子树（根为 $i$ ）可能的情况数
#### 状态转移
将 $i+1$ 到 $j$ 的节点分成两部分（ $i$ 为根不参与分割 ），则总情况数为两部分情况相乘。定义 $k$ 将 $i+1$ 到 $j$ 的节点分成 $i+1$ 到 $k$ 和 $k$ 到 $j$ 两部分（因为以 $k$ 为根的可能子树中 $k$ 也同样不参与分割，所以 $k$ 既作为前一部分的结尾，也是后一部分的根节点）（可自行举例理解）。当然也可以理解成将节点编号为 $i+1$ 到 $k$ 的子树与 $k$ 到 $j$ 的子树合并。

综上所述，转移方程为：
$$
dp_{i,j}= \sum_{k=i+1}^{j} dp_{i,k} \times dp_{k,r}
$$

#### 转移条件
由于 DFS 序在一个根的两个儿子之间先遍历编号小的，又因为在一棵树中子树的顺序都会先考虑到，我们只需要考虑当前操作。那么在子树的合并中，只要 $i+1$ 节点 与 $k+1$ 节点的顺序符合就可以进行操作，（ $i$ 节点 和 $k$ 节点为根， $ k$ 的顺序在该操作前之前的考虑 $i$ 节点 到 $k$ 节点的子树的方案数时就应该考虑过了，而 $i$ 为最终的根节点不需要考虑），即 $b_{i+1} < b_{k+1}$ 。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mod 1000000007
int n,b[505];
int dp[505][505];
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>b[i];
	for(int i=1;i<=n;i++)dp[i][i]=1;  //初始化
	for(int l=2;l<=n;l++)
	{
		for(int i=1;i+l-1<=n;i++)
		{
			int j=i+l-1;
			for(int k=i+1;k<=j;k++)  //三层循环的内容不用多说了吧
			{
				if(k!=j&&b[k+1]<b[i+1]) //判断（原因见上），k==j时为特殊情况
					continue;
				dp[i][j]+=dp[i+1][k]*dp[k][j]%mod; //转移
				dp[i][j]%=mod;
			}
		}
	}
	cout<<dp[1][n]<<endl;
}
```

---

## 作者：Umbrella_Leaf (赞：0)

### 题意

> 给一个 $1$ 到 $n$ 的排列，问有多少棵 $n$ 个点的树 `dfs` 序是这个排列。$n\le 500$。

### 分析

看到题就能想到是区间 DP，而且 $n\le 500$。

做法比较简单，$dp_{l,r}$ 表示 $[l,r]$ 这段区间是多少棵树的 `dfs` 序，同时也可以表示 $[l+1,r]$ 这段区间是多少个森林的 `dfs` 序。

转移：
$$
dp_{l,r}=\sum_{k=i+1}^j[a_{i+1}<a_{k+1}\ or\ k=j]dp_{i+1,k}\times dp_{k,j}
$$

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod=1e9+7;
int n;
int a[505];
ll dp[505][505];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)dp[i][i]=1;
	for(int len=2;len<=n;len++)
		for(int i=1;i<=n-len+1;i++){
			int j=i+len-1;
			for(int k=i+1;k<=j;k++)
				if(k==j||a[i+1]<a[k+1])dp[i][j]=(dp[i][j]+dp[i+1][k]*dp[k][j]%mod)%mod;
		}
	printf("%lld\n",dp[1][n]);
	return 0;
}
```

---

## 作者：ifffer_2137 (赞：0)

大家好祝大家以后看到 $n\le 500$ 就都能想到区间 DP。
### 题意
给定一个 dfn 序，求有多少种不同的有标号树的 dfn 序为该序列。

定义两棵树不同当且仅当存在一个编号在两棵树中的父亲不同。
### 分析
区间 DP。具体怎么想到的个人认为可能就看看数据范围感觉一下，~~反正我就是假了一次以后抿了一下数据范围就会了~~。

然后你发现设一个区间是一棵子树不是很够，转移升天。所以考虑设 $dp_{l,r}$ 表示 $[l,r]$ 这个区间能还原成一个森林 dfn 序的方案数。

然后你考虑怎么转移，直接枚举分出来的第一棵子树，然后因为是顺序遍历邻接矩阵，所以要满足子树根的编号小于后面那一段第一棵子树根的编号，然后两个乘法原理简单计数再加起来就好了。

然后一个区间只生成一棵树的方案也记录一下，最后直接输出整个序列的方案数即可。
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
const int mod=1e9+7;
int n;
int a[maxn];
int dp[maxn][maxn][2];
void add(int &x,int y){x+=y;if(x>=mod) x-=mod;}
signed main(){
	#ifndef ONLINE_JUDGE
		assert(freopen("data.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	cin.tie(0),cout.tie(0);
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) dp[i][i][0]=dp[i][i][1]=1;
	for(int i=2;i<=n;i++){
		for(int l=1;l+i-1<=n;l++){
			int r=l+i-1;
			dp[l][r][0]=dp[l][r][1]=dp[l+1][r][1];
			for(int k=l;k<r;k++) if(a[k+1]>a[l]) add(dp[l][r][1],dp[l][k][0]*dp[k+1][r][1]%mod);
			//cout<<l<<' '<<r<<' '<<dp[l][r][0]<<' '<<dp[l][r][1]<<'\n';
		}
	}
	cout<<dp[1][n][0]<<'\n';
	return 0;
}
```

---

