# [NWRRC 2021] Kaleidoscopic Route

## 题目描述

Kaleidostan 有 $n$ 个城市，通过 $m$ 条双向道路相连。城市编号从 $1$ 到 $n$。每条道路都有一个整数，称为“色彩度”。

Keanu 想从城市 $1$ 前往城市 $n$。他希望选择一条“最短”路线——即经过道路数最少的路线。在所有最短路线中，他又希望选择一条“万花筒”路线——即这条路线中道路的最大色彩度与最小色彩度之差尽可能大。请你帮助 Keanu 找到这样一条路线。

## 说明/提示

![](https://cdn.luogu.com.cn/upload/image_hosting/bun5oktu.png)

在示例测试中，所需路线经过 $3$ 条道路，且其最大色彩度与最小色彩度之差为 $8-2=6$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6 8
1 5 2
5 2 5
3 5 4
1 3 10
3 4 6
4 5 7
4 6 8
2 6 1```

### 输出

```
3
1 5 4 6```

# 题解

## 作者：zhuweiqi (赞：0)

题目大意：找出一条最短路且边权极差最大。

解题思路：以 $1$ 和 $n$ 为起点分别跑出每个点的最短路，且在最短路基础上可经过的边权最大的边的边权，这个用 bfs 就能预处理出来。然后枚举每条边，判断从起点走到这条边的端点加上另一个端点走到终点的距离再加一是否是最短路，是的话将最大边权减去这条边的边权，最后答案取最大值即可。

**坑点注意**：当 $n\leq 3$ 即答案边和 $1$ 或 $n$ 直接相连时，发现最终答案会变成负数，所以初始时答案应赋值为极小值。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+2;
vector<pair<int,int>> e[N];
int f1[N],fn[N],g1[N],gn[N],p1[N],pn[N];
queue<int> q;
struct node{int x,y,z;}s[N<<1];
vector<int> seq;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int n,m,ans=INT_MIN,idx=0;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int x,y,z;
		cin>>x>>y>>z;
		e[x].push_back({y,z});
		e[y].push_back({x,z});
		s[i]={x,y,z};
	}
	memset(f1,-1,sizeof(f1));
	memset(fn,-1,sizeof(f1));
	memset(g1,-1,sizeof(g1));
	memset(gn,-1,sizeof(g1));
	f1[1]=g1[1]=0;
	q.push(1);
	while(!q.empty()){
		int x=q.front();q.pop();
		for(auto it:e[x]){
			int y=it.first,z=it.second;
			if(f1[y]==-1){
				f1[y]=f1[x]+1;
				q.push(y);
			}
			if(f1[y]==f1[x]+1 && g1[y]<max(g1[x],z)){
				g1[y]=max(g1[x],z);
				p1[y]=x;
			}
		}
	}
	fn[n]=gn[n]=0;
	q.push(n);
	while(!q.empty()){
		int x=q.front();q.pop();
		for(auto it:e[x]){
			int y=it.first,z=it.second;
			if(fn[y]==-1){
				fn[y]=fn[x]+1;
				q.push(y);
			}
			if(fn[y]==fn[x]+1 && gn[y]<max(gn[x],z)){
				gn[y]=max(gn[x],z);
				pn[y]=x;
			}
		}
	}
	for(int i=1;i<=m;i++){
		int x=s[i].x,y=s[i].y,z=s[i].z;
		if(f1[x]+fn[y]+1==f1[n] && ans<max(g1[x],gn[y])-z) ans=max(g1[x],gn[y])-z,idx=i;
		if(fn[x]+f1[y]+1==f1[n] && ans<max(gn[x],g1[y])-z) ans=max(gn[x],g1[y])-z,idx=i;
	}
	cout<<f1[n]<<"\n";
	int x=s[idx].x,y=s[idx].y,z=s[idx].z;
	if(f1[x]+fn[y]+1==f1[n] && ans==max(g1[x],gn[y])-z){
		for(int num=x;num;num=p1[num]) seq.push_back(num);
		if(seq.back()!=1) return 1;
		for(int i=seq.size()-1;i>=0;i--) cout<<seq[i]<<" ";
		for(int num=y;num;num=pn[num]) cout<<num<<" ";
	}
	else {
		swap(x,y);
		for(int num=x;num;num=p1[num]) seq.push_back(num);
		if(seq.back()!=1) return 1;
		for(int i=seq.size()-1;i>=0;i--) cout<<seq[i]<<" ";
		for(int num=y;num;num=pn[num]) cout<<num<<" ";
	}
	return 0;
}
```

---

