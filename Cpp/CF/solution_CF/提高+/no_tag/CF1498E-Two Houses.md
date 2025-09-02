# Two Houses

## 题目描述

This is an interactive problem. Remember to flush your output while communicating with the testing program. You may use fflush(stdout) in C++, system.out.flush() in Java, stdout.flush() in Python or flush(output) in Pascal to flush the output. If you use some other programming language, consult its documentation. You may also refer to the guide on interactive problems: <https://codeforces.com/blog/entry/45307>.

There is a city in which Dixit lives. In the city, there are $ n $ houses. There is  exactly one directed road between every pair of houses. For example, consider two houses A and B, then there is a directed road either from A to B or from B to A but not both. The number of roads leading to the $ i $ -th house is $ k_i $ .

Two houses A and B are bi-reachable if A is reachable from B and B is reachable from A. We say that house B is reachable from house A when there is a path from house A to house B.

Dixit wants to buy two houses in the city, that is, one for living and one for studying. Of course, he would like to travel from one house to another. So, he wants to find a pair of bi-reachable houses A and B. Among all such pairs, he wants to choose one with the maximum value of $ |k_A - k_B| $ , where $ k_i $ is the number of roads leading to the house $ i $ . If more than one optimal pair exists, any of them is suitable.

Since Dixit is busy preparing CodeCraft, can you help him find the desired pair of houses, or tell him that no such houses exist?

In the problem input, you are not given the direction of each road. You are given — for each house — only the number of incoming roads to that house ( $ k_i $ ).

You are allowed to ask only one type of query from the judge: give two houses A and B, and the judge answers whether B is reachable from A. There is no upper limit on the number of queries. But, you cannot ask more queries after the judge answers "Yes" to any of your queries. Also, you cannot ask the same query twice.

Once you have exhausted all your queries (or the judge responds "Yes" to any of your queries), your program must output its guess for the two houses and quit.

See the Interaction section below for more details.

## 说明/提示

In the first sample input, we are given a city of three houses with one incoming road each. The user program asks one query: "? 1 2": asking whether we can reach from house $ 1 $ to house $ 2 $ . The judge responds with "Yes". The user program now concludes that this is sufficient information to determine the correct answer. So, it outputs "! 1 2" and quits.

In the second sample input, the user program queries for six different pairs of houses, and finally answers "! 0 0" as it is convinced that no two houses as desired in the question exist in this city.

## 样例 #1

### 输入

```
3
1 1 1
Yes```

### 输出

```
? 1 2
! 1 2```

## 样例 #2

### 输入

```
4
1 2 0 3
No
No
No
No
No
No```

### 输出

```
? 2 1
? 1 3
? 4 1
? 2 3
? 4 2
? 4 3
! 0 0```

# 题解

## 作者：platelett (赞：16)

### 此题无需询问，可以线性求出所有强连通分量。
> [题目链接](https://codeforces.com/contest/1498/problem/E) [可能更好的体验](http://coding-pages-bucket-3532178-8430896-13917-522304-1305159063.cos-website.ap-hongkong.myqcloud.com/CF1498E/)
>
> 有一张 $n$ 个点的竞赛图。
>
> 不会给这张竞赛图，但会给每个点的入度 $k_i$。
>
> 还可以**通过交互**询问从 $u$ 能否到达 $v$，但一旦回答了”是“，就不能再询问了。
>
> 定义一个点对 $(u,v)$ 的价值是 $|k_u-k_v|$。
>
> 求所有双向可达的点对中价值最大的一对，或者输出无解。如果有多对，输出任意一对。
>
> $n \le 500$

考虑拓扑序最小的几个**强连通分量**的并集 $S$，$S$ 内的点全部向 $S$ 外的点连边，所以 $S$ 内所有点的入度和等于 $\binom {|S|}2$，**反之亦然**。

> 引理：在竞赛图中，如果 $u$ 能到达 $v$ 而 $v$ 不能到达 $u$，即 $u$ 的拓扑序严格小于 $v$，那么 $k_u < k_v$
> 
> 证明：如果 $v$ 不能到达 $u$，$\exists S,u \in S \land \forall x \in S, y \not \in S,x \rightarrow y$，即集合 $S$ 内的点全部向 $S$ 外的点连边。
> 
> $\therefore k_v \ge |S|,k_u < |S| \Rightarrow k_u < k_v$

把所有点按入度从小到大排序，如果前 $m$ 个节点的入度和等于 $\binom m2$，那么前 $m$ 个点一定是拓扑序最小的几个强连通分量的并集，**并且不会漏掉**，这样就可以分离出所有的强连通分量，直接统计答案即可。

复杂度 $O(n)$，因为排序可以桶排，**无需询问**。

代码：

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for(int i = (l); i <= (r); i++)
#define per(i, r, l) for(int i = (r); i >= (l); i--)
#define mem(a, b) memset(a, b, sizeof a)
#define For(i, l, r) for(int i = (l), i##e = (r); i < i##e; i++)
#define fi first
#define se second
#define mp make_pair

using namespace std;
const int N = 505;
typedef pair <int, int> P;
int n; P a[N];
int main() {
	cin >> n;
	rep(i, 1, n) scanf("%d", &a[i].fi), a[i].se = i;
	sort(a + 1, a + n + 1);
	int su = 0; P mi(n, 0), ma(-1, 0);
	pair <int, P> as;
	rep(i, 1, n) {
		su += a[i].fi;
		mi = min(mi, a[i]), ma = max(ma, a[i]);
		if(su == i * (i - 1) / 2) {
			if(mi.se ^ ma.se) as = max(as, mp(ma.fi - mi.fi, mp(mi.se, ma.se)));
			mi.fi = n, ma.fi = -1;
		}
	}
	if(as.se.fi) printf("! %d %d\n", as.se.fi, as.se.se);
	else puts("! 0 0");
	fflush(stdout);
	return 0;
}
```

---

## 作者：E_huan (赞：4)

或许算是性质题。

性质：若 $x$ 的出度大于 $y$ 的出度，则 $x$ 可以到达 $y$。（本题给的是入度，但竞赛图任何点都和其它所有点有且只有一条边，所以出度就是  $(n-1)-入度$）。

前置性质：竞赛图缩点后一定是一条链。（~~读者不难自证~~ 若缩完点后若 SCC 个数不超过 $2$，显然成立。否则对于缩完点后的任意 $3$ 个 SCC  $x$，$y$，$z$，按照竞赛图的定义它们之间两两有边，而其不属于同一个 SCC 即这三条边不构成环，则只能是 $x \rightarrow y$，$x\rightarrow z$，$y\rightarrow z$（$y\rightarrow z$，$y\rightarrow z$，$x\rightarrow z$ 这类是一样的）的链的形式）

若 $x$ 和 $y$ 在同一个 SCC 中显然成立。否则缩点后拓扑排序，（假设入度为 $0$ 的 SCC 为链顶，深度为 $0$），由于它们不是同一个 SCC ，深度小的 SCC 可以通过链上边到达深度大的 SCC ，则深度更大的 SCC 一定没有边指向深度小的 SCC 。而任意两个点之间都有有向边，则任意一个点 $x$ 有指向任意深度大于 $x$ 所在 SCC 的 SCC 中的点的边。则对于不在同一个 SCC 里的点，出度更大的点所在 SCC 深度更小，必定能到达深度更大的 SCC 里的点。

由性质可知，出度大，即本题中入度 $k$ 小的点，必定能到达出度小（入度大）的点，所以两个点能否双向到达只需要知道出度较小（入度较大）的点能否到达另一个点即可。把所有点对按照 $k$ 值的差值从大到小排序，按顺序询问，每次询问这对点中出度较小（入度较大）的点能否到达另一个点，只要获得 `Yes` 回答就输出当前询问的点对即可。

代码实现：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=550;
int n,tot,k[N];//k是入度
struct node
{
    int x,y;
    bool operator<(const node &t)const
    {
        return abs(k[x]-k[y])>abs(k[t.x]-k[t.y]);
    }
}p[N*N];
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>k[i];
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            p[++tot]={i,j};
    sort(p+1,p+tot+1);
    for(int i=1;i<=tot;i++)
    {
        int x=p[i].x,y=p[i].y;
        if(k[x]<k[y]) swap(x,y);
        cout<<"? "<<x<<' '<<y<<endl;
        string ch; cin>>ch;
        if(ch=="Yes") 
        {
            cout<<"! "<<x<<' '<<y<<endl;
            return 0;
        }
    }
    cout<<"! 0 0"<<endl;
    return 0;
}
```


---

## 作者：Crazyouth (赞：2)

**分析**

首先，有一个结论如下：对于一个竞赛图，在将 SCC 缩成点后会变成另一个竞赛图，且是 DAG。因此，对于两个点 $u,v$，若 $k_u\le k_v$，则 $u$ 可以到达 $v$。因为 $u,v$ 若在一个 SCC 内，必可达。若不在一个 SCC 里，则缩点后 $u$ 所在的 SCC 可以到达 $v$ 的。

综上，我们对每对满足 $k_u>k_v$ 的点对 $(u,v)$，按照 $k_u-k_v$ 从大到小排序，若 $u$ 可以到达 $v$（向交互库发出询问），则点对 $(u,v)$ 就是所求点对。若图中没有这样的点对，即无解，输出 `! 0 0`。

**AC Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
int k[510],cnt=0;
struct edge
{
	int u,v,w;//这里w不是权值，而是k[u]-k[v]
}e[int(1e6)];
int cmp(edge a,edge b)
{
	return a.w>b.w;
}
int main()
{
	int n,cnt=0;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>k[i];
	for(int i=1;i<=n;i++)
	for(int j=i+1;j<=n;j++)
	{
		int u=i,v=j;
		if(k[u]<k[v]) swap(u,v);
		e[++cnt].u=u;
		e[cnt].v=v;
		e[cnt].w=k[u]-k[v];
	}
	sort(e+1,e+cnt+1,cmp);
	for(int i=1;i<=cnt;i++)
	{
		cout<<"? "<<e[i].u<<' '<<e[i].v<<endl;
		cout.flush();
		string s;
		cin>>s;
		if(s=="Yes")
		{
			cout<<"! "<<e[i].u<<' '<<e[i].v<<endl;
			cout.flush();
			return 0;
		}
	}
	cout<<"! 0 0"<<endl;
	cout.flush(); 
	return 0; 
}

---

## 作者：MadokaKaname (赞：1)

## solution

这题应该是结论题，~~什么 Tarjan 什么拓扑序，这不 shaber 题吗，用这些干嘛~~ 

看到**输出 Yes 后结束**则大致可以猜到询问为从大到小猜测所有的解。

那如何在一次交互之后得知该组解合法？

仔细观察题目，猜测**一个点必然能到达出度大于等于它的点**。

### 证明他！

接下来证明这个结论。

因为原图是一张完全图进行了定向，因此通过入度可以得知出度。

显然，**入度小的点的出度一定大于入度大的点**

根据抽屉原理，可知**出度大的点必然有一条边连向出度小的点或有边指向出度小的点的边**

嗯，好像有点抽象。

用图来感性理解一下。

下面的图上点上标的数字为**出度**。

![](https://cdn.luogu.com.cn/upload/image_hosting/maczu5kj.png)

~~笔者画图功力不高，不喜勿喷~~

显然，$s$ 所有边可以指向 $t$ 一次可以到达的点集还有剩余，这些边自然就连向 $t$ 和一次可以到达 $t$ 的点集。

而当两点之间出度相同时，若所有出边指向同一点集，则必然不存在这样的图（有两条不同方向的边连接在两点之间）

Q.E.D.

因此将所有点对按入度绝对值之差从大到小排序，一个一个试即可。


## code

```cpp
#include <bits/stdc++.h>
#define f fflush(stdout)
using namespace std;
struct edge{
	int from,to,val;
}x;
int n,i,j,k,m;
struct cmp{
	bool operator()(const edge &x,const edge &y){
		return x.val<y.val;
	}
};
priority_queue<edge,vector<edge>,cmp> h;
int a[505];
string s;
int main() {
    scanf("%d",&n);
    for(i=1;i<=n;i++)
      scanf("%d",&a[i]);
    for(i=1;i<=n;i++)
      for(j=i+1;j<=n;j++){
      	int tmp1=i,tmp2=j;
      	if(a[tmp1]<a[tmp2]) swap(tmp1,tmp2);
      	x.from=tmp1;x.to=tmp2;x.val=a[tmp1]-a[tmp2];
      	h.push(x);
	  }
	while(!h.empty()){
		x=h.top();h.pop();
		printf("? %d %d\n",x.from,x.to);
		f;
		cin>>s;
		if(s=="Yes"){
			printf("! %d %d\n",x.from,x.to);
			return 0;
		}
	}
	printf("! 0 0");
	return 0;
}

```






---

## 作者：do_while_true (赞：1)

# $\mathcal{Translate}$

有一个 $n$ 个点的竞赛图，其中 $i$ 的入度为 $k_i$，你可以进行交互，每次询问点对 $(A,B)$，回答是否存在 $A$ 到 $B$ 的路径，如果回答为 "Yes" 则不能再询问，否则可以继续询问。

求出一个点对 $(A,B)$ ，其中 $A,B$ 可以互相到达，并且 $|k_A-k_B|$  最大。

$3\leq n\leq 500$。

# $\mathcal{Solution}$

提供一个 $\mathcal{O}(n)$ 且不需要询问的[做法](https://codeforces.com/blog/entry/89137?#comment-775682)。

简单来说是：按照入度从小到大排序，如果到前 $i$ 个的入度和恰好为 $i\times(i-1)/2$，则出现了一个新的强连通分量，假设上一次符合条件的是 $lst$，则 $[lst+1,i]$ 构成了一个新的强连通分量。

这样遍历一遍就可以求出每个强连通分量里有哪些点，就能统计出答案了。

排序选择计数排序，时间复杂度 $\mathcal{O}(n)$。

# $\mathcal{Code}$

```cpp
//Code by do_while_true
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#define pp std::pair<int,int>
#define mp std::make_pair
#define fir first
#define sec second
template <typename T>
T& read(T& r) {
	r = 0; bool w = 0; char ch = getchar();
	while(ch < '0' || ch > '9') w = ch == '-' ? 1 : 0, ch = getchar();
	while(ch >= '0' && ch <= '9') r = r * 10 + (ch ^ 48), ch = getchar();
	return r = w ? -r : r;
}
const int N = 510;
int n, mx = -1, lst, sum, ansu, ansv, ct;
std::vector<int>vec[N];
pp a[N];
signed main() {
	read(n);
	for(int i = 1, x; i <= n; ++i) {
		read(x);
		vec[x].push_back(i);
	}
	for(int i = 0; i <= n; ++i)
		for(auto j : vec[i])
			a[++ct] = mp(i, j);
	for(int i = 1; i <= n; ++i) {
		sum += a[i].fir;
		if(sum == i * (i-1) / 2) {
			if(lst != i-1) {
				int now = a[i].fir - a[lst+1].fir;
				if(now > mx)
					mx = now,
					ansu = a[lst+1].sec,
					ansv = a[i].sec;
			}
			lst = i;
		}
	}
	printf("! %d %d\n", ansu, ansv);
	return 0;
}
```

# $\mathcal{Proof}$

竞赛图有个经典结论，其强连通缩点后的DAG呈类似于链状, 前面的所有点向后面的所有点连边。网上能搜到很多证明，这里就不重复论述了。

可以发现，**拓扑序在前的SCC的任意一节点的入度**严格小于**拓扑序在后的SCC的任意一节点入度**。因为前面的SCC的点必定向后面的SCC的点连边。

所以所有节点按照入度和从小到大排序后，同一个SCC的节点一定是连续的。

---

引理一：若一个竞赛图按照入度从小到大排序，仅有 $i=n$ 满足前 $i$ 的入度和为 $i\times (i-1)/2$，则这个竞赛图缩点后只有一个SCC。

原因很简单，如果有多个SCC，那么第一个SCC若以 $j$ 结尾，一定满足入度和为 $j\times(j-1)/2$，与仅有 $i=n$ 时满足不符。

---

$\mathcal{Solution}$ 中的结论的必要性比较显然，在此不多赘述。

考虑 $Solution$ 中提到的步骤，由引理一得，若第一个满足条件的为 $i$ ，则前 $i$ 个节点在同一个SCC，因为前 $i$ 个节点之间互相只有 $i\times(i-1)/2$ 条边，而入度也正好统计到了这么多边，所以可以看成引理一的情况。

现在已经求出第一个SCC了，如果我们找到的第二个满足条件的点在 $j$ 。

由于满足必要性，所以此时考虑前 $j$ 个节点时，要不然是两个 SCC，要不然后面的组成不了SCC。

设第一个SCC为集合 $L$，其大小为 $l$。后面的点组成的集合为 $R$，其大小为 $r$。

只考虑 $L$，则他们的入度和为 $\sum\limits_{k=0}^{l-1}k=l\times(l-1)/2$，由于图为竞赛图，所以 $L$ 中的每个点一定都与 $R$ 中每个点相连，且这些有向边一定是朝向 $R$ 中的点，这一部分的入度和为 $l\times r=\sum\limits_{k=l}^{j-1}l$。

总的入度和为 $j\times(j-1)/2=\sum\limits_{k=0}^{j-1}k$，发现这个求和与前面两个求和的差值恰好为 $\sum\limits_{k=l}^{j-1}k-l=\sum\limits_{k=0}^{r-1}k$。

也就是说，$R$ 内部的点的入度和为 $\sum\limits_{k=0}^{r-1}k=r\times(r-1)/2$，由引理一可得 $R$ 可组成一个SCC。

这是两个的情况，注意到对于 $L$ 来说，仅使用到了 $L$ 内部的入度和为 $l\times(l-1)/2$ ，以及 $L$ 中的每个点一定都与 $R$ 中每个点相连，将  $L$ 扩展为前 $k$ 个SCC的点组成的集合同样满足这两条性质。

结论的充分性得证。

---

本文即使略去一些繁琐的，不必要的推导，仍显得篇幅略长。如有质疑或建议欢迎提出。

---

## 作者：7KByte (赞：1)

首先这道题给定的图是竞赛图。

竞赛图是一张完全图，对每条边指定一个方向得到的有向图。

竞赛图拥有一些比较神奇的性质，比如对于任意一张竞赛图，一定包含一条哈密顿路径。

然而这个性质在这道题中用不到，我们需要发掘其他性质。

比如这道题的交互方式已经告诉了我们解法。

在我们得到第一个$\texttt{Yes}$后需要结束询问，也就意味着我们需要构造询问使得得到的$\texttt{Yes}$能告诉我们两点是强连通的。

题目还给定了入度$k_i$，我们可以猜测，如果入度大的点能够到达入度小的点，则两个点强连通。

证明：

我们对竞赛图使用强连通分量缩点，然后跑拓扑排序。则在拓扑序中相邻的两个分量，第一个分量中的任意一个点必定向第二个分量中所有点连边，则出度$\ge sz_r$，而第二个分量不能向第一个分量连边，因为如果右边则可以继续缩点，所以出度$<sz_r$。对于其余的联通分量，由于是完全图，则与两个联通分量中连有相同方向的边。

所以如果两个点$k_i<k_j$，则 $i$ 的出度大于 $j$ 的出度。如果 $i,j$ 在一个联通分量，则显然强连通。否则 $i$ 一定能到达 $j$，如果 $j$ 又能到达 $i$，则两个点强连通。

一个没有太大用的性质，就是对于 $k=0$ 的点 ，只有出边，可以将这个点删掉，并将其他 $k$ 减 $1$。这样可以大大减少交互次数。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define N 505
using namespace std;
int n,T;
typedef pair<int,int> Pr;
Pr k[N];
struct node{
	int l,r,val;
	bool operator<(const node o)const{
		return val>o.val;
	}
}a[N*N];
int main(){
	cin>>n;
	rep(i,1,n)cin>>k[i].first,k[i].second=i;
	sort(k+1,k+n+1);
	int j=1;
	while(j<=n&&k[j].first==0){
		rep(u,j+1,n)k[u].first--;
		j++;
	}
	rep(x,j,n)rep(y,x+1,n)a[++T].l=k[x].second,a[T].r=k[y].second,a[T].val=k[y].first-k[x].first;
	sort(a+1,a+T+1);
	rep(i,1,T){
		cout<<"? "<<a[i].r<<" "<<a[i].l<<endl;
		string op;cin>>op;
		if(op=="Yes"){cout<<"! "<<a[i].l<<" "<<a[i].r<<endl;return 0;}
	}
	cout<<"! 0 0"<<endl;
	return 0;
} 
```

---

## 作者：Priestess_SLG (赞：0)

可是我还真的不知道这个性质啊/kel

这题太麻森了，交互题不交互.jpg

考虑到图是一张竞赛图，竞赛图有下面的几条性质：

+ 任意一个点入度加上出度为 $n-1$。
+ 任意一张竞赛图缩点后一定为链。
+ 若 $x$ 点的出度大于或等于 $y$ 点的出度，则 $x$ 一定可以到达 $y$。
+ 同样的，若 $x$ 点的入度小于或等于 $y$ 点的入度，则 $x$ 一定可以到达 $y$。

然后这题就很简单了。考虑到对任意两个点 $x,y$，钦定 $x$ 的出度比 $y$ 的出度小，则根据性质 $3$ 可以知道一定存在路径使得 $y$ 可以到 $x$。此时只需要将所有二元组排序然后依次询问 $x,y$ 判断是否合法即可得到答案，时间复杂度为 $O(n^2\log n)$ 可以通过。

[AC Code](https://codeforces.com/contest/1498/submission/299250856)，很好写。

---

## 作者：zjjws (赞：0)

### 题意

有一个 $n$ 个节点的竞赛图，给定每个点的入度 $k_i$，但不知道具体的连边方案。

现在你可以询问 ```? x y``` 来查询是否可以从 $x$ 出发到达 $y$。如果可以，返回 $\texttt{Yes}$，否则返回 $\texttt{No}$。在得到一次 $\texttt{Yes}$ 的结果后必须停止询问。

要求两个点 $x,y$ 满足：这两个点可以相互达到。输出 $|k_x-k_y|$ 的一个点对。如果有多组，输出任意即可。如果不存在，输出 ```! 0 0```。

---

### Solution

竞赛图有一个很好的性质：缩完点的图是一个 DAG，并且拓扑序小的点向后面所有的点都有连边。

前面相互到达的限制，实际上就是要求在同一个强连通分量内。

易证：按照 DAG 的拓扑序排列的强连通分量，内部的每一个点的入度都比之前的强连通分量内部的点严格要大。

因为每个强连通分量内部，假设有 $x$ 个点，每个点从内部获得的入度贡献最多为 $x-2$（一个点的话为 $0$），而对拓扑序靠后的强连通分量内部的所有点都有 $x$ 的贡献。


那么只要把所有二元组 $(x,y),k_x\le k_y$ 塞入一个堆中，以 $|k_x-k_y|$ 为关键字维护一个大根堆，拿出来的时候，询问 ```? y x``` 即可。如果返回 $\texttt{Yes}$，说明它们在同一个强连通分块内（若不在，后面的强连通分量无法到达前面的，会返回 $\texttt{No}$），那么它就是当前最优秀的二元组。

---


### Code

```cpp
#include <stdio.h>
#include <algorithm>
#define LL long long
using namespace std;
inline LL rin()
{
    LL x=0;
    char c;
    bool tag=false;
    for(c=getchar();c>'9'||c<'0';c=getchar())if(c=='-'){c=getchar();tag=true;break;}
    for(;c>='0'&&c<='9';c=getchar())x=(x<<1)+(x<<3)+(c^'0');
    if(tag)x=-x;
    return x;
}
inline bool get_typ(){char c=getchar(),x;for(;c!='Y'&&c!='N';c=getchar());if(c=='Y')return true;return false;}
inline void jh(int &x,int &y){if(x^y)x^=y^=x^=y;return;}
inline int min(int x,int y){return x<y?x:y;}
inline int max(int x,int y){return x>y?x:y;}
const int N=5e2+3;
int n;
int k[N];
inline int que(int x,int y){printf("? %d %d\n",x,y);fflush(stdout);return get_typ();}

int cutt;
pair<int,int>a[N*N];
int val[N*N];
int d[N*N];
int num[N*N];
int tail;
inline void jh_(int &x,int &y){jh(d[x],d[y]);jh(x,y);return;}
inline void up(int x){if(x==1)return;if(val[d[x]]>val[d[x>>1]])jh_(num[d[x]],num[d[x>>1]]),up(x>>1);return;}
inline void down(int x)
{
    if((x<<1)>tail)return;
    int nxt=x;if(val[d[x<<1]]>val[d[nxt]])nxt=x<<1;if(((x<<1)|1)<=tail&&val[d[(x<<1)|1]]>val[d[nxt]])nxt=(x<<1)|1;
    if(nxt!=x)jh_(num[d[x]],num[d[nxt]]),down(nxt);return;
}
inline int top(){return d[1];}
inline void pop_top(){jh_(num[d[1]],num[d[tail]]);tail--;down(1);return;}
inline void push(int x){d[++tail]=x;num[x]=tail;up(tail);return;}
inline void work()
{
    n=rin();
    if(n==2){puts("! 0 0\n");fflush(stdout);}
    for(int i=1;i<=n;i++)k[i]=rin();
    for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++)a[++cutt]=make_pair(i,j),val[cutt]=abs(k[i]-k[j]);
    for(int i=1;i<=cutt;i++)push(i);
    for(;tail;)
    {
        int now=top();pop_top();
        int x=a[now].first,y=a[now].second;if(k[x]>k[y])jh(x,y);
        if(k[x]==k[y]){printf("! %d %d\n",x,y);fflush(stdout);return;}
        if(que(y,x)){printf("! %d %d\n",x,y);fflush(stdout);return;}
    }
    puts("! 0 0\n");fflush(stdout);
    return;
}
int main()
{
    work();
    return 0;
}

```

---

