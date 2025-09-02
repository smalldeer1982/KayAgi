# [ABC044D] 桁和

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc044/tasks/arc060_b

$ 2 $ 以上の整数 $ b $ および $ 1 $ 以上の整数 $ n $ に対し、関数 $ f(b,n) $ を次のように定義します。

- $ n\ <\ b $ のとき $ f(b,n)\ =\ n $
- $ n\ \geq\ b $ のとき $ f(b,n)\ =\ f(b,\,{\rm\ floor}(n\ /\ b))\ +\ (n\ {\rm\ mod}\ b) $

ここで、$ {\rm\ floor}(n\ /\ b) $ は $ n\ /\ b $ を超えない最大の整数を、 $ n\ {\rm\ mod}\ b $ は $ n $ を $ b $ で割った余りを表します。

直感的に言えば、$ f(b,n) $ は、$ n $ を $ b $ 進表記したときの各桁の和となります。 例えば、

- $ f(10,\,87654)=8+7+6+5+4=30 $
- $ f(100,\,87654)=8+76+54=138 $

などとなります。

整数 $ n $ と $ s $ が与えられます。 $ f(b,n)=s $ を満たすような $ 2 $ 以上の整数 $ b $ が存在するか判定してください。 さらに、そのような $ b $ が存在するならば、その最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ n\ \leq\ 10^{11} $
- $ 1\ \leq\ s\ \leq\ 10^{11} $
- $ n,\,s $ はいずれも整数である

## 样例 #1

### 输入

```
87654
30```

### 输出

```
10```

## 样例 #2

### 输入

```
87654
138```

### 输出

```
100```

## 样例 #3

### 输入

```
87654
45678```

### 输出

```
-1```

## 样例 #4

### 输入

```
31415926535
1```

### 输出

```
31415926535```

## 样例 #5

### 输入

```
1
31415926535```

### 输出

```
-1```

# 题解

## 作者：oimaster (赞：5)

简单数学题。

分几种情况来讨论。

- $n<s$，显然不可能，输出 $-1$。
- $n=s$，可以知道 $b>n$，那么最小的 $b$ 就是 $n+1$。

如果两种特殊情况都不符合，我们就需要分析一下 $n$。$n\le10^{11}$，那么复杂度应在 $\operatorname{O}\left(\sqrt{n}\right)$。

那么如果 $b<\sqrt{n}$，直接枚举即可。

如果枚举无结果，那么我们就知道 $b\ge\sqrt{n}$。那么再次显然我们的 $n$ 在 $b$ 进制中是两位数。

那么我们假设 $n$ 的第一位为 $x$，第二位为 $y$，可以得到：

- $n=xb+y$
- $s=x+y$

那么就可以得到 $n-s=xb+y-(x+y)$，整理一下就是 $n-s=x(b-1)$。

由此我们知道 $x$ 是 $n-s$ 的因数，$b$ 是 $\frac{n}{x}+1$，而且 $b$ 还是一个整数。

现在我们就可以枚举所有可能的 $x$，算出对应的 $b$。最后进行检验即可。

```cpp
#include<iostream>
#include<cmath>
using namespace std;
#define int long long
int f(int b,int n){
	if(n<b)
		return n;
	return f(b,n/b)+n%b;
}
signed main(){
	int n,s;
	cin>>n>>s;
	if(n<s){
		cout<<-1<<endl;
		return 0;
	}
	if(s==n){
		cout<<n+1<<endl;
		return 0;
	}
	int sqr=ceil(sqrt(n));
	for(int i=2;i<=sqr;++i)
		if(f(i,n)==s){
			cout<<i<<endl;
			return 0;
		}
	int ans=-1;
	for(int i=1;i<=sqr;++i)
		if((n-s)%i==0&&f((n-s)/i+1,n)==s)
			ans=(n-s)/i+1;
	cout<<ans<<endl;
}
```

---

## 作者：naroto2022 (赞：3)

# ABC044D 题解

### 题面

[原题传送门](https://www.luogu.com.cn/problem/AT_arc060_b)

### 题意

给定一个 $n$ 和 $s$，求一个最小的 $m$ 使得 $n$ 在 $m$ 进制下各位数的和为 $s$。

### 思路

这类题其实可以往 $\sqrt n$ 部分暴力，剩下的利用其在 $m,m\geqslant\sqrt n$ 进制下只有两位的特性找性质。

类似的有这道题：[P2425](https://www.luogu.com.cn/problem/P2425)。

这道题首先先判断特殊情况。

1. $n=s$，此时显然 $m=n+1$。
2. $n<s$，此时无解，输出 `-1`。

接下来就开始暴力枚举所有的小于 $\sqrt n$ 的进制下的 $s$，一一判断，相等的直接输出。

紧接着，开始思考大于等于 $\sqrt n$ 的情况，此时 $n$ 在 $m$ 进制下只有两位，不妨设 $n=\overline{xy}$，则有如下两个式子。

- $n=mx+y$。
- $s=x+y$。

两式相减得 $n-s=(m-1)x$。

所以 $x,m-1$ 均为 $n-s$ 的因数，同时要满足 $m-1\geqslant\sqrt n$，所以考虑枚举 $x$，然后判断其是否是 $n-s$ 的因数，如果是再算其是否满足题意。

于是，就过了这道题啦~~~

### 实现细节

1. 在枚举 $x$ 时，因为要求的 $m$ 要尽量小，所以 $x$ 就要尽量大，所以考虑倒序枚举。
2. 最后如果没有找到 $m$ 满足题意，记得输出 `-1`。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define ll long long
using namespace std;
ll n,s;
void write(ll n){if(n<0){putchar('-');write(-n);return;}if(n>9)write(n/10);putchar(n%10+'0');}
ll read(){ll x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
ll f(ll a, ll b){ll res=0;while(a){res+=a%b;a/=b;}return res;}
int main(){
    n=read();s=read();
    if(n<s){write(-1);putchar('\n');return 0;}
    if(n==s){write(n+1);putchar('\n');return 0;}
    for(int i=2; i<=sqrt(n); i++) if(f(n,i)==s){write(i);putchar('\n');return 0;}
    for(int i=sqrt(n); i>=1; i--) if((n-s)%i==0&&f(n,(n-s)/i+1)==s){write((n-s)/i+1);putchar('\n');return 0;}//记得是倒序枚举
    write(-1);putchar('\n');//无解
    return 0;
}
//n=mx+y
//s=x+y
//n-s=(m-1)x
```

---

## 作者：Krimson (赞：3)

### 先给出结论：所有的x进制一定满足$x-1|n-s$    
~~感觉只要去写过柿子都蛮好发现结论的吧。~~  
接下来给出证明:    
对于n,把它拆分成  
$$
a_0+xa_1+...+x^na_n=n
$$
$$
a_0+...+a_n=s  
$$  
上式减下式可以得到  
$$
a_1(x-1)+a_2(x-1)(x+1)+...+a_n(x-1)(x^{n-1}+x^{n-2}+...+1)=n-s
$$  
对于这个因式分解有很多种证明方法，这里就不赘述了  
发现左边每一项都有$x-1$  
也就是说$x-1|n-s$，证毕  
所以只要去枚举n-s的因数，再暴力套给函数判断是否为s就好了  
记得判断一下无解的情况和n=s的情况  
```
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define ri register int
#define ll long long
il ll read(){
    bool f=true;ll x=0;
    register char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=false;ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    if(f) return x;
    return ~(--x);
}
il void write(const ll &x){if(x>9) write(x/10);putchar(x%10+'0');}
il void print(const ll &x) {x<0?putchar('-'),write(~(x-1)):write(x);putchar('\n');}
il int max(const int &a,const int &b){return a>b?a:b;}
il int min(const int &a,const int &b){return a<b?a:b;}
ll n,s;
ll getval(ll x,ll k){
    ll ans=0;
    while(x){
        ans+=x%k;
        x/=k;
    }
    return ans;
}
const int MAXN=1e6+7;
ll yz[MAXN];
int main(){
    n=read(),s=read();
    for(ll i=1;i*i<=n-s;++i){
        if(!((n-s)%i)){
            if(i*i==n-s){
                yz[++yz[0]]=i;
            }
            else{
                yz[++yz[0]]=i;
                yz[++yz[0]]=(n-s)/i;                
            }
        }
    }
    sort(yz+1,yz+yz[0]+1);
    for(ri i=1;i<=yz[0];++i){
        if(getval(n,yz[i]+1)==s){
            print(yz[i]+1);
            return 0;
        }
    }
    if(n==s) print(n+1);
    else print(-1);
    return 0;
}
```


---

## 作者：shaozhehan (赞：2)

[原题链接](https://www.luogu.com.cn/problem/AT_arc060_b)

[AtCoder 链接](https://atcoder.jp/contests/abc044/tasks/arc060_b)

题目大意：

设一个函数 $f$，$f(b,n)=\begin{cases}n&n<b\\f(b,\left\lfloor\dfrac{n}{b}\right\rfloor)+(n\bmod b)&\text{otherwise}\end{cases}$，如 $f(100,87654)=8+76+54=138$。给定两个数 $n$ 和 $s$，求满足 $f(b,n)=s$ 时的 $b$ 的最小取值。如果无解，输出 $\texttt{-1}$。

思路：

显然，$f(b,n)$ 就等于 $n$ 在 $b$ 进制中的数码和。我们可以写出 $f$ 函数的代码。
```cpp
inline long long f(const long long &b, const long long &n){// 题目中的 f 函数，求 n 在 b 进制中的数码和
    long long sum = 0, temp = n;
    while (temp){
        sum += temp % b;
        temp /= b;
    }
    return sum;
}
```

- 如果 $s>n$，那么显然没有可以符合条件的 $b$，输出 $\texttt{-1}$ 并退出程序。
- 如果 $s=n$，那么 $n$ 在 $b$ 进制中必为一位数，$b\geq n+1$，输出 $n+1$ 并退出程序。
- 如果 $b\leq\sqrt{n}$，那么 $b^2\leq n$，所以 $n$ 在 $b$ 进制下的位数至少为 $3$。此时，我们可以暴力枚举 $b$，如果有符合条件的 $b$，就输出 $b$ 并退出程序。
- 如果没有符合要求的 $b\leq\sqrt{n}$，那么显然 $n$ 在 $b$ 进制中必然为两位数，设其为 $(\overline{pq})_b$。

可以列出关于 $b$ 的含参方程如下：$\begin{cases}n=bp+q\\s=p+q\end{cases}$。

两式相减可得：$n-s=(b-1)p$。

移项并化简可得：$b=\dfrac{n-s}{p}+1$。

我们考虑暴力枚举 $p$，显然 $p<b$，所以我们可以从 $1$ 枚举到 $\sqrt{n}$。最终，如果有符合条件的 $p$ 和 $b$，那么就输出 $b$，否则输出 $\texttt{-1}$。

坑点：

1. 全程开 ```long long```，否则会炸精度！
1. $n<s$ 和 $n=s$ 的特判不要忘记！
1. 每次找到符合要求的 $b$ 时，立即跳出程序！
1. 在枚举 $b>\sqrt{n}$ 时，我们需要特判 $(n-s)\bmod i\not = 0$ 时直接枚举下一个 $p$！
1. 在枚举 $b>\sqrt{n}$ 时，不要找到 $b$ 就输出，我们还需要验证 $f(b,n)$ 是否等于 $s$ 才能输出！

上代码：
```cpp
#include <cmath>
#include <iostream>
using namespace std;

// f 函数，上文有注释，不解释
inline long long f(const long long &b, const long long &n){
    long long sum = 0, temp = n;
    while (temp){
        sum += temp % b;
        temp /= b;
    }
    return sum;
}

int main(){
    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);// cin、cout 加速
    long long n, s;// 坑点 1：开 long long
    cin >> n >> s;
    if (n < s){// 坑点 2：特判
        cout <<"-1\n";
        return 0;
    } else if (n == s){// 坑点 2：特判
        cout << n + 1 << "\n";
        return 0;
    } else {
        for (long long i = 2; i * i <= n; i++){// 坑点 1：开 long long
            if (f(i, n) == s){
                cout << i << "\n";
                return 0;// 坑点 3：退出程序
            }
        }
        for (long long i = (long long)(sqrt(n)); i >= 1; i--){// 坑点 1：开 long long
            if ((n - s) % i != 0){// 坑点 4：特判
                continue;
            }
            long long b = (n - s) / i + 1;
            if (f(b, n) == s){// 坑点 5：验证 f(b,n)=s
                cout << b << "\n";
                return 0;// 坑点 3：退出程序
            }
        }
    }
    cout << "-1\n";
    return 0;
}
```

---

## 作者：henry_y (赞：2)

[推一下博客](http://www.cnblogs.com/henry-1202)

## 总结：数学题

被数学题虐爆...研究了好久的题解才明白这题...

题意：给一个函数$f(b,n)$可以求出$n$在$b$进制下各位数的和，设$f(b,n)=s$，现在已知$n,s$，求$b$

我们可以分成两种情况来讨论

当$b<=\sqrt{n}$时，我们可以直接枚举$b$，然后套用题目的公式来计算

当$b>\sqrt{n}$时，我们可以寻找一下规律：

设$n$在$b$进制下的高位为$p$低位为$q$（因为$b>\sqrt{n}$,所以这里的$n$在$b$进制下一定是两位数）

这时的$n=pb+q$ ， $s=p+q$

所以$n-s=(b-1)p$

即$$b=\frac{n-s}{p}+1$$

因为$b$是整数，所以枚举$n-s$的所有因数$p$就可以了，不过枚举之后要更新答案的时候记得再套一遍$f(b,n)$来检查一下，因为算出来的$b$可能会出现某些奇奇怪怪的东西（亲测...）

复杂度是$O(\sqrt{n})$的

```
#include <bits/stdc++.h>

using namespace std ;

#define inf 0x3f3f3f3f
#define ll long long

ll n , s ;

ll f( ll b , ll n ) {
	return n < b ? n : f( b , n / b ) + n % b ;
}

int main() {
	scanf( "%lld%lld" , &n , &s ) ;
	if( s > n ) return puts( "-1" ) , 0 ;
	if( s == n ) return printf( "%lld\n" , n + 1 ) , 0 ;
	ll m = sqrt( n ) + 1 ;
	for( ll i = 2 ; i <= m ; i ++ ) {
		if( f( i , n ) == s ) 
			return printf( "%lld" , i ) , 0 ;
	}
	ll ans = 1e11 ; n -= s ;
	for( ll i = 1 ; i * i <= n ; i ++ ) {
		if( n % i == 0 ) {
			ll b = n / i + 1;
			if( f ( b , n + s ) ==  s ) ans = min ( ans , b ) ;
		}
	}
	printf( "%lld\n" , ans != 1e11 ? ans : -1 ) ;
	return 0 ;
} 
```

---

## 作者：_Eriri_ (赞：1)

我居然做出了这道题！！

但是我是突然抖机灵想到了根号分治。那就写一下这个东西。

即对于数 $n$ ，它在 $b\ (\sqrt n < b \le n)$ 进制下有且仅有 $2$ 位。其数位和为 $\lfloor\frac{n}{b}\rfloor+n\%b$ 。

于是这个题就是枚举 $b \le \sqrt n$ ，然后 $b>\sqrt n$ 解一个方程就行。

这个方程大概是：
$$
\begin{cases}
b \cdot d+q=n
\\ d+q=s
\\ q < b
\\ \sqrt n < b \le n
\end{cases}
$$

发现 $(b-1) \mid (n-s)$ 。所以枚举 $n-s$ 的因数然后看对应 $b$ 是否能让方程有解就行。

只有一个边界， $s=n$  时 $b$ 可能是 $n+1$ 。

时间复杂度 $O(\sqrt n )$ 。

---

## 作者：NY_An18623091997 (赞：1)

## 题目大意
$n$ 在 $b$ 进制中的数位和为 $s$，求正整数 $b$ 的最小值（$1 < b$）。  
## 解题思路
分情况讨论：
### $n < s$ 时：
$n$ 的数位和肯定小于 $s$，无解，输出 $-1$。 
### $n = s$ 时：
$n$ 在 $b$ 进制中必为一位数，则 $b > n$，$b$ 的最小值为 $n+1$。  
### $n > s$ 时：
我们可以想到暴力枚举，但是 $1 \le n \le 10^{11}$，暴力显然会超时。  
然后我们可以分 $b < \sqrt{n}$ 和 $b \ge \sqrt{n}$ 两种情况讨论。
#### $b < \sqrt{n}$ 时：
直接在 $2$ 到 $\sqrt{n}$ 之间枚举 $b$ 即可。
#### $b \ge \sqrt{n}$ 时：
显然 $n$ 在 $b$ 进制中为两位数。那么我们不妨设 $n$ 为 $\overline{xy}$，这时候我们可以把 $n$ 表示为 $bx+y$，$s$ 表示为 $x+y$。则 $n-s = (b-1)x$ ，进一步推出 $b = \displaystyle \frac{n-s}{x}+1$。  
然后我们就开始枚举 $x$，当 $\displaystyle \frac{n-s}{x}$ 为整数且 $f( \frac{n-s}{x}+1,n)=s$ 时，输出 $\displaystyle \frac{n-s}{x}+1$。
## AC代码
记得开 **long long**
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,s,ans,stn;
ll f(ll b,ll n){
	if(n<b)		return n;
	return f(b,n/b)+n%b;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>s; 
	
	//特判 
	if(n<s)		cout<<"-1",exit(0);
	if(n==s)	cout<<n+1,exit(0);
	
	stn=sqrt(n);
	for(ll i=2;i<=stn;i++){//b<sqrt(n)
		if(f(i,n)==s)	cout<<i,exit(0);
	}
	for(ll i=stn;i>=1;i--){//n在b进制中是两位数时 
		if((n-s)%i==0&&f((n-s)/i+1,n)==s){
			ans=(n-s)/i+1;
			break;
		}
	}
	
	if(ans)	cout<<ans,exit(0);
	cout<<"-1";
	return 0;
}
```
**[AC记录](https://www.luogu.com.cn/record/191913985)**

---

## 作者：cike_bilibili (赞：0)

自己做出来了，感觉 AT 评分虚高。

看数据范围和这个神秘的下取整容易想到根号分治，不难发现一次计算 $f(b,n)$ 的值时间复杂度是 $O(\log n)$ 的，所以小于等于 $\sqrt n$ 的 $b$ 直接暴力计算即可，时间复杂度 $O(\sqrt n \log n)$。

继续想大于 $\sqrt n$ 怎么做，我们发现 $f$ 迭代一次就到底了，列出式子得 $f(b,n)=(n-b \lfloor \frac{n}{b} \rfloor) + (\lfloor \frac{n}{b}  \rfloor)$，联立 $f(b,n) = s$ 可得方程：

$$ (n-b \lfloor \frac{n}{b} \rfloor) + (\lfloor \frac{n}{b}  \rfloor) = s $$

移项得：

$$ n - s = (b-1) \lfloor \frac{n}{b} \rfloor $$

整理解得：

$$b = \frac{n-s}{\lfloor \frac{n}{b} \rfloor} + 1$$

对于下面这一坨 $\lfloor \frac{n}{b} \rfloor$，不难想到用整除分块，这样解出来判断 $b$ 是否在枚举的这个块内即可，时间复杂度 $O(\sqrt n)$。

综上，总时间复杂度为 $O(\sqrt n \log n)$。

---

## 作者：easy42 (赞：0)

是一道数学加上分类讨论的题目。

### 题意
$n$ 在 $b$ 进制中的数位和为 $s$，求正整数 $b$ 的最小值。
### 分析
分类讨论。

1. 若 $n<s$，不满足条件，输出 $-1$。
2. 若 $n=s$，那么 $b>n$，输出最小的比 $n$ 大的数，也就是 $n+1$。
3. $n>s$ 时，如果 $b<\sqrt{n}$，直接暴力枚举，不会超时。如果 $b\ge\sqrt{n}$，需要进行一些推导。此时 $n$ 在 $m$ 进制下只有两位，所以设他的第一位为 $x$，第二位为 $y$，有如下两个式子：
- $n=mx+y$
- $s=x+y$

两式相减得 $n-s=(m-1)x$。

所以 $x$ 和 $m-1$ 均为 $n-s$ 的因数，所以枚举 $x$，看他是否是 $n-s$ 的因数，如果是，进一步判断它是否满足题意。

此时，需要枚举的总数缩减到了 $\sqrt{n}$ 级别，所以总时间复杂度是 $O(\sqrt{n})$ 的，可以通过。
### 代码
```cpp
#include <iostream>
#include <cmath>

#define int long long

// 计算函数
int f(int b, int n) {
    if (n < b) {
        return n;
    }
    return f(b, n / b) + n % b;
}

signed main() {
    using namespace std;
    // 输入的数字和目标值
    int inputNumber, targetValue;
    cin >> inputNumber >> targetValue;
    if (inputNumber < targetValue) {
        cout << -1 << endl;
        return 0;
    }
    if (targetValue == inputNumber) {
        cout << inputNumber + 1 << endl;
        return 0;
    }
    int sqrtValue = ceil(sqrt(inputNumber));
    for (int i = 2; i <= sqrtValue; ++i) {
        if (f(i, inputNumber) == targetValue) {
            cout << i << endl;
            return 0;
        }
    }
    int answer = -1;
    for (int i = 1; i <= sqrtValue; ++i) {
        if ((inputNumber - targetValue) % i == 0 && f((inputNumber - targetValue) / i + 1, inputNumber) == targetValue) {
            answer = (inputNumber - targetValue) / i + 1;
        }
    }
    cout << answer << endl;
}
```

---

## 作者：Zyh_AKer (赞：0)

## 题解 ABC044D 桁和
### 题目链接
 [洛谷](https://www.luogu.com.cn/problem/AT_arc060_b)   
 [AtCoder](https://atcoder.jp/contests/abc044/tasks/arc060_b)
### 题意简述
给定一个十进制下的数 $n$ 和这个数在 $b$ 进制下的数位和$s$，求最小的 $b$。
### 算法标签
根号分治。
### 题解
这类根号分治的题一般是在 $\sqrt n$ 的范围内暴力，剩下的部分利用另一个值 $b$ 的特殊性质解决。

根号分治模板题：[小红帽的回文数](https://www.luogu.com.cn/problem/P2425)。

本题我们可以先判特殊情况：

- $n < s$，无解，输出`-1`。
- $n = s$，此时数位和等于这个数本身，显然 $b = n + 1$。

如果都不满足，开始根号分治：

- $b < \sqrt n$ 直接暴力枚举即可
- $b \ge \sqrt n$ 则 $(n)_{b}$ 一定是一个两位数，我们不妨设第一位为 $x$，第二位为 $y$，可以得到：  
$\begin{cases}n = xb + y\\ s = x + y\end{cases}$  
将两式相减可得 $n - s = xb + y - (x + y)$，化简可得$n - s = x(b-1)$，则 $b = \frac{n-s}{x} + 1$。枚举 $x$ 即可。
### 时间复杂度
暴力枚举部分的时间复杂度是 $O(\sqrt n)$，枚举 $x$ 的时间复杂度也是 $O(\sqrt n)$，所以总时间复杂度是 $O(\sqrt n)$。
### Code
```cpp
# include <bits/stdc++.h>
# define int long long
using namespace std;
int n, s;
bool check(int b, int val)
{
    int res = 0;
    while (val)
    {
        res += val % b;
        val /= b;
    }
    return res == s;
}
signed main()
{
    cin >> n >> s;
    if (n < s)
    {
        cout << -1;
        return 0;
    }
    if (s == n)
    {
        cout << n + 1;
        return 0;
    }
    for (int i = 2; i * i <= n; i ++)
    {
        if (check(i, n))
        {
            cout << i << '\n';
            return 0;
        }
    }
    int ans = -1;
    for (int i = 1; i * i <= n; i ++)
    {
        if ((n - s) % i == 0 && check((n - s) / i + 1, n))
        {
            ans = (n - s) / i + 1;
        }
    }
    cout << ans;
    return 0;
}
```

---

## 作者：__qkj__ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc060_b)
## 解题思路
这是一道数学题。

当 $n<m$ 时，无解，输出 $-1$。

当 $n=m$ 时，直接输出 $n+1$。

否则，直接模拟。

先从 $2$ 到 $\lceil\sqrt{n}\rceil$ 循环，按题意模拟，如果结果恰好等于 $m$，直接输出 $i$。

如果还是不行，因为 $n$ 的 $b$ 进制中是两位数，设第一位是 $x$，第二位是 $y$，那么：
$$
\begin{cases}x \times b+y=n\\x+y=m\end{cases}
$$
变一下，可得：
$$
b=\dfrac{n-m}{x}+1
$$
那就遍历 $\lceil\sqrt{n}\rceil$ 到 $1$，如果 $(n-m) \bmod i=0$ 且 $dg(\dfrac{n-m}{i}+1,n)=m$，那就直接输出 $\dfrac{n-m}{i}+1$。

如果都不行，输出 $-1$。

时间复杂度：$O(\sqrt{n})$。
## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int dg(int x,int y)
{
	if(y<x)return y;
	return dg(x,y/x)+y%x;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,m;
	cin>>n>>m;
	if(n<m)cout<<-1;
	else if(n==m)cout<<n+1;
	else
	{
		int x=sqrt(n);
		if(sqrt(n)!=(int)sqrt(n))x++;
		for(int i=2;i<=x;i++)
			if(dg(i,n)==m)
			{
				cout<<i;
				return 0;
			}
		for(int i=x;i>=1;i--)
			if((n-m)%i==0&&dg((n-m)/i+1,n)==m)
			{
				cout<<(n-m)/i+1;
				return 0;
			}
		cout<<-1;
	}
	return 0;
}
```

---

## 作者：wuzijinmlily (赞：0)

年代久远的题……

# 题意

给你两个数 $N$ 和 $S$，通过一个 $f$ 函数求 $B$ 的值，$f$ 的定义详见题目，如果 $B$ 没有符合题意的值，就输出 `-1` 。

# 思路

第一眼小模拟，想枚举来求答案，然后就看到了这个惊人的数据 $1\le n \le 10^{11}$，如果要枚举的话肯定要爆炸的，所以这道题绝对是一道思维题。分三种情况讨论，$N=S$，$N<S$ 和 $N>S$。如果 $N<S$，显然不符合题意，直接 `-1`，$N=S$ 说明 $B>N$，最小为 $N+1$，如果 $N>S$ 就进入 $f$ 函数，详细代码如下。

# 代码

```CPP
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,s;
signed main()
{
	scanf("%lld %lld",&n,&s);
	if(s==n)
	{
		printf("%lld\n",n+1);
		return 0;
	}
	for(int i=2;i*i<=n;i++)//i*i与sqrt(i)是一样的，但是时间复杂度能优化 
	{
		int sum=0,num=1;
		while(num<=n)
		{
			sum+=(n/num)%i;
			num*=i;
		}
		if(sum==s)
		{
			printf("%lld",i);
			return 0;
		}
	}
	int ans=-1;//初始-1可以在少一个判断 
	for(int i=1;i*i<=n;i++)//i*i与上面同理 
	{
		int b=((n-s)/i)+1;
		if(b<sqrt(n))
		{
			continue;
		}
		int sum=0,num=1;
		while(num<=n)
		{
			sum+=(n/num)%b;
			num*=b;
		}
		if(sum==s)
		{
			ans=b;
		}
	}
	printf("%lld",ans);
	return 0;
}
```



---

## 作者：_edge_ (赞：0)

挺不错的根号分治，首先看到这种题，要先很熟练的写出暴力程序。

然后对于 $1$ 到 $10^6$ 中的数进行遍历，然后暴力查询它是否合法，每次查询复杂度是不超过 $O(\log n)$，所以是不会 TLE 的。

然后我们就可以默认它的 $b$ 是一定大于 $10^6$。

然后我们再考虑一下原来的式子，发现它不会除以两次，它除了一次就会变成 $0$。

因此我们所需要找到的即为 $\lfloor{\dfrac{n}{b}}\rfloor+n \bmod b =s$ 。

小小的对他进行拆柿子操作，也就是变成了 $\lfloor{\dfrac{n}{b}}\rfloor \times (b-1) = n-s$。

然后会发现 $\lfloor{\dfrac{n}{b}}\rfloor$ 这东西是可以整除分块的，它的取值不超过 $\sqrt n$，然后需要注意的是，我们求出答案之后需要带入验证，同时要特判 $n=s$ 的情况，这种情况下需要输出 $n+1$。

```cpp
#include <iostream>
#include <cstdio>
#define int long long 
using namespace std;
const int INF=1e5+5;
int n,s,sum;
int f(int x,int y) {
//	cout<<x<<" "<<y<<" weirji\n";
	if (x<y) return x;
	else return f(x/y,y)+x%y;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>s;
	if (n==s) {
		cout<<n+1<<"\n";
		return 0;
	}
	for (int b=2;b<=1e6;b++) {
		sum=f(n,b);
		if (sum==s) {
			cout<<b<<"\n";
			return 0;
		}
	}
	int T=n-s;
	for (int l=1;l<=n;l=n/(n/l)+1) {
		int r=n/(n/l),tt=n/l;
		if (T%tt==0) {
			int b=T/tt+1;
//			cout<<b<<" yiw\n";
			if (b==1) continue;
			if (l<=b && b<=r && f(n,b)==s) {
				cout<<b<<"\n";
				return 0;
			}
		}
	}
	cout<<"-1\n";
	return 0;
}
```


---

## 作者：Purslane (赞：0)

## Solution

数学题 . 

我们不妨设 $n=a_0+a_1b+a_2b^2+a_3b^3+ \cdots$ , 则 $s=a_0+a_1+a_2+\cdots$ .

先考虑特殊情况 :

- $n = s$ . $b=n+1$ .

- $n<s$ . 无解 . 

然后 , 我们用 $n$ 减去 $s$ 得到 :

$$n-s=a_1(b-1)+a_2(b^2-1)+a_3(b^3-1)+\cdots$$

我们很容易知道 , $b^n-1=(b-1)(b^{n-1}+b^{n-2}+\cdots+1)$ . 所以说 , 右式可以提出 $(b-1)$ . 那么很显然 , $(b-1)|(n-s)$ . 那么 , $b$ 可能取值的数量就缩成了 $\sqrt{n}$ 的量级 . 然后直接套用函数 , 逐个判断可能的 $b$ 就可以了 . 

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
int n,s;
int f(int b,int n) {
	if(n<b) return n;
	return f(b,n/b)+(n%b);
}
int check(int b) {
	if(f(b,n)==s) return 1;
	return 0;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>s;
	if(n<s) {cout<<-1;return 0;}
	if(n==s) {cout<<n+1;return 0;}
	int d=n-s,ans=LONG_LONG_MAX;
	ffor(i,1,sqrt(d)) if(d%i==0) {
		if(check(i+1)) ans=min(ans,i+1);
		if(check(d/i+1)) ans=min(ans,d/i+1);
	}
	if(ans==LONG_LONG_MAX) {cout<<-1;return 0;}
	cout<<ans;
	return 0;
}
```

---

## 作者：C6H14 (赞：0)

## 一点废话

[题目传送门](https://www.luogu.com.cn/problem/AT2038)

[My blog](https://www.luogu.com.cn/blog/128433/#)

分块+数学专题看到这题，感觉就是根号讨论，结果讲了一个更数学的方法……~~wtcl~~

## 思路

注意到 $(b-1) \mid (n-s)$，证明可以参考十进制数字和与模 $9$ 关系的证明。

那么我们枚举 $b-1$ ，每次判断一下即可，时间复杂度 $O(\sqrt n \log n)$。

注意特判下 $n=s$ 的情况。


## 代码

```cpp
ll s,n,b,m,ans;
inline ll digit(ll n,ll b)
{
	if (b<=1)
		return 0;
	ll cnt=0;
	while (n)
	{
		cnt+=n%b;
		n/=b;
	}
	return cnt;
}
int main()
{
	n=read(),s=read();
	if (n==s)
	{
		write(n+1);
		return 0;
	}
	for (ll i=1;i*i<=n-s;++i)
	{
		if ((n-s)%i)
			continue;
		if (digit(n,i+1)==s)
		{
			write(i+1);
			return 0;
		}
		if (digit(n,(n-s)/i+1)==s)
			ans=(n-s)/i+1;
	}
	if (ans)
	{
		write(ans);
		return 0;
	}
	if (digit(n,n-s+1)==s)
	{
		write(n-s+1);
		return 0;
	}
	write(-1);
	return 0;
}
```


---

## 作者：dread (赞：0)

- 先考虑一些特殊情况比如$n > s$与$n=s$时
- 当$n > s$时，可以想象这样是无解的
- 当$n = s$时，$b = n + 1$
- 然后呢，先考虑朴素做法：枚举$n$以内所有数，作为$b$。
- 当然$1\leq n \leq 10^{11}$，朴素做法肯定会TLE。
- 当然看这个范围，如果以$O(\sqrt n)$的算法肯定可过。
- 我们就想想以$\sqrt n$为分界线
- 小于$\sqrt n$就可以直接枚举$b$的值
- 而大于$\sqrt n$时又会怎么样呢
- 可设整数$a, t$使得$a * b + t = n$与$a+t=s$
- 那么我们有$(b-1)*a=n-s$
- 那么答案就在$n-s$的质因数中了。
- 枚举质因数，这道题就变成$O(\sqrt n)$了。

## code:


```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;

ll n, s, ans = -1;

inline ll read() {
	ll s = 0, f = 1;
	char ch;
	for(; ch < '0' || ch > '9'; ch = getchar())	if(ch == '-')	f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar())	s = (s << 1) + (s << 3) + ch - '0';
	return s * f;
}

inline ll f(ll b, ll n) {
	ll ans = 0;
	while(n)	ans += n % b, n /= b;
	return ans;
}

int main() {
	n = read(), s = read();
	ll u = sqrt(n) + 1;
	for(ll i = 2; i <= u; ++i)	if(f(i, n) == s) { ans = i; break; }
	if(n == s) { ans = n + 1; }
	if(ans == -1 && n > s) {
		ll c = n - s;
		u = c / (u - 1) + 1;
		for(ll i = u; i >= 1; --i) {
			ll b = c / i + 1;
			if(!(c % i) && s >= i && (s - i) < b && i < b) {
				ans = b;
				break;
			}
		}
	}
	printf("%lld\n", ans);
	return 0;
}

```

~~又是一道结论题~~

---

