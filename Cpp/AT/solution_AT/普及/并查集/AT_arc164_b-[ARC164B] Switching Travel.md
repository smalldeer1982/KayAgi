# [ARC164B] Switching Travel

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc164/tasks/arc164_b

頂点に $ 1 $ から $ N $ までの番号がついた $ N $ 頂点の単純、連結な無向グラフがあります。 このグラフには $ M $ 本の辺があり、 $ i $ 番目の辺は $ 2 $ 頂点 $ a_i $ , $ b_i $ を結んでいます。

また、各頂点は白または黒の色を持ち、最初の状態が $ c_i $ で与えられます。 $ c_i $ は $ 0 $ または $ 1 $ であり、$ c_i=0 $ であれば頂点 $ i $ は初め白色であり、$ c_i=1 $ であれば頂点 $ i $ は初め黒色です。

あなたはこのグラフ上で、好きな頂点を $ 1 $ つ選んで出発点とし、

- 今いる頂点と辺で結ばれた頂点のうち、今いる頂点と異なる色の頂点に移動する。その直後に、移動元の頂点の色を反転する（元の色が白なら黒に、黒なら白に変える）。
 
という動作を好きな回数繰り返します。

$ 1 $ 回以上の動作を行ったうえで、再び出発点に戻ってくることは可能でしょうか。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ N-1\ \leq\ M\ \leq\ \mathrm{min}\ \lbrace\ 2\ \times\ 10^5,N(N-1)/2\ \rbrace $
- $ 1\ \leq\ a_i,\ b_i\ \leq\ N $ $ (1\ \leq\ i\ \leq\ M) $
- $ c_i=0 $ または $ c_i=1 $ $ (1\ \leq\ i\ \leq\ N) $
- 与えられるグラフは単純かつ連結である
- 入力される値はすべて整数である
 
### Sample Explanation 1

例えば、頂点 $ 1 $ から出発することを考えます。 最初の動作では、頂点 $ 2 $ に移動し、移動元である頂点 $ 1 $ の色を白から黒に変化させます。この際のグラフの変化は下の図の通りです（丸で囲った頂点が今いる頂点を表します）。 その後、頂点 $ 3 $, $ 4 $, $ 2 $ へと順に移動すると、この時点で頂点 $ 1,2,3,4 $ の色は順に黒、白、黒、白となっています。 したがって、次の動作で頂点 $ 1 $ に移動することができ、出発点に戻ってくることができました。 !\[\](https://img.atcoder.jp/arc164/69700c7a0d96daa9c93ad01b89530e53.png)

### Sample Explanation 2

このグラフでは、どの頂点を出発点に選んでも、条件を満たすような移動を行って出発点に戻ってくることができません。

## 样例 #1

### 输入

```
4 4
1 2
2 3
3 4
4 2
0 1 0 1```

### 输出

```
Yes```

## 样例 #2

### 输入

```
5 6
1 2
2 3
3 4
4 5
1 4
2 5
0 1 0 1 0```

### 输出

```
No```

# 题解

## 作者：zzk2010 (赞：4)

并查集判环是个好东西，代码很短，~~但我赛时脑抽没想出来~~。

## 分析

首先，如果能回到起点，那么肯定是走了一个环。

这是一个什么样的环呢？

我们设起点的颜色为黑色，那么下一个点的颜色一定和起点不一样，**这样才能走到下一个点**，所以下一个点的颜色是白色。那再下面一个点的颜色又是黑色了，以此类推。

那我们在外面兜兜转转了一圈，终究是要走回起点的。当你的下一步要走回起点时，起点的颜色已经被反转了，也就是说，此时起点的颜色是白色。那么，走向起点的这个点一定是黑色的，**这样才能走回起点**。

如果起点是白色的，那么同理，下一个点是黑色，再下一个点是白色……最后走向起点的这个点是白色的，最后走回起点。

所以，我们要找由一条**黑白相间，两端颜色一致**的链拼起来的一个环。

可以配合下图食用：

![](https://cdn.luogu.com.cn/upload/image_hosting/59qc8hj0.png)

那就可以用**并查集**维护。

### step1.把所有不同颜色的相邻的点在并查集中连边

如下图，这样就满足了**黑白相间**的要求。

![](https://cdn.luogu.com.cn/upload/image_hosting/duk9y8ey.png)

### step2.查询是否有相邻的，颜色一致且在同一连通块的两个点

如果有，就满足了**两端颜色一致**的要求。见下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/2lx2nr11.png)

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
struct edge { int u, v; } e[200005];
int n, m, fa[200005], c[200005];
bool ok;
//并查集基本操作
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { fa[find(x)] = find(y); }
int main() {
	cin >> n >> m;
	for(int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		e[i] = (edge){u, v};
	}
	for(int i = 1; i <= n; i++) cin >> c[i];
	for(int i = 1; i <= n; i++) fa[i] = i;       //并查集初始化 
	for(int i = 1; i <= m; i++) if (c[e[i].u] != c[e[i].v]) merge(e[i].u, e[i].v);                    //如果两个点相邻且不同色，连边 
	for(int i = 1; i <= m; i++) if (c[e[i].u] == c[e[i].v] && find(e[i].u) == find(e[i].v)) ok = 1;   //查询是否有相邻的，颜色一致且在同一连通块的两个点 
	if (ok) puts("Yes");
	else puts("No");
	return 0;
}
```

---

## 作者：Elairin176 (赞：4)

[传送门](https://www.luogu.com.cn/problem/AT_arc164_b)    
观察性质的题。   
## 题意
给你一张无向图，这张图的每个结点都有黑白两种颜色，第 $i$ 个结点的颜色为 $c_i$，$c_i=0$ 表示结点 $i$ 为白色，否则为黑色。    
我们先选定一个结点为起点，再可以执行以下的操作任意次：    
- 移动到和当前结点颜色不同的、有一条边连接的任意结点。在移动之后，原来的结点颜色反转。    

问你最后能不能有一个结点执行这些操作后回到这个结点。    
## 解法
实际上，所有有解的情况都可以归纳为下面一个模型：一个结点连接了一个和它颜色相同的点和一个不同的，且这两个点互相可达。        
那么这道题就变得很简单了：     
我们用一个并查集来表示图之间的联通关系。建边时如果两个结点的颜色不同就更新并查集，否则什么也不用做。    
我们如何判断结点连接的结点中是否有以上说的两种结点呢？我们可以设 $d_{i,j}$ 为第 $i$ 个结点上，状态为 $j$ 的结点是否存在。这里我们设 $j=0$ 为颜色相同，否则为不同。   
这一点我们建边的时候也能预处理出来。  
那我们又如何判断两个结点互相可达呢？答案是用一个 vector。我们设它为 $vec$，如果建边时，我们发现有颜色相同的，那么我们把这个点加入 $vec_i$ 中，$i$ 表示这条边上的结点，注意无向图要建两次。     
之后，我们再设 $mp$，$mp$ 用 unordered_map 实现，$mp_{i,j}$ 表示，第 $i$ 个结点是否连着一条边，边的另一端在并查集所属的集合为 $j$，是的话，为 $1$，否则为 $0$。**注意：这一步一定要在建图之后进行处理！**        
最后我们对 $1$ 到 $n$ 扫一遍，设扫到了 $n$。如果 $d_{i,0}=1,d_{i,1}=1$ 且我们在 $vec_i$ 中可以找到一个结点，它在 $mp$ 中也能被找到，那么最后的答案就是 `Yes`。如果到最后也没找到就是 `No`。      
时间复杂度是 $O(m\alpha(m))$ 的，$\alpha(m)$ 为一次并查集的复杂度。        
[CODE](https://www.luogu.com.cn/paste/g9giq1ub)

---

## 作者：yydfj (赞：2)

这是本蒟蒻第三十一次写的题解，如有错误点请好心指出！

## 问题简述

给定一个包含 $n$ 个点和 $m$ 条边的无向图，每个点的颜色要么是黑色，要么是白色。你可以选择一个点作为起点出发，沿着边走到下一个不同颜色的点，并且改变走之前的那个点的颜色。问在走的过程中是否存在一个起点，出发后还会回到这个点。

## 解法综述

首先我们要在图上找到一个环，因为如果我们要从点 $u$ 走到点 $v$，必须先满足这两点的颜色不同，而走了之后要改变点 $u$ 的颜色，此时这两点的颜色相同，也就意味着我们走了之后就不能往回走，只能通过走环来回到起点。

其次，假设这个环存在一条合法路径，那么这条路径一开始两端的颜色一定相同，因为在走的过程中起点的颜色会被改变，此时路径两端的颜色就不同了，也就意味着我们可以从一端走到另一端了。而且这条路径一开始相邻两点的颜色一定不同，因为我们要保证走到的下一个点必须是不同颜色的点。

于是我们可以在图中找出相邻的且颜色相同的两个点，看它们能否成为一条合法路径的两端。

## 代码描述
```cpp
#include<cstdio>
int n,m,nxt[400005],to[400005],h[200005],cnt;
int a[200005],b[200005],c[200005];
bool bz[200005],bj;//数组bz用来判环，防止被卡死
void add(int x,int y)
{
	nxt[++cnt]=h[x];
	to[cnt]=y;
	h[x]=cnt;
}
void dfs(int x,int fa,int y)
{
	if(x==y||bj)//如果存在两个点能成为一条合法路径的两端
	{
		bj=1;
		return;
	}
	for(int i=h[x];i;i=nxt[i])
	if(to[i]!=fa&&!bz[to[i]]&&c[x]!=c[to[i]])//要求这条路径中相邻两点的颜色不同
	{
		bz[to[i]]=1;
		dfs(to[i],x,y);//遍历该路径
		bz[to[i]]=0;
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a[i],&b[i]);
		add(a[i],b[i]);add(b[i],a[i]);//建图
	}
	for(int i=1;i<=n;i++) scanf("%d",&c[i]);
	for(int i=1;i<=m;i++)
	{
		if(c[a[i]]==c[b[i]]&&!bz[a[i]]&&!bz[b[i]])//找出相邻的且颜色相同的两个点
		{
			bz[a[i]]=1;
			dfs(a[i],b[i],b[i]);//看它们能否成为一条合法路径的两端
			bz[a[i]]=0;
		}
		if(bj)//如果存在两个点能成为一条合法路径的两端
		{
			printf("Yes");
			return 0;
		}
	}
	printf("No");
	return 0;
}
```

---

## 作者：Hog_Dawa_IOI (赞：2)

### 题意简述   
给定一个简单连通无向图，每个点上有一个颜色（非黑即白），现在使用以下规则进行移动，问能否从任意一个点出发，最后还能回到起点。    
-  移动到由当前顶点的边连接的不同颜色的顶点。移动后，立即反转移动顶点的颜色（如果是白色，则更改为黑色，反之亦然）。    
这里反转颜色的顶点是出来的那个点，即如果要从 $A$ 点移动到 $B$ 点，那么要改变 $A$ 点的颜色。    

------

### 算法分析
首先，不难看出我们只需要在环上判断就可以了。因为我们往前走时要一路上改变经过顶点的颜色，导致一路上身后所有的点都是同一个颜色，于是我们就无法掉头回去，必须通过一个环绕回去才能设法回到起点。（作者无法严谨证明，大家感性理解就好。）         
那么考虑是否可以在环上绕一圈。         
对于一条边的两个端点，如果它俩不同色，那么我们可以从其中一个点走到另一个点。于是我们可以考虑并查集，把这两个点合并在同一个集合内。到最后，检查每一条边，如果它的两个端点是同一个颜色的，并且在同一个集合内，那么我们就同样可以从其中一个点走到另一个点（当然不是通过这条边，而是通过另一条路）。  
为便于描述，设“其中一个点”为点 $A$，“另一个点”为点 $B$。当我们从点 $A$ 通过另一条路走到点 $B$ 时，点 $A$ 已经改变了一次颜色，也就是说点 $A$ 和点 $B$ 此时不同色，我们就可以从点 $B$ 走回点 $A$，从而回到起点。   
所以有了如下算法：    
1. 对于每条边，如果这条边的两个端点不同色，那么把这两个点所在的并查集的集合合并。
1. 再次访问每条边，如果一条边的两个端点同色并且它俩在同一个集合内，那么输出 `Yes`。  
1. 如果到最后都没有输出 `Yes`，那么输出 `No`。    


喜闻乐见的代码时间：
```cpp
#include<cstdio>
#include<vector>
using namespace std;
struct sss{long long end,next;}bian[400005];bool f[200005];
long long n,m,a[200005],b[200005],color[200005],first[200005],num,father[200005],high[200005];
long long fa(long long where)
{
    if(father[where]==where) return where;
    return father[where]=fa(father[where]);
}
void merge(int x,int y)
{
    if(father[x]==x&father[y]==y) father[x]=y,high[y]++;
    else if(father[x]!=x&father[y]==y) father[y]=fa(x);
    else if(father[x]==x&father[y]!=y) father[x]=fa(y);
    else merge(father[x],father[y]);
}
int main()
{
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=m;i++) scanf("%lld%lld",&a[i],&b[i]),
    bian[++num].end=b[i],bian[num].next=first[a[i]],first[a[i]]=num,
    bian[++num].end=a[i],bian[num].next=first[b[i]],first[b[i]]=num;
    for(int i=1;i<=n;i++) scanf("%lld",&color[i]),father[i]=i,high[i]=1;
    for(int i=1;i<=m;i++) if(color[a[i]]^color[b[i]]) merge(a[i],b[i]);
    for(int i=1;i<=m;i++) if(color[a[i]]==color[b[i]]&&fa(a[i])==fa(b[i])) {printf("Yes");return 0;}
    printf("No");
}
```

-----
### 复杂度分析    
操作一和操作二需要遍历每条边，对于每条边进行合并或查询操作，一次合并或查询操作时间复杂度为 $O(\log n)$，对于每条边都进行合并或查询操作，共 $m$ 条边，所以总的时间复杂度为 $O(m \log n)$，可以通过。      

在这里感谢[这位大佬](https://www.luogu.com.cn/user/808529)提供的思路，是他给我的思路帮助我一次就过了这道题，没吃罚时。    
完结撒花。

---

## 作者：DengDuck (赞：1)

想要无限走那不就是找环吗？那么我们设这个环为 $a_1\to a_2 \to ...\to a_n \to a_1$。

发现应该有以下性质：

- 对于 $i(2\leq i\leq n)$，$c_{a_i}\not =c_{a_{i-1}}$。
- 对于 $a_n\to a_1$ 而言，由于 $a_1$ 颜色变换，按照原颜色而言有 $c_{a_n}=c_{a_1}$。

我们根据这两个性质找环即可，可以考虑使用 DFS，时间复杂度为 $O(n)$。

其实本质上是看对于满足 $c_i=c_j$ 的边 $(i,j)$ 是否有另外的路径连接。

需要注意的细节是：我们不妨先只看所有颜色不同的边，组成一个个连通块，再单独看每个连通块即可。

其实用并查集应该会好一点。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=2e5+5;
LL n,m,x,y,c[N],vis[N],b[N];
vector<LL>v[N];
map<pair<LL,LL>,LL>ma;
void dfs(LL x,LL k)
{
	vis[x]=1;
	b[x]=k;
	for(LL i:v[x])
	{
		if(b[i]==b[x]&&c[i]==c[x])
		{
			puts("Yes");
			exit(0);
		}
		if(c[i]!=c[x]&&!vis[i])
		{
			dfs(i,k);
		}
	}
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>x>>y;
		v[x].push_back(y);
		v[y].push_back(x);
	}
	for(int i=1;i<=n;i++)
	{
		cin>>c[i];
	}
	for(int i=1;i<=n;i++)
	{
		if(!vis[i])dfs(i,i);
	}
	puts("No");
}
```

---

## 作者：Harrylzh (赞：0)

思路：如果目前再走一次可以返回原点，则此点和颜色翻转后的原点颜色不同，所以最开始此点和原点初始颜色相同。所以，只需要找到颜色相同且互相可达的点即可。

解法：考虑使用并查集。两个点如果颜色不相同，就可以互相到达。把可以互相到达的点都放入同一个并查集。再枚举每条边，如果这两个点满足上文条件，就直接输出 `Yes`。如果没有任何两点满足要求，则输出 `No`。

代码：
```cpp
#include<iostream>
using namespace std;
int fath[200000+5];
int get_father(int i)
{
    return fath[i]==i?i:fath[i]=get_father(fath[i]);
}
int n,m;
struct node
{
    int x;
    int y;
} l[200000+5];
bool a[200000+5];
int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        cin>>l[i].x>>l[i].y;
        fath[i]=i;
    }
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    for(int i=1;i<=m;i++)
    {
        int fx=get_father(l[i].x);
        int fy=get_father(l[i].y);
        if(a[l[i].x]!=a[l[i].y])
        {
            fath[fx]=fy;//存并查集
        }
    }
    for(int i=1;i<=m;i++)
    {
        int fx=get_father(l[i].x);
        int fy=get_father(l[i].y);
        if(a[l[i].x]==a[l[i].y]&&fx==fy)//判断
        {
            cout<<"Yes"<<endl;
            return 0;
        }
    }
    cout<<"No"<<endl;
    return 0;
}
```

---

## 作者：OldDriverTree (赞：0)

# Solution
可以发现，满足题目要求的路径必然是一个只有一条边两个端点同色，其他边端点不同色的一个环。

考虑先用并查集把两个端点不同色的边合并到一个连通块里。

再判断是否存在一条两个端点同色的边使得两个点在一个连通块里即可。

如果有，输出 `Yes`，否则输出 `No`。

# Code
```c++
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+1;
int n,m,a[N],fa[N];
struct edge { int x,y; }e[N];
int find(int x) { return fa[x]^x?fa[x]=find(fa[x]):x; }
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=0;i<m;i++) scanf("%d%d",&e[i].x,&e[i].y);
	for (int i=1;i<=n;i++) scanf("%d",a+i),fa[i]=i;
	for (int i=0;i<m;i++) if (a[e[i].x]^a[e[i].y]) fa[find(e[i].x)]=find(e[i].y);
	for (int i=0;i<m;i++) if (a[e[i].x]==a[e[i].y]&&find(e[i].x)==find(e[i].y) ) return puts("Yes"),0;
	return puts("No"),0;
}
```

---

## 作者：CrTsIr400 (赞：0)

# ARC164B 题解

这是本蒟蒻第 90 次写的题解，如有错误点请好心指出！

---

感觉和今年 NOIP 的 T2 很像，但是思维难度要高一些。可以到达主题库某些绿题的难度，但是代码难度很明显很低。

乍一看维护所有这些信息很复杂，也是不太能直接贪心的。但是，点本身的编号是无关紧要的，我们只关心每个点的颜色。

手玩一下样例，研究一下这个题目给定的操作，发现一个点被访问到且被翻转之后的访问序列，它的颜色是 0/1 交替的。

于是你会发现要形成一个解，就要有环，而长度为偶数的环是显然不行的，只有长度为奇数的环能够满足条件。而这个奇数环的末尾其实不是一个完整意义上的环，而需要满足末尾元素原来的值恰好等于起始元素开始的值。

为什么不用考虑从其它起点开始走一段环再回到起点的情况呢？因为按照题意操作，只要能走出环，就一定有解，就不用考虑再按照来时路走回去了。

于是简单并查集维护一下就行了，代码很简单。

```cpp
#include<bits/stdc++.h>
#define fo(i,a,b) for(I i(a),_ed(b);i<=_ed;++i)
using namespace std;using I=int;using LL=long long;using V=void;
const I N=2e5+10;
I main(){ios::sync_with_stdio(0);cin.tie(0);
	I n,m,f[N],c[N];
	cin>>n>>m;
	auto gf=[&](I x){for(;f[x]!=x;x=(f[x]=f[f[x]]));return x;};
	auto mrg=[&](I x,I y){x=gf(x);y=gf(y);if(x==y)return 0;
		return f[x]=y,1;};
	vector<array<I,2>>e(m);
	for(auto&i:e)cin>>i[0]>>i[1];
	fo(i,1,n)cin>>c[i],f[i]=i;
	for(auto&i:e)if(c[i[0]]!=c[i[1]])mrg(i[0],i[1]);
	for(auto&i:e)if(c[i[0]]==c[i[1]])if(gf(i[0])==gf(i[1]))return puts("Yes"),0;
	return puts("No"),0;}
```



---

## 作者：出言不逊王子 (赞：0)

不难发现我们只能按照 `0101` 这样的顺序去找点。

如果有奇数彩环当然是最好的，但是可能在没有的情况下也能爆出一个。

手玩样例发现在彩色偶环外面接一根同色棒子也能改判（也就是走完异色的后跨一步回到已经变色的起点，成功反转颜色）。

那么我们先把异色边给缩点，然后看有没有在同一边双内的同色边。

如果有的话，在绕一圈后往那个“同色边（此时一边已经被改变颜色了）”就可以改判，成功回家。

```cpp
//已删去暴戾语言注释
#include<bits/stdc++.h>
#define fs(i,x,y,z) for(int i=x;i<=y;i+=z)
#define ft(i,x,y,z) for(int i=x;i>=y;i+=z)
#define ll long long
#define ull unsigned long long
#define db double
#define ms(a,b) memset(a,b,sizeof(a))
#define sz(a) sizeof(a)
#define pii pair<int,int> 
#define mid (l+r>>1)
using namespace std;
const int rw[]={-1,0,1,0,-1,1,-1,1},cl[]={0,1,0,-1,-1,1,1,-1};
const int N=300001,inf=0x3f3f3f3f;
inline int read(){
	int date=0,w=1;char c=0;
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){date=date*10+c-'0';c=getchar();}
	return date*w;
}
//struct edge{int v,nx;}e[N<<1];
vector<pii> v;
int hd[N],totm,du[N];
int n,m,c[N],res[N],tot,vis[N],visd[N],fa[N];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
signed main(){
	n=read(),m=read();fs(i,1,m,1){
		int u=read(),vv=read();
	//	add(u,vv);add(vv,u);
		v.push_back({u,vv});
	}
	fs(i,1,n,1) fa[i]=i,c[i]=read();
	for(auto x:v) if(c[x.first]^c[x.second])fa[find(x.first)]=find(x.second);
	for(auto x:v)if(c[x.first]==c[x.second]) if(find(x.first)==find(x.second)) return puts("Yes"),0;
	puts("No");
	return 0;
}
//一个奇环可以调转状态
//你的任务就是找出这个环？****，彩环就可以了
//有没有其他方案？
//应该找奇环就可以了 
//奇数彩环？ 
//********，不是彩环根本走不了
//********
//彩色奇环没用
//只能******在外面再接一个奇环 
//所以充要条件是
```

---

## 作者：_Z_F_R_ (赞：0)

### 题意
给定一个无向图，要求从一个点出发，每次能到达与该点有边直接相连的点。每个点又有一个颜色，黑或白。走到一个点时，要求该点颜色与上一个点的颜色不同，同时要将上一个点的颜色由黑变成白，白变成黑。问是否能从一个点出发，再回到这个点。
### 思路
若一个点 $u$ 能返回到 $u$，当且仅当存在一个点 $v$，使得：

- 在原图中，$u$ 能走到 $v$，即存在互不相等的 $k_1,k_2,\cdots,k_t$，使得 $c_u \not = c_{k_1},c_{k_1} \not = c_{k_2},\cdots,c_{k_{t-1}} \not = c_{k_t},c_{k_t} \not = c_v$；
- $c_u = c_v$。

此时，可以先从 $u$ 走到 $v$，然后 $c_u$ 经过一次变换，使得 $c_u \not = c_v$，然后就可以从 $v$ 到 $u$ 了。
### 代码
考虑原图 $G$ 的一个子图 $G'$，若 $G'$ 的任意两个点，都能相互到达，那么这个子图就是“联通的”。

用 DFS 扩展这些“联通的”子图，对于每个子图再暴力枚举每个点及其连接的每个点，若这个点属于子图 $G'$，且两点颜色相同，那么输出 `Yes`，否则输出 `No`。

```
#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
int n,m,c[N];
struct Edge
{
    int to,nex;
}e[N * 2];
int cnt,head[N];
void Add_Edge(int a,int b)//加边
{
    e[++cnt] = {b,head[a]};
    head[a] = cnt;
}
vector<int> Get_Node(int x)//求一个点的所有相邻的点
{
    vector<int>v;
    int i = head[x];
    while(i != -1)
        v.push_back(e[i].to),i = e[i].nex;
    return v;
}
int path[N];
void dfs(int x,int path_num,int col)//DFS，扩展 G'
{
    path[x] = path_num;
    vector<int>v = Get_Node(x);
    for(auto node : v)
        if(c[node] != col && !path[node])
            dfs(node,path_num,c[node]);
}

int main()
{
    memset(head,-1,sizeof(head));
    scanf("%d %d",&n,&m);
    while(m--)
    {
        int u,v;
        scanf("%d %d",&u,&v);
        Add_Edge(u,v),Add_Edge(v,u);
    }
    int i,cnt_path = 0;
    for(i = 1;i <= n;i++)
        scanf("%d",&c[i]);
    for(i = 1;i <= n;i++)
        if(!path[i])//如果没搜过，则 DFS
            dfs(i,++cnt_path,c[i]);
    for(i = 1;i <= n;i++)//枚举点
    {
        vector<int>v = Get_Node(i);
        for(auto node : v)//枚举相邻点
            if(c[node] == c[i] && path[node] == path[i])
            {
                printf("Yes\n");
                return 0;
            }
    }
    printf("No\n");
}
```

---

