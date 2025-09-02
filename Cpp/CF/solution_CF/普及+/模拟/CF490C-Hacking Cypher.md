# Hacking Cypher

## 题目描述

Polycarpus participates in a competition for hacking into a new secure messenger. He's almost won.

Having carefully studied the interaction protocol, Polycarpus came to the conclusion that the secret key can be obtained if he properly cuts the public key of the application into two parts. The public key is a long integer which may consist of even a million digits!

Polycarpus needs to find such a way to cut the public key into two nonempty parts, that the first (left) part is divisible by $ a $ as a separate number, and the second (right) part is divisible by $ b $ as a separate number. Both parts should be positive integers that have no leading zeros. Polycarpus knows values $ a $ and $ b $ .

Help Polycarpus and find any suitable method to cut the public key.

## 样例 #1

### 输入

```
116401024
97 1024
```

### 输出

```
YES
11640
1024
```

## 样例 #2

### 输入

```
284254589153928171911281811000
1009 1000
```

### 输出

```
YES
2842545891539
28171911281811000
```

## 样例 #3

### 输入

```
120
12 1
```

### 输出

```
NO
```

# 题解

## 作者：wxzzzz (赞：3)

### 题意

给定一个正整数 $s$，问是否可以把它分成两段：$x,y$，使得 $x \bmod a=0,y \bmod b=0$。

### 思路

设 $na_i$ 为以 $i$ 结尾的 $x$，$nb_i$ 为以 $i$ 结尾的 $y$。

有：

$$na_i=na_{i-1}×10+s_i$$

$$nb_i=nb_{i+1}+s_i×10^{n-i}$$

然后枚举断点，如果满足 $na_i \bmod a=0$ 并且 $nb_{i+1} \bmod b=0$ 这就是一个合法断点。

但是这样显然会爆 int。

可以发现，将每个 $na_i,nb_i$ 对 $a,b$ 取模，对答案没有影响，并且可以用 int 存下。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int a, b, n, p = 1, pos, na[1000005], nb[1000005];
char s[1000005];
int moda(int x) {
    return (x % a + a * 2) % a;
}
int modb(int x) {
    return (x % b + b * 2) % b;
}
int main() {
    scanf("%s", s + 1), n = strlen(s + 1);
    cin >> a >> b;

    for (int i = 1; i <= n; i++)
        na[i] = moda(moda(na[i - 1] * 10) + s[i] - '0');

    for (int i = n; i >= 1; i--) {
        nb[i] = modb(nb[i + 1] + modb(p * (s[i] - '0')));
        p = modb(p * 10);
    }

    for (int i = 1; i < n; i++)
        if (s[i + 1] != '0' && !na[i] && !nb[i + 1]) {
            pos = i;
            break;
        }

    if (!pos) {
        puts("NO");
        return 0;
    }

    puts("YES");

    for (int i = 1; i <= pos; i++)
        cout << s[i];

    cout << '\n';

    for (int i = pos + 1; i <= n; i++)
        cout << s[i];

    return 0;
}
```

---

## 作者：CSP_Sept (赞：3)

为什么在洛谷搜 $\text{interactive}$ 会搜出来这题啊 /fad

### Description

给定一个长度不超过 $10^6$ 的数，问能否把它分割成**没有前缀 0** 的两部分，使得两部分分别能被 $a,b$ 整除。

### Solution

做法很简单，维护前 $i$ 位构成的数对 $a$ 取模的结果，后 $n-i+1$ 位对 $b$ 取模的结果。

这里分别用 $x_i,y_i$ 表示。

容易得到递推式：

$$
\begin{matrix}
x_i=(10x_{i-1}+d_i)\bmod a\\
y_i=(y_{i+1}+10^{n-i}d_i)\bmod b
\end{matrix}
$$

然后扫一遍，每次判断是否有 $x_i=y_i=0$ 即可，注意特判前缀 0。

### Code

```cpp
#include <cstdio>
#include <cstring>

#define N 1000010
using namespace std;
int n, a, b;
int d[N];
char s[N];
int x[N], y[N];
int main(){
	scanf("%s", s + 1);
	scanf("%d%d", &a, &b);
	n = strlen(s + 1);
	for(int i = 1 ; i <= n ; i++){
		d[i] = s[i] - '0';
		x[i] = (x[i - 1] * 10 % a + d[i]) % a;
	}
	int base = 1;
	for(int i = n ; i > 1 ; i--){
		y[i] = (y[i + 1] + base * d[i] % b) % b;
		base *= 10;
		base %= b;
		if(d[i] == 0) continue;
		if(x[i - 1] == 0 && y[i] == 0){
			puts("YES");
			for(int j = 1 ; j <= i - 1 ; j++)
				printf("%d", d[j]);
			puts("");
			for(int j = i ; j <= n ; j++)
				printf("%d", d[j]);
			puts("");
			return 0;
		}
	}
	puts("NO");
	return 0;
}
```

---

## 作者：kimi0705 (赞：0)

# 思路
用 $x_i$ 表示前 $i$ 个数构成的数模 $a$ 的结果；用 $y_i$ 表示 $i\sim n$ 构成的数模 $b$ 的结果。

$$x_i = (10x_{i-1} + ch_{i}) \bmod a$$
$$y_i = (10^{n-i}ch_i +y_{i}) \bmod b$$

对于 $y_i$ 来说，$10^{n-i}$ 太大了！！

所以要对式子进一步修改:

$$y_i = (10^{n-i}ch_i +y_{i}) \bmod b = ((10^{n-i}\mod b)ch_i +y_{i})$$

这样就不会爆 `int` 了。

# Code

~~禁止抄袭~~
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 10;
char ch[N];
int n, x, y, temp = 1;
int a[N], b[N];
signed main() {
    scanf("%s", ch + 1); 
    cin >> x >> y;
    if(ch[1] == '0') {
        cout << "NO\n";
        return 0;
    }
    n = strlen(ch + 1);
    for (int i = 1; i <= n; i++) a[i] = (a[i - 1] * 10 + ch[i] - '0') % x;
    for (int i = n; i >= 1; i--) b[i] = (b[i + 1] + temp * (ch[i] - '0')) % y,temp = temp * 10 % y;
    for (int i = 1; i < n; i++)
        if (a[i] == 0 && b[i + 1] == 0 && ch[i + 1] != '0') {
            cout << "YES\n";
            for (int j = 1; j <= i; j++) cout << ch[j];
            cout << endl;
            for (int j = i + 1; j <= n; j++) cout << ch[j];
            return 0;
        }
    cout << "NO\n";
    return QWQ;
}
```

---

## 作者：FutaRimeWoawaSete (赞：0)

题意：一个超长整数问你是否可以割成两部分使得前一段是 $a$ 的倍数，后一段是 $b$ 的倍数。              

转化题意，就是选定一个位置 $i$ 使得 $1 \sim i$ 数字组成的数和 $i + 1 \sim n$ 数字组成的数和是否能 $\mod a$ 和 $\mod b$ 能为 $0$ 。              

考虑直接预处理两个数组 $pre_i$ 和 $suf_i$ 表示 $1 \sim i$ 的数字组成的数 $\mod a$ 的值和 $i \sim n$ 的数字组成的数 $\mod b$ 的值。               

然后再扫一遍就可以 $O(n)$ 判了。         

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 1e6 + 5;
int n,m,pre[Len],suf[Len],a,b,p;
char s[Len];
int main()
{
	scanf("%s",s + 1);
	n = strlen(s + 1);
	scanf("%d %d",&a,&b);
	for(int i = 1 ; i <= n ; i ++) pre[i] = pre[i - 1] * 10 % a + (s[i] - '0') , pre[i] %= a;
	p = 1;bool flag = true;
	for(int i = n ; i >= 1 ; i --) 
	{
		flag = flag && (s[i] == '0');
		suf[i] = suf[i + 1] + p * (s[i] - '0') % b , suf[i] %= b;
		p = p * 10 % b;
		if(i != 1 && pre[i - 1] == 0 && suf[i] == 0 && !flag) 
		{
			puts("YES");
			for(int j = 1 ; j < i ; j ++) putchar(s[j]);
			puts("");
			for(int j = i ; j <= n ; j ++) putchar(s[j]);
			return 0;
		}
	}
	puts("NO");
 
	return 0;
}
```

---

