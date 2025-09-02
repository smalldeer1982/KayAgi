# [ABC079D] Wall

## 题目描述

## 【题目大意】

你面前有一堵墙，墙上有数字，你需要将墙上的数字都变成 ```1``` 。  
现在给出一个 $W\times H$ 的矩阵 $A$ 表示墙上数字的情况。  
其中若 $A_{i,j}=-1$ ，则表示位置 $(i,j)$ 上没有数字，否则 $A_{i,j}$ 的值表示墙上 $(i,j)$ 位置的数字。  
当然，你还有一张 $10\times 10$ 的表 $C$，其中 $C_{i,j}$ 表示把数字 $i$ 转化成数字 $j$ 所需要的花费。  
求花费的最小值。

## 说明/提示

$1\le H,W\le200$  
$1\le C_{i,j}\le 10^3 (i\neq j)$  
$C_{i,j}=0(i=j)$  
$-1\le A_{i,j}\le 9$
所有数据保证在 ```int``` 范围以内。

## 样例 #1

### 输入

```
2 4
0 9 9 9 9 9 9 9 9 9
9 0 9 9 9 9 9 9 9 9
9 9 0 9 9 9 9 9 9 9
9 9 9 0 9 9 9 9 9 9
9 9 9 9 0 9 9 9 9 2
9 9 9 9 9 0 9 9 9 9
9 9 9 9 9 9 0 9 9 9
9 9 9 9 9 9 9 0 9 9
9 9 9 9 2 9 9 9 0 9
9 2 9 9 9 9 9 9 9 0
-1 -1 -1 -1
8 1 1 8```

### 输出

```
12```

## 样例 #2

### 输入

```
5 5
0 999 999 999 999 999 999 999 999 999
999 0 999 999 999 999 999 999 999 999
999 999 0 999 999 999 999 999 999 999
999 999 999 0 999 999 999 999 999 999
999 999 999 999 0 999 999 999 999 999
999 999 999 999 999 0 999 999 999 999
999 999 999 999 999 999 0 999 999 999
999 999 999 999 999 999 999 0 999 999
999 999 999 999 999 999 999 999 0 999
999 999 999 999 999 999 999 999 999 0
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1
1 1 1 1 1```

### 输出

```
0```

## 样例 #3

### 输入

```
3 5
0 4 3 6 2 7 2 5 3 3
4 0 5 3 7 5 3 7 2 7
5 7 0 7 2 9 3 2 9 1
3 6 2 0 2 4 6 4 2 3
3 5 7 4 0 6 9 7 6 7
9 8 5 2 2 0 4 7 6 5
5 4 6 3 2 3 0 5 4 3
3 6 2 3 4 2 4 0 8 9
4 6 5 4 3 5 3 2 0 8
2 1 3 4 5 7 8 6 4 0
3 5 2 6 1
2 5 3 2 1
6 9 2 5 6```

### 输出

```
47```

# 题解

## 作者：Erinyes (赞：4)

## Part 1 : 题目分析

题目给出了一个二维数组和 $0$ ~ $9$ 中不同数字之间变化的花费，求将这个二维数组中的所有数字都变成 $1$ 所需要的最小花费的和。

在这道题中，从把一个数字变成另一个数字时，可以使用另外一个数字作为 “跳板”，不一定要直接转化，所以很容易就可以想到最短路径。

于是这道题就简化成了:

给出一个**无向图**的[邻接矩阵](https://baike.baidu.com/item/%E9%82%BB%E6%8E%A5%E7%9F%A9%E9%98%B5/9796080?fr=aladdin)，求所有点到编号为 $1$ 的点的最短路径的长度的和。

## Part 2 ： 图的储存

题目输入的是 $0$ ~ $9$ 中的数字互相转化的花费，但是如果我们将 $0$ ~ $9$ 中的数字都看作图的点，那么这些花费便可以当作边权储存。

```cpp
for(int i=0;i<=9;i++){ 
	for(int j=0;j<=9;j++){ //i,j分别枚举0-9中的数字,也就是这条边连接的两个节点
		scanf("%d",&dis[i][j]); //dis数组储存边权
	}
}
```

## Part 3 ： 运算

题目给出的数组中有 $1$ 和 $-1$，$1$ 代表这个数字不需要转化，所以不需要加在总和上，而 $-1$ 代表这个位置没有数字，所以可以直接变成 $1$，也不需要加在总和上。

因为这道题需要求出的不止是单源最短路径，而是任意两个点之间的最短路径，所以我选择了 [Floyd 算法](https://baike.baidu.com/item/Floyd%E7%AE%97%E6%B3%95)来计算最短路径。

```cpp
void floyd(){
	for(int k=0;k<=9;k++){ //枚举每一个点
		for(int i=0;i<=9;i++){
			for(int j=0;j<=9;j++){
				if(dis[i][k]!=INF and dis[k][j]!=INF) dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]); //松弛操作
			}
		}
	}
}
```

注意：在使用 Floyd 算法计算最短路径时，$k$ , $i$ , $j$ 这三个变量在枚举时的顺序是固定的，因为 Floyd 算法的本质其实是动态规划，而 $k$ 枚举的是中间点，也就是状态，所以必须放在最外层。

最后再用一个 $ans$ 变量来累加最短路径的和。

```cpp
int ans=0;
for(int i=1;i<=h;i++){
	for(int j=1;j<=w;j++){
		scanf("%d",&x); //在输入时在线处理
		if(abs(x)==1) continue; //如果这个点是1或-1，则不需要加在ans上
		ans+=dis[x][1]; //累加x到1的最短路径
	}
}
```

## Part 4 ： 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define INF 0x7fffffff/2 //int最大值
using namespace std;
int h,w;
int x,dis[15][15];
void floyd(){
	for(int k=0;k<=9;k++){ //枚举每一个点
		for(int i=0;i<=9;i++){
			for(int j=0;j<=9;j++){
				if(dis[i][k]!=INF and dis[k][j]!=INF) dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]); //松弛操作
			}
		}
	}
}
int main(){
	scanf("%d%d",&h,&w);
	for(int i=0;i<=9;i++){
		for(int j=0;j<=9;j++){ //i,j分别枚举0-9中的数字,也就是这条边连接的两个节点
			scanf("%d",&dis[i][j]); //dis数组储存边权
		}
	}
	floyd();
	int ans=0;
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			scanf("%d",&x); //在输入时在线处理
			if(abs(x)==1) continue; //如果这个点是1或-1，则不需要加在ans上
			ans+=dis[x][1]; //累加x到1的最短路径
		}
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：cqbztz2 (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT3677)

# 题意

给出每个点之间转换的费用，求出最短路 $ c_{[a[i][j]][1]} $ 的总和。

# 思路

图论水题，首先跑一边 Floyd ,求出 $ c_{[a[i][j]][1]} $ 的最短路，最后循环求和。

# 代码

```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int n,m,dp[15][15],a[205][205],ans;
  int main(){
      cin>>n>>m;
      for(int i=0;i<10;i++){
          for(int j=0;j<10;j++){
              cin>>dp[i][j];
          }
      }
      for(int i=1;i<=n;i++){
          for(int j=1;j<=m;j++){
              cin>>a[i][j];
          }
      }
      for(int k=0;k<10;k++){//Floyd
          for(int i=0;i<10;i++){
              for(int j=0;j<10;j++){
                  dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j]);
              }
          }
      }
      for(int i=1;i<=n;i++){
          for(int j=1;j<=m;j++){
              if(a[i][j]!=-1){//求和
                  ans+=dp[a[i][j]][1];
              }
          }
      } 
      cout<<ans;
      return 0;
  }
```


---

## 作者：_byta (赞：3)

感觉其他题解都没有说为什么要用 $floyd$，在这里补充一下。

要想把所有数变成 $1$，那有两种选择，一是直接变成 $1$，二是将这个数先变成其他某个数，再有那个数继续迭代下去。

到这里，我们应该感觉到了，这与 $floyd$ 求最短路的过程一致，所以我们可以跑 $floyd$ 求解。

代码就不贴了，也就是一个 $floyd$ 的板子。

---

## 作者：Trump__Biden (赞：1)

### [传送门](https://www.luogu.com.cn/problem/AT_abc079_d)

## 题意：
给出每个点的花费，需要将它转换为 $ 1 $，求最小花费。
## 思路：
向 $ 1 $ 装换时需要借助一些点，肯定要借助花费小的点，我们可以把它抽象的理解为它到 $ 1 $ 这个点的最短路径。先跑一遍 Floyd，最后累计求和即可得出答案。
## 代码如下：
```
#include<iostream>
#include<cstdio>
#include<string>
#include<climits>
#include<cstring>
#include<algorithm>
#define inf 2147483647
using namespace std;
int h,w,a,ans,dis[10][10];
void Floyd(){
	for(int k=0;k<10;++k){
		for(int i=0;i<10;++i){
			if(i==k||dis[i][k]==inf){
				continue;
			}
			for(int j=0;j<10;++j){
				if(dis[i][k]!=inf&&dis[k][j]!=inf){
					dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
				}
			}
		}
	}
}
int main(){
	scanf("%d%d",&h,&w);
	for(int i=0;i<10;++i){
		for(int j=0;j<10;++j){
			scanf("%d",&dis[i][j]);
		}
	}
	Floyd();
	for(int i=1;i<=h;++i){
		for(int j=1;j<=w;++j){
			scanf("%d",&a);
			if(a==1||a==-1){
				continue;
			}
			else{
				ans=ans+dis[a][1];
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
```
不要忘记换行哦。

---

## 作者：TRZ_2007 (赞：1)

**[题解 【AT3677 [ABC079D] Wall】](https://www.luogu.com.cn/problem/AT3677)**    
# Solution  

我们可以把题目抽象化：就是说现在有从 0 到 9 共十个点，现有 $c_{i,j}$ 表示从 $i$ 到 $j$ 的路径长度为 $c_{i,j}$， 求 $\sum d_{a_{i,j},1}$ ,其中 $d_{i,j}$ 表示从 $i$ 到 $j$ 的最短路。  
然而这题只需要到 1 号点，是单元最短路，~~我们可以用 spfa 来解决~~。  
但是观察数据范围，发现在这个出具范围下， Floyd 也能够跑出优秀的速度，所以~~偷个懒~~用 Floyd 就好了。时间复杂度 $\mathcal{O(W\times H)}$

# Code  
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 209;

int c[N][N],h,w,ans,x;

int main() {
	scanf("%d %d",&h,&w);
	for(int i = 0;i < 10;i++) {
		for(int j = 0;j < 10;j++) scanf("%d",&c[i][j]);
	}
	for(int k = 0;k < 10;k++) {
		for(int i = 0;i < 10;i++) {
			for(int j = 0;j < 10;j++) if(c[i][j] > c[i][k] + c[k][j]) c[i][j] = c[i][k] + c[k][j];
		}
	}
	for(int i = 1;i <= h;i++) {
		for(int j = 1;j <= w;j++) {
			scanf("%d",&x);
			ans += (x == -1) ? 0 : c[x][1];
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

# 分析
首先我们来想想那张表 $C$ 每个位置的定义，$C_{i,j}$ 表示把数字 $i$ 转化成数字 $j$ 所需要的花费。

感觉很熟悉？

其实就是邻接矩阵！！(不懂邻接矩阵[戳这里](https://blog.csdn.net/weixin_39469127/article/details/81050955))

那就简单很多了，先用 floyd （不懂 floyd [戳这里](https://www.cnblogs.com/wangyuliang/p/9216365.html)） 求最短路（其实用 dijkstra 或者 spfa 都行，~~只是蒟蒻不想写~~）,再把墙上每个点的值（如果有值）到 $1$ 的最短路累加起来，最后输出。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int c[10][10],a[205][205];

int main(){
	int w,h,ans=0;
	cin>>w>>h;
	for(int i=0;i<10;++i)
		for(int j=0;j<10;++j){
			cin>>c[i][j];
		}
	for(int i=1;i<=w;++i)
		for(int j=1;j<=h;++j){
			cin>>a[i][j];
		}
	for(int k=0;k<10;++k)
		for(int i=0;i<10;++i)
			for(int j=0;j<10;++j){
				c[i][j]=min(c[i][j],c[i][k]+c[k][j]);
			}
	for(int i=1;i<=w;++i)
		for(int j=1;j<=h;++j)
			if(a[i][j]!=-1){
				ans+=c[a[i][j]][1];
			}
	cout<<ans<<endl;
	return 0;
}
```


---

