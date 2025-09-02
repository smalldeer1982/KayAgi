# Nastia and a Good Array

## 题目描述

Nastia has received an array of $ n $ positive integers as a gift.

She calls such an array $ a $ good that for all $ i $ ( $ 2 \le i \le n $ ) takes place $ gcd(a_{i - 1}, a_{i}) = 1 $ , where $ gcd(u, v) $ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ u $ and $ v $ .

You can perform the operation: select two different indices $ i, j $ ( $ 1 \le i, j \le n $ , $ i \neq j $ ) and two integers $ x, y $ ( $ 1 \le x, y \le 2 \cdot 10^9 $ ) so that $ \min{(a_i, a_j)} = \min{(x, y)} $ . Then change $ a_i $ to $ x $ and $ a_j $ to $ y $ .

The girl asks you to make the array good using at most $ n $ operations.

It can be proven that this is always possible.

## 说明/提示

Consider the first test case.

Initially $ a = [9, 6, 3, 11, 15] $ .

In the first operation replace $ a_1 $ with $ 11 $ and $ a_5 $ with $ 9 $ . It's valid, because $ \min{(a_1, a_5)} = \min{(11, 9)} = 9 $ .

After this $ a = [11, 6, 3, 11, 9] $ .

In the second operation replace $ a_2 $ with $ 7 $ and $ a_5 $ with $ 6 $ . It's valid, because $ \min{(a_2, a_5)} = \min{(7, 6)} = 6 $ .

After this $ a = [11, 7, 3, 11, 6] $ — a good array.

In the second test case, the initial array is already good.

## 样例 #1

### 输入

```
2
5
9 6 3 11 15
3
7 5 13```

### 输出

```
2
1 5 11 9
2 5 7 6
0```

# 题解

## 作者：_VEGETABLE_OIer_xlc (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/CF1521B)

我们将利用一个神奇的性质：**相邻的两个自然数一定互质。**

所谓互质是什么，其实就是两个数的最大公因数为 $1$，用公式表现就是 $\gcd(x,y)=1$。

输入这个序列，定义一个变量 $minn$ 来统计最小值，再用一个变量 $pos$ 记录最小值所在的下标。然后输出 $pos$，$i$，$minn$，$minn+|(i-pos)|$。

总而言之，输出格式就是最小数的下标，当前数的下标，最小数，最小数加上当前数下标减最小数下标的绝对值。就会有：

当 $1 \le i \le pos-1$ 时，$a_i=a_{i+1}+1$。

当 $pos+1 \le i \le n$ 时，$a_i=a_{i-1}+1$。

这个序列就可以满足要求！

好了，废话不多说，上代码！！！

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[100010];
int main(){
	cin>>t;
	while(t--)
	{
		int pos=-1,minn=1e9+7;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			if(a[i]<minn)
			{
				minn=a[i];
				pos=i;
			}
		}
		cout<<n-1<<endl;
		for(int i=1;i<=n;i++)
		{
			if(i==pos)continue;
			cout<<pos<<" "<<i<<" "<<minn<<" "<<minn+abs(i-pos)<<endl;
		}
	}
	return 0;
} 
```


---

## 作者：qinyihao (赞：3)

我们将利用这样一个事实：对于任何整数 $i \leq 1$ , 总有 $\gcd (i, i + 1)= 1$ 。

让我们找到数组 `a` 中位于 `pos` 位置的最小元素 `x` 。然后对所有整数 $i$ ( $1 \leq i \leq n$ ) 进行如下操作: $(pos, i, x, x + abs(pos - i))$。这就是我们如何将 $a_i$ 替换为 $x+ abs(pos - i)$ 的方法。主要条件 $\min(a_i, a_j) = \min(x, y)$ 得以满足，因为 $a_{pos}$ 总是等于 $x$ ，这个值总是小于数组`a`中任何其他元素。

考虑一下执行上述操作后的数组`a`的结构。

让我们定义 $l = x + pos - i$ , $r = x + i - pos$。它们分别是数组`a`中最左边和最右边的元素。

数组 `a` 与 `[l, l - 1 ... x - 1, x, x + 1 ... r - 1, r]` 相类似。因此，我们得到了所有相邻元素对之间的绝对差值，等于 $1$。

code
```cpp
#include "bits/stdc++.h"

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int q;
    cin >> q;

    while (q--) {
        int n; cin >> n;
        int x = 1e9 + 7, pos = -1;
        for (int i = 0; i < n; ++i) {
            int a; cin >> a;
            if (a < x) x = a, pos = i;
        }
        cout << n - 1 << endl;
        for (int i = 0; i < n; ++i) {
            if (i == pos) continue;
            cout << pos + 1 << ' ' << i + 1 << ' ' << x << ' ' << x + abs(i - pos) << "\n";
        }
    }
}
```

---

## 作者：LinkZelda (赞：3)

- **题意**：给定一个长度为 $n$ 的序列 $a$，每次操作可以选择四个数 $i$，$j$，$x$，$y$ 满足 $i\neq j,\min(a_i,a_j)=\min(x,y)$，然后将 $a_i$ 改为 $x$，$a_j$ 改为 $y$。你需要在 $n$ 次操作内使得该序列满足**任意相邻的两个数互质**，并输出操作序列。

- **Solution**:

没有限制操作次数最小化，那么我们可以考虑简单点的方法。首先可以发现数据范围保证了 $a_i\leq10^9$ 但是 $x,y\leq 2\times 10^9$。那么我们只需要将每个位置尽量改为大于 $10^9$ 但小于 $2\times 10^9$ 的大质数即可。因为任意两个不相等的数，较大数为质数则两数必然互质。

具体地，我们可以先扫描一次序列，找到整个序列的最小值并记录这个数的位置。然后将其他 $n-1$ 个位置修改，最小值位置还是放最小值，修改那个位置放大质数。

其实我们只需要选两个大质数保证相邻的两数不等即可，那么我们可以选 $10^9+7$ 和 $10^9+9$。具体实现可以看一下我的代码，这样做的时间复杂度为 $O(n)$。

- [代码](https://www.luogu.com.cn/paste/4bw2kz8o)

---

## 作者：我梦见一片焦土 (赞：1)

# [题目传送门](https://www.luogu.com.cn/problem/CF1521B)

---

# 题意：

给一个数组，想要让这个数组满足 $a_i−1$ 和 $a_i$ 的最小公因数为 $1$，你可以进行 $n$ 次操作，如果满足 $\min(a_i,a_j)=\min(x,y)$，则将 $x$ 赋给 $a_i$，将 $y$ 赋给 $a_j$。 

---

# 思路：

本题数组中最小的数一定会留下，并且题目没有要求 $n$ 最小，所以我们直接找到最小的数，然后将数组变成向左右两边，每个数都递增加一的序列即可。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
const int INF=0x3f3f3f3f;
int T,n,a[N];
signed main(){
	cin>>T;
	while(T--){
		cin>>n;
		int mi=INF,pm=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(a[i]<mi){
				mi=a[i];
				pm=i;
			}
		}
		int v=mi;
		cout<<n-1<<endl;
		for(int i=pm+1;i<=n; i++) {
			cout<<pm<<" "<<i<<" "<<mi<<" "<<++v<<endl;
		}
		v=mi;
		for(int i=pm-1;i>=1;i--){
			cout<<pm<<" "<<i<<" "<<mi<<" "<<++v<<endl;
		}
	}
    return 0;
}
```

完结撒花~

---

## 作者：houpingze (赞：1)

这里给一种~~很容易想到~~的构造方法（

首先，$a_i\leq10^9$，我们找一个大于$10^9$的**质数**:$10^9+7$。

由于修改后的$a_i\leq2*10^9$，所以我们可以填写$10^9+7$这个大质数。

至于为什么要填大质数？因为一个质数$x$，和一个正整数$y$，如果$x < y$，则显然满足一个式子就是$\gcd(x,y)=1$~~这不是废话吗~~，由于初始的$a_i\leq2*10^9$，$10^9<10^9+7$，所以是满足题意的。



所以，我们可以填$\left\lfloor\dfrac{n}{2}\right\rfloor$次，每次填写$a_i$和$a_{i+1}$，第一个参数$x$直接输出$\min(a_i,a_{i+1})$，第二个参数就输出$10^9+7$（$i$从$1$到$n$，每次加$2$）。

然后就没有然后了。

---

## 作者：feicheng (赞：1)

UPD：修复了 latex

## [$\textbf{Description}$](https://www.luogu.com.cn/problem/CF1521B)

给定长度为 $n$ 的序列 $a$，你可以进行如下操作：

将 $a_i$ 变为 $x$，$a_j$ 变为 $y$，其中 $x,y$ 需要满足 $\min(x,y)=\min(a_i,a_j)$。

求一种变换方案使得 $\forall i \in [1,n-1] a_i \perp a_{i+1}$。

输出每次变换的 $i,j,x,y$。

## $\textbf{Solution}$

注意到所有不同的质数都是互质的，所以我们只需要找到第一个比 $\min(a_1,a_n)$ 大的质数 $p_1$，第一个比 $\min(a_1,a_2,a_n)$ 大的质数 $p_2$，然后将所有的数按顺序替换成 $p_1,p_2$ 即可。

也就是每次的四元组为 $(i,n,p_{1/2},\min(a_1,a_2,\cdots,a_n))$

由于判断素数可能会判断比较多次，所以用到了 `Miller-Rabin` 素性测试。

## $\textbf{Code}$

```cpp
constexpr int N = 1e5 + 7 ;
constexpr int Test[] = {2,3,5,7,11,13,17};

int n,t;
int a[N] ;

inline int ksm(int x,int y,const int mod) {
    int res = 1;
    for(; y; y >>= 1,x = 1ll*x*x%mod) 
        if(y&1) res = 1ll*x*res%mod;
    return res ;
}

inline bool Judge(const int p) {
    if(p == 2) return 1 ;
    if(p < 2 or !(p&1)) return 0 ;
    int t = p - 1,s = 0;
    while(!(t&1)) ++s,t >>= 1; //分解
    for(auto pri : Test) {
        if(pri == p) return true; 
        if(pri > p) break ; 
        int b = ksm(pri,t,p) ;
        for(int j = 1;j <= s;++j) {
            int k = 1ll*b*b%p;
            if(k == 1 and b != 1 and b != p - 1) return 0 ; 
            b = k ;
        }
        if(b != 1) return 0 ;
    }
    return 1 ; 
}

inline void solve() {
    cin >> n ;
    for(int i = 1; i <= n; ++i)
        cin >> a[i] ;
    if(n == 1) return cout << 0 << '\n',void();
    int v1 = min(a[1],a[n]),v2 = min(a[2],v1) ;
    int p1 = v1+1,p2 = v2+1;
    while(!Judge(p1)) ++p1;
    while(!Judge(p2)) ++p2;
    if(p1 == p2) {
        ++p2;
        while(!Judge(p2)) ++p2 ;
    }
    cout << n - 1 << endl ;
    for(int i = 1;i < n;++i)  {
        cout << i << " " << n << " " ;
        cout << ((i%2) ? p1 : p2) << " " << (a[n] = min(a[n],a[i])) << endl;
    }

}

```

---

## 作者：Meaninglessness (赞：1)

### B. Nastia and a Good Array

**题目大意:**

> 给你一个长度为 $n$ 的初始序列 $a$,你可以执行如下操作:
> 
> 对于依次操作 $[i,j,x,y](1\le i \ne j\le n)$,有  $\min(a_i,a_j)=\min(x,y)$,那么可以将 $a_i$改为 $x$,$a_j$ 改为$y$。
>
> 请在n次操作以内,使得 $\forall 2\le i\le n$,有$\gcd(a_i,a_{i-1})=1$,并打印操作方案。

---

**解题思路:**

我们可以发现,在x是正整数时,很明显有 $\gcd(x,x+1)=1$。

那么我们可以找到这样一种~~神奇的~~构造方法:

找到最小值 $mina$,然后得到 $mina$ 的位置 $pos$ 

然后我们构造数组 $b$

- $b_{pos}=a_{pos}$

- 当$1\le i<pos$ , $b_i=b_{i+1}+1$
- 当$pos<i\le n$ , $b_i=a_{b-1}+1$

当操作为$[i,pos,b_i,b_{pos}]$ ,一定有 $\min(a_i,a_{pos})=\min(b_i,b_{pos})= b_{pos}$

这样构造的 $b$ 数组满足要求。

---

**代码实现:[Code](https://www.luogu.com.cn/paste/b1xm2g4f)　时间复杂度$O(Tn)$**



---

## 作者：__O_w_O__ (赞：0)

### 题意

给你一个数组，要让这个数组满足 $a_{i-1}$ 和 $a_i$ 互质，你可以进行 $n$ 次操作，如果满足 $\min(a_i,a_j)=\min(x,y)$ 则可以将 $x$ 赋值给 $a_i$，将 $y$ 赋值给 $a_j$。

### 思路

这是一道很明显的构造题，看完题目之后很明显的可以想到一种方法：利用相邻两个数一定互质这个定理来解决问题。

在输入的时候求出最小值的位置和下标，构造出来的结果就是每次输出最小值的下标，当前的下标，最小值和当前的下标减去最小值下标的绝对值。

当 $1\le i\le pos-1$ 的时候，$a_i=a_{i+1}+1$。

当 $pos + 1\le i\le n$ 的时候，$a_i=a_{i-1}+1$。

不难看出这样构造的话数组中相邻两个元素一定是相邻的数，满足了互质这一条件。

看到其他题解在求最小值及其下标的时候用的是一个大质数，实际上感觉没有必要，因为在求的时候这个求最小值的变量是一定会改变的（前提是初始值足够大），那么这么做的话直接把这个变量初始化成 $2\times 10^9$ 也是可以通过的。

[通过记录](https://codeforces.com/contest/1521/submission/278187586)

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 100010;
const int INF = (int) 2e9;

int a[N];
int main() {
    int T;
    scanf("%d", &T);
	while(T--) {
        int n;
        scanf("%d", &n);
        int mi = INF, pos = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            if (a[i] < mi) {
                mi = a[i];
                pos = i;
            }
        }
        printf("%d\n", n - 1);
        for (int i = 1; i <= n; i++) {
            if (i == pos) continue;
            printf("%d %d %d %d\n", pos, i, mi, mi + abs(i - pos));
        }
	}
	return 0;
}
```

---

