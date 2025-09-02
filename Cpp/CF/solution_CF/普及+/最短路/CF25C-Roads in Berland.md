# Roads in Berland

## 题目描述

There are $ n $ cities numbered from 1 to $ n $ in Berland. Some of them are connected by two-way roads. Each road has its own length — an integer number from 1 to 1000. It is known that from each city it is possible to get to any other city by existing roads. Also for each pair of cities it is known the shortest distance between them. Berland Government plans to build $ k $ new roads. For each of the planned road it is known its length, and what cities it will connect. To control the correctness of the construction of new roads, after the opening of another road Berland government wants to check the sum of the shortest distances between all pairs of cities. Help them — for a given matrix of shortest distances on the old roads and plans of all new roads, find out how the sum of the shortest distances between all pairs of cities changes after construction of each road.

## 样例 #1

### 输入

```
2
0 5
5 0
1
1 2 3
```

### 输出

```
3 ```

## 样例 #2

### 输入

```
3
0 4 5
4 0 9
5 9 0
2
2 3 8
1 2 1
```

### 输出

```
17 12 ```

# 题解

## 作者：Suiseiseki (赞：10)

看到任意两点之间的最短路，我们很容易就可以想到floyd，没有错，这一道题就是floyd，一道最短路题。

但是$O(n^4)$会超时怎么办！考虑到我们每次只更新一条边，所以只需要floyd里面的循环即可，时间复杂度$O(n^3)$，可以通过本题。

下面是代码：
```cpp
#include <cstdio>
int mp[305][305];
int mn(int a,int b){
	return a<b?a:b;
}
int main(){
	int n;
	int k;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%d",&mp[i][j]);
		}
	}
	scanf("%d",&k);
	int a,b,c;
	long long sum;
	while(k--){
		scanf("%d%d%d",&a,&b,&c);
		sum=0;
		if(mp[a][b]>c){//小优化，当能够更新时才做
			mp[a][b]=mp[b][a]=c;
			for(int i=1;i<=n;i++){
				for(int j=1;j<=n;j++){
					if(i==j){
						continue;
					}
					mp[i][j]=mp[j][i]=mn(mp[i][j],mp[i][a]+mp[a][j]);
					mp[i][j]=mp[j][i]=mn(mp[i][j],mp[i][b]+mp[b][j]);
				}
			}//标准的floyd
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				sum+=mp[i][j];
			}
		}
		printf("%I64d ",sum>>1);//结果要用long long，并且我们将同一条边计算了两次，需要/2
	}
	puts("");
	return 0;
}

```

---

## 作者：dzz1537568241 (赞：5)

第一眼看过去，反应是：Floyd的板子题？模板？水题？当然都不是。

# 这是一道NOIP真题。


不知道各位有没有做过, 这个 [P1119 灾后重建](https://www.luogu.org/problem/P1119)
 
首先， floyd 相对于 spfa 和 dijkstra，有一个很本质上的区别

floyd求解的是：

# 多源最短路

而 dij 和 ~~某已死算法~~求解的是

### 单源最短路

众所周知，多源最短路的意义是能够求出所有点到所有点的最短路径，我floyd能做的到的事情，它 dijkstra 能做的到吗？

dijkstra(弱弱)：可是一旦变成稀疏图了你就做不到了啊

对，floyd有一个致命的缺陷，就是一旦点非常大，比如像50000这种数量的点，用floyd去求解最短路明显是不可能的（二维数组都容不下），反过来说：

# 如果点数少，那一定优先考虑floyd

这道题目里，看到 n <= 300, 基本可以确定是用floyd了。

然后我们看到了

**每个点之间的最短路**

我笑了。

floyd裸题啊。

# 二，floyd的性质

毫无疑问，能够找到这道题目是你的幸运，通过这道题目，你可以彻底弄清楚floyd怎么求解出最短路径的。

首先来看，floyd怎么通过套三重循环得出多源点最短路的？

我们一层一层扒开来瞧瞧。

首先是最外层循环，它枚举了中间点 k。

然后是里面的两层，枚举了 1~N 的每一个点对( i, j )。

duài ，然后呢?

然后就是对floyd的理解问题了，

我们认为，**第一层循环表示只经过k点形成的最短路**，进行松弛操作。

可以想象成一排排路灯，随着k的枚举，路灯一盏盏被点亮，点对之间的最短路被不断的，而当k来到第N个点结束后，最后一盏灯被点亮，最短路被求出。

而这道题目呢？

可以认为 加入两条边，相当于**熄灭两盏灯**（经过这两个节点形成的最短路需要被更新），因此可以**略去一重循环**，只需要枚举以 **两个节点作为中间点的最短路**即可

最后给出代码:

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#define int long long
using namespace std;
int rd(){
	int x = 0, f = 1; char c = getchar();
	while(c < '0' || c > '9'){if(c == '-'){f = -1;}c = getchar();}
	while(c >= '0' && c <= '9'){x = x * 10 + c - '0'; c = getchar();} 
	return x * f;
} 

const int maxn = 350;
int a[maxn][maxn], p[maxn], N, T, t1, t2, t3, ans;

signed main(){
	//freopen("CF25C Roads in Berland.in", "r", stdin);
	//freopen("CF25C Roads in Berland.in", "w", stdout);
	N = rd();
	for(int i = 1; i <= N; i++){
		for(int j = 1; j <= N; j++){
			a[i][j] = rd();
		}
	}
	T = rd();
	
	for(int kkk = 1; kkk <= T; kkk++){
		t1 = rd(), t2 = rd(), t3 = rd();
		if(a[t1][t2] > t3){
			int k = t1;
			a[t1][t2] = t3;
			a[t2][t1] = t3;
			k = t1;
			for(int i = 1; i <= N; i++){
				for(int j = 1; j <= N; j++){
					if(i == j)continue;
					a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
					a[j][i] = a[i][j];
				}
			}
			k = t2;
			for(int i = 1; i <= N; i++){
				for(int j = 1; j <= N; j++){
					if(i == j)continue;
					a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
					a[j][i] = a[i][j];
				}
			}
		}
		ans = 0;
		for(int i = 1; i <= N; i++){
			for(int j = 1; j <= N; j++){
				ans += a[i][j];
			//cout<<ans<<endl;
			}
		}
		p[kkk] = ans/2;
	}
	for(int i = 1; i <= T; i++){
		cout<<p[i]<<endl;	
	}
	//fclose(stdin);
	//fclose(stdout);
}
```

# 祝各位~~NOIP~~   CSP RP++

---

## 作者：szbszb (赞：2)

这是一道考Floyd的好题目

与其类似的还有[P1119 灾后重建](https://www.luogu.org/problem/P1119)，不同的是一个是加点，一个是加边。

如果并不会最短路算法的[欢迎到我的博客参观~](https://www.cnblogs.com/szbszb/p/11280672.html)

考虑每加进一条边，如果它本来就比最短路长，那就不用更新了，而如果更短的话，我们用Floyd对该路径的两个端点进行重新处理，再对答案进行更新就行了。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,i,j,q,x,y,l,ans,p[301][301];
int main()
{
	scanf("%lld",&n);
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++)
		scanf("%lld",&p[i][j]);
	scanf("%lld",&q);
	for (i=1;i<=n;i++)
		for (j=i+1;j<=n;j++)
		ans+=p[i][j];//先求一遍答案，因为如果第一条要改的路更长会直接输出ans，那就会直接输出0,，所以就先求一遍了
	while(q--)
	{
		scanf("%lld%lld%lld",&x,&y,&l);
		if (p[x][y]<=l)//如果新加进去的更长，那就不用重新算了
		{
			printf("%lld ",ans);
			continue;
		}
		p[x][y]=l;
		p[y][x]=l;
		for (i=1;i<=n;i++)
			for (j=1;j<=n;j++)
			if (i!=j)
			{
				p[i][j]=min(p[i][j],p[i][x]+p[x][j]);//对修改的两个端点进行更新
				p[i][j]=min(p[i][j],p[i][y]+p[y][j]);
			}
		ans=0;
		for (i=1;i<=n;i++)
			for (j=i+1;j<=n;j++)//这样子的话就不会出现边求了两次的问题了
			ans+=p[i][j];
		printf("%lld ",ans);
	}
	return 0;
}
```
不得不说，在求多源最短路径上，Floyd的n3做法已经是足够的了，优化是有，但也相差不大

希望这篇题解能让你再进一步！

---

## 作者：PrincessYR✨～ (赞：2)

~~Dij~~（floyd）

一看道标签为最短路，一进来我就打了Dij，整整卡了我一个小时。

结果发现正解是floyd，我太难了。

来讲一下这道题为什么用floyd：

我们都知道Dij只能求单源最短路，也就是事先必须确定起点，然后求到每个点的距离，然而这道题让求所有路径的和，也就是全源最短路，而且n<=300，数据范围也不是很大,所以用到了floyd。

```
for(int k=1;k<=n;k++)
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		if(dis[i][j]>dis[i][k]+dis[k][j])
		{
			dis[i][j]=dis[i][k]+dis[k][j];
		}
	}
}
```


这是一个标准的floyd，而floyd最后求出来的答案存储在dis[i][j]中，也就是以i为起点，j为终点，呢么跑floyd的话，只用跑一遍,而Dij最坏情况下要跑k*n遍

```
#include<bits/stdc++.h>
using namespace std;
#define si 305
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
inline void write(int a){
   if(a<0) putchar('-'),a/=-1;
   if(a>9) write(a/10);
   putchar(a%10+'0');
}
int n,dis[si][si],a,b,c,k,d;
long long ans;
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cin>>a;
			dis[i][j]=a;
		}
	}
	k=read();
	for(int w=1;w<=k;w++)
	{
		cin>>b>>c>>d;
		if(dis[b][c]>d)//如果修后道路变得更长了，那么我们就不需要更新
		{
		 dis[b][c]=d;
		 dis[c][b]=d;
		 for(int k=1;k<=n;k++)
		 {
			for(int i=1;i<=n;i++)
			{
				if(k==i) continue;
				else
				dis[i][k]=dis[k][i]=min(dis[k][i],min(dis[k][b]+dis[b][i],dis[k][c]+dis[c][i]));//核心代码
			}
		 }
		} 
		for(int i=1;i<=n;i++)
		{
			for(int j=i+1;j<=n;j++)
			{
				ans+=dis[i][j];
			}
		}
		cout<<ans<<endl;
		ans=0;
	}
	return 0;
}
 
```


---

## 作者：G_A_TS (赞：1)

题解同步发布于[blog](https://www.cnblogs.com/wzzorz/articles/10367221.html)  

------------
[Codeforces](http://codeforces.com/contest/25/problem/C)  
[luogu](https://www.luogu.org/problemnew/show/CF25C)  
其实前一篇题解讲得很清楚了(发自内心)  
每次插边更新一次  
最后/=2  
这里补充[Floyd](https://www.cnblogs.com/GumpYan/p/5540549.html)的基础知识，这篇目测可以(会最短路的可以忽略)  
~~开long long保险好~~  

------------
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,dist[1010][1010],ans;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cin>>dist[i][j];
			ans+=dist[i][j];
		}
	}
	cin>>k;
	int a,b,c;
	for(int js=1;js<=k;js++)
	{
		cin>>a>>b>>c;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				if(dist[i][a]+dist[b][j]+c<dist[i][j])
				{
					ans-=dist[i][j]-(dist[i][a]+dist[b][j]+c);
                    dist[i][j]=dist[i][a]+dist[b][j]+c;
				}
				if(dist[i][b]+dist[a][j]+c<dist[i][j])
				{
					ans-=dist[i][j]-(dist[i][b]+dist[a][j]+c);
                    dist[i][j]=dist[i][b]+dist[a][j]+c;
				}
			}
		}
		cout<<ans/2<< " ";
	}
}
```

---

## 作者：DinnerHunt (赞：0)

> 点和新边的数量在`200`以内,然后每次只更新一条边,就很容易想到`flody`，每次插边都更新一次两点间的最短距离就可以了  
> 存值要用 long long 不然会 WA  
> 新边是双向的，所以$dp[i][a]+dp[b][j],dp[i][b]+dp[a][j]$ 都要考虑

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxd = 300+10;
long long  arr[maxd][maxd],ans,c;
int a,b,k,n;
int main()
{
    // freopen("a.in","r",stdin);
    // freopen("k.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            cin >> arr[i][j];      
            ans += arr[i][j];
        }
    // for(int i=1;i<=n;i++)
    //     for(int j=1;j<=n;j++)
    //         for(int k=1;k<=n;k++)
    //             arr[i][j] = min(arr[i][k]+arr[k][j],arr[i][j]);
    // for(int i=1;i<=n;i++)
    //     for(int j=1;j<=n;j++)
    //         ans += G[i][j];
    scanf("%d",&k);
    while(k--)
    {
        cin >> a >> b >> c;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
            {
                if(arr[i][j] > arr[i][a]+arr[b][j]+c)
                {
                    ans -= arr[i][j] - (arr[i][a] + arr[b][j] + c);
                    arr[i][j] = arr[i][a] + arr[b][j] + c;
                }
                if(arr[i][j] > arr[i][b]+arr[a][j]+c)
                {
                    ans -= arr[i][j] - (arr[i][b] + arr[a][j] + c);
                    arr[i][j] = arr[i][b] + arr[a][j] + c;
                }
            }
        cout << ans / 2 << " ";
    }
    return 0;
}
```

---

