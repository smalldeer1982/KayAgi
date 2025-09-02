# [ICPC 2022 Jinan R] Set of Intervals

## 题目描述

庞教授有一个多重区间集 $S=\{[l_i,r_i]\}$（$l_i<r_i$）。

庞教授将对 $|S|-1$ 次执行以下操作：

- 从 $S$ 中选择两个区间 $[a,b]$ 和 $[c,d]$，然后选择两个整数 $x,y$ 满足 $x\in [a,b], y\in [c,d], x<y$。之后，从 $S$ 中删除 $[a,b]$ 和 $[c,d]$，并将 $[x,y]$ 添加到 $S$。

很容易发现，经过这些操作后，$S$ 中恰好包含一个区间，庞教授将得到这个区间作为礼物。

现在庞教授希望你计算他可以得到多少个不同的区间。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4
1
1 1000000000
2
1 1000000000
1 1000000000
4
1 2
3 4
5 6
7 8
4
1 3
2 4
5 8
6 7```

### 输出

```
1
499999999500000000
26
28```

# 题解

## 作者：minstdfx (赞：2)

蓝蓝题，非常小清新（？）的分类讨论。

首先如果 $n=1$ 那么显然只能选目前集合中唯一的区间。答案为 $1$。
  
我们先解决这样一个问题：给定左端点所在的区间 $[l,r]$ 和右端点所在的区间 $[L,R]$，有多少种合法的区间？  
若 $[l,r]$ 与 $[L,R]$ 为空，答案显然为 $0$。  
若 $[l,r]$ 与 $[L,R]$ 不相交，且 $r<L$，则两端点可以任取，答案为 $(r-l+1)\times(R-L+1)$。若两区间不相交且 $l>R$，则显然答案为 $0$。  
若 $[l,r]$ 与 $[L,R]$ 相交且并不存在包含关系，则：  
假设 $r'=\min\{r,R\},l'=\max\{l,L\}$。我们分以下几类情况讨论：  
先计算左端点在 $[l,l')$，右端点在 $[l',R]$ 的答案 $(l'-l)\times(R-l'+1)$。若 $l=l'$，即 $L\le l,R\le r$，则不存在这一类，答案为 $0$。否则，右端点不可能在 $[l,l')$，故此类完全包含左端点在 $[l,l')$ 的情况。  
再计算左端点在 $[l',r']$，右端点在 $(r',R]$ 的答案 $(r'-l'+1)\times(R-r')$。  
最后计算两端点都在 $[l',r']$ 的情况，显然是 $\binom{r'-1'+1}{2}$。  
显而易见，如果 $r>r'$，则左端点不能取 $(r',r]$，否则无右端点可取。故不考虑。  
因此此时的答案为
$$(l'-l)\times(R-l'+1)+(r'-l'+1)\times(R-r')+\binom{r'-1'+1}{2}$$
$$=(l'-l)\times(R-l'+1)+(r'-l'+1)\times(2R-l'-r')\times\dfrac 1 2$$

然后考虑区间包含的情况。若 $[l,r]\subseteq[L,R]$，则相当于右端点在 $[l,R]$。则答案显然为 $\binom{r-l+1}{2}+(r-l+1)\times(R-r)$。容易发现这和两区间相交不包含的形式上等价，因此我们可以把两区间相交不包含的答案计算方式扩展到这种情况。$[L,R]\subseteq[l,r]$ 则同理。


然后考虑 $n=2$ 的原题答案计算。  
假设两个区间分别为 $[l,r],[L,R]$，并且有 $l\le L$。我们可以分别根据右端点最大值 $r_{\max}$ 和左端点最大值 $l_{\min}$ 是否在一个区间来判断使用上述哪种计算方法。
具体地，如果在一个区间（包含）的情况，我们分别钦点左端点在两个区间，但这样子就计算重了两端点都在小区间内的情况，需要予以去重。否则，直接钦点左右端点所在区间计算即可。


假设右端点最大值 $r_{\max}$ 和左端点最大值 $l_{\min}$ 在同一个区间，那么我们算出除掉该区间之外的右端点最大值 $r'$ 和左端点最小值 $l'$。无论如何我们可以通过操作获得一个最大的区间 $[l',r']$，然后套用 $n=2$ 区间包含的做法。

否则，首先发现，如果 $n>4$，则我们可以在不破坏 $l',r'$ 的情况下合并到 $n=4$ 的情况。继续，可以假设两个包含极值点的区间分别为 $[l_{\min},R],[L,r_{\max}]$我们可以用类似的方法得到上述构造方法构造出的所有在 $n=2$，区间为 $[l',r'],[l_{\min},r_{\max}]$ 的情况下得到的所有作为最终答案的区间。除此之外，我们还可以得到：

- 左端点在 $[l_{\min},l')$、右端点在 $[L,l')$ 的所有区间。构造方法：任意选取一个区间和 $[l_{\min},R]$ 合并，并第二次和 $[L,r_{\max}]$ 合并。
- 左端点在 $(r',R]$、右端点在 $(r',r_{\max}]$ 的所有区间。构造方法同理。

最后还要加上左端点在 $[l_{\min},l')$，右端点在 $(r',r_{\max}]$。

若 $n\ge 4$，则分别取两个区间和包含极值点的区间合并，然后上述区间都可以取到。

否则（$n=3$），假如 $L \le r'+1$ 或者 $R \ge l'-1$，则有一个区间不需要合并，合并另一个即可取到所有情况。若非这两种情况，则我们需要分别计算合并了其中一个区间的情况，然后去重。

至此，我们严谨而完整地讨论了整道题目最终答案的每一种情况。

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int maxn=1e6+6;
typedef long long ll;
int t,n,m;
ll calc_noinside(int l1,int r1,int l2,int r2) // left bound in [l1,r1] and right bound in [l2,r2], no inside
{
	if(l1>r1 || l2>r2) return 0;
	if(r1<l2) return 1ll*(r1-l1+1)*(r2-l2+1);
	int R=min(r1,r2),L=max(l1,l2);
	if(l1>R || L>r2) return 0;
	return 1ll*(L-l1)*(r2-L+1)+1ll*(R-L+1)*(2*r2-L-R)/2ll;
}
int pl[maxn],pr[maxn];
ll calc_inside(int l1,int r1,int l2,int r2) // inside
{
	// [l2,r2] is inside [l1,r1]
	return calc_noinside(l1,r1,l2,r2)+calc_noinside(l2,r2,l1,r1)-calc_noinside(l2,r2,l2,r2);
}
ll calc(int l1,int r1,int l2,int r2)
{
	if(l1>l2) swap(l1,l2),swap(r1,r2);
	if(l1==l2 && r1>r2) swap(r1,r2);
	if(r1>=r2) return calc_inside(l1,r1,l2,r2);
	else return calc_noinside(l1,r1,l2,r2);
}
ll getans()
{
	cin>>n;
	int posminl=-1,posmaxr=-1,minl,maxr;
	for(int i=1;i<=n;++i)
	{
		cin>>pl[i]>>pr[i];
		if(posminl==-1 || pl[posminl]>pl[i]) posminl=i;
		if(posmaxr==-1 || pr[posmaxr]<pr[i]) posmaxr=i;
	}
	minl=pl[posminl];
	maxr=pr[posmaxr];
	if(n==1) return 1;
	if(n==2) return calc(pl[1],pr[1],pl[2],pr[2]);
	int l2=2e9,r2=-2e9;
	for(int i=1;i<=n;++i)
	{
		if(posminl==i || posmaxr==i) continue;
		l2=min(l2,pl[i]);
		r2=max(r2,pr[i]);
	}
	ll ans=calc(minl,maxr,l2,r2);
	if(posminl==posmaxr) return ans;
	ans+=calc(minl,l2-1,pl[posmaxr],l2-1);
	ans+=calc(r2+1,pr[posminl],r2+1,maxr);
	if(n>=4 || pr[posminl]>=l2-1 || pl[posmaxr]<=r2+1)
		ans+=calc(minl,l2-1,r2+1,maxr);
	else
	{
		ans+=calc(minl,l2-1,pl[posmaxr],maxr);
		ans+=calc(minl,pr[posminl],r2+1,maxr);
		ans-=calc(minl,pr[posminl],pl[posmaxr],maxr);
	}
	return ans;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--) cout<<getans()<<endl;
	cout.flush(); return 0;
}
```


---

## 作者：Jsxts_ (赞：0)

有点太恶心了。

考虑对于每个 $l$，求出它能对应多少 $r$，那么首先离散化，然后对于每段分别考虑：

- 若有一个包含 $i$ 的区间，那么我们可以一直保留它，并将其它所有区间合并来得到一个尽可能大的区间 $[l,r]$。这样这两个区间最后合并时可以使 $i$ 右端点取到 $[\max(i+1,l),r]$ 中的数。显然这种方案最后的答案是所有可能 $[l,r]$ 的并。

- 还有一种方案，我们考虑将左右两个不包含 $i$ 的区间合并来包含 $i$，那么剩下的所有区间能组成的最大区间最后可以与之合并，答案同样是所有可能的 $[l,r]$ 的并。

发现在大多数情况都是端点分别取到最值，也有取到次最值的。

对于答案分别取到最值的情况：

- 求出包含 $i$ 的区间的最大 $l$、最小 $r$。若这两个都不为最值，则对这两个（或 $1$ 个）区间都做上述操作即可。

- 求出在 $i$ 左侧的完整区间中 $l$ 的最大值、在 $i$ 右侧完整区间 $r$ 的最小值。若这两个都不为最值，则对这两个（或 $1$ 个）区间都做上述操作即可。

接下来是不分别取到最值。那么我们同样求出包含 $i$ 的区间的最大 $l$、最小 $r$，这两个区间分别可以作为可能最优之一。同样求出在 $i$ 左侧的完整区间中 $l$ 的最大值、在 $i$ 右侧完整区间 $r$ 的最小值。

这里有一个特例：在这样一组数据里：

```
3
1 2
4 5
7 8
```

对于 $3$ 作为 $l$ 时，右端点可以取到的实质上是 $[4,5],[7,8]$ 这两个区间。也就是在 $i$ 左侧只有一个区间，右侧只有 $2$ 个区间时，需要特殊处理使答案为右侧两个区间的并。

求出一段区间作为 $l$ 对应的合法区间 $[l,r]$ 后，求答案是简单的。

代码写得过于丑陋，就不放了。

---

