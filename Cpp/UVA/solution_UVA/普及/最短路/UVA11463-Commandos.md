# Commandos

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=26&page=show_problem&problem=2458

[PDF](https://uva.onlinejudge.org/external/114/p11463.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11463/6db49602a4d25da560ee412c34699e1614bef1f2.png)

## 样例 #1

### 输入

```
2
4
3
0 1
2 1
1 3
0 3
2
1
0 1
1 0```

### 输出

```
Case 1: 4
Case 2: 1```

# 题解

## 作者：wwwidk1234 (赞：7)

[洛谷题目传送门](https://www.luogu.com.cn/problem/UVA11463)

[UVA 题目传送门](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=26&page=show_problem&problem=2458)

[也许更好的阅读体验?](https://wwwidk1234.github.io/)

## 题目大意
一组敢死队队员从起点 $s$，经过道路摧毁敌人指挥部之后在终点 $d$ 集合。需要求出完成任务的最短时间。

## 题目分析
### 算法分析
可以使用**多源最短路 Floyd 算法**算出任意两点之间的最短路，将每个点分配一位敢死队队员进行爆破。最后枚举分割点 $i$ 求出起点至 $i$ 点至终点的最短距离。因为任务完成时间是以最后一个敢死队队员到达终点为准，所以我们要求出最后一位敢死队队员到达终点的时间作为本题答案。

### 样例分析
现有一张无向无权图：

![g](https://cdn.luogu.com.cn/upload/image_hosting/8hd6s5ou.png)

约定用红色箭头表示前往爆破地点的路径，蓝色箭头表示前往终点的路径。下面是前往 $1$ 号点进行爆破的敢死队队员的路径：

![g](https://cdn.luogu.com.cn/upload/image_hosting/now9i05d.png)

路径长度为 $2$。

下面是前往 $2$ 号点进行爆破的敢死队队员的路径：

![g](https://cdn.luogu.com.cn/upload/image_hosting/mu8ybg4i.png)

路径长度为 $4$。

在所有情况取一个最大值，即为本组数据答案。

### 解题步骤
考虑使用**邻接矩阵**储存图，首先将所有点数初始化为最大值。
```cpp
const int inf=114514191;
vector<vector<int>> g(N,vector<int>(N,inf));
```

读入边 $u,v$ 并将边存入邻接矩阵中。将点到自己的距离设置为 $0$。
```cpp
int n,m,s,d;
cin>>n>>m;
for(int i=0;i<m;i++)
{
    int u,v;
	cin>>u>>v;
	g[u][v]=g[v][u]=1;
}
for(int i=0;i<N;i++) g[i][i]=0;
```

接着开始跑 Floyd。
```cpp
void floyd(int n,vector<vector<int>>& f) //floyd多源最短路算法
{
	for(int k=0;k<n;k++) //枚举中间点
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
}
```

最后计算出最后一位敢死队队员回到基地的最短时间，并输出答案。
```cpp
int path=-inf;
for(int i=0;i<n;i++)
{
	path=max(dis[s][i]+dis[i][d],path);
}
cout<<"Case "<<test<<": "<<path<<endl;
```

## 完整代码
```cpp
#include<bits/stdc++.h>
//#define int long long
using namespace std;
const int N=110; //最大点数
const int inf=114514191;
void floyd(int n,vector<vector<int>>& f) //floyd多源最短路算法
{
	for(int k=0;k<n;k++) //枚举中间点
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
}
signed main()
{
	int T;
	cin>>T;
	for(int test=1;test<=T;test++)
	{
		vector<vector<int>> g(N,vector<int>(N,inf));  //十年OI一场空,不清数组见祖宗
		int n,m,s,d;
		cin>>n>>m;
		for(int i=0;i<m;i++)
		{
			int u,v;
			cin>>u>>v;
			g[u][v]=g[v][u]=1;
		}
		for(int i=0;i<N;i++) g[i][i]=0;
		cin>>s>>d;
		vector<vector<int>> dis=g;
		floyd(n,dis);
		int path=-inf;
		for(int i=0;i<n;i++)
		{
			path=max(dis[s][i]+dis[i][d],path);
			cout<<i<<":"<<dis[s][i]+dis[i][d]<<endl;
		}
		cout<<"Case "<<test<<": "<<path<<endl;
	}
	return 0;
}
```

## 注意事项
- 本题的数据为**无向图**，应**双向连边**。
- 本题有**多组数据**，每一组都必须**清空变量与数组**。

---

## 作者：shitingjia (赞：5)

[传送门](https://www.luogu.com.cn/problem/UVA11463)

### 题目大意

题意是有无数位敢死队员，从起点 $s$ 出发，在每一个建筑物放上一枚炸弹，最后在终点 $d$ 集合，问最少要多少时间。

### 题目思路

注意 $N \leq 100$，可以想到用 Floyd 算出任意两点之间的距离。由于有无数位敢死队员，所以我们就派一个队员去一个建筑物，也就是无向图上的一个节点。最后枚举一下每个点 $i$，计算起点 $s$ 到点 $i$ 再到终点 $d$ 的总距离，取最大值。

注意输出的格式，不要少空格。不要问我怎么知道的。

更多细节请见代码。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=305;
int cnt,t,n,m,s,e,g[N][N];
void floyd(){
	for(int k=0;k<n;k++){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				g[i][j]=g[j][i]=min(g[i][j],g[i][k]+g[k][j]);
			}
		}
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--){
		cnt++;
		cin>>n>>m;
		memset(g,0x3f,sizeof(g));//初始化
		for(int i=0;i<n;i++){
			g[i][i]=0;//初始化
		}
		for(int i=1;i<=m;i++){
			int u,v;
			cin>>u>>v;
			g[v][u]=g[u][v]=1;//有向图建双向边
		}
		cin>>s>>e;
		floyd();
		int ans=-1;
		for(int i=0;i<n;i++){
			ans=max(ans,g[s][i]+g[i][e]);//求最晚回来的队员
		}
		cout<<"Case "<<cnt<<": "<<ans<<endl;//注意格式
	}
	return 0; 
}
```

---

## 作者：CyberRiot (赞：2)

# UVA11463 Commandos

[翻译](https://www.luogu.com.cn/discuss/436596)

（感谢 [@东方澂 ](https://www.luogu.com.cn/user/161223)提供翻译）

题意简述：有一些敢死队员，从给定的一处出发，要破坏所有建筑物，并最终在给定的一处集合，敢死队员数量和每个敢死队员所携带的炸弹数目不限，求任务完成的最短时间。

大致思路：考虑使用 Floyd 算法，求出任意两点间的最短路径。读入起始地点和集合地点后循环更新以其余点为中间点的最短路径中的最长路。

下面是对思路的解释：题目要求每个建筑物都要破坏掉，且敢死队员人数不限。由此我们可以想到一个比较明显的方案：**对于每一座建筑物，都指派一位敢死队员去安置炸弹，安置完后就直接去集合地点**。每一位敢死队员都走他所能走的最短路径，即从起点去对应的建筑物，再去终点，这样就避免了多余的绕路。最后我们遍历所有队员完成任务所需的时间，即从起点到任意一点再到终点的路径长度，在其中取最大值，就得到了答案。$N\le100$ 的数据范围和**需要通过中间点来算路径长度**提示我们：可以考虑使用 Floyd 算法。

本题中 Floyd 算法的要点

- 对于存放最短路的数组 $dist$，在每一组测试开始时都需要进行初始化，对于不同的两个点 $i$ 和 $j$，$dist_{i,j}$ 初始化为极大值，对于相同的点 $i$，同一个点到它自身的距离为 $0$，所以 $dist_{i,i}$ 的值为 $0$。

+ 本题中的道路是双向的，更新两点间路径时要更新双向的路。

* 本题有多测数据，每一次多测 $dist$ 数组都要进行初始化。

其余的就很简单了，跑一遍 Floyd 就行。

AC 代码如下

```cpp
#include<bits/stdc++.h>
#define INF 1e9
using namespace std;
int dist[110][110];
int main(){
	int T;
	cin>>T;
	for(int q=1;q<=T;q++){
		int n,m;
		cin>>n>>m;
		for(int i=0;i<=n+1;i++){
			for(int j=0;j<=n+1;j++) dist[i][j]=INF;//初始化极大值
			dist[i][i]=0;//一个点到它自己的距离为零
		}
		for(int i=0;i<m;i++){
			int s,e;
			cin>>s>>e;
			dist[e][s]=dist[s][e]=1;//双向更新道路长度
		}
		for(int k=0;k<n;k++){
			for(int i=0;i<n;i++){
				for(int j=0;j<n;j++){
					if(dist[i][j]>dist[i][k]+dist[k][j]){
						dist[j][i]=dist[i][j]=dist[i][k]+dist[k][j];//这里也需要双向更新最短路
					}
				}
			}
		}//Floyd 核心
		int s,e,ans=-1;
		cin>>s>>e;
		for(int k=0;k<n;k++) if(dist[s][k]+dist[k][e]>ans) ans=dist[s][k]+dist[k][e];//更新经过任意一点的最短路中的最长路
		cout<<"Case "<<q<<": "<<ans<<endl;
	}
    return 0;
}
```


---

## 作者：limingyuan333 (赞：1)

# 题意解析
1. 首先在一个无向图中每一个点到每一个点的最短路径。

2. 然后求在中求一个点到一个中转点再到另一个点的最大值。

# 思路

发现数据范围中 $n \le 100$ 无向图算法，想到可以 floyd 算法。

简述一下，就是去枚举中转点，更新最小值。

代码如下:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,dp[110][110],n,r;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL),cout.tie(NULL);
	cin>>T;
	for(int t=1;t<=T;t++){
		cin>>n>>r;
		memset(dp,0x3f,sizeof(dp));
		for(int i=1;i<=r;i++){
			int x,y;cin>>x>>y;++x,++y;//序号都加一
      dp[x][y]=dp[y][x]=1;//双向边的大小初始为1
		}
		for(int i=1;i<=n;i++)	dp[i][i]=0;
		for(int k=1;k<=n;k++){
			for(int j=1;j<=n;j++){
				for(int i=1;i<=n;i++){
					dp[j][i]=min(dp[j][i],dp[j][k]+dp[k][i]);//枚举中转点
				}
			}
		}
		int mx=-1e9;
		
		int x,y;cin>>x>>y;++x,++y;
		for(int i=1;i<=n;i++) mx=max(mx,dp[x][i]+dp[i][y]);//取最大值
		cout<<"Case "<<t<<":"<<" "<<mx<<'\n';
	}
	return 0;
} 
```

---

