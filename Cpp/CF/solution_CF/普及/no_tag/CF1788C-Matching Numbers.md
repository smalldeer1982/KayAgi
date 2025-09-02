# Matching Numbers

## 题目描述

You are given an integer $ n $ . Pair the integers $ 1 $ to $ 2n $ (i.e. each integer should be in exactly one pair) so that each sum of matched pairs is consecutive and distinct.

Formally, let $ (a_i, b_i) $ be the pairs that you matched. $ \{a_1, b_1, a_2, b_2, \ldots, a_n, b_n\} $ should be a permutation of $ \{1, 2, \ldots, 2n\} $ . Let the sorted list of $ \{a_1+b_1, a_2+b_2, \ldots, a_n+b_n\} $ be $ s_1 < s_2 < \ldots < s_n $ . We must have $ s_{i+1}-s_i = 1 $ for $ 1 \le i \le n - 1 $ .

## 说明/提示

For the third test case, each integer from $ 1 $ to $ 6 $ appears once. The sums of matched pairs are $ 4+2=6 $ , $ 1+6=7 $ , and $ 3+5=8 $ , which are consecutive and distinct.

## 样例 #1

### 输入

```
4
1
2
3
4```

### 输出

```
Yes
1 2
No
Yes
1 6
3 5
4 2
No```

# 题解

## 作者：Remilia1023 (赞：5)

## 前言

好生气！做了 1.5h，结果发现构造方式超级简单。

## 题解

设等差数列第一项为 $x$，可以算出等差数列之和 $sum=\displaystyle\frac{n(2x+n-1)}{2}$，
而 $1$ 到 $2n$ 的和为 $n(1+2n)$，即 $\displaystyle\frac{n(2x+n-1)}{2}=n(1+2n)$，得 $x=\displaystyle\frac{3n+3}{2}$。

$x$ 为整数，因此 $n$ 为偶数时无解。

接下来考虑构造方式，等差数列的每一项可以表示成 $a_i+b_i$，以下构造方式能使 $a_i$ 取遍 $1\sim n$，$b_i$ 取遍 $(n+1)\sim 2n$，首先把**前 $n$ 个数**分成两组：

- $1,3,\cdots, n\qquad (1)$

- $2,4,\cdots, n-1\ (2)$

组内每项都比前一项大 $2$，这时可以通过调整 $b_i$ 来使组内变为每项都比前一项大 $1$，容易发现 $b_i$ 逐渐减小且每次减 $1$。

此时通过加上 $b_i$，把第 $(2)$ 组平移到 $x\sim\left(x+\displaystyle\frac{n-3}{2}\right)$ 的位置，第 $(1)$ 组平移到 $\left(x+\displaystyle\frac{n-1}{2}\right)\sim(x+n-1)$ 的位置即可。

说的十分抽象 $\cdots\cdots$，实际上很容易，看看代码就能理解了。

```cpp

#include <bits/stdc++.h>
using namespace std;
int n, T;
int main()
{
  cin >> T;
  while (T--) {
    cin >> n;
    if (!(n & 1)) cout << "NO\n";
    else {
      cout << "YES\n";
      int a = 2 * n, b = 3 * (n + 1) / 2 - 2;
      for (int i = 1; i <= n; i++) 
        if (i & 1) cout << i << ' ' << a-- << endl;
        else cout << i << ' ' << b-- << endl;
    }
  }
  return 0;
}

```

---

## 作者：xzyg (赞：3)

## 题意简述

给定一整数 $ n $，每次从 $ [1,2n] $ 里面取出两个数加和放进新序列。要求 $ n $ 次操作后将新序列排序时，新序列为一个公差为 $ 1 $ 的等差数列。构造一组取数方案使得满足要求，若不存在输出 $ -1 $。

## Sol

神奇构造题。

设如果存在合法方案，则排序后数列为 $ s = \{ s_i \} ,i \in [1,n] $。

首先考虑不合法的情况，~~根据样例可知~~显然所有 $ n $ 为偶数的情况是不合法的：

若 $ n $ 为偶数时存在合法解，则 $ \sum_{i = 1} ^ {2n} i  = \frac{2n(2n + 1)}{2} = n(2n + 1) $。

$ s $ 中所有数的平均数为 $ \frac{n(2n + 1)}{n} = 2n + 1 $。

但实际上如果 $ n $ 为偶数，$ s $ 中所有数的平均数应该是小数点后有一位 $ 5 $。

矛盾，所以 $ n $ 为偶数时不存在合法解。

接下来只需要对每个奇数 $ n $ 构造一组通解即可。

可以举一个 $ n = 5 $ 的例子：

最终序列为 $ 9,10,11,12,13 $。

可构造 $ 9 = 3 + 6, 10 = 2 + 8, 11 = 1 + 10, 12 = 5 + 7, 13 = 4 + 9 $。

如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/4t4q1z1r.png)

~~我们钦定~~ $ 1 $ 总是与 $ 2n $ 配对形成最终序列里最中间的数。

若 $ i \in [1, \lceil \frac{n}{2} \rceil] $，则可以将 $ i $ 与 $ 2n - 2(i-1) $ 即 $ 2n - 2i + 2 $ 配对。

若 $ i \in [\lceil \frac{n}{2} \rceil + 1, n] $，则可以将 $ i $ 与 $ 2n - 1 - 2(i - (\lceil \frac{n}{2} \rceil + 1) ) $ 即 $ 2n - 2i+ 2\lceil \frac{n}{2} \rceil + 1 $ 配对。

至于这样构造为什么是合法的，这里给出一个简单的证明：

对于每种情况，与 $ i $ 配对的数随着 $ i $ 的增大而减小，在每种情况内不会用重复的数，且该数一定在 $ [n+1, 2n] $ 范围内。

对于第一种情况，与 $ i $ 配对的数一定是偶数；对于第二种情况，与 $ i $ 配对的数一定是奇数。

两种情况互补，所有的数都没有重复的可能性，并且最终构造结果长度合法，所以该方案一定合法。

### 代码：

```cpp
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdio>
#include<algorithm> 
#define ll long long

using namespace std;

int main(){
	ll T;
	cin >> T;
	while(T--){
		ll n;
		cin >> n;
		if(n & 1){
			cout << "Yes\n";
			for(ll i = 1; i <= n/2 + 1; i++)
				cout << i << " " << 2 * n - 2 * i + 2 << '\n'; 
			for(ll i = n/2 + 2; i <= n; i++)
				cout << i << " " << 2 * n - 2 * i + 2 * (n + 1) / 2 + 1 << '\n';
		}else{
			cout << "No\n";
		}
	}
	return 0;
}
```


---

## 作者：copper_ingot (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1788C)

题面翻译得不是很清楚，给出一个 $m$，希望找到一种方法把 $1 \sim 2m$ 的整数两两配对，得到 $m$ 个配对，再把每个配对中两个数的和放到一个数组里，使得这个数组里是连续自然数。

首先，这 $2m$ 个数和是 $(1 + 2m)m$，所以 $m$ 个和的平均数是 $1 + 2m$。

如果 $m$ 是偶数，那么 $m$ 个连续自然数的平均数应该是一个整数加上 $0.5$。

但是 $1 + 2m$ 是整数，所以遇到 $m$ 是偶数时直接输出 `No`。

所以这个数列的中间值是 $1 + 2m$，最小值是 $\frac{3m + 3}{2}$，最大值是 $\frac{5m + 1}{2}$。

注：因为从这步开始保证 $m$ 是奇数，所以下面用 $\frac{m + 1}{2}$ 代替 $\lceil \frac{m}{2} \rceil$，用 $\frac{m - 1}{2}$ 代替 $\lfloor \frac{m}{2} \rfloor$。

现在考虑构造方式，首先枚举 $i$ 从 $1$ 到 $\frac{m + 1}{2}$，让它和 $2m - 2i + 2$ 配对（即从右往左第 $2i - 1$ 位），就像这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/2iekdki3.png?x-oss-process=image/resize,m_lfit,h_680,w_900)

这样正好可以满足从中间值 $1 + 2m$ 到最小值 $\frac{3m + 3}{2}$ 的所有值。

然后枚举 $i$ 从 $\frac{m + 1}{2} + 1$ 到 $m$，并让它和 $3m - 2i + 2$，就是从右往左第 $2(i - \frac{m + 1}{2})$ 位配对。

![](https://cdn.luogu.com.cn/upload/image_hosting/6b9i0rr3.png?x-oss-process=image/resize,m_lfit,h_680,w_900)

这样可以满足从最大值 $\frac{5m + 1}{2}$ 到比中间值多一 $2 + 2m$ 的所有值。

把配对依次输出即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, m;
int main(){
	scanf("%d", &t);
	while (t--){
		scanf("%d", &m);
		if (m % 2 == 0){puts("No"); continue;}//如果是偶数直接输出 No
		int j = 2 * m; puts("Yes");
		for (int i = 1; i <= m / 2 + 1; i++){//第一轮配对
			printf("%d %d\n", i, j);
			j -= 2;
		}
		j = 2 * m - 1;
		for (int i = m / 2 + 2; i <= m; i++){//第二轮配对
			printf("%d %d\n", i, j);
			j -= 2;
		}
	}
	return 0;
}
```

---

## 作者：Pwtking (赞：2)

一道~~简单的~~数学思维题。

题目的翻译有点问题，事实上输入的第一个数应该是 $t$ （代表数据组数），后面才是每一组数 $m$ （大家应该能看出来。

## Solution 

我们假设等差数列的第一项为 $x$，则根据小学三年级的等差数列求和公式可得这个等差数列的的和为 $\frac{(x + x + m - 1) \times m}{2}$，亦等于这 $2m$  个数的和 $(1 + 2m) \times m$，所以我们可以得到方程： $\frac{(x + x + m - 1) \times m}{2}=(1 + 2m) \times m$，解得 $x=\frac{3+3m}{2}$。由此我们显然能看出如果 $x$ 即 $\frac{3+3m}{2}$ 不为整数，则此时无解应输出  No。

接下来就容易了，我们构造每个等差数列的每一项即可，具体看代码。

然后喜提 AC。

**AC code**
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define inf 0x7fffffff
ll t,m,vis[1000010];
inline void work(ll k) {
	memset(vis,0,sizeof(vis)); 
	ll f=(3*m+3)/2;
	ll a=1,b=f-a,flag=0,ff=0;
	cout<<a<<" "<<b<<endl;
	vis[a]=1,vis[b]=1;
	for (ll i=2;i<=k;++i) {
		a+=2,--b;
		if (!vis[a]&&!vis[b]&&!flag) {
			cout<<a<<" "<<b<<endl;
			vis[a]=1,vis[b]=1;
			continue;
		}
		flag=1;
	    if (!ff) a=2,b=f+i-1-a,ff=1;
	    if (!vis[a]&&!vis[b]) {
	    	vis[a]=1,vis[b]=1;
	    	cout<<a<<" "<<b<<endl;
		}
	}
}
int main() {
	cin>>t;
	while (t--) {
		cin>>m;
		if (m%2) {
			cout<<"Yes"<<endl;
			work(m);
		}
		else cout<<"No"<<endl;
	}
	return 0;
} 
```


---

## 作者：loser_seele (赞：1)

当 $ n $ 为偶数的时候，$ k+k+1+...+k+n-1 $ 与 $ 1+2+...+2n $ 的奇偶性不同，显然无解。

当 $ n $ 为奇数的时候，则可以构造出等差数列 $ 3m+4,3m+5,3m+6,... $ 满足题意，然后直接构造即可。

时间复杂度线性。

[提交记录](https://codeforces.com/contest/1788/submission/192996983)

---

## 作者：yuanruiqi (赞：0)

## 题意简述

分别由数字 $1$ 到 $n$ 和 $n+1$ 到 $2n$ 构建两个排列 $a, b$，使得对应元素相加构成的集合可以成为公差为一的等差数列。输出是否可行，若可行，任意顺序输出两个排列对应位置组成的数对 $a_i, b_i$。

## 题目分析

规律题。考虑 $n = 5$ 时的做法。$a, b$ 可以为 $1,2,3,4,5$ 和 $10,8,6,9,7$。进一步分析，$a_i = i$；$1 \leq i \leq \lceil \frac{n}{2} \rceil$ 时 $b_i=2(n-i+1)$，否则 $b_i=2(n+\lceil \frac{n}{2} \rceil-i)+1$。按此规律模拟即可，具体可以看代码。

## 代码

```cpp
void solve()
{
    int n;
    cin >> n;
    if (n % 2 == 0) cout << "No\n";
    else
    {
        cout << "YES\n";
        int cnt = 2 * n;
        for (int i=1;i<=n;++i)
        {
            cout << i << ' ' << cnt << '\n';
            cnt -= 2;
            if (cnt <= n) cnt = 2 * n - 1;
        }
    }
}
```

---

## 作者：MSavannah (赞：0)

**Statement**

给 $1\sim 2n$ 的排列，将数两两配对，构造一个配对方案使得，这 $n$ 对数构成一个公差为 $1$ 的等差数列。

**Solution**

首先 $n$ 为偶数时一定无解。

证明：

设我们构造出的等差数列的第一项为 $x$，根据公式我们知道等差数列的和是 $\tfrac{n\times(x+x+n-1)}{2}$，而等差数列的和又是 $1\sim 2n$ 的和。解得 $x=\tfrac{3n+3}{3}$。所以 $n$ 取偶数得时候注定无解。

那么考虑 $n$ 是奇数得时候如何构造。

对于 $[1,\left\lceil\dfrac{n}{2}\right\rceil]$ 的任意数 $x$，让它 $2n-2(x-1)$ 配对。

对于 $[\left\lceil\dfrac{n}{2}\right\rceil+1,n]$ 中的 $x$，和 $2n-1-2(x-(\left\lceil\dfrac{n}{2}\right\rceil+1))$ 配对。

[code](https://www.luogu.com.cn/record/156844394)

---

