# Skyscrapers (easy version)

## 题目描述

这题是 [CF1313C2](https://www.luogu.com.cn/problem/CF1313C2) 的简单版本。这个版本中 $1 \leq n \leq 1000$。

Berland要起摩天大厦了。所有的摩天大厦都在高速公路附近建。发展商买了 $n$ 块地准备建 $n$ 栋摩天大厦，一块地一栋。

当规划一间摩天大厦的时候，建筑师要考虑一些条件。

第一，因为每栋摩天大厦有不同的用途，所以每栋摩天大厦都有自己的层数限制，也就是说，这栋摩天大厦的高度不能超过给定的值 $m_i$。

第二，根据城市的建设规则，一栋摩天大厦不能同时在左右有比它高的摩天大厦。

如果规范地表示，让我们把地编上一个编号从 $1$ 到 $n$。那么如果在第 $i$ 块地的摩天大厦有 $a_i$ 层，那么我们需要保证 $1 \le a_i \le m_i$。另外，这里不可以有整数 $j$ 和 $k$ 满足 $j < i < k$ 并且 $a_j > a_i < a_k$。第 $j, k$ 块地并不需要与第 $i$ 块地相邻。

发展商想要使得每块地上摩天大厦的楼层数之和最大。也请帮他找出在**任意一个**最优状况中每个摩天大厦的高度。也就是，要让建筑师考虑的条件都符合，而且要使得每块地上摩天大厦的楼层数之和最大。

## 样例 #1

### 输入

```
5
1 2 3 2 1```

### 输出

```
1 2 3 2 1```

## 样例 #2

### 输入

```
3
10 6 8```

### 输出

```
10 6 6```

# 题解

## 作者：123456zmy (赞：5)

题意：  
给你一个数列 $m$，你要把其中的一部分数减少一些，使得存在至少一个 $k$ 使得 $m_1\le m_2\le…\le m_k\ge m_{k+1}\ge…\ge m_n$。输出操作后的数列。（$1\le n\le1000$）。
___
因为 $n$ 只开到了 $1000$，所以可以枚举 $k$，然后每次从 $k$ 向两边计算出答案，最后再把最优解输出即可。

代码：（$O(n^2)$）
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m[1001],ans1,ans,k,ansi,ans_[1001];
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&m[i]);
	for(int i=1;i<=n;i++)
	{
		k=m[i];
		ans=0;
		for(int j=i-1;j>0;j--)ans+=(k=min(m[j],k));
		k=m[i];
		for(int j=i+1;j<=n;j++)ans+=(k=min(m[j],k));
		if(ans+m[i]>ans1)ans1=ans+m[i],ansi=i;
	}
	k=m[ansi];
	for(int j=ansi-1;j>0;j--)ans_[j]=(k=min(m[j],k));
	k=m[ansi];
	for(int j=ansi+1;j<=n;j++)ans_[j]=(k=min(m[j],k));
	ans_[ansi]=m[ansi];
	for(int i=1;i<=n;i++)printf("%lld ",ans_[i]);
	return 0;
}
```

---

## 作者：BreakPlus (赞：2)

> 首先我们发现，最后的答案一定是一个不降序列加上一个不升序列。

这是大多数题解的第一句话，这篇题解重点来解释为什么。

首先我们把所有楼的高度看成一个曲线在变化。


假设一开始曲线不讲，我们来看（某哥们的 `` CF Rating`` ）变化：

![image.png](https://i.loli.net/2021/03/27/HFfl5pxtEVdviQm.png)

现在我们发现，满足这个要求：

> 另外，这里不可以有整数 $j$ 和 $k$ 满足 $j < i < k$ 并且 $a_j > a_i < a_k$
 。第 $j, k$ 块地并不需要与第 $i$ 块地相邻。
 
如果暂时下降，显然也是满足要求的。

![image.png](https://i.loli.net/2021/03/27/NYds3LfBKvhZ8EX.png)


如果再上升呢？

![image.png](https://i.loli.net/2021/03/27/aPVpu5oglvxKfXT.png)

红笔圈着的点，也就是下降到上升的中转点不满足要求了。

所以我们发现：不能出现 $\text{lower} \to \text{higher}$ 的趋势，即不能先下降再上升。

--------

如果一开始就下降，根据上一条，不能再上升了。

综上所述，最后的答案一定是一个不降序列加上一个不升序列。

我们可以枚举一个最高点 $k$ ，让左右两边分别呈上升和下降的趋势即可。变化 $a$ 数组的伪代码（ $k$ 为当前枚举的最高点）

```
for each i=k-1...1
	if a[i] > a[i+1] then a[i]=a[i+1]
for each i=k+1 .. n
	if a[i] > a[i-1] then a[i]=a[i-1]
```

然后这题就做完了。

---

## 作者：Night_sea_64 (赞：1)

~~奇怪，为啥 C2 题解满了而 C1 题解还有？？~~

题目描述中说对于每一个大楼，不能在左右有比它高的楼。我们用序列 $a$，$a_i$ 表示第 $i$ 个大楼的高度。则我们可以推出序列一定长这个样子：存在一个位置 $k\in [1,n]$，对于 $i\in[1,k)$，$a_i\le a_{i+1}$。对于 $i\in(k,n]$，$a_{i-1}\ge a_i$。则我们可以枚举那个 $k$，让 $k$ 左边的部分单调不降，右边的部分单调不升，同时让序列中每个元素都取到最大。这样总和最大的 $k$ 对应的序列即为答案。

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int a[1010],b[1010],ans[1010];
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    int maxn=0;
    for(int i=1;i<=n;i++)
    {
        b[i]=a[i];
        for(int j=i-1;j>=1;j--)b[j]=min(b[j+1],a[j]);
        for(int j=i+1;j<=n;j++)b[j]=min(b[j-1],a[j]);
        int sum=0;
        for(int j=1;j<=n;j++)sum+=b[j];
        if(sum>maxn)
        {
            maxn=sum;
            memcpy(ans,b,sizeof(ans));
        }
    }
    for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
    cout<<endl;
    return 0;
}
```

个人感觉还是挺简单的。

---

## 作者：Kevin_Mamba (赞：1)

发现较难的版本已经关闭题解通道了，不过我还是会讲讲正解。

## 题意

给定长度为 $n$ 的数组 $m$，构造数组 $a$，要求满足以下条件。

* $a_i\le m_i$。

* **不能同时存在** $j,k$ 满足 $1\le j\lt i\lt k\le n$ 且 $a_j> a_i$ 且 $a_k>a_i$。

* 要求 $\sum\limits_{i=1}^{n}a_i$ 最大。

求任意一组构造方案。

## $Solution$

条件一和条件三都比较普通，主要是条件二。

若**满足条件二**会存在的形状如下。

![](https://cdn.luogu.com.cn/upload/image_hosting/8lf3nlyc.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

所以合法的大概形状有以下四种。

![](https://cdn.luogu.com.cn/upload/image_hosting/efth2wif.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

整个图就用这些部分组成。为了不形成条件二的那种形状，选择构造**像山一样的形状（中间高，两边低）**。注意：**可以存在平地,也可以一直不上升或不下降**。如同下面这样（仅供参考，而且有些误差勿喷）。

![](https://cdn.luogu.com.cn/upload/image_hosting/abcv14nu.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

所以枚举山顶 $s$（包括首项和末项）。暴力求出每项的最大值，具体如下。

* 若 $i\lt s$，则 $a_i=\min(m_i,a_{i+1})$。

* 若 $i\gt s$，则 $a_i=\min(m_i,a_{i-1})$。

暴力代码就出炉了。$n^2$ 复杂度轻松过 $easy \space version$。


```cpp
#include<bits/stdc++.h>
#define re register
#define il inline
#define int long long
using namespace std;

const int N=2e3+10; 

int n,m[N],a[N],s,S,ans[N];

signed main()
{
	scanf("%lld",&n);
	for(re int i=1;i<=n;i++)
		scanf("%lld",&m[i]);
	for(re int i=1;i<=n;i++)
	{
		s=0;
		a[i]=m[i];
		s+=a[i];
		for(re int j=i-1;j;j--)
		{
			a[j]=min(a[j+1],m[j]);
			s+=a[j];
		}
		for(re int j=i+1;j<=n;j++)
		{
			a[j]=min(a[j-1],m[j]);
			s+=a[j];
		}
		if(s>S)
		{
			S=s;
			for(re int j=1;j<=n;j++)
				ans[j]=a[j];
		}
	} 
	for(re int i=1;i<=n;i++,putchar(' '))
		printf("%lld",ans[i]); 
	return 0;
} 
```


### 正解

$hard\space version$ 明显 $n^2$ 是过不了的。考虑 $dp$。

可以把山分成两部分，上升部分和下降部分。但只要把数组倒过来，下降部分就会变成上升部分。所以我们就考虑每个山顶的上升部分。

设 $f_s$ 为以 $s$ 为山顶的 $\sum\limits_{i=1}^{s}a_i$（每个 $a_i$ 的最大值就是前面见到过的算法）。

![](https://cdn.luogu.com.cn/upload/image_hosting/x130e4sn.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

假设我们已经算出 $f_1,f_2,...,f_{s-1}$，怎么求 $f_s$ 的转移方程呢？

如图圈出了一个转折点 $i(i\lt s)$。它所满足的条件和性质：

* $m_i\lt m_s $

* $m_{i+1}\ge m_s$

* $a_i=m_i$

那么 $i$ 之前的项的和的最大值就不受 $s$ 的影响了，就为 $f_i$。

所以，$f_s=f_i+m_s\times(s-i)$。

最后一个问题：$i$ 是什么？

$i$ 就是**最大的** $j$ 满足 $j\lt s$ 且 $m_j\lt m_s$，也就是离 $s$ 最近的，$m_i$ 值小于 $m_s$ 的位置。

这就需要一个**单调栈**，具体详见代码。下降部分就只需要将输入数组倒过来处理即可。

**注意看注释，有些变量名的意思会和你想得不一样。**

```cpp
#include<bits/stdc++.h>
#define re register
#define il inline
#define int long long
using namespace std;

const int N=5e5+10; 

int n,a[N],b[N],pos[N],top,fa[N],fb[N],s,S,ans[N],mtop;

signed main()
{
	// 不开 long long 见祖宗 
	scanf("%lld",&n);
	for(re int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		// a 数组就是 m 数组 
		b[n-i+1]=a[i];	
		// 倒过来搞	
	}
	for(re int i=1;i<=n;i++)
	{
		while(top&&a[i]<=a[pos[top]]) top--;
		fa[i]=fa[pos[top]]+a[i]*(i-pos[top]);
		pos[++top]=i;
	} 
	top=0;
	for(re int i=1;i<=n;i++)
	{
		while(top&&b[i]<=b[pos[top]]) top--;
		fb[i]=fb[pos[top]]+b[i]*(i-pos[top]);
		pos[++top]=i;
	}
	// 处理距离最近比 i 小的位置，单调栈部分 
	for(re int i=1;i<=n;i++)
	{
		s=fa[i]+fb[n-i+1]-a[i];
		// 枚举山顶 i，s 为山顶为 i 时数组最大和 
		// 注意山顶的值多加了一遍，需要减掉 
		if(s>S) 
		{
			S=s;
			mtop=i;
			// 更新山顶 
		}
	}
	ans[mtop]=a[mtop];
	for(re int i=mtop-1;i;i--) ans[i]=min(ans[i+1],a[i]);
	for(re int i=mtop+1;i<=n;i++) ans[i]=min(ans[i-1],a[i]);		
	for(re int i=1;i<=n;i++) printf("%lld ",ans[i]);
	// 构造 
	return 0;
} 
```



---

## 作者：gyh20 (赞：1)

首先我们发现，最后的答案一定是一个不降序列加上一个不升序列。

令 $dp_i$ 表示从 $1\sim i$ 的不降序列值和的最大值， $dp1_i$ 表示从 $i\sim n$ 的不升序列值和的最大值。

得出 $dp_i=dp_k+(i-k)\times a_i$，其中 $k$ 为 $i$ 之前第一个 $a_k<a_i$ 的值。

同理可以得到 $dp1_i$ 的值。

时间复杂度 $O(n^2)$。

```cpp
#include<cstdio>
#include<algorithm>
#include<map>
#include<set>
#include<iostream>
#define re register
#define int long long
using namespace std;
inline int read(){
	re int t=0;
	re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0'){
		t=(t<<3)+(t<<1)+v-48;
		v=getchar();
	}
	return t;
}
inline int max(re int x,re int y){
	return x>y?x:y;
}
inline int min(re int x,re int y){
	return x<y?x:y;
}
map<int,int>pos;
set<int>s;
set<int> :: iterator it;
int t,a[500002],dp[500002],dp1[500002],n,lst[500005],p,mx,ans[500005];
signed main(){
n=read();
for(re int i=1;i<=n;++i)a[i]=read();
for(re int i=1;i<=n;++i){
	lst[i]=0;
	for(re int j=i-1;j>=1;--j){
		if(a[i]>=a[j]){
			lst[i]=j;
			break;
		}
	}
}
for(re int i=1;i<=n;++i){
	dp[i]=dp[lst[i]]+(i-lst[i])*a[i];
}
reverse(a+1,a+n+1);
for(re int i=1;i<=n;++i){
	lst[i]=0;
	for(re int j=i-1;j>=1;--j){
		if(a[i]>=a[j]){
			lst[i]=j;
			break;
		}
	}
}
for(re int i=1;i<=n;++i){
	dp1[i]=dp1[lst[i]]+(i-lst[i])*a[i];
}
reverse(dp1+1,dp1+n+1);
for(re int i=1;i<=n;++i){
	if(dp[i]+dp1[i+1]>mx){
		mx=dp[i]+dp1[i+1];
		p=i;
	}
}
reverse(a+1,a+n+1);
mx=a[p];
for(re int i=p;i>=1;--i){	
mx=min(mx,a[i]);
	ans[i]=mx;

}
mx=a[p+1];
for(re int i=p+1;i<=n;++i){	
mx=min(mx,a[i]);
	ans[i]=mx;

}
for(re int i=1;i<=n;++i)printf("%lld ",ans[i]);
}
```


---

## 作者：极寒神冰 (赞：0)

可以发现答案一定由一个不下降子序列和一个不上升子序列构成。那我们可以考虑将原数列分成两个数列，通过枚举峰值位置将左右两边的贡献加起来即可。

左边贡献$L_i$即从上一个$a_{last}<=a_i$推过来

$$L_i=L_{last}+a_i*(i-last)$$

右边贡献同理

可以发现朴素枚举$last$的复杂度$O(n^2)$。

但是每次都要枚举$last$太麻烦了，可以使用单调栈或者笛卡尔树进行优化,复杂度即为$O(n)$

```
#include<bits/stdc++.h>
#define ld long double
#define tset puts("qwq");
#define test puts("QAQ");
#define pb push_back
#define pii pair<int,int> 
#define mkp make_pair
#define Max(a,b) ((a>b)?a:b)
#define us unsigned 
#define int long long
using namespace std;
const int inf=1e18;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21], *p1 = buf, *p2 = buf;
int read()
{
    int x=0,f=1;
    char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
    return x*f;
}
const int N=5e5+10;
int n,a[N];
int L[N],R[N];
int stk[N],top;
signed main()
{
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++)
	{
		while(top&&a[stk[top]]>a[i]) top--;
		L[i]=L[stk[top]]+a[i]*(i-stk[top]);
		stk[++top]=i;
	}
	stk[top=1]=n+1;
	for(int i=n;i>=1;i--)
	{
		while(top&&a[stk[top]]>a[i]) top--;
		R[i]=R[stk[top]]+a[i]*(stk[top]-i);
		stk[++top]=i;
	}
	int res=-1,pos;
	for(int i=1;i<=n;i++) if(L[i]+R[i]-a[i]>res) pos=i,res=L[i]+R[i]-a[i];
	int tmp=a[pos];
	for(int i=pos;i>=1;i--) if(a[i]>tmp) a[i]=tmp;else tmp=a[i];
	tmp=a[pos];
	for(int i=pos;i<=n;i++) if(a[i]>tmp) a[i]=tmp;else tmp=a[i];
	for(int i=1;i<=n;i++) printf("%lld ",a[i]);
}
```



---

## 作者：Ludo (赞：0)

## Part I. 思考

**提示** 记得开long long... 因为数据可以让最大的楼层数之和为 $10^9 \times 10^3$。

理解题目在这题很重要。

因为左右不能有比**它**高的（**它是任意一个位置**）。

如果我们将高度化成一个个直条，高度越高，直条越长，那么符合规定的答案一定是**山形**的。

也就是说，有**连续的一段相同数**是最高点。

因此，本题关键在于找出这个最高点，把图形**约束**为山形后高度和最大的答案。

枚举就好了。也有单调栈做法。

怎样约束呢？

枚举一栋大厦。定义最高点就是大厦的高度。

跑出山形：

1. 向最高点的左方循环，让目前所在的大厦高度不能高于最高点，且不能高于走过（就是目前大厦右方到最高点左方）的大厦。

2. 向最高点的右方循环，让目前所在的大厦高度不能高于最高点，且不能高于走过（就是最高点右方到目前大厦左方）的大厦。

可能解释不清楚。不过看代码就可以了。

## Part II. 代码

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
long long n,a[1001],b[1001],mini,tmp,ans,ans2[1001];
int main(void)
{
	scanf("%lld",&n);
	for (long long i=1;i<=n;i++) scanf("%lld",&a[i]);
	for (long long i=1;i<=n;i++) //枚举一个最高点。
	{
		mini=a[i];tmp=0;         //让接下来走的大厦最高的为mini，tmp就是大厦约束后高度和                 
		for (long long j=1;j<=n;j++) b[j]=a[j]; //复制到b数组，方便操作
		for (long long j=i-1;j>=1;j--) //向左走，所以要倒着枚举
		{
			if (b[j]>mini) b[j]=mini;  //约束目前大厦高度，不能高于右方至最高点的任何一栋大厦。
			mini=min(b[j],mini);       //可能比现在最低点低，更新。
            tmp+=b[j];                 //统计大厦约束后高度和
		}
		mini=a[i];tmp+=b[i];           //跟上面差不多，让接下来走的大厦最高的为mini 
		for (long long j=i+1;j<=n;j++) //向右走，正着枚举
		{
			if (b[j]>mini) b[j]=mini;  //约束目前大厦高度，不能高于右方至最高点的任何一栋大厦。
			mini=min(b[j],mini);       //可能比现在最低点低，更新。
            tmp+=b[j];                 //统计大厦约束后高度和
		}
		if (ans<tmp)                   //更新最优答案
		{
			ans=tmp;
			for (long long j=1;j<=n;j++) ans2[j]=b[j];
		}
	}
	if (n==1) //怕就加个特判吧。
	{
		printf("%lld",a[1]);
	}
	else
	{
		for (long long int i=1;i<=n;i++) printf("%lld ",ans2[i]);
	}
}
```


---

