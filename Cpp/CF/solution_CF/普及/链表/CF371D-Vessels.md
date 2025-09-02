# Vessels

## 题目描述

There is a system of $ n $ vessels arranged one above the other as shown in the figure below. Assume that the vessels are numbered from 1 to $ n $ , in the order from the highest to the lowest, the volume of the $ i $ -th vessel is $ a_{i} $ liters.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF371D/f198564e53bb2ea5c99e17b823930a432879118f.png)Initially, all the vessels are empty. In some vessels water is poured. All the water that overflows from the $ i $ -th vessel goes to the $ (i+1) $ -th one. The liquid that overflows from the $ n $ -th vessel spills on the floor.

Your task is to simulate pouring water into the vessels. To do this, you will need to handle two types of queries:

1. Add $ x_{i} $ liters of water to the $ p_{i} $ -th vessel;
2. Print the number of liters of water in the $ k_{i} $ -th vessel.

When you reply to the second request you can assume that all the water poured up to this point, has already overflown between the vessels.

## 样例 #1

### 输入

```
2
5 10
6
1 1 4
2 1
1 2 5
1 1 4
2 1
2 2
```

### 输出

```
4
5
8
```

## 样例 #2

### 输入

```
3
5 10 8
6
1 1 12
2 2
1 1 6
1 3 2
2 2
2 3
```

### 输出

```
7
10
5
```

# 题解

## 作者：zzx0102 (赞：9)

求管理员给过。

首先这题的 50 分做法很简单，只需要一个一个往下找就可以了。

100 分做法：

我们不难发现有很多已经装满的沙漏，这些没用的沙漏如果跳过，那么时效会好很多。

所以可以用并查集，每次一个装满就把上一个直接连到下一个，就可以 AC 了。

比如说 $i$ 沙漏满了，就可以把 $i-1$ 的下一个设成 $i+1$，这样，当下一次我访问到 $i-1$ 时，它的下一个就是 $i+1$ 了，跳过了 $i$，节约了复杂度。

总复杂度 $O(n+m)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 200010;
int water[N], a[N], n, nxt[N];
int find(int x){return nxt[x] == x ? x : nxt[x] = find(nxt[x]);}
inline int read() //快读优化
{
	int x = 0; char ch = getchar();
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <='9') x = x * 10 + (ch ^ 48), ch = getchar();
	return x;
}
void add(int x) //均摊O(1)
{
	int y = read();
	int i;
	water[x] += y;
	while(x <= n && water[x] > a[x])
	{
		nxt[find(x - 1)] = find(x); //精华，跳过x节点
		i = find(x) + 1;
		water[i] += water[x] - a[x];
		water[x] = a[x];
		x = i;
	}
}
int main()
{
	n = read();
	for(int i = 1; i <= n; i++)
	{
		a[i] = read();
		nxt[i] = i;
	}
	int Q = read();
	while(Q--)
	{
		int op = read(), x = read();
		if(op == 1) add(x);
		if(op == 2) printf("%d\n", water[x]);
	}
	return 0;
}
```


---

## 作者：b6e0_ (赞：7)

题目链接：<https://www.luogu.com.cn/problem/CF371D>

介绍一个 $\mathcal O(m+n)$ 的并查集做法。

考虑优化暴力。发现如果一个沙漏满了后，在 $1$ 操作的循环中就不用看它了。这似乎可以优化暴力的时间复杂度。分析一下：在 $1\ u\ x$ 操作中，如果 $u$ 这个沙漏根本没被倒满，那么只循环了 $1$ 次；如果 $u$ 被倒满了，流到 $u+1$ 后没有满，那么循环了 $2$ 次，另外有 $1$ 个沙漏满了，也就是说以后不会再看了；如果流到 $u+1$ 也满了，流到 $u+2$ 没有满，那么循环了 $3$ 次，有 $2$ 个沙漏以后不会再看了。可以发现，每个 $1$ 操作会先循环一次，之后循环了多少次就会有多少个沙漏被倒满。而最多只有 $n$ 个沙漏会被倒满，所以如果有一种方法能做到一个沙漏被倒满之后一遍也不会看它，那么复杂度就是 $\mathcal O(m+n)$ 的。

考虑并查集，$x$ 的祖先是 $y$ 表示 $x$ 后第一个没有被倒满的节点是 $y+1$。这正好对应了并查集一开始将所有节点的祖先设置成它本身。对于一个 $1$ 操作，每次通过并查集求祖先的操作 $\mathcal O(1)$ 跳到它之后第一个没有被倒满的。如果循环到节点 $x$ 并且它被倒满了，那么对于所有将 $x$ 当做第一个没有满的沙漏的沙漏（即祖先是 $x-1$ 的沙漏），他们都应该被更新为 $x$ 的祖先，于是我们需要将 $x-1$ 合并到 $x$ 上。查询时直接输出答案即可。代码：
```cpp
#include<bits/stdc++.h>
using namepace std;
int a[200010],fa[200010],ans[200010];
inline int read()
{
	char c=getchar();
	int x=0;
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
	{
		x=(x<<3)+(x<<1)+c-'0';
		c=getchar();
	}
	return x;
}
int get(int x)
{
	if(fa[x]!=x)
		return fa[x]=get(fa[x]);
	return x;
}
int main()
{
	int n=read(),m,i,o,x;
	for(i=1;i<=n;i++)
	{
		a[i]=read();
		fa[i]=i;
	}
	m=read();
	while(m--)
	{
		o=read();
		x=read();
		if(o-1)
			printf("%d\n",ans[x]);
		else
		{
			ans[x]+=read();
			while(x<=n&&ans[x]>a[x])//如果水在x处溢出了就一直循环
			{
				fa[get(x-1)]=get(x);//将x-1合并到x上
				o=get(x)+1;
				ans[o]+=ans[x]-a[x];//下一个沙漏加上溢出的水
				ans[x]=a[x];
				x=o;
			}
		}
	}
	return 0;
}
```

---

## 作者：SunnyYuan (赞：6)

### 思路：

定义一个权值并查集，权值保存这个集合还可以存下多少水。

如果这个集合可以存放的水已经小于要装入的水，就将这个集合与下一个集合合并。

否则，直接把这个集合可以存放的水减去要装入的水的体积。

### 代码：

```

#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = 200010;

int n, m;
int fa[N];
LL g[N], b[N];

int find(int x) {
    if (x == fa[x]) return x;
    return fa[x] = find(fa[x]);
}

int merge(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx == fy) return fx;
    fa[fx] = fy;
    g[fy] += g[fx];
    return fy;
}

void init() {
    for (int i = 1; i <= n; i++) fa[i] = i;
}

void modify(int x, LL v) {
    x = find(x);
    while (true) {
        if (g[x] >= v || x >= n) break;
        x = merge(x, x + 1);
    }
    g[x] = max(0ll, g[x] - v);
}

void query(int x) {
    int fx = find(x);
    if (fx == x) cout << b[x] - g[x] << '\n';
    else cout << b[x] << '\n';
}

int main() {
    #ifdef DEBUG
    freopen("D:/Exercise/Test.in", "r", stdin);
    clock_t st, ed;
    cout << "===================START===================" << endl;
    st = clock();
    #endif

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> g[i], b[i] = g[i];
    init();
    cin >> m;
    int opt, a;
    LL b;
    for (int i = 1; i <= m; i++) {
        cin >> opt;
        if (opt == 1) { cin >> a >> b; modify(a, b); }
        else { cin >> a; query(a); }
    }

    #ifdef DEBUG
    ed = clock();
    cout << "====================END====================" << endl;
    cout << "Time:" << (ed - st) * 1.0 / CLOCKS_PER_SEC << " sec" << endl;
    #endif
    return 0;
}
```

---

## 作者：zt17 (赞：3)

# [CF371D Vessels](https://www.luogu.com.cn/problem/CF371D)  题解

## 题目大意
给定 $n$ 个从上往下排列的沙漏，其中第 $i$ 个沙漏的容量为 $a_i$。接下来进行 $m$ 次操作，有两种操作：

`1 u x` : 将第 $u$ 个沙漏中加入 $x$ 的水，如果已被装满那就将溢出部分加入至第 $u + 1$ 的沙漏去。（可以理解为沙漏溢出的水自由落体流进下面的沙漏。

`2 u` : 输出第 $u$ 个沙漏中存放了多少水。

## 分析过程
我们可以建立两个数组分别存储每个杯子的容量和每个沙漏装了多少水，然后直接暴力求解，此算法可以拿到部分分，但会 TLE，因此我们进行优化。  

如果你对写出来的代码进行观察，会发现主要耗时在当水满了的时候向下搜索时的操作，所以我们可以在建立一个数组，存储每个沙漏下面第一个非空的沙漏的位置，倒入此沙漏的水就可以直接加在下面的沙漏里面。

分析完毕。

## 完整代码
```cpp
#include<bits/stdc++.h>
#define IOS cin.tie(0), ios::sync_with_stdio(false)
using namespace std;
typedef unsigned long long  ull;

const int N = 1e6 + 10;

int n, m;
int a[N]; // 每个杯子的容量
int ne[N]; // 指向每个杯子的右边第一个没有满的指针
int use[N]; // 每个杯子装了多少水

int main() {
	IOS;
	cin >> n;
	// 读入数据，初始化ne数组
	for(int i = 1 ; i <= n ; i ++) cin >> a[i], ne[i] = i + 1;
	cin >> m;
	while(m --) {
		int op, u, x;
		cin >> op >> u;
		if(op == 1) {
			cin >> x;
			// 从now开始加水
			int now = u;
			while(ne[now]) {
				// c表示当前杯子最多能加多少水
				int c = min(x, a[now] - use[now]);
				use[now] += c;
				x -= c;
				
				if(a[now] != use[now]) break;
				now = ne[now];
			}
			int t;
			// 把从u开始加，加满了的所有杯子的下一个指向now
			while(u != now) t = u, u = ne[u], ne[t] = now;
		} else cout << use[u] << "\n";
	}
}
```

~~管理大大求过QAQ~~

---

## 作者：Lijunzhuo (赞：2)

[原题传送门](https://www.luogu.com.cn/problem/CF371D)  
这道题用模拟会超时，所以我们要用一种更快的方法。  
找规律后我们发现当这个沙漏里的水满的时候，水只会往下流，这个沙漏里的水因为是满的所以水量是不会变的，每次加水一定会流到一个位置或流到地板上。  
所以我们可以用并查集来解决这道题。  
并查集是什么？  
**并查集是一种树型的数据结构，用于处理一些不相交集合的合并及查询问题。**  
我们可以开一个数组 $A$，用于维护存储当这个沙漏中水溢出的时候会漏到的最终位置。   
在开两个数组 $T$、$S$，分别表示目前这个沙漏存储的水的数量和这个沙漏最大可存储的水的数量。  
### 做法：
1. 初始化：  
数组 $A$ 的第 $i$ 项存储 $i+1$ 表示目前这个沙漏溢出后水会溢出到下一个沙漏内。
2. 加水操作：  
把 $T$ 的第 $i$ 项加上水的重量。
3. 溢出操作（重点！！！）：  
若超出这个沙漏最大可存储的水的数量 $S_i$，用维护好的数组 $A$ 进行加水操作，数组 $A$ 维护的值也会溢出的话继续使用数组 $A$ 进行加水操作，直到水无溢出或流到地板上。最后更新数组 $A$ 的值即可。  
4. 查询操作：  
直接输出 $T$ 的第 $i$ 项即可。

最后，别忘了用快读快写。  
用并查集时间复杂度为 $O(n+m)$。  

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int n,m,A[N],nextt[N],B[N],op,a,b;
int add(int trough,int water)
{
	B[trough]+=water;
	if(B[trough]>A[trough])
	{
		nextt[trough]=add(nextt[trough],B[trough]-A[trough]);
		B[trough]=A[trough];
		return nextt[trough];
	}else return trough;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		nextt[i]=i+1;
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]);
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&op,&a);
		if(op==1)
		{
			scanf("%d",&b);
			add(a,b);
		}else printf("%d\n",B[a]);
	}
	return 0;
}
```

---

## 作者：scc36 (赞：1)

[原题跃迁窗口](https://www.luogu.com.cn/problem/CF371D)   
本蒟蒻代码较复杂，勿抄。
### 解析  
本体的正确做法其实就是链表，但由于用链表具有很大的不确定性（尤其在上机考试中），所以不能直接用。     
但并非一定就要用并查集，我们可以不用指针，纯模拟，模出链表，模出 AC。
### 思路
就像链表一样，数组中有三样东西：数值，前面的“大哥”，后面的“小弟”。   
一个沙漏如果满了，就把多余的放到“小弟”那儿。因为这个沙漏已经满了，所以它也就“失去了价值”，“大哥”就把它的“小弟”当成自己的“小弟”，“小弟”就把它的“大哥”当成了自己的大哥。     
~~这纯属黑帮内斗。~~   
此外，还需要一点点小小的优化。  
如果将上述内容全部放在 while 中，就会超时。而如果将头指针（“大哥”）和尾指针（“小弟”）放在 while 外面，就可以减少一些时间。
### 程序
```cpp
#include <bits/stdc++.h>     //万能头
using namespace std;
int n,m,i,x,y,z,a[200001],yy,s;  //定义
struct no{            //定义一个结构体 b 
	int a,        t,      w; 
  //   数值（水量） “大哥”  “小弟”
}b[200002];
int main(){
	ios::sync_with_stdio(0);  //有趣的加速代码
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(i=1;i<=n;i++) cin>>a[i],b[i].t=i-1,b[i].w=i+1;      //确定“大哥”和“小弟”
	cin>>m;
	for(i=1;i<=m;i++){
		cin>>x;
		if(x==1){
			cin>>y>>z;
  			s=0;    //默认没有溢出（不会有水流到下一层）
			yy=y;   //保存初始位置
			b[y].a+=z; //倒水
			while(b[y].a>=a[y]&&y!=n+1){   //溢出了，并且没有越界
				b[b[y].w].a+=b[y].a-a[y];  //把多余的水加到“小弟”那里去
				b[y].a=a[y];      //水量变成正常值
				y=b[y].w;        //找到“小弟” 
				s=1;           //我来过（至少溢出过一次）
			}
			if(s){            //如果溢出过，也就是说明有人要在“内斗”中“死去”
				b[y].t=b[yy].t;   //“小弟”认“大哥”
				b[yy].w=y;      //“大哥”认“小弟”
			}
		}
		if(x==2){
			cin>>y;
			cout<<b[y].a<<"\n";  //输出
		}
	}
}
```
求通过……

---

## 作者：TheShuMo (赞：1)

## 分析

~~题目应该都看的懂吧~~

首先，很容易能够想到，对于每一次倒水的情况，如果这个沙漏并没有装满，则可以不断向下遍历以找到其下第一个没有装满水的沙漏，然后把水倒在里面，如果还有剩余则继续向下遍历。

上述方法大概是 $O(n^2)$ 的复杂度，明显不能通过此题。

考虑怎么优化来加快找到下一个沙漏的时间。

可以想到（题目标签），维护一个 $fa$ 数组，$fa$ 表示第 $i$ 个沙漏下方第一个没有盛满水的沙漏的编号。	
用并查集使每一个 $x$ 的父亲是它下面第一个没装满水的沙漏就好了。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long

namespace IO {
    #define int long long 
    #define gh getchar
    inline int read(){char ch=gh();int x=0;bool t=0;while(ch<'0'||ch>'9')   t|=ch=='-',ch=gh();while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=gh();return t?-x:x;}
    inline char getc(){char ch=gh();while(ch<'a'||ch>'z') ch=gh();return ch;}
    inline void write(int x){if(x < 0){putchar('-');x = -x;}if(x > 9){write(x / 10);}putchar((x % 10 + '0'));}
}
using namespace IO;
using namespace std;
const int Maxn = 210010;
int fa[Maxn];
int zl[Maxn];
int a[Maxn];
int n;int temp;
int find(int x){
    if(fa[x] != x) return fa[x] = find(fa[x]);
    return x;
}
void adw(int x){
    int k = read();
	int nxt;
	zl[x] += k;
	for(;x <= n && zl[x] > a[x];){
		fa[find(x - 1)] = find(x); // x-1的下一个
		nxt = find(x) + 1;
		zl[nxt] += zl[x] - a[x];
		zl[x] = a[x]; // 到达上限，赋值为 a[x]。
		x = nxt; // 不断向下遍历。
 	}
}
signed main(){
	n = read();
	for(int i = 1; i <= n; i++){
		a[i] = read();
		fa[i] = i; // 并查集初始化，父亲为自己。
	}
	int q = read();
	for(int i = 1;i <= q; i++){
	    int cz = read();
	    int x = read();
	    if(cz==1)adw(x);
	    if(cz==2)cout<<zl[x]<<endl;
	}
	return 0;
}

```


---

## 作者：OIer_ACMer (赞：0)

~~谁说这道题要用链表做的！！！~~

------------
## 警钟敲烂：
这道题一开始想用链表水过去，结果在外网 TLE 了 $8$ 个点，所以，链表不是万能的！！！

------------
## 大致思路：
本题考察的是并查集的活学活用，根据题目要求，我们可以想象一个事情：假如我现在在往第 $k$ 个漏斗里注水，是不是就意味着我在向对**大于等于** k **的没装满水的沙漏注水**？因为我们可以知道，当一个沙漏被装满时，它的水就会流到大于它的编号的沙漏里面去，所以当我给 $k$ 个沙漏装水时，**我就已经给下面的沙漏准备好了水**。

综上所述，如果第 $k$ 个盘子注满水后，我们可以把 $k$ 和 $k + 1$ 个盘子合并起来，这样对 $k$ 操作就是直接对大于等于 $k$ 的盘子进行操作了。

最终，在计算答案时，我们只需要判断如果 $\operatorname{find}(x) > n$，则说明水已经溢出至地面，所有的沙漏均已装满。直接结束循环即可。

------------
## 代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
const int N = 2e5 + 50;
const int inf = 0x3f3f3f3f;
int a[N], fa[N], v[N];
int n, q;
int find(int x)
{
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
void merge(int x, int y)
{
    int t1 = find(x);
    int t2 = find(y);
    fa[t1] = t2;
}
void init()
{
    for (int i = 1; i <= n + 2; i++)
    {
        fa[i] = i;
    }
}
int main()
{
    n = read();
    init();
    for (int i = 1; i <= n; i++)
    {
        v[i] = read();
    }
    memset(a, 0, sizeof a);
    q = read();
    while (q--)
    {
        int op;
        op = read();
        if (op == 1)
        {
            int k, c;
            k = read();
            c = read();
            while (c)
            {
                k = find(k);
                if (k > n)
                {
                    break;
                }
                if (a[k] + c >= v[k])
                {
                    c -= (v[k] - a[k]);
                    a[k] = v[k];
                    merge(k, k + 1);
                }
                else
                {
                    a[k] += c;
                    c = 0;
                }
            }
        }
        else
        {
            int k;
            k = read();
            cout << a[k] << endl;
        }
    }
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/121550320)

---

## 作者：MuYC (赞：0)

#### 前言

这道题的常规写法大概有：链表，线段树。

我做的时候什么也没想，就直接线段树干就完了.....因为我没有脑子......

但是实际上可以用链表做到复杂度 O($n$) 级别。

#### 具体做法

+ 1.**线段树**

线段树做法需要支持的操作为：

区间覆盖，单点修改，区间查询，单点查询。

这道题目的难点就在于怎么样维护水一直往下面流。那么我们可以想到**二分**来判断水会流满哪一些沙漏，然后对于这段区间实行**区间覆盖**，用一个**前缀和（前缀和里面存的是容量的前缀和)） + 区间查询目前水量区间和**来辅助**二分**。最后我们发现会剩下一点水无法注满下一个漏斗，然后采用**单点修改**，将水注入不能注满的沙漏即可即可。

对于询问就直接单点查值即可。

#### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
char buf[1 << 22],*p1 = buf,*p2 = buf;
#define mid ((L[x] + R[x]) >> 1)
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf , 1 , 1 << 21 , stdin),p1 == p2) ? EOF: *p1++)
inline int read() {
    int x = 0 , flag = 1;
    char ch = getchar();
    for( ; ch > '9' || ch < '0' ; ch = getchar()) if(ch == '-') flag = -1;
    for( ; ch >= '0' && ch <= '9' ; ch = getchar()) x = (x << 3) + (x << 1) + ch - '0';
    return x * flag;
}

typedef long long LL;
const int MAXN = 2e5 + 50;
int n,m;
int A[MAXN],S[MAXN];//A存容量，S存容量的前缀和

struct SegmentTree {
    LL sum[MAXN << 2],laz[MAXN << 2],L[MAXN << 2],R[MAXN << 2];
    void build(int x,int l,int r) {
        sum[x] = laz[x] = 0;
        L[x] = l , R[x] = r;
        if(l == r) return ;
        build(x << 1 , l , mid);
        build(x << 1 | 1 , mid + 1 , r);
        return ;
    }

    void ad(int x,LL k) {
        laz[x] = 1;
        sum[x] = S[R[x]] - S[L[x] - 1];//全部注满
        return ;
    }

    void changepos(int x,int pos,int k) {
        if(pos > n) return ;
        if(L[x] == R[x] && L[x] == pos) {
            sum[x] += k; return;
        }
        pushdown(x);
        if(pos <= mid) changepos(x << 1 , pos , k);
        if(pos  > mid) changepos(x << 1 | 1 , pos , k);
        sum[x] = sum[x << 1] + sum[x << 1 | 1];
        return ;
    }

    void change(int x,int l,int r,LL k) {
        if(l > r) return ;
        if(L[x] >= l && R[x] <= r) {
            ad(x,k); return ;
        }
        if(l <= mid) change(x << 1 , l , r , k);
        if(r  > mid) change(x << 1 | 1 , l , r , k);
        sum[x] = sum[x << 1] + sum[x << 1 | 1];
        return ;
    }

    void pushdown(int x) {//下传标记
        if(laz[x] == 0) return ;
        ad(x << 1 , laz[x]);
        ad(x << 1 | 1 , laz[x]);laz[x] = 0;
        return ;
    }

    int GetVal(int x,int l,int r) {
        if( l > r) return 0;
        int s = 0;
        if(L[x] >= l && R[x] <= r) return sum[x];
        pushdown(x);
        if(l <= mid) s += GetVal(x << 1 , l , r);
        if(r  > mid) s += GetVal(x << 1 | 1 , l , r);
        return s;
    }
} T;

int check(int u,int val) {//二分找出可以注满的沙漏的区间右端点
    int s = u - 1;//注意这个地方初值要写成u-1
    for(int i = log2(n - u + 1) ; i >= 0 ; i --) {
        int C = s + (1 << i);
        if(C > n) continue;
        if(val >= (S[C] - S[u - 1] - T.GetVal(1,u,C))) s += (1 << i);//二分
    }
    return s;
}

signed main() {
    n = read();
    for(int i = 1 ; i <= n ; i ++) A[i] = read(),S[i] = S[i - 1] + A[i];
    m = read();
    T.build(1 , 1 , n + 1);
    while(m --) {
        int op = read(),u,x;
        if(op == 1) {
            u = read() , x = read();
            int l = u , r = check(u,x),val = x - (S[r] - S[l - 1] - T.GetVal(1,l,r));
            //val代表的是剩下的水
            T.change(1, l, r, 1);//区间覆盖
            T.changepos(1,r + 1,val);//单点修改
        }
        else {
            u = read();
            cout << T.GetVal(1,u,u) << endl;
        }
    }
    return 0;
}
```

+ 链表

第一篇题解讲得很详细，这里我就不展开讲了。

大概思路：

链表里存的是下一个没有被装满的水桶。初始值即为 $nxt[i] = i + 1$，当一个水桶被装满的时候，我们每次跳其$nxt[]$ 即可，这样子跳下去，直到跳到水没了，然后再更新路径上的 $nxt$ 数组。这个方法不难发现均摊下来是 O($n$) 的。代码短了不止一点点，快了不止亿点点。

#### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
char buf[1 << 22],*p1 = buf,*p2 = buf;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf , 1 , 1 << 21 , stdin),p1 == p2) ? EOF: *p1++)
inline int read() {
    int x = 0 , flag = 1;
    char ch = getchar();
    for( ; ch > '9' || ch < '0' ; ch = getchar()) if(ch == '-') flag = -1;
    for( ; ch >= '0' && ch <= '9' ; ch = getchar()) x = (x << 3) + (x << 1) + ch - '0';
    return x * flag;
}

typedef long long LL;
const int MAXN = 2e5 + 50;
int n,m;
int A[MAXN],nxt[MAXN],N[MAXN];

signed main() {
    n = read();
    for(int i = 1 ; i <= n ; i ++) A[i] = read(),nxt[i] = i + 1;
    m = read();
    while(m --) {
        int op = read(),u,x;
        if(op == 1) {
            u = read() , x = read();
            int now = u;
            while(nxt[now]) {
                if(x + N[now] >= A[now]) x -= (A[now] - N[now]), N[now] = A[now];
                else {N[now] += x ; break;}
                now = nxt[now];
            }
            int t;
            while(u != now) t = u , u = nxt[u] , nxt[t] = now;
        }
        else {
            u = read();
            cout << N[u] << endl;
        }
    }
    return 0;
}
```

#### 总结

以后一定要动脑子思考问题，不要一上来就打暴力，这个习惯不好......


---

## 作者：Kirisame_Marisa_ (赞：0)

考虑一个十分naive的暴力：  
- 直接维护每一个容器中的水量
- 对于操作1，我们直接加水，如果水溢出了就执行`downflow`操作，暴力向下遍历所有容器
- 对于操作2，我们直接输出对应的水量

发现此时瓶颈在`downflow`操作上，每次溢出我们最坏要遍历$O(n)$个容器才能完成。

通过一些细致的观察，可以发现如果容器$i$中的水溢出了，那么溢出的这一部分影响到的第一个容器应该是$i$下方第一个没有满的容器。暴力的做法是每次一个一个遍历容器，显然它运作十分缓慢。

考虑对于第$i$个容器，维护它下方第一个没有满的容器$nxt_i$。开始的时候$nxt_i=i+1$，那么每次执行`downflow`时我们只要检查$nxt_i$是否会溢出，会的话则递归执行`downflow`，更新$nxt_i=nxt_{nxt_i}$。

这么做看起来每次`downflow`最坏还是$O(n)$的，好像没变？  
分析时间复杂度。首先$nxt$数组有一个性质：这里面的每个元素只会变大，不会变小。  
其次我们会发现，如果一次操作中$nxt_i$的值增加了$d$，那么这次`downflow`操作最多遍历了$d+1$个容器。因为有的时候，如果`downflow`过程中发现$nxt_u=n+1$，此时$nxt_i$到$nxt_u$都会变成$n+1$，而这种变化根据性质，最多发生$n$次，也就是此时的`downflow`是均摊$O(n)$的。  
根据$nxt$数组的定义，也因为`downflow`操作是递归执行的，所以如果一次操作中$nxt_i$的值增加了$d$，那么一直到$nxt_n$为止，这些位置上的$nxt$值一定不会小于$nxt_i$。而这些更新都是在同一次`downflow`操作中完成的。  
最后，因为$nxt_1$的初值为$2$，它最多变大到$n+1$，也就是说我们最多会遍历$O(n)$个容器，整个$nxt$数组就全部等于$n+1$，不会再发生变化了。

所以，最终的复杂度是均摊$O(n)$的。

[code](https://www.luogu.org/paste/ss363pfs)

---

