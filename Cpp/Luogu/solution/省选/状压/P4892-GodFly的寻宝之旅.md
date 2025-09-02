# GodFly的寻宝之旅

## 题目背景

“蒹葭苍苍，白露为霜。所谓伊人，在水一方…”

怀着$a$ $burning$ $desire$，$GodFly$开启了他追寻学妹之路。

## 题目描述

我们把校园抽象成一个具有$n$个点的无向连通图，其中的$n$个结点分别编号为$1,2,3,...,n$。把$GodFly$经过的结点表示为一个路径集合$A=\left\{a_1,a_2,a_3,...,a_m\right\}$，表示他依次经过了编号为$a_1$、$a_2$、…、$a_m$的结点，由于集合的元素具有互异性，这意味着$GodFly$无法重复经过同一个结点。

$GodFly$现在要从第$1$个结点走到第$n$个结点，然而他的腿疾对他造成了许多不便。定义$GodFly$经过了$m$个结点，当前在点$a_m$，且路径集合$A=\left\{a_1,a_2,a_3...,a_{m-1}\right\}$（加入新结点$a_m$前）时，他的总体力耗费为$w_m=(w_{m-1}+a_m*sum(A))$%$2$，其中$w_{m-1}$表示上一个路径集合的体力耗费；且对于集合$A$，$sum(A)=a_1+a_2+...+a_{m-1}$。

对于$w=0$的情况，我们称$GodFly$处于“滑基态”，否则对于$w=1$的情况，我们称$GodFly$处于“对偶态”。现在$GodFly$想要知道，他走到$n$结点后处于滑基态或对偶态的方案数，由于这个数可能很大，你只需要输出它对$19260817$取膜（模）的结果；注意两个方案是不同的，当且仅当它们有至少一条经过的边不同，而非路径集合不同。

**注意：T3压缩包内第一个数据有误，以题面的样例为准。**

## 说明/提示

**【数据范围】**

对于$30$%的数据，$n<=10$，$k<=45$，无重边及自环；

对于$60$%的数据，$n<=15$，$k<=300$；

对于$80$%的数据，$n<=15$，$k<=100000$；

对于$100$%的数据，$n<=18$，$k<=100000$；

样例数据在**data.zip\fantasy\**中。

**【样例说明】**

![](https://cdn.luogu.com.cn/upload/pic/30986.png)

如图，初始时在$1$结点，路径集合为$\left\{1\right\}$，费用为$0$；

若从$1$走到$2$结点再走到$3$结点，到$2$结点时，费用为$(0+2*sum(\left\{1\right\}))$%$2=2*1$%$2=0$，并把$2$加入路径集合，则此时路径集合为$\left\{1,2\right\}$；到$3$结点时，因上一次费用为0，费用为$(0+3*sum(\left\{1,2\right\}))$%$2=3*(1+2)$%$2=1$；

若从$1$结点直接走到$3$结点，则费用为$(0+3*sum(\left\{1\right\}))$%$2=3*1$%$2=1$。

故最终走到$3$结点时费用为$1$的方案数为$2$。

**【提示】**

本题时限$3s$，且可以开启$O_2$优化，不必过分担心卡常数，但请确保算法足够优美。

## 样例 #1

### 输入

```
3 3
1 2
2 3
1 3
1```

### 输出

```
2```

# 题解

## 作者：Fellyhosn (赞：8)

## 典型的状压dp

### 状压dp的精髓就在于去压缩状态！然后通过一系列位运算让一个int变量实现一个约20位的数组的功能。

### [蒟蒻写的状压dp总结](https://fellyhosn.blog.luogu.org/zhuang-ya-dp-hui-zong)顺便安利一波[博客](https://fellyhosn.blog.luogu.org)

现在回到正题，$n<=18$是明显的状压标志，我们用$f[i][j]$表示当前点为$i$，走过的点集合为$j$时的方案数。

上一篇题解已经把状态转移说的很清楚了，这里就不再赘述。

有人可能会问：题目中不是要求**滑~~稽~~基态**或者**对偶态**的情况数量吗？按照正常逻辑应该在后面再加上一维$[0/1]$，来记录滑稽态/对偶态的情况数量。（事实上出题人的官方题解也是开了三维数组的）

### 事实上只需要开两维就行了。为什么呢？

### @yuyue大佬告诉我：“这题其实有规律的：一条路径无论顺序如何w始终相等”（有兴趣的可以去证明一下，打表也是可以的）

%%%太巨了@yuyue [巨佬](https://www.luogu.org/space/show?uid=76192)

有了这个结论，就可以直接通过最后的状态算出滑稽/对偶态。

### 代码：
~~~
#include<iostream>
#include<cstdio>
#include<algorithm>
#define mod 19260817
#define ll long long
using namespace std;

int n,m,c;
int a[20][20];
ll f[20][1<<18+2];//当前点i状态为j 
ll ans;
//判断状态的w值
bool pd(int v){
    int sum=0,w=0;
    for(int o=1;o<=n;o++)
    if(v&(1<<o-1))
    w=(w+sum*o)%2,sum=(sum+o)%2;
    return w%2==c;
} 

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
       int x,y;
       scanf("%d%d",&x,&y);
       if(x!=y)
       a[x][y]++,a[y][x]++;	
    }
    scanf("%d",&c);
    f[1][1]=1;
    for(int i=1;i<(1<<n);i++)//枚举所有状态
    for(int j=1;j<=n;j++)//枚举to点
    if((1<<j-1)&i)
    for(int k=1;k<=n;k++)//枚举fro点
    if((1<<k-1)&i&&k!=j&&a[j][k])
    f[j][i]=(f[j][i]*1ll+1ll*a[j][k]*f[k][i-(1<<j-1)])%mod;
    for(int i=1;i<(1<<n);i++)
    if((i&1)&&(i&1<<n-1))
    if(pd(i))
    ans=(ans+f[n][i])%mod;
    cout<<ans;
    return 0; 
}
~~~

---

## 作者：wind_seeker (赞：2)

是没有发现性质的 dp。

考虑 $dp_{i,j,k}$，$i$ 表示最后的点，$j$ 表示点的集合，$k$ 表示 $w,sum$ 的状态，计算 $k$ 是 $w,sum$ 在模 $2$ 意义下组合成的二进制转十进制。

然后直接按照题意转移即可。

然后我们来证明一下楼上题解没给证明的性质：

- 不难发现，其实计算 $w$ 就是将排列的每一位和前缀和相乘，则每两位都相乘了 $1$ 次，所以只要路径集合确定，无论集合的数是怎么排列的，最后答案都是一样的。

```cpp
/*********************************************************************
    作者: wind_seeker
    日期: 2023-10-05 09:26 
*********************************************************************/
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=20,mod=19260817;

int n,m,ans;
int e[N][N],dp[N][1<<N][4],op;

inline int read(){
	int res=0,f=1;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) res=(res<<3)+(res<<1)+(c^48);
	return res*f;
}
//  w sum
//0:0 0
//1:0 1
//2:1 0
//3:1 1

signed main(){
	n=read(),m=read();
	for(int i=1,u,v;i<=m;i++){
		u=read(),v=read();
		e[u][v]++,e[v][u]++;
	}
	op=read();
	int S=(1<<n);
	dp[1][1][1]=1;
	for(int i=1;i<S;i++){
		for(int j=1;j<=n;j++){
			if(!((i>>(j-1))&1)) continue;
			for(int k=1;k<=n;k++){
				if((i>>(k-1))&1||e[j][k]==0) continue;
				int w,sum,now;
				w=0,sum=k%2,now=w*2+sum;
				dp[k][i+(1<<(k-1))][now]=(dp[k][i+(1<<(k-1))][now]+dp[j][i][0]*e[j][k])%mod;
				w=k%2,sum=(k+1)%2,now=w*2+sum;
				dp[k][i+(1<<(k-1))][now]=(dp[k][i+(1<<(k-1))][now]+dp[j][i][1]*e[j][k])%mod;
				w=1,sum=k%2,now=w*2+sum;
				dp[k][i+(1<<(k-1))][now]=(dp[k][i+(1<<(k-1))][now]+dp[j][i][2]*e[j][k])%mod;
				w=(k+1)%2,sum=(k+1)%2,now=w*2+sum;
				dp[k][i+(1<<(k-1))][now]=(dp[k][i+(1<<(k-1))][now]+dp[j][i][3]*e[j][k])%mod;
			}
		}
		if(op==0) ans=(ans+dp[n][i][0]+dp[n][i][1])%mod;
		if(op==1) ans=(ans+dp[n][i][2]+dp[n][i][3])%mod;
	}
	/*for(int i=1;i<S;i++)
		for(int j=1;j<=n;j++)
			for(int k=0;k<=3;k++)
				if(dp[j][i][k]) printf("dp[%lld][%lld][%lld]:%lld\n",j,i,k,dp[j][i][k]);*/
	printf("%lld\n",ans);
	return 0;
}
/*
3 3
1 2
2 3
1 3
1
*/
/*
4 4
1 2
1 2
2 3
2 4
0
*/

```

---

## 作者：JimmyF (赞：1)

Part I：前言

 为数不多自己独立思考写出来的紫题之一，发篇题解纪念一下。
感觉现有的两篇题解与自己思路略有不同，自己做完题后有感而发，写一下这一类 DP 的总结。

Part II：题意
 
给一个 $n$
个点 $m$
条边的无向图。

$n$
个结点分别编号为
$1,2,3,...,n$
。

定义经过了 $m$
个结点，当前在点 $a_m$ 
 ，且路径集合 $A=\left\{a_1,a_2,a_3...,a_{m-1}\right\}$
（加入新结点 $a_m$
前）时，他的总体力耗费为 $w_m=(w_{m-1}+a_m\times Sum(A)) \%2$
，其中 $w_{m-1}$
表示上一个路径集合的体力耗费；且对于集合 $A$
， $Sum(A)=a_1+a_2+...+a_{m-1}$
 。
最后给出一个 $opt \in \{0,1\}$
求出 $w=opt$
且最后走到 $n$
号节点的方案总数对 $19260817$
取模的结果。

PS：两个方案是不同的，当且仅当它们有至少一条**经过的边**不同，而非路径集合不同。

Part III：分析

考虑**状态，阶段，转移**， DP 三要素。较容易得出我们需要记录当前我们处理了哪些节点（一个集合），当前处在哪个节点，以及当前集合的 $w$
值为多少。

那么设出状态 $dp[s][i][op]$
表示处理完了 $s$
集合，当前处于 $i$
号节点且 $w$
值为 $op$
的方案总数。

阶段则是从 $1$
到 $n$
的节点转移，也就是题目描述的 GodFly 现在要从第 $1$
个结点走到第 $n$
个结点。

接下来考虑转移，枚举一个节点 $j$
，如果有一条连边 $i\to j$
且 $j\notin s$
则可以从 $dp[s][i][op]$
转移到 $dp[s\cup j][j][(op+\text Sum(s)\times a_j)\% 2]$
。

但是考虑一个细节：假如一条边出现了**多次**，如何计算呢？那么同一个集合的转移则会有同样**多次**，将贡献乘上次数即可。

Part IV：代码

仅供参考。

```cpp
#include<bits/stdc++.h>
#define il inline
#define rint register int
#define int long long
using namespace std;
il int rd(){
	int x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
const int N=19,mod=19260817;
il void ad(rint &x,rint y){
	x+=y;
	x%=mod;
}
int G[N][N];
int x,y;
int dp[N][1<<N][2];
int sum[1<<N];
signed main(){
	int n=rd(),m=rd();
	for(rint i=1; i<=m; ++i){
		int x=rd(),y=rd();
		++G[x][y];
		++G[y][x];
	}//建边 
	for(rint i=0; i<(1<<n); ++i){
		rint tmp=i,tot=0;
		while(tmp){
			++tot;
			if(tmp&1)sum[i]+=tot;
			tmp>>=1;
		}
	}//预处理Sum() 
	dp[1][1][0]=1;//初始值 
	for(rint i=1; i<(1<<n); ++i){
		for(rint j=1; j<=n; ++j){
			for(rint k=1; k<=n; ++k){
				if(!G[j][k])continue;
				int to=k;
				if(i&(1<<(to-1)))continue;
				ad(dp[to][i|(1<<(to-1))][(to*sum[i]+0)&1],G[j][k]*dp[j][i][0]);
				ad(dp[to][i|(1<<(to-1))][(to*sum[i]+1)&1],G[j][k]*dp[j][i][1]);
				//转移 
			}
		}
	}
	int ans=0;
	rint id=rd();
	for(rint i=1; i<(1<<n); ++i){
		if((i&1)&&i&(1<<n-1))
			ad(ans,dp[n][i][id]);
	}
	//统计 
	cout<<ans;
	return 0;
}
```


Part V：尾声

那么这题就结束了，题解写得不好还请海涵。

另外这题还有一个比较相似的题
$\to$
[P3959 [NOIP2017 提高组] 宝藏](https://www.luogu.com.cn/problem/P3959)

AC 了这题后可以去尝试一下。



---

## 作者：soul_M (赞：1)

题意描述略，有点繁琐，点此[GodFly的寻宝之旅](https://www.luogu.org/problemnew/show/U37614)

题解：由于只有18位，用状压DP。

首先读入边，r[i][j]表示i，j之间连边数量。

定义状态：f[i][s][w]表示停留在i点，路径集合为s，花费为w时方案总数，则答案即为sigma(f[n][s][q]),其中s为任意状态。

初始化：f[1][1][0]=1;

状态转移方程：设从i点，状态为s转移到t点，则有

f[t][s|(1<<t-1)][(0+t×num[s])%2]+=f[i][s][0]×r[i][t]

f[t][s|(1<<t-1)][(1+t×num[s])%2]+=f[i][s][1]×r[i][t]

即 下一状态方案数 +=当前方案数×转移的路径条数

最后ans=sigma(f[n][s][q])，q为询问状态。

### 题解结束

## 正文开始

位运算/状压DP常用技巧:

### 每位只有0,1两种状态，共有n位，枚举所有状态：

for(int s(0);s<=(1<<n)-1;s++)

### 第i位为1的二进制表示：

（1<<i-1）

### 判断状态s第i位是否为1(判断是否已经选过)

return (1<<i-1)&s

若为1，则在（i和s都为1）

若为0，不在。

### 将s的第i位设置为1

s=s|(1<<t-1) 

|  表示按位或



---

