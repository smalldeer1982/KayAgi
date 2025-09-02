# [USACO16JAN] Lights Out G

## 题目描述

Farmer John 在他的谷仓里安装了一个非常不错的新挤奶机，但是这台挤奶机耗电太多了，有时候会让谷仓直接停电！这种事发生的太频繁了，以至于 Bessie 直接把谷仓的地图背过了，以便于可以在黑暗中找到谷仓的出口。她对于停电对于她快速离开谷仓的能力的影响非常好奇。比如说，她想知道她在黑暗中需要走多远来找到谷仓的出口。

谷仓里的路可以被描述为是一个简单的用几个顶点来表示的多边形，这些顶点可以按照顺时针被表示为 $(x_1, y_1) \cdots (x_n, y_n)$（保证这些顶点连成的线没有交叉的情况）。这些点构成的边在水平轴（平行于 $x$ 轴）和竖直轴（平行于 $y$ 轴）之间交替出现。第一条边可以是任意一种类型。谷仓出口在坐标 $(x_1, y_1)$ 。Bessie 从谷仓内任意一个点 $(x_i, y_i)$ 开始走。她只可以沿着这些边走，要不然是顺时针，要不然就是逆时针，她的目标就是以最短距离抵达出口。当然，如果灯亮着的话这个事还算相对简单，因为她要不然顺时针要不然逆时针走，无所谓哪个方向的路程更短一点。

一天，谷仓突然停电了，导致 Bessie 受到惊吓、忘记了她站在哪个顶点。幸亏她还记得谷仓的准确地图，所以她可以四处走走，用她的触觉来弄清楚她的位置。不管什么时候，只要她站在一个顶点，那么她就可以感受到她在这个点的朝向角度，弄清楚这个点是不是出口。当她沿着谷仓的一个边走完的时候，她可以算出精确的边长。Bessie 决定用这么一个策略：她会顺时针沿着谷仓周围的边走，直到她知道了足够的角度和边、可以推断出她目前在的是哪个顶点。在那个顶点，她就可以轻易地弄清楚怎样以最短距离到达出口（要不然继续沿着顺时针走，要不然倒回去沿着逆时针走）。

请帮助 Bessie 算出在起点可以是任何一个顶点情况下，在最坏的情况下，她在黑暗中和亮着灯的时候到达出口的距离的差值（即找到差值的最大值）。

## 说明/提示

在这个样例中，Bessie 开始可以感觉到她沿着 $90 \degree$ 角站着，但是她辨别不出来她是在 $2, 3, 4$ 中的哪一个顶点。

在走了一条边以后，Bessie 要不然到了出口要不然就可以根据她走过的距离推断出她的位置。情况如下：

如果她从 $2$ 号点开始走，她需要在黑暗中走 $12$ 个单位，包括一个单位到达第三个点、十一个单位离开谷仓。同时，如果亮着灯，她可以只走 $10$ 个单位就离开谷仓。差值是 $2$ 。

如果从 $3$ 号点开始，她两种情况都要走 $11$ 个单位。

如果从 $4$ 号点开始，她两种情况都要走 $1$ 个单位。

所以最坏情况差值是 $2$ 。

## 样例 #1

### 输入

```
4
0 0
0 10
1 10
1 0```

### 输出

```
2```

# 题解

## 作者：DengDuck (赞：3)

我一开始读错题了，以为奶牛知道方向......

感觉大家都是字符串做法，来个快一点的哈希。

我们要找奶牛走的路径是否唯一，判断两个路径是否相同，需要存储很多信息，而且只比较是否相等，这显然是哈希的标志。

哈希的方式就很多了，我的方式是每条边距离乘上内角，内角用两个常数表示。

这里我觉得可能需要进一步解释，内角只有两种情况，分别是 $90\degree$ 和 $270\degree$ 两种可能，如何求角是个麻烦的事情。

我们可以讨论一手，然后发现，我们给出点的时候（也就是输入），要么是顺时针给，要么是逆时针给，而角度与 $(i-1,i)$ 旋转至 $(i,i+1)$ 是顺时针还是逆时针有关。

进一步地，我们不关心角度到底是多少，我们反正要把它变成一个常量了，我们不妨直接按顺时针还是逆时针给其表示内角的常量。

处理好了，每次还要乘上一个常数 $K$，防止溢出还需要模 $10^9+7$。

我们把这些路径存在 `multiset` 之中，我们需要多个 `multiset`，第 $i$ 个表示路径经历边数为 $i$ 的路径的哈希值可重集。

我们直接模拟吧，当我们走的一个地方时，我们的哈希值在可重集中是唯一的，那么终止循环并更新答案即可。

由于我用了 `multiset`，时间复杂度为 $O(n^2\log n)$，理论上可以优化成 $O(n^2)$，但我懒。

我丧心病狂也才全洛谷第四，前面的字符串怎么比我快啊 QAQ。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=1005;
const LL L=114514,R=191981,K=2008;
const LL mod=1e9+7;

LL n,x[N],y[N],dis[N],mx,l[N],r[N],d[N];
multiset<LL>s[N];
LL cal(LL a,LL b)
{
	if(a==n+1)a=1;
	return abs(x[a]-x[b])+abs(y[a]-y[b]);
}
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&x[i],&y[i]);
	}
	for(int i=2;i<=n;i++)
	{
		dis[i]=dis[i-1]+cal(i-1,i);
	}
	for(int i=n;i>=2;i--)
	{
		dis[i]=min(dis[i],dis[i+1]+cal(i+1,i));
	}	
	for(int i=1;i<=n;i++)
	{
		if(i==1)
		{
			if(x[i]+y[i]<=x[n]+y[n])l[i]=1;	
		}
		else if(x[i]+y[i]<=x[i-1]+y[i-1])l[i]=1;	
	}
	for(int i=n;i>=1;i--)
	{
		if(i==n)
		{
			if(x[i]+y[i]<=x[1]+y[1])r[i]=1;	
			if(x[i]==x[1]&&l[i]==0&&r[i]==1)d[i]=R;
			else if(y[i]==y[1]&&l[i]==1&&r[i]==1)d[i]=R;
			else if(x[i]==x[1]&&l[i]==1&&r[i]==0)d[i]=R;
			else if(y[i]==y[1]&&l[i]==0&&r[i]==0)d[i]=R;
		}
		else
		{
			if(x[i]+y[i]<=x[i+1]+y[i+1])r[i]=1;
			if(x[i]==x[i+1]&&l[i]==0&&r[i]==1)d[i]=R;
			else if(y[i]==y[i+1]&&l[i]==1&&r[i]==1)d[i]=R;
			else if(x[i]==x[i+1]&&l[i]==1&&r[i]==0)d[i]=R;
			else if(y[i]==y[i+1]&&l[i]==0&&r[i]==0)d[i]=R;
		}
		if(d[i]==0)d[i]=L;
	}	
	for(int i=2;i<=n;i++)
	{
		LL cnt=d[i];
		s[0].insert(d[i]);
		for(int j=i+1;j<=n;j++)
		{
			cnt=cnt*K%mod;
			if(x[j]+y[j]<=x[j-1]+y[j-1])
			{
				cnt=(cnt+d[j]*cal(j,j-1)%mod)%mod;
			}
			else
			{
				cnt=(cnt+d[j]*cal(j,j-1)%mod)%mod;
			}
			s[j-i].insert(cnt);
		}
	}
	for(int i=2;i<=n;i++)
	{
		LL cnt=d[i],sum=0;		
		for(int j=i+1;j<=n;j++)
		{
			cnt=cnt*K%mod;
			if(x[j]+y[j]<=x[j-1]+y[j-1])
			{
				cnt=(cnt+d[j]*cal(j,j-1)%mod)%mod;
			}
			else
			{
				cnt=(cnt+d[j]*cal(j,j-1)%mod)%mod;
			}
			sum+=cal(j,j-1); 
			if(s[j-i].count(cnt)<=1)
			{
				mx=max(mx,dis[j]+sum-dis[i]);
				break;
			}			
		}		
	}
	printf("%lld",mx);
	return 0;
}
```

---

## 作者：Noir_ (赞：3)

# P3134 [USACO16JAN]Lights Out G题解

#### 题目大意

真不好概括，可以去看看[讨论](https://www.luogu.com.cn/discuss/314570) （逃

#### 分析

首先，我们可以发现，在黑暗中，要使 Bessie 意识到自己在哪个顶点，当且仅当她走过的边的结构在地图中是独一无二且最短的。

要实现这个目的，我们需要一种数据结构来维护地图的结构以及 Bessie 走过的路径，并且这种数据结构要满足如下几个特点：

1. 可以查找路径在地图中的出现次数

2. 支持在末尾新添状态

3. 复杂度小

4. 每种地图结构只有一种表达方式，反之亦然

这里给出一种很好实现的方法：**字符串哈希**。

接下来说明如何实现。

#### 实现

对于一个地图结构，我们可以模拟 Bessie 的路线：从起点出发，走一段长度到另一个顶点，然后左转或右转，直到到达出口。

那我们也可以这样记录地图结构：

1. 左转：在字符串中加入一个字符 $L$

2. 右转：在字符串中加入一个字符 $R$

3. 直走：在字符串中加入当前边的长度

可以得到如下函数：

```cpp
inline void add(register string &mode,const int x){
	if(a[x].lr) mode+='R';else mode+='L';//左右转
	register string s;register int tmp=a[x].len;//路径长度
	while(tmp) s+=char((tmp%10)|48),tmp/=10;
	reverse(s.begin(),s.end());mode+=s;//加进字符串中
}
```

而要实现查找路径在地图中的出现次数，可以用到 STL 中的 string 函数 find()。

循环使用 find() 即可：

```cpp
inline int count(const string &a,const string &b){
	register size_t pos=0;register int ans=0;
	while((pos=a.find(b,pos))!=string::npos) ++ans,++pos;
	return ans;
}
```

**But!!** 仔细思考一下即可发现几个问题：

1. 若路径串为 **R10** ，地图串中有一个子串为 **R1065** ，那么此时这个 count() 函数仍然会匹配到。

    所以我们对 add() 函数进行一些修改：**每次加入完一条边后再加一个空格**：

    ```cpp
    inline void add(register string &mode,const int x){
        if(a[x].lr) mode+='R';else mode+='L';//左右转
        register string s;register int tmp=a[x].len;//路径长度
        while(tmp) s+=char((tmp%10)|48),tmp/=10;
        reverse(s.begin(),s.end());mode+=s;mode+=' ';//新加一个空格（或其他字符也行）
    }
    ```

2. 重新审题，可以发现 Bessie 每到一个顶点，她是可以判断下一条边的转向方向的（左 $or$ 右）。

    所以我们对 count() 函数进行一些修改：**每次匹配路径时，临时在路径串末尾加入下一次转向的符号**：

    ```cpp
    inline int count(const string &a,register string b,const char c){
        b+=c;//临时加入下一次转向的方向符号
        register size_t pos=0;register int cnt=0;
        while((pos=a.find(b,pos))!=string::npos) ++cnt,++pos;
        return cnt;
    }
    ```

有了 add() 和 count() 函数，我们即可写出 solve() 函数统计答案：

```cpp
inline void solve(const int now){
	register string path;
	register int sum=0;
	for(register int i=now;i<=n;++i){
		if(count(mode,path,a[i].lr?'R':'L')) return void(ans=max(ans,abs(dis[now]-(sum+dis[i]))));
		add(path,i),sum+=a[i].len;
	}
}

for(register int i=2;i<=n;i++) solve(i);
```

~~接下来就是最恶心的**数据读入**了。~~

代码中注释很详细，可以自行理解：

```cpp
/*a[i].lr: 0->左转，1->右转*/
/*a[i].dir: 1->东，2->南,3->西,4->北*/
n=read();
for(register int i=1;i<=n;++i) mp[i].first=read(),mp[i].second=read();
mp[n+1]=mp[1];
for(register int i=2;i<=n+1;++i){
    if(mp[i].first==mp[i-1].first){//竖着走
        tot+=(a[i-1].len=abs(mp[i].second-mp[i-1].second));
        if(mp[i].second>mp[i-1].second){//向上走
            a[i-1].dir=4;if(!a[i-2].dir) continue;
            if(a[i-2].dir==1) a[i-1].lr=0;//前一个是向东走，那么就是左转
            else a[i-1].lr=1;//前一个是向西走，那么就是右转
        }
        else{//向下走
            a[i-1].dir=2;if(!a[i-2].dir) continue;
            if(a[i-2].dir==1) a[i-1].lr=1;//前一个是向东走，那么就是右转
            else a[i-1].lr=0;//前一个是向西走，那么就是左转
        }
    }
    else{//横着走
        tot+=(a[i-1].len=abs(mp[i].first-mp[i-1].first));
        if(mp[i].first>mp[i-1].first){//向右走
            a[i-1].dir=1;if(!a[i-2].dir) continue;
            if(a[i-2].dir==2) a[i-1].lr=0;//前一个是向南走，那么就是左转
            else a[i-1].lr=1;//前一个是向北走，那么就是右转
        }
        else{//向左走
            a[i-1].dir=3;if(!a[i-2].dir) continue;
            if(a[i-2].dir==2) a[i-1].lr=1;//前一个是向南走，那么就是右转
            else a[i-1].lr=0;//前一个是向北走，那么就是左转
        }
    }
}
```

#### 完整代码

```cpp
#include<bits/stdc++.h>
#define N 205
#define inf 0x3f3f3f3f
#define endl '\n'
#define debug cerr<<__LINE__<<endl
using namespace std;
int n,tot,ans=-inf;
int dis[N];
int shun[N],ni[N];
pair<int,int>mp[N];
struct node{int len,dir;bool lr;}a[N];
string mode;
inline char gc(){
	static const int L=1<<22|1;static char c[L],*a,*b;
	return (a==b)&&(b=(a=c)+fread(c,1,L,stdin),a==b)?-1:*a++;
}
inline int read(){
	register int f=1,k=0;
	register char c=gc();
	while(c!='-'&&(c<'0'||c>'9')) c=gc();
	if(c=='-') f=-1,c=gc();
	while(c>='0'&&c<='9') k=(k<<3)+(k<<1)+(c^48),c=gc();
	return f*k;
}
inline void write(register int x){
	if(x<0) x=-x,putchar('-');
	if(x>9) write(x/10);
	putchar((x%10)|48);
}
inline void add(register string &mode,const int x){
	if(x==1) mode+='T';else if(a[x].lr) mode+='R';else mode+='L';
	register string s;register int tmp=a[x].len;
	while(tmp) s+=char((tmp%10)|48),tmp/=10;
	reverse(s.begin(),s.end());mode+=s;mode+=' ';
}
inline void init(){
	for(register int i=1;i<=n;i++) add(mode,i);
	for(register int sum=0,i=1;i<=n;i++) dis[i]=min(tot-sum,sum),sum+=a[i].len;
}
inline int count(const string &a,register string b,const char c){
	b+=c;
	register size_t pos=0;register int cnt=0;
	while((pos=a.find(b,pos))!=string::npos) ++cnt,++pos;
	return cnt;
}
inline void solve(const int now){
	register string path;
	register int sum=0;
	for(register int i=now;i<=n;i++){
		if(count(mode,path,a[i].lr?'R':'L')==1) return void(ans=max(ans,abs(dis[now]-(sum+dis[i]))));
		add(path,i),sum+=a[i].len;
	}
}
main(void){
	n=read();
	for(register int i=1;i<=n;i++) mp[i].first=read(),mp[i].second=read();
	mp[n+1]=mp[1];
	for(register int i=2;i<=n+1;i++){
		if(mp[i].first==mp[i-1].first){
			tot+=(a[i-1].len=abs(mp[i].second-mp[i-1].second));
			if(mp[i].second>mp[i-1].second){
				a[i-1].dir=4;if(!a[i-2].dir) continue;
				if(a[i-2].dir==1) a[i-1].lr=0;
				else a[i-1].lr=1;
			}
			else{
				a[i-1].dir=2;if(!a[i-2].dir) continue;
				if(a[i-2].dir==1) a[i-1].lr=1;
				else a[i-1].lr=0;
			}
		}
		else{
			tot+=(a[i-1].len=abs(mp[i].first-mp[i-1].first));
			if(mp[i].first>mp[i-1].first){
				a[i-1].dir=1;if(!a[i-2].dir) continue;
				if(a[i-2].dir==2) a[i-1].lr=0;
				else a[i-1].lr=1;
			}
			else{
				a[i-1].dir=3;if(!a[i-2].dir) continue;
				if(a[i-2].dir==2) a[i-1].lr=1;
				else a[i-1].lr=0;
			}
		}
	}
	init();for(register int i=2;i<=n;i++) solve(i);
	write(ans),putchar('\n');
	return 0;
}
```

码风较奇葩（~~压行强迫症+卡常小能手~~）

欢迎觉得做法很麻烦或有错误的巨佬来喷

---

## 作者：Chydz (赞：2)

容易想到，我们可以分别对每一个点进行模拟，找出从它开始要走到哪个点才能判断出位置。

对于能否判断当前点的位置，我们可以将从点 $i$ 顺时针走到点$1$经过的边长和点的度数拼在一起，连成一个字符串 $s(i)$。

注意某个点 $x$ 的度数是指：当前Bessie站在 $x$ 处，背对 $x-1$ ，准备向 $x+1$ 前进需要向左或是向右转，这里需要用到一点计算几何的基础知识。

将当前记录的信息也按此方式连成字符串 $ch$，若 $ch$ 仅仅只是某一个串 $s(i)$ 的前缀，说明通过当前记录的信息可以唯一确定出发的位置。然后就可以按照题目要求从当前位置走较短路到达终点。

判断是否为前缀就用hash进行处理。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#define ll long long
using namespace std;

const ll mod=2005060711;
int n,hs[205][205],mi[805],d1[205],d2[205],b[205],nxt[205],tot,ans;
struct dian{
	int x,y;
}t[205];
int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x*f;
}
int cross(dian p1,dian p2,dian p0){//计算几何基础知识
	return 1ll*(p1.x-p0.x)*(p2.y-p0.y)<1ll*(p2.x-p0.x)*(p1.y-p0.y);
}
int abss(int s){
	return s<0?-s:s;
}
int dis(int a,int b){
	if(t[a].x==t[b].x)return abss(t[a].y-t[b].y);
	return abss(t[a].x-t[b].x);
}
int ask(int x){
	int s=lower_bound(b+1,b+1+tot,x)-b;
	int a=0;
	while(s)s/=10;
	return a;
}
int main()
{
	n=read();
	mi[0]=1;
	for(int i=1;i<=800;i++)mi[i]=13ll*mi[i-1]%mod;
	for(int i=1;i<=n;i++){
		int x=read(),y=read();
		t[i]=(dian){x,y};
	}
	t[n+1]=t[1];
	for(int i=2;i<=n;i++)b[++tot]=dis(i,i-1);//离散化距离，用于hash 
	sort(b+1,b+tot);
	tot=unique(b+1,b+n)-b-1;
	//d1----顺时针到1的距离；d2----逆时针
	for(int i=2;i<=n;i++)d2[i]=d2[i-1]+dis(i,i-1);
	for(int i=n;i>=2;i--)d1[i]=d1[i+1]+dis(i,i+1);
	//nxt:0----向左转,1----向右转；nxt----这个点的转角
	for(int i=2;i<=n;i++)
		nxt[i]=cross(t[i],t[i+1],t[i-1]);
	for(int i=2;i<=n;i++){
		for(int j=i+1;j<=n+1;j++){
			ll x=dis(j-1,j)*13ll%mod+nxt[j];//将(j-1)=>(j)的距离和j的角度拼在一起
			x=(x>=mod)?x-mod:x;
			hs[i][j]=(hs[i][j-1]*mi[ask(dis(j-1,j))+1]%mod+x)%mod;
			//hs[]为hash数组，注意此处未将初始位置i的转角度数进行存储 
		}
	}
	for(int i=2;i<=n;i++){
		if(d1[i]<=d2[i])continue;//若i的较短路方向即为顺时针，则一定不会产生多余路程
		for(int j=i+1;j<=n+1;j++){
			int s=0;
			for(int k=2;k<=n;k++)
				if(nxt[k]==nxt[i]&&hs[k][j-i+k]==hs[i][j])s++;
				//判断是否为'k的前缀'，注意还有初始位置的转角 
			if(s==1){
				ans=max(ans,d1[i]-d1[j]+min(d2[j],d1[j])-d2[i]);
				break;
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：cwfxlh (赞：1)

# P3134
## [题面传送门](https://www.luogu.com.cn/problem/P3134)
本题的关键在于找到在行走多久后能够辨认出位置，那么我们可以用字符串来存储整个地图。  
具体的讲，因为这头牛在黑暗中所能感受到的只有这条路较上一条路的左转或右转（这里注意它是感受不到具体方向的，只有相对的方向变化），所以我们存地图的时候用转的方向和行走的距离进行描述。  
举个例子，样例中的图存过来就是 R10RR1RR10RR1RR10R。这个存图有一些的细节，大家可以自己去领悟一下，主要的两点就是：  
1. 边长的两侧要用方向包上，不然匹配的时候会出越界匹配的问题。   
2. 最后要把第一条边存上，因为它是个环。  

数据结构出来以后，其他的都好说了。开灯时牛走的路程可以前缀和处理出来。在黑暗中摸索的时候，每次往当前已知信息中加边就行了，已知信息也用和地图的方式表达成字符串，每次用 C++ string  的函数去找一下看是否出现多处匹配，如果只出现了一次，那么这个牛就可以确定自己位置了。（若是还有不懂可以参考代码食用）   
上代码：    
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x[2003],y[2003],pre[2003],ans,sum,sum2;
char fx[2003];
string mp,k1,k2;
void addmp(int X)
{
	k1="";
	while(X)
	{
		k1=(char)(X%10+'0')+k1;
		X/=10;
	}
	mp+=k1;
	return;
}
void addk1(int X)
{
	k2="";
	while(X)
	{
		k2=(char)(X%10+'0')+k2;
		X/=10;
	}
	k1+=k2;
	return;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d%d",&x[i],&y[i]);
	x[n+1]=x[1];
	y[n+1]=y[1];
	for(int i=1;i<=n;i++)
	{
		if(x[i+1]==x[i]&&y[i+1]>y[i])fx[i]='W';
		if(x[i+1]==x[i]&&y[i+1]<y[i])fx[i]='S';
		if(y[i+1]==y[i]&&x[i+1]>x[i])fx[i]='D';
		if(y[i+1]==y[i]&&x[i+1]<x[i])fx[i]='A';
	}
	fx[0]=fx[n];
	fx[n+1]=fx[n];
	x[n+2]=x[2];
	y[n+2]=y[2];
	for(int i=1;i<=n+1;i++)
	{
		if((fx[i-1]=='W'&&fx[i]=='A')||(fx[i-1]=='A'&&fx[i]=='S')||(fx[i-1]=='S'&&fx[i]=='D')||(fx[i-1]=='D'&&fx[i]=='W'))
		{
			mp+='L';
			addmp(abs(x[i]-x[i+1])+abs(y[i]-y[i+1]));
			mp+='L';
		}
		else
		{
			mp+='R';
			addmp(abs(x[i]-x[i+1])+abs(y[i]-y[i+1]));
			mp+='R';
		}
	}
	for(int i=2;i<=n+1;i++)
	{
		pre[i]=pre[i-1]+abs(x[i]-x[i-1])+abs(y[i]-y[i-1]);
	}
	fx[0]=fx[n];
	for(int i=2;i<=n;i++)
	{
		sum=min(pre[i],pre[n+1]-pre[i]);
		k1="";
		if((fx[i-1]=='W'&&fx[i]=='A')||(fx[i-1]=='A'&&fx[i]=='S')||(fx[i-1]=='S'&&fx[i]=='D')||(fx[i-1]=='D'&&fx[i]=='W'))
		{
			k1+='L';
		}
		else
		{
			k1+='R';
		}
		int j=i;
		sum2=0;
		while(mp.find(k1)!=mp.rfind(k1)&&j<=n)
		{
			addk1(abs(x[j+1]-x[j])+abs(y[j+1]-y[j]));
			sum2+=abs(x[j+1]-x[j])+abs(y[j+1]-y[j]);
			if((fx[j-1]=='W'&&fx[j]=='A')||(fx[j-1]=='A'&&fx[j]=='S')||(fx[j-1]=='S'&&fx[j]=='D')||(fx[j-1]=='D'&&fx[j]=='W'))
			{
				k1+='L';
			}
			else
			{
				k1+='R';
			}
			j++;
			if((fx[j-1]=='W'&&fx[j]=='A')||(fx[j-1]=='A'&&fx[j]=='S')||(fx[j-1]=='S'&&fx[j]=='D')||(fx[j-1]=='D'&&fx[j]=='W'))
			{
				k1+='L';
			}
			else
			{
				k1+='R';
			}
		}
		sum2+=min(pre[j],pre[n+1]-pre[j]);
		ans=max(ans,sum2-sum);
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：Violet___Evergarden (赞：1)

# 题意
给一个边平行于坐标轴的多边形，其中 $1$ 号点是出口，从某个点出发顺时针走，只记录点的内角与边长，知道记录的信息足够确定位置时，再沿着边走最短路到出口。要你计算这种走法比直接从那个点走最短路到起点会多走多少距离，求这个距离的最大值。
# 解法
STL 大法好！

**预处理**：枚举除 $1$ 以外的每个节点，让它一直顺时针走一直走到 $1$ 号点，用一个 ```vector``` 数组记录走过的角度和距离，然后再用一个 ```map``` 记录每一种 ```vector``` 的数量。

**计算**：枚举除 $1$ 以外的每个节点，和预处理一样顺时针走，用一个 ```vector``` 数组记录走过的角度和距离，走到每一个点时通过 ```map``` 判断该路径是否已经唯一，如果唯一，那么获得的信息就足够判断出点，此时直接计算已经走过的距离加从改点到 $1$ 的最短路减从原来的点到 $1$ 的最短路就能算出每个点的答案，最后取最大值即可。

# CODE
```cpp
#include <iostream>
#include <vector>
#include <map>
using namespace std;
const int kMaxN=201;
vector<int> path;
map<vector<int>,int>mp;
int x[kMaxN],y[kMaxN],n;
int dis[kMaxN],ans;
int Dis(int a,int b)//获得距离
{
  return abs(x[a]-x[b])+abs(y[a]-y[b]);
}
int Cj(int a,int b,int c)//获得角度（通过向量叉积判断左旋还是右旋）
{
  return (x[b]-x[a])*(y[c]-y[a])-(x[c]-x[a])*(y[b]-y[a]);
}
int main()
{
cin>>n;
for(int i=1;i<=n;i++)
{
  cin>>x[i]>>y[i];
}
for(int i=2;i<=n;i++)
{
  dis[i]=dis[i-1]+Dis(i-1,i);
}
dis[1]=dis[n]+Dis(n,1);
for(int i=2;i<=n;i++)//最开始走一遍，预处理map
{
  path.clear();
  for(int j=i;j<=n;j++)
  {
    int jiao=(Cj(j-1,j,(j==n?1:j+1))>0?1:0);
    path.push_back(jiao);
    mp[path]++;
    path.push_back(Dis(j,(j==n?1:j+1)));
  }
}
for(int i=2;i<=n;i++)//走第二遍，计算答案
{
  path.clear();
  for(int j=i;j<=n;j++)
  {
    int jiao=(Cj(j-1,j,(j==n?1:j+1))>0?1:0);
    path.push_back(jiao);
    if(mp[path]==1||j==n)
    {
      ans=max(ans,dis[j]-dis[i]+min(dis[j],dis[1]-dis[j])-min(dis[i],dis[1]-dis[i]));
      break;
    }
    path.push_back(Dis(j,(j==n?1:j+1)));
  }
}
cout<<ans;
return 0;
}
```

---

