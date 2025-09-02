# Medians

## 题目描述

You are given an array $ a = [1, 2, \ldots, n] $ , where $ n $ is odd, and an integer $ k $ .

Your task is to choose an odd positive integer $ m $ and to split $ a $ into $ m $ subarrays $ ^{\dagger} $ $ b_1, b_2, \ldots, b_m $ such that:

- Each element of the array $ a $ belongs to exactly one subarray.
- For all $ 1 \le i \le m $ , $ |b_i| $ is odd, i.e., the length of each subarray is odd.
- $ \operatorname{median}([\operatorname{median}(b_1), \operatorname{median}(b_2), \ldots, \operatorname{median}(b_m)]) = k $ , i.e., the median $ ^{\ddagger} $ of the array of medians of all subarrays must equal $ k $ . $ \operatorname{median}(c) $ denotes the median of the array $ c $ .

 $ ^{\dagger} $ A subarray of the array $ a $ of length $ n $ is the array $ [a_l, a_{l + 1}, \ldots, a_r] $ for some integers $ 1 \le l \le r \le n $ .

 $ ^{\ddagger} $ A median of the array of odd length is the middle element after the array is sorted in non-decreasing order. For example: $ \operatorname{median}([1,2,5,4,3]) = 3 $ , $ \operatorname{median}([3,2,1]) = 2 $ , $ \operatorname{median}([2,1,2,1,2,2,2]) = 2 $ .

## 说明/提示

In the first test case, the given partition has $ m = 1 $ and $ b_1 = [1] $ . It is obvious that $ \operatorname{median}([\operatorname{median}([1])]) = \operatorname{median}([1]) = 1 $ .

In the second test case, the given partition has $ m = 3 $ and:

- $ b_1 = [1] $
- $ b_2 = [2] $
- $ b_3 = [3] $

Therefore, $ \operatorname{median}([\operatorname{median}([1]), \operatorname{median}([2]), \operatorname{median}([3])]) = \operatorname{median}([1, 2, 3]) = 2 $ .

In the third test case, there is no valid partition for $ k = 3 $ .

In the fourth test case, the given partition has $ m = 5 $ and:

- $ b_1 = [1, 2, 3] $
- $ b_2 = [4, 5, 6] $
- $ b_3 = [7, 8, 9] $
- $ b_4 = [10, 11, 12] $
- $ b_5 = [13, 14, 15] $

Therefore, $ \operatorname{median}([\operatorname{median}([1, 2, 3]), \operatorname{median}([4, 5, 6]), \operatorname{median}([7, 8, 9]), \operatorname{median}([10, 11, 12]), \operatorname{median}([13, 14, 15])]) = \operatorname{median}([2, 5, 8, 11, 14]) = 8 $ .

## 样例 #1

### 输入

```
4
1 1
3 2
3 3
15 8```

### 输出

```
1
1
3
1 2 3
-1
5
1 4 7 10 13```

# 题解

## 作者：Drifty (赞：2)

### Preface

好神奇的构造题，实现跟官解有点不一样，发一篇。

### Solution

考虑分类讨论。

我们考虑直接让 $a_k=k$ 单独一组。由于 $n$ 是奇数，因此 $n - 1$ 是偶数，那么 $k - 1$ 和 $n - k$ 奇偶性相同。

我们做一个分讨：

- $n=1\land k=1$ 时，那么整个划为一段。答案为 $1$。
- $k=1\lor k=n$ 时，注意到 $n=\sum_{i = 1} ^m\vert b_i\vert $ 且 $n$ 和 $\vert b_i\vert $ 均为奇数，而 $k$ 要么在第一个要么在最后一个然而由于 $n > 1$，因此 $m \ge 3$，所以 $k$ 注定成为不了中位数。
- $k - 1\equiv 1 \pmod 2$ 直接把 $1\sim k-1$ 看做一段，$k$ 单独看做一段，$k + 1 \sim n$ 看做一段即可，正确性显然。
- $k - 1\equiv 0 \pmod 2$ 把 $1\sim k - 1$ 随便分成两段，$k$ 单独看做一段，$k + 1\sim n$ 随便分成两段，正确性显然。

然后就做完了。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int T; cin >> T;
    for (int n, k; T --; ) {
        cin >> n >> k;
        if (n == 1 && k == 1) {
            cout << 1 << '\n' << 1 << '\n';
            continue;
        }
        if (k == n || k == 1) {
            cout << -1 << '\n';
            continue;
        }
        if (n - k & 1) {
            cout << 3 << '\n';
            cout << 1 << ' ' << k << ' ' << k + 1 << '\n';
        }
        else {
            cout << 5 << '\n';
            cout << 1 << ' ' << 2 << ' ' << k << ' ' << k + 1 << ' ' << k + 2 << '\n';
        }
    }
    return 0;
}

```

---

## 作者：chen_z (赞：1)

考虑将 $k$ 这个元素划分成单独的一段。

由于 $a=[1,2,3,\dots,n]$，不论如何划分，前一段的中位数不可能大于后一段的中位数，因此只要 $k$ 所在的这一段位置是所有段的正中间就好了。

然后你直接将序列划分成 $[1,k-1]$，$[k,k]$ 和 $[k+1,n]$ 三段就好了。

注意题目要求每一段的长度都为奇，在 $[1,k-1]$ 这一段长度为偶的时候你把它再划分成 $[1,k-2]$ 和 $[k-1,k-1]$。

只有 $k$ 前后没有足够的数给你划分的时候才是不合法的（例如我 $k$ 前面至少划分成两缎，但是只有一个元素了）。

Ac code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,k;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>k;
        if(k==1&&n==1){
            cout<<"1\n1\n";
            continue;
        }
        if(k==1||k==n){
            cout<<"-1\n";
            continue;
        }
        if((k-1)%2==0){
            cout<<"5\n";
            if(k<=2||k>=n-1){
                cout<<"-1\n";
                continue;
            }
            cout<<1<<" "<<k-1<<" "<<k<<" "<<k+1<<" "<<k+2<<'\n';
        }
        else{
            cout<<"3\n";
            cout<<1<<" "<<k<<" "<<k+1<<'\n';
        }
    }
    return 0;
}
```

---

## 作者：huanglihuan (赞：0)

### 题意
询问是有否一个合法的 $m$ 能将序列 $\{1,2,\ldots,n\}$ 划分为 $m$ 段，每段均为奇数，且每段的中位数的中位数是 $k$。
### Solution
很好的构造题。  
特殊情况：
* $n=k=1$，可以构造 $m=1,b=\{\{1\}\}$，满足要求。
* $n\ne 1,k\in[1,n]$，显然无解。

正常情况：
* $k\bmod2=0$，发现直接令 $k$ 为中位数，构造 $b=\{\{1,2,\ldots,k-1\},\{k\},\{k+1,k+2,\ldots,n\}\}$ 即可。
* $k\bmod2=0$，发现把 $\{k-1,k,k+1\}$ 构造为 $b_2$，则 $b=\{\{1,2,\ldots,k-2\},\{k-1,k,k+1\},\{k+2,k+3,\ldots,n\}\}$ 可以满足要求，因为此时中位数为 $\{k-1,k,k+1\}$ 的中位数即为 $k$。
### Code

```cpp
#include <bits/stdc++.h>
#include <cstdio>
#define int long long
#define ull unsigned long long
#define mod 998244353
#define MOD 1000000007
using namespace std;
const int N = 2e6 + 5,maxn = 3e3 + 5;
const double goldnum = (sqrt (5) + 1) / 2;
inline int read ()
{
	int x = 0;
	bool f = 1;
	char c = getchar ();
	while (c < '0' || c > '9') f = (c == '-' ? !f : f),c = getchar ();
	while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c ^ 48),c = getchar ();
	return (f ? x : -x);
}
inline void write (int x)
{
	if (x < 0) putchar ('-'),x = -x;
	if (x > 9) write (x / 10);
	putchar (x % 10 + '0');
	return ;
}
signed main ()
{
	int T;
	cin >> T;
	while (T --)
	{
		int n,k;
		cin >> n >> k;
		if (n == 1)
		{
			cout << "1\n1\n";
			continue;
		}
		if (k == 1 || k == n)
		{
			cout << "-1\n";
			continue;
		}
		cout << "3\n";
		if (k % 2 == 0) cout << 1 << ' ' << k << ' ' << k + 1 << endl;
		else cout << 1 << ' ' << k - 1 << ' ' << k + 2 << endl;
	}
	return 0;
}
```

---

## 作者：tai_chi (赞：0)

可以在 [cnblog](https://www.cnblogs.com/tai-chi/p/18523933) 中阅读。

### 题意

给一个数组 $a=[1,2, \dotsb ,n]$（保证 $n$ 为奇数），需要将这个数组划分成连续的 $m$ 段（$m$ 不固定），使得

- 每段的长度都是奇数；
- `每一段的中位数`的中位数等于给定的 $k$。

构造一个划分方案。

### 分析

注意到条件二的关键只在最中间一段，我们可以让中间的一段只包含 $k$ 一个元素以满足条件二。剩下的工作就是让左边的段数为奇数，右边的段数也为奇数，且左右划分出的段数相等。

接下来只要对左边右边根据奇偶性分类下就行，若左右奇偶性不相同则无解。全奇数整个作为一段即可，全偶数先分出一个再整个作为一段即可。

还有一些总数较小的边界情况，讨论下也不难。

```cpp
void solve()
{
	int n,k; cin>>n>>k;
	int l=k-1,r=n-k;
	if(l%2!=r%2) {cout<<-1<<endl; return;}
	if((!l&&r)||(!r&&l)) {cout<<-1<<endl; return;}
	if(n==1)
	{
		cout<<1<<endl;
		cout<<1<<endl;
	}
	else if(l%2==0&&r%2==0)
	{
		cout<<5<<endl;
		cout<<1<<" "<<k-1<<" "<<k<<" "<<k+1<<" "<<k+2<<endl;
	}
	else if(l%2!=0&&r%2!=0)
	{
		cout<<3<<endl;
		cout<<1<<" "<<k<<" "<<k+1<<endl;
	}
}
```

---

## 作者：Milky_Cat (赞：0)

注意审题：分成 $m$ 段的长度必须全部是奇数。

注意到数列是一个 $1 \sim n$ 的排列，每个子区间都是有序的，由中位数的定义可知区间 $[x-l,x+l]$ 的中位数就是 $x$。所以我们一定可以构造出一个 $m \leq 3$ 的方案。

看代码，比较清晰：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T, n, k;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> T;
	while (T--){
		cin >> n >> k;
		if (n == 1){
			cout << "1\n1\n";
			continue;
		}
		if (k == 1 || k == n){//k 不能是 1 或 n，否则没法成为中位数
			cout << "-1\n";
			continue;
		}
		if ((k - 1) & 1){//[1,k-1] 长度为奇数
			cout << "3\n";
			cout << 1 << " " << k << " " << k + 1 << "\n";
		}else{//要保证长度为奇数，所以左右多划一个
			cout << "3\n";
			cout << 1 << " " << k - 1 << " " << k + 2 << "\n";
		}
	}
	return 0; 
}
```

---

## 作者：__galaxy_1202__ (赞：0)

## 解题思路：
分类讨论题。
容易发现当 $k = 1$ 或 $k = n$ 时无解，接下来讨论
- 当 $n=1$ 时，显然分成 $1$ 份即可。
- 当 $k$ 为偶数时，序列明显可以分为 $1 \sim k-1，k，k+1 \sim n$ 这 $3$ 个奇数段。
- 否则继续分类
  - 当 $k$ 不为倒数第二个数时，可以将左右个延长一个数，即分为 $1 \sim k-2，k-1 \sim k+1，k+2 \sim n$ 这 $3$ 个奇数段。
  - 否则无解。


## CODE：

```cpp
#include <iostream>
using namespace std;
long long t, n, k;
int main()
{
    cin >> t;
    while (t--)
    {
        cin >> n >> k;
        if (n == 1)
        {
            cout << "1\n1\n";
            continue;
        }
        if (k == n || k == 1)
        {
            cout << "-1\n";
            continue;
        }
        cout << "3\n";
        if (k & 1) 
        {
            if (k + 2 > n) cout << "-1\n"; 
            else cout << 1 << ' ' << k - 1 << ' ' << k + 2 << '\n';
        }
        else cout << 1 << ' ' << k << ' ' << k + 1 << '\n';
    }
    return 0;
}
```

---

