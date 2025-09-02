# [USACO24OPEN] Bessie's Interview S

## 题目描述

Bessie 正在寻找新工作！幸运的是，$K$ 名农夫目前正在招聘并举行面试。由于工作竞争激烈，农夫们决定按申请的顺序对奶牛进行编号和面试。有 $N$ 头奶牛在 Bessie 之前申请，因此她的编号为 $N+1$（$1\le K\le N\le 3\cdot 10^5$）。

面试过程如下。在时刻 $0$，对于每一个 $1\le i\le K$，农夫 $i$ 将开始面试奶牛 $i$。一旦一名农夫完成面试，他将立刻开始面试队列中的下一头奶牛。如果多名农夫同时完成，下一头奶牛可以根据自己的偏好选择接受任一此时空闲的农夫的面试。

对于每一个 $1\le i\le N$，Bessie 已经知道奶牛 $i$ 的面试将恰好花费 $t_i$ 分钟（$1\le t_i\le 10^9$）。然而，她不知道每头奶牛对农夫的偏好。

由于这份工作对 Bessie 来说非常重要，所以她想要认真准备面试。为此，她需要知道她会在何时接受面试，以及哪些农夫可能会面试她。帮助她求出这些信息！ 

## 说明/提示

### 样例解释 1

除了 Bessie 之外有 $6$ 头奶牛，以及 $3$ 名农夫。面试过程将如下进行：

1. 于时刻 $t=0$，农夫 $1$ 面试奶牛 $1$，农夫 $2$ 面试奶牛 $2$，农夫 $3$ 面试奶牛 $3$。
2. 于时刻 $t=1$，农夫 $2$ 结束了对奶牛 $2$ 的面试并开始面试奶牛 $4$。
3. 于时刻 $t=3$，农夫 $1$ 和农夫 $2$ 都完成了面试，从而有两种可能：
    * 农夫 $1$ 面试奶牛 $5$，农夫 $2$ 面试奶牛 $6$。在这种情况下，农夫 $2$ 将于时刻 $t=8$ 完成面试并开始面试 Bessie。
    * 农夫 $1$ 面试奶牛 $6$，农夫 $2$ 面试奶牛 $5$。在这种情况下，农夫 $1$ 将于时刻 $t=8$ 完成面试并开始面试 Bessie。

从而，Bessie 的面试将于时刻 $t=8$ 开始，并且她可能会被农夫 $1$ 或农夫 $2$ 面试。

### 测试点性质

- 测试点 $2-3$：没有两名农夫同时完成面试。
- 测试点 $4-9$：$N\le 3\cdot 10^3$。
- 测试点 $10-21$：没有额外限制。

## 样例 #1

### 输入

```
6 3
3 1 4159 2 6 5```

### 输出

```
8
110```

# 题解

## 作者：cff_0102 (赞：21)

第一个问题比较简单，只需要用优先队列模拟，里面存下当前每个农夫面试的奶牛的结束面试的时间即可，最后输出 `q.top()`。

重点在第二问。好像很多题解没说清楚为什么不能用并查集，这里举出一个例子：

输入：

```text
8 3
4 4 5 1 2 3 4 1
```

它对应的农夫每个时刻面试的奶牛编号是这样的：

```text
1 2 3
1 2 3
1 2 3
1 2 3
4 5 3
6 5 7
6 8 7
6 . 7
. . 7
```

在第 $4$ 时刻结束后，$1,2$ 号农夫可以交换，因此 Bessie 可能被第 $1,2$ 号农夫面试。

在第 $5$ 时刻结束后，第 $1,3$ 号农夫可以交换（如果先前 $1,2$ 号农夫已经交换则此时 $2,3$ 号农夫可以交换），但是交不交换无所谓，因为 Bessie 已经不可能被这两个农夫中的任何一个面试了。

而如果使用并查集，在第 $5$ 时刻结束后，会将 $1,3$ 号农夫合并，而先前已经将 $1,2$ 号农夫合并。因此，如果使用并查集，最终的答案会认为 $3$ 号农夫也是有可能面试到 Bessie 的，然而实际上不行，只不过是 $1,3$ 号农夫最终面试的奶牛编号可能不同罢了。

那么正确的解法应该是什么呢？

拿优先队列跑过一遍后，我们可以在中途存下每个奶牛开始面试和结束面试的时间。这个值是确定的，即使面试这些奶牛的农夫可能不确定。首先拿 Bessie 开始面试的时间找到结束面试的时间为这个值的奶牛，这些奶牛是有可能在此时让 Bessie 排到后面的。继续拿这些奶牛的开始时间找结束时间相同的奶牛，最终直到找到了编号在 $1$ 到 $k$ 之间的奶牛，那么 Bessie 有可能排在这些奶牛的后面，而面试这些奶牛的农夫编号就是这些奶牛的编号，存下这些编号即可。

具体实现时，注意到拿第 $i$ 号奶牛的开始时间找结束时间相同的奶牛时，不可能找到编号比 $i$ 大的奶牛，所以可以之间从 $n$ 到 $1$ 倒着跑一遍，拿一个 `set` 维护当前需要找结束时间为多少的奶牛。遍历到一个奶牛时，如果这个奶牛的结束时间正好是我们要找的，那么就把它的开始时间放到 `set` 里面。如果 $i\le k$，那么就把一个记录最终答案的 `bool` 数组标记一下即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[300005],st[300005],ed[300005];
priority_queue<int,vector<int>,greater<int>>q;
set<int>s;
bool b[300005];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n,k;cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=k;i++){
		ed[i]=a[i];
		q.push(ed[i]);
	}
	for(int i=k+1;i<=n;i++){
		int x=q.top();q.pop();
		st[i]=x;ed[i]=x+a[i];
		q.push(ed[i]);
	}
	cout<<q.top()<<endl;
	s.insert(q.top());
	for(int i=n;i>=1;i--){
		if(s.find(ed[i])!=s.end()){
			s.insert(st[i]);
			if(i<=k)b[i]=1;
		}
	}
	for(int i=1;i<=k;i++)cout<<b[i];
	return 0;
}
```

---

## 作者：EnofTaiPeople (赞：8)

考虑如何快速通过银组。

首先使用优先队列来模拟一下，找出一种可行解和花费的时间，重载运算符每次弹出最早的即可。

关于可行性，一种想法是将中途有过值相同的两个农夫用并查集合并，最终与可行解并在一起的就可以。

不过这种想法是不对的，因为有可能一个数刚开始是可行解，中途和可行解并起来了，但后来操作一段时间之后，他已经不可能得到“**贝**茜”了！这时将失去“**贝**茜”的他和其他的并起来也不能说明其他的农夫可能获取“**贝**茜”。

发现一个农夫可能获取“**贝**茜”当且仅当从他的初始时间可以变成最终的答案时间，考虑将队列弹出时，将时间连边（具体地，将 $k+t_i$ 向 $k$ 连边），最后从末尾广搜即可，需要离散化。

时间为离散化和优先队列的 $O(n\log n)$，空间 $O(n)$：
```cpp
int T,n,K,m,f[N],mst,gt,q[N];
ll a[N],b[N],mp[N];
int gf(int x){return x==f[x]?x:f[x]=gf(f[x]);}
void mg(int x,int y){f[gf(x)]=gf(y);}
priority_queue<pair<ll,int>>q1;
bitset<N>vs;
vector<int>lk[N];
#define MP(x) lower_bound(mp+1,mp+m+1,x)-mp
struct Eg{
    ll a,b;
    void run(){
        lk[MP(a)].push_back(MP(b));
    }
}g[N];
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int i,j,k,l,r,x,y,z;ll v1,v2;
    cin>>n>>K,m=K;
    for(i=1;i<=n;++i)cin>>a[i];
    for(i=1;i<=K;++i)q1.emplace(mp[i]=-a[i],i);
    for(i=K+1;i<=n;++i){
        tie(v1,x)=q1.top(),q1.pop();
        q1.emplace(v1-a[i],x);
        mp[++m]=v1-a[i],g[++gt]={v1-a[i],v1};
    }
    sort(mp+1,mp+m+1),m=unique(mp+1,mp+m+1)-mp-1;
    printf("%lld\n",-q1.top().first);
    for(i=1;i<=gt;++i)g[i].run();
    vs[q[l=r=1]=MP(q1.top().first)]=1;
    while(l<=r){
        x=q[l++];
        for(int y:lk[x])
            if(!vs[y])vs[q[++r]=y]=1;
    }
    for(x=1;x<=K;++x)putchar(vs[MP(-a[x])]?'1':'0');
    return 0;
}
```

---

## 作者：chala_tea (赞：5)

## 船新做法——分层连边 dfs

这个做法是在校内断网模拟赛里灵光一现想出来的。码量相比一楼更大，但是相较更为直观。

### 题目描述：

有 $k$ 个农夫要面试 $n+1$ 头牛。每头牛面试时间为 $a_i$。开始第 $0$ 秒时，指定第 $i$ 个农夫面试第 $i$ 头牛。当有一个农夫面试结束时，该农夫紧接着面试编号最小且没被面试的牛。如果有两名或多名农夫同时面试结束，将会随机分配面试哪头牛。

询问：
1. 第 $n+1$ 头奶牛最快将在哪个时刻被面试；
2. 第 $n+1$ 头奶牛在最快情况下有可能被谁面试；

### 思路分析：

首先很显然，对于第一个问题我们考虑直接用``priority_queue<pair<int,int>>``来解决，第一关键字为时间，第二关键字为农夫序号。模拟即可。难点在于第二小问。

在考场上第一反应是并查集。但是我们会发现，前期潜在的最优解，即使最终不是最优解，也会和最终的最优解连成一块。这里提供一组 hack 数据，读者有兴趣可以手模测试：
```
input:
9 4
3 1 4 5 2 1 2 2 2
output:
5
1101
（使用并查集则为1111）
```
那么，我们该怎么将潜在的最优解剔除，保证输出一定是最优解的路径呢？

以上面的 hack 数据为例。此时，我们将每一次“有羊面试结束，其他羊加入面试”的事件按时间先后并将其作为纵坐标，而将农夫根据序号从小到大横向排开作为横坐标，而将潜在的或是确定要加入的羊作为点。我们默认假设农夫按序号从小到大依次取羊（即图中的红色数字），这样我们可以得到如下一张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ip1bq4e2.png)

首先，我们可以确定，最后总耗时最小的一个或多个点，一定属于答案集合。如图中的 $2$ 号农夫与 $4$ 号农夫。我们可以想象在这些纵列里存在一条从终点走向起点的路径。称为“答案路径”。

然后我们发现，如果在已知的路径上存在一个点，这个点所在行还有别的点，那么这个答案路径就可以“分叉”到该行的其他点上。为什么呢？因为同行的点意味着该农夫也是可以取到那只“正解羊”的。例如图中纵坐标为 $2$ 的行，如果农夫 $1$ 取走了耗时为 $2$ 的羊，世界线就发生了变动，使得农夫 $1$ 也可以在最后面试 Bessie。最后从这个转折点开始，也接一条到起点的答案路径并按照上面的方法判断要不要“分叉”。结果如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/uzaf4job.png)

所以，我们可以将一整行看成整体的一层。从答案路径经过的每一层的每一点向后做一条答案路径。这样最后起点有连接答案路径的横坐标即为答案。

具体做法是：从最后一层开始，向上按层 dfs 即可。注意每一层只需要被 dfs 一次就可以。

实现细节请看代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long //坏习惯不要学
#define MAXN 314514

int n,k;
int t[MAXN],ans[MAXN],cnt=0;
priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> q;
bool been[MAXN]; 

vector<int> g[MAXN];//层与层的连边建图
vector<int> layer[MAXN];//存某横坐标上有哪些层
vector<int> contain[MAXN];//存某层上有哪些点

inline void merge(int x,int y){
	for(auto i:layer[y]){
		g[x].emplace_back(i);//向每个点所在横坐标上存在的层建有向边
	}
	layer[y].emplace_back(x);//如定义
	contain[x].emplace_back(y);//如定义
}

void dfs(int x){
	if(been[x])return; //判断该层有没有被走过，走过就不用再走一遍了
	been[x]=1;
	for(auto i:contain[x]){
		ans[i]=1;//遍历该层，如果在这个点上分叉了则这个点所在横坐标一定有答案路径。
	}
	for(auto i:g[x]){
		dfs(i);//按图dfs
	}
}


signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>t[i];
	
	for(int i=1;i<=k;i++) q.push(make_pair(t[i],i));
	
	pair<int,int> now;
	for(int i=k+1;i<=n;){
		now=q.top();
		q.push(make_pair(now.first+t[i++],now.second));
		q.pop();
		if(i>n)break;
		merge(++cnt,now.second);
		while(now.first==q.top().first){
			if(i>n)break;
			q.push(make_pair(now.first+t[i++],q.top().second));
			merge(cnt,q.top().second);
			q.pop();
		}
		if(i>n)break;
	}

  //这里要讨论。如果第n+1头羊仍属于上一层则把上一层先建好，否则往下建一层。
	if(now.first==q.top().first){
		while(now.first==q.top().first){
			merge(cnt,q.top().second);
			q.pop();
		}
	}else{
		now=q.top();
		q.pop();
		cnt++;
		merge(cnt,now.second);
		while(now.first==q.top().first){
			merge(cnt,q.top().second);
			q.pop();
		}
	}
	
	dfs(cnt);	
	cout<<now.first<<endl;
	for(int i=1;i<=k;i++)cout<<ans[i];
	return 0;
}

```

求省和大大通过！偶捏该！

---

## 作者：lzt415 (赞：4)

# P10277 题解
## 思路分析
首先，这道题分为两个小问，分别是求开始面试的时间和可能面试的农夫编号。所以整篇题解会分为两部分进行解释。
### 并查集反例
想了想，最终决定给大家一个并查集的反例。

很多人也许会在第一时间内想到用并查集来做这道题，但其实这个做法是错误的，并且其他题解也已经详细的解释了为什么是错的，不过由于这是一个错误的解法，所以本人觉得并没有必要在这里说明一个错的东西，不过还是决定为大家提供一个并查集反例以供参考。

注：该数据来源于讨论区。

具体样例如下：
```cpp
8 4 1 1 2 3 2 1 100 100
```
不出意外的话你手动模拟一下会发现你的并查集是错的。

下面开始正式讲解，请仔细听讲。
### 问题一
问题一是求解面试时间，是较简单的一问。

解决这个问题需要用到优先队列，先把前 $k$ 个存入优先队列中，然后再把编号从 $k$ 到 $n$ 的奶牛依次存入，具体操作是每次将队头元素扔出去，在把当前元素的开始时间设为上一个元素的结束时间，当前元素的结束时间设为开始时间加上该元素的面试时间，再将其压入队列。至于原因后面会讲到。

而大致操作是：

```cpp
for(int i=1;i<=n;i++)
{
	cin>>a[i];
}
for(int i=1;i<=k;i++)
{
	End[i]=a[i];//End为结束时间。
	q.push(End[i]);
}
for(int i=k+1;i<=n;i++)
{
	int t=q.top();
    q.pop();
	Start[i]=t;//Start为开始时间。
    End[i]=t+a[i];
	q.push(End[i]);
}
```
### 问题二
这个问题是求可能的面试者编号。

写题解前发现好多大佬一开始想到了并查集，~~可是我太弱了，都没想到它，可恶。~~  

不过上面已经说明了这个解法是错的，并且举了反例，所以就不多加赘述了，还是好好说说正解吧。

究竟要怎样做呢？？别急。还记得上文说的开始时间和结束时间吗，按理说开始时间是不用存的，但是这道题需要，下面开始解释原因：

我们要从万变之中找不变。  
因为无论面试者是谁，面试时间永不变，所以说每头奶牛也许面试者不确定，但是面试的初始时间一定是确定的，而从题干中告诉我们，编号从 $1$ 到 $k$ 的奶牛面试者固定，所以以上这些就不会改变。  

我们要从变化之中推正解。  
每头奶牛如果在面试之前发现有多种选择，那么他的选择就会影响后面奶牛的面试者，所以我们可以从后往前推导，直到找到前 $k$ 个不变的量，也就是面试者编号。

于是我们可以在优先队列中途存下每个奶牛开始面试和结束面试的时间。然后一个 $n$ 到 $1$ 的循环往前找，每次查找这头奶牛前面有和当前奶牛的开始时间相同的结束时间的奶牛，也就是可以进行的选择，一直往前找，直到查到前 $k$ 个，你就可以知道面试者编号可能是多少。

这个操作可以用 ```set``` 进行维护，具体操作如下：

```cpp
s.insert(q.top());//插入进集合，即Bessie的开始时间。 
for(int i=n;i>=1;i--)
{
	if(s.find(End[i])!=s.end())//如果这头奶牛的结束时间在集合中有，也就是存在后面的奶牛的开始时间和这头奶牛的结束时间相等。 
	{
		s.insert(Start[i]);//把这头奶牛的开始时间存进去。 
		if(i<=k)
		{
			b[i]=1;//查到了前k头，说明编号为i的农夫可能面试 Bessie。 
		}
	}
}
for(int i=1;i<=k;i++)
{
	cout<<b[i];//输出即可。 
}
```
下面给完整代码。

~~作者十分良心，为大家提供了一份优质的代码，马蜂优良。并且直接黏贴提交后还会送你红色的花花，紫色的花花，就是没有小绿叶子，不过大概率你这些都得不到，因为你极有可能会得到一份编译错误。~~
## CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+10;
int a[N],Start[N],End[N];
bool b[300005];//上面已经解释了这几个数组表示什么 
priority_queue<int,vector<int>,greater<int> > p;
set<int> s;
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=k;i++)
	{
		End[i]=a[i];
		q.push(End[i]);
	}
	for(int i=k+1;i<=n;i++)
	{
		int t=q.top();
		q.pop();
		Start[i]=t;
		End[i]=t+a[i];
		q.push(End[i]);
	}
	cout<<q.top();
	s.insert(q.top());
	for(int i=n;i>=1;i--)
	{
		if(s.find(End[i])!=s.end())
		{
			s.insert(Start[i]);
			if(i<=k)
			{
				b[i]=1;
			}
		}
	}
	for(int i=1;i<=k;i++)
	{
		if(b[i]) cout<<b[i];
	}
	return O;
}
```
## 题外话
你真的以为把代码复制上去就完事了么？？？你真的以为代码是正确的么？？？你确定你要抄代码吗？？？

以上节选自灵魂三问。

所以，抄代码需要慎重。

---

## 作者：Jim_Franklin (赞：4)

第一问比较好求，只需要用优先队列模拟即可。

对于第二问，首先能够想到要把同一个时间的农夫用并查集合并，但是很明显有反例。

分析这个做法错误的原因，在于可能存在两个农夫因为某些原因导致他们的合并变得不合法。

因此问题出在农夫身上。

分析合并内容的共性，发现他们的时间都相同，于是可以想到以时间为点建图。

对于每个时间节点 $t$ ，令一个长度为 $m$ 的二进制串 $s$ 表示如果在当前时间接受采访可能会遇到的农夫有哪些。

容易发现这个 $s$ 具有传递性，其具体意义就是有一头奶牛 $i$ 在 $t+t_i$ 时刻的时候结束它的面试，则 $t+t_i$ 的 $s$ 一定与 $t$ 的 $s$ 相同，因为面试它们的是同一批农夫。

于是便可以由 $t+t_i$ 向 $t$ 连边，然后以第一问的答案为起点搜一遍，能够遍历到的点打上标记，具体的看代码吧。

时间复杂度 $O(n\log{n})$。

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ri register
const int inf=0x3f3f3f3f;
inline int rd(){
	int x=0,y=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar())if(c=='-')y=-1;
	for(;c>='0'&&c<='9';c=getchar())x=(x<<1)+(x<<3)+(c^48);
	return x*y;
}
const int N=6e5+5;
int n,m,t[N],cnt,vis[N];
map<int,int>mp;
vector<int>e[N];
priority_queue<int,vector<int>,greater<int> >q;
void solve(int u){
	if(!mp[u])mp[u]=++cnt;
} //把点离散化
void dfs(int u){
	vis[u]=1;
	for(auto v:e[u])if(!vis[v])dfs(v);
}
signed main(){
	n=rd();cnt=m=rd();//最初的 m 个点就是对第二问有贡献的点
	for(int i=1;i<=n;i++)t[i]=rd();
	for(int i=1;i<=m;i++)
		q.push(t[i]),solve(t[i]),e[mp[t[i]]].push_back(i);
	for(int i=m+1;i<=n;i++){
		int tmp=q.top();q.pop();
		int v=tmp+t[i];solve(v);
		e[mp[v]].push_back(mp[tmp]);
		q.push(v);
	}
	dfs(mp[q.top()]);
	cout<<q.top()<<'\n';
	for(int i=1;i<=m;i++)cout<<vis[i];
	return 0;
}
```
[这个帖子](https://www.luogu.com.cn/discuss/797868)里有并查集做法的反例。

---

## 作者：天野星河 (赞：3)

upd on 2024.11.10: 修复 $\LaTeX$ 符号，使其更加规范。

使用堆来模拟。我们定义多个农民同时完成任务称为“事件”。

对于每个事件，存储完成任务农民的集合。把接下来的几头牛随意地分配给这些农民。由此，我们可以确定 Bessie 面试的时间，以及其中一个可以面试到 Bessie 的农民 $x$。

令事件集合为 $E_i$。

现在，考虑一下如果我们**按倒序遍历**这些事件会发生什么。

如果农民 $x$ 参与了其中一项活动（即 $x\in E_i$），那么任何与他同时完成的农民都可能是贝茜的采访者。因此，每当贝茜可能的采访者和某一事件中的农民相交时，该事件中的任何一个农民最终都可能成为贝茜的采访者。

然后我们让答案的集合初始化为 $S=\{x\}$。

接着**倒序**枚举“事件”$E_i$：

若 $S \cap E_i \ne \varnothing$，更新 $S\gets S\cup E_i$。

可以用 bitset 实现。

时间复杂度 $\Theta(n\log k+\frac{n^2}w)$。

~~并且跑得飞快。~~

**注意：需要 long long。**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 3e5 + 10;
int n, k;
int a[N];
vector<bitset<N>> eve;

inline pair<int, int> sol() {
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
	for (int i = 1; i <= k; i++) q.emplace(a[i], i);
	int l = k;
	while (l <= n) {
		int t = q.top().first;
		pair<int, int> u = q.top();
		q.pop();
		q.emplace(u.first + a[++l], u.second);
		if (q.top().first == t && l <= n) {
			eve.emplace_back();
			eve.back().set(u.second);
		}
		while (q.top().first == t && l <= n) {
			u = q.top();
			q.pop();
			q.emplace(u.first + a[++l], u.second);
			eve.back().set(u.second);
		}
	}
	return q.top();
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> k;
	for (int i = 1; i <= n; i++) cin >> a[i];
	pair<int, int> x = sol();
	bitset<N> ans;
	ans.set(x.second);
	reverse(eve.begin(), eve.end());
	for (const bitset<N> &i : eve) if ((ans & i).any()) ans |= i;
	cout << x.first << '\n';
	for (int i = 1; i <= k; i++) cout.put(ans[i] | 48);
}

```

---

## 作者：_WRYYY_ (赞：3)

[在我的博客观看。](https://www.cnblogs.com/wryyy-233/p/18084090)

#### 题意简述：

有 $n$ 个奶牛，$k$ 个农夫，$k\le n$，每一个奶牛有一个面试时长 $t_i$，表示面试这个奶牛要多长时间。$0$ 时刻时对于所有的 $1\le i\le k$，第 $i$ 个农夫会面试第 $i$ 个奶牛，之后的面试顺序满足以下条件：

1. 若在某时刻 $t$，存在某个农夫已经面试完当前的奶牛，那么他会立即按顺序面试下一个还没有面试到的奶牛。
1. 如果当前存在 $x>1$ 个农夫，那么可以随意面试还没面试到的下 $x$ 个奶牛。

现在奶牛 Bessie 排在第 $n+1$ 位，请求出她能面试的最早时间，以及可能会面试她的农夫有哪些，如果一个农夫可能面试她则输出了$1$，不可能则输出 $0$。

#### Solution：

考虑实际上不同的时间至多有 $2n$ 个。我们可以考虑使用 ``map`` 来储存这是第几个最新出现的数，接着对于时间 $t$，如果存在一个时间 $t_0$ 是可以转移到 $t$ 的，那么我们就由 $t$ 向 $t_0$ 连边，最后由 Bessie 最早可以面试的时间逐渐向下走，因为面试时间为正整数，该图实际上是个有向无环图，最后记录可以走到的初始时间，再将这些时间对应的农夫标记，输出即可。

至于第二个限制，可以发现我们这里并不需要考虑是如何选择的，任意的选择方案最后得出的图总是同一个图，图是同一个，那么最终对应的农夫也是同样的。

需要注意的是不能重复加边，会爆空间。

我这里是直接使用 ``set`` 存边。

#### Code：

```cpp
#include <bits/stdc++.h>
#include <bits/extc++.h>
#define ll long long
#define ull unsigned long long
#define m_p make_pair
#define m_t make_tuple
#define inf (0x7f7f7f7f)
#define N 300010
using namespace std;
using namespace __gnu_pbds;
ll ti[N];
int mpcnt = 1;
typedef pair<ll, int> pii;
std::priority_queue<pii, vector<pii>, greater<pii>> q;
vector<int> hs[N], avi, ans;
set<int> a[N << 1];
map<ll, int> mp;
bitset<N << 1> vis, vis1;
void checkins(ll x)
{
	if (!mp.count(x))
	{
		mp[x] = mpcnt;
		++mpcnt;
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	ll n, k, cnt, beginc, nt = 0, fl = 0, x;
	cin >> n >> k;
	for (ll i = 1; i <= n; i++)
		cin >> ti[i];
	for (ll i = 1; i <= k; i++)
	{
		q.push(m_p(ti[i], i));
		checkins(ti[i]);
		hs[mp[ti[i]]].push_back(i);
	}
	beginc = mpcnt;
	cnt = k + 1;
	while (!q.empty())
	{
		nt = q.top().first;
		if (cnt > n)
			fl = 1;
		while (!q.empty() && q.top().first == nt)
		{
			avi.push_back(q.top().second);
			q.pop();
		}
		x = mp[nt];
		for (ll i = 0; i < avi.size(); i++)
			if (cnt <= n)
			{
				q.push(m_p(nt + ti[cnt], avi[i]));
				checkins(nt + ti[cnt]);
				a[mp[nt + ti[cnt]]].insert(x);
				++cnt;
			}
			else
				fl = 1;
		if (fl)
			break;
		avi.clear();
	}
	queue<int> qq;
	qq.push(mp[nt]);
	while (!qq.empty())
	{
		x = qq.front();
		qq.pop();
		vis[x] = 1;
		if (x < beginc)
			for (auto px : hs[x])
				vis1[px] = 1;
		for (auto y : a[x])
			if (!vis[y])
				qq.push(y);
	}
	cout << nt << "\n";
	for (int i = 1; i <= k; i++)
		cout << vis1[i];
	return 0;
}
```

时间复杂度为 $O(n\log_2n)$，附带大常数。

本来还想写写考场思路的，想了想有点丢人，还是不写了。

---

## 作者：Epi4any (赞：2)

首先我们来考虑第一个问题，可以简单的模拟得出答案，用优先队列维护各个面试官完成当前面试的时间，复杂度 $O(n \log n)$。

然后看第二个问题，不难发现我们需要找的就是面试 Bessie 的面试官是否在某一个时刻与另外一个面试官结束时间相同。而且很明显所有的牛无论被哪个面试官面试，其开始时间与结束时间必然是固定的，所以我们可以在遍历的过程中把所有牛的开始时间与结束时间记录下来。最后，我们只需要从 ans 开始，找历史上任何一个与其想同过的牛，然后一直找到面试官的序号，用 set 维护。总复杂度 $O(n \log n)$。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=3e5+10;
struct Node {
	ll st, ed, t; 
	void update() {
		ed=st+t;
	}
	friend bool operator<(Node fst, Node snd) {
		return fst.ed<snd.ed;
	}
} a[maxn];
ll n,m,ans,fa[maxn],siz[maxn],vis[maxn];
priority_queue<ll, vector<ll>, greater<ll>  > q;
set<ll> s;
ll getf(ll x) {
	if(fa[x]==x) {
		return x;
	} else {
		fa[x]=getf(fa[x]);
		return fa[x];
	}
}
void merge(ll x, ll y) {
	ll fx=getf(x),fy=getf(y);
	if(siz[fx]<siz[fy]) {
		fa[fx]=fy;
		siz[fy]+=siz[fx];
	} else {
		fa[fy]=fx;
		siz[fx]+=siz[fy];
	}
}
int main() {
	cin>>n>>m;
	for(int i=1;i<=n;i++) {
		cin>>a[i].t;
		a[i].update();
		siz[i]=0;
		fa[i]=i;
	}
	for(int i=1;i<=m;i++) {
		q.push(a[i].ed);
	}
	for(int i=m+1;i<=n;i++) {
		ll lst=q.top();
		q.pop();
		a[i].st=lst;
		a[i].update();
		q.push(a[i].ed);
	}
	ans=q.top();
	cout<<ans<<endl;
	s.insert(ans);
	for(int i=n;i>=1;i--) {
		if(s.find(a[i].ed)!=s.end()) {
			if(i<=m) {
				vis[i]=true;
			} else {
				s.insert(a[i].st);
			}
		}
	}
	for(int i=1;i<=m;i++) {
		if(vis[i]) {
			cout<<1;
		} else {
			cout<<0;
		}
	}
	return 0;
}
```

---

## 作者：Aurie (赞：1)

# P10277 [USACO24OPEN] Bessie's Interview S 题解

首先，第一问是可以轻易的使用小根堆维护的，只需要把每一个正在面试的奶牛以及它的结束时间 $push$ 到小根堆里，堆顶就是最先结束的奶牛，让下一个奶牛接在它后面即可。

考虑第二问如何解决，首先按照第一问的方式模拟出最后一个奶牛可能到哪个人去面试，结束时间最早且相等的那些部分都是有可能的，但这只求得了一组可行解，并不是全部解，考虑什么时候会漏掉一些解。假如 $a$ 面试者和 $b$ 面试者同时空闲出来，现在奶牛可以选择 $a$ 或 $b$ 中的其中一个面试，若它选择了 $a$ 并且它所在的地方最终成为了一个可行解，那么它选择 $b$ 也能使 $b$ 成为可行解，因为 $a$，$b$ 同时空出，对于选择他们的奶牛来说，他们是等价的。

因此就可以考虑倒序从一组可行解推出全局所有解。

```cpp
#include<bits/stdc++.h> 
#define int long long// 不开 long long 见祖宗，不开 long long 只有 4 分。
using namespace std;

const int N = 1e6+10;

struct node{
	int t,id;// t 记录结束时间，id 记录是哪个面试者。
	bool operator<(const node &other)const{
		return t>other.t;// 小根堆！！！ 
	} 
};
priority_queue<node> q;

struct node1{
	int te,id,cow;
	bool operator<(const node1 &other)const{
		return te<other.te;
/*
用于倒推的结构体，te 存下每个奶牛的结束时间，
用于迅速找到相同结束时间的奶牛，id 记录面试
者的编号，用于标记某个面试者是一个解，cow 存
最后一个奶牛的编号，用 te-t[cow] 得到的时间
就是此奶牛开始的时间，也是上一个奶牛结束的时
间，可以这样往前推。
*/
	}
};
int t[N];
multiset<node1> s;
/*
要么开multiset
如果用 set 在重载node1的小于号改为：
bool operator<(const node1 &other)const{
    if(te==other.te){
        return cow<other.cow;
    }
    return te<other.te;
}
如果不这么写，两个元素在 te 相等但其它不等时 set 会认为它们一样，然后去重，
话说压根就没重载等于号，它怎么知道它们相等？
因为：
若 a<b 为 false 且 b<a 为 false 那么 a=b。。。
*/
queue<int> dq;
bitset<N> mk;
// 有 bitset 了谁还用 bool mk[N]？
signed main(){
	int n,k;
	cin>>n>>k;// 此题 cin 足矣。
	for(int i = 1;i<=n;i++){
		cin>>t[i];
	}
	if(k>n){// 特判一种简单的情况。
		cout<<0<<endl;
		for(int i = 1;i<=k;i++){
			cout<<1;
		}
	}else{
		for(int i = 1;i<=k;i++){
			q.push({t[i],i});// 前 i 个奶牛先找前 i 个人。
			s.insert({t[i],i,i});// 顺便记录下每个奶牛的结束时间。
		}
		for(int i = k+1;i<=n;i++){
			q.push({q.top().t+t[i],q.top().id});// 获取堆顶进新奶牛。
			s.insert({q.top().t+t[i],q.top().id,i});
			q.pop();// 别忘了在 set 里记录并 pop。
		}
		dq.push(q.top().t);// 最后最小的时间就是最后一个奶牛会进入的可行时间，从此时间往前地推，采用bfs。
		cout<<q.top().t<<endl;// 输出进入时间。
		while(dq.size()){
			int u = dq.front();
			dq.pop();
			while(s.size()){
				auto f = s.lower_bound({u,0,0});//找到与可行时间相等的时间，都是可行时间。
				if((*f).te==u)
					mk[(*f).id] = 1,// 这个人可行，标记上！
					dq.push((*f).te-t[(*f).cow]),//往前递推。
					s.erase(f);// 用过别忘了删掉，删的时候一定要传迭代器，传值会一次性把相等的值全部删掉。
				else{
					break;
				} 
			}
		}
		for(int i = 1;i<=k;i++){
			putchar(mk[i]|0x30);// |0x30在此等价于+'0'。
		}
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：Lame_Joke (赞：1)

- ### 大体思路

  此题我们可以用优先队列来求出开始面试的时间，然后离散化一下，再模拟一次，建从所到达的时间到当前时间的边，这里我用的是链式前向星加堆，所以代码略长，当然也可以开挂（懂得都懂），连完边之后跑宽搜，从开始面试的时间开始宽搜，搜到的所有点都标记上，输出时判断这个农夫第一次面试奶牛后的时间有没有被标记，被标记了输出 $1$，否则输出 $0$ 即可。
  
 - ### 参考代码
 
 [代码太长了，上链接](https://www.luogu.com.cn/paste/fxyj4ba1)

---

## 作者：Liyunze123 (赞：1)

# 1.题目大意
有 $K$ 个农夫面试 $N + 1$ 头牛。每头牛面试时间为 $a_i$。第 $0$ 秒，第 $i$ 个农夫面试第 $i$ 头牛。一个农夫面试结束，面试编号最小且没被面试的牛。如果有两名或多名农夫同时面试结束，可以选择面试哪头牛。
# 2.解题思路
## 普通思路
先用优先队列求出第 $N + 1$ 头牛被面试时间（优先队列存第  $i$ 头牛面试结束时间和 $i$，从小到大排序），如果某农夫面试 $i$ 结束后下一个面试 $j$，就把面试 $i$ 结束的时间和面试 $j$ 结束的时间连一条边，最后 $a_i$ 能走到面试第 $N + 1$ 头牛的开始时间就输出 $1$，否则输出 $0$。

时间复杂度 $O(NK)$，会超时。
## 优化
因为每次 BFS 的结束点是同一个点，可以考虑反向建边，从结束点开始，搜到 $a_i$，就是 $1$。
# 3.注意事项
BFS 时不要重复搜，不然还会超时。

**注意 long long！**

还有，记录搜到的点是否出现在 $a$ 数组中，因为 $a_i \le 2 \times 10^9$，因为点数不多，可以计这个点是第几个出现的点。
# 4.代码展示
```
//我的码风奇特，抄袭一眼就看出来
#include<bits/stdc++.h>
#include<queue>
#include<map>
#include<vector>
using namespace std;
int n,k,a[300010],idx=1,ans[300010],l;
vector<int>u[300010];//时间可能相同，要用vector
long long s;
map<long long,long long>e,ne,h,p,d,c;
typedef pair<long long,int>b;//结束时间和几号牛
priority_queue<b,vector<b>,greater<b>>t;
queue<long long>o;
void add(long long a,long long b){e[idx]=b,ne[idx]=h[a],h[a]=idx++;}
void bfs(long long i){
    o.push(i),c[i]=1;
    while(o.size()){
        long long m=o.front();o.pop();
        if(d[m])for(int w=0;w<u[p[m]].size();w++)ans[u[p[m]][w]]=1;//注意，这个点出现在a[1]~a[k]中再做，不然p[m]可能会变乱七八糟
        for(int w=h[m];w;w=ne[w])if(!c[e[w]])o.push(e[w]),c[e[w]]=1;
    }
}
int main(){
    scanf("%d%d",&n,&k);
    for(int w=1;w<=n;w++)scanf("%d",&a[w]);
    for(int w=1;w<=k;w++){t.push({a[w],w});if(!p[a[w]])p[a[w]]=++l;u[p[a[w]]].push_back(w);d[a[w]]=1;}
    for(int w=1;;w++){//优先队列
        int i=t.top().second;
        long long h=t.top().first;//h是面试i结束的时间
        t.pop();
        if(i>n+1)continue;//没有这个编号
        if(!p[h])p[h]=++l;//压缩点
        if(!p[h+a[k+w]])p[h+a[k+w]]=++l;//压缩点
        t.push({h+a[k+w],k+w}),add(h+a[w+k],h);//add为加边函数
        if(k+w==n+1){s=h,printf("%lld\n",h);break;}//面试到了
    }
    bfs(s);
    for(int w=1;w<=k;w++)printf("%d",ans[w]);
    return 0;
}
```

---

## 作者：Sih_qwq (赞：1)

[洛谷题目链接](https://www.luogu.com.cn/problem/P10277)。

## 思路

对于第一个问题，每个奶牛要找到最早“空闲”出来的农夫面试，即找到时间最小的加上这个奶牛面试所需要的时间。由每次找出农夫之间最早“空闲”即总时间最小的农夫，想到用优先队列模拟，复杂度 $O(n \log n)$。

接下来是比较难解决的问题。对于每一个奶牛，如果有其他奶牛开始面试的时间与这一只奶牛的开始面试的时间相同，那么这两只奶牛的面试的农夫可以互换，这两个农夫都有可能面试到这两只奶牛中的一只。以此类推，Bessie 面试的开始时间，即某一只奶牛面试的结束时间，与其他某只奶牛面试的结束时间相同，那么这两只奶牛对应的农夫都有可能；这两只奶牛分别开始面试的时间又会与其他奶牛面试的结束时间相同，那么这些奶牛也有可能……

这样一来，我们可以从 Bessie 面试的开始时间起，寻找其他奶牛相同的结束时间；用这些奶牛的起始时间寻找其他有相同结束时间的奶牛的农夫……直到跳回的奶牛在 $1$ 到 $m$ 之间，即找到了可能面试的农夫。

对于从 Bessie 的面试时间跳回前面奶牛的面试时间，我们可以将时间塞进 set 里维护，如果有奶牛的结束时间与 set 里的某个时间相同，那么说明这只奶牛可以进行互换，这只奶牛对应的农夫是可能的，直到跳回 $1$ 至 $m$。

直接使用了 STL 往回跳，省去了其他题解的建图和遍历。~~但是对于时间有限的题尽量减少 STL 次数。~~

这种解法看似很像并查集。不同点在于，这种解法基于已经求出的面试时间和奶牛的面试的开始时间，而并查集尚未知道是否可行就先连边了，可以互换的奶牛到最后可能不是结果，因为后续的奶牛的结束时间不同。

## AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define N 300010
priority_queue < ll, vector < ll >, greater < ll > > q;
int cnt[N], n, m;
ll a[N], st[N], en[N];
set < ll > s;
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
	for (int i = 1; i <= m; ++i) en[i] = a[i], q.push(a[i]);
	ll tmp;
	for (int i = m + 1; i <= n; ++i) {
		tmp = q.top(); q.pop();
		st[i] = tmp, en[i] = tmp + a[i];
		q.push(en[i]); 
	}
	printf("%lld\n", q.top());
	s.insert(q.top());
	for (int i = n; i; --i) 
		if (s.find(en[i]) != s.end()) {
			if (i <= m) cnt[i] = 1;
			else s.insert(st[i]);
		}
	for (int i = 1; i <= m; ++i) printf("%d", cnt[i]);
	return 0;
} 
```

---

## 作者：创世游戏科技 (赞：0)

## 题目大意

面试过程如下。在时刻 $0$，对于每一个 $1\le i\le K$，农夫 $i$ 将开始面试奶牛 $i$。一旦一名农夫完成面试，他将立刻开始面试队列中的下一头奶牛。**如果多名农夫同时完成，下一头奶牛接受任一此时空闲的农夫的面试。**

求最后空余的最短时间和可能空余的**农夫编号**。

## 思路解析

考虑若两名农夫同时完成面试。

**那么可以模拟这个过程**，对于每个奶牛遍历数组寻找结束时间最短的农夫，让它去面试这个奶牛即可。时间复杂度 $O(NK)$。

使用优先队列可以加速这个过程，每次取出队首时间最少的农夫去面试奶牛即可。时间复杂度 $O(N\log N)$。

若有农夫同时完成面试，那么对于这个时间来说，下一头奶牛可能去到**其中的任意一个**，显然这些奶牛在对应时间是等价的，均有可能转移到下一个时间点。

但这并不能使用并查集，因为对于一个时刻这两个奶牛可以交换，**后续有可能结束时间并不相同，不作为答案**，所以用并查集是错误的。

我们考虑离散化后建边，从答案回溯到的所有农夫，即为我们所求的答案。

![](https://cdn.luogu.com.cn/upload/image_hosting/ffoyw28p.png)

样例示意图，5号节点为最终答案，可以回溯到 1,2 号节点。实际操作时建反图即可。

## 参考实现
```
#include <bits/stdc++.h>
#define int long long
#define prr pair<int,int>
using namespace std;
const int MAXN=4e5+10;
int n,m,a[MAXN],fa[MAXN],t[MAXN];
bool vis[MAXN];
priority_queue<prr,vector<prr>,greater<prr> >q;
map<int,int>mp;
vector<int>G[MAXN];
int cnt=0;
int get(int x){
    if(mp.find(x)==mp.end())mp[x]=++cnt;
    return mp[x];
}
void dfs(int x){
    if(vis[x])return;
    vis[x]=true;
    for(auto j:G[x]){
        
        dfs(j);
    }
}
void add(int x,int y){
    G[x].emplace_back(y);
}
signed main(){
    cin>>n>>m;cnt=m;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=m;i++){
        q.push(make_pair(a[i],i)),t[i]=a[i];
        add(get(t[i]),i);
    }
    for(int i=m+1;i<=n;i++){
        int u=q.top().second;
        t[u]+=a[i];
        q.pop();
        q.push(make_pair(t[u],u));
        add(get(t[u]),get(t[u]-a[i]));
    }
    
    cout<<q.top().first<<endl;
    dfs(get(q.top().first));
    for(int i=1;i<=m;i++)cout<<vis[i];
    return 0;
}


```

---

## 作者：IGA_Indigo (赞：0)

## 题目大意
有 $n$ 个人依次被 $k$ 个人面试，一个面试完了下一个继续面试，如果有两个面试官同时面试完那么下一个人去哪都可能，问第一个没有下一个面试人的面试官面试完的最小时间和可能是哪几个面试官。
## 大体思路
我们首先开一个优先队列，用来存面试结束时间，进行一些贪心，附加的，建立一个 $endd$ 数组，用来存储这个面试官的结束时间，用优先队列存储 $endd$ 数组，每一个 $endd$ 对标一个 $hs$ 回溯数组，存储这个面试官还没面试当前面试人的 $endd$，最后直接输出最小的那个面试官结束时间，用 `map` 存所有最优解的回溯数组，从后往前遍历，每次查到 `map` 是真值的时候再让 map 记录当前查到的这个点的回溯数组，一直遍历面试官到 $i\le k$ 也就是当前面试官在面试第一个人的情况，标记这个面试官，最后输出标记即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
priority_queue<long long,vector<long long>,greater<long long>> q;
long long kk[300005],a[300005],endd[300005],hs[300005];
unordered_map<long long,bool> mp;//因为数据比较大所以我们可以开 map 
bool vis[300005];
int main(){
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=k;i++){
		endd[i]=a[i];//初始化 end 为自己这头牛 
		q.push(a[i]);
	}
	for(int i=k+1;i<=n;i++){
		long long x=q.top();
		q.pop();
		hs[i]=x;//回溯数组变成没面试这头牛的 end 的大小 
		endd[i]=x+a[i];//end 时间自然变大 
		q.push(x+a[i]);//结束时间存到小根堆里。 
	}
	cout<<q.top();
	puts("");
	mp[q.top()]=1;
	for(int i=n;i>=1;i--){//从后往前查找 hs 数组 
		if(mp[endd[i]]){
			mp[hs[i]]=1;//加到回溯数组里去，一直到只有一个牛的时候，否则要接着往下走
			if(i<=k){
				vis[i]=1;//如果是一个牛的情况而且是最优解之一，就标记 
			} 
		}
	}
	for(int i=1;i<=k;i++){//输出标记的 
		if(vis[i]){
			cout<<1;
		}
		else{
			cout<<0; 
		} 
	}
	return 0;
}
```

---

## 作者：Jerrywang09 (赞：0)

赛时想到了并查集，正解是优先队列。

将前 $k$ 头牛入队。每层循环内，找到等效的面试官编号，用 $vec$ 临时记录；用 $record$ 记录每一层的 $vec$。给接下来的 $|vec|$ 头牛分配面试官。

第二问的本质是什么？假如面试官 $i$ 可以面试 Bessie，某一层循环中 $i,j$ 是等效的，可以相互替换，那么 $j$ 就可以面试 Bessie。

考虑回溯求得答案。倒着循环层数 $i$，有一位面试官 $x\in record_i$ 又已知 $x$ 可以面试 Bessie，则所有的 $y\in record_i$ 都可以。

```cpp
// Title:  Bessie's Interview
// Source: USACO24OPEN Silver
// Author: Jerrywang
#include <bits/stdc++.h>
#define F first
#define S second
#define pii pair<ll, int>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cerr<<#x<<":"<<x<<endl;
const int N=300010;
using namespace std;

int n, k, res[N]; ll a[N];
priority_queue<pii, vector<pii>, greater<pii>> q;
vector<vector<int>> record;

int main()
{
    #ifdef Jerrywang
    freopen("E:/OI/in.txt", "r", stdin);
    #endif
    scanf("%d%d", &n, &k);
    rep(i, 1, n) scanf("%lld", a+i);
    rep(i, 1, k) q.push({a[i], i});
    int cur=k;
    while(1)
    {
        ll x=q.top().F;
        vector<int> vec;
        while(q.size() && q.top().F==x)
            vec.push_back(q.top().S), q.pop();
        if(cur+vec.size()>n)
        {
            printf("%lld\n", x);
            for(int i:vec) res[i]=1;
            break;
        }
        record.push_back(vec);
        for(int i:vec) q.push({x+a[++cur], i});
    }
    for(int i=record.size()-1; i>=0; i--)
    {
        bool ok=0;
        for(int j:record[i]) if(res[j]) ok=1;
        if(!ok) continue;
        for(int j:record[i]) res[j]=1;
    }
    rep(i, 1, k) printf("%d", res[i]);
    
    return 0;
}
```

---

