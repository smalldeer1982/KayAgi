# Dima and Salad

## 题目描述

有 $n$ 个水果，每个水果有两个属性：美味值和卡路里值。现在选用若干个（至少 $1$ 个）水果制作一份特殊的沙拉，沙拉的美味值为所选的水果的美味值的和，沙拉的卡路里值为所选水果的卡路里值的和。沙拉的美味值恰好是卡路里值的 $K$ 倍。请计算该沙拉美味值最大为多少。

## 样例 #1

### 输入

```
3 2
10 8 1
2 7 1
```

### 输出

```
18
```

## 样例 #2

### 输入

```
5 3
4 4 4 4 4
2 2 2 2 2
```

### 输出

```
-1
```

# 题解

## 作者：TMLL (赞：33)

思路：根据a[i] - k*b[i] = 0 ,我们可以将其看作是一个背包问题，a[i]当作是价值，a[i]-k*b[i]当作是重量 ,0为容量，因为 a[i]-k*b[i]有正有负，所以可以在0上加个10000 
所以最后答案由dp[0]变为dp[10000]; 


---

## 作者：Liynw (赞：30)

### 前言

[题目链接](https://www.luogu.com.cn/problem/CF366C)

**正解：动态规划-01背包**

转化思维难度比较大 qwq。

***

### 转化

首先假设我们选了 $m$ 个水果。已知：

$$\dfrac{\sum\limits_{i=1}^{m}a_i}{\sum\limits_{i=1}^{m}b_i}=k$$

转换式子后可得：

$$\sum\limits_{i=1}^{m}a_i=\sum\limits_{i=1}^{m}b_i\times k$$

再次转换：

$$\sum\limits_{i=1}^{m}a_i-\sum\limits_{i=1}^{m}b_i\times k=0$$

可以写成：

$$\sum\limits_{i=1}^{m}(a_i-b_i\times k)=0$$

所以我们可以让第 $i$ 个水果的重量为 $a_i-b_i\times k$，最后只要让重量总和等于 $0$ 就算满足条件啦。

### 数组范围和初始值

此时我们需要注意初始值：因为按照上面这么分析，水果的重量和完全有可能是负数。这个时候看到数据范围：

$1\le n\le 100,1\le k\le 10,1\le a_i,b_i\le 100$

最小极限情况：$n=100,k=10,a_i=1,b_i=100$

那么重量总和就为：

$100\times (1-100\times 10)\approx -100000$

所以 $dp$ 数组中，每一个数字都需要加上 $100000$ 以保证不越界。我们可以定义一个常量 $p=100000$，写代码更加简洁，不过不写也是可以的。

接着我们计算最大极限情况：$n=100,k=1,a_i=100,b_i=1$

那么重量总和就为：

$$100\times (100-1\times 1)\approx 10000$$

所以 $dp$ 数组需要开 $110000+5$，这也是最大有可能出现的背包容量。

### 细节

最后要注意：因为重量有正有负，所以我们不知道循环是从小到大还是从大到小。所以我没有打滚动，如果要打滚动，需要注意判断重量的正负之后判断循环的顺序。

打代码要注意细节，我错了很多次才对。

（PS：我打代码的时候觉得 $a_i-b_i\times k$ 看着不爽，就改成了 $b_i\times k-a_i$，这样在分析极限值的时候有变化，需要注意。）

### $Code$

```cpp
#include<cstdio>
#include<cstring>
#define max(a,b) (a)>(b)?(a):(b)
int n,k,a[105],b[105],m[105],dp[105][110005];
int main(){
	memset(dp,-1,sizeof(dp));
	dp[0][10000]=0; //最后答案的位置是0
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&b[i]);
		m[i]=k*b[i]-a[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=110000;j>=0;j--){
			if(j-m[i]<=110000&&j-m[i]>=0){ //不能越界，越了界后面就没有回来的可能性了，直接跳过此循环
				if(dp[i-1][j-m[i]]==-1)
					dp[i][j]=dp[i-1][j]; //不可能
				else
					dp[i][j]=max(dp[i-1][j],dp[i-1][j-m[i]]+a[i]);
			}
		}
	}
	if(dp[n][10000])
		printf("%d",dp[n][10000]);
	else
		printf("-1");
	return 0;
}
```

### 写在最后

我写了好久，求赞n(\*≧▽≦\*)n。

---

## 作者：YellowBean_Elsa (赞：12)

#### UPD 8.2.2020 

之前代码里有一处问题，现已修正。感谢@Lcx柒伍陆 的指出。

### 结合分数规划思想的的背包

推式子：

$$\sum(a_i) / \sum(b_i) = k;$$

$$\sum(a_i - b_i\times k) = 0;$$

所以我们令 
$$c_i = a_i - b_i \times k$$
再以 c 为质量 a 为价值进行背包即可

#### Attention

由于 c 可能为负数，我们用这种经典思路：

令 f[i] 表示质量和为i时最大价值

令 g[i] 表示质量和为-i时最大价值

用 f[i] + g[i] 统计答案

贴代码，注意初始化及背包质量上限：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=216;
const int M=20019;
inline int read(){
	int x=0;char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
	return x;
}
int n,k;
int a[N],b[N];
int c[N],f[M],g[M];
//f：维护正的c。g：维护负的c。
int ans;
int main(){
	n=read(),k=read();
	for(int i=1;i<=10001;i++)f[i]=g[i]=-1e9;//初始化，f[0]=g[0]=0，其他-INF 
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=1;i<=n;i++){
		c[i]=a[i]-b[i]*k;
		if(c[i]>=0)//c[i]为正数 
			for(int j=1e4;j>=c[i];j--)
				f[j]=max(f[j],f[j-c[i]]+a[i]);
		else//c[i]为负数 
			for(int j=1e4;j>=-c[i];j--)
				g[j]=max(g[j],g[j+c[i]]+a[i]);
	}for(int i=0;i<=1e4;i++)
		ans=max(ans,f[i]+g[i]);//统计答案
		//f[i]+g[i]保证c之和为0 
	if(ans)printf("%d\n",ans);
	else puts("-1");
	return 0;
}
```


---

## 作者：xixiup (赞：7)

## 思路分享

这道题有 $n$ 个水果，每个水果可以选或不选，是不是非常熟悉呢？

没错，这就是一道背包问题。

但是问题来了，如何维护 $\sum a_i$ 恰好是 $\sum b_i$ 的 $k$ 倍呢？

考虑看一看题中给的这个式子，并将其变形：
$$
\boxed{\dfrac{\sum\limits_{j=1}^m a_j}{\sum\limits_{j=1}^m b_j}=k}
$$
$$
\boxed{\sum\limits_{j=1}^m a_j=k\times\sum\limits_{j=1}^m b_j}
$$
$$
\boxed{\sum\limits_{j=1}^m a_j-k\times\sum\limits_{j=1}^m b_j=0}
$$
所以我们不妨设一个水果的体积 $v_i=a_i-k\times b_i$，价值为 $a_i$，然后就可以跑普通的背包了。

但是要考虑一个问题：$v_i$ 有正有负，且最终结果为 $dp_0$，所以我们就可以开两个 $dp$ 数组，一个叫做 $po$,专门管正的 $v_i$，另一个叫做 $ne$，专门管负的 $v_i$，最后的答案就是 $po_i+ne_i$，问题不就迎刃而解了吗？

## 代码展示

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=110,maxm=100100;
int n,m,k,a[maxn],b[maxn],v[maxn];
int po[maxm],ne[maxm];
int main(){
	cin>>n>>k;
	m=100000;//m就是最大的空间
	for(int i=1;i<=m;i++){
		po[i]=ne[i]=-1000000000;
	}//i时从1开始的
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&b[i]);
		v[i]=a[i]-k*b[i];
	}
	for(int i=1;i<=n;i++){
		if(v[i]>=0){//正的情况
			for(int j=m;j>=v[i];j--){
				po[j]=max(po[j],po[j-v[i]]+a[i]);
			}
		}
		else{
			v[i]=-v[i];//负的情况
			for(int j=m;j>=v[i];j--){
				ne[j]=max(ne[j],ne[j-v[i]]+a[i]);
			}
		}
	}
	int ans=0;
    //ans要赋为0，方便待会儿判断误解
	for(int i=0;i<=m;i++){
		ans=max(ans,po[i]+ne[i]);
	}
	if(ans==0){
		puts("-1");
	}
	else{
		cout<<ans; 
	}
	return 0;
}
```


---

## 作者：_Aoi_ (赞：3)

在开始做这道题的时候，看到了楼上大佬们的题解，便也想写一篇。


------------
### 这是一道背包问题
根据大佬@TMLL的思路：
```
思路：根据a[i] - kb[i] = 0 ,我们可以将其看作是一个背包问题，a[i]当作是价值，a[i]-k*b[i]当作是重量 ,0为容量，因为 a[i]-k*b[i]有正有负，所以可以在0上加个10000 所以最后答案由dp[0]变为dp[10000];
```
$dp_{i,j}$表示在前$i$种水果中，$c$的和为$j$时$a$的和的最大值。

注意：转移的时候，先前的状态是否可以达到。如果不能达到，一定不能从先前的状态转移，要 **特判**。

code：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct emm{//可爱的结构体 
	int a,b,c;
}em[1001];
int dp[105][50005],n,k;//dp数组要定义大一些，因为最后加上了1000 
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>em[i].a;//价值 
	for(int i=1;i<=n;i++)
	{
		cin>>em[i].b;
		em[i].c=em[i].a-k*em[i].b;//重量 
	}
	memset(dp,-1,sizeof(dp));//初始化 
	dp[0][10000]=0;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=50000;j++)
		{
			if(dp[i-1][j]==-1&&dp[i-1][j-em[i].c]==-1)//特判 
				continue;
			else if(dp[i-1][j-em[i].c]!=-1)
				dp[i][j]=max(dp[i-1][j],dp[i-1][j-em[i].c]+em[i].a);
			else
				dp[i][j]=dp[i-1][j];
		}
	if(dp[n][10000]==0)
		cout<<-1;
	else
		cout<<dp[n][10000];//加上1000后输出 
	return 0;
}
```




---

## 作者：Tyyyyyy (赞：3)

# 实质是一道背包问题。
题目大意已经翻译得很清楚了，直接讲思路。

对于每个水果，有选或不选两种状态。容易联想到背包$dp$。

那么问题来了：如何将它转化为背包问题？

题目要求最后使得总美味值$A$是总卡路里值$B$的$k$倍。

由于总美味值$A$是所有水果的美味值之和，即$a_1+a_2+......+a_i$。

同理，总卡路里$B$是所有水果的卡路里之和，即$b_1+b_2+......+b_i$。

因此有：

$a_1+a_2+......+a_i=k(b_1+b_2+......+b_i)$

由于$a_i$和$b_i$是一一对应的，容易得到：

当且仅当所有被挑选的水果的$a_i-b_i\times$$k$之和为0时，满足题目条件。

我们不妨用$c_i$来表示对应的$a_i-b_i\times$$k$。

但此时，$c_i$有可能为负数。

因此我们分两种情况讨论，$c_i$为正数、负数的结果分别存入两个数组$dp1$,$dp2$中。

因为要计算一种水果的多个参数，不妨使用结构体来存储数据。

最后的答案不断在$ans$与$dp1[i]+dp2[i]$中取较大值即可。

如果$ans$最终为0，说明没有符合题意的搭配，输出$-1$即可。

此处注意：由于运算涉及到负数，一开始的$dp$数组要定义一个极小值。

AC代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<iomanip>
#include<cmath>
#include<queue>
#include<algorithm>
using namespace std;
int n,k,dp1[110000],dp2[110000],ans;
struct fruits
{
	int a,b,c;
}m[110];
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)scanf("%d",&m[i].a);
	for(int i=1;i<=n;i++)scanf("%d",&m[i].b);
	for(int i=1;i<=100000;i++)dp1[i]=dp2[i]=-1e9;
	for(int i=1;i<=n;i++)
	{
		m[i].c=m[i].a-m[i].b*k;
		if(m[i].c>0)
			for(int j=100000;j>=m[i].c;j--)dp1[j]=max(dp1[j],dp1[j-m[i].c]+m[i].a);
		if(m[i].c<=0)
			for(int j=100000;j>=-m[i].c;j--)dp2[j]=max(dp2[j],dp2[j+m[i].c]+m[i].a);
	}
	for(int i=0;i<=100000;i++)ans=max(ans,dp1[i]+dp2[i]);
	if(ans)printf("%d",ans);
	else printf("-1");
	return 0;
}
```

---

## 作者：_masppy_ (赞：2)

### 题目链接：[Link](https://www.luogu.com.cn/problem/CF366C)

&nbsp;

### 题目大意：
给定长度为 $n$ 的两个序列 $a$ 和 $b$ 和一个不大于 $10$ 的正整数 $k$，选出若干个下标 $i$ 组成集合 $X$，使得$\sum\limits_{i=1}^{i\in X}a_i=k\times \sum\limits_{i=1}^{i\in X}b_i$，求满足这个条件时 $\sum\limits_{i=1}^{i\in X}a_i$ 的最大值。

### 解题思路：
看到常规写法题解区已经有很多了，这里提供一种略微有些抽象的实现方式。

先讲讲思路，题目一眼 `dp`，于是开始看数据范围猜测一下时间复杂度，发现 $1 \leq n,a_i,b_i\leq 100$，$1 \leq k \leq 10$，比较小，一看就是给我这种乱搞选手准备的（bushi）。

于是开始观察题面，准备找一些可以乱搞的性质。发现对于 $x \equiv z\pmod{m}$ 和 $y\equiv m-z\pmod{m}$，$x+y\equiv 0\pmod{m}$，于是我们显然可以将序列分为 $a_i-k\times b_i>0$，这里称为 $pst$，和 $a_i-k\times b_i<0$，这里称为 $neg$，两部分进行处理，而对于等于零的那部分，显然会被选择，于是输入的时候直接添加到答案中即可， 然后又因为 $a_i,b_i\leq100$，$k\leq10$，所以在最极端的情况下 $|a_i-k\times b_i|=999$，这时 $a_i=1$， $b_i=100$，$k=10$。假设对于所有的 $i \in [1,n]$，$|a_i-k\times b_i|=999$，那么任意从中选取若干个下标 $i$ 组成集合 $X$，$\sum\limits_{i=1}^{i\in X}|a_i-k\times b_i| \leq99900$，这是显然的。

可以发现最大值并不是不可接受，于是便考虑使用一种极度抽象的做法，也就是对于序列 $pst$ 和 $neg$，枚举出所有的可能的 $\sum\limits_{i=1}^{i\in X}|a_i-k\times b_i|$，之后对于每个可能值，记录其最大的 $\sum\limits_{i=1}^{i\in X}a_i$。

然后我们尝试对于两个序列进行配对，也就是枚举由 $pst$ 序列中的元素能构造出的和，判断 $neg$ 序列是否也能构造，如果可以就计算出两个序列中这个和所对应的最大值之和，这里记为 $sum$，这些 $sum$ 的最大值，即为最终的答案。

枚举可能和不难实现，这里记一个数组 $stk$，和一个数组 $deli$，代表 $pst$ 中的元素能够造出的可能和和每个可能和所对应的最大 $a_i$ 之和，假设现在枚举到 $pst_i$，而 $stk$ 数组中已经记录了$x$ 个可能和，那么我们尝试枚举 $i \in [1,x]$，并判断 $deli[stk[i]+pst[j]]$ 是否已经赋值，如果未赋值则 $stk[i]+pst[j]$ 一定为一个未出现过的可能和，将其记录到 $stk$ 中并给对应的 $deli$ 赋值，而如果则有值，则判断是否能增大 $deli[stk[i]+pst[j]]$ 的值。

配对也比较容易实现，这里不再多赘述，详细可以看代码。

代码如下：
```cpp
#include<bits/stdc++.h>
#define lson pos<<1
#define rson pos<<1|1
#define ll long long
using namespace std;
const int maxn=1e2+10;
const ll mod=998244353;
int n,m,k;
int a[maxn],b[maxn];
int neg[maxn],pst[maxn];
int neg1[maxn],pst1[maxn];
int cnt1=0,cnt2=0;
int deli[100010],deli1[100010];
int stk[100010],stk1[100010];
struct node{
	int id,sum;
}q[100010];

int main(){
	//freopen("test.in","r",stdin);
	//freopen("wjudge.out","w",stdout);
	memset(deli,0,sizeof(deli));
	memset(deli1,0,sizeof(deli1));
	scanf("%d%d",&n,&m);
	
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	
	int ans=0;
	for(int i=1;i<=n;i++){
		scanf("%d",&b[i]);
		if(b[i]*m<a[i]) pst[++cnt1]=a[i]-b[i]*m,pst1[cnt1]=a[i];//分为不同的序列
		else if(b[i]*m==a[i]) ans+=a[i];
		else neg[++cnt2]=b[i]*m-a[i],neg1[cnt2]=a[i];  
	}
	
	stk[0]=stk1[0]=0;
	int tp=0,tp1=0;
	for(int i=1;i<=cnt1;i++){
	//	cout<<pst[i]<<" ";
		int r=0;
		int tmp=tp;//这里防止单个数重复计算
		for(int j=0;j<=tmp;j++){
			//if(stk[j]+pst[i]==) cout<<endl<<stk[j]<<" "<<pst[i]<<endl;
			if(deli[stk[j]+pst[i]]){//如果已经出现过这个和则更新最大值
				if(deli[stk[j]+pst[i]]<deli[stk[j]]+pst1[i]){
					q[++r].id=stk[j]+pst[i];
					q[r].sum=deli[stk[j]]+pst1[i];
				}
			}
			else{//没有出现就把新的和推进来
				stk[++tp]=stk[j]+pst[i];
				if(deli[stk[j]+pst[i]]<deli[stk[j]]+pst1[i]){
					q[++r].id=stk[j]+pst[i];
					q[r].sum=deli[stk[j]]+pst1[i];
				}
			}
		}
		
		for(int j=1;j<=r;j++) deli[q[j].id]=q[j].sum;
	}
	//cout<<deli[408]<<endl;
	
	for(int i=1;i<=cnt2;i++){
	//	cout<<neg[i]<<"  ";
		int r=0;
		int tmp=tp1;
		for(int j=0;j<=tmp;j++){
		//	if(stk1[j]+neg[i]==342)cout<<endl<<stk1[j]<<" "<<neg[i]<<endl;
			if(deli1[stk1[j]+neg[i]]){
				if(deli1[stk1[j]+neg[i]]<deli1[stk1[j]]+neg1[i]){
					q[++r].id=stk1[j]+neg[i];
					q[r].sum=deli1[stk1[j]]+neg1[i];
				}
			}
			else{
				stk1[++tp1]=stk1[j]+neg[i];
				if(deli1[stk1[j]+neg[i]]<deli1[stk1[j]]+neg1[i]){
					q[++r].id=stk1[j]+neg[i];
					q[r].sum=deli1[stk1[j]]+neg1[i];
				}
			}
		}
		
		for(int j=1;j<=r;j++) deli1[q[j].id]=q[j].sum;
	}
	
	int tmp=0;
	for(int i=1;i<=tp;i++){//配对
		if(deli1[stk[i]]) tmp=max(tmp,deli[stk[i]]+deli1[stk[i]]);//判断stk中出现的数在stk1中是否也出现过
	}
	//cout<<endl;
	
	if(ans==0&&tmp==0) printf("-1");//是否有解
	else printf("%d",tmp+ans);
	return 0;
}

```
完结撒花 OvO！！！

---

## 作者：black_trees (赞：1)

### 推式子+背包
----

显然的，这一题只需要做两种决策：拿，不拿。

所以本质是一道 $0/1$ 背包。

题目中要求 $ \Sigma a_i = k \times \Sigma b_i$。

珂以推出柿子：


$$\Sigma a_i- \ (k\times\Sigma b_i\ )=0$$

再来看如何换成背包。

我想到的是把美味值 $a$ 拿来作价值，因为我们可以将它看成"主元"（大概是这个意思）

背包的总容量 $V$ 应该 $=10^4$  。
为何？ 题中说最多有$100$个水果，每个水果的美味值最大$100$ 也就是 $100^2 =10^4$。

那么，每个物品的体积是什么呢？

设 $sum_i=a_i-k\times b_i$ （此时 $sum_i$ 不一定满足上面等于 $0$ 的性质）

如果 $sum_i =0$ 那么它满足性质，也就是说可满足 $k$ 倍关系。

否则它会是一个 $-10^4 $ 到 $10^4$ 之间的非$0$整数。

我们可以将它看成一个“差值”。

如果它太大，需要之后的负数来减，如果太小，需要之后的整数来加。

也就是尽量使它等于 $0$。

套入背包的方程：

$$\begin{cases}f_1[j]=\max(f_1[j],f_1[j-sum[i]]+a[i]),(sum[i] \ge0)\\f_2[j]=\max(f_2[j],f_2[j+sum[i]]+a[i]),(sum[i]\le0)\end{cases}$$

最后用 $ans$ 和 $f_1[i]+f_2[i]$ 不断更新最大值即可（$ans=0$ 即是无解，输出 $-1$）

---

代码：：

初始化：（这里最好赋值为 $-10^9$，我试过 $0xcf,INT\_MIN$ 都是错的……（玄学））

![](https://cdn.luogu.com.cn/upload/image_hosting/dvr1ubc7.png)



$DP$：

![](https://cdn.luogu.com.cn/upload/image_hosting/8axuy57s.png)

(图片防抄袭~（思路有了应该不用看代码吧……）)

-----


---

## 作者：Light_in_Dark (赞：0)

~~早就想写这篇题解了，只是一直没找到题目。。。~~

看到这种题目，像什么求最大或求方案之类的，不是高级数据结构就是 `dp`！于是就可以很~~不~~轻松地想出一个大概的框架 $--$ 背包 `dp`！为什么是背包？看着数据范围就可以知道，价值不是负数，而又小于 $100$，~~而普通 `dp` 又没有思路~~，就可以确信，他就是背包 `dp`！

$emm...$，那既然是背包 `dp`，状态是什么？首先 `k` 是定值，意思就是说让我们求出一个最大的 $\sum\limits^{m}_{i=1}a_j$ 使得 $\sum\limits^{m}_{i=1}a_j=k\sum\limits^{m}_{i=1}b_j$，就可以很~~不~~清晰地想出用 $\sum\limits^{m}_{i=1}a_j-k\sum\limits^{m}_{i=1}b_j$ 作为背包容量。但背包容量可能是负数怎么办？有两种方法，一种是用 `map`，但过不过的了就不是我的问题了；另一种是把背包的“0”往后移，使负数也可以用 $0$ 以上的数表示。很懵？看代码：

$NO.1$ 搜索

```cpp
#include <bits/stdc++.h>
using namespace std;
const int inf = 10000; //表示 "0" 
int k, n, a[105], b[105], dp[105][(inf << 1) + 5], ans;
void dfs(int w, int i, int tot) {
	if (dp[i][w] >= tot) //判断是否可以更新答案 
		return;
	dp[i][w] = tot; //更新答案 
	if (i > n) {
		if (w == inf)
			ans = tot; //如果为 "0"，就更新答案 
		return;
	}
	dfs(w, i + 1, tot); //不选 
	dfs(w + k * b[i] - a[i], i + 1, tot + a[i]); //选 
	return;
}
int main() {
	memset(dp, -1, sizeof(dp)); //初始化 
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &a[i]);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &b[i]);
	dfs(inf, 1, 0); //开始暴搜 
	printf("%d", ans ? ans : -1); //输出答案 
	return 0;
}
```

$NO.2$ `dp`

```cpp
#include <bits/stdc++.h>
using namespace std;
const int inf = 10000; //为 "0" 
int k, n, a[105], b[105], dp[105][(inf << 1) + 5];
int main(){
	memset(dp, -1, sizeof(dp)); //初始化 
	dp[0][inf] = 0;
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &a[i]);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &b[i]);
	for (int i = 1; i <= n; ++i) {
		int w = k * b[i] - a[i], end = max(0, w), begin = (inf << 1) + min(0, w); //begin 与 end 是防止越界 
		for (int j = begin; j >= end; --j) {
			if (dp[i - 1][j - w] != -1) //如果此处可以用 j - w 到达 
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w] + a[i]);
			else //否则 
				dp[i][j] = dp[i - 1][j];
		}
	}
	if(dp[n][inf]) //如果有值 
		printf("%d", dp[n][inf]);
	else //否则 
		printf("%d", -1);
	return 0;
}
```

不过自测记忆化搜索比 `dp` 慢不止一倍。。。

---

## 作者：李至擎 (赞：0)

[点我看题](https://www.luogu.com.cn/problem/CF366C)

思路：感谢 $dalao$ [@little_coco](https://www.luogu.com.cn/user/149219)的思路：

```
由于所选a[i]的和等于b[i]的和的k倍，所以a[i]的和减k*b[i]=0。

考虑01背包，将a[i]-kb[i]的值设为重量，a[i]为价值。又发现a[i]-kb[i]有正有负，所以把正负分开，最终的答案为dp[i][0]+dp[i][1]。因为这时i与i抵消，最终a[i]之和-k*b[i]之和等于0
```

方法：

- $1.$ 输入 $a$ 数组与 $b$ 数组；

- $2.$ 计算并储存 $a[i]-k*b[i]$ 的差；

- $3.$ 将其按差的正负进行分类讨论并按 $01$ 背包处理；

- $4.$ 如果有答案，输出答案；如果没有答案，输出 $-1$ 。

细节：

- $1.$ 是先输入$a$ 数组在输入 $b$ 数组，而不是同时输入；

- $2.$ CF似乎用不起三目运算符的样子，所以老老实实写 $if$ 吧！

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105],b[105],c[105];//a、b数组如题意，c是a[i]-k*b[i]的差值 
int dp[1000005][5];//dp[i][0]表示差值大于0时容量为i的最大值，dp[i][1]表示差值小于0时容量为i（差值为-c[i]）的最大值
int n,k,ans;//n、k数组如题意，ans是答案 
int main()
{	
	memset(dp,-0x3f3f3f3f,sizeof(dp));//赋上极小值 
	dp[0][0]=dp[0][1]=0;//当容量为0时，最大值为0 
	cin>>n>>k;//输入 
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n;i++)
	{
		cin>>b[i];
	}
	for(int i=1;i<=n;i++)
	{
		c[i]=a[i]-k*b[i];//计算并储存差值 
	}
	for(int i=1;i<=n;i++)
	{
		if(c[i]>=0)//如果差值不小于0 
		{
			for(int j=10000;j>=c[i];j--)//01背包板子 
			{
				dp[j][0]=max(dp[j][0],dp[j-c[i]][0]+a[i]);//转移 
				ans=max(ans,dp[j][0]+dp[j][1]);//答案更新 
			} 			
		}
		else//反之，如果差值小于0 
		{
			for(int j=10000;j>=-c[i];j--)//01背包板子  
			{
				dp[j][1]=max(dp[j][1],dp[j+c[i]][1]+a[i]);//转移
				ans=max(ans,dp[j][0]+dp[j][1]);//答案更新 
			} 			
		}
	}
	if(ans==0)cout<<-1;//如果无解，输出-1 
	else cout<<ans;//如果有解，输出答案  
    return 0;//结束程序 
}
```


---

## 作者：AC自动机 (赞：0)

### 思路
首先这道题要保证商为k的条件下，能得到a的和最大，直接做dp的话很麻烦，无法直接推导出结果，所以要转化一下题意，如果先计算出每种水果的c=a-k*b的值，那么只需要保证所有挑选的c相加和为0，就可以说明商为k，此时可以做dp，dp[i][j]表示在前i种水果中选择，c的和为j时a的和的最大值。最终答案应为dp[n][0],但是计算时会算到下标为负值，所以要将dp数组平移。

### 小细节
一定到注意，转移的时候，先前的状态是否可以达到，如果不能达到，一定不能从先前的状态转移，要** _特判_ **！！！！！

#### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
struct nod{
	int a;
	int b;
	int cha;
};
nod fr[105];
int dp[105][50050];
int main(){
	int n,k;
	cin>>n>>k;
	int xx=150*n;
	for(register int i=1;i<=n;i++){
		cin>>fr[i].a;
	}
	int fu=0;
	for(register int i=1;i<=n;i++){
		cin>>fr[i].b;
		fr[i].cha=fr[i].a-k*fr[i].b;
		if(fr[i].cha<0){
			fu+=fr[i].cha;
		}
	}
	memset(dp,-1,sizeof(dp));
	dp[0][xx]=0;
	for(register int i=1;i<=n;i++){
		for(register int j=0;j<=50045;j++){
			if(dp[i-1][j]==-1&&dp[i-1][j-fr[i].cha]==-1)continue;
			else if(dp[i-1][j-fr[i].cha]!=-1){
				dp[i][j]=max(dp[i-1][j],dp[i-1][j-fr[i].cha]+fr[i].a);
			}
			else {
				dp[i][j]=dp[i-1][j];
			}
		}
	}
	if(dp[n][xx]==0)cout<<-1<<endl;
	else cout<<dp[n][xx]<<endl;
}
```

---

