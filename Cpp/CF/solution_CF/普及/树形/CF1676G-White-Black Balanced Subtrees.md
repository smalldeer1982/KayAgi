# White-Black Balanced Subtrees

## 题目描述

You are given a rooted tree consisting of $ n $ vertices numbered from $ 1 $ to $ n $ . The root is vertex $ 1 $ . There is also a string $ s $ denoting the color of each vertex: if $ s_i = \texttt{B} $ , then vertex $ i $ is black, and if $ s_i = \texttt{W} $ , then vertex $ i $ is white.

A subtree of the tree is called balanced if the number of white vertices equals the number of black vertices. Count the number of balanced subtrees.

A tree is a connected undirected graph without cycles. A rooted tree is a tree with a selected vertex, which is called the root. In this problem, all trees have root $ 1 $ .

The tree is specified by an array of parents $ a_2, \dots, a_n $ containing $ n-1 $ numbers: $ a_i $ is the parent of the vertex with the number $ i $ for all $ i = 2, \dots, n $ . The parent of a vertex $ u $ is a vertex that is the next vertex on a simple path from $ u $ to the root.

The subtree of a vertex $ u $ is the set of all vertices that pass through $ u $ on a simple path to the root. For example, in the picture below, $ 7 $ is in the subtree of $ 3 $ because the simple path $ 7 \to 5 \to 3 \to 1 $ passes through $ 3 $ . Note that a vertex is included in its subtree, and the subtree of the root is the entire tree.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1676G/70fb6ac8a70942903450f21b07ea9969f086df2c.png) The picture shows the tree for $ n=7 $ , $ a=[1,1,2,3,3,5] $ , and $ s=\texttt{WBBWWBW} $ . The subtree at the vertex $ 3 $ is balanced.

## 说明/提示

The first test case is pictured in the statement. Only the subtrees at vertices $ 2 $ and $ 3 $ are balanced.

In the second test case, only the subtree at vertex $ 1 $ is balanced.

In the third test case, only the subtrees at vertices $ 1 $ , $ 3 $ , $ 5 $ , and $ 7 $ are balanced.

## 样例 #1

### 输入

```
3
7
1 1 2 3 3 5
WBBWWBW
2
1
BW
8
1 2 3 4 5 6 7
BWBWBWBW```

### 输出

```
2
1
4```

# 题解

## 作者：a1co0av5ce5az1cz0ap_ (赞：11)

来水一篇 div4 的题解，这是我人生第一次AK的CF比赛（虽然用了1h+）
## 一、题意
给你一棵根节点为 1 的树，每个节点的颜色都是黑或白（有点像红黑树？）。称一棵树是 **平衡的** 为这棵树里黑色节点的个数和白色节点的个数相同。问你在这棵树里，有多少子树是 **平衡的**？
## 二、思路
我们只要从根开始往下遍历每个孩子，在回溯的时候计算是否平衡即可。

怎么计算呢？我们让黑色的节点可以得到的分数为 1，白色的节点为 -1，就在往下遍历的时候把每一个孩子节点的分数加起来，再加上自己的分数。如果得到的总分数恰好为 0，那么答案就加一。
## 三、代码
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> v[4005];//存图
int color[4005];//记录每个节点的分数
int ans;//答案
int co(int rt){//遍历
	int sum=color[rt];//提前设为自己的分数
	for(int i=0;i<v[rt].size();i++) sum+=co(v[rt][i]);//依次加上孩子的分数
	if(sum==0) ans++;//又一个
	return sum;
}
int main(){
	int t,n,fa;char c;
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++) v[i].clear();//记得清空数组
		ans=0;
		for(int i=2;i<=n;i++){
			cin>>fa;//输入每个节点的父亲
			v[fa].push_back(i);//不要建双向边，没用
		}
		for(int i=1;i<=n;i++){
			cin>>c;
			if(c=='W') color[i]=-1;//白色
			else color[i]=1;//黑色
		}
		co(1);//根节点是1
		cout<<ans<<endl;//输出
	}
	return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/75829721)

---

## 作者：Coros_Trusds (赞：4)

比较简单的一道题。

# 题目分析

对于每个询问，一遍 $\rm dfs$ 统计出每个点的子树内黑点和白点的数量。最后扫描 $i(1\le i\le n)$，看以 $i$ 为根节点的子树中的黑点个数是否与白点个数相等，若相等计数器则 $+1$。

换句话说，答案就是 $\sum\limits_{i=1}^n[\operatorname{white-cnt}(i)=\operatorname{black-cnt}(i)]$。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> PII;

const int N = 4005;
struct Graph {
    int v,nxt;
} gra[N << 1];
int head[N];
PII col[N];
char s[N];
int T,n,idx;
inline void add(int u,int v) {
    gra[++ idx] = (Graph){v,head[u]},head[u] = idx;
}
inline void init() {
    memset(head,0,sizeof head),memset(col,0,sizeof col);
    idx = 0;
}
inline void dfs(int now,int fath) {
    if (s[now] == 'B') col[now].first = 1;
    else col[now].second = 1;
    for (register int i = head[now];i;i = gra[i].nxt) {
        int v = gra[i].v;
        if (v != fath) {
            dfs(v,now);
            col[now].first += col[v].first,col[now].second += col[v].second;
        }
    }
}
inline void solve() {
    scanf("%d",&n);
    for (register int i = 2;i <= n; ++ i) {
        int x;
        scanf("%d",&x);
        add(i,x),add(x,i);
    }
    scanf("%s",s + 1);
    dfs(1,0);
    int ans = 0;
    for (register int i = 1;i <= n; ++ i) {
//        cout << "vertex: " << i << ",black: " << col[i].first << ",white: " << col[i].second << "\n";
        if (col[i].first == col[i].second) {
            ans ++;
        }
    }
    printf("%d\n",ans);
}
int main(void) {
    cin >> T;
    while (T --) {
        init();
        solve();
    }

    return 0;
}
```

---

## 作者：Withers (赞：2)

[题目传送门](https://codeforces.com/contest/1676/problem/G)
# 题目大意
给出一颗树，每个节点有两种颜色，求在所有节点里，包括它自己的子树中黑色和白色数量相等的节点个数。

# 思路
模板树形dp，每个节点存子树中黑色的数量和白色的数量。直接 dfs 遍历所有节点，处理每个节点子树中黑色节点和白色节点数量加在自己的身上，最后判断一下是否满足性质，把可以的个数即可。

具体的：

$dp_{u,b}=\sum dp_{v,b}+s$，在 $v\in u$ 的情况下，其中 $s$ 是这个节点是否为黑色

$dp_{u,w}=\sum dp_{v,w}+s$，在 $v\in u$ 的情况下，其中 $s$ 是这个节点是否为黑色

最后判断 $dp_{u,w}$ 是否等于 $dp_{u,b}$ 就可以了
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int b,w;
} k[4010];
int n,x;
vector<int> g[4010];
char s[200010];
void dfs(int u,int fa)
{
	for(int i=0;i<g[u].size();i++)
	{
		int to=g[u][i];
		if(to==fa) continue;
		dfs(to,u);
		k[u].b+=k[to].b,k[u].w+=k[to].w;
	}//板子树形dp，遍历每个节点
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++) k[i].b=k[i].w=0;
		for(int i=1;i<=n;i++) g[i].clear();
		for(int i=1;i<n;i++)
		{
		
			scanf("%d",&x);
			g[x].push_back(i+1);//建边
		}
		scanf("%s",s+1);
		for(int i=1;i<=n;i++)
		{
			if(s[i]=='B') k[i].b=1;
			else k[i].w=1;
		}//初始化
		dfs(1,1);
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			if(k[i].b==k[i].w) 
			{
				ans++;
			}
		}//判断加和
		printf("%d\n",ans);
	}
}
```


---

## 作者：5k_sync_closer (赞：2)

# 题意
给定一棵树，点有黑白之分。

问这棵树有多少个黑白结点数量相同的子树。
# 思路
令以 $x$ 为根的子树中黑白结点的个数分别为 $s[x][0/1]$。

则 $s[x][0]=\sum s[v][0]+(x\ \text{is black})$，$s[x][1]=\sum s[v][1]+(x\ \text{is white})$（$v$ 是 $x$ 的子结点）。

如果 $s[x][0] = s[x][1]$，那么以 $x$ 为根的子树是平衡的。
# 代码
```cpp
#include <cstdio>
#include <cstring>
struct E{int v, t;}e[4050];int T, n, q, c, h[4050], s[4050][2];
void add(int u, int v) {e[++c] = {v, h[u]};h[u] = c;}
int g() {char c = getchar();while(c != 'W' && c != 'B') c = getchar();return c == 'W';}
void dfs(int x)
{
    for(int i = h[x], v;i;i = e[i].t)
        v = e[i].v, dfs(v), s[x][0] += s[v][0], s[x][1] += s[v][1];
    if(s[x][0] == s[x][1]) ++q;
}
int main()
{
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);c = q = 0;memset(e, 0, sizeof e);
        for(int i = 1;i <= n;++i) h[i] = s[i][0] = s[i][1] = 0;
        for(int i = 2, t;i <= n;++i) scanf("%d", &t), add(t, i);
        for(int i = 1;i <= n;++i) s[i][g()] = 1;
        dfs(1);printf("%d\n", q);
    }
    return 0;
}
```


---

## 作者：_JF_ (赞：1)

## CF1676G White-Black Balanced Subtrees 

$\mathit{dp}_{i,j}$
考察树的遍历。

题目翻译有一个没有翻译到，就是输入的第二行，输入的是 $i+1$ 到 $n$ 的根节点。

第三行是一个字符串，我们可以对 $siz_{i}$ 进行初始化了。

$siz[i]$ 表示以 $i$ 为根，其的子树下面有多少个黑色结点，多少个白色结点。

其中 $\mathit {siz}_{i,black}$ 即它的子节点为黑的和，$\mathit {siz}_{i,white}$ 为子节点为白色的和，最后在回溯之中统计即可。

最后看每个 $i$ 的黑色结点的数量是否等于白色结点即可。

注意多测清空。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
vector<int> g[N<<1];
struct node
{
	int black=0,white=0;
}siz[N];
int ans;
void dfs(int u,int fath)
{
	for(int i=0;i<g[u].size();i++)
	{
		int v=g[u][i];
		if(v==fath)
			continue;
		dfs(v,u);
		siz[u].black+=siz[v].black,siz[u].white+=siz[v].white; 
	}
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		ans=0;
		cin>>n;
		for(int i=2,u;i<=n;i++)
			cin>>u,g[u].push_back(i);
		for(int i=1;i<=n;i++)
		{
			char k;
			cin>>k;
			if(k=='W')
				siz[i].white=1;
			else
				siz[i].black=1; 
		}
		dfs(1,0);
		for(int i=1;i<=n;i++)
			if(siz[i].black==siz[i].white)
				ans++; 
		cout<<ans<<endl;
		for(int i=1;i<=n;i++)
			g[i].clear(),siz[i].black=siz[i].white=0;
	}
	return 0;
}
 
```




---

## 作者：Deamer (赞：1)

题意：

有一棵根节点为 1 的树，每个结点有一种颜色，或白，或黑。让我们求，在所有节点中，有多少个结点（包括自己）和它所有子树的黑白颜色总和相等。

我们来考虑：

每个结点的黑白总合来自于它本身的颜色加上它所有子结点的黑白总数之和。换句话说，每个结点的黑白总合肯定会影响到它的父亲黑白总和（ 1 除外）。那我们就用子节点的值更新父节点的值就行了。

用子节点更新父节点，这像什么？这是不是就是 DFS 时的回溯操作？

我们来想想 DFS ，它是搜到最底层，就一层一层的向上回溯。换到这个题中就是搜到叶子节点就一层一层向上更新。因为叶子节点没有子节点，它的黑白总和就是本身颜色。

所以我们跑一遍 DFS 就行了。

**~~reader : talks are cheap, show me the code!!!~~**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e3+10;
int T,n;
int b[N],w[N];
char s[N];
vector<int>G[N];
int ans;

void DFS(int u,int fa){
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(v==fa) continue;
        DFS(v,u);
        b[u]+=b[v]; w[u]+=w[v];
    }
}

int main(){
    scanf("%d",&T);
    while(T--){
        ans=0;
        int x;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            G[i].clear();
            b[i]=w[i]=0;
        }
        for(int i=2;i<=n;i++){
            scanf("%d",&x);
            G[x].push_back(i);
        }
		cin>>(s+1);
		for(int i=1;i<=n;i++){
			b[i]=(s[i]=='B');
			w[i]=(s[i]=='W');
		}
        DFS(1,1);
        for(int i=1;i<=n;i++){
        	if(b[i]==w[i]) ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}
```
我们想一想，我们 DFS 是不是从叶子结点开始回溯。那我们直接从叶子结点倒搜行不行呢？

- 如果从叶子结点倒搜时只回溯加上叶子结点的值，那些不是叶子结点的值就没有被回溯回去。

- 如果从叶子结点倒搜时加上当前搜索到的结点的黑白总和，这样就考虑到了不是叶子结点的值。但会重复计算，举个例子：一个结点有两个子结点，这两个子节点往上倒搜时都会加上这个结点的值，这样就重复计算了。

DFS 正好可以解决以上问题。

那如果想倒搜的话，只能每个结点都往上倒搜一遍了，那就慢多了。

还是把代码附上吧……

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e3+10;
int T,n;
int f[N],b[N],w[N];
char s[N];
int ans;

void DFS(int u,int x){
	w[f[u]]+=w[x];
	b[f[u]]+=b[x];
	if(f[u]!=1) DFS(f[u],x);
}

int main(){
	scanf("%d",&T);
	while(T--){
		ans=0;
		char ch;
		scanf("%d",&n);
		for(int i=1;i<=n;i++) b[i]=w[i]=0;
		for(int i=2;i<=n;i++) scanf("%d",&f[i]);
		cin>>(s+1);
		for(int i=1;i<=n;i++){
			b[i]=(s[i]=='B');
			w[i]=(s[i]=='W');
		}
		for(int i=2;i<=n;i++) DFS(i,i);
		for(int i=1;i<=n;i++){
			if(b[i]==w[i]) ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```
[DFS](https://www.luogu.com.cn/record/75768176)

[倒搜](https://www.luogu.com.cn/record/75758641)



---

## 作者：Jadebo1 (赞：1)

### 题目大意
每个节点均为白色和黑色中的一种，求子树（包含自己）中黑色和白色数量相同的节点数。
### 解题思路
建立一个 $col$ 数组，记录每个节点的颜色 ( 将黑色赋为 $-1$，白色为 $1$ )

然后从根节点开始 $dfs$ ，使 $col_{now}$ 加上  $col_{son}$ ,最后只需要在 $dfs$ 结束后统计 $col_{now}$ 是否为零即可

**ps:由于是多组数据，所以一定要记得将变量清零**

### 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define cf int _;cin >> _; while (_--)
#define f(i, l, r) for (int i = l; i <= r; i++)
#define F(i, r, l) for (int i = r; i >= l; i--)
#define endl "\n"
const int N = 4000 + 3;
int head[N], col[N], tot, siz[N];
int res;
struct node
{
    int ne, to;
} e[N];
void add(int u, int v)
{
    e[++tot].ne = head[u];
    e[tot].to = v;
    head[u] = tot;
}
void dfs(int now, int fa)
{
    for (int i = head[now]; i; i = e[i].ne)
    {
        int v = e[i].to;
        if (v == fa)
            continue;
        dfs(v, now);
        col[now] += col[v];
    }
    if (!col[now])
        res++;
}
void solve()
{
    memset(e, 0, sizeof(e));
    memset(head,0,sizeof(head));
    tot=0,res=0;
    int n;
    cin >> n;
    f(i, 2, n)
    {
        int v;
        cin >> v;
        add(v, i);
    }
    string s;
    cin >> s;
    f(i, 0, n - 1)
    {
        if (s[i] == 'W')
            col[i + 1] = 1;
        else
            col[i + 1] = -1;
    }
    dfs(1, 0);
    cout << res << endl;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cf
    {
        solve();
    }
}
```

---

## 作者：Engulf (赞：1)

通过一次 dfs 处理出每个节点所在的子树中黑色节点和白色节点个数，再进行统计。

```cpp
// author: TMJYH09
// create time: 2022/05/10 23:50:09
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

const int N = 4005;
struct edge{
    int to,nxt;
}e[N<<1];
int head[N],idx;
void add(int x,int y){
    e[++idx]={y,head[x]};
    head[x]=idx;
}
char col[N];
int n;

int black[N],white[N];

void dfs(int u,int fa){
    if(col[u]=='B')black[u]=1;
    if(col[u]=='W')white[u]=1;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;
        if(v!=fa){
            dfs(v,u);
            black[u]+=black[v];
            white[u]+=white[v];
        }
    }
}


void init(){
    idx=0;
    for(int i=1;i<=n;i++)head[i]=0,col[i]=' ',black[i]=white[i]=0;
}

void solve(){
    init();
    cin>>n;
    for(int i=2,x;i<=n;i++){
        cin>>x;add(i,x);add(x,i);
    }
    for(int i=1;i<=n;i++)cin>>col[i];
    dfs(1,0);
    int ans=0;
    for(int i=1;i<=n;i++){
        //cout<<"i = "<<i<<' '<<black[i]<<' '<<white[i]<<endl;
        if(black[i]==white[i])ans++;
    }
    cout<<ans<<endl;
}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int _;cin>>_;while(_--)solve();
    return 0;
}
```

---

## 作者：_Revenge_ (赞：0)

### 题目简化和分析：  

求一颗子树的黑白两数是否相等。  

我们设黑 $1$，白 $-1$，若某一棵子树的权值为 $0$，说明此刻的黑白个数相等，贡献加一。   

从根搜索，每次将值传递给父亲，判断父亲此时的权值。   

### Solution:

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef double db;

const int N=4e3+50;
const int M=1e5+50;
const int Mod=1e9+7;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}

int t,n;
int ans;
int c[N],si[N];
vector<int>tree[N];

void dfs(int u,int p){
	si[u]=c[u];
	for(int v=0;v<(int)tree[u].size();++v){
		if(tree[u][v]==p) continue;
		dfs(tree[u][v],u);
		si[u]+=si[tree[u][v]];
	}
	if(si[u]==0) ans++;
}
int main()
{
	scanf("%d",&t);
	while(t--){
		ans=0;
		n=read();
		for(int i=2;i<=n;++i){
			int x;
			x=read();
			tree[x].push_back(i);
			tree[i].push_back(x);
		}
		string s;
		cin>>s;
		for(int i=0;i<n;++i){
			if(s[i]=='W') c[i+1]=-1; else c[i+1]=1;
		}
		dfs(1,0);
		printf("%d\n",ans);
		for(int i=1;i<=n;++i) tree[i].clear();
	}
	return 0;
}

```

---

