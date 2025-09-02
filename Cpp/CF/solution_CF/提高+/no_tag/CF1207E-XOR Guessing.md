# XOR Guessing

## 题目描述

**这是一道交互题。**  
为了刷新你的输出，要使用 `fflush(stdout)` (对于C++)。

jury 随便想了一个在 $[0,2^{14}-1]$ 范围内的整数 $x$，你要猜出它是多少。

你可以进行至多两次询问，每次输出 $100$ 个 $[0,2^{14}-1]$ 范围内的整数 $a_1,a_2,...a_{100}$ 。需要注意的是，你输出的所有数必须两两不同。

作为回复，jury 会从你的每次输出中选一个数(你并不知道她选了哪个)，告诉你 $x$ 与其按异或的结果。

## 说明/提示

注意：样例输出是 **不正确的**。你的每次询问必须输出刚好 $100$ 的整数。

## 样例 #1

### 输入

```
0
32```

### 输出

```
? 3 5 6
? 32 24 37
! 5```

# 题解

## 作者：fsy_juruo (赞：8)

[CF1207E - XOR Guessing](https://codeforces.com/contest/1207/problem/E)

首先，设答案为 $X$，每次挑选到的两个数为 $A, B$，返回的异或值为 $C,D$，则可以得到以下两个方程：$X \text{ xor } A = C$，$X \text{ xor } B = D$。从而得到：$X \text{ xor } A \text{ xor } X \text{ xor } B = C \text{ xor } D$。由于 $X \text{ xor } X = 0$，故 $A \text{ xor } B = C \text{ xor } D$。

因此，我们只要构造出两个序列，使其满足：对于任意 $i, j$，满足 $A_i \text{ xor } B_j$ 唯一。就可以确定答案。

这样的序列很好构造。最简单的方法是：把第一个序列设为 $[1, 2, 3, \cdots, 100]$，第二个序列设为 $[1 \times 2^7, 2 \times 2^7, 3 \times 2^7, \cdots, 100 \times 2^7]$。这样子构造，第一个序列的前七位全为 $0$，第二个序列的后七位全为 $0$。二者不影响。则这个序列满足对于任意 $i, j$，$A_i \text{ xor } B_j = A_i + B_j$。明显，$A_i + B_j$ 是唯一的。

所以， 在询问到答案 $C, D$ 后，可以直接得到 $B = (C \text{ xor } D) \text{ Rsh } 7 \text{ Lsh } 7$。输出 $B \text{ xor } D$ 即可。

**代码：**

```cpp
#include <bits/stdc++.h>
#define _rep(i, x, y) for(int i = x; i <= y; i++)
#define _per(i, x, y) for(int i = x; i >= y; i--)
#define LL long long
using namespace std;
template <typename T>
inline void read(T &x) {
    x = 0;
    LL f = 1;
    char c = getchar();
    for (; !isdigit(c); c = getchar())
        if (c == '-')
            f = -1;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - 48;
    x *= f;
}
template <typename T>
inline void write(T x) {
	if(x < 0) {putchar('-'); x = -x;}
	if(x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
int a[101], b[101], x;
int main() {
	_rep(i, 1, 100) {
		a[i] = i;
		b[i] = (i << 7);
	}
	cout << "?";
	_rep(i, 1, 100) {
		cout << " " << a[i];
	}
	cout << endl;
	fflush(stdout);
	int c; cin >> c;
	cout << "?";
	_rep(i, 1, 100) {
		cout << " " << b[i];
	}
	cout << endl;
	fflush(stdout);
	int d; cin >> d;
	int b = (c ^ d) >> 7;
	cout << "! " << ((b << 7) ^ d) << endl; 
	return 0;
}
```



---

## 作者：rui_er (赞：6)

发现 $1\sim 100$ 的二进制表示只占了后 $7$ 位，而数据范围又很巧地是 $14$ 位，两次询问刚好。考虑每次询问确定出 $7$ 位来。

我们先询问 $1\sim 100$，这样每次的前 $7$ 位全是 $0$，不管选哪个数异或结果的前 $7$ 位都跟我们要猜的数相同，就可以确定前 $7$ 位。后 $7$ 位可以同理确定，最后把它们拼到一起就好了。

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
#define debug printf("Running %s on line %d...\n",__FUNCTION__,__LINE__)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}
int ask(int L, int R, int x) {
	printf("?");
	rep(i, L, R) printf(" %d", i<<x);
	puts("");
	fflush(stdout);
	scanf("%d", &R);
	return R;
}
void give(int x) {
	printf("! %d\n", x);
	fflush(stdout);
}

int main() {
	int A = ask(1, 100, 0);
	int B = ask(1, 100, 7);
	give((A>>7<<7)|(B&127));
	return 0;
}
```

---

## 作者：CNCAGN (赞：4)

## 题目描述
题意得知我们要猜测一个最大 $2^{14}-1$ 的确定的数字 $x$，只能两次猜测，并每次提供 $100$ 个数字。每次回复任意一个数与 $x$ 异或的结果。

## Solution
首先，它会选择 $100$ 个数字中任意一个数回复，那么我们就要保证一次询问中的每一个数与 $x$ 异或都能得到至少一半的答案有效位（二进制），而 $100$ 个数字还不能相同。

考虑每次询问获得 $7$ 位（二进制）有效答案，需要保证 $x$ 与 $100$ 个数字中任意一个数异或得到 $7$ 个不变的二进制位。最简单的，我们设计第一次询问的 $100$ 个数字的 $2^0$ 到 $2^6$ 位赋 $0$；设计第二次询问的 $100$ 个数字的 $2^7$ 到 $2^{13}$ 位赋 $0$，其余位随意赋值作为无效信息只需要保证不相同即可。

至此我们获得了 $x$ 的低七位和高七位答案，按位与去除无效信息加和即得答案 $x$。

## code
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<string>
#include<vector>
#include<queue>
#include<stack>
#include<deque>
#include<map>
using namespace std;
inline int red() {
    int op = 1, x = 0;
    char ch = getchar();
    while(!isdigit(ch)) {
        if(ch == '-')   op = -1;
        ch = getchar();
    }
    while(isdigit(ch)) {
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    return op * x;
}
int main() {
	cout << "? ";
	for(int i = 1; i <= 100; ++i) {
		int tmp = i;
		tmp = tmp << 7;
		cout << tmp << ' ';
	}
	puts("");
	fflush(stdout);
	int ans1 = red();
	
	cout << "? ";
	for(int i = 1; i <= 100; ++i) {
		int tmp = i;
		cout << tmp << ' ';
	}
	puts("");
	fflush(stdout);
	int ans2 = red();
	ans1 &= (1 << 7) - 1;
	ans2 &= ((1 << 7) - 1) << 7;
	cout << "! " << ans1 + ans2 << endl;
    return 0;
}

```


---

## 作者：览遍千秋 (赞：4)

### 这是一道交互题。

---

一共有两次询问机会，第一次询问的100个数二进制后7位下全都为1，第二次询问的100个数二进制前7位都为1.

这样无论系统返回哪个的xor值，都可以推算出这$[1,2^{14}-1]$范围内的数。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;

int aa,bb;

int a[107],tota;
int b[107],totb;
int x;
int main(){
	for(register int i=1;i<=((1<<14)-1);i++){
		if(((i&127)==127)&&tota<100){
			a[++tota]=i;
		}
		if((((i>>7)&127)==127)&&totb<100){
			b[++totb]=i;
		}
	}
	printf("?");
	for(int i=1;i<=100;i++){
		printf(" %d",a[i]);
	}
	puts("");fflush(stdout);
	cin>>aa;
	for(int i=0;i<7;i++){
		if(((aa>>i)&1)==0){
			x+=(1<<i);
		}
	}
	printf("?");
	for(int i=1;i<=100;i++){
		printf(" %d",b[i]);
	}
	puts("");fflush(stdout);
	cin>>aa;
	for(int i=7;i<14;i++){
		if(((aa>>i)&1)==0){
			x+=(1<<i);
		}
	}
	cout<<"! "<<x<<endl;
	return 0;
}
```

---

## 作者：ZMQ_Ink6556 (赞：2)

## 题解：CF1207E XOR Guessing

### 题意简述

你要向评测机提供两个长度为 $100$ 的序列，评测机会随机在两个序列中各挑选一个数 $a , b$，返回 $a \operatorname{xor} x$，$b \operatorname{xor} x$ 的值，让你确定 $x$ 的值。

### 解题思路

不妨先设前 $100$ 个数为 $1$ 到 $100$，发现只占用了后 $7$ 位二进制码，而前 $7$ 位二进制都没有使用，恰好 $x$ 的范围是 $2^{14}$，所以不管评测机选择哪个数，这个结果的前 $7$ 位二进制码就是最终答案 $x$ 的前 $7$ 位二进制码。

相同操作重复一遍，将所有的询问的 $100$ 个数乘以 $2^7$，会导致只占用前 $7$ 位，而后 $7$ 位为 $0$，依照上面的逻辑，将第一次询问的前 $7$ 位和第二次询问的后 $7$ 位拼接起来即为最终答案。

~~虽然我使用的是在 $0$ 到 $127$ 范围内随机 $100$ 个数。~~

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int x , y , q;
bool vis[205];
int main()
{
	srand(time(0));
	cout << '?';
	for(int i = 1 ; i <= 100 ; i++)
	{
		q = rand() % 127 + 1;
		while(vis[q])
		{
			q = rand() % 127 + 1;
		}
		vis[q] = 1;
		cout << " " << q;
	}
	cout << endl;
	cin >> x;
	memset(vis , 0 , sizeof(vis));
	cout << '?';
	for(int i = 1 ; i <= 100 ; i++)
	{
		q = rand() % 127 + 1;
		while(vis[q])
		{
			q = rand() % 127 + 1;
		}
		vis[q] = 1;
		cout << " " << (q << 7);
	}
	cout << endl;
	cin >> y;
	cout << "! " << ((((x ^ y) >> 7) << 7) ^ y) << endl; 
	return 0;
}
```

---

## 作者：No21 (赞：2)

### 解题思路

只能询问两次的交互题，卡的很死，但同时也降低了难度。因为次数限制，我们不能像对待常规的交互题一样去设计方案，那么我们就应该考虑本题特殊的运算——异或有什么优秀的性质。很自然的就能想到任何数异或 $0$ 都不变。再看，$2^{14}$，两次询问，对半折一下，$2^7=128$，正好大于 $100$。OK，那么接下来就好办了，第一遍求前 $7$ 位（保证前七位是零，具体怎么搞先自己思考一下，实在不会看代码里的注释），第二遍求后 $7$ 位（基本同上），两次答案一拼接就是最后的答案。

```
#include<bits/stdc++.h>
using namespace std;
namespace TO
{
    int ans1,ans2,mod=2*2*2*2*2*2*2;
    int mian()
    {
        cout<<"? ";
        for(int i=1;i<=100;i++)//100 小于 2^7，因此前 7 位全是 0。
            cout<<i<<' ';
        cout<<endl;
        cin>>ans1;
        ans1-=ans1%128;
        cout<<"? ";
        for(int i=1;i<=100;i++)
            cout<<i*128<<' ';//128 是 2^7，因此一直加 128 不会影响后 7 位，同时 2^14 是 128*128，因此不会超过限制。
        cout<<endl;
        cin>>ans2;
        ans2%=mod;
        cout<<"! "<<ans1+ans2<<endl;
        return 0;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    return TO::mian();
}
```

---

## 作者：yinqf (赞：2)

### Part1 题目大意

有一个在 $[0,2^{14}-1]$ 范围内的整数 $x$，你要猜出它是多少。\
你可以进行至多两次询问，每次询问输出 $100$ 个 $[0,2^{14}-1]$ 范围内的整数 $a_1,a_2,...a_{100}$ 。你输出的所有数必须两两不同。\
测评机会从你的每次输出的数中随机选一个数，告诉你 $x$ 与其异或的结果，但不告诉你和那个数进行异或。
你需要求出 $x$。

### Part2 做法介绍

人类智慧题

发现 $1 \sim 100$ 刚好占了 $7$ 位二进制，而 $x$ 又很巧是 $14$ 位二进制，两次询问分别求出前 $7$ 位和后 $7$ 位，最后再拼接在一起。

第一次询问 $1 \sim 100$，由于询问前 $7$ 位为 $0$，所以一定可以知道前 $7$ 位，后 $7$ 位同理，输出 $(1 \sim 100)\times 128$，得到后 $7$ 位。

### Part3 完整代码

```cpp
#include<bits/stdc++.h>
#define faster ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define LL long long
using namespace std;
int x,ans;
int main()
{
    cout << "? ";
    for(int i=1;i<=100;i++)
    {
        cout << i <<' ';
    }
    cout << endl;
    cin >> x;
    ans=x&32640;
    cout << "? ";
    for(int i=1;i<=100;i++)
    {
        cout << (i<<7) <<' ';
    }
    cout << endl;
    cin >> x;
    ans+=(x&127);
    cout << "! "<< ans << endl;
    return 0;
}
```

---

## 作者：WuMin4 (赞：1)

## [CF1207E XOR Guessing](https://codeforces.com/problemset/problem/1207/E)
## 思路

设答案为 $a$，第一次异或的数为 $b$，第二次异或的数为 $c$，则可以通过两次询问知道 $a \oplus b$ 和 $a\oplus c$，所以 $b\oplus c = (a \oplus b) \oplus (a\oplus c)$。

因为范围为 $[0,2^{14}-1]$，且每次询问只有 $100$ 次，所以可以让第一次询问 $\{1,2,\cdots,100\}$，第二次询问 $\{1\times 2^7,2\times 2^7,\cdots,100\times 2^7\}$，这样 $b$ 只会影响 $b\oplus c$ 的前 $7$ 位，$c$ 只会影响 $b\oplus c$ 的后 $7$ 位，进而可以通过分解 $b\oplus c$ 推出 $b,c$，通过 $(a\oplus b)\oplus b$ 或 $(a\oplus c)\oplus c$ 得到 $a$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int x1,x2,c1,c2;
signed main() {
	cout<<"? ";
	for(int i=1;i<=100;i++)
		cout<<i<<" ";
	cout<<endl;
	cin>>x1;
	cout<<"? ";
	for(int i=1;i<=100;i++)
		cout<<(i<<7)<<" ";
	cout<<endl;
	cin>>x2;
	cout<<"! "<<(x2^(((x1^x2)>>7)<<7))<<endl;
	return 0;
}
```

---

## 作者：Yc_cY (赞：1)

非常显然的水题。

设第一次询问的数组为 $a$，第二次为 $b$，注意到 $ 2^7 \gt 100 $，我们可以令 $a$ 中所有数满足二进制下 $1$ 至 $7$ 位均为 $0$，令 $b$ 中所有数满足二进制下 $8$ 到 $14$ 位均为 $0$。

具体的，对于 $\forall x \in a $，满足 $x \vee 127 = 0 $ 对于 $\forall y \in b $，满足 $x \vee ( 127 \times 2^7 ) = 0 $，设第一次答案为 $q_1$，第二次询问答案为 $q_2$，最终答案为 $ ( a \vee ( 127 \times 2^7 ) ) \wedge ( b \vee 127 ) ) $。

最简单的，取 $a_i = i $，$b_i = i \times 128 $ 即可。

code : 

```cpp
#include<bits/stdc++.h>
#define For( i , a , b ) for( register ll i = ( a ) ; i <= ( b ) ; ++i )
#define Rep( i , a , b ) for( register ll i = ( a ) ; i >= ( b ) ; --i )
#define ll long long 
using namespace std ;
int n , a , b ;
int main() {
	cout << "? " ;
	For( i , 1 , 100 ) cout << i << " " ; cout << endl ;
	cin >> a ; cout << "? " ;
	For( i , 1 , 100 ) cout << ( i << 7 ) << " " ; cout << endl ;
	cin >> b ;
	cout << "! " ;
	cout << ( ( a & ( 127 << 7 ) ) ^ ( b & 127 ) ) ;
	return 0 ;
}
```

---

## 作者：hgcnxn (赞：0)

## CF1207E XOR Guessing题解

### 思路

假设两轮询问中被选中参与异或的两个数为 $k$ 和 $m$，两次询问所得结果分别 $p$ 和 $q$：

那么有
$$\begin{cases}
x\oplus k=p\\
x\oplus m=q
\end{cases}$$

将两式异或，可得
$$k\oplus m=p\oplus q$$

由于 $p\oplus q$ 是已知的，所以我们要做的，**就是通过某种构造方式，推出 $k$ 和 $m$ 的值。**

为什么题目中所有数的值域在 $2^{14}$ 以内？为什么每次要询问恰好 $100$ 个数？它们之间有什么联系？

我们注意到，$2^7=128$，而 $128$ 比 $100$ 大一点。同时，$2^7$ 还是 $2^{14}$ 的算数平方根。也许，我们可以把 $2^{14}$ 拆成两个 $2^7$ 看待，用前七位推出 $m$，用后七位推出 $k$？没错！

我们第一次询问 $1$ 到 $100$ 之间的所有数，第二次询问 $1$ 到 $100$ 之间的所有数乘 $2^7$。这样，$p\oplus q$ 的后七位所构成的数就是 $k$，前七位构成的数乘 $2^7$ 就是 $m$。那么 $p\oplus k$ 和 $q\oplus m$ 都是 $x$ 的值，这道题也就结束了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int x[101],y[101],p,q,k,m;
int main(){
	for(int i=1;i<=100;i++){
		x[i]=i;
		y[i]=i<<7;
	}
	cout<<"?";
	for(int i=1;i<=100;i++)cout<<" "<<x[i];
	cout<<endl;
	cin>>p;
	cout<<"?";
	for(int i=1;i<=100;i++)cout<<" "<<y[i];
	cout<<endl;
	cin>>q;
	m=(p^q)>>7<<7;
	k=(p^q)%128;
	cout<<"! "<<(q^m)<<endl;
	return 0;
}
```

---

## 作者：wwxxbb (赞：0)

蒟蒻的第一道交互题！

## 题意

只有两次询问，每次只问 $100$ 个数，交互库随机选一个数并告诉你这个数异或它想的数的值，求它想的数。

## 思路

题目的数据范围很奇怪，上界是 $2^{14}$。

发现如果输出 $1\sim100$ 刚好能确定二进制下的 $7$ 位（$100<2^7$），因为前 $7$ 位都是 $0$，异或之后还是原值。这样的话两次询问刚好能够确定 $14$ 位，这也更加坚定这种构造是正确的。

所以，第一次询问，我们给出 $1\sim100$；第二次，我们给出 $2^7\times1\sim2^7\times100$。将两次的答案拼起来就是它想的数。

这个拼起来的操作可以用位运算，也可以~~暴力~~判每一位，如果用位运算的话要捋清楚条理还要注意一下优先级。

## 代码

```c++
#include <bits/stdc++.h>
using namespace std;

int main() {
	// ios::sync_with_stdio(0), cin.tie(0), cout.tie(0); // 有没有人告诉我为什么关流了就 ILE 了
	cout << '?';
	for (int i = 1; i <= 100; i++) cout << ' ' << i;
	cout << '\n';
	fflush(stdout);
	int a;
	cin >> a;

	cout << '?';
	for (int i = 1; i <= 100; i++) cout << ' ' << (i << 7);
	cout << '\n';
	fflush(stdout);
	int b;
	cin >> b;
    
	cout << "! ";
    cout << ((a ^ b) >> 7 << 7 ^ b);
    /* 或：
    // int ans = b;
	// for (int i = 7; i <= 13; i++) {
	// 	if (((ans >> i) & 1) && ((a >> i) & 1) == 0) ans ^= (1 << i);
	// 	if (((ans >> i) & 1) == 0 && ((a >> i) & 1)) ans ^= (1 << i);
	// }
	// cout << ans;
    */
    return 0;
}
```

---

## 作者：arrow_king (赞：0)

# 题意

**这是一道交互题。**

有一个整数 $x\in[0,2^{14}-1]$，你有两次询问机会，每次询问需要给出 $100$ 个两两不同的整数 $a_1,a_2,\dots,a_{100}\in[0,2^{14}-1]$，交互库会在这些数中选择一个数 $b$ 并告诉你 $x\oplus b$ 的结果。请用询问猜出 $x$。

# 思路

观察到 $100$ 的二进制有 $7$ 位，而答案区间有 $14$ 位。这不是一个巧合，而说明每次询问可以得到答案的 $7$ 位信息。

因此第一次询问的数只有最低的 $7$ 位上全 $0$，第二次询问的数只有最高的 $7$ 位上全 $0$，这样可以取得最高最低的 $7$ 位的值，将它们加起来即可。

# 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
#define ll long long
#define il inline
il ll read() {
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') {f=-1;} c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
ll a,b;
int main() {
	printf("? ");
	for(int i=1;i<=100;i++) printf("%d ",i);
	putchar('\n');fflush(stdout);
	a=read()&(127ll<<7);
	printf("? ");
	for(int i=1;i<=100;i++) printf("%d ",i<<7);
	putchar('\n');fflush(stdout);
	b=read()&127;
	printf("! %lld\n",a^b);
	return 0;
}

```

---

## 作者：cosf (赞：0)

简单题。

我们可以在第一次询问算出答案的前七位，第二次算出后七位。

因为 $2^7 \gt 100$，所以我们第一次询问 $1$ 到 $100$，那么，无论交互库选哪一个数，返回的结果的前七位一定是答案的前七位。

第二次，我们询问 $1 \times 128, 2 \times 128, \dots, 100 \times 128$，那么，返回的结果的后七位一定是答案的后七位。

## 代码

```cpp
#include <iostream>
using namespace std;

int main()
{
    cout << '?';
    for (int i = 1; i <= 100; i++)
    {
        cout << ' ' << i;
    }
    cout << endl;
    int x;
    cin >> x;
    cout << '?';
    for (int i = 1; i <= 100; i++)
    {
        cout << ' ' << (i << 7);
    }
    cout << endl;
    int y;
    cin >> y;
    cout << "! " << ((x & 16256) | (y & 127)) << endl;
    return 0;
}
```

---

## 作者：Register_int (赞：0)

最烦人的限制就是互不相同，因为如果没有这个限制，我们让所有 $a$ 都一样即可。

所以我们得想个办法忽悠交互库。此时可以只让这些数的一部分位相同，剩下部分不相同。所以容易想到，第一次询问将低 $7$ 位全设为 $0$，高 $7$ 位则为 $1\sim 100$；第二次询问将高 $7$ 位全设为 $0$，低 $7$ 位则为 $1\sim 100$。这样，两次询问都有 $7$ 位是固定的，将高低 $7$ 位合并即可得到答案。

# AC 代码

```cpp
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

const int MAXN = 2e5 + 10;

int n, x;

int main() {
	printf("?");
	for (int i = 1; i <= 100; i++) printf(" %d", i << 7); cout << endl;
	scanf("%d", &x), n = x & (1 << 7) - 1, printf("?");
	for (int i = 1; i <= 100; i++) printf(" %d", i); cout << endl;
	scanf("%d", &x), printf("! %d\n", n | x >> 7 << 7);
}
```

---

## 作者：Plozia (赞：0)

宣传博客 $\to$ [link](https://www.cnblogs.com/Plozia/p/16229210.html)

一道不错的思维题，不过这个 100 具有迷惑性，感觉改成 127 会方便做题，不过改成 100 也有其意义。

既然每次询问是随机一个数异或，因此我们要保证给出去的 100 个数要有相同点，由于猜测数二进制下只有 14 位，因此第一次询问前 7 位为 0，第二次询问后 7 位为 0，然后得到的两个答案一个能确定前 7 位一个能确定后 7 位。

至于构造询问，第一轮一百个数输出 1 到 100，这样保证前 7 位为 0，第二轮将这些数全部左移 7 位或者乘个 $2^7$，保证后 7 位为 0，最后回答时两个答案组合即可。

GitHub：[CodeBase-of-Plozia](https://github.com/Plozia/CodeBase-of-Plozia/blob/main/%E6%9D%82%E9%A1%B9/%E6%80%9D%E7%BB%B4%E9%A2%98%2B%E4%BA%A4%E4%BA%92%E9%A2%98/CF1207E%20XOR%20Guessing.cpp)

Code：

```cpp
/*
========= Plozia =========
	Author:Plozia
	Problem:CF1207E XOR Guessing
	Date:2022/5/5
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 100 + 5;
int a[MAXN], b[MAXN], ans1, ans2, ans;

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

int main()
{
	for (int i = 1; i <= 100; ++i) a[i] = i, b[i] = i * (1 << 7);
	printf("? "); for (int i = 1; i <= 100; ++i) printf("%d%c", a[i], " \n"[i == 100]);
	fflush(stdout); ans1 = Read();
	printf("? "); for (int i = 1; i <= 100; ++i) printf("%d%c", b[i], " \n"[i == 100]);
	fflush(stdout); ans2 = Read();
	printf("! %d\n", (ans1 >> 7 << 7) ^ (ans2 - (ans2 >> 7 << 7))); fflush(stdout); return 0;
}
```

---

## 作者：DerrickLo (赞：0)

我们先把 $x$ 补成一个 $14$ 位数，那么可以通过以下两次询问求出 $x$：

1. 询问 $1,2,\ldots 100$，那么 $x$ 的前 $7$ 位必然是答案的前 $7$ 位，因为 $1,2,\ldots 100$ 的前 $7$ 位都是 $0$，所以异或之后必然不变。

2. 询问 $1\times 2^7,2\times 2^7,\ldots 100\times 2^7$，那么同理 $x$ 的后 $7$ 位就是答案的后 $7$ 位。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int ans,x;
signed main(){
	cout<<"? ";
	for(int i=1;i<=100;i++)cout<<i<<" ";cout<<endl;
	cin>>x;
	for(int i=14;i>7;i--)if(x&(1<<(i-1)))ans+=(1<<(i-1));
	cout<<"? ";
	for(int i=1;i<=100;i++)cout<<i*128<<" ";cout<<endl;
	cin>>x;
	for(int i=7;i;i--)if(x&(1<<(i-1)))ans+=(1<<(i-1));
	cout<<"! "<<ans<<endl;
	return 0;
}
```

---

