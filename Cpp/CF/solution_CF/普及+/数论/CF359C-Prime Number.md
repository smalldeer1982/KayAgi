# Prime Number

## 题目描述

Simon has a prime number $ x $ and an array of non-negative integers $ a_{1},a_{2},...,a_{n} $ .

Simon loves fractions very much. Today he wrote out number ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF359C/30ceed91a13d03a8240cb0eaa60aa832738192a0.png) on a piece of paper. After Simon led all fractions to a common denominator and summed them up, he got a fraction: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF359C/e0810919ce9aff20137654b00c598ccaa33ece8d.png), where number $ t $ equals $ x^{a_{1}+a_{2}+...+a_{n}} $ . Now Simon wants to reduce the resulting fraction.

Help him, find the greatest common divisor of numbers $ s $ and $ t $ . As GCD can be rather large, print it as a remainder after dividing it by number $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

In the first sample ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF359C/a1e2654626975b2109236cae030121c98f55e9d0.png). Thus, the answer to the problem is $ 8 $ .

In the second sample, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF359C/21aa04c7cee2f3b67d81ff94d48ffd8a4add7ce1.png). The answer to the problem is $ 27 $ , as $ 351=13·27 $ , $ 729=27·27 $ .

In the third sample the answer to the problem is $ 1073741824 mod 1000000007=73741817 $ .

In the fourth sample ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF359C/b75d78ae6544e1f3836b40eca1b29ba08f0f671d.png). Thus, the answer to the problem is $ 1 $ .

## 样例 #1

### 输入

```
2 2
2 2
```

### 输出

```
8
```

## 样例 #2

### 输入

```
3 3
1 2 3
```

### 输出

```
27
```

## 样例 #3

### 输入

```
2 2
29 29
```

### 输出

```
73741817
```

## 样例 #4

### 输入

```
4 5
0 0 0 0
```

### 输出

```
1
```

# 题解

## 作者：是个汉子 (赞：4)

我这个题解**可能**好理解一些。o(*￣▽￣*)o

### Solution

我开始的思路：因为 $x$ 为质数，那 $\gcd$ 肯定是 $x^k$ 啊！不就是找一下 $a_i$ 的最小值，用 $sum$ 一减最后来个快速幂吗，然后样例 $1$ 就干没我了。≧ ﹏ ≦

​		然后发现在提取了最小的因子之后，一些指数变为 $0$ 的数字之和可能是 $x$ 的倍数，所以在我们不断找最小因子的时候需要求+判断指数变为 $0$ 的数字。



细节：因为 $a_i\leq 10^9$ ，如果加起来的可以稍微用扩展欧拉定理将指数取个小模（其实不用，因为~~我没用就过了~~没大多少）

#### 代码

```c++
#include<bits/stdc++.h>
#define ll long long

using namespace std;
const int N=1e5+5,mod=1e9+7;
ll a[N],n,x,cnt,sum,num[N];

inline ll fpow(ll a,ll b){
    ll res=1;
    while(b){
        if(b&1) res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}

ll calc(ll x,ll y){
    ll res=0;
    while(x&&(x%y==0)){
        res++;
        x/=y;
    }
    return res;
}

int main(){
    scanf("%lld%lld",&n,&x);
    for(int i=0;i<n;i++){
        scanf("%lld",&a[i]);
        sum+=a[i];
    }
    for(int i=0;i<n;i++)
        num[i]=sum-a[i];
    sort(num,num+n);
    ll tot=1,now=num[0],tmp;
    int pos=0;
    while(233){
        while(pos+1<n&&num[pos+1]-cnt==now) tot++,pos++;
        cnt+=now;
        if((tot%x)||(now==0)){
            tmp=min(sum,cnt);
            ll ans=fpow(x,tmp);
            printf("%lld\n",ans);
            break;
        }
        now=calc(tot,x);
        if(pos+1<n) now=min(now,num[pos+1]-cnt);//从新定位当前最小的因子
        for(int i=1;i<=now;i++) tot/=x;
    }
    return 0;
}
```



---

## 作者：weihaozhen2010 (赞：1)

# 题意：

[CF359C](https://www.luogu.com.cn/problem/CF359C)

# 思路：

一道数学思维题，根据题目的引导，很容易顺着思路发现：

- 通分后的分母 $t$ 是 $x^{sum}$，其中 $sum$ 表示 $a$ 数组的和。
- 通分后的分子 $s$ 是 $x^{sum-a_1} + x^{sum-a_2} + \dots +x^{sum-a_n}$，同样 $sum$ 表示 $a$ 数组的和。

因此观察第二个样例：

```cpp
3 3
1 2 3
```

我们可以发现：

-  $t = 3^6$。
- $s = 3^5 + 3^4 + 3^3$。
- $s$ 和 $t$ 的最大公约数即为 $x^{mn}$，其中 $mn$ 代表 $s$ 中所有加数的指数的最小值，$x^{mn}$ 即为 $3^3$。

因此计算 $x^{mn}$ 即可，由于 $x$ 和 $mn$ 可能会很大，所以要使用快速幂。

但是可以发现 `WA` 在了第一个样例上：

```cpp
2 2
2 2
```

我们可以发现在这个样例中：

-  $t = 2^4$。
- $s = 2^2 + 2^2$。
- $x^{mn}$ 按上面的思路应为 $2^2$，但是 $s$ 可以化简为 $2 \times 2^2 = 2^3 = 8$。

所以我们还要化简一下 $s$：

```cpp
for(int i=1;i<=n;i++)
{
	if(f[i]>mn) val+=qpow(x,(f[i]-mn),MOD);//f[i]是s内的各个指数
	else val++;
}
```

上面的这段代码会求出来一个 $val$，代表 $s$ 化简后，初始的最大公约数的倍数。对于第二个样例  $val = 13$。因为 $3^5 + 3^4 + 3^3 = 3^3 \times 13$。

接着，只需要看看 $val$ 里面能不能再提取出来一些 $x$ 来就行了。

但是要判断一下最终的最大公约数的指数是否有超过 $t$ 的指数，这是不行的。否则会 `WA` 在第八个点上。

```cpp
if(val>=x)
{
	ll p=0;
	while(val%x==0)
	{
		val/=x;
		p++;
	}
	if(mn+p>sum) mn=sum;
	else mn+=p;
}
```


# 参考代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e5+5,MOD=1e9+7;
ll n,x,sum=0,num=0,val=0,mn=3e18;
ll a[N],f[N];
ll qpow(ll a,ll b, ll p)
{
	ll ans=1,base=a;
	while(b)
	{
		if(b&1) ans=(ans*base)%p;
		base*=base;
		base%=p;
		b>>=1;
	}
	return ans;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>x;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) sum+=a[i];
	for(int i=1;i<=n;i++) f[i]=sum-a[i];
	for(int i=1;i<=n;i++) mn=min(mn,f[i]);
	num=qpow(x,mn,MOD);
	for(int i=1;i<=n;i++)
	{
		if(f[i]>mn) val+=qpow(x,(f[i]-mn),MOD);
		else val++;
	}
	if(val>=x)
	{
		ll p=0;
		while(val%x==0)
		{
			val/=x;
			p++;
		}
		if(mn+p>sum) mn=sum;
		else mn+=p;
	}
	cout<<qpow(x,mn,MOD);
	return 0;
}
```

---

## 作者：Kirisame_Marisa_ (赞：1)

一些记号：记$M=\prod x^{a_i}$（也就是最终分数中的$t$），$S=\sum a_i$（也就是$\log _x t$

------
考虑原式中的第$i$个分数：它原本是$\frac{1}{x^{a_i}}$，通分后变为$\frac{M/x^{a_i}}{M}$。

直接这么一坨除法乘方不好看，因为底数都是相同的（$x$），所以将其化为$\frac{x^{S-a_i}}{x^S}$。这个时候，原问题转化为求$\gcd(\sum x^{S-a_i},x^S)$。

这个式子看起来还是很棘手，所以，举例。  
如果$x=2$，那么原式相当于求$\gcd(\sum 2^{S-a_i},2^S)$。   
考虑这两个数的二进制表达法，后者相当于`1000...000`，前者则是许多`100...000`相加，其中可以有进位。更重要的一点，此时求二者的$\gcd$，并不需要真正去求出两个数再进行辗转相除。  
记二者二进制表达中末尾连续`0`的个数分别为$c_1,c_2$，那么二者的$\gcd=2^{\min(c_1,c_2)}$。因为此时将二者同时向右位移$\min(c_1,c_2)$位，要么是左边的末尾出现`1`，而右边等于$2$的某次方；要么是左边末尾是`0`，而右边等于$1$。显然此时二者的$\gcd=1$，所以上面提到的$\gcd$的计算方法是正确的。

现在将其从$x=2$推广，考虑两个数的$x$进制表达法，可以发现上面的计算方法仍然成立，我们只需要找到两个数末尾`0`的个数。

$a_i$达到了$10^9$级别，所以使用`std::map`（或`std::unordered_map(c++11限定)`）来维护左边的$x$进制表达。同样，我们也不能一位一位枚举其$x$进制中的每一位，所以用`std::set`存下左边开始时哪些位上不是`0`来维护其表达。

时间复杂度：$O(n\log n)$

[code](https://www.luogu.org/paste/y045u199)

---

## 作者：yuhaocheng (赞：0)

**~~鉴于本蒟蒻没太看懂其他的题解，~~ 就来自己写一篇（*可能*会更好理解？）** 

## ~~广告~~ 

同步发表于[这里](https://yhank.top/2022/08/17/CF359C-%E9%A2%98%E8%A7%A3/)**（可能更好的阅读体验）** 

## 题面 

[点这里](https://www.luogu.com.cn/problem/CF359C) 

## 分析 

可以先回忆一下我们平时是如何通分的（以*样例#2*为例）。 

首先，把分母全部乘起来： 

$$\frac{1}{3^1}+\frac{1}{3^2}+\frac{1}{3^3}=\frac{3^2 \times 3^3+3^1 \times 3^3+3^1 \times 3^2}{3^1 \times 3^2 \times 3^3}$$ 

把指数加起来，得到： 

$$\frac{3^5+3^4+3^3}{3^6}$$ 

显然，分子和分母上的任意一个数都是 $3^n$，也就是说：我们只需要找到分子中**次数最低的一项**（$3^3$）去跟分母（$3^6$）比较，输出其中次数更低的一项（$3^3$）即可。 

稍作观察即可得到答案的公式：$ans = \min(sum - a_i)$（其中 $sum$ 表示所有 $a_i$ 的和）。 

**但是**，看到样例一，这里出现了两个 $2$，根据 $ans = \min(sum - a_i)$，此时的答案应为 $2^2=4$，但是实际答案为 $8$。 

为什么？显然是因为 $2^2+2^2=2 \times 2^2=2^3$（只看分母），也就是说，当 $a_i$ 有重复时，要把每个值的个数也考虑进去，比如说，$12$ 个 $2^2$ 就应该写成 $3 \times 2^4$。 

所以我们可以统计每个 ${sum - a_i}$ 的值的出现次数，然后计算**出现次数**中有几个因数 $x$，可以用这样一个函数来实现： 

```cpp
int count(int a, int &b) { // 计算b中有几个因数a，用“&b”是因为处理完后b剩余的数还要用到
	int res = 0;
	while (b && b % a == 0) { // 如果b大于0且还有因数a
		res++; // 个数加一
		b /= a; // 除掉因数a
	}
	return res;
}
```

但是，如果你这样写，还是会 `WA`，因为有可能出现这样的情况： $2^2 \times 8 + 2^3 \times 4 = 2^2 \times 2^3 + 2^3 \times 2^2 = 2^5 + 2^5 = 2 ^ 6$。也就是说，即使考虑了每个 ${sum - a_i}$ 的值的出现次数，在计算的过程中，还是有可能出现**重复的情况**。 

对于这个问题，我的解决办法： 

首先，开一个 `Number` 类型（定义见下方）的优先队列。 

```cpp
struct Number {
	int k; // x的k次方
	int cnt; // 有cnt个
	bool operator>(const Number &_x) const { // 重载大于运算符，优先队列中会用到
		return k > _x.k;
	}
};


priority_queue<Number, vector<Number>, greater<Number>> q;
```

在输入完成后，先预处理出每个 $sum - a_i$，放在 $b$ 数组中，代码如下： 

```cpp
int sum = 0;
for (int i = 1; i <= n; i++) { // 计算a[i]的和
	sum += a[i];
}
for (int i = 1; i <= n; i++) { // 预处理出每个sum - a[i]的值
	b[i] = sum - a[i];
}
```

然后，统计每个 $b_i$ 值的个数，一起 `push` 到优先队列里： 

```cpp
int tmp = 1;
b[0] = -1;
for (int i = n - 1; i >= 0; i--) { // 倒着统计（其实正向也可以）
	if (b[i] != b[i + 1]) {
		// 把sum - a[i]（即b[i]）的值和它的个数一起push到单调队列里
		q.push({b[i + 1], tmp});
		tmp = 0; // 清除计数器
	}
	tmp++; // 计数器加一
}
```

每次取出次数最小的数并不断检查剩下的队首元素，如果次数和当前元素的次数相同，那么就合并 `cnt` 最后，调用上文提到的 `count()` 函数来处理 *$b_i$值的个数*，并把结果乘到当前元素上，把 `count()` 处理完的 `cnt` （也就是不能再拆出 $x$ 了）最为新的 `cnt`，然后重新加入队列；**注意：** 如果 `count()` 函数的返回值为 $0$ ，则意味着 `cnt` 中已经拆不出来因数 $x$ 了，所以此时的答案就是当前元素的次数，可以直接 `break`，代码： 

```cpp
while (!q.empty()) {
	Number f = q.top(); // 每次取出次数最小的数
	q.pop();
	while (!q.empty() && q.top().k == f.k) { // 如果队首元素的次数和当前元素的次数相同
		f.cnt += q.top().cnt; // 合并个数
		q.pop();
	}
	ans = f.k; // 更新答案
	int tmp = count(x, f.cnt); // 计算cnt中能拆出开的因数x的个数
	if (tmp) {
		// k加上处理结果，剩下拆不掉的数仍然作为cnt
		q.push({f.k + tmp, f.cnt});
	} else {
		// cnt中拆不出来因数x了，可以直接结束
		break;
	}
}
```

由于分子的结果可能比分母的次数高，还需要取一下最小值： 

```cpp
ans = min(ans, sum);
```

最后用快速幂算出 $x^{ans}$ 即可。 

## 完整代码

最然看起来很长，其实内容并不多。 

```cpp
/*
*	Author: Hank Yu
*	Problem: CF359C
*	Date: 2022/08/16
*/

#include <bits/stdc++.h>
using namespace std;

#define endl "\n"

void faster_io() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
}

#define int long long

#define MAXN 100005
#define MOD 1000000007

struct Number {
	int k; // x的k次方
	int cnt; // 有cnt个
	bool operator>(const Number &_x) const { // 重载大于运算符，优先队列中会用到
		return k > _x.k;
	}
};

int n, x;
int a[MAXN];
int b[MAXN];
priority_queue<Number, vector<Number>, greater<Number>> q;

int count(int a, int &b) { // 计算b中有几个因数a
	int res = 0;
	while (b && b % a == 0) { // 如果b大于0且还有因数a
		res++; // 个数加一
		b /= a; // 除掉因数a
	}
	return res;
}

int qpow(int x, int k, int q) { // 快速幂模板
	int ans = 1;
	while (k > 1) {
		if (k % 2 == 1) {
			ans *= x;
			ans %= q;
		}
		x *= x;
		x %= q;
		k /= 2;
	}
	if (k == 1) {
		ans *= x;
		ans %= q;
	}
	return ans;
}

signed main() {
	faster_io(); // cin/cout加速
	cin >> n >> x;
	for (int i = 1; i <= n; i++) { // 输入
		cin >> a[i];
	}
	int sum = 0;
	for (int i = 1; i <= n; i++) { // 计算a[i]的和
		sum += a[i];
	}
	for (int i = 1; i <= n; i++) { // 预处理出每个sum - a[i]的值
		b[i] = sum - a[i];
	}
	{ // 防止变量名污染
		int tmp = 1;
		b[0] = -1;
		for (int i = n - 1; i >= 0; i--) { // 倒着统计（其实正向也可以）
			if (b[i] != b[i + 1]) {
				// 把sum - a[i]（即b[i]）的值和它的个数一起push到单调队列里
				q.push({b[i + 1], tmp});
				tmp = 0; // 清除计数器
			}
			tmp++; // 计数器加一
		}
	}
	int ans = 0;
	{ // 防止变量名污染
		while (!q.empty()) {
			Number f = q.top(); // 每次取出次数最小的数
			q.pop();
			while (!q.empty() && q.top().k == f.k) { // 如果队首元素的次数和当前元素的次数相同
				f.cnt += q.top().cnt; // 合并个数
				q.pop();
			}
			ans = f.k; // 更新答案
			int tmp = count(x, f.cnt); // 计算cnt中能拆出开的因数x的个数
			if (tmp) {
				// k加上处理结果，剩下拆不掉的数仍然作为cnt
				q.push({f.k + tmp, f.cnt});
			} else {
				// cnt中拆不出来因数x了，可以直接结束
				break;
			}
		}
	}
	ans = min(ans, sum); // 由于分子的结果可能比分母的次数高，这里需要取最小值
	cout << qpow(x, ans, MOD) << endl;
}
```

## AC

### Upd on 2022/8/30: 更新了某个链接。

### Upd on 2022/9/1上午：在汉字和字母、latex间添加了空格。

### Upd on 2022/9/1下午：再次修改空格，并添加了句号。。。

---

## 作者：xiaorui2007 (赞：0)

### 思路
~~不得不说，Simon 的通分方式很奇怪。~~  
记 $a=\max(a_1,a_2,\dots,a_n),s=\sum\limits_{i=1}^{n}{a_i}$。  
根据正常的通分方法，可以得到：
$$\sum\limits_{i=1}^{n}{\dfrac{1}{x^{a_i}}}=\dfrac{\sum\limits_{i=1}^{n}x^{a-a_i}}{x^a}$$
这样，我们就已经得到了 $x^{s-a}$ 的答案。接下来要求 $\gcd(\sum\limits_{i=1}^{n}x^{a-a_i},x^a)$，记为 $d$。因为 $x$ 为质数，所以 $d=x^\alpha$。以下求 $\alpha$。

记 $b_i=a-a_i$。  
1. $\alpha=0,t=0$。
1. 若 $\alpha=a$，跳至 $6$。
1. 记 $s=b$ 中值为 $\alpha$ 的数的个数。
1. 记 $p=(t+s)\bmod x$。
1. 若 $p$ 不为 $0$，跳至 $6$；若 $p=0$，令 $t=\dfrac{t+s}{x},\alpha=\alpha+1$，跳至 $2$。
1. 现 $\alpha$ 值为所求。

解释一下，这就相当于一个 $x$ 进制加法，求末尾有几个 $0$。
对于从右往左数第 $i$ 位，影响它是不是为 $0$ 的数只有影响第 $1$ 到 $i$ 位的数。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long mod=1e9+7;
int n;
long long x,a[100005],sum/*和*/,ma/*最大值*/;

long long qpow(long long a,long long b)//快速幂
{
	long long ans=1;
	while(b)
	{
		if(b&1)
			ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin>>n>>x;
	for(int i=1;i<=n;sum+=a[i],ma=max(ma,a[i]),i++)
		cin>>a[i];
	a[n+1]=-10000;
	for(int i=1;i<=n;a[i]=ma-a[i],i++);//节省空间，以a代b
	sort(a+1,a+n+1);//排序，便于第3步
	long long p,s=0,i=1;
	for(p=0;p<ma/*必须要，我因为这个没加，WA了十几发*/;s/=x,p++)
	{
		for(;a[i]==p;s++,i++);
		if(s%x)
			break;
	}
	cout<<qpow(x,sum-ma+p)<<endl;
	return 0;
}
```

---

