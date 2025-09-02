# Wormhouse

## 题目描述

虫子阿尼又吃完了苹果屋，决定搬家。他把所有的房间从1到n编号。所有的走廊都是双向的。

阿尼希望新房子看起来和以前的一样。也就是说，它应该有N个房间，如果在旧房子里有一个从房间I到J室的走廊，它也应该建在新房子里。

我们知道，在建造房屋的过程中，阿尼从某个房间开始吃苹果，直到他穿过所有走廊，回到起点才停下来。众所周知，阿尼吃东西不停。也就是说，直到阿尼把房子盖好，他每时每刻都在忙着啃一条新走廊。阿尼不会沿着已经建成的走廊走。（一笔画）

然而，你换房子的时候，要以同样的顺序啃出走廊是一项非常困难的工作。这就是为什么阿尼知道走廊在前一栋房子里的位置顺序，想用另一个顺序啃走廊。它被表示为一个房间列表，按访问顺序排列。新的顺序应该是字典序上最小的，但是它也应该严格大于之前的字典序。

## 样例 #1

### 输入

```
3 3
1 2 3 1
```

### 输出

```
1 3 2 1 ```

## 样例 #2

### 输入

```
3 3
1 3 2 1
```

### 输出

```
No solution```

# 题解

## 作者：NXYorz (赞：5)

[题目链接](https://www.luogu.com.cn/problem/CF62D)

题目给你了一条欧拉回路，让你再找一条欧拉回路，使得新找到的欧拉回路的字典序在严格大于题目中给的欧拉回路的情况下，保证字典序最小。

可以考虑搜索啊....

在每一层我们都把当前节点的扩展到的节点扔到堆中，然后每一次取堆顶，从而保证了字典序是最小的。需要注意的是，字典序比较的是第一个不一样的地方，所以我们可以维护一个全局变量```flag```，表示我们的新的序列的字典序是否已经严格大于。

然后暴力断边，因为我建的是双向边，所以我标记的时候只考虑一对边中小的编号。如果找到符合题意的序列，直接输出即可。~~数据范围小啊~~

#### $Code$

```
#include<queue>

#define N 111
#define M 2101

using namespace std;

int n,m,sum;
int a[M],first[N],ans[M];
bool v[M*2],flag;

struct E
{
    int next;
    int to;
    void add(int x,int y)
    {
        next=first[x];
        to=y;
        first[x]=sum;
    }
}e[M*2];

struct NO
{
    int w;
    int num;
    bool operator < (const NO b) const
    {return w>b.w;}
};

void print()
{
    for(int i=1;i<=m+1;i++)
        printf("%d ",ans[i]);
    exit(0);
}

void dfs(int x,int loc)
{
    ans[loc]=x;
    if(loc==m+1)
    {
        if(flag) print();
        return;
    }
    priority_queue<NO> q;
    while(!q.empty()) q.pop();
    for(int i=first[x];i;i=e[i].next)
        q.push((NO){e[i].to,i});
    while(!q.empty())
    {
        NO now=q.top();q.pop();
        int i=now.num;
        if(v[i&1?i:i-1]) 
			continue;
        int to=e[i].to;
		bool bj=0;
        if(to<a[loc+1]&&!flag) 
			continue;
        if(to>a[loc+1]&&!flag) 
		{
			flag=1;
			bj=1;
		}
        v[i&1?i:i-1]=1;
		dfs(to,loc+1);
        v[i&1?i:i-1]=0;
		if(bj) flag=0;
    }
}

int main()
{
    freopen("aa.in","r",stdin);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m+1;i++)
        scanf("%d",a+i);
    for(int i=2;i<=m+1;i++)
    {
		e[++sum].add(a[i-1],a[i]);
		e[++sum].add(a[i],a[i-1]);
	}
    dfs(a[1],1);
	printf("No solution");
	return 0;
}
```
-------------


不知道为什么在预览中炸了，不知道会不会影响题解中的展示，但是在博客里是可以正常观看的，如果排版会炸，可以点击[这里](https://www.luogu.com.cn/blog/niexiaoyang12138/solution-cf62d)

---

## 作者：freoepn (赞：0)

按照题意直接从起点开始搜索欧拉回路即可，需要做一些剪枝来优化时间复杂度，如当前回路字典序一定小于给定回路时剪枝，优先搜索字典序小的下一个点，已经出解时终止搜索等，做完剪枝即可通过。


```cpp
#include <bits/stdc++.h>
using namespace std;
vector<int> v[103];
int a[2005];
int n, m;
bool b[2005][2005];
int s;
int ans[2005], anss[2005];
bool u = 0;
void dfs(int x, int siz, int p) {
  if(u == 1){
    return;
  }
  if (siz == m + 2) {
    if (p == 0 || u == 1 || s != ans[m+1]) {
      return;
    }
    u = 1;
    for (int i = 1; i <= m + 1; i++) {
      anss[i] = ans[i];
    }
    return;
  }
  for (int i = 0; i < v[x].size(); i++) {
    if (b[v[x][i]][x] == 0 && b[x][v[x][i]] == 0) {
      if (p == 1 || v[x][i] >= a[siz]) {
        b[x][v[x][i]] = 1;
        if (v[x][i] > a[siz]) {
          ans[siz] = v[x][i];
          dfs(v[x][i], siz + 1, 1);
        } else {
          ans[siz] = v[x][i];
          dfs(v[x][i], siz + 1, max(p, 0));
        }
        b[x][v[x][i]] = 0;
      }
    }
  }
}
signed main() {
  cin >> n >> m;
  for (int i = 1; i <= m + 1; i++) {
    cin >> a[i];
    if (i >= 2) {
      v[a[i - 1]].push_back(a[i]);
      v[a[i]].push_back(a[i - 1]);
    }
  }
  for (int i = 1; i <= n; i++) {
    sort(v[i].begin(), v[i].end());
  }
  for (int i = a[1]; i <= a[1]; i++) {
    s = i;
    ans[1] = i;
    if (i == a[1]) {
      dfs(a[1], 2, 0);
    } else {
      dfs(i, 2, 1);
    }
    if (u == 1) {
      for (int j = 1;j <= m+1; j++) {
        cout << anss[j] << " ";
      }
      return 0;
    }
  }
  cout << "No solution";
  return 0;
}
```

---

## 作者：hxhhxh (赞：0)

## 大意

给定一个图和一条图中的欧拉回路，求另一条欧拉回路，使得它的字典序比给的回路大。

## 思路

一看数据范围小，可以直接爆搜。

用一个`bool`记录当前是否和原回路字典序相等，如果相等就不用考虑比原字典序小的点能否到达。因为要找欧拉回路，所以走完一条边之后就可以直接断开这条边，回溯时在连回来。

如果已经走过了 $ m $ 条边，需要判断一下这条路径是否为欧拉回路，以及字典需是否**严格**大于原序列。

时间复杂度 $ O(\text{能过}) $ 

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[2222],n,m,ans[2222];
bool e[222][222];
bool dfs(int x,int p,bool dw){
	ans[x]=p;
	if(x==m+1&&p==a[m+1]&&(!dw)) return true;
	if(x==m+1){
		ans[x]=0;
		return false;
	}
	for(int i=1;i<=n;i++){
		if((!e[p][i])||(dw&&i<a[x+1])) continue;
		e[p][i]=e[i][p]=false;
		if(dfs(x+1,i,dw&&(i==a[x+1]))) return true;
		e[p][i]=e[i][p]=true;
	}
	ans[x]=0;
	return false;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m+1;i++){
		scanf("%d",&a[i]);
		if(i>1) e[a[i-1]][a[i]]=e[a[i]][a[i-1]]=true;
	}
	if(dfs(1,a[1],true)) for(int i=1;i<=m+1;i++) printf("%d ",ans[i]);
	else printf("No solution");
} 
```

---

