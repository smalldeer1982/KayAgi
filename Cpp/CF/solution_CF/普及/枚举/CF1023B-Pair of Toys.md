# Pair of Toys

## 题目描述

Tanechka is shopping in the toy shop. There are exactly $ n $ toys in the shop for sale, the cost of the $ i $ -th toy is $ i $ burles. She wants to choose two toys in such a way that their total cost is $ k $ burles. How many ways to do that does she have?

Each toy appears in the shop exactly once. Pairs $ (a, b) $ and $ (b, a) $ are considered equal. Pairs $ (a, b) $ , where $ a=b $ , are not allowed.

## 说明/提示

In the first example Tanechka can choose the pair of toys ( $ 1, 4 $ ) or the pair of toys ( $ 2, 3 $ ).

In the second example Tanechka can choose only the pair of toys ( $ 7, 8 $ ).

In the third example choosing any pair of toys will lead to the total cost less than $ 20 $ . So the answer is 0.

In the fourth example she can choose the following pairs: $ (1, 1000000000000) $ , $ (2, 999999999999) $ , $ (3, 999999999998) $ , ..., $ (500000000000, 500000000001) $ . The number of such pairs is exactly $ 500000000000 $ .

## 样例 #1

### 输入

```
8 5
```

### 输出

```
2
```

## 样例 #2

### 输入

```
8 15
```

### 输出

```
1
```

## 样例 #3

### 输入

```
7 20
```

### 输出

```
0
```

## 样例 #4

### 输入

```
1000000000000 1000000000001
```

### 输出

```
500000000000
```

# 题解

## 作者：naroto2022 (赞：2)

# CF1023B题解

### 题意
题目的意思浅显易懂：就是有 $n$ 个物品，第 $i$ 件物品价值为 $i$，问只取其中两个物品，价值能打到 $k$ 的方案数有几个。
### 思路
首先先看数据范围，$1\le n,k\le 10^{14}$，本蒟蒻的暴力梦破裂了，只好用用小学学的数学。

我们知道：若 $x+y=z$，则 $(x-s)+(y+s)=z$（$s$ 可以为任意实数，而本题视为非负整数）。

于是：

1. 若 $k\equiv0\pmod 2$，则答案就为 $\min(k\div2-1,n-k\div2)$。
2. 若 $k\equiv1\pmod 1$，则答案就为 $\min(k\div2,n-k\div2)$。
3. 若 $2\times n-1<k$，则无解，输出 $0$。

下面就来解释一下上面的分类讨论：

1. 为啥要用 $\min$ 函数？

答：因为 $k$ 可能是奇数，我们取了中间的两个数，一共有 $1\sim k\div2-1$ 配 $k\div2\sim k$，要选出可以配对的数量就是两组数中小的那一组的数量。

2. 为啥若 $2\times n-1<k$，就无解呢？

答：因为每件物品是唯一的，也就是说只能取一次。所以最大的价值就是 $2\times n-1$，要是 $k$ 比这个价值还要大的话，绝对无解。

### 总结
1. 要开 long long，不开 long long 见祖宗。
2. 要特判。
3. 要一点点的小学数学基础。
4. 需要取小（$\min$ 函数）。
### 代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
long long n,k;
int main(){
	scanf("%lld %lld",&n,&k);
	if(2*n-1<k) printf("0");//无解的情况
	//为啥无解呢？
	//因为每件物品是唯一的，也就是说只能取一次。
	//所以最大的价值就是2*n-1，要是k比这个价值还要大的话，绝对无解。
	else if(k%2==0) printf("%lld",min(k/2-1,n-k/2));
	//一定要取小的！
	//因为k可能是奇数，我们取了中间的两个数，一共有1~k/2-1配k/2~k，要选出可以配对的数量就是两组数中小的那一组的数量。
	else printf("%lld",min(k/2,n-k/2));
	//与上面同理。
	return 0;
} 
```

---

## 作者：sto__Liyhzh__orz (赞：2)

### [传送门：](https://www.luogu.com.cn/problem/CF1023B)

思路：分类讨论。

* 我取最多最多都达不到 $k$，即 $2 \times n-1 < k$ 的情况，输出 $0$。

* 在 $n \ge k-1$ 的情况下，怎么拆都行，也就是能从 $1$ 一直拆到 $\lfloor \frac{k}{2}\rfloor$，但是，若 $k \equiv 0 \pmod 2$ 时，会出现（$k/2$，$k/2$）的情况，应再减去一。
  
  所以公式为 $\begin{cases} \lfloor \frac{k}{2}\rfloor & k \equiv 1 \pmod 2 \\ \lfloor \frac{k}{2}\rfloor-1 & k \equiv 0 \pmod 2 \end{cases}$
  
* 剩下的情况就非常简单了，$(2 \times n - k + 1)/  2$。

注意！不开 `long long` 见祖宗！

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

#define LL long long

LL n,k; 

int main()
{
    ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	if(n+n-1<k) cout<<0<<endl;
	else if(n>=k-1) cout<<k/2-(k%2?0:1)<<endl;
	else cout<<(2*n-k+1)/2<<endl;
    return 0;
}

```

---

## 作者：Fraction (赞：2)

~~这么好的题，怎么能没有题解？~~

本人表示codeforces当场A炸穿之后3minA了这题qwq

听群里的dalao说这题是解不等式组

然而其实这题只需要分三种情况：

1.$2*n-1 < k$ 这种情况下无解，输出0

2.$1+n≥k$ 我们就使$l=1,r=k-1$，让$l+r$正好等于$k$

3.$1+n≤k$且$2*n-1≥k$ 我们可以让$l=k-n,r=n$

最后答案就是$(r-l+1)/2$

为什么可以得到这样的结论呢？

我们看，假设有$(a,b)$一对数使得$a+b=k$那么$(a-1,b+1),(a+1,b-1)$也会等于k

以此类推，既然$a\neq b$且$(a,b)$与$(b,a)$是同一组解

那么总数应该是$(r-l+1)/2$

这应该是小学的一个什么原理

好了，贴代码：

```cpp
#include <bits/stdc++.h>
#define fp(i, l, r) for(register int i = (l); i <= (r); ++i)
#define fd(i, l, r) for(register int i = (l); i >= (r); --i)
#define ANTISYNC ios::sync_with_stdio(false)
#define full(a, b) memset(a, b, sizeof(a))
#define MAXN (int)1e5 + 5
#define lowbit(x) x & -x
#define ll long long
#define il inline
using namespace std;

ll n, k, l, r;

il int init() {
    cin >> n >> k;
    if(2 * n - 1 < k) {
        printf("0");
        return 0;
    }
    if(1 + n >= k) l = 1, r = k-1;
    else l = k - n, r = n;
    cout << (r-l+1)/2 ;
    return 0;
}

int main() {
    init();
    return 0;
}
```

---

## 作者：MorsLin (赞：1)

### 题目大意

输入两个数$n,k$，问从$1$~$n$中取出$2$个数使得它们的和为$k$的方案数（$(a,b)$和$(b,a)$算同一种方案）

### 题解

如果$a+b==k$，那么$(a+1)+(b-1),(a+2)+(b+2)$……也等于$k$。所以我们可以找到最接近的两个数$k/2,k/2+1$，然后$1$~$k/2$和$(k/2+1)$~$(k{-}1)$就是所有的方案。接下来我们只需要找出合法的方案数就可以了

首先我们可以确定如果$k/2{>=}n$，肯定无解，当$k/2{<}n$的时候，因为$n$可能小于$k$，所以合法的方案数应为$\min(k/2,(k-1)-k/2,n-k/2)$

P.S. 不要忘了开$long\; long$

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int main(){
	long long n,k; cin>>n>>k;
	long long mid=k/2,ans;
	if(mid<n) ans=min(mid,min(k-1-mid,n-mid));
	else{
		cout<<0; return 0;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：2012zxt (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1023B)

# 1.思路

### 遇事不决，小学数学！！！

没错，这道题就是一道小学数学题。

我们可以想到，第一个玩具每一种取值都只能匹配一个第二种玩具，所以我们可以分别算第一个和第二个玩具的取值范围并取较小值。

而它说了，这是一种组合的选择，所以如果我们设定第一个玩具是较小的，那它只能取 $1 \sim \frac{k}{2}$。

但这里有一个问题，因为每一种玩具**只有一个**，所以如果第一个和第二个的玩具一样，那第一个就得减 $1$，第二个就得加 $1$。

所以这道题得代码就可以写了。

# 2.代码

```cpp
#include<bits/stdc++.h>
#define int long long//十年OI一场空，不开long long见祖宗
using namespace std;
int n,k;
signed main(){
	cin>>n>>k;
	if(k>2*n-1){//最大的和第二大的都没有k，绝杀，无解！
		cout<<0;
		return 0;
	}
	int tmp=k/2;//第一个玩具的最大值
	if(k%2==0)//如上特判
		tmp--;
	int ans=min(tmp,max(0ll,n-(k-tmp)+1/*第二个玩具得取值范围，至少有1个，要加1*/));
	cout<<ans;
	return 0;
}
```

---

## 作者：qiuzijin2026 (赞：0)

# Pair of Toys

## [题面](https://www.luogu.com.cn/problem/CF1023B)

## 思路

这道题如果使用模拟的话，$10^{14}$ 的数据一定会TLE，所以考虑数学。

如果 $a+b=k$ 那么 $(a-x)+(b+x)=k $ 和 $(a+x)+(b-x)=k $ 一定成立。

于是我们就分情况讨论：

- 如果 $k\bmod 2$ 余 $1$，那么答案就是 $\min((k-1)\div 2,n-(k-1)\div 2)$。

- 如果 $k\bmod 2$ 余 $0$，那么答案就是 $\min((k-1)\div 2-1,n-(k-1)\div 2)$。

无解的情况就是 $n\times 2-1<k$，输出 $0$ 即可。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,k;
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	scanf("%lld%lld",&n,&k);
	if(2*n-1<k){
		printf("0"); 	
		return 0;
	} 
	if(k%2==0){
		printf("%lld",min(k/2-1,n-k/2));	
	}
	else{
		printf("%lld",min(k/2,n-k/2));
	}
	return 0;
}

```

---

## 作者：小闸蟹 (赞：0)

```cpp
// 找规律题
// 通过观察我们可以确定有三种情况
// 1) k太大，导致取数列中最大的两个(n, n - 1)都无法满足
// 2) k比n小，此时决定取法的只有k，因为上界比k大，无法够得着
// 3) k比n大但不会太大，此时决定取法的是k和n，列方程解出下界即可
#include <iostream>

using ll = long long;

int main()
{
    ll n, k;
    std::cin >> n >> k;
    if (n * 2 <= k) // k太大
    {
        std::cout << 0 << std::endl;
    }
    else if (k <= n)    // k比n小
    {
        std::cout << (k - 1) / 2 << std::endl;
    }
    else    // k比n大但不会太大
    {
        std::cout << (n * 2 + 1 - k) / 2 << std::endl;
    }

    return 0;
}
```

---

## 作者：yfct (赞：0)

一看数据范围就知道枚举是不可能的，看完题干发现是**纯数学题**。简单的整数分拆，根据k的奇偶性讨论即可。注意ans=0的情况要单独讨论。
```c++
//Author:  书海扬帆
//Website: www.ljhedp.cn
#include <iostream>
#include <cstdio>
using namespace std;
long long n,k;
int main()
{
	scanf("%lld%lld",&n,&k);
	if (k&1)
	{
		if (n<=k/2) printf("0");
		else if (n<k) printf("%lld",n-k/2);
		else printf("%lld",k/2);
	}
	else {
		if (n<=k/2) printf("0");
		else if (n<k) printf("%lld",n-k/2);
		else printf("%lld",k/2-1);
	}
	return 0;
}
```

---

