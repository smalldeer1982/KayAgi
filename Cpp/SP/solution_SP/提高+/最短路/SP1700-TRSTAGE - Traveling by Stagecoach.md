# TRSTAGE - Traveling by Stagecoach

## 题目描述

Once upon a time, there was a traveler.   
  
 He plans to travel using stagecoaches (horse wagons). His starting point and destination are fixed, but he cannot determine his route. Your job in this problem is to write a program which determines the route for him.   
  
 There are several cities in the country, and a road network connecting them. If there is a road between two cities, one can travel by a stagecoach from one of them to the other. A coach ticket is needed for a coach ride. The number of horses is specified in each of the tickets. Of course, with more horses, the coach runs faster.   
  
 At the starting point, the traveler has a number of coach tickets. By considering these tickets and the information on the road network, you should find the best possible route that takes him to the destination in the shortest time. The usage of coach tickets should be taken into account.   
  
 The following conditions are assumed.

- A coach ride takes the traveler from one city to another directly connected by a road. In other words, on each arrival to a city, he must change the coach.
- Only one ticket can be used for a coach ride between two cities directly connected by a road.
- Each ticket can be used only once.
- The time needed for a coach ride is the distance between two cities divided by the number of horses.
- The time needed for the coach change should be ignored.

## 样例 #1

### 输入

```
3 4 3 1 4
3 1 2
1 2 10
2 3 30
3 4 20
2 4 4 2 1
3 1
2 3 3
1 3 3
4 1 2
4 2 5
2 4 3 4 1
5 5
1 2 10
2 3 10
3 4 10
1 2 0 1 2
1
8 5 10 1 5
2 7 1 8 4 5 6 3
1 2 5
2 3 4
3 4 7
4 5 3
1 3 25
2 4 23
3 5 22
1 4 45
2 5 51
1 5 99
0 0 0 0 0```

### 输出

```
30.000
3.667
Impossible
Impossible
2.856

Since the number of digits after the decimal point is
not specified, the above result is not the only
solution. For example, the following result is also acceptable.

30.0
3.66667
Impossible
Impossible
2.85595```

# 题解

## 作者：Z1qqurat (赞：5)

珂爱的状压 dp。

### 思路分析

Part 1：为什么是状压 dp？

好好看看题目，完全符合 dp 的特征。

然后再看看数据范围可以发现票最多只有 $8$ 种，并且每一张票只有两种状态：用了与没用。

于是就大致可以确定是状压 dp 了。

Part 2：如何确定的状态？

有了大致确定的思路，我们就可以开始尝试定义状态了。

我们用 $0$ 表示没用过这张票，用 $1$ 表示用过。

不难想到可以这么定义：定义 $dp_{i,j,k}$ 表示当旅行家从城市 $i$ 出发去城市 $j$ 且票的状态为 $k$ 时最少要花多长时间。

然后可以发现起点只可能为 $a$，于是可以省去第一维。

Part 3：状态的转移？

那我们设 $i$ 为目前终点城市的编号，$j$ 为目前票的状态，$k$ 为上一步的终点城市的编号，$p$ 为从上一步到目前这一步花的票。

于是转移方程如下：

```cpp
dp[i][j]=min(dp[i][j],dp[k][j^(1<<p)]+G[i][q].dis*1.0/t[p+1]);
```

Part 4：具体的实现？

那我们不用什么最短路，我们直接用邻接表存图然后循环遍历。

```cpp
dp[a][0]=0;
for(ri j=1;j<(1<<n);j++){//枚举目前票的状态 
	for(ri p=0;p<n;p++){//枚举上一次花的票 
		if(((j>>p)&1)==0)continue;
		for(ri i=1;i<=m;i++){//枚举票目前的终点城市 
			for(ri q=0;q<G[i].size();q++){//枚举上一次到达的城市在i的邻居中的编号 
				int k=G[i][q].pos;//记录上一次城市编号
				dp[i][j]=min(dp[i][j],dp[k][j^(1<<p)]+G[i][q].dis*1.0/t[p+1]); 
			}
		}
	}	
}
```

### 代码

注意多组数据和浮点数即可，也许有注释。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
#define ll long long
#define ri register int
using namespace std;
const int MAXN=8;
int n,m,r,a,b,t[10];
double dp[40][1<<MAXN],ans=1e9;
struct node{
	int pos,dis;
};
vector <node> G[40];

void work() {
	ans=1e9;
	for(ri i=1;i<=m;i++){
		G[i].clear();
		for(ri j=0;j<(1<<n);j++)dp[i][j]=1e9;
	}
	for(ri i=1;i<=n;i++)cin>>t[i];
	for(ri i=1;i<=r;i++){
		int u,v,yyhak;
		cin>>u>>v>>yyhak;
		node cur={v,yyhak};
		G[u].push_back(cur);
		node curcur={u,yyhak};
		G[v].push_back(curcur);
	}

	dp[a][0]=0;
	for(ri j=1;j<(1<<n);j++){//枚举目前票的状态 
		for(ri p=0;p<n;p++){//枚举上一次花的票 
			if(((j>>p)&1)==0)continue;
			for(ri i=1;i<=m;i++){//枚举票目前的终点城市 
				for(ri q=0;q<G[i].size();q++){//枚举上一次到达的城市在i的邻居中的编号 
					int k=G[i][q].pos;//记录上一次城市编号
					dp[i][j]=min(dp[i][j],dp[k][j^(1<<p)]+G[i][q].dis*1.0/t[p+1]); 
				}
			}
		}
	}

	for(ri i=0;i<(1<<n);i++){
		ans=min(ans,dp[b][i]);
	}
	if(ans==1e9)cout<<"Impossible\n";
	else printf("%.3lf\n",ans);
}

int main() {
	//ios::sync_with_stdio(false);
	while(cin>>n>>m>>r>>a>>b){
		if(n==0&&m==0&&r==0&&a==0&&b==0)return 0;
		work();
	} 
	return 0;
} 
```

---

## 作者：__Deng_Rui_Song__ (赞：3)

~~可怕的状压dp~~

咳咳，言归正传
# problem
[传送门](/problem/SP1700)

题意已经很清楚了，我就不再叙述一遍了
# solution
Q1：为啥是状压 dp？

A1：看看数据范围：票和城市很小，并且都只有两种状态，符合状压 dp 性质，接下来 dp 四步走。

Q2：dp 状态是什么？

A2：状压城市有点不现实，但是可以状压票，不难想到设 $dp_{i,j}$ 表示票的状态为 $i$，当前城市为 $j$ 的最短时间。

Q3：答案是什么？

A3：由于最后票的状态不确定，所以当然是 $\min_{i=0}^{2^n-1}dp_{i,b}$。

Q4：dp 转移怎么写？

A4：枚举上一个城市 $k$ 和上一个用的票 $x$，城市 $k$ 和当前城市 $j$ 之间必须存在一条边（~~超巨的你：废话~~），票 $x$ 在状态 $i$ 里必须为 $1$（~~超巨的你：又一句废话~~），城市 $k$ 到城市 $j$ 的时间为 $\frac{g_{k,j}}{t_x}$，因此转移方程为：$dp_{i,j} = \min\{dp_{i,j},dp_{i\oplus2^x,last} + \frac{g_{j,k}}{a_x}\}$。

Q5：初始化？

A5：很明显，$dp_{0,a}=0$，其余设 $+\infty$，dp 四步走结束。

Q6：怎么实现？

A6：可以用邻接矩阵，邻接表，链式前向星存图，我用的是邻接表存图。
# code
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{int v,w;};
int n,m,p,a,b,t[8];
double dp[256][35];
vector<node> g[35];
void solve(){
    for (int i = 0; i < n; i++) cin >> t[i];
    while (p--){
        int x,y,w;
        cin >> x >> y >> w;
        g[x].push_back({y,w});
        g[y].push_back({x,w});
    }
    for (int i = 0; i < 1 << n; i++) for (int j = 1; j <= m; j++) dp[i][j] = 1e9;
    dp[0][a] = 0;//初始化
    for (int i = 1; i < 1 << n; i++)//票的状态
        for (int j = 1; j <= m; j++)//当前城市
            for (int k = 0; k < g[j].size(); k++)//上一个城市
                for (int x = 0; x < n; x++)//上一个用的票
                    if (i >> x & 1)//如果用了这个票
                        dp[i][j] = min(dp[i][j],dp[i ^ 1 << x][g[j][k].v] + g[j][k].w * 1.0 / t[x]);//转移
    double ans = 1e9;
    for (int i = 0; i < (1 << n); i++) ans = min(ans,dp[i][b]);//答案
    (ans == 1e9 ? cout << "Impossible\n" : cout << fixed << setprecision(3) << ans << '\n');
    for (int i = 1; i <= m; i++) g[i].clear();//多测不清空，爆零两行泪
}
int main(){
    while (cin >> n >> m >> p >> a >> b){
        if (!n) return 0;
        solve();
    }
    return 0;
}
```

---

## 作者：xuchuhan (赞：2)

显然每张票只有使用过或者没使用过两种状态。又考虑到票的总数小于等于 $16$，可以试着状压每张票是否使用过。若已使用过车票 $i$，则状态第 $i$ 位的值为 $1$，否则值为 $0$。

设 $dp_{i,j}$ 表示使用票的状态为 $i$，此时到了点 $j$ 所用最短时间。如何设计代码？

### Part1 初始状态

$dp_{0,a}=0$，其余状态的值均为 $-\infty$。因为初始时在起点 $a$，所有车票均未使用。

### Part2 转移

转移时我们需要知道当前状态的上一个状态。

- 设当前车票使用情况为 $i$，到了点 $x$，则上一个状态 $lst$ 的第一维必然是将 $i$ 的某一二进制位 $j$ 的值从 $1$ 改为 $0$，表示上一个状态到这一个状态用了第 $j$ 张车票；第二维必然是 $x$ 的某一邻接点编号 $y$，表示上一个状态到了点 $y$，从点 $y$ 走到了这一个状态的点 $x$。
  
- 从上一个状态 $dp_{lst,y}$ 到这一个状态 $dp_{i,x}$ 的花费为 $\dfrac{w_{x,y}}{t_j}$，$w_{x,y}$ 为 $x,y$ 间的道路长度，$t_j$ 表示走这条路用了第 $j$ 张车票，与上一段的 $j$ 同样含义。$dp_{i,j}$ 的答案则为最小的 $dp_{lst,y}+\dfrac{w_{x,y}}{t_j}$。

### Part3 答案

答案是 $\min_{i=0}^{2^n-1} dp_{i,b}$。第一维表示任何状态都理论可行，第二位表示到了终点 $b$。

结合代码理解一下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=10,M=(1<<8)+5,MM=35;
int n,m,p,a,b;
double ans;
int t[N];
double w[M][M],dp[M][MM];
bool f[M][M];
void Work(){
	for(int i=0;i<n;i++)
		cin>>t[i];
	memset(f,0,sizeof(f));
	for(int i=1;i<=m;i++)
		for(int j=1;j<=m;j++)
			w[i][j]=0;
	for(int i=1;i<=p;i++){
		int x,y;
		double z;
		cin>>x>>y>>z;
		f[x][y]=f[y][x]=1;
		w[x][y]=w[y][x]=z;//邻接表 
	}
	for(int i=0;i<(1<<n);i++)
		for(int j=1;j<=m;j++)
			dp[i][j]=1e18;
	dp[0][a]=0;
	for(int i=0;i<(1<<n);i++){//状态i
		for(int j=0;j<n;j++){//从上一个状态到这个状态用的车票j
			if((i&(1<<j))==0)//i的第j位为0,表示没用过车票j,矛盾 
				continue;
			for(int x=1;x<=m;x++){
				for(int y=1;y<=m;y++){
					if(!f[x][y]) 
						continue;//y不是x的邻接点
					dp[i][x]=min(dp[i][x],dp[i^(1<<j)][y]+(w[x][y]*1.0/t[j]));
					//i^(1<<j)就是将i的第j位变为0,也就是题解中的lst,因为已知i的第j位为1,又有(1<<j)的第j位为1,其余位数为0,1^1=0,所以i^(1<<j)的作用是将i的第j位变为0,其余位数不变 
				}
			}
		}
	}
	ans=1e18;
	for(int i=0;i<(1<<n);i++)
		ans=min(ans,dp[i][b]);
	if(ans>1e17)	
		cout<<"Impossible\n";
	else
		printf("%.6lf\n",ans);//答案 
}
signed main(){
	while(cin>>n>>m>>p>>a>>b){
		if(!n&&!m&&!p&&!a&&!b)//结束条件 
			return 0;
		Work();
	}
	return 0;
}
```

---

## 作者：kevin1616 (赞：2)

### 审题
给定一个无向图，旅行家有 $n$ 张车票，每张车票都写有马的匹数。他要从 $a$ 点到 $b$ 点，其中经过每一条边所花费的时间是这条边的长度除以车票上写的马匹的数量。求最短时间。
***
### 方法
【最短路】看到无向图的点到点问题，很容易想到最短路。但是这道题的车票的使用顺序是不一样的，所以就会出现先要枚举使用的顺序，才可以开始求最短路。此时就会发现时间复杂度很大，故该做法不可以通过本题。

【状态压缩 DP】当我们发现最短路无法通过本题时，发现本题的 $n$ 非常小，就可以枚举当前车票的使用情况。因为车票是越用越少的，就可以把他当成子问题来枚举（意思就是把这一维的循环放在最外面），同时还需枚举当前所到的点。时间复杂度 $O(n\times m^2\times2^{n})$，是可以通过本题的。
***
### 思路
`dp[i][j]` 表示车票使用情况为二进制下的 $i$ 时，旅行家到达 $j$ 点的最短时间。

此时发现答案就在到达 $b$ 点的所有车票使用情况上，即：

```cpp
for(int i = 0;i < (1 << n);i++) ans = min(ans,dp[i][b]);
```

然后将其对于上一次的情况进行转移，对于每个被用过的车票 $k$ 和被走过的点 $l$，转移方程如下：

```cpp
dp[i][j] = min(dp[i][j],dp[i ^ (1 << (k - 1))][l] + w[l][j] * 1.0 / t[k]);
```

也就是从 $l$ 走到 $j$ 后，车票状态为 $i$，则由上一次的状态加上边的长度除以使用的车票 $k$ 中马的匹数即可完成转移。因为在起点的时候一张车票都没有使用，所以最短时间为零。即：

```cpp
dp[0][a] = 0;
```

最后，发现本题有多个测试点，需要清空数组和答案，DP 数组需要赋极大值，因为答案和 DP 数组都是小数，需要开 `double`，极大值就不可以用 `memset` 来得到，需要通过循环来给每个位置赋上极大值。而边权数组的初始值也是极大值。
***
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,p,a,b;
int t[100005];
long long w[35][35]; //边的权值
double dp[(1 << 8)][35]; //dp[i][j]代表车票使用情况为二进制下的i时，旅行家到达j点的最短时间。
double ans = 1e18;
int main(){
    while(cin >> n >> m >> p >> a >> b){
        if(n == 0 && m == 0 && p == 0 && a == 0 && b == 0) return 0; //终止条件
        ans = 1e18;
        for(int i = 1;i <= n;i++) cin >> t[i];
        memset(w,0x3f,sizeof(w)); //边权数组赋极大值
        for(int i = 1;i <= p;i++){
            int x,y,z;
            cin >> x >> y >> z;
            w[x][y] = w[y][x] = z; //双向边
        }
        for(int i = 0;i < (1 << n);i++){ //DP数组赋极大值
            for(int j = 1;j <= m;j++){
                if(i == 0 && j == a) dp[i][j] = 0;
                else dp[i][j] = 1e18;
            }
        }
        for(int i = 0;i < (1 << n);i++){ //车票的使用状态
            for(int j = 1;j <= m;j++){ //当前的点
                for(int k = 1;k <= n;k++){ //枚举使用过的车票来做上一次使用的车票
                    if((i >> (k - 1)) & 1){
                        for(int l = 1;l <= m;l++){ //上一个的点
                            dp[i][j] = min(dp[i][j],dp[i ^ (1 << (k - 1))][l] + w[l][j] * 1.0 / t[k]); //转移方程
                        }
                    }
                }
            }
        }
        for(int i = 0;i < (1 << n);i++) ans = min(ans,dp[i][b]); //答案
        if(ans < 1e9) printf("%.3lf\n",ans); //输出
        else cout << "Impossible\n";
    }
    return 0;
}
```
不抄题解，从我做起！

---

## 作者：Stone_Xz (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/SP1700)

## 题意

> 给定一张 $m$ 个点 $p$ 条边的无向图，每条边有距离 $l_i$。再给定 $n$ 张车票，每张车票有马的匹数 $t_i$，用车票可以在边上走，用车票 $i$ 通过边 $j$ 的时间为 $\frac{l_j}{t_i}$。求从 $a$ 到 $b$ 的最短时间。 

## 分析：状压 DP

 - 首先，由于使用每张车票的通过时间并不固定，所以不能直接跑最短路。
 
 - 我们发现 $n \le 8$，范围比较小，而车票只有选或不选两种情况，一眼状压 DP。
 
1. 状态：$dp[i][j]$ 表示车票的使用情况为 $i$，到达点 $j$ 的最短时间。

2. 答案：定义完状态，我们立马想到答案，枚举车票的使用情况 $i$，答案为 $\min(dp[i][b])$。

3. 状态转移：

除了枚举车票使用状态和当前的点，转移还要用到上一个点，并且要知道上一个点到当前点的距离，还要枚举当前使用的车票。

```
枚举车票使用情况
	枚举当前用掉的车票
		if(用了当前的车票) // 即【当前用掉的车票】合法 
			枚举当前到达的车站 
				枚举上一个车站
					更新到达当前车站的最小时间 
```

4. 初始状态：$dp[0][a] = 0$，其余赋为极大值。

## 注意

本题的边权、答案都是 `double` 类型，有很多需要注意 `double` 的地方，要认真审题和检查。需要定义为 `double` 的地方都已经在代码中标明。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int M = 31;
int n, m, p, a, b, t[M];
double dp[1 << 8][M], ans; // // 注意为 double 类型 

struct Edge{
	int to;
	double w; // 注意为 double 类型 
};
vector<Edge> nbr[M];

void init()
{
	// 注意 dp 是 double 类型，不能 memset 1e9
	for(int i = 0; i < (1 << n); i++)
		for(int j = 1; j <= m; j++)
			dp[i][j] = 1e9;
	
	for(int i = 1; i <= m; i++)
		nbr[i].clear();
	
	ans = 1e9;
	return ;
}

void solve()
{
	init(); // 记得初始化 
	for(int i = 1; i <= n; i++)
		cin >> t[i];
	for(int i = 1; i <= p; i++)
	{
		int x, y;
		double w; // 注意 w 为 double 类型 
		cin >> x >> y >> w;
		nbr[x].push_back((Edge){y, w});
		nbr[y].push_back((Edge){x, w});
	}
	dp[0][a] = 0;
	for(int i = 0; i < (1 << n); i++) // 车票使用情况
	{
		for(int k = 0; k < n; k++) 
		// 当前用掉的车票，注意为了位运算方便，从 0 到 n - 1。 
		{
			if(!((i >> k) & 1))
				continue;
			for(int j = 1; j <= m; j++) // 当前到达的车站 
			{
				for(auto tmp : nbr[j]) // 当前车站从哪里过来
				{
					int last = tmp.to;
					double dis = tmp.w; // 注意为 double 类型 
					
					// 尝试用 last 到 j 这条路的时间更新到达 j 的最短时间 
					dp[i][j] = min(dp[i][j], dp[i ^ (1 << k)][last] + dis * 1.0 / t[k + 1/*注意+1*/]);
				}
			}
		}
	}
	for(int i = 0; i < (1 << n); i++) // 最终车票使用情况
		ans = min(ans, dp[i][b]);
		
	if(ans == 1e9)
		cout << "Impossible";
	else
		cout << fixed << setprecision(3) << ans;
	cout << "\n";
	return ;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	while(cin >> n >> m >> p >> a >> b)
	{
		if(!n && !m && !p && !a && !b)
			break;
		solve();
	}
	return 0;
}
```

---

## 作者：Stars_visitor_tyw (赞：1)

## 题解：SP1700 TRSTAGE - Traveling by Stagecoach
### 分析
很容易知道，车票的使用数量只会越来越多，我们考虑按车票来划分子问题写状压。

定义状态为 $dp_{i,j}$ 表示车票的使用情况为二进制下的 $i$，且当前到点 $j$ 的最小时间。

状态转移：枚举车票使用情况，枚举车票，枚举每个城市。当状态有效时也就是枚举的车票在二进制状态为 $i$ 时对应位为 $1$ 时，转移方程为 `dp[i][j]=min(dp[i][j],dp[i^(1<<x)][nxt]+w[nxt][j]*1.0/t[x]);`。

由于车票可以不全用完，所以枚举车票的使用情况为二进制下的 $i$，答案在 $dp_{i,b}$ 中取最小值。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, m, p, a, b, t[45];
double dp[1024][40], ans=1e9;
vector<int> nbr[45];
double w[45][45];
void work()
{
	for(int i=0;i<(1<<n);i++)
	{
		for(int j=1;j<=m;j++)
		{
			dp[i][j]=1e9;
		}
	}
	dp[0][a]=0;
	for(int i=1;i<=m;i++)
	{
		nbr[i].clear();
	}
	for(int i=0;i<n;i++)
	{
		cin>>t[i];
	}
	for(int i=1;i<=p;i++)
	{
		int x, y;
		double z;
		cin>>x>>y>>z;
		w[x][y]=w[y][x]=z;
		nbr[x].push_back(y);
		nbr[y].push_back(x);
	}
	for(int i=0;i<(1<<n);i++)
	{
		for(int x=0;x<n;x++)
		{
			for(int j=1;j<=m;j++)
			{
				for(int nxt:nbr[j])
				{
					if((i>>x)&1)
					{
						dp[i][j]=min(dp[i][j],dp[i^(1<<x)][nxt]+w[nxt][j]*1.0/t[x]);
					}
				}
			}
		}
	}
	ans=1e9;
	for(int i=0;i<(1<<n);i++)
	{
		ans=min(ans,dp[i][b]);
	}
	if(ans==1e9)
	{
		cout<<"Impossible\n";
	}
	else
	{
		cout<<fixed<<setprecision(3)<<ans<<"\n";
	}
}
signed main()
{
	while(cin>>n>>m>>p>>a>>b)
	{
		if(n==m&&m==p&&p==a&&a==b&&b==0)
		{
			return 0;
		}
		work();
	}
}
```

---

## 作者：wujingfey (赞：1)


~~蒟蒻的第一篇题解，有不完善的地方敬请谅解 awa~~
# 题意理解
题目链接[TRSTAGE - Traveling by Stagecoach](https://www.luogu.com.cn/problem/SP1700)

给定 $n$ 张车票和一个 $m$ 个点，$p$ 条边的无向图，设边权为 $l_i$，通过每条边时需要消耗一张车票 $t_i$，花费是 $\dfrac{l_i}{t_i}$，求从 $a$ 到 $b$ 的最小花费。$1\le n \le 8,2\le m \le 30,1\le a,b \le m (a \ne b),1 \le t_i \le 10,1 \le l_i \le 100$。

# 思路分析
## 普通 DP
读完题，我们会有一种 DP 的冲动，即用数组 $dp_{x,S}$ 表示从起点 $a$ 到点 $x$ 时，剩余票数状态为 $S$ 的最小花费。其中我们用一个长度为 $n$ 的 $01$ 字符串表示 $S$，$S_i$ 为 $1$ 表示这张票还没用过，反之亦然。从点 $u$ 转移到另点 $v$ 使用第 $j$ 张票，相当于将 $S_j$ 从 $1$ 改为 $0$，然后花费增加 $\dfrac{l_{u,v}}{t_j}$。

于是我们可以得到粗略的状态转移方程式：
$$dp_{v,S'}\leftarrow \min(dp_{v,S'},dp_{u,S}+\dfrac{l_{u,v}}{t_j})$$ 

## 状态压缩 DP
在普通 DP 中我们可以发现一个问题：$S$ 是一个长度最大为 $8$ 的 $01$ 字符串，这会导致 MLE。但事实上，我们总共的状态数远不到 $10^8$，这是因为我们用十进制的空间表示了一个只需要二进制就能表示的状态，这是极其浪费的。所以我们考虑状态压缩 DP **（在我的理解中，其实状态压缩 DP 的本质是利用类似哈希的方法，把极大的状态映射成较小的状态，以此达到减少空间复杂度的目的）。**
### 状态压缩 DP 详解
以本题为例，将 $n$ 张车票标上 $0\sim n-1$ 的编号，利用位进制的方式将二进制状态 $S$ 压缩成十进制状态 $S'$。即：$S'=\sum_{i=0}^{n-1}s_i*2^i$。例如 $n=4,S=0110$ 的状态，经过压缩后就是 $6$，成功将四位数压缩到一位数。

**于是我们可以得到如下的基本性质：**
- 空集：$S=0$
- 全集：$S=2^n -1$
- 只有第 $i$ 个元素的集合：$(1<<n)-1$
- 判断第 $i$ 个元素是否属于集合 $S$：$if(S>>i\&1)$，即 $S_i$ 是否为 $1$，$i\in[0,n-1]$
- 向集合 $S$ 中加入第 $i$ 个元素：$S\mid (1<<i),i\in[0,n-1]$
- 从集合 $S$ 中删除第 $i$ 个元素：$S-=(1<<i)$
- 集合 $S$ 和 $T$ 的并集：$S\mid T$
- 集合 $S$ 和 $T$ 的交集：$S\&T$

倘若我们想要将集合 $S$ 的所有状态枚举出来，则可以：
```cpp
for(int i=0;i<(1<<n);i++){
   //对子集的处理
}
```
## 将状态压缩 DP 融入本题
假设现在的状态是：到达城市 $u$，剩下车票的集合压缩后为 $S$，从这个状态出发，使用一张车票 $j\in S$ 到达城市 $v$，于是得到了新状态，到达城市 $v$，剩余状态是 $S-(2^j)$。最开始只知道从 $a$ 出发，剩余状态 $S=2^n-1$ 时的最小花费为 $0$（即全集）。我们**票数从多到少的顺序进行松弛操作**，对于每个剩余票数状态 $i$，枚举所有起点 $u$，再枚举票 $j$，若 $j\in i$ 则枚举终点 $v$，于是我们可以**得到还剩票数集合为 $i$ 时,各个点到起点 $a$ 的最短距离。随着 $i$ 从全集到空集，剩余票数越来越少，我们逐渐将整张图松弛完毕，最后得到答案。**
状态转移方程式如下（数组变量含义详见代码）：
$$dp_{v,i-(2^j)}\leftarrow \min(dp_{v,i-(2^j)},dp_{u,i}+\dfrac{mp_{u,v}}{t_j})$$
代码具现化为：
```cpp
for(int i=(1<<n)-1;i>=0;i--){//从多向少枚举剩余车票集合 
	for(int u=1;u<=m;u++){//枚举每一个出发点 
		for(int j=0;j<n;j++){//枚举每张票 
			if(i&(1<<j)){//剩余车票中有j号车票 
				for(int v=1;v<=m;v++){//枚举终点 
					if(mp[u][v]){//相互可达 
						dp[v][i-(1<<j)]=min(dp[v][i-(1<<j)],dp[u][i]+(double)mp[u][v]/t[j]);//更新答案
					}
				}
			}
		}
	}
}
```

可能比较费解的一点是：为什么要从大到小枚举 $i$ 进行松弛。**我的理解是：因为我消耗票数是从少到多，到达其他城市是从近到远的，我们从高到低枚举 $i$ 可以保证剩余票数单调不增，从而达到松弛操作是从近到远的目的，也就避免了我在松弛的时候，枚举到的 $u$ 还没被更新答案，导致讨论漏情况。**

# 最后附上代码
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int INF=1<<29;
int n,m,p,a,b;
int t[10];
int mp[31][31];//领接矩阵 
double dp[31][1<<9];
void solve(){
	for(int i=(1<<n)-1;i>=0;i--){//从多向少枚举剩余车票集合 
		for(int u=1;u<=m;u++){//枚举每一个出发点 
			for(int j=0;j<n;j++){//枚举每张票 
				if(i&(1<<j)){//剩余车票中有j号车票 
					for(int v=1;v<=m;v++){//枚举终点 
						if(mp[u][v]){//相互可达 
							dp[v][i&~(1<<j)]=min(dp[v][i&~(1<<j)],dp[u][i]+(double)mp[u][v]/t[j]);//更新答案
						}
					}
				}
			}
		}
	}
} 
signed main(){
	while(scanf("%d%d%d%d%d",&n,&m,&p,&a,&b)!=EOF){
		if(!n && !m) break;
		memset(mp,0,sizeof(mp));
		for(int i=0;i<n;i++) scanf("%d",&t[i]);//车票编号从0~n-1 
		for(int i=1;i<=p;i++){//邻接矩阵读边
			int x,y,z; 
			scanf("%d%d%d",&x,&y,&z);
			mp[x][y]=mp[y][x]=z;
		}
		for(int i=0;i<=m;i++){
			fill(dp[i],dp[i]+(1<<9)-1,INF);//用memset会炸掉 
		}
		dp[a][(1<<n)-1]=0;//起点到自己花费显然为0，不需要花费车票 
		solve();
		double ans=INF;
		for(int i=0;i<(1<<n);i++){
			ans=min(ans,dp[b][i]);//枚举剩余车票的每一种情况，取最小值 
		}
		if(ans==INF) printf("Impossible\n");
		else printf("%.5f\n",ans);
	}
	return 0;
}
```

## 其他
~~洛谷UKE死活提交不上 awa，在 POJ 上终于 AC 了，求通过 Orz.~~

---

## 作者：Durancer (赞：1)

### 前置知识

- 状压

- $\text{dead algorithm}$

### 思路

从 $a$ 出发跑最短路，用类似于 $\text{spfa}$ 的思想求解。

设 $f_{i,j}$ 表示走到了第 $i$ 个城市，用了的票的状态为 $j$ 的最小距离。

每一次都更新一遍所有状态，如果有一个地方可以松弛，就把路径终点加进去，最后枚举取最小值。

### 坑点

样例确实很良心，当 $l_i/t_j$ 是一个小数的时候，可能会出现精度大大损失的情况，就可能会导致松弛不断进行下去，因此，如果距离是浮点数的时候，判断的时候把误差加上去防止死循环。

### 代码实现

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int N=39;
const int M=(1<<9);
const double lim=1e-9;
struct node{
	int last;
	int to;
	double dis;
}e[N*N];
int head[N],cnt;
int ticket,n,m,a,b;
double f[N][M];//表示到了 i 城市，状态为 j 的最小距离
double t[N],ans;
int U;
bool vis[N]; 
int read()
{
	int f=1,x=0;
	char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=(x<<1)+(x<<3)+(s^'0');s=getchar();}
	return f*x;	
} 
void add(int from,int to,double dis)
{
	e[++cnt].last=head[from];
	e[cnt].to=to;
	e[cnt].dis=dis;
	head[from]=cnt;
}
void clear()
{
	ans=0x3f3f3f3f; cnt=0;
	memset(f,127,sizeof(f));
	memset(vis,false,sizeof(vis));
	memset(head,0,sizeof(head));
}
void dijstra()
{
	queue<int> q;
	f[a][0]=0;
	q.push(a); vis[a]=true;
	while(!q.empty())
	{
		int u=q.front();
		q.pop(); vis[u]=false;
		for(int i=head[u];i;i=e[i].last)
		{
			int v=e[i].to;
			double l=e[i].dis;
			for(int s=0;s<=U;s++)//枚举用过票的状态
				for(int j=1;j<=ticket;j++)//枚举票
				{
					int T=1<<(j-1);
					double w=l/t[j];//涨肚 
					if(s & T) continue;
					if(f[v][s|T] > f[u][s] + w + lim)
					{
						//cout<<"old -> f[v][s|T] = "<<f[v][s|T]<<" , ";
						f[v][s|T] = f[u][s] + w;
						//cout<<"new -> f[v][s|T] = "<<f[v][s|T]<<endl;
						if(!vis[v])
						{
							q.push(v);
							vis[v]=true;
						} 
					}
				}
		} 
	}
}
int main()
{
	while(1)
	{
		clear();
		ticket=read(); n=read(); U=(1<<ticket)-1;
		m=read(); a=read(); b=read();
		
		//cout<<ans<<endl;
		
		if(!ticket and !n and !m and !a and !b)
			return 0;
		
		for(int i=1;i<=ticket;i++)
			scanf("%lf",&t[i]);
		for(int i=1;i<=m;i++)
		{
			int u=read();
			int v=read();
			double w;
			scanf("%lf",&w);
			add(u,v,w); add(v,u,w);
		}
		dijstra(); 
		for(int i=0;i<=U;i++)
			ans=min(ans,f[b][i]);
		if(ans==0x3f3f3f3f)
			printf("Impossible\n");
		else printf("%.5lf\n",ans);
	}
	return 0;
}
```

---

## 作者：GrayCatH (赞：1)

# 一·状压+最短路
把状态作为顶点，把状态的转移看成边来建图            

对于现在在**城市v,此时还剩下的车票的集合S** 这样的状态，从这个状态出发，使用一张车票i属于S移动到相邻的城市u，就相当于转移到了“**在城市u，此时还剩下车票的集合为S\{i}**”这个状态。   

那么，把这个转移看成一条边，那么边上的花费是**（v-u间道路的长度）/ti**

集合S使用状态压缩的方法表示就可以啦，然后就可以dij求解了。  

2018.11.1补充：       
由于机房巨佬 @YMRJRSJZ 提出了问题：以城市为状态建图跑dij如何保证用的票是否重复或是否用了最合适的？   
思路：    
假如你现在在一个城市（一个状态），你要去某一个城市，但对于到你接下来要去的城市不止会产生一个状态，因为状态转移是多样的。所以这里的建图过程是将一个状态到它可以到达的每一个状态处理出来，状态作为节点，转移时候车票的使用记录为边权，这样就可以保证在建完的图上跑dij是正确的了。
# 二·DAG+dp
由于剩余的车票的集合S随着移动元素个数不断减小，因此这个图实际上是一个DAG，于是就可以巧妙地ac啦。

呔码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int INF=0x3f3f3f3f;
int n,m,a,b,p;
int t[10];
int d[35][35];
double dp[1<<10][35] ;
void solve(){
    for(int i=0;i<1<<n;i++){
        fill(dp[i],dp[i]+m,INF);
        
    }
    dp[(1<<n)-1][a-1]=0;
    double res=INF;
    for(int S=(1<<n)-1;S>=0;S--){
        //cout<<dp[S][b]<<"$"<<S<<" "<<b<<endl;
        res=min(res,dp[S][b-1]);
    //	printf("$%.3lf\n",res);
        for(int v=0;v<m;v++)
        for(int i=0;i<n;i++) 
        if((S>>i)&1){
            for(int u=0;u<m;u++){
                if(d[v][u]>=0){//cout<<"#"<<endl;
                    dp[S & ~ (1 << i)][u]=min(dp[S & ~( 1 << i )][u],dp[S][v]+(double)d[v][u]/t[i]);
                    //cout<<"#"<<d[S][b-]<<endl;
                }
            }
        }
        
    }
    if(res==INF)printf("Impossible\n");
    else printf("%.3lf\n",res);
    
}
int main(){
    while(true){
    scanf("%d%d%d%d%d",&n,&m,&p,&a,&b);
    if(n==0&&m==0&&p==0&&a==0&&b==0)return 0;
    memset(d,-1,sizeof(d));
    for(int i=0;i<n;i++)
    scanf("%d",&t[i]);
    for(int i=1;i<=p;i++){
        int x,y,z;
    scanf("%d%d%d",&x,&y,&z);
    d[x-1][y-1]=z;
    d[y-1][x-1]=z;
}
solve();}
return 0;}
```

---

## 作者：foryou_ (赞：0)

首先我们发现这题车票数很少。

于是考虑状压 dp，按车票划分状态。

显然地，我们令 $dp_{i,j}$ 表示车票使用状态为二进制下的 $i$，且行走路径为 $a \to j$ 时所需的最小时间。

易得初始状态：$dp_{a,0}=0$，答案：$\min\{dp_{i,b}\}$。

转移时，我们枚举当前点的邻接点 $k$，以及当前使用的车票 $x$，得到转移方程：

$$
dp_{i,j}=\min(dp_{i,j},dp_{i \operatorname{xor} 2^j,k}+\frac{w}{t_x})
$$

（$w$ 表示当前点到 $k$ 的边的边权）

直接做即可。[code](https://www.luogu.com.cn/paste/wmdos65b)。

---

## 作者：Weekoder (赞：0)

### 思路

这是一篇状压 DP 题解。

第一眼看上去像最短路，但是探究问题本质，我们可以发现这是一个边权不确定的最短路问题。观察到数据范围很小，车票可以状压而且只有用了和没用两种状态，考虑状压 DP。

可是这是一个无向图，该如何划分子问题？可以发现车票总是越用越少的，而且车票的数量非常少，可以以车票划分子问题。定义状态 $dp_{i,j}$ 表示车票的使用情况为二进制下的 $i$，且当前到达点 $j$ 的最少时间。我们有初始状态 $dp_{0,a}=0$，其余极大值。

如何状态转移？状压 DP 的状态转移比较规整好想，只要弄清循环顺序跟着思路转移即可。先划分子问题，从 $0$ 到 $2^n-1$ 枚举车票状态。接着，再枚举使用的车票编号 $x$。这时候，可以提前在这里加入合法状态判断：`((i >> x) & 1) == 1`，既然使用了车票 $x$，那么在状态中第 $x$ 位也必须为 $1$，这个状态才是合法的。第三层循环枚举当前位置 $j$，从 $1$ 到 $m$。有了 $j$，我们就要收集状态：枚举 $j$ 的邻接点 $k$ 并转移。状态转移方程是什么？与哈密尔顿路径的转移很像，在使用车票 $x$ 之前，状态中的第 $x$ 位是 $0$，取反。从 $k$ 到 $j$ 的时间为路径长度除以马的数量，即 $dis_{k,j}\div t_x$。完整的状态转移方程：

$$
dp_{i,j}=\min(dp_{i,j},dp_{i\text{ xor }2^x,k}+dis_{k,j}\div t_x)
$$

答案是什么？由于车票有可能不会全部使用，我们可以枚举车票使用的状态 $i$，答案为 $\min(dp_{i,b})$。若答案仍为极大值，则无解。注意，有多组数据。

考虑一个问题：有没有可能，重复经过某个点，而导致答案变大？是否需要记录点的经过情况，避免重复？显然不可行，因为一共有 $30$ 个点，$2^{30}$ 的空间一定会 MLE。那这样能保证正确性吗？答案是肯定的，因为我们在转移时会取较小值，这个状态将不会被转移。

完整代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

const int S = 8, N = 35;

struct Edge {
	int to;
	double w;
};

int n, m, p, a, b, t[N];

double dp[1 << S][N], ans;

vector<Edge> nbr[N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	while (cin >> n >> m >> p >> a >> b) {
		if (!n && !m && !p && !a && !b)
			break;
		for (int i = 0; i < n; i++)
			cin >> t[i];
		for (int i = 0; i < (1 << n); i++)
			for (int j = 1; j <= m; j++)
				dp[i][j] = 1e9;
		for (int i = 1; i <= m; i++)
			nbr[i].clear();
		dp[0][a] = 0;
		for (int i = 1, u, v; i <= p; i++) {
			double w;
			cin >> u >> v >> w;
			nbr[u].emplace_back((Edge){v, w});
			nbr[v].emplace_back((Edge){u, w});
		}
		for (int i = 1; i < (1 << n); i++)
			for (int x = 0; x < n; x++)
				if ((i >> x) & 1)
					for (int j = 1; j <= m; j++)
						for (auto k : nbr[j])
							dp[i][j] = min(dp[i][j], dp[i ^ (1 << x)][k.to] + 1.0 * k.w / t[x]);
		ans = 1e9;
		for (int i = 0; i < (1 << n); i++)
			ans = min(ans, dp[i][b]);
		if (ans == 1e9)
			cout << "Impossible\n";
		else
			cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：I_AK_IOI_and_NOI (赞：0)

## 思路

首先我们可以想到用 dfs 遍历所有情况来解决这个问题，

但是 dfs 复杂度太高，不适用这个题目，可以将 dfs 改为记忆化搜索的方法。

但是记忆化搜索也无法满足本题目，因为调用函数占用的时间也很多，

最后将递归改为递推式，利用动态规划的思想，

将记忆化搜索改为递推式动态规划写法即可。

----------

先说说如何写 dfs，

首先需要一个集合去判断去判断n张票哪一张被使用过了，进行标记，

再者需要一个遍历 $now$，表示当前抵达的城市，

只需要每次去遍历所有的票，从没选取的中选择一个，施加标记，

然后计算出一个结果，继续 dfs，直到遇到点 $b$，说明抵达目的地，

或者是集合中的票被使用完了，说明无法到达，

用一个全局遍历 $res$ 在每次抵达目的地后更新 $res$，

如果 $res$ 没被更新过说明无法到达，否则就输出 $res$ 即可。

dfs 复杂度高的原因是存在很多重复计算，只要将重复的计算删除，

就可以实现高效的记忆化搜索。

显然本题的搜索状态有两个，分别是票的集合以及当前到达的点，

集合如果用一个数组实现的话无法将其放入到 $dp$ 数组中，

所以可以用一个整数来表示这个集合，如果整数 $i$ 的第 $k$ 位是 0，

表示第 $k$ 张票没被选取，否则表示被选取。整数的大小依赖于票数，如果有 $n$ 张票，整数至少要 $2^n$ 这么大。

因此我们可以定义二维数组来记录每一个 dfs 两个确定参数的状态，

每次搜索到之后将 $dp$ 数组对应值更新，

如果下次进入 dfs 的状态在 $dp$ 数组中被更新过，就直接返回值，

否则就进行计算并在计算完成后更新 $dp$ 数组中对应状态的值。

```
double dfs(int index, int now) {//index表示选票的集合  now表示当前所在的城市 
	if (dp[index][now] < inf) {
		return dp[index][now];
	}
	if (now == b) {
		return dp[index][now] = 0;
	}
	if (index == (1 << n) - 1) {
		return inf * 1.0;
	}
	for (re int i = 1; i <= m; i++) {//遍历每一个即将要去的城市 
		if (g[now][i] >= 0) {
			for (re int j = 0; j < n; j++) {//遍历要选择的票 
				if (!(index >> j & 1)) {//选择票必须选择之前没有选择过的 
					dp[index][now] = min(dp[index][now], dfs(1 << j | index, i) + (double)g[now][i] / ticket[j]);
				}
			}
		}
	}
```


------------
通过记忆化搜索我们可以得到动态规划的状态转移方程，

通过状态转移方程可以得知，

计算过程中的状态是从集合大的方向往集合小的方向转移，

因此可以得知递推式的循环顺序，从大集合向小集合循环，

知道了循环方向，初始化一定是初始化循环的起点，

也就是不需要计算可以得知的状态，由此我们可以得到循环递推的代码。


```
for (re int i = (1 << n) - 1; i >= 0; i--) {
	for (re int j = 1; j <= m; j++) {//遍历当前所在的城市
		for (re int k = 0; k < n; k++) {//遍历要选择的票 
			if (!(i >> k & 1))for (re int l = 1; l <= m; l++) {//遍历要去的城市  
//					要求：票不能被选过一次，即不能在集合 i 中 
				if (g[j][l] >= 0) {//城市 j 和 l 之间必须有路相连 
					dp[i][j] = min(dp[i][j], dp[1 << k | i][l] + (double)g[j][l] / ticket[k]);//转移方程 
				}
			}
		}
	}
}
```



------------


完整代码：

```
#include<iostream>
#include<cstring>
using namespace std;
#pragma G++ optimize(2)
int n, m, p, a, b;
int ticket[10];
int g[33][33];
#define re register
const int maxn = 1 << 12;
const int inf = 0x3f3f3f3f;
double dp[maxn][33];
double ans;
double temp;
double dfs(int index, int now) {//记忆化搜索 
//index表示选票的集合  now表示当前所在的城市 
	if (dp[index][now] < inf) {
		return dp[index][now];
	}
	if (now == b) {
		return dp[index][now] = 0;
	}
	if (index == (1 << n) - 1) {
		return inf * 1.0;
	}
	for (re int i = 1; i <= m; i++) {//遍历每一个即将要去的城市 
		if (g[now][i] >= 0) {
			for (re int j = 0; j < n; j++) {//遍历要选择的票 
				if (!(index >> j & 1)) {//选择票必须选择之前没有选择过的 
					dp[index][now] = min(dp[index][now], dfs(1 << j | index, i) + (double)g[now][i] / ticket[j]);
					//					dp[index][now]=min(dp[index][now],dp[1<<j|index],i)+(double)g[now][i]/ticket[j];
				}
			}
		}
	}
}
int main()
{
	while (~scanf("%d %d %d %d %d", &n, &m, &p, &a, &b) && (n || m || p || a || b)) {
		for (re int i = 0; i < n; i++)scanf("%d", ticket + i);
		int t1, t2, t3;
		memset(g, -1, sizeof g);
		for (re int i = 0; i < maxn; i++)for (re int j = 0; j < 33; j++)dp[i][j] = inf;
		for (re int i = 0; i < p; i++) {
			scanf("%d %d %d", &t1, &t2, &t3);
			g[t1][t2] = g[t2][t1] = t3;
		}
		dp[(1 << n) - 1][a] = 0;//dp数组初始化 
		for (re int i = (1 << n) - 1; i >= 0; i--) {//递推式 
			for (re int j = 1; j <= m; j++) {//遍历当前所在的城市
				for (re int k = 0; k < n; k++) {//遍历要选择的票 
					if (!(i >> k & 1))for (re int l = 1; l <= m; l++) {//遍历要去的城市  
//					要求：票不能被选过一次，即不能在集合 i 中 
						if (g[j][l] >= 0) {//城市 j 和 l 之间必须有路相连 
							dp[i][j] = min(dp[i][j], dp[1 << k | i][l] + (double)g[j][l] / ticket[k]);//转移方程 
						}
					}
				}
			}
		}
		double res = inf * 1.0;
		for (re int i = 0; i < (1 << n); i++) {//从所有到达 b 的状态中选取最小值即是答案 
			res = min(res, dp[i][b]);
		}
		res == inf ? puts("Impossible") : printf("%lf\n", res);
	}
	return 0;
}
```
~~打了很久求过。~~


---

## 作者：Code_AC (赞：0)

### 题目大意：
给你一些车票和一些城市，问你从 $a$ 走到 $b$ 怎么走才能使总花费时间最小，并且没有限制城市的先后顺序。

### 题目分析：

这里看到题目后，因为数据范围 $1 \leqslant n \leqslant 8$ ，很容易就想到能用状压DP做，只不过这是在图上做DP。

但这里需要考虑一个很重要的问题，是对车票做状压还是对城市做状压？

**我们这样想：**

若是用城市来做状压，因为题目并没有规定先到哪一座，后到哪一座，所以城市是没有顺序的，也就是说你无法知道当前状态的上一个城市是哪一个，也就无法实现转移，所以我们这里只能对车票做状压。

然后三部曲：

**1.设计状态：**

这里我们设 $dp_{i,j}$ 表示表示车票使用情况是二进制下的i时，当前走到了城市j。

**2.状态转移：**

很明显，当前状态肯定是由上一个城市的状态再加上在当前车票状态下，它们之间所耗时间，由于要求最小值，所以取 $min$ 。

状态转移：

```cpp
for(register int i=0;i<(1<<n);i++)//枚举车票情况 
{
	for(register int j=0;j<n;j++)//枚举到当前城市所用车票编号 
	{
		if(!(i&(1<<j)))//无效状态，舍去 
			continue;
		for(register int x=1;x<=m;x++)//枚举上一个到达的城市 
		{
			for(register int l=head[x];l;l=e[l].nxt)//遍历图 
			{
				int y=e[l].to;
				double z=e[l].len;
				dp[i][x]=min(dp[i][x],dp[i^(1<<j)][y]+z*1.0/t[j+1]);//状态转移 
			}
		}
	}
}
```

**3.初始状态及输出：**

题目给了我们起点 $a$ ，所以初始状态就是将 $dp_{0,a}$ 设为 $0$ 。

输出是从所有的车票状态里找到到终点 $b$ 所用的时间最小值，即：

```cpp
for(register int i=0;i<(1<<n);i++)
	minn=min(minn,dp[i][b]);//在每种车票使用情况到终点所耗的时间中取最小值 
```

最后还要记得判断是否可以走到，详细见代码。

这里弱弱的问一句，为什么其他大佬都要用最短路，我没用好像也能过。


**Code（带注释版）**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=35;
const int MAXN=9; 
const int MAXM=1024;

struct Node
{
	int to,nxt;
	double len;
}e[MAXM];

int head[MAXM],cnt;

inline void add(int x,int y,int z)//链式前向星 
{
	e[++cnt].to=y;
	e[cnt].len=z;
	e[cnt].nxt=head[x];
	head[x]=cnt;
}

int n,m;
int p,a,b;
double t[MAXN+5];//马的数量 
double dp[1<<MAXN][N];//dp[i][j]表示车票使用情况是二进制下的i时，走到了城市j 

int main()
{
	while(scanf("%d%d%d%d%d",&n,&m,&p,&a,&b))
	{
		if(!n&&!m&&!p&&!a&&!b)//若均为0，则结束 
			return 0;
		cnt=0;
		memset(head,0,sizeof(head));//多组数据清空 
		for(register int i=0;i<(1<<n);i++)
		{
			for(register int j=1;j<=m;j++)
			{
				dp[i][j]=1e9;//将dp值设为极大值，后面好判断 
			}
		}
		for(register int i=1;i<=n;i++)
			scanf("%lf",&t[i]);//输入车票 
		for(register int i=1;i<=p;i++)
		{
			int x,y;
			double z;
			scanf("%d%d%lf",&x,&y,&z);
			add(x,y,z);
			add(y,x,z);//根据题目要求建双向边 
		}
		dp[0][a]=0;//到起点不需要车票，也不需要时间 
		for(register int i=0;i<(1<<n);i++)//枚举车票情况 
		{
			for(register int j=0;j<n;j++)//枚举到当前城市所用车票编号 
			{
				if(!(i&(1<<j)))//无效状态，舍去 
					continue;
				for(register int x=1;x<=m;x++)//枚举上一个到达的城市 
				{
					for(register int l=head[x];l;l=e[l].nxt)//遍历图 
					{
						int y=e[l].to;
						double z=e[l].len;
						dp[i][x]=min(dp[i][x],dp[i^(1<<j)][y]+z*1.0/t[j+1]);//状态转移 
					}
				}
			}
		}
		double minn=1e9;//设为极大值 
		for(register int i=0;i<(1<<n);i++)
		{
			minn=min(minn,dp[i][b]);//在每种车票使用情况到终点所耗的时间中取最小值 
		}
		if(minn!=1e9)//若有答案则输出 
		{
			printf("%.3lf\n",minn);
		}
		else
		{
			printf("Impossible\n");//否则输出Impossible
		}
	}
	return 0;
}
```

[实测AC](https://www.luogu.com.cn/record/76473700)


---

