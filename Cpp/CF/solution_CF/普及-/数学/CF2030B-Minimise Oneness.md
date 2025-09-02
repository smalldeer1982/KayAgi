# Minimise Oneness

## 题目描述

For an arbitrary binary string $ t $ $ ^{\text{∗}} $ , let $ f(t) $ be the number of non-empty subsequences $ ^{\text{†}} $ of $ t $ that contain only $ \mathtt{0} $ , and let $ g(t) $ be the number of non-empty subsequences of $ t $ that contain at least one $ \mathtt{1} $ .

Note that for $ f(t) $ and for $ g(t) $ , each subsequence is counted as many times as it appears in $ t $ . E.g., $ f(\mathtt{000}) = 7, g(\mathtt{100}) = 4 $ .

We define the oneness of the binary string $ t $ to be $ |f(t)-g(t)| $ , where for an arbitrary integer $ z $ , $ |z| $ represents the absolute value of $ z $ .

You are given a positive integer $ n $ . Find a binary string $ s $ of length $ n $ such that its oneness is as small as possible. If there are multiple strings, you can print any of them.

 $ ^{\text{∗}} $ A binary string is a string that only consists of characters $ \texttt{0} $ and $ \texttt{1} $ .

 $ ^{\text{†}} $ A sequence $ a $ is a subsequence of a sequence $ b $ if $ a $ can be obtained from $ b $ by the deletion of several (possibly, zero or all) elements. For example, subsequences of $ \mathtt{1011101} $ are $ \mathtt{0} $ , $ \mathtt{1} $ , $ \mathtt{11111} $ , $ \mathtt{0111} $ , but not $ \mathtt{000} $ nor $ \mathtt{11100} $ .

## 说明/提示

In the first test case, for the example output, $ f(t)=1 $ because there is one subsequence that contains only $ \mathtt{0} $ ( $ \mathtt{0} $ ), and $ g(t)=0 $ because there are no subsequences that contain at least one $ 1 $ . The oneness is $ |1-0|=1 $ . The output $ \mathtt{1} $ is correct as well because its oneness is $ |0-1|=1 $ .

For the example output of the second test case, $ f(t)=1 $ because there is one non-empty subsequence that contains only $ \mathtt{0} $ , and $ g(t)=2 $ because there are two non-empty subsequences that contain at least one $ \mathtt{1} $ ( $ \mathtt{01} $ and $ \mathtt{1} $ ). The oneness is thus $ |1-2|=1 $ . It can be shown that $ 1 $ is the minimum possible value of its oneness over all possible binary strings of size $ 2 $ .

## 样例 #1

### 输入

```
3
1
2
3```

### 输出

```
0
01
010```

# 题解

## 作者：末然Ender (赞：3)

# 题解：CF2030B Minimise Oneness

## 思路

显然，对于一个长度为 $x$ 数列的，因为每一个数都可以选择或者不选，所以其非空子序列个数为 $2^x-1$ 。

题目中的 $f(t)$为字符串 $t$ 中仅包含 $0$ 的非空子序列个数，也就是把所有 $0$ 摘出来，其子序列个数就是 $2^x-1$，$x$ 是字符串中 $0$ 的个数。所以易得：

$$f(t)=2^x-1$$

因为一个子序列不全是 $0$ 就一定包含至少 $1$ 个 $1$，所以：

$$g(t)=2^n-f(t)=2^n-2^x+1$$

其中 $n$ 是输入的字符串长度。所以我们需要求的是最小化这个东西：

$$
\begin{aligned}
|f(s)-g(s)|&=|2^x-1-(2^n-2^x+1)|\\&=|2^{x+1}-2^n-1|
\end{aligned}
$$

因为 $n>0$，所以 $|2^{x+1}-2^n|$ 不可能等于 $1$，所以我们令 $x+1=n$ 也就是 $x=n-1$ 即可，所以对于每组输入，我们输出一个 $1$ 然后再输出 $n-1$ 个 $0$ 即可。

## 代码

$14$ 行代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		scanf("%d",&n);
		putchar('1');
		for(int i=1;i<n;i++)putchar('0');
		putchar('\n');
	}
	return 0;
} 
```

---

## 作者：zsfzhjf (赞：1)

可以发现若 $t$ 中有 $1$ 那么 $f \le g$

所有全 $0$ 的串都可加上若干个 $1$ 使之符合 $f$ 的条件

那么答案最小的 $t$ 就是一个 $1$ 其他全 $0$ 的串


```cpp
#include<bits/stdc++.h>
int T;
int n;
signed main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<n;i++) printf("0");
		printf("1");
		puts("");
	}
}
```

---

## 作者：wuyouawa (赞：0)

### 题目大意

有 $t$ 组数据，每组数据输入一个整数 $n$，求出一个长度为 $n$ 的01串 $s$，使得 $| f(s)-g(s) |$ 最小，其中 $f(s)$ 表示 $s$ 的非空子序列中只包含 $0$ 的序列的个数，$g(s)$ 表示 $s$ 的非空子序列中包含至少 $1$ 个 $1$ 的序列的个数，如有多解输出```any```。
### 思路

因为由于我们需要 $| f(s)-g(s) |$ 最小，也就是说，要 $f(s)$ 与 $g(s)$ 尽量接近，所以前面一个 $1$，后面全是 $0$ 的是最优的。因为这样的话，要想有至少一个 $1$，就必须要选择第一个 $1$，那么其它的 $0$ 就选不选均可了，这样就变成了 $n-1$ 个 $0$ 组成的字符串有多少个子序列，这就是 $g(s)$。那么如果要全是 $0$，就是 $n-1$ 个 $0$ 组成的字符串有多少个**非空**子序列，这就是 $f(s)$。注意到 $f(s)$ 与 $g(s)$ 只差 $1$，因为 $f(s)$ 不可选 $1$，但 $g(s)$ 可以，就只差这一个，这样就是最优的。

### CODE


```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n;
int main() {
	cin >> t;
	while (t--) {
		cin >> n;
		cout << 1;
		for (int i = 1; i < n; i++) {
			cout << 0;
		}
		cout << endl;//直接输出1个1，n-1个0，注意多测，换行
	}
	return 0;
}
```

---

## 作者：Priestess_SLG (赞：0)

首先所有非空子序列的数目为 $2^n-1$ 是奇数，因此两数的差也只能为奇数，最小值最小为 $1$。因此考虑构造串 $000\ldots01$，此时两数的差为 $1$。根据上面的分析发现差的绝对值必然是奇数，因此无更优构造。

单组数据时间复杂度为 $O(n)$。

```python
T = int(input())
for _ in range(T):
  n = int(input())
  for i in range(n - 1) : print('0')
  print('1')
```

---

## 作者：GeYang (赞：0)

# 题意

[翻译已经很简明了](https://www.luogu.com.cn/problem/CF2030B)。

# 思路

结论题，重点证明结论。

因为 $f(t)$ 是只包含 $0$ 的子序列的个数，而 $g(t)$ 是包含 $1$ 的子序列个数。

所以，当这个字符串 $s$ 里没有 $1$ 时 $∣f(s)−g(s)∣$ 的值为 $\frac{n(n+1)}{2}$ 显然不行。

当 $s$ 里有 $1$ 时 $g(s)=n$。

所以我们要尽可能让 $f(s)$ 的值大，从而减小 $∣f(s)−g(s)∣$ 的值。

显然，所有 $0$ 连在一起时 $f(s)$ 最大。

综上，只要输出 $n-1$ 个 $0$ 和一个 $1$ 即可。

# 代码


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll t;
void solve()
{
	ll n;
	cin>>n;
	for(int i=1;i<=n-1;i++) cout<<0;
	cout<<1<<endl;
}
int main(){
	cin>>t;
	while(t--) solve();
	return 0;
}
```

# 记录
[在这里](https://codeforces.com/problemset/submission/2030/287613097)。

---

## 作者：xixisuper (赞：0)

# CF2030B Minimise Oneness 题解

简单题。

## 思路

设 01 串 $s$ 长为 $n$，则我们有：

$$
g(s)=2^n-1-f(s)
$$

显然在所有非空子序列中去掉只包含 `0` 的子序列就是至少包含一个 `1` 的子序列数。

假设 $s$ 中有 $x$ 个 `0`，则：

$$
f(s)=2^x-1
$$

简单说一下这个式子，我们对于每个 `0` 都有选或不选两种状态，显然一共 $2^x$ 种不同的状态，又因为子序列非空，最后减一即可。

所以我们要最小化的式子是：

$$
\begin{aligned}
|f(s)-g(s)|&=|2f(s)-2^n+1|\\
&=|2^{x+1}-2^n-1|
\end{aligned}
$$

由于 $2^{x+1}-2^n$ 不可能等于 $1$，所以说只需要让 $x+1=n$ 便能得到最小值，即输出一个 01 串让里面有 $1$ 个 `1` 和 $n-1$ 个 `0` 即可。

```cpp
#include <iostream>
using namespace std;
void solve(){
    int n;
    cin>>n;
    cout<<"1";
    while(--n) cout<<"0";
    cout<<"\n";
}
int main(){
    int T;
    cin>>T;
    while(T--) solve();
    return 0;
}
```

---

## 作者：He_XY (赞：0)

## [B. Minimise Oneness](https://codeforces.com/contest/2030/problem/B) 题解

~~给审核看的：我的 `|` 就是绝对值，不是整除。~~
### 思路

对于任意的 $01$ 字符串 $t$，设 $f(t)$ 为只包含 $0$ 的 $t$ 的非空 **子序列** 的数量，设 $g(t)$ 为至少包含一个 $1$ 的 $t$ 的非空子序列的数量。

定义 $t$ 的 *单一性* 为 $| f(t)−g(t)∣$，给定一个 $n$，找到一个长度为 $n$ 的二进制字符串 $s$，使其 *单一性* 尽可能小。如果存在多个字符串，你可以输出其中的任何一个。

### 思路

设字符串 $s$ 中 $0$ 的数量为 $k$，则 $f(s)=2^k-1$，$g(s)=(2^n-1)-(2^k-1)$；

相减得：$f(s)-g(s)=2^{k+1}-2^n$；

可得，当 $k=n-1$ 时，$|f(s)-g(s)|=0$；

所以无论顺序，这个字符串应该包含 $n-1$ 个 `0` 和 $1$ 个 `1`。

### C++ 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
	cin>>t;
	while(t--){
		int n;
        cin>>n;
        n--;
        while(n--){
            cout<<0;
        }
        cout<<1<<endl;
	}
	return 0;
}
```

---

