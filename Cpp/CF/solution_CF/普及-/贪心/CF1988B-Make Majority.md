# Make Majority

## 题目描述

You are given a sequence $ [a_1,\ldots,a_n] $ where each element $ a_i $ is either $ 0 $ or $ 1 $ . You can apply several (possibly zero) operations to the sequence. In each operation, you select two integers $ 1\le l\le r\le |a| $ (where $ |a| $ is the current length of $ a $ ) and replace $ [a_l,\ldots,a_r] $ with a single element $ x $ , where $ x $ is the majority of $ [a_l,\ldots,a_r] $ .

Here, the majority of a sequence consisting of $ 0 $ and $ 1 $ is defined as follows: suppose there are $ c_0 $ zeros and $ c_1 $ ones in the sequence, respectively.

- If $ c_0\ge c_1 $ , the majority is $ 0 $ .
- If $ c_0<c_1 $ , the majority is $ 1 $ .

For example, suppose $ a=[1,0,0,0,1,1] $ . If we select $ l=1,r=2 $ , the resulting sequence will be $ [0,0,0,1,1] $ . If we select $ l=4,r=6 $ , the resulting sequence will be $ [1,0,0,1] $ .

Determine if you can make $ a=[1] $ with a finite number of operations.

## 说明/提示

In the fourth testcase of the example, initially $ a=[1,0,0,0,0,0,0,0,1] $ . A valid sequence of operations is:

1. Select $ l=2,r=8 $ and apply the operation. $ a $ becomes $ [1,0,1] $ .
2. Select $ l=1,r=3 $ and apply the operation. $ a $ becomes $ [1] $ .

## 样例 #1

### 输入

```
5
1
0
1
1
2
01
9
100000001
9
000011000```

### 输出

```
No
Yes
No
Yes
No```

# 题解

## 作者：shiziyu111 (赞：4)

## 题目大意
给定一个长度为 $n$ 的字符串 $a$，每次可以选择一个 $l$ 和 $r$，使得 $a_l$ 到 $a_r$ 的区间合并，合并操作如下：

记 $c_0$ 为该区间中 $0$ 的长度，$c_1$ 为该区间中 $1$ 的长度。

- 如果 $c_0\ge c_1$，则将区间合并成 $0$。
- 如果 $c_0<c_1$，则将区间合并成 $1$。

问能否使 $a=[1]$。
## 分析
如果要使 $a=[1]$，那么我们就要使 $0$ 尽可能的少，所以先合并所有连在一起的 $0$。

我们再分析假如在合并后 $c_0\ge c_1$，那么再多的合并都无力回天，故输出 ```No```。假如合并后 $c_0<c_1$，那么就简单了，把 $a$ 整体合并就行了，故输出 ```Yes```。

在知道这些后，就到了我们喜爱的：
## 我爱打代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int T;
	cin>>T;
	for(int i=1;i<=T;i++)
	{
		int n,c0=0,c1=0;;
		char a[200005];
		cin>>n;
		cin>>a;
		for(int i=0;i<n;i++)
		{
			if(a[i]=='1')
			{
				c1++;
			}
			else
			{
				if(a[i-1]=='1'||i==0)
				{
					c0++;
				}
			}
		} 
		if(c0>=c1)
		{
			cout<<"No"<<endl;
		}
		else
		{
			cout<<"Yes"<<endl;
		}
	}
	return 0;
}
```

~~都看到这里了，还不点个赞~~。

---

## 作者：qw1234321 (赞：2)

首先，对于两个连续的 `0`，将它们合并成一个新的 `0` 一定更优。

那么会得到一个没有连续的两个 `0` 的字符串，设为 $S$。

定义一次消除操作为：

- 对于不在两端的任意一个 `0`，它的两旁一定为两个 `1`，故可以选择 `101` 这段区间变为 `1`，同时消除了一个 `0` 与一个 `1`。

考虑最终进行若干次上述操作后得到的字符串一定为 `01...10` 或 `1...10` 或 `01...1` 的形式，由于 `1...10` 与 `01...1` 可以看成同一种情况，下面只分类讨论前两种。

- `01...10`

明显需要中间的 `1` 的个数大于 `0` 的个数，而一次消除操作消除的 `0` 与 `1` 的个数明显相等，所以只需要 $S$ 中的 `1` 的个数大于 `0` 即可。

- `1...10`

同上，需要左端连续的 `1` 的个数大于 `0` 的个数，可以推出也只需要 $S$ 中的 `1` 的个数大于 `0` 即可。

综上，若 $S$ 中的 `1` 的个数大于 `0` 输出 `Yes`，否则，输出 `No`。

代码不放了。

---

## 作者：Z3k7223 (赞：1)

## Problem
给定一个 01 序列，每次操作可选择一个区间，将该区间替换为一个该区间的众数（若个数相同则为 0），问能否将该序列变换为一个 1。

## Solution
注意到一串连续的 0 对我们的操作无贡献，所以不妨将连续的 0 化为一个 0，在这样操作完成后，我们可以统计 0 和 1 的个数，记为 $c_0$ 和 $c_1$，有三种情况：

- $c_0 < c_1$，此时直接全部合并即可，有解。
- $c_0 > c_1$，实际上只有 `0101010` 这种情况，此时 $c_0 = c_1 + 1$，考虑若每次操作只将区间合成 1，则 1 的数量只会相对更少，因此无论怎么操作都无法使在最后一次操作前序列中的 1 更多，若合成 0，只可能是合并 `010` 或 `1010` 两种，前者消除后 $c_0 = c_1$，同下文；后者无论怎么操作，$c_0$ 与 $c_1$ 的相对数量都不变，无法在最后一次操作前使 $c_0 < c_1$，故无解。
- $c_0 = c_1$，考虑会出现该情况仅有两种可能，即形如 `10101010` 和 `01101010` 两种，且第二种有且仅有一组位于两端的 `0110`，手推可得两种情况都无解。

代码就很好写了。

### Code

```
#include <bits/stdc++.h>
using namespace std;
char s[200005];
int main(){
    int t,n;
    cin>>t;
    while(t--){
        cin>>n;
        cin>>(s+1);
        int cnt0=0,cnt1=0;
        for(int i=1;i<=n;i++){
            if(s[i]=='1')cnt1++;
            if(s[i]=='0'&&s[i-1]!='0')cnt0++;
        }
        if(cnt1>cnt0)puts("Yes");
        if(cnt1<=cnt0)puts("No");
    }
    return 0;
}
```

---

## 作者：_zqh_ (赞：1)

写一篇没有代码的思路题解。

> 涉及知识点：简单构造

对于任意连续的 $0$，我们可以将其转化成 $1$ 个 $0$，因为若干个 $0$ 的众数一定是 $0$。

考虑用 $1$ 去消除 $0$。

先说结论，化简后的字符串的众数是 $1$ 输出 `Yes`，否则输出 `No`。

接下来讲讲证明；

首先，如果想要让 $0$ 变为 $1$，起码需要 $k+1$ 个 $1$ 和 $k$ 个 $0$，简单来说就是：

$$
(011,101,110) \Rightarrow 1
$$

那么相较于原来，$1$ 减少了 $k$ 个，$0$ 减少了 $k$ 个，相对于整体没变。

接着，如果将 $k + t$ 个 $1$ 和 $k$ 个 $0$ 结合（$t \gt 1$），那么 $1$ 减少了 $k + t - 1$ 个，$0$ 减少了 $k$ 个，相对于整体 $1$ 减少了 $t - 1$ 个，显然不优。

那么只需要用化简后的整体进行判断众数即可。

---

## 作者：Little_Cabbage (赞：1)

# 题目大意

题面写得很清楚，我就不再赘述了。

# 解题思路

> 涉及知识点：字符串，构造。

由于所有相邻的 $0$ 合并完会变成一个 $0$，所以先贪心地把所有挨在一起的 $0$ 合并起来，放在一个新的字符串里。

而且题目需要你判断是否最终是否能合并成一个 $1$，所以 $1$ 是不需要想 $0$ 一样合并的，这样才能保证答案最优。

```cpp
while (now < n) {
		if (s[now] == '1') t += '1', now++;
		else {
			t += '0';
			while (now < n && s[now] == '0') now++;
		}
	}
```

合并完成之后，我们得到了一个对于当前最优的序列，现在只需判断 $0$ 与 $1$ 的大小关系即可。

# 代码

```cpp
#include <bits/stdc++.h>
#define ull unsigned long long
#define int long long
#define ll __int128
#define ldb long double
#define db double
#define bl bool
#define endl '\n'
#define PII pair<int, int>
#define p_q priority_queue
#define n_m unordered_map
#define il inline
#define re register
#define ve vector
#define bs bitset
using namespace std;

//#define O2 1
#ifdef O2
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3, "Ofast", "inline")
#endif

namespace OI {
	template <typename T>
	il T read() {
		T x = 0, f = 1;
		int ch = getchar();
		while (!isdigit(ch)) {
			if (ch == '-') f = -1;
			ch = getchar();
		}
		while (isdigit(ch)) {
			x = (x << 3) + (x << 1) + (ch ^ 48);
			ch = getchar();
		}
		return x * f;
	}
	template <typename TE>
	il void write(TE x) {
		if (x < 0) {
			x = -x;
			putchar('-');
		}
		TE sta[35];
		int top = 0;
		do {
			sta[top++] = x % 10, x /= 10;
		} while (x);
		while (top) putchar(sta[--top] + '0');
	}
	il string read_with_string() {
		string s = "";
		char ch = getchar();
		while ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) {
			s += ch;
			ch = getchar();
		}
		return s;
	}
	il void write_with_string(string s) {
		for (int i = 0; i < s.size(); i++) putchar(s[i]);
	}
}
using namespace OI;

//#define fre 1
#define IOS 1
#define multitest 1

const int N = 2e5 + 10;
const int M = 4e5 + 10;
const int inf = 1e12;

int n;
string s;
string t;
int c1, c2;

il void Init() {
	cin >> n >> s;
}

il void Solve() {
	int now = 0;
	t = "";
	while (now < n) {
		if (s[now] == '1') t += '1', now++;
		else {
			t += '0';
			while (now < n && s[now] == '0') now++;
		}
	}
	c1 = c2 = 0;
//	cout << t << endl;
	for (int i = 0; i < t.size(); i++) {
		c1 += t[i] == '0';
		c2 += t[i] == '1';
	}
	if (c1 >= c2) cout << "No\n";
	else cout << "Yes\n";
}

signed main() {
	int T;
#ifdef IOS
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
#endif
#ifdef fre
	freopen(".in", "r", stdin);
	freopen(".out", "w", stdout);
#endif
#ifdef multitest
	cin >> T;
#else
	T = 1;
#endif
	while (T--) {
		Init();
		Solve();
	}
	return 0;
}
/*

*/
```

[记录](https://codeforces.com/contest/1988/submission/270688850)。

---

## 作者：Annihilation_y (赞：0)

## 题目大意
我认为题目说的比较明白了，我就不解释了。

## 思路
首先，我们可以变换一下思路。我们不去想是否能够满足要求，而是去想如何在每一步中留下来更多的 $1$。

根据题目要求：

-   If $c_0\ge c_1$，the majority is $0$。
-   If $c_0<c_1$，the majority is $1$。

则，我们可以假定以下的情况。

- 当 $c_0 \ge c_1$ 的时候，将只保留一个 $0$，那么这样的方案明显不如对于每一段的 $0$ 做这样的操作，留下来一个 $0$。
- 当 $c_0 < c_1$ 的时候，将只保留一个 $1$。明显，这样的操作不能使总共的 $c_1 - c_0$ 的差最大。

所以，做法是先处理所有的连续的 $0$，然后再统一处理最后一次，根据题目要求进行判断即可。

## 代码
~~~c++
#include <bits/stdc++.h>
using namespace std;
int n,num_0,num_1;
string s;
int main(){
    int T;cin>>T;
    while(T--) {
        cin>>n>>s;
        s=" "+s;
        num_0=0,num_1=0;
        for(int i=1;i<=n;i++) {
            if(s[i]=='1') num_1++;
            if(s[i]=='0' && (i==1 || s[i-1]=='1')) num_0++; 
        }
        if(num_0>=num_1) printf("No\n");
        else printf("Yes\n");
        // cout<<"num0:"<<num_0<<" num1:"<<num_1<<endl;
    }
}
~~~

---

## 作者：白鲟 (赞：0)

首先容易想到将 $0$ 的连续段缩成一个 $0$。此时，任意连续段中，$0$ 的个数至多比 $1$ 的数目多 $1$，再做替代不会使得 $0$ 比 $1$ 多的数目减少，不会比整体替代更优，统计整体 $0$ 的个数与 $1$ 的个数比较即可。

```cpp
#include<cstdio>
int T, n, last, x, cnt[2];
int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        last = 1;
        cnt[0] =  cnt[1] = 0;
        for(int i = 1; i <= n; ++i) {
            scanf("%1d", &x);
            if(!x && !last) continue;
            ++cnt[last = x];
        }
        puts(cnt[0] >= cnt[1] ? "NO" : "YES");
    }
    return 0;
}
```

---

## 作者：_H17_ (赞：0)

## 题目分析

要把 $0$ 都“干掉”守先要自己干自己，把连续的一段 $0$ 变为一个。

然后考虑用 $1$ 消 $0$。用两个 $1$ 和一个 $0$ 可以把刚才的数变为一个 $1$。所以 $1,0$ 的数量都少了一个。

所以一个 $1$ 和 $0$ 相消。

如果最后序列 $1$ 多就可行，否则不可以。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,ans;
string s;
vector<int>vec;
int main(){
    for(cin>>T;T;--T){
        cin>>n>>s;
        vec.clear();
        ans=0;
        for(int i=0,lst=1;i<n;i++)
            if(s[i]^48)
                vec.push_back(lst=1);
            else if(lst)
                vec.push_back(lst=0);
        for(auto p:vec){
            if(p)
                ans++;
            else
                ans--;
        }
        cout<<(ans>0?"yEs\n":"nO\n");
    }
    return 0;
}
```

---

## 作者：Jordan_Pan (赞：0)

首先可以把所有连续的 $0$ 替换成单个的 $0$。

因为每次替换中 $0$ 更占优势，手玩一下发现替换中 $1$ 减少的数量一定不会比 $0$ 少，或者说想要消掉这么多的 $0$ 至少要付出同样数量的 $1$。

同时，如果 $1$ 更多可以直接把整个序列替换成 $1$。

所以统计序列中 $0$ 和 $1$ 的数量，如果 $1$ 更多输出 Yes，否则输出 No。

代码有点丑，就不放了。

---

## 作者：tzzl3035 (赞：0)

# CF1988B 题解
### 题目大意
有 $t$ 组数据，每组给出一个长度为 $n$，由 `0` 和 `1` 组成的字符串。可以进行一种操作：选取一个区间，若有任意一种字符占区间长度的一半以上，则可以将这个区间用**单个**的这种字符代替。问是否可以在有限的操作内将字符串变成 `1`。若可以，输出 `Yes`，否则输出 `No`。
### 思路
想要达到目标，我们就要让 `0` 的数量尽量少，`1` 的数量尽量多。所以，我们可以先将全是 `0` 的区间变成单个 `0`，然后判断剩下的 `1` 是否超过一半即可输出答案。
### 代码
``` c++
#include <bits/stdc++.h> // 万能头
using i64 = long long;

void solve() {
	// 输入
	int n;
	std::cin >> n;
	std::string s;
	std::cin >> s;
	// 统计操作后 0 的个数（c0）和 0 原来的个数（rc0）
	int c0 = 0, rc0 = 0;
	if(s[0] == '0') ++c0, ++rc0;
	for(int i = 1; i < n; ++i) {
		if(s[i] == '0' && s[i-1] == '1') 
			++c0;
		if(s[i] == '0') 
			++rc0;
	}
	// 判断后输出
	if(n - rc0 >= (n-rc0+c0)/2+1) std::cout << "Yes\n";
	else std::cout << "No\n";
	return;
}

int main()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(nullptr);

	int t; std::cin >> t;
	// 挨组处理
	while(t--) {
		solve();
	}
	
	return 0;
}

```
### [RESULT](https://codeforces.com/contest/1988/submission/270679935)

---

## 作者：Chillturtle (赞：0)

# 题意

给你一个由 $1$ 和 $0$ 组成的字符串，每次可以任意选择一个子串，在这个子串里数出 $1$ 和 $0$ 的个数。如果 $0$ 的个数大于等于 $1$ 的个数，那么就把这个子串全部换成 $0$ 否则全部换成 $1$。

# 思路

首先，我们知道一连串的 $0$ 可以缩成一个 $0$。那么此时如果它的旁边有 $2$ 个 $1$ 则此时这个 $0$ 就可以被替换掉。由此，我们可以发现。最后用于比较的 $0$ 的个数和块数有关的。这个地方我们只需要算出 $0$ 的连续子串个数就可以了。

现在，我们来处理 $1$。如果 $1$ 也想 $0$ 那样来数块，显然是不行的。我们要使 $1$ 的个数尽量大，以此来超过 $0$ 并且抵消 $0$。那我们就要物尽其用，把每一个 $1$ 都算上。这样才能使所有的 $1$ 都被用去抵消 $0$ 而不是自己抵消自己。

总结：用 $0$ 的块数和 $1$ 的个数进行比较，如果 $0$ 的块数大于等于 $1$ 的个数时输出 NO，否则输出 YES。

下面我来模拟一组数据解释：

![](https://cdn.luogu.com.cn/upload/image_hosting/6v1044n0.png)

~~我认为这道题放图好像没有太大意义（小声）。~~

# AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
int t, n;
char a[N];
vector<int> q;
int main() {
	cin >> t;
	while (t--) {
		q.clear();
		cin >> n;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			if (a[i] != '0' || a[i] != a[i - 1] || i == 1) {
				q.push_back(a[i] - '0');
			}
		}
		int zero = 0, one = 0;
		for (int i = 0; i < q.size(); i++) {
			if (q[i] == 1) one++;
			else zero++;
		}
		if (zero < one) {
			cout << "YES" << endl;
		} else {
			cout << "NO" << endl;
		}
	}
	return 0;
}
```

---

## 作者：florrygg (赞：0)

# CF1988B Make Majority 题解

## 思路

1. 首先我们需要发现一个结论：如果有多个连续的 $0$，那么把这些 $0$ 合并成一个绝对更优（应该用不着证明了吧）。
2. 对于剩下的数，如果选择只比 $0$ 多一个数的 $1$ 合成是没有区别的，因为合并之前这一段的 $1$ 比 $0$ 多一个，合并之后也是一样的，所以剩下的数直接全部合并即可判断是否可行即可。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

const int maxn=2e5+1;
int t,n;
string s;

signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n>>s;
		int cnt=0,cnt2=0;
		for(int i=0;i<n;i++)
		{
			if(s[i]=='1')
			{
				cnt++;
			}
			else if(s[i]=='0'&&(i==0||s[i-1]=='1'))
			{
				cnt2++;
			}
		}
		cout<<(cnt>cnt2?"Yes":"No")<<endl; 
	}
	return 0;
}
/*

*/
```

---

## 作者：wth2026 (赞：0)

# 题目大意
给定你一个字符串，只包含 $0$ 和 $1$。

你需要进行如下操作：每次在现有的串里选择一个区间，将其变成此区间里包含较多的数（特殊的，如果两者数量相等，则是 $0$）。

问是否可以通过操作使得最后的答案变成 $[1]$。

# 题目思路
我们肯定是希望相对的 $1$ 越多越好，那么就等同于相对的 $0$ 越少越好。我们可以将所有连在一起的 $0$ 变成一个 $0$。最后统计一下是 $1$ 多，还是 $0$ 的连续块多。

# AC Code
```cpp
#include <cstring>
#include <iostream>
#include <algorithm>

#define endl '\n'
#define int long long
#define inf 0x3f3f3f3f
#define lnf 0x3f3f3f3f3f3f3f3f

#pragma GCC optimize (1)
#pragma GCC optimize (2)
#pragma GCC optimize (3)
#pragma GCC optimize ("Os")
#pragma GCC optimize ("Ofast")

using namespace std;

const int N = 2e5;

void init ();

int T, n, _[2], _Lst;
char a;

signed main () {
	cin >> T;
	
	while (T --) {
		_[0] = _[1] = 0;
		_Lst = -1;
		cin >> n;
		
		while (n --) {
			cin >> a;
			
			if (a - '0') {
				++ _[1];
				_Lst = 1;
			} else {
				if (_Lst != 0) {
					_Lst = 0;
					++ _[0];
				}
			}
		}
		
		if (_[1] > _[0]) {
			puts ("Yes");
		} else {
			puts ("No");
		}
	}
	
	return 0;
}

```

---

## 作者：EricWan (赞：0)

### 逻辑简述

如果有一整段都是 $0$ 那么我们不如把它们整个做一次操作变成一个 $0$（这一步一定是严格优的），最后看总共的 $1$ 的个数是不是大于 $0$ 的个数即可。

### 证明

如果 $1$ 的个数大于 $0$ 的个数，通过一次操作将整个数组都变成一个 $1$ 即可。

如果 $1$ 的个数小于等于 $0$ 的个数，下面采用反证法：假设有一个合法的操作序列使得最后一次操作时 $1$ 的个数大于 $0$ 的个数，因为我们已经把连续的 $0$ 变成一个零了，所以可以证出每一次操作使用到的 $1$ 的数量 $use_1$ 和每一次操作使用到的 $0$ 的数量 $use_0$ 满足关系 $use_1\ge use_0 - 1$（不详细说了，有兴趣可以自己在草稿纸上证明）。当 $use_1=use_0 - 1$ 或 $use_1=use_0$ 时这一段被操作的序列变成一个 $0$，然而可以证明如果这样做了，$1$ 的总个数减 $0$ 的总个数不会增加，换句话说，这种操作不会让 $1$ 相对更多。类似的，当 $use_1>use_0$ 时这一段被操作的序列只会变成一个 $1$，$1$ 还是不可能相对 $0$ 更多。

### 具体做法

把 $0$ 的段数和 $1$ 的数量统计出来，最后进行比较，输出对应的答案即可。

---

## 作者：wangzc2012 (赞：0)

## 题意概括
~~这道题一看就不简单，身为蒟蒻的我好帕帕~~。给定一个只包含 $0$ 和 $1$ 的序列 $a _ {n}$，我们可以选择一个区间，将区间替换为单个区间内数量多的元素。求能否经过有限次操作，使 $a=[1]$。
## 思路分析
要使 $a=[1]$，就要使 $0$ 的数量尽可能少。因此，我们对全是 $0$ 的区间进行操作，将其替换为一个 $0$，就可以在尽可能减少 $0$ 的数量的同时使 $1$ 的数量保持不变。最后，如果 $1$ 的数量比 $0$ 多，则可以经过有限次操作，使 $a=[1]$，否则不能。
## AC Code
代码有亿点丑，请谅解。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
string a;
int main(){
    cin>>t;
    while (t--){
        int cnt=0,cn=0;
        cin>>n;
        cin>>a;
        for (int i=1;i<n;i++){
        	if (a[i]=='0' and a[i]!=a[i-1]) cnt++;  //0的数量
        	if (a[i]=='0' and a[i]==a[i-1]) cn++;  //0减少的数量
		}
		if (a[0]=='0') cnt++;  //特判第一位
        if (2*cnt<(n-cn)) cout<<"YES"<<'\n';   //判断
        else cout<<"NO"<<'\n';
    }
    return 0;
}
```
最后，附上AC记录：
![](https://cdn.luogu.com.cn/upload/image_hosting/wwmv4fnl.png)

---

## 作者：Dioretsa (赞：0)

最后必定要对整个区间进行一次操作以得到序列 $a=[1]$，由此想到要最小化序列中 $0$ 的个数。注意到可以将一串全为 $0$ 的子序列化为一个 $0$，问题得解。

赛时代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read() {
	int x=0,f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9') {
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9') {
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*f;
}
int T;
int main() {
	T=read();
	while(T--){
		int n=read(),c0=0,c1=0;
		char x,y='&';
		for(int i=1;i<=n;i++){
			cin>>x;
			if(x!=y&&x=='0') c0++;
			if(x=='1') c1++;
			y=x;
		}
		if(c1>c0) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
```

---

## 作者：Wind_love (赞：0)

## 思路
根据题意，我们想让 1 的数量尽量多，但数量是无法增加的，所以我们可以让 0 的数量尽量少。

根据题目中的替换操作，我们可以把相邻的 0 压缩成一个 0，这样就实现了让 0 的数量尽量少的目的。

最后，只要统计 1 与 0 的个数，按题意输出即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
string s;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		cin>>s;
		for(int i=0;i<s.size();i++){
			if(i==0)continue;
			if(s[i]=='0'&&s[i]==s[i-1])s[i-1]='*';
		}
		int c0=0,c1=0;
		for(int i=0;i<s.size();i++){
			if(s[i]=='0')c0++;
			if(s[i]=='1') c1++;
		}
		if(c0>=c1)cout<<"NO\n";
		else cout<<"YES\n";
	}
	return 0;
}

---

## 作者：Special_Tony (赞：0)

# 思路
显然，使用操作 $2$ 不会对 $1$ 产生任何好处，所以我们考虑使用操作 $1$ 把所有连续的 $0$ 压缩成一个，最后直接判断 $0,1$ 谁多就行。
# 代码
```cpp
# include <bits/stdc++.h>
# define I return
# define AK 0
# define IOI ;
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int t, n, s1, s2;
string a;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		s1 = s2 = 0;
		cin >> n >> a;
		for (int i = 0; i < n; ++ i)
			if (a[i] == '1')
				++ s1;
			else if (! i || a[i - 1] != '0')
				++ s2;
		cout << (s1 > s2 ? "Yes\n" : "No\n");
	}
	I AK IOI
}
```

---

## 作者：Halberd_Cease (赞：0)

下文称将一段区间删去变成 $1$ 的操作为操作 $A$，变成 $0$ 的为操作 $B$。

注意到能够将一个区间进行操作 $A$ 的充要条件是区间内 $1$ 的数比 $0$ 的数个数多至少一个。我们先考虑如何使区间内 $0$ 的个数尽量少。显然将一段连续进行操作 $B$ 将 $0$ 删掉一定不劣。

然后考虑一次操作 $A$ 能给我们带来什么，因为区间需要满足的条件是 $1$ 个数比 $0$ 个数至少多 $1$，而操作过后只会剩下一个 $1$，如当是把区间内 $1$ 和 $0$ 的个数差减少为 $1$，所以进行两次及以上的操作 $A$ 一定不优。

在只进行一次操作 $A$ 的情况下，最优策略一定是先将连续的 $0$ 使用操作 $B$ 消至一个 $0$，然后对整个序列进行 $A$ 操作，因为需要覆盖到所有的 $0$，因此选取整个序列一定不劣。

然后直接统计 $1$ 的个数和连续 $0$ 的段数比较即可。

[submission](https://codeforces.com/contest/1988/submission/270783564)

---

