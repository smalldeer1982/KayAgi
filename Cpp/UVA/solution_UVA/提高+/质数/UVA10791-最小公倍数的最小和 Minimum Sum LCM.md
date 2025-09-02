# 最小公倍数的最小和 Minimum Sum LCM

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=19&page=show_problem&problem=1732

[PDF](https://uva.onlinejudge.org/external/107/p10791.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10791/46b9c621d71e185653bf0a7197761eb0efdc4589.png)

## 样例 #1

### 输入

```
12
10
5
0```

### 输出

```
Case 1: 7
Case 2: 7
Case 3: 6```

# 题解

## 作者：Larry76 (赞：10)

## 前言：

#### 数学符号约定：

1. $p$ ：任意一个质数
  
2. $n$ 或 $m$：任意一个正整数
  
3. $a_i$：唯一分解时质数的指数
  
4. $A$：集合
  

若无特殊说明，本篇题解的数学符号将会严格按照上述符号进行编写。

## 题目描述：

给定一个数 $n$，求出**至少两个数**，使得他们的**最小公倍数**为 $n$，且相加最小。

## 题目分析：

首先，我们浅浅的思考一下，很容易得出一个结论，多个数的最小公倍数其实就是他们唯一分解后每个质数的最小幂的乘积。打个比方，比如对于 $12$ 和 $30$ 来说，对他们分别进行唯一分解后，得出的结果分别是：

$$12=2^2 \times 3^1$$
$$30=2^1 \times 3^1 \times 5^1$$

所以他们的最小公倍数就是：

$$
\operatorname{lcm}(12,30)=2^2 \times 3^1 \times 5^1 = 60
$$

根据这个结论，我们可以反向思考，对一个数来说，其唯一分解出的每个质数幂所组成的集合中所有元素的最小公倍数必定是这个数，举个例子，对于 $1890$ 来说，对其进行唯一分解后得出的结果为：

$$
1890 = 2^1 \times 3^3 \times 5^1 \times 7^1
$$

所以，分解出的每个质数幂所组成的集合 $A$ 为：

$$
A=\{2^1,3^3,5^1,7^1\}
$$

由此，我们不难看出，集合 $A$ 中的所有元素的最小公倍数即为：

$$
\operatorname{lcm}(A)=\operatorname{lcm}(2^1,3^3,5^1,7^1)=2^1 \times 3^3 \times 5^1 \times 7^1 =1890
$$

现在，我们再思考另一个问题，对于多个大于 $1$ 且两两不同的正整数来说，如何在他们的乘积不变的情况下相加最小。

首先，对于两个正整数 $n$ 和 $m$ （$n$ 和 $m$ 都大于 $1$，且保证 $n$ 和 $m$ 不同）来说，我们可以十分轻易地看出来，$n \times m$ 一定是大于 $n + m$ 的。证明如下：

$$
\begin{array}{r}
(n-1)\times(m-1) > 1\\
n \times m - n - m + 1 > 1\\
n \times m - n - m >0\\
n \times m > n+m
\end{array}
$$

所以，对于任意一个非质数幂**合数** $n$，若有多个整数的最小公倍数为它，则这些整数的和的最小值就应当为合数 $n$ 唯一分解后的质数幂的和。

那么对于质数幂来说，就不适用上面的结论了，因为质数幂的唯一分解还是其本身，不满足题目条件“至少两个数”，解决方法也十分简单，如果一个数为质数幂，那么它的结果就应当是其本身加 $1$。

那么，问题又来了，我们需不需要判断他是不是质数幂呢，答案显然是不需要，我们只需要在唯一分解时，判断这个数是否只由一种质数组成即可。

## 代码实现：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int ResolveNumber(int n) { //唯一分解并求得答案。 
    int fin = sqrt(n); 
    int kinds = 0; //质数的种类个数。 
    int answer = 0; 

    for (int i = 2; i <= fin; i++) {
        int power = 0;

        if (n % i == 0) {
            kinds++;
            power = 1;
        }

        while (n % i == 0) {
            n /= i;
            power *= i;
        }

        answer += power;
    }

    if (n > 1) {
        answer += n;
        kinds++;
    }

    if (kinds == 1) //如果只有一种质数，则证明其为质数或质数幂，那我们就把结果加 1。 
        ++answer;

    return answer;
}
signed main() {
    int cnt = 0;

    while (1) {
        int n;
        cin >> n;

        if (n == 0) 
            break;

        if (n == 1) //特判一下 1。 
            printf("Case %lld: 2\n", ++cnt);
        else
            printf("Case %lld: %lld\n", ++cnt, ResolveNumber(n));
    }

    return 0;
}
```

---

## 作者：Citnaris (赞：4)

# UVA10791 最小公倍数的最小和

设这个数为
$$x=p{\tiny 1}^{a{\tiny 1}} \times p{\tiny 2}^{a{\tiny 2}} \times......\times p{\tiny n}^{a{\tiny n}} $$
则：

①$p{\tiny x}^{a{\tiny x}}$与$p{\tiny y}^{a{\tiny y}}$(都$>1$)要放在两个数里，而不是相乘放在一个数里，因为对于$m,n>1$，有：
$$(m-1)\times (n-1)>1,m\times n-m-n+1>1,m\times n-m-n>0$$
所以
$$m\times n>m+n$$
即相乘比相加大，所以不能相乘。

②一个数$x$若包含$p{\tiny y}$，则要包含其最高次数。

所以答案
$$ans=p{\tiny 1}^{a{\tiny 1}}+p{\tiny 2}^{a{\tiny 2}}+......+p{\tiny n}^{a{\tiny n}} $$

**$code$**
```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<iostream>
using namespace std;
long long n,ans,cnt,q;
int num;
void solve()
{
    int tmp=n;
    while(n%q==0) n/=q;
    if(tmp/n>1) ans+=(tmp/n),num++;
    return;
}//加上px^ax
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    while(cin>>n&&n!=0)
    { 
        cnt++;
        ans=0;
        for(q=2;q<=sqrt(n);q++) solve();
        if(n>1) ans+=n,num++;
        if(num==0) ans+=2;
        if(num==1) ans+=1;//特判
        printf("Case %lld: %lld\n",cnt,ans);
        num=0;//清零
    }
    return 0;
}
```
注意：

①不开$long$ $long$见祖宗

②不用特判$p{\tiny x}$是否是质数，因为如果其是合数，在它$solve$的时候，$n$已经不是它的倍数了，因为它的因子已经取完了，复杂度便从$O(\sqrt{n})$变成了$O(1)$。

---

## 作者：pufanyi (赞：4)

首先，我们把问题简化：输入正整数$n$，求几个正整数（可以是一个），是它们的最小公倍数为$n$，且这些整数的和最小。输出最小的和。

我们考虑$n$是素数时，不难证明只有一个数$n$，那么如果要求至少要分解成两个，那么只能在加一个$1$。

当$n$是合数时。如果$n$能被分解为两个大于$1$的互质整数的积$a_1,a_2$，由于$(a_1,a_2)=1$，如$[a_1,a_2]=a_1\times a_2$，又由于$a_1>1,a_2>1$，那么$a_1+a_2<a_1\times a_2$，所以我们要把它分解开来。这样，我们就把问题转成了上面简化问题中$n=a_1,n=a_2$的子问题。如此递归下去，我们发现：设$n$的标准分解式为$n=p_{1}^{a_1}p_{2}^{a_2}\cdots p_x^{a_x}$，当所有数分别为$p_{x_0}^{a_{x_0}}$时最小。

此外，我们还要特判一下开始$n=p^a$的情况。此时$n$无法继续分解，则$ans=n+1$。最后，记得当$n=1$时，$ans=2$。

然后我们来看实现问题。

从$1$枚举到$n$？TLE。

是否记得判断一个数是素数的时候（在学会Miller-Rabin之前我们通常是从$1$枚举到$\sqrt{n}$），这题可以吗？

我们发现对于任意正整数$n$，在超过$\sqrt{n}$且不等于$n$的数中，最多只有一个。如果有两个，那么它们的乘积就已经超过$n$了。那么我们就只要枚举$\sqrt{n}$个数即可。

### 代码

```cpp
#include <cstdio>

typedef long long LL;

int nn;

inline void sol(LL n)
{
	int f=0;
	LL ans=0;
	if(n==1)//对1的特判
	{
		printf("Case %d: 2\n",++nn);
		return;
	}
	LL ttt,tn=n;
	for(LL i=2; i*i<=n; ++i)//计算标准分解式，枚举到sqrt即可
	{
		ttt=1;
		if(!(n%i) && (n!=1))
		{
			do
			{
				ttt*=i;
				n/=i;
			}
			while(!(n%i) && (n!=1));
			f++,ans+=ttt;
		}
		if(n==1) break;
	}
	if(tn==n || f==1) ans++;
		//tn==n:n是素数，f==1:n不是素数但除1与n外的因子只有一个
	if(n!=1) ans+=n;//在sqrt(n)以上除n外还有一个n的因子
	printf("Case %d: %lld\n", ++nn, ans);
		//最后一行的换行让我很惊讶(UVa什么时候对输出这么随意了?)
	return;
}

int main()
{
	LL n;
	while(scanf("%lld", &n) && n) sol(n);
	return 0;
}
```



---

## 作者：Wi_Fi (赞：2)

先说结论：设将 $n$ 分解成 $n= p_1^{a_1} \times p_2^{a_2} \times ...... \times p_n^{a_n}$ 的形式，则每个 $p_i^{a_i}$ 作为一个单独的整数时最优。

简单的证明：

- 每个质因子 $p_i^{a_i}$ 只存在于一个数字中，答案是最优的。因为如果有两个数都存在质因子 $p_i^{a_i}$，显然去掉其中一个之后，最小公倍数不会改变，但和会变小。
- 每个质因子 $p_i^{a_i}$ 只单独地存在于一个数字中，答案是最优的。因为如果有一个数 $n = p_i^{a_i} \times p_j^{a_j}$，显然把它替换为 $p_i^{a_i} $ 和 $ p_j^{a_j}$ 两个数后，最小公倍数不会改变，但和会变小。

但是如果你直接交肯定是错的，因为有特殊情况：

- $n = 1$ 时，答案为 $2$。
- $n$ 只有一个因子（即为某一个正整数的幂）时，答案额外加 $1$。
- 不开 $long$ $long$ 见祖宗哦。


简单的代码：
```cpp
#include<bits/stdc++.h>

using namespace std;

long long i,n,k,ans,sum;
int main()
{
	while(cin>>n&&n)
	{
		ans=sum=0;
		for(i=2;i*i<=n;i++)
		{
			int m=n;
			while(n%i==0)n/=i;
			if(m/n>1)ans+=m/n,sum++;
		}
		if(n>1)ans+=n,sum++;
		cout<<"Case "<<++k<<": "<<ans+(sum==1)+(sum==0)*2<<"\n";
	}
	return 0;
}
```


---

## 作者：小闸蟹 (赞：1)

```cpp
// 这一题用到的是唯一分解式
#include <iostream>
#include <cmath>

using ll = long long;

// 算出n里面最大能除掉多少d，返回d的k次方
int DivedeAll(int &n, int d)
{
    int x = 1;
    while (n % d == 0)
    {
        n /= d;
        x *= d;
    }

    return x;
}

ll Solve(int n)
{
    if (n == 1) // 注意特判：1 == 1 * 1
    {
        return 2;
    }

    ll Ans = 0; // 最后的答案
    int pf = 0; // 质因子的个数
    int m = static_cast<int>(std::sqrt(n)); // 不要放在循环里，因为要修改n的值
    for (int i = 2; i <= m; ++i)
    {
        if (n % i == 0) // i是一个新的质因子
        {
            ++pf;
            Ans += DivedeAll(n, i);
        }
    }

    if (n > 1)  // 如果除到最后还有剩余的，那就把它也加上去
    {
        ++pf;
        Ans += n;
    }
    if (pf <= 1)
    {
        ++Ans;  // 如果n这个数是个质数，那还要加上1(n == 1 * n)
    }

    return Ans;
}

int main()
{
    int n, NO = 0;
    while (std::cin >> n && n)
    {
        std::cout << "Case " << ++NO << ": " << Solve(n) << std::endl;
    }

    return 0;
}
```

---

## 作者：endswitch (赞：0)

前置芝士：简单数论。

一个正整数可以分解成 ${p_1}^{c_1}\times{p_2}^{c_2}\times{p_3}^{c_3}\times......\times{p_n}^{c_n}$ 的形式。其中 $p$ 为素数，$c$ 为正整数。这里有一个定理：对于 $m,n>1$  且 $n\ne m$ 有 $m\times n>m+n$。所以对于我们分解出来的每一项之和便是我们的答案。

这里再给出上述定理的证明：

已知 $m,n>1$  且 $n\ne m$，求证：$m\times n>m+n$。

证明：

$$\because m,n>1,n\ne m$$

$$\therefore (n-1)\times (m-1)>1$$

将不等式变形，得：

$$m\times n>m+n$$

证毕。

题目让我们求答案的最小值，所以 $ans={p_1}^{c_1}+{p_2}^{c_2}+{p_3}^{c_3}+......+{p_n}^{c_n}$。

还有几个细节：当一个数在分解质因数后只由一项构成时答案要加一。分解后不满足题目条件“至少两个数”，需要配另一个因数 $1$ 来满足要求。

代码很简单，不放了。

---

## 作者：Light_Star_RPmax_AFO (赞：0)

### 前言


长沙市一中8机房0714模拟测1。

[传送门](https://www.luogu.com.cn/problem/UVA10791)

[blog](https://www.luogu.com.cn/blog/JJL0610666/solution-uva10791)


# 思路

本题思路，首先我们先看 $\operatorname{lcm}$，明显要使得这些数的 $\operatorname{lcm} = n$ 那么我们就需要所有的数的质因子必须包含 $n$ 的质因子。

若 $1 \le a,b$，则 $a\times b \ge a+b$，所以我们就有了策略。

将同一个质因子放在一个数中，这样就可以使得数最小。

```cpp
for(ll i = 2;i <= sqrt(b);++i){
	ll sum = 1;
	while(b % i == 0){
		sum *= i;
		b /= i;
	}
	if(sum != 1)ans += sum;
}
```

这样就保证了每个质因数在同一个数中。

## 坑点

1. $1$，两个正整数的值是 $1,1$ 所以我们需要输出 $2$。

2. 质数，值为 $1,n$ 我们应该输出 $1 + n$。

3. 质数的指数幂，值为 $n,1$，输出 $1 + n$。

4. 输出 $ans$。

# AC Code
```
#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll b;

int main(){
    int cnt = 0;
    while(1){
    	cnt++;
    	cin>>b;
    	if(b == 0)break;
	    if(b == 1){
		    cout<<"Case "<<cnt<<": "<<2<<endl;
		    continue;
	    }
	    ll ans = 0,can = 0;
	    for(ll i = 2;i <= sqrt(b);++i){
		    ll sum = 1;
		    while(b % i == 0){
			    sum *= i;
			    b /= i;
		    }
		    if(sum != 1)ans += sum,can++;
	    }
	    if(b > 1)ans += b,can++;
	    if(can < 2)cout<<"Case "<<cnt<<": "<<ans + 1;
	    else cout<<"Case "<<cnt<<": "<<ans;
	    cout<<endl;
    }
	return 0;
}

---

## 作者：Aiopr_2378 (赞：0)

## 题目大意

输入整数 $n(1\le n<2^{31})$，求至少两个正整数，是它们的最小公倍数为 $n$，且这些整数的和最小。输出最小的和。

## 解题思路

我们可以将 $n$ 分解质因数，根据唯一分解定理，我们将其分解为

$$n=p_1^{c_1}\times p_2^{c_2}\times p_3^{c_3}\times\cdots\times p_k^{c_k}$$

因为 $p_1,p_2,\cdots ,p_k$ 都是质数，我们可以得出：$\forall i,j\in[1,k]$ 且 $i\not=j$，有 

$$p_i^{c_i}\perp p_j^{c_j}$$

即 $p_i^{c_i}$ 两两互质，所以我们可以考虑构造 $p_1^{c_1},p_2^{c_2},\cdots,p_k^{c_k}$，这样他们的最小公倍数一定是 $n$。

接下来考虑 $p_i^{c_i}+p_j^{c_j}$ 和$p_i^{c_i}\times p_j^{c_j}$ 二者的大小关系，我们将选择较小的作为构造方法。我们令 $P=p_i^{c_i}$，$Q=p_j^{c_j}$，因为 $P$ 和 $Q$ 最小为 $2$，故有

$$\begin{aligned}
(P-1)(Q-1)&>1\\
PQ-P-Q+1&>1\\
PQ&>P+Q
\end{aligned}$$

所以我们选择构造

$$ans=\sum\limits_{i=1}^k p_i^{c_i}$$

我没只需要进行质因数分解即可，注意常数优化。

## 参考代码

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
typedef long long ll;
ll n,ans;
int main(){
    ll num=0;
    while(1){
        scanf("%lld",&n);
        if(n==0) return 0;
        ans=0;
        ll cnt=0;
        for(ll i=2;i*i<=n;i++){
            ll temp=n;
            while(n%i==0) n/=i;
            if(temp/n>1){
                ans+=temp/n;
                cnt++;
            }
        }
        if(n>1){
            ans+=n;
            cnt++;
        }
        if(cnt==1) ans++;
        if(cnt==0) ans+=2;
        printf("Case %lld: %lld\n",++num,ans);
    }
    return 0;
}
```


---

## 作者：Fire_flame (赞：0)

[[题目传送门](https://www.luogu.com.cn/problem/UVA10791)]

# 分析

假设 $n=P_1^{x_1}\times P_2^{x_2}\times \dots \times P_k^{x_k}$。

显然这几个数为 $P_1^{x_1},P_2^{x_2},\dots , P_k^{x_k}$ 时解最优。

### 答案正确性证明：

$1.$ 如果选了一个数 $P_1^{t}$，其中 $t<x_1$。因为所有数的最大公约数包含 $P_1^{x_1}$，所以一定有一个数整除 $P_1^{x_1}$。也就是说，$P_1^{t}$ 这个数不要反而更优。

$2.$ 如果一个数为 $P_i^{x_i}\times P_j^{x_j}(i\ne j)$，把 $a$ 设为 $P_i^{x_i}$，$b$ 设为 $P_j^{x_j}$，因为 $a\times b$ 明显大于 $a+b$。所以把这个数替换成 $P_i^{x_i}$ 和 $P_j^{x_j}$ 更优。

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll ans,n;
bool flag;
ll calc(ll a,ll b){
	ll num=1;
	for(int i=1;i<=b;i++)num*=a;
	return num;
}
int main(){
	for(int t=1;;t++){
		scanf("%lld",&n);
		if(!n)return 0;
		printf("Case %d:",t);
		for(int i=2;i*i<=n;i++){
			ll cnt=0;
			if(n%i)continue;
			while(n%i==0){
				cnt++;
				n/=i;
			}
			flag=1;
			ans+=calc(i,cnt);
		}
		if(n>1){
			ans+=n;
			n=1;
		}
		if(n==1&&!flag)ans++;
		printf("%lld\n",ans);
		ans=0;
		flag=0;
	}
	return 0;
}
```

${\color{red}{Ps:}}$一定要开`long long`！！！

---

## 作者：Arghariza (赞：0)

小学知识告诉我们所有正整数都是能质因数分解的（

即 $\forall n\in \mathbb{N^+},\exists m,p,k,\  n=\prod\limits_{i=1}^{m}p_i^{k_i}$

对于 $\forall x,y \in \{x\mid x \in \mathbb{R^+},x>1\},$

$\ (x-1)(y-1)=xy-x-y\ge 0,\ xy\ge x+y$ 

$\therefore \min\{xy,x+y\}=x+y$

$\therefore ans = \sum\limits_{i=1}^{m}p_i^{k_i}$

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace ntftxdy {
	#define int long long
	inline int read() {
	    int w = 1, q = 0;
	    char ch = ' ';
	    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
	    if (ch == '-') w = -1, ch = getchar();
	    while (ch >= '0' && ch <= '9') q = q * 10 + ch - '0', ch = getchar();
	    return w * q;
	}

	inline void write(int x) {
	    if (x < 0) {
	        x = ~(x - 1);
	        putchar('-');
	    }
	    if (x > 9) write(x / 10);
	    putchar(x % 10 + '0');
	}
}
using namespace ntftxdy;

int ans, num, n, rnd;

signed main() {
	n = read();
	while (n != 0) {
		printf("Case ");
		write(++rnd);
		printf(": ");
		for (int i = 2; i <= sqrt(n); i++) {
			//计算指数 
			int t = n;
			while (n % i == 0) n /= i;
			if (t / n >= 2) {
				ans += t / n;
				num++;
			}
		}
		if (n >= 2) ans += n, num++;
		//特判 
		if (num == 0) write(ans + 2);
		else if (num == 1) write(ans + 1);
		else write(ans);
		num = ans = 0;
		puts("");
		n = read();
	}
	return 0;
}

```

---

## 作者：逆流之时 (赞：0)

我来改善码风了  
这题我用了只筛6n+1与6n+5的筛法。  
```cpp
#include<cstdio>
#include<cmath>
using namespace std;
long long T,maxn,n,sum,ans;
void pri(long long x)//码风优化核心
{
	if(n%x==0)
	{
		int sum1=1;
		while(n%x==0)sum1*=x,n/=x;
		ans+=sum1,sum++;
	}
}
int main()
{
	while(scanf("%lld",&n)!=EOF&&n)
	{
		sum=ans=0;
		maxn=sqrt(n);
		if(n==1)ans=1;
		pri(2);
		pri(3);
		for(long long i=6;i<=maxn;i+=6)
		{
			pri(i-1);
			pri(i+1);
			if(n==1)break;
		}
		if(n>1)ans+=n,sum++;//n还有一个大于sqrt(n)的约数
		if(sum<=1)ans++;//n为素数
		printf("Case %lld: %lld\n",++T,ans);
	}
	return 0;
}
```


---

## 作者：rihothy (赞：0)

将n唯一分解为a1^p1 * a2^p2 * ... * an^pn。易得把每个ai^pi作为一个数时处理才能最优。因为如果用ai^k之外的数，最小公倍数一定不是n，此时该数不是n的因子；如果k<pi，那么最小公倍数一定小于n。所以必须用ai^pi。我们把所有ai^pi算出来存进一个数组里，然后排序之，最后用dfs进行组合，选取最小值即可。

由于n<2^31，所有要用到大约前50000个质数来进行对n的唯一分解。首先用欧拉线性筛得到前50000个质数备用。
```cpp
vector<unsigned long long> euler(size_t n)
{
	vector<bool> vis(n + 1, false);
	vector<unsigned long long> primes;

	for (size_t i = 2; i <= n; ++i)
	{
		if (not vis[i])
		{
			primes.push_back(i);
		}

		for (size_t j = 0; j < primes.size() && i * primes[j] <= n; ++j)
		{
			vis[i * primes[j]] = true;

			if (i % primes[j] == 0)
			{
				break;
			}
		}
	}

	return move(primes);
}
```

然后是唯一分解的代码，num为要分解的数，mp存放<ai, pi>字典（不含1）
```cpp
void unique_decomposition(int num, map<int, int>& mp)
{
	for (int i = 0; i < primes.size(); ++i)
	{
		if (num % primes[i] == 0)
		{
			++mp[primes[i]];
			num /= primes[i];
			--i;
		}

		if (num == 1)
		{
			return;
		}
	}

	if (num != 1)
	{
		++mp[num];
	}
}
```

还有求最小公倍数的代码
```cpp
ull gcd(const ull& a, const ull& b)
{
	return b ? gcd(b, a % b) : a;
}

ull lcm(const ull& a, const ull& b)
{
	return a / gcd(a, b) * b;
}
```

最后用得到的数组在dfs中寻找答案
```cpp
void dfs(vector<int>& arr, ull lcm_num, ull sum, int i)
{
	if (lcm_num == n)
	{
		ans = min(ans, sum);
	}
	else if (lcm_num < n && i < arr.size())
	{
		for (int j = i + 1; j < arr.size(); ++j)
		{
			dfs(arr, lcm(lcm_num, arr[j]), sum + arr[j], j);
		}
	}
};
```

所以这道题其实就是把一堆模板复制进去，然后写了个dfs就行了

---

