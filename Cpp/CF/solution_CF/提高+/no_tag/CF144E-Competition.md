# Competition

## 题目描述

The secondary diagonal of a square matrix is a diagonal going from the top right to the bottom left corner. Let's define an $ n $ -degree staircase as a square matrix $ n×n $ containing no squares above the secondary diagonal (the picture below shows a 5-degree staircase).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF144E/e3fce56b75bea8833ad5e51edea79f8a51661523.png)The squares of the $ n $ -degree staircase contain $ m $ sportsmen.

A sportsman needs one second to move to a side-neighboring square of the staircase. Before the beginning of the competition each sportsman must choose one of the shortest ways to the secondary diagonal.

After the starting whistle the competition begins and all sportsmen start moving along the chosen paths. When a sportsman reaches a cell of the secondary diagonal, he stops and moves no more. The competition ends when all sportsmen reach the secondary diagonal. The competition is considered successful if during it no two sportsmen were present in the same square simultaneously. Any square belonging to the secondary diagonal also cannot contain more than one sportsman. If a sportsman at the given moment of time leaves a square and another sportsman comes to it, then they are not considered to occupy the same square simultaneously. Note that other extreme cases (for example, two sportsmen moving towards each other) are impossible as the chosen ways are the shortest ones.

You are given positions of $ m $ sportsmen on the staircase. Your task is to choose among them the maximum number of sportsmen for who the competition can be successful, that is, so that there existed such choice of shortest ways for the sportsmen at which no two sportsmen find themselves in the same square simultaneously. All other sportsmen that are not chosen will be removed from the staircase before the competition starts.

## 说明/提示

A note to the first sample.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF144E/3d94f14c44e777f4fdd801207cac70018a6b3b0e.png) The picture shows a three-degree staircase. The arrows show the shortest paths that the sportsmen choose.

## 样例 #1

### 输入

```
3 3
2 3
3 2
3 3
```

### 输出

```
3
1 2 3 
```

# 题解

## 作者：jifbt (赞：2)

## 题意简述

[题目链接](https://www.luogu.com.cn/problem/CF144E)

有一个 $n \times n$ 的方阵，副对角线（左下—右上）的左上方被去掉了，如图所示。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF144E/e3fce56b75bea8833ad5e51edea79f8a51661523.png)

方阵中有 $m$ 个人，每个人在一秒内可以走到相邻的一个格子。在开始前，他们可以分别选择一条到副对角线的最短路径。然后他们同时开始沿着最短路径运动，走到副对角线上时停止。在任何时刻，两个人不能位于同一个格子（即使他们已经停止运动）。

请保留最多的人，使得存在一种合法的移动方案。

## 思路

以下称「斜线」为平行于副对角线的线。

首先容易发现，最短路径是只往左或往上走的路径。由此可以确定出每个人可以到达的终点区间。

在某个时刻，两个人位于同一个格子，要么说明他们位于同一条斜线上，且运动路径有交叉；要么说明他们的路径终点为同一个。

为了让后一种情况不发生，我们考虑给每一个人找不同的终点，这相当于在若干区间中选出互不相同的点。

然后看前面的情况。如果在同一条斜线上的人，他们在斜线上的顺序与终点在副对角线上的顺序相同，那么让每个人先向左走，再向上走，这样一定是合法的。否则我们可以交换配对的顺序，这样操作后方案合法，且答案不变。

![](https://cdn.luogu.com.cn/upload/image_hosting/5gnbdst7.png)

这样，我们把问题转化为在若干区间中选互不相同的点，使得选出的点数量最多。我们从左往右扫，如果这个点还可以在某些区间中选中，则贪心地选择右边界最靠左的区间。

我们可以把区间排序，从左往右扫时，用 `priority_queue` 维护可以选择的区间。复杂度大致为 $O(n+m\log m)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define rp(i,a,b) for(int i=(a);i<=(b);++i)
using namespace std;
template<typename T>void rd(T&x){
	x=0;int f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-48;c=getchar();}
	x*=f;
}
template<typename T,typename...T2>void rd(T&x,T2&...y){rd(x),rd(y...);}
const int N=1e5+5;
int n,m;
struct T{int s,t,i;}a[N];
bool operator<(const T&a,const T&b){return a.t>b.t;}
priority_queue<T>q;
vector<int>v;
int main(){
	rd(n,m);
	rp(i,1,m){int x,y;rd(x,y);a[i]={n+1-x,y,i};}
	sort(a+1,a+m+1,[](const T&a,const T&b){return a.s<b.s;});
	int j=1;
	rp(i,1,n){
		while(a[j].s==i)q.push(a[j]),++j;
		if(!q.empty())v.push_back(q.top().i),q.pop();
		while(!q.empty()&&q.top().t==i)q.pop();
	}
	printf("%d\n",v.size());
	for(int i:v)printf("%d ",i);
}
```

---

## 作者：Allanljx (赞：1)

## 思路
我们可以算出，每一个格子到达辅助对角线的最短距离以及每个运动员能到达哪几个辅助对角线上的格子（走最短距离，记录左右端点）。然后枚举每个辅助对角线上的格子，在所有能到达这个格子的点中找右端点最小的。

## 代码
```cpp
#include<bits/stdc++.h>
#define mp make_pair
using namespace std;
int n,m,top;
int ans;
int ans1[100005];
int x[100005],y[100005];
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
vector<pair<int,int> > t[100005];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>x[i]>>y[i];
		t[n-y[i]+1].push_back(mp(x[i],i));//表示左端点为i时的右端点
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<t[i].size();j++)
		{
			q.push(t[i][j]);//将左端点满足要求的放进去
		}
		while(q.size()&&q.top().first<i)//将左端点大于当前格子的剔除
		{
			q.pop();
		}
		if(q.size())//找右端点最小的
		{
			ans1[++ans]=q.top().second;
			q.pop();
		}
	}
	cout<<ans<<endl;
	for(int i=1;i<=ans;i++) cout<<ans1[i]<<' ';
	return 0;
}
```


---

