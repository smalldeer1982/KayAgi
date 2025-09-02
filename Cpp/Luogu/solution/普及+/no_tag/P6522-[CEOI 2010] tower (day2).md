# [CEOI 2010] tower (day2)

## 题目背景

古巴比伦人决定建造一座塔。

## 题目描述

这座塔共有 $n$ 层，每层由一个边长为 $a_i$ 的立方体石块构成。一个石块 $i$ 能够直接放在石块 $j$ 上当且仅当 $a_i  \leq a_j+D$，其中 $D$ 为一个给定的常数。

你需要求出如果使用全部的石块，有多少种不同的搭建方案。输出答案 $\bmod\ 10^9+9$ 的结果。

**注意：即使两个石块的边长相同，也看做不同的石块。**


## 说明/提示

#### 【样例解释】

#### 样例 1 解释

首先把边长为 $100$ 的石块放在底部，其余的石块可以任意顺序放置，除了以下两种情况：`2,1,3` `1,3,2`。

#### 样例 2 解释

首先不允许在 $10$ 上面放 $20$。

所以就把 $20$ 一堆放在底下，$10$ 一堆放在上面。

即 $(3!)\times (3!)=36$。

#### 【数据规模与约定】

- 对于 $10\%$ 的数据，保证 $n\le 10$；
- 对于 $30\%$ 的数据，保证方案数不超过 $10^6$；
- 对于 $45\%$ 的数据，保证 $n\le 20$；
- 对于 $70\%$ 的数据，保证 $n\le 70$；
- 对于 $100\%$ 的数据，保证 $2\le n\le 6.2\times 10^5$，输入中所有数字为不超过 $10^9$ 的正整数。


#### 【说明】

**题目译自 [CEOI 2010](http://ceoi2010.ics.upjs.sk/Contest/Tasks) day 2 *[T3 tower](https://people.ksp.sk/~misof/ceoi2010/tow-eng.pdf)***。

翻译版权为题目提供者 @[ShineEternal](https://www.luogu.com.cn/user/45475) 所有，未经许可禁止转载。



## 样例 #1

### 输入

```
4 1
1 2 3 100```

### 输出

```
4```

## 样例 #2

### 输入

```
6 9
10 20 20 10 10 20```

### 输出

```
36```

# 题解

## 作者：Wan__Ye__Chu (赞：8)

## 前置条件：乘法原理
乘法原理：做一件事，有 $ n $ 个步骤需要依次完成，第一个步骤有 $ a_1$ 种方法，第二个步骤有 $ a_2 $ 种方法，第 $n $ 个步骤有 $a_n$ 种不同的方法，则完成这件事有      $\prod_{i=1}^na_i $ 种不同的方案。

## 思路
1. 排序。
2. 枚举。
3. 累乘。

易得方案数为 $y-x+1$。

当 $ a_x +D <a_y $ 时 $x = x+1$。

或者：计算方案数。

## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,d,ans=1,x=1;
int a[1114514];
const int mod=1000000009;

int main()
{
	ios::sync_with_stdio(0);
	cin>>n>>d;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+n+1);
	for(int y=1;y<=n;y++)
	{
		while(a[x]+d<a[y])
			x++;
		ans*=(y-x+1)%mod;
	}
	cout<<ans;
	return 0;
}
```
最后点个赞再走吧 qwq 。

等等！！！！！

上面的代码只能拿28分！
![](https://cdn.luogu.com.cn/upload/image_hosting/i5rzqg7e.png)

ans 会爆 int！！！要改为 long long！！！
```cpp
#include<bits/stdc++.h>
using namespace std;

long long n,d,ans=1,x=1;
long long a[1114514];
const int mod=1000000009;

int main()
{
	ios::sync_with_stdio(0);
	cin>>n>>d;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+n+1);
	for(int y=1;y<=n;y++)
	{
		while(a[x]+d<a[y])
			x++;
		ans=ans*(y-x+1)%mod;
	}
	cout<<ans;
	return 0;
}
```
这次真的对啦，真的。
![](https://cdn.luogu.com.cn/upload/image_hosting/l2n1rf7s.png)

---

## 作者：Azazеl (赞：6)

#### 题意
> $~~~~$ 给出 $n$ 个数表示砖长，通过排列使其构成一个数列，满足 $a_i+D\geq a_{i+1}$，求可以构成的数列个数（每个数字互不相同）

#### 题解

$~~~~$ 显然某一块砖能放在哪些砖上面是固定的，并且在升序的序列中，对于砖块 $i$ ，它可以放的砖块区间是一个右端 $r=n$，左端点 $l\leq i$ 的区间。  

$~~~~$ 因此先升序排序，从左至右对每一块砖维护其能放在哪些**前面**的砖上面。  

$~~~~$ 注意到必须满足 $a_i+d\geq a_j(i<j)$，因此在升序的 $a$ 序列里随着 $j$ 的增加，最小的满足条件的 $i$ 也会增加。  

$~~~~$ 因此对于每个砖块 $i$ 双指针维护合法区间 $[l,r]$（这里的 $r=i$ ），注意到放在地上/更大的砖上也是一种选择（但是放在哪块最大的砖上是由大砖来计算的），因此每块砖的合法数量为 $r-l+1$，累乘即可。

#### 代码
```cpp
#include <cstdio>
#include <algorithm>
#define ll long long
using namespace std;
int arr[620005];
const int MOD=1e9+9;
int main() {
	int n,k;ll Ans=1;
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d",&arr[i]);
	sort(arr+1,arr+1+n);
	for(int l=1,r=1;r<=n;r++)
	{
		while(arr[l]+k<arr[r]) l++;
		Ans=Ans*(r-l+1)%MOD;
	}
	printf("%lld",Ans);
	return 0;
}
```

---

## 作者：analysis (赞：3)

今天随机跳题跳到的，做一做。

## solution

先从小情况开始。

显然 $n=1$ 时，答案为 $1$，即直接摆放。

$n=2$ 时，我们考虑先摆放其中一个。

剩下一个如何摆？

如果 $a_1 + d \geq a_2$，$a_2$ 可以摆在 $a_1$ 上面。

如果 $a_2 + d \geq a_1$，$a_2$ 可以摆在 $a_1$ 下面。

对于上面的比较过程还是过于多以及麻烦了，考虑简化一下。

由于关乎大小关系，可以考虑排序一下 $a$ 数组。

则 $a_i \geq a_j(i \geq j)$。

对于第一种 $a_j + d \geq a_i$（$i$ 放置于 $j$ 上），在保证单调性后，可以使用一个指针维护最小的满足情况的 $j$。

对于第二种情况，在保证单调性后，显然成立。

所以 $i$ 的放置可能有：

在 $(i-1) - (j-1) = i-j$ 个石砖的上面。

在最下面。

共 $i-j+1$ 种。

```cpp
#include<bits/stdc++.h>
#define int long long
const int mod = 1e9+9;
using namespace std;
int n,d,a[700005];
signed main()
{
    cin>>n>>d;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+1+n);
	int ans = 1;
	for(int i=1,j=1;i<=n;i++)
	{
		while(a[j]+d<a[i])j++;
		ans = ans * (i-j+1) % mod;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Fkxxx (赞：2)

### 思路

本题乘法原理和双指针。

先对数组升序排序。

设 $r$ 上面只能放 $\left [l,r \right ]$ 这些石头。

我们可以用双指针维护 $l$ 和 $r$。

循环判断 $a_r-a_l>D$ 是否成立，成立就 $l\gets l+1$，否则 $ans \gets ans \times \left(r - l+1\right)\bmod 10^9+9,r\gets r + 1$。

### 参考代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MOD = 1e9 + 9 ;
int n , a[620005] , l , r , ans = 1 , d ;
signed main(){
    cin >> n >> d ;
    for( int i = 1 ; i <= n ; i ++ ){
        cin >> a[i] ;
    }
    sort( a + 1 , a + 1 + n ) ;
    l = r = 1 ;
    while( r <= n ){
        while( a[r] - a[l] > d ) l ++ ;
        ans *= r - l + 1 ;
        ans %= MOD ;
        r ++ ;
    }
    cout << ans ;
    return 0 ;
}
```

---

## 作者：yuzhechuan (赞：1)

递推题

---

### 题解：

既然所有的都要用，那我们就考虑从小到大插入砖块

注意到一个砖块只可以被放在特定长度的一段砖块里，于是可以双指针维护

将每个砖块的放置方案数累乘即可

---

### 代码：

```cpp
#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC target("avx,avx2")
#include <bits/stdc++.h>
using namespace std;
template<class t> inline t read(t &x){
	char c=getchar();bool f=0;x=0;
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f) x=-x;return x;
}
template<class t> inline void write(t x){
	if(x<0) putchar('-'),write(-x);
	else{if(x>9) write(x/10);putchar('0'+x%10);}
}

const int mod=1e9+9,N=6.2e5+5;
int n,k,ans=1,a[N];

signed main(){
	read(n);read(k);
	for(int i=1;i<=n;i++) read(a[i]);
	sort(a+1,a+1+n);
	for(int l=1,r=1;r<=n;r++){
		while(a[l]+k<a[r]) l++; //双指针维护可行区间
		ans=1ll*ans*(r-l+1);
	}
	write(ans);
}
```

---

## 作者：ZettaByte (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P6522)

### 题意

有 $n$ 个石块，$a_i$ 是第 $i$ 块石头的边长，如果 $a_i\le a_j+D$，那么石块 $i$ 能被直接放在石块 $j$ 上。让你求堆叠石块的总方案数。

### 解法

首先将 $a_i$ 按从小到大的顺序排序。

假设能使第 $i$ 块石头满足要求的石头只有 $[l,i)$，那么很明显，$l$ 只会随着 $i$ 的增加而增加。

因此使用双指针把 $a$ 数组扫一遍即可。方案数在处理过程中就可以统计。

#### AC CODE：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod = (int)1e9 + 9;
int a[620010];

int main()
{
	int n, d; scanf("%d%d", &n, &d);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	sort(a + 1, a + n + 1); long long ret = 1;
	for (int l = 1, r = 1; l <= n && r <= n; r++)
	{
		while (l <= n && a[l] + d < a[r]) l++;
		ret *= r - l + 1, ret %= mod;
	} printf("%lld\n", ret);
    return 0;
}
```

---

## 作者：iyka (赞：0)

题目简洁明了，我们只需了解一个帮助我们解题的东西——乘法原理：

（以下资料选自百度百科）

做一件事，完成它需要分成 $n$ 个步骤，做第一步有 $m_1$ 不同的方法，做第二步有 $m_2$ 种不同的方法，以此类推，那么做第 $n$ 步有 $mn$ 种不同的方法。那么完成这件事共有 $N=m_1×m_2×m_3×…×m_n$ 不同的方法。

那我们可以先对数组进行排序，再根据乘法定理跑一次 $a_1 \to a_n$，再在过程中统计可以使 $a_i+d<a_j$ 成立的每一步的方案数最后再相乘就可以了。（记得开 long long）

### 代码部分
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=7e5+10,mod=1e9+9;
int n,a[N],d,ans=1,i=1;
signed main()
{
    cin>>n>>d;
    for(int u=1;u<=n;++u)
        cin>>a[u];
    sort(a+1,a+n+1);
    for(int j=1;j<=n;++j)
    {
        while(a[i]+d<a[j]) //统计单个方案数
        	i++;
        ans=ans*(j-i+1)%mod;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：kanzaki (赞：0)

## 思路
观察本题要求，发现石块的体积越大，能放在他下面的石块则越少。

那么我们可以将石块按照大小从小到大排序。这时能放在某一个石块下面的必须排在那一个石块后面。并且所有可以的石块一定形成了一个连续的序列。

设当前石块大小为 $a$，给定的常数为 $D$，总共有 $n$ 个石块。则答案组成的序列从第一个大于 $a+D$ 的数开始，到序列最后一个数结束。产生的方案数为 $n-(a+D)$。

我们可以使用双指针求出序列并进行维护。如果右端点大于左端点加 $D$ 则将左端点右移，否则将产生的方案数加到答案中并将右端点右移。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define maxn 650005
#define mod 1000000009
#define int long long
int n,d,a[maxn],ans,l,r;
signed main(){
	cin>>n>>d;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	ans=l=r=1;
	while(r<=n){
		for(;a[l]+d<a[r];l++);
		ans=ans*(r++-l+1)%mod;
	}
	cout<<ans;
	return 0;
}//此代码码风奇怪，读者可以根据自己理解编写代码
```

---

## 作者：danb123 (赞：0)

## 题目大意
一组数据，如果一个数加上一个指定的常量大于等于另一个数，那这两个数就可以交换。求这种排列的方法数。
## 题目分析
很简单的一道模拟题目，先把这个序列从小到大排列好了，之后再用双指针进行遍历，如果符合上面的交换就把右指针加一，直到不符合以上操作要求为止。

接下来就可以将答案记录下来。
```cpp
ans*=y-x+1,ans=ans%1000000009,y++;//先更新它的方法数，再取余。并且左指针加一。
```
## 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll; 
ll n,m,a[1000001],x=1,y=1,ans=1;
int main() {
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+1+n);
	while(y<=n) {
		while(a[y]-a[x]>m)x++;
		ans*=y-x+1,ans=ans%1000000009,y++;
	}
	cout<<ans;
	return 0 ;
}
```
时间复杂度为线形，注意开到长整型。

---

## 作者：seika27 (赞：0)

### 分析
对于石头的尺寸，先将其从小到大排序。

对于 $a_i$，令只有在 $x\sim i$ 的区间内的石头能让 $a_i$ 放在其上面。

那么，其贡献的方案数为 $i-x+1$。

不难看出 $x$ 只会越来越大，考虑用双指针维护。

当 $a_x+D<a_i$ 时，将 $x$ 加一。

否则，计算方案数。

### code
```cpp
#include <bits/stdc++.h>
#define int long long 
#define cin std::cin
#define cout std::cout
int n,d;
int a[620001];
const int mod=1e9+9;
int ans=1;
signed main()
{
	cin>>n>>d;
	for(int i=1;i<=n;i++)cin>>a[i];
	std::sort(a+1,a+1+n);
	int l=1,r=1;
	while(r<=n)
	{
		while(a[l]+d<a[r])++l;
		ans=ans*(r-l+1)%mod;
		++r;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：NaturalSelection (赞：0)

## 思路

对于每一块石块，盖在上面的石块范围是一个闭区间，且下面石块的大小影响上方石块的大小，考虑使用~~深度优先搜索~~乘法原理。

## 前置知识

1. 乘法原理：做一件事，完成它需要分成 $n$ 个步骤，做第一步有 $m_1$ 种不同的方法，做第二步有 $m_2$ 种不同的方法，……，做第 $n$ 步有 $m_n$ 种不同的方法。那么完成这件事共有 $N=m_1 \times m_2 \times m_3 \times ……\times m_n$ 种不同的方法（内容来自[百度](https://baike.baidu.com/item/%E4%B9%98%E6%B3%95%E5%8E%9F%E7%90%86/7538447)）。

## 具体做法

先升序排序，再枚举符合条件的石块，累乘即可。

## 代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int a[(int)6.2*10000000];
long long ans=1;
int main(){
	int n,d;
	cin>>n>>d;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+1+n);
	for(int l=1,r=1;r<=n;r++){
		while(a[l]+d<a[r])l++;
        ans=ans*(r-l+1)%1000000009;
	}
	cout<<ans;
}
```


---

## 作者：封禁用户 (赞：0)

## 基本思路
本题主要需要使用深搜和乘法原理。

此处做完所有的事情的方法中第一件事情有 $n_1$ 中，第二件有 $n_2$ 种。以此类推，第 $m$ 件有 $n_m$ 种。所以总共有 $S = n_1 × n_2 × ... × n_m$  种方法。

所以本题做法如下：

1. 升序排序。
2. 全部枚举一遍。
3. 累乘答案。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int a[(int)6.2 * 10000000], ans = 1;

signed main()
{
	int n, d;
	cin >> n >> d;
	for(int i = 1; i <= n;i++)
    {
		cin >> a[i];
	}
	sort(a + 1, a + 1 + n);
	for(int l = 1, r = 1; r <= n; r++)
    {
		while(a[l] + d<a[r])
        {
        	l++;
        }
        ans = ans * (r - l + 1) % 1000000009;
	}
	cout << ans << endl;
    return 0;
}
```

---

