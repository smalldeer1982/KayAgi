# Particles

## 题目描述

You have discovered $ n $ mysterious particles on a line with integer charges of $ c_1,\dots,c_n $ . You have a device that allows you to perform the following operation:

- Choose a particle and remove it from the line. The remaining particles will shift to fill in the gap that is created. If there were particles with charges $ x $ and $ y $ directly to the left and right of the removed particle, they combine into a single particle of charge $ x+y $ .

For example, if the line of particles had charges of $ [-3,1,4,-1,5,-9] $ , performing the operation on the $ 4 $ th particle will transform the line into $ [-3,1,9,-9] $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1844C/e6e0f8b89386e2413f8854df6b39484bae0098bc.png)If we then use the device on the $ 1 $ st particle in this new line, the line will turn into $ [1,9,-9] $ .

You will perform operations until there is only one particle left. What is the maximum charge of this remaining particle that you can obtain?

## 说明/提示

In the first test case, the best strategy is to use the device on the $ 4 $ th particle, then on the $ 1 $ st particle (as described in the statement), and finally use the device on the new $ 3 $ rd particle followed by the $ 1 $ st particle.

In the second test case, the best strategy is to use the device on the $ 4 $ th particle to transform the line into $ [998244353,998244353,1996488706] $ , then on the $ 2 $ nd particle to transform the line into $ [2994733059] $ . Be wary of integer overflow.

In the third test case, there is only one particle, so no operations can be performed.

## 样例 #1

### 输入

```
3
6
-3 1 4 -1 5 -9
5
998244353 998244353 998244353 998244353 998244353
1
-2718```

### 输出

```
9
2994733059
-2718```

# 题解

## 作者：zct_sky (赞：5)

### Solution:
-----
可以发现，每次合并中间的数后下标奇偶性不变（合并奇数个数成为一个数，实际上下标减少了偶数个），且每次合并的为相邻两个奇偶性相同的下标。

因此，下标奇偶性不同的两数无法合并。

所以，答案便是奇数下标合并值和偶数下标合并值中的较大值。

接下来处理合并过程中的数：

- 正数：对于答案有贡献，直接累加
- $0$：累加后答案不变，直接累加
- 负数：可通过一次合并消除，视为 $0$（如 `1 0 -1 1 1` 合并 $-1$ 后变为 `1 1 1`）

于是，最终答案为：

$$\max\left(\sum\limits_{i \ is \ odd}^{n}\max(c_i, 0), \sum\limits_{i \ is \ even}^{n}\max(c_i, 0)\right)$$

特别的，对于 $c_i$ 全部为负数的情况，因为每次合并中间数只会得到一个更小的值，所以最佳方案就是不合并中间数，只合并两边的数，最终留下一个最大值。
### Code:
-----
```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read(){
	ll x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch&15),ch=getchar();
	return x*y;
 
}
const int N=2e5+7;
int t,n; 
ll a[N];
 
int main(){
	t=read();
	while(t--){
		n=read();
		bool f1=1;
		for(int i=1;i<=n;i++){
			a[i]=read();
			if(a[i]>=0)f1=0;
		}
		if(f1){
			ll maxn=INT_MIN;
			for(int i=1;i<=n;i++)
				maxn=max(maxn,a[i]);
			printf("%lld\n",maxn);
			continue;
		}
		ll sum1=0,sum2=0;
		for(int i=1;i<=n;i++)
			if(i&1)sum1+=max(a[i],0ll);
			else sum2+=max(a[i],0ll);
		printf("%lld\n",max(sum1,sum2));
		
	}
	return 0;
}
```

---

## 作者：无钩七不改名 (赞：3)

观察可以发现，可以合并的点奇偶性一定相同（因为中间一定间隔奇数个点），而且两边的点可以直接移去。

所以我们只需要记录，到当前点前，偶数和奇数的合并后的最大点分别为多少即可，并对答案和最大点进行更新。

赛时代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int T,n;
long long c[200005],js,os,maxn;

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);maxn=-1e9;
		os=0;js=0;
		for(int i(1);i<=n;i++){
			scanf("%lld",c+i);maxn=max(maxn,c[i]);
			if(c[i]<=0)continue;
			if(i&1){
				c[i]=max(c[i],c[i]+js);
				js=max(js,c[i]);
			}
			else{
				c[i]=max(c[i],c[i]+os);
				os=max(os,c[i]);
			}
			maxn=max(maxn,c[i]);
		}
		printf("%lld\n",maxn);
	}
	//printf("%d",ans);
	return 0;
}
```


---

## 作者：Halberd_Cease (赞：2)

观察操作，显然，挨在一起的两个元素不可能被合并。

中间没有元素，所以不可能这样操作。

一次操作过后会干掉 $2$ 个元素（不在两边），我们可以想到一个有关奇偶的思路：

我们用下标代替每一个元素：

$$ 1\text{ }2\text{ }3\text{ }4\text{ }5\text{ }6$$
 
我们把 $4$ 删掉，$3$ 和 $5$ 合并后还是 $3$，就得到了一个新的序列：

$$ 1\text{ }2\text{ }3\text{ }6$$

我们发现，原来的数列和新的数列的相对奇偶性不发生变化，即原来在偶数位上的，现在还在偶数位上。

在回来看合并操作，由于合并的是一个数的左右两个，形式理解就是合并的 $x-1$ 和 $x+1$ 位，显然位数要全是奇数或全是偶数才能合并。

这样我们就有结论：奇数位只能和奇数位合并，偶数位只能和偶数位合并。

然后我们考虑两边的情况：

- 删后面显然对奇偶没有影响；

- 删前面可以改变所有的数的奇偶，但是合并操作看的是相对的位置，所以不会有影响。

知道了以上合并的规则，现在统计答案。

由于奇数位和偶数位不能互相合并，可以删掉其中的一种来合并另外一种，统计奇数位和偶数位可能的答案最大值即可。

注意：如果某一位是负数的话不用统计，可以直接删掉而不合并，但是如果整个数列全是负数的话因为必须要剩下一个，所以答案是整个数列的最大值。

核心代码：

```cpp
for(int i=1;i<=n;i++)
{
    cin>>a[i];
    if(i&1)
    {
        mx1=max(mx1,a[i]);
        sum1+=max(0ll,a[i]);//统计答案和最大值
    }
    else
    {
        mx2=max(mx2,a[i]);
        sum2+=max(0ll,a[i]);
    }
}
if(sum1==0&&sum2==0)//全是非正数（和负数一样讨论即可）
{
    cout<<max(mx1,mx2)<<endl;
}
else
{
    cout<<max(sum1,sum2)<<endl;
}
```

---

## 作者：EuphoricStar (赞：1)

原题是 [[ARC092E] Both Sides Merger](https://atcoder.jp/contests/arc092/tasks/arc092_c)。

Key observation：每个元素的下标奇偶性不改变。

于是讨论最后一个数是下标为奇数还是偶数加起来的数。将下标奇偶性相同的元素分开考虑。对于下标奇偶性相同的元素，不难发现答案的上界是所有 $> 0$ 的元素之和（没有 $> 0$ 的元素时选一个最大的），并且一定能够构造方案以达到上界。

例如，下面 `O` 代表对答案有贡献的元素，`.` 代表没有贡献的元素：

`.O.O...O`

方案是 `.O.O...O` $\to$ `O.O...O` $\to$ `O...O` $\to$ `O.O` $\to$ `O`。

于是分下标奇偶性排序一遍从大到小取即可。复杂度 $O(n \log n)$。

[code](https://codeforces.com/contest/1844/submission/213983300)

---

## 作者：_sunkuangzheng_ (赞：1)

**【题目分析】**

注意到一个关键的性质：**每次合并对答案有贡献的下标位置的奇偶性相同**。（可以画图理解）

然后显然任何一个位置的数字都可以通过合并它来把它消掉，所以只需分奇偶求出区间内正数的和，取 $\max$ 即为答案。

最后注意，如果两个和都是 $0$，即序列内只有负数，要取所有负数的最大值输出。（因为必须保留一个数字）


---

## 作者：IYSY2009I (赞：0)

每次合并只会合并现数组中两个相邻距离为二的元素，同时合并前后元素下标的奇偶性不变，因此我们无论如何都无法合并两个奇偶性不同的元素。

考虑一组奇偶性相同的递增下标 $k_1,k_2,...,k_m$，我们都能找到一组方法使得最后剩下的元素等于 $\sum_{i=1}^m a_{k_i}$：

- 从左往右删掉 $a_1,a_2,...a_{k_1}-1$
- 从右往左删掉 $a_1,a_2,...a_{k_m}+1$
- 对于两个相邻的要合并的元素 $a_i,a_j$，每次删掉 $a_{\frac{i+j}{2}}$，更新下标。

因此答案看似就是所以下标为奇数的大于 $0$ 的数的和与下标为偶数的大于 $0$ 的数的和的较大值。

但当这个数组中所有数都是负数的时候，我们被迫要选择至少一个，此时答案是所有数的最大值。

代码：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
long long a[2][100005];
long long sum[2][100005];
void solve(){
	int n;
	scanf("%d",&n);
	long long ans0=0,ans1=0,mx=-1e18;
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i&1][(i+1)>>1]);
		if(i&1) ans1+=max(1ll*0,a[1][(i+1)>>1]);
		else ans0+=max(1ll*0,a[0][(i+1)>>1]);
		mx=max(mx,a[i&1][(i+1)>>1]);
	}
	if(mx<0) printf("%lld\n",mx);
	else printf("%lld\n",max(ans0,ans1));
	return;
}
int main(){
	int t;
	scanf("%d",&t);
	for(int i=1;i<=t;i++)
		solve();
	return 0;
}
```


---

