# Treasure Hunting

## 题目描述

有一个$n*m$的矩阵，行的标号从$1$到$n$，列的标号从$1$到$m$，矩阵中共有$k$个宝藏，第$i$个宝藏的位置为$(r_i,c_i)$。有$q$个安全的列，第$i$个安全的列的编号是$b_i$。

最初你站在矩阵的左下角（也就是$(1,1)$的位置），并且可以向左走（从$(r,c)$到$(r,c-1)$）和向右走（从$(r,c)$到$(r,c+1)$）。同时，你也可是向上走（从$(r,c)$到$(r+1,c)$），但是你必须在安全的列上。由于某些玄学原因，你不可以向下走。

你的任务是收集所有的宝藏，但是你的时间已经不多了，所以你必须走最快的路径。现在你要使用你的人脑大法来计算出最快的路径需要多少时间（经过有宝藏的格子时收集宝藏不消耗时间，只有移动消耗时间）。

## 样例 #1

### 输入

```
3 3 3 2
1 1
2 1
3 1
2 3
```

### 输出

```
6```

## 样例 #2

### 输入

```
3 5 3 2
1 2
2 3
3 1
1 5
```

### 输出

```
8```

## 样例 #3

### 输入

```
3 6 3 2
1 6
2 2
3 4
1 6
```

### 输出

```
15```

# 题解

## 作者：老莽莽穿一切 (赞：12)

[更好的阅读体验](https://www.cnblogs.com/LaoMang-no-blog/p/16033541.html)

---

[**你谷 link**](https://www.luogu.com.cn/problem/CF1201D)

[**CF link**](https://codeforces.com/problemset/problem/1201/D)

题解区有一半是 $\mathcal O\left(n\log n\right)$ 做法，剩下两篇 $\mathcal O\left(n\right)$ 做法，跑得又慢，代码还又臭又长，活生生整出大模拟的味道，明明是可以写的很简洁的代码。

在下莽某人不才，暂时拿下你谷最优解：

![](https://s2.loli.net/2022/03/21/B5jIDLgVlaytWfx.png)

### 正片开始

废话到此为止，接下来讲做法，其实大家题解里做法都已经讲得比较清楚了，我这里还是再讲一遍。

给定一张网格图以及一些特殊点和特殊列，只允许向左右走或在特殊列向上走，问经过所有特殊点的最短路径长度。

第一眼就是 dp，感觉就很对，先设一个 dp 状态 $f_{i,j}$ 表示**已经经过所有前 $i$ 行特殊点**，走到第 $i$ 行第 $j$ 个特殊点，所经过的最短路径长度。

转移方程就不写了。

然后发现光状态就有 $\mathcal O\left(n^2\right)$ 个，铁定爆炸，所以考虑做一点优化。

首先肯定从状态入手，发现要经过**全部**的特殊点，那么在一层内移动方式已经固定了，到达这一层后，要么先走到最左边的特殊点，再往右边走到最右边的特殊点，要么反过来，中间的点可以忽略不计。

这下简单了，每层只记最左边和最右边的点就可以了，时间复杂度瞬减一个 $n$。

大体思路上就是这样，但是细节还是有的。

首先，如果有空行，那么所有信息应该继承上一行的。

其次，纵向上不一定是走 $n-1$ 步，顶端如果有空行，注意不用跑到第 $n$ 行，应当将 $n$ 设为最靠上的特殊点的纵坐标。

然后就是一点小分类讨论，比如从 $(1,1)$ 走到 $(2,3)$ ，如果第 $1$ 列到第 $3$ 列中有特殊列，那么横向移动距离就是 $3-1=2$，否则的话应该找最近的特殊列去“借道”，比如如果第 $5$ 列是特殊列，那么横向移动距离就是 $5\times2-3-1=6$，所以要先预处理每一列左右两边最靠近的特殊列，这样就可以做到 $\mathcal O\left(1\right)$ 查询，否则如果用二分会变成 $\mathcal O\left(n\log n\right)$。

最后是[**代码**](https://codeforces.com/contest/1201/submission/150313552)，自认为还挺简洁的，跑的也不错。

---

## 作者：DarkMoon_Dragon (赞：8)

# $CF1201D$ `Treasure Hunting`

## 题意：
+ 有$2*10^5$个宝藏，可以在任意地方往左右走，在安全列可以往上走，不能往下走。初始在$(1,1)$。每走一格消耗时间$1$。求取完所有宝藏花费最小时间。

## $Solution$
+ 考虑$dp$
+ 因为不能往下走，显然每行末状态只能是在最左边或者最右边的宝藏
+ $dp[i][0/1]$表示前$i$行宝藏选完在左/右的最小花费
+ 发现只有每一行只有最左边和最右边的宝藏有用(从最左到最右或者从最右到最左走一遍)
+ 记录一个$p$数组，表示当前行的最左和最右宝藏
+ 然后讨论如下两种情况
    1. 当前行有宝藏
        + 可以从上个状态的左右转移到当前状态的左右，转移四次
        + 每次转移可能从上个状态的最近左安全列转移过来，也有可能从上个安全点的最近右安全列转移过来，每次转移判断两次
        + 每次转移的判断具有很大的相似性，考虑写个函数减少码量(之前写了$160$多行的$8$种情况判断然后放弃了)
        + 设函数 $calc(j,u,i,v)$ 表示从$j$点的$u$方向转移到$i$点的$v$方向要走的路程
        + 画图发现的规律是
        + ![](https://cdn.luogu.com.cn/upload/image_hosting/vc8ixf6n.png)
        + 一句话就是距离贡献等于当前点到转移点的另一边的距离加上左右两点长度
        + 这样就可以用`lower_bound`查找$p$数组快速更新当前点的前驱和后继从而更新答案了
    2. 当前行没有宝藏
        + 把上一行的宝藏位置转移到当前行
        + $dp$值++
        + 注意可能上面宝藏都没有了，就不能使$dp$值++
        + 所以记录一个$las$表示上一个宝藏在哪一行，转移时加上行差
        
~~看前面几篇都讨论了好多情况，这篇题解利用通性少讨论点情况。~~


```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
#define rr int
using namespace std;
typedef long long ll;
inline ll read() {
    char i = getchar();
    ll f = 1, res = 0;
    while (i < '0' || i > '9') {
        if (i == '-') f = -1;
        i = getchar();
    }
    while (i >= '0' && i <= '9') {
        res = res * 10 + i - '0';
        i = getchar();
    }
    return res * f;
}
const int N = 2e5 + 50;
int n, m, k, q;
ll p[N][2], dp[N][2], inf;
vector<ll> line;
vector<ll>::iterator ite;
inline ll calc(int j, int u, int i, int v) {
    ite = lower_bound(line.begin(), line.end(), p[j][u]);  // suf
    ll res = inf;
    if (ite != line.end()) {
        ll pos = *ite;
        res = abs(p[j][u] - pos) + abs(p[i][v ^ 1] - pos) +
              abs(p[i][v] - p[i][v ^ 1]);
    }
    ite = lower_bound(line.begin(), line.end(), p[j][u]);  // pre
    if (ite != line.begin()) {
        --ite;
        ll pos = *ite;
        res = min(res, abs(p[j][u] - pos) + abs(p[i][v ^ 1] - pos) +
                           abs(p[i][v] - p[i][v ^ 1]));
    }
    return res;
}
int main() {
    n = read(), m = read(), k = read(), q = read();
    memset(dp, 0x3f3f3f3f, sizeof dp);
    inf = dp[0][0];
    for (rr i = 1; i <= n; ++i) {
        p[i][0] = inf;
        p[i][1] = -inf;
    }
    ll x, y;
    for (rr i = 1; i <= k; ++i) {
        x = read();
        y = read();
        p[x][0] = min(p[x][0], y);
        p[x][1] = max(p[x][1], y);
    }
    p[1][0] = 1;
    p[1][1] = max(p[1][1], ll(1));
    for (rr i = 1; i <= q; ++i) {
        x = read();
        line.push_back(x);
    }
    sort(line.begin(), line.end());
    dp[1][0] = abs(p[1][1] - 1) + abs(p[1][1] - 1);
    dp[1][1] = abs(p[1][1] - 1);
    int las = 1;
    for (rr i = 2; i <= n; ++i) {
        if (p[i][0] == inf) continue;
        for (rr u = 0; u < 2; ++u)
            for (rr v = 0; v < 2; ++v) {
                dp[i][v] =
                    min(dp[i][v], dp[las][u] + calc(las, u, i, v) + i - las);
            }
        las = i;
    }
    ll ans = min(dp[las][0], dp[las][1]);
    cout << ans;
}
```

---

## 作者：zhmshitiancai (赞：3)

[门门](https://codeforces.com/problemset/problem/1201/D)

### 题意：
一个$n \times m$的矩阵，初始时在$(1,1)$处，只能向上，向左，向右走，并且只有在给定列才能向上走。一些格子中有宝藏，问拿到所有宝藏的最小步数。


### 题解
考虑dp,$dp[i][0/1]$ 表示看到第$i$行，目前在此行的最左$/$右格子的宝藏，所需要的最小步数。

为什么要这样设计呢？

首先，因为不能向下走，所以在走到更高的一行前必须把这行的宝藏全经过，经过所有宝藏时，一定停在两端的宝藏上，可以证明这样最优。

转移时，只要考虑前一行宝藏最近的柱子。所以是$2 \times 2\times2 $ 的


### 注意
如果某一行没有宝藏，要把前一行的$dp$值和两端宝藏的位置都复制过来，$dp$值要$+1$，相当于直接向上平移。但如果这行后面都没有宝藏，这样就不对了，所以开始时，倒着扫一遍，如果没宝藏，就把$n$减一。

如果第一行没有宝藏，为了方便，就在$(1,1)$  处加一个宝藏，显然这样不影响答案。

这两个点卡了我好久。。。

### Tips:
1. 考虑问题要全面啊！

code:

```cpp
//love yjl forever;
#include<bits/stdc++.h>
using namespace std;
const int INF=0x3f3f3f3f,MAX=2e5+5;
int n,m,k,q;
int zz[MAX],zr[MAX];
int td[MAX];
int le[MAX],ri[MAX];
long long dp[MAX][2];
long long js(int now,int i)
{
	long long s=0;
	if(now<=zz[i])
		s+=zr[i]-now;
	else 
		s+=now-zz[i]+(zr[i]-zz[i]);
	return s;	
}

long long js1(int now,int i)
{
	long long s=0;
	if(now>=zr[i])
		s+=now-zz[i];
	else 
		s+=zr[i]-now+(zr[i]-zz[i]);
	return s;
}
int main()
{
/*	freopen("","r",stdin);
	freopen("","w",stdout);*/
	cin>>n>>m>>k>>q;
	int i;
	for(i=1;i<=n;i++)
		zz[i]=m+1;
	
	
	for(i=1;i<=k;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		zz[x]=min(zz[x],y);
		zr[x]=max(zr[x],y);
	}
	
	for(i=1;i<=q;i++)
	{
		int x;
		scanf("%d",&x);
		td[x]=1;
	}
	
	int x=0;
	for(i=1;i<=m;i++)
	{
		if(td[i]) x=i;
		le[i]=x;
	}
	
	x=m+1;
	for(i=m;i;i--)
	{
		if(td[i]) x=i;
		ri[i]=x;
	}	
	for(i=1;i<=n;i++)
		dp[i][0]=dp[i][1]=400000000000+5;
	
	if(zz[1]==m+1)
		zz[1]=zr[1]=1;
	
	dp[1][1]=zr[1]-1;
	dp[1][0]=dp[1][1]+zr[1]-zz[1];	
	
	while(zz[n]==m+1)
	{
		n--;
	}
	for(i=2;i<=n;i++)
	{
		if(zz[i]==m+1||!zr[i])
		{
			dp[i][0]=dp[i-1][0]+1;
			dp[i][1]=dp[i-1][1]+1;
			zz[i]=zz[i-1];
			zr[i]=zr[i-1];
			continue;
		}
		int now;
		long long s;
		//dp[i-1][1]--------dp[i][1];
		x=zr[i-1];
		if(le[x]!=0)
		{
			s=0;
			s+=1+x-le[x];
			now=le[x];
			s+=js(now,i);
			dp[i][1]=min(dp[i][1],s+dp[i-1][1]);
		}
		if(ri[x]!=m+1)
		{
			s=0;
			s+=ri[x]-x+1;
			now=ri[x];
			s+=js(now,i);
			dp[i][1]=min(dp[i][1],s+dp[i-1][1]);
		}
	//	if(i==3&&dp[i][1]==15)	cout<<1<<endl;

		//dp[i-1][0]--------dp[i][1];
		x=zz[i-1];
		if(le[x]!=0)
		{
			s=0;
			s+=1+x-le[x];
			now=le[x];
			s+=js(now,i);
			dp[i][1]=min(dp[i][1],s+dp[i-1][0]);
		}
		if(ri[x]!=m+1)
		{
			s=0;
			s+=ri[x]-x+1;
			now=ri[x];
			s+=js(now,i);
			dp[i][1]=min(dp[i][1],s+dp[i-1][0]);
		}
		//if(i==3&&dp[i][1]==15)	cout<<2<<endl;
		
		//dp[i-1][1]--------dp[i][0];
		x=zr[i-1];
		if(le[x]!=0)
		{
			s=0;
			s+=1+x-le[x];
			now=le[x];
			s+=js1(now,i);
			dp[i][0]=min(dp[i][0],s+dp[i-1][1]);
		}
		if(ri[x]!=m+1)
		{
			s=0;
			s+=ri[x]-x+1;
			now=ri[x];
			s+=js1(now,i);
			dp[i][0]=min(dp[i][0],s+dp[i-1][1]);
		}
		//dp[i-1][0]--------dp[i][0];
		x=zz[i-1];
		if(le[x]!=0)
		{
			s=0;
			s+=1+x-le[x];
			now=le[x];
			s+=js1(now,i);
			dp[i][0]=min(dp[i][0],s+dp[i-1][0]);
		}
		if(ri[x]!=m+1)
		{
			s=0;
			s+=ri[x]-x+1;
			now=ri[x];
			s+=js1(now,i);
			dp[i][0]=min(dp[i][0],s+dp[i-1][0]);
		}
	}
/*	for(i=1;i<=n;i++)
		cout<<dp[i][0]<<" "<<dp[i][1]<<endl;*/
	cout<<min(dp[n][0],dp[n][1])<<endl;
	return 0;
}
/*
3 6 2 2
2 2
3 4
1 6

*/
```


---

## 作者：Alioth_ (赞：3)

[原题链接](https://www.luogu.org/problem/CF1201D)

# 题解

大概就是说一个网格图 你在左下角 可以向上 向右 向左走 不能向下走 
而且向上走时只能通过指定的列向上走 有一些点有宝藏求把它们吃完的最小步数

![](https://codeforces.com/predownloaded/c7/2a/c72ae8d7e76c07277be9dd6841fa0d9bc199ab31.png)

看到不能向下走 想到$Dp$的阶段按行划分 本来我想$Dp[i][j]$表示当前在$i$行$j$列的最小代价 但光状态就存不下 后来一想 每一行吃完宝藏所在的点只能是$R[i]$或者$L[i]$即最左边或最右边的宝藏的位置 这样可以用$f[i][0/1]$表示一个状态 考虑转移 在这一行走很远找到一个向上的通道上去然后再在上面的一行吃肯定不如找最近的上去然后在上面的一行走更优 因为这样有了更多选择的余地 然后就可以用二分查找到最近的通道 计算$dis$后转移就行了 注意一行若没有东西 直接加$1$ 上去就行了

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+999;
int sum[maxn],f[maxn][2],b[maxn],l[maxn],r[maxn],n,s[maxn],m,k,q;
int dis(int pos,int h,int opt){
	if(!opt)return abs(pos-r[h])+abs(r[h]-l[h]);
	else return abs(pos-l[h])+abs(l[h]-r[h]);
}
int find_pos(int pos,int opt){
	if(!opt)
	{
		int l=0,r=pos;
		while(l<r){
			int mid=(l+r+1)>>1;
			if(sum[pos]-sum[mid-1]>0)l=mid;
			else r=mid-1;
		}
		return l;
	}
	else
	{
		int l=pos,r=m+1;
		while(l<r){
			int mid=l+r>>1;
			if(sum[mid]-sum[pos-1]>0)r=mid;
			else l=mid+1;
		}
		return l;
	}
}
 
signed main()
{
	cin>>n>>m>>k>>q;
	for(int i=1;i<=k;i++){
		int x,y;
		cin>>x>>y;
		x=n-x+1;
		l[x]=l[x]==0?y:min(l[x],y);
		r[x]=r[x]==0?y:max(r[x],y);
		s[x]++;
	}
	for(int i=1;i<=q;i++){
		int x;
		cin>>x;
		sum[x]=1;
	}
	for(int i=1;i<=m;i++)sum[i]=sum[i-1]+sum[i];
	memset(f,0x3f,sizeof(f));
	f[n][0]=dis(1,n,0);
	f[n][1]=dis(1,n,1);
	if(!s[n])f[n][0]=f[n][1]=0,l[n]=r[n]=1;
	for(int i=n-1;i>=1;i--)
	{
		if(!s[i]){f[i][0]=f[i+1][0]+1;l[i]=l[i+1],r[i]=r[i+1],f[i][1]=f[i+1][1]+1;continue;}
		int pos;
		pos=find_pos(l[i+1],0);
		if(pos)f[i][0]=min(f[i][0],f[i+1][0]+l[i+1]-pos+dis(pos,i,0)),f[i][1]=min(f[i][1],f[i+1][0]+l[i+1]-pos+dis(pos,i,1));
		pos=find_pos(l[i+1],1);
		if(pos!=m+1)f[i][0]=min(f[i][0],f[i+1][0]+pos-l[i+1]+dis(pos,i,0)),f[i][1]=min(f[i][1],f[i+1][0]+pos-l[i+1]+dis(pos,i,1));
		pos=find_pos(r[i+1],1);
		if(pos!=m+1)f[i][0]=min(f[i][0],pos-r[i+1]+f[i+1][1]+dis(pos,i,0)),f[i][1]=min(f[i][1],pos-r[i+1]+f[i+1][1]+dis(pos,i,1));
		pos=find_pos(r[i+1],0);
		if(pos!=0)f[i][0]=min(f[i][0],r[i+1]-pos+f[i+1][1]+dis(pos,i,0)),f[i][1]=min(f[i][1],r[i+1]-pos+f[i+1][1]+dis(pos,i,1));
		f[i][0]++;f[i][1]++;
	}
	for(int i=1;i<=n;i++)
		if(s[i]){
			cout<<min(f[i][0],f[i][1]);return 0;
		}
}
```

---

## 作者：allen2010 (赞：2)

# Part 0

~~感觉各位大佬的题解叙述有点炸裂，所以决定写一篇题解方便后人。~~

# Part 1 思路

显然这是一道 DP 题。因为不能向下走，所以每走到一行就必须拿完这行的所有宝藏。用 $dp[i][0/1]$ 表示**拿完**第 $i$ 行全部宝藏后在最左/最右宝藏的最小距离，可知转移分以下几种情况：

- 从上一行的左端点到这一行的右端点，再到这一行的左端点。

- 从上一行的右端点到这一行的右端点，再到这一行的左端点。

- 从上一行的左端点到这一行的左端点，再到这一行的右端点。

- 从上一行的右端点到这一行的左端点，再到这一行的右端点。

这样就可以保证能拿完这行的所有宝藏。

至于求不同行之间的两点的最小距离，可以使用 $O(\log n)$ 的二分查找，也可以用某些大佬的 $O(1)$ 预处理。我用的是二分查找。

# Part 3 注意事项

- 要开 ```long long```
- 对于顶端没有宝藏的多余行要删掉
- 如果这一行没有宝藏但后面的行有宝藏，可以虚拟两个宝藏，最小距离加1（相当于折叠了这一行）。

# Part 4 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int safe[200007];
int tleft[200007],tright[200007];
long long dp[200007][2];
int m,q;
int mdis(int x,int y)
{
    int ans=0x3f3f3f3f;
    if(x>y) swap(x,y);
    int op=lower_bound(safe,safe+q,x)-safe;
    if(op<q&&op>=0) ans=min(ans,abs(safe[op]-x)+abs(safe[op]-y));
    op=lower_bound(safe,safe+q,x)-safe-1;
    if(op<q&&op>=0) ans=min(ans,abs(safe[op]-x)+abs(safe[op]-y));
    op=lower_bound(safe,safe+q,y)-safe;
    if(op<q&&op>=0) ans=min(ans,abs(safe[op]-x)+abs(safe[op]-y));
    op=lower_bound(safe,safe+q,y)-safe-1;
    if(op<q&&op>=0) ans=min(ans,abs(safe[op]-x)+abs(safe[op]-y));
    return ans;
}
int main()
{
    int n,k;
    cin>>n>>m>>k>>q;
    while(k--)
    {
        int x,y;
        cin>>x>>y;
        if(!tleft[x]) tleft[x]=tright[x]=y;
        tleft[x]=min(tleft[x],y);
        tright[x]=max(tright[x],y);
    }
    for(int i=0;i<q;i++) cin>>safe[i];
    sort(safe,safe+q);//排序
    tleft[1]=1;
    while(!tleft[n]) n--;//去除空行
    memset(dp,0x3f,sizeof(dp));
    if(!tright[1]) tright[1]=1;
    else dp[1][1]=tright[1]-1;
    dp[1][0]=2*(tright[1]-1);
    tleft[0]=tright[0]=1;
    for(int i=2;i<=n;i++)
    {
        if(!tleft[i])
        {
            tleft[i]=tleft[i-1];
            tright[i]=tright[i-1];
            dp[i][0]=dp[i-1][0]+1;
            dp[i][1]=dp[i-1][1]+1;
            continue;
        }
        //四种情况
        dp[i][0]=min(dp[i][0],dp[i-1][0]+1+tright[i]-tleft[i]+mdis(tright[i],tleft[i-1]));
        dp[i][0]=min(dp[i][0],dp[i-1][1]+1+tright[i]-tleft[i]+mdis(tright[i],tright[i-1]));
        dp[i][1]=min(dp[i][1],dp[i-1][0]+1+tright[i]-tleft[i]+mdis(tleft[i],tleft[i-1]));
        dp[i][1]=min(dp[i][1],dp[i-1][1]+1+tright[i]-tleft[i]+mdis(tleft[i],tright[i-1]));
    }
    cout<<min(dp[n][0],dp[n][1]);
    return 0;
}
```

---

## 作者：Lamb_Carp (赞：0)

## advertisement

这位靓仔，你都来看我的题解了，为什么不来[我的博客](https://www.cnblogs.com/carp-oier/p/17772803.html)看一眼呢。

## analysis

我们首先通过读题就可以得出，我们要想走到下一层，必须先将这一层里面的所有宝藏都拿完。我们又可以想到，我们一定是直接从一端走到另外一端这样子才能保证在这一层中的花费时间最小。

所以对于每一层来说，我们只需要记录左右两个端点就好了。

对于每一个安全列来说，我们在通往下一层的时候都得要先走到这一列上，然后再转移到下一层之后，再转移到下一层的端点位置。

我们现在的问题就已经简化成了：

> 如何让我从一层转移到另外一层的花费最小。

我们就可以考虑存储一个前缀，表示这个列前面的第一个安全列的位置在哪里；同时存储一个后缀，表示这个列后面的第一个安全列在哪里。

我们的转移方程就呼之欲出（calc 函数用来求从这个端点到下一层端点的最近距离）：

$$f_{i, 0} \gets \min(f_{i - 1, 1} + calc(l_i, r_{i - 1}), f_{i - 1, 0} + calc(l_i, l_{i - 1}))$$
$$f_{i, 1} \gets \min(f_{i - 1, 1} + calc(r_i, r_{i - 1},  f_{i - 1, 0} + calc(r_i, l_{i - 1}))$$

## code time

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rl register ll
#define foa(i, a, b) for(rl i=a; i < b; ++ i)
#define fos(i, a, b) for(rl i=a; i <= b; ++ i)
#define fop(i, a, b) for(rl i=a; i >= b; -- i)
#define ws putchar(' ')
#define wl putchar('\n')

template <class T> inline void waw(T x)
{
    if(x > 9) waw(x / 10);
    putchar(x % 10 ^ 48);
}

template <class T> inline void ww(T x)
{
    if(x < 0) x = ~x + 1, putchar('-');
    waw(x);
}

template <class T> inline void read(T &res)
{
    char ch = getchar(); bool f = 0; res = 0;
    for(; !isdigit(ch); ch = getchar()) f |= ch == '-';
    for(; isdigit(ch); ch = getchar()) res = (res << 1) + (res << 3) + (ch ^ 48);
    res = f ? ~res + 1 : res;
}

const ll N = 2e5 +10;

ll f[N][2], l[N], r[N], pre[N], nxt[N], n, m;

bool sf[N];

inline ll calc(ll x, ll y)
{
    if(x > y) swap(x, y);
    if(pre[y] >= x) return y - x;
    
    ll res = 1e18;
    if(pre[x]) res = min(res, y + x - (pre[x] << 1));
    if(nxt[y]) res = min(res, (nxt[y] << 1) - x - y);
    return res;
}

int main()
{
    ll c, d; read(n), read(m), read(c), read(d);

    n = m = 0;
    
    fos(i, 1, c)
    {
        ll x, y; read(x), read(y); 
        n = max(n, x), m = max(m, y);
        l[x] = l[x] ? min(l[x], y) : y;
        r[x] = r[x] ? max(r[x], y) : y;
    }

    if(!l[1]) l[1] = r[1] = 1;
    
    memset(f, 0x3f, sizeof f);
    fos(i, 1, d) { ll x; read(x); m = max(m, x), sf[x] = 1; }
    fos(i, 1, m) pre[i] = sf[i] ? i : pre[i - 1];
    fop(i, m, 1) nxt[i] = sf[i] ? i : nxt[i + 1];

    f[1][0] = (r[1] << 1) - 1 - l[1], f[1][1] = r[1] - 1;

    fos(i, 2, n)
    {
        if(!l[i])
        {
            l[i] = l[i - 1], r[i] = r[i-1], f[i][0] = f[i-1][0], f[i][1] = f[i-1][1];
            continue;
        }
        f[i][0] = min(f[i-1][0] + calc(l[i], l[i-1]), f[i-1][1] + calc(r[i-1], l[i]));
        f[i][1] = min(f[i-1][0] + calc(r[i], l[i-1]), f[i-1][1] + calc(r[i-1], r[i]));
        swap(f[i][0], f[i][1]); f[i][0] += r[i] - l[i], f[i][1] += r[i] - l[i];
    }

    ww(min(f[n][0], f[n][1]) + n - 1), wl;
    return 0;
}
```

---

## 作者：Minuit (赞：0)

**Update:改了标点**

一个 $n\times m$ 的网格上有许多物品，每次可以向左右走，仅在给定的几个列可以向上走，求取完所有物品的最短路程。

显然不适合最短路，原因在于每次到达一行必定要走完这一行的所有物品，而穿过物品不回头从另一端离开显然不一定是最优的。

容易发现，对于每层，只需要考虑取完该层物品之后从哪里去往下一层，而取完物品时一定位于物品块的两端，于是从每层物品块两端分别向下一层物品块的两端转移，对于每个转移，考虑依次尝试离四个端点的最近的两个通道，显然没有比这四个通道更优的方法(其他都是冤枉路)，具体计算路程时还要考虑是否顺路完成了物品块的覆盖，以及是否需要走回头路。

细节较多，注意分类讨论：四端转移，每对有四种通道，每条路有四种通道与两端的相对位置，每种相对位置有左右端与左右端是否超过通道需要走回头路四种情况，共有 $4^4=64$ 种情况，依次讨论即可。

注意几个坑点：

- 端点可能就在通道上,.不用找左右端直接尝试转移即可。
- 从某层往上可能都没有物品,要把它们删掉。
- 某两层间可能有多层没有物品,用指针记录上一个有物品的层即可。

```cpp
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
const int N = 200005, INF = 0x7ffffff;
int n, m, k, q;
bool treasure_in_line[N];
int left_of_line[N], right_of_line[N], safecolumn[N], closest_left_safe_column[N], closest_right_safe_column[N], len[N];
int dp[N][2];
namespace solve
{
    void init()
    {
        ios::sync_with_stdio(false);
        cin >> n >> m >> k >> q;
        for (int i = 1; i <= n; i++)
            left_of_line[i] = m + 1, right_of_line[i] = -1;
        for (int i = 1; i <= k; i++)
        {
            int x, y;
            cin >> x >> y;
            treasure_in_line[x] = 1;
            left_of_line[x] = min(left_of_line[x], y);
            right_of_line[x] = max(right_of_line[x], y);
        }
        for (int i = 1; i <= n; i++)
            len[i] = right_of_line[i] - left_of_line[i];
        for (int i = 1; i <= q; i++)
        {
            int temp;
            cin >> temp;
            safecolumn[temp] = 1;
        }
        for (int i = 1; i <= m; i++)
        {
            if (!safecolumn[i])
                continue;
            closest_left_safe_column[i] = i;
            closest_right_safe_column[i] = i;
            int templ = i - 1, tempr = i + 1;
            while (templ >= 1 && !safecolumn[templ])
            {

                closest_right_safe_column[templ] = i;
                templ--;
            }
            while (tempr <= m && !safecolumn[tempr])
            {

                closest_left_safe_column[tempr] = i;
                tempr++;
            }
        }
        int cnt = n;
        for (cnt; cnt >= 1; cnt--)
            if (treasure_in_line[cnt])
                break;
        if (cnt < n)
            n = cnt;
    }
    int real_distant(int line1, int line2, int column1, int column2, int path, int lr1, int lr2)
    {
        int sum;
        if (path <= column1 && path <= column2)
        {
            sum = column1 - path + column2 - path + 1;
            if (lr2 == 0)
                sum += 2 * len[line2];
            else
            {
                if (left_of_line[line2] < path)
                    sum += 2 * (path - left_of_line[line2]);
            }
        }
        if (path <= column1 && path >= column2)
        {
            sum = column1 - column2 + 1;
            if (lr2 == 1)
                sum += 2 * len[line2];
            else
            {
                if (right_of_line[line2] > path)
                    sum += 2 * (right_of_line[line2] - path);
            }
        }
        if (path >= column1 && path <= column2)
        {
            sum = column2 - column1 + 1;
            if (lr2 == 0)
                sum += 2 * len[line2];
            else
            {
                if (left_of_line[line2] < path)
                    sum += 2 * (path - left_of_line[line2]);
            }
        }
        if (path >= column1 && path >= column2)
        {
            sum = path - column1 + path - column2 + 1;
            if (lr2 == 1)
                sum += 2 * len[line2];
            else
            {
                if (right_of_line[line2] > path)
                    sum += 2 * (right_of_line[line2] - path);
            }
        }
        return sum;
    }
    int get_dis(int low_line, int high_line, int low_line_column, int high_line_column, int position_low, int position_high)
    {
        int ans = INF;
        if (closest_left_safe_column[low_line_column])
            ans = min(ans, real_distant(low_line, high_line, low_line_column, high_line_column, closest_left_safe_column[low_line_column], position_low, position_high));
        if (closest_right_safe_column[low_line_column])
            ans = min(ans, real_distant(low_line, high_line, low_line_column, high_line_column, closest_right_safe_column[low_line_column], position_low, position_high));
        if (closest_left_safe_column[high_line_column])
            ans = min(ans, real_distant(low_line, high_line, low_line_column, high_line_column, closest_left_safe_column[high_line_column], position_low, position_high));
        if (closest_right_safe_column[high_line_column])
            ans = min(ans, real_distant(low_line, high_line, low_line_column, high_line_column, closest_right_safe_column[high_line_column], position_low, position_high));
        return ans;
    }
}
using namespace solve;
int head=1;
signed main()
{
    init();
    if (!treasure_in_line[1])
    {
        dp[1][0] = 0, dp[1][1] = 0;
        left_of_line[1] = 1, right_of_line[1] = 1;
        len[1] = 0;
    }
    else
        dp[1][0] = left_of_line[1] - 1 + 2 * len[1], dp[1][1] = right_of_line[1] - 1;
    for (int i = 2; i <= n; i++)
        if (treasure_in_line[i])
        {
            dp[i][0] = i - head - 1 + min(dp[head][0] + get_dis(head, i, left_of_line[head], left_of_line[i], 0, 0), dp[head][1] + get_dis(head, i, right_of_line[head], left_of_line[i], 1, 0));
            dp[i][1] = i - head - 1 + min(dp[head][0] + get_dis(head, i, left_of_line[head], right_of_line[i], 0, 1), dp[head][1] + get_dis(head, i, right_of_line[head], right_of_line[i], 1, 1));
            head = i;
        }
    cout << min(dp[n][0], dp[n][1]);
}
```



---

