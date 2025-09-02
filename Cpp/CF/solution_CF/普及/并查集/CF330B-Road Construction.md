# Road Construction

## 题目描述

A country has $ n $ cities. Initially, there is no road in the country. One day, the king decides to construct some roads connecting pairs of cities. Roads can be traversed either way. He wants those roads to be constructed in such a way that it is possible to go from each city to any other city by traversing at most two roads. You are also given $ m $ pairs of cities — roads cannot be constructed between these pairs of cities.

Your task is to construct the minimum number of roads that still satisfy the above conditions. The constraints will guarantee that this is always possible.

## 说明/提示

This is one possible solution of the example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF330B/35d4305bf70554ede027d8d59a869bd396bac3b7.png)These are examples of wrong solutions:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF330B/ae8e621e98d61f91c51460d115381f92d4ec087b.png) The above solution is wrong because it doesn't use the minimum number of edges ( $ 4 $ vs $ 3 $ ). In addition, it also tries to construct a road between cities $ 1 $ and $ 3 $ , while the input specifies that it is not allowed to construct a road between the pair. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF330B/6e2daf27fe5688077c977d3182e39189aa3373cd.png) The above solution is wrong because you need to traverse at least $ 3 $ roads to go from city $ 1 $ to city $ 3 $ , whereas in your country it must be possible to go from any city to another by traversing at most $ 2 $ roads. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF330B/a2943b03b1f25a460029662960912e364f0494fa.png) Finally, the above solution is wrong because it must be possible to go from any city to another, whereas it is not possible in this country to go from city $ 1 $ to $ 3 $ , $ 2 $ to $ 3 $ , and $ 4 $ to $ 3 $ .

## 样例 #1

### 输入

```
4 1
1 3
```

### 输出

```
3
1 2
4 2
2 3
```

# 题解

## 作者：lutaoquan2012 (赞：3)

## 题意：
给你 $n$ 个城市，又给定你 $m$ 条约束，让你不能在 $m_i$ 和 $m_j$ 连边，其中 $m_i$ 和 $m_j$ 是两个点。

## 思路：
这道题我们观察数据给你的图可以发现，构造就是一个**菊花图**，因为这道题有一些约束，所以我们不能随便的定一个点当菊花图的中间，我们要找到一个在给定的约束中不存在的一个点当作中心，也就是说找一个在 $m$ 数组中不存在的点，模拟即可。

## 代码：
```cpp
//
// Created by 55062 on 2024/4/21.
//
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
ll n,m,x,y;
bool flag[1010];
int main() {
    cin>>n>>m;
    cout<<n-1<<endl;
    for(int i=1;i<=m;i++) {cin>>x>>y;flag[x]=flag[y]=true;}
    for(int i=1;i<=n;i++)
        if(flag[i]==false){
            x=i;
            break;
        }
    for(int i=1;i<=n;i++)
        if(x!=i) cout<<x<<" "<<i<<endl;
    return 0;
}
```

---

## 作者：wei2013 (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF330B)

## 题目大意：
特别的，这题翻译出错了，更正看讨论区的第一篇帖子别人的纠正。~~更大一部分原因是蒟蒻看不懂不会翻译~~。

## 题目思路：
	
仔细观察，发现每一个城市都可以通过最多**两条**道路，自然也就能想到**菊花图**，也能得知道最少路数是 $n-1$。我们也所以直接找出 $m$ 组点中不存在的点，在与其他与其不同的点，一一输出即可。


## code：

```cpp
#include<bits/stdc++.h>// 头文件件
using namespace std;// 使用命名空间
bool flag[10005];// 统计哪些点是m组点中出现过的与未出现过的。
int main(){// 主函数
	int n,m,s;
	cin>>n>>m;
	for(int i=1;i<=m;i++){// 统计
		int x,y;
		cin>>x>>y;
		flag[x]=1;
		flag[y]=1;
	}
	cout<<n-1<<endl;
	for(int i=1;i<=n;i++){
		if(!flag[i]){// 找出未出现过的点
			s=i;
			break;
		}
	}
	for(int i=1;i<=n;i++){// 输出
		if(i!=s){
			cout<<s<<" "<<i<<endl;
		}
	}
	return 0;//结束
}
```


望审核通过！

---

## 作者：_xbn (赞：2)

其实是道简单题，考察了菊花图的性质。

看到任意两个点距离不大于 $2$，我们就想到了菊花图。

由于有些边不能连，我们可以找到一个点，如果它能与其他任意点连边，那我们就把它作为菊花图的中心点，之后将所有点与它连一条边即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 50002;
int n, m, l, r, p, t, k, ans, sum, tot, cnt, a[N], b[N], c[N], to[N], nxt[N], head[N], g[1002][1002];
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
	{
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while('0' <= ch && ch <= '9')
	{
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
int main()
{
    n = read(); m = read();
    for(int i = 1; i <= m; i++)
    {
		int x = read(), y = read();
		g[x][y] = g[y][x] = 1;
    }
    for (int i = 1; i <= n; i++)
    {
    	bool flag = 0;
    	for (int j = 1; j <= n; j++)
    	{
    		if(g[i][j] == 1)
    		{
    			flag = 1;
    			break;
			}
		}
		if(!flag) 
		{
			t = i;
			break;
		}
	}
	cout << n - 1 << endl;
	for (int i = 1; i <= n; i++)
	{
		if(i != t) cout << t << " " << i << endl;
	}
    return 0;
}
```



---

## 作者：Edmundino (赞：1)

这题看着似乎有些难度，但是认真分析

就会发现一个神奇的东西

从样例入手：他给了你几幅图

正解确是一个菊花图

再看题目：“每两个城市的距离不超过2”

这不就是菊花图吗

边的的个数就是n-1

所以我们只要统计出没有出现过的数

然后输出这个数与其他的数

问题就漂亮的解决了

送上AC代码

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<iomanip>
#include<cmath>
#include<vector>
#include<queue>

using namespace std;

const int N=1050;

int n,m,a,b,v[N],s;

int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>a>>b;
		v[a]++;
		v[b]++;
	}
	int q;
	for(int i=1;i<=n;i++)
	{
		if(v[i]==0)
		{
			q=i;
			break;
		  }  
	}
	cout<<n-1<<endl;
	for(int i=1;i<=n;i++)
	{
		if(i!=q)
		  cout<<i<<" "<<q<<endl;
	}
}
```


---

## 作者：Lame_Joke (赞：0)

- ### 大体思路
	此题要求每一个点都能连到 $1$，并且让边数最小，每个点到 $1$ 的距离最短，那么不难想到，可以打一个菊花图，在菊花图中，一个点到另一个点的距离最大为 $2$，然后再看另一个要求，给出的 $a$ 和 $b$ 数组中的点不能互相连接，但是如果一个点作为一个菊花图的中心，那么就必定会与其他每一个点连接，所以 $a$ 和 $b$ 数组中的点不能作为菊花图的中心。所以标记不能作为中心的点，再挑一个能作为中心的点，将其与其他的所有点连接即可（在此之前要输出道路数量 $n-1$）要优先判断 $1$ 因为要求所有点离 $1$ 的距离最短。
    
- ### 具体实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
bool bz[1005];
int main()
{
	scanf("%d%d",&n,&m);
	int in;
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&in);
		bz[in]=1;
		scanf("%d",&in);
		bz[in]=1;
	}
	printf("%d\n",n-1);
	for(int i=1;i<=n;i++)
	{
		if(bz[i]==0)
		{
			for(int j=1;j<=n;j++)
			{
				if(i==j) continue;
				printf("%d %d\n",i,j);
			}
			break;
		}
	}
}

---

## 作者：Lian_zy (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF330B)

## 题目翻译
这题翻译有问题，详见[这个帖子](https://www.luogu.com/discuss/51851)。

正确的翻译应为：

给定 $n$ 个节点，你需要给他们连**最少**的边，使得每个任意两个节点之间都能经过最多两条边互相到达，另外还有 $m$ 个节点之间不能直接互相连边。

## 题目分析

首先图最少连边都为 $n - 1$，所以第一行输出 $n - 1$ 即可。

构造图也很简单，只需要找一个没有限制的节点然后把所有节点都连向它即可。

由于 $m \le \frac{n}{2} - 1$，最坏情况下输入的 $a_i,b_i$ 都不一样，一共限制了 $m \times 2 \le n$ 个，所以一定可以找到没有限制的节点。

就拿样例来举例子，节点 $1$ 连不了节点 $3$，我们就在剩下的里面选一个节点 $2$（$4$ 也行）。

然后把所有节点连向它，答案就为：

```
1 2
3 2
4 2
```

这道题就做完了。

---

## 作者：封禁用户 (赞：0)

由于每个点到另外任意一个点所经过的边数 $\le2$，所以显而易见，本题的图都是菊花图。

所以只需要从图中心的点到其他每一个点都连上边即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,u,v,rt,vis[1001];
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++)cin>>u>>v,vis[u]=vis[v]=1;//vis 用来寻找中心点
	for(int i=1;i<=n;i++)if(!vis[i]){rt=i;break;}//寻找中心点
	cout<<n-1<<'\n';
	for(int i=1;i<=n;i++)if(i!=rt)cout<<rt<<' '<<i<<'\n';//输出
	return 0;
}
```

---

## 作者：_shine_ (赞：0)

十分考察对数据的观察度，并且题面有较大问题，应该采纳[翻译里的第二篇](https://www.luogu.com.cn/discuss/51851)。

看完题目似乎毫无想法，因为任意两点距离小于等于 $2$，所以说显然用构造会较为困难。但是如果模拟几个数据就可以发现构造的国家是一棵树形结构并且在梳理后都连一个共同的点，所以立马想到菊花图。随后立马去分析数据 $m$，因为 $m<\frac{n}{2}$ 所以无论如何构造出来都会空出一个完全没有限制的点，这是只需要把这个点与其他所有的点连上即可。

[ac records](https://codeforces.com/problemset/submission/330/234718368)

---

## 作者：ZZZZZZZF (赞：0)

### Translation

翻译有亿点点问题

一个国家有 $n$ 个城市，之间没有道路。一天，国王决定修建一些连接城市的公路。他希望这些道路建设的方式是，每一个城市都可以通过最多两条道路从一个城市到另一个城市。有 $m (m < n / 2)$ 对城市之间不能建设道路。求最小道路数量并输出方案。数据保证始终有解。

### 思路

~~什么菊花图？没学过。~~

首先，要求最少路径数，结果一定是一棵树。如果结果不是一棵树，我们就可以通过删掉环中的一条边得到更优的结果。

要求树上任意两点间距离小于等于 $2$，显然，不能有深度为 $3$ 的点。即，一定存在一个与其他所有点距离为 $1$ 的根节点，也就是菊花图的根。

不知道菊花图怎么办呢？

观察条件 $m (m < n / 2)$，即使最差情况下 $m$ 对不能修路的城市互不相同，依然至少有 $1$ 座城市可以直接跟所有城市相连。设不能修路的城市为 $k$，即 $2m \le k < n$。

所以直接找出 $m$ 组点中不存在的点即可。

### Code:
```cpp
#include<bits/stdc++.h>
#define N 10010
#define M 10010
using namespace std;

int m,n,root;
int vis[N];

int main(){
    scanf("%d%d",&n,&m);
    for(int i = 1,u,v;i<=m;i++){
        scanf("%d%d",&u,&v);
        vis[u] = vis[v] = 1;
    }

    for(int i = 1;i<=n;i++) 
    	if(vis[i] == 0) root = i;
    
    printf("%d\n",n-1);
    for(int i = 1;i<=n;i++) 
    	if(root!=i) printf("%d %d\n",root,i);
    
    return 0;
}
```

建议降橙

---

## 作者：yingkeqian9217 (赞：0)

翻译有~~亿~~点问题QwQ。
## 前置芝士
**菊花图**：满足存在 $u$ 使得所有除 $u$ 以外结点均与 $u$ 相连的**树**称为菊花。(自行脑补）
## 题意
这里应该是有 $n$ 个点，$m$ 对点不能建边，让你构造一个点互相之间的距离 $\le$ 2的联通图。
## 分析
注意到，这里点的距离 $\le2$,显然最好不是使所有点都相连（距离全为 $1$），所以对于任意一对点 $u,v$，要么直接相连，要么经过中间点 $t$。
![](https://cdn.luogu.com.cn/upload/image_hosting/kqsvstx8.png)

此时，对于一个新点 $w$ 它不可能只与 $u,v$ 的一个连接，要么与 $t$相连——那么就不再要与其他点相连了,要么一起形成一个环——但是明显不是最佳答案，比 $f1$多加了一边。所以只能用第一种方式，对于图论敏感的人会发现，这以此类推后，不就是菊花图吗？

那么就简单了，因为菊花图的中心与其他所有点相连，所以不可能出现在 $m$ 个不可连的点对中。只要用一个 $b$ 数组记录是否有不可连的边，然后枚举点找到中心，最后直接输出总边数 $n-1$ 和边就好了。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=12900001;
int n,m;
bool b[maxn];//记录是否可能是中心
signed main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		b[x]=b[y]=1;//标记
	}
	for(int i=1;i<=n;i++)
	 if(!b[i]){//i为中心
	 	printf("%d\n",n-1);//输出边数
	 	for(int j=1;j<=n;j++)
	 	 if(j!=i)//注意特判qwq
	 	  printf("%d %d\n",i,j);
	 	break;
	 }
	return 0;
}

```

---

## 作者：Mars_Dingdang (赞：0)

本题翻译有误吧。其实认真读一下英文题面就很快能想到正确的构造方法了。
## 题目大意
给你 $n$ 个点，有 $m$ 个点对不能连边，且任意两个点最短路径不超过 $2$。你需要输出最少的边数，然后构造一种方案。

$n\le 10^3$，$m<\dfrac n 2$。

## 大体思路
首先，由于要求图连通，必然有答案边数 $ans\ge n-1$，当且仅当图构成一棵树时取等。

因此，我们只需考虑，对于任意的 $m$ 组点对，如何构造一棵树使得任意两节点距离不超过 $2$。

关注题目范围：$m<\dfrac n 2,n\ge 1$，因此有 $m<\lfloor\dfrac n 2\rfloor\le n-1$，即 $m<n-1$。由于 $m=n-1$ 时才可能通过构成一棵树使得任意两节点都不能连边，所以本题必然存在一个点 $s$，使得 $\forall u\in [1,n]$，$(s,u)$ 均可以连边。

此时构造方法就浮出水面了：使得图构成一颗以 $s$ 为根节点的[菊花图](https://oi-wiki.org/graph/tree-basic/)。此时，任意结点到根的距离为 $1$，任意两个非根节点距离为 $2$，满足要求。

## 完整代码
```cpp
#include<bits/stdc--.h>//抄袭有奖
using namespace std;
#define rep(ii,aa,bb) for(re int ii = aa; ii <= bb; ii++)
#define Rep(ii,aa,bb) for(re int ii = aa; ii >= bb; ii--)
typedef long long ll;
typedef unsigned long long ull;
const int manx = 1e3+5;
namespace IO_ReadWrite {
	#define re register
	#define gg (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1<<21, stdin), p1 == p2) ? EOF :*p1++)
	char buf[1<<21], *p1 = buf, *p2 = buf;
	template <typename T>
	inline void read(T &x){
		x = 0; re T f=1; re char c = gg;
		while(c > 57 || c < 48){if(c == '-') f = -1;c = gg;}
		while(c >= 48 &&c <= 57){x = (x<<1) + (x<<3) + (c^48);c = gg;}
		x *= f;return;
	}
	inline void ReadChar(char &c){
		c = gg;
		while(!isalpha(c)) c = gg;
	}
	template <typename T>
	inline void write(T x){
		if(x < 0) putchar('-'), x = -x;
		if(x > 9) write(x/10);
		putchar('0' + x % 10);
	}
	template <typename T>
	inline void writeln(T x){write(x); putchar('\n');}
}
using namespace IO_ReadWrite;//快读
int n,m,s;
bool vis[maxn];//标记哪个点可以作为根节点
int main(){
	read(n);read(m);
	rep(i,1,m){
		int u,v;
		read(u);read(v);//输入不能连的边
		vis[u]=vis[v]=1;
	}
	writeln(n-1);//树的边数
	rep(i,1,n){
		if(!vis[i]){//若该节点与所有节点均可连边，
			s=i;//则将其作为根节点
			break;
		}
	}
	rep(i,1,n){
		if(s^i) write(i),putchar(' '),writeln(s);
        //若不为根节点则连边
	}
	return 0;
}
```

---

