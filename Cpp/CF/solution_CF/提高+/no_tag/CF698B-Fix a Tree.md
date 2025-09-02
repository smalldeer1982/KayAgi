# Fix a Tree

## 题目描述

对于下图中的树，

![图1](https://cdn.luogu.org/upload/vjudge_pic/CF698B/ea9575b3579124ae37e825f49fe0814b0c31d306.png)

可以用**数组**表示为 $[2,3,3,2]$。这种可以表示树的数组（即**有效**）需要符合以下条件：

1. 有且只有一个索引 $r$，符合 $p_r=r$。其中顶点 $r$ 是树的根。
2. 对于所有剩下的 $n-1$ 个顶点 $i$ 一定要有在 $i$ 和 $p_i$ 之间的边。

比如 数列 $(1,2,2)$、$(2,3,1)$ 和 $(2,1,3)$ 都是因为**根**的数目而导致不**有效**。

现在给你一个**数组** $a_1,a_2,\cdots ,a_n$，**不一定**是**有效**的。你需要对数组里面的值，通过**最小次数**的**更改**，使得这个数组**有效**。

并输出**最小更改次数**和一个通过最小更改次数而更改成功的**有效数组**。

如果有多种解，只需说出任何一组。

## 说明/提示

- 第一个样例只需要改一个就好啦！第一个样例输出是一个扎根于顶点 $4$ 的树（因为 $p_4=4$），你可以在下面的图中看到。另一个正确的答案应该是数列 $2,3,3,2$，扎根在顶点 $3$，也可以在下面的图中看到。两个图中顶点将用红色标出。

![图2](https://cdn.luogu.org/upload/vjudge_pic/CF698B/dd2f59c1134ab719fcaf6a10f190c10a1976cedf.png)

- 第二个样例中，给出的数列已经是有效的了。

## 样例 #1

### 输入

```
4
2 3 3 4
```

### 输出

```
1
2 3 4 4 
```

## 样例 #2

### 输入

```
5
3 2 2 5 3
```

### 输出

```
0
3 2 2 5 3 
```

## 样例 #3

### 输入

```
8
2 3 5 4 1 6 6 7
```

### 输出

```
2
2 3 7 8 1 6 6 7
```

# 题解

## 作者：Gokix (赞：8)

**upd on 22/9/5：修锅，原做法是有问题的，虽然代码歪打正着了**

[CF698B](https://www.luogu.com.cn/problem/CF698B)

题目有些细节还是不错的

------------

显然输入构成了几个树或环（不会出现非环的图），最后只会有根是自环，其余节点的父亲都不会是自己。

考虑一件事，如果输入中就有自环（某棵树的根），那不妨就让它当最后树的根。显然答案不会更劣。

如果一开始没有自环，那选择环上一点作为根即可。

------------

接下来考虑合并连通块；

- 首先要把环变成树。方法是记录 $vis$ 数组，表示是否访问过。然后从每个节点开始 $\text{dfs}$，如果之前访问过了那就证明找到了一个环。又因为输入只可能是环或树，所以这时候你已经遍历过整个环了。于是随便找一个节点的父亲指向总根 $root$ 即可。如果之前还未确定 $root$，则选中的这个节点就是 $root$。

- 接下来合并树与树。方法十分简单，只需要把每个数根的父亲都指向 $root$ 即可。判断树根十分简单：自己的父亲指向自己的节点就是树根。

至此，本题就解决完了。还有什么细节会在代码中体现。

------------

CODE:

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

long long n,a[2000010],f[2000010],vis[2000010],root,tot,ans;

void dfs(long long u){
	if(vis[u]) return;
	vis[u]=tot;
	if(f[u]==u){
		if(!root) root=u;//如果本来没有root它自己就当root
		else{
			f[u]=root;
		}
		return;
	} 
	if(vis[f[u]]){
		if(vis[f[u]]==tot){//是环
			if(!root){
				f[u]=u;
				root=f[u];
			}
			else{
				f[u]=root;
			}	
		}
		return;
	}
	dfs(f[u]);
}

int main(){
	long long i,j,u,v;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>a[i];
	}
	memcpy(f,a,sizeof(a));
	for(i=1;i<=n;i++){//提前找root
		if(f[i]==i){
			root=i;
			break;
		}
	}
	for(i=1;i<=n;i++){
		tot++;//这是一个细节坑点：有可能你之前访问过树的一部分（不是环），所以每次dfs都要打不同的标记
		dfs(i);
	}
	for(i=1;i<=n;i++){
		if(f[i]!=a[i]) ans++;//最后统计答案
	}
	cout<<ans<<endl;
	for(i=1;i<=n;i++){
		cout<<f[i]<<" ";
	}
	cout<<endl;
	return 0;
}
```


---

## 作者：VTloBong (赞：6)

**题意：修改一个图（所有节点出度均为一）上部分节点的父节点，使其成为一颗树**  
**注意：图不一定连通**
## 做法：
>用并查集维护每个连通块，  
因为所有节点出度均为1， 所以连通块只可能为树和简单环  
判别方法见代码  
将所有pre[i]=i的节点连到同一根上，  
若图中只有环，最小操作数为连通块数；  
否则，最小操作数为连通块数-1；


# 放代码：
```cpp
#include<stdio.h>
int pre[210000],n,fa[210000],rtn,qn,rt,q;
int find(int x) {
	return pre[x]==x?x:pre[x]=find(pre[x]);
}
void merge(int x,int y) {
	int fx=find(x),fy=find(y);
	if(fx==fy)return;
	pre[fx]=fy;
}
int readin() {
	int num=0;
	char str=getchar();
	while(str<'0'||str>'9')str=getchar();
	while(str>='0'&&str<='9')
		num=(num<<1)+(num<<3)+str-48,str=getchar();
	return num;
}
int main() {
	n=readin();
	for(int i=1; i<=n; i++)pre[i]=i;
	for(int i=1; i<=n; i++) {
		fa[i]=readin();
		merge(i,fa[i]);
	}//所有节点出度均为1，图中只有树和简单环 
	for(int i=1; i<=n; i++)
		if(pre[i]==i&&fa[i]==i)//判树
			rt=i; //找根 
	if(rt) {
		for(int i=1; i<=n; i++) {
			if(pre[i]-i)continue;
			qn++;
			if(fa[i]==i) {//处理树
				rtn++;
				if(i-rt)fa[i]=rt;
			} else fa[i]=rt;//处理环 
		}
		printf("%d\n",qn-1);
	}else{//只有环的树单独处理 
		for(int i=1; i<=n; i++) {
			if(pre[i]-i)continue;
			qn++;
			if(!rt)rt=i;
			fa[i]=rt;
		}printf("%d\n",qn);
	}for(int i=1; i<=n; i++)
		printf("%d ",fa[i]);
	return 0;
}
```


---

## 作者：业余门槛 (赞：5)

首先说明一下：~~那个翻译的人根本就像是没有读过题目！！！~~

水题一道：

先通过dfs找出哪些有可能时根节点，然后在他们中找一个当做root，剩下来的归到root上就行了。

废话不多，上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MX=200005;
int v[MX],c[MX],f[MX],n;
inline int dfs(int x){  //染色
	if(c[x]) return c[x];
	if(v[x]) return c[x]=x;
	v[x]=1;
	return c[x]=dfs(f[x]);
}
int mian(){
	ios_base::sync_with_stdio(false);
	int i,j,root,gs;
	root=gs=0;
	cin>>n;
	for(i=1;i<=n;i++) cin>>f[i];
	for(i=1;i<=n;i++) dfs(i);                      //每一个都找一遍，进行染色
	for(i=1;i<=n;i++) if(c[i]==i&&f[i]==i) root=i; 
	if(!root){                                     //没有根自己造根
		for(i=1;i<=n;i++){
			if(c[i]!=i) continue;
			gs++;
			f[i]=i;
			root=i;
			break;
		}
	}
	for(i=1;i<=n;i++) if(c[i]==i) gs++,f[i]=root;
	cout<<gs-1<<endl;                              //最后只有一个根
	for(i=1;i<=n;i++) cout<<f[i]<<" ";
	cout<<endl;
	return 0; 
}
```

---

## 作者：_JF_ (赞：2)

[CF698B Fix a Tree](https://www.luogu.com.cn/problem/CF698B)

考虑调整法。

先按照题目给定的 $i$ 和 $fa_i$ 连边。考虑怎么样调整才能保证变成一棵树。

现在的这个图不一定是连通的。但是对于每一个块，只有两种情况：

- 没有环，那么这个地方一定构成了一棵树。

- 有环，那么这时候对于这个块的 $x$ 个点，我们只能保留 $x-1$ 条边，让他构成树的形态。（也就是删去构成环的边）

一个重要的观察，对于一个块，如果有环，**那么这个环最多也是一个**。考虑序列里面 $k$ 个点构成的块，那么这个块至多也就分到了 $k$ 条边。

那只找一个环很简单，拓扑排序即可。

最后就是钦定根的问题，按照题目的连边出来可能有很多个块。在什么地方最优呢？

首先如果有 $fa_i=i$ 的话，直接钦定它为根即可。这样就不用浪费次数再去钦定根了。

如果没有，那说明原图分成了多个环状物，随便钦定一个点为根都是一样的。

具体实现是按照 $i$ 连 $fa_i$ 有向边的形式做的。当然你无向边也行。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
struct node{
	int v,w;
};
vector<node> g[N<<1];
vector<int> G[N],In;
bool vis[N];
int in[N],a[N],root,n,Ans;
void dfs(int u){
	vis[u]=true;
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i].v,w=g[u][i].w; 
		if(w==1)	G[u].push_back(v),in[v]++;
		if(vis[v]==true)	continue;
		In.push_back(v),dfs(v);
	}
}
void Slove(){
	queue<int> q;
	int sum=0;
	for(int i=0;i<In.size();i++)	if(in[In[i]]==0)	q.push(In[i]);
	while(!q.empty()){
		int now=q.front();q.pop();sum++;
		for(int i=0;i<G[now].size();i++){
			int v=G[now][i]; in[v]--;
			if(in[v]==0)	q.push(v);	
		}
	}
	if(sum==In.size()){
		for(int i=0;i<In.size();i++) 
			if(a[In[i]]==In[i]&&In[i]!=root)	Ans++,a[In[i]]=root;
	}
	else{
		int lst=0;
		for(int i=0;i<In.size();i++)	if(in[In[i]]>0)	lst=In[i];
		if(root==0)	root=lst,a[lst]=lst,Ans++;	
		else if(lst!=root)	a[lst]=root,Ans++;
	}
	for(int i=0;i<In.size();i++)	G[In[i]].clear(),in[In[i]]=0;	
	In.clear();
}
int main(){
	cin>>n;
	for(int i=1,x;i<=n;i++){
		cin>>x,a[i]=x;
		if(i!=x)	g[i].push_back({x,1}),g[x].push_back({i,0});
		else	g[i].push_back({x,1});
		root=((x==i)?x:root);
	}
	for(int i=1;i<=n;i++)	if(!vis[i])	dfs(i),In.push_back(i),Slove();
	cout<<Ans<<endl;
	for(int i=1;i<=n;i++)	cout<<a[i]<<" ";
	cout<<endl;
	return 0;
}
```

---

## 作者：TernaryTree (赞：2)

首先这是一坨内向基环树森林。

每次操作修改一条边，可以合并两个连通块。连通块用并查集维护，如果新加入的边两端点在同一连通块内，说明加上以后会有环，需要更改这条边。

首先在原数组中找到一个 $a_i=i$ 的点钦定它是根。然后一切要改的边全部无脑往根上连即可。

如果在原数组中找不到 $a_i=i$ 的点怎么办呢，我们找到第一条需要改的边 $i\to a_i$，把它的出发点 $i$ 钦定为根。这样就可以愉快地使用并查集维护了。

简短的代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5 + 1;

int n;
int a[maxn];
int fa[maxn];
int cnt, root;

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        fa[i] = i;
        if (!root && a[i] == i) root = i;
    }
    for (int i = 1; i <= n; i++) {
        if (i == root) continue;
        int u = find(i), v = find(a[i]);
        if (u != v) fa[u] = v;
        else if (!root) root = i, a[i] = i, ++cnt;
        else a[i] = root, fa[u] = find(root), ++cnt;
    }
    cout << cnt << endl;
    for (int i = 1; i <= n; i++) {
        cout << a[i] << " ";
    }
    return 0;
}
```

---

## 作者：2huk (赞：1)

> - 对于一棵大小为 $n$ 的有根树，我们定义 $f_i$：
>
>   - 对于非根节点 $i$ 有 $f_i=fa_i$，也就是 $i$ 的父节点。
>   - 对于根节点 $root$，有 $f_{root}=root$。
>
>   这样的 $f$ 数组对应了一棵有根树。
>
>   现给你一个长度为 $n$ 的数组 $a$，你需要修改尽量少的数组元素，使得该数组能够对应一棵有根树。
>
> - $a_i \le n \le 2 \times 10^5$。

显然原图构成了若干棵树和基环树。我们要做的是将它们合并。

首先我们可以钦定一个点作为根节点。若原图中存在 $a_i = i$ 的情况，就把这个 $i$ 钦定为根。反之如果不存在，就随便找一个环，并钦定环上某个点为根即可。

然后对于每个环，我们希望破坏这个环使得整个图成为树。那么任选其中一个点，并将这个点指向根即可。

```cpp
int n, a[N], f[N], st[N], cnt, root;

void dfs(int u, int cnt) {
	st[u] = cnt;
	if (f[u] == u) {
		if (!root) root = u;
		else f[u] = root;
	}
	else if (st[f[u]]) {
		if (st[f[u]] == cnt) {
			if (!root) {
				root = u;
				f[u] = u;
			}
			else f[u] = root;
		}
	}
	else dfs(f[u], cnt);
}

void Luogu_UID_748509() {
	fin >> n;
	for (int i = 1; i <= n; ++ i ) {
		fin >> a[i];
		f[i] = a[i];
		if (i == f[i]) root = i;
	}
	
	for (int i = 1; i <= n; ++ i )
		if (!st[i]) dfs(i, ++ cnt);
	
	int res = 0;
	for (int i = 1; i <= n; ++ i ) res += a[i] != f[i];
	fout << res << '\n';
	for (int i = 1; i <= n; ++ i ) fout << f[i] << ' ';
}
```

---

## 作者：Cure_Wing (赞：1)

[CF698B  Fix a Tree](https://www.luogu.com.cn/problem/CF698B)

### 思路

我们把 $p_r=r$ 的节点也连上自环，那么所有的 $(p_r,r)$ 的有向边就构成了基环树森林。在这样的条件下，连成一棵树只需要只存在一个环且这个环是自环就可以了。

假设原图存在一个自环，那么我们可以就钦定它为根，也就是不拆它。那么对于其它的环（包括自环），如果不拆，那么永远不会和其它的连通块连通，也不可能只存在一个环。并且我们发现，由于一个点的出度恰好为 $1$，所以一个连通块内至多只有一个环。因此，我们在其它的有向图连通块内一旦找到了一个环，那么就找到任意一个环上的点，让它连向我们钦定的根即可。可以发现，此时以连出去的点为根的子树内不再存在环。

假设原图不存在一个自环，那么一定存在一个二元及以上的环，毕竟每个点都有一条出边。此时我们拆掉这个环，让环上的其中一个点连向它自己，形成一个自环，这样就可以让它成为树的根。这样其它的环就可以按照有自环（有根）的方式做了。

找环可以 `dfs`，但是我写了 `tarjan`。

时间复杂度 $O(n)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<stack>
using std::cin;using std::cout;
constexpr int N=200005;
int n,a[N],root,dfn[N],low[N],cnt,ans;
std::vector<int>edge[N];
bool vis[N];
std::stack<int>s;
inline void tarjan(int u){
	dfn[u]=low[u]=++cnt;vis[u]=1;s.push(u);
	for(int i:edge[u])	
		if(!dfn[i]){
			tarjan(i);
			low[u]=std::min(low[u],low[i]);
		}else if(vis[i]) low[u]=std::min(low[u],dfn[i]);
	if(dfn[u]==low[u]){
		int cnt=0,w=s.top();//tarjan 栈顶节点一定属于环（如果存在）
		while(s.top()!=u){vis[s.top()]=0;s.pop();++cnt;}
		++cnt;s.pop();vis[u]=0;
		if(w==u&&a[u]==u){//自环
			if(root!=u){a[u]=root;++ans;}
		}
		if(cnt>1){//特判节点无出边的情况，此时不成环
			if(!root)root=a[w]=w;//无根
			else a[w]=root;
			++ans;
		}
	}
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		edge[a[i]].push_back(i);
		if(i==a[i]) root=i;
	}
	for(int i=1;i<=n;++i) if(!dfn[i]) tarjan(i);
	cout<<ans<<'\n';
	for(int i=1;i<=n;++i) cout<<a[i]<<' ';
	return 0;
}
```

---

## 作者：tmp_get_zip_diff (赞：1)

当时也是想到了并查集，但是有几个地方没有想清楚，所以就不知道怎么写了，比如说如何确定最优的问题。

其实没有那么复杂，这个题目我们的操作只有三个
- 1、确定根节点。
- 2、解环。
- 3、连接子树。

如果题目中给出了一个或者多个根节点，我们任选一个即可，证明：假设有 $k$ 个可行根节点，那么选择一个不动，改动 $k-1$ 次，每种选择都是这样。但如果题目中没有可选根节点，就不可以随便去选了，首先明确这种情况一定存在了1个或者多个环，我们一定要从环中选取根节点，因为这样只进行了一次操作就破环了环结构而且确定了根节点，如果在环外选择根节点，则改动为根节点需要1步，解环也需要一步，不是最优解！

为了操作方便，使用并查集寻找环，并将找到第一个环的任意一个节点作为根节点。

在确定了根节点之后，如果遇到其他可行根节点，直接连接到已确定根节点即可，就是连接子树的操作。

注意：这个注意是对我自己说的，也是对一些向我一样的人说的，我犯了一个低级错误，我在判断环的时候居然没有用 find 判断，而是用 $fa$ 判断，当时还感觉很困惑，以为合并方式不对，发现了以后才感觉自己真是好久没做过并查集了，太蒟蒻了。。

代码如下：

```
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define N 200020
int a[N],fa[N];
int Find(int x)
{
    return x==fa[x] ? x : fa[x] = Find(fa[x]);
}
void unin(int x,int y)
{
    int fax = Find(x);
    int fay = Find(y);
    fa[fay] = fax;
}
int main()
{
    int root = -1,ans=0,n;
    cin>>n;
    for(int i = 1; i <= n; i++)
    {
        cin>>a[i];
        fa[i] = i;
        if(a[i]==i) root = i;
    }
    for(int i = 1; i <= n; i++)
    {
        if(i == a[i] && a[i] == root) continue;
        else if(a[i] == i && i != root)
        {
            a[i] = root;
            ans++;
            unin(root,i);
        }
        else if(a[i] != i && Find(a[i]) != Find(i))
        {
            unin(a[i],i);
        }
        else if(a[i] != i && Find(a[i]) == Find(i))
        {
            ans++;
            if(root == -1)
            {
                root = i;
            }
            a[i] = root;
            unin(root,i);
        }
    }
    cout<<ans<<endl;
    for(int i = 1; i <= n; i++)
    {
        if(i==n) cout<<a[i]<<endl;
        else cout<<a[i]<<" ";
    }
    return 0;
}
```

-------------

希望看懂

---

## 作者：World_Creater (赞：1)

我们注意到按照原图的划分方式，这个图会划分成若干个连通块。

如果我们考虑 $a_i=i$ 的自环，那么**每一个连通块都是一棵基环树**（即边数与点数相同的连通图）。

我们考虑找出这些基环树的环，删除其中一条边，并用这条边与其他连通块连接，这样我们用一次修改减少了一个连通块。

我们考虑将那些删掉的边与哪个连通块相连。

注意到题目中将 $a_i=i$ 的环当作根节点。也就是说，**存在这种情况的连通块实际上是一棵“树”**。
 
因此我们可以考虑提出一棵“树”，将所有删掉的边都连向这棵“树”，答案便是连通块的个数减一。

注意到题目中可能没有 $a_i=i$ 的情况，这种情况需要额外修改出这种边，并使答案加一。

Code: 
```cpp
#include<bits/stdc++.h>
using namespace std;
struct dsu{
	int f[200005];
	dsu(){
		iota(f+1,f+200001,1);
	}
	int find(int x)
	{
		return f[x]==x?x:f[x]=find(f[x]);
	}
	void make(int x,int y)
	{
		f[find(x)]=find(y);
	}
}T;//并查集部分，用来找连通块
int n,a[200005],cnt,v[200005],vis[200005],nxt[400005],head[200005],go[400005],tag[400005],k,ans[200005],po[200005],q,d=-1;
void add(int u,int v,int w)
{
	nxt[++k]=head[u];
	head[u]=k;
	go[k]=v;
	tag[k]=w;
}
void dfs(int x,int fa,int p)
{
	v[x]=p;
	for(int i=head[x];i;i=nxt[i])
	{
		int g=go[i];
		if(g!=fa)
		{
			if(v[g]==p)
			{
				ans[tag[i]]=p;
				q=1; //标记环边
				break;
			}
			else dfs(g,x,p);
		}
	}
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int u;
		cin>>u;
		a[i]=u;
		add(u,i,i);
		add(i,u,i);
		T.make(u,i);
	}
	for(int i=1;i<=n;i++)
	{
		if(!vis[T.find(i)])
		{
			cnt++;
			q=0;
			vis[T.find(i)]=cnt;
			po[cnt]=i;
			dfs(i,0,cnt);
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(ans[i])
		{
			if(a[i]==i) 
			{
				d=vis[T.find(i)]; //标记连向哪个连通块
				break;
			}
		}
	}
	if(d==-1) //不存在就造一个
	{
		cnt++;
		d=1;
		for(int i=1;i<=n;i++)
		{
			if(ans[i]&&vis[T.find(i)]==1)
			{
				ans[i]=0;
				a[i]=i;
				break;
			}
		}
	}
	cout<<cnt-1<<"\n";
	for(int i=1;i<=n;i++)
	{
		if(ans[i]!=0&&vis[T.find(i)]!=d)
		{
			cout<<po[d]<<" ";
		}
		else
		{
			cout<<a[i]<<" ";
		}
	}
}
```

---

## 作者：ZLCT (赞：0)

# CF698B Fix a Tree
## 题目简述
给定一个数组 $a$ 表示在一棵树中 $father_i=a_i$。如果 $a_i=i$ 则表示它是根节点。求最少更改次数使序列合法，并输出更改后的序列。
## 先贪后证 $\times$ 边贪边证 $\checkmark$
### 从根节点入手？
注意到根节点是非常特殊的，于是我们先研究根节点的情况。
1. 如果存在 $a_i=i$。那么我们直接把它当根节点。\
证明：假设存在一个最优解的根不是 $i$，那么一定需要把 $a_i$ 变成最优解的根，这与把该解的根的父亲变成 $i$ 相比一定是不劣的。
2. 如果有多个 $a_i=i$，那么随便把其中一个当作根都可以，证明同上。
3. 如果没有 $a_i=i$ 呢？那随便把一个本来就要改的作为根就行了。但是必须要改一个吗？答案是肯定的，具体证明见下。
### 其余节点？
我们考虑什么时候是合法的，就是 $a_i$ 与 $i$ 不在一个连通块里，也就是说不能出现环。\
那如果出现环怎么办呢？那说明我们肯定要断掉一条 $a_i$ 与 $i$ 的连边，因为我们只需要连通性，所以改变任意一条边的代价和影响都一样，于是我们直接断掉这条边向根连即可。\
下面问题就回到了没有根的情况了，这时候我们如果有一个要改的点，那么本来就要改，把它当作根即可。\
会不会出现没有要改的点呢？答案是不会的，下面我们给出证明：\
假设没有根，就一定会出现 $n$ 条没有自环的边，在 $n$ 个点的图中，$n$ 条边一定会出现至少一个环，这与**我们没有要改的点**的假设矛盾。\
于是我们在一堆看起来显而易见的结论中就完成了这道题。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,fa[202222],a[202222],rk[202222],ans[202222],cnt,pre,root;
bool flagroot;
bool vis[202222];
int find(int x){
    if(x==fa[x])return x;
    return fa[x]=find(fa[x]);
}
void merge(int x,int y){
    x=find(x);y=find(y);
    if(rk[x]>rk[y]){
        fa[y]=x;
    }else if(rk[x]==rk[y]){
        fa[y]=x;rk[x]++;
    }else{
        fa[x]=y;
    }
}
int main(){
    cin>>n;
    for(int i=1;i<=n;++i)fa[i]=i;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        if(find(i)!=find(a[i])){
            merge(i,a[i]);
            vis[i]=1;
            ans[i]=a[i];
        }else{
            if(!flagroot&&a[i]==i){
                flagroot=1;
                root=i;
                vis[i]=1;
                ans[i]=a[i];
            }
            else{
                cnt++;
            }
        }
    }
    for(int i=1;i<=n;++i){
        if(!vis[i]){
            if(!flagroot){
                ans[i]=i;
                flagroot=1;
                root=i;
                continue;
            }
            else{
                merge(i,root);
                ans[i]=root;
                continue;
            }
        }
    }
    cout<<cnt<<'\n';
    for(int i=1;i<=n;++i){
        cout<<ans[i]<<' ';
    }
    cout<<'\n';
    return 0;
}
```

---

## 作者：happybob (赞：0)

考虑把题目中的边设为有向边，$i \rightarrow p_i$。考虑每个连通块。

显然每个连通块是一个 $x$ 个点 $x$ 条边的图，且至多只有一个自环。于是这必然是一棵树，或者内向基环树。

首先确定最终树的根。如果存在任意一个 $p_i=i$，那么根就可以确定为 $i$。有多个取任意一个即可。

如果没有，将某个基环树的环上某个点设为根，把 $p_u$ 改成 $u$。

接着考虑每个连通块。如果是树，把树根的 $p$ 改成最终树的根。否则搜出环，把环上任意一个点的 $p$ 改成根即可。显然每个连通块改一次，答案已经是最小的了。

实现上有一些细节。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int n, a[N], na[N];
vector<int> G[N];
 
bool vis[N];
int rt;
bool isc = 0;
int cl;
int fp;

void dfs(int u, int fa)
{
	if (a[u] == u) fp = u;
	vis[u] = 1;
	for (auto &j : G[u])
	{
		if (j == fa) 
		{
			if ((na[u] == fa && na[fa] == u))
			{
				isc = 1;
				cl = j;
			}
			continue;
		}
		if (vis[j])
		{
			isc = 1;
			cl = j;
		}
		else dfs(j, u);
	}
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) 
	{
		cin >> a[i];
		na[i] = a[i];
		if (i == a[i])
		{
			rt = i;
			continue;
		}
		G[i].emplace_back(a[i]);
		G[a[i]].emplace_back(i);
	}
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		if (vis[i]) continue;
		isc = 0, cl = 0, fp = 0;
		dfs(i, 0);
		if (isc)
		{
			if (!rt) a[cl] = cl, rt = cl;
			else a[cl] = rt;
			ans++;
		}
		else
		{
			if (rt == fp) continue;
			a[fp] = rt;
			ans++;
		}
	}
	cout << ans << "\n";
	for (int i = 1; i <= n; i++) cout << a[i] << " ";
	return 0;
}
```


---

## 作者：TruchyR (赞：0)

## Part 1 思路
将每个点 $i$ 与 $a_i$ 连边。  
容易发现最终构成的图是一个基环树森林（$n$ 个点，$n$ 条边）！  
[（基环树的定义？）](https://oi-wiki.org/graph/concept/#%E7%89%B9%E6%AE%8A%E7%9A%84%E5%9B%BE)  
那么只有每个基环树中间的环通过改变祖先需要打破，有多个环的话把他们按照链的方式连起来。  
**最小次数就是基环树的数量**。  
随后你会发现，你的改祖先是合法的，而样例一**方案数多了**。  
把样例一进行一个构图：  
![](https://cdn.luogu.com.cn/upload/image_hosting/apyfr1ar.png)  
容易发现，这个图中的两个环大小都是 $1$。  
这个样例答案是 $1$ 的原因是**大小为 $1$ 的环如果在链的开头，不需要改祖先。**  
所以我们特判一下有没有大小为 $1$ 的环即可。
## Part 2 代码
找非环部分可以用拓扑排序实现。  
```cpp
#include<bits/stdc++.h>
#define MX 200005
using namespace std;
int n,a,b,f[MX],c[MX],d[MX],res;
struct eg{int id,sz;}l[MX];
bool cmp(eg X,eg Y){return X.sz<Y.sz;}
vector<int> v[MX];queue<int> q;
int dfs(int t){//把环上所有的点都染色防止重复搜索
	c[t]=1;int cnt=1;
	for(auto i:v[t]){
		if(c[i]) continue;
		cnt+=dfs(i);
	}return cnt;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>f[i];
		d[i]++;d[f[i]]++;
		v[i].push_back(f[i]);
		v[f[i]].push_back(i);
	}
	//找基环树的非环部分
	for(int i=1;i<=n;i++){
		if(d[i]!=1) continue;
		q.push(i);c[i]=1;
	}
	while(q.size()){
		int t=q.front();q.pop();
		for(auto i:v[t]){
			if(c[i]) continue;
			d[i]--;
			if(d[i]==1){
				c[i]=1;
				q.push(i);
			}
		}
	}
	//找基环树的环部分
	for(int i=1;i<=n;i++){
		if(c[i]) continue;
		res++;
		l[res]=eg{i,dfs(i)};
	}
	sort(l+1,l+res+1,cmp);
	f[l[1].id]=l[1].id;//第一个环把祖先给自己
	for(int i=2;i<=res;i++)
		f[l[i].id]=f[l[i-1].id];//按照链的方式改祖先
	if(l[1].sz==1) res--;//有环大小为1
	cout<<res<<'\n';
	for(int i=1;i<=n;i++)
		cout<<f[i]<<' ';
	return 0;
}
```


---

## 作者：loser_seele (赞：0)

首先不难发现，因为题目限制了一个点最多只有一条出边，所以所有连通块显然要么是基环树要么是树。

观察可知题目给定的操作相当于允许断掉一条边或者改变一条边。

如果有树的情况下直接把树的根节点确定下来显然更优，否则需要先断一条边将这个连通块变成树，现在假设连通块是至少一棵树和若干个环。

对于环的部分，直接改变这条边接到树上即可，树类似，所以问题实际上转化为统计点连通块数量。

看见点连通块问题，果断上 LCT 维护，找到一个环的时候断掉环，累加答案，否则直接合并两个点即可。

时间复杂度 $ \mathcal{O}(n\log{n}) $，可以通过。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
const int maxn=2e5+10;
const int mod=1e9;
struct Splay
{
    int ch[maxn][2],fa[maxn],siz[maxn],val[maxn],sum[maxn],add[maxn],mul[maxn],rev[maxn];
    void clear(int x)
    {
        ch[x][0]=ch[x][1]=fa[x]=siz[x]=val[x]=sum[x]=add[x]=rev[x]=0;
        mul[x]=1;
    }
    int getch(int x)
    {
        return (ch[fa[x]][1]==x);
    }
    int isroot(int x)
    {
        clear(0);
        return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;
    }
    void maintain(int x)
    {
        clear(0);
        siz[x]=(siz[ch[x][0]]+1+siz[ch[x][1]])%mod;
        sum[x]=(sum[ch[x][0]]+val[x]+sum[ch[x][1]])%mod;
    }
    void pushdown(int x)
    {
        clear(0);
        if(mul[x]!=1)
        {
            if(ch[x][0])
            mul[ch[x][0]]=(mul[x]*mul[ch[x][0]])%mod,val[ch[x][0]]=(val[ch[x][0]]*mul[x])%mod,sum[ch[x][0]]=(sum[ch[x][0]]*mul[x])%mod,add[ch[x][0]]=(add[ch[x][0]]*mul[x])%mod;
            if(ch[x][1])
            mul[ch[x][1]]=(mul[x]*mul[ch[x][1]])%mod,val[ch[x][1]]=(val[ch[x][1]]*mul[x])%mod,sum[ch[x][1]]=(sum[ch[x][1]]*mul[x])%mod,add[ch[x][1]]=(add[ch[x][1]]*mul[x])%mod;
            mul[x]=1;
        }
        if(add[x])
        {
            if(ch[x][0])
            add[ch[x][0]]=(add[ch[x][0]]+add[x])%mod,val[ch[x][0]]=(val[ch[x][0]]+add[x])%mod,sum[ch[x][0]]=(sum[ch[x][0]]+add[x]*siz[ch[x][0]])%mod;
            if(ch[x][1])
            add[ch[x][1]]=(add[ch[x][1]]+add[x])%mod,val[ch[x][1]]=(val[ch[x][1]]+add[x])%mod,sum[ch[x][1]]=(sum[ch[x][1]]+add[x]*siz[ch[x][1]])%mod;
            add[x]=0;
        }
        if(rev[x])
        {
            if(ch[x][0])
            rev[ch[x][0]]^=1,swap(ch[ch[x][0]][0],ch[ch[x][0]][1]);
            if(ch[x][1])
            rev[ch[x][1]]^=1,swap(ch[ch[x][1]][0],ch[ch[x][1]][1]);
            rev[x]=0;
        }
    }
    void update(int x)
    {
        if(!isroot(x))
        update(fa[x]);
        pushdown(x);
    }
    void rotate(int x)
    {
        int y=fa[x],z=fa[y],chx=getch(x),chy=getch(y);
        fa[x]=z;
        if(!isroot(y))
        ch[z][chy]=x;
        ch[y][chx]=ch[x][chx^1];
        fa[ch[x][chx^1]]=y;
        ch[x][chx^1]=y;
        fa[y]=x;
        maintain(y);
        maintain(x);
        maintain(z);
    }
    void splay(int x)
    {
        update(x);
        for(int f=fa[x];f=fa[x],!isroot(x);rotate(x))
        if(!isroot(f))
        rotate(getch(x)==getch(f)?f:x);
    }
    void access(int x)
    {
        for(int f=0;x;f=x,x=fa[x])
        splay(x),ch[x][1]=f,maintain(x);
    }
    void makeroot(int x)
    {
        access(x);
        splay(x);
        swap(ch[x][0],ch[x][1]);
        rev[x]^=1;
    }
    int find(int x)
    {
        access(x);
        splay(x);
        while(ch[x][0])
        x=ch[x][0];
        splay(x);
        return x;
    }
    void final_mul(int u,int v,int c)
    {
    makeroot(u), access(v), splay(v);
      val[v] = val[v] * c % mod;
      sum[v] = sum[v] * c % mod;
      mul[v] = mul[v] * c % mod;
    }
    void final_add(int u,int v,int c)
    {
    makeroot(u), access(v), splay(v);
      val[v] = (val[v] + c) % mod;
      sum[v] = (sum[v] + siz[v] * c % mod) % mod;
      add[v] = (add[v] + c) % mod;
    }
    int query1(int u,int v)
    {
    makeroot(u), access(v), splay(v);
    return sum[v];
    }
    void link(int u,int v)
    {
    if (find(u) != find(v)) 
    makeroot(u), fa[u] = v;
    }
    void cut(int u,int v)
    {
    makeroot(u);
      access(v);
      splay(v);
      if (ch[v][0] == u && !ch[u][1]) 
      ch[v][0] = fa[u] = 0;
    }
    bool query2(int u,int v)
    {
    return find(u) == find(v);
    }
}st;
int find(int x)
{
return st.find(x);
}
void merge(int u,int v)
{
st.link(u,v);
}
void clean(int n)
{
for(int i=1;i<=n;i++)
st.clear(i),st.maintain(i),st.splay(i);
}//main
int a[2000020],ans=0;
void gen(int n)
{
int f[2000020];
for(int i=1;i<=n;i++)
f[i]=i;
do
{
if(0)//add something here.
ans++;
}while(next_permutation(f+1,f+n+1));
}
#define Y cout<<"Yes"<<'\n'
#define N cout<<"No"<<'\n'
signed main()
{
int T=1;
//cin>>T;
while(T--)
{
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) 
    cin >> a[i];
    clean(n);
    int root = 0;
    int ans = 0;
    for(int i = 1; i <= n; i++)
        if(i==a[i]) 
        root = i;
    for(int i = 1; i <= n; i++)
    {
        if(i==root) 
        continue;
        int x = st.find(i);
        int y = st.find(a[i]);
        if(x==y)
        {
            if(!root) 
            root = i;
            a[i] = root;
            ans++;
        }
        else
        merge(x,y);
    }
    cout<<ans<<'\n';
    for(int i = 1; i <= n; i++) 
    cout<<a[i]<<" "; 
}
}
//V me 30000
```


---

