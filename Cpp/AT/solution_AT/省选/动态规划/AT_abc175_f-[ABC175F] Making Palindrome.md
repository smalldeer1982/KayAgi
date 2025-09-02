# [ABC175F] Making Palindrome

## 题目描述

### 题目大意

有 $N$ 个仅含小写字母的字符串 $S_1,S_2,\cdots,S_N$。你需要把从这些字符串中选择一些以任意顺序拼接起来，同一个字符串可以被选择多次。每选择一次 $S_i$，你都需要花费 $C_i$ 的代价，也就是说你选择 $S_i$ 所花费的代价为 $C_i$ 与 $S_i$ 被选择的次数之积。求使拼接得到的字符串为回文串所需的最小花费。若不管如何都无法拼接成回文串，输出 `-1`。

数据范围：$1 \le N \le 50$，$1 \le |S_i| \le 20$，$1 \le C_i \le 10^9$。

## 样例 #1

### 输入

```
3
ba 3
abc 4
cbaa 5```

### 输出

```
7```

## 样例 #2

### 输入

```
2
abcab 5
cba 3```

### 输出

```
11```

## 样例 #3

### 输入

```
4
ab 5
cba 3
a 12
ab 10```

### 输出

```
8```

## 样例 #4

### 输入

```
2
abc 1
ab 2```

### 输出

```
-1```

# 题解

## 作者：Illus1onary_Real1ty (赞：3)

我们发现一个性质，任意一个合法的串都可以在两边分别添有字符串后，不断地在已生成的串中间添加字符串构造出来，这就是我们的基本策略。

于是我们引入一个回文字符串题中常见的元素——不平衡元素（Unbalanced elements），以下简称 ub。

如下图所示，以蓝线为界，$ \texttt{qwq}$ 即为 ub。

![](https://cdn.luogu.com.cn/upload/image_hosting/yrurk2nv.png)

通俗来讲，我们将一个字符串分为两半，若某一边靠中间的部分多出了一些元素，这些元素就是 ub。

而对于一个不仅在靠中间的部分多出了一些元素，还在其他部分有不同的串，按照开头提及的策略，无法构造成回文串，因此忽略不计。

特殊地，当 ub 的数量为 $0$ 或 $1$ 时，该字符串是回文串。

我们切入正题。

显然，此题可以通过搜索解决。

我们定义状态 $f_{strnum, side, ublen}$ 表示，目前第 $strnum$ 个字符串的前或后缀是 ub，ub 长度为 $ublen$。

$side$ 为 $0$ 时，第 $strnum$ 个字符串在左边，反之，在右边。

对于搜索转移，任意一个能够抵消掉当前 ub 部分的字符串都可以用于转移。

下一个转移到的状态可以通过分类讨论解决，令 $strnum$ 为 $i$，用于转移的字符串为 $s_j$，则有如下转移：

```cpp
int nxtstr = i, side = 0, nxtub;
if (s[j].length() > ub){
	nxtstr = j;
	side = 1;
	nxtub = s[j].length() - ub;
}else	nxtub = ub - s[j].length();
```

对于判断 $s_j$ 是否能够抵消掉当前 ub 部分，则有如下写法（当 $side = 0$ 时）：

```cpp
int res = min(ub, s[j].length()), flg = 1;
int st = s[i].length() - ub;
for (int k = 0; k < res; k++)
	if (s[i][st+k] != s[j][s[j].length()-1-k]){
		flg = 0;
		break;
    }
```

举个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/pu0p7hyz.png)

暴力搜索显然不可行。

我们想到记忆化搜索，$O(n^4)$ ，可过（由大佬 Eason2009 实现）。

考虑如何使算法更优：

这样无序的转移让我们联想到隐视图，[戳这里看例题](https://www.luogu.com.cn/problem/P1979)。

对于每个状态，我们有如下状态压缩函数：

```
int Get(int str, int side, int ub){
	return str * 2 * 21  + side * 21 + ub;
}
```

当然也有解压函数（用于 Debug）：

```
void release(int x){
	cout << x / 42 << " " << (x%42) / 21 << " " << (x%42) % 21 << endl;
}
```

接着，我们将搜索转移转化为建边。

最后我们使用 Dijkstra 算法，就可以解决问题。

最后考虑细节：

+ 所有 $strnum \ne 0$ 且 $ublen \le 1$ 的状态为终止状态。

+ 建立超级源点，我使用的是 $pt_{0, 0, 0}$。

+ 当剩下的 ub 部分为回文串时，即使 $ublen > 1$ 也是一种终止状态，所以连边到任意一个终止状态。

本文思路大多来自大佬 galen_colin 在油管上发布的视频，在此表示感谢。

最后附上代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 5010;
const int INF = 9e18;
string s, t, s_[55];
int n, maxn, ans, c[55];

struct Edge{
	int to, w;
	
	Edge() {}
	
	Edge(int to_, int w_){
		to = to_;
		w = w_;
	}
};

vector<Edge> g[N];

void Add(int a, int b, int c){
	g[a].push_back(Edge(b, c));
}

struct Node{
	int u, dis;
	
	Node() {}
	
	Node(int u_, int dis_){
		u = u_;
		dis = dis_;
	}
	
	bool operator < (const Node& b) const{
		return dis > b.dis;
	}
};

priority_queue<Node> pq;

int Get(int str, int side, int ub){
	return str * 2 * 21  + side * 21 + ub;
}

void release(int x){
	cout << x / 42 << " " << (x%42) / 21 << " " << (x%42) % 21 << endl;
}

void Init(){
	ans = INF;
	
	for (int i = 1; i <= n; i++){
		int flg = 1;
		
		for (int j = 0; j < s_[i].length() / 2; j++)
			if (s_[i][j] != s_[i][s_[i].length() - j  - 1])
				flg = 0;
		
		if (flg)
			ans = min(ans, c[i]);
	}
}

void Graph_Build(){
	int st = Get(1, 0, 0);
	
	for(int i = 1; i <= n; i++){
		for(int ub = 2; ub <= 21; ub++){
			//加在左边 
			for(int j = 1; j <= n; j++){
				int res = min(ub, (long long)s_[j].length());
				int nxtstr = i, side = 0, nxtub;
				
				if (s_[j].length() > ub){
					nxtstr = j;
					side = 1;
					nxtub = s_[j].length() - ub;
				}else	nxtub = ub - s_[j].length();
				
				int flg = 1;
				int st = s_[i].length() - ub;
				for (int k = 0; k < res; k++)
					if (s_[i][st+k] != s_[j][s_[j].length()-1-k]){
						flg = 0;
						break;
					}
				
				int nxtid = Get(nxtstr, side, nxtub);
				if (flg){
					int curid = Get(i, 0, ub);
					Add(curid, nxtid, c[j]);
				}
				
				int rflg = 1;
				if (s_[j].length() > ub){
					for (int qwq = 0; qwq < nxtub / 2; qwq++)
						if (s_[j][qwq] != s_[j][nxtub-qwq-1])
							rflg = 0;
				}else{
					for (int qwq = 0; qwq < nxtub / 2; qwq++)
						if (s_[i][s_[i].length()-nxtub+qwq] != s_[i][s_[i].length()-qwq-1])
							rflg = 0;
				}
				
				if (rflg)
					Add(nxtid, st, 0);
			}
			
			//加在右边 
			for(int j = 1; j <= n; j++){
				int res = min(ub, (long long)s_[j].length());
				int nxtstr = i, side = 1, nxtub;
				
				if (s_[j].length() > ub){
					nxtstr = j;
					side = 0;
					nxtub = s_[j].length() - ub;
				}else
					nxtub = ub - s_[j].length();
				
				int flg = 1;
				for(int k = 0; k < res; k++)
					if (s_[j][k] != s_[i][ub-1-k]) {
						flg = 0;
						break;
					}
				
				int nxtid = Get(nxtstr, side, nxtub);
				if (flg){
					int curid = Get(i, 1, ub);
					Add(curid, nxtid, c[j]);
				}
				
				int rflg = 1;
				if (s_[j].length() > ub){
					for (int qwq = 0; qwq < nxtub / 2; qwq++)
						if  (s_[j][ub+qwq] != s_[j][s_[j].length()-qwq-1])
							rflg = 0;
				}else{
					for (int qwq = 0; qwq < nxtub / 2; qwq++)
						if (s_[i][qwq] != s_[i][nxtub-1-qwq])
							rflg = 0;
				}
				
				if (rflg)
					Add(nxtid, st, 0);
			}
		}
	}
}

int vis[N], dis[N];
void Dijkstra(){
	for (int i = 0; i <= maxn; i++)
		dis[i] = INF;
	
	dis[0] = 0;
	pq.push(Node(0, 0));
	
	while (!pq.empty()){
		int u = pq.top().u;
		//release(u);
		pq.pop();
		if (vis[u])
			continue;
		vis[u] = 1;
		
		for (auto e : g[u]){
			int to = e.to, w = e.w;
			//release(to);
			if (dis[to] > dis[u] + w){
				dis[to] = dis[u] + w;
				pq.push(Node(to, dis[to]));
			}
		} 
	}
}

signed main(){
	cin >> n;
	maxn = (n + 2) * 2 * 21;
	for (int i = 1; i <= n; i++){
		cin >> s_[i] >> c[i];
		Add(0, Get(i, 0, s_[i].length()), c[i]);
		Add(0, Get(i, 1, s_[i].length()), c[i]);
	}
	
	//for (auto e : g[0])
		//release(e.to);
	
	Init();
	Graph_Build();
	
	Dijkstra();
	
	for (int i = 1; i <= n; i++)
		for (int side = 0; side <= 1; side++)
			for (int ub = 0; ub <= 1; ub++){
				int id = Get(i, side, ub);
				ans = min(ans, dis[id]);
			} 
	
	if (ans == INF)
		return puts("-1"), 0;
	cout << ans << endl;
	
	return 0;
}
```

完结撒花！

---

## 作者：houzhiyuan (赞：2)

设串长之和为 $m$。

从中间开始，在两边塞串，使得中间是匹配的。

那么左边或者右边会多出一段没有匹配的，这一段肯定是一个串的前缀或者后缀。

那么把每个串的前缀后缀设一个状态，就有 $O(m)$ 个状态。

然后跑最短路进行转移。

转移有两种，一种是左边多出一段 $T$，右边塞一个 $S$，$T$ 是 $S$ 的前缀，这样状态转移到 $S$ 多出来的这段。

hash 一下，把左边这段状态连向 $rev(T)$ 的 hash 值，然后一个 hash 值向所有这个 hash 值的串连边，这样总边数 $O(m)$。

还有一种转移是 $|T|>|S|$，也就是 $T$ 还是多出来，只不过长度减少了，注意到所有串的不同长度只有 $\sqrt{m}$ 个，因此对于每个长度找到是否有对应的串转移即可。

也可以根号分治，长度小于根号的暴力，大的串只有根号个暴力即可。

这样点数 $O(m)$，边数 $O(m\sqrt{m})$，跑 dij 的话是 $O(m\sqrt{m}\log m)$，采用斐波那契堆优化就可以做到 $O(m\sqrt{m})$。

代码有点难写的。

[code](https://atcoder.jp/contests/abc175/submissions/46489669)

---

## 作者：luanmenglei (赞：2)

正着考虑平凑出来回文串是困难的，我们考虑倒着做。

如果我们对于最后的回文串每次消去两边更小的剩下的那个串，那么剩下的那个一定是一个前缀或者后缀，并且到最后剩下的某个字符串的前缀/后缀一定是个回文串。

于是考虑建立这样的一个自动机，一个节点对应着一个字符串的前缀或者后缀，自动机上的一条边就代表着删去较小的那个前缀/后缀并且剩下了一个新的前缀/后缀。

那么最小代价其实就是这个图上整串到回文前缀/后缀的最短路。

那么就引出了这样的一个做法，我们建立一个起点和终点，然后将起点向所有整串前缀/后缀，将所有回文前缀后缀向终点连边。转移边直接暴力判断前缀和后缀的消去关系，然后再跑最短路就做完了。

时间复杂度 $\mathcal{O}(n^4+n^3\log n)$。

[https://atcoder.jp/contests/abc175/submissions/45481327](提交记录)

---

## 作者：Fesdrer (赞：0)

我们可以倒着构造出这样一个回文串：先填左右两边的字符串，然后不断地在中间加入新的字符串。

具体的，如果当前我们填写的左右两边的字符串为 $\texttt{abcqwq}$ 和 $\texttt{cba}$，那么左右两边消掉 $\texttt{abc}$ 和 $\texttt{cba}$ 后只剩下靠左的 $\texttt{qwq}$，这样子我们就可以在右边继续填写字符串继续把 $\texttt{qwq}$ 消掉（当然也可能只消掉一部分，比如右边填写 $\texttt{qw}$ 后左边还剩下 $\texttt{q}$）。我们不可能左右两边都剩下字符串，否则这两边的字符串不管中间再怎么填也无法消掉。同时可以发现**右边**剩下的字符串只能是某一个原串的**前缀**，**左边**剩下的字符串只能是某一个原串的**后缀**。

基于以上的思考，我们可以建出一个自动机（或者说是一个有向图），每一个节点都代表一个串的前缀或后缀，另外再加一个起点和终点。每填入一个原串 $S_i$ 就相当于从一个节点以 $c_i$ 的代价转移到另一个节点，转移到终点时即为构造出了回文串。因此只需要求出从起点到终点的**最短路**即可。接下来讲解如何建图：

首先要**特判**：如果一个前缀或后缀本身就是回文串，自然将其以 $0$ 的边权连向终点。否则的话，对于前缀，枚举在左边选择填入的原串 $S_i$，检查能否消掉。前缀和原串 $S_i$ 都被**刚好**消掉则找到回文串，以 $c_i$ 的边权连向终点。如果原串 $S_i$ 被消掉，前缀还剩下更短的前缀没被消掉则以 $c_i$ 的边权连向这一更短的前缀代表的节点，否则 $S_i$ 还剩一部分后缀没被消掉，以 $c_i$ 的边权连向这一后缀代表的节点。最后对每个原串 $S_i$，以 $c_i$ 的代价从起点连向原串 $S_i$ 代表的节点，表示一开始先填入了 $S_i$。

最后计算复杂度，我们不超过 $50$ 个原串，长度不超过 $20$，再区分前缀后缀，因此有不超过 $2000$ 个节点。每个节点有不超过 $50$ 条出边，因此可以通过。

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=55;
int n,c[N],len[N];
char s[N][25];
vector<pair<int,int>> e[2005];
long long dist[2005];
int vis[2005];
priority_queue<pair<long long,int>> q;
void add(int x,int y,int z){
	e[x].push_back({y,z});
}
int gid(int x,int direct,int pal){
	assert((40*(x-1)+20*direct+pal)<=2000);
	return 40*(x-1)+20*direct+pal;
}
void build(int x,int direct,int pal){//0[->  1<-]
	int l=(direct?pal:1),r=(direct?len[x]:pal);
	bool flag=true;
	while(l<r)	flag&=(s[x][l]==s[x][r]),l++,r--;
	if(flag){
		add(gid(x,direct,pal),2001,0);
		return;
	}
	for(int i=1;i<=n;i++){
		bool flag=true;
		if(!direct){
			int j,k;
			for(j=pal,k=1;j>=1&&k<=len[i];j--,k++)	flag&=(s[x][j]==s[i][k]);
			if(flag){
				if(j==0&&k==len[i]+1)	add(gid(x,0,pal),2001,c[i]);
				else if(j==0)	add(gid(x,0,pal),gid(i,1,k),c[i]);
				else	add(gid(x,0,pal),gid(x,0,j),c[i]);
			}
		}
		else{
			int j,k;
			for(j=pal,k=len[i];j<=len[x]&&k>=1;j++,k--)	flag&=(s[x][j]==s[i][k]);
			if(flag){
				if(j==len[x]+1&&k==0)	add(gid(x,1,pal),2001,c[i]);
				else if(j==len[x]+1)	add(gid(x,1,pal),gid(i,0,k),c[i]);
				else	add(gid(x,1,pal),gid(x,1,j),c[i]);
			}
		}
	}
}
void dijkstra(){
	memset(dist,0x3f,sizeof dist);
	memset(vis,0,sizeof vis);
	while(q.size())	q.pop();
	q.push({0,2002}),dist[2002]=0;
	while(q.size()){
		int x=q.top().second;q.pop();
		if(vis[x])	continue;
		vis[x]=1;
		if(x==2001)	return;
		for(auto it:e[x]){
			int y=it.first,z=it.second;
			if(dist[y]>dist[x]+z)	q.push({-(dist[y]=dist[x]+z),y});
		}
	}
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>(s[i]+1)>>c[i],len[i]=strlen(s[i]+1);
	for(int i=1;i<=n;i++){
		add(2002,gid(i,0,len[i]),c[i]),add(2002,gid(i,1,1),c[i]);
		for(int j=1;j<=len[i];j++)	build(i,0,j),build(i,1,j);
	}
	dijkstra();
	if(dist[2001]==0x3f3f3f3f3f3f3f3f)	cout<<-1<<endl;
	else	cout<<dist[2001]<<endl;
	return 0;
}
```

---

