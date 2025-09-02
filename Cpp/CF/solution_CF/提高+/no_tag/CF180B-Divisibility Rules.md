# Divisibility Rules

## 题目描述

Vasya studies divisibility rules at school. Here are some of them:

- Divisibility by $ 2 $ . A number is divisible by $ 2 $ if and only if its last digit is divisible by $ 2 $ or in other words, is even.
- Divisibility by $ 3 $ . A number is divisible by $ 3 $ if and only if the sum of its digits is divisible by $ 3 $ .
- Divisibility by $ 4 $ . A number is divisible by $ 4 $ if and only if its last two digits form a number that is divisible by $ 4 $ .
- Divisibility by $ 5 $ . A number is divisible by $ 5 $ if and only if its last digit equals $ 5 $ or $ 0 $ .
- Divisibility by $ 6 $ . A number is divisible by $ 6 $ if and only if it is divisible by $ 2 $ and $ 3 $ simultaneously (that is, if the last digit is even and the sum of all digits is divisible by $ 3 $ ).
- Divisibility by $ 7 $ . Vasya doesn't know such divisibility rule.
- Divisibility by $ 8 $ . A number is divisible by $ 8 $ if and only if its last three digits form a number that is divisible by $ 8 $ .
- Divisibility by $ 9 $ . A number is divisible by $ 9 $ if and only if the sum of its digits is divisible by $ 9 $ .
- Divisibility by $ 10 $ . A number is divisible by $ 10 $ if and only if its last digit is a zero.
- Divisibility by $ 11 $ . A number is divisible by $ 11 $ if and only if the sum of digits on its odd positions either equals to the sum of digits on the even positions, or they differ in a number that is divisible by $ 11 $ .

Vasya got interested by the fact that some divisibility rules resemble each other. In fact, to check a number's divisibility by $ 2 $ , $ 4 $ , $ 5 $ , $ 8 $ and $ 10 $ it is enough to check fulfiling some condition for one or several last digits. Vasya calls such rules the  $ 2 $ -type rules.

If checking divisibility means finding a sum of digits and checking whether the sum is divisible by the given number, then Vasya calls this rule the  $ 3 $ -type rule (because it works for numbers $ 3 $ and $ 9 $ ).

If we need to find the difference between the sum of digits on odd and even positions and check whether the difference is divisible by the given divisor, this rule is called the  $ 11 $ -type rule (it works for number $ 11 $ ).

In some cases we should divide the divisor into several factors and check whether rules of different types ( $ 2 $ -type, $ 3 $ -type or $ 11 $ -type) work there. For example, for number $ 6 $ we check $ 2 $ -type and $ 3 $ -type rules, for number $ 66 $ we check all three types. Such mixed divisibility rules are called  $ 6 $ -type rules.

And finally, there are some numbers for which no rule works: neither $ 2 $ -type, nor $ 3 $ -type, nor $ 11 $ -type, nor $ 6 $ -type. The least such number is number $ 7 $ , so we'll say that in such cases the mysterious  $ 7 $ -type rule works, the one that Vasya hasn't discovered yet.

Vasya's dream is finding divisibility rules for all possible numbers. He isn't going to stop on the decimal numbers only. As there are quite many numbers, ha can't do it all by himself. Vasya asked you to write a program that determines the divisibility rule type in the $ b $ -based notation for the given divisor $ d $ .

## 说明/提示

The divisibility rule for number $ 3 $ in binary notation looks as follows: "A number is divisible by $ 3 $ if and only if the sum of its digits that occupy the even places differs from the sum of digits that occupy the odd places, in a number that is divisible by $ 3 $ ". That's an $ 11 $ -type rule. For example, $ 21_{10}=10101_{2} $ . For it the sum of digits on odd positions equals $ 1+1+1=3 $ , an on even positions — $ 0+0=0 $ . The rule works and the number is divisible by $ 3 $ .

In some notations a number can fit into the $ 3 $ -type rule and the $ 11 $ -type rule. In this case the correct answer is "3-type".

## 样例 #1

### 输入

```
10 10
```

### 输出

```
2-type
1
```

## 样例 #2

### 输入

```
2 3
```

### 输出

```
11-type
```

# 题解

## 作者：MyukiyoMekya (赞：5)

首先来判断 `2-type` ，等于就是问最小的 $x$ 使得 $d\times k_1=b^x\times k_2$ $(1\le k_2\le b,x>0)$，

如果存在这个 $x$，并且 $k_2=0$，说明可以通过 `2-type` ，并且最少需要最后 $x$ 位就可以了。

实现起来就是如果 $\gcd(b,d)>1$ ，那么就 $d\leftarrow \dfrac d{\gcd(b,d)}$，然后 $x\leftarrow x+1$，

最后 $d=1$ 那就说明 `2-type`，否则我们也不用还原这个 $d$ ，也不用清空 $x$ ，因为判 `6-type` 和其他要用。

首先我们可以把 $d$ 表示为 $\sum_{i=0}^na_ib^i$，`3-type` 的式子就是：
$$
\sum_{i=0}^na_ib^i-\sum_{i=0}^na_i=0 \pmod d
$$

$$
\sum_{i=1}^na_i(b^i-1)=0 \pmod d
$$

然后你会发现对于每个 $(b^i-1)$ 都能提一个 $(b-1)$ 因式出来，所以 `3-type` 的条件就是 $b-1$ 是 $d$ 的倍数，

注意，如果 $x>0$ `3-type` 不成立。

接下来是 `11-type`，我们如法炮制：（此处感谢 @[YanLei](https://www.luogu.com.cn/user/243760) 提醒，已改正）
$$
(a_0b^0+a_1b^1+a_2b^2+a_3b^3+\cdots) =0 \pmod d
$$

$$
(a_0-a_1+a_2-a_3+\cdots) =0 \pmod d
$$

上式减下式：
$$
a_1(b^1+1)+a_2(b^2-1)+a_3(b^3+1)+\cdots = 0 \pmod d
$$
发现 $(b^k- (-1)^k)$ 都能提一个 $(b+1)$ 因式出来，所以 `11-type` 的条件就是 $b+1$ 是 $d$ 的倍数，

注意，如果 $x>0$ `11-type` 也不成立。

然后就是 `6-type` ，显然只要 `2-type` 成立并且 `3或11-type` 成立就行了。

`3-type` 和 `11-type`   也可以推出 `6-type` ，只要 $b+1$ 和 $b-1$ 同时是 $d$ 的倍数就行了，那就是 $\operatorname {lcm}(b+1,b-1)$ 是 $d$ 的倍数。

否则就是 `7-type`。

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
template <class t> inline void read(t &s){s=0;
reg int f=1;reg char c=getchar();while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
while(isdigit(c))s=(s<<3)+(s<<1)+(c^48),c=getchar();s*=f;return;}
template<class t,class ...A> inline void read(t &x,A &...a){read(x);read(a...);}
inline int lcm(int a,int b){return a/std::__gcd(a,b)*b;}
signed main(void)
{
	int p,d,y;read(p,d),y=d;
	reg int cnt=0;
	while(std::__gcd(p,y)>1)++cnt,y/=std::__gcd(p,y);
	if(y==1)std::printf("2-type\n%d\n",cnt);
	else if(!(lcm(p+1,p-1)%y))
	{
		if(!cnt&&!((p-1)%y))std::puts("3-type");
		else if(!cnt&&!((p+1)%y))std::puts("11-type");
		else std::puts("6-type");
	}
	else std::puts("7-type");
	return 0;
}
```



---

