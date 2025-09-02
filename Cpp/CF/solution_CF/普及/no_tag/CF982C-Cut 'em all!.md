# Cut 'em all!

## 题目描述

现在有一棵有N个节点的树，你可以删去树中的一些边使其成为森林，你的任务是删去最多的边使得每一棵森林中的树的大小为偶数，并输出删去的边数。

## 样例 #1

### 输入

```
4
2 4
4 1
3 1
```

### 输出

```
1```

## 样例 #2

### 输入

```
3
1 2
1 3
```

### 输出

```
-1```

## 样例 #3

### 输入

```
10
7 1
8 4
8 10
4 7
6 5
9 3
3 5
2 10
2 5
```

### 输出

```
4```

## 样例 #4

### 输入

```
2
1 2
```

### 输出

```
0```

# 题解

## 作者：acup (赞：5)

```cpp
/*
如果给出的点的个数是奇数，
无论怎么删除边都不会产生全是偶数的连通子树，输出-1。
如果给出的点的个数是偶数，
对于每一个结点u,父结点为v，
u及其子树的结点总数为偶数的话就可以删除e(u,v)，
因为偶数-偶数还是偶数，统计所有这样的结点个数即可。
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
vector<int>G[maxn];
int ans[maxn],vis[maxn];
int dfs(int x){
    for(int i = 0; i < G[x].size(); i++){
        int u = G[x][i];
        if(!vis[u]){
            vis[u] = 1;
            ans[x] += dfs(u);
            vis[u] = 0;
        }
    }
    ans[x]++;//加上自己 
    return ans[x];
}
int main(){
    int n;
    cin>>n;
    for(int i = 1; i <= n - 1; i++){
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v);
        G[v].push_back(u);
    } 
    if(n % 2)
        printf("-1\n");
    else{
		vis[1] = 1;
		dfs(1);
        int cnt = 0;
        for(int i = 1; i <= n; i++){
            if(ans[i] % 2 == 0)
                cnt++;
        }
        cout<<cnt - 1<<endl;
    }
    return 0;
}
```

---

## 作者：lichenghan (赞：2)

~~作者想要橙名，于是有了这篇题解。。。~~

# CF982C
简单的树上问题。
### 思路
首先，当 $n$ 为奇数时，肯定没有答案（无论如何都有一个子树有奇数个点），输出 $-1$ 即可。

然后，我们不难发现，对于一个节点 $u$ ，
如果它子树的节点个数 $siz_u$ 是奇数，则 $u$ 与其父亲节点的边就不能删去（删去的话那么这棵子树就变成了点数为奇数的树，就没有答案了），反之则可以删去。

那么，我们就可以用一次 $dfs$ 求出每一个 $siz_u$，最后统计一下 $siz_u$ 为奇数的点数就可以了。
### 小坑
- 根节点没有父亲，需要特判
### code

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
int n;
vector<int> g[100001];
int siz[100001];
void dfs(int u,int fa){//dfs求子树大小
	siz[u]=1;
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==fa) continue;
		dfs(v,u);
		siz[u]+=siz[v];
	}
}
int main(){
	scanf("%d",&n);
	if(n%2){puts("-1");return 0;}//n为奇数
	int u,v;
	for(int i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1,1);
	int  ans=0;
	for(int i=1;i<=n;i++){//统计答案
		if(siz[i]%2==0){
			ans++;
//			printf("%d\n",i);
		}
	}
	printf("%d",ans-1);//特判根节点
}

---

## 作者：Edmundino (赞：2)

# 分析

这是一题很不错的树上dp的题目

竟然是dp，就有一定的转移方程

首先，当它是有奇数个点的时候，肯定是输出-1的

所以我们只要考虑偶数个点的情况

我们可以通过分析（就是分析样例）

发现当以一个节点为根节点的子树中有偶数个节点时

那么他与他父亲节点的那一条边便可删去

最后我们可以得出要删去的边数

但是，最后输出时要减1（因为根节点没有父亲节点）

所以怎么求子树的个数呢？

就是用树上dfs与dp结合

方程便为f[u]=
∑f[v]+1;

# 代码

dfs代码

```cpp
void dfs(int u)
{
    int lon=vec[u].size();
    bo[u]=1;
    for(int i=0;i<lon;i++)
    {
        int v=vec[u][i];
        if(bo[v]==0)
        {
            dfs(v);
            siz[u]+=siz[v];
        }
    }
    siz[u]+=1;
    return;
}

```
bo数组是防止逆查找

siz数组就是上面说的f数组

vec是一个vector；

最后送上完整AC代码


```cpp
#include<iostream>
#include<algorithm>
#include<iomanip>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<vector>

using namespace std;

const int N=100000+50;

vector<int>vec[N];

int n,s,x,y,siz[N];

bool bo[N];

void dfs(int u)
{
    int lon=vec[u].size();
    bo[u]=1;
    for(int i=0;i<lon;i++)
    {
        int v=vec[u][i];
        if(bo[v]==0)
        {
            dfs(v);
            siz[u]+=siz[v];
        }
    }
    siz[u]+=1;
    return;
}

int main()
{
    cin>>n;
    for(int i=2;i<=n;i++)
    {
        cin>>x>>y;
        vec[x].push_back(y);
        vec[y].push_back(x);
    }
    if(n%2==1)
    {
        cout<<-1;
        return 0;
    }
    dfs(1);
   for(int i=1;i<=n;i++)
   {
       if(siz[i]%2==0)
         s++;
   }
   cout<<s-1;
   return 0;
}
```


---

## 作者：CSPAK_Zhangxiuqi0011 (赞：1)

#  CF982C Cut 'em all! 题解
## 0.  前言
本蒟蒻个人认为本题不难，但是我旁边的[某位大佬](https://www.luogu.com.cn/user/910530)~~又~~挂了硬是调不出来，所以我决定写一篇题解帮帮 Ta。还有，因为最近 CF 加强了一下那个什么东西，导致洛谷爬虫爬不到提交记录，所以洛谷提交不了，只能在 [vjudge](https://vjudge.net/) 上面提交。[提交记录。](https://vjudge.net/status#un=CSPAKZXQ&OJId=CodeForces&probNum=982C&res=0&language=&onlyFollowee=false)  
## 1.  题目
~~这能算一块内容吗~~[题目传送门。](https://www.luogu.com.cn/problem/CF982C)  
## 2.  前置芝士
知道什么是树的大小是什么的大佬就可以跳过了。  
首先，森林都知道是什么吧（就是若干个树的集合）。  
然后，到了我们这块内容的重头戏：什么是树的大小。  
树的大小定义很简单：一棵树上节点的个数叫做树的大小。如图：  
![](https://cdn.luogu.com.cn/upload/image_hosting/g4lmgnyi.png)  
这棵树的大小就是 $6$。
## 3.  思路
首先，如果总节点数量是奇数，那么肯定不能分成大小全是偶数的若干个子树（奇数减偶数还是奇数嘛）。  
接下来我们就需要考虑总结点数量是偶数的情况了。  
首先，定义 $dp_i$ 为以 $i$ 号节点为根的子树的大小。然后，我们可以分情况讨论：  
1. $dp_i$ 为偶数。  
当 $dp_i$ 是偶数的时候，意味着这时候断开 $i$ 号节点和他父亲的边，是依旧满足要求的，此时可以统计答案。  
2. $dp_i$ 为奇数。  
当 $dp_i$ 是奇数的时候，此时不能断开 $i$ 号节点和他父亲的边。

综上所述，我们就可以写代码了？  
NO！！！如果你直接按照这个思路写代码的话，你会很遗憾地比 AC 答案多一个。那么为什么呢？因为**根节点是没有父亲的，但是我们在累加答案的时候把根节点的情况也累加进去了，所以需要减去** $1$。
## 4.AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,son[100005];
vector<int>ve[100005];
void dfs(int now,int fa){
	son[now] = 1;
	int l;
	l = ve[now].size();
	for(int i = 0;i<l;i++){
		if(ve[now][i] == fa){
			continue;
		}
		dfs(ve[now][i],now);
		son[now] = son[now]+son[ve[now][i]];
	}
}
signed main(){
	cin>>n;
	for(int i = 1;i<n;i++){
		int u,v;
		cin>>u>>v;
		ve[u].push_back(v);
		ve[v].push_back(u);
	}
	if(n%2){
		cout<<"-1\n";
		return 0;
	}
	dfs(1,0);
	int ans;
	ans = -1;
	for(int i = 1;i<=n;i++){
		if(son[i]%2 == 0){
			ans++;
		}
	}
	cout<<ans<<"\n";
	return 0;
}

```

---

## 作者：bitset_iTM (赞：1)

### 思路：  
显然，当整个树的节点数为奇数时，不存在可以删除的边。  
现在我们来考虑有解时的情况。  
不难想出，对于任意一个点，如果她的所有子节点数（包括她自己）为偶数，那么我们就可以删除这个点和她的父节点之间的那条边。也就是说，我们只要求出这些点的数量，然后 _减一_ ，就是我们要求的边的数量啦~！  


### Code：
------------
```cpp
/* 第一次写题解，求通过 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;

vector<int> g[maxn]; //邻接表存图
int p[maxn], vis[maxn];

int dfs(int u)
{
    for (int i = 0; i < g[u].size(); i++)
    {
        int v = g[u][i];
        if (!vis[v]) //如果没访问过这个点，搜索
        {
            vis[v] = 1;
            p[u] += dfs(v);
            vis[v] = 0; //回溯
        }
    }

    return p[u]; //返回
}

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        
        g[u].push_back(v);
        g[v].push_back(u); //将两点当作无向图处理
    }
    
    if (n & 1) //n为奇数时无解
    {
        puts("-1"); //输出-1
        return 0;
    }
    
    memset(p, 1, sizeof(p)); //每个点的子树节点树要包含自己
    vis[1] = 1;
    dfs(1); //爆搜
    int res = 0;
    for (int i = 1; i <= n; i++)
        if (!(p[i] & 1)) //p[i]为偶数时，说明找到了一个符合我们刚刚分析的条件的点i
            res++;
    
    printf("%d\n", res - 1); //边=点-1
    return 0; //完美地结束qwq
}

```


---

## 作者：Kevin_Zhen (赞：1)

题目链接 [$\mathfrak{CF982C}$](https://www.luogu.com.cn/problem/CF982C)。

### 解题核心
奇数减去偶数仍是奇数，偶数减去偶数仍是偶数。所以减掉偶数并不影响一个数的奇偶性。

### 思路
显然如果总点数为奇数，无论如何切分，一定会有奇数大小的子树。因为切去的结点有偶数个，不影响剩余结点的奇偶性。所以如果 $n$ 为奇数，直接输出 $-1$。

对于每一个结点 $u$，如果它的子树大小为偶数，那么可以切去它与它的父亲结点之间的连边，且不会影响剩余结点的奇偶性；若子树大小为奇数，则无法切分。因此，可以统计每一棵子树的大小，累加偶数大小的子树个数。**特别地，不要累加上根结点所在子树，因为根结点没有父亲结点**。

### AC CODE
```cpp
#include <iostream>
#include <cstdio>
using namespace std;

const int maxn = 1e5 + 10;

struct Edge {
	int u, v, nxt;
} edge[maxn << 1]; int head[maxn], tot;

inline void init(int u, int v) {
	edge[++tot] = (Edge){ u, v, head[u] }; head[u] = tot;
}

int n, ans, siz[maxn];

void dfs(int u, int fa) {
	siz[u] = 1;
	for (int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].v;
		if (v == fa) continue;
		dfs(v, u);
		siz[u] += siz[v];
	}
}

int main() {
	scanf("%d", &n);
	if (n & 1) { printf("-1"); return 0; }
	for (int i = 1; i < n; ++i) {
		int p1, p2; scanf("%d%d", &p1, &p2);
		init(p1, p2); init(p2, p1);
	}
	dfs(1, n + 1);
	for (int i = 2; i <= n; ++i) if (!(siz[i] & 1)) ++ans;
	printf("%d", ans);
	return 0;
}
```
### 感谢观赏！

---

## 作者：Tiago (赞：1)

## Solution

容易想到如果 $n$ 为奇数，一定不可以（因为奇数不管怎么拆分成偶数总会剩下一个奇数），所以输出直接判定无解。

接下来只用考虑 $n$ 为偶数的情况。

题目要求要使每一颗森林中的树的大小要为偶数，即儿子数（自己也要算上）为偶数的节点均可删除其与父亲节点的连边使得构造出的树的大小为偶数。

所以只需要 DFS 预处理儿子数，然后统计有多少个偶数即可。

注意根节点不能算，因为它没有父亲节点。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define For(i,a,b) for(int i=(a);i<=(b);i++)
#define FOR(i,a,b) for(int i=(a);i>=(b);i--)
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)

const int N=1e5+4;
int n,sontot[N],ans;
bool vis[N];
vector<int> E[N];
void dfs(int x)
{
	sontot[x]=1;
	for(auto i:E[x])
		if(vis[i]==0)
		{
			vis[i]=1;
			dfs(i);
			sontot[x]+=sontot[i];
		}
}
int main()
{
	IOS;
	cin>>n;
	if(n%2==1)return cout<<"-1",0;
	For(i,1,n-1)
	{
		int u,v;cin>>u>>v;
		E[u].push_back(v);
		E[v].push_back(u);
	}
	vis[1]=1;
	dfs(1);
	For(i,2,n)if(sontot[i]%2==0)ans++;
	cout<<ans;

	return 0;
}
```


---

## 作者：FiraCode (赞：1)

## 题解思路：
当节点数是奇数的时候，连通块内一定会有一个是奇数个点，所以一定无解。

那么节点数是偶数的时候，我们对于每条边来说，当他连着的部分有奇数个点，那么这条边一定不能删，若都是偶数个点，那么就要删掉。

那么我们就一遍 dfs 判断他们两边的点的个数来判断删或不删就可以了。

## AC CODE:
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 100010, M = N * 2;
int n;
int ans;//表示一共可以删除多少条边
int h[N], e[M], ne[M], idx;
void add(int a, int b) {
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
int dfs(int u, int fa) {
	int sz = 1;
	for (int i = h[u]; ~i; i = ne[i]) {
		int j = e[i];
		if (j != fa) {
			int s = dfs(j, u);
			if (!(s & 1)) ans++;//是偶数个点，那么就可以删
			sz += s;//统计长度
		}
	}
	return sz;
}
int main() {
	scanf("%d", &n);
	if (n & 1) {//无解
		puts("-1");
		return 0;
	}
	memset(h, -1, sizeof(h));
	for (int i = 2; i <= n; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		add(a, b);
		add(b, a);
	}
	dfs(1, -1);//dfs
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：ny_Dacong (赞：0)

# 思路

对于一个节点 $u$ ，如果以 $u$ 为根的子树的节点数（连同它自己）是偶数，那么我们就可以删去 $u$ 与他父节点所连的边。

所以我们先跑 DFS，计算出每个点的子节点个数。然后枚举即可。

注意，根节点没有父亲，要特判。

# AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans = 0;
int etot = 0,Last[200005],Next[200005],End[200005];
int sontot[200005];
void addedge(int u,int v){
	etot++;
	Next[etot] = Last[u];
	Last[u] = etot;
	End[etot] = v;
}
void totson(int now,int fa){
	sontot[now] = 1;
	for(int i = Last[now]; i; i = Next[i]){
		if(End[i] != fa){
			totson(End[i],now);
			sontot[now] += sontot[End[i]];
		}
	}
}
int main(){
	scanf("%d",&n);
	if(n%2){
		printf("-1");
		return 0;
	}
	for(int i = 1; i < n; i++){
		int tpa,tpb;
		scanf("%d%d",&tpa,&tpb);
		addedge(tpa,tpb);
		addedge(tpb,tpa);
	}
	totson(1,0);
	for(int i = 1; i <= n; i++){
		if(sontot[i]%2 == 0){
			ans++;
		}
	}
	printf("%d",ans-1);
	return 0;
} 
```

---

## 作者：zhouzihang1 (赞：0)

# CF982C Cut 'em all! 题解

[洛谷传送门](https://www.luogu.com.cn/problem/CF982C)

[CF 传送门](https://codeforces.com/problemset/problem/982/C)

[文章区链接](https://www.luogu.com.cn/article/trxxutuo)

## 题意

给出 $n$ 个点 $n-1$ 条边的树，问这棵树最多可以删掉几条边使每部分都是 $2$ 的倍数。

如果不能，输出 $-1$。

## 思路

![](https://cdn.luogu.com.cn/upload/image_hosting/jc36gpe6.png)

对于这棵树，把 $1$ 号店看做根节点，使用树形 dp 计算叶子结点到当前节点的节点数。

显然，$3,9$ 可以分为一组，$5,6$ 分为一组，$2,10$ 分为一组，$4,8$ 分为一组，$1,7$ 分为一组。

这样子，就可以断掉 $4$ 条边。

这么一说就很好想了，就是判断当前能不能分，能分就分。~~废话~~

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e5+10;
int n,ans,f[N];
vector<int> vc[N];//邻接表 
void dfs(int u,int fa)
{
	f[u]=1;
	for(int v:vc[u])
	{
		if(v==fa) continue;//不能向上走 
		dfs(v,u);
		if(f[v]%2==0) f[v]=0,ans++;//能分就分 
		f[u]+=f[v];
	}
}
int main()
{
	scanf("%d",&n);
	if(n&1)
	{
		printf("-1");
		return 0;
	}//特判 
	for(int i=1,u,v;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		vc[u].push_back(v);
		vc[v].push_back(u);//建双向边 
	}
	dfs(1,-1);
	printf("%d",ans);
	return 0;
}
```

---

## 作者：dhpzy (赞：0)

这是一道深搜题。
# 思路
- 如果点的数量为奇数，那么无论如何怎么样删都无解，输出 $-1$ 即可。
- 之后我们会发现，如果一个节点有奇数棵树，那么就不可以删去，否则因为偶数减偶数还是偶数，所以当一个节点有偶数棵子树时，就可以删去。
- 所以，这题可以用 dfs 来求每个点的子树量，然后再判断是否为偶数便可。

# Code
```
#include<bits/stdc++.h>
using namespace std;
int a[1000001],s,n;
bool b[1000001];
vector<int>g[1000001];
int dfs(int x)
{
	for(int i=0;i<g[x].size();i++)
		if(!b[g[x][i]])
		{
			b[g[x][i]]=1;
			a[x]+=dfs(g[x][i]);
			b[g[x][i]]=0;
		}
	return ++a[x];
}
int main()
{
	cin>>n;
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	if(n&1) cout<<-1;
	else{
		b[1]=1;
		dfs(1);
		for(int i=1;i<=n;i++)
			if(a[i]%2==0) s++;
		cout<<s-1;
	}
}
```


---

