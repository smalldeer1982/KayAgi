# Birds

## 题目描述

Apart from plush toys, Imp is a huge fan of little yellow birds!

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922E/3bbf7144a65fde520de46a3e8b677997bfb55fe8.png)To summon birds, Imp needs strong magic. There are $ n $ trees in a row on an alley in a park, there is a nest on each of the trees. In the $ i $ -th nest there are $ c_{i} $ birds; to summon one bird from this nest Imp needs to stay under this tree and it costs him $ cost_{i} $ points of mana. However, for each bird summoned, Imp increases his mana capacity by $ B $ points. Imp summons birds one by one, he can summon any number from $ 0 $ to $ c_{i} $ birds from the $ i $ -th nest.

Initially Imp stands under the first tree and has $ W $ points of mana, and his mana capacity equals $ W $ as well. He can only go forward, and each time he moves from a tree to the next one, he restores $ X $ points of mana (but it can't exceed his current mana capacity). Moving only forward, what is the maximum number of birds Imp can summon?

## 说明/提示

In the first sample base amount of Imp's mana is equal to $ 12 $ (with maximum capacity also equal to $ 12 $ ). After he summons two birds from the first nest, he loses $ 8 $ mana points, although his maximum capacity will not increase (since $ B=0 $ ). After this step his mana will be $ 4 $ of $ 12 $ ; during the move you will replenish $ 4 $ mana points, and hence own $ 8 $ mana out of $ 12 $ possible. Now it's optimal to take $ 4 $ birds from the second nest and spend $ 8 $ mana. The final answer will be — $ 6 $ .

In the second sample the base amount of mana is equal to $ 1000 $ . The right choice will be to simply pick all birds from the last nest. Note that Imp's mana doesn't restore while moving because it's initially full.

## 样例 #1

### 输入

```
2 12 0 4
3 4
4 2
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4 1000 10 35
1 2 4 5
1000 500 250 200
```

### 输出

```
5
```

## 样例 #3

### 输入

```
2 10 7 11
2 10
6 1
```

### 输出

```
11
```

# 题解

## 作者：开始新的记忆 (赞：11)

题目大意：现在有n棵树，第i棵树上有ci只鸟，每只的价格为costi，初始你有w元，持有钱的上限也是w元，你每买一只鸟会增加b的上限，你每走过一棵树会增加x元，请问最后你能买多少只鸟。

大致思路：一看题很像背包，用DP。先看数据范围，发现dp的下标不能是钱数因为钱数是1e9级别的，所以我们换个思路，把鸟的个数换成下标，然后把dp的值换成钱数。于是有dp[i][j]表示走到第i棵树下，这时候已经买了j只鸟，剩下的钱数,dp[i][j]=max{dp[i-1][j-k]-k*c[i-1]+x}

code:
```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll c[1010],cost[1010],dp[1010][10010],sum=0,n,w,b,x,ans=0;
 
int main()
{	cin>>n>>w>>b>>x;
	for(int i=1;i<=n;++i) 
		cin>>c[i];
	for(int i=1;i<=n;++i) 
		cin>>cost[i];
	memset(dp,-1,sizeof(dp));
	dp[0][0]=w;
	for(int i=1;i<=n;++i)
	{
		sum+=c[i];
		for(int j=0;j<=sum;++j)
			for(int k=0;k<=c[i] && k<=j;++k)
			{
			    if(dp[i-1][j-k]==-1)
					continue;
				if(dp[i-1][j-k]-k*cost[i]<0) 
					continue;
				dp[i][j]=max(dp[i][j],min(dp[i-1][j-k]-k*cost[i]+x,w+j*b));
			}
	}
	for(int i=0;i<=sum;++i)
        if(dp[n][i]!=-1) 
			ans=i;
    cout<<ans<<endl;
	return 0;
}
```


---

## 作者：Vsinger_洛天依 (赞：8)

# [Birds](https://www.luogu.com.cn/problem/CF922E)

逆天[冲刺 NOIP 题单](https://www.luogu.com.cn/training/484173)可做题之二。

首先看数据范围，肯定不能用魔法上限和魔法做 $\text{dp}$ 的决策。

考虑 $f_{i,j}$ 表示在走到第 $i$ 棵树，买了 $j$ 只鸟的时候的最大魔力数。

- 为什么不需要记录魔力上限？

    因为魔力上限为 $\text W+i\times \text{cost}_i$，可以直接计算，不需要记录。

然后很明显的我们存在一个转移方程。

$$f_{i,j}=\max\{f_{i-1,j-k}+\text X-\text{cost}_i\times k\}$$

因为存在魔力上限和魔力下限，因此 $f_{i,j}>0$ 且 $f_{i,j}<\text W+\text{cost}_i \times j$。

这里有一个边界，$f_{0,0}=\text W$，因为此时没有选择任何一只鸟而且没有走任何一棵树。

最后只要倒序枚举去判断是否存在即可，这样就能求出最大的鸟数。

## 代码

```cpp
namespace solve{
	inline int read(){
		int s=0,w=1;char ch=getchar();
		while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
		while(ch>='0'&&ch<='9'){s=s*10+ch-'0';ch=getchar();}
		return s*w;
	}
    inline void write(const int x){
        if(x>=10) write(x/10);
        putchar(x%10+'0');
    }
    inline void print(const int x,string s){
        if(x<0) putchar('-');
        write(x<0?-x:x);
        int len=s.size();
        for_(i,0,len-1) putchar(s[i]);        
    }
    int c[1005],C[1005],sum[1005],f[1005][10005];
	inline void In(){
        int n=read(),W=read(),B=read(),X=read();
        for_(i,1,n){
            c[i]=read();
        }
        for_(i,1,n){
            C[i]=read();
        }
        for_(i,1,n){
            sum[i]=sum[i-1]+c[i];
        }
        memset(f,-1,sizeof(f));
        f[0][0]=W;
        for_(i,1,n){
            for_(j,0,sum[i]){
                int len=min(j,c[i]);
                for_(k,0,len){
                    if(f[i-1][j-k]-C[i]*k>=0){
                        if(f[i-1][j-k]!=-1){
                            f[i][j]=max(f[i-1][j-k]+X-C[i]*k,f[i][j]);
                        }
                    }
                }
                if(f[i][j]>W+B*j) f[i][j]=W+B*j;
            }
        }
        _for(i,sum[n],1){
            if(f[n][i]!=-1){
                print(i,"\n");
                return;
            }
        }
        print(0,"\n");
	}
}
```

---

## 作者：冲啊小笼包 (赞：6)

这明显是一道DP题。

那么DP的话就先想办法找状态，这里有个关键条件，Ci的总和不超过1e4，这个条件很特别，因此考虑从这里下手。

稍微分析以后，可以发现，这似乎是个类背包问题。

每只小鸟都可以看成一个物品，且价值为1，体积为costi，而这道题特别的就是体积是会动态变化的。

考虑设立状态dp[i][j]表示前i棵树召唤j只小鸟后，且站在第i棵树下能保留的最大魔法值。

如果这么设计状态，我们可以发现，所有的量都是可以表示的。

- 召唤的小鸟的量
- 当前拥有的魔法值
- 当前的状态阶段
- 以及魔法上限，这个量不是直接可以看得，但是可以通过我们这个状态维护的上面3个值给求出来，很明显就是j*b + w

对于状态转移，明显可以转换成01背包问题，就是把每个小鸟当成一个物体，然后一个个转移，但是这样太不优雅了。简单思考其实就是一个多重背包问题，因此二进制拆分一下，这部分复杂度就降下来到log级别了（二进制拆分不详细展开了）

同时可以发现，其实第一维可以优化掉的，01背包那样，倒着枚举就可以了。

注意在每进入下一个阶段的时候要更新当前的魔法值。

总复杂度不劣于O（n*log(sumc)*sumc)

其中sumc为ci的总和。

注意可能爆int，要开ll

下面为代码：
```cpp
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string.h>
#include <limits.h>
#include <string>
#include <iostream>
#include <queue>
#include <math.h>
#include <map>
#include <bitset>
using namespace std;
typedef long long int ll;

const int MAXN = 1e3 + 10;
const int MAXC = 1e4 + 10;

struct item{
    ll num,v;
};

ll dp[MAXC];
int n;
ll w,b,x,sumc;
ll num[MAXN],v[MAXN];
vector<item> s;

void setItem(int i){
    s.clear(); ll now = num[i]; ll p = 1;
    while(now != 0){
        if(now >= p){
            item x; x.num = p; x.v = p * v[i]; s.push_back(x);
            now -= p; p <<= 1;
        }else{
            item x; x.num = now; x.v = now * v[i]; s.push_back(x);
            now = 0;
        }
    }
}

void ceshi(){
    for(int i = 0; i <= sumc; ++i){
        printf("%I64d ",dp[i]);
    }
    printf("\n");
}

int main(){
    scanf("%d%I64d%I64d%I64d",&n,&w,&b,&x); sumc = 0;
    for(int i = 1; i <= n; ++i){ scanf("%I64d",&num[i]); sumc += num[i];}
    for(int i = 1; i <= n; ++i){ scanf("%I64d",&v[i]);}
    memset(dp,-1,sizeof(dp));
    dp[0] = w;
    for(int i = 1; i <= n; ++i){
        setItem(i);
        for(int j = 0; j <= sumc; ++j){
            if(dp[j] == -1){ continue;}
            ll limit = j * b + w;
            dp[j] = min(dp[j] + x,limit);
        }
        for(int j = 0; j < s.size(); ++j){
            for(int k = sumc; k >= s[j].num; --k){
                if(dp[k - s[j].num] == -1){
                    continue;
                }
                ll mana = dp[k - s[j].num];
                if(mana >= s[j].v){
                    dp[k] = max(dp[k],mana - s[j].v);
                }
            }
        }
        //ceshi();
    }
    int maxn = 0;
    for(int i = sumc; i >= 0; --i){
        if(dp[i] >= 0){
            maxn = i; break;
        }
    }
    printf("%d\n",maxn);
    return 0;
}

```

---

## 作者：ChthollyTree (赞：4)

我怕不是数据结构学傻了qwq，就这题也能写过数据结构优化dp

dp题

$f[i][j]$表示到第$i$棵树，召唤了$j$只鸟所剩下的能量最大值

那么我们可以很容易得到方程 

$f[i][j] = max(f[i-1][k] -(j-k)*cost[i])+X(j-c[i]<=k<=j)$

这时候直接暴力的话会TLE

但是我们可以用st表优化

$f[i][j] = max(f[i-1][k] + k*cost[i]-j*cost[i])+X$

$ = max(f[i-1][k] + k*cost[i])-j*cost[i]+X$


所以我们用st表维护$f[i-1][k] + k*cost[i]$的区间最大值就行了qwq

转移的时候询问$[j-c[i],j]$的最大值即可

这样写可能常数有点大（我的代码最慢接近800ms）

```
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 1005
#define MAXC 10005
#define max(x,y) (x)>(y)?(x):(y)
const int INF = (int)0x3f3f3f3f*(int)0x3f3f3f3f;

int n,W,B,X,C;
int c[MAXN];
int f[MAXN][MAXC],g[MAXN][MAXC];
int s[MAXC][20];
int cost[MAXN];

inline void jianbiao(int ii)
{
	for(int i = 0; i <= C; i ++)
		s[i][0] = f[ii][i] + cost[ii+1]*i;
	for(int j = 1; j <= 17; j ++)
		for(int i = 0; i+(1<<j) <= C; i ++)
		{
			s[i][j] = max(s[i][j-1],s[i+(1<<(j-1))][j-1]);
		}
}

inline int rmq(int l,int r)
{
	if(l < 0) l = 0;
	int o = log2(r-l+1);
	return max(s[l][o],s[r-(1<<o)+1][o]);
 } 
 
void rd()
{
	cin >> n >> W >> B >> X;
	for(int i = 1; i <= n; i ++)
	{
		cin >> c[i];
		C += c[i];
	}
	for(int i = 1; i <= n; i ++)
		cin >> cost[i];
}

signed main()
{
	rd();
	f[0][0] = W;
	g[0][0] = W;
	for(int i = 1; i <= C; i ++) {
		f[0][i] = -INF;
		g[0][i] = -INF;
	}
	jianbiao(0);
	for(int i = 1; i <= n; i ++) {
		for(int j = 0; j <= C; j ++) {
			f[i][j] = rmq(j-c[i],j) - j*cost[i] + X;
			if(f[i][j] < X) f[i][j] = -INF; 
			if(f[i][j] > W+j*B) f[i][j] = W+j*B;
		}
		jianbiao(i);
	}
	int ans = 0;
	for(int i = 0; i <= C; i ++)
		if(f[n][i] >= 0) ans = i;
	cout<<ans;
	return 0;
 } 
```

---

## 作者：jianhe (赞：3)

类似于 [CF1974E](https://www.luogu.com.cn/problem/CF1974E) 的思路，魔法值很大，无法用数组存下，于是交换下标与值，将状态转换为：

设 $dp_{i,j}$ 表示目前考虑第 $i$ 棵树，总共选了 $j$ 只鸟的最大魔法值。

枚举当前树上选的鸟的个数 $k$，则转移方程为：

$dp_{i,j} = \max_{k=0}^{\min(j,c_i)}(dp_{i-1,j-k}+X-k \times cost_i)$，其中变量名与题目一致。

注意魔法值上限为 $W+B \times j$，同时 $dp_{0,0}$ 应设置为 $W$。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=1e3+10;
ll n,W,B,X,c[N],q[N],cost[N],dp[N][N*10];
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>W>>B>>X;memset(dp,-1,sizeof dp);dp[0][0]=W;
	for(int i=1;i<=n;i++) cin>>c[i],q[i]=q[i-1]+c[i];
	for(int i=1;i<=n;i++) cin>>cost[i];
	for(int i=1;i<=n;i++)
		for(ll j=0;j<=q[i];dp[i][j]=min(dp[i][j],W+B*j),j++)
			for(int k=0;k<=min(j,c[i]);k++)
				if(~dp[i-1][j-k]&&dp[i-1][j-k]-k*cost[i]>=0) dp[i][j]=max(dp[i][j],dp[i-1][j-k]+X-k*cost[i]);
	for(int i=q[n];i;i--)
		if(dp[n][i]!=-1){cout<<i;return 0;}
	cout<<0;
	return 0;
}
```

---

## 作者：yuheng_wang080904 (赞：2)

## 题意

从左往右有 $n$ 棵树，第 $i$ 棵树上有 $c_i$ 只鸟。你可以花费 $cost_i$ 能量召唤一只鸟，但是你必须站在第 $i$ 棵树下。

你的初始能量和能量上限都是 $W$，从第一棵树出发，只能往右走。每经过一棵树恢复 $X$ 的能量。每召唤一只鸟，你的能量上限增加 $B$。求出你最多能够召唤多少只鸟。 

## 思路

我们其实可以很容易想到一个暴力的 dp，$dp(i,j,k)$ 表示前 $i$ 棵树，当前能量为 $j$，当前上限为 $k$，最多召唤鸟个数。

但你可以发现 $k=W+dp(i,j,k)\times B$。因此可以省略一维。$dp(i,j)$ 表示前 $i$ 棵树，当前能量为 $j(j\le W+dp(i,j)\times B)$，最多召唤鸟个数。

可以得到转移方程 $dp(i,j)=\max(dp(i-1,j+k\times cost_i-x)+k)(0\le k\le c_i)$。这个算法时间复杂度是 $O(n^2W)$ 的，显然会 TLE。

我们注意到 $\sum_{i=1}^nc_i\le10^4$，因此我们可以改变一下 dp 思路。

我们用 $dp(i,j)$ 表示前 $i$ 棵树召唤了 $j$ 只鸟时最大当前能量，这个算法的时间复杂度为 $O(n\sum_{i=1}^nc_i)$，是我们能够接受的。

写出转移方程 $dp(i,j)=\max(f(i-1,j-k)+x-k\times cost_i)(0\le k\le c_i)$，考虑到能量上限与下限，于是所得结果要保证 $f(i-1,j-k)+x-k\times cost_i\ge 0$ 并与 $W+B\times j$ 取最小值。

## 代码

放上代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,w,b,x,c[1005],cost[1005],s[1005],dp[1005][10005];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>w>>b>>x;
    for(int i=1;i<=n;i++)cin>>c[i];
    for(int i=1;i<=n;i++)cin>>cost[i];
    for(int i=1;i<=n;i++)s[i]=s[i-1]+c[i];
    for(int i=0;i<=n;i++){
	for(int j=0;j<=s[n];j++)dp[i][j]=-1;
    }
    dp[0][0]=w;
    for(int i=1;i<=n;i++){
	for(int j=0;j<=s[i];j++){
	    for(int k=0;k<=c[i]&&k<=j;k++){
		if((dp[i-1][j-k]==-1)||(dp[i-1][j-k]-k*cost[i]<0))continue;
		dp[i][j]=min(max(dp[i][j],dp[i-1][j-k]+x-k*cost[i]),w+b*j);
	    }
	}
    }
    int ans=0;
    for(int i=1;i<=s[n];i++){
	if(dp[n][i]!=-1)ans=max(ans,i);
    }
    cout<<ans<<endl;
    return 0;
}

```

---

## 作者：shao0320 (赞：2)

注意到$B$和$W$都很大，因此直接记能量会爆炸，但是$\sum c_i$却很小，而这里有一个比较好的性质：当吃的鸟数定了的时候，最大能量上限也就定了。因此考虑记吃过的鸟数。

再考虑一个事情：对于一个状态，我们肯定是希望到这里的时侯剩余能量越多越好。

因此我们可以设计出一个$dp$状态：$f(i,j)$表示到第$i$棵树的时候，已经吃了$j$只鸟，剩余的最大能量。

但是直接枚举在第$i$棵树上吃的鸟数会$TLE$，注意到这是个多重背包，因此直接二进制拆分优化一下就可以了

总复杂度不会超过$O(N\sum c_i*log\sum c_i)$。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1005
#define int long long
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n,w,b,x,c[N],cost[N],f[N][10005],C,a[10005],tot;
int cmp(int x,int y)
{
	return x>y;
}
signed main()
{
	n=read();w=read();b=read();x=read();
	for(int i=1;i<=n;i++)c[i]=read(),C+=c[i];
	for(int i=1;i<=n;i++)cost[i]=read();
	memset(f,-0x3f,sizeof(f));
	f[0][0]=w;
	for(int i=1;i<=n;i++)
	{
		if(i!=1)for(int j=0;j<=C;j++)f[i][j]=min(f[i-1][j]+x,w+b*j);
		else for(int j=0;j<=C;j++)f[i][j]=f[i-1][j];
		tot=0;
		for(int k=1;k<=c[i];k*=2)
		{
			a[++tot]=k;
			c[i]-=k;
		}
		if(c[i])a[++tot]=c[i];
		sort(a+1,a+tot+1,cmp);
		for(int k=1;k<=tot;k++)
		{
			for(int j=C;j>=a[k];j--)
			{
				if(min(f[i][j-a[k]],w+b*(j-a[k]))>=cost[i]*a[k])f[i][j]=max(f[i][j],min(f[i][j-a[k]],w+b*(j-a[k]))-cost[i]*a[k]);
			}
		}
	}
	int ans=0;
	for(int i=C;i>=0;i--)
	{
		if(f[n][i]>=0)
		{
			ans=i;
			break;
		}
	}
	cout<<ans<<endl;
	return 0;;
}
```



---

## 作者：TempestMiku (赞：2)

# [题目](https://www.luogu.com.cn/problem/CF922E)

## 题意
一条直线上有 $n$ 棵树，第 $i$ 棵树上有 $c_i$ 只鸟。

在第 $i$ 棵树底下召唤一只鸟的魔法代价是 $cost_i$。每召唤一只鸟，魔法上限会增加 $B$。从一棵树走到另一棵树，会增加魔法 $X$。一开始的魔法和魔法上限都是 $W$。

问最多能够召唤的鸟的个数。


## 思路
发现能量值为 $1\times 10^9$，但是鸟的数量为 $1\times 10^3$，于是我们设计 $dp_{i,j}$ 表示到第 $i$ 个树，已经有 $j$ 个鸟的魔力值共有多少。

得出转移方程：


$$dp_{i,j}=\sum_{k=0}^{\min\{c_i,j\}}{\max\{dp_{i-1,j}-k\times cost_i+x,w+j\times b\}}(dp_{i-1,j}-k\times cost_i\ge 0)$$

直接转移即可

最终答案可以倒序枚举 $dp_{n,i}$，如果有一个数大于等于 $0$，那么这时候 $i$ 即为答案，直接输出即可。

注意到可能会爆内存空间，所以滚动一下 $dp$ 数组即可。

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
namespace Testify{
    inline int read(){
        int f(1),x(0);
        char ch=getchar();
        for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
        for(;isdigit(ch);ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
        return f*x;
    }
    inline void WritE(int x){
        if(x<0) putchar('-'),x=-x;
        if(x>9) WritE(x/10);
        putchar(x%10+48);
    }
    inline void write(int x){
        WritE(x);
        puts("");
    }
    inline void Write(int x){
        WritE(x);
        putchar(' ');
    }
}
using namespace Testify;
int n,w,b,x;
const int N=1005;
int c[N],cost[N],dp[2][100008],sum=0;
signed main(void){
    n=read(),w=read(),b=read(),x=read();
    for(register int i=1;i<=n;i++){
        c[i]=read();
    }
    for(register int i=1;i<=n;i++){
        cost[i]=read();
    }
    for(register int j=0;j<=100000;j++){
        dp[0][j]=dp[1][j]=-114514;
    }
    dp[0][0]=w;
    for(register int ii=1;ii<=n;ii++){
        int i=ii&1;
        sum+=c[ii];
        for(register int j=0;j<=sum;j++){
            for(register int k=0;k<=c[ii]&&k<=j;k++){
                if(dp[i^1][j-k]-k*cost[ii]<0){
                    continue;
                }
                dp[i][j]=max(dp[i][j],min(dp[i^1][j-k]-k*cost[ii]+x,w+j*b));
            }
        }
    }
    for(register int i=sum;i>=0;i--){
        if(dp[n&1][i]>=0){
            write(i);
            return 0;
        }
    }
    return 0;
}
```


---

## 作者：Arcaea (赞：2)

一眼背包，于是我们设计 $dp_{i,j}$ 表示到第 $i$ 个树，已经有 $j$ 个鸟的魔力值有多少。

$$dp_{i,j}=\sum_{k=0}^{\min\{c_i,j\}}{\max\{dp_{i-1,j}-k\times cost_i+x,w+j\times b\}}$$

直接转移即可，注意判断之前背包为负数无法转移到现在的情况。

---

## 作者：Clover_Lin (赞：1)

## 思路
发现直接算答案很麻烦，我们可以记录最大魔力，然后找到满足最大魔力非负的最大的鸟数。

令 $f_{i,j}$ 表示前 $i$ 棵树上，总共召唤 $j$ 只鸟的最大魔力。易得 $f_{i,j}=\max_{k=0}^{c_i}\min(mxx,\min(mx,f_{i-1,j-k}+X\cdot[i\neq1])-cost_i\cdot k)$。有点绕，解释一下，$mx$ 表示上一棵树走完后的魔力上限，$mxx$ 表示这一棵树走完后的魔力上限。计算也很简单：$mx=W+B\cdot (j-k),mxx=W+B\cdot j$。

这道题最好不要压成一维，否则很可能会输出 $\sum_{i=1}^N c_i$。
## 代码
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int n, w, b, x;
int c[1010];
long long cost[1010];
long long f[1010][10010];

int main()
{
    cin >> n >> w >> b >> x;
    for (int i = 1; i <= n; i++)
        cin >> c[i];
    for (int i = 1; i <= n; i++)
        cin >> cost[i];
    int s = 0;
    memset(f, -0x3f, sizeof(f));
    f[0][0] = w;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= c[i]; j++)
            for (int k = j; k <= s + j; k++)
            {
                if (f[i - 1][k - j] < 0) continue;
                long long mx = w + 1LL * b * (k - j);
                long long mxx = w + 1LL * b * k;
                int X = 0; if (i != 1) X = x;
                long long val = min(mx, f[i - 1][k - j] + X);
                val -= cost[i] * j;
                f[i][k] = max(f[i][k], min(mxx, val));
            }
        s += c[i];
    }
    for (int i = s; i >= 0; i--)
        if (f[n][i] >= 0)
        {
            cout << i << endl;
            return 0;
        }
	return 0;
}
```

---

## 作者：STA_Morlin (赞：1)

[题目 in CF](https://codeforces.com/problemset/problem/922/E) 

## 题目大意

> 一条直线上有 $n$ 棵树，第 $i$ 棵树上有 $c_i$ 只鸟。
> 
> 在第 $i$ 棵树下召唤一只鸟的魔力代价是 $cost_i$。每召唤一只鸟，魔力上限会增加 $B$。每向前走一棵树，会增加 $X$ 的魔力。一开始的魔力和魔力上限都是 $W$。你只能向前移动。
>
> 问最多能够召唤几只鸟。

## 思路简析

还是先考虑状态：必然不能以魔力为状态，那么只能以树和鸟，而答案却又是树和鸟所以我们需要反向思考一下：$f_{i, j}$ 代表在第 $i$ 棵树时总共已召唤了 $j$ 只鸟时能有的最大魔力值，
最终结果是 $\max\limits_{f_{n, j}\ is\ existent}\{j\}$。

转移方程：

$$f_{i, j} = \max\limits_{0 \leq k \leq \min\{j, c_i\}}\{f_{i-1, j-k}+X-cost_i\times k\}$$

（$Range: i_{1\rightarrow n}, j_{0\rightarrow\sum\limits_{p=0}^i c_p}$ ） 

这里的 $k$ 表示在第 $i$ 棵树下召唤了 $k$ 只鸟；加上的 $X$ 是从第 $i$ 棵树走到第 $i+1$ 棵树的魔力值，所以严格来说其实当 $i=n$ 时不应加上 $X$，但是有判断条件即可；转入该方程应有条件：$f_{i-1, j-k}-cost_i\times k$（这里就是不加 $X$）。

边界条件是 $f_{0, 0} = W$。

那么就比较简单了。

~~这真的是背包 dp 吗？~~

另外考虑你的魔力上限，显然是 $W+B\times j$。

我是真服了，$cst_i \times k$ 会爆 `int`，硬控我 4h+，切记开 `ll`。

这东西虽然是三层循环，但是似乎时间复杂度仅是 $\Omega(n\cdot\sum\limits_{i=1}^nc_i)$ 即 $10^7$ 的（这里似乎还应该加个带 $\log$ 的？若算错请指正谢谢。）。

```cpp
ll n, W, B, X;
ll c[man], cst[man], sum[man];
ll f[man][mac];
int main () {
    // files("test");
    scanf("%lld%lld%lld%lld", &n, &W, &B, &X);
    for (int i = 1; i <= n; ++ i) scanf("%lld", c+i), sum[i] = sum[i-1]+c[i];
    for (int i = 1; i <= n; ++ i) scanf("%lld", cst+i);
    memset(f, -1, sizeof(f)), f[0][0] = W;

    for (int i = 1; i <= n; ++ i) 
        for (int j = 0; j <= sum[i]; ++ j) {
            for (int k = 0; k <= min(1LL*j, c[i]); ++ k) 
                if (f[i-1][j-k]-cst[i]*k>=0) 
                    f[i][j] = max(f[i][j], f[i-1][j-k]+X-cst[i]*k);
            f[i][j] = min(f[i][j], W+B*j); }

    for (int i = sum[n]; i; -- i) 
        if (f[n][i] != -1) return printf("%d", i)&0;
        
    return puts("0")&0;
}
```

点名批评可爱洛天依，写 $\max$ 不写范围，中间变量还来回标错。

---

## 作者：大菜鸡fks (赞：1)

设f[i][j]表示前i个树，还有j能量，所能打的最多鸟数。 裸的多重背包

然而发现j范围太大，考虑优化，最常见的套路就是把状态和目标值换一下位置

记录状态的最优。于是f[i][j]表示前i个树，打了j只鸟，最多剩余的能量

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const int M=1e4+5,N=1e3+5;
ll n,W,B,X;
int A[N],sum,c[N];
inline void init(){
	scanf("%I64d%I64d%I64d%I64d",&n,&W,&B,&X);
	for (int i=1;i<=n;i++){
		scanf("%d",&A[i]);
		sum+=A[i];
	}
	for (int i=1;i<=n;i++){
		scanf("%d",&c[i]);
	}
}
ll dp[N][M];
int ans;
inline void solve(){
	memset(dp,-1,sizeof dp); dp[0][0]=W;
	for (int i=1;i<=n;i++){
		for (int j=0;j<=sum;j++){
			for (int k=0;k<=min(j,A[i]);k++){
				if (dp[i-1][j-k]==-1) continue;
				ll tmp=min(W+(j-k)*B,dp[i-1][j-k]+X)-(ll)c[i]*k;
				if (tmp<0) continue;
				dp[i][j]=max(dp[i][j],min(W+j*B,tmp));
				ans=max(ans,j);
			}
		}
	}
	printf("%d\n",ans);
}
signed main(){
	init();
	solve();
	return 0;
}
```



---

## 作者：Svemit (赞：0)

# Sol:

记 $m = \sum_{i = 1} ^ {n} c_i$。

设 $f_{i, j}$ 为到第 $i$ 棵树，有了 $j$ 只鸟，剩余钱数的最大值，如果不存在则为 -1。

考虑转移：

先枚举 $i, j$ 这两维，再枚举第 $i$ 棵树得到了 $k$ 只鸟。

首先当前的钱数 $tot$ 是 $\min (f_{i - 1, j - k} + X, W + B \times (j - k))$。

如果 $tot$ 足够买 $k$ 只鸟，则 $f_{i, j} = \min (f_{i - 1, j}, tot - cost_i \times k)$。

最后找到最大的 $i$ 使得 $f_{n, i}$ 不等于 -1 就好。

写出来代码的复杂度看上去是 $O(n m ^ 2)$ 的，实际上最后一层循环加起来一共只有 $m$，所以复杂度 $O((n + m) \times m)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e3 + 5, M = 1e4 + 5;
 
int n, m;
ll W, B, X;
int a[N], b[N];
ll f[M], g[M];
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    cin >> n >> W >> B >> X;
    for (int i = 1; i <= n; i ++) {
    	cin >> a[i];
    	m += a[i];
	}
	for (int i = 1; i <= n; i ++) {
		cin >> b[i];
	}
	
	memset(f, -1, sizeof f);	
	f[0] = W;
	for (int i = 1; i <= a[1]; i ++) {
		if (1ll * b[1] * i <= W) {
			f[i] = W - 1ll * b[1] * i;
		} 
	}
	
	for (int i = 2; i <= n; i ++) {
		swap(f, g);
		memset(f, -1, sizeof f);
		for (int j = 0; j <= m; j ++) {
			for (int k = 0; k <= a[i] && k <= j; k ++) {
				if (g[j - k] == -1) {
					continue;
				}
				ll tot = min(g[j - k] + X, W + 1ll * (j - k) * B);
				if (tot >= 1ll * b[i] * k) {
					f[j] = max(f[j], tot - 1ll * k * b[i]);
				}
			}
		}
	}
	
	int ans = 0;
	for (int i = m; i >= 0; i --) {
		if (f[i] != -1) {
			ans = i;
			break;
		}
	}
	
	cout << ans << "\n";
 
    return 0;
}
```

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF922E)

# 前置知识

[背包 DP](https://oi-wiki.org/dp/knapsack/)

# 解法

观察到 $w$ 极大，若使用正常的背包空间会爆炸。

依据 [AT_dp_e Knapsack 2](https://www.luogu.com.cn/problem/AT_dp_e) 的经验，考虑将背包“反”着用。设 $f_{i,j}$ 表示到第 $i$ 棵树时一共召唤了 $j$ 只小鸟时剩余的最大魔力值，状态转移方程为 $f_{i,j}=\min(\max\limits_{k=0}^{\min(j,c_{i})} \{ f_{i-1,j-k}-cost_{i} \times k+x \},w+b \times j)$，边界为 $f_{0,0}=w$。

最终，有 $\max\limits_{i=0}^{\sum_{j=1}^{n}c_{j}} \{ [f_{n,i} \ge 0] \times i \}$ 即为所求。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
ll c[10010],sum[10010],cost[10010],f[1010][10010];
int main()
{
    ll n,w,b,x,ans=0,i,j,k;
    cin>>n>>w>>b>>x;
    for(i=1;i<=n;i++)
    {
        cin>>c[i];
        sum[i]=sum[i-1]+c[i];
    }
    for(i=1;i<=n;i++)
    {
        cin>>cost[i];
    }
    memset(f,-0x3f,sizeof(f));
    f[0][0]=w;
    for(i=1;i<=n;i++)
    {
        for(j=0;j<=sum[i];j++)
        {
            for(k=0;k<=min(j,c[i]);k++)
            {
                if(f[i-1][j-k]-cost[i]*k>=0)
                {
                    f[i][j]=max(f[i][j],f[i-1][j-k]-cost[i]*k+x);
                }
            }
            f[i][j]=min(f[i][j],w+b*j);
        }
    }
    for(i=sum[n];i>=0;i--)
    {
        if(f[n][i]>=0)
        {
            ans=i;
            break;
        }
    }
    cout<<ans<<endl;
    return 0;
} 		   		     	
```

---

