# [ABC298D] Writing a Numeral

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc298/tasks/abc298_d

文字列 $ S $ があり、初め $ S= $ `1` です。  
以下の形式のクエリが $ Q $ 個与えられるので順に処理してください。

- `1 x` : $ S $ の末尾に数字 $ x $ を追加する
- `2` : $ S $ の先頭の数字を削除する
- `3` : $ S $ を十進数表記の数とみなした値を $ 998244353 $ で割った余りを出力する

## 说明/提示

### 制約

- $ 1\ \leq\ Q\ \leq\ 6\ \times\ 10^5 $
- $ 1 $ 番目の形式のクエリについて、$ x\ \in\ \{1,2,3,4,5,6,7,8,9\} $
- $ 2 $ 番目の形式のクエリは $ S $ が $ 2 $ 文字以上の時にのみ与えられる
- $ 3 $ 番目の形式のクエリが $ 1 $ 個以上存在する

### Sample Explanation 1

$ 1 $ 番目のクエリにおいて、$ S $ は `1` なので ( $ 1 $ を $ 998244353 $ で割った余りに等しい) $ 1 $ を出力します。 $ 2 $ 番目のクエリにおいて、$ S $ は `12` になります。 $ 3 $ 番目のクエリにおいて、$ S $ は `12` なので ( $ 12 $ を $ 998244353 $ で割った余りに等しい) $ 12 $ を出力します。

### Sample Explanation 3

出力されるべき値は $ 998244353 $ で割った余りであることに注意してください。

## 样例 #1

### 输入

```
3
3
1 2
3```

### 输出

```
1
12```

## 样例 #2

### 输入

```
3
1 5
2
3```

### 输出

```
5```

## 样例 #3

### 输入

```
11
1 9
1 9
1 8
1 2
1 4
1 4
1 3
1 5
1 3
2
3```

### 输出

```
0```

# 题解

## 作者：CuteChat (赞：10)

博客体验区：https://www.luogu.com.cn/blog/zhangjinxuan/solution-at-abc298-d


本蒟蒻的第一篇题解，若什么地方不太正确，欢迎批评指出\~



## 原题大意

[原题链接](https://www.luogu.com.cn/problem/AT_abc298_d)

你要维护一个数字 $S$，起初，$S = 1$

现在你要按顺序来处理以下 $Q$ 次其一操作：

1. `1 x`  在 $S$ 的末尾添加非零数字 $x$
2. `2` 删掉 $S$ 的首位数字
3. `3` 输出 $S$ 的十进制表示，对 $998244353$ 取摸

最关键的数据范围：$1 <= Q <= 600000$

## 题目分析

首先，我们可以想一想，如果没有对 $998244353$ 去摸，也假设 C\+\+ 可以给我们存储很大的数字，我们该怎么做呢？

我们可以先记一个变量 `ans`，表示答案，**`ans` 一开始肯定要设为 $1$**。

- 如果是 1 操作，我们直接执行 `ans = ans * 10 + x` 就行。

- 如果是 2 操作，我们先获取 `ans` 的首位数字，并且获取它的所在位(从右往左），分别存储到 $x, y$，最后 `ans` 减去 `x * pow(10, y - 1)` 即可。

例如，我们设现在 `ans` 为 $114514$，我们得到的 $x, y$ 也就是 $1, 6$，`ans` 就减去 $1 \times 10^{6 - 1}$，也就是 $100000$，`ans` 减去这个数，刚好就是 $14514$。

- 如果是 3 操作，直接输出即可。



现在我们就有 1 个大问题：

**直接获取的复杂度是线性的，而线性会 TLE，所以，如何用 $O(1)$ 的时间复杂度获取 2 操作所需的首位数字以及所在位？**

这种情况我们就要使用一个新的容器来维护这个数字了，可以用什么呢？

对了！是**队列**！

我们获取首位数就是 `queue[front]`，而所在位数就是 `rear - front + 1` !

只要我们在操作一顺便 `queue[++rear] = x`，操作二执行完 `++front` 就能愉快地维护起这个队列啦！

同时，**不要忘了**一开始要 `queue[rear = front = 1] = 1` ……

然后加上取摸运算，也很简单，只要在适当的位置对 $998244353$ 取余即可。

例如，操作 1 执行完 `ans %= 998244353`，操作 2 中的 `x, y` 分别对它取余，`ans` 减了之后也对它取余……

不过，这样做仍然有一个问题，`ans` 执行操作 2 是可能会变成**负数**，但 C++ 普通的取余运算得到的结果也不是我们想的那样，所以，**我们还要自己写一个取余的函数**，具体实现见代码。

## 正解代码

本人在获取二操作的 $y$ 索性直接建了个变量 `len`，获取 `x * pow(10, y - 1)` 这一步骤也用了一个 $p$ 数组来算 ($p_i = 10^i \mod 998244353$，这样是为了更加方便，效率更高。

```cpp
#include <bits/stdc++.h>
using namespace std;

int q, st[600005], front, rear; // st 为队列
long long p[600005]; // p[i] = 10^i % 998244353
const long long mod = 998244353;
long long ans = 1; // 答案
int opt, n, len = 1; //len 表示当前数字长度，也就是 floor(log10(ans)) + 1

long long mymod(long long x) { //自定义的 mod 函数
	if (x >= 0) return x % mod; // 整数直接 mod
	else {
		return mod - (labs(x) % mod); //否则，就应该用绝对值来 mod，还要被模数减
	}
}

int main() {
	p[0] = 1; //10^0 = 1
	for (int i = 1; i <= 600004; ++i) {
		p[i] = p[i - 1] * 10;
		p[i] %= mod;
	}
	st[rear = front = 1] = 1; //一开始的数字是 1
	scanf("%d", &q);
	long long x = 0;
	while (q--) {
		scanf("%d", &opt);
		if (opt == 1) {
			scanf("%d", &n);
			ans = ans * 10 + n;
			ans %= mod; //注意模，这里无需考虑正负数
			st[++rear] = n;
			++len; //长度加了一个
		} else if (opt == 2) {
			x = st[front++]; //获取第一个数字
			x *= p[len - 1]; //获取应该要减去的数（这里似乎忘了 %，但好像没问题）
			--len; //长度减了一个
			ans -= x; 
			ans = mymod(ans); //这里可能是负数，必须用自定义的来模
		} else {
			printf("%lld\n", ans); //直接输出
		}
	}
	return 0; //愉快AC
}
```

本人 AC 记录：https://www.luogu.com.cn/record/108220243

### 注意 long long ！因为可能会爆 int！


## 总结

还是一道很普通的数学题，对取余运算这一块得要充分掌握，例如取余运算的分配律等等。

---

## 作者：STARSczy (赞：8)

# 题意：
有一个数 $S$，最开始为 $1$，输入 $N$ 次对它进行操作。有三种操作，分别为：

1. 输入 `1` 时，在末尾加上一位数 $x$;

2. 输入 `2` 时，删除开头的一位数;

3. 输入 `3` 时，输出这个数对 $998244353$ 取模后的结果。

# 做法：
观察可得，这个数很像队列。我们可以直接使用队列 $que$ 存储，再用一个同步变量 $T$ 存储当下的取模结果。

1. 对于操作 $1$：我们压入 $x$ 进入 $que$，同时，$T=(T + x)\mod 998244353$；

2. 对于操作 $2$：$T$ 直接减去 $10$ 的 $que$ 长度次方乘上队列 $que$ 的队头再模上 $998244353$。当然，$T$ 值现在有为负数的情况，所以我们要让此时的 $T=(998244353 + T)\mod 998244353$。最后让 $que$ 弹出首位元素；

3. 对于操作 $3$：直接输出 $T$。

# 代码：
```cpp
#include<bits/stdc++.h>
#define int __int128
using namespace std;

inline int read(){
	int x=0;
	bool w=1;
	char ch=getchar();
	while(ch<48||ch>57){
		if(ch==45) w=0;
		ch=getchar();
	}
    while(ch>47&&ch<58){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return w?x:(-x);
}

inline void write(int x){
	if(x<0){
		putchar(45);
		x=-x;
	}
	if(x>9) write(x/10);
	putchar(x%10+48);
}

inline int ksm(int n,int k,int mod){return k==1?n%mod:!k?1%mod:ksm(n*n%mod,k/2,mod)*(k%2?n:1)%mod;}
//快速幂，用来求10的n次方对模数取模的结果。

const int mod=998244353,maxn=6e5+10;
int ln,n=read(),now=1;
queue<int> que;

signed main(){
	que.push(1);
	while(n--){
		int t=read();
		if(t==1) que.push(read()),now=(now*10%mod+que.back())%mod,++ln;
		else if(t==2){
			now=(mod+(now-ksm(10,ln,mod)*que.front()%mod)%mod)%mod,--ln;
			que.pop();
		}
		else{
			write(now);
			putchar('\n');
		}
	}
	return 0;
}
```

---

## 作者：whx2009 (赞：6)

* [传送门](https://www.luogu.com.cn/problem/AT_abc298_d)
## 本题思路：
这道题我们可以用队列去模拟，按着题目的意思，如果是第 $1$ 种就直接在队尾加入数据，然后把原先答案翻 $10$ 倍再加上这个输入的数；如果是第 $2$ 种，我们就可以把答案减去队头的数字乘它的位置，然后弹出队头；如果是第 $3$ 种我们就可以直接输出答案。
## 本题代码：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int Mx=6*1e5;
const int mod=998244353;
int a[Mx]/*记录数列的位置*/,q/*问题个数*/,ans=1;
queue <int> h;//建队列 
signed main()
{
	int s=1;
	for(int i=1;i<=Mx;i++)//记录数列的位置 
	{
		a[i]=s;
		s=(s*10)%mod;
	}
	h.push(1);//头结点为1，因为s一开始只有一 
	scanf("%d",&q);
	while(q--)//记录每次问题 
	{
		int op,x;
		scanf("%lld",&op);
		if(op==1)
		{
			scanf("%lld",&x);
			h.push(x);//把这个数加入队尾 
			ans=(ans*10+x)%mod;//答案增加 
		}
		if(op==2)
		{
			ans=ans+mod-(a[h.size()]*h.front())%mod;//答案减去队头所在位置乘以队头的数字 
			ans%=mod;
			h.pop();//弹出队头 
		}
		if(op==3)
		 printf("%lld\n",ans);//输出答案 
	}
	return 0;
}
```
**请勿抄袭**

---

## 作者：Coffee_zzz (赞：5)

### 思路

发现在所有操作中，只会在 $S$ 的末位添加数和在 $S$ 的首位删除数，显然可以用队列模拟。

显然每进行一次操作 $1$ 或操作 $2$ 后，我们都可以直接求出此时 $S \bmod 998244353$ 的值，具体过程如下：

令 $a=S \bmod 998244353$。

设 $S$ 的末位为 $x$，进行操作 $1$ 时，只需要将 $a$ 修改为 $(10a+x) \bmod 998244353$。

设 $S$ 的位数为 $len$，$S$ 的首位为 $x$，进行操作 $2$ 时，只需要将 $a$ 修改为 $(a-x\times(10^{len-1}\bmod 998244353))\bmod998244353$。注意此时 $a$ 的值可能为负数，需要利用取模的特性将 $a$ 设为 $(a+998244353)\bmod998244353$，此时的 $a$ 即为正确的结果。

当执行操作 $3$ 时直接输出 $a$ 的值即可。

其中 $10^{n}\bmod 998244353$ 可以预处理求出

### 代码

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
namespace IO{
	char ibuf[(1<<20)+1],*iS,*iT;
	#if ONLINE_JUDGE
	#define gh() (iS==iT?iT=(iS=ibuf)+fread(ibuf,1,(1<<20)+1,stdin),(iS==iT?EOF:*iS++):*iS++)
	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read(){
		reg char ch=gh();
		reg long long x=0;
		reg char t=0;
		while(ch<'0'||ch>'9')   t|=ch=='-',ch=gh();
		while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=gh();
		return t?-x:x;
	}
}
using IO::read;
const int mod=998244353;
int p[600005],s[600005],l=0,r=1,q,ans;
signed main(){
	q=read();
	int id,x;
	p[0]=1,s[0]=1,ans=1;
	for(int i=1;i<=600000;i++) p[i]=p[i-1]*10%mod;
	for(int i=1;i<=q;i++){
		id=read();
		if(id==1){
			x=read();
			s[r++]=x;
			ans=(ans*10+x)%mod;
		}
		else if(id==2){
			ans=((ans-p[r-l-1]*s[l])%mod+mod)%mod;
			l++;
		}
		else{
			printf("%lld\n",ans);
		}
	}
	return 0;
}
```

---

## 作者：zajasi (赞：4)

## 题意
现在有 $3$ 个操作和一个数字 $a$。$a$ 初始为 $1$。

* `1 x`：在数字 $a$ 的末尾添加 $x$。如 $123$ 添加 $4$ 就变成了 $1234$。
* `2`：删除 $a$ 的最高位。如 $1234$ 就变成了 $234$。
* `3`：输出 $a$ 取模 $998244353$ 的结果。
## 解题思路
我们把题目简化一下。

* 对于操作 $1$，就是将原数 $a \times 10 + x$。
* 对于操作 $2$，定义 $y$ 为 $a$ 的长度。根据位值原理，易知要减去的就是 $x$ 的最高位乘 $10^{y-1}$（快速幂）。
* 对于操作 $3$，直接输出就行了。

不难发现，如果我们直接这样做的话，$a$ 的范围会超长整数类型。也就是说，我们需要在每一次操作 $1$ 处将 $a$ 取模 $998244353$。同理，当每次在操作 $2$ 的时候减去一个数后，也要模。如果出现了负数就加到非负数为止。

还有一个难点——如何求 $a$ 的最高位。我们可以记录一个队列或字符串或数组什么的，存一下每一次加进去的数。每次询问时取一个删一个即可。

详见代码。
## AC 代码
```cpp
/*
written by : zjs123
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long  
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
const int p=998244353;
int t;
int op;
int x;
string a;
int z=1;
int po(int x){
    int xx=10;
    int re=1;
    while(x){
        if(x&1)re=re*xx%p;
        xx=xx*xx%p;
        x/=2;
    }
    return re;
}
main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    a+='1';//刚开始是 1
    cin>>t;
    while(t--){
        cin>>op;
        if(op==1){
            cin>>x;
            a+=x+'0';//添加
            z=z*10+x;
            z%=p;
        }
        else if(op==2){
            z-=((a[0]-'0')*po(a.size()-1));//涉及到 10 的次幂，用快速幂
            z%=p;   
            while(z<0)z+=p;//加到非负数
            a.erase(a.begin());//删除最高位
        }
        else{
            cout<<z%p<<"\n";//直接输出
        }
//        cout<<z<<"\n";
    }
    return 0;
}

```



---

## 作者：Jerry_heng (赞：1)

（一）

这题可以运用同余的性质，预处理出每一位 $s_k=10^k \bmod\ 998244353$。

记录输入的每一位 $a_i$，第一位的下标 $be$，最后一位下标 $en$。

对于操作 1，$ans=ans\times10+x,en=en+1$。

对于操作 2，$ans=ans-a_{be}\times s_{en-be+1},be=be+1$。

其中 $en-be+1$ 是当前位数。

对于操作 3，输出  $ans$。

以上操作默认都是在 $\bmod\ 998244353$ 情况下。

（二）

AC 代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int md=998244353;
const int mx=6e5;
int q,s[mx],ans=1,be=1,en=1,a[mx];
signed main(){
	s[1]=1;
	a[1]=1;
	for(int i=2;i<=mx;i++)s[i]=(s[i-1]*10)%md;
	cin>>q;
	while(q--){
		int op,x;
		cin>>op;
		if(op==1){
			cin>>x;
			a[++en]=x;
			ans=(ans*10+x)%md;
		}
		if(op==2){
			ans=(ans-a[be]*s[en-be+1]+md*10)%md;
			be++;
		}
		if(op==3)cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：incra (赞：1)

### 题解
假设一个数 $\overline{A_1A_2A_3\dots A_n}$，取模于 $998244353$ 后是 $ans$。

那么对于操作 $1$，在这个数后面加上 $A_{n+1}$，也就是 $\overline{A_1A_2A_3\dots A_nA_{n+1}}$，同时更新答案 $ans\gets(ans\times10+A_{n+1})\bmod998244353$。

对于操作 $2$，删除头上的数，也就是删除 $A_1$，那么答案 $ans\gets{(ans-A_1\times 10^{n-1})\bmod 998244353}$（这里的取模要记得取正的，如一个数 $x$，取模于 $998244353$ 的结果就是 $(x\bmod 998244353+998244353)\bmod998244353$）。然后删除 $A_1$ 即可。

对于操作 $3$，输出 $ans$。

要找到一个数据结构支持删除头部元素而插入尾部元素的，可以使用 deque。

最后，我们要预处理出 $10^x\bmod 998244353$ 的结果，可以方便后续计算。
### 代码
```cpp
#include <iostream>
#include <deque>
using namespace std;
typedef long long LL;
const int N = 600010,MOD = 998244353;
int q;
LL ans = 1;
LL ten[N];
deque <int> Q;
int main () {
	ten[0] = 1;
	for (int i = 1;i < N;i++) ten[i] = ten[i - 1] * 10 % MOD;
	cin >> q;
	Q.push_back (1);
	while (q--) {
		int op;
		cin >> op;
		if (op == 1) {
			int x;
			cin >> x;
			Q.push_back (x);
			ans = (ans * 10 + x) % MOD;
		}
		else if (op == 2) {
			ans = ((ans - ten[Q.size () - 1] * Q.front ()) % MOD + MOD) % MOD;
			Q.pop_front ();
		}
		else cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：2huk (赞：1)

## 题目描述

我们有一个数字串 $S$，最开始 $S$ = `1`。

执行 $Q$ 次操作：

- `1 x` 将 $x$ 插入 $S$ 最后；
- `2` 删除 $S$ 的第一个数字；
- `3` 输出当前的 $S$。

## 数据范围

$1 \le Q \le 6 \times 10^5$

## 分析

对于这道题目，我们当然~~不~~可以按照题目要求模拟，定义一个字符串 $S$ 存储当前数字，对于第一个操作直接 `S.push_back(x)`，第二个操作直接 `S.erase(s.begin())`，第三个操作直接计算。

这样显然不可取，对于第二个和第三个操作都是 $\Theta(n)$ 的时间复杂度。

观察第一个和第二个操作，在末尾插入，在开头删除，正好是队列 `FIFO` 的性质。

接下来考虑队列 `queue`，以下为三种操作对应的实现过程：

1. 在末尾插入 $x$，可以 `q.push(x)`；
2. 删除第一个元素，也就是弹出队头元素，可以 `q.pop()`；
3. 输出当前的数字，可以在上面两个操作中顺带地求出 $res$，输出即可。

## 代码

```cpp
#include <iostream>
#include <cmath>
#include <queue>

using namespace std;

#define int long long

const int N = 1e6 + 10, P = 998244353;

int Q, op, x, res = 1;

queue<int> q;		// 队列 

int add(int a, int b)		// (a + b) % P 的值 
{
	return ((a % P) + (b % P) % P + P) % P;
}

int mul(int a, int b)		// (a ×b) % P 的值 
{
	return ((a % P) * (b % P)) % P; 
}

int fpm(int a, int b)		// (a ^ b) % P 的值 
{
	int res = 1;
	while (b)
	{
		if (b & 1) res = mul(res, a);
		b >>= 1;
		a = mul(a, a);
	}
	return res;
}

signed main()
{
	q.push(1);		// 开始队列中为 1 
	cin >> Q;
	
	while (Q -- )		// Q 次询问 
	{
		cin >> op;
		if (op == 1)		// 第一种操作：将 x 入队 
		{
			cin >> x;
			q.push(x);
			res = add(res * 10, x);
		}
		if (op == 2)		// 第二种操作：弹出队头元素 
		{
			res = add(res, -(q.front() * fpm(10, q.size() - 1)));
			q.pop();
		}
		if (op == 3)		// 第三种操作：输出答案 
		{	
			cout << res << '\n';
		}
	}
	
	return 0;
}
```


---

## 作者：ダ月 (赞：0)

### 题意概要：

一个序列 $S$，初始有 $1$。

你需要满足以下三种操作：

$1\ x$：将一个数字 $x$ 加到序列最后面；

$2$：删除 $S$ 最前面；

$3$：查询 $S$ 从前往后，由数位拼凑的数字。对 $998244353$ 取模。

### 题目分析：

对于加入最后面，删除最前面的操作，显然是让你维护一个队列。

若当前拼凑的数为 $k$，队列内有 $p$ 个元素。

对于操作 $1$，在将 $x$ 加入队列的同时，然后将 $k$ 更新成 $10k+x$；

对于操作 $2$，队列的首元素 $x$ 弹出，将 $k$ 更新成 $k-x\times10^{p-1}$，$10^{p-1}$ 用快速幂完成。

对于操作 $3$，直接输出即可。

### 代码如下：

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+10;
//===
//缺省源
//===
int len=0;
queue<int> q; 
ll ans=1;
const int mod=998244353;
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	q.push(1);int m;
	cin>>m;
	while(m--){
		int opt;cin>>opt;
		if(opt==1){
			int x;cin>>x;
			q.push(x),ans=(ans*10+x)%mod;
		}
		else if(opt==2){
			int k=q.front();q.pop();
			ans=(ans-k*QP(10,q.size(),mod))%mod;
		}else{
			ans=(ans+mod)%mod;
			printf("%lld\n",ans);
		}
	}return 0;
}






```


---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc298_d)        
比较简单的 deque 思维题。       
我们要维护的这个大数需要支持两种操作：在最后加入和删除最前面的数。          
所以很容易想到用 deque 来维护。               
我们让 deque 在从队尾到队头连接起来的数字为这个大数即可。          
但是，我们进行查询操作的时候每次遍历会很慢。     
我们设 $ans$ 为当前操作下的大数模 $998244353$ 的结果。        
那么，对于第一种操作，$ans=(ans\times10+x)\bmod 998244353$。       
对于第二种操作，我们需要取出队尾，将其设为 $b$，设当前大数长度为 $n$，则有 $ans=(ans-b\times10^{n-1})\bmod 998244353$。         
这里计算 $10$ 的幂的时候暴力可能会有些慢，所以我们使用快速幂解决。         
这里一定要注意负数取模的结果是正数。                
[CODE](https://www.luogu.com.cn/paste/pg0noo43)

---

## 作者：Unnamed114514 (赞：0)

赛时做出来的题中，时间最长的一道。~~不排除是 DDos 的原因~~

在前删除，在后加入，符合队列先进先出的特征，于是考虑用队列维护元素。

我们可以记录一个 $val$ 值表示当前的答案。

`1 x`：注意到这个操作我们直接在末尾添加元素，所以应该就是 $val\gets(val\times 10+x)\bmod p$。

`2`：设队列长度为 $len$，队首为 $x$，那么 $x$ 造成的实际贡献就是 $x\times 10^{len-1}$，因为是从 $0$ 开始算的，所以是 $len-1$，于是 $val\gets(val-x\times10^{len-1}\bmod p+p)\bmod p$。

`3`：直接输出 $val$ 即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+5,mod=998244353;
int q,val=1;
queue<int> que;
inline int qpow(int a,int b){
	int s=1;
	while(b){
		if(b&1)
			s=s*a%mod;
		b>>=1;
		a=a*a%mod;
	}
	return s;
}
signed main(){
	que.push(1);
	scanf("%lld",&q);
	while(q--){
		int op,x;
		scanf("%lld",&op);
		if(op==1){
			scanf("%lld",&x);
			val=(val*10+x)%mod;
			que.push(x);
		} else if(op==2){
			int t=que.front(),len=que.size();
			que.pop();
			val=(val-t*qpow(10,len-1)%mod+mod)%mod;
		} else
			printf("%lld\n",val);
	}
	return 0;
}
```

---

