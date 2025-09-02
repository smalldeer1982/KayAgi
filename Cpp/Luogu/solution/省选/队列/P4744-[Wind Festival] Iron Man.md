# [Wind Festival] Iron Man

## 题目背景

[Midnight - 23:59]

在风筝节上交到了老铁(并不是 Nishikino)，接触了 OI，gyx 全身的热情都被点燃啦！！为了更好地参与到下一届风筝节的工作中去，gyx 准备开始为期一年的学习。


## 题目描述

gyx 想用全部的时间学(tui)OI(fei)!!!

gyx 为了合理的利用所有时间学 OI，他开始规划自己的学习计划。

首先，gyx 的眼里每年有 $n$ 天，因为 gyx 实在是太想学习啦，所以他并没有留下玩耍的时间（每天都全部用来学 OI 或者文化课），gyx 划分天数的原则是，在每一天中，gyx 对 OI 的感兴趣程度相同。但是，未免 gyx 也会因生活琐事而没法静心学习，所以某些天 gyx 对 OI 的兴趣程度有可能是负的。

然后，gyx 开始安排学习 OI 的时间，gyx 统计出他要学习的OI 知识有 $k$ 种。因为 gyx 是一个追求完美的人，他认为对于每一种 OI 知识，知识体系的完整性是必要的，某一个部分的 OI 知识学习过程中一旦停下来会影响自己的学习效果，所以他会用连续的一些天来学习一个部分的知识，期间不能停下来学习文化课，也不会穿插着进行几种知识的学习。

但是注意，gyx 在进行每部分 OI 知识的学习之间可以留出一些时间段用来学文化课。并且，gyx 并不介意各个部分 OI 知识间学习的顺序，因为他对每一部分的 OI 知识兴趣程度是相同的。

现在，gyx 想知道他总共用于学 OI 的日子兴趣值之和是多少，因为 gyx 还没有学习过高级的规划算法，所以 gyx 将他学习计划的规划交给你，你可以选择任意一个小于等于 $n$ 的一个正整数 $i$，使他从第 $i$ 天开始，进行长 $n$ 天的学习（不一定一开始就必须学 OI），但在这一年中他一定要把清单中所有的知识都学完，gyx 相信你一定能给出兴趣值之和最高的方法。



## 说明/提示

### 样例解释

从第 $3$ 个时间段开始学习，那么他学 OI 的这一年兴趣程度的序列便为：

- $[3,-1,2,3,2,-4]$。

用于学习两个知识的时间段分别是新序列的第 $1$ 个和第 $3,4,5$ 个，于是 $ans=3+(2+3+2)=10$。

### 数据范围

- 对于 $10\%$ 的数据，满足 $k=1$；
- 对于另 $30\%$ 的数据，满足 $k=2$；
- 对于$100\%$ 的数据，满足：$1\le k\le50$，$k\le n\le10^5$，$|a_i|\le 10^4$。

## 样例 #1

### 输入

```
6 2
2 -4 3 -1 2 3
```

### 输出

```
10```

# 题解

## 作者：WinXP (赞：6)

~~我又来写毒瘤题解啦~~

我们一看这题，哇，我会网络流！

网络流:~~什么鬼？管我什么事？~~

考虑建出这样一个图。

![](https://cdn.luogu.com.cn/upload/pic/22894.png )

~~毒瘤思路毒瘤图~~

具体来说就是由 $S$ 向一个点连费用为 $0$ 流量为 $k$ 的边。再由这个点向所有点连一条费用为 $0$ 流量为 $1$ 的边。由所有的点向他的下一个点连边，流量为 $1$ ，费用为 $a_i$ 。再由所有的点向 $T$ 连边，流量为 $1$ 费用为 $0$，跑最大费用最大流。

这样相当于我们完全模拟出了选 $k$ 次的过程，而决策交给算法。别急着写，这个范围显然不是网络流的范围(我也不知道能不能大力跑过)，能不能考虑手动模拟网络流的决策?

如果当 $k$ 为 $1$ 的时候，我们可以知道这个做法就是在求出最长链。取完这条链出来之后，考虑将这条链上的所有点取反。在下一次的过程中，如果选出的第二条链与第一条链没有交集，这个显然是对的；如果选出的第二条链与第一条链包含或者被包含，相当于我们贪心反悔，把更大的链分割成两条链来选；不过如果选出的链与第一条链有交集而且不包含，就会出问题，因为网络流中退流的过程保证这种选法是不合法的。  

而这种选法不会出现。

![](https://cdn.luogu.com.cn/upload/pic/22895.png )

对于这种情况，我们设这三条链的编号为 $1,2,3$ ，具体如上图。设 $2$ 号链如果是后选出来的链，根据决策我们知道 $2$ 号链是最长链；既然 $2$ 号链是最长链则 $3$ 号链现在的值显然大于 $0$ ，否则不能选；因为 $3$ 号链现在的值大于 $0$，说明在选 $1$ 号链的时候， $3$ 号链的值小于 $0$ ，才能被取反成大于 $0$ 的链；但是选 $1$ 号链也是最长链，不可能把值为负的 $3$ 号链包含在内。所以这种情况是不合法的。

然后就可以开心敲代码了---吗?

有一个小问题。如果 $k$ 比正数的个数少，我们知道必须要多选出一些最小的负数出来才能满足题意。而网络流的做法是默认每次选中的链大于 $0$ ，因为如果小于 $0$ 直接就流进 $T$ 了。对于这种情况需要特判。

顺便说一下如何求最长链：链长度翻一倍模拟环拆链，对于每个点维护前缀和，对于每一个点 $i$ 计 $P_i$ 为它的前缀和，即为求 $P_i-min(P_j)\quad (j<i)$，维护这个过程可以用单调队列实现。  
不过话说dp好像也要用单调队列优化一下。


然后就可以开心敲代码啦~

```cpp
#include <bits/stdc++.h>
#define rap(i,s,n) for(int i=s;i<=n;i++)
#define drap(i,n,s) for(int i=n;i>=s;i--)
#define N 210000
#define inf 0x3f3f3f3f
#define ll long long
#define m(s,k) memset(s,k,sizeof s)
using namespace std;
char xB[1<<15],*xS=xB,*xTT=xB;
#define getc() (xS==xTT&&(xTT=(xS=xB)+fread(xB,1,1<<15,stdin),xS==xTT)?0:*xS++)
#define isd(c) ((c>='0'&&c<='9')||(c=='-'))
template<typename T>
inline bool rd(T& xa){
    char xchh; T f=1; while(xchh=getc(),(!isd(xchh))&&(xchh!=0));
    if(xchh==0) return 0; if(xchh=='-') xchh=getc(),f=-1; xa=xchh-'0';
    while(xchh=getc(),isd(xchh)) xa=xa*10+xchh-'0'; xa*=f; return 1;
}
int n,k,a[N],pre[N],ans;
struct mqueue{
	//单调队列
    int g[N],t[N],r,l;
    void init(){r=0,l=1;}
    void in(int x,int xt){while(r>=l&&g[r]>=x) r--; g[++r]=x,t[r]=xt;}
    int tmin(){return t[l];} int gmin(){return g[l];}
    void push(int xt){while(l<=r&&t[l]<=xt) l++;}
}q;
int main(){
    rd(n); rd(k); rap(i,1,n) rd(a[i]); 
    int dk=0; rap(i,1,n) if(a[i]>0) dk++; if(dk<=k){
        sort(a+1,a+n+1); drap(i,n,1){
            if(k==0) break; ans+=a[i]; k--;
        }
        printf("%d\n",ans); return 0;
        //特判
    }
    while(k--){
        q.init(); int maxv=-inf,maxt=0,fx;
        rap(i,1,n) a[i+n]=a[i],pre[i]=a[i]+pre[i-1],q.in(pre[i],i);
        rap(i,n+1,2*n){
            pre[i]=a[i]+pre[i-1];
            if(maxv<pre[i]-q.gmin()) maxv=pre[i]-q.gmin(),maxt=i,fx=q.tmin();
            q.in(pre[i],i); q.push(i-n);
        }
        //求出最长链 我为了方便写求的是左开右闭..
        if(maxt==0) return 0; ans+=maxv;
        rap(i,fx,maxt-1) a[i%n+1]=-a[i%n+1];
    }
    printf("%d\n",ans);
    return 0;
}

```

---

## 作者：zhoutb2333 (赞：5)

我的思路好像和大家都不太一样啊...首先$k$段要么是纯粹的$k$段，要么是$k+1$段，并且第一段和最后一段贴开头和结尾。

就是设$f[i][j]$是前$i$个数选出$j$段的最大和（$i$不一定选）。

$g[i][j]$为前$i$个数选出$j$段的最大和，并且第一段贴开头（$i$不一定选）。

然后就列转移，发现记个前缀和就做完啦

（感觉哪里不对啊，有没有hack数据

``` cpp
#include<bits/stdc++.h>
#define maxn 100010
#define maxk 55
#define INF 1<<30
using namespace std;

int f[maxn][maxk],g[maxn][maxk],a[maxn],n,k,ans=-INF;
int mx;
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]),a[i]+=a[i-1];
    memset(f,0xcf,sizeof(f)),memset(g,0xcf,sizeof(g));
    f[0][0]=0;
    for(int j=0;j<=k;j++){
        mx=0;
        for(int i=1;i<=n;i++){
            if(j)
                f[i][j]=max(f[i][j],mx+a[i]);
            f[i][j]=max(f[i][j],f[i-1][j]);
            mx=max(mx,f[i][j-1]-a[i]);
        }
    }
    ans=f[n][k];
    for(int i=1;i<=n;i++)
        g[i][1]=max(a[i],g[i-1][1]);
    for(int j=2;j<=k;j++){
        mx=-INF;
        for(int i=1;i<=n;i++){
            g[i][j]=max(g[i][j],mx+a[i]);
            g[i][j]=max(g[i][j],g[i-1][j]);
            mx=max(mx,g[i][j-1]-a[i]);
        }
    }
    for(int i=1;i<=n;i++)
        ans=max(ans,g[i][k]+a[n]-a[i]);
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：chdy (赞：3)

我发一个正经的dp做法，无惧所有hack。

觉得题目很长对不对，简化题意 一个环形的数列求从其中k个连续子序列的和的最大值。

如何做这道题，~~其实我是看着网络流的标签来的~~。我也不会建模啊，我也不会建图啊。不过这道题的dp是很好写的。

我们先简化问题，把这个环形的变成一条链。

- 此时我们可以设状态 f[i][j][k] 表示到了第i个数字前面已经选择了j段当前数字选不选0/1 这个状态是必要的，因为包含了整个状态空间。

- 转移简单 但是注意不要忘记j==0时的转移比较特殊。。

接下来讨论环形，3种方法：

1. 暴力做n次dp 然后统计最优答案。

n过大了显然会T.

2. 破环成链在后面续上一段，然后转移取其中的一段。

续上一段其要求的是和前面没有什么影响我们这个状态一转移就是和前面i-1有关系所以也不行。

3. 两次dp，一次不连接，一次强制连接。

这个是可以的！可以强制选1和n 然后剩下的直接转移即可。 

~~小声bb一句双倍经验：p1121.~~

code:
```cpp
//#include<bits/stdc++.h>
#include<iostream>
#include<queue>
#include<iomanip>
#include<cctype>
#include<cstdio>
#include<deque>
#include<utility>
#include<cmath>
#include<ctime>
#include<cstring>
#include<string>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<stack>
#include<map>
#include<set>
#include<bitset>
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)>(y)?(y):(x))
#define INF 1000000000
#define ll long long
#define db double
using namespace std;
char buf[1<<15],*fs,*ft;
inline char getc()
{
    return (fs==ft&&(ft=(fs=buf)+fread(buf,1,1<<15,stdin),fs==ft))?0:*fs++;
}
inline int read()
{
	int x=0,f=1;char ch=getc();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getc();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getc();}
    return x*f;
}
inline void put(int x)
{
    x<0?putchar('-'),x=-x:0;
    int num=0;char ch[50];
    while(x)ch[++num]=x%10+'0',x/=10;
    num==0?putchar('0'):0;
    while(num)putchar(ch[num--]);
    putchar('\n');return;
}
const int MAXN=100010;
int n,k,maxx=-(INF<<1);
int a[MAXN];
int f[MAXN][60][2];//f[i][j][k]表示到了第i个数字选择了j段且当前数字选择了没有0/1
//两次dp 一次断开 一次强制连接
int main()
{
	//freopen("1.in","r",stdin);
	n=read();k=read();
	for(int i=1;i<=n;++i)a[i]=read();
	memset(f,0xcf,sizeof(f));
	f[0][0][1]=f[0][0][0]=0;
	for(int i=1;i<=n;++i)
		for(int j=0;j<=k;++j)
		{
			if(j>=1)f[i][j][1]=max(f[i][j][1],f[i-1][j-1][0]+a[i]);
			if(j>=1)f[i][j][1]=max(f[i][j][1],f[i-1][j-1][1]+a[i]);
			if(j>=1)f[i][j][1]=max(f[i][j][1],f[i-1][j][1]+a[i]);
			f[i][j][0]=max(f[i][j][0],f[i-1][j][1]);
			f[i][j][0]=max(f[i][j][0],f[i-1][j][0]);
		}
	maxx=max(f[n][k][0],f[n][k][1]);
	memset(f,0xcf,sizeof(f));
	f[1][0][1]=a[1];
	for(int i=2;i<=n;++i)
	{
		for(int j=0;j<=k;++j)
		{
			if(j>=1)f[i][j][1]=max(f[i][j][1],f[i-1][j-1][0]+a[i]);
			if(j>=1)f[i][j][1]=max(f[i][j][1],f[i-1][j-1][1]+a[i]);
			f[i][j][1]=max(f[i][j][1],f[i-1][j][1]+a[i]);
			f[i][j][0]=max(f[i][j][0],f[i-1][j][1]);
			f[i][j][0]=max(f[i][j][0],f[i-1][j][0]);
		}
	}
	maxx=max(maxx,f[n][k][1]);
	put(maxx);
	return 0;
}

```


---

## 作者：foreverlasting (赞：1)

说实话 这题还真的没想到题解里说的DP

主要题目思路来自于bzoj2288,其实做过bzoj2288的人就会发现这道题和那道题只差环的条件和必须选择k个的条件。

按照那道题的思路，先将同号且连续的一段整合在一段。因为这一段肯定会是整段选上，所以用一个小根堆去维护一样值就好了。然后用链表瞎搞一下就好了。

我就是在那道题的基础上加一个环和必须选择k个就水过去了......

代码就不给了，反正跟bzoj2288差不多。

---

## 作者：laorui (赞：1)

介绍一个贪心的算法

如果只选一个的话可以建一个堆维护一下前缀和然后乱搞就能搞出来

然后把被选的链全部取反当成一个新的链，和剩下的的链一起存进vector里

每次选链时直接在这些链里找最大的子链，和开始一样取反存成新的链，
原来的链被删除一个子链变成两个链，这三个都存到vector里，删掉之前的串，重复k-1次即可

取反是什么意思呢？列如我们先选了1~100这条链然后选了30~50这段反链，就相当于选了1~29和51~100这两条链，反串的反串以此类推就行

一个特判，这个方法好像没法处理负数，所以如果选最大的k天仍然<0就直接输出结果就行

时间复杂度O(nk)，~~不过我不会用vector~~，只能生开数组，空间卡的又比较死，只能打个标记，时间被卡成O(nk^2),不过也能过

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<queue>
using namespace std;
int a[100007][57];int n,k,aaa;
int f[100007][57],last[100007][57];//last是串的起始位置 
bool v[100007][57];int le[57],b[200007],sum[200007],c[200007];//v代表是否被选过 ,l代表串的长度 
struct node
{int data,num;};
bool operator < (const node &A,const node &b)
{return A.data>b.data;}
int main()
{
cin>>n>>k;
for(int i=1;i<=n;++i)
{
scanf("%d",&b[i]);
c[i]=b[i];
b[i+n]=b[i];}
sort(c+1,c+n+1);
int Ans=0;
for(int i=n;i>=n-k+1;--i)Ans+=c[i];
if(Ans<0){cout<<Ans;return 0;}//特判是否必须小于0 
int mmm=0,kkk=0,lll=0;
for(int i=1;i<=n*2;++i)sum[i]=sum[i-1]+b[i];
priority_queue<node>heap;
node orz;orz.num=0;orz.data=0;
heap.push(orz);
for(int i=1;i<=n*2;++i)
{
node x=heap.top();
while(i-x.num>n)
{
heap.pop();
x=heap.top();
}
if(sum[i]-x.data>mmm)
{
mmm=sum[i]-x.data;
kkk=i;lll=x.num+1;
}
x.data=sum[i];x.num=i;
heap.push(x);
}
le[1]=n-(kkk-lll+1);
aaa+=mmm;
for(int i=1;i<=(kkk-lll+1);++i)
{
a[i][2]=-b[lll+i-1];}
le[2]=kkk-lll+1;
for(int i=1;i<=le[1];++i)
{
a[i][1]=b[(kkk+i-1)%(n*2)+1];}
for(int w=2;w<=k;++w)
{
int maxn=-0x3f3f3f3f,x=0,y=0;
for(int j=1;j<=w;++j)
{
for(int i=1;i<=le[j];++i)
{
if(v[i][j]==1)continue;
if(v[i-1][j]==0&&f[i-1][j]>0)
{
f[i][j]=f[i-1][j]+a[i][j];
last[i][j]=last[i-1][j];
}
else
{
f[i][j]=a[i][j];
last[i][j]=i;}
if(f[i][j]>maxn){maxn=f[i][j];x=i;y=j;}
}}
aaa+=maxn;
int d=0;
le[w+1]=x-last[x][y]+1;
for(int i=last[x][y];i<=x;++i)
{
++d;
a[d][w+1]=-a[i][y];
v[i][y]=1;}
}
printf("%d",aaa);
return 0;
}
```

---

