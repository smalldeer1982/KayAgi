# [USACO09DEC] Video Game Troubles G

## 题目描述

农夫约翰的奶牛们非常喜欢玩电子游戏！FJ 发现，在玩了这些游戏后，他的奶牛产的奶比平时多得多，这肯定是因为快乐的奶牛产奶更多。

然而，奶牛们对于哪个是最好的游戏机存在分歧。一头奶牛想买 Xbox 360 来玩《光环 3》；另一头想买任天堂 Wii 来玩《任天堂明星大乱斗》；第三头想在 PlayStation 3 上玩《合金装备 4》。FJ 想购买一套游戏机（每种不超过一台）和游戏（每种不超过一个——并在给定预算的限制内），以帮助他的奶牛产出最多的牛奶，从而养育更多的孩子。

FJ 调查了 $N$ 台游戏机（$1 \leq N \leq 50$），每台游戏机的价格为 $P_i$（$1 \leq P_i \leq 1000$），以及特定于该游戏机的游戏数量 $G_i$（$1 \leq G_i \leq 10$）。当然，奶牛必须先拥有一台游戏机，才能购买该游戏机特定的任何游戏。每个游戏都有一个游戏价格 $GP_j$（$1 \leq GP_j \leq 100$）和一个生产值（$1 \leq PV_j \leq 1,000,000$），表示奶牛在玩游戏后会产出多少牛奶。最后，农夫约翰有一个预算 $V$（$1 \leq V \leq 100,000$），这是他最多能花的钱。帮助他最大化他购买的游戏的生产值之和。

考虑一个数据集，$N=3$ 台游戏机，预算 $V=800$ 美元。第一台游戏机价格为 $300 美元，并有两个游戏，价格分别为 $30 美元和 $25 美元，生产值如下所示：

游戏编号    价格    生产值

1       $30          50

2       $25          80

第二台游戏机价格为 $600 美元，只有一个游戏：

游戏编号    价格    生产值

1       $50          130

第三台游戏机价格为 $400 美元，有三个游戏：

游戏编号    价格    生产值

1       $40         70

2       $30         40

3       $35         60

农夫约翰应该购买游戏机 1 和 3，游戏机 1 的游戏 2，以及游戏机 3 的游戏 1 和 3，以最大化他的期望生产值为 210：

```cpp
                                生产值
        预算:     $800      
        游戏机 1  -$300
           游戏 2   -$25              80
        游戏机 3  -$400
           游戏 1   -$40              70
           游戏 3   -$35              60
      -------------------------------------------
        总计:         0 (>= 0)      210
```


## 说明/提示

（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
3 800 
300 2 30 50 25 80 
600 1 50 130 
400 3 40 70 30 40 35 60 
```

### 输出

```
210 
```

# 题解

## 作者：Gavin·Olivia (赞：13)

魔鬼教练举行了一次连续三天的动规测试，这题是T2(一共31题）我再也不想打动规了（手动黄豆再见）

这题很明显是背包类动规，最容易想到的思路当然是像金明的预算方案一样做分组01背包，$f[i]$表示花费为$i$时奶牛的最大产出值。状态转移方程也很好推。然而，不用试也知道

$\huge{TLE!}$

经过观察我们可以很轻易地得到一个结论，每个游戏平台之间是互不影响的，那么我们就有了一个大胆的想法：可不可以把当前平台单独动规出来后与前面合并呢？所以就有了$g$数组，$g[j]$表示在已经买了当前平台$i$的前提下，在$1$~$i$平台共花费$j$元所能带来的最大产出,是个简单的01背包（我相信你们都会哒）。然后将$g$和$f$数组进行合并（$f[j]=max(f[j],g[j])$）。具体实现过程看代码。

```cpp
#include<bits/stdc++.h>
 using namespace std;
 int i,j,k,n,v,p,gc,gp,pv;
 long long f[1000005],g[1000005];
 inline int read()
{
	int x=0,c; bool f=0;
	for(;(c=getchar())<'0'||c>'9';f|=c=='-');
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+c-48;
	return f?-x:x;
}
 int main()
{
	n=read(); v=read();
	for(i=1;i<=n;i++)
	{
		p=read(); gc=read();
		for(j=p;j<=v;j++) g[j]=f[j-p];
		for(j=1;j<=gc;j++)
		{
			gp=read(); pv=read();
			for(k=v-gp;k>=p;k--) g[k+gp]=max(g[k+gp],g[k]+pv);
		}
		for(j=p;j<=v;j++) f[j]=max(g[j],f[j]);
	}
	printf("%d",f[v]);
	return 0;
}
```

---

## 作者：PaulFrank (赞：8)

马上就要2017NOIP复赛了,在此发复赛前的最后一篇题解,望管理员给予采纳！

本题看楼下写的代码有些冗长,在此发一篇较短题解,感谢SLQ老师的启发!

在这里我们用f[i][j]表示前i组总和为j的最小代价,此题还需关注i与j的取值范围,为了优化空间用上了滚动数组

我们通过探索可知道f[i][j]与f[i-1][j-p]和f[i-1][j]有关

还可优化成一维数组,请读者自己完成

详情看代码注释吧

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int k,n,V,a,b,p,g,f[2][100005];//滚动数组
inline int Max(int a,int b){
       return a>b?a:b;
} 
inline int read(){
    int ans=0,ok=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {
        if(ch=='-')ok=-1;
        ch=getchar();
    }
    for(;ch>='0'&&ch<='9';ch=getchar()) ans=ans*10+ch-'0';
    return ans*ok;
}
int main(){
    freopen("vidgame.in","r",stdin);
    freopen("vidgame.out","w",stdout);
    n=read(),V=read();
    for(register int i=1;i<=n;i++){
        p=read(),g=read();
        for(register int j=p;j<=V;j++)
            f[i&1][j]=f[(i-1)&1][j-p];//p为平台i的价值,假设每个游戏必须买 
        while(g--){
            a=read(),b=read();
            for(register int j=V;j>=a+p;j--)//范围为>=a+p,即为游戏平台的价格再加上每个游戏的价格 
                f[i&1][j]=Max(f[i&1][j],f[i&1][j-a]+b);//减去价格,加上产出值 
        }
        for(register int j=0;j<=V;j++)
            f[i&1][j]=Max(f[i&1][j],f[(i-1)&1][j]);//不选 
    }
    printf("%d\n",f[n&1][V]);
    return 0;
}
```
FINISHED!!

---

## 作者：Yang818 (赞：4)

## 题目大意
$n$ 种游戏主机，第 $i$ 种主机的价格是 $P_i$。该主机有 $G_i$ 个独占游戏。很明显，奶牛必须先买进一种游戏主机，才能买进在这种主机上运行的游戏。在每种主机中，游戏 $j$ 的价格为 $\mathit{GP}_j$，每头奶牛在玩了该游戏后的牛奶产量为 $\mathit{PV}_j$。预算为 $V$。请帮怎么购买，产出值的和最大。

## 分析
### 给定空间的最大价值，明显的背包啊！

$f_{i,j,v}$ 表示现在第 $i$ 个平台，第 $j$ 个游戏，现有预算为 $v$ 的情况下的最大产量。

$$f_{i,j,v}=\max(f_{i,j-1,v},f_{i,j-1,v- \mathit{GP}_{ij}} + \mathit{PV}_{ij} )$$

到现在为止这个方程不完整，只对后两位进行了递推，$i$ 没有递推过，所以还要加上。

$f_{i,0,v}$ 表示确定要用第 $i$ 个主机

其实这个方程里面有一个隐含条件就是我们会用第 $i$ 个主机。这样的话我们还需要考虑分给第 $i$ 个主机多少钱。所以要再修改一下。~~好麻烦~~

$g_{i,v}$ 考虑前 $i$ 个平台最大收益。

$$g_{i,v}=\max_{0\leqslant k\leqslant v}h_{i,k}+g_{i-1,v-k}$$

其中 $h_{i,k}=f_{i,G_i,k-P_i
}$



## 代码

```cpp
#include<iostream>
#include<algorithm>
const int maxv = 100001;
int save[maxv], fork[maxv];
int main()
{
  int n, v;
  std::cin >> n >> v;
  while (n --> 0) {
  	int p, g;
  	std::cin >> p >> g; 
  	for (int x = 0; x+p <= v; ++x)	// fork 在 [0, p) 之间是无效的	  	
  	  fork[x+p] = save[x];  	  
  	while (g --> 0) {
  	  int pv, gp;
  	  std::cin >> gp >> pv;
  	  for (int x = v-gp; x >= p; x--) 
  	    fork[x+gp] = std::max(fork[x+gp], fork[x] + pv);  	    
  	}
  	for (int x = v; x >= p; x--)
  	  save[x] = std::max(save[x], fork[x]); 
  }
  std::cout << save[v];
}
```
望通过！谢谢管理员大大！




---

## 作者：walk_out_study (赞：3)

### 题意
你有 $p$ 元，有 $N$ 种商品，每种需要 $V$ 元解锁，解锁后才能购买价格为 $v_i$，价值为 $w_i$ 的商品，问能获得的最大价值。

-----
### 思路
先对每一种商品进行讨论，下标统一用 $j$，因为 $i$ 只是不用在状态中写出，其实还是有的。 

假设不需要解锁商品，就成了 01 背包的模板。直接定义 $dp_j$ 为最多花费 $j$ 元的最大价值，然后做 01 背包。

现在再来解锁商品。假设最多花 $x$ 元，但实际在 $dp$ 中买不到 $dp_x$，只能买到 $dp_{x-V}$，直接更新数组即可，我们就得到了**解锁了当前种类，花费** $j$ **元的最大价值**。

再设 $ddp_j$ 为考虑完当前平台，最多花费 $j$ 元的最大价值。就有 $ddp_j=\max{ddp_j,dp_j}$。

#### 初始值

对于每种商品，都要更新 $dp$，来维护 $dp_j$ 为最多花费 $j$ 元的最大价值的定义。

---
这题其实是 dp 套了一个 dp。比较考验对 01 背包，定义状态的能力。代码很短，但对剖析问题有高要求。

最后把 $ddp_P$，即最多花费 $P$ 元的最大价值输出即可。
```cpp
#include<iostream>
using namespace std;
int N,p,n,V,v,w,dp[111111],ddp[111111]; 
int main()
{
	cin>>N>>p;
	while(N--) {
		cin>>V>>n;
		for(int j=0;j<=p;j++)//维护最多花费 j 元的最大价值 
			dp[j]=ddp[j];
		while(n--)
		{
			cin>>v>>w;
			for(int j=p;j>=v;j--)
				dp[j]=max(dp[j],dp[j-v]+w);// 01 背包 
		}
		for(int j=p;j>=V;j--)//更改状态为 解锁当前商品，最多花费 j 元的最大价值 
			dp[j]=dp[j-V];
		for(int j=p;j>=V;j--)//更新答案 
			ddp[j]=max(dp[j],ddp[j]);
	}
	cout<<ddp[p];
	return 0;
}

```

---

## 作者：kakakaka (赞：3)

本题动态规划分组背包问题，当然也可以说是金明的预算方案的加强版。

本人刚刚看到这道题时果断把金明的预算方案修改之后就交上来了，基本思路就是先整合成很多种物品，然后分组背包。

结果显然……超时，错误代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;
int n,m;
int head[101],size;
struct student
{
    int n,next,m,w;
}edge[50001];
int dp[1000001],tdp[1000001];
int main()
{
    int i,j,k,mm,to,mw,ww;
    cin>>n>>m;
    for(i=1;i<=n;i++)head[i]=-1;
    for(i=1;i<=n;i++)
    {
        scanf("%d%d",&mm,&to);
        size++;
        edge[size].n=i;
        edge[size].m=mm;
        edge[size].w=0;
        edge[size].next=head[i];
        head[i]=size;
        size++;
        edge[size].n=i;
        edge[size].m=0;
        edge[size].w=0;
        edge[size].next=head[i];
        head[i]=size;
        for(j=1;j<=to;j++)
        {
            scanf("%d%d",&mw,&ww);
            for(k=head[i];k!=-1;k=edge[k].next)
            if(edge[k].m!=0)
            {
                size++;
                edge[size].n=i;
                edge[size].m=mw+edge[k].m;
                edge[size].w=ww+edge[k].w;
                edge[size].next=head[i];
                head[i]=size;
            }
        }
    }
    for(i=1;i<=n;i++)
    {
        for(j=head[i];j!=-1;j=edge[j].next)
        {
            int p=edge[j].m,q=edge[j].w;
            for(k=m;k>=p;k--)
            {
                tdp[k]=max(max(tdp[k],dp[k]),q+dp[k-p]);
            }
        }
        for(j=m;j>=1;j--)
        {
            dp[j]=max(dp[j],tdp[j]);
            tdp[j]=0;
        }
    }
    cout<<dp[m];
    return 0;
}
```
显然是需要优化的，用f[i][j]表示前i组物品总和为j的最大值，dp就可以了。
当然，洛谷内存限制128MB，然后就炸了空间。

错误代码如下：

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstdlib>
using namespace std;
int f[51][1000001],mm[51],s[51],m[51][11],w[51][11],n,v,ans;
int main()
{
    int i,j,k;
    cin>>n>>v;
    for(i=1;i<=n;i++)
    {
        scanf("%d%d",&mm[i],&s[i]);
        for(j=1;j<=s[i];j++)
        {
            scanf("%d%d",&m[i][j],&w[i][j]);
        }
    }
    for(i=1;i<=n;i++)
    {
        for(j=0;j<mm[i];j++)
        f[i][j]=f[i-1][j];
        for(j=mm[i];j<=v;j++)
        f[i][j]=f[i-1][j-mm[i]];
        for(j=1;j<=s[i];j++)
        {
            for(k=v-m[i][j];k>=mm[i];k--)
            f[i][k+m[i][j]]=max(f[i][k+m[i][j]],f[i][k]+w[i][j]);
        }
        for(j=mm[i];j<=v;j++)
        f[i][j]=max(f[i][j],f[i-1][j]);
    }
    cout<<f[n][v];
    return 0;
}
```
然后由于每一次dp中f[i][j]都只和f[i-1][j]有关系，所以可以将程序简化成两个一维数组。
AC代码如下：

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstdlib>
using namespace std;
int f1[1000001],f2[1000001],mm[51],s[51],m[51][11],w[51][11],n,v,ans;
int main()
{
    int i,j,k;
    cin>>n>>v;
    for(i=1;i<=n;i++)
    {
        scanf("%d%d",&mm[i],&s[i]);
        for(j=1;j<=s[i];j++)
        {
            scanf("%d%d",&m[i][j],&w[i][j]);
        }
    }
    for(i=1;i<=n;i++)
    {
        for(j=mm[i];j<=v;j++)
        f2[j]=f1[j-mm[i]];
        for(j=1;j<=s[i];j++)
        {
            for(k=v-m[i][j];k>=mm[i];k--)
            f2[k+m[i][j]]=max(f2[k+m[i][j]],f2[k]+w[i][j]);
        }
        for(j=mm[i];j<=v;j++)
        f1[j]=max(f2[j],f1[j]);
    }
    cout<<f1[v];
    return 0;
}
有史以来本人最曲折的一道题目，于是果断发题解了。
```

---

## 作者：xueshengyi (赞：2)

~~CSP RP++~~

这道题就是一个背包升级的板子，

~~我不会告诉你，这题我用了半个小时才做完~~

本题的思路是：

第一步：

先忽略第 $i$ 台主机的价格，只对第 $i$ 款游戏的 $G _ {i}$ 款游戏做01背包，此时得到的 $f[i][j]$ 为从前 $i$ 台主机中花费了 $j$ 元购买游戏得到的伪收益。

第二步：

再考虑第 $i$ 台主机的价格，计算第 $i$ 阶段的真实收益 $f1[i][j]$。对于第 $i$ 阶段，要么不买第 $i$ 台主机及其游戏，此时 $f1[i]=f[i-1] [j]$。要么购买第i台主机及其若干款游戏，那么此时 $f1[i] [j] =f1 [i] [j-p[i]]$。

话不多说，上代码。
```cpp
#include <bits/stdc++.h>
using namespace std;
int p[60],x[60],pp[60][20],v[60][20],f[105][100001],f1[105][100001];
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>p[i]>>x[i];
        for(int j=1;j<=x[i];j++)
        {
            cin>>pp[i][j]>>v[i][j];
        }
    }
    memset(f,0xcf,sizeof(f));
    memset(f,0xcf,sizeof(f));
    f1[0][0]=0;
    for(int i=1;i<=n;i++)
    {
        for(int k=0;k<=m;k++)
        {
            f[i][k]=f1[i-1][k];
        }
        for(int j=1;j<=x[i];j++)
        {
            for(int k=m;k>=0;k--)
            {
                if(k>=pp[i][j])
                {
                    f[i][k]=max(f[i][k],f[i][k-pp[i][j]]+v[i][j]);
                }
            }
        }
        for(int k=0;k<=m;k++)
        {
            f1[i][k]=f1[i-1][k];
            if(k>=p[i])
            {
                f1[i][k]=max(f1[i][k],f[i][k-p[i]]);
            }
        }
    }
    int ans=-1e9;
    for(int i=0;i<=m;i++)
    {
        ans=max(ans,f1[n][i]);
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：cjrqwq (赞：2)

## 思路
有购买需要的条件、有价格、有价值、求最大价值。不难看出，这是一道有依赖的背包问题。

有依赖的背包问题就是要先把某一个物品取走，才能取后面的某些物品。所以需要对 **分背包**（每个平台）里的所有物品进行01背包，再用 **总背包** （最终结论）对 **分背包** 进行分组背包得出最优解。

但是此时有一个问题—— **TLE** 出现了。

有一个结论是显而易见的，就是 **总背包** 每一次结论都可以得出一个最优的子结构。所以就可以继承之前的最优解进行 **一定要购买游戏平台** 的决策。既然可以选择用最优解进行背包，何必要重新开始呢？

最后将继承之前的决策与购买新的游戏平台求最优解就好了。

## 细节

动态规划是有很多细节需要注意的，不是说思路对了就能 AC  。

### 细节1

每一次的 **购买平台决策** 所需花费对应着总背包的什么花费？

### 细节2

对于分背包， V~V-P 的价值可不可能被用到？

-------------

思考并明白了以上 ~~做题时的大坑~~ 问题，才算真正明白此题。

```cpp

#include<bits/stdc++.h>
using namespace std;
int N,gwi,gvi,p,G,V,gdp[111111],dp[111111];
int main() {
	scanf("%d%d",&N,&V);
	while(N--) {
		scanf("%d%d",&p,&G);
		for(int i=0;i<=V-p;i++) {
			gdp[i]=dp[i];
		}
		while(G--) {
			scanf("%d%d",&gvi,&gwi);
			for(int j=V-p;j>=gvi;j--) {
				gdp[j]=max(gdp[j],gdp[j-gvi]+gwi);
			}
		}
		for(int i=V;i>=p;i--)
			dp[i]=max(dp[i],gdp[i-p]);
	}
	cout<<dp[V];
	return 0;
}
```



---

## 作者：Ascnbeta (赞：1)

## P2967 Video Game Troubles G
一道不错的依赖背包问题，评蓝在目前感觉已经略显水分。

## 题面大意
预算为 $V$，现在有 $N$ 组物品，在选该组物品之前需要先花费 $P_i$（依赖关系），然后才可以选择本组所有物品，每个物品也有自己的 $gp_i$ 和 $pg_i$，在预算不超过 $V$ 前提下最大化价值 $PG$。

## 思路分析
显然这是一道依赖背包问题，建议先完成 [P1064](https://www.luogu.com.cn/problem/P1064)，了解什么是依赖背包问题以及如何处理依赖关系。

回到这题，类比多重背包优化的~~或者说是 P1064~~ 思路，我们可以想到把主机和其独占游戏打包成新的物品，但是这题问题在于一台主机最多有 $10$ 款独占游戏，打包的复杂度过高，难以接受。

那该怎么办呢？注意到这题的区别在于：主机本身除了花销不会产生价值，而所有游戏都一定依赖于某一款主机。因此我们就可以以主机来划分阶段，以预算划分状态，对每一个主机所带游戏进行 01 背包，问题就解决了。
## 具体实现
代码中使用了两个数组 $dp$ 和 $dpt$ 用于动态规划。其中 $dpt$ 是用于在不考虑**第** $i$ 款主机费用的情况下，**前** $i$ 款主机的最大价值。在对该款主机的所有游戏 01 背包后，再用里面的数据扣除**第** $i$ 款主机的价格后，决策选不选第 $i$ 款主机，并更新 $dp$ 数组。注意在对新的一款主机的游戏做 01 背包之前先把 $dp$ 的值拷贝到 $dpt$ 数组中。

最后答案就是 $dp_i$ 的最大值。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,V;
int g[53];
vector<int> p[53],v[53];//p 是价格,v 是价值
int dp[100004],dpt[100004];
int main () {
	cin >> n >> V;
	for (int i = 1; i <= n; i++) {
		cin >> g[i];
		int x;
		cin >> x;
		for (int j = 1; j <= x; j++) {
			int y,z;
			cin >> y >> z;
			p[i].push_back(y);
			v[i].push_back(z);
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= V; j++) dpt[j] = dp[j];//拷贝dp到dpt中
		for (int j = 0; j < p[i].size(); j++) {
			for (int k = V; k >= 0; k--) {
				if (k >= p[i][j]) {
					dpt[k] = max(dpt[k-p[i][j]]+v[i][j],dpt[k]);//对该主机游戏做 01 背包，注意到因为需要上一主机的数据，需要倒序枚举。
				}
			}
		}
		for (int j = 0; j <= V; j++) {
			if (j >= g[i]) {
				dp[j] = max(dp[j],dpt[j-g[i]]);//扣除该主机价格后决定是否选择该主机。
			}
		}
	}
	int ans = 0;
	for (int i = 0; i <= V; i++) ans = max(ans,dp[i]);
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：Y_QWQ_Y (赞：1)

# P2967【Video Game Troubles G】题解

扯一句题外话：不愧是 FJ，养的奶牛都会打游戏。

## 接下来进入正题：

## STEP0

很明显，本题是一道 dp。我们将主机和它的游戏看做一个组，按已经处理的主机数量划分阶段。设阶段变量 $i$ 表示已处理前 $i$ 台主机，设 $f[i][j]$ 为代表前 $i$ 台主机恰好花费 $j$ 元时的最大产奶量。

## STEP1

我们先忽略第 $i$ 台主机的价格，对该主机的 $G_i$ 款游戏做 01 背包。这个时候的 $f[i][j]$ 从前 $i$ 台主机中花费 $j$ 元购买游戏得到的伪收益（即买了第 $i$ 台主机的游戏但没算主机的钱）。

## STEP2：

再考虑第 $i$ 台主机的价格，计算当前阶段的真实收益 $ff[i][j]$。对于第 $i$ 阶段，要么不买第 $i$ 台主机和它的游戏，$ff[i][j]=ff[i-1][j]$；或者买，$ff[i][j]=f[i-1][j-P_i]$（$P_i$ 为第 $i$ 台主机的价格）。

接下来就是构造代码
```cpp
#include <bits/stdc++.h>
#define int long long
#define sycn ios::sync_with_stdio (0),cin.tie (0), cout.tie (0)
using namespace std;
int n, m, P[55], num[55], p[55][15], f[55][100001], ff[55][100001], v[55][15], ans = -2e18;
signed main ()
{
	sycn;
	cin >> n >> m;
	for (int i = 1; i <= n; ++ i)
	{
		cin >> P[i] >> num[i];
		for (int j = 1; j <= num[i]; ++ j)cin >> p[i][j] >> v[i][j];
	}
	memset (f, 0xcf, sizeof (f));
	for (int i = 1; i <= n; ++ i)
	{
		for (int j = 0; j <= m; ++ j)ff[i][j] = f[i][j] = ff[i - 1][j];//先把过去的状态传递到f[i][j]
		for (int j = 1; j <= num[i]; ++ j)for (int k = m; k >= 0; -- k)if (k >= p[i][j])f[i][k] = max (f[i][k], f[i][k - p[i][j]] + v[i][j]);//计算伪收益
		for (int j = 0; j <= m; ++ j)if (j >= P[i])ff[i][j] = max (ff[i - 1][j], f[i][j - P[i]]);//状态转移
	}
	for (int i = 0; i <= m; ++ i)ans = max (ans, ff[n][i]);//最后统计答案即可
	cout << ans;
	return 0;
}
```


---

## 作者：zmxqs (赞：1)

## 发布一个滚动数组的做法，巧妙地节省掉许多空间


~~就这也能是USACO金组？这题也太没难度啊~~

用$dp_{i}{j}$表示在费用为$i$、选到第$j$个主机时的最大价值

不难推出方程转移式$dp_{i+p}{j}=$ $\max{(dp_{i-GP_j}{j-1}+PV_j,dp_{i}{j-1})}$

进一步推导可知，当前的状态只和上一次的状态有关

则方程转移式为：

$dp_{i+p}{\text{j mod 2}}=$ $\max{(dp_{i-GP_j}{\text{(j+1) mod 2}}+PV_j,dp_{i}{\text{(j+1) mod 2}})}$

（本人$\LaTeX$略菜，不要喷啊）


接下来就是愉快的 Coding 时间了

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXV = 100000 + 10000 ;
int dp[MAXV][2] ;
int n,v;

int main() {
	scanf("%d%d",&n,&v);
	for(int t=1;t<=n;++t) {
		int p,g;
		scanf("%d%d",&p,&g);
		for(int i=p;i<=v;++i) {
			dp[i][t&1]=dp[i-p][t&1^1];
		}
		for(int k=1;k<=g;++k) {
			int gp,pv;
			scanf("%d%d",&gp,&pv);
			for(int i=v;i>=gp+p;--i) {
				dp[i][t&1]=max(dp[i][t&1],dp[i-gp][t&1]+pv);
			}
		}
		for(int i=1;i<=v;++i) {
			dp[i][t&1]=max(dp[i][t&1],dp[i][t&1^1]);
		}
	}
	printf("%d",dp[v][n&1]);
	return 0;
}
```

Update1:修改了2处错误
Update2:修改了一个单词的拼写错误，请管理通过一下（原本已经通过两次了）

---

## 作者：_Weslie_ (赞：0)

很好的一道题，使我的背包旋转，

## Solution P2967

### Idea

如果我们直接背包，第一不方便考虑限制，第二可能会 TLE。

但是不难发现每一个游戏机之间是不冲突的。这意味着第 $i$ 个游戏机如何选取不会影响第 $i+1$ 个游戏机的选取。

我们考虑每个游戏机当做一个子任务。然后对这个子任务跑 01 背包。

设 $dp_{i,j}$ 为考虑到游戏机 $i$ 的总花费为 $j$ 的最大价值。

对于选了的情况，显然有先选这个游戏机的价格：$dp_{i,j}=dp_{i-1,j-v}$，其中 $v$ 为游戏机价格。

然后选游戏，做 01 背包即可，$dp_{i,j}=\max(dp_{i,j-v}+w,dp_{i,j}$，其中 $v$ 为游戏价格，$w$ 为价值。、

可能有人会问为什么是 $dp_{i,j-v}$。实际上因为限制，我们要求转移必须以选了这个游戏机作为前提。如果先转移选了，这个时候 $dp_{i,j-v}$ 一定是一个选了的状态。

如果这个游戏机不选，就很简单：$dp_{i,j}=dp_{i-1,j}$。

### Code

```
#include<bits/stdc++.h>
using namespace std;
const int N=55,M=100005;
int n,m,w,v,d,dp[2][M],k;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&d,&k);
		for(int j=d;j<=m;j++){
			dp[i&1][j]=dp[(i-1)&1][j-d];
		}
		while(k--){
			scanf("%d%d",&v,&w);
			for(int j=m;j>=v+d;j--){//v+d 的原因是要包括游戏机的价格
				dp[1&i][j]=max(dp[i&1][j],dp[i&1][j-v]+w);
			}
		}
		for(int j=0;j<=m;j++){
			dp[i&1][j]=max(dp[i&1][j],dp[(i-1)&1][j]);
		}
	}
	printf("%d",dp[n&1][m]);
	return 0;
}
```

---

