# SNGPG - Prime Generator The Easiest Question Ever

## 题目描述

给定区间 $[a, b]$，求该区间中满足 $p^2 + 1$ 或 $p^2 + 2$ 为质数的质数 $p$ 的数量。特别地，我们认为 $0$ 和 $1$ 也为质数。

## 说明/提示

对于 $100\%$ 的数据，$1 \leq T < 100$，$0 \leq a \leq 5 \times 10^4$，$1 \leq b \leq 10^5$，$a < b$。

## 样例 #1

### 输入

```
2\n0 1\n4 5```

### 输出

```
2\n0\n\n[Consider 0 and 1 as prime numbers for this question]```

# 题解

## 作者：Kreado (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/SP15891)

此题非常简单，一分钟切没问题。

#### 思路

我们可以讨论一下当 $p$ 为质数时的性质：

要使得 $p^2+1$ 为质数，当且仅当 $p$ 为偶数时，所以这种情况 $p$ 的值只能为 $2$。


要使得 $p^2+2$ 为质数，因为 $p^2 \equiv1 \pmod 3$，所以 $p=3k+1(k>0)$。

即 $p^2+2=9k^2+6k+3=3(3k^2+2k+1)$，所以这种情况 $p$ 的值只能为 $3$。

即对答案有贡献的仅有 $0,1,2,3$，所以答案为 $\max(\min(b,3)-a+1,0)$。

---

## 作者：very_easy (赞：1)

这题可以写一个质数筛，那就会有~~聪明~~的小朋友问了，什么是质数筛？

质数筛又叫埃氏筛，原理如下：

如果当前数还未被标记，则将该数所有的倍数标记。

但是埃氏筛也有一个缺陷：

如举例 $12$ 这个数，在第一次被 $2$ 筛了一遍，又被 $3$ 筛了一遍，就会导致一个数有可能会被很多数筛掉，所以就有了[欧拉筛](https://blog.csdn.net/qaqwqaqwq/article/details/123587336)，有兴趣的可以自己去了解一下。

不过本题数据较小用埃氏筛就可以了，所以这题也就成了一道水题。

# 代码

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int prime[N];//标记质数 
void p(){
	for(int i=2;i<=N;i++){//从2开始,0和1默认为0 
		if(!prime[i]){
			for(int j=i+i;j<=N;j+=i){
				prime[j]=1;//将当前数的倍数全部标记 
			}
		}
	}
} 
int main(){
	p();
	int t;
	cin>>t;
	while(t--){
		int a,b,cnt=0;
		cin>>a>>b;
		for(int i=a;i<=b;i++){
			if(prime[i]==0&&(prime[i*i+1]==0||prime[i*i+2]==0)){
				cnt++;//超级简单不过多赘述 
			}
		}
		cout<<cnt<<endl;
	}
	return 0;
}


```
最后说一句，那个欧拉筛的详解不是我写的，要感谢大佬。

---

## 作者：luuia (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/SP15891)

## 前置知识：

Q : 什么是质数(素数)？

A : 质数(素数)是指在大于 $1$ 的自然数中，除了 $1$ 和它本身以外不再有其他因数的自然数，例如 $2,3,5,7$ 等等。

Q：如何筛选素数？

A：一个简单的算法是筛选法。筛选法的具体做法是先把前$n$个数字从大到小排列起来。

比如：$1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22$

首先排除 $1$，$1$ 后面的第一个数是 $2$，那么把 $2$ 的所有倍数都去掉，变成下面这样：

$2,3,5,7,9,11,13,15,17,19,21$ 

$2$ 后面的第一个数是 $3$，继续同样划去 $3$ 的所有倍数，变成下面这样：

$2,3,5,7,11,13,17,19$

同理，继续划 $5,7,11,13,17,19$ 的倍数，但是由于这些数的倍数已经都被划去或不在这个序列中，那么我们便得到了这个序列中的质数。

当然，这个方法的时间复杂度还比较高，那么有没有更快的算法呢？

 **答案是：有。**

下面介绍两种算法：埃氏筛法和欧拉筛法。

### 埃氏筛法 $O(n\log({\log}n))$

首先，我们列出 $2$ 以后的我们要筛选的数的序列：

$2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23$

标出序列中的第一个素数，也就是 $2$ ，序列变成：

$2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23$

将剩下序列中，划掉 $2$ 的倍数，序列变成：

$2,3,5,7,9,11,13,15,17,19,21,23$

如果这个序列中最大数小于最后一个标出的素数的平方，那么剩下的序列中所有的数都是素数，否则回到第二步。

本例中，因为 $23$ 大于 $2$ 的平方，我们返回第二步：

剩下的序列中第一个素数是 $3$，将主序列中 $3$ 的倍数划掉，主序列变成：

$2,3,5,7,11,13,17,19$

我们得到的素数有：$2$，$3$

$25$ 仍然大于 $3$ 的平方，所以我们还要返回第二步：

序列中第一个素数是 $5$，同样将序列中 $5$ 的倍数划掉，主序列成了$2,3,5,7,11,13,17,19,23$

我们得到的素数有：$2,3,5$ 。

因为 $23$ 小于 $5$ 的平方，跳出循环。

结论： $2$ 到 $25$ 之间的素数是：$2,3,5,7,11,13,17,19,23$。

代码实现：
[埃氏筛法](https://www.luogu.com.cn/paste/19w1yrm5)
```cpp
long long sieve(long long n)
{
	long long f[1000010] = {1,1};//f[i]=1代表i不是素数，f[i]=0代表i是素数
	for(long lnog i = 2;i <= n;i++)
	{
		if(f[i] == 1) continue;
		for(long long j = 2;i * j <= n;j++)
		{
			f[i * j] = 1;
		}
	}
}
```
### 欧拉筛法 $O(n)$
欧拉筛法和埃氏筛法的区别在于，埃氏筛法其中有很多数倍筛选了很多遍，例如 $60$，它被 $2,3,5$ 都筛选过，就造成了时间的浪费。而欧拉筛法的好处在于，它其中的所有数都只会被筛选一遍。

欧拉筛法的关键便在于每个合数只被其最小的质因数筛掉，比如 $21$，它只会被 $3$ 筛掉，而在 $7$ 时，就不会去浪费时间判断了。

那么如果 $21$ 被 $3$ 筛掉，我们要研究 $7$ 应该筛到哪个数才能停止？

我们设这个数为 $n = p_1^{x_1} \times p_2^{x_2} \times \cdots \times p_m^{x_m}$

$$(p_1 \lt p_2 \lt \cdots \lt p_m,x_1,x_2,\cdots,x_m \ge 1,m \ge 2)$$

当我们筛到 $p_1$ 时继续向下筛选，不妨设此时筛选的质数为 $p_0$，那么

$$ n \times p_0 = p_0 \times p_1^{x_1} \times p_2^{x_2} \times ... \times p_m^{x_m} \  = p_1 \times p_0 \times p_1^{x_1 - 1} \times p_2^{x_2} \times ... \times p_m^{x_m} $$

那么此时 $n \times p_0$ 可以由 $p_1$ 筛选掉，就不需要 $p_0$ 来筛选了。

这样便实现了 $O(n)$ 的时间复杂度。

代码实现：
[欧拉筛法](https://www.luogu.com.cn/paste/ypk97qsn)

```cpp
int euler(int n)
{
	int d = 0;
	int p[100010] = {0};
	int f[100010] = {1,1};
	for(int i = 2;i <= n;i++)
	{
		if(f[i] == 0)
		{
			p[d++] = i;
		}
		for(int j = 0;j < d;j++)
		{
			if(p[j] * i <= n)
			{
				f[p[j] & i] = 1;
			}
			else
			{
				break;
			}
			if(i % p[j] == 0)
			{
				break;
			}
		}
	}
} 
```

**扯得有点远了，接下来，让我们回到这个题目**
## 题目讲解
### 题意
在区间 $[a,b]$ 中，满足 $p$ 为质数，$p^2+1$ 或 $p^2+2$ 为质数的 $p$ 的个数。

### 分析
由前面的知识我们知道，质数除了 $2$ 以外均是奇数，又因为 $p$ 是质数，

那么 $p \ge 2$，则 $p^2+1 \ge 5$，所以

$$p^2+1 \equiv 1 \pmod 2$$

$$p^2 \equiv 0 \pmod 2$$

$$p \equiv 0 \pmod 2$$

那么 $p$ 只能为 $2$，检验 $p^2+1=5$，符合要求。

由于一个平方数

$$a^2 \equiv 0 / 1 \pmod 3$$

而质数 $p$ (除了 $3$ )

$$p \equiv 1 / 2 \pmod 3$$

那么

$$p^2 \equiv 1 \pmod 3$$

那么

$$p^2 + 2 \equiv 0 \pmod 3$$

所以

$$3 \mid p^2+2 $$

又 $p^2+2\ge6$，所以 $p^2+2$ 为合数，不符合题意，所以此时的 $p$ 一定为 $3$。

另外，由题目规定，$p=0$ 和 $1$ 也记为质数，那么

$p = 0$ 时，$p^2 + 1 = 1$ ，$p^2 + 2 = 2$，均为质数。

$p = 1$ 时，$p^2 + 1 = 2$ ，$p^2 + 2 = 3$，均为质数。

**综上所述， $p$ 可以等于 $0,1,2,3$。**
### 代码

分析完毕，接下来我们开始写本题的代码。

有了前面的分析，我们知道，这道题只需要统计区间 $[a,b]$ 之间 $0,1,2,3$ 的个数即可。

$a>3$ 时，不可能有 $0,1,2,3$ 的任意一个，直接输出 $0$ 即可。

$a=3$ 时，只会有 $3$ 一个数字，直接输出 $1$ 即可。

$a<3$ 时，$ans = \min(b,3) - a + 1$，输出 $ans$ 即可。

下面给出 AC 代码：
[AC 代码](https://www.luogu.com.cn/paste/qe7uve77)
```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		int a,b;
		cin >> a >> b;
		if(a > 3) cout << "0" << endl;
		else if(a == 3) cout << "1" << endl;
		else
		{
			int ans = min(b,3) - a + 1;
			cout << ans << endl;
		}
	}
	return 0;
}
```

或者可以由以上 $3$ 种情况，总结出通项公式：

$ans = \max(\min(b,3) - a + 1,0)$ ，直接输出 $ans$ 即可。

这种方法的 AC 代码：[AC 代码](https://www.luogu.com.cn/paste/221u8izf)
```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		int a,b;
		cin >> a >> b;
		cout << max(min(b,3) - a + 1,0) << endl;
	}
	return 0;
}
```
**但是，如果我们没学过数论，也不会高级的质数筛选，怎么做呢？**
 
**非正解：暴力**

原题数据告诉我们，$a \le 50000$ ， $b \le 100000$；

我们考虑最坏情况，$b - a = 1\times10^5$，最大时间复杂度约为 $1\times 10^9$， 常数还蛮大的，在 TLE 的边缘疯狂试探......

那么~~乱搞~~暴力一下，挨个枚举 $a$ 到 $b$，满足 $p$ 为质数且 $p^2+1$ 或 $p^2+2$ 为质数时计数器 $cnt$ 加 $1$，最终输出 $cnt$ 即可。时间复杂度为 $O(n\sqrt{n})$。

考虑到读入输出量较大，可以使用快读快写，附赠[快读快写+快速幂模版](https://www.luogu.com.cn/paste/zhf1daf3)

注意：判断时 $p^2+1$ 最大值能达到 $1\times10^{10}$，所以需要**开 long long 存储**

代码实现：[暴力](https://www.luogu.com.cn/paste/ni1ujhcs)

```cpp
#include<bits/stdc++.h>
using namespace std;

int read()//快读 
{
	int s = 0,w = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9')
	{
		if(ch == '-') w = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		s = s * 10 + ch - '0';
		ch = getchar();
	}
	return s * w;
}

void write(long long a)//快写 
{
	if(a > 9) write(a / 10);
	putchar(a % 10 + '0');
}

long long pow_quick(long long a,long long n)//快速幂 
{
	long long res = 1;
	while(n)
	{
		if(n & 1) res *= a;
		a *= a;
		n >>= 1;
	}	
	return res;
} 

bool prime(long long x)//最简单的枚举判断质数 
{
	if(x == 0 || x == 1) return 1;
	for(int i = 2;i * i <= x;i++)
	{
		if(x % i == 0) return 0;	
	}	
	return 1;
} 

int main()
{
    int T,a[100010],b[100010];
    T = read();
    for(int i = 1;i <= T;i++)
    {
    	a[i] = read();b[i] = read();
	}
    for(int k = 1;k <= T;k++)
    {
    	int cnt = 0;
    	for(int j = a[k];j <= b[k];j++)
    	{
    		long long ans1 = pow_quick(j,2) + 1;
    		long long ans2 = ans1 + 1;
    		if(prime(j) && ((prime(ans1)) || (prime(ans2)))) cnt++;
		}
		write(cnt);cout << endl;
	}
    return 0;
}                   

```

---

## 作者：Fengyiwei1234 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/SP15891)

这道题刚开始看没看懂，分析一会就出来了。

**思路**


首先，当 $ \ \ p^2+1\ $ 为质数时，这个数一定为奇数，所以 $ \ P \ $ 为偶数。

偶质数只有当 $ \ P=2 \ $ 时。



第二，当 $ \ \ p^2+2\ $ 为质数时，由于 $ \ \ 3|p^2-1$，不妨设 $ \ \ P=3k+1(k∈Z)$。

则 $ \ \ p^2+2 = 9k^2+6k+3 = 3(3k^2+2k+1)\ $，此时 $ \ \ P=3$。

所以，综上所述，满足条件的只有 $ \ \ P=0,1,2,3$。

---

## 作者：ttq012 (赞：0)

**Solution**

这个题很简单，使用 `miller_rabin` 暴力判断每一个数是否满足条件，然后前缀和计算答案即可。

时间复杂度 $O(nk\log n)$，其中 $k$ 是选取的质数的数量。

跑的很快。

```cpp
#include <bits/stdc++.h>
#define int long long
const int N = 100000, M = N + 10;
bool vis[N];
int s[N];
namespace PRIME
{
  auto ksm(int a, int b, int c) -> int
  {
    if (!b)
      return 1;
    int ans = ksm(a, b >> 1, c);
    ans = ans * ans % c;
    if (b & 1)
      ans = ans * a % c;
    return ans;
  }
  int prime_list[] = {2, 3, 5, 7, 13, 19, 41, 97};
  auto miller_rabin(int n, int a) -> bool
  {
    int d = n - 1, r = 0;
    while (d % 2 == 0)
      d /= 2, r++;
    int x = ksm(a, d, n);
    if (x == 1)
      return true;
    for (int i = 0; i < r; i++)
    {
      if (x == n - 1)
        return true;
      x = x * x % n;
    }
    return false;
  }
  auto isprime(int n) -> bool
  {
    if (n == 0 || n == 1)
      return true;
    if (n < 0)
      return false;
    for (int i = 0; i < 8; i++)
    {
      if (n == prime_list[i])
        return true;
      if (n % prime_list[i] == 0 || !miller_rabin(n, prime_list[i]))
        return false;
    }
    return true;
  }
}
auto main() -> signed
{
  int T;
  std::cin >> T;
  for (int i = 0; i <= N; i++)
    if (PRIME::isprime(i) && (PRIME::isprime(i * i + 1) || PRIME::isprime(i * i + 2)))
      vis[i] = true;
  s[0] = vis[0];
  for (int i = 1; i <= N; i++)
    s[i] = s[i - 1] + (int)vis[i];
  while (T--)
  {
    int l, r;
    std::cin >> l >> r;
    std::cout << s[r] - s[l - 1] << std::endl;
  }
}

```



---

## 作者：Jerry_heng (赞：0)

（一）

1. 先考虑 $p<3$。

	- $p=0$，$p^2+1=1$ 为质数，$p^2+2=2$ 为质数，成立！

	- $p=1$，$p^2+1=2$ 为质数，$p^2+2=3$ 为质数，成立！
    
   
1. 考虑 $p>3$。

	- 要使 $s=p^2+1$为质数。
    
    	- 当 $p=2$ 时，成立！
        
      - 当 $p\ge 2$ 时，$p \equiv 1(\bmod\ 2)$，所以 $2\mid s$，不成立！
    
   - 要使 $s=p^2+2$为质数。
   		
      - 当 $p=3$ 时，成立！
      
      - 当 $p>3$ 时，$p^2 \equiv 1(\bmod\ 3)$，所以 $2 \mid s$，不成立！
      
综上，$p$ 符合条件当且仅当 $p\le 3$。

（二）
   		
AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a,b;
int main(){
	cin>>t;
	while(t--){
		cin>>a>>b;
		if(a>3)cout<<0<<endl;
		else cout<<min(3,b)-a+1<<endl;
	}
	return 0;
}
```

---

## 作者：zeekliu (赞：0)

这题给人第一眼看上去是判断素数，但实际上，这是个**坑题**！

仔细想想，举个例子，$ n=5 $ 时，$ n^2+1=26 $，$ n^2+2=27 $，诶，怎么回事，都不是素数呀。再举几个例子，比如 $ n=7,n=11,n=13 $，都不是。

分析一下：排除掉 $ 2 $，素数全是奇数，那么 $ n^2+1 $ 就是偶数，没戏，那么仔细观察，$ n^2+2 $ 好像都是 $ 3 $ 的倍数。

因为 $ n $ 是素数，所以 $ n \bmod 3 = 1 $ 或 $ 2 $，那么平方后除以 $ 3 $ 一定余 $ 1 $，加上 $ 2 $ 后一定是 $ 3 $ 的倍数，也没戏。

所以对于一般的素数，都没戏。

但有两个特别的素数：$ 2 $ 和 $ 3 $，这两个数可以（$ 2 \times 2+1=5 $，$ 3 \times 3+2=11 $）。

又因为此处认为 $ 0 $ 和 $ 1 $ 也是素数，所以得到结论：$ n=0,1,2,3 $ 时满足要求。

因此若 $ a \ge 4 $，无解。

否则，若 $ b \ge 4 $，则等同于 $ b=3 $。

然后答案就是 $ b-a+1 $。

因此给出代码：

```cpp
//SP15891 22-10-04
#include <bits/stdc++.h>
using namespace std;
int _,a,b;

int main() 
{
	cin>>_;
	while (_--)
	{
		cin>>a>>b;
		if (a>=4) { cout<<"0"<<endl; continue; }
		else if (b>3) b=3;
		cout<<b-a+1<<endl;
	}
	exit(0);
}
```

---

## 作者：Inui_Sana (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/SP15891)

思路：数论

你看到这道题的第一反应是否是线性筛呢？但你很快就会发现，实际上如果这样做，我们要筛出 $10^{12}$ 之内的所有素数，或是只筛出 $10^6$ 之内的质数，然后判断 $p^2+1$ 和 $p^2+2$ 是否为质数。但这两种做法都会超时。

这时，我们可以分析一下符合题意的 $p$ 的性质：

如果 $p$ 为奇数即 $p \neq 2$ 时，$p^2$ 一定为奇数，则 $p^2+1$ 一定为 $\gt 2$ 的偶数，则一定为合数。

如果 $p$ 不为 $3$，$p^2 \equiv 1 \pmod{3}$，所以 $p^2+2 \equiv 0 \pmod{3}$，也为合数。

综上所述，只有 $2$ 和 $3$ 符合条件，再加上特别判断的 $0$ 和 $1$，符合条件的数只有这几个。

code：

```cpp
#include<cstdio>
#define run int T;scanf("%d",&T);while(T--)solve
//甚至不用using namespace std;
typedef long long ll;
const int maxn=1e5+7,inf=2147483647;
const int mod=1;
int n,m,pm[5]={0,0,1,2,3};//为方便处理，将他们存在一个数组里
void solve(){
	scanf("%d%d",&n,&m);
	int cnt=0;
	for(int i=1;i<=4;i++){
		if(pm[i]>=n&&pm[i]<=m)cnt++;
	}
	printf("%d\n",cnt);
}
signed main(){
	run();
}
```
upd：做了一点小修改

---

## 作者：Leasier (赞：0)

随便打个表就能发现 $p \in [0, 3]$ 时满足条件，否则一定不满足条件。

证明：$p > 3$ 时一定可以表示为 $6k \pm 1$ 且为奇数，于是考虑 $p^2 + 2$ 是否一定不为质数。显然，$p^2 + 2 = 36k \pm 6k + 3$，即其一定能被 $3$ 整除。

答案即为 $\min(b, 3) - \min(a - 1, 3)$。

代码：
```cpp
#include <stdio.h>

inline int min(int a, int b){
	return a < b ? a : b;
}

int main(){
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++){
		int a, b;
		scanf("%d %d", &a, &b);
		printf("%d\n", min(b, 3) - min(a - 1, 3));
	}
	return 0;
}
```

---

## 作者：Loser_Syx (赞：0)

## 思路

什么？你以为这题考你质数判定？那可就大错特错了，这是一道**数论题**。

接下来，我们讨论一下 $p^2 + 1$ 和 $p^2 + 2$ 所具有的特征（$p$ 为质数）。

当 $p$ 不为 $2$ 且 $p$ 是奇数时，$p^2$ 也为奇数，那么 $p^2 + 1$ 为就一定是合数，便不是质数。

当 $p$ 不为 $3$ 时，显然 $p \bmod 3$ 肯定不为 $0$，只看能是 $1$ 或 $2$，然而 $1^2 \bmod 3 = 1, 2^2 \bmod 3 = 1$， 则 $p^2 \bmod 3$ 也是 $1$，那么 $(p^2 + 2) \bmod 3 = 0$。

再来看看题目的特殊规则 `Consider 0 and 1 as prime numbers for this question`，此处 $0$ 和 $1$ 都视为质数。

所以，此题成立的数只有 $0,1,2,3$。

那么答案就是 $\max(0,\min(b,3)-a+1)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int T;
	cin>>T;
	while (T--){
    int a, b;
	    cin>>a>>b;
		cout<<max(0,min(b,3)-a+1)<<'\n';
	}
	return 0;
}
``` 

---

