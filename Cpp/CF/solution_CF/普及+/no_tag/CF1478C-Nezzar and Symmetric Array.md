# Nezzar and Symmetric Array

## 题目描述

Long time ago there was a symmetric array $ a_1,a_2,\ldots,a_{2n} $ consisting of $ 2n $ distinct integers. Array $ a_1,a_2,\ldots,a_{2n} $ is called symmetric if for each integer $ 1 \le i \le 2n $ , there exists an integer $ 1 \le j \le 2n $ such that $ a_i = -a_j $ .

For each integer $ 1 \le i \le 2n $ , Nezzar wrote down an integer $ d_i $ equal to the sum of absolute differences from $ a_i $ to all integers in $ a $ , i. e. $ d_i = \sum_{j = 1}^{2n} {|a_i - a_j|} $ .

Now a million years has passed and Nezzar can barely remember the array $ d $ and totally forget $ a $ . Nezzar wonders if there exists any symmetric array $ a $ consisting of $ 2n $ distinct integers that generates the array $ d $ .

## 说明/提示

In the first test case, $ a=[1,-3,-1,3] $ is one possible symmetric array that generates the array $ d=[8,12,8,12] $ .

In the second test case, it can be shown that there is no symmetric array consisting of distinct integers that can generate array $ d $ .

## 样例 #1

### 输入

```
6
2
8 12 8 12
2
7 7 9 11
2
7 11 7 11
1
1 1
4
40 56 48 40 80 56 80 48
6
240 154 210 162 174 154 186 240 174 186 162 210```

### 输出

```
YES
NO
NO
NO
NO
YES```

# 题解

## 作者：胖头鱼学员 (赞：6)

# CF1478C

[洛谷传送门](https://www.luogu.com.cn/problem/CF1478C)

[CF传送门](https://codeforces.com/contest/1478/problem/C)

## $Question \ Meaning$

给定长度$2 \cdot n$个数组$a$，满足：

1. $a$中的元素不重复。

2. 对于任意一个下标$i(1 \leq i \leq 2 \cdot n, i \ne j)$，都能找到一个下标$j$，使得$a_i = -a_j$。

现在有一个数组$d$，其中

$$
d_i = \sum_{j=1}^{2n}|a_i -a_j|
$$

问能不能构造出$a$数组。

## $Solution$

考虑贪心：

根据初中知识我们可以发现：
$$
|x - y| + |x + y| = 2 \cdot \max(|x|, |y|)
$$

那么我们不妨设$d_{2n} = -d_{2n - 1} = \max\limits_{i=1}^{2n} d_i$，$d_{2n-2} = -d_{2n - 3} = \max\limits_{i=1}^{2n-2}d_i$，那么可以根据上式发现：

$$
d_{2n} = -d_{2n - 1} = \sum_{i = 1}^{2n}|a_i - a_j| = 2n \cdot \max\limits_{i =1}^{2n}|a_i|
$$

则

$$
\max\limits_{i = 1}^{2n}a_i = \frac{d_{2n}}{2n}
$$

那么

$$
d_{2n - 2} = -d_{2n - 3} = \sum_{i = 1}^{2n}|a_i - a_j| = 2(n-1) \cdot \max\limits_{i = 1}^{2n - 2}|a_i| + 2 \cdot d_{2n}
$$

则

$$
\max\limits_{i = 1}^{2n-2}|a_i| = \frac{d_{2n-2}}{2(n-1)} - 2 \cdot d_{2n}
$$

递推计算即可。

## $Code$
```cpp
# include <algorithm>
# include <iostream>

using namespace std;

const int kMaxN = 2e5 + 1;
long long T, n, d[kMaxN];

bool Check() {
  for (int i = 1; i <= n * 2; i += 2) {
    if (d[i] != d[i + 1]) {
      return 1;
    }
  }
  return 0;
}

string Solve() {
  scanf("%lld", &n);
  for (int i = 1; i <= n * 2; i++) {
    scanf("%lld", &d[i]);
  }
  sort(d + 1, d + 2 * n + 1);
  if (Check() == 1) {
    return "NO\n";
  }
  long long id = 2 * n, flag = 1, num = 2 * n, sum = 0, last = 0;
  while (id) {
    if ((d[id] - 2 * sum) % num != 0 || (d[id] - 2 * sum) / num <= 0) {
      return "NO\n";
    } else {
      if (last != 0 && last <= ((d[id] - 2 * sum) / num)) {
        return "NO\n";
      }
      last = ((d[id] - 2 * sum) / num);
      sum += ((d[id] - 2 * sum) / num), id -= 2, num -= 2;
    }
  }
  return "YES\n";
}

int main() {
  scanf("%lld", &T);
  while (T--) {
    cout << Solve();
  }
  return 0;
}
```

---

## 作者：zjz2333 (赞：2)



我们先将数组d排序又容易知道$a[i],-a[i]$都在数组中出现一次

先仅考虑正数时，我们可以发现，当 ${a[i]>a[j]}$ 时，$a[j]$对${\sum_{j=1}^n}|a[j]-a[i]|$的贡献是$2*a[j]$

否则是$2*a[i]$

从n向1走，$d[i]$越大对应的$a[i]$越大

知道$a[n]=d[n]/n$,$a[n-1]=-a[n]$

当到达$n-2$时，我们就可以知道$(n-2)*a[n-2]+2*a[n]=d[i]$从而解出$a[n-2]$

通过维护一个后缀和我们就可以得到所有$a[i]$

通过能否构造出合法的a数列从而判断是否有解

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 101;
int n, d[N], a[N];

void work()
{
	scanf("%lld",&n); n *= 2;
	for(int i = 1;i <= n; i++) scanf("%lld",&d[i]);
	sort(d + 1,d + n + 1);
	int flag = 0;
	for(int i = 1;i <= n; i += 2)
	    if(d[i] != d[i + 1]) flag = 1;
    if(flag) { puts("NO"); return; }
    if(d[n] % n != 0) { puts("NO"); return; }
    a[n] = d[n] / n;a[n - 1] = - a[n];
    int sum = 2 * a[n];
    for(int i = n - 2;i >= 2; i -= 2)
    {
    	if(d[i] <= sum || (d[i] - sum) % i != 0) { puts("NO"); return; }
    	a[i] = (d[i] - sum) / i;
		a[i - 1] = -a[i];
		if(a[i] == a[i + 2]) { puts("NO"); return; }
		sum = sum + 2 * a[i]; 
	}
	puts("YES");
}

signed main()
{
	int t; scanf("%lld",&t);
    while(t --) work();
}
/*
1
4
40 56 48 40 80 56 80 48
*/
```

---

## 作者：_Anchor (赞：2)

# C题（性质）

## Problem

![](https://s3.ax1x.com/2021/02/05/yGznRx.md.png)

## Solution

根据绝对值的定义，我们很容易发现这样一个事实：

对于每一个数$x$都对应着一个区间$[-|x|,|x|]$，其对应的$d$是比这个区间大的区间的长度之和，加上比这个区间小的**一些**长度之和

具体解释就是：

假设当前原数是$a_1,a_2,a_3$，不妨设$0<a1<a2<a3$

![](https://s3.ax1x.com/2021/02/05/yGz3ee.md.png)

图中红线代表：$a_1$对应的$d_1$在线段长度上的呈现，同理，$d_2$是蓝线，$d_3$是绿线

所以我们可以观察发现：

$0.$ $a_i$对应的$d_i$必定和$-a_i$相等

$1.$ 绝对值越小，其对应的$d$就越小

$2.$ 相邻两项$d_i$的差就是其对应$|a_i-a_{i-1}|$的$2(i-1)$倍

那么我们现在就可以直接把给出的序列（不妨假设为$d$）排序

然后先判断是否$d$两两相同，如果不是，输出$NO$，否则再判断$d$有没有三个及以上相同，如果有，输出$NO$，否则继续

接下来我们考虑相邻两个$d$的差，如果某个$d_i-d_{i-1}$不可以被$2(i-1)$整除，直接输出$NO$

然后我们可以算出所有的线段了，最后只需要检查一下最开始的最小的那个线段就可以了

也就是如果$\sum len_{min}$不能被$2n$整除，那么也是$NO$

否则，这个答案可行，输出$YES$
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
template <typename T>
inline void read(T &x){
	x=0;char ch=getchar();bool f=false;
	while(!isdigit(ch)){if(ch=='-'){f=true;}ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	x=f?-x:x;
	return ;
}
template <typename T>
inline void write(T x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10^48);
	return ;
}
template <typename T>
inline void print(T x){write(x),putchar(' ');}
#define ll long long
#define ull unsigned long long
#define inc(x,y) (x+y>=MOD?x+y-MOD:x+y)
#define dec(x,y) (x-y<0?x-y+MOD:x-y)
#define min(x,y) (x<y?x:y)
#define max(x,y) (x>y?x:y)
const int N=2e5+5,M=1e6+5,MOD=1e9+7;
long long n,a[N],b[N],ans,ans1;
unordered_set<int> tar;
bool flag[N];
int main(){
	int t;
	read(t);
	while(t--){
		read(n);ans=0;tar.clear();int tot=2*n;
		for(int i=1;i<=2*n;i++) read(a[i]);
		sort(a+1,a+2*n+1);bool pp=false;
		for(int i=2;i<=2*n;i+=2){
			b[i/2]=a[i];
			if(b[i/2]==b[i/2-1]||a[i]==a[i+1]||a[i]!=a[i-1]){
				pp=true;
				break;
			}
		}
		if(pp||b[1]==0){
			puts("NO");
			continue;
		}
		for(long long i=2;i<=n;i++){
			if((b[i]-b[i-1])%(2*(i-1))){pp=true;break;}
			ans+=(b[i]-b[i-1])*(n-i+1)/(i-1);
		}
		if(pp){
			puts("NO");
			continue;
		}
		ans1=b[1]-ans;
		if((ans1%(2*n))||ans1<=0) puts("NO");
		else puts("YES");
	}
	// system("Pause");
	return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：0)

注意开long long 。                 

自己推的时候没上数轴，强行表达式法推错了一个性质，淦。            

首先我们可以把 $d$ 数组排序，然后对于 $a_i$ 和 $-a_i$ ，显然他们两个的 $d$ 值相等，所以我们先分开他们两个，把原序列变成一个长为 $n$ 的 $a$ 序列。  

我们用表达式分析 $a_i$ 和 $a_{i + 1}$ 时，会发现他们的 $d$ 值也只相差 $2 \times i \times (a_{i + 1} - a_i)$ ，这里默认 $a$ 数组排好序，当然你用数轴会更直观，并且几乎不会推错。（自己用表达式算的时候就在这里推错了一步）             

接着我们发现，我们这个式子里面唯一一个无法确定的东西就是 $a_1$ ，如果 $a_1$ 出来了我们自然可以获得 $a$ 序列。                       

我们考虑计算 $a_1$ ，具体而言，就相当于判断当前的 $|a_1 - (-a_1)|$ 是否合法，我们用 $d_1$ 减去所有形如 $a_{i + 1} - a_i$ 线段贡献的答案，那么剩下的值 $res$ 必须要大于 $0$ 并且要被 $2 \times n$ 整除，否则就说明 $|a_1 - (-a_1)|$ 不是整数，当前的序列无法构造。            

然后直接判断就好了。               

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Len = 2e5 + 5;
int n,m;
long long d[Len << 1],a[Len];
bool check()
{
	for(int i = 1 ; i <= n ; i ++)
	{
		a[i] = d[i * 2];
		if(a[i] == a[i - 1] || d[i * 2] == d[i * 2 + 1] || d[i * 2] != d[i * 2 - 1]) return false;
	}
	long long res = 0;
	for(int i = 2 ; i <= n ; i ++)
	{
		if((a[i] - a[i - 1]) % (2 * (i - 1))) return false;
		res += (a[i] - a[i - 1]) / (i - 1) * (n - i + 1);
	}
	if((a[1] - res) <= 0 || (a[1] - res) % (2 * n)) return false;
	return true;
}
int main()
{
	int t;scanf("%d",&t);
	while(t --)
	{
		scanf("%d",&n);
		for(int i = 1 ; i <= (n << 1) ; i ++) scanf("%lld",&d[i]);
		sort(d + 1 , d + 1 + (n << 1));
		if(!check()) puts("NO");
		else puts("YES");
	}
	return 0;
}
```



---

## 作者：fanfansann (赞：0)

## C - Nezzar and Symmetric Array

定义长度为$2 \times n$ 的数组 $a$，满足：

$a$ 中的元素不重复。

并且对于任意一个下标$i(1 \leq i \leq 2 \cdot n, i \ne j)$，都能找到一个下标 $j$，使得 $a_i = -a_j$ 。

现在给定一个数组 $d$，其中

$$d_i = \sum_{j=1}^{2n}|a_i -a_j|$$
问能不能通过数组 $d$ 构造出数组 $a$ 。

**Solution**

一般这种有 $n$ 个的数组，$n$ 会很大，求一种 $\tt value$ 什么的，一定是一种规律性的问题。

所以我们一般从两个数开始，从特殊到一般，一般简单推一下就能找到拓展到 $n$ 个数的答案。

我们首先分析两个的情况。

我们假设两个正整数 $a,b$ 

那么序列就会有四个数：$a,b,-a,-b$

$d_1=|a-a|+|a-b|+|a-(-a)|+|a-(-b)|$
$\ \ \ =|a-b|+|a+b|+|2a|$

$d_2=|b-b|+|b-a|+|b-(-a)|+|b-(-b)|$
$\ \ \ \ \ =|b-a|+|b+a|+|2b|$
当 $a>b$ 时：

$|a-b|=a-b$
$|a+b|=a+b$

$d_1=2a+2a=4a$

$d_2=a-b+a+b+2b=2a+2b$

当 $a<b$ 时

$|a-b|=b-a$
$|a+b|=a+b$

$d_1=2a+2b$
$d_2=4b$

我们发现

若 $a>b$ 则 $d_1>d_2$

若 $a<b$ 则 $d_1<d_2$ 

我们发现题中给我们的数列 $d$ 和实际上想要我们求的数列 $a$ 是同步的，同单调性的，所以很明显我们可以将数列从大到排序

然后拓展到 $n$ 个数字：

$d_1=2\times na_1=2na_1$

$d_2=2a_1+2\times(n-(2-1))a_2$

$d_3=2a_1+2a_2+(2\times(n-(3-1)))a_3$

$\cdots$

$d_i=2a_1+2a_2+\cdots+2a_{i-1}+2\times(n-(i-1))a_i$

>$(n-(i-1))a_i$ 表明前面有 $i-1$ 个比他大的数。

因为排过序了，所以想要构造出答案，就从前往后，依次按照公式，减掉前面刚刚求得的 $a_1$ ~ $a_{i-1}$ 然后除以系数就是当前的 $a-i$。

推出公式之后，我们可以手算样例，发现不存在解的情况：

- $d_i$ 不能整除 $2\times(n-(i-1))$，因为 $a_i$ 全是整数，所以很明显。

- 手算倒数第二组数据的时候发现， $d_i$ 不能小于 $0$ ，因为题目中要求的是正整数。

- 以及因为我们证明了 $a_i$ 一定和 $d_i$ 是同单调性的，所以如果我们发现上一个 $a_{i-1}$ 是小于 $a_i$ ，则同样无解。

所以整体的思路就是先输入，去重得到 $n$ 个数，然后根据上面得到的三个结论判断是否存在解。

然后就是实现上的细节了，因为 $d_i\le 10^{12}$，所以我们去重的时候可以用 `unordered_map` 来当作 `hash` 表使用，普通数组存不下。


--------- 

注意本题究极卡常

本题的最优解时间复杂度为：$O(Tnlogn)$

而 $T,n\le10^5$，还好保证了 $\sum_{\text text\ \text case} n\le10^5$，所以我们上面看上去很离谱的时间复杂度可以勉强卡过...

所以我们要减少**任何会浪费时间的写法**
比如： 

- `memset` 改为 `for` 循环初始化，注意 $n\le10^5$，而输入的数据有 $2*n$ ，虽然我们不需要存这么多，但是如果我们使用 `for` 循环初始化而不是用 `memset` ，那我们的数组就要开二倍以上

- 不要偷懒用 `reverse` ！能直接写 `cmp`   ，写个 `reverse` 还多了个常数...

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>
#include <unordered_map>

using namespace std;
typedef long long ll;
typedef int itn;
const int N = 5e5 + 7, mod = 1e9 + 7;
const ll INF = 1e18 + 7;

itn n, m, t;
ll d[N];
unordered_map<ll, int> vis;

bool cmp(ll a, ll b)
{
    return a > b;
}

int main()
{
    scanf("%d", &t);
    while(t -- ) {
        int cnt = 0;
        bool flag = 1;

        scanf("%d", &n);

        for(int i = 1; i <= 2 * n; ++ i)
            d[i] = 0;

        vis.clear();

        for(int i = 1; i <= 2 * n; ++ i) {
            ll x;
            scanf("%lld", &x);
            if(vis[x] == 0)
                d[ ++ cnt] = x, vis[x] = 1;
            else vis[x] ++ ;
        }
        sort (d + 1, d + 1 + cnt, cmp);
        //reverse (d + 1, d + 1 + cnt);//就多用了一个 reverse 结果T了...
        //这题时间卡的非常的紧, T, n ≤ 10^5...
        itn deer = 2 * n;
        ll sum = 0, last = INF;

        for(int i = 1; i <= cnt; ++ i) {
            if(vis[d[i]] != 2) {
                flag = false;
                break;
            }
            d[i] -= sum;
            int mul = 2 * (n - (i - 1));
            if(d[i] % mul != 0 || d[i] <= 0) {
                flag = false;
                break;
            }
            //cout << d[i] << "mul" << mul << "?" << endl;
            ll a = d[i] / mul;
            if(last <= a) {
                flag = false;
                break;
            }
            last = a;
            //cout << a << endl;
            sum += 2 * a;
        }
        if(flag) {
            puts("YES");
        }
        else {
            puts("NO");
        }
    }
    return 0;
}
```


---

## 作者：RyexAwl (赞：0)

将值放在数轴上考虑，我们发现成对点的$d[]$是相同的

只考虑正的$a[]$的$d[]$。 当$\forall 1\le i <n,a[i] <a[i+1]$时。

$$
\begin{aligned}
d[i]&=\sum_{1\le j\le n}\{a[j]+a[i]\} + \sum_{1\le j<i}\{a[i]-a[j]\}+\sum_{i+1\le j\le n}\{a[j]-a[i]\} \\
&=\sum_{1\le j\le n}a[j]+\sum_{i+1\le j\le n} a[j]-\sum_{1\le j<i}a[j]+n\times a[i]+(i-1)\times a[i]  -(n-i)\times a[i] \\
&=2\sum_{i+1\le j\le n}a[j]+a[i]+n\times a[i]+(i-1)\times a[i]  +(i-n)\times a[i] \\
&=2\sum_{i+1\le j\le n}a[j] + 2i\times a[i] \\
&=2(i\times a[i]+\sum_{i+1\le j\le n}a[j])
\end{aligned}
$$
考虑差分求出$a[]$。
$$
\begin{aligned}
d[i+1]-d[i]&=2((i+1)\times a[i+1]+\sum_{i+2\le j\le n}a[j])-2(i\times a[i]+\sum_{i+1\le j\le n}a[j]) \\
&=2\{i\times a[i+1]+\sum_{i+1\le j\le n}a[j] -i\times a[i]-\sum_{i+1\le j\le n}a[j]\} \\
&=2[i(a[i+1]-a[i])]
\end{aligned}
$$
$$
a[i+1]-a[i]=\frac{1}{2i}(d[i+1]-d[i])
$$
并且我们发现当$a[]$递增时，$\forall1\le i<n,a[i+1]-a[i]>0$，因此若$a[]$是递增的，$d$也一定是递增的。

接下来考虑求出$a[1]$。

我们对当前$a[]$的差分数组$da[]$作前缀和，其前缀和数组为$s[]$

$$
\begin{aligned}
d[1]&=2(\sum_{1\le j\le n}a[j]) \\
&=2(\sum_{1\le j\le n}da[i]+a[1]) \\
&= 2(n\times a[1]+\sum_{2\le j\le n}da[i])
\end{aligned}
$$
简单解方程即可解出$a[1]$,接下来即可得出所有的$a[]$,$check$一下是否每一位均大于$0$即可（以及是否有重复元素）。

~~代码过于暴力~~
```cpp
#include <iostream>
#include <algorithm>
 
namespace wxy{
 
const int N = 2e5 + 5;
 
#define int long long
 
int d[N],b[N],cpy[N],s[N],sa[N],a[N];
 
bool vis[N];
 
inline void main(){
    int t; std::cin >> t;
    while (t--){
        int n; std::cin >> n;
        for (int i = 1; i <= 2 * n; i++) std::cin >> d[i];
        std::sort(d + 1,d + 1 + 2 * n); int cnt = 0;
        bool check = true;
        for (int i = 1; i <= 2 * n; i += 2){
            cpy[++cnt] = d[i];
            if (d[i + 1] != d[i]){
                std::cout << "NO" << std::endl;
                check = false;
                break;
            }
        }
        if (!check) continue;
        for (int i = 1; i <= n; i++) s[i] = cpy[i] - cpy[i - 1];
        for (int i = 2; i <= n; i++){
            if (s[i] % (2 * (i - 1)) != 0){
                std::cout << "NO" << std::endl;
                check = false;
                break;
            }
            sa[i] = s[i] / (2 * (i - 1));
        }
        if (!check) continue;
        int sum = 0;
        for (int i = 2; i <= n; i++){
            a[i] = a[i - 1] + sa[i];
            sum += a[i];
        }
        if (!check) continue;
        if (cpy[1] % 2 != 0){
            std::cout << "NO" << std::endl;
            check = false;
        }
        if (!check) continue;
        cpy[1] /= 2;
        if (cpy[1] - sum <= 0){
            std::cout << "NO" << std::endl;
            check = false;
        }
        if (!check) continue;
        cpy[1] -= sum;
        if (cpy[1] % n != 0){
            std::cout << "NO" << std::endl;
            check = false;
        }
        if (!check) continue;
        cpy[1] /= n;
        for (int i = 1; i <= n; i++)
            if (a[i] + cpy[i] <= 0){
                std::cout << "NO" << std::endl;
                check = false;
                break;
            }
        if (!check) continue;
        for (int i = 1; i <= n; i++) b[i] = a[i] + cpy[1];
        std::sort(b + 1,b + 1 + n);
        for (int i = 1; i <= n; i++){
            if (b[i] == b[i - 1]){
                std::cout << "NO" << std::endl;
                check = false;
                break;
            }
        }
        if (!check) continue;
        std::cout << "YES" << std::endl;
    }
}
 
}signed main(){wxy::main();return 0;}
```


---

## 作者：Meaninglessness (赞：0)

### C. Nezzar and Symmetric Array

**题目大意:**

> 定义 $a$ 数组为:对于每一个位置 $i(1\le i\le 2n)$,都能找到一个位置 $j(1\le j\le2n)$,使得 $a_i=-a_j$。(**$a_i$都是互不相同的整数**)
 
> 定义 $d$ 数组为:$d_i=\sum_{j=1}^{2n} \left\vert a_i-a_j\right\vert$ 。

>现在给你 $d$ 数组,请你判断是否有满足情况的 $a$ 数组。

---

**解题思路:**

既然涉及到了绝对值,那么我们可以将 $a$ 数组的 $2n$ 个点,看作数轴上的 $2n$ 个点,且因为题目特殊要求 $a_i=-a_j$,这些点在数轴上是对称的。

举个 $n=2$ 时的例子:

![](https://cdn.luogu.com.cn/upload/image_hosting/s4t2r37r.png)

这$4$个点的对应的 $d_i$ 从左到右依次是:

$a+(a+2b)+(2a+2b)=4a+4b$

$a+b+2b+(a+2b)=2a+4b$

$(a+2b)+2b+b+a=2a+4b$

$(2a+2b)+(a+2b)+a=4a+4b$

发现了什么规律?

从这儿你肯定能发现:**会有两个点对应的 $d_i$ 相等!**

下面我们直接来看看一般情况

![](https://cdn.luogu.com.cn/upload/image_hosting/szbpyhad.png)

这次我们只讨论前 $n$ 个点。这 $n$ 个点的对应的 $d_i$ 从左到右依次是:

$d_1=c_1+(c_1+c_2)+...+(c_1+2c_2+...+2c_n)+(2c_1+2c_2+...+2c_n)=2nc_1+2nc_2+...+2nc_n$

$d_2=c_1+c_2+(c_2+c_3)+...+(2c_2+2c_3+...+2c_n)+(c_1+2c_2+...+2c_n)$

停!这个该怎么算呢?

我们发现,**在这里只有最开始和最后出现了一次 $c_1$**,剩下的还是照常,所以:

$d_2=c_1+c_2+(c_2+c_3)+...+(2nc_2+2nc_3+...+2nc_n)+(c_1+2c_2+...+2c_n)=2c_1+2nc_2+2nc_3+...+2nc_n$

那么如果接下来的按照刚刚的推,会得到:

$d_3=2c_1+4c_2+2nc_3+...+2nc_n$

$d_4=2c_1+4c_2+6c_3+2nc_4+...+2nc_n$

$...$

$d_n=2c_1+4c_2+6c_3+8c_4+...+(2n-2)c_{n-1}+2nc_n$

***

这里一定有:**$\left\vert a_i\right\vert$越大,$d_i$越大**

这里先定义:

```cpp
f[n]=c[1]+c[2]+c[3]+...+c[n]
f[n-1]=c[2]+c[3]+..+c[n-1]+c[n]
...
f[2]=c[n-1]+c[n]
f[1]=c[n]

f[n]>f[n-1]>...>f[2]>f[1]
```

我们将 $d$ 数组排序,这样可以得到:

```cpp
f[n]=d[2*n]/(n*2)
f[n-1]=(d[2*(n-1)]-2*f[n])/(2*(n-1))
f[n-2]=(d[2*(n-2)]-2*f[n]-2*f[n-1]/(2*(n-2)))
...
f[1]=(d[2]-2*f[n]-2*f[n-1]-...-2*f[3]-2*f[2])/(2*1)
```
如果 $f$ 数组中的数都为整数,且保证 $f_i>f_{i-1}$ 即可。

---

**代码实现:[Code](https://www.luogu.com.cn/paste/xtcvwj5h)　时间复杂度O(Tn)**

按理来说不应该会TLE吗。。。


---

