# Madoka and Laziness

## 题目描述

Madoka has become too lazy to write a legend, so let's go straight to the formal description of the problem.

An array of integers $ a_1, a_2, \ldots, a_n $ is called a hill if it is not empty and there is an index $ i $ in it, for which the following is true: $ a_1 < a_2 < \ldots < a_i > a_{i + 1} > a_{i + 2} > \ldots > a_n $ .

A sequence $ x $ is a subsequence of a sequence $ y $ if $ x $ can be obtained from $ y $ by deletion of several (possibly, zero or all) elements keeping the order of the other elements. For example, for an array $ [69, 1000, 228, -7] $ the array $ [1000, -7] $ is a subsequence, while $ [1] $ and $ [-7, 1000] $ are not.

Splitting an array into two subsequences is called good if each element belongs to exactly one subsequence, and also each of these subsequences is a hill.

You are given an array of distinct positive integers $ a_1, a_2, \ldots a_n $ . It is required to find the number of different pairs of maxima of the first and second subsequences among all good splits. Two pairs that only differ in the order of elements are considered same.

## 说明/提示

In the first test case there are 3 possible pairs: $ (3, 4) $ , $ (2, 4) $ , $ (1, 4) $ . And they are achieved with the following partitions: $ [1, 2, 3], [4] $ ; $ [4, 3], [1, 2] $ ; $ [1], [2, 4, 3] $

## 样例 #1

### 输入

```
4
1 2 4 3```

### 输出

```
3```

## 样例 #2

### 输入

```
8
2 12 13 7 14 6 11 8```

### 输出

```
4```

## 样例 #3

### 输入

```
7
9 5 3 10 2 6 8```

### 输出

```
0```

## 样例 #4

### 输入

```
8
8 6 10 9 1 5 2 14```

### 输出

```
0```

# 题解

## 作者：I_am_Accepted (赞：11)

### Analysis

诈骗题：发现**必然有一个峰值是全局最大值**（位置设为 $x$），所以最终答案小于 $n$。

我们约定**另一个峰值在最大值之右**（位置设为 $y$）（之左的情况 reverse 序列再做一遍）。那我们要做的就是：

1. 将 $[1,x]$ **分解成两个递增序列**，让不包含 $x$ 位置的序列右端值最小（贪心）。

2. 将 $[y,n]$ **分解成两个递减序列**，同上方贪心让序列左端值最小。

3. 将 $[x,y]$ **分解成（一个递减、一个递增）两个序列**，必须保证 $a_x$ 在递减序列、$a_y$ 在递增序列里。

![](https://cdn.luogu.com.cn/upload/image_hosting/58zy3td8.png)

步骤 $1,2$ 可以用简单的线性 DP 解决（记得将步骤 $2$ 的 DP 数组计算到 $x+1$，并保存）。

步骤 $3$ 接上步骤 $1$ 序列的末尾，从 $x$ 向右出发 DP，保存（其实就是有初始值的 CF1144G）。

然后枚举 $y\in[x+1,n]$，用步骤 $2,3$ 的 DP 结果判断是否能接上，统计答案即可。

### Code

[Link](https://codeforces.com/contest/1647/submission/152448488)

```cpp
//Said no more counting dollars. We'll be counting stars.
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define For(i,j,k) for(int i=j;i<=k;i++)
#define Rof(i,j,k) for(int i=j;i>=k;i--)
#define ckmx(a,b) a=max(a,b)
#define ckmn(a,b) a=min(a,b)
#define N 500010

const int inf=1e9+7;
int n,a[N],mx=1,ans=0,f[N][2],g[N],h[N];
void solve(){
	g[1]=0;
	For(i,2,mx){
		g[i]=inf;
		if(a[i-1]<a[i]) ckmn(g[i],g[i-1]);
		if(g[i-1]<a[i]) ckmn(g[i],a[i-1]);
	}
	if(g[mx]==inf) return ;
	int sta=g[mx];
	h[n]=0;
	Rof(i,n-1,mx+1){
		h[i]=inf;
		if(a[i+1]<a[i]) ckmn(h[i],h[i+1]);
		if(h[i+1]<a[i]) ckmn(h[i],a[i+1]);
	}
	f[mx][0]=0,f[mx][1]=sta;
	For(i,mx+1,n){
		f[i][0]=0,f[i][1]=inf;
		if(a[i-1]<a[i]) ckmx(f[i][0],f[i-1][0]);//uu
		if(a[i-1]>a[i]) ckmn(f[i][1],f[i-1][1]);//dd
		if(f[i-1][1]<a[i]) ckmx(f[i][0],a[i-1]);//du
		if(f[i-1][0]>a[i]) ckmn(f[i][1],a[i-1]);//ud
	}
	For(i,mx+1,n) if(f[i][0]>h[i]) ans++;	
}
signed main(){IOS;
	cin>>n;
	For(i,1,n) cin>>a[i];
	For(i,1,n) if(a[mx]<a[i]) mx=i;
	solve();
	mx=n+1-mx;
	reverse(a+1,a+1+n);
	solve();
	cout<<ans<<endl;
return 0;}
```

---

## 作者：周子衡 (赞：11)

显见全部 $a_i$ 中的最大值一定是最后两个最大值中的一个，我们只需要计算另一个最大值的可能取值即可。

假设全部 $a_i$ 中的最大值为 $a_k$，我们现在要判断某个 $a_p$ 能不能成为另一个最大值。不失一般性，我们可以假定 $p < k$（$p > k$ 的情形可以类似地计算）。此时原序列被自然地分成三段：$[1,p)$，$(p,k)$ 以及 $(k,n]$，我们需要分别将这三段中的元素分配给两个序列。

首先来考察 $[1,p)$ 这段元素的分配。可以发现，我们希望尽可能使得这些元素中和 $k$ 同一个序列的最大元素尽可能小，这样最有可能构造出符合条件的序列。可以考虑 DP，设 $f(i)$ 表示将 $a_1\sim a_i$ 划分为两个上升序列，其中不以 $a_i$ 结尾的序列的结尾元素的最小值。转移的时候，如果 $a_i < a_{i+1}$，我们用 $f(i)$ 更新 $a_{i+1}$；如果 $f(i) < a_{i+1}$，我们用 $a_i$ 更新 $a_{i+1}$。

$(k,n]$ 这段元素的分配也类似，我们希望尽可能使得这些元素中和 $p$ 同一个序列的最大元素尽可能小。可以仿照上面的算法同样 DP。注意由于 $k$ 是固定的，所求出来的最大元素也是不变的，下面记为 $a_v$。

接下来解决 $(p,k)$ 之间的元素分配。我们需要找到一个下降序列，所有元素大于 $a_v$、小于 $a_p$；另一个上升序列所有元素大于 $f(p)$、小于 $a_k$。由于 $a_k$ 是原序列的最大值，“小于 $a_k$”这个条件无需考虑。我们再来设计 DP：用 $g(i)$ 表示将 $a_i\sim a_k$ 划分为一个下降序列、一个上升序列，其中下降序列的末尾元素大于 $a_v$，且 $i$ 属于下降序列时，上升序列开头元素的最大可能值；$h(i)$ 表示将 $a_i\sim a_k$ 划分为一个下降序列、一个上升序列，其中下降序列的末尾元素大于 $a_v$，且 $i$ 属于上升序列时，下降序列开头元素的最小可能值。判断是否有 $f(i) < g(i)$ 即可。这两个 DP 值可以从大到小依次递推计算，具体细节略去。

总时间复杂度 $O(n)$。

```cpp
#include<cstdio>
#include<algorithm>

using namespace std;

const int INF=1e9+1;

int a[1000000],f[1000000][2],g[1000000],h[1000000];

int main()
{
	int n=0;scanf("%d",&n);for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	int k=1;for(int i=2;i<=n;i++)if(a[i]>a[k])k=i;
	f[0][0]=f[n+1][1]=-INF,a[0]=a[n+1]=-INF;
	for(int i=1;i<=k;i++)
	{
		f[i][0]=INF;
		if(a[i]>f[i-1][0])f[i][0]=min(f[i][0],a[i-1]);
		if(a[i]>a[i-1])f[i][0]=min(f[i][0],f[i-1][0]);
	}
	for(int i=n;i>=k;i--)
	{
		f[i][1]=INF;
		if(a[i]>f[i+1][1])f[i][1]=min(f[i][1],a[i+1]);
		if(a[i]>a[i+1])f[i][1]=min(f[i][1],f[i+1][1]);
	}
	//for(int i=1;i<=k;i++)printf("%d ",f[i][0]);puts("");
	//for(int i=k;i<=n;i++)printf("%d ",f[i][1]);puts("");
	
	int ans=0;
	g[k]=-INF,h[k]=f[k][1];
	for(int i=k-1;i>=1;i--)
	{
		g[i]=-INF,h[i]=INF;
		if(a[i]<a[i+1])h[i]=min(h[i],h[i+1]);
		if(a[i]>h[i+1])g[i]=max(g[i],a[i+1]);
		if(a[i]>a[i+1])g[i]=max(g[i],g[i+1]);
		if(a[i]<g[i+1])h[i]=min(h[i],a[i+1]);
		if(g[i]>f[i][0])ans++;
	}
	g[k]=-INF,h[k]=f[k][0];
	for(int i=k+1;i<=n;i++)
	{
		g[i]=-INF,h[i]=INF;
		if(a[i]<a[i-1])h[i]=min(h[i],h[i-1]);
		if(a[i]>h[i-1])g[i]=max(g[i],a[i-1]);
		if(a[i]>a[i-1])g[i]=max(g[i],g[i-1]);
		if(a[i]<g[i-1])h[i]=min(h[i],a[i-1]);
		if(g[i]>f[i][1])ans++;
	}
	printf("%d",ans);
}
```

**后记**

~~为啥 CF Div.2 F 的质量比 Div.1 F 还要高了~~

---

## 作者：longlinyu7 (赞：9)

# 题目分析
把一个序列分割成相对位置不变的两个序列，求这两个序列的**峰**的不同组合方案数。

~~说了跟说了是的。~~

## 解题思路
可以先去看看这道题 [CF1144G](https://www.luogu.com.cn/problem/CF1144G)，~~把这道题通过了之后说不定就会写了。~~

再来观察题目，可以发现，不管怎么分割，**必然有一个子序列的峰是整个序列的最大值**，因为你不可能把这个最大值丢了不要。

那么我们只需要考虑另一个子序列的峰就好了，显而易见，答案一定小于 $n$。

在整个序列中找到最大值 $mx$，枚举其他的数 $y$，判断其能否作为另一个序列的峰。

**先约定 $y$ 位于 $mx$ 右边。** 

至于在左边的情况，将序列反转一下就好了。~~别问为什么是右边。~~

如下图所示：
![](https://cdn.luogu.com.cn/upload/image_hosting/s2ifj7zq.png)

分为三个部分，其实前后两个部分实质是一样的，可以归为一类。

在做过 [CF1144G](https://www.luogu.com.cn/problem/CF1144G) 这道题后你就会恍然大悟。

- 左半部分是两个递增的线段，我们需要红的那个递增序列最右端的值尽量小，这样好让 $y$ 合法。
  
- 右半部分同理，需要让红的那个递减序列最左端的值尽量小。

- 写过 [CF1144G](https://www.luogu.com.cn/problem/CF1144G) 的话，中间部分应该难不倒你了。但是还有条件，需要钦定$mx$ 在黑色的递减序列，$y$ 在红色的递增序列上。

### 设计状态

- 设 $f1_{i} $表示第 $i$ 项位于黑线的递增序列，**红线的递增序列最右边的数的最小值是多少。**
  
- 设 $f2_{i} $ 表示第 $i$ 项位于黑线的递减序列，**红线的递减序列最左边的数的最小值是多少。**

   
- - 设 $g_{i,0}$ 表示第 $i$ 项位于递增序列，**递减序列右端的最大值是多少。**

  - 设 $g_{i,1}$ 表示第 $i$ 项位于递减序列，**递增序列右端的最小值是多少。**

### 状态如何转移

- 先分析 $f1_i$ 是如何转移的。因为我们钦定了$a_i$ 是属于黑色的递增序列的，转移时考虑 $a_{i-1}$ 的情况，是属于黑色还是红色的递增序列。
  - 如果 $a_{i-1} < a_{i}$ ，$a_{i-1}$ 就也可以属于黑色的递增序列，符合 $f1_{i-1}$ 的定义，那么 $f_i$ 就可以由 $f1_{i-1}$ 转移过来。
  - 如果 $f1_{i-1} <a_i$ ，$a_{i-1}$ 就可以属于红色的递增序列，那么 $f_i$ 的值就可以由 $a_{i-1}$ 转移而来。

**注意：时刻记住 $f1_i$ 维护的是红色递增序列最右端的最小值，而不是黑色的。**
- $f2_i$ 的转移与 $f1_i$ 本质相同，不做过多分析。

- 考虑 $g_{i,0}$ 的转移，**请再次回顾一遍 $g_{i,0}$ 的定义。**

  -  如果 $a_{i-1} < a_{i}$，$a_{i-1}$ 就可以属于递增序列，那么 $g_{i,0}$ 就可以由 $g_{i-1,0}$ 转移而来。
  -  如果 $g_{i-1,1}<a_{i}$，即 $a_{i-1}$ 属于递减序列，且此时递增序列的最右端的最小值小于 $a_{i}$，$a_{i}$ 是合法的。那递减序列做右端的最大值就可以由 $a_{i-1}$ 转移而来。

- $g_{i,1}$ 的转移同理。

#### 注意细节
1. 注意转移方程的初始值，看情况设为**无穷大**或着**无穷小。**

2. 在三个转移方程都处理完之后，需要对在 $mx$ 右边的每个数都判断一边是否能成为另一个峰。观察发现，在中间和左右边两端，黑色的递减序列将其连接起来了，没有拐弯，那就用 $g_{i,0}$ 和 $f2_{i}$ 来判断。

3. 反转序列之后最大值需要重新找。

## Code


```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD=1e9+7;
const int N=5e5+10;
const int inf=1e9;
const int M=1005;
int f1[N],f2[N],g[N][2];
// f1[i] 表示 第i项在一个递增序列中，另一个递增序列的最小值
// f2[i] 表示 第i项在一个递减序列中，另一个递减序列的最小值

// g[i][0] 表示 第i项在一个递增序列中，另一个递减序列的最大值 
// g[i][1] 表示 第i项在一个递减序列中，另一个递增序列的最小值
int n,a[N],mx,ans;
void solve(){
	mx=0;
	for(int i=1;i<=n;i++)if(a[mx]<a[i])mx=i;
	// cout<<mx<<"\n";
	f1[0]=-inf;
	// 算左半部分的递增序列 
	for(int i=1;i<=mx;i++){
		f1[i]=inf;
		if(a[i-1]<a[i]){  // a[i-1]在 一个递增序列中 
			f1[i]=min(f1[i],f1[i-1]);
		}
		if(f1[i-1]<a[i]){ // a[i-1] 在另一个递增序列中 
			f1[i]=min(f1[i],a[i-1]);
		}
	}
	// 算右半部分的递减序列 
	f2[n+1]=inf;
	for(int i=n;i>=mx;i--){
		f2[i]=inf;
		if(a[i+1] <a[i]) f2[i]=min(f2[i],f2[i+1]);
		if(f2[i+1]<a[i]) f2[i]=min(f2[i],a[i+1]);
	}
	// a[mx] 肯定是在递减序列里的， 
	g[mx][0]=-inf ,g[mx][1]= f1[mx]; // 这样赋值是为了转移 
	for(int i=mx+1;i<=n;i++){
		g[i][0]=-inf,g[i][1]=inf; // 赋初始值 
		if(a[i-1]<a[i])g[i][0]=max(g[i][0],g[i-1][0]); // a[i-1] 属于递增序列的 
		if(a[i-1]>a[i])g[i][1]=min(g[i][1],g[i-1][1]);
		if(g[i-1][1]<a[i]) g[i][0]=max(g[i][0],a[i-1]);//a[i-1]属于递减序列的，必须合法 
		if(g[i-1][0]>a[i]) g[i][1]=min(g[i][1],a[i-1]); 
	} 
	
	for(int i=mx+1;i<=n;i++){
		// 当第i项属于递增序列时，检查递减序列的最大值 
		if(g[i][0] >f2[i])ans++;
	} 
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}	
	solve();
	reverse(a+1,a+1+n);
	solve();
	cout<<ans;
	return 0;
} 
```

## 后记
~~废了一个多小时，终于写完了。~~

如果有什么错误或疑问还请指出。

希望分享一下做题的经验与想法，这道题不知道套路的话还是挺难想的。

~~如果觉得写的好要个赞不过分吧。~~

---

## 作者：Cry_For_theMoon (赞：6)

你小圆怎么 Div2 F 撞原 Div3 G 啊（恼）。我怎么半年前就做过场上还是不会啊（雾）

如果大家这个题有点困难可以先去学习核心部分的解法 [CF1144G](https://www.luogu.com.cn/problem/CF1144G) ，然后很快就懂了。

题意有点绕。就是说定义一个好的序列为先严格上升再严格下降。称最大值为拐点，记作 $\alpha$。

然后给你一个 $n$ 个数互不相同的数列 $a$，让你拆成两个非空的好序列，记两个序列的拐点为 $\alpha_1\lt \alpha_2$，然后就是问你 $(\alpha_1,\alpha_2)$ 有多少种可能。

------------

这个题诈骗性质很强，因为你注意到 $\alpha_2$ 必定是 $a$ 数组最大值。所以答案不超过 $n-1$：我们只用考虑暴力枚举 $\alpha_1$ 并判断是否有拆分方式即可。

然后不失一般性我们可以设 $\alpha_1$ 的位置在最大值的右边（左边的话可以翻转数列再做一遍）。

这样整个数列应该被分成三部分：最左边的部分被拆成两个上升子序列，中间部分被拆成一个下降和一个上升的子序列，最右边的部分被拆成两个下降子序列。

这三个问题本质上是相近的，如果做过 CF1144G 这样的问题应该就立马会做了（除了我）。

我们就来分开来考虑三个问题好了：给定一个序列，能否拆成两个上升子序列（第一部分）；或者一个上升一个下降的子序列（第二部分）；或者两个下降子序列（第三部分）。

注意到第一部分和第三部分本质是相同的。我们只考虑第一部分和第二部分怎么做。

这部分很有趣，解决这类“二择”问题，关键是我们发现每个元素必定属于两个上升序列的一个，而上升/下降序列的话，我们只关注结尾的值，所以有这样一个想法：设 $f(1,i)$ 是前 $i$ 个元素，第 $i$ 个元素被划分进了第一个序列，此时第二个序列结尾的最优秀值（如果第二个序列是下降的，就是结尾的最大值；如果第二个序列是上升的，就是结尾的最小值。）；同理 $f(2,i)$ 是前 $i$ 个元素，第 $i$ 个元素被划分进了第二个序列，此时第二个序列结尾的最优秀值。

然后转移的思想是这样的：考虑 $i-1$ 和 $i$，因为要么 $i-1$ 和 $i$ 划分进同一个序列，要么不在同一个序列。对于第一种情况，$f(i)$ 直接继承 $f(i-1)$ 就好了；对于第二种情况，$f(i)$ 就直接从 $a_{i-1}$ 继承。

另外我们注意到，对于第一部分和第三部分 $f(1,i)=f(2,i)$，所以这里我们就直接记作 $f(i)$ 了。

然后考虑把左中右三段拼接起来。左和中的拼接是容易的，我们只是把左边 $f(maxpos)$ 的信息作为中间一段的 $f$ 数组的初始化。而中和右的拼接实质上就是枚举 $\alpha_2$ 的位置 $pos$，然后判断其合法性，就是中间的 $f(2,pos)$ 要大于右边的 $f(pos)$。

这样，时间复杂度是 $O(n)$ 的！

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
using namespace std;
const int MAXN=5e5+10,INF=2e9;
int n,ans,a[MAXN];
int f1[MAXN],f2[MAXN],g[2][MAXN];
void solve(){
    int maxpos=1;rep(i,2,n)if(a[i]>a[maxpos])maxpos=i;
    f1[0]=-INF;
    rep(i,1,maxpos){
        f1[i]=INF;
        if(a[i-1]<a[i])f1[i]=min(f1[i],f1[i-1]);
        if(f1[i-1]<a[i])f1[i]=min(f1[i],a[i-1]);
    }
    f2[n+1]=-INF;
    per(i,n,maxpos){
        f2[i]=INF;
        if(a[i+1]<a[i])f2[i]=min(f2[i],f2[i+1]);
        if(f2[i+1]<a[i])f2[i]=min(f2[i],a[i+1]);
    }
    g[0][maxpos]=f1[maxpos];
    g[1][maxpos]=-INF;
    rep(i,maxpos+1,n){
        g[0][i]=INF;g[1][i]=-INF;
        if(a[i-1]>a[i])g[0][i]=min(g[0][i],g[0][i-1]);
        if(g[1][i-1]>a[i])g[0][i]=min(g[0][i],a[i-1]);
        if(a[i-1]<a[i])g[1][i]=max(g[1][i],g[1][i-1]);
        if(g[0][i-1]<a[i])g[1][i]=max(g[1][i],a[i-1]);
    }
    rep(i,maxpos+1,n){
        if(g[1][i]>f2[i])ans++;
    }
}
int main(){
    cin>>n;
    rep(i,1,n)cin>>a[i];
    solve();
    reverse(a+1,a+1+n);
    solve();
    cout<<ans;
    return 0;
}
```

---

