# Anu Has a Function

## 题目描述

Anu has created her own function $ f $ : $ f(x, y) = (x | y) - y $ where $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR). For example, $ f(11, 6) = (11|6) - 6 = 15 - 6 = 9 $ . It can be proved that for any nonnegative numbers $ x $ and $ y $ value of $ f(x, y) $ is also nonnegative.

She would like to research more about this function and has created multiple problems for herself. But she isn't able to solve all of them and needs your help. Here is one of these problems.

A value of an array $ [a_1, a_2, \dots, a_n] $ is defined as $ f(f(\dots f(f(a_1, a_2), a_3), \dots a_{n-1}), a_n) $ (see notes). You are given an array with not necessarily distinct elements. How should you reorder its elements so that the value of the array is maximal possible?

## 说明/提示

In the first testcase, value of the array $ [11, 6, 4, 0] $ is $ f(f(f(11, 6), 4), 0) = f(f(9, 4), 0) = f(9, 0) = 9 $ .

 $ [11, 4, 0, 6] $ is also a valid answer.

## 样例 #1

### 输入

```
4
4 0 11 6```

### 输出

```
11 6 4 0```

## 样例 #2

### 输入

```
1
13```

### 输出

```
13```

# 题解

## 作者：oimaster (赞：18)

## 题目
如果不知道题面的请点击题目链接：<https://www.luogu.com.cn/problem/CF1299A>

这里不多做介绍，毕竟这道题翻译的还行。
## 或运算
首先，这道题一定是一道关于二进制的题目，作者对二进制其实不太敏感，所以我们不如一起研究一下这个`或`逻辑运算。如果你很熟悉，我建议跳过这一段。
```
这个运算是一位一位“或”的。
这个运算很快，因为是计算机底层的操作。
规则：
0|0=0
0|1=1
1|0=1
1|1=1
发现了：只有在两个数都为0的时候才会是0，其他时候返回1。
那么再举个例子，5|3是多少？
5转二进制是101
3转二进制是11
那么就是这样的画面：
101
011    //这里位数不够，补前导零
111    -> 7 
所以3|5的结果是7。
```
好的，现在关于`或`运算我们已经很熟悉了。
## 函数分析
接下来我们可以把这个函数`f`来研究研究。

这个函数请你自己分析一些二进制，我在这里只写一个结论。请你自觉分析。

好嘞，现在我来告诉大家自己分析的结果。
```
这个函数有两个参数，我们把它们命名为x和y。
我们一位一位看。（二进制）
如果y的这位是0的话，那么这一位最终结果就是x的这一位。
如果y的这位是1的话，那么这一位最终结果就是0。（为什么？大家自己想吧）
```
但是我们再看看这个函数有点乱，这道题目的函数嵌套实在是太烦了，不如我们把这个函数的内容弄在一个运算符里，把这个新符号叫做`#`。

这样，整个表达式就可以被整理了。最后发现结果就是
$$a_1\#a_2\#a_3\#...\#a_{n-1}\#a_n$$
居然这么简单！现在这个运算符的操作我们也知道了，我们只需要想一想怎样可以让这个数字最大。
我们先要了解，这个运算符是有一下的性质的。
$$a_1\#a_2\#a_3\#...\#a_{n-1}\#a_n=a_1\#a_3\#a_4\#...\#a_n\#a_2$$
光这样写我知道你肯定弄不懂这是什么意思的，我用中文再表达一遍。
```
这个运算符号把第一个数确定后，不管后面的数字怎么调换位置，这个结果都是不变的。
为什么？你可以结合上面这个运算符的意义来证明。
```
这样，我们只需确定第一个数是多少了。
## 解法
有没有发现，题目已经变得很简单了？没错，我们现在只需要判断第一个数是什么。

我们可以假设这个数字已经确定了。

接下来，我们再次分析。注意，后面凡是提到数位的一定是二进制。

如果这个数字的某一位是$1$，且后面的一大堆数其中有至少一个数在这一位上也是$1$，我可以瞬间告诉你，这一个$1$已经报废了。为什么啊？因为这个运算符中，我们算到后来，一定会到这一位上也是$1$的那个数。当$y$这一位上的数字为$1$时，不管$x$这一位是几，结果都会是0。相当于这个数位已经无效了。

所以，我们发现有效位数只有`有且整个数组只有1个数在这一位上是1`的几位。

求这个很方便，预处理一下就行了。

接下来，我们可以把每个数字里的有效位都拿出来，组成数组$b$。

最后，只需要求出这个数组中最大的一个数，记下来下标$maxi$，然后输出就行了。
## 输出
我们只需要先答应$a_{maxi}$，最后顺序打印其他的数即可。
## 复杂度分析
首先，我们的方法几乎就是“比较大小”。

每个数扫一遍是$O(N)$算法。
中间内循环来取每个数的有效位最多有$32$次，而且还多了。为什么？C++中的int型变量或者是Pascal的longint变量就是$32$位的，最大值为$2147483647$，远远比数据范围中的$a_i$大了$2$倍多。

显然，不会超时。
## 代码
C++代码：
```cpp
#include<iostream>
using namespace std;
int n;
int bin[32];
int check(int x){
	int j=0;
	int ret=0;
	while(x){
		if((x&1)&&bin[j]==1)
			ret+=(1<<j);
		x>>=1;
		++j;
	}
	return ret;
}
int main(){
	cin>>n;
	int a[n+1];
	for(int i=1;i<=n;++i){
		cin>>a[i];
		int p=a[i];
		int j=0;
		while(p){
			if(p&1)
				++bin[j];
			p>>=1;
			++j;
		}
	}
	int maxi,maxv=-1;
	for(int i=1;i<=n;++i){
		int j=check(a[i]);
		if(j>maxv){
			maxv=j;
			maxi=i;
		}
	}
	cout<<a[maxi]<<' ';
	for(int i=1;i<=n;++i)
		if(i!=maxi)
			cout<<a[i]<<' ';
	return 0;
}
```
不过，还是希望大家自己完成代码，增加印象。

~~题解写了一个下午，求赞~~

---

## 作者：lemonfor (赞：5)

考虑贪心，分析按位运算结果后~~或者你可以一眼看出结果~~ ，如果两个数哪一位有多于一个 $1$ ，则运算结果一定为 $0$ 。。。

则如果只有一个 $1$ ，那么只有把那个 $1$ 放到答案序列第一个才可行 ，所以贪心考虑最高的只有一个 $1$ 的位 ，那个位为 $1$ 的数一定要放到最前面，后面的想怎么放就怎么放啦
```cpp
#include<cstdio>
#include<algorithm>
#define _ 0
#define INF 0x3f3f3f
#define int long long
#define N 500001
#define re register
#define drep(i ,l ,r) for(re int i = (r) ; i >= (l) ; -- i)
#define rep(i ,l ,r) for(re int i = l ; i <= r ; ++ i)
using namespace std;
int n ,a[N] ,_a[32] ,a_[32] ,maxn ,QAQ;
int read() {
    char cc = getchar() ; int cn = 0 ,flus = 1;
    while(cc < '0' || cc > '9') {if(cc == '-') flus = - flus ; cc = getchar();}
    while(cc >= '0' && cc <= '9') cn = cn * 10 + cc - '0' ,cc = getchar();
    return flus * cn;
}
signed main() {
    n = read();
    rep(i ,1 ,n) {
        a[i] = read();
        rep(j ,0 ,30) if(a[i] & (1 << j)) {if(!_a[j]) a_[j] = i; ++ _a[j];}
    }
    drep(i ,0 ,30) if(_a[i] == 1) {
        printf("%lld " ,a[a_[i]]);//把那个位为1的数放到最前面
        rep(j ,1 ,n) if(j != a_[i]) printf("%lld " ,a[j]);
        return ~~(0^_^0);
    }
    rep(i ,1 ,n) printf("%lld " ,a[i]);
    return ~~(0^_^0);
}
*/
```

---

## 作者：gyh20 (赞：4)

将式子变一变
 
$x | y - y = x - x\& y $

一般位运算都采取贪心的策略，满足最高位最大即可。

如果第 $i$ 位出现在最终答案之中，需要满足以下两个条件:

$1.$第一个数的第 $i$ 位为 $1$。(如果不为 $1$ ，则减去 $x\& y$ 后也不会出现 $1$。)

$2.$只有一个数的第 $i$ 位为 $1$。(如果存在另一个，那么在 $x - x\& y $ 后这一位会变成 $0$)

综上，我们只需要枚举每一位，看是否有且仅有一个数的第 $i$ 位为 $1$，如果有，则将它放在第一个。

```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
#define re register
using namespace std;
#define int long long
int n,a[100002],m,k;
inline int read(){
	re int t=0;
	re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0'){
		t=(t<<3)+(t<<1)+v-48;
		v=getchar();
	}
	return t;
}
signed main() {
	n=read();
	for(re int i=1;i<=n;++i)a[i]=read();
	for(re int i=31;i>=0;--i){
		int opt=0;
		int pos=0;
		for(re int j=1;j<=n;++j)if(a[j]&(1ll<<i))++opt,pos=j;
		if(opt==1){swap(a[1],a[pos]);break;
		}
	}
	for(re int i=1;i<=n;++i)printf("%lld ",a[i]);
}

```


---

## 作者：jijidawang (赞：2)

- [请去博客体验](https://www.luogu.com.cn/blog/writeSTL/solution-cf1299a)
- [题目传送门](https://www.luogu.com.cn/problem/CF1299A)

## 题面简述

> 定义函数 $\operatorname{f}(x,y)=\operatorname{f}(x|y)-y$
> 
> 给定数列 $a$，定义其价值 $s(a)=\operatorname{f}(\operatorname{f}(\operatorname{f}(\dots\operatorname{f}(a_1,a_2),a_3),\dots a_{n-1}),a_n)$，请重排序列 $a$,使得 $s(a)$ 最大，输出重排后序列。

## 算法分析

### [进位制](https://baike.baidu.com/item/%E8%BF%9B%E5%88%B6)

> 进位制是一种 *记数方式*，故亦称进位记数法/位值计数法，可以用有限的数字符号代表所有的数值。可使用数字符号的数目称为基数(`radix`)或底数，基数为 $n$，即可称 $n$ 进位制，简称 $n$ 进制。现在最常用的是十进制，通常使用 $10$ 个阿拉伯数字 $0\sim 9$ 进行记数。

任意一个 $k$ 进制整数 $r$ 都可表示为如下形式 ：

$$r=\sum_{i=0}^{\log_kr}k^ia_i=k^0a_0+k^1a_1+\dots k^{\log_kr}a_{\log_kr}$$

比如十进制：

$$r=\sum^{\lg r}_{i=0}10^ia_i$$

其中 $a_i$ 表示数字第 $i$ 位的数码，即 $a_i=\dfrac{r}{k^i}\bmod k$。

- 对任意一个 $k$ 进制整数，转换为 $10$ 进制可用上方展开式计算。
- 对任意一个 $10$ 进制整数，转换为 $k$ 进制可用短除法计算。

### 或运算

题目中的 $|$ 指**按位或**，是一种位运算。

比如要对 $a,b$ 做按位或，首先要把 $a,b$ 转换为二进制，然后一位一位的进行**逻辑或**。

- $a$ 按位或 $b$ 写作 $a\operatorname{or}b$ 或 $a|b$ （后面那种其实不对，是考虑`C++`选手习惯），$a$ 逻辑或 $b$ 写作 $a || b$

逻辑或表格如下：

![图片.png](https://i.loli.net/2020/03/24/rz6vEBbl27mVayH.png)

所以，当且仅当 $a,b$ 都为 $\mathrm{false}(0)$ 时，$a,b$ 逻辑或后的值才是 $\mathrm{false}(0)$。

比如计算 $5|3$：

$5=(101)_2,3=(11)_2$ （进制转换简写）

$\begin{aligned}
&\texttt{101}\\
\operatorname{or}\;&\texttt{011}&(\textsf{用}\,0\,\textsf{补齐})\\
\text{---}&\text{------}\\
&\texttt{111}
\end{aligned}
$

$(111)_2=7$，所以 $5\operatorname{or}3=7$ 。

### 函数 f 的分析

研究函数 $\operatorname{f}(x,y)$

按位分析：

- 如果 $y$ 的第 $i$ 位为 $0$ ，那么这一位最终结果就是 $x$ 的第 $i$ 位。

- 如果 $y$ 的这位是 $1$ 的话，那么这一位最终结果就是 $0$。

发现此函数 $\operatorname{f}$ 是将二进制中都为 $1$ 的位置 $0$。

不妨设：
$\operatorname{f}(x,y)=x @y$；

$a_1@a_2@a_3@\dots @a_n=@_{i=1}^na_i$。

所以数列价值表达式即为：

$$s(a)=\operatorname{f}(\operatorname{f}(\operatorname{f}(\dots\operatorname{f}(a_1,a_2),a_3),\dots a_{n-1}),a_n)=a_1@a_2@\dots @a_n=@_{i=1}^na_i$$

很容易发现：

$p@_{i=1}^na_i=p@_{i=1}^nc_i$，其中 $c_i=a_{d_i}$，$d$ 为 $n$ 的一个排列。

用自然语言讲述，就是：

> 第一个数不变，后面的数字可以自由打乱。

### 题目分析

我们现在只需要判断第一个数是什么。

假设这个数字已经确定了。

注意，后面凡是提到数位、数码的一定是二进制。

如果这个数字的第 $i$ 位是 $1$，且后面的数码其中有至少一个数在这一位上也是 $1$ ，我们算到后面时，一定会到这一位上也是 $1$ 的那个数。当 $y$ 这一位上的数字为 $1$ 时，不管 $x$ 这一位是几，结果都会是 $0$。

> 所以，我们发现有效位数只有整个数组只有 $1$ 个数在这一位上是 $1$ 的几位。

求这个很方便，预处理一下就行了。

接下来，我们可以把每个数字里的有效位都拿出来，组成数组 $b$。

最后，只需要输出数组 $b$ 里的最大值即可，即输出 $\max\limits_{i\in b}b_i$

### 复杂度分析

#### 空间复杂度分析

显然是 $\mathcal{O}(n)$。

#### 时间复杂度分析

扫描数码需要 $\mathcal{O}(\log n)$ 的时间，输入输出需要 $\mathcal{O}(n)$ 的时间，扫描数字需要 $\mathcal{O}(n)$ 的时间。

合计：$2\mathcal{O}(n)+\mathcal{O}(n)\mathcal{O}(\log n)=\mathcal{O}(n\log n)$。

---

## 作者：lzy120406 (赞：1)

## [原题](https://codeforces.com/problemset/problem/1299/A)
就是重新排列序列 $a_i$，使

$$ f(f(\dots f(f(a_1, a_2), a_3), \dots a_{n-1}), a_n) $$

最大。其中，$ f(x, y) = (x | y) - y $，$ | $ 表示按位或。

## 思路
如果你对二进制敏感的话就会发现：

**若 $ f(x, y) $ 的二进制中的某一位为 $1$，当且仅当对于 $x$ 和 $y$ 的二进制位，$x$ 的这一位是 $1$，而 $y$ 的这一位为 $0$。**

~也可以打表找到这个结论。~

这意味着，排列的第一个元素对结果的影响最大。

为了使最终结果最大，应该将具有最高有效位的元素放在最前面。

通过按位或运算的性质，我们可以确定哪些元素的**最高有效位**对结果贡献最大。

具体细节看代码。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100005];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	// 找到具有最高有效位的元素
	for (int bit = 30; bit >= 0; --bit) {
		int cnt = 0;
		int candidate = -1;
		for (int i = 0; i < n; ++i) {
			if ((a[i] >> bit) & 1) {
				cnt++;
				candidate = i;
			}
		}
		if (cnt == 1) {
			swap(a[0], a[candidate]);
			break;
		}
	}
	// 输出结果
	for (int i = 0; i < n; ++i) {
		cout << a[i] << " ";
	}
	cout << '\n';
	return 0;
}
```
时间复杂度 $ \mathcal{O}(n) $，可以通过本题。

---

## 作者：Shaaaadow (赞：1)

萌新的第一篇题解qwq

我们先看题目哦

## 题目描述

定义一个函数 $\operatorname{f}(x,y)=(x|y)-y$。

给定一个长度为 $n$ 数列 $a$，定义 
$$\operatorname{f}(\operatorname{f}..\operatorname{f}(\operatorname{f}(a_1,a_2),a_3),...a_{n-1}),a_n)$$

为这个数列的值。

现在，请你将数列改变一种顺序，使得最后的值最大。
输出你改变后的数列。

translate by @[ShineEternal](https://www.luogu.com.cn/user/45475)。

## 题解

这题打眼一看，好嘛，又是烦人的位运算。该咋整呢？

看看样例先。

### 样例

#### 输入1

```
4
4 0 11 6
```

#### 输出1

```
11 6 4 0
```

### 分析

既然是位运算，我们就把这些烦人的数字变成二进制再来看吧～

输入为： `100 0 1011 110`

如果我们直接对这个序列进行操作会变成什么样呢？

$$
\begin{aligned}
f(100, 0) &= (100 | 0) - 0 &=& 100 - 0 &=& 100\\
f(100, 1011) &= (100 | 1011) - 1011 &=& 1111 - 1011 &=& 100\\
f(100, 110) &= (100 | 110) - 110 &=& 110 - 110 &=& 0
\end{aligned}
$$

最后的结果是 `0`。

那对输出的结果进行操作会怎么样呢？

$$
\begin{aligned}
f(1011, 110) &= (1011 | 110) - 110 &=& 1111 - 110 &=& 1001\\
f(1001, 100) &= (1001 | 100) - 100 &=& 1101 - 100 &=& 1001\\
f(1001, 0) &= (1001 | 0) - 0 &=& 1001 - 0 &=& 1001
\end{aligned}
$$

我们可以发现！其实这个 `f(x,y)` 就是把 `x` 的二进制里面，抠掉 `y` 的二进制！

比如，`f(11,6) => f(1011,110)`，从 `1011` 里面抠掉一个 `110` ，最后就得到了 `1001`！

其实 `f(x,y)` 就相当于 `x & ~y`，当然这都是后话了。

---

好了，函数的本质了解了，那么对整个序列的操作其实也就是

$$
\operatorname{f}(\operatorname{f}..\operatorname{f}(\operatorname{f}(a_1,a_2),a_3),...a_{n-1}),a_n) = \operatorname{f}(a_1,(a_2|a_3|\dots|a_n))
$$

即从第一个数字的二进制中抠掉后面所有数字的二进制。

也容易得知，最后的结果跟 除第一个数字外 其它数字的顺序是无关的。

那么，我们只需要让第一个数字最大（**含有最高二进制位的**）就好了嘛？

（其实这样子是不对的

如果样例是 `2 4 5` 呢？

把 `5` 放到前面的话，

`f(f(5,2),4)->f(f(101,10),100)=f(101,100)=1`

但是最大值其实是

`f(f(2,4),5)->f(f(10,100),101)=f(10,101)=10`

为什么，为什么会变成这样子呢？

因为`4`和`5`有共同的最高位啊！这个最高位会被抠掉的啊！

那么该怎么办呢？

答案是：让**含有最高且唯一的二进制位**的数字到最前面就好啦。

上代码。

### 代码

```cpp
#include <iostream>
#include <algorithm>
const int maxn = 1e+5 + 5;

int main()
{
	int n, a[maxn];
	std::cin >> n;
	for (int i=0; i<n; i++) std::cin >> a[i];
	for (int i=30; i>=0; i--)	// 从第31位开始向下搜索
	{
		int t = 1 << i, count = 0, idx=0;
		for (int j=0; j<n; j++)
			if (a[j] & t)	// 判断数字是否含有这一位
			{
				idx = j;
				count++;	// 统计含有该位的数字个数
			}
		if (count == 1)		// 如果只有一个，跟第一个数字交换，break
		{
			std::swap(a[0], a[idx]);
			break;
		}
	}
	std::cout << a[0];
	for (int i=1; i<n; i++) std::cout << ' ' << a[i];
	return 0;
}
```

就酱啦～

---

## 作者：fighter (赞：1)

分析一下题目中的柿子，可以发现$f(a,b)$就是要把在a,b中同时为1的位变成0。

那么不难想到，如果我们确定了序列的第一个数，后面的顺序并不影响答案。并且我们可以把后面所有的数字先or起来，最后再和第一个数字做一遍$f$。

所以我们只要枚举序列的第一个数，然后通过预处理前后缀or，算出其他数的or，然后计算并更新答案。

```cpp
#include <bits/stdc++.h>
#define MAX 500005
#define ll long long
using namespace std;
 
int n;
ll a[MAX], l[MAX], r[MAX];
 
int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++){
        scanf("%lld", &a[i]);
        l[i] = l[i-1]|a[i];
    }
    for(int i = n; i >= 1; i--){
        r[i] = r[i+1]|a[i];
    }
    int ans = -1, p = 0;
    for(int i = 1; i <= n; i++){
        ll x = l[i-1]|r[i+1];
        if((a[i]|x)-x > ans){
            ans = (a[i]|x)-x;
            p = i;
        }
    }
    cout << a[p] << " ";
    for(int i = 1; i <= n; i++){
        if(i != p) printf("%lld ", a[i]);
    }
 
    return 0;
}
```

---

## 作者：Frictional (赞：0)

## 题意
定义新运算 $x\ominus y=(x\operatorname{or}y)-y$，给定一个长度为 $n$ 的序列 $a$。可以更改序列 $a$ 的顺序，使得 $a_1\ominus a_2 \ominus \ldots \ominus a_{n-1}\ominus a_n$ 的值最大
## 思考
我们先来对这个运算找找规律，只看两个数之间的这个运算。

首先，我们知道 $x\operatorname{or}y$ 中某一位只要有一个数的这一位为 1，那么 $x|y$ 后这一位也为 1。我们可以分几种情况讨论下
1. 当 $x$ 为 $1$，$y$ 为 $1$ 时，则 $x\ominus y=0$。因为这时 $x\operatorname{or}y=1$,所以 $(x\operatorname{or}y)-y=1-1=0$。
2. 当 $x$ 为 $0$，$y$ 为 $1$ 时，则 $x\ominus y=0$。因为这时 $x\operatorname{or}y=1$,所以 $(x\operatorname{or}y)-y=1-1=0$。
3. 当 $x$ 为 $1$,$y$ 为 $0$ 时，则 $x\ominus y=1$。因为这时 $x\operatorname{or}y=1$,所以 $(x\operatorname{or}y)-y=1-0=1$。
4. 当 $x$ 为 $0$,$y$ 为 $0$ 时，则 $x\ominus y=1$。因为这时 $x\operatorname{or}y=0$,所以 $(x\operatorname{or}y)-y=0-0=0$。

总结一下就会发现两条规律。
```
1.当 y 的这一位为 1 时，那运算的结果这一位为0

2.当 y 的这一位为 0 时，那运算的结果这一位为 x 的这一位的值
```
这说明如果在我们运算的序列中，这一位为 $1$ 的数超过 $1$ 个，那么运算完后这一位就一定是 $0$ 了。反之，如果没有超过 $1$ 个，而且第一个运算的数的这一位为 $1$，那么运算结果的这一位一定为 $1$。所以我们只要找到序列中只有一个为 $1$ 且位数最高的那个数为运算的第一个数，其他的数随便排列就可以了。

## AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define FOR(a,b,c) for(int a=b;a<=c;a++)
#define ROF(a,b,c) for(int a=b;a>=c;a--)
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define debug(x) cerr<<#x<<'='<<x<<endl
int rd(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' or ch>'9'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0' && ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x*f;
}
const int N=1e5+5;
int n;
int a[N];
struct node{
    int cnt,x;
}bit[35];
int tmp;
int cnt,top;
int ans=1;
signed main(){
    n=rd();
    FOR(i,1,n){
        a[i]=rd();
        tmp=a[i];
        cnt=0;
        while(tmp){
            if(tmp%2){
                if(!bit[cnt].x) bit[cnt].x=i;
                bit[cnt].cnt++;
            }
            tmp>>=1;
            cnt++;
        }
        top=MAX(top,cnt);
    }
    FOR(i,0,top+1){
        if(bit[i].cnt==1){
            ans=bit[i].x;
        }
    }    
    cout<<a[ans]<<" ";
    FOR(i,1,n){
        if(i==ans) continue;
        cout<<a[i]<<" ";
    }
    return 0;
}
```
jk:wq

---

## 作者：World_Creater (赞：0)

首先我们将 $f(x,y)$ 简写为 $x\oplus y$。  
我们将这个运算的常量表写出来：  

|$x$|$y$|$x \oplus y$| 
|--|--|--|
|$0$|$0$|$0$|
|$0$|$1$|$0$|
|$1$|$0$|$1$|
|$1$|$1$|$0$|

我们发现，当且仅当 $x=1,y=0$ 时，当前一位才为 $1$。  
从这里我们也可以得到很显然的性质：如果 $x$ 已经为 $0$，那么无论后续 $y$ 如何取值，$x\oplus y$ 都只能是 $0$。  
把这个性质从 $2$ 个变量扩大到 $n$ 个变量，显然，**如果当前那一位上 $1$ 的个数，恰好只有一个**，那么这一位是 $1$，且只有那一位上 $1$ 的那一个数在最前面的时候。  
于是我们就得到了贪心思路：从高到低位枚举，如果当前那位只有一个 $1$，就把这个数提到最前方，否则直接跳过这一位。  
复杂度 $O(n\log w)$，$w$ 是值域。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200005],p[65],ans[200005],l,vis[200005];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	memset(p,-1,sizeof(p));
	for(int w=63;w>=0;w--)
	{
		int f=1;
		for(int i=1;i<=n;i++)
		{
			if(!vis[i]&&(a[i]&(1LL<<w)))
			{
				if(p[w]!=-1)
				{
					f=0;
					break;
				}
				p[w]=i;
			}
		}
		if(f==1&&p[w]!=-1)
		{
			ans[++l]=a[p[w]];
			vis[p[w]]=1;
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(!vis[i])
		ans[++l]=a[i];
	}
	for(int i=1;i<=n;i++)
	{
		cout<<ans[i]<<" ";
	}
}
```

---

## 作者：qjyzLfy (赞：0)

### 思路

进入二进制模式

先看看 $f(x,y)$ 怎么算:

- 1|1-1=0;
- 1|0-0=0;
- 0|1-1=0;
- 0|0-0=0;

于是我们知道 $f(x,y)$ 运算没有进位和借位,而且 x 的作用是积极的,y 的作用是消极的,类似减法.

更具体的理解 : 若 x 某一位上为 1 ,那么若 y 在同以为上为 1 ,该为被消为 0,否则保持 1;若 x 某一位上为 0 ,那么结果依然为 0.

好吧其实 $f(x,y)$ $=$ $x&(~y)$,但这种理解更形象(雾

而题目要求的运算是:寻找一个 $a_{1}$ ,然后用其它所有数来消它.显然对于 $a_{1}$ 中某一位上的 1,只要其它数中某个数同一位上也有 1,这一位都会消为 0.因此直接用其它数的**或和**来当 y 算一次就可以了.

然后要枚举哪个数作 $a_{1}$ ,为了方便地求出其它数的或和,可以对 $a_{1}$ 两边的数各用一个前缀和.(右边是不是应该叫后缀和?)

### 代码
```cpp
    #include <cstdio>
    #include <algorithm>
    #define LL long long
    using namespace std;
     
    const LL nma=111005;
    LL n;
    LL arr[nma];
    LL le[nma],ri[nma];
    LL i,j;
    LL sco,aanti,scoma,pma;
     
    int main()
    {
    	scanf("%lld",&n);
    	for(i=1;i<=n;i++){
    		scanf("%lld",&arr[i]);
    		le[i]=le[i-1]|arr[i];
    	}
    	for(i=n;i>0;i--){
    		ri[i]=ri[i+1]|arr[i];
    	}
    	for(i=1;i<=n;i++){
    		aanti=ri[i+1]|le[i-1];
    		sco=(arr[i]|aanti)-aanti;
    		if(sco>scoma){
    			scoma=sco;
    			pma=i;
    		}
    	}
    	if(pma==0)	pma=1;//以防谁开头结果都是 0.
    	printf("%lld ",arr[pma]);
    	for(i=1;i<=n;i++){
    		if(i!=pma)	printf("%lld ",arr[i]);
    	}
    	return 0;
    }
```

---

## 作者：Meatherm (赞：0)

观察到 $f(f(f(a_1,a_2),a_3)a_4,...)$ 与 $a_2,a_3,a_4,...$ 的顺序无关。

以及一个很显然的性质：答案的某一位是 $1$ 当且仅当 $a_1$ 的这一位是 $1$ 且之后的所有数这一位上都是 $0$。

考虑枚举 $a_1$，然后根据上面的性质计算答案即可。

```cpp
# include <bits/stdc++.h>
# define rr register
# define int long long
const int N=100010,INF=0x3f3f3f3f;
int a[N];
int ve[N];
int n;
inline int read(void){
	int res,f=1;
	char c;
	while((c=getchar())<'0'||c>'9')
		if(c=='-')f=-1;
	res=c-48;
	while((c=getchar())>='0'&&c<='9')
		res=res*10+c-48;
	return res*f;
}

signed main(void){
	n=read();
	for(rr int i=1;i<=n;++i){
		a[i]=read();
		for(rr int j=35;j>=1;--j){
			if(a[i]&(1<<(j-1))){
				++ve[j];// 存储每一位上 1 的数量
			}
		}
	}
	int maxx=-1e9,id=-1;//找 a1
	for(rr int i=1;i<=n;++i){
		int ans=0;
		for(rr int j=35;j>=1;--j){
			if((a[i]&(1<<(j-1)))&&ve[j]==1){// 如果这一位上是 1 并且这一位上只有一个 1
				ans=ans|(1<<(j-1));
			}
		}
		if(ans>maxx){
			maxx=ans;
			id=i;
		}
	}
	printf("%I64d ",a[id]);
	for(rr int i=1;i<=n;++i){// a1 确定后其它数的顺序无所谓 直接按照顺序输出即可
		if(id!=i)
			printf("%I64d ",a[i]);
	}
	return 0;
}

```

---

## 作者：ShineEternal (赞：0)

[更佳的阅读效果](https://blog.csdn.net/kkkksc03/article/details/104245002)


## description：

- 定义一个函数 $\operatorname{f}(x,y)=\operatorname{f}(x|y)-y$。

- 给定一个长度为 $n$ 数列 $a$，定义 
$$\operatorname{f}(\operatorname{f}..\operatorname{f}(\operatorname{f}(a_1,a_2),a_3),...a_{n-1}),a_n)$$

为这个数列的值。

- 现在，请你将数列改变一种顺序，使得最后的值最大。

- 输出你改变后的数列。

- $n\le 10^5$。

- translate by @[ShineEternal](https://www.luogu.com.cn/user/45475)。

## solution：

这题我们发现只有某一位只有一个 $1$ 时才对答案有贡献。

所以枚举每一位每个数，每次把符合条件的数字提到前面即可（其他随便排）。

时间复杂度：$O(32\times n)$ ?

## code:
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int a[200005],b[200005];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(int i=32;i>=1;i--)
	{
		int tag=0,tmp;
		for(int j=1;j<=n;j++)
		{
			if((a[j]>>(i-1))&1==1&&b[j]==0)
			{
				tmp=j;
				if(tag==1)
				{
					tag=0;
					break;
				}
				tag=1;
			}
		}
		if(tag==1)
		{
			printf("%d ",a[tmp]);
			b[tmp]=1;
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(b[i]==0)
		{
			printf("%d ",a[i]);
		}
	}
	printf("\n");
	return 0;
} 
```


---

