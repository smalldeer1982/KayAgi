# [EC Final 2021] DFS Order

## 题目描述

庞教授有一棵以 $1$ 为根的树，这棵树有 $n$ 个节点。这 $n$ 个节点的编号从 $1$ 到 $n$。

现在他想从根节点开始进行深度优先搜索。他想知道对于每个节点 $v$，它在深度优先搜索顺序中出现的最小和最大位置。深度优先搜索顺序是指在深度优先搜索过程中访问节点的顺序。一个节点出现在这个顺序中的第 $j$ 个位置（$1 \le j \le n$）意味着它是在 $j-1$ 个其他节点之后被访问的。由于一个节点的子节点可以以任意顺序进行迭代，因此存在多种可能的深度优先顺序。庞教授想知道对于每个节点 $v$，使得 $v$ 出现在第 $j$ 个位置的最小值和最大值分别是多少。

以下是对根树进行深度优先搜索的伪代码。在其执行之后，$\texttt{dfs\_order}$ 是深度优先搜索顺序。

```
let dfs_order be an empty list

def dfs(vertex x):
    append x to the end of dfs_order.
    for (each son y of x): // sons can be iterated in arbitrary order.
        dfs(y)

dfs(root)
```

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
2
4
1 2
2 3
3 4
5
1 2
2 3
2 4
1 5```

### 输出

```
1 1
2 2
3 3
4 4
1 1
2 3
3 5
3 5
2 5```

# 题解

## 作者：yszkddzyh (赞：12)

因为是从根节点开始按任意顺序进行深度优先遍历，所以如果想让一个节点尽可能早地遍历到，那显然就应该先朝它这个方向遍历，但由于是深度优先，所以它能遍历到的最早的序号应该就是它的深度，因为你必须经过它的祖先结点才能到它。

反之，如果想让它尽可能晚地遍历到，那就需要先去把别的点尽量都遍历一遍，但同样地，由于是深度优先，所以你不能把这个节点的子节点先遍历了再遍历这个节点，由此，答案即为所有节点数减这个节点的子树的大小加一。

这样，我们 dfs 预处理出每个节点的深度和子树大小，问题迎刃而解。

注意，代码中存储节点深度和子树大小的两个数组在多测中**不需要**清空，如果你用 `memset` 会超时第 $3$ 个点（深受其害）。

代码如下：

```cpp

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
vector <int> G[N];
int t, n, siz[N], dep[N];

void dfs(int u, int f){
	dep[u] = dep[f] + 1;
	siz[u] = 1;
	for(int i = 0; i < G[u].size(); i++){
		int v = G[u][i];
		if(v == f) continue;
		dfs(v, u), siz[u] += siz[v];
	}
	return;
}

int main(){
	
	ios :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t--){
		cin >> n;
//      memset(dep, 0, sizeof(dep));
//      memset(siz, 0, sizeof(siz));
		for(int i = 1; i <= n; i++) G[i].clear();
		for(int i = 1, u, v; i < n; i++){
			cin >> u >> v;
			G[u].push_back(v);
			G[v].push_back(u);
		}
		dfs(1, 0);
		for(int i = 1; i <= n; i++)
			cout << dep[i] << ' ' << n - siz[i] + 1 << '\n';
	}
	
	return 0;
}

```

---

## 作者：szh_AK_all (赞：5)

## 良心题解
### 题意
这道题分为两问，第一问求一棵树中每个节点在深度优先搜索中最少几次被搜到，第二问求一棵树中每个节点在深度优先搜索中最多几次被搜到。

### 分析
首先解决第一问。

我们要求一个节点最少几次被搜到，那么得先求出它的父节点最少几次被搜到。用 $d_{i}$ 表示第 $i$ 个节点最少第几次被搜到，用 $f_{i}$ 表示第 $i$ 个节点的父亲，则 $d_{i}=d_{f_{i}}+1$。类似于求出每个节点的深度。

其次解决第二问。

我们要尽可能让某个节点在深搜中后搜到，则这个节点的子树在深搜中也是后搜到，因为我们要搜每个节点，必须先搜到该节点的所有祖先。所以，我们要先搜到初这个节点及子树外的所有节点，再搜该节点。那么，用 $sz_{i}$ 表示第 $i$ 个节点的子树的大小（包括这个节点），则 $n-sz_{i}+1$ 就是搜到第 $i$ 个节点的最大次数。

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int>a[100005];
int de[100005];
int sz[100005];
void dfs(int x,int fath)//求深度
{
	de[x]=de[fath]+1;
	for(int i=0;i<a[x].size();i++)
	{
		int y=a[x][i];
		if(y!=fath)
			dfs(y,x);
	}
}
void df(int x,int fath)//求子树大小
{
	sz[x]=1;
	for(int i=0;i<a[x].size();i++)
	{
		int y=a[x][i];
		if(y!=fath)
		{
			df(y,x);
			sz[x]+=sz[y];
		}
	}
}//df和dfs其实可以放在一起写
int main()
{
	int t;
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		int n;
		cin>>n;
		for(int j=1;j<n;j++)
		{
			int x,y;
			cin>>x>>y;
			a[x].push_back(y);
			a[y].push_back(x);
		}
		de[1]=1;
		dfs(1,0);
		df(1,0);
		for(int j=1;j<=n;j++)
		{
			cout<<de[j]<<" "<<n-sz[j]+1<<endl;
			a[j].clear();
			de[j]=0;
			sz[j]=0;
		}
	}
}
```


---

## 作者：_CUI_ (赞：4)

## 思路
这道题要求若按任意顺序进行深度优先搜索，则第 $i$ 个点最小是第几个被搜到的以及最大是第几个。

最小很好想，就是从根节点每次都往下走直到走到这个节点（换而言之就是这个节点的深度）。而最大就是先把除了这个节点的其他能走的节点都走了在遍历这个点。由于不遍历这个节点就无法遍历它的子节点，所以最大就是 $n$ 减去它的子节点个数后加 $1$。

## AC Code
```
#include<bits/stdc++.h>
using namespace std;
int T,n,d[100001],t[100001];
vector<int> e[100001];
bool f[1000001];
void dfs(int p){
	for(auto i:e[p]){
		if(f[i]){
			d[i]=d[p]+1,f[i]=false;
			dfs(i);
			t[p]+=t[i];
		}
	}
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i) d[i]=0,t[i]=1,f[i]=true,e[i].clear(); 
		d[1]=1,f[1]=false;
		for(int i=1;i<n;++i){
			int x,y;
			scanf("%d%d",&x,&y);
			e[x].push_back(y);
		}
		dfs(1);
		for(int i=1;i<=n;++i){
			int ans1=0,ans2=0;
			ans1=d[i];
			ans2=n-t[i];
			printf("%d %d\n",ans1,ans2+1);
		}
	}
	return 0;
}
```


---

## 作者：Lyrith_with_xQ (赞：2)

首先，[读题!](https://www.luogu.com.cn/problem/P9872)

题意
-
给出一棵树，从 $1$ 号节点开始遍历，一个结点的儿子的遍历顺序可以任意调换，问这棵树上的每个节点最早被遍历到的时间戳和最晚被遍历到的时间戳。

思路
-
很容易看出来，每个节点最早被遍历到的时间戳就是这个结点的深度。对于如何求最晚被遍历到的时间戳，可以参考下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/m2xdse5j.png)

当遍历到节点 $1$ 时，可以发现它的一个孩子节点 $6$ 最晚被遍历到的时间戳就是节点 $1$ 最晚被遍历到的时间戳加上以节点 $1$ 为根的子树的节点数再减去这个孩子节点 $6$ 为根的子树的节点数（简单来说，就是先把其他孩子节点为根的子树中所有的节点先遍历完后再来遍历这个以孩子节点 $6$ 为根的子树）。把这段话概括成公式后是这样的（下文公式中 $t_x$ 表示节点 $x$ 最晚被遍历到的时间戳，$s_x$ 表示以节点 $x$ 为根的子树的节点数）：

$$t_x=t_f+s_f-s_x$$

别忘了要先预处理好 $s$ 数组。

代码
-
```
#include<bits/stdc++.h>
using namespace std;

int t,n,a,b,maxt[100005],mint[100005],cnt[100005];
vector<int> mp[100005];

void dfs1(int x,int f)//预处理以任何一个节点作为根的子树的节点数，储存在cnt数组中
{
    cnt[x]=1;
    for(int i=0;i<mp[x].size();i++)
    {
        if(mp[x][i]==f)continue;
        dfs1(mp[x][i],x);
        cnt[x]+=cnt[mp[x][i]];
    }
}

void dfs2(int x,int t,int f)//计算每个节点最早被遍历到的时间戳和最晚被遍历到的时间戳
{
    mint[x]=t;//每个节点最早被遍历到的时间戳就是这个结点的深度
    maxt[x]=(x==1? 1:cnt[f]-cnt[x]+maxt[f]);//用上文提到的公式计算每个节点最晚被遍历到的时间戳
    for(int i=0;i<mp[x].size();i++)
    {
    	if(mp[x][i]==f)continue;
        dfs2(mp[x][i],t+1,x);
    }
}

void read(int &n)//快输快读 
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    n=x*f;
}

void print(int n)
{
    if(n<0)
    {
        putchar('-');
        n*=-1;
    }
    if(n>9)print(n/10);
    putchar(n%10+'0');
}

int main()
{
    cin>>t;
    while(t--)
    {
        read(n);
        for(int i=1;i<=n;i++)mp[i].clear();//多测不清空，爆零两行泪
        for(int i=1;i<n;i++)
        {
            read(a);read(b);
            mp[a].push_back(b);
            mp[b].push_back(a);
        }
        dfs1(1,0);//别忘了需要先预处理
        dfs2(1,1,0);
        for(int i=1;i<=n;i++){print(mint[i]);printf(" ");print(maxt[i]);printf("\n");}
    }
    return 0;
}
```
性能分析
-
时间复杂度：$O(nT)$。

空间复杂度：$O(n)$。

单个测试点最大用时：$265$ ms。

可以通过本题。


---

## 作者：bcbgszyzh (赞：1)

二〇二三年十一月二十七日最新版本

先来看最小步数，最小步数就是当前节点的深度，因为深度优先遍历可以直接向下遍历到该节点。再来看最大步数，最大步数是总节点数量减去以当前节点为根的子树的大小再加 $1$ ，加 $1$ 是为了把自己加回来，这个很好理解吧。

这些都有了，代码就很简单了。

注意：多组数据需要清空用到的数组。

AC code：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long c,n,x,y,ss[100010],step[100010];
vector<int>G[100010];
void dfs(int i,int fa){
	ss[i]=1;
	step[i]=step[fa]+1;
	for(auto j:G[i]){
		if(j==fa)continue;
		dfs(j,i);
		ss[i]+=ss[j];
	}
} 
int main(){
	scanf("%lld",&c);
	while(c--){
		scanf("%lld",&n);
		for(int i=1;i<=n;++i)G[i].clear();
		for(int i=1;i<n;++i){
			scanf("%lld%lld",&x,&y);
			G[x].push_back(y);
			G[y].push_back(x); 
		}
		dfs(1,0);
		for(int i=1;i<=n;++i)printf("%lld %lld\n",step[i],n-ss[i]+1);
	}
	return 0;
}
```

有任何问题请写在评论去我会来回复的。

---

## 作者：BugGod (赞：1)

首先考虑最小步数，显然，不绕弯路一路往下走到该点步数最小，这个步数也是该点的深度。再考虑最大步数，我们尽量不往这个点的方向走，先把其他的点溜达完，再往该点走。显然，我们除了该点的子树外，都可以逛一圈，所以答案为 $n-s_i+1$，$s_i$ 为 $i$ 子树的节点个数。

CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
void IOS()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
int lyh_AK_NOIP,n,x,y,ss[100010],step[100010];//step记录深度，ss记录子树节点个数
vector<int>G[100010];
void dfs(int i,int fa)
{
	ss[i]=1;
	step[i]=step[fa]+1;//往深一层
	for(auto j:G[i])//遍历子节点
	{
		if(j==fa)continue;
		dfs(j,i);
		ss[i]+=ss[j];//再加上子节点的子树节点个数
	}
}
void solve()
{
	cin>>n;
	for(int i=1;i<=n;i++)G[i].clear();//多测不清空，亲人两行泪
	for(int i=1;i<n;i++)
	{
		cin>>x>>y;
		G[x].push_back(y);
		G[y].push_back(x);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)cout<<step[i]<<' '<<n-ss[i]+1<<'\n';
}
signed main()
{
	cin>>lyh_AK_NOIP;
	while(lyh_AK_NOIP--)solve();
	return 0;
}
```

---

## 作者：_O_v_O_ (赞：0)

基础 dfs 题。

首先考虑最小，最优就是从根节点一条链搜下来，顺序就是点的深度。

再考虑最大，最劣是搜完其它子树再搜这个节点，只有这个点的子树搜不到，也就是为 $n-$ 该节点的深度。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int T;
int n;
vector<int> e[100005];
int dep[100005],siz[100005],late[100005];

void dfs(int x){
	siz[x]=1;
	for(auto i:e[x]){
		dep[i]=dep[x]+1;
		dfs(i);
		siz[x]+=siz[i];
		late[i]=n-siz[i]+1;
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++) e[i].clear();
		for(int i=1;i<n;i++){
			int u,v;
			cin>>u>>v;
			e[u].push_back(v);
			
		}
		dep[1]=1;
		late[1]=1;
		dfs(1);
		for(int i=1;i<=n;i++){
			cout<<dep[i]<<' '<<late[i]<<endl;
		}
	}
	return 0;
}
```


---

## 作者：Chenyichen0420 (赞：0)

# 简要题意

给你一棵树，有 $n$ 个节点，问你每一个节点在 DFS 序中的最早的可能访问时间和最晚的可能访问时间。从 $1$ 号节点开始遍历。

# 解法分析

对于每一个节点，显然他的最早访问时间为他的深度（$1$ 号节点深度为 $1$）。那么最晚呢？显然这个节点一定比以他为根节点的子树中的其他节点更先访问到，而除此以外的都一定可以比他更先访问到。所以他最晚的访问时间为 $n-siz[x]+1$，其中 $siz[x]$ 为以 $x$ 节点为根节点的子树的大小。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
int t,n,a,b,dep[100005],siz[100005];vector<int>son[100005];
inline void dfs(int pos,int fa){
	dep[pos]=dep[fa]+1,siz[pos]=1;
	for(int i=0;i<son[pos].size();++i)
		if(son[pos][i]!=fa)
			dfs(son[pos][i],pos),
			siz[pos]+=siz[son[pos][i]];
} 
int main(){
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--){
		cin>>n; 
		for(int i=1;i<=n;++i) son[i].clear();
		for(int i=1;i<n;++i)
			cin>>a>>b,
			son[a].pb(b),
			son[b].pb(a);
		dfs(1,0);
		for(int i=1;i<=n;++i)
			cout<<dep[i]<<" "<<n-siz[i]+1<<endl;
	} 
   return 0;
} 
```

---

