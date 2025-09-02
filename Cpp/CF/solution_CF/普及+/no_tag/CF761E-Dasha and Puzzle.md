# Dasha and Puzzle

## 题目描述

Dasha decided to have a rest after solving the problem. She had been ready to start her favourite activity — origami, but remembered the puzzle that she could not solve.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF761E/f94317c6a4e9720232d894633f6f0c7ec38b7c88.png)The tree is a non-oriented connected graph without cycles. In particular, there always are $ n-1 $ edges in a tree with $ n $ vertices.

The puzzle is to position the vertices at the points of the Cartesian plane with integral coordinates, so that the segments between the vertices connected by edges are parallel to the coordinate axes. Also, the intersection of segments is allowed only at their ends. Distinct vertices should be placed at different points.

Help Dasha to find any suitable way to position the tree vertices on the plane.

It is guaranteed that if it is possible to position the tree vertices on the plane without violating the condition which is given above, then you can do it by using points with integral coordinates which don't exceed $ 10^{18} $ in absolute value.

## 说明/提示

In the first sample one of the possible positions of tree is: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF761E/9f7bd78ab90b0ce22425fab0baf00155435088d1.png)

## 样例 #1

### 输入

```
7
1 2
1 3
2 4
2 5
3 6
3 7```

### 输出

```
YES
0 0
1 0
0 1
2 0
1 -1
-1 1
0 2```

## 样例 #2

### 输入

```
6
1 2
2 3
2 4
2 5
2 6
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
4
1 2
2 3
3 4```

### 输出

```
YES
3 3
4 3
5 3
6 3```

# 题解

## 作者：Chenyanxi0829 (赞：2)

先判无解，当有某个节点的度数大于 $4$ 时显然无解。接着就可以直接构造方案，以任意节点为根开始给每个儿子确定坐标，这些儿子的方向可以任意选，只要不和这个点与其父亲连接的边重合就可以，为了保证边不相交只需要把这条边的长度设成 $2^{n-deep}$ 就可以了（其中 $deep$ 表示这个点的深度），因为 $2^x>2^{x-1}+2^{x-2}+\dots +2^0$，所以之后的边就算全加起来也不可能与这条边相交，就做完了。

## 代码
其他细节见代码。
```cpp
#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 31, dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};

int n, X[kMaxN], Y[kMaxN];
vector<int> e[kMaxN];

void dfs(int x, int L, int A, int d) {
  int W = 0;
  for (int i : e[x]) {
    if (i != A) {
      W += (W == L), X[i] = X[x] + dx[W] * (1 << (n - d)), Y[i] = Y[x] + dy[W] * (1 << (n - d)), dfs(i, (W ^ 1), x, d + 1), W++;
    }
  }
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1, u, v; i < n; i++) {
    cin >> u >> v, e[u].push_back(v), e[v].push_back(u);
  }
  for (int i = 1; i <= n; i++) {
    if (e[i].size() > 4) {
      cout << "NO", exit(0);
    }
  }
  cout << "YES\n";
  dfs(1, -1, 0, 0);
  for (int i = 1; i <= n; i++) {
    cout << X[i] << ' ' << Y[i] << '\n';
  }
  return 0;
}
```

---

## 作者：npqenqpve (赞：2)

### 思路：

无解显然等价于存在点度大于 $4$ 的节点，因为与 $(x,y)$ 关于坐标轴平行的点满足边不相交只有 $4$ 个

钦定 $1$ 为根


第一反应是边权要尽量大，要不然容易出现兄弟节点重合的情况，但由于边不能相交，所以边权要随着树的层数的增加不断减小，假设深度为 $d$，$i$ 和它子节点的连边的权值是 $p_i$，那么应该满足对于任意 $i$，都有 $p_i > \sum_{i< k \leq d} p_k$，满足这个等式的构造方法是显然的，即对于任意 $1\leq i\leq d$，满足$p_i=2^{n-i+1}$，因为 $n$ 很小，所以不必担心跑出 $10^{18}$。

现在每条边的权值已经得到，还需要考虑 $u$ 的子节点的方向不能朝向 $u$ 的父节点，记录来的方向即可。

### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
#define ld long double
using namespace std;
int n,d[50];
bool f=0;
vector<int>edge[50];
struct node
{
	int x,y;
};
node p[50];
map<pair<int,int>,bool>m;
void dfs(int u,int fa,int len,int from)
{
	for(int i=0;i<edge[u].size();i++)
	{
		int v=edge[u][i];
		if(v==fa) continue;
		int f;
		if(!m[make_pair(p[u].x,p[u].y+len)]&&from!=4) p[v]=(node){p[u].x,p[u].y+len},m[make_pair(p[u].x,p[u].y+len)]=1,f=1;
		else if(!m[make_pair(p[u].x,p[u].y-len)]&&from!=1) p[v]=(node){p[u].x,p[u].y-len},m[make_pair(p[u].x,p[u].y-len)]=1,f=4;
		else if(!m[make_pair(p[u].x+len,p[u].y)]&&from!=3) p[v]=(node){p[u].x+len,p[u].y},m[make_pair(p[u].x+len,p[u].y)]=1,f=2; 
		else if(!m[make_pair(p[u].x-len,p[u].y)]&&from!=2) p[v]=(node){p[u].x-len,p[u].y},m[make_pair(p[u].x-len,p[u].y)]=1,f=3;
		dfs(v,u,len/2,f);
	}
}
signed main()
{
	cin>>n;
	for(int i=1;i<n;i++) 
	{
		int u,v;cin>>u>>v;
		edge[u].push_back(v);
		edge[v].push_back(u);
		d[u]++,d[v]++;
	}
	for(int i=1;i<=n;i++)
	{
		if(d[i]>4) f=1;
	}
	if(f==1) puts("NO");
	else 
	{
		puts("YES");
		p[1]=(node){0,0};m[make_pair(0,0)]=1;
		dfs(1,0,2147483647,0);
//		for(int i=1;i<=n;i++) cout<<d[i]<<" ";
//		puts("");
		for(int i=1;i<=n;i++) cout<<p[i].x<<" "<<p[i].y<<"\n";
	}
}
```

---

## 作者：kradcigam (赞：2)

这道题非常有意思。

首先存在点的度数 $>4$ 即无解。

因为要和坐标轴平行，且要求路径不能相交，那么点显然更不能相交，但只有 $4$ 个象限，最多只能向 $4$ 个象限分别连一条边，所以当度数超过 $4$ 的时候无解。

如何保证不相交？我们注意到 $n$ 到数据范围特别小，只到 $30$，相比之下边权到范围非常大。甚至 $2^n$ 都是完全可以通过的。于是我们可以把根放在原点，边的长度为 $2^{31-dep}$，向 $4$ 个不同方向连出边。

DFS 一遍即可。

这道题就做完了！

代码非常简短：

```cpp
#include<bits/stdc++.h>
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define LL long long
#define SZ(x) ((int)x.size()-1)
#define ms(a,b) memset(a,b,sizeof a)
#define F(i,a,b) for(int i=(a);i<=(b);++i)
#define DF(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
inline int read(){char ch=getchar(); int w=1,c=0;
	for(;!isdigit(ch);ch=getchar()) if (ch=='-') w=-1;
	for(;isdigit(ch);ch=getchar()) c=(c<<1)+(c<<3)+(ch^48);
	return w*c;
}
const int N=35;
vector<int>v[N];
int dep[N],h[N];LL kx[N],ky[N];
void dfs(int x,int fa){
	dep[x]=dep[fa]+1;
	LL k=(1ll<<(30-dep[x]));
	int z=-1;
	F(i,0,SZ(v[x]))
		if(v[x][i]!=fa){
			kx[v[x][i]]=kx[x];
			ky[v[x][i]]=ky[x];
			z++;
			if(z==(h[x]^1))z++;
			h[v[x][i]]=z;
			if(z==0)kx[v[x][i]]+=k;
			if(z==1)kx[v[x][i]]-=k;
			if(z==2)ky[v[x][i]]+=k;
			if(z==3)ky[v[x][i]]-=k;
			dfs(v[x][i],x);
		}
}
signed main(){
	int n=read();
	F(i,2,n){
		int x=read(),y=read();
		v[x].push_back(y);
		v[y].push_back(x);
	}
	F(i,1,n)
		if(v[i].size()>4){
			puts("NO");
			return 0;
		}
	h[1]=-1;
	dfs(1,0);
	puts("YES");
	F(i,1,n)cout<<kx[i]<<" "<<ky[i]<<endl;
	return 0;
}
```



---

## 作者：water_tomato (赞：2)

个人觉得这道题目还是比较有意思的，如果你没有很好发现性质的话就会像我一样搞 rand 之类的阴间东西搞了一个多小时还做不出来……
## 题意
[题目链接](https://www.luogu.com.cn/problem/CF761E)

大体见翻译。注意树被"拍扁"到平面中之后，要求所有边都与坐标轴平行，且所有点是整点。

## 解析
首先有一件很显然的事情，就是如果有任意一个点的度数大于 $4$，结果一定为 $-1$，因为由于边的方向只有上下左右四种，所有第五条边是无论如何也无法连出去的。

接着考虑对于可行的情况，我们只需要满足没有任何两条边相交就可以了。那么我们考虑什么情况下边会发生相交。

![](https://cdn.luogu.com.cn/upload/image_hosting/ugqagcw1.png)

观察上图，我们发现，发生了相交的情况，以上图为例，就意味着 $CD+DE+EF>AB$ 且 $BG>AC$。

那么我们如何避免这种情况的出现呢？我们发现 $n$ 的范围只有 $30$，从而我们想到一个式子：

$$2^k>2^{k-1}+2^{k-2}…+2^1+2^0$$

因此我们可以在进行 dfs 绘点时，每次向下传递时都让 $k$ 减一，这样，上图中的 $CD+DE+EF$ 或是 $BG$ 最大（全满）时也仅能是 $AB-1$。

然后在 dfs 里还需要注意一点，就是不能往“来”时的方向，即父亲的方向走，记录一下即可。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=55;
int n,du[N];
struct edge{
	int to,next;
}e[N<<1];
int head[N],cnt,ansx[N],ansy[N];
int pos[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
inline void add(int u,int v){
	e[++cnt].to=v;
	e[cnt].next=head[u];
	head[u]=cnt;
}
inline void dfs(int u,int f,int x,int y,int tag,int from){
	//tag 代表题解中的 k，from 代表父亲所在的方向 
	int tot=0;//tot 表示当前即将要走的方向 
	ansx[u]=x,ansy[u]=y;
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to;
		if(v==f) continue;
		if(tot==from) tot++;
		dfs(v,u,x+(1<<tag)*pos[tot][0],y+(1<<tag)*pos[tot][1],tag-1,(tot+2)%4);
		tot++;
	} 
}
signed main(){
	scanf("%lld",&n);
	for(int i=1,u,v;i<n;i++){
		scanf("%lld%lld",&u,&v);
		add(u,v);add(v,u);
		du[u]++;du[v]++;
		if(du[u]>4||du[v]>4){//度数超 4 
			printf("NO");
			return 0;
		}
	}
	dfs(1,0,0,0,30,-1);//这个 30 实际上也可以大一点 
	printf("YES\n");
	for(int i=1;i<=n;i++){
		printf("%lld %lld\n",ansx[i],ansy[i]);
	}
	return 0;
}
```


---

