# Quests

## 题目描述

There are $ n $ quests. If you complete the $ i $ -th quest, you will gain $ a_i $ coins. You can only complete at most one quest per day. However, once you complete a quest, you cannot do the same quest again for $ k $ days. (For example, if $ k=2 $ and you do quest $ 1 $ on day $ 1 $ , then you cannot do it on day $ 2 $ or $ 3 $ , but you can do it again on day $ 4 $ .)

You are given two integers $ c $ and $ d $ . Find the maximum value of $ k $ such that you can gain at least $ c $ coins over $ d $ days. If no such $ k $ exists, output Impossible. If $ k $ can be arbitrarily large, output Infinity.

## 说明/提示

In the first test case, one way to earn $ 5 $ coins over $ 4 $ days with $ k=2 $ is as follows:

- Day 1: do quest 2, and earn $ 2 $ coins.
- Day 2: do quest 1, and earn $ 1 $ coin.
- Day 3: do nothing.
- Day 4: do quest 2, and earn $ 2 $ coins.

 In total, we earned $ 2+1+2=5 $ coins.In the second test case, we can make over $ 20 $ coins on the first day itself by doing the first quest to earn $ 100 $ coins, so the value of $ k $ can be arbitrarily large, since we never need to do another quest.

In the third test case, no matter what we do, we can't earn $ 100 $ coins over $ 3 $ days.

## 样例 #1

### 输入

```
6
2 5 4
1 2
2 20 10
100 10
3 100 3
7 2 6
4 20 3
4 5 6 7
4 100000000000 2022
8217734 927368 26389746 627896974
2 20 4
5 1```

### 输出

```
2
Infinity
Impossible
1
12
0```

# 题解

## 作者：cjh20090318 (赞：11)

大家好，我是 CQ-C2024 蒟蒻 CJH。

（最近一次更新：2022/12/20 21:16，发现 $k$ 无解的情况笔误，已修改，感谢 @[budaiyanjing](https://www.luogu.com.cn/user/625488) 的提醒）

## 题意

有 $n$ 个任务，完成第 $i$ 个任务可以获得 $a_i$ 个金币，完成一个任务在未来 $k$ 天内不能再次完成。你要在 $d$ 天内获得 $c$ 个金币，求**最大**的 $k$。

## 分析思路

貌似看各位大佬都是用的二分，我这里补一篇贪心排序的题解。

首先将 $a$ 数组从大到小排序，$k$ 此时有三种情况：

### 一、$k$ 无解

考虑最坏的情况，如果 $k=0$ 时，在 $d$ 天都做利润最高的那个任务，如果仍不能达到 $c$ 个，即 $d \times a_1 < c$，则判定为无解。

### 二、$k$ 为无穷大

在这 $d$ 天内，将所有的任务只做一遍即可达到 $c$ 个，即 $\sum\limits_{i=1}^{\min\{d,n\}}a_i \ge c$，则 $k$ 为无穷大。

### 三、$k$ 有解

这里在 $d-1 \sim 0$ 中枚举 $k$，我们将每 $k+1$ 视为一个循环，且每个循环中做最大利润的任务，余下的天数就做利润从大到小的任务。

## 注意事项

$c\le 10^{16}$，需要用 `long long` 存储，~~不开 `long long` 见祖宗~~。

## 代码

```cpp
//the code is from chenjh
#include<bits/stdc++.h>
#define MAXN 200002
using namespace std;
typedef long long LL;
int a[MAXN];
LL b[MAXN];
void solve(){
	int n,d;LL c;
	scanf("%d%lld%d",&n,&c,&d);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	sort(a+1,a+n+1,greater<int>());//从大到小排序。
	if((LL)a[1]*d<c){puts("Impossible");return;}//判断无解。
	for(int i=1;i<=n;i++) b[i]=b[i-1]+a[i];//前缀和数组，表示前 i 个任务的利润。
	if(b[min(n,d)]>=c){puts("Infinity");return;}//判断是否无穷大。
	int k;
	for(k=d-1;k>=0;k--){//枚举 k。
		int x=d%(k+1);//判断余下的天数。
		if(b[min(n,x)]+d/(k+1)*b[min(n,k+1)]>=c){//一定要取最小值，要不然就会访问到 n 个任务以外！
			printf("%d\n",k);
			return;
		}
	}
	puts("Impossible");
}
int main(){
	int t;scanf("%d",&t);
	while(t--) solve();
	return 0;
}

```

---

## 作者：liujy_ (赞：7)

 ###  题目大意  
 给定 $n$ 给数，你每天可以最多选一个，选过的数在未来 $k$ 天内不得再选。你有 $d$ 天的时间，需要求最大的一个 $k$ 可以使得能选出来的价值大于等于 $c$。  
 

 ------------  
 首先我们来想一下，题目要求选的数大于一个数，我们选数的策略肯定要使得选出的数尽可能的大，所以我们每次肯定是贪心的选当前可以选的最大的数。所以如果每天都可以选序列中的最大值，也就是 $k=0$ 的情况，都不能使得最后答案大于 $c$ 的话，即为无解。同样，如果 $k \geq d$ 的情况下依然有方案使得选出来的数满足条件，$k$ 就可以是无穷大。  
 考虑其他情况，我们要使得 $k$ 尽可能的大。我们发现随着 $k$ 的增大，可以取到的最大的数一定是单调不增的。所以可以直接二分，上界是 $d$ 下界为 $0$。因为我们每次都选当前能选的最大值，所以选择可以分为一组一组来看，每 $k+1$ 天即为一组，我们把数组 $a$ 从大到小排序，做前缀和，每一组的价值就是 $s_{k+1}$（如果 $k \geq n$ 则每组价值为 $s_n$）。因为 $d$ 不一定被 $k+1$ 整除，所以最后一组的天数为 $d \bmod k+1$。
 代码如下。
 ```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#define int long long
using namespace std;
int t,n,c,d,s[200005];
bool cmp(int a,int b){return a>b;}
bool check(int k){
	int sum=s[min(n,k+1)]*(d/(k+1));
	sum+=s[min(n,d%(k+1))];
	return sum>=c;
}
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld%lld%lld",&n,&c,&d);
		for(int i=1;i<=n;i++)scanf("%lld",&s[i]);
		sort(s+1,s+n+1,cmp);
		for(int i=1;i<=n;i++)s[i]+=s[i-1];
		if(s[min(n,d)]>=c)printf("Infinity\n");
		else if(s[1]*d<c)printf("Impossible\n");
		else {
			int l=0,r=d,ans=0;
			while(l<=r){
				int mid=(l+r)>>1;
				if(check(mid))ans=mid,l=mid+1;
				else r=mid-1;
			}
			printf("%lld\n",ans);
		}
	}
	return 0;
}
```


---

## 作者：LZYAC (赞：1)

# 思路
+ Impossible

考虑极限情况：在随便完成任务的情况下都不行，那么肯定不行。
+ Infinity

只要最大值要的钱还多那就可以。（因为 $k$ 无论是多少，挨着完成任务就可以了）
+ normal

此题按常规思路难做，不如转换为判定性问题：

当前 $k$ 能否让我得到 $c$ 元？

于是发现从大到小排序后周期循环（**贪心**）。

最后二分即可。
# 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,c,d,a[200010],l,r,mid,sum,temp,ans;
bool cmp(int t1,int t2){return t1>t2;}
bool check(int k){
	temp=a[min(n,k+1)]*(d/(k+1))+a[min(n,d%(k+1))];
	return temp>=c;
}
signed main(){
	scanf("%lld",&t);
	for(int tt=1;tt<=t;tt++){
		sum=0;
		scanf("%lld%lld%lld",&n,&c,&d);
		for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
		sort(a+1,a+1+n,cmp);
		for(int i=1;i<=n;i++)a[i]+=a[i-1];
		
		l=0,r=d;
		if(a[min(n,d)]>=c){
			printf("Infinity\n");
			continue;
		}
		if(a[1]*d<c){
			printf("Impossible\n");
			continue;
		}
		while(l<r){
			mid=(l+r+1)/2;
			if(check(mid)){
				l=mid;
			}
			else r=mid-1;
		}
		printf("%lld\n",l);
	}
	return 0;
}
```

---

## 作者：Merge_all (赞：1)

## 思路
- Impossible 的情况

判断最大值和 $d$ 的**乘积**是否小于 $c$，小于了的话就是无解。
- Infinity 的情况

只要所有值的总和比 $c$ 还大就可以。
- normal

二分答案判断当前的答案是否可行，**从大到小排序**即可（**贪心**）。
## 代码
```
#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

#define int long long

const int N=202000;

int T;
int n,c,d;
int a[N],sum,mid,t;

void search(int L,int R){
	while(L<R){
		mid=(L+R+1)/2;
		sum=0;
		for(int i=1;i<=d;i++){
			int k=((i-1)%(mid+1)+1);
			if(k<=n) sum+=a[k];
		}
		if(sum>=c) L=mid;
		else R=mid-1;
	}
	printf("%lld\n",L);
}

signed main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld%lld",&n,&c,&d);
		for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
		sort(a+1,a+n+1,greater<int>());
		sum=0,t=min(n,d);
		for(int i=1;i<=t;i++) sum+=a[i];
		if(sum>=c){
			puts("Infinity");
			continue;
		}
		if(a[1]*d<c){
			puts("Impossible");
			continue;
		}
		search(0,2e9);
	}
	return 0;
}
```

---

## 作者：sto__Liyhzh__orz (赞：1)

注：我的教练把这道题放在了二分里面，但我用贪心做

### 题目大意

若完成了第 $i$ 个任务，你将获得 $a_i$ 元。

但如果今天完成了一个任务，那么之后 $k$ 天内都不能再完成这个任务。

输出：（$k$ 有解，取最大）/`Impossible`的情况（无解）/`Infinity`的情况（$k$ 为无穷大）。


------------

### `Impossible` 的情况

考虑最坏情况：$k = 0$，每天都做利润最高的任务，但总和仍达不到 $c$，无解。

输出`Impossible`。

------------

### `Infinity` 的情况
这 $d$ 天内，将所有的任务做一遍即可达到 $c$ 个，$ \sum _ {i = 1} ^ {\min (n,d)} a_i \ge c$，则 $k$ 无穷大。

输出`Infinity`。

------------

### $k$ 有解

我们在 $d-1 \sim 0$ 中循环枚举 $k$，将每 $k+1$ 看做一个循环，并且每个循环中我们都做最大利润的任务，余下的天数就做利润从大到小的任务。

输出 $k \max$。

------------

### 核心代码

```cpp
if(1ll*a[1]*d<c)//Impossible 的情况
{
    printf("Impossible\n");
    return ;
}
for(int i=1;i<=n;i++) b[i]=b[i-1]+a[i];
if(b[min(n,d)]>=c)//Infinity 的情况
{
    printf("Infinity\n");
    return ;
}
//输出k的max
for(int k=d-1;k>=0;k--)
{
    int x=d%(k+1);
    if(b[min(n,x)]+d/(k+1)*b[min(n,k+1)]>=c)
    {
        printf("%d\n",k);
        return ;
    }
}
```


------------

---

## 作者：Fubaogege (赞：0)

#### 题意简述
有很多个任务，要你在 $d$ 天之内获得 $c$ 个金币，且一个任务完成之后有 $k$ 天不能完成它，求最大的 $k$。
#### 思路
这道题我们要求的是 $k$ 的最大值，我们可以用贪心完成它。  

前期准备：将 $a_i$ 从大到小排序。

- 当 $k$ 有解，循环让他的利润最大。
- 当 $k$ 无解：每次做最高利润还达不到，则无解。
- 无穷大的 $k$：做一次就满足，则他为无穷大。

这样我们就把 $k$ 给求出来了。
#### 程序实现
根据思路分别对应 $3$ 段核心程序：

- $k$ 无解：

`if((xx)a[1]*d<c)puts("Impossible");`

- $k$ 无穷大：

`if(x[min(n,d)]>=c)puts("Infinity");`

- 否则他就是有解：

```c
	for(k=d-1;k>=0;k--){
		int t=d%(k+1);
		if(x[min(n,t)]+d/(k+1)*x[min(n,k+1)]>=c){printf("%d\n",k);return;}
	}
```

---

## 作者：SkyLines (赞：0)

## 思路：

如果 $k$ 可以无限大，那么 $d$ 天把所有工作做一遍会获得 $\geq c$ 元。

如果不存在这样的 $k$，那么 $d$ 天都做能获得最大的钱的工作，所获得的钱 $< c$ 元。

很明显是个二分。可以对答案 $k$ 二分。做工作是一个循环，每个循环有 $k+1$ 天，为了让 $k$ 最大，即获得的钱最大，就要先将 $a$ 数组从大到小排序。可以先用一个数组求出 $a$ 数组的前缀和，用一个循环所获得的钱乘循环数加上剩余的钱就是能获得的钱，能获得的钱 $\geq c$ 的话，更新 $l$，否则更新 $r$。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t, n, c, d, a[200005], minn, l, r, mid, ans, S[200005];
bool cmp(int xx, int yy){
	return xx > yy;
}
bool check(int aa){
	return S[min(n, aa + 1)] * (d / (aa + 1)) + S[min(n, d % (aa + 1))] >= c;
}
signed main(){
	scanf("%lld", &t);
	for(int k = 1; k <= t; k++){
		ans = -1;
		scanf("%lld %lld %lld", &n, &c, &d);
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		sort(a + 1, a + n + 1, cmp);
		if(d * a[1] < c){
			printf("Impossible\n");
			continue;
		}
		minn = min(n, d);
		for(int i = 1; i <= n; i++) S[i] = S[i - 1] + a[i];
		if(S[minn] >= c){
			printf("Infinity\n");
			continue;
		}
		l = 0;
		r = d;
		while(l <= r){
			mid = (l + r) >> 1;
			if(check(mid)){
				if(mid > ans) ans = mid;
				l = mid + 1;
			}
			else r = mid - 1;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：ZBH_123 (赞：0)

## 题目分析
对于本题，我们可以对 $k$ 进行二分答案。通过观察不难发现，本题中做工作是一个周期性的问题，周期为 $k+1$ 天。为了让获得的钱尽可能的多，每一个周期都需要做 $a_i$ 尽可能大的工作，这样，我们就需要先对 $a$ 按照从大到小的顺序排序，然后处理出它的前缀和。在二分答案时，求出做完整的周期可以获得多少钱，再加上剩下的能获得的钱，与 $c$ 进行比较，从而对二分答案的区间进行调整。

判断是否输出 `Infinity`，就需要看是不是将所有工作做一遍就可以得到 $c$ 元。判断是否输出 `Impossible`，就需要看是不是 $d$ 天都做 $a_i$ 最大的工作都到不了 $c$ 元。

**AC code：**
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=2e5;
int t,n,d;
long long a[maxn+5],sum[maxn+5],c;
bool check(int x){
	int len=x+1;
	long long money=d/len*sum[min(n,len)]+sum[min(d%len,n)];
	return money>=c;
}
int main(){
	int l,r,ans;
	scanf("%d",&t);
	while(t--){
		scanf("%d %lld %d",&n,&c,&d);
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i]);
		}
		sort(a+1,a+n+1,greater<int>());
		for(int i=1;i<=n;i++){
			sum[i]=sum[i-1]+a[i];
		}
		if(sum[min(d,n)]>=c){
			puts("Infinity");
			continue;
		}
		if(d*a[1]<c){
			puts("Impossible");
			continue;
		}
		l=0,r=d;
		while(l<=r){
			int mid=(l+r)/2;
			if(check(mid)){
				ans=mid,l=mid+1;
			}
			else{
				r=mid-1;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：Phartial (赞：0)

为什么一车人用的二分/jy

手玩一下不难得到最优方案一定是重复取前 $k+1$ 大的数，推一下柿子得到对应答案为 $s_{k+1}\lfloor\dfrac{d}{k+1}\rfloor+s_{d\mod (k+1)}$，其中 $s_i$ 为 $a_i$ 的前缀和。

把 $a_i$ 排序后枚举 $k$ 即可，时间复杂度 $O(n)$。

细节：

`Impossible` 的情况：$k=0$ 时结果还小于 $c$。

`Infinity` 的情况：$k=\max(n,d)$（即重复取了 $n$ 个数后剩下的只能用 $0$ 填）时结果还不小于 $c$。

```cpp
#include <algorithm>
#include <iostream>

using namespace std;
using LL = long long;

const int kN = 2e5 + 2;

int t, n, d;
LL c, a[kN], s[kN];

LL C(int k) {
  return s[k + 1] * (d / (k + 1)) + s[d % (k + 1)];
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  for (cin >> t; t--; ) {
    cin >> n >> c >> d;
    fill_n(a + 1, max(n, d), 0);
    for (int i = 1; i <= n; ++i) {
      cin >> a[i];
    }
    sort(a + 1, a + n + 1, greater<int>());
    for (int i = 1; i <= max(n, d); ++i) {
      s[i] = s[i - 1] + a[i];
    }
    if (C(0) < c) {
      cout << "Impossible\n";
      continue;
    }
    if (C(max(n, d)) >= c) {
      cout << "Infinity\n";
      continue;
    }
    int k = max(n, d);
    for (; C(k) < c; --k) {
    }
    cout << k << '\n';
  }
  return 0;
}
```

---

## 作者：litachloveyou (赞：0)

分析题目，发现 $k$ 有三种情况。

第一种，在天数足够的情况下，每一个物品都买一次即可满足要求，那么 $k$ 无论有多大都可以。

第二种，每一个物品买一次无法满足要求，那就至少有一个物品需要买两次的情况，这时候 $k$ 具有单调性。

第三种，每一天都买价值最大的都无法满足题目要求，此时 $k$ 无解。

于是排完序之后可以使用二分答案，每一次判断购买时，尽量购买价值最大的物品。

时间复杂度 $O(nlogn)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 2e5 + 10;
constexpr ll maxn = 1e18 + 10;
ll a[N];
ll n, c, d;
bool check(ll mid)
{
	ll f = d;
	ll sum = 0;
	if (!mid)
	{
		return f * a[n] >= c;
	}
	ll days = 0, now = n;
	while (f)
	{
		if (now > 0)sum += a[now];
		now--;
		if (days == mid)
		{
			now = n;
			days = 0;
			f--;
			continue;
		}
		days++;
		f--;
	}
	return sum >= c;
}
void solve()
{
	scanf("%lld%lld%lld", &n, &c, &d);
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld", &a[i]);
	}
	sort(a + 1, a + n + 1);
	ll l = 0, r = 1e18 + 10;;
	ll mid, ans = -1;
	while (l <= r)
	{
		mid = l + r >> 1;
		if (check(mid))
		{
			ans = mid;
			l = mid + 1;
		}
		else
		{
			r = mid - 1;
		}
	}
	if (ans == -1)
	{
		puts("Impossible");
	}
	else if (ans == maxn)
	{
		puts("Infinity");
	}
	else
	{
		printf("%lld\n", ans);
	}
}
int main()
{
	int T = 1;
	scanf("%d", &T);
	while (T--)solve();
	return 0;
}
```


---

## 作者：_Remake_ (赞：0)

## 题目分析
给定一些任务，完成每一个任务都能获得一定的金钱，每个任务获得的金钱固定，但每个任务之间需要有一些冷却才能再次完成，求使你能够在指定时间内至少获得指定金钱数量的最大的冷却时间。

先对任务按照金钱数量排序，获得金钱多的任务排在前面，可以把指定的时间划分为多个周期，设 $N$ 为任务总数，$cd$ 为冷却时间，每个周期只会完成排名前 $\min(N,cd)$ 的任务，之后可以求出每个周期的金钱数，再计算不满一个周期的钱数，就可以获得当前冷却时间下可以获得的钱数。之后可以二分求出最大的冷却时间。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read()
{
    int n=0,k=1;
    char ch=getchar();
    while(ch>'9'||ch<'0')
    {
        if(ch=='-')
        {
            k=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        n=n*10+ch-'0';
        ch=getchar();
    }
    return n*k;
}
int n,m,T,c,d;
int A[200001];
int B[200001];
bool cmp(int x,int y)
{
	return x>y;
}
int presum[200001];
bool check(int X)
{
	int circle=std::min(X+1,n);
	int canget=presum[circle];
	int cirnum=d/(X+1);
	int Get=canget*cirnum;
	if(Get>=c)
	{
		return 1;
	}
	Get+=presum[std::min(n,d-(cirnum*(X+1)))];
	if(Get>=c)
	{
		return 1;
	}
	return 0;
}
signed main()
{
	T=read();
	while(T--)
	{
		n=read();
		c=read();
		d=read();
		for(int r=1;r<=n;r++)
		{
			A[r]=read();
		}
		std::sort(A+1,A+n+1,cmp);
		int tot=0;
		for(int r=1;r<=n;r++)
		{
			presum[r]=presum[r-1]+A[r];
		}
		for(int r=1;r<=std::min(d,n);r++)
		{
			tot+=A[r];
		}
		if(tot>=c)
		{
			puts("Infinity");
		}
		else
		{
			if(A[1]*d<c)
			{
				puts("Impossible");
			}
			else
			{
				int L=0,R=200000,mid;
				int ans=0;
				while(L<=R)
				{
					mid=(L+R)>>1;
					if(check(mid))
					{
						ans=mid;
						L=mid+1;
					}
					else
					{
						R=mid-1;
					}
				}
				printf("%lld\n",ans);
			}
		}
	}
    return 0;
}


```


---

