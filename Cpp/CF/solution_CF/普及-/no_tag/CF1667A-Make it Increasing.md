# Make it Increasing

## 题目描述

给定一个包含 $n$ 个**正整数**的数列 $a$ 以及一个长度为 $n$ 的数列 $b$ ,初始时数列 $b$ 的每一个元素都为0。定义一次操作为把数列 $b$ 中的某个元素 $b_i$ 加上或减去 $a_i$ 的值，求使得数列 $b$ 严格递增最小的操作次数。

## 样例 #1

### 输入

```
5
1 2 3 4 5```

### 输出

```
4```

## 样例 #2

### 输入

```
7
1 2 1 2 1 2 1```

### 输出

```
10```

## 样例 #3

### 输入

```
8
1 8 2 7 3 6 4 5```

### 输出

```
16```

# 题解

## 作者：Moyyer_suiy (赞：4)

[原题](https://www.luogu.com.cn/problem/CF1667A)
## 题意
首先有一个初始化为 $0$ 的数组 $b$，现在给你一个长度为 $n$ 的数组 $a$，对于数组 $b$，每次操作可以使 $b_i$ 加上或者减去 $a_i$。要求：求使得数列 $b$ **严格递增**最小的操作次数。
## 分析思路
看样例解释并仔细分析题目，发现最后得到的序列中一定有一个 $b_i$ 值仍为 $0$。以该元素为分界点，序列左半边的 $b_i$ 值为负数，右半边的 $b_i$ 为正数。即从分界点往两边的绝对值越来越大。

因此我们可以遍历数组 $a$，枚举这个 $0$ 的位置，以此为分界点向前和向后遍历数组，分别减掉和加上 $a_i$。其实质是两边的绝对值不断加 $a_i$。因此在这里就直接用绝对值代替加减的区别了。

此时用变量 $k$ 来记录这个元素操作最少次数后这个元素的值。再用一个累加器记录最少操作数并输出就可以了。详情见代码。
## 代码
```cpp
#include <bits/stdc++.h>
#define ll long long//一定要看数据范围，记得开long long!! 
using namespace std;
ll n,a[5005],ans=0x7fffffff;
int main()
{
    cin>>n;
    for(ll i=1;i<=n;i++) cin>>a[i];
    for(ll i=1;i<=n;i++)//即枚举0所在的位置 
	{ 
    	ll k=0,sum=0;//k记录每次操作后的值 
		for(ll j=i-1;j>=1;j--)//向前操作 
		{
    		sum+=k/a[j]+1;//记操作数，达到上一次的值后多一次操作 
    		k=(k/a[j]+1)*a[j];//更新 
		}
		k=0;//一定要记得清空！ 
    	for(ll j=i+1;j<=n;j++)//同上，向后操作 
		{
    		sum+=k/a[j]+1;
    		k=(k/a[j]+1)*a[j];
		}
		ans=min(ans,sum);
	}
	cout<<ans;
}
```

本题的讲解到这里就结束了。但还是想稍稍总结一下从本题中学到的问题。

$1.$ 做题时一定要仔细读题，一个字都不要落，提取关键信息。比如本题，如果你能看到样例解释的话，应该能很快有思路。另外一定要看数据范围！像平时的比赛都很喜欢卡你 `long long`。

$2.$ 读完题之后要清楚的理解题意再开始做题。读懂了之后自然就很好做了，不然半懵的状态下是很困难的！

$3.$ 做完一道要注意积累总结方法经验，做到类似的题目时就很快有思路了。

## 完。

---

## 作者：让风忽悠你 (赞：2)

从样例解释中不难看出，最后形成的 $b$ 数组中必然有一个 $b_i=0$。

很显然，当 $b_i=0$ 时，表示这个 $i$ 不用做任何操作，所以最优方案中必然存在这样的一个 $b_i$。

又因为题目中提到的数组 $b_i$ 严格单调递增，所以 $b_{1 \thicksim i-1}$，必然小于 0，$b_{i+1 \thicksim n}$，必然大于 0。

考虑枚举 $i$，表示 $b_i=0$，称这个 $i$ 为 0 点，那么其实可以视作 0 点左右都满足从 0 点开始严格单调递增，因为 $b_{1 \thicksim i-1}$ 满足从 $b_1$ 开始严格单调递增，就满足 $\left| b_{1 \thicksim i-1} \right|$ 从 $\left| b_1 \right|$ 开始单调递减，即从 $i-1$ 到 1 单调递增，且加减操作花费一样。

那么就可以将 0 点两边分开操作，定义当前操作数的上一个数为 $last$，那么当前数的操作次数即为 $last \div a_i+1$，然后更新 $last$。

```cpp
#include<cstdio>
#include<algorithm>
#define N 5005
#define inf 0x7fffffffffffffff
#define ll long long

using namespace std;

int n;
ll a[N],ans=inf; // 记得开 LL 

ll get(int x){
	ll res=0,last=0;
	
	for(int i=x-1;i>=1;i--){
		res+=(last/a[i]+1);
		
		last=(last/a[i]+1)*a[i]; // 更新last
	} // 以 0 点为起点绝对值递增
	
	last=0;
	for(int i=x+1;i<=n;i++){
		res+=(last/a[i]+1);
		
		last=(last/a[i]+1)*a[i]; 
	} // 同上 
	
	return res;
}

int main(){
	scanf("%d",&n);
	
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	
	for(int i=1;i<=n;i++)
		ans=min(ans,get(i)); // 枚举 0 点 
	
	printf("%lld",ans);
	
	return 0; 
}
```


---

## 作者：BX_mot (赞：1)

## 1. [题目](https://www.luogu.com.cn/problem/CF1667A)
## 2. 思路：
对于每一个 $b_{i}$ 可以枚举作为 $0$ 的情况暴力解决。

因为使改变次数最小，有一个 $0$ 就少一次改变机会，但是要求严格递增，就只能有一个 $0$。

然后找前面和后面符合严格递增的最小次数就可以了。

注意一个细节：**答案的初始值必须要大一些。**

## 3. 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long 
int n,a[10001];
int ans=0xffffffffffffff;//不能用0x3f3f3f3f，太小了,INT_MAX也不行，也小  555~
int x=0,ans1=0;
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)//枚举每一个作为0的点 找最小值
	{ 
		
		//前面的值
		for(int j=i-1;j>=1;j--)ans1+=x/a[j]+1,x=(x/a[j]+1)*a[j];
		x=0;
		//后面的值
		for(int j=i+1;j<=n;j++)ans1+=x/a[j]+1,x=(x/a[j]+1)*a[j];
		ans=min(ans,ans1);//找最小值
	}
	cout<<"QAQ"<<'\n';//防抄QAQ
	return 0;
}
```


---

## 作者：Dehydration (赞：1)

### 前言：

挺简单一道题，但大多数题解讲得晦涩难懂，我就以蒟蒻的方式向众蒟蒻解释一番。

[problem](https://www.luogu.com.cn/problem/CF1667A)。

### 思路：

很多题解讲到一定有个点为 $0$。这个他们不难从网上搜到，但后面的我就看不明白了，搞明白后在这里向大家解释一下。

在贪心证明出 $b$ 里面一定有一个点是 $0$ 以后，我们就可以枚举所有点**假设**这个点为最优点，再在所有解里面求最优值。

大多数都讲到了这里，但这里又是啥呢：

```
	int ansnow,lastmin;
	ansnow=lastmin=0;
	for(int j=i-1;j>=1;j--)
	{
		ansnow=ansnow+(lastmin/a[j])+1;
		lastmin=a[j]*((lastmin/a[j])+1);
	}
	lastmin=0;
	for(int j=i+1;j<=n;j++)
	{
		ansnow=ansnow+(lastmin/a[j])+1;
		lastmin=a[j]*((lastmin/a[j])+1);
	}
```



其中 ```lastmin``` 为前一个点的最小可能值，而 ```ansnow``` 为这个点的最小花费。

其中第一个循环为循环这个点前面所有点所花费的最小值：

```(lastmin/a[j])+1``` 是为了算出要达到比前面一个**严格**大于的最小代价，所以要加一。

```a[j]*(lastmin/a[j]+1)``` 是为了算出现在的点的最小可能值，因为要**严格**大于，所以不能写成 ```a[j]*lastmin``` 或者 ```a[j]*lastmin+1```。

第二个循环也是，但要注意将 ```lastmin``` 清零，因为中间还有个 $b_i=0$。

### 代码：

```
#include<bits/stdc++.h>
const int M=5005;
#define int long long
using namespace std;
int n,a[M],ans=LONG_LONG_MAX;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)
	{
		int ansnow,lastmin;
		ansnow=lastmin=0;
		for(int j=i-1;j>=1;j--)
		{
			ansnow=ansnow+(lastmin/a[j])+1;
			lastmin=a[j]*((lastmin/a[j])+1);
		}
		lastmin=0;
		for(int j=i+1;j<=n;j++)
		{
			ansnow=ansnow+(lastmin/a[j])+1;
			lastmin=a[j]*((lastmin/a[j])+1);
		}
		ans=min(ansnow,ans);
	}	
	cout<<ans<<'\n';	
}
```

**完美撒花！**

---

## 作者：IvanZhang2009 (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF1667A)

## 题意
给你一个数组 $a$，和一个一开始全是 0 的数组 $b$。每次操作可以使 $b_i=b_i+a_i$ 或 $b_i=b_i-a_i$，求最少操作次数使得数组 $b$ 严格单调递增。

简而言之，花费 $x$ 代价可以使 $b_i=x\cdot a_i$ 或 $-x\cdot a_i$。

## 解法
首先，要最优地达到目标，应该使前一部分的 $b_i$ 变成负数，中间一个 $b_i$ 保持是 0，后面一部分的 $b_i$ 变成正数。

考虑到 5000 的数据范围可以勉强过 $O(n^2)$ 的复杂度，那么可以枚举中间那个保持为 0 的 $b_i$ 的位置，然后 $O(n)$ 计算前后两部分的代价。

怎么计算代价呢？

以后面一部分要变成正数的 $b_i$ 为例：

我们设当前枚举到了 $j$。定义变量 $x$ 表示 $b_{j-1}$，那么接下来使 $b_j$ 严格大于 $b_{j-1}$ 的代价就是 $\lceil\frac{x+1}{a_j}\rceil$，同时将 $x$ 更新为 $\lceil\frac{x+1}{a_j}\rceil\cdot a_j$ 。

注意这里只是拿后面一部分要变成正数的 $b_i$ 为例， ~~虽然前面一部分变成负数的 $b_i$ 也是一样的~~。

## 代码
```cpp
#define int long long
#define REP(i,a,n) for(int i=(a);i<(n);i++)
int n;
int a[5005];
int res=1e18;
void Main() {
    cin>>n;
    REP(i,0,n)cin>>a[i];
    REP(i,0,n){
        int x=0,ans=0;
        for(int j=i-1;j>=0;j--){   //注意从i-1开始计算，因为b_i保持为0
            x+=a[j]-x%a[j];        //ceil((x+1)/a_j)*a_j=x+a_j-x mod a_j
            ans+=x/a[j];
        }
        x=0;
        REP(j,i+1,n){              //注意从i+1开始计算，因为b_i保持为0
            x+=a[j]-x%a[j];
            ans+=x/a[j];
        }
        res=min(res,ans);  //更新答案
    }
    cout<<res<<endl;
}
```

---

## 作者：Anguei (赞：1)

## 题意

给定长度为 $n (1 \leq n \leq 5000)$ 的数组 $a$，此外还有初始值全为零的 $b$ 数组。每次操作可以对 $b_i$ 加上 $a_i$，或者减去 $a_i$。

问最小经过多少次操作，可以使得数组 $b$ **严格单调递增**？

## 思路

结论：最优方案中，最终状态的 $b$ 数组，**有且仅有一个 $0$**。即：有且仅有一个位置可以不进行操作。

- 首先证明最多存在一个 $0$：假设存在多个 $0$，则无法满足 $b$ 数组严格单调递增的条件。故最多存在一个 $0$。
- 再证明存在一个 $0$：假设现在已经有一种 $b$ 数组当中不含 $0$ 的方案：$b_{k-1} < 0$，$b_k > 0$，$b_{k+1} > b_k$。此时一定可以忽略掉对 $b_k$ 的操作，即减少一些操作次数，将 $b_k$ 置零，这依然满足 $b_{k-1} < b_k < b_{k+1}$ 的条件。

数据范围只有 $5000$，支持 $O(n^2)$ 的做法：枚举每个位置作为零点，从这个位置向两边扩展，分别累加两边总共需要多少次操作即可。左边做减法，右边做加法。

注意：一些情况下，答案会爆 `int`，如 $a = [1, 1, 1, 1000000000, 1, 1000000000, 1, 1, 1]$ 时。

## 代码

```cpp
void solution() {
  int n;
  read(n);
  std::vector<int> a(n + 1), b(n + 1);
  for (int i = 1; i <= n; ++i) read(a[i]);
  ll ans = 1e18;
  for (int i = 1; i <= n; ++i) {
    ll sum = 0, now1 = 0, now2 = 0;
    for (int j = i + 1; j <= n; ++j)
      sum += now1 / a[j] + 1, now1 = a[j] * (now1 / a[j] + 1);
    for (int j = i - 1; j >= 1; --j)
      sum += now2 / a[j] + 1, now2 = a[j] * (now2 / a[j] + 1);
    ans = std::min(ans, sum);
  }
  print(ans);
}
```

---

## 作者：ylch (赞：0)

# CF1667A Make it Increasing 题解

[- 题目传送门 -](https://www.luogu.com.cn/problem/CF1667A)

### 思路

观察样例解释，$b$ 中一定有一个元素一定为 $0$（即原点）。再想一想，设置一个元素为 $0$ 可以省下一个操作数，所以一定有一个点为 $0$。

看一下数据范围，$5000^2=25000000$，$O(n^2)$ 的算法在 $2$ 秒内肯定是够的。

所以我们可以循环枚举 $0$ 点的位置 $i$，从 $0$ 点开始，分别向左右进行降序和升序延伸。

注意一个细节，两个数组元素之间的加减是要对应的（$b$ 数组的第 $i$ 个元素只能和 $a$ 数组的第 $i$ 个元素进行操作）。

### 当前代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int a[5005], b[5005];
int n;

signed main()
{
	cin >> n;
	for (int i=1; i<=n; i++)
		cin >> a[i];
	int minn = 1e9;
	for (int i=1; i<=n; i++)
	{
		int ans = 0;
		b[i] = 0;
		for (int j=i-1; j>=1; j--)
		{
			b[j] = 0;
			while (b[j] >= b[j+1])
			{
				b[j] -= a[j];
				ans++;
			}
		}
		for (int j=i+1; j<=n; j++)
		{
			b[j] = 0;
			while (b[j-1] <= b[j])
			{
				b[j] -= a[j];
				ans++;
			}
		}
		memset(b, 0, sizeof b);
		minn = min(ans, minn);
	}
	cout << minn << endl;
	return 0;
}
```

~~成功的超时了~~

### 改进与提升

改动哪里呢？仔细观察，我们使用的是三层循环，可以简化成两层循环，优化加减过程。

因为每一个元素都要比前一个元素更小（更大），那么我们可以记录下前一个改动的元素是多少，用前一个改动的元素 $\div$ 轮到的 $a_i$ 再 $+1$，就求出了这一个位置要进行几次加（减）。

求出当前改动后的元素：用元素填充数量（前一个改动的元素 $\div$ 轮到的 $a_i$ 再 $+1$ 的和）乘上当前元素 $a_j$。

过程解释：求出这个数有几个改动单位 $a_i$，因为题目要求严格递增，每两个相邻元素不可能相等，所以次数要加一。

最后求出改动数的和，循环打擂台就行。

### AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll n,a[5005];
ll ans = 0x3ffffff;

int main()
{
    cin >> n;
    for (ll i=1; i<=n; i++)
        cin >> a[i];
    for (ll i=1;i<=n;i++) 
    { 
    	ll k = 0, sum = 0; 
		for (ll j=i-1; j>=1; j--) 
        {
    	    sum += k / a[j] + 1; 
    	    k = (k / a[j]+1) * a[j]; 
		}
		k = 0; 
		for (ll j=i+1; j<=n; j++) 
		{
            sum += k / a[j] + 1;
    	    k = (k / a[j]+1) * a[j];
		}
		ans = min(ans, sum);
	}
	cout << ans << endl;
	return 0;
}
```

管理员大大辛苦啦~谢谢大家！

我们一起进步，一起 $rp++$！

---

## 作者：Spir1t (赞：0)

[题目](https://www.luogu.com.cn/problem/CF1667A)

这道题还算可以，我们的一道作业，现在让我们分析一下思路：

首先，看到说明提示后可以看出 $b$ 数组中肯定有一个数为 $0$，所以我们要枚举这个 $i$。

我们可以让 $b_1$ 到 $b_{i-1}$ 满足严格单调递增，即它们的绝对值也满足严格单调递增，也就是说将这个 $b$ 数组按题目要求来说的变成了严格递增。

然后就是操作次数了，不难想出，当前的操作次数即为上一个数除以当前 $a$ 数组的值即可，还有就是别忘了更新。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read() {
	ll x = 0, f = 1; char ch = getchar();
	while (ch > '9' || ch < '0') { if (ch == '-')f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}
/*
	a:1 2 1 2 1 2 1
	b:--3 -2 -1 0 1 2 3
*/
const ll N=5005;
ll n,a[N];
void solve(){
	cin>>n;
	ll mi=LONG_LONG_MAX;
	for(ll i=1;i<=n;i++){
		cin>>a[i];
	}
	for(ll i=1;i<=n;i++){
		//开始枚举b数组的0点
		ll ans=0,ss=0;
		for(ll j=i+1;j<=n;j++){
			ans+=(ss/a[j])+1;
			ss=a[j]*(ss/a[j]+1);
		}
		ss=0;
		for(ll j=i-1;j>0;j--){
			ans+=(ss/a[j])+1;
			ss=a[j]*(ss/a[j]+1);
		}
		mi=min(mi,ans);//求最小
	}
	printf("%lld\n",mi);
}
signed main(){
	solve();
	return 0;
}
```


---

## 作者：ForeverCC (赞：0)

完成操作后的数组 $b$ 可以看成三部分。

负数，$0$，正数。

枚举 $0$ 的位置，向前和向后遍历，将 $a_i$ 乘上一个数使它刚好比上一个 $b_{i+1}$ 小（或者比 $b_{i-1}$ 大）。

最后输出操作数量的最小值即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long//注意是long long
int n,a[5005],ans=1e18;
signed main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
    	scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++){
    	int pre=0,cnt=0;
    	for(int j=i+1;j<=n;j++){
    		cnt+=pre/a[j]+1;
    		pre=a[j]*(pre/a[j]+1);
		}
		pre=0;
		for(int j=i-1;j>=1;j--){
    		cnt+=pre/a[j]+1;
    		pre=a[j]*(pre/a[j]+1);
		}
		ans=min(ans,cnt);
	}
	printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：wzy2021 (赞：0)

一个位置，要不一直加，要不一直减。

枚举最终 $b_i = 0$ 的 $i$，

那么小于 $i$ 的位置都为负数，大于 $i$ 的位置都为正数，

既然“加”还是“减”的方向都定了，那么就容易了。

思路有了，最好还是自己独立写一写。

~~~cpp
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;

const int N = 5010;

int a[N];

int main() {
	int n; scanf ("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf ("%d", &a[i]);
	}
	long long ans = 1e18;
	for (int i = 1; i <= n; ++i) {
		long long use = 0; // use 表示需要“加”“减”多少次
		long long now = 0;
		for (int j = i - 1; j >= 1; --j) {
			long long t = (now + 1) / a[j]; // 选取一个最小的t，得到的结果大于前一个数。
			if (t * a[j] < now + 1) t ++;
			use += t; now = 1ll * t * a[j];
		}
		now = 0;
		for (int j = i + 1; j <= n; ++j) {
			long long t = (now + 1) / a[j];
			if (t * a[j] < now + 1) t ++;
			use += t; now = 1ll * t * a[j];
		}
		ans = min (ans, use);
	}
	printf ("%lld", ans);
	return 0;
} 
~~~

---

