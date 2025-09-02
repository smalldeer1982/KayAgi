# [ABC343C] 343

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc343/tasks/abc343_c

正整数 $ N $ が与えられます。

$ N $ 以下の正整数であって回文立方数であるものの最大値を求めてください。

ただし、正整数 $ K $ は以下の $ 2 $ つの条件を満たすとき、またそのときに限り回文立方数であると定義します。

- ある正整数 $ x $ が存在し、$ x^3\ =\ K $ を満たす。
- $ K $ を先頭に $ 0 $ をつけずに $ 10 $ 進表記した文字列が回文となる。より厳密には、$ 0 $ 以上 $ 9 $ 以下の整数 $ A_0,\ A_1,\ \ldots,\ A_{L-2} $ および $ 1 $ 以上 $ 9 $ 以下の整数 $ A_{L-1} $ を用いて $ K\ =\ \sum_{i\ =\ 0}^{L-1}\ A_i10^i $ と表記したときに $ i\ =\ 0,\ 1,\ \ldots,\ L-1 $ に対して $ A_i\ =\ A_{L-1-i} $ を満たす。

## 说明/提示

### 制約

- $ N $ は $ 10^{18} $ 以下の正整数

### Sample Explanation 1

$ 343 $ は回文立方数であり、$ 344,\ 345 $ は回文立方数ではありません。したがって、$ 343 $ が答えとなります。

## 样例 #1

### 输入

```
345```

### 输出

```
343```

## 样例 #2

### 输入

```
6```

### 输出

```
1```

## 样例 #3

### 输入

```
123456789012345```

### 输出

```
1334996994331```

# 题解

## 作者：Little_x_starTYJ (赞：8)

### 解题思路
这道题目既然让我们求不超过 $n$ 的最大的回文完全立方数，那我们就可以先用 `cbrt` 函数求出 $n$ 的立方根，然后再挨个判断他们的立方数是否为回文数即可。

CODE:
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	unsigned long long n;
	cin >> n;
	for (unsigned long long i = cbrt(n) + 1; ; i--)
	{
    	if (i * i * i > n)
    		continue;
	    string a = to_string(i * i * i);
	    string b = a;
		reverse(a.begin(), a.end());
		if (a == b) {
			cout << i * i * i;
			return 0;
		}
	}
	cout << 1;
	return 0;
}
```

---

## 作者：littlesnake (赞：3)

复杂度只有 $O(N^{\frac{1}{3}})$，立方体数小于或等于 $N$。因此，我们可以对所有的立方数进行运算，并检查其十进制表示是否为回文，以解决此问题。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool check(ll n) {
    string s = to_string(n);
    string t = s;
    reverse(t.begin(), t.end());
    return s == t;
}

int main() {
    ll n;
    cin >> n;
    ll ans = 0;
    for (ll i = 1; i * i * i <= n; i++) if (check(i * i * i)) ans = i * i * i;
    cout << ans << '\n';
}

```

---

## 作者：XXh0919 (赞：3)

### 题意

给定一个 $N$，找出不大于 $N$ 的最大的回文立方数。

### 解法

这一题很简单。既然是回文立方数，那我们就把它分成 “回文”和“立方数”两个词。“回文”很简单，就是把这个数翻转一遍，然后与原数比较，相等即为回文。最主要的就是“立方数”。因为 $N\leq10^{18}$，所以从 $1$ 直接循环肯定会爆，所以我们就要把这个 $10^{18}$ 给压缩一下：因为是立方数，所以我们就用它的逆运算三次根把 $10^{18}$ 变成 $10^6$，这样循环就不会爆了。然后我们再在循环里面进行回文判断，找到一个就对 $ans$ 取最大值就行了。

### AC Code

```cpp
#pragma GCC optimize(2)//手动 O2
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n,ans;


signed main() {
	scanf("%lld",&n);
	for(int i=1; i<=1000000; ++i) {
		int x=i*i*i;//因为取了三次根，所以循环里要把它转回来
		string s=to_string(x);//将整数转成字符串
		string ss=s;
		reverse(ss.begin(),ss.end());//翻转
		if(s==ss&&x<=n)ans=max(ans,x);//判回文
	}
	printf("%lld\n",ans);
	return 0;
}
```
[AC记录](https://atcoder.jp/contests/abc343/submissions/50844108)

---

## 作者：include13_fAKe (赞：2)

## 前言
开学第一场 ABC。
## 题意
给定正整数 $N$，找出不大于 $N$ 的**最大回文立方数**。

$1\le N\le 10^{18}$。
## 思路
**从大到小**枚举 $10^6$ 至 $1$ 中所有数的立方。

遇到第一个**小于等于** $N$，且回文的立方数就输出即可。然后结束程序运行。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

long long n;
int ptr;
int c[25];
signed main(){
	cin>>n;
	for(long long a=1e6;a>=1;a--){
		long long b=1ll*a*a*a;
		long long d=b;
		if(b<=n){
			ptr=0;
			while(b){
				c[++ptr]=b%10;
				b/=10;
			}
			bool flag=true;
			for(int i=1;i<=ptr;i++){
				if(c[i]!=c[ptr-i+1])	flag=false;
			}
			if(flag==true){
				cout<<d<<endl;
				return 0;
			}
		}
	}
}
```

---

## 作者：littlebug (赞：2)

题目要求找到在 $[0,n]$ 内最大的 $x$ 使得 $x$ 是一个**回文立方数**，即 $x$ 既是回文数又是立方数。再看数据范围 $x\le10^{18}$，而 $\sqrt[3]{10^{18}}=10^6$，所以可以枚举所有立方数，判断每个数是否为回文数就好了，不会超时。

关于判断回文数这里就不再赘述了，如果你不会的话可以看这道题：[link](/problem/B2136)。

**code**：
```cpp
#include<iostream>
#include<cstdio>
#define ll long long
#define il inline
using namespace std;
ll n;
il bool check(ll x) //判断回文数 
{
	ll a[50]={};
	int ai=0;
	while(x) a[++ai]=x%10,x/=10;
	for(int i=1,j=ai;i<=j;++i,--j) //双指针判回文 
		if(a[i]!=a[j])
			return 0;
	return 1;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n;
	ll x=1000000+5; //从1e6开始向下枚举 
	while(x>0)
	{
		--x;
		if(x*x*x>n) //如果x^3>n就跳过 
			continue;
		if(check(x*x*x)) //判断回文 
		{
			cout<<x*x*x;
			return 0; //找到最大值就退出 
		}
	}
	return 0;
}

```

**总结**：要正确理解了题意再做题，~~不要像我似的以为是 $k$ 要回文~~。

---

## 作者：OIerWu_829 (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/AT_abc343_c)

## 思路

感觉没啥可说的，直接枚举每个 $\le n$ 的 $i$，判断 $i^3$ 是否为回文，如果是就赋值给 $ans$。

```cpp
#include <iostream>
#define int long long
using namespace std;
inline bool check(int x) {
    string s = to_string(x); // 可以转化为字符串
    for (int i = 0; i < s.size(); i++)
        if (s[i] != s[s.size() - i - 1]) return false;
    return true;
}
signed main()
{
    int n;
    cin >> n;
    int ans = 0;
    for (int i = 1; i * i * i <= n; i++)
        if (check(i * i * i)) ans = i * i * i;
    cout << ans << endl;
    return 0;
}
```

---

## 作者：Guizy (赞：1)

给定一个 $n$，求小于 $n$ 的最大回文立方数（$n\le 10^{18}$）。

考虑到 $n$ 比较大，我们不能判断每一个数是否回文或者是否是立方数。设答案为 $ans$，我们考虑枚举 $\sqrt[3]{ans}$，很小，只有 $10^6$ 左右。

然后就可以暴力了！

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n,maxn,temp,ans,cnt,num[20];

bool check(int x){//判断是否回文
	memset(num,0,sizeof num),cnt=0;
	while(x) num[++cnt]=x%10,x/=10;
	for(int i=1;i<=cnt/2;i++)
		if(num[i]!=num[cnt-i+1]) return 0;
	return 1;
} 

signed main(){
	
	scanf("%lld",&n);
	for(int i=1;i*i*i<=n;i++){
		temp=i*i*i;//算出原数
		if(check(temp))	ans=temp;
	} 
	printf("%lld",ans);
	
	return 0;
}
```

---

## 作者：OIer_Tan (赞：1)

## 题意

给你一个正整数 $N$，让你求 **不大于** $N$ 的最大回文立方数。

这里，立方数定义为能使一个正整数 $x$ 在 $x^3=N$ 时成立的数。

## 思路

一个朴素的想法是从 $N$ 开始向 $1$ 枚举，直到找到这种数为止。但很显然，这样的时间复杂度为 $O(N)$，在 $1\le N\le10^{18}$ 的情况下是会超时的。

考虑另外一种做法。我们可以枚举 $x$，使 $x^3\le N$ 并判断 $x$ 是否回文即可。这样的时间复杂度为 $O(\sqrt[3]{N}\times \log_{10}{N})$ 的，可以通过。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std ;

typedef long long ll ;
typedef unsigned long long ull ;
typedef long double ld ;

string maxn ;

int main ()
{
	// freopen ( ".in" , "r" , stdin ) ;
	// freopen ( ".out" , "w" , stdout ) ;
	ios::sync_with_stdio ( 0 ) ;
	cin.tie ( 0 ) ;
	cout.tie ( 0 ) ;
	ll n ;
	cin >> n ;
	ll i = 1 ;
	while ( i * i * i <= n )
	{
		string temp = to_string ( i * i * i ) , a = temp ;
		reverse ( temp.begin () , temp.end () ) ;
		if ( a == temp )
		{
			maxn = a ;
		}
		i ++ ;
	}
	cout << maxn << endl ;
	return 0 ;
}
```

---

## 作者：Albatross_LC (赞：1)

### 思路：

二分和回文数判断。

先用二分求出 $\sqrt[3]{n}$，再从 $\sqrt[3]{n}$ 依次枚举到 $1$，判断回文数，时间复杂度 $O(\log_{2}{n} + \sqrt[3]{n})$。

由于 $n \le 10 ^ {18}$，所以 $mid$ 有可能爆 `long long`，所以 $r$ 最开始可以设为 $\sqrt[2]{n}$。

### Code:

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n;
signed main() {
	cin >> n;
	int l = 1, r = sqrt(n);
	while (l < r) {
		int mid = ((__int128)l + r + 1) >> 1;
		if ((__int128)mid * mid * mid <= n) l = mid;
		else r = mid - 1;
	}
	for (int i = l; i >= 1; i -- ) {
		__int128 op = (__int128)i * i * i;
		if (op > n) continue;
		int p = i * i * i;
		string s;
		s += '0'; int l = 0;
		while (p) s += p % 10 + '0', p /= 10, l ++ ;
		bool flag = 1;
		for (int j = 1; j <= (l >> 1); j ++ )
			if (s[j] != s[l - j + 1]) {
				flag = 0;
				break;
			}
		if (flag) return cout << i * i * i, 0;
	}
}
```

---

## 作者：int_stl (赞：1)

这道题让我们去求不大于正整数 $N$ 的最大的回文立方数。

考虑用暴力模拟，从 $\sqrt[3]{10^{18}}$ 倒序遍历到 $1$，每次用函数判断这个数的立方是否为回文数，如果符合条件，则输出这个回文数：

```cpp
#include <iostream>
#include <cmath>
#define int long long
using namespace std;
int check(int x) {
	static int tmp[21];
	int len = 0;
	while (x) tmp[++len] = x % 10, x /= 10;
	for (int l = 1, r = len; l <= r; l++, r--) {
		if (tmp[l] != tmp[r]) return 0;
	}
	return 1;
}
signed main() {
	int maxn = 1000000000000000000;
	for (int i = cbrt(maxn); i >= 1; i--) {
		int ans = i * i * i;
		if (check(ans)) {
			cout << ans << endl;
		}
	}
}
```

输出：
```
1331399339931331
1033394994933301
1000030000300001
1334996994331
1030607060301
1000300030001
10662526601
1003003001
1367631
1030301
1331
343
8
1
```

可以发现，从 $1$ 到 $10^{18}$ 之间只有 $14$ 个回文立方数，打表即可。

```cpp
#include <iostream>
#include <cmath>
#include <string>
using namespace std;
long long ans[30] = { 1331399339931331,1033394994933301,1000030000300001,1334996994331,1030607060301,1000300030001,10662526601,1003003001,1367631,1030301,1331,343,8,1 };
int main() {
    long long N;
    cin >> N;
    for (int i = 0; i <= 13; i++) {
        if (ans[i] <= N) {
            cout << ans[i];
            return 0;
        }
    }
}
```

---

## 作者：Programming_Konjac (赞：1)

# 思路
~~赛时一遍过。~~

打暴力，枚举到 $\sqrt[3]n$，看数据范围，显然 $\sqrt[3]{ 10^{18}}$ 不会超过 $10^6$，所以暴力枚举即可。

定义一个最大值变量 $maxx$ 赋值为 $1$，然后变量 $i$ 从 $1$ 枚举到 $\sqrt[3]n$，对于每个 $i$，用一个变量 $k$ 进行赋值 $i^3$，因为是立方数，然后用一个变量 $j$ 存储倒序之后的数字，使用数位分离再合并法，数位分离再合并代码：

```cpp
while(k){
    j=j*10+k%10;
    k/=10;
}
```

如果 $j$ 等于 $i^3$，那么这个立方数合法，把 $i^3$ 与 $maxx$ 求最大值。

最后输出 $maxx$。

注意：要开 `long long`！
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
	ll n,maxx=1;
	cin>>n;
	for(ll i=1; i*i*i<=n; i++){
		ll j=0,k=i*i*i;
		while(k){
			j=j*10+k%10;
			k/=10;
		}
		if(j==i*i*i){
			maxx=max(maxx,i*i*i);
		}
	}
	cout<<maxx;
	return 0;
}
```

---

## 作者：aaron0919 (赞：0)

# [AT_abc343_c の题解](https://www.luogu.com.cn/problem/AT_abc343_c)

### 题目大意

求出不大于 $n$ 的最大回文立方数。

### 理性分析

$n \le 10^{18}$，而 $\sqrt[3]{n} \le 10^6$，因此，我们枚举立方根就可以了。

### 代码实现

可以用自带函数实现数字转字符串和反转字符串。

### code

[AC 记录](https://atcoder.jp/contests/abc343/submissions/50901539)

```cpp
#include <bits/stdc++.h>
using namespace std;

long long n, ans;
int main()
{
	cin >> n;
	for (long long i = 1; i * i * i <= n; i++)
	{
		string s = to_string(i * i * i), t = s;
		reverse(s.begin(), s.end());
		if (s == t)
		{
			ans = i * i * i;
		}
	}
	cout << ans;
}
```

---

## 作者：code_hyx (赞：0)

暴力题，唯一注意的点就是当枚举的 $k^3>n$ 时候就应该停了，以免超时。  
对于回文数的判断，可以采用取模截位法，然后首尾一一配对比对就行了。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,maxx=0;
bool check(long long x)
{
	char ch[50]={0},cnt=0;
	while(x)
	{
		ch[cnt++]=x%10;
		x/=10;
	}
	for(int i=0;i<cnt;i++)
	{
		if(ch[i]!=ch[cnt-1-i])return false;
	}
	return true;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
    cin>>n;
    for(long long i=1;i*i*i<=n;i++)
	{
		if(check(i*i*i))
		{
			maxx=i*i*i;
		}
	}
	cout<<maxx;
    return 0;
}
```

---

## 作者：无名之雾 (赞：0)

输入一个 $n$ 请你找出一个回文立方数 $x$ 使得 $x \le n$。

只需要枚举立方数判断即可。

注意不要使用 `cbrt` 使用精度更高的 `cbrtl`。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int unsigned long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
bool ipe(int num) {
    int NUM=num;
    int RNUM=0;
    while(num>0){
        int digit=num%10;
        RNUM=RNUM*10+digit;
        num=num/10;
    }
    return NUM==RNUM;
}
signed main(){
	int n=read();
	int k=cbrtl(n);
	while(1){
		int q=k*k*k;
		if(ipe(q)){
			cout<<q;
			return 0;
		}
		else k--;
	}
	return 0; 
}

```

---

## 作者：vectorxyz (赞：0)

### 题意描述
题目说了那么长一堆，简化下来就两个条件：是一个立方数和是一个回文数。

每次我们只要枚举立方数，然后判断是否是回文数，如果是就存入 $ans$，如果当前枚举到的数大于 $n$，就输出当前最大的答案。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int ans;
signed main()
{
    int n;
    cin >> n;
    for(int x = 1;;x ++ ){
        if(x * x * x > n) {
            cout << ans << endl;
            return 0;
        }
        int k = x * x * x;
        string s = to_string(k);
        string s1 = s;
        reverse(s1.begin(),s1.end());
        if(s == s1) ans = k;
    }
    return 0;
}
```

赛时为了速度更快，用的打表，虽然不是正解，但是也贴这里吧。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int a[] = {1,8,343,1331,1030301,1367631,1003003001,10662526601,1000300030001,1030607060301,1334996994331,1000030000300001,1033394994933301,1331399339931331};
signed main()
{
    int n;
    cin >> n;
    for(int i = 0;i < 14;i ++ ) {
        if(a[i] > n && i != 0){
            cout << a[i - 1] << endl;
            return 0;
        }
    }
    cout << a[13];
    return 0;
}
```

---

## 作者：qinshi0308 (赞：0)

## 思路：
这个题的 $n$ 大的恐怖，但是需要注意这个数是回文数的同时还要是完全立方数，所以枚举量从 $10^{18}$ 骤减到 $10^{6}$，可以直接暴力枚举。

## 代码：
```cpp
# include <bits/stdc++.h>
using namespace std;
string work(long long x){//一个把整数转换成字符串的函数，做法类似于快写
    if(x==0){
        return "";
    }
    string s;
    s+=x%10+'0';
    return work(x/10)+s;
}
int main(){
    long long n;
    cin>>n;
    long long ans=0;
    for(long long i=1;i*i*i<=n;i++){//
        long long x=i*i*i;
        string s=work(x);//吧数转换成字符串
        string s1=s;
        reverse(s1.begin(),s1.end());//翻转字符串
        if(s==s1){//比较翻转前后的字符串，判断是否为回文数
            ans=x;
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：2021zjhs005 (赞：0)

直接枚举即可。

观察到 $1\le n\le 10^{18}$，所以可以枚举到 $10^6$ 结束（因为 $10^6\times 10^6\times 10^6 \le 10^{18}$ 且最大。）

因此，对 $1\le i\le 10^6$ 的每一个数进行回文判断，如果是回文数就打擂台。

注意：当 $i^3 > n$ 时，记得 `break`。

[Code](https://atcoder.jp/contests/abc343/submissions/50952735)。

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc343_c)

## 思路

从 $1$ 到 $\sqrt[3]{N}$ 循环，每次查询当前这个数的三次方是否为回文数，如果是就记录最大值。最后输出最大值即可。

判断回文数可以使用 ``to_string()`` 函数，转化为 string 类型后循环比较。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll ans;
inline bool hw(ll x){
    string s=to_string(x);
    int len=s.size();
    s=" "+s;
    for(int i=1;i<=len;++i){
        if(s[i]!=s[len-i+1])return 0;//两边不一样就不是回文。
    }
    return 1;
}
int main(){
    ll n;
    cin>>n;
    for(ll i=1;i*i*i<=n;++i){
        if(hw(i*i*i)){
            ans=max(ans,i*i*i);
        }
    }    
    cout<<ans;
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/149272993)

---

## 作者：Spark_King (赞：0)

# ABC343C题解
[题目传送门](https://www.luogu.com.cn/problem/AT_abc343_c)

## 题意分析
题目要求我们先输入一个整数 $n$ 然后找出最大的小于等于 $n$ 的一个**回文的完全立方数**。

比如：
```
输入样例：345
输出样例：343
```
这里 $343=7^3$ 既满足了回文，又是完全立方数。

这里由于数据范围《并不大》，只有 $10^{18}$ 而已（记得开 long long），所以我们可以直接暴力枚举 $n$ 以下每一个完全立方数。

下面是代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n;
bool check(ll x) {//判断回文
	ll num[20], cnt = 0;
	while (x) {
		num[++cnt] = x % 10;
		x /= 10;
	}
	for (ll i = 1; i <= cnt; i++) {
		if (num[i] != num[cnt - i + 1]) return 0;
	}
	return 1;
}
ll ans;
int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n;
	for (ll i = 1; i * i * i <= n; i++) {//枚举
		if (check(i * i * i)) ans = i * i * i;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：WhxStar2024 (赞：0)

## 本题思路：
这道题其实很简单，我们可以直接枚举一个数字，把他立方后判断他是否是回文字符串，如果是找到最大的一个即可。
## 本题代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[20];
int main()
{
	long long n,ans;
	cin>>n;
	for(long long i=1;i<=1000000;i++){
		if(i*i*i>n) break;
		long long cnt=0,u=i*i*i;
		while(u>0){
			a[++cnt]=u%10;
			u/=10;
		}
		int f=0;
		for(int i=1;i<=cnt;i++){
			if(a[i]!=a[cnt-i+1]) f=1;
		}
		if(f==0) ans=i*i*i;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：coderJerry (赞：0)

~~342 和 343 两场 A 都吃了一发罚时~~。
### 题目描述
找出不超过 $N$ 的最大回文立方数。
### 题目分析
$N$ 最大为 $10^{18}$，于是我们暴力查询 $1-10^6$ 各数的立方是否为回文数即可。判断回文数的话将原数反转再和原数比较即可。
### AC 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
bool ish(int x){
int temp=x,y=0;
    while(temp){//计算原数反转的结果
        y=y*10+temp%10;
    //每往后 1 位，就乘 10 并加上原数对应的那一位
        temp=temp/10;
    }
    return (x==y);
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    int n;
    cin>>n;
    for(int i=1000000;i>=1;i--){
        if(i*i*i<=n&&ish(i*i*i)){
            cout<<i*i*i<<endl;
            break;//找到了最大的就要及时 break
        }  
    }
    return 0;
}
```

---

## 作者：Ivan422 (赞：0)

# AT_abc343_c

题目大意：找到不超过 $N$ 的最大回文立方数。

思路：$\sqrt[3]{N}\leq 10^{6} $ 可以从 $1$ 到 $10^6$ 枚举，每次求出立方并判断是否回文即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=110;
int n,sn,ans,tt;
string st;
bool isa;
signed main(){
    cin>>n;
    for(int i=1;i*i*i<=n;i++){ // 枚举 1 到 开立方n
        tt=i*i*i; // 计算出原数
        st=to_string(tt);sn=st.size(); // 转字符串判断回文
        isa=1;
        for(int i=0;i<sn;i++){if(st[i]!=st[sn-i-1])isa=0;}
        if(isa)ans=max(ans,tt); //找到一个解，取最大
    }
    cout<<ans;
    return 0;
}
```

---

