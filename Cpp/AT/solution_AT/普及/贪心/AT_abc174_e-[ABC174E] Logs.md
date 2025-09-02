# [ABC174E] Logs

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc174/tasks/abc174_e

丸太が $ N $ 本あり、それぞれ長さは $ A_1,A_2,\cdots,A_N $ です。

これらの丸太を合計 $ K $ 回まで切ることができます。 長さ $ L $ の丸太を片端から $ t\ (0\ <\ t\ <\ L) $ の位置で切ると、長さ $ t,L-t $ の丸太に分かれます。

丸太を合計 $ K $ 回まで切った後最も長い丸太の長さが最小でいくつになるか求め、小数点以下を切り上げた値を出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ K\ \leq\ 10^9 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- 入力はすべて整数である。

### Sample Explanation 1

\- まず、長さ $ 7 $ の丸太を片端から $ 3.5 $ の位置で切り、長さ $ 3.5 $ の丸太二本に分けます。 - 次に、長さ $ 9 $ の丸太を片端から $ 3 $ の位置で切り、長さ $ 3 $ と $ 6 $ の丸太に分けます。 - 最後に、長さ $ 6 $ の丸太を片端から $ 3.3 $ の位置で切り、長さ $ 3.3 $ と $ 2.7 $ の丸太に分けます。 すると、最も長い丸太の長さは $ 3.5 $ になります。これが最小なので、小数点以下を切り上げた $ 4 $ を出力します。

## 样例 #1

### 输入

```
2 3
7 9```

### 输出

```
4```

## 样例 #2

### 输入

```
3 0
3 4 5```

### 输出

```
5```

## 样例 #3

### 输入

```
10 10
158260522 877914575 602436426 24979445 861648772 623690081 433933447 476190629 262703497 211047202```

### 输出

```
292638192```

# 题解

## 作者：Fire_flame (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc174_e)

**题意简述：**

有 $n$ 个数 $a_1,a_2\dots a_n$。你要进行最多 $k$ 次操作。

每一次操作可以选一个数 $a_i$，将它分成 $t,a_i-t(0<t<a_i)$ 两个数。求问操作完后最大的数最小是多少，请四舍五入到整数位输出。

## $\mathtt{Solution}$

我们可以二分答案 $ans$，由于 $1\le a_i\le 10^9$，所以不会超时。

因为每一段最长是 $ans$，性价比最高的操作就是每一次减掉 $ans$，所以对于 $a_i$，在它这里需要花费 $[\dfrac{a_i}{ans}]$ 的操作步数。

但是要注意，如果 $a_i=ans$（样例 $2$），是不用增加步数的。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 5;
int n, k, a[MAXN];
bool check(int x){
	int cnt = 0;
	for(int i = 1;i <= n;i ++){
		cnt += a[i] / x;
		if(a[i] == x)cnt --;
	}
	return cnt <= k;
}
int main(){
	scanf("%d%d", &n, &k);
	for(int i = 1;i <= n;i ++)scanf("%d", &a[i]);
	int l = 1, r = 1e9;
	while(l < r){
		int mid = (l + r) / 2;
		if(check(mid))r = mid;
		else l = mid + 1;
	}
	printf("%d", l);
	return 0;
}

```


---

## 作者：PineappleSummer (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc174_e)

读题，看到“最大值最小”，考虑二分答案。

主函数部分就是板子，不再说了，代码见下：
```cpp
int l=1,r=1e9;
while(l<r)
{
	int mid=(l+r)>>1;
	if(check(mid)) r=mid;
	else l=mid+1;
}
```

考虑如何 check。

每次 check 一个数 $x$，这个 $x$ 代表操作完成后的最大值。我们判断使得操作完成后的最大值为 $x$ 的操作数是否小于等于 $k$，如果是让 `r=mid`，否则 `l=mid+1`。check 代码见下：
```cpp
bool check(int x)
{
	int sum=0;//sum记录操作数
	for(int i=1;i<=n;i++)
	{
		if(a[i]%x==0) sum+=a[i]/x-1;//如果a[i]是x的整倍数，则需要操作a[i]/x-1次
		else sum+=a[i]/x;//否则操作a[i]/x次
	}
	return sum<=k;//判断sum是否小于等于k
}
```

[完整代码](https://atcoder.jp/contests/abc174/submissions/44188705)，时间复杂度 $O(n\log n)$。

---

## 作者：jasonshen_ (赞：1)

# 思路

二分答案。

首先有两种特殊情况需要处理：

1. $K = 0$：

    我们无法执行切片操作，因此最短的 $L$ 是当前最大的木棒长度。

2. $K \geq \sum_{i=1}^{n}{A_i} - n$：

    因为我们确实可以随意切下整个木棒。所以答案将是 $\max(A)$。

接下来考虑二分答案，令左右端点分别为 $L$ 和 $R$，中点为 $mid = \lfloor\frac{L+R}{2}\rfloor$。

对于每个木板 $i$，计算它被切割多少次后长度会达到或超过 $mid$。如果总共切片操作的次数超过 $K$，则必须缩小上限，即 $R = mid-1$；否则必须增加下限，即 $L=mid+1$。

重复这个过程，直到 $L=R$，此时最短的 $L$ 是要求解的答案。

# CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
long long a[200010];
bool poss(long long x){
    long long cnt = 0;
    for(int i = 1;i<=n;i++){
        if(a[i]<=x)continue;//如果这根木材在>=x的情况下已经够砍了，那么就不需要再尝试 
        cnt += (a[i]+x-1)/x-1;//加上切几刀可以把长为a[i]的木头分成大小为x的小木棒 
    }
    return cnt<=k;//是否符合操作数 
}
int main(){
    cin>>n>>k;
    for(int i = 1;i<=n;i++){
        cin>>a[i];
    }
    long long l = 0,r = 1000000000;//二分答案 
    while(r-l>=2){
        int mid = (l+r)/2;
        if(poss(mid))r = mid;//如果当前这个x可行，那么记录它 
        else l = mid;//否则将搜索右端点变小 
    }
    if(poss(l+1))cout<<l+1<<endl;//注意小于等于的边界集与向上取整是一致的 
    else cout<<l<<endl;
    return 0;
}
```

---

## 作者：rickyxrc (赞：1)

本文章遵守知识共享协议 CC-BY-NC-SA，同步发表于洛谷题解区，转载时须在文章的任一位置附上原文链接和作者署名（rickyxrc）。推荐在[我的个人博客](https://blog.rickyxrc.cc)阅读。

### 题面大意

给定 $n$ 个数 $A_1,A_2,\cdots,A_n$，并给你 $k$ 次操作机会，每次你从 $A$ 中选择一个数 $a\in A$ 并指定一个实数 $t \in (0,a)$，在 $A$ 中删除 $a$ 并加入 $t$ 和 $a-t$，求使得 $A$ 中最大值最小的最小值。

图形化理解：给你 $n$ 条绳子，你需要切 $k$ 刀，求最长长度最短可以被切成多少。

### 解法

显然，我切的刀数越多，最长长度就会越小。

考虑二分答案，二分那个最大值，检验使得所有的值小于给定值的方案数能否小于要求的 $k$ 次，如果满足继续缩小右边界，不满足扩大左边界，直到两边界趋近于一个值为止。

#### 为什么想到二分答案？

通常，我们会一个一个判断给定条件是否合法，复杂度为 $O(n^2)$，也就是遍历和检查的复杂度乘积。

而这里，题目的问题具有单调性，就是上文所说的切的越多，最长长度越小。

考虑二分答案，也就是二分可以的最长长度，计算出让所有长度小于那个长度的需要刀数，判断是否合法，再二分，直到找到答案为止。

我们要将一个数 $x$ 切成不大于 $l$ 的段，那么每次切的长度最大可以为 $l$，最少要切 $\lceil \frac{x}{l} \rceil-1$ 段，我们要判断是否合法，只需要计算 $\sum_{i=1}^n \lceil \frac{x_i}{l} \rceil-1$ 是否小于 $k$ 即可。

判断答案是否合法的函数就可以实现如下：

```cpp
// 这里是指切成小于val的段的总刀数是否满足
bool check(double val)
{
  long long res = 0;
  for (long long i = 1; i <= n; i++)
    if (lenn[i] - val > 1e-3) // 注意精度
      res += (long long)(ceil(double(lenn[i]) / val)) - 1;
  return res <= k;
}
```

主函数也很好实现，但是记得注意精度！！

```cpp
#include <stdio.h>
#include <math.h>
#define maxn 200007

long long lenn[maxn];
long long n, v, k, mx;
long long max(long long a, long long b)
{
  return a > b ? a : b;
}

signed main()
{
  scanf("%lld%lld", &n, &k);
  for (long long i = 1; i <= n; i++)
    scanf("%lld", lenn + i),
        mx = max(mx, lenn[i]);
  
  double l = 0, r = mx, mid;
  while (r - l > 1e-6)
  {
    mid = (l + r) / 2.0;
    if (check(mid))
      r = mid;
    else
      l = mid;
  }
  
  printf("%d", (long long)(mid + 1));
  return 0;
}
```


---

## 作者：linxuanrui (赞：0)

### 思路

这题要求操作完后最大的数最小是多少，显然是用二分。

这道题关键在于 `check` 函数如何编写。首先，`check` 函数会传入一个参数 $x$，表示在 $k$ 次内能否使最大值小于等于 $x$。

接下来要知道的是一个数 $a_i$ 要多少步才能使它小于等于 $x$（这里就是为了满足最大值小于等于 $x$，所以每个数都要小于等于 $x$）。这时候，我们就要分情况讨论。

1. $a_i\le x$：此时不需要操作。

2. $a_i>x$：因为对于每次操作，可以分成 $t$ 和 $a_i-t$，如果要减少操作的次数，那么就要使 $t$ 和 $a_i-t$ 之中有一个要小于等于 $x$。所以总的操作次数就是 $a_i$ 整除 $x$。

有了 `check` 函数，代码应该就不难写了吧。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,k,a[200001],l,r;
bool check(ll x){
	ll cnt = 0;
	for(ll i = 1;i <= n;i++){
		if(a[i] > x)cnt += a[i] / x;
	}
	return cnt <= k;
}
int main(){
	ios::sync_with_stdio(false); 
	cin.tie(0);
	cout.tie(0);
	cin >> n >> k;
	for(ll i = 1;i <= n;i++)cin >> a[i],r = max(r,a[i]);
	while(r - l > 1){
		ll mid = (l + r) >> 1;
		if(check(mid))r = mid;
		else l = mid;
	}
	cout << r;
}
```

---

## 作者：zhouzihe (赞：0)

## 1 观察题目
观察题目，发现我们可以对最终的答案进行二分。设最后的答案为 $ans$，需要的操作次数为 $\sum\limits_{i=1}^{n}{\left\lfloor\frac{a_i}{x}\right\rfloor}$。若操作次数大于 $k$，将 $ans$ 增大，否则则减小。
## 2 code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long int n,k,a[200005],lb,ub=1e10,mid;
bool check(long long int x){
	int sum=0;
	for(int i=1;i<=n;i++){
		sum+=a[i]/x;
		if(a[i]%x==0){
			sum--;
		}
	}
	return sum<=k;
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	while(ub-lb>1){
		mid=(ub+lb)/2;
		if(check(mid)){
			ub=mid;
		}
		else{
			lb=mid;
		}
	}
	cout<<ub;
	return 0;
}
```


---

## 作者：VitrelosTia (赞：0)

思路很好想，就是二分搜索最长木棍的长度，设为 $x$。事实上题目给出的限制条件就只有 $x$ 能切出不大于 $k$ 段，然后由于显然每次切掉 $x$ 是最好的策略，于是每一根需要花费的次数就是 $\lceil \dfrac{a_i}{x} \rceil - 1$，二分时累加然后看是否满足不大于 $k$ 的条件即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int M = 2e5 + 5, INF = 1e9;
int n, k, a[M];

bool check(int x) {
	int sum = 0;
	for (int i = 1; i <= n; i++) {
		if (a[i] % x == 0) sum += (a[i] / x) - 1;
		else sum += a[i] / x;
	}
	return sum > k;
}

int b_find() {
	int l = 1, r = INF;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (check(mid)) l = mid + 1;
		else r = mid - 1;
	} 
	return l;
}

signed main() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++) cin >> a[i];
	cout << b_find();
	return 0;
}
```

---

