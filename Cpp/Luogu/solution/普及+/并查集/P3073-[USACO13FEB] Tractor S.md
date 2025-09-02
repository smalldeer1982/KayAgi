# [USACO13FEB] Tractor S

## 题目描述

FJ有块农田太崎岖了，他要买一辆新拖拉机才能在这里巡视。这块农田由N x N个格子的非负整数表示高度(1<=N<=500)。拖拉机从当前格子走到相邻格子（东、南、西、北四个方向）的代价为高度差D，则FJ驶过这两个格子的拖拉机最少也要值D块钱。

FJ愿意花足够的钱买一辆新的拖拉机使得他能以最小的高度差走遍所有格子的一半(如果格子总数是奇数，那么一半的值为四舍五入的值)。因为FJ很懒，所以他找到你帮他编程计算他最小需要花多少钱买到符合这些要求的拖拉机。

## 样例 #1

### 输入

```
5 
0 0 0 3 3 
0 0 0 0 3 
0 9 9 3 3 
9 9 9 3 3 
9 9 9 9 3 
```

### 输出

```
3 
```

# 题解

## 作者：daihang (赞：46)

# 并查集+最小生成树算法
#### 题目要求最大值最小化，满足最小生成树的性质


------------
### Details

**1.** 建图。除边缘外的每个点均可以向**上下左右**四个方向连边，点的编号可表示为:       _n*(i-1)+j_ (i为行,j为列)

实现代码：

```cpp
int ex(int i,int j){
	return (i-1)*n+j;
}
```
边的权值即为两点高度差的**绝对值**


**2.** 如何维护集合的大小。初始化将size全设为1，后续再进行合并操作(merge)时，将旧的集合的大小更新到新的集合上。在新的集合大小**大于**(n*n)/2时，输出当前边的权值即可。

实现代码：
```cpp
x=find(x);//find函数是为了找父亲
y=find(y);
if(x!=y){
	fa[x]=y;
	siz[y]+=siz[x];
	if(siz[y]>=(n*n+1)/2){
		cout<<w<<endl;
		return 0;
	}
}
```
**3.** 最小生成树Kruskal 不解释

不会的可以找模板题[P3366 【模板】最小生成树](https://www.luogu.com.cn/problem/P3366)

### 最后送上代码，祝各位~~水题~~切题愉快

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=501;
int n;
int mp[maxn][maxn];
inline int read(){//快读
	int x=0,y=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')y=-y; ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*y;
}
int fa[maxn*maxn];
int siz[maxn*maxn];
struct node{
	int u,v,w;
	node(){}
	node(int uu,int vv,int ww){
		u=uu;
		v=vv;
		w=ww;
	}
}edge[maxn*maxn*4];
bool cmp(const node &a,const node &b){
	return a.w<b.w;
}
int ans=0;
void init(){
	for(int i=1;i<=n*n;i++){
		fa[i]=i;
		siz[i]=1;
	}
}
int find(int x){
	if(x==fa[x]) return x;
	else return fa[x]=find(fa[x]);
}
int ex(int i,int j){
	return (i-1)*n+j;
}
int main(){
	n=read();
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			mp[i][j]=read();
		}
	}
	init();
	int tp=1;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			if(i>1){
				edge[tp]=node(ex(i,j),ex(i-1,j),abs(mp[i-1][j]-mp[i][j]));
				tp++;
			}
			if(j>1){
				edge[tp]=node(ex(i,j),ex(i,j-1),abs(mp[i][j-1]-mp[i][j]));
				tp++;
			}
			if(i<n){
				edge[tp]=node(ex(i,j),ex(i+1,j),abs(mp[i+1][j]-mp[i][j]));
				tp++;
			}
			if(j<n){
				edge[tp]=node(ex(i,j),ex(i,j+1),abs(mp[i][j+1]-mp[i][j]));
				tp++;
			}
		}
	}
	sort(edge+1,edge+tp,cmp);
	for(int i=1;i<tp;i++){
		int x=edge[i].u;
		int y=edge[i].v;
		int w=edge[i].w;
		x=find(x);
	    y=find(y);
	    if(x!=y){
		    fa[x]=y;
		    siz[y]+=siz[x];
		    if(siz[y]>=(n*n+1)/2){
			    cout<<w<<endl;
			    return 0;
		    }
	    }
	}
}
```

 _写题解不易，求个赞_ 

---

## 作者：JJA_ (赞：12)

# 题目大意

[题目链接](https://www.luogu.com.cn/problem/P3073)

让 $Farmer John$ 在花费代价最小的情况下驶过农场的一半，而代价为所经过最大的高度差。

# 思路

由于题目的输入为联通块，所以可以使用 $DFS$ 解题。 [这里是一道相近的基础 $DFS$ 联通块题目。](https://www.luogu.com.cn/problem/P1596) 大体思路就是标记走过的格子，而小于之前最小的高度差都是同一块中的，最后统计走过的所有格子。

## 方法一

暴力 $DFS$

```cpp
int xpos[]={0,0,1,0,-1},ypos[]={0,1,0,-1,0};//搜索上下左右
int dfs(int x,int y,int d){
	int sum=1;//记录走过的格子
	flag[x][y]=1;
	for(int i=1;i<=4;i++){
		int px=x+xpos[i];
		int py=y+ypos[i]; 
		if(abs(mapp[x][y]-mapp[px][py])<=d/*高度差小于d* /&&px>=1&&py>=1&&px<=n&&py<=n/*未发生数组越界* /&&!flag[px][py]/*未被标记* /){
			sum+=dfs(px,py,d);//自己调用自己 
		} 
	}
	return sum;
}
```

之后就是暴力部分。

```cpp
bool chkans(int x){//判断答案是否符合要求 
	memset(flag,0,sizeof(flag));//清空标记 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(!flag[i][j]&&dfs(i,j,x)*2>=n*n){
				return 1;//符合要求，返回 true 
			}
		}
	}
	return 0;
}
```
```cpp
int ans=1;
while(ans++){
	if(chkans(ans))break;
}
```

### 得分 $10pts$ 剩下全部超时。

## 方法二

$DFS+$ 二分

大体思路差不多，二分代码：

```cpp
while(l<=r){
	int mid=(l+r)/2;
	if(chkans(mid)==1){
		r=mid-1,ans=mid;
	}
	else{
		l=mid+1;
	}
}
```

其中 $l r$ 可以在输入 `mapp` 时线性更新。 

```cpp
for(int i=1;i<=n;i++){
	for(int j=1;j<=n;j++){
		cin>>mapp[i][j];
		l=min(mapp[i][j],l);
		r=max(mapp[i][j],r);//线性更新 
	}
}
``` 
但是注意， $l r$ 初始值要赋。

完整代码： 

```cpp
#include<bits/stdc++.h>
#define int long long
#define MAXN 1145140
#define MINN -1
using namespace std;
int n,l=MAXN,r=MINN;
int xpos[]={0,0,1,0,-1},ypos[]={0,1,0,-1,0};
map<int,int> mm;
bool flag[1001][1001];
int mapp[1001][1001];
int dfs(int x,int y,int d){
	int sum=1;
	flag[x][y]=1;
	for(int i=1;i<=4;i++){
		int px=x+xpos[i];
		int py=y+ypos[i];
		if(abs(mapp[x][y]-mapp[px][py])<=d&&px>=1&&py>=1&&px<=n&&py<=n&&!flag[px][py])sum+=dfs(px,py,d);
	}
	return sum;
}
bool chkans(int x){
	memset(flag,0,sizeof(flag));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(!flag[i][j]&&dfs(i,j,x)*2>=n*n){
				return 1;
			}
		}
	}
	return 0;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>mapp[i][j];
			l=min(mapp[i][j],l);
			r=max(mapp[i][j],r);
		}
	}
	int ans=1;
	while(l<=r){
		int mid=(l+r)/2;
		if(chkans(mid)==1){
			r=mid-1,ans=mid;
		}
		else{
			l=mid+1;
		}
	}
	cout<<ans;
}
```
望过审核，谢谢（（（ 

---

## 作者：CR_Raphael (赞：8)

不要理会标签里的“线段树”和“背包”，都是假的QAQ

以相邻两点之差为边权建图。然后跑<伪>最小生成树，维护并查集大小，当最大值大于点数一半时输出当前边

```c++
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

const int inf  =0x7fffffff;
const int maxn =250010;
const int maxm =1000010;
const int maxl =505;

int node[maxl][maxl];
int fa[maxn];
int size[maxn];
int n, m, sum, ans, maxsize, maxi;

struct road {
	int st;
	int en;
	int l;
}r[maxm];

bool operator<(road a, road b){
	return a.l<b.l;
}

bool operator>(road a, road b){
	return a.l>b.l;
}

int find(int a){
	if(fa[a] == a)return a;
	fa[a]=find(fa[a]);
	return fa[a];
} 

void add(int a,int b){
	int faa, fab;
	faa=find(a);
	fab=find(b);
	fa[fab]=faa;
	size[faa]+=size[fab];
	if(size[faa] > maxsize) {
		maxsize=size[faa];
		maxi=faa;
	}
	return;
}

int main() {
	
	int i, j, ii, ta, tb, tc, minn, mint, mi, mj;
	int zi[4]={0, 1}, zj[4]={1, 0};
	road t;
	
	scanf("%d", &n);
	
	for(i=1; i <= n*n; i++)
		fa[i]=i, size[i]=1;
	
	for(i=1; i <= n; i++)
		for(j=1; j <= n; j++)
			scanf("%d", &node[i][j]);
	
	m=0;
	for(i=1; i <= n; i++)
		for(j=1; j <= n; j++) {
			for(ii=0; ii <= 1; ii++){
				mi=i+zi[ii];
				mj=j+zj[ii];
				if(mi > n || mj > n) continue;
				
				m++;
				r[m].st = ( i-1)*n+ j;
				r[m].en = (mi-1)*n+mj;
				r[m].l  = abs(node[i][j] - node[mi][mj]);
			}
		}
	
	sort(r+1,r+1+m);
	
	maxsize=0;
	i=0;
	n=n*n;
	while(maxsize < n/2){
		i++;
		if(i>m)break;
		t=r[i];
		ta=t.en;
		tb=t.st;
		
		if(find(ta)==find(tb))continue;
		
		add(ta, tb);
	}
	
	printf("%d\n", t.l);
	return 0;
}
```

---

## 作者：Rainbow_qwq (赞：5)

[原题链接](https://www.luogu.org/problemnew/show/P3073)

**一道二分答案的好题。**
---

思路：**dfs+二分答案**

由于题目要求的是最大值最小化，所以很容易想到二分答案。

要用二分答案，就要写$check$函数。

怎么写$check$函数呢？我们可以结合$dfs$.

具体请看代码：
```cpp
int n,a[wlxsq][wlxsq],ans;
bool vis[wlxsq][wlxsq];   //标记
int dfs(int x,int y,int k)
//dfs返回一个int,表示在k高度下能到达的格数
{
    vis[x][y]=1;
    int res=1;
    For(i,0,3)
    {
        int xx=x+dx[i],yy=y+dy[i];
        if(xx>0&&yy>0&&xx<=n&&yy<=n&&!vis[xx][yy]&&abs(a[xx][yy]-a[x][y])<=k)
            res+=dfs(xx,yy,k);
    }
    return res;
}
//二分答案 check函数
bool check(int k)
{
    memset(vis,0,sizeof vis);//标记清零
    For(i,1,n)
        For(j,1,n)
            if(!vis[i][j])
                if(dfs(i,j,k)*2>=n*n)
                //超过一半，符合要求
                	return 1;
    return 0;
}
```
接下来就是二分答案。

我把二分答案的$l$设为矩阵中最小值，$r$设为矩阵中最大值，然后二分答案
```cpp
int l=1e6,r=-1,ans;
For(i,1,n)
    For(j,1,n){
       	a[i][j]=read();
        r=max(r,a[i][j]);
        l=min(l,a[i][j]);
    }
while(l<=r)
{
    int mid=(l+r)>>1;
    if(check(mid))r=mid-1,ans=mid;
    	//符合，设置ans与右区间
    else l=mid+1;
}
printf("%d",ans);
```
时间复杂度：二分答案是$O(log m)$,m为答案范围;$dfs$为$O(n^2)$

所以总共是$O(n^2 log m)$

**完整AC代码：**
```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
#define TP int
inline TP read(){//快读
    char c=getchar();TP x=0;bool f=0;
    while(!isdigit(c))f^=!(c^45),c=getchar();
    while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f)x=-x;return x;
}
const int wlxsq=505;
const int dx[]={0,1,0,-1},dy[]={1,0,-1,0};
int n=read(),a[wlxsq][wlxsq],l=1e6,r=-1,ans;
bool vis[wlxsq][wlxsq];
int dfs(int x,int y,int k)
{
    vis[x][y]=1;
    int res=1;
    For(i,0,3)
    {
        int xx=x+dx[i],yy=y+dy[i];
        if(xx>0&&yy>0&&xx<=n&&yy<=n&&!vis[xx][yy]&&abs(a[xx][yy]-a[x][y])<=k)
            res+=dfs(xx,yy,k);
    }
    return res;
}
bool check(int k)
{
    memset(vis,0,sizeof vis);
    For(i,1,n)
        For(j,1,n)
            if(!vis[i][j])
                if(dfs(i,j,k)*2>=n*n)
                	return 1;
    return 0;
}
int main()
{
    For(i,1,n)
        For(j,1,n){
        	a[i][j]=read();
        	r=max(r,a[i][j]);
        	l=min(l,a[i][j]);
        }
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(check(mid))r=mid-1,ans=mid;
        else l=mid+1;
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：KALY (赞：3)

### 给大家提供一个带权并查集+最小生成树的做法。

我觉得很多选择用并查集做的人应该是卡在点是横坐标+纵坐标上了，但其实可以通过一些巧妙的转化使得每个点有一个独一无二的编号。

如果对二维数组理解比较透彻的话应该知道二维数组也可以当作一维数组。



------------


#### 转化原理：

对于一个数 a(i,j) 他前面一共有 (i-1) 行元素加上 j 个元素。

那么就可以直接使用他在二维数组中的位置作为这个点的编号，这样子就可以将
横坐标+纵坐标的点转化为能用单个数字表示的点了。



------------


如果还不会带权并查集 [带权并查集模板题](https://www.luogu.com.cn/problem/P1196)

~~最小生成树的话，您都切蓝题了肯定会~~

#### 代码:
```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<vector>
#include<cmath>
#define  r read()//懒惰
using namespace std;
inline int read()//快读不解释
{
    char c=getchar();
    int x=0,fh=0;
    while(c<'0'||c>'9'){fh|=c=='-';c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return fh?-x:x;
}
struct node //为最小生成树算法的准备
{
    int u,v,w;
    node(int x,int z,int y):u(x),w(z),v(y){}
};
vector<node>g;//存边
int f[501*501];//并查集用的数组
int s[501*501];//存放连通块大小
int t[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
int f1(int a)//找父亲
{
    return f[a]==a?a:f[a]=f1(f[a]);
}
void marge(int a,int b)//合并
{
    int t1=f1(a);
    int t2=f1(b);
    if(t1!=t2)
    {
        s[t1]+=s[t2];//所在维护连通块的大小
        f[t2]=f[t1];//注意：不能反，为什么不能就留做思考题
    }
}
bool cmp(node a,node b)
{
    return a.w<b.w;
}//比较函数
int a[501][501];//存储地图
int main()
{
    int n=r,k=1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            a[i][j]=r;
            f[(i-1)*n+j]=(i-1)*n+j;//初始化并查集
            s[(i-1)*n+j]=1;//每个点目前所在连通块大小就是1
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            for(int m=0;m<4;m++)
            {
                int x=i+t[m][0];
                int y=j+t[m][1];
                if(x<1||y<1||x>n||y>n)
                    continue;
                node x=node((i-1)*n+j,abs(a[x][y]-a[i][j]),(x-1)*n+y);
                g.push_back(x);
            }
        }
    sort(g.begin(),g.end(),cmp);
    int maxn=0;
    for(int i=0;i<g.size();i++)
    {
        if(f1(g[i].u)!=f1(g[i].v))
        {
            marge(g[i].u,g[i].v);
            if(s[f1(g[i].u)]>(n*n+1)/2-1)//先加1再除以2就能自动向上取整了
            //和最小生成树板子的唯一区别
            //当合并的这两个连通块总大小大于总格子的一半就满足条件了
            //直接 break 掉
            //因为排过序，所以这个连通块高度差最大的两个格子的差值就是
            //这两个格子的高度差，同样因为排过序，所以第一个达到要求的
            //连通块最大高度差肯定最小
            {
                maxn=g[i].w;
                break;
            }
        }
    }
    printf("%d",maxn);
    return 0;
}
```


---

## 作者：endless_loop (赞：2)

这题很明显是一个最小生成树，节点是每个格子，然后从每个格子向四个方向连边。

**1.节点编号**

不知道有没有用一维数组当二维数组用过。我们设 `a[i][j]` 表示第 $i$ 行，第 $j$ 列，每行 $n$ 个元素，那么转化为一维数组就是 `a[(i-1)*n+j]`。这个应该很好想通，有 $i$ 行说明前面已经有了 $(i-1)\times n$ 个元素，再加上这行的 $j$ 个元素就得了。由于下标是从 $0$ 开始的，我们转成一维的时候就不用减  $1$ 了。

节点编号同理，${i,j}$ 转化成 ${i\times n+j}$。

**2.连边**

这个好理解，每个节点向四面都连一个边，边权就是两节点高度差的绝对值。

总体代码如下：

```cpp
cin>>n;
for(int i=0;i<n;++i)
	for(int j=0;j<n;++j)
		cin>>a[i][j];
const int dx[]={0,0,-1,1};
const int dy[]={1,-1,0,0};
for(int i=0;i<n;++i)
	for(int j=0;j<n;++j)
		for(int k=0;k<4;k++){
			int x=i+dx[k],y=j+dy[k];
			if(0<=x&&x<n&&0<=y&&y<n)
				edges.push_back(edge(i*n+j,x*n+y,abs(a[i][j]-a[x][y])));
			}
```

接着，就是 kruskal 了。

**注意！**

如果你直接使用连通块的个数小于一半是错的。

拿样例来说

```
5 
0 0 0 3 3 
0 0 0 0 3 
0 9 9 3 3 
9 9 9 3 3 
9 9 9 9 3 
```

我们所有的 $0,9,3$ 全部连起来了，此时连通块只有三个，程序肯定会输出 $0$，但这种情况明显是错的。

~~在这里WA的死去活来~~

于是我们用 `size[i]` 来表示 $i$ 所在连通块的大小，当我们合并时也将 `size[i]` 合并，然后看合并完后的连通块是否满足大于总数的一半。

AC代码如下：

```cpp
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int n,m;
const int maxn=500+5;
struct edge{
	int u,v,dis;
	bool operator<(const edge& rhs)const{
		return dis<rhs.dis;
	}
	edge(int u=0,int v=0,int d=0):u(u),v(v),dis(d){}
};
vector <edge> edges;
int a[maxn][maxn];
int cnt=0;
const int dx[]={0,0,-1,1};
const int dy[]={1,-1,0,0};
int size[maxn*maxn];
int pa[maxn*maxn];
int root(int x){
	return pa[x]==x?x:pa[x]=root(pa[x]);
}
int main(){
	cin>>n;
	for(int i=0;i<n;++i)
		for(int j=0;j<n;++j)
			cin>>a[i][j];
	for(int i=0;i<=n*n;++i)
		pa[i]=i,size[i]=1;
	for(int i=0;i<n;++i)
		for(int j=0;j<n;++j)
			for(int k=0;k<4;k++){
				int x=i+dx[k],y=j+dy[k];
				if(0<=x&&x<n&&0<=y&&y<n)
					edges.push_back(edge(i*n+j,x*n+y,abs(a[i][j]-a[x][y])));
			}
	sort(edges.begin(),edges.end());
	for(int i=0;i<edges.size();++i){
		int x=root(edges[i].u),y=root(edges[i].v);
		if(x!=y){
			pa[x]=y;
			size[y]+=size[x];//由于是直接找到根节点的，只在这里维护连通块大小就好了
			if(size[y]>=(n*n+1)/2){
				cout<<edges[i].dis;
				return 0;
			}
		}
	}
	return 0;
}
```

---

## 作者：Tyyyyyy (赞：2)

# 二分答案+dfs
**算法分析**

首先，题目理解一下可以知道是求最大高度差的最小值。

“最大值最小”“最小值最大”这一类大家应该都见过，是二分答案的标志，所以可以确定是二分答案。

**怎样判断答案是否成立呢？**

很简单，只需要按照题目要求遍历即可。一谈到遍历，大概自然都会想到$dfs$。

所以算法就确定了。分析一下时间，$O(n^2logd)$，显然不会超时。

**接下来的实现大概就比较简单啦~下面是代码，参照即可。**

```
#include<bits/stdc++.h>
using namespace std;
int n,mp[1010][1010],maxc,ans,mid,l=1e9,r;
bool vis[1010][1010],f;
int dx[]={0,1,0,-1},dy[]={1,0,-1,0};
template <typename T> inline void read(T &x)
{
    x=0;
    int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    x*=f;
}
inline int dfs(int x,int y,int cn)
{
	vis[x][y]=1;
	int now=1;
	for(int i=0;i<4;i++)
	{
		int nx=x+dx[i],ny=y+dy[i];
		if(nx<1||ny<1||nx>n||ny>n)continue;
		if(vis[nx][ny])continue;
		if(abs(mp[nx][ny]-mp[x][y])<=cn)now+=dfs(nx,ny,cn);
	}
	return now;
}
inline bool check(int k)
{
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(vis[i][j])continue;
			if(dfs(i,j,k)>=n*n/2)return 1;
		}
	}
	return 0;
}
int main()
{
	read(n);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			read(mp[i][j]);
			l=min(l,mp[i][j]);
			r=max(r,mp[i][j]);
		}
	}
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(check(mid))r=mid-1,ans=mid;
		else l=mid+1;
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：yoyiETO (赞：2)

- 拖拉机最低费用$0$元，最高$10^6$元。 

- 可以从每一个格子出发判断是否能巡视一半的格子。

- 巡视可以用dfs搜索连通快，用一个变量计数。

dfs代码：
```cpp
int dfs(int x,int y)
{
	int sum=1;//记录能巡视的格子 
	vis[x][y]=1;//标记已经走过 
	for(int i=0;i<4;i++)
	{
		int xx=x+dx[i],yy=y+dy[i];
		if(xx>=1&&xx<=n&&yy>=1&&yy<=n&&!vis[xx][yy]&&abs(a[xx][yy]-a[x][y])<=mid)//在农田内&没访问过&mid元的拖拉机可以通过 
			sum+=dfs(xx,yy);
	}
	return sum;
}
```
逻辑上没有问题，但枚举$0$到$10^6$的时间复杂度为$10^6*n^2$=$2.5*10^11$ 有点小TLE（ 

当然可以做一点优化，比如~~O2优化~~记录所有格子高度的最大值代替$10^6$可能会多得一些分数。

求最优值三板斧：贪心动规二分答案，考虑二分答案：

拖拉机的钱越多，巡视的格子就更多，符合单调性√

二分答案代码：
```cpp
while(l<r)
{
	mid=(l+r)/2;//求中间值 
	if(check()) r=mid;//如果mid可以，mid+1,mid+2..都行，r=mid 
	else l=mid+1;//如果mid不行，mid-1,mid-2...都不行，l=mid+1 
}
//最后答案为l 
```

AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[501][501],tot,l,r=1e6,mid; 
int dx[4]={-1,1,0,0},dy[4]={0,0,-1,1};
bool vis[501][501];
int dfs(int x,int y)
{
	int sum=1;
	vis[x][y]=1;
	for(int i=0;i<4;i++)
	{
		int xx=x+dx[i],yy=y+dy[i];
		if(xx>=1&&xx<=n&&yy>=1&&yy<=n&&!vis[xx][yy]&&abs(a[xx][yy]-a[x][y])<=mid)
			sum+=dfs(xx,yy);
	}
	return sum;
}
bool check()
{
	memset(vis,0,sizeof(vis));//初始化 
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
		if(!vis[i][j]&&dfs(i,j)>=tot)
			return 1;
	return 0;
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
		cin>>a[i][j];
	tot=n*n/2+n*n%2;//注意要加上n*n%2 
	while(l<r)//二分答案 
	{
		mid=(l+r)/2;
		if(check()) r=mid;
		else l=mid+1;
	}
	cout<<l;
	return 0;
}
```

---

## 作者：Goes (赞：2)

这算是贪心思路吧
排序+并查集

按点与点之间的高度差排序（该思路源于最短路....2333）
并查集的过程中维护面积和花费就好

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
inline int read(){
	char ch='*';int sum=0,f=1;
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')
		sum*=10,sum+=ch-'0',ch=getchar();
	return sum*f;
}
#if 0
Writers: G.S.M. && Goes
Enjoyable
#endif
int fa[505*505],n;
int f(int x){
	if(fa[x]==x)return x;
	else return fa[x]=f(fa[x]);
}
#define num(x,y) (x-1)*n+y
struct ss{
	int dis,pos,to;
}tlj[505*505*4];int tot;
bool cmp(ss a,ss b){return a.dis<b.dis;}
int va[505*505],mj[505*505];
int con(int p){
	int x=tlj[p].pos,y=tlj[p].to;	int fx=f(x),fy=f(y);
	if(fx==fy) return false;
	fa[fx]=fy;va[fy]=tlj[p].dis;mj[fy]+=mj[fx];
	if(mj[fy]>=n*n/2) return va[fy];
	else return false;
}
#include<cmath>
#include<algorithm>
int H[505][505];
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			H[i][j]=read();
			if(i>1)tlj[++tot]=(ss)
			{abs(H[i][j]-H[i-1][j]),num(i,j),num(i-1,j)};
			if(j>1)tlj[++tot]=(ss)
			{abs(H[i][j]-H[i][j-1]),num(i,j),num(i,j-1)};
		}
	for(int i=1;i<=n*n;i++) fa[i]=i,mj[i]=1;
	sort(tlj+1,tlj+tot+1,cmp);int ans;
	for(int i=1;i<=tot;i++)if(ans=con(i)) break;
	cout<<ans<<endl;	return 0;
}

```

---

## 作者：曹老师 (赞：2)

## Sol ##

[blog食用](http://www.caolaoshi.men/index.php/archives/usaco13feb-trac.html)

~~好水的一道题啊……~~直接二分答案就可以过，不需要并查集的，二分加广搜，时间复杂度是$O(n^2 logM)$，能过的。

读完题，我们很容易的就能知道，答案满足单调性，也就是说，如果mid能够到达一半以上，那么>mid的所有的数都可以达到一半以上，于是就会有一个临界值是达到和达不到之间的，这个值就是我们最终的答案。经分析得，本题满足二分条件，可以二分。二分出来，我们正着做广搜，搜索的路上就能求出最大的联通块，如果最大的联通块比一半要多，右端点移动，反之左端点移动。

## Code ##

```
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;

void read(int &x)
{
    char c = getchar(); x = 0;
    while(c < '0' || c > '9') c = getchar();
    while(c <= '9' && c >= '0') x = x*10+c-48, c = getchar();
}

void put(int x)  
{  
    int num = 0; char c[15];
    while(x) c[++num] = (x%10)+48, x /= 10;
    while(num) putchar(c[num--]);
    putchar('\n'); 
}

struct Node {
    int x , y;
    Node(){}
    Node (int xx , int yy) {
        x = xx , y = yy;
    }
};
int n , map[505][505] , minn = 1e8 , maxx = -1 , vis[505][505] , K;

inline int mymax(int a , int b) { return a>b?a:b; }
inline int mymin(int a , int b) { return a<b?a:b; }
inline int myabs(int a) { return a>0?a:(-a); }
inline int mypow(int a , int b) { if(b == 1) return a; int t = mypow(a , b/2); if(b % 2 == 0) return t*t; return t*t*a; }

int bfs(int x , int y , int k) {
    int res = 1;
    vis[x][y] = 1;
    queue<Node>q; 
    q.push(Node(x , y));
    while(!q.empty()) {
        Node u = q.front();
        q.pop();
        if(u.x-1>=1 && !vis[u.x-1][u.y] && myabs(map[u.x-1][u.y]-map[u.x][u.y])<=k) {
            vis[u.x-1][u.y] = 1;
            res++;
            q.push(Node(u.x-1,u.y));
        }
        if(u.x+1<=n && !vis[u.x+1][u.y] && myabs(map[u.x+1][u.y]-map[u.x][u.y])<=k) {
            vis[u.x+1][u.y] = 1;
            res++;
            q.push(Node(u.x+1,u.y));
        }
        if(u.y-1>=1 && !vis[u.x][u.y-1] && myabs(map[u.x][u.y-1]-map[u.x][u.y])<=k) {
            vis[u.x][u.y-1] = 1;
            res++;
            q.push(Node(u.x,u.y-1));
        }
        if(u.y+1<=n && !vis[u.x][u.y+1] && myabs(map[u.x][u.y+1]-map[u.x][u.y])<=k) {
            vis[u.x][u.y+1] = 1;
            res++;
            q.push(Node(u.x,u.y+1));
        }
    }
    return res;
}

int jud(int x) {
    int ans = 0;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            if(!vis[i][j])
                ans = mymax(ans , bfs(i,j,x));
    if(ans >= K)
        return 1;
    return 0;
} 

int main() {
    read(n);
    K = mypow(n , 2) / 2;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++) {
            read(map[i][j]);
            minn = mymin(minn , map[i][j]);
            maxx = mymax(maxx , map[i][j]);		
        }
    int l = 0 , r = maxx - minn; 
    while(l <= r) {
        memset(vis , 0 , sizeof(vis)); 
        int mid = (l+r)>>1;
        if(jud(mid))
            r = mid - 1;
        else
            l = mid + 1;
    } 
    put(l);
    return 0;
}
```


  [1]: https://www.luogu.org/problemnew/show/P3073

---

## 作者：Thomasguo666 (赞：0)

更~~糟~~好的阅读体验，请戳[这里](https://thomasguo666.github.io/2020/02/14/solution-P3073/)


---


首先我们简化一下题意。题目的意思是说，让我们找一个包含 $\lceil \frac{n^2}{2} \rceil $ 个点的连通块的相邻格之间高度差的最大值的最小值。

诸如这种最小化 max 值的题目，常见思路是使用**二分答案**将其由**最优化问题**转为**可行性问题**。

具体到这道题，我们二分高度差的最大值，设最大值为 mid。然后我们可以把把 $n^2$ 个格子对应成 $n^2$ 个点，把整张网格当作一张无向图。两个节点之间有边，当且仅当这**两个节点所对应的格子相邻，且高度之差不超过 mid**。

那么接下来我们可以发现，问题转化为：**求出一张 $n^2$ 阶图中是否存在至少有 $\lceil \frac{n^2}{2} \rceil $ 个点的联通块**。这里我们使用**并查集**即可快速地解决该问题。具体地说，对于图中的每一条边，若其两端点不在同一连通块，则我们将其右端点的连通块和左端点的连通块合并。若新连通块包含了过半数的点，则判定为存在。若对所有边进行了上述操作后，仍未判定为存在，则判定为不存在。



更多实现的细节问题，见代码：

```cpp
#include <bits/stdc++.h>
#define debug printf("Running %s on line %d...\n",__FUNCTION__,__LINE__)
#define in inline
#define re register
using namespace std;
typedef long long ll;
typedef double db;
in int read()
{
    int ans=0,f=1;char c=getchar();
    for (;!isdigit(c);c=getchar()) if (c=='-') f=-1;
    for (;isdigit(c);c=getchar()) ans=(ans<<3)+(ans<<1)+(c^48);
    return ans*f;
}
in int cmin(int &a,int b) {return a=min(a,b);}
in int cmax(int &a,int b) {return a=max(a,b);}
int n;
int a[505][505];
int dx[]={1,0};
int dy[]={0,1};
int st[500005],en[500005];
int fa[250005],sz[250005],tot;
in int zip(int x,int y) // 将点 (x,y) 压缩成一个 [1,n*n] 之间的整数
{
    return (x-1)*n+y;
}
int find(int x) // 并查集寻根函数
{
    return x==fa[x]?x:fa[x]=find(fa[x]); // 路径压缩
}
int check(int mid) // 二分答案的判断函数
{
    tot=0;
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=n;j++)
        {
            fa[zip(i,j)]=zip(i,j);
            sz[zip(i,j)]=1;
            for (int k=0;k<2;k++)
            {
                int ii=i+dx[k],jj=j+dy[k];
                if (ii<=n && jj<=n && abs(a[i][j]-a[ii][jj])<=mid) // 只有符合要求的才连边
                {
                    st[++tot]=zip(i,j);
                    en[tot]=zip(ii,jj);
                }
            }
        }
    }
    for (int i=1;i<=tot;i++)
    {
        int u=st[i],v=en[i];
        int uu=find(u),vv=find(v);
        if (uu==vv) continue;
        fa[vv]=uu;
        sz[uu]+=sz[vv]; // 合并集合
        sz[vv]=0;
    }
    for (int i=1;i<=n*n;i++)
    {
        if (sz[i]*2>=n*n) return 1;
    }
    return 0;
}
int main()
{
    n=read();
    for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) a[i][j]=read();
    int l=0,r=1000000,ans=1000000;
    while (l<=r) // 二分答案
    {
        int mid=l+r>>1;
        if (check(mid)) r=mid-1,ans=mid;
        else l=mid+1;
    }
    cout<<ans<<endl;
    return 0;
}

```



---

## 作者：关怀他人 (赞：0)

## 二分+并查集
不难发现答案具有单调性，因为如果小的价值满足条件，那么大的价值也一定满足条件，大价值的联通块大小一定大于等于小价值的联通块大小。

因为答案具有单调性，所以可以二分，关键就是如何check，可以考虑用并查集维护联通块，如果相邻两个格子的高度差$abs(a_{i,j}-a_{i'j'})\leq x$,其中$x$为当前二分的答案，那么$(i,j)$和$(i',j')$一定可以相互到达，于是可以用并查集维护连通性，顺便统计一下大小，最后只需判断最大的联通块大小是否大于$\lceil \frac{n*n}{2}\rceil$即可

复杂度为$O(n^2logn^2*\alpha)$

### AC代码
```cpp
/*
Problem : luogu P3073
Algorithm : binary search + Dsu
Status : AC
*/
#include <bits/stdc++.h>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

const int INF = 0x3f3f3f3f;
const int MAXN = 505;
const int MAXM = MAXN * MAXN;
const int dx[] = {1,0,-1,0};
const int dy[] = {0,1,0,-1};

int n,limit;
int a[MAXN][MAXN];

int getId(int x,int y){
	return (x - 1) * n + y;
}

namespace Dsu{ //并查集
	int f[MAXM],size[MAXM];
	
	void Init(){
		for(int i = 1;i <= n * n;i++){
		    f[i] = i;
		    size[i] = 1;
		}
	}
	
	int Find(int x){
		if(x == f[x])
		    return x;
		else
		    return f[x] = Find(f[x]);
	}
	
	void Unionn(int x,int y){
		int fx = Find(x);
		int fy = Find(y);
		if(fx != fy){
			if(size[fx] >= size[fy]){ //按秩合并
			    f[fy] = fx;
			    size[fx] += size[fy];
			}else{
			    f[fx] = fy;
			    size[fy] += size[fx];
			}
		}
	}
	
	int GetMax(){
		int Max = 0;
		for(int i = 1;i <= n * n;i++) //找最大的联通块
			Max = max(Max,size[i]);
		return Max;
	}
}

bool check(int x){
	Dsu::Init();
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++){
			for(int k = 0;k < 4;k++){
				int nx = i + dx[k];
				int ny = j + dy[k];
				if(nx >= 1 && nx <= n && ny >= 1 && ny <= n && abs(a[i][j] - a[nx][ny]) <= x)
					Dsu::Unionn(getId(i,j),getId(nx,ny)); //维护连通性
			}
		}
	}
	return Dsu::GetMax() >= limit;
}

int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
	scanf("%d",&n);
	limit = (n * n + 1) / 2;
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++)
		    scanf("%d",&a[i][j]);
	}
	int l = 0,r = INF,ans = 0;
	while(l <= r){
		int mid = (l + r) >> 1;
		if(check(mid)){
			ans = mid;
			r = mid - 1;
		}else
		    l = mid + 1;
	}
	printf("%d\n",ans);
	return 0;
}

```


---

## 作者：孑彧 (赞：0)

# P3073 Tractor

### 题目描述

FJ有块农田太崎岖了，他要买一辆新拖拉机才能在这里巡视。这块农田由N x N个格子的非负整数表示高度(1<=N<=500)。拖拉机从当前格子走到相邻格子（东、南、西、北四个方向）的代价为高度差D，则FJ驶过这两个格子的拖拉机最少也要值D块钱。

FJ愿意花足够的钱买一辆新的拖拉机使得他能以最小的高度差走遍所有格子的一半(如果格子总数是奇数，那么一半的值为四舍五入的值)。因为FJ很懒，所以他找到你帮他编程计算他最小需要花多少钱买到符合这些要求的拖拉机。

### 思路

我们可以二分这个答案，因为它符合单调性，然后接下来我们就需要去求出在这个答案下能否驶过一半的格子，我们可以用一个并查集维护，假如当前这个格子能够到达下一个格子，那么就可以合并起来，同时维护根节点的大小

### 贴代码

```c++
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define maxn 600
using namespace std;
int dx[2]={1,0};
int dy[2]={0,1};
int m[maxn][maxn];
int n,ans;
int l,r,mid;
int d[maxn*maxn];
int f[maxn*maxn];
struct Edge{
	int x,y,v;
	bool operator < (const Edge &a)const{
		return v<a.v;
	}
}e[maxn*maxn*4];
int ecnt;
int abs(int x){
	return x<0?-x:x;
}
void adde(int x,int y,int v){
	e[++ecnt].x=x;
	e[ecnt].y=y;
	e[ecnt].v=v;
}
bool check(int x,int y){
	if(x<1||x>n||y<1||y>n){
		return false;
	}
	else{
		return true;
	}
}
int num(int x,int y){
	return n*(x-1)+y;
}
int find(int x){
	return f[x]==x?x:f[x]=find(f[x]);
}
void merge(int a,int b){
	int fa=find(a);
	int fb=find(b);
	if(fa==fb){
		return;
	}
	if(d[fa]>d[fb]){
		swap(fa,fb);
	}
	f[fa]=fb;
	d[fb]+=d[fa];
	return;
}
bool solve(int limit){
	for(int i=1;i<=n*n;i++){
		f[i]=i;
		d[i]=1;
	}
	for(int i=1;i<=ecnt;i++){
		if(e[i].v>limit){
			break;
		}
		merge(e[i].x,e[i].y);
	}
	for(int i=1;i<=n*n;i++){
		if(d[find(i)]>=n*n/2){
			return true;
		}
	}
	return false;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>m[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			for(int k=0;k<2;k++){
				int nx=i+dx[k];
				int ny=j+dy[k];
				if(check(nx,ny)){
					int de=abs(m[i][j]-m[nx][ny]);
					r=max(r,de);
					adde(num(i,j),num(nx,ny),de);
				}
			}
		}
	}
	sort(e+1,e+1+ecnt);
	while(l<=r){
		mid=(l+r)/2;
		if(solve(mid)){
			ans=mid;
			r=mid-1;
		}
		else{
			l=mid+1;
		}
	}
	printf("%d",ans);
}
```



---

## 作者：Wall_breaker (赞：0)

# 二分大法好
~~ps：也不知道哪些大佬贴了线段树之类的标签（tql），也可能是我蒟蒻看不出~~


------------
本题是一个求最值问题，很容易就想到二分相差值，只是判断函数有点难写。怎么写呢？
##### 核心代码
```c++
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
int a[502][502], r = 1e6, l, mid, n, sum;
bool vis[501][501];
inline void dfs(int x, int y) {
    int xi, yi;
    vis[x][y] = true;
    sum ++; 
    for (int i = 0; i < 4; i ++) {//向四方扩展
        xi = x + dx[i], yi = y + dy[i];
        if (a[xi][yi] && !vis[xi][yi] && abs(a[x][y] - a[xi][yi]) <= mid) {
            dfs(xi, yi);//在这里为使判断变少，我把节点值都加了1，使其从非负整数变为正整数，0就是边界
        }
    }
}
inline bool check() {
    memset(vis, false, sizeof(vis));//判断有没有到过
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            if (!vis[i][j]) {//未访问过
                sum = 0;//所能到格子个数
                dfs(i, j);
                if ((sum << 1) >= n * n) return true;//超过一半
            }
        }
    }
    return false;
}
```
### dfs是什么？dfs就是指如果我从这个点开始遍历。
### 如果这一块不满，那么要从我没遍历过的点再次开始搜。
下面来讲讲二分。
如果x能满足题目要求，即能遍历的一半点中任意两点差值都小于等于x，那么比x大的y肯定满足要求。因此本题具有二分的性质。
## 全代码
```c++
#include<bits/stdc++.h>
using namespace std;
template <typename T> inline void read(T &x) {
    x = 0;
    register int f = 1;
    register char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -1;
    for (; isdigit(c); c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
    x *= f;
}
template <typename T> inline void w(T x) {
    if (x > 9) w(x / 10);
    putchar(x % 10 + 48);
}
template <typename T> inline void write(T x, char c) {
//	if (x < 0) putchar('-'), x = -x;
    w(x);
    putchar(c);
}
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
int a[502][502], r = 1e6, l, mid, n, sum;
bool vis[501][501], flg;
inline void dfs(int x, int y) {
    int xi, yi;
    vis[x][y] = true;
    sum ++; 
    for (int i = 0; i < 4; i ++) {
        xi = x + dx[i], yi = y + dy[i];
        if (a[xi][yi] && !vis[xi][yi] && abs(a[x][y] - a[xi][yi]) <= mid) {
            dfs(xi, yi);
        }
    }
}
inline bool check() {
    flg = false;
    memset(vis, false, sizeof(vis));
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            if (!vis[i][j]) {
                sum = 0;
                dfs(i, j);
                if ((sum << 1) >= n * n) return true;
            }
        }
    }
    return false;
}
int main() {
    read(n);
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            read(a[i][j]);
            a[i][j] ++;
        }
    }
    while(l < r) {
        mid = (l + r) >> 1;
        if (check()) {
            r = mid;
        }
        else l = mid + 1;
    }
    write(r, '\n');
    return 0;
}
```



---

