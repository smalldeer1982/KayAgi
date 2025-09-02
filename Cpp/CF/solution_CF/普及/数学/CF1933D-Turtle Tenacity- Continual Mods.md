# Turtle Tenacity: Continual Mods

## 题目描述

Given an array $ a_1, a_2, \ldots, a_n $ , determine whether it is possible to rearrange its elements into $ b_1, b_2, \ldots, b_n $ , such that $ b_1 \bmod b_2 \bmod \ldots \bmod b_n \neq 0 $ .

Here $ x \bmod y $ denotes the remainder from dividing $ x $ by $ y $ . Also, the modulo operations are calculated from left to right. That is, $ x \bmod y \bmod z = (x \bmod y) \bmod z $ . For example, $ 2024 \bmod 1000 \bmod 8 = (2024 \bmod 1000) \bmod 8 = 24 \bmod 8 = 0 $ .

## 说明/提示

In the first test case, rearranging the array into $ b = [1, 2, 3, 4, 5, 6] $ (doing nothing) would result in $ 1 \bmod 2 \bmod 3 \bmod 4 \bmod 5 \bmod 6 = 1 $ . Hence it is possible to achieve the goal.

In the second test case, the array $ b $ must be equal to $ [3, 3, 3, 3, 3] $ , which would result in $ 3 \bmod 3 \bmod 3 \bmod 3 \bmod 3 = 0 $ . Hence it is impossible to achieve the goal.

In the third test case, rearranging the array into $ b = [3, 2, 2] $ would result in $ 3 \bmod 2 \bmod 2 = 1 $ . Hence it is possible to achieve the goal.

## 样例 #1

### 输入

```
8
6
1 2 3 4 5 6
5
3 3 3 3 3
3
2 2 3
5
1 1 2 3 7
3
1 2 2
3
1 1 2
6
5 2 10 10 10 2
4
3 6 9 3```

### 输出

```
YES
NO
YES
NO
YES
NO
YES
NO```

# 题解

## 作者：szhqwq (赞：9)

## 思路

妙妙题。

首先当数组 $a$ 中没有重复的数时，可以想到将其从小到大排序，这样一定能够使得题目要求的值不为 $0$。

但是显然会有重复的数，令数组 $a$ 从小到大排序后为数组 $b$，可以发现，只要排序后最小的那个数只有一个的话（即 $b_1 \ne b_2$），最后的值同样为 $0$。那么当存在有多个最小数的话，只需要看是否存在 $i$ 有 $b_i \ne b_1$ 且 $b_i \bmod b_1 \ne 0$ 即可。这样我们将这个 $b_i$ 放在 $b_1$ 的前面，就能使题目要求的值为 $0$。

[Link](https://codeforces.com/contest/1933/submission/249034426)

---

## 作者：IOI_official (赞：3)

## 思路：

此题其实很简单，不要被邪恶的出题人迷惑了双眼。

此题判断有解一共有两种情况。

通过题意可以知道将原数组排序后如果 $b_{1} \ne b_{2}$，那么最后的结果一定 $\ne 0$，这是第一种情况。

第二种情况其实就是第一种情况的变形，在排序后 $b_{1} = b_{2}$ 的情况下，如果 $b$ 中有一个数 $\bmod b_{1} \ne 0$，就可以把这个数放在第一位来满足第一种情况，所以输出 YES。

除这两种情况外其它都无解。

## AC 代码：

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int n,a[114514],m;
bool f;
int main() {
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>m;
		for(int j=1; j<=m; j++){
			cin>>a[j];
		}
		sort(a+1,a+m+1);
		if(a[1]!=a[2]) {
			cout<<"YES"<<endl;
			continue;
		}
		else {
			f=0;
			for(int j=2; j<=m; j++){
				if(a[j]%a[1]!=0){
					f=1;
				}
			}
			if(f==1){
				cout<<"YES"<<endl;	
			}
			else{
				cout<<"NO"<<endl;
			}
		}
	}
	return 0;
}
```

---

## 作者：__YSC__ (赞：3)

# 题目描述

给定一个数组 $\{A_1,A_2,\dots,A_N\}$，请判断是否能通过改变其顺序使得 $A_1 \bmod A_2 \bmod \dots \bmod A_N \ne 0$。

# 思路

可以发现，如果满足要求只有两种情况：

- $A_1 \le A_2 \le \dots \le A_N 且 A_1 \bmod A_2 \bmod \dots \bmod A_N \ne 0$
- $\exists A_i使得A_i \not \equiv 0 \pmod {\min \limits_{x=1}^N \{A_x\}})$，因为在这时余数肯定小于最小值，即小于所有值，所以最终答案肯定不为 $0$。

时间复杂度 $O(TN \log N)$，空间复杂度 $O(N)$。

## 细节

无。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 100001;

int t, n, a[MAXN];

bool check() {
  int m = a[1];
  for(int i = 2; i <= n; ++i) {
    m %= a[i];
    if(!m) {
      return 0;
    }
  }
  return 1;
}

bool Check() {
  for(int i = 1; i <= n; ++i) {
    if(a[i] % a[1]) {
      return 1;
    }
  }
  return 0;
}

void Solve() {
  cin >> n;
  for(int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  sort(a + 1, a + n + 1);
  cout << (check() || Check() ? "YES\n" : "NO\n");
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

## 作者：2huk (赞：2)

## Description

给定一个长度为 $n$ 的数组 $a$。你需要将其重新排列成数组 $b$，判断是否存在一种方案使得 $b_1 \bmod b_2 \bmod \dots \bmod b_n \ne 0$。

多测。$1 \le t \le 10^4$，$2 \le n \le 10^5$，$\bm 1 \le a_i \le 10^9$。

## Solution

注意到 $a_i \ge 1$。而我们又有在 $x < y$ 时：

$$
x \bmod y = x
$$

所以很自然的想法就是把 $a_i$ 从小到大排序。例如 $a = \{1, 2, 3, 4, 5\}$，那么答案为 $a_1 \bmod a_2 \bmod a_3 \bmod a_4 \bmod a_5 = a_1 = 1$。

这样做可能会出现问题。如果 $a_1 \bmod a_2 = 0$，那么最终的 $a_1 \bmod \dots \bmod a_n$ 一定为 $0$。这样的话，我们做下面的处理。

我们肯定是希望将 $a_1$ 换成某一个别的数 $a_i(2 \le i \le n)$。此时原答案为 $a_i \bmod a_2 \bmod a_3 \bmod \dots \bmod a_1 \bmod \dots \bmod a_n$。那么我们此时只需要判断 $a_i \bmod a_2$ 是否为 $0$。只要存在一个 $i$ 满足 $a_i \bmod a_2 \ne 0$，答案为 YES。

## Code

```cpp
// LUOGU_RID: 148849197
#include <bits/stdc++.h>

using namespace std;

//#define int long long
typedef long long ll;
typedef unsigned long long LL;
typedef pair<int, int> PII;

struct FASTREAD {
	template <typename T>
	FASTREAD& operator >>(T& x) {
		x = 0; bool flg = false; char c = getchar();
		while (c < '0' || c > '9') flg |= (c == '-'), c = getchar();
		while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + c - '0', c = getchar();
		if (flg) x = -x; return *this;
	}
	template <typename T>
	FASTREAD& operator >>(vector<T>& x) {
		for (auto it = x.begin(); it != x.end(); ++ it ) (*this) >> *it;
		return *this;
	}
}fin;

struct FASTWRITE {
	template <typename T>
	FASTWRITE& operator <<(T x) {
		if (x < 0) x = -x, putchar('-');
		static int buf[35]; int top = 0;
		do buf[top ++ ] = x % 10, x /= 10; while (x);
		while (top) putchar(buf[ -- top] + '0');
		return *this;
	}
	FASTWRITE& operator <<(char x) {
		putchar(x); return *this;
	}
	template <typename T>
	FASTWRITE& operator <<(vector<T> x) {
		for (auto it = x.begin(); it != x.end(); ++ it ) (*this) << *it, putchar(' ');
		putchar('\n');
		return *this;
	}
}fout;

const int N = 1e6 + 10;
const int P = 998244353;

void Luogu_UID_748509() {
	int n; fin >> n;
	vector<int> a(n);
	fin >> a;
	
	sort(a.begin(), a.end());
	bool flg = false;
	if (a[0] != a[1]) flg = true;
	else {
		for (int i = 1; i < n; ++ i ) {
			if (a[i] % a[0]) flg = true;
		}
	}
	
	puts(flg ? "YES" : "NO");
}

signed main() {
	int Testcases = 1;
	fin >> Testcases;
	while (Testcases -- ) Luogu_UID_748509();
	return 0;
}
```

---

## 作者：appear_hope (赞：2)

考虑什么样会同时取模两个数为 $0$，显然是这两个数的最大公因数的因数，这个最大公因数的因数是小于等于这两个数的。

那么对于一个长度为 $N$ 的序列是同理的。

我们接下来只考虑这个序列的最大公因数，为什么不去考虑最大公因数的因数（不包括本身），因为一个数的因数不包括本身那么剩下的因数肯定是小于这数的，首先这个序列的最大公因数是小于等于这个序列的最小值的，所以这个序列的最小公因数不包括自己的因数肯定是小于这个序列的最小值的，而这个题目是要求通过调换顺序使得不存在那样的情况，所以我们并不需要考虑这个序列的最大公因数的因数。

如果这个序列中不存在这个序列的最大公因数当然是合理的。

如果这个序列存在一个这个序列的最大公因数我们可以把这个数放在 $b_1$ 的位置。

如果这个序列存在两个及以上的这个序列的最大公因数，仔细思考，肯定是不合法的。（整个序列的最大公因数是小于等于这个序列的，所以最大公因数他在取模意义下模这个序列中的数只会变成原数或 $0$，而若有两个及以上的最最大公因数，意味这取模出的数一定会是 $0$）

令 $V = \max \limits_{i = 1}^{n} a_i$。

时间复杂度：$O(n \log_{2} V)$。

代码如下：

```cpp
#include<bits/stdc++.h>

using namespace std;

int T, n;

int gcd(int a, int b){
  return !b ? a : gcd(b, a % b);
}

void Solve(){
  cin >> n;
  int Gcd = INT_MAX;
  map<int, int> mp;
  for(int i = 1, x; i <= n; i++){
    cin >> x;
    Gcd = min(Gcd, x);
    mp[x]++;
  }
  cout << (mp.find(Gcd) != mp.end() && mp[Gcd] > 1 ? "NO" : "YES") << '\n';
}

int main(){
  ios::sync_with_stdio(0), cin.tie(0);
  for(cin >> T; T--; Solve()){
  }
  return 0;
}

```

---

## 作者：minVan (赞：1)

**题目大意**

给定序列 $a_1,a_2,\cdots,a_n$，重新排列为 $b_1,b_2,\cdots,b_n$ 后，是否能使得 $b_1\bmod b_2\bmod\cdots b_n\neq0$。

**解题思路**

将 $a$ 数组从小到大排序，如果最小值唯一，那此时答案为 $a_1$ 不等于 $0$，符合题意；否则代表最小值不唯一，看 $a_2\sim a_n$ 中是否有不被 $a_1$ 整除的，不妨设为 $a_i$，则 $a_i\bmod a_1\in\mathbb{R}^+$ 且其小于 $a_1$ 小于 $a_2$ 唯一，那么最终答案为 $a_i\bmod a_1$ 符合题意。

**AC 代码，请勿抄袭。**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 5;
int n, a[N];
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while(t--) {
    bool flag = 0;
    cin >> n;
    for(int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    sort(a + 1, a + n + 1);
    if(a[1] != a[2]) {
      cout << "YES\n";
      continue;
    }
    for(int i = 2; i <= n; i++) {
      if(a[i] % a[1]) {
        flag = 1;
        break;
      }
    }
    if(flag) { cout << "YES\n"; }
    else { cout << "NO\n"; }
  }
  return 0;
}
```

---

## 作者：Stars_visitor_tyw (赞：1)

## 题解：CF1933D Turtle Tenacity: Continual Mods
### 分析
将数组排序，若此时 $a_1 < a_2$，则 $a_1 \bmod a_2$ 不为 $0$，而 $a_3,a_4,…,a_n$ 都比 $a_1 \bmod a_2$ 大，则最终结果为 $a_1$，输出 `YES`。

否则就拿数组中其他元素对 $a_1$ 取模，只要有一个数对 $a_1$ 取模的结果不为 $0$，则最终结果不为 $0$，输出 `YES`。

最后如果上述条件都不满足，输出 `NO`。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t, n, a[100005];
signed main()
{
    int t;
    for(cin>>t;t;t--)
    {
        cin>>n;
        for(int i=1;i<=n;i++)
        {
            cin>>a[i];
        }
        sort(a+1,a+1+n);
        if(a[1]<a[2])
        {
            cout<<"YES\n";
            continue;
        }
        bool f=0;
        for(int i=2;i<=n;i++)
        {
            if(a[i]%a[1]!=0)
            {
                cout<<"YES\n";
                f=1;
                break;
            }
        }
        if(!f)cout<<"NO\n";
    }
}
```

---

## 作者：OPEC (赞：0)

# [Turtle Tenacity: Continual Mods](https://www.luogu.com.cn/problem/CF1933D)
因为小数除以大数的余数仍然是小数，所以这题只需要判断最小数是否相同，如果相同，则输出 YES。否则，寻找一个模最小数不为零的数，这样余数就会比最小数更小。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define int long long
const int N=1e6+10,M=2e6+10;
const int INF=0x3f3f3f3f3f3f3f3f;
const int P=998244353;//3221225477
int t;
int a[N];
void solve()
{
	//不要抄题解 QAQ
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	if(a[1]!=a[2])
	{
		cout<<"YES\n";
		return;
	}
	for(int i=2;i<=n;i++)
	{
		if(a[i]%a[1])
		{
			cout<<"YES/n";
			return;
		}
	}
	cout<<"NO/n";
}
signed main()
{
	fst
	cin>>t;
	while(t--)
	{
		solve();
	}
	return 0;
}
```

---

## 作者：yhylivedream (赞：0)

## 分析

考虑先将数组排序。

发现如果 $a_1<a_2<a_3<\cdots< a_n$，那么最后的答案就是 $a_1$，输出 `YES`。

否则可以依次用 $a_2,a_3,\cdots,a_n$ 对 $a_1$ 取余，如果余数不为 $0$ 的话，那么其范围肯定在 $1 \sim a_1-1$ 之间，这时上面的条件就满足了，输出 `YES`。

如果都不满足就输出 `NO`。

## 代码

```cpp
# include <bits/stdc++.h> 

using namespace std;
using ll = long long;
using PII = pair <int, int>;

const int N = 2e5 + 5;
ll T, n, a[N];

signed main () {
  for (cin >> T; T; T --) {
    cin >> n;
    for (ll i = 1; i <= n; i ++) {
      cin >> a[i];
    }
    sort (a + 1, a + n + 1);
    if (a[1] != a[2]) {
      cout << "YES\n"; continue;
    }
    bool fl = 0;
    for (ll i = 2; i <= n; i ++) {
      ll t = a[i] % a[1];
      if (t) {
        cout << "YES\n";
        fl = 1; break;
      }
    }
    !fl && (cout << "NO\n");
  }
  return 0;
}
```

---

## 作者：hytallenxu (赞：0)

## 题目大意
有一个序列 $arr$，问这个序列有无一种排列方式使得 $arr_1 \bmod arr_2 \dots \bmod arr_n \neq 0$。

## 思路
我们先对数组进行排序，然后分情况讨论。

### Case 1

如图，

![](https://cdn.luogu.com.cn/upload/image_hosting/6nt2aq8q.png)

假如排序后 $arr_1 \neq arr_2$，即可以使得条件成立（想想，为什么？），所以排序就是一种合法方案，输出 ```YES```。

### Case 2

如图，

![](https://cdn.luogu.com.cn/upload/image_hosting/3kbtz9dm.png)

这里的情况是排序后 $arr_1 = arr_2$ 的情况。

这个时候我们要往后找一个 $arr_i$，使得 $arr_i \bmod arr_1 \neq 0$，这样就可以把 $arr_i$ 放在第一位，从而保证了条件。

剩下的情况就是 $arr$ 数组中其他所有数都是排序后 $arr_1$ 的倍数，且 $arr_1=arr_2$（即 $arr_1/arr_2$ 是所有数的**最小公约数**）。在这种情况下，任意排序方法都会使得，在 $arr_1/arr_2$ 的位置之前，柿子的结果就已经成为了 $arr_1/arr_2$ 的倍数，即这种情况无解。

所以，这种情况输出 ```NO```。

## Code

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int arr[100001];
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)cin>>arr[i];
		sort(arr+1,arr+1+n);
		if(arr[1]!=arr[2]){
			cout<<"YES\n";
			continue;
		}else{
			bool flag=0;
			for(int i=2;i<=n;i++) if(arr[i]%arr[1]!=0) flag=1;
			if(flag) cout<<"YES\n";
			else cout<<"NO\n";
		}
	}
	return 0;
}
```

---

## 作者：Houkiseino_Kokoro (赞：0)

### $\texttt{D. Turtle Tenacity: Continual Mods}$
#### [原题链接](https://codeforces.com/contest/1933/problem/D)
#### 题意简述
给定一个含 $n$ 项的数列 $a$。问能否重排数列，使得 $( \ldots ((a_1 \bmod a_2) \bmod a_3) \ldots ) \bmod a_n \ne 0$。
#### 解法
赛场上差一点做出来这道题，因此挨了大刀。

我这种蒟蒻确实不知道怎么处理这种连续求余式，于是只能根据样例一点一点猜结论了。

首先把样例推了推后容易发现一个结论：设 $r$ 为经过若干次求余运算后的结果，$m$ 为剩余所有未进行求余运算的元素中的最小值，若可以通过重排数列使 $r < m$ 且 $r \ne 0$，则必能满足题目的要求。

这个结论是显然的：不妨任设一个 $m$ 项数列 $b$ 与一个数 $p$ 满足 $\forall i \in \left[1,m\right], p < b_i$，总有 $\forall i \in \left[1,m\right], p \bmod b_i = p \ne 0$。

因此，我们对数列由小到大进行排序，可以得到数列的最小值 $a_1$。若等于最小值的元素只有一个，则直接满足上述结论，输出 `Yes`；若有多个，考虑到模运算一个显然的性质是 $a \bmod b < b$，可让数列其余元素分别模最小值。若能找到一个元素 $a_i$ 使 $a_i \bmod a_1 \ne 0$，同样可以得到上述结论需要的小于最小值的结果，输出 `Yes`；否则输出 `No`。

#### 代码
```cpp
void solve()
{
    int n, tmp;
    std::cin >> n;
    std::multiset<int> arr;
    std::map<int, int> cnt;
    for (size_t i = 1; i <= n; i++)
    {
        std::cin >> tmp;
        arr.insert(tmp);
    }
    if (arr.count(*arr.begin()) == 1)
    {
        std::cout << "YES" << std::endl;
    }
    else
    {
        for (int i : arr)
        {
            if (i % *arr.begin())
            {
                std::cout << "YES" << std::endl;
                return;
            }
        }
        std::cout << "NO" << std::endl;
    }
}
```

---

