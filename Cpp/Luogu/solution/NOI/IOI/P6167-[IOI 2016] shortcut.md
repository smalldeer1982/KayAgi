# [IOI 2016] shortcut

## 题目描述

Pavel 有一个非常简单的铁路玩具。 它有一条含有 $n$ 个车站的主干线并且连续编号为 $0$ 到 $n-1$。车站 $0$ 和车站 $n-1$ 就在这条主干线的两端。其中车站 $i$ 和车站 $i+1$ 之间的距离为 $l_i$ 厘米（$ 0 \le i<n-1$）。

除了这条主干线之外，这个铁路也许会有些支线。每条支线都是由主干线中的一个车站和主干线 外的一个新车站之间的一条新铁路构成（这些新的车站不会被编号）。在主干线中的一个车站最多只能有一条支线。以主干线中的车站 $i$ 为起点的支线的长度为 $d_i$ 厘米。我们用 $d_i=0$ 来表示车站 $i$ 没有支线。

![](https://cdn.luogu.com.cn/upload/image_hosting/h21s6cjy.png)

Pavel 现正规划一条快捷方式：一条在主干线中两个不相同的车站之间（它们可能相邻）的快速干线。这条快速干线无论是连接哪两个车站，它的长度都将会恰好是 $c$ 厘米。

铁路中的每一段，包括那条新的快速干线，都能够双向行驶。任意两个车站的距离就是它们之间沿着铁路由一个车站到另一个车站之间最短路径的长度。所有车站组合中最大的距离就叫做整个铁路网络的直径。换句话说，存在一个最小值 $t$ 使任意两个车站之间的距离都不会超过 $t$。

Pavel 就是想建造一条快速干线，使得有了这条快速干线后新的铁路网络的直径能达到最小值。

### 样例一

```
4 10
10 20 20
0 40 0 30
```

最优解是在车站 $1$ 和车站 $3$ 之间建造一条快速干线，如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/a31c6opk.png)

这个新铁路网络的直径是 $80$ 厘米，所以应该输出数值 $80$。

### 样例二

```
9 30
10 10 10 10 10 10 10 10
20 0 30 0 0 40 0 40 0
```

最优解是连接车站 $2$ 和车站 $7$，这个解的直径是 $110$。

### 样例三

```
4 1
2 2 2
1 10 10 1
```
最优解是连接车站 $1$ 和车站 $2$，这样直径将被缩短到 $21$。

### 样例四

```
3 3
1 1 
1 1 1
```
在任意两个车站中建立长度为 $3$ 的快速干线都不会改进整个铁路网络的直径，因此其直径仍为初始值 $4$。



## 说明/提示

对于 $100\%$ 的数据，$2\le n\le 10^6$，$1\le l_i\le 10^9$，$0\le d_i\le 10^9$，$1\le c\le 10^9$。



## 样例 #1

### 输入

```
4 10
10 20 20
0 40 0 30
```

### 输出

```
80
```

# 题解

## 作者：itisover (赞：9)

设主干上的点的距离前缀和为 $x_i$，每个点的支线长度为 $d_i$，我们可以考虑二分直径最小值 $k$。

对于任意点对 $(i,j)$​，若 $k$​ 是合法的则需满足下列条件的一个：

+ 只走原先的边就合法：$d_i+d_j+|x_i-x_j|\le k$
+ 走新建的边合法（$y,z$ 表示建新边的两端点的 $x$ 值，$c$ 是新建的边的长度）：$d_i+d_j+|x_i-y|+|x_j-z|+c \le k$

如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/nwqo8uih.png)

考虑解一下这个绝对值不等式方程，可以转化为四个不等式构成的一个不等式组：

$$\begin{cases}z+y\le k+(x_j-d_j)+(x_i-d_i)-c;\\z+y\ge (x_j+d_j)+(x_i+d_i)-k+c;\\z-y\le k+(x_j-d_j)-(x_i+d_i)-c;\\z-y\ge (x_j+d_j)-(x_i-d_i)-k+c.\end{cases}$$

我们现在要做的就是求这 $4$ 个不等式的解集的交

我们考虑先枚举 $j$​，求出对于每个 $j$，$4$ 个不等式右边部分的最值。

运用我们的解不等式的知识（如果一个数小于等于一个函数，则这个数要小于等于这个函数的最小值；如果一个数大于等于一个函数，则这个数要大于等于这个函数的最大值）。因为我们枚举 $j$​，所以 $k,x_j,d_j$​ 这几项都是定值，于是我们考虑用一个东西来维护 $d_i+x_i$​ 和 $d_i-x_i$​ 的最大值就行了（注意：这里的最大值的前提条件是上述的只走原先的边的情况不合法），可以考虑用单调队列。我们维护 $d_i-x_i$​ 的最大值，当 **队头的值**$+d_j+x_j>k$​ 的时候，就是上述的只走原先的边的情况不合法的时候，我们就可以更新 $d_i-x_i$​ 的最大值了。但是这里的单调队列有个小漏洞，就是如果的 $d_{i-1}$​ 特别长，当前的 $d_i$​ 很短，就会导致在前一次出队的队头可能可以被更新为最大值，即 **队头的值**$+d_i+x_i\le k$​ 且 **队头的值**$+d_{i-1}+x_{i-1}>k$​，但是我们模拟一下求不等式右边部分的最值的过程，不难发现这种情况不会对答案（$x1,x2,x3,x4$ 等）有更新，所以就没影响了。

等到我们把 $z+y$​​​​ 和 $z-y$​​​​ 的解集求出来后，我们只用枚举 $z,y$​​​​ 代回验证就好了，因为 $z,y$​​​​ 本质上是 $x$​​​​ 数组里的元素，即前缀和数组里的元素，所以满足单调递增，于是我们可以枚举 $y$​​​​，用指针模拟 $z$​​​​ ，如果 $z+y$​​​ 和 $z-y$​​​ 的在 $x$​​ 数组中的范围有交，则有解，合法，反之不合法或范围是空集也不合法。

怎么模拟呢？我们对于 $z+y$​​，我们可以考虑从后往前枚举，求出使 $z+y$​​ 连续合法的左端点 $l1$​​，再从后往前求出使 $z+y$​​ 连续不合法的位置的左边一个位置，即使 $z+y$​​ 连续合法的右端点 $r1$​​，$z+y$​​ 的范围即为 $[l1,r1]$，即 $x[l1\sim r1]$ 中的任意元素都满足条件。根据单调性，这显然正确，时间复杂度 $\Theta(n)$​

对于 $z-y$ 同理。

总时间复杂度 $\Theta(n\log m)$​

感谢神仙 slzs 的帮助。

[IOI官方题解](https://ioinformatics.org/files/ioi2016solutions.pdf)

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
template <class T>
inline T read(){
    T r=0,f=0;char c=getchar();
    while(!isdigit(c)) f|=c=='-',c=getchar();
    while(isdigit(c)) r=(r<<3)+(r<<1)+(c^48),c=getchar();
    return f?-r:r;
}
const int N=1e6+5,INF=1e18;
int n,c;
int d[N],x[N],q[N];
bool check(int k){
    int l=1,r=0,max1=-INF,max2=-INF,x1=INF,x2=-INF,x3=INF,x4=-INF;
    for(int i=1;i<=n;++i){
        if(max1+d[i]+x[i]>k){
            while(l<=r&&d[q[l]]-x[q[l]]+d[i]+x[i]>k) max2=max(max2,d[q[l]]+x[q[l]]),++l;
            x1=min(x1,k+x[i]-d[i]-max1-c);//分别对应上述不等式组的1、2、3、4式
            x2=max(x2,-k+c+x[i]+d[i]+max2);
            x3=min(x3,k+x[i]-d[i]-max2-c);
            x4=max(x4,-k+c+x[i]+d[i]+max1);
        }
        max1=max(max1,d[i]-x[i]);//维护 d[i]-x[i] 的最大值
        //为什么不用满足只走原先的边不合法再求最大值呢？因为当 max1 能进到上面的 if 中去就已经满足了只走原先的边不合法
        while(l<=r&&d[q[r]]-x[q[r]]<=d[i]-x[i]) --r;
        q[++r]=i;
    }
    if(x1<x2||x3<x4) return false;//如果 z+y 或 z-y 的解集为空，则不合法
    int l1=n+1,l2=1,r1=n,r2=0;//枚举 z,y 判断是否合法
    for(int i=1;i<=n;++i){
        while(l1>1&&x[l1-1]+x[i]>=x2) --l1;//判断合法，对应2式
        while(l1<=r1&&x[r1]+x[i]>x1) --r1;//判断不合法，对应1式
        while(r2<n&&x[r2+1]-x[i]<=x3) ++r2;//判断合法，对应3式
        while(l2<=r2&&x[l2]-x[i]<x4) ++l2;//判断不合法，对应4式
        if(l1<=r1&&l2<=r2&&l1<=r2&&l2<=r1) return true;//范围不为空集且有交
    }
    return false;
}
signed main(){
    n=read<int>(),c=read<int>();
    for(int i=2;i<=n;++i) x[i]=x[i-1]+read<int>();
    for(int i=1;i<=n;++i) d[i]=read<int>();
    int l=1,r=1e18,mid,ans;
    while(l<=r) if(check(mid=l+r>>1)) ans=mid,r=mid-1;else l=mid+1;
    printf("%lld",ans);
    return 0;
}
```



---

## 作者：myee (赞：8)

### 前言

很厉害的题目！不涉及什么高深的算法，一些细节却并不好想。

### 思路

我们设 $x_{i+1}=x_i+l_i,x_0=0$。

显然两个点 $u,v$ 要么走树上路径，要么走跨越该边的路径。

我们假设连边 $(s,t)$，满足 $s<t,u<v$。

则前者贡献是 $d_u+d_v+x_v-x_u$，后者贡献是 $d_u+d_v+|x_u-x_s|+|x_v-x_t|+c$。

考虑二分答案，判断答案是否 $\le w$。

也即，

$$\forall u<v,d_u+d_v+\min\{x_v-x_u,|x_u-x_s|+|x_v-x_t|+c\}\le w$$

也即

$$\forall u<v,(d_u-x_u)+(d_v+x_v)\le w\lor\begin{cases}(d_u+x_u)+(d_v+x_v)\le w+x_s+x_t-c\\(d_u+x_u)+(d_v-x_v)\le w+x_s-x_t-c\\(d_u-x_u)+(d_v+x_v)\le w-x_s+x_t-c\\(d_u-x_u)+(d_v-x_v)\le w-x_s-x_t-c\end{cases}$$

我们设 $A_p=d_p+x_p,B_p=d_p-x_p$，那么合法等价于

$$\forall u<v,B_u+A_v\le w\lor\begin{cases}A_u+A_v\le w+x_s+x_t-c\\A_u+B_v\le w+x_s-x_t-c\\B_u+A_v\le w-x_s+x_t-c\\B_u+B_v\le w-x_s-x_t-c\end{cases}$$

我们不妨**对每个 $u<v\land B_u+A_v>w$ 算出后面四条限制的左式的最大值**。

假设已经算出，我们就得到关于 $x_s$ 和 $x_t$ 的四条方程，也就得到 $x_t\pm x_s$ 的上下界，枚举下 $t$，可以顺带对 $s$ 的区间拿四个指针维护一下做到 $O(n)$。

于是考虑怎么算。直接对 $u<v$ 一维分治是单轮 $O(n\log n)$ 的，总复杂度 $O(n\log n\log(nv))$，较难通过。

考虑优化。

对于限制 $3,4$，考虑直接枚举 $v$。那么我们就是要得到前缀中每个 $B>w-A_v$ 的 $\max B$，直接维护前缀中最大 $B$，然后 check 其是否 $>w-A_v$ 即可。

限制 $1$ 可以通过枚举 $u$ 类似地实现。

最后考虑第 $2$ 条限制怎么求。

也即，我们现在需要求

$$\max_{u<v,B_u+A_v>w}\{A_u+B_v\}$$

这个看上去只能 $O(n\log n)$ 计算。

不过实际上由于本题性质，其可以做到 $O(n)$！

具体地，我们注意到随着 $u$ 的增长，必有 $A_u-B_u=2x_u$ 变大。

于是 $(A,B)$ 对只可能出现三种情况（把等于视作边界情况）：
* $A$ 增，$B$ 增。
* $A$ 增，$B$ 减。
* $A$ 减，$B$ 减。

拿一个单调栈维护一下。

如果你的 $A_u,B_u$ 均比上一个小，直接被暴打，因此可以当作不存在。顺带计算一下和上一项之间的贡献即可。

如果你的 $A_u,B_u$ 均比上一个大，直接暴打那个数，不妨在把上一个数弹栈的同时计算一下弹栈的两个数之间的贡献。

于是剩下的栈里总形如 $A$ 单调增 $B$ 单调减。

考虑建出栈之后，再解决栈内部的贡献。

这个直接双指针即可维护。

于是复杂度即为 $O(n)$。

最后由于要套一个二分答案，总复杂度 $O(n\log(nv))$。

### Code

代码跑得很快。

以下是核心代码。

```cpp
uint n;
llt X[1000005],A[1000005],B[1000005];
llt MaxPreB[1000005],MaxSufA[1000005],c;
std::vector<std::pair<llt,llt> >S,T;
bol check(llt w)
{
    llt x1=-1e18,x2=-1e18,x3=-1e18,x4=-1e18;
    for(uint i=0;i<n;i++)
    {
        if(A[i]+MaxPreB[i]>w)_max(x3,MaxPreB[i]+A[i]),_max(x4,MaxPreB[i]+B[i]);
        if(B[i]+MaxSufA[i]>w)_max(x1,MaxSufA[i]+A[i]);
    }
    for(auto s:T)if(s.first>w)_max(x2,s.second);
    for(uint i=1,j=0;i<S.size();i++)if(S[0].second+S[i].first>w)
    {
        while(j+1<i&&S[j+1].second+S[i].first>w)j++;
        _max(x2,S[j].first+S[i].second);
    }
    llt l_add=x1+c-w,r_add=w-x4-c,l_sub=x3+c-w,r_sub=w-x2-c;
    _max(l_add,X[1]),_max(l_sub,0ll),_min(r_add,X[n-1]+X[n-2]),_min(r_sub,X[n-1]);
    if(l_add>r_add||l_sub>r_sub)return false;
    for(uint i=0,a=n,b=n,c=0,d=0;i<n;i++)
    {
        while(a&&X[i]+X[a-1]>=l_add)a--;
        while(b&&X[i]+X[b-1]>r_add)b--;
        while(c<n&&X[c]+l_sub<=X[i])c++;
        while(d<n&&X[d]+r_sub<X[i])d++;
        if(std::max(a,d)<std::min(b,c))return true;
    }
    return false;
}
int main()
{
#ifdef MYEE
    freopen("QAQ.in","r",stdin);
    freopen("QAQ.out","w",stdout);
#endif
    scanf("%u%lld",&n,&c);
    for(uint i=1;i<n;i++)scanf("%lld",X+i),X[i]+=X[i-1];
    for(uint i=0;i<n;i++)scanf("%lld",A+i),B[i]=A[i]-X[i],A[i]+=X[i];
    MaxPreB[0]=MaxSufA[0]=-1e18;
    for(uint i=1;i<n;i++)_max(MaxPreB[i]=MaxPreB[i-1],B[i-1]);
    for(uint i=n-1;i;i--)_max(MaxSufA[i-1]=MaxSufA[i],A[i]);
    S={{A[0],B[0]}};
    for(uint i=1;i<n;i++)
    {
        T.push_back({S.back().second+A[i],S.back().first+B[i]});
        if(S.back().first>=A[i])continue;
        while(S.size()&&S.back().second<=B[i])S.pop_back();
        S.push_back({A[i],B[i]});
    }
    llt l=0,r=X[n-1]+2000000000;
    while(l<r){llt mid=(l+r)>>1;if(check(mid))r=mid;else l=mid+1;}
    printf("%lld\n",l);
    return 0;
}
```



---

## 作者：蒟蒻丁 (赞：7)

[洛谷地址](https://www.luogu.com.cn/problem/P6167)//[UOJ地址](https://uoj.ac/problem/237)  
[更好体验！！](https://www.cnblogs.com/caijiLYC/p/14384106.html)
## 题意描述
在一个 $n$ 个点的链上，每个点下面挂了一条长度为 $d_i$ 的边  
现在可以添加一条边连接两个链上的点，这条边长度为 $c$，现在要使直径最小
## 题解
$IOI$ ~~题目被 $wc$ 老师五分钟带过……~~  
~~本站第一个过真爽~~  
首先求出每个点到第一个点的距离，设其为 $L$，那么每两点间的最短路就是 $L_j-L_i+d_i+d_j$  
若在 $a,b$ 两点间添加一条边，那么 $i,j$ 间的距离就变成 $|L_i-L_a|+|L_j-L_b|+d_i+d_j$  
那么这个时候我们想找到 $min(式1，式2)$ 的最大值  
这个时候想到了二分一个 $M$，然后去验证这个 $M$是否可行  
对于加边前，两点距离就已经小于等于 $M$ 的，我们就没必要管他，重点是 $L_j-L_i+d_i+d_j>M$ 的  
然后我们看一下式二，既然式一不能满足限制，那么式二肯定要满足限制，也就是 $|L_i-L_a|+|L_j-L_b|+d_i+d_j \leq M$  
然后就考虑爆拆绝对值，分别求最小值再求交  
~~然后老师就默认大家都会，没有讲了~~![](https://cdn.luogu.com.cn/upload/pic/62227.png)  
其实呢，老师的意思是，把绝对值爆拆之后，把含 $a,b$ 的项移到右边去，构成约束，找到最紧的约束，这样就可以判   
于是我们来拆开这个式子看一下（分类中的小于等于和大于等于就省略掉等于了）  
### 一
* $L_j>L_b$且$L_i>L_a$
$$L_i-L_a+L_j-L_b+d_i+d_j \leq M$$
$$L_i+L_j+d_i+d_j-M \leq L_a+L_b$$
* $L_j>L_b$且$L_i<L_a$
$$L_a-L_i+L_j-L_b+d_i+d_j \leq M$$
$$L_j-L_i+d_i+d_j-M \leq L_b-L_a$$
$$L_i-L_j-d_i-d_j+M \geq L_a-L_b$$
### 二
* $L_j<L_b且L_i>L_a$
$$L_i-L_a+L_b-L_j+d_i+d_j \leq M$$
$$L_i-L_j+d_i+d_j-M \leq L_a-L_b$$
* $L_j<L_b且L_i<L_a$
$$L_a-L_i+L_b-L_j+d_i+d_j \leq M$$
$$-L_i-L_j+d_i+d_j-M \leq -L_a-L_b$$
$$L_i+L_j-d_i-d_j+M \geq L_a+L_b$$
***
~~啊,$mk$ 排版有待提升~~  
然后我们得到了一系列约束，这个时候我们发现很多符号不太统一，所以我们给第二、四种情况两边取负，这样的话 $L_a$ 就一直会是正的（然后我们会从求最大值变成求最小值）  
我们对于四种情况，把左式求出，考虑枚举一个 $j$，我们可以想到用一个线段树来找到 $L_i+d_i$ 或 $L_i-d_i$ ，似乎需要两棵树（没试过）  
这样的话时间就是 $O(nlog_nlog_n)$，还是过不去，我们还需要更好的
原课件是证明了一个单调性之后使用双指针，但是我并没有看懂，于是在网上找到了一位大佬的代码做参考，使用单调队列  
然后由于我比较菜，一眼看过去并不怀疑其正确性，所以没有研究为什么单调队列就可以了  
然后我们说一下怎么判断有没有解  
我们的 $L$ 数组肯定是单调不降的，这没问题，但是细心的小伙伴可能发现，有没有可能，第一种情况下，约束是最紧的，但是我们在该约束条件下找到的$a,b$并不满足该约束的前提（也就是 $L_j>L_b$且$L_i>L_a$ ）  
这是不可能的，因为如果不符合前提，那么爆拆绝对值之后的值就是负数，不是最优的  
最后，枚举一个 $a$，用两组 $l,r$ 分别代表两组约束,然后如果 $r1>=l1且r1>=l2$，$r2$同理，成立，那么就是有解了  
具体细节可以看代码(这次没有放毒瘤码风了)  

```
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
const ll inf=((1ll<<62)-1);
ll n,m,s[10100101],d[1010001],L,R,ans,mid;

bool check(ll sam){
	ll mx1=-inf,mx2=-inf,mn1=inf,mn2=inf,Mx=-inf,mx=d[1]-s[1];
	ll qq[1001001],l1=n+1,r1=n,l2=1,r2=0,l=1,r=1;
	qq[1]=1;
	for(ll i=2;i<=n;++i){
		if(mx+s[i]+d[i]>sam){
			mn1=min(mn1,sam-d[i]+s[i]-mx-m);
			mn2=min(mn2,sam-d[i]-s[i]-mx-m);
			while(l<=r&&d[qq[l]]-s[qq[l]]+d[i]+s[i]>sam){
				Mx=max(Mx,d[qq[l]]+s[qq[l]]);
				++l;
			}
			mx1=max(mx1,-sam+d[i]+s[i]+Mx+m);
			mx2=max(mx2,-sam+d[i]-s[i]+Mx+m);
		}
		mx=max(mx,d[i]-s[i]);
		while(r>=l&&d[i]-s[i]-d[qq[r]]+s[qq[r]]>=0)--r;
		qq[++r]=i;
	}
	if(mx1>mn1||mx2>mn2)return 0;
	for(ll i=1;i<=n;++i){//寻找 a b 
		while(l1>1&&s[l1-1]+s[i]>=mx1)--l1;
		while(r1>=l1&&s[r1]+s[i]>mn1)--r1;
		while(r2<n&&s[r2+1]-s[i]<=-mx2)++r2;
		while(l2<=r2&&s[l2]-s[i]<-mn2)++l2;
		if(l1>r1||l2>r2)continue;
		if(!(l2>r1||l1>r2))return 1;
	}
	return 0;
}

int main(){
	scanf("%lld%lld",&n,&m);
	for(ll i=2;i<=n;++i)scanf("%lld",&s[i]);
	for(ll i=1;i<=n;++i)s[i]+=s[i-1];
	for(ll i=1;i<=n;++i)scanf("%lld",&d[i]);
	L=0,R=(n+1)*(1e9);
	while(L<=R){
		mid=(L+R)>>1;
		if(check(mid))ans=mid,R=mid-1;
		else L=mid+1;
	}
	cout<<ans;
}
```

---

## 作者：zzzYheng (赞：2)

#### 题意：

现在有一条链，点编号 $1\sim n$，$i$ 和 $i+1$ 之间边的边权为 $l_i$。

点 $i$ 的下面还挂了一个儿子，与儿子边的长度为 $d_i$（$0$ 表示没有）。

你可以选择两个点 $s,t\in [1,n]$，在它们间连一条长度为 $c$ 的边。

你的目标是最小化添加边后这张图的直径。

数据范围：$n\le 10^6,1\le l_1\le 10^9,0\le d_i \le 10^9,1 \le c_i \le 10^9$。

#### 思路：

首先我们假设 $i$ 号点距离 $1$ 号点的距离为 $p_i$.

最小化两点间距离的最大值，容易想到二分答案，假设现在判定直径能否小于 $lim$.

显然距离最远的点一定是两个下挂叶子，假设它们的父亲分别是 $x$ 和 $y$（$x <y$），它们只有两种走法：直接走过去、走新加的边再过去。长度不能都大于 $lim$，对应了以下两个式子：
$$
\begin{aligned}
d_x+d_y+p_y-p_x>lim\\
d_x+d_y+|p_s-p_x|+|p_t-p_y|>lim
\end{aligned}
$$
对于下面这个式子，绝对值肯定是要拆的，但是分类讨论的方法肯定不行，因为 $s$ 和 $t$ 的位置并没有确定。但是可以考虑把 $|a-b|$ 拆成 $\max(a-b,b-a)$，而 $\max>lim$ 就等价于存在一个大于 $lim$。

所以下式等价于下面四个式子之一成立：
$$
\begin{aligned}
d_x+d_y+p_s-p_x-p_t+p_y>lim\\
d_x+d_y+p_s-p_x+p_t-p_y>lim\\
d_x+d_y-p_s+p_x+p_t-p_y>lim\\
d_x+d_y-p_s+p_x-p_t+p_y>lim\\
\end{aligned}
$$
整理一下，把和 $x,y$ 有关的放到一边，和 $s,t$ 有关的放到一边：
$$
\begin{aligned}
p_s-p_t>lim-d_x-d_y+p_x-p_y\\
p_s+p_t>lim+d_x+d_y+p_x+p_y\\
-p_s+p_t>lim-d_x-d_y-p_x-p_y\\
-p_s-p_t>lim-d_x-d_y-p_x-p_y\\
\end{aligned}
$$
所以限制就是 $d_x+d_y+p_y-p_x>lim$ 和上面四个式子之一不能同时成立。

即 $d_x+d_y+p_y-p_x>lim$ 满足时，上四式都不能成立，也就是下四式全部满足：
$$
\begin{aligned}
p_s-p_t\le lim-d_x-d_y+p_x-p_y\\
p_s+p_t\le lim+d_x+d_y+p_x+p_y\\
-p_s+p_t\le lim-d_x-d_y-p_x-p_y\\
-p_s-p_t\le lim-d_x-d_y-p_x-p_y\\
\end{aligned}
$$
容易发现不同 $(x,y)$ 对应的限制是可以合并的。对于所有满足 $d_x+d_y+p_y-p_x>lim$ 的 $x<y$ 对，统计上面四个式子每个的 $\min$ 即可，显然这是一个二维偏序问题。这样所有限制就合并成了两个对 $p_s\pm p_t$ 的范围限制。

对于这两个范围限制，假设为 $p_s+p_t\in [l_1,r_1]$ 和 $p_s-p_t\in [l_2,r_2]$。枚举 $s$ 的位置，利用双指针可以求出两个限制分别对应的对 $t$ 取值的一个区间限制，简单判一下这两个区间是否有交即可。

复杂度瓶颈在于每次二分都要做一次二维偏序，复杂度为 $\Theta(n\log^2n)$，无法通过。

考虑继续优化，对于多维偏序问题我们第一个要考虑的优化就是是否某一维偏序限制是无效的。

我们尝试去除 $x<y$ 这一维偏序。这样会多出一些满足 $x\ge y$ 且 $d_x+d_y+p_y-p_x>lim$ 的对的贡献。

这时第二个式子的含义也就变成了 $d_x$ 加上 $d_y$ 减去 $x$ 和 $y$ 之间的距离，发现如果这个值 $>lim$，那 $d_x+d_y$ 就也会 $>lim$，那无论怎么连边，一定无解。所以我们将二分下界设为 $\max d_x+d_y$，就可以避免出现这种贡献。

但我们还是不能直接做一维偏序，因为就是 $x=y$ 的情况我们还是可能多算贡献，解决方法是记录一个次小值，当最小值冲突时我们用次小值即可。

我们提前排序，每次做一维偏序的复杂度就是 $\Theta(n)$，这样总复杂度就是 $\Theta(n\log n)$。

#### 总结：

对于这种题目，最重要的就是要把条件和限制都清晰地列出来，然后一步一步地推即可。

这题一个比较重要的 $\text{trick}$ 就是 $|a-b|$ 不仅可以通过分类讨论拆，也可以直接拆为 $\max(a-b,b-a)$。

还有就是优化多维偏序一定要先考虑是否有偏序限制是无效的。

---

