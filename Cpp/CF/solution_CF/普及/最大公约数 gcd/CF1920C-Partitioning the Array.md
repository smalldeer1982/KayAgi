# Partitioning the Array

## 题目描述

Allen has an array $ a_1, a_2,\ldots,a_n $ . For every positive integer $ k $ that is a divisor of $ n $ , Allen does the following:

- He partitions the array into $ \frac{n}{k} $ disjoint subarrays of length $ k $ . In other words, he partitions the array into the following subarrays: $ $$$[a_1,a_2,\ldots,a_k],[a_{k+1}, a_{k+2},\ldots,a_{2k}],\ldots,[a_{n-k+1},a_{n-k+2},\ldots,a_{n}] $ $  </li><li> Allen earns one point if there exists some positive integer  $ m $  ( $ m \\geq 2 $ ) such that if he replaces every element in the array with its remainder when divided by  $ m$$$, then all subarrays will be identical.

Help Allen find the number of points he will earn.

## 说明/提示

In the first test case, $ k=2 $ earns a point since Allen can pick $ m = 2 $ and both subarrays will be equal to $ [1, 0] $ . $ k=4 $ also earns a point, since no matter what $ m $ Allen chooses, there will be only one subarray and thus all subarrays are equal.

In the second test case, Allen earns $ 1 $ point for $ k=3 $ , where his choice for $ m $ does not matter.

## 样例 #1

### 输入

```
8
4
1 2 1 4
3
1 2 3
5
1 1 1 1 1
6
1 3 1 1 3 1
6
6 2 6 2 2 2
6
2 6 3 6 6 6
10
1 7 5 1 4 3 1 3 1 4
1
1```

### 输出

```
2
1
2
4
4
1
2
1```

# 题解

## 作者：Luzhuoyuan (赞：13)

### 题目链接

[[to Codeforces]](https://codeforces.com/contest/1920/problem/C) [[to Luogu]](https://www.luogu.com.cn/problem/CF1920C)

### 题意简述

给定一个长为 $n$ 的序列 $a$，对于 $n$ 的**每个**正因子 $k$，将 $a$ 分为 $\frac{n}{k}$ 个长为 $k$ 且不相交的子串，即分为：

$$[a_1,a_2,\dots,a_k],[a_{k+1},a_{k+2},\dots,a_{2k}],\dots,[a_{n-k+1},a_{n-k+2},\dots,a_n]$$

如果存在一个正整数 $m$ 使得 $m\ge 2$ 且将 $a$ 中每个元素 $a_i$ 替换为 $a_i\bmod m$ 后分成的每个子串都相等，那么你得到一分。求最终的总分。每个测试点 $t$ 组测试用例。

$$1\le t\le 10^4;1\le n,\sum n\le 2\cdot 10^5;1\le a_i\le n$$

### 做法

这是一道暴力题。

我们考虑枚举 $n$ 的因数 $k$ 并对每个 $k$ 求分数。有一个显然的性质：若 $x\equiv y\pmod m$，则有 $m|(x-y)$。所以我们对于每个 $|a_i-a_{i-k}|(k<i\le n)$ 求 $\gcd$，若最终值大于等于 $2$ 则答案加一。由于过程中 $\gcd$ 会逐渐减小且至多减小 $\log n$ 次，因此该过程复杂度为 $O(n+\log n)=O(n)$。总复杂度为 $O(n\sqrt n)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int T,n,a[N],ans;
inline int read(){
    int x=0;
    char c=getchar();
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x;
}
inline bool work(int x){
    int g=0;
    for(int i=x+1;i<=n;i++){
        int t=abs(a[i]-a[i-x]),tmp=0;
        while(t)tmp=g%t,g=t,t=tmp;
        if(g==1)return false;
    }
    return true;
}
signed main(){
    T=read();
    while(T--){
        n=read();ans=0;
        for(int i=1;i<=n;i++)a[i]=read();
        for(int i=1;i*i<=n;i++)
            if(n%i==0){
                ans+=work(i);
                if(i*i!=n)ans+=work(n/i);
            }
        printf("%d\n",ans);
    }
    return 0;
}
```

（逃

---

## 作者：mountain_climber (赞：3)

#### 题目分析

考虑一下数据范围，发现可以接受暴力枚举所有因数，然后挨个判断是否对答案产生贡献。

对于因数 $n$ 来说，一定对答案产生贡献，因为只分成了一段。

对于因数 $k$，考虑将 $a$ 分成相等的 $\frac{n}{k}$ 段，有 $a_{i} \equiv a_{i+k} \pmod m$，于是有 $m \mid |a_{i}-a_{i+k}|$，注意到 $2 \leq m$，所以当 $\gcd(|a_{1}-a_{1+k}|,|a_{2}-a_{2+k}|t,\ldots,|a_{n-k}-a_{n} |) \neq 1$ 时，存在一个满足条件的模数 $m$，即因数 $k$ 对答案产生贡献。

#### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
const int N=2e5+10;
int t,n,a[N];
void ipt(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]); 
}
int gcd(int x,int y){
	return !y?x:gcd(y,x%y); 
}
bool check(int k){
	if(k==n) return true;
	int m=abs(a[1]-a[1+k]);
	for(int i=1;i<=n-k;i++){
		m=gcd(abs(a[i]-a[i+k]),m);
		if(m==1) return false;
	}
	return true;
}
void solve(){
	int ans=0;
	for(int i=1;i<=n;i++){
		if(n%i) continue;
		ans+=check(i); 
	}
	printf("%d\n",ans);
}
int main(){
	scanf("%d",&t);
	while(t--){
		ipt();
		solve();
	}
	return 0;
} 
```


---

## 作者：Zemu_Ooo (赞：3)

对于每个 $k$，检查是否存在一个整数 $m \geq 2$，使得将数组中的每个元素除以 $m$ 后的余数都相同。如果满足这个条件，那么所有的子数组在这个操作下都将变得相同。

对于每个测试用例，找出 $n$ 的所有除数，然后将数组分成长度为 $k$ 的子数组。其次，对于每个子数组，尝试不同的 $m$ 值，检查将数组中的每个元素除以 $m$ 后的余数是否都相同。如果对于某个 $k$ 找到了满足条件的 $m$，则增加 Alen 得分。

使用哈希表来存储每个子数组的模 $m$ 余数模式很高效。

第一版：

```cpp
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

vector<int> findDivisors(int n) {
    vector<int> divisors;
    for (int i = 1; i <= n / i; ++i) {
        if (n % i == 0) {
            divisors.push_back(i);
            if (i != n / i) divisors.push_back(n / i);
        }
    }
    return divisors;
}

bool checkEqual(vector<int>& arr, int k, int m) {
    for (int i = 0; i < k; ++i) {
        int remainder = arr[i] % m;
        for (int j = i + k; j < arr.size(); j += k) {
            if (arr[j] % m != remainder) return false;
        }
    }
    return true;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int& ai : a) cin >> ai;

        vector<int> divisors = findDivisors(n);
        int score = 0;
        for (int k : divisors) {
            for (int m = 2; m <= n; ++m) {
                if (checkEqual(a, k, m)) {
                    score++;
                    break;
                }
            }
        }
        cout << score << endl;
    }
    return 0;
}
```

然后发现输出变成：

```
2
1
2
4
4
1
2
0
```

重新排查了一遍，才发现问题出在处理单个元素数组的情况上（

在这种情况下应该总是增加一分，因为只有一个子数组，所以无论 $m$ 的值如何，它总是与自身相同。

所以我改成了首先检查是否只有一个子数组（即 $k = n$）。如果是这样，就直接增加一分。其他情况则继续检查是否存在一个合适的 $m$。

```cpp
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

vector<int> findDivisors(int n) {
    vector<int> divisors;
    for (int i = 1; i <= n / i; ++i) {
        if (n % i == 0) {
            divisors.push_back(i);
            if (i != n / i) divisors.push_back(n / i);
        }
    }
    return divisors;
}

bool checkEqual(vector<int>& arr, int k, int m) {
    for (int i = 0; i < k; ++i) {
        int remainder = arr[i] % m;
        for (int j = i + k; j < arr.size(); j += k) {
            if (arr[j] % m != remainder) return false;
        }
    }
    return true;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int& ai : a) cin >> ai;

        vector<int> divisors = findDivisors(n);
        int score = 0;
        for (int k : divisors) {
            if (k == n) {
                score++;
                continue;
            }
            for (int m = 2; m <= n; ++m) {
                if (checkEqual(a, k, m)) {
                    score++;
                    break;
                }
            }
        }
        cout << score << endl;
    }
    return 0;
}
```

---

## 作者：huangrenheluogu (赞：0)

考虑到 $n$ 的因数不会很多，考虑枚举因数然后 $O(n\log n)$ 判断。

假设我们取了 $m$，此时区间长度是 $k$。

$a_i\equiv a_{i+1}\pmod m\Leftrightarrow m|(a_i-a_{i+1})$，所以只要 $a_i$ 和 $a_{i+k}$ 的差值求 gcd 就好了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int n, g, a[N], T, ans;
inline bool check(int x){
	if(x == n) return 1;
	g = abs(a[1 + x] - a[1]);
	for(int i = 1; i <= n - x; i++){
		g = __gcd(g, abs(a[i + x] - a[i]));
		if(g == 1) return 0;
	}
	return 1;
}
int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		ans = 0;
		for(int i = 1; i * i <= n; i++){
			if(n % i == 0){
				if(check(i)) ans++;
				if(n / i != i && check(n / i)) ans++;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：kczw (赞：0)

# 题意
共 $t$ 组数据，每组数据给定一个 $n$ 的序列 $a$。

$k$ 为 $n$ 的因数，将序列 $a$ 依次分成 $\frac{n}{k}$ 个长度均为 $k$ 的序列。对于每个 $k$ 若有 $m(m\ge 2)$ 让序列 $a$ 的所有元素对 $m$ 取模后可以使 $\frac{n}{k}$ 个序列相等，那么分值加一。

问对于每组数据给定 $a$，分值应该为多少。
# 思路
首先因为要处理 $t\le10^4$ 组数据，所以要预处理出每一个 $n\le2\times10^5$ 的因数，方便使用。

然后，这道题是可以暴力枚举的。

每次有一个 $n$，我们遍历其所有 $k$，然后判断是否有 $m\ge2$ 可使得这 $\frac{n}{k}$ 序列对应的元素同余即可。

关于怎么找 $m$，首先要知道 $a_i\equiv 
a_{i+k}\pmod{m}$，我们知道最大 $m$ 为 $|a_i-a_{i+k}|$。但是这里不止有两个数，所以我们要对所有求出来的类 $|a_i-a_{i+k}|$ 求最小公因数，这样也可以保证同余。

当 $\gcd(a_i-a_{i+k},a_{i+k}-a_{i+k\times2}\dots)$ 等于 $1$ 时，就说明不符合要求，此时直接枚举下一个 $k$。

这里可以知道当 $n$ 为 $120120$ 时最多有 $2^7=128$ 种不同的 $k$，通过分析 $n$ 和 $k$ 数据量不难发现极限情况下也能通过此题。

最后，我们只需要枚举 $k$，然后对于每个 $k$ 检查 $\frac{n}{k}$ 个序列对应的部分同余时的最大模数 $m$ 是否合格，然后计数即可。
# 思路
```cpp
#include<iostream>
#include<vector>
#define abs(x) (x<0?-x:x)
using namespace std;
inline int gcd(int a,int b){return b==0?a:gcd(b,a%b);}
vector<int> num[200005];
int t,n,a[200005];
int main(){;
    for(int i=1;i<=200000;i++)
    for(int j=i;j<=200000;j+=i)
        num[j].push_back(i);
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        int cd,lst,ans=0;
        for(auto siz:num[n]){
            cd=0;
            for(int i=1;i<=siz&&(cd==0||cd>=2);i++){
                lst=a[i];
                for(int j=i+siz;j<=n&&(cd==0||cd>=2);j+=siz){
                    cd=gcd(cd,abs((a[j]-lst)));
                    lst=a[j];
                }
                
            }
            if(cd==0||cd>=2)ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：Saint_ying_xtf (赞：0)

直接枚举 $i$，为每一段长度为 $i$。

放进一个函数里看是否有一个贡献。

若干个数同余，对于每两个数的差求最大公因数。

接着 $k$ 组的数再求一个最大公因数。

最后不为 $1$ 就说明存在一个答案贡献。

很显然的结论，因为你要模完之后相等，所以要模他们公因数。

时间复杂度应该是 $O(n \sqrt n)$。

[link](https://codeforces.com/contest/1920/submission/241516878)。

---

