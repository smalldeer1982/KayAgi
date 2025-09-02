# [ARC158C] All Pair Digit Sums

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc158/tasks/arc158_c

正整数 $ x $ に対し，その各桁の和を $ f(x) $ と表すことにします．例えば $ f(158)\ =\ 1\ +\ 5\ +\ 8\ =\ 14 $，$ f(2023)\ =\ 2\ +\ 0\ +\ 2\ +\ 3\ =\ 7 $，$ f(1)\ =\ 1 $ です．

正整数列 $ A\ =\ (A_1,\ \ldots,\ A_N) $ が与えられます．$ \sum_{i=1}^N\sum_{j=1}^N\ f(A_i\ +\ A_j) $ を求めてください．

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 2\times\ 10^5 $
- $ 1\leq\ A_i\ <\ 10^{15} $
 
### Sample Explanation 1

$ \sum_{i=1}^N\sum_{j=1}^N\ f(A_i\ +\ A_j)\ =\ f(A_1+A_1)+f(A_1+A_2)+f(A_2+A_1)+f(A_2+A_2)=7+9+9+11=36 $ です．

### Sample Explanation 2

$ \sum_{i=1}^N\sum_{j=1}^N\ f(A_i\ +\ A_j)\ =\ f(A_1+A_1)\ =\ 135 $ です．

## 样例 #1

### 输入

```
2
53 28```

### 输出

```
36```

## 样例 #2

### 输入

```
1
999999999999999```

### 输出

```
135```

## 样例 #3

### 输入

```
5
123 456 789 101 112```

### 输出

```
321```

# 题解

## 作者：lzxyl (赞：4)

## **题目描述**

对于正整数 $x$，设 $f(x)$ 表示其位数之和。现给定一个正整数序列 $A=(A_1,…,A_N)$。求 $\sum^{N}_ {i=1}\sum^N_{j=1}f(A_i+A_j)$ 的值。

## **约束**

$1 \le N \le 2 \times 10^5$

$1 \le A_i \le 10^{15}$

**用 $f(x)$ 表示 $x$ 的数字和，用 $g(x,y)$ 表示 $x+y$ 共进位了几次。** 

首先需要一个性质：$f(x+y)=f(x)+f(y)−9 \times g(x,y)$。

对于 $x+y$，假如第 $i$ 位发生进位（第 $i$ 位加完了 大于 $10$），那么第 $i+1$ 位 $+1$，第 $i$ 位 $−10$。所以数字和 $−10+1$，相当于 $−9$。发生多少个进位就相当于减几次 $9$。

这个性质成立后就可以得出：$\sum^{N}_{i=1} \sum^N_{j=1}f(A_i+A_j)=\sum^{N}_{i=1}\sum^N_ {j=1}f(A_i)+f(A_j)-\sum^{N}_{i=1}\sum^N_{j=1}9 \times g(A_i,A_j)$。

所以只需要求出 $\sum^{N}_{i=1} \sum^N_{j=1}f(A_i)+f(A_j)$ 和 $\sum^{N}_{i=1} \sum^N_{j=1}9\times g(A_i,A_j)$ ，再把它们相减就可以了。

首先对于 $\sum^{N}_{i=1} \sum^N_{j=1}f(A_i)+f(A_j)$，这个是很好计算的，只需要在每个数输入的时候进行累加就可以，但注意每个数会出现 $2 \times n$ 次，所以要将 $ans\times 2\times n$。

对于 $\sum^{N}_{i=1}\sum^N_{j=1}9\times g(A_i,A_j)$，这个就有点复杂了。考虑对于每个 $A_i+A_j$，当第 $k$ 位（从个位开始）发生进位时，一定是 $A_i$ 和 $A_j$ 的前 $k$ 位加起来大于等于 $10^{k+1}$。所以定义 $b_{j,i}$ 表示 $a_i$ 的前 $j$ 位，每次枚举 $i$，第二项总和加上和 $i$ 加起来大于等于 $10^{j+1}$ 的数字数量。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//记得开long long
const int N=2e5+10,M=16;
ll n,a[M][N];
int main(){
	cin>>n;
	ll ans=0;
	for(int i=1;i<=n;i++){
		ll x;
		cin>>x;
		ll y=10;
		for(int j=1;j<M;j++){//记录下x的每一位
			a[j][i]=x%y;
			y*=10;
		}
		while(x){//统计所有x的f(x)值
			ans+=x%10;
			x/=10;
		}
	}
	ans*=2*n;//每个数作为x时有n次累加,作为y时还有n次,所以一共为2n次 
	ll y=1;
	for(int i=1;i<M;i++){
		y*=10;
		sort(a[i]+1,a[i]+n+1);//用lower_bound前预处理 
		for(int j=1;j<=n;j++){
			ans-=9*(a[i]+n+1-lower_bound(a[i]+1,a[i]+n+1,y-a[i][j]));
		}
	}
	cout<<ans;
	return 0;
} 
```

---

## 作者：DaydreamWarrior (赞：2)

[可能更好的阅读体验](https://rainlycoris.github.io/#/post/16)

## 题意简述

设 $f(x)$ 为 $x$ 的数字和。例如 $f(158)=1+5+8=14$。

给定一个长度为 $N$ 的正整数序列 $A$，求 $\sum_{i=1}^{N}\sum_{j=1}^{N}f(A_i+A_j)$。

## 分析

设 $g(a,b)$ 为 $a+b$ 进位的次数，则 $f(a+b)=f(a)+f(b)-9 \times g(a,b)$，其中 $\sum_{i=1}^{N}\sum_{j=1}^{N}f(A_i)+f(A_j)=2 n \times \sum_{i=1}^{N} f(A_i)$。

考虑如何计算 $\sum_{i=1}^{N}\sum_{j=1}^{N}g(A_i,A_j)$。对于两个数 $x,y$，如果 $x+y$ 在第 $d$ 位上有进位，当且仅当 $x \bmod 10^d+y \bmod 10^d \geq 10^{d+1}$。将所有 $A_i \bmod 10^d$ 排序，枚举 $d$ 和 $A_j$ 去二分 $A_i \bmod 10^d$ 中大于 $10^{d+1}-A_j \bmod 10^d$ 的值的个数即可。


## 代码
```cpp
const int N = 200005,M = 17;
int a[M][N];
int n;

signed main(){
    cin >> n;
    int ans = 0;
    for(int k=1;k<=n;k++){
        int c;
        cin >> c;
        int d = 10;
        for(int j=1;j<M;j++){
            a[j][k] = c%d;
            d *= 10;
        }
        while(c){
            ans += c%10;
            c /= 10;
        }
    }
    ans *= 2*n;
    for(int k=1;k<M;k++)
        sort(a[k]+1,a[k]+1+n);
    int d = 10;
    int sum = 0;
    for(int k=1;k<M;k++){
        for(int j=1;j<=n;j++){
            int w = a[k]+n+1-lower_bound(a[k]+1,a[k]+1+n,d-a[k][j]);
            sum += w;
        }
        d *= 10;
    }
    cout << ans-sum*9;
    return 0;
}
```

---

## 作者：sad_lin (赞：1)

## 题意：

设 $f(x)$ 为 $x$ 的数字和。例如 $f(158)=1+5+8=14$。

给定一个长度为 $N$ 的正整数序列 $A$，求 $\sum_{i=1}^{N}\sum_{j=1}^{N}f(A_i+A_j)$。

## 分析：

首先明确 $f(x)$ 为 $x$ 的**数位和**。

举例情况：

若有两个数分别为：$12,21$。

$$ 
f(12+21)=f(12)+f(21)=3
$$

可以发现**两个数相加的数位和**可以转化为**第一个数的数位和**和**第二个数数位和**相加。

但总有特殊情况如：

这两个数分别为：$53,27$。

$$
f(53+27)=f(80)=8
$$

$$
f(53)+f(27)=8+9=17
$$

可以发现这两个数的数位相加时在个位上**进了一位**，就不符合上面的情况了，那该怎么办呢？

仔细思考**进位**对**数位和**的贡献是什么？

相当于此位变为 $0$ 和更高的一位 $+1$，则是对总答案相当于贡献了 $-9$。

那么我们就**明确了计算的过程**：

设 $g(a,b)$ 表示 $a+b$ **进位个数**。

$$
f(a+b)=f(a)+f(b)-9\times g(a,b)

\\
 f(a)+f(b)=\sum_{i=1}^{N}\sum_{j=1}^{N}f(A_i)+f(A_j)=2N \times \sum_{i=1}^{N}f(A_i)

\\

9\times g(a,b)=9 \times \sum_{i=1}^{N}\sum_{j=1}^{N}g(A_i,A_j)

$$

第二个式子为什么是 $2n$ 呢？因为它作 $a_i$ 时加了 $n$ 次，它作 $a_j$ 时被加了 $n$ 次。

那怎么求 $g(a,b)$ 呢？

对于两个数 $a,b$，如果 $a+b$ 在第 $x$ 位上发生了进位，那么有 $a+b\ge10^x$。

那么我们就可以枚举 $x$，按照每个前 $x$ 位的数的**大小排序**，再枚举 $j$，二分找到第一个 $a_j+a_k\ge10^i$ 的数的下标 $k$，$k$ 后面的数就全是可以进位的，然后就可以 $(n-k+1)$ 求出 $g(a,b)$ 的个数了。

时间复杂度为 $O(n\log{n})$。

下面见代码（有注释不要担心）：

**注：十年OI一场空，不开long long 见祖宗**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int n;
ll x;
ll a[20][200005];//a[前几位的数][第几个数] 
ll ans=0;
ll p(ll x){//计算数位和 
	ll sum=0;	
	while(x){
		sum+=x%10;
		x/=10;
	}
	return sum;
}

int main() {
	scanf("%d",&n);
	
	for(int i=1;i<=n;i++){
		scanf("%lld",&x);
		ans+=2*n*p(x);//先不考虑进位，单纯地都加上 
		ll mod=10;
		for(int y=1;y<=15;y++){
			a[y][i]=x%mod;//前i的数为记录起来 
			mod*=10;
		}
	}	
	ll w=1;
	for(int i=1;i<=15;i++){//枚举前i位 
		w*=10;
		sort(a[i]+1,a[i]+1+n);//对前i位的数的大小进行排序 
		for(int j=1;j<=n;j++){//对每个数进行排序 
		
			//统计加上a[i][j]后大于等于10^i的个数 
			ll k=n+1-(lower_bound(a[i]+1,a[i]+1+n,w-a[i][j])-a[i]);
			ans-=9*k;//减去进位减少的贡献 
		}
	}
	
	cout<<ans; 
	
    return 0;
}
```

---

## 作者：xuezhiyu (赞：1)

# 题面

## 题目描述

对于正整数 $x$，设 $f(x)$ 表示其数位之和，现给定一个数列 $A=(A_1,A_2,\cdots,A_N)$，求 $\displaystyle{\sum_{i=1}^N \sum_{j=1}^N f(A_i+A_j)}$。

## 数据范围

$1 \le N \le 2 \le 10^5$

$1 \le A_i \le 10^5$

# 分析题目

因为这道题的数据范围 $2 \times 10^9$ 太大了，所以直接暴力就会炸掉。只能用更快的算法。

不妨设 $g(a,b)$ 为 $a$ 和 $b$ 相加时进位的个数，那么容易得知 $f(a+b)=f(a)+f(b)-9 \times g(a,b)$，那么原来需要求的 $\displaystyle{\sum_{i=1}^N \sum_{j=1}^N f(A_i+A_j)}$ 就变成了 $\displaystyle{\sum_{i=1}^N \sum_{j=1}^N(f(A_i)+f(A_j)-9 \times g(a,b))}$。

$$
\sum_{i=1}^N\sum_{j=1}^N(f(A_i)+f(A_j)-9 \times g(a,b))= \sum_{i=1}^N\sum_{j=1}^N(f(A_i)+f(A_j))-9 \times \sum_{i=1}^N \sum_{j=1}^N g(A_i,A_j)
$$

其中 $\displaystyle {\sum_{i=1}^N\sum_{j=1}^N(f(A_i)+f(A_j))}=2 \times n \times \displaystyle \sum_{i=1}^N f(A_i)$，在输入的时候就可以 $\text O(N)$ 计算。

然后就是要计算 $\displaystyle{\sum_{i=1}^N \sum_{j=1}^N g(A_i,A_j)}$ 了。我们先分析一下整数的进位，如果两个数 $a$ 和 $b$ 在第 $d$ 位上有进位，当且仅当 $x \bmod {10^d}+y \bmod {10^d} \ge 10^{d+1}$，那么我们就可以枚举 $d$ 和 $A_i$ 去二分 $A_j \bmod {10^d}$ 中有多少个数大于 $10^{d+1}-A_i \bmod 10^d$ 再累加就行了。

在具体代码实现中，我们可以不存 $A_i$，在输入的时候累加 $\displaystyle{\sum_{i=1}^N\sum_{j=1}^N(f(A_i)+f(A_j))}$，只用一个二维数组（第一位 $d$，第二维 $i$）记录 $A_i \mod 10^d$，再运算的时候直接用。至于二分，完全不用自己写， `std` 标准库中又有一个 `lower_bound`，排好序后直接用，个数的话就是坐标，因为整个数组都是排好序的。

**注意：要开 `long long`！**

# 代码时间

```cpp
#include <algorithm>
#include <iostream>
#define int long long

using namespace std;

const int N = 2e5 + 10, M = 17;
int n, a[M][N], ans;

signed main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int t;
        cin >> t;
        int temp = 10;
        for (int j = 1; j < M; j++) {
            a[j][i] = t % temp;
            temp *= 10;
        }
        while (t) {
            ans += t % 10;
            t /= 10;
        }
    }
    ans *= 2 * n;
    for (int i = 1; i < M; i++) sort(a[i] + 1, a[i] + n + 1);
    int temp = 10, sum = 0;
    for (int i = 1; i < M; i++) {
        for (int j = 1; j <= n; j++)
            sum += a[i] + n + 1 - lower_bound(a[i] + 1, a[i] + n + 1, temp - a[i][j]);
        temp *= 10;
    }
    cout << ans - sum * 9;
    return 0;
}
```

---

## 作者：Jasonshan10 (赞：1)

## 题意

- 定义 $f(x)$ 表示 $x$ 的数字和。

- 现给定一个长度为 $n$ 的正整数序列 $X$，求 $ {\textstyle \sum_{i=1}^{n}}  {\textstyle \sum_{j=1}^{n}} f(X_i+X_j)$。

## 思路

- 首先我们定义 $d(x,y)$ 表示在 $x+y$ 的过程中进位了几次。

- 可得 $f(x+y)=f(x)+f(y)-d(x,y)\times 9$。

- 我们求的答案变为 ${\textstyle \sum_{i=1}^{n}}  {\textstyle \sum_{j=1}^{n}} f(X_i+X_j)={\textstyle \sum_{i=1}^{n}}  {\textstyle \sum_{j=1}^{n}} f(X_i)+f(X_j)-9\times {\textstyle \sum_{i=1}^{n}}  {\textstyle \sum_{j=1}^{n}} d(X_i,X_j)$。

- 所以我们只需要求出 ${\textstyle \sum_{i=1}^{n}}  {\textstyle \sum_{j=1}^{n}} f(X_i)+f(X_j)$ 和 ${\textstyle \sum_{i=1}^{n}}  {\textstyle \sum_{j=1}^{n}} d(X_i,X_j)$ 即可。

- 对于 ${\textstyle \sum_{i=1}^{n}}  {\textstyle \sum_{j=1}^{n}} f(X_i)+f(X_j)$，非常简单，因为对于每个 $x$，在 $X_i$ 和 $X_j$ 上各贡献 $n$ 次，所以我们相当于求 ${\textstyle \sum_{i=1}^{n}} f(X_i)\times 2 \times n$，时间复杂度 $O(n)$。

- 对于 ${\textstyle \sum_{i=1}^{n}}  {\textstyle \sum_{j=1}^{n}} d(X_i,X_j)$，我们考虑什么时候会进位，只要当 $X_i$ 和 $X_j$ 的前 $k$ 位 $\ge 10^k$ 时，才会产生进位。（这里的 $k$ 从个位开始）

- 对于快速算 ${\textstyle \sum_{i=1}^{n}}  {\textstyle \sum_{j=1}^{n}} d(X_i,X_j)$，我们可以采用二分，时间复杂度 $O(n\log n)$。

- 总时间复杂度 $O(n\log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N=2e5+5,M=18;
ll f[M][N],ans;
ll check(ll x){
	ll cnt=0;
	while (x!=0){
		cnt+=x%10;
		x/=10;
	}
	return cnt;
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		ll t;
		scanf("%lld",&t);
		for(ll w=1,now=10;w<=15;++w){
			f[w][i]=t%now;
			now=now*10;
		}
		ans=ans+2*n*check(t);
	}
	ll now=1;
	for(int i=1;i<=15;++i){
		now=now*10;
		sort(f[i]+1,f[i]+n+1);
		for(int j=1;j<=n;++j){
			ans=ans-9*(-lower_bound(f[i]+1,f[i]+n+1,now-f[i][j])+f[i]+n+1);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：farfarqwq (赞：1)

## 前言

这个彩笔在一场二分比赛中想了这道题的简化版两小时没想出来。

## 题意

给你一个长度为 $n$ 的数组 $a$，对于任意 $(a,b)$，求它们的**和的数字和**之和。

以下用 $f(x)$ 表示 $x$ 的数字和，用 $g(x,y)$ 表示 $x+y$ 共进位了几次。

$n \le 2\times 10^5$

## 解法

首先需要一个性质：

$f(x+y)=f(x)+f(y)-9 \times g(x,y)$

对于 $x+y$，假如第 $i$ 位发生进位（第 $i$ 位加完了 $>10$），那么第 $i+1$ 位 $+1$，第 $i$ 位 $-10$

所以数字和 $-10+1$，相当于 $-9$。

发生多少个进位减几次 $9$。

那么，只要算出 $\sum_{x=1}^n\sum_{y=1}^n{f(a_x)+f(a_y)}$ 和 $9\times \sum_{x=1}^n\sum_{y=1}^n{g(a_x,a_y)}$，再把他们**相减**就行了。

**前面的那一项**很好算，可以发现对于每个 $i$，作为 $x$ 时贡献了 $n$ 次，作为 $y$ 时也贡献了 $n$ 次，所以相当于 $\sum_{i=1}^n{2\times n \times f(a_i)}$。

**第二项**考虑对于每个 $a_i+a_j$，当第 $k$ 位（从个位开始）发生进位时，一定是 $a_i$ 和 $a_j$ 的前 $k$ 位加起来大于等于 $10^{k+1}$。

所以定义 $b_{j,i}$ 表示 $a_i$ 的前 $j$ 位，每次枚举 $i$，第二项总和加上**和 $i$ 加起来大于等于 $10^{j+1}$** 的数字数量（自己也可以）。

自然想到二分，所以直接上就行了。

**记得开long long**。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 200005;
ll a[20][N];
int main() {
    int n;
    ll ans = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        ll x;
        scanf("%lld", &x);//用x表示a[i]，因为后面不用了
        for (ll now = 10, l = 1; l < 16; now *= 10, ++l) {//l是前l位，now是10^l
            a[l][i] = x % now;//比如111的前1位，那就是111%(10^1)=1，前2位就是111%(10^2)=11
        }
        while (x) {
            ans += n * 2 * (x % 10);//第一部分
            x /= 10;
        }
    }
    ll pw = 1;//pw就是10^i
    for (int i = 1; i <= 15; i++) {
        pw *= 10;
        sort(a[i] + 1, a[i] + n + 1);//排序，为二分做准备
        for (int j = 1; j <= n; j++) {
            ans -= 9 * (a[i] + n + 1 - lower_bound(a[i] + 1, a[i] + n + 1, pw - a[i][j]));//a[i]+n+1是存储前i位的数组末项指针，减去lowerbound的指针就是有多少个数>=pw-a[i]
        }
    }
    printf("%lld", ans);
	return 0;
}
```

有问题记得私信/评论

---

## 作者：CaoSheng_zzz (赞：0)

对于本题，权值统计方式：

1. 每一个数位上的权值直接相加。
2. 对于数位上相加大于 $10$ 的数我们需要在他们相加后 $-9$。

我们接着再看 $\sum \limits_{i=1}^n \sum \limits_{j=1}^n f(a_i + a_j)$，先设 $g(a_i)$ 为 $a_i$ 所有数位上的数字之和。我们就可以发现对于每一个 $a_{i_{1 \leq i \leq m}}$ 我们都算了 $2n$ 次，所以我们可以求出 $ 2 \times \sum \limits_{i=1}^n g(a_i)$。

然后我们需要维护任意两个数字在同一数位上相加大于 $10$ 的方案，但是我们又不能枚举每一位上的数字，我们得算进位产生的后效性。

所以对于 $a_i$ 从低位到高位的第 $k$ 位，我们看他对权值的贡献就可以去找有多少 $a_j \geq 10^{k+1} - (a_i \bmod 10^k)$。

为了避免不必要的循环，我们可以先对 $a$ 数组排序，我们寻找第一个 $a_j \geq 10^{1} - (a_i \bmod 10^k)$ 中 $j$ 的位置，然后用 $n - j + 1$，我们就可以求出有多少个数对答案具有 $-9$ 的贡献。

我们设 $mis$ 为有多少对数，对答案有 $-9$ 的贡献。最后的答案就为 $2 \times \sum \limits_{i=1}^n g(a_i) - mis \times 9$。

（代码是我考试的时候写了，为了避免正解不小心写错了挂分，所以我写了 subtask_1 这个 $60$ 分暴力）。

Code：

```cpp
#include <algorithm>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <queue>
#include <map>
#define prt printf
#define ll long long
#define int long long
#define spc prt(" ")
#define ent prt("\n")
using namespace std;

int read(){
	int f = 1 , k = 0;
	char c = getchar();
	while(c < '0' || c > '9'){
		if(c == '-') f = -1;
		c = getchar() ;
	}
	while(c >= '0' && c <= '9'){
		k = (k << 3) + (k << 1) + (c ^ 48);
		c = getchar() ;
	}
	return (f == 1 ? k : -k);
}

void output(int now){
	if(now > 9) output(now / 10);
	putchar((now % 10) ^ 48);
}

const int maxn = 2e5 + 1;
int n , a[maxn] , f[21][maxn];

namespace subtask_1{
	int f(int num){
		int res = 0;
		while(num){
			res += num % 10;
			num /= 10;
		}
		return res;
	}
	void main(){
		int ans = 0;
		for(int i=1 ; i<=n ; i++){
			for(int j=i+1 ; j<=n ; j++) ans += f(a[i] + a[j]) * 2;
			ans += f(a[i] + a[i]);
		}
		output(ans);
		return ;
	}
}

namespace subtask_2{ 
	int ans = 0 , s = 10 , mis_9 = 0; 
	
	int F(int i , int num){
		int res = 0 , j = 0 , d = 10 , cnt = num;
		while(num){
			res += num % 10;
			f[++ j][i] = cnt % d;
			d *= 10;
			num /= 10;
		}
		for( ; j<=16 ; j++) if(! f[j][i]) f[j][i] = f[j - 1][i];
		return res;
	} 
	
	void main(){
		for(int i=1 ; i<=n ; i++) ans += F(i , a[i]);
		for(int i=1 ; i<=16 ; i++) sort(f[i] + 1 , f[i] + n + 1);
		for(int i=1 ; i<=16 ; i++){
			for(int j=1 ; j<=n ; j++){
				mis_9 += f[i] + n + 1 - lower_bound(f[i] + 1 , f[i] + n + 1 , s - f[i][j]);
			}
			s *= 10;
		}
		output(ans * 2 * n - mis_9 * 9);
		return ;
	}
}

signed main(){
	freopen("digit.in" , "r" , stdin);
	freopen("digit.out" , "w" , stdout);
	n = read() ; for(int i=1 ; i<=n ; i++) a[i] = read() ;
	if(n <= 2000) subtask_1::main() ;
	else subtask_2::main() ;
	return 0;
}
```

---

## 作者：FRZ_29 (赞：0)

# AtCoder [ARC158C] All Pair Digit Sums 题解  
题目传送门： [AtCoder](https://atcoder.jp/contests/arc158/tasks/arc158_c)， [luogu](https://www.luogu.com.cn/problem/AT_arc158_c)。  
[也许更好的阅读体验](https://www.cnblogs.com/FRZ29/p/18336998)。
## 思路
考虑两个数对答案的贡献是多少。  
发现若某一位没有发生进位，该位的贡献即为两个数的和，否则为两数之和减去 $9$。  
设 $g(A_i + A_j)$ 表示 $A_i + A_j$ 的进位次数。  
易得：$\sum_{i = 1}^N \sum_{j = 1}^Nf(A_i + A_j)=2\times \sum_{i = 1}^N f(A_i) + 9\times\sum_{i = 1}^N\sum_{j = 1}^Ng(A_i+A_j)$。  
如何求 $g(A_i+A_j)$：依次考虑 $A_i$ 和 $A_j$ 的每一位，若该位能进位则 $g(A_i + A_j) \leftarrow g(A_i+A_j) + 1$。  
发现依次对每个数计算的时间复杂度为 $O(n^2)$，而若预处理时对于所有数的前 $d$ 位数进行排序，就可以二分求解。时间复杂度为 $O(n\log n)$。
## 代码

```cpp
#include <algorithm>
#include <iostream>
#include <cstdio>
typedef long long LL;

using namespace std;

const int N = 2e5 + 5;

#define LF(i, __l, __r) for (int i = __l; i <= __r; i++)
#define RF(i, __r, __l) for (int i = __r; i >= __l; i--)

LL ksm[20],ans;
LL a[20][N], n;

int main() {
    scanf("%d", &n);
    ksm[0] = 1;
    LF(i, 1, 15) ksm[i] = ksm[i - 1] * 10;

    LF(i, 1, n) {
        LL x;
        scanf("%lld", &x);
        LF(j, 1, 15) a[j][i] = x % ksm[j];

        while (x) {
            ans += x % 10;
            x /= 10;
        }
    }
    ans = ans * n * 2;
    LF(i, 1, 15) {
        sort(a[i] + 1, a[i] + n + 1);
        LF(j, 1, n) {
            LL fi = ksm[i] - a[i][j];
            LL low = lower_bound(a[i] + 1, a[i] + n + 1, fi) - a[i];
            ans -= 9 * (n - low + 1);
        }
    }

    printf("%lld", ans);
    return 0;
}
```

---

## 作者：MSavannah (赞：0)

**Statement**

设 $f(x)$ 为 $x$ 的数字和。

给定一个长度为 $n$ 的序列 $A$。求 $\sum\limits_{i=1}^n\sum\limits_{j=1}^nf(a_i,a_j)$。

**Solution**

首先注意到一个关键性质。设 $g(a,b)$ 表示 $a+b$ 的进位次数，则有 $f(a+b)=f(a)+f(b)-9\times g(a,b)$。

证明：

如果 $a+b$ 在第 $k$ 位发生进位。那么第 $k$ 位减 $10$，第 $k+1$ 位加 $1$。所以对于每一次进位，相当于减 $9$。

推出这个性质就好办了，我们发现要求的式子变成了：

$$\sum\limits_{i=1}^n\sum\limits_{j=1}^nf(a_i)+f(a_j)-9\times g(a_i,a_j)$$

对于前一项就是 $2\times n\times \sum\limits_{i=1}^nf(a_i)$。问题就进一步转化成了如何快速求 $\sum\limits_{i=1}^n\sum\limits_{j=1}^ng(a_i,a_j)$。

考虑 $a+b$ 的位置 $k$ 要进位需要满足什么，显然必须要满足 $a\bmod 10^k+b\bmod 10^k\geq10^k$。

每次将取模后的序列排序，枚举每个数，二分出满足上述要求的起始点，贡献就是从起始点开始的后缀长度。

每次二分求 $g(a,b)$ 的时间复杂度是 $O(\log n)$ 的，总时间复杂度 $O(nk\log n)$。

[code](https://www.luogu.com.cn/record/158186788)

---

## 作者：Cloote (赞：0)

## 题目分析
我们可以先从简单一点的情况开始分析，如果现在 $a_{[i]},a_{[j]}$ 都**不会进位**，那么最后的 $f(a_{[i]}+a_{[j]})=f(a_{[i]})+f(a_{[j]})$。证明如下：

有两个数 $x=\overline{x_nx_{n-1}....x_1}$ 和 $y=\overline{y_my_{m-1}...y_1}$。令 $n\le m$，由于不会进位,所以最后它们两相加应该是 $z=\overline{y_my_{m-1}...y_{n+1}(x_n+y_n)...(x_1+y_1)}$，那么 $f(z)=y_m+y_{m-1}...y_{n+1}+x_n+y_n+....x_1+y_1=\sum\limits_{i=1}^n x_i+\sum\limits_{i=1}^m y_i=f(x)+f(y)$。

**考虑进位的情况**，还是先从简单的入手，比如现在 $x$ 和 $y$ 都是一位数且它们的和要大于 $10$。那么 $z=x+y=\overline{1(x+y-10)}$，于是 $f(z)=1+x+y-10=x+y-9=f(x)+f(y)-9$。

根据之前的分析，我们可以推测一下，每进一次位最终的答案就会减去 $9$，那么 $f(x+y)=f(x)+f(y)-9g(x+y)$。其中 $g$ 函数表示进位次数。

**考虑如何求 $g$ 函数**，一个显然的结论：如果 $x+y$ 会进位并且 $z\ge y$，那么 $x+z$ 也必定进位。根据这个性质，我们可以存储所有数的后 $i$ 位放进 $nbr_{[i]}$ 中，从小到大排个序。接着双指针维护，一个指针指现在是求第 $i$ 与多少个数发生进位，另一个指针指向现在第一个不能与 $a_{[i]}$ 发生进位的数。前面这个指针从小往大扫，后面这个指针从大往小扫。

当然二分也是可行的，只是其他题解二分已经很详细了，但是双指针题解比较少，所以我来补充一发，顺便提供一下此题是如何一步一步思考到正解的。

最大时间复杂度大概是 $O(n \log n)$。

## 参考代码
~~~cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,a[N];
int sum[N][20];
vector<int>nbr[20];

int f(int cur,int x){
	int ansi=0,cnt=0,now=1;
	while(x){
		cnt++;
		ansi+=(x%10);
		sum[cur][cnt]=sum[cur][cnt-1]+(x%10)*now;
		now*=10;
		x/=10;
	}
	return ansi; 
}

signed main(){
	ios::sync_with_stdio(false);
	cin>>n;
	int ansi=0;//所有f函数的和
	for(int i=1;i<=n;i++){
		cin>>a[i];
		ansi+=f(i,a[i]);
		
		for(int j=1;j<=15;j++){
			if(!sum[i][j]) sum[i][j]=sum[i][j-1];//有可能这个数不满15位
			nbr[j].push_back(sum[i][j]);
		}
	}
	
	for(int i=1;i<=15;i++){
		nbr[i].push_back(0);
		sort(nbr[i].begin(),nbr[i].end());
	}
	
	int tmp=0,k=1;//tmp表示所有g函数的和
	for(int i=1;i<=15;i++){
		int now=n;
		k*=10;
		for(int j=0;j<=n;j++){
			while(nbr[i][j]+nbr[i][now]>=k) now--;
			tmp+=n-now;
		}
	}
	cout<<ansi*2*n-tmp*9;
	return 0;
}

~~~

感谢巨佬 Biuld 帮我 debug 并教我怎么算时间复杂度/bx

---

## 作者：Leasier (赞：0)

考虑逐位统计。对于某一位 $x$ 的贡献我们只需要知道：

- 不考虑进位时第 $x$ 位的数位和。
- 从第 $x - 1$ 位进了几位。
- 向第 $x + 1$ 位进了几位。

对于第一类贡献，我们直接开个桶统计即可。

对于第二类贡献，我们考虑在一棵插入了所有 $a_i$ 的 Trie 树上统计。下面我们来讨论一个数 $a_i$。

若要产生进位，则另一个 $a_j$ 一定形如：

- 前若干位（**可能为 $0$ 位**）与 $a_i$ 的前缀加起来是一堆 $9$ 拼在一起。
- 下一位与 $a_i$ 的这一位加起来 $\geq 10$。

于是我们在 Trie 树上记录子树和，遍历加起来全是 $9$ 的前缀并暴力扫一遍即可。

对于第三类贡献，我们还是在一棵 Trie 树上统计。枚举当前这个 $a_i$ 的第 $x$ 位是 $y$，然后把这些 $a_i$ 插入 Trie 树，最后用所有第 $x$ 位是 $9 - y$ 的 $a_j$ 类似地查询即可。

综上，时间复杂度为 $O(n |\Sigma| \log_{10}^2 w)$，其中 $w$ 为值域 $10^{15} - 1$。

- 如果用树状数组维护后缀和可以做到高贵的 $O(n \log_{10}^2 w \log |\Sigma|)$。~~但是有什么屁用吗？~~
- 如果上 Trie 树合并可以做到更高贵的 $O(n |\Sigma| \log_{10} w)$。~~看上去有点用了！~~

代码：
```cpp
#include <stdio.h>

typedef long long ll;

typedef struct {
	int cnt;
	int nxt[17];
} Node;

int id = 0;
int cnt[17][17];
ll val[200007][17];
Node tree[3000007];

inline void init(){
	for (int i = 1; i <= id; i++){
		tree[i].cnt = 0;
		for (int j = 0; j <= 9; j++){
			tree[i].nxt[j] = 0;
		}
	}
	id = 1;
}

inline void insert(int up, ll bit[]){
	int pos = 1;
	for (int i = up; i >= 1; i--){
		tree[pos].cnt++;
		if (tree[pos].nxt[bit[i]] == 0) tree[pos].nxt[bit[i]] = ++id;
		pos = tree[pos].nxt[bit[i]];
	}
	tree[pos].cnt++;
}

inline int query(int up, ll bit[]){
	int pos = 1, ans = 0;
	for (int i = up; i >= 1; i--){
		ll oppo = 9 - bit[i];
		for (int j = oppo + 1; j <= 9; j++){
			ans += tree[tree[pos].nxt[j]].cnt;
		}
		if (tree[pos].nxt[oppo] == 0) break;
		pos = tree[pos].nxt[oppo];
	}
	return ans;
}

int main(){
	int n;
	ll ans = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		ll a;
		scanf("%lld", &a);
		for (int j = 1; j <= 15; j++){
			val[i][j] = a % 10;
			a /= 10;
			cnt[j][val[i][j]]++;
		}
	}
	for (int i = 1; i <= 16; i++){
		int i_d = i - 1;
		init();
		for (int j = 0; j <= 9; j++){
			for (int k = 0; k <= 9; k++){
				ans += (ll)cnt[i][j] * cnt[i][k] * ((j + k) % 10);
			}
		}
		for (int j = 1; j <= n; j++){
			insert(i_d, val[j]);
		}
		for (int j = 1; j <= n; j++){
			ans += query(i_d, val[j]);
		}
		for (int j = 0; j <= 4; j++){
			init();
			for (int k = 1; k <= n; k++){
				if (val[k][i] == j) insert(i_d, val[k]);
			}
			for (int k = 1; k <= n; k++){
				if (val[k][i] == 9 - j) ans -= query(i_d, val[k]) * 20;
			}
		}
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：快乐的大童 (赞：0)

### 题目大意
令 $f(x)$ 为 $x$ 在十进制下各个数位之和，请求出 $\sum _{i=1}^n\sum_{j=1}^n f(a_i+a_j)$ 的值。

$n\le 2\times10^5,1\le a_i<10^{15}$
### 思路
>性质：$f(a+b)=f(a)+f(b)-9\times c$，其中 $c$ 为计算 $a+b$ 时进位的次数。

证明考虑模拟进位的过程即可。

原式转化为 $\sum_{i=1}^n f(a_i) \times2n-9\times c$，其中 $c$ 为总进位次数。

现在难点转移到如何快速判断一个数与其他 $n$ 个数的进位位数总和。

我们按位考虑，设我们枚举到了从低到高第 $j$ 位，发现将 $a_i$ 按照 $a_i\bmod10^j$ 从小到大排序后，由于两数 $x,y$ 的第 $j$ 位要发生进位要满足 $x\bmod10^j+y\bmod10^j\ge 10^j$，所以能产生进位贡献的数只能是排序数组的一段后缀。

我们考虑二分出它的起始点，这样的话我们就能在 $O(\log n)$ 的时间内计算出这 $n$ 个数与第 $i$ 个数第 $j$ 位产生进位的数的数量，将其乘以 $9$ 后从总答案中减去，最终枚举所有数和所有数位后得到的就是答案。

每次二分复杂度是 $O(\log n)$，再加上枚举数和枚举数位的复杂度，总时间复杂度是 $O(nk\log n)$，其中 $k=15$。

~~题外话：我赛时由于实现不好被卡的满天飞。~~
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int R(){
	int x=0,f=1;int ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}return x*f;
}
inline void write(int x){
	if(x<0){x=-x;putchar('-');}
	int y=0;char z[70];
	while(x||!y){z[y++]=x%10+48;x/=10;}
	while(y--)putchar(z[y]);
}
#define rep(a,b,c) for(int a=b;a<=c;a++)
const int maxn=2e5+5;
int n,a[maxn],b[maxn],mi[20];
int calc(int x){
	int res=0;
	while(x){
		res+=x%10;
		x/=10;
	}
	return res;
}
int ck(int bs,int x){
	int l=1,r=n,ret=n+1;
	while(l<=r){
		int mid=l+r>>1;
		if(b[x]+b[mid]>=mi[bs]) r=mid-1,ret=mid;
		else l=mid+1;
	}
	return n-ret+1;
}
signed main(){
	n=R();rep(i,1,n)a[i]=R();
	mi[0]=1;rep(i,1,15)mi[i]=mi[i-1]*10;
	int ans=0;rep(i,1,n)ans+=calc(a[i]);ans*=2*n;
	rep(j,1,15){
		rep(i,1,n)b[i]=a[i]%mi[j];
		sort(b+1,b+n+1);
		rep(i,1,n)ans-=ck(j,i)*9;
	}
	write(ans);
}

```


---

## 作者：JWRuixi (赞：0)

~~我不会写双指针……~~

- 题意

令 $f(x)$ 为 $x$ 十进制下的数为和，给定长度为 $n$ 的序列 $a$，求 $\sum\limits_{1\le i,j\le n}f(a_i+a_j)$。

- 分析

考虑答案可以表示成 $\sum\limits_{1\le i,j\le n}f(a_i)+f(a_j)$ 在减去进位的次数 $cnt$ 乘 $9$。也就是 $2n\sum\limits_{1\le i\le n}a_i - 9cnt$，转化成算 $cnt$。

考虑用 $s_{i,j}$ 表示数组中十进制下第 $i$ 位为 $j$ 的数的集合。若当前位和大于 $9$，肯定有进位，处理后缀和 $suf_j=\sum\limits_{k=j}^9|s_{i,k}|$，可以 $\mathcal O(n\log_{10}V)$ 计算。

第二种情况相对复杂就是当前为和为 $9$ 且两个数前 $i-1$ 位的和大于 $10^i$。考虑如果将 $s$ 按前 $i-1$ 位的值排序，直接用双指针复杂度 $\mathcal O(n\log n\log_{10}V)$，瓶颈在于排序。

综上复杂度为 $\mathcal O(n\log n\log_{10}V)$，可以通过本题。

- code

```cpp
#include <bits/stdc++.h>
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#define LL long long
#define int long long
#define pii pair<int, int>
#define writesp(x) write(x), putchar(' ')
#define writeln(x) write(x), putchar('\n')
#define FileIO(ch) freopen(ch".in", "r", stdin), freopen(ch".out", "w", stdout)
using namespace std;

namespace IO {
    char ibuf[(1 << 20) + 1], *iS, *iT;
#if ONLINE_JUDGE
#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
#else
#define gh() getchar()
#endif
    inline long long read() {
        char ch = gh();
        long long x = 0;
        bool t = 0;
        while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
        while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
        return t ? ~(x - 1) : x;
    }
    template <typename _Tp>
    inline void write(_Tp x) {
    	static char stk[64], *top = stk;
        if (x < 0) {
            x = ~(x - 1);
            putchar('-');
        }
        do *top++ = x % 10, x /= 10;
        while (x);
        while (top != stk) putchar((*--top) | 48);
    }
}

using IO::read;
using IO::write;

const int maxn(2e5 + 7);
int n, a[maxn], pw[maxn], ans, cnt, suf[15];
vector<pii> vc[16][10];

inline int getb (int x, int i) {
	return x / pw[i] % 10;
}

inline int calc (int x) {
	int res = 0;
	for (; x; x /= 10) res += x % 10;
	return res;
}

inline int gtb (int x, int i) {
	return a[x] % pw[i];
}

signed main() {
	pw[0] = 1; for (int i = 1; i <= 20; i++) pw[i] = pw[i - 1] * 10;
	n = read();
	for (int i = 1; i <= n; i++) a[i] = read();
	for (int i = 1; i <= n; i++) 
		for (int j = 0; j < 15; j++) 
			vc[j][getb(a[i], j)].emplace_back(make_pair(i, gtb(i, j)));
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 10; j++)
			sort(vc[i][j].begin(), vc[i][j].end(), [](const pii &x, const pii &y) { return x.second < y.second; });
	for (int i = 1; i <= n; i++) ans += calc(a[i]);
	ans *= (n << 1);
	for (int i = 0; i < 15; i++) {
		for (int j = 9; ~j; --j) suf[j] = suf[j + 1] + vc[i][j].size();
		for (int j = 1; j < 10; j++) cnt += suf[10 - j] * vc[i][j].size();
		for (int j = 0; j < 10; j++) {
			int k = 9 - j;
			if (vc[i][j].empty() || vc[i][k].empty()) continue;
			int p = 0, q = vc[i][k].size() - 1;
			for (; p < vc[i][j].size(); ++p) {
				while (~q && vc[i][k][q].second + vc[i][j][p].second >= pw[i]) --q;
				cnt += vc[i][k].size() - q - 1;
			}
		}
	}
	write(ans - cnt * 9);
}
// I love WHQ!
```

---

