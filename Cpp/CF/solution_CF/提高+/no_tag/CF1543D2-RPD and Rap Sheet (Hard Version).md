# RPD and Rap Sheet (Hard Version)

## 题目描述

This is the hard version of the problem. The only difference is that here $ 2\leq k\leq 100 $ . You can make hacks only if both the versions of the problem are solved.

This is an interactive problem!

Every decimal number has a base $ k $ equivalent. The individual digits of a base $ k $ number are called $ k $ -its. Let's define the $ k $ -itwise XOR of two $ k $ -its $ a $ and $ b $ as $ (a + b)\bmod k $ .

The $ k $ -itwise XOR of two base $ k $ numbers is equal to the new number formed by taking the $ k $ -itwise XOR of their corresponding $ k $ -its. The $ k $ -itwise XOR of two decimal numbers $ a $ and $ b $ is denoted by $ a\oplus_{k} b $ and is equal to the decimal representation of the $ k $ -itwise XOR of the base $ k $ representations of $ a $ and $ b $ . All further numbers used in the statement below are in decimal unless specified.

You have hacked the criminal database of Rockport Police Department (RPD), also known as the Rap Sheet. But in order to access it, you require a password. You don't know it, but you are quite sure that it lies between $ 0 $ and $ n-1 $ inclusive. So, you have decided to guess it. Luckily, you can try at most $ n $ times without being blocked by the system. But the system is adaptive. Each time you make an incorrect guess, it changes the password. Specifically, if the password before the guess was $ x $ , and you guess a different number $ y $ , then the system changes the password to a number $ z $ such that $ x\oplus_{k} z=y $ . Guess the password and break into the system.

## 说明/提示

Test Case 1:

In this case, the hidden password is $ 2 $ .

The first query is $ 3 $ . It is not equal to the current password. So, $ 0 $ is returned, and the password is changed to $ 1 $ since $ 2\oplus_2 1=3 $ .

The second query is $ 4 $ . It is not equal to the current password. So, $ 0 $ is returned, and the password is changed to $ 5 $ since $ 1\oplus_2 5=4 $ .

The third query is $ 5 $ . It is equal to the current password. So, $ 1 $ is returned, and the job is done.

Test Case 2:

In this case, the hidden password is $ 3 $ .

The first query is $ 1 $ . It is not equal to the current password. So, $ 0 $ is returned, and the password is changed to $ 7 $ since $ 3\oplus_3 7=1 $ . $ [3=(10)_3 $ , $ 7=(21)_3 $ , $ 1=(01)_3 $ and $ (10)_3\oplus_3 (21)_3 = (01)_3] $ .

The second query is $ 4 $ . It is not equal to the current password. So, $ 0 $ is returned, and the password is changed to $ 6 $ since $ 7\oplus_3 6=4 $ . $ [7=(21)_3 $ , $ 6=(20)_3 $ , $ 4=(11)_3 $ and $ (21)_3\oplus_3 (20)_3 = (11)_3] $ .

The third query is $ 6 $ . It is equal to the current password. So, $ 1 $ is returned, and the job is done.

Note that these initial passwords are taken just for the sake of explanation. In reality, the grader might behave differently because it is adaptive.

## 样例 #1

### 输入

```
2
5 2

0

0

1
5 3

0

0

1```

### 输出

```
3

4

5


1

4

6```

# 题解

## 作者：Evier (赞：6)

## 题意
你要猜一个数 $x$ ，且 $0\le x < n$ 。特别地，设一次交互猜的数为 $y$ ，若 $y \ne x$ 则 $x$ 变为 $z$ ，其中 $x \oplus_{k} z=y$ 。定义 $a \oplus_{k} b$ 为 $k$ 进制下的 $a,b$ 做按位的不进位的加法。你需要在 $n$ 次交互内猜出 $x$ 。
## 题解
**引理1**：
定义$a \ominus_{k} b$ 为k进制下的 $a,b$ 按位作不进位减法，
则$z = y \ominus_{k} x$

**证明**：

$\because x \oplus_{k} z=y $

$\therefore$ 设 $k$ 进制下 $x,y,z$ 的第 $i$ 位为 $x_{i},y_{i},z_{i}$ ，则对于每个 $i$ 都有 $(x_{i}+z_{i})$ $mod$ $k$ $=$ $y_{i}$ $mod$ $k$

$\therefore$ 对于每个 $i$ 都有 $(y_{i}-x_{i})$ $mod$ $k$ $=$ $z_{i}$ $mod$ $k$

$\therefore$ $z = y \ominus_{k} x$

**引理2**：

$(a \ominus_{k} b) \ominus (a \ominus_{k} c) = c \ominus_{k} b$

$(b \ominus_{k} a) \ominus (c \ominus_{k} a) = b \ominus_{k} c$

**证明**：

$\because$ $(a \ominus_{k} b) \ominus (a \ominus_{k} c) = c \ominus_{k} b$

$\therefore$ $(a-b)$ $mod$ $k$ $-$ $(a-c)$ $mod$ $k$ $=$ $(c-b)$ $mod$ $k$

$\therefore (a-b-a+c)$ $mod$ $k$ $=$ $(c-b)$ $mod$ $k$

$\therefore$ $(c-b)$ $mod$ $k$ $=$ $(c-b)$ $mod$ $k$

第二条可以用类似方法证明。

类似D1，我们需要构造一种询问方式使得之前的询问对现在没有影响。
由以上两个引理我们得出一种**构造方案**：

先输出 $0$ 并从 $1$ 枚举到 $n-1$ 。对于每个 $i$ ，若 $i$ 是奇数则输出 $(i-1) \ominus _{k} i$ ，反之则输出 $i \ominus _{k} (i-1)$ 。

**结论**：

这样当i为奇数x变为$x \ominus _{k} i$，反之变为$i \ominus _{k} x$。

**证明**：

**1 .** $i$ 为奇数，假设询问前x为 $(i-1) \ominus _{k} x$ ，则询问后 $x$ 变为$((i-1) \ominus_{k} i) \ominus ((i-1) \ominus_{k} x) = 
x\ominus_{k} i$（引理2）

**2 .**  $i$ 为偶数，假设询问前x为 $x \ominus _{k} (i-1)$ ，则询问后 $x$ 变为$(i \ominus_{k} (i-1)) \ominus (x \ominus_{k} (i-1)) = i\ominus_{k} x$（引理2）

**3 .** 对于我们的假设，可以将 $i$ 代入 $1$ 使得假设正确，再根据上面两个证明推得结论正确。

这样我们便能在i枚举到x时正确猜出x来。

---

## 作者：Cry_For_theMoon (赞：4)

[弱化版](https://codeforces.com/contest/1543/problem/D1)

[原版](https://codeforces.com/contest/1543/problem/D2)

又是豪华二合一题解呢。

这场被 ACD 一起吊打两小时。BTW，我是 $\gcd(x,0)=0$ 人 /cy

不说废话了。

先看 D1 $k=2$ 的情况。

一般位运算题按理说操作应该都是 $\log $ 级别，但是本题却允许我们 $n$ 次操作。根据经验，一般观察操作次数上界都能得到方向或者有用的结论。$n$ 次操作不难让我们想到从小到大或者从大到小一个一个猜。

假设我们从小到大猜，第 $i$ 次猜的数是 $q_i$.

考虑到异或性质 
$$
x \oplus z=y \Longleftrightarrow z=x\oplus y
$$
 也就是说猜了 $j$ 次后 $x$ 会变成 $x \oplus q_1 \oplus q_2 \oplus ... \oplus q_j$.

然后**如果初始密码为 $x$ 我们要在第 $x+1$ 次**猜中它，也就是说 $q_i=(i-1) \oplus q_1 \oplus ...\oplus q_{i-1}$.

然后发现这个东西是 $O(n^2)$  。

但是由于 $q_{i-1}=(i-2)\oplus q_1\oplus q_2 \oplus ... \oplus q_{i-2}$. 所以 $q_i$ 等号右边里 $q_1$ 至 $q_{i-2}$ 都被消掉（这是因为$a \oplus a=0$)。最后只剩下：
$$
q_i=(i-1) \oplus (i-2)
$$
于是在 $O(n)$ 的时间内解决了问题。

（我感觉 D1 比 C 难多了怎么都一眼秒切）

 然后看 D2，直觉告诉我们这种交互猜东西的题两问关联一定很强。

问题在于广义的 $k$ 进制不进位加法不满足自反律 $a \oplus a=0$. 所以 D1 解法失效。同样 $z=x \oplus y$ 也是失效的，变成了 $z=y \ominus x$. 这里 $\ominus$ 被定义为 $k$ 进制不退位减法。

然后我们不需要像题解里解法 $1$ 那样突然就想到了 $\ominus$ 的一些性质然后再分讨奇偶做出来。实际上还是可以利用 D1 的思想的延续。

显然 $q_1=0$ 依旧存在。考虑猜完 $q_1$ 以后 $x$ 会变成 $q_1 \ominus x$. 猜完  $q_2$ 后 $x$ 会变成 $q_2 \ominus (q_1 \ominus x)$. 因此得到结论：猜完 $j$ 次后，$x$

 会变成：
$$
q_j\ominus(q_{j-1}\ominus (q_{j-2}\ominus(...\ominus(q_1\ominus x))))
$$
所以 $q_{i}$ 必须为 
$$
q_{i-1}\ominus(q_{i-2}\ominus(...\ominus(q_1\ominus (i-1)))))
$$
 ~~请忽略最后右括号数量，我也不知道嵌套多少层~~

同样这个玩意还是 $O(n^2)$ 计算的。但是注意到 $q_{i-1} \ominus (q_{i-2}\ominus(...\ominus q_1)))$ 这个东西是可以一边算 $q$ 一边维护的，而那个 $(i-1)$ 完全可以拿到最外层，改变的只有其正负。更一般地，当 $i$ 为偶数时，里面那个 $(i-1)$ 拿出来是负数；$i$ 为奇数的时候，里面的 $(i-1)$ 拿出来是正数。所以令 $sum=q_{i-1}\ominus(q_{i-1}\ominus(...\ominus q_1)))$，则
$$
q_i=\begin{cases}sum \ominus (i-1) , 2\mid i \\ sum \oplus (i-1),2\nmid i \end{cases}
$$
特殊地，$q_1=0$.

写两个 $O(\log k)$ 算不进位加减法的函数。则总复杂度变为 $O(n \log k)$ .

```c++
#include<bits/stdc++.h>
#define rep(i,a,b) for(ll i=(a);i<=(b);i++)
#define per(i,a,b) for(ll i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
int T,n,k,q;
ll sum;
ll Add(int a,int b){
	ll ret=0,ans=0,base=1;
	rep(i,1,20){
		if(!a && !b)break;
		ll val=(a%k+b%k)%k;
		ret=ret+val*base;
		base*=k;
		a/=k;b/=k;
	}
	return ret;
}
ll Minus(int a,int b){
	ll ret=0,ans=0,base=1;
	rep(i,1,20){
		if(!a && !b)break;
		ll val=(a%k-b%k+k)%k;
		ret=ret+val*base;
		base*=k;
		a/=k;b/=k;
	}
	return ret;
}
int main(){
	cin>>T;
	while(T--){
		cin>>n>>k;
		sum=0;
		rep(i,1,n){
			if(i==1)q=0;
			else{
				if(odd(i))q=Add(sum,i-1);
				else q=Minus(sum,i-1);
			}
			cout<<q<<endl;
			int r;
			cin>>r;
			if(r==1)break;
			sum=Minus(q,sum);
		}
	}
	return 0;
}

```



---

## 作者：DaiRuiChen007 (赞：0)

# CF1543D2 题解



## 思路分析

先从 easy version 入手考虑：

先假设每次操作完不改变 $x$ 值，显然由于询问次数有 $n$ 次，因此每次我们询问 $0\sim n-1$ 即可。

那么在改变 $x$ 值的情况下，我们对于第 $i$ 次询问，只要询问在 $x$ 最初为 $i$ 的情况下经过若干次修改后得到的值即可。

注意到每次询问 $q$ 实际上就是让 $x$ 变成 $x\oplus q$，因此维护所有询问的 $q$ 的异或和即可。

接下来考虑 $k>2$ 的情况，类似上面的操作，我们依然考虑维护 $x$ 最初为 $i$ 时经过若干次修改后的值。

定义 $x\ominus_ky$ 为在 $k$ 进制下对 $x$ 和 $y$ 做不退位减法得到的值。

我们可以证明运算 $\oplus_k$ 和 $\ominus_k$ 均满足交换律结合律，并且有 $0\ominus_k(0\ominus_kz)=z$。

每当我们询问 $q$，$x$ 会变成 $q\ominus_kx$。

假设第 $i$ 次询问的数为 $q_i$，那么 $x$ 的变化为：$x\to (q_0\ominus_kx)\to(q_1\ominus_k q_0\oplus x)\to(q_2\ominus_k q_1\oplus_k q_0\ominus_k x)\to\cdots$。

因此我们分别维护前面的 $q_i\ominus_kq_{i-1}\oplus_kq_{i-2}\ominus\cdots$ 和 $x$ 的符号，每次询问 $i$ 的时候令 $x=i$ 并把两部分合并起来即可。

时间复杂度 $\Theta(n\log_kn)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+1;
int n,k;
struct node {
	int a[20];
	node(int x) {
		for(int i=0;i<20;++i) a[i]=0;
		int len=0;
		while(x) {
			a[len]=x%k;
			x/=k,++len;
		}
	}
	node() { node(0); }
	inline int& operator [](int i) { return a[i]; }
	inline friend node operator +(node A,node B) {
		node C;
		for(int i=0;i<20;++i) C[i]=(A[i]+B[i])%k;
		return C;
	}
	inline friend node operator -(node A,node B) {
		node C;
		for(int i=0;i<20;++i) C[i]=(A[i]+k-B[i])%k;
		return C;
	}
	inline int val() {
		int x=0;
		for(int i=0,p=1;i<20;++i,p*=k) {
			if(p>=MAXN) break;
			x+=a[i]*p;
		}
		return x;
	}
};
inline bool read(int x) {
	cout<<x<<endl;
	int ret; cin>>ret; return ret;
}
inline void solve() {
	cin>>n>>k;
	node sum(0);
	for(int i=0;i<n;++i) {
		node q=(i%2==0)?(sum+node(i)):(sum-node(i));
		if(read(q.val())) return ;
		sum=q-sum;
	}
}
signed main() {
	int T;
	cin>>T;
	while(T--) solve();
	return 0;
}
```



---

## 作者：pengyule (赞：0)

简单题。[easy](https://www.luogu.com.cn/problem/CF1543D1)/[hard](https://www.luogu.com.cn/problem/CF1543D2) version

从 easy version 入手找思路。应该很显然吧——题目说 $x\oplus z=y$ 那 $z=x\oplus y$。由异或的结合律可知，我们每次想询问“最初的数是不是 $x$ 啊？”的时候，只需要将问的 $x$ 输成 $x\oplus sum$，其中 $sum$ 表示之前的询问的 **输出值** 之异或和。原始的想问的“$x$”由 $0\sim n-1$ 枚举即可。

然而 hard version 中，$x\oplus z=y$ 不再等价于 $z=x\oplus y$，我们推导一下，若记第 $i$ 次询问的参数 $y$ 为 $y_i$：
$$
x\oplus z=(x+z)\bmod k\\
IF:x+z<k\\
THEN:y_1=x+z\to z=y_1-x=-x+y_1\\
IF:x+z\ge k\\
THEN:y_1=x+z-k\to z=y_1-x+k=-x+y_1
$$
对最后一个等号的解释：我们都知道 unsigned long long 基本上就是这个原理，这里我们的加减法都是在“unsigned $P=k$”中的，即一旦结果为 $c(c<k)$ 就变为 $k-c$，一旦结果大于 $k$ 就变为 $c\bmod k$。继续推导，$i=2$ 时：
$$
X(=x_{now})\gets -x+y_1\\
IF:X+z<k\\
THEN:y_2=X+z\to z=y_2-X=-X+y_2=x-y_1+y_2=x-(y_1-y_2)\\
IF:X+z\ge k\\
THEN:y_2=X+z-k\to z=y_2-X+k=-X+y_2=x-(y_1-y_2)
$$
下面 $i=3$ 时不再分类，因为显然两类在“unsigned $P=k$”中结果相同。
$$
X(=x_{now})\gets x-(y_1-y_2)\\
y_3=X+z\to z=y_3-X=-X+y_3=-x+(y_1-y_2+y_3)
$$
通过找规律，我们发现只需维护 $sum=y_1-y_2+y_3-y_4+\cdots$ 的值即可，再根据循环次数的奇偶性确定是 $y=x-sum$ 还是 $y=sum-x$。

总的来说，这道题的原理就是 $x\oplus sum=y\oplus sum\to x=y$。

最后提醒一句，所有的推导都是建立在“按位”基础上的，因此 $sum$ 的维护也是按位地加减 $\Delta y$ 的；unsigned $P=k$ 的维护方式是：减——$x'=((x-v)\bmod k+k)\bmod k$，加——$x'=(x+v)\bmod k$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int k;
int Minus(int x,int v){
	int ret=0,mi=1;
	while(x||v){
		int p=x%k,q=v%k;
		int z=((p-q)%k+k)%k;
		ret+=mi*z;
		mi*=k;
		x/=k,v/=k;
	}
	return ret;
}
int Add(int x,int v){
	int ret=0,mi=1;
	while(x||v){
		int p=x%k,q=v%k;
		int z=(p+q)%k;
		ret+=mi*z;
		mi*=k;
		x/=k,v/=k;
	}
	return ret;
}
int main(){
	int t,n;
	cin>>t;
	while(t--){
		cin>>n>>k;
		int sum=0,r;
		for(int i=0;i<n;i++){
			int ask=((i&1)?Minus(sum,i):Minus(i,sum));
			cout<<ask<<endl;
			cin>>r;
			if(r==1)break;
			if(i&1)sum=Minus(sum,ask);
			else sum=Add(sum,ask);
		}
	}
}
```



---

