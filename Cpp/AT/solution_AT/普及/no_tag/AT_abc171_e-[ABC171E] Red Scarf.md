# [ABC171E] Red Scarf

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc171/tasks/abc171_e

猫のすぬけくんが $ N\ (\textbf{偶数}) $ 匹います。各すぬけくんには $ 1,\ 2,\ \ldots,\ N $ の番号が振られています。

各すぬけくんは首に赤いスカーフを巻いており、スカーフにはそのすぬけくんが一番好きな非負整数が $ 1 $ つ書き込まれています。

すぬけくんたちは最近、整数の xor（排他的論理和）と呼ばれる演算を覚えました。

 xor とは $ n $ 個の非負整数 $ x_1,x_2,\ \ldots,\ x_n $ について、それらの xor、 $ x_1~\textrm{xor}~x_2~\textrm{xor}~\ldots~\textrm{xor}~x_n $ は以下のように定義されます。

- $ x_1~\textrm{xor}~x_2~\textrm{xor}~\ldots~\textrm{xor}~x_n $ を二進表記した際の $ 2^k(k\ \geq\ 0) $ の位の数は、$ x_1,x_2,\ \ldots,\ x_n $ のうち、二進表記した際の $ 2^k(k\ \geq\ 0) $ の位の数が $ 1 $ となるものの個数が奇数ならば $ 1 $、そうでなければ $ 0 $ となる。
 
 例えば、$ 3~\textrm{xor}~5\ =\ 6 $ となります。 早速この演算を使いたくなったすぬけくんたちは、自分以外のすぬけくんのスカーフに書かれた整数の xor を計算することにしました。

番号 $ i $ が振られたすぬけくんが計算した、自分以外のすぬけくんのスカーフに書かれた整数の xor が $ a_i $ であることが分かっています。 この情報を元に、各すぬけくんのスカーフに書かれた整数を特定してください。

## 说明/提示

### 制約

- 入力はすべて整数である
- $ 2\ \leq\ N\ \leq\ 200000 $
- $ N $ は$ \textbf{偶数} $
- $ 0\ \leq\ a_i\ \leq\ 10^9 $
- 与えられた情報と整合するようなスカーフ上の整数の組合せが存在する

### Sample Explanation 1

\- $ 5~\textrm{xor}~7~\textrm{xor}~22\ =\ 20 $ - $ 26~\textrm{xor}~7~\textrm{xor}~22\ =\ 11 $ - $ 26~\textrm{xor}~5~\textrm{xor}~22\ =\ 9 $ - $ 26~\textrm{xor}~5~\textrm{xor}~7\ =\ 24 $ より、この出力は与えられた情報と整合します。

## 样例 #1

### 输入

```
4
20 11 9 24```

### 输出

```
26 5 7 22```

# 题解

## 作者：shenbairui (赞：3)

### 题目分析

大家都知道，异或的特点是两个相同的数异或等于 $0$，

大家还知道，异或的特点就是拿 $0$ 异或什么数，结果就是什么数。

### [异或知识](https://oi-wiki.org/math/bit/)

我们就可以发现，求一个数列里除了某个数剩余数字的异或和其实就是整个数列的异或和异或了该数字。因为数列里的这个数字被异或为 $0$，对结果不造成改变，相当于消除了，就算出了不包括该数的异或和。

### 上代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200005],sum;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sum^=a[i];
    }
    for(int i=1;i<=n;i++){
    	cout<<(sum^a[i])<<" ";
    }
    return 0;
}
```

### 下期见！

---

## 作者：CoderCharlie (赞：2)

### 题意

现有 $n$ 个数 $a_1,a_2,\ldots,a_n$。

已知：

$$
\left\{
\begin{matrix}
b_1=a_2\oplus a_3\oplus a_4\oplus \ldots \oplus a_n \\
b_2=a_1\oplus a_3\oplus a_4\oplus \ldots \oplus a_n \\
b_3=a_1\oplus a_2\oplus a_4\oplus \ldots \oplus a_n \\
\ldots \\
b_n=a_1\oplus a_2\oplus a_3\oplus \ldots \oplus a_{n-1} \\
\end{matrix}
\right.
$$

现在给出 $b_1,b_2,\ldots,b_n$，请你求出 $a_1,a_2,\ldots,a_n$。

### 题目分析

首先，我们要知道一个基本的定理：

$$
k \oplus k=0
$$

这是因为异或相同为 $0$，不同为 $1$。所以两个相同的数异或的值为 $0$。

知道了这个之后，我们就可以把题目中的式子全部都异或起来，变成这样：

$$
\overbrace{(a_1\oplus a_1\oplus \ldots \oplus a_1)}^{n-1}\oplus \overbrace{(a_2\oplus a_2\oplus \ldots \oplus a_2)}^{n-1}\oplus \ldots \oplus \overbrace{(a_n\oplus a_n\oplus \ldots \oplus a_n)}^{n-1}=b_1\oplus b_2\oplus \ldots\oplus b_n
$$

因为 $n$ 是偶数，所以可以化简成：

$$
a_1\oplus a_2\oplus \ldots \oplus a_n=b_1\oplus b_2\oplus \ldots \oplus b_n
$$

我们令 $b_1\oplus b_2\oplus \ldots \oplus b_n$ 为 $x$，则：

$$
a_1\oplus a_2\oplus \ldots \oplus a_n=x
$$

把这个式子和题目中第一个式子异或，得：

$$
a_1\oplus (a_2\oplus a_2)\oplus (a_3\oplus a_3)\oplus \ldots \oplus (a_n\oplus a_n)=x\oplus b_1
$$

化简一下，得：

$$
a_1=x\oplus b_1
$$

同理可证，$a_i=x\oplus b_i$。

于是，我们就可以得出答案了。

### AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200100];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,k=0;
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		cin>>a[i];
		k^=a[i];
	}
	for (int i=1;i<=n;i++)
		cout<<(k^a[i])<<' ';
	return 0;
}
```

---

## 作者：沉石鱼惊旋 (赞：2)

>upd 2023.05.05 20:10：修复了一处 $\LaTeX$ 错误。

[更好的阅读体验](http://blog.cyx2009.top/archives/165/)

# 题目翻译

> 给出有 $n$ 个数的序列 $b$，还原序列 $a$，使 $a_i$ 为除 $b_i$ 以外所有数的异或和。
> $2\leq n\leq 2\times 10^6,0\leq a_i\leq 10^9$。
> $n\equiv0\pmod{2}$。

# 题目思路

前置知识：异或的归零律、恒等律与自反 $a\oplus a=0,a\oplus 0=a,a\oplus b\oplus a=b$。

观察题意可得我们求出的 $a_i$ 即为 $b_1\oplus b_2\oplus \dots \oplus b_n$ 再去除一个 $b_i$。

设 $b_1\oplus b_2\oplus \dots \oplus b_n=k$。

我们根据异或的自反可得：

$$
\begin{aligned}k\oplus b_i&=b_1\oplus b_2\oplus \dots \oplus b_n\oplus b_i\\&=b_1\oplus b_2\oplus\dots\oplus b_{i-1}\oplus b_{i+1}\oplus b_{i+2}\oplus \dots \oplus b_n\end{aligned}
$$

于是我们得到了想求的 $a$ 数组。

# 完整代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int a[200020];
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        k^=a[i];
    }
    for(int i=1;i<=n;i++)
    {
        cout<<(k^a[i])<<" \n"[i==n];
    }
    return 0;
}
```


---

## 作者：Dr_Octopus (赞：1)

## 题意

有一个长度为 $n$ 的序列 $b$，$n$ 为偶数，现在已知序列 $a$，满足 $a_i$ = $b_1$ $\oplus$ $\cdots$ $\oplus$ $b_{i - 1}$ $\oplus$ $ \cdots$ $b_n$，要求还原出序列。


------------


### [异或基础知识](https://oi-wiki.org/math/bit/)


------------

## 解题思路

设 $tot$ = $a_1$ $\oplus$ $a_2$ $\oplus$ $\cdots$ $\oplus$ $a_{n - 1}$ $\oplus$ $a_n$。


所有 $b_i$ 都在里面异或了 $n-1$ 次，且 $n$ 为偶数，则 $n-1$ 为奇数。

所以结果 $tot = b_1 \oplus b_2 \oplus \cdots \oplus b_{n-1} \oplus b_n$。

最后 $tot \oplus a_i$ 的值即为 $b_i$ 的值。

------------

## code
```cpp
#include<bits/stdc++.h>
#define int long long 
const int N = 200010;
using namespace std;

int a[N],b[N];
int n, tot;

signed main() {
	cin >> n;
	for(int i = 1;i <= n; i++) {  cin >> a[i], tot ^= a[i];  }
	for(int i = 1;i <= n; i++) {  b[i] = tot ^ a[i], cout << b[i] << " ";  }
	return 0;
}


```



---

## 作者：Anaxagoras (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc171_e)

### 0x00 前置知识

异或有六个法则（摘自百度百科）：

1. 归零律：$a\oplus a=0$。
2. 恒等律：$a\oplus0=a$。
3. 交换律：$a\oplus b=b\oplus a$。
4. 结合律：$a\oplus b\oplus c=a\oplus\left(b\oplus c\right)=\left(a\oplus b\right)\oplus c$
5. 自反律：$a\oplus a\oplus b=b$
6. $a\oplus b\oplus c=d\Rightarrow b\oplus c\oplus d=a$。

实际上我们可以看出，前三条是显而易见的，而后三条是根据前三条推出来的（第四条的依据是第三条，第五条的依据是前两条，第六条的依据是前两条的关系）。

这篇题解需要用到第四、五条。

### 0x01 思路

就拿 $a_1$ 来说，$a_1=b_2\oplus b_3\oplus\dots\oplus b_n=b_1\oplus b_2\oplus b_3\oplus\dots\oplus b_n\oplus b_1$，也就是说，$a_i$ 其实就是整个序列的异或和异或 $b_i$，整个序列的异或和可以边输入边处理，最后再 $\Theta(n)$ 输出，所以整个时间复杂度是 $\Theta(n)$，完全可以过。

### 0x02 AC Code
```cpp
//by olkieler
#include <bits/stdc++.h>
#define int unsigned long long
#define inf LLONG_MAX
#define ios ios::sync_with_stdio(0);cin.tie(0);
#define retrun return
#define N 200005
#define M 100005
#define mod 360732200906210037
#define pint pair<int,int>
#define mp make_pair
#define base 997
#define prime 20090561
using namespace std;
int a[N];
signed main()
{
	ios;
	int n, sum = 0;
	cin >> n;
	for (int i = 1; i <= n; i ++)
	{
		cin >> a[i];
		sum ^= a[i];
	}
	for (int i = 1; i <= n; i ++)
	{
		cout << (sum ^ a[i]) << ' ';
	}
}
```

---

## 作者：ReeChee (赞：1)

## Problem

给出一个长为 $N$ 的序列 $a$，$a_i$ 为原始序列 $b$ 上的每一个除了 $b_i$ 其它所有数的异或和，求出原始序列 $b$。

$2 \leq N \leq 200000$，$0 \leq a_i \leq 10^9$，**且 $N$ 为偶数**。

## Algorithm #1 100pts

首先异或有两个运算定律：

1. 自反律： $x \operatorname{xor} y \operatorname{xor} y = x$。

2. 结合律： $x \operatorname{xor} y \operatorname{xor} z = x \operatorname{xor} (y \operatorname{xor} z) = (x \operatorname{xor} y) \operatorname{xor} z$。

考虑将 $a_i$ 展开成 $b_i$ 的形式：

$a_1=b_2 \operatorname{xor} b_3 \operatorname{xor} \dots \operatorname{xor} b_n$

$a_2=b_1 \operatorname{xor} b_3 \operatorname{xor} \dots \operatorname{xor} b_n$

$a_3=b_1 \operatorname{xor} b_2 \operatorname{xor} \dots \operatorname{xor} b_n$

因为自反律，其实也可以写成：

$a_1=b_1 \operatorname{xor} b_2 \operatorname{xor} \dots \operatorname{xor} b_n \operatorname{xor} b_1$

$a_2=b_1 \operatorname{xor} b_2 \operatorname{xor} \dots \operatorname{xor} b_n \operatorname{xor} b_2$

$a_3=b_1 \operatorname{xor} b_2 \operatorname{xor} \dots \operatorname{xor} b_n \operatorname{xor} b_3$

$\dots$

$a_i=b_1 \operatorname{xor} b_2 \operatorname{xor} \dots \operatorname{xor} b_n \operatorname{xor} b_i$

结合一下：

$a_i=(b_1 \operatorname{xor} b_2 \operatorname{xor} \dots \operatorname{xor} b_n) \operatorname{xor} b_i$

统计 $a_i$ 的异或和 $k$，**因为 $N$ 为偶数**，所以前面整体消去。

最终可以发现 $a_i$ 的异或和即为 $b_i$ 的异或和。

而又因 $a_i=b_1 \operatorname{xor} b_2 \operatorname{xor} \dots \operatorname{xor} b_n \operatorname{xor} b_i$，所以 $k \operatorname{xor} a_i=(b_1 \operatorname{xor} b_2 \operatorname{xor} \dots \operatorname{xor} b_n) \operatorname{xor} (b_1 \operatorname{xor} b_2 \operatorname{xor} \dots \operatorname{xor} b_n \operatorname{xor} b_i)=b_i$。

输入时统计 $a_i$ 的异或和，最后对于每一个 $a_i$ 输出 $k \operatorname{xor} a_i$ 即可。

时间复杂度 $\mathcal{O}(n)$。

## Code

```cpp
ll n,a[N],k;
int main(){
    n=read();
    F(i,1,n){
        a[i]=read();
        k^=a[i];
    }
    F(i,1,n)
        printf("%lld ",k^a[i]);
    return 0;
}
```

---

## 作者：PineappleSummer (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc171_e)

异或性质好题。

题目中说 $a_i$ 为除 $b_i$ 以外所有数的异或和，考虑计算 $a_1\oplus a_2 \oplus \cdots \oplus a_n$ 的值。

我们知道 $a_1=b_2 \oplus b_3\oplus\cdots\oplus b_n$，$a_2=b_1\oplus b_3\oplus \cdots\oplus b_n$，$\ldots$，$a_n=b_1\oplus b_2\oplus \cdots\oplus b_{n-1}$。所以

$a_1\oplus a_2 \oplus \cdots \oplus a_n=\overbrace{(b_1\oplus b_1\oplus \cdots \oplus b_1)}^{n-1}\oplus \overbrace{(b_2\oplus b_2\oplus \cdots \oplus b_2)}^{n-1}\oplus \cdots \oplus \overbrace{(b_n\oplus b_n\oplus \cdots \oplus b_n)}^{n-1}$

根据异或的性质：$a\oplus a=0$，得出 $\overbrace{(b_i\oplus b_i\oplus \cdots \oplus b_i)}^{n-1}=b_i$，所以上面的式子还可化简为：$a_1\oplus a_2 \oplus \ldots \oplus a_n=b_1\oplus b_2\oplus \cdots b_n$。

设 $x=a_1\oplus a_2\oplus \cdots a_n$，则 $x=b_1\oplus b_2\oplus \cdots b_n$。看题目：$a_i$ 为除 $b_i$ 以外所有数的异或和，所以每个 $a_i$ 与 $x$ 之间只差了个 $b_i$，再根据异或的性质可得：$b_i=x\oplus a_i$。由此得出本题代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+10;
ll n,a[N],x;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i],x^=a[i];
	for(int i=1;i<=n;i++)
		cout<<(x^a[i])<<' ';
	return 0;
}
```

时间复杂度 $O(n)$。

---

## 作者：fish_love_cat (赞：0)

众所周知，异或有个神奇的特点，那就是两个相同的数异或出来的结果必定为 $0$。

众所又周知，异或还有个神奇的特点，那就是拿 $0$ 异或什么数，结果就是什么数。

故此，我们可以发现，求一个数列里除了某个数剩余数字的异或和其实就是整个数列的异或和异或了该数字。因为数列里的这个数字被异或为 $0$，对结果不造成改变，相当于消除了，就算出了不包括该数的异或和。

**那么代码就没啥难的了：**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200000],ans;
int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
        ans^=a[i];
    }
    for(int i=0;i<n;i++) cout<<(ans^a[i])<<" ";
    return 0;
}
```

---

## 作者：zhouzihe (赞：0)

## 1 观察题目
想要做出这道题，首先我们得知道 $a \bigoplus a=0$，知道了这个以后事情就好办了。我们先用 $ans$ 记录所有数的异或和，输出 $a_i$ 时，即输出 $ans \bigoplus b_i$。
## 2 code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long int n,b[200005],sum;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>b[i];
		sum^=b[i];
	}
	for(int i=1;i<=n;i++){
		cout<<(sum^b[i])<<" ";
	}
	return 0;
}
```


---

## 作者：DPseud (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc171_e)

题目意思不必赘述，很明显，可以用 $O(n^2)$ 求出 $a$，但是这样会超时。

注意到每一个 $a_i$ 其实都是 $b_1 \oplus b_2 \oplus b_3 \oplus \dots \oplus b_n$ 的结果中少异或了 $b_i$，考虑如何把这个 $b_i$ 进行反异或。

异或的[法则](https://www.luogu.com.cn/paste/d30twpvv)有这么两条相互关联的律：

$a\oplus a=0$

$a\oplus 0=a$

根据第一条，我们能得出 $b_i \oplus b_i=0$，考虑把它代入 $b_1 \oplus b_2 \oplus b_3 \oplus \dots \oplus b_n$ 中，能发现，只需要加入一个 $b_i$ 就能得出一个 $b_1 \oplus b_2\oplus \dots \oplus b_{i-1} \oplus b_{i+1}\oplus \dots \oplus b_n \oplus (b_i\oplus b_i)$，实际上就相当于 $b_1 \oplus b_2\oplus \dots \oplus b_{i-1} \oplus b_{i+1}\oplus \dots \oplus b_n \oplus 0$，而根据第二条，这就相当于 $b_1 \oplus b_2\oplus \dots \oplus b_{i-1} \oplus b_{i+1}\oplus \dots \oplus b_n$，已经是把 $b_i$ 去掉了，因此得出：

$a_i=b_1 \oplus b_2 \oplus \dots \oplus b_n \oplus b_i$

于是能打出代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    static int n,a[222222],yh;
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i],yh^=a[i];
    for(int i=1;i<=n;i++)cout<<(yh^a[i])<<" ";
    cout<<endl;
    return 0;
}
```


---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc171_e)

## 前置知识

异或（xor）的六个运算律：

1. 归零律：$a\oplus a=0$
1. 恒等率：$a\oplus 0=a$
1. 交换律：$a\oplus b=b\oplus a$
1. 结合律：$a\oplus b\oplus c=a\oplus(b\oplus c)$
1. 自反律：$a\oplus a\oplus b=b$
1. 移项：$a\oplus b\oplus c=d\rightarrow b\oplus c\oplus d=a$

这道题需要用到第四、五条。

## 思路

题目中给的条件，意思就是 $a_i$ 是整个序列的异或和再 $\oplus b_i$。求出异或和之后，再在遍历每个 $b_i$ 的时候异或这个异或和，就是这个序列 $a$。

- 最后别忘输出换行。

## 代码 

~~~cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,a[N],ans;
int main(){
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        ans^=a[i];
    }
    for(int i=1;i<=n;++i)cout<<(ans^a[i])<<" ";
    cout<<endl;
    return 0;
}
~~~

[AC 记录](https://www.luogu.com.cn/record/96733961)

---

