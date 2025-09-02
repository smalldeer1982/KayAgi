# Fortune Telling

## 题目描述

Haha, try to solve this, SelectorUnlimited!

— antontrygubO_o



Your friends Alice and Bob practice fortune telling.

Fortune telling is performed as follows. There is a well-known array $ a $ of $ n $ non-negative integers indexed from $ 1 $ to $ n $ . The tellee starts with some non-negative number $ d $ and performs one of the two operations for each $ i = 1, 2, \ldots, n $ , in the increasing order of $ i $ . The possible operations are:

- replace their current number $ d $ with $ d + a_i $
- replace their current number $ d $ with $ d \oplus a_i $ (hereinafter $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Exclusive_or))

Notice that the chosen operation may be different for different $ i $ and for different tellees.

One time, Alice decided to start with $ d = x $ and Bob started with $ d = x + 3 $ . Each of them performed fortune telling and got a particular number in the end. Notice that the friends chose operations independently of each other, that is, they could apply different operations for the same $ i $ .

You learnt that either Alice or Bob ended up with number $ y $ in the end, but you don't know whose of the two it was. Given the numbers Alice and Bob started with and $ y $ , find out who (Alice or Bob) could get the number $ y $ after performing the operations. It is guaranteed that on the jury tests, exactly one of your friends could have actually gotten that number.

Hacks

You cannot make hacks in this problem.

## 说明/提示

In the first test case, Alice could get $ 9 $ using the following operations: $ 7 + 2 = 9 $ .

In the second test case, Alice could get $ 2 $ using this operations: $ (0 + 1) \oplus 3 = 2 $ .

In the third test case, Bob started with $ x+3 = 0+3=3 $ and could get $ 1 $ this way: $ (((3 + 1) + 2) \oplus 3) \oplus 4 = 1 $ .

## 样例 #1

### 输入

```
4
1 7 9
2
2 0 2
1 3
4 0 1
1 2 3 4
2 1000000000 3000000000
1000000000 1000000000```

### 输出

```
Alice
Alice
Bob
Alice```

# 题解

## 作者：Rnfmabj (赞：15)

### 题意

已知一个长为 $n$ 的数组 $a$ ， 一个整数 $x$ ，一个目标整数 $y$ ，判断 $x$ 和 $x+3$ 是否可通过对数组 $a$ 中每个元素 $a_i$ ，选择让整数 $x$ （或 $x+3$ ） 加上 $a_i$ 或变为 $x ⊕ a_i$ ，来使原整数变为目标整数 $y$ 。


------------


### 思路

看到异或的时候我已经猜到了结局。

我们揣测一下出题人的意图，原题目中要求的是输出 $x$ 和 $x+3$ 中哪个能通过以上操作变为 $y$ ，也就意味着 $x$ 和 $x+3$ 中只有一个是可以满足要求的。为什么？

注意到异或运算的性质。“（位上）相同为假，相异为真”，由于它 $0⊕0=0$ 、 $1⊕1=0$ 的特点，感性理解一下就好像“不会进位的加法”。

也就意味着，同样的两组整数，其进行加法和进行异或运算的结果在二进制的末位相同，即： $a+b \equiv a ⊕ b \left( mod 2 \right) $ 。

所以，由于 $x$ 与 $x+3$ 的奇偶性不同，它们在对相同序列进行一系列加法运算或异或运算后得到的结果，奇偶性也是不同的。我们就可以用这个性质来区分哪个是可以满足要求的——只要得到结果的奇偶性与 $y$ 的奇偶性相同，那么它就是满足要求的那一个。



------------

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define R read()
#define file(a) freopen(#a".in","r",stdin),freopen(#a".out","w",stdout)
using namespace std;
inline ll read() {
	ll s=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-')f*=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*f;
}
inline void write(ll x) {
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10),x%=10;
	putchar('0'+x);
}//Don't use it for CF.
inline void wk(ll x){write(x);putchar(' ');}
inline void we(ll x){write(x);putchar('\n');}//这一段往上都是快读快写。
ll n,x,y;//变量与题目中相同。
ll T;
signed main(){
	T=R;//R 是我的宏定义，快读。
	while(T--){
		n=R,x=R&1,y=R&1;//由于我们只要用到 x 和 y 的奇偶性，可以在一开始就将其简化为模 2 意义后的值。
		for(ll i=1;i<=n;i++){
			x^=R&1;//可以在读入的时候直接对 x 操作，这里我选了异或，对答案没有影响。同时读入的数也可以简化。
		}
		if(!x^y)cout<<"Alice"<<endl;//如果最后的 x 和 y 相同那么就是 x 满足条件。
		else cout<<"Bob"<<endl;//反之 x+3 满足条件。
	}
	return 0;
}

```


---

## 作者：8atemak1r (赞：7)

## Description

`Alice` 和 `Bob` 在玩游戏，给定一个目标数 $y$ 和初始数 $x$（`Alice` 的初始数为 $x$，`Bob` 的初始数为 $x + 3$），以及一个长度为 $n$ 的数组，他们依次进行 $n$ 次操作，操作的编号从 $1$ 至 $n$ ，他们每次可以选择将当前自己的数 $d$ 变为 $d + a_i$ 或 $d⊕a_i$，已知 `Alice` 和 `Bob` 两人中有且只有一个人能在进行 $n$ 次操作后得到目标数 $y$，求出是哪个人得到了 $y$。



## Solution

相信有不少朋友看到这道题之后，和我在赛时的第一反应一样，是 DFS，但是当我们看到 $n < 10^5$ 的数据范围，只能换用别的方法。既然暴力算法不行，那我们只能尝试去寻找题目的性质了。



首先我们注意到`Alice` 和 `Bob` 的初始数刚好相差 $3$，所以这两个数字的奇偶性必然是不同的。



我们向奇偶性这个方向去想，惊喜的发现，异或运算和加法运算对于一个数的奇偶性的影响是一样的，用更加形式化的方式描述，可以表示为

$$a + b \equiv a ⊕ b\pmod 2$$

接下来就简单了，只需要将他们中某一个人的初始数进行 $n$ 次异或或加和操作后判断与 $y$ 的奇偶性是否相同就好了。



## Code

```cpp
#include<iostream>
using namespace std;
long long t, n, a, b, y, tmp;
int main() {
    ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0); // 读入速度优化
    cin >> t; // t 组数据
    while(t --) {
        cin >> n >> a >> y;
        for(int i = 1; i <= n; ++ i) {
            cin >> tmp;
            a ^= tmp;
        }// 这里直接用的是Alice的初始数做n次异或操作
        if(((a & 1) ^ (y & 1)) == 1) cout << "Bob\n";
        else cout << "Alice\n"; 
    }
    return 0;
}
```





---

## 作者：cyrxdzj (赞：1)

### 一、思路

相信大家都知道，对于加法，若两个数同奇或同偶，则结果一定为偶数。否则结果一定为奇数。

而异或运算，也是这样的。

因此，无论每次操作是加法还是异或，最终结果的奇偶性一定不変。

我们可以发现，Alice 以 $x$ 开始，Bob 以 $x+3$ 开始。因此，Alice 的结果和 Bob 的结果的奇偶性一定不同。

再考虑到题目保证一定有某个人可以得出要求的结果，我们就可以判断 Alice 进行全部操作后得出的结果与要求的结果的奇偶性是否相同。若相同，则输出 Alice。否则输出 Bob。

### 二、完整代码

```
#include<cstdio>
using namespace std;
int t;
int n,x;
long long y;
long long abs(long long a)
{
	return a>=0?a:-a;
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d%lld",&n,&x,&y);
		int temp=0;
		for(int i=1,k;i<=n;i++)
		{
			scanf("%d",&k);
			temp+=(k%2);
		}
		temp%=2;//数组中所有数据加起来是偶数（0）还是奇数（1）？
		if(temp==abs(x-y)%2)
		{
			printf("Alice\n");
		}
		else
		{
			printf("Bob\n");
		}
	}
	return 0;
}

```

---

## 作者：miao5 (赞：1)

### 题目大意

给定两个数 $x$ 和 $x+3$ ，有一个数列 $a$，$n$ 代表 $a$ 的长度。给定的两个数在数列上从 $1$ 到 $n$ 做操作，每次可以选择异或或者加法，两个数互不影响。问哪一个数经过 $n$ 次操作后能变成给定数 $y$，保证有且仅有一个解。

### 大体思路

我们思考异或的基本性质，一个数异或另一个数时，如果两个数的奇偶性相同，得数为偶数，否则得数为奇数，而加法有相同的性质。这样从奇偶性的角度来考虑，异或操作和加法操作变成了同一个操作。

我们再从奇偶性的角度观察给定的数。$x$ 和 $x+3$ 的奇偶性一定不同，那么他们经过一串相同的操作之后的奇偶性一定也不同。由于题目保证有且仅有一个答案，我们对 $x\bmod 2$ 执行一遍操作，判断最后得数与 $y\bmod 2$ 进行对比，如果相同则答案为 $x$，否则答案为 $x+3$。
```
#include<iostream>
#define int long long
using namespace std;
int a[100005];
int q[100005],p[100005];
signed main(){
	int t;
	cin>>t;
	while(t--){
		int n,x,y;
		cin>>n>>x>>y;
		for(int i=1;i<=n;i++) cin>>a[i];
		int flag=(x%2);
		for(int i=1;i<=n;i++){
			if(a[i]%2==flag) flag=0;
			else flag=1;
		}
		if(flag==y%2) cout<<"Alice"<<endl;
		else cout<<"Bob"<<endl;
	}
}
```

---

## 作者：江户川コナン (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1634B)

题意：

给你一个长为 $n$ 的序列 $a$，给你两个数 $x$、$y$，求 $x$ 和 $x+3$ 两个数哪个经过与 $a$ 中每个元素都进行一次加法或异或后可以变成y。

分析：

相信大家跟我一样，看到这道题的第一反应就是爆搜。然鹅，一看数据范围 $n \le 1 \times 10^5$……算了吧。

重新看题：$x$ 和 $x+3$ ？似乎奇偶性有戏？于是我们来分析一下：

加法：

- 奇+奇=偶
- 奇+偶=奇
- 偶+偶=偶

异或：

- 奇⊕奇=偶
- 奇⊕偶=奇
- 偶⊕偶=偶

一看：两种运算算出来的数的奇偶性竟然是一样的！用式子表示就是：
$$a+b\equiv a⊕b \pmod 2$$

这样一来，解题思路就有了：

将 $x$ 对 $a$ 中的每一个数都进行一次加法（异或也可以），最后算出来的数与 $y$ 比较奇偶性：
相同则Alice，不同则Bob，也就是：
$$ ans = \begin{cases}
\text{Alice} \quad x\equiv y \pmod 2\\
\text{Bob}\quad x \not\equiv y \pmod 2 
\end{cases}$$

于是我们就可以愉快的写出代码啦~~~
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long //y 可以达到 1e15，所以要开long long
int n,x,y,T;
void read(){
    cin>>n>>x>>y;
    int op;
    for(int i=1;i<=n;i++){  
        cin>>op;
        x+=op;
    }
    bool flagx,flagy;
    if(x&1) flagx=true;
    else flagx=false;
    if(y&1) flagy=true;
    else flagy=false;
    if(!(flagx^flagy)){
        cout<<"Alice\n";
    }else cout<<"Bob\n";
    //利用异或判断奇偶性是否相同。不过记得如果异或后得1说明奇偶性不相同，而异或后得0才说明奇偶性相同
}
signed main(){
    //cin>>n>>x>>y;
    cin>>T;
    while(T--){
        read();
    }
    return 0;
}
```

完结撒花~

---

## 作者：Cocoly1990 (赞：0)

诈骗题。本场比赛因为 AI 的参与（虽然最后放了大家鸽子），命题组使出了高超骗术，ABC 全他妈是诈骗。

看到不能叉，容易发现标程无法在短时间检查数据是否合法，根据异或的小知识，我们注意到

$$x\oplus y \bmod2=x+y\bmod2$$

可以发现，不管如何操作，最后答案的奇偶性是定值。

又发现，$x$ 和 $x+3$ 奇偶性不同。

直接取 $x$ 对每个 $a_i$ 做异或判断奇偶性即可。

---

## 作者：ttq012 (赞：0)

思维题。

我们首先推算一下异或运算的规律。

异或运算的定义：两个数转换为二进制数，对于二进制的每一位，如果两个数相同，这一位就是 $0$，否则就是 $1$。最后将答案转换回十进制。

|运算位 $1$|运算位 $2$|两个位异或之后的得数|
|-|-|-|
|$0$|$0$|$0$|
|$0$|$1$|$1$|
|$1$|$0$|$1$|
|$1$|$1$|$0$|

可以通过上述的表格发现以下的规律：$a \operatorname{xor} b$ 和 $a + b$ 对 $2$ 取模后的得数是相同的。

因此我们从数字 $s$ 开始，对 $a_i$ 进行运算，从 $a_1$ 一直运算到 $a_n$，答案对 $2$ 取模的结果一定是 $\sum_{i=1}^{n} a_i + x$。由于题目保证数据一定有解，所以直接计算 $\sum_{i=1}^{n} a_i + x$ 对 $2$ 取模的结果和 $y$ 对 $2$ 取模的结果是否相同即可，如果相同，则 `Alice` 必定获胜，输出 `Alice`，否则 `Bob` 必定获胜，输出 `Bob`。

**Code**

```cpp
#include <bits/stdc++.h>

using namespace std;

signed main() {
    int t;
    cin >> t;
    while (t --) {
        long long n, x, y;
        scanf ("%lld%lld%lld", &n, &x, &y);
        y &= 1;
        long long sum = x & 1; // 计算总和
        for (int i = 1; i <= n; i ++) {
            long long te;
            scanf ("%lld", &te);
            sum += te;
            sum &= 1; // 对2取模的位运算写法
        }
        if (sum == y) puts("Alice");
        else puts("Bob");
    }
    return 0;
}

```


---

## 作者：newbie_QwQ (赞：0)

这是一道思维题。

------------
分析：读完这道题之后，我们惊奇地发现一个数和另一个数相加或者异或之后，奇偶性是不变的。所以，我们就可以用 $x$ 把整个 $a$ 数组都加一遍（异或也行），判断是不是和 $y$ 的奇偶性一样。如果一样，输出 ```Alice```，如果不一样，就输出 ```Bob```。

------------
## AC 代码：
```cpp
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
using namespace std;
long long n,i,x,y,t,a,flag; 
int main()
{
	cin>>t; 
	while(t--)
  	{
  		cin>>n>>x>>y;
  		for(i=1;i<=n;i++) 
		{
			cin>>a;//为了节省空间，只用了一个变量。
			x=x+a;//把 a 数组加一遍（异或也行）。
		}
		if((x%2)==(y%2)) cout<<"Alice"<<endl;//判断奇偶性。
		else cout<<"Bob"<<endl;
	}
	return 0;//再见！
}
```

---

## 作者：feicheng (赞：0)


## Description

给定长度为 $n$ 的序列 $a$ 和整数 $x,y$，对某一个固定的整数 $d$，可以按照下标递增的顺序做 $n$ 次操作，对第 $i$ 次操作，可以选择将 $d$ 变为 $d+a_i$ 或是 $d\oplus a_i$（$\oplus$ 表示异或），操作之间不独立。

询问 $x$ 还是 $x+3$ 可以在经过若干次操作后变成 $y$（保证有解且不可能同时变成 $y$）。

多测

**限制**：$1\le n,\sum n\le 10^5$，$0\le x\le 10^9$，$0\le y\le 10^{15}$。

## Solution

这个题场上的时候感觉好怪，就先去做 $\text C$ 了，做完回来发现是个萌萌题。

从奇偶性的角度考虑：设 $a,b$ 是整数，则 $a+b\equiv a\oplus b\pmod 2$，所以直接对 $x$ 从 $1\sim n$ 做一遍模意义下加法就行，如果最后的奇偶性和 $y$  一样，说明是 $x$，否则是 $x+3$。

## Code

```cpp
using LL = int_fast64_t;
 
inline void solve() {
  int n;
  LL x, y;
  cin >> n >> x >> y;
  std::vector<LL> a(n);
  for (auto& it : a) {
    cin >> it;
  }
  for (const auto& it : a) {
    x = (x + it) & 1;
  }
  if (x == (y & 1)) {
    cout << "Alice\n";
  }
  else {
    cout << "Bob\n";
  }
}
 
```

---

## 作者：13802919466djh (赞：0)

### 题目
[题目传送门](https://www.luogu.com.cn/problem/CF1634B)

### 解法
注意到 $x$ 和 $x+3$ 中一定有一个偶数和一个奇数。于是我们可以朝奇偶性方向想，容易发现，${a\oplus{b}\equiv{a+b}}\pmod{2}$，那么解法就出来了。

先将 `Alice` 的初始数 $x$ 做 $n$ 次异或操作或 $n$ 次加法操作，判断是否和 $y$ 的奇偶性相同，如相同，输出 `Alice`，否则输出 `Bob`。

### AC代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){int f=1,x=0;char ch=getchar();while (ch<'0'||ch>'9'){if (ch=='-') f=-1; ch=getchar();}while (ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}return x*f;}
inline void write(int x){if (x<0){putchar('-');x=-x;}if(x>9) write(x/10);putchar(x%10+'0');}
inline void Write(int x){write(x);putchar('\n');}
//快读加快写是个人习惯，不加也可以AC
int t,n,x,y;
signed main(){
    t=read();
    while(t--){
        n=read(),x=read(),y=read();
        for(int i=1;i<=n;++i)x=(x+read())%2;//n次加法处理 
        if(x%2==y%2)printf("Alice\n");
        else printf("Bob\n"); 
    }
    return 0;
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 题意

有一个算命游戏，规则如下：

有一个自然数 $d$，一个长为 $n$ 的自然数数组 $a$。

对于每一个 $i(1\le i\le n)$，有两种操作：

+ $d\gets d+a[i]$；

+ $d\gets d\oplus a[i]$

对于每一个 $i$，每一个操作必须且仅执行一次。

然后看看是否可能结果为 $y$。

现在，`Alice` 和 `Bob` 拿到了各自的 $d$，其中 `Alice` 的是 $d=x$，`Bob` 的是 $d=x+3$。

请问，有谁最后能得出结果为 $y$？

保证他们有且仅有一个能得出结果为 $y$。

输入一个正整数 $t$ 表示数据组数。

然后对于每组数据，先输入 $3$ 个整数 $n$、$x$、$y$，再输入长度为 $n$ 的整数数组 $a$。

### 2 思路

让我们记住一句话：**奇变偶不变，**符号看象限。

很明显，加、减、异或都遵守这半句话，并且，`Alice` 和 `Bob` 的 $d$ 的奇偶性必定不同。

我们可以设一个变量 $u$，初始化为 $x\operatorname{mod}2$。不过呢，二进制运算更快，毕竟，对于所有自然数 $i$，有 $i\operatorname{mod}2=i\operatorname{and}1$。

然后，我们把 $u$ 跟 $a$ 里所有的数的奇偶性都异或一遍。

如果 $u$ 的奇偶性与 $y$ 相同，那么 `Alice` 就能得到 $y$；否则是 `Bob`。

换句话说，设：

$$u=(x\operatorname{and}1)\oplus\bigoplus^n_{i=1}(a[i]\operatorname{and}1)$$

如果 $u\operatorname{and}1=y\operatorname{and}1$，输出 `Alice`；否则输出 `Bob`。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
#define max_n 100000
int t;
int n;
int x;
long long y;
long long a[max_n+2];
bool u;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1634B_1.in","r",stdin);
	freopen("CF1634B_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%lld",&n,&x,&y);
		u=x&1;
		for(int i=1;i<=n;++i){
			scanf("%d",a+i);
			if(a[i]&1)u^=1;
		}
		if(u==(y&1))printf("Alice\n");
		else printf("Bob\n");
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/68887604)

By **dengziyue**

---

