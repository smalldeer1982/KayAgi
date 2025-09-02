# Garage

## 题目描述

Pak Chanek plans to build a garage. He wants the garage to consist of a square and a right triangle that are arranged like the following illustration.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1725G/7e485d3e8037daefec2b8ca00b8b11546f3e5f77.png)Define $ a $ and $ b $ as the lengths of two of the sides in the right triangle as shown in the illustration. An integer $ x $ is suitable if and only if we can construct a garage with assigning positive integer values for the lengths $ a $ and $ b $ ( $ a<b $ ) so that the area of the square at the bottom is exactly $ x $ . As a good friend of Pak Chanek, you are asked to help him find the $ N $ -th smallest suitable number.

## 说明/提示

The $ 3 $ -rd smallest suitable number is $ 7 $ . A square area of $ 7 $ can be obtained by assigning $ a=3 $ and $ b=4 $ .

## 样例 #1

### 输入

```
3```

### 输出

```
7```

# 题解

## 作者：sixrc (赞：4)

转化题意，就是求第 $n$ 个数 $c$ 使得它可以表示为 $b^2-a^2$ 的形式，其中 $a,b$ 为整数，且 $c>0$。

根据平方差公式，$b^2-a^2=(b-a)(b+a)$，所以我们只需要保证 $b-a$ 与 $b+a$ 同奇偶即可。

不难发现所有的奇数以及所有 $4$ 的倍数都满足条件。

但是我们不能选 $1,4$，原因显然，不存在满足题意的合法解。

然后这个数列写下来是有周期的，形如 $3,5,7,(8,9,11),(12,13,15),(16,17,19),...$

除去前三项，每相邻三项就是 $4k,4k+1,4k+3$。把前三项判掉即可 $O(1)$ 得出答案。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, m, s;
signed main(){
	scanf ("%lld", &n);
	if (n == 1) return puts ("3"), 0;
	else if (n == 2) return puts ("5"), 0;
	else if (n == 3) return puts ("7"), 0;
	n -= 4;
	m = n / 3;
	s = 4 + (m + 1) * 4;
	m = n % 3;
	if (m >= 1) s ++;
	if (m >= 2) s += 2;
	printf ("%lld\n", s);
	return 0;
}
```

---

## 作者：yan_jun (赞：3)

## 题目描述 ：求 $b^2-a^2$ 的第 $n$ 小值 $(b>a)$。


## 思路：
不妨先设 $b=a+1$ , 就可以得到 $ b^2-a^2=(a+1)^2-a^2=2a+1$。

因为 $a$ 与 $b$ 均 **大于 $0$**，所以所有大于 $1$ 的奇数全部合法。

再设 $b = a+1$,同上可以得到 $b^2-a^2=4a+4$。

所以，所有大于 $4$ 的且为 $4$ 的倍数的的数全部合法。

但是，当我们设 $b=a+3$ 与 $b=a+4$ $\dots$ 时发现得到的合法集合与以上是被包含关系。

我们将所有的数排个序就可以得到:

$3,5,7,8,9,11,12,13,15,16,17,19,\dots$

于是乎我们就已经找到了所有合法数据，但是要注意当 $n$ 小于 $4$ 时得到的三个答案与后方不成规律,所以输出需要特判一下。

而当 $n>3$ 时我们不难发现每三个数的规律为:

$$4x,4x+1,4x+3,4(x+1),4(x+1)+1,4(x+1)+3....$$

下面附上我简陋的代码：

```cpp
#include<bits/stdc++.h>
#define re register
#define ll long long
#define inl inline
using namespace std;
int read(){
	int sum=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
	while(isdigit(c)){sum=(sum<<3)+(sum<<1)+(c^48);c=getchar();}
	return sum*f;
}
inl void write(int x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
int main(){
	int n=read();
	if(n==1){puts("3");return 0;}
	if(n==2){puts("5");return 0;}
	if(n==3){puts("7");return 0;}
	n-=3;
	int cnt=n/3;
	cnt+=2;
	int tmp=n%3;
	if(tmp==1) cout<<cnt*4;
	if(tmp==2) cout<<cnt*4+1;
	if(tmp==0) cout<<(cnt-1)*4+3;
}
```


---

## 作者：undefined_Ryan (赞：3)

Codeforces 难度：`*1500`，偏水题，此题并不需要过多的分类讨论。

看到题面，首先勾股定理，得正方形面积为 $b^2-a^2$，且 $b>a>0$。

记 $b^2-a^2=k$，因为 $k=(b+a)(b-a)$ 而 $b+a$ 与 $b-a$ 同奇偶，$k\equiv2\pmod4$ 不可能成立。

1. 当 $k$ 为 $4$ 的倍数时，显然 $k=4$ 时不成立，否则设 $b=\frac k4+1,\ a=\frac k4-1$ 则 $b^2-a^2=\dfrac k2\times2=k$。
2. 当 $k$ 为奇数时，显然 $k=1$ 时不成立，否则设 $b=\frac{k+1}2,\ a=\frac{k-1}2$ 则 $b^2-a^2=k\times1=k$。

得到 $k$ 的所有可能值为除 $1$ 和 $4$ 以外的所有 $4$ 的倍数和奇数，即 `3 5 7 8 9 11 12 13...`。

除去 $3$ 和 $5$，剩下的数可以按照 $4t-1,\ 4t,\ 4t+1$ 的形式分组，对于任意 $n\ge3$，可得 $t=[\frac n3]+1$，第 $n$ 小的数为 $4t+(n\bmod3)-1$。

所求即为 $4\times[\frac n3]+(n\bmod3)+3=n+[\frac n3]+3$。

$n=2$ 时上述公式仍然成立，$n=1$ 时计算结果应从 $4$ 调整为 $3$。

最后附上完整代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int main() {
    cin>>n;
    cout<<n+n/3+3-(n==1)<<endl;
    return 0;
}
```

---

## 作者：cyhtxdy (赞：2)

这里对官方题解做一下翻译和补充。

首先，根据题目，设 $c$ 为三角形的一条直角边（不是 $a$）。根据勾股定理，$a^2+c^2=b^2$。那么下面这个正方形的面积就为 $b^2-a^2$。

考虑 $b=a+1$ 的情况，拆开完全平方得到： $b^2-a^2=(a+1)^2-a^2=a^2+1^2+2a-a^2=2a+1$。因为 $a$ 为正整数，那么这种情况时的答案就是**大于或等于 $3$ 的奇数**。

考虑 $b=a+2$ 的情况，同样拆开完全平方可以得到：
$b^2-a^2=(a+2)^2-a^2=a^2+2^2+2\times 2a-a^2=4a+4$。同样因为 $a$ 为正整数，那么这种情况时的答案就是**大于或等于 $8$ 的 $4$ 的倍数**。

在上面两种情况后，再考虑答案对 $4$ 取模余数为 $2$ 的情况。

这种答案不可能表示为 $b^2-a^2$，因为**完全平方数对 $4$ 取模的余数只可能为 $0$ 或 $1$**。（证明不赘述，读者若不懂可以看[此篇证明](https://baijiahao.baidu.com/s?id=1701320376037465539)。）
 
结合以上所有内容，可以得到：所有符合要求的答案都是**大于或等于 $3$ 的奇数**或**大于或等于 $8$ 的 $4$ 的倍数**。

为了找到第 $n$ 个符合要求的答案，可以在答案范围内进行二分查找，判断当前答案之前的符合要求的答案个数是否大于或等于 $n$，找到最小的答案即可。

设当前答案为 $x$，那么符合条件的个数为 $\frac{x-1}{2}+\max(\frac{x}{4}-1,0)$。

得到代码：
```
#include <bits/stdc++.h>

using namespace std;

#define int long long

signed main () {
	int n;
	cin >> n;
	int l = 1, r = 2e9, ans;
	while (l <= r) {
		int mid = l + r >> 1;
		if ((mid - 1) / 2 + max (mid / 4 - 1, 0ll) >= n) {
			ans = mid;
			r = mid - 1;
		}
		else {
			l = mid + 1;
		}
	}
	cout << ans;
	return 0;
}

```



---

## 作者：kaizel (赞：0)

设 $ c $ 为直角三角形的底边（即既不是 $ a $ 也不是 $ b $ 的边），由勾股定理可知，$ a^2 + c^2 = b^2 $，所以 $ c^2 = b^2 - a^2 $。我们可以知道底部正方形的面积是 $ c^2 $。所以一个整数当且仅当它对于某些正整数 $ a $ 和 $ b $（$ a < b $）可以表示为 $ b^2 - a^2 $ 是正确的。

考虑 $ b = a + 1 $ 的情况。所以 $ b^2 - a^2 = ( a + 1 )^2 - a^2 = a^2 + 2 \times a + 1 - a^2 = 2 \times a + 1 $。由于 $ a $ 必须是一个正整数，那么在这种情况下，所有可能的结果都是大于或等于 $ 3 $ 的奇数。

再来考虑 $ b = a + 2 $ 的情况。则 $ b^2 - a^2 = ( a + 2 )^2 - a^2 = a^2 + 4 \times a + 4 - a^2 = 4 \times a + 4 $。由于 $ a $ 必须是一个正整数，那么在这种情况下，所有可能的结果都是大于或等于 $ 8 $ 的 $ 4 $ 的倍数。

我们考虑一个整数，它除以 $ 4 $ 余数为 $ 2 $。我们可以得到这样一个整数永远不能表示为 $ b^2 - a^2 $。这是因为任何平方数除以 $ 4 $ 的余数一定是 $ 0 $ 或 $ 1 $。

使用简单的暴力，我们可以得到 $ 1 $ 和 $ 4 $ 不能表示为 $ b^2 - a^2 $。

利用以上所有信息，我们可以看到，所有合适的数字都是大于或等于 $ 3 $ 的奇数和大于或等于 $ 8 $ 的 $ 4 $ 的倍数的整数。

为了找到第 $ N $ 个最小的合适数，我们可以对一个值 $ d $ 进行二分搜索。在每次二分搜索的迭代中，我们检查是否至少有 $ N $ 个合适数小于或等于 $ d $。
或者，我们可以使用数学公式在 $ O(1) $ 时间复杂度中找到第 $ n $ 个最小的合适数。

时间复杂度：$ O( \log N) $ 或 $ O(1) $。

---

## 作者：__int127 (赞：0)

## CF1725G Garage 题解

[**题目传送门**](https://www.luogu.com.cn/problem/CF1725G)

### 题目大意

给定一个整数 $n$，求出第 $n$ 小的 $b^2-a^2$，$1\le a<b$，$1\le n\le10^9$。

### 思路

我们先列举一下 $b^2-a^2$ 的部分情况，得到以下数列：

$(3,5,7),(8,9,11),(12,13,15),(16,17,19),(20,21,23)\dots\dots$

以每个括号为一组，发现规律了吗？除去第一组，每一组的项分别为 $4k,4k+1,4k+3$（$2\le k$，$k$ 为组数），那么将第一组的数值特判，剩下的只要知道 $k$ 就可以求出答案，那如何知道 $k$ 呢？

我们可以发现，每一组的数字个数都为 $3$，但是这里不能直接将 $n\div3$ 得到 $k$，因为 $n$ 可能不是每组的最后一项，导致 $n$ 不是 $3$ 的倍数，得到错误结果。其实只需要判断三种情况，使得 $n$ 为每组的最后一项的位置，得到 $k$ 就可以了，那么三种情况和对应的求 $k$ 的公式如下：

$\begin{cases}
\text{if} & n \bmod 3=1 & k=(n+2)\div3 \\
\text{if} & n \bmod 3=2 & k=(n+1)\div3 \\
\text{if} & n \bmod 3=0 & k=n\div3
\end{cases}$

但如果你是大佬的话，$k$ 其实可以用一个公式解决，因为 $n$ 每次要加到每组的最后一项的位置，也就是说 $n$ 每次加的是 $3-n\bmod3$，但也有 $n$ 本身就是每组的最后一项的位置的情况，所以还要 $\bmod3$，所以，公式为 $k=(3-n\bmod3)\bmod3$，但没有上面的公式好理解，所以以下用的都是上面的公式。

这样就可以根据，$4k,4k+1,4k+3$，来求出答案，总公式如下：

$\begin{cases}
\text{if} & n \bmod 3=1 & (n + 2) \div 3 \times 4 \\
\text{if} & n \bmod 3=2 & (n + 1) \div 3 \times 4 + 1 \\
\text{if} & n \bmod 3=0 & n \div 3 \times 4 + 3
\end{cases}$

就可以用 $O(1)$ 的时间复杂度来完成此题。

### 代码+注释

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int main(){
	cin >> n;// 读入 n
	if (n == 1){
		cout << "3";
	} else if (n == 2){
		cout << "5";
	} else if (n == 3){
		cout << "7";
	// 以上为特判
	} else {
		n -= 3;
		if (n % 3 == 1){
			cout << (n + 2) / 3 * 4;
		} else if (n % 3 == 2){
			cout << (n + 1) / 3 * 4 + 1;
		} else {
			cout << n / 3 * 4 + 3;
		}
        // 以上为公式，『思路』中已给出
	}
	return 0;
}
```

### 最后

本题题解到此结束，希望大家能看懂、有思路。

---

## 作者：PigJokerYellow (赞：0)

# 思路

###  初一数学+小学数学

------------
由平方差公式：$b^2 - a^2 = (b - a)(b + a)$。

可以得到：任何奇数（ $1$ 除外），任何 $4$ 的倍数（ $4$ 除外）皆可成为上式的值。

理由：
$\because b^2 - a^2 = (b - a)(b + a)$。

$\therefore$（$\mathrm{i}$）当 $b$ 比 $a$ 大 $1$ 时（也可以想成一奇一偶）。

- 原式 $ = a + b = $ 一个奇数（自己去补小学数学）。  
- 但显然，$1$ 不可以成为上式的值。
        
        
 （$\mathrm{ii}$）$a,b$ 为两个奇数/两个偶数。
     		
- 原式=偶数 $\times$ 偶数。          
- $\because$ 最小的偶数是 $2$ （b比a大，所以不可能为0）。
- $\therefore$ 原式 $=(2 \times n)(2 \times m)=4(nm)$。
- 然而 $b \ne a$。
- $\therefore mn \ne 1 \times 1$。
- $\therefore mn \ne 1$。
- 因此得到上述结论。



------------
接下来，我们把所有满足 $b^2 - a^2$ 的数写下来。

- $3,5,7,8,9,11,12,13,15,16,17,19,20,21,23\cdots$

### 三个为一组，便会发现规律：

- $(3,5,7),(8,9,11),(12,13,15),(16,17,19),(20,21,23)\cdots$

除第一组外，其余每组都可以写成 $ 4 \times k,4 \times k+1,4 \times k+3 $ 的形式。

~~（变成小学周期问题了）~~。

于是去模拟这个过程。


------------

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;

long long n;
long long foo(long long num){
	if(num==1) return 3;
	if(num==2) return 5;
	if(num==3) return 7;
	//特判第一组 
	if((num-1)%3==0) return ((num-1)/3+1)*4;
	//如果num-1 mod 3为0 则它为一组的第一个，返回它的组别*4 
	if((num-1)%3==1) return ((num-1)/3+1)*4+1;
	// 如果num-1 mod 3为1 则它为一组的第二个，本组的第一个+1 
	return ((num-1)/3+1)*4+3;
	//否则为第三个，返回第一个+1 
}

int main(){
	cin>>n;
	cout<<foo(n);
	return 0;
}
```




---

## 作者：Wings_of_liberty (赞：0)

# 分析
首先我们能发现，这是一道找规律题。  
然后，我们主观判断一下，当两个数的差值越大，那么这两个数平方差也就越大，也就是说，两个数差值越大，这两个数的平方差越有可能被其他较小差值的一组数找到，比如说：差值为 $4$ 的一组数，平方差一定是 $8$ 的倍数；差值为 $2$ 的一组数，平方差一定是 $4$ 的倍数，很明显，差值为 $2$ 的包含了差值为 $4$ 的。

# 规律
根据我们刚才的猜测，我们从差值较小的数开始，我们设 $a=x$，$b=x+1$，那么 $b^2-a^2=2 \times x+1$，很明显，由于 $x>0$，这个式子可以表示除 $1$ 以外所有奇数。  
同理，设 $a=x$，$b=x+2$，那么 $b^2-a^2=4 \times x+4$，这个式子可以表示除了 $4$ 以外所有 $4$ 的倍数。  
接下来，当 $b=x+3$，或者 $b=x+4$ 时，都只能表示出已经被表示的数，所以说规律已经找到了。

# 证明
上面的方法也算是一个证明，但感觉不是非常严谨。  
顺着上面的思路，我们将所有的平方差可以表示成 $2 \times x+1$，$4 \times x+4$，$6 \times x+9$ 等形式，根据前两个式子，我们只需要证明所有不是 $4$ 的倍数的偶数表示不出来即可，这样的偶数可以被表示为 $4 \times n +2$，$n$ 为自然数，如果想要表示这样的数，$x$ 一定是偶数，我们用 $2 \times x$ 表示，也就是 $2 \times 2 \times x \times n+x^2$。  
即 $4 \times x \times n+x^2=4 \times n+2$，很明显这个式子无解，所以说上文结论是正确的。

# 实现
找完规律后，我们发现，除了 $3,5,7$ 几个之外，剩下的能够被表示出来的点其实就是排除了是偶数却不是 $4$ 的倍数的点，所以说，我们可以3个一组，如 $8,9,11$ 和 $12,13,14$ 这样求。

# 代码
```
#include <bits/stdc++.h>
using namespace std;
#define op(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
#define cl() fclose(stdin),fclose(stdout)
#define F(i,x,y) for(int i=(x);i<=(y);i++)
typedef long long ll;
int ans[5]={0,3,5,7};
int n;
inline void init(){
	scanf("%d",&n);
}
inline void work(){
	if(n<4){
		printf("%d",ans[n]);
		return;
	}
	int a=(n-3)/3+2;
	int b=(n-3)%3;
	if(b==1){
		printf("%d",a*4);
	}else if(b==2){
		printf("%d",a*4+1);
	}else{
		printf("%d",(a-1)*4+3);
	}
}
int main(){
//	op("");
	init();
	work();
//	cl();
	return 0;
}

```


---

