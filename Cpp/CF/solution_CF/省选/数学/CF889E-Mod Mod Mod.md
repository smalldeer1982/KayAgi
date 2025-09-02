# Mod Mod Mod

## 题目描述

You are given a sequence of integers $ a_{1},a_{2},...,a_{n} $ . Let ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF889E/babd3332060a4ee6973a9fa3f688c744930d9a0a.png), and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF889E/3a61ca4726dc1db34df92b20859e100704661de5.png) for $ 1<=i&lt;n $ . Here, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF889E/609a42354b344d4b30f3720c48d42a71dbe37fb8.png) denotes the modulus operation. Find the maximum value of $ f(x,1) $ over all nonnegative integers $ x $ .

## 说明/提示

In the first example you can choose, for example, $ x=19 $ .

In the second example you can choose, for example, $ x=3 $ or $ x=2 $ .

## 样例 #1

### 输入

```
2
10 5
```

### 输出

```
13
```

## 样例 #2

### 输入

```
5
5 4 3 2 1
```

### 输出

```
6
```

## 样例 #3

### 输入

```
4
5 10 5 10
```

### 输出

```
16
```

# 题解

## 作者：day_dream (赞：17)

容易发现我们最后一定会存在至少一个位置i满足最初的x模下去，到第i为恰好为a[i]-1，否则可以整体加1.

我们考虑dp

设x=X%a[1]%a[2]...%a[i],F[i][j]表示当x取0~j时，位置1~i的贡献为x*i+f[i][j].

考虑转移，若j<a[i+1],则F[i+1][j]=F[i][j].

否则分成两部分：

> $F[i+1][j \% a[i+1]]=F[i][j]+i \ast (j-j \% a[i+1])$

> $F[i+1][a[i+1]-1]=F[i][j]+i \ast ((j+1)/a[i+1] \ast a[i+1]-a[i+1])$

容易发现这样只有O(n)个有用状态，并且对于每个有用状态，我们只会转移O(log A)次，可以用数据结构/map等来维护这个DP.

总复杂度O(nlognlogA).

```cpp
#include<algorithm>
#include<cstdio>
#include<map>
#define LL long long
using namespace std;
typedef map<LL,LL>::iterator it;
LL n,x,y,sl,ans,a[200010];
map<LL,LL> dp;
char gc()
{
	return getchar();
	static char buf[1<<16],*S,*T;
	if(S==T){T=(S=buf)+fread(buf,1,1<<16,stdin);if(S==T)return EOF;}
	return *S++;
}
LL rd()
{
	sl=0;
	char ch=gc();
	while(ch<'0'||'9'<ch) ch=gc();
	while('0'<=ch&&ch<='9') sl=sl*10+ch-'0',ch=gc();
	return sl;
}
int main()
{
	n=rd();
	for(int i=1;i<=n;++i) a[i]=rd();
	dp[a[1]-1]=0;
	for(int i=1;i<n;++i)
		for(it j=dp.lower_bound(a[i+1]);j!=dp.end();dp.erase(j++))
		{
			x=j->first;y=j->second;
			dp[x%a[i+1]]=max(dp[x%a[i+1]],y+i*(x-x%a[i+1]));
			dp[a[i+1]-1]=max(dp[a[i+1]-1],y+i*((x+1)/a[i+1]*a[i+1]-a[i+1]));
		}
	for(it i=dp.begin();i!=dp.end();++i)
	{
		x=i->first;y=i->second;
		ans=max(ans,x*n+y);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：yllcm (赞：15)

考了这题，感到十分震撼，发篇题解纪念一下。

考虑朴素的 DP 怎么做，设 $f_{i,j}$ 表示第 $i$ 轮的结果是 $j$，答案是多少。容易得到转移 $f_{i,j}+(j\bmod a_{i+1})\to f_{i+1,j\bmod a_{i+1}}$。

这玩意状态数达到了 $O(na)$，考虑一个经典技巧。注意到最开始的 $f_{1,*}$ 呈现一个一次函数的形态（$f_{1,i}=i$），之后考虑转移中每个连续的部分（即对于区间 $[l,r]$，不存在 $i\in [l,r)$，满足 $(i\bmod a_i)=a_i-1,((i+1)\bmod a_i)=0$），它的贡献也是一个一次函数，且斜率均为 $1$。因此我们断言，对于 $f_{i,*}$，它呈现为若干个一次函数的分段函数形态，且各段斜率都为 $i$。

因此我们只需要维护这些函数就可以了。考虑填表法转移，即把 $f_{i,x}$ 分成若干个模 $a_{i+1}$ 的同余周期（即按照 $\lfloor x/a_{i+1}\rfloor$ 的值分类）把它们排到一起，然后取 $\max$。

![](https://cdn.luogu.com.cn/upload/image_hosting/42mlgmpu.png)

容易发现其实我们只要考虑两条直线：最上面一条短的和最上面一条满的。

然而如果我们真的取 $\max$ 的话函数会变得非常混乱，考虑保留这些函数，求答案的时候再取 $\max$。这样一条函数就变成了一个前缀，于是完全可以用二元组 $(b,r)$ 表示，其中 $b$ 表示截距，$r$ 表示右端点。

那么考虑一次操作新增的直线，一条是 $(b_1',r\bmod a_{i+1})$，一条是 $(b_2',a_{i+1}-1)$，只需要计算 $b_1',b_2'$ 的表达式即可，具体可以参考其它题解，这里不再赘述。

由于除了 $(b,a_i-1)$ 一类直线外，一条直线最终只会新增至多 $\log a_i$ 根直线，而上面那一类最多是 $O(n)$ 条的，因此复杂度是 $O(n\log a_i\log n)$。

https://codeforces.com/contest/889/submission/150452030

希望能够帮到大家。

---

## 作者：ywy_c_asm (赞：13)

这题的dp转移还挺有意思的。

首先一个显而易见的事实就是这个初始的数$x$不断的取模之后一直都是单调不增的，那么我们假设最后取模取到了$x_{end}$，可以考虑把这个和搞成$nx_{end}+b$的形式，换句话说我们要对于一个确定的$x_{end}$找一个最大的$b$，即大于$x_{end}$的那部分的和（可以画个图象）。

然后我们考虑$dp[i][j]$为模完$a_i$之后$x=j$时的最大的$b$，此时我们的和是$ij+b$，实际上这里就蕴含一个东西就是如果$x<j$那么$dp[i][x]<=dp[i][j]$没有任何意义，肯定不如$j$更优。那么，我们不妨就把$[0,j]$**视作一个整体**去转移，也就是说我们在$j$处考虑到$dp[i+1]$的转移时暂且假设$[0,j]$的$b$都取到了$dp[i][j]$，这样一定是合法的。**注意，现在以下所讨论的转移都假设$[0,j]$的$b$取的都是$dp[i][j]$而不是什么更大的数，如果有更大的我们一定能在$dp[i][<j]$的转移中考虑到**。但是我们肯定不可能考虑$[0,j]$里所有数模$a_{i+1}$的结果，我们有一个naive的想法是尽量让模$a_{i+1}$的结果尽量大，而$[0,j]$模$a_{i+1}$是$0,1,2,3,\cdots a_{i+1}-1,0,1,2\cdots j\%a_{i+1}$（这里我们假设$j>=a_{i+1}$，否则的话转移显然就是$dp[i+1][j]=dp[i][j]$，因为$x_{end}$并不改变，$b$也是不变的），假设$[0,j]$最后一个$\%a_{i+1}=a_{i+1}-1$的是$y$，那么考虑$[y+1,j-1]$这一段，显然就已经不用考虑和它们余数相同的比它们还要小的$[0,j]$的数了，但是既然它们后面没有模的0到$a_{i+1}-1$的循环了，那么可以给它们不断的++一直到$j$，这样自身+1，余数也+1，所以$j$一定要比$[y+1,j-1]$这一段数更优。然后我们考虑$<=y$的部分，即还没考虑的$[y-a_{i+1}+j\%a_{i+1},y]$这一段，它们也可以通过不断的+1加到$y$，所以$y$是比剩下的部分更优的，所以我们只考虑$j->j\%a_{i+1}$与$y->y\%a_{i+1}$（即$a_{i+1}-1$）这两个过程就行了，所以我们的转移方程就是：

$dp[i+1][j\%a_{i+1}]=\max\{dp[i][j]+i(j-j\%a_{i+1})\}$

这个$i(j-j\%a_{i+1})$的意思是本来现在的和是$ij+dp[i][j]$，模完之后变成了$ij+dp[i][j]+j\%a_{i+1}=(i+1)(j\%a_{i+1})+dp[i][j]+i(j-j\%a_{i+1})$。

另外还有考虑$y$的转移：

$dp[i+1][a_{i+1}-1]=\max\{dp[i][j]+ia_{i+1}(\lfloor\frac{j-(a_{i+1}-1)}{a_{i+1}}\rfloor\}$

这个类似上面的，此时$y-(a_{i+1}-1)=a_{i+1}(\lfloor\frac{j-(a_{i+1}-1)}{a_{i+1}}\rfloor$。

显然，这个dp可以用$map$滚动转移，由于每次只会凭空多一个$a_{i+1}-1$的状态，或者是$j$变成（因为$j>=a_{i+1}$，我们做完这个转移之后会把它删掉）$j\%a_{i+1}$，前者相当于有$O(n)$个起始状态，后者是一个起始状态会不断的取模变成更小的，而我们知道每次取模变成更小的会至少减半，所以总共转移的复杂度加上map是$O(n\log n\log x)$的。

上代码~

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <functional>
#define ll long long
using namespace std;
namespace ywy {
	inline ll get() {
	    ll n = 0;
	    char c;
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            break;
	        if (c == '-')
	            goto s;
	    }
	    n = c - '0';
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 + c - '0';
	        else
	            return (n);
	    }
	s:
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 - c + '0';
	        else
	            return (n);
	    }
	}
	ll ints[222222];
	map<ll, ll, greater<ll> > mp;
	typedef map<ll, ll, greater<ll> >::iterator it;
	ll tmp[1000001];
	void ywymain() {
	    int n = get();
	    for (register int i = 1; i <= n; i++) ints[i] = get();
	    mp[ints[1] - 1] = 0;
	    for (register int i = 1; i < n; i++) {
	        int ptr = 0;
	        ll mx = 0;
	        for (it j = mp.begin(); j != mp.end(); j++) {
	            if ((j->first) < ints[i + 1])
	                break;
	            mp[ints[i + 1] - 1] =
	                max(mp[ints[i + 1] - 1],
	                    (j->second) + (ll)i * (ints[i + 1] * (((j->first) + 1) / ints[i + 1]) - ints[i + 1]));
	            mp[(j->first) % ints[i + 1]] = max(mp[(j->first) % ints[i + 1]],
	                                               (j->second) + (ll)i * ((j->first) - (j->first) % ints[i + 1]));
	            tmp[ptr] = j->first;
	            ptr++;
	        }
	        while (ptr) ptr--, mp.erase(tmp[ptr]);
	    }
	    ll ans = 0;
	    ll mx = 0;
	    for (it i = mp.begin(); i != mp.end(); i++) {
	        ans = max(ans, n * (i->first) + (i->second));
	    }
	    cout << ans << endl;
	}
}
int main() {
    ywy::ywymain();
    return (0);
}
```

---

## 作者：约瑟夫用脑玩 (赞：11)

> 如果一道题看过但不会做，80%是之前看完都没理解，15%是忘了，3%是换了个壳子（题面），剩下的2%留给抽风。——《模拟赛后有感》

做的时候由于不会没看出来，下来发现这道题除了要求的东西，框架竟然和 [AGC003E](https://www.luogu.com.cn/problem/AT2005) 一模一样。（话说昨天还在说 AGC003E 难度虚高来着）

题目不太好看，看作 $x$ 从 $i:1\to n$，每次对 $a_i$ 取模并累加和，求和的最大值。

首先对于 $a_{i+1}\ge a_{i}$，去除 $a_{i+1}$，并将其权值（初始为 $v_i=1$）累加到 $v_i$ 上，随便做一下。

于是有了条件 $\forall a_{i+1}<a_{i}$，如果你问有什么用，我可以告诉你不这么做也不会错。

用处实际上应该是可以减少常数，~~我总不可能跟你说是从隔壁那道题贴过来的吧~~。

令 $b_i$ 为 $x\bmod a_1\bmod a_2\cdots\bmod a_i$ 后的值，自然的想到若 $\forall i,a_i-b_i>1$，那么将 $x\to x+1$，则 $b_i\to b_i+1$。

于是最优的 $x$ 一定满足 $\exists i,a_i-b_i=1$，~~然后一般的题解就可以直接把式子贺过来放代码了~~。

令 $c_k=a_k-b_k$，上面的 $a_i-b_i=1$ 即为 $c_i=1$，补充说明若有多个 $c_i=1$ 我们考察的 $i$ 是最小的那个。

为了自然过渡到下一步，我们需要一个显然的观察：

有 $\exists j<i,c_j=\min_{k<i}c_k$，则 $1<c_j<a_i$。

令 $dlt=c_j-1$，不一定自然的想到 $\forall k<i,c_k\to c_k+dlt$ 都不会溢出，那么由 $\forall k<i,c_k'=c_k+dlt\to c_k$ 也都是可行的！

此时有 $c_j'=1$，于是我们可以构想这样的一个过程：在 $j$ 处将 $x$ 取得 $c_j'=1$ 的最大，再在 $i$ 处调整至 $c_i=1,c_j'\to c_j$，以此来更新 $c_i=1$ 的最大。

这样的好处是调整的过程是平凡的，也就是说知道 $a_j,a_i$ 就可以简单计算得到调整 $c_j'=1\to c_j$ 的 $dlt$。

~~我觉得很显然的是~~这样就把所有可能的最优情况都考虑完了，同时这个过程也很好维护，后面会说。

再考虑 $c_i=1$ 后 $\forall p>i$ 的贡献，显然后面每个位置的 $b_p$ 都已经确定了，直接快速计算即可：

由于 $r=x\bmod a_i<a_i<r+k a_i=x$，而 $x\ge a_i$ 时才会被取模，则 $k\ge 1$，$x\ge r+a_i>2r$，故每次取模缩小两倍。

于是直接在 $a_i\le x$ 的最小的那个 $i$ 那里取模，总共只会取 $\log$ 次。

最后要做的就是实现转移和计算贡献，如果你想方便的实现，可以像其他题解那样：

将所有的 $c_i=1$ 对应的 $x$ 走到当前位置 $p$ 得到的 $b_p'$ 以及 $x$ 中最大贡献都维护着走，然后处理两种情况：

- $c_i=1$ 不变，继承并计算贡献，把 $b_p'\ge a_p$ 的变为 $b_p<a_p$ 并累加。

  由上文所说只会取 $\log$ 次模，复杂度是 $\log$。

- 改变为满足 $c_p=1$，调整 $c_i=1\to c_i=\max_{k<p}c_k$，改变的贡献就是一起减一个值。

  不难发现只有在 $b_p'\ge a_p$ 的才可能达到 $c_p=1$，也才可能需要改变为 $c_p=1$，即当 $b_p'=a_p-1$ 时虽然有 $c_p=1$，这种情况看作继承不当做改变。
  
  故和取模的那些 $b_p'$ 一起处理即可，多个两倍常数，复杂度不变。
  
~~更方便的~~，我们可以在一个确定的转折点（确定在这里会被取模）后才计算它之前的贡献，它之后的贡献先暂时不定，从而方便 $c_i=1\to c_p=1$ 的改动。
  
代码：

```cpp
	int i,s;LL x,y,v,nw,mx=0;n=read();
	for(stk[0]=LLONG_MAX;n;n--)
	{
		read(x);ckmx(mx,x);
		if(x<stk[top])stk[++top]=x,val[top]=1;
		else val[top]++;
	}
	F[stk[1]-1]=0;
	for(s=val[1],i=2;i<=top;s+=val[i++])
	{
		for(it=F.lower_bound(nw=stk[i]);it!=F.end();F.erase(it++))
		{
			x=f(*it);v=s(*it);y=x%nw;
			ckmx(F[y],v+s*(x-y));
			ckmx(F[nw-1],v+s*((x+1)/nw*nw-nw));
		}
	}
	for(pair<LL,LL> pr:F)ckmx(ans,f(pr)*s+s(pr));
```

~~没人点赞惹~~，个人认为这篇题解写的挺好，思路更自然，虽然准确度相较就差了点，但还是希望能有人看见/kel

补充一点东西，巧妙之处与 AGC003E 的相通之处：

其实都在一个点上，就是使用了每个 $(i,a_i-1)$ 来转移，发现 AGC003E 也是使用了 $(i,q_i)$，从而实现类似记忆化的方式一起转移。

这道题本身 $(i,a_i-1)$ 就是最优决策点，我们又发掘信息使得转移可以在这些决策点直接进行，从而这样合并 DP 信息，相较于另一题更为自然（应该是吧）。

---

## 作者：feecle6418 (赞：8)

题意：给定序列 $a$，求一个 $x$，使得 $f(x)=x\bmod a_1+x\bmod a_1\bmod a_2+\dots$ 最大。

比较神仙！

令 $g(x,i)=x\bmod a_1\bmod a_2\bmod ...\bmod a_i$。

发现，只要 $\forall i,g(x,i)$ 都不是 $0$，则 $x-1$ 做了前 $i$ 次操作之后，每次得到的都是上一次减一，即 $\forall i,g(x-1,i)=g(x,i)-1$。可以发现，只要保证 $x\bmod a_i$ 都不是 $0$，可以随便降低 $x$，不影响 $g(x,j)$ 之间相对的差。直观地说，相对 $g(x,last\_i)$ 高出来的部分是不变的。

设 $f(i,R)=y$ 表示如果 $x\bmod a_i$ 最后变成了 $0\sim R$，这时多出来的部分的最大值都可以是 $y$。直观地看是这个意思：

![](https://cdn.luogu.com.cn/upload/image_hosting/rte9dn4d.png)

蓝色的是 $x$ 模上 $a_1\sim a_i$ 之后的值，棕色是 $a_i$，绿色部分的和是 $y$。蓝色柱子可以不停往上走，直到限制最紧的那个被顶满，在图中就是可以向上移橙色箭头那么多，移到满（$a_j-1$）。这时 $i$ 移到的位置称为 $R$。

这时可以设计 dp：用一个 map 存下所有的 $R$ 对应的最大 $y$。

在 $i$ 处枚举所有 $(R,y)$ 二元组，试图使其适配 $a_{i+1}$。

- 如果 $R<a_{i+1}$，则该二元组不变，不用管。
- 否则，可以直接延展到 $a_{i+1}$，变为 $(R\bmod a_{i+1},y')$。
- 如果 $R\ge a_{i+1}$，可以把 $R$ 降低到 $a_{i+1}-1$，使 $i+1$ 成为卡着上界的地方，变为 $(a_{i+1}-1,y'')$。
- 除了上述两种转移，其它改变方式都不能保证 $R$ 存在一个位置卡满上界。如果前 $i$ 个有的卡满就是转移一；否则就是转移二。

可以发现该算法时间复杂度是 $O(n\log a_i\log n)$。具体地，只要某个二元组被枚举到了，它本身到下一层转移的时候因为进行了取模，至少减小一半。同时，一共只新产生了 $n$ 个初始的 $R$（所有 $a_i-1$）。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=998244353;
int n;
ll a[200005],mx=0;
map<ll,ll> f;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	f[a[1]-1]=0;
	for(int i=2;i<=n;i++){
		while(1){
			auto k=f.lower_bound(a[i]);
			if(k==f.end())break;
			auto j=*k;
			ll x=j.first,y=j.second;
			f[x%a[i]]=max(f[x%a[i]],y+(x-x%a[i])*(i-1));
			if(x>=a[i]){
				ll z=(x-a[i]+1)/a[i]*a[i]+a[i]-1;
				f[a[i]-1]=max(f[a[i]-1],y+(z-a[i]+1)*(i-1));
			}
			f.erase(k);
		}
	}
	for(auto i:f)mx=max(mx,i.first*n+i.second);
	cout<<mx;
}
```

---

## 作者：hfjh (赞：6)

# CF889E Mod Mod Mod
要求的 $f(x, 1)=x \bmod a_{1}+x \bmod a_{1} \bmod a_{2}+x \bmod a_{1} \bmod a_{2} \bmod a_{3}+\ldots+x \bmod a_{1} \bmod a_{2} \bmod \ldots$，相加的这 n 个项从左往右单调，由于 $x$ 不固定，因此希望把答案跟 $x$ 相关的部分弄得尽量简单，可以把最终的答案看成 $x \times n+y$，其中 $y$ 是所有相邻两项差值之和。如图:

![](https://cdn.luogu.com.cn/upload/image_hosting/oafk81nr.png)

$$
\begin{array}{c}

f_{i+1, j} \leftarrow f_{i, j}, j<a_{i} \\
f_{i+1, j \bmod a_{i}} \leftarrow f_{i, j}+\left(j-j \bmod a_{i}\right) \times(i-1), j \geq a_{i} \\
f_{i+1, a_{i + 1}-1} \leftarrow f_{i, j}+\left\lfloor\frac{\left(j-a_{i}+1\right)}{a_{i + 1}}\right\rfloor \times a_{i} \times(i-1), j \geq a_{i}
\end{array}

$$

三种转移分别是没变，继续取模和更换卡满上界的  $x$。
第一个转移没有必要进行，因为值没变，第二种转移对于每个状态最多执行 $\log a$ 次，因为每次都模比自己小的数。
对于任意一个 $i$，都要新建一个 $x$ 卡满 $a_{i}-1$ 的状态。
拿个 map 做，总复杂度 $\mathcal{O}(n \log A \log n)$。

# code
```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int N = 2e5 + 10;
int n;
ll a[N], ans = 0, now, fa, mx, j, v;
map<ll, ll> f;
struct node{
	ll v;
	int cnt;
};
vector<node> p;
void input(){
	cin>> n ;
	for(int i = 1; i <= n; ++i){
		cin>>a[i];
	}
}
void op(){
	f[a[1] - 1] = 0;
	for(int i = 2; i <= n; ++i){
		auto l = f.lower_bound(a[i]);
		mx = -1e18;
		for(auto it = l; it != f.end(); ++it){
			j = it -> first, v = it -> second;
			f[j % a[i]] = max(f[j % a[i]], v + (j - j % a[i]) * (i - 1));
			mx = max(mx, v + (j - a[i] + 1) / a[i] * a[i] * (i - 1));
		} 
		if(mx >= 0) f[a[i] - 1] = max(f[a[i] - 1], mx);
		f.erase(l, f.end());
	}
}
void output(){
	for(auto it = f.begin(); it != f.end(); ++it){
		j = it -> first, v = it -> second;
		ans = max(ans, j * n + v);
	}
	cout<<ans;
}
int main(){
	freopen("up.in","r",stdin);
	freopen("up.out","w",stdout);
	input();
	op(); 
	output();
	
	return 0;
}
```


---

## 作者：tzc_wk (赞：4)

[Codeforces 题目传送门](https://codeforces.com/contest/889/problem/E) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF889E)

~~题目名称 hopping~~

我们记 $x_i=X\bmod a_1\bmod a_2\bmod\dots\bmod a_i$，也就是 $X$ 连续 mod 上前 $i$ 个数后得到的结果。

一个非常 naive 的想法是设 $dp_{i,j}$ 表示考虑到前 $i$ 个数，当前的 $x_i=j$ 的最大的 $\sum\limits_{k=1}^ix_k$，显然有一个 $\mathcal O(na_i)$ 的转移。但事实上稍微了解一下 $dp$ 优化的同学都可用看出这个 $dp$ 是没有前途的，因为这个状态本身就无法优化，每个 $dp_{i,j}$ 都有可能对最终的 $dp_n$ 产生贡献。

于是我们只好换个状态。首先可以观察到一个性质，就是若 $x_i\ne 0$，那么若我们令 $X\leftarrow X-1$ 一定有新的 $x_i$ 等于原本的 $x_i$ 减 $1$，我们记 $Y=\sum\limits_{j=1}^ix_j-x_i$，根据上面的推论可知，如果我们令 $X\leftarrow X-x_i+v(v\in[0,x_i])$ 一定有 $\sum\limits_{j=1}^ix_j=Y+vi$。于是我们考虑**将 $[0,j]$ 搞在一起转移**。设 $dp_{i,j}$ 为考虑到前 $i$ 个数，当前的 $x_i=j$ 的最大的 $Y$。考虑怎么转移，我们考虑枚举一个 $k$ 并将 $X$ 改为 $X-x_i+k$，那么就有 $dp_{i+1,k\bmod a_{i+1}}\leftarrow dp_{i,j}+(k-k\bmod a_{i+1})\times i$（因为将 $X$ 改为 $X-x_i+k$ 之后，真实的 $\sum\limits_{j=1}^ix_j=Y+ki$，$\sum\limits_{j=1}^ix_j-(k\bmod a_{i+1})=Y+ki-i(k\bmod a_{i+1})=dp_{i,j}+(k-k\bmod a_{i+1})\times i$），但显然我们不可能枚举 $k$ 进行转移，考虑将 $[0,j]$ 中所有数 $\bmod a_{i+1}$ 的值写成一排，若 $j\ge a_{i+1}$ 那显然是若干个 $0...a_{i+1}-1$ 的周期加一个零头，不难发现我们最优转移点只有两个，那就是最后一个周期的 $a_{i+1}-1$，以及最后零头部分的最后一个数（$j\bmod a_{i+1}$），因为其他状态要么没有这两个状态来得优，要么可以通过这两个状态在未来的转移中得到，这个稍微想想就能想通；若 $j<a_{i+1}$，与上面的情况也类似，只不过少了最后一个周期的 $a_{i+1}-1$ 的情况。形式化地写下来就是以下状态转移方程：

- $a_{i+1,j}\leftarrow dp_{i,j}(j<a_{i+1})$

- $a_{i+1,j\bmod a_{i+1}}\leftarrow dp_{i,j}+(j-j\bmod a_{i+1})\times i(j\ge a_{i+1})$

  $a_{i+1,a_{i+1}-1}\leftarrow dp_{i+j}+(\lfloor\dfrac{j+1}{a_{i+1}}\rfloor\times a_{i+1}-a_{i+1})\times i(j\ge a_{i+1})$

第一维可以直接去掉，第二维可以用 `map` 优化，注意到每个 $j$ 最多转移 $\log a_i$ 次，因此复杂度 $n\log a_i\log n$，可通过此题。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned long long u64;
namespace fastio{
	#define FILE_SIZE 1<<23
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=!(c^'-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=(~x)+1;
	}
	template<typename T> void recursive_print(T x){if(!x) return;recursive_print(x/10);putc(x%10^48);}
	template<typename T> void print(T x){if(!x) putc('0');if(x<0) putc('-'),x=~x+1;recursive_print(x);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}
const int MAXN=2e5;
int n;ll a[MAXN+5];
map<ll,ll> dp;
int main(){
	scanf("%d",&n);for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	dp[a[1]-1]=0;
	for(int i=1;i<n;i++){
		for(map<ll,ll>::iterator it=dp.lower_bound(a[i+1]);it!=dp.end();it++){
			ll x=it->fi,y=it->se;
			dp[x%a[i+1]]=max(dp[x%a[i+1]],y+1ll*i*(x-x%a[i+1]));
			dp[a[i+1]-1]=max(dp[a[i+1]-1],y+1ll*i*((x+1)/a[i+1]*a[i+1]-a[i+1]));
		} dp.erase(dp.lower_bound(a[i+1]),dp.end());
	} ll ans=0;
	for(map<ll,ll>::iterator it=dp.begin();it!=dp.end();it++){
		ll x=it->fi,y=it->se;chkmax(ans,y+x*n);
	} printf("%lld\n",ans);
	return 0;
}
```



---

## 作者：small_john (赞：4)

## 解题思路

首先可以想到，$x=a_i-1$ 中肯定是存在最优解的。那么考虑 dp。

设 $dp_{i,j}$ 表示第 $i$ 个数，$x$ 取 $j$ 的最大值，分两种情况：

1. $j<a_i$：$dp_{i,j}=dp_{i-1,j}$，即可以直接转移；
2. $j\ge a_i$：分两种转移：
	- 把 $x$ 变为 $a_x-1$，则 $dp_{i,a_i-1}=dp_{i-1,j}+(i-1)\times(\lfloor\frac{j+1}{a_i}\rfloor\times a_i-a_i)$；
	- 就取当前的值，则 $dp_{i,j\bmod a_i}=dp_{i,j}+(i-1)\times(j-j\bmod a_i)$。

由于值域比较大，所以直接开个 map 来维护 $dp$ 数组，再继续优化空间，用滚动数组的思想。时间复杂度为 $O(n\log n\log V)$（$V$ 为值域）。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define x first
#define y second
using namespace std;
const int N = 2e5+5;
int n,a[N],ans;
map<int,int> dp;
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i = 1;i<=n;i++)
		cin>>a[i];
	dp[a[1]-1] = 0;
	for(int i = 2;i<=n;i++)
	{
		for(auto j = dp.lower_bound(a[i]);j!=dp.end();dp.erase(j++))
		{
			int x = j->x,y = j->y;
			dp[x%a[i]] = max(dp[x%a[i]],y+(i-1)*(x-x%a[i]));
			dp[a[i]-1] = max(dp[a[i]-1],y+(i-1)*((x+1)/a[i]*a[i]-a[i]));
		}
	}
	for(auto i = dp.begin();i!=dp.end();i++)
	{
		int x = i->x,y = i->y;
		ans = max(ans,x*n+y);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：FZzzz (赞：3)

看不懂题解，说下我的理解。

记 $b_i$ 为 $x$ 依次模前 $i$ 个 $a$ 得到的结果，要求的就是最大的 $\sum\limits_{i=1}^nb_i$。

如果对于所有 $i$ 都有 $b_i<a_i-1$ 那么把 $x$ 换成 $x+1$ 会使得所有 $b$ 加一，这是不劣的。所以至少有一个 $i$ 满足 $b_i=a_i-1$。如果这个 $i$ 确定了，$b_i$ 到 $b_n$ 也就确定了。

这启发我们的 dp 不需要执着于直接将 $b$ 的值列入状态。考虑设 $f_{i,j}$ 为钦定 $b_j=a_j-1$，此时前 $i$ 个 $b$ 的和的最大值。尝试使用这个状态进行转移。

$f_{i,j}$ 直接从 $f_{i-1,j}$ 得来，重点在于如何得到 $f_{i,i}$。我们断言：$f_{i,i}$ 取最优值时的 $b_1$ 到 $b_{i-1}$（下简称“$f_{i,i}$ 对应的局面”）一定由某个 $f_{i-1,j}$ 所对应的局面整体减去某个数得到。

否则，考虑将 $f_{i,i}$ 对应的局面整体加上某个数 $\Delta$ 使得对于某个 $j<i$ 有 $b_j=a_j-1$，并且此时也是一个合法的局面（虽然不能使 $b_i=a_i-1$）。

发现，$f_{i-1,j}$ 对应的局面整体减去 $\Delta$ 后也是一个能使得 $b_i=a_i-1$ 的合法局面，但它比 $f_{i,i}$ 对应的局面劣。于是，将 $f_{i,i}$ 对应的局面整体加上 $\Delta$ 后的局面是一个满足 $f_{i-1,j}$ 条件的局面，而它比 $f_{i-1,j}$ 对应的局面优，矛盾。

这样，我们枚举 $f_{i,i}$ 由哪个 $f_{i,j}$ 平移而来，然后算出最小的偏移量进行转移。至此我们得到了一个 $O(n^2)$ 的算法。

下面写得比较抽象，如果看不懂可以理解 $n^2$ 以后快进到代码。

考虑优化这个算法。发现，这样进行转移时，我们并不关心 $j$，我们关心的只有 $f_{i-1,j}$ 和它所对的 $b_{i-1}$。维护所有这样的 $(b_{i-1},f_{i-1,j})$ 键值对，那么对于键相等的对我们只需要保留值最大的一个。

考虑从 $i-1$ 转移到 $i$ 会产生怎样的影响。对于原先的一个对 $(x,y)$，转移后有一个 $(x\bmod a_i,y+x\bmod a_i)$。并且，若 $x\ge a_i$，那么我们会将 $b_{i-1}$ 从 $x$ 平移到 $x'=a_i\left\lfloor\dfrac{x-a_i+1}{a_i}\right\rfloor$，有一个 $(a_i-1,y-(i-1)(x-x')+a_i-1)$。

对于 $x<a_i$ 的部分，在 $n$ 步转移中总变化量可能达到 $O(n^2)$，这是无法接受的。但是，如果我们把维护的对改为 $(x,y-xi)$，这部分就不会有变化。

那么我们考虑使用 `map` 维护这些键值对。一次转移时，把键不小于 $a_i$ 的部分拉出来按上面的方法转移，然后把这部分删掉并加入新的对。

分析这样的复杂度：新加入一个键时，它要么是 $a_i-1$，这只有 $O(n)$ 个；要么是之前的某个键模 $a_i$ 得到的，由于我们只考虑 $x\ge a_i$ 所以它至少减半。所以总变化量是 $O(n\log a)$，算上 `map` 总时间复杂度 $O(n\log n\log a)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
inline ll read(){
	ll x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c)){
		if(c=='-') f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
int main(){
#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
#endif
	int n=read();
	map<ll,ll> f;
	f[read()-1]=0;
	for(int i=2;i<=n;i++){
		ll a=read();
		map<ll,ll> f2;
		auto it=f.lower_bound(a);
		for(auto j=it;j!=f.end();j++){
			ll x=j->first,y=j->second;
			f2[x%a]=max(f2[x%a],y+(x-x%a)*(i-1));
			f2[a-1]=max(f2[a-1],y+(x-a+1)/a*a*(i-1));
		}
		f.erase(it,f.end());
		for(auto j:f2)
			f[j.first]=max(f[j.first],j.second);
	}
	ll ans=0;
	for(auto i:f) ans=max(ans,i.second+i.first*n);
	printf("%lld\n",ans);
#ifdef LOCAL
	fprintf(stderr,"%f\n",1.0*clock()/CLOCKS_PER_SEC);
#endif
	return 0;
}
```
~~突然感觉好像不比其他题解好理解多少。~~

---

## 作者：ZillionX (赞：1)

# Description

给定一个长为 $n$ 的序列 $a$，求最大的 $f(x)=x \bmod a_1+x \bmod a_1 \bmod a_2 + \cdots$。

$n \le 2 \times 10^5 , V \le 10^{13}$，时限 2s。

# Solution

这题神仙 DP 啊。

我们设 $x_i=x \bmod a_1 \bmod a_2 \cdots \bmod a_i$。你考虑一个上界，就是说，除非已经有一个 $x_i=a_i -1$，否则我们可以整体抬高所有 $x_i$。

那么我们设最后取模到了 $x_{\text{ed}}$，那么就可以把整个的和表示为 $f(x)=nx_{\text{ed}} +b$ 的形式。我们 DP 的时候就需要对这个 $x_{\text{ed}}$ 找到最大的 $b$，这样看起来状态数是直接爆炸的，但是我们先不管，后面再尝试把状态数压下来。

你考虑设 $f(i,j)$ 表示取模到了 $a_i$ 时对于 $x_{\text{ed}}=j$ 的最大的 $b$，我们怎么转移这个东西。这个时候就有一个很妙的思想：把 $[0,j]$ 视为一个整体来转移。

转移的时候我们考虑两个最优决策点，一个是 $j$，一个是使得 $x' \bmod a_i=a_i-1$ 的最大的 $x'$。因为只有这两个地方能卡满上界，那么我们就有转移

$$f(i+1,j \bmod a_{i+1})=\max\{f(i,j)+i(j-j\bmod a_i)\}$$

$$f(i+1,a_{i+1}-1)=\max\bigg\{f(i,j)+ i\bigg(\left\lfloor\dfrac{j+1}{a_{i+1}}\right\rfloor a_{i+1}-a_{i+1}\bigg) \bigg\}$$

然后你会发现真正有用的状态数极少，是 $\mathcal O(n)$ 级别的，我们就可以用 map 等数据结构来转移。总体的时间复杂度就可以达到 $\mathcal O(n \log n \log V)$。

# Code

```cpp
typedef long long LL;
const int N=2e5+5;

int n;
LL Ans,a[N];
map<LL,LL> f;

int main() {
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%lld",&a[i]);
	f[a[1]-1]=0;
	for (int i=1;i<n;i++)
		for (map<LL,LL>::iterator j=f.lower_bound(a[i+1]);j!=f.end();f.erase(j++)) {
			LL x=j->first,y=j->second;
			f[x%a[i+1]]=max(f[x%a[i+1]],y+i*(x-x%a[i+1]));
			f[a[i+1]-1]=max(f[a[i+1]-1],y+i*((x+1)/a[i+1]*a[i+1]-a[i+1]));
		}
	for (map<LL,LL>::iterator i=f.begin();i!=f.end();i++) {
		LL x=i->first,y=i->second;
		Ans=max(Ans,x*n+y);
	}
	printf("%lld",Ans);
	return 0;
}
```


---

## 作者：ppip (赞：0)

首先我们有一个倒着 DP 的做法就是你维护 $f_{i,j}$ 表示 $i$ 之前的取模不生效的情况下，$X<j$ 的答案。

转移找到首个 $a_k<j$ 的 $k$，令 $c=\lfloor j/a_k \rfloor$，有 $f_{i,j}=\max(f_{k,a_k}+a_k(c-1)(k-1),f_{k,j\bmod a_k}+a_kc(k-1))$，这么转移是因为 $<j$ 的数中只有最大的 $a_k$ 个数有用，分为最大的 $j\bmod a_k$ 个数和去掉余数后最大的 $a_k$ 个数转移。

这里有用的状态显然只有每个点出发取模的断点（对于每个 $i$ 求 $a_i \bmod a_{i+1}\bmod a_{i+2}\dots \bmod a_n$ 中 $a_i$ 发生变化的位置），共 $O(n\log V)$ 个。容易用 P11692 求出所有状态然后直接转移。

时空复杂度 $O(n\log V)$，空间不能通过，我感觉时间也不能过。

---

