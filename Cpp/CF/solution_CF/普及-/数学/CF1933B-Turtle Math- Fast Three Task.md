# Turtle Math: Fast Three Task

## 题目描述

You are given an array $ a_1, a_2, \ldots, a_n $ .

In one move, you can perform either of the following two operations:

- Choose an element from the array and remove it from the array. As a result, the length of the array decreases by $ 1 $ ;
- Choose an element from the array and increase its value by $ 1 $ .

You can perform any number of moves. If the current array becomes empty, then no more moves can be made.

Your task is to find the minimum number of moves required to make the sum of the elements of the array $ a $ divisible by $ 3 $ . It is possible that you may need $ 0 $ moves.

Note that the sum of the elements of an empty array (an array of length $ 0 $ ) is equal to $ 0 $ .

## 说明/提示

In the first test case, initially the array $ a = [2, 2, 5, 4] $ . One of the optimal ways to make moves is:

- remove the current $ 4 $ th element and get $ a = [2, 2, 5] $ ;

 As a result, the sum of the elements of the array $ a $ will be divisible by $ 3 $ (indeed, $ a_1 + a_2 + a_3 = 2 + 2 + 5 = 9 $ ).In the second test case, initially, the sum of the array is $ 1+3+2 = 6 $ , which is divisible by $ 3 $ . Therefore, no moves are required. Hence, the answer is $ 0 $ .

In the fourth test case, initially, the sum of the array is $ 1 $ , which is not divisible by $ 3 $ . By removing its only element, you will get an empty array, so its sum is $ 0 $ . Hence, the answer is $ 1 $ .

## 样例 #1

### 输入

```
8
4
2 2 5 4
3
1 3 2
4
3 7 6 8
1
1
4
2 2 4 2
2
5 5
7
2 4 8 1 9 3 4
2
4 10```

### 输出

```
1
0
0
1
1
2
1
1```

# 题解

## 作者：littlebug (赞：4)

**形式化题意**：给定一个序列 $a$，共有 $2$ 种操作，求最小操作次数使得 $\sum a \bmod 3=0$。

- 操作一：删除 $a$ 中的任意一个元素。
- 操作二：将 $a$ 中的任意一个元素 $+1$。

记 $sum=\sum a \bmod 3$。

初始序列的 $sum$ 有 $3$ 种情况，我们分类讨论一下：

- $sum=0$：已经满足条件，不需要做任何操作。
- $sum=1$：如果使用操作二，则至少需要操作 $2$ 次；如果使用操作一，当 $a$ 中存在一个元素 $a_i$ 满足 $a_i\bmod 3=1$ 时，删除这个元素，则 $sum-1$，只用进行一次操作就可以满足条件。
- $sum=2$：使用一次操作二，将序列中任何一个数 $+1$ 即可，操作数为 $1$。

时间复杂度 $O(n)$。

**code**：
```cpp
#include<iostream>
#include<cstdio>
#define il inline
using namespace std;
const int MAXN=1e5+5;
const int mod=3;
int n;
int a[MAXN];
int cnt[3];
int sum;
il void solve()
{
	sum=cnt[0]=cnt[1]=cnt[2]=0;
	cin>>n;
	for(int i=1;i<=n;++i)
	{
		cin>>a[i];
		++cnt[a[i]%mod];
		sum+=a[i]%mod;
	}
	sum%=mod;
	if(sum==0)
		cout<<0<<'\n';
	else if(sum==1)
	{
		if(cnt[1])
			cout<<1<<'\n';
		else
			cout<<2<<'\n';
	}
	else
		cout<<1<<'\n';
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
		solve();
	return 0;
}
```

---

## 作者：szhqwq (赞：2)

## 思路

我们可以先统计出数组 $a_i$ 之和模 $3$ 的模数，记为 $x$。

对于 $x$，可以进行分类讨论：

1. 当 $x = 0$ 时，不需要进行任何操作；

2. 当 $x = 1$ 时，如果存在 $a_i \bmod 3 = 1$，则我们可以直接删除这个数，只需进行一次操作，否则，我们必须进行两次操作才能够满足题目条件；

3. 当 $x = 2$ 时，将值增加一就能满足题目条件。

[Link](https://codeforces.com/contest/1933/submission/249034993)

---

## 作者：Infinite_Loop (赞：1)

# CF1933B
## 题意
有 $t$ 组数据，每组数据给定一个长度为 $n$ 的数组 $a _ {i}$，你可以执行以下两种操作：

- 从数组中删除一个元素。
- 将数组中的一个元素的值 $+1$。

求让数组 $a$ 所有元素的和除以 $3$ 的余数等于 $0$ 的最小操作数量。
## 思路
我们可以先求出数组 $a$ 中所有元素的和 $sum$ 和 数组 $a$ 中是否有元素除以 $3$ 的余数等于 $1$。如果 $sum \bmod 3 = 0$，输出 $0$。如果 $sum \bmod 3 = 1$，如果有除以 $3$ 等于 $1$ 的元素，输出 $1$；如果没有除以 $3$ 等于 $1$ 的元素，输出 $2$。如果 $sum \bmod 3 = 2$，输出 $1$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int t,n,a[N];
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		int sum=0,s1=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			sum+=a[i];
			if(a[i]%3==1)s1++;
		}
		if(sum%3==0)cout<<0<<'\n';
		else if(sum%3==1){
			if(s1!=0)cout<<1<<'\n';
			else cout<<2<<'\n';
		}else cout<<1<<'\n';
	}
	return 0;
}
```

---

## 作者：__YSC__ (赞：1)

# 题目描述

给定一个数组 $A$，每次行动你可以执行以下两种中的一种：

- 删除一个元素。
- 使一个元素加一。

求最少进行多少次操作可以使 $\sum \limits_{i=1}^N A_i \equiv 0(\operatorname{mod} 3)$。

# 思路

分类讨论：

- $\sum \limits_{i=1}^N A_i \equiv 0(\operatorname{mod} 3)$，很明显答案为 $0$。
- $\sum \limits_{i=1}^N A_i \equiv 1(\operatorname{mod} 3)$：
	+ $\exists A_i \equiv 1(\operatorname{mod} 3)$，则可以把 $A_i$ 删掉，所以答案为 $1$。
    + 否则，只能加两次 $1$，所以答案为 $2$。
- $\sum \limits_{i=1}^N A_i \equiv 2(\operatorname{mod} 3)$，则直接加 $1$，所以答案为 $1$。

时间复杂度 $O(TN)$，空间复杂度 $O(N)$。

## 细节

**数据千万条，清空第一条。**

**多测不清空，爆零两行泪。**

**清空不规范，超时总相伴。**

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int t, n, cnt[3], sum;

void Solve() {
  cin >> n;
  cnt[0] = cnt[1] = cnt[2] = sum = 0;
  for(int i = 1, x; i <= n; ++i) {
    cin >> x;
    cnt[x % 3]++;
    sum = (sum + x % 3) % 3;
  }
  cout << (!sum ? 0 : (sum == 2 ? 1 : (cnt[1] ? 1 : 2))) << "\n";
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> t;
  while(t--) {
    Solve();
  }
  return 0;
}

```

---

## 作者：yhylivedream (赞：0)

## 分析

以下记 $sum$ 为数组 $a$ 的总和。

考虑分类讨论：

- $sum \bmod 3 = 0$，这时不用操作，答案为 $0$。

- $sum \bmod 3 = 2$，这时只需把任意一个元素加 $1$ 即可，答案为 $1$。

- $sum \bmod 3 = 1$，如果有一个 $a_i \bmod 3 = 1$ 的话，直接将 $a_i$ 删除即可，否则要把任意一个元素 加 $2$ 才行。

## 代码

```cpp
# include <bits/stdc++.h> 

using namespace std;
using ll = long long;
using PII = pair <int, int>;

int T, n, sum, fl;

signed main () {
	for (cin >> T; T; T --) {
		cin >> n;
		fl = sum = 0;
		for (int i = 1, x; i <= n; i ++) {
			cin >> x;
			sum += x;
			fl |= (x % 3 == 1);
		}
		if (sum % 3 == 0) {
			cout << "0\n";
		} else if ((sum % 3 == 1 && fl) || (sum % 3 == 2)) {
			cout << "1\n";
		} else {
			cout << "2\n";
		}
	}
	return 0;
}
```

---

## 作者：Houkiseino_Kokoro (赞：0)

### $\texttt{B. Turtle Math: Fast Three Task}$
#### [原题链接](https://codeforces.com/contest/1933/problem/B)
#### 题意简述
给定一个含 $n$ 项的数列 $a$ 和两种操作，在数列非空的前提下，可以任意对数列执行以下两种操作之一：

1. 选定一个数列中的元素，将其从数列中移除。
2. 选定一个数列中的元素，令其自增 $1$。

现要使数列各元素之和能被 $3$ 整除，求最少要执行几次操作。
#### 解法
根据模运算的性质，可以先预处理，将所有元素对 $3$ 求余后相加。

显然分类讨论，设预处理后得到的和为 $s$，可分为 $3$ 种情况：

- $s\mid3$。显然此时不需要执行任何操作，故输出 `0`。
- $s \equiv 2 \pmod 3 $。显然一种最优解是任选一个元素令其自增 $1$，故输出 `1`。
- $s \equiv 1 \pmod 3 $。通过样例提示可以得知，仅当 $s$ 只由 $2$ 相加得到时至少需要 $2$ 次操作才能使 $s\mid3$。若 $s$ 的加数中有 $1$，则可以直接将其删去，这仅需 $1$ 次操作。

因此，在预处理同时开一个 `std::map` 记录出现的余数的个数，分类判断即可。
#### 代码
```cpp
void solve()
{
    int n;
    long long sum = 0;
    std::cin >> n;
    std::vector<int> arr(n + 1);
    std::map<int, int> cnt; // 记录余数
    for (size_t i = 1; i <= n; i++)
    {
        std::cin >> arr[i];
        sum += arr[i] % 3;
        cnt[arr[i] % 3]++;
    }
    if (sum % 3 == 2)
    {
        std::cout << 1 << '\n';
    }
    else if (sum % 3 == 0)
    {
        std::cout << 0 << '\n';
    }
    else
    {
        if (cnt[1]) 
        {
            std::cout << 1 << '\n';
        }
        else
        {
            std::cout << 2 << '\n';
        }
    }
}
```

---

## 作者：Programming_Konjac (赞：0)

# 翻译
给定一个数组 $a$，每次进行以下两种操作之一：

1. 删除一位，长度减 $1$。

2. 将第 $x(1\le x \le n)$ 位进行加 $1$。

要是和为 $3$ 的倍数，求最小操作步数。
# 思路和证明
我们发现，答案只能是 $0,1,2$，因为其他的数减去 $3$ 的倍数就相当于是这些数，所以确定了答案范围，所以进行分类讨论：

- $0$ 的情况：

1. 和为 $3$ 的倍数，这个不需要证明。

- $1$ 的情况：

1. 和取余 $3$ 为 $2$，证明：将其中一个数加 $1$ 就满足条件了。

2. 如果总和取余 $3$ 等于 $1$ 并且数组中有取余 $3$ 余 $1$ 的数，证明：把这个数删除就满足条件了。

- $2$ 的情况：

1. 如果总和取余 $3$ 等于 $1$ 并且数组中**没**有取余 $3$ 余 $1$ 的数，证明：把其中一个数加上 $2$ 次 $1$，就能满足条件。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
	int t;
	cin>>t;
	while(t--){
		int n,flag=0,a[100005],sum=0;
		cin>>n;
		for(int i=1; i<=n; i++){
			cin>>a[i];
			sum+=a[i];
			if(a[i]%3==1){
				flag=1;
			}
		}
		if(sum%3==0) cout<<0<<endl;
		else if(sum%3==2) cout<<1<<endl;
		else cout<<(flag==1?1:2)<<endl;
	}
	return 0;
} 
```

---

