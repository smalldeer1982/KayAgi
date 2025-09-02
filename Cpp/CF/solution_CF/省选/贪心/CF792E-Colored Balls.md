# Colored Balls

## 题目描述

There are $ n $ boxes with colored balls on the table. Colors are numbered from $ 1 $ to $ n $ . $ i $ -th box contains $ a_{i} $ balls, all of which have color $ i $ . You have to write a program that will divide all balls into sets such that:

- each ball belongs to exactly one of the sets,
- there are no empty sets,
- there is no set containing two (or more) balls of different colors (each set contains only balls of one color),
- there are no two sets such that the difference between their sizes is greater than $ 1 $ .

Print the minimum possible number of sets.

## 说明/提示

In the first example the balls can be divided into sets like that: one set with $ 4 $ balls of the first color, two sets with $ 3 $ and $ 4 $ balls, respectively, of the second color, and two sets with $ 4 $ balls of the third color.

## 样例 #1

### 输入

```
3
4 7 8
```

### 输出

```
5
```

## 样例 #2

### 输入

```
2
2 7
```

### 输出

```
4
```

# 题解

## 作者：UperFicial (赞：9)

> Update 2.17：在某一句话后面加上了句号。

> Update 2.20：加了一个空格。

情人节快乐，祝大家早生贵子。

假设我们分成 $k$ 组，每组的大小为 $x$ 或 $x+1$。

那么，对于 $v$ 个相同颜色的球，他能被合法分组当且仅当 $v\bmod x\le \lfloor\dfrac{v}{x}\rfloor$。

理解这个式子很简单，我们全部用大小为 $x$ 的组可以分成 $\lfloor\dfrac{v}{x}\rfloor$ 组，并且这些组都可以成为 $x+1$，也就是说除了这些组，剩下的还没有被分的球中，有 $\lfloor\dfrac{v}{x}\rfloor$ 是可以被分到组里的，那么我们只需要计算剩下的球有 $v\bmod x$ 个，判断一下是否够用。

一个暴力的想法是，枚举合法的 $x$，然后计算有多少组，显然这个 $x$ 越大越好，这样分的组就尽可能的少。

但是枚举量是 $10^9$，肯定超时，那么我们就需要找其它的性质。**我觉得剩下的性质还是比较难发现的，如果没有往根号这方面想的话 T_T**。

假设 $a_1$ 为 $a$ 中最小的元素，那么对于 $x\le \sqrt{a_1}$，上面的式子都是成立的，这个很容易证明。

那么我们只需要考虑 $x>\sqrt{a_1}$ 的部分，枚举量同样很大。

这就体现出一个技巧，**我们不枚举 $x$，而是枚举 $\lfloor\dfrac{a_1}{x}\rfloor$ 的值，通过这个值，就类似值域分块一样，确定出 $x$ 的范围，然后再将范围中的 $x$ 的值带进去尝试是否合法。**

设这个值为 $a$，则有 $a_1=ax+b$，那么根据上述不等式，我们可以得出 $b$ 的范围为 $[0,a]$。

然后就是小学的知识啦，根据 $b$ 的范围推出 $x$ 的范围，首先我们有 $x=\dfrac{a_1-b}{a}$，然后往里面套就行了。

$0\le b\le a$，同时用 $a_1$ 减去，$a_1-a\le a_1-b\le a_1$，还要再除以一个 $a$，$\lfloor\dfrac{a_1-a}{a}\rfloor\le \lfloor\dfrac{a_1-b}{a}\rfloor\le \lfloor\dfrac{a_1}{a}\rfloor$，第一项可以看做 $\lfloor\dfrac{a_1}{a}\rfloor-1$，第二项直接替换成 $x$，于是就的得到了 $x$ 的范围：
$$
\lfloor\dfrac{a_1}{a}\rfloor-1\le x\le \lfloor\dfrac{a_1}{a}\rfloor
$$
我们惊奇的发现，对于一个 $a$，$x$ 最多只会取两个值！所以我们就在 $O(n\sqrt{V})$ 的时间复杂度下完成了本题。

当然，求出 $\max x$ 后求答案也非常简单，对于每个球，贪心考虑，我们优先用 $x+1$ 大小的集合来装，所以直接对 $x+1$ 除后向上取整就好了，因为反正我们是可以有一种合法方案的，而这个合法方案一定是一些 $x+1$ 大小的集合变成 $x$ 大小的集合，但是总集合数量是不变的。

---

## 作者：reyik (赞：4)

我们先排序

考虑知道$k$,怎么知道每一个$ai$至少多少个

那么显然$ai=a*k+b$

如果$b>a$ 那么如果每一个$k$的改成$k+1$的还是放不下，所以$b<=a$

那么$a=ai/k$,$b=ai\%k$

然后考虑怎么枚举$k$

显然$k<=sqrt(a[1])$ 一定成立

那么考虑怎么搞$k>sqrt(a[1])$

直接枚举$k$肯定$TLE$

所以我们枚举$a1$被分成了几份

假设$a1$被分成$k$份

那么我们可以得出此时的$k$和剩余多少

那么我们可以得出每一个$ai$在这个情况下的份数

然后更新答案

然后注意如果$a1\%k==0$可以尝试$k-1$

```cpp
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <math.h>
using namespace std;
const int N=505;
int a[N],n,res=-1;
long long ans=0;
bool check(int sz,int sy,int t) {
  for (int i=1;i<=n;++i) {
    int x=a[i]/sz,y=a[i]%sz;
    if(sy && y>x) return 0;
    if(!sy) {
      if(y>x) {
        --sz;
        sy=1;
        x=a[i]/sz;
        y=a[i]%sz;
      }
      if(y>x) return 0;
    }
  }
  res=sz;
  return 1;
}
int main() {
  scanf("%d",&n);
  for (int i=1;i<=n;++i) scanf("%d",&a[i]);
  sort(a+1,a+1+n);
  for (int i=1;i<=(int)(sqrt(a[1]))+1;++i) {
    int zs=a[1]/i,sy=a[1]%i;
    if(check(zs,sy,i)) break;
  }
  for (int i=1;i<=n;++i) {
    ans=ans+1ll*(a[i]+res)/(res+1);
  }
  printf("%lld\n",ans);
  return 0;
}
```

---

## 作者：o51gHaboTei1 (赞：3)

**CF792E sol**。

只会 $O(n \sqrt V \log n)$。

推一下性质：设只用 $x,x+1$ 分组，则显然一个 $x$ 能将数 $v$ 合法分组的充要条件是 $v~\text{mod}~ x \leq \lfloor \frac{v}{x} \rfloor$。

考虑直接 check 所有合法的 $x$，找到最大的一个。

首先我们可以对每个数用数论分块拆成若干个区间，对于每个数而言有 $\sqrt V$ 个区间满足 $\lfloor \frac{a_i}{i} \rfloor$ 的值相同。

复合共 $n \sqrt V$ 个区间，对每个区间可以用类似维护一次函数最值的做法查最大的 $x$，时间复杂度 $O(n \sqrt V \log n)$。

提供一种单根做法。

考虑再多推点性质：

- 记 $am = \min_{i = 1} ^ n a_i$。

- 对于 $x \leq \sqrt {am}$ 的数肯定全都合法，因为此时余数严格小于 $\sqrt {am}$ 而商严格大于等于 $\sqrt {am}$。

- 对于 $x > \sqrt {am}$，我们枚举商，此时的商只有 $\sqrt {am}$ 种。

- 记商为 $w$。假设 $am = w \times x + y$，由于要满足上述的不等式，则 $y \in [0,w]$，显然存在不等式 $\lfloor \frac{am - w}{x}\rfloor \leq \lfloor \frac{am-y}{x}\rfloor \leq \lfloor \frac{am}{x}\rfloor$。化简一下即可得到 $\lfloor \frac{am}{x}\rfloor - 1 \leq x \leq \lfloor \frac{am}{x} \rfloor$。

- 所以此时需要 check 的 $x$ 数量级也为 $O(\sqrt {V})$。至此我们的时间复杂度也为 $O(n \sqrt V)$。

```cpp
/*
什么 jb。
一个想法是我们枚举小的数。
显然让这个数越大越好，设为 x
成立的条件是 \frac{v}{x} > v % x = v - v / x * x 
数论分块，然后直接暴力判每个段。
一个更好的想法是对 x < sqrt 的暴力。
对于 x > sqrt 的我们枚举 v / x，这只有 sqrt 个。 
*/
#include "bits/stdc++.h"
using namespace std;
const int Len = 5e2 + 5;
int n,m,a[Len],ans;
bool check(int as)
{
	if(as <= 0) return 0;
	for(int i = 1 ; i <= n ; i ++) if(a[i] % as > a[i] / as) return 0;
	return 1;
}	
#define ll long long
int main()
{
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i ++) scanf("%d",&a[i]);
	sort(a + 1 , a + 1 + n);
	ans = sqrt(a[1]);
	for(int i = 1 ; i <= sqrt(a[1]) + 1 ; i ++) 
	{
		if(check(a[1] / i)) ans = max(ans , a[1] / i);
		if(check(a[1] / i - 1)) ans = max(ans , a[1] / i - 1);
	}
	ll res = 0;
	for(int i = 1 ; i <= n ; i ++) res += ((a[i] + ans) / (ans + 1));
	printf("%lld\n",res);
	return 0;
}
```

---

