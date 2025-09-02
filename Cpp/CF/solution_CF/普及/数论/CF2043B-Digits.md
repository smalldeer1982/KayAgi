# Digits

## 样例 #1

### 输入

```
3
2 6
7 1
8 5```

### 输出

```
1 3 
1 3 7 9 
1 3 5 7 9```

# 题解

## 作者：xxseven (赞：8)

首先一个正整数数被 $1$ 整除是肯定的，被 $5$ 整除只需要判断 $d$ 是否等于 $5$ 即可。

我们知道，一个数被 $3,9$ 整除等价于这个数的数位和被 $3,9$ 整除。而当前数的数位和显然为 $n! \times d$。

可以分别判断 $n!$ 和 $d$ 中各有几个质因子 $3$。如果共有至少一个那么可以被 $3$ 整除，如果至少两个那么可以被 $9$ 整除。

在 $n!$ 中，$3$ 会贡献一个，$6=2\times 3$ 会贡献一个，之后的即使有质因子 $3$ 也不需要考虑了。

在 $d$ 中，$3,6=2\times 3$ 会贡献一个，$9=3\times 3$ 会贡献两个。

最后考虑 $7$ 的情况。我们把原数拆成 $11111\ldots  \times d$ 处理，$d$ 能整除 $7$ 当且仅当 $d=7$。  

如果你知道[三位截断法](https://www.baidu.com/s?wd=%E4%B8%89%E4%BD%8D%E6%88%AA%E6%96%AD%E6%B3%95&tn=55145041_oem_dg)，或者知道 $1001 \bmod 7 =0，1001 \times 111=111111$，甚至是直接拿计算器算了一下，就能知道 $11111\ldots$ 能被 $7$ 整除，当且仅当它的位数能被 $6$ 整除。

那么问题就简单了，注意到 $2\times 3 =6$，所以 $n \ge 3$ 的时候 $n!$ 一定能被 $6$ 整除。至此我们就做完了这道题。

[提交记录](https://codeforces.com/contest/2043/submission/298392196)。

希望这篇题解能够帮到你！

---

## 作者：WA2025 (赞：6)

[题目传送门](/problem/CF2043B)

## 题意

有一个有 $n!$ 位，每一位都为数字 $d$ 的数，形如 $ddd\dots d$（有 $n$ 个 $d$）。

问 $1,3,5,7,9$ 这 $5$ 个奇数中有哪些能整除这个数。

## 思路

1. 考虑奇数 $1$，只要是正整数都可以被 $1$ 整除。\
   $\therefore$ 每个数的输出必有 $1$。
2. 考虑奇数 $3$，如果这个数的数位和为 $3$ 的倍数，那么这个数就会被 $3$ 整除。\
   但由于这道题目中每位数字都是相同的，所以只需要满足 $d=3,6,9$。
3. 考虑奇数 $5$，如果这个数的个位为 $0$ 或 $5$，那么这个数就可以被 $5$ 整除。\
   因为这个题中 $1\le d\le9$，所以只需要满足 $d=5$。
4. 考虑奇数 $7$，通过计算器观察可得，当 $n\ge3$ 或 $d=7$ 这个数就可以被 $7$ 整除。
5. 考虑奇数 $9$。\
   $\because 9=3^2$\
   $\therefore n\ge6$ 或 $d=9$ 或 $n\ge3\And d\mid3$ 即为 $9$ 的倍数。

这里就不贴代码了，与其他题解代码相似，可以参照其他题解的代码。

---

## 作者：HuangBarry (赞：5)

- 是否为 $1$ 的倍数：  
  任何非零自然数都是 $1$ 的倍数。
- 是否为 $3$ 的倍数：  
  只要 $n!$ 和 $d$ 的因子包含 $3$ 那么就是 $3$ 的倍数。
- 是否为 $5$ 的倍数：  
  只要 $d=5$ 那么就是 $5$ 的倍数，因为是否是 $5$ 的倍数只用看个位。
- 是否为 $7$ 的倍数：  
  因为 $1001\bmod7=0$ 所以 $1001\times111\equiv1001\pmod7$ 也是 $7$ 的倍数，所以只要 $n!\ge6$，即 $n\ge3$ 或者 $d=7$ 就是 $7$ 的倍数。
- 是否为 $9$ 的倍数：  
  跟判断是否为 $3$ 的倍数差不多，只要 $n!$ 和 $d$ 的因子 $3$ 的数量大于等于 $2$ 那么就是 $9$ 的倍数。
  
代码如下（个人喜欢用超长火车头）：

```cpp
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define stl_priority_queue std::priority_queue
#define pbds_priority_queue __gnu_pbds::priority_queue
#define endl '\n'
#define Endl cout<<endl
#define Made return
#define by 0
#define Barry +0
#define Freopen(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout);
#define debug(x) cout<<#x<<"----->"<<x<<endl;
using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;
using ll=long long;
using ull=unsigned long long;
using ld=long double;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
int t,n,d;
int main(){
    //Freopen("filename");
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--){
        cin>>n>>d;
        cout<<1<<" ";
        if(n>=3||d%3==0)
            cout<<3<<" ";
        if(d==5)
            cout<<5<<" ";
        if(n>=3||d==7)
            cout<<7<<" ";
        if(n>=6||d==9||(n>=3&&d%3==0))
            cout<<9;
        Endl;
    }
    Made by Barry;
}
```

---

## 作者：Ambrose0321 (赞：3)

思路：
---
因为题目只要 $1 \sim 10$ 之间的奇数是否能整除 $n!$ 个 $d$ 就行，所以可以考虑挨个数字判断。

1. 所有数字都 $1$ 的倍数。

2. $n \le 3$ 或 $d \bmod 3 = 0$ 就是 $3$ 的倍数。

3. $d = 0$ 或 $d = 5$ 就是 $5$ 的倍数。

4. 判断 $7$ 的倍数比较复杂，通过三位截断法我们发现如果 $n \ge 3$ 那么一定有偶数个三位，也就是这个数是 $7$ 的倍数。

5. 判断 $9$ 的倍数判断 $3$ 的倍数同理，但是因为 $n \ge 6$ 时也能被 $9$ 整除，所以 $n \ge 6$ 或 $d \bmod 9 = 0$ 就是 $9$ 的倍数了。

只剩下 $n \lt 3$ 的情况了，直接拼出来数字判断是否能整除就能 AC 这道题啦！


AC code：
---


```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int _, n, ans, a[501][501];
inline void calc(int i, int j) {
	int m = 0;
	for (int d = 0; max(i, j) <= n - d; d++)
		m = max(m, -a[i + d][j + d]);
	for (int d = 0; max(i, j) <= n - d; d++)
		a[i + d][j + d] += m;
	ans += m;
}
int main() {
	scanf("%d", &_);
	for (; _--; ) {
		ans = 0;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				scanf("%d", &a[i][j]);
		for (int i = 1; i <= n; i++)
			calc(1, i);
		for (int i = 2; i <= n; i++)
			calc(i, 1);
		printf("%d\n", ans);
	}
}
```
这是本蒟蒻的第二篇题解，请各位大佬不喜勿喷，希望能过审 qwq。

---

## 作者：gaominzhang (赞：3)

# 题解：CF2043B Digits
## 题解部分
显然这个题的数据范围很大， $O(n)$ 都过不了，更何况这题还有个是 $n!$，就算高精模都能撑爆空间~~吧~~，但这个题只需要算能否被五个数整除即可，所以这显然是一道数论题。为了方便，我们把 ddd……dd 称为 $x$ 。　
1. $x$ 必然能被 $1$ 整除，所以直接输出 $1$ 即可
2. $x$ 想被 $3$ 整除，必然其每位上数字的和是 $3$ 的倍数，有两种情况，（1） $d\bmod3=0$ 即其每位上的数字都是 $3$ 的倍数，所以数字和是 $3$ 的倍数。（2） $n!\bmod3=0$ 即数字位数是 $3$ 的倍数，和自然是 $3$ 的倍数。
3. 同理可得 $x$ 想被 $9$ 整除，必然其每位上数字的和是 $9$ 的倍数，有三种情况。（1）$\bmod9=0$ 即其每位上的数字都是 $9$ 的倍数，所以数字和是 $9$ 的倍数。（2）$n!\bmod9=0$ 即数字位数是 $9$ 的倍数，和自然是 $9$ 的倍数。（3）然而还有一种情况，知周所众， $9=3\times3$ 所以还有一种可能，即 $d\bmod3=0$ 且 $n!\bmod3=0$ 即其每位上的数字都是 $3$ 的倍数且数字位数是 $3$ 的倍数，和自然是 $3\times3=9$ 的倍数。
4. $x$ 想被 $5$ 整除，很显然个位只能是 $0$ 或 $5$，$d\le1$ 所以 $d=5$ 时,$x$ 被 $5$ 整除。
5.  $x$ 想被 $7$ 整除，是最难的，知周所众，[三位隔断法](https://wenda.so.com/q/1665183647217256)可以算出能被 $7$ 整除的数，那么显然可知，如果一个数字的位数是 $6$ 的倍数或 $d\bmod7=0$，那么 $x$ 能被 $7$ 整除。  
## 代码部分
```cpp
#include<bits/stdc++.h>
#define int long long//不开long long见祖宗
using namespace std;
signed main() {
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	for(int hg=1; hg<=t; hg++) {
		int n,d;
		cin>>n>>d;
		cout<<"1 ";//一定能被1整除
		if(n>=3||d%3==0)cout<<"3 ";//一定能被3整除
		if(d==5)cout<<"5 ";//一定能被5整除
		if(n>=3||d%7==0)cout<<"7 ";//n>=3时n!%6==0，一定能被7整除
		if(n>=6||d%9==0||(n>=3&&d%3==0))cout<<"9 ";//三种情况一定能被9整除
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：New_Void (赞：3)

1 . 是否为 $1$ 的倍数，这很简单，所有大于零的自然数都是 $1$ 的倍数。

2 . 是否为 $3$ 的倍数，由于这道题存在阶乘，所以我们不可以算出值来然后除以，我们可以用 $n!$ 和 $d$ 判断。只要 $n!$ 和 $d$ 有因子 $3$ ,那么就是 $3$ 的倍数。

3 . 是否为 $5$ 的倍数，只要 $d$ 等于 $5$ ，那就是 $5$ 的倍数。

4 . 是否为 $7$ 的倍数，我们知道 $1001$ 是 $7$ 的倍数，所以通过计算器，我们得出只要是 $n!$ 大于 $3$ ，或者 $d$ 等于 $7$ ，那就是 $7$ 的倍数。

5 . 是否为 $9$ 的倍数，跟 $3$ 差不多，但是 $9$ 是两个 $3$ 相乘，所以 $n$ 要大于等于 $6$ ，或者 $d$ 等于 $9$ ，或者 $n$ 大于等于 $3$ 并且 $d$ 能被 $3$ 整除，那就是 $9$ 的倍数。

# Code

```cpp
#include <iostream>
using namespace std;
int main(){
    int t;
    cin>>t;
    for (int i=0;i<t;i++){
        int n,d;
        cin>>n>>d;
        cout<<1<<" ";
        if (n>=3 || d%3==0){
            cout<<3<<" ";
        }
        if (d==5){
            cout<<5<<" ";
        }
        if (n>=3 || d==7){
            cout<<7<<" ";
        }
        if (n>=6 || d==9 || (n>=3 && d%3==0)){
            cout<<9<<" ";
        }
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：ClV_Csy (赞：2)

# CF2043B Digits
## 前言
题目翻译者题解。
## 题意
求出由 $n!$ 个 $d$ 拼合成的数能被 $1, 3, 5, 7, 9$ 中的哪些数整除。
## 思路
数据范围非常之大：
> $2 \le n \le 10^9$

这样一来，$n!$ 不知道要大到哪里去了，更何况还要表示出这么大位数的数，再逐一判断是否能整除。所以暴力的做法是完全不可取的。考虑利用数论知识。

证明 1：设有一个三位数，表示为 $100a + 10b + c$。

$
\begin{aligned}
  (100a + 10b + c) \bmod 3 &= ((99a + 9b) + (a + b + c)) \bmod 3\\
                           &= (99a + 9b) \bmod 3 + (a + b + c) \bmod 3\\
                           &= (a + b + c) \bmod 3
\end{aligned}
$

这样一来，$100a + 10b + c$ 模 $3$ 的结果就是 $a + b + c$（各位之和）模 $3$ 的结果了。这个结果还可以推广到任意位数的正整数。即：  
一般地，**任意一个正整数，它的各位数之和模 $3$ 的结果就是它本身模 $3$ 的结果。**  
特殊的，**任意一个正整数，若它的各位数之和是 $3$ 的倍数，则它本身也是 $3$ 的倍数。**

逐一判断是否是 $1, 3, 5, 7, 9$ 的倍数。
- $1$ 的倍数：任何正数都是 $1$ 的倍数。
- $3$ 的倍数：利用证明 1，可知只要一个正数的各个数位之和为 $3$ 的倍数，该数就是 $3$ 的倍数。由于此题每个 $d$ 相等，因此各位数之和为 $n! \times d$，判断 $n!$ 或 $d$ 能否被 $3$ 整除，只要其中一个能整除，则原数是 $3$ 的倍数。$n! = 1 \times 2 \times 3 \times … \times n - 1 \times n$，注意到 $n \ge 3$ 时，$n!$ 一定能被 $3$ 整除。所以判断原数是否为 $3$ 的倍数就变成了判断 $n$ 是否大于等于 $3$ 或 $d$ 是否能被 $3$ 整除。
- $5$ 的倍数：有且仅有个位为 $0$ 或 $5$ 的数可以被 $5$ 整除，且因为 $1 \le d \le 9$，所以只有 $d = 5$ 时才被 $5$ 整除。
- $7$ 的倍数：由于 $1001 \mid 7$，$1001 \times 111 = 111111$，因此只有 $n! \mid 6$ 时（$n \ge 3$ 时）原数为 $7$ 的倍数。
- $9$ 的倍数：类比 $3$ 的倍数，判断原数是否为 $9$ 的倍数相当于判断 $n \ge 6$ 或 $d \mid 9$ 或同时满足 $n \ge 3$ 和 $d \mid 3$。

## 代码

```cpp
#include <iostream>
using namespace std;
int main() {
	int t, n, d;
	cin >> t;
	while (t--) {
		cin >> n >> d;
		cout << "1 ";
		if (n >= 3 || d % 3 == 0) cout << "3 ";
		if (d == 5) cout << "5 ";
		if (n >= 3) cout << "7 ";
		if (n >= 6 || d % 9 == 0 || (n >= 3 && d % 3 == 0)) cout << "9";
		cout << "\n";
	}
	return 0;
}
```

---

## 作者：Sakura_Emilia (赞：2)

# Solution

这道题其实可以用打表的方式解决。

首先 $1$ 是显然要有的，而 $5$ 也很好判断，只需要看 $d$ 是不是 $5$ 就行。对于 $3$ 和 $9$ 也很好判断，最大的困难就是当 $d$ 为 $7$ 的时候不好判断。

对于所有当 $d$ 为 $7$ 的时候，都可以等价为当 $d$ 为 $1$ 的时候。因为形如 $ddddddd$ 的数等价于 $1111111$ 乘以一个 $d$，本质上还是来判断 $1111111$ 是否为 $7$ 的倍数。

虽然这种情况用数学其实也很好推导，但最简单粗暴的方法就是直接打表。由于位数较多，推荐使用自带大整数的 Python 进行打表。经过打表可以发现：只有当总位数为 $6$ 的倍数的时候，形如 $1111111$ 的数才是 $7$ 的倍数。

之后稍微分情况讨论一下就行了。

# Code

```cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define Ciallo main
#define int long long
#define el else
#define wl while
#define rt return
#define il inline
#define br cout << endl;
using namespace std;

int T, n, k;

il void solve() {
    cin >> k >> n;
    if(k >= 6) {
        cout << "1 3";
        if(n == 5)
            cout << " 5";
        cout << " 7 9\n";
    } el if(k >= 3) {
        cout << "1 3 ";
        if(n == 5)
            cout << "5 ";
        cout << "7 ";
        if(n % 3 == 0)
            cout << "9 ";
        br
    } el {
        n *= 11;
        cout << '1';
        if(n % 3 == 0)
            cout << " 3";
        if(n % 5 == 0)
            cout << " 5";
        if(n % 7 == 0)
            cout << " 7";
        if(n % 9 == 0)
            cout << " 9";
        br
    }
}

signed Ciallo() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> T;
    wl(T--)
        solve();

    rt 0;
}
```

---

## 作者：xxxalq (赞：1)

[洛谷题目链接](https://www.luogu.com.cn/problem/CF2043B) & [CF 题目链接](http://codeforces.com/problemset/problem/2043/B)

# 思路分析：

首先所有正整数都是 $1$ 的倍数。

其次判断 $3$ 的倍数。

一个正整数是 $3$ 的倍数的充分必要条件为各数位上数字之和为 $3$ 的倍数。本题中各数位之和为 $n!\times d$，所以要么 $d$ 是 $3$ 的倍数；要么 $n!$ 是 $3$ 的倍数，此时当且仅当 $n \ge 3$。

$5$ 的倍数很好判断，当且仅当 $d=5$。

$7$ 的倍数也有判断方法，每三位拆开分成两部分，两部分之差为 $7$ 的倍数即可，显然当 $n!$ 为 $6$ 的倍数即 $n\ge 3$ 时两部分差为 $0$，因为此时可以拆成长度都是 $3$ 的倍数的相等的两部分。或者 $d=7$ 显然也可以满足条件。

$9$ 的判断方法可以类比 $3$。

# 代码：

```cpp
//code by xxxalq
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int maxn=300003;

int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch>57||ch<48){
		if(ch==45){
			f=-1;
		}
		ch=getchar();
	}
	while(ch>=48&&ch<=57){
		x=(x<<1)+(x<<3)+(ch-48);
		ch=getchar();
	}
	return x*f;
}

int T,n,d;

int jc(int x){
	int res=1;
	while(x){
		res*=x;
		x--;
	}
	return res;
}

void solve(){
	cout<<"1 ";
	if(d%3==0||n>=3){
		cout<<"3 ";
	}
	if(d==5){
		cout<<"5 ";
	}
	if(n>=3||d==7){
		cout<<"7 ";
	}
	if(d==9||n>=6||(n<6&&(jc(n)*d)%9==0)){
		cout<<"9 ";
	}
	cout<<'\n';
	return;
}

int main(){
	T=read();
	while(T--){
		n=read(),d=read();
		solve();
	}
	return 0;
}
```

---

## 作者：sjh0626 (赞：0)

## 思路分析
一道经典分类讨论题。

首先，$1$ 不用讨论了，因为任何非零自然数都是 $1$ 的倍数。

接下来是 $3$，它有两种情况：
- 如果 $n \ge 3$，那么 $3 \mid n!$，这个数能被 $3$ 整除；
- 如果 $3 \mid k$，那么这个数也能被 $3$ 整除。

第三个是 $5$，我们只需要看个位，也就是 $k$，如果 $5 \mid k$ 根据数据范围即 $k=5$ 时，能被 $5$ 整除。

第四个是 $7$，因为 $7$ 的倍数满足三位一段奇偶段相减的差能被 $7$ 整除的奇妙原理，所以当 $6 \mid n!$ 即 $n\ge 3$ 时或 $k=7$ 时能被 $7$ 整除。

最后是 $9$，和 $3$ 差不多，有两种情况：
- 如果 $n \ge 6$，那么 $9 \mid n!$，能被 $9$ 整除；
- 如果 $k=9$，那么这个数也能被 $9$ 整除。

## 代码解析
因为根据上面的结论已经能写出代码了，所以不必亮出代码。

---

## 作者：Perfect_Youth (赞：0)

1. 判断 $1$ 的倍数，很明显，是正整数一定是 $1$ 的倍数。
2. 判断 $3$ 的倍数，就是它的所有数位的和加起来是 $3$ 的倍数。但是题目给的是 $n!$ 位，所以你只需判断 $n\ge 3$ 或者 $d\bmod 3 = 0$ 就可以了。
3. 判断 $5$ 的倍数，看最后一位是 $5$ 或者 $0$，就可以了，但是题目中 $d\ne 0$，所以判断 $d=5$ 即可。
4. 判断为 $7$ 的倍数，知道 $1001$ 是 $7$ 的倍数，所以通过计算，我们得出只要是 $n!$ 大于 $6$ ，或者 $d$ 等于 $7$ ，那就是 $7$ 的倍数。
5. 判断 $9$ 的倍数，跟判断 $3$ 的倍数类似，判断 $n!$ 和 $d$ 的因子 $3$ 是否大于 $2$ 就行了。

代码如下：
```cpp
#include <bits/stdc++.h>

using namespace std;

int t, n, d;

inline
int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' or ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^ '0');
		ch = getchar();
	}
	return x * f;
}

int main() {
	t = read();
	while (t--) {
		n = read(), d = read();
		printf ("1 ");
		if (n >= 3 or d % 3 == 0) printf ("3 ");
		if (d == 5) printf ("5 ");
		if (d == 7 || n >= 3) printf ("7 ");
		if (n >= 6 or d == 9 or (n >= 3 && d % 3 == 0)) printf ("9 ");
		puts("");
	}
	return 0;
}
```

---

