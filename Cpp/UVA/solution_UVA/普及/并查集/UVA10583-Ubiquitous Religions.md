# Ubiquitous Religions

## 题目描述

### 题目简述

有一个 $n$ 个点，$m$ 条边的无向图，求这个图有多少个连通块。

## 说明/提示

$0<n\le 5\times 10^4$，$0\le m\le \frac{n\times (n-1)}{2}$。

## 样例 #1

### 输入

```
10 9
1 2
1 3
1 4
1 5
1 6
1 7
1 8
1 9
1 10
10 4
2 3
4 5
4 8
5 8
0 0```

### 输出

```
Case 1: 1
Case 2: 7```

# 题解

## 作者：onepeople666 (赞：10)

由题面中有 $n$ 个点，$m$ 条边和描述从 $x$ 到 $y$ 的无向边可以看出这题是典型的[并查集](https://www.luogu.com.cn/problem/P3367)题目。

- **如何计算连通块的个数**

在一般情况下，可以认为原本有 $n$ 个连通块，如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/xupu2weo.png)

然后，是合并一次后连通块的示意图：

![](https://cdn.luogu.com.cn/upload/image_hosting/x7856ijs.png)

我们发现，①和②两个连通块合并成了新的连通块①，然后连通块的总数减少了一个。于是我们可以得出，在一般情况下，连通块每合并一次，总数就会减少一个，于是我们就可以得出一般情况下时，连通块的个数是点的个数减去边的条数，也就是 $n-m$。

- **特殊情况**

但是如果那么简单，这道题就不是一道绿题了，肯定会有特殊情况发生。如果题目中两个点本身就处在一个连通块内，再在他们之间连上一条无向边，连通块的个数是不会减少的，像这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/e4lurv2p.png)

此时点①和点②之间有一条无向边，②和③之间也有一条边，①、②和③此时已经处于同一连通块内，再在①和③之间连一条边，连通块个数并不会减少。

那要怎样判断两个点是否在同一连通块内呢？这时候我们就需要并查集算法（还不会的自己找资料）。在题目每给出一条边时，我们就用并查集判断其是否在同一集合内，如果是，$n$ 不减，如果不是，合并两个点 $x$ 和 $y$ 所在的集合，并将 $n$ 减一，最后的 $n$ 就是我们要的答案。

---

## 作者：Nt_Tsumiki (赞：2)

## 题意

有一个 $n$ 个点，$m$ 条边的无向图，求在图中有多少个连通块。

## 做法

### 题意分析

由无向图可以看出我们可以把这个图构建成一棵树，而由求连通块可以看出，这是一道典型的并查集问题。

### 算法实现

并查集一共需要两个函数，```find``` 和 ```join```，这两个函数起到查找祖先和合并集合的作用，具体写法如下：

```cpp
int find(int x) {
	return (fa[x]==x?x:fa[x]=find(fa[x]));
    // 等效于
    // if (fa[x]==x) return x;
    // else return find(fa[x]);
}
```

```cpp
void join(int x,int y) {
	fa[find(x)]=find(y);
}
```

即可（主函数内容详见代码注释）。

**注意**：本题多组数据，记得清空。

## Code
```cpp
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;
int n,cnt,m;
int fa[500001];

int find(int x) {return (fa[x]==x?x:fa[x]=find(fa[x]));}//查找函数 

void join(int x,int y) {fa[find(x)]=find(y);}//合并函数

int main() {
    while (1) {//有多组数据
		scanf("%d%d", &n, &m);
		if (!n and !m) return 0;
		int ans=n;
        memset(fa,1,sizeof fa);// 清空
    	for (int i=1;i<=n;i++) fa[i]=i;
    	for (int i=1,x,y;i<=m;i++) {//连边
        	cin>>x>>y;
        	if (find(x) != find(y)){//集合不同则合并
				ans --;//如果两个原本不同的集合合并，则相当于，总集合数减 1
				join (x, y);
			}
		}
		cout<<"Case "<<++cnt<<": "<<ans<<endl;//注意输出格式
    }
    return 0;//完美结束
}
```

---

## 作者：_Andy_Lin_ (赞：2)

如果不会并查集，也可以用暴力dfs，一样可以AC。

------------
$Code:$
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,tot,T;
vector<int>ver[50001];
bool vis[50001];
inline void dfs(int x){
	vis[x]=true;
	for(int i=0;i<ver[x].size();i++){
		if(vis[ver[x][i]])continue;
		dfs(ver[x][i]);
	}
}
int main(){
	while(scanf("%d%d",&n,&m)!=EOF&&n!=0&&m!=0){
		tot=0;
		memset(vis,false,sizeof(vis));
		for(int i=1;i<=n;i++)ver[i].clear();
		for(int i=1;i<=m;i++){
			int x,y;
			scanf("%d%d",&x,&y);
			ver[x].push_back(y);
			ver[y].push_back(x);
		}
		for(int i=1;i<=n;i++){
			if(!vis[i]){
				dfs(i);
				tot++;
			}
		}
		printf("Case %d: %d\n",++T,tot);
	}
	return 0;
}
```

---

## 作者：linyinuo2008 (赞：1)

[原题链接](https://www.luogu.com.cn/problem/UVA10583)

AC 20道绿题祭

这是一道并查集模板题，就是无向图求连通块数，我们来看一下是如何实现的。

# 1、题意理解

给你一些数，然后告诉你有些数是属于一个集合的，然后问你最多有几个集合。

显然，要达到最大值的目的，我们就需要初始假设每一个数都是一个单独的集合，然后当它告诉我们哪两个数是属于一个集合时，我们再~~不情愿地~~把它们合并。

貌似也没有什么要点，我们就来简单说一下怎么用并查集实现。
# 2、算法实现
[这里](https://blog.csdn.net/weixin_43886592/article/details/107561330)有一个并查集的简单介绍。

我们开一个$father$数组记录每个元素的父亲

思路是这样的：当我们想把两个数合并时，我们不仅合并这两个数，我们还要合并这两个数的所有子节点。方法就是让其中的一个数成为另一个数的父节点，同时进行路径压缩。

路径压缩就是在查找一个数的最远祖先时，我们同时直接把这位最远祖先变成它的直接父亲。

代码实现：
```cpp
int getfa(int k)
{
	if(father[k]==k)//如果父节点是它自己
		return k;//返回
	return father[k]=getfa(father[k]);//路径压缩
}
```
然后当我们想把元素$a$与$b$所在集合合并时，我们仅需让$father_a=b$即可。代码如下：
```cpp
void merge(int a,int b)
{
	a=getfa(a);
	b=getfa(b);
	father[a]=b;
}
```
最后当查询有几个连通块时，仅需找有几个独立的集合就可以了，后者可以用父节点来判断，当$father_i=i$时，$ans$加一。
# 3、代码
代码奉上（有注释）：
```cpp
#include <iostream>
using namespace std;
const int N=5e4+5;
int fa[N],n,m,ans;
int p,q;
int getfa(int k)
{
	if(fa[k]==k)//如果父节点是它自己
		return k;//返回
	return fa[k]=getfa(fa[k]);//路径压缩
}
void merge(int a,int b)//合并
{
	a=getfa(a);
	b=getfa(b);
	fa[a]=b;//将a的父亲设为b
}
void Init()//初始化
{
	ans=0;
	for(int i=1;i<=n;i++)
	{
		fa[i]=i;//每个元素为一个独立集合
	}
}
int main()
{
	int cnt=0;
	while(cin>>n>>m&&n&&m)
	{
		cnt++;//计数器到第几组数据了
		Init();
		for(int i=1;i<=m;i++)
		{
			cin>>p>>q;
			merge(p,q);
		}
		for(int i=1;i<=n;i++)//找有几个父节点
		{
			if(fa[i]==i)
			{
				ans++;
			}
		}
		cout<<"Case "<<cnt<<": "<<ans<<endl;
	}
	return 0;
} 
```
撰写不易，求通过！

**若有错误，欢迎指出！**

---

## 作者：Phoenix_chaser (赞：1)

## 本题基本上是并查集模板题

#### 并查集：
并查集，在一些有N个元素的集合应用问题中，我们通常是在开始时让每个元素构成一个单元素的集合，然后按一定顺序将属于同一组的元素所在的集合合并，其间要反复查找一个元素在哪个集合中。

实现方法：

```cpp
int fd(int x){
	if(fa[x]==x) return x;
	return fa[x]=fd(fa[x]);
} 
```
#### 这边用 fa[x]=fd(fa[x])减少时间复杂度

类似于记搜的思想

 跟模板基本上 _**只差一个查找连通块的步骤**_ 
 
 ```cpp
	for(int i=1;i<=n;i++)
	if(fa[i]==i)
	ans++;
```

还有一步就是处理输入

```cpp
while(scanf("%d%d",&n,&m)&&(n!=0||m!=0))
```
AC代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int fa[100004],n,a,ans=0,m,x,y,e=0;
int fd(int x){
	if(fa[x]==x) return x;
	return fa[x]=fd(fa[x]);
	//并查集 
} 
int main(){
	while(scanf("%d%d",&n,&m)&&(n!=0||m!=0)){
	ans=0;
	for(int i=1;i<=n;i++)
	fa[i]=i;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y); 
		int x1=fd(x);
		int x2=fd(y);
		fa[x1]=x2;
	}
	for(int i=1;i<=n;i++)
	if(fa[i]==i)
	ans++;
	//找连通块 
	e++;
	printf("Case %d: %d\n",e,ans);
	
}
	return 0;
}

```
刷完此题之后推荐

[P1525](https://www.luogu.com.cn/problem/P1525)

[P3183](https://www.luogu.com.cn/problem/P3183)

(以上皆是分组并查集)

## 谢谢观看

### THE END




---

## 作者：thyzzs (赞：1)

无人做过的题...
走一波题解

```cpp
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
int f[50005],TT,A,B,n,m,i,g[50005],sum;
int getf(int k)
{
	return f[k]==k?f[k]:f[k]=getf(f[k]);
}
void read(int &x)
{
	char c;
	int f=0;
	for (c=getchar(); c<'0' || c>'9'; c=getchar()) if (c=='-') f=1;
	x=c-'0';
	for (c=getchar(); c>='0' && c<='9'; c=getchar()) x=x*10+c-'0';
	if (f) x=-x;
}
int main()
{
	while (1)
	{
		TT++;
		scanf("%d%d",&n,&m);
		if (n==0 && m==0) return 0;
		for (i=1; i<=n; i++) f[i]=i;
		while (m--)
		{
			read(A); read(B);
			f[getf(A)]=getf(B);
		}
		for (i=1; i<=n; i++) g[i]=0;  //g[i] i是否是祖先 
		for (i=1; i<=n; i++) g[getf(i)]=1;  //把每个点的祖先标记为1 
		sum=0;
		for (i=1; i<=n; i++) sum+=g[i];
		printf("Case %d: %d\n",TT,sum);
	}
	return 0;
}
```

---

## 作者：DeepSkyBlue__ (赞：1)

这道题如果不用并查集而是用 BFS 来做的话也比较方便，主要思路就是利用 BFS 把一个点能到的所有点都标记，如果某个点没有被标记说明它属于另外一个连通块，并对它进行 BFS 找到它所在连通块里所有的点。

CODE：

```cpp
#include<bits/stdc++.h>
//#include<tr1/unordered_map> 
using namespace std;
//using namespace std::tr1;
unordered_map<int,vector<int> >adj;
queue<int>q;
bool v[200001];
void bfs(int s)//bfs
{
	q.push(s);//入队
	v[s]=true;//这个点已经被走过了
	while(!q.empty())
	{
		int cur=q.front();
		q.pop();//弹出栈顶元素
		for(int i=0;i<adj[cur].size();i++)
		{
			int next=adj[cur][i];//下一步能走到的点
			if(!v[next])//如果这个点没有被走过
			{
				v[next]=true;//那么就走这个点
				q.push(next);//这个点入队
			}
		}
	}
}
int main()
{
	int n,m;		
	int sum=0;//组数
	while(cin>>n>>m)
	{
		memset(v,0,sizeof(v));
		adj.clear();//多测注意清空
		sum++;
		if(n==0&&m==0)return 0;
		for(int i=1;i<=m;i++) 
		{
			int x,y;
			cin>>x>>y;
			adj[x].push_back(y);
			adj[y].push_back(x);//无向图两次建边
		}
		int ans=0;//ans代表连通块个数
		for(int i=1;i<=n;i++)
		{
			if(!v[i])//这个点没有被走过
			{
				ans++;//多了一个连通块
				bfs(i);//对这个点进行bfs，把这个点能到的所有点都标记
			}
		}
		cout<<"Case "<<sum<<": "<<ans<<endl;//输出连通块个数
	}
	return 0;
}
```


---

## 作者：Coros_Trusds (赞：0)

# 题目大意

给定一个 $n$ 个点，$m$ 条边的无向图，求这个图有多少个连通块。

# 题目分析

用并查集维护连通块是求连通块个数的常用套路。

将每条边的两个端点合并在一起，表示在一个连通块内，最后处理完所有边后查询总共有多少个单独的连通块即可。

----
怎样查询有多少个不同的联通块?

遍历所有节点，如果一个节点的父亲节点是自己，自己就代表了自己所在的连通块，之后就不需要重复计算了。

# 代码

对于每个操作：

```cpp
		ans=0;
		for(register int i=1; i<=n; i++)fa[i] = i;
        
		for(register int i=1; i<=m; i++){
			int x,y;
			cin >> x >> y;
			merge(x,y);
		}
        
     //查找联通块个数
		for(register int i=1;i<=n;i++)
        {
			if(fa[i]==i)ans++;
		}
```

---

## 作者：cyrxdzj (赞：0)

### 一、思路

本题考察并查集。

在每组数据的一开始，先把 $ans$ 设为 $n$，我们可以在每次连边之前，检查一下连边的两个点是不是已经连通。如果不是，$ans$ 减 $1$，并将并查集的这两个点合并。最后输出 $ans$ 即可。

### 二、完整代码

```cpp
#include<cstdio>
using namespace std;
int n,m,case_id;
int ans;
int father[50005];//并查集。
int find_father(int x)//寻找祖先。
{
	if(x==father[x])
	{
		return x;
	}
	return father[x]=find_father(father[x]);
}
int main()
{
	while(true)
	{
		scanf("%d%d",&n,&m);
		if(n==0&&m==0)//退出条件判定。
		{
			break;
		}
		ans=n;//初始化ans。
		case_id++;
		for(int i=1;i<=n;i++)//初始化并查集数组。
		{
			father[i]=i;
		}
		for(int i=1;i<=m;i++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			int u=find_father(x),v=find_father(y);//寻找这两个点的祖先。
			if(u!=v)//祖先不一致，两个点并未连通，则连边。
			{
				ans--;
				father[u]=v;
			}
		}
		printf("Case %d: %d\n",case_id,ans);//输出。
	}
	return 0;//完结撒花！
}

```

### 四、后记

记录：<https://www.luogu.com.cn/record/51480327>。

By [dengzijun](https://www.luogu.com.cn/user/387836)

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

首先，肯定是有 $n$ 个连通块。

那么，每连接两个本来并不相连的点，就可以减少 $1$ 个连通块。

如何判断原来这两个点是否连通呢？用并查集。

### 2 代码

```cpp
#include<cstdio>
using namespace std;
const int max_n=50000;//最大点数
int n,m;//点数与边数
int fa[max_n+2];//并查集
int tot;//连通块总数
int ts=0;//测试点编号
int main(){
	while(true){
		scanf("%d%d",&n,&m);
		if(n==0){
			break;
		}
		++ts;
		for(int i=1;i<=n;++i){//初始化并查集
			fa[i]=i;
		}
		tot=n;//初始化总数
		for(int i=1,x,y,xf,yf;i<=m;++i){//连边
			scanf("%d%d",&x,&y);
			xf=x;
			yf=y;
			while(xf!=fa[xf]){
				xf=fa[xf];
			}
			while(yf!=fa[yf]){
				yf=fa[yf];
			}
			if(xf!=yf){//这不是连通块
				--tot;
				fa[xf]=yf;
			}
		}
		printf("Case %d: %d\n",ts,tot);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/51448121)

By **dengziyue**

---

## 作者：HFAKzzy (赞：0)

### 题目 [UVA10583 Ubiquitous Religions](https://www.luogu.com.cn/problem/UVA10583)

进入正题，这题是并查集模板题。

先来说一下要开的变量${\colon}$
```cpp
int f[1000000],n,m,x,y;

```

$f$ 数组是存祖宗的数组，$n$，$m$，$x$，$y$ 都是工具人。记得开全局变量。

写个 find 函数，来慢慢解释,代码如下${\colon}$
```cpp
int find(int a)
{
	if(f[a]==a)
	return a;
    else
	return f[a]=find(f[a]);
 } 
```

这就是查找一个人的祖宗的函数。如果他的祖宗就是自己了，就返回这个值。
不然继续递归查找祖宗，直到找到为止。
```cpp
return f[a]=find(f[a]);
```

这里进行了路径压缩，如果其祖宗是 $s$，那么其爸爸的祖宗肯定也是 $s$，方便查找。

再来写集合两个数的函数，让他们认祖归宗${\colon}$
```cpp
void jihe(int a,int b)
 {
 	int ee1=find(a),ee2=find(b);
	if(ee1!=ee2)
	{
		f[ee1]=ee2;
		n--;
	}
	return;
 }
```

~~这里有个坑点是要 return,不然不能开 O2。~~

集合 $a$，$b$，那么看他们的祖宗是不是一个就行了。不然有一个要变成另一个的儿子（如何归顺是随便的）。

最后是~~无聊的~~主代码${\colon}$

记得每次初始化自己的祖宗为自己。

```cpp
int main()
{
	for(int j=1;;j++)//用j纪录组数
	{
	    cin>>n>>m;
	    if(n==0&&m==0)//n,m都为0就结束
	    break;
	    for(int i=1;i<=n;i++)
	    f[i]=i;//一开始祖宗都为自己
	    for(int i=1;i<=m;i++)
    	{
	    	cin>>x>>y;
	    	jihe(x,y);//合并关系
	    }
	    printf("Case %d: %d\n",j,n);//按格式输出即可
	}
}
```

主代码就不放出了。





---

## 作者：YuanZhizheng (赞：0)

 这题就是一个简单的并查集

重点就是解释一下在并的操作中，为什么存在n--的操作。

1.一开始，最大的可能宗教数量为n。

2.如果他们的根节点不同，说明一开始并不知道他们是有同样宗教信仰的。现在，i和j肯定是在同一宗教，所以可能的宗教数量就减少。

3.如果他们的根节点相同，说明他们是一个宗教的，在这之前这两个人肯定被记录过，这个时候对可能的宗教数量没有影响。

上代码（注释中有一些补充）：
```
#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
int a[50005];
int n,m;
int b=0;
int Find(int x)//查
{
    if(a[x]!=x)
        a[x]=Find(a[x]);
    return a[x];
}
void join(int x,int y)//并
{
    x=Find(x);
    y=Find(y);
    if(y!=x)
    {
        n--;
        a[x]=y;
    }
}
int main()
{
    while(~scanf("%d%d",&n,&m))
    {
        int i,j;
        b++;//记录这是第几个例子，详见样例
        if(n==0&&m==0)//题目说n=m=0时退出
            break;
        for(i=1; i<=n; i++)
            a[i]=i;
        while(m--)
        {
            scanf("%d%d",&i,&j);
            join(i,j);
        }
        printf("Case %d: %d\n",b,n);
    }
    return 0;
}
```

---

