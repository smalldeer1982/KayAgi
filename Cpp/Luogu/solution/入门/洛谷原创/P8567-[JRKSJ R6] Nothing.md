# [JRKSJ R6] Nothing

## 题目背景

【此处应有图】

## 题目描述

我们定义 $f(x)$ 表示 $x$ 在 $2$ 进制下最低的 $1$ 的位置（你需要注意，二进制下的最低位是第 $0 $ 位）。以下是其在 `C++` 语言中的代码（未考虑数据类型造成的问题）：

```c++
int f(int x){
	int ans = 0;
	while (x % 2 == 0){
		x /= 2;
		ans += 1;
	}
	return ans;
}
```

共有 $T$ 组询问，每组询问给定区间 $[l,r]$，求有多少个 $i\in [l,r]$ 使得 $f(i)< f(i+1)$。

## 说明/提示

### 数据规模
本题采用捆绑测试。

| $\text{Subtask}$ | $T\le$ | 特殊限制 | $\text{Score}$ |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $10^5$ | $l=r$ | $10$ |
| $2$ | $10^4$ | $r-l\le10^3$ | $30$ |
| $3$ | $10^5$ | $r\le10^6$ | $20$ |
| $4$ | $10^5$ | 无 | $40$ |

对于 $100\%$ 的数据，$1\le T\le 10^5$，$1\le l\le r\le 10^{18}$。

## 样例 #1

### 输入

```
2
3 5
15 20```

### 输出

```
2
3```

# 题解

## 作者：aimcf (赞：12)

这一篇题解的目标：让初学 OI 的蒟蒻也能理解这道题，并且拿到 $100$ 分的好成绩。

## $\texttt{Part 0:}$ $f$ 函数的含义

```cpp
int f(int x){
	int ans = 0;
	while (x % 2 == 0){
		x /= 2;
		ans += 1;
	}
	return ans;
}
```

进一步分析这个函数：

这是一个循环，当 $x\bmod 2 = 0$，也就是当 $x$ 是奇数的时候，停止循环并且返回计数器，否则进入循环，计数器自增 $1$，并且让 $x$ 除以 $2$。

蒟蒻：咦？这是什么？

那么这样解释：

将一个数 $x$ 转换成二进制，求 $x$ 的末尾有多少个连续的 $0$。

如果一个数 $x=11$，那么 $x$ 的二进制是 $(1011)_2$，容易发现末尾没有 $0$，也就是说，$f(11)=0$。

如果一个数 $x=12$，那么 $x$ 的二进制是 $(1100)_2$，容易发现末尾有两个 $0$。也就是说，$f(12)=2$。

由于 `x /= 2` 这一句话可以看做 `x >>= 1`，也就是将二进制右移一位。所以这个程序就是求解二进制的末尾有多少个连续的 $0$ 的。

进一步理解，`x >>= 1` 可以看做 `x /= 2`，那么求二进制的末尾有多少个连续的 $0$，就可以看做是求 $x$ 里面有多少个因子 $2$。

## $\texttt{Part 1: Subtask \#1}$ 

在这一个 `Subtask` 里，$l=r$。也就是说，我们有一些不同的方法：

方法 $1$：直接判断 $f(l)$ 和 $f(l+1)$ 的大小。但是有一点麻烦，并且时间复杂度较高，是 $O(T\log x)$ 的。

方法 $2$：考虑 $f$ 函数的性质。

容易发现，如果 $x$ 是一个奇数，那么 $f(x)=0$。

原因：奇数没有因子 $2$。

同理，偶数有因子 $2$。所以 $f(x+1) > 0$。

因此，当 $l$ 为奇数的时候，$f(l) < f(l+1)$，否则，$f(l) > f(l+1)$。

由于奇数和奇数，偶数和偶数不会连续，所以没有 $f(l) = f(l+1)$ 的情况。

那么这一个 `Subtask` 可以在 $O(T)$ 的时间复杂度内完成。

## $\texttt{Part 2: Subtask \#2}$ 

在这一个 `Subtask` 里，$r-l \le 10^3$，所以可以用 `Subtask #1` 的性质进行枚举。时间复杂度 $O(T\times (r-l))$。可以通过。

## $\texttt{Part 3: Subtask \#3}$

在这一个 `Subtask` 里，$l\le r\le 10^6$。直接暴力枚举显然超时。

考虑使用前缀和进行优化。

蒟蒻：前缀和是什么？

假设有一个 $a$ 数列，那么考虑创建一个 $b$ 序列，满足 $b_i = b_i-1 + a_i$ 并且 $b_i = 0$，那么 $b$ 序列就是 $a$ 序列的前缀和序列。

区间求和问题：假设要求 $[l,r]$ 的和。

那么可以使用容斥原理。

$b_r$ 为 $[1,r]$ 区间的和，$b_{l-1}$ 为 $[1,l-1]$ 区间的和，那么 $b_r - b_{l-1}$ 的值就是 $[l,r]$ 区间的和。

时间复杂度 $O(1)$。[模板题](https://www.luogu.com.cn/problem/B3612)。

考虑进行预处理。

容易发现，$b_r = b_{r-1} + g(r)$，其中 $g(r)$ 判断的是 $r$ 是否为奇数。

然后询问区间 $[l,r]$ 只需要询问 $b_r - b_{l-1}$ 的值即可。

## $\texttt{Part 4: Subtask \#4}$

$1\le l,r\le 10^{18}$，那么无法进行 $O(n)$ 的前缀和。

然后就需要使用性质。

+ 奇数和偶数是交替的。
+ 如果 $f(x) < f(x+1)$，那么一定有 $f(x + 1) > f(x + 2) < f(x + 3)$。

考虑特殊情况：$l=r$ 直接使用 `Subtask #1` 的性质，$l+1 = r$ 进行特殊判断。

然后考虑 $l\bmod 2 = 0$，$r\bmod 2 = 0$ 的特殊情况。

容易发现，$l$ 和 $r$ 此时都不满足 $f(x) < f(x+1)$ 的特殊性质。

那么这个时候直接使用公式 $\lfloor\frac{r-l}{2}\rfloor$ 即可算出答案。

那如果 $l\bmod 2 = 1$，$r\bmod 2 = 1$ 怎么办？

那么将 $l$ 进行右移一直到满足 $l\bmod 2 = 0$，并且答案 $+1$。

$r$ 同理，进行左移一直到满足 $r\bmod 2 = 0$，并且答案 $+1$。

实际上只需要进行 `if` 判断即可。这个地方一开始想复杂了，使用了 `while` 循环。

然后就可以在 $O(T)$ 的时间复杂度内通过这道题了！

超级大常数代码：

```cpp
// 跑了 163ms
// 常数巨大
// 模拟赛因为常数 100->90 可以AFO了
#include <bits/stdc++.h>
#define int long long

using namespace std;

signed main()
{
	int T;
	cin >> T;
	while (T --)
	{
		int l, r;
		cin >> l >> r;
		if (l == r)
			cout << l % 2 << '\n';
		else
		{
		    int ans = 0;
		    while (l % 2)
		    {
		        ans ++;
		        l ++;
		    }
		    while (r % 2)
		    {
		        ans ++;
		        r --;
		    }
		    if (l > r)
		        cout << ans << '\n';
		    else
		    {
		        ans += (r - l) / 2;
		        cout << ans << '\n';
		    }
		}
	}
	return 0;
}

```

注意点：不要忘记开 `long long`！十年 OI 一场空，不开 `long long` 见祖宗。


---

## 作者：zhangyuanxiao (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/P8567)
## 题意
- 定义 $f(x)$ 表示 $x$ 在 $2$ 进制下最低的 $1$ 的位置（**从第 $0$ 位开始**）。  
- $T$ 组询问，每组询问给定区间 $[l,r]$，求有多少个 $i\in [l,r]$ 使 $f(i)< f(i+1)$。
- $1\le T\le 10^5$，$1\le l\le r\le 10^{18}$。

## 题目分析
对 $i\in [l,r]$，且 $f(i)< f(i+1)$，说明 $i$ 在 $2$ 进制下最低的 $1$ 的位置比 $i+1$ 在 $2$ 进制下最低的 $1$ 的位置要低。因此 $i+1$ 必定在 $2$ 进制下产生了进位，又因为只加了 $1$，所以只能在第 $0$ 位产生进位，因此 i 的第 $0$ 位为 $1$，$i$ 为奇数。所以我们只需要求出区间 $[l,r]$ 有多少个**奇数**即可。

### 如何求奇数个数？
记区间长度为 $a$，$a=r-l+1$。若 $a$ 为奇数：

- $l$ 为奇数时，奇数比偶数多一个，奇数个数为 $\left\lfloor\dfrac{a}{2}\right\rfloor+1$。

- $l$ 为偶数时，偶数比奇数多一个，奇数个数为 $\left\lfloor\dfrac{a}{2}\right\rfloor$。

$a$ 为偶数时，奇数和偶数个数相等，为 $\dfrac{a}{2}$。

#### 主要代码
```cpp
long long a=r-l+1;//记得开long long
cout<<((a%2==1)?a/2+l%2:a/2)<<'\n';
```

---

## 作者：Limitless_lmw (赞：7)

$\Large{\text{Introduction}}$

设 $f(x)=\text{lowbit(x)}$

求在 $x\in [l,r]$ 下，满足 $f(x)<f(x+1)$ 的 $x$ 数量。

$\Large{\text{Solution}}$

显然，对于一个非负整数，若这个数为奇数，则它的二进制表示中第 $0$ 位为 $1$；若这个数为偶数，则它的二进制表示中第 $0$ 为 $1$。

并且，我们可以发现题面中有这样一句话:

$$1\le l \le r \le 10^{18}$$

就可以排除 $0$ 的存在，那么一个偶数最低位的 $1$ 所在位置一定是大于这个数 $+1$ 最低位的 $1$ 所在位置的。

那么，$f(x)<f(x+1)$ 的必须条件为 $x\,\bmod 2=1$

现在这个问题就转化为了

>
> 求 $[l,r]$ 中，有多少个奇数？
>

显然，$O(n)$、$O(\log n)$、$O(\sqrt n)$、$O(\log \log n)$ 等许许多多甚至时间上更优的算法都是不行的，我们需要 $O(1)$ 的解决方法。

我们设 $lmw(x)$ 为区间 $[0,x]$ 中的奇数数量。

我们把 $lmw(x)$ 分两种情况讨论：

$$\begin{cases}
  x \bmod 2 = 0\\
  x \bmod 2 = 1
\end{cases}$$

对于第 $1$ 种情况，我们可以从 $0$ 开始，两个数分 $1$ 组，则有 $\dfrac{x}{2}$ 组，每组 $1$ 个奇数，则有 $\dfrac{x}{2}\times 1=\dfrac{x}{2}$ 个奇数。

对于第 $2$ 种情况，显然按第 $1$ 种情况的方法，会漏下 $1$ 个奇数，那么我们再增加一个偶数，求 $lmw(x+1)=\dfrac{x+1}{2}$ 就可以得到答案。 

现在我们需要考虑怎么整合：

首先，我们可以发现第 $2$ 种情况的答案和第 $1$ 种情况的答案只差 $\dfrac{1}{2}$，我们就可以把第 $1$ 种情况的公式修改为 $\lfloor\dfrac{x+1}{2}\rfloor$。又因为 C++ 的整除特性，我们在代码中只需要整合成 `cout<<(x+1)/2<<'\n'`。

现在我们该考虑怎么求 $[l,r]$ 区间中的奇数了。

用类似前缀和的思想，转化成求 $lmw(r)-lmw(l-1)$，套入公式，得：

$$ans=\lfloor\dfrac{r+1}{2}\rfloor-\lfloor\dfrac{l}{2}\rfloor$$

至此，我们顺利的切掉了 T1。~~也只能切掉 T1。~~

这些思路，赛时应该只要 $5$ 分钟吧。

$\Large{\text{End}}$

本篇博客就写到这里，如果读者有任何疑惑，请私聊 @[lmw_AK_noip](https://www.luogu.com.cn/user/547446) 或 @[lmw_Algorithm](https://www.luogu.com.cn/user/809765)

代码，没放就是没放。

自我嘲讽：

 _杀鸡焉用牛刀？_ 
 
 Update： 22/10/18 修复了一个问题

---

## 作者：Strelitzia_ (赞：3)

首先是几个显然的性质：

1. 偶数在二进制下最低位是 $0$，奇数在二进制下最低位是 $1$；
1. 如果 $x$ 为偶数，那么 $x+1$ 为奇数；
1. 如果 $x$ 为奇数，那么 $x+1$ 为偶数。

由性质 $1$ 可以看出对于任意的偶数 $x$ 与奇数 $y$，必有 $f(x)>f(y)$；

由性质 $2$ 与 $3$ 可以看出对于任意奇数 $x$，一定有 $f(x)<f(x+1)$。

所以，我们只需要求出给出的 $[l,r]$ 之间的奇数个数即可。首先我们求出区间长度再除以 $2$；若 $l$ 与 $r$ 都是奇数说明少算了一个，再加上。然后就可以通过本题了。代码如下：

```cpp
int Nothing(int l,int r){
	int ans=(r-l+1)/2;
	if(l%2==1&&r%2==1) ans++;
	return ans;
}
signed main(){
	int t=read();while(t--){
		int l=read(),r=read();
		printf("%lld\n",Nothing(l,r));
	}
	return 0;
}
```

---

## 作者：AKPC (赞：3)

好不容易抢到 rated 比赛第一题题解 QAQ。
### 思路
本蒟蒻开始图快，直接把函数复制粘贴，暴力判断，没想到后面两个数据点 TLE 了，只拿了 $40$。所以暴力不可行。

我们可以转换题目思路：你可以发现给出的函数的意思就是求出 $x$ 分解质因数后包含多少个 $2$。

题目要我们求有多少个 $i\in [l,r]$ 使得 $f(i)< f(i+1)$。我们回到自然数的范围，假设 $x$ 是一个奇数，那么分解质因数后不包含 $2$，所以 $f(x)=0$；加一后变成偶数，因子就有 $2$ 了。

所以经过推算，将题目概括为一句话就是：求 $[l,r]$ 有多少奇数。求区间奇数个数非常简单，所以在这里不再详细解释。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int query(int l,int r){  //求区间奇数个数
	if (l%2==0&&r%2==0) return (r-l)/2;
	else if (l%2!=0&&r%2!=0) return (r-l)/2+1;
	else return (r-l+1)/2;
}
int t,l,r;
signed main(){
	cin>>t;
	while (t--){
		cin>>l>>r;
		cout<<query(l,r)<<endl;
	}
	return 0;
}

```

---

## 作者：Night_sea_64 (赞：2)

整个比赛就这一道大水题，别的题都难到爆。

因为一个数二进制的最低位是这个数 $\bmod\text{ }2$ 的余数。很容易发现，当 $x$ 是奇数时，$f(x)=0$。而当 $x$ 是偶数时，$f(x)>0$。也就是当 $x$ 是奇数时，满足条件 $f(x)<f(x+1)$。是偶数则不满足条件。

于是这道题就转化成了求 $[l,r]$ 中的奇数个数。分类讨论，有下列 $4$ 种情况：

- 如果 $l$ 是奇数 $r$ 也是奇数，例如 $l=1,r=3$。则奇数个数就是 $\dfrac{r-l+2}{2}$。

- 如果 $l$ 是奇数 $r$ 是偶数，例如 $l=1,r=2$。则奇数个数就是 $\dfrac{r-l+1}{2}$。

- 如果 $l$ 是偶数 $r$ 是奇数，例如 $l=0,r=1$。则奇数个数就是 $\dfrac{r-l+1}{2}$。

- 如果 $l$ 是偶数 $r$ 是偶数，例如 $l=0,r=2$。则奇数个数就是 $\dfrac{r-l}{2}$。

于是这道题就解决了。AC 代码如下：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        long long l,r;
        scanf("%lld%lld",&l,&r);
        if(l%2==0)
        {
            if(r%2==0)printf("%lld\n",(r-l)/2);
            else printf("%lld\n",(r-l+1)/2);
        }
        else
        {
            if(r%2==0)printf("%lld\n",(r-l+1)/2);
            else printf("%lld\n",(r-l+2)/2);
        }
    }
    return 0;
}
```

---

## 作者：Epoch_L (赞：2)

## Solution
注意到奇数的函数值为 $0$，偶数的函数值 $\ge1$，而要满足条件的 $f(i)$ 和 $f(i+1)$ 中的 $i$ 和 $i+1$ 必为一奇一偶，根据最开始的推断，当且仅当 $i$ 为奇数时不等式成立，所以问题转化为 $[l,r]$ 中有几个奇数，直接手模几组样例，分情况讨论即可。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
void read(int &x)
{
	char ch=getchar();
	int r=0,w=1;
	while(!isdigit(ch))w=ch=='-'?-1:1,ch=getchar();
	while(isdigit(ch))r=(r<<3)+(r<<1)+(ch^48),ch=getchar();
	x=r*w;
}
void solve(){
	int x,y;
	read(x);read(y);
	if(x%2==0&&y%2==0)cout<<(y-x)/2<<endl;
	else cout<<(y-x)/2+1<<endl;
}
main()
{
	int T;
	read(T);
	while(T--)solve();
	return 0;
}
```

---

## 作者：wangif424 (赞：2)

~~图呢？~~

### 简要题意：
对于每次询问，求出 $[l,r]$ 中有多少个**奇数**。

### 思考：
为什么是奇数？由题意知 $f(x)$ 为 $x$ 在 $2$ 进制下，第一个 $1$ 的位置，因为对于任意一个奇数 $n$ 都有 $n\equiv1\pmod2$ ，即 $f(n)=0$。

同理，对于任意偶数 $n^{'}$ 都有 $f(n^{'})\ge1$。

所以，当 $i$ 为奇数时，$f(i)=0<1\le f(i+1)$，即所有的奇数都满足$f(i)<f(i+1)$。

### 完成代码：
由于通常情况下奇数和偶数的数量对半开，所以容易想到直接 ```cout << (l-r)/2;```。然后喜提 WA 声一片。

此时我们需要考虑 $l,r$ 的奇偶性：

- $l,r$ 一个为奇数，一个为偶数，此时 $\frac{l+r+1}{2}$ 为正确答案。

- $l,r$ 都为偶数，可以将 $r$ 减一，减去一个偶数，不会影响最终答案，转化成“一个为奇数，一个为偶数”的情况，即为 $\frac{(r-1)-l+1}{2}=\frac{r-l}{2}$。

- $l,r$ 都为奇数，可以将 $r$ 加一，增添一个偶数，不会影响答案，转化成“一个为奇数，一个为偶数”的情况，即为 $\frac{(r+1)-l+1}{2}=\frac{r-l+2}{2}$。

### AC代码：
~~正解的公式都给了，还要什么 AC 代码，自己写去。~~

---

## 作者：yuheng_wang080904 (赞：2)

## 思路

题意很清晰：若 $f(x)$ 表示 $x$ 在二进制下最低的 1 的位置，则共 $T$ 组询问，每次给定区间 $[l,r]$，求有多少 $i\in[l,r]$，满足 $f(i)<f(i+1)$。

这是一道简单的签到题。

很明显，我们知道奇数在二进制下最低的 1 就在它的最低位，而偶数则不是。因此当 $i\equiv1\pmod 2$ 时，原先在最低位，加一后变为高位，则有 $f(i)<f(i+1)$，反之则从高位变为最低位，有 $f(i)>f(i+1)$。

因此这道题就被转换成了输出区间内奇数的个数的问题了。很明显，我们可以将奇偶一一配对，然后答案就是对数，但由于是闭区间，因此如果两端都为奇结果还要加一。

## 代码
代码很简单，时间复杂度 $O(T)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
long long l,r;
int main(){
    cin>>t;
    while(t--){
        cin>>l>>r;
        cout<<(r-l+1)/2+(l%2==1&&r%2==1)<<endl;
    }
    return 0;
}
```


---

## 作者：JustinXiaoJunyang (赞：1)

思路分析：

这是一道数学题，我们可以先运行一下题目中给出的 $f(x)$ 函数。例如输入 $6$，函数的返回值是 $1$。但如果我们输入 $5$，它就会返回 $0$。

知道了 $f(x)$ 函数的机制，我们就要进行推导：

因为奇数在 $2$ 进制下的末位一定是 $1$。相反地，偶数在 $2$ 进制下的末位一定是 $0$。

也就是说，如果 $i$ 是奇数，它就符合题目中的 $f(i)<f(i+1)$。于是这道题就是让我们求 $[l,r]$ 中有多少个奇数。

最后提醒：十年 OI 一场空，不开 `long long` 见祖宗。当然，这里真心建议不要用 `#define int long long`。

参考代码：

```cpp
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        long long l, r;
        cin >> l >> r;
        if ((l % 2 && r % 2) || (l % 2 ^ r % 2)) cout << (r - l) / 2 + 1 << endl;
        else cout << (r - l) / 2 << endl;
    }
    return 0;
}
```

---

## 作者：快斗游鹿 (赞：1)

## 思路

若要使 $f(x)<f(x+1)$，显然仅当 $x$ 为奇数时才会成立。每次询问只需要统计 $l$ 到 $r$ 之间的奇数即可。

## 代码

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll t,l,r;
namespace IO{//by cyffff
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
int main(){
	scanf("%lld",&t);
	while(t--){
		l=read();r=read();
		if(l%2==0)l++;
		if(r%2==0)r--;
		printf("%lld\n",(r-l)/2+1);
	}
	return 0;
}

```


---

## 作者：sunkuangzheng (赞：1)

**【题目分析】**

首先看到 $10^{18}$ 的数据范围，再考虑到这是比赛的 A 题，就应该想到这是一个结论题。然后发现，对于任意一个奇数，$f(x) = 1$；对于任意一个偶数，$f(x) > 1$。所以不难发现：满足 $f(i) < f(i+1)$ 的数字都是奇数。因此，原题转化成求 $[l,r]$ 内奇数的数量。

然后进行分类讨论：

- 当 $l,r$ 都是偶数时，答案就是 $\dfrac{r-l}{2}$。
- 当 $l,r$ 一个奇数一个偶数时，答案是 $\dfrac{r-l}{2} + 1$。
- 当 $l,r$ 都是奇数时，答案也是 $\dfrac{r-l}{2} + 1$。

因此得到代码。

**【完整代码】**

为了简洁，代码中快读省略。
```cpp
#include <bits/stdc++.h>
using namespace std;
long long t,a,b;
int main(){
    t = read();
    while(t--){
    	a=read();b=read();
    	if(a%2==0 && b%2==0) cout << (b-a)/2 << "\n";
		else cout << (b-a)/2+1 << "\n"; 
	}
	return 0;
}
```

---

## 作者：Kreado (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P8567)

签到题。

#### 思路

因为 $f(x)$ 表示 $x$ 在二进制状态下最低位下 $1$ 的位置，即求 $x$ 能被多少个 $2$ 整除，所以 $f(x)<f(x+1)$ 当且仅当 $x$ 为奇数时，问题即转换成了区间 $[l,r]$ 内有多少个奇数，注意 $l$ 和 $r$ 要同奇偶性。 

#### 贴贴代码

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#define ll long long
ll T,l,r;
using namespace std;
int main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld",&l,&r);
		if(!(l&1)) l+=1;
		if(!(r&1)) r-=1;
		printf("%lld\n",(r-l)/2+1);
	}
	return 0;
}
```


---

## 作者：xhabc66 (赞：0)

# 思路
由于 $i$ 和 $i+1$ 必有一个为奇数，所以 $f(i)$ 和 $f(i+1)$ 之间必有一个为 $1$ 且另一个 $>1$。

而只有 $i$ 为奇数时，$f(i)=1$，所以原问题就变为：给定 $l$ 和 $r$，求 $l\sim r$ 间的**奇数个数**。

如果将一奇一偶分成一组，则分为三种情况：
1. $l$、$r$ 一奇一偶，这时便能分成 $\frac{r-l+1}{2}$ 组，答案即为 $\frac{r-l+1}{2}$。
2. $l$、$r$ 均为奇，这时便能分成 $\frac{r-(l+1)+1}{2}$ 组再加一个奇数，答案即为 $\frac{r-l}{2}+1$。
2. $l$、$r$ 均为偶，这时便能分成 $\frac{r-(l+1)+1}{2}$ 组再加一个偶数，答案即为 $\frac{r-l}{2}$。

每次判断的时间为 $O(1)$，总时间复杂度为 $O(T)$，可以通过。
# AC code
```cpp
#include<bits/stdc++.h> 
using namespace std;

int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		long long l,r;
		cin>>l>>r;
		if(l%2!=r%2)cout<<(r-l+1)/2<<endl;
		else if(l%2==1)cout<<(r-l)/2+1<<endl;
		else cout<<(r-l)/2<<endl;
	}
	return 0;
}
```

---

## 作者：Lvyuze (赞：0)

# 题意

给定 $T$ 组询问，每组询问给定一个区间，求有多少个 $i\in [l,r]$ 使得二进制下 $i$ 的 $1$ 的最低位小于二进制下 $i+1$ 的 $1$ 的最低位。

# 分析

一个正整数，不是奇数就是偶数，而奇数的二进制的 $1$ 的最低位是第 $0$ 位，比如 $101$，$1$，$111$ 等，他们的十进制都是奇数，因为 $2^0$ 等于 $1$，而高位上 $2$ 的幂之和都是偶数，加上 $1$ 必然是奇数。

偶数则反之，末尾必定是 $0$，只有这样才是偶数，二进制偶数 $1$ 的最低位是第 $1$ 位。

可以发现，二进制奇数 $1$ 的最低位要小于二进制偶数 $1$ 的最低位，这个问题就成了：给定区间 $[l,r]$，求这个区间内有多少个奇数。

如果 $l$ 和 $r$ 都是偶数，那么这个区间就有 $\dfrac{r-l}{2}$ 个奇数；否则有 $\dfrac{r-l}{2}+1$ 个奇数。

# 代码

还有个 long long 的问题。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n;
long long l,r;
signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        scanf("%lld%lld",&l,&r);
        if(l%2==0 && r%2==0) printf("%lld\n",(r-l)/2);
        else printf("%lld\n",(r-l)/2+1);
    }
    return 0;
}
```


---

## 作者：lrqlrq250 (赞：0)

## 解题思路
题目说的挺清楚的，题意就不复述了。

我们考虑任意一个数 $a$，显然如果 $a$ 是个偶数，那 $f(a)$ 一定是大于 $0$ 的（最低位是第 $0$ 位），因为偶数的最低位都是 $0$ 嘛。

那么考虑 $f(a + 1)$，那就一定是最低位是 $1$ 了，也就是 $f(a + 1) = 0$，这时候一定无法满足 $f(a) < f(a + 1)$。

如果 $a$ 是奇数呢？那 $f(a) = 0$ 就是显然的了。而不管 $a$ 的二进制末尾有多少个 $1$，$a + 1$ 造成进位，一定有 $f(a + 1) > 0$，因此恒满足 $f(a) < f(a + 1)$。

至此，我们的问题就变成了求给出区间中的奇数个数~~甚至连红题都算不上~~。

只需要考虑左右端点的奇偶就行了。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;


int main(){
	int t;
	long long l, r;
	scanf("%d", &t);
	while (t--){
		scanf("%lld%lld", &l, &r);
		if (l & 1 || r & 1) printf("%lld\n", (r - l) / 2 + 1);
		else printf("%lld\n", (r - l) / 2);
	}
	return 0;
}
```


---

## 作者：Failure_Terminator (赞：0)

## Solution

使用 $\operatorname{lowbit}$ 暴力只有 $40pts$，考虑以数学方式思考。

众所周知，相邻两数必然是一奇一偶。

那么我们可以将其分为两种情况：

- 奇数，最低位的 $1$ 在第 $0$ 位。

- 偶数，最低位的 $1$ 最低会在第 $1$ 位。

因此，当 $i$ 为奇数时， $i+1$ 为偶，$f(i)< f(i+1)$。

反之，$i$ 为偶数，$i+1$ 为奇数，$f(i) > f(i+1)$。

因此，这个问题可转化为：对于每个询问，求区间 $[l,r]$ 之间的奇数个数。

这样就做到了每个询问 $\Theta (1)$。

## AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define ri register int
using namespace std;
int count(int low,int high){
    if(low&1) return 1+(high-low)/2;
	if(high-low) return 1+(high-low-1)/2;
	return 0;
}
void solve(){
	int l,r;
	cin>>l>>r;
	cout<<count(l,r)<<endl;
}
signed main()
{
	int t;cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：ran_qwq (赞：0)

如果 $x$ 为奇数，则 $f(x)<f(x+1)$。

证明：因为 $x$ 为奇数，所以 $x$ 在二进制下第 $0$ 位为 $1$，即 $f(x)=0$。又因 $x+1$ 为偶数，所以 $x+1$ 第 $0$ 为为 $0$，即 $f(x+1)>0$。综上，当 $x$ 为奇数时，$f(x)<f(x+1)$。

所以 $[l,r]$ 中奇数的个数就是答案，设 $g(x)$ 为 $[1,x]$ 中奇数的个数，易得 $g(x)=\left\lfloor\dfrac{x+1}{2}\right\rfloor$。

根据容斥原理，$[l,r]$ 中奇数个数等于 $g(r)-g(l-1)$，所以答案就是 $\left\lfloor\dfrac{r+1}{2}\right\rfloor-\left\lfloor\dfrac{l}{2}\right\rfloor$。

提醒：十年 OI 一场空，不开 long long 见祖宗。

```cpp
#include<iostream>
using namespace std;
int T;
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--)
	{
		long long l,r;
		cin>>l>>r;
		cout<<(r+1)/2-l/2<<"\n";
	}
}
```


---

