# Lucky Sum

## 题目描述

Petya loves lucky numbers. Everybody knows that lucky numbers are positive integers whose decimal representation contains only the lucky digits 4 and 7. For example, numbers 47, 744, 4 are lucky and 5, 17, 467 are not.

Let $ next(x) $ be the minimum lucky number which is larger than or equals $ x $ . Petya is interested what is the value of the expression $ next(l)+next(l+1)+...+next(r-1)+next(r) $ . Help him solve this problem.

## 说明/提示

In the first sample: $ next(2)+next(3)+next(4)+next(5)+next(6)+next(7)=4+4+4+7+7+7=33 $

In the second sample: $ next(7)=7 $

## 样例 #1

### 输入

```
2 7
```

### 输出

```
33
```

## 样例 #2

### 输入

```
7 7
```

### 输出

```
7
```

# 题解

## 作者：Withershine (赞：4)

不好意思，又双把通过率拉低了。在 CF 上交了 22 次才过。这里给出不同的写法。

## 思路
规律其他题解写得都很好，这里不需要再讲述如何推出规律。预处理出前 $5000$ 个符合要求的数（其实我也不知道处理多少个刚好够，就随便写了一个数）。接下来借用到一点分块思想，将整个 $[l,r]$ 区间拆成三个大部分：左边散块，右边散块以及中间的整块。这里要运用二分找出 $l$，$r$ 所在的块 $L$ 和 $R$ 中。

对于左右的散块，数学方法 $O(1)$ 处理。对于中间的整块，显然有 $R - L$ 个整块，每块进行单独处理即可。

### 特判
当 $l$ 与 $r$ 在同一个块时直接暴力处理。

## 代码
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<string>
#include<ctime>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<map>
#include<set>
#include<sstream>
#include<cassert>
#define ll long long
#define inf 0x3f3f3f3f
#define fr(i , a , b) for(ll i = a ; i <= b ; ++i)
#define fo(i , a , b) for(ll i = a ; i >= b ; --i)
#pragma comment(linker , "/stack : 200000000")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
inline char gchar()
{
    static char buf[1000000] , *p1 = buf , *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf , 1 , 1000000 , stdin) , p1 == p2) ? EOF : *p1++;
}
inline ll read()
{
    ll x = 0 , f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
	  {
        if(ch == '-')
        {
        	f = -1;
		}
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
	  {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
ll l , r;
ll f[100005] , tag;
inline ll check_l(ll L , ll R , ll x)
{
    while(L < R)
    {
        ll mid = (L + R) >> 1;
        if(f[mid] >= x)
        {
            R = mid;
        }
        else
        {
            L = mid + 1;
        }
    }
    return L;
}
inline ll check(ll L , ll R , ll x)
{
    while(L < R)
    {
        ll mid = (L + R + 1) >> 1;
        if(f[mid] <= x)
        {
            L = mid;
        }
        else
        {
            R = mid - 1;
        }
    }
    return L;
}
signed main()
{
    fr(i , 0 , 5000)
    {
        f[++tag] = f[i] * 10 + 4;
        f[++tag] = f[i] * 10 + 7;
    }
    l = read();
    ll L = check_l(0 , tag , l);
    r = read();
    ll R = check(0 , tag , r);
    if(L == R + 1)
    {
        printf("%lld" , f[L] * (r - l + 1));
        system("pause");
        return 0;
    }
    ll sum = 0 , left = (f[L] - l + 1) * f[L] , right = (r - f[R]) * f[R + 1];
    for(ll i = R - L , block = L + 1 ; i > 0 ; --i , ++block)
    {
        sum += (f[block] - f[block - 1]) * f[block];
    }
    printf("%lld", left + sum + right);
    system("pause");
    return 0;
}
/*
4 7 44 47 74 77 444 447 474 477
*/
```

---

## 作者：WCG2025 (赞：2)

不得不说这道题是一道好题，既有一定的思维难度，同时考察代码实现能力，还能考验细心程度

依照题意，只含有4和7的数字称作幸运数，但是数字过大，打表是肯定不行的了，区间中的数一个一个判断肯定会超时，所以我们应该算出一个幸运数与下一个幸运数之间的区间，直接乘以相加就好了
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
    char ch=getchar();
    int x=0,f=1;
    while(ch<'0'||ch>'9')
    {
       if(ch=='-') f=-1;
       ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
       x=x*10+ch-'0';
       ch=getchar();
    }
    return x*f;
}
int l,r;
long long luck[10000];
int t=3;
long long dfs(int n)//计算从1到n的值为多少
{
    if(n==0)
        return 0;
    long long ans=0;
    for(int i=1;i<=1024;i++)//luck[1000]大概就能水过去了，但保险起见，开大一点
    {
            if(luck[i]<n)
            ans+=luck[i]*(luck[i]-luck[i-1]);//n覆盖了这个区间
            else//n还没覆盖完这个区间
            {	
                ans+=luck[i]*(n-luck[i-1]);
                break;//直接退出
            }
    }
    return ans;
}
int main()
{
    l=read();
    r=read();
    luck[1]=4;
    luck[2]=7;
    for(int i=1;i<=512;i++)//预处理，算出luck数组的值
    {
        luck[t++]=luck[i]*10+4;
        luck[t++]=luck[i]*10+7;
    }
    printf("%lld",dfs(r)-dfs(l-1));//直接相减就好了
    return 0;
}

```
不开long long 一场空！！

---

## 作者：__UrFnr__ (赞：1)

**题目思路**：

这道题确实有点思维含量，你用暴力去做肯定不可行，我们可以去使用前缀和进行优化。如果你学过前缀和，那你应该知道 $[l,r]$ 在这个区间和为 $1\sim r$ 的和减去 $1\sim l-1$ 的和的差，中间过程不再赘述。我们先预处理出 $1\sim10^9$ 所有的 `Lucky Number`，将符合条件的加入数组，接着运用前缀和的思想求出 $[l,r]$ 区间内的 `Lucky Number` 的个数。我们可以写一个函数 $sum$ 来枚举计算出 $[1,x]$ 这个区间内 `Lucky Number` 的个数，接着直接输出 $sum(r)-sum(l-1)$ 的值即可。

制作不易，请多多支持，谢谢！

---

## 作者：boluo2014 (赞：1)

我又有了一个新的想法。应该是对的，大家一起看一下。

### 思路

首先还是和正常思路一样，把 Luck Number 给求出来，很简单。代码：
```
for(i=1;;i++)
{
    if(good[i]*10+7>(LLONG_MAX>>2))
    {
        break;
    }
    n++;
    good[n]=good[i]*10+4;
    n++;
    good[n]=good[i]*10+7;
}
```
注意：要开 long long，否则要见祖宗的！

后续的做法我就和其他人不一样了：

因为按照上面这一段代码进行求 Luck Number，可以使它自动排序，不信的话你可以数出来看看，而且长度也是知道的，那就是我的程序中的 $n$。因为任意两个好数之间会存在一定的间隔，也就是说 $(good_i-good_{i-1})$ 这个值比较大，我们可能会浪费大量的时间。那么这个能否简化呢？很简单，再求最终的答案的时候，中间连续的一段（从 $good_i$ 到 $good_{i+1}$）就是 $i \times (good_{i+1}-good_{i})+i+1$，也可以简化为 $i \times (good_{i+1}-good_i+1)+1$，当然这没有什么意义。

接下来看一下末尾和开头的情况。

#### 末尾

从 $good_{i}$ 到 $x$，值是 $i \times (x-good_i)$。
#### 开头
从 $good_{i}$ 到 $y$，值是 $(y-good_i) \times i$。
而因为最多才多少位啊？直接用 for 循环遍历一次，然后中间、两头相加即可。

完整代码就先不给了，自己想吧！

---

## 作者：Insouciant21 (赞：1)

这道题目实际上就是求这个式子
$$
\sum_{i=1}^rnext(i)-\sum_{j=1}^{l-1}next(j)
$$

可以先预处理出处于 $next(10^9)$ 内的所有的 Lucky Number，即需要求出的最大的 Lucky Number 即 $4444444444$。

因为其已经超过了 `int` 的范围 $2147483647$ ，所以这题需要开 `long long`

#### 计算上面的式子

可以发现对于一段数字，它们的 $next()$ 是相同的，所以分段计算

即可得两个相邻的 Lucky Number $l$ 和 $r$ $(l<r)$ 之间的所有数的取值为 $r$
    
所以有
$$ 
\sum_{i=l}^r next(i)=r\times(r-l)
$$

而当最后 $n$ 已经小于当前 Lucky Number 时，则计算区间内剩余的数的总和，即 $r\times(n-l)$


``` cpp
#include <bits/stdc++.h>

using namespace std;

long long num[10000];

long long sum(int n) {
    if (n == 0)
        return 0;
    long long res = 0;
    for (int i = 1;; i++) {
        if (num[i] < n)
            res += num[i] * (num[i] - num[i - 1]);
        else {
            res += num[i] * (n - num[i - 1]);
            break;
        }
    }
    return res;
}

int main() {
    int l, r;
    cin >> l >> r;
    num[1] = 4, num[2] = 7;
    for (int i = 1, tot = 2; num[i] * 10 + 4 <= (long long)(1e10); i++) {
        num[++tot] = num[i] * 10 + 4;
        num[++tot] = num[i] * 10 + 7;
    }
    cout << sum(r) - sum(l - 1) << endl;
    return 0;
}
```

---

## 作者：xiaohuang (赞：1)

[更好的阅读体验](https://xiaohuang888.github.io/2019/08/07/%E3%80%8E%E9%A2%98%E8%A7%A3%E3%80%8FCodeforces121A%20Lucky%20Sum)

### Description in Chinese

`Petya`喜欢`Lucky Number`。仅含有数字$4$和$7$的数字是一个`Lucky Number`。

规定$next(x)$等于最小的大于等于$x$的`Lucky Number`。现在Petya想知道$next(l) + next(l + 1) + \cdots + next(r - 1) + next(r)$

### Solution

我们可以先预处理出所有的`Lucky Number`。

在询问时，我们可以采用前缀和的思想，题目中的询问可转换为：

$$\sum^{r}_{i = l} \mathrm{next}(i) = \sum^{r}_{i = 1}{\mathrm{next}(i)}- \sum^{l - 1}_{i = 1}{\mathrm{next}(i)}$$

当我们在询问$\sum^{x}_{i = 1}{\mathrm{next}(i)}$是，如果一个个暴力枚举一定会超时。所以我们可以把连续的一段（第一个大于等于$x$的值相同的数）一起加起来。

### Code

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>

using namespace std;

typedef long long LL;
const int MAXN = 2005;
int l, r;
LL f[MAXN];
inline void prepare() {//预处理Lucky Number的值
    f[1] = 4; f[2] = 7;
    int cnt = 2;
    for (int i = 1; i <= 512; i++) {
        f[++cnt] = f[i] * 10 + 4;
        f[++cnt] = f[i] * 10 + 7;
    }
}
inline LL calc(int x) {//计算前n个next(i)的值
    LL ret = 0;
    for (int i = 1; i <= 2000; i++) {
        if (f[i] >= x) {//如果超出了x（也就是累加询问的上界），就加完退出
            ret += f[i] * (x - f[i - 1]);//询问上界的值与最大小于询问上界的值的差，也就是有多少个next(i)要一起累加
            return ret;
        } else ret += f[i] * (f[i] - f[i - 1]);//否则就一段一段加，增加的就是两个相邻的Lucky Number的差
    }
    return ret;
}
int main() {
    scanf("%d%d", &l, &r);
    prepare();
    printf("%lld\n", calc(r) - calc(l - 1));
    return 0;
}
```

---

## 作者：Andy1101 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF121A)
# 思路
首先，暴力一定是不行的。我们可以使用前缀和来计算答案：
$$ \sum\limits_{i = l}^{r}next(i) = \sum\limits_{i = 1}^{r}next(i) + \sum\limits_{i = 1}^{l-1}next(i)$$

## 预处理
我们定义第 $i$ 个幸运数为 $f[i]$。

一开始，我们需要预处理所有的幸运数。

```cpp
void pre() //预处理 1~1e9之间的所有Lucky Number
{
	f[++idx]=4;
	f[++idx]=7;
	for(int i=1;i<=600;i++) //600完全足够 
	{
		//预处理 
		f[++idx]=f[i]*10+4;
		f[++idx]=f[i]*10+7;
	}
}
```
注意：**一定要开 long long**。
## 计算
我们定义 $calc(x) = next(1) + next(2) + \dots + next(x-1) + next(x)$。

我们发现，对于每个 $f[i]$，有 $f[i] \ - \ f[i-1]$ 个数的值为 $f[i]$，此时的求和公式为 $f[i] \times (f[i]-f[i-1])$。

但如果 $f[i] \ge x$，那么刚才的公式就不正确了，此时的求和公式为 $f[i] \times (x-f[i-1])$。

最后输出 $calc(r)-calc(l-1)$。
# AC Code
再提醒一次，**一定要开 long long**。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+5;
long long f[N];
long long idx=0;
void pre() //预处理 1~1e9之间的所有Lucky Number
{
	f[++idx]=4;
	f[++idx]=7;
	for(int i=1;i<=600;i++) //600完全足够 
	{
		//预处理 
		f[++idx]=f[i]*10+4;
		f[++idx]=f[i]*10+7;
	}
}
long long calc(int x) //计算 next(x) 
{
	long long sum=0;
	for(int i=1;i<=1500;i++)
	{
		if(f[i]>=x)
		{
			sum=sum+(f[i]*(x-f[i-1]));
			return sum;
		}
		else
		{
			sum=sum+(f[i]*(f[i]-f[i-1]));
		}
	}
}
int main()
{
	int l,r;
	cin >>l>>r;
	pre();
	cout <<calc(r)-calc(l-1); //绝对不是 calc(r-l) 
	return 0;
}

```

---

## 作者：helongyun (赞：0)

# 题意
这题意思挺明确的，这里就不赘述了。
# 思路
首先考虑暴力，$r$ 有 $10^9$，肯定会超时。
再仔细想，可以先预处理一下，将每一位对应的最小的大于等于 $x$ 的 Lucky Number 求出来，用数组储存，之后做前缀和，每当询问时用前缀和算区间和即可。
# 注意
可以使用 map 数组，以防数组超界。

---

## 作者：Lyw_and_Segment_Tree (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/CF121A)  
## 题意简述
> 首先定义仅含有数字 4 和 7 的数是一个 `Lucky Number`。  
我们定义 $next(x)$ 为最小的、大于等于 $x$ 的 `Lucky Number`。给定两个整数 $l$ 和 $r$，试求出 $next(l) + next(l+1) + \dots + next(r-1) + next(r)$。  

## 开始解题！
如果先预处理出所有范围的 `Lucky Number`，再一个个累加，这样的时间复杂度是 $O(r-l)$ 的，会超时。  
由于无法暴力，考虑正解。  
由于 $x$ 的值和 $next(x)$ 的值相关，所以，我们先列个表来观察 $x$ 和 $next(x)$ 之间的关系。    
[![pihIo0H.png](https://s11.ax1x.com/2023/12/14/pihIo0H.png)](https://imgse.com/i/pihIo0H)  
然后我们发现，在某一段区间内，这些 $next(x)$ 的值是相同的。考虑找规律。  
我们定义 $f_i$ 为第 $i$ 个 `Lucky Number` 所对应的值。那么观察表，可得对于每个 $f_i$，有 $f_i - f_{i-1}$  个的值是 $f_i$。求和式子是 $f_i \times (f_i - f_{i-1})$。然后再次判断，如果某个 $f_i$ 的值大于了 $x$，那么这一状态下的求和程序变为 $f_i \times (x - f_{i-1})$。  
最后我们定义 $calc(x)$ 为 $next(1) + next(2) + \dots + next(x)$ 的和。代入题目，可得答案为 $calc(r) - calc(l-1)$ 的值。  
整理一下，可得代码如下：
## AC 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int f[2025],n;
inline void pre(){
    f[1]=4,f[2]=7;
    int cnt=2;
    for(int i=1;i<=514;i++){
        f[++cnt]=f[i]*10+4;
        f[++cnt]=f[i]*10+7;
    }
}
inline int calc(int x){
    int ans=0;
    for(int i=1;i<=2023;i++){
        if(f[i]>=x){
            ans+=f[i]*(x-f[i-1]);
            return ans;
        }else ans+=f[i]*(f[i]-f[i-1]);
    }
}
signed main(){
    int l,r;
    cin>>l>>r;
    pre();
    cout<<calc(r)-calc(l-1)<<endl;
}
```  
[AC 记录](https://www.luogu.com.cn/record/139618539)

---

## 作者：InfSauf (赞：0)

由题，Lucky number是由 $4$ 和 $7$ 组成的数字，例如： $47444$，$477777$ 就是Lucky number，而像 $114514$，$1919810$，这种就不是Lucky number。

因为题目要我们求 $\sum\limits_{i=l}^{r}{next(i)}$，所以我们开始处理 $\sum\limits_{i=l}^{r}{next(i)}$，因为是区间求和，所以我们将这个式子进行变形，可得：

$$\sum\limits_{i=l}^{r}{next(i)}=\sum\limits_{i=l}^{r}{next(i)}-\sum\limits_{i=l}^{l-1}{next(i)}$$

我们可以先预处理一下Lucky number，只需要将符合条件的数按顺序放入数组即可，预处理部分：

```cpp
int a[1145];
void init(){
	int t = 0;
	for(int i = 1; i <= 520; i++){
		if(i == 1){
			a[++t] = 4;
			a[++t] = 7;
		}
		a[++t] = a[i] * 10 + 4;
		a[++t] = a[i] * 10 + 7;
	}
}
```

然后我们将这个之前式子的两个部分分别用代码实现，两部分代码类似，如下：
```cpp
int sum = 0;
	for(int i = 1; i <= 11451; i++){
		if(a[i] >= r){
			sum += a[i] * (r - a[i - 1]);
			break;
		}
		else {
			sum += a[i] * (a[i] - a[i - 1]);
		}
	}
	int sum1 = 0;
	for(int i = 1; i <= 11451; i++){
		if(a[i] >= l - 1){
			sum1 += a[i] * (l - 1 - a[i - 1]);
			break;
		}
		else {
			sum1 += a[i] * (a[i] - a[i - 1]);
		}
	}
```

最终的代码如下：

```cpp
#include <bits/stdc++.h>
#include <string>
#define int long long
using namespace std;
int k;
int a[1145];
int func(int a,int k)
{
    int res = 0;
    while(k){
        if(k & 1)res += a;
        k >>= 1;
        a += a;
    }
    return res;
}

void init(){
	int t = 0;
	for(int i = 1; i <= 520; i++){
		if(i == 1){
			a[++t] = 4;
			a[++t] = 7;
		}
		a[++t] = func(a[i], 10) + 4;
		a[++t] = func(a[i], 10) + 7;
	}
}
signed main(){
	init();
	int l, r;
	cin >> l >> r;
	int sum = 0;
	for(int i = 1; i <= 11451; i++){
		if(a[i] >= r){
			sum += a[i] * (r - a[i - 1]);
			break;
		}
		else {
			sum += a[i] * (a[i] - a[i - 1]);
		}
	}
	int sum1 = 0;
	for(int i = 1; i <= 11451; i++){
		if(a[i] >= l - 1){
			sum1 += a[i] * (l - 1 - a[i - 1]);
			break;
		}
		else {
			sum1 += a[i] * (a[i] - a[i - 1]);
		}
	}
	int ans = sum - sum1;
	cout << ans;
}
```


---

