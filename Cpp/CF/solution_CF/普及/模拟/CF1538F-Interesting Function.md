# Interesting Function

## 题目描述

给定两个正整数 $l, r$（$l < r$），将 $l$ 不断加 $1$ 直到 $l = r$，求出这一过程中 $l$ 发生变化的位数**总数**。

位数变化指：

- $l=909$，将 $l+1$ 后有 $2$ 位数字发生变化。
- $l=9$，将 $l+1$ 后也有 $2$ 位数字发生变化。
- $l=489999$，将 $l+1$ 后有 $5$ 位数字发生变化。

而总数指：

- $l=10$，$r=20$，个位变化了 $10$ 次，十位变化了 $1$ 次，所以总数为 $11$。

## 样例 #1

### 输入

```
4
1 9
9 10
10 20
1 1000000000```

### 输出

```
8
2
11
1111111110```

# 题解

## 作者：Akoasm_X (赞：10)

题目链接 [CF1538F Interesting Function](https://www.luogu.com.cn/problem/CF1538F)


题目要求统计 $\left[{l},{r}\right]$ 的每个数位的变化，很自然地想到分别统计 $\left[{0},{l}\right]$ 和 $\left[{0},{r}\right]$，然后作差即可。

考虑按位统计，从高位开始统计，暂不考虑比他低的位，那么此时高位以及高位之前的位所组成的数字，就是这一位的变换次数

举个例子 ：计算 $\left[{0},{39567}\right]$，考虑第 $2$ 位，暂且组成的数字是 $39$ ，也就是说这一位从 $0$ 跳到了 $39$，一共跳了 $39$ 次，对于第 $3$、$4$、$5$ 位，变化次数分别是 $395$、$3956$、$39567$。

代码如下

```cpp
#include <bits/stdc++.h>
using namespace std;
int Ans;
inline int read(){
    int x = 0 , f = 1 ; char c = getchar() ;
    while( c >= '0' && c <= '9' ) { x = x * 10 + c - '0' ;Ans += x; c = getchar() ; }
}//在快读加了一句话 Ans += x;根据题目分析，x就是当前这一位的变化次数 
int main(){
	int T;scanf("%d\n",&T);
	while(T--)
	{//先分别统计 [0,l] 和 [0,r] 然后做差 
		Ans = 0;read();Ans = - Ans;read();
		printf("%d\n",Ans);
	}
	return 0;
}
```

---

## 作者：JCLinux (赞：8)

提供一个自认为比较精简的思路：

别看这个题的数据范围是 $10^9$ ,但是 实际上只有**一位**数。

我们假设 $l=99$，$r=111$ 

数从两位数变成三位数，因此我们要统计这三位数变化次数之和。

对于个位数，显然变了 $111-99=12$ 次。既然我们统计完了个位数的变化，这个个位数就**再也没用了**，弃之可已。

问题就变成了 $l=9$ , $r=11$ 了原来的十位数变成了现在的个位数，重复之前的过程。 $11-9=2$ 次。

最后一步就成了 $l=0 $ , $r=1$ 了，有 $1-0=1$ 次。

最终的答案就是这三次的和 $sum=12+2+1$。

按照这个思路，代码可以很精简。

上代码（17行）：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;cin>>t;
	while(t--){
		long long l,r;
		cin >>l>>r;
		long long sum=0ll;
		while(r){
			sum+=(r-l);//注意字体区分 l和1
			r/=10;
			l/=10;
		}
		cout <<sum<<endl;
	}
	return 0;
}
```


---

## 作者：Acc_Robin (赞：5)

赛时发现做出来这 F 题的人比 D 都多...

#### 题意：

给你两个整数 $l,r(1\le l\le r\le 10^9)$，请你求出从 $l$ 每次加一直到 $r$ 的过程中，每个数位上数码变化的次数之和。

比如：

从 $1$ 加到 $9$ 变化了 $8$ 次；

从 $9$ 加到 $10$ 变化了 $2$ 次；

从 $48999$ 加到 $490000$ 变化了 $5$ 次。

#### 题解：

考虑数位DP（其实就算是个找规律）：

令 $f[i]$ 表示 **从 $0$ 加到 $10^i$** 数码变化的次数之和。

那么有 $f[0]=1$ （显然）

以及

$$
f[i]=f[i-1]*10+1
$$

考虑多出一个最高位，最高位从 $0$ 到 $9$ 变化 $9$ 次，以及最后的一次进位了 $f[i-1]+1$。

对于任意的 $x$，从 $0$ 加到 $x$ 的变化次数，可以枚举 $x$ 的每一位，计算贡献。

最终的答案就是 $r$ 的答案减去 $l$ 的答案。

#### 复杂度：

$n$ 表示 $l,r$ 的大小， $T$ 为数据组数。

$O(\log n)$ 预处理 $f[]$ 数组，单次查询为 $O(\log n)$，空间只需要一个 $f[]$ 数组，则总复杂度为

$O(\log n)-O(T\log n)-O(\log n)$

#### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Acc{
#define int long long
	const int N = 15;
	int dp[N],T,l,r;
	int sol(int x){
		int res=0;
		for(int i=0;x;i++)res+=dp[i]*(x%10),x/=10;
		return res;
	}
	void work(){
		dp[0]=1;
		for(int i=1;i<=10;i++)dp[i]=dp[i-1]*10+1;
		for(cin>>T;T--;puts(""))cin>>l>>r,cout<<sol(r)-sol(l);
	}
#undef int
}
int main(){
	return Acc::work(),0;
}
```


---

## 作者：きりと (赞：4)

### 题目大意

给定 $l,r$ ，每次操作可以使 $l+1$ ，求要使得 $l$ 变成 $r$ ，每个数位要被加的次数。

### 解题思路

sb题，题解区有些大佬竟然是用数位dp做的Orz，赛时我一看这题不就是个nt英语阅读理解题吗？显然当我枚举到第 $i$ 位数字的时候，我要使这一位数字能够被 $+1$，那就要让前 $i-1$ 位，每一位数字 $+1$ 十次。

那就很简单了qwq，最后只需要分别算一下 $l$ 和 $r$ 的数位增加次数，做个差就彳亍了。

~~凭什么这题是F题啊~~ ![](https://pic.imgdb.cn/item/60c22019844ef46bb28a8ce9.jpg)

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define forr(i,l,r) for(int i=l;i<=r;i++)
#define ffor(i,r,l) for(int i=r;i>=l;i--)
using namespace std;
signed main()
{
	int t,l,r;
	cin>>t;
	while(t--)
	{
		cin>>l>>r;
		int x=0,y=0;
		while(l)
		{
			x+=l;
			l/=10;
		}
		while(r)
		{
			y+=r;
			r/=10;
		}
		cout<<y-x<<endl;
	}
	return 0;
}

```

---

## 作者：saixingzhe (赞：2)

# 题意
给定两个正整数，$l,r$ $(l<r)$，将 $l$ 不断加 $1$ 直到 $l=r$，求出这一过程中 $l$ 每位发生变化的总次数。
# 思路
首先，如果某一位要加 $1$，它的下一位肯定要加 $10$，这样就简单了，我们只要算 $l$ 和 $r$ 分别从 $0$ 开始每位发生变化的总次数，然后相减即可得出结果。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,l,r;
int main(){
	scanf("%d",&t);
	while(t--){
		int a=0,b=0;
		scanf("%d %d",&l,&r);
		while(l){a+=l;l/=10;}
		while(r){b+=r;r/=10;}
		cout<<b-a<<endl;
	} 
    return 0;
}
```

---

## 作者：xiexinzhe (赞：1)

#### [题目传送门](https://www.luogu.com.cn/problem/CF1538F)

我觉得这道题只能评个橙题。
# 分析
这道题看似范围很大，不可能用循环。但仔细观察，会发现：只需要按照位数从低到高就可以了。
# 举例：
$l=15 , r=30$
首先看个位变化了多少次，个位的变化是： $l+1$ ，个位就变化了一次。所以个位变化的次数就是 $r-l=30-15=15$ 次。

再看十位变化了几次。十位是当个位进位到十位的次数。所以我们只需要把 $l$ 和 $r$ 都除以十，再算差就可以了。所以十位变化的次数就是 $r/10-l/10=3-1=2$ 次。

所以 $15$ 到 $30$ 的总变化次数就是： $15+2=17$ 次。

更高位以此类推。

# 代码：
```cpp
cin>>t;
	for(int i=1;i<=t;i++)
	{
		ans=0;//初值
		cin>>l>>r;
		while(r!=0)
		{
			ans+=r-l;//和累加
			r/=10;l/=10;//每次除以十
		}
		cout<<ans<<endl;
	}
```

感谢大家的支持！

---

## 作者：Register_int (赞：1)

看到数位计数，啪的一下，很快啊！直接上套路。  
题目要求计算的值就是 $[l,r)$ 中每一个数 $+1$ 后会变化的数位总和，再转化为前缀和的形式，就可以直接贺上数位 dp。  
接下来，考虑一个数 $x$ 进行 $+1$ 后会被影响多少数位。这里结合例子来进行分析。  
首先，个位是一定会被影响的。比如 $x=810$ 时，$x+1=811$，数位的变化量为 $1$。  
其次，考虑高位什么时候收到影响。显然，高位只有可能在低位进位时发生 $+1$ 的变化。而只有在低位为 $9$ 的时候，$+1$ 才会发生进位。比如 $x=1919$ 时，$x+1=1920$，变化的数位量为 $2$。多个 $9$ 连续的情况也一样，比如 $x=153999$，$x+1=154000$，影响的数位量为 $4$。  
最后考虑会影响几个数位。根据上面的分析，就可以得出，单个数的答案即为 $x$ 末尾连续 $9$ 的数量 $+1$。  
记忆化搜索里面加个参数，表示当前连续 $9$ 的数量，就可以数位 dp 了。
# AC 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll dp[10][10];

char s[10]; int len;

ll dfs(int p, int cnt, bool lim) {
	if (p == len) return cnt + 1;
	if (!lim && ~dp[p][cnt]) return dp[p][cnt];
	int n = lim ? s[p] ^ '0' : 9; ll res = 0;
	for (int i = 0; i <= n; i++) {
		res += dfs(p + 1, i == 9 ? cnt + 1 : 0, lim && i == n);
	}
	if (!lim) dp[p][cnt] = res;
	return res;
}

inline 
ll solve(ll n) {
	memset(dp, 0xff, sizeof dp);
	sprintf(s, "%lld", n), len = strlen(s);
	return dfs(0, 0, 1);
}

int t;

ll l, r;

int main() {
	for (scanf("%d", &t); t--;) scanf("%lld%lld", &l, &r), printf("%lld\n", solve(r - 1) - solve(l - 1));
}
```

---

## 作者：封禁用户 (赞：0)

[更好的阅读体验](https://www.doittomorrow.xyz/post/cf1538f-interesting-function-de-ti-jie/)
## 题目大意
给定两个正整数 $l, r$，将 $l$ 不断加 $1$ 直到 $l = r$，求出这一过程中 $l$ 发生变化的位数总数。

- $1 \le l < r \le 10^9$。
## 思路
假设从 $l$ 处理到 $r$ 变化的次数为 $f(l,r)$。

因为直接求解出 $f(l,r)$ 十分困难，所以可以通过求出 $f(0,l)$ 和 $f(0,r)$ 最后做差得到。

假设一个数为 $x$ 那么从 $0$ 一直变化到 $x$ 对于各位变化的次数就是 $x$。

因为从 $0$ 增加的 $x$ 一共增加了 $x$ 次。

而每当他增加一次，这个数的个位就会变化一次。

考虑从后向前数第 $k$ 为，假设增加一次为 $10^{k-1}$，那么随着每增加一次，第 $k$ 位就会变化一次。

因为走后会变成 $x$，所以第 $k$ 位一共会变换 $\lfloor x/10^{k-1}\rfloor$。


$$f(0,l)=\sum _{i=0}^{(\log_{10}l)-1} \lfloor l/{10^i}\rfloor$$

## AC Code
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=50;
char a[N],b[N];
void solve(){
	int ans=0;
	cin>>a+1>>b+1;
	int n=strlen(a+1),m=strlen(b+1);
	for(int i=1,x=0;i<=n;i++){
		x=x*10+a[i]-48;
		ans-=x;
	}
	for(int i=1,x=0;i<=m;i++){
		x=x*10+b[i]-48;
		ans+=x;
	}
	cout<<ans<<'\n';
}
signed main(){
	int T;
	cin>>T;
	while(T--){
		solve();
	}
	return 0;
}
```

---

## 作者：Underage_potato (赞：0)

[**传送门**](https://www.luogu.com.cn/problem/CF1538F)

这道题可以不用数位 dp 来做，而是通过 $l$，$r$ 来求出变化次数。

## 题意

给定两个正整数 $l, r$（$l < r$），将 $l$ 不断加 $1$ 直到 $l = r$，求出这一过程中 $l$ 发生变化的位数**总数**。

## 思路

一个数的某一位要加一，那么它的下一位肯定会加上十。所以分别统计 $l$，$r$ 每一位变化的总次数，然后作差输出即可。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int l,r,a=0,b=0;
		cin>>l>>r;
		while(l){
			a+=l;
			l/=10;
		}
		while(r){
			b+=r;
			r/=10;
		}
		cout<<b-a<<endl;
	}
	return 0;
}
/* by Underage_potato*/

```


---

## 作者：YangXiaopei (赞：0)

## Solution:

其实在题目中就已经给了我们思路。

我们可以算出每一位变化的次数，再累加即可。

举个例子：

$l = 114514, r = 1919810$。

$\text{个位变换的次数} = 114514 \text{变成} 1919810 \text{的次数} = 1805296$。

$\text{十位变换的次数} = 11451 \text{变成} 191981 \text{的次数} = 180530 $。

$\text{百位变换的次数} = 1145 \text{变成} 19198 \text{的次数} = 18053$。

$\text{千位变换的次数} = 114 \text{变成} 1919 \text{的次数} = 1805$。

$\text{万位变换的次数} = 11 \text{变成} 191 \text{的次数} =  180$。

$\text{十万位变换的次数} = 1 \text{变成} 19 \text{的次数} = 18$。

$\text{百万位变换的次数} = 0 \text{变成} 1 \text{的次数} = 1$。

合起来就是 $1805296 + 180530 + 18053 + 1805 + 180 + 18  + 1 = 2005883$。

这样就能完美切掉这题了。

## Code:

再次提醒您：~~规则千万条，诚信第一条。写题不规范，封号两行泪~~。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t, l, r;
int solve(int a, int b){
	int sum = 0;
	while(a || b){
		sum += abs(a - b);
		a /= 10;
		b /= 10;
	}
	return sum;
}
signed main(){
	cin >> t;
	while(t--){
		cin >> l >> r;
		cout << solve(l, r) << "\n";
	}
	return 0;
} 
```

---

## 作者：huyangmu (赞：0)

看到数据范围，就发现暴力肯定不行，所以考虑数学做法。

这道题求的是 $l$ 变成 $r$ 需要进的位数，根据十进制满十进一的规则，我们只需要计算 $l$ 和 $r$ 每一数位相差的位数，然后除以十统计下一位，一直统计到两个数都为 $0$ 时。
### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,l,r,ans;
int main (){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>T;
	while (T--){
		cin>>l>>r;
		ans=0;
		while (l||r){
			ans+=abs(r-l);
			r/=10,l/=10; 
		}
		cout<<ans<<'\n';
	}
	return 0;
} 


---

