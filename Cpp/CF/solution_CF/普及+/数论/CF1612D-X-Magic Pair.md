# X-Magic Pair

## 题目描述

You are given a pair of integers $ (a, b) $ and an integer $ x $ .

You can change the pair in two different ways:

- set (assign) $ a := |a - b| $ ;
- set (assign) $ b := |a - b| $ ,

 where $ |a - b| $ is the absolute difference between $ a $ and $ b $ .The pair $ (a, b) $ is called $ x $ -magic if $ x $ is obtainable either as $ a $ or as $ b $ using only the given operations (i.e. the pair $ (a, b) $ is $ x $ -magic if $ a = x $ or $ b = x $ after some number of operations applied). You can apply the operations any number of times (even zero).

Your task is to find out if the pair $ (a, b) $ is $ x $ -magic or not.

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
8
6 9 3
15 38 7
18 8 8
30 30 30
40 50 90
24 28 20
365 216 52
537037812705867558 338887693834423551 3199921013340```

### 输出

```
YES
YES
YES
YES
NO
YES
YES
YES```

# 题解

## 作者：_SeeleVollerei_ (赞：17)

题意：给一个数对 $(a,b)$，每次可以进行操作 $(a,b) \to (|a-b|,b)$ 或 $(a,|a-b|)$。问最后能否令 $a=x$ 或 $b=x$。$a,b,x \le 10^{18}$。

为了方便，我们假设 $a >b$，否则交换它们即可。

我们考虑第一步，可以达到两个状态 $(a-b,b)$ 和 $(a,a-b)$。

对于右边的状态 $(a,a-b)$，显然下一步能到达的状态为 $(b,a-b)$ 和 $(a,b)$。一个是走回去了，一个是和左边一样。

所以这两个状态我们可以当它们是等价的，直接判断一下右边这个状态然后往左边的跳即可。

考虑 $(a-b,b)$，如果 $a-b >b$，则可到达状态为 $(a-b-b,b)$ 和 $(a-b,a-b-b)$。

与上面是同样的道理，显然右边的状态可以到达左边。

**那么相当于一直让 $a$ 减去 $b$，直到 $a<b$，也就相当于令 $a$ 变为 $a\bmod b$。这有点像欧几里得算法求 $\gcd$。**

而 $a-b<b$ 时，直接令 $a'=b,b'=a-b$，继续往下递归即可。

递归的同时判断 $a-pb=x$，其实就相当于 $x<a$ 且 $x \equiv a \pmod b$。

然后每次由 $(a,b)$ 往 $(a\bmod b,b)$ 递归即可。

具体看代码实现。

```cpp
#include<cstdio>
typedef long long LL;
inline void Swap(LL&x,LL&y){
	LL tmp=x;
	x=y;y=tmp;
	return ;
}
inline bool Work(LL a,LL b,const LL x){
	if(a<b) Swap(a,b);
	if(a==x||b==x)
		return 1;
	if(!a||!b) return 0;
	if(x>a) return 0;
	if(x%b==a%b)
		return 1;
	return Work(a%b,b,x);
}
LL a,b,x;
int T;
int main(){
	for(scanf("%d",&T);T;T--){
		scanf("%lld %lld %lld",&a,&b,&x);
		if(Work(a,b,x)) puts("YES");
		else puts("NO");
	}
	return 0;
}
```

~~每次写题解都要审核三次以上，不愧是我。~~

---

## 作者：断清秋 (赞：8)

[题目传送门](https://www.luogu.com.cn/problem/CF1612D)

吐槽一下，这样例是什么东西，还不如不给……

定义一个状态为 $(a,b)$。 

令 $a<b$。

容易知道，$(a,b)$ 只能转化为 $(a,b-a)$ 或 $(b-a,b)$。然后能继续向下转移的只有 $(a,b-a)$。

然后推而广之，$(a,b)$ 可以转化为 $(a,b-ma)$。（$m$ 为正整数）

然后满足答案的情况只有两种：$a=x$ 或 $b-ma=x$。

因为 $b-ma=x \iff (b-x) \equiv0\pmod{a}$。

所以满足答案的条件是 $a=x$ 或 $ (b-x) \equiv0\pmod{a}$。

然后判断一下这两个条件是否成立即可，若都不满足则可以转移至 $(b \bmod a,a)$。

注意判断条件的时候应该有 $b \ge x$。

时间复杂度 $O(t \log n)$。

---

## 作者：bsdsdb (赞：2)

题意：对 $(a,b)$ 的一次操作定义为：

- $a\gets|a-b|$，或
- $b\gets|a-b|$

多次询问，求 $(x,y)$ 若干次操作后能不能有一个数为 $c$。

提示：

写个暴力，观察：

- 对于任意的 $x,y,c$，输入 $x\ y\ c$ 和 $y\ x\ c$，结果有何规律？如何证明？
- 对于任意的 $x,y<c$，输入 $x\ y\ c$，结果有何规律？如何证明？
- 对于任意的 $x>y,c$，输入 $x\ y\ c$ 和 $x\ x-y\ c$，结果有何规律？如何证明？
- 对于任意的 $x>y,k,c$，输入 $x\ y\ c$ 和 $x+ky\ y\ c$，结果有何规律？如何证明？

设 $(x,y)$ 的答案为 $P(x,y)$。注意到 $P(x,y)=P(y,x)$（可由定义和归纳法证明），因此只讨论 $x\ge y$ 的情况。又 $P(x,y)=P(x,x-y)$，因此可以默认 $y\le\frac{x}{2}$。考虑 $(x,y)$ 下一步要变成什么，可以是 $(x-y,y)$ 和 $(x,x-y)$，而后者下一步可以变成 $(y,x-y)$ 和 $(x,y)$，其中 $(x,y)$ 没意义，$P(y,x-y)=P(x-y,y)$，所以我们可以说：

$$
\begin{aligned}
P(x,y)=&[c=x]\lor[c=y]\lor P(x-y,y)\\
=&[c=x]\lor[c=x-y]\lor[c=x-2y]\lor\cdots\lor[c=x-ky]\lor[c=y]\\
&\lor P(x-ky,y), k=\lfloor\frac{x}{y}\rfloor\\
=&[c\equiv x\pmod y]\lor[c=y]\lor P(y,x\bmod y)
\end{aligned}
$$

然后辗转相除即可 $\mathcal O(\log x)$ 求出答案。

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(1, 2, 3, "inline", "Ofast")
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/exception.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/list_update_policy.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
// using namespace __gnu_pbds;
// tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>T;
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef long double ldb;
//#define umap unordered_map
#define umap __gnu_pbds::cc_hash_table
#define mkp make_pair
#define prque priority_queue
#define emp emplace
#define empb emplace_back
#define empf emplace_front
random_device rndv;
mt19937 rd(rndv());
const ll inf = 0x3f3f3f3f3f3f3f3fll;
const ldb eps = 1e-8;
const vector<ll> millerrabin = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
inline void enter(){putchar('\n');}
inline void space(){putchar(' ');}
inline ll readll(){ll ret=0,k=1;char c;do{c=getchar();if(c=='-'){k=-1;}}while(('0'>c)|('9'<c));do{ret=(ret<<3)+(ret<<1)+c-48;c=getchar();}while(('0'<=c)&(c<='9'));return ret*k;}
inline void read(ll&x){x=readll();}
inline char readchar(){char ret;do{ret=getchar();}while(ret<=32);return ret;}
inline void read(char&x){x=readchar();}
inline string readstr(){string ret;char c;do{c=getchar();}while(c<=32);do{ret+=c;c=getchar();}while((c>32)&(c!=EOF));return ret;}
inline void read(string&x){x=readstr();}
inline void write(ll x){if(!x){putchar('0');return;}if(x<0){putchar('-');x*=-1;}char op[20]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){putchar(op[cur--]);}}
inline ostream& operator<<(ostream& out, __int128 x){if(!x){out<<"0";return out;}if(x<0){out<<"-";x*=-1;}char op[40]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){out<<op[cur--];}return out;}
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ll a, b, tg;
bool fg = 0;

void srh(ll x, ll y) {
	if (fg) {
		return;
	}
	if (y > x) {
		swap(x, y);
	}
	if (tg > x) {
		return;
	}
	if (y == 0) {
		if (x == tg) {
			fg = 1;
		}
		return;
	}
	if (x % y == tg % y) {
		fg = 1;
		return;
	}
	srh(x % y, y);
}

void init() {
	fg = 0;
}
int mian() {
	read(a), read(b), read(tg);
	if (tg > a && tg > b) {
		puts("NO");
		return 0;
	}
	srh(a, b);
	if (fg) {
		puts("YES");
	} else {
		puts("NO");
	}
	return 0;
}

int main() {
	ll T;
	read(T);
	while (T--) {
		init();
		mian();
	}
	return 0;
}

;             ;;;;;;;;          ;
;                   ;          ; ;
;                  ;          ;   ;
;                 ;          ;     ;
;                ;          ;;;;;;;;;
;               ;          ;         ;
;              ;          ;           ;
;;;;;;;;;;;   ;;;;;;;;   ;             ;

   ;                        ;
  ;                          ;
 ;                            ;
;                              ;
;                              ;
;                              ;
 ;                            ;
  ;         ;;          ;;   ;
   ;        ;;          ;;  ;
```

---

## 作者：Genius_Star (赞：2)

### 题意：

题意：现有数对 $(a,b)$ 考虑两种操作：

- $a \to |a-b|$ 。

- $b \to |a-b|$。

问，是否可能经过一些变换，使得 $a=x$ 或 $b=x$。

### 思路：

自己手推一下，看起来每次都会延申出两种选择，而实际上状态之间的关系类似于：

![](https://cdn.luogu.com.cn/upload/image_hosting/6hpjrtnn.png)

也就是说，对于“支链”上面的数，我们“主链”上都有，所以，我们只需要枚举“主链”即可，对于主链就是我们不断将 $b \to b-a$，如果 $a>b$，那么交换一下继续减即可，我们写出了这样一个代码：

```cpp
while(a){
	if(x==a||x==b){
		f=1;
		puts("YES");
		break;
	}
	b-=a;
	if(a>b)
	  swap(a,b);
}
if(!f)
  puts("NO");
```

但是我们注意到 $a,b \le 10^{18}$，所以这样会超时，但是我们注意到这样的操作有点儿像“更相减损法”，那么我们就可以用欧几里得法来进行优化，即每次将 $b \to b \bmod a$，这样我们就省掉了中间大部分的减法，但是这样我们可能就无法判断中间是否有值是等于 $x$ 的。

但是我们注意到，只要 $x \equiv b\pmod a$，即 $x \bmod a=b \bmod a$，这样的话因为我们是不断将 $y-a$ 的，只要 $x \le b$，并且还和 $b$ 同余，不断减去 $a$ 的话是肯定可以得到等于 $x$ 的值的。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read(){ 
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll T,a,b,x;
int main(){
	T=read();
	while(T--){
		bool f=0;
		a=read(),b=read(),x=read();
		if(a>b)
		  swap(a,b);
		while(a){
			if(x%a==b%a&&x<=b){
				f=1;
				puts("YES");
				break;
			}
			b%=a;
			if(a>b)
			  swap(a,b);
		}
		if(!f)
		  puts("NO");
	}
	return 0;
}
```

---

## 作者：xujingyu (赞：1)

## 题意简述

给出一对数 $(a,b)$，每次可以将 $(a,b)$ 变为：

* $(|a-b|,b)$
* $(a,|a-b|)$

问能否使 $a$ 或 $b$ 等于 $x$。

## 解答

设 $a < b$。

所以能转移到：

* $(b-a,b)$
* $(a,b-a)$

发现只有 $(a,b-a)$ 能再进行转移。

所以最后就会变成 $(a,b-ka)$。

最终只要判断 $b-ka=x$ 或 $a=x$。

第一个也可以写成 $b-x\equiv 0 \pmod a$。

可以 $\mathcal O(1)$ 判断。接下来递归判断 $(b\bmod a,a)$ 即可。

---

## 作者：The_foolishest_OIer (赞：0)

可恶的样例毁我青春。

每次可以对 $(a,b)$ （设 $a \ge b$）进行两种操作，可以变为 $(b,a - b)$ 和 $(a,a - b)$。

对于第二种状态，下一步能达到的状态就是 $(a,b)$ 和 $(b,a - b)$。

所以我们只需要递归一种方案即可。

是不是很像辗转相减法？

递归的内容其他题解说得很详细了，我就不在赘述了。

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
int t,a,b,c;
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
bool work (int a,int b){
	if (a == c || b == c) return true;
	if (a == 0 || b == 0) return false;
	if (c > a) return false;
	if (c % b == a % b) return true;
	return work(b,a % b);
}
string change (bool x){
	if (x == true) return "YES\n";
	else return "NO\n";
}
void solve(){
	cin >> a >> b >> c;
	cout << change(work(max(a,b),min(a,b)));
} 
signed main(){
    close();
    cin >> t;
    while (t--) solve();
	return 0;
}
```

---

## 作者：zhangxiao666 (赞：0)

## 题意：
[题目传送门](https://www.luogu.com.cn/problem/CF1612D)

## 思路：
点开一看，诶，这长得好像辗转相除呀。

稍微推一推。

先假定 $a>b$。

首先 $(a,b)$ 可以到 $(a-b,b)$ 和 $(a,a-b)$。

看 $(a,a-b)$，可以到 $(b,a-b)$ 和 $(a,b)$，发现状态和之前重复，没有贡献，所以可以直接判一下，不用递归。

再看 $(a-b,b)$，假定 $a-b>b$ 可以到 $(a-2b,b)$ 和 $(a-b,a-2b)$，右边和之前一样，没有贡献，而左边可以一直推到 $(a-kb,b)$ 直到 $a<b$ 也就是 $(a\bmod b,b)$，那就成了求 $\gcd$ 的辗转相除法，直接递归即可，复杂度 $O(\log a)$。

## 代码：
不太难写，就是注意点细节。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

bool Check(int a, int b, int x)
{
	if (a < b) swap(a, b);
	if (a == x || b == x) return 1;
	if (!a || !b) return 0;
	if (x > a) return 0;
	if (a % b == x % b) return 1;
	return Check(a % b, b, x);
} 

signed main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T; cin >> T;
	while (T--)
	{
		int a, b, x; cin >> a >> b >> x;
		if (Check(a, b, x)) cout << "YES\n";
		else cout << "NO\n";
	}
	return 0;
}


```

---

## 作者：lovely_codingcow (赞：0)

## 思路
我们首先假定 $a < b$ ，那么我们可以通过题目给定的方式将 $(a,\,b)$ 转移到：

- $(b - a,\,b)$
- $(a,\,b- a)$

这是显然的。但是我们发现如果我们转化为 $(b - a,\, a)$，那么下一步就会转移到：

- $((b - a) - (b - a),\, a) = (0,\,a)$
- $(b - a,\, a - (b - a)) = (b -a,\, 2a - b)$

很显然这两种情况都是相当复杂且并不优的，于是我们只考虑转移到 $(a,\, b - a)$ 的情况。

在这种情况中，如果一直转换，就会变成 $(a,\,b - ka)$，其中 $k \in \mathbb{Z}^+$。

知道了转移方式，我们就只需要判断 $b - ka = x$ 或者 $a = x$ 即可，而 $b - ka = x$ 又可以被表达为 $b - x \equiv 0 \pmod a$，使得判断更为简单。此后类似辗转相除的递归 $(b \bmod a, a)$ 判断即可。

## 代码

```cpp
#include <iostream>

#define int long long

using namespace std;

int t, a, b, x;

bool check(int a, int b, int x) {
	if (b < a) {
		swap(a, b);
	}
	if (a <= 0 || b <= 0 || b < x) {
		return false;
	}
	if (a == x || (b - x) % a == 0) {
		return true;
	}
	return check(b % a, a, x);
}

signed main() {
	cin >> t;
	while (t--) {
		cin >> a >> b >> x;
		if (b < a) {
			swap(a, b);
		}
		if (check(a, b, x)) {
			cout << "YES\n";
		} else {
			cout << "NO\n";
		}
	}
}
```

---

## 作者：正负君 (赞：0)

## 题意

共 $t$ 组数据。

每组数据，给出一个数对 $(a,b)$ ，每次可以进行操作 $(a,b)$ 变为 $(|a-b|,b)$ 或 $(a,|a-b|)$ 。

问最后能否令 $a=x \wedge b=x$ 。

## 分析

首先保证 $a < b$ 。

如果 $x \bmod a = b \bmod a$ ，那么 $b - k a = x $ ，直接省去 $k$ 步。

无法跳步接着递归。

而当 $a=0 \wedge b=0$ 时，无论如何都不可能得到 $x$ 。

若 $x$ 都比较大数 $b$ 大，那么更不可能得到 $x$ 。

如下

$$
f(a,b)= \begin{cases}False &a=0\wedge b=0 \wedge x>b\\True& a=x\wedge b=x\wedge x\bmod a=b\bmod a\\ f(b\bmod a,a)&{Otherwise.}\end{cases}$$

注意 $ 1 \le a, b, x \le 10^{18} $ 开 ```long long int```

## 代码

```cpp
#include<iostream>
using namespace std;
#define int long long 
int T,a,b,x;
bool f(int a,int b)
{
  if(!a||!b||x>b)return false;
  if(a==x||b==x||x%a==b%a)return true;
  else return f(b%a,a);
}
signed main()
{
  cin>>T;
  while(T--)
  {
    cin>>a>>b>>x;
    if(a>b)swap(a,b);
    if(f(a,b))cout<<"YES\n";
    else cout<<"NO\n";
  }
  return 0;
}
```

---

## 作者：him的自我修养 (赞：0)

## 题意
给定 $(a,b)$ 两数，每次操作可以变为 $(a,|a-b|),(|a-b|,b)$ 两种状态之一。求能否达到 $a=x$ 或 $b=x$。

---
看这个操作，很容易想到和欧几里得算法比较像。

为了方便讨论，假设 $a>b$。

如果 $a=x$ 或 $b=x$，显然能够完成题目要求。对于 $x \bmod b=a \bmod b$，就相当于 $a-kb=x$，也能够完成题目要求。

在转移时，发现题目的操作更像是“更相减损”法，更相减损把就是把两个数相减，最终得到最大公约数。但显然欧几里得算法的复杂度更优秀，为 $O(\log n)$。把他优化成欧几里得算法，复杂度就变成了 $O(t \log n)$，完全能够通过。

## code
```
#include <bits/stdc++.h>
#define int long long
using namespace std;
bool ans(int a,int b,int x){
	if(a<b) swap(a,b);
	if(a==x || b==x) return true;
	if((!a || !b) || x>a) return false;
	if(x%b==a%b) return true;
	return ans(a%b,b,x);
}
signed main(){
	int t;cin >>t;
	while(t--){
		int a,b,x;cin >>a>>b>>x;
		cout <<(ans(a,b,x)?"Yes":"No")<<endl;
	}
	return 0;
}
```

---

## 作者：Little_Entropy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1612D)

首先对题面进行一下分析就会发现题面中有两种操作，假设当前两个数是 $(a,b)(a \geq b)$,则在下一步，会分别变成状况一：$(a-b,b)$ 或状况二：$(a,a-b)$，在下一步，第二种情况就会变成状况三：$(a,b)$ 或状况四：$(a-b,b)$,状况三会退回了初始状况，状况四与状况一相同，所以，题面中的两种操作是等价的，那么，接下来的叙述中，只考虑操作一。

$(a,b)$ 操作一之后变为 $(a−b,b)$，如果 $b\lt a-b$,则变为 $(a-2b,b)$,否则，变为 $(a−b,2b-a)$。

显然，我们只需要让 $a$ 变成 $a\mod b$,之后交换 $a$ 和 $b$ 的位置，再继续递归执行即可。

AC代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline bool dfs(long long a,long long b,long long x){
	if(a<b)swap(a,b);
	if(a==x||b==x)return true;
	if(a<x)return false;
	if(a==0||b==0)return false;
	if(x%b==a%b)return true;
	return dfs(a%b,b,x);
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	long long t;
	cin>>t;
	while(t--){
		long long a,b,x;
		cin>>a>>b>>x;
		if(dfs(a,b,x))puts("YES");
		else puts("NO");
	}
} 
```

---

