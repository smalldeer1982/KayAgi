# [AGC027C] ABland Yard

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc027/tasks/agc027_c

$ N $ 頂点 $ M $ 本の辺からなる無向グラフが与えられます。 頂点には $ 1 $ から $ N $ の番号が、辺には $ 1 $ から $ M $ の番号がついています。 頂点には番号以外に `A` か `B` のラベルがついており、頂点 $ i $ には $ s_i $ のラベルがついています。

辺 $ i $ は頂点 $ a_i $ と $ b_i $ を双方向につなぐ辺です。

怪盗ヌスークは好きな頂点を始点として選び、そこから $ 0 $ 回以上辺を辿って移動するのが好きです。 今日は移動後に、訪れた頂点についているラベルを始点から訪問した順に並べて文字列を作ることにしました。

例えば、頂点 $ 1 $ にラベル `A` が、頂点 $ 2 $ にラベル `B` がついているグラフにおいて、ヌスークが $ 1\ \rightarrow\ 2\ \rightarrow\ 1\ \rightarrow\ 2\ \rightarrow\ 2 $ と移動した場合、`ABABB` が作られます。

怪盗ヌスークが文字 `A`,`B` のみからなる任意の文字列が作れるかどうかを判定してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^{5} $
- $ 1\ \leq\ M\ \leq\ 2\ \times\ 10^{5} $
- $ |s|\ =\ N $
- $ s_i $ は `A` または `B`
- $ 1\ \leq\ a_i,\ b_i\ \leq\ N $
- 与えられるグラフは単純とも連結とも限らない

### Sample Explanation 1

\- ヌスークは頂点 $ 1 $ と頂点 $ 2 $ を自由に訪れることができるため、`A`,`B` のみからなる任意の文字列が作ることが可能です !\[77e96cf8e213d606ddd8f3c3f8315d32.png\](https://img.atcoder.jp/agc027/77e96cf8e213d606ddd8f3c3f8315d32.png)

### Sample Explanation 2

\- 例えば、`BB` を作ることができません - 与えられるグラフは連結とは限りません !\[1ab1411cb9d6ee023d14ca4e77c4b584.png\](https://img.atcoder.jp/agc027/1ab1411cb9d6ee023d14ca4e77c4b584.png)

## 样例 #1

### 输入

```
2 3
AB
1 1
1 2
2 2```

### 输出

```
Yes```

## 样例 #2

### 输入

```
4 3
ABAB
1 2
2 3
3 1```

### 输出

```
No```

## 样例 #3

### 输入

```
13 23
ABAAAABBBBAAB
7 1
10 6
1 11
2 10
2 8
2 11
11 12
8 3
7 12
11 2
13 13
11 9
4 1
9 7
9 6
8 13
8 6
4 10
8 7
4 3
2 1
8 12
6 9```

### 输出

```
Yes```

## 样例 #4

### 输入

```
13 17
BBABBBAABABBA
7 1
7 9
11 12
3 9
11 9
2 1
11 5
12 11
10 8
1 11
1 8
7 7
9 10
8 8
8 12
6 2
13 11```

### 输出

```
No```

# 题解

## 作者：run_away (赞：2)

## 题意

给定一张无向图，每个点点权为 `A` 或 `B`。求对于每一个由 `A` 和 `B` 组成的字符串 $S$，是否在图中存在一条路径满足路径上的点权连在一起为 $S$，可以重复经过任意一个点和任意一条边。

## 分析

显然我们需要找到一个环，让路径不断重复在上面走。

考虑一个满足条件的最小环，原图只要存在这种环就满足条件，这个环应该满足每个点的后继都存在 `A` 和 `B`。

直接找比较困难，为了简化它，可以考虑把不满足的点去掉。

这个过程类似拓扑排序，对每个点记录它后继中 `A` 和 `B` 的数量，如果有一个为 $0$ 就删去这个点。

如果剩下有点，就说明满足条件，否则不满足。

时间复杂度 $O(n)$。

## Code

```cpp
#include<bits/stdc++.h>
typedef int ll;
using namespace std;
static char buf[100],*p1=buf,*p2=buf,obuf[100],*p3=obuf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,100,stdin),p1==p2)?EOF:*p1++
#define putchar(x) (p3-obuf<100)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x)
mt19937_64 rnd(chrono::system_clock::now().time_since_epoch().count());
#define dbg(x) cout<<#x<<": "<<x<<"\n"
inline ll read(){ll x=0,f=1;char c=getchar();while(c<48||c>57){if(c==45)f=0;c=getchar();}while(c>47&&c<58)x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?x:-x;}
inline void write(ll x){if(!x){putchar(48);putchar('\n');return;}short top=0,s[40];if(x<0)x=-x,putchar(45);while(x)s[top++]=x%10^48,x/=10;while(top--)putchar(s[top]);putchar('\n');}
namespace tobe{
	const ll maxn=2e5+5,mod=998244353;
	ll n,m,cnt[maxn][2];
	string a;
	bool vis[maxn];
	vector<ll>son[maxn];
	inline void mian(){
		n=read(),m=read();
		cin>>a;a=" "+a;
		while(m--){
			ll u=read(),v=read();
			son[u].push_back(v);
			son[v].push_back(u);
			++cnt[u][a[v]-'A'];
			++cnt[v][a[u]-'A'];
		}
		queue<ll>q;
		for(ll i=1;i<=n;++i){
			if(!cnt[i][0]||!cnt[i][1]){
				q.push(i),vis[i]=1;
			}
		}
		while(!q.empty()){
			ll u=q.front();q.pop();
			for(auto v:son[u]){
				if(!--cnt[v][a[u]-'A']&&!vis[v]){
					q.push(v);vis[v]=1;
				}
			}
		}
		ll ans=0;
		for(ll i=1;i<=n;++i)ans+=!vis[i];
		if(ans)puts("Yes");
		else puts("No");
	}
}
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	ll t=1;
	while(t--)tobe::mian();
	fwrite(obuf,p3-obuf,1,stdout);
	return 0;
}
```

---

## 作者：zhylj (赞：2)

## 分析

题目相当于问是否存在一个点集 $V$ 使得 $V$ 导出的子图中的每个点都存在到标有 $\mathtt A,\mathtt B$ 的点的出边。

类似于拓扑排序，考虑每次从图中删除不存在到 $\mathtt A,\mathtt B$ 的出边的点，直到不能删为止，若仍有剩下的点则答案为 ``Yes``，否则为 ``No``.

用一个队列即可维护这个过程，时间复杂度为 $\mathcal O(n)$.

## 代码

```cpp
const int kN = 5e5 + 5;

int n, m, dg[kN][2], typ[kN]; char str[kN];
std::vector <int> E[kN];
void Add(int u, int v) {
	E[u].push_back(v);
	E[v].push_back(u);
	++dg[u][typ[v]];
	++dg[v][typ[u]];
}

std::queue <int> que;
bool vis[kN];
int Calc() {
	int res = n;
	for(int i = 1; i <= n; ++i)
		if(!dg[i][0] || !dg[i][1]) {
			que.push(i); --res;
			vis[i] = true;
		}
	while(!que.empty()) {
		int u = que.front(); que.pop();
		for(auto v : E[u]) {
			--dg[v][typ[u]];
			if(!dg[v][typ[u]] && !vis[v]) {
				que.push(v); --res;
				vis[v] = true;
			}
		}
	}
	return res;
}

int main() { 
	rd(n, m);
	scanf("%s", str + 1);
	for(int i = 1; i <= n; ++i) typ[i] = str[i] - 'A';
	for(int i = 1; i <= m; ++i) {
		int u, v; rd(u, v);
		Add(u, v);
	}
	printf(Calc() > 0 ? "Yes\n" : "No\n");
	return 0;
}
```

---

## 作者：ARIS2_0 (赞：1)

### 思路

下文中称 A 为 $1$，B 为 $0$。

我们称一个节点是**不受限制的**，当且仅当从这个节点可以到达 $0$ 和 $1$。

显然我们一定不能走到受限制的节点，因为如果我们走到了这些节点，我们就不能自己决定下一步是 $0$ 还是 $1$，就不能形成所有合法的串。所以直接把这些节点删除。

因为删除了节点，所以还有可能有新的受限制的节点，还要删除。

如果删到最后有节点留下来了，那这个图就是可行的，否则是不可行的。

使用类似 BFS 的方法维护即可，具体见代码。

### Code

```cpp
#include<algorithm>
#include<bitset>
#include<deque>
#include<iomanip>
#include<iostream>
#include<iterator>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<string>
#include<utility>
#include<vector> 
#include<chrono>
#include<random>
#include<tuple>
#include<unordered_map>
using namespace std;
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define debug1(x) cerr<<#x<<"="<<x<<" "
#define debug2(x) cerr<<#x<<"="<<x<<"\n"
const int inf=1e16,maxn=2e5+10;
int a[maxn],cnt[maxn][2];
vector<int>v[maxn];
bool vis[maxn];
queue<int>q;
void bfs(int n){
	for(int i=1;i<=n;i++){
		if(cnt[i][0]==0 or cnt[i][1]==0){
			vis[i]=1;
			q.push(i);
		}
	}
	while(q.size()){
		int x=q.front();q.pop();
		for(int y:v[x]){
			if(!vis[y]){
				cnt[y][a[x]]--;
				if(cnt[y][a[x]]==0){
					vis[y]=1;
					q.push(y);
				}
			}
		}
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n,m;cin>>n>>m;
	string s;cin>>s;
	for(int i=0;i<n;i++)a[i+1]=(s[i]=='A');
	for(int i=1,p,q;i<=m;i++){
		cin>>p>>q;
		v[p].push_back(q);
		v[q].push_back(p);
		cnt[p][a[q]]++;
		cnt[q][a[p]]++;
	}
	bfs(n);
	bool g=0;
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			g=1;break;
		}
	}
	cout<<(g?"Yes\n":"No\n");
	return 0;
}
/*
clang++ -std=c++14 -Wall -Wextra -Wshadow -Wconversion -Wl,-stack_size -Wl,512000000
*/
```

---

## 作者：igAC (赞：1)

# $\text{Describe}$

[ATlink](https://atcoder.jp/contests/agc027/tasks/agc027_c)

[洛谷 link](https://www.luogu.com.cn/problem/AT_agc027_c)

简要题意：

给定一张无向图，每个点为 ``A`` 或 ``B``。

问是否任何一种仅包含 ``A`` 和 ``B`` 的字符串都能由图上的某条路径表示。

# $\text{Solution}$

首先思考哪些是合法的路径。

首先任何一种字符串，说明可以是无限长的。

所以我们需要的是一个环。那是哪种环呢？

我们需要的是一个 ``AA`` 和 ``BB`` 交替的环，其他的环都是不合法的。

拿最简单的环举例。

![](https://cdn.luogu.com.cn/upload/image_hosting/jd2pfrjn.png)

任何路径要求每个点都要有 ``A`` 和 ``B`` 的出点，显然这样是合法的。

而其他不是 ``AABB`` 交替的环显然都是不合法的。

这样就非常简单了。

我们将一个点拆成两个点，一个点连接与它颜色相同的点，另一个点连接与它颜色不相同的点。

判断是否有环即可。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define N 400005
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int n,m,head[N],tot;
string col;
struct Edge{
	int to,nxt;
}e[N<<1];
void add_edge(int x,int y){
	e[++tot].to=y;
	e[tot].nxt=head[x];
	head[x]=tot;
}
int vis[N];
void dfs(int x){
	if(!(~vis[x])) return;
	vis[x]=1;
	for(int i=head[x];i;i=e[i].nxt){
		int y=e[i].to;
		if(vis[y] && ~vis[y]){
			puts("Yes");
			exit(0);
		}
		dfs(y);
	}
	vis[x]=-1;
}
int main(){
	n=read(),m=read();
	cin>>col;col=" "+col;
	for(int i=1;i<=m;++i){
		int x=read(),y=read();
		if(col[x]==col[y]){
			add_edge(x,y+n);
			add_edge(y,x+n);
		}
		else{
			add_edge(x+n,y);
			add_edge(y+n,x);
		}
	}
	for(int i=1;i<=n+n;++i) dfs(i);
	puts("No");
	return 0;
}
```

---

## 作者：Sampson_YW (赞：0)

咋 *2000 做了 1h 啊。。

手玩一下，举几个例子会发现，要找一个环使得这个环表示的字符串是由 `AABB` 循环若干次得到的。

那么变成了如何在这个无向图上找这样一个环。一个点在环上会有两种可能的状态：不妨设这个点的字符是 `A`，那么它可能是 `AABB` 中的第一个 `A` 或第二个 `A`。`B` 同理。

那么将一个点 $x$ 拆成两个点 $L_x$ 和 $R_x$，分别表示它是第一个/第二个字符。

然后在新图上建边（有向边）。对于原图的一条边 $(x,y)$：

如果 $x$ 和 $y$ 的字符不一样，那么这条边就是 `AB` 或者 `BA`，从某种字符的第二个走到了另一种字符的第一个。于是连边为 $R_x\to L_y$，$R_y\to L_x$。

如果 $x$ 和 $y$ 的字符一样，那么这条边就是 `AA` 或者 `BB`，从某种字符的第一个走到了这种字符的第二个。于是连边为 $L_x\to R_y$，$L_y\to R_x$。

建完图后容易发现如果有环，那么这个环就是 `AABB` 循环若干次得到的。跑拓扑排序判环就行。

[code](https://atcoder.jp/contests/agc027/submissions/48524541)

---

## 作者：IcyFoxer_XZY (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT4377)

~~第一次写 AT 题解，有点激动。~~

#### 废话不多说，进入正题！

这次给拓扑和二分图两种方法啊。

### 分析

对于一个点，如果它的后继只有三种可能：A 、B 或者没有，那么显然它不能在这条路径上。

#### 拓扑：

我们把这样的点删掉。然后我们再判断连向它的点是否要被删掉，以此类推。这样一直删之后，再判断最后是否存在未被删掉的点。

这样做和拓扑排序差不多。

#### 二分图：

由上面的结论也可以看出，路径只能是 AABB 这样的环的排列方式（或者 AABBAABB ...）（这样每个点就存在两种转移）。

AA , AB , BB , BA ，这样的环我们可以通过二分图找，即对于相同字符连一条 $s$ 到 $t$ 的边，不同字符连一条 $t$ 到 $s$ 的边，最后判环。

**拓扑 code：**
```cpp
#include<cctype>
#include<cstdio>
#include<algorithm>
const int N=2e5+1;
int num,head[N],ne[N<<1],to[N<<1];//链式前向星 
int t,q[N],cnt[N][2];
char s[N];
bool del[N];//是否被删除 
inline int read(){
    char ch=getchar();
    int n=0;
    while (ch<'0'||ch>'9')ch=getchar();
    while (ch<='9'&&ch>='0')n=n*10+ch-48,ch=getchar();
    return n;
}
void add(int u,int v){//链式前向星 
	++cnt[u][s[v]-'A'],to[++num]=v,ne[num]=head[u],head[u]=num;
	++cnt[v][s[u]-'A'],to[++num]=u,ne[num]=head[v],head[v]=num;
}
void De(int x){//删除
	if(del[x]||(cnt[x][0]&&cnt[x][1]))return ;
	q[++t]=x,del[x]=1; 
}
int main(){
    int n=read(),m=read();
    scanf("%s",s+1);
    while(m--)add(read(),read());
    for(int i=1;i<=n;++i)De(i);
    for(int i=1;i<=t;++i){
        int x=q[i];
        for(int j=head[x];j;j=ne[j])--cnt[to[j]][s[x]-'A'],De(to[j]);
    }
    puts(t==n?"No":"Yes");//AT必须换行，刚好能用puts 
    return 0;
}
```
**稳居榜首！！！**

后面的二分图不推荐用，跑一遍 dfs 即可，建图也不难，因此代码不贴了。


Bye！


---

## 作者：A_Đark_Horcrux (赞：0)

考虑这样一种极端情况：

```cpp
BBBBBB...A
//不知道多少个B
```
为了使得任意个 B 加上一个 A 组成的字符串都能在原图中被找到，原图中每一个标签为 B 的节点都必须连接着一个标签为 A 的节点，对于 A 节点也相同。

因此，问题转化为：找到原图的一个子图，使得子图中每一个节点都至少有一条到子图内标签为 A 的节点的边，和一条到子图内标签为 B 的节点的边。

具体过程是，记录下每个节点到 A 和 B 出边的条数，每次找到不满足要求的节点，更新其他节点的出边情况，直道无法更新为止。这个过程可以用一个队列维护。

```cpp
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N=2e5+10;
int read()
{
	int s=0; char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') s=s*10+c-'0',c=getchar();
	return s;
}struct edge
{
	int nxt,to;
}a[N*2];
int t,h[N*2],dis[N*2];
void build(int x,int y) {a[++t]=edge{h[x],y},h[x]=t;}
//链式前向星相关操作

//--------------------------------------------------------

int n,m,c,i,j; char s[N]; bool vis[N];
int x[N],y[N],b[N],f[N],out[N][2];
queue<int> q;
int main()
{
	n=read(),m=read();
	scanf("%s",s+1);
	for(i=1;i<=n;i++) b[i]=s[i]-'A';
	for(i=1;i<=m;i++)
	{
		x[i]=read(),y[i]=read();
		build(x[i],y[i]),build(y[i],x[i]);//建边
		out[x[i]][b[y[i]]]++,out[y[i]][b[x[i]]]++;//记录出边
	}
	for(i=1;i<=n;i++)
		if(!out[i][0]||!out[i][1]) vis[i]=1,q.push(i);//不满足的标记，然后进队
	while(!q.empty())//队里还有
	{
		int now=q.front(); q.pop();//先取出队头
		for(j=h[now];j;j=a[j].nxt)//对于每一条边
			if(!vis[a[j].to])//如果连接的节点没有被判断不满足过
			{
				out[a[j].to][b[now]]--;//更新连边情况
				if((!out[a[j].to][0]||!out[a[j].to][1]))//如果不满足了
					vis[a[j].to]=1,q.push(a[j].to);//标记，进队
			}
	}
	for(i=1;i<=n;i++)
		if(!vis[i]) {puts("Yes"); return 0;}//如果还有没被标记的，就是找到子图了。输出Yes
	puts("No"); return 0;//否则输出No
	return 0;
}//完结awa
```


---

