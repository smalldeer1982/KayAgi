# Powers Of Two

## 题目描述

A positive integer $ x $ is called a power of two if it can be represented as $ x = 2^y $ , where $ y $ is a non-negative integer. So, the powers of two are $ 1, 2, 4, 8, 16, \dots $ .

You are given two positive integers $ n $ and $ k $ . Your task is to represent $ n $ as the sum of exactly $ k $ powers of two.

## 样例 #1

### 输入

```
9 4
```

### 输出

```
YES
1 2 2 4 
```

## 样例 #2

### 输入

```
8 1
```

### 输出

```
YES
8 
```

## 样例 #3

### 输入

```
5 1
```

### 输出

```
NO
```

## 样例 #4

### 输入

```
3 7
```

### 输出

```
NO
```

# 题解

## 作者：Pretharp (赞：4)

注：非常抱歉打错了几个字，只能重新提交审核了！

本蒟蒻第一次提交题解，有错的地方欢迎指出！一下是正片：

### 1、思路实现

[先给个 link](https://www.luogu.com.cn/problem/CF1095C)

先一看，是道蓝题，不过别急，这道蓝题很简单。题目要求我们把 $n$ 拆成 $k$ 个 $2$ 的幂，显然我们可以先转换成二进制。比如样例中的 $n$ 转换为二进制就是： $(1001)_2$ ，通过位值原理，又可以转换成： $(1000)_2+(1)_2$ ，转成十进制，就是 $(8)_{10}+(1)_{10}$ ，这样， $n$ 就被拆分成了两个 $2$ 的幂。

不过样例要求要拆 $4$ 个 $2$ 的幂，所以这样显然不行。但是，我们知道： $2^k = 2^{k-1}*2$ 所以，通过这种方法，我们可以每次挑出最大的 $2$ 的幂，然后把它拆成两个小一半的 $2$ 的幂，这样，我们就离答案进了一步！

**总结：** 现将 $n$ 转成二进制，在每次挑出最大的 $2$ 的幂，把它拆成两个，直到出现了 $k$ 个幂。

### 2、特殊情况

1. 不难发现， $2$ 的幂的数量只会越来越多，所以如果 $k$ 一开始就小于的 $2$ 的幂数量，直接输出 $“No”$。注意一下， $n$ 的二进制中， $1$ 的数量就是幂的数量哦！

1. 如果 $n$ 小于 $k$ ，那么也输出 $“No”$ ，具体为什么不解释（因为太简单了）。

加上了两种特殊情况，就到了代码时间了！

### 3、具体实现

我们可以先用数组 $a$ 存储 $n$ 的二进制，但具体表达却与二进制不太相同。例如 $1001$ 就按照之前所说，把当前最大的 $2$ 的幂拆成两个小一点的，再按照原来的方法就表示为 $0201$ （也就是 $(100)_2+(100)_2+(1)_2$ ，现在数组 $a$ 已经不是只有 $0$ 和 $1$ 了），此时，从右往左的 $n$ 位就表示有几个 $2^{n-1}$ 。当 $a$ 中的数字总和等于 $k$ 时，就是答案。比如样例，现先是 $1001$ ，然后是 $0201$ ，再将首位 “推” 一次，就得到 $0121$ ，等于 $(100)_2+(10)_2+(10)_2+(1)_2$ 最后一转换，就得到了 $(4)_{10}+(2)_{10}+(2)_{10}+(1)_{10}$ ，注意要从小到大输出。

其他的具体细节就看注释吧！

```cpp
#include<bits/stdc++.h>
#define int long long // 这道题可以不开 long long 哦！
#define QWQ while(1) cout<<"yee" 
using namespace std;
const int N=2e5+5;
int n,k,idx,a[N],t;
// idx 是 n 的二进制时的位数, a 数组用于储存 n 的二进制。 
// t 是用于临时记录 n 中， 2 的幂的数量（也就是 1 的数量）。
signed main()
{
	QWQ;
	cin>>n>>k; // 平平无奇的输入。 
	if(n<k){
		cout<<"NO";
		return 0;
		// 特殊情况 2 ，之前介绍过了 qwp 。 
	}
	while(n){ // 进制转换部分，把 n 转成二进制。 
		s[++idx]=n&1; // 这一步是位运算，不懂得可以去我博客里看看。
		t+=s[idx]; // 统计 n 二进制下 1 的数量。 
		n>>=1; // 也是位运算，等价于 n/=2 。 
	}
	if(t>k){
		cout<<"NO";
		return 0;
		// 特殊情况 1 ，之前介绍过了 qwp 。 
	}
	// 接下来是本代码的重点：将 n 中的 2 的幂数量增多。
	k-=t;
	while(k--){ // 前已经有了 t 个 2 的幂，先在还需要 k-t 个幂，每次只增加一个。 
		while(a[idx]==0) idx--; // 找到当前最大的 2 的幂。
		s[idx]--;
		s[idx]+=2; // 模拟 “推”的过程。 
	}
	cout<<"YES"<<endl;
	for(int i=0;i<=l;i++){
		for(int j=1;j<=a[i];j++){ // 第 n 为是多少就要输出 a[n] 个 2 的 n-1 次方。 
			cout<<(1<<i-1); // 位运算，等价于 1*(i-1)*2 ,但不同的是 i-1 为 0 时，也会输出 1 。 
		}
	}
	return 0; // 完美结束！ 
}
```

---

## 作者：vocaloid (赞：3)

将一个数字化成二进制，然后从最高位向下拆，看看最终能不能拆到刚好 $k$ 即可。

什么意思呢？假定我们现在是 $233$ ，要拆成 $8$ 个 $2^k$ 的和，我们先将它化成二进制：

`11101001`

然后从高位一步步拆：

`03101001` `sum=6` $\rightarrow$ `02301001` `sum=7` $\rightarrow$ `01501001` `sum=8`

然后反向输出就$get$了答案。

`01501001` = $1\times 1$ + $8\times 1$ + $32\times 5$ + $64\times 1$

也就是 `1 8 32 32 32 32 32 64`。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[105],tot,sum;
int main()
{
    scanf("%d %d",&n,&k);
    int x=n;
    while(x)
    {
        a[++tot]=x&1;
        x>>=1;
        if(a[tot]) sum++;
    }
    while(sum<k)
    {
        if(tot==1) break;
        a[tot-1]+=2;
        a[tot]--;
        if(!a[tot]) tot--;
        sum++;
    }
    if(sum!=k) return puts("NO"),0;
    puts("YES");
    int t=1;
    for(int i=1;i<=tot;i++)
    {
        for(int j=1;j<=a[i];j++) printf("%d ",t);
        t<<=1;
    }
    return 0;
}
```

---

## 作者：exited (赞：1)

两个月前交过的题，今天趁着有空~~水~~写一片题解。
______________
### 正文：

题目简意：给出 `n`，`k`，求出一个长度为`k`的2的幂的数列，使得$\sum_{i=1}^ka_i=n$。

- 先来看无解情况：

1. 经过分析，要把 $n$ 拆成 $k$ 个 $2$ 的非负整次幂，必须 $n\geq k$ ,否则就会有负次幂出现；

2. 对于一个正整数 $n$，如 $114514$，它的二进制数为 $(11011111101010010)_2$，它中间有 $11$ 个 $1$，也就是 $11$ 个 $2$ 的幂，那么 $k$ 至少也得是 $11$（不然就凑不出来）。

- 分析到此，接下来便可以开凑了（一定有解）。

之前已经分析过了一个数要保证有解的最小的 $k$ 是多少，那么当实际的 $k$ 比这个最小的 $k$ 大时怎么办呢？

首先对于一个大于 $1$ 的 $2$ 的幂，它可以拆成两个较小的 $2$ 的幂的和，即：$2^n=2^{n-1}+2^{n-1}$。

因此从大到小拆完 $n$ 后，再把最大的数拆开，一步一步凑出 $k$ 个数就行啦。

这一步我用堆来维护，~~其实是因为我蒻~~。

代码见下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[200005],tp;
priority_queue<int> q;
int main()
{
	cin>>n>>k;
	if(n<k){
		puts("NO");
		return 0;
	}
	for(int i=30;i>=0;i--)
		if(n>=(1<<i)){
			n-=(1<<i);
			q.push(i);
		}
	if(q.size()>k){
		puts("NO");
		return 0;
	}
	puts("YES");
	while(q.size()<k){
		int p=q.top();
		q.pop();
		q.push(p-1);
		q.push(p-1);
	}
	while(!q.empty()){
		a[++tp]=q.top();
		q.pop();
	}
	for(int i=tp;i>=1;i--)	
		cout<<(1<<a[i])<<' ';
	return 0;
}
```


---

## 作者：woshishei (赞：1)

开始看到这道题的时候，乍一看，就要用dp。

然后看到了数据范围：$1 \le n \le 10^9$……

说明需要复杂度更低的算法。

------------

先把$n$转换成二进制，例如：$323 = (101000011)_2$

很容易发现当$k > n$或$k$小于二进制中$1$的个数时无解。

把二进制存在一个数组中，因为$1 \times 2^n = 2 \times 2^{n-1}$，所以可以把一个1往后“推”一位成为2，此时拆出的个数+1，重复步骤，知道等于$k$为止，即为正解。

**例：**输入：`323 8`

$101000011 \rightarrow 021000011 \rightarrow 013000011 \rightarrow 005000011 \rightarrow 004200011$

输出：`1 2 32 32 64 64 64 64`

---

## 作者：happybob (赞：0)

考虑对 $n$ 进行二进制拆分，最终可以表示成 $n =2^{a_1} + 2^{a_2} + \cdots 2^{a_p}$，$a_i \geq 0(1 \leq i \leq p)$。

当 $p>k$ 或 $k>n$ 时，显然无解。

当 $p=k$ 时，输出即为这 $p$ 个数，即 $2^{a_1}, 2^{a_2}, \cdots, 2^{a_p}$。

当 $p<k$ 时，显然有 $2^x = 2^{x-1} + 2^{x-1}$，将每一个 $a_i \geq 1$ 的 $i$ 变成两个 $2^{a_i-1}$。即每次添加一个。

最终一定能变至 $k$。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int N = 5e5 + 5;

ll n, k, cnt;

deque<ll> v; 

int main()
{
	scanf("%lld%lld", &n, &k);
	ll rn = n, cnt = 0;
	while (rn)
	{
		if (rn & 1)
		{
			v.push_front(cnt);
		}
		rn >>= 1;
		cnt++;
	}
	if (v.size() > k || k > n)
	{
		printf("NO\n");
		return 0;
	}
	printf("YES\n");
	while (v.size() < k)
	{
		int u = v.front();
		v.pop_front();
		if (u == 1)
		{
			v.push_back(u - 1);
			v.push_back(u - 1);
		}
		else
		{
			v.push_front(u - 1);
			v.push_front(u - 1);
		}
	}
	while (v.size())
	{
		int u = v.front();
		printf("%lld ", 1ll << u);
		v.pop_front();
	}
	printf("\n");
	return 0;
}
```


---

## 作者：Kedit2007 (赞：0)

## 题目链接
[CF1095C Powers Of Two](https://www.luogu.com.cn/problem/CF1095C)

## 题目含义
给出 $n$ 和 $k$ ，求出一个长度为 $k$ 的 $2$ 的幂的数列 $a$ ，使得 $\sum_{i = 1}^{k} a_i\ =n$。

## 思路

先拆几个简单的例子看看。$8$ 能够组成长度为 $1$ 到 $8$ 的合法序列：

- $8 = 8$
- $8 = 4 + 4$
- $8 = 2 + 2 + 4$
- $8 = 2 + 2 + 2 + 2$
- $8 = 1 + 1 + 2 + 2 + 2$
- $8 = 1 + 1 + 1 + 1 + 2 + 2$
- $8 = 1 + 1 + 1 + 1 + 1 + 1 + 2$
- $8 = 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1$

将这些等式右边的部分写成 $n \cdot 2^m + ...$ 的形式，即：
- $8 = 1 \cdot 2^3$
- $8 = 2 \cdot 2^2$
- $8 = 2 \cdot 2^1 + 1 \cdot 2^2$
- $8 = 4 \cdot 2^1$
- $8 = 2 \cdot 2^0 + 3 \cdot 2^1$
- $8 = 4 \cdot 2^0 + 2 \cdot 2^1$
- $8 = 6 \cdot 2^0 + 1 \cdot 2^1$
- $8 = 8 \cdot 2^0$

可以发现，如果我们想要让某一个序列的长度增加，可以将 $2^m$ 前的系数减一，并将 $2^{m-1}$ 前的系数加二，这个性质对所有自然数分割成的序列都生效。其中 $m > 1$ 且 $2^m$ 项前系数不为零。如：$3 \cdot 2^5 + 2 \cdot 2^6$ 可以变成 $5 \cdot 2^5 + 1 \cdot 2^6$。

按照这个思路，我们就通过不断执行上面所说的操作，尝试让序列长度到达 $k$。

---
维护一个数组 $b$ 表示上述的序列，其中 $b_i$ 表示 $2^i$ 项前系数。定义序列的长度 $l$ 为 $b$ 中所有元素之和。

对于输入的数字，我们可以这样构造初始的数组：

```cpp
int num;
cin >> num;
	
vector<int> b{};
	
int l = 0;
	
while (num)
{
	if (num % 2 == 1)
	{
		l++;
	}
	b.push_back((num % 2 == 0) ? 0 : 1);
	num /= 2;
}
```


因为我们上面所做的操作只能让 $l$ 增大，所以如果此时 $l > k$，则无解。

---

接下来只需要一直持续上面的变换操作直到 $l = k$ 就可以得到答案。若直到只有 $2^0$ 项前系数不为零时仍有 $l < k$ ，则无解。

当 $l = k$ 时，对于每个 $b_i$ ，打印 $b_i$ 次 $2^i$ 的值即可得到一个合法的序列。

```cpp
int mask = 1;
for (auto n : b)
{
	for (int i = 0; i < n; i++)
	{
		cout << mask << ' ';
	}
	mask *= 2;
}
```

## 完整参考代码
```cpp
#include <bits/stdc++.h>

using namespace std;

int main()
{
	int num; //对应题目中的 n
	cin >> num;
	
	vector<int> bits{}; //对应上文的 b
	
	int count = 0; //对应上文的 l
	
	while (num)
	{
		if (num % 2 == 1)
		{
			count++;
		}
		bits.push_back((num % 2 == 0) ? 0 : 1);
		num /= 2;
	}
	
	int target; //对应题目中的 k
	cin >> target;
	
	if (target < count)
	{
		cout << "NO" << endl;
		return 0;
	}
	
	if (target == count)
	{
		cout << "YES" << endl;
		int mask = 1;
		for (auto bitCount : bits)
		{
			for (int i = 0; i < bitCount; i++)
			{
				cout << mask << ' ';
			}
			mask *= 2;
		}
		return 0;
	}
	
	while (bits.size() > 1)
	{
		if (bits[bits.size() - 1] == 0)
		{
			bits.erase(bits.end() - 1);
			continue;
		}
		
		
		bits[bits.size() - 1]--;
		bits[bits.size() - 2] += 2;
		count++;
		
		if (count != target)
		{
			continue;
		}
		
		cout << "YES" << endl;
		int mask = 1;
		for (auto bitCount : bits)
		{
			for (int i = 0; i < bitCount; i++)
			{
				cout << mask << ' ';
			}
			mask *= 2;
		}
		
		return 0;
	}
	
	cout << "NO";
	return 0;
}

```


---

## 作者：XL4453 (赞：0)


### 题目分析：

思路肯定是往二进制上想，那么把要表示的数拆成二进制。

首先判断有没有解。发现假如 $k$ 还没有二进制各位上的 1 的数多，那么一定是无解的，没有任何一个二进制位能代替两个不相同的二进制位。另一方面，如果把当前数全拆成 1 都不能满足 $k$ 个数的要求，那么也是无解的。

然后就考虑如何构造，想到可以一个高位 1 拆成两个低一位的 1 的和，这样的就可以在和不变得情况下平添一个位置了。

实现上，计算出需要的拆分操作数，并记录下每一个位置上的一的个数，然后从高位到低位枚举，每有一次操作就拆分一次，最后输出即可。

---------
### 代码：
```cpp
#include<cstdio>
using namespace std;
int n,k,num[200005],len=-1,tot;
int main(){
	scanf("%d%d",&n,&k);
	if(n<k){
		printf("NO\n");
		return 0;
	}
	while(n){
		num[++len]=n&1;
		tot+=num[len];
		n>>=1;
	}
	if(k<tot){
		printf("NO\n");
		return 0;
	}
	k-=tot;
	while(k--){
		while(num[len]==0)len--;
		num[len]--;
		num[len-1]+=2;
	}
	printf("YES\n");
	for(int i=0;i<=len;i++)
	for(int j=1;j<=num[i];j++)
	printf("%d ",(1<<i));

	return 0;
}
```



---

## 作者：Argon_Cube (赞：0)

* **【题目链接】**

[Link:CF1095C](https://www.luogu.com.cn/problem/CF1095C)

* **【解题思路】**

看到这道题第一感觉就是，分解成二进制，然后把大的一步步分解成小的。

对，差不多就是细胞分裂的感觉。

然后有了思路，我们就可以做题了。

* **如何拆？**

首先分解成二进制。

然后，一位一位往下拆，每次将第一个非零位减$1$，然后把低位加$2$。

复杂度$\Theta(k)$。

然后看一看数据范围：$1\leq k \leq 2\times10^5$。

可以过，但是$k$一大就很慢。能不能再优化一些？

能。

思路：每拆一次，数组长度就会增加$1$。

那么，如果这一位拆完数组长度都不够的话，就把这一位一次拆完。

如果拆完了数组长度够，那么计算这一位拆出几可以正好让数组长度符合要求。

判断使用计算实现，复杂度$\Theta(1)$。

遍历$n$的每一位，理论复杂度为$\Theta(log_2n)$。

但是，$n$的二进制表示法最多30位。（因为$\lfloor log_210^9\rfloor =30$）

所以，可以把$\Theta(log_2n)$视为$\Theta(1)$。

又因直接把$n$的二进制表示法视为$30$位（加前导零）实现更方便，所以我的程序是基本用常数实现（除核心代码）。

* **无解情况是什么？**

本题存在无解情况。

所以，问题来了：如何判断无解？

看一看样例，$3$、$4$均为无解情况。

从样例$3$看出，如果$n<k$，那么即使把$n$拆成最小的$1$让数组长度最大也不够。

从样例$4$看出，如果$n$二进制表示法中$1$的个数大于$k$，那么数组最小长度都大于$k$，怎么也不能符合要求。

上面就是所有的无解情况。

* **【代码】**

```cpp
#include <iostream>

using namespace std;

int main(void)
{
	int num,exclen;
	cin>>num>>exclen;
	if(num<exclen)//无解情况一
	{
		cout<<"NO";
		return 0;
	}
	const int binarys[30]={536870912,268435456,134217728,67108864,33554432,16777216,8388608,4194304,2097152,1048576,524288,262144,131072,65536,32768,16384,8192,4096,2048,1024,512,256,128,64,32,16,8,4,2,1};//半打表
	int binnums[30]={},sum=0;
	for(int i=0;i<30&&num;i++)//把n拆成二进制
		if(num>=binarys[i])
			sum++,num-=binarys[i],binnums[i]=1;
	if(sum>exclen)//无解情况二
	{
		cout<<"NO";
		return 0;
	}
	int i=0;
	while(sum<exclen)//拆数部分
	{
		if(binnums[i]+sum<=exclen)
			binnums[i+1]+=binnums[i]*2,sum+=binnums[i],binnums[i]=0;
		else
			binnums[i+1]+=(exclen-sum)*2,binnums[i]-=exclen-sum,sum=exclen;
		i++;
	}
	cout<<"YES\n";//别忘了这个
	for(int i=29;i>=0;i--)//输出数组
		while(binnums[i]--)
			cout<<binarys[i]<<' ';
 	return 0;
}

```


---

## 作者：开始新的记忆 (赞：0)

题目大意：给你两个数n和k，让你用k个2的p次幂（1<=p<=32）的和变成n。
题目链接：[http://codeforces.com/problemset/problem/1095/C](http://codeforces.com/problemset/problem/1095/C)

大致思路：先把n转成二进制数，然后如果k有剩余，那么就把数组里不是1的数都除以2可分为两个e.g：
n=5 k=3，先分成101，记录4,1然后把4 /2，得2 2 1，发现到了k个，输出。

code：

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<vector>
#include<cmath>
#include<map>
using namespace std;
long long ans[100010],t=1,n,k,x;
long long num[100010],cnt=1;

void work(long long y)
{
    if(y==1)
    {
        cout<<1<<' ';
        return;
    }
    if(k==0)
    {
        cout<<y<<' ';
        return;
    }
    k--;
    work(y/2);work(y/2);
}

int main()
{	for(int i=0;i<=31;++i)
	{
		ans[i]=t;
		t*=2;
	}
	cin>>n>>k;
	if(k>n)
    {
        cout<<"NO"<<endl;
        return 0;
    }
    for(int i=0;i<=31;++i)
        if(ans[i]<=n && ans[i+1]>n)
        {
            x=i;
            break;
        }
    while(n)
    {
        while(n>=ans[x] && k>=0)
            num[cnt++]=ans[x],n-=ans[x],--k;
        if(k<=0 && n)
        {
            cout<<"NO"<<endl;
            return 0;
        }
        --x;
    }
    cout<<"YES"<<endl;
    for(int i=cnt-1;i>=1;--i)
    {
        if(k!=0)
            work(num[i]);
        else
            cout<<num[i]<<' ';
    }
    cout<<endl;
	return 0;
}
```


---

## 作者：Zechariah (赞：0)

先按二进制把这个数分解，然后从高位开始往下拆，拆出刚好k个数为止
```cpp
#include <bits/stdc++.h>
#define rg register
#define inl inline
typedef long long ll;
const int N = 1e5 + 10, mod = 998244353, oo = 0x3F3F3F3F3F3F3Fll;
using namespace std;
namespace fast_IO {
    long long read()
    {
        rg long long num = 0;
        rg char ch;
        rg bool flag = false;
        while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
        if (ch == EOF)return ch; if (ch == '-')flag = true; else num = ch ^ 48;
        while ((ch = getchar()) >= '0'&&ch <= '9')
            num = (num << 1) + (num << 3) + (ch ^ 48);
        if (flag)return -num; return num;
    }
    ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
    ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
    void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
};
int a[N];

int main()
{
    rg int n = fast_IO::read(), k = fast_IO::read(), minn = 0, maxn = n, tmp = n;
    while (tmp)tmp = tmp & tmp - 1, ++minn;
    if (k<minn || k>maxn) { puts("NO"); return 0; }
    puts("YES");
    for (rg int i = 0; i <= 30; ++i)
        if (n&(1 << i))a[i] = 1;
    for (rg int i = 30; i >= 1; --i)
        if (minn < k&&a[i] + minn <= k)a[i - 1] += a[i] << 1, minn += a[i], a[i] = 0;
        else if (minn < k)a[i - 1] += k - minn << 1, a[i] -= k - minn, minn = k;
    for (rg int i = 0; i <= 30; ++i)
        if (a[i])for (rg int j = 1; j <= a[i]; ++j)fast_IO::write(1 << i), putchar(' ');
    return 0;
}

```

---

