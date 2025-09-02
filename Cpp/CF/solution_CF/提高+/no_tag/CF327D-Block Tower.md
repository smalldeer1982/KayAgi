# Block Tower

## 题目描述

After too much playing on paper, Iahub has switched to computer games. The game he plays is called "Block Towers". It is played in a rectangular grid with $ n $ rows and $ m $ columns (it contains $ n×m $ cells). The goal of the game is to build your own city. Some cells in the grid are big holes, where Iahub can't build any building. The rest of cells are empty. In some empty cell Iahub can build exactly one tower of two following types:

1. Blue towers. Each has population limit equal to $ 100 $ .
2. Red towers. Each has population limit equal to $ 200 $ . However, it can be built in some cell only if in that moment at least one of the neighbouring cells has a Blue Tower. Two cells are neighbours is they share a side.

Iahub is also allowed to destroy a building from any cell. He can do this operation as much as he wants. After destroying a building, the other buildings are not influenced, and the destroyed cell becomes empty (so Iahub can build a tower in this cell if needed, see the second example for such a case).

Iahub can convince as many population as he wants to come into his city. So he needs to configure his city to allow maximum population possible. Therefore he should find a sequence of operations that builds the city in an optimal way, so that total population limit is as large as possible.

He says he's the best at this game, but he doesn't have the optimal solution. Write a program that calculates the optimal one, to show him that he's not as good as he thinks.

## 样例 #1

### 输入

```
2 3
..#
.#.
```

### 输出

```
4
B 1 1
R 1 2
R 2 1
B 2 3
```

## 样例 #2

### 输入

```
1 3
...
```

### 输出

```
5
B 1 1
B 1 2
R 1 3
D 1 2
R 1 2
```

# 题解

## 作者：米奇奇米 (赞：3)

## 题解-CF327D Block Tower

### **题目意思**

就是让你想尽所有的方法让容量最大，有$spj$的

### $Solution$

* **贪心+广搜**

我们先把所有的点都建成绿塔，然后开始$bfs$一遍,然后呢把一个一个绿塔除掉变成红塔知道栈尾只有一个元素为止。

### $Code$
```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxstep=1000005+5;
char ch[505][505];
int n,m,s,ans,vis[505][505],step[maxstep][3];

const int dx[]={0,0,-1,1};
const int dy[]={-1,1,0,0};

struct nood {
	int x,y;
} q[260005];

inline void bfs(int x,int y) {
	int head=1,tail=1;
	q[1].x=x,q[1].y=y;
	vis[q[1].x][q[1].y]=1;
	while(head<=tail) {
		for ( int i=0;i<=3;i++ ) {
			int tx=dx[i]+q[head].x;
			int ty=dy[i]+q[head].y;
			if(ch[tx][ty]=='.'&&vis[tx][ty]==0) {
				vis[tx][ty]=1;
				tail++;
				q[tail].x=tx;
				q[tail].y=ty;
			}
		}
		head++;
	}
	for ( int i=tail;i>1;i-- ) {
		int ux=q[i].x,uy=q[i].y;
		ch[ux][uy]='#';
		step[++s][1]=2;
		step[s][2]=ux;
		step[s][3]=uy;
		step[++s][1]=3;
		step[s][2]=ux;
		step[s][3]=uy;
	}
}

int main() {
	scanf("%d%d",&n,&m);
	for ( int i=1;i<=n;i++ ) scanf("%s",ch[i]+1);
	for ( int i=1;i<=n;i++ ) 
		for ( int j=1;j<=m;j++ ) 
			if(ch[i][j]=='.') {
				step[++s][1]=1;
				step[s][2]=i;
				step[s][3]=j;
			}
	for ( int i=1;i<=n;i++ ) 
		for ( int j=1;j<=m;j++ ) 
			if(ch[i][j]=='.') bfs(i,j);
	printf("%d\n",s);
	for ( int i=1;i<=s;i++ ) {
		if(step[i][1]==1) putchar('B');
		else 
			if(step[i][1]==2) putchar('D');
			else putchar('R');
		printf(" %d %d\n",step[i][2],step[i][3]);
	}
	return 0;
}
```



---

## 作者：Ninelife_Cat (赞：1)

由于红房子能容纳的人比蓝房子多，所以显然要建造尽可能多的红房子。但这样最多也只能做到红蓝房子交错分布，那该怎么办呢？

注意题目中的一句话。

>拆除蓝房子不影响已经建造的红房子。

再加上题目没有限制操作次数，那我们就有个大胆的想法：先把每个连通块内全部建上蓝房子，然后从最外边依次把蓝房子拆掉，改成红房子，直到连通块中只存在一个蓝房子。

至于为什么要从外往内拆，是因为如果先拆了里面的，就可能会导致某个位置四周不存在蓝房子，从而无法建造红房子。

核心代码：

```cpp
#define endl '\n'
#define fir first
#define sec second
#define ri register
#define mp make_pair
#define pb push_back
#define int long long
const int N=521,dx[4]={0,0,-1,1},dy[4]={-1,1,0,0};
int n,m;
char a[N][N];
bool vis[N][N];
vector<pair<char,pair<int,int> > > v;//记录答案
inline void Dfs(int x,int y)
{
	vis[x][y]=1;v.pb(mp('B',mp(x,y)));
	for(ri int i=0;i<4;++i)
	{
		ri int tx=x+dx[i],ty=y+dy[i];
		if(tx>0&&ty>0&&tx<=n&&ty<=n&&!vis[tx][ty]&&a[tx][ty]=='.')
			Dfs(tx,ty);
	}
}
inline void Dfs2(int x,int y)
{
	for(ri int i=0;i<4;++i)
	{
		ri int tx=x+dx[i],ty=y+dy[i];
		if(tx>0&&ty>0&&tx<=n&&ty<=m&&!vis[tx][ty]&&a[tx][ty]=='.')
			vis[tx][ty]=1,Dfs2(tx,ty),v.pb(mp('D',mp(tx,ty))),v.pb(mp('R',mp(tx,ty)));
	}
}
signed main()
{
	fastcin;cin>>n>>m;
	for(ri int i=1;i<=n;++i)
		for(ri int j=1;j<=m;++j)
			cin>>a[i][j];
	for(ri int i=1;i<=n;++i)
		for(ri int j=1;j<=m;++j)
			if(!vis[i][j]&&a[i][j]=='.') Dfs(i,j);//先全部建成蓝房子
	reset(vis,0);
	for(ri int i=1;i<=n;++i)
		for(ri int j=1;j<=m;++j)
			if(!vis[i][j]&&a[i][j]=='.') vis[i][j]=1,Dfs2(i,j);//把蓝房子拆了改成红房子
	cout<<v.size()<<endl;
	for(ri int i=0;i<v.size();++i)
		cout<<v[i].fir<<" "<<v[i].sec.fir<<" "<<v[i].sec.sec<<endl;
	return 0;
}
```

---

## 作者：cike_bilibili (赞：0)

# 思路
看完题面注意到其实就是模拟 DFS 的过程，我们可以先选择一个点开始 DFS 并染上蓝色，到无路可走时染上红色并开始回溯，回溯时拆掉原来的蓝色并染上红色，每一个点只会搜到一遍所以时间复杂度 $O(nm)$。
# AC CODE 
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(){
	int ans=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		ans=(ans<<1)+(ans<<3)+ch-'0';
		ch=getchar();
	}
	return w*ans;
}
int n,m;
char ch[505][505];
bool vis[505][505];
int dx[4]={1,0,-1,0},dy[4]={0,-1,0,1}; 
bool check(int x,int y){
	for(int i=0;i<4;i++){
		int tx=x+dx[i],ty=y+dy[i];
		if(!vis[tx][ty]&&ch[tx][ty]=='.')return 0;
	}
	return 1;
}
int yx,yy;
struct node{
	char ch;
	int x,y;
}ans[1000005];
int top;
void dfs(int x,int y){
	vis[x][y]=1;
	if(check(x,y)&&(x!=yx||y!=yy)){
		ans[++top]={'R',x,y};
		return ;
	}
	ans[++top]={'B',x,y};
	for(int i=0;i<4;i++){
		int tx=x+dx[i],ty=y+dy[i];
		if(!vis[tx][ty]&&ch[tx][ty]=='.')dfs(tx,ty);
	}
	if(x!=yx||y!=yy){
		ans[++top]={'D',x,y};
		ans[++top]={'R',x,y};
	}
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		string s;
		cin>>s;
		for(int j=1;j<=m;j++)ch[i][j]=s[j-1];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(!vis[i][j]&&ch[i][j]=='.')yx=i,yy=j,dfs(i,j);
		}
	}
	cout<<top<<'\n';
	for(int i=1;i<=top;i++){
		cout<<ans[i].ch<<' '<<ans[i].x<<' '<<ans[i].y<<'\n';
	}
	return 0;
}
```

---

## 作者：WorldMachine (赞：0)

### Solution

首先肯定要多建容量大的红房子。由于拆除蓝房子不影响已经建造的红房子，我们可以像剥洋葱那样，从外向内依次把蓝房子拆掉建成红房子，直到最内层只剩下一个蓝房子即可。这一点可以通过修改 dfs 的顺序实现。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 505, d[] = {-1, 0, 1, 0, -1};
int n, m, t;
char s[N][N];
bool v[N][N];
struct node { char c; int x, y; } p[N * N * 3];
#define check(x, y) (x >= 1 && x <= n && y >= 1 && y <= m && s[x][y] == '.' && !v[x][y])
void dfs(int x, int y) {
	v[x][y] = 1;
	p[++t] = {'B', x, y};
	for (int i = 0, xx, yy; i < 4; i++) {
		xx = x + d[i], yy = y + d[i + 1];
		if (check(xx, yy)) dfs(xx, yy);
	}
}
void Dfs(int x, int y) {
	v[x][y] = 1;
	for (int i = 0, xx, yy; i < 4; i++) {
		xx = x + d[i], yy = y + d[i + 1];
		if (check(xx, yy)) {
			Dfs(xx, yy);
			p[++t] = {'D', xx, yy};
			p[++t] = {'R', xx, yy};
		}
	}
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%s", s[i] + 1);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (s[i][j] == '.' && !v[i][j]) dfs(i, j);
		}
	}
	memset(v, 0, sizeof(v));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (s[i][j] == '.' && !v[i][j]) Dfs(i, j);
		}
	}
	printf("%d\n", t);
	for (int i = 1; i <= t; i++) printf("%c %d %d\n", p[i].c, p[i].x, p[i].y);
}
```

---

## 作者：XL4453 (赞：0)

### 解题思路：

这道题不要求操作数最小，那么就考虑如何让操作最无脑。

首先将所有的空地全都变成蓝色建筑，然后尝试将一定量的蓝色建筑变成红色建筑，这里考虑从 BFS 之后反向操作，将蓝色拆掉改建红色。

这样的一个做法显然是可行的，因为在 BFS 中每一个节点都由之前的某一个节点拓展而来，而这样的一个节点也一定不会在其后继节点完成操作之前被更改。

另一方面，这样的操作也一定是最优的，因为在这样的操作结束之后，每一个联通块都剩下且仅剩下了一个蓝色建筑，而这样的一个蓝色建筑是不可避免的，所以一定最优。

---
### 代码：
```cpp
#include<cstdio>
using namespace std;
struct node{
	int x,y;
	char c;
}ans[10000005];;
int n,m,a[505][505],cnt;
int dx[10]={0,0,1,-1};
int dy[10]={1,-1,0,0};
char get(){
	char c=getchar();
	while(c=='\n'||c==' '||c=='\r')c=getchar();
	return c;
}
void work(char c,int x,int y){
	ans[++cnt].c=c;
	ans[cnt].x=x;
	ans[cnt].y=y;
}
void dfs(int x,int y,int fi){
//	printf("B %d %d\n",x,y);
	work('B',x,y);
	a[x][y]=0;
	for(int i=0;i<=3;i++)
	if(a[x+dx[i]][y+dy[i]]==1)
	dfs(x+dx[i],y+dy[i],0);
	if(fi==0){
		work('D',x,y);
		work('R',x,y);
//		printf("D %d %d\n",x,y);
//		printf("R %d %d\n",x,y);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	if(get()=='.')a[i][j]=1;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	if(a[i][j]==1)dfs(i,j,1);
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++)
	printf("%c %d %d\n",ans[i].c,ans[i].x,ans[i].y);
	return 0;
}
```


---

