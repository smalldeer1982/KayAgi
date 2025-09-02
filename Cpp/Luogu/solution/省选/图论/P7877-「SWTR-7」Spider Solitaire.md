# 「SWTR-7」Spider Solitaire

## 题目背景

#### 题目描述下方有简化题意。

![](https://cdn.luogu.com.cn/upload/image_hosting/7tdo8cdf.png)

---

小 A 在玩蜘蛛纸牌。  
为了方便你理解蜘蛛纸牌，小 A 给出了简化后的游戏规则：

- 一副牌有 $n$ 张，从小到大分别为 $1,2,\cdots,n$。
- 现有 $m$ 个牌堆，$1$ 副牌。每个牌堆中有 $0$ 张或多张牌。
- 定义「龙」$a_1,a_2,\cdots,a_d$ 为满足 $a_i-1=a_{i+1}\ (1\leq i<d)$ 的任意多张连续的牌。**一张牌也是一个「龙」。**
- 一组连续的牌可以移动，当且仅当这组牌形成了一个「龙」，且「龙」在牌堆的**最右边**。
- 一组连续的牌只能移动到一个**非空**牌堆的最右边，**且必须满足可以与该非空牌堆最右边的「龙」构成一条更大的「龙」**。
- 游戏胜利，当且仅当所有的 $n$ 张牌形成了一个「龙」。

---

例如当 $m=3$，$n=9$，局面为

```plain
9 8 4 3 2 1
7 5
6
```

时，第一个牌堆最右边的 `4 3 2 1` 形成了一个「龙」，所以 `4 3 2 1` 可以移动。将 `4 3 2 1` 移动到第二个牌堆的最右边，此时局面为

```plain
9 8
7 5 4 3 2 1
6
```

接下来将第二个牌堆右边的 `5 4 3 2 1` 移动到第三个牌堆的最右边，此时局面为

```plain
9 8
7
6 5 4 3 2 1
```

接下来将第三个牌堆的 `6 5 4 3 2 1` 移动到第二个牌堆的最右边，此时局面为

```plain
9 8
7 6 5 4 3 2 1
\
```

接下来将第二个牌堆的 `7 6 5 4 3 2 1` 移动到第一个牌堆的最右边，此时牌堆为

```plain
9 8 7 6 5 4 3 2 1
\
\
```

因为所有 $9$ 张牌形成了一个「龙」，所以游戏胜利。

## 题目描述

给定一个蜘蛛纸牌初始局面，小 A 想知道能否获得胜利。若能，请输出 $\texttt{YES}$ 以及**获胜所需的最小步数**。否则输出 $\texttt{NO}$。

小 A 还想知道，对于每张牌 $i$，如果要移动 $i$ 至少需要多少步，**包括移动 $i$ 的这一步**。如果无法移动输出 `-1`。

---

#### 「简化题意」

有 $m$ 个**横向**的数堆，数堆里共有 $n$ 个数，每个数堆里有 $0$ 或多个数。所有数堆里的数组成了 $1\sim n$ 中的所有数。

你可以将一个数堆**最右边递减且公差为 $-1$ 的**连续若干个数 $a_1,a_2,\cdots,a_c$ **按照原来的顺序移到另外一个非空数堆的最右边**，当且仅当该非空数堆最右边的一个数 $b=a_1+1$。

求将所有的 $n$ 个数都移动到同一个数堆且满足从左往右依次递减的最小步数。如果无解输出 $\texttt{NO}$。

**此外，你还需要对于每个数 $i$，输出如果要移动 $i$ 至少需要多少步。**

## 说明/提示

**「样例 1 说明」**

因为 1,2,3,4,5 可以直接移动，所以至少需要 1 步即可移动。  
因为需要先将 5 移至 6 右侧，6 才能移动，所以至少需要 2 步即可移动。  
因为需要先将 5 移至 6 右侧，再将 4,3,2,1 移至 5 右侧，7 才能移动，所以至少需要 3 步即可移动。  
显然 8,9 无法移动。

**「Special Judge」**

本题使用 Special Judge，请**严格遵守输出格式**：

- 如果你正确输出对能否获胜的判定，且如果能够获胜，你正确输出最小步数，你将获得该测试点**至少** $40\%$ 的分数。
- **在上一部分的基础上**，如果你正确输出移动每张牌的最小步数，你将获得该测试点**剩下** $60\%$ 的分数。也就是说，如果你上一部分输出错误，你在这一部分也不会获得任何分数。
- **如果你的输出格式错误，你将获得该测试点 $0\%$ 的分数**，包括但不限于**只输出对能否获胜的判定**。
- 需要特别注意的是，如果你不能正确求出移动每张牌的最小步数，请**随机输出 $[-1,n]$ 之间的任意整数**，否则你将获得该测试点 $0\%$ 的分数。
- 每行结束后你都需要输出换行符，**包括最后一行**。

checker 将在题目最后给出。

**「数据范围与约定」**

**本题采用捆绑测试。**

- Subtask #0（0 points）：是样例。
- Subtask #1（15 points）：$n\leq 3\times 10^3$，$m=2$。
- Subtask #2（15 points）：$b_i>b_{i+1}\ (1\leq i<c)$，$n\leq 3\times 10^3$。
- Subtask #3（25 points）：$n\leq 14$，$m=3$。
- Subtask #4（30 points）：$n\leq 3\times 10^3$。
- Subtask #5（15 points）：无特殊限制。

对于 $100\%$ 的数据，$1\leq n,m\leq 5\times 10^4$。时间限制 1s，空间限制 512MB。

**「题目来源」**

[Sweet Round 07](https://www.luogu.com.cn/contest/51773) D。  
idea & solution & data：[Alex_Wei](https://www.luogu.com.cn/user/123294)；验题：[chenxia25](https://www.luogu.com.cn/user/138400)。

---

以下是 checker，你需要有 testlib.h 才能成功编译。

```cpp
#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define pii pair <int,int>
#define fi first
#define se second
#define pb emplace_back
#define mp make_pair 
#define vint vector <int>
#define vpii vector <pii>
#define all(x) x.begin(),x.end()
#define sor(x) sort(all(x))
#define rev(x) reverse(all(x))
#define mem(x,v) memset(x,v,sizeof(x))

#define rint inf.readInt
#define reof inf.readEof()
#define reoln inf.readEoln()
#define rspace inf.readSpace()

// wrong answer : quitf(_wa,"The answer is wrong")
// accepted :  quitf(_ok,"The answer is correct")
// partly correct : quitp(0.5,"The answer is partly correct")

int main(int argc,char* argv[]){
	registerTestlibCmd(argc,argv);
	
	string jans=ans.readToken();
	string pans=ouf.readToken(jans);
	int sub=rint(),n=rint(),diff=0;
	
	if(jans=="YES"){
		int jstep=ans.readInt();
		int pstep=ouf.readInt();
		if(jstep!=pstep)quitf(_wa,"The answer is wrong");
	}
	
	for(int i=1;i<=n;i++){
		int jans=ans.readInt();
		int pans=ouf.readInt();
		if(jans!=pans)diff=1;
	}
	
	while(!ouf.seekEof())ouf.readToken();
	while(!inf.seekEof())inf.readToken();
	while(!ans.seekEof())ans.readToken();
	if(diff)quitp(0.4,"The answer is partially correct");
	else quitf(_ok,"OK, you AK IOI");
	
	return 0;
}
```

## 样例 #1

### 输入

```
0
9 3
6 9 8 4 3 2 1
2 7 5
1 6
```

### 输出

```
YES
4
1
1
1
1
1
2
3
-1
-1
```

## 样例 #2

### 输入

```
0
13 4
4 13 10 1 7
3 11 4 8
4 6 5 3 2
2 12 9
```

### 输出

```
YES
10
2
2
2
3
3
3
1
1
3
6
7
8
-1
```

## 样例 #3

### 输入

```
0
5 1
5 5 4 3 2 1
```

### 输出

```
YES
0
-1
-1
-1
-1
-1
```

## 样例 #4

### 输入

```
0
17 10
2 12 14
1 3
3 1 13 15
0
2 9 8
1 5
3 16 7 6
2 11 2
1 4
2 17 10
```

### 输出

```
YES
14
4
1
1
1
1
1
1
1
1
2
3
4
3
1
2
4
-1```

## 样例 #5

### 输入

```
0
13 4
4 10 1 13 7
4 11 12 4 8
4 6 5 3 2
1 9
```

### 输出

```
NO
-1
2
2
3
3
3
1
1
-1
-1
6
5
-1
```

# 题解

## 作者：gyh20 (赞：10)

考虑移动的一个过程，每次让原本不相邻的 $x$ 和 $x+1$ 变得相邻，也就是说，我们可以把每一条极长「龙」（即同一列中 $a_i=x+1,a_{i+1}=x$ 的极长连续段）缩在一起，称为一个点，则每次移动后点数 $-1$，也就是说如果有解，那么步数一定是点数 $-1$。

现在先是如何判定有解，应该可以通过暴力找所有可移动的点移动来实现模拟的效果，但这样难写，并且对第二问帮助不大。

考虑建出如下一个图，$i\rightarrow j$ 存在表示 $i$ 需要在 $j$ 之前移动，那么这样的边又分为两种：

$1.$ $i$ 同一牌堆，且比 $i$ 更靠右的点需要先被移开才能移动 $i$。

$2.$ 假设 $i$ 需要移动到的位置是 $x$，则与 $x$ 同一牌堆，且比 $x$ 更靠右的点需要先被移开才能把 $i$ 移到 $x$ 后方。

这两种建边都可以直接后缀优化建图做到 $O(n)$ 的复杂度。

则有解当且仅当这个图是一个 DAG。

第二问的答案也很明显，即对于 $x$ 所对应的点考虑有多少 DAG 上的点可达它，可以直接使用 bitset 做到 $O(\dfrac{n^2}{w})$，注意拓扑排序删不掉的点答案是 $-1$，以及最后一个点（即 $n$ 所属的点）答案为 $-1$。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int n,m,fa[50002],sum,px[50002],py[50002],mx[50002],head[50002],cnt,low[50002],d[50002],S,ed[50002],lst;
vector<int>V[50002];
queue<int>q;
bitset<50002>B[50002];
struct edge{int to,next;}e[100002];
inline void add(re int x,re int y){e[++cnt]=(edge){y,head[x]},head[x]=cnt;++d[y];}
inline int root(re int x){return x==fa[x]?x:fa[x]=root(fa[x]);}
int main(){
	read();
	n=read(),m=read();
	for(re int i=1;i<=n;++i)fa[i]=i,ed[i]=i;
	for(re int i=1;i<=m;++i){
		re int x=read();
		while(x--)V[i].push_back(read());
		for(re int j=1;j<V[i].size();++j)if(V[i][j]==V[i][j-1]-1)fa[V[i][j]]=V[i][j-1],ed[root(V[i][j])]=V[i][j];
		if(V[i].size())lst=V[i][0];
		for(re int j=1;j<V[i].size();++j)if(fa[V[i][j]]==V[i][j])add(V[i][j],lst),lst=V[i][j];
		for(re int j=0;j<V[i].size();++j)px[V[i][j]]=i,py[V[i][j]]=j; 
	}
	for(re int i=1;i<=n;++i)sum+=fa[i]==i;
	for(re int i=1;i<=m;++i)mx[i]=0;
	for(re int i=1;i<=m;++i){
		for(re int j=0;j<V[i].size();++j)
			if(fa[V[i][j]]==V[i][j]&&V[i][j]!=n){
				re int x=ed[root(V[i][j]+1)];
				if(py[x]==V[px[x]].size()-1)continue;
				x=V[px[x]][py[x]+1];
				add(x,V[i][j]);
			}
	}
	for(re int i=1;i<=n;++i)if(!d[i])q.push(i);
	while(!q.empty()){
		re int x=q.front();q.pop();++S;B[x][x]=1;
		if(x==n)continue;
		for(re int i=head[x];i;i=e[i].next){
			B[e[i].to]|=B[x];
			if(!--d[e[i].to])q.push(e[i].to);
		}
	}
	re int ss=0;
	for(re int i=1;i<=n;++i)ss|=d[i];
	if(ss)puts("NO");
	else puts("YES"),printf("%d\n",sum-1);
	B[n].reset();
	for(re int i=1;i<=n;++i){
		re int x=root(i);
		if(!B[x].count()||d[x])puts("-1");
		else printf("%d\n",B[x].count());
	}
}
```


---

## 作者：Graphcity (赞：5)

显然对于牌堆中连续的一组数应该一起被移走，这样整个牌组就被分成了几个部分。对于样例一是这样：

```
9 8 / 4 3 2 1
7 / 5
6
```

对于第 $i$ 个部分，设 $fa_i$ 表示牌堆中在它上面的那个部分（ 如果没有则 $fa_i=0$ ），$link_i$ 表示它应该移到这个部分的上面。$fa_i$ 让每个部分连成了一棵树，$link_i$ 则让每个部分连成了一条链。

下面是样例一中的 $fa$ 树和 $link$ 链：

![](https://cdn.luogu.com.cn/upload/image_hosting/xlj7z8if.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/t979at4e.png)

设 $f_i$ 表示结点 $i$ 代表的部分是否可以到达牌堆的最顶端，$g_i$ 表示是否可以被移走，则有

$$
\begin{aligned}
f_i &=g_{fa_i} \\
g_i &=f_i \land f_{link_i}
\end{aligned}
$$

这个可以用一遍 bfs 解决。如果能够获胜，那么除了最大的那一部分，其它部分都需要被移走，$g$ 值应该为真。每一次移动都会有一部分被移走，所以最小的歩数为部分的数量减去 1。

对于第二问，求出第 $i$ 部分至少需要多少步被移走，也就是问要移走 $i$ 就至少需要移走几个部分。

若要移走 $i$，那么 $i$ 的上面，也就是 $fa_i$ 必须要先被移走。同时，$link_i$ 的上面，也就是 $fa_{link_i}$ 也需要被移走。枚举结点，用 dfs 标记需要移走的点并统计数量，时间复杂度 $O(n^2)$，可以获得 85pts 的好成绩。

考虑优化。建一张新图，对于每个点 $i$，用单向边连接到 $fa_i$ 和 $fa_{link_i}$，那么需要被移走的点数就等于新图中从 $i$ 出发可以到达的点数。

对于可以被移走的点建图后必然不会出现环，否则就会有 “它被移走之前先要移走自己” 的情况。所以拓扑排序并用 bitset 统计即可。时间复杂度 $O(\dfrac{n^2}{w})$，可以获得满分。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=5e4;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int T,n,m,s,ans=1,h[Maxn+5],ind[Maxn+5];
int siz[Maxn+5],fa[Maxn+5],lnk[Maxn+5],pre[Maxn+5],g[Maxn+5];
int id[Maxn+5],L[Maxn+5],R[Maxn+5],vis[Maxn+5],flag[Maxn+5];
vector<int> crd[Maxn+5],v[Maxn+5],w[Maxn+5];
bitset<Maxn+5> bst[Maxn+5];

inline void bfs() // 判断是否可以获胜
{
    queue<int> q; while(!q.empty()) q.pop();
    q.push(0),vis[0]=1;
    while(!q.empty())
    {
        int x=q.front(); q.pop();
        if(flag[x]) continue;
        flag[x]=1;
        for(auto y:v[x])
        {
            vis[y]=1;
            if(vis[y] && vis[lnk[y]]) q.push(y);
            if(vis[pre[y]] && vis[y]) q.push(pre[y]);
        }
    }
}
inline void dfs(int x) // 统计可达点的数量
{
    bst[x][x]=1;
    for(auto y:w[x])
    {
        if(bst[y].none()) dfs(y);
        bst[x]|=bst[y];
    }
}

int main()
{
    T=read(),n=read(),m=read();
    For(i,1,m) // 划分点
    {
        siz[i]=read();
        For(j,1,siz[i]) crd[i].push_back(read());
        crd[i].push_back(0);
    }
    For(i,1,m)
        Rof(j,siz[i]-1,0)
        {
            if(crd[i][j]==1 || crd[i][j]!=crd[i][j+1]+1) s++,L[s]=crd[i][j],fa[s]=id[crd[i][j+1]];
            id[crd[i][j]]=s,R[s]=crd[i][j];
        }
    For(i,1,s) v[fa[i]].push_back(i); // 连边
    For(i,1,n-1) if(id[i]!=id[i+1]) lnk[id[i]]=id[i+1],pre[id[i+1]]=id[i];
    lnk[id[n]]=n+1;
    bfs();
    For(i,1,s) if(i!=id[n]) ans&=flag[i];
    if(ans) printf("YES\n%d\n",s-1);
    else printf("NO\n");
    For(i,1,s) // 建新图
    {
        if(fa[i]) w[i].push_back(fa[i]),ind[fa[i]]++;
        if(fa[lnk[i]]) w[i].push_back(fa[lnk[i]]),ind[fa[lnk[i]]]++;
    }
    For(i,1,s) if(!ind[i]) dfs(i);
    For(i,1,s) g[i]=(flag[i]?bst[i].count():-1);
    For(i,1,n) printf("%d\n",g[id[i]]);
    return 0;
}
```

---

## 作者：Nuisdete (赞：1)

首先在原牌堆中就已经连续的牌一定不会再拆开了，可以缩起来。

考虑一张牌能够移动的条件：

- 压着它的牌都能够移动；

- 压着 **比它恰好大一的牌** 的牌都能够移动；

注意 $n$ 不可移动。

这样我们根据 **$a, b, c \cdots$ 能够移动， $x$ 才能移动** 分别建出 $a, b, c \cdots \to x$ 的边。

显然游戏有解当且仅当图是一个 DAG，而最少步数就是缩后的牌数 $- 1$（大小为 $n$ 的牌不需要移动）。

然后就可以用拓扑排序判断游戏是否有解，同时顺便用 `bitset` 维护出第二问的答案。

瓶颈在于 `bitset` 维护第二问的答案，时间复杂度为 $\mathcal{O}(\frac{n^2}{\omega})$。

注意输出要求。

```cpp
# include <cstdio>
# include <vector>
# include <bitset>

const int MAXN = 5e4 + 5;

int n, m;

std::vector<int> vec[MAXN << 1], G[MAXN << 1];

int fa[MAXN << 1];
int mp[MAXN << 1], nxt[MAXN << 1], val[MAXN << 1];

int deg[MAXN << 1];

int que[MAXN << 1], *hd = que, *tl = que;

std::bitset<MAXN> bit[MAXN];

int main() {
	
	int T, id = 0;
	scanf("%d %d %d", &T, &n, &m);
	for (int i = 1; i <= n; ++i) fa[i] = i;
	for (int i = 1; i <= m; ++i) {
		int x;
		scanf("%d", &x), vec[i].resize(x);
		for (int j = 0; j < x; ++j) 
			id ++, scanf("%d", &vec[i][j]), mp[ vec[i][j] ] = id, val[id] = vec[i][j];
	}
	id = 0, deg[ mp[n] ] = 1;
	for (int i = 1; i <= m; ++i) {
		if (!vec[i].empty()) id ++;
		for (int j = 1; j < vec[i].size(); ++j) {
			id ++;
			if (vec[i][j] == vec[i][j - 1] - 1) fa[id] = fa[id - 1];
			else G[id].push_back(fa[id - 1]), nxt[ fa[id - 1] ] = id, deg[ fa[id - 1] ] ++;
		}
	}
	id = 0;
	for (int i = 1; i <= m; ++i) {
		for (int j = 0; j < vec[i].size(); ++j) {
			id ++;
			if ((!j || vec[i][j] != vec[i][j - 1] - 1) && nxt[ fa[ mp[ vec[i][j] + 1 ] ] ]) 
				G[ nxt[ fa[ mp[ vec[i][j] + 1 ] ] ] ].push_back(id), deg[id] ++;
		}
	}
	int tot = 0;
	for (int i = 1; i <= n; ++i) 
		if (fa[i] == i) ++tot, bit[i].set(i);
		
	for (int i = 1; i <= n; ++i)
		if (fa[i] == i && deg[i] == 0) *tl ++ = i;
	
	while (hd != tl) {
		int u = *hd ++;
		for (int k : G[u]) {
			deg[k] --, bit[k] |= bit[u];
			if (deg[k] == 0) *tl ++ = k;
		}
	}
	bool flg = true;
	for (int i = 1; i <= n; ++i)
		if (val[i] != n && fa[i] == i && deg[i]) flg = false;
	
	puts(flg ? "YES" : "NO");
	if (flg) printf("%d\n", tot - 1);
	for (int i = 1; i <= n; ++i) 
		printf("%d\n", deg[ fa[ mp[i] ] ] ? -1 : bit[ fa[ mp[i] ] ].count());
	
	return 0;
}
```


---

## 作者：lyhqwq (赞：0)

# Solution

好题，被薄纱了。

由于一张牌只有一种，所以已经组成龙的若干张牌可以压缩为一张。经典套路建图，$i \to j$ 表示 $i$ 需要在 $j$ 之前移动，分为两种情况。

一种是 $i$ 上面的牌需要在 $i$ 前面移动，一种是 $i+1$ 上面的牌需要在 $i$ 前面移动，用类似拆点的套路进行建图可以做到 $O(n)$。

对于合法的情况，图一定是一个 DAG。我们跑拓扑，如果最后不存在环那么合法。移动步数的计算可以考虑 bfs，用 bitset 可以做到 $O(\frac{n^2}{\omega})$。

注意 $n$ 不能移动。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e4+5;
struct edge{
	int v,nxt;
}edge[N<<1];
int head[N],cnt;
int _;
int n,m,ans;
int fa[N],nxt[N],deg[N];
int posx[N],posy[N];
vector<int> vec[N];
queue<int> q;
bitset<N> f[N];
int find(int x){
	return x==fa[x]?x:fa[x]=find(fa[x]);
}
void addedge(int u,int v){
	edge[++cnt].v=v,edge[cnt].nxt=head[u],head[u]=cnt;
	deg[v]++;
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	scanf("%d",&_);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1,x,v;i<=m;i++){
		scanf("%d",&x);
		while(x--) scanf("%d",&v),vec[i].push_back(v);
		for(int j=0;j<vec[i].size();j++) posx[vec[i][j]]=i,posy[vec[i][j]]=j;
		for(int j=0;j<vec[i].size();j++){
			if(j&&vec[i][j]==vec[i][j-1]-1){
				fa[vec[i][j]]=vec[i][j-1];
				nxt[find(vec[i][j])]=j+1;
			}
			else nxt[vec[i][j]]=j+1;
		}
		if(!vec[i].size()) continue;
		int pre=vec[i][0];
		for(int j=nxt[vec[i][0]];j<vec[i].size();j=nxt[vec[i][j]]){
			addedge(vec[i][j],pre);
			pre=vec[i][j];
		}
	}
	for(int i=1;i<n;i++){
		if(fa[i]==i){
			if(posy[i+1]==vec[posx[i+1]].size()-1) continue;
			addedge(vec[posx[i+1]][posy[i+1]+1],i);
		}
	}
	for(int i=1;i<=n;i++) if(!deg[i]) q.push(i);
	while(!q.empty()){
		int u=q.front();
		q.pop(); 
		f[u][u]=1;
		if(u==n) continue;
		for(int i=head[u];i;i=edge[i].nxt){
			int v=edge[i].v;
			f[v]|=f[u];
			if(!(--deg[v])) q.push(v);
		}
	}
	int ok=1;
	for(int i=1;i<=n;i++) if(deg[i]) ok=0;
	if(!ok) puts("NO");
	else{
		for(int i=1;i<=n;i++) ans+=(fa[i]==i);
		puts("YES");
		printf("%d\n",ans-1);
	}
	for(int i=1;i<=n;i++){
		int u=find(i);
		if(u==n||deg[u]) puts("-1");
		else printf("%d\n",f[u].count());
	}
	return 0;
}

```

---

