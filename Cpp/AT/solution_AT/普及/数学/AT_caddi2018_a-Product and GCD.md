# Product and GCD

## 题目描述

[problemUrl]: https://atcoder.jp/contests/caddi2018b/tasks/caddi2018_a

$ N $ 個の $ 1 $ 以上の整数 $ a_1,\ a_2,\ ...,\ a_N $ があります． $ a_1,\ a_2,\ ...,\ a_N $ の値はわかりませんが，$ a_1\ \times\ a_2\ \times\ ...\ \times\ a_N\ =\ P $ がわかっています．

$ a_1,\ a_2,\ ...,\ a_N $ の最大公約数として考えられるもののうち，最も大きいものを求めてください．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^{12} $
- $ 1\ \leq\ P\ \leq\ 10^{12} $

### Sample Explanation 1

例えば $ a_1=2,\ a_2=6,\ a_3=2 $ の場合，最大公約数は $ 2 $ となります．

### Sample Explanation 2

$ a_i $ は正の整数なので，$ a_1\ =\ a_2\ =\ a_3\ =\ a_4\ =\ a_5\ =\ 1 $ 以外にはありえません．

## 样例 #1

### 输入

```
3 24```

### 输出

```
2```

## 样例 #2

### 输入

```
5 1```

### 输出

```
1```

## 样例 #3

### 输入

```
1 111```

### 输出

```
111```

## 样例 #4

### 输入

```
4 972439611840```

### 输出

```
206```

# 题解

## 作者：kind_Ygg (赞：1)

~~来水一发。~~
## 简述题意
找到 $n$ 个数（可以相同），使得这 $n$ 个数的乘积为 $P$，同时使它们的最大公约数最大化。
## 思路
如果这 $n$ 个数为实数的话，那我们可以用二分和快速幂解决。就是求 $t$，使 $t^n=P$。但因为要求整数，我们可以将 $P$ 分解质因数，一旦出现 $kn$ 个相同的数（$k\ge1$），$ans=ans\times i$（$i$ 为他的因子）。这是因为我们要使每个数都要有一个 $i$，才能使 $ans$ 产生变化。
## 代码

```
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,p;
int cont;
int ans=1;
signed main()
{
	cin>>n>>p;
	for(int i=2;i*i<=p;i++)//时间优化，不然会T
	{
		cont=0;
		while(p%i==0)
		{
			p/=i;
			++cont;
			if(cont%n==0)
				ans*=i;//但凡出现n个i，ans*=i
		}
	}
	cout<<ans<<'\n';
	return 0;
}
```
如果你是这样写的话，那就一定会 WA，为什么呢？举一个反例，$n=120=2\times2\times2\times3\times5$，按程序运行到最后，$i=5$ 且 $P=5$，由于 $i^2>P$ 所以会直接跳出循环，$5$ 就不会记录了。在 $n>1$ 时是没有问题的，但当 $n=1$ 时，$ans$ 可能就会少记录最后一个单独数（也有可能没错，比如 $100$，两个 $10$ 是连一起的）。所以就要再加这样一串：

```
if(n==1)
{
	cout<<p<<'\n';
	return 0;
}
```
~~今天又水了一道黄。~~

---

## 作者：_yang_yi_bo_ (赞：0)

由于 $\prod\limits_{i=1}^{N}a_i=P$，我们可以考虑分解质因数，使用 `map` 存储每个质因数以及其出现次数。

比如说 $n=2,p=576$，$p$ 就 $=2^6 \times 3^2$，$a_1$ 与 $a_2$ 就可以都分到 $2^3 \times 3$，最大公因数就 $×24$，因为是平分，每个数的最大公因数会尽可能地大。

可以得出：若 $p=x_1^{a_1}\times x_2^{a_2}\times \dots x_m^{a_m}$，最大公因数就是 $x_1^{\lfloor \frac{a_1}{n} \rfloor}\times x_2^{\lfloor \frac{a_2}{n} \rfloor}\times \dots x_m^{\lfloor \frac{a_m}{n} \rfloor}$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
map<int,int> mp;
int n,p;
int ans=1;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>p;
	for(int i=2;i*i<=p;i++){
		while(p%i==0){
			mp[i]++;
			p/=i;
		}
	}if(p>1){
		mp[p]++;
	}for(auto i:mp){
		if(i.second>=n){
			for(int j=1;j<=(i.second/n);j++){
				ans*=i.first;
			}
			
		}
	}cout<<ans;
	return 0;
} 
```

---

## 作者：jinfanhao (赞：0)

题目大意：找到 $n$ 个数，要求这 $n$ 个数的乘积为 $m$，同时使 $n$ 个数的最大公约数最大。
那么就对他分解质因数，只要他的这个数含有这个因数超过 $n$ 个，便可以把这个质因数算进去。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,sum=1;
signed main(){
	scanf("%lld%lld",&n,&m);
	if(n==1){
		printf("%lld\n",m);
		return 0;
	}
	for(int i=2; i<=m/i; ++i){
		int cnt=0;
		while(!(m%i)){
			m/=i;
			++cnt;
			if(!(cnt%n))sum*=i;
		}
	}
	printf("%lld",sum);
	return 0;
}
```

---

## 作者：chengjindong (赞：0)

[题目](https://www.luogu.com.cn/problem/AT_caddi2018_a)

因为要求整数，所以我们可以将 $P$ 分解质因数，循环 $i$，判断 $i$ 是不是 $P$ 的因数，是的话除以 $i$，再次判断 $i$ 现在是不是 $P$ 的因数，如果 $i$ 的个数已经有 $n$ 个了，答案乘上 $i$，最后输出答案就行了。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int n,p;
	cin >>n>>p;
    if(n==1){//特判，这里要注意！！
        cout<<p<<endl;//输出，AT题要换行 
        return 0;
    }
	int ans=1;//答案，初始是一，要乘，不能是零  
	for(int i=2;i*i<=p;i++){//这里和筛质数一样，用i*i<=p，用i<=p会TLE 
		int s=0;//p因数i可以分解的个数
		while(p%i==0){//i是p的因数 
			p/=i;//除掉i，不除会死循环
			s++;//个数加一
			if(s%n==0){//出现了n个i，答案乘上i 
				ans*=i;//乘 
			}
		}
	}
	cout<<ans<<endl;//输出，AT题要换行 
	return 0;
}
```

---

## 作者：RioFutaba (赞：0)

# 解法
考虑将 $P$ 进行质因数分解。


设 $P= \prod c_i^{k_i} $。  
答案显然是 $\prod c_i^{\lfloor{\frac{k_i}{N}}\rfloor}$。

对于每一个 $k_i$，如果 $k_i \geq N$，那么 $\displaystyle c_i^{\lfloor{\frac{k_i}{N}}\rfloor}$ 就可以“分配”到 $a$ 数组的每一个值上，对答案产生贡献。

特别地，当 $N=1$ 时，因为只有一个数，所以答案为 $P$。

Code:

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll n,p;
ll ans=1;
int main(){
	cin >> n >> p;
	if(n==1){
		cout << p << endl;//如果只有一个数那么gcd一定是p
		return 0;
	}
	for(ll i=2;i*i<=p;i++){
		ll cnt=0;
		while(p%i==0){
			cnt++;
			p/=i;
		}
		for(int j=1;j<=cnt/n;j++) ans*=i;
	}
	cout << ans << endl;
	return 0;
}
```

极致压行：


```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long 
ll n,p;ll ans=1;int main(){cin >> n >> p;if(n==1){cout << p << endl;return 0;}for(ll i=2;i*i<=p;i++){ll cnt=0;while(p%i==0){cnt++;p/=i;}for(int j=1;j<=cnt/n;j++) ans*=i;}cout << ans << endl;return 0;}
```

---

## 作者：Lele_Programmer (赞：0)

# AT_caddi2018_a 题解

## 思路

可以将 $P$ 先进行质因数分解，为了使得序列 $a$ 的最大公因数更大，就需要将相同的质因数尽量多地分配到各个元素中。

比如，$N=5$，然后一个质因数出现了 $4$ 次，那么不能够做到每个元素都分配到一次，这个质因数对结果没有贡献。

再比如，$N=5$，然后一个质因数出现了 $14$ 次，那么可以将其均摊，五个元素均可以分配到两个这样的质因数，然而剩余的 $4$ 个质因数并不能再进行一轮分配了，所以对结果做出的贡献是 $prime^{\lfloor\frac{cnt}{n}\rfloor}$，对所有的质因数进行相同的操作即可。

## 代码

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

int n,p;
vector<int> ps;
vector<int> cnt;
int ans;

signed main() {
    scanf("%lld %lld",&n,&p);
    if (n==1) {
        printf("%lld\n",p);
        return 0;
    }
    for (int i=2;i*i<=p;++i) {
        if (p%i) continue;
        ps.push_back(i);
        cnt.push_back(0);
        while (p%i==0) {
            p/=i;
            cnt.back()++;
        }
    }
    if (p!=1) {
        ps.push_back(p);
        cnt.push_back(1);
    }
    ans=1;
    for (int i=0;i<cnt.size();++i) {
        while (cnt[i]>=n) {
            cnt[i]-=n;
            ans*=ps[i];
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：andyli (赞：0)

设答案为 $g$，则显然 $p$ 必须被 $g^n$ 整除。对 $p$ 分解质因数，$p=\prod{a_i}^{c_i}$，最大化 $g$ 则显然令 $g=\prod{a_i}^{\left\lfloor\frac{c_i}{n}\right\rfloor}$。

```python
from collections import *
from math import *
n, p = map(int, input().split())
c = Counter()
for i in range(2, int(p**0.5) + 1):
    while p % i == 0:
        p //= i
        c[i] += 1
if p > 1:
    c[p] += 1
print(prod(k**(v // n) for k, v in c.items()))
```

---

## 作者：RainFestival (赞：0)

有$n$个数字$a_1,a_2\cdots$

告诉你$\prod\limits_{1}^{n}a_i=P$

你可以随意指定$a_i,i\in[1,n]$的值

让你求$max\{\gcd\limits_{1}^{n}a_i\}$

当$n=1$时，答案显然是$P$

否则我们将$n$分解质因数

设$n=p_1^{a_1}\times p_2^{a_2}\cdots$

那么答案$=p_1^{\lfloor \frac{a_1}{n}\rfloor}\times p_2^{\lfloor \frac{a_2}{n}\rfloor}\cdots$

注意$long$ $long$,我$WA$了$4$次

代码：

```cpp
#include<cstdio>
long long p,ans=1,n;
int main()
{
	scanf("%lld%lld",&n,&p);
	if (n==1)
	{
		printf("%lld\n",p);
		return 0;
	}
	for (long long i=2;i*i<=p;i++)
	{
		long long cnt=0;
		while (p%i==0) ++cnt,p=p/i;
		for (long long j=1;j*n<=cnt;j++) ans=ans*i;
	}
        //如果p没有分解完，则它一定是一个质数,a=1,然而n=1的情况已经特殊判断过了
	printf("%lld\n",ans);
}
```

然后就$AC$了

$QAQ$


---

