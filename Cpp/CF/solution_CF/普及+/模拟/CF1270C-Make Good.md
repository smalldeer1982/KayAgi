# Make Good

## 题目描述

Let's call an array $ a_1, a_2, \dots, a_m $ of nonnegative integer numbers good if $ a_1 + a_2 + \dots + a_m = 2\cdot(a_1 \oplus a_2 \oplus \dots \oplus a_m) $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

For example, array $ [1, 2, 3, 6] $ is good, as $ 1 + 2 + 3 + 6 = 12 = 2\cdot 6 = 2\cdot (1\oplus 2 \oplus 3 \oplus 6) $ . At the same time, array $ [1, 2, 1, 3] $ isn't good, as $ 1 + 2 + 1 + 3 = 7 \neq 2\cdot 1 = 2\cdot(1\oplus 2 \oplus 1 \oplus 3) $ .

You are given an array of length $ n $ : $ a_1, a_2, \dots, a_n $ . Append at most $ 3 $ elements to it to make it good. Appended elements don't have to be different. It can be shown that the solution always exists under the given constraints. If there are different solutions, you are allowed to output any of them. Note that you don't have to minimize the number of added elements!. So, if an array is good already you are allowed to not append elements.

## 说明/提示

In the first test case of the example, the sum of all numbers is $ 12 $ , and their $ \oplus $ is $ 6 $ , so the condition is already satisfied.

In the second test case of the example, after adding $ 4, 4 $ , the array becomes $ [8, 4, 4] $ . The sum of numbers in it is $ 16 $ , $ \oplus $ of numbers in it is $ 8 $ .

## 样例 #1

### 输入

```
3
4
1 2 3 6
1
8
2
1 1
```

### 输出

```
0

2
4 4
3
2 6 2
```

# 题解

## 作者：Fearliciz (赞：5)

一道水构造题。

#### 题目翻译：

给你一个数列，让你在其中插入最多 $3$ 个数字当然也可以不插入，使得这些数字的总和等于异或的2倍，只要给出任何一种方案即可。

#### 解题思路：

先来看一下异或

将一个数转换成二进制后异或。

+ $1 \oplus 1= 0$
 
+ $0 \oplus 0= 0$ 
 
+ $1 \oplus 0= 0$ 
 
+ $1 \oplus 1= 0$ 

显然，可以得到两个式子：

+ $x \oplus x=0$ 

+ $0 \oplus x=x$

知道了这两个式子就很简单了。

首先定义两个变量分别记录异或后的值和整个数列和。

然后将异或后的值再异或自己，得到 $0$。

最后再异或一下原数列异或后的值加整个数列的和。

这样就完成了题目要求。

不过为什么呢？

我们来统计一下加了数字后的数列包含什么：

+ 第一部分：原数列的和

+ 第二部分：原数列异或的值

+ 第三部分：原数列异或的值加原数列的和

所以总共包含了 $2$ 个原数列的和以及 $2$ 个原数列异或的值。

所以得到的结果就是上面的一半。

#### 参考代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
	int T,n,ans,x,cnt;
	cin>>T;
	while(T--){
		ans=0;
		cnt=0;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>x;
			ans^=x;
			cnt+=x;
		}	
		cout<<2<<endl<<ans<<" "<<(cnt+ans)<<endl;
	}
	return 0;
}

```

---

## 作者：EXODUS (赞：3)

# Part 1：前言
学弟一眼秒了，我还想了 114514 年，又被单调队列了/kk。

# Part 2：正文
首先有一个知识铺垫

$$x \oplus x=0$$
$$x \oplus 0=x$$

**注意异或是满足交换律的。**

下文中，我们记 $sums$ 表示**初始**序列所有数字的和， $sumx$ 表示**初始**序列所有数字的异或和。

首先我们考虑一下异或和为 $0$ 的情况怎么做，我们可以直接套上第二个式子，得出加入一个数 $sums$ 后，原序列和变成 $2\times sums$，异或和变为 $sums$，满足题意。

再考虑怎样把异或和变为 $0$。可以套上第一个公式，加入数字 $sumx$，此时异或和变为 $0$，和变为 $sums+sumx$，又变成了第一个问题。

所以得到通解，$b_1=sumx,b_2=sums+sumx$。

没了？
没了。

# Part 3：代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
typedef long long ll;
il int read(){
	int ans=0,flag=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flag=-1;ch=getchar();}
	while(isdigit(ch))ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
	return ans*flag;
}

const int N=1e5+7;
int t;
int n;
int a[N];

signed main(){
	t=read();
	while(t--){
		n=read();
		int sumx=0,sums=0;
		for(int i=1;i<=n;i++){
			a[i]=read();
			sumx^=a[i];
			sums+=a[i];
		}
		printf("2\n%lld %lld\n",sumx,sums+sumx);
	}
	return 0;
}
```
# Part 4：后文
点赞再走吧（可怜

---

## 作者：天南月 (赞：3)

~~这是一道人类智慧题~~

前几天机房一巨佬打完CF就跟我们讲了这道题，一开始听到异或和就想到线性基，于是朝这个错误的方向苦苦思索了好一阵，无果。接着又开始找和与异或和的关系，又苦苦思索了好一阵，又无果。然后知道正解的我……~~我有一句MMP不知当讲不当讲~~

回到这题。

做法就是先将所有数的异或和XOR与和SUM求出来，接着我们只需加入两个数XOR与XOR+SUM。我们发现：XOR^XOR^(XOR+SUM)=XOR+SUM=(1/2)*(SUM+XOR+XOR+SUM)。是的你没看错你做完了~~mmp~~。

写个题解纪念一下这道困扰了我40min然后提交框打完的题~~虽然CE了一遍~~

代码……不放了吧，谁都会打。

---

## 作者：__zhuruirong__ (赞：0)

简单的一道构造题。

## 题目大意

给你一个长度为 $n$ 的数组 $a$，让你至多添加 $3$ 个元素，使得这些数字的总和等于异或的 $2$ 倍。

## 算法分析

由于异或的特性，相同的两个数异或起来为 $0$，这就让我们轻而易举的想到一个做法：首先输出 $a$ 的异或和，让异或和为 $0$，再输出一个整数，使得 $a$ 的和加上这个整数等于这个整数 $\times2$。

现在就要看第二个整数为多少，假设 $a$ 的异或和为 $x$，和为 $y$，我们可以输出 $a$ 的和，$a$ 各个元素的和就为 $y+y+x=2y+x$，而异或和的两倍则是 $2y$，少一个 $x$，所以得把 $y$ 加上 $x$，和就变成 $2y+2x=2(x+y)$，异或和的两倍为 $2(x+y)$，符合条件。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5 + 10;
int T, n, a[N];

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> T;
	while(T--) {
		cin >> n;
		for(int i = 1; i <= n; i++)
			cin >> a[i];
		int sum1 = 0, sum2 = 0;
		for(int i = 1; i <= n; i++) {
			sum1 += a[i];
			sum2 ^= a[i];
		}
		cout << 2 << endl << sum2 << " " << (sum1 + sum2) << endl;
	}

	return 0;
}

```

---

## 作者：Michael1234 (赞：0)

- 本题属于**思维**题：

- 我们先将所有数的异或和记录在 $sum1$ 中，所有数的和记录在 $sum2$ 中。

- 以第一组样例为例（忽略是否已经符合要求）：

~~~
sum1:6
sum2:12
~~~

- 接下来我们添加一个等于 $sum1$ 的数：

~~~
sum1:0
sum2:18
~~~

- 最后，我们添加一个等于 $sum2$ 的数：

~~~
sum1:18
sum2:36
~~~

- 此时，我们满足题目要求。

- 我们添加的数分别是 $sum1$ 和 $sum1+sum2$，输出。

## CODE

~~~cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll t,n,now,sum1,sum2;//见祖宗
int main()
{
	cin>>t;
	while(t--)
	{
		sum1=0;
		sum2=0;//清空!!!
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>now;
			sum1^=now;
			sum2+=now;//记录每个数
		}
		cout<<"2\n"<<sum1<<" "<<sum1+sum2<<"\n";//输出
	}
	return 0;
}

---

## 作者：Acerkaio (赞：0)

### 题意：

给你 $n$ 个非负整数，要求你加入不多于 $3$ 个非负整数，使得这些数总和是这些数异或和的二倍。

### 思路：

结论很简单。

但是很难想。

我们要去构造这样的一些数字，必然有他的独特之处。比如，我们知道 $a \oplus a = 0$。那么我们就可以把原来的数异或和提前求出并加入这个数。这样这 $n + 1$ 个数的异或和为 $0$。那么接下来就好搞了，现在的这 $n + 1$ 个数总和为 $sum$，加入其即可。

想到这个非常不容易了。

所以最后只要加入两个数。

### CODE：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
    int T;
    cin >> T;
    while (T--) {
        int n, ans1 = 0, ans2 = 0;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            int a;
            cin >> a;
            ans1 ^= a;
            ans2 += a;
        }
        cout << 2 << '\n' << ans1 << ' '<< ans1 + ans2 << '\n';
    }
    return 0;
}
```

---

## 作者：xiaomimxl (赞：0)

# 题目大意：

给一个序列最多加 3 个数，使该序列的和 $S$ 与异或和 $X$ 满足 $S=2X$ 的关系。

# 思路分析：

#### 明确异或的两个小结论：

0 异或其他数，该数不改变 ；两个相同数异或为 0,那么用就可以尝试构造两个相同的数保证 $X$ 不变同时改变 $x$。

#### 当 $S \le 2X$，且 $S$ 为偶数时，构造两个 $(2X-S) \div 2$ 即可。

那么对于 $S > 2X$，想办法让其转化到第一种，因为第一个性质 ，我们可以用一个尽量大的且除最高位都是 0 的数字 $a$ 保证 $S \le 2X$，因为 $S$ 增加了 $a$，而 $X$ 也增加了 $a$ 乘 2 后 ，显然比 $S$ 大。

之后解决 $S$ 的奇偶问题，当 $S$ 为奇数，给 $a+1$ 就好。

# AC code:

```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N = 10 + 1e5, mod = 1e9 + 7;
int n,s,x;
signed main() {
	ios::sync_with_stdio(0);
	int t;
	cin >> t;
	while (t--) {
		s=0;x=0;
		cin >> n;
		for (int i = 1; i <= n; i++) {
			int t;
			cin >> t;
			s += t;
			x ^= t;
		}
		int k = (1LL << 50) + s % 2;
		s += k, x ^= k;
		int a = (2 * x - s) >> 1;
		cout << 3 << endl;
		cout << a << ' ' << a << ' ' << k << endl;
	}
	return 0;
}

```


---

## 作者：XL4453 (赞：0)

### 解题思路：

考虑直接构造这样的一个解，结论是统计所有数的和和所有数的异或和，然后直接加入所有数的异或和和所有数的异或和原来所有数的和加进去就好了。

换言之，设所有数的异或和为 $a$，原来所有数的和 $b$，需要加进去的是 $a$ 和 $a+b$。

这样是显然成立的，新加入的一个异或使得原先的异或变成 0，然后又加入了一个异或和和原来数的和使得新的异或等于这个数，同时又发现所有的数的和就是这个数的两倍，符合题意。

----------
注意开 long long。

-------------
### 代码：

```cpp
#include<cstdio>
using namespace std;
long long n,a,b,x,T;
int main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld",&n);
		a=b=0;
		for(int i=1;i<=n;i++){
			scanf("%lld",&x);
			a+=x;b^=x;
		}
		printf("2\n%lld %lld\n",b,a+b);
	}
	return 0;
}
```



---

## 作者：FutaRimeWoawaSete (赞：0)

~~神仙思维构造题~~   
完全是人类智慧好不好。    
我们要满足题意，只需要把 $XOR$ 与 $XOR + SUM$ 丢入即可，即：    
```
XOR ^ XOR ^ (XOR + SUM) = (XOR + XOR + SUM + SUM) / 2
```
此题完，我承认我r $Trie$ r 了一个世纪。    
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int Len = 1e5 + 5;
long long n,m,XOR,SUM,x;
int main()
{
	int T;
	scanf("%d",&T);
	while(T --)
	{
		XOR = SUM = 0;
		scanf("%lld",&n);
		for(int i = 1 ; i <= n ; i ++)
		{
			scanf("%lld",&x);
			XOR ^= x;
			SUM += x;
		}
		printf("2\n");
		printf("%lld %lld\n",XOR , XOR + SUM);
	}
	return 0;
}
```

---

## 作者：liuyz11 (赞：0)

# 题解 CF1270C 【Make Good】

*该场比赛所有题题解：[我的博客求围观](https://www.cnblogs.com/nblyz2003/p/12161998.html)*

题目大意：给你一串数字，让你在其中插入最多3个数字，使得这些数字的总和等于异或的2倍，只要给出任何一种方案即可。

首先这串数字是和我们没关系了，我们需要的只是它们的异或以及和。

很显然，必定存在一种方案只放一个数字就能成立（不要问我为什么，程序员不需要证明）。

然后么将异或的乘个二，按照二进制来计算。

对于每一位，要是该位的为1，会对和产生1的贡献，对异或产生2的贡献，那么对于一个二进制位，要是这两个数不同，插入的数该位一定为1。

感觉解释的有点模糊……那就来个样例解释一下。

以下以[1,2,3,7]为例：

            和：13 二进制：01101

            异或：7 二进制：00111

            异或的先乘个2也就是右移一位，为01110

            0110 | 1

            0111 | 0

            两位置不同，答案该位为1，即加上1 << 0，变成1

            和变成01110，异或变成01100，最后一位已经相同了，舍掉

            011 | 1

            011 | 0

            不同，答案变成3，两数分别变成1000和0100，同样舍最后一位

            10 | 0

            01 | 0                     相同

        ------------

            1 | 0

            0 | 1                      不同，答案变成11


        ------------

            | 1

            | 1                         相同

插入后数列为 1， 2， 3， 7 ， 11符合条件

具体代码实现：
```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define rep(x, l, r) for(int x = l; x <= r; x++)
#define repd(x, r, l) for(int x = r; x >= l; x--)
#define clr(x, y) memset(x, y, sizeof(x))
#define all(x) x.begin(), x.end()
#define pb push_back
#define mp make_pair
#define MAXN
#define fi first
#define se second
#define SZ(x) ((int)x.size())
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = 1 << 30;
const int p = 1000000009;
int lowbit(int x){ return x & (-x);}
int fast_power(int a, int b){ int x; for(x = 1; b; b >>= 1){ if(b & 1) x = 1ll * x * a % p; a = 1ll * a * a % p;} return x % p;}

int main(){
	int t;
	scanf("%d", &t);
	rep(times, 1, t){
		int n;
		scanf("%d", &n);
		ll s1 = 0, s2 = 0;
		rep(i, 1, n){
			ll x;
			scanf("%lld", &x);
			s1 += x;
			s2 ^= x;
		}
		s2 <<= 1;
		ll ans = 0;
		for(int i = 0; s1 != s2; i++){
			if((s1 & 1) ^ (s2 & 1)){
				s1 += 1;
				s2 ^= 2;
				ans += 1ll << i;
			}
			s1 >>= 1;
			s2 >>= 1;
		}
		printf("1\n%lld\n", ans);
	}
    return 0;
}
```cpp

---

## 作者：Thaumaturge (赞：0)

前几天有人告诉我们$CF$有个题，说它不难

如果没有这个提示我就真想不出来了= =

题意：给你n个数，让你向其中添加最多三个数，使他们的异或和为加法和的一半

考虑异或的性质。令这$n$个数的异或和为$T$，则先扔一个$T$进去

现在他们的异或和就是0了。

令现在他们的$sum$是$S$

再扔个$S$进去

这下和就是$2S$,异或和就是$S$

做完了？

是的，做完了。$qwq$

如果压行应该可以在两行之内解决这题

---

