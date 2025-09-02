# [HNOI/AHOI2018] 道路

## 题目描述

W 国的交通呈一棵树的形状。W 国一共有 $n-1$ 个城市和 $n$ 个乡村，其中城市从 $1$ 到 $n-1$ 编号，乡村从 $1$ 到 $n$ 编号，且 $1$ 号城市是首都。道路都是单向的，本题中我们只考虑从乡村通往首都的道路网络。

对于每一个城市，恰有一条公路和一条铁路通向这座城市。对于城市 $i$， 通向该城市的道路（公路或铁路）的起点，要么是一个乡村，要么是一个编号比 $i$ 大的城市。没有道路通向任何乡村。除了首都以外，从任何城市或乡村出发只有一条道路；首都没有往外的道路。从任何乡村出发，沿着唯一往外的道路走，总可以到达首都。

W 国的国王小 W 获得了一笔资金，他决定用这笔资金来改善交通。由于资金有限，小 W 只能翻修 $n-1$ 条道路。小 W 决定对每个城市翻修恰好一条通向它的道路，即从公路和铁路中选择一条并进行翻修。小 W 希望从乡村通向城市可以尽可能地便利，于是根据人口调查的数据，小 W 对每个乡村制定了三个参数，编号为 $i$ 的乡村的三个参数是 $a_i$，$b_i$ 和 $c_i$。假设从编号为 $i$ 的乡村走到首都一共需要经过 $x$ 条未翻修的公路与 $y$ 条未翻修的铁路，那么该乡村的不便利值为：

$$c_i \cdot (a_i + x) \cdot (b_i + y)$$

在给定的翻修方案下，每个乡村的不便利值相加的和为该翻修方案的不便利值。 翻修 $n-1$ 条道路有很多方案，其中不便利值最小的方案称为最优翻修方案，小 W 自然希望找到最优翻修方案，请你帮助他求出这个最优翻修方案的不便利值。

## 说明/提示

【样例解释 1】 

![](https://cdn.luogu.com.cn/upload/pic/17506.png)

如图所示，我们分别用蓝色、黄色节点表示城市、乡村；用绿色、红色箭头分别表示 公路、铁路；用加粗箭头表示翻修的道路。 

一种不便利值等于 $54$ 的方法是：翻修通往城市 $2$ 和城市 $5$ 的铁路，以及通往其他城市的 公路。用 $\rightarrow$ 和 $\Rightarrow$ 表示公路和铁路，用 $∗\rightarrow$ 和 $∗\Rightarrow$ 表示翻修的公路和铁路，那么： 

编号为 $1$ 的乡村到达首都的路线为：$-1 ∗\rightarrow 3 \Rightarrow 1$，经过 $0$ 条未翻修公路和 $1$ 条未翻修铁路，代价为 $3 \times (1 + 0) \times (2 + 1) = 9$；  

编号为 $2$ 的乡村到达首都的路线为：$-2 \Rightarrow 3 \Rightarrow 1$，经过 $0$ 条未翻修公路和 $2$ 条未翻修铁路，代价为 $2 \times (1 + 0) \times (3 + 2) = 10$；  
编号为 $3$ 的乡村到达首都的路线为：$-3 ∗\rightarrow 4 \rightarrow 2 ∗\rightarrow 1$，经过 $1$ 条未翻修公路和 $0$ 条未翻修铁路，代价为 $3 \times (2 + 1) \times (1 + 0) = 9$；  

编号为 $4$ 的乡村到达首都的路线为：$-4 \Rightarrow 4 \rightarrow 2 ∗\rightarrow 1$，经过 $1$ 条未翻修公路和 $1$ 条未翻修铁路，代价为 $1 \times (2 + 1) \times (3 + 1) = 12$；

编号为 $5$ 的乡村到达首都的路线为：$-5 \rightarrow 5 ∗\Rightarrow 2 ∗\rightarrow 1$，经过 $1$ 条未翻修公路和 $0$ 条未翻修铁路，代价为 $2 \times (3 + 1) \times (1 + 0) = 8$；  

编号为 $6$ 的乡村到达首都的路线为：$-6 ∗\Rightarrow 5 ∗\Rightarrow 2 ∗\rightarrow 1$，经过 $0$ 条未翻修公路和 $0$ 条未翻修铁路，代价为 $1 \times (3 + 0) \times (2 + 0) = 6$；  

总的不便利值为 $9 + 10 + 9 + 12 + 8 + 6 = 54$。可以证明这是本数据的最优解。 

【样例解释 2】 

在这个样例中，显然应该翻修所有公路。


【数据范围】 
一共 $20$ 组数据，编号为 $1 \sim 20$。 
对于编号 $\le 4$ 的数据，$n \le 20$；  
对于编号为 $5 \sim 8$ 的数据，$a_i,b_i,c_i \le 5$，$n \le 50$；  
对于编号为 $9 \sim 12$ 的数据，$n \le 2000$；  
对于所有的数据，$n \le 20000$，$1 \le a_i,b_i \le 60$，$1 \le c_i \le 10^9$，$s_i,t_i$ 是 $[-n,-1] \cup (i,n - 1]$ 内的整数，任意乡村可以通过不超过 $40$ 条道路到达首都。

## 样例 #1

### 输入

```
6 
2 3 
4 5 
-1 -2 
-3 -4 
-5 -6 
1 2 3 
1 3 2 
2 1 3 
2 3 1 
3 1 2 
3 2 1```

### 输出

```
54```

## 样例 #2

### 输入

```
9 
2 -2 
3 -3 
4 -4 
5 -5 
6 -6 
7 -7 
8 -8 
-1 -9 
1 60 1 
1 60 1 
1 60 1 
1 60 1 
1 60 1 
1 60 1 
1 60 1 
1 60 1 
1 60 1```

### 输出

```
548```

## 样例 #3

### 输入

```
12 
2 4 
5 3 
-7 10 
11 9 
-1 6 
8 7 
-6 -10 
-9 -4
-12 -5 
-2 -3 
-8 -11 
53 26 491 
24 58 190 
17 37 356 
15 51 997 
30 19 398 
3 45 27 
52 55 838 
16 18 931 
58 24 212 
43 25 198 
54 15 172 
34 5 524```

### 输出

```
5744902
 
```

# 题解

## 作者：Kelin (赞：74)

## [题意](https://blog.csdn.net/BeNoble_/article/details/79951215)


给你一颗二叉树$,$每个叶子节点$i$有三个属性$a_i,b_i,c_i$

每个非叶子节点都能标记往左右儿子的边中的一条边$($分别记为$L$边和$R$边$)$

设叶子节点$i$到根的路径上没有被标记的$L$边有$x$条$,R$边有$y$条

那么$i$的贡献就是

$$c_i(a_i+x)(b_i+y)$$

最小化所有点的贡献和

---

## 题解

那个式子是唬你的

直接考虑**倒推**

设$f[u][i][j]$表示从根到$u$有$i$条没标记的$L$边和$j$条没标记的$R$边

对于每个叶子节点枚举有多少没有被标记的$L$边和$R$边

$$f[u][i][j]=c_u(a_u+i)(b_u+j)$$

对于非叶子节点枚举删哪条边

$$f[u][i][j]=min\{f[lson][i+1][j]+f[rson][i][j],f[lson][i][j]+f[rson][i][j+1]\}$$

$$Ans=f[1][0][0]$$

貌似这题还可以卡空间

```
#include<bits/stdc++.h>
#define fp(i,a,b) for(register int i=a,I=b+1;i<I;++i)
#define fd(i,a,b) for(register int i=a,I=b-1;i>I;--i)
#define go(u) for(register int i=fi[u],v=e[i].to;i;v=e[i=e[i].nx].to)
#define file(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
template<class T>inline bool cmin(T&a,const T&b){return a>b?a=b,1:0;}
using namespace std;
char ss[1<<17],*A=ss,*B=ss;
inline char gc(){return A==B&&(B=(A=ss)+fread(ss,1,1<<17,stdin),A==B)?-1:*A++;}
template<class T>inline void sd(T&x){
    char c;T y=1;while(c=gc(),(c<48||57<c)&&c!=-1)if(c==45)y=-1;x=c-48;
    while(c=gc(),47<c&&c<58)x=x*10+c-48;x*=y;
}
const int N=4e4+1;
typedef int arr[N];
typedef long long ll;
int n,m,Top,Tot;arr a,b,c,s,t,Num,S;ll f[82][41][41];
void dfs(int u,int x,int y){
    int p=Num[u]=Top?S[Top--]:++Tot;
    if(!s[u]){
        fp(i,0,x)fp(j,0,y)f[p][i][j]=(ll)c[u]*(a[u]+i)*(b[u]+j);
        return;
    }
    dfs(s[u],x+1,y),dfs(t[u],x,y+1);
    int ls=Num[s[u]],rs=Num[t[u]];
    fp(i,0,x)fp(j,0,y)
        f[p][i][j]=min(f[ls][i+1][j]+f[rs][i][j],f[ls][i][j]+f[rs][i][j+1]);
    S[++Top]=ls,S[++Top]=rs;
}
int main(){
    #ifndef ONLINE_JUDGE
        file("s");
    #endif
    sd(n);m=2*n-1;int u,v;
    fp(i,1,n-1)sd(u),sd(v),s[i]=u<0?n-1-u:u,t[i]=v<0?n-1-v:v;
    fp(i,n,m)sd(a[i]),sd(b[i]),sd(c[i]);
    dfs(1,0,0);
    printf("%lld\n",f[Num[1]][0][0]);
return 0;
}
```

---

## 作者：teafrogsf (赞：33)

## 考场上的我是多SB才没想到这题的写法啊......我连树链剖分都没想到啊.....
那么，转移的形式楼下讲的非常清楚了，我主要讲下如何卡空间。  
我们可以发现每次$\rm dp$统计答案是自下而上的，所以你当前节点的两个子节点在你这个节点统计完答案后就用不上了。  
所以我们可以记录当前节点的$\rm dfn$，然后遍历左儿子$\rm dfn+1$，右儿子$\rm dfn+2$，因为你的叶子节点是直接将所有情况初始化的，所以不用担心转移的点会弄错。  
你可以发现这样转移最右边的叶子节点，它的$\rm dfn$也不会超过$\rm 40*2+1$。所以空间就可以满足要求了。  
~~不过貌似我初始化的时候没有memset也过了？是数据水还是可以证明不需要啊？不想想了~~  
好像速度是全站Rank3的样子。
```cpp
#include<cstdio>
#include<cstring>
#define neko 100010
#define chkmin(a,b) ((a)<(b)?(a):(b))
#define f(i,a,b) for(register int i=(a);i<=(b);i=-(~(i)))
int n,a[neko],b[neko],c[neko],dfn[neko],son[neko][2];
long long dp[110][50][50];
void dfs(int u,int now,int rd,int tr)
{
    dfn[u]=now;
    if(u>=n)//countries are leaves
    {
      //  memset(dp[dfn[u]],0,sizeof(dp[dfn[u]]));
        f(i,0,rd)
         f(j,0,tr)
          dp[dfn[u]][i][j]=1ll*c[u]*1ll*(a[u]+i)*1ll*(b[u]+j);
        return;
    }
    dfs(son[u][0],now+1,rd+1,tr),dfs(son[u][1],now+2,rd,tr+1);
    f(i,0,rd)
     f(j,0,tr)
      dp[dfn[u]][i][j]=chkmin(dp[dfn[son[u][0]]][i][j]+dp[dfn[son[u][1]]][i][j+1],
      					dp[dfn[son[u][0]]][i+1][j]+dp[dfn[son[u][1]]][i][j]);
}
int main()
{
    int x,y;
    scanf("%d",&n);
    f(i,1,n-1)
    {
        scanf("%d%d",&x,&y),x=(x<0)?(-x+n-1):x,y=(y<0)?(-y+n-1):y;
        son[i][0]=x,son[i][1]=y;
    }
    f(i,0,n-1)scanf("%d%d%d",&a[i+n],&b[i+n],&c[i+n]);
    dfs(1,1,0,0),printf("%lld\n",dp[dfn[1]][0][0]);
    return 0;
}
```

---

## 作者：龙神哈迪斯 (赞：27)

在网上翻了几篇博客没看懂，自己强行开码，于是就写篇博客希望对别的“走投无路”的人有所帮助

心路历程：

普及+的题目，不知道当时自己在想什么，dp式倒是推对了，然而优化不了空间，惨痛RE，然后钦定HNOI凉凉

## 题意:


设叶子结点到根结点，会经过i条未翻修的公路，j条未翻修的铁路

则叶子结点到根结点的贡献为$c[i]*(a[i]+i)*(b[i]+j)$

设计方案控制$i,j$使$\sum_{叶子结点i}c[i]*(a[i]+i)*(b[i]+j)$最小

## Solution

设$f[u][i][j]$表示从根结点到结点u经过$i$条未翻修公路，$j$条未翻修铁路

的贡献最小值

于是有针对叶子结点（乡村），先预处理出
$$f[u][i][j]=c[u]*(a[u]+i)*(b[u]+j)$$

然后是城市点$u$

当$u->v$选择修公路时，则右儿子会多经过一条未修的铁路
$$f[u][i][j]=f[lson][i][j]+f[rson][i][j+1]$$

同理，当$u->v$选择修铁路时，则左儿子会多经过一条未修的公路
$$f[u][i][j]=f[lson][i+1][j]+f[rson][i][j]$$

所以最终二者取$min$
$f[u][i][j]=min(f[lson][i][j]+f[rson][i][j+1],f[lson][i+1][j]+f[rson][i][j]);$

然后是值得注意的细节

1.$f[u][i][j]$开$long long$，然后中间叶子结点相乘时开`1LL`

2.本题卡空间，$f[u][i][j]$ 中的一维$u$是不能开到20000的，这显然MLE，但是我们注意到上述dp再处理过程中，是一定先把儿子处理完才处理的自己，又由于这是一颗满二叉树，所以它相当于每次处理一条链，链与链之间的不影响，所以可以定义$dfn[u]$表示点在链中映射的结点编号，然后只需要开到80就够了（~~恐怕这就是这个题目唯一有价值的地方了吧~~）

最后是激动人心的上代码过程

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
#define ll long long
#define rg register
const int _=40100;
inline int read()
{
    rg char ch='!';rg int z=1,num=0;
    while(ch!='-'&&(ch<'0'||ch>'9'))ch=getchar();
    if(ch=='-')z=-1,ch=getchar();
    while(ch<='9'&&ch>='0')num=(num<<3)+(num<<1)+ch-'0',ch=getchar();
    return z*num;
}
int n,a[_],b[_],c[_];
struct ed{int to,next;}e[_<<1];
vector<int>g[_];
int cnt,head[_];
inline void link(int u,int v){e[++cnt]=(ed){v,head[u]};head[u]=cnt;}
int sz[_],dep[_],dfn[_];
ll f[105][45][45];
void dfs(int u,int k)
{
    dfn[u]=k;
    sz[u]=1;
    for(rg int i=head[u];i;i=e[i].next)
    {
        rg int v=e[i].to;
        dep[v]=dep[u]+1;
        g[u].push_back(v);
        if(g[u][1])dfs(v,k+2);
        else dfs(v,k+1);
        sz[u]+=sz[v];
    }
    if(sz[u]==1)
        for(rg int i=0;i<=dep[u];++i)
            for(rg int j=0;j<=dep[u];++j)
                f[dfn[u]][i][j]=1ll*c[u]*(a[u]+i)*(b[u]+j);
    else
        for(int i=0;i<=dep[u];++i)
            for(int j=0;j<=dep[u];++j)
                f[dfn[u]][i][j]=min(f[dfn[g[u][0]]][i][j]+f[dfn[g[u][1]]][i][j+1],f[dfn[g[u][0]]][i+1][j]+f[dfn[g[u][1]]][i][j]);
}
int main()
{
    memset(f,63,sizeof(f));
    n=read();
    for(rg int x,y,i=1;i<n;++i)
    {
        x=read(),y=read();
        if(y<0)link(i,-y+n-1);
        else link(i,y);
        if(x<0)link(i,-x+n-1);
        else link(i,x);
    }
    for(rg int i=n;i<=2*n-1;++i)a[i]=read(),b[i]=read(),c[i]=read();
    dep[1]=0;dfs(1,0);
    printf("%lld\n",f[dfn[1]][0][0]);
    return 0;
}

```


---

## 作者：grass8cow (赞：16)

先读题。

这个题给出了一棵树，在这棵树里，乡村的点都没有儿子，而城市的点都有两个儿子。所以？

很据题意，可以设 $f_{i,j,k}$，表示从根节点走到序号为 $i$ 的点，通过了 $j$ 条向左走的未修的路（走向左儿子的路），以及 $k$ 条向右走的未修的路（走向右儿子的路）时，以 $i$ 为节点的子树的最小不便利值。


这个数组一开出来，就有浓厚的 $DP$ 气息了。
当 $i$ 是一个乡村时，显然能直接求出 $f_{i,j,k}=c_i(a_i+j)(b_i+k)$ 。而$i$是一个城市，则设 $l_i$ 为 $i$ 的左儿子，$r_i$ 为 $i$ 的右儿子。有两种情况：

1.修向左走的路。则有：

$f_{i,j,k}=f_{l_i,j,k}+f_{r_i,j,k+1}$

2.修向右走的路。则有：

$f_{i,j,k}=f_{l_i,j+1,k}+f_{r_i,j,k}$

两者取其 $min$ ，方能得解。

最后的答案？当然是 $f_{1,0,0}$ 了。

对于输入时乡村序号为负数的情况，采取$x=n-x-1$，使乡村的序号从 $-n$ 到 $-1$ 转化为从 $2n-1$ 到 $n$ ，这样就巧妙而简洁地化解了这一问题。

关于代码：我选用记忆化搜索，使自己不用大量思考循环的细节，空间能打擦边球通过，就懒得优化了~（但优化的方法是很值得学的，多学学其他题解）
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l[20001],r[20001];
long long f[20001][41][41],a[20001],b[20001],c[20001];
long long dfs(int i,int j,int k)
{
	if(i>=n)return c[i-n+1]*(a[i-n+1]+j)*(b[i-n+1]+k);
	if(f[i][j][k]!=f[0][0][0])return f[i][j][k];//记忆化
	return f[i][j][k]=min(dfs(l[i],j,k)+dfs(r[i],j,k+1),dfs(l[i],j+1,k)+dfs(r[i],j,k));
}
int main()
{
	cin>>n;memset(f,63,sizeof(f));
	for(int i=1;i<n;i++)
	{
		cin>>l[i];
		if(l[i]<0)l[i]=n-l[i]-1;
		cin>>r[i];
		if(r[i]<0)r[i]=n-r[i]-1; 
	}
	for(int i=1;i<=n;i++)cin>>a[i]>>b[i]>>c[i];
	cout<<dfs(1,0,0);
	return 0;
}
```

UPD on 2022.2.8: 发现自己当年记忆化了个寂寞（已修改代码）


---

## 作者：不存在之人 (赞：10)

树形dp。

~~刚开始竟然没有想出来，我太菜辣。~~

son[i][0]表示i的左儿子（也就是修公路），son[i][1]表示i的右儿子（也就是修铁路）。

f[i][j][k]表示第i个点到根经过j个未被修复的公路，k个未被修复的铁路所得到的最小值。

最后用个记忆化搜索一下即可。
```cpp
#include<cstdio>  
#include<cstring>  
#include<algorithm>  
#define LL long long  
using namespace std;  
    int n;  
    struct node{LL x,y,z;} a[20010];  
    int son[20010][5];  
    LL f[20010][45][45];  
LL dfs(int x,int p,int q)  
{  
    if(x>=n) return a[x-n+1].z*(a[x-n+1].x+p)*(a[x-n+1].y+q);  
    if(f[x][p][q]!=f[n+1][41][41]) return f[x][p][q];  
    return f[x][p][q]=min(dfs(son[x][0],p,q)+dfs(son[x][1],p,q+1),dfs(son[x][1],p,q)+dfs(son[x][0],p+1,q));  
}  
int main()  
{  
    int x,y;  
    scanf("%d",&n);  
    memset(f,63,sizeof(f));  
    for(int i=1;i<n;i++)  
    {  
        scanf("%d %d",&x,&y);  
        if(x<0) x=-x+n-1;  
        if(y<0) y=-y+n-1;  
        son[i][0]=x;  
        son[i][1]=y;  
    }  
    for(int i=1;i<=n;i++)  
        scanf("%lld %lld %lld",&a[i].x,&a[i].y,&a[i].z);  
    printf("%lld",dfs(1,0,0));  
}
```

---

## 作者：ww3113306 (赞：6)

考试的时候一直看T2，，，最后还是没想出来，结果考完之后再看T3竟然一下就想出转移方程了。。。。。。果然考试这种事emmm。。。

首先我们观察到一个乡村产生的贡献只受公路和铁路条数影响，且每条铁路和公路都是
等效的（也就是说没有权值），

又观察到题目中说乡村可以通过不超过40条路到首都，也就是说深度最大为40，

而且式子处理起来比较麻烦（也可能是我比较弱），于是考虑先暴力预处理出每个乡村在每种可能情况下的贡献

于是f[i][j][k]代表节点i上面有j条公路未翻新，k条铁路未翻新的最优结果.

这样的话，显然有：

**f[x][i][j]=min(f[l[x]][i][j] + f[r[x]][i][j+1] , f[l[x]][i+1][j] + f[r[x]][i][j]);**

但是由于到一个点时，我们并不知道最优情况到底会剩多少路，因此我们需要暴力枚举所有可能。

考虑到深度不超过40，因此所有可能不会太多，

但是本着优化常数的目的，我们先一遍dfs求出每个点上面有几条公路几条铁路，于是枚举的时候就只用枚举到这么多

递推到首都时，答案即为f[1][0][0]

~~自认为代码风格还不错的代码~~
```cpp
#include<bits/stdc++.h>
using namespace std;
#define R register int
#define AC 40020
#define LL long long
int n;
LL f[AC][42][42];
int l[AC],r[AC];//城市
LL a[AC],b[AC],c[AC];//乡村
int have1[AC],have2[AC];
inline int read()
{
	int x=0;char c=getchar();bool z=false;
	while(c > '9' || c < '0') 
	{
		if(c == '-') z=true;
		c=getchar();
	}
	while(c >= '0' && c <= '9') x=x*10+c-'0',c=getchar();
	if(!z) return x;
	else return -x;
}

void pre()
{
	n=read();
	for(R i=1;i<n;i++)
	{
		l[i]=read(),r[i]=read();//左公右铁	
		if(l[i] < 0) l[i]=-l[i] + n - 1;
		if(r[i] < 0) r[i]=-r[i] + n - 1;
	}
	for(R i=1;i<=n;i++)
	{
		int now=i + n - 1;
		a[now]=read(),b[now]=read(),c[now]=read();
	}
}

void dfs(int x)
{
	if(x >= n) return ;
	have1[l[x]] += have1[x] + 1;//上面的都要算下来，另外再加1
	have2[l[x]] = have2[x];
	have2[r[x]] += have2[x] + 1;
	have1[r[x]] = have1[x];
	dfs(l[x]);
	dfs(r[x]);
}

void DFS(int x)
{
	if(x >= n)//如果是叶子节点就要暴力计算了
	{
		for(R i=0;i<=have1[x];i++)
			for(R j=0;j<=have2[x];j++)
				f[x][i][j]=c[x] * (a[x] + i) * (b[x] + j);
		return ;
	}	
	else
	{
		DFS(l[x]);
		DFS(r[x]);
		for(R i=0;i<=have1[x];i++)
			for(R j=0;j<=have2[x];j++)
				f[x][i][j]=min(f[l[x]][i][j] + f[r[x]][i][j+1] , f[l[x]][i+1][j] + f[r[x]][i][j]);
	}
}

int main()
{
	freopen("in.in","r",stdin);
	pre();
	dfs(1);
	DFS(1);
	printf("%lld\n",f[1][0][0]);
	fclose(stdin);
	return 0;
}
```

~~突然发现空间开太大了，，，貌似应该是卡不过的。。。~~

~~这里口胡一个解决方案吧~~

因为我们发现一个点用完之后就没用了，毕竟是棵树嘛

而且叶子节点本来就可以直接算，所以可以f只开20000*40*40

然后特判一下如果是叶子节点的话就直接算，其他的就调用f数组就可以了，

而且因为是树形结构，所以直接算应该不会影响复杂度

这样的话就只用开城市的点了

---

## 作者：feicx (赞：6)

这道题是一道奇妙的树形dp题，~~可以在联赛之前用此练练手~~。

当时在省选上看到这道题是懵逼的，但是现在透过题面看思路，发现是在一个二叉树上求最优值，首先一看看状态，看似是要用树链剖分什么的，后面一看难度提高+/省选-，应该是用树形DP吧。

首先想状态，最先我设$dp_{i,j,k}$表示在以$i$为点的子树中，翻修$j$条公路和$k$条铁路的最小不便利度，后面发现状态是无法转移的，再次思考。发现对于每一个村庄，我们知道不翻修$j$条公路和$k$条铁路的花费是很容易求的，那我于是就重新设$dp_{i,j,k}$表示从起点到$i$号点的路上，不翻修$i$条公路和$j$条铁路的最小花费。

对于每一个点，我定义$u_i$和$v_i$分别表示，从起点到终点，要经过$u_i$条公路和$v_i$条铁路，这样我们可以把村庄的状态表示出来：

$$dp_{i,j,k}=c_i \times (a_i+j) \times (b_i+k)$$

然后对于城市，我们可以翻修铁路和公路，选择一个最小的方案，所以对于一个城市，我们可以得到转移方程如下：

$$dp_{i,j,k}=\min\{dp_{lson_i,j+1,k}+dp_{rson_i,j,k},dp_{lson_i,j,k}+dp_{rson_i,j,k+1}\}$$

它们的限制条件是：

$$j \leq u_i,k \leq v_i$$

要注意**左儿子和右儿子分别使用公路和铁路连接**。这样我就把程序写出来了：

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;

typedef long long int ll;

ll chkmin(ll x,ll y){return x<y?x:y;}
ll chkmax(ll x,ll y){return x<y?y:x;}

ll dp[40010][50][50],c[20010];
int n,a[20010],b[20010];
int lson[20010],rson[20010];

void dfs(int r,int x,int u,int v){
    if(x>0){
        dfs(r*2,lson[x],u+1,v);
        dfs(r*2+1,rson[x],u,v+1);
        for(int i=0;i<=u;i++)
            for(int j=0;j<=v;j++){
                dp[r][i][j]=chkmin(dp[r*2+1][i][j]+dp[r*2][i+1][j],\
                                dp[r*2+1][i][j+1]+dp[r*2][i][j]);
            }
    }
    else{
        for(int i=0;i<=u;i++)
            for(int j=0;j<=v;j++){
                dp[r][i][j]=c[-x]*(a[-x]+i)*(b[-x]+j);
            }
    }
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<n;i++)
        scanf("%d%d",&lson[i],&rson[i]);
    for(int i=1;i<=n;i++)
        scanf("%d%d%lld",&a[i],&b[i],&c[i]);
    dfs(1,1,0,0);
    printf("%lld\n",dp[1][0][0]);
    return 0;
}
```

但是一交上去，我发现只有40分，剩下的点都是RE。

仔细调试分析，发现用这个做枚举的话，$r$可以达到几十万，这是数组存不下的，思考一下，发现我们在做dp枚举的时候，有效状态只有两个，因此每一个当前处理的$r$的左儿子和右儿子可以用$r+1$和$r+2$表示，因此这样可以大大缩小空间，这是后面$60$分的得分关键。

修改一下，然后就过了。

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;

typedef long long int ll;

ll chkmin(ll x,ll y){return x<y?x:y;}
ll chkmax(ll x,ll y){return x<y?y:x;}

ll dp[400][50][50],c[20010];
int n,a[20010],b[20010];
int lson[20010],rson[20010];

void dfs(int r,int x,int u,int v){
    //cout<<r<<" "<<x<<" "<<lson[x]<<" "<<rson[x]<<endl;
    if(x>0){
        dfs(r+2,lson[x],u+1,v);
        dfs(r+2+1,rson[x],u,v+1);
        for(int i=0;i<=u;i++)
            for(int j=0;j<=v;j++){
                dp[r][i][j]=chkmin(dp[r+2+1][i][j]+dp[r+2][i+1][j],\
                                dp[r+2+1][i][j+1]+dp[r+2][i][j]);
            }
    }
    else{
        for(int i=0;i<=u;i++)
            for(int j=0;j<=v;j++){
                dp[r][i][j]=c[-x]*(a[-x]+i)*(b[-x]+j);
            }
    }
}

int main(){
    //freopen("road9.in","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<n;i++)
        scanf("%d%d",&lson[i],&rson[i]);
    for(int i=1;i<=n;i++)
        scanf("%d%d%lld",&a[i],&b[i],&c[i]);
    dfs(1,1,0,0);
    printf("%lld\n",dp[1][0][0]);
    return 0;
}
```

做这道题要注意有两点，第一个是状态的选择，一个好的状态是成功解题的关键；第二个是细节的处理，像本题的空间压缩。

---

## 作者：GoldenPotato137 (赞：5)

[戳我获得更好的阅读体验qwq](https://www.goldenpotato.cn/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92/luogu-p4438-hnoi-ahoi2018%E9%81%93%E8%B7%AF/)

---
# Solution
这是一道树形DP妙题。

平时，我们设计树形DP的状态一般都是以子树为基础来设计的。很不幸的是，这题因为那个蜜汁柿子无法化简，导致了极其严重的后效性。因此，我们这里并不能以子树为基础来设计状态了。

.

这题妙就妙在这个状态设计。这题我们考虑以链为基础来设计状态。

**设$f[i][j][k]$表示从根节点到达第$i$个点，一路上经过了$j$条没有修过的公路及$k$条没有修过的铁路，把它的孩子全部连同到根所需的最小代价**。

这样一来，我们惊讶的发现这样设就没有后效性问题，因为链的状态已经被我们包含在DP的状态里了。

.

转移非常简单，我们只需要**讨论一下是这个点是修铁路还是公路就好。**
即：$f[i][j][k]=min(f[lson][j][k]+f[rson][j][k+1],f[lson][j+1][k],f[rson][j][k])$

但是这样做还有一个问题，就是我们的空间复杂度是$O(n\cdot40\cdot40)$的，开不下。

仔细观察后可以发现我们上面开辣么大的数组，很多地方是用不到的。因此，我们可以考虑只记录一个映射，然后把值记到一个统一的一维数组里面去。

.

时间复杂度$O(n\cdot 40 \cdot 40)$

就酱，这题就被我们切掉啦(～￣▽￣)～ 

---
# Code
```cpp
//Luogu P4438 [HNOI/AHOI2018]道路
//Mar,27th,2019
//你从未见过的船新树形DP
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
long long read()
{
    long long x=0,f=1; char c=getchar();
    while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)){x=x*10+c-'0';c=getchar();}
    return x*f;
}
const int N=20000*2+200;
const int M=40+3;
const long long inf=0x3f3f3f3f3f3f3f3fll;
int f[N][M][M],a[N],b[N],c[N];
long long ans[20000000];
int n,s[N],t[N],to;
long long dfs(int now,long long cnt_s,long long cnt_t)
{
    if(f[now][cnt_s][cnt_t]!=0) 
        return ans[f[now][cnt_s][cnt_t]];
    f[now][cnt_s][cnt_t]=++to;
    if(now>=n)
        return ans[f[now][cnt_s][cnt_t]]=c[now]*(a[now]+cnt_s)*(b[now]+cnt_t);
    long long t_ans=inf;
    t_ans=dfs(s[now],cnt_s,cnt_t)+dfs(t[now],cnt_s,cnt_t+1);
    t_ans=min(t_ans,dfs(s[now],cnt_s+1,cnt_t)+dfs(t[now],cnt_s,cnt_t));
    return ans[f[now][cnt_s][cnt_t]]=t_ans;
}
int main()
{
    n=read();
    for(int i=1;i<n;i++)
    {
        s[i]=read(),t[i]=read();
        if(s[i]<0) s[i]=-s[i]+n-1;
        if(t[i]<0) t[i]=-t[i]+n-1;
    }
    for(int i=1;i<=n;i++)
        a[i+n-1]=read(),b[i+n-1]=read(),c[i+n-1]=read();
    
    int tim=clock();
    
    printf("%lld",dfs(1,0,0));
    cerr<<endl<<clock()-tim;
    return 0;
}

```






---

## 作者：Soulist (赞：5)

题面真的好长$.jpg$

所以考场上某初二大佬打了85分的题我$TM$一分都没拿$QAQ$

~~（算了，我在讲什么？）~~

首先是把罪恶的题面化简：

给一棵树，1节点为根，叶子节点均为农村，城市都是非叶节点，每个城市都有两条边，一条为铁路，一条为公路，现在你可以对每个**非叶节点** 选择其中**一条** 进行番修。

番修后假设一个叶子节点到根要经过$x$条未被番修的道路，$y$条未被番修的公路，那么其对答案产生的贡献为：$(c_i * (a_i+x) * (b_i+y))$

要求最小贡献。

这道题出在省选上，记得当时看的时候，以为它和毒瘤$(Day1T3)$一样毒瘤，而且题面太长了，就没写了.......

然而实际上个人觉得没有机房那些大佬说的那么水啊 QAQ 

观察数据，我们发现其实可以记录每个点到根节点

首先考虑记录状态：$dp_{x,i,j}$表示以$x$根的子树，上面有$i$条公路未被番修，$j$条铁路未被番修的答案。

如果$dp$到了最底下的叶子节点，我们可以$O(K^2)$的去算答案。

当然，要记录每个点顶上有多少条道路和有多少条公路

对于非叶节点，转移也并不难想：

```cpp

for( int i = 0; i <= dep1[x]; ++ i )
for( int j = 0; j <= dep2[x]; ++ j ) 
dp[x][i][j] = dp[ls(x)][i][j] + dp[rs(x)][i][j + 1], 
//这里表示修左儿子的公路，那么右儿子顶上就有一条铁路未被番修。

dp[x][i][j] = min( dp[x][i][j], dp[ls(x)][i + 1][j] + dp[rs(x)][i][j] );

//此处类似
```

然而这样会 $MLE$

我们可以发现，某次$dp$，$dp$到某一层后，其在回溯去更新的点，只有它的父亲，换而言只：**某个点的$dp$值只有在更新其父亲的时候才生效，然后其$dp$不会影响其他点**

如果我们将原来的过程写成$dfs$，我们可以发现，某次$dp$的过程中，对于某一种/层深度，我们只会用到两个点。（左儿子+右儿子）

所以我们可以类似滚动数组去做，用深度去更新，在更新完后此状态无用。

最后的代码在这里啦：

```cpp

#include<bits/stdc++.h>
using namespace std;
int read() {
	char cc = getchar(); int cn = 0, flus = 1;
	while(cc < '0' || cc > '9') {  if( cc == '-' ) flus = -flus;  cc = getchar();  }
	while(cc >= '0' && cc <= '9')  cn = cn * 10 + cc - '0', cc = getchar();
	return cn * flus;
}
#define int long long
const int N = 40000 + 5;
const int K = 45;
const int M = 105;
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i )
#define ls(x) son[x][0]
#define rs(x) son[x][1]
int dp[M][K][K], son[N][3], fa[N], dep1[N], dep2[N]; 
int head[N], cnt, n, a[N], b[N], c[N];
void dfs( int x, int dep, int k ) {
	if( !son[x][0] ) {
		rep( i, 0, dep1[x] ) rep( j, 0, dep2[x] ) 
		dp[dep + k * dep][i][j] = c[x] * ( a[x] + i ) * ( b[x] + j );
		return ;
	}
	dep1[ls(x)] = dep1[x] + 1, dep2[ls(x)] = dep2[x]; //dep1表示公路 
	dep1[rs(x)] = dep1[x], dep2[rs(x)] = dep2[x] + 1; 
	dfs(ls(x), dep + 1, 0 ), dfs(rs(x), dep + 1, 1 );
	rep( i, 0, dep1[x] ) rep( j, 0, dep2[x] )
	dp[dep + k * dep][i][j] = min( dp[dep + 1][i][j] + dp[2 * (dep + 1)][i][j + 1], dp[dep + 1][i + 1][j] + dp[2 * (dep + 1)][i][j] );
}
signed main()
{
	n = read();
	rep( i, 1, n - 1 ) {
		son[i][0] = read(), son[i][1] = read();
		if( son[i][0] < 0 ) son[i][0] = -son[i][0] + n;
		if( son[i][1] < 0 ) son[i][1] = -son[i][1] + n;
	}
	rep( i, 1, n ) a[i + n] = read(), b[i + n] = read(), c[i + n] = read();
	dfs( 1, 0, 0 );
	printf("%lld\n", dp[0][0][0] );
	return 0;
}

```

---

## 作者：LJ07 (赞：4)

## 题目描述
[题目传送门](https://www.luogu.com.cn/problem/P4438)

## 思路简述

+ 由题面能得到的一些结论
1. 乡村一定是叶子节点，城市一定不是叶子结点（每个城市都有通向它的单向路径，但乡村没有）。
2. 树根一定是 $1$ 号节点（通向该城市的道路的起点，要么是一个乡村，要么是一个编号比 $i$ 大的城市）。
3. 树其实是一颗二叉树（显然）。
+ 为了方便编写代码，我们规定城市的编号是 $1$ 到 $n-1$, 乡村的编号是 $n$ 到 $2 \times n -1$。也不妨假定左儿子是用公路连接的，右儿子是用铁路连接的。
+ 看到求最值，容易想到是使用树形 dp。
+ 看到 **任意乡村可以通过不超过40条道路到达首都**，状态其实就已经很明显了。
+ 我们规定 
1. $f[u][i][j]$ 表示第 $u$ 个节点上面已经修建了 $i$ 条公路， $j$ 条铁路。
2. $A[i]$ 表示第 $i$ 个节点是 $1$ 号节点走了几次左儿子到达的。
3. $B[i]$ 表示第 $i$ 个节点是 $1$ 号节点走了几次右儿子到达的。
4. $l[i]$ 表示第 $i$ 个节点的左儿子的编号。
5. $r[i]$ 表示第 $i$ 个节点的右儿子的编号。
+ 我们关于 $A[]$, $B[]$ 有以下的转移：
1. $A[l[i]]=A[i]+1$,$A[r[i]]=A[i]$
2. $B[r[i]]=B[i]+1$,$B[l[i]]=B[i]$
+ 对于每个非乡村的节点 $i$， 有两种决策，一种是修建公路，另一种是修建铁路，对应的转移方程如下：
$f[i][j][k]=\min(f[l[i]][j+1][k]+f[r[i]][j][k],
			f[l[i]][j][k]+f[r[i]][j][k+1]);$
+ 特别地，对于 $i$ 号节点是乡村的情况直接计算即可。
+ 如果你直接使用 $3$ 维数组的 dp 提交会发现 MLE 了 $4$ 个点。直接使用 map 替代 $3$ 维数组即可（常数略大）。
## 丑陋的代码
[click here](https://www.luogu.com.cn/paste/kgo8snip)

---

## 作者：happybob (赞：1)

注意到树高度不超过 $40$，我们考虑有没有什么可以突破的地方。

我们要求的答案也是与路径中的边数有关，不妨考虑 DP，$f_{i,j,k}$ 表示从根到 $i$ 经过了 $j$ 条未翻修的公路和 $k$ 条未翻修的铁路，考虑以 $i$ 为根的子树的最小答案。转移考虑选的是左儿子翻修还是右儿子翻修即可。注意到这个东西顺推可能有点难写，考虑写个记忆化。令 $D$ 为树最高高度，复杂度 $O(nD^2)$，$D \leq 40$，可以通过。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

const int N = 4e4 + 5;
int n;
int s1[N], s2[N];
long long f[N][41][41];
long long a[N], b[N], c[N];
vector<int> G[N];

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	for (int i = 1; i < n; i++)
	{
		int s, t;
		cin >> s >> t;
		if (s < 0) s = (-s) + n - 1;
		if (t < 0) t = (-t) + n - 1;
		s1[i] = s, s2[i] = t;
	}
	for (int i = n; i <= 2 * n - 1; i++) cin >> a[i] >> b[i] >> c[i];
	auto dfs = [&](auto self, int u, int x, int y)->long long
		{
			if (f[u][x][y]) return f[u][x][y];
			if (u > n - 1)
			{
				return c[u] * (a[u] + x) * (b[u] + y);
			}
			// think of left or right
			// left
			long long res = self(self, s1[u], x, y) + self(self, s2[u], x, y + 1);
			long long res2 = self(self, s1[u], x + 1, y) + self(self, s2[u], x, y);
			return f[u][x][y] = min(res, res2);
		};
	cout << dfs(dfs, 1, 0, 0) << "\n";
	return 0;
}
```


---

## 作者：Lee666666 (赞：1)

极其一眼的想法：树形 DP。

传统做法：用子树根节点记录子树的状态，那么考虑设 $dp_{i,j}$ 表示以 $i$ 为根的子树中翻修了 $j$ 条公路的最小不便利值。因为**每一个非叶子节点都会修一条公路或一条铁路**，所以可以通过 $j$ 以及以 $i$ 为根的子树的大小算出翻修铁路的数量。

但是因为 $n \leq 2 \times 10^4$ 而这种做法的时间复杂度达到了 $O(n^2)$，所以得另寻他法。

注意到数据范围中给出树的深度 $dep \leq 40$，于是考虑重设状态，以根节点到 $i$ 的信息作为第二维。那么设 $dp_{i,j,k}$ 表示根节点到 $i$ 的路径中未翻修 $j$ 条公路， $k$ 条铁路的最小不便利值，于是对于非叶子节点，依旧由**每一个非叶子节点都会修一条公路或一条铁路**得出转移方程
$$
dp_{i,j,k}=\min(dp_{lson,j,k}+dp_{rson,j,k+1},dp_{lson,j+1,k}+dp_{rson,j,k})
$$

其中 $lson$ 表示公路连向的儿子，$rson$ 表示铁路连向的儿子。

对于叶子结点有初始状态
$$
dp_{i,j,k}=c_i \times (a_i + x) \times (b_i + y)
$$

答案显然为 $dp_{1,0,0}$。

时间复杂度 $O(n \times dep^2)$，空间复杂度 $O(n \times dep^2)$。

这道树形 DP 常数较小，时间方面问题不大。但因为 $a_i,b_i \leq 60,c_i \leq 10^9$ 显然要开 long long 存储 DP 数组，约占空间 $2 \times 2 \times 10^4 \times 40^2 \times 8 \div 1024^2 \approx 488$ MB，非常极限。~~事实上这个空间复杂度就是卡在最后一个点过不去。~~ 于是我们利用与**滚动数组**类似的思想，对于每一个**当前未求出 DP 值的节点**，我们只需记录**其儿子节点的 DP 信息**，而无需记录其**已经计算出 DP 值的儿子节点的子孙的信息**。于是，空间复杂度就达到了 $O(dep^3)$，十分稳健。关于具体实现细节，我的想法是考虑记录 mp 数组表示节点编号到 DP 数组编号的映射，然后类似于 tarjan 算法维护一个类似于时间戳的东西去更新 mp 数组，**注意时间戳增加和减少的顺序**。

Code
```cpp
#include <cstdio>
using namespace std;

typedef long long LL;

inline int read() {
	bool f = 0;
	int s = 0;
	char ch = getchar();
	while (ch < 48 || ch > 57) {
		f = ch == 45;
		ch = getchar();
	}
	while (ch > 47 && ch < 58) {
		s = (s << 3) + (s << 1) + (ch ^ 48);
		ch = getchar();
	}
	return f ? -s : s;
}

inline LL min(LL a, LL b) {
	return a < b ? a : b;
}

int n, times, a[20015], b[20015], c[20015], lson[20015], rson[20015], mp[40015];
LL dp[115][41][41];

inline int ord(int x) {
	return x < 0 ? -x : x + n;
}

void dfs(int u, int xcnt, int ycnt) {
	if (u <= n) {
		mp[u] = ++times;
		for (int x = 0; x <= xcnt; x++) {
			for (int y = 0; y <= ycnt; y++) {
				dp[mp[u]][x][y] = 1LL * c[u] * (a[u] + x) * (b[u] + y);
			}
		}
		return;
	}
	else {
		mp[u] = ++times;
		dfs(lson[u - n], xcnt + 1, ycnt);
		dfs(rson[u - n], xcnt, ycnt + 1);
		for (int x = 0; x <= xcnt; x++) {
			for (int y = 0; y <= ycnt; y++) {
				dp[mp[u]][x][y] = min(dp[mp[lson[u - n]]][x][y] + dp[mp[rson[u - n]]][x][y + 1], dp[mp[lson[u - n]]][x + 1][y] + dp[mp[rson[u - n]]][x][y]);
			}
		}
		times -= 2;
	}
	return;
}

int main() {
	n = read();
	for (int i = n + 1; i < n << 1; i++) {
		lson[i - n] = ord(read());
		rson[i - n] = ord(read());
	}
	for (int i = 1; i <= n; i++) {
		a[i] = read();
		b[i] = read();
		c[i] = read();
	}
	dfs(n + 1, 0, 0);
	printf("%lld", dp[1][0][0]);
	return 0;
}
```


---

## 作者：xuhanxi_dada117 (赞：1)

（原题太离谱了，不放传送门了）。

# 题目分析

乍一看：我去什么鬼？？

其实很简单。

注意这句话：

> 对于每一个城市，恰有一条公路和一条铁路通向这座城市。对于城市 
i， 通向该城市的道路（公路或铁路）的起点，要么是一个乡村，要么是一个编号比 
i 大的城市。

这证明了什么？

+ **原树是一课二叉树！**

+ 乡村为根节点。（要存成整数！）

再看题目：

> 小 W 决定对每个城市翻修恰好一条通向它的道路。

相当于修一条边（左或右）。

再联系其他条件不难看出题意。

好的，题目大意大概知道了，可以做题了。

# 解法

考虑 DP ：$dp[u][x][y]$ 代表从 $u$ 到首都 $1$ 中，修 $x$ 条左儿子，$y$ 条右儿子的不方便度。

$ans=dp[1][0][0]$。

递推式：

```cpp
long long tmp1=0,tmp2=0;
			if(lf[p]>=n) tmp1+=F(lf[p],x,y);
			else tmp1+=dp[lf[p]][x][y];
			if(rf[p]>=n) tmp1+=F(rf[p],x,y+1);
			else tmp1+=dp[rf[p]][x][y+1];
			if(lf[p]>=n) tmp2+=F(lf[p],x+1,y);
			else tmp2+=dp[lf[p]][x+1][y];
			if(rf[p]>=n) tmp2+=F(rf[p],x,y);
			else tmp2+=dp[rf[p]][x][y];
			dp[p][x][y]=min(tmp1,tmp2);
```

其中 $F(p,x,y)$ 为特判叶节点（会卡空间！）。

时间复杂度 $\Theta(N\times 40\times 40)$。

代码：

```cpp
#include<bits/stdc++.h>
#define N 40010
using namespace std;
long long n,lf[N],rf[N],a[N],b[N],c[N];//一定long long
long long dp[N/2][50][50]={};
long long F(int p,int x,int y){
	return c[p-n+1]*(a[p-n+1]+x)*(b[p-n+1]+y);
}
void dfs(int p){
	if(p>=n) return;
	dfs(lf[p]);dfs(rf[p]);
	for(int x=0;x<=40;++x){
		for(int y=0;y<=40;++y){
			long long tmp1=0,tmp2=0;
			if(lf[p]>=n) tmp1+=F(lf[p],x,y);
			else tmp1+=dp[lf[p]][x][y];
			if(rf[p]>=n) tmp1+=F(rf[p],x,y+1);
			else tmp1+=dp[rf[p]][x][y+1];
			if(lf[p]>=n) tmp2+=F(lf[p],x+1,y);
			else tmp2+=dp[lf[p]][x+1][y];
			if(rf[p]>=n) tmp2+=F(rf[p],x,y);
			else tmp2+=dp[rf[p]][x][y];
			dp[p][x][y]=min(tmp1,tmp2);
		}
	}
}
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n-1;++i){
		cin>>lf[i]>>rf[i];
		if(lf[i]<0) lf[i]=-lf[i]+n-1;
		if(rf[i]<0) rf[i]=-rf[i]+n-1;
	}
	for(int i=1;i<=n;++i) cin>>a[i]>>b[i]>>c[i];
	dfs(1);
	cout<<dp[1][0][0];
	return 0;
}
```

完结撒花~~

---

## 作者：AzusaShirasu (赞：1)

依据题意，所有的城市节点都是**非叶节点**、所有的村庄都是**叶节点**。且每个非叶节点（即城市）最多只有 $2$ 个子节点（即村庄或城市）。这就是一棵二叉树。

依照这个性质，对所有节点**重新**进行编号。按输入的顺序，所有城市编号不变，为从 $1$ 到 $n-1$；所有村庄编号在原基础上加 $n$，变为从 $n$ 到 $2n$。这样一来，判断当前节点是否为村庄只需要看编号是否大于等于 $n$ 即可。

题目中要求修复的公路或铁路数量不超过 $n-1$，这一点其实不需要过多考虑——对于每个城市，只修复连接左子节点的边或右子节点的边。这样一来，每个城市**只修一条路**，因此修的边总数就是城市数 $n-1$。

理清了思路，接着设计状态。用三元组 $(v, x, y)$ 表示节点 $v$ 到根节点的路径中，有 $x$ 条**未修复**的公路和 $y$ 条未修复的铁路。记 $v$ 的左子节点为 $v_L$、右子节点为 $v_R$，则可能的状态转移如下：

$$
(v, x, y)
\rightarrow
\begin{cases}
(v_L, x,y)+(v_R,x,y+1)  && \text{(修左边)}\\
(v_L, x+1,y)+(v_R,x,y)  && \text{(修右边)}\\
\end{cases}
$$

边界就是到达了村庄，即 $v \geq n$：
$$
(v, x, y)
\rightarrow
c_v \cdot (a_v+x) \cdot(b_v+y)
$$

至此，本题已经基本分析完毕了。需要注意的是，答案需要开 $\mathtt{\text{long long}}$。此外还有一些小细节，见代码：

```
#include <cstdio>
#include <cstring>

const int maxn = 20000 + 5;
const long long inf = 0x3f3f3f3f3f3f3f3f; // long long 的 INF 要写 8 个 3f 

int n;
int son[maxn][2]; // son[0] 左子节点 son[1] 右子节点 
long long f[maxn][40 + 2][40 + 2];
long long a[maxn], b[maxn], c[maxn];

#define vlg(x) ((x) - n + 1) // 输入转化为村庄编号 

long long min(long long & x, long long & y) {
	return x < y ? x : y;
}

long long dp(int v, int x, int y) {
	if(v >= n) { // 边界 
		return c[vlg(v)] * (a[vlg(v)] + x) * (b[vlg(v)] + y); 
	}
	else {
		if(f[v][x][y] < inf) return f[v][x][y];
		long long l = dp(son[v][0], x, y) + dp(son[v][1], x, y + 1); // 修左边
		long long r = dp(son[v][0], x + 1, y) + dp(son[v][1], x, y); // 修右边 
		return f[v][x][y] = min(l, r);
	}
}

int main() {
	int x, y;
	memset(f, 0x3f, sizeof(f));
	scanf("%d", &n);
	for(int i = 1; i <= n - 1; i++) {
		scanf("%d%d", &x, &y);
		if(x >= 0) son[i][0] = x;
		else son[i][0] = -vlg(x); // 注意负数必须转化为正数 
		
		if(y >= 0) son[i][1] = y;
		else son[i][1] = -vlg(y);
	}
	for(int i = 1; i <= n; i++) {
		scanf("%lld%lld%lld", &a[i], &b[i], &c[i]);
	}
	printf("%lld", dp(1, 0, 0));
	return 0;
}
```




---

## 作者：Aw顿顿 (赞：1)

题目真的很阅读理解……这里给出简化版的题意。

## 题意

给定一颗二叉树，每个叶子结点均有参数 $(a_i,b_i,c_i)$，而每个非叶子结点可以对于连通其左右儿子的边进行修缮，一共能够修缮 $n-1$ 条边。

对于每个叶子结点 $x$，在其到根节点的路径上，若有 $x$ 条左边未被修缮，$y$ 条右边未被修缮，则其权重为：

$$c_i(a_i+x)(b_i+y)$$

求问最小的权值和是多少？

## 解法

我们显然要用 DP，首先需要两维的状态表示左边和右边。那我们可以从叶子结点向上进行推演，设计状态如：

- $f(x,i,j)$ 表示从根到 $x$ 有 $i$ 个左边和 $j$ 个右边未被修缮。
- 若 $f(x,i,j)$ 是叶子结点，直接计算 $c_x(a_x+i)(b_x+j)$。
- 反之，则分类讨论是公路还是铁路。

那么状态转移方程就是：

$$f(x,i,j)=\begin{cases}c_x(a_x+i)(b_x+j)\\\min\big\{f(l,i,j)+f(r,i,j+1),f(l,i+1,j)+f(r,i,j)\big\}\end{cases}$$

这个东西带着 $\texttt{DFS}$ 实现一下难度不大，注意点：

- 适当的时候需要开 $\texttt{long long}$。
- 注意使用的内存空间。





---

## 作者：_Yoimiya_ (赞：1)

[题目传送门。](https://www.luogu.com.cn/problem/P4438)

解题思路:
- 一眼树形 DP。先定个状态，设 $f[k][i][j]$ 表示从根结点到结点 $k$ 经过 $i$ 条未翻修公路，$j$ 条未翻修铁路的贡献最小值。  

- 然后推状态转移。在本题的 DFS 时要先处理叶子（乡村）的初始值，即：$f[k][i][j] = c[k]\times(a[k]+i)\times(b[k]+j) $。

- 考虑非叶节点（城市）。无论是翻修哪一种路，都会多出另一种路没有被翻修（~~废话~~）。所以，状态转移为：  

- $ f[k][i][j] = \min ^{f[lson][i][j]+f[rson][i][j+1]}_{f[lson][i+1][j]+f[rson][i][j]}$

- 其他就可以直接套树形 DP 板子。值得一提的是，尽量不要开```#define int long long ```，本人因为开了这个调了很久的样例。

AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int M(2e5+1);
#define rg register int
struct node{
	int to,next;
};node t[M<<1];
int n,m,siz[M],idx,head[M<<1];
long long f[110][50][50];
int a[M],b[M],c[M],dep[M];
vector<int> v[M];
inline int read(){
	register int X(0); bool flag(1); char ch(getchar());
	while(ch<'0'||ch>'9') {if(ch=='-') flag=0; ch=getchar();}
	while(ch>='0'&&ch<='9') {X=(X<<1)+(X<<3)+ch-'0'; ch=getchar();}
	if(flag) return X;
	return ~(X-1);
}
inline void add(int u,int w){t[++idx]=(node){w,head[u]};head[u]=idx;}
inline void dfs(int x,int k) {
	siz[x]=1;
	for(rg i(head[x]);i;i=t[i].next){
		int y(t[i].to);
		dep[y]=dep[x]+1;v[x].push_back(y);
		if(!v[x][1]) dfs(y,k+1);else dfs(y,k+2);
		siz[x]+=siz[y];
	}
	if(siz[x]==1){
		for(rg i(0);i<=dep[x];++i)
			for(rg j(0);j<=dep[x];++j)
				f[k][i][j]=1ll*c[x]*(a[x]+i)*(b[x]+j);
	}
	else{
		for(rg i(0);i<=dep[x];++i)
			for(rg j(0);j<=dep[x];++j)
				f[k][i][j]=min(f[k+1][i+1][j]+f[k+2][i][j],f[k+1][i][j]+f[k+2][i][j+1]);
	}
	return;
}
signed main(){
	n=read();
	memset(f,0x3f,sizeof f);
	for(rg i(1);i<n;++i){
		int u(read()),w(read());
		add(i,w<0?n-w-1:w);add(i,u<0?n-u-1:u);
	}
	for(rg i(n);i<n*2;++i) cin>>a[i]>>b[i]>>c[i];
	dfs(1,0);cout<<f[0][0][0];return 0;
}
```

---

## 作者：Biscuit46 (赞：1)

# BZOJ5290 [Hnoi2018]道路

------

## 前言

这道题目我竟然没有在去年省选切?  

我太菜了.  



## Solution

对题面进行一个语文透彻解析,发现这是一个二叉树,乡村都是叶子节点,城市都有两个儿子.(依据在下)

[![k0iDpt.md.png](https://s2.ax1x.com/2019/02/13/k0iDpt.md.png)](https://imgchr.com/i/k0iDpt)



那么就可以树形dp了.我们假设公路是左儿子,铁路是右儿子.

$dp_{i,j,k}$表示到了$i$节点,经过了$j$条未翻修的公路,经过了$k$条未翻修的铁路.

考虑对于不同的$i$怎么计算.

1. 叶子节点,直接计算贡献即可.  
2. 非叶子节点,考虑要么不翻修公路,要么不翻修铁路,直接从左右儿子的两种情况转移就好了.

具体的转移方程参考代码.



## 代码实现

```cpp
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<queue>
#include<set>
#include<map>
#include<iostream>
using namespace std;
#define ll long long
#define re register
#define file(a) freopen(a".in","r",stdin);freopen(a".out","w",stdout)
inline int gi()
{
	int f=1,sum=0;char ch=getchar();
	while(ch>'9' || ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
	return f*sum;
}
const int N=40010;
ll dp[510][41][41];
int son[N][2],c[N<<1],b[N<<1],a[N<<1],n,id[N<<1],sta[N<<1],tot,top;
void dfs(int u,int x,int y)
{
	int p=id[u]=top?sta[top--]:++tot;
	if(!son[u][0])
	{
		for(int i=0;i<=x;i++)
			for(int j=0;j<=y;j++)
				dp[p][i][j]=1ll*c[u]*(a[u]+i)*(b[u]+j);
		return;
	}
	dfs(son[u][0],x+1,y);dfs(son[u][1],x,y+1);
	int ls=id[son[u][0]],rs=id[son[u][1]];
	for(int i=0;i<=x;i++)
		for(int j=0;j<=y;j++)
			dp[p][i][j]=min(dp[ls][i][j]+dp[rs][i][j+1],dp[ls][i+1][j]+dp[rs][i][j]);
	sta[++top]=ls;sta[++top]=rs;//重复利用了.
}
int main()
{
	n=gi();
	for(int i=1;i<n;i++)
	{
		int s=gi(),t=gi();
		if(s<0)s=-s+n-1;
		if(t<0)t=-t+n-1;
		son[i][0]=s;son[i][1]=t;
	}
	for(int i=n;i<=n+n-1;i++)
		a[i]=gi(),b[i]=gi(),c[i]=gi();
	dfs(1,0,0);
	printf("%lld\n",dp[1][0][0]);
	return 0;
}
```



---

