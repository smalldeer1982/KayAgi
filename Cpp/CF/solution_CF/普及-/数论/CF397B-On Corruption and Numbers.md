# On Corruption and Numbers

## 题目描述

Alexey, a merry Berland entrant, got sick of the gray reality and he zealously wants to go to university. There are a lot of universities nowadays, so Alexey is getting lost in the diversity — he has not yet decided what profession he wants to get. At school, he had bad grades in all subjects, and it's only thanks to wealthy parents that he was able to obtain the graduation certificate.

The situation is complicated by the fact that each high education institution has the determined amount of voluntary donations, paid by the new students for admission — $ n_{i} $ berubleys. He cannot pay more than $ n_{i} $ , because then the difference between the paid amount and $ n_{i} $ can be regarded as a bribe!

Each rector is wearing the distinctive uniform of his university. Therefore, the uniform's pockets cannot contain coins of denomination more than $ r_{i} $ . The rector also does not carry coins of denomination less than $ l_{i} $ in his pocket — because if everyone pays him with so small coins, they gather a lot of weight and the pocket tears. Therefore, a donation can be paid only by coins of denomination $ x $ berubleys, where $ l_{i}<=x<=r_{i} $ (Berland uses coins of any positive integer denomination). Alexey can use the coins of different denominations and he can use the coins of the same denomination any number of times. When Alexey was first confronted with such orders, he was puzzled because it turned out that not all universities can accept him! Alexey is very afraid of going into the army (even though he had long wanted to get the green uniform, but his dad says that the army bullies will beat his son and he cannot pay to ensure the boy's safety). So, Alexey wants to know for sure which universities he can enter so that he could quickly choose his alma mater.

Thanks to the parents, Alexey is not limited in money and we can assume that he has an unlimited number of coins of each type.

In other words, you are given $ t $ requests, each of them contains numbers $ n_{i},l_{i},r_{i} $ . For each query you need to answer, whether it is possible to gather the sum of exactly $ n_{i} $ berubleys using only coins with an integer denomination from $ l_{i} $ to $ r_{i} $ berubleys. You can use coins of different denominations. Coins of each denomination can be used any number of times.

## 说明/提示

You can pay the donation to the first university with two coins: one of denomination 2 and one of denomination 3 berubleys. The donation to the second university cannot be paid.

## 样例 #1

### 输入

```
2
5 2 3
6 4 5
```

### 输出

```
Yes
No
```

# 题解

## 作者：very_easy (赞：2)

# 题意
这题的题意（~~为什么没有翻译啊！~~）是：

你有一些硬币，面值是 $l\sim r (\le 10^9)$，问能不能凑出面值 $n (\le 10^9)$，如果可以就输出 ```Yes```，否则就输出 ```No```。

# 思路
如果要凑的 $n<l$，很明显是无解的，直接输出 No 就可以了，否则就判断 $\left\lceil\dfrac{n}{r}\right\rceil$，这样就可以确定下限，而上限也很好找，就是 $\left\lfloor\dfrac{n}{l}\right\rfloor$，也就是在 $\left\lceil\dfrac{n}{r}\right\rceil\times l$ 到 $\left\lfloor\dfrac{n}{l}\right\rfloor \times r$ 的范围内就一定可以凑出。

注意这个范围```int```可能会爆，所以要开```long long```。

# AC Code
```c++
#include<bits/stdc++.h>
using namespace std;
long long t,n,l,r;
int main(){
	cin>>t;
	while(t--){//有多组数据 
		cin>>n>>l>>r;
		if(n<l){//特判 
			cout<<"No"<<endl;
			continue;
		}
		//(n-1)/r+1为n/r上取整,(n/l)会自动下取整 
		if(n>=((n-1)/r+1)*l&&n<=(n/l)*r){
			cout<<"Yes"<<endl;
		}
		else{
			cout<<"No"<<endl;
		}
	}
	return 0;
}
```

---

## 作者：Paris_Commune (赞：1)

### 分析

分类讨论

- $l>n$，输出 `No`。
- $l\le n$，如果要凑出 $n$ 元，最少需要 $\lceil \frac{n}{r} \rceil$ 个硬币，最多需要 $\lceil \frac{n}{r} \rceil$，最多硬币数量为 $\lfloor \frac{n}{l} \rfloor$，设能凑到的钱的区间为 $m$，则 $\lceil \frac{n}{r} \rceil\times{l} \le m\le \lfloor \frac{n}{l} \rfloor\times{r}$。

### AC 代码

```
#include <bits/stdc++.h>
#define int long long 
//注意开 long long 
using namespace std;
signed main(){
    int t;
    cin>>t;
    while(t--){
    	int n,l,r;
    	cin>>n>>l>>r;
    	if(n<l){
    		cout<<"No\n";
    		continue;
        }
    	if(n>=((n-1)/r+1)*l&&n<=(n/l)*r){
    		cout<<"Yes\n";
		}
    	else{
    		cout<<"No\n";
		}
    }
    return 0;
}
```

---

## 作者：BqtMtsZDnlpsT (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF397B)

### 题意简述：
你拥有面值为 $l_i$ 到 $r_i\;(1\le l_i\le r_i\le10^9)$ 的硬币，每种面值都有无数个，现在问能否用这些硬币恰好凑 $n_i\;(1\le n_i\le10^9)$ 元？

第一行输入一个正整数 $t$，表示有 $t\;(1\le t\le10^3)$ 组数据。
接下来输入 $t$ 行，每行 $3$ 个正整数,依次为 $n_i,l_i,r_i$。

对于每组数据，若可以用完，输出 `Yes`，反之输出 `No`。
### 解题思路

- 如果 $n_i<l_i$ 很容易发现无解。
- 反之我们考虑凑出 $n_i$ 所需硬币数量。
	
    很容易发现所需硬币数量的最小值为 $\lceil \frac{n_i}{r_i}\rceil$，最大值为 $\lfloor \frac{n_i}{l_i}\rfloor$。
    
    因为你拥有面值为 $l_i$ 到 $r_i$ 的硬币，每种面值都有无数个，所以，在最小值为 $\lceil \frac{n_i}{r_i}\rceil$，最大值为 $\lfloor \frac{n_i}{l_i}\rfloor$ 的前提下，可以凑钱的范围是 $\lceil \frac{n_i}{r_i}\rceil \times l_i $ 到 $\lfloor \frac{n_i}{l_i}\rfloor \times r_i$，且这个区间内任意一种都能凑出。
    
    注意：$\lceil \frac{n_i}{r_i}\rceil \times l_i $ 和 $\lfloor \frac{n_i}{l_i}\rfloor \times r_i$ 可能超出 `int` 范围。
    
    所以只需判断 $n_i$ 是否在上述区间内即可。
    
代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define int long long
using namespace std;
int t,n,l,r;
signed main(){
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld%lld%lld",&n,&l,&r);
		if(n<l){puts("No");continue;}
		if(n>=((n-1)/r+1)*l&&n<=(n/l)*r)puts("Yes");
		else puts("No");
	}
	return 0;
}
```

---

## 作者：zjjc1104111 (赞：0)

# 思路

首先，如果 ${n}$ 比 ${l}$ 小，那么一定凑不成，直接输出 ```No```。

接着，我们可以发现，凑出 ${n}$ 元所需要的最少硬币数量为 $\lceil \frac{n}{r} \rceil$ ,最多硬币数量为 $\lfloor \frac{n}{l} \rfloor$，那么我们能凑到的钱的区间就是 $\lceil \frac{n}{r} \rceil\times{l}$ 到 $\lfloor \frac{n}{l} \rfloor\times{r}$，那么只需要判断 ${n}$ 是否在这个区间里就行了。

别忘了开 ```long long```。

# Code

```
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
    	long long n,l,r;
    	cin>>n>>l>>r;
    	if(n<l){//特判
    		cout<<"No\n";
    		continue;
        }
    	if(ceil(n/r)*l<=n && floor(n/l)*r>=n) cout<<"Yes\n";//记得换行
    	else cout<<"No\n";
    }
    return 0;
}
```



---

## 作者：zhang_Jimmy (赞：0)

思路：

首先 $n < l$ 显然无法凑够，直接输出 `No`。


我们可以发现所需硬币数量的最小值为 $\lceil \frac{n}{r_i} \rceil$，最大值为 $\lfloor \frac{n}{l_i} \rfloor$。在这个前提下，我们能凑到钱的范围是 $\lceil \frac{n}{r_i} \rceil \times l_i$ 到 $\lfloor \frac{n}{l_i} \rfloor \times r_i$，且这个区间里的钱都能凑到。

记得开 `long long`。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,l,r;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>l>>r;
		if(n<l)
		{
			cout<<"No\n";
			continue;
		}
		if(n>=ceil(n/r)*l&&n<=(n/l)*r)
		cout<<"Yes\n";
		else cout<<"No\n";
	}
}
```


---

## 作者：drah_yrev (赞：0)

## 题意
你拥有面值为 $l$ 到 $r$ 的钱，每种面值都有无数个，问是否可以求出 $n$ 元？

## 思路
如果 $n<l$，说明无法求解。

不然，
我们知道，可以求出的最小钱数为：$\left\lceil\dfrac{n}{r}\right\rceil$。

最大钱数为：
$\left\lfloor\dfrac{n}{l}\right\rfloor$。

只要在此区间内的任何一个数，都可以求出来。

注意：不开 `long long` 见祖宗。
## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
using namespace std;
long long int t,n,l,r;//要开 long long 
signed main() {
	cin>>t;
	while(t--) {
		cin>>n>>l>>r;
		if(n<l){//n<l，说明无法求出 
			cout<<"No\n";
			continue;
		}
		if(n>=((n-1)/r+1)*l&&n<=n/l*r){//在区间内 
			cout<<"Yes\n";
		} else {
			cout<<"No\n";
		}
	}
	return 0;
}
```


---

## 作者：__HHX__ (赞：0)

# 思路（小学数学）
假设我们全取 $l$，一共有 $\lfloor {n \over l} \rfloor$ 个硬币。

从面值 $l$ 到面值 $r$ 会增加 $r - l$。

那我只需保证 $\lfloor {n \over l} \rfloor \times l \le n \le \lfloor {n \over l} \rfloor \times (r - l) + \lfloor {n \over l} \rfloor \times l$ 就可以了。

稍微变形 $0 \le n- \lfloor {n \over l} \rfloor \times l \le \lfloor {n \over l} \rfloor \times (r - l)$。
# 代码
```cpp
#include<iostream>

using namespace std;

int main() {
	int t;
	cin >> t;
	while(t--) {
		long long l, r, n;
		cin >> n >> l >> r;
		cout << ((r - l) * (n / l) >= (n - n / l * l) ? "Yes\n" : "No\n");
	}
}
```

---

