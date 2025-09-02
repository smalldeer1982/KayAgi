# Sushi 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/s8pc-5/tasks/s8pc_5_a

E869120 は, AtCoder 回転寿司という店に行った.  
 この店には, $ N $ 個の寿司がある. 寿司にはそれぞれ $ 1,\ 2,\ 3,\ \cdots,\ N $ の番号がつけられている. 寿司 $ i $ は, 彼が来店してから $ a_i+kT $ 秒後 ($ k $ は $ 0 $ 以上の整数) のみに取ることができる.

彼は, 寿司 $ 1 $ → 寿司 $ 2 $ → … → 寿司 $ N $ という順番で食べたいと思っている. しかし, 彼は貪欲なので, 寿司を一度取ってしまうとすぐに食べてしまう. 彼が $ N $ 個の寿司を食べ終わるまで, 来店してから最短何秒かかるか求めよ. ただし, 寿司を取る時間・食べる時間は無視して良いものとし, 彼は来店して $ 0 $ 秒後に来る寿司も取ることができるものとする.

## 说明/提示

### 制約

- $ N $ は $ 1 $ 以上 $ 100 $ 以下の整数.
- $ T $ は $ 1 $ 以上 $ 100 $ 以下の整数.
- $ a_i $ は $ 0 $ 以上 $ T-1 $ 以下の整数 $ (1\ \leq\ i\ \leq\ N) $.
- $ 1\ \leq\ i\ <\ j\ \leq\ N $ に対し, $ a_i\ \neq\ a_j $.

### 小課題

小課題 $ 1 $ \[$ 100 $ 点\]

- $ N\ =\ 1 $.

小課題 $ 2 $ \[$ 100 $ 点\]

- 追加の制約はない.

### Sample Explanation 1

この場合, 寿司 $ 1 $ は来店してから $ 4,\ 10,\ 16,\ 22,\ 28,\ \cdots $ 秒後に取ることができる. 一番早いのは $ 4 $ 秒後である.

### Sample Explanation 2

寿司 $ 1,\ 2,\ 3 $ をそれぞれ $ 3,\ 7,\ 12 $ 秒後に取るのが最短である.

## 样例 #1

### 输入

```
1 6
4```

### 输出

```
4```

## 样例 #2

### 输入

```
3 10
3 7 2```

### 输出

```
12```

## 样例 #3

### 输入

```
6 15
8 6 9 1 2 0```

### 输出

```
45```

# 题解

## 作者：__UrFnr__ (赞：4)

~~看到这么水的题，蒟蒻马上来发波题解~~

**题目大意：**

$n$ 个寿司，第 $i$ 个寿司只能在他来店的第 $a_i+kT$ 才可以吃，求出吃完所有寿司所需的时间。

**题目思路：**

找出 $a_i>a_{i + 1}$ 的个数，也就是逆序对的数量，这个个数就是 $k$，最后输出 $a_n+kT$ 即可。

代码如下：


```cpp
#include <bits/stdc++.h>
using namespace std;
int n, t, a[110], ans;
signed main () {
    cin >> n >> t;
    for (int i = 1; i <= n; i ++) 
        cin >> a[i];
    for (int i = 1; i < n; i ++) 
        if (a[i] > a[i + 1]) 
            ans ++;
    cout << a[n] + ans * t;
}
```

---

## 作者：__XU__ (赞：3)

## AT\_s8pc\_5\_a Sushi 2 题解

### 题目大意：

有 $N$ 个寿司。第 $i$ 个寿司在 $a_{i} + kT$ 时间出现。若要按顺序吃完寿司，最短需要多少时间？

### 思路：

要求最小值，且数据不大，暴力枚举即可。但很显然有更好的做法。

### 解题做法：

如果你理解了题意，那这道题将变得很简单。实质上只需要我们求一个单向的逆序对的个数。即遍历数组一遍，开一个变量更新所需时间值即可。（可以自己出几个样例）。

### 补充：

按照这种做法，最后一个元素即 $a_n$ 是必取的。求每个寿司所带来的价值按原题目所给的式子，逆序对的数量 $\times\space T$ 即可。

## AC code

```
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=105;
int n,t;
int cnt,sum;
int a[N];
bool cmp(int a,int b){
	if(a<b){
		return true;
	}
	else{
		return false;
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);//加速 
	cin>>n>>t;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		if(cmp(a[i],a[i-1])==true){
			cnt++;
		}
		sum=cnt*t;
	}
//	cout<<cnt;
	cout<<sum+a[n];
	
	return 0;
}

```

谢谢观看。

---

## 作者：goIdie (赞：2)

## 思路

简单模拟。

题目给定第 $i$ 种寿司在 $a_i+kT$ 时才能吃，那么答案即为 $a_n+kT$，但是我们如何求 $k$ 呢？

思考一下，因为寿司是按顺序吃的，所以编号越靠前的寿司吃得越早，那么 $k$ 就为 $a_i>a_{i+1}$ 的个数，也就是逆序对的个数。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,a[101],sum;
int main(){
	cin>>n>>t;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<n;i++){
		if(a[i]>a[i+1]){
			sum++;
		}
	}
	cout<<a[n]+t*sum;
}
```

---

## 作者：King_and_Grey (赞：2)

## [AT_s8pc_5_a题解](/problem/AT_s8pc_5_a)

### 题目翻译：

有 $n$ 个寿司。第 $i$ 个寿司在 $a _ i + kT$ 时间出现，若要按顺序吃完寿司并且让时间最短。

这一题按照题意模拟就行，模拟完最后输出 $a_n + t \times x$（其中 $x$ [逆序对](https://blog.csdn.net/github_51186756/article/details/108871760#:~:text=%E5%8D%95%E9%93%BE%E8%A1%A8%E9%93%BE%E6%8E%A5%E7%9A%84%E6%96%B9%E5%90%91,%E9%92%88%E5%8F%98%E9%87%8F%E6%8C%87%E5%90%91X1%E3%80%82)的数量）。

**奉上 AC 代码：**
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k,ans;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n >> k;
	int a[n + 1];
	for(int i = 1;i <= n;i++){
		cin >> a[i];
	}
	for(int i = 2;i <= n;i++){
	    if(a[i] < a[i - 1]){
			ans++;
		}
	}
	cout << a[n] + ans * k << endl;
	return 0;
}
```

[通过记录。](https://www.luogu.com.cn/record/164892452)

谢谢观看！！！

---

## 作者：renzhanwen (赞：1)

他想要按照从寿司 $$1$$ 到寿司 $$n$$ 的顺序来吃寿司。如果他吃第 $$i$$ 寿司的时间大于他吃第 $$i+1$$ 个寿司的时间，也就是 $$$$a_i >a_{i+1}$$$$，$$k$$ 将要加 $$1$$。你将会发现，这个 $$k$$ 就是**逆序对**的个数。所以第 $$i$$ 个寿司的答案为 $$a_i+k \times t$$，第 $$n$$ 个寿司的答案为 $$a_n+k \times t$$。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,a[105],k; 
int main()
{
	cin>>n>>t;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<n;i++)
		if(a[i]>a[i+1])
			k++;
	cout<<a[n]+k*t<<endl;
    return 0;
}
```

---

## 作者：Malkin_Moonlight (赞：1)

# 题解：AT_s8pc_5_a Sushi 2
# 0x00 前言
~~不是这题怎么还没上翻译啊，先上一波翻译。~~

E869120 去了一个名为 AtCoder 的旋转寿司店。这家店有 $N$ 种寿司。每个寿司都被标记了从 $1$ 到 $N$ 的编号。寿司 $i$ 只能在他来到店里的时候，以及他来到店里的 $a_i+kT$ 秒后 ($k\geq 0$) 才能取。

他想要按照从寿司 $1$ 到寿司 $N$ 的顺序来吃寿司。但是他很贪心，所以他一旦拿到寿司，就会立刻把它吃掉。请计算他至少需要多久才能吃完 $N$ 种寿司。注意，您可以忽略获取和吃掉寿司所需的时间，并认为他可以在来到店里的 $0$ 秒就拿起寿司。

# 0x01 思路
直接按题意模拟即可，不知道大佬们为什么要搞什么逆序对。

首先我们按题意读入数据。根据题意，后面的寿司不能在前面的前前面就吃，我们需要注意，后面的寿司吃到的时间必须大于等于前面的寿司吃到的时间。

我们定义一个变量 $k$，如果拿 $k$ 算出的这个寿司吃的时间小于下一个寿司最小拿到的时间，那我们就把变量 $k$ 加上 $1$。

# 0x02 代码

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <map>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
#define endl '\n'
#define pb emplace_back
const ll MAXN = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll dx[] = {0, 0, 1, -1};
const ll dy[] = {1, -1, 0, 0};
ll n, k, t, ans;
ll a[105], record[105];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
    cin >> n >> t;
    for (int i = 1; i <= n; i++)
    {
    	cin >> a[i];
	}
	for (int i = 1; i <= n; i++)
	{
		while (a[i] + k * t < record[i - 1]) k++;
    	record[i] = a[i] + k * t;
    	ans = record[i];
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Failure_Terminator (赞：1)

## Problem

有 $n$ 种寿司，第 $i$ 个附带一个时间值 $a_i$。

第 $i$ 种寿司会于 $a_i + kT$ 时间产生，其中 $T$ 被给定，$k \ge 0$。

某人要从第 $1$ 种吃到第 $n$ 种，但是种类在后的寿司吃到的时间必须**大于等于**种类在前的寿司吃到的时间。

求吃过 $n$ 种寿司的时间的最小值。

## Solution

入门题，按题意模拟即可。

加粗的是坑点，海默就在这挂了好几次。

用一个变量 $p$ 记录 $k$，再用一个变量记录当前的时间。

若用 $p$ 所算出的时间小于当前的时间，则将 $p$ 增加 $1$。

最后算出的时间即为答案。

时间复杂度 $\Theta(n)$。

## AC Code

[Link](https://atcoder.jp/contests/s8pc-5/submissions/36476492)

---

## 作者：nightwatch.ryan (赞：1)

### 思路
要求将寿司按顺序吃完，那么顺序靠前的吃的肯定越早。

所以我们可以统计 $a_i>a_{i+1}$ 的个数，乘上 $T$，并且还要加上最后一个寿司的 $a_n$，因为不能早于这个时间。
### 代码
```cpp
#include<iostream>
#define N 105
int a[N],n,t,cnt;
signed main(){
	std::cin>>n>>t;
	for(int i=1;i<=n;i++)std::cin>>a[i];
	for(int i=1;i<n;i++)
		if(a[i]>a[i+1])
			cnt++;
	std::cout<<a[n]+t*cnt;
}
```

---

## 作者：GuoMingXuants1 (赞：0)

## 思路
这道题可能看上去比较毒瘤，其实思路并不是很难，我们只需要依照题意作答即可。

这道题的整体大意就是给定取食第 $ i $ 个寿司需要在 $ a_i + kT $ 时才能取食，求取食完所有寿司所用的最少时间，其中不计进食的时间，默认为 $ 0 $ 秒。

很明显，假定有 $ n $ 个寿司，我们只需要求第 $ n $ 个寿司在何时才能取食，即 $ a_n + kT $。

好了，我们现在只需要求 $ k $ 就行了，依据题意，主人公比较贪婪，必须按顺序来取，后面的寿司必须在前面的寿司取食完后才能取食，即取食到后面寿司的时间不能小于取食到前面寿司的时间，这时，$ k $ 就是逆序对的数量（即 $a_i > a_{i+1}$ 的数量），我们只需要查找逆序对的数量并标记即可。

## 代码


```cpp
#include<iostream>
using namespace std;
int main()
{
    int n,t;
    int a[150];
    cin>>n>>t;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    int count;
    count = 0;
    for(int i=1;i<=n-1;i++)
    {
        if(a[i+1]<a[i])
        {
            count++;
        }
    }
    int s;
    s = a[n] + count*t;
    cout<<s<<endl;
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_s8pc_5_a)

~~一道大 water 题。~~ 

### 思路
对于第 $i$ 个寿司，所需要的答案为 $a_i+kT$，所以最终的答案即为 $a_n+kT$，所以此时的问题就是要得出 $k$ 的值。

不难想到 $k$ 为 $a_i>a_{i+1}$ 的个数，于是问题就迎刃而解了。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,T,a[101],k;
int main(){
	cin>>n>>T;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<n;i++) if(a[i]>a[i+1]) k++;
	cout<<a[n]+T*k;
}
```

---

## 作者：tanzexiaodezhonghao (赞：0)

## 思路
~~一道简单题居然还没有关题解通道。~~

大意：$n$ 个寿司，每个寿司在 $a_i+kT$ 时可以开始吃。问：按顺序吃完全部寿司的最短时间是多少？

考虑暴力，可以通过，但不是最优解。事实上 $k$ 就是逆序对数，计算方式为 $a_n+kT$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=105;
int a[N],n,T,k;
int main(){
	cin>>n>>T;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=2;i<=n;i++){
	    if(a[i]<a[i-1]) k++;
	}
	cout<<a[n]+k*T<<endl;//别忘了换行!!! 
}
```

---

## 作者：Melo_DDD (赞：0)

很水的入门模拟题。

# 题目大意

给定 $\{a_i\mid i \in[1,n] \cap\Z\}$ 和 $T$，每个寿司可食用时间为 $a_i + k \times T$，且**下一个寿司不能在上一个前食用**，求最短所需时间。

# 题目实现

按题意模拟即可。

模拟 $k$ 的值直到满足题意，更新时间即可。

## 代码

```cpp
#include <bits/stdc++.h>
#define f(i ,m ,n ,x) for (int i = (m) ;i <= (n) ;i += (x))
using namespace std ;
const int N = 107 ;
int n ,t ,a[N] ,sum[N] ,ans ,k ;
template <typename T> inline void read (T &x) {
	x = 0 ;
	bool flag (0) ;
	register char ch = getchar () ;
	while (! isdigit (ch)) {
		flag = ch == '-' ;
		ch = getchar () ;
	}
	while (isdigit (ch)) {
		x = (x << 1) + (x << 3) + (ch ^ 48) ;
		ch = getchar () ;
	}
	flag ? x = -x : 0 ;
}
int main () {
	read (n) ,read (t) ;
	f (i ,1 ,n ,1) {
		read (a[i]) ;
	}
	f (i ,1 ,n ,1) {
		while (a[i] + k * t < sum[i - 1]) k ++ ;
		sum[i] = a[i] + k * t ;
		ans = sum[i] ;
	} 
	cout << ans << '\n' ;
	return 0 ;
}
```

---

## 作者：Programming_Konjac (赞：0)

# 思路
找出寿司中逆序对出现的数量，这就是答案的最优选择的一部分。

让题目中的人物选择最后一个寿司，也就是 $a_n$，根据公式 $a_i+k\times t$，带入以上的条件，输出就是 $a_n+t\times q$，$q$ 为逆序对的数量。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,t,a[110],i,q=0; 
	cin>>n>>t;
	for(i=0;i<n;i++) cin>>a[i];
	for(i=1;i<n;i++) if(a[i]<a[i-1]) q++; 
	cout<<a[n-1]+q*t; 
}
```

---

## 作者：DGL__DGL_AFO (赞：0)

 [传送门](https://www.luogu.com.cn/problem/AT_s8pc_5_a)
## 分析
先输入 $n$ 个寿司的基础时间，然后从第 $1$ 个寿司开始计算最短时间。

第 $i$ 个寿司所需时间要大于等于第 $i-1$ 个寿司的时间。

因为寿司数少于 $100$，直接枚举即可。


## 代码
```
#include<bits/stdc++.h>
using namespace std;
int n,t,a[1145],b[1145];//记录第i个寿司的价值和吃完第i个寿司的时间
int ans;
int Main()
{
	cin>>n>>t;
	cin>>a[1];
	b[1]=a[1];
	ans=a[1];
	for(int i=2;i<=n;i++)
	{
		cin>>a[i];
		for(int j=0;;j++)
		{
			if(a[i]+j*t>=b[i-1])//与第i-1个吃完的寿司比较时间
			{
				b[i]=a[i]+j*t;
				ans=b[i];
				break;
			}
		}
	}
		
  cout<<ans;
	
	
	return 0;
}
```


---

