# Little Elephant and Interval

## 题目描述

小象非常喜欢区间中的数.

此时他有一対整数$l$和$r(l <= r)$. 小象需要找到满足以下条件的$x ( l <= x <= r) $,使得数x的第一个数字与最后一个数字相等. 例如, $101, 477474,9$是符合这个条件的,而$47, 253, 1020$则不符合.

请帮助他找到符合这个条件的数的数目.

## 样例 #1

### 输入

```
2 47
```

### 输出

```
12
```

## 样例 #2

### 输入

```
47 1024
```

### 输出

```
98
```

# 题解

## 作者：123456zmy (赞：6)

题意：  
求出在区间 $[l,r]$ 中，有多少整数满足最高位与个位相同。$1\le l\le r\le10^{18}$。
___
要求一段区间的答案，可以转化为两段从 $1$ 开始分别到 $r$ 和 $l-1$ 的区间答案之差，这样会比直接求方便一些。

关于求答案，我们可以把数除了最后一位的数字确定下来，然后最后一位也可以确定了，只要再特判一下 $10$ 以内和最大的那个值能否取到即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long l,r;
long long ans_(long long k)
{
	if(k<10)return k;
	long long ans=k/10+9,ans1=k%10;
	while(k>9)k/=10;
	return ans-(k>ans1);
}
int main()
{
	scanf("%lld%lld",&l,&r);
	printf("%lld",ans_(r)-ans_(l-1));
	return 0;
}
```

---

## 作者：Colead (赞：3)

大家好，这题是个 A 题，不过有一点点的思维含量。

首先，既然是判断首位和末尾相等，就应该先写出取一个数首位、尾位的函数。

这里为了方便、易于说明，把它们包装成函数：

```
long long fir(long long g)//首位
{
	while(g>=10)g/=10;
	return g;
}
long long fin(long long g)//尾位
{
	return g%10;
}
```

这个简单的问题解决以后，就是一些算法上的问题了。

**首先，暴力是一定可以解决数据在较小范围内的测试点的。大约 $10^6$ 左右。**

判断每一个数的复杂度都是常数，大约在 $10$ 左右。

但是数据范围有点大啊。如果暴力的话就绝对 TLE 了。

尝试优化。可以想到对于一个大的范围，中间的数中，每十个数中会有一个满足要求。原理显而易见：

$10$ $11$ $12$ $13$ $14$ $15$ $16$ $17$ $18$ $19$ $20$ $21$

个位是十个一循环的。

所以可以用类似分块的思想（没学过也没事）：中间的一部分直接用个数除以十，两边特判。

**总结：中间 $O(1)$ 两边 $O(n)$ 但是个数很少，不到 $20$ 个。**

复杂度已经过关了，但是两边特判……还是容易写挂。怎么办？

**两边不爽，就砍到一边**。（想要把两边都砍掉的前面就白看了，从头看吧）

使用类似前缀和的思路，计算从 $1$ 至 $r$ 的个数，再减去从 $1$ 至 $l-1$ 的。

这样就省去了左侧的特判，减小出错率。

```
#include<bits/stdc++.h>
using namespace std;
long long l,r;
long long fir(long long g)//首位
{
	while(g>=10)g/=10;
	return g;
}
long long fin(long long g)//尾位
{
	return g%10;
}
long long solve(long long n)
{
	if(n<=9)return n;
	else
	{
		long long base=(n/10+9);
		long long first=fir(n);
		bool flag=(fir(n)>fin(n));
		return base-flag;//**************
	}
}
int main()
{
	cin>>l>>r;
	cout<<solve(r)-solve(l-1)<<endl;
	return 0;
}
```

够简单？！只有一个地方需要解释一下：加星号那一行。

按理来说， C++ 中的 $/$ 是向下取整，但是实际上末尾可能产生合法的数啊，而且后面的判断还是往下减的。

这是因为个位前面已经判掉了，一来一回正好抵消。

这一篇题解应该是比较详细的了。希望能让各位明白。有问题可以在评论区提问。上面这两行是最难理解的，可以反复来几次哦~

---

## 作者：Anins (赞：2)

# [CF204A Little Elephant and Interval](https://www.luogu.com.cn/problem/CF204A)

## 题意

给定 $l,r$ 求区间 $[l,r]$ 中数字首位和尾位相等的数字的个数。

数据范围：$1 \leq l \leq r \leq 10^{18} $（**开 long long**）

## 思路

- 首先想到通过暴力枚举区间内所有数，每次检测是否符合要求，但显然对于大范围的区间会超时。
- 那么我们考虑找规律，直接对区间内的合法数统计比较麻烦，那我们不妨统计 $[1,r]$ 和 $[1,l-1]$ 两个区间内合法数的个数，并做差。当右端点小于 $10$ 时，那么个数一定为右端点的值。当右端点不小于 $10$ 时，我们举几个例子：

```
 i   [1,i]总数  [10,i]总数
12  ->  10  ->  10-9=1
21  ->  10  ->  10-9=1
25  ->  11  ->  11-9=2
33  ->  12  ->  12-9=3
36  ->  12  ->  12-9=3
```

我们发现对于一个数 $i$，在 $[10,i]$ 中，当 $i$ 首位比尾位大，那么结果为 $\lfloor \frac{i}{10} \rfloor - 1$，否则为 $\lfloor \frac{i}{10} \rfloor$。原因是个位每 $10$ 一个循环，每个循环内一定有合法数，如 $11,22,\dots,101,111,\dots,202,212\dots$，当尾位比首位小时，在该循环无法构成首尾相等，如 $31 < 33$。

这是思路，更多详情请看代码。



## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long get_first(long long n){ //取首位
	while(n>=10) n/=10;
	return n;
}
long long solve(long long n){
	if(n<10) return n;
	long long ans=n/10+9, last=n%10, first=get_first(n); //last为尾位,first为首位,答案别忘了+9
	if(first>last) ans--; //比较首尾,首比尾大-1
	return ans;
}
int main(){
	long long l, r;
	cin >> l >> r;
	cout << solve(r)-solve(l-1) << endl;
	return 0;
}
```

完结撒花！

---

## 作者：zhu_wen (赞：2)

# Little Elephant and Interval
## 大体思路
观察到，第一个数字与最后一个数字相等的数的个数是与数的位数有关的。假设区间 $[l, r]$ 的位数为 $d$，则该问题等价于计算 $d$ 位数中首位和末位相等的数的个数，注意数据范围，要开 long long 就这个 long long 卡我 10 分钟。

 
## 做法
我们运用前缀和思想来做这道题，~~鬼知道我用暴力来做,错了好几个点~~
- 对于只有一位数首位和末位相等的数只有一个，即该位的数字本身。
- 对于两位数及以上首位和末位相等的数有以下规律:返回首位的数字加上 $9$ 但是要注意，如果首位的数字大于末位的数字时，我们要减一。

整个思路就说完了，接下来附上代码，并带有注释。
## $code$
```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

inline int read()
{
    int x = 0;
    bool f = true;
    char c = getchar();
    while (c < 48 || c > 57)
    {
        if (c == '-')
            f = false;
        c = getchar();
    }
    while (c >= 48 && c <= 57)
        x = (x << 3) + (x << 1) + c - 48, c = getchar();
    return f ? x : -x;
}
inline void write(int x)
{
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + 48);
}
inline void wel(int x) { write(x), putchar('\n'); }

/*上面都是板子不用管
********************************************************************************************************/

int l, r; // 上面已经define了
// 注意要开long long，数据范围大
int f(int n)
{
    int cnt = 0;
    if (n < 10) // 特判
    {
        return n; // 如果是个位数，直接返回值
    }
    else
    {
        int back = n % 10; // 取末尾
        cnt = n / 10 + 9;  // 返回末尾的数加9
        while (n >= 10)
        {
            n /= 10;
        }
        int front = n;
        if (front > back)
            cnt--;
    }
    return cnt;
}

signed main()
{
    l = read(), r = read();    // 快读——不理解用scanf
    int res = f(r) - f(l - 1); // 前缀和思想
    wel(res);                  // 快写
    return 0;
}
```
## 记录
![](https://cdn.luogu.com.cn/upload/image_hosting/38xfdr76.png)
第一篇题解，希望官方大大通过啊。

---

## 作者：dxy2020 (赞：2)

# 前言
这题尽管是 A 题，但还是有些思维难度的。
# 分析
我们要求区间 $[l,r]$ 中末位等于首位的数，我们可以采取前缀和的思想,求出区间 $[1,r]$ 之间的满足题意的数，再减去 $[1,l-1]$ 中满足题意的数即为答案。

因为个位是十个一循环，所以中间的个数同样为十个一循环，可以直接用 $\lfloor \frac{n}{10} \rfloor$ 求出。再特判一下 $n≤10$ 和最大的值能否取到即可。

附上代码（含注释）：
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <queue>
#define int long long
using namespace std;
inline void in (int &x){
	int f=1;x=0;char c=getchar();
	while (c>'9'||c<'0'){if (c=='-') f=-1;c=getchar();}
	while (c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	x*=f;
}
int l,r;
inline int First (int x){//求首位数字  
	while (x>=10) x/=10;
	return x;
}
inline int Last (int x){//求末位数字  
	return x%10;
}
inline int Getsum (int u){
	return u<=9?u:u/10+9-(First (u)>Last (u));
	//答案为10个一循环 
}
signed main(){
	in (l);in (r);
	printf ("%lld\n",Getsum (r)-Getsum (l-1));//前缀和思想  
	return 0;
}
```


---

## 作者：cyj0314 (赞：1)

# CF204A题解
 
 ## 题意

求出在区间 $ [l,r]$ 中，有多少整数满足最高位与个位相同。$1\le l\le r\le10^{18}$。

 ## 分析

要求一段区间的答案，可以转化为两段从 $1$ 开始分别到 $r$ 和 $l-1$ 的区间答案之差。

 ## 求答案
 
我们可以把数除了最后一位的数字确定下来，然后最后一位也可以确定了，只要再特判一下 $10$ 以内和最大的那个值能否取到即可。

代码：

~~~cpp
#include<bits/stdc++.h>
using namespace std;
long long l,r;
long long fir(long long x){
	while(x>=10)
		x/=10;
	return x;
}
long long lst(long long x){
	return x%10;
}
long long sol(long long n){
	if(n<=9)
		return n;
	else{
		long long tmp1=(n/10+9);
		bool f=(fir(n)>lst(n));
		return tmp1-f;
	}
	return -1;
}
int main(){
	cin>>l>>r;
	cout<<sol(r)-sol(l-1);
	return 0;
}
~~~

---

## 作者：_int123_ (赞：1)

### 题意：

题目翻译有点长，简化一下便是：给你两个数 $l$ 和 $r$，让你求 $l$ 到 $r$ 中有多少个满足首位与末位相等的数。

### 思路：

1. 由于直接求 $l$ 到 $r$ 中的数不好求，于是我们可以先分别求出 $1$ 到 $l-1$ 和 $r$ 中有都少数满足，再两者相减即为答案，我们可以通过函数来实现。

2. 不难发现，当一个数 $n<10$ 时都是可以的；当 $n \ge 10$ 时，我们看 $n$ 的首位与末位，如果相等，有 $n \div 10 + 9$ 个数满足，如果不相等，要再减 $1$。

3. 然后便不难写出代码了。

### AC 代码：

```cpp
#include<bits/stdc++.h>
#define int long long //记得开 long long 
using namespace std;
int l,r;
int f(int n)//求 1~n 中有多少数满足题目条件 
{
	if(n<10) return n;//小于 10 都行 
	int ans=n/10+9;
	int anss=n%10;//末位 
	while(n>=10) n/=10;//首位 
	if(n>anss) return (ans-1);//如果不一样要减 1 
	return ans;
}
signed main()//因为 #define int long long 了，要用 signed 
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);//加速 
	cin>>l>>r;//输入 
	cout<<f(r)-f(l-1);//输出答案 
	return 0;
}
```

完结撒花！！！

---

## 作者：PigJokerYellow (赞：0)

## CF204A Little Elephant and Interval

### 题意

- 给定 $ l $ 与 $ r $ ，判断从 $ l $ 到 $ r $ 这些数中，有多少个数的第一位与最后一位相同。

### 思路

- 可以采用前缀和的思想，先求 $ 1 $ 到 $ r $ 中满足要求的个数与 $ 1 $ 到 $ l-1 $ 中满足要求的个数，再将它们做差即为答案。

- 所以我们去考虑对于任意数 $ n $ ，从 $ 1 $ 到 $ n $ 中有多少个数满足要求。

- 不难看出，若 $ n<10 $ ，则就有 $ n $ 个数满足要求，否则可分析出每十个数里，就会有一个数符合要求，就变成了小学奥数某周期问题，十个一组，故当 $ n \ge 10 $ 时，若最后一组存在合法的数，有 $ \frac{n}{10} + 9 $ 个数满足要求，否则有 $ \frac{n}{10} + 8 $ 个数满足要求。

### 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
//不开long long 见祖宗 

ll ans(ll n){
	if(n<10) return n;
	//n<10的情况 
	string str=to_string(n);
	//str[0]即为首位,str[str.size()-1] 即为末位 
	if(str[0]>str[str.size()-1]) return n/10+8;
	else return n/10+9;
} 

ll l,r;

int main(){
	
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>l>>r;
	cout<<ans(r)-ans(l-1);
	
	return 0;
} 
 
```

---

## 作者：Graph_Theory (赞：0)

### 思路
为了让代码简单一些，分别求出从 $1$ 到 $r$ 和 $1$ 到 $l-1$ 的答案，取差。

难点就在于如何求答案。

这里可以将每一部分的答案分开求解，先求 $1$ 到 $9$ 的答案再求其他的答案。

仔细想一下，这些数出现的频率，不难发现每 $10$ 个中就会有一个这样的数，最后你只需要特判一下最后那个数是否合法就可以了。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int ans(int a)
{
    int anns=a/10+9;
	if(a<=9) return a;
	
	int start=a%10;
	while(1)
   {
        if(a>=10) a/=10;
        else break;
	}
	int aend=a;
	
	return (start<aend? anns-1:anns);
}
signed main()
{
	int l,r;
    cin>>l>>r;
	cout<<abs(ans(r)-ans(l-1));
}
```

---

## 作者：zhanghx0219 (赞：0)

先理解一下题意：求在 $[l,r]$ 之间，有多少个最高位和最低位相同的整数。

对于求解区间类问题，一般使用前缀和思想，先求 $[1,r]$ 的答案,再求 $[1,l-1]$ 的答案，两者取差即为答案。

对于求解 $[1,x]$ 之间的答案，我们可以先对区间中 $10$ 以外的数进行判定，对于这些数，将除了最低位的数字确定下来，然后最低位也就可以确定了，然后再特判一下 $10$ 以内和最大的那个值是否能取到即可。

下面贴上代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll read(){
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
void write(ll x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
	return;
}
ll a,b;
ll getfirst(ll x){
	while(x>=10)x/=10;
	return x;
}
ll getlast(ll x){return x%10;}
ll getans(ll r){
	if(r<10)return r;
	ll sum=r/10+9,last=getlast(r);
	r=getfirst(r);
	return sum-(r>last);
}
int main(){
	a=read();b=read();
	write(getans(b)-getans(a-1));
	return 0;
}
```


---

## 作者：SY_nzwmb83 (赞：0)

### 题意

给出 $l$ 和 $r$ 的值，请你求出在 $[l,r]$ 区间内，首位数与末位数相同的数的个数。

### 分析

因为 $1 \leq l \leq r \leq 10^{18}$，所以暴力枚举肯定是不行的。想到如果把某个正整数 $x$ 的最后一位分离出来，那么前半部分可能产生的数就会有 $\lfloor \frac{x}{10} \rfloor$ 种可能，即前半部分所表示的数。特别注意不要考虑位数问题，因为这些可能的数中就已经包含了具有各种位数的数。


进一步思考，发现要满足首位数与末位数相同，只要确定了首位数，那末位数也就确定了下来。特别地，如果原来的首位数大于末位数，就会减少一种情况。另外，别忘了加上小于 $10$ 的 $9$ 个一位数

例如 $1000$ 这个数，它最后的 $0$ 被分离后，剩下 $100$，代表有 $100$ 种可能，即 $[1,100]$ 中所有正整数，每个正整数后面放上唯一的个位后就是要求的数，又因为首位数大于末位数，也就是 $1001$ 不满足，所以总个数减 $1$。最后加上小于 $10$ 的 $9$ 个一位数就可以。

现在有了求 $1$ 到某个正整数的方案个数，那么 $[l,r]$ 区间内就会有 $[1,r]$ 的方案数减去 $[1,l-1]$ 的方案数种答案。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int l,r;
int fi(int x)//取首位数
{
	while(x>=10)x/=10;
	return x;
}
int solve(int x)
{
	if(x<10)return x;//一位数直接得出结果
	int n=x/10+9,las=x%10,fir=fi(x);//求出方案数、首位数、末位数
	if(fir>las)n--;//首位数大于末位数，减1
	return n;
}
signed main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	cin>>l>>r;
	cout<<solve(r)-solve(l-1);
	return 0;
}
```

---

## 作者：cyz_czy (赞：0)

# CF204A 题解

> 我是 CYZ，这期带你看题解。

## 题目大意
小象非常喜欢区间中的数。

此时他有一対整数 $l$ 和 $r(l \leq r)$。小象需要找到满足以下条件的 $x ( l \leq x \leq r) $，使得数 $x$ 的第一个数字与最后一个数字相等。例如，$101,477474,9$ 是符合这个条件的，而 $47,253,1020$ 则不符合。

请帮助他找到符合这个条件的数的数目。

## 大概思路
对于区间计数，我们可以转换为 $\left  [l,r  \right ]$ 转换为 $\left[1,r  \right ] $ 中符合要求的数减去 $\left  [1,l  \right ) $ 中符合要求的数。

关于区间求答案，我们可以先把区间中 $10$ 以外的数进行判定，对于这些数，将除了最后一位的数字确定下来，然后最后一位也可以确定了，然后再特判一下 $10$ 以内和最大的那个值是否能取到即可。

## Code:

```cpp
#include <iostream>

#define ll long long//不开long long 见祖宗。

inline long long read(){
    long long x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    
    return x*f;
}

inline void print(long long x){
  if(x<0){putchar('-');x=-x;}
  if(x>9){print(x/10);putchar(x%10+'0');}
  else putchar(x+'0');
  return;
}

//快读快写，用 scanf 与 printf 也行。

ll r,l;

inline ll f(ll x){
	if(x<10)
		return x;
		
	ll temp1=x/10+9;
	ll temp2=x%10;
	
	while(x>9)
		x/=10;
		
	return temp1-(x>temp2);	
}

int main(){
	l=read();
	r=read();
	
	print(f(r)-f(l-1));
	
	return 0;
} 

```

[AC 记录](https://www.luogu.com.cn/record/111623536)。

> 我是 CYZ，下期带你看题解。

---

## 作者：Gaode_Sean (赞：0)

我们可以结合数位 dp 的思想解决这道题。

设 $sum_i$ 为 $1 \sim i$ 中首位和末位相同的数，最终的答案即为 $sum_r-sum_{l-1}$。

对于一个数 $i$，我们可以枚举首位和末位相同的数的位数，且这个数小于等于 $i$。

时间复杂度接近 $O(1)$。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll l,r,a[19];
ll Sum(ll n)
{
	if(n<=9) return n;
	ll x=n,z=1;
	while(x>9) x/=10,z++;
	ll ans=((a[z-2]-1)/9+1)*9+(x-1)*a[z-2]+(n/10-a[z-2]*x);
	if(n%10>=x) ans++;
	return ans;
}
int main()
{
	scanf("%lld%lld",&l,&r);
	a[0]=1;
	for(ll i=1;i<=18;i++) a[i]=a[i-1]*10;
	printf("%lld",Sum(r)-Sum(l-1));
	return 0;
}
```

---

