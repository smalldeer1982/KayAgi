# [ABC247E] Max Min

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc247/tasks/abc247_e

長さ $ N $ の数列 $ A\ =\ (A_1,\ A_2,\ \dots,\ A_N) $ および整数 $ X,\ Y $ があります。 次の条件をすべて満たす整数の組 $ (L,\ R) $ の個数を求めてください。

- $ 1\ \leq\ L\ \leq\ R\ \leq\ N $
- $ A_L,\ A_{L+1},\ \dots,\ A_R $ の最大値は $ X $ であり、最小値は $ Y $ である。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ Y\ \leq\ X\ \leq\ 2\ \times\ 10^5 $
- 入力される値はすべて整数である。

### Sample Explanation 1

条件を満たすのは $ (L,R)=(1,3),(1,4),(2,4),(3,4) $ の $ 4 $ 通りです。

### Sample Explanation 2

条件を満たす $ (L,R) $ は存在しません。

### Sample Explanation 3

$ X=Y $ である場合もあります。

## 样例 #1

### 输入

```
4 3 1
1 2 3 1```

### 输出

```
4```

## 样例 #2

### 输入

```
5 2 1
1 3 2 4 1```

### 输出

```
0```

## 样例 #3

### 输入

```
5 1 1
1 1 1 1 1```

### 输出

```
15```

## 样例 #4

### 输入

```
10 8 1
2 7 1 8 2 8 1 8 2 8```

### 输出

```
36```

# 题解

## 作者：FFTotoro (赞：10)

本题需要应用容斥原理。

题目要求统计 $A$ 中满足**最大值为 $X$，最小值为 $Y$** 的连续子序列的个数。

首先，如果 $A$ 中包含比 $X$ 大的元素，那么子序列肯定不能包含它，于是，它就把目前的序列分成了两个序列。

例如，$A=(21,23,3,21,7,20),X=22,Y=6$，$A$ 中的 $23$ 肯定不能被包含，于是 $A$ 就被划分成了 $(21)$ 和 $(3,21,7,20)$。

所以，对于每个分割出来的子序列（暂且称为 $B$），我们只需寻找有多少个 $B$ 的连续子序列 $C$ 既包含 $X$ 又包含 $Y$。

这是容斥原理就派上用场了：

设 $L$ 为所有子序列，$P$ 为不包含 $X$ 的所有子序列，$Q$ 为不包含 $Y$ 的所有子序列，那么答案就是 $|L|-|P|-|Q|+|P\cap Q|$。

放代码：

```cpp
#include<iostream>
#define int long long
using namespace std;
int a[200000],n;
int f(int x,int y){
	int c=0;
	for(int i=0,j=0;i<n;i++){
		if(a[i]<y||a[i]>x)j=i+1;
		c+=i-j+1;
	}
	return c;
}
signed main(){
	int x,y; cin>>n>>x>>y;
	for(int i=0;i<n;i++)cin>>a[i];
	cout<<f(x,y)-f(x-1,y)-f(x,y+1)+f(x-1,y+1)<<endl;
	return 0;
}
```

---

## 作者：沉石鱼惊旋 (赞：8)

### 题目翻译

输入一个长度为 $n$ 个数字，还有 $X$ 和 $Y$。
问数组中有几个区间最大值是 $X$ 且最小值是 $Y$。

### 题目思路

所有数字分为 $a_i>Y$，$a_i=Y$，$a_i<X$，$a_i=X$，$X<a_i<Y$ 五种情况。
$>Y$ 和 $<X$ 的位置一定不能选。
选一个区间，包含至少一个 $=Y$，包含至少一个 $=X$，问有多少种方案。
问以每个位置作为结尾，有多少个方案。
对于每个位置，找自己之前的最近的 $X$ 是多少，最近的 $Y$ 是多少，至多选多少个数字没有 $>Y$ 和 $<X$ 的情况。

### 主要代码

```cpp
void solve()
{
	int n,x,y,maxxid=0,minnid=0,la=1;
	long long ans=0;
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++)
	{
		int z;
		cin>>z;
		if(z==x)
		{
			maxxid=i;
		}
		if(z==y)
		{
			minnid=i;
		}
		if(z>x||z<y)
		{
			maxxid=0;
			minnid=0;
			la=i+1;
		}
		if(maxxid!=0&&minnid!=0)
		{
			ans+=min(maxxid,minnid)-la+1;
		}
	}
	cout<<ans<<endl;
}
```



---

## 作者：Silence_World (赞：4)

# 思路

题意很简单，注意题中说的是子串，不是序列，看到题解都写什么容斥，dp，完全没有必要啊！因为是子串，他必须连续啊！所以我们可以考虑以每一个元素作为结尾时的方案，且这个方案中每个子串都需要包含最大和最小值，我们先考虑当 $a_{i}$ $<$ $y$ 或 $a_{i}$ $>$ $x$ 时，那必然是不能选进去的，所以我们就从开头或者是它的后面选，我们就可以统计下目前到这个元素的元素值是否包含 $x$ 或 $y$，如果都包含，那说明这个元素一定能作为子串的结尾，那我们只需要统计一下前面 $x$ 和 $y$ 出现的地方距离它的最远距离，如果出现了第二个 $x$ 或 $y$ 前面那个就当成普通元素就行了。

# AC 代码

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[1000005];
signed main(){
	int n,x,y;
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int la=0;
	int max1=-1;
	int min1=-1;
	int sum=0;
	for(int i=1;i<=n+1;i++){
		if(a[i]==x){
			if(max1==-1)max1=i;
			max1=max(max1,i);
		}
		if(a[i]==y){
			if(min1==-1)min1=i;
			min1=max(min1,i);
		}
		if(a[i]<=x and a[i]>=y){
			if(max1!=-1 and min1!=-1){
				sum+=min(max1,min1)-la;
			}
		}
		else{
			max1=-1;
			min1=-1;
			la=i;
		}
	}
	cout<<sum;
}
```


---

## 作者：Unnamed114514 (赞：1)

一句话题解：因为发现最大最小可以二分，所以我们分别求出最大 $=X$ 的区间和最小 $=Y$ 的区间，然后取 $\min$ 即可。

[按照管理的要求，贴了份代码](https://atcoder.jp/contests/abc247/submissions/46271060)

---

## 作者：mi_Y13c (赞：1)

### 算法
#### (容斥原理、双指针)  $O(n)$
记  $f(y, x)$  表示满足  $y \leqslant a_{i} \leqslant x(l \leqslant i \leqslant r)$  的区间个数

根据容斥原理可知，答案 $= f(y, x)-f(y+1, x)-f(y, x-1)+f(y+1, x-1) $

对于  $f(y, x)$  ，可以通过双指针来实现，即扫描区间右端点  $r$  ，若  $a[r] \notin[y, x]$  ，则将区间 左端点  $l$  移动到  $r+1$  的位置。接着将  $r+1-l$  的值加进答案。


### 代码
```
#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (n); ++i)

using namespace std;
using ll = long long;

int main() {
    int n, x, y;
    cin >> n >> x >> y;

    vector<int> a(n);
    rep(i, n) cin >> a[i];

    auto f = [&](int y, int x) {
        ll res = 0;
        int l = 0, r = 0;
        while (r < n) {
            if (a[r] > x or a[r] < y) {
                l = r+1;
            }
            res += r+1-l;
            ++r;
        }
        return res;
    };

    ll ans = f(y, x) - f(y+1, x) - f(y, x-1) + f(y+1, x-1);
    cout << ans << '\n';

    return 0;
}
```

---

## 作者：Tsawke (赞：1)

# [ABC247E Max Min](https://www.luogu.com.cn/problem/AT_abc247_e) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.monkey-hyx.tech?t=ABC247E)

## 题面

给定数列 $ A_n $，给定 $ X, Y $，我们定义数对 $ (L, R) $ 满足 $ 1 \le L \le R \le n $，且数列 $ A_L, A_{L + 1}, \cdots, A_R $ 满足最大值为 $ X $，最小值为 $ Y $，求有多少种满足条件的数对。

## Solution

关于本题有一些较为显然的 $ O(n \log ^2 n) $ 或 $ O(n \log n) $ 或 $ O(n) $ 的做法，前两个大概对应着树套树和线段树，然后后者大概是维护前一个等于 $ X $ 等于 $ Y $，在 $ (X, Y) $ 之间的啊等等一堆东西然后跑一遍，这里就不多赘述了，网上相关做法很多。这里主要提供一个机房巨佬 @Zpair 想出来的人类智慧容斥的做法与推导。

首先我们考虑这段区间里一定不能包含在 $ (-\infty, Y) \cup (X, +\infty) $ 内的数，所以我们考虑让所有在这个区间内的数作为分割点，这样最终会让我们的序列被分成很多个子序列，这里我们不难发现，合法的区间一定不会有跨越两个子区间的，一定都是在子区间内的子子区间。

所以这时候我们只需要对于每个划分出来的子区间考虑其中的合法区间即可，不难想到我们要找的区间合法当且仅当里面包含了至少一个 $ X $ 和至少一个 $ Y $，为了方便记录这里我们令等于 $ X $ 的点为 $ 1 $，等于 $ Y $ 的点为 $ -1 $，在 $ (X, Y) $ 之间的点为 $ 0 $，也就是我们要找的就是每个子区间里包含 $ -1 $ 和 $ 1 $ 的区间由多少个。这里我们令包含 $ 1 $ 的区间的集合为 $ A $，包含 $ -1 $ 的为 $ B $，令子区间内的所有区间的集合为 $ \Omega $，不难想到我们比较好求的是，不包含 $ 1 $ 和 $ -1 $ 的区间，不包含 $ 1 $ 的区间，不包含 $ -1 $ 的区间，以及全集，分别对应着 $ \overline{A} \cap \overline{B} $，$ \overline{A} $，$ \overline{B} $，$ \Omega $。我们的目标是求出 $ A \cap B $，所以我们希望通过前面的四个求出答案，不难想到如下推导：
$$
A \cap B = \Omega - \overline{A} - \overline{B} + \overline{A} \cap \overline{B}
$$
此时考虑如何维护这四个值，显然我们可以考虑把子区间再次进行分割，遍历三次，分别由 $ 1 $ 分割，由 $ -1 $ 分割，由 $ -1 $ 或 $ 1 $ 分割，也就分别对应着式子中的三个区间的大小，然后对于每个子区间维护一遍即可，最后就是一个大常数的线性求解。

然后还有个点就是如果 $ X = Y $ 的话那么其实际上是既是 $ 1 $ 又是 $ -1 $，需要特判一下。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/extc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;
using namespace __gnu_pbds;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

template< typename T = int >
inline T read(void);

int N, X, Y;
int a[210000];
int cnt0(0), cnt1(0), cnt_1(0), l(1), r(-1);
ll ans(0);

ll GetC(int n, int m){
    if(n == 1)return 1;
    if(!n || m > n)return 0;
    ll ret(1);
    for(int i = n; i >= n - m + 1; --i)ret *= i;
    for(int i = m; i >= 1; --i)ret /= i;
    return ret + n;
}

int main(){
    N = read(), X = read(), Y = read();
    for(int i = 1; i <= N + 1; ++i){
        a[i] = i <= N ? read() : INT_MAX;
        a[i] = a[i] == X && a[i] == Y ? -114514 : (a[i] == X ? 1 : (a[i] == Y ? -1 : (Y <= a[i] && a[i] <= X ? 0 : 114514)));
        if(a[i] != 114514){r = i; continue;}
        if(!~r){l = i + 1; continue;}
        ll cur(0);
        cur += GetC(r - l + 1, 2);
        int ll(l), rr(-1);
        for(int j = l; j <= r; ++j){
            if(a[j] != -1 && a[j] != -114514){rr = j; continue;}
            if(!~rr){ll = j + 1; continue;}
            cur -= GetC(rr - ll + 1, 2);
            ll = j + 1;
        }if(ll <= rr)cur -= GetC(rr - ll + 1, 2);
        ll = l, rr = -1;
        for(int j = l; j <= r; ++j){
            if(a[j] != 1 && a[j] != -114514){rr = j; continue;}
            if(!~rr){ll = j + 1; continue;}
            cur -= GetC(rr - ll + 1, 2);
            ll = j + 1;
        }if(ll <= rr)cur -= GetC(rr - ll + 1, 2);
        ll = l, rr = -1;
        for(int j = l; j <= r; ++j){
            if(!a[j]){rr = j; continue;}
            if(!~rr){ll = j + 1; continue;}
            cur += GetC(rr - ll + 1, 2);
            ll = j + 1;
        }if(ll <= rr)cur += GetC(rr - ll + 1, 2);
        ans += cur;
        l = i + 1;
    }
    printf("%lld\n", ans);

    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    short flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

然后因为我是完全按照这个思路实现的所以上面的可能非常丑，所以这里也贴一个 @Zpair 的优美实现。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int l1,l2,l3,l4,n,x,y;ll ans;
ll get(int x){return (ll)x*(x+1)/2;}
int main(){
	cin>>n>>x>>y;int v;
	for(int i=1;i<=n;++i){
		scanf("%d",&v);
		if(v>x||v<y){ans+=get(l1)-get(l2)-get(l3)+get(l4),l1=l2=l3=l4=0;continue;}
		if(v!=x&&v!=y)l1++,l2++,l3++,l4++;
		if(v==x&&v==y)l1++,ans+=-get(l2)-get(l3)+get(l4),l2=l3=l4=0;
		if(v==x&&v!=y)l1++,l3++,ans+=-get(l2)+get(l4),l2=l4=0;
		if(v!=x&&v==y)l1++,l2++,ans+=-get(l3)+get(l4),l3=l4=0;
	}
	ans+=get(l1)-get(l2)-get(l3)+get(l4);
	cout<<ans;
}
```

## UPD

update-2022_10_24 初稿

---

