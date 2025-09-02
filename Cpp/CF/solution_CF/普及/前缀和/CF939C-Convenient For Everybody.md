# Convenient For Everybody

## 题目描述

In distant future on Earth day lasts for $ n $ hours and that's why there are $ n $ timezones. Local times in adjacent timezones differ by one hour. For describing local time, hours numbers from $ 1 $ to $ n $ are used, i.e. there is no time "0 hours", instead of it " $ n $ hours" is used. When local time in the $ 1 $ -st timezone is $ 1 $ hour, local time in the $ i $ -th timezone is $ i $ hours.

Some online programming contests platform wants to conduct a contest that lasts for an hour in such a way that its beginning coincides with beginning of some hour (in all time zones). The platform knows, that there are $ a_{i} $ people from $ i $ -th timezone who want to participate in the contest. Each person will participate if and only if the contest starts no earlier than $ s $ hours 00 minutes local time and ends not later than $ f $ hours 00 minutes local time. Values $ s $ and $ f $ are equal for all time zones. If the contest starts at $ f $ hours 00 minutes local time, the person won't participate in it.

Help platform select such an hour, that the number of people who will participate in the contest is maximum.

## 说明/提示

In the first example, it's optimal to start competition at $ 3 $ hours (in first timezone). In this case, it will be $ 1 $ hour in the second timezone and $ 2 $ hours in the third timezone. Only one person from the first timezone won't participate.

In second example only people from the third and the fourth timezones will participate.

## 样例 #1

### 输入

```
3
1 2 3
1 3
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5
1 2 3 4 1
1 3
```

### 输出

```
4
```

# 题解

## 作者：信守天下 (赞：3)

## [CF传送门](http://codeforces.com/contest/939/problem/C)
## [洛谷传送门](https://www.luogu.com.cn/problem/CF939C)
## 题目大意
某星球的一天被划分成$n$个小时，于是这个星球的世界被划分成$n$个时区，标记为$1$ ~ $n$。

一个时区的“本地时间”表示为$1$~$n$。相邻两个时区的“本地时间”间隔为$1$小时。当$1$时区的“本地时间”为$1$时，$i$时区的“本地时间”为$i$。

现在举行一场在线赛事，持续时间为$1$小时。在$i$时区，将有$a[i]$人参赛。

若赛事在“本地时间”$s$之后开始，且在“本地时间”$f$之前结束，则该时区的人将参赛，否则不参赛。

为使得这个世界的参赛人数最多，求赛事开始的最早时间
（表示为$1$时区的“本地时间”)
## 思路
设赛事开始的“标准时间”为$x$，若$i$时区参赛，则有：

①$s$ - $i$ ≤ $x$

②$f$ - $i$ ≥ $x$ + $1$

于是，参赛时区的区间为[$s$ - $x$ ~ $f$ - $x$ - $1$]

现在只需枚举$x$，并将对应区间中的参赛人数求和，即可寻找参赛人数的最大值

可以进行前缀和优化，或者滚动窗口

## $code$
~~~cpp
#include <iostream>
using namespace std;
const int kMaxN = 100001;
int a[kMaxN] , n , s , f , sum , mx , ans = -1 , l , r;
int main() {
  cin >> n;
  for (int i = 1; i <= n; i++){
    cin >> a[i % n];
  }
  cin >> s >> f;
  for (int i = s; i <= f; i++){
    sum += a[i % n];
  }
  for (int i = 0; i < n; i++) {
    l = (s - i + n) % n;
    r = (f - i + n) % n;
    sum -= a[r];
    sum += a[l];
    if (sum > mx) {
      mx = sum;
      ans = i;
    }
  }
  cout << ans + 1;
  return 0;
}
~~~

---

## 作者：helongyun (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF939C)
# 大意
来自一个时区的人只会参加开始时间不早于当地时间 $s$ 小时，结束时间不晚于当地时间 $f$ 小时的比赛。
求出可以使得参赛人数最多的时间（指开始时间）。
# 思路
一道前缀和题。
用一个数组做前缀和数组，有三种情况：
- $i≤s$，从 $s-i+1$ 到 $f-i$ 的时区都可以参加。
- $s<i<f$，从 $1$ 到 $f−i$ 和从 $s−i+1+n$ 到 $n$ 的时区都可以参加。
- $i≥f$，从 $s−i+1+n$ 到 $f−i+n$ 的时区都可以参加。
# code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,s,f,a[100005],z[100005],ans,da,v;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		z[i]=z[i-1]+a[i];//做前缀和
	}
	cin>>s>>f;
	for(int i=1;i<=n;i++)
	{
		if(i<=s) ans=z[f-i]-z[s-i];
		if(s<i&&i<f) ans=z[f-i]+z[n]-z[s-i+n];
		if(i>=f) ans=z[f-i+n]-z[s-i+n];//判断三种情况
		if(ans>v)
		{
			v=ans;
			da=i;
		}
	}
	cout<<da;
}
```

---

## 作者：封禁用户 (赞：0)

## 题目描述

[Convenient For Everybody](https://www.luogu.com.cn/problem/CF939C)

### 题意

有 $n$ 个时区。现在要举办一场持续 $1$ 小时的比赛，开始时间与某个小时的开始时间一致。在第 $i$ 时区，有 $a[i]$ 人参赛。 

来自一个时区的人只会参加开始时间不早于当地时间 $s$ 小时，结束时间不晚于当地时间 $f$ 小时的比赛。

求出可以使得参赛人数最多的时间。

## 思路

### 前缀和优化

我们可以知道这时能够参加比赛的时区只有以下几种情况：

- $i \le s$，从 $s - i + 1$ 到 $f - i$ 的时区都可以参加。

- $s < i < f$，从 $1$ 到 $f - i$ 和从 $s - i + 1 + n$ 到 $n$ 的时区都可以参加。

- $i \ge f$，从 $s - i + 1 + n$ 到 $f - i + n$ 的时区都可以参加。

此时我们就可以用前缀和优化时间复杂度。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=100010;
ll n,a[N],s,f,l,r,sum,ans,daan;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)
    {
		cin>>a[i];
		a[i]+=a[i-1];
	}
	cin>>s>>f;
	for(int i=1;i<=n;i++)
	{
		if(i<=s)
		{
			sum=a[f-i]-a[s-i];
		}
		if(s<i&&i<f)
		{
			sum=a[f-i]+a[n]-a[s-i+n];
		}
		if(i>=f)
		{
			sum=a[f-i+n]-a[s-i+n];
		}
		if(sum>ans)
		{
			ans=sum;
			daan=i;
		}
	}
	cout<<daan<<"\n";
	return 0;
}
```

---

## 作者：Caro23333 (赞：0)

#### 本蒟蒻的第一篇题解（~~而且还是道水题~~

在此不对题意做解释。
据题意，由于最后一个时区和第一个时区是连续的，所以当比赛举办者确立比赛时间在第一个时区为i时，任意一个时区j的时间为(j+i-1)%n.经过推理可以知道此时能够参加比赛的时区有如下三种情况：

i<=s 从s-i+1时区到f-i时区可以参加

s<i<f 从1到f-i时区和s-i+n+1到n时区可以参加

i>=f 从s-i+n+1时区到f-i+n时区可以参加

由于每个时区的人数是固定的，所以使用前缀和来维护人数的和。
#### 代码：  
```cpp
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>

using namespace std;
const int MAXN = 100005;
int n,s,f;
int a[MAXN],pre[MAXN];
int main()
{
    cin >> n;
    for(int i = 1; i<=n; i++)
    {
        scanf("%d",&a[i]);
        pre[i] = pre[i-1]+a[i]; //维护前缀和
    }
    cin >> s >> f;
    int ans = 0, maxa = 0;
    for(int i = 1; i<=n; i++)
    {
        int tmp;
        if(i<=s) tmp = pre[f-i]-pre[s-i]; //第一种情况
        else if(i<=f) tmp = pre[f-i]+pre[n]-pre[s-i+n]; //第二种情况
        else tmp = pre[f-i+n]-pre[s-i+n]; //第三种情况
        if(tmp>maxa)
        {
            ans = i;
            maxa = tmp;
        }
    }
    cout << ans << endl;
    return 0;
} 
```


---

