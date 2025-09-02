# CORNET - Corporative Network

## 题目描述

原本有 $n$ 个节点，最初每个节点的父亲都是自己。

现在给你若干操作，共分为两种，操作格式如下：

1. `I x y`（大写字母`I`）

将 $x$ 的父亲变为 $y$，而且令 $x$ 与 $y$ 之间的距离为 $\lvert x-y \rvert \bmod 1000$。

2. `E x` 询问x点到其根节点的距离

数据保证对于所有的 $1$ 操作合法，即保证之前 $y$ 不是 $x$ 的父亲、

## 样例 #1

### 输入

```
1
4
E 3
I 3 1
E 3
I 1 2
E 3
I 2 4
E 3
O```

### 输出

```
0
2
3
5```

# 题解

## 作者：___new2zy___ (赞：8)

## 题解 SP264 【CORNET - Corporative Network】

题目传送门:

https://www.luogu.org/problemnew/show/SP264

这题挺好的，可以来练习**并查集**

但其实还是有一点**小变化**的，即**带权（加权）并查集**

~~（这近乎是一道带权并查集板子题）~~（逃~~~

===================================================================

先来看看**算法构建**：

对于本题，有两个操作：

	1.将x的父亲设为y，其中规定x与y之间的距离为abs(x-y)%1000
    
    2.询问点x到其根节点的距离

emmm，冷静思索。。。~~貌似**暴力**可以做~~？？？

#### 思路一：暴力

我们可以每次对于一个I操作，都使得x与y之间连一条边，权值为w=abs(x-y)%1000

如果询问的话直接跑一遍dfs就行了

但是对于n=20000的图，如果每一次都来一下dfs查询答案，那么时间的消耗是不可想象的！

试想最坏情况，一个有20000个节点的链，每次如果查询都是最尾端的节点，都暴力的跑，那么每次查询的时间复杂度将会是O(n^2)，妥妥的TLE了

那么我们不妨换一下思路，是否有一种东西，**支持随时随地查询自己与父节点之间的距离**，而**不会耗费太多时间，同时能更新父子关系**呢？

那么很自然而然的想到---- _**并查集**_ 

因为并查集能很好的维护父子之间的关系，能够在均摊意义下接近常数级别的时间里找出一个节点的父亲

那么我们为了**维护一个节点与自己的根节点之间的距离**，对于并查集的改进算法也应运而生

它就是----**带权（加权）并查集，属于并查集的变种**

有的时候，我们不仅需要像普通并查集一样记录一些元素之间有无关系，还需要记录它们之间有怎样的关系，这时候就需要引入**加权并查集**。

通常情况下，我们使用一个数组d来记录这些关系，d[i]表示元素i与父结点的关系。至于是什么关系，还要根据具体要求来看。

个人还是喜欢叫它**带权并查集**，毕竟它**通常会维护一些距离之类的值**，而距离通常都是有权的（即边权）

#### 思路二：带权并查集

对于本题，就是要维护一个点与它的根节点之间的距离，这正好派上用场

我们可以在**每一次询问操作E时，使用普通并查集中的find函数更新一下父亲，同时维护一下它到自己根节点的距离就行了**。

由于**在find的时候会用到路径压缩**（普通并查集的常规优化方法），我们要**先记录原本的父节点，避免因路径压缩造成的父节点更新，导致维护的信息出错**

这其实就是**带权并查集与普通并查集之间的区别**

代码实现如下：（dis[x]即为x点到自己的根节点之间的距离）

```cpp
inline int find(int x)//带权并查集的find函数 
{
	if(fa[x]==x)return x;
	int old_fa=fa[x];//先记下原本的父节点 
	fa[x]=find(fa[x]);//更新父亲 
	dis[x]+=dis[old_fa];//更新距离（维护值）
	return fa[x];
}
```
这样在使用并查集的时候，我们就能很好的维护一个点到它的根节点之间的距离了

那么对于题目中的I操作，也很好做了

我们每次直接将x点的父亲置为y，同时将abs(x-y)%1000累加到x点的dis值中即可

还有就是。。。注意多组数据，记得清空

大概就没什么了，下面放代码吧

PS：代码里也有解释哦

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
inline int read()//读入优化:快读
{
    int p=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){p=(p<<3)+(p<<1)+c-'0';c=getchar();}
    return f*p;}
const int maxn=20003;
int n,dis[maxn],fa[maxn];
inline void pre()//初始化 
{
	memset(dis,0,sizeof(dis));
	for(int i=1;i<=n;i++)//并查集初始化
		fa[i]=i;
}
inline int find(int x)//带权并查集的find函数 
{
	if(fa[x]==x)return x;
	int old_fa=fa[x];//先记下原本的父节点 
	fa[x]=find(fa[x]);//更新父亲 
	dis[x]+=dis[old_fa];//更新距离 
	return fa[x];
}
int main()
{
	int T=read();
	while(T--)//多组数据
		{
			n=read();
			pre();
			char s[3];
			while(scanf("%s",s)&&s[0]!='O')//注意读入
				{
					if(s[0]=='I')//合并x到y,x为y儿子 
						{
							int x=read(),y=read();
							fa[x]=y;
							dis[x]+=abs(x-y)%1000;
						}
					else if(s[0]=='E')//询问距离 
						{
							int x=read();
							find(x);//先递归下去更新
							printf("%d\n",dis[x]);
						}
				}
		}
	return 0;
}
```
好了，到这里就没什么了。。。

如果有什么问题，可以在评论区留言或者私信我，我会一一回答的

好啦，感谢您的阅读

最后推一波我的blog：

https://www.luogu.org/blog/new2zy/

拜拜~~~






---

## 作者：CaiXY06 (赞：2)

### 带权并查集板子题

双倍经验：[UVA1329 Corporative Network](https://www.luogu.com.cn/problem/UVA1329)

虽然一样，但是 UVA 的数据较水，可以直接暴力水过。

$like\ this\ \downarrow $

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1000;
int T,n,fa[20010];
char c;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)fa[i]=i;
		while(cin>>c&&c!='O'){
			int x,y=0;
			if(c=='I'){
				scanf("%d%d",&x,&y);
				fa[x]=y;
			}
			else{
				scanf("%d",&x);
				while(x!=fa[x]){
					y+=abs(x-fa[x])%mod;
					x=fa[x];
				}
				printf("%d\n",y);
			}
		}
	}
	return 0;
}
```
显然时间复杂度是 $O(TQn)$ 级别的，铁定的 **TLE**。

所以我们考虑用并查集路径压缩，优化代码，降至 $O(TQ\log n)$。

我们维护两个值， $x$ 的祖先 $fa$ 以及 $x$ 到祖先的距离 $dis_{x\rightarrow fa}$ 。

注意在维护并查集时，要先路径压缩查询祖先，再更新 $dis$ ，不然就会像我一样 **WA** 了半天而不自知。

附上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1000;
int T,n,fa[20010],dis[20010];
char c;
inline int find(int x){//路径压缩，维护并查集
	if(fa[x]==x)return x;
	int father=fa[x];
	fa[x]=find(fa[x]);
	dis[x]+=dis[father];
	return fa[x];
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)fa[i]=i;//初始化
		memset(dis,0,sizeof(dis));//有多组数据，所以要清空
		while(scanf(" %c",&c)&&c!='O'){
			int x,y;
			if(c=='I'){
				scanf("%d%d",&x,&y);
				fa[x]=y;//更改父亲节点
				dis[x]=abs(x-y)%mod;
			}
			else{//查询答案
				scanf("%d",&x);
				find(x);
				printf("%d\n",dis[x]);
			}
		}
	}
	return 0;
}
```


---

## 作者：Ferdina_zcjb (赞：1)

这道题用暴力显然 $O(TQn)$ 是很差劲的。

那我们考虑并查集压缩路径（~~似乎是压缩路径的板子~~）。

我们用 $fa$ 数组维护 $x$ 的祖先即 $fa_x$。用 $d$ 数组维护 $dis_{fa \to x}$。

在每次 $find$ 的时候，就将 $d_x+d_{fa_x}$（注意写 $find$ 时的顺序）。

合并时只需要 $d_x = |x-y| \operatorname{mod} 1000$。

以下是代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXM = 2e4+1;
const int mod = 1000;
int fa[MAXM],d[MAXM];
void init(int N){
    for(int i = 1;i <= N;++i){
        fa[i] = i;
        d[i] = 0;
    }
    return ;
}
int find(int x){//找爸爸。
    if(fa[x] == x)return x;
    int fat = fa[x];
    fa[x] = find(fa[x]);
    d[x] = d[x] + d[fat];//注意顺序。
    return fa[x];
}
void change(int x,int y){//合并。
    fa[x] = y;//合并x到y。
    d[x] = abs(x-y)%mod; 
    return ;
}
signed main(){
    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        init(n);
        string c;
        while(cin >> c){
            if(c[0] == 'O')break;//注意是“O”不是“0”。
            //cout << c << endl;
            if(c[0] == 'I'){//合并。
                int u,v;
                cin >> u >> v;
                change(u,v);
            }else if(c[0] == 'E'){//查询。
                int v;
                cin >> v;
                find(v);
                cout << d[v] << endl;
            }
        }
    }
}
```


---

## 作者：COsm0s (赞：1)

## 带权并查集

**题目大意**

一棵树有 n 个节点，若干次操作，每次操作有如下两种形式：

+ 将 $x$ 的父亲改为 $y$，此时令 $x$ 到 $y$ 的距离为 $ |x-y| \bmod 1000$。

+ 求 $x$ 到其根节点的距离。

**思路1**

暴力，每次都搜一遍最短路，很容易超时，而且代码量很大。

**思路2（正解）**

带权并查集，带权并查集就是在普通的并查集的基础上维护了一个 $dis$ 数组，本题中，$dix_x$ 表示 $x$ 节点到它父节点的距离。

每次寻找时都将 $dis_x$ 的距离加上 $dis_{fa_x }$ 的距离，合并时将 $dis_x$ 的值按照 $ \lvert x-y \rvert \bmod 1000$ 用。

由于在查找的时候会用到路径压缩，所以要先记录原来的父节点，避免因路径压缩造成的父节点更新，导致出错。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod = 1e3;//每次要 mod 1000 
int n,fa[20010],dis[20010];//fa数组是当前节点的父节点，dis数组是他们的距离 
char c;
inline int find(int x) {
	if(fa[x]==x)return x;
	int ans=fa[x];
	fa[x]=find(fa[x]);
	dis[x]+=dis[ans];//x到根的距离=x到父亲的距离+父亲到根的距离
	return fa[x];
}
//查找函数 
int main() {
	int T;
	cin>>T;
	while(T--) {
		cin>>n;for(int i=1; i<=n; i++)fa[i]=i;
		memset(dis,0,sizeof(dis));//注意初始化 
		while(scanf(" %c",&c)&&c!='O') {//注意 %c 前的' ' 
			int x,y;
			if(c=='I') {
				cin>>x>>y;
				fa[x]=y;
				dis[x]=abs(x-y)%mod;
			} 
			//第一种情况 
			else {
				cin>>x;
				find(x);
				cout<<dis[x]<<endl;
			}
			//第二种情况 
		}
	
	}
	return 0;
}
```


---

## 作者：pokefunc (赞：1)

挺好的带权并查集题。

最开始所有结点的父亲都是自己，每次操作把结点不断地连到其他节点上，每次询问求到根的距离......

这不就是带权并查集了嘛。

带权并查集，顾名思义，就是除了维护基本关系以外还维护一个到根距离 `dist` 的并查集。

正常的并查集 `find` 函数长这样（其实我更习惯用三目运算符压成一行，这样写是方便接下来改）：

```cpp
int find(int x){
    if(x==fa[x])return x;
    else{
        int r=find(fa[x]);
        return fa[x]=r;
    }
}
```

带权并查集加一行就完了：

```cpp
int find(int x){
    if(x==fa[x])return x;
    else{
        int r=find(fa[x]);
        dist[x]+=dist[fa[x]]; //x到根的距离=x到父亲的距离+父亲到根的距离
        return fa[x]=r;
    }
}
```

而 `merge` 也只用加一行：

```cpp
void merge(int x,int y){
    int p=find(x),q=find(y);
    if(p==q)return;
    fa[p]=q;
    dist[q]+=dist[p];//这行是加的
}
```

这道题更简单，由于题目给定了合并方向不能用启发式合并（~~这不是省码量嘛哈哈哈哈~~），`merge` 操作甚至不需要判父亲，距离也可以直接加：

```cpp
void merge(int x,int y){
    fa[x]=y;dist[x]+=abs(x-y)%1000;
}
```

然后就做完了。

至于复杂度嘛......我的教练曾说过只带路径压缩的并查集最坏会被卡到总复杂度 $O(n \log n)$，但只是提了一嘴所以本蒟蒻不会证，不过相信对付 $2 \times 10^4$ 规模是够了。

### AC Code:

```cpp
#include<cstdio>
#include<iostream>
#include<string>
#include<cmath>
const int M=2e4+5;
int fa[M],dist[M];
int n;
void init(int x){for(int i=1;i<=x;++i)fa[i]=i,dist[i]=0;}
int find(int x){
    if(x==fa[x])return x;
    else{
        int r=find(fa[x]);
        dist[x]+=dist[fa[x]];
        return fa[x]=r;
    }
}
void merge(int x,int y){fa[x]=y;dist[x]+=abs(x-y)%1000;}
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        init(n);
        int u,v;
        std::string s;
        while(std::cin>>s&&s[0]!='O'){
            if(s[0]=='E'){
                scanf("%d",&u);
                find(u);
                printf("%d\n",dist[u]);
            }
            else{
                scanf("%d%d",&u,&v);
                merge(u,v);
            }
        }
    }
    return 0;
}
```



---

## 作者：Siteyava_145 (赞：0)

并查集模板题。

操作 `I`：让 $x$ 认 $y$ 做爸爸。

操作 `E`：输出 $x$ 与他的爸爸的距离。

---

就是在并查集模板上加一个 ```dis``` 数组，来记录距离即可。

操作 `I` 直接 ```f[x]=y``` 即可，将 $x$ 与他爸爸的距离改为 $\left\vert {x-y}\right\vert \bmod 1000$。

操作 `E` ：找 $x$ 的爸爸，再算出他们之间的距离。

``find`` 函数：

在原模板的基础上，加上一行更新距离，也就是 ```dis[x]+=dis[fa]```，更新更远的祖先的距离。

代码：

```
#include<bits/stdc++.h>
using namespace std;
int f[200005],dis[200005];
int find(int x){
    if(f[x]==x){//祖先
        return x;
    }
    int fa=f[x];//原来的爸爸
    f[x]=find(f[x]);//找爸爸的爸爸
    dis[x]+=dis[fa];//更新距离
    return f[x];
}
int main(){
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        char op;
        for(int i=1;i<=n;i++)f[i]=i;//必须加的初始化
        memset(dis,0,sizeof dis);//dis 清空。
        while(cin>>op){
            if(op=='O')break;//是O，不是0！！！
            int x,y;
            if(op=='I'){
                cin>>x>>y;
                f[x]=y;
                dis[x]=abs(x-y)%1000;
            }else if(op=='E'){
                cin>>x;
                find(x);
                cout<<dis[x]<<endl;
            }
        }
    }
    return 0;
}
```


---

## 作者：UperFicial (赞：0)

# 带权并查集模板

### 前言

白赚了道蓝题，~~好评~~。

题目链接：[$\text{Link}$](https://www.luogu.com.cn/problem/SP264)。

~~再次无耻的求互关/kel~~

### 题目大意

一棵树有 $n$ 个节点，若干次操作，每次操作有如下两种形式：

- `I x y`：将 $x$ 的父亲改为 $y$，此时令 $x$ 到 $y$ 的距离为 $\mid x-y\mid\bmod 1000$。

- `E x`：求 $x$ 到其根节点的距离。

保证 `I` 操作合法。

### 解题思路

第一个感觉就是暴力，每次都 $dijkstra$ 一遍，显然很容易超时。

第二个感觉就是**带权并查集**，带权并查集通俗来讲就是在普通的并查集的基础上额外维护了一个 $dis$ 数组，$dix_x$ 来记录 $x$ 与父节点的某种关系或是权值，在本题中，$dix_x$ 用来表示 $x$ 到它父节点的距离。

每次 $find$ 时都额外将 $dis_x$ 的距离加上 $dis_{par_x }$ 的距离，合并时额外将 $dis_x$ 的值按照题目中的公式去用就好了。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=20010;
const int MOD=1000;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')s=s*10+(ch-'0'),ch=getchar();
	return s*w;
}
int t,n,par[MAXN],rankk[MAXN],dis[MAXN];
void init(int n)
{
	for(register int i=1;i<=n;i++) 
	{
		par[i]=i;
		rankk[i]=0;
		dis[i]=0;
	}
}
int find(int x)
{
	if(par[x]==x) return par[x];
	int fa=par[x];
	par[x]=find(par[x]);
	dis[x]+=dis[fa];
	return par[x];
}
int abs(int x)
{
	if(x>=0) return x;
	else return -x;
}
void unite(int x,int y)
{
	par[x]=y;
	dis[x]=abs(x-y)%MOD;
}
void solve()
{
	n=read();
	init(n);
	while(true)
	{
		char opt[5];
		scanf("%s",opt);
		if(opt[0]=='O') return;
		if(opt[0]=='I')
		{
			int x=read(),y=read();
			unite(x,y);
		}
		else
		{
			int x=read();
			find(x);
			printf("%d\n",dis[x]);
		}
	}
}
int main()
{
	t=read();
	while(t--) solve();
	return 0;
}
```


---

## 作者：FutureThx (赞：0)

~~感觉这题最多绿……~~
### 题意
要求维护一个并查集，并且要求可以询问每个节点对于祖先节点的距离
### 思路
其实就是一个并查集的板子题，与一般的模板题不同的是这题**需要开两个并查集维护，** 那么具体是哪两个并查集呢？
- $father$ 数组，对于 $father_i$ 表示第 $i$ 个节点的父亲节点
- $dis$ 数组，对于 $dis_i$ 就表示第 $i$ 个节点与祖先的距离
$ $

那么我们只要在**寻找祖先的过程中不断更新 $dis$ 数组，$father$ 数组常规维护**，这题就迎刃而解了。

一个小提示:$SPOJ$ 中的评测要求可能与洛谷不同，$C++$ 死活 $CE$ 的同学建议开 $C++11$ ~~(就因为这事我错了几次)~~
### 代码
代码解释注释里有，抄袭后果自负

$100pts:$
```cpp
#include <iostream>
#include <cmath>
using namespace std;
int dis[20001],father[20001];
int find_father(int x){
    if(father[x] == x)
       return x;
    int second_father = father[x];
    father[x] = find_father(father[x]);
    dis[x] += dis[second_father];
    return father[x];
}
int main(){
    int t;
    cin >> t;
    for(int i = 1;i <= t;i++){
        int n;
        cin >> n;
        for(int i = 1;i <= n;i++)
            father[i] = i,dis[i] = 0;
        char opt;
        cin >> opt;
        while(opt != 'O'){
            if(opt == 'E'){
                int x;
                cin >> x;
                find_father(x);
                cout << dis[x] << endl; 
            }
            else{
                int x,y;
                cin >> x >> y;
                father[x] = y;
                dis[x] = abs(x - y) % 1000;
            }
            cin >> opt;
        }
    }
    return 0;
}
```
### 后记
$Updata \ 2020.9.15:$ 完成题解，求管理员通过

---

## 作者：_Qer (赞：0)

~~这不是裸并查集么~~  
下面来一个~~TLE3次，最后~~AC的程序

前置技能：[并查集](https://www.luogu.org/problemnew/show/P3367)

并查集中每个节点存它的父亲和到根节点的距离，再存它的儿子和他父亲的下一个儿子（后面更改距离用）  
大部分和并查集模板差不多，~~为了不要TLE~~，把递归的部分都尽量改成循环形式，~~由于我不会其他算法~~，把更改的操作改成改自己和自己的子孙的距离，就不需要路径压缩了。  
更新部分是和别的并查集最大的不同，这里是改子孙，所以之前存了儿子和兄弟（父の下一个儿子），用BFS来修改每个子孙的距离。

这个方法的修改应该是O(n)的（欢迎评论计算结果），查询是O(1)，出题人的数据应该主要是卡查询O(n)的算法，所以这种写法应该不容易被卡。

PS：~~代码可能有丶问题，~~欢迎挑错

```cpp
#include <bits/stdc++.h>
using namespace std;
int T, n;
struct info{
	int prt, dis;//父亲、到根距离
	int son, nxt;//儿子、兄弟
} node[20010];
inline void init() {
	memset(node, 0, sizeof(node));//全部初始化为0
    //为了减少一个O(n)的并查集初始化（其实可以不要），所以prt=0即表示为根
}
/*没用
inline int fprt(int x) {
	while (node[x].prt != 0) {
		x = node[x].prt;
	}
	return x;
}*/
inline void updata(int x, int dis) {
	//更新点x的子孙到根距离
    //dis为需要更改的每个点所需增加的距离
	queue<int> que;
	que.push(node[x].son);
	int u;
	while (!que.empty()) {
		u = que.front(), que.pop();
		node[u].dis += dis;
		if (node[u].nxt)  que.push(node[u].nxt);
		if (node[u].son)  que.push(node[u].son);
	}
}
inline void mix(int x, int y) {//合并
	node[x].nxt = node[y].son, node[y].son = x, 
	node[x].prt = y, node[x].dis = abs(x - y) % 1000 + node[y].dis;
    //依次更改x的兄弟、y的儿子、x的父亲、x的到根距离
	updata(x, node[x].dis);//更新x的子孙
	return;
}
int main() {
//scanf更快
  scanf("%d", &T);
  for (int i = 1; i <= T; ++i) {
  	scanf("%d", &n);
  	init();
  	char op;//操作
  	int x, y;//操作数
  	op = getchar();
  	while (op != 'I' && op != 'E' && op != 'O') {op = getchar();}
    //以上为读入操作符（cin慢scanf会读空格）
  	while (op != 'O') {
  		if (op == 'I') {
  			scanf("%d%d", &x, &y);
  			mix(x, y);//合并
			} else {
				scanf("%d", &x);
				printf("%d\n", node[x].dis);
                //到根距离
			}
  			op = getchar();
  			while (op != 'I' && op != 'E' && op != 'O') {op = getchar();}
        	//同上输入
		}
	}
  return 0;
}

```

---

