# [HNOI2002] Tinux系统

## 题目描述

在 dos 系统诞生以前，美国曾研究出一种类似的操作系统，名为 Tinux 系统。但由于硬件设施的制约，Tinux 系统有许多的缺点。下面就对 Tinux 系统作一个简单的介绍：

Tinux 系统是 Tiger 博士为美国军方研制开发的一种操作系统，该系统对文件的存储方式类似于 dos 系统，像一棵树一样，每一个叶子节点表示一个文件，每一个非叶子节点表示一个目录。其中定义 $i$ 级子目录表示从根目录开始访问，一直访问到该子目录（不包括该子目录）需要访问的目录的个数为 $i$ 的目录，所以根目录下的目录为一级子目录，其他的目录以此类推。但是在同一子目录下，受到硬件的制约 Tinux 系统最多只能够存储 $k$ 个文件或子目录，也就是说这棵树里面的每一个非叶子节点最多只有 $k$ 个子节点。这样就导致在文件数量较多的情况下，访问存储在该系统当中的文件 A，往往要先访问一系列的子目录，我们称这些子目录为文件 A 的上级目录。例如下面这一个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/11pz60gn.png)

当我们要访问文件 A4A2A1 时就必须先访问它的上级目录：一级子目录 A4 和二级子目录 A4A2。

Tinux 系统在存储文件时，给每一个子目录都分配了 $k$ 个指针，分别指向存放在该目录下的每一个文件和每一个目录，因此对文件的访问实质上就是对指针的访问。但是由于硬件原因，这 $k$ 个指针不尽相同，因此访问它们的时间也不同，访问第 $i$ 个指针所耗费的时间为 $P_i$。但是对于两个不同的子目录（不管它们各自属于哪一级目录）而言它们各自所拥有的 $k$ 个指针是相同的。

Tinux 系统最大的缺点是访问一个目录时，必须把该目录下所有的文件读入到内存当中来，这些文件包括在其各级子目录当中的文件，例如上面那一个例子，访问 A4 那一个目录，就必须把 A4A1，A4A2A1，A4A2A2，A4A3 这四个文件都读入到内存当中来，访问一个目录所需要的时间为 $P_i \times x$（$x$ 表示该目录及其各级子目录下文件的个数，$P_i$ 表示指向该目录的指针的访问时间）。因此根据上面介绍的访问方法，单独访问一个文件所需要的总时间为访问其所有上级目录（不包括根目录）所需要的时间与访问指向该文件的指针所需要的时间的和，例如上面那一个例子，访问文件 A4A2A1 需要的时间 = 访问目录 A4 的时间 + 访问目录 A4A2 的时间 + 访问指向文件 A4A2A1 的指针需要的时间。

现在，tiger 博士准备将 $n$ 个文件存储到一个空的 Tinux 系统当中，希望你帮助他设计一个程序找到一种最优的存储方法，使得单独访问这 $n$ 个文件所需要的时间总和最小。

## 说明/提示

![](https://cdn.luogu.com.cn/upload/pic/1296.png)

**【数据范围】**

$1 \le n \le 1000$，$2 \le k \le 150$，$1 \le P_i \le 150$。

## 样例 #1

### 输入

```
4 3
3
5
4
```

### 输出

```
28
```

# 题解

## 作者：王奕清 (赞：26)

这是一道~~很水的~~黑题。

但是，本题的题意十分难懂。注意：样例输入是错的，最后一个4是多出来的。

整个题目的意思大概是：

一个节点最多可以有 $k$ 条边连向儿子，每条边有一个权值 $a_i$ ，一条边 $(u,v)$ （ $u$ 是父亲， $v$ 是儿子）对答案的贡献是 $v$ 子树内**叶子节点**的 个数² $* a_i$

其中，每个节点可以连出的边的权值是固定的，也就是说，每一个节点，它向儿子连边时，可以选择的边都是一样的。现在告诉你有 $n$ 个叶子结点，问你最小的答案。$(n<=1000,k<=1000)$

思路很简单，就是一个记忆化搜索，$f[x][y]$ 表示现在有 $x$ 个叶子节点待填，已经连了 $y-1$ 条边出去，当然对边权排序是必要的，因为显然，我们要保证最小的边下面跟的叶子节点最多。

然后转移也十分容易，对每条边，只有两种选择：

1.连叶子，直接加上 $a_i$ 

2.连非叶子节点，先加上这条边的贡献，然后在继续递归就可以了。

所以，我们只需要枚举第二种情况时，该节点下面放几个叶子节点就ok了

时间复杂度：$O(nk)$

代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,k,f[1005][1005],a[1005];
int dfs(int x,int y)
{
	if(x==1)
	{
		f[x][y]=a[y];
		return f[x][y];
	}//只剩一个节点
	if(y==k)return f[x][y]=dfs(x,1)+a[y]*x*x;
    //只剩一条边，必须是连非叶子节点
	if(f[x][y])return f[x][y];
	f[x][y]=dfs(x-1,y+1)+a[y];//直接连叶子
	for(int i=2;i<x;i++)//枚举
	f[x][y]=min(f[x][y],dfs(x-i,y+1)+a[y]*i*i+dfs(i,1));
	return f[x][y];
}
signed main()
{
	cin>>n>>k;
	for(int i=1;i<=k;i++)cin>>a[i];
	sort(a+1,a+k+1);
	printf("%d",dfs(n,1));
}
```

---

## 作者：奔波儿霸 (赞：19)

#### 先说几句
楼下那是~~狗屎~~题解啊，强烈谴责，希望管理员早点发现他

话说这是我做的第一道黑题啊。

[点击就送超神套装](https://www.cnblogs.com/bljfy/p/9598616.html)

#### 题目大意
题面这么长，先说说题意吧。

就是有一个操作系统，他的存储方式是树形的。其中分为文件和目录(文件夹)每一个子目录下只能存储 $K$ 个文件或目录。并且有 $K$ 个指针分别指向这 $K$ 个文件或文件夹。每一个指针都有一个访问时间 $P$。

然后每一个文件或目录都有一个访问时间,文件和目录的访问时间计算方式不相同

 - 文件：访问其所有上级目录(就是这个文件访问路径上的文件夹)的访问时间加上这个文件的指针的访问时间。
 - 文件夹：它的各级子目录下文件的个数 $\times $ 它的指针的访问时间。通俗一点就是它的子树上的文件的个数为 $x$，它的指针访问时间是 $y$ 那么它的访问时间就是 $x\times y$。这里要说一下题面描述出了锅，最起码我现在看是这样的。
 
现在你需要计算出给出的 $N$ 个文件的最小访问时间总和。

#### 解题思路
我看了``vijos``上的题解表示并没有看懂，于是问问机房的``dalao``。``dalao``就是``dalao``。

这是一道树形DP。首先要明白一个贪心策略。在同一层子目录下，如果现在的剩余空间已经无法容纳剩下的文件那么我们必然是需要在开一个文件夹进行存储的。那这个文件夹开的位置的指针访问时间越小越好。因为如果它是一个文件夹的话，它对答案的影响会随着它的子目录中文件的数量增加而成倍增加。所以要尽量的小。这就是一个贪心的策略，显然在输入的时候是需要对指针的访问时间从小到大排序的。

接下来做树形dp。先看下代码，我们一段一段的讲。

排序这一部分自然是不用多说了，上面已经说过了。
```cpp
int main() {
	scanf("%d%d", &n, &k);
	for(int i=1; i<=k; i++)
		scanf("%d", &p[i]);
	sort(p+1, p+1+k);
	printf("%d", dp(n, 1, n-1));
}
```
然后是这个dp函数
```cpp
inline int dp(int x, int y, int l) {
	if(x == 1) {
		f[x][y] = p[y];
		return f[x][y];
	}
	if(y == k) {
		f[x][y] = p[y] * x * x + dp(x, 1, x-1);
		return f[x][y];
	}
	int tmp = k-y+1;
	if(tmp * l < x)
		return INF;
	if(f[x][y]) return f[x][y];
	tmp = (x-1)/tmp + 1;
	for(int i=tmp; i<=l; i++) {
		if(i == 1)
			f[x][y] = p[y] + dp(x-1, y+1, x-2);
		else
			f[x][y] = MIN(f[x][y], dp(x-i, y+1, x-i-1) + dp(i, 1, i-1) + p[y] * i * i);
	}
	return f[x][y];
}
```
$x$ 表示还剩下多少个文件没有被安排。$y$ 表示现在用到的是第 $y$ 个指针。$f[x][y]$ 表示还剩 $x$ 个文件用第 $y$ 个指针的最小的访问时间。

显然如果 $x == 1$ 的话，就直接将现在这个指针的时间给它就好了。如果 $y==k$ 的话，说明 $k$ 个指针已经用到了最后一个那肯定是要建一个文件夹。

这里的 $p[y]*x*x$ 的含义呢，是将这个文件夹的访问时间计算出来并且它之后会产生 $x$ 次影响，将这 $x$ 次影响在这里直接计算出来。

$l$ 表示层数，是最多还能伸下去安排几层。$tmp$ 那个地方是一个小剪枝。如果剩余的内存还不够将这 $x$ 个文件安排好的话就直接反回 $inf$。

往后的状态转移，如果只剩下一个需要安排的话，那就直接安排上。否则的话就开一个文件夹，把除文件夹外的剩余空间进行分配，并且往下深入一层。

#### 附上代码

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int maxn = 1003, INF = 2147483647;
int n, k, p[153], f[maxn][maxn];
inline int MIN(int x, int y) {
	if(!x) return y;
	else return min(x, y);
}
inline int dp(int x, int y, int l) {
	if(x == 1) {
		f[x][y] = p[y];
		return f[x][y];
	}
	if(y == k) {
		f[x][y] = p[y] * x * x + dp(x, 1, x-1);
		return f[x][y];
	}
	int tmp = k-y+1;
	if(tmp * l < x)
		return INF;
	if(f[x][y]) return f[x][y];
	tmp = (x-1)/tmp + 1;
	for(int i=tmp; i<=l; i++) {
		if(i == 1)
			f[x][y] = p[y] + dp(x-1, y+1, x-2);
		else
			f[x][y] = MIN(f[x][y], dp(x-i, y+1, x-i-1) + dp(i, 1, i-1) + p[y] * i * i);
	}
	return f[x][y];
}
int main() {
	scanf("%d%d", &n, &k);
	for(int i=1; i<=k; i++)
		scanf("%d", &p[i]);
	sort(p+1, p+1+k);
	printf("%d", dp(n, 1, n-1));
}
```








---

## 作者：Mo默Sh笙 (赞：2)

### [传送门](https://www.luogu.com.cn/problem/P2230)

------------

### 题目大意：
一个 $n$ 个叶子节点，一个节点最多可以有 $k$ 条边连向子节点，每个节点 $i$ 有一个权值 $P_{i}$。记每个节点子树内点的个数（不包括它自己）为 $son_{i}$，那么每个节点对答案的贡献就是 $son_{i}^2 \times P_{i}$。特别的，根节点贡献为 $0$，求总贡献。

------------

两种解法：记忆化搜索和 DP，两种解法本质一样只是写法不同。

------------

### 一、记忆化搜索：

首先贪心的对点权 $P_{i}$ 升序排序。

设 $dp_{rest,now}$ 表示还剩 $rest$ 个节点要连，当前考虑的是第 $now$ 个指针的总贡献。

分三种情况转移：

1. 只剩一个节点，直接连上走人，加上当前点的贡献：$dp_{rest,now}=val_{now}$。
1. 只剩一个指针并且剩下的节点不止一个，开下一层，并加上当前点的贡献：$dp_{rest,now}=dp_{rest,1}+val_{now}\times rest\times rest$。
1. 以上两种情况都不满足，将这个指针作为目录，枚举其连接的点数进行转移：$dp_{rest,now}=\min_{i\in[2,rest)}{dp_{rest,now},dp_{rest-i,now+1}+dp_{i,1}+val_{now}\times i\times i}$。

$\mathcal{Code}$：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define db double
#define il inline
#define re register
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
#define F(i,a,b) for(re int (i)=(a);(i)<=(b);(i)++)
#define DF(i,a,b) for(re int (i)=(a);(i)>=(b);(i)--)
#define G(i,u) for(re int (i)=head[u];(i);(i)=nxt[(i)])
inline ll read(){ll x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-48;ch=getchar();}return x*f;}
const int N=1010,K=160;
int n,k;
int val[K];
int dp[N][K]; 
il int dfs(int rest,int now)//剩rest个点要连，当前用这一层的第now个指针 
{
	if(dp[rest][now]!=INF) return dp[rest][now];//记忆化 
	if(rest==1)//只剩一个节点，直接连上走人 
		return dp[rest][now]=val[now];
	if(now==k)//只剩一个指针并且连不完，再开一层 
		return dp[rest][now]=dfs(rest,1)+val[now]*rest*rest;//val[now]*rest*rest是当前指针对答案的贡献 
	dp[rest][now]=min(dp[rest][now],dfs(rest-1,now+1)+val[now]);//就这个指针作为叶子节点的情况 
	F(i,2,rest-1)//这个指针作为目录，连i个点的情况 
		dp[rest][now]=min(dp[rest][now],dfs(rest-i,now+1)+dfs(i,1)+val[now]*i*i);//val[now]*i*i是当前指针对答案的贡献 
	return dp[rest][now];
}
int main()
{
	memset(dp,0x3f,sizeof(dp));
	n=read(),k=read();
	F(i,1,k) val[i]=read();
	sort(val+1,val+k+1);
	printf("%d",dfs(n,1));
	return 0;
}
```


------------

### 二、DP：

[此 DP 做法以 `53ms` 的时间拿下了此题最优解](https://www.luogu.com.cn/record/list?pid=P2230&orderBy=1&status=&page=1)

还是先贪心的对点权 $P_{i}$ 升序排序。

**TIP：为了防止变量重名，将原先的指针数量 $k$ 改成了 $m$。**

设 $dp_{i,j}$ 表示在当前目录下，用前 $j$ 个指针放 $i$ 个文件，所增加的贡献。

设 $g_{i}$ 表示放 $i$ 个文件的最少时间，$g_{n}$ 即所求答案。

先预处理 $dp_{1,i}=val_{i}(i\in[1,k])$ 表示只放一个文件的特殊情况，这种情况不用开目录直接放。

还要预处理 $g_{1}=0$，这是因为只放一个文件是不用开目录的，在转移时会统计目录的贡献，由于只放一个点时开目录贡献和叶子节点的贡献一样，为了防止重复，将 $g_{1}$ 设为 $0$，并对 $n=1$ 的情况特判。

**这里有个小剪枝：要使答案最优，数值大的指针放的文件个数一定小于等于数值小的指针放的文件个数，均摊的情况即 $\lfloor \frac{i}{j} \rfloor$，将此作为上界以减少转移次数。**

转移时枚举之前的指针目录下已经放置的文件 $k$，对当前的 $dp_{i,j}$ 进行更新，转移即：$dp_{i,j}=\min_{k\in[1,i-j+1]}{dp_{i,j},dp_{i-k,j-1}+g_{k}+k\times k\times val_{j}}$。

然后对 $g_{i}$ 和特殊情况 $dp_{i,1}$ 进行更新用于下一轮的转移。



$\mathcal{Code}$：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define db double
#define il inline
#define re register
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
#define F(i,a,b) for(re int (i)=(a);(i)<=(b);(i)++)
#define DF(i,a,b) for(re int (i)=(a);(i)>=(b);(i)--)
#define G(i,u) for(re int (i)=head[u];(i);(i)=nxt[(i)])
inline ll read(){ll x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-48;ch=getchar();}return x*f;}
const int N=1010,K=160;
int n,m;
int val[K];
int dp[N][K],g[N];//dp[i][j]表示放i个文件，用了前j个指针所花；g[i]表示放i个文件的最优解 
int main()//贡献记为：子文件个数×当前指针的值 
{
	memset(dp,0x3f,sizeof(dp));
	memset(g,0x3f,sizeof(g));
	n=read(),m=read();
	F(i,1,m) val[i]=read();
	sort(val+1,val+m+1);
	if(n==1) return printf("%d",val[1]);//因为g[1]设为了0，所以n=1时要特判 
	g[1]=0;//只放一个文件，不用开目录，这个文件自身的贡献在转移时已被计算，所以这里的贡献设为0 
	F(i,1,m) dp[1][i]=val[i];//第i个指针，放1个文件，直接放，贡献为val[i]
	F(i,2,n)
	{
		F(j,2,min(i,m)) 
			F(k,1,i/j)//剪枝：贪心的想：大指针放的文件个数一定小于等于小指针放的文件个数，所以设定上界i/j即均摊的情况 
				dp[i][j]=min(dp[i][j],dp[i-k][j-1]+g[k]+k*k*val[j]);
		F(j,2,min(i,m))//更新最优解 
			g[i]=min(g[i],dp[i][j]);
		dp[i][1]=g[i]+i*i*val[1];//更新只用一个指针的情况用于更新 
	}
	printf("%d",g[n]);
	return 0;
}
```


---

## 作者：qwerty12346 (赞：2)

# [题目传送门](https://www.luogu.com.cn/problem/P2230)

## 题意

这题就是让我们找一种最优的存储方法，让单独访问这 $n$ 个文件所需要的总时间最少。

## 思路

直接树形动态规划就行。记得先将 $a$ 数组排序。

## 状态定义

$dp_{i,j}$ 表示目前有 $i$ 个子节点待填，并且有 $j-1$ 条边连接。

## 状态转移方程加回溯

$dp_{i,j}=\min(DP(i-k,j+1)+DP(k,1)+a_{j} \times k \times k)$

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[100005],f[1005][1005];
int dp(int i,int j){//dp函数
    if(i==1)
    {
	f[i][j]=a[j];
	return f[i][j];
    }
    if(j==m)return f[i][j]=dp(i,1)+a[j]*i*i;
    if(f[i][j])return f[i][j];
    f[i][j]=dp(i-1,j+1)+a[j];
    for(int k=2;k<i;k++)f[i][j]=min(f[i][j],dp(i-k,j+1)+dp(k,1)+a[j]*k*k);//状态转移方程加回溯
    return f[i][j];
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++)cin>>a[i];
    sort(a+1,a+m+1);//排序
    cout<<dp(n,1);//调用dp函数
    return 0;
}
```


---

## 作者：qyzyq (赞：0)

[传送门](https://www.luogu.com.cn/problem/P2230)

提供一种基于贪心的解法。

首先是将 $p$ 从小到大排序。

考虑到该系统是一棵树，所以对于系统中的每个点，我们记：

$tr_{son}$ 表示该点(目录)的儿子的位置。

$tr_{fa}$ 表示该点(目录)的父亲的位置。

$tr_{siz}$ 表示该点(目录)包含的点的个数。

$tr_{cnt}$ 表示该点(目录)有多少个儿子。

$tr_{val}$ 表示该点(目录)的 $p$ 值。

考虑对于现在系统中已经有了 $x$ 个文件，现在要插入第 $x+1$ 个文件。

考虑这个文件可以插入到的地方以及对答案贡献：

操作 $1$、插入到原有目录中。

贡献为：$(\sum\limits_{pos \in tr} tr_{val} \times (tr_{siz}\times 2+1))+p_{pos}$。

即新文件所有父亲目录的 $p_i$ 乘上两倍该目录的点的个数加一，然后再加上新文件的 $p_i$。

操作 $2$、将该位置的文件变成目录，然后向这个目录中插入原位置文件和新文件。

贡献为：$(\sum\limits_{pos \in tr} tr_{val} \times (tr_{siz}\times 2+1))+p_1+p_2+p_{pos} \times 3$。

即该位置文件所有父亲目录的 $p_i$ 乘上两倍该目录的点的个数加一，然后加上该文件的 $p_i$ 乘三，再加上 $p_1$ 和 $p_2$。

这些不难推导，可以结合样例推导。

考虑其正确性：

$1$、若要将新文件插入到一个目录，一定会将新文件插在 $p_i$ 尽量小的地方，而将 $p$ 从小到大排序之后，一定会先插完 $p_{1 \sim i-1}$，再插 $p_i$。

$2$、对于一个空位置，新文件一定是直接插在该位置比在该位置建目录，再插入到目录中更优。

$3$、无论是插入到哪里，设该次插入对答案造成的贡献为 $t$，则新的可以插入的位置对答案造成的贡献不会小于 $t$。

对于第三个性质的证明，我们只证明先进行操作 $2$ 再进行操作 $1$ 仍满足性质 $3$：

若再新建的目录下插入第 $3$ 个文件，则相比操作二， $\sum$ 中多出来的就是 $p_{pos} \times (pos_{siz}+1)$ 即，$p_{pos} \times 5$，而再加上 $p_3$，显然 $p_{pos} \times 5+p_3>p_{pos} \times 3 p_1+p_2$。

其他同理。

基于这三个性质，我们可以如此操作：

对该系统进行深搜。

对于一个目录，考虑它可以加入的最小的 $p_i$ 对答案的贡献，加入数组 $a$ 中。

对于一个文件，考虑它变成目录再插入文件对答案的贡献，加入数组 $a$ 中。

然后将 $a$ 从小到大排序。

将最小的加入答案，并更改该系统即可。

注意特别判断在 $root$ 插入的情况。

上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1010;
int n,k,p[N],ans;
struct jgt
{
	int son[155];
	int siz,val,cnt,fa;
}tr[N*2];
int tot;
struct jgt1
{
	int x,pos;
}a[N*2];
int idx;
bool cmp(jgt1 t1,jgt1 t2)
{
	return t1.x<t2.x;
}
void dfs(int wz,int sum)
{
	if(wz==0)
	{
		for(int i=1;i<=tr[wz].cnt;i++)
			dfs(tr[wz].son[i],0);
		if(tr[wz].cnt!=k)
		{
			a[++idx].pos=wz;
			a[idx].x=p[tr[wz].cnt+1];
		}
	}
	else
	{
		if(tr[wz].cnt==0)
		{
			a[++idx].pos=wz;
			a[idx].x=sum+tr[wz].val*3+p[1]+p[2];
		}
		else if(tr[wz].cnt==k)
		{
			for(int i=1;i<=k;i++)
				dfs(tr[wz].son[i],sum+tr[wz].val*(tr[wz].siz*2+1));
		}
		else
		{
			a[++idx].pos=wz;
			a[idx].x=sum+tr[wz].val*(tr[wz].siz*2+1)+p[tr[wz].cnt+1];
			for(int i=1;i<=tr[wz].cnt;i++)
				dfs(tr[wz].son[i],sum+tr[wz].val*(tr[wz].siz*2+1));
		}
	}
}
void get(int wz)
{
	tr[wz].siz++;
	if(tr[wz].fa!=0) get(tr[wz].fa);
}
void add(int wz)
{
	if(wz==0)
	{
		tr[wz].cnt++;
		int shu=tr[wz].cnt;
		tr[wz].son[shu]=++tot;
		tr[tot].val=p[shu];
		tr[tot].fa=wz;
		return ;
	}
	if(tr[wz].cnt!=0)
	{
		tr[wz].cnt++;
		tr[wz].siz++;
		int shu=tr[wz].cnt;
		tr[wz].son[shu]=++tot;
		tr[tot].val=p[shu];
		tr[tot].fa=wz;
		if(tr[wz].fa!=0) get(tr[wz].fa);
		return ;
	}
	if(tr[wz].cnt==0)
	{
		tr[wz].cnt=2;
		tr[wz].siz=2;
		tr[wz].son[1]=++tot;
		tr[tot].val=p[1];
		tr[tot].fa=wz;
		tr[wz].son[2]=++tot;
		tr[tot].val=p[2];
		tr[tot].fa=wz;
		if(tr[wz].fa!=0) get(tr[wz].fa);
		return ;
	}
}
int main()
{
	scanf("%d %d",&n,&k);
	for(int i=1;i<=k;i++)
		scanf("%d",&p[i]);
	sort(p+1,p+k+1);
	for(int i=1;i<=n;i++)
	{
		idx=0;
		dfs(0,0);
		sort(a+1,a+idx+1,cmp);
		ans+=a[1].x;
		add(a[1].pos);
	}
	printf("%d\n",ans);
	return 0;
}
```

---

