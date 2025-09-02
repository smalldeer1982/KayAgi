# [JOI 2021 Final] とてもたのしい家庭菜園 4 (Growing Vegetables is Fun 4)

## 题目描述

给定一个长为 $N$ 的序列 $A_i$，你可以进行若干次操作：

- 选定一个区间 $[L,R]$，让这个区间里的数加 $1$。

设经过这若干次操作后的序列为 $B_i$，那么你需要让 $B_i$ 满足下面这个要求：

- 存在一个整数 $k \in [1,N]$，满足对于子序列 $A_1=\{B_1,B_2,\cdots,B_k\}$ 为严格递增序列，对于子序列 $A_2=\{B_k,B_{k+1},\cdots,B_N\}$ 为严格递减序列。

你想知道最少需要多少次操作才能满足上面这个要求。

## 说明/提示

#### 样例 1 解释

- 对 $[2,5]$ 进行操作，序列变为 $\{3,3,3,4,2\}$。
- 对 $[2,3]$ 进行操作，序列变为 $\{3,4,4,4,2\}$。
- 对 $[3,3]$ 进行操作，序列变为 $\{3,4,5,4,2\}$。

#### 样例 2 解释

序列已经满足要求，不需要操作。

#### 样例 3 解释

对区间 $[1,1]$ 或 $[2,2]$ 进行操作都可。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（40 pts）：$N \le 2000$。
- Subtask 2（60 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le N \le 2 \times 10^5$，$1 \le A_i \le 10^9$。

#### 说明

翻译自 [The 20th Japanese Olympiad in Informatics Final Round A とてもたのしい家庭菜園 4 的英文翻译 Growing Vegetables is Fun 4](https://www.ioi-jp.org/joi/2020/2021-ho/2021-ho-t1-en.pdf)。

## 样例 #1

### 输入

```
5
3 2 2 3 1```

### 输出

```
3```

## 样例 #2

### 输入

```
5
9 7 5 3 1```

### 输出

```
0```

## 样例 #3

### 输入

```
2
2021 2021```

### 输出

```
1```

## 样例 #4

### 输入

```
8
12 2 34 85 4 91 29 85```

### 输出

```
93```

# 题解

## 作者：LZH_LOVE_ZRG (赞：24)

分析题面可知，这是一道序列操作题。

因为 $A$ 数组前半段严格递增，后半段严格递减，

且只有加法一种操作，

所以我们可以使用差分思想。

记 $B$ 为 $A$ 的差分数组，我们接下来就用 $B$ 进行一系列操作。

显而易见，这道题我们需要枚举界点，因此我们要定义：

+ $x$ 数组，$x_i$ 表示从 $1$ ~ $i$ 严格递增所需的步数；
+ $y$ 数组，$y_i$ 表示从 $i+1$ ~ $n$ 严格递减所需的步数。

那么可知： $ans \gets \min\limits _{1\le i\le n}\{{\max(x_i,y_{i+1})}\}$。

接下来的问题是，如何处理 $x$ 与 $y$？

显而易见每次的 $x$ 都是一个前缀的形式，而 $y$ 是一个后缀的形式。

$x_i$ 的赋值有 $2$ 种情况：

1. $b_i\le0$，即对答案有贡献（需要加才能符合严格递增），$x_i\gets x_{i-1}+\left\vert b_i\right\vert+1$；
2. $b_i>0$，即对答案没有贡献，$x_i\gets x_{i-1}$。

$y_i$ 同理，这里就不赘述了。

代码：

```
#include<bits/stdc++.h>
using namespace std;
const int N=200010;
int a[N],b[N];
long long x[N],y[N];
int main(){
    int n; cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        b[i]=a[i]-a[i-1];
    }
    for(int i=2,j=n;i<=n;i++,j--){
        x[i]=(b[i]<=0?x[i-1]-(b[i]-1):x[i-1]);
        y[j]=(b[j]>=0?y[j+1]+(b[j]+1):y[j+1]);
    }
    long long ans=LONG_LONG_MAX;
    for(int i=1;i<=n;i++)
        ans=min(ans,max(x[i],y[i+1]));
    cout<<ans;
    return 0;
}

```

---

## 作者：苏联小渣 (赞：10)

## 题目大意

给定序列 $a$，每次可选择区间 $[L,R]$ 加一，求最少操作次数使得 $\exists k \in[1,n]$，

- $a_1< a_2 <...< a_k$ ；

- $a_k > a_{k+1} > ... > a_n$。

### 前置知识 - 差分

差分，相当于前缀和的逆运算。我们定义一个差分数组 $f$，满足如下性质：

 - $f_i=a_i-a_{i-1}$
 
 - $a_i=\sum_{j=1}^if_j$
 
 - 将区间 $[l,r]$ 加上 $k$，相当于 $f_l  \gets f_l+k,f_{r+1} \gets f_{r+1}-k$

## 分析

区间加，且只能加 $1$，且分析递增递减性质，考虑差分。

定义一个差分数组 $d_i=a_i-a_{i-1}$
。

则题目要求满足的条件就转化为：$\exists k \in[1,n]$，

- $d_1,d_2...d_k > 0$；

- $d_{k+1},d_{k+2}...d_n < 0$。

传统差分到此为止仿佛就没法做下去了，而本题就妙在于采用一种类似于**动态规划**的差分做法。

由于本题的 $k$ 并不是固定的，而是选择最优的，所以考虑定义 $f_{i\in[1,n],j\in[0,1]}$。其中：

- $f_{i,0}$ 表示让 $a_1...a_i$ 严格递增的方案数；

- $f_{i,1}$ 表示让 $a_i...a_n$ 严格递减的方案数。

再推转移方程，以 $f_{i,0}$ 为例：

前文说过，如果两数差为正，则一定满足递增。那么，就可以推出第一个式子：

$$f_{i,0}=f_{i-1,0},d_i>0$$

如果不为正，就需**加上**两数差的**绝对值**，此时已经保证了单调递增。若须严格递增，则还要加上 $1$，保证两数差为正。这一步操作类似于 [P4552](https://www.luogu.com.cn/problem/P4552)，也相当于一道双倍经验题。

这样，就推出了第二个式子：

$$f_{i,0}=f_{i-1,0}-d_i+1,d_i \le 0$$

两式结合，就推出了本题的第一个方程。

对于递减，其实可以转化为从 $n$ 开始，保证 $a_n>a_{n-1}>...>a_k$，这样也转化为了和递增差不多的方程。

最后一步，从 $1$ 到 $n$ 枚举中间点 $k$，取 $\max (f_{i,0},f_{i+1,1})$ 的最小值。

最后提醒一句：**一定要记得开 long long**。

### Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, s=1e18, a[200010], d[200010];
int f[200010][3];
signed main(){
	scanf ("%lld", &n);
	for (int i=1; i<=n; i++){
		scanf ("%lld", &a[i]);
		d[i] = a[i] - a[i-1];
	}
	for (int i=2; i<=n; i++){
		if (d[i] > 0) f[i][0] = f[i-1][0];
		else f[i][0] = f[i-1][0] - d[i] + 1;
	}
	for (int i=n; i>=2; i--){
		if (d[i] < 0) f[i][1] = f[i+1][1];
		else f[i][1] = f[i+1][1] + d[i] + 1;
	}
	for (int i=1; i<=n; i++){
		s = min(s, max(f[i][0], f[i+1][1]));
	}
	printf ("%lld\n", s);
	return 0;
}

```

---

## 作者：iMya_nlgau (赞：10)

记 $A$ 的差分序列为 $B$，将区间 $\left[L,R\right]$ 内的数加 $1$ 等价于将 $B_L$ 加 $1$ 并将 $B_{R+1}$ 减 $1$，$\left\{A_1,A_2,\cdots ,A_k\right\}$ 为严格递增序列，$\left\{A_k,A_{k+1},\cdots ,A_n\right\}$ 为严格递减序列等价于 $\forall 2\leq i\leq k,B_i>0$ 并且 $\forall k< i\leq n,B_i<0$。

记

$$f_k=\sum\limits_{2\leq i\leq k}(B_i-1)[B_i\leq0]$$

$$g_k=\sum\limits_{i\leq k\leq n}(B_i+1)[B_i\geq0]$$

然后对于枚举到的 $k$，需要的最少操作次数就是 $\max(|f_k|,|g_{k+1}|)$，所以最终答案就是 $\min\limits_{1\leq k\leq n}\{\max(|f_k|,|g_{k+1}|)\}$。

时间复杂度 $O(n)$。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int maxn=2e5+10;
int n,a[maxn],b[maxn];
ll f[maxn],g[maxn];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=2;i<=n;i++) b[i]=a[i]-a[i-1];
	for(int i=2;i<=n;i++) f[i]=b[i]<=0?f[i-1]-b[i]+1:f[i-1];
	for(int i=n;i>=2;i--) g[i]=b[i]>=0?g[i+1]+b[i]+1:g[i+1];
	ll ans=0x3f3f3f3f3f3f3f3f;
	for(int k=1;k<=n;k++) ans=min(ans,max(f[k],g[k+1]));
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：STL_qwq (赞：8)

原题链接：**[传送门](https://www.luogu.com.cn/problem/P7404)**

------------
### 题目大意：

这道题大致是说，给你一个 $n$ 个数的序列 $A_i$，你可以让一个区间里的每一个数加上 $1$。现在让你找到一个中间节点 $k$，对于子序列 $A_1=\{A_1,A_2,\cdots,A_k\}$ 为严格递增序列，对于子序列 $A_2=\{A_k,A_{k+1},\cdots,A_n\}$ 为严格递减序列。问你实现这个状态找哪个中间节点所需的加法操作最少。

------------
### 分析：

这道题我们可以用 **DP** 的思想来想。

我们要用一个 $sx$ 数组，**来存放每一个元素与它前面的每一个元素构成升序序列所需的操作次数。**

降序同理。我们用 $jx$ 数组**来存放每一个元素与它后面的每一个元素构成降序序列所需的操作次数。**

那么应该怎么处理这两个数组呢？

我们不妨先让：$sx_0=0$，$js_n=0$。

然后对于序列里的每一个元素，我们发现：

对于升序序列而言，一个元素的状态应是由前一个的状态转移而来的，而且还要加上比前一个大最少需要的操作数。如果 $a_i<=a_i-1$，那么状态转移方程为：

$sx_i=sx_{i-1}+(a_{i-1}-a_{i}+1)$

否则，直接继承前一个元素的状态。

自然的，降序序列中，一个元素的状态应是由后一个的状态转移而来的，而且还要加上比后一个大最少需要的操作数。如果 $a_i<=a_i+1$，那么状态转移方程为：

$jx_i=jx_{i+1}+(a_{i+1}-a_{i}+1)$

否则，直接继承前一个元素的状态。

处理完之后，我们就跑一遍数组，枚举 $k$ 点 ，用一个变量 $ans$ 寻找 $\max(jx_k,sx_k)$ 的最小值。然后输出即可。

------------
### 注意事项：
1. 要开 **long long**；
2. $ans$ 初始化一定要够大，否则有几个点会被卡。

------------
### **AC 代码：**

```cpp
#include<cstdio>
#include<iostream>
#define int long long

using namespace std;

int n,a[200005],sx[200005],jx[200005];
int ans=0x3f3f3f3f3f3f3f3f; 
//ans一定要够大。

inline int read()//快读。 
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9')
    {if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9')
    {x=x*10+ch-48;ch=getchar();}
	return x*f;
}

signed main(){
	
	n=read();
	
	for(int i=1;i<=n;i++) a[i]=read();
	
	for(int i=2;i<=n;i++){
		sx[i]=sx[i-1];
		if(a[i-1]>=a[i]) sx[i]+=a[i-1]-a[i]+1;
	}//处理每个点成为上升序列所需操作数。
	
	for(int i=n-1;i>=0;i--){
		jx[i]=jx[i+1];
		if(a[i+1]>=a[i]) jx[i]+=a[i+1]-a[i]+1;
	}//处理每个点成为下降序列所需操作数。 
	
	for(int i=1;i<=n;i++) 	
        ans=min(ans,max(sx[i],jx[i]));
        //找最小值，枚举中间节点。 
	
	printf("%lld",ans);//输出。 
	
	return 0;
}
```


 ### _Thanks for reading!_ 

---

## 作者：LEle0309 (赞：6)

### 差分好题……

差分，就是把数列相邻两项之差存进来，即 $ d_i=a_i-a_{i-1} $。

#### 差分有一个重要性质：

当把一个数组的一段区间加上一个数 $ x $ 时，如果挨个挨个修改，时间复杂度 $ O(n) $。

而差分数组的中间部分因为做差的两个数都同时增加了 $ x $，无需改变，此时只需要改变差分数组的首尾，即 $ d_l $ 加 $ x $，$ d_{r+1} $ 减 $ x $，时间复杂度 $ O(1) $。

所以，我们做题时一看到把一个区间同时加上一个数时，就可以试一试差分。
***
回到此题，数组要修改通过不断将**一段区间同时加上 $ 1 $ 后**（明显的差分），存在一个 $ k $ 且 $ k \in [1,N] $ 使得数组的前 $ k $ 个数**严格**递增，后 $ k $ 个数**严格**递减。

我们~~随手~~举出一个满足条件的数组：`1 2 3 2 1`

差分数组写出来：`1 1 1 -1 -1` 

很明显，差分数组满足**前半段为正，后半段为负**。

这里，我推荐两种做法：

法一：枚举差分数组后半段正数变负和前半段负数变正的修改次数，参见[同机房大佬的题解](https://www.luogu.com.cn/blog/878137/p7404-ti-xie)

法二：因为出现了两段，容易想到 two-pointer 做法。

上代码：

```
#include<iostream>
using namespace std;
const int maxn=2e5+7;
long long a[maxn],d[maxn],n,r,i,l,ans,D;//十年OI一场空，不开long long见祖宗
int main()
{
	cin>>n;l=1;r=n;
	for(i=1;i<=n;i++)cin>>a[i],d[i]=a[i]-a[i-1];//求差分数组
	while(l<r)//双指针
	{
		while(d[l]>0)l++;//找前半段的负数
		while(d[r]<0)r--;//找后半段的正数
		if(l>r)break;//注意
		D=min(-d[l]+1,d[r]+1);
                //改变区间[l,r]
                //d[l],d[r]配对修改，要改变能同时满足这两个数的最小值
		ans+=D;d[l]+=D;d[r]-=D;//ans加上D（D也是这一次修改的步数）
	}
	cout<<ans<<endl;//输出
	return 0;//完结撒花！
}
```

---

## 作者：water_three (赞：3)

#### 前置知识：

差分数组及 [P2367 语文成绩](https://www.luogu.com.cn/problem/P2367)。

#### 性质：
* 由上题和差分数组的基本概念我们可以得知：选定一个区间 $L$ 和 $R-1 $让这个区间里的数加 1，在差分数组里的**实质是将 $f_L$ 加 1 , $f_R$ 减 1**.

* 因为题目要求保持严格单调递增、减，所以最后差分数组中除 $f_1$ 外不能有 0.

因为题目要求一个 $k$ 使得 $a_1$ 到 $a_k$ 为严格升序排列，反应在差分数组中**表现为 $f_2$ 到 $f_k$ 均为正数**---所以在 $a_2$ 到 $a_k$ 中，后一个数总比前一个数大。

同理让 $k$ 使 $a_k$ 到 $a_n$ 为严格降序排列，需要使 **$f_k$ 到 $f_n$ 均为负数（不包含 $f_k$）**。

## 实现：
由此我们可以每次通过操作**选定一个区间 $L$ 和 $R$ 让这个区间里的数加1** ，最终要使得 $f_k$ 前面均为正数，$f_k$ 后面均为负数。

我们设 $A$ 为 $k$ （包括 $k$ ）以前的**非正数减 1** 的绝对值之和（**因为严格单调递增，所以不能为 0**），$B$ 为 $k$ 以后的**非负数加 1 **之和，因此很容易想出最少的操作次数就等于 $A$ 和 $B$ 中的最大值。

#### $k$ 的转移：
 那么，我们可以枚举当 $k$ 等于 1，2 到 $n$. 然后取操作次数最小值。
 * 当 $k$ 从 1 转移到 2 时，如果 **$f_2$** 为正数，那么 $k$ 右边的非负数和会减 $f_2$ 再减 1.

* 如果为 **0**，因为严格单调递增、减，所以 $k$ 右边的非负数和会减 1, 左边的非正数之和会加 1.

* 如果为**负数**，那么 $k$ 左边的非正数之和会加 $f_2$ 的绝对值，再加 1.

### 优化
* 对于输入本身就是严格递增或递减序列，我们可以直接输出 0.

* 当只有两个数时，如果两数相等，输出 1，否则输出 0.

#### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long A,B,pan1,pan2;//A为k左边负数个数，B为K右边正数个数。 
long long ans=1e20;//ans一定要初始化特别大 
const int n=2e5+10;
long long N,a[n],f[n];//f[]为方差 
int main() {
	cin>>N;
	for(long long i=1; i<=N; i++) {
		cin>>a[i];
		if(i!=1)f[i]=a[i]-a[i-1];
		if(f[i]>=0&&i!=1)B+=abs(f[i])+1;//预处理当k==1时f[1]右边有多少非负数
		if(i!=1&&a[i]>=a[i-1])pan2=0;//不是递减序列 
		if(i!=1&&a[i]<=a[i-1])pan1=0;//不是递增序列 
	}
	if(pan2||pan1) {//特判1 
		cout<<"0"<<endl;
		return 0;
	}
	if(N==2) {//特判2 
		if(a[1]==a[2]) {
			cout<<"1"<<endl;
			return 0;
		} else {
			cout<<"0"<<endl;
			return 0;
		}
	}
	ans=min(ans,max(A,B));//处理当k=1时操作步数max（A，B）；
	for(long long i=2; i<=N; i++) {//k的转移 
		if(f[i]>0) {
			B--;
			B-=abs(f[i]);
		} else if(f[i]==0) {
			B--;
			A++;
		} else {
			A+=abs(f[i]);
			A++;
		}
		ans=min(ans,max(A,B));
	}
	cout<<ans<<endl;
   return 0;
}
```

---

## 作者：liuyi0905 (赞：2)

### 题意：
可以每次将区间 $[L,R]$ 里的数加一，要你求出至少要多少次操作才能使 $a_1\sim a_k$ 严格递增，$a_k\sim a_n$ 严格递减。
### 思路：
当我们看到这一句话：
+ 选定一个区间 $[L,R]$，让这个区间里的数加 $1$。

这道题大概就是要用差分来解题了。

既然要用差分，得先找到目标状态下差分数组的要求。看完后发现：
+ 设 $A=\{sub_1,sub_2,⋯,sub_k\}$，则所有 $A_i$ 都为正整数。
+ 设 $A=\{sub_k,sub_{k+1},⋯,sub_n\}$，则所有 $A_i$ 都为负整数。

这时候，问题就转化为了使 $sub_1\sim sub_k$ 都为正，$sub_k\sim sub_n$ 都为负。

定义 $pr_i$ 为将 $sub_1\sim sub_i$ 全部变成正数的最小操作次数；$nx_i$ 为将 $sub_i\sim sub_n$ 全部变成负数的最小操作次数。就是一个前缀和与后缀和。

所以最后的答案变为了 $\min\limits_{1\le i\le n}\{\max(pr_i,nx_{i+1})\}$。

记住，在算前缀与后缀时要加一，应为仅仅将 $sub_i$ 变成 $0$ 是不够的，应为要严格递增递减。
### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,a[N],sub[N],pr[N],nx[N],mini=1e18;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],sub[i]=a[i]-a[i-1];
	for(int i=1;i<=n;i++)
		if(sub[i]>0)pr[i]=pr[i-1];
		else pr[i]=pr[i-1]-sub[i]+1;
	for(int i=n;i>=1;i--)
		if(sub[i]<0)nx[i]=nx[i+1];
		else nx[i]=nx[i+1]+sub[i]+1;
	for(int i=1;i<=n;i++)mini=min(mini,max(pr[i],nx[i+1]));
	cout<<mini;
	return 0;
}
```

---

## 作者：EthanOI (赞：2)

## 前言
这是一道差分的好题，我也是在[语文成绩](https://www.luogu.com.cn/problem/P2367)中认识了这个神奇的东西，自己误打误撞学会的，若有错误请指出
## 做法
每次将若干个连续的数加 $1$ ，这是差分非常明显的标志。在本题中，我们对 $k$ 进行枚举，计算使 $a_1<a_2<...<a_k$ 的最小步数 $dp1[i]$，以及使 $a_{k+1}>a_{k+2}>...>a_n$ 的最小步数 $dp2[i]$ ，最终计算 $\max {\min(dp1[i],dp2[i+1])}$ ，其中 $ 1\leqslant i\leqslant n$ 。
## $\mathcal{AC}\text{ }\mathcal{CODE}$

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, num[200010], sub[200010]; //num[i]为第i个数据，sub[i]=num[i]-num[i-1]（差分） 
ll dp1[200010], dp2[200010]; //x[i]表示num[1]至num[i]单调递增的最短步数，y[i]表示num[i]至num[n]单调递减的最短步数  
int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> num[i], sub[i] = num[i] - num[i - 1]; //差分  
	for (int i = 2, j = n; i <= n; i++, j--)
	{
        dp1[i] = (sub[i] <= 0 ? dp1[i - 1] - (sub[i] - 1) : dp1[i - 1]);
        dp2[j] = (sub[j] >= 0 ? dp2[j + 1] + (sub[j] + 1) : dp2[j + 1]);
    }
    ll _min = 0x3f3f3f3f3f3f3f3f;
    /*找出情况中的最小者*/
    for (int i = 1; i <= n; i++)
        _min = min(_min, max(dp1[i], dp2[i + 1]));
    cout << _min;
	return 0;
}
```
珍惜生命，请勿抄袭，棕名可不是开玩笑的！

完结撒花 （~~求管理员通过~~）

---

## 作者：Leaper_lyc (赞：0)

题目要求将序列 $A$ 分成两段，前半段递增，后半段递减。我们不知道这两半怎么分，所以只能枚举那个“断点”。

假设已知“断点”为 $k$，我们的情况如下：
- 设 $Q_k$ 表示将子序列 $A_1,A_i,...,A_k$ 变为递增序列所需操作的步数（前）。
- 设 $H_k$ 表示将子序列 $A_{k+1},A_{k+2},...A_N$ 变为递减序列所需操作的步数（后）。

易知 $ans=\min\{ans,\max\{Q_k,H_{k+1}\}\}$，其中 $k\in[1,n]$。

现在只剩 $Q_k$ 与 $H_k$ 的求法了。

为了方便观察每一个数之间的大小关系，我们先计算出序列 $A$ 的差分数组，记为 $C$（不懂差分？就是 $C_i=A_i-A_{i-1}$）。

分类讨论一下数与数之间的情况。
- 若 $C_i\le0$，则 $Q_i=Q_{i-1}-C_i+1$。
- 若 $C_i>0$，则 $Q_i=Q_{i-1}$。

$H_i$ 的算法也差不多，加减对调罢了。

于是 $ans=\min\{ans,\max\{Q_i,H_{i+1}\}\},i\in[1,n]$。

代码如下

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#define int long long

using namespace std;

#define maxn 200005

int n, a[maxn], c[maxn], f1[maxn], f2[maxn];
int ans = LONG_LONG_MAX;
signed main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        c[i] = a[i] - a[i - 1];
    }
    for (int i = 2, j = n; i <= n; i++, j--) {
        f1[i] = ((c[i] <= 0) ? (f1[i - 1] - (c[i] - 1)) : f1[i - 1]);
        f2[j] = ((c[j] >= 0) ? (f2[j + 1] + (c[j] + 1)) : f2[j + 1]);
    }
    for (int i = 1; i <= n; i++) {
        ans = min(ans, max(f1[i], f2[i + 1]));
    }
    cout << ans;
}
```

---

## 作者：_QWQ__QWQ_ (赞：0)

## 分析题意：
题意就是让前半段序列呈上升趋势，后半段呈下降趋势。

## 解题方法：
考虑差分出序列的高度。

$ x_i $ 表示以 $ i $ 为 $ k $ 的前半段需增加量。

$ y_i $ 表示以 $ i-1 $ 为 $ k $ 的后半段需增加量。

#### 从 $ 2 $ 开始枚举：

如果当前 $ d_i $ 为负数，说明它比前一个小，为了满足前半段呈上升趋势，需要增加 $ x_i $。


##### 从最后开始枚举：

如果当前 $ d_i $ 为正数，说明它比前一个大，为了满足后半段呈下降趋势，
~~给它前面的加，为了好统计，就加在它这里~~ $ y_i $ 增加。


注意：**十年 OI 一场空，不开 `long long` 见祖宗！答案大小能开多大开多大！**


## 附源码：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=200100;
long long n,sum=LONG_LONG_MAX-1,a[maxn],d[maxn],x[maxn],y[maxn];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		d[i]=a[i]-a[i-1];//求差分数组
	}
	for(int i=2;i<=n;i++){//从2枚举
		x[i]=x[i-1];
	    if(d[i]<=0){//如果为负数或0
	        x[i]+=-d[i]+1; //x[i]增加
	    }
	}
	for(int i=n;i>0;i--){//从最后面枚举
		y[i]=y[i+1];
	    if(d[i]>=0){//如果为整数或0
	        y[i]+=d[i]+1; //y[i]增加
	    }
	}
	for(int i=1;i<=n;i++){
	    sum=min(sum,max(x[i],y[i+1])); //最后答案取min(x[i],y[i+1])
	}
	cout<<sum;
	return 0;
}
```

---

## 作者：I_AK_IOI_and_NOI (赞：0)

## 题目大意

给定一个 A 数组，选定一个区间 $[L,R]$，让这个区间里的数加 1。问最少经过多少次操作，才能使得：前半段严格递增，后半段严格递减。

## 解题部分

首先声明一个 $B$ 数组为 $A$ 数组的差分序列。

即：$b_1 = a_1$，$b_i = a_i-a_{i-1}  (i \ne 1,i \le n)$。

定义 $x_i$ 为使得前 $i$ 项递增的最少步数。

$y_i$ 为使得后 $i$ 项递减的最少步数。

这样很明显可以看出来，答案就是： $ \max_{i \le n} a_i+b_{i+1} $

那么我们怎么去计算 $ x_i $ 和 $y_i$ 呢？

首先我们先来说说一下 $x_i$ 的计算方法，计算方法如下：

如果 $b_i \ge 0$ 时，此时已经是递增，对答案没有任何贡献，所以：

$ x_i = x_{i-1} $。

如果 $b_i \le 0$ 时，此时不是递增，对答案有贡献。

为了让数列变成递增，要让 $ b_i > 0 $，需要增加 $\left\vert b_i\right\vert+1$次。

得到：$x_i = x_{i-1}+\left\vert b_i\right\vert+1$ 也就是 $x_i = x_{i-1}-b_i+1$。

$ y_i $ 与 $ x_i $ 的求法差不多，如下：

如果，$b_i \le 0$ 那么 $ y_i=y_{i+1}$。

否则 $y_i=y_{i+1} + b_{i}+1$。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll a[200001],b[200001],n;
ll x[200001],y[200001];
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
	{
        cin>>a[i]; //读入 。
        b[i]=a[i]-a[i-1]; //计算差分数列 。
    }
    int j=n; 
    for(int i=2;i<=n;i++)
	{
		if(b[i]<=0) //刚才推的公式 。
		{
			x[i]=x[i-1]-(b[i]-1);
		}
		else
		{
			x[i]=x[i-1];
		}
    	if(b[j]>=0)
    	{
    		y[j]=y[j+1]+(b[j]+1);
    	}
        else
        {
        	y[j]=y[j+1];
        }
        j--;
    }
    long long ans=99999999999; //答案 。
    for(int i=1;i<=n;i++)
        ans=min(ans,max(x[i],y[i+1])); //统计答案 。
    cout<<ans;
    return 0;
}
```
注意 $ans$ 一定要开大，开小了过不去。

---

