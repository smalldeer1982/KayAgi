# Palindromic Numbers 

## 题目描述

#### 题目大意

每天散步时，艾琳娜都会注意到地上有一个很长的数字（一个 $n$ 位数）。现在艾琳娜想找一个不含前导 $0$ 的 $n$ 位数，使得这两个 $n$ 位数的和是一个回文数。

数据保证一定有一个 $n$ 位数符合要求。如果有多个 $n$ 位数符合要求，任意输出其中的一个即可。

（回文数：如果一个数字从右往左读和从左往右读得到的数相同，那么它就被称为回文数。例如，数字121、66、98989是回文数，103、239、1241不是回文数。）

## 样例 #1

### 输入

```
3
2
99
4
1023
3
385```

### 输出

```
32
8646
604```

# 题解

## 作者：Phartial (赞：5)

## 题意简述

给你一个 $n$ 位数 $a$，你需要找到另一个 $n$ 位数 $b$，使得 $a+b$ 是一个回文数。

## 思路

下面假设 $n=3$，$n\ne3$ 时同理。

显然当 $a<900$ 的时候，$a+b=999$ 是一组合法的方案。

考虑 $a\ge 900$ 时，我们发现只有当 $a+b-900<1000$（$a+b$ 减去最小的 $a$ 不能超过 $n$ 位数）且 $a+b-999\ge100$（$a+b$ 减去最大的 $a$ 不能不到 $n$ 位数），随便移个项就能得到 $1099\le a+b<1900$，在这个范围里随便拎个回文数出来（我选的是 $1111$）就行了。

最后写个高精减就行了。

## 代码

```cpp
#include <iostream>

using namespace std;

const int kN = 1e5 + 2;

int t, n, a[kN], b[kN], c[kN];

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = n - 1; i >= 0; --i) {
      char c;
      cin >> c;
      a[i] = c - '0';
    }
    if (a[n - 1] == 9) {              // a >= 900
      for (int i = 0; i <= n; ++i) {  // 1111 即可
        b[i] = 1;
      }
    } else {                         // a < 900
      for (int i = 0; i < n; ++i) {  // 999 即可
        b[i] = 9;
      }
    }
    for (int i = 0; i < n; ++i) {  // 高精减
      if (b[i] < a[i]) {
        --b[i + 1], b[i] += 10;
      }
      c[i] = b[i] - a[i];
    }
    for (int i = n - 1; i >= 0; --i) {  // 输出
      cout << c[i];
    }
    cout << '\n';
  }
  return 0;
}
```

---

## 作者：Galois_Field_1048576 (赞：2)

一个比较容易想到的回文数是 $10^n-1=\begin{matrix}\underbrace{9\dots9}\\n\end{matrix}$，但是当数字首位为 $9$ 时就退化为 $\lt n$ 位数。于是考虑 $\dfrac{10^{n+1}-1}9=\begin{matrix}\underbrace{1\dots1}\\n+1\end{matrix}$，发现在最大数据 $10^n-1$ 下有 $\dfrac{10^{n+1}-1}9 - (10^n-1) = \dfrac{10^{n+1}+8}9$，为 $n$ 位数，表现良好。由于需要高精度，所以使用 Python。  
```python
for i in range(int(input())):
    l = int(input())
    n = int(input())
    if str(n)[0] == '9':
        print((10**(l+1)-1)//9-n)
    else:
        print((10**l-1)-n)
```

### update log
7.1 修改了一处大意造成的错误（$\dfrac{10^{n+1}-1}9 - (10^n-1)$ 而非 $\dfrac{10^{n+1}-1}9 - 10^n - 1$）。

---

## 作者：happy_dengziyue (赞：2)

### 1 视频题解

![](bilibili:BV1Fv4y137u9)

### 2 思路

我们可以分两种方式。

如果给出的数字的第一位数不是 $9$，就可以构造一个数字使得两者相加为 $\begin{matrix}\underbrace{999\cdots999}\\n\end{matrix}$，即为 $n$ 个 $9$；

否则构造 $11\begin{matrix}\underbrace{000\cdots000}\\n-3\end{matrix}11$。

用高精度减法即可。

### 3 代码与记录

```cpp
//Luogu submission 2
#include<cstdio>
#include<cstring>
using namespace std;
#define max_n 100000
int t;
int n;
char a[max_n+2];
char b[max_n+2];
bool fl;
char ans[max_n+2];
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1700B_1.in","r",stdin);
	freopen("CF1700B_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d%s",&n,a+1);
		if(a[1]=='9'){//第1个是9
			//选择1+(n-1)*0+1模式
			if(n==1){
				printf("2\n");
				continue;
			}
			if(n==2){
				if(a[2]>='2')printf("1%d\n",11-(a[2]-'0'));
				else printf("1%d\n",1-(a[2]-'0'));
				continue;
			}
			for(int i=0;i<=n;++i)b[i]='0';
			b[0]=b[1]=b[n-1]=b[n]='1';
			for(int i=n;i>=1;--i){
				if(b[i]<a[i]){
					b[i]+=10;
					--b[i-1];
				}
				ans[i]=b[i]-a[i];
			}
			for(int i=1;i<=n;++i)printf("%d",ans[i]);printf("\n");
		}
		else{
			for(int i=1;i<=n;++i)printf("%d",'9'-a[i]);
			printf("\n");
		}
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/77692731)

By **dengziyue**

---

## 作者：庄nnnn额 (赞：0)

### 题意简述
给出一个 $n$ 位数 $a$，请输出另一个没有前导 $0$ 的 $n$ 位数 $b$**（注意都是 $n$ 位数）**，使 $a+b$ 是一个**回文数**。多组数据。$2\leq n\leq 100000$。
### 解题思路
我们可以设定一个 $n$ 位或 $n+1$ 位回文数，用它减去 $a$，然后输出。**但是**，我们找不到任何一个 $n$ 位或 $n+1$ 位数，使它与任何 $n$ 位数的差都是没有前导 $0$ 的 $n$ 位数（不信自己试试）。所以，对于不同大小的数要**分别考虑**。

我考虑了两种情况：
1. $a<9\times 10^n$（$a$ 的第一位小于 $9$）：设定回文数为  $\begin{matrix}\underbrace{99\dots\dots 9}\\n\colorbox{White}{个}9\end{matrix}$；
2. $a\geq 9\times 10^n$（$a$ 的第一位等于 $9$）：设定回文数为 $\begin{matrix}11\underbrace{00\dots\dots 00}11\\n-3\colorbox{White}{个}0\end{matrix}$（$n=2$ 时为 $111$，$n=3$ 时为 $1111$）。

还有，因为 $2\leq n\leq 100000$，$a$ 会爆`unsigned long long`，所以得用高精。

代码就不放了，自己打吧。

---

## 作者：cyrxdzj (赞：0)

### 一、思路

如果输入的 $n$ 位数字的最高位不是 $9$，那么我们可以认为这个数字加上答案的和是 $99…99$（共有 $n$ 个 $9$），然后分别计算答案的每一位即可。显然，此时答案的最高位不为零，并且计算起来也非常方便，因为输入数字的每一位都不可能大于 $9$（废话，这是十进制诶）。

否则，我们可以认为这个数字加上答案的和是 $11…11$（共有 $n+1$ 个 $1$），然后进行竖式高精度运算即可。

### 二、代码

```cpp
#include<cstdio>
using namespace std;
int t;
int n;
char a[100005],b[100005];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%s",&n,a+1);
		if(a[1]!='9')//当最高位不为九
		{
			for(int i=1;i<=n;i++)//每一位分别计算
			{
				printf("%d",(9-(a[i]-'0')));
			}
			printf("\n");
		}
		else
		{
			for(int i=0;i<=n;i++)//填充被减数
			{
				b[i]='1';
			}
			for(int i=n;i>=1;i--)
			{
				if(b[i]<'0')//被减数的某一位小于零或小于减数的某一位，则借位
				{
					b[i]+=10;
					b[i-1]-=1;
				}
				if(b[i]<a[i])
				{
					b[i]+=10;
					b[i-1]-=1;
				}
				b[i]=b[i]-a[i]+'0';//计算
			}
			for(int i=1;i<=n;i++)//输出
			{
				printf("%c",b[i]);
			}
			printf("\n");
		}
	}
	return 0;
}

```


---

## 作者：jia_shengyuan (赞：0)

题意：$t(1\le t\le100)$ 次给你一个 $n(2\le n\le 100000)$ 位正整数 $a$，求任意一个 $n$ 位正整数 $b$，使得 $a+b$ 回文。

显然，我们应该规定一些总能保证有合法 $b$ 的回文数作为 $a+b$。比较容易想到的有 $10^n-1$（也就是 $n$ 个 $9$）。但不难发现这个数仅在 $a$ 最高位不为 $9$ 时合法，因为最高位是 $9$ 的时候 $b$ 的位数将小于 $n$。因此我们需要考虑另一个回文数在最高位是 $9$ 时备用。

因为要对于所有最高位为 $9$ 的数，都有 $b$ 的位数为 $n$，故这个 $a+b$ 不能小于 $10^n-1+10^{n-1}$（$10^n-1$ 是最大的 $n$ 位数，$10^{n-1}$ 是最小的 $n$ 位数），所以我们不妨把他设为 $(n+1)$ 个 $1$，这样把它减去 $n$ 就解决了。

因为要高精度，所以直接上 Python。

```python
t = int(input())

for _ in range(t):
    len = int(input())
    s = input()
    x = int(s)
    if s[0] == "9"[0]:
        n = int("1"*(len+1))
        print(n-x)
    else:
        n = int("9"*len)
        print(n-x)
```


---

## 作者：CodeMao (赞：0)

### 简化题意：

给定一个 $n$ 位数 $a$，寻找另一个 $n$ 位数 $b$，使得 $a+b$ 是一个回文数（正、反读起来都一样的数）。

### 主要思路：

简单构造，分两种情况：（以下 $99......9$ 均为 $n$ 个 $9$，$11......1$ 均为 $n+1$ 个 $1$）

- $a$ 的首位不是 $9$。此时我们很容易可以想到一个构造：$a+b=99......9$，此时 $b=99......9$ $-a$，直接高精减即可，不用考虑借位，因为 $a$ 的每一个数位最高也只能是 $9$，不可能达到 $10$。
  
- $a$ 的首位是 $9$。此时因为要求 $b$ 也是 $n$ 位数，所以不能再选择 $a+b=99......9$ 这种构造方法，如果这样构造的话 $b$ 的首位就一定为 $0$，则 $b$ 就不是 $n$ 位数了，不符合题意；此时可以选择 $a+b=11......1$ 这种构造方式，此时 $b=99......9-a$，直接用高精减，需要考虑退位情况。
  

这道题的主要算法就是**构造法**和**高精度减法**，不会高精度减发的盆友们戳这里：[高精度减法](https://blog.csdn.net/c20190413/article/details/72966835)

直接使用字符串处理即可。

代码（已`AC`）:

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 100005
#define ll long long 
int t,n;
char a[N],b[N];
int main(){
	//freopen("G:\\C\\in.in","r",stdin);
	//freopen("G:\\C\\out.out","w",stdout);
	scanf("%d",&t);
	while(t--){
		scanf("%d\n",&n);
		scanf("%s",a+1);
        memset(b,0,sizeof(b));
		if(a[1]!='9')
			for(int i=1;i<=n;++i) b[i]='9'-a[i]+'0';
		else{
            memset(b,49,sizeof(b));
			for(int i=n;i;--i){
				if(b[i]<'0') b[i]+=10,b[i-1]--;
				if(b[i]<a[i]) b[i]+=10,b[i-1]--;
				b[i]=b[i]-a[i]+'0';
			}
        }
		for(int i=1;i<=n;++i) putchar(b[i]);
		puts("");
	}
	return 0;
}
```

---

