# Mathematical Circus

## 题目描述

A new entertainment has appeared in Buryatia — a mathematical circus! The magician shows two numbers to the audience — $ n $ and $ k $ , where $ n $ is even. Next, he takes all the integers from $ 1 $ to $ n $ , and splits them all into pairs $ (a, b) $ (each integer must be in exactly one pair) so that for each pair the integer $ (a + k) \cdot b $ is divisible by $ 4 $ (note that the order of the numbers in the pair matters), or reports that, unfortunately for viewers, such a split is impossible.

Burenka really likes such performances, so she asked her friend Tonya to be a magician, and also gave him the numbers $ n $ and $ k $ .

Tonya is a wolf, and as you know, wolves do not perform in the circus, even in a mathematical one. Therefore, he asks you to help him. Let him know if a suitable splitting into pairs is possible, and if possible, then tell it.

## 说明/提示

In the first test case, splitting into pairs $ (1, 2) $ and $ (3, 4) $ is suitable, same as splitting into $ (1, 4) $ and $ (3, 2) $ .

In the second test case, $ (1 + 0) \cdot 2 = 1 \cdot (2 + 0) = 2 $ is not divisible by $ 4 $ , so there is no partition.

## 样例 #1

### 输入

```
4
4 1
2 0
12 10
14 11```

### 输出

```
YES
1 2
3 4
NO
YES
3 4
7 8
11 12
2 1
6 5
10 9
YES
1 2
3 4
5 6
7 8
9 10
11 12
13 14```

# 题解

## 作者：WhiteSunFlower (赞：14)

[SunFlower是醉醉醉可爱的](https://www.luogu.com.cn/blog/guicai-qq-1443870605/)

这是一道数学题

观察式子的结构：$(a+k) \times b$ 。要求 $(a+k)\times b$ 是 $4$ 的倍数，通过数学的思想将式子拆开,我们得出：

要使 $(a+k) \times b$ 是 $4$ 的倍数 ，那么将会满足以下条件之一：

>一、 $(a+k)$ 和 $b$ 都是偶数

>二、 $b$ 是 $4$ 的倍数

>三、 $(a+k)$ 是 $4$ 的倍数

我们依次考虑

一：

因为 $n$ 是偶数，那么 $1$ $\sim$ $n$ 有 $n/2$ 个数是偶数，即有 $n/2$ 个数可以作为 $b$ ，且对于每一个 $b$ 都有一个奇数 $a$ 与其对应，我们知道奇数加奇数得到偶数，所以 $k$ 必然为奇数。

所以 $k$ 为奇数时满足条件一，从 $1$ $\sim$ $n$ 输出一遍就好。

```cpp
if(k%2==1){
	puts("YES");
	for(int i=1;i<=n;i+=2){
		cout << i << " " << i+1 << "\n";
	}
}
```

二：

因为 $k$ 为奇数时直接选择方案一，现在考虑 $k$ 为偶数的情况。已知 $1$ $\sim$ $n$ 只有 $n/4$ 个 $b$ 满足条件，每个 $b$ 可以分配一个奇数，仍剩余 $n-(n/4)\times 2$ 个数，考虑**方案二结合方案三**：$(a+k)$ 为 $4$ 的倍数就必为偶数，即 $a$ ，$k$ 同为偶数，$a$ 不是 $4$ 的倍数，就要求 $k$ 也不是 $4$ 的倍数，答案显现！

```cpp
if(k%2==0&&k%4!=0){
	puts("YES");
	int j=1;//顺序输出奇数
	for(int i=1;i*4<=n;i++){
		cout << j << " " << i*4 << "\n";//方案二
		j+=2;
	}
	for(int i=1;i*4-2<=n;i++){
		cout << i*4-2 << " " << j << "\n";//方案三
		j+=2;
	}
}else{
	puts("NO");
}
```

### $AC$ $Code:$

```cpp
#include<bits/stdc++.h>
#define WhiteSunflower int main()//防伪标识
using namespace std;
int t,n,k;
WhiteSunflower{
	cin >> t;
	while(t--){
		cin >> n >> k;
		if(k%2==1){
			puts("YES");
			for(int i=1;i<=n;i+=2){
				cout << i << " " << i+1 << "\n";
			}
		}else if(k%2==0&&k%4!=0){
			puts("YES");
			int j=1;
			for(int i=1;i*4<=n;i++){
				cout << j << " " << i*4 << "\n";
				j+=2;
			}
			for(int i=1;i*4-2<=n;i++){
				cout << i*4-2 << " " << j << "\n";
				j+=2;
			}
		}else {
			puts("NO");
		}
	}
	return 0;
}
```

###### 搞定，掰掰~

---

## 作者：weizhiyonghu (赞：7)

## B Mathematical Circus Solution

### 思路

#### 判断是否有解

可以发现，除了 $4 \mid k$ 无解，其余情况均有解。

​	$k \equiv 1 \pmod 4: $ 此时只要让 $a$ 为奇数， $b$ 为偶数即可。

​	$k \equiv 2 \pmod 4:$ 此时，让 $a,b$ 奇偶性不一致：

​		若偶数那个不能被 $4$ 整除，那只可能是除 $4$ 余 $2$ ，那让这个偶数加上 $k$ 再乘上奇数即可。换种方法来说就是使 $a \equiv 2 \pmod 4,2 \nmid b$ 。

​		若偶数那个可以被 $4$ 整除，那无论前面的 $(a+k)$ 是多少，乘上这个偶数均可被 $4$ 整除。所以直接使 $4 \mid b$ 即可。

​	$k \equiv 3 \pmod 4:$ 解决方式与 $k \equiv 1 \pmod 4$ 一样。

​	$4 \mid k:$ 可以枚举这时候 $a,b$ 对于 $4$ 的余数的所有情况，发现是不行的。

#### 构造解

对于给出的 $k$ ，进行分类讨论：

$k \equiv 1 \pmod 2$：

​	此时， $(a,b)$ 可以为 $(2m-1,2m)_{1 \le m \le \frac n2}$ ，那么 $(a+k) \equiv 1+1 \equiv 0\pmod2$ ，又因为 $2 \mid b$ ，则 $(a+k) \times b$ 为 $4$ 的倍数，必然可以被 $4$ 整除，所以这种情况有解。直接输出 $(2m-1,2m)$ 即可。

$k \equiv 0 \pmod2$ ：

​	此时可以分类讨论 $a,b$ 的奇偶性来排除掉一些错误情况：

​	$(1)$ 若 $2 \nmid a,2 \nmid b$ ，那么 $2 \nmid (a+k) \times b$ ，直接排除。

​	$(2)$ 若 $2 \mid a,2 \nmid b$ ，那么 $2 \mid (a+k) \times b$ ，但考虑到 $a+k$ 不一定能被 $4$ 整除，需要特判解决。

​	$(3)$ 若 $2 \nmid a,2 \mid b$ ，那么除非 $4 \mid b$ ，否则均无解。

​	$(4)$ 若 $2 \mid a,2 \mid b$ ，那么在 $[1,n]$ 的整数中也一定会有一组 $(a',b')$ 使得 $a',b'$ 均为奇数，那么排除。

注意到，若是直接枚举 $2m-1,2m_{1\le m \le \frac n2}$ ，那么 $(1),(4)$ 两种情况根本不会出现，而 $(2),(3)$ 两种情况实际上就是将 $2m-1,2m_{1 \le m \le \frac n2}$ 的位置调换了一下，所以可以直接枚举 $m$ ，再判断情况决定是否要交换 $(a,b)$ 即可。

那么，根据上述推理过程进行模拟即可通过。

### CODE

```cpp
#include <iostream>
#include <string.h>
#include <cstring>
 
using namespace std;
int T,n,m; 
 
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);//这里的m实际上就是k
        if(m % 2 == 1)//第一种情况
        {
            puts("YES\n");
            for(int i = 1;i < n;i+=2)
               	printf("%d %d\n",i,i+1);
            continue;
        }
		if(m % 4 == 0)
            puts("NO\n");
		else
		{
			printf("YES\n");//对于k%2==0
			for(int i = 1;i < n;i+=2)
				if((i + m + 1) % 4 == 0)//那么选择2m,2m-1的方法
                    printf("%d %d\n",i+1,i);
           		else 
                    printf("%d %d\n",i,i+1);
		}
	}
	return 0;
}
 
 
```



---

## 作者：zajasi (赞：4)

**题面传送门** 

[题面](https://www.luogu.com.cn/problem/CF1719B)

**题意**

给你两个整数 $n,k$($n$ 为偶数)，让你将 $1$ 到 $n$ 这 $n$ 个数分成 $\frac{n}{2}$ 个有序二元组 $(a,b)$，满足 $(a+k)\times b$ 能被 $4$ 整除。

**思路**

很明显，应该用一个奇数和一个偶数进行配凑。及 $(1,2)$ 为一对 , $(3,4)$ 为一对 $\dots$ 对于每一个 $k$,将两种情况都试验一遍，若发现不合法，直接输出。否则最后输出答案

**AC 代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t;
int n,k;
pair<int,int> d[200020];
main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>k;
		int f=0;
		for(int i=1;i<=n;i+=2){
			d[i]=make_pair(i,i+1);
			if(((i+1+k)*i)%4==0){
				d[i]=make_pair(i+1,i);
			}
			else if(((i+k)*(i+1))%4==0){
				
			}
			else{
				f=1;
				break;
			}
//			cout<<d[i].first<<" "<<d[i].second<<"\n";
		}
		if(f==1){
			cout<<"NO\n";
			continue;
		}
		cout<<"YES\n";
		for(int i=1;i<=n;i+=2){
			cout<<d[i].first<<" "<<d[i].second<<"\n";
		}
	}
	return 0;
}


```


---

## 作者：Dry_ice (赞：3)

[cnblogs推广](https://www.cnblogs.com/dry-ice/p/cf1719b.html)

题链：[cf](https://codeforces.ml/contest/1719/problem/B) [luogu](https://www.luogu.com.cn/problem/CF1719B)

> 分类讨论思想。

## Description
把 $1$ 到 $n$ 共 $n$ 个整数分成 $\frac{n}{2}$ 对有序数对 $\left(a_i, b_i\right)$，则对于 $\forall \left(a_i, b_i\right), 4\mid(a_i+k)\times b_i$。问合法方案是否存在，若存在给出一组合法方案。

## Analysis
既然是与被 $4$ 整除有关，那么我们可以对 $4$ 这个数进行分析。
$$4=4\times 1=1\times 4=2\times 2$$
即三种情况，简记为：$p\times 4q$，$4p\times q$，$2p\times 2q$。

显然可以使所有 $x\left(4\mid x,x\in \left[1,n\right],x\in\mathbb{Z}\right)$ 尽量放在 $b$ 的位置，$a$ 选择奇数，此时方案一定最优，共能匹配 $\frac{n}{2}$ 个数字。也就是说还剩 $\frac{n}{2}$ 没有完成匹配，其中有一半奇数，一半偶数（$4x+2$ 型）。

对于剩余的 $\frac{n}{2}$ 个数，我们考虑通过 $a+k$ 或 $b$ 与 $a+k$ 配合使被 $4$ 整除，此时我们需要对 $k$ 的性质进行讨论。

1. $4\mid k$，加 $k$ 之后对 $\left(a+k\right)\times b\pmod4$ 无任何影响，即一定无法匹配；
2. $k\equiv2\pmod4$：使 $b$ 为偶数即 $a\equiv2\pmod4$，此时 $4\mid \left(a+k\right)$；
3. $k\equiv1\pmod4$ 或 $k\equiv3\pmod4$，使 $a$ 为奇数，$b$ 为偶数，一定可以配成**偶数** $\times$ **偶数** 的形式，此时可被 $4$ 整除。

## Code
代码细节较多。具体解释见注释。

```cpp
#include <stdio.h>
int n, k;
int main(void) {
    int t; for (scanf("%d", &t); t--; ) {
        scanf("%d %d", &n, &k); //读入
        if (k % 4 == 0) puts("NO"); //NO 情况特判
        else {
            puts("YES");
            if (k & 1) { //k%4==2，使a%4==2
                for (int i = 1; i <= n; i += 2)
                    printf("%d %d\n", i, i + 1);
            }   
            else { //k 为奇数，使 a 为奇，b 为偶
                for (int i = 3; i <= n; i += 4)
                    printf("%d %d\n", i, i + 1);
                for (int i = 2; i <= n; i += 4)
                    printf("%d %d\n", i, i - 1);
                putchar('\n');
            }
        }
    }
    return 0;
}
```

## The end. Thanks.

~~（一键三连~~

---

## 作者：D2T1 (赞：3)

## B. Mathematical Circus

感谢 @[nomonick](https://www.luogu.com.cn/user/415231) 指出的错误！

考虑对 $k\bmod4$ 的值分类讨论：

- 若 $k\bmod4=0$，那么即 $4|ab$，此时所有的奇数都要和 $4$ 的倍数分类，而显然 $[1,n]$ 的正整数中奇数要比 $4$ 的倍数多，所以无解。
- 若 $k\bmod4=2$，每四个数为一组，类似 $(2,1),(3,4)$ 构造。
- 若 $k\bmod4=1$ 或 $k\bmod4=3$，每两个数为一组，类似 $(1,2)$ 构造。

```cpp
#define multiple_test_cases
 
const int N = 2e5 + 10;
int n, k;
 
void solve(){
	n = rdi;
	k = rdi;
	k %= 4;
	if(k == 0){
		puts("NO");
	} else if(k == 2){
		puts("YES");
		for(int i = 1; i <= n; i += 2){
			if(((i-1)/2) & 1){
				printf("%d %d\n", i, i+1);
			} else {
				printf("%d %d\n", i+1, i);
			}
		}
	} else {
		puts("YES");
		for(int i = 1; i <= n; i += 2){
			printf("%d %d\n", i, i+1);
		}
	}
}
```

---

## 作者：Epi4any (赞：1)

很好的一道同余题。

通过数据范围我们不难发现，构造答案只能 **$O(1)$** 的复杂度才可以，也就是说我们需要提前想好如何构造，不能进行太复杂的运算。

### 构造
所以我们就开始想构造方法，具体来讲就是根据 $k$ 除以 $4$ 的余数构造，在考试期间就意味着找规律，具体如下：
1. 如果 $k$ 除以四余零，那么一定无解。
2. 如果 $k$ 除以四余一或三，那么构造方法就是一奇一偶。
3. 如果 $k$ 除以四余二，那么比较复杂，分为两部分，第一部分是一个奇数和一个四的倍数，第二部分是两个除以四余二的数分一组。

其实到这里就可以开始敲代码了。（不想看证明的可以跳过证明部分）

### 论证
#### 一、$k$ 是四的倍数时无解
$k$ 是四的倍数也就是说 $k$ 对最终的余数没有实质贡献，说白了就是乘了等于白乘。

所以我们要求数对中的两个数中有一个是四的倍数，或者两个都是二的倍数。

但是很显然，$1 - n$ 中奇数个数远远少于四的倍数的个数，也就是说配不成对，即无解。

#### 二、$k$ 除四余一或三可以一奇一偶构造
很显然，余数可以相加，假设这个数对为 $i\times2$，另一个是 $i\times2+1$，那么就有 $i\times 2+k\equiv i\times 2\equiv 0\space\pmod 2$，这时二者的乘积肯定是四的倍数。

#### 三、$k$ 除以四余二可以如上构造
第一种：一个奇数一个四的倍数，这个不用废话了吧。

第二种：一个除四余二的数和另一个除四余二的数很明显也可以。

具体见代码：
```cpp
#include <iostream>
#include <cstdio>
using namespace std;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f; 
}

int t, n, k;

int main() {
	t = read();
	while (t--) {
		n = read(), k = read();
		if (k % 4 == 0) {
			cout << "NO" << endl;
			continue;
		}
		if (k % 2 != 0) {
			cout << "YES" << endl;
			for (int i = 1; i <= n - 1; i += 2) cout << i << " " << i + 1 << endl;
			continue;
		}
		cout << "YES" << endl;
		for (int i = 1; i * 4 <= n; i++) cout << i * 4 - 1 << " " << i * 4 << endl;
		for (int i = 1; i * 4 - 2 <= n; i++) cout << i * 4 - 2 << " " << i * 4 - 3 << endl;
	}
	return 0;
}
//结尾警告：理解思路，杜绝抄袭
```

---

## 作者：_lfxxx_ (赞：1)

分类讨论题。~~有点数学数论证明题的感觉。~~

下面用 $x$ 来代表 $(a+k) \cdot b$。

当 $k \equiv 0 \pmod 4$ 时，$x \equiv a \cdot b \equiv 0 \pmod 4$，奇数只有搭配 $4$ 的倍数才能使 $4\mid x$ 成立。而这时奇数显然多于 $4$ 的倍数，故该情况无解。

当 $k \equiv 2 \pmod 4$ 时，$x \equiv (a+2) \cdot b \pmod 4$，构造 $(2,1)(3,4)\cdots(n-2,n-3)(n-1,n)$，容易验证，这是对的。

构造的想法就是 $(a+2)$ 和 $b$ 中有一个 $4$ 的倍数即可。

当 $k$ 为奇数时，$a+k \equiv a+1 \pmod 2$。构造 $(1,2)(3,4)\cdots(n-3,n-2)(n-1,n)$ 即可，容易验证，这是对的。

构造的想法就一奇一偶。这样就有 $2$ 个 $2$ 的倍数。
### 代码：
```cpp
namespace solution{
void main(){
	int T,n,k;
	cin>>T;
	while(T--){
		cin>>n>>k;
		if(k%4==0)
			cout<<"NO\n";
		else{
			cout<<"YES\n";
			if(k%4==2)
				for(int i=1;i<=n;i+=2)
					if((i+1)%4==0)
						cout<<i+1<<' '<<i<<'\n';
			else
				for(int i=1;i<=n;i+=2)
					cout<<i<<' '<<i+1<<'\n';
		}
	}
}
}
```

---

## 作者：Dregen_Yor (赞：1)

一道不错的构造题。

# 思路

~~先说一句废话~~，能被 $4$ 整除的数在除以 $2$ 之后得到的数还是一个偶数。

我们可以根据 $k$ 的奇偶性以及 $k$ 除以 $2$ 之后的奇偶性分成三种情况来进行讨论。

当 $k$ 为奇数时，我们把所有偶数都放在 $b$ 的位置上，把所有的奇数都放在 $a$ 的位置上，因为奇数 $+$ 奇数 $=$ 偶数，这样可以保证每个 $(a + k) \cdot b $ 都是两个偶数相乘，两个偶数相乘的结果一定可以被 $4$ 整除。

当 $k$ 为偶数且 $\dfrac{k}{2}$ 为奇数时，我们把所有能被 $4$ 整除的偶数放在 $b$ 的位置上，并任找一个奇数放在 $a$ 的位置上即可，对于那些不能被 $4$ 整除的偶数，我们可以把它放在 $a$ 的位置上，把任意一个奇数放在 $b$ 的位置上，原因很简单，我们设 $k=2\times p$，其中 $p$ 为一个奇数，设相对的偶数 $a$ 为 $a=2\times q$，其中 $q$ 为一个奇数。这时 $(a+k)=2\times (p+q)$。
因为 $p$ 和 $q$ 都是奇数，它们的和是一个偶数，两个偶数的积一定可以被 $4$ 整除，这时后让 $b$ 等于任意一个奇数即可。

当 $k$ 为偶数且 $\dfrac{k}{2}$ 为奇数时，我们把所有能被 $4$ 整除的偶数放在 $b$ 的位置上，并任找一个奇数放在 $a$ 的位置上即可，对于那些不能被 $4$ 整除的偶数，我们可以把它放在 $a$ 的位置上，把任意一个奇数放在 $b$ 的位置上，原因很简单，我们设 $k=2\times p$，其中 $p$ 为一个奇数，设相对的偶数 $a$ 为 $a=2\times q$，其中 $q$ 为一个奇数。这时 $(a+k)=2\times (p+q)$。又因为 $p$ 和 $q$ 都是奇数，他们的和是一个偶数，偶数和偶数的积一定可以被 $4$ 整除。这时候令 $b$ 为任意一个奇数即可。

当 $k$ 为偶数且 $\dfrac{k}{2}$ 为偶数时，类比上面的过程，那些不能被 $4$ 整除的偶数没有搭配对象，无论如何都不能被 $4$ 整除，此时无解。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, k;

int main() {
	scanf("%d", &t);

	while (t--) {
		scanf("%d%d", &n, &k);

		if (k & 1) {
			puts("YES");

			for (int i = 1; i <= n; i += 2) {

				printf("%d %d\n", i, i + 1);
			}
		} else {
			if ((k >> 1) & 1) {
				puts("YES");

				for (int i = 1; i <= n; i += 2) {

					if (((i + 1) >> 1) & 1) {
						printf("%d %d\n", i + 1, i);
					} else {
						printf("%d %d\n", i, i + 1);
					}

				}
			} else {
				puts("NO");
			}
		}
	}

	return 0;
}

```


---

## 作者：Failure_Terminator (赞：1)

## Problem

题目翻译够清楚了。略。

## Solution

一道很有趣的构造题。

### Part 1

我们可以从 $k$ 对 $4$ 取模的值入手。

显然，$k=0$ 是一种不可能的情况。

我们可以通过其拓展到 $k \equiv 0 \pmod{4}$ 的情况。

当 $k \equiv 0 \pmod{4}$ 时，对于每对数字，需要满足 $(a+4) \times b$ 是 $4$ 的倍数。

而由于 $4 \times b$ 一定是 $4$ 的倍数，所以需要满足 $a \times b \equiv 0 \pmod{4}$。

而存在两种数，即 $\mod 4=1$ 和 $\mod 4=3$ 的数，通过能被 $4$ 整除的数最多只能消去一组，另外一组无法操作。

因此 $k \equiv 0 \pmod{4}$ 的情况无解。

### Part 2

剩下的也可以分为两种情况。

两种情况皆可以构造为 $a$ 和 $a+1$ 同组的情况（$a$ 为奇数且 $1 \leq a < n$）。

当 $k \equiv 2 \pmod{4}$ 时，若一组中的偶数 $q \equiv 0 \pmod{4}$，偶数放在后面。

否则需要使 $a+k$ 是 $4$ 的倍数，需将偶数放在前面。

其他情况，需把奇数作为 $a$ 位置。

直接按 $(1,2)$，$(3,4),\dots(n-1,n)$ 的构造方式输出。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
void solve(){
	int n,k;
	cin>>n>>k;
	if(k%4==0) cout<<"NO\n";
	else{
		cout<<"YES\n";
		if(k%4==2){
			for(int i=4;i<=n;i+=4)
				cout<<i-1<<" "<<i<<endl;
			for(int i=2;i<=n;i+=4)
				cout<<i<<" "<<i-1<<endl;
		}
		else{
			for(int i=2;i<=n;i+=2)
				cout<<i-1<<" "<<i<<endl;
		}
	}
} 
int t;
int main(){
	cin>>t;
	while(t--) solve();
}
```

Written by **haimo**

---

## 作者：E1_de5truct0r (赞：0)

如果 $4\mid k$，那么 $1$ 到 $n$ 中 $4$ 的倍数只有 $n/4$ 个，显然无法构造。

如果 $k \equiv 2(\bmod\ 4)$，那么我们把所有模 $4$ 余 $2$ 的偶数放前面，所有 $4$ 的倍数的数放后面，把它们和奇数配对即可。具体化地：

- $2 \bmod 4=2$，所以 $2$ 放前面，这样 $(2+k) \bmod 4=(2+2) \bmod 4=0$，于是就有了 $4$ 的倍数。显然在这里放奇数是最优选择，所以匹配之后就是 $(2,1)$。

- $4 \bmod 4=0$，所以 $4$ 放后面，这样就已经有 $4$ 的倍数了，显然放奇数仍然最优，因此是 $(3,4)$。

我们发现每个偶数和它前面那个奇数直接匹配即可。得到代码：

```cpp
for(int i=2;i<=n;i+=4) cout<<i<<" "<<i-1<<endl;
for(int i=4;i<=n;i+=4) cout<<i-1<<" "<<i<<endl;
```

否则，说明 $k$ 一定是奇数。显然，奇数加奇数就是偶数了，偶数至少有一个 $2$，两个偶数乘起来就至少有一个 $4$。所以，我们把奇数放前面，偶数放后面就好了。得到代码：

```cpp
for(int i=1;i<=n;i+=2) cout<<i<<" "<<i+1<<endl;
```

于是把这三种情况拼起来即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int T; cin>>T;
	while(T--){
		int n,k; cin>>n>>k;
		if(k%4==0) puts("No");
		else{
			puts("Yes");
			if(k&1)	for(int i=1;i<=n;i+=2) cout<<i<<" "<<i+1<<endl;
			else{
				for(int i=2;i<=n;i+=4) cout<<i<<" "<<i-1<<endl;
				for(int i=4;i<=n;i+=4) cout<<i-1<<" "<<i<<endl;
			}
		}
	}return 0;
}
```

p.s. 很简单的思维题，目测难度 `*1300` 以下，但我思考了足足 10 分钟，可以考虑退役了。

---

## 作者：_FJX_ (赞：0)

这是一道分类讨论题：

我们可以分 $x$($k$ mod $4$) 的以下几种情况讨论：

-  $x = 0$ ,那么就是 $4 | ab$ ,此时所有的奇数都要和 $4$ 的倍数分类,而显然 $[1,n]$ 的正整数中奇数要比 $4$ 的倍数多，无解。
-  $x = 2$ ,那么就每四个数分为一组，以 $(i + 1, i)$ , $(i, i + 1)$ 这样的形式构造。
-  $x = 1$ $or$ $3$ ,每两个数为一组，以 $(1,2)$ 构造。

注：上述的 $i$ 表示从 $1$ 开始小于 $n$ 的奇数。

_AC node:_
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
void work()
{
	int n, k;
	cin >> n >> k;
	k %= 4;
	if (k == 0)
	{
		cout << "NO\n";
	 } 
	else if (k == 2)
	{
		cout << "YES\n";
		for (int i = 1; i <= n; i += 2)
		{
			if (((i - 1) / 2) & 1)
			{
				cout << i << ' ' << i + 1 << "\n";
			}
			else
			{
				cout << i + 1 << ' ' << i << "\n";
			}
		}
	 } 
	else
	{
		cout << "YES\n";
		for (int i = 1; i <= n; i += 2)
		{
			cout << i << ' ' << i + 1 << "\n";
		}
	}
}
int main(){
    ios_base::sync_with_stdio(false);
	cin.tie (0);
	cout.tie (0);
	int T;
	cin >> T;
	while (T --)
	{
		work();
	}
	return 0;
}

```


---

## 作者：_1437_ (赞：0)

小奥套路题。

### Step $1$：判 $\texttt {"NO"}$

如果 $k\bmod 4=0$，那么一旦存在 $ab\bmod 4\not= 0$，就会有 $(a+k)b\bmod 4\not=0$。

对于 $i=1,2,3,\dots,n$，里面总共就只有 $\lfloor\frac{n}{4}\rfloor$ 个 $i\bmod 4=0$，所以就会导致如果配对，完全不够。所以一定会存在 $ab\bmod 4\not=0$ 的情况。

那么如果有 $k\bmod 4=0$，直接输出 $\texttt{"NO"}$ 即可。

### Step $2$：构造

对于 $i=1,3,5,\dots,n-1$，我们考虑每一对都由 $i,i+1$ 构成，按照 $k\bmod 4$ 的情况讨论即可。

- 如果 $k\bmod 2=1$：
	
	> 显然当 $(i+1)\bmod 4=0$ 的时候 $a=i,b=i+1$ 就直接满足要求。当 $(i+1)\bmod 4=2$ 的时候，$a=i,b=i+1$ 的策略满足 $a$ 和 $b$ 都是偶数，相乘自然是 $4$ 的倍数。

	所以对于每一对，$a=i,b=i+1$ 即可。

- 如果 $k\bmod 4=2$：

	> 显然当 $(i+1)\bmod 4=0$ 的时候 $a=i,b=i+1$ 就直接满足要求。当 $(i+1)\bmod 4=2$ 的时候，$a=i+1,b=i$ 的策略满足 $a\bmod 4=0$，是 $4$ 的倍数。

	所以对于每一对，当 $i\bmod 4=3$ 的时候，$a=i,b=i+1$，否则交换 $a,b$ 即可。
    
### Step $3$：Code

```cpp
int n = getInt(), k = getInt();
if(k % 4 == 0) return puts("NO") & 0;
puts("YES");
if(k % 2 == 1) {
	rep(i, 1, n / 2) {
		putInt(2 * i - 1, ' ');
		putInt(2 * i, '\n');
	}
} else {
	rep(i, 1, n / 2) {
		if(i % 2 == 1) cout << 2 * i << ' ' << 2 * i - 1 << endl;
		else cout << 2 * i - 1 << ' ' << 2 * i << endl;
	}
}
```

---

## 作者：nomonick (赞：0)

## CF1719B Mathematical Circus

题面 link : [CF1719B](https://www.luogu.com.cn/problem/CF1719B)

## 浅要分析一下

题面要求 $(a + k) \times b \bmod 4 = 0$。

显然当 $b \bmod 4 = 0$ 就无须考虑 $a$ 的取值。

那么只需要对于 $a + k$ 直接形成 $4$ 的倍数（下称构造方案一）或者 $a + k$ 和 $ b $ 同时是 2 的倍数（下称构造方案二）。

所以显然让 $ 4 $ 的倍数携带一个奇数形成二元组最优。

那么不妨考虑二元组含 $4p - 2 (p \in N_+)$（不妨设为 $y$ ） 的解法。

已知 $ 4 $ 的倍数已被使用，那么二元组的另一个一定是奇数（不妨设为 $x$ )。

此时显然：

 - 当 $k$ 为奇数时，$x + k$ 一定是偶数，满足构造二。
 - 当 $k$ 为 $4p - 2 (p \in N_+)$ 时，$y + k$ 一定是 $4$ 的倍数，满足构造一。
 - 当 $k$ 为 $4p (p \in N_+)$ 时，必然无解。



## code

```cpp
inline void solve()
{
	n = read(); k = read();
	if (k % 4 == 0) return puts("NO"), void();
	puts("YES");
	if (k % 4 == 2) 
	{
		for (int i = 1,j = 1; i <= n; i += 2,++j) 
		{
			if (j & 1) printf("%lld %lld\n",i+1,i);
			else printf("%lld %lld\n",i,i+1);
		} return;
	}
	for (int i = 1; i <= n; i += 2) printf("%lld %lld\n",i,i+1);
	return ;
}
```

---

## 作者：RoyWu1207 (赞：0)

（写在开头：我是蒟蒻，我不是大佬，我写的没有那么深奥）

这题样例很奇怪。

重点：第三个 $\text{testcase}$，如果我们将这个答案序列重新排一下，是这样的：

- $2$，$1$
- $3$，$4$
- $6$，$5$
- $7$，$8$
- $10$，$9$
- $11$，$12$

很神奇的事情发生了，结合样例，我们发现：如果有解，必定有一组解是形如 $(i,i + 1)$ 或 $(i + 1, i)$ $(i \mod 2 \equiv 1)$ 的。

但是如何证明呢？

将对 $k$ 取模的情况分类讨论：

1. 当 $k \equiv 1 \pmod 4$ 或 $k \equiv 3 \pmod 4$ 时：

	- 由于余数具有可加性和可乘性，在这种情况下，$k$ 为奇数且 $a = i$ 时，$(a + k) \equiv 0 \pmod 2,b \equiv 0 \pmod 2,(a + k) \times b \equiv 0 \pmod 4$，符合条件。


2. 当 $k \equiv 0 \pmod 4$ 时：

	- 当 $a = i$ 时，显而易见的是，此时答案取模 $4$ 的结果与 $a + k$ 无关，需要 $i + 1$ 为 $4$ 的倍数，可以证明，在范围内，$i + 1$ 为 $4$ 的倍数的数个数不足以与 $a$ 配对；
  	- 当 $a = i + 1$ 时同样是差不多的情况；
   - 因此这种情况无解。


3. 当 $k \equiv 2 \pmod 4$ 时： 

	- 当 $(i + 1) \mod 4 \equiv 0$ 时，令 $b = i + 1$ 即可；
   - 当 $(i + 1) \mod 4 \equiv 2$ 时，令 $a = i + 1$ 即可；
   - 因此，这种情况符合条件。


通过这个规律，我们就能做题了。

~~（当然，考场上没想出23两部分，所以 AC Code凑合看吧！）~~

#### **AC Code：**

```cpp
#include <iostream>
#include <cstring>

using namespace std;

bool bo[200001];

int main() {
	int t; cin >> t;
	while (t--) {
		memset(bo, false, sizeof (bo));
		int n, k; cin >> n >> k;
		if (k % 2 == 1) {
			cout << "YES" << endl;
			for (int i = 1; i <= n; i += 2)
				cout << i << ' ' << i + 1 << endl;
		} else {
			int flag = 1; k %= 4;
			for (int i = 1; i <= n; i += 2) {
				if ((i + k) % 4 * ((i + 1) % 4) % 4 == 0)
					bo[i] = true;
				else if ((i + 1 + k) % 4 * (i % 4) % 4 == 0)
					bo[i + 1] = true;
				else {
					flag = 0;
					break; 
				} 
			} if (!flag)
				cout << "NO" << endl;
			else {
				cout << "YES" << endl;
				for (int i = 1; i <= n; i += 2) {
					if (bo[i])
						cout << i << ' ' << i + 1 << endl;
					else
						cout << i + 1 << ' ' << i << endl;
				}
			}
		}
	} return 0;
}
```
代码凑合看吧，不是最优解，但它还是A了~~

谢谢大家，如果有问题欢迎向本蒟蒻指出！谢谢！

---

## 作者：落花月朦胧 (赞：0)

# Problem

构造 $n$ 个二元组，满足这些二元组是 $1$ 到 $2\times n$ 中所有的数，这里设二元组为 $a, b$，同时要求所有 $4 | (a + k) \times b$，要求你构造，或者报告无解。

# Solution

首先考虑 $k$ 是奇数的时候，显然我们可以构造这样的二元组， $(i, i + 1)$，其中 $i$ 是一个奇数，显然， $i + 1$ 是一个偶数， $i + k$ 也是一个偶数，那我们一定可以从这两个偶数中各抽出一个 $2$， 于是就满足了是 $4$ 的倍数的条件。

比较麻烦的是当 $k$ 是偶数的时候，显然可以先构造出 $n/4$ 个二元组，满足第一个数是一个任意数，第二个数是 $4$ 的倍数，剩下的如何构造？

首先如果把奇数放在前面，加了 $k$ 还是一个奇数，没法满足，考虑把偶数放在前面，似乎可以满足条件，但是发现如果 $k$ 是 $4$ 的倍数， $2+k$ 不是 $4$ 的倍数，其他情况都可以构造。

于是我们先判掉 $k$ 是 $4$ 的倍数的情况，然后把所有 $4$ 的倍数的数存起来，一个一个配对输出，没有了再把偶数放在前面，奇数放在后面输出即可。

# Code

```cpp
void solve() {
    int n, k;
    std::cin >> n >> k;

    if (k % 4 == 0) {
        std::cout << "NO\n";
        return;
    }

    std::cout << "YES\n";
    if (k & 1) {
        for (int i = 1; i <= n; i += 2) {
            std::cout << i << " " << i + 1 << '\n';
        }
        return;
    }

    std::vector<int> a, b;
    for (int i = 1; i <= n; i++) {
        if (i % 4 == 0) a.push_back(i);
        else if (i % 2 == 0) b.push_back(i);
    }

    int pos1 = 0, pos2 = 0;
    for (int i = 1; i <= n; i += 2) {
        if (pos1 < a.size()) {
            std::cout << i << " " << a[pos1] << "\n";
            pos1++;    
        } else {
            std::cout << b[pos2] << " " << i << '\n';
            pos2++;
        }   
    }
}
```

---

## 作者：郑朝曦zzx (赞：0)

# 一 解题思路
显然是否能构造与 $k \bmod 4$ 的值有关，通过分析样例，我们发现当 $k \bmod 4 = 0$ 的时候，是不存在构造方案的，这也很好理解，$k \bmod 4 = 0$ 也就是说 $a$ 是否加上 $k$ 对余数不产生影响，那么要么是 $a \bmod 4 = 0$ 或者 $b \bmod 4 = 0$ 才能使得这组解合法，但是显然 $n$ 以内除以四余数为 $0$ 的数没有那么多，故无法构造。

如果模 $4$ 后余数不为 $0$，那么我们分析一下样例就能发现构造方法：

- 要是余数为 $1$ 或 $3$，每次输出连续的奇数与偶数
```cpp
for (int i = 1; i * 2 <= x; ++i)
    printf("%d %d\n", i * 2 - 1, i * 2);	
```

- 否则，每两组解凑出连续四个整数
```cpp
for (int i = 1; i * 4 <= x; ++i)
{
    printf("%d %d\n", i * 4 - 1, i * 4);
    printf("%d %d\n", i * 4 - 2, i * 4 - 3);
}
if (x % 4 == 2) printf("%d %d\n", x, x - 1);
```

# 二 完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline int read()
{
	bool flag = true;
	char c = getchar();
	if (c == '-') flag = false;
	while(!(c >= '0' && c <= '9')) c = getchar();
	int x = 0;
	while(c >= '0' && c <= '9')
	{
		x = (x << 3) + (x << 1) + c - '0';
		c = getchar();
	}
	if (flag == true) return x;
	return -x;
}
void IOS()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
int main()
{
	int t = read();
	while (t--)
	{
		int x = read(), y = read();
		if (y % 4 == 0) printf("NO\n");
		else if (y % 4 == 1 || y % 4 == 3)
		{
			printf("YES\n");
			for (int i = 1; i * 2 <= x; ++i)
				printf("%d %d\n", i * 2 - 1, i * 2);	
		}
		else if (y % 4 == 2)
		{
			printf("YES\n");
			for (int i = 1; i * 4 <= x; ++i)
			{
				printf("%d %d\n", i * 4 - 1, i * 4);
				printf("%d %d\n", i * 4 - 2, i * 4 - 3);
			}
			if (x % 4 == 2) printf("%d %d\n", x, x - 1);
		}
	}
    return 0;
}
```


---

## 作者：Scorilon (赞：0)

因为若 $4 \mid (a+k)\times b$，那么 $a$ 和 $b$ 一定满足 $|a-b|=1$，那么我们就可以从 $1 \sim n$ 进行枚举，每次判断 $i$ 和 $i+1$ 可不可以满足上式，因为 $a$ 和 $b$ 的位置关系非常重要，所以我们两个都要试，若无法匹配则说明这里面存在着不满足上式的数，那么答案就是否，反之答案就是是，并输出前面记录的答案。

每次操作的最坏时间复杂度为 $O(\frac{n}{2})$ 可以通过本题。

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

int t,n,k;
int x[100005],y[100005],idx;//x和y用来记录答案

int main() {
	scanf("%d",&t);
	while(t--) {
		scanf("%d%d",&n,&k);
		bool f=true;
		idx=0;
		for(int i=1;i<=n;i++) {
			if((i+k)*(i+1)%4==0) x[++idx]=i,y[idx]=i+1,i++;
			else if((i+1+k)*i%4==0) x[++idx]=i+1,y[idx]=i,i++;
			else {
				puts("NO");
				f=false;
				break;
			}
		}
		if(f) {
			puts("YES");
			for(int i=1;i<=idx;i++) {
				printf("%d %d\n",x[i],y[i]);
			}
		}
	}
	return 0;
}
```


---

## 作者：Jeremiahy (赞：0)

## 分析

考虑根据 $k$ 进行分类讨论：

- $k\mod4=0$。 那么显然要在 $b$ 处安排奇数， $a$ 处安排 $4$ 个倍数（或者采用其他安排方法），但是 $[1,n]$ 内 $4$ 的倍数显然少于奇数，所以无解。

- $k$ 为奇数。两个一组，按照 $(1,2),(3,4),\dots,(n-1,n)$ 的顺序安排。这样安排正确原因是 $a+k$ 一定是偶数， $b$ 也一定是偶数，所以相乘一定是 $4$ 的倍数。

- 其他情况（$k\mod4=2$）。此时按照 $(2,1),(3,4)$ 的顺序安排。即第奇数组安排的 $a>b$，偶数组安排的 $a<b$。这样做正确的原因是凑出一个 $4$ 因子。奇数组的偶数为 $2$ 的倍数，偶数组的偶数为 $4$ 的倍数，所以奇数组的偶数放在 $a$ 的位置凑出 $4$ 的倍数，偶数组的偶数放在 $b$ 直接当 $4$ 的倍数。

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, k;
signed main() {
	cin >> t;
	while (t--) {
		cin >> n >> k;
		if (!(k % 4))//k mod 4 = 0
			puts("No");
		else if (k & 1) {// k 为奇数
			puts("Yes");
			for (register int i = 1; i <= n / 2; i++)
				cout << i + i - 1 << ' ' << i + i << '\n';			
		}
		else { // k mod 4 = 2
			puts("Yes");
			for (register int i = 1; i <= n / 2; i++)
				if (i & 1) // 奇数组
					cout << i + i << ' ' << i + i - 1 << '\n';
				else 
					cout << i + i - 1 << ' ' << i + i << '\n';
		}		
	}

	return 0;
}
```


---

## 作者：ztlh (赞：0)

# Solution

不难发现，$k$ 与 $k - 4$ 实际上是一样的，因此我们可以将 $k$ 模 $4$，将它的范围限定在 $0 \leq k \leq 3$。

然后分类讨论：

- $k = 0$ 时，我们可以直接将 $k$ 忽略。每个奇数必然要和一个 $4$ 的倍数组合，而每 $4$ 个数字中有 $2$ 个奇数和 $1$ 个 $4$ 的倍数，且后者是最后一个，明显不够。所以直接输出 $NO$。

- $k = 1$ 或 $k = 3$ 时，按 $(1, 2), (3, 4), ..., (n - 1, n)$ 组合，每个数对 $(a, b)$ 中，$a + k$ 是偶数，$b$ 也是偶数，两者乘积必然是 $4$ 的倍数。所以直接输出 $YES$ 并输出解即可。

- $k = 2$ 时，按 $(2, 1), (3, 4), (6, 5), ...$ 组合（奇数数对反一下），则奇数数对中 $a + k$ 是 $4$ 的倍数，偶数数对中 $b$ 是 $4$ 的倍数。所以直接输出 $YES$ 并输出解即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int n,k;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&k);
		k%=4;
		if(k==0) printf("NO\n");
		else if(k&1){
			printf("YES\n");
			for(int i=1;i<=n;i+=2)
				printf("%d %d\n",i,i+1);
		}
		else{
			printf("YES\n");
			for(int i=1;i<=n/2;i++){
				if(i&1) printf("%d %d\n",i*2,i*2-1);
				else printf("%d %d\n",i*2-1,i*2);
			}
		}
	}
	return 0;
}
```

---

## 作者：cachejtt (赞：0)

## 题意
对于给定正整数 $n$ 和 $k$，保证 $n$ 是偶数，你需要做以下事情。

选取 $1$ 到 $n$ 的数，两两一对。对于一对数 $(a,b)$，必须保证 $(a+k)\times b$ 是 $4$ 的倍数。

判断是否可行，若可行，输出 `YES` 并给出方案，若不可行，输出 `NO`。

## 思路
考虑总是让相邻的两个数一组，因为这样能保证每一组里总有一个偶数。考虑分类讨论 $k$。

### 奇数
若 $k\bmod 2=1$，则显然成立。

对于数对 $(2\times m,2\times m+1)$，

由于 $2\mid (2\times m+1+k)$，且 $2\mid (2\times m)$，故 

$$4\mid [(2\times m+1+k)\times (2\times m)]$$

成立。

### 偶数

需要分类讨论。

#### 情况1
当 $k\bmod 4=2$ 时，显然成立。

对于数对 $(4\times m,4\times m+1)$,

由于 $4\mid (4\times m)$，显然

$$4\mid [(4\times m)\times (4\times m+1+k)]$$

而对于数对 $(4\times m+2,4\times m+3)$

由于 $4\mid (4\times m+2+k)$，故

$$4\mid [(4\times m+2+k)\times (4\times m+3)]$$

#### 情况2
当 $k\bmod 4=0$ 时，对于数对 $(4\times m+2,4\times m+3)$，无法成立。

## 做法
这是我考场上的写法，当时没想到分类讨论，就写了一个暴力判断，也可以用上面的写法，二者差不多。

只需对于 $(i,i+1)$，看是否能满足即可。若满足，存下答案，否则打上标记。
## 代码
```cpp
#include<bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define nrep(i, a, b) for (int i = (a); i >= (b); --i)
#define endl "\n"
using namespace std;
int t=1,n,m,k;
int ans[200005],flag;
signed main(){
  ios::sync_with_stdio(0);
  cin>>t;
  rep(kk,1,t){
    cin>>n>>k;
    flag=1;
    rep(i,1,n){
      if(i%2==1){//(i,i+1)
        if((i+k)*(i+1)%4==0){
          ans[i]=i;
          ans[i+1]=i+1;
        }
        else if((i)*(i+1+k)%4==0){
          ans[i]=i+1;
          ans[i+1]=i;
        }
        else flag=0;
      }
    }
    if(flag==0)cout<<"NO"<<endl;
    else{
      cout<<"YES"<<endl;
      rep(i,1,n){
        if(i%2==1){
          cout<<ans[i]<<" "<<ans[i+1]<<endl;
        }
      }
    }
  }
  return 0;
}
```

---

