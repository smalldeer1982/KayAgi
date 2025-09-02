# XOR and Triangle

## 题目描述

这次，粉色士兵们给了你一个整数 $x$（$x \ge 2$）。

请判断是否存在一个正整数 $y$ 满足以下条件：

- $y$ 严格小于 $x$
- 存在一个非退化三角形$^{\text{∗}}$，其边长为 $x$、$y$ 和 $x \oplus y$。其中 $\oplus$ 表示[按位异或运算](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)

若存在这样的整数 $y$，请输出任意一个满足条件的值。

$^{\text{∗}}$当边长为 $a$、$b$、$c$ 的三角形满足 $a + b > c$、$a + c > b$ 且 $b + c > a$ 时，该三角形是非退化的。

## 说明/提示

在第一个测试用例中，存在边长为 $3$、$5$ 和 $3 \oplus 5 = 6$ 的非退化三角形。因此 $y=3$ 是有效答案。

在第二个测试用例中，$1$ 是 $y$ 的唯一可能候选值，但无法构成非退化三角形。因此答案为 $-1$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
7
5
2
6
3
69
4
420```

### 输出

```
3
-1
5
-1
66
-1
320```

# 题解

## 作者：_xguagua_Firefly_ (赞：8)

### 分析

我们可以先按照非退化三角形（我的翻译器是这么给的）的定义，列出一个不等式组。

$$
\begin{cases}
x + y \gt x \oplus y \\ 
x + (x \oplus y) \gt y \\ 
y + (x \oplus y) \gt x
\end{cases}
$$

首先，第二个不等式是一定满足的，因为 $y \gt x$，并且 $x \oplus y \ge 0$，所以一定满足。再将第三个不等式移项，得到 $x \oplus y \gt x - y$。

所以，我们对 $y$ 的限制就是 $x + y \gt x \oplus y \gt x - y$。

先给出结论：$x + y \ge x \oplus y$，当且仅当 $x \operatorname{and} y = 0$ 取等，$x - y \le x \oplus y$，当且仅当 $x \operatorname{and} y = y$ 取等。

证明如下：

考虑异或运算的本质，就是不带进位的加法。所以，当出现两个数的同一位上都为 $1$ 的情况，则 $x + y$ 会因为进位高位比 $x \oplus y$ 大 $1$，若不存在这种情况，则 $x + y = x \oplus y$。同理，若两个数的同一位不同时为 $1$ 时，$x - y$ 的高位会因为借位比 $x \oplus y$ 少 $1$，若不存在同一位不同，则 $x - y = x \oplus y$。

因此，$y$ 需要在满足 $x \operatorname{and} y \neq 0$ 的同时 $x \operatorname{and} y \neq y$。我们考虑构造这个 $y$，因为 $y \lt x$，所以我们可以删除最高位的一个 $1$，同时将最低的一个 $0$ 变为 $1$。如果用这种构造构造出的 $y \ge x$，则无解。

我相信大家都能写出代码，所以不给了。

---

## 作者：A_R_O_N_A (赞：4)

神秘二进制构造题？并非神秘。

先思考一下什么情况是无解的：

1. 当 $x=2^k$ 时无解：

   因为 $y<x$，那么我们此时构造出来的 $y$ 的二进制可能的最高位一定是 $x$ 的二进制次高位，我们无法对 $x$ 的二进制最高位产生任何影响，又因为 $x=2^k$，所以除了最高位，其余位全部为 $0$，根据异或的运算规则，此时有 $x\oplus y=x+y$，所以我们构造出来的三个数一定是 $\{x,y,x+y\}$，显然有 $x+y=x+y$，无法构成三角形。

1. 当 $x=2^k-1$ 时无解：

   此时 $x$ 的二进制表示为 $k$ 个 $1$，且只有这 $k$ 个 $1$，根据异或的运算规则，我们构造出来的 $x\oplus y=x-y$。异或可以看作二进制下的不进位加法，因为异或的逆运算是本身，同样也可以看作不借位减法，而此时 $x$ 每一位都是 $1$，即二进制下一个位所能表示的最大数，自然不需要借位，所以此时 $x\oplus y=x-y$。所以我们构造出来的三个数一定是 $\{x,y,x-y\}$，显然有 $(x-y)+y=x$，无法构成三角形。

剩余的情况就是有解的了。如何构造？根据上文所说，异或可以看作不进位加法，那么我们可以构造一个最大的 $y=2^k-1$ 使得 $y<x$，此时 $y$ 在二进制下的表示为 $k$ 个 $1$，异或之后，我们显然没有异或掉 $x$ 二进制最高位的那一个 $1$。于是在新数中我们便自然地保留的最高位的那一个 $1$，然后我们又相当于对于 $x$ 的除了最高位的每一位都做了一次反转，设 $z=x \oplus y$，那么一定有 $y+z>x$ 以及 $x+y>z$，为什么呢？因为异或不进位，加法要进位啊！当 $x$ 与 $y$ 在某一位上都为 $1$ 时，两种运算结束后这一位都会变为 $0$，当 $x$ 与 $y$ 在某一位上不同时，两种运算结束后这一位都会变为 $1$。但是加法你要考虑进位，所以更高的一位就会多加一个 $1$，又因为我们判断掉了无解的情况，所以 $x$ 与 $y$ 必定在某一位上会进位，所以这样子下来加法完的数肯定大于异或完的数。$z$ 与 $y$ 同理，我们就很轻松地解决了这道题。

上面可能说的有些模糊，可以自己手造几个 $x$ 理解理解。


```cpp
inline void work(){//pw 是预处理好了的 2 的幂次数组
	x=read();
	for(int i=0;i<31;i++){
		if(x==pw[i]-1||x==pw[i]){
			puts("-1");
			return;
		}
	}
	for(int i=0;i<31;i++){
		if(x>(1<<i)-1&&x<(1<<(i+1))-1){
			cout<<(1<<i)-1<<"\n";
			return;
		}
	}
}
```

---

## 作者：liuzhenhao09 (赞：3)

直接 check 对于 $y=x-1,y=x-2,y=\lfloor{\frac{x}{2}}\rfloor$ 能否与 $x,x \oplus y$ 组成三角形即可。

复杂度 $O(T)$。

补充证明：

如果存在一个数 $x$ 使得其有解且没有被这三个数 check 到，则这三个数都是 $x$ 的子集或与 $x$ 无交。

如果 $x-1$ 是 $x$ 的子集，则 $x$ 的最低位是 $1$。

如果 $x-1$ 与 $x$ 无交，则 $x$ 是 $2$ 的整数次幂，此时原题显然无解，不考虑。

所以 $x$ 的最低位是 $1$。

如果 $x-2$ 是 $x$ 的子集，则 $x$ 的次低位是 $1$。

由于 $x$ 的最低位是 $1$，$x-2$ 一定与 $x$ 有交。

所以 $x$ 的次低位是 $1$。

如果 $\lfloor{\frac{x}{2}}\rfloor$ 是 $x$ 的子集，考察 $x$ 的最高位，其除以 $2$ 下取整后一定在下一位，所以下一位也是 $1$，以此类推，$x$ 一定是 $2$ 的整数次幂减 $1$，此时原题显然无解，不考虑。

所以 $\lfloor{\frac{x}{2}}\rfloor$ 与 $x$ 不交。考虑次低位除以二后一定会使最低位为 $1$，那就与 $x$ 有交了。矛盾。

故不存在这样的数。

---

## 作者：XZDZD (赞：3)

# [CF2074C XOR and Triangle](https://www.luogu.com.cn/problem/CF2074C)

# 二分做法
根据异或的规律我们不难发现，一个数异或它的一半的结果大于这个数本身，异或它的四分之一的结果会比刚才的小。

具体的证明本蒻给不出（悲）。

# AC Code

```cpp
#include<bits/stdc++.h>
#define ll long long
const int N = 1e5 + 10;
using namespace std;
ll n;
int main(){
	ios::sync_with_stdio(0);
	int T;
	cin>>T;
	while (T--) {
		cin>>n;
		if (n == 2){
			cout<<"-1"<<'\n';continue;
		} 
		ll l = 1,r = n;
		bool ok = true;
		while (l < r) {
			ll mid = (l+r)>>1;
			ll p = mid ^ n;
			if(p+mid > n && p+n > mid && mid+n > p) {
				cout<<mid<<endl;ok=false;ok1=false;break;
			}else {
				l = mid + 1; //单方向二分就可以了，这里是向上，下面有向下的。 
			}
		}
	/*  第二种二分办法 
		if(ok1){
			while (l < r) {
			ll mid = (l+r)>>1;
			ll p = mid ^ n2;
			if(p+mid > n && p+n > mid && mid+n > p) {
				cout<<mid<<endl;ok=false;break;
			}else {
				r = mid;
			}
		}
		}
	*/	
		if(ok) cout<<"-1"<<'\n';
	}
	return 0;
}
```

---

## 作者：_Kamisato_Ayaka_ (赞：2)

[Problem](https://www.luogu.com.cn/problem/CF2074C)

## Statement

给定 $x$，问是否存在 $y$，使得 $x,y,x\oplus y$ 可以构成一个三角形。

## Solution

记 $cnt = \operatorname{popcount(x)}$。

首先打表发现，当 $cnt = 1$ 和 $x = 2^{cnt}-1$ 时无解的。

因为 $cnt = 1$ 时如果说 $x$ 为 $1$ 的那一位 $y$ 并不为 $1$，$x + y = x \oplus y$，反之就是 $x + x \oplus y = y$，不满足。

$x = 2^{cnt} - 1$ 也同理。

然后依旧是打表，经过多组小数据的测试我们发现 $y = 2^{k} + 1$，也就是说我们去枚举 $0 \sim \log_2{x} - 1$ 找到任意一个 $y$ 就可以 $O(\log x)$ 实现。

## Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int Test, x;

inline bool Chk (int x, int y, int z) { return (x + y > z) && (x + z > y) && (y + z > x); }

inline void Solve() {
	cin >> x;
	int tot1 = __builtin_popcount(x);
	if (tot1 == 1) {
		cout << "-1" << endl;
		return;
	}
	if ((1 << tot1) - 1 == x) {
		cout << "-1" << endl;
		return;
	}
	int _x = x;
	for (int i = 0; i < log2(x); i ++) {
		if (!((x >> i) & 1)) {
			_x -= (1 << i);
			break;
		}
	}
	cout << _x << endl;
	return;
}

signed main() {
	cin >> Test;
	while (Test --) Solve();
	return 0;
}
```

---

## 作者：Nahida_Official (赞：1)

考场调了将近 1h，没绷住。

读完题目之后，容易写出以下大模拟：
```cpp
#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false)
using namespace std;
const int N=1e6;
int T;
int x,bits;
bool flag=true;
signed main(){
  IOS;
  cin>>T;
  while(T--){
    flag=true;
    cin>>x;
    for(int i=1;i<=x;i++){
      bits=x^i;
      if(x+i>bits && x+bits>i && i+bits>x){
        cout<<i<<'\n';
        flag=false;
        break;
      }
    }
    if(flag) cout<<"-1"<<'\n';
  }
  return 0;
}
```

然后就会喜提 TLE.....

那么正解有两个，找规律（位运算）或者二分，两种做法都是 $O(\log n)$ 的复杂度，运算量都很小。

这里说一下二分写法。

好吧其实就是普通二分，只不过加了一个 $\operatorname{check}$ 函数。

令 $l=1,r=x$，因为满足题目的数一定在 $1$ 和 $x$ 之间，如果 $\operatorname{check}$ 函数返回值为 true，那么代表答案可行，于是保存，如果二分结束仍然没有保存答案，那么直接输出 -1。

当然，$\operatorname{check}$ 函数也十分好写，只不过是一个普普通通的判断三角形函数。

~~就这个题我还卡了一个小时我真不食人~~

二分复杂度 $O(\log n)$，足以通过本题。

~~毒瘤数据范围~~
## Code:
```cpp
#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false)
using namespace std;
const int N=1e6;
int T,x;
int ans=-1;
bool check(int op){
  int bs=x^op;
  if(bs+x>op && bs+op>x && op+x>bs) return true;
  else return false;
}
signed main(){
  IOS;
  cin>>T;
  while(T--){
    ans=-1;
    cin>>x;
    int l=1,r=x;
    while(l<=r){
      int mid=(l+r)>>1;
      if(check(mid)){
        ans=mid;
        r=mid-1;
      }else{
        l=mid+1;
      }
    }
    cout<<ans<<'\n';
  }
  return 0;
}
```

---

## 作者：Bai_R_X (赞：1)

## 思路
赛时对的。

对于 $x$ 是 $2$ 的幂时，任意可能的 $y$ 都有 $x+y=x\oplus y$，明显无解。

然后为了使 $x+y>x\oplus y$，我们必须使 $x$ 和 $y$ 在（非 $x$ 的最高）二进制位必须存在一个相同的，使得 $x\oplus y<x+y$。

那我们不难想到构造一个二进制位全是 $1$ 且小于 $x$ 的 $y$，这样必定保证有相同。可以通过构造 $y=2^k-1$ 获得。

最后判断一下就可以。
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t,x,i,v;
signed main()
{
	cin>>t;
	while(t--)
	{
		cin>>x;
		if(!(x&(x-1)))
		{
			cout<<-1<<endl;
			continue;
		}
		v=1;
		while(v<=x)v<<=1;
		v>>=1;
		v--;
		if(x+v>(x^v)&&x+(x^v)>v&&v+(x^v)>x)cout<<v<<endl;
		else cout<<-1<<endl;
	}
	return 0;
}
```

---

