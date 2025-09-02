# [ABC146D] Coloring Edges on Tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc146/tasks/abc146_d

$ N $ 頂点の木 $ G $ が与えられます。 頂点には $ 1 $ から $ N $ までの番号がついており、$ i $ 本目の辺は頂点 $ a_i $ と頂点 $ b_i $ を結んでいます。

$ G $ の辺を何色かで塗り分けることを考えます。 このとき、各頂点について、その頂点を端点に持つ辺の色がすべて相異なるようにしたいです。

上記の条件を満たす塗り分けの中で、使用する色の数が最小であるようなものを $ 1 $ つ構築してください。

## 说明/提示

### 制約

- $ 2\ \le\ N\ \le\ 10^5 $
- $ 1\ \le\ a_i\ \lt\ b_i\ \le\ N $
- 入力はすべて整数
- 与えられるグラフは木である

## 样例 #1

### 输入

```
3
1 2
2 3```

### 输出

```
2
1
2```

## 样例 #2

### 输入

```
8
1 2
2 3
2 4
2 5
4 7
5 6
6 8```

### 输出

```
4
1
2
3
4
1
1
2```

## 样例 #3

### 输入

```
6
1 2
1 3
1 4
1 5
1 6```

### 输出

```
5
1
2
3
4
5```

# 题解

## 作者：liaoxingrui (赞：3)

## Content

给定一棵树，要求每个节点的各个出边的权值互不相同。求至少需要多少种不同的权值，并构造一颗这样的带权树。

## Solution

可以想到最少的不同权值一定为这颗树里一个点出边数量的最大值，构造权值就可以根据那个点来向下一步一步推，注意每个点的各个出边上的权值要各不相同。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,ma,tot;
int x[N],y[N],fa[N],cnt[N],ans[N],head[N];
struct node{
	int x,y;
}nex[N<<1];
void add(int x,int y){
	tot++;
	nex[tot].x=y;
	nex[tot].y=head[x];
	head[x]=tot;
}
void dfs(int node,int last){
	int sum=0;
	for(int i=head[node];i;i=nex[i].y){
		int w=nex[i].x;
		if(w!=fa[node]){
			sum++;
			if(sum==last)
				sum++;
			fa[w]=node;
			ans[w]=sum;
			dfs(w,sum);
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>x[i]>>y[i];
		add(x[i],y[i]);
		add(y[i],x[i]);
		cnt[x[i]]++;
		cnt[y[i]]++;
		if(cnt[ma]<cnt[x[i]])
			ma=x[i];
		if(cnt[ma]<cnt[y[i]])
			ma=y[i];
	}
	cout<<cnt[ma]<<endl;
	dfs(ma,0);
	for(int i=1;i<n;i++)
		if(fa[x[i]]==y[i])
			cout<<ans[x[i]]<<endl;
		else
			cout<<ans[y[i]]<<endl;
	return 0;
}
```

---

## 作者：CD_Sun_doer (赞：3)

### 题目： [[ABC146D] Coloring Edges on Tree](https://www.luogu.com.cn/problem/AT_abc146_d)
---
提供一个很简单的暴力思路（~~虽然跑的不快~~）。

遇见这种题，不要被题目描述中诸如树、带权这种词唬住，仔细理解理解提议，其实发觉题中说这是一棵树反而使题目更简单。

我们需要考虑两个问题：**求至少需要多少种不同的权值** 和 **构造一颗这样的带权树** 建议在演草纸上画一画样例会很清晰，我们以样例二为例，如下图，

![样例二图解](https://cdn.luogu.com.cn/upload/image_hosting/eu50672y.png)

因为这是一棵树，所以每一个节点至多有一个父亲节点，我们记录一下节点 $u$ 的入边的权值为 $w$，然后让此节点 $u$ 与它的 ~~众多~~（也可能没有）出边的边权依次从一开始赋值，如果赋值到 $w$ 那就跳过接着下一个数，由于父亲节点只有一个，所以这一步还是很好处理的。这时用 $ans$ 来比较记录一下最大权值即可。

这里我选择用 bfs 来处理这些节点，存两个值，分别是此节点与它的出边的边权，如果是根节点没有父亲节点，那就存上零。至于要把哪些点塞进 bfs 的队列里，用一个数组记录这个点的入度，如果为零代表其为根节点。

最后要注意的一点，输出要按边的序号来，而不是我们边 bfs 边输出。

到此，已经大功告成了，还有什么不明白的相信一看代码疑问就荡然无存了。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,u[100010],v[100010];
int cnt,ans;
struct node{
	int v,w;
};
vector<node> e[100010];
queue<node> q;
int in[100010];
int main(){
	cin.tie(0),cout.tie(0)->sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>u[i]>>v[i];
		e[u[i]].push_back((node){v[i],0});
		in[v[i]]++;
	}
	for(int i=1;i<=n;i++){
		if(in[i]==0) q.push((node){i,0});
	}
	while(!q.empty()){
		node uu=q.front();
		q.pop();
		int u=uu.v;//u 为此节点
		int ww=uu.w;//ww 为此点的入边的边权
		int cn=0;//cn 为此点出边的边权
		for(int i=0;i<e[u].size();i++){
			if(e[u][i].w==0){
				cn++;
				while(cn==ww) cn++;
				e[u][i].w=cn;//将此出边赋值
				ans=max(ans,cn);
			}
			q.push((node){e[u][i].v,e[u][i].w});
		}
	}
	cout<<ans<<"\n";
  //这一步↓也许有点麻烦，遍历一遍 按输入顺序 输出每个边的权值。
	for(int i=1;i<=n;i++){
		for(auto it:e[u[i]]){
			if(it.v==v[i]){
				cout<<it.w<<"\n";
			}
		}
	}
	return 0;
}
```

---

## 作者：high_sky (赞：2)

### 解法思路
对于一个点，他的所有边颜色都必须不同，那么显然最小颜色数就是所有点中的最大度数。

设 $x$ 为度数最大的点，那么以 $x$ 为树根开始 `dfs`，用递归对边涂色就行了。

涂完色之后，就输出，那涂完色之前呢？

我们还得存一下每个点的度数以及邻接点，构成邻接表，本人用 `vector` 实现。

### Code
本代码有注释，请尽情观看。
```cpp
#include<bits/stdc++.h>
#define int long long
#define PI pair<int,int>
#define IOS std::ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
using namespace std;
const int maxm=1e5+5;
vector<PI>g[maxm];
int used[maxm];
int d[maxm];
int c[maxm];
int n;
void dfs(int x,int pre_id){//pre_id为连接父子点的边
    int col=1;
    for(auto i:g[x]){//进行涂色
        int v=i.first,now_id=i.second;
        if(now_id==pre_id)continue;
        if(col==c[pre_id])col++;//重复颜色就加
        c[now_id]=col++;
        dfs(v,now_id);//递归涂色
    }
}
void solve(){//核心代码
    cin>>n;
    for(int i=1;i<n;i++){//输入
        int a,b;
		cin>>a>>b;
        g[a].push_back({b,i});//邻接表
        g[b].push_back({a,i});
        d[a]++,d[b]++;//度数
    }
    int ma=1;
    for(int i=1;i<=n;i++) if(d[ma]<d[i]) ma=i;//最大度数下标
    cout<<d[ma]<<endl;
    dfs(ma,0);//递归涂色
    for(int i=1;i<n;i++) cout<<c[i]<<endl;//输出
}
signed main(){
	IOS;//加速
    solve();
    return 0;
}

```

---

## 作者：tsh_qwq (赞：0)

### 大致思路：
题目意思简单明了，求出至少需要多少种不同的权值其实就是找出度数最大的节点，可以轻松求出。

本题的难点（其实也不难）在于如何求出方案，此处我们将本体视作一个涂色问题，这一点其他题解讲的已经很明白了，不多做叙述。

这里的方法很多，我使用的是 DFS，从任意节点（我选择 1 号节点）出发，跑一遍 DFS，使一个节点的相邻节点没有相同的颜色即可。

### 代码：
```cpp
#include <bits/stdc++.h>
#pragma GCC optimize("3","Ofast","inline")
#define int long long
#define endl "\n"
using namespace std;
int n,ans=INT_MIN,an[100005],k;
int to[100005],nxt[100005];
int head[100005],a[100005];
void add(int x,int y)
{
	k++;
	to[k]=y;
	nxt[k]=head[x];
	head[x]=k;
	a[x]++,a[y]++;
}
void dfs(int x,int y)
{
	int s=0;
	for(int i=head[x];i;i=nxt[i])
	{
		s++;
		an[i]=s;
		if(s==y)
		{
			s++;
			an[i]=s;
		}
		dfs(to[i],an[i]);
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<n;i++)
	{
		int x,y;
		cin>>x>>y;
		add(x,y);
		ans=max(ans,max(a[x],a[y]));
	}
	cout<<ans<<endl;
	dfs(1,0);
	for(int i=1;i<n;i++)
	{
		cout<<an[i]<<endl;
	}
	return 0;
}
```
码风比较丑陋，将就看吧 qwq。

---

## 作者：Hog_Dawa_IOI (赞：0)

非常贪心地想，除非必要，否则尽量使用之前出现过的权值。     
对于一条从 $u$ 到 $v$ 的边，我们只限制它的权值不同于 $u$ 到 $v$ 的兄弟的边，以及 $fa_u$ 到 $u$ 的边。    
直接遍历这棵树，对于边一一赋值即可。     
这里使用了 BFS，DFS 应当也可以通过。   
```cpp
#include<stdio.h>
struct sss{long long end,next,which;}bian[100005];
long long n,a,b,first[100005],num,ans[100005],s1,s2,queue[100005],from[100005];
int main()
{
	scanf("%lld",&n),queue[++s2]=1;
	for(int i=1;i<n;i++) scanf("%lld%lld",&a,&b),
	bian[++num].end=b,bian[num].which=i,bian[num].next=first[a],first[a]=num;
    //which：第几条边
	while(s1<s2)
	{
		s1++;long long ls=0;
		for(int i=first[queue[s1]];i;i=bian[i].next) 
		{
            //from：从这个点的父亲到它的这条边编号
            //当前遍历到的这条边不能和父亲下来的这条边权值相同
			ls++;if(ls==ans[from[queue[s1]]]) ls++;
			ans[bian[from[bian[i].end]=i].which]=ls,queue[++s2]=bian[i].end;
		}
	}
	for(int i=1;i<n;i++) ans[0]=ans[0]>ans[i]?ans[0]:ans[i];
    //统计权值种类数
	for(int i=0;i<n;i++) printf("%lld\n",ans[i]);
}
```

---

## 作者：I_am_Tangser (赞：0)

## 题目大意

给你一个有 $n$ 个点的树，要求你给每个边都染上一种颜色，一个点所连的边的颜色不能有相同的，求最少的颜色数和每条边的颜色。

## 题目思路

首先可以很明显的看出：最少颜色数一定是连接边数最多的点的边数。然后我们通过 dfs 对树进行染色，我选择使用 `map<pair<int,int>,int>` 来保存每条边的颜色。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,maxn,u[N],v[N];
map<pair<int,int>,int>mp;
vector<int>edge[N];
void dfs(int x,int fa,int z){
	int flag=0;
	for(int i=0;i<edge[x].size();i++){
		int y=edge[x][i];
		if(fa==y){flag=1;continue;}
		if(i+1-flag>=z)mp[make_pair(x,y)]=i+2-flag,dfs(y,x,i+2-flag);
		else mp[make_pair(x,y)]=i+1-flag,dfs(y,x,i+1-flag);
	}
}
int main(){
	cin>>n;
	for(int i=1;i<n;i++)cin>>u[i]>>v[i],edge[u[i]].push_back(v[i]),edge[v[i]].push_back(u[i]);
	for(int i=1;i<=n;i++)maxn=max(maxn,(int)edge[i].size());
	cout<<maxn<<"\n";
	dfs(1,0,maxn+1);
	for(int i=1;i<n;i++)cout<<mp[make_pair(u[i],v[i])]<<"\n";
	return 0;
}
```

---

## 作者：Merge_all (赞：0)

### 思路：
- 发现权值最少的值是**最大度节点的度数**。
- 设这个最大节点的度数为 $cnt$，我们就可以**把任意一个点当做根节点**，然后再进行 dfs 并同时赋值即可。

### 代码：
```
#include<bits/stdc++.h>

using namespace std;

const int N=1000005;

int idx;
int head[N],e[N],nxt[N],v[N],deg[N];
int color[N];
int ans,n,x,y;

void add(int u,int value){
	v[++idx]=value,deg[u]++,deg[value]++;
	nxt[idx]=head[u],head[u]=idx;
}

void dfs(int x,int c){
	int w=0;
	for(int i=head[x];i;i=nxt[i]){
		color[i]=++w;
		if(w==c) color[i]=++w;
		dfs(v[i],color[i]);
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>x>>y;
		add(x,y);
	}
	for(int i=1;i<=n;i++){
		ans=max(deg[i],ans);
	}
	cout<<ans<<"\n";
	dfs(1,0);
	for(int i=1;i<n;i++){
		cout<<color[i]<<"\n";
	}
	return 0;
}
```

---

## 作者：LZYAC (赞：0)

## 思路

此题有两问，依次解决。

第一问：因为连接每个节点的边都得不同，所以最多用的颜色就是最大度节点的度数。

第二问容易看出 DFS 就可以，直接在 DFS 遍历整个树的时候加一个前驱记录哪个颜色不能即可。

## 代码

```cpp
#include<cstdio>
#define N 100005
using namespace std;
int n,ans,col[N],tot,head[N],nxt[N],ver[N],deg[N];
void insert(int x,int y){
	ver[++tot]=y;
	deg[x]++,deg[y]++;
	nxt[tot]=head[x];
	head[x]=tot;
}
void dfs(int x,int c){
	int now=0;
	for(int i=head[x];i;i=nxt[i]){
		col[i]=++now;
		if(now==c) col[i]=++now;
		dfs(ver[i],col[i]);
	}
	return ;
}
int main(){
	scanf("%d",&n);
	for(int i=1,x,y;i<n;i++){
		scanf("%d%d",&x,&y);
		insert(x,y);
	}
	for(int i=1;i<=n;i++){
		if(deg[i]>ans) ans=deg[i];
	}
	printf("%d\n",ans);
	dfs(1,0);
	for(int i=1;i<n;i++){
		printf("%d\n",col[i]);
	}
}
```

---

## 作者：ny_Dacong (赞：0)

# 思路

比较基础的一道 DFS 题。

从根节点开始，依次向它的所有出边赋一个边权。赋的边权可以从 1 开始，依次增加。如果当前的边权是自己入边的边权，那就再换一个颜色。

总数可以用标记数组统计。

几个值得注意的点：

- 题目没有保证树根是 1。所以要自己判断。虽然实践发现数据的根都是 1，但下一次遇到类似的就不一定了。
- 题目输入没有保证 $a$ 是父亲，$b$ 是儿子。但是这道题的数据单向边能过。

~~有趣的事实：我在打线下赛的时候，赛题就是这道。这是我写的 `freopen`：`freopen("color.out","r",stdout);`~~

~~于是呢，$100 \to 0$。火大。~~

# AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,root = 1,ans = 0;
bool used[200005];
long long etot = 0,Last[200005],Next[200005],End[200005],color[200005],ind[200005];
void addedge(long long u,long long v){
	etot++;
	Next[etot] = Last[u];
	Last[u] = etot;
	End[etot] = v;
	color[etot] = 0;
	ind[v]++;
}
void dfs(long long now,long long mycolor){
	if(used[mycolor] == 0){
		ans++;
	}
	used[mycolor] = 1;
	long long tpc = 1;
	for(long long i = Last[now]; i; i = Next[i]){
		if(tpc == mycolor){
			tpc++;
		}
		color[i] = tpc;
		dfs(End[i],tpc);
		tpc++;
	}
}
int main(){
	//freopen("color.in","r",stdin);愿天下再也没人写错freopen!
	//freopen("color.out","w",stdout);铭记逝去的AC 
	scanf("%lld",&n);
	for(long long i = 1; i < n; i++){
		long long tpa,tpb;
		scanf("%lld%lld",&tpa,&tpb);
		addedge(tpa,tpb);
	}
	for(long long i = 1; i <= n; i++){
		if(ind[i] == 0){
			root = i;
			break;
		}
	}
	dfs(root,0);
	printf("%lld\n",ans-1);
	for(long long i = 1; i < n; i++){
		printf("%lld\n",color[i]);
	}
	return 0;
}
```

---

## 作者：LYJ_B_O_Creation (赞：0)

## 题目思路：
### 第一问：
显然颜色最少为连接边最多的点所连的边数，直接统计，找最大值即可。
### 第二问：
用 dfs，由于已经求出颜色数量，所以一条条边循环染色即可（具体的，对于这一条边，染成上一条边加 $1$，超过总颜色数量就再从 $0$ 开始，用模除处理即可），注意输出时要将颜色加 $1$。

## 题目代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n , col;
vector<int>e[N];
int sum[N];
pair<int , int>edge[N];
map<pair<int , int> , int>mp;

void add(int x , int y)
{
    e[x].push_back(y);
    sum[x]++;
}

void dfs(int x , int fa , int last)
{
    for(int i = 0; i < e[x].size(); i++)
    {
        if(e[x][i] == fa) continue;
        last = (last + 1) % col;
        mp[make_pair(x, e[x][i])] = mp[make_pair(e[x][i], x)] = last;
        dfs(e[x][i], x, last);
    }
}
int main()
{
    cin >> n;
    for(int i = 1;i < n;i++)
    {
        int x , y;
        cin >> x >> y;
        add(x , y), add(y , x);
        edge[i] = make_pair(x , y);
    }
    for(int i = 1;i <= n;i++)
    {
        col = max(col , sum[i]);
    }
    cout << col << endl;
    dfs(1 , 0 , col);
    for(int i = 1;i < n;i++)
    {
        cout << mp[edge[i]] + 1 << endl;
    }
    return 0;
}
```
最后感谢 @[zhangxiao666](https://www.luogu.com.cn/user/742017) 的帮助。

---

## 作者：expecto__patronum (赞：0)

## 题意：
给你一颗树，然后让你给边染色（颜色为：$1$，$2$，$3$，$4$ 等等。），对于一个节点来说，连接它的边的颜色不能相同。问你最少可以花费多少种颜色来染色。

## 思路：
很显然，染色需要花费的最少颜色种类肯定是最大度节点的度数。假设这个度数 为 $num$，那么颜色种类就是 $1$ 到 $num$，我们可以选取这个点作为树的树根，然后进行 dfs 进行染色。

还有一点就是，这里我为了方便染色，取得染色为 $0$ 到 $num-1$，最后加 $1$ 就好了。

## AC Code：
```
#include<iostream>
#include<cstring>
#include<queue>
#include<map>
#include<set>
#include<stack>
#include<cstdio>
#include<sstream>
#include<vector>
#include<algorithm>
 
using namespace std;
#define read(x) scanf("%d",&x)
#define Read(x,y) scanf("%d%d",&x,&y)
#define gc(x)  scanf(" %c",&x);
#define mmt(x,y)  memset(x,y,sizeof x)
#define write(x) printf("%d\n",x)
#define pii pair<int,int>
#define INF 1e13
#define ll long long
const ll mod = 2333;
const int N = 1e5 + 10;
const int M = 2e6 + 1005;
map<pii,int> hap;
struct Edge
{
    int next;
    int to;
}edge[N*2];
int deg[N];
int head[N],tot;
inline void add(int from,int to){
    edge[++tot].next= head[from];
    edge[tot].to = to;
    head[from] = tot;
    deg[to] ++;
}
inline void init(){
    mmt(head,-1);
    tot = 0;
}
void dfs(int root,int fa,int color,int color_num){
    for(int i = head[root];~i;i = edge[i].next){
        int y = edge[i].to;
        if(y != fa){
           // cout<<"y: "<<y<< " "<<" c  "<<color<<endl;
            hap[{root,y}] = hap[{y,root}] = color;//染色
            color = (++color)%color_num;
            dfs(y,root,color,color_num);
        }
    }
   // cout<<"UES"<<endl;
}
pii res[N];
int main()
{
    init();
    int n;
    read(n);
 
    int u,v;
    for(int i = 1;i <= n - 1;++i){
        Read(u,v);//重边？,这题很良心，没给重边
        add(u,v);
        add(v,u);
        res[i].first = u;res[i].second = v;
    }
    int root;
    int MAX = -1;
    for(int i = 1;i <= n;++i){//找最大度节点
        if(MAX < deg[i]){
           MAX = deg[i];
           root = i;
        }
    }
    cout<<MAX<<endl;
    //cout<<root;
   // return 0;
    dfs(root,-1,0,MAX);//分别是子树的根节点，子树根节点的父亲，颜色，颜色数量
    for(int i = 1;i <= n - 1;++i){
        cout<<hap[res[i]] +1<<endl;
    }
}
```
[更好阅读体验](https://blog.csdn.net/qq_43408238/article/details/103230117)


---

## 作者：L_zaa_L (赞：0)

## 分析
由于每个点的出边颜色都不能相同，而且还是个树，那么只要子节点的颜色不等于父节点就可以染，从根节点到叶节点都搜一遍，那么每到一个节点那么就可以从一开始枚举，给这个节点的子节点染色。用边表存储边和点，就行了。

## Code
```
#include<bits/stdc++.h>
#define int long long
#define ll long long
#define FOR(i,a,b) for(ll i=(a); i<=(b); ++i)
using namespace std;
inline ll read(){//快读
	ll t=0,f=0;char v=getchar();
	while(!isdigit(v))f|=(v=='-'),v=getchar();
	while(isdigit(v))t=(t<<3)+(t<<1)+v-48,v=getchar();
	return f?-t:t;
}
inline void write(ll x){//快写
	if(x<0){x*=-1; putchar('-');}
	if(x>9) write(x/10);
	putchar(x%10+'0');
	return;
}
int tot,head[1145140],to[1145140],nxt[1145140],bian[1145140];
void add(int u,int v,int p){to[++tot]=v;nxt[tot]=head[u];head[u]=tot;bian[tot]=p;}//边表
string s;
vector<int> a[1145140];
int n,m,k,q,mod,x,y,answer[1145140];
int ans=0;
bool vis[1145140];
void dfs(int now,int fa){
	int col=0;
	for(int i=head[now];i;i=nxt[i]){
		if(!vis[to[i]]){//给他的子节点染色
			col++;
			if(col==fa) col++;//颜色不能等于父节点
			vis[to[i]]=1;
			answer[bian[i]]=col;
			ans=max(col,ans);
			dfs(to[i],col);
		}
	}
}
signed main(){
	//init();
	n=read();
	FOR(i,1,n-1){
		int u,v;
		u=read(),v=read();
		add(u,v,i);
		add(v,u,i);//建立双向边表
	}
	vis[1]=1;
	dfs(1,0);
	cout<<ans<<endl;
	for(int i=1;i<n;i++){
		cout<<answer[i]<<endl;
	}
   return 0;
}

```


---

## 作者：andyli (赞：0)

依题意构造出的答案，权值数量等于一定不小于度数最大点的度数 $d$。考虑以 $1$ 号点为根 dfs，对于当前点的每条出边，设该点与父亲边的权值为 $c$（$1$ 号点 $c=-1$），依次填入 $(c+1)\bmod d$、$(c+2)\bmod d$、$(c+3)\bmod d$……

可以发现这样构造出的答案权值数量等于 $d$。题目要求权值从 $1$ 开始编号，代码里可以 $+1$ 后输出。

```python
import sys
sys.setrecursionlimit(10**8)

n = int(input())
g = [[] for _ in range(n)]
for i in range(n - 1):
    u, v = map(int, input().split())
    g[u - 1] += (v - 1, i), # 记录边的编号，下同
    g[v - 1] += (u - 1, i),

ans = [-1] * (n - 1)
d = max(len(x) for x in g) # 最大度数

def dfs(u, f, c):
    for v, id in g[u]:
        if v != f:
            c = (c + 1) % d # 依次填入
            ans[id] = c + 1 # +1
            dfs(v, u, c)

dfs(0, -1, -1)
print(d, *ans, sep='\n')
```

---

## 作者：yaaaaaan (赞：0)

### 思路
权值最大的肯定是每个点的最大度数，权值方案只需要随便选取一个点一遍 dfs 使得颜色不同就行了。

### code
```cpp
#include <bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
int n,d[100001],ans,c[100001],t;
vector<int> v[100001];
int vv[100001],nxt[100001],head[100001];
void add(int x,int y)
{
	vv[++t]=y;
	nxt[t]=head[x];
	head[x]=t;
	d[x]++;
	d[y]++;
}
void dfs(int x,int q)
{
	int col=0;
	for(int i=head[x];i;i=nxt[i])
	{
		c[i]=++col;
		if(col==q) c[i]=++col;
		dfs(vv[i],c[i]);
	}
}
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<n;i++)
	{
		int x,y;
		cin>>x>>y;
		add(x,y);
	}
	for(int i=1;i<=n;i++)
	{
		ans=max(ans,d[i]);
	}
	cout<<ans<<"\n";
	dfs(1,0);
	for(int i=1;i<n;i++)
	{
		cout<<c[i]<<"\n";
	}
	return 0;
}


```

---

