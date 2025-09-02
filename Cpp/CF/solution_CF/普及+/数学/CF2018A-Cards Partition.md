# Cards Partition

## 题目描述

[DJ Genki vs Gram - Einherjar Joker](https://soundcloud.com/leon-hwang-368077289/einherjar-joker-dj-genki-vs-gram)

⠀

你有若干张卡片。每张卡片上写有一个介于 $1$ 和 $n$ 之间的整数：具体来说，对于每个 $i$ 从 $1$ 到 $n$，你有 $a_i$ 张写有数字 $i$ 的卡片。

商店中提供无限量的各类卡片。你拥有 $k$ 枚硬币，因此最多可以购买 $k$ 张新卡片，购买的卡片可以包含 $1$ 到 $\mathbf{n}$ 之间的任意整数（含边界）。

在购买新卡片后，你必须将所有卡片按照以下规则分配成若干牌组：

- 所有牌组必须具有相同的大小；
- 同一牌组中不允许存在两张数值相同的卡片。

请找出在最优购买和分配方案下，牌组可能的最大大小。

## 说明/提示

在第一个测试用例中，你可以购买一张写有数字 $1$ 的卡片，此时你的卡片变为 $[1, 1, 1, 1, 2, 2, 3, 3]$。你可以将它们分配为牌组 $[1, 2], [1, 2], [1, 3], [1, 3]$，所有牌组的大小均为 $2$ 且包含不同数值。可以证明无法得到大小大于 $2$ 的分配方案，因此答案为 $2$。

在第二个测试用例中，你可以购买两张写有数字 $1$ 的卡片和一张写有数字 $3$ 的卡片，此时卡片变为 $[1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 4, 4, 5, 5, 5, 4]$，可以分配为 $[1, 2, 3], [1, 2, 4], [1, 2, 5], [1, 2, 5], [2, 3, 5], [2, 4, 5]$。可以证明无法得到大小大于 $3$ 的分配方案，因此答案为 $3$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
9
3 1
3 2 2
5 4
2 6 1 2 4
2 100
1410065408 10000000000
10 8
7 4 6 6 9 3 10 2 8 7
2 12
2 2
2 70
0 1
1 0
1
3 0
2 1 2
3 1
0 3 3```

### 输出

```
2
3
1
7
2
2
1
1
2```

# 题解

## 作者：Super_Cube (赞：9)

# Solution

题意：牌的类型为 $1\sim n$，现在已有 $a_i$ 张牌 $i$，且可以获得至多 $k$ 张任意牌。现在要将这些牌分为若干堆，要求每堆牌数量相等且每堆牌内不存在相同的牌，希望最大化牌堆大小。

记 $v=\max a_i$，$s=\sum a_i$。设最终牌堆大小为 $x$。

先考虑 $k=0$ 的情况，此时无任意牌。只有当 $x\mid s$ 且 $v\le\dfrac{s}{x}$ 时才能满足条件。原因？首先整除肯定是必要的，于是共有 $\dfrac{s}{x}$ 个牌堆，而同一牌堆中不能有相同牌，所以需要牌堆数不小于众数出现次数。

再来考虑原问题，也就是可以给 $s$ 加上一个 $[0,k]$ 的整数。套用上面的结论，得到 $x$ 符合要求的条件为 $\begin{cases}s+k\ge vx & s<vx\\(x-s\bmod x)\bmod x\le k & s\ge vx\end{cases}$，于是从大到小枚举 $x$ 逐一判断即可。

# Code
```cpp
#include<bits/stdc++.h>
int T,n;
long long m,a,v,s;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%lld",&n,&m);
		s=v=0;
		for(int i=1;i<=n;++i)
			scanf("%lld",&a),v=std::max(v,a),s+=a;
		for(int i=n;i;--i)
			if((s<v*i&&s+m>=v*i)||(s>=v*i&&(i-s%i)%i<=m))
				printf("%d\n",i),i=1;
	}
	return 0;
}
```

---

## 作者：GUO120822 (赞：2)

题目大意：给定 $n,k$ 表示数列元素个数和最大添加数。问添加 **至多** $k$ 的数值，使得整个数列恰好分为 $x$ 组，且每组元素都不相同。

首先答案不超过 $n$，所以枚举答案并判断。设目前枚举为 $x$。

令 $sum=\sum_{i=1}^{n} a_i$，$ma=\max_{i=1}^{n} a_i$。

先考虑 $k=0$ 的情况。要满足的条件是 $sum \mod x = 0$ 和 $ma \leq \lfloor \frac{sum}{x} \rfloor$。

首先我们要保证 $[sum,sum+k]$ 中包含 $x$ 的倍数。

那么就是 $\lfloor \frac{sum+k}{x}\rfloor \geq sum$。

然后我们需要保证 $ma \leq \lfloor \frac{sum+k}{x} \rfloor$。

**为什么 $ma$ 不会变呢？这正是其他题解没讲清楚的地方。**

我们首先考虑 $ma$ 不变的情况，那当然是没问题的。

当所有元素变为相同的时候，设此时所有数为 $num$。

那么目前的 $\frac{n \times num}{num}$ 在每次加法之后会变成 $\frac{n \times (num+1)}{num+1}$。还是 $n$。

所以是没有关系的。

代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+10;
int T,n,i;
ll a[N],sum,ma,k,ans;
struct FSI{//快读（不用管）
	template<typename T>
	FSI& operator >> (T &res){
		res=0;T f=1;char ch=getchar();
		while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
		while (isdigit(ch)){res=res*10+ch-'0';ch=getchar();}
		res*=f;
		return *this;
	}
}scan;
void work()
{
	scan>>n>>k;sum=ma=0;
	for (i=1;i<=n;i++) scan>>a[i],sum+=a[i],ma=max(ma,a[i]);
	for (i=1;i<=n;i++) if ((sum+k)/i*i>=sum&&(sum+k)/i>=ma) ans=i;
	printf("%d\n",ans);
}
int main()
{
	scan>>T;
	while (T--) work();
	return 0;
}
```

---

## 作者：chenxi2009 (赞：1)

## 思路
先要明确一点：有 $n$ 种卡牌，一组中不能有同类牌，所以答案，即牌组大小，最大为 $n$。$\sum n\le2\times10^5$，可以枚举。问题在于怎么检测一个牌组大小是否可行。

令 $x$ 为可能的牌组大小，首先牌的数量必须有可能整除 $x$，即 $[\sum a_i,\sum a_i+k]$ 中是否有 $x$ 的倍数，可以转换为 $\left\lfloor\frac{\sum a_i+k}{x}\right\rfloor\times x\ge\sum a_i$ 判断。其次在合法的前提下最大的牌组数量得大于 $\max a_i$，即 $\left\lfloor\frac{\sum a_i+k}{x}\right\rfloor\ge\max a_i$。可以证明满足上述条件时，一定有合法方案，具体构造方法：\
买卡之前先把所有的牌分成若干组，每组大小 $\le x$，不必均分，要求不重；然后通过买卡补足每一组的大小到 $x$ 就行了，由于答案 $\le n$，买卡是一定可以买到不重的卡的。

没有了，时间复杂度 $O(\sum n)$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,ans;
long long a[300000],k,sum,mx;
int main(){
	scanf("%d",&T);
	while(T --){
		sum = mx = 0;
		scanf("%d%lld",&n,&k);
		for(int i = 1;i <= n;i ++) scanf("%lld",&a[i]);
		for(int i = 1;i <= n;i ++) sum += a[i],mx = max(mx,a[i]);
		for(int i = 1;i <= n;i ++) if((sum + k) / i * i >= sum && (sum + k) / i >= mx) ans = i;//后面遇到的大的合法答案会覆盖小的答案
		printf("%d\n",ans);
	}
	return 0;
}
```

---

