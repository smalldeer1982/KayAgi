# [ARC117C] Tricolor Pyramid

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc117/tasks/arc117_c

$ N $ 個のブロックが横一列に並んでおり、それぞれのブロックは青・白・赤のうちいずれかで塗られています。 左から $ i $ 番目 $ (1\ \leq\ i\ \leq\ N) $ のブロックの色は文字 $ c_i $ で表され、`B` は青、`W` は白、`R` は赤に対応しています。

この状態から青・白・赤のブロックを積み上げ、$ N $ 段のピラミッドの形にします。以下の図がその一例です。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_arc117_c/f795a525a74e48b7e43010cb259b0e9d82262039.png) 

ここでは、ブロックを下から順に、以下の規則で $ 1 $ 個ずつ置いていきます。

- 直下にある $ 2 $ 個のブロックの色が同じ場合、それと同じ色のブロックを置く
- 直下にある $ 2 $ 個のブロックの色が異なる場合、そのどちらでもない色のブロックを置く

このとき、一番上のブロックはどの色になるでしょうか？

## 说明/提示

### 制約

- $ N $ は $ 2\ \leq\ N\ \leq\ 400000 $ を満たす整数
- $ c_1,\ c_2,\ \dots,\ c_N $ はそれぞれ `B`，`W`，`R` のいずれか

### Sample Explanation 1

この入力例では、ブロックを以下のように積み上げることになります。 - 一番下の段の左から $ 1,\ 2 $ 番目のブロックはそれぞれ青色・白色なので、その上に赤色のブロックを置く。 - 一番下の段の左から $ 2,\ 3 $ 番目のブロックはそれぞれ白色・赤色なので、その上に青色のブロックを置く。 - 下から $ 2 $ 段目のブロックはそれぞれ赤色・青色なので，その上に白色のブロックを置く。 一番上のブロックの色は白となるため、`W` を出力します。

### Sample Explanation 2

この入力例では、ブロックを以下のように積み上げることになります。 - 一番下の段の左から $ 1,\ 2 $ 番目のブロックはそれぞれ赤色・赤色なので、その上に赤色のブロックを置く。 - 一番下の段の左から $ 2,\ 3 $ 番目のブロックはそれぞれ赤色・青色なので、その上に白色のブロックを置く。 - 一番下の段の左から $ 3,\ 4 $ 番目のブロックはそれぞれ青色・青色なので、その上に青色のブロックを置く。 - 下から $ 2 $ 段目の左から $ 1,\ 2 $ 番目のブロックはそれぞれ赤色・白色なので、その上に青色のブロックを置く。 - 下から $ 2 $ 段目の左から $ 2,\ 3 $ 番目のブロックはそれぞれ白色・青色なので、その上に赤色のブロックを置く。 - 下から $ 3 $ 段目のブロックはそれぞれ青色・赤色なので、その上に白色のブロックを置く。 一番上のブロックの色は白となるため、`W` を出力します。

### Sample Explanation 3

最終的なブロックの並びは、以下の図のように表されます。一番上のブロックの色は青となるため、`B` を出力します。 !\[ \](https://img.atcoder.jp/arc117/333af8ef18ae0a6ce966c46492cb07e6.png) なお、これは問題文中に例示したケースと同じものになっています。

### Sample Explanation 4

最終的なブロックの並びは、以下の図のように表されます。一番上のブロックの色は赤となるため、`R` を出力します。 !\[ \](https://img.atcoder.jp/arc117/36a2a6777ac49fa0bb43440de385dced.png)

## 样例 #1

### 输入

```
3
BWR```

### 输出

```
W```

## 样例 #2

### 输入

```
4
RRBB```

### 输出

```
W```

## 样例 #3

### 输入

```
6
BWWRBW```

### 输出

```
B```

## 样例 #4

### 输入

```
8
WWBRBBWB```

### 输出

```
R```

## 样例 #5

### 输入

```
21
BWBRRBBRWBRBBBRRBWWWR```

### 输出

```
B```

# 题解

## 作者：SalN (赞：8)

[linkqwq](https://www.luogu.com.cn/problem/AT_arc117_c)


#### 题目描述

有一个金字塔（就杨辉三角那种形状），每一个格子有 ```B，W，R``` 三种字符之一。

```
B
WR
WWB
BRBB
```

对于一个格子，如果它 $A(i,j)$ 的左下 $A(i+1,j)$ 右下 $A(i+1,j+1)$ 字符相同，那它的字符为与左下右下相同的字符，否则为左下右下没有出现的字符。

给定最下面那一层的字符情况，求顶端的字符是什么 o.O

行数 $N\leq 400000 $。

----

#### 题目解法

这种题目我们肯定希望从底层直接考虑，不然很容易平方。

我们考虑简化这个题目的变换，给字符赋值，然后通过简单一点的式子概括这些变换，式子要满足结合律交换律之类的。

$f(i,i)=i,f(j,j)=j,f(k,k)=k,f(i,j)=k,f(i,k)=j,f(j,k)=i$

考虑到这个题目大概要组合数，然后组合数会很大，题目又正好没有取模，我们可以考虑模运算。~~况且加法那些的手玩之后发现都不可以捏 /wq~~

假设三个数为 $i,j,k$，运算为 $f$，那么 $i+j+k$ 应该是一定的，想到对于 $f(i,j)=k$ 这类可以用和去减。令 ```B``` 为 0，```W``` 为 1，```R``` 为 2，设颜色 $p$ 左右下方分别是颜色 $x,y$，如果 $p\equiv3-x-y\pmod 3$ 的话恰好全都是符合的，所以 $f(i,j)=(6-i-j)\bmod 3$

然后看一下金字塔的 sum，取模显然可以最后考虑。

```
		(3-x1-3x2-3x3-x4)
	(x1+2x2+x3-3)  (x2+2x3+x4-3)
(3-x1-x2)        (3-x2-x3)      (3-x3-x4)
x1         x2          x3          x4
```

对于 $n$ 为奇数，顶端 $p$ 就是 $p\equiv\sum a_iC_{n-1}^i\pmod 3$

对于 $n$ 为偶数，顶端 $p$ 就是 $p\equiv-\sum a_iC_{n-1}^i\pmod 3$

由于模数很小，所以有些数可能没有逆元，不太好阶乘逆元去做组合数，但是套 [lucas](https://www.cnblogs.com/chelsyqwq/p/17625779.html) 随便做。

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=500100;
int n, b[N];

int c(int n,int m) {
	if(n<m) return 0;
	int mul=1;
	for(int i=n-m+1; i<=n; ++i) mul*=i;
	for(int i=1; i<=m; ++i) mul/=i;
	return mul%3;
}

int lucas(int n,int m) {
	if(n<m) return 0;
	if(n<=10) return c(n,m);
	return lucas(n/3,m/3)*c(n%3,m%3)%3; 
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n; string a; cin >> a;
	for(int i=0; i<n; ++i) {
		if(a[i]=='B') b[i]=0;
		if(a[i]=='W') b[i]=1;
		if(a[i]=='R') b[i]=2;
	}
	int cnt=0;
	for(int i=0; i<n; ++i)
		cnt+=lucas(n-1,i)*b[i]%3, cnt%=3;
	if(n%2==0) cnt=(3-cnt)%3;
	if(cnt==0) cout << 'B' << '\n';
	if(cnt==1) cout << 'W' << '\n';
	if(cnt==2) cout << 'R' << '\n';
	return 0;
}

```






---

## 作者：Shunpower (赞：5)

智商题。

## 思路

不妨称红蓝白分别为 $0,1,2$。

考虑对于两个积木算出上面的积木是什么。

先考虑相同颜色积木得到相同颜色，一般的地我们采取对于下方两个积木加和的构造方法，然后注意到：

$$
\begin{cases}
-(0+0) \mod 3=0\\
-(1+1) \mod 3=1\\
-(2+2) \mod 3=2
\end{cases}
$$

然后可以发现这玩意在不同颜色得到第三种颜色的时候也是对的。也就是说，对于积木 $d_3$，如果它下方有两块积木 $d_1,d_2$，那么 $d_3=-(d_1+d_2)\mod 3$。

这个加和长得很类似杨辉三角，不妨模拟一下。下面是 AT 官方题解中的图片：

![](https://img.atcoder.jp/arc117/6d089e1cdfb0ed3c0bf6daee87fc198e.png)

也就是说，高度为 $n$（底层为 $n$ 块积木）的金字塔，顶端积木的颜色其实就是 $[(-1)^{n+1}\times \sum\limits_{i=0}^{n-1}\binom {n-1}{i}\times d_{i+1}]\mod 3$，这里我们规定底端积木的编号从 $1$ 到 $n$。

实现的时候由于 C++ 取模和数学取模不一样，答案可能是负数。得到答案之后再加一个 $3$ 再模一次即可。

由于模数太小并且 $3$ 为质数，需要使用卢卡斯定理解决计算组合数的问题。

代码很好写。[AC 记录](https://www.luogu.com.cn/record/101876941)。

---

## 作者：PCCP (赞：2)

## 赛时思路

昨天晚上牛客的提高模拟赛出来这个做 B 题，我觉得这题作为个构造，还是 ARC 的，是不是不太适合出现在 OI 赛场……

赛场上我花了一个小时想在不改变字符串的基础上解决这题，但是我尝试了单调栈、寻找规律等等后都一无所获。

不过我想到了一种非常极限的暴力做法，如果时限开大两倍，可能能卡过去，因为牛客的数据范围比本题小一半。这种做法在三进制的基础上通过预处理优化暴力，设预处理的最大子串长度为 $ B $，时间复杂度是 $ O(3^B+\frac{n^2}{B}) $，由于还带一个 $ \frac{1}{2} $ 的全局常数，预估可以通过 $ n\le 2 \times 10^4 $ 的数据范围。

不过我在写这个暴力的时候想到既然我用了三进制，是否可以从中发现什么数量关系呢？我预处理了一组数据，敏锐地观察到一行相邻的两个数如果不同，这两个数和他们产生的数加起来正好等于三。这是个重大线索，但是如果两个数相同呢？我用三减去下面的两个数，可能会得到负数，但好消息是这个负数加上三又是符合规律的了。

所以我们得到一个规律：转换成三进制后，两个相邻的数产生的数等于三减去这两个数再对三取模。用数学表示就是这样：

$$ A $$

$$ B \ C $$

$$ A=(6-B-C) \bmod 3 $$

得到这个规律能干啥呢？难道只是使得我们的暴力更好写一些吗？继续寻找规律，既然是相减的规律，看看能不能这样一层一层地算出每一层的数字的总和，我们设从下面开始的第一层的三进制序列为 $ a_1 $，题目给定了我们 $ a_{1,1}, \dots , a_{1,n} $。这样开始递推，发现每一层的和都要减去上一层的和，但是还要加回上一层最两边的数的和，这样我们还是只能暴力。

但是在此前的基础上，如果我们把每一层的数这样用第一层的数表示出来，不难发现：$ a_{2,1}=(3-a_{1,1}-a_{1,2}) \bmod 3 $，继续推下去：$ a_{3,1}=(a_{1,1}+2a_{1,2}+a_{1,3}) \bmod 3 $。提取系数的绝对值发现可能会是我们很熟悉的二项式系数。

继续推第四第五层，你会发现他们都符合二项式定理。也就是说：

$$ a_{i,j}=(3+ (-1)^{i-1}\times\displaystyle\sum_{k=j}^{j+i-1}{\binom{i}{k-1}a_{1,k}}) \bmod 3 $$

那这样我们想求任意一层任意一块砖的颜色都轻而易举了，不过为了快速计算组合数，我们需要用到大名鼎鼎的 Lucas 定理。值得一提的是 Lucas 定理的模板题是蓝题，然而这道题却是绿题，符合我对你谷的刻板印象。

这样我们就愉快地切出了这道题。

## 代码

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>
#include<queue>
#include<stack>
#include<set>
#define int long long
using namespace std;
const int N=6e5+10;
const long long p=3;
const int MOD=3000000;
int t,n,m;
string s;
long long a[N],c[N],ans;
long long qpow(long long y,long long z){
	y%=p;
	if(z==1){
		return y;
	}
	long long ans=qpow(y,z>>1);
	ans=ans*ans%p;
	if(z&1){
		ans=ans*y%p;
	}
	return ans;
}
long long C(long long n,long long m){
	if(m>n){
		return 0;
	}
	return (long long)(a[n]*qpow(a[m],p-2))%p*qpow(a[n-m],p-2)%p;
}
long long Lucas(long long n,long long m){
	if(m==0){
		return 1;
	}
	return (C(n%p,m%p)*Lucas(n/p,m/p))%p;
}
signed main(){
	a[0]=1;
	for(int i=1;i<=p;i++){
		a[i]=(a[i-1]*i)%p;
	}
	cin>>n;
	int k=!(n%2)?-1:1;
	ans=0;
	cin>>s;
	for(int i=1;i<=n;i++){
		if(s[i-1]=='W'){
			s[i-1]='A';
		}
		if(s[i-1]=='R'){
			s[i-1]='C';
		}
		c[i]=s[i-1]-'A';
	}
	for(int i=1;i<=n;i++){
		ans=(ans+Lucas(n-1,i-1)*k*c[i]%p+MOD)%p;
	}
	char tem=ans+'A';
	if(tem=='A'){
		tem='W';
	}
	if(tem=='C'){
		tem='R';
	}
	cout<<tem<<endl;
}
```

---

## 作者：Nuclear_Fish_cyq (赞：1)

首先，为了更好的进行接下来的计算，我们将白色定义为 $0$，蓝色为 $1$，红色为 $2$。接下来我们可以观察堆叠积木颜色的性质。我们可以列个表：

|  | 0 | 1 |2  |
| :----------: | :----------: | :----------: | :----------: |
| 0 | 0 | 2 | 1 |
| 1 | 2 | 1 |  0|
| 2 | 1 | 0 | 2 |

很容易就能得出，如果一个积木下面的积木颜色为 $a,b$ 的话，那么这个积木的颜色为 $(6-a-b)\bmod3$，即 $(6-(a+b))\bmod3$。注意到我们事实上只需要知道 $a+b$ 就可以知道这个积木的颜色，所以我们的目标就从每个积木具体的颜色变为了每个底层积木颜色的系数。

然后我们思考，底层的第 $i$ 个砖块有多少种到达终点的路径，即它有多少种影响终点的方式，也就是它的系数。现在这就是一个最基础的组合数问题了，答案就是在有 $n-1$ 个改变方向的点的路径中要向左走 $i$ 步的方案数，即 $C_{n-1}^i$。这玩意直接求很难求，但是我们使用 Lucas 大法可以直接秒。最后还有一点，因为 $a+b$ 在表达式中还带个负号，所以当 $n$ 是偶数的时候还要记得取相反数。

可能讲的有点抽象，上代码。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define db double
#define ull unsigned long long
#define inf INT_MAX
#define linf LLONG_MAX
#define ninf INT_MIN
#define nlinf LLONG_MIN
#define mod 3
//#define range
using namespace std;
int n, a[400000], fac[3] = {1, 1, 2}, ans;
int lucas(int p, int q){
	if(p < q){
		return 0;
	}
	if(p < 3 && q < 3){
		return fac[p] / fac[p - q] / fac[q];
	}
	return lucas(p % mod, q % mod) * lucas(p / mod, q / mod) % mod;
}
//如果再忘记把题目给的1~n变为0~n-1自罚20仰卧起坐
int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	string s;
	cin >> s;
	for(int i = 0; i < n; i++){
		if(s[i] == 'W'){
			a[i] = 0;
		}
		else if(s[i] == 'B'){
			a[i] = 1;
		}
		else{
			a[i] = 2;
		}
	}
	for(int i = 0; i < n; i++){
		ans += a[i] * lucas(n - 1, i);
		ans %= 3;
	}
	if(n % 2 == 0){
		ans = 3 - ans;
		ans %= 3;
	}
	if(ans == 0){
		cout << 'W' << endl;
	} 
	else if(ans == 1){
		cout << 'B' << endl;
	}
	else{
		cout << 'R' << endl;
	}
	return 0;
}

```

---

## 作者：DDF_ (赞：1)

## 题面

有一个最底层有 $n$ 个砖块的金字塔，砖块有 `B，W，R` 三种颜色，每个砖块颜色与其下面一层两个相邻砖块相关。

如果下层相邻两个砖块颜色相同，那么这个砖块的颜色就和他们相同；否则这砖块颜色就是与这两个砖块不同的第三种颜色。求最顶层砖块颜色。

## 思路

第一眼看这个题目，$n$ 的取值范围为 $2 \le n \le 4 \times 10^{5}$，打个 $n^{2}$ 暴力可以水一点分，但要 `AC` 还是要找性质。

首先设颜色 `B` 为 $0$，颜色 `R` 为 $1$，颜色 `W` 为 $2$，然后考虑不同情况。

如果两个颜色相同，则有 $(0,0) \Rightarrow 0$，$(1,1) \Rightarrow 1$，$(2,2) \Rightarrow 2$ 三种情况。

如果两个颜色不同，则有 $(0,1) \Rightarrow 2$，$(1,2) \Rightarrow 0$，$(0,2) \Rightarrow 1$ 三种情况。

然后找这六组数据的共性。

设 $x$ 为前两个数字之和。

则有 $[x=0] \Rightarrow 0$，$[x=1] \Rightarrow 2$，$[x=2] \Rightarrow 1$，$[x=3] \Rightarrow 0$，$[x=4] \Rightarrow 2$。

列出这些，规律就已经很明了了，发现数据呈一个 $2$，$1$，$0$ 循环，所以有对 $3$ 取模的运算，又因为数据顺序是反的，所以有减法运算。

由此可得，下一层的颜色 $c'_{i} = -x \bmod 3 = -c_{i}-c_{i+1} \bmod 3$。

推出这个很不容易，但我们还是要继续推最顶层颜色。

由于每一层的颜色都有一个膜 $3$ 运算，所以我们可以看作运算是在膜 $3$ 意义下进行。

然后我们举一些例子，设 $n=4$，接着列表可得下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/vn42xcp6.png)

可以发现，$n$ 层的第 $i$ 个颜色的系数为杨辉三角形第 $n$ 层的第 $i$ 项。

还可以发现，$n$ 为偶数，答案就为负数；$n$ 为奇数，答案就为正数。

这里说一下杨辉三角形。

杨辉三角形中，第一排为 $1$，左右对称，下面一排每个数都为上方两数之和，形成这样的数三角。

![](https://cdn.luogu.com.cn/upload/image_hosting/6wz19eal.png)

杨辉三角形中，$(a+b)^{n}$ 展开式中各项系数依次对应与三角形第 $n+1$ 层的每一项。

想到 $(a+b)^n$，就容易想到二项式定理。

由牛顿发现的二项式定理，有公式为

$$
(a+b)^{n} = \binom {n} {0}a^{n}+ \binom {n} {1} a^{n-1}b + \dots + \binom {n} {i} a^{n-i}b^{i} + \dots + \binom {n} {n} b^{n}
$$

所以数列中，第 $i$ 项系数为 $n-1 \choose i-1$。

所以有 $ans= (\sum _{i=1} ^{n} \binom {n-1}{i-1} \times c_{i}) \times [2 \mid n] \bmod 3$。

算组合数的方法有很多，大多数放在这一题中会 `TLE`，但针对组合数取模运算有卢卡斯定理，公式为

$$
\binom{n} {m} \bmod p = \binom { \lfloor \frac {n} {p} \rfloor} {\lfloor \frac {m} {p} \rfloor} \times \binom {n \bmod p} {m \bmod p} \bmod p 
$$

用这个计算，复杂度便可降低到 $O(n \times \log_{3}n)$，便能过此题。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[400002];
int C(int n,int m) {
	if(n<3&&m<3) {
		int res=1;
		for(int i=n-m+1;i<=n;i++) res*=i;
		for(int i=1;i<=m;i++) res/=i;
		return res;
	}
	return C(n/3,m/3)*C(n%3,m%3)%3;
} //Lucas 求组合数
char get(int x) {
	if(x==0) return 'B';
	if(x==1) return 'R';
	if(x==2) return 'W';
} //将数换成字母
void solve() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {
		char c=getchar();
		while(c!='B'&&c!='R'&&c!='W') c=getchar();
		if(c=='B') a[i]=0;
		if(c=='R') a[i]=1;
		if(c=='W') a[i]=2;
	} //将字母换成数
	int sum=0;
	int f=(n&1)?1:-1;//若 n 为奇数，答案则为正数；若 n 为负数，答案则为偶数
	for(int i=1;i<=n;i++) {
		sum=(sum+a[i]*C(n-1,i-1)%3)%3;
	}
	putchar(get((sum*f%3+3)%3));
	puts("");
	return;
}
int main() {
	solve();
	return 0;
}
```

---

## 作者：HappyJaPhy (赞：1)

- [[ARC117C] Tricolor Pyramid](https://www.luogu.com.cn/problem/AT_arc117_c)
- [博客阅读体验 ~~（也许）~~ 更佳](https://www.luogu.com.cn/blog/ImDustSans/solution-at-arc117-c)
# 题意
- 给一个金字塔的底部颜色组成和生长规律，问顶部的颜色是什么。

# 分析
- 试几次就可以很容易得到的一种构造：令颜色 B 为 $0$，W 为 $1$，R 为 $2$。设左右两个方块的颜色分别为 $col_l$ 和 $col_r$，则生长规则可以描述为 $col_{now}\equiv-(col_l+col_r)\pmod 3$。因为底部每一个元素有 $C_{n-1}^{i-1}$ 种方式贡献到顶部元素上（一共要走 $n-1$ 步，其中有 $i-1$ 步是向左走，因此是 $C_{n-1}^{i-1}$），于是顶部元素颜色的表达式就出来了。
$$col_{top}\equiv(-1)^n\sum_1^n{C_{n-1}^{i-1}col_i}\pmod3$$
- 这里的 $p$ 很小，因此组合数直接用 Lucas 求解即可。

# 代码
```cpp
#include <bits/stdc++.h>
#define int long long
#define N 500005
using namespace std;
int n, a[N], ans;

inline int C(int n, int m) {
	if (n < m) return 0;
	int res = 1;
	for (int i = n - m + 1; i <= n; i++) res *= i;
	for (int i = 1; i <= m; i++) res /= i;
	return res % 3;
}

int Lucas(int n, int m) {
	if (m == 0) return 1;
	return Lucas(n / 3, m / 3) * C(n % 3, m % 3) % 3;
}

signed main() {
	scanf("%lld", &n);
	char ch = 0;
	while (ch < 'A' || ch > 'Z') ch = getchar();
	for (int i = 1; i <= n; i++) {
		if (ch == 'B') a[i] = 0;
		if (ch == 'W') a[i] = 1;
		if (ch == 'R') a[i] = 2;
		ch = getchar();
	}
	for (int i = 1; i <= n; i++) {
		ans += Lucas(n - 1, i - 1) * a[i] % 3;
		ans %= 3;
	}
	if ((n & 1) == 0) ans = (3 - ans) % 3;
	if (ans == 0) printf("B");
	if (ans == 1) printf("W");
	if (ans == 2) printf("R");
	return 0;
}
```

---

## 作者：_ZSR_ (赞：1)

### [AT_arc117_c [ARC117C] Tricolor Pyramid](https://www.luogu.com.cn/problem/AT_arc117_c)

我们把 $B,W,R$ 分别看成 $0,1,2$，那么一个格子的值 $w$ 为 $-(w_{l}+w_{r}) \bmod 3$。其中 $w_{l},w_{r}$ 分别表示左下和右下的格子的值。

我们把每个格子的值列出来就长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/ije9eari.png)

容易发现，这长得很像杨辉三角，只不过是倒过来而已。那么直接用二项式定理。由于模数很小并且为质数，所以我们使用卢卡斯定理。

code
```
#include <bits/stdc++.h>
using namespace std;
const int N=4e5+10;
int n;
int a[N];
char str[N];
int fac[10],ifac[10];
inline int ksm(int a,int b)
{
    int res=1;
    while (b)
    {
        if (b&1) res=res*a%3;
        a=a*a%3;
        b>>=1;
    }
    return res;
}
inline int C(int a,int b)
{
    if (a<b) return 0;
    if (a==0||b==0||a==b) return 1;
    return fac[a]*ifac[a-b]%3*ifac[b]%3;
}
inline int lucas(int a,int b)
{
    if (a<b) return 0;
    if (a==0||b==0||a==b) return 1;
    return C(a%3,b%3)*lucas(a/3,b/3);
}
int main()
{
    scanf("%d",&n);
    scanf("%s",str+1);
    fac[0]=1;
    for (int i=1;i<3;++i) fac[i]=fac[i-1]*i%3;
    ifac[2]=ksm(fac[2],2);
    for (int i=1;i>=0;--i) ifac[i]=ifac[i+1]*(i+1)%3;
    for (int i=1;i<=n;++i)
    {
        if (str[i]=='B') a[i]=0;
        else if (str[i]=='W') a[i]=1;
        else a[i]=2;
    }
    int ans=0;
    for (int i=1;i<=n;++i) ans=(ans+lucas(n-1,i-1)*a[i]%3)%3;
    if (n%2==0) ans=(3-ans)%3;
    if (ans==0) puts("B");
    else if (ans==1) puts("W");
    else puts("R");
    return 0;
}
```


---

## 作者：SError_ (赞：1)

讲一种跟其他题解完全不同的构造。

令 $B=1$，$W=2$，$R=4$，构造 $f(a,b)=(ab)^{-1}\bmod 7$.

可以发现这是一种符合题意的构造。考虑模拟统计答案的过程，以 $n=4$ 为例。

$$a_1,a_2,a_3,a_4$$

$$\Longrightarrow a_1^{-1}\cdot a_2^{-1},a_2^{-1}\cdot a_3^{-1},a_3^{-1}\cdot a_4^{-1}$$

$$\Longrightarrow a_1\cdot a_2^2\cdot a_3,a_2\cdot a_3^2\cdot a_4$$

$$\Longrightarrow a_1^{-1}a_2^{-3}a_3^{-3}a_4^{-1}$$

我们要做的就是求 $\displaystyle\prod_{i=1}^{n}a_i^{\binom{n-i}{i-1}}$ 模 $7$ 的值。另外如果 $n$ 为偶数，再对答案式求模 $7$ 的逆。

因为组合数比较大可以用欧拉定理降幂，即将组合数对 $6$ 取模。

对 $2,3$ 分别 Lucas 一下合并就好了。时间复杂度 $O(n\log_2 n +n\log_3 n)$.

~~如果 ARC 考场上像我这样做你就寄了~~

[评测记录](https://atcoder.jp/contests/arc117/submissions/46488952)

```cpp
#include<bits/stdc++.h>
#define N 400010
using namespace std;
int read(){
	int x=0,w=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')w=-1;ch=getchar();}
	while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x*w;
}
int n;char s[N];
const int P=7;
int inv[P],a[N];
int qpow(int k,int b){
	int ret=1;
	while(b){
		if(b&1)ret=ret*k%P;
		k=k*k%P,b>>=1;
	}
	return ret;
}
int C2(int n,int m){
	if(n<0||m<0||n<m)return 0;
	return 1;
}
int L2(int n,int m){
	if(n<0||m<0||n<m)return 0;
	if(!n||!m)return 1;
	return L2(n/2,m/2)*C2(n%2,m%2)%2;
}
int C3(int n,int m){
	if(n<0||m<0||n<m)return 0;
	if(!n||!m||n==m)return 1;
	return 2;//n=2,m=1
}
int L3(int n,int m){
	if(n<0||m<0||n<m)return 0;
	if(!n||!m)return 1;
	return L3(n/3,m/3)*C3(n%3,m%3)%3;
}
int CRT(int x2,int x3){
	if(x3==0)return x2?3:0;
	if(x3==1)return x2?1:4;
	return x2?5:2;
}
void solve(){
	n=read(),scanf("%s",s+1);
	int ans=1;
	for(int i=1;i<=n;i++){
		a[i]=(s[i]=='B')?1:(s[i]=='W'?2:4);
		ans=ans*qpow(a[i],CRT(L2(n-1,i-1),L3(n-1,i-1)))%P;
	}
	if(!(n&1))ans=inv[ans];
	putchar(ans==1?'B':(ans==2?'W':'R'));
	printf("\n");
}
int main(){
	inv[1]=1,inv[2]=4,inv[4]=2;
	int T=1;
	while(T--)solve();
	
	return 0;
}
```

---

## 作者：guozhetao (赞：0)

## 前言
今天早上模拟赛刚考这题，考场虽然写出来（思路和其他题解好像不太一样），但是不太会证明，若题解有不当之处或者代码可以被举出反例，请及时联系 [@guozhetao](https://www.luogu.com.cn/user/669924) 改正。

## 思路
**本题解定义 $bh(i,j)$ 为将第 $i$ 个点与第 $j$ 个点依据题意变换（如果颜色相同，则为它们的相同颜色；如果颜色不同，则为一个颜色与它们都不同的颜色）。**

因为 $2 \le n \le 400000$，因此直接模拟肯定过不了。

观察样例：
```
W
BR
RWB
RRBB
```

可以发现最上方的 `W` 根据题意是由 `B` 与 `R` 组合而成，而最低下一行的左右两边分别是 `B` 与 `R`。

考场上，我尝试其他几种情况，发现当最后一行个数是 $4$ 时，顶端的字母只和底端左右两个端点有关（且刚好与题目所提供的变化方式相同），于是我猜想：当最后一行个数为 $3^k + 1$ 时，顶端只和底端左右端点有关。

于是，我们每次对于 $n$，找到最大的 $k$ 使得 $3^k + 1 \leq n$，并枚举第 $n - 3 ^ k$ 层的情况：当 $(i + 3 ^ k \leq n)$ 时依次更新 $b_i = bh(i,i + 3^k)$，则此时我们将一个长度为 $n$ 的序列变为一个长度为 $n - 3^k$ 的序列，然后将 $n \gets n - 3^k$。重复以上操作直至 $n < 4$。

操作后若 $n \not= 1$，因为 $n$ 很小，将最后的几行依照题意枚举即可。
## 代码
[记录](https://www.luogu.com.cn/record/146355594)
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n;
char b[400005];
int find(int x) {
	int tot = 1;
	while(x >= 3) {
		x /= 3;
		tot *= 3;
	}
	return tot;
}
signed main() {
	//freopen("B.in","r",stdin);
	//freopen("B.out","w",stdout);
	scanf("%lld",&n);
	for(int i = 1;i <= n;i++) cin >> b[i];
	int ans = n;
	while(ans >= 4) {
		int x = find(ans - 1);//寻找最大的 3^k
        //依题意进行模拟
		for(int i = 1;i + x <= n;i++) {
			if(b[i] == b[i + x]) continue;
			else if(b[i] == 'B' and b[i + x] == 'W') b[i] = 'R';
			else if(b[i] == 'W' and b[i + x] == 'B') b[i] = 'R';
			else if(b[i] == 'W' and b[i + x] == 'R') b[i] = 'B';
			else if(b[i] == 'R' and b[i + x] == 'W') b[i] = 'B';
			else b[i] = 'W';
		}
		ans -= x;
		//printf("%lld\n",ans);
	}
    //最后几行自己模拟
	for(;ans > 1;ans--) {
		for(int i = 1;i < ans;i++) {
			if(b[i] == b[i + 1]) continue;
			else if(b[i] == 'B' and b[i + 1] == 'W') b[i] = 'R';
			else if(b[i] == 'W' and b[i + 1] == 'B') b[i] = 'R';
			else if(b[i] == 'W' and b[i + 1] == 'R') b[i] = 'B';
			else if(b[i] == 'R' and b[i + 1] == 'W') b[i] = 'B';
			else b[i] = 'W';
		}
	}
	cout<<b[1]<<endl;
	return 0;
}
```
## 证明过程
因个人能力原因，本部分有参照[这篇题解](https://www.luogu.com.cn/blog/371825/solution-at-arc117-c)，若无法理解可跳过本部分。

设最底层个数为 $m(m = 3 ^ k + 1)$,若令 `B` 为 $0$，`W` 为 $1$，`R` 为 $2$，则顶层 $p \equiv -\sum b_i \times \dfrac{(m - 1)!}{i! \times (m - 1 - i)!} \pmod 3$。

由于 $m -1 \equiv 0 \pmod 3$，则当 $0 < i < m$ 时，$\dfrac{(m - 1)!}{i! \times (m - 1 - i)!} \equiv 0  \pmod 3$;

因此：$p \equiv -\sum b_i \times \dfrac{(m - 1)!}{i! \times (m - 1 - i)!} \equiv 6-b_0 - b_m\pmod 3$。

所以当最后一行个数为 $3^k + 1$ 时，顶端只和底端左右端点有关。

---

## 作者：TernaryTree (赞：0)

很巧妙的题，虽然我秒了。

一眼顶针鉴定为，这个东西得考虑在模 $3$ 意义下，去给 `B,W,R` 一个标号，分别记为 $0,1,2$ 吧。然后我们发现实际上有

$$f_{i,j}=2(f_{i+1,j}+f_{i+1,j+1})$$

额哦，然后 $2$ 可以提出来，剩下的就是杨辉三角，最下面一行每个点对第一行的贡献是 $\dbinom{n-1}{i}$。所以答案是

$$2^{n-1}\sum_{i=0}^{n-1}\dbinom{n-1}{i}a_i\bmod 3$$

再对应回三个字母即可。

Lucas 计算。

---

## 作者：出言不逊王子 (赞：0)

发现颜色值域是 $3$，考虑位运算。

然后考虑位数为 $2$ 的运算，然后发现没法做。

有三个数为啥不考虑三进制呢？

考虑异或的定义是“不进位加法”，那我们把异或的真值表给写出来，发现是一个夹杂着四则运算和位运算的狗屎式子。

显然没有结合律，做不了了。

考虑四则运算。

我们发现 $a\ne b\to r=3-a-b$，然后我们惊喜地发现 $a=b\to r=3-a-b$ 同样成立。

有了结合律就可以做了。

把规律写下来，会发现答案的绝对值是 $\sum C_{n-1}^{i-1} a_i$，如果遍历了奇数次答案为负，偶数次答案为正。

但是模数是 $3$，所以要运用卢卡斯定理。

```cpp
//已删除暴戾语言注释
#include<bits/stdc++.h>
#define fs(i,x,y,z) for(int i=x;i<=y;i+=z)
#define ft(i,x,y,z) for(int i=x;i>=y;i+=z)
#define int long long
#define ull unsigned long long
#define db double
#define ms(a,b) memset(a,b,sizeof(a))
#define sz(a) sizeof(a)
#define pii pair<int,int>
using namespace std;
const int rw[]={-1,0,1,0,-1,1,-1,1},cl[]={0,1,0,-1,-1,1,1,-1};
const int N=500001,inf=3;
inline int read(){
	int date=0,w=1;char c=0;
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){date=date*10+c-'0';c=getchar();}
	return date*w;
}
int ksm(int x,int y){
	int r=1;while(y){
		if(y&1) r=r*x%inf;
		x=x*x%inf;y>>=1;
	}return r;
}
char s[N];
int n,m,res;
int fac[N],inv[N];
int c(int x,int y){
	if(y<inf){//inf=3,C(x,y)
		if(x<y) return 0;
		if(y==0||x==y) return 1;
		if(y==1) return x%inf;
		return (x*(x-1)/2)%inf;
	}return c(x/inf,y/inf)*c(x%inf,y%inf)%inf;
}
void mian(){
	n=read();scanf("%s",s+1);
	//摩尔投票？
	//AABAB->ACCC->BCC->AC->B
	//荒谬的结论，我喜欢
	//考虑一个规律是ABABA->CCCC
	//ABAB是CCC
	//AAABA->AACC->ABC->CA->B
	//？
	//AAACA->AABB？？？
	//两个数最后
	//BAAB->CAC->BB->B
	//AB串怎么这么多B
	//如果BACCCAB->CBCCBC->AACAA->ABBA->CBC->AA->A
	//没有规律，但是现在能咋搞？
	//AABBCC->ACBAC->BACB->CBA->AC->B
	//中间的，最大的榜？问题是我们现在不会去打复活赛啊，每个数字都有表达方式
	//AABB->ACB->BA->C，不一样了
	//那说明形态是有关的，那AAAAB呢？是AAAC-AAB-AC-B，发现没啥区别
	//所以我们只要看最大的哪一个块？AAABB-AACB-ABA-CC-C???????????
	//****！
	//猜测：周期性
	//每个位置不一样的话，跑两趟又回来了
	//如果有相同位置呢？
	//和位运算有关，三个是00 01 10，则合并起来是(11)^(a|b)？问题在于说如果相等的话应该直接合并
	//不相等是三个取反，相等是直接等于其中一个……(a^b)^((s^a))
	//真值分布和xor很像，但是12得调换
	//AAB->B，少的
	//AAAB-> 
	int res=0,lvl=n-1;
	fs(i,1,n,1) (res+=c(n-1,i-1)*(s[i]-'A')%inf)%=inf;//
	if(lvl&1) (res*=2)%=inf;
	cout<<(char)(res+'A')<<'\n';
}
signed main(){
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	int t=read();while(t--) mian();
	return 0;
} 
//C(n,m)=C(n/p,m/p)*C(n%p,m%p)
```

---

## 作者：凑个热闹吖 (赞：0)

[ [ARC117C] Tricolor Pyramid](https://www.luogu.com.cn/problem/AT_arc117_c)

今天模拟赛的 T2。

介绍一种非卢卡斯的做法，而且要快一些，最慢的点 5ms。

其他题解也讲得很清楚了，大概就是让我们求 $(-1)^{n + 1} \sum_{i = 0}^{n - 1}C_{n - 1} ^ {i}a_i \pmod 3$。(如果为负数加上 $3$)

由组合数的计算公式有 $C_{m}^{n} = \frac{C_{m}^{n - 1}(m - n + 1)}{n}$。

由于是在模 $3$ 意义下的运算，所以特殊处理 $3$ 这个质因子。

用 $num$ 记 $C_{m}^{n - 1}$ 的质因子 $3$ 的个数，$las$ 记 $C_{m}^{n - 1}$ 除去所有质因子 $3$ 的值。

即 $C_{m}^{n - 1} = 3 ^ {num}las$，其中 $3 \nmid las$

计算 $C_{m}^{n}$ 时加上 $(m - n + 1)$ 的质因子 $3$ 的个数，再减去 $n$ 中的个数。

如果此时 $num$ 非零，说明 $C_{m}^{n}$ 的值在模 $3$ 的意义下为 $0$。

如果 $num$ 为零，就去掉 $(m - n + 1)$ 与 $n$ 中所有的质因子 $3$ 后与 $las$ 正常运算即可。

由于 $1$ 和 $2$ 在模 $3$ 意义下的逆元都是本身，所以可以直接把除法变为乘法。

详见代码。

```cpp
#include<bits/stdc++.h>
#define rep(i , m , n) for(register int i = m; i <= n; i++)

using namespace std;
const int INF = 0x3f3f3f3f;
char c[400005];
int a[400005];
int n;
char ans[3] = {'W' , 'B' , 'R'};
int d[200];
int main(){
	d['W'] = 0 , d['B'] = 1 , d['R'] = 2;
	scanf("%d" , &n);
	scanf("%s" , c + 1);
	rep(i , 1 , n)a[i] = d[c[i]];	
	int k = a[1];
	int num = 0 , las = 1;
	rep(i , 2 , n){
		int x = i - 1 , y = n - i + 1;
		int tmp = 0;
		while(y % 3 == 0)y /= 3 , tmp++;
		while(x % 3 == 0)x /= 3 , tmp--;
		num += tmp;
		int temp = pow(3 , num);
		x %= 3 , y %= 3;
		las *= (x * y) , las %= 3;
		if(num)continue;
		k += las * a[i];
	}
	if(n % 2 == 0)k = (3 - (k % 3)) % 3;
	else k = (3 + (k % 3)) % 3;
	printf("%c\n" , ans[k]);
	return 0;
}
```


---

## 作者：masonpop (赞：0)

贡献法。设 R，B，W 分别代表 $0,1,2$，则合并
 $(a,b)$ 的过程就是合并为模 $3$ 意义下的 $(-a-b)$。然后发现，这个符号每隔一层就反过来。

然后就成板题了。考虑位置 $i$ 贡献的次数。在往上的过程中，需要选择 $i-1$ 次操作往左，其方案数就是 $C_{n-1}^{i-1}$。然后考虑层数的奇偶性，偶数层则结果取反（负贡献）。模 $3$ 即可。

卢卡斯定理处理组合数，答案很容易统计。[代码](https://www.luogu.com.cn/record/125082186)。

---

