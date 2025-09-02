# [USACO16FEB] Fenced In G

## 题目背景

*本题和 [白金组同名题目](/problem/P3141) 在题意上一致，唯一的不同是数据范围。*

## 题目描述

Farmer John 意识到他的奶牛最近患上了一种恐惧症（害怕过于开阔的空间）。为了减少放牧的恐惧，FJ 决定在牧场中建一些水平和竖直方向的栅栏来将牧场分成若干个小区域。

整个牧场是一个矩形，两个角的坐标分别为 $(0,0)$ 和 $(A,B)$。FJ 在 $a_1,\ldots ,a_n$ 这 $n$ 个两两不同的位置建造了竖直方向的栅栏，每个栅栏从 $(a_i,0)$ 到 $(a_i,B)$；FJ 在 $b_1,\ldots ,b_m$ 这 $m$ 个两两不同的位置建造了水平方向的栅栏，每个栅栏从 $(0,b_i)$ 到 $(A,b_i)$。竖直方向的栅栏和水平方向的栅栏两两相交，将整个牧场分割成 $(n+1)(m+1)$ 个区域。

不幸的是，FJ 忘记了在栅栏上开门，奶牛都只能被困在一个个的小区域里！他想通过去掉一些栅栏来解决这个问题。他一次可以选择两个相邻的区域，将隔离这两个区域的栅栏去掉。FJ 的目标是让奶牛能够抵达牧场的任意一个地方。

这是一个例子：

```plain
+---+--+
|   |  |
+---+--+
|   |  |
|   |  |
+---+--+
```

去掉一些栅栏后的效果是这样的：

```plain
+---+--+
|      |
+---+  +
|      |
|      |
+---+--+
```

为了降低工程量，FJ 当然希望拆除的栅栏长度最短。

## 样例 #1

### 输入

```
15 15 5 2
2
5
10
6
4
11
3```

### 输出

```
44```

# 题解

## 作者：Mu_tr (赞：5)

# 题目大意
给一个大矩形，中间有一些横线和竖线，这些线又将整个大矩形分成    $(n+1)\cdot(m+1)$ 个小矩形，问最少删掉多长的线段可以让这些小矩形连通。

# 题目思路
很明显我们可以将这道题抽象成一道最小生成树问题，将一个小矩形看成一个点，然后将这个小矩形和四个方向上的其他矩形连边，由于小矩形的个数最多为   $2001\times 2001=4004001$，那么总边数即为 $4004001\times 4=16016004$，由于这道题中的边是无向边，所以我们一条边会被连两次，删掉重复的那么总边数即为 $16016004\div 2=8008002$ 。这里我们采用的是 kruskal   算法，时间复杂度还需要带上一个并查集的，代码中我使用了启发式合并和路径压缩两种优化方式优化时间复杂度，所以总时间复杂度为 $O(nm\alpha(nm))$ ，$\alpha(nm)$ 可以看做一个小于 5 的常数，所以总运行次数即为 $10^8$ 左右。在本机上不吸氧最后一个测试点用时 1.7s 左右，但洛谷会超时，不过吸口氧还是能够轻松过的，最后一个测试点只用了 0.7s。

# AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int cnt=0,n,m,a,b,x[2005],y[2005],f[4010005],rt[4010005],q1,q2,p;
long long ans1=0;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
struct ok{
	int ans,w1,w2;
}q[8020005];
inline bool cmp(ok x,ok y){
	return x.ans<y.ans;
}
inline int find(int k){
	return k==f[k]?k:f[k]=find(f[k]);
}
inline int js(int x,int y){
	return x*(m+1)+y+1;
}
signed main(){ 
	a=read(),b=read(),n=read(),m=read();
	for(register int i=1;i<=n;i++) x[i]=read();
	for(register int i=1;i<=m;i++) y[i]=read();
	sort(x+1,x+1+n);sort(y+1,y+1+m);
	x[n+1]=a;y[m+1]=b;
	for(register int i=0;i<=n;i++){
		for(register int j=0;j<=m;j++){
			p=js(i,j);
			f[p]=p;rt[p]=1;
			if(j!=m) q[++cnt].ans=x[i+1]-x[i],q[cnt].w1=p,q[cnt].w2=p+1;
			if(i!=n) q[++cnt].ans=y[j+1]-y[j],q[cnt].w1=p,q[cnt].w2=p+m+1;
		}
	}
	sort(q+1,q+1+cnt,cmp);
	for(register int i=1;i<=cnt;i++){
		q1=find(q[i].w1),q2=find(q[i].w2);
		if(q1!=q2){
			rt[q1]>rt[q2]?(f[q2]=f[q1],rt[q1]+=rt[q2]):(f[q1]=f[q2],rt[q2]+=rt[q1]);
			ans1+=q[i].ans;
		}	
	}
	printf("%lld",ans1); 
	return 0;
}
```


---

## 作者：羚羊WANG (赞：3)

相信大家看到这里的时候，对题目意思已经有了深入的了解

题目意思是说将图形分割成$n*(n+1)$个区域

那么就是删除$n*(n+1)-1$条边

而且我们会发现，这些删除的边都没有特殊的条件

所以，我们每次删边的时候可以考虑贪心

如果这条边平行于$x$轴就删去$m−j+1$条该边，如果这条边平
行于$y$轴就删去$n−i+1$条该边

这样子操作下来，我们就会发现，我们每一步删边都是删的最
值，所以这样子删边删完之后，求到最后一个，我们找到的一
定是最值

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int x=0;
	bool f=0;
	char c=getchar();
	while (!isdigit(c))
		  f|=(c=='-'),c=getchar();
	while (isdigit(c))
		  x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?-x:x;
}
void write(int x) {
    if(x<0) {
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int n,m;
int a[50010];
int b[50010];
int x[50010];
int y[50010];
int A,B;
int ans;
int l,r;
signed main(){
	A=read();
	B=read();
	n=read();
	m=read();
	for(register int i=1;i<=n;++i)
		a[i]=read();
	for(register int i=1;i<=m;++i)
		b[i]=read();
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
	for(register int i=1;i<=n;++i)
		x[i]=a[i]-a[i-1];
	x[n+1]=A-a[n];
	n++;
	for(register int i=1;i<=m;++i)
		y[i]=b[i]-b[i-1];
	y[m+1]=B-b[m];
	m++;
	sort(x+1,x+n+1);
	sort(y+1,y+m+1);
	l=2;
	r=2;
	ans=x[1]*(m-1)+y[1]*(n-1);
	while(l<=n && r<=m)
		{
			if(x[l]<y[r])
				{
					ans=ans+x[l]*(m-r+1);
					l++;
				}
			else
				{
					ans=ans+y[r]*(n-l+1);
					r++;
				}
		}
	write(ans);
	return 0;
}

```


---

## 作者：yingxi (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/P6171)

### 题目分析

在一个大矩形里，用横竖的线划分成多个小矩形。题目要求这些分出小矩形的最小的栅栏总长度，其实就是一个最小生成树问题。

### 思路

**F1**：直接构建图来求最小生成树，但是时间复杂度较高，会超时。

**F2**：直接进行分类处理，因为边只有水平和垂直两类。所以步骤如下：

- 首先先对水平和垂直的栅栏位置进行排序。
- 接着枚举每一条水平和垂直的栅栏，根据当前栅栏的位置和已有的栅栏的情况，计算加入如果这条栅栏能产生的新边数量，然后选择合适的边加入最小生成树。

好啦，可以来实现了。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=1e7+5;
int fa[N],A,B,n,m,cnt,sum;
int a[N],b[N];
struct node{
	int x,y,v;
}e[N];
int top;
bool coo(node x,node y)
{
	return x.v<y.v;
} 
int find(int x)
{
	if(fa[x]==x)
		return x;
	return fa[x]=find(fa[x]);
}
void unite(int x,int y)
{
	x=find(x);
	y=find(y);
	if(x!=y)
		fa[x]=y;
	return ;
}
signed main()
{
	cin>>A>>B>>n>>m;
	for(int i=0;i<=n;i++)
		for(int j=0;j<=m;j++)
			fa[i*(m+1)+j]=i*(m+1)+j;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+n+1);
	a[++n]=A;
	for(int i=1;i<=m;i++)
		cin>>b[i];
	sort(b+1,b+m+1);
	b[++m]=B;
	for(int i=1;i<=n;i++)
		for(int j=1;j<m;j++)
		{
			top++;
			e[top].x=(i-1)*m+j-1;
			e[top].y=(i-1)*m+j;
			e[top].v=a[i]-a[i-1];
		}
	for(int i=1;i<n;i++)
		for(int j=1;j<=m;j++)
		{
			top++;
			e[top].x=(i-1)*m+j-1;
			e[top].y=i*m+j-1;
			e[top].v=b[j]-b[j-1];
		}
	sort(e+1,e+top+1,coo);
	for(int i=1;i<=top;i++)
	{
		if(find(e[i].x)!=find(e[i].y))
		{
			unite(e[i].x,e[i].y);
			cnt++;
			sum+=e[i].v;
		}
	}
	cout<<sum;
	return 0;
}
```

### 时间复杂度

1. 排序：$O(n \log n+m \log m)$
2. 选边：$O(n+m)$

所以总复杂度为 $O(n \log n+m \log m)$。

#### 后

学到这一步说明你已经很擅长信息学了呀。

再掉咕值就要降橙啦！求管理大大给过！

---

## 作者：OreoTheGreat (赞：1)

最小生成树算法


------------
把每一个格子看作一个点，两个相邻的点之间栅栏的长度看作边的权重

然后建图跑Kruskal 


------------
上代码（JAVA）：
```java
import java.util.*;
import java.io.*;

public class fencedin {
	
	static int[] parent;

	public static void main(String[] args) throws IOException {
		
		BufferedReader br = new BufferedReader(new FileReader("fencedin.in"));
		PrintWriter pw = new PrintWriter(new File("fencedin.out"));
		
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		int A = Integer.parseInt(st.nextToken());   // [0, A] horizontal range
		int B = Integer.parseInt(st.nextToken());   // [0, B] vertical range
		int n = Integer.parseInt(st.nextToken());   // x=X[1], ..., X[n]
		int m = Integer.parseInt(st.nextToken());   // y=Y[1], ..., Y[m]

		int[] X = new int[n+2];  // vertical lines
		int[] Y = new int[m+2];  // horizontal lines
		
		for(int j=1; j<=n; j++)
			X[j] = Integer.parseInt(br.readLine());
		X[n+1] = A;
		
		for(int k=1; k<=m; k++)
			Y[k] = Integer.parseInt(br.readLine());
		Y[m+1] = B;
		
		Arrays.sort(X);
		Arrays.sort(Y);
		
		int[] deltaX = new int[n+1];  // vertical gaps
		int[] deltaY = new int[m+1];  // horizontal gaps
		
		for(int j=0; j<=n; j++)
			deltaX[j] = X[j+1] - X[j];
		
		for(int k=0; k<=m; k++)
			deltaY[k] = Y[k+1] - Y[k];

		Arrays.sort(deltaX);
		Arrays.sort(deltaY);
		
		int N1 = n+1;
		int M1 = m+1;

		// apply union-find on disjoint sets
		// Each set is represented by indices (j, k)
		// Fix j, and when k increases, the rectangles go up.
		parent = new int[N1*M1];
		for(int u=0; u<N1*M1; u++)
			parent[u] = u;
		
		long result = 0;   // sum of lengths of edges removed (connect nodes)

		// double indexing to visit each of deltaX and deltaY
		for (int j = 0, k = 0; j < N1 || k < M1; ) {
			if (k == M1 || (j < N1 && deltaX[j] < deltaY[k])) {
				for (int p = 0; p + 1 < M1; p++) {
					if (union(j*M1 + p, j*M1 + p + 1)) {  // one rectangle and above
						result += deltaX[j];
					}
				}
				j++;
			} 
			else {
				for (int q = 0; q + 1 < N1; q++) {
					if (union(q*M1 + k, (q+1)*M1 + k)) {  // one rectangle and to the right
						result += deltaY[k];
					}
				}
				k++;
			}
		}
		
		pw.println(result);
		br.close();
		pw.close();
	}


	// find the parent (or representative) of item k
	public static int find(int k) {
	    if( parent[k]==k ) { // k is the root (or representative)
	       return k;
	    }
	    else {
	       int krep = find( parent[k] );
	       parent[k] = krep;
	       return krep;
	    }
	}

	// merge two sets containing "x" and "y"
	public static boolean union(int x, int y) {
	    int xrep = find(x);
	    int yrep = find(y);
	    if( xrep==yrep )
	    	return false;
	    
	    parent[x]    = yrep;
	    parent[y]    = yrep;
	    parent[xrep] = yrep;
	    parent[yrep] = yrep;
	    return true;
	}	
}
```


---

## 作者：Double_Light (赞：0)

让我们把原问题转化为图论问题。

把每个原来被栅栏隔开的小区域视作一个点，打通相邻两个区域花费的代价为隔开它们的栅栏长度，也就是两点之间连边的边权。

如果需要让所有区域连通，只需要将图中的一棵生成树删掉。由于需要让拆除栅栏长度最小，所以我们求出一棵最小生成树，答案就是这棵树的边权和。

具体代码如下：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int A,B,n,m;
int a[2005],b[2005];
struct EDGE{
	int u,v,w,nxt;
}edge[9000005];
int head[5000005],tot;
void add(int u,int v,int w){
	edge[++tot]={u,v,w,head[u]};
	head[u]=tot;
}
int f(int x,int y){//计算区域对应点的编号
	return (x-1)*(m+1)+y;
}
bool cmp(EDGE x,EDGE y){
	return x.w<y.w;
}
int fa[5000005];
int Find(int x){
	if(fa[x]==x)return x;
	return fa[x]=Find(fa[x]);
}
long long ans;
signed main(){
	cin>>A>>B>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];a[n+1]=A;
	for(int i=1;i<=m;i++)cin>>b[i];b[m+1]=B;
	sort(a+1,a+n+1);//数组并非有序
	sort(b+1,b+m+1);
	for(int i=n+1;i;i--)a[i]-=a[i-1];//作差求出每段栅栏的长度
	for(int i=m+1;i;i--)b[i]-=b[i-1];
	for(int i=1;i<=n+1;i++){
		for(int j=1;j<=m+1;j++){
			if(i>1)add(f(i,j),f(i-1,j),b[j]);//连边
			if(j>1)add(f(i,j),f(i,j-1),a[i]);
		}
	}
	for(int i=1;i<=(n+1)*(m+1);i++)fa[i]=i;
	sort(edge+1,edge+tot+1,cmp);
	int cnt=(n+1)*(m+1);
	for(int i=1;i<=tot;i++){
		int u=edge[i].u,v=edge[i].v,w=edge[i].w;
		if(Find(u)!=Find(v)){
			cnt--;ans+=w;
			fa[Find(u)]=Find(v);
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：tiko_tao (赞：0)

## 题解：P6171 Fenced In G
[题目链接](https://www.luogu.com.cn/problem/P6171)  
本题属于弱化版。

我认为，本道题一大难点是题意的理解（~~我推了好久才看懂样例，也可能是我太蒟了~~）。

题意简述：告诉你一个矩形的两个顶点，给出 $n$ 个**竖直方向**的栅栏和 $m$ 个**水平方向**的栅栏的**一个坐标参数**我（之前一直以为是**长度**，导致卡了好久），这些栅栏将整个牧场分为一些区域。  
我们要做的就是选取任意个栅栏将其拆掉，使得操作后的所有区域是联通的。  
最好是根据坐标来理解这个栅栏。

还是画个图助于理解。  
![](https://cdn.luogu.com.cn/upload/image_hosting/1yhdxexv.png)
没错，这才是样例。  
显然每条栅栏的长度是需要计算得到的，而给出的只是一个坐标的 $x$ 或 $y$。

经过分析容易发现，我们删栅栏的过程类似图论中**加边**的过程，我们把每个区域看做一个**点**，栅栏长度当做**边权**，目的是使图连通。  
想到什么没？  
这就是最小生成树。

当然，考虑这题数据范围小，$n,m\le2000$。  
最小生成树的复杂度：排序 $O(n \log n)$，枚举加和 $O(n)$，这题的点数为 $n\times m$，边数是 $n^2$ 级别的。

最终时间复杂度 $O(n^2 \log n^2)$ （计算器算了一下大概是 $88000000$ 左右，本题时限 $2s$ ），再加上并查集的路径压缩，开个氧气黑科技的话，刚好可以通过本题。

另外这种做法仅限数据弱，有兴趣可以看一下[加强版](https://www.luogu.com.cn/problem/P3141)，是 $O(n\log n)$ 的做法。

---

## 作者：Big_Dinosaur (赞：0)

请先看看[网格图](https://www.luogu.com.cn/problem/P5687)。

下文 $a_{n+1}=A,b_{m+1}=B,a_0=b_0=0$。
## 思路转化
将矩阵中各个点联通，可以考虑转化为最小生成树。边权为拆除栅栏长度。

如果你画一下图，你可以发现此时该图为网格图，网格图第 $i$ 行第 $j$ 列的点与第 $i+1$ 行第 $j$ 列之间的边权为 $b_{j+1}-b_j$，第 $i$ 行第 $j$ 列的点与第 $i$ 行第 $j+1$ 列之间的边权为 $a_{i+1}-a_i$。

接下来，你可以发现：同一行边的边权相等，同一列的边权相等。

这可以转化为 P5687 网格图。

**注意：$a,b$ 不按升序给出，要先排序！**
## Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define ri register int
#define pii pair<int,int>
#define mp make_pair
#define fi first
#define se second
const int TXYAKIOI=1145141919810;
const int JYAAKIOI=0x3f3f3f3f3f3f3f3f;
using namespace std;
namespace IO{
	char ibuf[(1<<20)+1],*iS,*iT;
	#if ONLINE_JUDGE
		#define gh() (iS==iT?iT=(iS=ibuf)+fread(ibuf,1,(1<<20)+1,stdin),(iS==iT?EOF:*iS++):*iS++)
 	#else
		#define gh() getchar()
	#endif
	inline int r(){
		int o=1,p=0;
		char q=gh();
		while(q<'0'||q>'9'){if(q=='-')o=-1;q=gh();}
		while(q>='0'&&q<='9'){p=(p<<1)+(p<<3)+(q^48);q=gh();}
		return o*p;
	}
	inline char gc(){char q=gh();while(q<=' ')q=gh();return q;}
	inline string gs(){string s="";char g=gh();while(g<=' ')g=gh();while(g>' '){s+=g;g=gh();}return s;}
	inline void Wi(int E){
		if(E==0)return;if(E<0){E=-E;putchar('-');}
		Wi(E/10);putchar((E%10)^48);
	}
	inline void wln(int J){if(J==0)putchar('0');else Wi(J);putchar('\n');}
	inline void w(int J){if(J==0)putchar('0');else Wi(J);}
	inline void ww(int J){if(J==0)putchar('0');else Wi(J);putchar(' ');}
}
using namespace IO;
namespace D1n0{
	int n,m,A[256666],B[256666],a[256666],b[256666],X,Y;
	inline void zyt(){
		X=r(),Y=r(),n=r(),m=r();
		for(ri i=1;i<=n;++i)A[i]=r();sort(A+1,A+1+n);
		for(ri i=1;i<=m;++i)B[i]=r();sort(B+1,B+1+m);
//转换
		for(ri i=1;i<=n;++i)a[i]=A[i]-A[i-1];a[n+1]=X-A[n];
		for(ri i=1;i<=m;++i)b[i]=B[i]-B[i-1];b[m+1]=Y-B[m];
		++n,++m;
//网格图代码
		sort(a+1,a+1+n);
		sort(b+1,b+1+m);
		int t1=m-1,t2=n-1,S=a[1]*(m-1)+b[1]*(n-1);
		for(ri i=2,j=2;i<=n&&j<=m;){
			if(a[i]<b[j])S+=a[i]*t1,--t2,++i;
			else S+=b[j]*t2,--t1,++j;
		}
		wln(S);
	}
}
signed main(){
	D1n0::zyt();
}
```

---

## 作者：_smart_stupid_ (赞：0)

## [题目](https://www.luogu.com.cn/problem/P6171)

我们可以把每一个小方格看做一个点，要拆除一个栅栏就相当于给相邻的点连上一条边，使得这两个点联通，耗费的权值就是这个栅栏的长度。

那么要使权值最小，我们就要尽量拆除代价小的边，同时，如果有两个点已经联通，连接这两个点的边就不用拆除了。我们可以用并查集来判断两个点是否联通。

我们先建立纵横两个方向的边，再把每一条边按边权从小到大排序，遍历每一条边，如果这一条边连接的两点不联通，就给这两个点合并到一起，把答案的权值加上这条边的权值。最后输出答案的权值即可。

如果你没有学过 kruskal 算法，那么看到这里你都没有什么问题的话，你就学会了 kruskal 算法，因为我上面说的就是 kruskal 算法的主要流程，是不是很简单？

## 时间复杂度:

首先，建边，$nm$ 条边，然后排序并查集，$O(nm\log(n,m))$，吸氧能过。

## AC Code：

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int h, w, n, m;
int a[2010], b[2010];
struct edge{
    int u, v, w, nxt;
};
edge ed[10000100];
int cnt;
bool cmp(edge a, edge b) {
    return a.w < b.w;
}
int f[10000100];
int find(int x) {return x == f[x] ? x : f[x] = find(f[x]);}
long long ans;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> h >> w >> n >> m;
    for (int i = 1; i <= n; i ++) cin >> a[i];
    for (int i = 1; i <= m; i ++) cin >> b[i];
    sort (a + 1, a + n + 1);
    n++;
    a[n] = h;
    sort (b + 1, b + m + 1);
    m++;
    b[m] = w;
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= m; j ++) {
            f[(i - 1) * m + j - 1] = (i - 1) * m + j - 1;
        }
    }
    for (int i = 1; i < n; i ++) {
        for (int j = 1; j <= m; j++) {
            cnt++;
            ed[cnt].u = (i - 1) * m + j - 1;
            ed[cnt].v = i * m + j - 1;
            ed[cnt].w = b[j] - b[j - 1];
        }
    }
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j < m; j ++) {
            cnt++;
            ed[cnt].u = (i - 1) * m + j - 1;
            ed[cnt].v = (i - 1) * m + j;
            ed[cnt].w = a[i] - a[i - 1];
        }
    }
    sort(ed + 1, ed + cnt + 1, cmp);
    for (int i = 1; i <= cnt; i ++) {
        if (find(ed[i].u) != find(ed[i].v)) {
            ans += ed[i].w;
            f[find(ed[i].v)] = find(ed[i].u);
        }
    }
    cout << ans;
    return 0;
}
```

---

## 作者：_299817_ (赞：0)

## Part 0：前言
这里提供只能通过弱化版的做法。

强化版的题解在这里：[here](https://www.luogu.com.cn/blog/501470/solution-p3141)。

## Part 1：主要思路
首先，我们对于整个题目进行一个抽象化。

比如说，我们现在的图是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/tt1vie3g.png)

我们可以以每个格子为点建图。

那么怎么加边呢？

不难发现一件事情，就是我们要使得每个格子都联通，那么就是要求出所有格子组成的这个图的最小生成树。

答案既然要我们求最小代价，那么也就对应这里的最小生成树的大小，所以我们可以让边权变为两个格子之间的隔板的长度。

于是，对于这个图，我们就能建另外一个图了：

![](https://cdn.luogu.com.cn/upload/image_hosting/zlc7ht9v.png)

这时，我们需要对这个图求最小生成树，即可得出答案。

复杂度为 $O(nm\log(nm))$，瓶颈在于排序。

正常好像卡不过去，需要吸氧。

## Part 2：完整代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<unordered_map>
#include<map>
#include<queue>
#include<stack>
#include<bitset>
#define rep(i, l, r) for(int i = l; i <= r; i++)
#define per(i, l, r) for(int i = l; i >= r; i--)
#define map unordered_map
using namespace std;
typedef long long ll;

struct edge{
    int x, y;
    int val;
};

int A, B, n, m;
int aa[2010], bb[2010];
int a[2010];
int b[2010];
edge e[8020010];
int cnt;
int fa[4010010];

void add(int x, int y, int z){ // 加边
    cnt++;
    e[cnt] = {x, y, z};
}

int translate(int x, int y){ // 对于坐标 (x, y) 转化为一个点的编号。
    return (x - 1) * m + y;
}

int getf(int u){ // 并查集找父亲
    if(fa[u] == u){
        return u;
    }
    return fa[u] = getf(fa[u]);
}

bool cmp(edge x, edge y){ // 比较函数
    return x.val < y.val;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> A >> B >> n >> m;
    for(int i = 1; i <= (n + 1) * (m + 1); i++){
        fa[i] = i;
    }
    rep(i, 1, n){
        cin >> aa[i];
    }
    rep(i, 1, m){
        cin >> bb[i];
    }
    // 排序
    sort(aa + 1, aa + n + 1), sort(bb + 1, bb + m + 1);
    aa[n + 1] = A, bb[m + 1] = B;
    rep(i, 1, n + 1){
        a[i] = aa[i] - aa[i - 1];
    }
    rep(i, 1, m + 1){
        b[i] = bb[i] - bb[i - 1];
    }
    // 求出每条边长
    n++, m++;
    rep(i, 1, n){
        rep(j, 1, m){
            if(j < m){
                add(translate(i, j), translate(i, j + 1), a[i]);
            }
            if(i < n){
                add(translate(i, j), translate(i + 1, j), b[j]);
            }
        }
    }
    // 最小生成树算法
    sort(e + 1, e + cnt + 1, cmp);
    ll ans = 0;
    rep(i, 1 ,cnt){
        if(getf(e[i].x) == getf(e[i].y)){
            continue;
        }
        ans += e[i].val;
        fa[getf(e[i].x)] = getf(e[i].y);
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：zhzkiller (赞：0)

[本题强化版](https://www.luogu.com.cn/problem/P3141)

## 题目描述
给定一个网格图每一行的位置 $a_i$ 和每一列的位置 $b_i$，要求在这个图上找最小生成树。

## 解题思路
先把相邻行 / 列的距离求出来。

~~这个复杂度可以用 kruskal 和 prim 水？~~

虽然但是，最小生成树**一定包含最短的那条边**这个结论依然适用，在本题则是**最短的那一条行或列**。

找到了，$ans$ 也更新了，后面咋办？

既然我们找到的行 / 列已经联通，我们不妨一这条行 / 列为基础，向图的剩下相邻行 / 列进行 $O(n)$ 贪心。以下 $a$ 与 $b$ 数组均代表相邻距离。

假设我们现在以列进行贪心，当前所在列为 $i$，则我们要做的就是让所有 $i$ 上的点与列 $i-1$ 联通（反向同理），不难想到有两种情况：

**·** 任意一条连接 $i-1$ 与 $i$ 的边长（即所有的 $a_x$）均大于第 $i$ 列的 $b_i$。

**·** 存在若干条连接 $i-1$ 与 $i$ 的边长小于等于第 $i$ 列的 $b_i$。

对于第一种情况，我们无脑将第 $i$ 列联通即可，然后在这些 $a_x$ 中找一条最小的连上。

对于第二种情况，我们则可以将较小的列联通边 $a_x$ 连接，然后按其数量与 $n$ 的差连接第 $i$ 列上的边。

以行贪心同理。

但是判断大小关系又要 $O(n)$ 的复杂度。

虽然能过，但是我们也可以优化：

**预处理嘛！**

类似离散化，我们 `sort` 后进行前缀和，每次查询的时候用 `upperbound` 函数查一下，每次复杂度 $O(\log n)$。整体时间复杂度 $O(n\log n)$。

完结撒花~

献上蒟蒻的 AC 代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2010;

ll n,m,A,B;
ll a[N],b[N],tem[N];
ll backa[N],backb[N];
ll suma[N],sumb[N],ans;
ll mxa=1e10,mxb=1e10;
int tara,tarb;

void prework()
{
	memcpy(backa,a,sizeof(a));
	memcpy(backb,b,sizeof(b));
	sort(backa+1,backa+n+1);
	sort(backb+1,backb+m+1);
	for(int i=1;i<=n;i++) suma[i]=suma[i-1]+backa[i];
	for(int i=1;i<=m;i++) sumb[i]=sumb[i-1]+backb[i];
}

ll querya(int x)
{
	return upper_bound(backa+1,backa+n+1,x)-backa-1;
}

ll queryb(int x)
{
	return upper_bound(backb+1,backb+m+1,x)-backb-1;
}

int main()
{
	scanf("%lld %lld %lld %lld",&A,&B,&n,&m);
	for(int i=1;i<=n;i++) scanf("%lld",&tem[i]);
	tem[++n]=A;sort(tem+1,tem+n+1);
	for(int i=1;i<=n;i++)
	{
		a[i]=tem[i]-tem[i-1];
		if(mxa>a[i]) mxa=a[i],tara=i;
	}
	for(int i=1;i<=m;i++) scanf("%lld",&tem[i]);
	tem[++m]=B;sort(tem+1,tem+m+1);
	for(int i=1;i<=m;i++)
	{
		b[i]=tem[i]-tem[i-1];
		if(mxb>b[i]) mxb=b[i],tarb=i;
	}
	
	prework();
	if(mxa<mxb)
	{
		ans+=mxa*(m-1);
		for(int i=tara-1;i;i--)
		{
			ll tem=queryb(a[i]);
			if(tem==0) ans+=sumb[1]+a[i]*(m-1);
			else ans+=sumb[tem]+a[i]*(m-tem);
		}
		for(int i=tara+1;i<=n;i++)
		{
			ll tem=queryb(a[i]);
			if(tem==0) ans+=sumb[1]+a[i]*(m-1);
			else ans+=sumb[tem]+a[i]*(m-tem);
		}
	}
	else
	{
		ans+=mxb*(n-1);
		for(int i=tarb-1;i;i--)
		{
			ll tem=querya(b[i]);
			if(tem==0) ans+=suma[1]+b[i]*(n-1);
			else ans+=suma[tem]+b[i]*(n-tem);
		}
		for(int i=tarb+1;i<=m;i++)
		{
			ll tem=querya(b[i]);
			if(tem==0) ans+=suma[1]+b[i]*(n-1);
			else ans+=suma[tem]+b[i]*(n-tem);
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

