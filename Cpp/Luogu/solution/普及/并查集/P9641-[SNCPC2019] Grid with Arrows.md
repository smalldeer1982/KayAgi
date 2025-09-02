# [SNCPC2019] Grid with Arrows

## 题目描述

宝宝刚刚在他的左口袋里发现了一个 $n$ 行 $m$ 列的网格，其中第 $i$ 行第 $j$ 列的单元格（表示为 $(i, j)$）包含一个箭头（指向上、下、左或右）和一个整数 $a_{i, j}$。

宝宝决定用这个网格玩一个游戏。他首先会选择一个单元格作为初始单元格并标记它。在标记一个单元格之后（假设宝宝刚刚标记了单元格 $(i, j)$），宝宝将根据单元格 $(i, j)$ 中的箭头和整数继续标记另一个单元格。

- 如果单元格 $(i, j)$ 中的箭头指向上方，宝宝将继续标记单元格 $(i-a_{i, j}, j)$，如果该单元格存在的话。
- 如果单元格 $(i, j)$ 中的箭头指向下方，宝宝将继续标记单元格 $(i+a_{i, j}, j)$，如果该单元格存在的话。
- 如果单元格 $(i, j)$ 中的箭头指向左方，宝宝将继续标记单元格 $(i, j-a_{i, j})$，如果该单元格存在的话。
- 如果单元格 $(i, j)$ 中的箭头指向右方，宝宝将继续标记单元格 $(i, j+a_{i, j})$，如果该单元格存在的话。
如果宝宝决定标记的单元格不存在，或者该单元格已经被标记，游戏结束。

宝宝想知道他是否可以选择一个合适的初始单元格，以便在游戏结束前恰好标记网格中的每一个单元格一次。请帮助他找到答案。

## 样例 #1

### 输入

```
2
2 3
rdd
url
2 1 1
1 1 2
2 2
rr
rr
1 1
1 1```

### 输出

```
Yes
No```

# 题解

## 作者：WhitD (赞：3)

## 思路
我们把每个格子抽象为点，根据格子上的数和字母将这个格子和它指向的格子连边。

然后我们只要判断这个图是否可以从一个点出发，不经过重复点（边），走完所有点。

对于样例，可行方案如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/hmtu6pvu.png)

（事实上，这也是唯一可行方案）。

不难看出：任意一个点的出度一定是 $1$（因为它只会指向一个点），因此图是一颗基环树。

同时考虑为什么在样例中该方案是唯一的：图中有一个很特殊的点二，它的入度为 $0$，而我们的方案正是从点二出发的。也就是说我们的出发点一定是一个入度为 $0$ 的点。

这点很好理解：假设我们要经过所有点，入度为 $0$ 的点永远不可能从其他点到达（因为没有指向它的边嘛），因此只能从这个点出发。

于是可以维护一个数组来表示每个点的入度，寻找入度为 $0$ 的点并从它开始遍历（若所有点入度都不为 $0$ 则随便找一个点开始遍历），判断能否经过所有点。

数据范围较大，可以开动态数组（~~小周老师点了个赞~~）。

---

## 作者：luan341502 (赞：2)

赛时交了八发才过，少考虑了一种情况。

考虑将每个点对应能到的点连起来，这样就构成了一张图（如果对于不满足题目条件的点不进行连边的话，就无法构成一棵基环树）。

观察可以发现只有两种情况满足题目要求：

1. 整个图构成一个环，此时从任意点出发都能经过所有点。

2. 从一个点出发到达一个环，最终遍历完整个图。

对于两种情况分别判断，用并查集记录即可。

1. 所有点在一个并查集内就满足情况。

2. 只有一个点入度为零，否则一定不满足情况。统计入度情况进行判断即可。

由于 $n \times m \leq 10^5$，考虑使用将矩阵映射为直线的做法，这样只需开长度为 $10^5$ 的一维数组。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
string str[100005];
int fa[100005],d[100005];
int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
void merge(int x,int y,int x_,int y_){
	int s1=(x-1)*m+y,s2=(x_-1)*m+y_;
	int u=find(s1),v=find(s2);
	if(u!=v) fa[v]=u;
}
void solve(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n*m;i++){
		fa[i]=i;
		d[i]=0;
	}
	for(int i=1;i<=n;i++){
		cin>>str[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int x;
			scanf("%d",&x);
			int ch=(int)str[i][j-1],p,q;
			if(ch==117) p=i-x,q=j;
			else if(ch==100) p=i+x,q=j;
			else if(ch==108) p=i,q=j-x;
			else p=i,q=j+x;
			if(p<1||q<1||p>n||q>m) continue;
			merge(i,j,p,q);
			d[(p-1)*m+q]++;
		}
	}
	int x=find(1),cnt=n*m;
	for(int i=2;i<=cnt;i++){
		if(find(i)!=x){
			puts("No");
			return;
		}
	}
	int res=0;
	for(int i=1;i<=cnt;i++){
		if(!d[i]) res++;
		if(res>1){
			puts("No");
			return;
		}
	}
	puts("Yes");
}
int main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```


---

## 作者：Tsuki091117 (赞：2)

**看到这道题就想到了不久之前学的 Tarjan，但题解中好像并没有这种解法，所以我打算写一篇题解记录一下。** 
## 前置芝士
[Tarjan缩点](https://blog.csdn.net/qaqwqaqwq/article/details/119884138?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522172154381416800226583008%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=172154381416800226583008&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-119884138-null-null.142^v100^pc_search_result_base4&utm_term=tarjan&spm=1018.2226.3001.4187)

[链式前向星](https://blog.csdn.net/m0_62999278/article/details/137040986?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522172154404816800222866467%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=172154404816800222866467&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-2-137040986-null-null.142^v100^pc_search_result_base4&utm_term=%E9%93%BE%E5%BC%8F%E5%89%8D%E5%90%91%E6%98%9F&spm=1018.2226.3001.4187)

- 在此之前建议大家先去练习一下[P2002 消息扩散](https://www.luogu.com.cn/problem/P2002)。

## 题意概括
给定一张有向图，问是否存在一个点能够一次性到达剩下的所有的点。

## 题目分析
1. 首先，我们要建立一张有向图，将每个坐标为 $(x,y)$ 的点转换成第 $(i-1) \times m+j$ 个点，这样我们就得到了 $n \times m$ 个点，以下用 $cnt$ 表示。然后连接每条边，但要注意边界问题。

```cpp
switch(s[i][j-1]){
	case 'u':{
		if(i-p>=1) add((i-1)*m+j,(i-p-1)*m+j);//往上走，判断横坐标是否小于1
		break;
		}
	case 'd':{
		if(i+p<=n) add((i-1)*m+j,(i+p-1)*m+j);//往下走，判断横坐标是否大于n
		break;
	}
	case 'l':{
		if(j-p>=1) add((i-1)*m+j,(i-1)*m+j-p);//往左走，判断纵坐标是否小于1
		break;
	}
	case 'r':{
		if(j+p<=m) add((i-1)*m+j,(i-1)*m+j+p);//往右走，判断纵坐标是否大于m
		break;
	}
}
```

2. 现在，我们的有向图就建好了。接下来就是缩点模板。

```cpp
void tarjan(int u){
	dfn[u]=low[u]=++timestamp;
	stk[++top]=u,in_stk[u]=1;
	for(int i=h[u];i!=-1;i=ne[i]){
		int j=e[i];
		if(!dfn[j]){
			tarjan(j);
			low[u]=min(low[u],low[j]);
		} 
		else if(in_stk[j]) low[u]=min(low[u],dfn[j]);
	}
	if(dfn[u]==low[u]){
		int y;
		scc_cnt++;
		do{
			y=stk[top--];
			id[y]=scc_cnt;
			in_stk[y]=0;
		} while(y!=u);
	}
}
```

3. 然后我们考虑这样一个问题：在缩完点后，什么样的点能够满足题目中的条件呢？我们发现：入度为 $0$ 的点就可以！但不要忘了：这样的点只能有一个，再多就不连通了。

```cpp
for(int i=1;i<=cnt;i++){
	for(int j=h[i];j!=-1;j=ne[j]){
		if(id[i]!=id[e[j]]){
			din[id[e[j]]]++;
		}
	}
}
int ans=0;
for(int i=1;i<=scc_cnt;i++){
	if(!din[i]) ans++;
}
if(ans>1) cout<<"No\n";
else cout<<"Yes\n";
```

到这里，这道题就解决了。

$Code$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int T;
int din[N];
int h[N],e[N],ne[N],idx;
string s[N];
int dfn[N],low[N],timestamp;
int stk[N],top;
bool in_stk[N];
int id[N],scc_cnt;

void add(int a,int b){
	e[idx]=b,ne[idx]=h[a],h[a]=idx++;//链式前向星 
}

void tarjan(int u){
	dfn[u]=low[u]=++timestamp;
	stk[++top]=u,in_stk[u]=1;
	for(int i=h[u];i!=-1;i=ne[i]){
		int j=e[i];
		if(!dfn[j]){
			tarjan(j);
			low[u]=min(low[u],low[j]);
		} 
		else if(in_stk[j]) low[u]=min(low[u],dfn[j]);
	}
	if(dfn[u]==low[u]){
		int y;
		scc_cnt++;
		do{
			y=stk[top--];
			id[y]=scc_cnt;
			in_stk[y]=0;
		} while(y!=u);
	}
}//Tarjan模板 

signed main(){
	cin>>T;
	while(T--){
		int n,m,p,ans=0;
		cin>>n>>m;
		int cnt=n*m;
		top=0,idx=0,scc_cnt=0,timestamp=0;//多测要清空 
		memset(h,-1,sizeof h);
		memset(dfn,0,sizeof dfn);
		memset(low,0,sizeof low);
		memset(stk,0,sizeof stk);
		memset(id,0,sizeof id);
		memset(din,0,sizeof din);
		memset(in_stk,false,sizeof in_stk);
		for(int i=1;i<=n;i++) cin>>s[i];
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				cin>>p;
				switch(s[i][j-1]){//因为字符串是从0开始读入的，所以要看s[i][j-1] 
					case 'u':{
						if(i-p>=1) add((i-1)*m+j,(i-p-1)*m+j);;//往上走，判断横坐标是否小于1
						break;
					}
					case 'd':{
						if(i+p<=n) add((i-1)*m+j,(i+p-1)*m+j);//往下走，判断横坐标是否大于n
						break;
					}
					case 'l':{
						if(j-p>=1) add((i-1)*m+j,(i-1)*m+j-p);//往左走，判断纵坐标是否小于1
						break;
					}
					case 'r':{
						if(j+p<=m) add((i-1)*m+j,(i-1)*m+j+p);//往右走，判断纵坐标是否大于m
						break;
					}
				}
			}
		for(int i=1;i<=cnt;i++){
			if(!dfn[i]) tarjan(i);//缩点 
		}
		for(int i=1;i<=cnt;i++){
			for(int j=h[i];j!=-1;j=ne[j]){
				if(id[i]!=id[e[j]]){
					din[id[e[j]]]++;//计算入度 
				}
			}
		}
		for(int i=1;i<=scc_cnt;i++){
			if(!din[i]) ans++;//计算入度为0的点 
		}
		if(ans>1) cout<<"No\n";//记得换行
		else cout<<"Yes\n";
	} 
	return 0;
}



```

---

## 作者：Flaw_Owl (赞：0)

# P9641 [SNCPC2019] Grid with Arrows 题解

题目链接：[P9641 [SNCPC2019] Grid with Arrows](https://www.luogu.com.cn/problem/P9641)

## 题目分析

注意到题目中的这句话：

> 在游戏结束前恰好标记网格中的每一个单元格一次。

如果我们把这个网格中每一个格子都看作一个**点**，那么每个格子上的箭头方向和整数可以使得这个点指向另一个格子，即构建了点到点间的一条**有向边**。至此，题目的关键已经清晰：**寻找一张有向图中是否存在欧拉路**。

### 前置知识

#### 欧拉路简介

**欧拉路**的定义是：从图中某个点出发，遍历整个图，图中每条边通过且只能经过一次。而如果起点和终点也相同，就被称为**欧拉回路**。

欧拉路问题的解决主要通过处理**度（Degree）**。一个点的度数，是这个点上**连接的边的数量**。在**无向图**中，如果度数是偶数，则称这个点为**偶点**，反之则为**奇点**；在**有向图**中，因为边是有方向的，一个点的度又分为**出度**和**入度**两种。

#### 欧拉路的存在性

欧拉路存在的前提条件是**联通图**。因此要先用 DFS 或**并查集**判断图的连通性。

接着，根据图的种类（有向图或无向图）进行判断：

- 如果图是无向图，那么如果图中的点**全都是偶点**，则**存在欧拉回路**，并且任意点都可以作为起点和终点；如果图中**只有两个奇点**，则**存在欧拉路**，并且其中一个奇点是起点，另一个是终点。
- 如果图是有向图，那么如果图中所有点的**度数都是 $0$**，则**存在欧拉回路**；如果**只有一个度数为 $1$ 的点，一个度数为 $-1$ 的点**，则**存在欧拉路**，其中度数为 $1$ 的是起点，度数为 $-1$ 的是终点。

#### 例题

下面给出几道简单的例题，它们可以让你快速熟悉欧拉路相关的操作。它们有的还需要输出欧拉路，在一般情况下，只需利用 DFS + 栈就可以，但有些时候递归可能爆栈，就需要手写栈。下面给出的题目都不需要手写栈，很适合基础练习：

- 有向图：[P7771 【模板】欧拉路径](https://www.luogu.com.cn/problem/P7771)
- 无向图：[P1341 无序字母对](https://www.luogu.com.cn/problem/P1341)

上面的题目中，因为数据点较弱或是题目保证的原因，我们都无需判断图是否具有连通性。

### 本题程序设计

#### 存图

对于本题而言，我们首先要解决的问题就是如何存图。观察数据，它保证 $1 \leq n \times m \leq 10^5$，但没有单独对 $n,m$ 进行数据范围的规定。如果设图 `G[100005][100005]`，显然会爆空间。因此我们想到**用一维数组代替二维数组**的方式。反正我们也是要将每个格子抽象成一个点的序号，我们并不关心它的行列。

下面的函数将坐标点对 $(x,y)$ 转化成了一个唯一不重复的序号。其中，$x,y$ 都是从 $1$ 开始的。

```cpp
int getId(int x, int y)
{
    return (x - 1) * m + y;
}
```

#### 读入

接下来是读入的问题。题目中箭头方向和整数是分开给的，而箭头方向又是矩阵的形式，显然用 `char` 类型的二维数组存储也是不合适的。这里我使用了字符串一维数组进行存储。

```cpp
string b[maxN];

for (int i = 1; i <= n; i++)
    cin >> b[i];
```

而对于之后的整数，我们只要一个数字一个数字读即可。读入这个数字之后，我们要再根据这一格的箭头方向，找到其指向的格子坐标。值得注意的是，如果这里指向的格子已经超过了 $n \times m$ 这个矩阵的范围，那么它是不生效的，直接 `continue` 即可。找到坐标之后要做两件事情：

- 更新这两个点的度数。这里我只使用了 `degree[]` 一个一维数组，并将出度表示为 $+1$，入度表示为 $-1$。
- 利用并查集，将这两个点连起来。方便以后判断图是否具有连通性。

注意其中对字符串前面加一个空格的处理，它使得第一个字母从 $1$ 开始而不是从 $0$ 开始。

```cpp
for (int i = 1; i <= n; i++)
        {
            b[i] = " " + b[i]; // 保证第一个字母从 1 开始
            for (int j = 1; j <= m; j++)
            {
                int temp = read();
                x = getId(i, j);
                char ch = b[i][j];
                if (ch == 'u' && i - temp >= 1)
                    y = getId(i - temp, j);
                else if (ch == 'd' && i + temp <= n)
                    y = getId(i + temp, j);
                else if (ch == 'l' && j - temp >= 1)
                    y = getId(i, j - temp);
                else if (ch == 'r' && j + temp <= m)
                    y = getId(i, j + temp);
                else
                    continue;
                degree[x]++;
                degree[y]--;
                merge_set(x, y);
            }
        }
```

#### 并查集和判断连通性

并查集只需打板子即可。注意在读入 $n,m$ 之后需要初始化。

```cpp
void init()
{
    for (int i = 1; i <= n * m; i++)
    {
        fa[i] = i;
        degree[i] = 0;
    }
}

int find_set(int x)
{
    return fa[x] == x ? x : fa[x] = find_set(fa[x]);
}

void merge_set(int x, int y)
{
    x = find_set(x), y = find_set(y);
    if (x != y)
        fa[y] = x;
}
```

那么在存完所有的图之后，我们首先要利用并查集判断图的连通性。我的做法是建立了一个 `check()` 函数，它用来返回是否存在欧拉路。同时，直接遍历每一个点并判断其祖先，如果和 $1$ 的祖先不同，就返回 `false`。

```cpp
int root = find_set(1);
    for (int i = 2; i <= n * m; i++)
        if (find_set(i) != root)
            return false;
```

#### 判断欧拉路是否存在

根据开头的预备知识，最朴素的做法就是判断整张图之中度数是否全都为 $0$，或者除了 $0$ 外有且只有两个度数分别为 $1$ 和 $-1$ 的点。

```cpp
int sx = 0, ed = 0;
for (int i = 1; i <= n * m; i++)
{
    if (degree[i] == 1)
    {
        if (sx)
            return false;
        sx = i;
    }
    else if (degree[i] == -1)
    {
        if (ed)
            return false;
        ed = i;
    }
    else if (degree[i] != 0)
        return false;
}
return true;
```

### 参考代码

至此，整道题基本完成，剩下的将细节填充完整即可。下面给出参考代码：

```cpp
#include <iostream>
#include <cctype>
#include <vector>

using namespace std;

int read()
{
    int x = 0, f = 1;
    char ch = 0;
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int maxN = 1e5 + 10;

int T;
int n, m;
int x, y;

string b[maxN];
int degree[maxN];
int fa[maxN];

void init()
{
    for (int i = 1; i <= n * m; i++)
    {
        fa[i] = i;
        degree[i] = 0;
    }
}

int getId(int x, int y)
{
    return (x - 1) * m + y;
}

int find_set(int x)
{
    return fa[x] == x ? x : fa[x] = find_set(fa[x]);
}

void merge_set(int x, int y)
{
    x = find_set(x), y = find_set(y);
    if (x != y)
        fa[y] = x;
}

bool check()
{
    int root = find_set(1);
    for (int i = 2; i <= n * m; i++)
        if (find_set(i) != root)
            return false;
    int sx = 0, ed = 0;
    for (int i = 1; i <= n * m; i++)
    {
        if (degree[i] == 1)
        {
            if (sx)
                return false;
            sx = i;
        }
        else if (degree[i] == -1)
        {
            if (ed)
                return false;
            ed = i;
        }
        else if (degree[i] != 0)
            return false;
    }
    return true;
}

int main()
{
    T = read();
    while (T--)
    {
        n = read(), m = read();
        init();
        for (int i = 1; i <= n; i++)
            cin >> b[i];
        for (int i = 1; i <= n; i++)
        {
            b[i] = " " + b[i]; // 保证第一个字母从 1 开始
            for (int j = 1; j <= m; j++)
            {
                int temp = read();
                x = getId(i, j);
                char ch = b[i][j];
                if (ch == 'u' && i - temp >= 1)
                    y = getId(i - temp, j);
                else if (ch == 'd' && i + temp <= n)
                    y = getId(i + temp, j);
                else if (ch == 'l' && j - temp >= 1)
                    y = getId(i, j - temp);
                else if (ch == 'r' && j + temp <= m)
                    y = getId(i, j + temp);
                else
                    continue;
                degree[x]++;
                degree[y]--;
                merge_set(x, y);
            }
        }
        if (check())
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}
```

---

## 作者：chidor (赞：0)

### 题目关键

BaoBao is wondering if he can select a proper initial cell, so that he can tick every cell in the grid exactly once before the game ends. Please help him find the answer.

#### 大意：

宝宝想知道他是否可以选择一个合适的初始单元格，这样他就可以在游戏结束前准确地勾选网格中的每个单元格一次。请帮他找到答案。

### 解法

由题意可知，符合要求的方法只有两种

1.一条边连到一个环。

![](https://cdn.luogu.com.cn/upload/image_hosting/35xmlk92.png)

2.一个环。

![](https://cdn.luogu.com.cn/upload/image_hosting/2tebk0op.png)

也就是说符合要求的图不可能有 $2$ 个及以上入度为 $0$ 的点。

而且所有的点都在一个联通块里。
### 代码
```cpp
#include<bits/stdc++.h>
#define fun(x,y) (x-1)*m+y //偷个懒
using namespace std;
const int maxn=100005;//只知道总乘积范围，所以用一维数组存
int a[maxn],f[maxn],in[maxn],T,n,m;
char s[maxn];
int find(int x){ //并查集基本操作
	if(x==f[x])return x;
	return f[x]=find(f[x]);
}
void sol(){
	cin>>n>>m;
	memset(in,0,sizeof(in));
	for(int i=1;i<=n*m;i++)f[i]=i;//并查集初始化
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>s[fun(i,j)];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int nxt=-1;//指向的坐标
        int nw=fun(i,j);//映射一维坐标
			cin>>a[nw];//输入方向
			if(s[nw]=='u'&&i-a[nw]>=1)nxt=nw-a[nw]*m;//这条边是往上的
			if(s[nw]=='d'&&i+a[nw]<=n)nxt=nw+a[nw]*m;//这条边是往下的
			if(s[nw]=='l'&&j-a[nw]>=1)nxt=nw-a[nw];//这条边是往左的
			if(s[nw]=='r'&&j+a[nw]<=m)nxt=nw+a[nw];//这条边是往右的
			if(nxt!=-1){//如果该点存在
				in[nxt]++;//入度+1
				int x=find(fun(i,j)),y=find(nxt);//并查集合并
				f[x]=f[y];
			}
		}
	}
	int cnt=0;
	for(int i=1;i<=n*m;i++){
		if(in[i]==0)cnt++;
	}
	if(cnt>=2){//由上图可知
		cout<<"No\n";
		return;
	}
	int rt=find(1);	
	for(int i=2;i<=n*m;i++){
		if(find(i)!=rt){//判断连通性
			cout<<"No\n";
			return;
		}
	}
	cout<<"Yes\n";
}
int main(){
	cin>>T;
	while(T--)sol();
}
```

---

## 作者：niuzh (赞：0)

## 思路
将每一个格子都看做点，则构成一个 **有向图**。

题目所求则简化为：在这个有向图里，能否从一个点开始，不重复经过一个点，将所有点都做一遍。

对于样例中的第一组数据,有向图为：

![](https://cdn.luogu.com.cn/upload/image_hosting/eqbfu99j.png)

对于正确的数据，有向图是一棵 **基环树**。


唯一路径为：

![](https://cdn.luogu.com.cn/upload/image_hosting/x0bqr726.png)

可以看出，路径是从点 $[1,2]$ 开始的，而点 $([1,2]$ 的特殊性质为入度为 $0$，
所以 **出发点一定是一个入度为 $0$ 的点**。
因为只有入度不为 $0$，其他点都无法到达这个点，所以这个点只能是出发点。

若有多个,则图并不联通，可以直接判断不可行。

如果没有入度为 $0$ 的点，则有向图一定为 **有向环**( 因为一个点的出度一定是 $1$)。在这种情况下，则任选一个点作为出发点即可。

复杂度为 $O(nm)$，不会超时。

## 代码
```
/*
 * @FilePath: P9641 Grid with Arrows.cpp
 * @Author: niu-zh
 */
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+1;
long long a[N],c[N],n,m;//将二维数组压为一维数组
char d[N];
bitset<N> vis;//用bitset压缩空间
inline long long pl(int x,int y)//一个点在一维数组里的下标
{
	return (long long)(x-1)*m+y;
}
inline bool check(int x,int y)
{
	return x>=1&&x<=n&&y>=1&&y<=m;
}
inline void dfs(int x)//遍历图，标记从起点开始经过的每一个点
{
	vis[x]=true;
	if (a[x]&&!vis[a[x]])
	{
		dfs(a[x]);
	}
}
inline void work()
{
	cin>>n>>m;
	for (int i=1; i<=n*m; i++)
	{
		cin>>d[i];
	}
	//处理输入，构造有向图，并记录每个点的入度。
	for (int i=1; i<=n; i++)
	{
		for (int j=1; j<=m; j++)
		{
			int x;
			cin>>x;
			if (d[pl(i,j)]=='u')
			{
				if(check(i-x,j))//检查每个点是否存在
				{
					a[pl(i,j)]=pl(i-x,j);//有向图
					c[pl(i-x,j)]++;      //统计点的入度
				}
			}
			else if (d[pl(i,j)]=='d')
			{
				if(check(i+x,j))
				{
					a[pl(i,j)]=pl(i+x,j);
					c[pl(i+x,j)]++;
				}
			}
			else if (d[pl(i,j)]=='l')
			{
				if(check(i,j-x))
				{
					a[pl(i,j)]=pl(i,j-x);
					c[pl(i,j-x)]++;
				}
			}
			else
			{
				if(check(i,j+x))
				{
					a[pl(i,j)]=pl(i,j+x);
					c[pl(i,j+x)]++;
				}
			}
		}
	}
	//寻找入度为 0 的点作为起点，如果找不到则选第一个点 (哪个都行) 作为起点。若有多个，输出 No 并结束程序。
	int s=1,cnt=0;
	for (int i=1; i<=n*m; i++)
	{
		if (c[i]==0)
		{
			s=i;
			cnt++;
		}
	}
	if(cnt>1)//图不联通
	{
		cout<<"No";
		return;
	}
	dfs(s);
	//是否存在未被访问过的节点。
	for (int i=1; i<=n*m; i++)
	{
		if (!vis[i])
		{
			cout<<"No";
			return;
		}
	}
	cout<<"Yes";
}
inline void init()//初始化，极其重要！！！
{
	memset(a,0,sizeof(a));
	memset(c,0,sizeof(c));
	vis.reset();
}
int main()
{
	int t;
	cin>>t;
	while (t--)
	{
		init();
		work();
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：drinktowind (赞：0)

# 题目大意
给你一个 $n$ 行 $m$ 列的矩阵，对于矩阵中的点 ($i$,$j$)，给出了一个方向和一个值，由它们可以找到另一个点。问能否从某一个点开始，按照给定的方向和值走完所有的点。
# 思路分析
经过所有的点且每条边只经过一次，很容易就能想到欧拉路径。题目为有向图，我们记录这个有向图中每一个点的入度和出度，来判定是否存在欧拉回路。
### 欧拉回路满足条件：
1. 若这个有向图中每一个点的入度都等于出度。
2. 若存在一个点的入度比出度大 $1$，存在一个点的出度比入度大 $1$，其余的点入度出度相等。
#### 注意：  
在判断是否含有欧拉路径前要先判断有向图是否是连通图，如果不是连通图，则一定没有欧拉回路。
# AC代码
```
#include<bits/stdc++.h>
using namespace std;
string s[100005];
int f[100005],a[100005],b[100005],x,y,cnt,n,m,k;
bool flg;
int find(int x)//并查集板子
{
	if(f[x]==x)
	    return x;
    f[x]=find(f[x]);
    return f[x];
}
int main()
{
	cin>>k;
	while(k--)
	{
		cin>>n>>m;
		for(int i=0;i<n*m;i++)//初始化
		{
			f[i]=i;
			a[i]=b[i]=0;
		}
		for(int i=0;i<n;i++)
			cin>>s[i];
		for(int i=0;i<n;i++)//模拟
		{
			for(int j=0;j<m;j++)
			{
				cin>>x;
				if(s[i][j]=='u'&&i-x>=0)
				{
					a[(i-x)*m+j]++;
					b[i*m+j]++;
					f[find(i*m+j)]=find((i-x)*m+j);
				}else if(s[i][j]=='d'&&i+x<n)
				{
					a[(i+x)*m+j]++;
					b[i*m+j]++;
					f[find(i*m+j)]=find((i+x)*m+j);
				}else if(s[i][j]=='l'&&j-x>=0)
				{
					a[i*m+j-x]++;
					b[i*m+j]++;
					f[find(i*m+j)]=find(i*m+j-x);
				}else if(s[i][j]=='r'&&j+x<m)
				{
					a[i*m+j+x]++;
					b[i*m+j]++;
					f[find(i*m+j)]=find(i*m+j+x);
				}
			}
		}
		x=y=flg=cnt=0;
		for(int i=0;i<n*m;i++)
 		{
			if(f[i]==i)
			{
				if(flg)//如果不连通
				{
					flg=0;
					break;
				}
				flg=1;
			}
			if(a[i]!=b[i])
			{
				cnt++;
				if(a[i]==b[i]+1)
					x=1;
				else if(a[i]+1==b[i])
					y=1;
			}
		}
		if((!cnt&&flg==1)||(x==1&&y==1&&cnt==2&&flg==1))
			printf("Yes\n");
		else
			printf("No\n");
    }
    return 0;
} 
```

---

## 作者：zwye (赞：0)

### 题目大意
给你一个 $n$ 行 $m$ 列的矩阵，对于矩阵中的点 $(i,j)$,给出了一个方向和一个值，由它们可以找到另一个点，问能否从某一个点开始，按照给定的方向和值走完所有的点。

### 思路分析
经过所有的点且每条边只经过一次，可以想到欧拉路径。题目可以转换为一个有向图，因此我们可以统计这个有向图中每一个点的入度和出度，若这个有向图中每一个点的入度都等于出度，则存在欧拉回路，满足；若存在一个点的入度比出度大 $1$，存在一个点的出度比入度大 $1$，其余的点入度出度相等，则也满足。注：在判断是否含有欧拉路径前要先判断有向图是否连通，只有连通图才有欧拉路径，用并查集来判断。
```cpp
#include<iostream>
#include<cstring>
using namespace std;
string arrow[100005];
int fa[1000005],in[1000005],out[1000005];
int find(int i){
	if(fa[i]==i)
	return fa[i];
	else{
		fa[i]=find(fa[i]);
		return fa[i];
	}
}
void unions(int x,int y){
	int i=find(x);
	int j=find(y);
	fa[i]=j;
}
int main(){
	int t;
	cin>>t;
	while(t--){
		int n,m;
		scanf("%d%d",&n,&m);
		for(int i=0;i<n*m;i++) 
		{
			fa[i]=i;
			in[i]=0;
			out[i]=0;
		}
		for(int i=0;i<n;i++){
			cin>>arrow[i];
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				int a;
				scanf("%d",&a);
				if(arrow[i][j]=='u'&&i-a>=0){
					in[(i-a)*m+j]++;
					out[i*m+j]++;
					unions(i*m+j,(i-a)*m+j);
				}
				else
				if(arrow[i][j]=='d'&&i+a<n){
					in[(i+a)*m+j]++;
					out[i*m+j]++;
					unions(i*m+j,(i+a)*m+j);
				}
				else
				if(arrow[i][j]=='l'&&j-a>=0){
					in[i*m+j-a]++;
					out[i*m+j]++;
					unions(i*m+j,i*m+j-a);
				}
				else
				if(arrow[i][j]=='r'&&j+a<m){
					in[i*m+j+a]++;
					out[i*m+j]++;
					unions(i*m+j,i*m+j+a);
				}
			}
		}
		int fbig=0,fsmall=0,count=0,flag=0;
		for(int i=0;i<n*m;i++){
			if(fa[i]==i)
			flag++;
			if(flag>1)
			break;
			if(in[i]!=out[i]){
				count++;
				if(in[i]==out[i]+1)
				fbig=1;
				else
				if(in[i]+1==out[i])
				fsmall=1;
			}
		}
		if(count==0&&flag==1)
		{
			printf("Yes\n");
		}
		else
		if(fbig==1&&fsmall==1&&count==2&&flag==1)
		{
			printf("Yes\n");
		}
		else
		printf("No\n");
	}
} 
```


---

## 作者：fls233666 (赞：0)

我们从样例中的第一组数据入手：

	2 3
	rdd
	url
	2 1 1
	1 1 2

不妨把矩阵的每一个单元格看成点，并依次标号。

![pic1](https://cdn.luogu.com.cn/upload/image_hosting/c8mkeani.png)

根据每个格子的箭头，把两个点之间用有向边连接，从而**构建出一张有向图**。

![pic2](https://cdn.luogu.com.cn/upload/image_hosting/tlvwje06.png)

于是问题就简化为：**选择有向图上的一个点出发，能否遍历所有的点恰好一次。**

那么，进一步考虑，怎么选这个出发点？

既然我们要遍历 $n$ 个点，我们就需要 $n-1$ 条有向边。

那么，在原本的图上去掉一条边后，图应该呈现为一条有向链，如下：

![pic3](https://cdn.luogu.com.cn/upload/image_hosting/tkmnv6pq.png)

可以发现，能作为起点的点有一个特点：**没有任何有向边指向起点，即起点的入度为零。**

具体的可以用反证法来考虑，我们设这一个入度为零的点为 $X_0$，而我们假定选择点 $X_1$ 作为起点能达成题目要求。而因为 $X_0$ 入度为零，所以其他点都无法走到 $X_0$，则无法达成题目要求，假设不成立，所以 $X_0$ 必须作为起点。

但上述情况是在少掉一条边的情况下考虑的。当加入一条边后，入度为零的点则不一定存在了。

那么，什么时候入度为零的点不存在？

**有向环。**

![Pic 4](https://cdn.luogu.com.cn/upload/image_hosting/i5kkvpc9.png)

此时随便选择一个点作为起点即可达成题目要求。

那么转换到代码实现上，大致分为以下几步：

1. 把原有的箭头矩阵转化为有向图;
2. 记录每个点的入度;
3. 寻找入度为 $0$ 的点作为起点，如果找不到就随便找一个点作为起点;
4. 遍历整张图，看看遍历后是否存在未被访问过的节点，如果存在即不能满足题目要求。

总时间复杂度为 $O(nm)$，可以通过此题。

下面放上代码：

```cpp
#include<iostream>
#include<cstdio>
#include<map>
#include<cstring>
#define ll long long
using namespace std;

const int mxn = 1e5+5;

int n,m,rt;
int rn[mxn],in[mxn],to[mxn];
map < pair<int,int>,char > tmp;
map < pair<int,int>,int > pt;
bool vis[mxn],judge;

inline char gc(){
    char ch=getchar();
    while(ch<'a'||ch>'z')
        ch=getchar();
    return ch;
}

void dfs(int x){
    vis[x]=true;
    if(to[x]&&!vis[to[x]])
        dfs(to[x]);
}

int main(){
    int test,cnt;
    scanf("%d",&test);
    while(test--){
        cnt=1;
        memset(in,0,sizeof(in));
        memset(rn,0,sizeof(rn));
        memset(to,0,sizeof(to));
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                pt[make_pair(i,j)]=cnt;
                tmp[make_pair(i,j)]=gc();
                cnt++;
            }
        }  //把每个单元格根据坐标转化成点
        for(int i=1;i<=n;i++){
            for(int st,j=1;j<=m;j++){
                scanf("%d",&st);
                switch(tmp[make_pair(i,j)]){
                    case 'u': 
                        if(i-st>=1) { 
                            to[pt[make_pair(i,j)]]=pt[make_pair(i-st,j)];
                            in[pt[make_pair(i-st,j)]]++;
                            rn[pt[make_pair(i,j)]]++;
                        }break;
                    case 'd':
                        if(i+st<=n) { 
                            to[pt[make_pair(i,j)]]=pt[make_pair(i+st,j)];
                            in[pt[make_pair(i+st,j)]]++;
                            rn[pt[make_pair(i,j)]]++;
                        }break;
                    case 'l':
                        if(j-st>=1) { 
                            to[pt[make_pair(i,j)]]=pt[make_pair(i,j-st)];
                            in[pt[make_pair(i,j-st)]]++;
                            rn[pt[make_pair(i,j)]]++;
                        }break;
                    case 'r':
                        if(j+st<=m) { 
                            to[pt[make_pair(i,j)]]=pt[make_pair(i,j+st)];
                            in[pt[make_pair(i,j+st)]]++;
                            rn[pt[make_pair(i,j)]]++;
                        }break;
                }
            }
        }  //相应进行连边操作
        
        rt=1;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(!in[pt[make_pair(i,j)]]){
                    rt=pt[make_pair(i,j)];
                    break;
                }  //寻找入度为 0 的点，如果没有就从点 1 开始
            }
        }
        memset(vis,0,sizeof(vis));
        dfs(rt);  //dfs遍历
        judge=true;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(!vis[pt[make_pair(i,j)]]){
                    judge=false;
                    break;
                }
            }
        }  //看看是否有未访问的节点，确定是否有解
        printf(judge?"Yes\n":"No\n");
    }
    return 0;
}
```


---

## 作者：SDLTF_凌亭风 (赞：0)

稍微画一下你就会发现，每个格子看作有向图中的一个节点，最终答案构出来的树一定是基环外向树。

根据基环外向树的性质，如果有入度为 $0$ 的点，那么必须从这个点开始遍历；否则随便找一个点开始就行了。

一个技巧是，把二维的网络重新编号成一维，更利于遍历。

代码如下：

```cpp
#include <bits/stdc++.h>
#define floop(i, b, e) for(int i = b; i <= e; ++ i)
using namespace std;
vector<bool> vis; vector<string> s; vector<int> a, d;
int n, m;
bool dfs(int flg, int sgm) { return (sgm == n * m) ? (1) : (flg == -1 || vis[flg] ? (0) : (vis[flg] = 1, dfs(a[flg], sgm + 1))); }
int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	int T; cin >> T;
	for(; T; -- T) {
		cin >> n >> m;
        s.clear(), a.clear(), d.clear(), vis.clear(), vis.resize((n + 1) * (m + 1)), s.resize(n + 1), a.resize(1), d.resize((n + 1) * (m + 1));
		floop(i, 1, n) cin >> s[i];
        int stp, cur, x, y;
        floop(i, 1, n) floop(j, 1, m) {
            cin >> stp, cur = (i - 1) * m + j, x = i, y = j;
            if     (s[i][j - 1] == 'u') cur -= stp * m, x -= stp;
            else if(s[i][j - 1] == 'd') cur += stp * m, x += stp;
            else if(s[i][j - 1] == 'l') cur -= stp,     y -= stp;
            else                        cur += stp,     y += stp;
            if(x < 1 || x > n || y < 1 || y > m) cur = -1; if(~cur) ++ d[cur]; a.emplace_back(cur);
		}
		int num = 0, srt = 1;
		floop(i, 1, n * m) if(!d[i]) ++ num, srt = i;
        (num > 1) ? (cout << "No" << endl) : (dfs(srt, 1) ? (cout << "Yes" << endl) : (cout << "No" << endl));
	}
}
```

---

