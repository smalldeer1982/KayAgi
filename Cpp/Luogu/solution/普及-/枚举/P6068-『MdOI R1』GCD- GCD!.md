# 『MdOI R1』GCD? GCD!

## 题目描述

灵喜欢 $\mathrm{gcd}$，也就是 **最大公约数**。如果你不知道什么叫做最大公约数，你可以访问 [最大公约数 - OI Wiki](https://oi-wiki.org/math/gcd/)。

灵给了你一个正整数 $n$，要你把它分成三个 **互不相等的** 正整数 $a,b,c$ 之和，使得 $\mathrm{gcd}(a,b,c)$ 最大。

## 说明/提示

【样例解释】

将 $12$ 分成 $2+4+6$，可以证明 $\gcd(2,4,6)=2$ 为可能达到的最大值。

将 $27$ 分成 $3+6+18$，可以证明 $\gcd(3,6,18)=3$ 为可能达到的最大值。

$5$ 无法分成三个互不相等的正整数之和，输出 `-1`。

---

【数据范围】

**本题采用捆绑测试。**

| 子任务编号 | $n\leq$ | 分值 |
| :--------: | :-----: | :--: |
|     1      |  $50$   |  17  |
|     2      |  $500$  |  19  |
|     3      | $10^5$  |  23  |
|     4      | $10^9$  |  41  |

对于 $100\%$ 的数据，$1\le T \le 100$，$1\le n\le 10^9$。

## 样例 #1

### 输入

```
3
12
27
5
```

### 输出

```
2
3
-1
```

# 题解

## 作者：FCBM71 (赞：48)

其实是很简单的一道题，用不着二分再check什么的    

假设这个最后的答案为 $g$  
并假设 $a=A\times g$，$b=B\times g$，$c=C\times g$，令 $k=A+B+C$        
那么总和 $n=(A+B+C)\times g=k\times g$

由于 $g$ 和 $k$ 都是整数，所以他们都是 $n$ 的约数。为了最大化 $g$，我们需要 $k$ 尽可能小。

因为$a,b,c$ 互不相等，所以 $A,B,C$ 也一定互不相等。因此 $k$ 也一定能表示成三个互不相等的整数的和。什么样的 $k$ 才可以呢？只要 $k\geq 6$ 就可以了。因为 $k=6$ 是恰好为 $1+2+3$，比 $6$ 更大时一定可以拆成 $1+2+(k-3)$ 的形式。  

综上，本题要求的就是： 寻找一个最小的 $k$，使得 $k\geq 6$ 且 $n\%k=0$。  
输出的答案应该是 $n/k$。   
可以根据筛质数时的原理在 $O(\sqrt{n})$ 的复杂度内解决


---

## 作者：皎月半洒花 (赞：13)

这里说一个 $O(T\max(\log^3 n,n^\frac{1}{4}))$ 的优（胃）秀（疼）算法。

考虑对于一种拆分是最优的。即 $(a,b,c)=d$，$d$ 为所求，那么发现会有 $d\cdot (\frac{a}{d}+\frac{b}{d}+\frac{c}{d})=n$。发现当 $\frac{a}{d},\frac{b}{d},\frac{c}{d}$ 三者不同时，一定可以转化成其中一个数 $=d$ 的构造方式。

所以考虑质因数分解之后枚举 $\frac{n}{d}$。发现当 $\frac{n}{d}\leq 5$ 的时候，当前枚举的 $d$ 不可以让 $\frac{a}{d},\frac{b}{d},\frac{c}{d}$ 三者不同。所以判掉这些数据，剩下的取 $\rm max$ 即可。

发现现在要求的，就是从 $n$ 的所有分解里面，挑出一个最接近 $6$ 且 $\geq 6$ 的构造 $\frac{n}{d}$ 的方案。发现最多需要三个素因子才可以超过 $6\to (2,2,2)$，最少的话一个就足够了。所以考虑 $\log ^3n$ 三重循环枚举所有的质因子即可。

质因数分解完全可以 $\rm pollard-rho$。最后复杂度 $O(T\max(\log^3 n,n^\frac{1}{4}))$

代码就不展示了，按照上述方式实现，代码应该十分 $naive$。

---

## 作者：Gmt丶FFF (赞：11)

这是作者第一次发题解，若有不清楚的地方，敬请原谅。

其实这道题并不需要那么复杂的方法，只需要对每个数,也就是n/gcd(a,b,c)进行枚举，从1到sqrt(n)进行枚举。我们用x存储n/gcd(a,b,c)。如果n%x!=0，那gcd(a,b,c)就不是整数，自然就要continue。

然后我们再用一个y存储gcd(a,b,c)，也就是存储n/x。 当x<6,y<6时，因为过于小无法建成三个不同的数，所以当x>=6时，答案可以存储，我们就把答案ans=y，反之y>=6时，ans=x，这样可以保证每三个数构成时不会漏掉每一项。

下面是循环参考代码，因为上面解释，下面就不加注释了。

```
for(int i=1;i*i<=n;i++){
    if(n%i!=0) continue;
    int x=i,y=n/i;
    if(x>=6) ans=max(ans,y);
    if(y>=6) ans=max(ans,x);
}
```

接下来就只剩输入和输出的代码还有当n<6时的代码了，注意在输入时带上个ans=0，否则会像作者一样全WA。

---

## 作者：老咸鱼了 (赞：11)

比赛的时候差不多最快的代码了，没有读入优化。

因为要是三个互不相同的数，所以我们除去三个数后的最大公约数的三个数的和一定是大于等于6的倍数因为6是1+2+3，不可能拆分成比这个还小的，所以我们从6开始一直到根号n枚举（和素数判断原理差不多），如果有一个数能被n整除，那么所得到的这个就一定是拆分的三个数能组成的最大的最大公约数。

注意一下数比较小的情况像样例给的12。我们只需要判断它除以这个数后得到的数是不是大于6就行了。

整体时间复杂度大约为O(T*根号n)。
```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int main(){
	int n;
	cin>>T;
	while(T--){
		cin>>n;
		if(n<6)cout<<-1<<endl;
		else{
			bool v=false;
			for(int i=6;i*i<=n;i++){
				if(n%i==0){
					cout<<n/i<<endl;v=true;
					break;
				}
			}
			if(!v){
				for(int i=5;i>=1;i--){
					if(n%i==0&&n/i>=6){
						cout<<i<<endl;break;
					}
				}
			}
		}
	}
	return 0;
}
```


---

## 作者：HohleFeuerwerke (赞：9)

刚结束就来的抱灵选手。

#### 前言

[题目在此，需者自取。](https://www.luogu.com.cn/problem/P6068)

#### 正文

先讲部分分啊。

实在不知道 $n\leq 200$ 什么用啊...

$n\leq 50$：珂以直接枚举，每次都做一遍，算最小值，但还是可能会T？

$n\leq 10^5$：使用 $O(\frac{Tn}{6})$ 算法，给个思路啊（因为待会儿代码也有）。这题珂以转化，变成：
$$a=Ax,b=Bx,c=Cx,x=gcd(a,b,c)$$

然后因为要 $x$ 尽量大，所以直接使 $A+B+C$ 尽量小。

枚举 $A+B+C∈[6,n/6]$，就能求出来了。

---
下面是正解：

盲猜结论：如果 $x_{max}>5$ 那么直接得到 $x∈[6,\sqrt{n}]$，枚举即可，但是注意特判 $6\leq n\leq 36$，代码：

```cpp
#include<bits/stdc++.h>
#define HohleFeuerwerke using namespace std
HohleFeuerwerke;
int t;
inline int work1(int x)
{
	for(int i=6;i*i<=x;i++)
		if(x%i==0) return x/i;
	for(int i=5;i>1;i--)
		if(x%i==0&&(x/i)>=6) return i;
	return 1;
}
inline int work2(int x)
{
	int z=6;
	while(x%z!=0) z++;
	return x/z;
}
int main()
{
	cin>>t;
	while(t--){
		int n;cin>>n;
		if(n<6) cout<<-1<<endl;
		else if(n<=36)cout<<work2(n)<<endl;
		else cout<<work1(n)<<endl;
	}
}
```

---

## 作者：xh39 (赞：3)

## 59pts思路

此题的目的就是要求$<=n÷6$的最大因数。为什么这样,下面会解释。

## 1.为什么要求最大因数?
如果是一个因数$i$,那么它就可以分解为$a$,$b$,$c$都可以写成$k×i$的形式,最大公因数就至少是$i$。

$k$是这3个数的公约数。所以求到的就是最大公约数。
## 2.为什么是<=n÷6?
> 要你把它分成三个 互不相等的 正整数 a,b,c 之和 --[题面](https://www.luogu.com.cn/problem/P6068)第2行某加粗部分。

因为构成$a,b,c$的$k$,最小也得是$1,2,3$(互不相等 正整数,这两个条件推来的,我就不多解释)。
## 59pts代码
这是以上思路的代码($59pts$)
```cpp
#include<iostream>
#include<cmath>
using namespace std;
int Main(int n){
	if(n<6){ //最小的3个正整数是1,2,3。其和为6。小于6则不可能分解成3个正整数。
		return -1;
	}
	int i,ykb;
	for(i=n/6;;--i){ //倒序枚举,只要已找到就一定是max,就直接返回。比顺序要方便而且快很多。
		if(!(n%i)){ //此句相当于if(n%i==0),次数是它的因数。
			return i;
		}
	}
}
int main(){
	int n,a,i;
	cin>>n;
	for(i=0;i<n;++i){
		scanf("%d",&a);
		cout<<Main(a)<<endl;
	}
	return 0;
}
```
基本思路已经出来了。可是直接枚举会tle。

## 优化为100pts

一个大的因数一定是($n$÷一个小的因数)。所以我们直接枚举小因数,就可以得出大因数。可是从1枚举到$n÷6$还是会tle。所以还是要继续优化。

由于小因数超过$sqrt(n)$,得出来的大因数就小于小因数(可以自己举个例子来理解,此处$sqrt$是开平方根),那么小因数既然不能整除,大因数也不可能可以整除。就不用枚举了。

这样优化一下就可以AC了。时间复杂度为$O(t×sqrt(n))$。
## AC代码
```cpp
//许多注释在上一个59pts注释里了。
#include<iostream>
#include<cmath>
using namespace std;
int Main(int n){
	if(n<6){
		return -1;
	}
	int i,ykb;
	ykb=sqrt(n); //sqrt就是开平方根的函数。调用sqrt是要时间的,如果不存每循环一次就要调用一次,所以先存好,可以节约时间。
	for(i=6;i<=ykb;++i){
		if(!(n%i)){
			return n/i;
		}
	}
	for(i=min(n/6,5);;--i){ //注意如果大因数枚举失败,从5~1我们没有枚举过,所以还是要枚举的。
		if(!(n%i)){
			return i;
		}
	}
}
int main(){
	int n,a,i;
	cin>>n;
	for(i=0;i<n;++i){
		scanf("%d",&a);
		cout<<Main(a)<<endl;
	}
	return 0;
}
```

---

## 作者：lgnotus (赞：2)

下午一直在颓游戏，五点半才来比赛，T1乱打骗了几分过来捧场，差点抱灵$qwq$
## 分析
我们令$d=gcd(a,b,c)$,如果$n$可以被分解成三个正整数之和（即$n>5$），那么
$$\begin{aligned} n=k_1\times d+k_2\times d+k_3\times d\\
\end{aligned}$$
合并同类项，得：
$$n=d(k_1+k_2+k_3)$$
显然，$(k_1+k_2+k_3)$不能有两个或两个以上的数相同（即$k_1+k_2+k_3>5$)），否则$k_1\times d,k_2\times d,k_3\times d$就会有两个或两个以上的数相同（即$a,b,c$会有两个或两个以上的数相同），不符合题意。

另外的，如果$n$为质数，答案必定为$1$

我们可以枚举$k_1+k_2+k_3$,同时还可以直接得到$d$,如果两个值大于等于$6$,  取最大值即可

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
bool isprime(int N){
    for(int i=2;i<=sqrt(N);i++){
        if(N%i==0)return 0;
    }
    return 1;
}
int main(){
    ios::sync_with_stdio(false);
    cin>>t;
    while(t--){
        cin>>n;
        if(n<=5)cout<<-1<<endl;
        else if(isprime(n))cout<<1<<endl;
        else {
            int w=0;
            int ans=0;
            for(int i=1;i*i<=n;i++){
                if(n%i==0){
                    if(i>=6)ans=max(ans,n/i);
                    if(n/i>=6)ans=max(ans,i);
                }
            }
            if(ans)cout<<ans<<'\n';
        }

    }
    return 0;
}
```
      

---

## 作者：cirnovsky (赞：2)

其实有一种很简单的方法。。。

我们可以直接枚举答案。。。

主要是判断，具体看代码注释

因为做法是在是过于简单，故代码中的注释可能不会很多。

但是因为做法简单，所以大家应该都能看懂（不要说我说明过少。。。

时间复杂度:$\Theta(T\sqrt n)$

```cpp
using namespace std;

int ans;
int T, n;

signed main() {
	for (read(T); T; --T) {
	    read(n);
		if (n <= 5) { // 特判-1
		    write(io_l, -1);
		    continue;
		}
		int res = 0;
		for (int i = 2; i * i <= n; ++i) { // 枚举每一个约数
			if (n % i == 0) {
				if (n / i >= 6) res = max(res, i); // 因为我们需要将n分为3份，所以n/i应该>=6
				if (n / (n / i) >= 6) res = max(res, n / i); 
			}
		}
		write(io_l, res ? res : 1);
	}
	return 0;
}
```

---

## 作者：Alarm5854 (赞：2)

这道题目是一道数论题，我来给大家讲一下做题的方法。

首先，由于 3 个正整数互不相同，所以可以发现 $n<6$ 时是无解的，当 $n\ge6$ 时，才会有解。
### 解法 1：
直接枚举 3 个互不相同的正整数 $i,j,k$，若 $i+j+k=n$，就尝试更新一次答案，时间复杂度为 $O(Tn^3\log n)$（gcd的时间复杂度为 $O(\log n)$），期望得分：17 分。
### 解法 2：
由于要保证 3 个正整数的和为 $n$，所以可以只枚举 2 个互不相同正整数 $i,j$，另外一个数 $k=n-i-j$，若满足 $k>0,k\neq i,k\neq j$，就更新答案，时间复杂度为 $O(Tn^2\log n)$，期望得分：36 分。
### 解法 3：
利用解法 2，可以先打个表，打出 $6$ 到 $100$ 之间的表，发现所有的答案都不超过 $\lfloor n/6\rfloor$，且这个数能整除 $n$。其实也很容易证明，设 $n=x+2x+kx=(k+3)x$，其中，$k\ge3$，$x$ 为 $n$ 的一个因数，所以可以从 $\lfloor n/6\rfloor$ 到 $1$，倒着枚举，枚举到第一个能整除 $n$ 的数，时间复杂度为 $O(Tn)$，期望得分：59 分。
### 解法 4：
根据解法 3，可以先处理出 $n$ 的所有因数，再二分查找出小于等于 $\lfloor n/6\rfloor$ 的因数，可以使用 C++STL 中的 `lower_bound` 函数，时间复杂度为 $O(T\sqrt n\log n)$，期望得分：100分。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
FILE *fin, *fout;
inline int read(int &x) {//快读和快写（虽然比赛中没能成功卡常）
	char c = 0; int f = x = 0;
	while (c < 48 || c > 57) {
		if (c == -1) return 0;
		if (c == '-') f = 1; c = fgetc(fin);
	}
	while (c > 47 && c < 58) x = (x << 3) + (x << 1) + (c & 15), c = fgetc(fin);
	if (f) x = -x; return 1;
}
inline void write(int x) {
	if (x < 0) return fputc(45, fout), write(-x);
	if (x > 9) write(x / 10);
	fputc((x % 10) | 48, fout);
}
inline void write(char c) {
	fputc(c, fout);
}
int T, n, size, ans;
vector<int> a;
inline vector<int> work(int n) {
	vector<int> res;
	for (int i = 1; i * i <= n; ++i)
		if (!(n % i)) {
			res.push_back(-i);//这里用相反数，因为lower_bound找的是大于等于x的数
			if (i * i != n) res.push_back(-n / i);
		}
	sort(res.begin(), res.end()); return res;//要排序，才能用lower_bound，一个数的约数上界为2*sqrt(n)，故单次时间复杂度为O(sqrt(n)*log(n))
}
signed main() {
	#ifdef ONLINE_JUDGE
	fin = stdin;
	fout = stdout;
	#else
	fin = fopen("P6068.in", "rb");
	fout = fopen("P6068.out", "wb");
	#endif
	read(T);
	while (T--) {
		read(n), ans = 0;
		if (n < 6) {//特判n<6，直接输出-1
			write(-1LL), write('\n');
			continue;
		}
		a = work(n), ans = -(*lower_bound(a.begin(), a.end(), -n / 6));//注意负号不能少
		write(ans), write('\n');
	}
	return 0;
}
```
其实，有一个更优的，时间复杂度为 $O(T\sqrt n)$ 的做法，比我的解法更优，但是我就不说了。

---

## 作者：Skies (赞：1)

Tip:本文very详实，~~适合蒟蒻食用~~。

首先，可设 n=a+b+c,gcd(a,b,c)=p

根据[乘法分配律](https://baike.baidu.com/item/%E4%B9%98%E6%B3%95%E5%88%86%E9%85%8D%E5%BE%8B/2285256?fr=aladdin)
的逆运算，可变为：n=p(a/p+b/p+c/p)=p(a1+b1+c1)

可以看出,a1!=b1!=c1,又因题目说a,b,c是不同的自然数

所以a1+b1+c1的最小值为1+2+3=6.

其次，我们来看看因数的特点

拿24举例

因数:1 2 3 4 6 8 12 24

惊喜地发现首尾乘积都为24

所以只要求出其中一个就可以算出另一个了！！！

# code
```cpp
#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;
const int N= 10050;
#define inf 0x3f3f3f3f
#define ll long long
#define ull unsigned long long
inline int read(){int x=0,f=1;char ch=getchar();while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
inline void write(int x){if(x==0){putchar(48);return;}int len=0,dg[20];while(x>0){dg[++len]=x%10;x/=10;}for(register int i=len;i>=1;i--)putchar(dg[i]+48);}
int t;
int f(int a)
{
	int ans=-1;
	if(a<=5)//最小为3,2,1,和为6，若小于6，舍去 
	{
		return -1;
	}
	for(int i=1;i<=sqrt(a);i++)
	{
		if(a%i==0)
		{
			//第一种  一组中较小的一个——i
			if(a/i>=6)ans=max(ans,i) ;
			//第二种  一组中大的一个——a/i
//			if(a/(a/i)>=6) 化简qwq 
			if(i>=6)ans=max(ans,a/i) ;
		}
	}
	return ans;
}
int main()
{
    t=read();
    while(t--)
    {
    	int kk=read();
    	printf("%d\n",f(kk));
	  }
}
```
管理员小哥哥求过QwQ

---

