# [PFOI Round1] 暴龙的火锅

## 题目背景

暴龙爱吃火锅。

## 题目描述

定义 $S(x)$ 表示 $x$ 的每一位的数字之和，例如：$S(14)=1+4=5$，$S(114514)=1+1+4+5+1+4=16.$

另外，定义 $fib(x)$ 代表斐波那契数列的第 $x$ 项，具体地：

$$fib(1)=fib(2)=1,\ fib(x)=fib(x-1)+fib(x-2)\ (x≥3).$$

现在给定 $n$，求出下式的值，其中 $\bmod 9$ 表示对 $9$ 取余数：

$$(S(fib(1))+S(fib(2))+S(fib(3))+...+S(fib(n))) \bmod 9.$$

## 说明/提示

【样例解释】

对于第一组询问，$n=7$，答案为： 

$$
\begin{aligned}
& \ \ \ \ \ (S(fib(1))+S(fib(2))\ldots+S(fib(6))+S(fib(7)))\bmod 9 \\
& =(1+1+2+3+5+8+(1+3))\bmod 9 \\
& =6.
\end{aligned}
$$

---

【数据范围】

**「本题采用捆绑测试」**

- $\texttt{Subtask 1(10 pts)：}T=1,\ n\le 10$；
- $\texttt{Subtask 2(30 pts)：}T=10^2,\ n\le 10^3$；
- $\texttt{Subtask 3(60 pts)：}$无特殊限制。

对于 $100\%$ 的数据，满足 $1\le T\le 10^5,\ 1\le n\le 10^6$。

## 样例 #1

### 输入

```
3
7
14
114514```

### 输出

```
6
5
8```

# 题解

## 作者：chen_zhe (赞：36)

首先要知道一个结论：一个正整数对 $9$ 取余的结果就是它各位数之和对 $9$ 取余的结果。证明如下：

一个 $n$ 位的正整数 $a$ 可以被表示为 $a_1 \times 10^{n-1}+a_2 \times 10^{n-2}+\dots+a_n \times 10^0$

因为 $(a \times b) \bmod c=(a \bmod c \times b \bmod c) \bmod c$，则有 $10^k \bmod 9=(10 \bmod 9)^k \bmod 9=1$。

又因为 $(a+b) \bmod c=(a \bmod c+b \bmod c) \bmod c$

从而 $a \equiv (a_1+a_2+\dots+a_n) \pmod 9$。

这样一来，题面中的 $S(x) \equiv x \pmod 9$。从而我们相当于只需求出斐波那契数列的每一项对 $9$ 取模的结果，然后做前缀和即可完成本题。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <queue>
#include <vector>

using namespace std;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

int t,fib[1000055];

int main()
{
	cin >> t;
	fib[1]=fib[2]=1;
	for (int i=3;i<=1000050;i++)
		fib[i]=(fib[i-2]+fib[i-1])%9;
	for (int i=1;i<=1000050;i++)
		fib[i]=(fib[i]+fib[i-1])%9;
	while (t--)
	{
		int n;
		cin >> n;
		cout << fib[n] << endl;
	}
	return 0;
}
```

---

## 作者：wangzl (赞：12)

### 更新日志 
[2022/7/16] 更新了核心代码的复杂度 $O(1)$ 的 $\text{std}_2$
## 简要题意  

定义 $S(x)$ 表示 $x$ 的每一位的数字之和，例如：$S(14)=1+4=5$，$S(114514)=1+1+4+5+1+4=16.$

另外，定义 $fib(x)$ 代表斐波那契数列的第 $x$ 项，具体地：

$$fib(1)=fib(2)=1,\ fib(x)=fib(x-1)+fib(x-2)\ (x\ge3).$$

现在给定 $n$，求出下式的值，其中 $\bmod 9$ 表示对 $9$ 取余数：

$$(S(fib(1))+S(fib(2))+S(fib(3))+...+S(fib(n))) \bmod 9.$$

## 基本思路

我们看到题目要求的数据范围：  
>对于 $100\%$ 的数据，满足 $1\le T\le 10^5,\ 1\le n\le 10^6$。   

所以，我们首先想到的应该是一道找规律或者找通项公式的题，使用 $O(T)$ 的方法求解，对于每一个数据 $n$ ，使用 $O(1)$ 的方法求解。   
因为： $(S(fib(1))+S(fib(2))+S(fib(3))+...+S(fib(n))) \bmod 9$ 的值等于 $(S(fib(1))\bmod 9+S(fib(2))\bmod 9+S(fib(3))\bmod 9+...+S(fib(n))\bmod 9)$ 。  
我们过列举发现对于 $S(fib(i))\bmod 9$ 会成一定规律的出现。我们用 $spa_i$ 表示 $S(fib(i))\bmod 9$ 的值，可以列举，$spa$ 呈现一定的循环性规律，每 $24$ 次为一个循环，所以我们进行一下**预处理**：  
```cpp
spa[24] = {0, 1, 1, 2, 3, 5, 8, 4, 3, 7, 1, 8, 0, 8, 8, 7, 6, 4, 1, 5, 6, 2, 8, 1};
```
而且，我们发现 $\sum\limits_{i=0}^{23}spa_i\bmod9=0$ 所以，对于每一个循环节的总值为零，我们只需要求出 $\sum\limits_{i=0}^{n\bmod24}spa_i\bmod9$ 即是正确答案。
## $\text{std}_1$:
```cpp
#include <bits/stdc++.h>

using namespace std;
int n, data;
const int spa[] = {0, 1, 1, 2, 3, 5, 8, 4, 3, 7, 1, 8, 0, 8, 8, 7, 6, 4, 1, 5, 6, 2, 8, 1, 0};
int main() {
	scanf("%d", &n);
	while (n--) {
		scanf("%d", &data);
		int a = data % 24, ans = spa[a];
		while(a--) ans = (ans + spa[a]) % 9;
		printf("%d\n", ans);
	}
	return 0;
}
```
当然，我们也可以用 $s_x$ 储存 $\sum\limits_{i=0}^{x}spa_i\bmod9$的值，这样就可以不用代码里的 `while` 循环了。
## $\text{std}_2$:
```cpp
#include <cstdio>
//#define scanf scanf_s
using namespace std;
int n, data;
//const int spa[] = {0, 1, 1, 2, 3, 5, 8, 4, 3, 7, 1, 8, 0, 8, 8, 7, 6, 4, 1, 5, 6, 2, 8, 1, 0};
const int s[] = {0, 1, 2, 4, 7, 3, 2, 6, 0, 7, 8, 7, 7, 6, 5, 3, 0, 4, 5, 1, 7, 0, 8, 0, 0};
int main() {
    scanf("%d", &n);
    while (n--) {
        scanf("%d", &data);
        printf("%d\n", s[data % 24]);//核心代码O(1)
    }
    return 0;
}
```


---

## 作者：Abeeel51 (赞：11)

[题目传送门](https://www.luogu.com.cn/problem/P8377)

首先看题：

答案是斐波那契数列前 $n$ 项的各个数位之和相加取余 $9$ 的结果。

做这道题，首先要知道一个定理，一个数的各个位数之和取余 $9$ 与这个数取余 $9$ 的结果一样。

其实这只是小学奥数，~~大家都忘了~~，那我来讲一讲。

把一个两位数（假设）看成 $ab$，

则各个位数相加的和除以 $9$ 就是 $\frac{a+b}{9}$。

这个数除以 $9$ 就是 $\frac{10a+b}{9}$

所以，这个数除以 $9$ 比各个数位之和除以 $9$ 多了 $9a$，而 $9a$ 就是 $9$ 的 $a$ 倍，所以这两个余数是相等的。

那么，根据这个我们就可以得出代码步骤：

先求出斐波那契数列，接着根据斐波那契数列求出前 $i$ 项取余 $9$ 的结果，最后 $t$ 组 $n$ 输出 $sum_n$ 就可以了。

代码只给出关键部分，不要抄袭哦！

```cpp
for(int i=3;i<=MAXN-1;i++) a[i]=(a[i-1]+a[i-2])%mod;
for(int i=2;i<=MAXN-1;i++) a[i]=(a[i-1]+a[i])%mod;
```

留个赞再走吧。

---

## 作者：xiaohaoaibiancheng66 (赞：5)

# 思路
首先用暴力的时间复杂度为 $O(Tn\log n)$ 会超时。

所以要优化亿下下。

首先要知道一个结论 $S(x) \bmod 9=x \bmod 9$。

因为对于任意一个 $n$ 位数 $a$ 都有 $a=a_1 \times 10^n+a_2 \times 10^{n-1}+⋯+a_n \times 10^0$。

而 $(a \times b)\bmod c=(a\bmod  c \times b $ $\bmod  c)\bmod c$ 可以推出 $10^k \bmod 9={(10 \bmod 9)}^k \bmod 9=1$。

同理，$(a + b)\bmod c=(a\bmod  c + b $ $\bmod  c)\bmod c$ 可以推出 $a \bmod 9=(a_1+a_2+⋯+a_n)\bmod 9$。

这样可以把时间复杂度降到 $O(Tn)$。

但这样还不够，还得继续优化。

可以用预处理的方式现将每个 $n$ 的结果储存在数组中，直接调用即可。时间复杂度为 $O(T+n)$，可以通过。
# $AC code$
```cpp
#include<bits/stdc++.h>
using namespace std;

int f[1000000+10],c[1000000+10];

int main()
{
	//预处理
	f[1]=f[2]=1;
	c[1]=1,c[2]=2;
	for(int i=3;i<=1000000;i++)
	{
		f[i]=(f[i-1]+f[i-2])%9;
		c[i]=(c[i-1]+f[i])%9;
	}
    
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		cout<<c[n]<<endl;
	}
	return 0;
}
```


---

## 作者：_xxy_ (赞：3)

因为要调高考假期，学校端午节不放假，只能赛后写题解（其实是为了咕值）

可以观察到 $ n $ 最大有 $ 1000000 $ ，暴力求数字和肯定不行，可以发现，将一个数加上另一个数，所得的数的数位之和等于原来两数的数位之和相加减去 $ x $ 个 $ 9 $ （满 $ 10 $ 进 $ 1 $ ，数位之和便减少了 $ 9 $ ），于是再将这些斐波那契数的数位之和对 $ 9 $ 取模，就变成了斐波那契数列的每一项对 $ 9 $ 取模的结果，如果觉得抽象，可以运行下面这段代码。

```cpp
#include<cstdio>
using namespace std;
int num(long long x){
	int ans=0;
	while(x){
		ans+=x%10;
		x/=10;
	}
	return ans;
}
long long f[55]={0,1,1};
int main(){
	for(int i=3;i<=52;i++){
		f[i]=f[i-1]+f[i-2];
	}
	for(int i=1;i<=52;i++) printf("%lld\n",f[i]);
	printf("\n");
	for(int i=1;i<=52;i++) printf("%lld\n",num(f[i]));
	printf("\n");
	for(int i=1;i<=52;i++) printf("%lld\n",num(f[i])%9);
	return 0;
}
```

然后就可以写出正解了，注意要用前缀和优化。

**Code:**

```cpp
#include<cstdio>
using namespace std;
int f[1000005]={0,1,1},ans[1000005]={0,1,2};
int main(){
	for(int i=3;i<=1000000;i++){
		f[i]=(f[i-1]+f[i-2])%9;
		ans[i]=(ans[i-1]+f[i])%9;
	}
	int t;
	scanf("%d",&t);
	while(t--){
		int n;
		scanf("%d",&n);
		printf("%d\n",ans[n]);
	}
	return 0;
}
```

---

## 作者：Infinity_G (赞：3)

# 题目描述
定义 $S(x)$ 表示 $x$ 的每一位的数字之和，$\mathrm{fib}(x)$ 代表斐波那契数列的第 $x$ 项。给定 $n$，求 $\sum\limits_{i=1}^nS(\mathrm{fib}(i))\mod 9$。
# 题解
学过小奥的都知道 $S(x)\equiv x(\mathrm{mod}\;9)$，所以等价于求 $\sum\limits_{i=1}^n\mathrm{fib}(i)\mod 9$。

然后我们打个表，

![](https://cdn.luogu.com.cn/upload/image_hosting/i0fd1ah1.png)

发现每 $24$ 个数为一个周期，然后我们再算一下 $p_i=\sum\limits_{k=1}^i\mathrm{fib}(k)$，

![](https://cdn.luogu.com.cn/upload/image_hosting/9x5hi2fe.png)

这题就做完了。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int p[]={0,1,2,4,7,3,2,6,0,7,8,7,7,6,5,3,0,4,5,1,7,0,8,0};
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		printf("%d\n",p[n%24]);
	}
	return 0;
}
```

---

## 作者：_JF_ (赞：3)

# **[PFOI Round1] 暴龙的火锅**

这一题就是一个模拟题....

首先我们先预处理出斐波那契数组，注意要取余 $9$ （不然就会爆掉）。

斐波那契通项公式： $fib[i]=fib[i-1]+fib[i-2]$

其次就是我们的 $a$ 数组了，就是答案。只要 $(a[i-1]+fib[i])\%9$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1000010;
#define int long long
int fib[N],a[N];
signed main()
{
	/*int k=pow(10,6)+1;
	int fib[k];
	*/
	fib[1]=1,fib[2]=1;
	a[1]=1;a[2]=2;
	for(int i=3;i<=pow(10,6)+1;i++)
		fib[i]=(fib[i-1]+fib[i-2])%9,a[i]=(a[i-1]+fib[i])%9;
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		cout<<a[x]<<endl;
	}
	return 0;
}
```


---

## 作者：封禁用户 (赞：2)

本题巨简单推柿子。

大家可以大概把 $n$ 从 $1 \sim 30$ 都试一下就可以发现本题的巨简单周期规律。

小提示：可以不算外边那个 $S$，因为可以看成

$$\begin{matrix}
((S(fib(1))\mod 9+S(fib(2))\mod 9+S(fib(3))\mod 9+\cdots+S(fib(n))\mod 9) \mod 9
\end{matrix}$$

我们知道，模 $9$ 也就是求数字和，而 $S$ 和此简便算法相同，所以可以直接算

$$\begin{matrix}
(fib(1)+fib(2)+fib(3)+\cdots+fib(n)) \mod 9
\end{matrix}$$

你也可以在 $fib(i)$ 后面也模一下 $9$ 防止溢出。

-----

然后就好算了，更简单的方式是写一个打表程序，如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

int _6872_[50] = {0, 1, 1}; // 斐波那契数列

void f(){ for (int i = 3; i <= 30; i ++) _6872_[i] = _6872_[i - 1] + _6872_[i - 2]; } // 生成

int hotpot(int n){ 
    int sum = 0;
    for (int i = 1; i <= n; i ++) sum += (_6872_[i] % 9), sum %= 9; // 生成“火锅”（话说背景和题目感觉没啥关系 AwA
    return sum % 9; // 多模几遍（ owo
}

int main(){
    for (int i = 0; i <= 30; i ++) cout << hotpot(i) << endl;
    return 0;
}
```

然后你可以得到一串数字，然后可以发现 $24$ 个一组，有周期规律，如果不太放心可以去打一个 $50$ 的表。

然后就是代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int _6872_[30] = {0,1,2,4,7,3,2,6,0,7,8,7,7,6,5,3,0,4,5,1,7,0,8,0,0};
// 周期

int main(){
	int Sestt;
	scanf("%d", &Sestt);
	while (Sestt --){
		int RzAKIOI;
		scanf("%d", &RzAKIOI);
		printf("%d\n", _6872_[RzAKIOI % 24]);
	}
	return 0;
} 
```

这篇题解就到这里，谢谢大家的耐心观看。

---

## 作者：nullqtr_pwp (赞：2)

# P8377 题解
首先，对于一个数的数字之和，显然 $x\equiv S(x)\mod(9)$，原因：利用位值原理将 $x$ 展开，将每一个都减去一，剩下的部分就显然是 $9$ 的倍数，而减去的那个一即为原数的数字之和。

那么原问题就转化成了求斐波那契数列的前缀和模 $9$，打一个表就过了。打表发现答案数组是一个长度为 $24$ 的循环。

赛时代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	register int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x*f;
}
int t,n,ans[100]={0,1,2,4,7,3,2,6,0,7,8,7,7,6,5,3,0,4,5,1,7,0,8,0};
int main(){
	t=read();
	while(t--){
		n=read();
		printf("%d\n",ans[n%24]);
	}
}
```


---

## 作者：sixrc (赞：2)

令 $s(x)$ 为 $x$ 的各位数字之和，我们在小学校内学过 $x$ 与 $s(x)$ 是关于 $9$ 同余的，也就是说题目中的 $S$ 函数是用来骗人的。根据余数的可加性，只要这个数列相邻两个数都曾经出现过，那么我们就找到了一个周期。不难发现这个周期一定是存在的，然后手推一下就会发现周期是 $24$，也就是说，$n=25$ 的答案和 $n=1$ 的答案是一样的。于是就做完了。

### Code：
```c++
#include <bits/stdc++.h>
using namespace std;
int t, n, a[50];
int main(){
	scanf ("%d", &t);
	a[1] = 1, a[2] = 1;
	for (int i=3; i<=30; i++){
		a[i] = (a[i-1] + a[i-2]) % 9;
	}
	for (int i=1; i<=30; i++){
		a[i] += a[i-1];
		a[i] %= 9;
	}
	for (int i=1; i<=t; i++){
		scanf ("%d", &n);
		printf ("%d\n", n<=24?a[n]:a[n%24]);
	}
	return 0;
}

```


---

## 作者：V1mnkE (赞：1)

首先我们知道 $S(x)\bmod 9=x\bmod 9$，这个证明用小学奥数的位值原理展开即可。由于 $n\leq 10^6$，数组开的下，我们可以开一个数组，用 $a_i$ 表示 $\sum_{j=1}^i j\bmod 9$，这个预处理出来之后觉可以对于每次询问，直接输出 $a_n$。

## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int a[1000005]={0,1,1},sum[1000005]={0,1,2},tot;
void init(int x){
	for(int i=3;i<=x;i++){
		a[i]=a[i-1]+a[i-2];
		a[i]%=9;
		sum[i]=sum[i-1]+a[i];
		sum[i]%=9;
	}
}
int t,n;
int main(){
	scanf("%d",&t);
	init(1000000);
	while(t--){
		scanf("%d",&n);
		printf("%d\n",sum[n]);
	}
	return 0;
}
```

---

## 作者：Jasper08 (赞：1)

## 题目分析

首先我们需要知道 [同余式的性质](https://baike.baidu.com/item/%E5%90%8C%E4%BD%99%E5%BC%8F/6024642?fr=aladdin#2) 。

**定理1** $S(x)\equiv x\pmod{9}$ .

设 $x=\overline{x_n...x_3x_2x_1}=10^{n-1}x_n+...+10x_2+x_1$ .

因为 $10\equiv 1\pmod{9}$ ，所以 $10^{k}\equiv1^{k}\pmod{9}$ .

所以 $x\equiv x_n+...+x_2+x_1\pmod{9}$ ，即 $S(x)\equiv x\pmod{9}$ .

**定理2** $S(x)+S(y)\equiv S(x+y)\pmod{9}$ .

根据 **定理1** , $S(x)\equiv x\pmod{9}$ . 同理，$S(y)\equiv y\pmod{9}$ , $S(x+y)\equiv x+y\pmod{9}$ .

所以 $S(x)+S(y)\equiv x+y\equiv S(x+y) \pmod{9}$ .

根据 **定理2** ，可知 $S(fib(1))+S(fib(2))+S(fib(3))+...+S(fib(n))\equiv S(fib(1)+fib(2)+...+fib(n))\pmod9$ .

到这里思路就很清晰了：用递推求出斐波那契数列的前 $10^6$ 项，同时用类似前缀和的方法计算 $S(1)\sim S(10^6)$ .

## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1e6 + 10;

int fib[N], s[N]; 
//fib[i] 表示斐波那契数列的第 i 项 % 9 的值，s[i] 表示 (fib[1]+fib[2]+...+fib[n]) % 9

int main() {
    int t;
    scanf("%d", &t);
	  
    //初始化
    fib[1] = 1; 	
    fib[2] = 1;
    s[1] = 1;
    s[2] = 2;
    
    for (int i = 3; i <= N; ++i) {
        fib[i] = (fib[i-1] + fib[i-2]) % 9; //递推计算
        s[i] = (s[i-1] + fib[i]) % 9; //类似前缀和
    }

    while (t --) {
        int n;
        scanf("%d", &n);
        printf("%d\n", s[n]);
    }

    return 0;
}
```

---

## 作者：lyhqwq (赞：1)

### 思路
经典（也许？）trick

看到数据范围就知道这是一道结论题

题目让我们求的是

$\sum_i^n \operatorname{S} ( \operatorname{fib}(i) ) ( \bmod 9 )$

注意到

$\operatorname{S} (i) \equiv i ( \bmod 9)$

所以我们可以把式子化简为

$\sum_i^n \operatorname{fib} (i) ( \bmod 9 )$

之后我们写一个打表程序

```cpp
printf("1 1 ");
ll a=1,b=1,c=0;
ll t=90;
while(t--){
	c=a+b;
	a=b;
	b=c;
	printf("%d ",c%9);
}
```
可以发现 $\operatorname{fib} (i) ( \bmod 9 )$ 是有循环节的

可以得到循环节为

```
1 1 2 3 5 8 4 3 7 1 8 0 8 8 7 6 4 1 5 6 2 8 1 0
```

所以说我们可以先计算 $n$ 中有多少个循环节，在计算其余零散的部分

但是循环节的和是 $99$ ，而 $99 \equiv 0 ( \bmod 9 )$

所以我们只需要计算零散的部分即可

### ACcode

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll t,n;
ll sum[]={0,1,2,4,7,3,2,6,0,7,8,7,7,6,5,3,0,4,5,1,7,0,8,0,0};
int main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);
		printf("%lld\n",sum[n%24]);
	}
}
```


---

## 作者：gyc18 (赞：0)

本题解为官方题解

由于斐波那契数列增长速度很快，不能把每一项的具体数值求出来。

所以考虑从余数下手。

众所周知，一个数除以 $9$ 的余数等于这个数每一位的数字和除以 $9$ 的余数。

所以这题就转化为求数列前 $n$ 项的每一项除以 $9$ 的余数的和。

我们就可以预处理出斐波那契数列数列然后统计一下前缀和。

---

## 作者：songhx (赞：0)

思路就是找规律。

列一下前几项，就找到了周期，共 $24$ 项。

	斐波那契数列数字和对九取模：1,1,2,3,5,8,4,3,7,1,8,0,8,8,7,6,4,1,5,6,2,8,1,0,1,1,2,3,5,8,4,3,7,1,8,0,8,8,7,6,4,1,5,6,2,8,1,0……
    
不妨将上面的序列叫做 $f$ ，然后计算答案数列 $p$ ，

$p_0=0, p_i=(p_{i-1}+f_i)\text{ mod 9, }$ $(i\ge 1)$ 。

	p数列:1,2,4,7,3,2,6,0,7,8,7,7,6,5,3,0,4,5,1,7,0,8,0,0,1,2,4,7,3,2,6,0,7,8,7,7,6,5,3,0,4,5,1,7,0,8,0,0
    
不难发现 $p$ 数列和 $f$ 数列的周期相同，都是 $24$ 项。

最后把 $p$ 数列的前 $24$ 项存入数组，每次取模输出即可。
    
$\color{green}{AC}\color{black}\text{code}$:

```cpp
#include <iostream>
using namespace std;
int main(int argc, char *argv[]) {
	int T;
	int lis[40] = {0,1,2,4,7,3,2,6,0,7,8,7,7,6,5,3,0,4,5,1,7,0,8,0}; //注意，把最后一项提前方便取模输出
	cin >> T;
	while(T--){
		int n;
		cin >> n;
		cout << lis[n % 24] << endl;
	}
	return 0;
}
```



---

## 作者：RNTBW (赞：0)

### 序
几年没见过这么水的 A 题了。

又是 AC 完 A 题就走的一天...
## 题意（简化后）
- 求 $\sum_{i=1}^n s_i$，其中 $s_i$ 是斐波那契数列的第 $i$ 个数的每一位的和。

- $n \leqslant 10^6$。

- 答案对 9 取模。
## 思路

~~斐波那契数列怎么求就不用说了吧。~~

但是 $10^6$ 的数据，直接求斐波那契肯定不行。

其实，这数据还为我们简化了代码。

我们直接求斐波那契数列每个数的位数和，最后再求一遍前缀和即可。

递归或者循环都可以。

**递归要加记忆化！**

由于在 $10^6$ 以内的每个正整数都只会被递归一次，所以时间复杂度为线性级。

## 正确代码
就将斐波那契部分奉上就可以了。
```cpp
ll gw(ll x)
{
	ll s=0;
	while(x) s+=x%10,x/=10;
	return s;
}//求位数
ll fibo(ll i)
{
	if(i==1||i==2)return f[i]=1;
	if(f[i])return f[i];//一定要加这句话！
	return f[i]=gw(fibo(i-1)+fibo(i-2));//直接求位数和
}
```

---

## 作者：Asimplename (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P8377)

### 题目大意

求出斐波那契数列 $1$ 到 $n$ 项的数字和之和 $\bmod ~9$ 后的结果。


### 思路

根据 $(a+b)\bmod c = (a \bmod c + b \bmod c) \bmod c$，可以将题目所给公式转化成：

$S(fib(1)) \bmod 9 + S(fib(2))\bmod 9 + ... + S(fib(n)) \bmod 9$

再根据任意正整数取模 $9$ 等于其各个数位上数字的和取模 $9$（详见题解最后的证明部分），可以进一步转化成：

$fib(1) \bmod 9 + fib(2) \bmod 9 + ... + fib(n) \bmod 9$

所以只需要预处理斐波那契数列各项取模 $9$，然后对预处理后的数列各项求前缀和，查询时直接输出即可。

### 代码

```cpp
#include<iostream>
using namespace std;
int t = 0;
int n = 0;
int ans = 2;
int sum[1000010];//前缀和数组
void Init(){
	int a = 1;
	int b = 1;
	int c = 0;
	sum[1] = 1;
	sum[2] = 2;
	for(int i = 3; i <= 1000000; i ++){
		c = a + b;
		c %= 9;
		a = b;
		b = c;
		sum[i] = (sum[i - 1] + c) % 9;
	}
}
int main () {
	Init();
	cin >> t;
	for(int i = 1; i <= t; i ++){
		cin >> n;
		cout << sum[n] << endl;
	}
	return 0;
}

```

### 证明


对于任意一个正整数 $a$，可以将其拆分为：

$(a \bmod 10) \times 10 + (a \mid 10 \bmod 10) \times 10 + (a \mid 100 \bmod 10) \times 10 + ... $

对于其中的 $\times 10$，取模 $9$ 后为 $1$，这个式子也就相当于：

$(a \bmod 10) + (a \mid 10 \bmod 10) + (a \mid 100 \bmod 10) + ... $

而其中括号内的数之和恰好是 $a$ 的数位和，也就是说如果一个数的数位和能整除 $9$，那这个数就能整除 $9$。也就说明任意正整数取模 $9$ 等于其各个数位上数字的和取模 $9$。

---

