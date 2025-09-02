# [EC Final 2022] Chase Game

## 题目描述

Shou 教授被 Pang 教授在一个无向无权简单图上追赶。最初，Shou 教授在顶点 $1$。他的目的地是顶点 $n$。Pang 教授在顶点 $k$。

每秒钟，Shou 教授可以选择一个相邻的顶点并走向该顶点。然后，Shou 教授会受到 Pang 教授的攻击。此次攻击的伤害等于 $d-dis$，其中 $d$ 是 Pang 教授的攻击范围，$dis$ 是图上从 Shou 教授到 Pang 教授的距离（最短路径上的边数）。然而，当 $dis$ 大于或等于 $d$ 时，Pang 教授无法造成任何正伤害。在这种情况下，他将不会使用非正的伤害攻击，而是会传送到 Shou 教授所在的顶点，然后造成 $d$ 伤害。（当 $dis$ 小于 $d$ 时，Pang 教授将停留在当前顶点。）

请找出 Shou 教授从顶点 $1$ 到顶点 $n$ 所需的最小伤害总和。Shou 教授将在顶点 $n$ 处受到最后一次攻击。

## 样例 #1

### 输入

```
5 5 3 1
1 2
2 4
4 5
1 3
3 5
```

### 输出

```
2
```

## 样例 #2

### 输入

```
13 17 12 3
1 2
2 3
3 4
4 13
5 13
7 8
7 9
7 10
7 11
7 6
12 7
1 8
8 9
9 10
10 11
11 6
6 13
```

### 输出

```
7
```

# 题解

## 作者：FFTotoro (赞：5)

考虑 Pang 教授要怎么追 Shou 教授。一开始如果 Shou 教授一直待在 Pang 教授的攻击范围内那么 Pang 教授就不会动，一旦出了攻击范围 Pang 教授肯定直接就追，具体地，每隔 $d$ 步一个周期，攻击分别为 $d,d-1,\ldots 2,1$，直到 Shou 教授到达 $n$ 被进行完最后一轮攻击。所以一旦出了范围 Shou 教授肯定就直接沿最短路往 $n$ 走。

于是我们可以用 Dijkstra 算法解题。令 $d_{u,v}$ 为 $u$ 到 $v$ 的最短距离，$l_u$ 为当前到 $u$ 受到的最小伤害。假设现在到了 $u$，那么走到另一个点 $v$（$u,v$ 没有出攻击范围）的代价就是 $l_u+d-d_{k,v}$。如果 $v$ 出了攻击范围，那么就是 $l_u$ 加上从 $v$ 到 $n$ 一路过去 Pang 教授一路追的伤害，可以简单地推式子实现。

注意预处理一下 $k$ 与 $n$ 到每个点的距离，可以使用 01bfs 实现。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
typedef pair<int,int> pii;
main(){
  ios::sync_with_stdio(false);
  int n,m,k,d,c=1e16; cin>>n>>m>>k>>d;
  vector<vector<int> > g(n);
  for(int i=1;i<=m;i++){
    int u,v; cin>>u>>v;
    g[--u].emplace_back(--v);
    g[v].emplace_back(u);
  }
  auto bfs=[&](int u){
    queue<int> q; q.emplace(u);
    vector<int> d(n);
    vector<bool> b(n); b[u]=true;
    while(!q.empty()){
      int u=q.front(); q.pop();
      for(int i:g[u])
        if(!b[i])b[i]=true,d[i]=d[u]+1,q.emplace(i);
    }
    return d;
  }; // 预处理最短距离
  auto s=[](int l,int r){
    return max(0ll,r*(r+1)-l*(l-1)>>1);
  }; // 求 l 到 r 的和
  auto f=[&](int x){
    return x/d*s(1,d)+s(d-x%d+1,d);
  }; // 求一路追过去，总共走了 x 个点的伤害
  vector<int> dk=bfs(k-1),dn=bfs(n-1),l(n,1e16);
  vector<bool> b(n);
  priority_queue<pii,vector<pii>,greater<> > q;
  q.emplace(l[0]=0,0);
  while(!q.empty()){
    int u=q.top().second; q.pop();
    if(b[u])continue; b[u]=true; // 打标记
    for(int i:g[u])
      if(dk[i]>=d)c=min(c,l[u]+f(dn[i]+1)); // 注意要 +1，是因为走到 i 这个点也进去
      else if(l[u]+d-dk[i]<l[i])q.emplace(l[i]=l[u]+d-dk[i],i); // 更新最短路
  } // 使用堆优化 Dijkstra
  cout<<min(c,l[n-1])<<endl; // 也有可能都不出范围
  return 0;
}
```

---

## 作者：wangboyue (赞：2)

# 题意
一张简单无向无权图上有 $2$ 个人 A 和 B，A 要从点 $1$ 走到点 $n$，B 最开始在点 $k$。当 A 移动时：
1. 若 A 与 B 的距离超过 $d$，则 B 传送到 A 并对 A 造成 $d$ 的伤害；
2. 否则，定义 AB 间距离为 $dis$，B 对 A 造成 $d-dis$ 的伤害。

最小化 A 受到的伤害，输出。
# 思路
明显地，当 A 与点 $k$ 的距离大于 $d$ 时，A 直接走最短路到点 $n$ 最优。  
可以用 Dijkstra 算法解决。  
定义 $dk_i$ 表示点 $k$ 到点 $i$ 的最短路长度，$dn_i$ 表示点 $n$ 到点 $i$ 的最短路长度，$de_i$ 表示 A 从点 $1$ 到点 $i$ 收到的伤害的最小值，$ans$ 表示 A 走到点 $n$ 受到的最小伤害。  
$dk$ 和 $dn$ 直接跑最短路即可。  
$de$ 和 $ans$ 的求取较为复杂。当 Dijkstra 枚举到 $cur$，下一个点为 $nxt$ 时有 $2$ 种情况：
1. 若 $dk_{nxt}\ge d$，直接更新答案；
2. 若 $dk_{nxt}<d$，$de_{nxt}\gets de_x+d-dk_{nxt}$。

详见代码。
# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int n,m,s,dis[N],de[N],ans=1e18,dn[N],dk[N],k,d;
bool vis[N];
vector<int> nbr[N];
int get(int l,int r){
	if(l>r){
		return 0;
	}
	return (l+r)*(r-l+1)/2; 
}
int getsum(int x){
	return x/d*get(1,d)+get(d+1-x%d,d);
}
struct node{
	int y,w;
	bool operator<(const node &o)const{
		return w>o.w;
	}
};
void dij(int s,bool f,int ds[]){
	for(int i=0;i<=n;i++){
		ds[i]=1e18;
		vis[i]=false;
	}
	priority_queue<node> q;
	ds[s]=0;
	q.push({s,0});
	while(!q.empty()){
		node cur=q.top();
		q.pop();
		int x=cur.y,w=cur.w;
		if(vis[x]){
			continue;
		}
		vis[x]=true;
		for(int nxt:nbr[x]){
			if(!f){
				if(ds[x]+1<ds[nxt]){
					ds[nxt]=ds[x]+1;
					q.push({nxt,ds[nxt]});
				}
			}
			else{
				if(dk[nxt]>=d){
					ans=min(ans,de[x]+getsum(dn[nxt]+1));
//					cerr<<"Updated ans! "<<ans<<endl;
				}
				else if(de[x]+d-dk[nxt]<de[nxt]){
					de[nxt]=de[x]+d-dk[nxt];
//					cerr<<"Relax "<<nxt<<"<-"<<de[nxt]<<endl;
					q.push({nxt,de[nxt]});
				}
			}
		}
	}
	return;
}
signed main(){
	cin>>n>>m>>k>>d;
	for(int i=1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		nbr[a].push_back(b);
		nbr[b].push_back(a);
	}
	dij(k,false,dk);
	dij(n,false,dn);
	dij(1,true,de);
	cout<<min(de[n],ans);
	return 0;
}
```

---

