# [USACO13NOV] Pogo-Cow S

## 题目描述

In an ill-conceived attempt to enhance the mobility of his prize cow Bessie, Farmer John has attached a pogo stick to each of Bessie's legs. Bessie can now hop around quickly throughout the farm, but she has not yet learned how to slow down.

To help train Bessie to hop with greater control, Farmer John sets up a practice course for her along a straight one-dimensional path across his farm.  At various distinct positions on the path, he places N targets on which Bessie should try to land (1 <= N <= 1000).  Target i is located at position x(i), and is worth p(i) points if Bessie lands on it.  Bessie starts at the location of any target of her choosing and is allowed to move in only one direction, hopping from target to target.  Each hop must cover at least as much distance as the previous hop, and must land on a target.

Bessie receives credit for every target she touches (including the initial target on which she starts).  Please compute the maximum number of points she can obtain.

FJ给奶牛贝西的脚安装上了弹簧，使它可以在农场里快速地跳跃，但是它还没有学会如何降低速度。


FJ觉得让贝西在一条直线的一维线路上进行练习，他在不同的目标点放置了N (1 <= N <= 1000)个目标点，目标点i在目标点x(i)，该点得分为p(i)。贝西开始时可以选择站在一个目标点上，只允许朝一个方向跳跃，从一目标点跳到另外一个目标点，每次跳跃的距离至少和上一次跳跃的距离相等，并且必须跳到一个目标点。


每跳到一个目标点，贝西可以拿到该点的得分，请计算他的最大可能得分。


## 说明/提示

There are 6 targets.  The first is at position x=5 and is worth 6 points, and so on.


Bessie hops from position x=4 (8 points) to position x=5 (6 points) to position x=7 (6 points) to position x=10 (5 points).


## 样例 #1

### 输入

```
6 
5 6 
1 1 
10 5 
7 6 
4 8 
8 10 
```

### 输出

```
25 
```

# 题解

## 作者：gzw2005 (赞：34)

[题目链接戳这里](https://www.luogu.com.cn/problem/P3089)

# 简明题意

$Betty$ 在一条直线的 $N(1\leq N\leq 1000)$ 个目标点上跳跃，目标点i在目标点 $x(i)$，得分为 $p(i)$。$Betty$ 可选择**任意一个目标点上**，**只朝一个方向跳跃**，且每次跳跃距离**成不下降序列**。每跳到一个目标点，$Betty$ 可以拿到该点的得分，求最大总得分。

---

首先第一步当然是把这些点按照坐标从小到大排序啦。

# ~~会MLE~~的DP做法

定义 $f(i,j)$ 表示当前 $Betty$ 跳到了第 $i$ 个点，且最小跳跃距离为 $j$ 的最大总得分。很容易得到状态转移方程：

$$f(i,j)=\max\{f(j,k)+s(i)\}(0\leq k\leq j)$$

显然又会 `MLE` 又会 `TLE`。

# 正常 DP 做法

由于 $Betty$ **只朝一个方向跳跃**，所以要分两种情况：一种是一直向右跳，一种是一直向左跳。

当一直向右跳时，定义 $f(i,j)$ 表示当前 $Betty$ 已经跳到了第 $i$ 个点，且最后一步是从第 $j$ 个点跳到第 $i$ 个点的最大总得分。那么

$$f(i,j)=\max\{f(j,k)+s(i)\}$$

其中 $k<j<i$，$x(j)-x(k)\leq x(i)-x(j)$。

考虑边界 $f(i,i)=s(i)$。（即一开始站在任意一个点上）

当一直向左跳时也同理，只不过方向倒过来而已。只要做两次 `DP` 就可以了。

这个时候时间复杂度为 $O(N^3)$，由于数据水，期望  $81pts$。

# 优化

第一步显然：$f(i,j)=\max\{f(j,k)+s(i)\}=\max\{f(j,k)\}+s(i)$

第二步：我们观察式子：

$$f(i-1,j)=\max\{f(j,k)\}+s(i-1)$$

我们发现和原来的式子非常像，好像可以直接 $f(i,j)=f(i-1,j)-s(i-1)+s(i)$，但是上面的式子定义范围会变成了$x(j)-x(k)\leq x(i-1)-x(j)$。由于 $x(i-1)<x(i)$，所以满足条件的 $k$ 会变多！所以我们需要将**拓展到的** $k$ 先取一个**最大值**，然后才能直接转移。

因为这个时候我们是从 $i-1$ 转移到 $i$ 的，所以我们要先枚举 $j$，再枚举  $i$。

```cpp
for(int j=1;j<=N;j++){
	f[j][j]=s(j);//边界
	for(int i=j+1,now=j+1;i<=N;i++){
		f[i][j]=f[i-1][j]-s(i-1);//先得到之前的max
		while(now>1 && x(j)-x(now-1)<=x(i)-x(j))
			f[i][j]=max(f[i][j],f[j][--now]);//取拓展到k的最大值
		f[i][j]+=s(i);//直接转移
		Ans=max(Ans,f[i][j]);
	}
}
```

如果是一直往左跳，就反着做一遍 `DP` 就可以了。

由于每个$k$ 只会被拓展 $1$ 次，时间复杂度为 $O(N^2)$。

# 程序

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int read(){
	char ch=getchar();int f=1,num=0;
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while('0'<=ch&&ch<='9'){num=num*10+ch-'0';ch=getchar();}
	return num*f;
}
int N,f[1002][1002],Ans;
struct Point{int x,s;} point[1002];
bool cmp(Point a,Point b){return a.x<b.x;}
#define x(i) point[i].x
#define s(i) point[i].s
int main(){
	N=read();
	for(int i=1;i<=N;i++)x(i)=read(),s(i)=read();
	sort(point+1,point+1+N,cmp);
	for(int j=1;j<=N;j++){
		f[j][j]=s(j);//边界
		for(int i=j+1,now=j+1;i<=N;i++){
			f[i][j]=f[i-1][j]-s(i-1);//先得到之前的max
			while(now>1 && x(j)-x(now-1)<=x(i)-x(j))
				f[i][j]=max(f[i][j],f[j][--now]);//取拓展到k的最大值
			f[i][j]+=s(i);//直接转移
			Ans=max(Ans,f[i][j]);
		}
	}
	for(int j=N;j>=1;j--){
		f[j][j]=s(j);
		for(int i=j-1,now=j-1;i>=1;i--){
			f[i][j]=f[i+1][j]-s(i+1);
			while(now<N && x(now+1)-x(j)<=x(j)-x(i))
				f[i][j]=max(f[i][j],f[j][++now]);
			f[i][j]+=s(i);
			Ans=max(Ans,f[i][j]);
		}
	}
	printf("%d",Ans);
	return 0;
}
```

---

## 作者：QwQcOrZ (赞：14)

发个 `2-points` 的做法

先将所有点按 $x$ 坐标升序排序

首先有个 simple 的想法是设 $dp_{i,j}$ 表示到第 $i$ 个点，从第 $j$ 个点转移过来的最大得分

然后可以得到一个朴素的 $O(n^3)$ 的转移：$f_{i,j}=\max\limits_{x_i-x_j\geq x_j-x_k}\{f_{j,k}\}+val$

考虑优化

将转移中的条件 $x_i-x_j\geq x_j-x_k$ 移项：$x_k\geq 2x_j-x_i$

也就是说当 $k$ 满足 $k\leq j$ 且 $x_k\geq 2x_j-x_i$ 时 $k$ 是合法的

容易发现合法的 $k$ 是一段连续的区间，且上界一定是 $j$

然后可以发现当 $j$ 增大时下界 $2x_j-x_i$ 也会增大

那么就可以用 `2-points` 实现找下界的过程，然后这段区间内的最大值可以使用后缀和查询优化

并不需要用单调队列……只需要一个后缀和即可，因为区间右端点是固定的

还有一些奇奇怪怪的细节，比如可以从任意一点开始任意一点结束、可以倒着跑等

具体可以看代码

$Code\ Below$

```cpp
#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
const int N=1e3+5;

inline int read()
{
	register int s=0;
	register char c=getchar(),lc='+';
	while (c<'0'||'9'<c) lc=c,c=getchar();
	while ('0'<=c&&c<='9') s=s*10+c-'0',c=getchar();
	return lc=='-'?-s:s;
}
void write(register int x)
{
	if (x<0)
	{
		putchar('-');
		x=-x;
	}
	if (x<10) putchar(x+'0');
	else
	{
		write(x/10);
		putchar(x%10+'0');
	}
}
inline void print(const register int x,const register char c='\n')
{
	write(x);
	putchar(c);
}
pair<int,int>a[N];
int dp[N][N];

signed main()
{
	int n=read();
	for (int i=1;i<=n;i++)
	{
		a[i].x=read();
		a[i].y=read();
	}
	sort(a+1,a+1+n);
	int ans=dp[1][1]=a[1].y;
	for (int i=2;i<=n;i++)
	{
		dp[i][i]=a[i].y;
		for (int j=1,k=1;j<i;j++)
		{
			while (k<j&&a[k].x<2*a[j].x-a[i].x) k++;
			dp[i][j]=dp[j][k]+a[i].y;
		}
		for (int j=i;j>=2;j--) dp[i][j-1]=max(dp[i][j-1],dp[i][j]);
		ans=max(ans,dp[i][1]);
	}
	for (int i=1;i<=n/2;i++) swap(a[i],a[n-i+1]);
	for (int i=1;i<=n;i++) a[i].x=1e6-a[i].x;
	ans=max(ans,dp[1][1]=a[1].y);
	for (int i=2;i<=n;i++)
	{
		dp[i][i]=a[i].y;
		for (int j=1,k=1;j<i;j++)
		{
			while (k<j&&a[k].x<2*a[j].x-a[i].x) k++;
			dp[i][j]=dp[j][k]+a[i].y;
		}
		for (int j=i;j>=2;j--) dp[i][j-1]=max(dp[i][j-1],dp[i][j]);
		ans=max(ans,dp[i][1]);
	}
	print(ans);

	return 0;
}
/*
for i=1 to n
for j=1 to i-1
for k=0 to j-1
if x_i-x_j>=x_j-x_k
f_i,j=max{f_j,k}+val

for i=1 to n
for j=1 to i-1
for k=0 to j-1
if x_k>=2*x_j-x_i
f_i,j=max{f_j,k}+val
*/
```

---

## 作者：Zxsoul (赞：12)

[我的博客-------------缓存机制（内存和缓存的区别）](https://www.cnblogs.com/lToZvTe/articles/14408479.html)
## 思路

$n^3$ 的简单思路（~~我只会这个~~）

$$
f[i][j]=max\{f[j][k]+e[i].val\}
$$

$f[i][j]$ 表示从 $j$ 到 $i$点的最大价值，转移的话就是枚举上一个目标点$k$,加上此次跳跃的价值取最大值即可

本人不会单调队列，所以我用了暴力，但是他过了，其实我用了细微但可以影响全局的优化

普通的人的三重循环都是标准的 $i,j,k$,但是枚举顺序不同也会变快


**“为什么枚举顺序不同，时间反而更快了？”**

我们不难发现我们的 $f[i][j]$ 是由 $f[j][k]$转移而来，有缓存机制（下面有说明）可知，为了快速读入，就要保证数据连续，在这的意思就是保证 $j$不变，$k$变，放到循环里来说就是 $j$在最外层，这样你就可以愉快的**AC** 了， 

## 枚举顺序与时间复杂度

我们都知道在电脑中**内存**相对于**外存**读入数据是快的，但还有比内存更快的，那就是**缓存**,它的作用是当计算机调用**内存**数据时，他会猜测你是否会用它的下一个数据，所以提前存入**缓存**，如果用到下一个数据，那就可以直接用，无需调用，这样的操作时间的差距在**10倍**左右

我们存储的二维数组在计算机中其实存在形式是**线性**,先行后列，所以假设有 $f[i][j]$, 若他的转移是 $f[j][k]$(就像此题)，当我们先枚举$j$ 再枚举 $i$，$k$ 这时，虽然转移后的结果没变，但是当调用 $f[j][k]$时，$j$是不变的，这就是 $缓存$

注：若您不信，可以实践一下，利用$C++$中的 $ctime$ 即可检验

再有，$max$函数相对于直接判断，也是慢了10倍哟

## Code
```c
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;

const int A = 1e5 + 11;
const int B = 1e6 + 11;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

inline int read() {
  char c = getchar();
  int x = 0, f = 1;
  for ( ; !isdigit(c); c = getchar()) if (c == '-') f = -1;
  for ( ; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
  return x * f;
}
struct node{
  int x,p;
  bool operator <(const node &a) const
  {
    return x<a.x;
  }
}e[B];

int n,m,f[2000][2000];
int main() {
//  freopen(".in", "r", stdin);
//  freopen(".out", "w", stdout);
  n=read();
  for (int i=1;i<=n;i++) {e[i].x=read(),e[i].p=read();}
  sort(e+1,e+1+n);
  int sum=0,ans=0;
  for (int j=1;j<=n;j++)
  {
   
    for (int i=j+1;i<=n;i++)
      {
      f[i][j]=f[j][0]+e[j].p;
        for (int k=j-1;k>=1;k--)
        {
          if(e[i].x-e[j].x>=e[j].x-e[k].x) 
            f[i][j]=max(f[i][j],f[j][k]+e[j].p);
        }
        ans=max(ans,f[i][j]+e[i].p);
      }
  }
  for (int j=n;j>=0;j--)
  {
    
    for (int i=j-1;i>=0;i--)
      {f[i][j]=f[j][n+1]+e[j].p;
        for (int k=j+1;k<=n;k++)
        {
          if(e[j].x-e[i].x>=e[k].x-e[j].x) 
//          if(f[j][k]+e[j].p > f[i][j]) f[i][j]=f[j][k]+e[j].p
            f[i][j]=max(f[i][j],f[j][k]+e[j].p);
        }
        ans=max(ans,f[i][j]+e[i].p);
      }
  }
  printf("%d",ans);
  fclose(stdin);
  fclose(stdout);
  return 0;
}

```



---

## 作者：rain_forest (赞：11)

UPD:改正错误

这道题一看很明显就是一道dp题，然后我们就可以快乐的去想怎么dp了

首先，这道题明显不可能是一维dp，三维又驾驭不住，所以说只能是二维dp了。

然后我们就可以去分析我们要压缩什么条件，很明显，我们可以搞出二维数组``f[i][j]``，表示**现在在i并且是从j跳过来时的最大得分**。

而很明显，状态转移方程就是``f[i][j]=max{f[i][k](k<=j,j<i&&x[i]-x[j]>=x[j]-x[k])}``，而它的初值就是无法用状态转移推出的状态，也就是``f[i][i]=p[i]``

因为可以往两个方向跳，所以我们就要扫两遍，那么我们就有了一个超级暴力的不AC代码。

```
#include<bits/stdc++.h>
using namespace std;
struct VAN{
	int x,p;
	bool operator <(const VAN &a) const{
		return x<a.x;
	}
}a[1001];
int n,f[1001][1001];
int main()
{
	scanf("%d",&n);
	for(register int i=1;i<=n;++i)
		scanf("%d%d",&a[i].x,&a[i].p);
	sort(a+1,a+n+1);
	for(register int i=1;i<=n;++i)
		f[i][i]=a[i].p;
	for(register int i=1;i<=n;++i)
		for(register int j=1;j<i;++j){
			//f[i][j]=a[i].p;
			for(register int k=1;k<=j;++k)
				if(a[j].x-a[k].x<=a[i].x-a[j].x)
					f[i][j]=max(f[i][j],f[j][k]+a[i].p);
			//f[i][j]+=a[i].p;
		}
	int ans=0;
	for(register int i=1;i<=n;++i)
		for(register int j=1;j<=n;++j)
			ans=max(ans,f[i][j]);
  	//倒着扫
	memset(f,-0x3f,sizeof(f));
	for(register int i=1;i<=n;++i)
		f[i][i]=a[n-i+1].p;
	for(register int i=1;i<=n;++i)
		for(register int j=1;j<i;++j){
			//f[i][j]=a[i].p;
			for(register int k=1;k<=j;++k)
				if(a[n-j+1].x-a[n-k+1].x>=a[n-i+1].x-a[n-j+1].x)
					f[i][j]=max(f[i][j],f[j][k]+a[n-i+1].p);
			//f[i][j]+=a[i].p;
		}
	for(register int i=1;i<=n;++i)
		for(register int j=1;j<=n;++j)
			ans=max(ans,f[i][j]);
	printf("%d\n",ans);
	return 0;
}
	
```
但是这种方法明显不能AC，而我们看到要维护``f[j][k]``的最大值，那么很显然我们就能想到用单调队列来维护它。**但是注意，这里维护最大值的时候我们入队了就不要出队，无论多大都不用退役，无论来了有多少比你小还比你强的你也不用滚蛋，所以我们用一个变量来维护最大值即可。**

代码如下
```
#include<bits/stdc++.h>
using namespace std;
struct VAN{
	int x,p;
	bool operator <(const VAN &a) const{
		return x<a.x;
	}
}a[1001];
int n,f[1001][1001];
int main()
{
	scanf("%d",&n);
	for(register int i=1;i<=n;++i)
		scanf("%d%d",&a[i].x,&a[i].p);
	sort(a+1,a+n+1);
	for(register int i=1;i<=n;++i)
		f[i][i]=a[i].p;
    for(register int j=1;j<=n;++j)
        for(register int i=j+1;i<=n;++i){
            int k=j,val=0;
            while(k>=1&&a[j].x-a[k].x<=a[i].x-a[j].x)
                val=max(val,f[j][k]+a[i].p),--k;
            f[i][j]=max(f[i][j],val);
        }
	int ans=0;
	for(register int i=1;i<=n;++i)
		for(register int j=1;j<=i;++j)
			ans=max(ans,f[i][j]);
	memset(f,-0x3f,sizeof(f));
	for(register int i=1;i<=n;++i)
		f[i][i]=a[n-i+1].p;
	for(register int j=1;j<=n;++j)
        for(register int i=j+1;i<=n;++i){
            int k=j,val=0;
            while(k>=1&&a[n-j+1].x-a[n-k+1].x>=a[n-i+1].x-a[n-j+1].x)
                val=max(val,f[j][k]+a[n-i+1].p),--k;
            f[i][j]=max(f[i][j],val);
        }
	for(register int i=1;i<=n;++i)
		for(register int j=1;j<=i;++j)
			ans=max(ans,f[i][j]);
	printf("%d\n",ans);
	return 0;
}
	
```


---

## 作者：asuldb (赞：9)

很奇特的题目啊，还要反着做一遍$dp$

我们设$dp[i][j]$表示到达第$i$个点，且是由$j$这个点转移过来的最大的得分是多少

于是我们就有$dp[i][j]=max(dp[j][k]+a[i])$，其中$x_j-x_k<=x_i-x_j$

于是我们就有了一个$O(n^3)$的转移

考虑优化，这个方程给人一种可以单调队列优化的感觉

我们对每一个位置$i$开一个单调队列，保存从$i$之前位置转移到$i$的最大的$dp$值

于是我们可以对于每一个位置存一个$last[i]$，表示$i$这个位置中当前还没有进队的最小转移位置，每次转移的时候就先将所有合法的转移位置入队，之后取出队首转移就好了

对于每一个位置来说它和之后的位置之间得距离越来越大，所以之前每一个合法的位置在之后也一定合法，所以可以这样来优化

然后还要记得正反做两遍

```cpp
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<queue>
#define re register
#define max(a,b) ((a)>(b)?(a):(b))
#define maxn 1001
struct Point
{
	int x,p;
}a[maxn];
int dp[maxn][maxn];
std::deque<int> q[maxn];
int last[maxn];
int ans=0;
int n;
inline int read()
{
	char c=getchar();
	int x=0;
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9')
		x=(x<<3)+(x<<1)+c-48,c=getchar();
	return x;
}
inline int cmp(Point K,Point M)
{
	return K.x<M.x;
}
inline int cop(Point K,Point M)
{
	return K.x>M.x;
}
int main()
{
	n=read();
	for(re int i=1;i<=n;i++)
		a[i].x=read(),a[i].p=read();
	std::sort(a+1,a+n+1,cmp);
	dp[1][1]=a[1].p;
	last[1]=0;
	q[1].push_back(1);
	for(re int i=2;i<=n;i++)
	{
		dp[i][i]=a[i].p;
		ans=max(ans,dp[i][i]);
		last[i]=i;
		for(re int j=1;j<i;j++)
		{
			while(last[j]&&a[j].x-a[last[j]].x<=a[i].x-a[j].x)
			{
				while(!q[j].empty()&&dp[j][last[j]]>dp[j][q[j].back()]) q[j].pop_back();
				q[j].push_back(last[j]);
				last[j]--;
			}
			dp[i][j]=dp[j][q[j].front()]+a[i].p;
			ans=max(ans,dp[i][j]);
		}
	}
	std::sort(a+1,a+n+1,cop);
	memset(dp,0,sizeof(dp));
	for(re int i=1;i<=n;i++)
		while(!q[i].empty()) q[i].pop_back();
	dp[1][1]=a[1].p;
	last[1]=0;
	q[1].push_back(1);
	for(re int i=2;i<=n;i++)
	{
		dp[i][i]=a[i].p;
		ans=max(ans,dp[i][i]);
		last[i]=i;
		for(re int j=1;j<i;j++)
		{
			while(last[j]&&a[j].x-a[last[j]].x>=a[i].x-a[j].x)
			{
				while(!q[j].empty()&&dp[j][last[j]]>dp[j][q[j].back()]) q[j].pop_back();
				q[j].push_back(last[j]);
				last[j]--;
			}
			dp[i][j]=dp[j][q[j].front()]+a[i].p;
			ans=max(ans,dp[i][j]);
		}
	}
	std::cout<<ans;
	return 0;
}
```

---

## 作者：ezоixx130 (赞：5)

首先这道题是一道dp题，仔细研究题意后不难得到如下的状态转移方程：

```cpp
f[i][j]=max{f[j][k]+p[i]}
```
其中f[i][j]代表最后一步是j->i时得分的最大值。

但是这样做的时间复杂度为O(n^3)，会超时。

仔细想一想后发现当i确定，枚举j时，信息可以共用：

即上一个f[i][j-1]的信息对于f[i][j]是有用的。

这样我们就得到了O(n^2)的代码。


代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

struct node{
    int a,b;
    friend bool operator<(const node &n1,const node &n2){
        return n1.a<n2.a;
    }
}a[1001];

int n,f[1001][1001],ans;

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)scanf("%d%d",&a[i].a,&a[i].b);
    sort(a+1,a+n+1);
    for(int i=1;i<=n;++i)
    {
        int now=i-1,val=f[i][0]+a[i].b;
        for(int j=i+1;j<=n;++j)
        {
            while(now>0&&a[j].a-a[i].a>=a[i].a-a[now].a)val=max(val,f[i][now--]+a[i].b);
            f[j][i]=max(f[j][i],val);
            ans=max(ans,val+a[j].b);
        }
    }
    for(int i=n;i>=0;--i)
    {
        int now=i+1,val=f[i][n+1]+a[i].b;
        for(int j=i-1;j>=0;--j)
        {
            while(now<=n&&a[i].a-a[j].a>=a[now].a-a[i].a)val=max(val,f[i][now++]+a[i].b);
            f[j][i]=max(f[j][i],val);
            ans=max(ans,val+a[j].b);
        }
    }
    printf("%d\n",ans);
}
```

---

## 作者：linaonao (赞：3)

首先这道题的数据特水，暴力开$O2$可以直接$A$掉。这里我直接说正解的作法（正解是我从暴力做法优化而来的）。

题目说FJ可以向某一个方向跳，所以可以分向左和向右两部分做，代码几乎一样，就是反过来$dp$，下面就向右跳讲一下：

记数组$f[i][j]$表示已经跳到了第$i$个点，且由第$j$个点跳过来的（这是$dp$的一个常见思路）。那么我们可以得到：

```cpp
f[i][j]=max(f[j][k]+point[i].p);//一

```
在通过类比上一个点的也能得出：

```cpp
f[i-1][j]=max(f[j][k]+point[i-1].p);//二
```
我们知道$dp$就是由之前的状态推到现在的状态,于是通过一二两式，我们得到：
```cpp
f[i][j]=f[i-1][j]-point[i-1].p+point[i].p;//三
```
通过观察我们知道二式范围（$k<j<i-1$&& $point[j].x-point[k].x<=point[i-1].x-point[j].x$）显然小于一式的范围，所以三式范围中$k$的值一定有一个最大值且满足单调性，我们先处理掉$k$的最值，转移即可。

还要注意的是$j$先枚举，因为我们是从上一个点转移到下一个点的，要先把$j$处理完才可以。

点坐标要排序这种显而易见的我就不做赘述了。

最后是贴代码时间：

```cpp
#include<bits/stdc++.h>
template<typename T>inline void read(T &x){
	T f=0;x=0;char ch=getchar();
    for(;!isdigit(ch);ch=getchar())f|=ch=='-';
    for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
    x=f?-x:x;
}
template<typename T>inline void write(T x){
	if(x<0){putchar('-');x=-x;}
	if(x>9)write(x/10);
	putchar(x%10+48);
}
using namespace std;
int f[1005][1005],n,ans;
struct node{int x,p;}point[1005];
bool cmp(node a,node b){return a.x<b.x;}
int main(){
	read(n);
	for(int i=1;i<=n;++i){
		read(point[i].x),read(point[i].p); 
	}
	sort(point+1,point+n+1,cmp);
	for(int j=1;j<=n;++j){
		f[j][j]=point[j].p;
		for(int i=j+1,now=j+1;i<=n;++i){
			f[i][j]=f[i-1][j]-point[i-1].p;
			while(now>1&&point[j].x-point[now-1].x<=point[i].x-point[j].x) f[i][j]=max(f[i][j],f[j][--now]);
			f[i][j]+=point[i].p;
			ans=max(ans,f[i][j]);
		}
	}
	for(int j=n;j>=1;--j){
		f[j][j]=point[j].p;
		for(int i=j-1,now=j-1;i>=1;--i){
			f[i][j]=f[i+1][j]-point[i+1].p;
			while(now<n&&point[now+1].x-point[j].x<=point[j].x-point[i].x) f[i][j]=max(f[i][j],f[j][++now]);
			f[i][j]+=point[i].p;
			ans=max(ans,f[i][j]);
		}
	}
	write(ans);
	return 0;
}

```




---

## 作者：VioletIsMyLove (赞：2)

拿到这道题就会有一个 $n^3$ 的方法，$f[j][i]$ 表示第j个人跳到 $i$，之后枚举一个 $k$，$f[j][i]=max(f[j][i],f[i][k]+a[j].v);$ (但为了好写代码里写的是 $f[i][j]$ ,这里写 $f[j][i]$ 方便解释)这是 $n^3$ 的方法（实测不开 $O2$ 能过），那有没有更优秀的方法呢？我们发现，当 $i$ 往后推了一位的时候，也就是 $f[j][i+1]$，原本 $f[j][i]$ 所能用到的 $j$ 都能用到，也就是下次再推 $j$ 的时候只需要从 $f[j][i]$ 的 $j$ 往前继续推就可以了，这里用单调队列来实现，就把时效降到了 $n^2$。但是！！！千万要注意，“只允许朝一个方向跳跃”，是指贝西要么只能往左跳，要么只能往右跳，所以要刷两趟 $dp$ ,向右跳的直接就处理掉了，而往左跳怎么处理呢？把每个坐标都 $*-1$，然后再把整个序列翻转就 $ok$  了，为什么要乘 $-1$ 呢，是因为要把它们的间距改掉嘛。

Code:

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1005;
struct ha{
	int x,p;
	bool operator<(const ha&b)const{return x<b.x;}
}a[maxn];
int n,f[maxn][maxn],ans;
inline int red(){
	int tot=0;char ch=getchar();
	while (ch<'0'||'9'<ch) ch=getchar();
	while ('0'<=ch&&ch<='9') tot=tot*10+ch-48,ch=getchar();
	return tot;
}
void DP(){
	memset(f,192,sizeof(f));
	for (int i=1;i<=n;i++) f[i][i]=a[i].p;
	for (int j=1;j<n;j++){
		int k=j,Max=f[j][j];
		for (int i=j+1;i<=n;i++){
			while (k&&a[j].x-a[k].x<=a[i].x-a[j].x) Max=max(Max,f[k--][j]);
			f[j][i]=Max+a[i].p;
			ans=max(ans,f[j][i]);
		}
	}
}
int main(){
	n=red();
	for (int i=1;i<=n;i++) a[i].x=red(),a[i].p=red();
	sort(a+1,a+1+n);
	DP();
	for (int i=1;i<=n;i++) a[i].x*=-1;
	reverse(a+1,a+1+n);
	DP();
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：hater (赞：2)

这道题的思路其他题解已经解释过了 

这里补充一些东西 

首先 这里的dp优化应该不能算作单调队列吧 

这里转移中的决策集合只多不少 

可以拿一个变量记录决策集合的最大值 避免重复扫描 

~~（ 算法竞赛指南 267 ）~~  

单调队列这不出队头还算是单调队列吗 

你要队列的极值 直接拿个变量转移就好了啊 

之后还有本题还有一个小技巧 

第二遍可以不用倒着码一遍dp 

我们形象的把x画成一根数轴 

保持点和点之间的相对距离不变 

之后把原点挪到最大值 正负方向换一下 

也就是下面这个玩意 

```cpp
fp( i , 1 , n ) a[i].x = t - a[i].x ; 
fp( i , 1 , n/2 ) swap( a[i] , a[n-i+1] ) ; 
```

这个正确性不用讲了吧

之后复制粘贴就可以了 

---

## 作者：Frostnova (赞：2)

## 82分做法：

$O(n^3)$暴力$dp$算法

核心代码：

```cpp
FOR(i, 1, n) {
        FOR(j, 1, i - 1) {
            FOR(k, 1, j) {
                if(x[j] - x[i] >= x[k] - x[j]) {
                    f[i][j] = max(f[i][j], f[j][k] + p[i]);
                }
            }
            ans = max(ans, f[i][j]);
            // Write(f[i][j]);
            // printf(" ");
        }
        //puts("");
    }
    
```

注意：初值要在排序后赋

##### ~~挂C++17+O2可以直接A~~

---

## 满分做法：

如果要用优先队列优化必须先枚举中间节点,再枚举后一个和前一个
因为如果先枚举后一个再枚举前一个, 对于i来说, $j$, $k$都在动,不能利用上之前得结果求最大值.
而先枚举中间的话, 永远都是$f[j][k]$求最大值,这时候就可以用单调队列存储


```cpp

#include <bits/stdc++.h>
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define _FOR(i, a, b) for(int i = a; i >= b; i--)
typedef long long ll;
namespace fast_IO {
    const int IN_LEN = 10000000, OUT_LEN = 10000000;
    char ibuf[IN_LEN], obuf[OUT_LEN], *ih = ibuf + IN_LEN, *oh = obuf;
    char *lastin = ibuf + IN_LEN;
    const char *lastout = ibuf + OUT_LEN - 1;
    inline char getchar_() {
        if(ih == lastin) {
            lastin = ibuf + fread(ibuf, 1, IN_LEN, stdin);
        }
        return (*ih++);
    }
    inline void putchar_(const char x) {
        if(ih == lastout) {
            fwrite(obuf, 1, oh - obuf, stdout);
            oh = obuf;
        }
        *oh++ = x;
    }
    inline void flush() {
        fwrite(obuf, 1, oh - obuf, stdout);
    }
}
using namespace fast_IO;
using namespace std;
template <typename T>
inline void Read(T &x) {
    char cu = getchar();
    x = 0;
    bool fla = 0;
    while(!isdigit(cu)) {
        if(cu == '-') {
            fla = 1;
        }
        cu = getchar();
    }
    while(isdigit(cu)) {
        x = x * 10 + cu - '0';
        cu = getchar();
    }
    if(fla) {
        x = -x;
    }
}
template<typename T>
void printe(const T x) {
    if(x >= 10) {
        printe(x / 10);
    }
    putchar(x % 10 + '0');
}
template<typename T>
inline void Write(const T x) {
    if(x < 0) {
        putchar('-');
        printe(-x);
        return ;
    }
    printe(x);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int n, ans = -1e9;

// f[i][j]表示最近一跳为从目标点j跳到目标点i的最大得分
int f[2000][2000];
struct Node {
    int x, p;
} a[2000];
bool cmp1(Node a, Node b) {
    return a.x < b.x;
}
bool cmp2(Node a, Node b) {
    return a.x > b.x;
}
deque <Node> q;
int main() {
    Read(n);
    FOR(i, 1, n) {
        Read(a[i].x), Read(a[i].p);

    }
    
    sort(a + 1, a + 1 + n, cmp1);

    FOR(i, 1, n) {
        f[i][i] = a[i].p;
    }
    // FOR(i, 1, n) {
    //     cout << x[i] << " " << p[i] << endl;
    // }
    // puts("");
    FOR(j, 1, n) {
        int len = j, maxn = 0;
        FOR(i, j + 1, n) {
            while (len >= 1 && a[len].x >= 2 * a[j].x - a[i].x) {
                maxn = max(maxn, f[j][len]);
                len--;
            }
            f[i][j] = maxn + a[i].p;
            ans = max(ans, f[i][j]);
            // Write(f[i][j]);
            // printf(" ");
        }
        //puts("");
    }
    
    sort(a + 1, a + 1 + n, cmp2);

    memset(f, 0, sizeof(f));
    FOR(i, 1, n) {
        f[i][i] = a[i].p;
    }

    FOR(j, 1, n) {
        int len = j, maxn = 0;
        FOR(i, j + 1, n) {
            while (len >= 1 && a[len].x <= 2 * a[j].x - a[i].x) {
                maxn = max(maxn, f[j][len]);
                len--;
            }
            f[i][j] = maxn + a[i].p;
            ans = max(ans, f[i][j]);
            // Write(f[i][j]);
            // printf(" ");
        }
        //puts("");
    }
    cout << ans;
}

/*
6 
5 6 
1 1 
10 5 
7 6 
4 8 
8 10 
1 _ _ 8 6 _ 6 10 _ 5

*/


```





---

## 作者：zx2003 (赞：1)

```cpp
{$A+,B-,D-,E-,F-,G+,I-,L-,N+,O+,P+,Q-,R-,S-,T-,V-,X+,Y-}
{$M 65520,0,655360}
{$inline on}
type
 ys=record
```
len,da:longint
 end;
 point=record

xx,pp:longint


```cpp
 end;
operator <(a,b:point)c:boolean;
begin
 c:=a.xx<b.xx
end;
var
 ans,i,n,j,w,l,r,m:Longint;
 a:array[1..1000] of point;
 f:array[1..1000,0..1000] of ys;
 ll:array[1..1000] of longint;
 procedure sort(l,r: longint);
      var
         i,j: longint;
         x,y:point;
      begin
         i:=l;
         j:=r;
         x:=a[(l+r) div 2];
         repeat
           while a[i]<x do
            inc(i);
           while x<a[j] do
            dec(j);
           if not(i>j) then
             begin
                y:=a[i];
                a[i]:=a[j];
                a[j]:=y;
                inc(i);
                j:=j-1;
             end;
         until i>j;
         if l<j then
           sort(l,j);
         if i<r then
           sort(i,r);
      end;
begin
// assign(input,'aaa.in');reset(input);
 readln(n);
 for i:=1 to n do readln(a[i].xx,a[i].pp);
 sort(1,n);
 ll[1]:=1;
 f[1,1].da:=a[1].pp;
 ans:=a[1].pp;
 for i:=2 to n do
 begin
  for j:=1 to i-1 do
  begin
   l:=1;
   r:=ll[j];
   while l<r do
   begin
    m:=(l+r) shr 1;
    if f[j,m].len>a[i].xx-a[j].xx then l:=m+1
     else r:=m
   end;
   m:=f[j,l].da+a[i].pp;
   if m>ans then ans:=m;
   while (ll[i]>0)and(f[i,ll[i]].da<=m) do dec(ll[i]);
   inc(ll[i]);
   f[i,ll[i]].da:=m;
   f[i,ll[i]].len:=a[i].xx-a[j].xx
  end;
  while (ll[i]>0)and(f[i,ll[i]].da<=a[i].pp) do dec(ll[i]);
  inc(ll[i]);
  f[i,ll[i]].da:=a[i].pp;
  if a[i].pp>ans then ans:=a[i].pp;
  f[i,ll[i]].len:=0
 end;
 fillchar(f,sizeof(f),0);
 fillchar(ll,sizeof(ll),0);
 ll[n]:=1;
 f[n,1].da:=a[n].pp;
 for i:=n-1 downto 1 do
 begin
  for j:=n downto i+1 do
  begin
   l:=1;
   r:=ll[j];
   while l<r do
   begin
    m:=(l+r) shr 1;
    if f[j,m].len>a[j].xx-a[i].xx then l:=m+1
     else r:=m
   end;
   m:=f[j,l].da+a[i].pp;
   if m>ans then ans:=m;
   while (ll[i]>0)and(f[i,ll[i]].da<=m) do dec(ll[i]);
   inc(ll[i]);
   f[i,ll[i]].da:=m;
   f[i,ll[i]].len:=a[j].xx-a[i].xx
  end;
  while (ll[i]>0)and(f[i,ll[i]].da<=a[i].pp) do dec(ll[i]);
  inc(ll[i]);
  f[i,ll[i]].da:=a[i].pp;
  if a[i].pp>ans then ans:=a[i].pp;
  f[i,ll[i]].len:=0
 end;
 writeln(ans)
end.
```
先只考虑一个方向上的。（另一个方向的话只要反向做一遍就好了）

首先，肯定要先按照横坐标将这些点排序。


其实 O(N^3) 的 DP 是不难想到的：用 f(i, j) 表示从 i 跳到 j 再往后跳的最大得分（因为只考虑单方向所以假设 j > i），则


f(i, j) = w(i)+max{ f(j, k) }, k>j 且 x(k)-x(j) >= x(j)-x(i)



w(i) 表示第 i 个点的权值。

然后优化：


对于上面方程中的 k，我们只要找到第一个满足条件的 k 就会发现 k+1, k+2, ..., n 都是满足条件的。


那么我们干脆维护一个区间最大值：用 m(i, j) 表示 max{ f(i, j), f(i, j+1), ..., f(i, n) }


于是上面的方程就可以改写成：


f(i, j) = w(i)+m(j, k), k>j 且 k 是满足条件 x(k)-x(j) >= x(j)-x(i) 的第一个点


显然我们可以用二分查找来找到这个 k。


至于 m(i, j) 的维护，因为 k 在 j 的后面所以我们是倒着来 DP（i 和 j 逆序枚举），那么得到一个 f(i, j) 之后就可以更新 m(i, j) 的值了：



m(i, j) = max{ f(i, j), m(i, j+1) }

至此，问题的复杂度降为 O(N2logN)。

另：luogu现在pascal允许开编译开关了，这有利于卡常


---

