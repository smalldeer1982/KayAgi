# [AGC011B] Colorful Creatures

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc011/tasks/agc011_b

すぬけ君は，$ N $ 匹の変わった生き物を見つけました． それぞれの生き物には色と大きさが定まっており，$ i $ 番目の生き物の色は $ i $，大きさは $ A_i $ で表されます．

どの生き物も，大きさが自分の $ 2 $ 倍以下であるような他の生き物を吸収することができます． 大きさ $ A $，色 $ B $ の生き物が大きさ $ C $，色 $ D $ の生き物を吸収すると ($ C\ \leq\ 2\ \times\ A $)，合体して大きさ $ A+C $，色 $ B $ の生き物になります． ここで，$ 2 $ 匹の生き物の大きさによっては，どちらも他方を吸収することが可能な場合があります．

すぬけ君がこの生き物たちを観察していると，合体を繰り返して，最終的に $ 1 $ 匹になりました． このとき，残った生き物の色として考えられるものは何種類あるかを求めてください．

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 100000 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- $ A_i $ は整数

### Sample Explanation 1

最終的に残った生き物の色としては色 $ 1 $, $ 3 $ が考えられます． 例えば，色 $ 3 $ の生き物が色 $ 2 $ の生き物を吸収し，次に色 $ 1 $ の生き物が色 $ 3 $ の生き物と合体すると，色 $ 1 $ の生き物のみが残ります．

### Sample Explanation 2

同じ大きさの生き物が複数いる場合もあります．

## 样例 #1

### 输入

```
3
3 1 4```

### 输出

```
2```

## 样例 #2

### 输入

```
5
1 1 1 1 1```

### 输出

```
5```

## 样例 #3

### 输入

```
6
40 1 30 2 7 20```

### 输出

```
4```

# 题解

## 作者：chinazhanghaoxun (赞：6)

## 分析

看到这个题目要求我们求出可以活到最后的生物，应该就可以进行二分了，不知道大家有没有想到。

首先我们来进行一下单调性证明。如果当前这个生物可以被吸收，那么比它小的任何一个生物也能被吸收。反之，如果一个生物吸收不了现在的生物，那么比当前生物大的生物它一定也吸收不了。所以我们就知道这道题可以二分求出那些生物可以活到最后了，所以这道题具有单调性，可以二分，接下来看看代码怎么写吧。
## 思路

首先我们对数组 $A$ 进行升序排序，这样方便我们一会进行判断。接下来，二分谁可以活到最后，如果当前这个生物都可以的话，那就继续向更小的方向尝试所有情况，否则就往更大的方向尝试。

判断函数实际上就是一个贪心的过程：从小到大吸收生物，只要出现有一个生物不能吸收，那么比那个生物大的生物也不行，就不能活到最后，反之就可以。
## 代码

这次就不放代码了，众所周知，Atcoder 的题目码量是很少的，只需要注意开 long long。

---

## 作者：ZZ_WYZ (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_agc011_b)


 $2024年-11月-12日$ $17:29$ 被打回

 $2024年-11月-12日$ $18:18$ 二次提交

 $2024年-11月-13日$ $14:31$ 被打回

 $2024年-11月-12日$ $14:37$ 三次提交

 $2024年-11月-13日$ $21:58$ 被打回

$2024年-11月-14日$ $7:36$ 四次提交

---


## 题意理解

给定一个序列 $n$ ，对于 $a[i]$ 可以吃掉 $≤a[i]*2$ 的数，看这个数是否能吃完所有数。最后输出
 $$
ans = \sum_{i = 1}^{n} {是否吃完所有数（是为1，否为0）}
 $$
 

---

## 暴力

首先能够立马想到的就是排序，之后对于每个数看它能不能吃掉后面的数，能的话就吃掉，更新这个数的大小。

综合复杂度为 $O(n^2)$ ，效率感人。

## 正解

仍然排序。

十分易得每个数都能吃掉小于它的任何数，也是非常符合前缀和的规律啊。考虑用**前缀和**维护每个数最起码的大小为多少。

接下来怎么办呢？

我们还能知道如果一个数如果有能力吃掉比它大的数，那它就能变成最大的能吃掉的数的前缀和，根据这个递推规律我们能得到以下结论：

- 对于一个已经吃掉所有能吃的数之后的数，如果它吃不掉任何比它大的数，那么在他之前的数都无法吃掉所有数。

因此：我们考虑从倒数第二个数开始计算它是否能吃掉后面的数，如果可以，使最终的答案加一，如果不行就说明这个数之前的所有数都不行，直接跳出即可。



---

## Code

~~喜闻乐见的代码环节~~

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[100010],ans,pre[100010];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+1+n);
	pre[0]=0;
	ans++;
	for(int i=1;i<=n;i++){
		pre[i]=pre[i-1]+a[i];
	}
	for(int i=n-1;i>=1;i--){
		if(pre[i]*2>=a[i+1])ans++;
		else break;
	}
	cout<<ans;
	return 0;
//十年 OI 一场空，不开 long long 见祖宗。
}
```

给个过吧。

---

## 作者：UKE_Piu (赞：2)

[传送门](https://www.luogu.com.cn/problem/AT_agc011_b)
## 分析及思路
因为涉及到生物的大小 $a_i$，所以可以先对其进行排序。这样做并不会影响颜色。原因是每种生物的颜色都不同，我们只关心颜色种类的数量而不是具体的种类。

考虑贪心。可以使用前缀和进行一个优化。

手玩样例3可以发现一个规律。答案就是找到一个最大的 $i$ 使得对于任意的 $i \le j \le n $ 都可以让 $j$ 为最后剩下的颜色，答案就是 $n-i+1$。

## Code
别忘了开 long long。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n;
const int N=1e+5+5;
ll a[N],s[N],ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i];
	for(int i=n;i>=1;i--){
		if(s[i-1]*2ll>=a[i]) ans++;
		else break;
	}
	cout<<ans+1;
	return 0;
}
```

---

## 作者：SMall_X_ (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/AT_agc011_b)

---

我们知道，要想使一个生物能活到最后，那么它进行的每一次吸收前，它的大小应当尽可能大，所以我们考虑贪心，对生物的大小从小到大排序，每个生物都从小的开始吸收，看能不能活到最后，时间复杂度 $\mathcal{O(n^2)}$。

我们还知道，排序后，生物 $i$ 能活到最后，则生物 $i+1\sim n$ 一定也能活到最后；生物 $i$ 不能活到最后，则生物 $1\sim i-1$ 一定也不能活到最后。所以我们可以在排序后从后往前扫描 $a_i$，用前缀和求得 $a_i$ 当前最大的大小（即吸收前面所有比它小的），判断能否吸收生物 $i+1$，吸收不了则它就或不到最后，比它小的生物也或不到最后，所以终止扫描。时间复杂度降为 $O(n)$。 

## $\texttt{code}$

```cpp
/*Written by smx*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define QAQ cout<<"QAQ\n";
const int MAXN=1e5+5,inf=1e18,mod=1e9+7;
int n,ans=1;
int a[MAXN],sum[MAXN];
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1]+a[i];
	}
	for(int i=n-1;i>=1;i--){
		if(sum[i]*2>=a[i+1]){
			ans++;
		}else{
			break;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：lzh_juruo (赞：0)

# [AGC011B] Colorful Creatures 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_agc011_b)

考虑二分。

首先对数组进行排序，对于生物 $i$ ，如果它可以活到最后，那么比它大的生物 $i+1,i+2,...,n$ 也可以活到最后。反之如果不行，那么比它小的生物 $1,...,i-2,i-1$ 也不能活到最后，满足单调性。

 check 函数也不难写，考虑贪心，从小到大吸收生物，如果有一个生物不能吸收，那么比那个生物大的生物也不行，就不能活到最后，反之就可以。

 AC 代码，注意要开 long long ：
 
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[100002];
bool check(int x){
	int big = a[x];
	for(int i = 1;i <= n;i++){
		if(i == x) continue; //不能自己吸收自己
		if(big * 2 >= a[i]) big += a[i];
		else return false;
	}
	return true;
}
signed main(){
	cin>>n;
	for(int i = 1;i <= n;i++) cin>>a[i];
	sort(a + 1,a + n + 1);
	int l = 0,r = n;
	while(l < r){
		int mid=l + r >> 1;
		if(check(mid)) r = mid;
		else l = mid + 1;
	}
	cout<<n - r + 1;
    return 0;
}
```

---

## 作者：banglee (赞：0)

## AT_agc011_b [AGC011B] Colorful Creatures 题解
[题目传送门](https://www.luogu.com.cn/problem/AT_agc011_b)

## 正文
通过对生物按大小进行排序，不失一般性，可以认为 $A_1 \le A_2 \le \dots \le A_N$。设 $t$ 为满足 $2 \sum^k_{i=1} A_i < A_{k+1}$ 的最大的 $k$。（如果不存在这样的 $k$，则 $t = 0$）为了让第 $1,2,\dots,t$ 号生物能够一直保留到最后，需要在吸收第 $t + 1$ 号生物之前变得比 $\frac{A_{t + 1}}{2}$ 更大，但是因为即使第 $1,2,\dots,t$ 号的生物全部合并也做不到这一点，所以这是不可能的。（当然，也不可能先吸收比第 $t + 1$ 号更大的生物）另一方面，第 $t + 1,t + 2,\dots,N$ 号的生物可以通过依次吸收较小的生物最终剩下来。

因此，计算上述的 $t$（左侧的总和可以通过顺序尝试 $k = 1, 2,\dots,N$ 全部在 $O(N)$ 时间内求出），输出 $N - t$ 就可以了。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
int n,cnt;
int main(){
    scanf("%d",&n);
    vector<long long> a(n),b(n);
    vector<bool> ans(n+1,false);
    for(int i=0;i<n;i++)
        scanf("%lld",&a[i]);
    sort(a.begin(),a.end());
    for(int i=0;i<n;i++)
    {
        if(i==0) b[i]=a[i];
        else b[i]=b[i-1]+a[i];
    }
    ans[n]=true;
    for(int i=n-1;i>=0;i--)
    {
        long long v=b[i]*2ll;
        int h=upper_bound(a.begin(),a.end(),v)-a.begin()-1;
        ans[i]=ans[h];
        if(i==n-1) ans[i]=true;
    }
    for(int i=0;i<n;i++)
        if(ans[i]) cnt++;
    printf("%d",cnt);
    return 0;
}
```

---

## 作者：邈云汉 (赞：0)

由于每种颜色的怪兽只有一只，所以如果最后要想剩下某一种颜色，一开始该颜色的怪兽就必须能吃光所有的怪兽（一旦它在某个时刻被吃，这种颜色就绝迹了）。根据逻辑，把能吃的都吃了，如果吃完了，那就可以剩下这种颜色，反之，如果到某一个时刻发现剩下的怪兽一只都不能吃，那就不能剩下该颜色。

显然，一只怪兽一定能吃掉比自己小的怪兽，如果以此时的大小吃不掉后面比它大的怪兽，那么它的颜色就不可能作为最终答案，同时一开始比它小的怪兽的颜色更不可能成为最终答案。

先将数组从小到大排序，求一个前缀和（前面比它小的一定都能吃）。用一个变量来计数，如果某个怪兽不能吃掉下面一只，那么就将变量置为 0，否则增加 1。还有，前缀和会爆，记得开 long long。

~~众所周知 Atcoder 的题目的代码实现是非常简单的，~~ 这里就不发代码了。

---

## 作者：红黑树 (赞：0)

[可能更好的阅读体验](https://rbtr.ee/agc-011-b)

## [题意](https://atcoder.jp/contests/agc011/tasks/agc011_b)
有 $n$ 个生物，第 $i$ 个生物有大小 $A_i$ 和颜色 $i$。

第 $i$ 个生物可以吞噬第 $j$ 个元素当：
$$A_j \leq 2 \cdot A_i$$

这些生不停的吞噬着其它生物，最终成为一个生物。求该生物可能的颜色的数量。

$2 \leq n \leq 10^5, 1 \leq A_i \leq 10^9$

## 题解
考虑第 $i$ 个生物有没有可能成为最终的那个生物：

第 $i$ 个生物必然是从大小最小的生物开始吞噬，如果最后全部吞噬了，那么这个生物就是答案之一。

这样得到了一个 $\mathcal O\left(n^2\right)$ 的算法。

考虑如何优化：
1. 把数组排序，二分从哪个点开始可以。
2. 考虑到如果生物 $i$ 不能成为最后一个生物，那么一定是 $i$ 的**前缀和**的两倍小于第 $i + 1$ 个点的大小。所以，把数组排序，**从右往左** 找到第一个 $i$ 的**前缀和**的两倍小于第 $i + 1$ 个点的大小的点。那么这个点，以及更靠前的点不然不能成为最后一个生物。

因为要排序，复杂度是 $\mathcal O\left(n \log n\right)$。

## 代码
```cpp
// By rbtree (https://rbtree.archi)
// Please submit with C++14!
#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>
#define ra _Read()

using tp = long long;
tp _Read();
using namespace std;
constexpr bool __MTCS__ = 0;
constexpr tp Hat_N = 1e5 + 3;

namespace __SOL__ {
signed main() {
  tp n = ra, cnt = 0;
  array<tp, Hat_N> a, s;
  for (tp i = 1; i <= n; ++i) {
    a[i] = ra;
  }
  stable_sort(a.begin() + 1, a.begin() + n + 1);
  for (tp i = 1; i <= n; ++i) {
    s[i] = s[i - 1] + a[i];
  }
  for (tp i = n; i; --i) {
    if (s[i] * 2 < a[i + 1]) {
      break;
    }
    ++cnt;
  }
  cout << cnt << '\n';
  return 0;
}
}  // namespace __SOL__

signed main() {
  tp __MTCS__ = ::__MTCS__ ? ra : 1;
  while (__MTCS__--) {
    __SOL__::main();
  }
  return EXIT_SUCCESS;
}

tp _Read() {
  bool __neg(0);
  char __c(getchar());
  tp __val(0);
  for (; __c < 48 || __c > 57; __c = getchar()) {
    __neg = __c == 45;
  }
  for (; __c > 47 && __c < 58; __c = getchar()) {
    __val = __val * 10 + (__c & 15);
  }
  return __neg ? ~__val + 1 : __val;
}
```

---

