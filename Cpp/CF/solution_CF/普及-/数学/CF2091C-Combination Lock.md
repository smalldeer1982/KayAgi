# Combination Lock

## 题目描述

在 IT Campus "NEIMARK" 中，有几个开发重大编程竞赛题目的绝密房间。要进入其中一个房间，必须通过选择正确的密码来解锁一个圆形锁。该密码每天更新一次。

今天的密码是一个从 $1$ 到 $n$ 的排列$$$^{\text{∗}}$$$，且满足其每个循环位移$$$^{\text{†}}$$$中恰好有一个固定点。也就是说，在每一个循环位移中，存在且仅存在一个元素，其值等于它在排列中的位置。

请输出任意一个满足此条件的有效排列。请注意，有效的排列可能不存在，此时请输出 $-1$。

$$$^{\text{∗}}$$$排列的定义是一个长度为 $n$ 的序列，包含从 $1$ 到 $n$ 的整数，且每个数字恰好出现一次。例如，$(2\ 1\ 3)$、$(1)$、$(4\ 3\ 1\ 2)$ 是排列；而 $(1\ 2\ 2)$、$(3)$、$(1\ 3\ 2\ 5)$ 不是排列。

$$$^{\text{†}}$$$数组的循环位移是指将最后一个元素移动到数组开头得到的数组。一个长度为 $n$ 的排列恰好有 $n$ 个循环位移。

## 说明/提示

在第二个样例中，存在一个排列使得每个循环位移中都有一个固定点（用深红色标出）：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2091C/97f07d8865b709e2ac05cf6cf0c154be7dc52ee5.png)  
第一行表示元素的位置编号，第二行展示了目标排列的所有循环位移。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
4
5
3```

### 输出

```
-1
4 1 3 5 2
1 3 2```

# 题解

## 作者：Clare613 (赞：10)

## 思路
这一道题就是找一个数列，进行一轮循环，保证至少有一个 $a_i$ 的值为 $i$。\
由此我们可以想到，每一次只能有一个，因为如果哪一次多了，那么必然有一次少，所以我们要利用**错位**。\
**错位**怎么利用呢，题目的样例解释已经给得很清楚了，于是很快就能推测出，当 $n$ 为**奇数**时有解，而为**偶数**时无解。\
最后输出时就是先输出不大于 $n$ 的奇数，然后是不大于 $n$ 的偶数。如果 $n$ 为偶数时无解。
## code
```C++
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[200005];
bool cmp(int x,int y){
	return x>y;
}
signed main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		if(n%2==0){
			cout<<"-1\n";
		}
		else{
			for(int i=1;i<=n;i+=2){
				cout<<i<<" ";
			}
			for(int i=2;i<=n;i+=2){
				cout<<i<<" ";
			}
			cout<<"\n";
		}
	}
	return 0;
}

```

---

## 作者：Clare613 (赞：2)

~~我正在尝试向一道题交两篇题解。~~
## 思路
上一篇给大家说了一种利用错位方法过的题，根据之后的研究，我又发现了另一种解法。\
我们还是用错位的思想，基本框架也不变，但是最后 $n$ 除以 $2$ 的余数为 $1$ 的情况的输出就不一样了。\
我们可以列一个表：
|编号|1|2|3|4|5|
|:-:|:-:|:-:|:-:|:-:|:-:|
|数值|5|4|3|2|1|

这时我们可以看到，$3$ 是符合的。接下来把剩下四个表也列出来。\
$5$ 对应:
|编号|1|2|3|4|5|
|:-:|:-:|:-:|:-:|:-:|:-:|
|数值|4|3|2|1|5|

$2$ 对应:
|编号|1|2|3|4|5|
|:-:|:-:|:-:|:-:|:-:|:-:|
|数值|3|2|1|5|4|

$4$ 对应:
|编号|1|2|3|4|5|
|:-:|:-:|:-:|:-:|:-:|:-:|
|数值|2|1|5|4|3|

$1$ 对应:
|编号|1|2|3|4|5|
|:-:|:-:|:-:|:-:|:-:|:-:|
|数值|1|5|4|3|2|

不列不知到，一列吓一跳，很明显，由 $5$ 到 $1$ 的序列是可行的，放到更大的自然也是可行的。
## code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[200005];
bool cmp(int x,int y){
	return x>y;
}
signed main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		if(n%2==0){
			cout<<"-1\n";
		}
		else{
		    for(int i=n;i>=1;i--) cout<<i<<" ";
			cout<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：yulinOvO (赞：1)

### 题意
**经典数学题。**

这里排列定义题面说的比较模糊，也就是长度为 $n$ 的序列，包含 $1$ 至 $n$ 且每个数恰好出现一次。例如 $(2,1,3)$ 是排列，$(1,2,2)$ 不是。

**循环位移**也就是把数组末尾元素移到开头。例如 $(1,2,3)$ 循环一次变成 $(3,1,2)$。

题目说需要构造排列 $P$，使得存在某个循环位移后的排列与原排列至少有一个位置数字相同。

### 思路
1. **n 为奇数时**：构造排列 $P_i = (2i-1)$（若为 $0$ 取 $n$）。  
   - 例如 $n=3$，$P=(1,3,2)$，其循环位移 $(2,1,3)$ 第 $3$ 位匹配 $3$。
2. **n 为偶数时**：无法构造，因为会导致重复数字（非法排列），输出 $-1$。
### Code:
```cpp
#include<bits/sTdc++.h>
using namespace std;
int t,n;
int main()
{
    cin >> t;
    while(t--)
	{
        cin >> n;
        if(n%2==0)
		{
            cout << "-1" << endl;
            continue;
        }
        else
	        for(int i=1;i<=n;i++)
			{
            	if((i*2-1)%n) cout << (i*2-1)%n <<" ";
            	else cout<<n<<" ";
	        }
        cout << endl;
    }
    return 0;
}
```

---

## 作者：zyen11451425 (赞：1)

# [CF2091C Combination Lock](https://www.luogu.com.cn/problem/CF2091C)

## 思路

一道简单而纯粹的数学题。

题目中这两个定义可能有些费解：

∗
**排列**的定义是一个长度为 $n$ 的序列，包含从 $1$ 到 $n$ 的整数，且每个数字恰好出现一次。例如，$(2 1 3)$、$(1)$、$(4 3 1 2)$ 是排列；而 $(1 2 2)$、$(3)$、$(1 3 2 5)$ 不是排列。

†
**数组的循环位移**是指将最后一个元素移动到数组开头得到的数组。一个长度为 $n$ 的排列恰好有 $n$ 个循环位移。

这是样例解释给的图片：

![样例解释](https://cdn.luogu.com.cn/upload/image_hosting/scxm6crm.png)

可以发现，循环数组每一次循环都有一个相同数字与原数组位置匹配 （染红数字），而答案就是这个循环数组的任意一个状态。

我们设循环数组原状态第一个数字与原数组第一个数字匹配，循环 $i$ 次。

由于循环 $1$ 次后，循环数组第二个数移到第三个下标，于是跟原数组第三个数匹配，以此类推，循环数组 $a$ 的转移方程就是 $a[i]=(i + i - 1) \bmod n$（当 $i + i - 1$ 被 $n$ 整除时为 $n$）。

“有效的排列可能不存在”。

但不存在方案的情况又是怎么回事呢？

当 $n$ 为偶数时，我们发现循环数组计算结果居然有重复数字！

![示例](https://cdn.luogu.com.cn/upload/image_hosting/umdu4v1v.png)

这样就不符合**排列**的定义了，因此 $n$ 为偶数时排列不存在，特判输出 $-1$。

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int main(){
    cin>>t;
    while(t--){
        cin>>n;
        if(n%2==0){
            cout<<"-1\n";
            continue;
        }
        for(int i=1;i<=n;i++){
            if((i+i-1)%n)cout<<(i+i-1)%n<<" ";
            else cout<<n<<" ";
        }
        cout<<'\n';
    }
    return 0;
}
```

---

## 作者：ZMQ_Ink6556 (赞：1)

## 题解：CF2091C Combination Lock

### 解题思路

要求输出排列，保证有且仅有一个点使得 $a_i = i$。

不妨先钦定 $a_1 = 1$，此时会发现**剩余数字为偶数个**时才能使得旋转后没有更多点重合。

化简得 $n$ 为奇数时有解、$n$ 为偶数时无解。

此时有更简单的做法，即输出一个 $n , n - 1 , \dots , 3 , 2 , 1$ 的数列。

![pic](https://cdn.luogu.com.cn/upload/image_hosting/8y844zdy.png)

如图，序列是蓝线，在转动（黑线上下移动）时都有一个交点，此方法正确。

代码极其简单，复杂度 $O(n)$。

### 参考代码

```cpp

#include<bits/stdc++.h>
using namespace std;
long long t , n;
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t--)
	{
		cin >> n;
		if(n % 2 == 0)
		{
			cout << "-1\n";
			continue;
		}
		for(int i = n ; i >= 1 ; i--)
		{
			cout << i << ' ';
		}
		cout << '\n';
	}
	return 1;
}
```

---

## 作者：wrh316 (赞：1)

### 思路
假设经过 $k$ 循环移动之后，元素 $p_i$ 位于位置 $(i + k) \bmod n$。要使这个点固定下来，就必须有 $(i + k) \bmod n = p_i$。假设循环变换 $p$ 从 $0$，$[0,1,2,\ldots,n - 1]$ 开始。

由此可得 $k = p_i \equiv i \ (\bmod \ n)$。要使任何循环变换成为定点，必须能够从 $0$ 到 $n - 1$ 得到任何 $k$。让我们对 $k = p_i \equiv i \ (\bmod \ n)$ 的所有可能值两边求和。

得到 $\sum_{k=0}^{n - 1} k = \frac{n \cdot (n - 1)}{2}$ 和 $\sum_{i=0}^{n - 1} (p_i - i) =\sum_{0=1}^{n - 1} p_i - \sum_{i=0}^{n - 1} i = 0$。为了构造一个排列，这些和必须等于 $n$ 的模，即 $\frac{n \cdot (n - 1)}{2} = 0 \ (\bmod \ n)$。对于偶数 $n$ 这是不可能的，答案是 $-1$。而奇数 $n$ 可以是 $p = [n,n - 1,\ldots,2,1]$。

### 代码
```c++
#include <bits/stdc++.h>
using namespace std;

int t,n;
int main() {
    ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
    cin >> t;
    while (t--) {
        cin >> n;
        if (n % 2 == 0) cout << "-1\n";
        else {
            for (int i = n; i >= 1; i--) cout << i << " ";
            cout << "\n";
        }
    }
    return 0;
}
```

---

## 作者：Pyrf_uqcat (赞：1)

一道构造的橙题。

很好想出：当 $n$ 为偶数时无解。所以我们可以用 `if` 判断一下，奇数情况用 `else` 继续。

刚开始可以都赋值为 $1$ 到 $n$，然后把他分开来排序就可以满足要求。可以用我看到的一个词**错位**可以理解。

只需将奇数偶数相交输出即可。

答案：当 $n$ 为偶数时先输出所有的奇数，然后输出所有偶数。


```cpp
#define max(a,b) (a)>(b)?(a):(b) 
#define min(a,b) (a)<(b)?(a):(b) 
#include <bits/stdc++.h>
#define ll long long

const int N=2e5+5;

ll n,a[N];

int main()
{
	ll t;std::cin>>t;
	while(t--)
	{
		std::cin>>n;
		if(n%2==0)
		{
			std::cout<<-1;
		}
		else
		{
			for(ll i=1;i<=n;i+=2) std::cout<<i<<' ';
			for(ll i=2;i<=n;i+=2) std::cout<<i<<' ';
		}
		std::cout<<std::endl;
	}
	return 0;
}

```

---

## 作者：_Star_Universe_ (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF2091C)

### 思路
首先很容易发现，当 $n$ 为偶数时，只能出现没有固定点或者固定点不止一个的情况，显然无解，输出 `-1`。

当 $n$ 为奇数时，观察 $n=5$ 的样例解释，发现第二幅图选择最后一个数 $5$ 作为固定点，对应的答案是先输出所有的偶数，再输出所有的奇数，因此我们可以选择这种最简单的输出方式。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int n,a[200005];
int main(){
	int t;
  cin>>t;
	while(t--){
		cin>>n;
		if(n%2==0){
			cout<<-1;
		}
		else{
			for(int i=2;i<=n;i+=2) cout<<i<<' ';
			for(int i=1;i<=n;i+=2) cout<<i<<' ';
		}
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：ChengSinuo (赞：0)

## [题目传送门](https://codeforces.com/problemset/problem/2091/C)
这道题比较简单，主要还是一个数学问题。上思路：

## 思路

>一个从 $1$ 到 $n$ 的排列$$$^{\text{∗}}$$$，且满足其每个循环位移$$$^{\text{†}}$$$中恰好有一个固定点。也就是说，在每一个循环位移中，存在且仅存在一个元素，其值等于它在排列中的位置。

设项数为 $n$。

① 如果数列项数为偶数，无论如何也不会有固定点或不止一个固定点，无解。

以 4 为例： (样例 #1 测试用例 1 )
|1|2|3|4|
|:-:|:-:|:-:|:-:|
|4|3|2|1|

（无）

---
|1|2|3|4|
|:-:|:-:|:-:|:-:|
|$\color{Red}{1}$|3|2|$\color{Red}{4}$|

（不止一个）

---
|1|2|3|4|
|:-:|:-:|:-:|:-:|
|4|$\color{Red}{2}$|$\color{Red}{3}$|1|

（不止一个）



---


即：
```cpp
if(n%2==0) cout<<-1;
```

② 如果项数为奇数，可以发现，$n ,n-1, \cdots, 2, 1$ 正好符合题意。

（样例 #1 测试用例 2 ）
|1|2|3|4|5|
|:-:|:-:|:-:|:-:|:-:|
|5|4|	$\color{Red}{3}$|2|1|

|1|2|3|4|5|
|:-:|:-:|:-:|:-:|:-:|
|4|3|2|1|	$\color{Red}{5}$|

|1|2|3|4|5|
|:-:|:-:|:-:|:-:|:-:|
|3|	$\color{Red}{2}$|1|5|4|

|1|2|3|4|5|
|:-:|:-:|:-:|:-:|:-:|
|2|1|	5|$\color{Red}{4}$|3|

|1|2|3|4|5|
|:-:|:-:|:-:|:-:|:-:|
| $\color{Red}{1}$ |5|4|3|2|


---


（样例 #1 测试用例 3 ）
|1|2|3|
|:-:|:-:|:-:|
|3| $\color{Red}{2}$ |1|

|1|2|3|
|:-:|:-:|:-:|
|2|1| $\color{Red}{3}$ |

|1|2|3|
|:-:|:-:|:-:|
| $\color{Red}{1}$ |3|2|
---


数学归纳法，得：
|1|2|$\cdots$|$n-1$|$n$|
|:-:|:-:|:-:|:-:|:-:|
|$n$|$\cdots$|$\color{Red}{\frac{n+1}{2}}$|$\cdots$|1|
|$n-1$|$\cdots$|2|1|$\color{Red}{n}$|
|||$\cdots$|||
|$\color{Red}{1}$|$n$|$\cdots$|3|2|



即：

```cpp
else{
    for(int j=n;j>=1;j--){
        printf("%lld ",j);
    }
}
```


好了，完整代码：

## Code


```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
    long long t;
    scanf("%lld",&t);
    for(int i=0;i<t;i++){
        long long n;
        scanf("%lld",&n);
        if(n%2==0) printf("-1");
        else{
            for(int j=n;j>=1;j--){
                printf("%lld ",j);
            }
        }
        printf("\n");
    }
    return 0;
}
```

再附加一种 Python 的解法


```python
t=int(input())
for i in range(t):
    n=int(input())
    if n%2==0:
        print(-1)
    else:
        for j in range(n,0,-1):
            print(j,end=" ")
        print()
```


[AC Rank (C++)](https://codeforces.com/contest/2091/submission/315169718)

[AC Rank (Python)](https://codeforces.com/contest/2091/submission/315170965)

---

## 作者：小睿2012 (赞：0)

我们不妨钦定第 $i$ 次，数字 $i$ 在第 $i$ 个位置，这是一种解，若有解的话，那么这种情况显然也是可行的。我们填数的方法应该是：在第一个位置填上 $1$，为了让下个数下一次在正确的位置，所以我们应该隔一个格子填入下一个数，如果那个格子已经填了数，就说明无解，记得注意循环。

举个例子，当 $n = 5$ 时：
![](https://cdn.luogu.com.cn/upload/image_hosting/flbsgray.png)

按照已经讲述了的填数方法，就是这样填的。

### AC code：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int a[N],n;

int main()
{
	int t;
	cin >> t >> n;
	while(t--)
	{
		bool flag = 0;
		int d = 1;
		for(int i = 1;i <= n;i++)
		{
			if(a[d] != 0)
			{
				cout << -1  << '\n';
				flag = 1;
				break;
			}
			else
			{
				a[d] = i;
				d += 2;
				d %= n;
				if(d == 0) d = n;
			}
		}
		if(!flag)
			for(int i = 1;i <= n;i++) cout << a[i] << " ";
		if(t != 0)
			cin >> n;//读入下一次的n按需清空	
		for(int i = 1;i <= n;i++) a[i] = 0;			
		cout << '\n';	
	}
	return 0;
}
```

---

## 作者：Lyw_and_Segment_Tree (赞：0)

## 开始解题！

观察题目，样例其实给了挺多东西了。

首先可以发现 $n$ 为偶数的时候，直接是无解的。

而在 $n$ 为奇数的时候实际上是很好构造的，考虑 $a_i = n - i + 1$ 即可，即 $n, n - 1, n - 2, \dots, 2, 1$ 这个序列可以符合题意。

当然也有很多更加优秀的构造方法，但是我第一眼想到的是考虑这个序列是否直接是 $1, 2, \dots, n - 2, n - 1, n$ 这个排列进行简单变换得到的，事实也确实如此。

感觉这题还是偏向考察数学直觉了，贴一下代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
#define db double
#define vec vector
#define pll pair<ll, ll>
#define mkp make_pair
#define endl "\n"

using namespace std;

const ll mod = 998244353;

namespace fastio {
    char buf[1 << 21], *p1 = buf, *p2 = buf;
	
    const ll getc() {
        return p1 == p2 && ( p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1 ++;
    }
	
    const ll read() {
        ll x = 0, f = 1;
		
        char ch = getc();
		
        while (ch < '0' || ch > '9') {
            if (ch == '-') f = -1; ch = getc();
        }
		
        while (ch >= '0' && ch <= '9') {
            x = (x << 1) + (x << 3) + (ch ^ 48), ch = getc();
        }
		
        return x * f;
    }
	
    const void write(ll x) {
        if (x < 0) {
            putchar('-'), x = -x;
        }
		
        ll sta[35], top = 0;
	    
        do {
            sta[top++] = x % 10, x /= 10;
        } while (x);
	    
        while (top) putchar(sta[--top] + 48);
    }
}

#define rd fastio::read
#define wt fastio::write
#define gc fastio::getc

ll n, m, q, a[200005]; string s;

ll opt, l, r, ans = 0;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    
    ll i, j, k, x, y, z, res = 0, now;

    ll T = rd();

    while (T--) {
        n = rd();

        if (n % 2 == 0) {
            puts("-1");
        } else {
            for (i = n; i; i--) {
                wt(i), putchar(' ');
            }

            puts("");
        }
    }

    return 0;
}
```

[AC record](https://codeforces.com/contest/2091/submission/312808866)

---

## 作者：yehongxin (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF2091C)
### [原题传送门](https://codeforces.com/problemset/problem/2091/C)
### 题目大意
要进入一个房间，你必须通过选择正确的密码来打开一个圆形锁。密码是一个数字排列。其中只有一个固定点，也就是说，在每个循环移位中，恰好存在一个元素，其值等于其在置换中的位置。

排列的长度为 $n$，由数字 $1$ 到 $n$ 组成，每个数字只能出现一次。
### 解题方法
要输出密码，且最少有一个 $a_i$ 等于 $i$。经过模拟可以得到，当 $n$ 为偶数时，无法使一个 $a_i$ 等于 $i$，所以无解。当 $n$ 为奇数时，就可以输出排列。

题目说明了有多种解时，只要输出一种就可以了。所以当 $n$ 为奇数时，就有一种最简单的方法，就是输出从 $n$ 到 $1$ 这种排列。
### 核心代码

```cpp
if(n%2==0)cout<<"-1\n";
else
{
  for(int i=n;i>=1;i--)cout<<i<<" ";
  cout<<"\n";
}
```

---

## 作者：Andy1101 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF2091C)
# 思路
这题很明显要利用错位。

不难看出，当 $n$ 是偶数时无解。

而 $n$ 为奇数时就先输出不大于 $n$ 的所有奇数，再输出不大于 $n$ 的所有偶数即可。

# AC Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
void solve()
{
	int n;
	cin >>n;
	if(n%2==0)
	{
		cout <<-1<<"\n";
		return ;
	}
	else
	{
		for(int i=1;i<=n;i+=2) cout <<i<<" ";
		for(int i=2;i<=n;i+=2) cout <<i<<" ";
		cout <<'\n';
	}
}
int main()
{
	int t;
	cin >>t;
	while(t--)
	{
		solve();
	}
	return 0;
}

```

---

