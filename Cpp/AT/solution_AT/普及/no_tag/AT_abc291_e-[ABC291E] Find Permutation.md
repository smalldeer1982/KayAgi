# [ABC291E] Find Permutation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc291/tasks/abc291_e

$ 1,\ldots,N $ の並び替えである長さ $ N $ の数列 $ A=(A_1,\ldots,A_N) $ があります。

あなたは $ A $ を知りませんが、$ M $ 個の整数の組 $ (X_i,Y_i) $ について、$ A_{X_i}\ <\ A_{Y_i} $ が成り立つことを知っています。

$ A $ を一意に特定できるかどうか判定し、できるなら $ A $ を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ X_i,Y_i\ \leq\ N $
- 入力は全て整数である
- 入力に矛盾しない $ A $ が存在する

### Sample Explanation 1

$ A=(3,1,2) $ であると一意に特定できます。

### Sample Explanation 2

$ A $ として $ (2,3,1),(3,2,1) $ の $ 2 $ 通りが考えられます。

## 样例 #1

### 输入

```
3 2
3 1
2 3```

### 输出

```
Yes
3 1 2```

## 样例 #2

### 输入

```
3 2
3 1
3 2```

### 输出

```
No```

## 样例 #3

### 输入

```
4 6
1 2
1 2
2 3
2 3
3 4
3 4```

### 输出

```
Yes
1 2 3 4```

# 题解

## 作者：ダ月 (赞：7)

### 题意概要：

对于一个 $1,2,3,\dots,n$ 排列 $A$。给定其中 $m$ 对关系 $x_i,y_i$，满足 $A_{x_i}<A_{y_i}$。问该排列是否唯一。题目保证至少有一个排列与这些关系相匹配。

### 题目分析：

既然题目保证至少有一个排列与这些关系相匹配，这说明了条件保证不矛盾。

拿到这道题，可以考虑 $x_i$ 向 $y_i$ 连一条有向边，表示 $x_i$ 位置上的数小于 $y_i$ 上的数。

然后将问题转换一下，变成给定一张有向图，不存在环。求是否存在一条长度为 $n$ 链，为该图的子图。

我们记每个点的入度。显然，如果有两个及以上的入度为 $0$ 的点，那么 $1$ 这个数字所在点的位置不确定。

既然点有唯一的先后顺序，接下来跑拓扑排序，看拓扑排序是否深度为 $n$。

### 代码如下：

```
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
vector<int> a[N];
int into[N];
int n,m;
bool vis[N];
int ans[N];
int wh;
struct node{
	int x,dep;
};
bool bfs(){
	queue<node> q;
	q.push({wh,1});
	while(!q.empty()){
		int x=q.front().x;
		int D=q.front().dep;ans[x]=D;
		if(D==n) return true;
		q.pop();
		if(vis[x]) continue;
		vis[x]=true;
		for(int i=0;i<a[x].size();i++){
			into[a[x][i]]--;
			if(!into[a[x][i]])
				q.push({a[x][i],D+1});
		}
	}return false;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int x,y;scanf("%d%d",&x,&y);
		a[x].push_back(y);
		into[y]++;
	}
	int num=0;
	for(int i=1;i<=n;i++)
		if(!into[i]){
			wh=i;num++;
		}
	if(num!=1){puts("No");return 0;}
	if(bfs()){
		puts("Yes");
		for(int i=1;i<=n;i++) printf("%d ",ans[i]);
	}else puts("No");
	return 0; 
}
```

时间复杂度：$O(n)$。

---

## 作者：FFTotoro (赞：2)

本题需要使用**拓扑排序**。

因为题目中保证有解，所以将题目中的大小关系作为有向边建图，可得该图为一 DAG（有向无环图）。

根据拓扑序的性质：对于有向无环图 $G=(V,E)$ 中任意一对顶点 $u$ 和 $v$，若边 $<u,v>\in E$，则 $u$ 在拓扑序中出现在 $v$ 之前；就可以构造出需要的排列。

那么如何判断多解呢？显然，如果有多个合法的拓扑序，就会有多解。所以，如果 BFS 过程中队列里有多个元素，那么拓扑序就不唯一（可以通过任意的顺序遍历队列中的元素），直接判断输出即可。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
vector<int> g[200001],a;
int d[200001],b[200001];
map<pair<int,int>,bool> mp;
main(){
  ios::sync_with_stdio(false);
  int n,m; cin>>n>>m;
  for(int i=1;i<=m;i++){
    int u,v; cin>>u>>v;
    if(mp[make_pair(u,v)])continue;
    mp[make_pair(u,v)]=true;
    d[v]++,g[u].emplace_back(v); // 建图
  }
  queue<int> s;
  for(int i=1;i<=n;i++)if(!d[i])s.emplace(i);
  while(!s.empty()){
    if(s.size()>1){cout<<"No\n"; return 0;} // 有多解
    int t=s.front(); s.pop(); a.emplace_back(t);
    for(int i:g[t])if(!--d[i])s.emplace(i);
  }
  cout<<"Yes\n";
  for(int i=0;i<n;i++)b[a[i]]=i+1; // 根据顺序确定排列
  for(int i=1;i<=n;i++)cout<<b[i]<<' ';
  cout<<endl;
  return 0;
}
```

---

## 作者：zajasi (赞：2)

## 解题思路
我是用 dfs 求结束时间算拓扑。有一种玄学的方法。

求两次拓扑排序。一次从头往尾扫，一次从尾往头扫。然后看想不想等。无解的情况就是 $a$ 到 $b$ 有一条边，但是 $a$ 的结束时间比 $b$ 早，也就有环了无解。

具体请看代码
## AC 代码
```cpp
/*
written by : zjs123
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long  
int n,m;
int x,y;
vector<int> g[200010];
int st[200020];
int en[200020];
int st2[200020];
int en2[200020];
int z[200020];
int z2[200020];
pair<int,int> a[200020],a2[200020];
int t,t2;
void dfs(int x){
    st[x]=++t;
    for(int i=0;i<g[x].size();i++){
        if(!st[g[x][i]])dfs(g[x][i]);
    }
    en[x]=++t;
}
void dfs2(int x){
    st2[x]=++t2;
    for(int i=g[x].size()-1;i>=0;i--){
        if(!st2[g[x][i]])dfs2(g[x][i]);
    }
    en2[x]=++t2;
}
main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>x>>y;
        g[x].push_back(y);
    }
    for(int i=1;i<=n;i++){
        if(!st[i])dfs(i);
    }
    for(int i=n;i>=1;i--){
        if(!st2[i])dfs2(i);
    }//找两个排列
    for(int i=1;i<=n;i++){
        for(int j=0;j<g[i].size();j++){
            if(en[i]<en[g[i][j]]){
                cout<<"No";
                return 0;
            }
        }
    }//无解
    for(int i=1;i<=n;i++){
        a2[i]=make_pair(en2[i],i);
    }
    sort(a2+1,a2+n+1);
    for(int i=1;i<=n;i++){
        z2[a2[i].second]=n-i+1;
    }
    for(int i=1;i<=n;i++){
        a[i]=make_pair(en[i],i);
    }
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++){
        z[a[i].second]=n-i+1;
    }
    for(int i=1;i<=n;i++){
//        cout<<z[i]<<" "<<z2[i]<<"\n";
        if(z[i]!=z2[i]){
            cout<<"No";
            return 0;
        }//序列不一样：有多解
    }
    cout<<"Yes\n";
    for(int i=1;i<=n;i++){
        cout<<z[i]<<" ";
    }
    return 0;
}

```

---

## 作者：Neil_Qian (赞：2)

# [ABC291E] Find Permutation 题解

## 题意

有一个 $1$ 到 $n$ 的排列 $a_1,a_2,\dots,a_n$。有 $m$ 对大小关系，每次给定两个整数 $x,y$，要求 $x<y$。请问这个排列是唯一。保证有解。


## 标签

拓扑排序。默认您已经会了。

## 解决方案

首先想到一下性质（很简单）：
- 如果 $x<y,y<z$，则 $x<z$。
- 如果 $x<y,y<z,z<x$，则不符合题意。

这引导我们把它建成一个有向图，而根据上面的性质，它应该是无环的。所以这是一个有向无环图，会不会是拓扑排序呢？考虑一下吧。

在拓扑排序中，如何判断是否有唯一解？先建图，然后看入度为零的结点，只能有一个，否则将无法确定哪个是最小的，因为都满足条件。然后，按照拓扑排序的流程，一个结点的所有邻居的入度都减一了以后只能有一个入度为零，否则也无法确定谁更小，因为都满足条件。最后，有可能不连通，特判是否所有结点都入过队列即可。

综上，本题完结，时间复杂度同拓扑排序，$O(n+m)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;const int N=2e5+2;
int n,m,x,y,d[N],cnt,a[N],w;vector<int> v[N];queue<int> q;
int main(){
	scanf("%d%d",&n,&m);
	while(m--)scanf("%d%d",&x,&y),v[x].push_back(y),d[y]++;//建图&入度
	for(int i=1;i<=n;i++)if(!d[i])q.push(i);
	if(q.size()!=1)printf("No\n"),exit(0);//无解1
	while(!q.empty()){//拓扑排序模板
		x=q.front(),q.pop(),a[x]=++cnt,w=0;
		for(int t:v[x]){
			d[t]--;
			if(!d[t])q.push(t),w++;
			if(w>=2)printf("No\n"),exit(0);//无解2
		}
	}
	if(cnt!=n)printf("No\n"),exit(0);//无解3
	printf("Yes\n");//有解
	for(int i=1;i<=n;i++)printf("%d ",a[i]);
	return printf("\n"),0;
}
```

---

## 作者：WilliamFranklin (赞：2)

### 主要思路

相信不少人上来就想到了差分约束吧！ ~~（就像我~~

但是，你怎么也没想到，这就是一道简单的拓扑排序板子题！！！

好，不多说废话，开讲！

就像差分约束一样，我们可以将这个问题转化成一个图论问题。

我们将 $X_i$ 点与 $Y_i$ 点之间连一条有向边，表示 $A_{X_i}$ 小于 $A_{Y_i}$。

然后我们就会发现：只有求出来这个图的传递闭包后，这个图无环，只有一个终点并且每一个点的入度互不相同（这里只有一个起点已经包含在每一个点的入度互不相同里面了），那么这个序列 $A$ 才是独一无二的。

可能有些人不会证明，我们在这里举几个反例就好了。

这个是证明有多个终点的不可以，原因就是这个 $A_3$ 与 $A_4$ 都可以选 $3$ 或 $4$ 中的其中一个。

![](https://cdn.luogu.com.cn/upload/image_hosting/m3xfw3xq.png)

这个是证明有相同入度的点不可以，原因也是这个 $A_3$ 与 $A_4$ 都可以选 $3$ 或 $4$ 中的其中一个。

![](https://cdn.luogu.com.cn/upload/image_hosting/9447y7f4.png)

好，那么证明完后，我们就可以用拓扑排序解决了。

当然，有人可能会问：这个判环怎么办？

直接由拓扑排序不就可以解决吗？

好，上代码。

### AC Code

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <string>
#include <cmath>
#include <map> 
#include <vector>
#include <queue>

using namespace std;

const int N = 2e5 + 5;

map<pair<int, int>, bool> mp;
vector<int> G[N];
int in[N], out[N];
int ans[N];
int ans1[N];
int idx;
bool vis[N];

bool dfs(int x, int fa) {
	vis[x] = 1;
	for (int i = 0; i < G[x].size(); i++) {
		if (G[x][i] != fa) {
			if (vis[G[x][i]] == 1) {
				return 0;
			}
			
			if (!dfs(G[x][i], x)) {
				return 0;
			}
		}
	}
	
	vis[x] = 0;
	
	return 1;
}

queue<int> q;

void bfs(int s) {
	q.push(s);
	
	while (q.size()) {
		int t = q.front();
		q.pop();
		
		for (int i = 0; i < G[t].size(); i++) {
			int j = G[t][i];
			
			ans[j] = max(ans[j], ans[t] + 1);
			in[j]--;
			
			if (!in[j]) {
				q.push(j);
			}
		}
	}
}

int main() {
	int n, m;
	
	cin >> n >> m;
	
	for (int i = 1; i <= m; i++) {
		int u, v;
		
		cin >> u >> v;
		
		if (mp[make_pair(u, v)] == 0) {
			mp[make_pair(u, v)] = 1;
			
			G[u].push_back(v);
			
			in[v]++;
			out[u]++;
		}
	}
	
	bool f = 0;
	int cnti = 0, cnto = 0;
	int w = 0;
	for (int i = 1; i <= n; i++) {
		if (in[i] == 0) {
			cnti++;
			w = i;
		}
		
		if (out[i] == 0) {
			cnto++;
		}
	}
	
	if (cnti == 1 && cnto == 1) {
		bfs(w);
		
		for (int i = 1; i <= n; i++) {
			ans1[i] = ans[i];
		}
		
		sort(ans1 + 1, ans1 + n + 1);
		
		ans1[0] = -1;
		
		for (int i = 1; i <= n; i++) {
			if (ans1[i] == ans1[i - 1]) {
				cout << "No" << endl;
				return 0;
			}
		}
		
		cout << "Yes" << endl;
		for (int i = 1; i <= n; i++) {
			printf("%d ", ans[i] + 1);
		}
		
		return 0;
	}
	
	cout << "No";
	
	return 0;
} 
```


---

## 作者：bigclever (赞：1)

## 题意：
给定 $m$ 组关系 $A_{X_i} \lt A_{Y_i}$，求满足所有条件的**唯一排列** $A$。
## 思路：
对于每一组关系 $A_{X_i} \lt A_{Y_i}$，考虑建一条从 $X_i$ 到 $Y_i$ 的有向边。最后将该图进行拓扑排序，如果排完序是**一条长度为 $n$ 的链**，即所有点的位置是唯一的，则该排列唯一，否则不唯一。

但还有一种情况也是不行的，那就是一开始**入度为 $0$ 的点不止一个**。因为如果这样的话，则第一个位置有多种选择，那排列也不唯一。
## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,head[200005],cnt,in[200005],ans[200005];
struct zqs{int to,nxt;} edge[200005];
void add(int u,int v){edge[++cnt]={v,head[u]};head[u]=cnt;}
struct EZ{int id,dst;};
bool tuopu(){
	queue<EZ> q;
	for(int i=1;i<=n;i++)
		if(in[i]==0)q.push({i,1});
	if(q.size()!=1)puts("No"),exit(0);//入度为0的点不止一个，那么直接输出
	while(!q.empty()){
		EZ t=q.front(); q.pop(); 
		ans[t.id]=t.dst;//记录每个位置的数
		if(t.dst==n)return true;//如果填到n了就说明该排列唯一
		for(int i=head[t.id];i;i=edge[i].nxt){
			int v=edge[i].to;
			if(--in[v]==0)q.push({v,t.dst+1});//拓展新节点
		}
	}
	return false;
}
int main(){
	cin>>n>>m;
	while(m--){
		int x,y; cin>>x>>y;
		in[y]++,add(x,y);//建边
	}
	if(tuopu()){
		puts("Yes");
		for(int i=1;i<=n;i++)cout<<ans[i]<<' ';
	}
	else puts("No");
	return 0;
}
```

---

## 作者：liujy_ (赞：1)

 一开始没有什么特别具体的思路，然后我们根据直觉来尝试一下。   
 先不考虑多解如何判断多解，题目保证一定有解，我们来思考一下如何构造一组合法的解。   
 根据经验我们尝试把问题转化为图论，把关系转化为连边。对于一组关系 $ (X_i,Y_i) $，我们让 $X_i$ 向 $Y_I$ 连一条有向边，然后发现这样是可以做的。由于一定有解所以这张图是有向无环图。这张图任何一个合法的拓扑序都是合法的解。   
 考虑在什么情况下会多解。假设在一轮中，队列里有多个数，我们发现这些数互相之间没有关系也就是对答案没有约束。在这种情况下队列中的数调换顺序最后的答案都是合法的，也就是说这种情况会有多解。   
 总结一下，把每一组关系对应到图上的一条有向边，然后跑拓扑排序，任何时候如果队列中的数超过一个说明有多解。  
 代码如下。   
 ```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<map>
using namespace std;
const int N=2e5+5;
int n,m,a[N],in[N];bool vis[N];
int head[N],cnt;struct node{int to,nxt;}e[N<<1];
void add(int u,int v){e[++cnt]=((node){v,head[u]});head[u]=cnt;} 
map<pair<int,int>,bool> mp;queue<int> q;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,x,y;i<=m;i++){
		scanf("%d%d",&x,&y);
		if(mp[make_pair(x,y)])continue ;
		mp[make_pair(x,y)]=1;
		in[y]++;add(x,y);
	}bool flag=1;cnt=0;
	for(int i=1;i<=n;i++)if(!in[i])q.push(i);
	while(!q.empty()){
		if(q.size()>1){flag=0;break ;}
		int u=q.front();q.pop();a[u]=++cnt;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			in[v]--;
			if(!in[v])q.push(v);
		}
	}
	if(flag){
		printf("Yes\n");
		for(int i=1;i<=n;i++)printf("%d ",a[i]);
	}else printf("No\n");
	return 0;
}

```


---

## 作者：ImposterAnYu (赞：0)

题目保证一定存在符合要求的排列（说明/提示里面有），说明这些条件一定不矛盾。如果我们把每个条件看成一条有向边的话（如果 $A_x < A_y$，则从 $x$ 到 $y$ 连一条有向边），那么很容易得出结论：这是一个有向无环图。

为什么无环呢？

首先我们看在什么情况下这个图有环。假设现在有一个环：$x$ 到 $y$ 有一条边，$y$ 到 $z$ 有一条边，$z$ 到 $x$ 也有一条边，那么显然有 $A_x < A_y,A_y < A_z,A_z < A_x$。但是在 $A_x < A_y,A_y < A_z$ 的时候，必然有 $A_x < A_z$。所以~~就算你拿屁股想一想也知道~~这个图是不可能有环的。

于是，我们现在的任务，就成了在这个有向无环图里找一条有 $n$ 个顶点的链。因为只有找到了这个链，$A$ 排列里每个数的值才是可以确定的。

咋找？拓扑排序呗。拓扑排序不也是在有向无环图中确定每个点（元素）的顺序吗？

~~默认大家都会，不会的请移步[拓扑排序模板题](https://www.luogu.com.cn/problem/B3644)。~~

最后一个问题：如何判断多解？

首先，我们已经知道这是个有向无环图，所以如果可以从 $a$ 走到 $b$，从 $b$ 走到 $c$，从 $c$ 走到 $d$，那么必然不可以从 $a$ 走到 $c$，从 $c$ 走到 $b$，再从 $b$ 走到 $d$。也就是说，在这条链存在的前提下，这条链经过的结点的顺序是固定的！就算走过的边可能不是同一条（因为数据可以有重边），但经过的点的顺序依旧不变。

综上所述，我们可以直接建图，然后跑拓扑排序，如果能找到有 $n$ 个顶点的链就输出 `Yes`，不能就输出 `No`。非常简单。

```cpp
#include<bits/stdc++.h>
#define N 200000
#define M 200000 
#define int1 int
using namespace std;
int1 n,m,i,j,bs,st = 1,x,y,ta[N + 5],pre[M + 5],to[M + 5],num[N + 5],ru[N + 5],p,d,r;//（邻接表存图）num用于记录答案，ru用于记录每个点的入度。 
queue<pair<int1,int1> > q;
void C(){//关同步。 
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	return ;
}
void add_edge(int1 x,int1 y){//加边 
	pre[++bs] = ta[x],ta[x] = bs,to[bs] = y,ru[y]++;
	return ;
}
int main(){
	C();
	cin >> n >> m; 
	for(i = 1; i <= m; i++){
		cin >> x >> y;
		add_edge(x,y);
	}
	while(ru[st] && st < n){//找拓扑排序的起点。 
		st++;
	}
	q.push(make_pair(st,1));
	while(!q.empty()){//BFS（划掉）拓扑排序。 
		p = q.front().first,d = q.front().second;
		q.pop();
		num[p] = d;
		if(d == n){//搜到答案直接输出，反正答案就一种。 
			cout<< "Yes" << endl;
			for(i = 1; i <= n; i++){
				cout<< num[i] << " " ; 
			}
			return 0;
		}
		for(i = ta[p]; i; i = pre[i]){//删与其相关联的边。 
			r = to[i];
			ru[r]--;
			if(!ru[r]){
				q.push(make_pair(r,d + 1));
			}
		}
	}
	cout<< "No" << endl;//多解 
	return 0;
}
```

---

## 作者：SilverLi (赞：0)

[Find Permutation の 传送门](https://www.luogu.com.cn/problem/AT_abc291_e)

题目给定关系 $a_{x_i}<a_{y_i}$，所以考虑从 $x_i$ 到 $y_i$ 连一条有向边，表示 $x_i$ 位置上的数小于 $y_i$ 上的数。

然后这个问题就变成了给定一张 DAG，求是否存在一条长度为 $N$ 的链。

考虑拓扑排序，如果拓扑序列深度为 $N$，就有唯一解。

反之，就没有唯一解。

```cpp
#include <bits/stdc++.h>
#include <bits/stdc++.h>
using namespace std;
#pragma GCC target("avx2")
#define pi pair<int,int>
#define mk make_pair
#define v first
#define d second
const int N=2e5+5;
int n,m,h,x,t[N];
int vis[N],in[N];
vector<int> g[N];
inline int read() {int t;cin>>t;return t;}
inline bool topo() {
	queue<pi> q;
	q.push(mk(h,1));
	while(!q.empty()) {
		int v=q.front().v,d=q.front().d;q.pop();
		t[v]=d;
		if(d==n)	return 1;
		if(vis[v])	continue;
		vis[v]=1;
		for(auto i:g[v])
			if(--in[i]==0)	q.push(mk(i,d+1));
	}
	return 0;
}
signed main() {
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	while(m--) {
		int x,y;cin>>x>>y;
		g[x].push_back(y);
		++in[y];
	}
	for(int i=1;i<=n;++i)
		if(!in[i]) {
			if(++x>1) {cout<<"No";	return 0;}
			h=i;	}
	if(x==0)  {cout<<"No";	return 0;}
	if(topo()) {
		cout<<"Yes\n"<<t[1];
		for(int i=2;i<=n;++i)	cout<<' '<<t[i];
	}
	else	cout<<"No";
	return 0;
}
```

### 后记

AtCoder 的判断实在是太毒瘤，多一个换行和空格都算错。

---

## 作者：_JellyFish_ (赞：0)

# 1.题意
给出一个长为 $n$ 的序列和 $m$ 对大小关系，问是否能唯一确定此序列，如果确定还要输出序列。

# 2.分析
如果我们将每个关系看成一条有向边，不难发现，满足条件的序列一定是一个有向无环图，且该图只有一个无入度的点和无出度的点。即对于一个能确定的序列，从原点（指唯一的入度为 $0$ 的点）开始，遍历它所能到达的点并将它们的入度减一，遍历结束后必定会有且只有一个点的入度变为 $0$。所以这道题就很简单了：先跑一遍判断这是否是一个能确定的序列，然后再从原点跑一遍搜索，到达每个点的顺序就是该点的大小。在这里，正向建边与反向建边的效果是一样的。

# 3.代码
```cpp
#include<iostream>
#define N 1000005
using namespace std;
struct Node{
	int x,y;
}a[N];
int n,m,in[N],head[N],to[N],Next[N],nedge,vis[N],out[N],ans[N],maxx;
void add(int a,int b){
	Next[++nedge]=head[a];
	head[a]=nedge;
	to[nedge]=b;
} 
void dfs(int u){
	if(vis[u]){
		puts("No");
		exit(0);
	}
	vis[u]=1;
	int T=-1;
	for(int i=head[u];i;i=Next[i]){
		int V=to[i];
		in[V]--;
		if(T!=-1&&in[V]==0){
			puts("No");
			exit(0);
		}
		if(in[V]==0)T=V;
	}
	if(T==-1&&out[u]!=0){
		puts("No");
		exit(0);
	}
	if(T!=-1)dfs(T);
}
void dfs2(int u){
	ans[u]=maxx;
	maxx--;
	vis[u]=1;
	int T=-1;
	for(int i=head[u];i;i=Next[i]){
		int V=to[i];
		in[V]--;
		if(in[V]==0)T=V;
	}
	if(T!=-1)dfs2(T);
}
signed main(){
	cin>>n>>m;
	maxx=n;
	for(int i=1;i<=m;i++)cin>>a[i].x>>a[i].y,in[a[i].x]++,out[a[i].y]++,add(a[i].y,a[i].x);
	int flag=1;
	for(int i=1;i<=n;i++){
		if(flag==0&&out[i]==0)return cout<<"No",0;
		if(out[i]==0)flag=0;
	}
	flag=1;
	for(int i=1;i<=n;i++){
		if(flag==0&&out[i]==0)return cout<<"No",0;
		if(out[i]==0)flag=0;
	}
	for(int i=1;i<=n;i++)if(in[i]==0){
		dfs(i);
		break;
	}
	puts("Yes");
	for(int i=1;i<=n;i++)vis[i]=0;
	for(int i=1;i<=m;i++)in[a[i].x]++,out[a[i].y]++;
	for(int i=1;i<=n;i++)if(in[i]==0){
		dfs2(i);
		break;
	}

	for(int i=1;i<=n;i++)cout<<ans[i]<<' ';
	return 0;
}
```


---

## 作者：Escapism (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc291_e)

[洛谷上一道极其近似的题目](https://www.luogu.com.cn/problem/P1347)

# 题意

有一个 $n$ 个数的排列，里面的每个数都是 $1$ 到 $n$ 的正整数。现在知道这个排列中的 $m$ 条大小关系，每条关系表示第 $i$ 个数比第 $j$ 个数小。

现在问能否通过这些关系确定这个排列。

# 思路

根据给定的关系，我们可以建立一张大小关系图，即如果 $i$ 位置比 $j$ 位置小，那么 $i$ 号节点就向 $j$ 号点连一条有向边。

如果能确定这个排列，那么这张图应该是一个**有向无环图**，即不存在 $i,j,k$ 三个位置有 $i<j,j<k,k<i$ 等诸如此类的矛盾情况。

我们可以通过**拓扑排序**，来找出一条有效的排列。如果找不出，就是出现了矛盾，输出 ``No``；如果找出了多条有效的序列，就是序列不唯一无法确定，也输出 ``No``。

如果**有且仅有一条有效序列**，输出 ``Yes``。

---
### 拓扑排序是什么？

拓扑排序是一种在有向无环图上将图中的顶点以线性方式进行排序，使得对于任何的顶点 $u$ 到 $v$ 的有向边 $(u,v)$，都可以有 $u$ 在 $v$ 的前面。

具体方法是从入度为 $0$ 的点开始跑广搜（因为这种点的优先级最高，没有前置点），每跑过一条边就把点的入度减一，然后再次从入度为 $0$ 的点进行枚举。

在本题中，如果出现了**两个及以上的入度为 $0$ 的点都是无法确定序列的**，因为有两个地方是没有条件限制的。

---

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 2e5+10;
vector<int> G[MAXN];
int into[MAXN],ans[MAXN];
int n,m,cnt;
bool vis[MAXN];

struct node{
	int x,dep;
};
bool bfs(){//广搜式拓扑
	queue<node> Q;
	Q.push({cnt,1});
	while(!Q.empty()){
		int x = Q.front().x,D = Q.front().dep;
        ans[x] = D;
		if(D == n) return true;
		Q.pop();
		if(vis[x]) continue;
		vis[x] = true;
		for(int i = 0;i < G[x].size();i++){
			into[G[x][i]]--; //减入度
			if(!into[G[x][i]]) Q.push({G[x][i],D + 1});
		}
	}return false;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= m;i++){
		int x,y;
        scanf("%d%d",&x,&y);
		G[x].push_back(y);
		into[y]++; //记录每个点的入度
	}
	int num = 0;
	for(int i = 1;i <= n;i++){
		if(!into[i]) cnt = i,num++; //记录起始点和入度为 0 的点的个数
    }
	if(num != 1){
        puts("No"); //如果有不止一个起点，直接输出 No
        return 0;
    }
	if(bfs()){ //能找出有且仅有一条的合法序列
		puts("Yes");
		for(int i = 1;i <= n;i++) printf("%d ",ans[i]); //输出
	}
    else puts("No"); //出现了矛盾
	return 0; 
}

```

[通过记录](https://www.luogu.com.cn/record/103274299)

---

## 作者：YBaggio (赞：0)

 # 题意
 有一个长度为 $N$ 的排列 $A_1 \dots A_N$，然后给出 $M$ 对大小关系：输入 $i,j$ 表示 $A_i<A_j$。问 $A$ 是否只有一种可能，若是，输出`Yes`然后输出 $A$，如果不是输出`No`。
 # 题解
 如果要 $A$ 只要一种可能，则必须要求每两个数的大小关系都确定，因此我们对每一对输入的 $(i,j)$ 建边 $i \to j$，然后跑拓扑排序，如果有环（大小关系矛盾）或者队列里同时有两个数（这两个数可以调换位置）则输出`No`，否则按照拓扑排序的序列得出答案。
 ```cpp
 #include<map>
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
const int maxn=200010;
int n,m,tot,tp[maxn],rd[maxn],a[maxn];
map<pair<int,int>,bool>p;
queue<int>q;
vector<int>g[maxn];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int x,y;cin>>x>>y;
        if(p.find({x,y})!=p.end())continue;
        g[x].push_back(y);
        rd[y]++;
        p[{x,y}]=true;
    }
    for(int i=1;i<=n;i++){
        if(!rd[i])q.push(i);
    }
    while(!q.empty()){
        if(q.size()>1){
            cout<<"No";
            return 0;
        }
        int x=q.front();q.pop();
        tp[++tot]=x;
        for(int y:g[x]){
            rd[y]--;
            if(!rd[y])q.push(y);
        }
    }
    if(tot!=n){
        cout<<"No";
        return 0;
    }
    for(int i=1;i<=n;i++)a[tp[i]]=i;
    cout<<"Yes\n";
    for(int i=1;i<=n;i++)cout<<a[i]<<' ';
    return 0;
}
 ```

---

