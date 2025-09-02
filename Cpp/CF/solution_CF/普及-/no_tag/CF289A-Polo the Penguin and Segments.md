# Polo the Penguin and Segments

## 题目描述

Little penguin Polo adores integer segments, that is, pairs of integers $ [l; r] $ $ (l<=r) $ .

He has a set that consists of $ n $ integer segments: $ [l_{1}; r_{1}],[l_{2}; r_{2}],...,[l_{n}; r_{n}] $ . We know that no two segments of this set intersect. In one move Polo can either widen any segment of the set 1 unit to the left or 1 unit to the right, that is transform $ [l; r] $ to either segment $ [l-1; r] $ , or to segment $ [l; r+1] $ .

The value of a set of segments that consists of $ n $ segments $ [l_{1}; r_{1}],[l_{2}; r_{2}],...,[l_{n}; r_{n}] $ is the number of integers $ x $ , such that there is integer $ j $ , for which the following inequality holds, $ l_{j}<=x<=r_{j} $ .

Find the minimum number of moves needed to make the value of the set of Polo's segments divisible by $ k $ .

## 样例 #1

### 输入

```
2 3
1 2
3 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 7
1 2
3 3
4 7
```

### 输出

```
0
```

# 题解

## 作者：KaguyaH (赞：2)

我们定义当前的

$$a = \sum_{i = 1}^n(r_i - l_i + 1).$$

考虑每次操作都会使 $a \leftarrow a + 1$，故答案即为 $\min\limits_{d \geqslant a \land k | d}d - a$。

这时考虑 $a \leftarrow a \pm k$ 对答案没有影响，故可以将 $a \leftarrow a \bmod k$，然后答案即为 $(k - a) \bmod k$。

```cpp
# define _CRT_SECURE_NO_WARNINGS
# include <cstdio>

namespace Main {
	namespace Sourse {
		typedef long signed int ld;
		typedef long unsigned int lu;
	}
	using namespace Sourse;
	static lu n, k;
	static lu ans;
	static inline const void main() {
		scanf("%lu%lu", &n, &k);
		for (register lu i(0); i < n; ++i)
		{ static ld l, r; scanf("%ld%ld", &l, &r); ans = (ans + (r - l + 1)) % k; }
		printf("%lu\n", (k - ans) % k);
	}
}

signed int main() { Main::main(); return 0; }
```

---

## 作者：Molina (赞：1)

# 题目大意：
[题目链接](https://www.luogu.com.cn/problem/CF289A)

给你 $ n $ 段区间。对于每一段区间，你可以扩展区间，即将 $ l_i -1 $ 或 $ r_i + 1 $。

求使所有区间包含的整数数量之和被 $ k $ 整除的最少扩展的次数。

# 本题思路：
~~这就是红题难度啊。~~

因为每次扩展区间都是将整数数量之和加一，根本不需要考虑其他情况，直接解就可以了。

输入，在输入时用 $ sum $ 累加一下每个区间的整数数量，即加上 $ r_i - l_i + 1 $。

然后特判，若 $ sum $ 直接能被 $ k $ 整除，证明不需要进行任何操作，输出 $ 0 $ 即可。

然后输出还需要加几个数能使 $ sum $ 能被 $ k $ 整除即可。就是用 $ k $ 减去 $ sum $ 除以 $ k $ 的余数，就结束了。

详细解释请见代码。

# 代码来咯~
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
long long sum=0;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		int l,r;
		cin>>l>>r;
		sum+=r-l+1;//累加每个区间的整数数量
	}
	if(sum%k==0){//特判
		cout<<"0";
		return 0;
	}
	cout<<k-(sum%k);//输出
	return 0;
}
```

---

## 作者：Lydia1010__ (赞：1)

## 本题思路：
这道题其实很简单，我们只需要记录数据组到底有多少个区间，然后去取模 $k$，如果能整除就输出没有，如果有余数就用 $k$ 减去余数即可。
## 本题代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int ans=0,n,k; 
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		int x,y;
		cin>>x>>y;
		ans+=(y-x+1);
	}
	if(ans%k==0) cout<<0;
	else cout<<k-(ans%k);
	return 0;
}

```


---

## 作者：Back_Stuff (赞：1)

## 题目大意

- 给定 $n$ 个闭区间 $[l_i, r_i]$。
- 每次操作你可以将第 $i$ 个区间扩展，即将 $l_i-1$ 或 $r_i+1$。
- 求使所有区间包含的整数数量之和被 $k$ 整除的最小操作次数。

## 思路

我们将所有区间的长度加起来，用 $sum$ 计数，第 $i$ 个区间的长度是 $r_i-l_i+1$。

最后输出一个最小的比 $sum$ 大的能被 $k$ 整除的数与 $sum$ 的差值就行了。

~~说实话我觉得肯定是一道红题。~~

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int N,K,L,R,Sum;
int main(){
    //freopen(".in","r",stdin);//文件操作模板
    //freopen(".out","w",stdout);
    cin>>N>>K;
    while(N--){
        scanf("%d%d",&L,&R);//头端点和尾端点
        Sum+=(R-L+1);//将每个区间的长度求和
    }
    int Num=(Sum+K-1)/K*K;
    //这里Num是最小的比sum大的能被k整除的数
    cout<<Num-Sum;//输出差值
    //fclose(stdin);
    //fclose(stdout);
    return 0;
}
```


---

## 作者：Terry2011 (赞：0)

# 题目分析

本题给定 $n$ 个不重叠的区间，求区间长度总和再加几能被 $k$ 整除，所以，我们要先算出 $l$ 到 $r$ 的距离，即 $r-l+1$，然后进行特判：如果它就是 $k$ 的倍数，输出 $0$ 即可，否则输出 $k$ 与 $n$ 除以 $k$ 的余数的差。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,l,r,cnt,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>l>>r;
		cnt+=r-l+1;
	}
	if(cnt%k==0) cout<<0;
	else cout<<k-cnt%k;
	return 0;
}
```

---

## 作者：01Dragon (赞：0)

### 题意简化
给定 $n$ 个不重叠的区间，求区间长度总和再加几能被 $k$ 整除。
### 思路
直接按照题目模拟。$l$ 到 $r$ 的区间长度为 $r-l+1$，再记录下长度，就得到了长度总和。

如果长度总和能被 $k$ 整除，就直接输出 $0$，否则就输出 $k$ 与 $n$ 除以 $k$ 的余数的差。
### 代码
```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
int n,l,r,ans,k;//ans为长度总和
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>l>>r;
		ans+=r-l+1;//计算长度总和
	}
	if(ans%k==0)//如果能整除
	{
		cout<<0;
	}
	else
	{
		cout<<k-ans%k;
	}
	return 0;
}
```


---

## 作者：flysfy_LJX (赞：0)

这道题其实就是红题难度，我们可以在输入区间时累加区间的和，再输出还需要扩展几次区间能使能区间和被 $k$ 整除即可。

如果直接能被 $k$ 整除，不需要进行任何操作，在输出时再模上 $k$ 就行了。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,k,sum=0;
	cin >> n >> k;
	for(int i=1;i<=n;i++)
	{
		int x,y;
		cin >> x >> y;
		sum+=y-x+1;
	}
	cout << (k-(sum%k))%k;
	return 0;
}
```


---

## 作者：cyz_czy (赞：0)

# CF289A题解

> ~~几句闲话~~

我是 CYZ，这期带你看题解。

## 题目大意

- 给定 $n$ 个闭区间 $[l_i, r_i]$；
- 每次操作你可以将任意一个区间 $[l, r]$ 扩展，即变为 $[l - 1, r]$ 或 $[l, r + 1]$；
- 求使所有区间包含的整数数量之和被 $k$ 整除的最小操作次数。

## 题目分析

定义一个 $s$，将每一段的区间长度累加起来。对于总长度能够整除 $k$，我们需要找到第一个大于 $s$ 的 $k$ 倍的数，可以通过一层暴力。

但是循环容易不简洁，所以我们可以将 $k$ 减去 $s \bmod k$，我们就得到了第一个大于 $s$ 的 $k$ 倍的数。然而当 $s$ 本来就是 $k$ 的倍数时，我们得到的是 $k$，所以我们需要把这个数 $\bmod k$。

## Code:

```cpp
#include <iostream>

int n,m;

int main(){
	scanf("%d%d",&n,&m);
	
	int l,r;
	int s=0;
	
	while(n--){
		scanf("%d%d",&l,&r);
		
		s+=r-l+1; //区间长度是r-l+1
	}
	
	printf("%d",(m-s%m)%m);
	
	return 0;
} 
```

[AC 记录](https://www.luogu.com.cn/record/111071215)

---

## 作者：ztxtjz (赞：0)

## 【题意】
给你$n$段区间，这$n$段区间互不相交。你只能向左扩展左端点，或者向右扩展右端点，求最少扩展的步数让区间覆盖总长度能够整除$k$。
## 【思路】
设$ans$为$n$段区间总长度，每次输入一段区间的左端点$l$和右端点$r$，则这段区间的长度$di$为$r-l+1$，$ans=\sum\limits_{i=1}^ndi$。

要使区间的总长度能够整除$k$，需要找到$k$的倍数中第一个大于等于$ans$的数，可以通过暴力来寻找。

为了做到更简便，可以反向思考。$ans\bmod k$可以直接得到$ans$减去$k$的倍数的最小非负值，即为$k-ans\bmod k$。当$ans$可以整除$k$时，这一步得到的值仍为$k$，所以还要再一次对$k$进行取余。
## 【代码】
```cpp
#include <cstdio>
int n,k,ans;
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1,l,r;i<=n;i++) scanf("%d%d",&l,&r),ans+=r-l+1;
	printf("%d",(k-ans%k)%k);
	return 0;
}
```

---

## 作者：Swiftie_wyc22 (赞：0)

这道题绝对是红题。

我们可以先统计所有线段的长度之和 $sum$，每一条线段的长度和是 $r-l+1$。

于是我们可以想一下两个扩展操作的规律：

将 $r+1$ 或者将 $l-1$，我们可以发现，都会使得这条线段的长度 $+1$。

所以我们就找最小的 $x$，使得 $k | sum+x$，这个 $x$ 也正好就是操作数。

于是我们可以~~优雅地~~写出一个暴力代码，由于本题数据略水，于是下面的程序是可以AC的。

```cpp
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int ans = 0;
    int n, k, l, r;
    cin >> n >> k;
    for (int i = 0; i < n; i++)
    {
        cin >> l >> r;
        ans += r - l + 1;
    }
    int x = 0;
    while ((ans + x) % k != 0)
        x++;
    cout << x << endl;
    return 0;
}
```

不过我们可以改进一下。

我们只道最小值就是把 $sum\mod k$ 补上，额好像不能更清楚了

就是：

```cpp
(ans - ans % k) % k // 最外面的%k是为了保险
```

---

