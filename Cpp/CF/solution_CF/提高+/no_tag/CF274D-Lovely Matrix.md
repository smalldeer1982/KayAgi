# Lovely Matrix

## 题目描述

Lenny had an $ n×m $ matrix of positive integers. He loved the matrix so much, because each row of the matrix was sorted in non-decreasing order. For the same reason he calls such matrices of integers lovely.

One day when Lenny was at school his little brother was playing with Lenny's matrix in his room. He erased some of the entries of the matrix and changed the order of some of its columns. When Lenny got back home he was very upset. Now Lenny wants to recover his matrix.

Help him to find an order for the columns of the matrix so that it's possible to fill in the erased entries of the matrix to achieve a lovely matrix again. Note, that you can fill the erased entries of the matrix with any integers.

## 样例 #1

### 输入

```
3 3
1 -1 -1
1 2 1
2 -1 1
```

### 输出

```
3 1 2 
```

## 样例 #2

### 输入

```
2 3
1 2 2
2 5 4
```

### 输出

```
1 3 2 
```

## 样例 #3

### 输入

```
2 3
1 2 3
3 2 1
```

### 输出

```
-1
```

# 题解

## 作者：chenxia25 (赞：4)

难度只有$^*2100$？这难度虚低吧？？只是个蓝题？这是恶评吧？？

我想了足足两个晚上都没想出来，可能是因为我是弱弱吧/kk

>### [洛谷题目页面传送门](https://www.luogu.org/problem/CF274D) & [CodeForces题目页面传送门](https://codeforces.com/contest/274/problem/D)

>给定一个$n\times m$的矩阵$a$，其中$a_{i,j}=-1$表示位置$(i,j)$可以替换成任何数。要求重新排列这$m$列，使得每行都非严格单调递增。输出可能的排列。若有多解，输出任一。若无解，输出$-1$。

>$nm\in\left[1,10^5\right]$。

考虑建一张有向图$G=(V,E)$，路径$x\to y$存在当且仅当第$x$列必须在第$y$列前面。考虑对每行排序，然后会分成若干个相等段。$\forall i$，若第$i$个相等段不都为$-1$，那么第$i$个相等段中每一列和第$i+1$个相等段中每一列都连一条有向边，这样连边正确性显然。最终跑一遍拓扑排序即可。

但是这样很容易被卡成$\mathrm O\!\left(nm^2\right)$的。比如说，每一行都有$\dfrac m2$个数等于$x$，另$\dfrac m2$个数等于$y\neq x$。于是考虑如何优化连边方式使得相等段到相等段之间的连边的复杂度是线性的。其实很简单，只需要套路地虚拟节点优化建图：对于每$2$个要连边的相等段都建一个虚拟节点，然后前面那个相等段的列全部连向虚拟节点，虚拟节点再连向所有后面相等段内的列。这样显然$|E|=\mathrm O(nm)$。需要连边的相等段对数为$\mathrm O(nm)$，虚拟节点数自然也是$\mathrm O(nm)$；再加上表示列们的$m$个节点，$|V|=\mathrm O(nm)$。

下面是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define mp make_pair
#define X first
#define Y second
#define pb push_back
const int N_TIMES_M=100000;
int n,m;//矩阵大小 
int now;//|V| 
vector<int> nei[2*N_TIMES_M+1];//邻接矩阵 
int ideg[2*N_TIMES_M+1];//入度 
vector<int> topo;//拓扑序列 
void toposort(){//拓扑排序 
	queue<int> q;
	for(int i=1;i<=now;i++)if(!ideg[i])q.push(i);
	while(q.size()){
		int x=q.front();
		q.pop();
		topo.pb(x);
		for(int i=0;i<nei[x].size();i++){
			int y=nei[x][i];
			if(!--ideg[y])q.push(y);
		}
	}
}
int main(){
	cin>>n>>m;
	vector<vector<pair<int,int> > > a(n+1,vector<pair<int,int> >(m+1));//矩阵 
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin>>a[i][j].X,a[i][j].Y=j;
	now=m;//初始有表示m列的m个节点 
	for(int i=1;i<=n;i++){
		sort(a[i].begin()+1,a[i].end());//排序 
//		for(int j=1;j<=m;j++)printf("(%d,%d) ",a[i][j].X,a[i][j].Y);puts("");
		vector<pair<int,int> > rg;//相等段们 
		for(int j=1,je;j<=m;j=je+1){//算出有哪些相等段 
			je=j;while(je+1<=m&&a[i][je+1].X==a[i][j].X)je++;
			rg.pb(mp(j,je));
		}
//		for(int j=0;j<rg.size();j++)printf("[%d,%d] ",rg[j].X,rg[j].Y);puts("");
		for(int j=0;j+1<rg.size();j++){//相等段之间连边 
			int l1=rg[j].X,r1=rg[j].Y,l2=rg[j+1].X,r2=rg[j+1].Y;
			if(a[i][l1].X==-1)continue;
			now++;//新建虚拟节点 
			for(int k=l1;k<=r1;k++)nei[a[i][k].Y].pb(now),ideg[now]++;//连边 
			for(int k=l2;k<=r2;k++)nei[now].pb(a[i][k].Y),ideg[a[i][k].Y]++;//连边 
		}
	}
	toposort();//拓扑排序 
	if(topo.size()<now)puts("-1");//不是DAG，无解 
	else for(int i=0;i<topo.size();i++)if(topo[i]<=m)cout<<topo[i]<<" ";//输出解 
	return 0;
}
```

---

## 作者：tzc_wk (赞：4)

> Codeforces 274D

> 给出一个 $n \times m$ 的矩阵 $a$，有一些数是 $-1$，你要重新将这 $m$ 列进行排列，使得存在一种方案：将 $-1$ 替换为某些数，使得这 $n$ 行上的数单调不下降。求一种构造方案，或者宣布无解

> $1 \leq n \times m \leq 10^5$

~~像我这种蒟蒻只配写蓝题题解~~

很显然的一种方案是，将每一列看成一个点，然后对于两列 $i,j$，如果存在一个 $k$ 使得 $a_{k,i} \neq -1$，$a_{k,j} \neq -1$，并且 $a_{k,i}<a_{k,j}$，就连一条 $i \times j$ 的边，表示 $i$ 必须要在 $j$ 的前面。然后跑拓扑排序。

很显然这样是 $m^2$，会被极限数据卡掉。

我们考虑优化。将每一行里面不是 $-1$ 的值压到数组里排序。我们可以把排好序看成是由若干个连续的颜色段组成的。例如 $1\ 1\ 2\ 2\ 3\ 3\ 5$ 就可以看成是 $4$ 个颜色段。对每一个颜色段建一个虚拟节点。再从这个虚拟节点向对应的列的标号连边，以及从列的标号向下一个颜色段也连一条边。然后跑拓扑序就好了。

```cpp
//Coded by tzc_wk
/*
数据不清空，爆零两行泪。
多测不读完，爆零两行泪。
边界不特判，爆零两行泪。
贪心不证明，爆零两行泪。
D P 顺序错，爆零两行泪。
大小少等号，爆零两行泪。
变量不统一，爆零两行泪。
越界不判断，爆零两行泪。
调试不注释，爆零两行泪。
溢出不 l l，爆零两行泪。
*/
#include <bits/stdc++.h>
using namespace std;
#define fi			first
#define se			second
#define fz(i,a,b)	for(int i=a;i<=b;i++)
#define fd(i,a,b)	for(int i=a;i>=b;i--)
#define foreach(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define all(a)		a.begin(),a.end()
#define giveup(...) return printf(__VA_ARGS__),0;
#define fill0(a)	memset(a,0,sizeof(a))
#define fill1(a)	memset(a,-1,sizeof(a))
#define fillbig(a)	memset(a,0x3f,sizeof(a))
#define fillsmall(a) memset(a,0xcf,sizeof(a))
#define mask(a)		(1ll<<(a))
#define maskx(a,x)	((a)<<(x))
#define _bit(a,x)	(((a)>>(x))&1)
#define _sz(a)		((int)(a).size())
#define filei(a)	freopen(a,"r",stdin);
#define fileo(a)	freopen(a,"w",stdout);
#define fileio(a) 	freopen(a".in","r",stdin);freopen(a".out","w",stdout)
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#define put(x)		putchar(x)
#define eoln        put('\n')
#define space		put(' ')
#define y1			y_chenxiaoyan_1
#define y0			y_chenxiaoyan_0
typedef pair<int,int> pii;
inline int read(){
	int x=0,neg=1;char c=getchar();
	while(!isdigit(c)){
		if(c=='-')	neg=-1;
		c=getchar();
	}
	while(isdigit(c))	x=x*10+c-'0',c=getchar();
	return x*neg;
}
inline void print(int x){
	if(x<0){
		putchar('-');
		print(abs(x));
		return;
	}
	if(x<=9)	putchar(x+'0');
	else{
		print(x/10);
		putchar(x%10+'0');
	}
}
inline int qpow(int x,int e,int _MOD){
	int ans=1;
	while(e){
		if(e&1)	ans=ans*x%_MOD;
		x=x*x%_MOD;
		e>>=1;
	}
	return ans;
}
int n=read(),m=read();
vector<vector<int> > a;
vector<int> g[200005];
int vis[200005];
vector<int> ans;
inline void dfs(int x){
	vis[x]=1;
	foreach(it,g[x]){
		if(vis[*it]==1)	puts("-1"),exit(0);
		if(vis[*it]==0)	dfs(*it);
	}
	vis[x]=2;
	if(x<=m)	ans.push_back(x);
}
signed main(){
	a.resize(n+1);
	fz(i,1,n)	a[i].resize(m+1);
	fz(i,1,n)	fz(j,1,m)	a[i][j]=read();
	int cur=m; 
	for(int i=1;i<=n;i++){
		vector<pii> t;
		fz(j,1,m)	if(~a[i][j])	t.push_back(pii(a[i][j],j));
		sort(t.begin(),t.end());
		for(int i=0;i<t.size();i++){
			if(i==0||t[i-1].fi!=t[i].fi)	cur++;
			g[cur].push_back(t[i].se);
			g[t[i].se].push_back(cur+1);
		}
		cur++;
	}
	fz(i,1,cur)	if(!vis[i])	dfs(i);
	reverse(all(ans));
	foreach(it,ans)	cout<<*it<<" ";
	return 0;
}
```

---

## 作者：teylnol_evteyl (赞：1)

对于矩阵的每一行，可以确定一些列之间的关系，也就是对于 $i,j$ 满足 $a_i\neq-1,a_j\neq-1,a_i<a_j$，则第 $i$ 列应该排在第 $j$ 前面，可以连一条从 $i$ 到 $j$ 的边，进行拓扑排序就可以得到答案，如果有环就说明无解，时间复杂度 $O(nm^2)$。

考虑优化。可以发现只需要从比它小的最大的点向它连边，但是如果这样的点有多个就必须每个点向它连边。考虑对每行对每个数值建立虚拟节点，每个值不是 $-1$ 的点向它的数值对应的点连边，比它小的最大的数值对应的点（如果存在）向它连边，这样点和边的数量就是 $O(nm)$ 级别的了。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int n, m, a[N], x[N], s, pid;
int la[N], ne[N], en[N], idx, du[N];
int q[N], hh, tt, path[N];

void add(int a, int b)
{
	ne[ ++ idx] = la[a];
	la[a] = idx;
	en[idx] = b;
	du[b] ++ ;
}
bool topo()
{
	int cnt = 0;
	hh = 0, tt = -1;
	for(int i = 1; i <= pid; i ++ )
		if(!du[i])
			q[ ++ tt] = i;
	while(hh <= tt)
	{
		int u = q[hh ++ ];
		path[ ++ cnt] = u;
		for(int i = la[u]; i; i = ne[i])
		{
			int v = en[i];
			du[v] -- ;
			if(!du[v]) q[ ++ tt] = v;
		}
	}
	return cnt == pid;
}

int main()
{
	scanf("%d%d", &n, &m);
	pid = m;
	for(int i = 1; i <= n; i ++ )
	{
		s = 0;
		for(int j = 1; j <= m; j ++ )
		{
			scanf("%d", &a[j]);
			if(a[j] != -1) x[ ++ s] = a[j];
		}
		sort(x + 1, x + s + 1);
		s = unique(x + 1, x + s + 1) - x - 1;
		for(int j = 1; j <= m; j ++ )
			if(a[j] != -1)
			{
				int t = lower_bound(x + 1, x + s + 1, a[j]) - x;
				if(t > 1) add(pid + t - 1, j);
				add(j, pid + t);
			}
		pid += s;
	}
	
	if(topo())
	{
		for(int i = 1; i <= pid; i ++ )
			if(path[i] <= m)
				printf("%d ", path[i]);
	}
	else puts("-1");
	return 0;
}
```

---

## 作者：LionBlaze (赞：0)

看到从小到大，考虑拓扑排序。

节点代表什么？位置。具体来讲，编号为 $i$ 的节点在位置 $j$，说明第 $i$ 列原本在第 $j$ 的位置。

比如 `2 5 4` 这一行，原本的排列是 `2 4 5`，节点排列就是 `1 3 2`。

考虑如何建图。显然我们需要根据节点的小于关系建图。

设 $a$ 为矩阵的一行。若 $a_i < a_j$，则说明第 $i$ 列在原矩阵中必须排在第 $j$ 列之前，即从 $i$ 向 $j$ 连有向边（等于关系不连边，无法保证位置关系）。

这样随随便便就能够把一行的边数卡到 $\Theta(m^2)$（所有值都不同即可）。显然不行（总边数为 $\Theta(nm^2)$）。

考虑优化。我们发现，若存在 $a \to b$ 和 $b \to c$ 的边，则我们也会连上 $a \to c$ 的边，这是多余的。所以，我们可以只连上“相邻”的值，即在原本连边的方法中，加入限制条件“不存在 $a_k$ 满足 $a_i < a_k < a_j$”。

这样随随便便就能够把一行的边数卡到 $\Theta(n^2)$（比如 `1 1 1 1 1 ... 1 2 2 2 2 2 ... 2`）。显然不行。

考虑优化。我们发现建图的时候，相邻两**种**不同节点连上了完全二分图，具体地，若 $a_i$ 和 $a_j$ 有连边，则所有满足 $a_i=a_x$ 和 $a_j=a_y$ 的 $x$ 和 $y$ 都会有连边，形成完全二分图。

> 图的结构很像 MLP。或者说，好像就是 MLP？

如何优化？使用虚拟节点即可。这是完全二分图优化建图的经典技巧。比如从集合 $U$ 中的所有节点都向 $V$ 中的所有节点连边，则新建虚拟节点 $\omega$，把 $U$ 中所有节点向 $\omega$ 连边，然后把 $\omega$ 向 $V$ 中的所有节点连边即可。

最后求出的拓扑序列中去除掉 $w$ 即可。

这只是一行。但是如果有多列，则也非常简单，只需要把图的边合并即可。每次加边都只需要在同一个图上加（虚拟节点除外）。

时间复杂度看上去是 $\mathcal O(nm)$，但是别忘了我们建图的时候对于每一行都需要把所有元素排序分段，排序操作是带一只 $\log$ 的，所以总时间复杂度是 $\mathcal O(nm \log m)$。

代码不长，我只写了【蒜薢的月考成绩】行。

```cpp
#include <stack>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

class node
{
public:
	int num, id;
} arr[100005];
// 1~m for real nodes(columns), m+1~/ for virtual nodes.
// There are at most m virtual nodes in a column.
// We knew that 1+1=3, so the size of the array is 300005.
vector<int> web[300005];
int ind[300005];

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	int vIa = m;
	for (int i = 1; i <= n; i++)
	{
		int cur = 0;
		for (int j = 1; j <= m; j++)
		{
			scanf("%d", &arr[++cur].num);
			arr[cur].id = j;
			if (arr[cur].num == -1) cur--;
		}
		sort(arr + 1, arr + cur + 1, [](const auto& x, const auto& y) { return x.num < y.num; });
		vector<vector<int>> vv;
		int qwq = -1;
		for (int j = 1; j <= cur; j++)
		{
			auto v = arr[j];
			if (v.num == qwq) vv.back().push_back(v.id);
			else vv.push_back({ v.id });
			qwq = v.num;
		}
		// keai
		for (int j = 0; j + 1 < vv.size(); j++)
		{
			int id = ++vIa;
			for (int v : vv[j])
			{
				web[v].push_back(id);
				ind[id]++;
				// printf("%d -> %d\n", v, id);
			}
			for (int v : vv[j + 1])
			{
				web[id].push_back(v);
				ind[v]++;
				// printf("%d -> %d\n", id, v);
			}
		}
	}
	stack<int> q; // 可爱
	for (int i = 1; i <= vIa; i++)
	{
		if (ind[i] == 0) q.push(i);
	}
	vector<int> ans;
	while (!q.empty())
	{
		int u = q.top();
		q.pop();
		ans.push_back(u);
		for (int v : web[u])
		{
			if (!--ind[v]) q.push(v);
		}
	}
	if (ans.size() != vIa) printf("-1\n");
	else for (int v : ans)
	{
		if(v <= m) printf("%d ", v);
	}
	return 0;
}
```

---

## 作者：迟暮天复明 (赞：0)

显然每一行独立拿出来看，按照数值排序之后从小的数往大的数连一条边跑拓扑排序就行。但是这样每一行边数是 $m^2$ 的。然后观察到类似 $1\ 2\ 3\ 4$ 这样的东西，只需要从小到大相邻两个数连一下就行了。但是这样不好处理一堆数字相等的情况。那么这种情况就套路的开个辅助点就完了。

---

## 作者：Hoks (赞：0)

## 前言
duel 到的，感觉挺有意思的题。

摘自 [杂题选做](https://www.luogu.com.cn/training/518105)。
## 思路分析
初入手感觉很难做，根本没有思路方向。

注意到这题是让我们重排列非严格单调递增，先不考虑 $-1$。

那么我们就可以知道对于列 $i,j$，$i$ 是否能接在 $j$ 后面。

这会想到什么？

如果把接在后面看做连边的话，就可以建出来一张图，这样只要我们找到有 $m$ 个点的一条路径，即是合法方案。

用什么来找？

拓扑排序，因为后走到的点肯定是值更大的，输出这个顺序即为答案。

现在正确性已经保证了，但如果要这样连边的话，复杂度为 $O(nm^2)$，直接挂飞。

考虑每行的偏序若无 $-1$ 都是唯一确定的，直接用每行的偏序对列进行连边，复杂度来到 $O(nm\log n)$。

显然并不是这样，如果数据中每行都类似于 $1,1,1,\dots,2,2,2$，直接卡到 $O(nm^2)$。

考虑经典 trick，对每一种值都开一个等价类，虚点连边即可降到 $O(nm)$。

接着来考虑 $-1$，因为 $-1$ 啥都行，所以不造成影响，直接连即可。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10,V=1e5+10,M=1ll<<40,INF=0x3f3f3f3f3f3f3f3f;
int n,m,tot,a[N],id[N],in[N];vector<int>e[N],ans;queue<int>q;
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'||c=='.'||c=='#'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline bool cmp(int x,int y){return a[x]<a[y];}
signed main()
{
    n=read(),tot=m=read();
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++) a[j]=read(),id[j]=j;
        sort(id+1,id+m+1,cmp);sort(a+1,a+1+m);tot++;int k=1,f=0;
        while(k<=m)
        {
            if(a[k]==-1){k++;continue;}int t=k;
            while(t<=m&&a[k]==a[t])
            {
                if(f) e[tot].push_back(id[t]),in[id[t]]++;
                e[id[t]].push_back(tot+1);in[tot+1]++;t++;
            }
            tot++,k=t,f=1;
        }
    }for(int i=1;i<=m;i++) if(!in[i]) q.push(i);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        if(u<=m) ans.emplace_back(u);
        for(auto v:e[u]) if(!(--in[v])) q.push(v);
    }
    if(ans.size()<m) put("-1");
    else for(auto i:ans) print(i),put(' ');
    genshin:;flush();return 0;
}
```

---

## 作者：shinkuu (赞：0)

挺有意思的题。

每一行分开看，如果 $a_{i,j}>a_{i,k}$，则 $rk_j>rk_k$。$rk_i$ 为第 $i$ 列最后的排名。得到了这若干个关系后，可以发现 $rk_i>rk_j$ 可以转化为 $rk_j-rk_i\leq -1$，转化成一个差分约束问题。

但是如果让每个 $j$ 都向所有 $k$ 连边，边数是 $O(nm^2)$ 的。考虑优化。每个 $j$ 只向第一个比它小的 $k$ 连边。但是 $a_{i,j}$ 可能重复。如果每个值为 $a$ 的向每个值为 $b$ 的连边，边数仍然是 $O(nm^2)$ 的。

这个时候就要用到建立虚点连边了。想学习这个 trick 可以看[日报](https://www.luogu.com.cn/blog/chengni5673/tu-lun-di-xiao-ji-qiao-yi-ji-kuo-zhan)。具体到这题，可以给每一堆相同权值的列创建一个虚点，在虚点之间连边。大概这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/jqndhdh5.png)

边数就只有 $O(nm)$ 了。

然后高兴地打一个 spfa 上去，[结果](https://codeforces.com/contest/274/submission/204316164)。

众所周知，spfa 时间复杂度为 $O(|V||E|)$，但事实上，差分约束还有另一种实现方式，参考 [P3275 糖果](https://www.luogu.com.cn/problem/P3275)。于是，**将 spfa 变为拓扑排序**，时间复杂度就变为正确的了。

这里来简单讲一下怎样用拓扑排序实现。先缩点，将图变成一个 DAG。容易证明每个强连通分量里的所有点答案应相同，则如果一个强连通分量里有一条边权不为 $0$，那就是无解的。否则就在 DAG 上拓扑排序 dp。

最后时间复杂度 $O(nm\log m)$。瓶颈在找大小关系时排序。

code：

```cpp
int n,m,s;
int dis[N],cnt[N];
pii d[N];
int tot,rtot,head[N],rhead[N];
struct node{
	int to,nxt,cw;
}e[N<<1],re[N<<1];
vector<pii> vec;
inline void add(int u,int v,int w){
	e[++tot]={v,head[u],w};
	head[u]=tot;
}
inline void radd(int u,int v,int w){
	re[++rtot]={v,rhead[u],w};
	rhead[u]=rtot;
}
int ct,dfn[N],low[N];
int top,st[N];
bool vis[N];
int k,id[N];
void tarjan(int u){
	dfn[u]=low[u]=++ct;
	st[++top]=u;
	vis[u]=true;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}else if(vis[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]){
		k++;
		do{
			int v=st[top];
			vis[v]=false;
			id[v]=k;
		}while(st[top--]!=u);
	}
}
int in[N],dp[N];
void solve(){
	scanf("%d%d",&n,&m);
	s=n*m;
	for(int i=1;i<=n;i++){
		vec.clear();
		for(int j=1,x;j<=m;j++){
			scanf("%d",&x);
			vec.push_back(make_pair(x,j));
		}
		sort(vec.begin(),vec.end());
		for(int j=0;j<m;j++){
			if(vec[j].first==-1)
				continue;
			int p=j;
			if(j&&~vec[j-1].first)
				add(s+2,s-1,-1);
			add(s+1,vec[j].second,0);
			add(vec[j].second,s+2,0);
			while(p<m-1&&vec[p+1].first==vec[p].first){
				p++;
				add(s+1,vec[p].second,0);
				add(vec[p].second,s+2,0);
			}
			j=p;
			s+=2;
		}
	}
	for(int i=1;i<=s;i++){
		if(!dfn[i])
			tarjan(i);
	}
	for(int u=1;u<=s;u++){
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(id[u]!=id[v]){
				radd(id[u],id[v],e[i].cw);
				in[id[v]]++;
			}else if(e[i].cw){
				puts("-1");
				return;
			}
		}
	}
	mems(dp,0x3f);
	queue<int> q;
	for(int i=1;i<=k;i++){
		if(!in[i]){
			q.push(i);
			dp[i]=m;
		}
	}
	while(q.size()){
		int u=q.front();
		q.pop();
		for(int i=rhead[u];i;i=re[i].nxt){
			int v=re[i].to;
			dp[v]=min(dp[v],dp[u]+re[i].cw);
			in[v]--;
			if(!in[v])
				q.push(v);
		}
	}
	for(int i=1;i<=m;i++)
		d[i]=make_pair(dp[id[i]],i);
	sort(d+1,d+m+1);
	for(int i=1;i<=m;i++)
		printf("%d ",d[i].second);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)solve();
}
```

---

## 作者：plafle (赞：0)

# Lovely Matrix

## 1.题目描述

​	给定一个$n \cdot m (n \cdot m \leq 10^5)$大小的矩阵$A$，矩阵中某个格子中如果出现$-1$表示该格中没有数字。你可以在这些空的格子中任意填写整数，并在这之后任意交换矩阵的列，使得对于矩阵中任意的$i,j(j < m)$,满足$A[i][j] \leq A[i][j + 1]$.

​	如果有这样的方法，请输出$m$个整数$p_1,p_2,p_3,……,p_m$，表示处理后的新矩阵的第一列是原矩阵的第$p_1$列，新矩阵的第二列是原矩阵的$p_2$列，……，新矩阵的第$m$列是原矩阵的$p_m$列。

​	如果没有这样的方法，输出$-1$.

- 限制：**2s** + 250$MB$.

## 2.解法

​	首先用二维嵌套版本的$vector$存下这个矩阵。

​	接下来对这个矩阵的每一行排序（排序时保留其原有序号）（先不管$-1$)

​	排完之后发现排序后的序列中值较小的数所在的列一定要排在值较大的数所在的列的前面。

​	因此我们可以连一条有向边，起点为值较小的数所在的列，终点为值较大的数所在的列。最后对这张有向图跑一边拓扑排序。如果不存在环，就按拓扑序输出答案。如果存在环，那么问题无解，输出$-1$.

​	这样的做法会有一个问题，如果有一行矩阵排序后是**1,1,1,1,1,1……(50000个1),2,2,2,2……（50000个2)**，那么每一对**1,2**之间都要连一条有向边，总共需要连$\frac{50000 \cdot 50000} 2$条边。这个复杂度是我们不能接受的。

​	这里的做法是新建2个虚拟点$p_1,p_2$,将50000个1都向$p_1$连一条指向$p_1$的有向边，再从$p_1$向$p_2$连一条有向边，最后从$p_2$向50000个2都连一条有向边。即，值相同的点都连向一个虚拟点，再在虚拟点之间连有向边。这种做法时间复杂度就是线性的。

​	最后是有关$-1$的处理。如果一列上所有数都是$-1$，那么我们直接把这一列放在新矩阵的最前面，后面就不再考虑它。

​	去除这种情况后，我们在连有向边的时候就不考虑数值为$-1$的点，直接将其忽略，因为它可以被填写为任意整数。

​	最后注意一下$vector$不要放主函数里面，有可能会爆主函数$4KB$ 的内存。并且注意开了虚拟点之后，空间要开得大一些。

## 3.代码

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

const int maxn = 4e5 + 5;  //注意虚拟点带来的额外空间
struct node {
	int x,id;
};

vector<vector<node> > v; //嵌套vector
vector<node> vv;  //要定义在外面
int n,m,p,rd[maxn],ans[maxn];
int first[maxn],last[maxn],dx[maxn << 1],nxt[maxn << 1],xb;
bool used[maxn];
queue<int> q;

bool cmp(node a,node b) {
	return a.x < b.x || (a.x == b.x && a.id < b.id);
}

void build(int x,int y) { 
	rd[y]++;
	dx[++xb] = y;
	if (!first[x])
		first[x] = xb; else
		nxt[last[x]] = xb;
	last[x] = xb;	
}

int main() {
	scanf("%d%d",&n,&m);
	for (int i=1; i<=n; i++) {
		vv.clear(); //初始化
		for (int j=1; j<=m; j++) {
			int x;
			scanf("%d",&x);
			vv.push_back((node){x,j - 1}); //编号要-1，因为vector下标从0开始
		}
		v.push_back(vv);
	}
	for (int i=0; i<m; i++) {
		bool t = 1;
		for (int j=0; j<n; j++)
			if (v[j][i].x != -1) {
				t = 0;
				break;
			} //查找数字全部是-1的列。
		if (t) {
			used[v[0][i].id] = 1;
			q.push(v[0][i].id); //先把这一列放到最前面
		}
	} //这部分是查找并预处理数字全部是-1的列。
	for (int i=0; i<n; i++)
		sort(v[i].begin(),v[i].end(),cmp);
		
	p = m - 1; //虚拟点编号初始化
	
	for (int i=0; i<n; i++) {
		v[i].push_back((node){-100,0}); //小技巧，确保最后一块相同的数能被处理
		int u = m + 1;
		for (int j=0; j<m; j++) 
			if (v[i][j].x != -1) {
				u = j;
				break;
			} //忽略-1的点
		int lasts = 0,lastt = u;
		for (int j=u + 1; j<=m; j++) {
			if (v[i][j].x == v[i][j - 1].x)
 				continue;
			p++;
			for (int k = lastt; k < j; k++)
				build(p,v[i][k].id); //普通点连向虚拟点
			if (lasts)
				build(lasts,p); //虚拟点间连边
			p++;
			for (int k = lastt; k < j; k++) 
				build(v[i][k].id,p);  //虚拟点连向普通点
				
			lasts = p;
			lastt = j;
		}
	}
	
	for (int i=0; i<p; i++)
		if (!rd[i] && !used[i]) //used数组是为了防止前面被预处理过的点再次入队列。
			q.push(i);  //拓扑排序
	int cnt = 0;
	
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		ans[++cnt] = x;
		for (int i=first[x]; i; i = nxt[i]) {
			int y = dx[i];
			rd[y]--;
			if (!rd[y])
				q.push(y);
		}
	} //拓扑排序
	if (cnt != p + 1 || !cnt) 
		puts("-1"); else
		for (int i=1; i<=cnt; i++)
			if (ans[i] >= 0 && ans[i] < m)//注意这里只输出普通点，不输出虚拟点 
				printf("%d ",ans[i] + 1);	//编号+1，小细节。
	return 0;
}
```



---

