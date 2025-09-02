# pSort

## 题目描述

给定一个长度为 $n$ 的数列 $\{a_n\}$，初始时 $\{a_n\} = \{1, 2, \dots, n\}$。位置 $i$ 上的数可以和位置 $i \pm d_i$ 上的数交换。给定一个 $1 \sim n$ 的全排列，问初始的数列可否交换成给定的形式。

## 说明/提示

$1 \le n \le 100$

## 样例 #1

### 输入

```
5
5 4 3 2 1
1 1 1 1 1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
7
4 3 5 1 2 7 6
4 6 6 1 6 6 1
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
7
4 2 5 1 3 7 6
4 6 6 1 6 6 1
```

### 输出

```
YES
```

# 题解

## 作者：赤霞QvQ (赞：36)

## 一道并查集好题：思维难度：中，程序实现难度：简单

感觉翻译的不太好，因为不是$i$这个数能与$i±d[i]$交换，而是第$i$个格子中的数能与第$i±d[i]$个格子中的数交换。

大致题意：给你一串数字为$1$~$n$，然后告诉你每一个格子能与哪些格子中的数字交换，问你最后能不能得到给你的一组排列

本蒟蒻想了好久也没想出来，看到算法标签才顿悟：这个并查集藏得好深！

我们先证明一个东西：如果有一串数字，每相邻两个数字都可以交换，必然可以得到这组数字的所有全排列

我们先来看一组：

$ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ 位置：$1$ $ $ $2$ $ $ $3$ $ $ $4$ $ $ $5$

位置上的数：$1$ $ $ $2$ $ $ $3$ $ $ $4$ $ $ $5$

要得到的数：$5$ $ $ $3$ $ $ $1$ $ $ $2$ $ $ $4$

那么我们先考虑$1$这个数字，它如果要从第$1$个位置到第$3$个位置，必须先与第$2$个位置上的数字交换，然后与第$3$个位置上的数字交换，就能到第$3$个位置了！

$ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ 位置：$1$ $ $ $2$ $ $ $3$ $ $ $4$ $ $ $5$

位置上的数：$2$ $ $ $3$ $ $ $1$ $ $ $4$ $ $ $5$

要得到的数：$5$ $ $ $3$ $ $ $1$ $ $ $2$ $ $ $4$

现在我们再来考虑$2$这个数字，如果它要从第$1$个位置到第$4$个位置，就必须先和第$2$个位置上的数交换，然后和第$3$个位置上的数交换，然后再和第$4$个位置上的数交换，就可以到第$4$个位置啦！

$ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ 位置：$1$ $ $ $2$ $ $ $3$ $ $ $4$ $ $ $5$

位置上的数：$3$ $ $ $1$ $ $ $4$ $ $ $2$ $ $ $5$

要得到的数：$5$ $ $ $3$ $ $ $1$ $ $ $2$ $ $ $4$

这时候我们发现，$1$不在第$3$个位置了！那么我们再把$1$调到第$3$个位置：

$ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ 位置：$1$ $ $ $2$ $ $ $3$ $ $ $4$ $ $ $5$

位置上的数：$3$ $ $ $4$ $ $ $1$ $ $ $2$ $ $ $5$

要得到的数：$5$ $ $ $3$ $ $ $1$ $ $ $2$ $ $ $4$

那么这时候，$1$和$2$都已经调整好了，那我们看到$3$，把$3$用以上操作调到第$2$个位置

$ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ 位置：$1$ $ $ $2$ $ $ $3$ $ $ $4$ $ $ $5$

位置上的数：$4$ $ $ $3$ $ $ $1$ $ $ $2$ $ $ $5$

要得到的数：$5$ $ $ $3$ $ $ $1$ $ $ $2$ $ $ $4$

我们来检查一下$1$和$2$，发现$3$的调整没有影响到$1$和$2$，那么我们看到$4$

我们要把$4$调整到第$5$个位置，那么就会变成这样：

$ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ 位置：$1$ $ $ $2$ $ $ $3$ $ $ $4$ $ $ $5$

位置上的数：$3$ $ $ $1$ $ $ $2$ $ $ $5$ $ $ $4$

要得到的数：$5$ $ $ $3$ $ $ $1$ $ $ $2$ $ $ $4$

发现$1$、$2$和$3$的位置都被改变了，那么我们从右往左依次把$2$、$1$、$3$调整好，就会变成这样：

$ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ $ 位置：$1$ $ $ $2$ $ $ $3$ $ $ $4$ $ $ $5$

位置上的数：$5$ $ $ $3$ $ $ $1$ $ $ $2$ $ $ $4$

要得到的数：$5$ $ $ $3$ $ $ $1$ $ $ $2$ $ $ $4$

一对照，发现一样，成功啦！

那么我们总结出一条规律：$1$~$n$依次调整，每调整完一个数就检查前面的数，这样下来总归可以成功

那我们来看一下这道题：

他说第$i$个格子能与第$i±d[i]$个格子上的数交换

那我们不妨把所有能交换的格子排成一列，这样交换过程就变成了与相邻的格子交换，那如果$f[i]$这个数在这一列中，说明总归可以交换成功

这样一说，并查集就暴露了吧

把所有能交换的格子放在一个并查集里，最后检查$i$与$f[i]$是否在一个并查集里，这道题就$A$了！

上代码！$music$！

~~鸡你太美！oh，baby！鸡你太美！~~

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,fa[105],f[105],d[105];
int father(int x)     // 并查集基本操作之找爸爸
{
	if(fa[x]!=x) fa[x]=father(fa[x]);
	return fa[x];
}

void un(int x,int y)      //并查集基本操作之加一个爸爸
{
	int u=father(x),v=father(y);
	if(u!=v) fa[u]=v; 
}

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
	    cin>>f[i];     //在输入过程中顺便初始化一下
	    fa[i]=i;
	}
	for(int i=1;i<=n;i++)
	{
		cin>>d[i];
		if(i>d[i]) un(i,i-d[i]);    //在合并的时候一定要注意不要越界了
		if(i+d[i]<=n) un(i,i+d[i]);
	}
	for(int i=1;i<=n;i++)
	{
		if(father(i)!=father(f[i]))     //最后的判断
		{
			cout<<"NO"<<endl;
			return 0;
		}
	}
	cout<<"YES"<<endl;
	return 0;
}
```

还算比较好理解……把

---

## 作者：PDY08 (赞：29)

本题解使用 **Floyd** 算法进行求解
### 思路
本题主要是求能否交换成给定的样式，

即原本的点 $i$ 能否交换成给定的点 $j$

聪明的我们可以把题目转换成

这幅图中点 $i$ 与点 $j$ 是否相通

所以我们可以采用 **Floyd** 算法求解
### Floyd 算法
1.时间复杂度 
$O(n^3)$

~~数据范围才100嘛~~

2.代码实现简单（三十行不到）

### 重点
1.Floyd 算法的本质是动态规划，$k$ 是阶段，$i$ 和 $j$是附加状态。

我们采用标记的方法

$b[i][j] = 1$ 表示从点 $i$ 可以到达点 $j$

那我们的问题马上就解决了

2.代码中有一部分**位运算**

1 与运算 (&)

两个位都为1时，结果才为1

e.g:

$b[i][k]$ & $b[j][k]$ 表示如果从点 $i$ 能到达点 $k$，并且从点 $j$ 也可以到达点 $k$，那么就可以从点 $i$ 到达点 $j$ 

（$b[i][k]$ & $b[k][j]$ 亦然）

2 或运算 （$|$)

两个位都为0时，结果才为0

我就不解释了吧……~~其实是我懒~~

### 上代码
```cpp
#include <iostream>
using namespace std;
int a[101], b[101][101];
int main() {
	int n, d;
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) b[i][i] = 1; //b[i][j] = 1为从i点可以到达j点
	for (int i = 1; i <= n; i++) {
		cin >> d;
		if (i - d >= 1) b[i][i - d] = 1;
		if (i + d <= n) b[i][i + d] = 1; 
	} 
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				b[i][j] |= (b[i][k] & b[j][k]) | (b[i][k] & b[k][j]);
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		if (!b[i][a[i]]) {
			cout << "No";
			return 0;
		}
	}
	cout << "Yes";
	return 0;
} 
```

#### 既然你看得那么认真，那就点个赞再走吧qwq

---

## 作者：Mistybranch (赞：6)

[传送门](https://www.luogu.com.cn/problem/CF28B)

题目大概意思是：判断数列 $1 - n$ 在经过多次交换后能否到达目标数列 $p_i$（目标数列必为 $1 - n$ 的全排列），注意数列中的第 $i$ 个元素只能与第 $i - d_i$ 个元素和第 $i + d_i$ 个元素进行交换（如果这个元素存在的话）。

其实这道题的难点就在于：怎么才能想到图论。

我们可以将题意转换为：将数列元素中能两两交换的元素放置到同一个集合中，“两两交换”的含义是可以一次交换，也可以多次交换。最后判断时只用看原数列第 $i$ 位的数字 $i$ 与目标数列中第 $i$ 位的数字 $p_i$ 是否在同一集合（也就是判断了这两个数能否成功交换）。想到集合自然就会想到并查集。这就是这道题的思路。

以样例为栗举个栗子（为了看图方便所以画图时画成了环，实际上此题是个数列不是环）：

```
7
4 3 5 1 2 7 6
4 6 6 1 6 6 1
```
- 我们可以把每个数当做一个点（如图）：

![](https://cdn.luogu.com.cn/upload/image_hosting/arlp0i4y.png)

- 扫到第 $1$ 个数，发现可以跟第 $5$ 个数交换，将 $1,  5$ 添加到同一集合（也就是添加一条 $1, 5$ 的边）。扫到第 $2, 3$ 个数，发现没数可以跟这两个数交换。

![](https://cdn.luogu.com.cn/upload/image_hosting/kwjwxo66.png)

- 扫到第 $4$ 个数，发现可以跟第 $3$ 和 $5$ 这两个数交换，将 $4, 3, 5$ 添加到同一集合。扫到第 $5, 6$ 个数，发现没数可以跟这两个数交换。

![](https://cdn.luogu.com.cn/upload/image_hosting/lpl04fa6.png)

- 扫到第 $7$ 个数，发现可以跟第 $6$ 个数交换，将 $7,  6$ 添加到同一集合。结束。

![](https://cdn.luogu.com.cn/upload/image_hosting/5qu8jfwh.png)

那么创建集合的代码就显而易写了：

```cpp
for (int i = 1; i <= n; i++) {
	if (i - d[i] >= 1) {
		Unionn(i, i - d[i]);
	} 
	
	if (i + d[i] <= n) {
		Unionn(i, i + d[i]);
	}
}
```


- 现在一共有 $3$ 个集合，分别为 $[1, 3, 4, 5], [2], [6, 7]$，下面就该判断是否交换成功了。

- 从第 $1$ 个数开始判断是否能与 $d_1 = 4$ 交换（就是看这两个数是否处于同一个集合），发现可以。

- 判断第 $2$ 个数是否能与 $d_2 = 3$ 交换，发现不行，直接跳出，输出 $\texttt{NO}$。

- 如果最后都能满足条件，输出输出 $\texttt{YES}$。

```cpp
for (int i = 1; i <= n; i++) {
	if (!Check(i, p[i])) {
		printf("NO\n");
		return 0;
	}
}

printf("YES\n");
```
完整代码：

```cpp


#include <bits/stdc++.h> 

int n, p[109], d[109];
int f[109];

void Init () {//初始化
	for (int i = 1; i <= n; i++) {
		f[i] = i;
	}
}

int Find (int x) {//寻找 x 节点的父节点
	if (f[x] != x) {
		f[x] = Find(f[x]);
	}
	
	return f[x];
}

void Unionn (int x, int y) {//合并 x y 所在的集合
	x = Find(x);
	y = Find(y);
	
	if (x == y) {
		return ;
	} 
	
	f[y] = x;
}

bool Check (int x, int y) {//判断 x y 是否处于同一集合
	x = Find(x);
	y = Find(y);
	
	return x == y;
}

int main () {
	scanf("%d", &n);
	
	for (int i = 1; i <= n; i++) {
		scanf("%d", &p[i]);
	} 
	
	for (int i = 1; i <= n; i++) {
		scanf("%d", &d[i]);
	} 
	
	Init();
	
	for (int i = 1; i <= n; i++) {
		if (i - d[i] >= 1) {
			Unionn(i, i - d[i]);
		} 
		
		if (i + d[i] <= n) {
			Unionn(i, i + d[i]);
		}
	}
	
	for (int i = 1; i <= n; i++) {
		if (!Check(i, p[i])) {
			printf("NO\n");
			return 0;
		}
	}
	
	printf("YES\n");
	
	return 0;
}
```
注：
- 这道题使用并查集的函数可能跟有些 dalao 的写法不太一样，每个函数的作用已经注释写在函数旁边了。
- 其实这道题还可以用 DFS 来实现，只需判断两点是否连通即可，这里就不再讲详细思路了，有兴趣的 dalao 可自行百度。

---

## 作者：初雪_matt (赞：4)

### 题外话

这道题是一道```dfs```的水题，为什么很多人用并查集。。。

### 题目大意

给你一串数字，然后给出一个格子能跟一些格子交换的关系，问你能不能根据上面给出的关系交换获得目标序列。

### 题目思路

很简单，只要分析了题目即可得出简单的思路，每一个点都跟给出的另一个点连上一条边，最后遍历整个图，把所有路径放进一个```set```里，最后判断```set```是否某一时间内一条路径不等于目标路径就输出```NO```，反之输出```YES```。

### 代码

```cpp
#include<bits/stdc++.h>
#define N 1000005
using namespace std;
int n,a[N],d[N];
vector<int> v[N];//连边用vector
set<int> s1,s2;//存放路径的地方
bool vis[N];//路径是否走过呢？
void dfs(int x){
    if(vis[x]){//循环中止条件，当前这个点被走过了，回溯
        return ;
    }
    s1.insert(x);//记录路径
    s2.insert(a[x]);//记录路径
    vis[x]=1;//千万别忘要把路径标为走过
    for(int i=0;i<v[x].size();i++){
        dfs(v[x][i]);//dfs下一条边
    }
    return ;
}
int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
        a[i]--;//请读者自己想想为什么要减一呢？
    }
    for(int i=0;i<n;i++){
        cin>>d[i];
    }
    for(int i=0;i<n;i++){
        if(i+d[i]<n){
            v[i].push_back(i+d[i]);//以下都是建边
            v[i+d[i]].push_back(i);
        }
        if(i-d[i]>=0){
            v[i].push_back(i-d[i]);
            v[i-d[i]].push_back(i);
        }
    }
    for(int i=0;i<n;i++){
        s1.clear();//记得把路径清空
        s2.clear();//记得把路径清空
        if(!vis[i]){
            dfs(i);//循环每一个节点做开始编号
            if(s1!=s2){//如果两个路径不相等
                cout<<"NO"<<endl;
                return 0;
            }
        }
    }
    cout<<"YES"<<endl;    
}
```



---

## 作者：Error_Eric (赞：2)

### 前言

虽然并查集很帅，但是我不知道为什么没有人用更快更好理解的dfs。

### 正文

我们有以下两个结论：

如果 $j=i+d_i$ 那么 $a_j$ 和 $a_i$ 可以相互替换。

如果 $a_i$和 $a_j$，$a_i$ 和 $a_k$ 可以相互替换，那么 $a_j$ 和 $a_k$ 可以相互替换。

其正确性显然。

那么可以考虑抽象成一下题目：每一个点向 $i+d_i$ 和 $i-d_i$ 连**无向**边，求 $i$ 和 $f_i$ 是否在同一连通块。

虽然我知道并查集很帅，但是它的时间复杂度是 $O(n\alpha(n))$ ，其中 $\alpha()$ 表示[阿克曼函数](https://en.wikipedia.org/wiki/Ackermann_function)的反函数。大概在 $n\log n$ 上。所以我决定用 $O(n)$ 的 dfs。

将同一个连通块图上同一个颜色。判断这个数字和目标数字是否在同一连通块。

由于数据的特殊性，可以不用前向星之类的存边方式。

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<vector>
using namespace std;
#define il inline
#define rei register int
il void readln(int &I){//快读不解释
	I=0;char C=getchar();
	while(!isdigit(C))C=getchar();
	while( isdigit(C))I=I*10+C-'0',C=getchar();
}
int n,d[105],f[105],c[105],top;//n d如题意 f 目标排列 c 颜色 ，top 目前用到的最后的颜色
vector<int>u[105];//记录这个点连着的点
void dfs(int x,int col){//dfs(节点，颜色)
	for(rei i=0;i<u[x].size();i++)//对于每个节点
		if(!c[u[x][i]])//如果没有被访问过
			c[u[x][i]]=col,dfs(u[x][i],col);//dfs
}
int main(){
	readln(n);
	for(rei i=1;i<=n;i++)readln(f[i]);
	for(rei j=1;j<=n;j++){
		readln(d[j]);
		if(j-d[j]>=1)u[j-d[j]].push_back(j),u[j].push_back(j-d[j]);//连边
		if(j+d[j]<=n)u[j+d[j]].push_back(j),u[j].push_back(j+d[j]);//连边
	}
	for(rei i=1;i<=n;i++)if(!c[i])c[i]=++top,dfs(i,top);//从每个节点尝试开始dfs。
	for(rei i=1;i<=n;i++)if(c[i]!=c[f[i]])return puts("NO"),0;//如果有一个不行，那么整个不行。
	return puts("YES"),0;//那么可行。
}
```

不难发现，每个循环的复杂度为 $O(n)$ ，dfs 的复杂度为 $O(n)$ (每个节点最多被访问到一次）。

因为每次之后往 u 里面增加两个数，所以 $\sum u[i].size()<2\times n$

时空复杂度 $O(n)$ 。

---

## 作者：Lates (赞：2)

题目很显然。

对于位置 $i$，可以与 $i+d_i$ 交换 或 $i-d_i$ 交换。

考虑把 $n$ 个位置抽象成图，则 $i$ 位置可以与 $i+d_i,i-d_i$ 连无向边表示 $i,i+d_i,i-d_i$ 可以互相交换。

可以发现这三个位置的值可以通过多次交换得到所有的排列。

把上面结论推广，考虑对于每个 $i$，向 可以到达的位置连边，则建完图后，每个联通块都可以通过多次交换得到任意排列。

如 样例 $2,3$

![](https://i.loli.net/2020/04/26/1m3Hrn6i28E7olU.png)

可以得到三个联通块，即这三个联通块内位置上的数都可以通过多次交换得到任意排列。

样例 $2$ 中

要让 $1,2,3,4,5,6,7$ 变为 $4,3,5,1,2,7,6$

我们要把 原来在位置 $3$ 中的 $3$，排到位置 $2$ 去，

但是我们发现位置 $2,3$ 不在一个联通块内，则不能进行排列，所以是 $No$。

样例 $3$ 中

要让 $1,2,3,4,5,6,7$ 变为 $4 ,2 ,5 ,1 ,3 ,7,6$

可以发现对应点都在一个联通块内，则可以进行排列，所以是 $Yes$

所以 我们只要维护一个并查集，对于 $i$ 和 要转化的序列的 第 $i$ 项判断是否在一个联通块内即可。

$Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
inline int read(){
	register int x=0,f=0,ch=getchar();
	while('0'>ch||ch>'9')f^=ch=='-',ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^'0'),ch=getchar();
	return f?-x:x;
}
const int MAX=105;
int n,d,a[MAX],f[MAX];
int fa(int x){
	return f[x]==x?x:f[x]=fa(f[x]);
}
int x,y;
signed main(){
	n=read();
	for(register int i=1;i<=n;++i){
		a[i]=read();f[i]=i;
	}
	for(register int i=1;i<=n;++i){
		d=read();
		if(i-d>=1){
			x=fa(i);y=fa(i-d);
			if(x!=y)f[y]=x;
		}
		if(i+d<=n){
			x=fa(i);y=fa(i+d);
			if(x!=y)f[y]=x;
		}
	} 
	for(register int i=1;i<=n;++i){
		if(fa(i)!=fa(a[i])){
//			printf("%d %d\n",i,a[i]);
			return 0,puts("NO");
		}
	}
	puts("YES");
	return 0;
}

```

---

## 作者：mot1ve (赞：1)

看了其他题解的分析，自己思考一番之后想出了一个**很简单的思路**。

这个题的关键就在于 **如何想出要使用并查集**。

我们知道，如果 $a$ 可以推出 $b$，$b$ 可以推出 $c$，那么 $a$ 也可以推出 $c$，并查集就是维护这样一种具有传递以及集合关系的数据结构。

举个例子，$1$ 可以和 $3$ 交换，$3$ 可以和 $5$ 交换，那么 $1,3,5$ 之间就可以搞出全排列来，这个非常显然。那么只要 $n$ 个数在同一个集合内，那么这$n$个数的位置可以随意互换。

所以，要判断 $i$ 可以不可以到 $a_i$ 的位置上就判断 $i$ 和 $a_i$ 在不在一个集合内就可以了，因为如果 $i$ 和 $a_i$ 在同一个集合内，这两个数位置就可以互换。

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,fa[100010],a[100010];
int find(int x)
{
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}
void unionn(int x,int y)
{
	fa[find(x)]=find(y);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		fa[i]=i;
	}
	for(int i=1;i<=n;i++)
	{
		int d;
		scanf("%d",&d);
		if(i-d>0) unionn(i,i-d);
		if(i+d<=n) unionn(i,i+d);
	}
	for(int i=1;i<=n;i++)
	{
		if(find(i)!=find(a[i]))
		{
			printf("NO");
			return 0;
		}
	}
	printf("YES");
	return 0;
}


---

## 作者：ahawzlc (赞：1)

思路：并查集

----

首先我们知道，假如 a 可以变换成 b，b 可以变换成 c，那么 a 可以变换成 c ，这个也是并查集```find()```操作的主打功能。

题目要求其实就是把数列``[1,n]``变换成题目所给序列，并且给了每个位置能变换到哪个位置。

那么我们把每个位置和这个位置能够变换到的位置```merge()```起来，最后查看目标位置和原位置是否在一个并查集中，即可得到答案。

``` cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=105;
int f[N],to[N],d[N];
int find(int x) {
	if(f[x]!=x) f[x]=find(f[x]);
	return f[x];
}
void merge(int x,int y) {
	x=find(x);
	y=find(y);
	if(x!=y) f[x]=y;
}
int main() {
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {
		f[i]=i;
		scanf("%d",&to[i]);
	}
	for(int i=1;i<=n;i++) {
		scanf("%d",&d[i]);
		if(i-d[i]>0) merge(i,i-d[i]);
		if(i+d[i]<=n) merge(i,i+d[i]);//注意不要越界
	}
	for(int i=1;i<=n;i++) {
		if(find(i)==find(to[i])) continue;
		puts("NO");
		return 0;
	}
	puts("YES");
	return 0;
}

```

---

## 作者：Refined_heart (赞：1)

对于并查集的考察。

首先我们知道，值在哪里不重要，问题是它是否能到达它应该到的位置。

那么，我们用并查集维护一下每个点能到的位置，就是把$i$和$i-d[i],i+d[i]$合并起来，注意判断它们是不是在范围内，即 $(x>0$ $and$ $x<n)$

那么思路就显然了。

初始化之后，对于它们进行合并。

合并完之后，判断$i$点是否能到达目标点。不能就直接输出$NO$就好，否则$YES$.

$Code:$
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int n,f[500000],d[500000];
int goal[500000];
inline int find(int x){return x==f[x]?x:f[x]=find(f[x]);}
inline bool check(int x){
	return (x>0)&&(x<n);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d",&goal[i]);
	for(int i=1;i<=n;++i)scanf("%d",&d[i]);
	for(int i=1;i<=n;++i)f[i]=i;
	for(int i=1;i<=n;++i){
		int l=i-d[i],r=i+d[i];
		if(check(l)){
			int fx=find(l),fy=find(i);
			if(fx!=fy)f[fx]=fy;
		}
		if(check(r)){
			int fx=find(r),fy=find(i);
			if(fx!=fy)f[fx]=fy;
		}
	}
	for(int i=1;i<=n;++i)
		if(find(i)!=find(goal[i])){
			printf("NO\n");
			return 0;
		}
	printf("YES\n");
	return 0;
} 
```


---

## 作者：梦游的小雪球 (赞：1)

- 在看到这道题的时候，我是一脸懵逼的，但是，在我看我标签后，瞬间恍然大悟......众所周知，并查集是用来维护具有传递以及集合关系的数据结构的，也就是说，我们要把什么东西合并在一起。

## 梦雪的思路

- 将互相可以到达的点放在一个集合中，在最后看看每个点是否与他的目标点在一个集合内，只要在一个集合内，就一定可以移动到。

- 最为一个文科智障......你们还是看代码吧。

## 你们的最爱

```
#include<bits/stdc++.h>
using namespace std;
int n,m,f[120],a[120],b[120];
int zqq(int k){
	if(f[k]==k)return k;
	return f[k]=zqq(f[k]);
}//并查集基本操作——寻找祖宗
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		f[i]=i;
		cin>>b[i];
	}
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(i-a[i]>0)
			if(zqq(i)!=zqq(i-a[i]))
				f[zqq(i)]=zqq(i-a[i]);
		if(i+a[i]<=n)
			f[zqq(i)]=zqq(i+a[i]);
     		//将互相可以到达的点放在同一集合内。
	}
	for(int i=1;i<=n;i++){
		if(zqq(i)!=zqq(b[i])){
			cout<<"NO"<<endl;
			return 0;
		}//只要有一个点不行就输出“NO”
	}
	cout<<"YES"<<endl;//否则输出“YES”
    return 0;
}
```


---

## 作者：yimuhua (赞：0)

**题意：**

本题求能否交换成给定的样式，即原本的点 _i_ 能否交换成给定的点 _j_ 。

**思路：**

我们可以把它转换为点 _i_ 与点 _j_ 是否相通，这样答案就显而易见了。

**算法：**

并查集

**AC代码：**

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[105], b[105], fa[105];
int find(int x) {
    if(x == fa[x])//根节点
        return x;
    return fa[x] = find(fa[x]);//路径压缩
}
void unionn(int x, int y) {//合并
    int fx = find(x), fy = find(y);//各自所在的集合
    if(fx != fy)
        fa[fx] = fy;
    return;
}
int main() {
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i], fa[i] = i;//初始化
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
        if(i > b[i])//要判断界限，否则会RE
            unionn(i, i - b[i]);
        if(i + b[i] <= n)//界限
            unionn(i, i + b[i]);
        //可以到达(联通)的就合并。
    }
    for(int i = 1; i <= n; i++)
        if(find(i) != find(a[i])) {//最后判断能否全部到达目标位置
            cout << "NO";//不能就输出"NO"
            return 0;
        }
    cout << "YES";//成功到达就输出"YES"
    return 0;
}
```


---

## 作者：happy_dengziyue (赞：0)

### 1 思路

可以转换是指，每个原排列上的数字都要转换为目标排列。那么，这道题可以使用并查集。

那么，设每个数为点，转换规则为边，维护一个并查集，如果每个原排列上的数都与目标排列的对应的数“有亲戚关系”，就可以转化，输出“YES”；否则输出“NO”。

样例1的示例：

输入：
```
5
5 4 3 2 1
1 1 1 1 1
```

能够转换的有：（以下用下标表示）

$1\to2$

$2\to1$

$2\to3$

$3\to2$

$3\to4$

$4\to3$

$4\to5$

$5\to4$

而我们需要的转换：（同样用下标表示）

$1\to5$

$2\to4$

$4\to2$

$5\to1$

以上4个转换中，每一对数都有“亲戚关系”，所以输出“YES”。

### 2 代码与记录

```cpp
#include<cstdio>
using namespace std;
const int max_n=100;
int n;
int a[max_n+2];//目标状态
int d[max_n+2];//转换数组
int fa[max_n+2];//并查集
bool ok=true;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF0028B_1.in","r",stdin);
	freopen("CF0028B_1.out","w",stdout);
	#endif
	//输入
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",a+i);
	}
	for(int i=1;i<=n;++i){
		scanf("%d",d+i);
	}
	//并查集初始化
	for(int i=1;i<=n;++i){
		fa[i]=i;
	}
	//并查集连边
	for(int i=1;i<=n;++i){
		if(i-d[i]>=1){//注意不要越界
			int xf=i,yf=i-d[i];
			while(xf!=fa[xf]){
				xf=fa[xf];
			}
			while(yf!=fa[yf]){
				yf=fa[yf];
			}
			if(xf!=yf){//可以连边
				fa[xf]=yf;
			}
		}
		if(i+d[i]<=n){//注意不要越界
			int xf=i,yf=i+d[i];
			while(xf!=fa[xf]){
				xf=fa[xf];
			}
			while(yf!=fa[yf]){
				yf=fa[yf];
			}
			if(xf!=yf){//可以连边
				fa[xf]=yf;
			}
		}
	}
	//并查集检查
	for(int i=1,xf,yf;i<=n;++i){
		xf=i;
		yf=a[i];
		while(xf!=fa[xf]){
			xf=fa[xf];
		}
		while(yf!=fa[yf]){
			yf=fa[yf];
		}
		if(xf!=yf){//不能转换
			ok=false;
			break;
		}
	}
	printf("%s\n",(ok?"YES":"NO"));
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/51711950)

By **dengziyue**

---

## 作者：Oscar12345 (赞：0)

大家好，我是坐等拍砖的蒟蒻一枚，这道题呢是求关于图论的连通性的，难度嘛...普及组，还好啦，不算很难，至于做法。。。一番YY之后突然发现，这么小的数据量完全就是给Floyed准备的嘛...泪崩啊！！！

代码很简单，有注释（嗯哼。。。只有一行）

```cpp
#include <iostream>
#include <cstdio>
const int LMT=102;
using namespace std;
bool gra[LMT][LMT];
int a[LMT];
int main()
{
    int n,d;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)gra[i][i]=1;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&d);
        if(i-d>0)gra[i][i-d]=1;
        if(i+d<=n)gra[i][i+d]=1;
    }
    for(int k=1;k<=n;k++)
     for(int i=1;i<=n;i++)
       for(int j=1;j<=n;j++)
       gra[i][j]|=(gra[i][k]&gra[j][k])|(gra[i][k]&gra[k][j]);//路中有公共指向点即可1->2 3->2 则1->3
    for(int i=1;i<=n;i++)
    if(!gra[i][a[i]])
    {
        printf("NO\n");
        return 0;
    }
    printf("YES\n");
    return 0;
}
```
                         
用的是scanf和pringf，大家应该没问题，为了速度，大家谅解一下。

---

