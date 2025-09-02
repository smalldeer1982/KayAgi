# [ABC142D] Disjoint Set of Common Divisors

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc142/tasks/abc142_d

正整数 $ A,\ B $ が与えられます。

$ A $ と $ B $ の正の公約数の中からいくつかを選びます。

ただし、選んだ整数の中のどの異なる $ 2 $ つの整数についても互いに素でなければなりません。

最大でいくつ選べるでしょうか。

 公約数とは整数 $ d $ が整数 $ x $ と整数 $ y $ の公約数であるとは、$ d $ が $ x $ と $ y $ をともに割り切ることをいいます。

 

互いに素とは整数 $ x,\ y $ が互いに素であるとは、$ x,\ y $ の正の公約数が $ 1 $ のみであることをいいます。

 

割り切るとは整数 $ x $ が整数 $ y $ を割り切るとは、$ y\ =\ \alpha\ x $ なる整数 $ \alpha $ が存在することをいいます。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 1\ \leq\ A,\ B\ \leq\ 10^{12} $

### Sample Explanation 1

$ 12 $ と $ 18 $ の正の公約数は $ 1,\ 2,\ 3,\ 6 $ です。 $ 1 $ と $ 2 $、$ 2 $ と $ 3 $、$ 3 $ と $ 1 $ は互いに素なので、$ 1,\ 2,\ 3 $ を選ぶことができ、このときが最大です。

### Sample Explanation 3

$ 1 $ と $ 2019 $ の正の公約数は $ 1 $ しかありません。

## 样例 #1

### 输入

```
12 18```

### 输出

```
3```

## 样例 #2

### 输入

```
420 660```

### 输出

```
4```

## 样例 #3

### 输入

```
1 2019```

### 输出

```
1```

# 题解

## 作者：_xbn (赞：4)

### 题目大意：

给定正整数 $A$ 和 $B$。

让我们选择 $A$ 和 $B$ 的一些正公约数。任何两个选定的除数必须是互质的。

最多可以选择多少个除数？

### solution

首先大家小学时应该学过这么个定理：

如果一个数 $x$ 为 $A$ 和 $B$ 的公约数，那他一定整除 $\gcd(A, B)$。

了解这个后，我们就能解题了。

要找到 $A$ 和 $B$ 的公约数，我们可以对 $\gcd(A, B)$ 分解质因数，同时统计质因子的个数，作为最终的答案。因为是质因子，所以他们一定两两互质。由于我们把互质的数全都取出，所以最大值就是他们的个数。

下面给出证明：

设 $x$ 和 $y$ 为 $A$ 和 $B$ 的公因数。

则 $\gcd(a, x) \leq \gcd(ab, x)$，因此，比起选择整数 $ab$，选择 $a$ 更好(注意:如果 $ab$ 是公约数，那么 $a$ 也是公约数)。也就是说，如果 $P$ 是最优解，那么 $P$ 选择的公约数中存在表示为 $ab$ 的整数，那么就可以选择 $a$。

因此，存在只选择 $1$ 或素数的最优解。

证毕。


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 100002;
int n, m, l, r, p, t, k, ans, sum, tot, cnt, a[N], b[N], c[N];
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
	{
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while('0' <= ch && ch <= '9')
	{
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
int gcd(int x, int y)
{
	return y ? gcd(y, x % y) : x;
}
signed main()
{
	int A = read(), B = read();
	n = gcd(A, B); m = n;
	ans = 1;
	for (int i = 2; i <= sqrt(m); i++)
	{
		if(n % i != 0) continue;
		while (n % i == 0) n = n / i;
		ans++;
	}
	if(n != 1) ans++;
	cout << ans << endl; 
    return 0;
}
```


---

## 作者：CQ_Bab (赞：1)

# 思路
这道题好像暴力可以过，于是我果断去暴力。题目中说了既然要是 $A$ 和 $B$ 的倍数，那么 $A$ 和 $B$ 的最大公因数这样既能保证个数最多又能让它们互质，这样只需要将每一个质因数都分解干净，但是还需要注意一点那就是 $1$ 一定是两个数的公因数所以 $ans$ 从 $1$ 开始。最后一定要判断一下分解干净了没有，若没有那就答案加一。

# AC代码
```cpp
#include<bits/stdc++.h>
#define int long long // 一定要开 long long 
using namespace std;
int a,b,g;
signed main() {
	cin>>a>>b;
	g=__gcd(a,b); // C++自带函数 
	int n=g,res=1;// 从一开始 
	for(int i=2; i<=sqrt(n); i++) { // 分解质因数 
		if(g%i==0) {
			res++;
			while(g%i==0) g/=i;
		}
	}
	if(g!=1) res++; // 特判 
	cout<<res<<endl;
	return false;
}
```


---

## 作者：shaozhehan (赞：0)

[原题链接](https://www.luogu.com.cn/problem/AT_abc142_d)

[AtCoder 链接](https://atcoder.jp/contests/abc142/tasks/abc142_d)

题目大意：

给定两个数 $a$ 和 $b$，问你可以选出多少个数使得每一个数都能整除 $a$ 和 $b$，且数两两互质。

思路：

我们可以先算出 $\gcd(a,b)$，每一个满足要求的数都必然整除 $\gcd(a,b)$。显然，我们可以把 $\gcd(a,b)$ 分解质因数，再把质因数个数加上 $1$，也就是选 $1$，最终输出。

下证这种情况是最优解：

假设有两个数 $x$ 和 $y$，均能整除 $\gcd(a,b)$。如果现在有两个数 $m$ 和 $mn$ 可以选择，显然 $\gcd(m,x)$ 整除 $\gcd(mn,x)$，所以选择 $m$ 比选择 $mn$ 好。

坑点：

1. ```gcd``` 函数需要开 ```long long```！
1. 枚举质因数的时候循环变量要用 ```long long``` 或强制转换成 ```long long``` 类型，否则会炸精度！
1. 不要忘记 $1$ 也要选上！

上代码：
```cpp
#include <iostream>
using namespace std;

long long gcd(const long long &x, const long long &y){// gcd 函数模板(坑点1：long long 类型）
    return (x % y == 0 ? y : gcd(y, x % y));
}

int main(){
    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);// cin、cout 加速
    long long a, b;
    cin >> a >> b;
    long long temp = gcd(a, b);
    int cnt = 0;
    // 分解质因数，统计质因数个数
    for (int i = 2; 1ll * i * i <= temp; i++){// 坑点 2：循环变量
        if (temp % i == 0){
            cnt++;
            while (temp % i == 0){
                temp /= i;
            }
        }
    }
    if (temp != 1){// 如果还有剩余的质因数，那么 cnt 再加上 1
        cnt++;
    }
    cout << cnt + 1 << "\n";// 坑点 3：1 也要算上
    return 0;
}
```

---

## 作者：OIerBoy (赞：0)

## [题目传送门](https://atcoder.jp/contests/abc142/tasks/abc142_d)
## 翻译
给你两个数 $A$ 和 $B$，寻找能同时整除两个数，且两两互质的数的个数。
## 分析
这道题我们可以直接暴力解决的。

首先，我们知道如果一个数 $i$ 是 $A$ 和 $B$ 的公因数，那么 $i$ 一定是 $\gcd(A,B)$ 的因数。我们又知道任意两个质数都是互质的。所以我们只需要先求出 $\gcd(A,B)$，然后在枚举出它有多少个质因数。最后由于 $1$ 不是质数，所以这里的 $i\ne1$，但 $1$ 又是与其他数互质的，所以最后的答案需要加一。

分析一下可以发现时间复杂度是 $O(\log n)$。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
long long a,b,gc,ans=1;
int main(){
	cin>>a>>b;gc=__gcd(a,b);
	for(int i=2;i<=sqrt(gc);i++)
		if(gc%i==0){
			while(gc%i==0)gc/=i;
			ans++;
		}
	if(gc!=1)ans++;
	cout<<ans;
	return 0;
}
```

---

## 作者：Leaves_xw (赞：0)

**题意：**

给你两个数 $A$ 和 $B$，寻找能同时整除两个数，且两两互质的数的个数。

**思路：**

先定义一个为 $A,B$ 的最大公因数的变量 $x$，之后暴力枚举，如果 $x$ 模 $i$ 等于 $0$，则将计数器累加，之后进行`while`循环，将 $x$ 重复除以 $i$，防止重复，最后输出计数器即可。

注意：数 $A,B$ 过大，需要开`long long`。

**代码：**

```
#include<bits/stdc++.h>//万能头文件
using namespace std;
long long a,b;//全局变量，一定要开long long！
int main()//主函数
{
    cin>>a>>b;//输入a，b
    long long x=__gcd(a,b),ans=1;//__gcd表示求出a和b的最大公因数
    for(long long i=2;i<=sqrt(x);i++)//给x开根号
    {
        if(x%i==0)//如果除的开
        {
            ans+=1;//计数器累加
            while(x%i==0)//如果x%i=0，则循环，否则跳过循环
            {
            	x/=i;//防止重复，将x一直除以i
            }
        }
    }
    if(x!=1)ans++;//如果x不是1，则还有一个需要累加进计数器
    cout<<ans<<endl;//输出计数器，别忘了换行
    return 0;
}//完结
```

管理员求过！

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc142_d)

## 思路

这题暴力就可以过

首先定义一个变量 $tmp$ 用来存 $\gcd (a,b)$，即最大的能整除 $a$ 和 $b$ 的数。然后循环枚举从 $2$ 到 $\sqrt{tmp}$ 中能整除 $tmp$ 的数 $i$。如果找到了答案就 $+1$。之后只要 $i$ 能整除 $tmp$，$tmp$ 就除以 $i$，直到不能除了为止，$i$ 与 $tmp$ 就互为质数。循环到最后，如果 $tmp$ 这时不为 $1$，说明这时也是另一种情况，答案 $+1$，输出。

由于这题数据范围是 $1\leq A,B\leq 10^{12}$，所以我们要开 long long 存储。

- 最后别忘换行

## 代码

~~~cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a,b,ans=1;
int main(){
    cin>>a>>b;
    ll tmp=__gcd(a,b);
    for(ll i=2;i*i<=tmp;++i){
        if(tmp%i==0){
            ++ans;
            while(tmp%i==0)tmp/=i;
        }
    }
    if(tmp!=1)++ans;
    cout<<ans<<endl;
    return 0;
}

~~~

[已 AC](https://www.luogu.com.cn/record/96101434)

---

## 作者：tZEROちゃん (赞：0)

vp 用时 $2:25$。

显然 $\gcd(a,b)$ 的所有因数都是 $a$ 和 $b$ 的公因数，又因为题目说要互质，所以直接对 $\gcd(a,b)$ 进行质因数分解就可以了。

具体来说，我们设 $G = \gcd(a,b)$，那么我们从 $2$ 遍历到 $\sqrt G$，当 $i$ 是 $G$ 的因数时，我们就将 $G$ 一直除以 $i$，直到 $G$ 不是 $i$ 的倍数，最后记录因数数目即可。

需要注意的是，如果最后 $G \not = 1$，答案显然要加上 $1$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i, l, r) for(auto i = (l); i <= (r); i ++)
#define per(i, r, l) for(auto i = (r); i >= (l); i --)

typedef long long LL;

void solve() {
  LL N, M;
  cin >> N >> M;
  LL G = __gcd(N, M);
  int cnt = 1;
  for (LL i = 2; i <= sqrt(G); ++i) {
    if (!(G % i)) {
      ++cnt;
      while (!(G % i)) G /= i;
    }
  }
  if (G != 1) ++cnt;
  cout << cnt << endl;
}
 
int main(){
  // multiCase() 
  solve();
  return 0;
}
```

---

## 作者：SnowTrace (赞：0)

先求出两数的最大公因数，随后算出最大公因数的所有因数即可。

非常显然，只有取最大公因数中的所有质因数，才能是答案最大，所以该最大公因数中的质数因数的个数加上一便是要求的值。

这边采用一种质数筛法，可以自行理解。

基本上是枚举，遇到一次整除就把这个数除干净（即原数不再被这个数整除）。

代码如下。

用时不到二十毫秒。

~~（暴力算似乎可以过（？））~~

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long a,b,cnt = 1;
  //cnt为答案
	cin >>a >>b;
	long long g = __gcd(a,b);//c++自带函数 最小公因数
	for(long long i =2;i*i<=g;i++){
		if(g%i == 0){
			cnt++;
			while(g%i == 0){
				g/=i;
              //如果遇到整除的情况，就把答案加上一，并把数除干净
			}
		}
	}if(g!=1)cnt++;
	cout<<cnt << endl;
  return 0;
}
```



---

## 作者：沉石鱼惊旋 (赞：0)

### 题目翻译

给定两个数 $a$ 和 $b$，求能同时整除 $a$ 和 $b$ 的数的个数，且这些数需要两两互质。

### 题目分析

两两互质，也就说明有以下几种情况：

1：均为不同的质数。

2：相邻 。

3：一个是质数，另一个不是他的倍数。

4：所有数和 $1$。

5：相邻奇数。

6：较大数是质数。

……

这是常见的情况，其实还有很多。那么我们肯定不能全写到程序里。我们只选择第 $1$ 个性质：均为不同的质数。

确保了找的答案是质数，然后确保它是这两个数的因数（因为能整除），那么我们只要找到两个数**共同的质因数**。

共同的质因数，一定是两个数最大公因数的质因数。

所以找出最大公因数，再找出所有最大公因数的质因数（还要算上特殊的 "1"），即为答案。

### 题目代码

```cpp
#include<bits/stdc++.h>
#define ll long long//数据很大，要long long
using namespace std;
ll a,b,s=1;//1一定是两个数的公因数
ll gcd(ll x,ll y)
{
	return y?gcd(y,x%y):x;//辗转相除法求最大公因数
}
int main()
{
	cin>>a>>b;
	ll g=gcd(a,b);
	for(ll i=2;i<=sqrt(g);i++)//枚举最大公因数的质因数
	{
		if(g%i==0)//如果是的（后续补充说明）
		{
			s++;//找到了一个
			while(g%i==0)g/=i;//把这个质因数除完
		}
	}
	cout<<(g!=1?++s:s);//如果有剩余的质因数，再加上1
}
```

### 补充说明

第 $15$ 行 `if(g%i==0)` 解释
	
找到了 $g$ 最小能整除的数 $i$，那么 $i$ **肯定是个质数**，不用加以判断。

举个不成功的反例验证一下结论。

如果 $i$ 不是质数，说明 $i$ 还有其他因数，那么 $i$ 的因数也就是 $g$ 的因数了，$i$ 肯定不是最小能被整除的数了。

所以得出结论，$i$ 肯定是个质数，不用加上质数判断。

---

## 作者：μηδσ (赞：0)

## Description

给你两个数A和B，寻找能同时整除两个数，且两两互质的数的个数。

## Solution

思路比较简单，就是寻求两个数的最大公因数的所有质因子（注意这道题是可以包括1的，所以在最后的时候不要忘掉+1

### Step 1：最大公因数

众所周知，最大公因数就是最大的能整出两个数的整数（~~这不是废话吗~~

于是，我们只要枚举，即不超过a，也不超过b的最大的满足要求的数，所以就有了以下这个代码。

~~~cpp
int gcd(int a, int b){
	int tmp = min(a, b), ans = -1;
	if(tmp == 0)
		return -1;
	for(int i = tmp;i >= 1;i--)
		if(a % i == 0 && b % i == 0){
			ans = i;
			return ans;
		}
}
~~~

但是这样并不是很快，于是就有了这种方法——辗转相减

（以下思路纯属个人理解）

如果两个数a，b($a\geq b$)，有公因数k那么存在$a\equiv b\equiv a-b(mod\ k)$

重复以上步骤，知道一个数减到0，那么另外一个数就是这两个数的最大公因数

~~~cpp
int gcd(int a, int b){
	return b == 0 ? a : gcd(b, a % b);
}
~~~

### step 2:寻找一个数的所有质因子

众所周知(~~我又来了~~)，一个大于一的整数一定可以唯一的写成若干质数的幂的乘积。

$n={p_1}^{w_1}\times{p_2}^{w_2}\times{p_3}^{w_3}\times...\times{p_m}^{w_m}$

其中$p_1,p_2,p_3,...p_m$均为质数

$w_1,w_2,w_3,...,w_m$均为正整数

一般的情况，我们要把一个数分解成以上的样子，我们可以这样写

~~~cpp
void factorize(int x){
	for(int i = 2;i <= x;i++)
    	if(x % i == 0){
        p[++k] = i;
        while(x % i == 0){
        	x /= i;
          w[k]++;
        }
    }
} 
~~~

但是这样的时间复杂度较高，于是，我边便有以下的思路：

对于一个大于等于5的数，至多存在一个比他的算术平方根的大的质因子。

于是我们就可以枚举不超过$\sqrt{n}$的所有数字，看看是不是他的质因数，因为是从小到大枚举的，每次都把他的除到不能整除的时候，所以不会存在查到一个不是质数的因数。

~~~cpp
void factorize(int x){
	for(int i = 2;i * i <= x;i++)
    	if(x % i == 0){
        p[++k] = i;
        while(x % i == 0){
        	x /= i;
        	w[k]++;
        }
    }
    if(x >= 1){
    	p[++k] = x;
    	w[k] = 1;
	}
} 
~~~

其实如果是寻找多组数据的公因数的话，其实还有一个不错的优化。

首先预处理一遍所有质数（比如说质数筛法），然后用while(prime[cnt++] < x)

但是这道题只有一组数据，所以没有比作做一次预处理。

思路已经很清楚了，直接看代码吧

## Code

~~~cpp#include<cstdio>
#include<algorithm>
#include<map>
using namespace std;
#define ll long long

ll x, y;

ll gcd(ll a, ll b){				//寻找gcd函数,上面已经详细说过做法了
	return b == 0 ? a : gcd(b, a % b);
}

int main(){
	scanf("%lld %lld", &x, &y);	//输入两个数
	ll d = gcd(x, y);			//将gcd存在一个数中
	int ans = 1;
								//这里并没有专门放在一个函数中，因为这道题仅要求我们求质因子个数 
	if(d % 2 == 0) 				//判断他是不是2的倍数,因为2是惟一的一个偶数质数
		ans++;
	while(d % 2 == 0)
		d /= 2;
	for(ll i = 3;i * i <= d;i += 2)	//一个小优化,因为除了2意外,并没有其他的偶数质数了,所以可以每次都加2 
		if(d % i == 0){
			ans++;
			while(d % i == 0)
				d /= i;
		}
	if(d != 1) 					//判断有没有大于sqrt(n)的 
		ans++;
	printf("%d\n",ans);
	return 0;
}
~~~

---

