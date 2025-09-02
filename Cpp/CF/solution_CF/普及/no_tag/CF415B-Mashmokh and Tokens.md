# Mashmokh and Tokens

## 题目描述

Bimokh是Mashmokh的老板。他每天会给每个员工一定数量的代币。有 $n$ 天，每天老板给工人 $x_i$ 枚代币，每个工人都可以退还 $w$ 枚代币以获得 $\displaystyle \frac{w-a}{b}$ 数量的美元请

Mashmokh想尽可能多地存一些代币，这样他每天能得到最多的钱。你帮助他计算第$i$天他在获得最多钱时可以保存的代币数量。

## 样例 #1

### 输入

```
5 1 4
12 6 11 9 1
```

### 输出

```
0 2 3 1 1 ```

## 样例 #2

### 输入

```
3 1 2
1 2 3
```

### 输出

```
1 0 1 ```

## 样例 #3

### 输入

```
1 1 1
1
```

### 输出

```
0 ```

# 题解

## 作者：___define___ (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF415B)

[原题](https://codeforces.com/contest/415/problem/B)

这题的翻译错了，应该是 $\dfrac{w \cdot a}{b}$ 而不是 $\dfrac{w - a}{b}$。

## 思路

每个员工都想获得最多美元，所以我们不难发现公式为 $\dfrac{w \cdot a \bmod b}{a}$，然后根据题意套公式，这题就可以迎刃而解了。

注意：要开 `long long`！

[AC记录](https://codeforces.com/contest/415/submission/278998130)

---

## 作者：Gaochenxi103_QWQ (赞：2)

## 题目分析
这道题目的中文部分好像翻译错了，想了半天过不了样例，结果看了看英文，好像翻译有点坑。

Bimokh 每天给 Mashmokh 一点代币，一共给 $n$ 天，每天 $x_i$ 个代币，代币可以换取钱，每 $w$ 枚代币可以换 $\frac{w\times a}{b}$ 元，其中 Mashmokh 想要换很多钱的同时剩一些代币，换句话就是既要钱又要代币。

而既然要代币和钱都要多，那么最优的情况是不是就是上交 $n$ 代币，要使 $\frac{n\times a}{b}$ 的钱刚刚好可以换钱，并且不浪费。那是不是 $n\cdot w$ 刚好可以被 $b$ 整除，也就是换到的钱是整数。

那么是不是我们将当天发的代币全部拿去换，就是可以换 $\frac{x_i\times a}{b}$ 元，为了最优，是不是可以只换可以被整除的那部分，剩下的是不是就是我们的答案了？

因为剩下的代币在最开始的时候和全部的代币同时乘了 $a$ 这个数，所以我们要对剩下的部分除以一个 $a$ 来得出结果。

伪代码如下。
```cpp
剩下的代币 = (发放的代币 * a) % b /*剩下的不可以整除的部分*/ / a ;
```
所以代码实现就很简单了。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,a,b,cnt; 
signed main() {
	ios::sync_with_stdio(0);
	cout.tie(0);
	cin.tie(0);
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++)
	{
		cin>>cnt;
		cout<<((cnt*a)%b)<<" ";
	}
	return 0;
}
```


------------
首先不知道什么原因，我的代码 [ Unknown Error](https://www.luogu.com.cn/record/161770886) 了，但应该整体思路，没有问题。

哪位大佬帮忙看看。

---

## 作者：Elhaithan (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF415B)

### 题目大意  
这道题的题目翻译有误，其原文应为 $\lfloor \frac{w·a}{b}\rfloor $ 而并非 $\lfloor \frac{w-a}{b}\rfloor$ 。  

总共有 $n$ 天，每天老板会给 $x_i$ 个代币，将代币换成尽可能多的美元后，问最多能保留几个代币。  
### 思路  
首先，想要将 $x_i$ 个代币尽可能多的的换成美元，最多能得到的美元数 $dol$ 为 $\lfloor \frac{x_i·a}{b} \rfloor$ ,根据最多得到的美元数可求得换取这么多美元所需要的代币数 $need$ 为 $\lceil \frac{dol·b}{a} \rceil$ ，所以剩下的代币数量为 $x_i-need$ 。  
根据题目中 $x$ 的范围可知要开 `long long` 。
### 代码  
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//全局开 long long 
const int N = 1e5+2;
int n,a,b;
int x[N];//代币
int dol/*最大美元数*/,need/*美元需换取的代币数*/;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin>>n>>a>>b;
	for(int i=1; i<=n; i++){
		cin>>x[i];//输入 
	}
	for(int i=1; i<=n; i++){
		dol=floor(x[i]*a*1.0/b);
		need=ceil(dol*1.0*b/a);//一定要向上取整，不然最后剩下的代币可能会比现实多 
		cout<<x[i]-need<<' ';//差即为剩余代币数 
	}
	
	return 0;
}
```

---

## 作者：nominater (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF415B)  
### 题目大意
工人每人每天可以获得代币 $x$，可以退还 $w$ 枚代币以获得 $[\frac{w \times a}{b}]$ 美元。
### 思路  
应用 $[\frac{w \times a}{b}]$ 计算出最大能够兑换的钱币数量。然后再用数组储存所剩的最大代币数。对最大美元数关于 $a$ 取模。若能够整除，则最大代币数自减；若不能够整除，则仍保留原最大代币数。

### 代码
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+10;
ll n,a,b,x[N];
ll c[N];
int main()
{
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++)
	{
		cin>>x[i];
		ll m=(x[i]*a)/b;
		c[i]=x[i]-(m*b)/a;
		if((m*b)%a)c[i]--;
	}
	for(int i=1;i<=n;i++)
	{
		cout<<c[i]<<" ";
	}
	return 0;
}
```


---

## 作者：sunhaozhe111022 (赞：1)

# [题目传送门](https://www.luogu.com.cn/problem/CF415B)

**题目大意：**

有一个老板在 $n$ 天内每天给员工发 $ x_{i} $ 个代币,员工每天可以用 $w$ 个代币去换取 $\dfrac{w \cdot a}{b}$ 元。问员工每天会剩余多少个代币。

**思路：**

因为员工们都想要得到更多的马内，所以直接用 $a \cdot x$ 的结果对 $b$ 取模即可。

**代码如下：**

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,b,a,x;//记得开long long
int main()
{
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++)
	{
		cin>>x;
		cout<<x*a%b<<" ";
	}
	return 0;
}
```

---

## 作者：maomao233 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF415B)  
[CodeForces 传送门](https://codeforces.com/problemset/problem/415/B)

首先我们计算第 $i$ 天 Mashmokh 最多能获得多少钱。由题得，$w$ 枚代币 $=\lfloor\dfrac{w\cdot a}{b}\rfloor$ 美元，当我们把 $x_i$ 枚代币全部代入，则最多能获得 $\lfloor\dfrac{x_i\cdot a}{b}\rfloor$ 美元。

但这样可能不是最优解，因为这个式子是向下取整的，$x_i$ 小一点可能也不会影响式子的值。  
于是我们反推回去。设最少需要 $w'$ 枚代币能获得 $\lfloor\dfrac{x_i\cdot a}{b}\rfloor$ 美元，则需满足：
$$\lfloor\dfrac{w'\cdot a}{b}\rfloor=\lfloor\dfrac{x_i\cdot a}{b}\rfloor.$$
注意到当 $(w'\cdot a)\bmod b=0$ 时 $w'$ 可以达到最小。此时满足：
$$\dfrac{w'\cdot a}{b}=\lfloor\dfrac{x_i\cdot a}{b}\rfloor.$$
解方程，两边同乘 $b(b\not=0)$ 得：
$$w'\cdot a=\lfloor\dfrac{x_i\cdot a}{b}\rfloor\cdot b.$$
两边同除以 $a(a\not=0)$ 得：
$$w'=\dfrac{\lfloor\dfrac{x_i\cdot a}{b}\rfloor\cdot b}{a}.$$

显然最终的答案为 $(x_i-w')$，于是我们计算即可。  
注意向下取整和非向下取整。

```cpp
signed main()
{
	int n,a,b;
	rd(n,a,b);
	for(int i=1;i<=n;i++)
	{
		int x;
		rd(x);
		wt(x-ceil(x*a/b*b/(double)a)),kg;
	}
	hh;
	return 0;
}
```

---

## 作者：fox_nice (赞：1)

**大致题意：**

每天老板会给员工 $x_i$ 个代币，员工每天上交 $w$ 个代币，就能获得 $\lfloor\frac{w \times a}{b}\rfloor$ 元，这个员工想获得尽量多的钱，请问他每天能剩下多少个代币。

**分析：**

首先看数据范围，$(1\le a,b\le 10^9 )$，$(1 \le x_i\le 10^9 )$。一看，要开 `long long`。这是第一步。

第二步，理解题意。

要获得尽量多的钱币，也就是不能有剩余，也就是要上交的代币数 $w \times a$ 要能被 $b$ 整除。也就是指，剩下的代币数 $ = \dfrac{x_i \times a \bmod b } a$，为什么要 $ \div a$ 呢？我们进行讨论。

- 当 $a=b$ 或 $a$ 是 $b$ 的倍数时，剩下的代币数一定是 $0$，就算 $\div a$ 之后依旧是  $0$；

- 当 $a<b$ 且 $a$ 是 $b$ 的因数时，会剩下 $\dfrac{x_i \bmod b}a$。而这一部分代币一开始会被 $ \times a $ 的 ，现在再 $\div a $ 是可以整除且得到结果的；

- 当 $a<b$ 且 $a$ 与 $b$ 互质时，会剩下 $x_i \bmod b$ 这么多代币，而这么多钱一开始会被 $ \times a $ 的 ，现在再 $\div a $ 同样是可以整除且得到结果的。

### 代码

```cpp
#include <iostream>
using namespace std;
int main(){
    int n;
    long long a,b;
    cin >>n>>a>>b;
    for(int i=0;i<n;i++){
        long long x;
        cin >>x;
        cout<<x*a%b/a<<" ";
    }
}
```


---

## 作者：ST_AS_IS_ZHY (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF415B)

## 题意

每一天员工都能得到一些钱，而员工想要在利益最大化的情况下尽可能的留下更多钱。

## 思路

当钱乘以 $b$ 正好能被 $a$ 整除时，那就一点都不用留，直接梭哈。而如果不能整除，那就在求出让利益最大化的情况要存的最少钱币，也就是 ```ceil(1.0 * b * (x[i] * a / b) / a);```。 输出当天的钱减去这个值就行。

## 代码

```c++
// Problem: Mashmokh and Tokens
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF415B
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long

using namespace std;

int n , a , b , x[400001] , ans[400001];

signed main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin >> n >> a >> b;
    for(int i = 1 ; i <= n ; i ++)
    {
	cin >> x[i];
	if((x[i] * a) % b == 0) ans[i] = 0;
	else ans[i] = x[i] - ceil(1.0 * b * (x[i] * a / b) / a);
	cout << ans[i] << ' ';
    }
	
    return 0;
}

---

## 作者：Garbage_fish (赞：0)

## 题意

翻译有误，$w$ 个金币应该能换 $\left\lfloor\dfrac{wa}{b}\right\rfloor$ 个美元而非 $\dfrac{w-a}{b}$ 个。

每天给你 $x$ 个金币，当天没用完的不能留到第二天，你换成尽量多的美元后，还能剩下多少金币？

## 做法

好像题解区都是公式的，来推个式子。

$x$ 个金币能换成的美元数 $c$ 为：

$$c=\left\lfloor\dfrac{xa}{b}\right\rfloor$$

$c$ 个美元需要的金币数 $d$ 为：

$$d=\left\lceil\dfrac{bc}{a}\right\rceil$$

剩下的钱 $ans$ 为：

$$ans=x-d$$

**[AC](https://www.luogu.com.cn/record/136679734) Code:**

```cpp
#include <bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std; 
const int N=1e5+10;
int n,a,b,c,d,x,ans;
signed main(){
	IOS;
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++){
		cin>>x;
		c=x*a/b;
		d=ceil(1.0*b*c/a);
		ans=x-d;
		cout<<ans<<" ";
	}
	return 0;
}
```


---

## 作者：live_cxy110122 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF415B)
### 题意
每天会得到 $x$ 个代币，代币可以换钱，$w$ 个代币可以换 $\displaystyle \frac{w-a}{b}$ 美元，在换取最多钱的情况下留下最多的钱。
### 思路
要省下最多代币，只要上交刚好能换到最多的美元的代币就行了。
即公式为 $\displaystyle \frac{w \times a \bmod b}{a}$。
### 代码
```cpp
#include <bits/stdc++.h>
#define int long long		//不开long long见祖宗 
using namespace std;
int a, b, n;
signed main()				//signed == int
{
    cin>>n>>a>>b;
    while(n--)				//有n天 
	{
    	int x;
        cin>>x;
        cout<<(x * a % b) / a<<" ";//公式 
    }
    return 0;
}
```

---

## 作者：Chronomaly_Atlandis (赞：0)

**题目描述**

有 $n$ 天，每天老板给工人 $x$ 枚代币，每个工人都可以退还 $w$ 枚代币以获得一定数量的美元（ 为 $\left\lfloor\dfrac{w\times a}{b}\right\rfloor$ ）。要帮 $Mashmokh$ 计算每一天他在获得最多钱时可以保存的代币数量。

**题目思路**

要获得更多钱，必须要退还更多代币。

如果要尽可能多的省下代币，只要上交刚好能获得最多的美元数量的代币就行了。

不难发现公式是 $\left\lfloor\dfrac{w\times a\bmod b}{b}\right\rfloor$。

举个栗子

样例一中， $a$ 为 $1$ ， $b$为 $4$ 。

第一天获得 $12$ 枚代币。

| $退还的代币$ | $得到的美元$ | $剩下的代币$ |
| -----------: | -----------: | -----------: |
| $1$ | $0$ | $11$ |
| $2$ | $0$ | $10$ |
| $3$ | $0$ | $9$ |
| $4$ | $1$ | $8$ |
| $5$ | $1$ | $7$ |
| $6$ | $1$ | $6$ |
| $7$ | $1$ | $5$ |
| $8$ | $2$ | $4$ |
| $9$ | $2$ | $3$ |
| $10$ | $2$ | $2$ |
| $11$ | $2$ | $1$ |
| $12$ | $3$ | $0$ |


可以发现退还 $12$ 枚代币获得 $3$ 美元是最多的。剩下的几天读者可以自己推一下。

知道了公式，问题就迎刃而解了。

**Code**

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	long long a,b,n;
	cin.tie(NULL);
    cin >> n >> a >> b;
    while(n--){
    	long long x;
        cin >> x;
        cout << (x*a%b)/a << " ";
    }
    return 0;
}
```






---

## 作者：Wei_Yue (赞：0)

### 题意

用 $token$ 去换钱，在换取最多钱的情况下留下最多的 $tokens$。

每上交 $ w $ 个 $token$ 可以换取 $\lfloor\dfrac{w\times a }{a}\rfloor$ 元。

### 思路

根据题意不难发现，

因为每个员工都想要尽量多的钱，所以我们只需要将员工手中的代币尽可能的换成钱，这样所留下的代币就是最多的了。

公式为:  $\lfloor\dfrac{w\times a\bmod b }{a}\rfloor$

可以通过一个数组 $token$ 来记录每个员工的代币数，

再运用公式输出每个员工所最多剩下 $token$。

### Tip: 

因为题目给出的范围为  $ 0\leq a,b \leq10^9$，

且 $0 \leq x_i \leq 10^9$  ，

所以要开 ```
long long```。



### Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
long long token[100005],ans[100005],a,b,n;
int main(){
	cin>>n>>a>>b;
	for(int i=0;i<n;i++){
		cin>>token[i];//输入 
		ans[i]=((token[i]*a)%b)/a;//运用公式 
	}
	for(int i=0;i<n;i++){
		cout<<ans[i]<<" ";//输出 
	}
	return 0;
} 
```










---

## 作者：i_dont_know_who_am_i (赞：0)

**题意简介：**

老板会给员工 $x_i$ 个代币，员工可以上交 $w$ 个代币来获得 $\lfloor\frac{w \times a}{b}\rfloor$ 美元，这个员工想得到尽量多的美元，请问他会剩下多少个代币。

**分析：**

要获得尽量多的美元，首先要尽量给代币，其次要尽可能多的省下代币的话，只要上交刚好能达到能够获得最多的美元数量的代币就行了。那不难发现剩余的代币数为 $\frac{w\times a \bmod b}a$。

**代码：**

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
long long a,b,x;
int main(){
    cin >>n>>a>>b;
    for(int i=1;i<=n;i++){
        cin >>x;
        cout<<(x*a%b)/a<<" ";
    }
}
```


---

