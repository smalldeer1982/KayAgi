# [ABC339C] Perfect Bus

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc339/tasks/abc339_c

一台のバスが走っています。バスの乗客の数は常に非負整数です。

このバスにはある時点で $ 0 $ 人以上の乗客が乗っており、その時点から現在までに $ N $ 回停車しました。このうち $ i $ 回目の停車では乗客が差し引き $ A_i $ 人増えました。$ A_i $ は負の値であることもあり、その場合は乗客が差し引き $ -A_i $ 人減ったことを意味しています。また、停車時以外には乗客の乗り降りはありませんでした。

与えられた情報に矛盾しない現在のバスの乗客の数として考えられる最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ -10^9\ \leq\ A_i\ \leq\ 10^9 $
- 入力される数値はすべて整数
 
### Sample Explanation 1

はじめに乗っている乗客の人数が $ 2 $ 人であるとき、現在の乗客の人数は $ 2\ +\ 3\ +\ (-5)\ +\ 7\ +\ (-4)\ =\ 3 $ 人であり、さらにバスの乗客の人数は常に非負整数となります。

## 样例 #1

### 输入

```
4
3 -5 7 -4```

### 输出

```
3```

## 样例 #2

### 输入

```
5
0 0 0 0 0```

### 输出

```
0```

## 样例 #3

### 输入

```
4
-1 1000000000 1000000000 1000000000```

### 输出

```
3000000000```

# 题解

## 作者：Genius_Star (赞：4)

### 思路：

要求最小值，且公交车上不能有负数个人，考虑贪心。

我们先假设初始有 $0$ 人，找到公交车每时每刻人数的最小值即记为 $Min$；如果 $Min<0$，则这个时刻公交车上有 $Min$ 人，因为是负数了，所以初始应该至少有 $Min$ 人，才能导致现在不为负数个人；否则初始公交车上可以有 $0$ 人。

时间复杂度为 $O(N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=200200;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,sum,Min=0;
ll a[N];
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		sum+=a[i];
		Min=min(Min,sum);
	}
	if(Min<0)
	  write(abs(Min)+sum);
	else
	  write(sum);
	return 0;
}
```


---

## 作者：XXh0919 (赞：2)

我不知道该怎么说这题……

我们可以在输入时用 $sum$ 对输入的 $n$ 个数进行累加，表示此时车上所拥有的人数。然后每加一次就与题目中要求的车上初始最少人数 $ans$ 进行比较，找到最小的。即：找到最少要补上多少人才会使车上人数不为负。最后再用 $sum$ 减掉 $ans$ 即可（因为 $ans$ 是非正数）。

因为 $sum$ 在累加时可能会是负数，所以 $ans$ 不用赋一个极大值（赋了会出事，本人亲测）。

### AC Code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e6+15;

int n,sum,ans;
int a[N];

signed main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		sum+=a[i];
		ans=min(sum,ans);
	}
	cout<<sum-ans<<'\n';
	return 0;
}
```

---

## 作者：2c_s (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc339_c)

## 思路

$1\le N\le 2\times 10^5$，很容易想到二分，时间复杂度 $\mathcal{O}(N\log N)$。

读入数据后直接二分一开始的乘客数量。每次从 $1$ 到 $N$ 循环检查如果一开始有 ``mid`` 名乘客时能不能保证每站车上的乘客数不为负。如果可以那么减小右端点，反之则增大左端点。

找到最小初始乘客的值 ``ans`` 后计算 

$$\sum^n_{i=1}A_i$$ 

并输出 ``ans`` 加这个值即可。

## AC 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read(){//快读。
	ll k=0,flag=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')flag=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		k=(k<<1)+(k<<3)+(c^48);
		c=getchar();
	}
	return k*flag;
}
const int N=2e5+10;
ll n,a[N],ans;
inline bool check(ll x){//检查是否合格。
    ll sum=x;
    for(int i=1;i<=n;++i){
        sum+=a[i];
        if(sum<0)return 0;
    }
    return 1;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;++i)a[i]=read();
    ll l=0,r=1e18;//从 0 开始。
    while(l<=r){
        ll mid=l+r>>1;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }
        else l=mid+1;
    }
    for(int i=1;i<=n;++i)ans+=a[i];
    cout<<ans;
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/146033868)

---

## 作者：Crazyouth (赞：1)

## 分析

假设车上开始时没人，且乘客可以为负数，由于不合常理，我们需要找到它最少的时候有多少人，然后就会发现，我们只需要在上车时有这么多人，就不会出现负数。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[200010];
signed main()
{
	int n,minn=0,sum=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		sum+=a[i];
		minn=min(minn,sum);
	}
	minn=max(-minn,0ll);
	for(int i=1;i<=n;i++) minn+=a[i];
	cout<<minn;
	return 0;
}

---

## 作者：zhangboyong (赞：1)

## 题意简述

有一个长度为 $N$ 的序列 $a$，若 $a_i$ 为正，代表上车人数，$a_i$ 为负，代表下车人数。

要求的是最后车上的人数，当且仅当初始人数最小且满足任何一个时刻车上人数大于等于 $0$。

## 思路分析

如果初始人数不为 $0$，那么在原始序列 $a$ 中，一定存在某一时刻前缀和为负数。

显然我们可以去二分这个初始人数，再求出最后车上的人数。

因为一个数大于等于真正的答案时，那么就不会存在某一时刻前缀和为负数；反之就一定会存在前缀和为负数的情况。满足单调性。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,a[200005],ans,sum;
bool check(int x){
	for(int i = 1;i<=n;i++){
		x+=a[i];
		if(x<0)return 0;
	}
	return 1;
}
signed main(){
	cin >> n;
	for(int i = 1;i<=n;i++){
		cin >>a[i];sum+=a[i];
	}
	int l = 0,r=200000000000001,mid;//答案范围比较大，2e5*1e9
	while(l<=r){
		mid=l+r>>1;
		if(check(mid)){
			ans=mid;
			r = mid-1;
		}else{
			l = mid+1;
		}
	}
	cout <<sum+ans;//二分的是初始人数，需要加入要序列的和
}
```

---

## 作者：SJZ2010 (赞：1)

## 题意

有一辆公交车，开始不知道有几个人。公交车经过了 $N$ 个车站。给出一个序列 $A$，$A_i$ 表示在车站 $i$ 上来了几个人（$A_i<0$ 表示下去了一些人）。公交车上每时每刻都不能有负数个人。求**现在**公交车上最少有几个人。

## 做法

我们求一遍 $A$ 的前缀和，把 $A$ 中最小的数 $A_{min}$ 求出来，如果 $A_{min} < 0$，那么答案是 $-A_{min}+A_n$，否则答案是 $A_n$。

原因是如果 $A_{min}<0$，那我们需要在开始时在车上放几个人，把 $A_{min}$ 的人放上去可以直接把 $A_i$ 的前缀和上的每一个负数填为非负数。（前缀和反映的是如果初始人数为最小值 $0$，那在某时刻公交车上的人数）

```cpp
#include <cstdio>
#include <algorithm>

using ll = long long;

const int N = 2e5 + 5;

int n;
ll a[N];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	ll tmp(0), mi(0), ans;
	for (int i = 1; i <= n; i++)
	{
		tmp += a[i]; // tmp 就是 A 的前缀和
		mi = std::min(tmp, mi);
	}
	ans = -mi + tmp;
	printf("%lld\n", ans);
	return 0;
}


```

---

## 作者：jqQt0220 (赞：0)

## 题意简述

一辆公交车上的乘客人数总是一个非负整数。一开始公交车上有零或更多人，此后公交车停靠了 $N$ 次，在第 $i$ 个站点，乘客人数增加了 $A_i$。

请找出能使公交车上的人数在每一时刻都能保持非负整数的最小初始人数，并输出停靠 $N$ 次后公交车上的人数。

## 思路

没有 B 难。~~那就把 B 的题解通道开开（bushi~~。我们可以对每个 $A_{i}$ 求前缀和，再取最小值。这个最小值即为每一时刻人数相较开始时人数的偏移量的最小值。所以只要取一个最小的为非负整数的开始人数，使它加上这个最小值为非负整数。很明显，如果最小值非负，那么直接取 $0$ 即可；否则就取绝对值。我们可以用 `max(0,-t)` 表示这个初始人数，其中 $t$ 表示最小值。若 $t\ge0$，那么 $-t\le0$，函数返回 $0$；若 $t<0$，那么 $-t>0$，函数返回 $-t$，即最小值的绝对值。最后加上整个 $A$ 数组的总和就是要求的最后的最少人数了。

代码：
```cpp
#define ll long long
const int _mxn=2e5+5;
int n;
ll a[_mxn],s=0,t=1e9;//为防止爆掉开 long long
//s：前缀和，t：最小值 
int main()
{
    ___();
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i],s+=a[i],t=min(t,s);//边输入边求，可以不开数组
    cout<<max(0ll,-t)+s<<endl;//max 函数要让两个参数类型一样，所以用 0ll 表示 long long 类型的 0；最后再加上最终的和 s
    return 0;//完美结束 QwQ
}
```

---

## 作者：indream (赞：0)

## [ABC339C] Perfect Bus 题解
[AtCoder](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/abc339_c)

### 思路
显然，任意一个时刻，车上的人都不可能为负数。

我们只要对上车人数处理其前缀和，若处理到 $sum_i<0$，说明最开始车上至少有 $|sum_i|$ 人以保证此时车上不出现「负人数」。

显然，最小的**负数**前缀和之绝对值即为开始时最少的人数。再用这个数加上所有上车的人数即可。

时间复杂度 $O(n)$。

注意开超长整型。

### 代码
比我同场 A 的代码还短。。。

这里写的是 $O(1)$ 空间，显然 $a,sum$ 这两个数组可以被覆盖。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,tmp,sum,minn=0;
//最小值初始化为 0，自动忽略大于 0 的 sum[i]
int main(){
    cin>>n;
    for(int i=0;i<n;++i){
        cin>>tmp;
        sum+=tmp;
        if(sum<minn)
            minn=sum;
    }
    cout<<sum-minn;
    return 0;
}
```

---

## 作者：vorDeal (赞：0)

公共汽车上的乘客人数总是一个自然数，换言之，乘客人数总是大于等于 $0$。

考虑进行前缀和，令 $b_p=\sum\limits^{p}_{i=1}a_i$。

由当前车上乘客数最小，不妨令 $b_p$ 最小的站点 $p$ 之人数为 $0$。

则答案即为 $b_n-\min\limits_{p=1}^{n}b_p$。

**AC Code：**

```cpp
#include <bits/stdc++.h>
using namespace std;

long long n, a[200005], b[200005], mnx;

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i], b[i] = b[i - 1] + a[i], mnx = min(b[i], mnx);
    cout << max(0LL, b[n - 1] - mnx);
    return 0;
}
```

---

## 作者：Milthm (赞：0)

你发现这个求最后的最小人数可以转化为开始的最小人数，求完加上整个 $a$ 序列的和就可以了。

求开始的最小人数，很容易想到二分。再加上如果 $x$ 是符合要求的，那么 $>x$ 的一定也符合要求。所以满足二分的单调性，直接二分就可以了。

### AC code

```cpp
#include<bits/stdc++.h>
#define N 200005
#define int long long
using namespace std;
int n,a[N],qwq;
int check(int k){
	for(int i=1;i<=n;++i){
		k+=a[i];
		if(k<0)return 0;
	}
	return 1;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;++i)cin>>a[i],qwq+=a[i];
	int l=0,r=1e15,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	cout<<ans+qwq;
	return 0;
}

```


---

## 作者：Walrus (赞：0)

# [ABC339C](https://atcoder.jp/contests/abc339/tasks/abc339_e)

最多黄，顶天了，赛时**最后 5 分钟**以三发罚时（二分上界小了调半天）切了。

## 题意
简述：给你 $n$ 个数，下文称作 $a$ 数组，让你求一个数 $x$，$x$ 在每一时刻，加上每一个 $a_i$，其值都**必须大于等于 $0$。** 

## 做法
发现当一个 $x$ 满足条件时，比 $x$ 大的数一定可以满足，这里应该不需要证了。所以答案具有单调性，考虑二分。

二分时记得把上界设大，如果 $a$ 数组全是大负数肯定二分不到答案。

直接 $O(N)$ check 答案即可。

时间复杂度 $O(N \log N)$。


## Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 5;

int a[N], n, l, r, ans;

bool check(int x) {
	int now = x;
	for(int i = 1; i <= n; ++i) {
		now += a[i];
		if(now < 0)
			return false;
	}
	return true;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr), cout.tie(nullptr);
	
	cin >> n;
	for(int i = 1; i <= n; ++i)
		cin >> a[i];
	
	int l = 0, r = LONG_LONG_MAX;
	
	while(l < r) {
		int mid = l + r >> 1;
		if(check(mid))
			ans = mid, r = mid;
		else
			l = mid + 1;
	}
	for(int i = 1; i <= n; ++i)
		ans += a[i];
	cout << ans;
	return 0;
}

---

## 作者：WilliamFranklin (赞：0)

### 主要思路

直接贪心。

考虑如果 $i$ 满足 $A_i < 0$ 且当前车上的人数最小答案小于 $-A_i$ 时，那么我们发现此时让车上人数最少的情况，就是等于 $0$。

那么对于其他情况，直接当前车上的人数最小答案加上 $A_i$ 即可。

对于证明，也很简单，其实我们仅仅是将车上最初的人数最小化了。

话不多说，看看代码吧。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define mp(Tx, Ty) make_pair(Tx, Ty)
#define For(Ti, Ta, Tb) for(auto Ti = (Ta); Ti <= (Tb); Ti++)
#define Dec(Ti, Ta, Tb) for(auto Ti = (Ta); Ti >= (Tb); Ti--)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define range(Tx) begin(Tx),end(Tx)
const int N = 2e5 + 5;
int a[N];
int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int n;
	cin >> n;
	For(i, 1, n) cin >> a[i];
	long long now = 0;
	For(i, 1, n) {
		if (now + a[i] < 0) {
			now = 0;
		} else {
			now += a[i];
		}
	}
	cout << now;
	return 0;
}
```


---

## 作者：CheZiHe929 (赞：0)

# AT_abc339_c 题解

### 题目链接

[Atcoder](https://atcoder.jp/contests/abc339/tasks/abc339_c)

[Luogu](https://www.luogu.com.cn/problem/AT_abc339_c)

### 题目大意

给你 $n$ 个站点的人数变化，求通过改变初始时公交车上的人数，使得到达最后一个站点后可能的人数最小值。

即要保证每时每刻公交车上的人数都为非负数。

### 简要思路

我们对人数变化情况的数组 $a$ 求前缀和，记录出现的最小值。

如果最小值 $minn$ 是个负数且出现在位置 $i$，那么我们可以使 $[1,i]$ 这一部分的值为 $0$，因此只需要统计 $[i+1,n]$ 的和即可。

否则则说明每时每刻人数都一定是非负数，那么为了使最终答案最小，我们让初始人数为 $0$，那么最终答案就是整个数组的和。

### 完整代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define debug puts("#CheZiHe929")
#define Yes puts("Yes")
#define No puts("No")
const int MAXN=2e5+5;

inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
inline void print(int x){char st[105];int top=0;if(x==0)putchar('0');if(x<0)putchar('-');while(x){if(x>0)st[++top]=x%10+48;else st[++top]=-(x%10)+48;x/=10;}while(top)putchar(st[top--]);}
inline void println(int x){print(x);putchar('\n');}
inline void printsp(int x){print(x);putchar(' ');}
inline void put(int x,int i,int n){i==n?println(x):printsp(x);}

int n,a[MAXN],minn=INT_MAX,now,num,ans;

signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);

	int n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		now+=a[i];//计算前缀和
		if(minn>now)minn=std::min(minn,now),num=i;//更新最小值位置
	}
	
	if(minn<0){
		for(int i=num+1;i<=n;i++)ans+=a[i];//统计 [i+1,n] 的和
		put(ans,1,1);
	}else put(now,1,1);//即 [1,n] 的和

	return 0;
}
```

### AC 记录

[Atcoder](https://atcoder.jp/contests/abc339/submissions/49983772)

[Luogu](https://www.luogu.com.cn/record/146033367)

**THE END.**

**THANK YOU.**

---

## 作者：I_am_kunzi (赞：0)

# AT_abc339_c 题解

### 题目大意

有一辆公交车经过了 $ n $ 站，在第 $ i $ 站，车上增加了 $ a_i $ 个人（如果 $ a_i $ 为负就是减少），你需要确定一个初始的最小人数，使得公交车在行驶过程中人数一直是非负数。你需要输出这时公交车行驶过 $ n $ 站后剩余的人数。

### 题目思路

容易发现，设最小满足条件的初始人数为 $ x$，则当公交车初始的人数 $ \ge x $ 时都是满足条件的。所以我们可以二分这个最小值并模拟这个过程，最终求出的答案再模拟一次，求出最后公交车上的剩余人数，即为答案。也可以在判断时将最终的剩余人数赋值给一个变量，最终这个变量储存的值即为答案。

### 题目代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<iomanip>
#include<algorithm>
#include<set>
#include<vector>
#include<map>
#include<queue>
#include<stack>
#include<limits.h>
#include<list>
using namespace std;
long long a[200005];
int n;
bool check(long long x , long long &y) // 利用取地址符把答案赋值给 y
{
	long long nowans = x;
	for(int i = 1 ; i <= n ; i++)
	{
		nowans += a[i];
		if(nowans < 0) // 不满足条件直接退出
		{
			return 0;
		}
	}
	y = nowans;
	return 1;
}
signed main()
{
	scanf("%d" , &n);
	for(int i = 1 ; i <= n ; i++)
	{
		scanf("%lld" , &a[i]);
	}
	long long l = 0 , r = 2e14; // 2e5 * 1e9 = 2e14，这是二分的上界
	long long ans = 0;
	while(l <= r)
	{
		long long mid = l + r >> 1;
		if(check(mid , ans))
		{
			r = mid - 1;
		}
		else
		{
			l = mid + 1;
		}
	}
	printf("%lld\n" , ans);
	return 0;
}
```


---

## 作者：BugGod (赞：0)

首先我们记 $p_i$ 为在第 $i$ 站，车上的人数变化了多少。显然，$p_i=\sum_{1\le j\le i} a_j$。那么，为了使车上人数合法，我们可以求 $\operatorname{min} p_i$，这代表车上人数最少时相比于原来的情况，如果这个都 $\ge 0$，那么车上一开始 $0$ 人即可。否则取 $-\operatorname{min} p_i$ 来补齐，最后加上最终变化人数（$p_n$）即可求出最终人数。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define mp make_pair
#define fi first
#define se second
void IOS()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
void file(string file_name)
{
	freopen((file_name+".in").c_str(),"r",stdin);
	freopen((file_name+".out").c_str(),"w",stdout);
}
int n,a[200010],p[200010],ans;
signed main()
{
	//IOS();
	//file("");
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		p[i]=p[i-1]+a[i];
	}
	for(int i=1;i<=n;i++)ans=min(ans,p[i]);
	if(ans>=0)cout<<p[n];
	else cout<<-ans+p[n];
	return 0;
}
```

---

## 作者：apiad (赞：0)

问你，全程要人数非负，然而最后的人数最少。

首先，我们得维护一个 $sum$，统计此时相对于一开始已经有多少人的变化，也就是多了多少或者少了多少。

我们开一个 $ans$ 为每个时刻 $sum$ 值的最小值。

如果 $ans$ 为负数，那么代表对于一开始已经少了 $-ans$ 了。为了保证非负，所以一开始就设置为 $-ans$，若 $ans$ 非负，那么一开始 $0$ 个人也可以的。

所以答案就是，一开始的人数与最后一刻的 $sum$ 之和。

[link](https://atcoder.jp/contests/abc339/submissions/49945837)。

---

## 作者：Link_Cut_Y (赞：0)

## 简要题意

有一辆公交车，车上的人数恒非负。

有 $n$ 次上下车。每次上下车都用一个整数 $a_i$ 来表示。若 $a_i$ 是正数，表示上了 $a_i$ 个人。否则表示下了 $a_i$ 个人。

车上初始的人数不确定。你需要找到一个初始人数，使得满足车上的人数恒非负的前提下，最终的人最少。

-------------

设 $\Delta = \sum a_i$。显然 $S$ 是固定的。这表示最终人数与初始人数之差。

想要使最终人数最小，由于 $\Delta$ 恒定，只需让初始人数最小。

再设 $S = \min \limits_{i = 1}^{n} \{ \sum \limits_{j = 1}^{i} a_j\}$，即前缀和的最小值。

若 $S$ 小于 $0$，证明如果初始人数是 $0$ 的话，车上会有人数为负数的情况。这不符合题意。所以我们要让初始人数为 $|S|$ 来抵消掉这块少的人。

如果 $S$ 大于 $0$，说明车上的人一直都是非负的。只需要让初始人数为 $0$ 即可。

```cpp
const int INF = 1e18;
const int N = 200010;
int S, n, a[N], mn = INF;
signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; i ++ )
		scanf("%lld", &a[i]);
	for (int i = 1; i <= n; i ++ )
		S += a[i], mn = min(mn, S);
	if (mn < 0) S -= mn; printf("%lld", S);
	return 0;
}
```

---

