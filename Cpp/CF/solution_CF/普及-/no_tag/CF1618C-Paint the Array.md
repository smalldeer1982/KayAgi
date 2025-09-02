# Paint the Array

## 题目描述

You are given an array $ a $ consisting of $ n $ positive integers. You have to choose a positive integer $ d $ and paint all elements into two colors. All elements which are divisible by $ d $ will be painted red, and all other elements will be painted blue.

The coloring is called beautiful if there are no pairs of adjacent elements with the same color in the array. Your task is to find any value of $ d $ which yields a beautiful coloring, or report that it is impossible.

## 样例 #1

### 输入

```
5
5
1 2 3 4 5
3
10 5 15
3
100 10 200
10
9 8 2 6 6 2 8 6 5 4
2
1 3```

### 输出

```
2
0
100
0
3```

# 题解

## 作者：j1ANGFeng (赞：6)

首先如果这个数列符合条件,那么它有两种情况:

1. 偶数位全都能被 d 整除,奇数位全都不能被 d 整除。

1. 偶数位全都不能被 d 整除,奇数位全都能被 d 整除。

那么 d 呢?

首先 d 一定是能被所有偶数位(奇数位全都不能被 d 整除)整除或被所有奇数位(偶数位全都不能被 d 整除)整除的数。

那么为了防止不应该被整除的位数被整除的几率下降,我们可以使用最大公因数作为 d 。

为什么用最大公因数呢？

`12 6 24`

观察上面那个数列可以发现,除了最大公因数 12 其他数 $( 3 , 6 )$ 都会被 6 整除所以为最大公因数是最优化解。 

那么只需要判断两种情况(最上面)如果都不符合就输出 0 就行了

#### AC   CODE
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define ll long long
using namespace std;
ll a[1001];
ll gcdd(ll a,ll b){
	ll r=a%b;
	while(r){
		a=b;
		b=r;
		r=a%b;
	}
	return b;
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n;
		scanf("%d",&n);
		ll g1=0,g2=0;
		for(int i=1;i<=n;++i){
		  scanf("%lld",&a[i]);
		  if(i%2)
		    g1=gcdd(g1,a[i]);
		  else
		    g2=gcdd(g2,a[i]);
		}
		int f=0;
		for(int i=2;i<=n;i+=2)
		  if(a[i]%g1==0){
		  	f=1;
		  }
		if(f==0)
		  printf("%lld\n",g1);
		else{
			for(int i=1;i<=n;i+=2)
			  if(a[i]%g2==0){
			  	f=0;
			  }
			if(f){
				printf("%lld\n",g2);
			}
			else
			  printf("0\n");
		}
	}
}
```

---

## 作者：activeO (赞：3)

## 题意

给你一个长度为 n 的序列，问你存不存在一个 d，使得相邻的元素 $ x_i,x_{i+1} $ 满足：

 $ x_i \bmod d = 0 \&\& x_{i+1} \bmod d \neq 0 $ 或者

 $ x_i \bmod d \neq 0 \&\& x_{i+1} \bmod d=0 $。

存在就输出 d，否则输出0.

## 思路

我们就隔一个元素算 gcd。

记奇数下标的 gcd 为 x，偶数下标的 gcd 为 y。

我们要求的 d，肯定是 x 或 y 或他们的因数，如果 x 和 y 都不满足 d，显然他们的因数也不可能满足。

由于题目只要求输出任意一个，就只考虑 x 和 y。

- 对于 x，看看 $ x_{2i} $ 是否能整除
- 对于 y，看看 $ x_{2i+1} $ 是否能整除

最后输出 x 和 y 中满足的，如果都不满足就输出 0。

## 代码

```cpp
#include <bits/stdc++.h>//祝大家学习愉快！

#define int long long

using namespace std;

const int maxn=110;
int a[maxn];

int gcd(int x,int y){
	if(y==0) return x;
	return gcd(y,x%y);
}

signed main(){
	
	int t;
	
	scanf("%lld",&t);
	
	while(t--){
		int n,x=0,y=0;
		scanf("%lld",&n);
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i]);
			if(i&1) x=gcd(x,a[i]);
			else y=gcd(y,a[i]);
		}
		bool fl1=1,fl2=1;
		for(int i=1;i<=n;i++){
			if((i&1)&&a[i]%y==0) fl1=0;
			if((!(i&1))&&a[i]%x==0) fl2=0;
		}
		if(fl2) printf("%lld\n",x);
		else if(fl1) printf("%lld\n",y);
		else puts("0");
	}
	
	return 0;
}
```


---

## 作者：Implicit (赞：2)

显然序列最终的染色结果只可能是 红蓝红蓝红... 和 蓝红蓝红蓝...

这俩本质相同，以 红蓝红蓝红... 举例罢

先求出所有奇数位数的 $\gcd$，即求
$$G=\gcd(a_1,a_3,\cdots)$$
然后显然 $g\mid G$ .

不难发现所有偶数位的数必然不能被 $G$ 整除，可以用反证法轻易证明 .

然后如果行输出 $G$ 就完了 .

Code:

```cpp
using namespace std;
typedef long long ll;
const int N = 114;
int T, n;
ll a[N];
ll gcd(ll a, ll b){return b ? gcd(b, a%b) : a;}
int main()
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		for (int i=1; i<=n; i++) scanf("%lld", a+i);
		ll ans = 0;
		ll g = a[1];
		for (int i=3; i<=n; i+=2) g = gcd(g, a[i]);
		bool v = true;
		for (int i=2; i<=n; i+=2)
			if (!(a[i] % g)){v = false; break;}
		ans = g * v;
		g = a[2];
		for (int i=4; i<=n; i+=2) g = gcd(g, a[i]);
		v = true;
		for (int i=1; i<=n; i+=2)
			if (!(a[i] % g)){v = false; break;}
		ans = max(ans, g * v);
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：Hooch (赞：0)

### 题目大意

给定一个长度 $n$ 的序列。求出有无一个 $x$，使得每两个相邻元素中只有一个能整除 $x$。

### 思路

由题意可推测，能整除 $x$ 的元素下标必定**全**是奇数，或**全**是偶数。

于是我们分别把奇数下标的元素取出来，将它们集合的 $\gcd$ 求出，看一看偶数下标元素是否能整除它。

偶数下标同理。

### 代码

```cpp
#include <bits/stdc++.h>
#define rep1(i, j, n) for (register int i = j; i <= (int)(n); ++i)
#define rep2(i, j, n) for (register int i = j; i >= (int)(n); --i)
#define il inline
using namespace std;
namespace D_K_D {
	const int Buffer_Size = 1<<10;
	char buffer[Buffer_Size], *ihead = buffer + Buffer_Size, *itail = ihead;
	char Next_Char() {
		if (ihead == itail) fread(buffer, 1, Buffer_Size, stdin), ihead = buffer;
		return *ihead++;
	}
	template <typename T>
	il void read(T &x) {
		x = 0; T f = 1; char ch = Next_Char();
		while (!isdigit(ch)) {if (ch == '-') f = -1; ch = Next_Char();}
		while (isdigit(ch)) {x = (x << 1) + (x << 3) + (ch & 15); ch = Next_Char();} x *= f;
	}
}
using namespace D_K_D;
const int N = 105, inf = 0x3f3f3f3f, mod = 1;
#define int long long
#define _gcd(a, b) __gcd(min(a, b), max(a, b))
int a[N], b[N], n, t, c[N], t1, t2;
signed main(void) {
	ios::sync_with_stdio(0);
	cin >> t; int tot = 0;
	while (t--) {
		++tot; 
		cin >> n; int ans = 0; t1 = t2 = 0;
		rep1(i, 1, n) {cin >> a[i]; if (i & 1) b[++t1] = a[i]; else c[++t2] = a[i];} 
		if (n == 2) {
			if (a[1] == a[2]) cout << 0 << endl;
			else cout << max(a[1], a[2]) << endl;
			continue;
		} else if (n == 3) {
			if (a[2] % _gcd(a[1], a[3])) cout << _gcd(a[1], a[3]) << endl;
			else if (a[1] % a[2] && a[3] % a[2]) cout << a[2] << endl;
			else cout << 0 << endl;
			continue;
		}
		rep1(i, 1, t1) rep1(j, i + 1, t1) {
			int k = _gcd(b[i], b[j]);
			if (!ans) ans = k; else ans = _gcd(ans, k);
		}
		if (ans > 1) { bool flg = 0;
			rep1(i, 1, t2) if (c[i] % ans == 0) {flg = 1; break;}
			if (!flg) {cout << ans << endl; continue;}
		} ans = 0;
		rep1(i, 1, t2) rep1(j, i + 1, t2) {
			int k = _gcd(c[i], c[j]);
			if (!ans) ans = k; else ans = _gcd(ans, k);
		}
		if (ans > 1) { bool flg = 0;
			rep1(i, 1, t1) if (b[i] % ans == 0) {flg = 1; break;}
			if (!flg) {cout << ans << endl; continue;}
		}
		cout << 0 << endl;
	}
}
```

---

## 作者：WhitD (赞：0)

## 题意简述
给定 T 个数列，问是否存在一个数 d，使每一对相邻的两个数，都满足正好一个被 d 整除，另一个无法被 d 整除。
## 题目分析
普通的暴力肯定是行不通了，毕竟数据是 1e18 的，但是经过分析我们发现，可行的情况只有如下两种：对于数 d，所有奇数位的都能被 d 整除，所有偶数位的都不能被 d 整除，根据题意，图就是下面这样。

![](https://cdn.luogu.com.cn/upload/image_hosting/lj5l3gdg.png)

反过来亦是如此，对于数 d，所有偶数位的都能被 d 整除，所有奇数位的都不能被 d 整除，根据题意，图就是下面这样。
![](https://cdn.luogu.com.cn/upload/image_hosting/xloxhqon.png)

（我是画渣，大家见谅）。

满足条件的情况可以确定只有如上两种。

------------
### 那么
我们不妨先计算出每组数据奇数位和偶数位的最大公因数（GCD）（因为 GCD 肯定能被对应位整除），然后根据我们上面的分析可以得出如下结论：
1. 如果奇数位的 GCD 不能被所有偶数位整除，那么输出他。
1. 反过来，如果偶数位的 GCD 不能被所有奇数位整除，输出他。
1. 如果上述条件都无法满足，那么输出 0。
## AC代码
  ```cpp
    #include<bits/stdc++.h>
    using namespace std;
    long long T,n,a[105];//1e18啊oier们，不开long long见祖宗！ 
    int main()
    {
        cin>>T;
        while(T--)
        {
            cin>>n;
            for(int i=1;i<=n;i++)
                cin>>a[i];
            long long gcd1=0,gcd2=0;//gcd1是奇数位GCD,gcd2是偶数位GCD 
            for(int i=1;i<=n;i++)
            {
                if(i&1)//上文提到的，分别计算奇偶位的GCD，（ &1 是位运算，可以判断是否为奇数） 
                    gcd1=__gcd(gcd1,a[i]);
                else 
                    gcd2=__gcd(gcd2,a[i]);
            }
            bool flag=true;//flag统计是否满足条件 
            for(int i=1;i<=n;i++)//只统计奇（偶）的，所以每次记得特判
                if(a[i]%gcd1==0&& i%2==0)//判断是否不满足条件一 
                    flag=false;
            if(flag)
                cout<<gcd1<<endl;
            else
            {
                flag=true;
                for(int i=1;i<=n;i++)
                    if(a[i]%gcd2==0&& i&1)//判断是否不满足条件二 
                        flag=false;
                if(flag)
                    cout<<gcd2<<endl;
                else
                    cout<<0<<endl;//都不满足输出0 
            }
        }
        return 0;
    }
  ```
 updata：提前祝各位审核大大和读者朋友们新年快乐，元旦快乐

---

## 作者：徐晨轩✅ (赞：0)

对于本题，我们可以对奇数位和偶数位的数分别求一下 $\gcd$，然后：

* 对于奇数位的 $\gcd$，我们检查一下是否所有的偶数位的数都无法整除这个 $\gcd$。如果都无法整除，就输出这个值，`return`（这实际上是所有奇数位都是红色、偶数位都是蓝色的情况）。
* 对于偶数位的 $\gcd$，我们检查一下是否所有的奇数位的数都无法整除这个 $\gcd$。如果都无法整除，就输出这个值，`return`（这实际上是所有奇数位都是蓝色、偶数位都是红色的情况）。
* 输出 $0$（即没有合适的 $d$）。

**注意要用 `long long`！**

AC Code:

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t,n,a[101];
void solve()
{
	int flag1=0,flag2=0,ans=0;
	cin >> n;
	for(int i=1;i<=n;i++)
		cin >> a[i];
	int gcd1=a[1],gcd2=a[2];
	for(int i=1;i<=n;i++)
		if(i%2==1)
			gcd1=__gcd(gcd1,a[i]);
	for(int i=1;i<=n;i++)
		if(i%2==0)
			gcd2=__gcd(gcd2,a[i]);
	for(int i=1;i<=n;i++)
		if(i%2==0&&a[i]%gcd1==0)
			flag1=1;
	if(!flag1)
	{
		cout << gcd1 << endl;
		return;
	}
	for(int i=1;i<=n;i++)
		if(i%2==1&&a[i]%gcd2==0)
			flag2=1;
	if(!flag2)
	{
		cout << gcd2 << endl;
		return;
	}
	cout << 0 << endl;
} 
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> t;
	while(t--)
		solve();
	return 0;
}
```

---

