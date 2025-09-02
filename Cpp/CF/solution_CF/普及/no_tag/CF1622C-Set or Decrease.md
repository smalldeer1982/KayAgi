# Set or Decrease

## 题目描述

给你一个长度为 $n(1 \leq n \leq 2 \cdot 10^5)$ 的序列 $a_1,a_2,...,a_n(1 \leq a_i \leq 10^9)$ 和整数 $k(1 \leq k \leq 10^{15})$。

每一步你可以：

1. 选择一个下标 $i$ 使得 $a_i = a_i - 1$。
2. 或者选择两个下标 $i$ 和 $j$ 使得 $a_i =a_j$。

你需要求出最少在多少步之后，$\sum\limits_{i=1}^na_i \leq k$（你可以将一些元素减成负数）。

## 样例 #1

### 输入

```
4
1 10
20
2 69
6 9
7 8
1 2 1 3 1 2 1
10 1
1 2 3 1 2 6 1 6 8 10```

### 输出

```
10
0
2
7```

# 题解

## 作者：__KrNalty__ (赞：19)

大佬们都太苣了，像我这样的蒟蒻连贪心都想不出来。

### 题意简述：

给你一个长度为 $n(1 \leq n \leq 2 \cdot 10^5)$ 的序列 $a_1,a_2,...,a_n(1 \leq a_i \leq 10^9)$ 和整数 $k(1 \leq k \leq 10^{15})$。

每一步你可以：

1. 选择一个下标 $i$ 使得 $a_i = a_i - 1$。
2. 或者选择两个下标 $i$ 和 $j$ 使得 $a_i =a_j$。

你需要求出最少在多少步之后，$\sum\limits_{i=1}^na_i \leq k$（你可以将一些元素减成负数）。

### 做题思路：

二分答案。

~~知周所众，~~ 二分答案有基础的 4 个步骤：

1. 看看这题是否满足二分的条件。

2. 确定二分的边界。

3. 写出 ```check``` 函数，不断更新 ans。

4. 最后输出答案。

接下来我们一步一步介绍如何完成这题。

#### step 1. 二分的条件：

我们看这题，大家想一想，如果你用 2 次操作就可以使数组满足条件，那么 3 次操作可以吗？ 4 次呢？

答案是肯定的。我们只要随意的将一个数字进行第一种操作，就还可以使数组满足条件，所以我们说，这题是满足二分的条件的，是可以二分的。

#### step 2. 确定二分的边界：

显而易见的，最好的情况肯定是一次操作也不进行。但最坏的情况（或者说最那啥的情况）呢？

动动脑筋，最坏的情况肯定是每次都执行第一种操作使数组满足条件，因为对于一个不是最小的数，将其减一所带来的收益一定没有把它的值变为最小的数好。

综上所述，二分的边界就是：

```
l = 0, r = sum[n] - k; // sum 数组为 a 数组的前缀和。
```

#### step 3. 写出 ```check``` 函数，更新 ans：

我们在外面已经使用了一个 $O(\log {n})$ 的二分，那么我们在 ```check``` 函数中就只能使用 $O(n)$ 或 $O(n \log {n})$ 了。

~~这写 ```check```，多是一件美逝啊。~~

思路：

让 ```i``` 从 ```max(0ll, mid - n + 1)``` 到 ```mid``` 枚举执行第一种操作的次数，那么执行第二种操作的次数就是 ```mid - i``` 次了。想一想：这里为什么是从 ```max(0ll, mid - n + 1)``` 开始枚举呢？（思考时间，不提供答案啦）

在 ```for``` 循环中，我们肯定是将最小值减去 ```i``` 次，将最大的 ```mid - i``` 个数都变成减完后的最小值，这样可以使这一次的答案最优。

用代码实现，```a[1] - i``` 是减完后的最小值，```sum[n] - sum[n - j]``` 是最大的 j 个数的和。即我们将最大的 j 个数都变成减完后的最小值会损失： 
```(sum[n] - sum[n - j]) - j * (a[1] - i)```。

最后对所有的情况求 $\min$ 即可。

```check``` 函数代码：

```
bool check(int mid)
{
	int minn = 1e18;
	for (int i = max(0ll, mid - n + 1); i <= mid; i++)
	{
		int j = mid - i; 
		minn = min(minn, sum[n] - ((sum[n] - sum[n - j]) - j * (a[1] - i)) - i);
	} 
	return minn <= k;
}
```

想一想：如果 ```check``` 函数返回的是 ```true```，那么我们应该做什么呢？

#### step 4. 输出答案：

当二分结束时，输出最后一次更新的 ```ans``` 就是最后的答案啦！

### 完整代码供参考：

```
#include <bits/stdc++.h>
using namespace std;
#define int long long // 偷懒神器 
int t, n, k, a[200005], sum[200005]; // sum 数组用来求 a 数组的前缀和 
bool check(int mid)
{
	int minn = 1e18;
	for (int i = max(0ll, mid - n + 1); i <= mid; i++) // 枚举在这 mid 次操作中几次是第一种操作
	{
		int j = mid - i; // 那么第二种操作就是 mid - i 次
		// 我们肯定是将最小值减去 i 次，将最大的 j 个数都变成减完后的最小值即可
		// 注意在这里不要修改 a 数组的值
		// a[1] - i 是减完后的最小值，sum[n] - sum[n - j] 是最大的 j 个数的和
		// 即将最大的 j 个数都变成减完后的最小值会损失： 
		// (sum[n] - sum[n - j]) - j * (a[1] - i)
		minn = min(minn, sum[n] - ((sum[n] - sum[n - j]) - j * (a[1] - i)) - i);
	} 
	return minn <= k;
}
signed main()
{
	cin >> t;
	while (t--)
	{
		cin >> n >> k;
		for (int i = 0; i <= n + 3; i++)
		{
			sum[i] = 0;
		}
		for (int i = 1; i <= n; i++)
		{
			cin >> a[i];
		}
		sort(a + 1, a + n + 1);
		for (int i = 1; i <= n; i++)
		{
			sum[i] = sum[i - 1] + a[i];
		}
		if (sum[n] <= k)
		{
			cout << 0 << endl;
			continue; 
		}
		int l = 0, r = sum[n] - k, ans; 
		/*
		确定二分边界 left = 0，
		right 是总和 - k。 
		因为如果每一次都执行第一种操作的话就是 sum[n] - k 次 
		*/
		while (l <= r) // 二分答案 
		{
			int mid = (l + r) / 2;	
			if (check(mid))
			{
				r = mid - 1; // 如果 mid 可以说明右边都可以
				ans = mid; // 记录当前的答案 
			}
			else
			{
				l = mid + 1; // 如果 mid 不可以说明左边都不可以 
			}
		} 
		cout << ans << endl;
	}
	return 0;
}
```

蒟蒻的第二篇「题解」，望通过。

###### ~~超长凉心题解，丶个赞吧。~~

---

## 作者：ArrogHie (赞：6)

## 题意

可以执行两种操作：

- 将 $a_i$ 减一
- 将 $a_i$ 的值变为 $a_j$

求最少需要多少次操作使得 $\sum a_i \leq k$

## 题解

可以发现，我们只需要将最小的一个数进行减一操作，对于一个不是最小的数，将其减一所带来的收益一定没有把它的值变为最小的数好。所以我们只需要判断将最小的数减到多少需要的步数最小即可。

枚举需要将多少个数执行第二种操作，设其为 $x$，一定是将最大的 $x$ 个数执行操作最优。之后计算要想满足条件需要将最小的 $a_i$ 减去多少。可以发现每次将最小的 $a_i$ 减一，会使这 $x$ 个数全都减一，因为一定是先进行第一种操作再进行第二种操作更优。设将这 $x$ 个数全部变成最小的 $a_i$ 后一共还需要减去 $p$ 才满足条件，则最小的 $a_i$ 需要减去的数就是 $\left \lceil p/(x+1) \right \rceil$，满足条件所需的步数即为 $x+\left \lceil p/(x+1) \right \rceil$。取最小值即可

---

## 作者：Isshiki·Iroha (赞：3)

## 题解

~~此题我因为少加了几个字符导致赛时 WA 傻~~

这个题有两种操作：选定一个 $i$

- 使 $a_i=a_i-1$
- 使 $a_j=a_i(j \in[1,n])$

然后用最少的操作使得 $\sum^n_{i=1}a_i \le k$，$k$ 为给定的数字。

### 思路

肯定是贪心，想把 $a_i$ 变小，肯定是把他直接变成当前最小值而不是一个一个减。如果把所有的 $a_i$ 都变成最小值都不行那肯定只能把最小值一个一个减了。

还有，我如果要把一个数变为最小值，肯定先把数组里面最大的变成最小的，这个不解释了。

我们设最小值减小了 $x\ (x \in (-\inf,0])$，把后面第 $m,(m \in [0,n))$ 大个数减小，（为了方便计算，我们数组从小到大排序）那么要使得：

$$(a_1-x) \times (m+1)+sum_{n-m}-sum_1 \le k$$

我们发现 $m$ 的范围我们确定了，我们可以枚举 $m$ 来求出 $x$，把 $x$ 分离：

$$x \ge a_1-\frac{k-sum_{n-m}+sum_1}{m+1}$$

然后这样除会有取舍的问题，我们要使右边这个式子取整后更可能大，取整后 $x$ 就可以直接取右边式子的值了，但是注意： **$x$ 最小是 $0$!!!**

代码实现：（不上快读快输了）

```cpp
// Problem: C. Set or Decrease
// URL: https://codeforces.com/contest/1622/problem/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Author: Isshiki Iroha
// Created in 2021-12-27 23:04:00
// Description: 

#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=2e6+10;
int T,n;
ll k,a[maxn],sum[maxn];
ll Div(ll a,ll b){
	
	if(a<0&&a%b!=0)return a/b-1;
	return a/b;
}
int main() {
	read(T);
	while(T--){
		read(n,k);
		for(int i(1);i<=n;++i){
			read(a[i]);
		}
		sort(a+1,a+1+n);
		for(int i(1);i<=n;++i){
			sum[i]=sum[i-1]+a[i];
		}
		if(sum[n]<=k){
			write(0);
			putc('\n');
			continue;
		}
		ll ans=1e18;
		ll s1=0;
		for(int b(0);b<n;++b){
			s1=max(a[1]-Div((k-sum[n-b]+sum[1]),(b+1ll)),0ll);
			if(s1+b<ans){
				ans=s1+b;
			}
		}
		write(ans);
		putc('\n');
	}
	flush();
	return 0;
}
```



---

## 作者：daniEl_lElE (赞：2)

## 思路

考虑如何更快降低。

我们令一个 $a_i$ 降低，降低到一定高度时让另外一些 $a_j$ 变成 $a_i$ 来完成要求。显而易见地，降低的 $a_i$ 应该满足 $a_i=\min(a_1,a_2,\dots,a_n)$。

考虑先将 $a$ 数组排序，记 $minus=\sum_{i=1}^na_i-k$。考虑先降低 $a_1$，然后将最后 $j$ 个降低为 $a_1$。这样，$a_1$ 要降低的次数是 $\max(\lceil\dfrac{minus-\sum_{i=n-j+1}^n(a_i-a_1)}{j+1}\rceil,0)$。意思是现将后 $j$ 个 $a_i$ 变成 $a_1$，再同时降低 $j+1$ 个一次。则总操作次数为 $\max(\lceil\dfrac{minus-\sum_{i=n-j+1}^n(a_i-a_1)}{j+1}\rceil,0)+j$。对于不同的 $j$ 将这个式子比大即可。复杂度 $O(n)$。

## code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	int t;
	cin>>t;
	while(t--){
		int n,k;
		cin>>n>>k;
		int a[n+1]; 
		int tot=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			tot+=a[i];//计算总数
		}
		sort(a+1,a+n+1);//排序预处理
		int qzh[n+1];
		qzh[1]=0;//计算前缀和
		for(int i=2;i<=n;i++){
			qzh[i]=qzh[i-1]+a[i];
		}
		if(tot<=k){//是否已经小于，特判一下
			cout<<0<<endl;
			continue;
		}
		int ans=tot-k;//考虑全部降a1，则要降低ans次
		for(int i=n;i>=2;i--){
			int down=(k-qzh[i-1])/(n-i+2);
			if(down*(n-i+2)>k-qzh[i-1]){
				down--;
			}
			ans=min(ans,max(a[1]-down,0ll)+(n-i+1));
			if(down>a[1]){
				break;
			}//以上为推式子过程
		}
		cout<<ans<<endl;
	}
}
/* things to check
1.  int overflow or long long memory need
2.  recursion/array/binary search/dp/loop bounds
3.  precision
4.  special cases(n=1,bounds)
5.  delete debug statements
6.  initialize(especially multi-tests)
7.  = or == , n or m ,++ or -- , i or j , > or >= , < or <= , - or =
8.  keep it simple and stupid
9.  do not delete, use // instead
10. operator priority
11. is there anything extra to output?
12. if you don't know where the bug is , try to clear some parts of the code
 and check each part seperately.
13. ...
*/

```

---

## 作者：huyangmu (赞：2)

可以发现，每次操作 $1$ 会使序列和减少 $1$，每次操作 $2$ 除了 $a_{i}$ 和 $a_{j}$ 相等时，对序列和的影响都是比操作 $1$ 大的。

所以要尽量对序列使用操作 $2$，但我们不知道具体要进行多少次操作 $2$，所以要枚举，设当前枚举到 $x$，即要进行 $x$ 次操作 $2$，最优策略显然是把最大的 $x$ 个数变成序列中最小的数。但经过修改后可能仍然比 $k$ 大，就需要进行操作 $1$，如果在操作 $2$ 之后进行操作 $1$，和每次会减少 $1$，但在操作 $2$ 之前对最小的数进行操作 $1$，会使和每次减少 $x+1$。所以考虑先对最小的数进行操作 $1$，直到对应的 $x$ 满足条件，再对最大的 $x$ 个数进行操作 $2$。

### 具体实现

将序列排序，方便求最小值，和最大的 $x$ 个值，对于任意一个 $x$，新的序列和为 $x \times a_{1} + \sum\limits_{i=1}^{n-i}a_{i}$，可以使用前缀和快速求和，如果和 $\le k$，则满足要求，不用进行操作 $1$。否则用两数之差除以 $x+1$ 后向上取整就是操作 $1$ 的次数。

### AC Code

```cpp

#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int T, n, k, a[N], s[N], sum = 0, pos, ans = -1;
int cal (int a, int b){
	if (a % b == 0) return a / b;
	return a / b + 1;
}
signed main (){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> T;
	while (T --){
		cin >> n >> k;
		sum = 0;
		for (int i = 1; i <= n; ++i){
			cin >> a[i];
			sum += a[i];
		}
		if (sum <= k){
			cout << 0 << '\n';
			continue;
		}
		sort (a + 1, a + n + 1);
		pos = a[1];
		for (int i = 1; i <= n; ++i) s[i] = s[i - 1] + a[i]; 
		ans = LONG_LONG_MAX;
		for (int i = 0; i < n; ++i){//相当于x 
			int tmp = max ((i * a[1] + s[n - i] - k), 0ll) //和0取max;
			ans = min (ans, i + cal (tmp, i + 1));
		}
		cout << ans << '\n';
	}
	return 0;
}

---

## 作者：songtaoran (赞：0)

考虑二分答案。  
首先肯定要对 $a$ 数组排序。  
记 $sum_i = \sum^i_{j = 1} a_j$，接下来就是`check`函数的时间啦。  
枚举做第一次操作的次数 $i$，则此时做第二次操作的次数就是 $j = mid - i$ 次，即先把 $a_1$ 减小 $i$，再把最大的 $j$ 个数都赋值成 $a_1$。一操作会减小 $i$，二操作会减小 $(sum_n - sum_{n - j}) - j \times (a_1 - i)$。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll T, n, k, a[200010], sum[200010];
bool check(ll x){
	ll mn = 9e18;
	for(ll i = max(0ll, x - n + 1); i <= x; i++){ // 防止出现 TLE，所以只能 O(n)了 
		ll j = x - i;
		mn = min(mn, sum[n] - ((sum[n] - sum[n - j]) - j * (a[1] - i)) - i);
	}
	return mn <= k;
}
int main(){
	cin >> T;
	while(T--){
		scanf("%lld %lld", &n, &k);
		for(ll i = 1; i <= n; i++) scanf("%lld", &a[i]);
		sort(a + 1, a + n + 1);
		for(ll i = 1; i <= n; i++) sum[i] = sum[i - 1] + a[i];
		if(sum[n] <= k){
			printf("0\n"); continue;
		}
		ll l = 0, r = sum[n] - k;
		while(l < r){
			ll mid = (l + r) >> 1;
			if(check(mid)) r = mid;
			else l = mid + 1;
		}
		printf("%lld\n", l);
	}
	return 0;
}
```
[提交记录 - $292460727$](https://codeforces.com/problemset/submission/1622/292460727)

---

## 作者：z_yq (赞：0)

### 题面
给定一个长度为 $n$ 的序列 $a$ 和一个整数 $k$，然后给定两种操作。
- 操作一，可以令任意一个 $a_i$ 变为 $a_i-1$，即选择一个 $i$ 使 $a_i=a_i-1$。
- 操作二，可以令任意一个 $a_i=a_j$。
求要多少次操作，可以使 $\sum_{i=1}^{n}a_i \le k$

### 做法
我们考虑两个数字，$a_i$ 与 $a_j$，这里还假设 $a_i \le a_j$，我们可以想到，如果我们要尽量减少，最好的方案是先使用操作一，在使用操作二，因为如果你先使用操作二在使用操作一时，$a_i = a_i - 1$ 而 $a_j = a_i$，但是如果先使用操作一即可让 $a_i = a_j = a_i - 1$ 所以我们肯定是对于这个序列 $a$ 是先使用操作一，再使用操作二的。

其次，我们需要考虑，我们的操作一明显是要减在 $a$ 的最小值上面，这样才能让最小值减小（操作二的复制必然是要把最大值复制到最小值），不浪费总操作次数。

所以我们可以设：$x$ 表示我们对最小值进行了 $x$ 次操作一，而 $m$ 表示我们对最大的 $m$ 个数进行了 $m$ 次操作二，$sum_i$ 表示 $\sum_{j=1}^{i}a_j$（此时的 $a$ 已经排好了序），则我们可以去推式子。

$ (sum_0 - x) \times (m +1) + sum_n - sum_{n-m} \le k$

提取 $x$ 并放在不等式右边

$ x \times (m+1) \le sum_0 \times (m+1) + sum_n - sum_{n-m} -k $

则 $x \ge (sum_0 \times (m+1) + sum_n - sum_{n-m} -k) \div (m+1)$

我们分离常数：$x \ge sum_0 + (sum_n - sum_{n-m} -k) \div (m+1)$

然后我们这个时候枚举 $m$ 就可以求出 $x$ 的最小值，然后就可以得到 $m + x$ 的最小值，然后就可以得到结果啦！

### Code
```cpp
//制作不易，请管理员大大验收，谢谢哦！
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=2e6+9;
ll n,k,T,a[N],ans,sum[N];
int main()
{
    cin>>T;
    while(T--)
    {
        cin>>n>>k;
        for(int i=1;i<=n;i++)
            cin>>a[i];
        sort(a+1,a+n+1);
        for(int i=1;i<=n;i++)
            sum[i]=sum[i-1]+a[i];
        ans=LONG_LONG_MAX;
        for(int i=0;i<n;i++)
        {
            ll step=(sum[1]-sum[n-i]+k)/(i+1);
            if((sum[1]-sum[n-i]+k)%(i+1)!=0 && (sum[1]-sum[n-i]+k)<0)
                step--;
            if(max(0ll,a[1]-step)+i<ans)
                ans=max(0ll,a[1]-step)+i;
        }
        cout<<ans<<'\n'; 
    }
    return 0;
}
```

---

