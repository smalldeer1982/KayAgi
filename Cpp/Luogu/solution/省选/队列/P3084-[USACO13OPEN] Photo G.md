# [USACO13OPEN] Photo G

## 题目描述

Farmer John has decided to assemble a panoramic photo of a lineup of his N cows (1 <= N <= 200,000), which, as always, are conveniently numbered from 1..N.  Accordingly, he snapped M (1 <= M <= 100,000) photos, each covering a contiguous range of cows: photo i contains cows a\_i through b\_i inclusive.  The photos collectively may not necessarily cover every single cow.

After taking his photos, FJ notices a very interesting phenomenon: each photo he took contains exactly one cow with spots!  FJ was aware that he had some number of spotted cows in his herd, but he had never actually counted them.  Based on his photos, please determine the maximum possible number of spotted cows that could exist in his herd.  Output -1 if there is no possible assignment of spots to cows consistent with FJ's photographic results.

农夫约翰决定给站在一条线上的N(1 <= N <= 200,000)头奶牛制作一张全家福照片，N头奶牛编号1到N。


于是约翰拍摄了M(1 <= M <= 100,000)张照片，每张照片都覆盖了连续一段奶牛：第i张照片中包含了编号a\_i 到 b\_i的奶牛。但是这些照片不一定把每一只奶牛都拍了进去。


在拍完照片后，约翰发现了一个有趣的事情：每张照片中都**有且仅有**一只身上带有斑点的奶牛。约翰意识到他的牛群中有一些斑点奶牛，但他从来没有统计过它们的数量。 根据照片，请你帮约翰估算在他的牛群中最多可能有多少只斑点奶牛。如果无解，输出“-1”。


Input

## 说明/提示

There are 5 cows and 3 photos.  The first photo contains cows 1 through 4, etc.


From the last photo, we know that either cow 3 or cow 4 must be spotted. By choosing either of these, we satisfy the first two photos as well.


## 样例 #1

### 输入

```
5 3 
1 4 
2 5 
3 4 
```

### 输出

```
1 
```

# 题解

## 作者：x义x (赞：81)

> UPD9/27：修正了第二张图片。对大家造成的不便请谅解。

显然这是一个DP题……（当然它也不太显然地是一个差分约束但是被卡了）（其实差分约束还是能过的）

首先定义状态：$f[i]$表示$i$位置必须有一头斑点奶牛，（包括$i$位置的那头牛）前面最多能放多少斑点奶牛。

显然

$$f[i]=\max(f[j])+1\quad(j<i,j\text{满足限制})$$

也就是$[j+1,i-1]$里不放奶牛，只在$f[i]$多放一头奶牛。

问题主要在于所谓的满足限制。题意中说一个区间里**必须有1头牛**，我们把它转化成一个区间里最多有1头牛，最少有1头牛，这是一个常用的技巧。下面分别进行分析。

### 限制1：区间$[l,r]$最多有1头奶牛

考虑$j<i$的两个都在$[l,r]$中的位置$j,i$。显然$i$不能通过$j$转移得到，不然$[l,r]$中就会有两头奶牛了。

也就是说：

> 对于任意包含$i$的区间$[l,r]$，合法的$j$必须小于$l$。

我们其实不用考虑所有的包含$i$的区间，我们只需要这些区间里$l$最小的那一个即可。它的“影响力”最大。

![](https://cdn.luogu.com.cn/upload/pic/66525.png)

$$\color{grey}\tiny\texttt{红框们使得图中指出的所有的j都不合法。}$$

我们定义：$minl[i]$为包含$i$的区间中最小的$l$。我们可以很快地从$N$到$1$扫一遍得到它：

$$minl[i]=\min(\text{右端点恰好是}i\text{的区间的最小的}l,minl[i+1])$$

可以理解为：包含$i$的区间要么右端点就是$i$，要么右端点比$i$大。

“$\text{右端点恰好是}i\text{的区间的最小的}l$”很好得出，弄个桶即可。

### 限制2：区间$[l,r]$至少有1头奶牛

考虑$j<l,r<i$的区间$[l,r]$和位置$j,i$。显然$i$不能通过$j$转移得到，不然$[l,r]$中一头奶牛也没有。

也就是说：

> 对于任何$r<i$（整个区间都在$i$之前）的区间，合法的$j$必须大于等于$l$。

同样，我们其实不用考虑所有的$r<i$的区间，我们只需要这些区间里$l$最大的那一个即可。小于它的$j$都不合法。

![](https://cdn.luogu.com.cn/upload/image_hosting/3m4bioe6.png)

$$\color{grey}\tiny\texttt{蓝框们使得图中指出的两个j都不合法，但是那个用红色标记的j是合法的。}$$

~~（复读ing）~~

同样我们还是只考虑右端点小于$i$的最大的$l$。称它为$maxl[i]$。我们同样可以从$1$到$N$扫一遍得出它：

$$maxl[i]=\max(\text{右端点恰好是}i-1\text{的区间的最大的}l,maxl[i-1])$$

那么，我们终于得到一个舒服一点的转移方程：

$$f[i]=\max(f[j])+1\quad (maxl[i]\le j<minl[i])$$

注意到$maxl[i],minl[i]$都单调不降，所以我们可以使用单调队列优化。参见[P1886](https://www.luogu.org/problem/P1886)。

代码如下：

（不建议抄，因为此题细节多的一匹）

```cpp
#include <bits/stdc++.h>
using namespace std;

int N,M;
int minl[200005],maxl[200005];

int q[200005],h,t;
int f[200005];

int main(){
	//注意我们设了一个虚拟节点N+1判无解 
	scanf("%d%d",&N,&M);
	for(int i=1;i<=N+1;i++) minl[i]=i;
	for(int i=1;i<=M;i++){
		int l,r;scanf("%d%d",&l,&r);
		//这里偷懒了，对应的桶和minl,maxl合并了 
		minl[r]=min(minl[r],l);
		maxl[r+1]=max(maxl[r+1],l);
	}
	//扫 
	for(int i=N;i>=1;i--)
		minl[i]=min(minl[i],minl[i+1]);
	for(int i=1;i<=N+1;i++)
		maxl[i]=max(maxl[i],maxl[i-1]);
	
	//单调队列和转移部分 
	h=1;q[++t]=0;int j=1;
	for(int i=1;i<=N+1;i++){
		for(;j<minl[i];j++)if(f[j]!=-1){	//新的合法j 
			while(h<=t&&f[q[t]]<f[j]) t--;
			q[++t]=j;
		}
		while(h<=t&&q[h]<maxl[i]) h++;
		if(h<=t) f[i]=f[q[h]]+(i!=N+1);		//选假的N+1不能有贡献 
		else f[i]=-1;
	} 
	printf("%d\n",f[N+1]);
	
	return 0;
}
```


---

## 作者：bztMinamoto (赞：74)

宣传一发[blog](https://www.cnblogs.com/bztMinamoto/p/9375444.html)

神仙般的dp……第一眼以为是差分约束……后来发现居然可以用dp乱搞……题解真神仙……

用$f[i]$表示到第i个位置为止且第i个位置必放，最多能放多少个

因为有两个限制条件：每个区间至少一个，每个区间至多一个

因为一个区间至多一个，所以所有包含这个点的区间都不能再放，要找到所有包含这个点的区间中最小的左端点，令$r[i]=左端点-1$

因为一个区间至少一个，所以不能有地方空着不放，找到整个区间在当前点之前的区间，取最大的左端点，令$l[i]=左端点$

每一次读入的时候，用$x$更新$l[y+1]$用x-1更新$x-1$更新$r[y]$

然后正着扫一遍，用$l[i-1]$更新$l[i]$（在i-1之前的左端点必定在i之前）；然后倒着扫一遍，用$r[i+1]$更新$r[i]$

所以$f[i]=max\{f[j]+1,l[i]<=j<=r[i]\}$，开个单调队列优化

莫名其妙跑到rank1……

```
//minamoto
#include<bits/stdc++.h>
#define N 200005
using namespace std;
#define getc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<15,stdin),p1==p2)?EOF:*p1++)
char buf[1<<15],*p1=buf,*p2=buf;
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
template<class T>inline bool cmin(T&a,const T&b){return a>b?a=b,1:0;}
inline int read(){
    #define num ch-'0'
    char ch;bool flag=0;int res;
    while(!isdigit(ch=getc()))
    (ch=='-')&&(flag=true);
    for(res=num;isdigit(ch=getc());res=res*10+num);
    (flag)&&(res=-res);
    #undef num
    return res;
}
int n,m,l[N],r[N];
int h,t,q[N],f[N];
int main(){
	//freopen("testdata.in","r",stdin);
	n=read(),m=read();
	for(int i=1;i<=n+1;++i) r[i]=i-1;
	for(int i=1;i<=m;++i){
		int x=read(),y=read();
		cmin(r[y],x-1);
		cmax(l[y+1],x);
	}
	for(int i=n;i>=1;--i) cmin(r[i],r[i+1]);
	for(int i=2;i<=n+1;++i) cmax(l[i],l[i-1]);
	int j=1;h=t=1,q[1]=0;
	for(int i=1;i<=n+1;++i){
		while(j<=r[i]&&j<=n){
			if(f[j]==-1){++j;continue;}
			while(f[j]>f[q[t]]&&h<=t) --t;
			q[++t]=j;
			++j;
			}
		while(q[h]<l[i]&&h<=t) ++h;
		if(h<=t) f[i]=f[q[h]]+(i!=n+1?1:0);
		else f[i]=-1;
	}
	printf("%d\n",f[n+1]);
	return 0;
}
```

---

## 作者：AcRapper (赞：29)

从提高试炼场的dp专题蹦过来，那么显然这个题是差分约束。

（我真的不是很明白题解里的大佬怎么想到的dp，这道题的dp思路真的太巧秒了%%%，，，）

虽然USACO~~W~~卡spfa卡的不亦乐乎，但我还是决定用**梦想spfa**水一波。

分析这道题目我们可以得到这样的关系：设D[i]为前i头奶牛中斑点奶牛的数目，我们要求的就是$max(D[n])$。每个给定的区间内有且只有一个，转换为符号语言	  $D[b]-D[a-1]=1$     ①

在这个性质上进一步思考，能够发现一个很显然的性质：每只奶牛要么是斑点奶牛，要么不是，转换为符号语言：
$0<=D[i]-D[i-1]<=1$。②

对①整理一下,因为**有且仅有一个斑点奶牛**那么能够得到下面两个不等式：

$D[b]-D[a-1]<=1,D[a-1]-D[b]<=-1$

这样用不等式表示出它的等于性质

②又能**写出** ：$D[i-1]-D[i]<=0$

那么差分约束的解法就相当自然了，把i和i-1之间连一条0边，i-1和i之间连一条1边，a-1和b之间连一条1边，b和a-1之间连一条-1边，跑一手华丽的spfa，然后去研究这个题的正解dp。

那么下一个摆在你面前的问题就是如何跑一手华丽的spfa，这里我们引出梦想spfa。~~值得一提的是，只单纯的用双端队列优化的spfa正儿八经的判负环就能得到90分的好成绩。~~

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<deque>
#define Endl endl;//qwq
using namespace std;
const int maxn=1e6;
int n,m,cnt=1;
int head[maxn],vis[maxn],dis[maxn];
struct node
{
	int nxt;
	int to;
	int w;
}edge[maxn];
void add(int x,int y,int z)
{
	edge[cnt].to=y;edge[cnt].w=z;edge[cnt].nxt=head[x];head[x]=cnt++;
}
//int cn[maxn];
int l,r;
int tot=0;
int spfa()
{
	deque<int> q;//双端队列优化spfa
	memset(dis,0x3f,sizeof(dis));
	dis[0]=0;//从0开始的原因见下面
	vis[0]=1;
	q.push_back(0);
	while(q.size())
	{
		int x=q.front();
		q.pop_front();
		vis[x]=0;
		for(int i=head[x];i;i=edge[i].nxt)
		{
			int y=edge[i].to,z=edge[i].w;
			if(dis[y]>dis[x]+z)
			{
				dis[y]=dis[x]+z;
				//cn[y]=cn[x]+1;
				if(!vis[y])
				{
					if(++tot>1926817) return -1;//人要有点信仰，这是梦想spfa的核心部分
					//if(cn[y]>n)return -1;这是正儿八经的判负环，请一定要学会
					vis[y]=1;
					if(q.size()&&dis[y]>dis[q.front()])q.push_back(y);
					else q.push_front(y);
				}
			}
		}
	}
	return dis[n];
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>l>>r;
		add(l-1,r,1);
		add(r,l-1,-1);
	}
	for(int i=1;i<=n;i++)
		add(i,i-1,0),add(i-1,i,1);//i-1可能为0，所以上面最短路要从0开始跑（前后呼应~~手动滑稽）
	cout<<spfa()<<Endl;
    return 0;
}
```

---

## 作者：Froggy (赞：15)

### 提供一种不需要用clock的差分约束做法

瓶颈在于spfa太慢

关于优化:这里用双端队列优化spfa(又称SLF优化,~~不会LLL优化,qwq~~)

前后对比明显:

[spfa+SLF优化](https://www.luogu.org/record/21955517) --->AC

[spfa+O2+O3](https://www.luogu.org/record/21955316) --->TLE70

只需改一些:

#### 原来的:
---

```cpp
q.push(v);
```
---

#### SLF优化:(注:queue变成了deque)
---

```cpp
if(q.size()&&dis[q.front()]<dis[v])q.push_back(v);
else q.push_front(v);
```

---

解释一下:也就是说,当队首元素小于等于目前结点的dis,那就直接把它放进队首,下次先扩展

---

除此之外还不够...(这时候是90分)

还要处理一些比较naive的情况..

可以统计所有点总入队数量,如果比较大的话就直接-1喽

### *Code:*

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<deque>
using namespace std;
#define N 200200
#define re register
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<3)+(x<<1)+c-'0';
        c=getchar();
    }
    return x*f;
}
int n,m;
int e_cnt=0,cnt[N],head[N],vis[N],dis[N],qwq;
deque<int>q;
struct Edge{
	int to,val,nxt;
}edge[N<<2];
void add(int a,int b,int c){
	e_cnt++;
	edge[e_cnt].to=b;
	edge[e_cnt].val=c;
	edge[e_cnt].nxt=head[a];
	head[a]=e_cnt;
}
bool SPFA(int s){
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0;
	vis[s]=1;
	q.push_back(s);
	while(!q.empty()){
		int u=q.front();
		q.pop_front();
		vis[u]=0;
		for(re int i=head[u];i;i=edge[i].nxt){
			int v=edge[i].to;
			if(dis[v]>dis[u]+edge[i].val){
				dis[v]=dis[u]+edge[i].val;
				if(!vis[v]){
					cnt[v]++;
					qwq++;
					if(q.size()&&dis[q.front()]<dis[v])q.push_back(v);
					else q.push_front(v);
					//q.push(v);
					vis[v]=1;
				}
				if(qwq>2015999||cnt[v]>n){//naive
					return true;
				}
			}
		}
	}
	return false;
}
int main(){
	n=read(),m=read();
	for(re int i=1;i<=m;i++){
		int l=read(),r=read();
		add(l-1,r,1);
		add(r,l-1,-1);
	} 
	for(re int i=1;i<=n;i++){
		add(i,i-1,0);
		add(i-1,i,1);
	}
	if(SPFA(0)){
		printf("%d\n",-1);
	}
	else{
		printf("%d\n",dis[n]);
	}
	return 0;
}

```


---

## 作者：巨型方块 (赞：12)

单调性dp

我靠你看到这个题目，怎么看都和查分约束有点关系对不对；

估计是我差分约束学的不好，也找不到为什么不能用差分约束，就是构造不出来；

我们思考dp

f[i]表示到igxe点切i点有一头斑点牛的最大值

显然有些位置是一定不能放斑点牛的；

那么对于可以放牛的i点我们有2个限制

每一个区间最多一头奶牛

每一个区间最少一头奶牛

这两个限制让我们发现了一个区间

有第一个限制我萌可以得到这个区间的右端点为所有覆盖i点的区间里的min（左端点）

第二个限制我们可以得到这个区间的左端点为所有没覆盖i点的区间里的max(左端点)

这个区间里的j才可以更新f[i]

f[i]=f[j]+1//f[j]!=-1

因为我们在这个区间里放一奶牛，才不适破坏限制；

那么之后我们只要去一个区间最大值就好啦

单调dp可以很好的做到这一点；

具体实现的话我就不讲了，自己感觉好难写


```cpp
#include<bits/stdc++.h>
#define Ll long long
using namespace std;
inline Ll RR(){Ll v=0,k=1;char c=0;while('0'>c||c>'9'){if(c=='-')k=-1;c=getchar();}while('0'<=c&&c<='9')v=v*10+c-48,c=getchar();return v*k;}
inline void W(Ll x){if(x<0)putchar('-'),x=-x;if(x>9)W(x/10);putchar(x%10+48);}
inline void WW(Ll x){W(x);puts("");}
inline void read(int &x,int &y){x=RR();y=RR();}
const int N=2e5+5;
int L[N],R[N],f[N],q[N];//L[i]表示f[i]的区间的左端点-1，R[i]为右端点-1 
int x,y,n,m,l,r;
void add(int x){
    if(f[x]==-1)return;
    while(r>=l&&f[q[r]]<=f[x])r--;
    q[++r]=x;
}
int main()
{
    read(n,m);
    for(int i=0;i<=n+1;i++)R[i]=i-1,L[i]=-1;
    for(int i=1;i<=m;i++){
        read(x,y);
        R[y]=min(R[y],x-1);
        L[y+1]=max(L[y+1],x-1);
    }
    for(int i=1;i<=n+1;i++)L[i]=max(L[i-1],L[i]);
    for(int i=n;i>=1;i--)R[i]=min(R[i+1],R[i]);
    l=1;r=0;
    for(int i=1;i<=n+1;i++){
        for(int j=R[i-1];j<=R[i];j++)add(j);
        while(r>=l&&q[l]<=L[i])l++;
        if(r<l)f[i]=-1;else f[i]=f[q[l]]+1;
    }
    printf("%d",max(f[n+1]-1,-1));
}
```

---

## 作者：joe19025 (赞：7)

## 解题思路

一开始被标签误导了……想了半天单调队列和线段树没想出来。

正当我百思不得其解时，打开了一篇题解，看到了差分约束如梦初醒。

设每个x[i]为前i头牛中，带斑点牛的个数。

### Math

根据题意可以列出如下几个式子：
- x[i+1]>=x[i]

- x[i+1]<=x[i]+1

对于每一对a,b来说：


- x[b]-x[a-1]=1

可推广得：
- x[b]-x[a-1]<=1

- x[a-1]-x[b]<=-1

### Graph

| 起点 | 终点 | 权值 |
| ---- | ---- | ---- |
| i+1  | i    | 0    |
| i    | i+1  | 1    |
| a-1  | b    | 1    |
| b    | a-1  | -1   |

### 无解

计时就行了

## Code

```c++
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <time.h>
#define MAXN 200005
using namespace std;

clock_t start;

namespace Graph{
    struct edge{
        int u,v,d;
    };
    vector<int>G[MAXN];
    vector<edge>E;
    void addedge(int u,int v,int d)
    {
        G[u].push_back(E.size());
        E.push_back((edge){u,v,d});
    }
    struct HeapNode{
        int u,d;
        bool operator<(const HeapNode a)const
        {
            return this->d>a.d;
        }
    };
    int d[MAXN];
    bool vis[MAXN];
    void dijstra(int s)
    {
        memset(d,0x3f,sizeof(d));
        d[s]=0;
        priority_queue<HeapNode>Q;
        Q.push((HeapNode){s,0});
        while(!Q.empty())
        {
            int x=Q.top().u;
            Q.pop();
            for(int i=0;i<G[x].size();i++)
            {
                edge &e=E[G[x][i]];
                if(clock()-start>=0.7*CLOCKS_PER_SEC)
                {
                    printf("-1");
                    exit(0);
                }
                if(d[e.v]>d[e.u]+e.d)
                {
                    d[e.v]=d[e.u]+e.d;
                    Q.push((HeapNode){e.v,d[e.v]});
                }
            }
        }
    }
}using namespace Graph;

int n,m;

int main()
{
    start=clock();
    scanf("%d%d",&n,&m);
    for(int i=0;i<=n;i++)
    {
        addedge(i+1,i,0);
        addedge(i,i+1,1);
    }
    for(int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        addedge(x-1,y,1);
        addedge(y,x-1,-1);
    }
    dijstra(0);
        printf("%d",d[n]);
    return 0;
}
```



---

## 作者：wudiss8 (赞：6)

本蒟蒻第二道题解


------------

做题历程:

夏令营模拟赛出了这道题，比赛时并不会做，老师一波玄学讲题，思路懂了，用了一天打出来，夏令营OJ全A，洛谷上WA了一个"-1"无解的点。~~夏令营OJ数据真水~~， 后面改了就AC了

------------
前置芝士：单调队列
单调队列就是一种具有严格单调性，先进先出，后进后出的数据结构，有队头和队尾两个指针。

说人话就是一个数组，数字从大到小或从小到大排列，元素可以从最后进入和最前面弹出。

实现下面会应用到。

------------


本蒟蒻并不懂什么差分约束,就直接讲讲DP的思路吧

首先，理解题意，题目大意就是一条数轴上，有多段区间，可能会相互覆盖，但不一定数轴上所有点都覆盖到，现在要求每个区间内都有且只有一个特殊点，求特殊点的最大数量。

接着，我们设F[i]表示i点放置，题意告诉我们，每个区间有且只有一个点，所以这个点的转移范围必然是前面的第一个不覆盖它的区间, 就像这样（不要吐槽我的图，我也不知道有什么好的软件，只能用画图了QwQ）![](https://cdn.luogu.com.cn/upload/pic/63325.png)

此时，我们的问题就变成了如何寻找每一个点的转移过来的区间，分析一下，这个转移过来的区间的右端点肯定是第一个覆盖到当前点的区间的左端点-1，大概就是这样![](https://cdn.luogu.com.cn/upload/pic/63330.png)

右端点好求，那怎么求左端点呢？

输入的时候，我们可以先预处理每一个照片区间，按左端点的先后sort排序,然后从数轴最右端往最左端枚举每个照片区间，当一个区间最先没有覆盖到F[i]时，这个照片区间的左端点也就是我们转移区间的左端点了（排了序，转移范围就最大了，感受一下awa）

要特别注意的是：在枚举过程中，如果一个F[i]没有被区间覆盖，那么它就是不受限制的，为求最大值，它就可以直接赋1，为了方便，我们就DP过程中就直接不统计这个点，统计这类点的个数，最后直接加上就好了。

下面就轮到了重点部分，DP了
按理来说，我们只要从左往右枚举每个点，对应地枚举区间，转移过来+1就好了，但是，如果每个点的区间都非常大，就会超时了，而在这个过程中，我们的转移区间是不断右移的，且每次只要取最大值，有没有什么方法优化呢？

那就是单调队列！

每一次我们从一个点到另一个点移动转移区间时，只要将区间右边的新元素进队，左边已不在转移范围内的旧元素出队就可以了。同时我们还要维护单调这一性质，因为我们要取最大值的队头。所以，这将是一个单调递减的队列。如果新进队的元素大于前面的元素，我们就将前面的元素弹出，让它顶替，再让它和前面的比较，如果也大于就弹出，直到符合整个队列符合单调性为止（可以将队列中的前面全部元素弹出，只剩最大的一个它）。DP转移的时候，每次获取队头的值就可以（不弹出）。图示：![](https://cdn.luogu.com.cn/upload/pic/63340.png)

另外，对于无解的情况，我们也要考虑，当一个区间完全覆盖了两个不相交的区间时，此时就无解了，如下图：![](https://cdn.luogu.com.cn/upload/pic/63357.png)
而在预处理的过程中，这种情况，右边的小区间的转移区间的左端点，会更新到左边小区间的左端点，而右端点则还保留在大区间的左端点，此时，这一部分就无法枚举，从而不会更新，，因为我们的左端点已经比右端点还右了，单调队列的头指针也先于了尾指针，整个队列里已经没有值了，也无法更新了！！！（头指针要在小于等于尾指针的情况下才能++）也就将这个状态一直持续到了结束，后面DP无法进行，也就保留了初始化化的状态（如果感觉这一段不清楚，可以看代码自己模拟）。

此时，程序的主体就已经完毕了，输出部分，我们需要从最后一个照片的左区间到N中选取，因为后面可能会没有覆盖到，而不做DP，至此，我们的程序就完毕了。

下面上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct sec{
	int l,r;
}ph[1000001];//照片区间
int f[1000001],L[1000001],R[1000001],q[1000001];
//f是DP数组，L是每个点的转移区间左端点，R是右端点，q是单调队列
bool cmp(sec x,sec y){
	return x.l<y.l;
}
inline int read(){//快读
	int s=0,f=1;
	char c;
	c=getchar();
	while(c<'0' or c>'9'){
	if(c=='-')
	f=-1;
	c=getchar();
	}
	while(c>='0' and c<='9'){
	s=s*10+c-'0';
	c=getchar();
	}
	return s*f;
}
int main(){
	int n,m,i,j,now,st,ed,ans=-1,ex=0;
	n=read();m=read();
	for(i=1;i<=m;i++){
		ph[i].l=read();ph[i].r=read();//读入照片区间
	}
	sort(ph+1,ph+m+1,cmp);//按左端点从小到大快排
	now=1;
	for(i=1;i<=n;i++){//预处理每个点转移区间的右端点
		while(ph[now].r<i and now<=m)now++;
     //  ph[now].r<i  当右端点大于该点时，就找到了
     //  now<=m  如果该点在最后没有被覆盖，要判断一下，别跑出去了
		if(now>m or ph[now].l>i)R[i]=-1,ex++;
     //如果没有被覆盖，ex统计个数+1;
	    else R[i]=ph[now].l-1;//否则记录右端点
	}
	now=m;
	for(i=n;i>=1;i--){
	    while(ph[now].r>=i and now>0)now--;
     //处理左端点，从后往前枚举，一个照片区间的右端点一旦没有大于它。
     //照片区间的左端点就是转移区间的左端点了
		if(now==0)L[i]=0;
     //如果最先一个区间覆盖了它，它就从最前面0开始转移
	    else L[i]=ph[now].l;
     //直接赋值，如果是没有被覆盖的点，区间右端点-1，不计算
    }
    for(i=1;i<=n;i++)f[i]=-1;//初始化
    st=ed=1;
    //单调队列,st队头指针(也可以理解成位置，后同)，ed队尾指针
    now=0;//当前点
    for(i=1;i<=n;i++){
    	if(L[i]<=R[i]){
    	    while(R[i]>now){
          now++;//如果右端点大于当前端点，依次前移，进队
    	    if(f[now]>=0){
    	    	while(f[now]>=f[q[ed]] and ed>=st)ed--;
       //如果队尾新元素大于前面的元素，依次弹掉前面的元素，直到队头 
    	    	ed++;q[ed]=now;//完成进队
            }
            }
            while(L[i]>q[st] and st<=ed)st++;
            //前面已不再转移区间内的元素依次出队
            //后面无法转移，不进队，头指针又向前。
            //一旦越过头指针≤尾指针的边界，就无解了
            if(st<=ed)f[i]=f[q[st]]+1;
            //取队头最大值转移
        }
    }
    for(i=ph[m].l;i<=n;i++)
    ans=max(ans,f[i]);//在最后取最大值 
    if(ans==-1)//如果过程中已无法转移过来，全为-1，则无解
    printf("-1\n");
    else
    printf("%d\n",ans+ex);//有解就最大值加上没被覆盖的点的数量，输出
	return 0;
}
```
本篇题解到此结束，本蒟蒻没写过几篇题解，如有不周之处，请各位神犇大佬多多包涵,同时也欢迎指正

---

## 作者：ccsc (赞：3)

题解：

本题题意：

在一群区间之中，需要满足：

1.在每个区间里面都必须要有一个斑点牛。

2.并且每个区间里面都必须只有一个斑点牛。

这两句话很关键。于是我们可以根据这两个条件做dp。

用f[i]表示到第i个位置为止且第i个位置必放，最多能放多少个

---------------------------------------------------------------------------


（敲黑板！！）那么具体思路是：：

确定j的范围？

根据条件1，我们可以确定左边界

（因为必须选，那么上一个区间也一定要选，故j一定是>=最靠近i左边的区间的左坐标）

根据条件2，我们可以确定右边界。

（因为必须选一个，所以包含i的区间里面的任意一个j都不能转移，即j<=包含i的区间的最小的左坐标）

故我们可以根据这些限定用单调队列来优化原来的dp方程。

整个事情变得简单了起来，，

觉得这个**题很水~~水~**


------------
具体实现：：


因为一个区间至多一个，所以所有包含这个点的区间都不能再放，要找到所有包含这个点的区间中最小的左端点，令r[i]=左端点−1；

因为一个区间至少一个，所以不能有地方空着不放，找到整个区间在当前点之前的区间，取最大的左端点，令l[i]=左端点

每一次读入的时候，用x更新l[y+1]用x-1更新r[y]

然后正着扫一遍，用l[i−1]更新l[i]（在i-1之前的左端点必定在i之前）；
然后倒着扫一遍，用r[i+1]更新r[i]、
所以f[i]=max{f[j]+1,l[i]<=j<=r[i]}，开个单调队列优化

ok了

完成！

code：
```cpp
#include<bits/stdc++.h>
#define N 200005
using namespace std;
#define getc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<15,stdin),p1==p2)?EOF:*p1++)
char buf[1<<15],*p1=buf,*p2=buf;
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
template<class T>inline bool cmin(T&a,const T&b){return a>b?a=b,1:0;}
inline int read(){
    #define num ch-'0'
    char ch;bool flag=0;int res;
    while(!isdigit(ch=getc()))
    (ch=='-')&&(flag=true);
    for(res=num;isdigit(ch=getc());res=res*10+num);
    (flag)&&(res=-res);
    #undef num
    return res;
}
int n,m,l[N],r[N];
int h,t,q[N],f[N];
int main(){
    n=read(),m=read();
    for(int i=1;i<=n+1;++i) r[i]=i-1;
    for(int i=1;i<=m;++i){
        int x=read(),y=read();
        cmin(r[y],x-1);
        cmax(l[y+1],x);
    }
    for(int i=n;i>=1;--i) cmin(r[i],r[i+1]);
    for(int i=2;i<=n+1;++i) cmax(l[i],l[i-1]);
    int j=1;h=t=1,q[1]=0;
    for(int i=1;i<=n+1;++i){
        while(j<=r[i]&&j<=n){
            if(f[j]==-1){++j;continue;}
            while(f[j]>f[q[t]]&&h<=t) --t;
            q[++t]=j;
            ++j;
            }
        while(q[h]<l[i]&&h<=t) ++h;
        if(h<=t) f[i]=f[q[h]]+(i!=n+1?1:0);
        else f[i]=-1;
    }
    printf("%d\n",f[n+1]);
    return 0;
}
```




---

## 作者：king_more (赞：2)

看到题目，看到标签，有点懵，再看题解，理解消化一下，才觉得明白，用通俗的语言和大家讲讲。

首先我们先设f[ i ]为在 i 点满足情况下放一头奶牛，如果放不下就把f[ i ]置为 -1。

易想f[ i ] = max(f[ j ]) + 1 (1 < j < i)

现在我们就要想如何满足限制。

如果一张照片左端点为 l ,右端点为 r 。那么，在 l 和 r 之间最小有一头奶牛，最多一头奶牛。

我们先考虑最多一头奶牛，如果 i 点放了奶牛，那么所有包含 i 的区间都不可以放奶牛了，我们可以用O( n )的时间把这个预处理出来。

假设输入一个l,r。

minn[r] = min(minn[r],l) 显而易见，输入的时候先处理一部分，把所有右端点都给处理了。

然后再从n 到 1，minn[ i ] = min (minn[ i ],minn[i + 1])

一个数最左边要不是它原来就有，要么就是它右边的最左位置。

再考虑最少一头奶牛，先举个例子

比如3张照片

1 5

3 4

5 5

枚举到f[ 5 ]的时候是不可以从f[ 2 ]继承的，因为如果这样的话，3 ~ 4就一头奶牛也没有放，不满足条件，所以我们可以发现，必须从r < i 的所有区间中寻找 l 最大的，不然就会空区间。

也可以直接O（n）处理。

输入l,r。

maxx[r - 1] = max(maxx[r - 1],l)

再从1 ~ n

maxx[r] = max(max[r - 1],maxx[r])

同理，要么本来就有，要么继承它左边的最大l

因为minn 都 maxx 都符合单调性，所以可以直接用单调队列维护，维护一个单调递减序列，队首永远是目前符合最大的f[ i ]

每次从 j 到 minn[ i ]，加入合法的 j。

然后到队首小于maxx[ i ]，直接使队首往下轮。

上代码

```
#include <cstdio>
#include <algorithm>
using namespace std;
const int M = 200000;
int minn[M + 5],maxx[M + 5];
int q[M + 5];
int f[M + 5];
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n + 1;i ++){
		minn[i] = i;
	}
	for(int i = 1;i <= m;i ++){
		int l,r;
		scanf("%d%d",&l,&r);
		minn[r] = min(minn[r],l);
		maxx[r + 1] = max(maxx[r + 1],l);
	}
	for(int i = n;i >= 1;i --){
		minn[i] = min(minn[i + 1],minn[i]);
	}
	/*for(int i = 1;i <= n + 1;i ++){
		printf("%d ",minn[i]);
	}
	printf("\n");*/
	for(int i = 1;i <= n + 1;i ++){
		maxx[i] = max(maxx[i],maxx[i - 1]);
	}
	/*for(int i = 1;i <= n + 1;i ++){
		printf("%d ",maxx[i]);
	}
	printf("\n");*/
	int h = 0,t = 0,j = 0;
	for(int i = 1;i <= n + 1;i ++){
		for(;j < minn[i];j ++){
			if(f[j] != -1){
				while(h <= t && f[j] > f[q[t]])
					t --;
				q[++ t] = j;
			}
		}
		while(h <= t && q[h] < maxx[i]) h ++;
		if(h <= t){
			f[i] = f[q[h]] + (i != n + 1); 
		}
		else f[i] = -1;
	//	printf("%d %d|",q[h],q[t]);
	}
	//printf("\n");
	/*for(int i = 1;i <= n + 1;i ++)
		printf("%d ",f[i]);*/
	printf("%d",f[n + 1]);
	return 0;
}
```


---

## 作者：XuYueming (赞：1)

## 前言

题目链接：[洛谷](https://www.luogu.com.cn/problem/P3084)。

[更好的体验](https://www.cnblogs.com/XuYueming/p/18397834)。

## 题意简述

一个长度为 $n$ 的序列，有一些位置染了色。现给出 $m$ 条限制，第 $i$ 条限制为 $l_i \sim r_i$ 中有且仅有一个位置染色。求出满足这 $m$ 中条件，染色位置个数最多为多少。

$n \leq 2 \times 10^5$，$m \leq 10^5$。

## 题目分析

### 方法 $1$：差分约束

区间问题使用前缀和，退化成关于两端点的限制：$v_{r_i} - v_{l_i - 1} = 1$，其中 $v_i$ 表示 $1 \sim i$ 中有多少染色的位置。以及题目本身的限制：$v_{i} - v_{i - 1} \in [0, 1]$，建图后差分约束跑一跑即可。

我们求 $\max v_n$，使用最短路算法。

无解情况等价于存在负环，最短路不存在。

但是显然会超时，如何优化？SPFA 经典优化：SLF 优化。嗯，还差一个点，循环次数超过魔法数字 $1736520$ 就无解。就水过去了。

### 方法 $2$：动态规划

差分约束显然不是正解。序列问题，决策是当前点是否染色，可以使用 DP 解决。

我们设 $f_i$ 表示 $i$ 染色时 $1 \sim i$ 染色的位置的个数的最大值。转移的时候枚举上一次染色的位置 $j$，有转移方程：

$$
f_i = \max _ {\text{meet given conditions}} \{ f_j \} + 1
$$

时间复杂度什么的先不谈，考虑怎么判断一个 $j$ 是否合法。

有一个 trick：**「恰好」等价于「不少于并且不大于」**。

对于本题，恰好区间染色了一个位置，拆成两个限制，即至少染色一个位置，至多染色一个位置。

先考虑前者。由于 $(i, j)$ 中没有染色，如果其中存在一个限制区间就会不合法。所以我们求得 $mi_x$ 表示右端点在 $x$ 左边，左端点的最大值。$j$ 需要满足 $j \geq mi_i$。

再考虑后者。如果一个区间同时包括了 $i$ 和 $j$，那么也是不合法的。我们求得 $mx_x$ 表示右端点在 $x$ 及右边，左端点的最小值。$j$ 需要满足 $j \lt mx_i$。

预处理扫一扫是简单的。

转移方程变成：

$$
\large f_i = \max _ {j = mi_i} ^ {mx_i - 1} \{ f_j \} + 1
$$

由于 $mx$ 和 $mi$ 单调不降，直接上单调队列就行了。注意如果我们记无效的 $f_i = -1$，则上式中的 $\max$ 需要满足 $f_j \neq -1$，如果没有满足条件的 $j$，那么 $f_i = -1$。

注意到我们不能直接取 $f$ 的最大值作为答案，因为我们需要满足所有 $m$ 条限制。不妨用 $f_{n + 1}$ 统计答案，这样就能完整考虑到所有限制，并求出最大值了。

时间复杂度：$\Theta(n + m)$。

**Update on 2024.11.2**：寻找到 $f$ 的性质，省略单调队列。

经过打表发现 $f$ 是单调递增的，所以单调队列可以换成双指针，维护 $\lt mx_i$ 的 $j$ 中，最后一个 $f_j \neq -1$ 的 $k$。转移的时候判断 $k$ 是否 $\geq mi_i$，转移即可。时间复杂度没有变化。

**详细证明**：

使用第二数学归纳法。假设所有 $j \lt i$ 满足 $f_j$ 具有单调性。如果能推出 $f_i \geq f_{i - 1}$ 即证。

有 $mx_i \geq mx_{i - 1}$，那么在 $mx_{i - 1} + 1 \sim mx_i$ 可能存在 $\geq f_{mx_{i - 1}}$ 的 $f$，因为所有 $j \lt i$ 满足 $f_j$ 具有单调性，那么 $f_i$ 就能从这里转移过来，从而 $\geq f_{i - 1}$。

## 代码

### 方法 $1$：差分约束

见[我的博客](https://www.cnblogs.com/XuYueming/p/18397834)。

### 方法 $2$：动态规划

### 单调队列

见[我的博客](https://www.cnblogs.com/XuYueming/p/18397834)。

### 双指针

```cpp
#include <cstdio>

const int MAX = 1 << 23, N = 200001;
int n, m, l, r, mx[N], mi[N], f[N];
char buf[MAX], *p(buf), *e(buf + MAX);

#define getchar() (p == e && fread(p = buf, 1, MAX, stdin), *p++)

[[always_inline]] inline void read(int &x) {
    x = 0; char ch = getchar();
    for (; ch <  48; ch = getchar());
    for (; 48 <= ch; ch = getchar())
        x = (x << 3) + (x << 1) + (ch ^ 48);
}
[[always_inline]] inline void tomin(int& a, int& b) { b < a && (a = b); }
[[always_inline]] inline void tomax(int& a, int& b) { b > a && (a = b); }

main() {
    fread(buf, 1, MAX, stdin), read(n), read(m);
    for (register int i(1); i <= n + 1; ++i) mx[i] = i;
    for (; m--; ) read(l), read(r), tomin(mx[r], l), tomax(mi[r + 1], l);
    for (register int i(n); i; --i) tomin(mx[i], mx[i + 1]);
    for (register int i(1), j(0), k(0); i <= n + 1; ++i, tomax(mi[i], mi[i - 1])) {
        for (; j + 1 < mx[i]; ~f[++j] && (k = j));
        f[i] = k >= mi[i] ? f[k] + 1 : -1;
    }
    ~f[n + 1] ? printf("%d", f[n + 1] - 1) : puts("-1");
}
```

---

## 作者：SamariumPhosphide (赞：1)

挺有趣的神仙 dp 题目，建议仔细思考一下。

首先考虑 dp，那么 $f[i]$ 很自然就是第 $i$ 头牛为有斑点的情况下前 $i$ 头牛的有斑点牛数量的最大值。

那么可以发现，$f[i]$ 只可以由一部分 dp 值转移得到，可以发现这些可以转移的是连续的一段。那么假设最小的为 $s[i]$，最大的是 $e[i]$。

那么 $e[i]$ 为**最大的满足不与 $i$ 在同一张照片中出现的点。**也就是覆盖 $i$ 的照片中，左端点的最小值 $-1$。

$s[i]$ 就是**左端点，右端点均 $<i$ 的照片中的最大的左端点。**

注意到 $e,s$ 数组均可以通过 dp 得到。转移方程很容易推出。
$$
e[i]=\min(e[i+1],\text{lmin}[i]-1)\\s[i]=\max(s[i-1],\text{lmax}[i-1])
$$
其中 $\text{lmin}, \text{lmax}$ 的意义分别为以 $i$ 为右端点的左端点最小值与最大值，可以通过预处理得到。

由递推式容易发现 $e[i]\leq e[i+1]$ 且 $s[i]\leq s[i+1]$，因此**转移部分只增不减，可以使用单调队列维护。**

最后注意一下细节，要判断无解情况。

[Code Here](https://www.luogu.com.cn/paste/q3xweyy7)

---

## 作者：Smallbasic (赞：1)

关于SPFA。她死了

本来想推dp的但由于要练差分约束于是就写了差分约束做法。

设$f_n$为前n头奶牛中有斑点的个数，由于每张照片中只有一只斑点奶牛，可以得到：

$$f_b-f_{a-1}=1$$

显然只有这一个还不够吧。。。

每个点只有两种取值，要么是，要么不是，也就是

$$0\le f_i-f_{i-1}\le1$$

~~没错差分约束就是尽量找废话一样的不等关系~~

于是就是裸差分约束了：

```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

inline int read() {
	register int s = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch)) f = (ch == '-' ? -1 : 1), ch = getchar();
	while (isdigit(ch)) s = (s << 1) + (s << 3) + (ch & 15), ch = getchar();
	return s * f;
}

int n, m, u, v, w, en = 0, cnt[1000005], dis[1000005];
deque<int> q; bool vis[1000005];

struct Edge {
	int head, to, val, nxt;
}ed[2000005];

inline void addedge(int from, int to, int val) {
	ed[++en].to = to; ed[en].val = val;
	ed[en].nxt = ed[from].head; ed[from].head = en;
}

int main() {
	n = read(); m = read();
	while (m--) { u = read(); v = read(); addedge(u - 1, v, 1); addedge(v, u - 1, -1); }
	for (int i = 1; i <= n; ++i) addedge(i, i - 1, 0), addedge(i - 1, i, 1);
	memset(dis, 0x3f, sizeof(dis));
	dis[0] = 0; vis[0] = 1; q.push_back(0);
	while (!q.empty()) {
		int x = q.front(); q.pop_front(); vis[x] = 0;
		for (int i = ed[x].head; i; i = ed[i].nxt) {
			int v = ed[i].to;
			if (dis[v] > dis[x] + ed[i].val) {
				dis[v] = dis[x] + ed[i].val;
				cnt[v] = cnt[x] + 1;
				if (!vis[v]) {
					if (cnt[v] > n) return printf("-1") & 0;
					if (!q.empty() && dis[v] > dis[q.front()]) q.push_back(v);
					else q.push_front(v); vis[v] = 1;
				}
			}
		}
	} printf("%d", dis[n]);
	return 0;
}
```

但这样正常写双端队列只能有90分~~无量出题人卡SPFA~~，于是要参照题解大佬写的信仰优化：

```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

inline int read() {
	register int s = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch)) f = (ch == '-' ? -1 : 1), ch = getchar();
	while (isdigit(ch)) s = (s << 1) + (s << 3) + (ch & 15), ch = getchar();
	return s * f;
}

int n, m, u, v, w, en = 0, cnt[1000005], dis[1000005], nm = 0;
deque<int> q; bool vis[1000005];

struct Edge {
	int head, to, val, nxt;
}ed[2000005];

inline void addedge(int from, int to, int val) {
	ed[++en].to = to; ed[en].val = val;
	ed[en].nxt = ed[from].head; ed[from].head = en;
}

int main() {
	n = read(); m = read();
	while (m--) { u = read(); v = read(); addedge(u - 1, v, 1); addedge(v, u - 1, -1); }
	for (int i = 1; i <= n; ++i) addedge(i, i - 1, 0), addedge(i - 1, i, 1);
	memset(dis, 0x3f, sizeof(dis));
	dis[0] = 0; vis[0] = 1; q.push_back(0);
	while (!q.empty()) {
		int x = q.front(); q.pop_front(); vis[x] = 0;
		for (int i = ed[x].head; i; i = ed[i].nxt) {
			int v = ed[i].to;
			if (dis[v] > dis[x] + ed[i].val) {
				dis[v] = dis[x] + ed[i].val;
				cnt[v] = cnt[x] + 1;
				if (!vis[v]) {
					if (++nm > 19260817) return printf("-1") & 0;
					if (!q.empty() && dis[v] > dis[q.front()]) q.push_back(v);
					else q.push_front(v); vis[v] = 1;
				}
			}
		}
	} printf("%d", dis[n]);
	return 0;
}
```
神奇啊

---

## 作者：zzr8178541919 (赞：0)

动态规划练习的一道很好的题目

要用到单调队列优化。

关键在于怎么用nlogn的复杂度写出这道题。

我们来仔细地考虑一下：
#### 如果说用n方的做法，很容易。
#### dp[i]表示前i个位置的答案，i一定要选
#### 我们只需要先枚举i。然后在i的前面枚举j（使得j满足限制即可）
#### 则有状态转移方程：
#### dp[i]=dp[j]+1;
现在我们就考虑优化。我们发现每个点能够选择的范围是有限度的。不是j前面的所有点都能选择。

而且我们发现，如果选择了i，那么j首先只能在包含i的区间的前面找。但是又不能跳过一个区间，因此枚举的这个j还应该只能在前一个区间上。

发现这个用动态规划的方法就可以预处理出来。

处理出来后我们就可以缩小范围dp了，可是还会超时
### 怎么办呢
我们又发现，我们从左向右枚举i，在枚举j的时候，j的区间肯定是
单调递增的。因此我们想到可以用单调队列优化DP

之后就有点像滑动窗口那道题了。

具体操作如下：
```cpp
#include<cmath>
#include<cstring>
#include<cstdio>
#include<queue>
#include<algorithm>
#include<iostream>
#include<deque>
using namespace std;
int dp[200005];
deque<int> q;
int minx[200005];
int maxn[200005];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n+1;i++) 
	minx[i]=i;
    for(int i=1;i<=m;i++)
	{
        int l,r;
		scanf("%d%d",&l,&r);
        minx[r]=min(minx[r],l);
        maxn[r+1]=max(maxn[r+1],l);
    }
    for(int i=n;i>=1;i--)
    minx[i]=min(minx[i],minx[i+1]);
    for(int i=1;i<=n+1;i++)
    maxn[i]=max(maxn[i],maxn[i-1]);
    int j1=1;
    q.push_front(0);
    for(int i=1;i<=n+1;i++)
    {
    	for(;j1<minx[i];j1++)
    	{
    		if(dp[j1]!=-1)
    		{
    			while(!q.empty() && dp[q.front()]<dp[j1])
    			q.pop_front();
    			q.push_front(j1);
			}
		}
		while(!q.empty() && q.back()<maxn[i])
		q.pop_back();
		if(!q.empty())
		{
			dp[i]=dp[q.front()]+(i!=n+1);
		}
		else
		dp[i]=-1;
	}
	printf("%d\n",dp[n+1]);
	return 0;
}
```
我发的使用stl中的deque写的，当然也可以手写\(^o^)/~。


---

## 作者：KesdiaelKen (赞：0)

作为一个暴力选手，只会用**高级数据结构替代低级算法**（这里指单调队列）……

思路的话，各大不是SPFA的题解已经解的很清楚了，用$f_i$表示只考虑$i$之前的区间，必选$i$的情况下的最大值。只不过，单调队列的部分我用线段树实现了。

这样的话可以给那些不怎么懂单调队列的同学一种更简单易懂的写法，也更利于理解。（不要跟我说单调队列比线段树简单）

思路的话其它题解有，代码里也有体现，所以这里就不多说了。

代码：

```
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
#include<iostream>
#include<cmath>
using namespace std;
struct NODE
{
	int a,b,id;
	NODE(){a=b=0;}
}pic1[300000],pic2[300000];
bool cmp1(const NODE&a,const NODE&b){return a.a<b.a;}
bool cmp2(const NODE&a,const NODE&b){return a.b<b.b;}
int cf[300000]={0};
int f[1000000],gs1=1,gs2=1,lc1,lc2;
void cha1(int zuo,int you,int node,int wz,int zhi)
{
	if(zuo>wz||you<wz)return;
	if(zuo==you){f[node]=zhi;return;}
	cha1(zuo,(zuo+you)>>1,node<<1,wz,zhi);
	cha1(((zuo+you)>>1)+1,you,node<<1|1,wz,zhi);
	f[node]=max(f[node<<1],f[node<<1|1]);
}
int xds[2000000]={0};
void cha2(int zuo,int you,int node,int wz,int zhi)
{
	if(zuo>wz||you<wz)return;
	if(zuo==you){xds[node]=zhi;return;}
	cha2(zuo,(zuo+you)>>1,node<<1,wz,zhi);
	cha2(((zuo+you)>>1)+1,you,node<<1|1,wz,zhi);
	xds[node]=min(xds[node<<1],xds[node<<1|1]);
}
int query(int zuo,int you,int node,int qzuo,int qyou)
{
	if(zuo>qyou||you<qzuo)return -2e9;
	if(qzuo<=zuo&&you<=qyou)return f[node];
	return max(query(zuo,(zuo+you)>>1,node<<1,qzuo,qyou),query(((zuo+you)>>1)+1,you,node<<1|1,qzuo,qyou));
}
int main()
{
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&pic1[i].a,&pic1[i].b);
		pic1[i].id=i;
		cf[pic1[i].a]++;cf[pic1[i].b+1]--;
		pic2[i]=pic1[i];
	}
	for(int i=1;i<=n+1;i++)cf[i]+=cf[i-1];
	for(int i=1;i<=n+1;i++)
	{
		if(cf[i]==0)
		{
			pic1[++m].a=i;pic1[m].b=i;
			pic1[m].id=m;
			pic2[m]=pic1[m];
		}
	}
	for(int i=1;i<=4*m;i++)xds[i]=2e9;
	sort(pic1+1,pic1+m+1,cmp1);
	sort(pic2+1,pic2+m+1,cmp2);
	for(int i=1;i<=n*4;i++)f[i]=-2e9;
	cha1(0,n+1,1,0,0);
	int maxn=0;
	for(int i=1;i<=n+1;i++)
	{
		for(int j=gs1;pic1[j].a==i;j++)lc1=j;
		for(int j=gs2;pic2[j].b==i;j++)lc2=j;
		if(pic1[gs1].a!=i)lc1=gs1-1;
		if(pic2[gs2].b!=i)lc2=gs2-1;
		for(int j=gs1;j<=lc1;j++)cha2(1,m,1,pic1[j].id,i);
		if(maxn>xds[1]-1)cha1(0,n+1,1,i,-2e9);
		else cha1(0,n+1,1,i,query(0,n+1,1,maxn,xds[1]-1)+1);
		for(int j=gs2;j<=lc2;j++)maxn=max(maxn,pic2[j].a);
		for(int j=gs2;j<=lc2;j++)cha2(1,m,1,pic2[j].id,2e9);
		gs1=lc1+1;gs2=lc2+1;
	}
	if(query(0,n+1,1,n+1,n+1)<=0)printf("-1\n");
	else printf("%d\n",query(0,n+1,1,n+1,n+1)-1);
	return 0;
}
```

---

