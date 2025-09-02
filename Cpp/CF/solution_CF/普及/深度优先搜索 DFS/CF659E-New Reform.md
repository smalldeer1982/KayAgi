# New Reform

## 题目描述

有 $n$ 个城市，$m$ 条双向道路，没有一个城市存在自己到自己的道路，两个不同的城市间，最多有一条道路，也不能保证能从一个城市到达任意一个其他城市。

现在需要对每一条道路定向，使之成为单向道路，当然需要尽可能少地产生孤立的城市。当其他所有城市都不能到达某个城市，则称这个城市为孤立城市。要求出最少的孤立城市的个数。

## 样例 #1

### 输入

```
4 3
2 1
1 3
4 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5 5
2 1
1 3
2 3
2 5
4 3
```

### 输出

```
0
```

## 样例 #3

### 输入

```
6 5
1 2
2 3
4 5
4 6
5 6
```

### 输出

```
1
```

# 题解

## 作者：dunko (赞：13)

luogu CF659E

看到是xukuan大佬翻译的，同市蒟蒻来写一写题解。

##**题目**

自己去看吧~~

##**思路**

看完题目后想到了去找**环**，如果不是环的话就一定有一个城市是孤立城市。但是因为是一个蒟蒻，写了好久的爆搜都未AC，一怒之下放弃了搜索，转而是用**并查集**来找环，这样题目就好写多了吗。（看到题解中只有xukuan大佬写了一份爆搜，自己也想来尝试一下）

都说到了是并查集，那一定要去看一看模板再马上开始写题。

之后附上带有蒟蒻注释的AC代码

##**代码**

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int n,m,ans,fa[100001];
bool mark[100001];
int find(int x){//并查集基础知识：找爸爸
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}
int main(){
    cin>>n>>m;//输入
    for(int i=1;i<=n;i++) fa[i]=i;//初始化，自己的爸爸是自己
    for(int i=1;i<=m;i++){
        int x,y;
        cin>>x>>y;//输入
        int fx=find(x),fy=find(y);//找到这条边的两个点的祖先
        if(fx!=fy){//归并，将一个点的祖先改为另一个点的祖先
        	fa[fx]=fy;
        	if(mark[fx]||mark[x]||mark[fy]||mark[y])
            //如果这四者中有一个被标记了，那全部都是被标记状态
        	mark[fx]=mark[x]=mark[fy]=mark[y]=1;
		}
		else mark[fx]=mark[x]=mark[fy]=mark[y]=1;//将全员标记
    }
    for(int i=1;i<=n;i++)
    if(find(i)==i&&!mark[i]) ans++;//找不在环中的点，数数
    cout<<ans<<endl;//输出
    return 0;
}
```
结束了，这是一道~~不~~难的题目，主要是想到判断是否是环。

88

Thanks for your coming.(蒟蒻嘤语不好，勿怪)

---

## 作者：liu_chen_hao (赞：11)

题目：luogu CF659E

## 分析
我们可以得到几个显然的结论：

1. 如果若干个点可以构成环，那么这些点可以做到不出现孤立城市。（依次相连即可）

2. 一颗单独的树型结构，至少出现1个孤立城市。（就是根）

3. 如果一棵树与一个环相连，那么这棵树与这个环构成的图，可以做到不出现孤立城市。（树根也可达了）

## 实现
一个标记数组 $v$，$v[i]$ 记录 $i$ 是否属于情况 $1$，$3$。

利用并查集这种数据结构，每读入一对点，判断他们是否在一个集合中，若果在，那么这个集合对应的图一定构成了环，则把总代表标记为 $1$；否则，合并这两个点，如果其中任意一个点的总代表的的 $v$ 为 $1$，则说明其集合所对应的图中已找出了环，就再把合并后集合的总代表标记为 $1$。

最后扫描所有总代表，其中未被标记的个数就是答案。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int n,m,ans;
int fa[100005];
bool v[100005];

// 寻找总代表 
int find(int x)
{
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i=1; i<=n; i++) fa[i]=i;   // 初始化并查集 
	for(int i=1; i<=m; i++)
	{
		int x,y;
		scanf("%d%d", &x, &y);
		int xx=find(x);
		int yy=find(y);
		if(xx==yy) v[xx]=1;  // 构成环，总代表标记为1 
		else
		{
			fa[xx]=yy;   // 合并 
			if(v[xx] || v[yy]) v[yy]=1;  // 若之前已找到过环，就把总代表标记为1 
		}
	}
	for(int i=1; i<=n; i++)
		if(find(i)==i && !v[i]) ++ans;   // 满足find(i)==i的点是总代表点，满足!v[i]的点属于情况2 
	printf("%d", ans);

	return 0;
}
```


---

## 作者：Stream月 (赞：4)

~~这题为什么是E题啊~~

图论小性质题目

分类讨论一下

![CF659E环](https://cdn.luogu.com.cn/upload/image_hosting/clynhn20.png)

如图，我们可以像基环外向树一样，环上的点围成一圈，然后其他边由环上的点指出，那么这个连通块中不存在入度为0的点，有多个环也一样。

![CF659E树](https://cdn.luogu.com.cn/upload/image_hosting/x162fwfd.png)

连通块内无环，那么它是一棵树，随便选一个根，由根指向儿子，儿子再指向它自己的儿子，整个连通块中只有根节点入度为0，对答案贡献为1

dfs一下就做完了

时间复杂度：$O(n + m)$

喜闻乐见的代码实现：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long ll;

using namespace std;
#define $(i,a,n) for(int i = a; i <= n; ++i)

inline ll read() {
	   ll ans = 0;
	   char last = ' ',ch = getchar();
	   while(ch < '0' || ch > '9') last = ch, ch = getchar();
	   while(ch >= '0' && ch <= '9') ans = (ans << 3) + (ans << 1) + ch - '0', ch = getchar();
	   if(last == '-') ans = -ans;
	   return ans;
}

const int INF = 0x3f3f3f3f;

const int N = 1e5 + 5;

int head[N];
struct Edge{
	int next, to;
}e[N << 1];
int tot, n, m;
void insert(int x, int y) {
	e[++tot].next = head[x];
	e[tot].to = y;
	head[x] = tot;
}

bool vis[N];
bool flag = false;
void dfs(int u, int fa) {
	vis[u] = true;
	int v;
	for(int i = head[u]; i; i = e[i].next) {
		v = e[i].to;
		if(v == fa) continue;
		if(vis[v]) {
			flag= false;
			continue;
		}
		dfs(v, u);
	}
	
}
int ans =0;
int main(){
	//freopen("testdata.in", "r", stdin);
	//freopen("ans.out", "w", stdout);
	n = read(), m = read();
	int x, y;
	$(i, 1, m) {
		x = read(), y = read();
		insert(x, y), insert(y,x);
	}
	for(int i = 1; i <= n; ++i) {
		if(!vis[i]) {
			flag = true;
			dfs(i, 0);
			if(flag) ++ans;
		}
	}
	printf("%d\n", ans);
	return 0;
}


```



---

## 作者：xukuan (赞：2)

### 翻译（我已被禁言，只能如此贡献翻译）：
有n个城市，m条双向道路，没有一个城市存在自己到自己的道路，两个不同的城市间，最多有一条道路，也不能保证能从一个城市到达任意一个其他城市。

现在需要对每一条道路定向，使之成为单向道路，当然需要尽可能少地产生孤立的城市。当其他所有城市都不能到达某个城市，则称这个城市为孤立城市。


输入格式：

第一行，两个整数，n和m。

接下来m行，每行两个整数，表示一条双向道路。

输出格式：
一行，一个整数，表示最少的孤立城市。

样例输入 1
```pascal
4 3
2 1
1 3
4 3
```

样例输出 1

1

样例输入 2
```pascal
5 5
2 1
1 3
2 3
2 5
4 3
```
样例输出 2

0

样例输入 3
```pascal
6 5
1 2
2 3
4 5
4 6
5 6
```
样例输出 3

1

数据范围：
2≤n≤100000,1≤m≤100000

提示：可能存在多组测试数据

______________________________________________________

### 题解正文
DFS判断环的有无

若过一个点无环则计数器+1

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<string>
#include<queue>
#define ll long long
using namespace std;

ll vis[100010],bo,n,m,ans;
vector<ll> map[100010];//不能用邻接矩阵，用STL之动态数组

inline ll read(){
    ll tmp=1,x=0;
    char ch=getchar();
    while(!isdigit(ch)){
        if(ch=='-') tmp=-1;
        ch=getchar();
    }
   
    while(isdigit(ch)){
        x=x*10+ch-48;
        ch=getchar();
    }
    return tmp*x;
}//读入优化

void dfs(ll k,ll prev){	
	vis[k]=1;
	for(ll i=0; i<map[k].size(); i++){//穷举每一个能到的城市
		ll v=map[k][i];//下一个城市
		if(v==prev) continue;//防止出现道路仍是双向（道路从prev到v又从v到prev），避免递归到上一个点导致死递归爆栈
		if(vis[v]==1){//这个点已经遍历过了
			bo=1;//有环标记
			continue;//进入下一层循环
		}
		dfs(v,k);//递归
	}
}

int main(){
	while(cin>>n>>m){//输入，测试可能有多组数据
		memset(vis,0,sizeof(vis));//清空vis数组
		for(ll i=1; i<=n; i++) map[i].clear();//清空map动态数组
		ans=0;//清空计数器
		
		for(ll i=1; i<=m; i++){	
			ll x=read(),y=read();//输入
			map[x].push_back(y);//x可以到y
			map[y].push_back(x);//y可以到x
		}
		
		for(ll i=1; i<=n; i++){
			if(vis[i]==0){
				bo=0;//标记为0
				dfs(i,-1);
				if(bo==0) ans++;//无环计数器+1
			}
		}
		
		cout<<ans<<endl;//输出总数
	}
	
	return 0;
}
```

---

## 作者：_byta (赞：1)

我们可以用并查集记录每一个连通块，当某两个连通块有连边时，就合并这两个块。

最后若某个点不属于认一个连通块，则孤立城市加一。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,x,y,ans,f[1000005],v[1000005],s[1000005];
int find(int x)
{
	return x==f[x]?x:f[x]=find(f[x]);
}
void merge(int x,int y)
{
	if(x<y)swap(x,y);
	v[x]+=v[y];
	f[y]=x;
}
int main()
{
	  scanf("%d%d",&n,&m);
	  for(int i=1;i<=n+1;i++)f[i]=i;
	  for(int i=1;i<=m;i++)
	  {
		    scanf("%d%d",&x,&y);
		    int fx=find(x),fy=find(y);
		    if(fx==fy)v[fx]=1;
		    else merge(fx,fy);
	  }
	  for(int i=1;i<=n;i++) 
	  {
	      if(find(i)==i && !v[i]) ans++;
	  }
	  printf("%d\n",ans);
	  return 0;
}
```


---

## 作者：TsH_GD (赞：0)


[传送门](https://www.luogu.com.cn/problem/CF659E)。

### 分析

得出：**如果城市之间形成环，就有 $0$ 个孤独城市**。


## 划重点

一个 $visit(x)$ ，利用并查集，读入一个点，如果已被标记在一个独立的环当中，标记为 $1$ 。

否则，就合并。



### 分析


画图发现：**如果一个城市已经在一个环里，那另一个直接加入到里面就可以了**。

## 关键

* 并查集来找环。

### ACcode（注释版）:
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<ctime>

using namespace std;

int n,m,ans,father[100005],x,y;
bool visit[100005];


//查找父亲
int ss(int x){
	return x==father[x]?x:father[x]=ss(father[x]);
}

int main(){
	scanf("%d%d",&n,&m);
	
	for(int i=1;i<=n;i++){
		//初始化 
		father[i]=i； 
		//每个节点的父亲设为自己 
	}
	
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		
		int tx=ss(x);
		int ty=ss(y);
		
		if(tx==ty){//如果父亲一样 （表示两个城市之间联通） 
			visit[tx]=true;
			continue;
		} 
		
		father[tx]=ty; //（联通城市）使父节点统一 
        
		// 若之前已找到过环，就把父亲节点标记为1 
		if(visit[tx]||visit[ty]){visit[ty]=true;} 
	}
    
	for(int i=1;i<=n;i++){ 
		if(ss(i)==i&&!visit[i]){ // 满足ss(i)==i的点是父亲节点，另一个就是一颗单独的树。
			ans++;  
		}
	} 
	printf("%d",ans);
	return 0;
}
```

---

