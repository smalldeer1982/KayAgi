# Imbalanced Array

## 题目描述

You are given an array $ a $ consisting of $ n $ elements. The imbalance value of some subsegment of this array is the difference between the maximum and minimum element from this segment. The imbalance value of the array is the sum of imbalance values of all subsegments of this array.

For example, the imbalance value of array $ [1,4,1] $ is $ 9 $ , because there are $ 6 $ different subsegments of this array:

- $ [1] $ (from index $ 1 $ to index $ 1 $ ), imbalance value is $ 0 $ ;
- $ [1,4] $ (from index $ 1 $ to index $ 2 $ ), imbalance value is $ 3 $ ;
- $ [1,4,1] $ (from index $ 1 $ to index $ 3 $ ), imbalance value is $ 3 $ ;
- $ [4] $ (from index $ 2 $ to index $ 2 $ ), imbalance value is $ 0 $ ;
- $ [4,1] $ (from index $ 2 $ to index $ 3 $ ), imbalance value is $ 3 $ ;
- $ [1] $ (from index $ 3 $ to index $ 3 $ ), imbalance value is $ 0 $ ;

You have to determine the imbalance value of the array $ a $ .

## 样例 #1

### 输入

```
3
1 4 1
```

### 输出

```
9
```

# 题解

## 作者：Velix (赞：17)

### 题意简述

给你一个长度为 $n$ 序列 $a_i$，让你求出

$$\sum\limits_{1\leqslant i\leqslant j\leqslant n,i\neq j} {\max\limits_{i\leqslant k\leqslant j}\{a_k\}}-{\min\limits_{i\leqslant k\leqslant j}\{a_k\}}$$

---

### 转化题意

如果直接暴力统计，时间复杂度为 $O(n^3)$，显然无法承受。

所以我们需要对计算方法进行优化。

我们可以考虑对于每个 $a_i$ 它可以对多少个区间进行贡献。

这里以最大值为例。

显然，对于每一个 $a_i$，它的左端点可选区间为此图的 $[l,i]$，右端点可选区间为此图的 $[i,r]$。

![](https://cdn.luogu.com.cn/upload/image_hosting/q7imq639.png)

我们可以看到，对于节点 $a_i$，我们可以发现：

其左端点的极左点为**在该数左边且从后往前数第一个大于** $a_i$ **的数的位置**，我们将其记录为 $l_i$，特别地，如果没有比它大的，那么 $l_i$ 为 $0$；

其右端点的极有点为**在该数右边且从前往后数第一个大于** $a_i$ **的数的位置**，我们将其记录为 $r_i$，特别地，如果没有比它大的，那么 $r_i$ 为 $n+1$。

而且我们可以看到，对于每一个数，由于左右端点每个可以各选一个。由乘法原理可得每个 $a_i$ 对于答案的贡献为

$$a_i*(i-l_i)*(r_i-i)$$

最后求出每一个数对答案的贡献并求和。

---
### 单调栈优化

前面讲到了如何利用左右端点求出所有的贡献，但暴力求 $l_i$ 和 $r_i$ 的时间复杂度为 $O(n^2)$ 对于 $10^6$ 的数据范围依旧远远不够。

所以我们要祭出一个好东西：**单调栈**

单调栈，可以简单理解为不会从队头出只会从队尾出的单调队列，**但只能从队尾取出**。

也就是说我们可以省略掉 $head$（后面为了适应栈用 $head$ 代替了 $tail$）

以 $l_i$ 为例，我们可以写出递推式：

$$l_i = \max\limits_{1\leqslant j\leqslant i,a_j>a_i}\{j\}$$

但由于要取 $\max$ 所以我们必须在尾端取，这时候便可以用单调栈维护。

**详细过程：**

最开始将 $0$ 入栈；

对于每次查询，如果 $a_i>a_{stack_{head}}$，那么 $l_i=i-1$；

否则从将栈中的元素一一弹出，直到 $a_i>a_{stack_{head}}$；

将 $l_i$ 赋值为 $stack_{head}$，并将 $i$ 入栈。

---

### 一些提示

- 答案会爆 $longlong$
- **注意，求** $r_i$ **时栈顶必须大于等于** $r_i$ **而不是大于**
- 记得求 $\max$ 时将 $a_0$ 和 $a_{n+1}$ 赋值为无穷大

---

### $Code$

```cpp
#include<bits/stdc++.h>
using namespace std;
int sta[1000002],a[1000002],n,mxl[1000001],mxr[1000001],mil[1000001],mir[1000001],h;
long long ans;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	sta[1]=0;h=1;
	for(int i=1;i<=n;i++)
	{
		if(a[i]>a[sta[h]])sta[++h]=i,mil[i]=i-1;
		else
		{
			while(a[i]<a[sta[h]])h--;
			mil[i]=sta[h];
			sta[++h]=i;
		}
	}
	sta[1]=n+1;h=1;
	for(int i=n;i>=1;i--)
	{
		if(a[i]>a[sta[h]])sta[++h]=i,mir[i]=i+1;
		else
		{
			while(a[i]<=a[sta[h]])h--;
			mir[i]=sta[h];
			sta[++h]=i;
		}
	}
	a[0]=a[n+1]=0x7fffffff;
	sta[1]=0;h=1;
	for(int i=1;i<=n;i++)
	{
		if(a[i]<a[sta[h]])sta[++h]=i,mxl[i]=i-1;
		else
		{
			while(a[i]>a[sta[h]])h--;
			mxl[i]=sta[h];
			sta[++h]=i;
		}
	}
	sta[1]=n+1;h=1;
	for(int i=n;i>=1;i--)
	{
		if(a[i]<a[sta[h]])sta[++h]=i,mxr[i]=i+1;
		else
		{
			while(a[i]>=a[sta[h]])h--;
			mxr[i]=sta[h];
			sta[++h]=i;
		}
	}
	//for(int i=1;i<=n;i++)
		//cout<<mil[i]<<' '<<mir[i]<<' '<<mxl[i]<<' '<<mxr[i]<<endl; 
	for(int i=1;i<=n;i++)
		ans+=1ll*a[i]*(1ll*(i-mxl[i])*(mxr[i]-i)-1ll*(i-mil[i])*(mir[i]-i));
	cout<<ans;
}
```


---

## 作者：Provicy (赞：9)

**题目大意：** 求一个序列的所有连续的子序列中的 **最大值之和** 与 **最小值之和** 的差值。

最朴素的方法当然是枚举区间的左右端点，然后最大值和最小值求一下，但是这个时间复杂度显然过不了此题。

考虑不去枚举每个区间。实际上，这个长度为 $n$ 的序列的 $\frac{n(n+1)}{2}$ 个位置不同的子区间最多只会产生 $n$ 种不同的最大值和最小值。这个数量级就比较小了，所以我们可以考虑每个位置上的数 $a_{i}$ 会给多少区间产生贡献。

**假设我们现在要求的是最大值之和**。对于第 $i$ 个位置，如果有一个区间包含了第 $i$ 个位置，则这个区间里其他的位置上的数都比 $a_{i}$ 小（如果和 $a_{i}$ 相等的话会重复计算）。那么这个区间怎么选是合法的呢？假设这个区间是 $[j,k]$ 。那么首先满足的条件是 $j\leq i$ 且 $i\leq k$。同时，还需要满足：

$$\sum_{x=j}^{k}[a_{x}\geq a_{i}]=1\text{（只有 x=i 时满足条件）}\qquad$$

那么我们现在要求出的就是 $1\leq x< i$ 中，满足 $a_{x}\geq a_{i}$ 且 $x$ 最大的 $x$ 与 $i<y\leq n$ 中，满足 $a_{y}\geq a_{i}$ 且 $y$ 最小的 $y$。特殊的，如果 $x$ 不存在，令 $x=1$；如果 $y$ 不存在，令 $y=n$。这个东西很显然就是可以用单调栈求出来了，最终答案利用乘法原理统计即可。

求最小值之和也是同理。（本篇题解注重如何思考到利用单调栈）

代码如下：

```cpp
#include <bits/stdc++.h>
#define ri register
#define inf 0x7fffffff
#define E (1)
#define int long long
using namespace std; const int N=1000010;
inline int read()
{
	int s=0, w=1; ri char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') w=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48), ch=getchar(); return s*w;
}
int n,q,a[N],ql[N],qr[N],sta[N],tp,ans;
signed main()
{
	n=read();
	for(ri int i=1;i<=n;i++) a[i]=read();
	for(ri int i=1;i<=n;i++)
	{
		while(tp&&a[i]>=a[sta[tp]]) qr[sta[tp--]]=i-1;
		ql[i]=sta[tp]+1; sta[++tp]=i;
	}
	while(tp) qr[sta[tp--]]=n;
	for(ri int i=1;i<=n;i++) ans+=(i-ql[i]+1)*(qr[i]-i+1)*a[i];
	memset(ql,0,sizeof(ql)), memset(qr,0,sizeof(qr));
	for(ri int i=1;i<=n;i++)
	{
		while(tp&&a[i]<=a[sta[tp]]) qr[sta[tp--]]=i-1;
		ql[i]=sta[tp]+1; sta[++tp]=i;
	}
	while(tp) qr[sta[tp--]]=n;
	for(ri int i=1;i<=n;i++) ans-=(i-ql[i]+1)*(qr[i]-i+1)*a[i];
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Karry5307 (赞：7)

### 题意

给定一个长度为 $n$ 的序列 $a$，求：

$$\sum\limits_{l=1}^{n}\sum\limits_{r=l}^{n}\max_{i=l}^{r}(a_i)-\sum\limits_{l=1}^{n}\sum\limits_{r=l}^{n}\min_{i=l}^{r}(a_i)$$

$\texttt{Data Range:}1\leq n\leq 10^6$

### 题解

大家好，我喜欢暴力，所以我用 $O(n\log n)$ 的东西 1996ms 水过了本题。

首先以求最大值为例。如果求每个区间对应的最大值肯定 T 飞，换一个思路，改成对于每个值求以这个值作为最大值的区间数量。

考虑从大到小加入每一个值。对于当前加入的位置 $x$ 的值，用 set 存比他大的所有值，这样可以二分出这个值最远能够影响到的两个位置 $l$ 和 $r$。左端点只能在 $l+1\sim x$ 里面选一个，右端点只能在 $x\sim r-1$ 里面选一个，于是就能算出来贡献了。

当然找左右端点的过程是可以单调栈的，具体可以见模板题。~~然而这个做法不开 O2 能够 AC，开了 O2 会 TLE……~~

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=1e6+51;
set<ll>st;
ll n,prv,nxt;
li mx,mn;
ll x[MAXN],c[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
int main()
{
	n=read(),st.insert(0),st.insert(n+1);
	for(register int i=1;i<=n;i++)
	{
		x[i]=read(),c[i]=i;
	}
	sort(c+1,c+n+1,[&](ll u,ll v){return x[u]>x[v];});
	for(register int i=1;i<=n;i++)
	{
		prv=*(--st.lower_bound(c[i])),nxt=*(st.lower_bound(c[i]));
		mx+=(li)(c[i]-prv)*(nxt-c[i])*x[c[i]],st.insert(c[i]);
	}
	st.clear(),st.insert(0),st.insert(n+1);
	for(register int i=n;i;i--)
	{
		prv=*(--st.lower_bound(c[i])),nxt=*(st.lower_bound(c[i]));
		mn+=(li)(c[i]-prv)*(nxt-c[i])*x[c[i]],st.insert(c[i]);
	}
	printf("%lld\n",mx-mn);
}
```

---

## 作者：zhengrunzhe (赞：6)

提供一个比较简洁的代码

考虑增量法 末尾添加一个数算出它的贡献

考虑多出来了哪些空间 假如插入第k个数(已经插了前k-1个）

多了$[1,k],[2,k],[3,k] \cdots [k,k]$这些区间 考虑更新答案

每个位置$i$当前状态下(要插入k)的权值为$[i,k]$的$\max-\min$ 考虑实时维护出这个东西

经典地，维护两个单调栈 一个单调递减一个单调递增 分别代表max和min

单调栈(以max栈为例)里的性质是 栈里的某个位置$stack[i],\max(stack[i-1],stack[i]]=a[stack[i]]$ 也就是栈里的前个数是它左边第一个比它大的数

同时 栈单调递减 区间$[stack[i],k],[stack[i]-1,k],[stack[i]-2,k]\cdots [stack[i-1]+1,k]$这些区间的max都是$a[stack[i]]$

这样我们就可以通过单调栈实时维护每个位置到末尾的max和min

插入k进来 会弹掉栈里的一些数 表明这些区间的max/min因k发生变化 先扣掉这些区间的原答案 也就是弹掉$stack[i]$时，区间$[stack[i-1]+1,stack[i]]$扣去原本的max,即$a[stack[i]]$，min同理，只不过是加上

然后弹掉之后的栈顶+1到k这些区间的max/min变成了$a[k]$

就发现实质在实现一个区间加(减)

题目要求求所有区间答案的和 所以我们并不关心每个位置的答案具体是多少，区间加 区间求和，这种操作是不需要数据结构的，开个全局变量表示当前状态下序列的答案和就行了

整理一下,max栈记作s1栈顶记作top1，min栈记作s2栈顶记作top2，当前的和记作sum，总答案记作ans,插入位置k时：

弹栈过程中：

$1.sum-=(s1[top1]-s1[top1-1])*a[s1[top1]]$

$2.sum+=(s2[top2]-s2[top2-1])*a[s2[top2]]$

弹栈后：

$3.sum+=(k-s1[top1])*a[k]$

$4.sum-=(k-s2[top2])*a[k]$

$5.ans+=sum$

然后把k插入s1,s2

时空复杂度:$O(n)$
```cpp
#include<cstdio>
template<class type>inline const void read(type &in)
{
	in=0;char ch(getchar());
	while (ch<48||ch>57)ch=getchar();
	while (ch>47&&ch<58)in=(in<<3)+(in<<1)+(ch&15),ch=getchar();
}
typedef long long ll;
const int N(1e6+5);
int n,a[N],s1[N],top1,s2[N],top2;
ll ans,sum;
inline const void insert(const int k)
{
	for (;top1&&a[k]>=a[s1[top1]];top1--)sum-=1ll*(s1[top1]-s1[top1-1])*a[s1[top1]];
	for (;top2&&a[k]<=a[s2[top2]];top2--)sum+=1ll*(s2[top2]-s2[top2-1])*a[s2[top2]];
	if (k>1)
		sum+=1ll*(k-1-s1[top1])*a[k],
		sum-=1ll*(k-1-s2[top2])*a[k];
	s1[++top1]=k;s2[++top2]=k;
	ans+=sum;
}
int main()
{
	read(n);
	for (int i(1);i<=n;i++)read(a[i]);
	for (int i(1);i<=n;i++)insert(i);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：SentoAyaka (赞：6)

## [CF817D Imbalanced Array](https://www.luogu.com.cn/problem/CF817D)解题报告

### 题意:

对于给定由 $n$ 个元素构成的数组
求出

$$
	\sum_{1 \leq i< j \leq n}a_{max}-a_{min}
$$

### 分析：

由于 $n<=1e6$ ，枚举每个区间显然不行，考虑转换思路，
对于每个数$a_i$，他能对哪些区间产生贡献，

画图可发现，对于$a_i$向右延伸，直到第一次$a_{j+1}>a_{i}$的区间 $i$~$j$, $a_i$都是其最大值
，向左同理。
那么，对于$i$，假设$l-1$，$r+1$的 a 值向左，向右第一次大于他的下标，那么i能产生的贡献为：
$$ a_i*(i-l+1)*(r-i+1) $$
如何理解:向左可选$0$~$(i-l+1)$个，向右可选$0$~$(r-i+1)$个，乘法原理得出结果。

（由最小值为例）
将$a_i$从大到小排序
对于排序后的下标i，
若是其 $i-1$ 在$i$前面，即$a_{i-1}>a_i$,那么对于 $i-1 $所能贡献的区间，$i$都能贡献，即将$i$的左界拓展为$i-1$所在的左界，右边同理。
那么如何知道$i-1$所在的界限呢，考虑使用**并查集**维护
，每次找到$i-1$,$i+1$所在联通的区间，$i$的界限拓展到联通块管辖区间的界限，并更新联通块

```cpp
sort(a+1,a+1+n,cmp2);
for(int i=1;i<=n;i++){
    int now=a[i].i;//找到a下标
    vis[now]=i;a[i].l=a[i].r=now;
    if(vis[now-1]){//a[i-1]>a[i]
       	a[i].l=a[find(vis[now-1])].l;fa[find(vis[now-1])]=i;
    }
    if(vis[now+1]){//a[i+1]>a[i]
     	a[i].r=a[find(vis[now+1])].r;fa[find(vis[now+1])]=i;
    }
    ans-=1LL*(now-a[i].l+1)*(a[i].r-now+1)*a[i].s;
}
    
```

### 代码：

```cpp

const int N=1e6+5;
int n,m,vis[N],fa[N];
long long ans;
struct node{
	int s,i,l,r;
}a[N];
bool cmp1(node a,node b){
	return a.s<b.s;
}
bool cmp2(node a,node b){
	return a.s>b.s;
}
int find(int k){
	if(fa[k]==k)return k;
	else return fa[k]=find(fa[k]);
}
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i].s=read();a[i].i=i;
	}
	memset(fa,0,sizeof fa);memset(vis,0,sizeof vis);
    sort(a+1,a+1+n,cmp1);
    for(int i=1;i<=n;i++)fa[i]=i;
    for(int i=1;i<=n;i++){
        int now=a[i].i;
        vis[now]=i;a[i].l=a[i].r=now;
        if(vis[now-1]){
        	a[i].l=a[find(vis[now-1])].l;fa[find(vis[now-1])]=i;
        }
        if(vis[now+1]){
        	a[i].r=a[find(vis[now+1])].r;fa[find(vis[now+1])]=i;
        }
        ans+=1LL*(now-a[i].l+1)*(a[i].r-now+1)*a[i].s;
    }
    memset(fa,0,sizeof fa);memset(vis,0,sizeof vis);
    sort(a+1,a+1+n,cmp2);
    for(int i=1;i<=n;i++)fa[i]=i;
    for(int i=1;i<=n;i++){
        int now=a[i].i;
        vis[now]=i;a[i].l=a[i].r=now;
        if(vis[now-1]){
        	a[i].l=a[find(vis[now-1])].l;fa[find(vis[now-1])]=i;
        }
        if(vis[now+1]){
        	a[i].r=a[find(vis[now+1])].r;fa[find(vis[now+1])]=i;
        }
        ans-=1LL*(now-a[i].l+1)*(a[i].r-now+1)*a[i].s;
    }
    cout<<ans;
	return 0;
} 

```



---

## 作者：xixiup (赞：5)

### 题解背景

这道题很多人都是单调栈做的，然而我要提供一个新的思路——并查集。

没错，就是并查集。

### 思路分享

对于 $10^6$ 级别的数据，我们显然不能直接处理出每种情况，所以我们要使用贡献的思想。

我们现在以最大值为例，思考对于某一个节点的贡献。

不妨设点 $i$ 的贡献为 $con_i$。

以下图为例，对于图中的节点 $i$，假设区间 $\left[l,r\right]$，对于任意 $j\in\left[l,r\right]$ 且 $j \not= i$，都有：$a_j<a_i$。那么，$con_i$ =区间 $\left[l,r\right]$ 中所有包含点 $i$ 的子串的数量 × $ a_i$。

![](https://cdn.luogu.com.cn/upload/image_hosting/w8k9aice.png)

转换成公式即为：$\boxed{con_i=(i-l+1)\times(r-i+1)\times a_i}$

其实到目前为止都和单调栈的做法相似。但接下来就是并查集了。

考虑如何对于每一个节点求出 $l$ 与 $r$，可以运用转换法的思想，将点的权值假设为某一个点的高度，然后就可以观察图像。

![](https://cdn.luogu.com.cn/upload/image_hosting/1a0iiih9.png)

可以发现，对于一定的高度 $hi$ 来说，会有几个高度大于 $hi$ 的节点将这些区间分为几个部分，故我们可以从小到大搜索每一个节点，然后如果一侧节点的权值要小于这个点的权值，那么就可以将这两个点合并到同一个并查集中。

而最小值则同理。

最后答案即为 $\boxed{\sum\limits_{i=1}^n maxcon_i-mincon_i}$。

其中 $maxcon_i$ 指 $i$ 作为最大值时的贡献，$mincon_i$ 指 $i$ 作为最小值时的贡献。

### 代码展示

注释已放在代码中

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e6+1000;
int n,nu[maxn],fa[maxn],le[maxn],ri[maxn];
//nu[i]表示a[i]，le[i]、ri[i]分别表示该并查集的左、右边界
struct node1{
	int hi,loc;
	bool operator <(node1 u){
		return hi==u.hi?loc<u.loc:hi<u.hi;
	}
}ma[maxn];
struct node2{
	int hi,loc;
	bool operator <(node2 u){
		return hi==u.hi?loc<u.loc:hi>u.hi;
	}
}mi[maxn];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
int work_ma(){
	int sum=0;
	for(int i=1;i<=n;i++){
		ma[i].hi=nu[i];
		ma[i].loc=i;
		fa[i]=le[i]=ri[i]=i;
	}//初始化并查集
	sort(ma+1,ma+1+n);
	for(int i=1;i<=n;i++){
		int x=ma[i].loc;
		int y=x-1;
		int fx=find(x);
		if(y>=1&&nu[y]<=nu[x]){
			int fy=find(y);
			fa[fy]=fx;//更新并查集
			le[fx]=min(le[fx],le[fy]);
			ri[fx]=max(ri[fx],ri[fy]);
		}
		y=x+1;
		if(y<=n&&nu[y]<nu[x]){
			int fy=find(y);
			fa[fy]=fx;//更新并查集
			le[fx]=min(le[fx],le[fy]);
			ri[fx]=max(ri[fx],ri[fy]);
		}
		sum+=(x-le[fx]+1)*(ri[fx]-x+1)*nu[x];计算贡献
	}
	return sum;
}
int work_mi(){
	int sum=0;
	for(int i=1;i<=n;i++){
		mi[i].hi=nu[i];
		mi[i].loc=i;
		fa[i]=le[i]=ri[i]=i;
	}//初始化并查集
	sort(mi+1,mi+1+n);
	for(int i=1;i<=n;i++){
		int x=mi[i].loc;
		int y=x-1;
		int fx=find(x);
		if(y>=1&&nu[y]>=nu[x]){
			int fy=find(y);
			fa[fy]=fx;//更新并查集
			le[fx]=min(le[fx],le[fy]);
			ri[fx]=max(ri[fx],ri[fy]);
		}
		y=x+1;
		if(y<=n&&nu[y]>nu[x]){
			int fy=find(y);
			fa[fy]=fx;//更新并查集
			le[fx]=min(le[fx],le[fy]);
			ri[fx]=max(ri[fx],ri[fy]);
		}
		sum+=(x-le[fx]+1)*(ri[fx]-x+1)*nu[x];//计算贡献
	}
	return sum;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%lld",&nu[i]);
	}
	cout<<work_ma()-work_mi();
	return 0;
}
```


---

## 作者：AFOier (赞：4)

好像题解里没有分治做法，我来交一发.

我们对序列进行分治，统计满足$l\leq mid<r$的区间$[l,r]$的答案.

分到的每一层都有四种情况：

1.$maxn$和$minn$都在区间$[l,mid]$中.

2.$maxn$和$minn$都在区间$[mid+1,r]$中.

3.$maxn$在区间$[l,mid]$中，$minn$在区间$[mid+1,r]$中.

4.$maxn$在区间$[mid+1,r]$中，$minn$在区间$[l,mid]$中.

对于1,3情况，枚举$i \in [l,mid]$，再在$[mid+1,r]$中拓展解.

对于2,4情况则反之.

我们发现1,3情况中我们实际维护的是一个只进不出的队列，2,4情况中我们实际维护的是一个普通队列，于是分别统计答案即可.

注：统计答案时为了避免算重，我们规定相同的数左边的总比右边的小.

时间复杂度$O(n\log n)$.

```
#include <bits/stdc++.h>
#define ll long long 
using namespace std;
int n;
ll ans, a[1000011], Min[1000011];
void solve(int l, int r) {
	if(l == r) return;
	int mid = (l + r) >> 1, w;
	ll minn, maxn; //维护的是当前枚举的区间中的最大值和最小值
	minn = maxn = a[mid]; w = mid;
	for(int i = mid; i >= l; i--) {
		minn = min(minn, a[i]);
		maxn = max(maxn, a[i]);
		while(a[w+1] < maxn && a[w+1] >= minn && w < r) ++ w;
		ans += (maxn - minn) * (w - mid); 
	} //1.maxn和minn都在[l,mid]内 
	minn = maxn = a[mid+1]; w = mid+1;
	for(int i = mid+1; i <= r; i++) {
		minn = min(minn, a[i]);
		maxn = max(maxn, a[i]);
		while(a[w-1] <= maxn && a[w-1] > minn && w > l) -- w;
		ans += (maxn - minn) * (mid - w + 1);
	} //2.maxn和minn都在[mid+1,r]内 
	int L, R; ll sum = 0; Min[mid] = 1e9;
	minn = maxn = a[mid]; L = mid+1; R = mid;
	for(int i = mid; i >= l; i--) {
		minn = min(minn, a[i]);
		maxn = max(maxn, a[i]);
		while(a[R+1] < maxn && R < r) {
			++ R; Min[R] = min(Min[R-1], a[R]);
			sum += Min[R];
		}
		while(L <= R && Min[L] >= minn) { 
			sum -= Min[L];
			++ L;
		}
		ans += maxn * (R - L + 1) - sum;
	} //3.maxn在[1,mid]内，minn在[mid+1,r]内
	minn = maxn = a[mid+1]; Min[mid+1] = 1e9;
	L = mid+1; R = mid; sum = 0;
	for(int i = mid+1; i <= r; i++) {
		minn = min(minn, a[i]);
		maxn = max(maxn, a[i]);
		while(a[L-1] <= maxn && L > l) {
			-- L; Min[L] = min(Min[L+1], a[L]);
			sum += Min[L];
		}
		while(R >= L && Min[R] > minn) {
			sum -= Min[R];
			-- R;
		}
		ans += maxn * (R - L + 1) - sum;
	} //4.maxn在[mid+1,r]内，minn在[l,mid]内
	//默认靠左的更小 
	solve(l, mid); solve(mid+1, r);
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	solve(1, n);
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：JA_yichao (赞：4)

推荐[博客食用](https://blog.csdn.net/Jackma_mayichao/article/details/107950239) ~~（更好看）~~
## 题目大意
给你个 $a$ 序列, 求 $a$ 序列的任意连续子序列中最大值 $-$ 最小值的值的和。 
## 本题思路
**~~当然~~用单调栈做！**

对于 $a[i]$ 里的每个数，

求出此点在哪个区间是最大值和是最小值。怎么求？

我们以当前点为中心，**分左右**用 $while$ 扩展，

如果**此点最小就单调递增**，

如果**此点最大就单调递减**。

直到不能求为止，求完后得到 $[l....i....r]$，

最后统计答案（乘法原理）

最大：$ans+=a[i]×(i-L[i])×(R[i]-i)$

最小：$ans-=a[i]×(i-L[i])×(R[i]-i)$

### 注意

 - 左右区间可能会有**重复数字**，所以扩展时的判断条件有不同（为了**判重**）
```cpp
while(a[z[tail]]<=a[i])  //允许相同数进来
while(a[z[tail]]<a[i])   //不允许相同数进来（判重）
```

- 每次处理前要**初始化**（注意要放墙，不同情况的墙有所不同）

- 统计 $ans$ 要统计**两次**，一次最大一次最小

- 如果是向右扩展，就要从 $n-1$ 枚举

## 代码：

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;
long long maxl[100010],maxr[100010];
long long minl[100010],minr[100010];
long long a[100010],z[100010];
long long n,tail,ans;
int main()
{
    cin>>n;
    for(long long i=1; i<=n; i++)
       scanf("%lld",&a[i]);
    a[0]=2147483647;   //初始化
    tail=1;
    z[1]=0;
    for(long long i=1; i<=n; i++)     //以此数为最大向左扩展
     {
     	while(a[z[tail]]<=a[i]) //找比当前数小的数
          tail--;
        maxl[i]=z[tail];
        z[++tail]=i;
     }
    a[n+1]=2147483647;
    tail=1;
    z[1]=n+1;
    for(long long i=n; i>=1; i--)     //以此数为最大向右扩展
     {
     	while(a[z[tail]]<a[i])
          tail--;
        maxr[i]=z[tail];
        z[++tail]=i;
     }
	a[0]=-2147483647;
    tail=1;
    z[1]=0;
    for(long long i=1; i<=n; i++)
       ans+=a[i]*(i-maxl[i])*(maxr[i]-i); 
    for(long long i=1; i<=n; i++)     //以此数为最小向左扩展
     {
     	while(a[z[tail]]>=a[i])
          tail--;
        minl[i]=z[tail];
        z[++tail]=i;
     }
	a[n+1]=-2147483647;
    tail=1;
    z[1]=n+1;
    for(long long i=n; i>=1; i--)     //以此数为最小向右扩展
     {
     	while(a[z[tail]]>a[i])
          tail--;
        minr[i]=z[tail];
        z[++tail]=i;
     }
    for(long long i=1; i<=n; i++)
       ans-=a[i]*(i-minl[i])*(minr[i]-i);
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Algha_Porthos (赞：3)

首先，Orz _DXL\_ .

然后冷静分析,发现这是一道比较玄学的题目。

**题目实际上是给定一个数组，求每一个区间的最大值最小值的差的总和。**

~~然后$\Theta(N^2logN)$水过。~~

对于1e6级别的数据，我们需要另辟蹊径：**求贡献**。

我们可以发现，“求（每一个区间的最大值最小值的差）的总和”（括号代表断句），

可以转化为“求（每一个区间的最大值的总和）与（每一个区间的最小值的总和）的差”，

又可以转化为“求每一个数字作为最大值和最小值的次数，两者乘上权，再求差，再求和”。

然后问题就迎刃而解。

进入代码部分。

这道题是用单调栈来求贡献。这是一个相当经典的模型。

![pic1](http://47.103.204.220/picture_bed/uploads/2020/02/CF817D1.png)

假如每个竖的线段的高度代表每一个数值，我们当前要求最大值得总和。那么我们需要考虑红的和绿的分别会作为哪些区间的最大值。

红：(2,2)

绿：(2,4)(3,4)(4,4)(2,5)(3,5)(4,5)

我们发现，作为区间最大值的区间数量其实就是

到左边“靠山”的距离  乘上  到右边的“靠山”的距离。


![pic2](http://47.103.204.220/picture_bed/uploads/2020/02/CF817D2.png)

读者自证不难。同时，对于求最小值总和，由于不方便形象举例，读者自行推导（反正就是大小于号换一下）。

## 代码

加一的细节卡了我好久，希望大家注意一下。

需要注意的是，如果所有元素都遍历完了，还有元素在单调栈里，我们需要在$n+1$的位置放一个“巨型靠山”，否则会出错。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1050005;
int n,st[N],a[N],b[N],pos[N],top=0;
int ans=0;
int sum_max,sum_min;
int Left[N],Right[N];
signed main(){
	cin>>n;
	for(int i=1;i<=n;++i)
		scanf("%lld",&a[i]);
//--------------以下是计算最大值贡献--------------
	for(int i=1;i<=n;++i){
		while(top!=0&&st[top]<a[i]){//单调栈的维护。st[]表示单调栈，存放元素的具体数值。top表示顶指针。 
			Right[pos[top]]=i-pos[top];//Right[]是右边的靠山。pos[i]表示st[i]的元素在a[]数组中的下标。 
			top--;
		}
		Left[i]=i-pos[top];//Left[]是左边的靠山。
		st[++top]=a[i];//元素入栈 
		pos[top]=i;
	}
	while(top)//栈内剩余元素处理（巨型靠山）
		Right[pos[top]]=n+1-pos[top],top--;
	for(int i=1;i<=n;++i)//计算贡献 
		sum_max+=(a[i]*(Left[i])*(Right[i]));
	
//-----以下是计算最小值贡献（就minmax换一下，改个大小于号。具体的参考上面。 
	memset(Left,0,sizeof(Left));
	memset(Right,0,sizeof(Right));
	for(int i=1;i<=n;++i){
		while(top!=0&&st[top]>a[i]){
			Right[pos[top]]=i-pos[top];
			top--;
		}
		Left[i]=i-pos[top];
		st[++top]=a[i];
		pos[top]=i;
	}
	while(top)
		Right[pos[top]]=n+1-pos[top],top--;
	for(int i=1;i<=n;++i)
		sum_min+=(a[i]*(Left[i])*(Right[i]));
		
	cout<<sum_max-sum_min<<endl;//输出 
}
```

注释都在上面了。有问题可以博客提问，或者私信提问！

## 鸣谢

感谢洛谷提供评测和博客服务。

感谢ISP项目组提供私人图床服务。

---

## 作者：shengnan (赞：2)

题意：求一个序列所有子区间最大值减最小值之和



首先：暴力做法就是枚举左右端点，用st表求区间最值相减，即可算出每个区间的贡献，然后相加即可。



发现：如果我们从每一个区间的贡献度考虑，那么需要枚举左右端点，$O$($n^2$) 起步，所以，直接求每个区间的贡献行不通



再分析题目，寻找突破口：求每个区间的最值——实际上，可能有几个包含  $a$[$i$]  子区间的最大值都是  $a$[$i$]  ，也就是说，我们是否可以**不必枚举每个区间求它的最大值，而是考虑每一个元素在哪些子区间是最大值**（最小值同理）。请仔细思考这一把求区间贡献转为求单个元素贡献的思考过程，这是复杂度从 $O$($n^2$) 降为 $O$($n$) 的关键。



考虑怎么求单个元素的贡献，也就是一个数 $a$[$i$] 在哪些范围内是该区间的最值？（下面以最大值为例，最小值同理）



所以，我们要找从  $a$[$i$]  开始往右第一个比  $a$[$i$]  大的数   $a$[$j$]  ，从  $a$[$i$]  开始往左第一个比  $a$[$i$]  大的数   $a$[$k$]  ，那么在  $a$[$j$]  到  $a$[$k$]  内的所有包含  $a$[$i$]  的子区间，最大值都是  $a$[$i$]  ，这可以用**单调栈**来实现。这样，左端点可以是在  $j$  ~  $i$  任意一个，右端点可以是在  $i$  ~  $k$  任意一个，根据乘法原理，即可求出答案。

AC代码：
```c
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,a[1000005],top,s[1000005],l[1000005][2],r[1000005][2],ans;
signed main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++){
        while(top&&a[i]<a[s[top]])--top;
        l[i][0]=i-s[top];s[++top]=i;
    }
    memset(s,0,sizeof(s));top=0;s[0]=n+1;
    for(int i=n;i>=1;i--){
        while(top&&a[i]<=a[s[top]])top--;
        r[i][0]=s[top]-i;s[++top]=i;
    }
    memset(s,0,sizeof(s));top=0;s[0]=0;
    for(int i=1;i<=n;i++){
        while(top&&a[i]>=a[s[top]])top--;
        l[i][1]=i-s[top];s[++top]=i;
    }
    memset(s,0,sizeof(s));top=0;s[0]=n+1;
    for(int i=n;i>=1;i--){
        while(top&&a[i]>a[s[top]])top--;
        r[i][1]=s[top]-i;s[++top]=i;
    }
    for(int i=1;i<=n;i++)ans+=(l[i][1]*r[i][1])*a[i],ans-=(l[i][0]*r[i][0])*a[i];
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：RedLycoris (赞：2)

实质上这题可以用4棵不同的树状数组莽过去

大致思路其他的题解已经讲的很清楚了，这里就讲讲树状数组的不同写法和作用。

比如这道题，我写的第1、2、3、4棵线段树，作用分别是：

1，求左端后缀最大值

2，求右端后缀最小值

3，求左端前缀最大值

4，求右端前缀最小值

如果是要处理前缀的话，我们的 add 函数 和 ask 函数 应该这么写：

```cpp
	inline void add(int x,int d){for(;x<mxn;x+=x&-x)val[x]=max(val[x],d);}  //add 往后 让后面的数在ask时能够处理到它
	inline int ask(int x){  //ask 往前
		int rt=0;
		for(;x;x-=x&-x)rt=max(rt,val[x]);
		return rt;
	}
```

反之，如果是处理后缀的话：

```cpp
	inline void add(int x,int d){for(;x;x-=x&-x)val[x]=max(val[x],d);}//add往前
	inline int ask(int x){//ask往后
		int rt=0;
		for(;x<mxn;x+=x&-x)rt=max(rt,val[x]);
		return rt;
	}
```

此外，这题还有个小问题，样例以就很好的体现了：在两个数相同的时候，且它们都可以作为最小/大值，那么，他们的贡献就会被多次计算。

其实没有太大的关系，因为我们可以钦定如果两个数相同，前面的数大于后面的数，就可以处理掉这种情况了。实现的话就是在 ask 左端时 ask $a_i$ 而在 ask 右端时 ask $a_i +1$ 或 $a_i -1$ 即可。

---

Code:

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mp make_pair
using namespace std;
const int mxn=1e6+6;
int a[mxn],n;
struct fenwick1{
	int val[mxn];
	inline void init(){memset(val,0,sizeof(val));}
	inline void add(int x,int d){for(;x;x-=x&-x)val[x]=max(val[x],d);}
	inline int ask(int x){
		int rt=0;
		for(;x<mxn;x+=x&-x)rt=max(rt,val[x]);
		return rt;
	}
}f1;
struct fenwick2{
	int val[mxn];
	inline void init(){for(int i=0;i<mxn;++i)val[i]=n+1;}
	inline void add(int x,int d){for(;x;x-=x&-x)val[x]=min(val[x],d);}
	inline int ask(int x){
		int rt=n+1;
		for(;x<mxn;x+=x&-x)rt=min(rt,val[x]);
		return rt;
	}
}f2;
struct fenwick3{
	int val[mxn];
	inline void init(){memset(val,0,sizeof(val));}
	inline void add(int x,int d){for(;x<mxn;x+=x&-x)val[x]=max(val[x],d);}
	inline int ask(int x){
		int rt=0;
		for(;x;x-=x&-x)rt=max(rt,val[x]);
		return rt;
	}
}f3;
struct fenwick4{
	int val[mxn];
	inline void init(){for(int i=0;i<mxn;++i)val[i]=n+1;}
	inline void add(int x,int d){for(;x<mxn;x+=x&-x)val[x]=min(val[x],d);}
	inline int ask(int x){
		int rt=n+1;
		for(;x;x-=x&-x)rt=min(rt,val[x]);
		return rt;
	}
}f4;
int BiggerL[mxn],BiggerR[mxn];
int SmallerL[mxn],SmallerR[mxn];
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i)cin>>a[i];
	f1.init(),f2.init(),f3.init(),f4.init();
	for(int i=1;i<=n;++i){
		BiggerL[i]=f1.ask(a[i]);
		f1.add(a[i],i);
	}
	for(int i=n;i;--i){
		BiggerR[i]=f2.ask(a[i]+1);
		f2.add(a[i],i);
	}
	for(int i=1;i<=n;++i){
		SmallerL[i]=f3.ask(a[i]);
		f3.add(a[i],i);
	}
	for(int i=n;i;--i){
		SmallerR[i]=f4.ask(a[i]-1);
		f4.add(a[i],i);
	}
	ll ans=0;
	for(int i=1;i<=n;++i){
		ans+=a[i]*1ll*(i-BiggerL[i])*(BiggerR[i]-i);
		ans-=a[i]*1ll*(i-SmallerL[i])*(SmallerR[i]-i);
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：yzh_Error404 (赞：2)

## 题意

给定一个 $n$ 个元素的数组 $a$ ,求 $\sum_{1\leqslant l\leqslant r\leqslant n}a_{max}-a_{min}$。
 
## 分析

首先我们先想到复杂度 $O(n^3)$ 的暴力！

枚举区间长度+枚举起点+枚举最大最小值。（显而易见的）

有了基本的想法，那么想想如何优化。

简单地推推式子，可以发现只需要算每一个数是多少子段的最大最小值。

现在，我们从枚举子段转化为算每个数的贡献。

如何算数的贡献呢？

有一个神奇的东西叫做**单调栈**。

它可以在 $O(n)$ 的复杂度内求出元素左右的第一个比它大/小的值。

**具体实现（最大值）：**

有一个数 $a_i$ 需要入栈，先比较 $a_i$ 与栈顶的大小。

 若 $a_i$ 大于栈顶，则不断弹出，并且让 $r_i=i$ ，直到 $a_i$ 小于等于栈顶再压入 $a_i$ ，否则直接压入 $a_i$。
 
 最后检查栈中是否还有元素，这些数都是右边没有比它大的数的，赋值为 $n+1$。

至此，我们就算出了每一个数右边第一个比它大的数的位置。

用单调栈求出每一个数左边第一个比它大/小的数以及右边第一个比它大/小的数，答案就可以转化为 $\sum_{1 \leqslant i \leqslant n}a_i*(i-lmax_i)*(rmax_i-i)-a_i*(i-lmin_i)*(rmin_i-i)$。

直接 $O(n)$ 解决即可。

上代码！

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e6+5;
int n;
int a[MAXN];
int l_max[MAXN],r_max[MAXN];//当最大值的区间的左边界与右边界
int l_min[MAXN],r_min[MAXN];//当最小值的区间的左边界与右边界
stack<int>q;
signed main()
{
	scanf("%lld",&n);
	for(register int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	for(register int i=1;i<=n;i++)//单调栈求右边第一个比它大的数
	{
		while(!q.empty()&&a[i]>a[q.top()])
		{
			r_max[q.top()]=i;
			q.pop();
		}
		q.push(i);
	}
	while(!q.empty())//右边没有比它大的
	{
		r_max[q.top()]=n+1;
		q.pop();
	}
	for(register int i=n;i>=1;i--)//求左边第一个比它大的数
	{
		while(!q.empty()&&a[i]>=a[q.top()])
		{
			l_max[q.top()]=i;
			q.pop();
		}
		q.push(i);
	}
	while(!q.empty())q.pop();//0为初始值，不用重复
	for(register int i=1;i<=n;i++)//求右边第一个比它小的数
	{
		while(!q.empty()&&a[i]<a[q.top()])
		{
			r_min[q.top()]=i;
			q.pop();
		}
		q.push(i);
	}
	while(!q.empty())
	{
		r_min[q.top()]=n+1;
		q.pop();
	}
	for(register int i=n;i>=1;i--)//求左边第一个比它小的数
	{
		while(!q.empty()&&a[i]<=a[q.top()])
		{
			l_min[q.top()]=i;
			q.pop();
		}
		q.push(i);
	}
	while(!q.empty())q.pop();
	int ans_max=0,ans_min=0;//答案会爆int，记得开long long
	for(register int i=1;i<=n;i++)//累加贡献
	{
		ans_max+=a[i]*(i-l_max[i])*(r_max[i]-i);
		ans_min+=a[i]*(i-l_min[i])*(r_min[i]-i);
	}
	printf("%lld",ans_max-ans_min);
	return 0;
}

```

---

## 作者：Jayun (赞：1)

# CF817D Imbalanced Array

## 链接

[CF817D Imbalanced Array](https://www.luogu.com.cn/problem/CF817D)

## 题目大意

求：
$$
\sum_{l=1}^n\sum_{r=l}^n\left(\max_{i=l}^r\{a_i\}-\min_{i=l}^r\{a_i\}\right)
$$

## 思路

### 方法一

$\mathcal{O}(n^3)$ 暴力。

### 方法二

先转化：
$$
\begin{aligned}
\sum_{l=1}^n\sum_{r=l}^n\left(\max_{i=l}^r\{a_i\}-\min_{i=l}^r\{a_i\}\right)=\sum_{l=1}^n\sum_{r=l}^n\max_{i=l}^r\{a_i\}-\sum_{l=1}^n\sum_{r=l}^n\min_{i=l}^r\{a_i\}
\end{aligned}
$$
然后考虑用单调栈优化：对于最大和最小分别开两个单调栈，分别记录若当前点为区间最大或最小的值，那么左右分别到哪个点，即找某个点左边、右边第一个比它大（或小）的值。

然后就能 $\mathcal{O}(n)$ 做了。

## 代码

```cpp
const int N = 1e6 + 10;

inline ll Read() {
	ll x = 0, f = 1;
	char c = getchar();
	while (c != '-' && (c < '0' || c > '9')) c = getchar();
	if (c == '-') f = -f, c = getchar();
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + c - '0', c = getchar();
	return x * f;
}

ll n, a[N], qx[N], qn[N], tx, tn, f[N], g[N];
ll ans;

int main() {
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	n = Read();
	for (int i = 1; i <= n; i++) a[i] = Read();
	for (int i = 1; i <= n; i++) {
		for (; tx && a[qx[tx]] <= a[i]; tx--);
		for (; tn && a[qn[tn]] >= a[i]; tn--);
		qx[++tx] = i, qn[++tn] = i;
		f[i] = i - qx[tx - 1];
		g[i] = i - qn[tn - 1];
	}
	tx = tn = 0;
	qx[0] = qn[0] = n + 1;
	for (int i = n; i; i--) {
		for (; tx && a[qx[tx]] < a[i]; tx--);
		for (; tn && a[qn[tn]] > a[i]; tn--);
		qx[++tx] = i, qn[++tn] = i;
		ans += a[i] * (qx[tx - 1] - i) * f[i] - a[i] * (qn[tn - 1] - i) * g[i];
	}
	printf ("%lld\n", ans);
	return 0;
}
```



---

