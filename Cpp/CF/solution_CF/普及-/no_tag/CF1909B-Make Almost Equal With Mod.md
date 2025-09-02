# Make Almost Equal With Mod

## 题目描述

[xi - Solar Storm](https://soundcloud.com/yugenero/xi-solar-storm)

⠀



You are given an array $ a_1, a_2, \dots, a_n $ of distinct positive integers. You have to do the following operation exactly once:

- choose a positive integer $ k $ ;
- for each $ i $ from $ 1 $ to $ n $ , replace $ a_i $ with $ a_i \text{ mod } k^\dagger $ .

Find a value of $ k $ such that $ 1 \leq k \leq 10^{18} $ and the array $ a_1, a_2, \dots, a_n $ contains exactly $ 2 $ distinct values at the end of the operation. It can be shown that, under the constraints of the problem, at least one such $ k $ always exists. If there are multiple solutions, you can print any of them.

 $ ^\dagger $ $ a \text{ mod } b $ denotes the remainder after dividing $ a $ by $ b $ . For example:

- $ 7 \text{ mod } 3=1 $ since $ 7 = 3 \cdot 2 + 1 $
- $ 15 \text{ mod } 4=3 $ since $ 15 = 4 \cdot 3 + 3 $
- $ 21 \text{ mod } 1=0 $ since $ 21 = 21 \cdot 1 + 0 $

## 说明/提示

In the first test case, you can choose $ k = 7 $ . The array becomes $ [8 \text{ mod } 7, 15 \text{ mod } 7, 22 \text{ mod } 7, 30 \text{ mod } 7] = [1, 1, 1, 2] $ , which contains exactly $ 2 $ distinct values ( $ \{1, 2\} $ ).

In the second test case, you can choose $ k = 30 $ . The array becomes $ [0, 0, 8, 0, 8] $ , which contains exactly $ 2 $ distinct values ( $ \{0, 8\} $ ). Note that choosing $ k = 10 $ would also be a valid solution.

In the last test case, you can choose $ k = 10^{18} $ . The array becomes $ [2, 1] $ , which contains exactly $ 2 $ distinct values ( $ \{1, 2\} $ ). Note that choosing $ k = 10^{18} + 1 $ would not be valid, because $ 1 \leq k \leq 10^{18} $ must be true.

## 样例 #1

### 输入

```
5
4
8 15 22 30
5
60 90 98 120 308
6
328 769 541 986 215 734
5
1000 2000 7000 11000 16000
2
2 1```

### 输出

```
7
30
3
5000
1000000000000000000```

# 题解

## 作者：Stars_visitor_tyw (赞：6)

## CF1909B Make Almost Equal With Mod 题解
### 分析
暴力枚举 $k$ 即可。

枚举 $k$ 从 $2$ 开始，此时 $a$ 数组模 $2$ 的结果有两种情况：

1. 有 $1$ 有 $0$：满足题意，输出 $2$ 。

2. 全为 $1$ 或全为 $0$：则将 $k \times 2$，变为 $4$ 后又可以分为两种情况。

综上所述，以此类推，则 $k$ 不停 $\times 2$ 一定能得到答案，因为原英文题面中说到：“You are given an array $ a_1, a_2, \dots, a_n $ **of distinct positive integers.** ”，就是说 $a$ 数组所有整数 **均不相同**，而不相同的两个数总会有 $1$ 个模数使得它们模那个模数得到的结果不同。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=105;
int n,a[N];
bool check(int k, int tmp)
{
	for(int i=2;i<=n;i++)
	{
		if(a[i]%k!=tmp)
		{
			return 1;
		}
	}
	return 0;
}
void work()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=2;;i*=2)
	{
	    if(check(i,a[1]%i))
	    {
	        cout<<i<<"\n";
	        return ;
	    }
	}
}
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		work();
	}
	return 0; 
}
```

---

## 作者：UncleSam_Died (赞：6)

### 解题思路
一个很显然的结论：
- 对于所有的 $a_i$，一定存在一个数 $2^b,b\in \mathbb Z$，使得 $a_i\bmod 2^b$ 有且仅有两个不同的值。

证明如下：
- 考虑将每个 $a_i$ 转化为二进制值，那么对于 $2^b$ 取模相当于保留后 $b$ 位；
- 设第 $i$ 个数第一次出现 $1$ 的位置在 $p_i$，那么对于这个数，$[1,\dots,p_i]$ 位均为 $0$；
- 设 $mp=\min \lbrace p_1,\dots,p_n\rbrace$，那么有当 $b=mp$ 时，若干个数取模后为 $2^{b-1}$，剩余的数为 $0$。

观察 $n$ 的范围发现 $n\le 10^{18}$，因此 $mp\le63$，所以我们直接枚举就可以了。

### AC 代码
```cpp
#include<math.h>
#include<time.h>
#include<stdio.h>
#include<algorithm>
#define ll long long
#define N 105
#include<set>
int n,m;ll a[N],b[N],delta[N];
std::set<ll> s;
inline void work(){
	scanf("%d",&n);
	for(register int i=1;i<=n;++i)
		scanf("%lld",&a[i]);
	ll Mode=2;
	while(true){s.clear();
		for(register int i=1;i<=n;++i){
			s.insert(a[i]%Mode);
		}if(s.size()==2){
			printf("%lld\n",Mode);
			return;
		}Mode=Mode*2;
	}
}signed main(){
	int T;scanf("%d",&T);
	while(T--) work();
}



```

---

## 作者：panxz2009 (赞：3)

## 题意简述
- 给定一个数列 $a$，求一个正整数 $k$，使得所有 $a_i \bmod k$ 恰好含有两个不同的值。 

## 解题思路

首先，很容易想到，一个可能的 $k$ 值为 $2$。如果数列 $a$ 中的所有数不全为奇数或全为偶数，则输出 $2$ 即可。

但是，如果 $a$ 中的所有数全为奇数或全为偶数，该怎么办呢？

若直接从 $2$ 开始枚举 $k$，必然会超时。可以考虑加大枚举跨度，这里使用一种个人认为类似倍增的思想，成倍增加地枚举 $k$。

事实上，根据同余的一些基本性质就能得知，假设 $a \bmod b=c$，则 $a \bmod 2b$ 一定等于 $c$ 或 $b+c$，那么因为考虑从 $2$ 开始，成倍枚举 $k$，最终一定能找到一个符合题意的 $k$ 值。
## 代码实现
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e2+10;
int a[N];
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		int k=2;
		while(1)
		{
			unordered_map<int,bool>mp;//用unordered_map（常数比map小）记录出现过几个模数 
			for(int i=1;i<=n;i++) mp[a[i]%k]=1;
			if(mp.size()==2) 
			{
				cout<<k<<"\n";//若符合要求，则直接结束 
				break;
			}
			k*=2;//成倍增长，考虑下一个 
		}
	}
	return 0;
}
```


---

## 作者：No_Rest (赞：2)

# 思路

可以证明，如果数列中所有数模 $n$ 只有一种结果 $a$，那么模 $2n$ 必然只能为 $a$ 或 $a + n$，也就是说只要之前模 $n$ 只有一种余数，那么模 $2n$ 不是一种就是两种余数。因为数列中的数两两不同，所以必定存在一个模数，使得数列中所有数模它所得余数有两种。

因为 $a_i \le 10^{17}$，所以我们可以直接枚举模数。

# 代码

```cpp
#include<bits/stdc++.h>
#define in inline
#define ll long long
using namespace std;
const ll maxn = 1e2 + 5;
const ll mod = 1e9 + 7;
in ll read(){
	char ch;
	ll f = 1, r = 0;
	ch = getchar();
	while(ch > '9' || ch < '0'){ if(ch == '-') f = -1; ch = getchar();}
	while(ch <= '9' && ch >= '0') r = (r << 3) + (r << 1) + (ch ^ 48), ch = getchar();
	return r * f;
}
in void write(ll f){
	if(f < 0) f = -f, putchar('-');
	if(f > 9) write(f / 10);
	putchar(f % 10 + '0');
	return;
}
ll t, n, a[maxn];
set <ll> s;
void solve(){
	n = read();
	for(ll i = 1; i <= n; ++i) a[i] = read();
	for(ll i = 2; ; i *= 2){//枚举模数
		s.clear();
		for(ll j = 1; j <= n; ++j) s.insert(a[j] % i);//用 set 记录余数
		if(s.size() == 2){//一共两种余数
			write(i), putchar('\n');
			return;
		}
	}
}
int main(){
	t = read();
	while(t--) solve();
    return 0;
}
```

---

## 作者：sdyzpf (赞：2)

## 思路

首先，对所有数进行排序。考虑到，令 $a_i=a_1+x \times k_i,x \in N,k_i \in N $。显然，$x$ 的最大值为 $\begin{matrix} \gcd_{i=2}^n {a_i-a_1} \end{matrix}$，并且，此时所有数 $\bmod x$ 的值相同。

进而，我们发现，此时，$k_i$ 的值必有奇有偶。 

### 证明如下： 
+ $k_1=0$，所以全为奇数不成立。
+ 若 $k$ 全为偶数，与 $x=\begin{matrix} \gcd_{i=2}^n {a_i-a_1} \end{matrix}$ 矛盾。
+ 证毕。

因此，$2x$ 即为答案。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,a[105],ans;
int main(){
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        sort(a+1,a+n+1);
        ans=a[2]-a[1];
        for(int i=3;i<=n;i++) ans=__gcd(ans,a[i]-a[1]);
        cout<<ans*2<<'\n';
    }
    return 0;
}
```
## 优化
+ 事实上，排序是没必要的，我们可以遍历一次找到最小值。
+ 事实上，找最小值也是没必要的，我们可以直接计算其他项与首项之差的绝对值的最小公倍数。[想不通可以点这里。](https://oi-wiki.org/math/number-theory/gcd/#%E6%9B%B4%E7%9B%B8%E5%87%8F%E6%8D%9F%E6%9C%AF)
+ 我们可以对输入输出进行优化，然后就能抢到最优解了。

---

## 作者：_luouhgy_ (赞：1)

思路可能与其他大佬有重复，但我真是纯手打的。

## 题目大意

给你一个长度为 $n$ 的序列 $a$，让你找一个正整数 $k$，使所有 $a_i\mod k$ 恰好含有两个不同的值。

## 思路

首先考虑 $2$，因为只要序列中有奇数也有偶数，那么取余后的结果有且只有 $1$ 和 $2$。

而且如果 $x \bmod y = z$，那么 $x \bmod (y \times 2) = z$ 或 $z + y$。

所以我们从 $2$ 枚举，只要不符合就翻倍，就可以完成这个题目啦。

## Code
```cpp
#include<bits/stdc++.h>//万能头文件 
using namespace std;
int t; 
int main(){
	cin>>t;
	while(t--){
		int n;
		int a[105];
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=2;;i*=2){//从2开始枚举，不符合就*2 
			int flag=0;
			int x=INT_MIN;
			for(int j=1;j<=n;j++){
				if(x==INT_MIN){
					x=a[j]%i;
				}else if(a[j]%i!=x){//满足条件 
					flag=1;
					break; 
				}
			}
			if(flag==1){
				cout<<i<<endl;//多组数据，输出换行 
				break;
			}
		}
	}
	return 0;//完工 
}
```


---

## 作者：OIerWu_829 (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/CF1909B)

## 思路

从 $2$ 开始枚举 $k$，可以用一个 set 容器来存储每次 $a_i\bmod k$ 得到的值，因为 set 自带去重功能，所以如果长度为 $2$ 就输出 $k$。

另外，为了优化时间，每次可以让 $k\times 2$。因为如果 $a\bmod b=c$，则 $a\bmod 2b$ 一定等于 $c$ 或 $b+c$。~~这算是小学数学知识吧。~~

```cpp
#include <iostream>
#include <set>
#define int long long
using namespace std;
int a[1010];
signed main()
{
    int t;
    cin >> t;
    while (t--) {
        set<int> s;
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int k = 2; ; k *= 2) {
            s.clear();
            for (int i = 1; i <= n; i++)
                s.insert(a[i] % k);
            if (s.size() == 2) {
                cout << k << endl;
                break;
            }
        }
    }
    return 0;
}
```


---

## 作者：shredded_beef_qwq (赞：1)

## 具体思路
对于正整数 $x$，将所有 $a_i \bmod 2^x$ 含有的不同的值的个数记作 $f(x)$。

可以发现，必然存在正整数 $x$，使得 $f(x) = 2$。因此，可以通过枚举 $x$ 得到一个可行的答案。
### 证明
使用反证法。

假设不存在正整数 $x$，使得 $f(x) = 2$。则对于任意 $x$，$f(x) = 1 \lor f(x) > 2$ 为真。

因为 $f(1) \le 2$ 且 $f(1) \ne 2$，所以 $f(1) = 1$，也就是一定存在 $x$，使得 $f(x) = 1$。

我们将使得 $f(x) = 1$ 的最大 $x$ 记作 $t$。$f(t) = 1$，意味着所有 $a_i$ 二进制表示的后 $t$ 位相同，此时，$f(t + 1)$ 表示所有 $a_i$ 的二进制表达下从低到高第 $t + 1$ 位的不同的数字个数。因为所有 $a_i$ 二进制表示下从低到高第 $t + 1$ 位只有两种可能，所以 $f(t + 1) \le 2$，又因为 $t$ 为使得 $f(x) = 1$ 的最大 $x$，所以 $f(t + 1) = 2$，与假设矛盾。


## 提示
枚举 $k$ 的取值，$k$ 可以直接从 $2$ 开始，因为 $ \bmod 2$ 只会有 $1$ 或 $2$ 种值，如果数组既有奇数，又有偶数，那么就直接输出 $2$。

## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
long long a[110];
bool f(long long k){
	long long x=a[1]%k;
	for(int i=2;i<=n;i++){
		if(a[i]%k!=x) return true;
	}
	return false;
}
int main(){
	int t;
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		long long k=2;
		while(f(k)==false) k*=2;//这样就只会有1或2种取值。
		cout<<k<<endl;
	}	
	return 0;
}
```

---

## 作者：Pyrf_uqcat (赞：1)

### 题意
多组数据，给定一个长度为 $n$ 序列 $a$，已知每一个 $a_i \bmod k$ 都有两个不同的值，求 $k$。
### 思路
方法：**枚举**。

虽说是枚举，但并不是将 $k$ 一个一个模拟下去，这样肯定会超时。那么应该怎么办呢。

能有两个余数的数，最小的只能是 $2$，所以将 $k$ 从 $2$ 开始。当 $k$ 为 $2$ 时，余数只有两种可能：余数相同（都为$1$ 或 $0$）和余数不同（$1$ 和 $0$），若不同，输出 $k$（输出要加换行），否则将 $k$ 乘 $2$，以此类推。将 $k$ 一直乘 $2$，最后一定可以找到符合条件的答案。题目给出，所有的 $a_i$ 各不相同，所以一定存在解。

---

## 作者：Six_chestnuts (赞：1)

## 思路

很明显，这题的数据范围很小可以直接暴力过此题。

## 细节

细节上的话，可以枚举 $k$ 的值，而且还可以改成乘 $2$ 因为 $k$ 是随便是哪一个值，而题目希望恰好有两只有两个不同的模数，而我们从 $2$ 开始枚举，模数就只有 $0$ 或者 $1$，而如果都是 $0$ 或 $1$ 那么就继续乘，总是会乘出来的。 

## AC 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#pragma GCC optimize(3)
using namespace std;
const int N=105;
int n,a[N];
bool check(int k)
{
	int num=a[1]%k;
	for(int i=2;i<=n;i++)
		if(a[i]%k!=num)
			return true;
	return false;
}
void work()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	int k=2;
	while(!check(k))
		k*=2;
	cout<<k<<"\n";
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	while(t--)
		work();
	return 0; 
}
```


---

## 作者：duanfeitong (赞：0)

### 题意解释

给定一个长度为 $n$ 且各项互不相等的序列 $a$，求使得对于任意 $i \in [1,n]$，$a_i \bmod k$ 的可能值有且仅有两种的 $k$ 的值。

### 题目分析

看到 $\bmod k$ 有且仅有 $2$ 种可能值，容易想到 $k=2$。当序列 $a$ 中同时存在奇数与偶数时，$k=2$ 就是答案。

当 $a$ 中只有奇数或者只有偶数时，因为序列各项互不相等，而各项在二进制下有且仅有 $0$ 和 $1$ 两种形式，所以一定存在一个正整数 $x$ 使得各项在二进制下倒数 $1$ 到 $x$ 位都相等，第 $x+1$ 位不等。这时各项 $\bmod 2^x$ 就只有：$1 \dots$ 与 $0 \dots$ 两种情况。

所以可知：当 $a$ 中只有奇数或者只有偶数时，一定有一个 $k=2^x$ 符合题意（$x$ 为非负整数）。

例如下面一个序列：$9,11,17,5,3$。

转换为二进制是：$01001,01011,10001,00101,00011$。

可以发现，它们最后一位均相等（因为都是奇数），但是倒数第二位有 $0$ 有 $1$，所有此时若 $k=2^2=4$，每个数在二进制下取模就只会剩下后两位一定有且仅有 $2$ 种可能的答案（$11$ 或 $01$）。

因为 $n\le 100$，所以我们只需要从 $2$ 开始枚举 $2$ 的整数次幂，并检查其是否满足题意即可。

---

## 作者：RainCQwQ (赞：0)

# CF1909B Solution
## 思路整理
暴力枚举 $k$ 是不可能的，但是我们可以这样做：

1. $k \gets 1$；
2. $k \gets 2k$；
3. 如果 $a_i \bmod k$ 都是一个数，则回到步骤二；否则 $k$ 便是最后的答案。

不要忘记多测以及存储 $k$ 和数组 $a$ 的数据类型哦。

------------
## AC Code
```cpp
#include <iostream>
using namespace std;
long long a[105];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		for(int i=0;i<n;i++) cin>>a[i];
		long long m=1;
		for(;;m*=2)
		{
			bool flag=false;
			for(int i=1;i<n;i++) if(a[i]%m!=a[i-1]%m) flag=true;
			if(flag) break;
		}
		cout<<m<<endl;
	}
	return 0;
}
```

[记录详情](https://www.luogu.com.cn/record/145500921)

------------
## 官方题解翻译
### 提示一
寻找一个 $k$ 能够使用于多种数据。
### 提示二
$k = 2$ 在多种数据下都起到作用，但如果它不起作用该怎么办？
### 提示三
如果 $k = 2$ 不起作用，即所有数字都是奇数或都是偶数，现在那个 $k$ 可以让你尝试？
### 题解
设 $f(k)$ 是操作后非重复值的数目。

让我们试试 $k = 2$，它适用于所有情况，除非所有数字都是偶数或所有数字都是奇数。

让我们概括一下。如果 $a_i \bmod k = x$，此时有两种情况，一下一种情况成立：

- $a_i \bmod 2k = x$；
- $a_i \bmod 2k = x + k$；

这意味着，如果 $f(k) = 1$（即运算后的所有值均为 $x$），否则便是 $f(2k) = 1$（如果所有 $a_i$ 都变成了 $x$，或者都变成了 $x + k$），或者 $f(2k) = 2$。

因此，尝试 $k = 2^1 , 2^2 , … , 2^{57}$ 便是足够的了。事实上 $f(1) = 1$ 并且 $f(2^{57}) = n$，所以它必定存在 $m < 57$ 这样 $f(1) = 1$ 且 $f(2^{m+1}) \ne 1 \Longrightarrow f(2^{m+1}) = 2$。

更多（更直观？）解释：

$a_i \bmod 2^j$ 对应着 $a_i$ 二进制的最后第 $j$ 位。肯定存在 $j$ 使得二进制的最后 $j$ 位有两种不同的状态。

在下图中，$a \gets [1005,2005,7005,11005,16005]$ 且 $k = 16$。

![CF1909B图](https://cdn.luogu.com.cn/upload/image_hosting/8wxnt39w.png)

时间复杂度：$O(n \log (\max a_i))$。

---

## 作者：__LiChangChao__ (赞：0)

## 思路

可以采用二进制分组的方式。

注意题目中有这样一段话：

> It is guaranteed that all the $ a_i $ are distinct.
>
> 保证 $a_i$ 互不相同。

有一个显然的结论，不同的数在二进制位下至少有一位不同。

所以可以考虑枚举二进制位，由于二进制位只有 $0,1$ 两种情况，也符合有且只有两种余数的要求。

于是代码就很好写了。

## 代码

```php
<?php
    $input="";
    $TOP=0;$INPUTARR=array();$NUMCOUNT=0;
    function read(){
        global $TOP,$input,$INPUTARR,$NUMCOUNT;
        if($TOP==$NUMCOUNT){
            $input=fgets(STDIN);
            $INPUTARR=explode(" ",$input);
            $TOP=0;$NUMCOUNT=count($INPUTARR);
        }
        $TOP++;
        return $INPUTARR[$TOP-1];
    }
    $t=read();
    while($t--){
        $n=read();
        $a=array(0);
        for($i=0;$i<$n;$i++){
            $a[$i]=read();
        }
        for($i=0;;$i++){
            $flag=array(false,false);
            foreach($a as $j)$flag[($j>>$i)&1]=1;
            if($flag[0]&&$flag[1]){
                print(1<<($i+1)."\n");
                break;
            }
        }
    }
?>
```



---

## 作者：The_jester_from_Lst (赞：0)

简易枚举题。

显然看到题目我们直接想到暴力枚举 $k$ 的值，但是普通枚举显然会超时，这时我们想到用二的次幂优化，把复杂度降到 $O(\log{n})$ 级别，即可通过此题。因为给出的 $a$ 互不相同，所以不存在无解。

附上代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int rd(){
	int jya=0,ysc=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')ysc=-1;ch=getchar();}
	while(isdigit(ch)){jya=jya*10+(ch-'0');ch=getchar();}
	return jya*ysc;
}
inline void wr(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)wr(x/10);
	putchar(x%10+'0');
}
int t,n,a[186];
inline bool ck(int k){
	int sa=a[1]%k;
	for(int i=2;i<=n;++i){
		if(a[i]%k!=sa){
			return 1;
		}
	}
	return 0;
}
signed main(){
	t=rd();
	while(t--){
		n=rd();
		for(int i=1;i<=n;++i)a[i]=rd();
		int k=2;
		while(!ck(k))k<<=1;
		wr(k);
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：AKPC (赞：0)

显然 $\exists i\in\text{N},2^i$ 满足条件。

因为如果模 $2^{i-1}$ 对应集合大小为 $k$，则 $2^i$ 最长只有 $2k$。

然而必然有一个 $i$ 满足集合大小为 $1$，$i$ 是能取到的最大值满足对应集合大小为 $1$ 时，$i+1$ 必然是正确答案。

$n$ 很小，那枚举 $i$ 并考虑 $2^i$ 就行了。

---

## 作者：kczw (赞：0)

# 题意
共 $t$ 组数据，每组数据给定一个长为 $n$ 数列 $a$，你需要给定一个最大的 $k$，保证数列 $a$ 中的所有数对 $k$ 取模后的结果有且仅有两种。
# 思路
$a$ 数列的所有元素对 $k$ 取模后的结果有两种，那么取模结果相同的两个 $a$ 数列的元素相减一定是 $k$ 的倍数。

所以我们将两种对 $k$ 取模结果不同的数分成两份，然后把每份的任意两数之间的差的绝对值取 $\gcd()$，得到的值就是 $k$ 的最大值。

但是新的问题出现了，在不知道 $k$ 的情况下，根本不知道怎么把 $a$ 数列正确分成两份。

这里我选择 DFS 去暴力枚举将 $n$ 分配成两份后取到的 $k$ 的值，同时剪枚，最后取最大 $k$ 值。
# 实现
```cpp
#include<iostream>
#include<set>
#define int long long
using namespace std;
inline int gcd(int a,int b){return b==0?a:gcd(b,a%b);}
int t,n,k,a[105];
void dfs(int e,int as,int f,int s){
	if(as<=k&&as!=0)return;
	if(e==n+1){k=as;return;}
	dfs(e+1,gcd(a[e]-(f<0?a[e]:f),as),a[e],s);
	dfs(e+1,gcd(a[e]-(s<0?a[e]:s),as),f,a[e]);
}signed main(){
	scanf("%lld",&t);
	while(t--){
		set<int> h;
		int nn=0,lst=1e18;k=2;
		scanf("%lld",&n);
		for(int i=1,q;i<=n;i++)scanf("%lld",&q),h.insert(q),lst=min(lst,q);
		for(auto num:h)a[++nn]=num-lst;
		if(nn<3){printf("%lld\n",1000000000000000000);continue;}
		dfs(1,0,-1,-1);
		printf("%lld\n",k);
	}return 0;
}
```

---

## 作者：Storm_Lightning (赞：0)

## 题意
给你一个整数 $n$，再给你 $n$ 个整数。

现要求一个整数 $k$，使得这 $n$ 个数中，$\bmod$ $k$ 的值有且只有两种值。

## 推导
因为题目要求有且只有两种值，所以我们第一个想到的 $k$ 一定是 $2$。

$n$ 个数 $\bmod$ $2$ 的值分为 $3$ 种：

- 余数全为 $1$。

- 余数全为 $0$。

- 余数为 $1$ 或 $0$。

若为前两种，则给 $2\cdot k$，这样其中的每一种又可以分为两种。一直循环下去，必定能找到满足条件的 $k$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int unsigned long long
#define inf 1000000000000000000
int t;
int n;
int a[101];
signed main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		int k=2;
		while(k<=inf)
		{
			int mod=a[1]%k;
			int ans1=-1,ans2=-1;
			ans1=mod;
			int flag=0;//记录行还是不行 
			for(int i=2;i<=n;i++)
			{
				if(a[i]%k!=ans1&&ans2==-1)
				{
					ans2=a[i]%k;
				}
				if(a[i]%k!=ans1&&a[i]%k!=ans2)
				{
					flag=1;
					break;
				}
			}
			if(ans2!=-1&&flag==0)
			{
				cout<<k<<endl;
				break;
			}
			k*=2;
		}
	}
	return 0;
} 
```

如果有看不懂的地方，请私信我。

---

## 作者：_O_v_O_ (赞：0)

首先，要是这个数组里面有奇有偶，那么肯定可以输出 $2$，可以。

众所周知，如果一个数 $x\bmod y=z$，则 $x\bmod (2\times y)$ 只能是 $z$ 或 $y+z$。

而根据上面的结论，只要 $\bmod\ x$ 不行，就将模数 $x$ 扩大一倍，数组中的所有数 $\bmod\ x$ 还是只有 $1$ 或 $2$ 种取值。

所以 $x$ 我们最先取 $2$，随后再 $O(n)$ 的检查一遍是否符合，如果不符合，就将模数 $\times 2$ 即可，然后一直做下去，直到符合为止。

时间复杂度 $O(n\log(\max\limits^{n}_{i=1}a_i))$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int T;
int n,a[100005];

bool check(int k){
	int x=-1;
	for(int i=1;i<=n;i++){
		if(x==-1) x=a[i]%k;
		else if(a[i]%k!=x) return true;
	}
	return false;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		int k=2;
		while(1){
			if(check(k)){
				cout<<k<<endl;
				break;
			}
			k*=2;
		}
	}
	return 0;
}
```


---

## 作者：Lu_xZ (赞：0)

构造题，这里介绍两种方法。
## 法一：二进制拆分
考虑只去模 $2^k$。

把每个数二进制拆分，模 $2^k$ 的结果即为这个数的 $[0, k - 1]$ 位。

一直往上枚举 $k$，直到所有数的 $[0, k - 2]$ 位相同，第 $k - 1$ 位不同。

```
void solve() {
	int n;
	cin>> n;
	vector<ll> a(n);
	for(ll &x : a) cin >> x;
	auto check = [&](ll p) -> bool {
		set<ll> se;
		for(int i = 0; i < n; ++ i) se.insert(a[i] % p); 
		return se.size() == 2;
	};
	for(int i = 1; ; ++ i) {
		if(check(1ll << i)) {
			cout << (1ll << i) <<'\n';
			return;
		}
	}
}
```
## 法二：数学
令
$$
x = gcd\{a[1] - a[0], a[2] - a[1], a[3]- a[2], ... , a[n - 1] - a[n - 2]\}
$$
此时
$$
ans = 2x
$$
考虑去如何证明。

不难得到
$$
\forall i \in [1, n),\hspace{0.3cm} x \mid a[i] - a[i - 1]
$$
换句话说，**此时所有数模 $x$ 结果相同**。

不妨设
$$
a[i] = p_ix + q
$$
+ 若$p_i$为偶数，则 $a[i] \bmod 2x = q$
+ 若$p_i$为奇数，则 $a[i] \bmod 2x = x + q$

> 由于 $q < x$，所以 $x + q < 2x$

> 又 $x \neq 0$，所以 $q \neq x + q$

情况一：$p$ 中既有奇数又有偶数，显然成立。

情况二：$p$ 全为奇数或全为偶数，则此时 $gcd\{a[i] - a[i - 1]\}$ 一定是 $2x$ 的倍数，与最大为 $x$ 矛盾。
```
void solve() {
	int n;
	cin >> n;
	ll ans = 0;
	vector<ll> a(n);
	for(int i = 0; i < n; ++ i) {
		cin >> a[i];
		if(i) ans = gcd(ans, abs(a[i] - a[i - 1]));
	}
	cout << ans * 2 << '\n';
}
```

---

