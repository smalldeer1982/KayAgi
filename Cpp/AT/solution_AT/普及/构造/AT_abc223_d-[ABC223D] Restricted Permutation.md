# [ABC223D] Restricted Permutation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc223/tasks/abc223_d

$ (1,\ 2,\ \dots,\ N) $ を並び替えて得られる数列 $ P $ であって以下の条件を満たすもののうち、辞書順で最小のものを求めてください。

- $ i\ =\ 1,\ \dots,\ M $ に対し、$ P $ において $ A_i $ は $ B_i $ よりも先に現れる。

ただし、そのような $ P $ が存在しない場合は `-1` と出力してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i,\ B_i\ \leq\ N $
- $ A_i\ \neq\ B_i $
- 入力は全て整数である。

### Sample Explanation 1

条件を満たす $ P $ は $ (2,\ 1,\ 3,\ 4),\ (2,\ 3,\ 1,\ 4),\ (2,\ 3,\ 4,\ 1),\ (3,\ 2,\ 1,\ 4),\ (3,\ 2,\ 4,\ 1) $ の $ 5 $ つです。これらのうち辞書順で最小のものは $ (2,\ 1,\ 3,\ 4) $ です。

### Sample Explanation 2

条件を満たす $ P $ は存在しません。

## 样例 #1

### 输入

```
4 3
2 1
3 4
2 4```

### 输出

```
2 1 3 4```

## 样例 #2

### 输入

```
2 3
1 2
1 2
2 1```

### 输出

```
-1```

# 题解

## 作者：Wi_Fi (赞：2)

题目中说的“$P$ 中的 $A_i$ 要出现在 $B_i$ 之前”，可以理解为“有一条从从 $A_i$ 到 $B_i$ 的有向边”，然后剩下的内容就是要求拓扑排序。

由于题目中说“字典序最小”，所以我们只需要把普通拓扑中的 ```queue``` 改为 ```priority_queue``` 即可。

代码：
```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;
vector<int>g[N],ans;
priority_queue<int,vector<int>,greater<int>>q;
int sum[N],cnt,n,m,x,y,i;
bool kahn()
{
	for(int i=1;i<=n;i++)if(!sum[i])q.push(i);
	while(!q.empty())
	{
		int u=q.top();
		q.pop(),cnt++,ans.push_back(u);
		for(int i=g[u].size()-1;i>=0;i--)
		{
			int v=g[u][i];
			sum[v]--;
			if(!sum[v])q.push(v);
		}
	}
	return cnt==n;
}
int main()
{
	cin>>n>>m;
	while(m--)
	{
		cin>>x>>y;
		g[x].push_back(y),sum[y]++;
	}
	if(!kahn())cout<<"-1";
	else
	{
		for(i=0;i<ans.size();i++)cout<<ans[i]<<' ';
	}
	return 0;
}
```


---

## 作者：___w (赞：2)

### [[ABC223D] Restricted Permutation](https://www.luogu.com.cn/problem/AT_abc223_d)
#### 题意简述
- 求一个图的拓扑序
- 小的编号在前

#### 题目分析
这一题是拓扑排序板子题，需要用优先队列来解决字典序的问题，具体做法是重载小于号，变成大于号。因为 STL 的 ```priority_queue``` 是大根堆，而我们需要的是小根堆。重载完之后我们就可以套用拓扑排序模板了，具体看代码。

#### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+5, M = 4e5+5;
struct edge {
	int to, next;
} e[M];
struct node {
	int num;
} ;
int n, m, tot, cnt, a[N], in[N], head[N];
void add(int x, int y) {
	e[++tot] = (edge){y, head[x]};
	head[x] = tot;
}
bool operator < (node x, node y) {//重载小根堆 
	return x.num > y.num;
}
void topsort() {
	priority_queue <node> q;//优先队列 
	for (int i = 1; i <= n; ++i) if (!in[i]) q.push((node){i});
	while (!q.empty()) {
		int x = q.top().num; q.pop();
		a[++cnt] = x;
		for (int i = head[x]; i; i = e[i].next) {
			int y = e[i].to;
			if (--in[y] == 0) q.push((node){y});
		}
	}
}
int main() {
	cin >> n >> m;
	int u, v;
	while (m--) {
		cin >> u >> v;
		add(u, v), ++in[v];
	}
	topsort();
	if (cnt < n) cout << -1;
	else for (int i = 1; i <= n; ++i) cout << a[i] << ' ';
	return 0;
}
```

---

## 作者：ZnHF (赞：2)

[题目链接](https://www.luogu.com.cn/problem/AT_abc223_d)

~~借助百度翻译~~可以很容易地看出这是一道拓扑排序模板题。

## 什么是拓扑排序
给定一张有向无环图，若一个由图中**所有的点**构成的序列 $L$ 满足：对于图中的每一条边 $(x,y)$，$x$ 在 $L$ 中都出现在 $y$ 之前，则称序列 $L$ 是这张有向无环图的一个拓扑序，解序列 $L$ 的过程就称为拓扑排序。 

## 如何进行拓扑排序
不断选择图中入度为 $0$ 的点 $x$，把 $x$ 连向的点的入度减去 $1$。

题目要求答案的字典序最小，我们可以使用优先队列来解决这个要求。

具体实现看代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int ver[200001],net[200001],head[200001],deg[200001],tot;
//deg[]为每个节点的入度
int n,m;
struct node{
	int num;
};
bool operator < (node x,node y){
	return x.num>y.num;
}//priority_queue默认是大根堆，需要重载小于号来实现小根堆
priority_queue<node> q;
vector<int> v;
void add(int x,int y){
	ver[++tot]=y;
	net[tot]=head[x];
	head[x]=tot;
	deg[y]++;//预处理该节点的入度
}
int main(){
	cin>>n>>m;
	for(int i=0;i<m;i++){
		int t1,t2;
		cin>>t1>>t2;
		add(t1,t2);
	}
	for(int i=1;i<=n;i++) if(!deg[i]) q.push((node){i});//将每个入度为0的节点入队
	while(!q.empty()){
		node temp=q.top();
		q.pop();
		v.push_back(temp.num);
		for(int i=head[temp.num];i;i=net[i]){
			int nn=ver[i];
			if(--deg[nn]==0) q.push((node){nn});//若该节点的入度被减为零则入队
		}
	}
	if(v.size()!=n){//判断是否有解;
		puts("-1");
		return 0;
	}
	for(int i=0;i<v.size();i++) cout<<v[i]<<" " ;
	cout<<endl;//AT题库记得换行
	return 0;
}
```


---

## 作者：_zzzzzzy_ (赞：1)

# 思路
这题根据题意我们显然能看出每一次约束是先选 $u$ 才能选 $v$，根据这个条件可以想到用拓扑排序来做。

接下来我们看看怎么保证字典序最小，如果我们每一选点的时候可以在点的队列里面选最小的一个，可以直接把队列换成优先队列。

当我们的约束条件出现环时就是无解的时候，就可以输出 $-1$ 了。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=200050;
vector<int>e[maxn];
int in[maxn];
signed main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		e[u].push_back(v);
		in[v]++;
	}
	priority_queue<int,vector<int>,greater<int>>Q;
	for(int i=1;i<=n;i++){
		if(in[i]==0){
			Q.push(i);
		}
	}
	vector<int>ans;
	while(Q.size()){
		int u=Q.top();
		Q.pop();
		ans.push_back(u);
		for(int v:e[u]){
			in[v]--;
			if(in[v]==0){
				Q.push(v);
			}
		}
	}
	if(ans.size()!=n)cout<<-1;
	else for(int x:ans)cout<<x<<" ";
	return 0;
}
```

---

## 作者：expecto__patronum (赞：0)

## 题意：
给出 $m$ 组限制条件，要求构造一个长度为 $n$ 的字典序最小的序列。每组 $a$，$b$ 表示在序列里 $a$ 在 $b$ 前面。
## 思路：
建图：$a$ 到 $b$ 有向边，跑一个拓扑排序，将队列换为优先队列，表示每次将最小的弹出，就能保证字典序最小了。
## 代码：
```
// Problem: D - Restricted Permutation
// Contest: AtCoder - AtCoder Beginner Contest 223
// URL: https://atcoder.jp/contests/abc223/tasks/abc223_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<iostream>
#include<cstdio> 
#include<string>
#include<ctime>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<stack>
#include<queue>
#include<map>
#include<set>
#include<sstream>
using namespace std;

typedef long long ll;

const int maxn=2e5+100;

int n,m,din[maxn];
vector<int>g[maxn],ans;
priority_queue<int,vector<int>,greater<int> >q;
int main() {
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
		din[v]++;
	}
	for(int i=1;i<=n;i++)
		if(!din[i]){
			q.push(i);
		}
	while(!q.empty()){
		int t=q.top();q.pop();
		ans.push_back(t);
		for(auto tt:g[t]){
			if(--din[tt]==0) q.push(tt);
		}
	}
	bool flag=0;
	for(int i=1;i<=n;i++)
		if(din[i]>0) flag=1;
	if(flag){
		puts("-1");return 0;
	}
	for(auto it:ans) cout<<it<<" ";
	
	
	
	
	
	

	return 0;
}

```
[博客](https://blog.csdn.net/weixin_45675097/article/details/120834713)


---

## 作者：awesomegordon (赞：0)



### 题目大意

输入一个 $n$ 点 $m$ 边的无向图，求该图**字典序最小**的**拓扑序**。

### 题目思路

经典的拓扑排序题，只不过要输出字典序最小的。

首先，您应该了解什么是[拓扑排序](https://blog.csdn.net/weixin_43004044/article/details/128690277)。然后，这道题的第一部分就解决了。

第二部分就是去解决**最小字典序**这个问题。

我们考虑使用 `priority_queue` 解决该问题。但是却发现它是大根堆，我们只需要把原先的 `priority_queue<int> ` 改为 `priority_queue<int,vector<int>,greater<int>>` 即可转换为小根堆，此部分就迎刃而解了！

### 代码

别抄。

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<int> v2[1000005];
int ru[1000005];
int arr[1000005];
int main(){
	//by awesomegordon. 
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		v2[u].push_back(v);
		ru[v]++;
	}
	int tmp=0;
	priority_queue<int,vector<int>,greater<int>> q;
	for(int i=1;i<=n;i++){
		if(ru[i]==0){
			q.push(i);
		}
	}
	while(!q.empty()){
		int p=q.top();
		arr[++tmp]=p;
		q.pop();
		for(auto i:v2[p]){
			ru[i]--;
			if(ru[i]==0){
				q.push(i);
			}
		}
	}
	if(tmp==n){
		for(int i=1;i<=tmp;i++){
			printf("%d ",arr[i]);
		}
	}else{
		cout<<"-1";
	}
	return 0;
}
```




---

## 作者：Tang_poetry_syndrome (赞：0)

## [ABC223D] Restricted Permutation 
[洛谷题面](https://www.luogu.com.cn/problem/AT_abc223_d) [atcoder题面](https://atcoder.jp/contests/abc223/tasks/abc223_d)
### 题目大意
给定一个 $n$ 个点，$m$ 条边的无向图，求它字典序最小的拓补序。
### 思路
一眼丁真为拓补排序模板题，仅仅加上字典序的要求。  
很明显看出用 STL 中的 `priority_queue` 来对入度为 $0$ 的节点排序即可。但 `priority_queue` 本身是大根堆，所以我们将它重载为小根堆即可，即 `priority_queue<int,vector<int>,greater<int> >`。  
**注意最好不要将两个小于号相连，否则可能会被误判为右移。**
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,m,a,b,rd[N],cnt,h[N],ans[N];
priority_queue<int,vector<int>,greater<int> >q;
struct tp{
	int a,b,nxt;
}d[N];
void add(int a,int b){d[++cnt].a=a,d[cnt].b=b,d[cnt].nxt=h[a],h[a]=cnt;}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++)
		cin>>a>>b,rd[b]++,add(a,b);
	for(int i=1;i<=n;i++)
		if(!rd[i])q.push(i);
	cnt=0;
	while(!q.empty())
	{
		a=q.top(),q.pop(),ans[++cnt]=a;
		for(int i=h[a];i;i=d[i].nxt)
		{
			b=d[i].b;
			rd[b]--;
			if(!rd[b])q.push(b);
		}
	}
	if(cnt<n)
		cout<<-1;
	else 
		for(int i=1;i<=cnt;i++)
			cout<<ans[i]<<' ';
	return 0;
 }
```
[提交记录](https://atcoder.jp/contests/abc223/submissions/45498218)

---

## 作者：xwh_hh (赞：0)

一道经典的拓扑排序题。  
我们将每一条限制 $(A_i,B_i)$ 看做是图上的一条边 $A_i\to B_i$，这样，本题的结果就变成了这个图的字典序最小的拓扑序，开一个小根堆维护，时间复杂度 $O((N+M)\log N)$。  
代码：  
```cpp
#include<bits/stdc++.h>
using namespace std;
int in[200005];
vector<int>g[200005];
int cnt;
int n,m; 
int ans[200005];
priority_queue<int,vector<int>,greater<int> > pq;
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		g[u].push_back(v);
		in[v]++;
	}
	for(int i=1;i<=n;i++){//入堆 
		if(!in[i]) pq.push(i);
	}
	while(!pq.empty()){
		int u=pq.top(); pq.pop();
		ans[++cnt]=u;//出堆，记录答案 
		for(int i=0;i<g[u].size();i++){
			in[g[u][i]]--;
			if(!in[g[u][i]]) pq.push(g[u][i]);//入堆 
		}
	}
	//可行性判定 
	if(cnt<n) cout<<-1;
	else{
		for(int i=1;i<=n;i++) cout<<ans[i]<<' '; 
	}
	return 0;
}

```

---

## 作者：ruanwentao666 (赞：0)

# AT_abc223_d 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_abc223_d)

## 题目分析
这题看上去花里胡哨，但实际上就是纸老虎，一个拓扑排序就解决了。

实际上就是把输入的数据看成图，求这个图的拓扑排序，最后输出即可。

## 拓扑排序的实现

1. 首先需要一个数组 $r$，来记录每个节点的入度。
2. 循环遍历每个节点，把入度为 $0$ 的节点放入优先队列。
(注意：题目中要求输出字典序最小的答案，所以用优先队列。)
3. 当优先队列不为空时，遍历优先队列，取出队首 $u$。遍历节点 $u$ 可以到达的所有节点，入度减 $1$，判断入度是否为 $0$。若是，放入优先队列；不是，则跳过。
4. 重复步骤 $3$，直到不符合要求结束。

## 代码展示

前言：禁止复制题解，共创和谐洛谷。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,u,v,r[200005];
vector<int>g[200005];
priority_queue<int,vector<int>,greater<int> >q;
vector<int>ans;
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>u>>v;
		g[u].push_back(v);
		r[v]++;
	}
	for(int i=1;i<=n;i++)
		if(!r[i])
			q.push(i);
	while(!q.empty()){
		v=q.top();
		ans.push_back(v);
		q.pop();
		for(int i=0;i<g[v].size();i++){
			u=g[v][i];
			if(r[u]==1){
				q.push(u);
			}
			r[u]--;
		}
	}
	if(ans.size()!=n){
		cout<<"-1\n";
	}else{
		for(int i=0;i<ans.size();i++){
			cout<<ans[i]<<" ";
		}
		cout<<"\n";
	}
	return 0;
}

```


---

## 作者：TLEWA (赞：0)

2023.8.9 upd：重写了题解

考虑将数字间的关系建图，具体的，将每个输入的关系视作 $A_i$ 到 $B_i$ 的一条有向边。可以发现，如果不要求字典序最小，只要求找到可行解，我们直接在图上跑一遍拓扑排序即可（就是纯板子了嘛）。

保证字典序最小的方法有多种，笔者使用了 `priority_queue` 来维护出队的序列，优先队列自动将出队的顺序排序，保证了字典序最小。具体可以看代码，有比较详细的注释。
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m,a,b;

int in[200005],arr[200005],p; //入度，字典序最小的方案 
vector<int> vec[200005]; //图 

bool topsort() {
	priority_queue<int,vector<int>,greater<int> > que; //小根堆 
	for(int i=1;i<=n;++i)
		if(in[i]==0)
			que.push(i);
	int node;
	while(!que.empty()) {
		node=que.top(); //从队列中取出一个点 
		que.pop(); //将其出队 
		arr[p++]=node;
		for(auto i:vec[node]) {
			in[i]--;
			if(in[i]==0) que.push(i); //如果入度为 0 就入队 
		} 
	} 
	if(p==n) return true; //如果可以找到方案就输出 
	else return false; //反之输出 -1 
} 

int main() {
	cin >> n >> m;
	for(int i=1;i<=m;++i) {
		cin >> a >> b;
		vec[a].push_back(b);
		in[b]++;
	}
	
	bool flag=topsort();
	
	if(flag) 
		for(int i=0;i!=p;++i) 
			cout << arr[i] << ' ';
	else cout << -1;
	return 0;
}

```

## （写在最后）priority_queue 的注意事项和变为小根堆方法

注意到 `priority_queue` 默认是大根堆，所以需要额外将其变为小根堆保证字典序最小，默认出队的顺序会使得字典序最大。

当你写下 `priority_queue<int>` 时，它其实默认执行了一部分设置，这种写法与 `priority_queue<int,vector<int>,less<int> >` 等同。作用是把这个优先队列设置成大根堆（从大到小出队），此时你可以写成 `priority_queue<int,vector<int>,greater<int> >`，就可以使元素从小到大出队了。

---

## 作者：loser_seele (赞：0)

经典的依赖性问题，转化为拓扑排序问题。对于一个限制 $ (A,B) $，建有向边 $ (A,B) $。之后使用拓扑排序把所有入度为 $ 0 $ 的点塞入队列，每次删除这些点并且更新与其相连的点的入度，将新的点塞入队列即可。

这样即可判断无解的情况：图中存在环。图中存在环则必定存在某些点从来没入队，于是记录下入队的点的个数即可。

现在遗留了一个问题：构造字典序最小的解。把队列换为优先队列，每次优先取编号最小的点即可。

因为每个点最多入队一次，出队一次，所以时间复杂度为 $ \mathcal{O}(n\log{n}) $，因为要使用优先队列。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
const int maxn=2e6+10;
vector<int>out[maxn];
int in[maxn];
int main()
{
    int n,m; 
    cin >> n >> m;
    while(m--)
    {
        int u,v;
    	cin>>u>>v;
    	out[u].push_back(v);
    	++in[v];
    }
    priority_queue<int,vector<int>,greater<int> >que;
    for(int i=1;i<=n;i++)
    if(!in[i])
    que.push(i);
    vector<int>res; 
    res.reserve(n);
    while(!que.empty())
    {
    	int node=que.top();
    	que.pop(); 
        res.push_back(node);
    	for (auto x:out[node])
    	{
    		--in[x];
    		if(!in[x])
    		que.push(x);
    	}
    }
    if(res.size()!=n)
    cout<<-1;
    else 
    for(auto x:res)
    cout<<x<<' ';
}
```


---

