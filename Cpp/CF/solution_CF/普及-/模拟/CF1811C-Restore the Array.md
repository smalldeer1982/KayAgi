# Restore the Array

## 题目描述

Kristina 有一个包含 $ n $ 个**非负整数**的数组 $ a $。

她构造了一个长度为 $ n - 1 $ 的新数组 $ b $，使得 $ b_i = \max(a_i, a_{i + 1}) \text{ } (1 \le i \le n - 1) $。

例如，假设 Kristina 有一个长度为 $ 5 $ 的数组 $ a = [ 3, 0, 4, 0, 5 ] $，则她将以以下方式构造数组 $ b $：

1. $ b_1 = \max(a_1, a_2) = \max(3, 0) = 3; $
2. $ b_2 = \max(a_2, a_3) = \max(0, 4) = 4; $
3. $ b_3 = \max(a_3, a_4) = \max(4, 0) = 4; $
4. $ b_4 = \max(a_4, a_5) = \max(0, 5) = 5. $

所以，她得到了一个长度为 $ 4 $ 的数组 $ b = [ 3, 4, 4, 5 ] $。

现在，你只知道数组 $ b $。你需要找出**任意一个**可能的数组 $ a $。



对于第二组测试数据，我们可以从 $ a = [ 2, 2, 1, 1 ] $ 推出 $ b = [ 2, 2, 1 ] $：

* $ b_1 = \max(a_1, a_2) = \max(2, 2) = 2; $
* $ b_2 = \max(a_2, a_3) = \max(2, 1) = 2; $
* $ b_3 = \max(a_3, a_4) = \max(1, 1) = 1. $

对于第三组测试数据，数组 $ b $ 中的所有元素均为 $ 0 $，因为 $ b $ 中的每个元素均为 $ a $ 中两个相邻元素的最大值，所以数组 $ a $ 中的每个元素均为 $ 0 $。

对于第四组测试数据，我们可以从 $ a = [ 0, 0, 3, 4, 3, 3 ] $ 推出 $ b = [ 0, 3, 4, 3, 3 ] $：

* $ b_1 = \max(a_1, a_2) = \max(0, 0) = 0; $
* $ b_2 = \max(a_2, a_3) = \max(0, 3) = 3; $
* $ b_3 = \max(a_3, a_4) = \max(3, 4) = 4; $
* $ b_4 = \max(a_4, a_5) = \max(4, 3) = 4; $
* $ b_5 = \max(a_5, a_6) = \max(3, 3) = 3. $

## 样例 #1

### 输入

```
11
5
3 4 4 5
4
2 2 1
5
0 0 0 0
6
0 3 4 4 3
2
10
4
3 3 3
5
4 2 5 5
4
3 3 3
4
2 1 0
3
4 4
6
8 1 3 5 10```

### 输出

```
3 0 4 0 5
2 2 1 1
0 0 0 0 0
0 0 3 4 3 3
10 10
3 3 3 1
4 2 2 5 5
3 3 3 3
2 1 0 0
2 4 4
8 1 1 3 5 10```

# 题解

## 作者：MarsTraveller (赞：8)

## 翻译：
定义 $b_i = \max(a_i,a_{i+1})$，先给出 $b$ 数组，求其中一种 $a$ 数组。
输入 $t$ 组数据，每组数据中输入 $n$ 表示 $a$ 数组的长度，再输入 $b$ 数组。

**注意： $b$ 数组的长度为 $n-1$。**

## 分析：
根据题目的定义，可以发现： $\begin{cases}
  b_i = \max({\color{red}a_i},a_{i+1}) \\
  b_{i-1} = \max(a_{i-1},{\color{red}a_i})
\end{cases}$

观察标红的部分，可以得出： $\begin{cases}
 a_i \le b_i \\
 a_i \le b_{i-1}
\end{cases}$，即： $a_i \le \min(b_i,b_{i-1})$。

那么只要符合这一式子的 $a_i$ 都是合法的，这里我们取 $a_i = \min(b_i,b_{i-1})$。

## 代码：
```cpp
#include <iostream>
#define big long long
using namespace std;
big t,n,b[200005],a[200005];
int main()
{
    cin >> t;
    while(t--)
    {
        cin >> n;
        for(big i = 1;i < n;i++)//注意b数组长度。
        {
            cin >> b[i];
        }
        b[0] = b[1];
        b[n] = b[n-1];//为了防止a数组开头和结尾出错，即a数组开头结尾与b数组相等。
        for(big i = 1;i <= n;i++)
        {
            a[i] = min(b[i],b[i-1]);
            cout << a[i] << " ";
        }
        cout << endl;
    }
    return 0;
}
```
完结，撒花！

---

## 作者：Coffee_zzz (赞：4)

### 思路

显然 $a_n$ 的值只对 $b_{n-1}$ 有影响。那我们让 $a_n=b_{n-1}$，只要保证 $a_{n-1} \le b_{n-1}$，$a_n$ 和 $a_{n-1}$ 就是满足条件的。

同时，我们还希望 $a_{n-1}=b_{n-2}$，因为这样的话，只要 $a_{n-2}\le b_{n-2}$，$a_{n-1}$ 和 $a_{n-2}$ 就是满足条件的。

所以，只要 $b_{n-2}\le b_{n-1}$，我们就可以让 $a_{n-1}=b_{n-2}$。

依次类推，只要 $b_{i-1} \le b_i$，我们就可以让 $a_i=b_{i-1}$；反之，若 $b_{i-1} > b_i$，$a_i$ 就最多只能等于 $b_i$ 了，

于是我们就可以愉快地开始构造了。注意别忘了给 $b_0$ 赋一个极大值。

### 代码

```c++
#include <bits/stdc++.h>

using namespace std;
namespace IO{
	char ibuf[(1<<20)+1],*iS,*iT;
	#if ONLINE_JUDGE
	#define gh() (iS==iT?iT=(iS=ibuf)+fread(ibuf,1,(1<<20)+1,stdin),(iS==iT?EOF:*iS++):*iS++)
	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read(){
		reg char ch=gh();
		reg long long x=0;
		reg char t=0;
		while(ch<'0'||ch>'9')   t|=ch=='-',ch=gh();
		while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=gh();
		return t?-x:x;
	}
}
using IO::read;
const int N=2e5+5;
int a[N],b[N];
void solve(){
	int n;
	n=read();
	for(int i=1;i<n;i++) b[i]=read();
	a[n]=b[n-1];
	b[0]=1e9;
	for(int i=n-1;i>=1;i--){
		if(b[i-1]<b[i]) a[i]=b[i-1];
		else a[i]=b[i];
	}
	for(int i=1;i<=n;i++) cout<<a[i]<<' ';
	cout<<endl;
}
signed main(){
	int t;
	t=read();
	for(int temp=0;temp<t;temp++) solve();
	return 0;
}
```

---

## 作者：hycqwq (赞：1)

## 思路

![](https://cdn.luogu.com.cn/upload/image_hosting/m5b1vcg6.png)

观察上面这张图，发现除首尾外，$a$ 数组的每个元素会对 $b$ 数组中的两个元素产生影响。

而要控制它所产生的影响，我们只需要将 $a_i$ 设为 $b$ 中在它两边的元素的最小值，即：

$$a_i = \begin{cases}
b_i & i = 1 \\
b_{i - 1} & i = n \\
\min(b_i, b_{i - 1}) & \text{otherwise}
\end{cases}
$$

## 代码

**注意：$b$ 的大小为 $n - 1$！**

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include <cctype>
#include <cmath>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>
using namespace std;
typedef long long ll;
const int inf = 0x3f3f3f3f;
#define elif else if

int t, n, b[200005];
vector<int> a;

int main()
{
    cin >> t;
    for (int i = 1; i <= t; i++)
    {
        cin >> n;
        for (int j = 1; j < n; j++)
            cin >> b[j];
        a.clear();
        a.push_back(b[1]);
        for (int j = 1; j < n - 1; j++)
            a.push_back(min(b[j], b[j + 1]));
        a.push_back(b[n - 1]);
        for (auto i : a)
            cout << i << " ";
        cout << endl;
    }
    return 0;
}
```

---

## 作者：隐仞Mrsu (赞：0)

# 题意
给定 $n-1$ 长的数组 $b$，要求出 $n$ 长的数组 $a$。

其中，对于 $1\le i<n$，需满足 $b_i=\max(a_i,a_{i+1})$。

题目保证给定的数组 $b$ 一定能求出数组 $a$。

# 分析
数组中，$a_1$ 只与 $b_1$ 有关，$a_n$ 只与 $b_{n-1}$ 有关。

于是，直接设 $a_1=b_1$，以及 $a_n=b_{n-1}$。

而对于剩下的 $1<i<n$，分为两种情况讨论。

### 当 $b_i\ge b_{i-1}$ 时
若 $a_i=b_i$，则 $\max(a_{i-1},a_i)=\max(a_{i-1},b_i)\ge b_{i-1}$，不一定满足题目条件 $b_{i-1}=\max(a_{i-1},a_i)$。

则此时需令 $a_i=b_{i-1}$。

### 当 $b_i<b_{i-1}$ 时
若 $a_i=b_{i-1}$，则 $\max(a_i,a_{i+1})=\max(b_{i-1},a_{i+1})> b_i$，不一定满足题目条件 $b_i=\max(a_i,a_{i+1})$。

则此时需令 $a_i=b_i$。

# 代码
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 2e5+5;
LL _,a[N],b[N],n;
void work(){
	cin>>n;
	for(LL i=1;i<n;i++){
		cin>>b[i];
	}
	a[1]=b[1];
	a[n]=b[n-1];
	for(LL i=2;i<n;i++){
		if(b[i]>=b[i-1]){
			a[i]=b[i-1];
		}
		else{
			a[i]=b[i];
		}
	}
	for(LL i=1;i<=n;i++){
		cout<<a[i]<<' ';
	}
	cout<<'\n';
}
int main(){
	ios::sync_with_stdio(false);
	cin>>_;
	while(_--){
		work();
	}
}
```


---

## 作者：zeekliu (赞：0)

稍加考虑可以发现，只有两头的两个数不会被两个最大值影响，所以，这两个位子可以直接填它旁边的那个最大值，这两个要特殊处理。

那其他的怎么办？我们设当前为 $b$ 数组中的第 $i$ 个位置，那么如果 $b_{i+1} > b_{i}$，说明 $b_i$ 和 $b_{i+1}$ 之间共用的位置 $a_{i+1}$ 肯定要跟随最大值更小的，即 $b_{i+1}$，所以 $a_{i+1}$ 的位置填 $b_{i+1}$。

类似的，当 $b_{i+1} < b_{i}$ 时，$a_{i+1}$ 就填值更小的 $b_{i}$。

所以，这样从左到右算一遍就行了，时间复杂度 $O(n)$。

代码：

```cpp
//CF1811C 23.04.13 *1100
#include <bits/stdc++.h>
using namespace std;
int n,a[200010];

inline void solve()
{
    cin>>n;
    for (int i=1;i<n;i++) cin>>a[i];  
    cout<<a[1]<<" ";
    for (int i=1;i<n-1;i++)
    {
        if (a[i]<a[i+1]) cout<<a[i]<<" ";
        else cout<<a[i+1]<<" ";
    }
    cout<<a[n-1]<<endl;
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int _; cin>>_;
    while (_--) solve();
    exit(0);
}
```

---

## 作者：Iniaugoty (赞：0)

[洛谷传送门](/problem/CF1811C)，[Codeforces 传送门](https://codeforces.com/contest/1811/problem/C)。

***

## 题意

对于一个数列 $a_i(1\le i\le n)$，设 $b_i=\max\{a_i,a_{i+1}\}(1\le i<n)$。

给出 $b$，求出一种满足条件的 $a$。

***

## 解法

显然 $a_n$ 最大不会超过 $b_{n-1}$，那就让 $a_n\gets b_{n-1}$ 好了，这么做并不会对其它 $b_i$ 产生影响。

然后考虑 $(1,n)$ 中的 $a_i$。

由题意（这几个字在不好写过程的数学题非常好用），有：

$$b_i=\max\{a_i,a_{i+1}\}$$

$$b_{i-1}=\max\{a_{i-1},a_i\}$$

也就是一定有 $a_i\le b_i$ **且** $a_i\le b_{i-1}$，那就让 $a_i\gets \min\{b_i,b_{i-1}\}$ 好了。

最后，$a_1\gets b_1$。

***

## 代码

```cpp
#include<bits/stdc++.h>
#define N 200005
using namespace std;
int t,n,a[N],b[N];
signed main(){
	cin>>t;
	while(t--){
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		cin>>n;
		for(int i=1;i<n;i++)
			cin>>b[i];
		a[n]=b[n-1],a[1]=b[1];
		for(int i=n-1;i>1;i--){//我也不知道为什么我赛时会打出这个顺序的循环
			a[i]=min(b[i],b[i-1]);
		}
		for(int i=1;i<=n;i++)
			cout<<a[i]<<' ';
		cout<<'\n';
	}
	return 0;
}
```

***

全文完。

---

## 作者：abensyl (赞：0)

原题传送门：[CF1811C Restore the Array](https://www.luogu.com.cn/problem/CF1811C)。

看到很多人说 C 比 D 难，但是我个人认为 C 比 D 简单得多。

## 思路

这道题目让我们构造一个长度为 $n$ 的序列 $a$，使得序列 $[\max(a_1,a_2),\max(a_2,a_3),\dots,\max(a_{n-1},a_n)]$ 与给定的序列 $b$ 相等。

解决此问题的构造方案为:

- 对于 $i=1$ 时，$a_i=b_i$；  
- 对于 $i\in [2,n-1]$ 时，$a_i=\min(b_i,b_{i+1})$；  
- 对于 $i=n$ 时，$a_n=b_{n-1}$。

### &#9733; 为什么这个解决方案是正确的呢？ 

那么，我们会发现对于任意一个 $b_i$，它的值的来源有两种可能。

- $a_i > a_{i+1}$，$b_i=a_i$；  
- $a_i < a_{i+1}$，$b_i=a_{i+1}$。

其中，对于 $b_i$，我将 $a_i$ 称为 $l_i$，将 $a_{i+1}$ 称为 $r_i$，那么 $a_i$ 理论上应该等于 $\max(l_i,r_i)$，如果理论与现实相符，则假设成立。

首先，对于 $b_1$，其 $l_i=b_1$，$r_i=\min(b_1,b_2)$，则 $b_1 = \max(b_1,\min(b_1,b_2))$，分类讨论易得，$b_1=b_1$，成立，同时 $b_{n-1}$ 也是同样的道理。

其次，对于 $b_i(i\in [2,n-2])$，$l_i=\min(b_{i-1},b_i)$，$r_i=\min(b_i,b_{i+1})$，则 $b_i=\max(\min(b_{i-1},b_i),\min(b_i,b_{i+1}))$，分类讨论，可得，$b_i=b_i$，成立。

那么，构造正确，化简后可以写出以下代码。

## 代码

```cpp
#include <iostream>
using namespace std;
const int N = 5e5 + 6;
int a[N], b[N];
int main() {
  int TT;
  cin >> TT;
  while (TT--) {
    int n;
    cin >> n;
    for (int i = 1; i < n; ++i) cin >> b[i];
    a[1] = b[1];
    for (int i = 1, j = 2; j <= n; ++i, ++j) {
      if (b[i] < a[i]) a[i] = b[i];
      a[j] = b[i];
    }
    for (int i = 1; i <= n; ++i) cout << a[i] << ' ';
    cout << '\n';
  }
  return 0;
}
```

我的 [AC 记录](https://codeforces.com/contest/1811/submission/200714353)。

---

## 作者：sto_5k_orz (赞：0)

构造题。

$b_i=\max(a_i,a_{i+1})$。

那么 $a_i\leq b_i,a_i\leq b_{i-1}$。

不妨直接设 $a_1=b_1,a_n=b_{n-1}$。

当 $2\leq i\leq n$ 时，$a_i=\min(b_i,b_{i-1})$。

那么数组为 $b_1,\min(b_1,b_2),\min(b_2,b_3)\cdots b_{n-1}$。

求 $\max$ 即为 $b_1,b_2,b_3\cdots b_{n-1}$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define gc getchar
#define pc putchar
#define W while
#define I inline
namespace SlowIO{
	I int read() {
		int x = 0, f = 1; char ch = gc();
		W(ch < '0' || ch > '9') {if(ch == '-') f = -f; ch = gc();}
		W(ch >= '0' && ch <= '9') x = x * 10 + (ch ^ 48), ch = gc();
		return x * f;
	}
	I void Read(int &x) {x = read();}
	I void write(int x) {
		if(x < 0) pc('-'), x = -x;
		if(x > 9) write(x / 10);
		pc(x % 10 + '0');
	}
	I void writeln(int x) {write(x); pc('\n');}
} using namespace SlowIO;
const int N = 200010; int a[N], b[N];
int main() {
	int t; Read(t);
	W(t--) {
		int n, pos, mi = 2e9; Read(n); for(int i = 1; i < n; i++) Read(b[i]);
		if(n == 2) {Write(b[1]), Write(b[1]); continue;}
		Write(b[1]);
		for(int i = 2; i < n; i++) {
			Write(min(b[i - 1], b[i]));
		}
		Write(b[n - 1]);
		pc('\n');
	}
	return 0;
}
```

---

