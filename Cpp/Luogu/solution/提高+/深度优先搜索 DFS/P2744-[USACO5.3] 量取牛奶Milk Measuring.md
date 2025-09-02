# [USACO5.3] 量取牛奶Milk Measuring

## 题目描述

农夫约翰要量取 $Q$（$1 \le Q \le 20,000$）夸脱（译注：即 quarts，容积单位）他的最好的牛奶，并把它装入一个大瓶子中卖出。消费者要多少，他就给多少，从不有任何误差。

农夫约翰总是很节约。他现在在奶牛五金商店购买一些桶，用来从他的巨大的牛奶池中量出 $Q$ 夸脱的牛奶。每个桶的价格一样。你的任务是计算出一个农夫约翰可以购买的最少的桶的集合，使得能够刚好用这些桶量出 $Q$ 夸脱的牛奶。另外，由于农夫约翰必须把这些桶搬回家，对于给出的两个极小桶集合，他会选择“更小的”一个，即：把这两个集合按升序排序，比较第一个桶，选择第一个桶容积较小的一个。如果第一个桶相同，比较第二个桶，也按上面的方法选择。否则继续这样的工作，直到相比较的两个桶不一致为止。例如，集合 $\{3,5,7,100\}$ 比集合 $\{3,6,7,8\}$ 要好。

为了量出牛奶，农夫约翰可以从牛奶池把桶装满，然后倒进瓶子。他决不把瓶子里的牛奶倒出来或者把桶里的牛奶倒到别处。用一个容积为 $1$ 夸脱的桶，农夫约翰可以只用这个桶量出所有可能的夸脱数。其它的桶的组合没有这么方便。

计算需要购买的最佳桶集，保证所有的测试数据都至少有一个解。

## 说明/提示

题目翻译来自NOCOW。

USACO Training Section 5.3


## 样例 #1

### 输入

```
16
3
3
5
7```

### 输出

```
2 3 5```

# 题解

## 作者：xMinh (赞：9)

S1
一开始看到这道题还是很好确定算法的，妥妥的是dfs+dp。先跑一遍完全背包，vis[i][j]表示体积为j的时候选不选i最优，可以把第一维压掉。如果vis[j-a[i]]选了i，那么vis[j]就不用再选一遍。这样可以确定出来一共选了多少种木桶，之后搜索，再跑布尔完全背包，因为已经把桶的大小排过序了，那么如果可以拼成体积为q的就直接输出结束程序就可以了。

S2
注意两个小错误。

第一个，在最初的那一遍完全背包中，如果f[j-a[i]]+value等于f[j]，那也要把vis[j]设为1，因为这样会最优——在同样的f[j]下，如果vis[j]=1，那么f[j+a[i]]的值会少加1，从而保证最终的结果最优。

第二个，这个真是无语，小错误害死人啊。在搜索完的那次完全背包中，我的初始化不是g[i]=big，而是g[q]=big……手一滑，三个人检查了一个小时，死活检查不出来，从网上下了数据才出来的……检查的时候一定要一个字一个字仔细看，不要因为语句简单就不看了，简单的语句也可能手滑打错。

代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#define rint register int
#define inv inline void
#define big 1e9
using namespace std;
int p,q,a[101],f[20001],que[101],cnt;
bool use[101],vis[20001],g[20001];
inv dp()
{
    for (rint i=0;i<=q;i++) g[i]=0;g[0]=1;
    for (rint i=1;i<=f[q];i++)
        for (rint j=a[que[i]];j<=q;j++)
            if (g[j-a[que[i]]]) g[j]=1;
    if (g[q])
    {
        printf("%d ",f[q]);
        for (rint i=1;i<=f[q];i++) printf("%d ",a[que[i]]);
        exit(0);
    }
}
inv dfs(int x,int dep)
{
    if (dep==f[q]) 
    {
        dp();
        return;
    }
    if (f[q]-dep>p-x) return;
    for (rint i=x+1;i<=p;i++)
    {
        que[dep+1]=i;
        dfs(i,dep+1);
    }
}
int main()
{
    scanf("%d%d",&q,&p);
    for (rint i=1;i<=p;i++) scanf("%d",&a[i]);
    sort(a+1,a+p+1);
    for (rint i=0;i<=q;i++) f[i]=big;f[0]=0;    
    for (rint i=1;i<=p;i++)
        for (rint j=0;j<=q;j++)
        {
            vis[j]=0;
            if (j>=a[i])
            {
                int value=vis[j-a[i]]^1;
                if (f[j-a[i]]+value<=f[j])
                {
                    f[j]=f[j-a[i]]+value;
                    vis[j]=1;
                }
            }
        }
    dfs(0,0);
} 
```
总结：

1.  要思考一下第一个搜出来的是不是最优解，是的话可以直接剪掉。

2.  一定要注意细节，等于号加不加是个问题，仔细思考。出错的时候一句一句认真检查，千万不要嫌麻烦，发愁的时间比检查的时间长多了。


---

## 作者：xzyyf (赞：9)

这一题和岳麓山上打水是一样的

先把原来的题解发一遍

虽说标签是DP，迭代搜索未尝不可


```cpp
#include <bits/stdc++.h>
using namespace std;
#define xyf main
const int maxn =105;
const int maxv=21000;
int f[maxv];
int a[maxn];
int v[maxn];
int V,n;
int maxd;
inline void read(int& d)
{
    d=0;
    bool mark=false;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')mark=true;ch=getchar();}
    while(ch<='9'&&ch>='0'){d=(d<<3)+(d<<1)+ch-'0';ch=getchar();}
    if(mark)d=-d;
}
inline void write(int x)
{
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
inline void init()
{
    read(V);
    read(n);
    for(int i=1;i<=n;++i)
        read(v[i]);
}
inline void print()
{
    write(maxd),putchar(' ');
    for(int i=1;i<=maxd;++i)
        write(a[i]),putchar(' ');;
    exit(0);
}
inline bool check(int x)
{
    int &s=f[x];
    if(s!=-1)
        return s;
    if(x==0)
        return s=1;
    for(int i=1;i<=maxd;++i)
        if(x>=a[i]&&check(x-a[i]))
            return s=1;
    return s=0;
}
inline void dfs(int depth,int k)
{
    if(depth>maxd)
    {
        memset(f,-1,sizeof(f));
        if(check(V))
            print();
        return;
    }
    if(k>n)
        return;
    a[depth]=v[k];
    dfs(depth+1,k+1);
    dfs(depth,k+1);
}
inline void id_dfs()
{
    sort(v+1,v+n+1);
    n=unique(v+1,v+n+1)-v-1;
    for(maxd=1;maxd<=n;++maxd)
        dfs(1,1);
}
int xyf()
{
    init();
    id_dfs();
    return 0;
}
```
本串代码中，利用了读入和输出优化，当然是雕虫小技。在进行搜索时，使用maxd控制搜索深度。 有一个小小的技巧，dfs函数中，先算选取，再算不选取，巧妙的覆盖了~~~

因为每个水桶可以用无限多次


所以我们可以用完全背包来解决


因为只需要判断是否能装满所以我们用f[]的0或1来表示能否到达


然后完全背包刷一遍即可


这里可以用递推地方法也可以用递归的方法，递归会比递推快很多~


因为递推要全部刷一遍复杂度是O(nV)的，而递归递归下去找到一个可行解就是连续递归返回，所以效率高了很多(220ms-45ms)


下面讲一讲代码里的小优化

先给出一串代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e4+10;
const int maxm = 1e2+10;
#define xyf main
int V,n,maxd;
int f[maxn];
int v[maxm];
int a[maxm];
inline void read(int& d)
{
    d=0;
    bool mark=false;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')mark=true;ch=getchar();}
    while(ch>='0'&&ch<='9'){d=(d<<3)+(d<<1)+ch-'0';ch=getchar();}
    if(mark)d=-d;
}
inline void write(int d)
{
    if(d<0)putchar('-'),d=-d;
    if(d>9)write(d/10);
    putchar(d%10+'0');
}
inline void init()
{
    read(V);
    read(n);
    for(int i=1;i<=n;++i)
        read(v[i]);
}
inline void print()
{
    write(maxd);
    putchar(' ');
    for(int i=1;i<=maxd;++i)
        write(a[i]),putchar(' ');
    exit(0);
}
inline bool check(int x)
{
    int s=f[x];
    if(s!=-1)
        return s;
    if(x==0)
        return s=1;
    for(int i=1;i<=maxd;++i)
        if(x>=a[i]&&check(x-a[i]))
            return s=1;
    return s=0;
}
inline void dfs(int depth,int k)
{
    if(depth>maxd)
    {
        memset(f,-1,sizeof(f));
        if(check(V))
            print();
        return;
    }
    if(k>n)
        return;
    a[depth]=v[k];
    dfs(depth+1,k+1);
    dfs(depth,k+1);
}
inline void id_dfs()
{
    sort(v+1,v+n+1);
    for(maxd=1;maxd<=n;++maxd)
        dfs(1,1);
}
int xyf(int argc, char const *argv[])
{
    init();
    id_dfs();
    return 0;
}
```
这串代码乍一看和上面一模一样，但是超时。
为什么呢？

首先我们对比一下

有两个不一样的地方

两个代码都用了读入输出优化，但还是会有3个点的差距，可见这一题数据是多么的sxbk。

第一处大概就是

unique(v+1,v+n+1)-v-1;

这里使用了unique函数，重复的筒子删掉，可能只有一点小小的改进吧。

但下面的这一点好像很有用

在check函数中，有一句int &s=f[x]

使用了取地址

更快更有效的进行取值（估计两个代码的主要差距就在这里了）

由此我们得到了经验

在对数组中的变量进行引用时，使用&会快不少呢

具体为什么，这涉及到c++的一些基本原理，大概就是与数组并不是“一等公民”有关吧（有关参见《算法竞赛入门经典》）。

还有什么不明白，可以私我。


---

## 作者：Celebrate (赞：7)

这一道题用完全背包来做

首先，看一下70分代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[110];
int f[21000][110];
bool bk[21000][110];
inline bool bijiao(int x,int y)
{
    for(int i=1;i<=f[x][0];i++)
    {
        if(f[x][i]<f[y][i]) return true;
        if(f[x][i]>f[y][i]) return false;
    }
    return false;
}
int main()
{
    int i,j,k,t;
    scanf("%d%d",&m,&n);
    for(i=1;i<=n;i++) scanf("%d",&a[i]);
    for(i=1;i<=m;i++) f[i][0]=200;
    sort(a+1,a+n+1);
    memset(bk,false,sizeof(bk));bk[0][0]=true;
    for(i=1;i<=n;i++) 
    {
        for(j=a[i];j<=m;j++)
        {
            if(bk[j-a[i]][0]==false) continue;
            t=f[j-a[i]][0];
            if(bk[j-a[i]][i]==false) t++;
            if(t>f[j][0]) continue;
            if(t<f[j][0] || bijiao(j-a[i],j)==true)
            {
        		memset(bk[j],false,sizeof(bk[j]));bk[j][0]=true;
                f[j][0]=t;
                for(k=1;k<=f[j-a[i]][0];k++) f[j][k]=f[j-a[i]][k],bk[j][f[j][k]]=true;
                if(bk[j-a[i]][i]==false) f[j][t]=i,bk[j][i]=true;
            }
        }
    }
    printf("%d",f[m][0]);
    for(i=1;i<=f[m][0];i++) 
    {
        //if(a[f[m][i]]==1576) a[f[m][i]]=949;
        printf(" %d",a[f[m][i]]);
    }
    printf("\n");
    return 0;
}
```

这个代码的问题就是容易在还没有找到的时候就被覆盖了

所以需要改一下代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int a[110],s,fa; 
	node()
	{
		memset(a,2,sizeof(a));
		s=200;
	}
}f[21000];
int t,n,m,ans;
struct box
{
	int x,d;
}a[210000];//记录桶 
bool bk[11000];
inline bool pd(node x,node y)//字典许判断 
{
	for(int i=1;i<=x.s;i++)
	{
		if(x.a[i]>y.a[i]) return false;
		if(x.a[i]<y.a[i]) return true;
	}
	return false;
}
inline int cmp(const void *xx,const void *yy)//快排 
{
    box x=*(box*)xx;
    box y=*(box*)yy;
    if(x.x!=y.x)
    {
        return x.x<y.x?0:1;
    }
    return x.d<y.d?0:1;
}
int main()
{
	int i,j,x,y;
	scanf("%d%d",&m,&t);
	memset(bk,true,sizeof(bk));//记录是否找过 
	for(i=1;i<=t;i++)
	{
		scanf("%d",&x);
		if(bk[x]==true)
		{
			bk[x]=false;
			y=1;
			while(x*y<=m)//改为倍增 
			{
				n++;
				a[n].x=x;a[n].d=y*x;
				y++;
			}
		}
	}
	qsort(a+1,n,sizeof(box),cmp);//排序 
	f[0].s=0;
	for(i=1;i<=n;i++)
	{
		for(j=0;j<=m;j++)
		{
			if(a[i].x!=a[i-1].x) f[j].fa=0;//如果这个桶和前面的桶不是同一个倍增来的，祖先就不一样 
			if(j-a[i].d<0)continue;//如果小于0 
			if(f[j-a[i].d].s!=200)//如果前面的能到达 
			{
				if(f[j].fa==0) 
				{
					if(f[j-a[i].d].s+1<f[j].s)
					{
						f[j]=f[j-a[i].d];
						f[j].a[++f[j].s]=a[i].x;
						f[j].fa=1;
					}
					else if(f[j-a[i].d].s+1==f[j].s)
                    {
                        f[j-a[i].d].a[++f[j-a[i].d].s]=a[i].x;
                        if(pd(f[j-a[i].d],f[j])==true)//判断字典序 
                        {
                            f[j]=f[j-a[i].d];
                            f[j].fa=f[j].s;
                        }
                        f[j-a[i].d].s--;
                    }
                }
                if(f[j-a[i].d].fa!=0)//如果是 
                {
                    if(f[j-a[i].d].s<f[j].s)f[j]=f[j-a[i].d];
                    else if(f[j-a[i].d].s==f[j].s)
                    {
                        if(pd(f[j-a[i].d],f[j])==true)f[j]=f[j-a[i].d];
                    }
                }
            }
        }
    }
    printf("%d",f[m].s);//输出 
    for(i=1;i<=f[m].s;i++) printf(" %d",f[m].a[i]);
    printf("\n");
    return 0;
}
```

这样就不会被提前覆盖了

可是这样子有些慢，听大佬们说用dfs，我就改了一下dfs的

代码，0ms，无后效性（dfs一次性搜到低）

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[110];
int d[110],f[110],flag;//d表示暂时储存，f表示最后结果 
bool bk=false;//bk表示是否找到 
void dfs(int k,int v,int s)//k表示当前储存的结果数，v表示剩余的奶量，s表示枚举到的桶的编号 
{
	if(k==flag)//如果到了 
	{
		if(v==0)//没有剩余的 
		{
			memcpy(f,d,sizeof(d));//复制 
			bk=true;//记为可以 
		}
		return;//返回 
	}
	if(s>n || /* k>flag */a[s]>f[k]) return;//如果超过了大小，或者字典序更大，都要退 
	d[k]=a[s];//记录下来 
	for(int i=1;i*a[s]<=v;i++)//枚举倍数 
	{
		dfs(k+1,v-i*a[s],s+1);//深搜 
	}
	if(s<n) dfs(k,v,s+1);//还有一种可能就是不用这个桶直接玩下深搜 
}
int main()
{
	int i;
	scanf("%d%d",&m,&n);
	memset(f,2,sizeof(f));//变得无限大 
	for(i=1;i<=n;i++) scanf("%d",&a[i]);//输入和排序 
	sort(a+1,a+n+1);
	for(flag=1;flag<=n;flag++)//枚举flag个桶是否可以 
	{
		dfs(0,m,1);//深搜 
		if(bk==true) break;
	}
	printf("%d",flag);
	for(i=0;i<flag;i++) printf(" %d",f[i]);
	printf("\n");return 0;
}
```

---

## 作者：巨型方块 (赞：4)

希望大神可以教我动归........555555

虽然我感觉不能用动归，.....

我用爆搜做的，拼命优化

```cpp
int a[101],an[101],ans[101];
int n,m,x,sum;
bool p;
void getnew(int z){
    sum=z;
    for(int i=1;i<=z;i++)ans[i]=an[i];
}
void dfs(int x,int y,int z){//第x位，剩余y，当前已买了z个桶 
    if(z>sum)return;
    an[z]=a[x];
    if(y%a[x]==0){
        if(z>sum)return;else
        if(z<sum)getnew(z);else{
            for(int i=1;i<=z;i++)if(an[i]!=ans[i]){
                if(an[i]<ans[i])getnew(z);
                break;
            }
        }
        return;
    }
    if(x==n)return;
    for(int j=1;j<=y/a[x];j++)dfs(x+1,y-a[x]*j,z+1);
    dfs(x+1,y,z);
}
int main()
{
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    sum=1e9;
    sort(a+1,a+n+1);
    dfs(1,m,1);
    printf("%d",sum);
    for(int i=1;i<=sum;i++)printf(" %d",ans[i]);
}
```

---

## 作者：爱喝敌敌畏 (赞：3)

这道题我也用了纯DP，不过，不同的是，我用了一种神奇的倍增，并且，背包数组还额外维护了zx一个变量，来记录他需不需要增加一个新的桶！

不说了，霸王硬上弓，看代码！

```cpp
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using  namespace std;
struct  node
{
    int  a[101],d/*计算需要多少个桶*/,zx;
    node()
    {
    	memset(a,1,sizeof(a));
    	d=99999999;
    }
}v[20003];int  n,m,ans=99999999,nn;//用来dp的数组 
struct  tong
{
    int  d,x;
}a[201000];//储存桶的信息 
bool  oo[11000];
inline  int  mymin(int  x,int  y){return  x<y?x:y;}
inline  int  mymax(int  x,int  y){return  x>y?x:y;}
inline  bool  pd(node  x,node  y)
{
    for(int  i=1;i<=x.d;i++)
    {
    	if(x.a[i]!=y.a[i])return  x.a[i]<y.a[i];
    }
    return  false;
}//字典序比较 
inline  bool  cmp(tong  x,tong  y){return  x.x!=y.x?x.x<y.x:x.d<y.d;}//神奇的排序（三级运算符版） 
int  main()
{
    scanf("%d%d",&m,&n);
    for(int  i=1;i<=n;i++)
    {
        int  x;
        scanf("%d",&x);
        if(oo[x]==false)
        {
            oo[x]=true;//去重是个好东西 
            int  t=1;
            while(t*x<=m)
            {
                a[++nn].x=x;
                a[nn].d=t*x;
                t++;
            }//神奇的倍增，只不过不需要减去 
        }
    }
    sort(a+1,a+nn+1,cmp);
    v[0].d=0;
    for(int  i=1;i<=nn;i++)
    {
        for(int  j=0;j<=m;j++)
        {
        	if(a[i].x!=a[i-1].x)v[j].zx=0;//把以前的zx标记去掉 
        	if(j-a[i].d<0)continue;
            if(v[j-a[i].d].d!=99999999)//以前被更新我再去算 
        	{
        		if(v[j-a[i].d].zx==0)
        		{
        			if(v[j-a[i].d].d+1<v[j].d)
                    {
                        v[j]=v[j-a[i].d];
                        v[j].a[++v[j].d]=a[i].x;
                        v[j].zx=1;//标记 
                    }//更新 
                    else  if(v[j-a[i].d].d+1==v[j].d)
                    {
                        v[j-a[i].d].a[++v[j-a[i].d].d]=a[i].x;
                        if(pd(v[j-a[i].d],v[j])==true)
                        {
                            v[j]=v[j-a[i].d];
                            v[j].zx=v[j].d;
                        }
                        --v[j-a[i].d].d;
                    }//维护字典序 
                }
                if(v[j-a[i].d].zx!=0)
        		{
        			if(v[j-a[i].d].d<v[j].d)v[j]=v[j-a[i].d];
                    else  if(v[j-a[i].d].d==v[j].d)
                    {
                        if(pd(v[j-a[i].d],v[j])==true)v[j]=v[j-a[i].d];
                    }
                }//这个桶之前出现过，就少了众多操作 
            }
        }
    }
    ans=v[m].d;
    printf("%d",ans);
    for(int  i=1;i<=ans;i++)printf(" %d",v[m].a[i]);//输出 
    printf("\n");
    return  0;
}
```

于是，这道题就这么漂亮的解决啦！

---

## 作者：pocafup (赞：2)

讲一个比较下饭的做法：

dp 一维的转移有点难想，那何不把他表示成二维？

用 dp 记录到每个数字时最小的桶的数量

$dp[i][0]$ 表示目前在第 $i$ 位，且没有取过，$dp[i][1]$ 表示在第 $i$ 位且已经取过。

那么转移显然只会跟 $dp[i][1]$ 挂钩 ：已经取过则不累加贡献，否则累加。

$dp[i][1] = min(dp[i-num][1],dp[i-num][0]+1);$

之后 sort 一遍桶顺序，开始跑字典序即可。

注意：这里选字典序不能用贪心选择，必须用 dfs + 剪枝

因为脑子转不动，我选择用数组记录每一位的能取的最小值。

dp 的作用为判断在取完某一个数字后是否可以取其他。

代码：

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 1e4+5;
const int MAXK = 1e5+5;
int k,n,pos[MAXN],dp[MAXK][2],dp2[MAXK],cnt,keep[MAXK],ll;
inline void update(int num, int v){
  for (int i=num;i<=k;i++) dp[i][1] = min (dp[i][1],min(dp[i-num][1],dp[i-num][0]+1));
  for (int i=0;i<=k;i++) dp[i][0] = min(dp[i][0],dp[i][1]),dp[i][1] = 1e9+5;
}//dp 操作
inline void dfs(int val, int kk, int po, int ini,int bound){
  if (keep[ini]<val) return;
  if (!kk) {keep[ini] = val;return;}
  if (kk>=val) dfs(val,kk-val,po,ini,bound);
  if (kk<val) return;
  if (dp2[kk-val]==bound-1){
    keep[ini] = val;
    for (int i=po+1;i<=n;i++) dfs(pos[i],kk-val,i,ini+1,bound-1);
  }
}//dfs找字典序
signed main(){
  cin >> k >> n;
  memset(dp,0x3f3f,sizeof(dp));
  dp[0][0] = 0;
  for (int i=1;i<=n;i++) {cin >> pos[i]; update(pos[i],i);}
  for (int i=0;i<=k;i++) dp2[i] = min(dp[i][0],dp[i][1]);
  cnt = dp2[k];
  memset(keep,0x3f3f,sizeof(keep));
  sort(pos+1,pos+1+n);
  for (int i=1;i<=n;i++) {
    dfs(pos[i],k,i,1,dp2[k]);
    if (keep[1]<1e9) break;
  }
  for (int i=1;i<=dp2[k];i++) cout << keep[i] << " ";
}
```

---

## 作者：CrTsIr400 (赞：1)

# 重点：一种~~玄学~~剪枝优化

此题的其他部分都大致讲得差不多了，都是 剪枝后的dfs+完全背包可达性dp ，蒟蒻在此讲述一个非常有效的剪枝方法qwq

对于每个 $a_i$ ，可以在这个数列中筛除它的 $2$ 倍以上倍数。

原因显然，都是完全背包，所以作为每个 $a_i$ 的倍数的，必不一定对最优解做出贡献，肯定可以筛除，缩小搜索规模。

于是代码出来了。

```cpp
#include<cstdio>
#include<cstring>
#include<cstdlib>
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<8,stdin),p1==p2)?EOF:*p1++)
char buf[1<<8],*p1=buf,*p2=buf;
int n,q,a[101],k,tmx,at; 
bool bz[101],f[20001],t[10001];
inline bool ck()
{
	memset(f,0,sizeof(f));f[0]=1;for(register int i=1;i<=n;++i)if(bz[i])for(register int j=a[i];j<=q;++j)f[j]|=f[j-a[i]];
	return f[q];
}
inline void dfs(int cnt)
{
	if(cnt==k+1){if(ck()){printf("%d ",k);for(register int i=1;i<=n;++i)if(bz[i])printf("%d ",a[i]);exit(0);}return;}
	for(register int i=cnt;i<=n;++i)if(!bz[i])bz[i]=1,dfs(cnt+1),bz[i]=0;
}
int main()
{
	scanf("%d%d",&q,&n);
	for(register int i=1;i<=n;++i)scanf("%d",&at),t[at]=1,tmx=(at>tmx)?at:tmx;
	n=0;
	for(register int i=2;i<=tmx;++i)if(t[i])for(register int j=i+i;j<=tmx;j+=i)t[j]=0;
	for(register int i=0;i<=tmx;++i)if(t[i])a[++n]=i;
	for(k=1;k<=n;++k)dfs(1);
	return 0;
}
```

---

## 作者：罗旅洲 (赞：1)

/\*
下面题解的DP程序求方案的做法太麻烦了。其实只要一个bool数组就ok了

\*/
    
```cpp
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
#include<cstdio>
#include<algorithm>
#define For(i,a,b) for(register int i=a;i<=b;++i)
#define Rep(i,a,b) for(register int i=a;i>=b;--i)
const int oo=1e9+7;
using namespace std;
int n,v,t[101],f[20001];        //t就是桶子，f表示最少的方案数
bool pre[20010][105];            //pre[i][j]存储状态i用了哪些j的桶
int read(){
    char x;
    while((x=getchar())>'9' || x<'0');
    int u=x-'0';
    while((x=getchar())>='0' && x<='9')
    u=u*10+x-'0';
    return u;
    }
bool pd(int a,int b){            //比较两种方案谁更优
                                //"对于给出的两个极小桶集合，他会选择“更小的”一个"
    For(i,1,n)
        if(pre[a][i]^pre[b][i]==1){
            if(pre[a][i]) return 1;
            else return 0;
        }
    return 1;
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
#endif
    int i,j,k,sum;
    v=read(); n=read();
    For(i,1,n) t[i]=read();
    sort(t+1,t+n+1);        //排序保证输出时从大到小
    memset(f,63,sizeof(f));
    f[v]=0;
    For(i,1,n)                //无限背包
        Rep(j,v,1)
            for(k=1;;k++){
                sum=j-t[i]*k;
                if(sum<0) break;
                if(f[sum]==f[j]+1){        //如果转移时第一问满足了
                    if(!pd(sum,j)){        //存字典序最小的
                        memcpy(pre[sum],pre[j],sizeof(pre[sum]));
                        pre[sum][i]=1;
                    }
                }
                else if(f[sum]>f[j]+1){
                    f[sum]=f[j]+1;
                    memcpy(pre[sum],pre[j],sizeof(pre[sum]));
                    pre[sum][i]=1;
                }
            }
    printf("%d ",f[0]);
    For(i,1,n)
        if(pre[0][i]){ printf("%d ",t[i]); } //如果有就输出
    return 0;
}

```

---

## 作者：yybyyb (赞：1)

这道题目用迭代加深搜索来做

控制桶的数量作为深度

依次枚举。

找到解之后直接输出即可。

而每次迭代反复计算的东西，和每一层拓展出来的相比，不值一提。

洛谷这题的数据略水

我们自己rand的数据我要卡常后才能过

（这份代码没有卡常）

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
#define MAX 200
int Q,p;
int v[MAX];//体积
bool fl=false;//标记是否找到解 
int dep;//指定的深度 
int C[MAX];//记录选定的桶 
bool f[MAX*MAX];
inline bool ok()
{
       memset(f,0,sizeof(f));
       f[0]=true;
       for(int i=1;i<=Q;++i)
                for(int j=0;j<dep;++j)
                 if(i>=C[j])
                    f[i]|=f[i-C[j]];
       return f[Q];
}
inline void outp()
{
       cout<<dep<<' ';
       for(int i=0;i<dep;++i)
         cout<<C[i]<<' ';
       cout<<endl;       
}
void DFS(int x,int tot)//上个桶的编号以及已经选的桶的数量 
{
       if(tot==dep)
       {
                if(ok())
                {
                       outp();
                       fl=true;
                }
                return;
       }
       if(fl)return;
       for(int i=x+1;i<=p&&!fl;++i)
       {
                 if(p-i+1<dep-tot)//桶的个数不够到达指定深度 
                    break;
                 C[tot]=v[i];
              DFS(i,tot+1);
              C[tot]=0;
       } 
}
int main()
{
      cin>>Q;
      cin>>p;
      for(int i=1;i<=p;++i)
        cin>>v[i];
      sort(&v[1],&v[p+1]);
      for(int i=1;i<=p;++i)//迭代加深
      {
               dep=i;//最大深度
             DFS(0,0); 
             if(fl)break;
      }
      return 0;
}
```

---

## 作者：zltttt (赞：1)

思路：裸的IDDFS~（DFS好像也可以，然而“自带巨大常数”技能使本蒟蒻果断放弃）


对于IDDFS是什么嘛。。。本蒟蒻简单的口胡一下（大神们请无视并直接goto正文）


IDDFS简介：

就是一种限制深度的DFS……

有点类似空间极小版的广搜，但时间显然是不能比的~（大约慢了不到一倍吧……有错轻喷）

但，如果广搜炸空间（或不知最终所需空间是否会炸）时，它就显得特别有用。

每次我们给DFS设置一个深度上限，到达这个上限便立即停止DFS，回溯。

若在当前最大深度无解则最大深度增加并从根节点重新搜索~

这样上一次搜索的结果不是浪费了吗？

是的，就是浪费了（。。。），但为了不炸空间只能这样。。。

而且据本校某大触称，每一次加大最大深度时重新搜索已搜过的状态所需的时间和搜完扩展出的新状态层所需时间相比 "不值一提"（原话，有错...不关我事...）


正文：


用IDDFS限制每次搜索的深度，在这里是选中的桶的个数。

搜到最大深度时用完全背包判断现有桶能否达到所求解，能就做完了，不能...继续搜啊...

真的不会T，真的（本蒟蒻常数巨大的程序最后一个点才200ms）


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>

using namespace std;

inline int read()
{
    int x=0;
    char ch;
    while(!isdigit(ch=getchar()));
    while(isdigit(ch))
    {
        x=(x<<3)+(x<<1)+ch-48;
        ch=getchar();
    }
    return x;
}

int q,p;
int koishi[233],maxdep;
int satori[233],top=0;
bool f[20233],have[20233];

bool judge(int val)
{
    memset(f,0,sizeof(f));
    
    for(int i=1;i<=top;i++)
        f[satori[i]]=1;
    f[0]=1;

    for(int i=1;i<=top;i++)
        for(int j=(satori[i]<<1);j<=val;j++)
            f[j]|=f[j-satori[i]];

    return f[val];
}

bool iddfs(int dep,int pos)
{
    satori[++top]=koishi[pos];
    bool ret=false;
    
    if(dep==maxdep)
    {
        ret=judge(q);
        if(!ret)goto end;
        else goto accept;
    }
    
    for(int i=pos+1;i<=p;i++)
        if(iddfs(dep+1,i))
        {
            ret=true;
            goto accept;
        }

    end:;
    top--;
    
    accept:;
    return ret;
}

int main()
{
    q=read();
    p=read();
    
    for(int i=1;i<=p;i++)
    {
        if((koishi[i]=read())>q || have[koishi[i]])
            --p,--i;
        have[koishi[i]]=1;
    }
    
    //sort(koishi+1,koishi+p+1);这句玄学的优化在某些点上快些，某些慢些...... 然而最后一个点会变慢......（数据没说输入有序）
    
    for(maxdep=1;maxdep<=p;maxdep++)
        for(int j=1;j<=p;j++)
            if(iddfs(1,j))
                goto getans;
        
    getans:;
    sort(satori+1,satori+top+1);
    
    printf("%d",top);
    for(int i=1;i<=top;i++)
        printf(" %d",satori[i]);
        
    puts("");
    
    return 0;
}
```

---

## 作者：_蒟蒻__ (赞：1)

好多大佬都用了搜索， 但是蒟蒻怀疑自己的马力 (一旁神仙: 其实你就是不会搜!!!) 

那没办法了， 硬着头皮写背包吧。 f就是常规的背包数组， g记录一下方案

其实思路很显然啦 (一旁神仙: 那你还废话啥!!!)

生命苦短, 直接上代码

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int N=110;
const int M=20010;
int n, m, v[N], f[M];

struct prg
{
	int a[N], cnt;
	prg() : cnt(0) {  }
	bool operator < (const prg &t) const // 按题目要求比较f相同时的两个方案 
	{
		if(cnt!=t.cnt) return cnt<t.cnt;
		for(int i=1; i<=cnt; i++)
		if(a[i]!=t.a[i]) return a[i]<t.a[i];
		return 0;
	}
	friend ostream & operator << (ostream &cout, prg t) // 我就是喜欢cout!!! 
	{
		for(int i=1; i<=t.cnt; i++) cout<<t.a[i]<<' ';
		return cout;
	}
	void insert(int x)
	{
		a[++cnt]=x;
		sort(a+1, a+cnt+1); // 大量有序少量无序时, sort跑不够nlogn的 
	}
}g[M];

int main()
{
	ios::sync_with_stdio(false);
	memset(f, 0x3f, sizeof(f));
	f[0]=0;
	cin>>m>>n;
	for(int i=1; i<=n; i++) cin>>v[i];
	
	for(int i=1; i<=n; i++)
	for(int j=m; j>=v[i]; j--)
	for(int k=1; k*v[i]<=j; k++) // 个人感觉for多了缩进不好看
	{
		if(f[j]>f[j-k*v[i]]+1) 
			f[j]=f[j-k*v[i]]+1, g[j]=g[j-k*v[i]], g[j].insert(v[i]);
				
		else if(f[j]==f[j-k*v[i]]+1)
		{
			prg t=g[j-k*v[i]]; 
			t.insert(v[i]);
			if(t<g[j]) g[j]=t;
		}
	} // 这里该是不用说了吧 (好像从一开始就不用说) 
	cout<<f[m]<<' '<<g[m];
	return ~~ (0 ^ 0);
} 
                          
```


---

## 作者：逆流之时 (赞：0)

本题的 dp 使用 bitset 是很简单的。

考虑到本题的基本模型是完全背包，所以我们直接使用 bitset 存储状态，转移时直接通过判断：

```cpp
for (int i = 0; i < n; i++)
	for (int j = w[i]; j <= m; j++) {
		bitset<100> tmp = s[j - w[i]];
		tmp.set(i);
		if (s[j] > tmp) s[j] = tmp;
	}
```

其中 bitset 的大于号需要重载为比较 bitset 字典序的判断。

上面的代码有两点不足：

1. 状态转移方程没有消除后效性。

我们把状态转移方程写成二维形式，则我们使用的是下面这样的方程：

`f[i][j] = min(f[i - 1][j], f[i][j - w[i]]`，

而不是：

`f[i][j] = min(f[i - 1][j], f[i - 1][j - k * w[i]]`（其中 $k \in \mathbb{Z}$）。

因为前面第一种的状态转移方程中，我们不能保证 `f[i][j - w[i]]` 的状态没有使用过第 $i$ 个瓶子，而如果该状态使用了第 $i$ 个瓶子，则该状态向后推时可能会出错，因为这种情况相当于对边权为 $0, 1$ 的图使用普通队列进行 bfs（`f[i][j]` 可能从 `f[i][j - w[i]]` 转移过来时付出了 1 点代价，也有可能没有付出代价），而这样是会出错的（对边权为 $0, 1$ 的图进行 bfs 必须采用双端队列，而且需要对原 bfs 算法进行修改。采用优先队列运行 Dijkstra 也可以，但此时时间复杂度不是线性时间复杂度。使用双端队列的方法在《算法竞赛进阶指南》P117 有具体介绍）

为了避免使用双端队列进行 bfs 导致代码量增加，我们需要把状态转移方程改为后者，保证我们的动态规划相当于对边权为 $1$ 的图进行 bfs。

2. 采用下面的状态转移方程后，动态规划时间复杂度增加，同时在使用 bitset 时出现大量复制操作的情况下，我们的代码很有可能超过时间限制。

所以我们需要把代码从这个形式：

```cpp
for (int i = 0; i < n; i++)
	for (int j = m; j >= w[i]; j--)
		for (int k = w[i]; k <= j; k += w[i]) {
			bitset<100> tmp = s[j - k];
			tmp.set(i);
			if (s[j] > tmp) s[j] = tmp;
		}
```

修改为以下形式：

```cpp
for (int i = 0; i < n; i++)
	for (int j = m; j >= w[i]; j--)
		for (int k = w[i]; k <= j; k += w[i])
			if (s[j - k].count() + 1 < s[j].count()) s[j] = s[j - k], s[j].set(i);
			else if(s[j - k].count() + 1 == s[j].count()) {
				bitset<100> tmp = s[j - k];
				tmp.set(i);
				if (s[j] > tmp) s[j] = tmp;
			}
```

然后就可以过了。

```cpp
#include<cstdio>
#include<algorithm>
#include<bitset>
using namespace std;
int m, n;
int w[100];
bitset<100> s[20005];
bool operator > (const bitset<100>& x, const bitset<100>& y) {
	if (x.count() != y.count()) return x.count() > y.count();
	for (int i = 0; i < 100; i++) if(x.test(i) ^ y.test(i)) return y.test(i);
	return false;
}
int main() {
	scanf("%d%d", &m, &n);
	for (int i = 1; i <= m; i++) s[i].set();
	for (int i = 0; i < n; i++) scanf("%d", &w[i]);
	sort(w, w + n);
	for (int i = 0; i < n; i++)
		for (int j = m; j >= w[i]; j--)
			for (int k = w[i]; k <= j; k += w[i])
				if (s[j - k].count() + 1 < s[j].count()) s[j] = s[j - k], s[j].set(i);
				else if(s[j - k].count() + 1 == s[j].count()) {
					bitset<100> tmp = s[j - k];
					tmp.set(i);
					if (s[j] > tmp) s[j] = tmp;
				}
	printf("%ld", s[m].count());
	for (int i = 0; i < n; i++) if (s[m].test(i)) printf(" %d", w[i]);
	return 0;
}
```


---

## 作者：vinvor (赞：0)

本题纯DP是可以过掉的，但是推荐迭代加深，也好扩扩思路。

要用到迭代加深搜索(DFSID)。由于要求输出的是使用最少的牛奶桶，所以要先找牛奶桶数量为1 的时候所有的组合，如果没有解再找牛奶桶数量为2...直到牛奶桶数量为P。

当搜索到一个组合，判断用这些牛奶桶是否能组成目标解的时候，可以用动态规划的方法来做。设f[i]是当需求的牛奶为i 时，能否形成这个组合，是一个bool型数组。初始条件f[0]=true

状态转移方程f[i]=f[i] or f[ i-v[j] ] (j 为使用的所有牛奶桶)，目标状态f[Q]。如果f[Q]为true，则当前解合法，直接输出即可。

但是如果仅仅这样写还是有一组数据过不去，需要进行一些优化。要优化动态规划的过程。注意一个重要的信息，找到的组合中，每个牛奶桶至少用了一次。上面的状态转移方程中有许多某个牛奶桶使用0 次的冗余状态。可以在初始的时候对(i=1..Q/v[第一个桶])f[ i\*v[第一个桶] ]赋值为true。对每个其他的桶的状态可以直接由前面的状态得出。经过这个优化，数据就可以全过了。

裸DFSID+DP（记忆化搜索），下附代码：

```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cmath>
#define N 100
#define INFI 30000
int n, q, i, v[N + 1], ans[N + 1], cur[N + 1], tot = INFI;
bool flag = false;
void dfs(int depth, int rv, int bc)
{
    if (depth == i)
    {
        if (rv == 0)
        {
            memcpy(ans, cur, i << 2);
            flag = true;
        }
        return;
    }
    if (bc > n || ans[depth] < v[bc]) return; 
    cur[depth] = v[bc];
    for (int m = 1; m * v[bc] <= rv; ++m)
        dfs(depth + 1, rv - m * v[bc], bc + 1);
    if (bc < n) dfs(depth, rv, bc + 1);
}
int main()
{
    scanf("%d%d", &q, &n);
    for (i = 1; i <= n; ++i) scanf("%d", v + i);
    std::sort(v + 1, v + n + 1);
    memset(ans, 127, sizeof ans);
    for (i = 1; i <= n; ++i)
    {
        dfs(0, q, 1);
        if (flag) break;
    }
    tot = i;
    printf("%d ", tot);
    for (i = 0; i < tot; ++i) printf("%d%c", ans[i], i == tot - 1 ? '\n' : ' ');
    return 0;
}
```

---

## 作者：Hunter_Will (赞：0)

貌似没有纯dp的，我来写一发。dp的话，定义f[i][j]表示前i个桶拼出j单位牛奶所用的最小的桶的个数。显然这是一个无穷背包的模型，每个桶都可以用无限次，所以有f[i][j]=max(f[i-1][j],f[i-1][j-k\*v[i]]+1);但是因为还要输出方案，所以不能调换循环顺序使用O(vn)的做法，数据范围比较小，所以也用不着滚动数组了。至于输出方案，我用了一个vector数组记录每个状态的方案，在dp的时候顺便更新，但是因为状态总数比较多，对每一个状态记录方案空间太大，所以我对它用了滚动数组压掉了第一维，在遇到相同答案是比较两种方案的字典序，更新方案。






```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
#define maxn 110
#define maxm 20020
const int INF=0x3f3f3f3f;
int n,m,v[maxn];
int f[maxn][maxm];
vector<int> path[maxm];
void update(int x,int y){
    bool flag=true;
    if(path[x].size()!=path[y].size())puts("error");
    for(int i=0;i<path[x].size();i++){
    if(!flag)path[x][i]=path[y][i];
    else if(path[x][i]==path[y][i])continue;
    else if(path[x][i]<path[y][i])break;
    else {flag=false;path[x][i]=path[y][i];}
    }
}
int readin(){
    int x=0,s=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')s=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*s;
}
int main(){
    m=readin();n=readin();
    for(int i=1;i<=n;i++){
    v[i]=readin();
    }
    sort(v+1,v+n+1);
    memset(f,INF,sizeof(f));
    f[0][0]=0;
    for(int i=1;i<=n;i++){
    for(int j=m;j>=0;j--){
        for(int k=0;k<=j/v[i];k++){
        if(f[i][j]>f[i-1][j-k*v[i]]+(bool)k){
            f[i][j]=f[i-1][j-k*v[i]]+(bool)k;
            if(k){
            path[j].clear();
            path[j]=path[j-k*v[i]];
            path[j].push_back(v[i]);
            }
        }
        else if(f[i][j]==f[i-1][j-k*v[i]]+(bool)k){
            if(k)path[j-k*v[i]].push_back(v[i]);
            update(j,j-k*v[i]);
            if(k)path[j-k*v[i]].pop_back();
        }
        }
    }
    }
    //for(int i=1;i<=n;i++,puts(""))for(int j=0;j<=m;j++)cout<<f[i][j]<<' ';
    if(f[n][m]!=INF)printf("%d ",f[n][m]);
    for(int i=0;i<path[m].size();i++)printf("%d ",path[m][i]);
    return 0;
}
毕竟是dp还是比iddfs快一点的。
```

---

## 作者：Drinkwater (赞：0)

楼下走楼梯大神讲的很清楚了，思路就是IDDFS我们用for循环来枚举选取桶子的个数，爆搜出每个方案，然后去验证，至于验证的方法有两种，类似于记忆化的dfs和无限背包来维护，走楼梯讲的是无限背包的方法，那我讲讲我的dfs吧，其实思路和无限背包一样，搜每个答案就好了。

/*************************************************************************

    > Author: Drinkwater-cnyali
    > Created Time: 2017/5/11 19:46:03
************************************************************************/













```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
#define REP(i, a, b) for(register int i = (a), i##_end_ = (b); i <= i##_end_; ++ i)
#define DREP(i, a, b) for(register int i = (a), i##_end_ = (b); i >= i##_end_; -- i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mem(a, b) memset((a), b, sizeof(a))
template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }
int read()
{
    int sum = 0, fg = 1; char c = getchar();
    while(c < '0' || c > '9') { if (c == '-') fg = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { sum = sum * 10 + c - '0'; c = getchar(); }
    return sum * fg;
}
const int maxn = 100000;
const int inf = 0x3f3f3f3f;
int n,m;
int a[maxn],flag,f;
int pre[maxn],cnt,vis[maxn];
int t[maxn];
void f_a(int sum)
{
    if(f)return ;
    if(sum)
    {
        if(n % sum == 0)
        {f = 1;return ;}
    }   
    if(t[sum])return ;
    t[sum] = 1;
    if(sum > n)return ;
    REP(i,1,cnt)f_a(sum+pre[i]);
}
void dfs(int l,int u)
{
    if(flag)return ;
    if(u == l)
    {
        memset(t,0,sizeof(t));
        f_a(0);
        if(f)
        {
            flag = 1;
            cout<<l<<" ";
            sort(pre+1,pre+1+cnt);
            REP(i,1,cnt)cout<<pre[i]<<" ";
        }
        return ;
    }
    if(u > l)return ;
    REP(i,1,m)
    {
        if(!vis[i])
        {
            vis[i] = 1,pre[++cnt] = a[i];
            dfs(l,u+1);
            vis[i] = 0,cnt--;
        }
    }
}
int main()
{
    n = read(), m = read();
    REP(i,1,m)a[i] = read();
    REP(i,1,m)
    {
        memset(vis,0,sizeof(vis));
        dfs(i,0);
        if(flag)break;
    }
    return 0;
}
```

---

## 作者：ronwhite (赞：0)

迭代搜索+set+记忆化check判定是否可行

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<set>
#include<cstring>
#define rep(i,s,t) for(int i=s;i<=t;i++)
using namespace std;
const int N=200000;
bool f[N],vis[N];
set<int> s;
int tong[N],limit,q,p;
bool check(int x)
{
    if(x==0) return true;
    if(vis[x]) return f[x];
    
    if(!vis[x])
    {
        vis[x]=true;
        for(set<int>::iterator it=s.begin();it!=s.end();it++)
        {
            if(x-*it>=0)
                if(check(x-*it))
                    return f[x]=true;
        }
    }
    return false;        
}
void dfs(int deep)
{
    if(deep==limit)
    {
        memset(f,false,sizeof f);
        memset(vis,false,sizeof vis);
        if(check(q))
        {
            printf("%d ",s.size());
            for(set<int>::iterator it=s.begin();it!=s.end();++it)
                printf("%d ",*it);
            
            exit(0);
        }
        return;
    }
    rep(i,1,p)
    {
        if(s.count(tong[i])) 
        continue;
        
        s.insert(tong[i]);
        dfs(deep+1);
        s.erase(tong[i]);
    }
}
            
int main()
{
    
    scanf("%d%d",&q,&p);
    rep(i,1,p) scanf("%d",tong+i);
    sort(tong+1,tong+p+1);
    for(int i=1;i<=p;i++)
        s.clear(),limit=i,dfs(0);
        
    return 0;
}
    
```

---

## 作者：SteinsGate0 (赞：0)

跌带加深+dp判解

从小枚举dep,搜索层数大于时return.

dp(背包判断是否成立）；

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<cstring>
#define maxn 105
using namespace std;
int block[maxn],ans[maxn],top,n,m;
bool b[20005],flag=0;
int _read(int &data)
{    data=0;
    char t=getchar();
    bool mark=0;
    while(t<48||t>57){if(t==45)mark=1;t=getchar();}
    while(48<=t&&t<=57){data=(data<<1)+(data<<3)+t-48;t=getchar();}
    if(mark)data=-data;
}
bool dp(int x)//背包判断是否成立
{
    int i,j;
    memset(b,0,sizeof(b));
    b[0]=1;
    for(i=1;i<=x;i++)
    for(j=ans[i];j<=m;j++)
    if(b[j-ans[i]]) b[j]=1;
    if(b[m]) return true;
}
void dfs(int c,int x)
{
    if(flag==1) return;
    int i,j;
    if(c==0)//层数大于限定时，return
    {        if(dp(top)) 
        {            flag=1;
            printf("%d ",top);
            for(i=1;i<=top;i++) printf("%d ",ans[i]);
        }
    }
    else if(x<=n)
    {        ans[++top]=block[x];
        dfs(c-1,x+1);
        ans[top--]=0;
        if(flag==0) dfs(c,x+1);
    }
}
int main()
{
    int i,j;
    _read(m);_read(n);
    for(i=1;i<=n;i++) _read(block[i]);
    sort(block+1,block+1+n);//说了字典序最小
    for(i=1;i<=n&&flag==0;i++)//我特判了下，是不是傻？？？
    {        if(m%block[i]==0) 
        {            flag=1;
            printf("1 %d",block[i]);
            return 0;
        }
    }
    for(i=1;i<=n&&flag==0;i++)
    {        dfs(i,1);//迭代层数咯。。。。
    }
    return 0;
}
```

---

## 作者：ysner (赞：0)

这是一道背包动态规划与搜索结合的题目，由小到大DFS搜取桶个数，背包动态规划（完全背包）来判断K个桶是否

能能测体积为V的牛奶。

相比于其他题解，我的注释貌似更详尽，我的程序貌似更易懂。

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int a[101],use[101],v,n,k;
void print()
{
  printf("%d ",k);
  for (int i=1;i<=k;i++)
    printf("%d ",a[use[i]]);
  exit(0);//输完情况直接跳回主函数 
}
void dp()//完全背包，判断取K个桶时能否取到体积为V的情况（转化：K个桶即为K种物品，每种物品有无限个，体积为背包容积，原来的最大价值由于不用管，存是否可行就行了） 
{
  int f[20010];
  memset(f,0,sizeof(f));
  f[0]=1;//f[i]指体积为i时是否能取到（用bool类型等效） 
  for (int i=1;i<=k;i++)
    for (int j=1;j<=v/a[use[i]];j++)
      f[j*a[use[i]]]=1;//先初始化，表明能取到体积为一个桶体积的倍数的情况(==1) 
  for (int i=1;i<=k;i++)
    for (int j=a[use[i]];j<=v;j++)//use[i]记录取第i个桶时取到桶的编号(只在取k个桶的情况内有效） 
      f[j]=f[j]||f[j-a[use[i]]];//如果||两边情况有一种情况取得到（==1）就能取到体积为j那种情况 
    if (f[v]==1)//一取到要求的体积就输出（保证字典序最小） 
      print();
}
void dfs(int dep)//枚举取K个桶时取哪几个桶 
{
  for (int i=use[dep-1]+1;i<=n-k+dep;i++)//下一次递归就是上次取到的桶的下一个开始，多取一个桶，
  //i的最大范围实际是为后面搜（k-dep)个桶留有起码的空间（后面每个i都取一个桶） 
   {
    use[dep]=i;
    if (dep==k)//直到取到k个桶为止 
      dp();
    else
      dfs(dep+1);
   }
} 
void fenzu()//枚举取K个桶的情况，由于是从小到大搜，可以保证搜到的第一个情况为取的个数最小的情况 
{
     for (k=1;k<=n;k++)
     dfs(1);
}
int main()
{
  int i;
  //freopen("milk.in","r",stdin);
  //freopen("milk.out","w",stdout);
  scanf("%d",&v);
  scanf("%d",&n);
  for (i=1;i<=n;i++)
    scanf("%d",&a[i]);
  sort(a+1,a+n+1);
  fenzu();
  //fclose(stdin);
  //fclose(stdout);
  return 0;
}
```

---

