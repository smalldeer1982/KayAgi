# [ABC224D] 8 Puzzle on Graph

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc224/tasks/abc224_d

高橋君は道端であるパズルを拾いました。  
 このパズルは、$ 9 $ 個の頂点と $ M $ 本の辺からなる無向グラフ、および、$ 8 $ つのコマで構成されます。

グラフの $ 9 $ つの頂点はそれぞれ頂点 $ 1 $、頂点 $ 2 $、$ \ldots $、頂点 $ 9 $ と呼ばれ、 $ i\ =\ 1,\ 2,\ \ldots,\ M $ について、$ i $ 番目の辺は頂点 $ u_i $ と頂点 $ v_i $ を結んでいます。  
 $ 8 $ つのコマはそれぞれコマ $ 1 $、コマ $ 2 $、$ \ldots $、コマ $ 8 $ と呼ばれ、 $ j\ =\ 1,\ 2,\ \ldots,\ 8 $ について、コマ $ j $ は頂点 $ p_j $ に置かれています。 ここで、すべてのコマはそれぞれ異なる頂点に置かれていることが保証されます。 コマが置かれていない「空の頂点」がただ一つ存在することに注意してください。

高橋君はこのパズルに対して下記の操作を好きな回数（ $ 0 $ 回でもよい）だけ行うことができます。

> 空の頂点に隣接する頂点に置かれたコマを $ 1 $ つ選び、選んだコマを空の頂点に移動する。

高橋君は上記の操作を繰り返して、このパズルを「完成」させようとしています。 パズルは、下記の状態を満たしたときに完成となります。

> $ j\ =\ 1,\ 2,\ \ldots,\ 8 $ について、コマ $ j $ は 頂点 $ j $ に置かれている。

高橋君がパズルを完成させることが可能かどうかを判定し、可能な場合はそのために必要な操作回数の最小値を出力してください。

## 说明/提示

### 制約

- $ 0\ \leq\ M\ \leq\ 36 $
- $ 1\ \leq\ u_i,\ v_i\ \leq\ 9 $
- 与えられるグラフは多重辺、自己ループを持たない
- $ 1\ \leq\ p_j\ \leq\ 9 $
- $ j\ \neq\ j'\ \Rightarrow\ p_j\ \neq\ p_{j'} $
- 入力はすべて整数

### Sample Explanation 1

下記の手順によって、$ 5 $ 回の操作でパズルを完成させることができます。 1. コマ $ 2 $ を頂点 $ 9 $ から頂点 $ 1 $ に移動する。 2. コマ $ 3 $ を頂点 $ 2 $ から頂点 $ 9 $ に移動する。 3. コマ $ 2 $ を頂点 $ 1 $ から頂点 $ 2 $ に移動する。 4. コマ $ 1 $ を頂点 $ 3 $ から頂点 $ 1 $ に移動する。 5. コマ $ 3 $ を頂点 $ 9 $ から頂点 $ 3 $ に移動する。 一方、$ 5 $ 回未満の操作でパズルを完成させることはできません。よって、$ 5 $ を出力します。 与えられるグラフは連結とは限らないことに注意してください。

### Sample Explanation 2

パズルは初めから完成しています。よって、完成させるために必要な操作回数の最小値は $ 0 $ 回です。

### Sample Explanation 3

操作の繰り返しによってパズルを完成させることができないので、$ -1 $ を出力します。

## 样例 #1

### 输入

```
5
1 2
1 3
1 9
2 9
3 9
3 9 2 4 5 6 7 8```

### 输出

```
5```

## 样例 #2

### 输入

```
5
1 2
1 3
1 9
2 9
3 9
1 2 3 4 5 6 7 8```

### 输出

```
0```

## 样例 #3

### 输入

```
12
8 5
9 6
4 5
4 1
2 5
8 9
2 1
3 6
8 7
6 5
7 4
2 3
1 2 3 4 5 6 8 7```

### 输出

```
-1```

## 样例 #4

### 输入

```
12
6 5
5 4
4 1
4 7
8 5
2 1
2 5
6 9
3 6
9 8
8 7
3 2
2 3 4 6 1 9 7 8```

### 输出

```
16```

# 题解

## 作者：SunburstFan (赞：3)

### D - 8 Puzzle on Graph

#### 题目大意

给定一个 $9$ 个顶点，$m$ 条边的图，共有八个棋子分别在 $p_1,p_2,p_3...p_8$，问最终能否让第 $i$ 个棋子放在 $i$ 号节点上。

#### 解题思路

考虑与[八数码](https://www.luogu.com.cn/problem/P1379)相同的做法。

将九个顶点对应的状态**压缩成一个九位数**，即每个定点上对应了哪个棋子。

令第 $i$ 个定点上最开始的棋子编号是 $r_i$，没有棋子的顶点 $u$ 的 $r_u$ 为 $9$，就能够生成初始状态。

然后将这个九位数压入队列，跑 BFS 求解，再用一个 map 记录，最后判断能否达到 $123456789$ 这个状态。

生成初始状态部分：

```cpp
string str="999999999"; //一开始都没有摆棋子
for(int i=1,pos;i<=8;i++){
    cin>>pos;
    str[pos-1]=i+'0'; //读入第 i 个棋子的位置后替换相应位置
}
```

BFS 部分：

```cpp
mp[str]=1;
q.push(str);

while(!q.empty()){
    str=q.front();
    q.pop();

    int u=1;
    for(int i=0;i<9;i++){
        if(str[i]=='9'){
            u+=i; //找到没有棋子的顶点的位置
            break;
        }
    }

    for(auto v:G[u]){
        string n_str=str;
        swap(n_str[u-1],n_str[v-1]);
        
        if(mp[n_str]){
            continue;
        }

        mp[n_str]=mp[str]+1;
        q.push(n_str);
    }
}

if(!mp["123456789"]) cout<<-1<<"\n"; //如果没有走过，就说明无法到达
else cout<<mp["123456789"]-1<<"\n";
```

---

## 作者：wang_freedom (赞：2)

### 思路
八数码游戏，但是在图上。

对于每次操作，将空格与周围相连接的棋子交换，然后对能转移到的每种状态编码。

所以从初始状态开始 bfs 是正确的，将新转移到的状态的编码后插入队列，如果一个状态的编码已经被访问则不扩展新的状态，这样可以保证每个状态最多入队一次，出队一次，所以时间复杂度即为总状态数。当所有状态都扩展后仍未到达目标状态则说明无解。

复杂度为 $O(n\times n!)$，其中 $n$ 最大为 $9$，可以通过此题。
### AC Code
```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define endl '\n'
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
int m,d;
vector<int>vec[305];
map<string,int>mp;
queue<string>q;
string s="#000000000";
signed main(){
	cin.tie(0);cout.tie(0);std::ios::sync_with_stdio(0);
	cin>>m;
	rep(i,1,m){
		int u,v;
		cin>>u>>v;
		vec[u].push_back(v);
		vec[v].push_back(u);
	}
	rep(i,1,8){
		cin>>d;
		s[d]=i+48;
	}
	q.push(s);
	while(q.size()){
		string t=q.front();
		q.pop();
		if(t=="#123456780"){
			cout<<mp[t];
			return 0;
		}
		int d=mp[t],id=t.find(48);
		for(int v:vec[id]){
			swap(t[v],t[id]);
			if(mp[t]==0){
				mp[t]=d+1;
				q.push(t);
			}
			swap(t[v],t[id]);
		}
	}
	cout<<-1;
	return 0;
}
/*

*/
```
[AC 记录](https://atcoder.jp/contests/abc224/submissions/me)

---

## 作者：_zzzzzzy_ (赞：1)

# 思路
是一道经典的水题，我们用做八数码游戏的基本套路，用字符串或数字表示八数码的状态，我们对于每一种状态找到空格的位置，然后更新相邻的点并记录状态最小步数，如果这个状态是第一次走到就记录一下并加入 `bfs` 的队列。

稍微算一下复杂度可以知道最多有 $!N$ 种状态，每个格子最多有 $N-1$ 个连边，那么时间复杂度就是 $O(!N \times N)$，最后算一下可以发现这个时间复杂度可过。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=10000;
vector<int>e[maxn];
map<string,int>mp;
signed main(){
	int m;
	cin>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	string S="#000000000";
	for(int i=1;i<=8;i++){
		int d;
		cin>>d;
		S[d]=i+'0';
	}
	queue<string>Q;
	Q.push(S);
	while(Q.size()){
		string tp=Q.front();
		Q.pop();
		if(tp=="#123456780"){
			cout<<mp[tp];
			return 0;
		}
		int d=mp[tp];
		int id=tp.find('0');
		for(int v:e[id]){
			swap(tp[v],tp[id]);
			if(mp[tp]==0){
				mp[tp]=d+1;
				Q.push(tp);
			}
			swap(tp[v],tp[id]);
		}
	}
	cout<<-1;
	return 0;
}
```

---

## 作者：Tairitempest (赞：0)

## 	[ABC224D] 8 Puzzle on Graph
最多存在 $9!$ 即约为 $3.6×10^5$ 状态数，考虑将每个状态压成一个 long long 整数并使用搜索解决。对于一个棋子，其最多有 $9$ 种位置，因此每个棋子占据一位，每一位存储其所在点的编号。

dfs 会浪费很多状态更新，建议使用 bfs。搜索的时候读取队列中 long long 整数中存储的状态信息，并根据状态信息找出空出来的位置，更新棋子位置和状态步数，并将这些状态转换成 long long 整数放入队列。最后查询完成状态的步数就可以了。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll m,u,v,J[12];
vector<ll> e[12];
unordered_map<ll,ll> cache;
queue<ll> q;
ll t[12];
void code2graph(ll N){
	memset(J,0,sizeof J);
	ll res=0;
	for(ll i=8;i>=1;i--){
		J[i]=N%13;
		N/=13;
	}
}
ll graph2code(){
	ll res=0;
	for(ll i=1;i<=8;i++){
		res*=13;
		res+=J[i];
	}
	return res;
}
int main(){
	cin>>m;
	for(int i=1;i<=m;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for(int i=1;i<=8;i++)
		cin>>J[i];
	ll pc=graph2code();
	q.push(pc);
	cache[pc]=0;
	while(!q.empty()){
		pc=q.front();
		q.pop();
		code2graph(pc);
		memset(t,0,sizeof t);
		for(int i=1;i<=8;i++)
			t[J[i]]=i;
		ll tmp=0;
		for(int i=1;i<=9;i++)
			if(t[i]==0) tmp=i;
		for(int i=0;i<e[tmp].size();i++){
			ll nxt=e[tmp][i];
			ll p=t[nxt],ori=J[p];
			J[p]=tmp;
			ll newpc=graph2code();
			if(!cache.count(newpc)){
				q.push(newpc);
				cache[newpc]=cache[pc]+1;
			}
			J[p]=ori;
		}
	}
	for(int i=1;i<=8;i++)
		J[i]=i;
	pc=graph2code();
	if(cache.count(pc)==0) cout<<-1<<endl;
	else cout<<cache[pc]<<endl;
	return 0;
}
```

---

## 作者：Hughpig (赞：0)

这不是我们[八数码难题](https://www.luogu.com.cn/problem/P1379)吗？

类似八数码难题做个状态压缩，把每个位置上的数压缩到一个数 $state$ 里。显然目标状态为 $123456780$。用 `map` 记录某个状态是否被访问以及被到达该状态的最少步数。

然后从初始状态开始 BFS。遍历每条边，如果某条边连接的两个位置中某个位置没有数，就把某个数移到空位置，然后把新的状态压缩一下继续 BFS。

时间复杂度 $O(m\times n!)$，实际上跑的飞快。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define up(l,r,i) for(register int i=(l);i<=(r);++i)


ll m,u[44],v[44];

ll s[11],state;
map<ll,ll> vis; 

void bfs(){
	queue<ll> q;
	q.push(state);
	vis[state]=0;
	while(q.size()){
		state=q.front();
		ll _s=state; 
		q.pop();
		if(state==123456780)cout<<vis[state]<<'\n',exit(0);
		for(int i=9;i;--i)s[i]=state%10,state/=10;
		up(1,m,i){
			ll _u=u[i],_v=v[i];
			if(s[_u]!=0&&s[_v]!=0)continue;
			swap(s[_u],s[_v]);
			state=0;
			up(1,9,i)state=state*10+s[i];
			if(!vis.count(state)){
				vis[state]=vis[_s]+1;
				q.push(state);
			}
			swap(s[_u],s[_v]);
		}
	}
	cout<<-1;
}

int main(){
	cin>>m;
	up(1,m,i){
		cin>>u[i]>>v[i];
	}
	up(1,8,i){
		int x;cin>>x;
		s[x]=i;
	}
	up(1,9,i)state=state*10+s[i];
	bfs();
}
```

---

## 作者：Happy_mouse (赞：0)

# [8 Puzzle on Graph](https://www.luogu.com.cn/problem/AT_abc224_d) 题解
[AC 证明](https://www.luogu.com.cn/record/173602695)
## 分析与解答
扫一眼，欸，这不[八数码](https://www.luogu.com.cn/problem/P1379)么？

定睛一看，欸，还真不是。

定睛再一看，欸，做法好像差不多。

求最少步数而且数据范围不太大（$N=9$），BFS 无疑了。

至于去重，一共八个棋子九个点，把每个棋子的位置存下来，转成十进制（一枚棋子一位数）即可。

详见代码。
## 代码
```cpp
//里面有一些地方系循环利用变量，可以改改
//我比较节约……
#include <bits/stdc++.h>
using namespace std;
#define int long long
vector<int>v[10];
int p[10],m,x,y,k,sum,cnt,sp,num,step;
void add(int x,int y){//加边
	v[x].push_back(y);
	v[y].push_back(x);
}
bool vis[100000000];//去重
struct nd{
	int space,number,step;
	//分别存空格位置，对应数字（上文解释过）和步数
};
queue<nd>q;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	//输入
	cin>>m;
	while(m--) cin>>x>>y,add(x,y);
	k=1,sum=0,cnt=0;
	for(int i=1;i<=8;i++) cin>>x,sum+=x*k,k*=10,cnt+=x;
	//BFS 主体
	q.push({45-cnt,sum,0});
	//45-cnt 这个应该看的懂吧
	//从 1 加到 9 一共 45，用这个减去存在的和就是空格的位置
	vis[sum]=1;
	while(q.size()){
		sp=q.front().space,num=q.front().number,step=q.front().step;
		q.pop();
		//输出最小步数
		//注意，棋番号越小，对应位数越低
		//因此下面判断是 87654321 而不是 12345678
		if(num==87654321){
			cout<<step;
			return 0;
		}
		//寻找下一项
		for(auto to:v[sp]){
			int nw=num;
			//设现在第i枚棋子在to位置
			//k求的是该棋子所在位数
			k=1;
			while(nw){
				if(nw%10==to) break;
				k*=10;
				nw/=10;
			}
			int r=num%k;//比i位数小的留下
			int much=num/(k*10)*(k*10);//比 i 位数大的留下
			nw=sp*k+r+much;//第 i 位变成空格原本所在位置（sp）
			if(!vis[nw]){//如果没遍历过该情况
				vis[nw]=1;//则进行标记
				q.push({to,nw,step+1});//并放入队列
			}
		}
	}
	//无解情况
	cout<<-1;
	return 0;
}
```

---

## 作者：A1C3 (赞：0)

# [ABC224D] 8 Puzzle on Graph

观察到本题数据范围较小，可以使用 bfs 算法。

将题目中的边用链式前向星存下来。将队列定义为结构体类型，一个存位置，一个存答案，并将队列以答案为关键字从小到大排序，这样取出的第一个符合要求的答案即为最小值。每次取出队首，使用一个标记数组判断当前哪个顶点没有棋子。遍历每一个点，查看当前点是否有一条边连接没有棋子的那个点。如果有，就查看移动棋子后的位置是否在之前出现过，如果没有，就将该位置标记，以后不再出现，并将其入队。

细节实现：如何判断当前位置是否“解开谜题”？如何判断移动棋子后该位置是否之前出现过？可以使用一个哈希映射。将当前所有棋子的位置映射为一个八位数，易证明每一个棋子的位置排列都有且仅有一个八位数与之对应，且不同的棋子位置映射成的八位数一定不同。“解开谜题”时的位置即为 $12345678$。可以使用 bool 数组标记，具体实现见代码中的 calc 函数。

## AC Code

```cpp
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
const int N = 47, M = 1e8 + 7;
int m;
int hd[N], pos[N];
bool vis[M], flag[N];
struct Edge { int to, nx; } eg[N<<1];
struct Node {
	int p, res;
	bool operator< (const Node &B) const {
		return res > B.res;
	}
};
inline void addE(int u, int v, int c) {
	eg[c] = {v, hd[u]}, hd[u] = c;
}
int calc(int a[N]) {
	int res = 0;
	for (int i = 1; i <= 8; ++i)
		(res *= 10) += a[i];
	return res;
}
void bfs() {
	priority_queue<Node> que;
	que.push({calc(pos), 0});
	vis[calc(pos)] = true;
	while (!que.empty()) {
		int qp = que.top().p, qres = que.top().res; que.pop();
		if (qp == 12345678) {
			printf("%d", qres);
			exit(0);
		}
		memset(flag, false, sizeof flag);
		string u = to_string(qp);
		int to;
		for (size_t i = 0; i < u.size(); ++i)
			flag[u[i]-'0'] = true;
		for (int i = 1; i <= 9; ++i)
			if (!flag[i]) { to = i; break; }
		for (size_t i = 0; i < u.size(); ++i) {
			for (int j = hd[u[i]-'0']; j; j = eg[j].nx) {
				int v = eg[j].to;
				if (v != to) continue;
				string hs = u;
				hs[i] = v+'0';
				if (vis[stoi(hs)]) continue;
				vis[stoi(hs)] = true;
				que.push({stoi(hs), qres+1});
			}
		}
	}
}
int main() {
	scanf("%d", &m);
	for (int i = 1, u, v; i <= m; ++i) {
		scanf("%d%d", &u, &v);
		addE(u, v, i<<1), addE(v, u, i<<1|1);
	}
	for (int i = 1; i <= 8; ++i)
		scanf("%d", pos + i);
	bfs();
	puts("-1");
	return 0;
}
```

---

## 作者：PikachuQAQ (赞：0)

## Description

[Link](https://www.luogu.com.cn/problem/AT_abc224_d)

## Solution

这个题的突破口就是将转移压缩到棋子编号然后广搜。

先将点 $1\sim9$ 的棋子编号取出来，没有棋子就看作 $0$。像这样的状态我们记作 $A_i$，这个初始状态记作 $A_0$。输入 #1 的 $A_0 = 031456782$。

可以想到，如果某个节点没有棋子，那么周围连边的点上的棋子都可以移到这个点。换句话说，原来的 $A$ 上的 $0$ 就可以与 其他连边的下标的棋子互换位置，花费为 $1$。

还是 $A_0 = 031456782$，如果点 $1$ 和点 $2$ 有边，那么这个 $A$ 就可以变成 $A_1 = 301456782$。

那么对于 $A_0$，记其花费为 $0$，找到 $A_0$ 中 $0$ 的位置，然后将其与这个 $0$ 连边的棋子编号互换位置，就能产生新状态，这些状态花费为 $1$。

以此类推，$A_i$ 的花费为 $x$，同理产生新状态（这个状态没有被遍历过），新状态的花费为 $x+1$。这实际上是一个广搜的过程。

最后找到目标状态 $A_t=123456780$ 的花费，没有被记录过输出 $-1$ 即可。

## Code

```cpp
// PikachuQAQ 2024/06/21

#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 11;
const string M = "123456780";

int n;
vector<int> g[kMaxN];
unordered_map<string, int> b, vis;
queue<string> q;
string s0 = "000000000";

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 0, u, v; i < n; i++) {
        cin >> u >> v, u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1, x; i <= 8; i++) {
        cin >> x, s0[x - 1] = i + '0';
    }
    q.push(s0), vis[s0] = 1, b[s0] = 0;
    for (int u, d; q.size(); ) {
        string s = q.front(); q.pop();
        u = s.find('0'), d = b[s];
        for (int v : g[u]) {
            string t = s; swap(t[u], t[v]);
            if (vis[t] == 0) q.push(t), vis[t] = 1, b[t] = d + 1;
        }
    }
    cout << (vis[M] ? b[M] : -1);

    return 0;
}
```

---

## 作者：JWRuixi (赞：0)

~~使用 `string` 和 `unordered_map` 还妄图拿最有解？~~

- 题意

就是在图上的八数码。

- 分析

八数码经典套路，考虑可以将一张图压缩成一个 $9$ 位数，直接在图上 `bfs` 就可以了。

讲一下优化，首先直接跑太慢了，考虑可以从起点和终点同时跑，让它们在中间会合，减少一半常数。同时讲一下科技 `__gnu_pbds::gp_hash_table`，它是 `pbds` 自带的哈希表，使用方法和 `map` 一摸一样，而且常数优势显著（~~虽然不如手写~~）。

总复杂度 $\mathcal O(n!\times n)$。

- code

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#define LL long long
#define writesp(x) write(x), putchar(' ')
#define writeln(x) write(x), putchar('\n')
#define FileIO(ch) freopen(ch".in", "r", stdin), freopen(ch".out", "w", stdout)
using namespace std;

namespace IO {
    char ibuf[(1 << 20) + 1], *iS, *iT;
#if ONLINE_JUDGE
#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
#else
#define gh() getchar()
#endif
    inline long long read() {
        char ch = gh();
        long long x = 0;
        bool t = 0;
        while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
        while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
        return t ? ~(x - 1) : x;
    }
    template <typename _Tp>
    inline void write(_Tp x) {
    	static char stk[64], *top = stk;
        if (x < 0) {
            x = ~(x - 1);
            putchar('-');
        }
        do *top++ = x % 10, x /= 10;
        while (x);
        while (top != stk) putchar((*--top) | 48);  
    }
}

using IO::read;
using IO::write;

int n, p[15];
vector<int> G[15];
__gnu_pbds::gp_hash_table<int, int> vis, d;

inline int enc () {
	int x = 0;
	for (int i = 1, j = 1; i < 10; i++, j *= 10) x += p[i] * j;
	return x;
}
inline void dec (int x) {
	for (int i = 1; i < 10; i++, x /= 10) p[i] = x % 10;
}

int main() {
	n = read();
	for (int i = 1; i <= n; i++) {
		int u = read(), v = read();
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	for (int i = 1; i < 9; i++) p[read()] = i;
	queue<int> q;
	q.push(enc()), d[enc()] = 0, vis[enc()] = 1;
	q.push(87654321), d[87654321] = 1, vis[87654321] = 2;
	if (enc() == 87654321) return puts("0"), 0;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		dec(u);
		int pos = 0;
		for (int i = 1; i < 10; i++) if (!p[i]) { pos = i; break; }
		for (int v : G[pos]) {
			swap(p[v], p[pos]);
			int x = enc();
			swap(p[v], p[pos]);
			if (vis[x] + vis[u] == 3) return write(d[x] + d[u]), 0;
			else if (vis[x] == vis[u]) continue;
			q.push(x), d[x] = d[u] + 1, vis[x] = vis[u];
		}
	}
	puts("-1");
}
// I love WHQ!
```

---

## 作者：loser_seele (赞：0)

这题就是一个八数码的板子，不过是改到了图上而已。

考虑对于每次操作，将空格与周围相连接的棋子交换，然后对能转移到的每种状态编码，这里比较懒所以直接用字符串实现，因为这题不是很卡常数所以可以过。

所以从初始状态开始 bfs 是正确的，将新转移到的状态的编码后插入队列，如果一个状态的编码已经被访问则不扩展新的状态，这样可以保证每个状态最多入队一次，出队一次，所以时间复杂度即为总状态数。当所有状态都扩展后仍未到达目标状态则说明无解。

而实际上本质不同的状态即为 $ 1-9 $ 的排列个数为 $ 9!=362880 $，可以通过。

因为字符串比较是 $ \mathcal{O}(n) $ 的，所以总时间复杂度为 $ \mathcal{O}(n! \times n) $，其中 $ n=9 $ 为棋盘大小。本题直接用 map 比较也可以通过，但这里用 unordered_map 实现，能拿到最优解。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
#define int long long
int const N=3e2+10;
vector<int>a[N];
signed main()
{ 
    int n;
    cin>>n;
	for(int i=1;i<=n;i++)
    {
		int u,v;
        cin>>u>>v;
		a[u].push_back(v);
		a[v].push_back(u);
	}
	string s="999999999";
	int p;
    for(int i=1;i<=8;i++)
    {
    cin>>p;
    s[p-1]=i+'0';
    }
	queue<string>q;
    q.push(s);
    unordered_map<string,int>mp;
	mp[s]=1;
	while(!q.empty())
    {
		string s=q.front();
        q.pop();
		int u=0;
		for(int i=0;i<9;i++) 
        if(s[i]=='9') 
        u=i+1;
		for (auto v:a[u])
        {
			string t=s;
            swap(t[u-1],t[v-1]);
			if(mp[t]) 
            continue;
			mp[t]=mp[s]+1;
            q.push(t);
		}
	}
	if(!mp["123456789"]) 
    cout<<"-1";
	else 
    cout<<mp["123456789"]-1;
}
```


---

