# Serval and The Formula

## 题目描述

给定两个正整数 $x$ 和 $y$（$1 \le x, y \le 10^9$）。

请找到一个非负整数 $k \le 10^{18}$，使得等式 $(x + k) + (y + k) = (x + k) \oplus (y + k)$ 成立$^{\text{∗}}$，或判断这样的整数不存在。

$^{\text{∗}}$符号 $\oplus$ 表示[按位异或运算](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。


## 说明/提示

第一个测试案例中，由于 $(2 + 0) + (5 + 0) = (2 + 0) \oplus (5 + 0) = 7$，因此 $k = 0$ 是合法答案。注意 $k = 4$ 也是一个合法答案，因为 $(2 + 4) + (5 + 4) = (2 + 4) \oplus (5 + 4) = 15$。

第二个测试案例中，$(x + k) \oplus (y + k) = (6 + k) \oplus (6 + k) = 0$。然而对于所有 $k \ge 0$，$(x + k) + (y + k) > 0$ 恒成立，因此这样的整数 $k$ 不存在。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
2 5
6 6
19 10
1024 4096
1198372 599188```

### 输出

```
0
-1
1
1024
28```

# 题解

## 作者：ZMQ_Ink6556 (赞：8)

## 题解：CF2085C Serval and The Formula

### 题意简述

您将获得两个正整数 $x$ 和 $y(1 \le x , y \le 10^9)$。

找到一个非负整数 $k \le 10^{18}$，使得 $(x + k) +(y + k) =(x + k) \operatorname{xor} (y + k)$ 成立，或者确定这样的整数不存在。

### 解题思路

题意可以转化为找到一个 $k$，使得 $(x + k) \operatorname{and} (y + k) = 0$。

首先提出 $2$ 个操作：

- 若能够找到一个 $k_1 > 0$，使得 $\lfloor \frac{x}{2^{k_1}} \rfloor \bmod 2 = 1$ 且 $\lfloor \frac{y}{2^{k_1}} \rfloor \bmod 2 = 1$，那么找到最大的 $k_2 > 0$，使得 $\lfloor \frac{x}{2^{k_2}} \rfloor \bmod 2 \neq \lfloor \frac{x}{2^{k_2}} \rfloor \bmod 2$，然后一直加上去，使得 $\lfloor \frac{x}{2^{k_1}} \rfloor \bmod 2 \neq \lfloor \frac{x}{2^{k_1}} \rfloor \bmod 2$。
- 若找不到 $k_2$，则让 $x$ 和 $y$ 就从 $k_1$ 一直往上加，直到找到一个不相同的二进制位。

观察发现，若 $x \neq y$，则对于任意 $k_1$，两种操作必有至少一个能够执行。

所以只有在 $x = y$ 时才无解。

剩下的模拟即可。

对于有解的情况，输出还有更简单的方法，即找到一个 $n$ 使得 $\max(x , y) \le 2^n \le 10^{18}$，输出 $2^n - \max(x , y)$（参见[官方题解](https://codeforces.com/blog/entry/140933)）。

### 参考代码

为方法 $1$ 的实现。

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
long long t , x , y , k , bk;
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t--)
	{
		cin >> x >> y;
		k = 0;
		if(x == y)
		{
			cout << "-1\n";
			continue;
		}
		for(long long tmp = 1 ; tmp <= 2000000000000000018ll ; tmp *= 2)
		{
			if(x / tmp % 2 && y / tmp % 2)
			{
				bk = tmp;
				while(x / tmp % 2 == y / tmp % 2)
				{
					tmp /= 2;
					if(tmp == 0)
					{
						tmp = bk;
						break;
					}
				}
				k += tmp;
				x += tmp;
				y += tmp;
			}
		}
		cout << k << '\n';
	}
	return 0;
}
```

---

## 作者：copper_ingot (赞：6)

[洛谷](http://luogu.com.cn/problem/CF2085C)

[CF](https://codeforces.com/problemset/problem/2085/C)

我们发现，如果正整数 $a$ 是 $2$ 的非负整数次方，那么对于任意一个小于 $a$ 的非负整数 $b$ 都满足 $a+b=a\oplus b$。

简单的证明：设 $a$ 在二进制下有 $m$ 位，那么 $a$ 的最高位为 $1$，其余位为 $0$。因为 $b<a$，所以 $b$ 的位数一定比 $a$ 少，于是 $a$ 和 $b$ 之间没有一位是同为 $1$ 的，所以 $a+b=a\oplus b$。

我们假设 $x>y$，那么我们找到一个最小的 $n$ 使得 $n$ 是 $2$ 的非负整数次方且 $n\ge x$，则 $k=n-x$，此时 $y+k<n$，满足上面的条件，因此输出 $n-x$ 即可。

还有，当 $x=y$ 时无论如何都没法满足条件，此时输出 $-1$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int T, x, y, n;
signed main(){
	scanf("%lld", &T);
	while (T--){
		scanf("%lld%lld", &x, &y);
		if (x == y){puts("-1"); continue;}
		x = max(x, y), n = 1;
		while (n < x) n *= 2;
		printf("%lld\n", n - x);
	}
	return 0;
}
```

---

## 作者：Magallan_forever (赞：1)

#### 简要说明题意：

已知 $x,y$，求 $k$ 使得 $(x+k)+(y+k) = (x+k) \space \textrm{xor} \space (y+k)$，如果不存在输出 $-1$。

#### 题目分析：

众所周知 $a+b=2(a \space \textrm{bitand} \space b)+a \space \textrm{xor} \space b$，那么只需要找到 $k$ 满足 $(x+k) \space \textrm{bitand} \space (y+k)=0$，就能让条件成立。也就是说，$x+k$ 和 $y+k$ 的任意二进制位不能同时为1。所以输出 $-1$ 的条件就是 $x=y$。

考虑到 $k$ 可以大于 $x,y$，那么直接从低位开始扫，两数的某位如果同时为 $1$，就把大的那个加进位。这个过程可以迭代，可以解决问题。

代码如下：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int main(){
    int T;
    long long x,y,t,temp,cnt,k;
    scanf("%d",&T);
    while(T--){
        scanf("%lld%lld",&x,&y),k=0ll,t=(x&y);
        if(x==y){
            printf("-1\n");
            continue;
        }
        while(t){
            temp=(t&(-t)),temp=(temp<<1)-1;
            cnt=min(((x&temp)^temp)+1,((y&temp)^temp)+1);//计算要加到进位差多少，可能有更简单的表达方式？
            k+=cnt,x+=cnt,y+=cnt;
            t=(x&y);
        }
        printf("%lld\n",k);
    }
    return 0;
}
/*
1
3 7
*/
```

---

