# [NOISG 2024 Prelim] Party

## 题目背景

翻译自 [NOI SG 2024 Prelim B.Party](https://github.com/noisg/noi-2024-prelim)。

## 题目描述

James 有 $n$ 个朋友，他想选择其中的 $0$ 个或者更多朋友来参加他的聚会。第 $i$ 个朋友如果参加了他的聚会，会产生 $a_i$ 点快乐值。注意：有些朋友并不想参加聚会，所以他们的 $a_i$ 会是负的。

然而，他家只有一排 $n$ 个座位，而且因为社交距离，两个人不能坐在相邻的座位上。现在 James 想知道，如果他按照最优方案邀请朋友，这些朋友的快乐值的和最大为多少。

## 说明/提示

### 【样例 #1 解释】

James 可以邀请第 $1,4,5$ 位朋友。


### 【样例 #2 解释】

James 可以邀请唯一一位朋友。


### 【样例 #3 解释】

James 可以邀请第 $3,4,6$ 位朋友。


### 【数据范围】

|$\text{Subtask}$|分值|特殊性质|
|:-:|:-:|:-:|
|$0$|$0$|样例|
|$1$|$49$|$n\le 3$|
|$2$|$38$|$n\le 1000$|
|$3$|$13$|无|

对于 $100\%$ 的数据，$1 \le n \le 2 \times 10^5,-10^9 \le a_i \le 10^9$。

## 样例 #1

### 输入

```
5
3 2 -1 4 5```

### 输出

```
12```

## 样例 #2

### 输入

```
1
10```

### 输出

```
10```

## 样例 #3

### 输入

```
6
1 -3 2 10 -4 9```

### 输出

```
21```

# 题解

## 作者：abc1234shi (赞：4)

我们先将数组进行排序，因为如果从小到大排序到后面其实挺麻烦的，所以我是从大到小排序。因为两个人不能坐相邻的位置，我们要求出要坐几个人，一共有 $n$ 把椅子，要坐的人数就为 $(n+1)/2$ 的值向下取整。接下来就将答案加从 $a_1$ 一直加到 $a_n$。但是注意如果其中有负数，那么说明剩下的数都是负数，如果加上就得不偿失了，所以就停止循环。最后输出答案。
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[210000];
long long sum;
int cmp(int x,int y)
{
	return x>y;
}
int main() {
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
    	cin>>a[i];
	}
	sort(a+1,a+n+1,cmp);
	n=(n+1)/2;
	for(int i=1;i<=n;i++)
	{
		if(a[i]<=0)break;
		sum+=a[i]; 
	 } 
	
	cout<<sum;
   return 0;
}
```

---

## 作者：leo120306 (赞：2)

首先，由于两个人不能坐在相邻的座位上，实际能坐的人数为 $\lceil \dfrac n2 \rceil$。然后，贪心地想，肯定是选快乐值高的人参加聚会。所以 sort 一下，选欢乐值最高的 $\lceil \dfrac n2 \rceil$ 个人，求和一下就好了。

当然没那么简单，题中还有一些坑点。首先，$\lceil \dfrac n2 \rceil$ 个座位不一定要坐满，所以负分的人肯定不要邀请。然后答案最大值是 $2\times10^{14}$，所以要开 long long。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

int a[200005];

int main(){
	int n;
	long long ans=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	sort(a+1,a+1+n);
	for(int i=n;i>n/2&&a[i]>=0;i--){
		ans+=a[i];
	}
	printf("%lld",ans);
	
	return 0;
}
```

---

## 作者：2022_37_yzyUUU (赞：2)

# P10709题解

## 题面

从 $n$ 个朋友中选一些朋友，每个朋友都有一个快乐值，快乐值可能是负数。每个朋友不能坐在相邻的座位。

## 思路

优先选择快乐值大的朋友，这一点可以用排序解决，然后又因为每个朋友必须隔着坐，所以当有 $n$ 个朋友时，最多只能选 $\lfloor \frac{n+1}{2} \rfloor$ 个朋友，而且坚决不能选快乐值是负数的朋友。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,ans;//不开long long见祖宗
long long a[200005];
bool cmp(long x,long long y){//自定义降序排序
	return x>y;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+n+1,cmp);//sort排序
	for(int i=1;i<=(n+1)/2;i++)//向0取整
		if(a[i]>0)ans+=a[i];
   cout<<ans;
   return 0;//好习惯
}
```

---

## 作者：Jorisy (赞：1)

首先，因为“两个人不能坐在相邻的座位上”，因此最多只能有 $m=\left\lfloor\dfrac{n+1}2\right\rfloor$ 人。

然后，为了最大化快乐值，我们必然按快乐值从大到小选取人，而且不会取快乐值为负的人。

因此，设 $a$ 降序后为 $a'$，$s=\sum\limits_{i=1}^n[a_i>0]$，则我们的答案当然就是 $\sum\limits_{i=1}^{\min\{s,m\}}a'_i$。
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m,a[200005];
long long ans;

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1,greater<int>());
	m=n+1>>1;
	for(int i=1;i<=m&&a[i]>0;i++) ans+=a[i];
	cout<<ans; 
 	return 0;
}
```

---

## 作者：zhuxiangrui_2010 (赞：1)

感谢[DFs_YYDS](https://www.luogu.com.cn/user/1119406)和[I_am_Kun](https://www.luogu.com.cn/user/973540)的提醒，错误已改正。
## 题意
James 有 $n$ 个朋友、$n$ 个座位，两个朋友不能坐在相邻的座位上，选择其中任意个朋友，求每个朋友产生的快乐值 $a_i$ 之和的最大值。
## 思路
因为两个朋友不能坐在相邻的座位上，所以 $n$ 个座位可以坐 $\left \lfloor \frac{n+1}{2}  \right \rfloor$ 个人。

由于希望总快乐值最大，所以每个朋友产生的快乐值 $a_i$ 都应该取较大的。可以进行排序由大到小进行取值且 $a_i \le 0$ 时不取，易证得此时总快乐值最大。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[10000001],s=0;
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+n+1);
    for(int i=n;i>n/2;i--){
        if(a[i]<=0){
            break;
        }
        s+=a[i];
    }
    cout<<s;
	return 0;
}
```
完结撒花~

---

## 作者：RainCQwQ (赞：1)

# P10709 Solution
## 思路整理
想到，James 家有 $n$ 个椅子，~~可由于疫情的影响~~，隔一个椅子坐一个人。

让我们分类讨论一下：

- 当 $n$ 为单数时，最多可以坐 $\frac{n+1}{2}$ 个人。
- 当 $n$ 为双数时，最多可以坐 $\frac{n}{2}$ 个人。

即最多可以坐 $\lfloor \frac{n+1}{2} \rfloor$ 个人。

输出快乐值最大的 $\lfloor \frac{n+1}{2} \rfloor$ 个人即可，注意不要加上负数。

## Code
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int a[200005];
int main()
{
    int n;
    cin>>n;
    for(int i=0;i<n;i++) cin>>a[i];
    sort(a,a+n,greater<int>());
    n=(n+1)/2;
    long long ans=0;
    for(int i=0;i<n;i++) if(a[i]>=0) ans+=a[i];
    cout<<ans;
    return 0;
}
```

十年 OI 一场空，不开 `long long` 见祖宗。

---

## 作者：FurippuWRY (赞：1)

由于两个人不能坐在相邻的座位上，那么一共可坐 $\left\lceil\dfrac{n}{2}\right\rceil$ 个人。

要求快乐值的和的最大值，那么考虑对 $\{a_n\}$ 进行排序，从最大值开始遍历，求 $a_i$ 的和。若遍历到 $a_i<0$，则后面的所有元素都小于 $0$，没必要再计算，退出循环。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 2e5 + 9;

int n, a[N], ans;

signed main() {

    cin >> n;
    for (int i = 1; i <= n; ++i) {
    	cin >> a[i];
    }
    sort(a + 1, a + n + 1);
    int p = ceil(n * 1.0 / 2);
    for (int i = n, j = 1; j <= p; --i, ++j) {
    	if (a[i] < 0) break;
    	ans += a[i];
    }
    cout << ans;
	
    return 0;
}
```

---

## 作者：LostKeyToReach (赞：0)

一道贪心题。

根据题目的描述，说明两个人不能坐在相邻的座位上，那么我们最多只能选择 $\lceil \frac{n}{2} \rceil$ 个人参加宴会。

那么我们按照 $a_i$ 从大到小排序，在 $1 \sim \lceil \frac{n}{2} \rceil$ 中选择，当 $a_i < 0$ 时立刻退出。

时间复杂度为 $O(n \log n)$。

参考代码如下：

```cpp
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#define ll long long
#define writes(x) write(x), putchar(' ')
#define writeln(x) write(x), putchar('\n');
static char buf[100000], * pa(buf), * pb(buf);
#define gc pa == pb && (pb = (pa = buf) + fread(buf, 1, 100000, stdin), pa == pb) ? EOF : *pa++
using namespace std;
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
template <typename T> void read(T& x) {
    T t = 0, sgn = 1;
    char ch = gc;
    while (!isdigit(ch)) {
        if (ch == '-') sgn = -sgn;
        ch = gc;
    }
    while (isdigit(ch)) {
        t = (t << 3) + (t << 1) + (ch ^ 48);
        ch = gc;
    }
    x = sgn * t;
}
template <typename T, typename ...Args> void read(T& tmp, Args &...tmps) {
    read(tmp); read(tmps...);
}
template <typename T> void write(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
template <typename T, typename ...Args> void write(T& tmp, Args &...tmps) {
    writes(tmp);
    writes(tmps...);
}
template <typename T> T rand(T l, T r) {
    return rnd() % (r - l + 1) + l;
}
ll n, a[200005];
int main() {
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    sort(a + 1, a + n + 1, greater<>());
    int rg = ceil(n / 2.0);
    ll ans = 0;
    for (int i = 1; i <= rg; i++) {
        if (a[i] < 0) break;
        ans += a[i];
    }
    write(ans);
}
```

---

## 作者：Bc2_ChickenDreamer (赞：0)

## P10709

### Sol

首先我们分析有几个朋友可以入座，$n$ 个座位，要隔出两个座位，那就是 $\Big\lceil \cfrac{n}{2} \Big\rceil$ 个朋友可以入座（$\lceil\rceil$ 表示上取整）。

很显然的，我们选取快乐值最大的 $\Big\lceil \cfrac{n}{2} \Big\rceil$ 个朋友即可。

但注意，**不能**邀请快乐值 $< 0$ 的朋友。

时间复杂度 $O(n \log n)$。

### Code

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
 
using namespace std;
 
using ll = long long;
 
const int kMaxN = 2e5 + 50, kInf = (((1 << 30) - 1) << 1) + 1, kMod = 998244353;
const ll kLInf = 9.22e18;

ll n, a[kMaxN], ans = 0;

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++ i) {
    cin >> a[i];
  }
  ll sit = n / 2 + n % 2;
  sort(a + 1, a + n + 1);
  for (int i = n; i >= n - sit + 1 && a[i] >= 0; -- i) {
    ans += a[i];
  }
  cout << ans << '\n';
  return 0;
}
```

---

## 作者：cqbzrjx (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10709)

# 思路

一眼**模拟**~~~~~~

**贪心**地想，想要获得最大值，那就可以先 `sort` 排序一遍。既然相邻两个座位不能坐，所以只能邀请 $\left \lceil \frac{n}{2} \right \rceil$ 个朋友。于是想到用**后缀和**，维护**最大值**，再进行取**最大值**。

# AC code
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;//不开longlong见祖宗
const int maxn = 2e5 + 10;
ll n,m,cnt;//m为可以邀请的最多朋友个数，cnt求最大快乐值
ll a[maxn],sum[maxn];//sum求后缀和
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>n;//输入
	for(int i = 1;i <= n;i++)
	{
		cin>>a[i];
	}
	sort(a + 1,a + 1 + n);//排序
	m = (n + 1) / 2;//向上取整求个数
	for(int i = n;i >= n - m + 1;i--)
	{
		sum[i] = sum[i + 1] + a[i];//计算后缀和
		cnt = max(cnt,sum[i]);//取最大值
	}
	cout<<cnt;//输出
	return 0;//完结，撒花
}
```

---

## 作者：D0000 (赞：0)

根据题意，要选择不超过 $\lfloor \frac{n+1}{2}\rfloor$ 个数，使它们的和最大。

那么发现，应当选最大的 $\lfloor \frac{n+1}{2}\rfloor$ 个数，但如果出现了负数，应当把它们踢掉。

选最大的 $\lfloor \frac{n+1}{2}\rfloor$ 个数可用排序实现，时间复杂度 $O(n\log n)$。

代码：
```cpp
#include<cstdio>
#include<algorithm>
int n,a[200005];
long long ans=0;
bool cmp(int x,int y){
	return x>y;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	std::sort(a+1,a+n+1,cmp);
	for(int i=1;i<=(n+1)/2&&a[i]>0;i++)ans+=a[i];
	printf("%lld",ans);
}
```

---

## 作者：fengyuxuan (赞：0)

# 题目大意

在 $n$ 个数中选择最多 $\lfloor \frac{n+1}{2} \rfloor $ 个数（可以选 $0$ 个）问这些数和最大能是多少。

# 题目解析

思路：贪心！！

将 $a_i$ 从大到小排序排序，选则前 $\lfloor \frac{n+1}{2} \rfloor $ 个数中，大于 $0$ 的数相加即可。

# 最终代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,ans,s,a[200005];
bool cmp(int x,int y){return x>y;}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+1+n,cmp);//排序
	s=(n+1)/2;
	for(int i=1;i<=s;i++)
		if(a[i]>0)//大于0的累加
			ans+=a[i];
	cout<<ans;
	return 0;
}
```

---

## 作者：qiuqiuqzm (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10709)

# 分析
这道题就是贪心，先排序，然后从最大的一个一个往下看。如果已经小于 $0$，那就不用继续看了，因为小于 $0$ 会让快乐值减小，而后面的会更小。如果人数已经大于 $\left \lceil n/2 \right \rceil $ 那就结束循环。最后输出即可。

# Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[200005];
long long ans=0;
int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+1+n);
	for(int i=n;i>=n-((n+1)/2)+1;i--)
	{
		if(a[i]>0)
			ans+=a[i];
		else
			break;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：zhoujunchen (赞：0)

做题思路
---
一道贪心题。

- 将快乐值排序。

- 由于两个人不能坐在相邻的座位上，所以我们选取前 
$\lceil \frac{n}{2}\rceil$ 个人。但是如果快乐值为负需要跳出循环。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[200005],cnt,ans;
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+n+1);
    cnt=n/2;
    for(int i=n;i>cnt;i--){
        if(a[i]>=0)ans+=a[i];
        else break;
    }
    cout<<ans;
    return 0;
}
```
十年OI一场空，不开 long long 见祖宗。

---

## 作者：donnieguo (赞：0)

## 题意简述

有 $n$ 个数，现在你可以从中选出 $\lceil\dfrac{n}{2}\rceil$ 个数，求最大的和。

## 思路

先求出人数 $p = \lceil\dfrac{n}{2}\rceil$，然后对数组进行从大到小排序，遍历数组的前 $p$ 个 $a_i$，将每个 $a_i$ 加总就可以了。

坑点：

- 如果前 $p$ 个数中有负数，则可以立即退出循环。

- 十年 OI 一场空，不开 `long long` 见祖宗。

code：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
int a[200010];
ll sum;
bool cmp(int a, int b)
{
	return a > b;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + n + 1, cmp);
	int p = n / 2;
	if (p * 2 != n) p++;
	for (int i = 1; i <= p; i++){
		if (a[i] < 0) break;
		sum += a[i];		
	}
	cout << sum << '\n';
	return 0;
}

```

---

## 作者：nightwatch.ryan (赞：0)

### 思路
首先将 $n$ 个数进行降序排序，选取前 $\lfloor \dfrac{n+1}{2} \rfloor$ 个快乐值大于 $0$ 的数，如果没有那么多，则有多少个快乐值大于 $0$ 的数就选多少个。累加起来，最后输出答案。
### 代码
```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
#define int long long
#define N 200005 
int n,a[N],ans;
signed main(){
	std::cin>>n;
	for(int i=1;i<=n;i++)
		std::cin>>a[i];
	int ok=(n+1)/2;
	std::sort(a+1,a+1+n,std::greater<int>());
	for(int i=1;i<=n&&ok;i++){
		if(a[i]<=0)break;
		ans+=a[i],ok--;
	}
	std::cout<<ans; 
}
```

---

## 作者：hexuchen (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10709)

[更好的阅读体验？](https://www.luogu.com.cn/article/v2dxelvx)

## 题目大意

James 想请了 $n$ 个人参加派对，每个人都有一个快乐值 $a
_i$。但 James 家只有 $n$ 个座位，并且朋友与朋友之间必须间隔一个座位，求快乐值最大多少。

## 思路分析

一道有点小坑的水题。

思路很好想：首先，由于人与人之间要有间隔，所以实际上只有 $\lceil n \div 2 \rceil $ 个人能来。既然要快乐值最大，那肯定要请快乐值最高的人来。先将人们按快乐值从大到小排序，取前 $\lceil n \div 2 \rceil $ 个人的快乐值，求和即可。

初步代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,s[200001],ans=0;
bool cmp(int a,int b){
	return a>b;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s[i];
	}
	sort(s+1,s+1+n,cmp);
	n=(n%2==0?n/2:n/2+1);
	for(int i=1;i<=n;i++){
		ans+=s[i];
	}
	cout<<ans;
	return 0;
}
```

[然而只有样例对，剩下的测试点几乎全 WA](https://www.luogu.com.cn/record/164515097)

为什么呢？仔细读题，发现 James 是可以请 $0$ 个人来参加聚会的！如果算出来的答案小于 $0$，那还不如不请，输出 $0$。

升级版代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,s[200001],ans=0;
bool cmp(int a,int b){
	return a>b;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s[i];
	}
	sort(s+1,s+1+n,cmp);
	n=(n%2==0?n/2:n/2+1);
	for(int i=1;i<=n;i++){
		ans+=s[i];
	}
	cout<<(ans<0?0:ans);
	return 0;
}
```

[这次对的更多了，但还是没有 AC](https://www.luogu.com.cn/record/164515354)

为什么还是没有 AC 呢？作者思考了很久，最后举出了一个 hack 数据：

>5
>
>1 -1 -2 -3 -4

按照我的方法，排序后请的人是

>1 -1 -2

所以快乐值是 $-2$。$-2$ 小于 $0$，所以代码输出了 $0$。事实上，请的人中有两个人的快乐值都是负数，为什么要请他们来啊？我们可以只请一个人，他的快乐值是 $1$，所以最后答案是 $1$。

根据这个 hack 数据，我们应该在最后求和的时候判断，如果请的人的快乐值是负数，就不请他。

## AC 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,s[200001],ans=0;
bool cmp(int a,int b){
	return a>b;
}
int read(){  //增加了快读
	int sum=0,fh=1;
	char c=getchar();
	while(c<'0' || c>'9'){
		if(c=='-')
			fh=-1;
		c=getchar();
	}
	while(c>='0' && c<='9'){
		sum=sum*10+c-'0';
		c=getchar();
	}
	return sum*fh;
}
void write(int a){ //快写
	if(a>=10)
    	write(a/10);
    putchar(a%10+'0');
}
signed main(){
	n=read(); //输入
	for(int i=1;i<=n;i++){
		s[i]=read();
	}
	sort(s+1,s+1+n,cmp); //排序
	n=(n%2==0?n/2:n/2+1); //注意人与人之间要有间隔
	for(int i=1;i<=n;i++){
        if(s[i]<0) //快乐值是负数，由于后面的人快乐值更低，所以直接结束循环
            break;
		ans+=s[i];
		//cout<<s[i]<<' ';
	}
	write(ans); //输出
	return 0;
}
//101010101
```

---

## 作者：yfl20130101 (赞：0)

### 思路
我们为了让每个人都不相邻，最多只能让 $n-(\lfloor n\div2\rfloor+1)+1$ 人来，那这些人最好兴趣值最大，故按兴趣值从大到小的顺序让这些人来。但如果这些人里面有兴趣值是负数的，那么我们就可以不再看了，因为后面肯定都是负数，就会使总兴趣值减少，我们就都不让他们来。详见代码。
### 代码
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int a[200005];
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	long long sum=0;
	for(int i=n;i>=n/2+1;i--){
		if(a[i]<0){
			break;
		}
		sum+=a[i];
	}
	cout<<sum;
	return 0;
}
```

---

## 作者：jiangyunuo (赞：0)

## 题目大意：
主人邀请他的朋友一起当派对客，每个人会有 $a_i$ 点快乐值，主人准备了 $n$ 个座位，任何两个人不能坐在相邻的座位上，主人要想要让快乐值总和最大，同时，邀请的人不能超过能坐的座位（指没有和任何座位相邻的座位），当 $n$ 为奇数时，那么最多有 $n \div 2 + 1$ 个能坐的座位，当 $n$ 为偶数时，那么最多有 $n \div 2$ 个能坐的座位。
## 主要思路：
我们肯定是不要请快乐值在 $0$ 以下的人，我们要请的是快乐值在 $0$ 以上的人，我们可以统计快乐值在 $0$ 以上的人，然后通过 `sort` 排序，来排好它们的大小，接着从后往前加快乐值，这样就能得出最大的快乐值。
## 代码：
#### 零分代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,x=0,ans=0;
	cin>>n;
	int a[n+1];
	for(int i=1;i<=n;i++){
		x++;
		cin>>a[x];
		if(a[x]<=0)x--;
	}
	sort(a+1,a+1+x);
	if(n%2==0)n/=2;
	else n=n/2+1;
	for(int i=1;i<=n;i++){
		ans+=a[x];
		x--;
	}
	cout<<ans;
return 0;
}
```
[WA 记录](https://www.luogu.com.cn/record/164490751)  
这份代码看起来能过样例，但有一个致命错误，在后面用于累加快乐值循环中，$x$ 一直在减少，最后可能会到达 $1$ 一下，接下来，数组就会出问题，累加的答案就会出错。
#### 四十九分代码：
为啥不是四十八分！
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,x=0,ans=0;
	cin>>n;
	int a[n+1];
	for(int i=1;i<=n;i++){
		x++;
		cin>>a[x];
		if(a[x]<=0)x--;
	}
	sort(a+1,a+1+x);
	if(n%2==0)n/=2;
	else n=n/2+1;
	for(int i=1;i<=n;i++){
		if(x==0)break;
		ans+=a[x];
		x--;
	}
	cout<<ans;
return 0;
}
```
[WA 记录](https://www.luogu.com.cn/record/164490843)  
这次多了一个判定 $x$ 是否等于 $0$ 的 `if` 语句，可以防止 $x$ 小于 $1$，导致后面出错，但为什么又错了呢？因为，`int` 太小了，乍一看，数据没有超过 `int` 范围，但多个 $a_i$ 加在一起就会超出 `int`，因此 $ans$ 要用 `long long`。
#### 一百分代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,x=0;
    long long ans=0;   //x 表示数组 a 的数量。
	cin>>n;
	int a[n+1];
	for(int i=1;i<=n;i++){
		x++;
		cin>>a[x];
		if(a[x]<=0)x--;   //判定输入的是否为负数，如果是那就要让 x 回到上一个数，也就是说重新数入这个数组。
	}
	sort(a+1,a+1+x);   //给数组 a 从小到大排序。
	if(n%2==0)n/=2;    //求出能坐的座位的最大数量。
	else n=n/2+1;
	for(int i=1;i<=n;i++){
		if(x==0)break;    //判定还有没有剩下的朋友。
		ans+=a[x];        //从后往前累加快乐值。
		x--;
	}
	cout<<ans;
return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/164490976)

---

## 作者：Mortidesperatslav (赞：0)

贪心。

首先，$n$ 个座位，因为社交距离，我们计算得到可以坐 $\lceil \dfrac{n}{2} \rceil$ 个人。

然后把 $a_i$ 从大到小排，选择最大的 $\lceil \dfrac{n}{2} \rceil$ 个人。你放心的交了上去……？你突然想到，负数是不优的，还不如不请。

于是你加了个特判上去，结果自然是 AC。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, a[300005];
int ans;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	sort(a + 1, a + 1 + n, [](int a, int b){return a > b;});
	for (int i = 1; i <= ((n + 1) >> 1); i++)
		if (a[i] >= 0)
			ans += a[i];
	cout << ans;
}
```

---

## 作者：ToastBread (赞：0)

## 思路
考虑贪心。

首先需要明确一点，**$a_i$ 为负的人，不能被邀请**。因为如果不被邀请的话，会向总和加上 $0$，显然比加上负数更优。

再然后需要弄清楚“社交距离”。社交距离实际上告诉了我们，这个聚会可以邀请至多 $\lceil \frac{n}{2}\rceil$ 个人。

然后思路就很直白了，按快乐值从大到小排序，选取前 $\lceil \frac{n}{2}\rceil$ 个人（前提是 $a_i \geq 0$）邀请到聚会，算出总和就可以了。

**注意，本题数据范围可能会超过 `int` 能表示的范围，记得开 `long long`。**

具体实现见代码注释。
## AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,a[200005],sit,ans;//ans 总和 
bool cmp(int x,int y)//从大到小排序 
{
	return x>y;
}
int main()
{
	cin>>n;
	sit=(n+1)/2;//最多能邀请的人数 
	for(int i = 1; i <= n; i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+n+1,cmp);//排序，注意从大到小 
	for(int i = 1; i <= sit; i++)
	{
		if(a[i]>0) ans+=a[i];//可以就选取 
	}
	cout<<ans;
	return 0;
}


```

---

## 作者：Drifty (赞：0)

### Solution

建议降红。

直接贪心，我们把 $a$ 从大到小排序，由于最多只能请 $\left \lfloor \frac{n+1}{2} \right \rfloor $ 个人，因此我们考虑前 $\left \lfloor \frac{n+1}{2} \right \rfloor $ 个人。从头开始计入答案，如果 $a_i$ 为负数，则必定会令快乐值减小，因此直接退出计算。如此模拟即可。

### AC-Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	int n; cin >> n;
    vector <int> a(n);
    for (int i=0; i<n; i++) cin >> a[i];
    sort (a.begin(), a.end(), greater<int>());
    long long ans = 0;
    for (int i=0; i < (n + 1 >> 1); i++) if (a[i] > 0) ans += a[i];
	return cout << ans, 0;
}
```

---

## 作者：jsisonx (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10709)

# 题目分析
首先明确一点，$n$ 个座位，不能坐在相邻的地方，最多一共有 $\lceil \frac{n}{2} \rceil$ 个座。

现在来化简一下题意：有 $n$ 个数，从中选出 $\lceil \frac{n}{2} \rceil$ 个数使得选出的和最大。

因为只要是正数就一定对答案有贡献，所以可以先将 $n$ 个数从大到小排序，然后从第一个数开始枚举 $\lceil \frac{n}{2} \rceil$ 个，如果该数为正就加到答案上，否则就退出，因为后面一定都是非正数。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int cmp(int a,int b){
	return a>b;
}
long long a[500001],ans=0;
int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	sort(a,a+n,cmp);
	int k=ceil((double)n/2);
	for(int i=0;i<k;i++){
		if(a[i]>0){
			ans+=a[i];
		}
		else{
		    break;
		}
	}
	cout<<ans;
	return 0;
} 

```

---

