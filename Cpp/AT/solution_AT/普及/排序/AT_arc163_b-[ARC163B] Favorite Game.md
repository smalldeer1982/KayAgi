# [ARC163B] Favorite Game

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc163/tasks/arc163_b

長さ $ N $ の整数列 $ A=(A_1,A_2,\dots,A_N) $ が与えられます。あなたは、以下の操作を好きな回数（$ 0 $ 回でもよい）行うことが出来ます。

- $ 1\ \le\ i\ \le\ N $ を満たす整数 $ i $ を $ 1 $ 個選び、$ A_i $ を $ 1 $ 増やすか $ 1 $ 減らす。
 
あなたの目標は、$ A_1\ \le\ A_i\ \le\ A_2 $ を満たす整数 $ i(3\ \le\ i\ \le\ N) $ の個数を $ M $ 個以上にすることです。目標を達成するために必要な最小の操作回数を求めてください。

## 说明/提示

### 制約

- $ 3\ \le\ N\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ M\ \le\ N-2 $
- $ 1\ \le\ A_i\ \le\ 10^9 $
 
### Sample Explanation 1

以下のように操作を行うことで $ A_1\ \le\ A_i\ \le\ A_2 $ を満たす整数 $ i(3\ \le\ i\ \le\ N) $ の個数を $ 1 $ 個以上に出来ます。 - $ i=3 $ を選び、$ A_i $ を $ 1 $ 減らす。 - $ i=2 $ を選び、$ A_i $ を $ 1 $ 増やす。 $ 1 $ 回以下の操作回数で目標を達成することは出来ないため、答えは $ 2 $ です。

### Sample Explanation 2

始めから目標を達成していることもあります。

## 样例 #1

### 输入

```
3 1
2 3 5```

### 输出

```
2```

## 样例 #2

### 输入

```
5 2
1 4 2 3 5```

### 输出

```
0```

## 样例 #3

### 输入

```
8 5
15 59 64 96 31 17 88 9```

### 输出

```
35```

# 题解

## 作者：Magus (赞：8)

蒟蒻写的第一篇题解，大佬们多多指教。~~用来水咕的~~

题意：

给定 $N,M$ 和序列 $A_n$，进行操作：

- 取一个 $A_i$，将 $A_i$ $+1$ 或 $-1$。

求最少需要多少次操作使得至少有 $M$ 个 $i(3\le i\le N)$ 满足 $A_1\le A_i \le A_2$。

显然可以得出：改变 $A_1$ 和 $A_2$ 最优。

假设任意一个 $A_i$ 不在 $A_1$ 到 $A_2$ 之内，那我们就进行操作使这个 $A_i$ 进入区间。虽然能看出来修改 $A_i$ 和 $A_1$ 或 $A_2$ 进行的操作次数是相同的，但是如果修改 $A_1$ 或 $A_2$ 也许能使后面的某些 $A_i$ 也进入了此区间，所以得出结论：改变 $A_1$ 和 $A_2$ 最优。

那我们就将 $A_3$ 到 $A_n$ 之内的元素排序，计算要将 $[A_1,A_2]$ 修改几次就做出来此题了。

完结撒花~

AC code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,qwq,awa=1e18,arr[1919810];
signed main()
{
	cin>>n>>m;
	for(int i=0;i<n;i++)
	{
		cin>>arr[i];
	}
	stable_sort(arr+2,arr+n);
	for(int i=2;i<=n-m;i++)
	{
		awa=min(awa,max(0ll,arr[0]-arr[i])+max(0ll,arr[i+m-1]-arr[1]));
	}
	cout<<awa;
	return 0;
}
```

求管理大大让通过。

---

## 作者：fengxiaoyi (赞：3)

$2023/7/8$：把代码块的语言改成了 `c++`。

### 题意简述

给一个长度为 $N$ 的序列 $A$，你可以进行若干次操作：

- 选择一个整数 $i$ 满足 $1\le i \le N$，将 $A_i$ 加上或减去 $1$。

求最少需要多少步，使得至少有 $M$ 个整数 $i$ 满足 $3\le i \le N$，$A_1 \le A_i \le A_2$。

### 解法

可以发现一个性质，**只改变 $A_1,A_2$ 的值是最优的**。

#### 证明

设 $A_1$ 的值为 $u$，如果它要包含的区间的最小值为 $u'$（这里，$u'\lt u$，因为如果 $u'\ge u$，$A_1$ 可以不做改变），则改变 $A_1$ 只需 $u-u'$ 步。

而如果改变的不是 $A_1$，仅仅是将 $u'$ 改成大于等于 $u$ 的数就要花 $u-u'$ 步了，如果还有其它点的值 $r$ 满足 $u'\le r\lt u$，那步数一定大于 $u-u'$ 步。

改变 $A_2$ 同理。

综上可得，只改变 $A_1,A_2$ 的值是最优的。

再配一张图理解一下（其中，红色的点分别表示 $A_1,A_2$，红线表示 $A_1,A_2$ 移动的步数，蓝线为其它点移动的步数，可以看出红线总长比蓝线总长短）

![](https://cdn.luogu.com.cn/upload/image_hosting/r6l7pk8s.png)

还有一个很好证明性质，包含的区间一定是按顺序（从大到小、从小到大都可以）排序中一个连续的子序列。

#### 算法简述

对后 $N-2$ 个点从小到大排序（当然，从大到小也可以），依次枚举长度为 $M$ 的区间（即左端点在 $[3,N-M+1]$ 的长度为 $M$ 的区间）。求出将 $A_1$ 改变成小于等于左端点的值，$A_2$ 改变成大于等于右端点的值最少需要的步数即可。

### 代码

```c++
#include<bits/stdc++.h>
using namespace std;
int n,m,a1,a2,b[200010],ans=0x7fffffff;
bool cmp(int x,int y){
	return x<y;
}
int main(){
	scanf("%d%d",&n,&m);
	scanf("%d%d",&a1,&a2);//A1,A2分开读
	n-=2;
	for(int i=1;i<=n;i++) scanf("%d",&b[i]);
	sort(b+1,b+n+1,cmp);
	for(int i=1;i<=n-m+1;i++) ans=min(ans,max(a1-b[i],0)+max(b[i+m-1]-a2,0));
	printf("%d",ans);
	return 0;
}
```


---

## 作者：yydfj (赞：2)

这是本蒟蒻第三十次写的题解，如有错误点请好心指出！

## 问题简述

有一个长度为 $n$ 的序列 $a$，你可以给数 $a_i(1 \le i \le n)$ 加或减一次 $1$，问最少要加或减多少次 $1$ 使得至少有 $m$ 个 $i(3 \le i \le n)$ 满足 $a_1 \le a_i \le a_n$。

## 解法综述

根据题意，很容易就想到贪心，要想让尽可能多的数的值在 $a_1$ 到 $a_2$ 之间，就一定要让 $a_1$ 尽可能小或让 $a_2$ 尽可能大，即让 $a_1$ 到 $a_2$ 之间的范围变得更大以便容纳更多的数。

根据上述贪心策略，将 $a_3$ 至 $a_n$ 从小到大排序，对于长度为 $m$ 的区间 $[i,i+m-1]$，发现有以下四种情况：

1. 若 $a_1 \le a_i$ 且 $a_2 \ge a_{i+m-1}$，说明目前已经有 $m$ 个数在 $a_1$ 至 $a_2$ 范围内，则不需要做加或减。

2. 否则，若 $a_1 \le a_i$，说明目前 $a_2$ 的值不够大，最少需要让 $a_2$ 加上 $a_{i+m-1}-a_2$ 次 $1$ 才能满足题目要求。

3. 否则，若 $a_2 \ge a_{i+m-1}$，说明目前 $a_1$ 的值不够小，最少需要让 $a_1$ 减去 $a_1-a_i$ 次 $1$ 才能满足题目要求。

4. 若上述情况都不符合，说明要同时改变 $a_1$ 和 $a_2$ 的值，即让 $a_1$ 减去 $a_1-a_i$ 且让 $a_2$ 加上 $a_{i+m-1}-a_2$ 才能满足题目要求。

根据上述情况输出最少次数即可。

## 代码描述
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
long long n,m,a[200005],ll,rr,ans=1e18;
int main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	stable_sort(a+3,a+n+1);//从小到大排序
	for(int i=3;i<=n-m+1;i++)
	if(a[1]<=a[i]&&a[2]>=a[i+m-1]) ans=0;//说明目前已经有m个数在范围内，不需要做加或减
	else if(a[1]<=a[i]) ans=min(ans,a[i+m-1]-a[2]);//说明目前a[2]的值不够大，最少需要让a[2]加上a[i+m-1]-a[2]才能满足题目要求
	else if(a[2]>=a[i+m-1]) ans=min(ans,a[1]-a[i]);//说明目前a[1]的值不够小，最少需要让a[1]减去a[1]-a[i]才能满足题目要求
	else ans=min(ans,a[1]-a[i]+a[i+m-1]-a[2]);//说明要同时改变a[1]和a[2]的值，即让a[1]减去a[1]-a[i]且让a[2]加上a[i+m-1]-a[2]才能满足题目要求
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：andyli (赞：2)

易证操作必然在 $a_1$ 或 $a_2$ 上。故只需枚举 $a_3, \dots, a_n$ 排序后所有长度为 $m$ 的区间，将区间端点与 $a_1,a_2$ 比较即可。时间复杂度 $O(n\log n)$。  

```python
n, m, L, R, *a = map(int, open(0).read().split())
a.sort()
print(min(max(0, L - a[i]) + max(0, a[i + m - 1] - R) for i in range(n - m - 1)))
```

---

## 作者：beifa (赞：1)

## 思路：
首先我们不难证明的是，只操作 $A_1$ 和 $A_2$ 的解法永远是最优的。

考虑枚举，先从小到大排序 $A_3$ 到 $A_N$，然后考虑枚举区间长度为 $m$ 的数列（从 $3$ 开始），只需要枚举 $n-m-1$ 次，每一次都能求出 $A_1$ 和 $A_2$ 需要操作的次数，取最小值即可。

### Tips:

答案的初始值应该赋值 $1e18$ 并且开 long long。~~十年 OI 一场空，不开 long long 见祖宗。~~

## CODE：

```cpp
#include <bits/stdc++.h>
#define int long long
#define ld long double
using namespace std;

int n , m , a[200010] , ans = 1e18;//别赋值1e9

signed main()
{
    cin >> n >> m;
    for(int i = 1; i <= n ; ++i)
    {
        cin >> a[i];
    }
    sort(a+3,a+n+1);
    for(int i = 3 ; i+m-1 <= n ; ++i)
    {
        ans = min(ans, max(0LL, a[i + m - 1] - a[2]) + max(0LL, a[1] - a[i]));
    }
    cout << ans;
    return 0;
}
```

---

## 作者：yuheng_wang080904 (赞：0)

## 题意

给定 $N,M$ 和数列 ${A_N}$。定义一次操作为任取一个 $A_i(1\le i\le N)$ 加一或减一。求经过几次操作后可以使得至少有 $M$ 个 $i(3\le i\le N)$ 满足 $A_1\le A_i \le A_2$。

## 思路

挺简单的一道题。

首先由于是与 $A_1$ 和 $A_2$ 比大小，我们不妨把剩下的数排个序 $A_3\le A_4\le \cdots \le A_{N-1}\le A_N$。

然后我们考虑贪心：只改变 $A_1$ 和 $A_2$。结论的简单证明：对于一个原先不在范围内的 $A_i(3\le i\le N)$，我们要使得其在范围内，无论是改变它本身的数值，还是范围的大小，操作次数都相同（当 $A_i>A_2$ 时，操作 $A_i-A_2$ 次；当 $A_i<A_1$ 时，操作 $A_1-A_i$ 次）。但是如果改变其本身数值，只能使得一个数满足要求；而改变范围可能会包括进其他的数，同时还会节省下次改变范围时的操作次数。综上所述，改变范围是更优的。

确定只改变范围，那么这个题目就好做了。

我们枚举所有连续的 $M$ 个数，计算所需操作次数取最小值即可（只需要保证最小的大于等于 $A_1$，最大的小于等于 $A_2$，具体实现见代码）。这个过程 $O(n)$ 即可完成。

## 代码

放上代码主要部分，总时间复杂度 $O(n \log n)$：

```cpp
ll n=read(),m=read(),a[200005],ans=1e18;
int main(){
    for(int i=1;i<=n;i++)a[i]=read();
    sort(a+3,a+n+1);
    for(int i=3;i<=n-m+1;i++)ans=min(ans,max(0ll,a[1]-a[i])+max(0ll,a[i+m-1]-a[2]));
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：qwq___qaq (赞：0)

[题面](https://atcoder.jp/contests/arc163/tasks/arc163_b)

令值域为 $V$。

因为我们为了使一个元素进入区间，我们可以增加这个区间，或者移动这个元素，但是显然增加区间的时候可能会有其它元素加入这个区间，所以改变区间应该会更优。于是，贪心地，我们只改变区间的左右端点。

容易想到枚举左右端点，然后判断这个答案是否是满足 $\ge M$ 的，如果是，那么就和答案取 $\min$，时间复杂度是 $O(nV^2)$。显然不行，考虑优化。

- 首先，可以想到一个区间内元素的数量可以使用权值线段树维护，本题数据范围是 $10^9$，所以要考虑动态开点。

- 其次，对于同一个左端点，显然我们需要的是最小的可行的右端点，并且比这个右端点更小的都不行，比这个右端点更大的都可行，所以右端点的选取是具有单调性的，于是可以考虑二分。

- 最后，左端点显然需要正好选到元素上或者不变，所以我们枚举左端点的时候只需要枚举元素，而不需要枚举值。

时间复杂度 $O(n\log^2V)$，常数比较大（其实这个算法复杂度本身就比较大），不打快读好像过不了。（好像打了也不一定能过）

[code](https://atcoder.jp/contests/arc163/submissions/43223948)

---

## 作者：syzxzqy (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/AT_arc163_b)  
#### 思路:  
题目给出一个 $a$ 数列，每次操作可以让数列中一个数可以加 $1$ 或减 $1$，求需要在 $a_3$ 至 $a_n$ 中有至少 $m$ 个数满足 $a_1\leqslant a_i\leqslant a_2$ 的最小操作次数。  
首先看到这道题目，我们可以想到贪心，因为在修改 $a_3$ 至 $a_n$ 中每个数使满足条件和修改 $a_1(a_2)$ 操作次数是相同的。  
减少 $a_1$ 的值，增加 $a_2$ 的值对于其他的数是会减少操作次数的，因此我们只需修改 $a_1$、$a_2$ 的值。  
我们把 $a_3$ 至 $a_n$ 排个序，我们可以发现，如果修改 $a_1$、$a_2$ 的值，排序后满足的是一段数。  
我们枚举开头，$i$ 从 $3$ 枚举到 $n-m+1$，对于每个 $i$，结尾就是 $i+m-1$，$a_1$ 减少的次数就为 $a_1-\min(a_i,a_1)-a_2$，$a_2$ 增加的次数就为 $\max(a_{i+m-1},a_2)-a_2$，总修改次数为 $a_1-\min(a_i,a_1)-a_2+\max(a_{i+m-1},a_2)-a_2$，接着只要求出最小操作次数即可。
#### 代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+10,M=1e3+10;
int n,m,i,mi=2e9,a[N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(i=1;i<=n;++i) cin>>a[i];
	sort(a+3,a+n+1);//排序
	for(i=3;i<=n-m+1;++i)//枚举开头
		mi=min(mi,a[1]-min(a[1],a[i])+max(a[i+m-1],a[2])-a[2]);//求最小操作次数
	cout<<mi;
}
```


---

## 作者：xiaoming007 (赞：0)

## 思路

我们可以贪心地排序 $a_3$ 至 $a_n$，这样我们在枚举长度为 $m$ 的区间时，可以直接看 $a_i$ 到 $a_{i+m-1}$，然后计算代价时候也只需计算它们与 $a_1$、$a_2$ 的差值，答案就是最小的代价。

```cpp
// Author:Saint_ying_xtf = xiaoming007
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;
inline int max(int x, int y){return x > y ? x : y;}
inline int min(int x, int y){return x < y ? x : y;}
int n, m, ans = 1e18;
int mi, mx;
int a[200005];
signed main () {
	ios::sync_with_stdio(0);
	cin.tie(nullptr);cout.tie(nullptr);
	cin >> n >> m;
	for (int i = 1; i <= n; i ++) cin >> a[i];
	sort(a + 3, a + n + 1);
	for (int i = 3; i + m - 1 <= n; i ++) {
		ans = min(ans, max(0LL, a[i + m - 1] - a[2]) + max(0LL, a[1] - a[i]));
	}
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：引领天下 (赞：0)

题意：

给定一个长度为 $N$ 的整数序列 $A=(A_1,A_2,\dots,A_N)$，现在可进行任意次的以下操作：

- 选择 $1\le i\le N$，将 $A_i$ 加一或者减一。

问至少要经过多少次操作之后才能存在至少 $M$ 个 $i$ 使得 $A_1\le A_i\le A_2$。

做法：

贪心。首先，我们一定只会修改 $A_1,A_2$。原因很简单，如果对于某个 $A_i$ 不在 $[A_1,A_2]$ 中（不妨 $A_i>A_2$），我们想让他进入这个区间，那么如果修改 $A_i$，需要 $A_i-A_2$ 次操作；而如果修改 $A_2$，也是 $A_i-A_2$ 次操作。但是修改 $A_2$ 显然更优，因为如果修改 $A_i$ 那这些操作只能增加一个数到 $[A_1,A_2]$ 的范围内，而修改 $A_2$ 可能使后面的某些 $A_j$ 进入 $[A_1,A_2]$ 的范围内。所以修改 $A_1,A_2$ 一定比修改其他元素更优。

那么我们的做法就很简单了：对 $A_3,\dots,A_N$ 排序，依次选取 $M$ 个元素，则这 $M$ 个元素中最小的就对应了使这 $M$ 个元素位于区间 $[A_1,A_2]$ 中的 $A_1$，最大的对应 $A_2$。实际处理的时候注意可能 $A_1,A_2$ 直接就满足要求，算答案的时候和 $0$ 取 $\max$ 即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,m,ans=1ll<<60,a[200005];
signed main(){
    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+3,a+n+1);
    for(int i=3;i<=n-m+1;i++)ans=min(ans,max(a[1]-a[i],0ll)+max(a[i+m-1]-a[2],0ll));
    cout<<ans;
    return 0;
}
```

---

