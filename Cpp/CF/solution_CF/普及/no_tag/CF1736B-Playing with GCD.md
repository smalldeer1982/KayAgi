# Playing with GCD

## 题目描述

You are given an integer array $ a $ of length $ n $ .

Does there exist an array $ b $ consisting of $ n+1 $ positive integers such that $ a_i=\gcd (b_i,b_{i+1}) $ for all $ i $ ( $ 1 \leq i \leq n $ )?

Note that $ \gcd(x, y) $ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ x $ and $ y $ .

## 说明/提示

In the first test case, we can take $ b=[343,343] $ .

In the second test case, one possibility for $ b $ is $ b=[12,8,6] $ .

In the third test case, it can be proved that there does not exist any array $ b $ that fulfills all the conditions.

## 样例 #1

### 输入

```
4
1
343
2
4 2
3
4 2 4
4
1 1 1 1```

### 输出

```
YES
YES
NO
YES```

# 题解

## 作者：jwsdy (赞：10)

# 题解：CF1736B Playing with GCD

## 题目分析

给定长度为 $n$ 的数组 $a$,问是否存在长度为 $n+1$ 的数列 $b$ 保证：

$a_{i}=\gcd(b_{i},b_{i+1})$

**$\gcd(x,y)$ 返回的是 $x$ 和 $y$ 的最大公因数。**

分析可得：$a_{i-1}$ 与 $a_{i}$ 的值均与 $b_{i}$ 有关，$a$ 数组取的最大公因数，则 $b_{i}$ 一定是 $a_{i}$ 和 $a_{i-1}$ 的倍数，要想让 $a$ 数组顺利取到**最大公因数**，则 $b$ 数组应取**最小公倍数**。

## 如何求最小公倍数？

直接用**要求最小公倍数的两数的乘积除以两数的最大公因数**即可，因为求乘积时，最大公因数算了两次。

而最大公因数可以用**辗转相除法**求（~~毕竟正规考试时不允许使用自带函数。。。~~）。

写完后还应再检查一下， $b$ 数组的值是否真正符合题目要求。

话不多说，上代码！

### code
```
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int N=1e6+100;
int n,t;
int a[N],b[N];
//辗转相除法求最大公因数
int gcd(int a,int b){
	if(a%b==0) return b;
	return gcd(b,a%b);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		a[0]=a[n+1]=1;//将无初始值却要用到的数赋为1
		for(int i=1;i<=n+1;i++)//求最小公倍数
		b[i]=a[i]*a[i-1]/gcd(a[i],a[i-1]);
		bool r=1;//判断是否符合题目要求
		for(int i=1;i<=n;i++){
			if(gcd(b[i],b[i+1])!=a[i]){
				cout<<"NO"<<endl;
				r=0;
				break;
			}
		}
		if(r) cout<<"YES"<<endl;
	}
	return 0;
}
```
**完结撒花❀！**

---

## 作者：Larryyu (赞：8)

## _Description_
给定 $a_1,a_2\dots a_n$，问是否存在一个 $b$ 数列满足 $\gcd(b_i,b_{i+1})=a_i$。

此处 $\gcd(x,y)$ 表示 $x$ 与 $y$ 的最大公因数。
## _Solution_
对于 $a_i,a_{i+1}$，都有 $b_i$ 的贡献，所以 $b_i$ 必为 $a_i,a_{i+1}$ 的公倍数，最后遍历 $b_i$ 验证，此处 $b_i$ 取 $a_i,a_{i+1}$ 的最小公倍数即可。
## _Code_
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int t;
int n;
int a[100100],b[100100];
ll read(){
    ll x=0,f=1;
    char ch;
    ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }
    return x*f;
}
int main(){
	t=read();
	while(t--){
		n=read();
		a[0]=1;
		a[n+1]=1;
		for(int i=1;i<=n;i++){
			a[i]=read();
		}
		for(int i=1;i<=n+1;i++){ //取LCMM
			b[i]=a[i]*a[i-1]/__gcd(a[i],a[i-1]);
		}
		bool f=0;
		for(int i=1;i<=n;i++){  
			if(__gcd(b[i],b[i+1])!=a[i]){
				cout<<"NO"<<endl;  //验证失败
				f=1;
				break;
			}
		}
		if(!f) cout<<"YES"<<endl;
	}
	return 0;
}

```
#### _完结撒花！！_

---

## 作者：Lemansky (赞：3)

### 简要题意

给定数列 $a$，问是否存在一个 $b$ 数列满足 $\gcd(b_i,b_{i+1})=a_i$。

### 解题分析

首先由 $a_{i-1}=\gcd(b_{i-1},b_i),a_i=\gcd(b_i,b_{i+1})$，容易得到 $b$ 数列的构造方式是 $b_i=\text{lcm}(a_{i-1},a_i)$，其中我们使 $b_1=a_1,b_{n+1}=a_n$。

这一点其他题解都讲了，但是判断时并不需要多个循环遍历。

其实我们只需要拓展一个判断，就能和输入同步解决了：

+ 当 $n$ 为 $1,2$ 时，上述构造一定成立。

+ $n\ge3$ 时，数列 $a$ 中存在 $a_i,a_{i+2}$，它们的最大公约数为 $p$，有 $\gcd(b_{i+1}=\text{lcm}(a_i,a_{i+1}),b_{i+2}=\text{lcm}(a_{i+1},a_{i+2}))=\text{lcm}(a_{i+1},p)$，易知仅当 $a_{i+1}$ 为 $p$ 的倍数时可以使构造成立。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[100005];
int main(){
	scanf("%d",&t);
	while(t--){
		bool f=1;
		scanf("%d",&n);
		for(int i=1;i<=2&&i<=n;i++) scanf("%d",&a[i]);//保证输入
		for(int i=3;i<=n;i++){
			scanf("%d",&a[i]);
			if(a[i-1]%__gcd(a[i-2],a[i])!=0) f=0;//判断无解
		}
		puts(f?"YES":"NO");
	}
	return 0;
}
```

---

## 作者：copper_ingot (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1736B)

简单思路题。

因为 $a_i$ 和 $a_{i - 1}$ 都是 $b_i$ 的因数，所以最好的方案是 $b_i = \operatorname{lcm}(a_i,a_{i - 1})$。

因为如果 $b_i = \operatorname{lcm}(a_i,a_{i - 1}) \times k$（$k > 1$ 且 $k$ 为整数），那么它就有可能与 $b_{i - 1}$ 和 $b_{i + 1}$ 有更大的公因数。

所以使用最好方案，如果还是不能满足就无解，否则输出答案。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, a[200001], b[200001];
inline int read(){
	int x = 0, f = 1; char c = getchar();
	while (!isdigit(c)){if (c == '-') f = -1; c = getchar();}
	while (isdigit(c)) x = x * 10 + c - 48, c = getchar();
	return f * x;
}
int main(){
	t = read();
	while (t--){
		n = read(); int f = 0;
		for (int i = 1; i <= n; i++) a[i] = read();
		a[0] = 1, a[n + 1] = 1;
		for (int i = 1; i <= n + 1; i++) b[i] = a[i] * a[i - 1] / __gcd(a[i], a[i - 1]);
		for (int i = 1; i <= n; i++) if (__gcd(b[i], b[i + 1]) != a[i]){puts("NO"); f = 1; break;}
		if (!f) puts("YES");
	}
	return 0;
}
```

---

## 作者：Texas_the_Omertosa (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1736B)

### 0x01 思路

分析数列：$a_{i-1}=\gcd(b_{i-1},b_i),a_i=\gcd(b_i,b_{i+1})$，所以 $b_i$ 既是 $a_{i-1}$ 的倍数，又是 $a_i$ 的倍数。所以我们可以使 $b_i=\operatorname{lcm}(a_{i-1},a_i)$，特别的，我们使 $b_1=a_1,b_{n+1}=a_n$。然后最后扫一遍检验一下就行了。

### 0c02 AC Code

```cpp
#include <bits/stdc++.h>
#define int long long
#define N 200005
#define M 100005
#define mod 10000007
#define iinf INT_MAX
#define linf LLONG_MAX
#define ios ios::sync_with_stdio(0);cin.tie(0);
using namespace std;
int a[N];
int b[N];
inline int lcm(int a, int b)
{
	return a * b / __gcd(a, b);
}
signed main()
{
	ios;
	int t;
	cin >> t;
	for (int asdf = 1; asdf <= t; asdf ++)
	{
		bool flag = 1;
		int n;
		cin >> n;
		for (int i = 1; i <= n; i ++)
		{
			cin >> a[i];
		}
		b[1] = a[1];
		for (int i = 2; i <= n; i ++)
		{
			b[i] = lcm(a[i], a[i - 1]);
		}
		b[n + 1] = a[n];
		for (int i = 1; i <= n; i ++)
		{
			if (__gcd(b[i], b[i + 1]) != a[i])
			{
				flag = 0;
				break;
			}
		}
		cout << (flag?"YES\n":"NO\n");
	}
	return 0;
}
```

---

## 作者：zyc230721hzx (赞：0)

蒟蒻的第六篇题解。

[题目传送门](https://www.luogu.com.cn/problem/CF1736B)。


### 思路：
构造一个数列 $b$，使得每一个元素都满足 $b_i=lcm(a_i-1,a_i)$。
- 先从 $i=1$ 开始遍历数组 $a$，构造出数组 $b$；
- 然后遍历数组 $b$，检查 $b$ 中的元素是否满足条件。

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n,a[100001],b[100001];
bool book;
int main()
{
	scanf("%d",&T);
	while(T--){
		book=true;
		scanf("%d",&n);
		a[0]=a[n+1]=1;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			if(i==1)b[i]=a[i];
			else
			b[i]=a[i]*a[i-1]/__gcd(a[i],a[i-1]);
		}if(n<=2){
			printf("YES\n");
			continue;
		}
		for(int i=1;i<=n;i++){
			if(a[i]!=__gcd(b[i+1],b[i])){
				book=false;
			}
		}printf((book?"YES\n":"NO\n"));
	}
	return 0;
}


```


预祝 AC！

---

## 作者：lizhixun (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1736B)

### $\texttt{Description}$

给定一个长度为 $n$ 的 $a$ 数组，要求构造一个 $b$ 数组，满足对于任意的下标 $i$ 满足 $a_i = \gcd(b_i,b_{i+1})$ 的条件，如果可以满足输出 `YES` 否则就输出 `NO` 。

### $\texttt{Solution}$

这题只需要让每一个 $b_i$ 为 $a_i$ 和 $a_{i-1}$ 的公倍数，为了简便，我们直接使用最小公倍数，然后从 $1 \sim n$ 遍历 $b$ 数组，看是否满足 $a_i = \gcd(b_i,b_{i+1})$ 的条件，如果不满足就直接标记一下并直接 `break` 掉节省时间。

再讲一下最大公约数和最小公倍数的求法。

- 最大公约数只需要用**辗转相除法**就行了。

- 而对于最小公倍数就是两数之积除以最大公约数就行。

### $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e6 + 5;
int t, n, a[N], b[N];

class num { // 两个函数
public:
	int gcd(int x, int y) {return x % y == 0 ? y : gcd(y, x % y); }
	int lcm(int x, int y) {return x / gcd(x, y) * y;}
} fun;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cin >> t;
	
	while (t--) {
		cin >> n;
		
		for (int i = 1; i <= n; i++) cin >> a[i];
		a[0] = a[n + 1] = 1; // 把没有初始值但是有用的数标为 1
		
		for (int i = 1; i <= n + 1; i++) {
			b[i] = fun.lcm(a[i], a[i - 1]);
			// 构造数组
		} 
		
		bool flag = 1;
		
		for (int i = 1; i <= n; i++) { // 遍历检查
			int g = fun.gcd(b[i], b[i + 1]);
			if (g == a[i]) continue;
			
			flag = 0;
			break;
		}
		
		cout << (flag ? "YES" : "NO") << "\n";
	}
	
	return 0;
}
```

完结。

---

## 作者：chrispang (赞：0)

~~虽然洛谷提交不了 CF 上的题，但不影响我写题解。~~

### 题目大意

给定长度为 $n$ 的数组 $a$，问是否存一个数组 $b$，满足 $a_i=\gcd(b_i, b_{i+1})$。

### 题目分析

由于 $a_i$ 和 $a_{i-1}$ 都是 $b_i$ 的因数，所以 $b_i$ 肯定是 $a_i$ 和 $a_{i-1}$ 的倍数。而倍数只需要取最小公倍数就好了。如果按照这种方式构造无解，则一定不存在解。

那么怎么求最小公倍数呢？其实只需要两数相乘，之后除以它们的最大公因数就可以了！

### 代码实现


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int T, n, a[100010], b[100010];
int gcd(int x, int y) { //求最大公因数 
	if(y == 0) return x;
	return gcd(y, x % y);
}

bool is() {
	for (int i = 1; i <= n; i++)
		if(gcd(b[i], b[i + 1]) != a[i]) return 0; //如果最大公因数不是a[i]，则说明生成失败 
	return 1; //否则成功 
}

void slove() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	a[0] = a[n + 1] = 1; //为了方便求最小公倍数，两边赋值为1 
	for (int i = 1; i <= n + 1; i++)
		b[i] = a[i] * a[i - 1] / gcd(a[i], a[i - 1]); //b[i]=a[i]和a[i-1]的最小公倍数 
	if(is()) cout << "YES" << endl; //判断生成出来的序列是否符合要求 
	else cout  << "NO" << endl;
}

signed main() {
	cin >> T;
	//写成函数更加直观 
	while(T--) slove();
	return 0;
}
```

---

## 作者：donnieguo (赞：0)

## 思路

记 $b$ 为答案数组。

首先我们不难发现：

- $a_{i-1} = \gcd(b_{i-1},b_i)$

- $a_i = \gcd(b_i,b_{i+1})$

那么也就是说，$b_i$ 是 $a_{i-1}$ 与 $a_i$ 的公倍数，那么我们就可以取 $\operatorname{lcm}(a_{i-1},a_i)$。

知道了以上几点，代码就很好写了。

记得处理一下边界，以及处理出 $b$ 数组之后还要判断一下是否满足条件。

### $\operatorname{lcm}$ 的求法

其实很简单，$\operatorname{lcm}(x,y)$ 就是 $\dfrac{x \times y}{\gcd(x,y)}$。

以下是证明：

由唯一分解定理可得，$x = p_1^{a_1} \times p_2^{a_2} \times \cdots \times p_n^{a_n},y = p_1^{b_1} \times p_2^{b_2} \times \cdots \times p_n^{b_n}$（可能某个 $p_i \; x$ 或 $y$ 没有，这里指数看作 $0$）。

那么 

$$\gcd(x,y) = p_1^{\min(a_1,b_1)} \times p_2^{\min(a_2,b_2)} \times \cdots \times p_n^{\min(a_n,b_n)}$$

$$\operatorname{lcm}(x,y) = p_1^{\max(a_1,b_1)} \times p_2^{\max(a_2,b_2)} \times \cdots \times p_n^{\max(a_n,b_n)}$$

所以 $\gcd(x,y) \times \operatorname{lcm}(x,y) = x \times y$，即 $\operatorname{lcm}(x,y) = \dfrac{x \times y}{\gcd(x,y)}$。

## AC code

```cpp
#include <iostream>
#include <cstring>
#define N 100010
using namespace std;

int T, n, a[N], b[N];
int gcd(int x, int y) {return y == 0 ? x : gcd(y, x % y);}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> T;
	while (T--)
	{
		memset(b, 0, sizeof b);
		cin >> n;
		for (int i = 1; i <= n; i++) cin >> a[i];
		a[0] = a[n + 1] = 1;
		for (int i = 1; i <= n + 1; i++)
			b[i] = a[i] * a[i - 1] / gcd(a[i], a[i - 1]);
		bool flag = 1;
		for (int i = 1; i <= n; i++)
			if (a[i] != gcd(b[i], b[i + 1])) {flag = 0; break;}
		flag ? cout << "YES" << '\n' : cout << "NO" << '\n';
	}
	return 0;
}
```

---

## 作者：Lan_yan (赞：0)

前置知识：最大公因数和最小公倍数。

不懂的自行百度，变强了再来挑战。

## 推导

下列推论中有关 $ \gcd (x,y)$ 的部分请自动理解为 $x$ 和 $y$ 的最大公因数。

因为 $a_i = \gcd (b_i,b_{i+1})$，所以可得 $a_i \mid b_i$，同时 $a_i \mid b_{i+1}$。

同理，$a_{i-1} \mid b_{i-1}$，$a_{i-1} \mid b_i$。

所以，我们可以知道 $a_{i-1} \mid b_i$ 且 $a_i \mid b_i$。

等同于 $b_i$ 是 $a_{i-1}$ 和 $a_i$ 的倍数，也是它们的最小公倍数的倍数。

也就是，$b_i$ 最小为 $a_i$ 和 $a_{i-1}$ 的最小公倍数。

而最小公倍数可被推导为：
$$x \times y \div \gcd (x,y)$$

## 思路

推论一旦出来，题目就非常简单了。

我们只需按照结论套入 $b_i$，最后验证 $a_i$ 是否为 $ \gcd (b_i,b_{i+1})$ 即可。

具体看代码。

## 代码

```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
int n,t,a[100005],b[100005];
int mygcd(int x,int y)//手打的gcd函数，可直接用库函数_gcd解决
{
	if(x%y==0)return y;
	return mygcd(y,x%y);
}
int main()
{
	scanf("%d",&n);
	while(n--)
	{
		int i,j=1;
		scanf("%d",&t);
		a[0]=1;//注意，a[0]必须为1，不然会出事
		for(i=1;i<=t;i++)
		{
			scanf("%d",&a[i]);
			b[i]=a[i]*a[i-1]/mygcd(max(a[i],a[i-1]),min(a[i],a[i-1]));//套入公式
		}
		b[t+1]=a[t];//b数组的最后一个数不能丢
		for(i=1;i<=t;i++)
		{
			if(a[i]!=mygcd(max(b[i],b[i+1]),min(b[i],b[i+1])))//验证a[i]是否为b[i]和b[i+1]的最大公因数
			{
				j=0;break;
			}
		}
		if(j==1)printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```

完结撒花！

---

## 作者：lucky_loser (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1736B)

### 题目大意

给定 $a_1,a_2\dots a_n$，问是否存在一个 $b$ 数列满足 $\gcd(b_i,b_{i+1})=a_i$。
### 题目分析
$a_{i-1}=\gcd(b_{i-1},b_i),a_i=\gcd(b_i,b_{i+1})$，所以 $b_i$ 既是 $a_{i-1}$ 的倍数，又是 $a_i$ 的倍数。所以先求出 $a_i,a_i-1$ 的最小公倍数，最后遍历 $b_i$ 进行验证。

特别的，我们使 $b_1=a_1,b_{n+1}=a_n$。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[100001],b[100001];
int lcm(int x,int y)
{
    return x*y/__gcd(x,y); 
}
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		a[0]=1;
		a[n+1]=1;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		for(int i=1;i<=n+1;i++)
			b[i]=lcm(a[i],a[i-1]);
		bool f=0;
		for(int i=1;i<=n;i++)
			if(__gcd(b[i],b[i+1])!=a[i])
			{
				cout<<"NO"<<endl;
				f=1;
				break;
			}
		if(!f) 
			cout<<"YES"<<endl;
	}
	return 0;
}
```
求过qwq

---

## 作者：zg_ji (赞：0)

### 题目分析

根据题目大意我们可以得出 $a_{i}$ 和 $a_{i-1}$ 一定都是 $b_{i}$ 的因数。

那么构造 $b$ 数列最好的方法就是求 $a_{i}$ 和 $a_{i-1}$ 的最小公倍数。

这里介绍一下最小公倍数的两种求法。

第一种是分解质因数法，第二种是使用最大公约数法。这里我们采用第二种方法，即用 $a_{i}$ 和 $a_{i-1}$ 的乘积除以 $a_{i}$ 和 $a_{i-1}$ 的最大公约数。

构造完 $b$ 数列后，我们就开始求 $b_{i}$ 和 $b_{i+1}$ 的最大公约数，看看其是否与 $a_{i}$ 相等，因为要满足 $a_{i}=\gcd(b_{i},b_{i+1})$，所以就不难推出 $a_{i-1}=\gcd(b_{i},b_{i-1})$ 和 $a_{i}=\gcd(b_{i},b_{i+1})$，那么我们就去遍历一遍，如果不等于了，则可以直接输出了。

### Code

```
#include<bits/stdc++.h>
const int N=2e5+100;
using namespace std;

int T;
int n;
int a[N],b[N];

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--)
	{
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		a[0]=1;
		a[n+1]=1;
		for(int i=1;i<=n+1;i++)
			b[i]=a[i]*a[i-1]/(__gcd(a[i],a[i-1]));
		bool f=false;
		for(int i=1;i<=n;i++)
		{
			if(__gcd(b[i],b[i+1])!=a[i])
			{
				f=true;
				cout<<"NO\n";
				break;
			} 
		}
		if(f==false)
			cout<<"YES\n";
	}
	
	return 0;
	
} 
```

[AC记录](https://www.luogu.com.cn/record/166965411)

---

