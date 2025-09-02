# Common Divisors

## 题目描述

你有一个由$n$个整数组成的数组，计算这样的正整数$x$的数量，使数组中的每个数字除以$x$余数都为$0$。 换句话说，您必须找到数组中所有元素的公约数的个数。  
例如，如果数组$a$为$[2,4,6,2,10]$，则$1$和$2$将每个数字除以数组（因此该示例的答案为$2$）。

## 样例 #1

### 输入

```
5
1 2 3 4 5
```

### 输出

```
1
```

## 样例 #2

### 输入

```
6
6 90 12 18 30 18
```

### 输出

```
4
```

# 题解

## 作者：andyli (赞：3)

先求出所有数字的最大公约数$x$，然后通过分解质因数的方法来计算$x$的约数个数。
如何用分解质因数的方法计算某个数的约数个数呢？  
假设我们需要求$216$这个数字的因数个数，分解质因数后得到：  
$$216=2^3*3^3$$  

对于2这个质数有4种选法：$2^0,2^1,2^2,2^3$，3也有4种选法：$3^0,3^1,3^2,3^3$，所以216的因数个数就是$4\times4=16$.  

既然明白了这个道理，就可以轻松编写出程序了，注意使用$long long$。代码如下：  
```cpp
#include <cmath>
#include <cstdio>
#include <numeric>
using namespace std;
const int maxn = 400005;

long long A[maxn];
bool isprime(long long n) // 判断质数
{
    if (n <= 1)
        return false;
    int m = sqrt(n) + 0.5;
    for (int i = 2; i <= m; i++)
        if (n % i == 0)
            return false;
    return true;
}
int main()
{
    int n;
    scanf("%d%lld", &n, &A[1]);
    long long x = A[1];
    for (int i = 2; i <= n; i++)
        scanf("%lld", &A[i]), x = gcd(x, A[i]); // <numeric>头文件中在C++17标准里内置了gcd函数
    long long ans = 1;
    for (long long i = 2; i * i <= x; i++) { // 将x分解质因数并计算ans
        if (isprime(i)) {
            int cnt = 0;
            while (x % i == 0)
                x /= i, cnt++;
            ans *= (cnt + 1);
        }
    }
    printf("%lld\n", x > 1 ? (ans << 1) : ans); // 输出答案
    return 0;
}
```

---

## 作者：July_S (赞：1)

## 大体思路：
① **欧几里得算法**可以来计算两个数的**最大公约数**。

[证明点我](https://zhuanlan.zhihu.com/p/346479426)

普通的欧几里得算法求最大公约数相信很多人已经很熟悉了，于是这里介绍一个**神奇的小函数**，能快速求出参数的最大公约数：

`__gcd(a,b)`;
 
(前为两个下划线) 其用法见下方代码。
②声明一个变量 `res`，并初始化为数组的**第一个元素**。
使用一个循环，从**第二个元素**开始遍历数组，每次将当前结果与**当前元素求最大公约数**，**更新**结果为新的**最大公约数**。
③定义一个变量 `cnt` 来记录公约数的个数。
使用一个循环，从 1 到结果的**平方根**，判断是否是结果的约数，如果是则计数加一。
④ 输出即可。
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int main(){
	//当然也可以直接写一个gcd函数，如下：
//        int gcd(int x,int y){
//		if(y == 0) return x;
//		else return gcd(y,x % y);
//	} 
    int n;
    cin>>n;
    long long a[n];//读入与定义 
	              //注意a[i]最大为1e12，因此这里a[n]要开long long 
    for (int i = 0; i < n; i++){
        cin>>a[i];
    }
    long long res = a[0];
    for (int i = 1; i < n; i++){
        res = __gcd(res, a[i]);//用函数__gcd（a,b）快速求出a,b的最大公约数 
    }                          //注：此函数在头文件<algorithm>里 
    int cnt = 0;
    for (long long i = 1; i * i <= res; i++) { //为了简便，这里只需循环至res的平方根即可 
        if (res % i == 0) {
            cnt++;
            if (i != res / i) {
                cnt++;
            } //符合要求，计数器++ 
        }
    }
    cout<<cnt;//输出 
    return 0;
}
```


---

## 作者：__HHX__ (赞：1)

# 题目大意
给出序列 $a$ 让你求出能成为所有 $a_i$ 的因数 $k$ 的数量。
# 思路
## 做法一（暴力）（TLE）
### 做法思路
最暴力的写法也就是直接从 $1$ 枚举到 $\displaystyle\max_{1 \le i \le n}a_i$ 看是否能成为所有 $a_i$ 的因数。

时间复杂度 $O(vn),v=\displaystyle\max_{1 \le i \le n}a_i$。
### 代码
```cpp
#include<iostream>
using namespace std;

const int MaxN=4e5+3;
long long a[MaxN],Max;
int main(){
	int n;
	long long ans=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		Max=max(Max,a[i]);
	}
	bool f=1;
	for(long long i=1;i<=Max;i++,f=1)
	{
		for(int j=1;j<=n;j++)
		{
			if(a[j]%i)
			{
				f=0;
				break;
			}
		}
		ans+=f;
	}
	cout<<ans;
	return 0;
}
```
## 做法二（做法一+剪枝）（TLE）
### 做法思路
在做法一的基础上我们是否能**缩小判断** $a_i$ **合法的范围**呢？

换句话说怎么知道他的**最大的因数**呢？

不错**最大的因数**就是 $\gcd(a_1 , a_2 , \dots ,a_n)$。

$\gcd$ 的时间复杂的大约等于 $\log_2 v$。

我们成功把 $O(vn)$ 变成了 $O(v+\log_2 v)$。
### 代码
```cpp
#include<iostream>
using namespace std;

const int MaxN=4e5+3;
long long a[MaxN];

long long gcd(long long x,long long y){return x%y?gcd(y,x%y):y;}//辗转相除求最大公约数 

int main(){
	int n;
	long long ans=0,d;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	d=a[1];
	for(int i=2;i<=n;i++)
	{
		d=gcd(a[i],d);
	}
	for(long long i=1;i<=d;i++) 
	{
		if(d%i==0)
		{
			ans++;
		}
	}
	cout<<ans;
	return 0;
}
```
## 做法三（做法二+剪枝）（AC）
### 做法思路
在做法二的基础上我们是否能**缩小枚举因数的范围**呢？

因为我们知道因数是**成对出现**的。

所以我知道了一个因数 $k$ 就知道另一个因数 $v \over k$。

所以说我们**只需枚举到** $O(\sqrt v)$。

**合并做法二**时间复杂度 $O(\sqrt v+\log_2 v)$。
### 代码
```cpp
#include<iostream>
using namespace std;

const int MaxN=4e5+3;
long long a[MaxN];

long long gcd(long long x,long long y){return x%y?gcd(y,x%y):y;}//辗转相除求最大公约数 

int main(){
	int n;
	long long ans=0,d;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	d=a[1];
	for(int i=2;i<=n;i++)
	{
		d=gcd(a[i],d);
	}
	for(long long i=1;i*i<=d;i++)//必须开long long不然会死的很惨的 
	{
		if(a[n]%i==0)
		{
			ans+=i*i==d?1:2;//i*i=n要特判只有一个因数 
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

## 分析

我们知道，若一个整数 $x$，满足：$a_1 \bmod x=0,a_2 \bmod x=0,...,a_n \bmod x=0$，则 $x$ 一定是 $a_1,a_2,...,a_n$ 的公因数。而这道题要我们找出所有满足的 $x$，所以我们可以把 $a_1,a_2,...,a_n$ 的最大公因数求出来，因为一旦有最大公因数 $x_1$，其余的公因数 $x_i$ 也一定是 $x_1$ 的一部分，即：$x_1 \bmod x_i=0$。于是，我们在求出来最大公因数之后，再求其的因数个数即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
const int N=1e6+10;
long long a[N],gcd_all;
long long ans;
signed main()
{
	cin>>n;
	for(long long i=1;i<=n;i++)
		cin>>a[i];
	gcd_all=a[1];
	for(long long i=2;i<=n;i++)
		gcd_all=__gcd(gcd_all,a[i]);
	for(long long i=1;i*i<=gcd_all;i++)
		if(gcd_all%i==0) 
			ans+=2;
	if((long long)(sqrt(gcd_all))*(long long)(sqrt(gcd_all))==gcd_all) ans--;
	return cout<<ans,0;
}
```


---

## 作者：封禁用户 (赞：1)

## 思路
现在我们需要处理两种操作：求最大公约数和计算因数个数。

首先看第 $1$ 种操作，我们只需要用辗转相除法两两求值就行了。

第 $2$ 个操作中，设最大公约数为 $x$，则设 $x=p_1^{a_1} \times p_2^{a_2} \cdots p_k^{a_k}$，则其因数个数为 $\prod_{i=1}^{k} a_i+1$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int gcd(int x,int y){//求最大公约数 
	if(y==0)return x;
	return gcd(y,x%y);
}
bool isprime(int x){
	if(x<2)return false;
	for(int i=2;i*i<=x;i++){
		if(x%i==0)return false;
	}
	return true;
} 
inline int calc(int x){//计算因数个数
	int ans=1;
	for(int i=2;i*i<=x;i++){
		if(isprime(i)){
			int cnt=0;
			while(x%i==0){
				x/=i;
				cnt++;
			}
			ans*=(cnt+1);
		}
	}
	return x>1?(ans<<1):ans;
}
int n,x;
signed main(){
	cin>>n;
	int ans=0;
	while(n--){
		cin>>x;
		ans=gcd(ans,x);
	}
	cout<<calc(ans)<<endl;
	return 0;
}
```


---

## 作者：w1049 (赞：1)

题意就是求一组数的公因子个数

于是先求最大公因数再求最大公因数的因子个数

昨天晚上一直TLE（i\*i变负数），注意小心乘法爆int

于是代码就很简单了
（然而这么简单的题蒟蒻也被TLE困扰了好久）

```
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;
int n, ans;
long long x, s;
int main() {
    scanf("%d%I64d", &n, &s);
    for (int i = 2; i <= n; i++) scanf("%I64d", &x), s = __gcd(x, s);
    //如果写i * i <= n，小心i * i爆int
    int lim = sqrt(s);
    for (int i = 1; i <= lim; i++) if (s % i == 0) ans += 2;
    printf("%d\n", 1ll * lim * lim == s ? --ans : ans);
}
```

---

## 作者：minVan (赞：0)

**解题思路**

先算出所有元素的最大公因数，如果最大公因数 $g$ 为 $1$，即所有元素两两互质，则直接输出 $1$；否则输出 $g$ 的因数个数。

最后注意要开 `long long`。

**求解因数个数代码**

```cpp
for(ll i = 1; i * i <= g; i++) {
	if(g % i == 0) {
		if(i * i == g) {
			ans++;
		} else {
			ans += 2;
		}
	}
}
```

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 4e5 + 5;
int n;
ll a[N], g, ans;
ll gcd(ll a, ll b) {
	if(a % b == 0) {
		return b;
	}
	return gcd(b, a % b);
}
int main() {
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	g = a[1];
	for(int i = 2; i <= n; i++) {
		g = gcd(g, a[i]);
	}
	if(g == 1) {
		cout << 1;
		return 0;
	}
	for(ll i = 1; i * i <= g; i++) {
		if(g % i == 0) {
			if(i * i == g) {
				ans++;
			} else {
				ans += 2;
			}
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：knsg251 (赞：0)

## 题目意思
给一串数组，求能整除数组中每一个值的数的个数。
## 题目分析
首先想到的是暴力，直接枚举。但是聪明的你一定看到了 $a[i]$ 的范围。所以应该果断放弃。

正确的思路应该是，先求出整个数组的**最大公因数**，然后去枚举最大公因数的**因子**有多少个，因子的个数就是能整除数组每个值得个数。
## 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;//不开longlong见祖宗
ll n,g,ans,x;
int main(){
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>x;
		g = __gcd(g,x);//求出整个数组最大的公因数 
	} 
	//然后枚举g的因数的个数 
	for(ll i=1;i*i<=g;i++){
		if(g % i == 0){
			ans++;
			if(i * i != g){
				ans++;
			}
		}
	}
	cout<<ans;//因数的个数就是答案 
	return 0;//over
}
```

---

## 作者：Kendrick_Z (赞：0)

很水的题了

首先很容易想到的是这一坨数的gcd是可以满足要求的

那么我们求出来这一坨数的gcd 很显然gcd的因数也是满足的

整体复杂度？O（nlogmaxx+sqrt(gcd)）

log是求gcd的复杂度

记得开long long 不然会WA3

code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0'){
		if(ch=='-'){
			f=-1;
		}		
		ch=getchar();		  
	} 
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
const int N=1e6+10;
int n,a[N],r=1,ans,tot=0,now; 
inline int gcd(int a,int b){
	 return b?gcd(b,a%b):a;  
} 
inline bool check(int k){
	for(int i=1;i<=n;i++){
		if(a[i]%k){
			return false;
		}
	}
	return true;
}
signed main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();	
	}
	r=gcd(a[1],a[2]);
	for(int i=3;i<=n;i++){
		r=gcd(a[i],r);
	}
	for(int i=1;i<=sqrt(r);i++){
		if(r%i==0){
			ans++;
			if(i*i!=r){
				ans++;
			} 
		}
	}
	printf("%lld",ans);
	return 0; 
} 
```


---

