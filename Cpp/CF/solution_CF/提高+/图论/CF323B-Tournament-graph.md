# Tournament-graph

## 题目描述

In this problem you have to build tournament graph, consisting of $ n $ vertices, such, that for any oriented pair of vertices $ (v,u) $ $ (v≠u) $ there exists a path from vertex $ v $ to vertex $ u $ consisting of no more then two edges.

A directed graph without self-loops is a tournament, if there is exactly one edge between any two distinct vertices (in one out of two possible directions).

## 样例 #1

### 输入

```
3
```

### 输出

```
0 1 0
0 0 1
1 0 0
```

## 样例 #2

### 输入

```
4
```

### 输出

```
-1
```

# 题解

## 作者：water_tomato (赞：5)

这道题乍看不难，但是构造过程中发现非常毒瘤，因为有一种情况极难构造。

## 题意

[题目链接](https://www.luogu.com.cn/problem/CF323B)

构造一张完全有向图（即任意两点之间都有一条单向边），使任意两有序点之间的距离不大于 $2$。题意应该还算是比较容易理解的。

## 解析

### $n$ 为奇数

题目已知 $n \ge 3$ 且 $n=4$ 时不可行。我们首先考虑 $n$ 是奇数的情况，我认为这种情况还是比较好想的，我们只要对于每一点，其接下来的奇数次序的点都可以直连，偶数次序的点都可以通过走到奇数次序的点，再走一条边到达（因此这些点让他们往回连）。对每一个点都以这种方式连边，我们会轻易发现这张图一定是可行的。

这种情况比较容易，不多做阐述，可以结合代码理解一下。

``` cpp
for(int i=1;i<n;i++){
	bool k=1;
	for(int j=i+1;j<=n;j++){
		if(k)
			a[i][j]=1;
		else a[j][i]=1;
		k^=1;
	}
}
for(int i=1;i<=n;i++){
	for(int j=1;j<=n;j++){
		printf("%d ",a[i][j]);
	}
	printf("\n");
}
```

### $n$ 为偶数

我们首先考虑，如果前 $n-2$ 个点已经可以构造成一张竞赛图的话，我们只需要让前 $n-2$ 个点都连向第 $n-1$ 个点，让第 $n$ 个点连向前 $n-2$ 个点，再让第 $n-1$ 个点连向第 $n-2$ 个点即可，自己画一下图即可确认这一点。

~~然而我们刚开始并不知道偶数个点能不能构造出一张竞赛图，但我们可以在一次 WA 后得到这一结论。~~

我们已知 $4$ 个点不能构造出一张竞赛图，而如果题目要我们手构出 $8$ 个点的图就太毒瘤了，因此本着这种自信，我们决定想办法构造出一张 $6$ 个点的竞赛图——而这我认为是这道题最为困难的一点，且我自己也没找到什么好办法。在以奇数点的构造思路进行尝试失败后，我们考虑到如果让一个点连向多个点，这样别的点只要连向这个点就可以同时完成两步内到达多个点，然后我们凭借这个可能并不明朗的思路，再经过无数次尝试之后，终于构造出了一张完美（~~毒瘤~~）的竞赛图。

![](https://cdn.luogu.com.cn/upload/image_hosting/wk8n20a2.png)

于是代码就很显然了。

``` cpp
a[1][2]=a[1][3]=a[1][4]=a[2][3]=a[2][4]=a[2][5]=
a[3][4]=a[3][6]=a[4][5]=a[4][6]=a[5][1]=a[5][3]=
a[6][1]=a[6][2]=1;
for(int i=n;i>6;i-=2){
	for(int j=1;j<=i-2;j++){
		a[j][i-1]=1;
		a[i][j]=1;
	}
	a[i-1][i]=1;
}
for(int i=1;i<=n;i++){
	for(int j=1;j<=n;j++){
		printf("%d ",a[i][j]);
	}
	printf("\n");
}
```

我们最后再补充上唯一一种无法构造的情况—— $n=4$。

``` cpp
if(n==4){
		printf("-1\n");
		return 0;
	}
```

将上述三段代码组合起来就是最终情况了，这里不再赘述。

---

## 作者：qnqfff (赞：1)

### 思路

考虑奇数怎么构造，容易发现对于每个 $i$ 向后面 $n/2$ 个点连边即可。

考虑偶数怎么构造，如果还像奇数那么构造就会有重复的，于是可以考虑将 $(i,i-\frac{n}{2}),i\in[\frac{n}{2}+1,n]$ 的边断掉，但这样 $i\in[\frac{n}{2}+1,n]$ 的 $i$ 就不符合条件了，于是考虑将 $(i-\frac{n}{2}+1,i),i\in[\frac{n}{2}+1,n]$ 这条边反向即可。

容易发现点数为 $4$ 时无解，需要特判。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<23],*p1=buf,*p2=buf;
int read(){int p=0,flg=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-') flg=-1;c=getchar();}while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}return p*flg;}
int n,a[1010][1010];
signed main(){
	n=read();if(n==4){cout<<-1;return 0;}
	if(n&1){
		for(int i=1;i<=n;i++) for(int j=i%n+1,k=1;k<=n/2;j=j%n+1,k++) a[i][j]=1;
		for(int i=1;i<=n;i++,cout<<'\n') for(int j=1;j<=n;j++) cout<<a[i][j]<<' ';
	}else{
		for(int i=1;i<=n;i++) for(int j=i%n+1,k=1;k<=n/2;j=j%n+1,k++) a[i][j]=1;
		for(int i=n/2+1;i<=n;i++) a[i][i-n/2]=0;for(int i=n/2+2;i<n;i++) a[i][i-n/2+1]=1,a[i-n/2+1][i]=0;
		for(int i=1;i<=n;i++,cout<<'\n') for(int j=1;j<=n;j++) cout<<a[i][j]<<' ';
	}
    return 0;
}
```

---

## 作者：Hoks (赞：1)

## 前言
比较恶心的构造题，duel 发生意外后来提款的时候跳到的题。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842#information)。
## 思路分析
首先看到样例可以先有一个猜想：奇偶讨论。

顺着这个思路，不妨先大胆猜测偶数都不可构造。

接着正式来构造。

我们考虑能否递推，通过 $n$ 这种情况推出 $n+2$ 的情况。

显然这个是可以的，考虑枚举出 $i\in[1,n]$。

那么连边就是 $(i,n+1),(n+2,i)$，最后再连上 $(n+1,n+2)$ 即可。

如果不懂的话可以自己尝试手模一下。

那这样我们就解决奇数的情况了，因为 $n=3$ 已经有一张图了，我们直接用这个图就能推出来所有其他情况了。

接着考虑偶数情况是否都是无解。

~~其实交一发就知道了~~。

那么就要考虑来手动构造一个可行的偶数情况。

从小到大考虑，先考虑最好构造的 $n=6$ 的情况。

大概手模 $5\sim7$ 分钟就能模出来了。

我造出来的如图：![](https://cdn.luogu.com.cn/upload/image_hosting/a93ktnek.png)

接着用这个玩意推除 $n=4$ 外的偶数情况即可。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e3+10,INF=0x3f3f3f3f3f3f3f,mod=998244353;
int n,f,a[N][N];
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
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
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
signed main()
{
    n=read();if(n==4){put("-1");goto genshin;}
    if(n&1) a[1][2]=a[2][3]=a[3][1]=1,f=3;
    else a[1][2]=a[2][3]=a[3][4]=a[4][1]=a[2][4]=a[3][1]=a[4][5]=a[5][3]=a[5][1]=a[2][5]=a[1][6]=a[3][6]=a[6][2]=a[4][6]=a[6][5]=1,f=6;
    for(int i=n;i>f;i-=2)
    {
        for(int j=1;j<=i-2;j++) a[j][i-1]=1,a[i][j]=1;
        a[i-1][i]=1;
    }
    for(int i=1;i<=n;i++){for(int j=1;j<=n;j++) print(a[i][j]),put(' ');put('\n');}
    genshin:;flush();return 0;
}
```

---

## 作者：Rain_chr (赞：1)

### 题意

构造一个有 $n$ 个点的有向图，使得任意两个点之间的最短路不大于 $2$。

### 分析

可以看出，题目要求即为每个点都与其他所有点在长度为 $3$ 的环内。

遇到这种构造题，我们首先就应该画图理解。

如下为 $n=5$ 的一种解法：

![](https://cdn.luogu.com.cn/upload/image_hosting/hpzbvio9.png)

我们再来分析每个点的入度和出度。

发现什么没有？只有两个点的度数相差 $1$，并且一个是入度大于出度，另一个正好相反。

由此恍然大悟：这不就是欧拉图吗？

于是我们就可以将欧拉回路的代码交上去了，只不过要特判 $n=4$。

### 证明

在此之前，我们需要证明对于任意 $n$ 个点的图如果可行，那么 $n+2$ 个点的图也可行。

我们可以将之前 $n$ 个点都向 $n+1$ 连一条出边，再将 $n+2$ 向它们连一条出边，最后将 $n+1$ 向 $n+2$ 连一条出边构成一个新的可行的图。

因为这样所有点都会在长度为 $3$ 的环内。

而为了加速这一过程，我们用了 DFS 找环。为了使连边不重复，我们就只能连一条边删一条边，而这恰恰与欧拉回路的思想相同，因此此题可以直接以欧拉回路来解决。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
bool ans[1010][1010];
int head[1010];
int n;
void dfs(int x)
{
	while(head[x]<n)
	{
		head[x]++;
		if(ans[x][head[x]]||ans[head[x]][x]||head[x]==x)
			continue;
		ans[x][head[x]]=1;
		dfs(head[x]);
	}
}
signed main()
{
	ios::sync_with_stdio(false); 
	cin>>n;
	if(n==4)
	{
		cout<<-1;
		return 0;
	}
	dfs(1);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
			cout<<ans[i][j]<<' ';
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：Rubidium_Chloride (赞：1)

神（xuan）奇（xue）构造题

## 0.前言

[$\color{Red}{\text{在}}\color{orange}\text{博}\color{yellow}\color{green}\text{客}\color{Turquoise}\text{里}\color{blue}\text{看}\color{purple}\color{Red}\text{效}\color{orange}\text{果}\color{yellow}\text{更}\color{green}\text{好}\color{Turquoise}\text{哦}\color{blue}!$](https://www.luogu.com.cn/blog/Rolling-blog1424/solution-cf323b)

## 1.题目大意

原题翻译说的很明确了，就略过了。

## 2.分析

构造题好评。

先证一个结论：

结论1：如果 $n$ 个点可以，$n+2$ 个点一定也可行

建议说明：

![](https://cdn.luogu.com.cn/upload/image_hosting/9305dtuj.png?x-oss-process=image/resize,m_lfit,h_1500,w_1500)

第 $n+1$ 个点向原来的 $n$ 个点各引出一条边，而原来的 $n$ 个点向 $n+2$ 引出一条边，最后 $n+2 \rightarrow n+1$。

下证这个图是可以的。

$1.\ i\rightarrow j$，其中 $1\le i,j \le n$：因为原图成立，所以新图仍成立；

$2.\ n+1\rightarrow i$，其中 $1\le i\le n$：有一条 $n+1\rightarrow i$ 的直接的边，所以成立；

$3.\ i\rightarrow n+1$，其中 $1\le i\le n$：$i\rightarrow n+2\rightarrow n+1$；

$4.\ i\rightarrow n+2$，其中 $1\le i\le n$：有一条 $i\rightarrow n+2$ 的直接的边，所以成立；

$5.\ n+2\rightarrow i$，其中 $1\le i\le n$：$n+2\rightarrow n+1\rightarrow i$；

$6.\ n+1\rightarrow n+2$：$n+1\rightarrow i\rightarrow n+1$，其中 $1\le i\le n$；

$7.\ n+2\rightarrow n+1$：有一条 $n+2\rightarrow n+1$ 的直接的边，所以成立；

综上，结论1证毕！

根据样例可以得到 $n=3$ 可以。

如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/bdxylicf.png?x-oss-process=image/resize,m_lfit,h_1500,w_1500)

结合结论1，可知对于 $n\ge 3$ 且 $n$ 为奇数的情况都成立。

然后再根据样例得到 $n=4$ 不行。

具体证明是通过有长度为 $3$ 的环和有长度为 $4$ 的环进行讨论。

有兴趣的读者可以自己证明试试。

所以我们来考虑 $n=6$ 吧！

事实证明可行：

![](https://cdn.luogu.com.cn/upload/image_hosting/cng0z8r2.png?x-oss-process=image/resize,m_lfit,h_1500,w_1500)

~~其实这图是很对称的。~~

有时间的可以尝试把这些点两两之间的路径列出来，作者这里就不列了。

给个邻接表：

```
0 1 1 1 0 0
0 0 1 1 1 0
0 0 0 1 0 1
0 0 0 0 1 1
1 0 1 0 0 1
1 1 0 0 0 0
```


然后就可以利用结论1的方法构造 $n\ge 6$ 且 $n$ 为偶数的情况啦。

## 3.CODE

```cpp
#include<bits/stdc++.h>
#define N 1009
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;
inline ll read(){
	int c=getchar();ll f=0,x=1;
	while(!isdigit(c)){if(c=='-') x=-1;c=getchar();}
	while(isdigit(c)) f=f*10+c-48,c=getchar();
	return f*x;
}
ll n,mp[N][N]; 
const ll mp3[4][4]={{0,0,0,0},
{0,0,1,0},
{0,0,0,1},
{0,1,0,0},},mp6[7][7]={{0,0,0,0,0,0,0},
{0,0,1,1,1,0,0},
{0,0,0,1,1,1,0},
{0,0,0,0,1,0,1},
{0,0,0,0,0,1,1},
{0,1,0,1,0,0,1},
{0,1,1,0,0,0,0},
};//初始化
void build(ll k){//建图
	if(k==3){
		for(int i=1;i<=3;i++)
			for(int j=1;j<=3;j++) mp[i][j]=mp3[i][j];
		return;
	}
	if(k==6){
		for(int i=1;i<=6;i++)
			for(int j=1;j<=6;j++) mp[i][j]=mp6[i][j];
		return;
	}
	build(k-2);
	for(int i=1;i<=k-2;i++) mp[k-1][i]=1;
	for(int i=1;i<=k-2;i++) mp[i][k]=1;
	mp[k][k-1]=1;
}
int main(){
	n=read();
	if(n==4){printf("-1");return 0;}//唯独n=4不行
	build(n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++) printf("%lld ",mp[i][j]);
		printf("\n");
	}
	return 0;
}

```

## 4.后记

图论构造题喜加一。

---

## 作者：lgswdn_SA (赞：1)

我们一开始有一个很 simple 的结论，就是三角形是可行的。于是我们可以我们首先通过~~瞎搞~~可以知道，**如果 $n$ 可行，那么 $n+2$ 一定可行**。具体连边就是 $(1...n)$, $n+1$ 和 $n+2$ 围成很多三角形。

![image.png](https://i.loli.net/2020/10/05/uXoQV4Lqvj3gwWl.png)

然后考虑最小的可行的 $n$。由于是 $n+2$，所以要分奇偶考虑。

对于奇数，最小可行的就是一个三角形，于是 $n=3$。邻接矩阵为

```plain
0 1 0
0 0 1
1 0 0
```

对于偶数，很遗憾，$n=4$ 并不可行。经过手动枚举或者暴力搜索，可以得到 $n=6$ 是可行的。并且 $n=6$ 的构造是

![image.png](https://i.loli.net/2020/10/05/8Pra7x3DLY9Wiyn.png)

邻接矩阵为

```plain
0 1 1 1 0 0
0 0 1 1 1 0
0 0 0 1 0 1
0 0 0 0 1 1
1 0 1 0 0 1
1 1 0 0 0 0
```

完整代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1009;

int n,e[N][N],base[2]={6,3};

void build() {
	for(int i=base[n%2]+2;i<=n;i+=2) {
		for(int j=1;j<=i-2;j++) e[i][j]=e[j][i-1]=1;
		e[i-1][i]=1;
	}
}

int main() {
	scanf("%d",&n);
	if(n&1) e[1][2]=e[2][3]=e[3][1]=1;
	else e[1][2]=e[1][3]=e[1][4]=e[2][3]=e[2][4]=e[2][5]=e[3][4]=e[3][6]
		=e[4][5]=e[4][6]=e[5][1]=e[5][3]=e[5][6]=e[6][1]=e[6][2]=1;
	if(n==4) return puts("-1"), 0;
	build();
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=n;j++) printf("%d ",e[i][j]);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：zk_y (赞：0)

考虑能否从 $n$ 较小的情况转化到 $n$ 较大的情况。

想从 $n$ 转移到 $n+1$。

考虑一个点 $u$，有边 $u\rightarrow n+1$，那么此时考虑从 $n+1$ 到 $u$ 的路径，那么只能从 $u$ 的连边来看，比较麻烦，先放在这里。

想从 $n$ 转移到 $n+2$

考虑一个点 $u$，有边 $u\rightarrow n+1$，那么考虑从 $n+1$ 到 $u$。

此时的想法就很自然，只需要有 $n+2\rightarrow u$ 以及 $n+1\rightarrow n+2$ 即可。

接着考虑有一个点 $v$，有边 $v\rightarrow n+2$，那么考虑从 $n+2$ 到 $v$。

此时无法利用 $n+1$ 这个点了（由于已经有边 $n+1\rightarrow n+2$）。于是，我们再找出一个点，不妨设为 $1$，考虑将 $1$ 当一个“中转站”。于是 $v$ 的要求便是有边 $1\rightarrow v$。

类似的，我们可以让 $u$ 满足有边 $u\rightarrow 1$。

由于 $1$ 是中转站，所以连边 $1\rightarrow n+1,n+2\rightarrow 1$。

此时考虑 $v$ 如何到 $n+1$，很简单，只需要连边 $n+1\rightarrow v$。

类似的，连边 $u\rightarrow n+2$。

整理一下：

> 记 $u$ 是所有满足有边 $u\rightarrow 1$ 的点，$v$ 是所有满足有边 $1\rightarrow v$ 的点。
> 
> 首先连边 $n+1\rightarrow n+2$。
> 
> 然后连边 $1\rightarrow n+1$，$n+2\rightarrow 1$。
>
> 最后连边 $u\rightarrow n+1$，$v\rightarrow n+2$，$n+2\rightarrow u$，$n+1\rightarrow v$。

那么，我们可以说明，当 $n$ 满足题意的时候，$n+2$ 也满足题意。

由于 $n=3$ 满足题意，知道所有大于等于 $3$ 的奇数满足题意。

由于 $n=4$ 不满足题意，所以考虑枚举出一个满足题意的偶数。

当 $n=6$ 时，可以给出构造：

![](https://cdn.luogu.com.cn/upload/image_hosting/dxxejyws.png)

然后就说明除了 $n=4$ 所有大于 $2$ 的偶数都有解。

于是就结束了。

```cpp
#include<bits/stdc++.h>2
using namespace std;
#define ll long long
#define ull unsigned long long
#define L(i,j,k) for(int i=j;i<=k;i++)
#define R(i,j,k) for(int i=j;i>=k;i--)

const int N=1e3+100;
//const ll inf=3e18;

int edge[N][N]; 

vector<int> A,B;
int n;
int main(){
	
	ios::sync_with_stdio(0);
	
	cin>>n;
	
	if(n==4){
		cout<<"-1\n";
		return 0;
	}
	
	if(n&1){
		edge[1][2]=edge[2][3]=edge[3][1]=1;
		A.push_back(2);B.push_back(3);
		for(int i=3;i<=n-2;i+=2){
			edge[1][i+1]=edge[i+1][i+2]=edge[i+2][1]=1;
			for(int j=0;j<A.size();j++)edge[i+1][A[j]]=1,edge[A[j]][i+2]=1;
			for(int j=0;j<B.size();j++)edge[i+2][B[j]]=1,edge[B[j]][i+1]=1;
			A.push_back(i+1);B.push_back(i+2);
		}
		L(i,1,n){
			L(j,1,n)cout<<edge[i][j]<<' ';
			cout<<'\n';
		}
	}else{
		edge[1][2]=edge[3][4]=edge[4][6]=edge[3][6]=edge[2][5]=edge[1][5]=edge[1][3]=edge[2][3]=edge[2][6]=edge[5][4]=edge[4][2]=edge[4][1]=edge[5][3]=edge[6][1]=edge[6][5]=1;
		A.push_back(2),A.push_back(3),A.push_back(5);
		B.push_back(4),B.push_back(6);
		for(int i=6;i<=n-2;i+=2){
			edge[1][i+1]=edge[i+1][i+2]=edge[i+2][1]=1;
			for(int j=0;j<A.size();j++)edge[i+1][A[j]]=1,edge[A[j]][i+2]=1;
			for(int j=0;j<B.size();j++)edge[i+2][B[j]]=1,edge[B[j]][i+1]=1;
			A.push_back(i+1);B.push_back(i+2);
		}
		L(i,1,n){
			L(j,1,n)cout<<edge[i][j]<<' ';
			cout<<'\n';
		}
	}
	
	
	return 0;
}
```

---

