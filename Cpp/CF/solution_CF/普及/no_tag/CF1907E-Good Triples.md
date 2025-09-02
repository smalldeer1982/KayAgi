# Good Triples

## 题目描述

Given a non-negative integer number $ n $ ( $ n \ge 0 $ ). Let's say a triple of non-negative integers $ (a, b, c) $ is good if $ a + b + c = n $ , and $ digsum(a) + digsum(b) + digsum(c) = digsum(n) $ , where $ digsum(x) $ is the sum of digits of number $ x $ .

For example, if $ n = 26 $ , then the pair $ (4, 12, 10) $ is good, because $ 4 + 12 + 10 = 26 $ , and $ (4) + (1 + 2) + (1 + 0) = (2 + 6) $ .

Your task is to find the number of good triples for the given number $ n $ . The order of the numbers in a triple matters. For example, the triples $ (4, 12, 10) $ and $ (10, 12, 4) $ are two different triples.

## 说明/提示

In the first example, the good triples are $ (0, 0, 11) $ , $ (0, 1, 10) $ , $ (0, 10, 1) $ , $ (0, 11, 0) $ , $ (1, 0, 10) $ , $ (1, 10, 0) $ , $ (10, 0, 1) $ , $ (10, 1, 0) $ , $ (11, 0, 0) $ .

In the second example, there is only one good triple $ (0, 0, 0) $ .

## 样例 #1

### 输入

```
12
11
0
1
2
3
4
5
3141
999
2718
9999999
10000000```

### 输出

```
9
1
3
6
10
15
21
1350
166375
29160
1522435234375
3```

# 题解

## 作者：yhx0322 (赞：4)

## Description
给定一个整数 $n$，我们称三元组 $(a,b,c)$ 是“好的”，仅当 $a+b+c=n$ 并且 $digsum(a)+digsum(b)+digsum(c)=digsum(n)$。这里的 $digsum(x)$ 指的是 $x$ 各个数位之和。

现在求不同三元组的数量。

## Solution
首先发现一个结论：如果这个三元组“好的”，只能是没有进位，必然不可能达成条件。

例如，$a=2,b=7,c=4$。他们的总和为 $2+7+4=13$。而 $13$ 各个位数字之和为 $1+3=4$。

**所以，出现进位的情况时，一定不能满足题目要求。**

根据乘法原理，我们可以分别计算每一个数字的答案，最后相乘，也是最终的结果。这样我们就可以利用短除法拆位，便可以计算答案。

**注意：本题需要开 `long long`。**

## Code
```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

int T, n;

inline void solve() {
    int ans = 1;
    cin >> n;
    while (n) {
        int d = n % 10;
        n /= 10;
        ans *= (d + 1) * (d + 2) >> 1LL;
    }
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> T;
    while (T--) solve();
    return 0;
}

```

---

## 作者：Sammy_prime (赞：2)

[CF1907E](https://www.luogu.com.cn/problem/CF1907E)

# 思路

根据题目的描述，我们得知本题目中描述的公式不能有进位，如果有进位，那么原来是 $10$ 现在就是 $1$，这个能满足条件。我们可以使用数学上的一种方法，乘法原理。计算每一位，相乘即可。现在知道怎么算了，那每一位怎么办呢？
这里需要用到组合插空法。这样求解就行了。
注意一定要开 `long long`。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//一定要开long long
int t; ll n;
int main(){
    scanf("%d",&t); 
    while(t--){
        scanf("%lld",&n);
        ll ans=1; 
        while(n!=0){ 
            ll m=n%10;
            ans*=(m+1)*(m+2)>>1ll;
            n/=10;
        }
        printf("%lld\n",ans); 
    } 
    return 0 ; 
}
```


---

## 作者：_txb_ (赞：1)

### 题目：[CF1907E Good Triples](https://www.luogu.com.cn/problem/CF1907E)

## 思路
如果是一个好的三元组，那么一定不会进位，因为当进位时，所有数位和会减少 $9$，只有不进位才能满足条件，我们需要把数的每一位拆开，算出一个数，最后再全部乘起来，就可以算出答案。

贴代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,x[10],n;
int main(){
	for(int i=0;i<=9;i++)
		for(int j=0;j<=9;j++)
			for(int k=0;k<=9;k++)
				if(i+j+k<10) x[i+j+k]++;//存储数 
	cin>>t;//多组数据 
	while(t--)
	{
		cin>>n;
		long long sum=1;//十年oi一场空，不开longlong见祖宗 
		while(n)
		{
			sum*=x[n%10];//求出数 
			n/=10;
		}
		cout<<sum<<endl;//多组数据必要输出换行 
	}
	return 0;
}
```


---

## 作者：紊莫 (赞：1)

感觉我的做题历程有点奇葩，记录一下。

首先我打了个表，发现当 $n$ 为 $1,10,100,\dots$ 时的答案是一样的，然后在 vscode 中发现了 $83$ 和 $38$ 对应的答案也是一样的。哎，这是不是说明了对于数字情况一样的 $n$，答案也是一样的呢？  

我很快验证了 $n=99$ 的情况，答案就是九的情况的平方！是不是意味着我们可以逐位计算呢？于是我很快过了这题。  

```cpp
int n,m,ans,D[]={1,3,6,10,15,21,28,36,45,55};
void solve(){
	ans = 1;n=rd();
	while(n){
		ans = ans*D[n%10];
		n/=10;
	}
	cout<<ans<<endl;	
}
```

现在让我们考虑一下这个东西的本质到底是什么，既然我们可以一位位分开计算，也就是说不会发生进位影响别的位置。那为什么不会进位呢？考虑题中所给的式子，假设发生了至少一次进位，那么就一定有两个和大于 $10$ 的数变成了 $1$。显然最后的数位和会变小，故假设不成立。

注：为啥要用 vscode？因为其自带将相同的字符串标记出来的功能，方便比较。

---

## 作者：kczw (赞：1)

# 题意
令函数 $f(a)$ 的值是 $a$ 十进制下每一位数的和。

有 $t$ 组数据，每组数据给定一个 $n$，问满足 $a+b+c=n$ 并且 $f(a)+f(b)+f(c)=f(n)$ 的三元组个数有多少。
# 思路
首先我们知道如果 $a+b+c$ 的过程中没有进位是一定满足的，但是如果进位又该如何呢。

单看进位的那一位，我们发现，任意两个十以内的数 $x,y$ 相加进位，$10\le x+y$，但是相加过后除了进了的 $1$，剩下的肯定小于 $9$，因为最大值 $(9+9)\mod10=8$，所以 $f(x)+f(y)>f(x+y)$，最后可以知道，进位的话绝对无法保证 $a+b+c=n$ 并且 $f(a)+f(b)+f(c)=f(n)$。

然后就好解决了,只需要算出将一个十以内的数，分成三份（这里分成的三份，是把 $n$ 的某一位拆成三份对应到 $a,b,c$ 同一位,这样保证不会进位）有多少种方案，然后对于 $n$ 的十进制下每一位的分配方案数相乘，即可得出方案总数。

关于怎么求一个数分成三份的方案，没能力或者懒得可以打表，有能力的可以自己用数论排列组合的知识算。
# 实现
```cpp
#include<iostream>
#define int long long
using namespace std;
int t,n,f[10]={1,3,6,10,15,21,28,36,45,55};
signed main(){
	scanf("%lld",&t);
	while(t--){
		int ans=1;
		scanf("%lld",&n);
		while(n){
			ans*=f[n%10];
			n/=10;
		}printf("%lld\n",ans);
	}return 0; 
}
```

---

## 作者：WAis_WonderfulAnswer (赞：1)

## 题目大意

你有一个整数 $n$，求出三个整数 $a,b,c$，满足 $a + b = c$，并且 $d(a) + d(b) + d(c) = d(n)$ 的组数。其中 $d(x)$ 表示 $x$ 的各位数位和。

## 思路

**结论：$a,b,c$ 相加时不能出现进位，否则一定不满足要求。**

简单证明：

因为如果 $a,b,c$ 相加时出现了进位，那么 $d(n)$ 一定会减 $9$，然而 $d(a) + d(b) + d(c)$ 是保持不变的，所以他们两个肯定不相等。

所以做法就出来了：拆掉 $n$ 的每一位，对于每一位利用乘法原理求出对于这一位的方案组数，最后相乘就是答案。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int _;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>_;
	while (_--)
	{
		int n,res=1;
		cin>>n;
		while (n>0) //拆位
		{
			int tmp=n%10;
			res*=(tmp+1)*(tmp+2)>>1LL;//乘法原理
			n/=10;
		}
		cout<<res<<'\n';
	}
	return 0;
}
```

---

## 作者：jr_inf (赞：1)

题意：求出 $a+b+c=n$ 且 $d(a)+d(b)+d(c)=d(n)$ 的三元组 $(a,b,c)$ 的个数。其中 $d(x)$ 等于 $x$ 的各位数位之和。

根据直觉和样例解释可以知道，如果 $a+b+c$ 没有发生进位，那么三元组 $(a,b,c)$ 一定合法。这里就不展开解释了。

然后考虑 $a+b+c$ 发生进位时 $(a,b,c)$ 是否有可能合法。如果有进位的情况，那么此时 $d(a)+d(b)+d(c)>d(a+b+c)$（这里用 $a+b+c$ 比 $n$ 要更加直观）。
而在上一种情况中 $d(a')+d(b')+d(c')=d(a'+b'+c')$，所以当前情况一定不合法。

综上，$(a,b,c)$ 合法当且仅当 $a+b+c=n$ 且 $a+b+c$ 没有进位，于是可以对于每一数位分别求解。设当前数位的值位 $x$，那么此位的贡献就是 $C_{x+2}^{2}=\frac{(x+2)(x+1)}{2}$，相当于把当前位的 $x$ 分给 $a,b,c$ 三个数且可以分到 $0$ 的方案数。

每位贡献的乘积就是答案，时间复杂度 $O(t \log n)$。

---

## 作者：Confringo (赞：1)

### 题意简述

给定 $n$，求 $a+b+c=n$ 且 $f(a)+f(b)+f(c)=f(n)$ 的三元组 $(a,b,c)$ 组数。$f(x)$ 表示 $x$ 的各数位之和。

### 思路

首先考虑没有进位的情况。考虑 $a,b,c$ 的对应位之和都会等于 $n$ 的对应位，这是显然的，因此满足条件。

再考虑有进位的情况，每一次进位都会让 $n$ 的数位和减少 $9$，但是左侧 $a+b+c$ 的数位总和不会减少，所以进位情况一定不满足条件。

所以我们只需要统计没有进位的情况即可。

既然每一位是相互独立的，用乘法原理把每一位不进位分拆成 $3$ 个数的方案数乘起来即可。这可以 $O(\omega^3)$ 处理，其中 $\omega$ 为数位集大小等于 $10$，处理的复杂度是 $O(T\log n)$，总复杂度为 $O(\omega^3+T\log n)$。

### 代码

去除了前面的头，记得开 long long。


```cpp
#include<bits/stdc++.h>
using namespace std;
int T,cnt[10],n;
int main(){
	for (int i=0;i<=9;i++){
		for (int j=0;j<=9;j++){
			for (int k=0;k<=9;k++){
				if (i+j+k<10){
					cnt[i+j+k]++;
				}
			}
		}
	}
	read(T);
	while (T--){
		read(n);
		long long ans=1;
		while (n){
			ans*=cnt[n%10];
			n/=10;
		}
		writeln(ans);
	}
	return 0;
}
```

---

## 作者：Luxingguang (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1907E)

## 一、思路分析
------------
只有三个数的数字和不进位，才能让等式成立。因此，可以用乘法原理，先求出 $0$ 到 $9$ 的可能数，再将每一位的可能数乘起来，便是答案。 

## 二、构造代码
------------
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n;
signed main(){
	scanf("%lld",&t);
	int a[10]={1,3,6,10,15,21,28,36,45,55};
	while(t--){
		scanf("%lld",&n);
		int ans=1;
		while(n){
			ans=ans*a[n%10];
			n/=10;
		}printf("%lld\n",ans);
	}
	return 0;
}



```

---

## 作者：zym20249_ (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1907E)

## 题意
给定一个非负整数 $n(0\le n)$。假设一个非负整数的三元组 $(a,b,c)$ 是好的，如果 $a+b+c=n$，且 $digsum(a)+digsum(b)+digsum(c)=digsum(n)$，其中 $digsum(x)$ 是数字 $x$ 的各位数字之和。

你的任务是找到给定数字 n 的好三元组的数量。三元组是有序的，例如三元组 $(4,12,10)$ 和 $(10,12,4)$ 是不同的三元组。

## 思路
好的三元组，有一个特性就是一定不能进位，进位的话数字之和会有变化。所以我们就可以把数的每一位都分开来计算拆开，最后再全部乘起来，最后的结果就是答案，注意这题需要开到 `long long`。

## code
```cpp
#include<bits/stdc++.h>
#define ll long long//十年OI一场空，不开long long见祖宗
using namespace std;
ll n,t;
int main()
{
    scanf("%lld",&t); 
    while(t--)//和for一样的用处，循环t次
    {
        scanf("%lld",&n);
        ll ans=1; //注意这里要每次赋值为一
        while(n!=0)
        { 
            ll m=n%10;
            ans*=(m+1)*(m+2)>>1ll;
            n/=10;
        }
        printf("%lld\n",ans); 
    } 
    return 0; 
}
```

---

## 作者：_segmenttree (赞：0)

容易发现，$digsum(a+b+c)\leq digsum(a)+digsum(b)+digsum(c)$，可以发现当 $a+b+c$ 中没有进位时取等。这样我们就可以把每一位的数分别计算方案数再乘起来。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int x[10],n,ans;
signed main() {
    int t;
    for(int i=0;i<10;i++)
       for(int j=0;j<10;j++)
           for(int k=0;k<10;k++)
               if(i+j+k<10) x[i+j+k]++;
    cin>>t;
    while(t--) {
        scanf("%lld",&n);
        ans=1;
        while(n) {
            ans=ans*x[n%10];
            n/=10;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：FiraCode (赞：0)

## 思路：

我们考虑一个性质：当他们出现进位时就一定不可以。

因为当出现进位，那么他们的和对下一位的贡献要比进位增加的贡献大，所以最后他们每个数位的和一定大于 $n$ 数位的和。

那么实际上每一位是独立的，考虑直接预处理出当数位和为 $k(0\le k\le9)$ 时有序三元组的方案数。

最后每一位乘起来即可。

## Code

```cpp
#include <bits/stdc++.h>

using namespace std;

int T;
int n;
int sum = 9;
array<int, 3> a;
int res = 0;
int f[10];

int main() {
	scanf("%d", &T);
	for (int i = 0; i <= 9; ++i) {
		for (int j = 0; j <= 9; ++j)
			for (int k = 0; k <= 9; ++k)
				for (int p = 0; p <= 9; ++p) {
					if (j + k + p == i) ++f[i];
				}
	}
	while (T--) {
		scanf("%d", &n);
		vector<int> a;
		while (n) {
			a.push_back(n % 10);
			n /= 10;
		}
		long long ans = 1;
		for (int i = 0; i < (int)a.size(); ++i) ans = 1ll * ans * f[a[i]];
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：Dawn_cx (赞：0)

题意：给你 $n$ 问你有多少组 $(a,b,c)$ 使得 $a+b+c=n$，并且 $a,b,c$ 的每一位数的和等于 $n$ 的位数的和。

很显然，因为等号两侧的数字和相等，所以每一位不能有进位，因此对每一位都是独立考虑，各个位之间的方案数满足乘法原理。

对于每一位的答案，赛时是通过观察样例前几个得到的答案。其实推也很好推，不想推一个一个写也写出来了，对于这一位为 $i$，答案就是 $0+1+\dots+i$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5+10;
const ll mod = 998244353;
inline void read(int &x){
    int s=0,w=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){s=(s<<3)+(s<<1)+(ch&15);ch=getchar();}
    x=s*w;
}
int n,t,a[]={1,3,6,10,15,21,28,36,45,55};
void solve(){
    read(n);
    ll s=1;
    while(n){
        s*=1ll*a[n%10];
        n/=10;
    }
    printf("%lld\n",s);
}
int main(){
    read(t);
    while(t--)solve();
    return 0;
}
```


---

## 作者：abensyl (赞：0)

原题：[CF1907E Good Triples](https://www.luogu.com.cn/problem/CF1907E)。

## 思路

假设 $\operatorname{digsum}(x)$ 表示十进制意义下 $x$ 各个数位上数字的和，那么经过简单推理，即可得到以下不等式：

若 $y+z=x$，则 $\operatorname{digsum}(x)\leq \operatorname{digsum}(y)+\operatorname{digsum}(z)$，当且仅当 $y+z$ 在十进制下没有进位时，等号成立。

那么，在本题中，将一个整数 $x$ 拆成三个数字，也是如此。

因为不进位，所以各个数位之间相互独立，可以分别考虑，我们只要考虑每个一位数字拆分成 $3$ 个一位数字的情况数量即可，可以考虑预处理，而我直接打表解决，打出来的表在程序中就是 cf 数组。

## 代码

```
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
const int mod = 1e9 + 7;
int cf[]={1,3,6,10,15,21,28,36,45,55};
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),
	cout.tie(nullptr);
	int T=0;
	cin>>T;
	while(T--) {
		int x;
		long long res=1;
		cin>>x;
		while(x) {
			res*=1ll*cf[x%10];
			x/=10;
		} cout<<res<<'\n';
	}
	return 0;
}
```
[我的 AC 记录](https://codeforces.com/contest/1907/submission/235898011)。

---

## 作者：Special_Tony (赞：0)

# 思路
本体核心：不能进位。

那就好做了，把每一位拆分分别计算，然后用组合数学中的插板法就行辣。

插板法不懂可以 bdfs。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int t, n;
ll sum;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n;
		sum = 1;
		while (n) {
			sum *= (n % 10 + 2) * (n % 10 + 1) / 2;
			n /= 10;
		}
		cout << sum << '\n';
	}
	return 0;
}
```

---

