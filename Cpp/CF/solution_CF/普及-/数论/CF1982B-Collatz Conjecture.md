# Collatz Conjecture

## 题目描述

Recently, the first-year student Maxim learned about the Collatz conjecture, but he didn't pay much attention during the lecture, so he believes that the following process is mentioned in the conjecture:

There is a variable $ x $ and a constant $ y $ . The following operation is performed $ k $ times:

- increase $ x $ by $ 1 $ , then
- while the number $ x $ is divisible by $ y $ , divide it by $ y $ .

 Note that both of these actions are performed sequentially within one operation.For example, if the number $ x = 16 $ , $ y = 3 $ , and $ k = 2 $ , then after one operation $ x $ becomes $ 17 $ , and after another operation $ x $ becomes $ 2 $ , because after adding one, $ x = 18 $ is divisible by $ 3 $ twice.

Given the initial values of $ x $ , $ y $ , and $ k $ , Maxim wants to know what is the final value of $ x $ .

## 说明/提示

In the first test case, there is only one operation applied to $ x = 1 $ , resulting in $ x $ becoming $ 2 $ .

In the second test case, for $ x = 2 $ , within one operation, one is added to $ x $ and it's divided by $ y = 3 $ , resulting in $ x $ becoming $ 1 $ .

In the third test case, $ x $ changes as follows:

- After the first operation, $ x = 1 $ , because $ 24 + 1 = 25 $ and $ 25 $ is divisible by $ y = 5 $ twice within one operation.
- After the second operation, $ x = 2 $ .
- After the third operation, $ x = 3 $ .
- After the fourth operation, $ x = 4 $ .
- After the fifth operation, $ x = 1 $ .

## 样例 #1

### 输入

```
13
1 3 1
2 3 1
24 5 5
16 3 2
2 2 1
1337 18 1
1 2 144133
12345678 3 10
998244353 2 998244353
998244353 123456789 998244352
998244354 998241111 998244352
998244355 2 9982443
1000000000 1000000000 1000000000```

### 输出

```
2
1
1
2
3
1338
1
16936
1
21180097
6486
1
2```

# 题解

## 作者：gaomingyang101011 (赞：4)

# CF1982B Collatz Conjecture 题解

## 思路

这道题我们只需每一次进行一个循环，每次讲 $x$ 的值加一，能整除 $y$ 就除到底。但看到数据是范围 $10^9$ 那我们就得对这个思路进行简化：

- 我们可以在一次操作中直接将 $x$ 加到能整除 $y$，然后再除以 $y$。
  
- 我们在 $x$ 的值为一时可以直接跳出循环，然后在循环外面处理还未完成的操作。
  

下面是代码，有不懂的可以根据代码来理解，还是比较简单的。

## 代码

```cpp
#include<iostream>
using namespace std;
long long t;
long long x,y,k;
// 变量名称都与题目中含义相同 
int main(){
	cin>>t;
	while(t--){
		cin>>x>>y>>k;
		while(k>0&&x!=1){
			int s=min(k,y-(x%y));
			k-=s;
			x=x+s;
			// 一次性加到能被整除，节约时间 
			while(x%y==0) x/=y;
		}
		k%=(y-1);
		x+=k;
		// 因为前面是在x=1时就跳出了while
		// 所以可能少进行了几次操作 
		if(x%y==0) x/=y;
		// 前面操作完之后x可能能被y整除 
		cout<<x<<endl;
	} 
	return 0;
}
```

---

## 作者：mynxzh (赞：3)

## 题解

场切了。

怎么还没有翻译。那我就说一下题面大概什么意思吧。

题面就是说我们有一个 $x$ 和一个 $y$。进行以下操作 $k$ 次：

- 将 $x$ 增加 $1$。
- 当数字 $x$ 可以被 $y$ 整除时，将其除以 $y$。

直接模拟显然是不行的。

那怎么办呢？

可以比较剩余操作次数 $k$ 和使 $x$ 成为 $y$ 的倍数所需的操作次数。为了使 $x$ 成为 $y$ 的倍数，需要增加 $q$ 次，其中 $q$ 取 $k$ 和 $y - x \bmod y$ 之间的最小值。然后将 $x$ 增加 $q$，将 $k$ 减去 $q$，直到 $k$ 次操作结束或者 $x$ 已经变为 $y$ 的倍数。

如果剩余的 $k$ 不为 $0$，并且 $x$ 不为 $1$，就要继续操作。将 $k$ 对 $y-1$ 取模，然后将结果加到 $x$ 上，这样就能得到最终的结果啦。

```cpp
#include <bits/stdc++.h>
#define ull unsigned long long

int32_t main() {
    ull t;
    std::cin>>t;
    while(t--){
        ull x,y,k ;
	    std::cin>>x>>y>>k ;
	    while(1){
	    	if(k==0||x==1){
	    		break;
			}
			else{
				ull q=std::min(k,y-(x%y));
		        x+=q;
		        k-=q;
		        while(x%y==0){
		            x/=y;
		        }
			}
	    } 
	    k=k%(y-1);
	    x+=k ;
	    std::cout<<x<<'\n';
    }
    return 0;
}

```

---

## 作者：zengxuheng (赞：2)

# 题意：
[题目传送门](https://www.luogu.com.cn/problem/CF1982Be)

# 思路
首先想到的是模拟，结果一看数据范围：$1 \le x, k \le 10^{9}$，$ 2 \le y \le 10^{9} $，瞬间死心了。

于是可以优化一下，如果我们每次直接把 $x$ 加到 $y$ 的倍数，然后除到 $x$ 不是 $y$ 的倍数时停止。

然后有一种情况，当 $x = 1$ 时，就不需要进行模拟了。

为什么呢？

当 $x = 1$ 时你每次要加到 $y$ 再除到 $1$，重复了。

所以当 $x=1$ 时，我们直接输出 $k \bmod (y-1)$，就是正确答案了。

这题有个坑点：

当 $x$ 一开始就是 $y$ 的倍数时我们不能直接除。因为我们必须先加一才能除。

# 代码
```
#include <bits/stdc++.h>
using namespace std;
void solve() {
	int x,y,k;
	cin>>x>>y>>k;
	x++,k--;
	while(x%y==0) x/=y;
	while(true) {
		if(!k||x==1||k<y-x%y) break;
		int q=y-x%y;
		x+=q;
		k-=q;
		while(x%y==0) x/=y;
	}
	cout<<x+k%(y-1)<<'\n';
}
int main() {
	int _;
	cin>>_;
	while(_--)solve();
}
```
**完结撒花**

---

## 作者：gaomingyang101011 (赞：1)

## 思路：

这道题如果我们在执行加一的步骤时一次次地加就会超时，所以我们可以一次性加到能被 $y$ 整除，然后再除以 $y$，每一次累加加一的次数。

## 代码：


```cpp
#include<iostream>
using namespace std;
long long t;
long long x,y,k;
// 变量名称都与题目中含义相同 
int main(){
	cin>>t;
	while(t--){
		cin>>x>>y>>k;
		while(k>0&&x!=1){
			int s=min(k,y-(x%y));
			k-=s;
			x=x+s;
			// 一次性加到能被整除，节约时间 
			while(x%y==0) x/=y;
		}
		k%=(y-1);
		x+=k;
		// 因为前面是在x=1时就跳出了while
		// 所以可能少进行了几次操作 
		if(x%y==0) x/=y;
		// 前面操作完之后x可能能被y整除 
		cout<<x<<endl;
	} 
	return 0;
}

```

---

## 作者：P_VICVIC_R (赞：1)

~~虽然短时间橙不了，但是这个估值真的没有一点安全感，于是我来写题解了~~

---

### 一、题面：

没人翻译题面？以下是机翻：

最近，一年级学生 Maxim 学习了 Collatz 猜想，但是他在上课的时候并没有太注意，所以他认为猜想中提到了以下过程：有一个变量 $x$ 和一个常数 $y$，下面的操作进行了 $k$ 次：

- 将 $x$ 加 $1$，然后
- 当 $x$ 能被 $y$ 整除时，再将其除以 $y$。

注意这两个动作是在一次操作中依次进行的。

例如，如果数字 $x=16,y=3,k=2$，那么经过一次运算，$x$ 变成 $17$，再经过另一次运算，$x$ 变成 $2$，因为加 $1$ 后，$x=18$ 可以被 $3$ 整除两次。
给定 $x、y$ 和 $k$ 的初始值，Maxim想知道 $x$ 的最终值是多少。

### 二、 思路：

模拟？~~就这个数据范围你能过就见鬼了！~~

我们发现：当 $x=1$ 时，出现循环。

那么我们就正常模拟，$x=1$时跳出，用数学方法解决……

模拟时注意：并不用每次老老实实的加 $1$  ，我们可以在 $k$ **足够大**的时候直接加上 $y-(x \bmod y)$，直接一步使 $y \mid x$。

那么什么时候 $k$ **足够大**呢？其实就是当 $ y-(x \bmod y) \le k$ 时。

#### [code](https://www.luogu.com.cn/paste/z68n9koi)

---

## 作者：xu_zhihao (赞：1)

### 题目理解

- 因为题目的数据有 $O(t\times k)$ 有 $10^{14}$ 那么大，所以肯定不能使用线性算法。

- 考虑指数级的 $O(\log n)$ 算法。将操作分为两段：

1. 操作若干次，将 $x$ 变为能被 $y$ 整除的最大数。时间复杂度 $O(1)$。
1. 操作若干次，将 $x$ 变为 $x \div y$。直到 $x \bmod y \ne0$。时间复杂度为 $O(1)$。

- 考虑到每一次操作 $2$，$x$ 都将除去若干个 $y$，在考虑 $1$ 的操作次数因该小于 $2$，所以复杂度约为 $O (\sum\log n)$。


### AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		long long x,y,k;
		cin>>x>>y>>k;
		int f=0;
		x++;
		k--;
		while(x>y)
		{
			long long u=ceil(1.0*x/y)*y-x;
			if(k-u<0)
			{
				printf("%lld\n",x+k);
				f=1;
				break;
			}
			x=ceil(1.0*x/y)*y;
			while(x%y==0 && x>0)x/=y;
			k-=u;
		}
		if(f)continue;
		long long h=y-x;
		if(k-h<0)
		{
			printf("%lld\n",x+k);
			continue;
		}
		k-=h;
		printf("%lld\n",k%(y-1)+1);
	}
}
```

---

## 作者：HsNu1ly7_ (赞：1)

## 题意

给定 $ x , y , k $ ，如果 $ x $ 为 $ y $ 的倍数 ，则让 $ x $ 除以 $ y $ , 否则让 $ x + 1 $ ， 问 $ k $ 次操作后，$ x $ 的值。

## 思路

根据题目直接模拟会超时，考虑每次让 $x$ 加上某一个数,
使得 $x$ 是 $y$ 的倍数， 然后再除以 $ y $ 。

可是这样如果 $y$ 是一个很小的数，还是会超时。

我们可以这样想：如果 $x$ 等于一，可以直接跳出循环，用数学来解决，因为这时 $x$ 就一直会在 $1$ 到 $y$ 之间。


代码如下：
 ```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
void solve (){
	int x , y , k ;
	cin >> x >> y >> k ;
	while ( k != 0 && x != 1 ){//k次操作没有结束且x不等于一
		int t = min ( k , y - x % y ) ;//x加t次就是y的倍数了
		x += t ;
		k -= t ;
		while ( x % y == 0 ){
			x /= y ;
		}
	}
	k %= ( y - 1 ) ;
	x = x + k ;
	cout << x << '\n' ;
	return ;
}
signed main (){
	ios::sync_with_stdio(0) ;
	cin.tie(0) ;
	cout.tie(0) ;
	int _ ;
	cin >> _ ;
	while ( _-- ){
		solve () ;
	}
	return 0 ;
}
```

---

## 作者：Dream_Stars (赞：0)

## 题目大意：
有一个变量 $x$ 和一个不变量 $y$，我们需要执行 $k$ 遍以下操作：

- 当 $x$ 不能被 $y$ 整除时，将 $x$ 增加 $1$；
- 当 $x$ 可以被 $y$ 整除时，将 $x$ 除以 $y$。

我们需要知道在 $k$ 次操作后，$x$ 的值是多少。有一点要注意，就是在除以 $y$ 的时候可以除多次，就比如 $x=9$，$y=3$ 的情况下可以**直接**除成 $x=1$，这一点需要注意，在具体实现中可以用一个 `while` 语句解决。

## 算法分析：
题面十分清晰，本人第一遍看的时候想到的算法是强模拟，但是，一看到**数据范围**是 $k\le10^9$ 就知道强模拟会**时间超限**，那么，为了解决时间超限的问题，我们需要进行一些剪枝的操作，在循环增加 $x$ 的数值时可以直接一次性增加至可以整除 $y$ 那样可以节省一些时间效率，从而达到**正确**。

## 代码展示：
```cpp
#include<bits/stdc++.h>//此代码用了子程序的写法。
#define ll long long
using namespace std;
ll n,t,k,x,y;
void read(){//输入。
  scanf("%lld" , &x);
  scanf("%lld" , &y);
  scanf("%lld" , &t);  
}
void paint(){//输出。
  printf("%lld" , x);
  printf("\n");
}
void work(){
  read(); 
  while(t > 0 && x != 1){
	k = min(t , y - (x % y));//这里找到加到y所需要的最小值
	t = t - k , x = x + k;//t减去操作次数，x加上数值
	while(x % y == 0) x = x / y;
/*
这里一定要while，不能用if，如果用if,那么万一数据如下：
x = 9
y = 3
那么只会除一次，从而WA。
*/
  }
  t = t % (y - 1) , x = x + t;
  while(x % y == 0) x = x / y;//这里要多做一次 。
  paint();//输出。
}
int main(){
  scanf("%lld" , &n);
  for(int i = 1 ; i <= n ; i++) work();//多组测试数据，调用子程序，精简，可读性强。
  return 0;//return 养成好习惯。
}
```

---

## 作者：IOI_official (赞：0)

# CF1982B 题解

## 思路：

我们直接模拟的话肯定会超时，所以考虑优化。

我们注意到每次操作 $x$ 才加 1，对于计算机来说有点太屈才了。

所以我们考虑在一次操作内将 $x$ 加到能整除 $y$，并在 $x$ 等于 1 时退出循环这样就能省去很多时间。

注意：由于我们在 $x$ 等于 1 时就退出了循环，所以要在循环外面检查一下是否有剩余。

## 代码：

``` cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int x,y,k;
int K;
signed main(){
	cin>>K;
	while(K--){
		cin>>x>>y>>k;
		while(k>0&&x!=1){
			if(k>=y-(x%y)){
				k-=y-(x%y);
				x+=y-(x%y);
				
				while(x%y==0)x/=y;
			}
			else{
				x+=k;
				k=0;
				while(x%y==0)x/=y;
				break;
			}
		}
		k%=(y-1);
		x+=k;
		if(x%y==0)x/=y;//防止有剩余 
		cout<<x<<endl;
	}
	return 0;
}
```

---

## 作者：__hjwucj__ (赞：0)

# 题解：CF1982B Collatz Conjecture

[题目传送门](/problem/CF1982B)

## 思路

首先，$10^9$ 的大小直接模拟是不可能的。但是，$+1$ 的操作是可合并的，所以每次 $+1$ 直到可以整除 $y$ 即可。

## 代码


```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define elif else if
#define fin(x) freopen (x,"r",stdin)
#define fout(x) freopen (x,"w",stdout)
#define rnt register int
#define reg(i,x,y) for (rnt i=(x);i<=(y);++i)
#define Reg(i,x,y) for (rnt i=(y);i>=(x);--i)
#define dec decltype
#define null nullptr
using namespace std;
namespace rwm {inline int read () {int s=0,w=0;char c=getchar ();while (!isdigit (c)) {w|=(c=='-');c=getchar ();}while (isdigit (c)) {s=(s<<1)+(s<<3)+(c^48);c=getchar ();}return w?-s:s;}inline void write (int x) {if (x<0) putchar ( '-'),x=-x;if (x>9) write (x/10);putchar (x%10|48);}inline void writesp (int x) {write (x),putchar (' ');}inline void writeln (int x) {write (x),putchar ('\n');}inline int square (int x) {return x*x;}inline int floor (double x) {return x;}inline int ceil (double x) {return (int)(x+0.5);}inline int gcd (int x,int y) {int z=x%y;while (z) x=y,y=z,z=x%y;return y;}inline int lcm (int x,int y) {return x/gcd (x,y)*y;}};
using namespace rwm;
int t,x,y,k;
inline void work (void)
{
	x=read (),y=read (),k=read ();
	while (k>0&&x!=1)
	{
		int p=min (k,y-(x%y));
		k-=p;
		x+=p;
		while (x%y==0) x/=y; 
	}
	if (k>0)
	{
		k%=(y-1);
		x+=k;
		if (x%y==0) x/=y;
	}
	writeln (x);
	return ;
}
signed main ()
{
	t=read ();
	while (t--) work ();
	return 0;
}

```

---

## 作者：王逸辰 (赞：0)

# CF1982B Collatz Conjecture 题解
## 思路
一个一个加会超时，那么我们只能另想一个办法。
因为每次加 $1$，且只要 $x$ 是 $y$ 的倍数就除以 $y$。所以，我们不妨在 $k$ 允许的基础上直接把 $x$ 加成 $y$ 的倍数，这样便省去了一个一个加的时间。

具体实现看代码。

```cpp
#include<iostream>
using namespace std;
long long t,x,y,k,s;//开long long
int main(){
	scanf("%lld",&t);
	while(t--){
	    scanf("%lld%lld%lld",&x,&y,&k);
		while(k>0&&x!=1){
			s=min(k,y-(x%y));//判断k是否够加
            k-=s,x+=s;
			while(x%y==0)
                x/=y;
		}
		k%=(y-1),x+=k;//加上剩余的k
		if(x%y==0)
            x/=y;
        printf("%lld\n",x);
	}
	return 0;
}
```

---

## 作者：TangyixiaoQAQ (赞：0)

# 题意简述
有一个变量 $x$ 和一个常数 $y$。将以下操作执行 $k$ 次：

- 将 $x$ 增加 $1$，然后
  
- 当 $x$ 可以被 $y$ 整除时，将 $x$ 除以 $y$。
  
给定 $x$、$y$ 和 $k$ 的初始值，Maxim 想知道 $x$ 的最终值是多少。
# 思路解析
直接**模拟**题目的过程显然会 `TLE` 。

但是 $x,y,k \le 10^9$，而 $t \le 10^4$，所以我们考虑**数论**优化这个过程。

类似于**角谷猜想**（冰雹猜想）：
> 一个正整数x，如果是奇数就乘以 $3$ 再加 $1$，如果是偶数就析出偶数因数 $2^n$，这样经过若干个次数，最终回到 $1$。
>
> 无论这个过程中的数值如何庞大，就像瀑布一样迅速坠落。而其他的数字即使不是如此，在经过若干次的变换之后也必然会到纯偶数：$4-2-1$ 的循环。据日本和美国的数学家攻关研究，在小于 $7*10^{11}$ 的所有的正整数，都符合这个规律。
>
> ——来自百度百科

注意到本题数据范围 $x,y,k \le 10^9$，满足 $x,y,k \le 7*10^{11}$，所以稍加转化，在该范围内运用猜想是正确的。

为了使 $y \mid x$ ，需要增加 $min(k,y−(x\mod y))$ 次。

当我们检测到 $x=1$ 时即可退出循环，取模得出 $x$ 在循环节中所处的位置，进而得出结果。

# 代码实现
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int T, x, y, k;
inline void solve() {
    cin >> x >> y >> k;
    while (k && x != 1) {
        int q = min(k, y - (x % y));
        x += q;
        k -= q;
        while (x % y == 0) {
            x /= y;
        }
    }
    k = k % (y - 1);
    x += k;
    cout << x << '\n';
    return;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
```

---

## 作者：zhangxiaohan007 (赞：0)

这题其实不难。

看到题目，~~好想写一个模拟~~再看到数据范围 $10^9$，~~模拟肯定不行~~考虑每次加上一个数使它满足要求，但实际上如果 $y$ 很小而 $k$ 很大，也会光荣地 ``TLE``。所以说我们要运用一下我们的数学知识，如果 $x$ 等于 $1$ 了，可以直接跳出循环，直接数学求解即可。还有别忘了多测。

奉上代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define inf 2e9
#define db double
using namespace std;
int x,y,k;
void solve()
{
	cin>>x>>y>>k;
	while(k>0&&x!=1)
	{
		int s=min(k,y-(x%y));
		k-=s;
		x=x+s;
		while(x%y==0)
		{
			x/=y;
		}
	}
	k%=(y-1);
	x+=k;
	if(x%y==0)x/=y;
	cout<<x<<"\n";
}
int main()
{
	int t;
	cin>>t;
	while(t--)solve();
	return 0;
}

```

---

## 作者：Miracle_1024 (赞：0)

## 思路：
  当 $x \ne 1$ 并且 $k \ne 0$ 的时候我们就可以暴力模拟，不满足条件的时候，如果 $k = 0$，说明操作完了，答案就是 $x$。
  
  当 $x = 1$ 时，在这种情况下已经说了会出现一个长度为 $y - 1$ 的循环节，直接模就可以了。
  
## 代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e6+10;
const int INF=0x3f3f3f3f;
inline int read(){ll x=0,f=1;char ch=getchar();while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
ll t,x,y,k; 
int main(){
    cin>>t;
    while(t--){
    	cin>>x>>y>>k;
    	while(x!=1&&k!=0){
      	 	ll z=x%y;
        	ll tmp=min(y-z,k);
       		if(tmp==0)tmp=min(y,k);
    	    x+=tmp;
    	    k-=tmp;
    	    while(x%y==0)x/=y;
    	}
    	if(!k)cout<<x<<endl;
    	else cout<<x+k%(y-1)<<endl;
   	}
}
```

---

