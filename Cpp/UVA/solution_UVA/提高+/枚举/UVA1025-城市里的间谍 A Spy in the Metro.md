# 城市里的间谍 A Spy in the Metro

## 题目描述

#### 题目大意

某城市地铁是一条直线，有 $n$（$2\leq	 n\leq	 50$）个车站，从左到右编号 $1\ldots n$。有 $M_1$ 辆列车从第 $1$ 站开始往右开，还有 $M_2$ 辆列车从第 $n$ 站开始往左开。列车在相邻站台间所需的运行时间是固定的，因为所有列车的运行速度是相同的。在时刻 $0$，Mario 从第 $1$ 站出发，目的在时刻 $T$（$0\leq T\leq 200$）会见车站 $n$ 的一个间谍。在车站等车时容易被抓，所以她决定尽量躲在开动的火车上，让在车站等待的时间尽量短。列车靠站停车时间忽略不计，且 Mario 身手敏捷，即使两辆方向不同的列车在同一时间靠站，Mario 也能完成换乘。

## 样例 #1

### 输入

```
4
55
5 10 15
4
0 5 10 20
4
0 5 10 15
4
18
1 2 3
5
0 3 6 10 12
6
0 3 5 7 12 15
2
30
20
1
20
7
1 3 5 7 11 13 17
0
```

### 输出

```
Case Number 1: 5
Case Number 2: 0
Case Number 3: impossible
```

# 题解

## 作者：alecli (赞：16)

此题属于较基本动态规划，详见lrj红书动态规划初步
- - -
 给定了左右站每个列车的发车时间以及每两站之间所需时间 因此可以想到以时间这个“序”为基准来做  用dp[i][j]表示在时刻i,你在车站j最低等待的时间，但首先要知道在i时刻，j这个车站是否有车,在此可以用两个bool数组保存
 
```cpp
for(int i=1; i<=M1; i++){
        int t1;//左(右）站出发时间
        cin>>t1;
        int sum=t1;
        for(int j=1; j<=n; j++){
            trainl[j][sum] = 1;
        //trainr[j][sum]=1;
            sum+=t[j];
        }
    }
```
存在的边界条件:

```cpp
for(int i=1; i<=n-1; i++)
        dp[T][i]=oo;//无法到达
    dp[T][n] = 0;
```
对于已经到达时间T 但未到达车站n的所有情况 dp[T][i]设置为无法到达

于是出现了三种决策：
1. 等一分钟
2. 乘坐向右开的车
3. 乘坐向左开的车

所以主程序的状态转移：

```cpp
//t[i]表示i站~i+1站所花时间
for(int i=T-1; i>=0; i--)//时间从后往前推
        for(int j=1; j<=n; j++){
            dp[i][j]=dp[i+1][j]+1;//等一分钟
            //注意限制条件
            if(j<n && trainl[j][i] && i+t[j]<=T )
            //乘坐向右开的车
                dp[i][j] = min(dp[i][j], dp[i+t[j]][j+1]);
            if(j>1 && trainr[j][i] && i+t[j-1]<=T )
            //乘坐向左开的车
                dp[i][j] = min(dp[i][j], dp[i+t[j-1]][j-1]);
    }
```
下面放完整程序：

```cpp
#include<bits/stdc++.h>
const int oo=0x3f3f3f3f;
using namespace std;
int n,T,M1,M2,kase;
int t[55];
bool trainl[55][10010];//train[i][j]:第i站第j时间是否有train
bool trainr[55][10010];
int dp[10010][55];//dp[i][j]:在时刻i你在车站j最低等多少时间
int main(){
    while(cin>>n && n!=0){
    kase++;
    cin>>T;
    memset(t, 0, sizeof(t));
    memset(trainl, 0, sizeof(trainl));
    memset(trainr, 0, sizeof(trainr));
    for(int i=1; i<=n-1; i++) cin>>t[i];//t[i]:i~i+1站时间
    cin>>M1;
    for(int i=1; i<=M1; i++){
        int t1;//左站出发时间
        cin>>t1;
        int sum=t1;
        for(int j=1; j<=n; j++){
            trainl[j][sum] = 1;
            sum+=t[j];
        }
    }
    cin>>M2;
    for(int i=1; i<=M2; i++){
        int t2;//右站出发时间
        cin>>t2;
        int sum=t2;
        for(int j=n; j>=1; j--){
            trainr[j][sum] = 1;
            sum+=t[j-1];
        }
    }
    for(int i=1; i<=n-1; i++)
        dp[T][i]=oo;
    dp[T][n] = 0;
    for(int i=T-1; i>=0; i--)
        for(int j=1; j<=n; j++){
            dp[i][j]=dp[i+1][j]+1;
            if(j<n && trainl[j][i] && i+t[j]<=T )
                dp[i][j] = min(dp[i][j], dp[i+t[j]][j+1]);
            if(j>1 && trainr[j][i] && i+t[j-1]<=T )
                dp[i][j] = min(dp[i][j], dp[i+t[j-1]][j-1]);
    }
    cout<< "Case Number " << kase<< ": ";
    if(dp[0][1] >= oo) cout<< "impossible\n";
    else cout<<dp[0][1] <<"\n";
    }
    return 0;
}

```

---

## 作者：⚡小林子⚡ (赞：14)

### 来发一波 Dijkstra 的题解

[题目传送门](https://www.luogu.com.cn/problem/UVA1025)

------------

**无关内容**

上课时老师把这题搞成了例题，本想着上谷看一看 Dijkstra 的题解，结果...

全是 DP！

然后呢...课下，就有了这篇题解。

------------
**正文**

大概就是把老师上课的思维再复述一遍吧。

- 将 $n$ 个站点按时间拆分成 $n\times T$ 个站点，点 $(i,j)$ 表示时间点 $j$ 时的 $i$ 站台。

- Maria 的目标是从站点 $(1,0)$ 到达站点 $(n,T)$，并使得总等待时间最短。

- 对于 Maria 到达站点 $(i,j)$ 时，最多有三种选择：

  - 待在 $i$ 站点不动， $(i,j)$ -> $(i,j+1)$ 存在边，权值为 $1$ （等待时间 $1$ 秒）
  
  - 如果时间点 $j$ 有从左向右的车经过站点 $i$，则 $(i,j)$ -> $(i+1,j+t[i])$ 存在边，权值为 $0$。
  
  - 如果时间点 $j$ 有从右向左的车经过站点 $i$，则 $(i,j)$ -> $(i-1,j+t[i-1])$ 存在边，权值为 $0$。

- 由于时间是单向的，该图是一个典型的 DAG。问题转换为求 $(1,0)$ 到 $(n,T)$ 的最短路径。

- 使用 Dijkstra 求解有权图的最短路。

  - 最大顶点数量：$n\times T=10000$，且有多组数据，普通 Dijkstra 可能超时。
  
  - 最大边数：$n\times T\times 3=30000$，Dijkstra 堆优化，时间复杂度：$\Theta(E\times log(E))$。

Code（注释挺详细的）：
```cpp
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
/*
	DAG 最短路：
	按时间拆点， 点 (i,j) 表示时间点  j 的 i 站台 。
	(i,j) -> (i,j+1) 存在边，权值为 1。
	如果时间点 j 有从 i 开往 i+1 的车，则 (i,j) 到 (i+1,j+t[i]) 存在边，权值为 0。
	如果 时间点 j 有从 i 开往 i-1 的车，则 (i,j) 到 (i-1,j+t[i-1]) 存在边，权值为 1。
	目标是 (i,0) 到 (n,T) 的等待时间最短（最短路）。
	顶点数量最多为 10000，边数量最多 30000， 使用 Dijkstra 堆优化，时间复杂度 O(E*Log(E))。
	
	预处理时间点 j，i 站台是否有车正好到达。
	forwardd[i][j]  标记时间点 j，i 站台 是否有往 i-1 的车。
	back[i][j]  标记时间点 j，i 站台 是否有往 i+1 的车。
*/ 
const int N=55,T=265,INF=0x3f3f3f3f;
//mt：见面时间。 
//t[i]：站台 i 到 j 的时间。 
int k,n,mt,t[N],m1,m2,d[N][T];
int vis[N][T],dis[N][T];
bool forwardd[N][T],back[N][T];
struct Node{
	int v,t,dis;
	bool operator < (const Node &rhs) const {
		return dis>rhs.dis;
	}
}vex;
//求从 (1,0) 到 (n,m) 的最短距离
void djs(){
	memset(dis,0x3f,sizeof dis);
	memset(vis,0,sizeof vis);
	dis[1][0]=0;
	vex.v=1;vex.t=0;vex.dis=0;
	priority_queue<Node>pq;
	pq.push(vex);
	while(!pq.empty()){
		//找出当前 dis 最小的
		vex=pq.top();pq.pop();
		int i=vex.v,j=vex.t;
		if(vis[i][j]) continue;
		vis[i][j]=1;
		if(i==n&&j==mt)
			return;
		//松弛所有连接点 
		//(vex.v,vex.t+1)
		if(j<mt&&dis[i][j]+1<dis[i][j+1]){
			dis[i][j+1]=dis[i][j]+1;
			vex.v=i;vex.t=j+1;vex.dis=dis[i][j+1];
			pq.push(vex);
		}
		//1->n 的方向，不在 n 号站台，当前有车，下一个状态的时间不超过 mt
		if(i<n&&forwardd[i][j]&&j+t[i]<=mt&&dis[i][j]<dis[i+1][j+t[i]]){
			dis[i+1][j+t[i]]=dis[i][j];
			vex.v=i+1;vex.t=j+t[i];vex.dis=dis[i][j];
			pq.push(vex);
		} 
		//n->1 的方向，不在 1 号站台，当前有车，下一个状态的时间不超过 mt
		if(i>1&&back[i][j]&&j+t[i-1]<=mt&&dis[i][j]<dis[i-1][j+t[i-1]]){
			dis[i-1][j+t[i-1]]=dis[i][j];
			vex.v=i-1;vex.t=j+t[i-1];vex.dis=dis[i][j];
			pq.push(vex);
		} 
	}
}
int main(){
	while(cin>>n&&n){
		//多组数据初始化
		memset(forwardd,0,sizeof forwardd);
		memset(back,0,sizeof back);
		cin>>mt;
		for(int i=1;i<n;i++)
			cin>>t[i];
		cin>>m1;
		//读取数据，预处理 forwardd[i][j] 
		int ts;  //发车时间 
		for(int i=1;i<=m1;i++){
			cin>>ts;
			for(int j=1;j<=n;j++){
				if(ts<=mt) forwardd[j][ts]=1;
				ts+=t[j];
			}
		}
		cin>>m2;
		//读取数据，预处理 back[i][j] 
		for(int i=1;i<=m2;i++){
			cin>>ts;
			for(int j=n;j>=1;j--){
				if(ts<=mt) back[j][ts]=1;
				ts+=t[j-1];
			}
		}
		djs();
		cout<<"Case Number "<<++k<<": ";
		if(dis[n][mt]>=INF) cout<<"impossible\n";
		else cout<<dis[n][mt]<<"\n";
	}
}
```
由于最近你谷无法提交 Uva，所以无法展出 AC 记录，但是能确定这个 Code 能过（在老师那边的 OJ 上过了）。

### The End.

---

## 作者：dl__hh6 (赞：11)

首先我们先看下题意：

在1..N个车站里，一个间谍在固定时间内，到达N，但他**尽可能多待在移动的火车上
少待在车站**，且已知站与站固定的时间和每辆车从1 或n 的发车时间与方向。

那么我们可以用一个三维数组来定义整个主要过程：
先设定两个变量。然后以时间为主轴，车站为副轴以及0,1来判断向左/向右是否有车经过来进行动态规划。

具体思路为：
 i表示 1..t 个时间，j表示 1..n 个车站枚举，而数组a表示在i时间里，j个车站，0（往左），1（往右）时是否有车。
  
```pascal
f[0,1]:=0;
  for i:=1 to t do
   for j:=1 to n do
   begin
    f[i,j]:=min(f[i,j],f[i-1,j]+1);
    if (a[i,j,0]=1)  and  (j<n)  then f[i,j]:=min(f[i,j],f[i-d[j],j+1]);
    if  (a[i,j,1]=1) and (j>1)   then f[i,j]:=min(f[i,j],f[i-d[j-1],j-1]);//d[j] 表示第j个车站到的第j+1 个车站的距离
   end;
```
以下为AC代码：

```pascal
uses math;//这里可以先用下Math库，之后能少写点函数过程

var 
k,s,n,i,m1,m2,j,t:longint;
d:array[-1000..1000] of longint;
f,a1:array[-1000..1000,-1000..1000] of longint;
a:array[-1000..1000,-1000..1000,0..1] of longint;

begin
  k:=0;
  while k=0 do//进行循环读入，当k=0时跳出循环
    begin
      fillchar(d,sizeof(d),0);
      fillchar(a,sizeof(a),0);
      fillchar(f,sizeof(f),100);//初始化
      inc(s);
      readln(n);//n表示表示站的数量，t表示规定时间
      if n=0 then exit;//如果当前为最后一个车站则exit
      readln(t);
      for i:=1 to n-1 do
        read(d[i]);
{以下为预处理}  
      readln(m1);
      for i:=1 to m1 do
      begin
        read(a1[i,1]);
        a[a1[i,1],1,1]:=1;
      end;
      for i:=1 to m1 do
        for j:=2 to n do
        begin
          a1[i,j]:=d[j-1]+a1[i,j-1];
          a[a1[i,j],j,1]:=1;
        end;
      readln(m2);
      for i:=m1+1 to m2+m1 do
        begin
          read(a1[i,n]);
          a[a1[i,n],n,0]:=1;
        end;
      for i:=m1+1 to m2+m1 do
        for j:=n-1 downto 1 do
        begin
          a1[i,j]:=d[j]+a1[i,j+1];
          a[a1[i,j],j,0]:=1;
        end;
{以上为预处理}
      f[0,1]:=0;//给第一个车站，初始时间赋初值
      for i:=1 to t do
        for j:=1 to n do
        begin
          f[i,j]:=min(f[i,j],f[i-1,j]+1);//在车站等着，时间+1
          if (a[i,j,0]=1)  and  (j<n)  then f[i,j]:=min(f[i,j],f[i-d[j],j+1]);/向左
          if  (a[i,j,1]=1) and (j>1)   then f[i,j]:=min(f[i,j],f[i-d[j-1],j-1]);//向右
        end;
      if f[t,n]<=t then  writeln('Case Number ',s,': ',f[t,n]) else
      writeln('Case Number ',s,': ','impossible');
    end;
  end.
end.//完工；
```



---

## 作者：Daniel_7216 (赞：8)

首先我们通过分析可以发现在第 $T$ 分钟以前，无论在哪个站台都有三种选择：等待、乘坐往右开的火车或乘坐往左开的火车（当然前提是有车可做）。接下来就开始定义状态了，假设 $dp_{i,j}$ 表示时刻 $i$ 在站台 $j$ 需要等待的时长。显然， $dp_{T,n}$ 表示成功到达，所以值为零，但是对于其余 $j$ 等于其他站台的 $dp_{T,j}$ 表示没有到达终点，值为正无穷。

初始化之后我们需要逆推时间从 $T-1$ 到 $0$ 的情况，如果选择等待，则有  $dp_{i,j} = dp_{i + 1,j}+1$ ，如果选择向右一站，则 $dp_{i,j} = \min(dp_{i,j}, dp_{i+t_j,j+1})$ , 如果选择向左一站，则 $dp_{i,j} = \min(dp_{i,j}, dp_{i+t_{j-1},j-1})$ ，最后 $dp_{0, 1}$ 就是答案，答案大于等于正无穷则说明无解。

 AC 代码：
 ```cpp
#include <cstdio>
#include <iostream>
#include <cstring> 
using namespace std;
const int INF = 0x3f3f; 
int n, T, t[51], m1, m2, a, b;
bool has_train[2001][51][2];//0右1左
int dp[2001][51], idx = 1;
int main(){
	while (true){
		scanf("%d", &n);
		if (n == 0) break;
        memset(has_train, 0, sizeof(has_train));
		scanf("%d", &T);
		for (int i = 1; i < n; i++){
			scanf("%d", &t[i]);
		}
		scanf("%d", &m1);
		for (int k = 0; k < m1; k++){
			scanf("%d", &a);
			for (int j = a, i = 1; j <= T, i <= n; i++){
				has_train[j][i][0] = true;
                j += t[i];
			}
		}
		scanf("%d", &m2);
		for (int k = 0; k < m2; k++){
			scanf("%d", &b);
			for (int j = b, i = n; j <= T, i >= 1; i--){
				has_train[j][i][1] = true;
                j += t[i - 1];
			}
		}
		for (int i = 1; i < n; i++) dp[T][i] = INF;
		dp[T][n] = 0;
		for (int i = T - 1; i >= 0; i--){
			for (int j = 1; j <= n; j++){
				dp[i][j] = dp[i + 1][j] + 1;
				if (j != n && i + t[j] <= T && has_train[i][j][0]){
					dp[i][j] = min(dp[i][j], dp[i + t[j]][j + 1]);
				}
				if (j != 1 && i + t[j - 1] <= T && has_train[i][j][1]){
					dp[i][j] = min(dp[i][j], dp[i + t[j - 1]][j - 1]);
				}
			}
		}
        cout << "Case Number " << idx << ": ";
		if (dp[0][1] >= INF) printf("impossible\n");
		else printf("%d\n", dp[0][1]);
		idx++;	
	}
	return 0;
}
```
完（无）结（耻）撒（求）花（赞） owo

---

## 作者：rsdbk_husky (赞：6)

## 零. 安利：

[安利一下我的博客。](https://rsdbkhusky.github.io/)

## 一. 思路

#### 1. 思考解法

- **时间** 是个好的 DP 阶段，时间轴上靠后发生的不会影响前面的事，反映到本题上就是 Maria 之后怎么走不会影响现在的最优解，**符合无后效性**。

- Maria 既可以乘向东的地铁，又可以乘向西的地铁，还可以呆着不动。那么一种情况可以由多种情况而来，多种情况也可以发展成一种情况，各种情况互相交织，**符合子问题重叠性**。

所以考虑 DP。

#### 2. 前缀和初始化

   题目给出了站的时间间距和每列地铁发车时的时间（只会从首末两站发车），事实上，地铁在前进中到达每站的时间就是个前缀和 ~~（偷偷点开标签我们也可以看到前缀和）~~，到达某站的时间就是前面所有站时间间距之和，当然还要加上发车时间。

#### 3. DP

我采用的是 **刷表法**，当然，**填表法** 也可以。

1. 所需条件：

    - $stabet_i$：站 $i-1$ 与站 $i$ 间相隔的时间。

    - $canright_{i,j}(canleft_{i,j})$：$i$ 时刻 $j$ 站是否有开向末站（首站）的火车。

    - $d_{i,j}$：得到 $i$ 时刻在 $j$ 站这种状态最少的停留时间。

通过前缀和我们已经得到 $canright$ 以及$canleft$ 数组。接下来就是状态转移了。

2. 初始状态：

易得，应初始化为： $d_{i,j}=\begin{cases}0~~~~~~~~~(i=0~\land~j=1)\\\infty~~~~~~~(else)       \end{cases}$

其中 $\infty$ 代表无法到达。
    
3. 状态转移：

因为本题的阶段之间不像普通的0/1背包那样只会由上一阶段转移到，而是也会由很多个单位时间之前的阶段转移到（站与站之间的时间不止1），所以我选择多维数组而非滚动数组。
	
首先，无论此刻此站有没有地铁，都可以在本站等待，这是普遍的转移；另外，如果此刻此站恰好有地铁，可以做特殊的转移。

**综上所述，状转方程**：（因为是刷表法，状转方程不方便写在一个括号里，蒟蒻就这么写了 qwq）

（$\operatorname{self}$ 代表自己）

$d_{i,j}=\min(\operatorname{self},~d_{i-1,j}+1)~~~~~~~~~~~~(i>0)$

$d_{i+stabet_{j+1},j+1}=\min(\operatorname{self},~d_{i,j})~~~~~~(canright_{i,j}=true)$

$d_{i+stabet_j,j-1}=\min(\operatorname{self},~d_{i,j})~~~~~~~~(canleft_{i,j}=true)$

4. 结果状态：

$d_{T,n}$

## 二. 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

const int MAXn = 50;
const int MAXT = 2000;
const int INF = 0x3f3f3f3f;

template <class T> 
inline void read(T &a) {
    register char c;while (c = getchar(), c < '0' || c > '9');register T x(c - '0');while (c = getchar(), c >= '0' && c <= '9')x = (x << 1) + (x << 3) + c - '0';a = x;  
}

int n, T, stabet[MAXn + 10], rightcnt, leftcnt;	
bool canright[MAXT + 10][MAXn + 10], canleft[MAXT + 10][MAXn + 10];	 
int d[MAXT + 10][MAXn + 10];										

int main() {
	int k = 0;
	read(n);
	while (n) {
		++k;
		memset(canright, 0, sizeof(canright));	// 
		memset(canleft, 0, sizeof(canleft));	//多组数据要初始化
		memset(d, 0x3f, sizeof(d));				//
		read(T);
		for (int i = 2; i <= n; ++i) {
			read(stabet[i]);
		}
		int time;								//
		read(rightcnt);							//
		for (int i = 1; i <= rightcnt; ++i) {	// 
			read(time);							//
			canright[time][1] = 1;				//
			for (int j = 2; j <= n; ++j) {		//
				time += stabet[j];				//
				canright[time][j] = 1;			//
			}									//
		}										//边读入边用前缀和计算canright和canleft数组
		read(leftcnt);							//
		for (int i = 1; i <= leftcnt; ++i) {	//
			read(time);							//
			canleft[time][n] = 1;				//
			for (int j = n - 1; j >= 1; --j) {	//
				time += stabet[j + 1];			//
				canleft[time][j] = 1;			//
			}									//
		}										//
		d[0][1] = 0;
		for (int i = 0; i <= T; ++i) {												//
			for (int j = 1; j <= n; ++j) {											//
				if (i)																//
					d[i][j] = min(d[i][j], 											//
								  d[i - 1][j] + 1);									//
				if (canright[i][j])													//
					d[i + stabet[j + 1]][j + 1] = min(d[i + stabet[j + 1]][j + 1], 	//动态规划 
													  d[i][j]					  );//
				if (canleft[i][j])													//
					d[i + stabet[j]][j - 1] = min(d[i + stabet[j]][j - 1], 			//
												  d[i][j]				  );		//
			}																		//
		}																			//
		if (d[T][n] == INF) {
			printf("Case Number %d: impossible\n", k);
		} else {
			printf("Case Number %d: %d\n", k, d[T][n]);
		}
		read(n);	
	}	
}
```

---

## 作者：楚风留罡 (赞：2)

**本题很多人大概是看了某《紫书》后来做的，我发现题解是用的反向做法，就是从目标状态倒推推回起始状态，在写这题的时候我没想到这个，于是用了正向顺推的方法，希望给写正向递推的选手一个参考吧。其实核心思想和倒推是差不多的**

每一秒在每个站台有3种决策：

1、等1秒，当前贡献值+1；

2、如果有左边来的车，依据贡献值大小，决策是否坐这辆车

3、如果有右边来的车，依据贡献值大小，决策是否坐这辆车

决策的原则：贡献值小的为当前最优决策

按照时间顺序，从第1s开始，顺推至第 T s，时间自成一轴，因此不会有后效性。

最终结果就是第 T s在第N号站台的最小贡献值。

```cpp
#include <cstdio>
#include <cstring>
#include <fstream>
#include <algorithm>
#define fi(i,l,r) for(int i=l;i<=r;i++)
#define fd(i,r,l) for(int i=r;i>=l;i--)

using namespace std;
const int maxn=55;
const int maxT=205;
const int INF=0x3f3f3f3f; 

int x,tot;
int N=1,T,M1,M2;
int f[maxT][maxn];
int Time[maxn];
bool lef[maxT][maxn];
bool rig[maxT][maxn];

template<typename T>void Read(T &x)
{
	x=0;char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar(); 
}
template<typename T>void Print(T x)
{if(x<0) {putchar('-');Print(-x);return;}if(x>9)Print(x/10);putchar(x%10+48);}


int main()
{
	while(true)
	{
		Read(N);
		if(N==0) break;
		tot++;//当前处理的任务编号，输出用 
		memset(Time,0,sizeof(Time));
		memset(f,0x3f,sizeof(f));
		memset(lef,0,sizeof(lef));
		memset(rig,0,sizeof(rig));
		Read(T);
		fi(i,1,N-1) Read(Time[i]);
		Read(M1);
		fi(i,1,M1)
		{
			Read(x);
			lef[x][1]=true;//x时刻在1号站点有车 
			fi(i,1,N-1)//这辆车开往右边，从左向右更新
			{
				x+=Time[i]; 
				if(x>T) break;
				lef[x][i+1]=true;
			}
		}
		Read(M2);
		fi(i,1,M2)
		{
			Read(x);
			rig[x][N]=true;//x时刻在N号站点有车 
			fd(i,N-1,1)//这辆车开往左边，从右向左更新
			{
				x+=Time[i];
				if(x>T) break;
				rig[x][i]=true;
			}
		}
		
		f[0][1]=0;//0时刻出发 
		fi(i,1,T)
		{
			fi(j,1,N)
			{
				int t=0x3f3f3f3f;
				if(lef[i][j])  //左边有车了，直接把这状态放在t里（t现在还是无穷大，不需要比较） 
				  t=f[i-Time[j-1]][j-1];
				if(rig[i][j])  //右边有车了，这时候t里可能已经存了左边有车的情况，因此要比较一下咯 
				  t=min(t,f[i-Time[j]][j+1]);
				f[i][j]=min(t,f[i-1][j]+1);//坐车和原地等待两种选其优 
			}
		}
		printf("Case Number %d: ",tot);
		if(f[T][N]>=0x3f3f3f3f) {puts("impossible");continue;} 
		printf("%d\n",f[T][N]);
	}
	return 0;
} 
```
**记得点个赞再走吧~！**

---

## 作者：安静学习 (赞：2)

	首先可以利用时间，车站建立一个DAG图，而从最后一个时间开始往前递推之前的情况。
   可以看成一个图，从最后的情况将结果一步步取最好的情况推上来
   dp表示的是时间t在车站n的最少等待时间，每一个车站的最少等待时间会
   一步步推到d[0][1]
   ```cpp
#include <iostream>
#include <climits>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <fstream>
using namespace std;
#define INF 0x3f3f3f3f
const int maxn = 250 + 10;
int has_train[maxn][maxn][2], dp[maxn][maxn], n, t, m1, m2, ttime[maxn];
fstream file;

void init(){
    memset(has_train, 0, sizeof(has_train));
    memset(ttime, 0, sizeof(ttime));
    cin >> t;
    for(int i = 1;i < n;i++){cin >> ttime[i];}
    cin >> m1;//left to right
    for(int i = 0;i < m1;i++){
        int temp = 0;
        cin >> temp;
        for(int j = 1; j < n; j++){
            has_train[temp][j][0] = 1;
            //cout << temp << ' ' << j << endl;
            //cin.get();
            temp += ttime[j];
            if(temp > t){break;}
        }
    }
    cin >> m2;//right to left
    for(int i = 0; i < m2; i++){
        int temp = 0, now = n;
        cin >> temp;
        for(int j = n - 1; j >= 1; j--){
            has_train[temp][j + 1][1] = 1;
            //cout << temp << ' ' << j + 1 << ' ' << endl;
            //cin.get();
            temp += ttime[j];
            if(temp >= t){break;}
        }
    }
}

void Dp(){
    for(int i = 1;i <= n;i++){dp[t][i] = INF;}
    dp[t][n] = 0;
    for(int i = t - 1; i >= 0; i--){
        for(int j = 1; j <= n; j++){
            dp[i][j] = dp[i + 1][j] + 1;//stay here
            if(has_train[i][j][0] && (j + 1) <= n && (i + ttime[j]) <= t){//go to right
                dp[i][j] = min(dp[i][j], dp[i + ttime[j]][j + 1]);
                //从后递推而来的结点和当前哪个更小
            }
            if(has_train[i][j][1] && (j - 1) >= 1 && (i + ttime[j - 1]) <= t){//go to left
                dp[i][j] = min(dp[i][j], dp[i + ttime[j - 1]][j - 1]);
            }
        }
    }
}

int main(){
    int kase = 0;
    file.open("out.txt", ios::out);
    while(cin >> n && n){
        init();
        Dp();
        //file.open("out.txt", ios::out);
        cout << "Case Number " << ++kase << ": ";
        if(dp[0][1] >= INF){cout << "impossible\n";}
        else{cout << dp[0][1] << endl;}
    }
    return 0;
}

```


---

## 作者：xiaohuang (赞：2)

### 题目描述：

一个间谍，他要从第一个车站开始恰好在用s时刻到达第n个车站。

给出车站之间的距离和两端火车的速度。求这个间谍在车站等候的时间的最小值。
        
### 分析：
经典动态规划题，f[i][j]表示恰好在第i个时刻，间谍在第j个车站。

动规DP是f[i][j]=min(f[i][j],f[i-1][j]+1);

### AC代码：
```pascal
var n,num,m1,m2,i,j,k,time,sx:longint;
    f:array[0..205,0..205] of longint;
    d,e,t:array[0..205] of longint;
    p:array[0..205,0..205,0..1] of 0..1;
function min(o1,o2:longint):longint;//求min
begin
  if o1<o2 then exit(o1) else exit(o2);
end;
begin
  read(n);
  num:=1;//把序号初始化为0
  while (n<>0) do
  begin
    for i:=0 to 200 do
      for j:=0 to 200 do
        f[i,j]:=maxlongint div 3;//把f[i][j]初始化成最大值
    fillchar(p,sizeof(p),0);//把p[i][j][]初始化成0
    fillchar(t,sizeof(t),0);//把车站之间的距离更新为0
    fillchar(d,sizeof(d),0);//把从出发点出来的列车速度更新为0
    fillchar(e,sizeof(e),0);//把从终点出来的列车速度更新为0
    read(time);//读入time
    for i:=1 to n-1 do//读入车站之间的距离
      read(t[i]);
    read(m1);//读入从出发点出来的列车的数量
    for i:=1 to m1 do//读入从出发点出来的列车的速度
      read(d[i]);
    read(m2);//读入从终点出来的列车的数量
    for i:=1 to m2 do//读入从终点出来的列车的速度
      read(e[i]);
    for i:=1 to m1 do//初始化p[i][j][1]
    begin
      k:=1;
      j:=d[i];
      while (j<=time) do
      begin
        p[j,k,1]:=1;
        inc(k);
        if (k>n) then break;
        j:=j+t[k-1];
      end;
    end;
    for i:=1 to m2 do//初始化p[i][j][0]
    begin
      k:=n;
      j:=e[i];
      while (j<=time) do
      begin
        p[j,k,0]:=1;
        dec(k);
        if (k=0) then break;
        j:=j+t[k];
      end;
    end;
    f[0,1]:=0;//动态规划初始化
    for i:=1 to time do//开始DP
      for j:=1 to n do
      begin
        f[i,j]:=min(f[i,j],f[i-1,j]+1);//动态规划方程
        if (p[i,j,1]=1) then f[i,j]:=min(f[i,j],f[i-t[j-1],j-1]);//动态规划条件方程
        if (p[i,j,0]=1) then f[i,j]:=min(f[i,j],f[i-t[j],j+1]);//动态规划条件方程
      end;
    if f[time,n]=maxlongint div 3 then writeln('Case Number ',num,': impossible') else//判断impossible情况
    writeln('Case Number ',num,': ',f[time,n]);//输出
    read(n); inc(num);//继续读入n，并且增加num
  end;
end.
```

---

## 作者：RyexAwl (赞：1)

## 状态设计

时间不能倒流，提供了一种天然的拓扑序。

设 $f(i,j)$ 是在时刻 $i$ ，在第 $j$ 个车站,想要在第 $T$ 个时刻到第 $n$ 站的最少等待次数。

对于任意状态 $f(i,j)$ 有以下三种决策：

1. **等一分钟**

2. **搭向右开的车（如果有）**

3. **搭向左开的车（如果有）**

## 决策 1

对于决策 $1$ 在等一分钟后，位置没变，时间加 $1$，那么我们要让其这个状态的等待时间最小，并且要加上等待的一分钟，那么就等价于 $f(i+1,j)+1$ （最优子结构）

## 决策 2 与 3
对于决策 $2$ ，我们可以在规定时间内到达位于位于 $j$ 站右面的任意一站，并且要满足：

$$
i+\sum_{k=j}^{n-1}t[k] \le T
$$

当前决策转移即为：

$$
\min\limits_{j\le k\le n-1}\{f(i+\sum_{w=j}^{k}t[w],k+1)\}
$$

而对于状态：

$$
\min\limits_{j+1\le k\le n-1}\{f(i+t[j]+\sum_{w=j+1}^{k}t[w],k+1)\}
$$

在状态 $f(i+t[j],j+1)$ 已经计算过。

因此当前决策的转移即为 $f(i+t[j],j+1)$

而对于决策约束，如果状态 $f(i+t[j],j+1)$ 不合法，状态 $f(i,j)$ 必然不合法，只需要将所有状态初始化为正无穷即可解决问题。

同理对于决策三，其转移状态为 $f(i+t[j-1],j-1)$。

## 转移方程
因此状态转移方程即为：
$$
f(i,j)=\max\left\{
\begin{aligned}
&f(i+1,j)+1 \\ 
&f(i+t[j],j+1) \\
&f(i+t[j-1],j-1)
\end{aligned}
\right.
$$
边界：$f(T,n)=0$；

目标：$f(0,1)$。

代码：

```cpp
#include <iostream>
#include <cstring>

namespace wxy{
    const int N = 55,T = 12550,inf = 0x3f3f3f3f;
    bool l[T][N],r[T][N];
    int f[T][N],ti[N];
    inline void init(){
        memset(l,false,sizeof l);
        memset(r,false,sizeof r);
        memset(ti,0,sizeof ti);
        memset(f,0x3f,sizeof f);
    }
    void main(){
        int Case = 0;
        int n;
        while (std::cin >> n && n != 0){
            ++Case;
            int t;
            std::cin >> t;
            init();
            for (int i = 1; i < n; i++) std::cin >> ti[i];
            int m1,m2;
            std::cin >> m1;
            for (int i = 1; i <= m1; i++){
                int start;
                std::cin >> start;
                l[start][1] = true;
                for (int j = 1; j < n; j++){
                    l[start + ti[j]][j + 1] = true;
                    start += ti[j];
                } 
            }
            
            
            std::cin >> m2;
            for (int i = 1; i <= m2; i++){
                int start;
                std::cin >> start;
                r[start][n] = true;
                for (int j = n - 1;j >= 1; j--){
                    r[start + ti[j]][j] = true;
                    start += ti[j];
                }
            }
            
            f[t][n] = 0;
            for (int i = t - 1; i >= 0; i--){
                for (int j  = 1; j <= n; j++){
                    f[i][j] = f[i + 1][j] + 1;
                    if (j < n && l[i][j]) f[i][j] = std::min(f[i][j],f[i + ti[j]][j + 1]);
                    if (j > 1 && r[i][j]) f[i][j] = std::min(f[i][j],f[i + ti[j - 1]][j - 1]);
                }
            }
            if (f[0][1] >= inf) std::cout << "Case Number " << Case << ": " << "impossible"<<std::endl;
            else std::cout << "Case Number " << Case << ": " << f[0][1] << std::endl;
            
        }


    }
}signed main(){wxy::main();return 0;}
```


---

## 作者：gongbangrui (赞：1)


分析
------------

时间是单向流逝的，是一个天然的“序”。影响到决策的只有当前时间和所处的车站，所以可以用d(i,j)表示时刻i，你在车站j（编号为1～n），最少还需要等待多长时间。边界条件是d(T,n)=0，其他d(T,i)（i不等于n）为正无穷。有如下3种决策。
		决策1：等1分钟。
		决策2：搭乘往右开的车（如果有）。
		决策3：搭乘往左开的车（如果有）。
        
        
主过程的代码如下：
------------

```cpp
for(int i = 1; i <= n-1; i++) dp[T][i] = INF;
dp[T][n] = 0;
for(int i = T－1; i >= 0; i——)
	for(int j = 1; j >= n; j++) {
	dp[i][j] = dp[i＋1][j] + 1; //等待一个单位
	if(j < n && has_train[i][j][0] && i+t[j] ＜= T)
		dp[i][j] = min(dp[i][j], dp[i＋t[j]][j＋1]); //右
	if(j > 1 && has_train[i][j][1] && i＋t[j－1] ＜= T)
		dp[i][j] = min(dp[i][j], dp[i＋t[j－1]][j－1]); //左
}
//输出
cout << "Case Number " << ++kase << ": ";
if(dp[0][1] >= INF) cout << "impossible\n";
else cout << dp[0][1] << "\n";
```


代码解释
------------
		
上面的代码中有一个has_train数组，其中has_train[t][i][0]表示时刻t，在车站i是否有往右开的火车，has_train[t][i][1]类似，不过记录的是往左开的火车。这个数组不难在输入时计算处理，细节留给读者思考。状态有O(nT)个，每个状态最多只有3个决策，因此总时间复杂度为O(nT)。


---

## 作者：SymphonyOfEuler (赞：0)

这题和P2583 地铁间谍一模一样，这个是我那个题的题解：[戳我](https://www.luogu.com.cn/blog/TRYHARDAKIOI/solution-p2583)。

真的是所谓的双倍经验，但是为了让没有看过那题的人，我再写一遍：

这道题是DAG上DP。

我们用dp的第一维表示现在在哪个车站，第二维表示现在几点。再定一个hTrain数组第一维表示在这个时刻，第二维表示在哪个车站，然后第三维是有没有向左右开的。还有一个t数组表示从i站到下一站需要的时间。

所以这整个问题变成了一个二维的问题：当前时间和现在所在的车站。

预处理时候对于m1，输入进来$d_i$从1循环到n枚举车站j，如果d大于了碰头时刻，那么直接跳出，否则把d时刻，j车站，往右开的车标为true，然后d加这个车站花费的时间。对于m2，输入进来$e_i$从n循环到1枚举车站j，如果e大于了碰头时刻，那么直接跳出，否则把e时刻，j车站，往左开的车标为true，然后e加这个车站花费的时间。把dp数组开始初始化一个时间节点，若到了，就不行，后面判断方便。并且初始化最后终点不许等待

这样枚举时间和车站，第一种策略是站着不动，于是$dp[i][j]=dp[i+1][j]+1$。然后对于向右和向左分别需要判断在范围之内，并且有火车，然后自己和这个车站加上跑了$ti[j]$步和下一个时间阶段取min。左面同理，判断完条件之后自己和车站加$ti[j-1]$还有前一个时间段取min。最后判断如果$dp[0][1]$位上比初始化的大，那么肯定不可能，则输出impossible，否则输出$dp[0][1]$。


借助注释：

```

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int ti[55], hTrain[2005][55][2];
int dp[2005][55];

int kase;

int main() {
    int n, t;
    while (true) {
        cin >> n >> t;
        kase++;
        memset(hTrain, 0, sizeof(hTrain));//必须清零
        if (n == 0) break;
        for (int i = 1; i <= n - 1; ++i) {
            cin >> ti[i];
        }
        int m1;
        cin >> m1;
        for (int i = 0; i < m1; ++i) {//预处理向右
            int d;
            cin >> d;
            for (int j = 1; j <= n; ++j) {
                if (d > t) {
                    break;
                }
                hTrain[d][j][0] = 1;
                d += ti[j];
            }
        }
        int m2;
        cin >> m2;
        for (int i = 0; i < m2; ++i) {//预处理向左
            int e;
            cin >> e;
            for (int j = n; j >= 1; --j) {
                if (e > t) {
                    break;
                }
                hTrain[e][j][1] = 1;
                e += ti[j - 1];
            }
        }
        for (int j = 0; j < n; ++j) {//初始化dp数组
            dp[t][j] = 5000;
        }
        dp[t][n] = 0;
        for (int i = t - 1; i >= 0; --i) {//time
            for (int j = 1; j <= n; ++j) { //which station
                dp[i][j] = dp[i + 1][j] + 1;
                if (j < n && i + ti[j] <= t && hTrain[i][j][0]) { //right
                    dp[i][j] = min(dp[i][j], dp[i + ti[j]][j + 1]);
                }
                if (j > 1 && i + ti[j - 1] <= t && hTrain[i][j][1]) { //left
                    dp[i][j] = min(dp[i][j], dp[i + ti[j - 1]][j - 1]);
                }
            }
        }
        if (dp[0][1] >= 5000) {//判断
            printf("Case Number %d: impossible\n", kase);
        } else {
            printf("Case Number %d: %d\n", kase, dp[0][1]);
        }
    }
    return 0;
}
```


---

