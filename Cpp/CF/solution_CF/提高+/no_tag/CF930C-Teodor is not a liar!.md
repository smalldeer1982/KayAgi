# Teodor is not a liar!

## 题目描述

Young Teodor enjoys drawing. His favourite hobby is drawing segments with integer borders inside his huge $ [1;m] $ segment. One day Teodor noticed that picture he just drawn has one interesting feature: there doesn't exist an integer point, that belongs each of segments in the picture. Having discovered this fact, Teodor decided to share it with Sasha.

Sasha knows that Teodor likes to show off so he never trusts him. Teodor wants to prove that he can be trusted sometimes, so he decided to convince Sasha that there is no such integer point in his picture, which belongs to each segment. However Teodor is lazy person and neither wills to tell Sasha all coordinates of segments' ends nor wills to tell him their amount, so he suggested Sasha to ask him series of questions 'Given the integer point $ x_{i} $ , how many segments in Fedya's picture contain that point?', promising to tell correct answers for this questions.

Both boys are very busy studying and don't have much time, so they ask you to find out how many questions can Sasha ask Teodor, that having only answers on his questions, Sasha can't be sure that Teodor isn't lying to him. Note that Sasha doesn't know amount of segments in Teodor's picture. Sure, Sasha is smart person and never asks about same point twice.

## 说明/提示

First example shows situation where Sasha can never be sure that Teodor isn't lying to him, because even if one knows $ cnt(x_{i}) $ for each point in segment $ [1;4] $ , he can't distinguish this case from situation Teodor has drawn whole $ [1;4] $ segment.

In second example Sasha can ask about 5 points e.g. $ 1,2,3,5,6 $ , still not being sure if Teodor haven't lied to him. But once he knows information about all points in $ [1;6] $ segment, Sasha can be sure that Teodor haven't lied to him.

## 样例 #1

### 输入

```
2 4
1 2
3 4
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4 6
1 3
2 3
4 6
5 6
```

### 输出

```
5
```

# 题解

## 作者：lenlen (赞：16)

### Problem

题目大意：给定一个总区间 $[1,m]$ 和一些小区间 $[l_i,r_i]$，询问者一次询问可以询问未被询问的整数 $k$，会得到 $k$ 在所有小区间中的次数。问你最多询问多少次之后，询问者仍不能确定没有一个总区间内的数被所有小区间包含。保证的确没有一个这样的数，且询问者不知道有多少个小区间。

数据范围： $n,m \leq 10^5$。

### Solution

题目描述非常拗口和难理解。

解释一下就是这样的，最多多少次不重复询问之后，你就能保证所有在总区间里的数，至少不存在于一个小区间内。输出这个次数 $-1$。

我们先来考虑一下什么时候我们可以保证所有总区间里的数，至少不存在于一个小区间内。

来看样例二（样例一啥都看不出）：

![](https://cdn.luogu.com.cn/upload/image_hosting/j9lwk2wl.png)

而样例给出的是，选择 $1,2,3,5,6$ 时仍不能确定所有整数都有一个小区间不包含它。也就是这时候询问者认为可能有整数被所有小区间包含。容易理解：当只询问 $1,2,3,5,6$ 时，询问者可以认为，区间是 $[1,6],[2,6]$，既满足询问得出结论，又存在 $2,3,4,5,6$ 被所有区间包含，所以这种情况是不确定的。

而为什么得知 $1,2,3,4,5,6$ 的答案后询问者就可以保证所有数都必定存在一个小区间不包含它了呢？可以发现，$4$ 的询问次数小于 $3$ 的也小于 $5$ 的，我们可以想象 $4$ 把整个序列分成了两段。可以证明一定有一个区间 $[l_i,r_i],l_i>4$ 和一个区间 $[l_j,r_j],r_j<4$。

证明：利用反证法，若所有区间都满足 $[l_i,r_i],l_i \leq 4$，且 $[l_j,r_j],r_j \geq 4$，那么 $4$ 的次数必然会大于等于 $3,5$ 的次数，矛盾，所以得证。

$4$ 左边部分肯定都不在一个 $[l_i,r_i],l_i>4$ 的一个区间内，右边同理，所以询问者就可以肯定所有数都有一个区间不包含它。

发现了什么？若存在 $i$ 使得 $f_i<f_{i-1}$ 且 $f_i<f_{i+1}$（$f_i$ 表示出现次数），那么就可以确定所有数都至少不被一个区间包含。

我们要求最多次数，很明显了，就是要求一个最长上凸的次数序列，不存在 $i$ 满足 $f_i<f_{i-1}$ 且 $f_i<f_{i+1}$。

可以发现，我们其实就是在求两段最长不下降子序列的长度和，我们可以设 $dp1_i$ 表示 $[1,i]$ 的最长不下降子序列的长度，$dp2_i$ 表示 $[i,m]$ 的最长不下降子序列的长度。答案就是 $\max\limits_{i=1}^m (dp1_i+dp2_i)$。

至于统计出现次数，利用差分的思想，很快能够解决。

计算最长不下降子序列的长度，可以用二分的方法在 $O(n \log n)$ 的复杂度内求出 $dp1_i$，然后再反过来做一遍就好了。

### Code

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+7232;
int n,m,l,r,ans;
int s[N],q[N],head,dp1[N],dp2[N];
int mx(int x,int y){return x>y?x:y;}
int main()
{
	scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&l,&r);
        ++s[l],--s[r+1];//差分思想快速求次数
    }
    for(int i=1;i<=m;i++) s[i]=s[i]+s[i-1];
    head=0;
    for(int i=1;i<=m;i++)//求正向最长不下降子序列的长度
    {
        if(s[i]>=q[head]) q[++head]=s[i];
        else 
        {
            if(s[i]>q[1])
            {
                l=1,r=head;int sum;
                while(l<=r)
                {
                    int mid=l+r>>1;
                    if(q[mid]>s[i]) sum=mid,r=mid-1;
                    else l=mid+1; 
                }
                q[sum]=s[i];
            }
        }
        dp1[i]=head;
    }
    head=0;
    for(int i=m;i>=1;i--)
    {
        if(s[i]>=q[head]) q[++head]=s[i];
        else 
        {
            if(s[i]>q[1])
            {
                l=1,r=head;int sum;
                while(l<=r)
                {
                    int mid=l+r>>1;
                    if(q[mid]>s[i]) sum=mid,r=mid-1;
                    else l=mid+1; 
                }
                q[sum]=s[i];
            }
        }
        dp2[i]=head;
    }
    for(int i=1;i<=m;i++) ans=mx(ans,dp1[i]+dp2[i]-1);//-1是因为若i为最长不下降子序列的头和尾各算了一次，算了两次，若i不再序列中，那肯定不优，所以-1也没有影响
    printf("%d\n",ans);
}
```


---

## 作者：龙潜月十五 (赞：16)

# 前言：

本篇只是一个蒟蒻详细的总结，大佬可以自行跳过~~


------------


------------

# 一.审题

### 大意：

给出一个 $1$ ~ $m$ 的数列和 $n$ 个小区间，
    
    
  每次询问一个数会给出这个数在几个小区间内，
    
   问最多访问几次后， 
   仍不能确定**并不存在一个数被所有小区间包含**。
   


------------


### 思考：

初看之下，似乎毫无头绪，但我们看题目所要求的东西 :

不能确定**并不存在一个数被所有小区间包含**。

那什么时候我们能确定存在一个数被所有的小区间包含，什么时候不能确定呢？

对着样例 $2$ 模拟一下：



| 数字 | 1 | 2 | 3 | 4 | 5 | 6 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| 出现次数 | 1 | 2 | 2 | 1 | 2 | 2 |
当我们知道 $3$ ~ $5$ 的出现次数后，可以确定 $4$ 一定是不被所有区间包含，因为 $4$ **一定不被包含 $3$ 和 $5$ 的区间所包含**。

当我们知道 $1$ ~ $4$ 的出现次数时，并**不能确定** $2$ 和 $3$ 是否被所有区间包含。

因此我们得出规律：

 **若存在数字 $i<j<k$，且出现次数 $N_i>N_j<N_k$，可以确定 $j$ 一定不被所有区间包含（即出现 $j$ 为谷底的向下凸的单峰）**。


 **题目求询问后仍不确定的最多次数，也就是反过来，求向上凸的的单峰的最长长度**

------------

------------



# 二.差分
   前面说要用到每个数出现在不同区间的次数，该如何统计呢？
     
   暴力计算当然不行，便要用到**差分**的技巧。
###  1. **作用**
 
在给定几个区间，统计每个数出现的次数。
       
###  2. **实现**
 
类似于**前缀和**（实际上差分是前缀和的**逆操作**）。

       
  当给定给定区间 $[l,r]$ 时，将差分数组 $diff[l]$ 加上1，将 $diff[r+1]$ 减去1(可以自己列数据发现这种方式的正确性）。
      
   最后类似于前缀和，将差分数组加起来。
       
$$diff[i]+=diff[i-1]$$
       
$diff[i]$ 即为第 $i$ 个数出现次数。
       
###  3.**例题**
- [P3406 海底高铁](https://www.luogu.com.cn/problem/P3406)
- [P1083 [NOIP2012 提高组] 借教室](https://www.luogu.com.cn/problem/P1083)


------------

# 三.最长不下降子序列
  求出最长单峰长度要求出最长不下降子序列，下面介绍一种效率高的方法。
     
### 1.实现
（1）用 $up$ 数组存放最长不下降子序列。
     
   （2）比较 $a[i]$ 和 $up$ 数组最后一位，不下降则直接接在 $up$ 数组的后面。
     
   （3）否则在 $up$ 数组中二分查找第一个大于 $a[i]$ 的数，并用 $a[i]$ 代替其，正确性可以在下面给的例题题解中看。
     
### 2.例题
- [P1020 [NOIP1999 普及组] 导弹拦截](https://www.luogu.com.cn/problem/P1020)

- [P1091 [NOIP2004 提高组] 合唱队形](https://www.luogu.com.cn/problem/P1091)


------------
# 四.代码
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=100005;
typedef long long ll;

ll n,m,a[N],up[N],s1[N],s2[N],len,ans;

int main()
{
	scanf("%lld%lld",&n,&m);
	//差分求每个数字被几个区间包含 
	for(ll i=1;i<=n;i++)
	{
		ll l,r;
		scanf("%lld%lld",&l,&r);
		a[l]++,a[r+1]--;
	}
	for(ll i=1;i<=m;i++)
		a[i]+=a[i-1];
	//从前往后求一遍最长上升子序列的长度 
	memset(up,0ll,sizeof(up));
	len=1;
	up[1]=a[1];
	s1[1]=1;//s1为每个数在从前往后的最长上升子序列长度
	for(ll i=2;i<=m;i++)
	{
		if(a[i]>=up[len])
		{
			up[++len]=a[i];
			s1[i]=len;
		}
		else
		{
			ll d=upper_bound(up+1,up+len+1,a[i])-up;
			up[d]=a[i];
			s1[i]=d;
		}
	}
	//从后往前求一遍最长不下降子序列的长度
	len=1;
	memset(up,0ll,sizeof(up));
	up[1]=a[m];
	s2[m]=1;//s2为每个数在从后往前的最长上升子序列长度
	for(ll i=m-1;i>=1;i--)
	{
		if(a[i]>=up[len])
		{
			up[++len]=a[i];
			s2[i]=len;
		}
		else
		{
			ll d=upper_bound(up+1,up+len+1,a[i])-up;
			up[d]=a[i];
			s2[i]=d;
		}
	}
	//求最长单峰的长度，即为最后的答案
	for(ll i=1;i<=m;i++)
		ans=max(ans,s1[i]+s2[i]-1);//注；-1是因为把自己算了两次
	printf("%lld",ans); 
	return 0;
}
```

     



---

## 作者：_Felix (赞：4)

看了看没有人写详细的证明……可能觉得太简单了？

另外，我不觉得题面上的翻译是给人类阅读的……

> 万老爷翻的题意：
> 
> Teodor 有 $n$ 条线段,端点都是正整数且在 $[1,m]$ 之间.他发现 **没有一个整点满足在所有线段上**。他把这个事实告诉 Sasha 然而她不信. Sasha 可以向 Teodor 询问若干个整点 $x_i$ ,Teodor会回答 $cnt(x_i)$ 表示 $x_i$ 在多少条线段上.
> 
> 提醒：Sasha 不知道 $n$ 的大小。Sasha 很聪明，所以 $x_i$ 互不相同。

---

$cnt_x$ : 整数点 $x$ 出现在 $cnt_x$ 条线段上（题面中的定义），可以 $O(n)$ 差分预处理。

所有整数点都不同时存在于所有线段上 其实就说明有至少两条线段不相交。不相交那就有一个点在“分界“上。那么或许 【能证明某点是分界点】 就说明有 【至少两条线段不相交】？

我们有结论：能判断出所有整数点都不同时存在于所有线段上 $\Leftrightarrow \exists x_1<x_2<x_3$，满足 $cnt_{x_2}<cnt_{x_1},cnt_{x_2}<cnt_{x,3}$

[![LJmATx.md.png](https://s1.ax1x.com/2022/04/16/LJmATx.md.png)](https://imgtu.com/i/LJmATx)

> Proof
> 
> 必要性：
> 
> 有至多 $cnt_{x_2}$ 条线段（红色）同时经过 $x_1,x_3$，那么还有 $cnt_{x_1}-cnt_{x_2}$ 条（橙色）无法到达 $x_2$，$cnt_{x_3}-cnt_{x_2}$ 条（蓝色）无法到达 $x_2$，那么 $x_2$ 就成为了橙色和蓝色的分界线，每个整数点会“属于”橙色 或 “属于”蓝色 或 都不属于。
> 
> 充分性：
> 如果当前还没有问出来这么一个 $x_2$，那么根据当前问出来的信息，是一个单峰的序列，肯定能构造出一种 【存在一个整数点同时存在于所有线段上】 的情况。（例如一层层叠上去，峰点会存在于所有线段上）
>
> ![](https://s1.ax1x.com/2022/04/16/LJm6hT.png)

那么我们不能满足这一条件的最大问题数，其实就是 单峰的最长序列。

树状数组正着和反着求两遍最长上升子序列即可。

虽然但是，这种结论到底是怎么想出来的啊/ll

---

## 作者：万弘 (赞：4)

//修复了一个手贱,如果还有手贱请联系我  
题意:Teodor有$n$条线段,端点都是正整数且在$[1,m]$之间.他发现没有一个整点满足在所有线段上.他把这个事实告诉Sasha然而她不信.Sasha可以向Teodor询问若干个整点$x_i$,Teodor会回答$cnt(x_i)$表示$x_i$在多少条线段上.

求一个最大的集合$S$,满足询问$\forall x\in S$的$cnt(x)$后仍然不能保证没有一个整点满足在所有线段上.(注意Sasha是不知道有多少条线段的)

解:乍一看很不可做.但可以发现能判断"没有一个整点满足在所有线段上"当且仅当存在至少一组$(x_1,x_2,x_3)$满足$x_1<x_2<x_3,cnt(x_2)<cnt(x_1),cnt(x_2)<cnt(x_3)$.  
感性理解:$x_1,x_2,x_3$最多同时被$cnt(x_2)$条线段覆盖,那么经过$x_1$的另外$cnt(x_1)-cnt(x_2)$条线段无法覆盖到$x_3$及其右边的所有点.反之亦然.

问题转化为求一个最长子序列满足不存在一组$(x_1,x_2,x_3)$满足上述条件.这等价于求原序列(即$cnt$,注意$cnt$可以直接差分预处理)的最长单峰子序列长度.这很容易dp求解.  
$f(0/1,i,j)$表示考虑前$i$个元素,以$j$结尾的最长单峰序列长度,且现在在递增/递减 段.  
$$f(0,i,j)=\max_{k\le j} f(0,i-1,k)+1$$
$$f(1,i,j)=\max\{f(0,i,j),\max_{k\ge j}f(1,i-1,k) \}+1$$
用线段树优化即可.时间复杂度$\mathcal O(m\log n)$
```cpp
/**********/
#define MAXN 200011
ll n,m;
struct Segment_Tree
{
    ll t[MAXN<<2|1];
    #define rt t[num]
    #define tl t[num<<1]
    #define tr t[num<<1|1]
    void modify(un pos,ll k,un l=0,un r=n,un num=1)
    {
        if(l==r){rt=k;return;}
        un mid=(l+r)>>1;
        if(pos<=mid)modify(pos,k,l,mid,num<<1);
        else modify(pos,k,mid+1,r,num<<1|1);
        rt=max(tl,tr);
    }
    ll Qmax(un ql,un qr,un l=0,un r=n,un num=1)
    {
        if(ql<=l&&r<=qr)return rt;
        un mid=(l+r)>>1;
        ll ans=0;
        if(ql<=mid)umax(ans,Qmax(ql,qr,l,mid,num<<1));
        if(qr>mid)umax(ans,Qmax(ql,qr,mid+1,r,num<<1|1));
        return ans;
    }
}t0,t1;
ll a[MAXN];
int main()
{
    n=read(),m=read();
    for(ll i=1;i<=n;++i)
    {
        ll l=read(),r=read();
        ++a[l],--a[r+1];
    }
    for(ll i=1;i<=m;++i)a[i]+=a[i-1];
    for(ll i=1;i<=m;++i)
    {
        ll v=t0.Qmax(0,a[i]);
        t0.modify(a[i],v+1);
        t1.modify(a[i],max(t1.Qmax(a[i],n),v)+1);
    }
    printf("%lld",max(t0.Qmax(0,n),t1.Qmax(0,n)));
    return 0;
}
```

---

## 作者：potatoler (赞：3)

### [题目](https://www.luogu.com.cn/problem/CF930C)简述

$n$ 条线段，断点都是正整数且都属于区间 $[1,m]$，Teodor 发现没有一个正整数点在所有的线段上。Sasha 可以向 Teodor 询问若干个整点（但 Sasha 不知道有多少条线段），对于每次询问的点 $x$，Teodor 会回答 $cnt_{x}$ 表示 $x$ 在多少条线段上。求一个最大的集合 $S$ 满足询问 $∀x∈S$ 的 $cnt_x$ 后仍然不能保证没有一个整点满足在所有线段上。只需要输出 $S$ 的大小。

### 思路

题目中的集合是询问了任意集合内的整点都不能保证这个条件，我们可以反着想 —— 怎样判断「没有一个正整数点在所有的线段上」。

考虑这个问题，可以发现当存在一组整点 $x<y<z$ 满足 $cnt_y<cnt_x$ 且 $cnt_y<cnt_z$ 的时候就可以确定没有一个正整数点在所有的线段上：因为线段是连续的，所以当满足条件时只有可能是中间的点的 $cnt$ 比两边的点大，否则一定有一条线段，覆盖了左边的点和中间的点儿没有右边的点，可以考虑三条线段 $l_1[x,y),\ l_2[x,z],\ l_3(y,z]$。

将每个整点的 $cnt$ 值作为这个位置的值，那么找到两个峰的时候就可以判断不满足条件。那么我们就是要求不能找到两个峰的最大位置集合大小，也就是最长单峰序列长度，只需要正反求两次最长上升子序列即可。其中 $cnt$ 可以差分预处理。

### Code

```c++
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<climits>
#include<algorithm>
#include<utility>
#include<map>
#include<vector>
#define int long long
using namespace std;
const int MaxN = 100005;
int n, m, a[MaxN], f[MaxN], g[MaxN], ans;
vector<int> number;

inline int Read(){
	int num = 0, op = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') op = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		num = num * 10 + ch - '0';
		ch = getchar();
	}
	return num * op;
}

signed main(){
	n = Read(), m = Read();
	for(int i=1; i<=n; i++){
		int l = Read(), r = Read();
		a[l]++, a[r+1]--;
	}
	for(int i=1; i<=m; i++)
		a[i] += a[i-1];
	number.clear();
	number.push_back(a[1]);
	f[1] = 1;
	for(int i=2; i<=m; i++){
		if(a[i] >= number.back()){
			number.push_back(a[i]);
			f[i] = number.size();
		}
		else{
			int pos = upper_bound(number.begin(), number.end(), a[i]) - number.begin();
			number[pos] = a[i];
			f[i] = pos + 1;
		}
	}
	number.clear();
	number.push_back(a[m]);
	g[m] = 1;
	for(int i = m-1; i>=1; i--){
		if(a[i] >= number.back()){
			number.push_back(a[i]);
			g[i] = number.size();
		}
		else{
			int pos = upper_bound(number.begin(), number.end(), a[i]) - number.begin();
			number[pos] = a[i];
			g[i] = pos + 1;
		}
	}
	for(int i=1; i<=m; i++)
		ans = max(ans, f[i]+g[i]-1);
	printf("%lld", ans);
	return 0;
}
```



---

## 作者：fanypcd (赞：1)

题目即为给定 m 个位置的覆盖线段个数，最多能让另一个人知道几个使得他不能确定有没有一个位置被所有的线段覆盖（不知道有多少线段）。

反向思考怎么能确定没有一个位置被所有的线段覆盖，发现，如果覆盖的个数的序列出现了三个位置，并且中间位置的覆盖条数小于两边，那么显然就能够确定没有一个位置被所有的线段覆盖。（显然有部分覆盖到左边的线段不会覆盖到右边，右边没有这样的位置，右边部分线段不能覆盖到左边，左边没有这样的位置，中间的更不是了）。

由此，我们发现，选取的询问位置的覆盖条数必须先单调不降，然后单调不增。

于是用 $O(n \log n)$ 的 DP 分别求出每个位置结尾的最长单调不降序列长度，和以每个位置为开头延伸到结尾的最长单调不增序列长度。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline void read(int &x)
{
	x = 0;
	int f = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9')
	{
		f |= ch == '-';
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	x = f ? -x : x;
	return;
}
#define inf 0x3f3f3f3f
#define N 100005
int n, m, a[N];
int bg[N], ed[N];
int g[N];
void dp(int *f)
{
	memset(g, 0x3f, sizeof(g));
	g[0] = 0;
	int len = 0;
	for(int i = 1; i <= m; i++)
	{
		if(a[i] >= g[len])
		{
			len++;
			f[i] = len;
			g[len] = a[i];
		}
		else
		{
			int pos = upper_bound(g, g + len + 1, a[i]) - g;
			f[i] = pos;
			g[f[i]] = a[i];
		}
	}
	return;
}
signed main()
{
	read(n), read(m);
	int xl, xr;
	for(int i = 1; i <= n; i++)
	{
		read(xl), read(xr);
		a[xl]++, a[xr + 1]--;
	}
	for(int i = 1; i <= m; i++)
	{
		a[i] += a[i - 1];
	}
	dp(bg);
	reverse(a + 1, a + m + 1);
	dp(ed);
	reverse(ed + 1, ed + m + 1);
	int ans = 0;
	for(int i = 1; i <= m; i++)
	{
		ans = max(ans, bg[i] + ed[i] - 1);
	}
	printf("%d", ans);
	return 0;
}
```

---

## 作者：SJZ2010 (赞：0)

结论真是太神了……

---

假装你是 Shasa，你得到了一堆返回的 $cnt_x$，你会怎么判断？~~反正我是不会。~~

如果可以确定，所有数都不会被所有区间覆盖，那么肯定是这样的：在某个点左边有一些区间，左端点在这个点的左边；而且某个点右端点有一些区间，右端点在这个点右边，即如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/p6evsjd6.png)

这样的话，肯定有 $x_1 < x_2 < x_3$ 满足 $cnt_{x_1} > cnt_{x_2}$，且 $cnt_{x_3} > cnt_{x_2}$，这个条件的含义是把它们可能共有的可能的最多的线段全去掉，左右还各剩一些。

那么我们要让 Shasa 多猜几次，就要避免出现这种情况，即找一个单峰的子序列。二分优化什么的我不会，就用树状数组求前后的 LIS 然后拼起来吧。

[AC.](https://codeforces.com/contest/930/submission/278455476)

---

## 作者：Find_Yourself (赞：0)

好题啊好题。

定义 $a_i$ 为有多少个区间包含 $i$。

拍脑袋一想，当且仅当存在顺序的三个坐标 $(i,j,k)$ 满足 $a_i>a_j$ 且 $a_j<a_l$ 时，可以确定没有数被所有区间包含。

这个结论很简单，因为如果存在，则 $a$ 序列必定为一个“山峰”。而如果出现上面这种情况，说明有“山谷”。

所以我们可以用树状数组求出 $f_i$ 表示以 $i$ 结尾的最长不下降子序列，$g_i$ 表示以 $i$ 开头的最长不上升子序列。

那么答案为 $ans=\max\limits_{i=1}^{n-1}\left(f_i+\max\limits_{j=i+1}^{n}g_j\right)$。

复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m,a[N],f[N],g[N],c[N];
int lbt(int x){return x&(-x);}
void update(int i,int k){for(;i<=n;i+=lbt(i))c[i]=max(c[i],k);}
int getmax(int i){int res=0;for(;i;i-=lbt(i))res=max(res,c[i]);return res;}
int main(){
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
  cin>>m>>n;
  for(int i=1;i<=m;++i){
    int l,r;cin>>l>>r;
    ++a[l];--a[r+1];
  }
  for(int i=1;i<=n;++i)a[i]+=a[i-1];
  for(int i=1;i<=n;++i)++a[i];
  for(int i=1;i<=n;++i){
    f[i]=getmax(a[i])+1;
    update(a[i],f[i]);
  }
  for(int i=1;i<=n;++i)c[i]=0;
  int ans=0,maxn=0;
  for(int i=n;i>=1;--i){
    g[i]=getmax(a[i])+1;
    update(a[i],g[i]);
    ans=max(ans,f[i]+maxn);
    maxn=max(maxn,g[i]);
  }
  cout<<ans<<endl;
  return 0;
}

```


---

## 作者：Uuuuuur_ (赞：0)

题意很难理解，简单来讲就是，有几个区间，每次询问可以知道某个点被 $k$ 个区间覆盖，在**运气最差**的情况下，询问了 $q$  次，还不能确定一个点是否被所有区间覆盖，求 $q$。

什么时候，**可能**有一个点能被所有区间覆盖。

首先，可能被全部覆盖的点，肯定是询问得到的 $k$ 最大的点。如果有多个，那它们肯定连续。这很简单。

这时候，我们可以想象出一幅画面：以**备选点**为中心，向两边辐射；把所有的区间都叠在备选点上，那么越远离备选点，被辐射的就越少。所以，由第一个已知点，到备选点，覆盖次数是**单调不减**，而备选点到最后一个已知点，覆盖次数是**单调不增**。有些点是未知的，但它们可以任意取值，不会影响单调性。

说到这里，就很清楚了，我们把每个点被覆盖次数作为其权值（这个用差分解决），然后做一遍最长单峰子序列（我自己瞎取的名字），就好了。

复杂度要求 $O(n \log n)$，但我又不会写单调子序列的优化，而且也不直观，所以我使用了很直观~~且很简单~~的**权值线段树**。

注意权值范围从 $0$ 到最多出现次数（不是 $m$ ）哦。

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#define ls(p) ((p) << 1)
#define rs(p) ((p) << 1 | 1)
using namespace std;
const int maxm = 1e5+5;
int n, m;
int a[maxm];
int v[4 * maxm];
int f[maxm];
int revf[maxm];
inline int max(int a, int b) {
    return a > b ? a : b;
}
void pushup(int p) {
    v[p] = max(v[ls(p)], v[rs(p)]);
}
void query(int l, int r, int x, int y, int p, int &ans) {
    if (x <= l && r <= y) {
       
        ans = max(ans, v[p] + 1);
        return ;
    }
    int mid = (l + r) >> 1;
    if (x <= mid) query(l, mid, x, y, ls(p), ans);
    if (y > mid) query(mid + 1, r, x, y, rs(p), ans);
}
void update(int l, int r, int x, int val, int p) {
    if (l == r) {
        v[p] = max(v[p], val);
        return ;
    }
    int mid = (l + r) >> 1;
    if (x <= mid) update(l, mid, x, val, ls(p));
    else update(mid + 1, r, x, val, rs(p));
    pushup(p);
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        a[l]++;
        a[r + 1]--;
    }
    for (int i = 1; i <= m; i++) {
        a[i] += a[i - 1]; 
        
    }
    for (int i = 1; i <= m; i++) {
        query(0, maxm, 0, a[i], 1, f[i]);
        update(0, maxm, a[i], f[i], 1);
      
    }
    memset(v, 0, sizeof(v));
    for (int i = m; i >= 1; i--) {
        query(0, maxm, 0, a[i], 1, revf[i]);
        update(0, maxm, a[i], revf[i], 1);
    }
    int ans = 0;
    for (int i = 1; i <= m; i++) {
        ans = max(ans, f[i] + revf[i] - 1);
    }
    cout << ans;
    return 0;
}


```


---

