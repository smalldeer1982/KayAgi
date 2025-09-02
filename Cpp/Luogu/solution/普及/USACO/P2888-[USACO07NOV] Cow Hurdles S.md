# [USACO07NOV] Cow Hurdles S

## 题目描述

Farmer John wants the cows to prepare for the county jumping competition, so Bessie and the gang are practicing jumping over hurdles. They are getting tired, though, so they want to be able to use as little energy as possible to jump over the hurdles.

Obviously, it is not very difficult for a cow to jump over several very short hurdles, but one tall hurdle can be very stressful. Thus, the cows are only concerned about the height of the tallest hurdle they have to jump over.

The cows' practice room has $N$ stations, conveniently labeled $1,\dots,N$. A set of $M$ one-way paths connects pairs of stations; the paths are also conveniently labeled $1,\dots,M$. Path $i$ travels from station $S_i$ to station $E_i$ and contains exactly one hurdle of height $H_i$. Cows must jump hurdles in any path they traverse.

The cows have $T$ tasks to complete. Task $i$ comprises two distinct numbers, $A_i$ and $B_i$, which connote that a cow has to travel from station $A_i$ to station $B_i$ (by traversing over one or more paths over some route). The cows want to take a path the minimizes the height of the tallest hurdle they jump over when traveling from $A_i$ to $B_i$ . Your job is to write a program that determines the path whose tallest hurdle is smallest and report that height.


Farmer John 想让她的奶牛准备郡级跳跃比赛，Bessie 和她的伙伴们正在练习跨栏。她们很累，所以她们想消耗最少的能量来跨栏。 显然，对于一头奶牛跳过几个矮栏是很容易的，但是高栏却很难。于是，奶牛们总是关心路径上最高的栏的高度。 

奶牛的训练场中有 $N$ 个站台，分别标记为 $1,\dots,N$。所有站台之间有 $M$ 条单向路径，第 $i$ 条路经是从站台 $S_i$ 开始，到站台 $E_i$，其中最高的栏的高度为 $H_i$。无论如何跑，奶牛们都要跨栏。 

奶牛们有 $T$ 个训练任务要完成。第 $i$ 个任务包含两个数字 $A_i$ 和 $B_i$，表示奶牛必须从站台 $A_i$ 跑到站台 $B_i$，可以路过别的站台。奶牛们想找一条路径从站台 $A_i$ 到站台 $B_i$，使路径上最高的栏的高度最小。 你的任务就是写一个程序，计算出路径上最高的栏的高度的最小值。


## 说明/提示

对于 $100\%$ 的数据，$1 \le N \le 300$，$1 \le M \le 2.5 \times 10^4$，$1 \le H_i \le 1 \times 10^6$，$1 \le T \le 4 \times 10^4$，$1 \le A_i,B_i \le N$。

感谢 @gaozhiyong @_Cppsteve_ 提供翻译


## 样例 #1

### 输入

```
5 6 3
1 2 12
3 2 8
1 3 5
2 5 3
3 4 4
2 4 8
3 4
1 2
5 1
```

### 输出

```
4
8
-1
```

# 题解

## 作者：沉辰 (赞：41)

再用佛洛依德进行新状态转移时，因为是以k作为中间点，所以牛跨过的最高高度是

max(d[i][k],d[k][j])，但是在i->j的整条路径上，跨过的最高高度应该最小，所以最后要取一个MIN，即d[i][j]=min(max(d[i][k],d[k][j]),d[i][j]);

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<map>
#include<queue>
#define mod 100000007
#define inf 336860180
#define PI 3.1415926
#define ll long long
using namespace std;
int T,s,t,n,m,d[400][400];
int main()
{
    memset(d,20,sizeof(d));
    scanf("%d%d%d",&n,&m,&T);
    for(int i=1;i<=m;i++)
    {
     int x,y,h;scanf("%d%d%d",&x,&y,&h);
      d[x][y]=h;    
    }
    for(int k=1;k<=n;k++)
     for(int i=1;i<=n;i++)
      for(int j=1;j<=n;j++)
       d[i][j]=min(max(d[i][k],d[k][j]),d[i][j]);
       //重点 
    for(int i=1;i<=T;i++)
    {
      int x,y;scanf("%d%d",&x,&y);    
      if(d[x][y]!=inf) cout<<d[x][y]<<endl;
      else cout<<"-1"<<endl;//不要忘记这种情况啊 
    }
    return 0;
}
```

---

## 作者：thoq (赞：17)

全都是floyd……谁说SPFA不行了？

#### Step1 SPFA暴力模板

对于每个出发点，跑一遍SPFA单源最短（其实是最高的栏最矮）路，代码如下（基本与单源最短路无区别，有区别已标注）：

```cpp
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 310
#define M 50010
#define inf 0x3f3f3f3f 
using namespace std;
int n,m,T,cnt,h[N],inque[N],d[N];
struct Edge
{
    int to,nxt,w;
}e[M];
void add(int u,int v,int wi)
{
    e[++cnt].to=v;
    e[cnt].w=wi;
    e[cnt].nxt=h[u];
    h[u]=cnt;
}
bool spfa(int s,int t)
{
    queue<int>q;
    memset(inque,0,sizeof(inque));
    memset(d,inf,sizeof(d));
    q.push(s);
    inque[s]=1;
    d[s]=0;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        inque[u]=0;
        for(int i=h[u];~i;i=e[i].nxt)
        {
            int v=e[i].to;
            if(d[v]>max(d[u],e[i].w))//此处，更新最长杆的最小值
            {
                d[v]=max(d[u],e[i].w);
                if(!inque[v])
                {
                    q.push(v);
                    inque[v]=1;
                }
            }
        }
    }
    return d[t]!=inf;
}
int main()
{
    memset(h,-1,sizeof(h));
    scanf("%d%d%d",&n,&m,&T);
    for(int i=1;i<=m;i++)
    {
        int si,ei,hi;
        scanf("%d%d%d",&si,&ei,&hi);
        add(si,ei,hi); 
    }
    for(int i=1;i<=T;i++)
    {
        int ai,bi;
        scanf("%d%d",&ai,&bi);
        if(spfa(ai,bi))printf("%d\n",d[bi]);
        else printf("-1\n");
    }
    return 0;
}
```

信心满满一交，结果……**TLE61**

#### Step2 记录！记录！记录！

看一下数据范围，T<=40000,而N<=300 !

也就是说，40000条询问最多只能从300个点出发，如果对于每次的出发点跑一遍SPFA，就做了39700次或更多重复的工作！

于是，自然地想到将答案记录下来，将d数组扩展到2维，新增vis数组判断a起点是否已走过，详见AC代码：

```cpp
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 310
#define M 50010
#define inf 0x3f3f3f3f 
using namespace std;
int n,m,T,cnt,h[N],inque[N],d[N][N],vis[N];
struct Edge
{
    int to,nxt,w;
}e[M];
void add(int u,int v,int wi)
{
    e[++cnt].to=v;
    e[cnt].w=wi;
    e[cnt].nxt=h[u];
    h[u]=cnt;
}
void spfa(int s)//发现不需要t，于是删了
{
    queue<int>q;
    memset(inque,0,sizeof(inque));
    memset(d[s],inf,sizeof(d[s]));//注意此处变更
    q.push(s);
    inque[s]=1;
    d[s][s]=0;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        inque[u]=0;
        for(int i=h[u];~i;i=e[i].nxt)
        {
            int v=e[i].to;
            if(d[s][v]>max(d[s][u],e[i].w))
            {
                d[s][v]=max(d[s][u],e[i].w);
                if(!inque[v])
                {
                    q.push(v);
                    inque[v]=1;
                }
            }
        }
    }
}
void print(int s,int t)
{
    if(d[s][t]==inf)printf("-1\n");
    else printf("%d\n",d[s][t]);
}
int main()
{
    memset(h,-1,sizeof(h));
    scanf("%d%d%d",&n,&m,&T);
    for(int i=1;i<=m;i++)
    {
        int si,ei,hi;
        scanf("%d%d%d",&si,&ei,&hi);
        add(si,ei,hi); 
    }
    for(int i=1;i<=T;i++)
    {
        int ai,bi;
        scanf("%d%d",&ai,&bi);
        if(!vis[ai])spfa(ai);//判断是否以ai为起点走过
        print(ai,bi);//输出，因为inf要输出-1，干脆写了个函数
        vis[ai]=1;//记录以ai为起点走过了
    }
    return 0;
}
```


---

## 作者：唔啊唔 (赞：10)

floyd模板，就不再多加解释了，直接上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,t,dis[1000][1000],a,b,c,x,y;
int main(){
	cin>>n>>m>>t;
	memset(dis,0x7f,sizeof(dis));	//一位大佬教给我的memset，此值无限接近int的最大值,等于0x7f7f7f7f 
	for(int i=1;i<=m;i++){
		cin>>a>>b>>c;
		dis[a][b]=c;
	}
	for(int k=1;k<=n;k++){	//模板稍加改动 
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				int s=max(dis[i][k],dis[k][j]);
				if(s!=0x7f7f7f7f&&s<dis[i][j]){	 
					dis[i][j]=s;
				}
			}
		}
	}
	for(int i=1;i<=t;i++){
		cin>>x>>y;
		if(dis[x][y]==0x7f7f7f7f){
			cout<<-1<<endl;
			continue;
		}
		cout<<dis[x][y]<<endl;
	}
	return 0;
}
```


---

## 作者：Starlight237 (赞：6)

本题解主要介绍一种floyd的优化方法：

注意到dp式中
$$f[i][j]=\min(f[i][j],\max(f[i][k],f[k][j]))$$
当$f[i][k]=\infty$时完全是在做无用功，因此我们在这种情况下可以跳过。

这种优化有什么效果呢？

对于本题，采用此类优化的程序为2019年提交的最优解，而在[牧场散步](https://www.luogu.org/problemnew/show/P2912)中，则直接关系到AC与否。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define reg register
#define IOSIZE 10000000
static char in[IOSIZE],*p=in,out[IOSIZE],*q=out,ch[20],*t=ch;
inline int read(){
    reg int x=0;
    while(*p<48)++p;
    while(*p>47)x=(x<<1)+(x<<3)+(*p++^48);
    return x;
}
inline void write(int x){
    x<0&&(*q++='-',x=-x);
    !x&&(*q++='0');
    while(x)*t++=x%10+48,x/=10;
    while(t!=ch)*q++=*--t;
}
static int n,m,Q,f[301][301];
int main(){
    fread(in,1,IOSIZE,stdin);
    n=read(),m=read(),Q=read();
    memset(f,0x3f,sizeof f);
    for(reg int i=1,u,v,w;i<=m;++i)
        u=read(),v=read(),w=read(),
        f[u][v]=w;
    for(reg int i=1;i<=n;++i)f[i][i]=0;
    for(reg int k=1;k<=n;++k)
        for(reg int i=1;i<=n;++i)
            if(f[i][k]!=0x3f3f3f3f)
                for(reg int j=1;j<=n;++j)
                    f[i][j]=min(f[i][j],max(f[i][k],f[k][j]));
    for(reg int u,v;Q;--Q)
        u=read(),v=read(),write(f[u][v]!=0x3f3f3f3f?f[u][v]:-1),*q++='\n';
    fwrite(out,1,q-out,stdout);
    return 0;
}
```

---

## 作者：ShineEternal (赞：3)

# 题目描述
  Farmer John 想让她的奶牛准备郡级跳跃比赛，贝茜和她的伙伴们正在练习跨栏。她们很累，所以她们想消耗最少的能量来跨栏。 显然，对于一头奶牛跳过几个矮栏是很容易的，但是高栏却很难。于是，奶牛们总是关心路径上最高的栏的高度。 奶牛的训练场中有 N (1 ≤ N ≤ 300) 个站台，分别标记为1..N。所有站台之间有M (1 ≤ M ≤ 25,000)条单向路径，第i条路经是从站台Si开始，到站台Ei，其中最高的栏的高度为Hi (1 ≤ Hi ≤ 1,000,000)。无论如何跑，奶牛们都要跨栏。 奶牛们有 T (1 ≤ T ≤ 40,000) 个训练任务要完成。第 i 个任务包含两个数字 Ai 和 Bi (1 ≤ Ai ≤ N; 1 ≤ Bi ≤ N)，表示奶牛必须从站台Ai跑到站台Bi，可以路过别的站台。奶牛们想找一条路径从站台Ai到站台Bi，使路径上最高的栏的高度最小。 你的任务就是写一个程序，计算出路径上最高的栏的高度的最小值。
# 题目分析：
咋一看，一股浓浓的最短路气息扑面而来，首先考虑dijkstra，发现单源最短路并不适用于多个起点，于是把目光投向了数据范围。

## $n\leq300$?

难，难道这就是传说中的的Floyd？
做梦都想用呀（~~虽然现在主攻dijkstra了~~）
别急，事情并不是你想象的那么简单。细看题目，我们发现要求出的结果是最高的栏杆，而不是栏杆高度之和！
其实不就是把转移式换一下吗。。。
所以和谐的状态转移方程就出来了：

##  $ f[i][j]=fmin(f[i][j],fmax(f[i][k],f[k][j]));(1<=k,i,j<=n)$

这个式子中因为要取最大值，所以每两个栏杆是要客观的取最大值（题意），而线路的最高栏杆我们就能主观的取最小值喽。

然后就是代码：

# [代码](https://blog.csdn.net/kkkksc03/article/details/83152203)

---

## 作者：Martian148 (赞：2)

### 咋一看，一股浓浓的最短路气息扑面而来，首先考虑SPFA，发现单源最短路并不适用于多个起点，于是把目光投向了数据范围。

# n≤300?
###### 难，难道这就是传说中的的Floyd？
做梦都想用呀（虽然现在主攻SPFA了）
别急，事情并不是你想象的那么简单。细看题目，我们发现要求出的结果是最高的栏杆，而不是栏杆高度之和！
其实不就是把转移式换一下吗。。。
所以和谐的状态转移方程就出来了:

##### 定义dis[i][j]表示从i到j的最长杆，肯定在dis[i][k]和dis[k][j]中

于是

## dis[i][j]=min(dis[i][j],max(dis[i][k],dis[k][j]));(其中1<=k,i,j<=n)
```cpp

#include<bits/stdc++.h>
using namespace std;
int n,m,t,dis[305][305],INF; 
int read(){
    int ret=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
    while(ch<='9'&&ch>='0')ret=ret*10+ch-'0',ch=getchar();
    return ret*f;
}
int main(){
//    freopen("NOIP.in","r",stdin);
//    freopen("NOIP.out","w",stdout);
    n=read(),m=read(),t=read();
    memset(dis,63,sizeof dis);INF=dis[0][0];
    for(int i=1;i<=m;i++){
        int s=read(),e=read(),h=read();
        dis[s][e]=h;
    }
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++){
                dis[i][j]=min(dis[i][j],max(dis[i][k],dis[k][j]));
            }
    for(int i=1;i<=t;i++){
        int x=read(),y=read();
        if(dis[x][y]==INF)printf("-1\n");
        else printf("%d\n",dis[x][y]);
    } 
    return 0;
} 
```

# 这个P的题是真的水！

---

## 作者：万弘 (赞：2)

不特别困难，主要是要看出用Floyed即可，40000的询问提示还是比较明显的

用一个$f[i][j]$数组存储i,j间最高的栏的高度的最小值

$f[i][j]=min(f[i][j],max(f[i][k],f[k][j])$

两个要点：

1：f要初始化为INF(一个很大的数，我们认为是无穷大），输出时如果答案是INF要输出-1  
2:这是**有向图！**（所幸有样例数据）

时间$O(n^3+m+t)$空间$O(n^3)$

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
typedef long long ll;//不开long long见祖宗
const ll INF=1ll<<60;//一个很大的数，注意会爆int
ll n,m,t;
ll f[501][501];
ll max(ll a,ll b)//我习惯手写max&min
{
    return a>b?a:b;
}
ll min(ll a,ll b)
{
    return a<b?a:b;
}
void fir()//初始化&图的输入
{
    ll u,v,w;
    scanf("%lld%lld%lld",&n,&m,&t);//研究表明scanf快于cin
    for(ll i=1;i<=n;++i)
        for(ll j=1;j<=n;++j)f[i][j]=INF;
    for(ll i=1;i<=m;++i)
    {
        scanf("%lld%lld%lld",&u,&v,&w);
        f[u][v]=min(f[u][v],w);//防重边
    }
}
void work()//Floyed
{
    for(ll k=1;k<=n;++k)
        for(ll i=1;i<=n;++i)
            for(ll j=1;j<=n;++j)
                f[i][j]=min(f[i][j],max(f[i][k],f[k][j]));
}
void end()//最后一问一答即可
{
    ll u,v;
    for(ll i=1;i<=t;++i)
    {
        scanf("%lld%lld",&u,&v);
        printf("%lld\n",f[u][v]==INF?-1ll:f[u][v]);
    }
}
int main()
{
    fir();
    work();
    end();
    return 0;
}
```

还有不懂可私信我

---

## 作者：zpf_13516358919 (赞：2)

floyed 的稍作改动，只要小改状态转移方程

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iomanip>
#define LL long long
const int INF=0x7fffffff;
LL map[310][310];
int n,m,t,x,y,v;
using namespace std;
int main()
{
    scanf("%d%d%d",&n,&m,&t);
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    map[i][j]=INF;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&x,&y,&v);
        map[x][y]=v;
    }
    for(int k=1;k<=n;k++)
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    if(map[i][j]>max(map[i][k],map[k][j]))//算法的精髓
    map[i][j]=max(map[i][k],map[k][j]); 
         //从i到j的两条大路径i->k和k->j中找最大值，并且和map[i][j]比较大小 
    for(int i=1;i<=t;i++)
    {
        scanf("%d%d",&x,&y);
        if(map[x][y]==INF)
        printf("-1\n");
        else
        printf("%d\n",map[x][y]);
    }
    return 0;
}

```

---

## 作者：k2saki (赞：1)

首先：看数据范围
### 1 ≤ N ≤ 300
再看题意：求i点到j点，奶牛需要跳过的最高的栏的高度的最小值

看完题后5秒钟，我发现：这个题就是floyd模板的一个变形(O(n³)不会TLE)

## Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,p;
int f[333][333];//f[i][j]表示i点到j点跳过的最高的栏高度的最小值
int main() {
	cin>>n>>m>>p;
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=n;++j)
		{
			f[i][j]=1234567;//初始化，如果无法通过，f[i][j]就等于1234567
		}
	}
	for(int i=1;i<=m;++i)
	{
		int a,b,c;
		cin>>a>>b>>c;
		f[a][b]=c;
	}
	for(int k=1;k<=n;++k)
	{
		for(int i=1;i<=n;++i)
		{
			for(int j=1;j<=n;++j)
			{
				f[i][j]=min(f[i][j],max(f[i][k],f[k][j]));//核心，如果max(f[i][k],f[k][j])比原来的f[i][j]要小，就改变它
			}
		}
	}
	for(int i=1;i<=p;++i)
	{
		int u,v;
		cin>>u>>v;
		if(f[u][v]!=1234567) cout<<f[u][v]<<endl;//别忘了判断是否打得到
		else cout<<-1<<endl;
	}
	return 0;
}

```





---

## 作者：SBS苏 (赞：1)

水题，依照题意建图，跑一边弗洛伊德算法即可。


/\*User:S.B.S.\*/

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#include<cstdlib>
#include<iomanip>
#include<cassert>
#include<climits>
#include<functional>
#include<bitset>
#include<vector>
#include<list>
#include<map>
#define maxn 500
#define F(i,j,k) for(int i=j;i<k;i++)
#define M(a,b) memset(a,b,sizeof(a))
#define FF(i,j,k) for(int i=j;i>=k;i--)
#define inf 0x3f3f3f3f
#define maxm 1001
#define mod 998244353
//#define LOCAL
using namespace std;
int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,m,t;
int mp[maxn][maxn];
inline void floyd()
{
    F(k,0,n)F(i,0,n){
        if(mp[i][k]==inf) continue;
        F(j,0,n){
            int mx;
            if(mp[k][j]==inf) continue;
            if(mp[i][k]>mp[k][j]) mx=mp[i][k];
            else mx=mp[k][j];
            if(mx<mp[i][j]) mp[i][j]=mx;
        }
    }
}
int main()
{
    std::ios::sync_with_stdio(false);//cout<<setiosflags(ios::fixed)<<setprecision(1)<<y;
    #ifdef LOCAL
    freopen("data.in","r",stdin);
    freopen("data.out","w",stdout);
    #endif
    cin>>n>>m>>t;
    F(i,1,n)F(j,0,i) mp[i][j]=mp[j][i]=inf;
    F(i,0,m){
        int a,b,c;
        cin>>a>>b>>c;a--;b--;
        mp[a][b]=c;
    }
    floyd();
    F(i,0,t){
        int x,y;
        cin>>x>>y;x--;y--;
        if(mp[x][y]==inf) cout<<"-1"<<endl;
        else cout<<mp[x][y]<<endl;
    }
    return 0;
}

```

---

## 作者：不存在之人 (赞：0)

### 题意：

一条路首先保证栅栏最低的最短路

### 分析：

这时稍微分析一下，考虑$i$到$j$这条路径的时候，它的答案一定是它本身与从$i$到$j$另外的路径上的站台高度的最大值。所以如果我们将最短路的定义改为这条路径上最高的栅栏的高度，那么根据上面的分析，更新答案的时候就为

$dis[i][j]=min(dis[i][j],max(dis[i][k],dis[k][j]));$

如上方叙述执行$floyd$，即可在$n^3$的时间内求出所有路径的答案，最后每组询问$o(1)$出解即可

### 代码实现：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 305
#define INF 1e8
using namespace std;
int n,m,k1;
int dis[maxn][maxn];
int main()
{
    memset(dis,0x3f,sizeof(dis));
    scanf("%d%d%d",&n,&m,&k1);
    for(int i=1;i<=m;i++)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        dis[x][y]=z;
    }
    for(int k=1;k<=n;k++)
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    if(i!=k&&k!=j&&i!=j)
    {
        if(dis[i][k]<INF&&dis[k][j]<INF)
        {  
            dis[i][j]=min(dis[i][j],max(dis[i][k],dis[k][j]));
		}
    }
    for(int i=1;i<=k1;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(dis[x][y]>INF)
        {
            printf("-1\n");
            continue;
        }
        printf("%d\n",dis[x][y]);
    }
    return 0;
}
```

---

## 作者：Palind_Rome (赞：0)

哈哈哈今天第二次学Floyd

正好老师讲了这道题，但我和老师习惯不同，我习惯下标从一开始，然后一个小bug改了很久qwq

```cpp
#include<iostream>
using namespace std;
int fl[501][501];
int main(){
	int n,m,t,a,b,d,i,j,k;
	cin>>n>>m>>t;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			fl[i][j]=1000000000;//因为没有自己站台到自己站台，所以不需要判断。
	for(i=1;i<=m;i++){
		cin>>a>>b>>d;
		fl[a][b]=d;//有向图
	}
    //Floyd
	for(k=1;k<=n;k++)
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
				if(fl[i][k]!=1000000000&&fl[k][j]!=1000000000)//怕溢出233
					fl[i][j]=min(fl[i][j],max(fl[i][k],fl[k][j]));
	for(i=1;i<=t;i++){
		cin>>a>>b;
		if(fl[a][b]!=1000000000)cout<<fl[a][b]<<endl;
		else cout<<-1<<endl;//它要是没变一定没有路
	}
	return 0;
}
```

---

## 作者：xukuan (赞：0)

这是一个 #有向图！

floyd之后直接输出两点距离，但不要忘了初始化








```cpp
uses math;
type
 arr=array[0..310,0..310] of longint;
var
 i,j,n,m,t,s,e,ai,bi:longint;
 a:arr;
procedure floyd;
 var
  i,j,k:longint;
 begin
  for k:=1 to n do
   for i:=1 to n do
    for j:=1 to n do
     a[i,j]:=min(a[i,j],max(a[i,k],a[k,j]));//注意函数
  for i:=1 to n do a[i,i]:=0;
end;
begin
 readln(n,m,t);
 for i:=1 to n do
  for j:=1 to n do
   a[i,j]:=maxlongint;//关键的初始化
 for i:=1 to m do
  begin
   read(s,e);
   readln(a[s,e]);//不能合并为readln(s,e,a[s,e]),不然全0；
  end;
 floyd;
 for i:=1 to t do
  begin
   readln(ai,bi);
   if a[ai,bi]=maxlongint then writeln(-1)//走不到
                          else writeln(a[ai,bi]);
  end;
end.

```

---

## 作者：hututu (赞：0)


```cpp
#include<iostream>
#include<cstring>
using namespace std;
int a[1001][1001];
int maxn;
int main()
{
    int n,m,t;
    cin>>n>>m>>t;
    memset(a,0x7f,sizeof(a));     //初始化 
    for(int i=1;i<=m;i++)
    {
        int x,y,z;
        cin>>x>>y>>z;         //输入路径 
        a[x][y]=z;
    }
    for(int k=1;k<=n;k++)        //弗洛伊德算法 
    {
        for(int i=1;i<=n;i++)
        {
            if(a[i][k]>1000000) continue;      //没有连边直接跳过 
            for(int j=1;j<=n;j++)
            {
                if(a[k][j]>1000000) continue;       ////没有连边直接跳过 
                if(a[i][k]>a[k][j]) maxn=a[i][k];     //比较更新 
                else maxn=a[k][j];
                if(a[i][j]>maxn) a[i][j]=maxn;
            }
        }
    }
    for(int i=1;i<=t;i++)
    {
        int x,y;
        cin>>x>>y;                  //输出两点之间最小值 
        if(a[x][y]<1000000000)
        {
            cout<<a[x][y]<<endl;
        }
        else cout<<-1<<endl;       //如果无法到达，输出 -1
    }
    return 0;
}

```

---

## 作者：JasonZRY (赞：0)

这是一道弗洛伊德最短路问题

不用多说，状态转移方程加三重循环就A了

```
#include<bits/stdc++.h>
using namespace std;
int n,m,t,f[301][301],a,b,u,v,w;                            //u是起始站台，v是终点站台，w是牛栏的高度 
int main(){
    memset(f,127,sizeof(f));                                //初始化 
    cin>>n>>m>>t;
    for(int i=1;i<=m;i++){
        cin>>u>>v>>w;
        f[u][v]=w;                                          //把一条头为u，尾为v的边赋值为w 
    }
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                f[i][j]=min(f[i][j],max(f[i][k],f[k][j]));  //直接了当的状态转移方程，完美 
            }
        }
    }
    for(int i=1;i<=t;i++){                                  //t次查询 
        cin>>a>>b;
        if(f[a][b]==f[0][0])cout<<-1<<endl;                 //如果不能到达就输出-1 
        else cout<<f[a][b]<<endl;                           //不然就输出最小值 
    }
    return 0; 
}
```

---

## 作者：睿屿青衫 (赞：0)

声明一下，我最开始21分，借鉴了一下@zpf\_13516358919题解赋值那一部分，且把int改成了long long（#define ll long long定义ll代表long long）


弗洛伊德变一下形，很容易想出来，输出的时候别忘了是lld（虽然我没试过int会不会炸）


强调一下，memset最少慎用！容易出毛病！（如果你打spfa的题目就会发现，特别是初始化一个大的数）


该注意的点也该说完了吧，那就贴代码(每个人风格都不同，在此提供一下，切勿抄袭):

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
#define maxn 1010
#define INF 0x7fffffff
using namespace std;
ll n,m,t,dis[1010][1010];
int main()
{
    ios::sync_with_stdio(false);//cin读入优化（如果你背了别人自定义函数的读入优化注意点，可能会出错，最好找神犇抄一下）
    cin>>n>>m>>t;
    for(int i=1;i<=n;++i)
     for(int j=1;j<=n;++j)
      dis[i][j]=INF;
    for(int i=1;i<=m;++i)
    {
        int a,b,c;
        cin>>a>>b>>c;
        dis[a][b]=c;
    }
    for(int k=1;k<=n;++k)
     for(int i=1;i<=n;++i)
      for(int j=1;j<=n;++j)
       if(dis[i][j]>max(dis[i][k],dis[k][j]))
        dis[i][j]=max(dis[i][k],dis[k][j]);//弗洛伊德，很短的几句代码
    for(int i=1;i<=t;++i)
    {
        int a,b;
        cin>>a>>b;
        if(dis[a][b]==INF) printf("-1\n");//特判输出情况
         else printf("%lld\n",dis[a][b]);//一定别炸int
    }
    return 0;
}
```

---

