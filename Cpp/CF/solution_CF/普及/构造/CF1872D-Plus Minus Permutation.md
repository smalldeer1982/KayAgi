# Plus Minus Permutation

## 题目描述

You are given $ 3 $ integers — $ n $ , $ x $ , $ y $ . Let's call the score of a permutation $ ^\dagger $ $ p_1, \ldots, p_n $ the following value:

 $ $$$(p_{1 \cdot x} + p_{2 \cdot x} + \ldots + p_{\lfloor \frac{n}{x} \rfloor \cdot x}) - (p_{1 \cdot y} + p_{2 \cdot y} + \ldots + p_{\lfloor \frac{n}{y} \rfloor \cdot y}) $ $ </span></p><p>In other words, the <span class="tex-font-style-it">score</span> of a permutation is the sum of  $ p\_i $  for all indices  $ i $  divisible by  $ x $ , minus the sum of  $ p\_i $  for all indices  $ i $  divisible by  $ y $ .</p><p>You need to find the maximum possible <span class="tex-font-style-it">score</span> among all permutations of length  $ n $ .</p><p>For example, if  $ n = 7 $ ,  $ x = 2 $ ,  $ y = 3 $ , the maximum <span class="tex-font-style-it">score</span> is achieved by the permutation  $ \[2,\\color{red}{\\underline{\\color{black}{6}}},\\color{blue}{\\underline{\\color{black}{1}}},\\color{red}{\\underline{\\color{black}{7}}},5,\\color{blue}{\\underline{\\color{red}{\\underline{\\color{black}{4}}}}},3\] $  and is equal to  $ (6 + 7 + 4) - (1 + 4) = 17 - 5 = 12 $ .</p><p> $ ^\\dagger $  A permutation of length  $ n $  is an array consisting of  $ n $  distinct integers from  $ 1 $  to  $ n $  in any order. For example,  $ \[2,3,1,5,4\] $  is a permutation, but  $ \[1,2,2\] $  is not a permutation (the number  $ 2 $  appears twice in the array) and  $ \[1,3,4\] $  is also not a permutation ( $ n=3 $ , but the array contains  $ 4$$$).

## 说明/提示

The first test case is explained in the problem statement above.

In the second test case, one of the optimal permutations will be $ [12,11,\color{blue}{\underline{\color{black}{2}}},4,8,\color{blue}{\underline{\color{red}{\underline{\color{black}{9}}}}},10,6,\color{blue}{\underline{\color{black}{1}}},5,3,\color{blue}{\underline{\color{red}{\underline{\color{black}{7}}}}}] $ . The score of this permutation is $ (9 + 7) - (2 + 9 + 1 + 7) = -3 $ . It can be shown that a score greater than $ -3 $ can not be achieved. Note that the answer to the problem can be negative.

In the third test case, the score of the permutation will be $ (p_1 + p_2 + \ldots + p_9) - p_9 $ . One of the optimal permutations for this case is $ [9, 8, 7, 6, 5, 4, 3, 2, 1] $ , and its score is $ 44 $ . It can be shown that a score greater than $ 44 $ can not be achieved.

In the fourth test case, $ x = y $ , so the score of any permutation will be $ 0 $ .

## 样例 #1

### 输入

```
8
7 2 3
12 6 3
9 1 9
2 2 2
100 20 50
24 4 6
1000000000 5575 25450
4 4 1```

### 输出

```
12
-3
44
0
393
87
179179179436104
-6```

# 题解

## 作者：hjqhs (赞：4)

简单贪心。  
容易想到 $p_{k_1 \times x}(1 \le k_1 \le \lfloor \frac{n}{x} \rfloor)$ 尽量放大的数，$p_{k_2 \times y}(1 \le k_2 \le \lfloor \frac{n}{y} \rfloor)$ 尽量放小的数。然后运用等差数列求和公式即可。
```cpp
int lcm(int x,int y){return x/__gcd(x,y)*y;}
int sum(int st,int ed,int num){return (st+ed)*num/2;}
void solve(){
  cin>>n>>x>>y;
  int cx=n/x,cy=n/y,cz=n/lcm(x,y);
  cx-=cz,cy-=cz;
  cout<<sum(n-cx+1,n,cx)-sum(1,cy,cy)<<'\n';
}
```

---

## 作者：an_ancient_ghoul (赞：2)

# 题目翻译
### 题目大意
给定三个整数 $n,x,y(1 \le n \le 10^9, 1 \le x, y \le n)$，对于 $n$ 的排列 $p$，有     
$ score(p)=(p_x+p_{2x}+p_{3x}+ \ldots +p_{\lfloor \frac{n}{x}\rfloor \cdot x}) - (p_{y} + p_{2y} + \ldots + p_{\lfloor \frac{n}{y} \rfloor \cdot y}) $。    
求可能的最大 $score$。
### 输入
一行一个整数 $t$，共 $t$ 组数据。
接下来 $t$ 行，每行三个整数 $n,x,y$。
### 输出
共 $t$ 行，每行一个整数，表示最大的 $score$。
### 样例解释
样例第二行 $(n=12,x=6,y=3)$ 选择如下：  
$[12,11,\color{blue}{\underline{\color{black}{2}}}\color{b},4,8,\color{blue}{\underline{\color{red}{\underline{\color{black}{9}}}}}\color{b},10,6,\color{blue}{\underline{\color{black}{1}}}\color{b},5,3,\color{blue}{\underline{\color{red}{\underline{\color{black}{7}}}}}\color{b}]$   
$score=(9 + 7) - (2 + 9 + 1 + 7) = -3$
# solve
尽量把大的往 $p_{k_1x}(1\le k_1 \le \lfloor \frac{n}{x}\rfloor)$ 中丢，小的往 $p_{k_2y}(1\le k_2 \le \lfloor \frac{n}{y}\rfloor)$ 中丢，无视 $\gcd(x,y)\mid k_1x$ 或 $\gcd(x,y)\mid k_2y$ 的情况（因为没有贡献），完了。

# code

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int t,a,b,c,n,ca,cb,cc;
int gcd(int x,int y)
{
	if(x<y)swap(x,y);
	if(x%y)return gcd(y,x%y);
	return y;
}
signed main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n>>a>>b;
		c=a*b/gcd(a,b);
		ca=n/a,cb=n/b,cc=n/c;
		ca-=cc,cb-=cc;
		cout<<(n+n-ca+1)*ca/2-(1+cb)*cb/2<<endl;
	}
	return 0;
} 
```
完结撒花*★,°*:.☆(￣▽￣)/$:*.°★* 。

---

## 作者：Larryyu (赞：2)

## _Description_
每次询问给定 3 个数 $n,x,y$，$p_1,p_2\dots p_n$ 为一个 $n$ 的排列，求 $\sum\limits_{i=1,x\mid i}^n p_i-\sum\limits_{j=1,y\mid j}^n p_j$ 的最大值。
## _Solution_
我们发现，有一部分 $p_i$，$i$ 即能被 $x$ 整除，又能被 $y$ 整除，所以需要加一遍 $p_i$，又减一遍，相当于没有贡献。

设 $a_1,a_2\dots a_{\lfloor\frac{n}{x}\rfloor-\lfloor\frac{n}{\operatorname{lcm}(x,y)}\rfloor}$ 为 $n$ 以内，只被 $x$ 整除，不被 $y$ 整除的数，$b_1,b_2\dots b_{\lfloor\frac{n}{y}\rfloor-\lfloor\frac{n}{\operatorname{lcm}(x,y)}\rfloor}$ 为 $n$ 以内，只被 $y$ 整除，不被 $x$ 整除的数。

为了使总贡献最大，需要最大化 $p_{a_1}+p_{a_2}+\dots+p_{a_{\lfloor\frac{n}{x}\rfloor-\lfloor\frac{n}{\operatorname{lcm}(x,y)}\rfloor}}$，那么我们让这些数取 $n\sim n-(\lfloor\frac{n}{x}\rfloor-\lfloor\frac{n}{\operatorname{lcm}(x,y)}\rfloor)+1$，同时还需要最小化 $p_{b_1}+p_{b_2}+\dots+p_{b_{\lfloor\frac{n}{y}\rfloor-\lfloor\frac{n}{\operatorname{lcm}(x,y)}\rfloor}}$，那我们让这些数取 $1\sim \lfloor\frac{n}{y}\rfloor-\lfloor\frac{n}{\operatorname{lcm}(x,y)}\rfloor$ 就好了。

最后算出数值即可。
## _Code_
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
long long get(long long x){
	return (x+1)*x/2;
}
int gcd(int x,int y){
	if(x==0) return y;
	if(x>y) swap(x,y);
	return gcd(y%x,x);
}
void  solve(){
	long long n,x,y;
	cin>>n>>x>>y;
	long long cnt1=n/x,cnt2=n/y,cnt3=n/(x*y/gcd(x,y)); //lcm(x,y)=x*y/gcd(x,y)，不会的需自行了解一下
	cnt1-=cnt3,cnt2-=cnt3;
	long long sum1=get(n)-get(n-cnt1),sum2=get(cnt2);
	cout<<sum1-sum2<<endl;
}
int main(){
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```

完结撒花！~~

LaTeX 写久了，真的眼花啊！

---

## 作者：LEle0309 (赞：0)

第一次 CF 的 div3 过 3 题（蒻），~~然后发现 D 题也挺水。~~

[题目传送门](https://www.luogu.com.cn/problem/CF1872D) or [CF 传送门](https://codeforces.com/contest/1872/problem/D)

#### 题目分析：

算法：**贪心**。

把大的往 $ p_x+p_{2x}+p_{3x}+ \ldots +p_{\lfloor \frac{n}{x}\rfloor \cdot x} $ 中扔，把小的往 $ p_{y} + p_{2y} + \ldots + p_{\lfloor \frac{n}{y} \rfloor \cdot y} $ 中扔。

然后，忽略 $ \dfrac{n}{\operatorname{lcm}(x,y)} $ 个数，因为这些数既算在加上的部分，又算在减去的数里。

最后，我们来总结公式：

令 加上 $ s_1 $ 个数，减去 $s_2$ 个数，（不包括既加又减的），$ \operatorname{lcm}(x,y)=s_3 $

- 加上的个数：$ s_1=\dfrac{n}{x}-s_3 $

- 减去的个数：$ s_2=\dfrac{n}{y}-s_3 $

- 加上的和：$ n-s_1+1 $ 到 $ n $ 的 $ s_1 $ 个数（最大），总和 $ \dfrac{(n+n-s_1+1) \times s_1}{2} $。

- 减去的和：$ 1 $ 到 $ s_2 $ 的 $ s_2 $ 个数（最大），总和 $ \dfrac{(1+s_2) \times s_2}{2} $。

- 答案的最大值：$ \dfrac{(n+n-s_1+1) \times s_1}{2}-\dfrac{(1+s_2) \times s_2}{2} $

代码：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
long long n,x,y,s1,s2,s3,ans,t;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>x>>y;
		s3=n/(x*y/__gcd(x,y));//算法库里的最大公约数函数
		s1=n/x-s3;s2=n/y-s3;//套公式
		ans=(n+n-s1+1)*s1/2-(1+s2)*s2/2;//score(n) 的最大值
		cout<<ans<<'\n';//多测，注意换行
	}
	return 0;//div3 D 题就完成了
}
```

2023.10.1：

补充：这题样例有误导性，因为 $ 6 $ 是 $ 3 $ 的倍数，加上的数全部减掉了，保证减掉的两个数最小即可。

---

## 作者：Special_Tony (赞：0)

[洛谷传送门](/problem/CF1872D) & [CF 传送门](//codeforces.com/problemset/problem/1872/D)
# 思路
我们设 $a=p_x+p_{2x}+p_{3x}+\ldots+p_{\lfloor\frac{n}{x}\rfloor\cdot x}$，设 $alen=\lfloor\frac{n}{x}\rfloor$；设 $b=p_{y}+p_{2y}+\ldots+p_{\lfloor\frac{n}{y}\rfloor\cdot y}$，设 $blen=\lfloor\frac{n}{y}\rfloor$；设 $g$ 为 $a$ 和 $b$ 中的公共部分，设 $glen=\frac n{\operatorname{lcm}(x,y)}$。去掉公共部分的 $glen$ 个元素，$alen$ 变成了 $alen-glen$，$blen$ 就变成了 $blen-glen$。我们要让 $a-b$ 最大，则要把 $a$ 设为最大的 $n\sim(n-alen+1)$ 最小，$b$ 设为最小的 $1\sim(n-blen)$，$g$ 部分随便设。根据等差数列求和公式，$a$ 的总和是 $\frac{(n\times2-alen+1)\times alen}2$，$b$ 的总和是 $\frac{(blen+1)\times blen}2$，答案就是 $\frac{(n\times2-alen+1)\times alen-(blen+1)\times blen}2$。记得开 long long。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll; //不开 long long 见祖宗
ll t, a, b, g, n;
int main () {
	cin >> t;
	while (t --) {
		cin >> n >> a >> b;
		g = a * b / __gcd (a, b); //lcm
		a = n / a, b = n / b, g = n / g; //算个数
		a -= g, b -= g; //减重复部分
		cout << ((n * 2 - a + 1) * a - (b + 1) * b) / 2 << '\n';
	}
	return 0;
}
```

---

## 作者：Daniel_yao (赞：0)

## Problem
给定三个整数 $n,x,y$，有排列 $p_1,p_2,\dots,p_n$，规定这种排列的分数为：
$$
(p_{1 \cdot x} + p_{2 \cdot x} + \ldots + p_{\lfloor \frac{n}{x} \rfloor \cdot x}) - (p_{1 \cdot y} + p_{2 \cdot y} + \ldots + p_{\lfloor \frac{n}{y} \rfloor \cdot y})
$$
求所有长度为 $n$ 的排列的最大分数。
## Solve
不是一眼能懂得题了。

分析一下：要想分数最大，$(p_{1 \cdot x} + p_{2 \cdot x} + \ldots + p_{\lfloor \frac{n}{x} \rfloor \cdot x})$ 就要最大，$(p_{1 \cdot y} + p_{2 \cdot y} + \ldots + p_{\lfloor \frac{n}{y} \rfloor \cdot y})$ 就要最小。排列的顺序可以自定。那么就贪心的将 $n\sim n-\lfloor \frac{n}{x} \rfloor \cdot x+1$ 分配给 $p_{1 \cdot x}, p_{2 \cdot x}, \ldots, p_{\lfloor \frac{n}{x} \rfloor \cdot x}$，将 $1\sim \lfloor \frac{n}{y} \rfloor \cdot y$，贪心的分配给 $p_{1 \cdot y}, p_{2 \cdot y}, \ldots, p_{\lfloor \frac{n}{y} \rfloor \cdot y}$。

细节问题就是：那些 $\frac{x·y}{\gcd(x,y)}$ 的位置贡献相当于 $0$（加减抵消）。所以这些位置要腾出来的话，可以多分配一些给有贡献的位置。

最后答案为：
$$
((2n-(\frac{n}{x}-\frac{n}{\frac{xy}{\gcd(x,y)}})+1)·(\frac{n}{x}-\frac{n}{\frac{2xy}{\gcd(x,y)}})) - ((1+(\frac{n}{y}-\frac{n}{\frac{xy}{\gcd(x,y)}}))·(\frac{n}{y}-\frac{n}{\frac{2xy}{\gcd(x,y)}}))
$$
看着有点吓人，其实写起来也有亿点点吓人
## Code
```cpp
#include <bits/stdc++.h>
#define int long long
#define H 19260817
#define rint register int
#define For(i,l,r) for(rint i=l;i<=r;++i)
#define FOR(i,r,l) for(rint i=r;i>=l;--i)
#define MOD 1000003
#define mod 1000000007
#define inf 1e9

using namespace std;

namespace Read {
  template <typename T>
  inline void read(T &x) {
    x=0;T f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x*=f;
  }
  template <typename T, typename... Args>
  inline void read(T &t, Args&... args) {
    read(t), read(args...);
  }
}

using namespace Read;

void print(int x){
  if(x<0){putchar('-');x=-x;}
  if(x>9){print(x/10);putchar(x%10+'0');}
  else putchar(x+'0');
  return;
}

const int N = 1e7 + 10;

int T, n, x, y;

void solve() {
  read(n, x, y);
  int l1 = n / x, l2 = n / y, l3 = n / (x * y / __gcd(x, y));
  l1 -= l3, l2 -= l3;
  cout << ((2 * n - l1 + 1) * l1 / 2) - ((1 + l2) * l2 / 2) << '\n';
}

signed main() {
  read(T);
  while(T--) {
    solve();
  }
  return 0;
}
```

---

## 作者：One_JuRuo (赞：0)

## 思路

又又又是一道 CF 诈骗题。

对于 $x$ 选出来的数，我们尽量放大的，对于 $y$ 选出来的数，我们尽量放小的，但是呢，存在同时被 $x$ 和 $y$ 选出来的数，就随便放。

但是可以发现按照题目给的数据范围，这么找选择的数，然后放最大或者是放最小，肯定是超时。

所以我们可以直接算出有多少个 $x$ 选出来的数和有多少个 $y$ 选出来的数以及有多少个同时被 $x$ 和 $y$ 选出来的数就可以了。

很显然的，$x$ 能选 $\lfloor \frac n x \rfloor$ 个数，$y$ 能选 $\lfloor \frac n y \rfloor$ 个数，同时被 $x$ 和 $y$ 选的数有 $\lfloor \frac n {\gcd(x,y)}\rfloor$ 个。

所以我们把只被 $x$ 选的 $\lfloor \frac n x \rfloor-\lfloor \frac n {\gcd(x,y)}\rfloor$ 个数都放成最大的，用等差数列求和就是 $\frac {[n+n-(\lfloor \frac n x \rfloor-\lfloor \frac n {\gcd(x,y)}\rfloor)+1]\times(\lfloor \frac n x \rfloor-\lfloor \frac n {\gcd(x,y)}\rfloor)} 2$。

再把只被 $y$ 选的 $\lfloor \frac n y \rfloor-\lfloor \frac n {\gcd(x,y)}\rfloor$ 个数都放成最小的，用等差数列求和就是 $\frac {(1+\lfloor \frac n y \rfloor-\lfloor \frac n {\gcd(x,y)}\rfloor)\times(\lfloor \frac n y \rfloor-\lfloor \frac n {\gcd(x,y)}\rfloor)} 2$。

式子看着复杂，实际上很简单，自己想一想就能明白。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,n,a,b,lc,dn,xn;
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld%lld",&n,&a,&b),lc=a*b/__gcd(a,b),dn=n/a-n/lc,xn=n/b-n/lc;
		printf("%lld\n",(n+n-dn+1)*dn/2-(1+xn)*xn/2);
	}
} 
```

---

