# 「NnOI R1-T1」购物

## 题目描述

小 R 是一个喜欢购物的女孩子，她生活在欧艾国中。

欧艾国共有 $n$ 种面值的硬币，它们的面值分别为 $1=a_1 < a_2 < a_3 < \cdots < a_n$，且满足 $a_{i+1}$ 是 $a_i$ 的倍数。欧艾国只有硬币一种付款方式。

欧艾国的商店不支持找零，她在购物时必须支付与价格完全相等的硬币。对于同样的价格，可以有不同的支付方式。例如，如果欧艾国硬币的面值为 $1$ 元和 $5$ 元，那么支付 $7$ 元有两种方式：支付 $7$ 枚 $1$ 元硬币，或者支付 $1$ 枚 $5$ 元硬币和 $2$ 枚 $1$ 元硬币。

由于硬币的质量大致相同，她不希望携带的硬币太重，因此每次购物都会携带符合要求的尽量少的硬币。她发现了一个神奇的现象：有的时候多买 $1$ 元的商品可以使她少带很多硬币。

你能求出最小的 $m$，使得买 $m$ 元的商品需要的硬币数比买 $m-1$ 元的商品需要的硬币数更少吗？

## 说明/提示

### 样例解释

对于样例 $1$，购买 $1\sim 5$ 元的商品分别需要 $1\sim 5$ 枚 $1$ 元硬币，购买 $6$ 元的商品只需要 $1$ 枚 $6$ 元硬币。

对于样例 $2$，购买 $1$ 元或 $2$ 元的商品都需要 $1$ 枚硬币，并不满足需要的硬币数更少的要求。

### 数据范围

对于 $100\%$ 的数据，$1\le n\le 10$，$1=a_1 < a_2 < a_3 < \cdots < a_n\le 10^9$，且满足 $a_{i+1}$ 是 $a_i$ 的倍数。

**提示：本题开启捆绑测试。**

本题共 $4$ 个子任务。

| 子任务编号 | $ n \le $ | 特殊性质 | 分数 |
|:-:|:-:|:-:|:-:|
| $ 1 $ | $ 2 $ | 无 | 20 |
| $ 2 $ | $ 10 $ | 保证 $a_i\le 10^3$ | 20 |
| $ 3 $ | $ 10 $ | 保证有解 | 30 |
| $ 4 $ | $ 10 $ | 无 | 30 |

### 题目来源

| 项目 | 人员 |
|:-:|:-:|
| idea | rui_er |
| std | rui_er |
| data | rui_er |
| check | Kevin0501 |
| solution | rui_er |

## 样例 #1

### 输入

```
4
1 6 12 48```

### 输出

```
6```

## 样例 #2

### 输入

```
3
1 2 8```

### 输出

```
8```

## 样例 #3

### 输入

```
1
1```

### 输出

```
-1```

# 题解

## 作者：Nightsky_Stars (赞：20)

# 思路：

因为  $a_{i+1}$  是  $a_i$  的倍数，所以很容易就能想到从小到大的第一个比前一个数大一以上的就是答案，假设  $a_1∼a_k$  是公差为  _1_  的等差数列，则  $a_1∼a_{k+1}-1$  的数都只能用相应个数的  _1_  构成，而到了  $a_{k+1}$  就只需要一个  $a_{k+1}$  就可购买。

无解的情况就很显然了，如果一共就一个数或者公差为  _1_  的等差数列，就无解（悲）

# Code:
```
#include<bits/stdc++.h>
using namespace std;
int n,a[15];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		if(a[i]!=a[i-1]+1){
			cout<<a[i]<<endl;
			return 0;
		}
	}
	cout<<-1<<endl;
	return 0;
}
```



---

## 作者：rui_er (赞：10)

出题人题解。

由于 $a_{i+1}$ 是 $a_i$ 的倍数，那么贪心地从大往小取一定最优。

首先，发现无解情况共有两个：$a=\{1\}$ 或 $a=\{1,2\}$。前者购买 $x$ 元的商品需要 $x$ 枚硬币，后者购买 $x$ 元的商品需要 $\lceil\frac{x}{2}\rceil$ 枚硬币，他们都单调不降。

否则，如果 $a_2 > 2$，那么 $m=a_2$。购买 $1\sim a_2-1$ 元的商品分别需要 $1\sim a_2-1$ 枚硬币，而购买 $a_2$ 元的商品只需要 $1$ 枚硬币。显然有 $a_2-1 > 1$。

如果 $a_2=2$，以上的构造就失效了，因为购买 $1$ 元或 $2$ 元的商品都只需要 $1$ 枚硬币，此时 $m=a_3$。购买 $1\sim a_3-1$ 元的商品分别需要 $1\sim\lceil\frac{a_3-1}{2}\rceil$ 枚硬币，而购买 $a_3$ 元的商品只需要 $1$ 枚硬币。其中 $a_3\ge 2a_2=4$，所以 $\lceil\frac{a_3-1}{2}\rceil\ge 2 > 1$。

综上，答案如下：

$$
m=
\begin{cases}
-1,&a=\{1\}\lor a=\{1,2\}\\
a_2,&a_2 > 2\\
a_3,&a_2=2
\end{cases}
$$

```cpp
//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
    uniform_int_distribution<int> dist(L, R);
    return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

const int N = 15;

int n, a[N];

int main() {
    scanf("%d", &n);
    rep(i, 1, n) scanf("%d", &a[i]);
    if(n == 1) puts("-1");
    else if(n == 2 && a[2] == 2) puts("-1");
    else if(a[2] == 2) printf("%d\n", a[3]);
    else printf("%d\n", a[2]);
    return 0;
}
```

---

## 作者：___w (赞：8)

### [P9412 「NnOI R1-T1」购物](https://www.luogu.com.cn/problem/P9412)

#### 题意简述
n 种面值的硬币，它们的面值分别为 $1=a_1 < a_2 < a_3 < \cdots < a_n$，且满足 $a_{i+1}$ 是 $a_i$ 的倍数。求最小的 $m$，使得买 $m$ 元的商品需要的硬币数比买 $m-1$ 元的商品需要的硬币数更少。

#### 题目分析
显然面值从大到小来选最优。因为 $a_{i+1}$ 是 $a_i$ 的倍数，所以 $a_i$ 会比 $a_i-1$ 更优。但 $a_1=1$，所以 $a_2$ 为首选答案。特别地，若 $a_2=2$，$a_i$ 会跟 $a_2-1$ 一样优，所以 $a_3$ 为首选答案。若 $a_2$ 或者 $a_3$ 不存在，即 $n$ 很小，就没有一个 $m$ 比 $m-1$ 更优，所以输出 $-1$。

代码就跟上述结论一样了。

#### 代码
[record](https://www.luogu.com.cn/record/112513841)。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 15;
int n, a[N];
int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	if (n == 1) cout << -1;
	else if (n == 2 && a[2] == 2) cout << -1;
	else if (a[2] == 2) cout << a[3];
	else cout << a[2];
	return 0;
}
```

---

## 作者：lailai0916 (赞：2)

## 原题链接

- [洛谷 P9412 「NnOI R1-T1」购物](https://www.luogu.com.cn/problem/P9412)

## 解题思路

分类讨论：

- 若 $n=1$，显然无解。
- 若 $n=2$，因为题目保证 $a_1=1$，如果 $a_2=2$，支付 $1$ 元和 $2$ 元都需要 $1$ 枚硬币，所以无解。
- 若 $n>2$，如果 $a_2=2$ ，类似第二种情况，答案不能为 $2$，所以答案最小为 $m=a_3$。
- 否则，$a_2$ 一定大于 $2$，所以答案最小为 $m=a_2$。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=15;
int a[N];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	if(n==1)
	{
		cout<<"-1"<<'\n';
	}
	else if(n==2&&a[2]==2)
	{
		cout<<"-1"<<'\n';
	}
	else if(n>2&&a[2]==2)
	{
		cout<<a[3]<<'\n';
	}
	else
	{
		cout<<a[2]<<'\n';
	}
	return 0;
}
```

---

## 作者：Vct14 (赞：1)

设 $P_i$ 表示买 $i$ 元的东西需要 $P_i$ 枚硬币。

我们可以发现，若 $n=1$，必无解。因为只会有面值为 $1$ 的一种硬币，则 $P_i=i$，必有 $P_{i+1}>P_i$。所以不存在 $m$，输出 $-1$。

那么现在有 $n\ge 2$。

当 $a_2=2$ 时，若 $n=2$，则也无解。因为 $P_{2i}=P_{2i-1}=i$（其中 $i$ 为正整数），所以也有 $P_k\ge P_{k-1}$。也不存在 $m$，输出 $-1$。若 $n\ne2$，因为 $a_3$ 最小为 $2\times2=4$，所以必有 $P_{a_3}>P_{a_3-1}$。输出 $a_3$ 即可。

若 $a_2\ne2$，则必有 $P_{a_2}>P_{a_2-1}$。输出 $a_2$ 即可。

```c++
#include<bits/stdc++.h>
using namespace std;

int main(){
	int n,a1,a2,a3;
	cin>>n>>a1;
	if(n==1){
		cout<<"-1";
		return 0; 
	}
	cin>>a2;
	if(a2==2){
	    if(n==2) cout<<"-1";
	    else{
	        cin>>a3;
	        cout<<a3;
	    }
	}
	else cout<<a2;
	return 0;
}
```

---

## 作者：ljk8886 (赞：1)

## 题目大意
构造一个数 $m$。$m - 1$ 元的商品所用的硬币数少。如无解，输出 $-1$。

## 题目分析
观察题目，可以发现，$m$ 只能是 $a_{i}$，但如果只有一种面值的硬币或所有面值都只比上一种面值大一元，那么无解。

## 代码

```cpp
#include<iostream>
using namespace std;
const int N=15;
int a[N];
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=2;i<=n;i++)
    {
        if(a[i]-a[i-1]!=1)//差不为1时，就输出。
        {
            cout<<a[i]<<endl;
            return 0;
        }
    }
    cout<<-1<<endl;//无解，输出-1。
    return 0;
}

---

## 作者：TheCliffSwallow (赞：1)

### 思路
因为每个数都是前面那个数的倍数而第一个数又是一，那么就很容易就能想到从小到大的第一个比前一个数大一以上的就是答案，假设 $a_1\sim a_k$ 为公差为 $1$ 的等差数列，则显然从 $a_1\sim a_{k+1}-1$ 的数都只能用相应个数的 $1$ 构成，而到了 $a_{k+1}$ 就只需要一个 $a_{k+1}$ 就可购买。

而无解的情况此时就很显然了，如果一共就一个数或者是一个公差为 $1$ 的等差数列，就无解。

### CODE
```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#include<vector>
#define ll long long
#define ull unsigned long long
using namespace std;
int n,a[15];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		if(a[i]!=a[i-1]+1){
			cout<<a[i]<<endl;
			return 0;
		}
	}
	cout<<-1<<endl;
	return 0;
}
```


---

## 作者：Convergent_Series (赞：1)

比赛的时候没看到 $a_{i+1}$ 是 $a_i$ 的倍数，但是发现也可以做，所以就讲一下无倍数关系时的做法。

令 $k$ 为最大的满足 $a_i=i\ (1\le i\le k)$ 的数，则钱数 $\le k$ 时需要一个硬币，钱数为 $x\ (k+1\le x\le a_{k+1}-1)$ 时均可以用 $\lfloor\dfrac{x}{k}\rfloor$ 个 $k$ 元硬币和一个或零个其它硬币付钱，容易发现硬币数单调不减且 $>1$，且钱数为 $a_{k+1}$ 时只需 $1$ 个硬币，答案即为 $a_{k+1}$。

若 $k=n$ ，则 $a_{k+1}$ 不存在（可看做无穷大），此时硬币数单调不减，无解。

参考代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){
	int a=0,f=1;char ch;ch=getchar();
	while(!((ch>='0'&&ch<='9')||ch=='-')) ch=getchar();
	if(ch=='-') f=-1,ch=getchar();
	while(ch>='0'&&ch<='9') a=(a<<3)+(a<<1)+(ch^'0'),ch=getchar();
	a*=f;return a;
} 
void write(int a){
	if(a<0){putchar('-'),a=-a;}
	if(a>9) write(a/10); 
	putchar(a%10+'0');
}
int n,a;
signed main(){
	n=read();
	for(int i=1;i<=n;i++){
		a=read();
		if(a!=i){
			write(a);return 0;
		}
	}
	write(-1);
    return 0;
}
```

---

## 作者：mark0575 (赞：0)

## 思路：
我们可以先找几个数模拟一下。假设我们要组成 $5$ 元，有 $1$ 元和 $5$ 元的硬币，可以直接拿 $1$ 枚五元硬币；假设还要组成 $5$ 元，有 $1$ 元 和 $2$ 元两种面额，最少要拿 $1$ 枚 $1$ 元硬币和 $2$ 枚 $2$ 元硬币。通过这个例子，我们可以发现，当所要组成的面额有这种面额的硬币时，会比没有这种面额要少拿硬币。如果有 $m$ 这种面额的硬币，没有 $m-1$ 这种面额的硬币，这个 $m$ 就是我们要的答案。但是，如果 $a_n=n$，说明相邻数的一定只相差 $1$。不能够满足上面的条件。因此输出 $-1$。

## AC code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[10101];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	if(a[n]==n)
	{
		cout<<"-1";
		return 0;
	}
	for(int i=2;i<=n;i++)
	{
		if(a[i]!=a[i-1]+1)
		{
			cout<<a[i];
			return 0;
		}
	}
	return 0;
 } 
```



---

## 作者：Lemonlwl (赞：0)

## P9412 「NnOI R1-T1」购物 题解
### 题意：
给出 $n$ 种不同面值的硬币，求出符合条件的 $m$ 使得购买 $m$ 元东西的硬币数量比购买 $m-1$ 元东西的硬币少。

------------

### 分析：
如果要使贵的东西使用的硬币比它少一元的东西使用的硬币数量少，则只能是有与该金额相同面值的硬币，并且没有比他少一元面值的硬币。

------------

### 思路：
1. 当 $n=1$ 时显然无解。

1. 因为题目已经明确告诉我们 $a_1=1$，所以根据分析中 ```并且没有比他少一元面值的硬币``` 可知，当 $n=2$ 并且 $a_2=2$ 时也无解。

1. 当 $n>2$ 并且 $a_2=2$ 时，则当 $m=a_3$ 时，答案符合条件且最小。

1. 其他情况时 $m=a_2$ 符合条件且最小。

------------

附上 [AC](https://www.luogu.com.cn/record/112575374) 代码：

```cpp
#include<iostream>
using namespace std;
int a[15];
int main(){
	int n;
	cin>>n;  //输入。
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	if(n==1 || (n==2 && a[2]==2)){  //第1、2种情况。
		cout<<-1<<endl;
	}
	else if(a[2]==2){   //第3种情况。
		cout<<a[3]<<endl;
	}
	else{   //第4种情况。
		cout<<a[2]<<endl;
	}
	return 0;
}
```


---

## 作者：Lemon_zqp (赞：0)

### 思路
在考场上推出了如下结论：
$$
m=
\begin{cases}
-1,&a=\{1\}\lor a=\{1,2\}\\
a_2,&a_2 > 2\\
a_3,&a_2=2
\end{cases}
$$

证明：发现无解情况共有两个：$a=\{1\}$ 或 $a=\{1,2\}$。前面购买 $x$ 元的商品需要 $x$ 枚硬币，后面购买 $x$ 元的商品需要 $\frac{x}{2}$ 向上取整枚硬币。

否则，如果 $a_2 > 2$，那么 $m=a_2$。

### 代码
```
#include<bits/stdc++.h>
using namespace std;

int a[1000005];

int main()
{
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) 
	{
		cin >> a[i];
	}
    if(n == 1 || (n == 2 && a[2] == 2))
	{
    	cout << -1;
	}
    else if(a[2] > 2) 
	{
		cout << a[2];
	}
    else
	{
		cout << a[3];
	}
    return 0;
}


```


---

## 作者：XBaiC (赞：0)

### 思路

无解情况共有两个：$a=\{1\}$ 或 $a=\{1,2\}$。开始购买 $x$ 元的商品需要 $x$ 枚硬币，后面购买 $x$ 元的商品需要 $\left [  \frac{x}{2} \right ] $ 枚硬币。如果 $a_2 > 2$，则 $m=a_2$。

得到以下结论：

$$m=
\begin{cases}
-1,&amp;a=\{1\}\lor a=\{1,2\}\\
a_2,&amp;a_2 >2\\
a_3,&amp;a_2=2
\end{cases}$$

### CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[11];
int main() 
{
    int n;
	cin >> n;
	for( int i = 1; i <= n; i++ )
	{
	    cin >> a[i];
	}
	if( n == 1 || ( n == 2 && a[2] == 2 ) ) 
	{
	    cout << "-1";
	    return 0;
	}
	else if( a[2] == 2 ) 
	{
	    cout << a[3];
	    return 0;
	}
	cout << a[2];
	return 0;
}

```


---

## 作者：smydahaoren (赞：0)

P9412 「NnOI R1-T1」购物 
------------

[原题 P9412 「NnOI R1-T1」购物 传送门](https://www.luogu.com.cn/problem/P9412)

**题目分析**：

------------
题目中给出欧艾国硬币面值数量 $n$ 和面值。（注：它们的面值为 $1=a_1<a_2<a_3<\cdots<a_i$ 且满足 $a_{i+1}$ 是 $a_i$ 的倍数）

求出最小的 $m$，使得买 $m$ 元的商品需要的硬币数比买 $m-1$ 元的商品需要的硬币数更少。

**思路分析**：

------------

1. 当 $n=1$ 时，只有面值为 $1$ 的硬币，显然无解，输出 $-1$。

1. 当 $n=2$ 时，如果 $a_2$ 的面值为 $2$，那么购买商品需要 $\lceil\frac{m}{2}\rceil$ 个硬币，无解，输出 $-1$。

所以当 $a=\{1\}$ 或者 $a=\{1,2\}$ 时，无解。

同时得出 $a_2\ge2$。

1. 当 $a_2=2$ 时，且 $n\ge3$，那么 $m=a_3$。

1. 当 $a_2>2$ 时，$m=a_2$。

**AC代码**：

------------

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2000009;
int n,a[N],m;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	if(n==1) {
		cout<<-1<<endl;return 0; //n=1的情况 ，无解 
	}
	if(n==2&&a[2]==2){
		cout<<-1<<endl;return 0; //n=2，a2=2的情况，无解 
	}
	if(a[2]==2){
		cout<<a[3]<<endl;return 0;//n>2，但是a2=2的情况，答案为a3 
	}
	cout<<a[2]<<endl;//最后一种情况，答案为a2 
	return 0;
}
```


---

## 作者：Kobe_BeanBryant (赞：0)

### 题目大意：
给你一个长度为 $ n $ 的数组，代表有 $ n $ 个不同面值的硬币。且 $ a_1 < a_2 < a_3 < \cdots < a_n $。

求：能让硬币数量尽量最小的最小值 $ m $，且 $ m-1 $ 的硬币总数大于 $ m $ 的硬币总数。

### 条件：
1. 让答案 $ m $ 的硬币数量尽量小。
2. $ m-1 $ 的硬币总数比 $ m $ 硬币总数大。
3. 答案为满足条件一与条件二的最小值。
4. 若没有答案，输出 $ -1 $。

### 大体思路：
1. 首先我们看到条件一时，就应该想到硬币数量最小的数量为 $ 1 $ 枚，也就是如果当你有面值为 $ 1 $ 元和 $ 5 $ 元，那么只满足条件一的 $ m $ 就可以为 $ 1 $ 或 $ 5 $。即，只满足条件一的 $ m $ 就可以为 $ a_i $。
2. 理清条件一后，我们再将条件二加入其中。条件二为：$ m-1 $ 的硬币总数比 $ m $ 硬币总数大。我们将从条件一寻找到的普遍规律加上条件二得：$ m $ 为 $ a_i $，且 $ a_i -1 $ 不能为给出面值中的其一。
3. 求最小，而且题目已经说了 $ a_1 < a_2 < a_3 < \cdots < a_n $，那么我们就可以直接从头到尾的将每一个面值查找一边，看是否满足题目给出的条件。

注意：$ m $ **永远不可能为 $ 1 $**，因为当 $ m $ 为 $ 1 $ 后，$ m-1 $ 就为 $ 0 $，而其不能为 $ 0 $。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m;
long long a[15];
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		if(a[i]!=1 && a[i]-1!=a[i-1]){
			cout<<a[i];
			return 0;
		}
	}
	cout<<-1;
	return 0;
}

```

---

