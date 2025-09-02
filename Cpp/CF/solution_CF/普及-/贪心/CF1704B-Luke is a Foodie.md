# Luke is a Foodie

## 题目描述

Luke likes to eat. There are $ n $ piles of food aligned in a straight line in front of him. The $ i $ -th pile contains $ a_i $ units of food.

Luke will walk from the $ 1 $ -st pile towards the $ n $ -th pile, and he wants to eat every pile of food without walking back. When Luke reaches the $ i $ -th pile, he can eat that pile if and only if $ |v - a_i| \leq x $ , where $ x $ is a fixed integer, and $ v $ is Luke's food affinity.

Before Luke starts to walk, he can set $ v $ to any integer. Also, for each $ i $ ( $ 1 \leq i \leq n $ ), Luke can change his food affinity to any integer before he eats the $ i $ -th pile.

Find the minimum number of changes needed to eat every pile of food.

Note that the initial choice for $ v $ is not considered as a change.

## 说明/提示

In the first test case, Luke can set $ v $ to $ 5 $ before he starts to walk. And he can walk straight to eat every piles of food without changing $ v $ .

In the second test case, Luke can set $ v $ to $ 3 $ before he starts to walk. And he could change $ v $ to $ 10 $ before he eats the second pile. After that, he can walk straight to eat remaining food without changing $ v $ .

In the fourth test case, Luke can set $ v $ to $ 3 $ before he starts to walk. And he could change $ v $ to $ 8 $ before he eats the sixth pile. After that, he can walk straight to eat remaining food without changing $ v $ .

In the fifth test case, Luke can set $ v $ to $ 4 $ before he starts to walk. And he could change $ v $ to $ 6 $ before he eats the fourth pile. Then he could change $ v $ to $ 12 $ before he eats the seventh pile. After that, he can walk straight to eat remaining food without changing $ v $ .

## 样例 #1

### 输入

```
7
5 3
3 8 5 6 7
5 3
3 10 9 8 7
12 8
25 3 3 17 8 6 1 16 15 25 17 23
10 2
1 2 3 4 5 6 7 8 9 10
8 2
2 4 6 8 6 4 12 14
8 2
2 7 8 9 6 13 21 28
15 5
11 4 13 23 7 10 5 21 20 11 17 5 29 16 11```

### 输出

```
0
1
2
1
2
4
6```

# 题解

## 作者：Andrewzdm (赞：7)

本题和 [CF1304C Air Conditioner](https://www.luogu.com.cn/problem/CF1304C) 的思想比较相似，不妨在切完本题后去切一下这题。

把题意抽象并且形象化一下，就是说，有一个区间 $[v-x, v+x]$ 可以通过改变 $v$ 的值移来移去，我们要尽可能地把 $a_i$ 框进去。

为了把 $a_1$ 框进去，$v$ 的范围为 $[a_1-x, a_1+x]$；  
在不考虑 $a_1$ 的情况下，为了把 $a_2$ 框进去，$v$ 的范围为 $[a_2-x,a_2+x]$。  
那么如果这两个限制区间有交集，我们就可以通过调整 $v$ 的初始值把 $a_1, a_2$ 一次性框进去，$v$ 的范围就是这两个区间的交集；  
如果这两个限制区间没有交集，那么就必须改变 $v$ 的值，$ans$ 增加 $1$，总的限制区间设置为 $[a_2-x,a_2+x]$。  
此后类似。

总结一下思路：计算把 $a_1,a_2,\cdots,a_k$ 都框进去的 $v$ 的限制区间 $[L,R]$。对其后的 $a_{k+1}$，若 $[a_{k+1}-x,a_{k+1}+x]$ 与 $[L,R]$ 有交集，那么就调整 $L$ 和 $R$；若没有交集，那么 `ans++`，$[L,R]$ 设为 $[a_{k+1}-x,a_{k+1}+x]$。

代码如下，时间复杂度 $O(n)$。
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;
int n;
ll a[maxn], x;
inline int read();

void work()
{
    n = read();
    x = read();
    for(int i = 1; i <= n; ++i) a[i] = read();
    ll L, R; int ans = 0;
    L = a[1] - x; R = a[1] + x;
    for(int i = 2; i <= n; ++i)
    {
        ll l = a[i] - x, r = a[i] + x;
        if(r < L || l > R)
        {
            ans++;
            L = l; R = r;
            continue;
        }
        L = max(L, l);
        R = min(R, r);
    }
    printf("%d\n", ans);
    return;
}

int main()
{
    int T;
    cin >> T;
    while(T--) work();
    return 0;
}

inline int read()
{
    int x = 0; bool f = true; char ch = getchar();
    while(!isdigit(ch)) { if(ch == '-') f = false; ch = getchar(); }
    while(isdigit(ch)) { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
    return f ? x : -x;
}
```

---

## 作者：luo_shen (赞：2)

**题意**  
给定 $n$ 个数，第 $i$ 个数为 $a_i$ 。给定一个范围值 $x$，可以在每次操作前给数 $v$ 赋值，使得对于每一个 $i$，都有 ${a_i-x} \le v \le {a_i+x}$，求给数 $v$ 赋值的最小次数 $sum$，并输出 $sum-1$。  
**分析**  
对于这题肯定不能直接枚举每次 $v$ 的赋值，因为最多会有 $2·10^5$ 次操作，一一枚举会导致时间复杂度炸裂。所以可以处理出 $v$ 的取值范围。令 $mn$ 为上一次赋值开始的 $a_i$ 最小值，$mx$ 为上一次赋值开始的 $a_i$ 最大值。因为对于两次赋值之间的任意 $a_i$ 满足 ${a_i-x} \le v \le {a_i+x}$ ，所以同样也会满足 ${mx-x} \le v \le {mn+x}$，即满足 $mx-mn \le 2x$。  
**代码**
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,x;
int read(){
    int s=0,f=1;
    char ch=getchar();
    while(ch>'9'||ch<'0'){
        if(ch=='-'){
            f=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        s=s*10+(ch-'0');
        ch=getchar();
    }
    return s*f;
}
int main(){
    t=read();
    while(t--){
        n=read(),x=read();
        int mn,mx,now,ans=0;
        mx=mn=read();//初始赋值，并维护范围，且该次不计入总赋值次数
        for(int i=1;i<n;i++){
            now=read();
            mx=max(mx,now);//维护到上一次赋值时a[i]的最大值
            mn=min(mn,now);//维护到上一次赋值时a[i]的最小值
            if(mx-mn>2*x){
                mx=mn=now;
                ans++;
            }//若不满足条件，计数，并重新开始维护
        }
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：xzy090626 (赞：1)

# CF1704B 题解
## 题意（简化）
有 $n$ 个数、一个常数 $x$ 和一个值 $v$，一开始你可以设 $v$ 为任何非负整数。从头到尾遍历这 $n$ 个数（不能回头），如果 $|v-a_i|>x$，那么你需要修改 $v$ 使得上式不成立。最后，你需要输出修改 $v$ 的最少次数（一开始设置 $v$ 时，我们不认为这是修改）。

多测，$1\le n\le2\cdot10^5$，$1\le t\le 10^4$，$1\le x \le 10^9$。
## 分析
一开始看到这题时，我们可能会以为重点在 $v$ 的值上面。然而实际上，我们无法通过较小复杂度决定它的值。

那么我们可以考虑绕开这个问题。

注意到要使得当前的 $v$ 合法，必须使 $a_i-x \le v \le a_i+x$。

显然我们得到了合法的 $v$ 值的区间。容易发现，其实 $v$ 的具体值不重要，只要所有的 $a_i$ 可以让 $v$ 合法即可。

考虑维护当前区间的最值，遍历时每次根据 $a_i$ 更新最值。

如果最值不在当前合法区间内，那么修改 $v$ 的值，并将答案加一。其实也不用真的去改，仍然可以重新维护最值区间。

最后输出答案即可。

---

## 作者：yinhy09 (赞：1)

## 思路讲解：

这个题主要是读题难度...

这里直接上翻译后的：希望分成若干段，每一段绝对差（最大减最小）小于等于 $2x$（这样就能找到一个数满足所有数与他的差的绝对值 $\le x$）。既然我们希望最小，就从头到尾 $O(n)$ 扫一遍，记录 $\max,\min$，不满足 $\max-\min \le 2 x$ 就新开一段。

## AC Code：

```cpp
// Problem: B. Luke is a foodie
// Contest: CodeTON Round 2 (Div. 1 + Div. 2, Rated, Prizes!)
// URL: https://codeforces.com/contest/1704/problem/B
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// Author: Luogu-yinhy09(575320),Codeforces-yinhy09
 
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
ll read()
{
	char c;
	ll x=0;
	ll f=1;
	c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')f*=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
ll T,n,x;
const int maxn=2e5+5;
ll a[maxn];
ll minn=9e18,maxx=-9e18;
void init()
{
	minn=9e18,maxx=-9e18;
}
ll ans=0;
int main()
{
	T=read();
	while(T--)
	{
		init();
		ans=0;
		n=read(),x=read();
		for(int i=1;i<=n;i++)a[i]=read();
		for(int i=1;i<=n;i++)
		{
			if(a[i]<minn)minn=a[i];
			if(a[i]>maxx)maxx=a[i];
			if(maxx-minn>2*x)
			{
				ans++;
				maxx=minn=a[i];
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

谢谢观看

---

## 作者：0xFF (赞：1)

#### 题目大意


------------
有一个长度为 $n$ 的序列 $a$，初始有一个 $v$，给定一个 $x$，如果 $|a_i - v| > x$ 就需要改变 $v$ 的值，输出最少需要的更改次数。

#### 思路分析


------------
如果从一到第 $i$ 个位置这段区间内的最大值减去最小值大于 $2x$，那么无论 $v$ 取何值都必然改变大小，故只需记录到 $i$ 位置的最大值和最小值的差，更新答案即可。

#### 代码实现


------------
```cpp
int main(){
	int T = read();
	while(T--){
		int n = read() , x = read();
		for(int i=1;i<=n;i++){
			a[i] = read();
		}
		mn = INF;
		mx = ans = 0;
		for(int i=1;i<=n;i++){
			mn = min(mn,a[i]);
			mx = max(mx,a[i]);
			if(mx - mn > 2*x){
				ans++;
				mx = mn = a[i];
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：cachejtt (赞：1)

## 题意
你有一个序列 $a$，和一个数 $x$，找到一个 $v$ 使得它能覆盖 $a_l,a_{l+1},\dots ,a_r$。覆盖的条件是 $|v-a_i|\le x$ 问你要覆盖整个序列最少需要更换几次 $v$？

## 思路
### 性质
考虑当什么时候我们需要更换 $v$。设目前最大值为 $max$ 最小值为 $min$，显然当 $max-min > 2\times x$ 时，我们需要更换下一个 $v$。

### 实现
每次更新 $max$ 与 $min$ 当需要更换 $v$ 时，计数器加一即可。

## 代码
```cpp
#include<bits/stdc++,h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define nrep(i, a, b) for (int i = (a); i >= (b); --i)
#define ll long long
#define endl "\n"
#define int ll
using namespace std;
int t,n,x,mx,mn,a[200005],cnt; 
signed main(){
  ios::sync_with_stdio(0);
  cin>>t;
  rep(kk,1,t){
    cin>>n>>x;
    cnt=0;
    rep(i,1,n)cin>>a[i];
    mn=a[1];
    mx=a[1];
    rep(i,1,n){
      if(max(mx,a[i])-min(mn,a[i]) <= 2*x){
        mn=min(a[i],mn);
        mx=max(a[i],mx);
      }
      else{
        mn=a[i];
        mx=a[i];
        cnt++;
      }
    }
    cout<<cnt<<endl;
  }
  return 0;
}
```

---

