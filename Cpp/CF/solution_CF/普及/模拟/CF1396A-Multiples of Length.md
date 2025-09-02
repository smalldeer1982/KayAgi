# Multiples of Length

## 题目描述

You are given an array $ a $ of $ n $ integers.

You want to make all elements of $ a $ equal to zero by doing the following operation exactly three times:

- Select a segment, for each number in this segment we can add a multiple of $ len $ to it, where $ len $ is the length of this segment (added integers can be different).

It can be proven that it is always possible to make all elements of $ a $ equal to zero.

## 样例 #1

### 输入

```
4
1 3 2 4```

### 输出

```
1 1 
-1
3 4
4 2
2 4
-3 -6 -6```

# 题解

## 作者：寒鸽儿 (赞：11)

构造题。  
我们可以通过在数值 $a_i$ 加上 $(n-1)a_i$ 将它变成 $n$ 的倍数。这样我们消耗一次操作就可以将 $n-1$ 个数变成 $n$ 的倍数。当我们选择区间为 $1$ , 不难发现可以在这个数上加上任意数 , 我们不妨加上 $n - a_i$ 将它变为 $n$ 。这样经过两次操作我们把所有数都变成了 $n$ 的倍数。最后一次操作就是选定区间长度为 $n$ , 由于所有数都是 $n$ 的倍数 , 它一定可以变成 $0$ 。  
```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
#define repp(i,a,b) for(int i=(a);i<(b);++i)
#define perr(i,a,b) for(int i=(b);i>(a);--i)

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> VI;
typedef vector<long long> VL;
typedef vector<double> VD;
typedef vector<int>::iterator itra;

const int maxn = 100010;
long long a[maxn];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
    long long n;
    cin >> n;
    rep(i,1,n) cin >> a[i];
    if(n == 1) {
        cout << 1 << ' ' << 1 << endl;
        cout << -a[1] << endl;
        cout << 1 << ' ' << 1 << endl;
        cout << a[1] << endl;
        cout << 1 << ' ' << 1 << endl;
        cout << -a[1] << endl;
    } else {
        cout << n << ' ' << n << endl;
        cout << n - a[n] << endl;
        cout << 1 << ' ' << n - 1 << endl;
        rep(i,1,n-1) {
            cout << ((n - 1) * a[i]) << ' ';
        }
        cout << endl;
        a[n] = n;
        cout << 1 << ' ' << n << endl;
        rep(i,1,n-1) {
            cout << -n * a[i] << ' ';
        }
			cout << -n << endl;
        cout << endl;
    }
    return 0;
}

```

---

## 作者：钓鱼王子 (赞：4)

根据题目性质，我们只能执行 $3$ 次操作，猜测肯定做一次 $1\sim n$ 的操作，且最后做。

那么我们应用前两次让所有数变为 $n$ 的倍数。

由于 $n-1$ 必定与 $n$ 互质，我们可以对一个长度为 $n-1$ 的区间执行操作，再对另一个长度为 $1$ 区间操作，使得全为 $n$ 倍数为止。

注意 $n=1$ 要特判。

```cpp
#include<bits/stdc++.h>
#define re register
#define int long long
using namespace std;
inline int read(){
	re int t=0,f=0;re char v=getchar();
	while(v<'0')f|=(v=='-'),v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return f?-t:t; 
}
int n,a[1000002],t,ans;
signed main(){
	n=read();
	for(re int i=1;i<=n;++i)a[i]=read();
	puts("1 1");
	printf("%lld\n",-a[1]);
	if(n==1){puts("1 1");puts("0");puts("1 1");puts("0");return 0;}
	a[1]=0;
	printf("%d %lld\n",2,n);
	for(re int i=2;i<=n;++i){
		re int x=a[i]%n+n;
		x%=n;
		re int y=x*(n-1);
		a[i]+=y;
		printf("%lld ",y);
	}puts("");
	printf("1 %lld\n",n);
	for(re int i=1;i<=n;++i)printf("%lld ",-a[i]);
	
}
```


---

## 作者：灵茶山艾府 (赞：2)

由于 $x+x*(n-1)=x*n$，所以得到如下构造方法：

1. 把 $a_1$ 加上 $-a_1$
2. 把从 $2$ 到 $n$ 的 $a_i$ 加上 $a_i*(n-1)$
3. 把从 $1$ 到 $n$ 的 $a_i$ 加上 $-a_i$

注意特判 $n=1$ 的情况。

AC 代码（Golang）：

```go
package main

import (
	"bufio"
	. "fmt"
	"os"
)

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var n int64
	Fscan(in, &n)
	a := make([]int64, n)
	for i := range a {
		Fscan(in, &a[i])
	}
	if n == 1 {
		Fprint(out, "1 1\n", -a[0], "\n1 1\n0\n1 1\n0")
		return
	}
	Fprintln(out, "1 1\n", -a[0])
	a[0] = 0
	Fprintln(out, 2, n)
	for i, v := range a[1:] {
		Fprint(out, v*(n-1), " ")
		a[i+1] += v * (n - 1)
	}
	Fprintln(out)
	Fprintln(out, 1, n)
	for _, v := range a {
		Fprint(out, -v, " ")
	}
}
```


---

## 作者：引领天下 (赞：2)

本题构造方法应该不止一种，这里给出一种。

首先是 $n=1$ 的时候的特判~~我跟别人说要特判然后自己没特判从而华丽丽的吃了一发罚时~~：

```
1 1
-a[1]
1 1
0
1 1
0
```

这个就不用我解释了吧。

然后是通用构造：

首先第一次操作选取区间 $\left[ 1,n-1 \right] $ ，挨个加上 $(n-1)\times(a_i\%n)$。

第二次操作对 $\left[ n,n \right] $ 强行微调：加上 $-(a_n\%n)$ 。

这样我们就可以最后一波操作解决啦：挨个加上 $-n\times \lfloor \frac{a_i}{n} \rfloor $。

```python
n=int(input())
a=list(map(int,input().split()))
if n==1:
    print(1,1)
    print(-a[0])
    print(1,1)
    print(0)
    print(1,1)
    print(0)
else:
    print(1,n-1)
    for i in range(n-1):
        x=(n-1)*(a[i]%n)
        print(x,end=' ')
        a[i]+=x
    print()
    print(n,n)
    print(-(a[-1]%n),end=' ')
    a[-1]+=(-(a[-1]%n))
    print()
    print(1,n)
    for i in range(n):
        print(n*-(a[i]//n),end=' ')
    print()
```


---

## 作者：PaRz1VaL (赞：1)

### 题意

给定一个序列，对序列进行三次以下操作，使序列中的所有元素都变成 $0$ 。

- 选择一个区间，将该区间中所有的数字加上区间长度的整数倍，区间中的每一个数字加的数可以不相等。

### 解法

可以把给定的整个区间划分为两部分，前 $n-1$ 个和第 $n$ 个，对于前 $n-1$ 个，给每一个数字都加上他本身的的 $n-1$ 倍后他们会变成自己的 $n$ 倍。

第 $n$ 个数由于区间长度为 $1$ ，可以直接将他转化为 $n$ 。

完成操作后整个区间都变成了 $n$ 的倍数，然后就可以减为 $0$ 了。

给定的序列只有1个数字的情况需要特判一下。

### 完整代码

```cpp
#include<cstdio>
typedef long long ll;
const int MAXN = 1e5+5;

int n;
ll num[MAXN];

int main() {

    scanf("%d",&n);

    if(n == 1) {
        scanf("%lld",&num[1]);
        printf("1 1\n");
        printf("%lld\n",-num[1]);
        printf("1 1\n0\n1 1\n0");
    }
    else {
        for(int i = 1; i <= n; i++)
            scanf("%lld",&num[i]);
        
        printf("1 %d\n",n-1);

        for(int i = 1; i < n; i++)
            printf("%lld ",num[i]*(n-1));
        puts("");

        printf("%d %d\n",n,n);
        printf("%lld\n",n-num[n]);

        printf("1 %d\n",n);
        for(int i = 1; i < n; i++)
            printf("%lld ",-num[i]*n);
        printf("%d",-n);
        puts("");
    }

    return 0;
}
```





---

## 作者：Tarsal (赞：1)

## [CF1397C](https://www.luogu.com.cn/problem/CF1396A)

$CF round 666$ 好神仙

### 题目大意

给定你一个长度为 $n$ 的序列。

你可以进行 $3$ 次操作。

每次可以选定一个区间，把这个区间的每个数都加上 $len \times x$

$1.$ 数 $x$ 是整数(可以为负)

$2.$ 对于区间的每个数可以取不同的 $x$

问你最后方案是什么。

### 输出格式

分 $3$ 段，每一段有 $2$ 行。

第一行 $2$ 个数表示区间 $l$ ~ $r$。

第二行 $r - l + 1$ 个数，表示加上的数，即 $len \times x$。

### 题解

考虑第一次我们只分区间 $1 ~ 1$ ，这样可以确保它变为 $0$。

第二次我们想把区间 $2 ~ n$ 的所有元素都变成 $n$ 的倍数。

对于 $a_i$ 我们可以把它加上一个 $n - 1$ 的倍数 ：$(n - 1) * a_i$

那么新的 $a_i$ 会变成 $a_i + (n - 1) * a_i$ 也就是 $a_i * n$ 那么就一定是 $n$ 的倍数。

而且这个对于所有的 $i \in [2, n]$ 都成立

最后就把 $1 ~ n$ 都减去 $a_i$ 就行了，因为 $a_i$ 已经都是 $n$ 的倍数了。

### 代码

```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <bits/stdc++.h>
#define maxn 100010
#define ls x << 1
#define rs x << 1 | 1
#define inf 0x3f3f3f3f
#define inc(i) (++ (i))
#define dec(i) (-- (i))
#define mid ((l + r) >> 1)
#define int long long
#define XRZ 1000000003
#define debug() puts("XRZ TXDY");
#define mem(i, x) memset(i, x, sizeof(i));
#define Next(i, u) for(register int i = head[u]; i ; i = e[i].nxt)
#define file(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout);
#define Rep(i, a, b) for(register int i = (a) , i##Limit = (b) ; i <= i##Limit ; inc(i))
#define Dep(i, a, b) for(register int i = (a) , i##Limit = (b) ; i >= i##Limit ; dec(i))
int dx[10] = {1, -1, 0, 0};
int dy[10] = {0, 0, 1, -1};
using namespace std;
inline int read() {
    register int x = 0, f = 1; register char c = getchar();
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
    return x * f;
} int a[maxn];
signed main() { int n = read();
	Rep(i, 1, n) a[i] = read();
	if(n == 1) {
		printf("1 1\n0\n");
		printf("1 1\n0\n");
		printf("1 1\n%d", -a[1]);
	}
	else if(n == 2) {
		printf("1 1\n%d\n", -a[1]);
		printf("2 2\n%d\n", -a[2]);
		printf("1 1\n0");
	}
	else if(n == 3) {
		printf("1 1\n%d\n", -a[1]);
		printf("2 2\n%d\n", -a[2]);
		printf("3 3\n%d\n", -a[3]);
	}
	else {
		printf("1 1\n%lld\n2 %lld\n", 0 - a[1], n);
		Rep(i, 2, n) {
			printf("%lld ", a[i] * (n - 1));
		} printf("\n1 %lld\n0 ", n);
		Rep(i, 2, n) printf("%lld ", 0 - a[i] * n);
	}
	return 0;
}
```

---

## 作者：45dinо (赞：1)

一个构造题。

可以想到，对于第二次操作后的 $n$ 个数，只要每一个数都是 $n$ 的倍数就行了。

然后发现，对于前 $n-1$ 个数进行一次操作，所有数都加上 $a_i\times(n-1)$，就会变成 $a_i\times n$。

只要把最后一个数变成 0 即可。

喜闻乐见的代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[100001];
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	if(n==1)
	{
		cout<<1<<" "<<1<<endl<<1<<endl;
		cout<<1<<" "<<1<<endl<<1<<endl;
		cout<<1<<" "<<1<<endl<<0-2-a[1]<<endl; 
		return 0; 
	} 
	cout<<1<<" "<<n-1<<endl;
	for(int i=1;i<=n-1;i++)
	{
		cout<<a[i]*(n-1)<<" ";
		a[i]*=n;
	}
	cout<<endl<<n<<" "<<n<<endl<<0-a[n]<<endl<<1<<" "<<n<<endl;
	a[n]=0;
	for(int i=1;i<=n;i++)
		cout<<0-a[i]<<" ";
	return 0;
}
```


---

## 作者：vectorwyx (赞：0)

一道有趣的构造题。

对于区间 $[L,R]$，用 $len$ 表示其长度，我们可以把 $a_{i}(L \le i\le R )$ 都加上 $len\times(len-1-a_{i})$

$\because$ $len\equiv 1$ $(mod \ len-1)$

$\therefore$ $a_{i}+len\times(len-1-a_{i})\equiv a_{i}+len-1-a_{i}=len-1$ $(mod\ len-1)$

因此此次操作后所有的 $a_{i}(L\le i\le R)$ 都会变成 $len-1$ 的倍数。

故而，我们先通过上述过程把区间 $[1,n]$ 中的元素都变为 $n-1$ 的倍数，然后对于区间 $[1,n-1]$ 和区间 $[n,n]$，分别加上原数的相反数。这样就能在三次操作内把原序列的元素都变为0。

另外要注意的一点是这个构造方法只适用于$n\ge 2$的情况，当 $n=1$ 时我们需要特判一下。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline ll read(){
	ll x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

const int maxn=1e6+5;
ll a[maxn];//加上的值最大是1e5 * 1e9，别忘了加longlong！

int main(){
	int n=read();
	fo(i,1,n) a[i]=read();
	if(n==1){
		puts("1 1");
		cout<<-a[n]<<'\n';
		puts("1 1");
		cout<<0<<'\n';
		puts("1 1");
		cout<<0<<'\n';
		return 0;
	}
	printf("%d %d\n",1,n);
	fo(i,1,n) printf("%lld ",1ll*n*(n-1-a[i])),a[i]+=1ll*n*(n-1-a[i]);
	puts("");
	
	printf("%d %d\n",1,n-1);
	fo(i,1,n-1) printf("%lld ",-a[i]),a[i]+=-a[i];
	puts("");
	
	printf("%d %d\n",n,n);
	cout<<-a[n]<<endl;a[n]+=-a[n];
	//fo(i,1,n) printf("%lld ",a[i]);
	return 0;
}
```


---

## 作者：KellyFrog (赞：0)

我们最终的目标状态可能是这样的：

```
0 4 8 -12 -4
```

之后我们再对 $[2,5]$ 进行一次操作就可以了。

于是我们进行如下的构造：

- 对 $[1,1]$ 进行操作，将 $a_1$ 变成 0
- 对 $[1,n]$ 进行操作，将 $[2,n]$ 中的数都变成 $n-1$ 的倍数
- 对 $[2,n]$ 进行操作，将 $[2,n]$ 中的数都变成 0

我们对第二步进行一下说明：

我们的目标是 $kn+a_i \equiv 0 \,(\operatorname{mod} (n-1))$。

由于 $n$ 和 $n-1$ 刚好差 1，所以这个方程的通解是 $k=(n-1)-(a_i\operatorname{mod}(n-1))$。

还需要判 $n=1$ 的情况，我就被罚了两次...

```cpp
#include <iostream>
#include <cstdio>

using namespace std;

typedef long long ll;

const int MAXN = 1e5 + 5;

ll a[MAXN];

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
	}
	if(n == 1) {
		puts("1 1\n0\n1 1\n0\n1 1");
		printf("%lld\n", -a[1]);
	} else {
		puts("1 1");
		printf("%lld\n", -a[1]);
		printf("1 %d\n0 ", n);
		for(int i = 2; i <= n; i++) {
			ll k = n - 1 - a[i] % (n - 1);
			a[i] += k * n;
			printf("%lld ", k * n);
		}
		puts("");
		printf("2 %d\n", n);
		for(int i = 2; i <= n; i++) {
			printf("%lld ", -a[i]);
		}
		puts("");
	}
}
```

---

## 作者：do_while_true (赞：0)

因为最多不超过三次，所以需要开放一下思维想怎么构造。

首先让序列所有数都变为 $0$ ，可以先让序列里面的数都是 $n$ 的倍数，最后一步 $l=1,r=n$，就可以把序列里面的数都削成 $0$ 。

那么怎么用两步把序列里面的数都变为 $n$ 的倍数呢？

把每一个数都看做他们对 $n$ 取余的数，这时候会发现，如果选择区间长度为 $(n-k)$，则这 $(n-k)$ 个数，每加上一个 $(n-k)$，对 $n$ 取余的结果相当于减去了 $k$ （如果为 $-x$ 则变为 $n-x$），因为每个数对 $n$ 取余的结果可能为 $0$ 到 $n-1$ 的任意一个，他们的公约数是 $1$ ，所以 $k$ 取 $1$ 一定能把 $(n-1)$ 个数里面的所有数都化为 $n$ 的倍数。

那么剩下的一次操作单独修改剩下的那个数即可，因为区间长度为 $1$ ，意味着可以随意修改。

记住特判 $n=1$，$a_i$ 可以为负数，开 ```long long```。

### $\mathcal{Code}$

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#define int long long
const int N=100010;
int n, a[N];
inline int read() {
	int r = 0,w = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') w = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		r = (r << 3) + (r << 1) + (ch ^ 48);
		ch = getchar();
	}
	return r * w;
}
signed main()
{
	n = read();
	if(n == 1) {
		puts("1 1\n0\n1 1\n0\n1 1");
		printf("%d", -read());
		return 0;
	}
	for(int i = 1; i <= n; ++i) 
		a[i] = read();
	printf("1 1\n%lld\n", (a[1] > 0 ? 1 : -1) * (n - abs(a[1]) %n ));
	a[1] += (a[1] > 0 ? 1 : -1) *( n - abs(a[1]) % n);
	printf("2 %lld\n", n);
	for(int i = 2; i <= n; ++i) {
		printf("%lld ", a[i] % n * (n - 1));
		a[i] += a[i] % n * (n - 1);
	}
	puts("");
	printf("1 %lld\n", n);
	for(int i = 1; i <= n; ++i) {
		printf("%lld ", -a[i]);
	}
	return 0;
}
```


---

## 作者：maruize (赞：0)

### **CF1396A/CF1397C Multiples of Length**

**题意**:

给你一个长度为$n$的序列$a$，你要通过进行三次以下操作使$a$全变成$0$:

- 选择$l$和$r(l<=r)$，令$len=r-l+1,b_i=k_i\times len (i\in[l,r],k_i$为任意自然数$)$，使$a_i-=b_i(i\in [l,r])$

可以证明可以使$a$全变成$0$.

**输入**

第一行$n$第二行$a_i$.

**输出**

共六行。

每两行中，

第一行$l$和$r$，

第二行$(r-l+1)$个数，为$b_i(i\in [l,r])$

$\ \ $

$\ \ $

---
**题解**

因为三这个数很小，考虑
- 第一次：把很长的一段(设长度为$x$)变成$y$的倍数 (尽量使$x,y=n|n-1$)。
- 第二次：把$y$个$y$的倍数消成$0$。
- 最后大致上剩下$1$个数$!=0$，把它消掉。

看起来还算靠谱...

重点在于第一步怎么做。

---

怎么做呢？

拿几组数据手算一下可以知道：

对于一个长度为$k$的序列$z_1..z_k$，若令$b_i=-z_i\times k$则操作后的$z$，$z_i=z_i \times (1-k)$

$\therefore$ 操作后的$z_i$满足$a_k\equiv 0(mod (k-1))$

于是就有了构造方法：

- First:$l=1,r=n,b_i=-a_i\times n $

- Second:$l=1,r=n-1,b_i=-a_i$

- Third:$l=2,r=n,b_i=0(i!=n)b_n=-a_n$

(在这里$a_i$在每步结束后$-=b_i$)

---

这里还有极其类似~~但麻烦~~的第二种方法：

(至于为什么有这个是因为我大概算错了还以为第一种方法不能用于偶数情况。。。~~直到写题解才发现~~)

- First:$l=1,r=n-1,b_i=a_i\times (n-1)$

- Second:$l=1,r=n,b_i=-a_i(i!=n),b_n=-a_n \div n \times n$

- Third:$l=n-abs(a_n)+1,r=n,b_i=0(i!=n),b_n=a_n$

(在这里$a_i$在每步结束后$-=b_i$,$\div$指整除)

code:
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
typedef long long LL;
using namespace std;
int a[100050];
#define LF "%lld"
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",a+i);
	if(n==1)//注意要特判
		{printf("1 1\n%d \n1 1\n0 \n1 1\n0 \n",-a[1]);return 0;} 
	if(/*n&1*/){//方法一
		printf("%d %d\n",1,n);
		for(int i=1;i<=n;i++)printf(LF" ",(LL)-a[i]*n);puts("");
		printf("%d %d\n",1,n-1);
		for(int i=1;i<n;i++)printf(LF" ",(LL)a[i]*(n-1));puts("");
		printf("%d %d\n",2,n);
		for(int i=2;i<n;i++)printf("0 ");
		printf(LF"\n",(LL)a[n]*(n-1));
	}
	else{//方法二
		printf("%d %d\n",1,n-1);
		for(int i=1;i<n;i++)printf(LF" ",(LL)a[i]*(n-1));puts("");
		
		printf("%d %d\n",1,n);
		for(int i=1;i<n;i++)printf(LF" ",-(LL)a[i]*n);
		//cout<<"\n|"<<a[n]-(LL)a[n]/n*n<<"|\n";
		if(abs(a[n])<=n)puts("0 ");
		else printf(LF" \n",-(LL)a[n]/n*n),a[n]=a[n]-(LL)a[n]/n*n;
		
		if(a[n]==0)puts("1 1\n0 \n");
		else{
			printf("%d %d\n",n-abs(a[n])+1,n);
			for(int i=n-abs(a[n])+1;i<n;i++)printf("0 ");
			printf("%d \n",-a[n]);
		}
	}
	return 0;
}



---

## 作者：stoorz (赞：0)

首先要求恰好修改 $3$ 次，很自然的想到选择一个位置 $k$，通过两次变换将 $[1,k]$ 和 $(k,n]$ 两个区间全部变为 $n$ 的倍数后，再通过一次操作将 $[1,n]$ 全部变为 $0$。

选定 $k=1$，那么第一次操作就将 $a[1]$ 加上 $n-a[1]$，~~显然这个数是 1 的倍数~~；然后要将 $[2,n]$ 中每一个数字加上若干个 $n-1$ 变为 $n$ 的倍数，那么对于其中一个数 $a[i]$ 加上 $(a[i] \bmod n)\times (n-1)$ 即可。

最后一次操作时 $a$ 全部变为 $n$ 的倍数，第 $i$ 个数加上 $a[i]$ 后数组全部为 $0$。

时间复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N=100010;
ll n,a[N];

int main()
{
	cin>>n;
	for (int i=1;i<=n;i++)
		cin>>a[i];
	if (n==1) return printf("1 1\n0\n1 1\n0\n1 1\n%d",(int)-a[1]),0;
	cout<<"1 1\n"<<n-a[1]<<"\n2 "<<n<<endl;
	a[1]=n;
	for (int i=2;i<=n;i++)
	{
		cout<<1LL*(a[i]%n+n)%n*(n-1)<<' ';
		a[i]+=1LL*(a[i]%n+n)%n*(n-1);
	}
	cout<<"\n1 "<<n<<endl;
	for (int i=1;i<=n;i++)
		cout<<-a[i]<<' ';
	return 0;
}
```

---

