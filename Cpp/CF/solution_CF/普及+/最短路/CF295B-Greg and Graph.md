# Greg and Graph

## 题目描述

Greg 有一个有边权的有向图，包含 $n$ 个点。这个图的每两个点之间都有两个方向的边。Greg 喜欢用他的图玩游戏，现在他发明了一种新游戏：

- 游戏包含 $n$ 步。
- 第 $i$ 步 Greg 从图中删掉编号为 $x_i$ 的点。当删除一个点时，这个点的出边和入边都会被删除。
- 在执行每一步之前，Greg 想知道所有点对间最短路长度的和。最短路可以经过任何没删掉的点。换句话说，如果我们假设 $d(i, v, u)$ 是在删掉 $x_i$ 前 $v$ 和 $u$ 间的最短路长度，那么Greg想知道下面这个求和的值：$\sum_{v, u, v \neq u} d(i, v, u)$ 。

帮帮 Greg，输出每一步之前要求的值。

## 样例 #1

### 输入

```
1
0
1
```

### 输出

```
0 ```

## 样例 #2

### 输入

```
2
0 5
4 0
1 2
```

### 输出

```
9 0 ```

## 样例 #3

### 输入

```
4
0 3 1 1
6 0 400 1
2 4 0 1
1 1 1 0
4 1 2 3
```

### 输出

```
17 23 404 0 ```

# 题解

## 作者：Dream_weavers (赞：29)

[题目传送门](https://www.luogu.com.cn/problem/CF295B)

## 题意

给出一个包含 $n$ 个点的**有向带权图**，第 $i$ 次求出图中两两相连的点的**最短路径**和，并删除点 $x_i$。

## 思路

此题推荐用 Floyd，循环 $n$ 次的 Dijkstra 和 SPFA 肯定会超时。

正向思路是按照题意每次删除点 $x_i$，但 Floyd 不支持删除点，并且这样做会很麻烦：每到一个点 $x_i$就要做一次复杂度为 $O(n^3)$ 的 Floyd，整体复杂度为 $O(n^4)$，也会超时。

所以我们逆向思考，看成每次添加一个点 $x_i$，并记录该点出现过。在计算总和时特判这些点是否出现过，记录答案。最后倒序输出。时间复杂度 $O(n^3)$。

## 代码

以下为核心代码，其余部分用注释略过。

```cpp
//输入n
//输入有向带权图
//输入数组x
for(int l=n;l>=1;l--){//循环每一个点
	int k=x[l];vis[k]=1;//标记并记录添加的点
		
	for(int i=1;i<=n;i++)//进行一次Floyd	
		for(int j=1;j<=n;j++)
			d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
	   
	sum=0;
	for(int i=1;i<=n;i++)//统计最短路的和
		for(int j=1;j<=n;j++)
			if(vis[i]&&vis[j])
				sum+=d[i][j];
	ans[l]=sum;//记录答案
}
//倒序输出答案
```

---

## 作者：RainAir (赞：8)

### 题目大意

给定一个 $N$ 个点的完全图，每次删掉一个点，询问剩下每一对点的最短路权值之和。
### 解题报告
主要是 Floyd + 离线

看到要求点对最短路径和，自然想到了 Floyd。但是 Floyd 不支持删除。。。

我们可以反过来想：每次加入一个点，求出加入后每一对点最短路权值的和、

是不是十分简单了？

具体来说，我们倒着枚举删除的点，用这个点来松弛其他的点，然后统计目前存在的点的答案。

为什么是正确的呢？因为 Floyd 对松弛点的顺序没有要求。

直接按照反过来的顺序进行 Floyd 即可。
### 代码
```c++
// Luogu 交不上去只能去 Vjudge
#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define R register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(R int i = a;i <= b;++i)
#define RFOR(i,a,b) for(R int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

namespace fastIO{
    #define BUF_SIZE 100000
    #define OUT_SIZE 100000
    #define ll long long
    bool IOerror=0;
    inline char nc(){
        static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE;
        if (p1==pend){
            p1=buf; pend=buf+fread(buf,1,BUF_SIZE,stdin);
            if (pend==p1){IOerror=1;return -1;}
        }
        return *p1++;
    }
    inline bool blank(char ch){return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';}
    inline void read(int &x){
        bool sign=0; char ch=nc(); x=0;
        for (;blank(ch);ch=nc());
        if (IOerror)return;
        if (ch=='-')sign=1,ch=nc();
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
        if (sign)x=-x;
    }
    inline void read(ll &x){
        bool sign=0; char ch=nc(); x=0;
        for (;blank(ch);ch=nc());
        if (IOerror)return;
        if (ch=='-')sign=1,ch=nc();
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
        if (sign)x=-x;
    }
    #undef ll
    #undef OUT_SIZE
    #undef BUF_SIZE
};
using namespace fastIO;
// fread 板快读

const int MAXN = 500 + 5;
int f[MAXN][MAXN],N;
int del[MAXN];
bool tag[MAXN];
LL ans[MAXN];
// ans[i] 表示后 i 个点组成的图的答案，tag[i] 记录第 i 个点目前是否在图里，del[i] 是删除点的顺序

int main(){
    read(N);
    FOR(i,1,N)
        FOR(j,1,N)
        read(f[i][j]);
    FOR(i,1,N) read(del[i]);
    RFOR(p,N,1){
        int k = del[p];
        tag[k] = true;
        FOR(i,1,N){
            FOR(j,1,N){
                f[i][j] = std::min(f[i][j],f[i][k] + f[k][j]);
                if(tag[i] && tag[j]) ans[p] += f[i][j];
            }
        }
    }
    FOR(i,1,N) printf("%I64d ",ans[i]);
    return 0;
}
```

---

## 作者：Gerald_Chen (赞：6)

### 首先来厘清一下题意  
- 在第i步Greg将删除一个点。  
- 在 _**删除之前**_ 我们要求出当前图中所有最短路径的和。  

### 分析  
既然是求图中所有最短路的和，我们首先想到的是用Floyd算法，将图中所有的最短路都算出来并求和。  
不过，题目有一个要求：每一次要删除一个点，在删除之前求和。  
删除点看起来十分的困难~~我太弱了不知道怎么做~~，所以我们可以采用逆向思维：倒着来看要删除的点，就是依次要添加的点了。  
换一种说法：假设要删除的点已经全部删除了！这时，把最后一个要删除的点加进图（它之前的点已经全部被删除了），然后在按题目要求求和（对应于先求和再删除，这时先加点再求和）。以此类推。  
这样，就可以依次求出答案。
具体实现详见代码：
```cpp
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int N=501;
int del[N]/*要删除的点*/,dist[N][N],n;
long long ans[N];
bool avi[N]/*(available)当前该点是否在图中*/;
inline int read()
{
    int sum=0;
    char ch=getchar();
    while(!(ch>='0' && ch<='9'))
        ch=getchar();
    while(ch>='0' && ch<='9')
        sum=sum*10+ch-'0',ch=getchar();
    return sum;
}
int main()
{
    n=read();
    for(int i=1; i<=n; ++i)
        for(int j=1; j<=n; ++j)
            dist[i][j]=read();
    for(int i=1; i<=n; ++i)
        del[i]=read();
    for(int cur=n; cur; --cur) {
        int k=del[cur];
        avi[k]=true;//将当前点加入图
        //Floyd
        for(int i=1; i<=n; ++i)
            for(int j=1; j<=n; ++j)
                if(i!=j) {
                    dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
                    if(avi[i] && avi[j])//只有i与j都在图中最短路才有意义
                        ans[cur]+=dist[i][j];//当前删除过程所求的答案
                }
    }
    for(int i=1; i<=n; ++i)
        printf("%I64d ",ans[i]);//按照要求输出
    return 0;
}
```

#### **Thanks for watching.**

---

## 作者：醉里挑灯看剑 (赞：3)

这个题正向来解肯定会超时，所以我们逆向考虑，相当于每次都添一个点，所以从后往前枚举每一条删除的点，跑一遍floyed就行了。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define long long ll;
const int maxn = 501;
ll mp[maxn][maxn], ans[maxn]，ask[maxn];
bool vis[maxn];

int main()
{
    int n;
    while(scanf("%d", &n) != EOF)
    {
        memset(vis, false, sizeof(vis));
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                scanf("%I64d", &mp[i][j]);
        for(int i = 1; i <= n; i++)
            scanf("%d", &ask[i]);
        int cont = 0;
        for(int i = n; i >= 1; i--)
        {
            int now = ask[i];
            vis[now] = true;
            for(int j = 1; j <= n; j++)
                for(int k = 1; k <= n; k++)
                    mp[j][k] = min(mp[j][k], mp[j][now] + mp[now][k]);
            ll sum = 0;
            for(int j = 1; j <= n; j++)
                for(int k = 1; k <= n; k++)
                {
                    if(vis[j] == false || vis[k] == false) continue;
                    sum += mp[j][k];
                }
            ans[cont++] = sum;
        }
        for(int i = cont-1; i >= 0; i--)
            printf("%I64d%c", ans[i], i == 0 ? '\n': ' ');
    }
    return 0;
}

```

---

## 作者：Exber (赞：2)

## 题意
- #### 给你一个有 $n$ 个点的单向有权图和 $n$ 次操作。每次操作都是删除某一个点，和这个点连接的所有边也会被删除。
- #### 对于每一次操作，输出操作之前图中的所有最短路径的和。

## 做法
Floyd 算法。

可以把删点看作是加点。那么对于每次加点操作，任意两点间的最短路径都只可能通过加的这个点来更新。只要把每次加点后的最短路径和存在一个数组里，最后倒序输出就行了。

## AC 代码
```cpp
#include <iostream>
#include <cstdio>

using namespace std;

int n,dis[505][505],delque[505]; // 最短距离，删点顺序 
long long ans[505]; // 存答案的数组 
bool hasdel[505]; // 该点是否被删除 

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			scanf("%d",&dis[i][j]);
		}
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&delque[i]);
		hasdel[delque[i]]=true; // 删掉了 
	}
	for(int tail=n;tail>=1;tail--) // 倒序遍历，加点 
	{
		int k=delque[tail]; // 加的是哪一个点 
		hasdel[k]=false;    // 加回来了 
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				if(j==i)
				{
					continue;
				}
				if(dis[i][k]+dis[k][j]<dis[i][j])
				{
					dis[i][j]=dis[i][k]+dis[k][j]; // 松弛 
				}
				if(!hasdel[i]&&!hasdel[j]) // 两个点都没有被删掉时最短路径才有意义 
				{
					ans[tail]+=dis[i][j];
				}
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		printf("%I64d ",ans[i]); // 注意一下 %I64d 
	}
	printf("\n");
	return 0;
}
```


---

## 作者：zhanghzqwq (赞：2)

## 嗯，这是一道Floyd的模板题。

这道题可以加深对Floyd的理解，是个好题

这道题就是说建好边之后把点一个一个删除，然后算一下图上最短路的和。嗯？那倒着加点不就是Floyd的模板了吗？代码很细节，见下：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=505;//n的最大值
int n;
int adj[MAXN][MAXN];//用邻接矩阵建边
int x[MAXN];//删点的数组
bool vis[MAXN];//vis数组是看现在的点有没有在图中
long long ans[MAXN]; 
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%d",&adj[i][j]);//读入不解释
		}
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&x[i]);//把删除的点读入
	}
	for(int k=n;k>=1;k--){//一定是反着加点
		int flag=x[k];//flag就是这次加的点
		vis[flag]=1;//把这个点加入图中
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				adj[i][j]=min(adj[i][j],adj[i][flag]+adj[flag][j]);//Floyd模板，不解释
			}
		}
		long long sum=0;//算一下最短路之和
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(vis[i]&&vis[j]){//如果点都在图中
					sum+=adj[i][j];//那就加上
				}
			}
		}
		ans[k]=sum;//给ans数组
	}
	for(int i=1;i<=n;i++){//这是正着输出哦
		printf("%I64d ",ans[i]);
	}
	printf("\n");//换行是个信仰
	return 0;//完结撒花
}
```


---

## 作者：tzl_Dedicatus545 (赞：1)

**1.题意分析**

- 由于题目中出现了最短路之和，考虑使用 Floyd 解决。

- 又因为题目中要求不停地“删点”，很麻烦，可以考虑反方向加点。

- 我们可以从大到小循环枚举 $x_i$ ，对于每次枚举，对 $x_i$ 进行标记，在 Floyd 中进行特判即可。

**2.一些坑点**

- 本题要开 `long long` ， 否则会炸 `int` 。

- 在 Floyd 内不能这么写：

```cpp
if(!canUse[i] || !canUse[j])
	continue;

dis[i][j]=min(dis[i][j],dis[i][x[l]]+dis[x[l]][j]);
```

因为这样会在后续转移时出现问题，原因是没有考虑途中经过 $x_l$ 的情况，正确的写法是：

```cpp
dis[i][j]=min(dis[i][j],dis[i][x[l]]+dis[x[l]][j]);
```

而在后续进行特判。

**AC Code:**

```cpp
//By: Luogu@⚡炭治郎⚡(308854)
#include <bits/stdc++.h>

using namespace std;

long long dis[1000][1000];
long long x[1000];
bool canUse[1000];
long long Sum[1000];

int main()
{
	int n;

	cin>>n;

	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>dis[i][j];

	for(int i=1;i<=n;i++)
		cin>>x[i];

	for(int l=n;l>=1;l--)
	{
		canUse[x[l]]=1;

		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
			{
				dis[i][j]=min(dis[i][j],dis[i][x[l]]+dis[x[l]][j]);
			}

		long long sum=0;

		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(canUse[i] && canUse[j])
					sum+=dis[i][j];

		Sum[l]=sum;
	}

	for(int i=1;i<=n;i++)
		cout<<Sum[i]<<" ";
}

```


---

## 作者：MuYC (赞：1)

#### 前言(feihua)

做完挺久了，回来补一篇题解，主要是这个题目的想法思路还是很妙的。

#### 思路：

做法：$Floyd$即可。

不难发现算法能够允许通过的算法复杂度为O($n^3$)，同时又跟全源最短路（因为是要求$\sum_{u != v}{dis(u,v)}$）有关，那么$Floyd$当然是首选了。

每次删边后，跑$Floyd$，这样子的时间复杂度是O($n^4$)的，显然过不了这一题。

如何优化？

我们观察到$Floyd$算法的（伪）代码：
```cpp
	for(int i = 1 ; i <= n ; i ++)
		for(int j = i ; j <= n ; j ++)
        		for(int k = 1 ; k <= n ; k ++)
        			if(i != j)
   	   				dis[i][j] = min(dis[i][k] + dis[k][j],dis[i][j]);
```
emmm....这个有什么规律呢？

不妨设$n$表示的是现有的点数，每次我们会删除一个点，那么由这一个被删除的点更新来的$dis(i,j)$就会被修改，但是，我们貌似找不出这些$dis(i,j)$。

因为我们根本不知道哪一些$dis(i,j)$是被当前这个被删除的点更新来的。

##### 正难则反!

我们不难发现:当我们加入一个点的时候，前面所有点已经跑完$Floyd$了，实际上，我们只需要将这个点作为$Floyd$算法中第三层循环的$k$(也就是中转点)即可。

这样我们就知道是哪一些$dis(i,j)$被更新了，并且我们可以直接对它进行修改！

这样子$Floyd$算法中的第三层循环就可以去掉了，直接设置为当前加入的点即可!

所以时间复杂度就降为了O($n^3$)

这道题的核心就讲完了。细节也不多，放代码。

#### Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long 
int n;
int dis[505][505];
int d[505];
int ansline[505],book[505];
signed main(){
	cin >> n;
	for(int i = 1 ; i <= n ; i ++)
		for(int j = 1 ; j <= n ; j ++)
		cin >> dis[i][j];
	for(int i = 1 ; i <= n ; i ++)cin >> d[i];
	for(int v = n ; v >= 1 ; v --){
		int x = d[v];
		book[x] = 1;
		for (int i = 1 ; i <= n ; i ++)
			for (int j = 1 ; j <= n ; j ++)
			if(i != j){
            //因为把当前加入的点x作为中转点，所以我们去掉了一重循环
				dis[i][j] = min(dis[i][x] + dis[x][j],dis[i][j]);//x即是当前加入的点
				if(book[i] != 0 && book[j] != 0)ansline[v] += dis[i][j];
			}
	}
	for(int i = 1 ; i <= n ; i ++)cout << ansline[i] <<" ";
	return 0;
}
```

---

## 作者：清小秋ovo (赞：0)

# CF295B 题解

前排提示：此题要开 `long long`。

Floyd + 反向加点。

每次取出要删除的点当做 Floyd 的中转点。剩下的就直接敲板子就完事了。

```cpp
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

ll n,mp[510][510],d[510],ans[510];
ll sum;
bool on[510];

void floyd(){
    for(int t=n;t>=1;t--){
        int node = d[t]; // 要关的点
        on[node] = true;
        sum = 0;
        //floyd 板子
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(i != j){
                    mp[i][j] = min(mp[i][j], mp[i][node]+mp[node][j]);
                }
                if(on[i]&&on[j]){
                    sum += mp[i][j];
                }
            }
        }
        ans[t] = sum;
    }
}

int main()
{
    memset(mp,0x3f,sizeof(mp));
    cin >> n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>mp[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        cin >> d[i];
    }
    floyd();
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<" ";
    }
   return 0;
}
```


---

## 作者：happybob (赞：0)

题目传送门：[CF295B](https://www.luogu.com.cn/problem/CF295B)

这道题是练习 $floyd$ 的好题。

首先我们来思考一下，删除 $n$ 次点，每次删点求一次最短路，用 $floyd$ 做则是 $\text O(n^3 \times n)$ 也就是 $\text O(n^4)$ 的复杂度，会 $T$ 飞，于是我们考虑从后往前，每次删点当作加点即可。优化后复杂度 $O(n^3)$，可以过。

代码：

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define int long long
const int N = 505;
int n;
int dis[N][N], del[N], ans[N];
bool f[N];

void floyd()
{
	for (int p = n; p >= 1; p--) 
    {
		int k = del[p];
		f[k] = true;
		int sum = 0;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if (i != j)
				{
					dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
					if (f[i] && f[j])
					{
						sum += dis[i][j];
					}
				}
			}
		}
		ans[p] = sum;
	}
}

void print()
{
	for (int i = 1; i <= n; i++)
	{
		cout << ans[i] << " ";
	}
	cout << "\n";
}

void input()
{
	cin >> n;
	memset(dis, 0x3f, sizeof(dis));
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			int w;
			cin >> w;
			dis[i][j] = w;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		cin >> del[i];
	}
}

signed main()
{
	input();
	floyd();
	print();
	return 0;
}
```


---

