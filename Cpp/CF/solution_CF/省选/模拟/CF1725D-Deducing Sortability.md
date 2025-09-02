# Deducing Sortability

## 题目描述

Let's say Pak Chanek has an array $ A $ consisting of $ N $ positive integers. Pak Chanek will do a number of operations. In each operation, Pak Chanek will do the following:

1. Choose an index $ p $ ( $ 1 \leq p \leq N $ ).
2. Let $ c $ be the number of operations that have been done on index $ p $  before this operation.
3. Decrease the value of $ A_p $ by $ 2^c $ .
4. Multiply the value of $ A_p $ by $ 2 $ .

After each operation, all elements of $ A $ must be positive integers.

An array $ A $ is said to be sortable if and only if Pak Chanek can do zero or more operations so that $ A_1 < A_2 < A_3 < A_4 < \ldots < A_N $ .

Pak Chanek must find an array $ A $ that is sortable with length $ N $ such that $ A_1 + A_2 + A_3 + A_4 + \ldots + A_N $ is the minimum possible. If there are more than one possibilities, Pak Chanek must choose the array that is lexicographically minimum among them.

Pak Chanek must solve the following things:

- Pak Chanek must print the value of $ A_1 + A_2 + A_3 + A_4 + \ldots + A_N $ for that array.
- $ Q $ questions will be given. For the $ i $ -th question, an integer $ P_i $ is given. Pak Chanek must print the value of $ A_{P_i} $ .

Help Pak Chanek solve the problem.

Note: an array $ B $ of size $ N $ is said to be lexicographically smaller than an array $ C $ that is also of size $ N $ if and only if there exists an index $ i $ such that $ B_i < C_i $ and for each $ j < i $ , $ B_j = C_j $ .

## 说明/提示

In the first example, the array $ A $ obtained is $ [1, 2, 3, 3, 4, 4] $ . We can see that the array is sortable by doing the following operations:

- Choose index $ 5 $ , then $ A = [1, 2, 3, 3, 6, 4] $ .
- Choose index $ 6 $ , then $ A = [1, 2, 3, 3, 6, 6] $ .
- Choose index $ 4 $ , then $ A = [1, 2, 3, 4, 6, 6] $ .
- Choose index $ 6 $ , then $ A = [1, 2, 3, 4, 6, 8] $ .

## 样例 #1

### 输入

```
6 3
1
4
5```

### 输出

```
17
1
3
4```

## 样例 #2

### 输入

```
1 0```

### 输出

```
1```

# 题解

## 作者：Polarisx (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1725D)。

本题解提供英文版，位于示例代码之后。

English version of this editorial is provided after the sample code.

## 思路

考虑求解第一个问题，不妨令 $A_{i,j}$ 表示数 $i$ 经过 $j$ 次操作后得到的数，将其暴力展开即可得到 $A_{i,j}=2^j(i-j)$，问题转换成了在 $A$ 中选出 $n$ 个互不相同的数使得它们的 $i$ 和最小。

因此我们贪心的从小到大枚举 $i$，考虑什么数是没在之前选的数中出现的，$A_{i,j}=2^j(i-j)=2^{j-1}(2i-j-1-(j-1))=A_{2i-j-1,j-1}$，根据这个，我们能很轻松的得到当 $i-j$ 为奇数的时候，这个数一定是不重复的，证明可参考唯一分解定理。

也就是说，我们每一行都会至少取出一半的数，因此总枚举的 $i$ 是 $\mathcal O(\sqrt n)$ 量级的，这样就可以求出最小和了，现在我们要求的就是第 $k$ 个数，接下来的操作就很妙了。

首先通过打表发现选出来的数一定构成若干个等差数列，第 $i$ 个等差数列的公差是 $2^{i-1}$。

考虑证明这个东西，对于第 $0$ 列，假设我们选出最大的数为 $k$，那么它在 $k$ 行，而 $[1,k-1]$ 行中一定会出现 $1,2,\cdots,k-1$ 这些数，接下来删去第一列，将剩下的数除以 $2$，我们会发现，这个子矩阵依旧满足这个条件，不断进行下去，最终会形成若干个等差数列，第 $i$ 个等差数列的公差为 $2^{i-1}$，不过这些等差数列会产生交集，去除掉这些交集即可，仍然是等差数列，故成立。

根据以上过程，我们可以求出每个等差数列的项数，由于等差数列的个数是 $\mathcal O(\sqrt n)$ 级别的，因此我们直接预处理，询问二分即可。

时间复杂度 $\mathcal O(\sqrt n +q\log n)$。


```cpp
#include <bits/stdc++.h>
#define ll long long 
using namespace std;

const int Maxn=1e5+7;
int n,Q;
ll ans;

int ps[Maxn],w[Maxn];

int main(){
    scanf("%d%d",&n,&Q);
    int len=1;
    while(1){
        if(n<=(len+1)/2) break;
        n-=(len+1)/2; 
        ans+=(len+1)/2*len; len++; 
    }
    ans+=n*len; 
    printf("%lld\n",ans);
    for(int i=1;i<=len;i++){
        w[i]=len-i+(i>=len-(n-1)*2);
        ps[i]=ps[i-1]+w[i]-w[i-1]/2;
    }
    while(Q--){
        int x;
        scanf("%d",&x);
        int p=lower_bound(ps+1,ps+len+1,x)-ps-1,t=x-(ps[p]-w[p]/2);
        while(!(t&1)) p++,t/=2;
        printf("%d\n",p+t);
    }

    system("pause");
    return 0;
}
```

Considering solving the first problem,let $A_{i,j}$ denote the number obtained from $i$ after $j$ operations.By expanding it,we get $A_{i,j}=2^j(i-j)$.The problem then transforms into selecting $n$ distinct numbers from $A$ such that the sum of their $i$ values is minimized.

Therefore,we greedily enumerate $i$ in increasing number and consider which numbers have not appeared among the previously selected numbers.$A_{i,j}=2^j(i-j)=2^{j-1}(2i-j-1-(j-1))=A_{2i-j-1,j-1}$.Based on this,we can easily observe that when $i-j$ is odd, this number must be unique. The proof can be referenced from the unique factorization theorem.

In other words, we select at least half of the numbers in each row, so the total number of $i$ values we need to enumerate is on the order of $\mathcal O(\sqrt n)$.This allows us to compute the minimum sum efficiently. Now, the problem reduces to finding the $k$-th number in this selection, and the subsequent operations are quite ingenious.

First, by examining small cases, we observe that the selected numbers must form several arithmetic sequences, where the $i$-th arithmetic sequence has a common difference of $2^{i-1}$.

Let's proceed to prove this observation.

For the $0$-th column, suppose the largest number we select is $k$. This number lies in the $k$-th row, while the rows $[1,k-1]$ must contain all the numbers $1,2,\dots,k-1$.

Next, we remove the first column and divide the remaining numbers by 2. We observe that the resulting submatrix still satisfies the same property. By repeating this process, we eventually obtain several arithmetic sequences, where the $i$-th sequence has a common difference of $2^{i-1}$.

However, these arithmetic sequences may overlap. After removing these overlapping terms, the remaining sequences still form arithmetic progressions. Thus, the claim holds.

Based on the above process, we can determine the number of terms in each arithmetic sequence. Since the number of arithmetic sequences is of order $\mathcal O(\sqrt{n})$, we can directly preprocess them and answer queries using binary search.

The time complexity is $\mathcal O(\sqrt n+q\log n)$.

---

## 作者：良心WA题人 (赞：1)

令 $a_{i,j}$ 表示初始值为 $i$ 的数经过 $j$ 次操作后的值，通过暴力展或者打表，可以容易得到 $a_{i,j}=(i-j)\times 2^j$。由于是正整数所以需要满足 $i>j$。因为 $i-j\ge 2$ 时，$a_{i,j}\ge 2^{j+1}$，令 $a_{i,j}=2^{j+1}+k(k\ge 0)$，则 $a_{i,j+1}=2\times(2^{j+1}+k-2^j)$=$2^{j+1}+2\times k\ge a_{i,j}$，所以对于每个 $i$，$a_i$ 单调递增。

题目里面要求和最小，所以一定是尽量取 $i$ 小的。则存在一个 $k$ 使得 $i\le k$ 的所有值都取完了，且剩下取的数 $i=k+1$。考虑剩下的那些会怎么取，因为字典序要求最小，所以这些 $i$ 最大的数一定尽量往后放，则由于 $a_i$ 单调不降，所以取的一定是一个后缀。

考虑哪些位置是不重的。注意到 $2^j\times(i-j)$ 和 $2^{j-1}\times(2\times i-2\times j)=2^{j-1}\times(2\times i-j-1-(j-1))$ 是相同的。因为 $i>j$，所以后面一个所处的行一定大于等于前一个所处的行。所以取的数满足 $i-j\equiv1\pmod 2$ 即可做到不重。则每一行可以取到约一半的数，一行一共 $i$ 个数，则最多取 $\sqrt n$ 行，暴力找每一行计算答案即可。

考虑如何求每个位置使用的什么数。对于第 $0$ 列，记最大的取了的数为 $k$。则这个 $k$ 属于第 $k$ 行。则我们可以知道 $1$ 到 $k-1$ 行所有不重的取值都取了，这包括了第 $0$ 列的所有取值，那么 $1$ 到 $k$ 的所有取值全都被取了。将第 $0$ 列去掉，剩余的数除以二，以此类推可以得到一系列等差数列，公差为 $2^j$。因此，前一个的等差数列一定包含了后一个的一段前缀，注意到一共只有 $\sqrt n$ 行，所以也一共只有 $\sqrt n$ 列，所以等差数列的个数是 $\sqrt n$。所以枚举等差数列，找到新的等差数列多出来的部分，这个长度可以容易计算，则我们对于每个询问可以快速找到属于哪个等差数列。则这个取值是多少可以直接求得，那么还原回最初的 $i$ 是容易的。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN=2e5+4;
int s[NN],start[NN],w[NN];
int main()
{
	int n,q;
	scanf("%d%d",&n,&q);
	int m=0;
	long long res=0;
	while(1)
	{
		m++;
		if(n<(m+1)/2)
			break;
		if(n>=(m+1)/2)
		{
			res+=1ll*m*((m+1)/2);
			n-=(m+1)/2;
		}
	}
	res+=1ll*m*n;
	printf("%lld\n",res);
	for(int i=1;i<=m;i++)
	{
		w[i]=m-i;
		if(i>=m-(n-1)*2)
			w[i]++;
		s[i]=s[i-1]+w[i]-w[i-1]/2;
	}
	while(q--)
	{
		int x;
		scanf("%d",&x);
		int p=lower_bound(s+1,s+1+m,x)-s,j=p-1,t=x-s[p-1]+w[p-1]/2;
		while(!(t%2))
		{
			j++;
			t/=2;
		}
		printf("%d\n",t+j);
	}
	return 0;
}
```

---

## 作者：NATO (赞：1)

Implementation，你素质真差！

### 思路浅析：

考虑一个数 $a$ 操作 $k$ 次会变成什么。

柿子是形如 $2(2(a-2^0)-2^1)-...-2^{k-1})$ 的，考虑暴力拆开，为 $2^k(a-k)$（注意到把 $2^0,2^1,...$ 拿出来实际上都是 $2^k$）。

这告诉我们当 $k\in[0,a-1]$ 时，搞出来的序列它是递增的，$k\ge a$ 时为非正整数，不合法。

这样我们就可以从小到大枚举 $a$ 算最大能填多长的序列了，但是你很快就能发现搞出来的数会重，不满足递增的限制。

考虑什么样的 $(a-k)2^k$ 会重，发现 $(a-k)$ 是奇数时，显然之前没有出现过，而如果 $(a-k)$ 为偶数，可以发现：

$(a-k)2^k=\frac{a-k}{2}2^{k+1}$

令 $b=\frac{k+a}{2}+1$，由于 $k<a-1$（$a-k$ 为偶数且 $k<a$），则必有 $b<a$，发现之前出现过！

故你只要对每个 $a$ 统计那些和它奇偶相反的 $k$ 就行了，有 $\lceil\frac{a}{2}\rceil$ 个。

这样我们可以求出一个最初 $A$ 序列中值的上界 $m$，显然是 $O(\sqrt n)$。

现在，问题变成了快速求位置 $i$ 上的数。

考虑把所有用到的 $2^k(a-k)$ 暴力按二进制长度分组（即值域上 $[1,1],[2,3],[4,7],...,[2^s,2^{s+1}-1]$ 这样分组）。

但是按 $a$ 考虑发现这么分组没有任何意义，考虑转换角度。

考虑枚举 $k$，对所有合法的 $a$ 分段。

考虑枚举 $b=a-k$，只有 $b$ 翻倍我们才会进入下一段，于是可以维护 $[l,r]$，在 $b\in[l,r]$ 时在 $[2^k,2^{k+1}-1]$ 内，将其整体插入之，$l=r+1,r=2r$ 后进入下一组即可。

这样一个 $k$ 最多只会对 $O(\log m)$ 组进行一个插入，同样，每一组中也只有 $O(\log m)$ 个整体段。

对于每一组，为了统一二的次幂，将第 $s$ 组的基准次幂视作 $2^{s-32}$，给插入整段的 $[l,r]$ 乘以它枚举的 $2^k$ 和基准次幂相除的结果即可。

这样我们组内就可以直接用 $[l,r]$ 比较大小了。

维护一个前缀组总长度和，对于一个询问，我们二分到它在哪一组，然后组内二分它的大小，暴力枚举每个整段算整段有多少个数小于等于它，同时找等于它的那个数还原回去的 $a$ 是多少即可。

现在题目变成了素质很差的 implementation，写写即可。

时间复杂度 $O(\sqrt n\log \sqrt n+q\log^2\sqrt n)$。

#### 参考代码：


```cpp
#include<bits/stdc++.h>
#define ll long long
#define INF 214748364719260817ll
using namespace std;
ll n,q;
struct px
{
	ll l,r;
	ll len,hp,yk;
};
vector<px>cs[70005];
ll m;
ll sz[70005],maxn;
int main()
{
//	freopen("qwer.in","r",stdin);
//	freopen("qwer.out","w",stdout);
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>q;
	ll sum=0,res=0;	
	for(ll i=1;i;++i)
	{
		ll val=((i&1)?(i+1)/2:i/2);
		if(sum+val<n)
		{
			sum+=val,res+=val*i;
		}
		else 
		{
			res+=(n-sum)*i;
			m=i;
			ll cot=0;
			for(ll j=(m-1);j>=0;j-=2)
			{
				++cot;
				ll k=j;
				ll a=(m-k);
				ll val=(1ll<<(k-(k+__lg(a)-32)));
				cs[__lg(a)+k].emplace_back((px){a*val,a*val,val*2,val,k});
				++sz[__lg(a)+k];
				maxn=max(maxn,__lg(a)+k);
				if(cot==n-sum)break;
			}
			break;
		}
	}
	for(ll k=0;k<m;++k)
	{
		ll cot=0;
		for(ll l=1;l+k<m;l*=2,++cot)
		{
			ll r=l*2-1;
			ll tl=l+k,tr=min(m-1,r+k);
			if(k&1)
			{
				if(tl&1)++tl;
				if(tr&1)--tr;
			}
			else
			{
				if(tl%2==0)++tl;
				if(tr%2==0)--tr;
			}
			if(tr<tl)break;
			ll val=(1ll<<((k)-(k+cot-32)));
			cs[k+cot].emplace_back((px){(tl-k)*val,(tr-k)*val,val*2,val,k});
			maxn=max(k+cot,maxn);
			sz[k+cot]+=(tr-tl)/2+1;
		}
	}
	for(ll i=1;i<=maxn;++i)sz[i]+=sz[i-1];
	cout<<res<<'\n';
	while(q--)
	{
		ll x;
		cin>>x;
		ll l=0,r=maxn,res=maxn;
		while(l<=r)
		{
			ll mid=l+r>>1;
			if(x<=sz[mid])r=mid-1,res=mid;
			else l=mid+1;
		}
		if(res)x-=sz[res-1];
		ll ans=INF;
		l=0,r=INF;
		while(l<=r)
		{
			ll mid=l+r>>1;
			ll len=0,yv=INF;
			for(auto it:cs[res])
			{
				if(it.l>mid)continue;
				if(it.r<=mid)
				{
					len+=(it.r-it.l)/it.len+1;
					if(it.r==mid)yv=it.r/it.hp+it.yk;
				}
				else 
				{
					len+=(mid-it.l)/it.len+1;
					if((mid-it.l)%it.len==0)yv=mid/it.hp+it.yk;
				}
			}
			if(len>=x)
			ans=yv,r=mid-1;
			else l=mid+1;
		}
		cout<<ans<<'\n';
	}
}//2^k(a-k)
//a 相等时必然递增
```

---

## 作者：yllcm (赞：0)

 

对[这份提交](https://codeforc.es/contest/1725/submission/181399323)的做法的说明~~官解我没看懂~~。

先转化一下问题。考虑矩阵 $A_{i,j}$ 表示 $i$ 操作 $j$ 次之后得到的结果，有 $A_{i,j}=2(A_{i,j-1}-2^{j-1})$，稍加推导可以得到封闭形式 $A_{i,j}=2^j(i-j)$。注意矩阵实际上是一个上三角的形态。

考虑二元组 $(i,A_{i,j})$，我们要做的实际上是：选出 $n$ 个二元组，使得它的第二关键字互不相同，并且将其按照第二关键字排序之后，第一关键字构成的序列按照题目定义尽可能小。

接下来给出结论：

> 结论 $1$：策略一定是先选择前 $x$ 行中互不相同的数，再在第 $x+1$ 行选择一个后缀。

证明先考虑前半句话，如果前 $x$ 行没有被取满，那么从后面删掉一个数并从前面加上一个数一定更优。后半句话不影响和，但是让最后一行的第二关键字尽可能大可以保证字典序最小。

一个等价的结论是，取数的顺序一定是按行数从小到大排序，列数从大到小排序的顺序依次选取。

问题在于如果按照这个策略取，如何定位到第 $n$ 个互不相同的数的位置。这个问题的关键在于考虑 $x$ 会在矩阵的哪些位置出现，假设 $x=2^ty$，其中 $y$ 为奇数，那么有 $x=A_{y+t,t}=2^t(y+t-t),x=A_{2y+t-1,t-1}=2^{t-1}((2y+t-1)-(t-1)),\cdots$。在遍历过程中，第一个出现的为 $A_{y+t,t}$。观察可知，对于所有 $i-j$ 为奇数的 $A_{i,j}$，$A_{i,j}$ 都是在遍历序中第一次出现的。

> 结论 $2$：所有有效的位置 $A_{i,j}$ 满足 $i-j$ 为奇数，即矩阵黑白染色后的所有黑色格子（$A_{1,0}$ 为黑色）

所以求和就简单了，枚举完整的行数，如果某一行不完整就去掉一个前缀即可。

接下来需要解决查询的问题，即所有二元组 $(i,A_{i,j})$ 中，第 $k$ 大的 $A_{i,j}$ 的 $i$ 是多少。

继续观察所有选取的 $A_{i,j}$ 排序后的形态，可以得到：

> 结论 $3$：选取的 $A_{i,j}$ 排序后构成 $\mathcal{O}(\sqrt{n})$ 个等差数列，第 $i$ 个等差数列的公差是 $2^{i-1}$。

另一个等价的描述是，考虑选取的 $A_{i,j}$ 构成的上三角区域，第 $0$ 列的最后一个数 $A_{2t+1,0}=2t+1$ 满足所有 $[1,2t+1]$ 都在选取的区域中出现过。接下来，将第 $0$ 列删去，并将剩下的数全体除以 $2$，仍然满足这个结论。

证明只需考虑对于所有 $2^y(x-y)<2t+1$，都有 $x<2t-1$。当 $x\geq 2t-1$ 的时候，$f(y)=2^y(x-y)$ 在 $y\in[0,x-1]$ 时的最小值在 $y=0$ 时取到。考虑其导数 $f'(y)=2^y\ln 2(x-y)-2^y$，可知 $f(y)$ 先递增后递减，而 $f(x-1)=2^{x-1}\geq x$。所以结论成立。

所以考虑第 $k$ 大在哪个等差数列取到即可。设 $f_i$ 表示最高次幂为 $i$ 的数的个数，那么第 $i$ 个等差数列的大小为 $2f_{i-1}-1$，带入 $f_0$ 可以理解。而在第 $i$ 个等差数列里面找到第 $k$ 个数的位置是简单的，在第 $1$ 个等差数列中，第 $k$ 个数即为 $k$，找到 $k=2^xy$ 的表示即可。对于剩下的数，可以沿用上面的操作，处理完第一个等差数列之后，将全体数除以 $2$，依次类推。

总复杂度为 $\mathcal{O}(\sqrt{n})$。

---

