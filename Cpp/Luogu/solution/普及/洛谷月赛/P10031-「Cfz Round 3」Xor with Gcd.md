# 「Cfz Round 3」Xor with Gcd

## 题目背景

她是午夜潜入海风漂流的沙砾

极光与她一齐许下明日愿景

飞身电波铺满天穹而海仍平静

“愿世界都繁花似锦”

## 题目描述

给定一个整数 $n$。

你需要求出 $\bigoplus\limits_{i=1}^{n} \gcd(i,n)$，即 $\gcd(1,n) \oplus \gcd(2,n) \oplus \cdots \oplus \gcd(n,n)$ 的值。其中 $\gcd(a,b)$ 表示 $a$ 和 $b$ 的**最大公约数**，$\bigoplus$ 表示**按位异或**，即 C++ 中的 `^`。

## 说明/提示

#### 「样例解释 #1」

对于第 $1$ 组数据，$\bigoplus\limits_{i=1}^{2} \gcd(i,2)=\gcd(1,2)\oplus\gcd(2,2)=1\oplus2=3$。

对于第 $2$ 组数据，$\bigoplus\limits_{i=1}^{3} \gcd(i,3)=\gcd(1,3)\oplus\gcd(2,3)\oplus\gcd(3,3)=1\oplus1\oplus3=3$。

#### 「数据范围」

对于所有数据，$1 \le T \le 100$，$1 \le n \le 10^{18}$。

**只有你通过本题的所有测试点，你才能获得本题的分数。**

## 样例 #1

### 输入

```
3
2
3
6
```

### 输出

```
3
3
5```

# 题解

## 作者：T_TLucas_Yin (赞：17)

**题目大意**：给定 $n$ ，求出 $n$ 与 $1$ 到 $n$ 中所有数的最大公约数的异或和。

看到数据范围，很容易发现这是个典型的结论题。所以直接开始找规律。

对于求最大公约数，有一种方法叫做**更相减损术**。其中用到了这样一条规律：

$$\gcd(a,b)=\gcd(b-a,b)$$

改一下字母就可得

$$\gcd(i,n)=\gcd(n-i,n)$$

我们又知道，异或和运算满足 $a \oplus b \oplus c = a \oplus c \oplus b$ 和 $a \oplus a = 0$。

也就是说，对于所有 $1\le i < n$，我们可以把每一对 $\gcd(i,n)$ 和 $\gcd(n-i,n)$ 放到一起，这样，它们的异或和就会抵消为 $0$。

接下来看整个式子。若 $n$ 为奇数，则两两抵消后，会剩下 $\gcd(n,n)$ ，也就是 $n$ 。由于除此之外整个式子都为 $0$，所以最终的结果就是 $n$。

若 $n$ 为偶数，则两两抵消后，会剩下 $\gcd(\frac n 2,n)$ 和 $\gcd(n,n)$ 两项，它们的值刚好分别为 $\frac n 2$ 和 $n$ ，因此最终的结果就是它们的异或和。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n;
int main(){
    cin>>t;
    while(t--){
        cin>>n;
        if(n&1) printf("%lld\n",n);// n&1就是n%2==1
        else printf("%lld\n",(n/2)^n);
    }
    return 0;
}
```

---

## 作者：Ahws_rwhy (赞：10)

比赛交了好多发才过。。。。

思路：

其实这题一看数据 $n\le10^{18}$，就知道这题的正解应应该是 $O(1)$ 的。

一看到这题毫无思路，于是打了暴力。

代码如下：

```
#include <iostream>
#include <cmath>
#include <bits/stdc++.h>
#define int long long
int ans = 0 ;
int ans1=0;
int GCD(int a,int b){
    while(b^=a^=b^=a%=b);
    return a;
}
main() {    int T;
    std::cin >> T;
    while (T--) {
    	ans=0,ans1=0;
        int n;
        std::cin >> n;
        for(int i = 1; i <= n; i++) {
        	ans^=GCD(i,n);
//        	std::cout << ans <<" ";
        	ans1^=ans;
		}
            std::cout << ans << std::endl;
      }
//	  else {
//            std::cout << 1 << std::endl;
//        }

    return 0;
}
```
然后我将 $n=1\sim 1000$ 的数据全都输出，结果发现了一些规律： $n$ 为奇数，答案就是它本身（十分容易证明，前 $n-1$ 个数两两配对（欧里几得算法），结果是 $0⨁\gcd(n,n)=n$）；$n$ 为偶数时，只有 $n/2$ 的值是有效的，其它都会抵消。

所以 $n$ 为偶数时输出 $\gcd(n/2,n)⨁n$ 即可。

```
#include <iostream>
using namespace std;
#define int long long
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}
int calculate_xor(int n) {
    if (n == 1) {
        return 1;
    } else if (n % 2 == 0) {
        return gcd(n / 2,n) ^ n;
    } else {
        return n;
    }
}
int main() {
	int _;
	cin>>_;
	while(_ --) {
    int n;
    cin >> n;
    int result = calculate_xor(n);
    cout << result  << endl;
}
    return 0;
}
```

---

## 作者：Phartial (赞：8)

oeis 做法（笔者赛时做法）：

把 $n\le 7$ 的表打出来丢进 oeis，可以找到 [A142149](https://oeis.org/A142149)，在 FORMULA 一栏中可以找到 [A048724](https://oeis.org/A048724) 和 [A005408](https://oeis.org/A005408)，于是你就做完了。

正经做法：

考虑更相减损术：

> 对于 $\gcd(a,b)$（$a\ge b$），有 $\gcd(a,b)=\gcd(a,a-b)$。

于是我们有 $\gcd(i,n)=\gcd(n-i,n)$。于是分类讨论：

当 $n$ 是奇数时：有

$$
\begin{aligned}
\bigoplus\limits_{i=1}^n\gcd(i,n)
&=\left(\bigoplus\limits_{i=1}^{\lfloor\frac{n}{2}\rfloor}\gcd(i,n)\oplus\gcd(n-i,n)\right)\oplus\gcd(n,n)\\
&=\left(\bigoplus\limits_{i=1}^{\lfloor\frac{n}{2}\rfloor}\gcd(i,n)\oplus\gcd(i,n)\right)\oplus\gcd(n,n)\\
&=\gcd(n,n)\\
&=n\\
\end{aligned}
$$

当 $n$ 时偶数时：有

$$
\begin{aligned}
\bigoplus\limits_{i=1}^n\gcd(i,n)
&=\left(\bigoplus\limits_{i=1}^{\frac{n}{2}-1}\gcd(i,n)\oplus\gcd(n-i,n)\right)\oplus\gcd(\frac{n}{2},n)\oplus\gcd(n,n)\\
&=\left(\bigoplus\limits_{i=1}^{\frac{n}{2}-1}\gcd(i,n)\oplus\gcd(i,n)\right)\oplus\gcd(\frac{n}{2},n)\oplus\gcd(n,n)\\
&=\gcd(\frac{n}{2},n)\oplus\gcd(n,n)\\
&=\frac{n}{2}\oplus n\\
\end{aligned}
$$

```cpp
#include <iostream>

using namespace std;
using LL = long long;

int tt;
LL n;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  for (cin >> tt; tt--; ) {
    cin >> n;
    cout << ((n & 1) ? n : (n ^ n / 2)) << '\n';
  }
  return 0;
}
```


---

## 作者：RyanLi (赞：6)

传送门：[P10031 「Cfz Round 3」Xor with Gcd](https://www.luogu.com.cn/problem/P10031)

更佳的阅读体验：[洛谷 P10031 题解](https://blog.ryanli.top/index.php/archives/122/)

---

**题意**：给定正整数 $n$，求出 $\bigoplus\limits_{i=1}^{n} \gcd(i,n)$。

根据题目要求，我们需要求两个数的最大公约数，可以使用**欧几里得算法**（辗转相除法）。

设我们需要求出最大公约数的两个数为 $a,b$ 且 $a > b$，用 $\gcd(a, b)$ 表示 $a$ 与 $b$ 的最大公约数，则有：
$$
\gcd(a, b) = \gcd(b, a \bmod b)
$$
证明过程如下：

- 设 $a = kb + r\ (k, r \in N^*)$，$d$ 是 $a,b$ 的公约数。

- 可得 $r = a - kb$，等式两边同时除以 $d$ 得 $\frac{r}{d} = \frac{a}{d} - \frac{kb}{d}$。
- 因为 $d$ 是 $a,b$ 的公约数，则 $a$ 和 $b$ 都可以被 $d$ 整除，等式右边为整数，所以等式左边 $\frac{r}{d}$ 也是整数，因此 $r$ 也可以被 $d$ 整除。

- 因此，$d$ 也是 $b,a \bmod b$ 的公约数，得证。

可以推出：
$$
\gcd(i, n) = \gcd(n \bmod i, n) = \gcd((n - i) \bmod i, n)
$$
我们知道，异或有如下运算法则：

- **归零律**：$a \oplus a = 0$。
- **恒等律**：$a \oplus 0 = a$。

因此，将这些运算法则代入上面推导出来的等式，可以发现：

- 如果 $n$ 是一个**奇数**，对于 $i < n$，$\gcd(i, n)$ 的项全部被消去了，答案等于 $n$ 本身。
- 如果 $n$ 是一个**偶数**，对于 $i < n$，除了 $i = \frac{n}{2}$ 的情况，剩下的 $\gcd(i, n)$ 的项全部被消去了，答案等于 $n \oplus \frac{n}{2}$。

---

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int t;
ll n;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    for (cin >> t; t; --t) {
        cin >> n;
        if (n & 1) cout << n << '\n';
        else cout << (n >> 1 ^ n) << '\n';
    } return 0;
}
```



---

## 作者：gaojizhe05 (赞：4)

# 题目分析
其实本题就是**找规律**，首先我们用辗转相除法 $\gcd(a,b)=\gcd(a-b,b)$，可以得到 $x\oplus x=0$。但直接找规律比较困难。我们可以举例分析：
$\bigoplus\limits_{i=1}^{1}\gcd(i,1)=\gcd(1,1)=1$

$\bigoplus\limits_{i=1}^{2}\gcd(i,2)=\gcd(1,2)\oplus\gcd(2,2)=1\oplus2$

$\bigoplus\limits_{i=1}^{3}\gcd(i,3)=\gcd(1,3)\oplus\gcd(2,3)\oplus\gcd(3,3)=1\oplus1\oplus3=3$

$\bigoplus\limits_{i=1}^{4}\gcd(i,4)=\gcd(1,4)\oplus\gcd(2,4)\oplus\gcd(3,4)\oplus\gcd(4,4)=1\oplus2\oplus1\oplus4=2\oplus4$

$\bigoplus\limits_{i=1}^{5}\gcd(i,5)=\gcd(1,5)\oplus\gcd(2,5)\oplus\gcd(3,5)\oplus\gcd(4,5)=\oplus\gcd(5,5)=1\oplus1\oplus1\oplus1\oplus5=5$

$\bigoplus\limits_{i=1}^{6}\gcd(i,6)=\gcd(1,6)\oplus\gcd(2,6)\oplus\gcd(3,6)\oplus\gcd(4,6)\oplus\gcd(5,6)\oplus\gcd(6,6)=1\oplus2\oplus3\oplus2\oplus1\oplus6=3\oplus6$

我们可以发现
*  当 $n$ 时一个奇数时，前面 $n-1$ 个数相互匹配，逐对抵消；
*  当 $n$ 是一个偶数时，两边逐一抵消，最终只剩下了 $\frac{n}{2}$ 和 $n$，化简得到 $(x/2) \oplus x$。

总结：
*  当 $n$ 是一个奇数时，最终结果为 $n$。
*  当 $n$ 是一个偶数时，最终结果为 $(x/2) \oplus x$。

# 代码
```cpp
#include <bits/stdc++.h>//万能头文件
using namespace std;
int T;//数据组数
long long n,ans;
void Init(){
	cin>>n;//读入
	return;
} 
void Work(){
	if(n%2==0) ans=(n/2)^n;//如果n是偶数
	else ans=n;//如果n是奇数
	cout<<ans<<endl;//输出
	return;
}
int main(){
	cin>>T;
	while(T--){
	    Init();//读入
	    Work();//运行
	}
	return 0;
}
``````
$LaTeX$ 使用不易，求审核给过！！！ 

---

## 作者：Coffee_zzz (赞：4)

我们由用来求最大公约数的欧几里得算法可以得到一个性质：$\gcd(i,n)=\gcd(n-i,n)\ (1 \le i \lt n)$。

那我们再做一个变形就能得到 $\gcd(i,n)\oplus\gcd(n-i,n)=0\ (1 \le i \lt n)$。

于是我们可以分类讨论一下：

- 若 $n$ 为奇数，则 $\bigoplus\limits_{i=1}^{n-1} \gcd(i,n)$ 都被消掉了，所以 $\bigoplus\limits_{i=1}^{n} \gcd(i,n)=\gcd(n,n)=n$。

- 若 $n$ 为偶数，我们设 $x=\dfrac n 2$，则除了 $\gcd(x,n)$ 和 $\gcd(n,n)$ 都被消掉了，所以 $\bigoplus\limits_{i=1}^{n} \gcd(i,n)=\gcd(x,n)\oplus \gcd(n,n)=x\oplus n$。

直接输出即可。

```c++
#include <bits/stdc++.h>

using namespace std;
void solve(){
	long long n;
	cin>>n;
	cout<<(n&1?n:n^(n/2))<<'\n';
}
signed main(){
	int T;
	cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：xz001 (赞：2)

- ~~打表找规律即可~~
- 众所周知 $\gcd(x,y)=\gcd(x-y,y)$，因此我们会发现若 $n$ 为奇数，那么前 $n-1$ 个数经过以上变换后两两相等，全异或没了，只剩 $\gcd(n,n)$ 了，若 $n$ 为偶数，则前面的 $n-1$ 个数字经过变换后只剩中间那个数 $\gcd(n/2,n)$ 和 $\gcd(n,n)$ 了。
- 代码如下：

```cpp

#include <bits/stdc++.h>

using namespace std;

#define re register
#define int long long 
#define fi first
#define se second
#define swap(a, b) a ^= b, b ^= a, a ^= b
#define pb push_back
#define all(x) x.begin(), x.end()
#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)
#define il inline
#define abs(x) ((x ^ (x >> 63)) - (x >> 63))
#define huk2 queue
#define is <int>
#define die q;

typedef pair<int, int> PII;

const int N = 2e6 + 10;
const int M = 2e6 + 10;
const int INF = 1e18, mod = 1e9 + 7;
const double eps = 1e-6;

int t, n;

signed main() {
	cin >> t;
	while (t -- ) {
		cin >> n;
		if (n & 1) cout << n << endl;
		else cout << (n ^ (n / 2)) << endl;
	}
    return 0;
}
```

---

## 作者：sugawara (赞：2)

# 前言

这是蒟蒻的第一篇题解！！望过！！

其实这可能是我今年打的比较好的一场比赛吧（蒟蒻）。

祝大家，新年快乐！

# 过程

## 模拟

根据题意可以写出模拟程序，分别是 $\gcd$ 和异或。很简单的可以得出第一步：

```cpp
#include<iostream>
using namespace std;
int t,n,y,h=1;
int gcd(int a,int b){
	if(!a) return b;
	return gcd(b%a,a);
}
int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0' && c<='9') x=x*10+c-'0',c=getchar();
	return x*f;
}
int main(){
	t=read();
	for(int i=1;i<=t;i++){
		n=read();
		for(int j=2;j<=n;j++){
			h=h^gcd(j,n);
		}
		printf("%d\n",h);
	}
	return 0;
}
```

以上程序赛时是万紫千红的，但是还是过了一个点。赛后提交就是爆零的，这就是错误程序。

## 进阶

接下来的过程就是可以帮助你 AC 的了！我们可以先观察数据范围，是 $10^{18}$ 的，所以在我想到的方法里面只能有 $O(1)$ 或者 $\operatorname{log}$ 级别的时间复杂度了。

#### 打表

一种试图找规律直接 $O(1)$ 求出答案的方法。

然后你就可以根据以上程序获取到了一个打表代码，稍作修改就可以得到如下结论：

```cpp
#include<iostream>
using namespace std;
int t,n,y,h;
int gcd(int a,int b){
	if(!a) return b;
	return gcd(b%a,a);
}
int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0' && c<='9') x=x*10+c-'0',c=getchar();
	return x*f;
}
int main(){
	t=100;
	for(int i=1;i<=t;i++){
		n=i;
		h=gcd(1,n); 
		for(int j=2;j<=n;j++){
			h=h^gcd(j,n);
		}
		printf("%d %d\n",i,h);
	}
	return 0;
}
```

然后我们就可以获得**表**这种用于找规律的好东西。

如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/f89g70lb.png)

我们看起来好像没什么规律，但是唯一能知道的就是好像就是 $3^n$ 这种数的结果是等于这个数本身，但是手贱的你可以去试一下把

```printf("%d %d\n",i,h);```


改成

```printf("%d  %d\n",i,h^n);```

你就会得到一张超级有实力的表：

![](https://cdn.luogu.com.cn/upload/image_hosting/eewi9ygt.png)

~~这回应该十个人十一个都看得出来规律了吧！~~

就是这个地方，右侧的是的出来的结果假如左侧的数是奇数的话，那么右侧的结果就是 $0$，这很容易让我们想到关于 $\gcd$ 的一个性质：

$\because\gcd(i,n)=\gcd(n,i-n)(i \geq n)$

$\therefore $
奇数：$\bigoplus\limits_{i=1}^{n} \gcd(i,n)=\gcd(n,n)=n$ 

偶数：$\bigoplus\limits_{i=1}^{n} \gcd(i,n)=\gcd(\frac{n}{2},n) \oplus \gcd(n,n) = \frac{n}{2} \oplus n$ 

得出代码：

```(n^((n>>1)*((n&1)^1)))```

最后别忘记开 long long 嗷！

AC 代码：

```cpp
#include<iostream>
using namespace std;
int t,y,h;
long long n;
long long read(){
	long long x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0' && c<='9') x=x*10+c-'0',c=getchar();
	return x*f;
}
int main(){
	t=read();
	for(int i=1;i<=t;i++){
		n=read();
		printf("%lld\n",(n^((n>>1)*((n&1)^1))));
	}
	return 0;
}
```

完结撒花！！

---

## 作者：CaiZi (赞：2)

## 「Cfz Round 3」Xor with Gcd 题解
#### [题目链接](https://www.luogu.com.cn/problem/P10031)
### 题意理解
题目描述很清楚了，求 $\bigoplus\limits_{i=1}^{n} \gcd(i,n)$。
### 题目分析
>性质一：异或操作具有结合律，即 $x\otimes y\otimes z=x\otimes (y\otimes z)$。

>性质二：因为两个相等的数二进制下每位均相同，因此，$x\otimes x=0$。

>性质三：根据更相减损法，$\gcd(x,y)=\gcd(x,x-y)=\gcd(x-y,y)$。

先设 $\bigoplus\limits_{i=1}^{n} \gcd(i,n)=x$。接下来分 $n$ 的奇偶讨论 $x$ 的值，并利用上述的 $3$ 个性质进行化简。

当 $n$ 为奇数时，根据性质一和性质三得：

$$x=(\bigoplus\limits_{i=1}^{n\div2-0.5} \gcd(i,n)\oplus\gcd(n-i,n))\oplus\gcd(n,n)$$

根据性质三化简得：

$$x=(\bigoplus\limits_{i=1}^{n\div2-0.5}\gcd(i,n)\oplus\gcd(i,n))\oplus\gcd(n,n)$$

根据性质一和性质二化简得：

$$x=0\oplus\gcd(n,n)=\gcd(n,n)$$

根据 $\gcd$ 的性质得：

$$x=n$$

而当 $n$ 为偶数时，根据性质一和性质三得：

$$x=(\bigoplus\limits_{i=1}^{n\div2-1} \gcd(i,n)\oplus\gcd(n-i,n))\oplus\gcd(n,n)\oplus \gcd(n\div 2,n)$$

根据性质三化简得：

$$x=(\bigoplus\limits_{i=1}^{n\div 2-1}\gcd(i,n)\oplus\gcd(i,n))\oplus\gcd(n,n)\oplus\gcd(n\div 2,n)$$

根据性质一和性质二化简得：

$$x=0\oplus\gcd(n,n)\oplus\gcd(n\div 2,n)$$

根据 $\gcd$ 的性质得：

$$x=n\div2\oplus n$$

综上所述，当 $n$ 为奇数时，答案为 $n$；当 $n$ 为偶数时，答案为 $n\div2\oplus n$。
### 代码展示
时间复杂度 $O(T)$，空间复杂度 $O(1)$。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>t;
	while(t--){
		cin>>n;
		cout<<(n&1?n:n/2^n)<<'\n';//n&1等同于n%2，判断奇偶用。
	}
	return 0;
}
```
#### [提交记录](https://www.luogu.com.cn/record/141613480)

---

## 作者：_O_v_O_ (赞：1)

首先 $\gcd(a,b)$ 因为更相减损所以可以转换成 $\gcd(a,b-a)$，所以 $\gcd(i,n)=\gcd(n-i,n)$。

又因为一个数异或自己答案为 $0$，所以 $\gcd(i,n)\oplus\gcd(n-i,n)=0$。

接下来分讨，推一下式子：

- $n\bmod 2=1$：因为除 $n$ 自己的 $i$ 都能一一配对，所以答案为 $n$。
- $n\bmod2=0$：因为只有 $1,2,3,\cdots n\div2-1$ 能和 $n\div 2+1,n\div2+2,n\div2+3\cdots n-1$ 配对，而 $n\div2$ 不能配对，所以答案为 $n\oplus(n\div2)$。

代码很短：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int T;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		if(n&1) cout<<n<<endl;
		else cout<<(n^(n/2))<<endl;
	}
	return 0;
}

```

upd：修改了一处笔误。

---

## 作者：lichenzhen (赞：1)

## 题目大意
求出 $\bigoplus\limits_{i=1}^{n} \gcd(i,n)$ 的值。
## 题目解法
前置知识：
1. 两个相同的数按位异或的结果是 $0$，即 $a \oplus a=0$；
2. 一个非 $0$ 的数按位异或 $0$ 的结果还是原来那个数，即 $0 \oplus a =a$；
3. 按位运算遵循交换律，即 $a \oplus b \oplus c=a \oplus (b \oplus c)$。

刚开始一看，想到了暴力。但是发现 $n \le 10^{18}$，我就知道这题目大概率是一个结论题。但是我没有思路，于是就用暴力打了一个表。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	for(int n=1;n<=1000;n++){
		int ans=0;
		for(int i=1;i<=n;i++) ans^=__gcd(i,n);
		cout<<n<<":"<<ans<<"\n";
	}
} 
```

之后就很容易发现，当 $n$ 为奇数时，结果就是 $n$。

这是为什么呢？这里用到了[欧几里得算法](https://baike.baidu.com/item/%E6%AC%A7%E5%87%A0%E9%87%8C%E5%BE%97%E7%AE%97%E6%B3%95)，证明过程我就不写了，详情可以自行查看。

结论就是：$\gcd(a,b) = \gcd(b-a,b)$，也就是 $\gcd(i,n) = \gcd(n-i,n)$。

因此，我们可以发现：
- 当 $n$ 为奇数时，由 $a \oplus a=0$ 可以得出，前 $n-1$ 项会互相抵消（第 $i$ 项和第 $n-i$ 项抵消），最后只剩下第 $n$ 项了，答案就是 $0 \oplus \gcd(n,n)$，由于 $0 \oplus a=a$ 以及 $\gcd(a,a)=a$ 我们可以得出答案就是 $n$；

- 当 $n$ 为偶数时，我们可以发现，前 $\dfrac{n}{2}-1$ 项和第 $\dfrac{n}{2}+1 \sim  n-1$ 项可以互相抵消，剩下的第 $\dfrac{n}{2}$ 项和第 $n$ 项按位异或就是答案了。

### 参考代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	int t,n;
	cin>>t ;
	while(t--){
		cin>>n;
		if(n%2!=0) cout<<n<<endl;
		else cout<<(n/2^n)<<endl;
	}
} 
```

2024年第一篇题解，祝大家新年快乐！

---

## 作者：Mortidesperatslav (赞：0)

求最大公约数，所以更相减损术。$\gcd(i,n)=\gcd(n-i,n)$。

这个时候我们发现了什么？$\gcd(i,n) \oplus \gcd(n-i,n)=0$。

那么显然当 $n$ 为奇数，答案为 $\gcd(n,n)=n$，否则为 $\gcd(\dfrac{n}{2},n)\oplus \gcd(n,n)=n \oplus \dfrac{n}{2}$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--){
	    long long n;
	    cin>>n;
	    cout<<(n^(n>>1)*((n&1)^1))<<"\n";
	}
}
```

这里讲讲位运算。

`n>>1` 等于 `n/2`。


`(n&1)^1` 等于 `n%2==0`。

所以这里用位运算代替掉了一个 `if` 语句，询问较多时可以节省大量时间！是一个优化技巧。

用位运算可以加速。

---

## 作者：Vct14 (赞：0)

由辗转相减法（欧几里得算法）可知 $\gcd(a,b)=\gcd(a-b,b)$，又 $a\oplus a=0$，那么 $\gcd(i,n)\oplus\gcd(n-i,n)=0$。

- 若 $n$ 为奇数，则前面 $n-1$ 个数两两配对，结果为 $0$。答案为 $0\oplus\gcd(n,n)=n$。
- 若 $n$ 为偶数，则前面还剩下正中间的 $\gcd(\dfrac{n}{2},n)$。答案为 $\gcd(\dfrac{n}{2},n)\oplus\gcd(n,n)=\dfrac{n}{2}\oplus n$。

```c++
#include <bits/stdc++.h>
using namespace std;

int main(){
    int T;
    cin>>T;
    while(T--){
    	long long n;cin>>n;
    	if(n%2) cout<<n;
    	else cout<<(n xor (n/2));
    	cout<<endl;
	}
    return 0;
}
```

---

## 作者：indream (赞：0)

## P10031 「Cfz Round 3」Xor with Gcd 题解
[P10031](https://www.luogu.com.cn/problem/P10031) | [AC](https://www.luogu.com.cn/record/141615239)
### 思路
[辗转相除法](https://baike.baidu.com/item/%E6%AC%A7%E5%87%A0%E9%87%8C%E5%BE%97%E7%AE%97%E6%B3%95)：
> $\gcd(i,n)=\gcd(n \bmod i,n)(i<n)$

于是把取模替换为减法，可得 $\gcd(i,n)=\gcd(n-i,i)(i \ge n / 2)$

于是这道题就解出来了。

由上式可得，$\gcd(i,n)\oplus\gcd(n-i,n)=0$。

这样一来大部分异或运算都消掉了，于是有：

$ans(n) = \begin{cases}
  (n/2) \oplus n & n \bmod 2=0\\
  n & n \bmod 2=1
\end{cases}$

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,ans;
int main(){
	cin>>t;
	while(t--){
	    cin>>n;
	    if(n%2==0)ans=n^(n/2);
	    else ans=n;
	    cout<<ans<<'\n';
	}
	return 0;
}
```

---

