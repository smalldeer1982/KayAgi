# Assembly via Remainders

## 题目描述

You are given an array $ x_2,x_3,\dots,x_n $ . Your task is to find any array $ a_1,\dots,a_n $ , where:

- $ 1\le a_i\le 10^9 $ for all $ 1\le i\le n $ .
- $ x_i=a_i \bmod a_{i-1} $ for all $ 2\le i\le n $ .

Here $ c\bmod d $ denotes the remainder of the division of the integer $ c $ by the integer $ d $ . For example $ 5 \bmod 2 = 1 $ , $ 72 \bmod 3 = 0 $ , $ 143 \bmod 14 = 3 $ .

Note that if there is more than one $ a $ which satisfies the statement, you are allowed to find any.

## 说明/提示

In the first test case $ a=[3,5,4,9] $ satisfies the conditions, because:

- $ a_2\bmod a_1=5\bmod 3=2=x_2 $ ;
- $ a_3\bmod a_2=4\bmod 5=4=x_3 $ ;
- $ a_4\bmod a_3=9\bmod 4=1=x_4 $ ;

## 样例 #1

### 输入

```
5
4
2 4 1
3
1 1
6
4 2 5 1 2
2
500
3
1 5```

### 输出

```
3 5 4 9
2 5 11
5 14 16 5 11 24
501 500
2 7 5```

# 题解

## 作者：lihongqian__int128 (赞：7)

# CF1968C Assembly via Remainders题解
构造题。

我们发现，当 $a_{i-1}$ 足够大时，其实只要满足 $a_i=a_{i-1}+x_i$ 就行了。

令 $a_1=501$，$a_i=a_{i-1}+x_i(2\le i\le n)$，则 $\begin{aligned}a_i\equiv a_{i-1}+x_i\equiv x_i\end{aligned}\pmod {a_i}$，满足条件。

另外，$a$ 数组的最大值 $a_n=501+\sum \limits _{i=2}^{n} x_i \le 10^9$，满足条件。

```cpp
#include <bits/stdc++.h>
using namespace std ;
int t , n , x ;
int main()
{
    cin >> t ;
    while(t--)
    {
        cin >> n ;
        n-- ;
        int a = 501 ;
        cout << a << ' ' ;
        while(n--)
        {
            cin >> x ;
            a += x ;
            cout << a << ' ' ;
        }
        cout << '\n' ;
    }
    return 0 ;
}
```

---

## 作者：Pursuewind (赞：4)

简单题赛时都写了 36 分钟，菜。

## 题意简述

给你 $n$，以及 $x_2,x_3,\dots,x_n$，请你构造一个长度为 $n$ 的数组 $a$，满足：

- 对于任意的 $1 \le i \le n$，有 $1 \le a_i \le 10^9$。
- 对于任意的 $2 \le i \le n$，有 $a_i \bmod a_{i-1}=x_i$。

## 做法

先不考虑第一条限制，我们来看第二条限制。

> 对于任意的 $2 \le i \le n$，有 $a_i \bmod a_{i-1}=x_i$。

思考一下，要想使 $a_i \bmod a_{i-1}=x_i$，在已经知道 $a_{i-1}$ 的前提下，如何构造出 $a_{i}$？

没错，你一定想到了。使 $a_i=a_{i-1}+x_i$ 即可，因为：

$$(a_{i-1}+x_i) \bmod a_{i-1}=x_{i}$$

初始条件是 $a_1=x_1+1$。

再想一想，这种情况下可以满足限制一吗？

显然可以，因为 $a_n$ 最大，而 

$$a_n=x_1 + 1 + \sum\limits_{i=2}^n x_i$$

$a_n$ 的数量级别在 $nx_i$，最大也就 $500 \times 500=2.5 \times 10^5$，远远小于 $10^9$。

附赛时代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 505;
int n, x[N];
void solve() {
  cin >> n;
  for (int i = 2; i <= n; i++) {
      cin >> x[i];
  }
  int a = 501;
  cout << a;
  for (int i = 2; i <= n; i++) {
      a += x[i];
      cout << ' ' << a;
  }
  cout << '\n';
}
int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
```

---

## 作者：nuc_x (赞：3)

## 题意：
给定一个整数 $n$ 和 $n-1$ 个数 $x_2, x_3, \ldots, x_n$，我们需要构造一个序列 $a_1, a_2, \ldots, a_n$，使得 $x_2 = a_2 \mod a_1, x_3 = a_3 \mod a_2, \ldots, x_n = a_n \mod a_{n-1}$。


## 思路：

构造方式如下：

1. 令 $a_1 = x_2 + 1$。

2. 对于 $i = 2, 3, \ldots, n$，构造 $a_i$：
   - 如果 $a_{i-1} > x_i$ 且 $x_i > x_{i+1}$（注意 $x_{n+1}$ 不存在，所以最后一项 $x_n$ 无需检查），则可以直接令 $a_i = x_i$。
   - 否则，从 $k = 1$ 开始递增地选择 $k$，直到找到一个 $k$ 使得 $a_i = k \cdot a_{i-1} + x_i > x_{i+1}$。一旦找到这样的 $k$，即令 $a_i = k \cdot a_{i-1} + x_i$。

按照这种方式，我们可以确保 $a_i > x_{i+1}$，从而满足 $x_{i+1} = a_{i+1} \mod a_i$ 的条件。

注意：在实际编程实现时，可能需要考虑整数溢出的问题，特别是在选择 $k$ 的过程中。如果 $a_{i-1}$ 和 $x_i$ 都很大，那么 $k$ 可能需要选择一个相对较小的值来避免溢出。如果 $k$ 过大导致溢出，可以考虑从 $k = 1$ 开始递减地选择 $k$，直到找到一个合适的 $k$。
## 代码：
```c++
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+10;
typedef long long ll;
ll n;
ll x[N],a[N];
void solve()
{
    cin>>n;
    for(int i=2;i<=n;i++)cin>>x[i];
    a[1]=x[2]+1;
    for(int i=2;i<=n;i++)
    {
        if(a[i-1]>x[i]&&x[i]>x[i+1])a[i]=x[i];
        else 
        {
            int k=1;
            while(k*a[i-1]+x[i]<=x[i+1])k++;
            a[i]=a[i-1]*k+x[i];
        }
    }
    for(int i=1;i<=n;i++)cout<<a[i]<<' ';
    cout<<endl;
}
int main()
{
    int T;
    cin>>T;
    while(T--)
    {
       solve();
    }
    return 0;
}
```

---

## 作者：junee (赞：3)

# CF1968C 题解

## 题目分析

本题比较抽象。我们发现 $1 \le x_i \le 500$，而 $1 \le a_i \le 10^9 $,所以如果当 $a_i$ 足够大时，我们可以发现 $ x_i=a_i \bmod a_{i-1} $ 其实就是要满足 $ a_i=x_i + a_{i-1}$。

所以我们令 $a_1 = 501$，然后依次更新就可以了。

## Code

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
typedef long long LL;
const int N=2e5+10;
int a,n,T; 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin>>T;
	while(T--{
		LL x=501;
		cin>>n;
		cout<<x<<" ";
		for(int i=1;i<n;i++){
			cin>>a;
			cout<<(x += a)<< " "; 
		}
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：JuRuoOIer (赞：2)

# 题解 CF1968C - Assembly via Remainders

前排提示：本题为 **结论题**。

### 题意

已提交翻译。

给定长度为 $n-1$ 的数组 $x_2,x_3,\dots,x_n$，要求构造一个长度为 $n$ 的数组 $a$，使得：
- $\forall 1\le i \le n$，$1 \le a_i \le 10^9$；
- $\forall 2\le i \le n$，$x_i=a_i\bmod a_{i-1}$。

数据范围：$2 \le n \le 500,1 \le x_i \le 500,\sum n \le 2\times10^5$。

### 做法

注意到 $x_i \le 500$，直接令 $a_1=501$，后面每个 $a_i$ 均为 $a_{i-1}+x_i$ 即可。这样 $a_i$ 最大不会超过 $500 \times 500 = 25000$。时间复杂度 $O(n)$。

```cpp
ll t,n,a,x;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		n--;
		a=501;
		cout<<a;
		while(n--){
			cin>>x;
			a+=x;
			cout<<' '<<a;
		}
		cout<<endl;
	}
	return 0;
}

```

---

## 作者：旻偲 (赞：2)

## 题号 ：CF1968C
### 做法：

若有 $a_i \bmod a_{i-1}$ $=$ $x_i$，即 $a_i$ = $k\times a_{i-1} + x_i = a_i$。  
若令 $k = 1$，得到 $a_i$ =  $a_{i-1} + x_i$，那么我们就得到了我们所求 序列 $a$ 的递推公式。

得到递推公式之后，联系样例，很容易就可以想到令 $a_1 = x_1 + 1$ ，然后得到整个序列，然后……

恭喜你挂在第五个样例上 （自行模拟）。那么我们就发现，递推公式是有条件的。

若想使得 $a_i = a_{i-1} + x_i$ 且 $a_i$ $\bmod$ $a_{i-1} = x_i$，   
则需满足 $a_{i-1} > a_i - a_{i-1} = x_i$。

**反证法：如果 $a_{i-1} \leq x_i$，那么 $a_i$ $\bmod$ $a_{i-1}$ $< x_i$，故余数不可能为 $x_i$ ，与题设不符，所以 $a_{i-1} > a_i - a_{i-1} = x_i$。**

又注意到数据范围 $x_i \leq 500$，那只要使得 $a_i > 500$ 即可。

所以令 $a_1 = 501$，联系递推公式 $a_i$ = $a_{i-1} + x_i$，便能求出所需的 $a$ 序列。

~~总结：纯纯诈骗题，我坐牢半天~~

---

## 作者：AK_400 (赞：2)

# [CF1968C](https://codeforces.com/contest/1968/problem/C) 题解
我们发现 $x>y$ 时 $ (x+y) \bmod x=y$。

于是我们令 
$$
a_i= \begin{cases} \max_{j=2}^{n}x_j+1 & i=1 \\ a_{i-1}+x_i & i\in[2,n]\end{cases}
$$
即可。
# CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[1000],mx;
int main(){
    ios::sync_with_stdio(0);
    cin>>t;
    while(t--){
        cin>>n;
        mx=0;
        for(int i=1;i<n;i++){
            cin>>a[i];
            mx=max(a[i],mx);
        }
        mx++;
        cout<<mx<<" ";
        for(int i=1;i<n;i++){
            mx+=a[i];
            cout<<mx<<" ";
        }
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：lailai0916 (赞：1)

## 原题链接

- [洛谷 CF1968C Assembly via Remainders](https://www.luogu.com.cn/problem/CF1968C)

## 题意简述

给定长度为 $n-1$ 的数列 $x_i$，构造长度为 $n$ 的数列 $a_i$，满足 $x_i=a_i \bmod a_{i-1}$。

## 解题思路

令 $a_i=a_{i-1}+x_i$，此时：

$$
\begin{aligned}
x_i &= a_i \bmod a_{i-1} \\
  &= (a_{i-1}+x_i) \bmod a_{i-1} \\
  &= a_{i-1} \bmod a_{i-1} + x_i \bmod a_{i-1} \\
  &= x_i \bmod a_{i-1}
\end{aligned}
$$

不难发现，当 $a_{i-1}$ 较大时即可满足条件。

由于 $x_i \le 500$，$a_i \le 10^9$，所以不妨令 $a_1$ 为一个较大的数。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll=long long;
const int inf=0x3f3f3f3f;
const int mod=1e9+7;
const int N=200005;
int x[N],a[N];
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int n;
		cin>>n;
		for(int i=2;i<=n;i++)
		{
			cin>>x[i];
		}
		a[1]=114514;
		for(int i=2;i<=n;i++)
		{
			a[i]=a[i-1]+x[i];
		}
		for(int i=1;i<=n;i++)
		{
			cout<<a[i]<<' ';
		}
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：keep_shining (赞：1)

## 题意：
给你一个 $n$ 和 $x$ 数组，让你构造一个长度为 $n$ 的序列 $a$，它需要满足以下两条限制：

- $a$ 序列中所有的数都要小于等于 $10^9$。
- 对于所有的 $1\le i \le n$，$x_i=a_i \bmod a_{i-1}$。

## 思路：
我们一条限制一条限制的来看，但由于限制一目前对我们没用，所以先看限制二。
> 对于任意的 $2 \le i \le n$，$a_i \bmod a_{i-1} = x_i$。

那~~浅浅的~~想一下，当我们知道了 $a_{i-1}$，我们怎么求出 $a_i$呢？

答案是 $a_i=a_{i-1}+x_i$，为什么呢？

因为 $(a_{i-1}+x_i) \bmod a_{i-1} =x_i$，于是，我们得出了 当 $2\le i \le n$ 时 $a_i$ 的公式，那 $a_1$ 等于什么呢？

我们让他等于 $501$ 就可以了，因为我们要让 $a_1$ 大于 $x$ 的最大值，这样就不会 $a_i \div a_{i-1} \ge2$ 的情况，如果他们的商 $\ge2$，就可能会导致余数相同的情况。

我们来算一下是否符合限制一，$a$ 数组的最大值是 $n\times maxx$，其中 $maxx$ 是 $x$ 中的最大值，所以最大值是 $500\times 500=250000$，不超 $10^9$，所以满足要求。

## AC code:
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+5;
int n,x[N],t;
void solve()
{
    cin>>n;
    for(int i=2;i<=n;i++)cin>>x[i];
    int a=501;//a1
    cout<<501;
    for(int i=2;i<=n;i++)
    {
        a+=x[i];//每次加上x[i]
        cout<<' '<<a;//输出
    }
    cout<<'\n';
}
int main()
{
    ios::sync_with_stdio(0);
    cin>>t;
    while(t--)solve();
    return 0;
}
```

---

## 作者：RainCQwQ (赞：0)

# CF1968C Solution
## 思路整理
可见题目要求我们构造一个数组 $a$ 满足：

- 对于 $a$ 数组中的每一个数，要求 $1 \le a_i \le 10^9$；
- 对于 $2 \le i \le n$，要求 $a_i \bmod a_{i-1} = x_i$。

主要观察条件 2。发现本条件是可以被轻易构造出来的，对于每一个 $2 \le i \le n$，都可以构造：

$$a_i = a_{i-1} + x_i$$

接着 $a_1 = 501$ 即可，因为我们不能让 $\frac{a_i}{a_{i-1}
} \ge 2$，以至于余数大于除数（这样会使余数变成余数取模与除数，而商增加余数除以除数）。

由此可得代码：

## Code
```cpp
#include <iostream>
using namespace std;
#define MAXN 505
int x[505],a[505];
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        for(int i=1;i<n;i++) cin>>x[i];
        for(int i=1;i<=n;i++)
        {
            if(i==1) a[i]=501;
            else a[i]=a[i-1]+x[i-1];
        }
        for(int i=1;i<=n;i++) cout<<a[i]<<" ";
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：Dream_Mr_li (赞：0)

## Solution

我们可以想到，如果 $a>b$，并且 $a \div b < 2$，那么 $a \bmod b = a-b$。根据这个特性，我们就可以知道题目解法。

但是，我们的 $a_1$ 必须要大于 $500$（$x_i$ 的边界），这样才不会出现 $a_i \div a_{i-1} \ge 2$ 的情况。

## Code

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=510;
int t,n,a[N],x[N];
void solve(){
	cin>>n;
	for(int i=2;i<=n;i++){
		cin>>a[i];
	}
	x[1]=N;
	cout<<x[1]<<" ";
	for(int i=2;i<=n;i++){
		x[i]=x[i-1]+a[i];
		cout<<x[i]<<" ";
	}
	cout<<endl;
}
signed main(){
	cin>>t;
	while(t--){
		solve(); 
	}
	return 0;
} 
```

---

## 作者：RSDL (赞：0)

很水很水的一道题，重要在第二条件 $x_i=a_i\bmod a_{i-1}$ ，怎么构造呢？  
我们先看一个公式： $x \bmod y = (x-y)\bmod y$ （这里设 $x>y$ )，那么可以用第二条件替换一下： $x_i=(a_i-a_{i-1}) \bmod a_i$ ，那么当 $a_i>x_i$ 时 $x_i=a_i-a_{i-1}$ ，那么此题现在就非常好办了！
# code
```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin>>n;
    while(n--)
    {
        int a,x[10000010];
        long long sum=114514;
        cin>>a;
        cout <<"114514 ";
        for(int i = 1;i<=a-1;i++)
        {
            cin>>x[i];
            sum+=x[i];
            cout <<sum<<" ";
        }
        cout <<endl;
    }
	return 0;
}
```

---

## 作者：mc_xiexie (赞：0)

# CF1968C Assembly via Remainders
## 题意简述

给定长度为 $n-1$ 的数组 $x_2,x_3,\dots,x_n$，要求构造一个长度为 $n$ 的数组 $a$，使得：
- $ 1\le i \le n$，$1 \le a_i \le 10^9$；
- $ 2\le i \le n$，$x_i=a_i\bmod a_{i-1}$。

数据范围：$2 \le n \le 500,1 \le x_i \le 500,\sum n \le 2\times10^5$。

## 思路
$((a+b) \bmod a)=b$，当 $0 \le b < a$ 时。所以我们可以尝试生成一个 $b=x_i$ 的序列。

我们可以取 $a_i$ 为 $a_i - 1+x_i$，因为 $((a_i - 1+x_i) \bmod a_i - 1)=x_i$ 成立。

$a$ 的最大值最多为 $1000+500n$，$\sum n \le 2\times10^5$,$1000+500n$ 小于 $10^9$,所以不用开 $\text{long long}$。
## 完整代码

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;//t为数据数
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		int sum=10000;
        cout<<sum<<" ";
		for(int i=2;i<=n;i++){
			int x;
			cin>>x;
			sum+=x;
			cout<<sum<<" ";
		}
		cout<<"\n";
	}
}
```

---

## 作者：Suboil (赞：0)

## 题意

提供N个数组成的数组 $a[N]$、构造新的数组 $b[N]$

满足 $b[i] \% b[i - 1] = a[i - 1]$


## 思路

结合案例给出的一组数据
```
3
1 5
```

这一组数据阐述解决了潜在的问题。

为了避免 $(a[1] + b[1]) \% a[1] == 0$ 我们需要使 $b[1] = a[1] + 1$ (看完后面看这个可能很好理解)。


回到正题、根据样例数据我们可以得到一张表如下：
```
1 5 题目提供的数组
2 3 构建的新数组
```

我们会发现 $b[2]$ 位置我们并不能使用3，因为3比5小我们在构建第三位的时候正常来说填写8，但是8%3结果是2并不是我们想要的5，所以说我们尽可能的将每一个数字进行放大直到大于下一位位置。

特殊情况下获取下一位值：

$(a[i] / b[i - 1] + 1) * b[i - 1] + a[i - 1]$

正常情况下：

$b[i] = b[i - 1] + a[i - 1]$


## 代码

[Submission](https://codeforces.com/contest/1968/submission/260143616)


```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long 
#define str string
#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define init(a) memset(a,0,sizeof(a))


const int N = 510;
int a[N],b[N];
void solve() {
    init(a),init(b);
    int n; cin >> n;
    for(int i = 1;i < n;i++) cin >> a[i];

    b[1] = a[1] + 1;
    
    for(int i = 2;i <= n;i++) {
        int t = a[i - 1] + b[i - 1];
        
        if(t <= a[i]) b[i] = (a[i] / b[i - 1] + 1) * b[i - 1] + a[i - 1];
        else b[i] = b[i - 1] + a[i - 1];
    }

    for(int i = 1;i <= n;i++) cout << b[i] << " ";
    cout << '\n';
}

signed main() {
    // freopen("input.txt","r",stdin);
    fst;
    int t; cin >> t;
    while(t--) solve();
    // solve();

    
    return 0;
}

```

---

## 作者：vectorxyz (赞：0)

基础的构造题。

#### 题目分析
可以发现构造的 $a_i$ 不大于 $10^9$，而所有 $x_i$ 的和不会超过 $500 \times 500 = 250000$，所以可以让 $a_n$ 为 $10^9$，然后 $a_{n - 1}$ 就是 $10^9$ 减去 $a_{n - 1}$，以此类推，可以保证条件成立。

拿样例说明一下吧，比如 $2$ 和 $4$ 和 $1$，不难构造 $10^9-7$ 和 $10^9-5$ 和 $10^9-1$ 和 $10^9$。不难证明这是对的。

#### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
 
const int N = 505;
int a[N], x[N];
void work()
{
    memset(a, 0, sizeof(a));
    memset(x, 0, sizeof(x));
    int n;
    cin >> n;
 
    for(int i = 1;i < n;i ++ ){
        cin >> x[i];
    }
    int ans = 1000000000;
    a[n] = ans;
    for(int i = n - 1;i >= 1;i -- ){
        ans -= x[i];
        a[i] = ans; 
    }
    for(int i = 1;i <= n;i ++ ) cout << a[i] << ' ';
    puts("");
}
 
signed main()
{
    int T;
    cin >> T;
    while(T -- )
    {
        work();
    }
    return 0;
}
```

[比赛记录](https://codeforces.com/contest/1968/submission/259175766)。

---

## 作者：DrAlfred (赞：0)

摘要：数论，构造

[传送门：https://www.luogu.com.cn/problem/CF1968C](https://www.luogu.com.cn/problem/CF1968C)

## 题意

给定一个数列 $x_2, x_3, \cdots, x_n$，试构造一个数列 $a_1, a_2, \cdots, a_n$，使得 $\forall i \in [2, n]$，$x_i = a_i \bmod a_{i-1}$。

## 分析思路

因为需要 $1 \leq a_i \leq 10^9$，所以我们希望 $a_i$ 尽可能小。

由于 $x_i = a_i \bmod a_{i-1}$，一种可行的构造即为 $x_i = a_i - a_{i - 1}$，也就是 $a_i = x_i + a_{i - 1}$。

由于 $1 \leq x_i, n \leq 500$，于是我们任意设置一个大于 $500$ 的 $a_1$，然后按照上述递推式即可得出一组合法构造。

时间复杂度 $O\left(n\right)$，可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 510;
using i64 = long long;
i64 t = 1, n, x[N];
inline void solve(void) {
    cin >> n;
    int cur = 1000;
    cout << cur << ' ';
    for (int i = 1; i < n; i++) {
        cin >> x[i];
        cout << (cur += x[i]) << ' ';
    }
    cout << '\n';
}
inline void optimizeIO(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
}
int main(int argc, char const *argv[]) {
    optimizeIO(), cin >> t;
    while (t--) solve();
    return 0;
}

```

---

## 作者：jess1ca1o0g3 (赞：0)

[Portal(CF)](http://codeforces.com/problemset/problem/1968/C)

[Portal(Luogu)](https://www.luogu.com.cn/problem/CF1968C)

## 思路

简单构造题。

通过观察发现 $a_1=x_1+1$。

然后又要求 $a_i\bmod a_{i-1}=x_i$。

我最开始以为设一个 $k=x_1+1$，然后 $a_i=k+x_i$ 就好了。

但是这样会导致 $k<x_{i+1}$，就不对了。因为余数不可能大于除数。

可以让 $k$ 一直增加直到大于 $x_i+1$，这样就好了。

## Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define YES cout<<"Yes"<<endl
#define NO cout<<"No"<<endl
#define f(a,b,c) for(int i=a;i<=b;i+=c)
#define wh(a) while(a)
#define ioyh ios::sync_with_stdio(0)
#define bk break
#define con continue
#define uns using namespace std
#define rt return
uns;
int t,n,a[505];
signed main(){
	ioyh;
	cin>>t;
	wh(t--){
		cin>>n;
		f(1,n-1,1) cin>>a[i];
		cout<<a[1]+1<<" ";
		int k=a[1]+1;
		f(2,n,1){
			int p=k;
			wh(k<=a[i]) k+=p;
			cout<<k+a[i-1]<<" ";
			k+=a[i-1];
		}
		cout<<endl;
	}
	rt 0;
}
```

---

## 作者：Special_Tony (赞：0)

# 思路
首先 $a_1$ 只要比 $x_1$ 大就行，例如 $114514$ 就一定合法（因为 $x_i\le500$）。后面的 $a_i$ 不仅要满足 $a_i>x_i$，还要满足 $a_i\bmod a_{i-1}=x_{i-1}$。但 $a_i$ 的范围要求很大，足足有 $10^9$，所以只要随便构造一个就好。这里我用的是保守的方法，就是用 $\lfloor\frac{x_i+a_{i-1}-x_{i-1}}{a_{i-1}}\rfloor\times a_{i-1}+x_{i-1}$ 来得出一个最小的 $a_i$ 使得 $a_i>x_i$ 且 $a_i\bmod a_{i-1}=x_i$。当然也有二分等许多方法，我这里就不详细说明了。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int t, n, a[200005], lst;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n;
		for (int i = 1; i < n; ++ i)
			cin >> a[i];
		a[n] = 0;
		cout << (lst = a[1] + 1);
		for (int i = 1; i < n; ++ i) {
			lst = (a[i + 1] + lst - a[i]) / lst * lst + a[i];
			cout << ' ' << lst;
		}
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：minVan (赞：0)

**题目大意**

给定 $x_2,x_3,\cdots,x_n$，求序列 $a_1,a_2,\cdots,a_n$，使得 $x_i=a_i\bmod a_{i-1}$。

**解题思路**

注意 $\bmod$ 的性质，因为 $x_i=a_i\bmod a_{i-1}$，所以 $x_i<a_{i-1}$，这就是本题的关键。

于是我们令 $a_1=x_2+1$ 来使得 $x_2<a_1$，然后对于 $a_i$（$i\in[2,n )$），都需要 $a_i\bmod a_{i-1}=x_i$ 并且 $a_i>x_{i+1}$。所以 $a_i=a_{i-1}\times(\left\lfloor x_{i+1}\div a_{i-1}\right\rfloor+1)+x_{i}$ 满足要求。

对于 $i=n$，$a_i$ 取 $x_i$ 就可以了。

**AC 代码，请勿抄袭。**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 505;
int x[N];
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while(t--) {
    int n;
    cin >> n;
    for(int i = 2; i <= n; i++) {
      cin >> x[i];
    }
    int l = x[2] + 1;
    cout << l;
    for(int i = 2; i < n; i++) {
      l = l * (x[i + 1] / l + 1) + x[i];
      cout << ' ' << l;
    }
    cout << ' ' << x[n] << '\n';
  }
  return 0;
}
```

---

