# [ABC129E] Sum Equals Xor

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc129/tasks/abc129_e

正整数 $ L $ が二進数表記で与えられます。 以下の条件を満たす非負整数 $ a,\ b $ の組 $ (a,\ b) $ がいくつ存在するか求めてください:

- $ a\ +\ b\ \leq\ L $
- $ a\ +\ b\ =\ a\ \text{\ XOR\ }\ b $

ただし、この値は非常に大きくなることがあるので、$ 10^9\ +\ 7 $ で割った余りを出力してください。

XOR とは

整数 $ A,\ B $ のビットごとの排他的論理和 $ a\ \text{\ XOR\ }\ b $ は、以下のように定義されます。

$ a\ \text{\ XOR\ }\ b $ を二進数表記した際の $ 2^k $ ($ k\ \geq\ 0 $) の位の数は、$ A,\ B $ を二進数表記した際の $ 2^k $ の位の数のうち一方のみが $ 1 $ であれば $ 1 $、そうでなければ $ 0 $ である。 例えば、$ 3\ \text{\ XOR\ }\ 5\ =\ 6 $ となります (二進数表記すると: $ 011\ \text{\ XOR\ }\ 101\ =\ 110 $)。

## 说明/提示

### 制約

- $ L $は二進数表記で与えられ、先頭文字は必ず $ 1 $ である
- $ 1\ \leq\ L\ <\ 2^{100,001} $

### Sample Explanation 1

条件を満たす $ (a,\ b) $ としては $ (0,\ 0),\ (0,\ 1),\ (1,\ 0),\ (0,\ 2),\ (2,\ 0) $ の $ 5 $ つが考えられます。

## 样例 #1

### 输入

```
10```

### 输出

```
5```

## 样例 #2

### 输入

```
1111111111111111111```

### 输出

```
162261460```

# 题解

## 作者：Acfboy (赞：17)

## 题意

以二进制形式给出一个整数 $L$ ，问有多少个非负整数对 $(a, b)$ 满足：$a+b = a \oplus b \le L$。答案对 $10^9+7$ 取模。

## 题解

首先，因为异或相比加法只能让两个一变成零，而不能产生新的一，所以不可以产生进位。

另 $f[i][1]$ 表示 $a+b$ 二进制前 $i$ 个刚好是 $L$ 的前 $i$ 位的方案数，$f[i][0]$ 是严格小于 $L$ 的方案数。

若 $L$ 当前位为 $1$, 那么恰好等于 $L$ 时， $a,b$ 可以分别填 $0, 1$ 或 $1, 0$， 所以 $f[i][1] = f[i-1][1] \times 2$。当前位为 $0$ 时 $f[i][1] = f[i-1][1]$ 。

考虑不严格小于的情况，若前面已经严格小于了，那么这一位可以随便填，不进位就行，有 $a,b$ 当前位为 $0,1|1,0 | 0,0$ 的三种情况，$f[i][0] = f[i-1][0] \times 3$, 还有一种情况是前面都相等，刚刚从这一位开始不相等，仅在 $L$ 当前位是 $1$ 时有这种情况，只能填 $0,0$, 所以此时 $f[i][0] = f[i-1][0] \times 3 + f[i-1][1]$

## 代码

代码很短，**只有 $9$ 行**。

```cpp
#include <cstdio>
long long f0 = 0, f1 = 1, p = 1000000007, s;
signed main() {
	while(scanf("%c", &s) != EOF && (s == '0' || s == '1')) {
		f0 = f0 * 3 % p;
		if(s == '1') f0 = (f0 + f1) % p, f1 = f1 * 2 % p;
	}
	printf("%lld", (f0+f1) % p);
}
```

~~我不会告诉你把 s 定义成 long long 仅仅是为了美观的。~~

---

## 作者：DengDuck (赞：6)

每一位其实只有$3$种决策，分别是： 

- 两个数字的这一位都是 0。
- $a$ 的这一位是 0，$b$ 的这一位是 1。
- $b$ 的这一位是 0，$a$ 的这一位是 1。

大家可能还想到了一个决策：两个数字的这一位都是 1，但是这样不对。

因为题面要求 $a+b=a \oplus b$，那么每一位的计算结果都应该是一样的。

如果两个都是 1，异或操作结果为 0，和操作却会进位，导致结果不一样。

在知道了这一点后，寻找两种操作的值相同的数字就不难了,接下来考虑大小限制。

对于最高位，我们有三种决策，也就是上面说的三种，我们来看一下每种对应个方案数是多少。

两个数字的这一位都是 0。那么，无论后面是什么，和绝对小于 $L$，原因显然，异或不会进位。

所以方案数就是 $3^{len-1}$，$len$ 表示 $L$ 的二进制位数。

两个数字一个这一位是 1，一个这一位是 0。那么，后面就不能随心所欲了，在后面的一段决策是固定的。

这一段就是这一位距离下一位 1 中间的一段 0。在这一段我们的决策一定是两个数字都是 0，否则显然会大于 $L$。

遇到下一个 1 的时候，我们又要做与最高位相同的选择了。

所以，我们将所有的 1 作为一个决策点，做 DP，从低位向高位转移。

设 $f_i$ 表示从高位往低位数第 $i$ 个 1,，往后有多少种方案。

$$
f_i=3^{n-x}+2\times f_{i+1};
$$


```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,pw3[100005],len,f[100005];
const long long mod=1e9+7;
char c[100005];
vector<long long>v;
int main()
{
	scanf("%s",c+1);
	n=strlen(c+1);
	pw3[0]=1;
	for(int i=1;i<=n;i++)
	{
		pw3[i]=pw3[i-1]*3;
		pw3[i]%=mod;
		if(c[i]=='1')v.push_back(i);
	}
	len=v.size();
	f[len]=1;
	for(int i=len-1;i>=0;i--)
	{
		long long x=v[i];
		f[i]=pw3[n-x]+2*f[i+1];
		f[i]%=mod;
	}
	printf("%lld",f[0]);
}
```

---

## 作者：high_sky (赞：3)

一看题目，就是一道 `dp` 题。

我们不妨来确定一个设数：设 $dp_{i,0/1}$ 表示前 $i$ 个数与 $l$ 前 $i$ 个数的关系，那就有两种情况：

* 如果 $j=0$ 则表示这前 $i$ 个数小于 $l$ 前 $i$ 个数。

* 如果 $j=1$ 则表示这前 $i$ 个数等于 $l$ 前 $i$ 个数。

那我们就可以得出两种情况：
* 如果 $l_i=1$ ，则:
    * $dp_{i,0}=dp_{i-1,0} \times 3 + dp_{i-1,1}$，解释：前一个的方案既然等于前 $l$ 的 $i$ 个数，那就有 $(1,0),(0,1),(0,0)$，三种情况，以及之前为等于它的前 $i$ 位有 $(0,0)$ 一种方法，因为 $(1,0),(0,1)$ 会使之相等，所以不行。
     
    * $dp_{i,1}=dp_{i-1,1} \times 2$，解释：只有两种方案，放 $(1,0),(0,1)$。
* 如果 $l_i=0$ ,则：
    * $dp_{i,0}=dp_{i-1,0}\times 3$，解释：三种方案，同上，只不过不能再之前相等的时候填 $(0,0)$ 会导致这个答案相等，不是 $dp_{i,0}$。
    * $dp_{i,1}=dp_{i-1,1}$，解释：之前相等了，只有一种方案 $(0,0)$，所以只有一个 $dp_{i-1,1}$。
    
### 代码
```cpp
#include<iostream>
#define int long long
using namespace std;
int n,dp[105000][2];
string s,s1;
const int mod=1e9+7;
signed main(){
	cin>>s1;
	n=s1.size();
	s=' ',s+=s1;
	dp[0][1]=1;//初始化
	for(int i=1;i<=n;i++){
		dp[i][0]=(dp[i-1][0]*3)%mod;
		if(s[i]=='1'){
			dp[i][0]=(dp[i][0]+dp[i-1][1])%mod;
			dp[i][1]=(dp[i-1][1]*2)%mod;
		}
		else dp[i][1]=dp[i-1][1];
	}
	cout<<(dp[n][0]+dp[n][1])%mod;
	return 0;
}
```

---

## 作者：YueYang1235 (赞：2)

[题目传送门](https://atcoder.jp/contests/abc129/tasks/abc129_e)
[同步于我的博客](https://blog.csdn.net/Yorug/article/details/119492001?spm=1001.2014.3001.5501)

## Describtion
以二进制给定一整数 $L$ ，求有多少二元组 $(a,b)$ 满足 $a+b=a\oplus b\leq L$ 。
## Solution

对 $a,b$ 的二进制形式的每一位进行讨论。

因为异或是不进位加法，所以 $a+b=a\oplus b$ 相当于 $a$ 和 $b$ 的同一位不能同为 $1$。

令 $dp[i][0]$ 为 $a\oplus b$ 的前 $i$ 位小于 $L$ 的前 $i$ 位的方案数，$dp[i][1]$ 则为等于的方案数。

 - $L$ 的当前位为 $1$。此时等于的情况为上一位等于且 $a,b$ 分别取 $1,0$ 和 $0,1$，即 $dp[i][1]=dp[i-1][1]\times2$。小于的情况有两种：上一位小于，则有 $3$ 种情况:$0,0$，$0,1$ 和 $1,0$ ；上一位等于的情况就 $1$ 种：$0,0$，即 $dp[i][0]=dp[i-1][0]\times3+dp[i-1][1]$。
 - $L$ 的当前位为 $0$。等于的情况为上一位等于且 $a,b$ 都取 $0$，即 $dp[i][1]=dp[i-1][1]$。小于的情况只有 $3$ 种，即上一位小于，$a,b$ 分别取 $0,0$，$0,1$ 和 $1,0$。
 
 
最终答案即为 $dp[n][1]+dp[n][0]$ ，$n$ 为 $L$ 的二进制位数。
 
 ## Code
 

```cpp
#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;
long long n,dp[105000][2];
char s[105000];
int main(){
	scanf("%s",s+1);
	n=strlen(s+1);
	dp[0][1]=1;//初始化
	for(int i=1;i<=n;++i){
		dp[i][0]=(dp[i-1][0]*3)%mod;
		if(s[i]=='1'){
			dp[i][0]=(dp[i][0]+dp[i-1][1])%mod;
			dp[i][1]=(dp[i-1][1]*2)%mod;
		}
		else dp[i][1]=dp[i-1][1];
	}
	printf("%lld\n",(dp[n][0]+dp[n][1])%mod);
	return 0;
}
```


---

## 作者：small_john (赞：1)

## 基本思路

因为 $a+b = a\oplus b$，有以下分析：

1. 当 $L_i$ 为 $0$ 时，$(a,b) = (0,0)$，共 $1$ 种情况；

2. 当 $L_i$ 为 $1$ 时，$(a,b) = (0,1)$ 或 $(1,0)$，共 $2$ 种情况。

---
$a+b\le L$ 分两种情况讨论：

1. 当 $a+b<L$ 时：对于一个任意是 $1$ 的位置 $i$，可以把 $L_i$ 变为 $0$，$L$ 中 $i$ 以后的位置可以是 $0$ 或 $1$，每位有 $3$ 种情况，则有：$ans = 2^k\times 3^{len-i-1}$，其中 $k$ 表示前 $i-1$ 位 $1$ 的个数，$len$ 表示 $L$ 的长度；

2. 当 $a+b=L$ 时，有 $ans = 2^k$，其中 $k$ 表示 $L$ 中 $1$ 的个数。

**注**：计算情况是要用**乘法原理**，~~这应该没人不知道，就当我啥也没说~~。

****

## 实现方法

$L$ 用字符串输入，用 $f_i$ 表示 $3^i$，$k$ 表示遍历到第 $i$ 位时前 $i-1$ 位的情况，$k$ 在循环结束后表示 $a+b=L$ 的情况，$ans$ 表示 $a+b<L$ 的情况，输出时表示总情况数。

先输入。
### code:
```cpp
getline(cin,s);//可以用cin，但getline是string的专属，没bug
```

然后预处理 $f$ 数组，记得初始化 $f_0=1$。

### code:
```cpp
f[0] = 1;
for(int i = 1;i<=s.size();i++)
	f[i] = (f[i-1]*3)%mod; 
```

接下来遍历 $L$，如果 $L_i=1$ 那就执行操作。

### code:
```cpp
for(int i = 0;i<s.size();i++) 
	if(s[i]=='1')
		ans = (ans+f[s.size()-i-1]*k)%mod,k = (k*2)%mod;
```

最后处理以下 $ans$，输出就行了
### code:
```cpp
ans+=k,ans%=mod;//原来ans是严格小于l的情况，加上严格等于的情况才是小于等于的情况 
printf("%lld",ans);
```

****

## 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7,N = 1e5+5;
string s;
long long f[N] = {1},k = 1,ans;//开long long的好习惯 
int main()
{
	getline(cin,s);//可以用cin，但getline是string的专属，没bug
	for(int i = 1;i<=s.size();i++)
		f[i] = (f[i-1]*3)%mod; 
	for(int i = 0;i<s.size();i++) 
		if(s[i]=='1')
			ans = (ans+f[s.size()-i-1]*k)%mod,k = (k*2)%mod;
	ans+=k,ans%=mod;//原来ans是严格小于l的情况，加上严格等于的情况才是小于等于的情况 
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：zesqwq (赞：1)

# AT4759 [ABC129E] Sum Equals Xor 题解

[题目传送门](https://www.luogu.com.cn/problem/AT4759)

非常基础的一道数位 $\text{dp}$。

用 $f_{i,j}$ 表示考虑到第 $i$ 位，前面从高位到当前数位是否比给定数的这几位小，因此，$j$ 是一个 $\text{bool}$ 值。

考虑转移，$a+b=a \oplus b$ 的条件是：$a$ 和 $b$ 的二进制表示下没有一位都是 $1$。因为在二进制下 $1 + 1 = 10$，而 $1 \oplus 1 = 0$。

那么我们就可以枚举现在决策的数位是 $01$ 还是 $00$，具体来说，就是：

$$f_{i,j} = \begin{cases}
   f_{i-1,j} &\text{if } [j = 1] \operatorname{and} [num_i = 1] \\
   f_{i-1,0}+f_{i-1,j \operatorname{and} [num_i = 1]} &\text{otherwise}
\end{cases}$$

其中 $num_x$ 表示数的从低到高的第 $x$ 位。

$\text{Code:}$

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, P = 1e9 + 7;
long long f[N][2];
char num[N];
long long dfs(int n, bool isup) {
    if (!n) return 1;
    if (~f[n][isup]) return f[n][isup];
    if (isup && num[n] == '0')
        f[n][isup] = dfs(n - 1, isup);
    else
        f[n][isup] = ((dfs(n - 1, isup && num[n] == '1') << 1) % P + dfs(n - 1, 0)) % P;
    return f[n][isup];
}
int main() {
    memset(f, -1, sizeof(f));
    scanf("%s", num + 1);
    int f = strlen(num + 1);
    for (int i = 1; i <= (f >> 1); i++) swap(num[i], num[f - i + 1]);
    cout << dfs(f, 1);
    return 0;
}
```



---

