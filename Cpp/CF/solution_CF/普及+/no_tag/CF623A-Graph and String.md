# Graph and String

## 题目描述

One day student Vasya was sitting on a lecture and mentioned a string $ s_{1}s_{2}...\ s_{n} $ , consisting of letters "a", "b" and "c" that was written on his desk. As the lecture was boring, Vasya decided to complete the picture by composing a graph $ G $ with the following properties:

- $ G $ has exactly $ n $ vertices, numbered from $ 1 $ to $ n $ .
- For all pairs of vertices $ i $ and $ j $ , where $ i≠j $ , there is an edge connecting them if and only if characters $ s_{i} $ and $ s_{j} $ are either equal or neighbouring in the alphabet. That is, letters in pairs "a"-"b" and "b"-"c" are neighbouring, while letters "a"-"c" are not.

Vasya painted the resulting graph near the string and then erased the string. Next day Vasya's friend Petya came to a lecture and found some graph at his desk. He had heard of Vasya's adventure and now he wants to find out whether it could be the original graph $ G $ , painted by Vasya. In order to verify this, Petya needs to know whether there exists a string $ s $ , such that if Vasya used this $ s $ he would produce the given graph $ G $ .

## 说明/提示

In the first sample you are given a graph made of two vertices with an edge between them. So, these vertices can correspond to both the same and adjacent letters. Any of the following strings "aa", "ab", "ba", "bb", "bc", "cb", "cc" meets the graph's conditions.

In the second sample the first vertex is connected to all three other vertices, but these three vertices are not connected with each other. That means that they must correspond to distinct letters that are not adjacent, but that is impossible as there are only two such letters: a and c.

## 样例 #1

### 输入

```
2 1
1 2
```

### 输出

```
Yes
aa
```

## 样例 #2

### 输入

```
4 3
1 2
1 3
1 4
```

### 输出

```
No
```

# 题解

## 作者：珅肐 (赞：5)

先描述一下题意吧：

给出一个由字符串$s$建图的过程，

- 字符仅有$a,b,c$三种，建出的图中第$i$个顶点表示原来的第$i$个字符。
- $i$与$j$有连边，当且仅当$s[i]$与$s[j]$相同或$s[i]$和$s[j]$是相邻的字符（$a$与$b$相邻，$b$与$c$相邻）

现给出由某个字符串$s$建出的图，构造一个字符串使其符合上面的要求要求，或者回答不存在这样的字符串。

###### 输入：
第一行两个整数$n,m$，表示节点数（即字符串长度）和边数
接下来$m$行，每行两个数字 $u_{i}$ and $v_{i}$，表示这两个节点之间有一条边

###### 输出：
如果字符串存在，第一行输出一个$“Yes”，第二行输出符合条件的字符串。

如果不存在，仅在第一行输出一个“No”；

---

#### 讲解时间：

由题意可知，$b$与所有的点都有连边，我们很容易就可以找出$b$，

反过来想，只有$a,c$之间有没有连的边，那么我们把图反过来，准确的说是建原图的补图，

如果有符合条件的字符串，那这个补图一定是个二分图，那么对补图进行二分图染色就完成了。

注意一下，在补图中一条边都没有的即为点$b$，我们并不需要对它进行处理，只在最后输出就可以啦。
##### 代码：
```cpp
#include<iostream>
#include<cstdio>
#include<ctype.h>
#include<cstring>
#include<cstdlib>
#define _ 0
using namespace std;
inline int read(){
    int x=0,f=0;char ch=getchar();
    while(!isdigit(ch))f|=ch=='-',ch=getchar();
    while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
    return f?-x:x;
}
int head[507],cnt;
struct Edge{
    int next,to;
}edge[500007];
bool ma[507][507];//用邻接矩阵存图，方便建补图
int col[507];
inline void Byebye(){printf("No\n");exit( ~~(0^_^0) );}//有点闲..
inline void add_edge(int from,int to){
    edge[++cnt].next=head[from];
    edge[cnt].to=to;head[from]=cnt;
}
bool dfs(int x){//二分图染色
    for(int i=head[x];i;i=edge[i].next){
        int to=edge[i].to;
        if(col[to]==col[x])return 0;
        if(~col[to])continue;col[to]=col[x]^1;
        if(!dfs(to))return 0;
    }
    return 1;
}
int main(){
    int n=read(),m=read();
    for(int i=1;i<=m;++i){
        int u=read(),v=read();
        ma[u][v]=ma[v][u]=1;
    }
    for(int i=1;i<=n;++i)for(int j=1;j<i;++j)//建补图
        if(!ma[i][j])add_edge(i,j),add_edge(j,i);
    memset(col,-1,sizeof col);//染色数组置为-1，最后若依旧为-1,即为b
    for(int i=1;i<=n;++i){
        if(~col[i] || !head[i])continue;
        col[i]=0;
        if(!dfs(i))Byebye();//染色基本套路，若不符合条件输出No，退出程序
    }
    for(int i=1;i<=n;++i)for(int j=1;j<i;++j)
        if(ma[i][j] && col[i]+col[j]==1)Byebye();//检查a,c之间是否有连边
    printf("Yes\n");
    for(int i=1;i<=n;++i)putchar(~col[i]?!col[i]?'a':'c':'b');//输出一种即可
    return 0;//好习惯
}
```

---

## 作者：Aisaka_Taiga (赞：3)

## 并查集做法

这里提供一种并查集的做法。

我们根据题意能发现：

1. $a$ 只与 $a,b$ 连边。

2. $b$ 与所有点连边。

3. $c$ 只与 $b,c$ 连边。

我们从上可以得知当一个点为 $b$ 的时候，他的度数是 $n-1$。

而剩下的 $a$ 和 $c$ 之间是互相连边的，也就是说，我们去掉为 $b$ 的点以及与之相连的边，我们最后得到的图，只有两个连通块（也是两个完全图），一个里面的点全是 $a$，一个里面的点全是 $c$。

所以我们处理出每一个点的度数 $du_{i}$，以及图的连通情况。

对于两个端点有 $b$ 的边我们直接跳过，其余的边我们进行并查集的合并，最后我们就可以发现如果要是有大于两个的连通块，一定是无解的，对于同一连通块里的点，如果有两个点之间是没有边相连的，说明无解，因为题目说了相同的字符之间有边。

最后我们需要标记一下 $n$ 个点的所属的连通块，然后输出即可。

### code：

```cpp
#include<bits/stdc++.h>
#define N 510
using namespace std;
int n,m,cnt,du[N],fa[N],mp[N][N],vis[N];
inline int fid(int x){if(fa[x]==x)return x;return fa[x]=fid(fa[x]);}
inline int read(){int x=0,f=1;char ch=getchar();while(!isdigit(ch)){f=ch!='-';ch=getchar();}while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return f?x:-x;}
signed main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++)fa[i]=i,mp[i][i]=1;
	for(int i=1;i<=m;i++)
	{
		int u=read(),v=read();
		du[u]++,du[v]++;
		mp[u][v]=mp[v][u]=1;
	}
	for(int i=1;i<=n;i++)
	{
		if(du[i]==n-1)continue;
	    for(int j=1;j<=n;j++)
	      if(du[j]!=n-1&&mp[i][j])fa[fid(i)]=fid(j);
		int xx=fid(i);
		if(!vis[xx])vis[xx]=++cnt;
	}
	if(cnt>2){cout<<"No"<<endl;return 0;}
	for(int i=1;i<=n;i++)
	{
		if(du[i]==n-1)continue;
	    for(int j=1;j<=n;j++)
		  if(fid(i)==fid(j))if(!mp[i][j]){cout<<"No"<<endl;return 0;}
	}
	cout<<"Yes"<<endl;
	for(int i=1;i<=n;i++)
	{
		int xx=fid(i);
		if(du[i]==n-1)cout<<"b";
		else if(vis[xx]==1)cout<<"a";
		else if(vis[xx]==2)cout<<"c";
	}
	return 0;
}
```

---

## 作者：saixingzhe (赞：2)

# 分析
我们发现，只有 $AC$ 不能连边，所以可以建原图的补图，用染色法往里染 $AC$，需要注意的是，染完色还需要判断一下，如下面这幅图：

![图片](https://cdn.luogu.com.cn/upload/image_hosting/5ejcltre.png?x-oss-process=image/resize,m_lfit,h_340,w_450)

我们发现，补图染色成功不代表着这图一定符合要求，所以要最后在判断一下，具体不懂看代码。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,l[502][502],u,v,vis[502];
vector<int>a[502],b[502];
bool dfs(int i,int col){
	vis[i]=col;
	for(int v:b[i]){
		if(vis[v]==vis[i])	return 0;
		if(vis[v]!=-1)	continue;
		if(dfs(v,col^1)==0)	return 0;
	}
	return 1;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)	scanf("%d%d",&u,&v),a[u].push_back(v),a[v].push_back(u),l[u][v]=1,l[v][u]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)	if(!l[i][j]&&i!=j) b[i].push_back(j);
	}
	for(int i=1;i<=n;i++)	vis[i]=-1;
	for(int i=1;i<=n;i++){
		if(b[i].size()&&vis[i]==-1){
			if(!dfs(i,0)){
				printf("No");
				return 0;
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j:a[i])	if(vis[j]==0&&vis[i]==1||vis[j]==1&&vis[i]==0){
			printf("No");
			return 0;
		}
	}
	printf("Yes\n");
	for(int i=1;i<=n;i++){
		if(!vis[i])	printf("a");
		else	if(vis[i]==1)	printf("c");
		else	printf("b");
	}
	return 0;
}
```

---

## 作者：wgyhm (赞：2)

# 【水题解记录】CF623A Graph and String

## 题意

给出一个由字符串 $s$ 建图的过程：

* 字符仅有 $a,b,c$ 三种，建出的图中第 $i$ 个定点表示原来的第 $i$ 个字符
* $i$ 和 $j$ 有边，当且仅当 $s_i=s_j$ 或者 $s_i$ 和 $s_j$ 是相邻的字符
* $a，b$ 相邻，$b,c$ 相邻

给出某个字符串 $s$ 建出的图，构造任意一个字符串使其满足以上要求。

如果无解输出 $No$。

## 题解

显然，如果这个字符是 $b$ ，它与除了自身的所有顶点都有顶点。我们先进行特判。

剩下只身下 $a,c$ ，对于顶点 $i,j$，如果 $i,j$ 有连边，则 $s_i=s_j$，否则 $s_i\not=s_j$。

发现是一个典型的 **2-SAT**，使用 $tarjan$ 解决本题。

## Code

```cpp
#define maxn 1005
int scc[maxn],dfn[maxn],low[maxn],stac[maxn],vis[maxn],times,tot,sccnum;
int h[maxn],in[maxn],head=1,f[maxn][maxn],ans[maxn],n,m;
struct yyy{
	int to,z;
	inline void add(int x,int y){
		to=y;z=h[x];h[x]=head;
	}
}a[maxn*maxn*2];
inline void tarjan(int x){
	rg int i;dfn[x]=low[x]=++times;stac[++tot]=x;vis[x]=1;
	for (i=h[x];i;i=a[i].z)
	    if (!dfn[a[i].to]) tarjan(a[i].to),low[x]=min(low[x],low[a[i].to]);
	    else if (vis[a[i].to]) low[x]=min(low[x],dfn[a[i].to]);
	if (low[x]==dfn[x]){
		++sccnum;
		while (1){
			vis[stac[tot]]=0;
			scc[stac[tot]]=sccnum;
			if (stac[tot--]==x) return;
		}
	}
}
signed main(){
	rg int i,j,x,y;
	read(n);read(m);
	for (i=1;i<=m;i++) {
		read(x);read(y);
		in[x]++;in[y]++;f[x][y]=f[y][x]=1;
	}
	for (i=1;i<=n;i++){
		if (in[i]==n-1) continue;
		for (j=1;j<=n;j++) 
            if (in[j]<n-1&&i!=j){
            	if (f[i][j]) a[++head].add(i,j),a[++head].add(i+n,j+n);
            	else a[++head].add(i,j+n),a[++head].add(i+n,j);
			}
	}
	for (i=1;i<=2*n;i++) if (!dfn[i]) tarjan(i);
	for (i=1;i<=n;i++) if (in[i]<n-1&&scc[i]==scc[i+n]) return puts("No"),0;
	for (puts("Yes"),i=1;i<=n;i++) 
	    if (in[i]==n-1) putchar('b');
	    else putchar(scc[i]<scc[i+n]?'a':'c');
	return 0;
}
```



---

## 作者：_zuoqingyuan (赞：1)

做了一下午，代码从 800B 改到 1.5KB。遂写篇题解记录一下。

# 思路分析

题目中所给出的边 $(u,v)$，表示第 $u$ 个字符和第 $v$ 个字符“相邻”。这种限制条件没什么用，因为其包含两种情况（分别是字符 $\texttt{a}$ 和字符 $\texttt{b}$，以及 $\texttt{b}$ 和字符 $\texttt{c}$），显然不好做。

但经过我们仔细分析样例，我们发现其一个很好的性质：如果第 $u$ 个点和第 $v$ 个点在原图中并没有被一条边直接连接，则说明第 $u$ 个字符和第 $v$ 个字符一定“不相邻”。这个条件很有用：如果两个字符不相邻，其只可能是字符 $\texttt{a}$ 和字符 $\texttt{c}$。

那么对于原图的**补图**上，相邻（指两点间有一条边之间连接）两点之间如果存在一条边，则这两个节点要么染成黑色，要么染成白色，这样就转化为了经典的二分图黑白染色。

不过我们不一定能保证直接在补图上黑白染色的合法性，因为两个点在原图中相邻，但在补图中位于不同连通块的情况是存在的。我们在第一步黑白染色完后要进行调整。

- 对于两个在原图中连通，补图中不连通的块 $i,j$，如果 $i/j$ 其中一个连通块的大小为 $1$，则将其对应的字符赋为字符 $\texttt{b}$。

- 对于两个大小不为 $1$ 的块，如果他们之间有原图的边连接，且边的两端颜色不一样。就将其中一个块颜色整个取反，然后打上标记，如果下次对一个块取反时，发现这个块已经打上标记了，则不存在合法方案。

但上述两种方法依旧无法保证合法性，我们在染色和调整完成后，再把原图中的所有边枚举一遍，查看是否合法。

好像第二类调整没有什么用，不过我感觉很有必要，这使得本解法时间复杂度为 $O(n^3)$，可以通过本题。

# Code：

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int N=501,M=N*N*2;
int n,m,vis[N],ver[N],to[M],nxt[M],idx,cnt,f[N],mk[N],siz[N];
bool w[N][N];
void add(int x,int y){
	to[++idx]=y,nxt[idx]=ver[x],ver[x]=idx;
}
bool dfs(int x,int col,int id){
	vis[x]=col,f[x]=id,siz[id]++;
	for(int i=ver[x];i;i=nxt[i]){
		int y=to[i];
		if(!vis[y]&&!dfs(y,3-col,id))return 0;
		if(vis[y]&&vis[y]==col)return 0;
	}
	return 1;
} 
bool pd(int a,int b){
	if(a==1&&b==2)return 1;
	if(a==2&&b==1)return 1;
	return 0;
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1,u,v;i<=m;i++){
		scanf("%d %d",&u,&v);
		w[u][v]=w[v][u]=1;
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(!w[i][j])add(i,j),add(j,i);
		}
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			if(!dfs(i,1,++cnt)){
				printf("No\n");
				return 0;
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(w[i][j]&&f[i]!=f[j]){
				if(siz[f[i]]==1)vis[i]=3;
				else if(siz[f[j]]==1)vis[j]=3;
				else if(vis[i]!=vis[j]){
					if(mk[f[j]]){
						printf("No\n");
						return 0;
					}else{
						mk[f[j]]=1;
						for(int k=1;k<=n;k++){
							if(f[k]==f[j])vis[k]=3-vis[k];
						}
					}
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(w[i][j]&&pd(vis[i],vis[j])){
				printf("No\n");
				return 0;
			}
		}
	}
	printf("Yes\n");
	for(int i=1;i<=n;i++){
		if(vis[i]==1)printf("a");
		else if(vis[i]==3)printf("b");
		else printf("c");
	}
	return 0;
}
```

---

## 作者：emo_male_god (赞：1)

### 题意简述

有一个只包含 $a,b,c$ 的字符串，每个字母只与和自己相同或者在字母表上相邻的字母连边。现在知道一幅图，问能不能通过这幅图还原出任意一个合法的字符串。

### 分析

我们发现，$b$ 是可以和每一个字母连边的（除了自己），所以在图中，如果有一个点有 $n\!-\!1$ 条边，那么就可以确定是 $b$。

我们确定了 $b$，再来看 $a,c$。因为 $a,c$ 是不相邻的，所以在去掉 $b$ 点及其所有边以后，$a$ 只能连其他的 $a$。$c$ 同理。

所以出来了两种做法。

### 做法 1：建补图

因为在去掉 $b$ 后，$a$ 不能连 $c$。所以在建补图之后 $a,c$ 就连上了，并且是一个二分图（一边全是 $a$，另一边全是 $c$），所以我们可以用判断二分图的方法，也就是染色法来做。

### 做法 2：判断连通图个数

还是因为把 $b$ 去掉以后，所有的 $a$ 都联通，所有的 $c$ 也都联通，所以我们可以看有多少个联通块，来判断。

这里给出做法 $2$ 的代码。

### 其他注意事项

不管你用方法 $1$ 还是 $2$，你都要在做完以后判断度数，因为题目给的图是正确的，但是不完整，这也算错误。

### Code
```cpp
#include <iostream>

using namespace std;

inline char getch()
{
	static char buf[100005], *p1 = buf, *p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100005, stdin), p1 == p2) ? EOF : *p1 ++ ;
}
template<typename Type>
inline void read(Type &x)
{
	char c = getch();
	bool t; x = t = 0;
	while (c < '0' || c > '9') t |= (c == '-'), c = getch();
	while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c ^ 48), c = getch();
	x = t ? -x : x;
}

const int N = 505, M = 250005;

int head[N], to[M], ne[M], idx = 1;
int n, m, d[N], Color;
char c[N], mapp[] = {'d', 'a', 'c'};

void add(int u, int v)
{
	to[idx] = v;
	ne[idx] = head[u];
	head[u] = idx ++ ;
}

void search(int u, int color)
{
	c[u] = mapp[color];
	for (int i = head[u]; i; i = ne[i])
	{
		int v = to[i];
		if (!c[v]) search(v, color);
	}
}

bool check() // 用度数来判断a,c向b连完没有
{
	int A = 0, B = 0, C = 0;
	for (int i = 1; i <= n; i = -~ i)
	{
		if (!c[i]) return false;
		if (c[i] == 'a') A ++ ;
		if (c[i] == 'b') B ++ ;
		if (c[i] == 'c') C ++ ;
	}
	for (int i = 1; i <= n; i = -~ i)
	{
		if (c[i] == 'a' && d[i] != B + A - 1) return false;
		if (c[i] == 'c' && d[i] != B + C - 1) return false;
	}
	return true;
}

int main()
{
	read(n), read(m);

	int u, v;
	for (int i = 1; i <= m; i = -~ i)
	{
		read(u), read(v);
		d[u] ++, d[v] ++ ;
		add(u, v), add(v, u);
	}
	for (int i = 1; i <= n; i = -~ i) if (d[i] == n - 1) c[i] = 'b';
	for (int i = 1; i <= n; i = -~ i)
	{
		if (!c[i])
		{
			if ( ++ Color >= 3) break;
			search(i, Color);
		}
	}

	if (!check()) return printf("No\n") & 0;

	printf("Yes\n");
	for (int i = 1; i <= n; i = -~ i) printf("%c", c[i]);

	return 0;
}
```

---

## 作者：dreamnotfounddd (赞：0)

通过**读题**，我们可以发现：字符`b`必须和每个字符连接，那么，我们可以考虑建**补图**。

---

**补图的定义：**

如果图中的两个点存在连边，那么就将连边删除，否则在他们之间建立一条连边。通过这种方式就可以得到一张图的补图。

---

在建立补图之后，我们发现，`b`字符只能存在于没有任何连边的点上；而只有`a`和`a`可以相通，并且两个有连边的点只可能是`a`和`c`。

因此，我们可以通过染色法进行判定,如果有两个存在连边的点字符相同，可以直接输出`No`并退出。

（二分图路过）~~~

但是！在建补图后，可能会出现多个连通图，因此需要全面查找！！！

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int maxn = 1e6+7;
int t,n,m;
char color[555];
vector<int> pg[555];
bool dfs(int u,char c){
	color[u]=c;
	for(int v : pg[u]){
		if(color[v]!='b'){
			if(color[u]==color[v]){
				return false;
			}
		}else{
			char e;
			if(c=='a')e='c';
			else e='a';
			if(!dfs(v,e))return false;
		}
	}
	return true;
}
int main(){
	ios::sync_with_stdio(NULL);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> n >> m;
	for(int i = 1;i<=n;i++){
		color[i]='b';
	}
	int gg[555][555];
	for(int u,v,i = 1;i<=m;i++){
		cin >> u >> v;
		gg[u][v]=1;
		gg[v][u]=1;
	}
	for(int i = 1;i<=n;i++)for(int j = 1;j<=n;j++)if(gg[i][j]==0 && i!=j)pg[i].push_back(j);
	bool l=true;
	for(int i = 1;i<=n;i++){
		if(color[i]=='b' && !pg[i].empty()){
			l &= dfs(i,'a');
		}
	}
	if(l){
		string temp="";
		for(int i = 1;i<=n;i++)temp+=color[i];
		bool flag=true;
		for(int i = 0;i<temp.size();i++){
			for(int j = 0;j<temp.size();j++){
				if(gg[i+1][j+1]==1 && (temp[i]=='a' && temp[j]=='c' || temp[i]=='c' && temp[j]=='a')){
					flag=false;
				}
			}
		}
		if(flag){
			cout << "Yes" << endl << temp;
		}else{
			cout << "No" << endl;
		}
	}else{
		cout << "No" << endl;
	}
	return 0;
}
```

---

## 作者：qwq___qaq (赞：0)

\* 1800，评什么蓝，建议降黄/绿。

容易想到只有 `a` 与 `c` 之间没有边，`b` 和每一个之间都有边。

于是建补图进行二分图判定，二染色后得到的颜色分别为 `a` 和 `c`。

但是这样会 WA on 26，把这个数据搞下来你会发现补图的两个部之间在原图上仍然有边。

于是我们把得到的字符串按照题意生成一个图出来，判断它是否和原图一样即可。

---

## 作者：ylch (赞：0)

Link：[Luogu - CF623A](https://www.luogu.com.cn/problem/CF623A)

## Description
给出一个由字符串 $s$ 建图的过程。

- 字符仅有 $a,b,c$ 三种，建出的图中第 $i$ 个顶点表示原来的第 $i$ 个字符。
- $i$ 与 $j$ 有连边，当且仅当 $s[i]$ 与 $s[j]$ 相同或 $s[i]$ 和 $s[j]$ 是相邻的字符（$a$ 与 $b$ 相邻，$b$ 与 $c$ 相邻）

现给出由某个字符串 $s$ 建出的图，构造一个字符串使其符合上面的要求要求，或者回答不存在这样的字符串。

## Analysis

这道题乍一看很懵。不要慌，去找性质和规律！

首先，如果两个节点没有连边，则它们一定是 `a` 和 `c`。

这里用“补图”的思想：把原图中没有连边的连上边，连了边的连上边。

这样操作之后，我们就得到一张新图。我们要给这些新图里相连的（原图里不相连的）交替变成 `a`,`c`（保证标记为 `a`,`c` 的点不与标号相同的点连接）。

这明显就是一个二分图染色的问题。如果补图不是二分图，那么一定不行。
如果是，那么就按照 `a`,`c` 染色，图中的孤点就一定是 `b`（只有 `b` 可以和其他所有点 `a`,`b`,`c` 相连，所以在补图中的孤点一定是之前的边全被删掉了）。

然后……就结束了。？

当然不是！因为这道题还有一些规则：相同字母的点可以连线，相邻字母的点（`a` 和 `b`，`b` 和 `c`）也可以连线。

所以上面染色的还可能不对，可以再暴力枚举检测一遍。如果原来连的边没了 或 原来没有的边连上了，就不可以。

最后的最后，如果这个答案能够坚持到现在，那么一定可以了。

## AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 505, maxm = 125000; // 500*500/2=125000

int n, m;
int g[maxn][maxn];
vector <int> G[maxn];
char col[maxn]; // 每个点的染色标记

inline char f(char c){
	return (c == 'a'? 'c' : 'a');
}

int dfs(int u, char c){
	col[u] = c;
	for(int v : G[u]){
		if(col[v] == c) return 0; // 染色重复，说明不是二分图
		if(col[v] == 0 && dfs(v, f(c)) == 0) return 0;
	}
	return 1;
}

bool connect(int u, int v){
	if(col[u] == col[v]) return true; // 相等
	if((col[u]=='a'&&col[v]=='b') || (col[u]=='b'&&col[v]=='c')
		|| (col[u]=='b'&&col[v]=='a') || (col[u]=='c'&&col[v]=='b')) return true; // 相差1
	return false; // 否则不相连
}

void solve()
{
	cin >> n >> m;
	for(int u, v, i = 1; i <= m; i ++){
		cin >> u >> v;
		g[u][v] = g[v][u] = 1;
	}
	
	// 建补图
	for(int i = 1; i <= n; i ++){
		for(int j = i + 1; j <= n; j ++){
			if(!g[i][j]){
				G[i].push_back(j);
				G[j].push_back(i);
			}
		}
	}
	
	// 二分图判断+染色
	int flag = 1; // 补图是不是二分图
	for(int i = 1; i <= n; i ++){
		if(G[i].size() == 0) col[i] = 'b'; // 孤点的标记是b
		else if(col[i] == 0 && dfs(i, 'a') == 0) flag = 0; // 染色失败
	}
	
	// 检查+答案输出
	if(flag == 0){
		cout << "No\n";
	}
	else{
		// 检查染完色之后的图是否符合原图的连边
		for(int i = 1; i <= n; i ++){
			for(int j = i + 1; j <= n; j ++){
				if((!g[i][j] && connect(i, j)) || (g[i][j] && !connect(i, j))){
					cout << "No\n";
					return ;
				}
			}
		}
		
		cout << "Yes\n";
		for(int i = 1; i <= n; i ++) cout << col[i];
	}
}

signed main()
{
	ios :: sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	solve();
	return 0;
}
```

## End

管理员大大辛苦啦~

这里是 ylch，谢谢大家！

---

## 作者：osfly (赞：0)

发现题解里面还没有和我同样的解法。

怎么都是建反图啊。

注意到 `b` 与 `a` 和 `c` 相邻，所以如果 $s_i$ 为 `b` 的话那么节点 $i$ 一定与其他所有节点都有连边。

那么我们可以先找出所有度为 $n-1$ 的点，把它们标记为 `b`，然后删掉这些点。

我们考虑剩下的图，因为相同的字符之间均有连边，所以这张图应当是一个完全图或者两个完全图。

直接洪水填充一下然后判断是否是两张完全图就好了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=510,M=N*N;
int n,m;
int d[N];
char ans[N];
struct edge
{
	int u,v,nxt;
}e[M<<1];
int head[N],tot;
void add(int u,int v)
{
	e[++tot]=edge{u,v,head[u]};
	head[u]=tot;
}
void dfs(int u,char col)
{
	ans[u]=col;
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(ans[v]=='d') dfs(v,col);
	}
}
int A,B,C;
bool check()
{
	for(int i=1;i<=n;i++)
		if(ans[i]=='d') return 0;
	for(int i=1;i<=n;i++)
	{
		if(ans[i]=='a') A++;
		if(ans[i]=='b') B++;
		if(ans[i]=='c') C++;
	}
	for(int i=1;i<=n;i++)
	{
		if(ans[i]=='a'&&d[i]!=B+A-1) return 0;
		if(ans[i]=='c'&&d[i]!=B+C-1) return 0;
	}
	return 1;
}
int main()
{
	memset(ans,'d',sizeof(ans));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		d[u]++,d[v]++;
		add(u,v),add(v,u);
	}
	for(int i=1;i<=n;i++)
		if(d[i]==n-1) ans[i]='b';
	for(int i=1;i<=n;i++)
		if(ans[i]=='d')
		{
			dfs(i,'a');
			break;
		}
	for(int i=1;i<=n;i++)
		if(ans[i]=='d')
		{
			dfs(i,'c');
			break;
		}
	if(check())
	{
		printf("Yes\n");
		for(int i=1;i<=n;i++) printf("%c",ans[i]);
	}
	else printf("No");
	return 0;
}
```

---

## 作者：LittleChara (赞：0)

注意到对于原图直接做的状态可能有很多种，而不相连的情况只有可能是一个 a 和一个 c。

那么我们可以建一个新图，原图没有相连的两个点将他们在新图相连，而原来已经有相连的就不连接。

这样我们可以直接在这个新图上直接做 dfs，并判断相邻点是否可以为不同权值，即判断是否有奇环，然后在每个点上面打 tag 即可。

在 dfs 中如果有相邻环无法为不同权值的情况就是不满足条件的。

这样直接做完会有一个弊端，就是你打完 tag 之后可能会有本该相连的点没有相连，那我们直接判原图中相连的两点在 tag 个限制下是否能连接即可。

如下有一组 hack 数据。

```
7 13
1 2
2 3
1 3
4 5
5 6
4 6
2 5
2 7
3 7
7 4
7 6
7 1
7 5
```

```
No
```

感觉蓝有点虚高。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define ll long long
#define ull unsigned ll
#define i128 __int128
#define db double
#define ld long db

#define M 505
#define N 105
#define mod 998244353
#define mod2 1222827239
#define base 51787
#define base2 38833
#define inf 1e9+7
#define dinf 1e15
#define linf 7e18

int n,m;
int e[M][M];
vector<int> g[M];

int lx[M];
bool ok=1;

void dfs(int u,int x){
//	printf("%d %d\n",u,x);
	if(!ok) return;
	lx[u]=x;
	for(auto v:g[u]){
		if(lx[v]){
			if(x==lx[v]){
				ok=0;
				return;
			}
		} else dfs(v,-x);
	}
}

void pri(int x){
	if(x==-1) printf("a");
	if(x==1) printf("c");
	if(!x) printf("b");
}

int main(){
	scanf("%d %d",&n,&m);
	while(m--){
		int u,v;
		scanf("%d %d",&u,&v);
		e[u][v]=e[v][u]=1;
	}
	for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) if(!e[i][j]&&i!=j) g[i].push_back(j);
	for(int i=1;i<=n;++i) if(!lx[i]&&!g[i].empty()) dfs(i,1);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			if(e[i][j]&&abs(lx[i]-lx[j])>1) ok=0;
		}
	}
	if(!ok) printf("No\n");
	else {
		printf("Yes\n");
		for(int i=1;i<=n;++i) pri(lx[i]);
	}
	return 0;
}
```


---

## 作者：james1BadCreeper (赞：0)

本身边的数量过多，不好处理，但是这样发现一件事情：只有 `a` 和 `c` 之间是没有连边的。

那么搞出原图的反图，有解的**必要条件**是我们可以对这张图进行黑白染色，也就是将点标成 `a` 和 `c`。

如果一个点在原图中与所有点都有连边，那么它应该是 `b`。

但是这样只能保证两个点之间没有边，所以最后需要检查一遍是否有了原图中所有的边。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m, col[505]; 
bool E[505][505]; 
vector<int> G[505]; 

int main(void) {
	scanf("%d%d", &n, &m); 
	while (m--) {
		int u, v; scanf("%d%d", &u, &v); 
		E[u][v] = E[v][u] = 1; 
	}
	for (int i = 1; i < n; ++i) for (int j = i + 1; j <= n; ++j) if (!E[i][j]) G[i].emplace_back(j), G[j].emplace_back(i); 
	memset(col, -1, sizeof col); 
	for (int i = 1; i <= n; ++i) if (col[i] == -1 && G[i].size()) {
		col[i] = 1; queue<int> q; q.push(i); 
		while (!q.empty()) {
			int u = q.front(); q.pop(); 
			for (int v : G[u])
				if (col[v] == -1) col[v] = 3 - col[u], q.push(v); 
				else if (col[u] == col[v]) return puts("No"), 0; 
		}
	}
	for (int i = 1; i <= n; ++i) for (int j = i + 1; j <= n; ++j) if (E[i][j] && col[i] + col[j] == 3) return puts("No"), 0; 
	puts("Yes"); 
	for (int i = 1; i <= n; ++i) putchar(col[i] == -1 ? 'b' : (col[i] == 1 ? 'a' : 'c')); 
	return putchar('\n'), 0; 
}
```

---

## 作者：hzx360 (赞：0)

前言：感谢审核大大百忙中审核 MnZn 题解。

### 题意：
- 一个字符串由 a，b，c 至少一种字母组成。
- 位置 $i$ 与 $j$ 连边当且仅当着俩位置的字符相邻或相同。

说人话就是：

1. $a$ 可以与 $a$ 和 $b$ 连边。
2. $b$ 可以与 $a$ 和 $b$ 和 $c$ 连边。
3. $c$ 可以与 $b$ 和 $c$ 连边。

### Solution

那这不就简单了，因为 $b$ 与谁都连了，可以直接把它找出来然后不理会它，剩下就是最多不连通的两个联通块，check 一下连通块个数是否满足条件即可。

不过值得注意的是同一联通块内还应检验是否互相有连边（因为同一块内字符相同）。

具体操作用并查集实现，不难。

### Code

```
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+100;
int fa[N];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void merge(int x,int y){
	int X=find(x),Y=find(y);
	if(X>Y) swap(X,Y);
	if(X!=Y) fa[X]=Y;
}
int n,m,in[N],x[N],y[N];
bool flag[N],vis[N],yes[510][510];
int a[4],num=0;
bool check(){
	int line1[N],line2[N],cnt1=0,cnt2=0;
	for(int i=1;i<=n;i++){
		if(flag[i]) continue;
		int f=find(i);
		if(f==a[1]) line1[++cnt1]=i;
		else if(f==a[2]) line2[++cnt2]=i;
	}
	for(int i=1;i<cnt1;i++) for(int j=i+1;j<=cnt1;j++) if(!yes[line1[i]][line1[j]]) return 0;
	for(int i=1;i<cnt2;i++) for(int j=i+1;j<=cnt2;j++) if(!yes[line2[i]][line2[j]]) return 0;
	return 1;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>x[i]>>y[i];
		in[x[i]]++,in[y[i]]++;
		yes[x[i]][y[i]]=yes[y[i]][x[i]]=1;
	}
	for(int i=1;i<=n;i++){
		fa[i]=i;
		if(in[i]==n-1) flag[i]=1;
	}
	for(int i=1;i<=m;i++){
		if(flag[x[i]] or flag[y[i]]) continue;
		merge(x[i],y[i]);
	}
	for(int i=1;i<=n;i++){
		//if(flag[i]) cout<<i<<"P"<<endl;
		if(fa[i]==i and !flag[i]){
			num++;if(num>2) return puts("No"),0;
			a[num]=i;
		}
	}
	if(!check()) return puts("No"),0;
	cout<<"Yes"<<endl;
	for(int i=1;i<=n;i++){
		if(flag[i]) cout<<'b';
		else if(find(i)==a[1]) cout<<'a';
		else cout<<'c';
	}
}

---

## 作者：RainFestival (赞：0)

首先注意到 $\texttt{b}$ 字符与所有字符连边

所以我们可以非常容易地求出哪些节点是 $\texttt{b}$ 字符

然后我们去掉其他字符连接 $\texttt{b}$ 的连边

容易发现如果有合法的构造方案

一定是 $2$ 个完全图，一个全是 $\texttt{a}$ ,一个全是 $\texttt{c}$

时间复杂度 $O(n+m)$

代码如下：

```cpp
#include<cstdio>
#include<queue> 
#include<vector>
#include<cstdlib>
#include<algorithm>
std::vector<int> a[100005];
int n,m,col[100005],cnt[100005];
void add(int x,int y){a[x].push_back(y);a[y].push_back(x);}
void bfs(int s,int k)
{
	int sz=0;
	std::queue<int> q;
	col[s]=k;q.push(s);
	while (!q.empty())
	{
		int v=q.front();q.pop();
		for (int i=0;i<a[v].size();i++)
		{
			int u=a[v][i];
			if (col[u]) continue;
			++sz;
			col[u]=k;
			q.push(u);
		}
	}
	for (int i=1;i<=n;i++) if (col[i]==k&&cnt[i]!=sz){puts("No");exit(0);}
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	for (int i=1;i<=n;i++) if (a[i].size()==n-1) col[i]=2;
	for (int i=1;i<=n;i++) for (int j=0;j<a[i].size();j++) if (!col[a[i][j]]) ++cnt[i];
	int k;
	for (k=1;k<=n;k++) if (!col[k]) break;
	bfs(k,1);
	for (k=1;k<=n;k++) if (!col[k]) break;
	bfs(k,3);
	for (int i=1;i<=n;i++) if (!col[i]){puts("No");return 0;}
	puts("Yes");
	for (int i=1;i<=n;i++) printf("%c",col[i]+96);
	puts("");
	return 0;
}
```


---

