# Really Big Numbers

## 题目描述

Ivan likes to learn different things about numbers, but he is especially interested in really big numbers. Ivan thinks that a positive integer number $ x $ is really big if the difference between $ x $ and the sum of its digits (in decimal representation) is not less than $ s $ . To prove that these numbers may have different special properties, he wants to know how rare (or not rare) they are — in fact, he needs to calculate the quantity of really big numbers that are not greater than $ n $ .

Ivan tried to do the calculations himself, but soon realized that it's too difficult for him. So he asked you to help him in calculations.

## 说明/提示

In the first example numbers $ 10 $ , $ 11 $ and $ 12 $ are really big.

In the second example there are no really big numbers that are not greater than $ 25 $ (in fact, the first really big number is $ 30 $ : $ 30-3>=20 $ ).

In the third example $ 10 $ is the only really big number ( $ 10-1>=9 $ ).

## 样例 #1

### 输入

```
12 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
25 20
```

### 输出

```
0
```

## 样例 #3

### 输入

```
10 9
```

### 输出

```
1
```

# 题解

## 作者：Fan_Tuan (赞：7)

## 题意：
统计从 1 到 $n$ 中有几个数减去其各数位之和后大于等于 $s$。

## 思路：
枚举.
可以发现小于 $s$ 的数是不符合要求的，所以这部分我们可以直接省掉。

对于大于 $s + 9 * 18$ 的数一定是符合要求的，这相当于每一位都是 9 的情况，这一部分我们可以直接加上。

对于中间的部分，我们直接枚举判断就能通过此题。

## 代码：
```c
#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#define int long long
using  namespace  std;

inline int read() {
	int f = 0, s = 0;
	char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
	return f ? -s : s;
}

void print(int x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

int n, s;

signed main() {
	n = read(), s = read();
	if (n < s) {
		print(0);
		return 0;
	}
	int ans = 0;
	if (n - s - 9 * 18 > 0) ans += n - s - 9 * 18, n = s + 9 * 18;
	for (int i = s; i <= n; i++) {
		int x = i, sum = 0;
		while (x) {
			sum += (x % 10);
			x /= 10;
		}
		if (i - sum >= s) ans++;
	}
	print (ans);
	return 0;
}
```


---

## 作者：Node_Edge (赞：7)

**题面**

统计从 1 到 $n$ 中有几个数减去其各数位之和后大于等于 $s$。

**思路**

此题具有单调性，可写个暴力验证。

所以二分一下边界即可，时间复杂度是 $\mathcal O(\log n)$。

**代码**

```cpp
#include<iostream>
using namespace std;
long long n,s;
long long check(long long x) {//判断  
	int sum=x,ans=0;
	while (sum) {
		ans+=sum%10;
		sum/=10;
	}
	return x-ans;
}
int main() {
	ios::sync_with_stdio(false);//关闭同步
	cin.tie(0);
	cout.tie(0);
	cin>>n>>s;
	int l=0,r=n+1;
	while (l+1<r) {
		int mid=(l+r)/2;
		if (check(mid)<s) l=mid;
		else r=mid;
	}
	cout<<n-l;//输出区间 
	return 0;
}
```


---

## 作者：hayzxjr (赞：3)

upd on 2023/10/21：修改了证明中不严谨之处以及码风，补充了许多内容。

## 题意分析

> 定义 Realy Big Number（下文简记作 $\text{RBN}$）为本身减去各数位上的数之和大于等于 $s$ 的数，统计 $[1, n]$ 中的 $\text{RBN}$ 的个数。

$n$ 的上界为 $10^{18}$，枚举不够优秀。

既然一般的 $\mathcal{O}(n)$ 算法无法解决，我们可以考虑分析样例，寻找一般 **结论**（或说是规律），以便进行优化：

```
//Input 1
12 1

//Output 1
3

//Input 2
25 20

//Output 2
0

//Input 3
10 9

//Output 3
1
```

可以发现样例一中的 $3$ 个数是 $10$，$11$，$12$；

样例二中由于第一个满足条件的数是 $30$，故没有答案；

样例三中满足条件的只有 $10$ 一个数。

可以猜想：

> 答案具有单调性！

（当然，此步猜想建立于对数学结论有充分的敏感之上，或许得出猜想才是本题成为蓝题的原因所在）

## 单调性证明

对于任意一个数 $s$，一定存在 $\text{RBN}$。可以考虑构造一个充分大的 $10^n$，其各数位上的数之和为 $1$，结论显然。

于是我们设 $s$ 的第一个 $\text{RBN}$ 为 $x$（显然 $x\ge s$），记 $f(x)$ 等于 $x$ 的各数位上的数之和，则有： 

$$x - f(x) \ge s$$

接下来要证明的是每一个大于 $y$ 的正整数都是 $\text{RBN}$，发现目标等价于：

$\forall d \in \mathbb{N}_{+}$，都有 $d \ge f(d)$，等号当且仅当 $1 \le d \le 10$ 时成立。

**证明**

我们对 $d$ 作十进制分解：$d = \sum_{i = 0}^{n}p_i \times 10^i$，其中 $0 < p_i < 10$ 且为整数，可得 $f(d) = \sum_{i = 0}^{n}p_i$，可以 **逐项比较** 得出两者大小，此处不再赘述。

并且，我们可以得到这样一个 **推论**：

> $d$ 的增长比 $f(d)$ 来得快。

可以感性理解：$d$ 增长得过程中会遇到逢十进一得情况，这样对 $d$ 来说是好的，可以 $f(d)$ 的几个 $9$ 就会变成 $1$，是亏损的。

总之，我们只需要找出第一个 $\text{RBN}$，就可以肯定大于等于这个数的所有数都满足要求。

## 实现

代码实现中，我们可以直接使用 `while` 来寻找第一个 $\text{RBN}$，当然也可以设置上界进行二分查找，但此处没有必要。

注意细节：

1. 不开 `long long` 见祖宗。
2. 当第一个真正大数大于 $n$ 的时候输出 $0$.

参考代码：

```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
ll n, s;
ll check(ll x, ll y){
	int tot = 0;
	while(y){
		tot = tot + (y % 10);
		y = y / 10;
	}
	return (x - tot) >= s;
}
int main(){
	scanf("%lld %lld", &n, &s);
	ll ans = s;
	while(check(ans, ans) == false) ans++;
	if(ans > n) printf("0\n");
	else printf("%lld\n", n - ans + 1);
	return 0;
}
```

参考代码中给出的 $\text{check}$ 即判断是否为 $\text{RBN}$ 的函数，复杂度是常数的。

整体复杂度也几乎是常数的。

---

## 作者：hanzhongtlx (赞：3)

这玩意一猜就有单调性啊，不信你可以手玩一下。 

而且发现还是 $10$ 个数一段的那种。  

所以二分一下边界即可，时间复杂度是 $\mathcal O(\log n)$。  

```
#include"iostream"
#include"cstdio"
#include"cstring"
#include"cmath"
using namespace std;

#define ll long long 
#define read(x) scanf("%lld",&x)
#define MAXN 1000000000000000002

ll n,s;

ll f(ll a)
{
    ll sum=a;
    while(a)
    {
        sum=sum-a%10;
        a/=10;
    }
    return sum;
}

int main()
{
    read(n),read(s);
    ll l=1ll,r=MAXN,mid;
    while(l<r)
    {
        mid=(l+r)>>1;
        if(f(mid)<s) l=mid+1;
        else r=mid;
    }
    printf("%lld\n",max((ll)0,n-l+1));
    return 0;
}
```

---

## 作者：3_soon (赞：2)

# 这题不难
 但一点都不简单
## 1）前置芝士
*******817，不多说，再说枪毙**

## 2）思路

先看看数据，找出些规律
![](https://cdn.luogu.com.cn/upload/pic/73789.png)

 不难发现，s都为9的倍数，且在连续10个n中都相同。（严谨证明很简单，~~在这里不做解释~~）
 
  **_注意：s每次增加时，不一定只增加10（比如n=90,n=100之间）_** 
  
 再枚举一下，会发现\[s/10]必小于\[n/10];
 
 现在我们知道了s的值，个么就从这里下手；
 
 感性理解一下，s的值是不降的，所以找出起点 n' 即可。（n'为10的倍数）
 
### 来枚举 n' 吧！

易证（感性理解）， s' 必小于其对应的 n' ；故从s开始枚举。

这时，枚举的下界定了，那么上界呢？在数据范围中。n最大为1e18，所以数位和最大时，即每位都是9，即n最多比s大 18*9=162.所以，上界就为s+162。（由上性质，故可枚举时每次+=10）


hin简单，当你枚举的 n' 所对应的 s' 大于给出的 s 时，说明这个 n' 也许过大（可能刚好）了，于是要让 n'-=10 ，相应的，再算一次 s' 。

这时，s'<=s，分类讨论一下；

如果s'==s，那么起点刚好是n'；

如果s'<s，那么起点 n' 也小了，就是说n'要+10（变大）。

这里可能存在找不到数（ans=0）的情况，如上ans会为负，所以加个特判就ok。


------------

代码：

```c++
#include<bits/stdc++.h>
using namespace std;
#define ll long long
long long n,s;
long long sum;
ll ans;
void deal(ll x)
{
	sum=0;
	while(x)
	{
		sum+=x%10;
		x/=10;
	}
}

int main()
{
	cin>>n>>s;
	if(s/10>=n/10) 
	{
		printf("0\n");
		return 0;
	}
	else
	{
		ll p=s/10+1;
		p*=10;
		for(int i=0;i<=20;i++)
		{
			p+=10;
			deal(p);
			if(p-sum>s) break;
		}
		p-=10;
		deal(p);
		ans=n-p+1;
		p-=sum;
		if(s>p) ans-=10;
		printf("%lld\n",max(0LL,ans));
	}
	return 0;
}
```

---

## 作者：Hisaishi_Kanade (赞：0)

设数字和为 $p_n$。

显然，$p_{n+1}-p_n\le 1$

即 $p_{n+1}\le p_n+1$

转化一下：

$n-p_{n+1}\ge n-p_n-1$

$n+1-p_{n+1}\ge n-p_n$

设 $f_x=x-p_x$，则由上显然若 $y>x$，$f_x\le f_y$。

则可以二分出最小的满足条件的值 $k$，由上对于任意满足 $k\le i\le n$ 的正整数 $i$ 都满足条件。

```cpp
#include <stdio.h>
long long n,s,l,r,mid,ans;
inline const bool check(long long x)
{
	static long long rem,sum;
	rem=x;sum=0;
	while(rem)
	{
		sum+=rem%10;
		rem/=10;
	}
	return x-sum>=s;
}
int main()
{
	scanf("%lld %lld",&n,&s);
	l=1;r=n+1;
	ans=-1;
	while(l<=r)
	{
		mid=l+r>>1;
		if(check(mid))
		{
			r=mid-1;
			ans=mid;
		}else
			l=mid+1;
	}
	if(ans==-1)
		puts("0");
	else
		printf("%lld",n-ans+1);
	return 0;
}

```

---

## 作者：loser_seele (赞：0)

我们企图得到一个枚举次数更少的做法。

首先要证明的结论是答案单调性，这个其他题解里有的有提及，有的没有具体证明，所以还是证明一下。

设 $ f(x) $ 为数位和，不难发现 $ f(x+1) \leq f(x)+1 $，这点显然，因为对于每一个数位，增加要么来自加操作，这只能使得数位和 $ +1 $，要么来自进位，但是每次进位总数位和都会减少。

于是我们需要证明 $ g(x)=x-f(x)-((x-1)-f(x-1)) \geq 0 $，这个是单调性的前提。

拆式子得到 $ g(x) \geq x-f(x-1)-1-((x-1)-f(x-1))=0 $，于是单调性得证。

接下来的做法是两个做法的结合：分析答案上界和二分。

然后发现 $ f(x) $ 最大为 $ 19 \times 8=162 $，则 $ (s+f(s))-s $ 是一种可能的构造，于是答案最大的上界为 $ s+f(s) $，这里手懒取 $ 162 $，不影响后面复杂度的分析。

因为当 $ i \leq s $ 的时候 $ i-f(i) \leq s $，所以答案的下界显然是 $ s $。于是我们确定了答案的上下界 $ [s,s+162] $，在这个范围内二分答案即可。

因为区间长度为 $ 163 $，所以只需要 $ 8 $ 次判断答案合法性即可通过本题，优于所有其他题解的复杂度。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,s;
int check(int x) 
{  
	int sum=x,ans=0;
	while (sum) 
	ans+=sum%10,sum/=10;
	return x-ans;
}
signed main() 
{
	cin>>n>>s;
	int l=s,r=s+162;
	while (l+1<r) 
    {
		int mid=(l+r)/2;
		if (check(mid)<s) 
        l=mid;
		else
        r=mid;
	}
	cout<<max(0ll,n-l);
}
```


---

## 作者：yuheng_wang080904 (赞：0)

## 题意

给定 $n(1\le n\le 10^{18})$ 和 $s(1\le s \le 10^{18})$，求出 1 到 $n$ 里有多少个数满足它与它的十进制数位之和的差不小于 $s$。

## 思路

###### ~~这题有兴趣的可以写下数位 dp，这里不多赘述。~~

枚举肯定会超时，那怎么办呢？

设一个数 $x$ 的数位之和为 $sd(x)$。很容易发现对于任意一个整数 $x$，$x\ge sd(x)$ 而且 $sd(x+1)\le sd(x)+1$。假如整数 $x$ 满足条件，则有 $s\le x-sd(x)$，则 $s\le x+1-sd(x+1)$，因此 $x+1$ 也满足条件。这样就证明出了：若整数 $x$ 满足条件，则 $x+1$ 也满足条件。

这样就很容易发现，我们只需要求出 $x_{min}$，就能够用 $n-x_{min}+1$ 求出答案。那么便会想到，可以二分来求 $x_{min}$ 。

还有写起来更容易的方法。

很容易发现，若整数 $x<s$，则 $x$ 不可能满足条件。而且因为 $n\le 10^{18}$，所以 $sd(x)\le 9\times 18=162$。于是我们可以从 $x=s$ 开始，已知枚举到 $x=s+162$，看它是否满足条件。当 $x>s+162$ 时，$x-sd(x)>s$，均满足条件，答案就是枚举的满足条件的总数与 $x>s+162$ 的数字的总个数之和。

## 代码

两个求解函数分别对应着两种思路，大家可以参考一下。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,s,cnt;
int sd(long long x){
    int ans=0;
    while(x){ 
	ans+=x%10;
	x/=10;
    }
    return ans;
}
void solve(){
    cin>>n>>s;
    long long l=1,r=n+1;
    while(l<r){
	long long mid=(l+r)/2;
	if(mid-sd(mid)>=s)r=mid;
	else l=mid-1;
    }
    cout<<n-l+1<<endl;
}
void solve_again(){
    cin>>n>>s;
    for(long long x=s;x<=min(s+9*18,n);x++){
	if(x-sd(x)>=s)cnt++;
    }
    cout<<max(0ll,n-(s+9*18))+cnt<<endl;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();//二分
    solve_again();//(部分枚举)
    return 0;
}
```


---

## 作者：_szs9601 (赞：0)

#### 题意
统计从 1 到 $n$ 中有几个数减去其各数位之和后大于等于 $s$。
#### 思路
打个暴力程序，我们可以发现，每个数减去其各数位之和后还是递增的，所以我们很容易就想到了二分。所以直接二分最小的那一个符合的数字就可以了。
#### 单调性证明
对于每一个数字 $s$，设其各数位之和为 $x$。

当 $s$ 加 1 且不进位时，$x$ 也同样加 1，所以 $s-x$ 是不变的。

当 $s$ 加 1 且进位时，个位从 9 变成了 0，十位加了 1。显然，每一次进位都会让 $x$ 减去 8。所以 $s-x$ 是增大的。

即 $s-x$ 具有单调性。
#### 代码
```cpp
#include<bits/stdc++.h>
#define LL long long//别忘了开long long
using namespace std;
LL n,m,t,w,mid,ans;
bool pd(LL x){//判断
	LL s=0,xx=x;
	while(xx) s+=xx%10,xx/=10;//减去各数位之和
	return x-s>=m;//减去其各数位之和后大于等于s
}
int main(){
	scanf("%lld%lld",&n,&m);
	t=1LL;w=n;ans=-1;
	while(t<=w){
		mid=(t+w)>>1;
		if(pd(mid)) ans=mid,w=mid-1;
		else t=mid+1;
	}//二分最小的那一个符合的数字
	if(ans==-1) printf("0\n");
	else printf("%lld\n",n-ans+1);
	return 0;
}
```



---

## 作者：BMTXLRC (赞：0)

我本来想写数位 DP 的，发现 DP 数组开不了那么大，放弃了。

**推论 $1$：** $\forall x\in[0,+\infty)$，$x$ 的答案等于 $x-x\%10$ 的答案。

这个证明很简单，设末位为 $k$，除末位以外数字和为 $p$：

$$
x-p-k=(x-k)-p
$$

得证。换句话说，$114514$ 的答案一定等于 $114510$ 的答案，每十个数的答案都是相同的。

**推论 $2$：** 答案**单调**。我们设 $f(x)$ 表示 $x$ 与 $x$ 的数字和的差（以下均采用这个记法）：

$\forall x_1-x_2=10,x_1\equiv 0\pmod{10}$，讨论：

1. 存在进位的情况，如 $990$ 与 $1000$。设进了 $j$ 次位，则进位后的 $x_1$，其 $sum_{x_1}=sum_{x_2}-9j+1$。而 $x_1-x_2=10$，故：

$$
f(x_1)-f(x_2)=x_1-x_2-(sum_{x_2}-9j+1)+sum_{x_2}=9+9j\geqslant 0
$$

故这种情况下必然单调。

2. 不存在进位的情况，如 $50$ 和 $60$，此时 $j=0$，上式仍然成立，这种情况也必然单调。

**推论 $3$：**$\forall s\in[1,10^{18}]$，$\exists x\leqslant 9\times 18$，使得 $[x,+\infty)$ 中所有数的数字和都大于等于 $s$。

这个很好证，由于答案单调，我们直接考虑最大的 $s$，它对应的最小 $x$ 是多少。构造得到 $s=10^{18}-1,x=17\times 9$。换句话说，这个 $x$ 取决于你能进多少个 $9$。

这条推论的意义在于，对于所有大于等于 $s+18\times 9$ 的数，其答案都大于等于 $s$。

**推论 $4$：** 所有小于 $s$ 的数，其答案必定小于 $s$。

这个很好证的，$sum(s)$ 最小都是 $1$（除了 $0$ 以外，但没啥意义。。），又因为答案单调，所以小于 $s$ 的数没有一个答案会大于等于 $s$。

嘿，有了这四条，我们就可以得出算法步骤：

- 排除掉所有 $x<s$
- 计算 $n-s-9\times 18$ 的答案
- 循环找到 $[s,s+9\times 18]$ 中所有满足条件的数。

**最后别忘了特判 $n<s$。**

代码如下：

```cpp
//CF817C
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,s,ans=0;
signed main(){
    scanf("%lld %lld",&n,&s);
    if(n<s){
        printf("0");
        return 0;
    }
    if(n-s-9*18>0){
        ans+=n-s-9*18;
        n=s+9*18;
    }
    for(register int i=s;i<=n;i++){
        int x=i,sum=0;
        while(x!=0) sum+=x%10,x/=10;
        if(i-sum>=s) ans++;
    }
    printf("%lld",ans);
}
```

---

