# DIV + MOD

## 题目描述

Not so long ago, Vlad came up with an interesting function:

- $ f_a(x)=\left\lfloor\frac{x}{a}\right\rfloor + x \bmod a $ , where $ \left\lfloor\frac{x}{a}\right\rfloor $ is $ \frac{x}{a} $ , rounded down, $ x \bmod a $ — the remainder of the integer division of $ x $ by $ a $ .

For example, with $ a=3 $ and $ x=11 $ , the value $ f_3(11) = \left\lfloor\frac{11}{3}\right\rfloor + 11 \bmod 3 = 3 + 2 = 5 $ .

The number $ a $ is fixed and known to Vlad. Help Vlad find the maximum value of $ f_a(x) $ if $ x $ can take any integer value from $ l $ to $ r $ inclusive ( $ l \le x \le r $ ).

## 说明/提示

In the first sample:

- $ f_3(1) = \left\lfloor\frac{1}{3}\right\rfloor + 1 \bmod 3 = 0 + 1 = 1 $ ,
- $ f_3(2) = \left\lfloor\frac{2}{3}\right\rfloor + 2 \bmod 3 = 0 + 2 = 2 $ ,
- $ f_3(3) = \left\lfloor\frac{3}{3}\right\rfloor + 3 \bmod 3 = 1 + 0 = 1 $ ,
- $ f_3(4) = \left\lfloor\frac{4}{3}\right\rfloor + 4 \bmod 3 = 1 + 1 = 2 $

As an answer, obviously, $ f_3(2) $ and $ f_3(4) $ are suitable.

## 样例 #1

### 输入

```
5
1 4 3
5 8 4
6 10 6
1 1000000000 1000000000
10 12 8```

### 输出

```
2
4
5
999999999
5```

# 题解

## 作者：IYSY2009I (赞：4)

这道题我们先来观察一下 $f_a(x)$ 的性质：

 _下图紫色的点代表 $a=2$ 的变化，红色的点代表 $a=3$ 的变化，橙色的点代表 $a=4$ 的变化，棕色的点代表 $a=5$ 的变化，因为纯手绘，可能会有错误，大致理解即可。_ 
 
 ![](https://cdn.luogu.com.cn/upload/image_hosting/mil3d2qa.png)
 
 假设我们在这段函数上截取 $[l,r]$,可能会有 2 种情况：
 
1. 这段正好是一段一次函数且 $r$ 的纵坐标最大。我们容易发现，需要满足 $\left\lfloor\dfrac{l}{a}\right\rfloor=\left\lfloor\dfrac{r}{a}\right\rfloor$ 

1. 这一段满足 $r \bmod a=a-1$ 此时也是 $r$ 的纵坐标最大

1. 其它情况。经过观察图像后发现，最优解一定使 $\left\lfloor\dfrac{x}{a}\right\rfloor$ 或 $x \bmod a$ 最大，两者取 $\max$ 即可。

代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*f;
}
int _max(int x,int y){
	if(x<y) return y;
	return x;
}
void cf(){
	int l=read(),r=read(),a=read();
	if(r/a==l/a&&r%a>=l%a){
		printf("%d\n",r/a+r%a);
		return;
	}
	else{
		printf("%d\n",_max(r%a+r/a,a-1+r/a-1));
		return;
	}
	return;
}
int main(){
	int t=read();
	for(int i=1;i<=t;i++)
		cf();
	return 0;
}
```


---

## 作者：0xFF (赞：3)

#### 题目大意


------------
给定一个函数 $f_{a}(x)=\left\lfloor\frac{x}{a}\right\rfloor+x \bmod a$。给定 $l$,$r$,$a$， $l \le x \le r$，求出 $f_{a}(x)$ 的最大值。

#### 思路分析


------------
此题与 [P7909 [CSP-J 2021] 分糖果](https://www.luogu.com.cn/problem/P7909) 有异曲同工之妙，不过此题显然更加困难。

首先考虑 $x \bmod a$ 最大可以取到 $a-1$，所以最理想的状态就是令 $x \bmod a = a-1$ 的同时 $x$ 尽可能的大。所以就是找出距离 $r$ 最近的 $i$ 满足上述条件。不难求出此 $x = \left\lfloor\frac{r}{a}\right\rfloor \cdot a - 1$，若此 $x \ge l $ 则直接输出 $f_{a}(x)$ 即可。

那如果不满足条件（$x \le l$）输出多少呢？

不难想到我们肯定是让 $x$ 越大越好，那么我们直接输出 $f_{a}(r)$ 即可。

#### 代码实现


------------
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cstdlib>
#include<vector>
#define int long long
using namespace std;
const int N = 500050;
inline int read(){
	int x=0,f=1;char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
	for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
	return x*f;
}

signed main(){
	int T = read();
	while(T--){
		int l = read() , r = read() , a = read();
		if(r % a == a - 1){
			printf("%lld\n",r/a + r % a);
		}
		else if(r/a * a - 1 >= l){
			printf("%lld\n",(r / a * a - 1) / a + (r / a * a - 1) % a);
		}
		else {
			printf("%lld\n",r/a + r%a);
		}
	}
	return 0;
}
```


---

## 作者：Novice233 (赞：2)

这是一道非常简单的数学题。

不难发现，要想让 $i/a+i\bmod a$ ($l\leqslant i \leqslant r$) 尽量大，关键在于要让 $i\bmod a$ 取到最大。

最理想的情况就是 $i\bmod a$ ($l\leqslant i \leqslant r$) 可以取到 $a-1$。这种情况对应的要求是，$l/a \neq r/a$（$l$ 和 $r$ 不在同一周期内。

剩余状况，答案即为 $r/a+r\bmod a$。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,l,r,a;
int main(){
	cin>>t;
	while(t--){
		cin>>l>>r>>a;
		if(r/a!=l/a) cout<<a-1+(r-a+1)/a;
		else if(r<a) cout<<r;
		else cout<<r/a+r%a;
		cout<<endl;
	}
	return 0;
} 
```


---

## 作者：落花月朦胧 (赞：1)

# B. DIV + MOD

## 题意

给出 $l, r, a$, 求函数 $f(x) = \left\lfloor \frac{x}{a}  \right \rfloor\ + x \bmod a(l\leq x \leq r)$ 的最值。

## Solution

显然，可以把函数分成两部分来看。 对于第一部分要求 $x$ 要尽可能的大， 而对于第二部分要求 $x$ 尽量是 $a - 1$。

分成两种情况讨论，第一种情况是 $r - l \geq a$ ，根据鸽巢原理， $x$ 一定可以是 $a - 1$， 
第二种情况则相反，最优的选择应该是 $r$。

```cpp
/*
Writer: ZhengXiangYu
*/
#include <bits/stdc++.h>

using i64 = long long;

int main() {
//	std::ios::sync_with_stdio(false);
//	std::cin.tie(nullptr);
	auto solve = [&]() -> void {
		int a, l, r;
		scanf("%d%d%d", &l, &r, &a);
		
		int pos = 0;
		if (l / a != r / a) {
			for (int i = r; i >= l; i--) {
				if (i % a != a - 1) {
					i -= i % a;
				}
				if (i % a == a - 1) {
					pos = i;
					break;
				}
			}
		} else {
			pos = r;
		}
		std::cout << pos / a + pos % a << std::endl;
	};
	
	int T;
	std::cin >> T;
	while (T--) {
		solve();
	} 


	return 0;
}


```

---

## 作者：ZZQF5677 (赞：0)

### 题目意思
有一个公式是 $ f_a(x)=\left\lfloor\frac{x}{a}\right\rfloor + x \bmod a $，然后你需要在 $l_i$ 到 $r_i$ 区间内求最大的 $f_a(x)$。
### 解题思路
数学题。
+ 首先我们看 $l_i$ 到 $r_i$ 区间有没有能被 $a_i$ 整除还要减 $1$ 的数，至于为什么要减 $1$，那是因为按照公式，光是整除得到的商是不够的，虽然被除数减 $1$ 后再进行除法得到的商就少了 $1$，但可能余数就增加了不少，毕竟如果能够被整除的情况下余数等于 $0$。
+ 否则，那 $f_a(r)$ 得到的数就最大。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, a, l, r;
int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') {
      f = -1;
    }
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0', ch = getchar();
  }
  return x * f;
}
int main() {
  t = read();
  while (t--) {
    l = read();
    r = read();
    a = read();
    int ans = int(r / a) + (r % a);
    if ((r / a) * a - 1 >= l && (r / a) * a - 1 <= r) {  //在区间里面。
      int k = (r / a) * a - 1;
      ans = max(ans, int(k / a) + (k % a));
    }
    cout << ans << "\n";
  }

  return 0;
}

```

---

## 作者：Coros_Trusds (赞：0)

# 题目大意

共 $T$ 个询问。

每个询问，给定 $l,r,a$，求 $\max\limits_{l\le i\le r}\{\lfloor\dfrac{i}{a}\rfloor+i\bmod a\}$。

# 题目分析

题解中若无特殊说明，除法默认向下取整。

把求的部分分成两部分：$\lfloor\dfrac{i}{a}\rfloor$ 和 $i\bmod a$

若 $r/a=l/a$，说明区间内不管取哪个数第一部分都是相等的。此时答案要最大，第二部分自然为 $r\bmod a$，总答案为 $r/a+r\bmod a$。

若不等，可能答案可能为 $r/a+r\bmod a$，也可能是 $(r/a)-1+(\max\{i\bmod a\})$， $\max\{i\bmod a\}$ 显然最大为 $a-1$，所以另一情况是 $r/a-1+a-1$。答案为 $\max\{r/a-1+a-1,r/a+r\bmod a\}$。

感性理解：

`l = 1,r = 7:1 2 3 4 5 6 7`，`a=4`。

答案可能为 $7/4+7\bmod 4=1+3=4$，也可能为 $3/4+3\bmod 4=0+3=3$。最大值为 $4$。

# 代码

```cpp
//2022/3/8
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#define int long long
#define enter() putchar(10)
#define debug(c,que) cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) cout << arr[i] << w;
#define speed_up() cin.tie(0),cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define Abs(x) ((x) > 0 ? (x) : -(x))
const int mod = 1e9 + 7;
inline int MOD(int x) {
	while (x < 0) x += mod;
	while (x >= mod) x -= mod;
	return x;
}
namespace Newstd {
	char buf[1 << 21],*p1 = buf,*p2 = buf;
	inline int getc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1 ++;
	}
	inline int read() {
		int ret = 0,f = 0;char ch = getc();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getc();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getc();
		}
		return f ? -ret : ret;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;
using namespace std;

int T,l,r,a;
inline void solve() {
	l = read(),r = read(),a = read();
	printf("%lld\n",r / a == l / a ? l / a + r % a : max((r / a) - 1 + a - 1,r / a + r % a));
}
#undef int
int main(void) {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	#define int long long
	T = read();
	while (T --) {
		solve();
	}
	
	return 0;
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

本题应该算“半撞”了 CSP-J202 1的 T1，建议大家先做做[这道题（P7909）](https://www.luogu.com.cn/problem/P7909)再来。

很明显，P7909 已经帮我们解决了 $x\operatorname{mod}a$ 最大是多少的问题。我们可以证明，选能够满足 P7909 的最大的 $x$ 对于这道题也是最优的。

以下是我的 P7909 的代码：

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
long long n;
long long l;
long long r;
int main(){
	scanf("%lld%lld%lld",&n,&l,&r);
	if(r/n==l/n)printf("%lld\n",r%n);
	else printf("%lld\n",n-1);
	return 0;
}
```

我们可以发现，若 $\lfloor l\div a\rfloor=\lfloor r\div a\rfloor$，那没办法，只能选 $r$，因为此时无论是 $\lfloor x\div a\rfloor$ 还是 $x\operatorname{mod}a$ 都是最大的。

那么，我们可以证明：如果能够使得 $x\operatorname{mod}a=a-1$，那么就最好这样。并且，通过刚刚的特判，我们已经能保证满足条件了。

那么，为了使得 $\lfloor x\div a\rfloor$ 最大，$x$ 需要尽可能大。

换句话说，$x$ 是满足 $x\operatorname{mod}a=a-1$ 的小于等于 $r$ 的最大的数。

我们可以发现：

+ 当 $r\operatorname{mod}a=a-1$，就选 $r$；

+ 否则，选 $\lfloor x\div a\rfloor\times a-1$。

### 2 代码与记录

```cpp
#include<cstdio>
using namespace std;
int t;
long long l;
long long r;
long long a;
long long ans;
long long le(int x){
	if(x%a==a-1)return x;
	return x/a*a-1;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1650B_1.in","r",stdin);
	freopen("CF1650B_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%lld%lld%lld",&l,&r,&a);
		if(l/a==r/a)ans=r/a+r%a;
		else ans=le(r)/a+a-1;
		printf("%lld\n",ans);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/71017414)

By **dengziyue**

---

## 作者：ryanright (赞：0)

## Description

定义函数 $f_a(x)=\lfloor\frac x a\rfloor+x\bmod a$，给出 $a$、$l$、$r$，求 $f_a(x)$ 在 $[l,r]$ 内的最大值。

## Solution

这个函数是由两个量相加而成，因此它在一个区间内的最大值只有下面几种可能：（下面所有的“这个数”均指在区间内使得 $f_a(x)$ 最大的 $x$）

- $\lfloor\frac x a\rfloor$ 最大，在此前提下使得 $x\bmod a$ 最大。那么这个数就是 $r$，很明显它满足上面的两个条件。计算结果为 $(\lfloor\frac r a\rfloor+r\bmod a)$；
- $x\bmod a$ 最大，在此前提下使得 $\lfloor\frac x a\rfloor$ 最大。此时要分两种情况讨论：
  - $\lfloor\frac l a\rfloor=\lfloor\frac r a\rfloor$，即区间内所有数除以 $a$ 向下取整的结果都相同，那么这个数还是 $r$，计算结果依然为 $(\lfloor\frac r a\rfloor+r\bmod a)$；
  - $\lfloor\frac l a\rfloor<\lfloor\frac r a\rfloor$，那么这个数就是 $(r-1-r\bmod a)$，就是退一步，把 $\lfloor\frac x a\rfloor$ 减小 $1$，再让 $x\bmod a$ 拉满，让它等于 $(a-1)$。计算结果为 $(\lfloor\frac x a\rfloor+a-2)$。

综上所述，答案就是

$$\begin{cases}\lfloor\frac r a\rfloor+r\bmod a&,\lfloor\frac l a\rfloor=\lfloor\frac r a\rfloor\\\max(\lfloor\frac r a\rfloor+r\bmod a,\lfloor\frac x a\rfloor+a-2)&,\lfloor\frac l a\rfloor<\lfloor\frac r a\rfloor\end{cases}$$

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int l,r,a;
		scanf("%d%d%d",&l,&r,&a);
		if(l/a==r/a) printf("%d\n",r/a+r%a);
		else printf("%d\n",max(r/a+r%a,r/a+a-2));
	}
	return 0;
}
```

---

## 作者：_Fatalis_ (赞：0)

### Solution

显然在范围区间内变化大的是右边的 $x\bmod a$（为什么？）。

但也会出现 $\lfloor\frac{x}{a}\rfloor$ 变化的情况。那么，最大值就有两种情况了（即两个大幅度的变化区间，下见图片）：

1. 在小于等于 $r$ 的数中除以 $a$ 的余数最大。
2. 数 $r$。

![](https://cdn.luogu.com.cn/upload/image_hosting/idwg4828.png)

那么，若存在情况 1，则取最大值。若不存在，直接取情况 2 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int l,r,a;
		cin>>l>>r>>a;
		int x=r/a*a-1;
		if(x>=l) cout<<max(x%a+x/a,r%a+r/a)<<endl;
		else cout<<r%a+r/a<<endl;
	}
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

# $\text{CF1650B - DIV+MOD}$ 题解

## 题目大意

定义函数 $f_a(x)=\left\lfloor\dfrac{x}{a}\right\rfloor+x\bmod a$ ，也就是 $x\div a$ 的商和余数之和。

现在给定 $a,l,r$，求出 $f_a(x)$ 在 $l\le x\le r$ 时的最大值。

数据范围保证：$a,l,r\le 10^9$。

## 思路分析

一道很像 [CSP-J2021 T1 分糖果](https://www.luogu.com.cn/problem/P7909) 的水题。

首先把 $f_a(x)$ 拆成 $\left\lfloor\dfrac{x}{a}\right\rfloor$ 和 $x\bmod a$ 的和，发现 $\left\lfloor\dfrac{x}{a}\right\rfloor$ 不降，所以贪心地想，$x$ 肯定越接近 $r$ 越好。

同时还要考虑一下 $x\bmod a$ 的值，发现当 $x\equiv a-1\pmod a$ 时 $x\mod a$ 取得最大值，那么把这两个条件综合起来的最优解一定是 $f_a(r)$ 或者 $f_a\left(\left\lfloor\dfrac{r}{a}\right\rfloor\times r-1\right)$ 中的一个，注意到第二个就是满足 $x\equiv a-1\pmod a$ 时最大的 $x$。

然后记得判断一下 $\left\lfloor\dfrac{r}{a}\right\rfloor\times r-1$ 是否在 $[l,r]$ 之间就可以了。

剩下还有一点思维的细节，自己想一下应该就明白了。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int f(int a,int x) {
	return x/a+x%a;
}
inline void solve() {
	int l,r,a;
	scanf("%lld%lld%lld",&l,&r,&a);
	int ans=f(a,r),d=r/a*a-1; //d是最大化余数用的
	if(d>=l&&d<=r) ans=max(ans,f(a,d));
	//防止d越界 
	printf("%lld\n",ans);
	return ;
}
signed main() {
	int T;
	scanf("%lld",&T);
	while(T--) solve();
	return 0;
}
```



---

