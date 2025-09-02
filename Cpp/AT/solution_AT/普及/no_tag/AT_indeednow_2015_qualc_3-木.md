# 木

## 题目描述

[problemUrl]: https://atcoder.jp/contests/indeednow-qualb/tasks/indeednow_2015_qualc_3

木とは、頂点とそれを結ぶ辺からなる構造「グラフ」の $ 1 $ 種で、頂点の数を $ N $ 個とすると、辺は $ N-1 $ 本あり、どの頂点も他の全ての頂点に辺で間接・直接的につながっています。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_indeednow_2015_qualc_3/db302ed5e6211ee095f87c2aa4b931b136442faf.png)

この問題では、頂点は $ N $ 個あり、$ 1 $ から $ N $ まで番号付けられています。

木が与えられたとき、以下の操作で作られる数列のうち、辞書順で最小のものを出力してください。

1. 頂点1を選ぶ。
2. 今まで選ばれた頂点と辺で結ばれている頂点のうち、まだ選ばれていない頂点を1つ選ぶ、という操作を選ばれていない頂点が無くなるまで繰り返す。
3. 頂点の番号を選ばれた順に並べた数列を作る。

ただし、長さ $ N $ の列 $ A=\{a_1,a_2,\ ...,a_N\} $ と $ B=\{b_1,b_2,\ ...,b_N\} $ に対し、辞書順で $ A $ が $ B $ より小さいとは、

- $ i\ で\ a_i $=$ b_i $
- $ i\ =\ k $ で $ a_i $b\_i

となるような $ k(1≦k≦N) $ が存在するということです。

## 说明/提示

### 部分点

この問題には部分点が設定されている。

- $ 50 $ 点分のテストケースにおいて、 $ 1\ ≦\ N\ ≦\ 3,000 $ を満たす。

### Sample Explanation 1

問題文中の図の木です。 まず、初めに頂点 $ 1 $ を選びます。 !\[\](http://indeednow-qualb.contest.atcoder.jp/img/other/indeednow-qualb/C\_sample2.png) 次に、頂点 $ 3 $ を選びます。頂点 $ 2 $ は今まで選んだ頂点(この場合、頂点 $ 1 $ のみ)と辺で結ばれていないので、選ぶことができないことに注意してください。 !\[\](http://indeednow-qualb.contest.atcoder.jp/img/other/indeednow-qualb/C\_sample3.png) 次に、頂点 $ 2 $ を選びます。 !\[\](http://indeednow-qualb.contest.atcoder.jp/img/other/indeednow-qualb/C\_sample4.png) 次に、頂点 $ 4 $ を選びます。 !\[\](http://indeednow-qualb.contest.atcoder.jp/img/other/indeednow-qualb/C\_sample5.png) 頂点の番号を選んだ順に並べると、$ 1 $ $ 3 $ $ 2 $ $ 4 $ となります。この列より辞書順で小さい選び方は存在しません。

## 样例 #1

### 输入

```
4
1 3
1 4
2 3```

### 输出

```
1 3 2 4```

## 样例 #2

### 输入

```
6
1 2
2 3
2 6
6 4
1 5```

### 输出

```
1 2 3 5 6 4```

## 样例 #3

### 输入

```
7
1 5
5 2
5 3
5 7
5 6
6 4```

### 输出

```
1 5 2 3 6 4 7```

# 题解

## 作者：RioFutaba (赞：1)

## 题意
给一颗树，从点 $1$ 开始，每次选一个与当前访问过的点有边相连的点进行访问直到没有点可以访问，求一种访问顺序，使访问的点按访问顺序排成序列字典序最小。
## 思路
显而易见，这个访问过程就是一个裸的 bfs。关键在于如何使访问序列的字典序最小。

进行贪心，每次都在能访问的点里选择编号最小的点访问即可。

注意输出答案时最后不能输出空格并且要输出换行。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn=2e5+5;
int n,head[maxn],ne[maxn],to[maxn],tot;
void add(int u,int v){
	to[++tot]=v;
	ne[tot]=head[u];
	head[u]=tot;
}//加边 
bool vis[maxn];
void solve(){
	vector<int> ans;
	priority_queue< int,vector<int>,greater<int> > q;//小根堆 
	q.push(1);vis[1]=1;
	while(!q.empty()){
		int u=q.top();
		ans.push_back(u);//记录答案 
		q.pop();
		for(int i=head[u];i;i=ne[i]){
			int v=to[i];
			if(!vis[v]){
				q.push(v);
				vis[v]=1;
			}
		}
	}
	cout << ans[0];
	for(int i=1;i<ans.size();i++) cout << " " << ans[i];//最后一个不能输出空格 
	cout << endl;//ATcoder经典换行 
}
int main(){
	cin >> n;
	for(int i=1,u,v;i<n;i++){
		cin >> u >> v;
		add(u,v);
		add(v,u);
	}
	solve();
	return 0;
}
```

---

## 作者：静静是他的， (赞：1)

题目描述是：

首先 **选择结点1** 开始,

然后通过 **边** 选择结点或选择 **已经** 到达过的结点，

这样就会得到 **按照选择结点的顺序** 的序列，

求这样的序列中 **字典序最小** 的序列。

思路：

使用 **链式前向星** 存边，从结点1遍历每个点,

用一个 **优先队列** 存的是当前到达和之前到达过的结点

在到达一个结点时首先把当前结点记录到答案数组(也可以直接输出)，

找到 到达的 并且 **之前没有到达过的** 结点存入优先队列

因为求字典序最小，所以选出最小的结点，并到达这个结点。

### 还有一个坑点：输出没有多余空格 和 行末要换行

上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN=1001010;//开大点

int n,ct,t;
int first[MAXN],ans[MAXN];
bool pd[MAXN];
struct data{
	int next,to;
}e[MAXN];//前向星,next上一条边,to到达的结点

priority_queue <int,vector<int>,greater<int> >q;//greater 小的优先

void add(int u,int v)
{
	++ct;
	e[ct].to=v;
	e[ct].next=first[u];
	first[u]=ct;
}//建边

void dfs(int u)
{
	ans[++t]=u;//记录到答案数组
	for(int i=first[u];i;i=e[i].next)
		if (!pd[e[i].to]) q.push(e[i].to);//没到达过才加入优先队列
	
	if (!q.empty())//如果还有结点
	{
		int v=q.top();q.pop();//找出最小的结点
		pd[v]=true;//标记到达过
		dfs(v);	
	}
}

int main()
{
	cin>>n;
	for(int i=1;i<n;i++)
	{
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
        //树是无向图建双向边
	}
	
	pd[1]=true;
	dfs(1);
	//从结点1开始,并标记到达
    
	for(int i=1;i<t;i++)
		cout<<ans[i]<<" ";//不能有多余空格
	cout<<ans[t]<<endl;	//行末换行
	return 0;
}
```

---

## 作者：__Creeper__ (赞：0)

## 题目描述

给一棵树，从节点 $1$ 开始，每次选择当前点的子节点中一个没有被选过的点访问，求字典序最小的一种访问顺序。

## 思路

其实这道题非常简单，只需要维护一个优先队列（小根堆），用 bfs 把这棵树遍历一遍即可。

- 注意：输出时行末不能有换行，且要输出换行。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
bool vis[N];
int n, m;
vector<int> ans;
vector<int> G[N]; // 用邻接表存树
priority_queue<int, vector<int>, greater<int> > q; 

void bfs ( int x ) // 对树进行遍历
{
	q.push ( x );
	vis[x] = 1;
	while ( !q.empty() )
	{
		int u = q.top();
		q.pop();
		ans.push_back ( u );
		for ( auto v: G[u] )
		{
			if ( vis[v] ) continue;
			vis[v] = 1;
			q.push ( v );
		}
	}
}

int main()
{
	cin >> n;
	for ( int i = 1; i <= n - 1; i++ )
	{
		int u, v;
		cin >> u >> v;
		G[u].push_back ( v );
		G[v].push_back ( u );
	}
	bfs ( 1 );
	for ( int i = 0; i < ans.size(); i++ ) // 注意输出
	{
		cout << ans[i];
		if ( i != ans.size() - 1 ) cout << ' ';
	}
	cout << '\n';
	return 0;
}
```

---

## 作者：Melo_DDD (赞：0)

半夜闲的来水一题。

做着做着发现这是 Atcoder，然后想起来 $\color{red}{不能有行末空格而且要有换行！}$

# 题目实现

从顶点开始遍历直接链式前向星之后搜索就可以了。

问题在于字典序最小，我们鉴于**字典序是逐位比较的**（这是正确的关键），所以可以考虑贪心（如果当前我们这一步优说明一定整个串优）。

那么如何在当前点的所有儿子节点中选出最小的？不难想到优先队列（准确来说是小根堆），咱们让 C++ 帮咱们排序就好了。相信写迪杰多的同学们肯定深有体会。

开个栈存顺序之后由栈底向栈顶输出即可。

别忘了是无向边。

## 代码：

```cpp
#include <bits/stdc++.h>
#define rep(i ,m ,n ,x) for (int i = (m) ;i <= (n) ;i += (x))
using namespace std ;
const int N = 1e5 + 7 ;
int n ,head[N << 1] ,tot ;
struct edge {
	int to ,nxt ;
}e[N << 1] ; 
namespace shin {
	template <typename T> inline void read (T &x) {
		x = 0 ;
		char ch = getchar () ;
		while (ch < '0' or ch > '9') {
			ch = getchar () ;
		}
		while (ch <= '9' and ch >= '0') {
			x = (x << 1) + (x << 3) + (ch ^ 48) ;
			ch = getchar () ;
		}
	}
	inline void add (int u ,int v) {
		e[++ tot].nxt = head[u] ;
		head[u] = tot ;
		e[tot].to = v ;
	}
	inline void get_ans (int cur) {
		priority_queue <int ,vector <int> ,greater <int> > q ;
		int stk[N] ,stop = 0 ;
		bool instk[N] ;
		memset (instk ,false ,sizeof (instk)) ;
		q.push (cur) ;
		instk[cur] = true ; // 好吧其实这个 instk 和这个栈一点关系没有
		while (! q.empty ()) {
			int now = q.top () ;
			q.pop () ;
			stk[++ stop] = now ;
			for (int i = head[now] ;i ;i = e[i].nxt) {
				int nex = e[i].to ;
				if (instk[nex]) goto her ;
				q.push (nex) ;
				instk[nex] = true ;
				her : ;
			}
		}
		rep (i ,1 ,stop ,1) {
			if (i != stop) cout << stk[i] << " " ;
			else cout << stk[i] << '\n' ;
		}
	}
} 
int main () {
	shin :: read (n) ;
	do {
		int u ,v ;
		shin :: read (u) ;
		shin :: read (v) ;
		shin :: add (u ,v) ;
		shin :: add (v ,u) ;	
	} while (n -- != 2) ;
	return shin :: get_ans (1) ,0 ;
}
//kafka & かみや
```
###### 你是否承认卡芙卡和狼谷的美貌举世无双？

---

## 作者：封禁用户 (赞：0)

因为题目中要求取长度最短的数列，所以考虑使用小根堆来存接下来可以遍历到的点。

从点 $1$ 开始 dfs，先输出，然后每次把没有被遍历到的相邻节点放到小根堆里，标记成已被遍历。如果优先队列非空，再从队头取出一个点（因为最小）dfs，一直重复上面的操作即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
const int N=100005;
vector<int> G[N];
priority_queue<int,vector<int>,greater<int> > pq;
bool vis[N];
int cnt;
void dfs(int u){
	++cnt;
	if(cnt<n) cout<<u<<' ';
	else cout<<u;
	for(auto v:G[u]){
		if(!vis[v]){
			vis[v]=1;
			pq.push(v);
		}
	}
	while(!pq.empty()){
		int tmp=pq.top();
		pq.pop();
		dfs(tmp);
	}
	return ;
}
int main(){
	cin>>n;
	int u,v;
	for(int i=1;i<n;++i){
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	vis[1]=1;
	dfs(1);
	cout<<endl;
	return 0;
} 
```

---

## 作者：awdereye (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_indeednow_2015_qualc_3)
### 本题思路
本题为一道改了调用函数 DFS 题目，题面给定从 1 开始，也就是说**根节点为 1**。但是题目中的边时无向边，所以在用链式前向星是 $(x,y)$ 和 $(y,x)$。都需要储存一遍，同时因为要的是**字典序最小的数列**，所以本题需要用小根堆（优先队列实现），写作 `priority_queue<int,vector<int>,greater<int>>q`。

- 前置知识 `priority_queue<int,vector<int>,greater<int>>q` 是优先队列一种，也叫做小根堆，是用完全二叉树实现的，其子节点永远大于父节点，子树同理。

### 样例注解
[这里](https://cdn.luogu.com.cn/upload/image_hosting/ws6hlnxv.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

从图中顺序为 1 2 3 5 6 4。它是把当前可以到达的点存到小根堆，然后输出第一个元素，第一个出去，把第一个可以到的元素入队，故本题需要额外调用，不能写成以前 `DFS(ver[i])` 的形式。
### 敲响警钟
**本题卡输出**最后一个不能加多余空格并且要换行。
### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
#define nt Next
int n;
priority_queue<int,vector<int>,greater<int>>q;
int head[1001010],ver[1001010],nt[1001010],vis[1001010],cnt=0;
void add(int father,int son){
	//cout<<father<<' '<<son<<endl;
		cnt++;//链式前向星
		ver[cnt]=son;
		nt[cnt]=head[father];
		head[father]=cnt;
	//cout<<ver[cnt]<<' '<<head[father]<<' '<<nt[cnt]<<endl;
}
void DFS(int x,int n){
		if(n==1){
			cout<<q.top()<<endl;//特判是否最后一个
			return ;
		}
		cout<<q.top()<<' ';
		q.pop();
		for(int i=head[x];~i;i=nt[i]){
			if(vis[ver[i]]==0){
				q.push(ver[i]);
			}
		}
		if(!q.empty()){
			vis[q.top()]=1;//不为空调用
			DFS(q.top(),n-1);	
		}
		
}
int main(){
		memset(head,-1,sizeof(head));
		cin>>n;
		for(int i=1;i<n;i++){
			int x,y;
			cin>>x>>y;
			add(x,y);
			add(y,x);
		}
		q.push(1);//根入堆
		vis[1]=1;
		DFS(1,n);
		return 0;
}
```

---

## 作者：KυρωVixen (赞：0)

## 题意：
给你一棵树，重复这样一个过程，直到每个点都访问过：从没有访问过的，与访问过的点直接相连的点中选一个点访问。第一次访问点 $1$。

按照访问顺序排列点的编号，可以形成一个“访问序列”，求字典序最小的可能的访问序列。

## 解法：
其实这个题难点主要在理解题面。直接维护一个小根堆随后 bfs 即可。

## 代码：
```cpp
#include<bits/stdc++.h>
#define psb push_back
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pqueue(a) priority_queue<a,vector<a>,greater<a>>
using namespace std;
const int N=1e5+5;
int n,vis[N]; vector<int>ans,G[N]; pqueue(int)q;
signed main(){
	cin>>n;
	rep(i,2,n){
		int u,v; cin>>u>>v;
		G[u].psb(v); G[v].psb(u);
	}
	q.push(1);
	while(!q.empty()){
		int u=q.top(); q.pop();
		if(vis[u]) continue; 
		vis[u]=1; ans.psb(u);
		for(auto v:G[u]) if(!vis[v]) q.push(v);
	}
	rep(i,0,n-1){
		if(i) cout<<" ";
		cout<<ans[i];
	}
	cout<<endl;
}
```

---

## 作者：cyhyyds (赞：0)

## 思路：
看到数据规模 $n$ 为 $10^5$，那么做法应该就是带一个 $\log$。

对于当前点，枚举与其连接的所有边，将没有存入过的存入堆中。

每次取出堆顶输出即可。

$AT$ 的坑点！！！

最后一个数后面不能加空格，要换行。

所以我将输出的答案存在一个队列中最后输出。

## 代码：
```
#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 7;

struct EDGE {
	int nxt;
	int to;
}e[N];

int head[N], _ = 0, n;

queue<int> ans;

inline void add (int u, int v) {
	e[++ _].nxt = head[u];
	e[_].to = v;
	
	head[u] = _;
}

bool used[N];

priority_queue<int> q;

int main () {
	cin >> n;
	
	for (int i = 1; i < n; i ++) {
		int u, v;
		
		cin >> u >> v;
		
		add (u, v);
		add (v, u);
		//双向边。 
	}
	
	q.push (-1);
	//大根堆存负数。 
	
	used[1] = true;
	
	while (!q.empty()) {
		int u = -q.top();
		
		ans.push (u);
		
		q.pop ();
		
		for (int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			
			if (used[v] == false) {
				q.push (-v);
				
				used[v] = true;
			}
		}
	}
	
	for (int i = 1; i < n; i ++) {
		cout << ans.front () << " ";
		
		ans.pop (); 
	}
	
	cout << ans.front () << endl;
	
	return 0;
}
```


---

## 作者：Violet___Evergarden (赞：0)

~~手写堆要失传了嘛~~，我来手写一下~
# 思路：
用 dfs，若此时在 $a$ 点，就将与 $a$ 相连且没有到达过得几个点入堆，取出最小的点 $x$，再 dfs $x$点。
# CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
struct EDGE
{
	int nt,to;
}e[1000001];
int hd[1000001],edge;
int n;
int ans[1000001],rans[1000001],rcnt,cnt;
bool v[1000001],v2[1000001];
int hp[1000001],sum;
void Add(int a,int b)
{
    e[++edge].to=b;
    e[edge].nt=hd[a];
    hd[a]=edge;
}
void Up(int x)
{
	while(x/2)
	{
		int now=x;
		x/=2;
		if(hp[x]>hp[now])swap(hp[x],hp[now]);
		else break;
	}
}
void Down(int x)
{
	while(x*2<=sum)
	{
		int now=x;
		x*=2;
		if(x+1<=sum&&hp[x+1]<hp[x])x++;
		if(hp[x]<hp[now])swap(hp[x],hp[now]);
		else break;
	}
}
void Push(int x)
{
	hp[++sum]=x;
	Up(sum); 
}
void Pop(int x)
{
	swap(hp[x],hp[sum]);
	sum--;
	Down(x);
}
void dfs(int d)//搜索
{
	if(v[d]==false)return;
	ans[++cnt]=d;
	for(int i=hd[d];i;i=e[i].nt)
	{
		//cout<<e[i].to<<" ";
		if(v[e[i].to]==false&&e[i].to!=0)
		{
			Push(e[i].to);//入堆
		}
	}
	while(sum)
	{
		v[hp[1]]=true;
		int x=hp[1];
		Pop(1);
		dfs(x);
	}
}
int main()
{
cin>>n;
for(int i=1;i<n;i++)
{
	int x,y;
	cin>>x>>y;
	Add(x,y);
	Add(y,x);
}
v[1]=true;
dfs(1);
for(int i=1;i<=cnt;i++)
{
	if(v2[ans[i]]==false)rans[++rcnt]=ans[i];//如果该点没有被记到答案中就记录，过滤重复的
	v2[ans[i]]=true;
}
for(int i=1;i<=rcnt;i++)
{
	if(i==1)cout<<rans[i];
	else cout<<" "<<rans[i];
}
cout<<endl;
return 0;
}

---

## 作者：Graphcity (赞：0)

这道题实际上就是 bfs 的一个简单应用。

在 bfs 的过程中，那些与已选中点相连的未选中点已经在队列中了，而题目需要要求字典序最小，所以我们只需要把普通队列改成**优先队列**就可以了。

这个题目的坑点：

- 输出需要注意 。

- STL 里面的优先队列默认是从大到小放置的，所以我们加入和取出一个数时要记得 **乘上 -1** 。

- 这棵树是 **无根树** 。

```cpp
#include<bits/stdc++.h>
#include<queue>
#define Maxn int(1e5)
using namespace std;

struct Node//邻接表 
{
	int to,nxt;
} Edge[(Maxn<<1)+5];
int Head[Maxn+5],tot;

inline void Addedge(int x,int y)//加边 
{
	Edge[++tot].to=y;
	Edge[tot].nxt=Head[x];
	Head[x]=tot;
}

priority_queue<int> q;//优先队列 
int n,vis[Maxn+5];//vis数组用来判断是否选中 

inline void bfs(int x)//跟一般的bfs差不多 
{
	if(x!=1) printf(" ");
	printf("%d",x);
	vis[x]=1;
	for(register int i=Head[x];i;i=Edge[i].nxt)
	{
		int y=Edge[i].to;
		if(vis[y]) continue;
		q.push(-y);
	}
	if(!q.empty())
	{
		int now=-q.top();
		q.pop();
		bfs(now);
	}
}

int main()
{
	scanf("%d",&n);
	for(register int i=1;i<n;++i)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		Addedge(a,b);
		Addedge(b,a);
	}
	bfs(1);
	printf("\n");
    return 0;
}

```


---

