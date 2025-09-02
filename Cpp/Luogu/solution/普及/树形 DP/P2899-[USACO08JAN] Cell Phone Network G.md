# [USACO08JAN] Cell Phone Network G

## 题目描述

Farmer John has decided to give each of his cows a cell phone in hopes to encourage their social interaction. This, however, requires him to set up cell phone towers on his N (1 ≤ N ≤ 10,000) pastures (conveniently numbered 1..N) so they can all communicate.

Exactly N-1 pairs of pastures are adjacent, and for any two pastures A and B (1 ≤ A ≤ N; 1 ≤ B ≤ N; A ≠ B) there is a sequence of adjacent pastures such that A is the first pasture in the sequence and B is the last. Farmer John can only place cell phone towers in the pastures, and each tower has enough range to provide service to the pasture it is on and all pastures adjacent to the pasture with the cell tower.

Help him determine the minimum number of towers he must install to provide cell phone service to each pasture.

Farmer John 想让他的所有牛用上手机以便相互交流。他需要建立几座信号塔在 $N$ 块草地中。已知与信号塔相邻的草地能收到信号。给你 $N-1$ 个草地 $(A,B)$ 的相邻关系，问：最少需要建多少个信号塔能实现所有草地都有信号。


## 样例 #1

### 输入

```
5
1 3
5 2
4 3
3 5
```

### 输出

```
2
```

# 题解

## 作者：InnovatorNZ (赞：162)

做法都在注释里了

每次dfs里面都有三种状态：-1,0,1

-1表示要让自己的父亲放天线

0表示自己不用放天线，不过也不用父亲放天线了，因为儿子帮你放好了

1表示自己不得不放天线，即要帮爹（也表示自己被坑了）

别的都看代码的注释就好了（可能是史上最滑稽的注释）





```cpp
#include <iostream>
#include <vector>
using namespace std;
#define maxn 100001
int n; 
int ans=0;
vector<int> conn_matrix[maxn];       //邻接表
int dfs(int u, int p){
    int chosen=-1;    //初始值
    for(auto val:conn_matrix[u]){    //循环每个邻居（儿子&父亲）
        if(val!=p){      //如果当前的val不是父亲，也就是说要对每个儿子枚举，但不包括父亲
            int ret=dfs(val, u);    //看儿子是啥状态
            if(ret==-1)        //如果儿子说要坑爹
                chosen=1;    //那么身为父亲的自己一定要立天线，即要帮爹
            else if(ret==1 && chosen!=1)    //如果儿子说“我要帮你了，我帮爹”，并且没有一个坑爹的儿子（其实近似等价于ret==-1）
                chosen=0;    //可以放飞自我了！即不用靠爹，不过也不用天线
        }
    }
    if(chosen==1) ans++;    //要帮爹了，那么ans++
    return chosen;      //返回自己的状态
}
int main(){
    cin>>n;
    for(int i=0; i<n-1; i++){
        int a, b;
        cin>>a>>b;
        conn_matrix[a].push_back(b);
        conn_matrix[b].push_back(a);    //无向图，双向连接
    }
    if(dfs(1, 0)==-1) ans++;    //如果根节点说：我要坑爹！！！但又没爹可坑，那么只能坑自己，自己放一根天线
    cout<<ans<<endl;    //输出答案
    return 0;
}
```

---

## 作者：zbwer (赞：55)

树形dp挺好的一道题  
这题其实是[P2548 保安站岗](https://www.luogu.org/problem/P2458)的数据弱化版  
$QwQ$双倍经验

---
这题显然是节点选择类的树形dp，我们需要明确父子关系，从而定义出状态，再思考暴力的状态转移，最后考虑优化转移过程。  
### 分析:
```cpp
父子关系:
自己(i),父亲(fa),儿子(son)中必须要存在一个
定义状态： 
f[i][0]表示i被自己覆盖 的最小花费
f[i][1]表示i被儿子覆盖 的最小花费
f[i][2]表示i被父亲覆盖 的最小花费
状态转移：
1.f[i][0]+=min(f[son][1],f[son][2],f[son][0]) 
2.f[i][1]=f[x][0]+sigma(min (f[son][0],f[son][1]) ) 
3.f[i][2]+=min(f[son][0],f[son][1])
    
我们分析一下上面状态转移的过程：
1.此时情况是节点i处放置警察，那么它的儿子可以选择被自己看守(f[son][0])，也可以选择被儿子看守(f[son][1]),当然也可以选择被父亲看守(f[son][2])
转移2有点小难度，我们先分析转移3
3.此时的情况是节点i被父亲覆盖(即i节点没有放置警察),那i的儿子(son)就只能选择被自己看守(f[son][0]),或者被它的儿子的看守(f[son][1])
```

### 现在讨论转移2：

此时的情况是节点$i$处不放置警察，节点$i$由它的儿子看守，那么我们显然要在$i$的众多儿子中，选择一个儿子(对应上面转移方程中的$x$)放置警察，这样当前节点$i$才会被看守到，然后对于剩余的儿子，我们进行和转移方程3一样的操作就可以了，因为此时节点$i$没有放置警察，那$i$的儿子就只能选择被自己看守,或者被它的儿子的看守。

那么我们只需要找到对于节点$i$来说，一个最优的儿子$x$就行了，可以考虑枚举所有儿子，但是也有数学方法来优化，以下内容参考:

题解 P2458 【[SDOI2006\]保安站岗】](https://www.luogu.org/blog/Parabola/solution-p2458)

对于x来说，有$f[i][1]=f[x][0]+\Sigma_{j\subset son(i),j!=x}{min(f[j][0],f[j][1])}$

若x不是最优的，则存在y满足$f[x][0]+\Sigma_{j\subset son(i),j!=x}{min(f[j][0],f[j][1])}<f[y][0]+\Sigma_{j\subset son(i),j!=y}{min(f[j][0],f[j][1])}$

合并同类项，整理得$f[x][0]-min(f[x][0],f[x][1])>f[y][0]-min(f[y][0],f[y][1])$

所以对于最优的x，只需要满足$f[x][0]-min(f[x][0],f[x][1])$是所有儿子中最小的就可以了。

我们不妨设最优的$x$一开始为0，然后对$f[0][0]$赋一个极大值来转移.
## Code:
```cpp

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define Mi return
#define manchi 0

using namespace std;
const int N = 10000+5;
const int INF = 0x3f3f3f3f;
/*
f[i][0/1/2]被自己/儿子/父亲覆盖
f[i][0]+=min(f[son][0/1/2])
f[i][1]=f[son][0]+sigma(f[other_son][0/1])
f[i][2]+=min(f[son][0/1])
 
*/
inline int read()
{
	int num=0,w=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')w=-1;ch=getchar();}
	while(isdigit(ch)) num=(num<<1)+(num<<3)+ch-'0',ch=getchar();
	Mi num*w;
 } 

int n,f[N<<1][3];
int tot,head[N],ver[N<<1],Next[N<<1];

inline void add(int x,int y)
{
	ver[++tot]=y;
	Next[tot]=head[x];
	head[x]=tot;
}

inline void dfs(int x,int fa)
{
	int special_son=0;f[x][0]=1;
	for(int i=head[x];i;i=Next[i])
	{
		int y=ver[i];
		if(y==fa) continue;
		dfs(y,x);
		f[x][0]+=min(f[y][0],min(f[y][1],f[y][2]));
		f[x][2]+=min(f[y][0],f[y][1]);
		if((f[special_son][0]-min(f[special_son][0],f[special_son][1])) > (f[y][0]-min(f[y][0],f[y][1])))
			special_son=y;
	}
	f[x][1]=f[special_son][0];
	for(int i=head[x];i;i=Next[i])
	{
		int y=ver[i];
		if(y==fa || y==special_son) continue;
		f[x][1]+=min(f[y][0],f[y][1]);
	}
}
int main()
{
	n=read();
	for(int i=1;i<n;i++)
	{
		int x=read(),y=read();
		add(x,y);add(y,x);
	}
	f[0][0]=INF;dfs(1,-1);
	printf("%d",min(f[1][0],f[1][1]));
	Mi manchi;
}
typed by zbwer 2019-09-19 16:52
```

---


---

## 作者：loceaner (赞：43)

### 题意

$n$个点，$n-1$条边（这就告诉我们这是一棵树），一个点染色可以传递给相邻的结点（也就是说相邻结点相当于被染色了）并将这些相邻结点覆盖，问最少染多少个结点可以完全覆盖这$n$个结点

### 做法

首先，这是一道**树形DP**基础题

那么，我们考虑一个结点可以被谁染色，不难想出，可以有$3$种情况：被自己染色，被儿子染色，被父亲染色

我们用$f[i][0/1/2]$分别表示$i$这个结点被自己/儿子/父亲染色的最小染色数，即用$f[i][0]$表示自己对自己染色了，用$f[i][1]$表示自己被儿子染色了，用$f[i][2]$表示自己被父亲染色了

那么就可以推出三种状态，我们设目前结点为$u$，他的儿子结点为$v$

#### $1.$**自己被自己染色**

这时我们可以想一下，$u$被自己染色可以由什么转移过来，如果$u$已经被自己染色了的话，他的儿子$v$可以选择自己染色，也可以选择被自己（$v$）的儿子染色，当然也可以被$u$染色，当然，我们要选最小的，所以转移方程就是

$$f[u][0] += \min (f[v][0], f[v][1], f[v][2])(v \in son_u)$$

#### $2.$**被自己的父亲结点染色**

如果被父亲结点($fa$)染色了，那么$u$的儿子$v$只能选择自己染色或者被它的儿子染色，转移方程为

$$f[u][0] += \min (f[v][0], f[v][1])(v\in son_u)$$

#### $3.$**被自己的儿子结点染色**

这是最麻烦的一种情况，因为$u$可能有多个儿子，只要有一个儿子自己染色了，就可以将$u$覆盖，这种情况就成立了

而现在它的儿子有两种情况，分别是自己染色和被它儿子染色

我们可以先假设每个儿子都是被它自己染色（$v$被自己染色）的，然后看一下$u$的每个儿子（$v$）被其儿子染色是否使结果变得更小，把能让结果更小的 自己染色（$v$自己染色）的儿子 替换为 被其儿子染色的儿子（$v$被它儿子染色）的儿子

(参考了$ysner$大佬的思路)

那么怎么实现呢？

1. 先让$f[u][1]$加上所有的$f[v][0]$（也就是假设所有的$v$目前都是自己给自己染色的）
2. 在进行一的同时，用一个$g$数组，表示$v$被儿子染色所需的价值减去$v$被自己染色的价值的差值，同时用一个变量$tot$记录一下一共有多少个儿子，即$g[++tot] = f[v][1] - f[v][0]$
3. 如果$u$没有儿子，即$tot$为$0$，说明$u$是一个叶结点，那么就没有从儿子来的价值，因为转移的时候我们要取小的，所以就把$f[u][1]$设为一个极大值
4. 如果$u$有儿子，就将$g$从小到大排序，如果是负值，我们就可以替换，因为是负值的话就说明，此时的$f[v][1]$比$f[v][0]$小，所以就可以替换，只要是负的，值越小越好，所以就排序一下，是负的就替换，否则就$break$，当然我们最多替换$tot-1$个，因为要保证$u$被染色，必须有一个儿子是自己染色的

至此主要部分就讲完了，需要注意的是每次$dfs$的时候先将$f[u][0]$设为$1$，因为自己给自己染色肯定至少为$1$

然后我们就做完啦~~

### 代码

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

inline int read() {
	char c = getchar();
	int x = 0, f = 1;
	for( ; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for( ; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + (c ^ 48);
	return x * f;
}

const int M = 1e5 + 11;
const int INF = 1e9 + 17;

int n, m;
int f[M][3];//f[i][0/1/2]0表示被自己染了，1表示被儿子染了，2表示被父亲染了 

struct node {
	int nxt, to;
} e[M];

int head[M], cnt;

inline void add(int from, int to) {
	e[++cnt].to = to;
	e[cnt].nxt = head[from];
	head[from] = cnt;
}

bool cmp(int x, int y) {
	return x > y;
}

void dfs(int u, int fa) {
	int tot = 0, g[M]; f[u][0] = 1;
	for(int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if(v == fa) continue;
		dfs(v, u);
		f[u][0] += min(f[v][0], min(f[v][1], f[v][2]));
		f[u][2] += min(f[v][0], f[v][1]);
		f[u][1] += f[v][0];
		g[++tot] = f[v][1] - f[v][0];
	}
	if(!tot) f[u][1] = INF;
	else {	
		sort(g + 1, g + 1 + tot);
		for(int i = 1; i < tot; i++) {
			if(g[i] < 0) f[u][1] += g[i];
			else break;
		}
	}
	return;
}

int main() {
	n = read();
	for(int i = 1; i < n; i++) {
		int x = read(), y = read();
		add(x, y), add(y, x);
	}
	dfs(1, 0);
	printf("%d", min(f[1][0], f[1][1]));
	return 0;
}

```

完结撒花qwq

---

## 作者：PI_AC (赞：30)


# 题目
[手机网络](https://www.luogu.org/problemnew/show/P2899)

---
# 题解
首先我们确定这道题是树形DP，而且可以看出这道题和树的最大独立集有几分相似

那么我们就先打一个树的最大独立集出来，但我们发现这样并不能`AC`

因为树的最大独立集可以全部由结点的儿子转移过来，而这道题还有另一种可能，就是有结点的父亲转移过来，所以我们不能像最大独立集那样定义状态，我们还需要多定义一个状态

$dp[i][j]$，其中$j$只有三种可能，$0$表示$i$号点有通讯塔，$1$表示$i$号点没有通讯塔，它由它父亲的通讯塔管辖，$2$表示$i$号点没有通讯塔，它由它儿子的通讯塔管辖

那么我们就可以分情况对这三种状态进行状态转移方程的讨论：

当$j$等于$0$时，因为$i$点有一个通讯塔，所以$son(i)$有可能从它的父亲（也就是$i$点）转移过来，也有可能有它的儿子转移过来，当然，也有可能它自己本身就有一个通讯塔，即
$$dp[i][0]=\sum Min(dp[son(i)][0],dp[son(i)][1],dp[son(i)][2])+1$$
(因为我们在i结点建立了一个通讯塔，所以要加1)

当$j$等于$1$时，因为$i$点没有通讯塔，所以$son(i)$不可能从它的父亲转移过来，它只有可能由它的儿子转移过来，或者是它自己有一个通讯塔，即
$$dp[i][1]=\sum Min(dp[son(i)][0],dp[son(i)][2])$$
当$j$等于$2$时，因为$i$点没有通讯塔，所以$son(i)$也不可能从它的父亲转移过来，它只有可能由它的儿子转移过来，或者是它自己有一个通讯塔，即
$$dp[i][2]=\sum Min(dp[son(i)][0],dp[son(i)][2])$$
但这样写我们很容易发现一个问题，如果$dp[i][2]$全是从$dp[son(i)][2]$转移过来的话，就证明它的所有儿子都没有通讯塔，那么就不可能将它覆盖，如何避免这种情况呢？

其实我们只需要记录下每一次$dp[son(i)][0]-dp[son(i)][2]$的差值，再取一个$min$值，简单的来说，就是
$$p=Min(dp[son(i)][0]-dp[son(i)][2])$$
在最后，如果我们发现$dp[i][2]$全是从$dp[son(i)][2]$转移过来的话，就再加上一个$p$，就相当于将其中的一个$dp[son(i)][2]$强制转换为了$dp[son(i)][0]$，同时还保证了最小

综上所述
$$dp[i][j]=\begin{cases} \sum Min(dp[son(i)][0],dp[son(i)][1],dp[son(i)][2])+1(j==0) \\ \sum Min(dp[son(i)][0], dp[son(i)][2])(j==1) \\ \sum Min(dp[son(i)][0], dp[son(i)][2])(j==2\ and\ flag==1) \\ \sum Min(dp[son(i)][0], dp[son(i)][2])+p(j==2\ and\ flag==0) \end{cases}$$
$flag$表示$dp[i][2]$是否由一个或多个$dp[son(i)][0]$转移过来

值得注意的是，最后输出的是$Min(dp[root][0],dp[root][2])$，因为最后的根结点是不可能有父亲的

----
# 代码
```cpp
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
#define reg register
 
template <class T>
inline T read() {
    T x = 0; T f = 1; char s = getchar();
    while(s < '0' || s > '9') {if(s == '-') f = -1; s = getchar();}
    while(s >= '0' && s <= '9') {x = (x << 3) + (x << 1) + s - 48; s = getchar();}
    return x * f;
}
 
template <typename T>
inline void wri(T x) {
    if(x < 0) {x = -x; putchar('-');}
    if(x / 10) wri(x / 10);
    putchar(x % 10 + 48);
}
 
template <typename T>
inline void write(T x, char s) {
    wri(x);
    putchar(s);
}
 
template <typename T>
inline T Min(T x, T y) {return x < y ? x : y;}
 
#define MAXN 10005
#define INF 0x3f3f3f3f
 
vector <int> G[MAXN];
 
int n;
int dp[MAXN][3];
bool vis[MAXN];
 
inline void dfs(int x) {
    vis[x] = 1;
    bool flag = 0;
    int siz = G[x].size(), p = INF;
    for(reg int i = 0;i <= siz - 1;i ++)
        if(! vis[G[x][i]]) {
            dfs(G[x][i]);
            dp[x][0] += Min(dp[G[x][i]][0], Min(dp[G[x][i]][1], dp[G[x][i]][2]));	//状态转移
            dp[x][1] += Min(dp[G[x][i]][0], dp[G[x][i]][2]);
            if(dp[G[x][i]][0] <= dp[G[x][i]][2]) {
                flag = 1;
                dp[x][2] += dp[G[x][i]][0];
            }
            else {
                p = Min(p, dp[G[x][i]][0] - dp[G[x][i]][2]);
                dp[x][2] += dp[G[x][i]][2];
            }
        }
    if(! flag)
        dp[x][2] += p;
    dp[x][0] ++;	//如果自己有通讯塔，要加上自己的那一个
}
 
int main() {
    n = read<int>();
    for(reg int i = 1;i <= n - 1;i ++) {
        int a = read<int>(), b = read<int>();
        G[a].push_back(b);	//用邻接表储存这棵树
        G[b].push_back(a);
    }
    dfs(1);	//dfs求解DP
    write(Min(dp[1][2], dp[1][0]), '\n');
    return 0;
}
```



---

## 作者：iwprc (赞：23)

一道树形dp,不过楼下讲的实在是太简短了，我要有所补充。

首先有3个状态：

1.f[i][0]表示不在第i块草地建信号塔，i和i的子树均有信号

2.f[i][1]表示在第i块草地建信号塔，i和i的子树均有信号

3.f[i][2]表示不在第i块草地建信号塔，i的子树均有信号,i无信号

则3个状态的转移方程分别为

1.f[i][2]=∑f[i.child][0]

2.f[i][1]=∑min(f[i.child][0],f[i.child][1],f[i.child][2])

3.f[i][0]=min(f[i.child-j][1]+∑min(f[i.child-k][0],f[i.child-k][1]))  (j是i的一个孩子，j!=k)

最后输出min(f[root][0],f[root][1])

代码：

```cpp
#include<cstdio>
const int N=200000;
const int MAX=100000;
int n,i,a,b,h[N],t[N],name[N],f[N][3];
int min(int x,int y){return x<y?x:y;}
int dfs(int i,int j,int fa){//当前计算f[i][j],fa是i的父亲
    if(f[i][j]>=0)
        return f[i][j];
    f[i][j]=0;
    if(j==2){
        for(int k=h[i];k;k=t[k])
            if(name[k]!=fa)
                f[i][2]+=dfs(name[k],0,i);
        return f[i][2];
    }
    if(j==1){
        for(int k=h[i];k;k=t[k])
            if(name[k]!=fa)
                f[i][1]+=min(min(dfs(name[k],0,i),dfs(name[k],1,i)),dfs(name[k],2,i));
        return ++f[i][1];
    }
    if(j==0){
        f[i][0]=MAX;int s=0;
        for(int k=h[i];k;k=t[k])
            if(name[k]!=fa)
                s+=min(dfs(name[k],0,i),dfs(name[k],1,i));
            //s=∑min(f[i.child][0],f[i.child][1])
        for(int k=h[i];k;k=t[k])
            if(name[k]!=fa)
                f[i][0]=min(f[i][0],dfs(name[k],1,i)+s-min(dfs(name[k],0,i),dfs(name[k],1,i)));
                //s-min(dfs(name[k],0,i),dfs(name[k],1,i))=∑min(f[i.child-j][0],f[i.child-j][1])(j!=k)
        return f[i][0];
    }
}    
int main(){
    scanf("%d",&n);
    for(i=1;i<n;i++){
        scanf("%d%d",&a,&b);
        t[i]=h[a];
        h[a]=i;
        name[i]=b;
        t[i+n]=h[b];
        h[b]=i+n;
        name[i+n]=a;
        f[i][0]=f[i][1]=f[i][2]=-1;
    }
    f[i][0]=f[i][1]=f[i][2]=-1;
    printf("%d",min(min(dfs(1,0,0),dfs(1,1,0)),dfs(1,2,0)+1));//记忆化搜索
    return 0;
}

```

---

## 作者：KagurazakaLorna (赞：20)

首先说2件事：

1.本题不需要树形DP~~（因为我不会）~~

2.本题也不需要~~奇怪的~~数据结构来维护

好了，然后是正常的题解：

思路是贪心。

考虑每一个叶子节点，我们可以发现。如果要覆盖一个叶子节点，最优的方案显然是在它的父亲节点上建立一个信号塔。

因此，我们每次找一个节点，该节点满足：它的子树已经被完全覆盖了（OR叶子节点）。然后，在这个节点的父亲节点建立信号塔，并且覆盖相邻的节点。重复以上操作。

我看到楼下有一位写贪心的巨佛说要用数据结构维护深度最大且没有被覆盖的节点，其实不需要。

我们可以在建树时，当回溯上来以后（OR当前点是叶子节点时）判断该点是否被覆盖过，若没有则覆盖其父亲和父亲的相邻节点。显然，当回溯到当前节点时，其子树已经被完全覆盖。

然后推荐一道思路类似的题目：

[P2279 [HNOI2003]消防局的设立](https://www.luogu.org/problemnew/show/P2279)

下面贴程序~~（Ugly）~~：
```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> path[10003];
inline void init() {
    scanf("%d",&n);
    for (register int i=1;i<n;++i) {
        int u,v;
        scanf("%d %d",&u,&v);
        path[u].push_back(v);
        path[v].push_back(u);
    }
    return;
}

int dep[10003],grand[10003];
int ans=0;
int vis[10003];
inline void build(int root) {
    for (register int i=0;i<path[root].size();++i) {
        int son=path[root][i];
        if (dep[son]>0) continue;
        dep[son]=dep[root]+1,grand[son]=root;
        build(son);
    }
    if (!vis[root]) {
        ++ans;
        int pos=grand[root];
        vis[pos]=1;
        for (register int i=0;i<path[pos].size();++i) 
            vis[path[pos][i]]=1;
    }
    return;
}

int main() {
    init();
    memset(dep,0,sizeof(dep));
    dep[1]=1; grand[1]=1;
    build(1);
    printf("%d\n",ans);
    return 0;
}

```

---

## 作者：Apro1066 (赞：15)

#### 或将成为本题最详细题解。


## 思路
有一点像树的最大独立集。

首先对于每个节点$i$，都有如下3种选择：

不选自己，选儿子；

不选自己，选父亲；

我自己选我自己。

令$dp[i][0/1/2]$为节点$i$及其节点$i$的子树中全部被信号覆盖所需的最小信号塔数，$dp[i][0]$表示点$i$有信号塔，$dp[i][1]$为点$i$没有信号，也就是就是父亲有信号塔，$dp[i][2]$表示节点$i$被间接信号，也就是儿子有信号塔。

**1.$dp[i][0]$**

因为节点$i$有信息塔，所以对于$i$的子节点$son$，它可以没有信号塔，也可以有信号塔，也可以从$son$的子节点转移过来。因此：

$$dp[i][0]=∑min(dp[son][1],dp[son][0],dp[son][2])+1$$

这里$+1$是因为自己本身放置了一个信号塔。

**2.$dp[i][1]$**

因为节点$i$没有信息塔，靠的是节点$i$的父亲才有信号的，所以对于节点$i$的子节点$son$是不可能选父亲的。所以$dp[i][1]$可以从$dp[son][0]$转移过来（子节点有信息塔），也可以从$dp[son][2]$转移过来（子节点的儿子有信息塔）。

$$dp[i][1]=∑min(dp[son][0[,dp[son][2])$$

**3.$dp[i][2]$**

因为节点$i$没有信息塔，靠它儿子，所以节点$i$的子节点$son$也不可能选父亲，必然可以从$dp[son][0]$转移过来，也可以从$dp[son][2]$转移过来。

$$dp[i][2]=∑min(dp[son][0],dp[son][2])$$

很快会发现，如果的确是这样的话，如果$dp[i][2]$**全**从$dp[son][2]$转移过来，也就是若**恒有**$dp[son][2] \leq dp[son][0]$，**就意味着节点i的所有子节点都没有信息塔！**（~~那不就凉了~~）怎么办？

所以我们要设立一个**反悔机制**。**我只需要一个儿子选**。只需要用$p$来记录每一次$dp[son][0]-min(dp[son][2],dp[son][0])$，这样就保证，**就算恒有$dp[son][2] \leq dp[son][0]$，也一定有一个是儿子选了的**，如果不选$dp[son][2]$，最后$p$的状态也为$0$。若不信，我们做个推导：

记$p=min(p,dp[son][0]-min(dp[son][0],dp[son][2]))$

$dp[i][2]=min(dp[son][0],dp[son][2])+p$

$=min(dp[son][0],dp[son][2])+dp[son][0]-min(dp[son][0],dp[son][2])$

若$dp[son][2] \leq dp[son][0]$恒成立**（注意我说的是恒成立，意思是说$dp[i][2]$全是从$dp[son][2]$转移过来）**

原式$=dp[son][2]+dp[son][0]-dp[son][2]$

$=dp[son][0]$

**也就是把$dp[son][2]$强制转换成了$dp[son][0]$！**

若$dp[son][2]>dp[son][0]$

原式$=dp[son][0]+dp[son][0]-dp[son][0]$

$=dp[son][0]$

也就是说并不影响$dp[son][0]$的正常取值！

最后答案为$min(dp[root][0],dp[root][2])$。
```cpp
#include <stdio.h>
#include <iostream>
#define inf 2e9+7
#define maxn 300001
using namespace std;
int n,cnt,head[maxn],s,dp[maxn][3];
struct node
{
	int to,nxt;
}e[maxn<<1];
inline void add(int u,int v)
{
	e[++cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
void dfs(int i,int fa)
{
	bool f(0);
	register int j,p(inf);
	for(j=head[i];j;j=e[j].nxt)
	{
		int v(e[j].to);
		if(v==fa) continue;
		dfs(v,i);
		dp[i][0]+=min(dp[v][1],min(dp[v][0],dp[v][2]));
		dp[i][1]+=min(dp[v][0],dp[v][2]);
		dp[i][2]+=min(dp[v][0],dp[v][2]);
		p=min(p,dp[v][0]-min(dp[v][2],dp[v][0]));//表示其它儿子的总和
	}
	dp[i][2]+=p;//最后再进行反悔操作
	dp[i][0]++;//最后再进行放置信号塔操作 
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	register int i,j;
	cin>>n;
	for(i=1;i<=n-1;i++)
	{
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	dfs(1,-1);
	cout<<min(dp[1][0],dp[1][2])<<endl;
	return 0;
}
```

---

## 作者：SimonSu (赞：13)

其他题解只给了转移方程而没有给清楚为什么是这样的 我在这就简要的分享一下自己的想法吧

### 首先这是一棵树

我们定义 三种状态：

```cpp
0.我自己不选，我有儿子选

1.我自己不选，我父亲选

2.我自己选
```

0状态需要建立反悔机制，因为我只需要一个儿子选，

先推导 dp[x][0]=min(dp[v][0],dp[v][2]); 注意：因为当前节点是不选的，所以他儿子是父亲选择的状态不应该列入考核范围内。

这个式子推出来后可能照成的结果是儿子都没选 ~~那我不就凉了~~ 建立反悔，

t=min(t,dp[v][2]-min(dp[v][0],dp[v][2])) 保证一定有一个是儿子选了的，而且如果不本身就有儿子已经选了的状态t会为0


1状态是不选 所以不能接受儿子对他的依赖 所以 dp[x][1]+=min(dp[v][0],dp[v][2])


2状态呢是自己要选 儿子怎样都可以 dp[x][2]+=min(dp[v][0],min(dp[v][1],dp[v][2]))

于是我们就可以开始愉快的写代码了

可能~~我~~大家会有一个疑问 如果是叶子节点，不就不能产生儿子选的状态了吗？？

我们建立的反悔机制在进入时给的是极大值，最后会加上去，如果本身就很大，没有更新就加上去了 肯定不会有点选的

```cpp
#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<queue>
#include<stack>
#include<cmath>
#define LL long long
using namespace std;
inline void read(int &x){
	x=0;int f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-') f=-1;c=getchar();	}
	while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
	x*=f;
}
struct node{
	int v,nxt;
}e[10010<<1];
int head[10010],tot;
inline void add(int x,int y)
{
	tot++;
	e[tot].v = y;
	e[tot].nxt = head[x];
	head[x] = tot;
}
int dp[10010][3];//0不选 儿子选  1不选 父亲选 2自己选 
inline void dfs(int x,int fa)
{
	dp[x][0]=0;
	dp[x][1]=0;
	dp[x][2]=1;
	int t=99999999;
	for(int i=head[x];i;i=e[i].nxt)
	{
		int v = e[i].v;
		if(v == fa) continue;
		dfs(v,x);
		dp[x][0]+=min(dp[v][0],dp[v][2]);
		t=min(t,dp[v][2]-min(dp[v][0],dp[v][2]));
		dp[x][1]+=min(dp[v][0],dp[v][2]);//父亲选 儿子不是父亲选随便 
		dp[x][2]+=min(dp[v][0],min(dp[v][1],dp[v][2]));//我选 
	}
	dp[x][0]+=t;
} 
int n,m,a,b;
int main()  
{     
    read(n);
    for(int i=1;i<n;i++)
        read(a),read(b),add(a,b),add(b,a);
    dfs(1,0);
    printf("%d",min(dp[1][0],dp[1][2]));
    return 0;
}  
```


---

## 作者：Orzalpha (赞：9)

本题的基本思路是贪心和图论。

看到有的大佬还写了回溯，正儿八经地当棵树来处理，我~~乱七八糟~~写了一个代码也没考虑回溯什么的就过了。

首先观察题意我们可以知道，这道题给出的是一棵树。对于一棵树而言，它的叶子结点如果想要有信号的话，必须在它自己或者它的父亲那里有一座信号塔，而显然在他父亲那里建一座信号塔要更优一些
。

（因为如果建在这个叶子结点自身的话，只能使这个结点和它的父亲
有信号，而如果建在它的父亲那里，则会使叶子结点、它的父亲、它
的兄弟（如果有的话）、它的祖父都会有信号）

然后我们把这个叶子结点删去。而对于已经有信号的叶子结点而言，就可以直接把它删去了。这样，不断地删去有信号的叶子结点，最后就删完了，输出答案。

另外，还有一个问题就是，当只剩下两个直接相连的结点时，如果直接删去其中一个已经有信号的点，会造成漏掉一座塔的情况，因此应当最后再遍历一遍，如果有没有信号的点，就再加一座塔。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,du[10001],q[66666],hd,tl,ans;//du[]记录与某个点相连的边数，如果为1则该点为叶子
int nex[20001],fir[10001],poi[20001],sum;
bool v[20001],u[20001]; //u[]数组记录某个点是否有信号
inline void draw(int a,int b)
{
	nex[++sum]=fir[a];
	poi[sum]=b;
	fir[a]=sum;
}
void re(int &num)
{
	char c;
	num=0;
	while((c=getchar())<'0'||c>'9');
	num=c-'0';
	while((c=getchar())>='0'&&c<='9') num=num*10+c-'0';
}
void search(int x)//核心搜索函数
{
	hd=tl=0;
	q[++tl]=x;
	v[x]=1;
	while(hd<tl)
	{
		int now=q[++hd];
		for(int i=fir[now]; i; i=nex[i])
		{
			int p=poi[i];
			if(!v[p])
			{
				du[now]--;
				du[p]--;//删去该点，即删去该点的出边与该点的父亲的入边
				if(du[p]==1)//如果该点变为叶子，入队
				{
					q[++tl]=p;
					v[p]=1;
				}
				if(u[now]) continue;//若该点有信号，则跳过建塔过程
				ans++;
				u[p]=1;
				for(int j=fir[p]; j; j=nex[j]) //建塔
				{
					int k=poi[j];
					if(!u[k]) u[k]=1;
				}
			}
		}
	}
	return;
}
int main()
{
	int a,b;
	scanf("%d",&n);
	for(register int i=1; i<n; i++)
	{
		re(a);re(b);
		du[a]++;du[b]++;
		draw(a,b);draw(b,a);
	}
	for(register int i=1; i<=n; i++)
	if(du[i]==1) search(i);         //是叶子节点的话就遍历
	for(register int i=1; i<=n; i++) //遍历查看是否有漏掉的点
		if(!u[i]) ans++;
	printf("%d",ans);
	return 0;
}
```


---

## 作者：JACKLOVEONE (赞：8)

# 总结：树形dp
## dp[u][0] 被自己守
## dp[u][1] 被父亲守
## dp[u][2] 被儿子守


------------

### dp[u][0] += min(dp[v][1], min(dp[v][0], dp[v][2]));//儿子三种情况都可以

### dp[u][1] += min(dp[v][0], dp[v][2]);//儿子只有这两种情况

### for(枚举v)//枚举被哪个儿子守,利用已经计算好的dp[u][1]

### dp[u][2] = min(dp[u][2], dp[u][1] - min(dp[v][0], dp[v][2]) + dp[v][0]);

 

### 初始化dp[u][0] = val[u], dp[u][2] = inf;
```cpp
#include<bits/stdc++.h>
 
using namespace std;
const int maxn = 300005;
 
int n, head[maxn], cnt = 1;
 
#define inf 10000007
int dp[maxn][3], val[maxn];
struct Node{
    int v, nxt;
} G[maxn];
 
void insert(int u, int v) {
    G[cnt] = (Node) {v, head[u]}; head[u] = cnt++;
} int in[maxn];
/*
dp[u][0] 被自己守
dp[u][1] 被父亲守
dp[u][2] 被儿子守
*/
void DP(int x, int fa) {
    dp[x][0] = 1; dp[x][2] = inf;
    for (int i = head[x]; i; i = G[i].nxt) {
        int v = G[i].v; if(v == fa) continue;
        DP(v, x); dp[x][0] += min(dp[v][1], min(dp[v][0], dp[v][2]));
        dp[x][1] += min(dp[v][0], dp[v][2]);
    }
    for (int i = head[x]; i; i = G[i].nxt) {
        int v = G[i].v; if(v == fa) continue;
        dp[x][2] = min(dp[x][2], dp[x][1] - min(dp[v][0], dp[v][2]) + dp[v][0]);
    }
}
 
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n - 1; ++i) {
        int x; scanf("%d", &x);
            int y; scanf("%d", &y);
            insert(x, y); insert(y, x);
    }
    DP(1, -1);
    printf("%d\n", min(dp[1][0], dp[1][2]));
    return 0;
}
```

---

## 作者：henry_y (赞：5)

本题正解树形dp

但是dp是不可能dp的，这辈子都不可能dp的，所以我们来考虑一下贪心做法

注意到每个点都要被选到，而且被选到的方法只有自己被选走或者相邻的点被选走，而且这是一棵树

所以我们先考虑一下在树中深度最大的节点，显然选它的父亲更划算

所以选走它的父亲，并将相邻的点全部扔掉

于是发现对新的树也可以这么做然后搞成一个更小的树直到整棵树没了（同理大法好）

但是你如果暴力去搞的话会$n^2$，所以考虑拿一个数据结构维护一下

因为每次都要选深度最大的点，所以用大根堆来维护深度就好

这样就能$nlogn$维护

至于怎么丢掉这些相邻节点，开一个vis数组来维护一下每个数有没有被丢掉，每次从堆中pop出堆顶的时候判一下它有没有被丢掉就好

正确性？~~（留给读者思考）~~

~~（我举不出反例，所以假定它是正确的，然后也确实能过，不过如果哪位大爷能推翻我这个贪心的话就跟我说一下呗，让我涨一下姿势）~~


```
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#define ll long long
#define inf 1<<30
#define il inline 
#define in1(a) read(a)
#define in2(a,b) in1(a),in1(b)
#define in3(a,b,c) in2(a,b),in1(c)
#define in4(a,b,c,d) in2(a,b),in2(c,d)
il void readl(ll &x){
    x=0;ll f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    x*=f;
}
il void read(int &x){
    x=0;int f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    x*=f;
}
using namespace std;
/*===================Header Template=====================*/
#define N 100010
struct edge{int to,next;}e[N<<2];
struct node{
    int dep,id,f;
    bool operator < (const node &x) const {
        return dep<x.dep;
    }
}a[N<<1];
int n,cnt=0,head[N<<2];
void ins(int u,int v){
    e[++cnt].to=v;e[cnt].next=head[u];head[u]=cnt;
}
bool vis[N];
void dfs(int x,int f,int dep){
    a[x].dep=dep;
    a[x].f=f;
    a[x].id=x;
    for(int i=head[x];i;i=e[i].next)
        if(e[i].to!=f)
            dfs(e[i].to,x,dep+1);
}
priority_queue<node>q;
int main(){
    in1(n);
    for(int i=1;i<n;i++){
        int u,v;
        in2(u,v);
        ins(u,v);ins(v,u);
    }
    dfs(1,1,1);
    for(int i=1;i<=n;i++)q.push(a[i]);
    int ans=0;
    while(!q.empty()){
        node t=q.top();q.pop();
        if(vis[t.id])continue;
        vis[t.id]=1;
        vis[t.f]=1;
        ans++;
        for(int i=head[t.f];i;i=e[i].next){
            int v=e[i].to;
            if(!vis[v])vis[v]=1;
        }
    }
    printf("%d\n",ans);
    return 0;
}
```
 

---

## 作者：ysner (赞：4)

**树形DP**

可知一个点被控制有且仅有一下三种情况：

**1、被父亲节点上的信号塔控制**

**2、被儿子节点上的信号塔控制**

**3、被当前节点上的信号塔控制**

我们设dp[u][0/1/2]表示u节点所在子树中全部被信号所需的最小塔数。(u为父亲，v为儿子）

dp[u][0]表示该点没有信号（就是父亲有塔）;
dp[u][1]表示该点有塔;
dp[u][2]表示该点被间接信号。

显然，dp[u][0]可以承接dp[v][2]的值（因自己无信号,所以儿子无塔）

dp[u][1]可承接dp[v][0/1/2]的值（因不确定儿子是否有塔、有信号）

**难点**其实在dp[u][2] 2情况,因为要成立2只要求任意一个儿子有塔（情况1儿子）即可

而每个儿子此时有1,2两种情况

于是我们可以先假设每个儿子都有塔

然后根据“儿子无塔是否使结果更小”这一原理,将 无塔能使结果更小的 情况1儿子 替换为 情况2儿子

**实现方式：**

**step 1：**给f[u][2]加上所有的f[v][1]值（假设每个儿子有塔）

**step 2**:用son数组存下f[v][2]-f[v][1],这个值为负就说明将该情况1儿子替换为情况2儿子有利,负值越大就越有利,越应优先替换（即f[v][2]小于f[v][1],能使结果更小）

**step 3**:给son排序,越有利越靠前

**step 4**:在 替换有利（son[i]<0) 且 一个儿子有塔(cnt-1)的前提下,实现替换

还是很考验思维的，推荐大家看完后自己再把DP式推一遍，然后看看[SDOI2006]保安站岗（只是加了个权值而已）。

```
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define ll long long
#define re register
#define il inline
#define fp(i,a,b) for(re int i=a;i<=b;i++)
#define fq(i,a,b) for(re int i=a;i>=b;i--)
using namespace std;
const int N=100005;
int n,m,h[N]={},w[N]={},in[N]={},out[N]={},root,id,u,v,cnt,ans=0;
ll f[N][3]={};//0表示没有信号（就是父亲有塔）,1表示有塔,2表示被间接信号,dp值保证这个子树中除根节点外一定会被信号
struct Edge
{
  int to,next;
}e[N<<1];
il void add(re int u,re int v)
{
  e[++cnt]=(Edge){v,h[u]};h[u]=cnt;
}
il int gi()
{
    re int x=0;
    re int t=1;
    re char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
    if(ch=='-') t=-1,ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-48,ch=getchar();
    return x*t;
}
il void dfs(re int u,re int fa)
{
  f[u][1]=1;
  re int son[1005]={},cnt=0;
  for(re int i=h[u];i+1;i=e[i].next)
    {
      re int v=e[i].to;
      if(v==fa) continue;
      dfs(v,u);
      f[u][0]+=f[v][2];
      f[u][1]+=min(f[v][0],min(f[v][1],f[v][2]));
      f[u][2]+=f[v][1];
      son[++cnt]=f[v][2]-f[v][1];
   }
  if(!cnt) f[u][2]=1e9;//没儿子就别谈被儿子信号了
  sort(son+1,son+1+cnt);
  fp(i,1,cnt-1)
    if(son[i]<0) f[u][2]+=son[i];//step 4:在 替换有利（son[i]<0) 且 一个儿子有塔(cnt-1)的前提下,实现替换
    else break;
}
int main()
{
  memset(h,-1,sizeof(h));
  n=gi();
  fp(i,1,n-1) u=gi(),v=gi(),add(u,v),add(v,u);
  dfs(1,0);
  printf("%lld\n",min(f[1][1],f[1][2]));//没有f[1][0],因为根节点无父亲
  return 0;
}


```

---

## 作者：lgnotus (赞：3)

推荐在博客中看。。。
# 分析

### 状态表示

考虑到每个节点都必须有信号，所以每个节点安放信号塔只有三种情况，我们用$dp[i][0\sim 2]$来表示这三种情况：
*   $dp[i][0]$表示$i$号节点放通讯站,他所在子树全部由信号的最少花费
*   $dp[i][1]$表示$i$号节点的父亲放通讯站,他所在子树全部由信号的最少花费
*   $dp[i][2]$表示$i$号节点的儿子放通讯站,他所在子树全部由信号的最少花费

### 状态转移方程
对于$dp[u][0]$，易得：
$$dp[u][0]=\sum_{v \epsilon \ son(v)} \min{(dp[v][0],dp[v][1],dp[v][2])}+1$$
对于$dp[u][1]$:
$$dp[u][1]=\sum_{v \epsilon \ son(v)} \min{(dp[v][0],dp[v][2])}$$
对于$dp[u][2]$，我们发现对于$u$号节点，它可以由$dp[v][0]$和$dp[v][2]$转移过来，但$u$的儿子节点必须至少有一个节点的信号站建立在本地。

我们可以设$flag$变量表示$dp[u][2]$是否全部按照$dp[v][2]$转移过来的，再令
$$tmp=\min_{v\epsilon \ son(u)}(dp[v][0]-dp[v][2])$$
很容易看出，当$dp[u][2]$全部按照$dp[v][2]$转移过来时，$dp[u][0]+=tmp$

整理一下：
$$dp[u][2]=\left\{
    \begin{aligned}
    &\sum_{v\epsilon\ son(u)}\min(dp[v][0],dp[v][2])(flag==0)\\
    & \sum_{v\epsilon \ son(u)} \min(dp[v][0],dp[v][2])+tmp(dlag==1)
    \end{aligned}
\right.
$$
## code
```cpp
/*
dp[i][0]表示i号节点放通讯站,他所在子树全部由信号的最少花费
dp[i][1]表示i号节点的父亲放通讯站,他所在子树全部由信号的最少花费
dp[i][2]表示i号节点的儿子放通讯站,他所在子树全部由信号的最少花费
*/

#include<bits/stdc++.h>
using namespace std;

int n,dp[10001][3];
vector<int>g[10001];

void dfs(int u,int fa){
    dp[u][0]++;
    int tmp=INT_MAX;
    bool flag=1;
    for(int i=0;i<g[u].size();i++){
        int v=g[u][i];
        if(v!=fa){
            dfs(v,u);
            dp[u][0]+=min(dp[v][0],min(dp[v][1],dp[v][2]));
            dp[u][1]+=min(dp[v][0],dp[v][2]);
            if(dp[v][0]>dp[v][2])tmp=min(tmp,dp[v][0]-dp[v][2]);
            else flag=0;
            dp[u][2]+=min(dp[v][0],dp[v][2]);
        }
    }
    if(flag)dp[u][2]+=tmp;
}

int main(){
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1,0);
    cout<<min(dp[1][0],dp[1][2])<<endl;
    return 0;
}

```

---

## 作者：蒟蒻zExNocs (赞：3)

## 杂言：

这个题很明显可以用树形dp，跟 [P2016战略游戏](https://www.luogu.org/problemnew/show/P2016) 
有点像，不过这两个题是不同的，P2016的题是需要全部边被占，包含全部点被占的情况，而这个题并不一定所有边都会被占。

这个题跟另一个树形dp [UVA1218 完美服务](https://www.luogu.org/problemnew/show/UVA1218) 
也有点像，不过本题比完美服务的题要麻烦一点。（完美服务的题可以参考刘汝佳的《算法竞赛入门经典》（紫书），会发现这两个状态转移方程如出一辙，当然不完全相同）

===============分界线=============

## 具体题解:

既然是用动态规划了，那么就需要定义状态，当然状态不一定是唯一的，那么我们需要定义多个数组。既然是树形dp，那么我们可以用回溯的方式从子节点推出其父节点，即每个节点的状态是由子节点转移来，那么状态转移的时候就需要从子节点的视角考虑。

我们定义：

### dp[u][0]为 u一定为信号塔，那么他的儿子和父亲有可能是信号塔

### dp[u][1]为 u不是信号塔，u父亲一定是信号塔，儿子有可能是信号塔

### dp[u][2]为 u不是信号塔，他儿子至少有一个是信号塔，父亲有可能是信号塔

那么我们从u的子节点v来分析：

 0:v的父亲是信号塔，v以及v的儿子有可能是信号塔，那么dp[u][0]由dp[v][0~2]推出来，取最小值。

 1:v的父亲不是信号塔，v和他的儿子有可能是信号塔，那么dp[u][1]由dp[v][0]和dp[v][2]推出来，取最小值。

 2:v的父亲不是信号塔，v和他的儿子有可能是信号塔，但是所有v中至少有一个是信号塔，那么这个状态就比较难推了，这时候就不能只由一个v的视角来状态转移了。我们可以枚举一定是信号塔的v，枚举哪个v一定是信号塔后(对于这个v来讲是dp[v][0])，无视这个是一定是信号塔的v，那么对于其他不一定是信号塔的v节点来说状态转移变成了<1>的情况，那么我们就把不一定是信号塔的子节点的min(dp[v][0],dp[v][2])相加和枚举出的一定是信号塔的v的dp[v][0]相加。设u的子节点v有m个，枚举一定是信号塔的v是O(m),再把其他子节点v的min(0,2)值相加是O(m)，那么总需要O(m²）次。很容易超时。我们可以从另一个角度来想，先把所有的min(dp[v][0],dp[v][2])相加（即dp[u][1]），然后枚举一定是信号塔的v时把一定是信号塔的v的min(dp[v][0],dp[v][2])减去，再加上dp[v][0]，那么时间复杂程度就降到了O(2m)

那么我们就很愉快的写出来状态转移方程了~

## $ dp[u][0]=Σmin(dp[v][1],dp[v][2],dp[v][0]) +1$

## $ dp[u][1]=Σmin(dp[v][0],dp[v][2]) $

## $ dp[u][2]=min(dp[u][2],dp[u][1]-min(dp[v][2],dp[v][0])+dp[v][0]) $

那么需要初始化dp[u][0]=1（相当于上述状态转移方程的+1）

$ code: $（奇怪的码风）

```
#include<bits/stdc++.h>
using namespace std;
#define ll int
#define gc(a) a=getchar()
#define pc(a) putchar(a)
#define rg register
const ll maxn=10010;
const ll INF=0x3f3f3f3f;
ll read(){
    char c;ll x=0;bool flag=0;gc(c);
    while(c<'0'||c>'9'){if(c=='-') flag=1;gc(c);}
    while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48),gc(c);}
    return flag?-x:x;
}
void pr(ll x){
    if(x<0){x=-x;pc('-');}
    if(x>9) pr(x/10);
    pc(x%10+48);
}
//---------快读------------
struct Edge
{
    ll v,nx;
    Edge(ll v,ll nx):v(v),nx(nx){}
};
vector<Edge>edge;
ll head[maxn];
void edgepush(ll u,ll v,bool f)
{
    edge.push_back(Edge(v,head[u]));
	head[u]=edge.size()-1;
	if(f) edgepush(v,u,0);//双向建边
}
ll n,dp[maxn][3];
void dfs(ll u,ll fa)
{
	dp[u][0]=1;dp[u][2]=INF;
	for(int v,i=head[u];i;i=edge[i].nx)
	{
		v=edge[i].v;if(v==fa) continue;
		dfs(v,u);
		dp[u][0]+=min(dp[v][1],min(dp[v][0],dp[v][2]));
		dp[u][1]+=min(dp[v][0],dp[v][2]);
	}
	for(int v,i=head[u];i;i=edge[i].nx)
	{
		v=edge[i].v;if(v==fa) continue;
		dp[u][2]=min(dp[u][2],dp[u][1]-min(dp[v][2],dp[v][0])+dp[v][0]);
	}
	
}
int main()
{
	edge.push_back(Edge(0,0));
	n=read();
	for(int i=1;i<n;i++)
	edgepush(read(),read(),1);//正常建边就可以了
	dfs(1,0);
	pr(min(dp[1][0],dp[1][2]));//因为根节点没有父节点，所以就是0和2的最小值了
}
```




---

## 作者：saxiy (赞：3)

介绍一个转移的技巧 **&&** 详细的状态转移解释

### 题目分析：

考虑树的一条枝干的任意子段，出现以下 $3$ 三种情况是允许的：

1. 建 --- 建

2. 建 --- 不建 --- 建

3. 建 --- 不建 --- 不建 --- 建

竖着看，对于一个节点，最远不建站的节点是自己的儿子的儿子，这时候，自己必须要建站，不然儿子将没有信号。

那么对于节点我们就可以设三种状态，分别是：

1. $f[i][0]$ 自己建站

2. $f[i][1]$ 自己不建，儿子至少有一个建站（这种状态的意义是 **可以不需要父亲建站**，因为自己的儿子已经给了自己信号）

3. $f[i][2]$ 自己不建，儿子也不建（这种状态要求儿子必须要已经有信号，父亲必须要建站）

现在来分条考虑转移：

#### 1. 自己建站：

- 自己动手，丰衣足食，可以由儿子的所有状态转移而来

$$f[i][0]=\sum_{i->j}\min(f[j][0],f[j][1],f[j][2])$$

#### 2. 自己不建，儿子至少有一个建站（最烦人的状态）:

- 首先这个状态肯定不能由儿子的 $3$ 状态转移而来（想想为什么）。因为可多个儿子建站，我们先不管是否存在至少一个儿子最优状态是 $1$ 状态（建站状态），每次贪心取儿子 $1,2$ 状态最小的代价转移，同时记录儿子从 $2$ 状态改取为 $1$ 状态的最小花费，如果最后最小花费为负，说明存在至少一个儿子最优状态是 $1$ 状态，贪心正确，不需要改取。否则说明所有儿子的最优状态都是 $2$ 状态，将这个最小改取费用加上即可。

$$f[i][1]=(\sum_{i->j}\min(f[j][0],f[j][1]))+\max(0,\min(f[j][0]-f[j][1]))$$

#### 3. 自己不建，儿子也不建：

- 因为自己不建，还要求儿子不能建，所以儿子要有信号来源必须要向它自己的儿子要，所以此状态只能从儿子的 $2$ 状态转移而来。

$$f[i][2]=\sum_{i->j}f[j][1]$$

#### 边界条件 -> 对于叶子节点：

$f[i][0]=1,f[i][1]=INF,f[i][2]=0$ 。 ~~（显然）~~

**最后，根节点没有父亲，它不能吃父亲的本，就只能自己建或者靠儿子的信号度日。**

终上所述，我们就可以很容易的写出非常简短的代码。

### 代码实现：

```cpp
#include <bits/stdc++.h>
#define N 10005
using namespace std;

int n, f[N][3];
int head[N], to[N << 1], nxt[N << 1], cnt = 1;

void addedge(int u, int v) {
	to[cnt] = v;
	nxt[cnt] = head[u];
	head[u] = cnt++;
}

void dfs(int p, int fa) {
	f[p][0] = 1;//自己建有一份初始花费
	int minn = n + 1;//极大值（对于状态而言已经最大了）
	for(int i = head[p];i;i = nxt[i]) {
		int v = to[i];
		if(v == fa) continue;
		dfs(v, p);
		f[p][0] += min(min(f[v][0], f[v][1]), f[v][2]);
		f[p][1] += min(f[v][0], f[v][1]);
		f[p][2] += f[v][1];
		if(f[v][0] - f[v][1] < minn) minn = f[v][0] - f[v][1];
	}
	if(minn > 0) f[p][1] += minn;
}

int main() {
	scanf("%d", &n);
	int a, b;
	for(int i = 1;i < n;i++) {
		scanf("%d%d", &a, &b);
		addedge(a, b);
		addedge(b, a);
	}
	dfs(1, -1);//1没有父亲，随便设不存在的点
	printf("%d", min(f[1][0], f[1][1]));//保证1有信号
	return 0;
}
```

### 后记：

很有意思的树上DP，一定要好好理解，与此类似的题可见讨论区，去多刷几道 ~~n倍经验~~ 的题吧。

---

## 作者：Ofnoname (赞：2)

这道题要求的是每个点周围有至少一个染色点，那么一条边的两端是有可能都没有染色的，一个节点被至少一个儿子染色就合法，此时自底向上的贪心可能更加简单易懂。

考虑一个叶节点，它还没有被染色，可以染它或者染他的父亲，显然染它的父亲可以覆盖更多的点。那么我们把所有点按照深度倒序排序，完全自底向上计算，当考虑到点`x`时，它的儿子已经处理过，不用再管，那么只要`x`还需要染色，我们染它的父节点一定更优。

建立数组`f[]`，`f`值为2表示设立了染色点，为`1`表示不是染色点但是受到了染色影响，当`x`未染色时，将父节点标记为2，自己和父节点的父节点标记为1即可。因为父节点的其他子节点还没有标记，所以判断一个点是否被影响还要看他的父亲。

![](https://s2.ax1x.com/2019/10/26/K0ICVg.png)

因为要排序，复杂度$O(NlogN)$，如果追求严格$O(N)$可以写桶排。

```cpp
#include <bits/stdc++.h>
#define MAX (10000 + 7)
using namespace std;

int N, ec, ans, f[MAX], fa[MAX], id[MAX], dep[MAX], head[MAX];

struct Edge{ int y, nxt; } E[MAX << 1];
void add(int x, int y)
{
	E[++ec] = Edge{y, head[x]};
	head[x] = ec;
}

#define y E[p].y
void DFS(int x)//计算dep和fa 
{
	id[x] = x;
	for (int p = head[x]; p; p = E[p].nxt)
		if (y != fa[x])
		{
			dep[y] = dep[x] + 1;
			fa[y] = x, DFS(y);
		}
}
#undef y

int main()
{
	scanf("%d", &N);
	for (int i = 1, x, y; i < N; i++)
	{
		scanf("%d%d", &x, &y);
		add(x, y), add(y, x);
	}
	DFS(1);
	sort(id+1, id+N+1, [](int a, int b){return dep[a] > dep[b];});//确定点的访问顺序 
	for (int i = 1; i <= N; i++)
	{
		int x = id[i];
		if (!f[x] && f[fa[x]]!=2)//自身无标记，父节点又不是染色点 
		{
			f[fa[x]] = 2;
			f[x] = f[fa[fa[x]]] = 1;
			ans++;
		}
	} printf("%d\n", ans);
}
```

---

## 作者：xy_xw_for_2024 (赞：2)

其实这道题跟我的上一篇的三道题都挺像的

尤其是树的最大独立集

但这道题还是有本质上的差别

那三道题都是要尽量多

而这道题要尽量少

所以区别还是很大的

而且这道题的dp的定义以及状态转移方程都与那三题大不一样

首先，我们定义三种不同状态的 dp ：：

- dp [ i ] [ 0 ] ：：i 节点的子树和 i 节点被全覆盖，i 节点上有塔
- dp [ i ] [ 1 ] ：：i 节点的子树和 i 节点被全覆盖，i 节点无塔
- dp [ i ] [ 2 ] ：：i 节点的子树被全覆盖，但 i 节点未被覆盖  

对于这三种状态，我们分别可以得到以下三种状态转移方程：：

 
dp [ i ] [ 0 ] + = min ( dp [ son ] [ 0 ] , min ( dp [ son ] [ 1 ] , dp [ son ] [ 2 ] ) ) + 1  
第一种情况，他的儿子节点的每一种状态都可以转移上来，再加上他本身再架设一个

dp [ i ] [ 1 ] = min ( dp [ i ][ 1 ] , dp [ son ] [ 0 ] + sum - min ( dp [ son ] [ 0 ] , dp [ son ] [ 1 ] ) )  
这个是最复杂的一种了。因为如果按定义来看，他至少有一个子节点是有塔的，所以。。。自己画图理解一下  
P.S. sum表示覆盖子树的最小值

dp [ i ] [ 2 ] + = dp [ son ] [ 1 ]  
第三种状态只能由第二个状态转移过来

 

还有就是这也是一棵无根树，需要自己定义根

~~（其实这个好像没有什么用，也不需要任何处理，随便从哪个节点开始都没问题）~~

所以我们可以随便从一个节点开始，然后dfs就行了

代码：：
```cpp
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
using namespace std;
inline void read(int &x) {
    x=0;
    int f=1;
    char s=getchar();
    while(s<'0'||s>'9') {
        if(s=='-')
            f=-1;
        s=getchar();
    }
    while(s>='0'&&s<='9') {
        x=x*10+s-48;
        s=getchar();
    }
    x*=f;
}
inline void pr(int x) {
    if(x<0) {
        putchar('-');
        x=-x;
    }
    if(x>9)
        pr(x/10);
    putchar(x%10+48);
}//快读快输不解释
vector<int>G[10005];
int n,k,a,b,dp[10005][3];
void dfs(int x,int fa) {
    dp[x][0]=1;//本身
    dp[x][1]=1000000;//这里不要开得过大，不然一不小心就爆int然后变成负数接而就炸了
    int sum=0;//按上面说的累和
    int o=G[x].size();
    for(int i=0;i<o;i++) {
        int v=G[x][i];
        if(v==fa)//父节点
            continue;
        dfs(v,x);//从叶子节点开始逆推上来
        dp[x][2]+=dp[v][1];//按上面说的状态转移方程推过来
        dp[x][0]+=min(dp[v][0],min(dp[v][1],dp[v][2]));//同上
        sum=sum+min(dp[v][0],dp[v][1]);//同上
    }
    if(o==1&&x!=1)//只有一个儿子&&非根节点
        return;
    for(int i=0;i<o;i++) {
        int v=G[x][i];
        if(v==fa)
            continue;
        dp[x][1]=min(dp[x][1],dp[v][0]+sum-min(dp[v][0],dp[v][1]));//同上上
    }
}
int main() {
    read(n);
    for(int i=1;i<n;i++)
        read(a),read(b),G[a].push_back(b),G[b].push_back(a);
    dfs(1,0);
    pr(min(dp[1][0],dp[1][1]));//读入+dfs+输出
}
```

大概就是这样，不懂的可以评论讨论

---

## 作者：何卓然 (赞：2)

本题是一道很经典的 tree-dp 题目，我这里提供一种另外的角度解决这个问题。


我们发现一个节点如果被选择，那么它和它相邻的节点就能满足覆盖，我们要求所有节点都被覆盖。

这道题要求我们从树上取尽量少的点组成一个集合，使得对于树上剩余的点都与取出来的点有边相连。也就是说，设V‘是树的一个支配集，则对于树上中的任意一个顶点u，要么属于集合V’，要么与V‘中的顶点相邻。在V’中出去任何元素后V‘不再是支配集，则这个支配集是最小支配集。

本题求的就是一棵树上的最小支配集的大小。


对于树上的最小支配集问题，贪心策略是首先选择一点为根，按照深度优先遍历得到遍历序列，按照所得序列的反向序列的顺序进行贪心，**对于一个既不属于支配集也不与支配集中的点相连的点来说，如果他的父节点不属于支配集，将其父节点加入支配集。**

请注意这里的贪心的策略中贪心的顺序非常重要，**按照深度优先遍历得到遍历序列的反向进行贪心，可以保证对于每个点来说，当其子树都被处理过后才轮到该节点的处理，保证了贪心的正确性。**


这样处理，得到的时间复杂度是 O(n) 的。




**Code**






    




    

```cpp
#include <bits/stdc++.h>
using namespace std;
#define REP(i, a, b) for (int i = (a), i##_end = (b); i < i##_end; ++i)
typedef long long LL;
vector< vector<int> > edges(10005);
int n,fm,to,cnt = 0;
int a[10005],deep[10005],father[10005];
bool vis[10005];
void dfs(int cur,int d)
{
    vis[cur] = true;
    deep[cur] = d;
    a[++cnt] = cur;
    REP(i,0,edges[cur].size())
    {
        if (!vis[edges[cur][i]])
        {
            father[edges[cur][i]] = cur;
            dfs(edges[cur][i],d+1);
        }
    }
}
int greedy()
{
    bool s[10005]; // 某一点是否被覆盖 
    bool set[10005]; // 是否假如支配集    
    int ans = 0;
    for(int i=n;i>0;i--)
    {
        int t = a[i];
        if(!s[t])
        {
            if(!set[father[t]])
            {
                set[father[t]]=true;
                ans++;
            }
            s[t]=true;
            s[father[t]]=true;
            s[father[father[t]]]=true;
        }
    }
    return ans;
}
int main()
{
    scanf("%d",&n);
    REP(i,1,n) 
    {
        scanf("%d%d",&fm,&to);
        edges[fm].push_back(to);
        edges[to].push_back(fm);
    }
    dfs(1,0);
    printf("%d",greedy());
    return 0;
}

```

---

## 作者：林志杰 (赞：2)

贪心，每次保证深度最深的点可达。

不过数据范围有坑，开始开1e4爆掉了，调试了一个小时！！！！！！！！








```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<utility>
#include<functional>
#include<queue>
using namespace std;
typedef pair<int,int> Pair;
const int maxn = 1e5 + 15;
struct edge{
    int nxt,to;
}e[maxn];
int n,first[maxn],cnt,fa[maxn],dep[maxn],ans=0;
bool vis[maxn];
priority_queue < Pair,vector<Pair>,less<Pair> > q;
inline void addedge(int u,int v)
{
    e[++cnt] = (edge) {first[u],v};
    first[u] = cnt;
}
void dfs(int x,int f,int deep)
{
    fa[x] = f;
    dep[x] = deep;
    for(int i=first[x],v;i;i=e[i].nxt) {
        v = e[i].to;
        if(v == f) continue;
        else dfs(v,x,deep+1);
    }
}
void bfs(int x)
{
    vis[x] = true;
    for(int i=first[x],v;i;i=e[i].nxt) {
        v = e[i].to;
        vis[v] = true;
    }
    ans++;
}
int main()
{
    cin>>n;
    for(int i=1,x,y;i<n;i++) {
        scanf("%d%d",&x,&y);
        addedge(x,y);addedge(y,x);
    }
    dfs(1,1,1);//建造一棵树
    for(int i=1;i<=n;i++) q.push(make_pair(dep[i],i));//优先队列维护深度
    while(!q.empty()) {
        int v = q.top().second;//每次选深度最大的
        q.pop();
        if(vis[v]) continue;
        bfs(fa[v]);//在父节点处安置信号塔
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：yzbsy (赞：1)

今天刷在列表里刷拓扑排序的题目
好不容易找到一个题
结果本蒟蒻翻题解的时候竟然没发现一个用拓扑排序的题目
既然这样我就写一篇用拓扑排序的题解吧
其实大致思路和楼上一样就是我用拓扑排序替代了dfs（~~或许能快一点~~）
算法本质都是树形dp
这里讲一讲拓扑排序在这里的应用，拓扑排序就是进行一个排序，排序选择后加入队列（和bfs有点相似）不过这里的排序后各个节点的更新都不受影响（意思是说这里节点更新所需要之前的节点都已经被更新了）
下面就是激动人心的环节辽，上代码
（里面还是加入了必要的注释）
```
#include<cstdio>
#include<iostream>
using namespace std;
#define maxn 100010
#define INF 0x3f3f3f3f

int e[maxn],ne[maxn],h[maxn],f[maxn][3],q[maxn],idx=1,indeg[maxn],outdeg[maxn],vis[maxn];

void add(int a,int b){
    e[idx]=b;ne[idx]=h[a];h[a]=idx++;
    e[idx]=a;ne[idx]=h[b];h[b]=idx++;
    return;
}

/*
f[u][0]+=min(f[v][0/1/2]) 子树和u均有信号 且在u建信号站 
f[u][1]=f[son][0]+Σf[other_son][0/1]; 子树和u均有信号 
f[u][2]+=min(f[v][0/1]) 子树有信号u无信号 
*/

void topsort(int n){
    int u,tail=0,head=0,updt;
    for(int i=1;i<=n;i++){
        if(indeg[i]<=1){
            q[tail++]=i;
            f[i][1]=1;
            vis[i]++;
        }
    }
    while(head<tail){
        updt=INF;
        u=q[head++];
        f[u][0]=1;
        vis[u]++;//vis[]=0/1/2 分别表示未被更新过/在队列中未被更新/被更新过
        for(int i=h[u],v=e[h[u]];i!=0;i=ne[i],v=e[i]){
            if(v==u||vis[v]==1)//未完成更新
                continue;
            indeg[v]--;
            if(vis[v]==0){//未入队 
                if(indeg[v]<=1){
                    q[tail++]=v;
                    vis[v]++;
                }
                continue;
            }
            f[u][0]+=min(f[v][0],min(f[v][1],f[v][2]));
            f[u][1]+=min(f[v][0],f[v][1]);
            f[u][2]+=min(f[v][0],f[v][1]); 
            if(updt>f[v][0]-min(f[v][0],f[v][1])){
                updt=f[v][0]-min(f[v][0],f[v][1]);
            }
        }
        if(updt!=INF){
            f[u][1]=f[u][1]+updt;
        }
    }
    printf("%d",min(f[u][0],f[u][1]));
    //根节点就是队列的最后一个节点
    return;
}

int main(){
    int n,a,b;
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        scanf("%d %d",&a,&b);
        add(a,b);
        indeg[a]++;
        indeg[b]++;
        outdeg[a]++;
        outdeg[b]++;
    }
    topsort(n);
    return 0;
}
```


---

## 作者：brealid (赞：1)

## 题目类型分析 & 同类题目

### 类型分析

这种题目的特点：一棵树上选一些尽量少的点打标记，使得每个点与最近的打了标记的点的距离不超过 $distance\_limit$ (本题为 $1$)

### similar problem

这种题目有很多种变式，下面给出几个：

1. 比这道题难一点的（$distance\_limit$ 为 $2$） [P2279 [HNOI2003]消防局的设立](https://www.luogu.org/problem/P2279) (蓝题)   
2. 这道题的同类题目模板 [P3942 将军令](https://www.luogu.org/problem/P3942) (蓝题)  
3. 超级升级版 [P3267 [JLOI2016/SHOI2016]侦察守卫](https://www.luogu.org/problem/P3267) (紫题)  

其中，这道题与上面的第 1, 2 题都可以用贪心解决，第 3 题则是恶心无敌大DP

### 这种类型的题目能够贪心解决的标志

在每个点上打标记的代价相同（都为 $1$）且所有点都需要满足 “每个点与最近的打了标记的点的距离不超过 $distance\_limit$”

那么我们讨论一下这题的贪心

## solution

考虑按 $depth$ 从深到浅遍历。

对于每个点，由遍历顺序可知其子树都已经遍历过。

所以如果他的儿子（不包括孙子及以下）没有一个是建了信号塔的，那这个点只能在其自己处或父亲处建塔。

考虑因为其后代都已经有信号了，所以建在自己处（只能服务自己与父亲）不如建在父亲处（能服务自己，父亲，兄弟以及爷爷）优

所以可以贪心了

## 拓展延伸

对于这一类题目的通用解法：

1. 建树；  
2. 初始化 $depth$；  
3. 把节点按深度从深到浅遍历；  
   如果他的后代没有一个打标记的点与他的距离不超过 $distance\_limit$，就在其祖宗（与其隔了 $distance\_limit$ 代）处打标记。
   
## 代码说明

1. dfs() 函数 : 初始化家谱信息（$fa$ 数组）与 $depth$ 数组  
2. type 数组 : 请结合代码中第 69 ~ 71 行一起看
   ```cpp
   #define HAS_SignalTower 2  // 这个节点有信号塔
   #define NEAR_SignalTower 1 // 这个节点挨着信号塔
   #define NO_SignalTower 0   // 这个节点没有也不挨着信号塔（无信号）
   ```

## code
```cpp
/*************************************
 * problem:      P2899 [USACO08JAN]手机网络Cell Phone Network.
 * user ID:      63720.
 * user name:    Jomoo.
 * time:         2019-08-19.
 * language:     C++.
 * upload place: Luogu.
*************************************/ 

#include <bits/stdc++.h>
using namespace std;
#define puts_return(x) { puts(x); return 0; }
#define write_return(x) { write(x); return 0; }

typedef signed char          int8;
typedef unsigned char       uint8;
typedef short                int16;
typedef unsigned short      uint16;
typedef int                  int32;
typedef unsigned            uint32;
typedef long long            int64;
typedef unsigned long long  uint64;

template <typename Int>
inline Int read()       
{
    Int flag = 1;
    char c = getchar();
    while ((!isdigit(c)) && c != '-') c = getchar();
    if (c == '-') flag = -1, c = getchar();
    Int init = c & 15;
    while (isdigit(c = getchar())) init = (init << 3) + (init << 1) + (c & 15);
	return init * flag;
}

template <typename Int>
inline void write(Int x)
{
    if (x < 0) putchar('-'), x = ~x + 1;
    if (x > 9) write(x / 10);
    putchar((x % 10) | 48);
}  

template <typename Int>
inline void write(Int x, char nextch)
{
    write(x);
    putchar(nextch);
}

int n, a[10007], fa[10007], depth[10007], type[10007];
int ans = 0;
vector<int> G[10007];

bool cmp(int x, int y) 
{
    return depth[x] > depth[y];
}

void dfs(int p, int f)
{
    fa[p] = f;
    depth[p] = depth[f] + 1;
    for (int nxt : G[p]) {
        if (nxt != f) dfs(nxt, p);
    }
}

#define HAS_SignalTower 2
#define NEAR_SignalTower 1
#define NO_SignalTower 0

int main()
{
    scanf("%d", &n);
    memset(type, NO_SignalTower, sizeof(type));
    int u, v;
    for (int i = 1; i <= n; i++) {
        a[i] = i;
    }
    for (int i = 2; i <= n; i++) {
        u = read<int>();
        v = read<int>();
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1, 0);
    sort(a + 1, a + n + 1, cmp);
    for (int i = 1; i <= n; i++) {
        if ((type[fa[a[i]]] != HAS_SignalTower) && (type[a[i]] == NO_SignalTower)) {
            ans++;
            // printf("build in %d.\n", fa[a[i]]);
            type[a[i]] = NEAR_SignalTower;
            type[fa[a[i]]] = HAS_SignalTower;
            type[fa[fa[a[i]]]] = NEAR_SignalTower;
        }
    }
    write(ans);
    return 0;
}
```

---

## 作者：crashed (赞：0)

前附：  
1.$near( i )$：与$i$相邻的节点的集合，不包括节点  
2.$son( i )$：$i$的子节点集合  
3.$fa( i )$：$i$的父亲节点编号   

# 分析:

看到这道题，我第一个想到的就是——  
舞会模型！  
这确实是最容易想到的，并且这也会为我们的转移带来一些启发。  
然而，如果我们真的用舞会模型去做的话，那么我们会惊奇地发现——不知道当前点该归属于哪个电话基站，所以无法求解！   
其实这个问题很好解决，我们将归属的这个信息记入状态之中，所以就有了  ：
## 定义状态：
$DP( i, j )$：第$i$号节点归属于$j$号节点上的基站的情况下能使得以$i$为根的子树上的所有节点都可以收到信号需要的最少基站数量( $j\in son(i)$ )  
$best( i )$：第$i$号节点归属于自己的儿子节点上的基站或者自己的基站的情况下能使得以$i$为根的子树上的所有节点都可以收到信号需要的最少基站数量  
## 转移：
转移其实也比较好写：  
1.$ DP( i, i ) = 1 + \{\sum_{v \in son(i)}min(best(v), DP(v, i)-1)\} $   
这个类似于舞会模型的转移。  
2.$ DP( i, fa( i ) ) = 1 + \{\sum_{v\in son(i)} best(v)\} $   
这个情况默认i节点不放基站，所以它的子节点们都只能“各家自扫门前雪”，自己就在自己的子树内解决问题了。  
3.$ DP( i, j ) = DP( j, j ) + \{\sum_{v\in (son(i)\backslash j)} best(v)\} $   
这个情况也是默认i节点不放基站。此时由于i依托在j上，所以j一定要放基站；其它的节点不能靠i上的基站，所以是用自己的best来解决。  
4.best的转移：  
$best( i ) = min\{ DP(i, j) | j\in son(i) \bigcup j=i \}$  

# 优化：
    
如果强行求解，那么这样的时间是$O( n^2 )$。  
不过我们可以看出一些联系——  
我们可以从$DP( i, fa( i ) )$转移到$DP( i, j )$( $j∈son( i )$ )，只需要减去$( best( j ) + 1 )$再加上$DP( j, j )$就可以了。  
所以，我们最后得到的时间是$O( n )$；空间则只需要$O( n )$（实际上只需要记录$DP( i, i )$，$DP( i, fa( i ) )$和$best( i )$） 
# 代码：
```cpp
#include <cstdio>
#include <map>
using namespace std;
 
const int MAXN = 10005;
 
template<typename _T>
void read( _T &x )
{
    x = 0;char s = getchar();int f = 1;
    while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
    while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
    x *= f;
}
 
template<typename _T>
void write( _T x )
{
    if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
    if( 9 < x ){ write( x / 10 ); }
    putchar( x % 10 + '0' );
}
 
template<typename _T>
_T MIN( const _T a, const _T b )
{
    return a < b ? a : b;
}
 
struct edge
{
    int to, nxt;
}Graph[MAXN * 2];
 
int DP[MAXN][2] = {}, best[MAXN];
//简化之后的DP，0表示靠自己，1表示靠父亲节点 
int head[MAXN] = {};
int n, cnt = 0;
 
void addEdge( const int from, const int To )
{
    cnt ++;
    Graph[cnt].to = To;
    Graph[cnt].nxt = head[from];
    head[from] = cnt;
}
 
void dfs( const int now, const int fa )
{
    int v;
    DP[now][0] = 1;
    DP[now][1] = 1;
    //两种情况都至少需要一个基站来让自己接受信号 
    for( int i = head[now] ; i ; i = Graph[i].nxt )
    {
        v = Graph[i].to;
        if( v ^ fa )
        {
            dfs( v, now );
            DP[now][1] += best[v];
            DP[now][0] += MIN( best[v], DP[v][1] - 1 );
            //转移 
        }
    }
    best[now] = DP[now][0];
    //将在自己上面建基站的状态作为初始状态 
    for( int i = head[now] ; i ; i = Graph[i].nxt )
    {
        v = Graph[i].to;
        if( v ^ fa )
        {
            best[now] = MIN( best[now], DP[now][1] - best[v] - 1 + DP[v][0] );
            //省去计算DP( i, j )的情况，直接用DP( i, fa( i ) )中得到的结果来转移 
        }
    }
}
 
int main()
{
    int u, v;
    read( n );
    for( int i = 1 ; i < n ; i ++ )
    {
        read( u ), read( v );
        addEdge( u, v );
        addEdge( v, u );
    }
    dfs( 1, 0 );
    write( best[1] ), putchar( '\n' );
    //根上的最优解就是整体最优解；1的父亲是虚建的节点，所以不能用DP( 1, fa( 1 ) )的状态 
    return 0;
}
```

---

## 作者：温词 (赞：0)

#### 唉又是一道n倍经验题，与消防局的设立那题有异曲同工之妙，~~就特么一样好不好~~
##### 读完题后稍微思考一下就知道，在一个还未被覆盖到的地方，选择自己肯定不如选择父节点优啊，源于这一点，我们可以直接贪心过这题。
#### 然后一个小细节，在处理结点深度时可以用一个大根堆，也可以像我写的这样
## 还是看代码吧！！！
```
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int w=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		w=(w<<3)+(w<<1)+ch-48;
		ch=getchar();
	}
	return w*f;
} //不要问我为什么我的快读写这b样
queue<int> q;
stack<int> s;
int n,head[100010],cnt,fa[100010],ans;
bool vis[100010];
struct Edge{
	int from,to,next,dis;
}edge[100010];
inline void addedge(int u,int v){
	cnt++;
	edge[cnt].dis=1;
	edge[cnt].from=u;
	edge[cnt].to=v;
	edge[cnt].next=head[u];
	head[u]=cnt;
}//到这都是常规操作，坐好准备起飞吧！！！
inline void bfs(){
	int u,v,i,j,k;
	s.push(1);
	q.push(1);//仔细思考一下，bfs的进队顺序就是按照深度来的，那么我开一个栈存一下，弹出的时候就是深度从大到小排序的了.
	while(!q.empty()){
		u=q.front();
		q.pop();
		for(i=head[u];i;i=edge[i].next){
			v=edge[i].to;
			if(fa[u]==v) continue;
			s.push(v);
			q.push(v);
			fa[v]=u;
		}
	}
}
inline void affect(int u){
	int i,j,k,v;
	vis[u]=true;
	for(i=head[u];i;i=edge[i].next){
		v=edge[i].to;
		vis[v]=true;
	}//这个是标记一个点可以影响的点的情况
	return;
}
inline void dfs(){
	int u,v,i,j,k;
	while(!s.empty()){
		u=s.top();
		s.pop();
		if(vis[u]) continue;
		ans++;
		affect(fa[u]);//注意：此处要在父节点安装覆盖，可以手推一下正确性。
	}
}
int main(){
	int i,j,k;
	n=read();
	for(i=1;i<n;i++){
		int x,y;
		x=read();
		y=read();
		addedge(x,y);
		addedge(y,x);
	}
	bfs();
	dfs();
	//while(!s.empty()){
	//	int now=s.top();
	//	s.pop();
	//	cout<<now<<endl;
	//}//debug好帮手
	printf("%d\n",ans);
	return 0;
}
```
#### 大概就是这样了，希望大家能顺利a掉这题

---

## 作者：ELLIAS (赞：0)

# 贪心
	本题是一道很基本的题.
    题干:
    Farmer John has decided to give each of his cows a cell phone in hopes to encourage their social interaction. This, however, requires him to set up cell phone towers on his N (1 ≤ N ≤ 10,000) pastures (conveniently numbered 1..N) so they can all communicate.
	Exactly N-1 pairs of pastures are adjacent, and for any two pastures A and B (1 ≤ A ≤ N; 1 ≤ B ≤ N; A ≠ B) there is a sequence of adjacent pastures such that A is the first pasture in the sequence and B is the last. Farmer John can only place cell phone towers in the pastures, and each tower has enough range to provide service to the pasture it is on and all pastures adjacent to the pasture with the cell tower.
	Help him determine the minimum number of towers he must install to provide cell phone service to each pasture.

	本题要求使用最少的电磁塔,把所有的节点覆盖掉.由N-1条边我们可以了解到,这是一棵树.从树的叶子节点向上看,显然在儿子节点摆电磁塔是不合算的.所以很显然地,从最后一层向上搜索,每遇到一个儿子节点没有被覆盖,就在他父亲上摆一个电磁塔.很显然,从下向上枚举,对于本题的数据这种方法是成立的.
    代码:
```cpp
#pragma GCC optimize ("Ofast")

#include "iostream"
#include "stdio.h"
#include "vector"

#define rint register int

using namespace std;

inline int read()
{
    int x=0ll,t=1ll;
    char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')t=-1,ch=getchar();
    while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
    return x*t;
}

bool check[10001];
int n, fa[10001], ans, mxdp;
vector <int> mp[10001], fl[10001];

inline void dfs (int u, int de)
{
	mxdp = max (mxdp, de);
	fl[de].push_back (u);
	int v;
	for (rint i = 0; i < mp[u].size (); i ++)
	{
		v = mp[u][i];
		if (v == fa[u]) continue;
		fa[v] = u;
		dfs (v, de + 1);
	}
}

inline void work (int u)
{
	check[u] = true;
	for (rint i = 0; i < mp[u].size (); i ++) check[mp[u][i]] = true;
}

int main ()
{
	n = read ();
	int u, v;
	for (rint i = 1; i < n; i ++)
	{
		u = read (), v = read ();
		mp[u].push_back (v);
		mp[v].push_back (u);
	}
	
	dfs (1, 0);
	
	for (rint i = mxdp; i >= 0; i --)
	{
		for (rint j = 0; j < fl[i].size (); j ++)
		{
			u = fl[i][j], v = fa[u];
			if (check[u]) continue;
			ans ++;
			work (v);
		}
	}
	printf ("%d", ans);
}
```

---

## 作者：kakakaka (赞：0)

详见本人博客<http://www.cnblogs.com/huangdalaofighting/p/6917309.html

很经典的树形dp，状态为f[i][3]分别表示此节点不选且不能被覆盖，此节点选，此节点不选但能被覆盖三种情况，然后动规方程就很显然了。不过多概述，以下是AC代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;
int n,m;
int f[10001][3];
struct student
{
    int next,to;
}edge[30001];
int head[10001],size;
void putin(int from,int to)
{
    size++;
    edge[size].next=head[from];
    edge[size].to=to;
    head[from]=size;
}
void dfs(int k,int father)
{
    int f0=2000000000,f2=0,f1=0,w=0,i,s=0;
    for(i=head[k];i!=-1;i=edge[i].next)
    {
        int y=edge[i].to;
        if(y==father)continue;
        dfs(y,k);
        s=min(f[y][1],f[y][0]);
        w+=s;
        if(f[y][1]-s<f0)f0=f[y][1]-s;
        f1+=min(f[y][1],min(f[y][0],f[y][2]));
        if(f2<2000000000)f2+=f[y][0];
    }
    f[k][1]=f1+1;f[k][2]=f2;
    if(f0==2000000000)f[k][0]=2000000000;
    else f[k][0]=w+f0;
}
int main()
{
    int i,j,from,to;
    cin>>n;
    for(i=1;i<=n;i++)head[i]=-1;
    for(i=1;i<n;i++)
    {
        scanf("%d%d",&from,&to);
        putin(from,to);
        putin(to,from);
    }
    dfs(1,0);
    cout<<min(f[1][0],f[1][1]);
    return 0;
}
```

---

