# [USACO06DEC] The Fewest Coins G

## 题目描述

Farmer John has gone to town to buy some farm supplies. Being a very efficient man, he always pays for his goods in such a way that the smallest number of coins changes hands, i.e., the number of coins he uses to pay plus the number of coins he receives in change is minimized. Help him to determine what this minimum number is.

FJ wants to buy T (1 ≤ T ≤ 10,000) cents of supplies. The currency system has N (1 ≤ N ≤ 100) different coins, with values V1, V2, ..., VN (1 ≤ Vi ≤ 120). Farmer John is carrying C1 coins of value V1, C2 coins of value V2, ...., and CN coins of value VN (0 ≤ Ci ≤ 10,000). The shopkeeper has an unlimited supply of all the coins, and always makes change in the most efficient manner (although Farmer John must be sure to pay in a way that makes it possible to make the correct change).

农夫 John 想到镇上买些补给。为了高效地完成任务，他想使硬币的转手次数最少。即使他交付的硬 币数与找零得到的的硬币数最少。 


John 想要买价值为 $T$ 的东西。有 $N$（$1 \le N \le 100$）种货币参与流通，面值分别为 $V_1,V_2,\dots,V_N$（$1 \le V_i \le 120$）。John 有 $C_i$ 个面值为 $V_i$ 的硬币（$0 \le C_i \le 10 ^ 4$）。

我们假设店主有无限多的硬币， 并总按最优方案找零。**注意**无解输出 `-1`。


## 说明/提示

Farmer John pays 75 cents using a 50 cents and a 25 cents coin, and receives a 5 cents coin in change, for a total of 3 coins used in the transaction.


## 样例 #1

### 输入

```
3 70
5 25 50
5 2 1```

### 输出

```
3```

# 题解

## 作者：hkr04 (赞：41)

题意中的金额我们不妨抽象为线段长度  
所以题意可以简化成：怎样拼凑成两段线段，且它们的长度之差等于T（图中数字为硬币编号）  
![](https://i.loli.net/2018/10/19/5bc95326d4c5b.png)  

你要怎么去拼凑线段，这就有些背包的感觉。所以我们可以分别从John和店主不同的角度来考虑最优解  

因为John的硬币数是有限的，所以可以视为多重背包，求达到一定钱数所需的最少的硬币数量;店长的硬币数是无限的，所以可以视为完全背包，也是求同种方案最少的硬币数量，再在最后枚举每种付钱和找钱的方案硬币数之和，求个min即可得出答案    

但是问题是，我们应该一直找到多少钱的方案才能保证找到合法的最优解呢？我认为这是这道题最关键的部分，以下为证明（然而其他的题解都没有说清楚）     

其余几位大佬的题解中说到，最大应一直找到$t+V_{max}^2$。这是先从店主的角度考虑的  

设货币面值为$V_{1}\le V_{2}\le \dots V_{n}$，$(V_{max}=V_{n})$那么当老板需要找$V_{max}^2$的钱时，至少需要$V_{max}$枚硬币。设一个前缀和数组为$S_{0}\ S_{1}\ S_{2}\dots S_{n}\ (S_{0}=0)$，其中共有$V_{max}+1$个元素。根据抽屉原理，至少有两个前缀和与$V_{max}$同余，则它们的差$=x\times V_{max}(x\text{为正整数且}x\ge 1)$。显然当$V_{max}$的数量足够时，将这一部分替换成$x$个面值为$V_{max}$是最优的（不要纠结真正采用的方案）。对于$V_{n-1}$，同理。  
所以在$V_{max}^2$的范围内一定可以找出最优方案，对于更大的$t+V_{max}^2$也一定可以   

顺手贴一下代码，同时感谢题解区的大佬们 
```cpp
#include <cstdio>
#include <cstring>
const int maxT=10000+10;
const int maxn=100+5;
const int maxv=120;
int f[maxT+maxv*maxv],g[maxT+maxv*maxv];//f[i]、g[i]分别表示John和店长付i元钱最少需要用的硬币 
int v[maxn],c[maxn];//如题意所示 
inline int max(int x,int y) {return x>y?x:y;}
inline int min(int x,int y) {return x<y?x:y;}
int main()
{
    int n,t;
    scanf("%d%d",&n,&t);
    for (int i=1;i<=n;i++)
        scanf("%d",&v[i]);
    int sum=0,mx=0;
    for (int i=1;i<=n;i++)
    {
        scanf("%d",&c[i]);
        sum+=c[i]*v[i];
        mx=max(mx, v[i]*v[i]);
    }
    if (sum<t)//买不起，退了 
    {
        printf("-1\n");
        return 0;
    }
    memset(g, 0x3f, sizeof(g));
    memset(f, 0x3f, sizeof(f));
    g[0]=0;
    f[0]=0;
    for (int i=1;i<=n;i++)
        for (int j=v[i];j<=mx;j++)//Rob找j元钱所用的最小钱数 
            g[j]=min(g[j], g[j-v[i]]+1);
    //实际上应该是g[i][j]=min(g[i-1][j], g[i][j-v[i]+1])
    //g[i][j]表示考虑到第i个物品支付j元的最少硬币数 
    //但是因为第一维存储的信息用不到
    //且更新前g[i][j]记录的就是g[i-1][j]的信息 
    //所以可以只用一维 
    for (int i=1;i<=n;i++)
    { 
        for (int j=1;j<=c[i];j<<=1)
        {
            for (int k=t+mx;k>=j*v[i];k--)//倒过来更新（实际上是拆分成01背包的形式） 
                f[k]=min(f[k], f[k-j*v[i]]+j);
            c[i]-=j;//相当于用拆分的物品进行了一次更新，要从数量中减去 
        }
        if (c[i])//还有剩余的没更新 
            for (int k=t+mx;k>=c[i]*v[i];k--)
                f[k]=min(f[k], f[k-c[i]*v[i]]+c[i]);
    }
    int ans=0x3f3f3f3f;
    for (int i=t;i<=t+mx;i++)
        ans=min(ans, f[i]+g[i-t]);
    printf("%d\n",ans==0x3f3f3f3f?-1:ans);
    return 0;
}
```

---

## 作者：RedreamMer (赞：18)

### [P2851](https://www.luogu.com.cn/problem/P2851)

是一道比较特别的的 $DP$ 题。

Update: 2020-5-4 公式部分炸了，修改一下

### $\texttt{Meaning}$

给你 $n$ 种硬币类型，每种硬币类型 $v_i$ 买家有 $c_i$ 个，卖家有无限个，买家要买一个 $m$ 元的东西（卖家可以找零），买家问你双方之间**交流的硬币个数**（指买家用的硬币数 + 卖家找零的硬币数）最少为多少个？

### $\texttt{Solution}$


首先，我们设买家总共支付 $x$ 元，那么卖家就是找零 $x-m$ 元，其实要凑齐 $x$ 元，就是对于买家做一个多重背包 $dp1$ （注意要二进制拆分优化），对于卖家，再做一个完全背包 $dp2$ ，然后枚举 $x$ ，求出

$$\min_{i=m}^{i \leq m+mx} dp1_i+dp2_{i-m}$$

关于这里的 $mx$ ，我们令它为 $\max_{i=1}^{n} v_i^2$ ，为什么呢？（重点部分，有些题解都没有讲的很清楚，这里着重分析）

关于二进制拆分，已经有一位金标爷发了题解，这里不做多阐述。

### $\texttt{Prove}$

假设，在 $m+mx$ 的范围内，没有买家付的钱-卖家找的钱等于 $m$ 的情况，那么卖家所找的硬币的**个数**必定大于 $v_{max}$ （因为 $v_{max}^2$ 显然小于 $mx$ ）。

设卖家找的钱的序列为 $p(\forall p_i<p_{i+1})$ 我们作一个前缀数组$s$ ，使 $s_i=\sum_{j=1}^{j\leq i} p_j$ ，根据同余的性质，必有两个（或两个以上）的 $s_i$ 是在 $mod$ $v_{max}$ 意义下是同余的，（因为 $s$ 序列长度大于 $v_{max}$，而取模后的数最多有 $v_{max}$ 种），那么必然 有$s_i-s_j=k*v_{max} (i>j)$ 即这部分的数可以替换成 $k$ 个 $v_{max}$ 。

那么，既然卖家不用还超过 $v_{max}^2$ 的钱，那么买家就不用付超过$m+v_{max}^2$ 的钱，证必。

### $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=10000010;
const int M=10000010;

int a,b,v[N],w[N],f1[N],f2[N],ans=0x3fffffff,mx,sum;//注意ans不要赋值为0x7fffffff，太大了可能会导致出现“伪答案”

signed main() {
	scanf("%d%d",&a,&b);
	for(int i=1;i<=a;i++) {
		scanf("%d",&v[i]);
		mx=max(mx,v[i]*v[i]);
	}
	for(int i=1;i<=a;i++) {
		scanf("%d",&w[i]);
		sum=sum+w[i]*v[i];
	}
	if(sum<b) {//特判，如果买家全用上钱都达不到m，直接输出-1
		printf("-1");
		return 0;
	}
	memset(f1,0x3f,sizeof f1);
	memset(f2,0x3f,sizeof f2);
	f1[0]=f2[0]=0;
	for(int i=1;i<=a;i++)//做卖家的完全背包
		for(int j=v[i];j<=mx;j++) f1[j]=min(f1[j],f1[j-v[i]]+1);
	for(int i=1;i<=a;i++){//做买家的多重背包
		for(int j=1;j<=w[i];j<<=1) {//二进制拆分
			for(int k=b+mx;k>=j*v[i];k--) f2[k]=min(f2[k],f2[k-j*v[i]]+j);
			w[i]-=j;
		}
		if(w[i]) for(int j=b+mx;j>=w[i]*v[i];j--) f2[j]=min(f2[j],f2[j-w[i]*v[i]]+w[i]);
	}
	for(int i=b;i<=b+mx;i++) ans=min(ans,f2[i]+f1[i-b]);
	if(ans==0x3fffffff) printf("-1");//注意特判
	else printf("%d",ans);
	return 0;
}
```

如果还有不明白的可以私聊我。

### [$\color{blue}\texttt{My Blog}$](https://www.luogu.com.cn/blog/184549/)

---

## 作者：installb (赞：12)

[题](https://www.luogu.com.cn/problem/P2851)  

官方题解中提到找零数的上界是 $v_{max}^2$，但是并没有给出证明，我目前也不会证。  
这里给出了找零数 $\leq 2\times v_{max}^2$ 的证明。


------------


首先一个显然的思路，枚举找零的量 $x$，那么付钱的量就是 $x+T$，找零是完全背包（硬币数无限），付钱是多重背包（硬币数有限），注意多重背包要二进制分组优化或者单调队列优化，这里不详细展开了。  

看到这里有一个问题，这个 $x$ 最大要枚举到多少？  
直观感受下，这个 $x$ 并不会特别大。  
实际上，如果面值最大的币面值为 $v_{max}$，$x\leq 2\times v_{max}^2$，下面给出证明。

- 首先，**找零中**面值非最大的币**总共最多**用 $v_{max}$ 个。   

反证，如果 $>v_{max}$，那么一定能找出一些硬币，它们的**面值之和 $v_{max}$ 的倍数**，可以替换成若干个面值最大的币，使得硬币总数减少。把这些硬币排成一排，面值形成一个序列 $a_i$，对这个序列做前缀和 $pre_i$，区间和等于前缀和作差，在**大于** $v_{max}$ 个前缀和中，根据抽屉原理，**必然存在两个 $pre_i$ 除以 $v_{max}$ 余数相同**，假设它们为 $pre_i$ 和 $pre_j(0\leq i<j)$，那么 $[i+1,j]$ 这段区间和是 $v_{max}$ 的倍数。  

接下来分类讨论。  

这里先说明一下，下面的过程都是按在付钱部分和找零部分中不断同时删去一些面值之和相等的硬币，直到按该方法无法再删去任何硬币为止分析的。

- 找零中有面值最大的币  

显然，此时付钱中不能有面值最大的币了，否则可以两边各删一个硬币，直到付钱中没有或者找零中没有为止。  

所以付钱中所有的钱都不是面值最大的币，那么如果付钱中硬币的数量小于 $v_{max}$，付钱就小于 $v_{max}^2$ 找零自然就小于 $v_{max}^2$ 了。如果付钱的硬币多于 $v_{max}$ 个，那么可以从中选出 $v_{max}+1$ 个硬币，根据上文的分析，在选出的硬币中一定存在一些硬币，它们的面值之和是 $v_{max}$ 的倍数，**我们并不知道具体是几倍，但是这个倍数一定 $\leq v_{max}$**（因为 $v_{max}+1$ 个面值小于 $v_{max}$ 的硬币面值之和不可能大于等于 $(v_{max}+1)\times v_{max}$）。这里可以得出找零中**最多只有 $v_{max}-1$ 个面值最大的币，否则可以替换。**  

找零中面值最大的币少于 $v_{max}$ 个，面值非最大的币最多有 $v_{max}$ 个，所以找零总量小于 $2\times v_{max}^2$

- 找零中没有面值最大的币  

很明显，找零小于 $v_{max}^2$

所以，在 $x\geq2\times v_{max}^2$ 的时候，一定可以通过一些方式把交流的硬币总数减少，直到 $x<2\times v_{max}^2$ 为止。  



------------


代码：  
```cpp
using namespace std;
typedef long long LL;
const LL INF = 0x3f3f3f3f3f3f3f3f;
const LL V = 28800; // 2 * v_{max}^2

LL n,t;
LL v[105],c[105];
LL dp1[V << 1],dp2[V << 1]; // 这里我直接 2V 了，其实 V+t 就够
LL ans = INF;

int main(){
	memset(dp1,INF,sizeof(dp1));
	memset(dp2,INF,sizeof(dp2));
	cin >> n >> t;
	for(LL i = 1;i <= n;i ++) cin >> v[i];
	for(LL i = 1;i <= n;i ++) cin >> c[i];
	dp1[0] = dp2[0] = 0;
	
	for(LL i = 1;i <= n;i ++)
		for(LL j = v[i];j <= V;j ++) dp2[j] = min(dp2[j],dp2[j - v[i]] + 1);
	for(LL i = 1;i <= n;i ++){
		for(LL w = 1;w <= c[i];w <<= 1){
			for(LL j = V + t;j >= v[i] * w;j --) dp1[j] = min(dp1[j],dp1[j - v[i] * w] + w);
			c[i] -= w;
		}
		if(c[i]) for(LL j = V + t;j >= v[i] * c[i];j --) dp1[j] = min(dp1[j],dp1[j - v[i] * c[i]] + c[i]);
	}
	for(LL i = t;i <= t + V;i ++) ans = min(ans,dp1[i] + dp2[i - t]);
	if(ans >= INF) ans = -1;
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：TaK_Vin (赞：6)

多重背包+完全背包。约翰能对各种硬币使用的次数是有限的，于是对约翰做多重背包。而老板对各种硬币的使用次数是无限的，于是对老板做完全背包。然后在min出最小的答案。

```cpp
#include<stdio.h>  
#include<string.h>   
#include<algorithm> 
#include<iostream> 
#define maxn 101000  
#define INF 1000000000  
using namespace std;  
int c[110],v[110];  
int f[maxn],g[maxn];    
int main()  
{
    int n,t,i,j,k,ans;  
    scanf("%d%d",&n,&t);  
    for (i=1;i<=n;i++)  
        scanf("%d",&v[i]);  
    int sum=0,mx=0;  
    for (i=1;i<=n;i++)  
        {  
            scanf("%d",&c[i]);  
            sum+=c[i]*v[i];  //求John带的钱的总值 
            mx=max(mx,v[i]*v[i]);  //根据某某原理，必然有若干个货币组合起来是v_max的倍数，且不大于v_max^2 
        }//t+mx即为找钱的上限  
        if (sum<t) 
            {
                printf("-1\n");
                return 0;
            }  //John带的钱还买不起要买的东西，自然没有解决方案，故直接输出-1并结束程序 
    memset(g,63,sizeof(g));  
    memset(f,63,sizeof(f)); 
    g[0]=0;f[0]=0;  
    for (i=1;i<=n;i++)  
        for (j=v[i];j<=t+mx;j++)  
            g[j]=min(g[j],g[j-v[i]]+1); //老板找j元时要花的最少纸币数量 
    for (i=1;i<=n;i++)  
        {  
            for (j=1;j<=c[i];j*=2)
                {  
                    for (k=t+mx;k>=j*v[i];k--)  
                        f[k]=min(f[k],f[k-j*v[i]]+j);  //John花k元时要用的最少纸币数量。 
                    c[i]-=j; 
                }  
            if (c[i])  
                for (k=t+mx;k>=c[i]*v[i];k--)  
                    f[k]=min(f[k],f[k-c[i]*v[i]]+c[i]);  //同上 
        }
    ans=INF;  
    for (i=t;i<=t+mx;i++)  
        ans=min(f[i]+g[i-t],ans);  
    if (ans==INF) 
        printf("-1\n");  
    else
        printf("%d\n",ans);  
    return 0;  
}
```

---

## 作者：学而思李老师 (赞：5)

其它题解里面没有详细说明为什么这个题是多重背包+完全背包，这里解释一下。

首先我们来看一下背包都有哪些类型：

1. 01背包：每个物品可以选也可以不选，如果选只能选1个，一般用dp实现；

2. 部分背包：每个物品可以选也可以不选，如果选可以全选或者只选择其中的一部分，用贪心就能实现；

3. 完全背包：每个物品可以选0个，1个，2个，……，无穷多个；

4. 多重背包：每个物品可以选0个，1个，2个，……，$n$ 个（$n$ 一般会在题目中给出），常常用二进制优化拆分为01背包实现。

回到这道题，我们发现，FJ给钱的时候，他可以使用每一种面额的硬币，而且第 $i$ 种硬币可以选择 $1,2,3,\cdots,c_i$ 个，所以dp FJ给钱的过程用的是多重背包的算法。注意在二进制拆分的时候，不仅钱数要乘以计数器，花费的硬币也要乘以计数器，本人就因为这个问题没有一次AC。如果对二进制拆分不太熟悉，可以看一下宝物筛选那题。

当店主找钱的时候，同样也可以使用所有面额的硬币，但是题目中说店主有无穷多硬币，这不就是完全背包吗？我们枚举店主找的钱，两次dp即可。

代码实现：

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int dp1[50005], dp2[50005];
int n, t, maxx, cnt;
int v[1005], c[1005];
int vt[50005], wt[50005];
int ans = 1e9;

int main()
{
	scanf("%d%d", &n, &t);
	for(int i = 1; i <= n; i ++)
		scanf("%d", v + i);
	//二进制拆分 
	int sum = 0;
	for(int i = 1; i <= n; i ++)
	{
		scanf("%d", c + i);
		sum += v[i] * c[i];
		maxx = max(maxx, v[i] * v[i]);
		for(int j = 1; j <= c[i]; j *= 2)
		{
			vt[++cnt] = v[i] * j;
			wt[cnt] = j;
			c[i] -= j;
		}
		if(c[i] > 0)
		{
			vt[++cnt] = v[i] * c[i];
			wt[cnt] = c[i];
		}
	}
	if(sum < t)
	{
		printf("-1");
		return 0;
	}

	memset(dp1, 0x3f, sizeof dp1);
	memset(dp2, 0x3f, sizeof dp2);
	dp1[0] = dp2[0] = 0;
	//FJ给钱 
	for(int i = 1; i <= cnt; i ++)
	{
		for(int j = t + maxx; j >= vt[i]; j --)
			dp1[j] = min(dp1[j], dp1[j - vt[i]] + wt[i]);
	}
	//店主找钱 
	for(int i = 1; i <= n; i ++)
	{
		for(int j = v[i]; j <= maxx; j ++)
			dp2[j] = min(dp2[j], dp2[j - v[i]] + 1);
	}

	for(int i = t; i <= t + maxx; i ++)
		ans = min(ans, dp1[i] + dp2[i - t]);
	if(ans == 1e9)
		printf("-1");
	else
		printf("%d", ans);
	return 0;
}
```


---

## 作者：cleverman (赞：5)

把题目看成John部分的多重背包+Rob部分的完全背包。

最后的答案来自于min(f[i]+r[i]) (i>N)

基础思路是动规，i为要付的钱时f[i]以及r[i]分别对应John和Rob需要交换的纸币数量。

还有就是多重背包的二进制优化，对f[i]部分dp的二进制优化是必须的，否则会TLE


    
              
      
                
    
    

```cpp
#include<iostream>
#include<algorithm>
#define MAX 999999
using namespace std;
int N,T,v[MAX],c[MAX],f[MAX],r[MAX],vk[MAX],k1[MAX],ans=MAX,V,K;
int log2(int a);
int main()
{    
    int i,j;    
    cin>>N>>T;        
    for (i=0;i<N;i++)    
    {        
        cin>>v[i];        
        if (T+v[i]*v[i]>V)           
        V=T+v[i]*v[i];    
    }        
    memset(f,MAX,(V+1)*sizeof(int));    
    memset(r,MAX,(V+1)*sizeof(int));     
    for (i=0;i<N;i++)        
        cin>>c[i];  
    r[T]=f[0]=0;    
    //binary
    for (i=0;i<N;i++)
    {
        int t=1,temp=c[i];
        while (t<temp)
        {
            vk[K]=v[i]*t;
            k1[K++]=t;
            temp-=t;
            t*=2;
        }
        vk[K]=v[i]*temp;
        k1[K++]=temp;
    } 
    for (i=0;i<K;i++)        
        for (j=V-vk[i];j>=0;j--)                           
                f[j+vk[i]]=min(f[j+vk[i]],f[j]+k1[i]);  
    /*for (i=0;i<N;i++)        
        for (j=V;j>=0;j--)            
            for (k=1;k<=min(c[i],(V-j)/v[i]);k++)                
                f[j+k*v[i]]=min(f[j+k*v[i]],f[j]+k); */       
    for (i=0;i<N;i++)        
        for (j=T;j<=V;j++)            
            r[j+v[i]]=min(r[j+v[i]],r[j]+1);        
    for (i=T;i<=V;i++)        
        ans=min(ans,f[i]+r[i]);    
    if (ans!=MAX)       
        cout<<ans<<endl;    
    else        
        cout<<-1<<endl;   
    return 0;
}
int log2(int a)
{
    int i=1,ans=0;
    while (i<=a)
    {
        i*=2;
        ans++;
    }
    return ans-1;
}
```

---

## 作者：NaVi_Awson (赞：4)

具体思路楼下都有了

这里主要讲二进制分解：

把件数C

分解成若干个件数的集合，这里面数字可以组合成任意小于等于C

的件数，而且不会重复，之所以叫二进制分解，是因为这样分解可

以用数字的二进制形式来解释

比如：7的二进制 7 = 111 它可以分解成 001 010 100 这三个数可以

组合成任意小于等于7 的数，而且每种组合都会得到不同的数

15 = 1111 可分解成 0001  0010  0100  1000 四个数字

如果13 = 1101 则分解为 0001 0010 0100 0110 前三个数字可以组合成

7以内任意一个数，加上 0110 = 6 可以组合成任意一个大于6 小于13

的数，虽然有重复但总是能把 13 以内所有的数都考虑到了，基于这种

思想去把多件物品转换为，多种一件物品，就可用01 背包求解了。

文献来源：http://blog.csdn.net/zcube/article/details/48223063


---

## 作者：llzzxx712 (赞：3)

# P2851

## 题意简述

本题给定每个硬币的价值和数量，求凑出某价钱的最少硬币数是多少。我们可以将价值看作重量，数量看作价值。那么题目就可以变成：

- 给定一个可以装重量为 T 的物品的背包
- 有 n 个物品，每个物品有 $c_i$ 个，每个物品价值为 1 ，质量为 $v_i$ 或 $-v_i$ 。

## 题目分析

经过初步分析，这道题就转化为了一个有负重量求最小价值的多重背包问题。那么我们就可以将递推式进行修改：

$f_j=min(f_j,f_{j-v_i}+c_i,f_{j+v_i}+c_i)$ 

$f_j$ 表示装总重量为 j 的物品的最小价值为多少。它既可以通过  $f_{j-v_i}$ 多装一个质量为 $v_i$ 的物品得到，也可以 $f_{j+v_i}$ 装一个质量为 $-v_i$ 的物品得到。

### 边界情况

因为要求最小值，所以首先要将 f 初始化为正无穷。

显然什么都不装的时候最优解为 $f_0=0$

### 二进制优化

遇到多重背包的时候养成好习惯。将 $c_i$ 件物品拆成 $1,2,4,8 .....2^i,c_i-2^{i+1}+1$ 件物品

### 排序

让重量大的物品先选，可以避免开负数组。

## 详细注释代码

```cpp
#include<bits/stdc++.h>
using namespace std;
void read(int &x){
	int f=1;x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
	x*=f;
}
#define N 1050
#define M 20010
int t,n,tot;
int f[M<<1];//开大点,大重量可以减 
struct coin{//结构体方便排序 
	int v,c;
}a[N];
bool cmp(coin aa,coin bb){
	return aa.v>bb.v;
}
int main(){
	read(n),read(t);
	for(int i=1;i<=n;i++){
		read(a[i].v);//读质量 
	}
	tot=n;
	for(int i=1;i<=n;i++){
		int cc;read(cc);//读数量 
		int vv=a[i].v;
		a[i].c=1;//先拆成 1 个 
		cc--;
		for(int j=2;j;j<<=1){//二进制优化 
			if(j>cc){//一直拆，直到不够，把剩下的放一堆 
				j=cc;
				a[++tot].v=vv*j;
				a[tot].c=j;
				break;
			}
			a[++tot].v=vv*j;
			a[tot].c=j;
			cc-=j;
		}
	}
	sort(a+1,a+1+tot,cmp);//排序 
	memset(f,0x3f,sizeof(f));//初始化 
	f[0]=0;//边界 
	for(int i=1;i<=tot;i++){//二进制优化后变成 tot 个 
		for(int j=t<<1;j>=a[i].v;j--){//两倍循环 
			f[j]=min(f[j],min(f[j-a[i].v]+a[i].c,f[j+a[i].v]+a[i].c));
		}
	}
	if(f[t]==0x3f3f3f3f) printf("-1");//无解 
	else cout<<f[t];
	return 0;
}


```


---

## 作者：小恐 (赞：3)

这应该是一道多重背包和完全背包的组合问题。

John付费就是多重背包，这个可以进行二进制优化。二进制优化就是说将每种硬币分成若干组，使得能选出若干组，凑出所有硬币的个数。显然（大雾，我们可以把它们分成$2^0$个、$2^1$个、$2^2$个……。到最后不够下一个数时，我们将剩下的再分成一组。这样就节省了很多时间（否则会T）。

店主找钱就是完全背包，这个就非常普通啦，不会上网查吧。

至于枚举到多大（John付的钱数），我们可以从时间上考虑。每种钱的个数最多10000，也就是差不多$2^{15}$，n最大100，考虑到跑1秒最多$10^8$，最多枚举到66666。保险起见，一般数据时限会在std两倍以上，所以我们就去个$\frac 2 3$，就是40000。

没听明白？上代码吧：
```cpp
#include<stdio.h>
#include<iostream>
#include<string.h>
#define MAXN 40000
using namespace std;
int v[105],dp[MAXN+5],dp2[MAXN+5];//dp为多重，dp2为完全，表示最少用dp[i]枚硬币能凑到i元
int main()
{
	int n,t;
	scanf("%d%d",&n,&t);
	for(int i=1;i<=n;++i)
		scanf("%d",v+i);
	memset(dp,999999,sizeof(dp));//设成无限大
	dp[0]=0;//初始化
	for(int i=1;i<=n;++i)
	{
		int c;
		scanf("%d",&c);
		int bei=1;
		while(bei<=c)//二进制优化
		{
			int cc=bei*v[i];
			int ww=bei;
			for(int j=MAXN;j>=cc;--j)
				dp[j]=min(dp[j],dp[j-cc]+ww);//多重背包
			c-=bei;
			bei*=2;
		}
		if(c)
		{
			int cc=c*v[i];
			int ww=c;
			for(int j=MAXN;j>=cc;--j)
				dp[j]=min(dp[j],dp[j-cc]+ww);//多重背包
		}
	}
	memset(dp2,999999,sizeof(dp2));//设成无限大
	dp2[0]=0;//初始化
	for(int i=1;i<=n;++i)
		for(int j=v[i];j<=MAXN-t;++j)
			dp2[j]=min(dp2[j-v[i]]+1,dp2[j]);//完全背包
	int ans=1e9;
	for(int i=0;i<=MAXN-t;++i)
		ans=min(ans,dp2[i]+dp[i+t]);//找最小
	if(ans<1e9)
		printf("%d",ans);
	else
		printf("-1");
	return 0;
}
```
**所有的代码都要自己敲，请勿Ctrl C+Ctrl V**

---

## 作者：Anemone (赞：2)

##训练的时候直接打了一个暴搜先试……然而这个暴搜中有背包的性质。

##可是考懵了，没看出来，还加了很多乱七八糟的剪枝各种骗分。很遗憾，空间开爆了，爆了零。


##后来经过分析，发现这题的John和店主应该分开看。这样就很明显了，John是一个多重背包，老板是一个完全背包。

##完全背包没有什么优化的空间了，然而多重背包如果不加二进制优化，只能过50~80。（如果上限设置为maxv\*maxv就可以80，t+maxv\*maxv就是50……尴尬）

##加了二进制优化就AC啦。

##PS：上限=t+maxv\*maxv，证明使用了鸽笼原理，自行百度吧。（不会也不要紧，上限开大一点就好，25000左右）




核心代码如下：


    


```cpp
void dp_John()//FJ的多重背包
{
    for(int i=1;i<=tt;i++)f[i]=INF;
    for(int i=1;i<=n;i++)
    {
        int k=1,c=a[i].cc;
        while(k<c)//二进制优化
        {
            for(int j=tt;j>=a[i].vv*k;j--)
                f[j]=min(f[j],f[j-a[i].vv*k]+k);
            c-=k;k*=2;
        } 
        for(int j=tt;j>=c*a[i].vv;j--)
            f[j]=min(f[j],f[j-a[i].vv*c]+c);
    }
}
void dp_Rober()//老板的完全背包，把老板看成取i-t个物品即可
{
    for(int i=1;i<=tt;i++)g[i]=INF;
    for(int i=1;i<=n;i++)
      for(int j=a[i].vv;j<=tt;j++)
      g[j]=min(g[j],g[j-a[i].vv]+1);
}
```
输出的ans=min(f[i]+g[i-t],ans);

---

## 作者：crashed (赞：0)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.org/problem/P2851)看题目。
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;首先，我们可以把硬币的流动分为两个部分——  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;一是$John$付钱流动的硬币，这相当于一个多重背包；二是商家找零的硬币，这相当于一个完全背包。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;所以我们先用背包算出凑出每种金额需要花的最少硬币数量。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;然后我们考虑枚举$John$给的钱时在哪个范围内能搜索到答案。其实，如果我们给出的硬币超过了$T+\sum_{i=1}^nV_i$的话，答案显然就不会使最小的了（因为此时我们已经可以通过抛弃多余的硬币来得到更优的解），所以我们在$[T,T+\sum_{i=1}^nV_i]$的范围内枚举即可。
# 代码
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAXN = 105, MAXT = 10005, MAXV = 125, MAXSIZ = MAXT + MAXN * MAXV;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MAX( const _T a, const _T b )
{
	return a > b ? a : b;
}

template<typename _T>
_T MIN( const _T a, const _T b )
{
	return a < b ? a : b;
}

namespace mine
{
	struct deque
	{
		int deq[MAXSIZ], h, t;
		deque(){ h = 1, t = 0; }
		void clear(){ h = 1, t = 0; }
		int& operator [] ( const int indx ){ return deq[indx]; }
		void push_front( const int val ){ deq[--h] = val; }
		void push_back( const int val ){ deq[++t] = val; }
		void pop_front(){ h ++; }
		void pop_back(){ t --; }
		int front() const { return deq[h]; }
		int back() const { return deq[t]; }
		bool empty() const { return h > t; }
		int size() const { return t - h + 1; }
	};
}

using namespace mine;

struct coin
{
	int V, C;
	bool operator < ( const coin & other ) const
	{
		return V < other.V;
	}
}c[MAXN];

deque deq[MAXV];

int DP[MAXN][MAXSIZ], f[MAXSIZ];
int N, T;

int getVal( const int lev, const int ind )
{
	return DP[lev - 1][ind] - ind / c[lev].V;
}

int main()
{
	int S = 0, upper = 0;
	read( N ), read( T );
	for( int i = 1 ; i <= N ; i ++ ) read( c[i].V ), upper = MAX( upper, c[i].V );
	for( int i = 1 ; i <= N ; i ++ ) read( c[i].C );
	for( int i = 1 ; i <= N ; i ++ ) S += c[i].V;
	std :: sort( c + 1, c + 1 + N );
	memset( DP, 0x3f, sizeof( DP ) );
	DP[0][0] = 0;
	int indx;
	upper = T + S;
	for( int i = 1 ; i <= N ; i ++ )
	{
		for( int j = 0 ; j < c[i].V ; j ++ ) deq[j].clear();
		for( int j = 0 ; j <= upper ; j ++ )
		{
			indx = j % c[i].V;
			while( ! deq[indx].empty() && getVal( i, deq[indx].front() ) >= getVal( i, j ) ) deq[indx].pop_back();
			deq[indx].push_back( j );
			while( ! deq[indx].empty() && deq[indx].front() < MAX( j - c[i].C * c[i].V, 0 ) ) deq[indx].pop_front();
			DP[i][j] = getVal( i, deq[indx].front() ) + j / c[i].V;
		}
	}
    //单调队列优化多重背包
	memset( f, 0x3f, sizeof( f ) );
	f[0] = 0;
	for( int i = 1 ; i <= N ; i ++ )
		for( int j = c[i].V ; j <= upper ; j ++ )
			f[j] = MIN( f[j], f[j - c[i].V] + 1 );
	int minVal = 0x3f3f3f3f;
	for( int i = upper ; i >= T ; i -- )
	{
		minVal = MIN( DP[N][i] + f[i - T], minVal );
	}
	if( minVal > upper ) puts( "-1" );
	else write( minVal ), putchar( '\n' );
	return 0;
}
```

---

