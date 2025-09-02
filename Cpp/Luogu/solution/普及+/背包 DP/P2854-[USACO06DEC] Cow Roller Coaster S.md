# [USACO06DEC] Cow Roller Coaster S

## 题目描述

有 $n$ 条线段，每条线段只能放在数轴上的一个特定位置，并且第 $i$ 根线段有如下几个属性：$X_i$（该线段放在数轴上的起点），$W_i$（该线段长度），$F_i$（你若使用该线段你能获得的价值），$C_i$（你若使用该线段你所需要的费用）。现在让你从中选出一些线段，使得这些线段能够铺满数轴上的区间 $[0,L]$ 且线段必须首尾相接（也就是不能重叠，也不能空缺），并且所花费用和不超过 $B$，同时要使你收获的价值尽量大，请你找到这个方案。

## 样例 #1

### 输入

```
5 6 10
0 2 20 6
2 3 5 6
0 1 2 1
1 1 1 3
1 2 5 4
3 2 10 2```

### 输出

```
17```

# 题解

## 作者：糪眾脦颰罷 (赞：28)

# 与背包问题类似

## 核心内容：

**f[i][j]的意义：坐标为0~i的连续轨道中， 使用成本为j时的最大乐趣值。**

**状态转移方程：f[xi+wi][j+ci]=max(f[xi][j]+fi,f[xi+wi][j+ci])(1<=i<=n,0<=j<=b-ci)**

注：需保证此时0~xi+wi均有轨道连着，这个技巧下面会讲到

## 基本步骤：

1.初始化二维数组f的值为**-1**(当没有可行方案时，是输出-1的，~~这点不知道为什么没翻译出来~~)并且f[0][0]=0

2.用结构体储存每根轨道的xi,wi,fi和ci

3.用sort按xi从小到大排序(方便dp)

4.dp中，当f[xi][j]不为-1时，进行状态转移，因为f[xi][j]等于-1说明没有轨道从起点一直连到xi(这就保证了0~xi+wi均有轨道连着)

5.输出f[l][i] (0<=i<=b)中的最大值

## 代码一波

```
#include<bits/stdc++.h>
using namespace std;
int l,n,b,f[1001][1001],ans=-1;
struct FT{
    int st;
    int ed;
    int f;
    int v;
};
FT p[100001];
bool cmp(FT a1,FT a2){
    return a1.st<a2.st;
}
int main(){
    scanf("%d %d %d",&l,&n,&b);
    memset(f,-1,sizeof(f));
    for(int i=1;i<=n;i++){
        int b;
        scanf("%d %d %d %d",&p[i].st,&b,&p[i].f,&p[i].v);
        p[i].ed=p[i].st+b;
    }
    sort(p+1,p+1+n,cmp);
    f[0][0]=0;
    for(int i=1;i<=n;i++){
    	for(int j=0;j<=b-p[i].v;j++){
    		if(f[p[i].st][j]!=-1)f[p[i].ed][j+p[i].v]=max(f[p[i].ed][j+p[i].v],f[p[i].st][j]+p[i].f);
        }
    }
    for(int i=0;i<=b;i++)ans=max(ans,f[l][i]);
    cout<<ans;
    return 0;
}
```

## [提交记录](https://www.luogu.org/record/show?rid=13204914)

104ms / 5.4MB 

代码：0.71KB C++

---

## 作者：2017gangbazi (赞：10)

排序？不存在的！

多好的一道动规题。

"万物皆可DP"

读题，可以想到基本的转移方程 

f [i] [j] = max(f[ i-l[x] ] [ j-c[x] ] + h[i];

其中 f[i][j]表示在i位置，已经用了j的成本，最多可以获得多少乐趣值

与楼上大佬们不同的是，开一个** vector [i] 记录到i点结束的钢轨编号**

这样，在枚举钢轨时，直接读取到i点结束的钢轨编号，进行填表即可

具体见代码


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=10001;

int l,n,b,ans;

int f[1001][1001];

vector<int>t[maxn];

int len[maxn],c[maxn],h[maxn];


int main() {
	scanf("%d%d%d",&l,&n,&b);
	for(int i=1; i<=n; i++) {
		int st;
		scanf("%d%d%d%d",&st,&len[i],&h[i],&c[i]);
		t[st+len[i]].push_back(i);
	}
	for(int i=0; i<=l; i++) {
    
		for(int j=0; j<=b; j++) {
        
			for(int k=0; k<t[i].size(); k++) {
            
				int r=t[i][k];//r为连接着i的钢轨编号
				if(i-len[r]>=0&&j-c[r]>=0) {//满足条件
                
					if(i-len[r]!=0&&!f[i-len[r]][j-c[r]])continue;
                    //很重要，这里解释一下
                    //思考一下，都什么样的钢轨能够修改该点的最优值？
                    //只有从起点一个一个连接过来的才可以
                    //不然不能保证是从起点连接过来
                    //这个地方卡了很久，建议自己画图想一下
					f[i][j]=max(f[i][j],f[i-len[r]][j-c[r]]+h[r]);
                    
				}
			}
		}
	}
	for(int i=0; i<=b; i++)ans=max(ans,f[l][i]);
    //找最优解，在n点成本≤b的都可以
	printf("%d",(ans>0?ans:-1));//特判-1
}
/*

5 5 10
0 2 20 6
2 3 5 6
0 1 2 1
1 2 5 4
3 2 10 2
*/
```


------------
~~很认真的一篇题解 希望通过~~

不懂的可以私信我

---

## 作者：BinDir0 (赞：9)

## 就是一个背包dp哦qwq

第一维是起点，第二维是成本呢


```cpp
#include<bits/stdc++.h>
using namespace std;
struct item
{
    int a,b,v,w;
}h[12000];
int l,m,n,dp[1220][1220],ans;
int cmd(item x,item y)
{
    return x.a<y.a;
}
int main()
{
    cin>>l>>n>>m;
    for(int i=1;i<=n;i++)
    cin>>h[i].a>>h[i].b>>h[i].w>>h[i].v;
    /*for(int i=1;i<=n;i++)
    {
        for(int j=a[i];j<=a[i]+b[i];j++)
        {
            for(int k=m;k>=v[i];k--)
            {
                dp[j][k]=max(dp[j][k],dp[j][k-v[i]]+w[i]);
            }
        }
    }*/
    sort(h+1,h+n+1,cmd);
    for(int i=1;i<=n;i++)
    {
        for(int k=m;k>=h[i].v;k--)
        {
            if(h[i].a!=0&&dp[h[i].a][k-h[i].v]==0)
            continue;
            dp[h[i].a+h[i].b][k]=max(dp[h[i].a+h[i].b][k],dp[h[i].a][k-h[i].v]+h[i].w);
        }
    }
    for(int i=1;i<=m;i++)
    {
        ans=max(ans,dp[l][i]);
    }
    if(ans!=0)
    cout<<ans;
    else
    cout<<-1;
    
    return 0;
}

```

---

## 作者：maorui_cow (赞：6)

很容易想到,只是一道背包题

但是这道题有两个条件，长度，成本，所以会想到三重循环背包

[like this->](https://www.luogu.org/problem/P1507)

但，对比数据

前者，N(1≤N≤10000)

后者，N(<50）

呵呵呵，所以显然不行

但仔细想一想

我们用dp[i][j]表示付出i成本，当前终点为j，得到的最大有趣指数

于是，很容易想出dp

```
	for(int i=1;i<=n;i++)
	{
		for(int j=b;j>=a[i].c;j--)
		{
			if(dp[j-a[i].c][a[i].x]>0||a[i].x==0)
			{
				dp[j][a[i].x+a[i].w]=max(dp[j][a[i].x+a[i].w],dp[j-a[i].c][a[i].x]+a[i].f);//先看这里
			}
		}
	}
```

这样就不要多写一重循环

但有很多细节

1.因为铁轨要连续，所以铁轨要按照起点排序

2.如果所有铁轨起点都没有含0的，输出无解

3.如果中间有铁轨不连续，不能做背包

		所以才有这一段
        
		if(dp[j-a[i].c][a[i].x]>0||a[i].x==0)


4.答案可以满足任意成本情况，但终点一定要是L


上代码


```
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int x;
	int w;
	int f;
	int c;
}a[10005];
int dp[10005][1005];
int cmp(node a,node b)
{
	return a.x<b.x;
}
int main()
{
	int l,n,b;
	scanf("%d%d%d",&l,&n,&b);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d%d",&a[i].x,&a[i].w,&a[i].f,&a[i].c);
	}
	sort(a+1,a+1+n,cmp);
	if(a[1].x!=0)
	{
		printf("-1\n");
		return 0;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=b;j>=a[i].c;j--)
		{
			if(dp[j-a[i].c][a[i].x]>0||a[i].x==0)
			{
				dp[j][a[i].x+a[i].w]=max(dp[j][a[i].x+a[i].w],dp[j-a[i].c][a[i].x]+a[i].f);
			}
		}
	}
	int ans=0;
	for(int i=1;i<=b;i++)
	{
		ans=max(ans,dp[i][l]);
	}
	if(ans==0)
	{
		printf("-1\n");
		return 0;
	}
	printf("%d\n",ans);
	return 0;
}

```



---

## 作者：沉辰 (赞：6)

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<map>
#include<queue>
#define mod 100000007
#define inf 21474347
#define PI 3.1415926
#define ll long long
using namespace std;
ll l,n,m,ans,f[1002][1002];//f[i][j]表示长度为i,花费为j的最大欢乐值 
struct po{ll x,w,f,c;}a[10009];
bool cmp(po xx,po yy){return xx.x<yy.x;} 
int main()
{
    scanf("%lld%lld%lld",&l,&n,&m);
    for(ll i=1;i<=n;i++)
     scanf("%lld%lld%lld%lld",&a[i].x,&a[i].w,&a[i].f,&a[i].c);    
    sort(a+1,a+n+1,cmp);//必须要排序才能满足无后效性原则 
    memset(f,-1,sizeof(f));//初始化，无解的情况包含在里面了 
    ans=-inf;
    f[0][0]=0;//显而易见的初始化 
    for(ll i=1;i<=n;i++)
    {
     ll u=a[i].x;//开始 
     ll v=a[i].x+a[i].w;//结束 
     for(ll j=m;j>=a[i].c;j--)
      if(f[u][j-a[i].c]!=(-1)) 
      //只有当起点被选中的时候才能去更新终点 
       f[v][j]=max(f[u][j-a[i].c]+a[i].f,f[v][j]);//终点取最优 
    }
    for(ll i=0;i<=m;i++)//因为不知道花费多少钱得到的欢乐值是最大的，所以要扫一遍 
     ans=max(ans,f[l][i]);
    cout<<ans;
    return 0;
}
```

---

## 作者：斗神_君莫笑 (赞：5)

本题就是背包的变种  
注意事项就是每个钢轨首尾相接，不能重叠或中断  
代码具体为(起点为0||之前有钢轨)  
因为有趣度为正整数，因此可以判断有趣度是否为0   
然后就是排序后基础的背包了  
因为翻译的锅，可能题意有些恶心  
```cpp
#include<bits/stdc++.h>
using namespace std;
long long f[1010][1010];//(i条)到j位置k成本的w 
struct Point{
	int st,len,v,w;
}a[10010];
int st[10010],len[10010],v[10010],w[10010];
bool cmp(const Point &x,const Point &y){
	if(x.st==y.st)return x.len<y.len;
	return x.st<y.st;
}
int main(){
	int n,m,b;
	scanf("%d%d%d",&b,&n,&m);
	for(register int i=1;i<=n;++i)
		scanf("%d%d%d%d",&a[i].st,&a[i].len,&a[i].w,&a[i].v);
	sort(a+1,a+n+1,cmp);
	for(register int i=1;i<=n;++i){
		st[i]=a[i].st;
		len[i]=a[i].len;
		v[i]=a[i].v;
		w[i]=a[i].w;
	}
	for(register int i=1;i<=n;++i){
		int length=st[i]+len[i];
		for(register int j=m;j>=v[i];--j)
			if(!st[i]||f[st[i]][j-v[i]])
				f[length][j]=max(f[length][j],f[st[i]][j-v[i]]+w[i]);
	}	
	long long ans=0;
	for(register int i=0;i<=m;++i)
		ans=max(ans,f[b][i]);
	if(ans==0)ans=-1;
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：AnChun999 (赞：3)

看了一下题解没有搜索，就写了一个

暴搜80分
下面是**八十分**代码
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<string>
using namespace std;
int idline[1100][11000];
int l,n,b;
int ans=-1;
struct asd
{
    int x,w,f,c;
}a[11000];

int cmp(asd a,asd b)
{
    return a.f>b.f;
}

int dfs(int id,int money,int funny)
{
    if(money>b)//限制条件① 
    return 0;
    
    if(a[id].w+a[id].x==l)//到达 
    {
        ans=max(funny,ans);
        return 0;
    }
    
    for(int i=1;i<=idline[a[id].w+a[id].x][0];i++)
    {
        int start=a[id].w+a[id].x;
        dfs(idline[start][i],money+a[idline[start][i]].c,funny+a[idline[start][i]].f);
    }
}
int main()
{
    scanf("%d%d%d",&l,&n,&b);
    for(int i=1;i<=n;i++)
    scanf("%d%d%d%d",&a[i].x,&a[i].w,&a[i].f,&a[i].c);
    
    sort(a+1,a+n+1,cmp);
    
    for(int i=1;i<=n;i++)
    {
        idline[a[i].x][0]++;
        idline[a[i].x][idline[a[i].x][0]]=i;
    }
    
    dfs(0,0,0);
    
    printf("%d",ans);
    return 0;
}
```

下面是
剪枝代码
剪完AC，解释都在代码里



```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<string>
using namespace std;
int idline[1100][11000],f[1100];//idline建图 
int l,n,b;
int ans=-1;//无解情况为-1； 
struct asd//建立结构体 
{
    int x,w,f,c;//x为起点，w为长度，f为有趣程度，c为成本 
}a[11000];

int cmp(asd a,asd b)//比较结构体里的有趣程度，有趣程度高的优先选择，为剪枝做准备 
{
    return a.f>b.f;
}

int dfs(int id,int money,int funny)
{
    if(money>b)//当前id轨道建成后，超出预算就退出 
    return 0;
    
    if(funny<f[a[id].x+a[id].w])//重要剪枝，没了就tle俩点 
    return 0;
	/*
	当前轨道建立完毕后，且预算不会超出，且有趣程度比“前辈”（过去到了这个距离的前辈）大
	就记录其有趣程度在记录榜f数组里。 
	*/ 
    f[a[id].x+a[id].w]=funny;
    
    if(a[id].w+a[id].x==l)//到了终点就记录 
    {
        ans=max(funny,ans);
        return 0;
    }
    
    for(int i=1;i<=idline[a[id].w+a[id].x][0];i++)//当前id轨道建立完毕后，以此为起点，开始dfs 
    {
        int start=a[id].w+a[id].x; 
        dfs(idline[start][i],money+a[idline[start][i]].c,funny+a[idline[start][i]].f);//这个要慢慢理解啦
    }
}
int main()
{
    scanf("%d%d%d",&l,&n,&b);//读入长度，轨道数，预算 
    for(int i=1;i<=n;i++)//每条轨道 
    scanf("%d%d%d%d",&a[i].x,&a[i].w,&a[i].f,&a[i].c);
    
    sort(a+1,a+n+1,cmp);//排序有趣 
    
    for(int i=1;i<=n;i++)//图 
    {
        idline[a[i].x][0]++;//计数 
        idline[a[i].x][idline[a[i].x][0]]=i;//计数每个轨道的起点，因为之前排序，所以这时候idline数组里的有趣程度为降序 
    }
    
    dfs(0,0,0);//一条轨道都没有的情况下，有趣程度为0，花费为0 
    
    printf("%d",ans);//输出答案 
    return 0;
}
```

---

## 作者：moosssi (赞：2)

一道简单的dp+背包的题

状态方程 $f[i][j]$ 表示：完成 $0$ 到 $i$ 之间钢轨拼接，花费为 $j$  ，有趣和最大值。

转移方程：$dp[i+w][k]$ $=max$（$dp[i+w][k],dp[i][k-c]+f$）。

其它处理：定义一个vector数组，以每个钢轨的起点为下标，把其它信息存进去。
遍历每个位置，枚举位置上的钢轨，再套用完全背包即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
typedef long long ll;
struct nod{
	int w,f,c;
}a[N*10];
int l,n,b;
ll dp[N][N];
vector<nod>q[N];
int main(){
	scanf("%d%d%d",&l,&n,&b);
	for(int i=1;i<=n;i++){
		int x;
		scanf("%d%d%d%d",&x,&a[i].w,&a[i].f,&a[i].c);
		q[x].push_back(a[i]);
	}
	memset(dp,-0x3f,sizeof(dp));
	dp[0][0]=0;
	for(int i=0;i<=l;i++){
		for(int j=0;j<q[i].size();j++){
			int w=q[i][j].w,c=q[i][j].c,f=q[i][j].f;
			for(int k=b;k>=c;k--){
				dp[i+w][k]=max(dp[i+w][k],dp[i][k-c]+(ll)f);
			}
		}
	}
	ll ans=-1;
	for(int i=0;i<=b;i++){
		ans=max(ans,dp[l][i]);
	}
	printf("%lld",ans);
	return 0;
} 
```


---

## 作者：linyinuo2008 (赞：2)

[原题链接](https://www.luogu.com.cn/problem/P2854)

这是一道非常不错的二维背包题（虽然我也是看着题解打的），所以做完后写了篇题解。

# 1、题意理解

这道题的意思是有$n$条钢轨，要求从$0$覆盖到$L$且总费用不能超过$b$（注意：可以覆盖到比$L$更大的点），第$i$条钢轨必须头放在$X_i$，长度为$T_i$，费用为$C_i$，价值为$W_i$。要求在满足条件的情况下，总价值最大。若无法满足要求，则输出$-1$。

这看起来是一个$01$背包题，但是还有一个多余的条件，就是要铺满$[0, L]$这个区间。因此我们要在普通的[$01$背包](https://blog.csdn.net/u014296502/article/details/80015722)上再加一个维度表示费用。

# 2、算法理解

我们先定义一个结构体数组$a$，记录每根铁轨的起点，终点，价值，费用。由于我们还要讨论无解的情况，所以我们把$f$数组初始化为$-\infty$。由于我们要从后向前枚举钢轨，所以我们要先按每根钢轨的起点排个序。

我们设$f(i,j)$表示当前走到了$i$，而已经花的总费用为$j$所能获得的最大价值。

先上动归转移方程：$ f(e_i,j)= \max( f(s_i,j-c_i)+w_i ) $ 其中$e_i$，$s_i$，$c_i$，$w_i$为第$i$根铁轨的终点,起点,费用，价值，并且仅当$f(s_i,j-c_i)$不等于$- \infty$时才能转移。

这个动归方程也很好理解：就是一个位置当花费为$j$时，就枚举每根钢轨。如果这根钢轨起点之前能被铺满，就进行一个$01$背包的转移。

**但是我要再强调一遍$01$背包的重点：第一层枚举物品，第二层枚举容量。**

并且最后别忘了如果所有终点为$L$的状态都不能取到（均为$- \infty$），那么输出$-1$。并且我还在最前面排完序后加了个小优化，就是如果没有钢轨的起点在$0$，那么一定不可能铺满。

# 3、代码

代码中有注释。

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int NR=10005;
const int MR=1005;
const int INF=0x7f7f7f;

struct comp
{
	int start,end,fun,cost;//分别是每根钢轨的起点，终点，价值，费用 
}a[NR];

int l,n,b,ans;
int f[MR][MR];

bool cmp(struct comp u,struct comp v)//排序 
{
	return u.start<v.start;
}

inline int max(int p,int q)//自己写max更快 
{
	return p>q?p:q;
} 

int main()
{
	memset(f,-INF,sizeof(f));//初始化f为负无限 
	cin>>l>>n>>b;
	for(int i=1;i<=n;i++)
	{
		int k;
		cin>>a[i].start>>k>>a[i].fun>>a[i].cost;
		a[i].end=a[i].start+k;//把输入转化为负无限 
	}
	sort(a+1,a+n+1,cmp);//用快排函数排个序 
	if(a[1].start!=0)//一个小优化 
	{
		cout<<-1;
		return 0;
	}
	f[0][0]=0;//别忘了初始化 
	for(int i=1;i<=n;i++)//第一层枚举物品 
	{
		for(int j=b;j>=a[i].cost;j--)//第二层倒序枚举容量 
		{
			if(f[a[i].start][j-a[i].cost]!=(-INF))//如果起点满足要求 
			{
				//转移 
				f[a[i].end][j]=max(f[a[i].end][j],f[a[i].start][j-a[i].cost]+a[i].fun);
			}
		}
	}
	ans=-INF;//先把ans设为负无限 
	for(int i=0;i<=b;i++)
	{
		ans=max(ans,f[l][i]);
	}
	if(ans==-INF) cout<<-1;//如果ans没有变 ，输出-1 
	else cout<<ans;//输出 
	return 0;
}
```
**若有错误，欢迎指出！**


---

## 作者：Sairfzy (赞：2)

##  此篇属于题解不一定正解系列.

机房模拟赛 老师用了这题 

没想DP 直接~~暴躁~~DFS  加O2~~（手动）~~

 T 两个点. 听机房大佬可以记忆化. 

然后 加个贼简单的 记忆化 就过了....

~~其实是原题数据太水了~~

我们老师 加了一组数据 就把所有DFS的卡死了.

其实DP是正解..

看DP 可以看第一个的~~我们机房大佬发的题解~~

代码+注释:

```cpp
#include<bits/stdc++.h>
using namespace std;
struct xx {
	int xi,wi,fi,ci;
} a[10005];
vector <int> s[1005]; // 表示不同位置 可以接上 哪几个铁轨.
int mem[1005]; // mem -> 记忆到当前位置 最大的有趣值 
int ans=-1;   // 无解
int l,n,b;
void dfs(int len,int he,int sum)  // he -> 此时的费用 sum->此时的有趣值  len->此时的长度. 
{
	if(he>b) return ;  // 简单的剪枝 
	if(mem[len] && mem[len] > sum) return ; //若相同长度的有趣值 已经小于 以前的 那就没必要搜下去了. 
	if(len==l) { //抵达目标 
		ans=max(sum,ans);
		return ;
	}
	
	if(mem[len]==0) mem[len] = sum;
	mem[len] = max(sum,mem[len]) ; //取最大 

	int h = s[len].size();
	for(int i=0 ; i<h; i++) { // 遍历所有可以接上的铁轨. 
		int z = s[len][i];
		dfs(len+a[z].wi,he+a[z].ci,sum+a[z].fi);
	}
}
void Ghost_main()
{
	scanf("%d%d%d",&l,&n,&b);
	for(int i=1; i<=n; i++) {
		scanf("%d%d%d%d",&a[i].xi,&a[i].wi,&a[i].fi,&a[i].ci); // 读入
		s[a[i].xi].push_back(i); // 将可以接上的 存到一个数组里 DFS用
	}
	dfs(0,0,0);
	printf("%d",ans);
	return ;
}
int main()
{
#define offline_
#ifdef offline
	freopen("coaster.in","r",stdin);
	freopen("coaster.out","w",stdout);
	Ghost_main();
	fclose(stdin),fclose(stdout);
#else
	Ghost_main();
#endif
	return 0;
}
```

---

## 作者：草原飞飞羊 (赞：1)

好题啊!好题!

又是一道~~邪恶坑人的~~DP题!

说实话,我觉得这道题还是一道绿题真是不对!!难度顶多也就个黄题了吧.

先推一道01背包裸题:[P2871 手链Charm Bracelet](https://www.luogu.org/problemnew/show/P2871)

分析一下:

算法:DP,01背包

数据范围:1≤N≤10000,1≤L≤1000,1≤Wi≤L,1≤Xi≤L-Wi,1 ≤Fi≤1000000,1≤Ci≤1000,1≤B≤1000

上代码,具体解释看注释.

---

代码:

```cpp
//dp代码.
/*
这道题显然是01背包变种.所以用01背包的状态改改就可以了
01背包状态:
状态:f[i]表示在重量为i时能获得的最大价值         
转移:f[j]=max(f[j],f[j-a[i].w]+a[i].v); 
初值:0
答案:f[m] 

本题状态:
状态:f[i][j]表示以i为终点,预算最多为j时的最大快乐度           
转移:f[x[k]+w[k]][j]=max(f[x[k]+w[k]][j],f[x[k]][j-c[i]]+f[i])
初值:f[0][j]=0,f[i][j]=-999999
答案:f[l][b]
是不是很像~~~
大家可以对比着来看.实际上这道题与01背包最大的差别也就是加了一维.
*/
#include<cstdio>
#include<cmath>
#include<cstring>
#include<string>
#include<iostream>
#include<algorithm>
#define for1(i,a,b) for(int i=a;i<=b;++i)
#define for2(i,a,b) for(int i=a;i>=b;--i)
using namespace std;
long long f[1001][1001];                                                                                                                                                                                                                                                                                                                         
//f[]用于DP.由于极限数据funny<=1000000,所以要开long long.开int应该会炸. 
/*
状态:f[i][j]表示以i为终点,预算最多为j时的最大快乐度           
转移:f[x[k]+w[k]][j]=max(f[x[k]+w[k]][j],f[x[k]][j-c[i]]+f[i])
初值:f[0][j]=0,f[i][j]=-999999
答案:f[l][b]
*/
struct Roller_Coaster
{
   	int start;//初始 
   	int length;//长度 
   	int funny;//娱乐度 
   	int cost;//花费 
}a[10001];
//过山车铁轨的结构体.a[]代表铁轨的资料 
bool cmp(Roller_Coaster x,Roller_Coaster y){
   	return x.start<y.start;
}
//用于sort()快排 
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
   	std::ios::sync_with_stdio(false);
   	int n,l,b;
   	cin>>l>>n>>b;//读入 
   	memset(f,-999999,sizeof(f));//f[]初始化.注意memst初始化并不是会把它们都赋值为写的值(0,1除外),memset是16进制工作的,大家可以自行输出看一下结果.但无论如何这是一个很小的值. 
   	for1(i,1,n) cin>>a[i].start>>a[i].length>>a[i].funny>>a[i].cost;
   	sort(a+1,a+1+n,cmp);//按起点排序 
   	for1(i,0,b)
	   	f[0][i]=0;//f[]初始化 
   	for1(i,1,n)
	   	for1(j,0,b)
		   	if(j-a[i].cost>=0)
			   	f[a[i].start+a[i].length][j]=max(f[a[i].start+a[i].length][j],f[a[i].start][j-a[i].cost]+a[i].funny);
   	if(f[l][b]<=0)
	   	cout<<-1;//如果在预算为b,l为终点时最大快乐度<=0,说明不能放铁轨,print(-1). 此处要特别注意:一定要特判.不加这条80分. 
   	else
	   	cout<<f[l][b];
   	return 0;
}   
//2018 11 4大刷题,作此篇.此篇本人noip2018前最后一篇题解,刷题173道,谨以此记.
```

noip2018 rp++!

2018 11 10noip2018 祝大家好运,rp++.

码风勿喷

草原飞飞羊 于2018 11 4 18:26

---

## 作者：望月野QwQ (赞：0)

## 1.题意理解

对于 $0$ ~ $L$ 的轨道中，填满所有段轨道，且保证花费都在 $B$ 之内，求最大的收获值。

## 2.分析
这道题第一眼看去就是一道背包类型的动规题，但是还有一个多余的条件，就是要铺满 $[0,L]$ 这个区间。所以我们要额外添加一个维度。

 以上，我们可以推出状态转移方程

 $f[end][j+c_i]= \max (f[start][j]+f,f[end][j+ci])$ 

 $f[i][j]$	其中 $i$ 表示第 $i$ 段铁轨，$j$ 表示已经使用了多少钱。

## 详解
```cpp

#include<bits/stdc++.h>
using namespace std;
int L,n,B;
struct line
{
	int st,w,ed,f,c;
}a[10001];
int f[1001][10001];
bool cmp(line a,line b)
{
	return a.st<b.st;
}
int main()
{
	cin>>L>>n>>B;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].st>>a[i].w>>a[i].f>>a[i].c;
		a[i].ed=a[i].st+a[i].w;
	}	//处理输入
	sort(a+1,a+n+1,cmp);	
   // 排序，保证起点在前的首先被使用
   // 否则会出现问题
   // 如数据	3 2 3
   // 		   1 2 1 1
   //		   0 1 1 1
   // 这会使先尝试第一组，导致第一组无法使用，原因往下看
	memset(f,-1,sizeof(f));
	f[0][0]=0;
	for(int i=1;i<=n;i++)
	{
		int b=B-a[i].c;
		for(int j=0;j<=b;j++)
		{
			if(f[a[i].st][j]!=-1)
            //	就是这里，为什么必须要首先排按照起始点顺序排序
            //  如果出现起始点在2，但是前面没有出现过结束点为2
            // 这时就会被认为，如果这段被摆上去，那么铁路不会被完整的修完
            //ps：铁路是不能重叠摆放的
                                               
				f[a[i].ed][j+a[i].c]=max(f[a[i].ed][j+a[i].c],f[a[i].st][j]+a[i].f);
		}
	}
	int ans=0;
	for(int i=1;i<=B;i++)ans=max(ans,f[L][i]);
	if(ans>0)cout<<ans;
	else	cout<<-1;
	return 0;
}
```

---

## 作者：Genevieve_xiao (赞：0)

### P2854 

有 n 条线段，每条线段只能放在数轴上的一个特定位置，现在让你从中选出一些线段，使得这些线段能够铺满数轴上的区间，并且所花费用和不超过 B，同时要使你收获的价值尽量大。

一道经典的dp问题。背包的思想。其实也有贪心。

蒟蒻考前写一篇题解（有生之年的第一篇），谨以此纪念2021noip的到来。

**思路来源于czdalao** [@crosaa](https://www.luogu.com.cn/user/477676) 
(((cztql！！！！！

~~于是就产生了蒟蒻的最优解~~ 25ms
***

做法区别于其他题解。

先对所有区间**按右端点进行排序**

用两个数组储存**状态**：

**f[ i ] 表示铺到第i个单位长度的最大价值**

**g[ i ] 表示状态f[ i ]对应的最小花费**

**初始化**： 

f[ ] 初始化为负无穷 g[ ]初始化为正无穷

当铺到第0个单位长度时的价值和花费都是0, 因此```f[0]=g[0]=0 ```

**状态转移**：

依次遍历每个区间，这里用结构体储存比较方便一些。

如果使用这块木板可以获得更优的价值，那么我们就更新它，并且更新它所对应的代价

```cpp
		if(f[e[i].ed]<f[e[i].st]+e[i].w){
			f[e[i].ed]=f[e[i].st]+e[i].w;
			g[e[i].ed]=g[e[i].st]+e[i].c;
		}
```

如果使用这块木板与不使用它价值相同，那么我们就取最小的代价，更新g[]

```cpp
		else if(f[e[i].ed]==f[e[i].st]+e[i].w){
			g[e[i].ed]==min(g[e[i].ed],g[e[i].st]+e[i].c);
		}
```

注意排除不合法状态，如果之前的代价加上这块木板的代价大于m，那么直接跳过

```cpp
		if(g[e[i].st]+e[i].c>m) continue;
```
最后判断一下 f[l] 是否有合法解就好了



### 代码

```cpp
int read(){}
const int N=20510;
int l,n,m,f[N],g[N];

struct node{
	int st,len,w,c,ed;
}e[N];

bool cmp(node x,node y){
	return x.ed<y.ed;
}
int main(){
	l=read(), n=read(), m=read();
	for(int i=1;i<=n;i++){
		e[i].st=read(), e[i].len=read();
		e[i].w=read(), e[i].c=read();
		e[i].ed=e[i].st+e[i].len;
	}
	sort(e+1,e+1+n,cmp); //排序
	memset(f,-0x3f,sizeof f);
	memset(g, 0x3f,sizeof g);
	f[0]=0;g[0]=0; //初始化
	for(int i=1;i<=n;i++){
		if(g[e[i].st]+e[i].c>m) continue; //不合法状态
		if(f[e[i].ed]<f[e[i].st]+e[i].w){ //更优价值
			f[e[i].ed]=f[e[i].st]+e[i].w; //代价和花费都要更新
			g[e[i].ed]=g[e[i].st]+e[i].c;
		}
		else if(f[e[i].ed]==f[e[i].st]+e[i].w){ //价值相同 取最小代价
			g[e[i].ed]==min(g[e[i].ed],g[e[i].st]+e[i].c);
		}
		
	}
	if(f[l]>0)	printf("%d",f[l]);
	else printf("-1"); //无解
	return 0;
}

//希望管理员大大给通过
```

***
2021noip rp++



---

## 作者：汪鸣谦 (赞：0)

这一题算是一个背包问题

大概的思路是，乍看一眼题目里有钢轨数目n，长度l，和花费b三种维度的变量，作为背包，我们肯定是要从中选取几个作为设计的状态。那么，我们发现三个都选肯定是不现实的，发现题目的问题是修建长度为l的铁路，并且还给出了每根钢轨的起点和长度，那么长度l（或者位置）就必须作为状态里的维度之一。又因为花费b必须作为维度之一，相比之下，铁轨数目n如果作为一个状态维度的话就既不好转移也没有实际意义。因此，我们可以设出一个这样的dp数组：dp[i][j]表示在正好花费为i的情况下修建从0-j的铁路的最大有趣值。

很容易得出转移方程，dp[i][j]=max(dp[i][j],a[k].f+dp[i-a[k].c][j-a[k].w])

上面式子里的k表示，因为我们目前的铁路是修到j位置的所以自然目前用的这块铁轨就要在j结束。于是我们就枚举铁轨编号k，如果枚举到的铁轨正好在k结束那么就可以进行转移了。

这里还要注意一点：k的范围如果是从1-n，那么时间复杂度会超时。于是做这样的优化：先按照每条铁轨的终点进行排序每次需要转移的时候从连续的重点正好是j的铁轨里取用即可。这部分的细节具体实现在代码里，给了注释。

另外还要注意一点：就是某些状态是不合法的，不可以由他们转移而来（就是这里如果不注意到只有30分）。首先每一种状态对应的的铁轨修建方式必须从0开始（这句话有些绕）

大概是什么意思呢，就是比如这种修建方式就是不合法的：

（1，2）-（2，3）-（3，4）

而这种修建方式是合法的

（0，1）-（1，2）-（2，3）-（3，4）

于是我们可以把那些不合法的状态用-1来表示，初始值是dp[0][0]=0，其他的都是-1。每次只能从初始值不是-1的地方转移。

代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,dp[2001][2001]={-1},ans=-1,l,b,s[10001]={0},cnt=0;
struct cow{
	int x,w,f,c,e;
}a[200001];
bool cmp(cow a,cow b){
	return a.e<b.e;
}
int main(){
	for(int i=0;i<=2000;i++)for(int j=0;j<=2000;j++)dp[i][j]=-1;
	cin>>l>>n>>b;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].w>>a[i].f>>a[i].c;
		a[i].e=a[i].x+a[i].w;
	}
	sort(a+1,a+n+1,cmp);
	dp[0][0]=0;
	for(int i=1;i<=n;i++)s[a[i].e]=i;//用s数组记录s[i]表示排序后的a数组中最后一个终点为a[i].e的铁轨编号是多少，因为排序了，所以保证终点为一个定值的铁轨一定是连续的
	for(int i=1;i<=b;i++){
		for(int j=1;j<=l;j++){
			for(int k=s[j];k>=1;k--){
				if(a[k].e!=a[s[j]].e)break;
				if(i>=a[k].c&&j-a[k].w==a[k].x&&dp[i-a[k].c][j-a[k].w]!=-1){dp[i][j]=max(dp[i][j],a[k].f+dp[i-a[k].c][j-a[k].w]);}
			}
		}
	}
	for(int i=1;i<=b;i++)ans=max(ans,dp[i][l]);
	cout<<ans<<endl;
	return 0;
}

```


---

## 作者：李若谷 (赞：0)

## DP + Vector


此题有一点像背包问题，但是，有一点不同。

背包问题只需要找出所有物品装发的最大值，此题要求轨道必须从0接到l。

所以，这道题在背包问题上加了一个限制。

解法和背包问题类似。

$dp(i,j)$ 表示轨道从0接到i，拥有j钱的最大值。

不难得出，$dp(i,j)$ 只能从某一个终点为i的轨道转移过来。

所以，$dp(i,j) = \max(dp[pos[k]][j-c[k]] + f[k])$。

其中，k表示一个终点为i的轨道的存储是的坐标（也就是读入时第几个读入）。

那么，如何求出这个k呢？

显然，终点为i的轨道可能不止一个。所以我们可以用stl:vector来存储。

可以用一个结构体里面内嵌vector，存储终点为i的所有轨道的存储坐标。

### 边界细节

如果按照上面的做法还是会有问题。因为有边界情况。

我们要找的必须是从0接过来的。

然而由于dp数组初始值是0，那么状态转移可能转移到一个并不是0位起点的状态。

比如一个轨道从1-3。那么$dp(3,j)$会转移到$dp(1,j-c[k])$，然而0并不能到1。

所以我们要把dp数组初始化为-1，表示走不到，并且$dp(0,j) = 0$。

状态转移时只转移 $dp$ 数组非0的情况

代码：
```cpp
#include <iostream>
#include <cstdio>
#include <map>
#include <vector>
#include <cstring>
using namespace std;
const int L = 1001,N = 10001,B = 1001;
long long dp[L][B];
long long l,n,b;
long long fun[N],c[N],x[N];
struct component
{
	vector <int> start;
}track[L];
inline long long read()	//快读模板
{
	long long ans = 0,f = 1;
	char ch = getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		ans = ans*10 + ch - '0';
		ch = getchar();
	}
	return ans * f;
}
int main()
{
	l=read(),n=read(),b=read();
	for(register int i=1;i<=n;i++)
	{
		long long w;
		x[i]=read(),w=read(),fun[i]=read(),c[i]=read();
		track[x[i]+w].start.push_back(i);
	}
	memset(dp,-1,sizeof(dp));
	for(register int i=1;i<=b;i++)
		dp[0][i] = 0;
	for(register int i=1;i<=l;i++)
	{
		for(register int j=0;j<=b;j++)
		{
			for(register int k=0;k<track[i].start.size();k++)
			{
				int pos = track[i].start[k];
				if(j>=c[pos]&&dp[x[pos]][j-c[pos]]!=-1) //特判
					dp[i][j] = max(dp[i][j],dp[x[pos]][j-c[pos]]+fun[pos]);
			}
		}
	}
	cout<<dp[l][b]<<endl;
	return 0;
}
```

---

## 作者：zyc____ (赞：0)

## P2854 USACO 06DEC Cow Roller Coaster

### 进入正题
### 题意

要建造一座过山车，给出建造需要的零件。每个零件都有一个固定的起始位置、长度、乐趣值和花费。给出过山车的长度，零件的数量，总共的预算，要求出在预算范围内选出一些零件，使总的乐趣值最大。

------------

### 分析
### 二维背包问题。
设dp[i][j]表示在i的位置修建零件花费为j时所获得的最大乐趣值。状态转移方程为dp[com[i].x+com[i].w[j+com[i].c]>=dp[com[i].x][j]+com[i].f ~~看着有点乱~~


------------
### AC代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
struct node{
    int x,w,f,c;
}com[10005];
int L,N,B,dp[1005][1005];
bool cmp(node a,node b){
    return a.x+a.w<b.x+b.w;
}
int main(){
    while(cin>>L>>N>>B){
        for(int i=0;i<N;i++)
            cin>>com[i].x>>com[i].w>>com[i].f>>com[i].c;
        sort(com,com+N,cmp);
        memset(dp,-1,sizeof(dp));   
        for(int i=0;i<=B;i++) dp[0][i]=0;
        for(int i=0;i<N;i++)
        for(int j=0;j<=B-com[i].c;j++){
            if(dp[com[i].x][j]<0) continue;   
            dp[com[i].x+com[i].w][j+com[i].c]=max(dp[com[i].x+com[i].w][j+com[i].c],dp[com[i].x][j]+com[i].f);
        }
        cout<<dp[L][B]<<endl;
    }
    return 0;
}
```


---

## 作者：Accoty_AM (赞：0)

**记忆化搜索**

x表示搜到位置x

money是当前用的钱

ID是当前在铁轨中的位置优化

当钱用完就说明，到不了终点，返回一个极小值

最后当ans为负，说明到不了，直接输出-1

```cpp
#include<bits/stdc++.h>
#define rg register
#define int long long
using namespace std;
int l,n,b,d[10010][1010],ans;
struct node{
	int x,len,v,w;
}a[10000];
bool operator < (const node a,const node b){
	return a.x<b.x;
}
inline int read(){
	rg char ch=getchar();
	rg int x=0,f=0;
	while(ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
int dfs(int x,int money,int id){
	if(d[x][money])return d[x][money];
	if(money>=b) return -0x3f3f3f3f;
	if(x>=l) return 0;
	int value=-0x3f3f3f3f;
	for(int i=id;i<=n;++i){
		if(a[i].x>x)break;
		if(a[i].x==x)
			value=max(dfs(x+a[i].len,money+a[i].w,i)+a[i].v,value);
	}
	d[x][money]=value;
	return value;
}
signed main()
{
	l=read(),n=read(),b=read();
	for(rg int i=1;i<=n;++i){
		a[i].x=read(),a[i].len=read(),a[i].v=read(),a[i].w=read();
	}
	sort(a+1,a+1+n);//优化搜索顺序
	int ans=dfs(0,0,1);
	if(ans<=0)printf("-1");
	else
	printf("%lld",ans);
	return 2333;
}
```

---

## 作者：翠竹叶飞 (赞：0)

简单的背包，注意top序。

另此题需判断可行性，即该状态是否可以达到。

将f数组置-1即可。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
int i,j,l,n,b,ans=-1;
int f[1001][1001];
struct ele
{
    int start, end, value, weight;
} a[10001];
int comp(ele a, ele b)
{
    return a.start<b.start;
}
int main()
{
    memset(f,-1,sizeof(f));
    f[0][0]=0;
    scanf("%d%d%d",&l,&n,&b);
    for (i=1; i<=n; i++)      
    {
        scanf("%d%d%d%d",&a[i].start,&a[i].end,&a[i].value,&a[i].weight);
        a[i].end+=a[i].start;
    }
    sort(a+1,a+n+1,comp);
    for (i=1; i<=n; i++)
      for (j=b; j>=a[i].weight; j--)
        if (f[a[i].start][j-a[i].weight]>=0)
          f[a[i].end][j]=max(f[a[i].end][j],f[a[i].start][j-a[i].weight]+a[i].value);
    for (i=1; i<=b; i++)
      ans=max(ans,f[l][i]);
    printf("%d",ans);
    return 0;
}
```

---

