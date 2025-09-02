# [ABC112D] Partition

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc112/tasks/abc112_d

整数 $ N,\ M $ が与えられます。

$ a_1\ +\ a_2\ +\ ...\ +\ a_N $ = $ M $ となる正整数からなる長さ $ N $ の数列 $ a $ において、$ a_1,\ a_2,\ ...,\ a_N $ の最大公約数のとり得る最大値を求めてください。

## 说明/提示

### 制約

- 入力はすべて整数である
- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ N\ \leq\ M\ \leq\ 10^9 $

### Sample Explanation 1

$ (a_1,\ a_2,\ a_3)\ =\ (2,\ 4,\ 8) $ としたときこれらの最大公約数が $ 2 $ となり最大です。

## 样例 #1

### 输入

```
3 14```

### 输出

```
2```

## 样例 #2

### 输入

```
10 123```

### 输出

```
3```

## 样例 #3

### 输入

```
100000 1000000000```

### 输出

```
10000```

# 题解

## 作者：RainFestival (赞：2)

设最终答案为 $k$

则 $k=\gcd(a_1,\cdots,a_n)$

因为 $\sum\limits_{i=1}^{n}a_i=m$

所以 $k|m$

我们枚举 $m$ 的每一个约数 $d$

判断 $d\times n$ 是否 $\le m$

在满足条件的所有 $d$ 中选一个作为 $k$

时间复杂度 $O(\sqrt m)$

代码：

```cpp
#include<cstdio>
#include<vector>
std::vector<int> p;
int n,m,ans;
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i*i<=m;i++)
	    if (m%i==0)
	    {
		    p.push_back(i);
		    if (i*i!=m) p.push_back(m/i); 
	    }
	for (int i=0;i<p.size();i++) if (p[i]>ans&&1ll*p[i]*n<=m) ans=p[i];
	printf("%d\n",ans);
	return 0;
}
```

然后就 AC 了

QAQ

---

## 作者：ccg12345 (赞：1)

### 思路
设最终结果为 $k$，因为 $k = \gcd(a_1,a_2,\cdots,a_n)$，所以 $k$ 必然小于等于其中最小的一个数，又最小的一个数小于等于 $\frac{m}{n}$，所以 $k$ 的取值就固定了，再倒序枚举即可。
### 附代码
```
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int m, n;	
	cin >> m >> n;
	for(int i = n / m; i >= 1; i--)
	{
		if(n % i == 0)
		{
			cout << i << endl;
			return 0;
		}
	}
}
```



---

## 作者：VitrelosTia (赞：0)

思路很直接，就是枚举这个最大公约数。容易想到这个最大公约数必然小于等于 $\dfrac{m}{n}$，所以要从这里枚举到 $1$，枚举的时候假如能整除 $m$ 就代表一定能分好，于是满足整除时直接输出当前的数然后结束程序就做完了。

---

## 作者：TLEWA (赞：0)

我们将最终的答案设为 $k$

$k$ 的值为 $\gcd(a_1,a_2,\dots,a_{n-1},a_n)$。

而 $\sum_{i=1}^na_i = m$

所以 $k∣m$，且 $kn \le m$。

可以枚举 $m$ 的所有因子，逐个判断取最大，时间复杂度 $O(\sqrt{m})$。

代码：
```cpp
#include<iostream>
using namespace std;

long long n,m,maxn;

int main() {
	cin >> n >> m;
	for(long long i=1;i*i<=m;++i) {
		if(m%i==0&&i*n<=m) {
			maxn=max(maxn,i);
			if((m/i)*n<=m) maxn=max(maxn,(m/i));
		}
	}
	cout << maxn;
	return 0;
}
```


---

## 作者：_Kagamine_Rin_ (赞：0)

### 题目大意

已知 $n,m$ ，有一组数 $a_1,a_2…a_n$ 使 $a_1+a_2+…+a_n=m$ 。输出 $a_1,a_2…a_n$ 最大可能的最大公约数。

### 解题思路

可以确定，答案在 $1$ 到 $\frac{M}{N}$ 之间。

我们可以从大到小枚举答案，若这个答案可以被 $n$ 除尽，就输出这个答案，结束程序。

因为是从大到小枚举，所以第一个答案一定是最大的。

```cpp
#include<stdio.h>
main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=m/n;i>0;--i)
		if(m%i==0){
			printf("%d\n",i);
			return 0;
		}
}
```

---

## 作者：Fr0sTy (赞：0)

### 题意简述
------------

给定两个整数 $n$，$m$。试构造一个正整数序列 $a$，使 $\sum\limits_{i=1}^{N} = M$ 。

求 $\gcd(a_1,a_2,...,a_N)$ 的最大值。

### 解题思路
------------

有点难想到的**结论题**。

推理 ~~观察样例~~ 可得，所有答案 $ans$ 都满足 $1 \leqslant ans \leqslant  \dfrac{m}{n} $。

又因为答案最小为 $1$，不会存在不输出的情况。

这样，我们从大到小枚举 $\dfrac{m}{n}$ 到 $1$ 即可。

如果此时 $M$ 能被 $i$ 整除，说明找到了答案，然后输出。

### 代码实现
------------

``` cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
void doit(int i) {
	printf("%d",i);
	exit(0);
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=m/n;i>=1;i--) 
		if(!(m%i)) doit(i);
	return 0;
}
//code by TheCedar
```

---

## 作者：Nightingale_OI (赞：0)

### 大意

长度为 $ n $ 的数组 $ a $ 满足：

$$ \sum_{i=1}^{n} a_i = m $$

求所有满足条件的 $ a $ 数组中最大公因数最大的值。

### 思路

当最大公因数为 $ x $ （ $ x | m $ ）时，如果 $ m / x \geq n $ ，就必定可以将其分成若干个正整数，枚举 $ m $ 的因数即可。

时间复杂度 $ O(\sqrt{m}) $ 。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,l;
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
int main(){
    cin>>n>>m;
    s=(int)sqrt(m);
    f(i,1,s){
        if(m%i)continue;
        if(m/i>=n)l=max(l,i);
        if(i>=n)l=max(l,m/i);
    }
    printf("%d\n",l);
    return 0;
}
```

---

## 作者：HYdroKomide (赞：0)

~~又是一道看上去很难但实际上很简单的氵题~~
# **正文：**
## 题意：
本题只要明白了思路代码非常简单，只需要一个循环即可搞定。首先，这个序列的最大公约数一定 $≤m \div n$ ，也就是这个序列的平均数，所以我们就可以从这里开始循环，一直循环到 $1$ 如果发现一个可以被 $m$ 整除的数，就代表可以将 $m$ 分成 $n$ 份，每份都可以整除这个数。本题答案最小为 $1$ ，不可能有不输出的情况。
## 简单代码：
```cpp
#include<iostream>
using namespace std;
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=m/n;i>=1;i--){
    	if(m%i==0){
    		cout<<i;
    		return 0;
		}
	}
}
```
# **THE END**

---

