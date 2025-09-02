# Alarm Clocks Everywhere

## 题目描述

```Ivan``` 要睡觉了！他决定先设置自己的闹钟，因为明天有许多必要的 $n$ 个活动要参加。第 $i$ 个活动将在 $x_i$ 分钟开始。```Ivan``` 不想错过任何活动，所以 ```Ivan``` 的闹钟必须在 $x_1,x_2,x_3...x_n$ 分钟都响一次，这样他才不会赖床。（然而闹钟在没有活动的时候响起是允许的）

```Ivan``` 需要为他的闹钟选择两个参数。$y$ 表示闹钟最初开始响铃的时间 ，$p$ 表示闹钟响铃的间隔。 闹钟参数设置好之后，他的闹钟会在 $y ,y+p,y+2p,y+3p...$分钟响起。

```Ivan``` 可以随意设置 $y$ ，但他不能随意设置 $p$ ，因为生产厂家给定了只有 $m$ 种 $p$，即 $p_1 ,p_2,p_3...,p_m$

所以 ```Ivan``` 需要找到两个参数 $y ,p_j$ ，使得闹钟的响铃时间包含 $x_1,x_2,x_3...x_n$ 的所有时间点。而你需要输出 $y,j$。如果有多种答案，任意输出一种。

## 样例 #1

### 输入

```
3 5
3 12 18
2 6 5 3 3
```

### 输出

```
YES
3 4
```

## 样例 #2

### 输入

```
4 2
1 5 17 19
4 5
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
4 2
1 5 17 19
2 1
```

### 输出

```
YES
1 1
```

# 题解

## 作者：Brilliant11001 (赞：3)

## [题目传送门](https://www.luogu.com.cn/problem/CF1155C)

### 题目大意：

给定一个长度为 $n$ 的单增序列 $a$ 和一个长度为 $m$ 的序列 $b$，询问是否存在一个**正整数** $y$ 使得 $a_1\equiv a_2\equiv\cdots \equiv a_n\equiv y\space (\bmod\space p)$，且 $p$ 在序列 $b$ 中出现过。

### 思路：

将条件转化一下，得：是否存在一个正整数 $y$ 使得 $p \mid (a_2 - a_1),p \mid (a_3 - a_2)\cdots p \mid (a_n - a_{n - 1})$，说白了就是我们要寻找的 $p$ 是序列 $a$ 所有相邻项之差的因数。

所以先构造一个差分序列 $c$，然后求出 $c$ 中所有数的最大公因数 $d$。

#### 引理：

任意 $n$ 个正整数 $(n\ge 2)$ 的所有公因数都是这 $n$ 个数的最大公因数的因数。

#### 证明：

先考虑两个数的情况。

设这两个数是 $a,b$，考虑将它们分解质因数，并将质因数对齐，得：

$$a = p_{1}^{a_1}p_{2}^{a_2}\cdots p_{k}^{a_k}$$

$$b = p_{1}^{b_1}p_{2}^{b_2}\cdots p_{k}^{b_k}$$

对于 $a,b$ 的任意因数 $d$，我们也将它分解质因数并对齐，得：

$$d = p_{1}^{c_1}p_{2}^{c_2}\cdots p_{k}^{c_k}$$

注意！这里的 $a_i$ 和 $b_i$ 可能为 $0$！（因为只是对齐处理，可能并不含此质因子）

根据因数的定义可得：

$$c_i \le \min(a_i, b_i),i\in [1, k]$$

而对于 $\gcd(a, b)$，此时有：

$$c_i = \min(a_i, b_i),i\in [1, k]$$

也就是取等了！

所以不难得出，$a,b$ 所有公因数都是最大公因数的因数。

那么推广到 $n$ 个数的情况就不难了，请读者自行证明。

~~其实挺显然的吧。~~

有了这个引理，我们就只需要找序列 $b$ 中是否存在一个数是 $d$ 的因数即可。

然后就是一些小细节了。

时间复杂度为 $O(n + m + \log(\max\{c_i\}))$。

$\texttt{Code:}$
```cpp
#include <iostream>

using namespace std;

const int N = 300010;
typedef long long ll;
int n, m;
ll a[N], p[N], c[N];

ll gcd(ll a, ll b) {
    if(b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    for(int i = 1; i <= m; i++) scanf("%lld", &p[i]);
    for(int i = 1; i <= n; i++) c[i] = a[i] - a[i - 1];
    ll d = c[2];
    for(int i = 3; i <= n; i++) 
        d = gcd(d, c[i]);
    bool flag = false;
    ll fac, ans;
    for(int i = 1; i <= m; i++)
        if(d % p[i] == 0) {
            puts("YES");
            flag = true;
            fac = p[i];
            ans = i;
            break;
        }
    if(!flag) {
        puts("NO");
        return 0;
    }
    if(c[1] % fac == 0) printf("%lld %lld", fac, ans);
    else printf("%lld %lld", c[1] % fac, ans);
    return 0;
}
```

---

## 作者：Aventurine_stone (赞：1)

## 1. 题目分析
看完题，我便知道这道题的核心便是找到所有时间间隔的公共因数，然后与 $p$ 数组比较。  
我第一时间想到的是将时间间隔分解质因数，但看一下数的取值范围，直接就放弃了这个想法。  
但我很快想到可以求最大公因数啊。
## 2. 题目做法
相信大家都知道，两个数的最大公因数，若它除以的数无余数，那么这个数是两个数公因数。  
有了这个结论，我们便可以将所有时间间隔的最大公因数求出来与 $p$ 数组比较，如果 $p$ 数组中有数是这最大公因数的因数，那么有解，否则无解。  
闹钟的起点也很简单，直接设成 $x$ 数组的第一个值就行了。
## 3. 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=300010;
inline long long read()
{
	long long x=0;
	char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
		x=(x<<1)+(x<<3)+c-'0',c=getchar();
	return x;
}
int n,m;
long long a[N],p[N],st,t;
int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	st=a[1];//提前记录，以免被覆盖 
	for(int i=1;i<=m;i++)
		p[i]=read();
	for(int i=1;i<n;i++)
		a[i]=a[i+1]-a[i];
	if(n==2)
	{
		t=a[1];
	}
	else
	{
		t=__gcd(a[1],a[2]);
		for(int i=3;i<n;i++)
			t=__gcd(t,a[i]);
	}
	for(int i=1;i<=m;i++)
	{
		if(!(t%p[i]))
		{
			printf("YES\n%lld %d",st,i);
			return 0;
		}
	}
	printf("NO");
	return 0;
}
```

---

## 作者：Tjaweiof (赞：1)

# CF1155C 题解
[题目传送门](https://www.luogu.com.cn/problem/CF1155C)

思路：先算出每个 $x_i-x_{i-1}(2\le i\le n)$，记为 $d_i$。然后算出 $d$ 数组内所有的数的最大公因数，记为 $s$，在 $p$ 数组内找出 $s$ 的因数。若没有，则输出 `NO`。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m;
long long ans, x[300001], d[300001], p[300001];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++){
		cin >> x[i];
	}
	for (int i = 1; i < n; i++){
		d[i] = x[i + 1] - x[i];
	}
	for (int i = 1; i <= m; i++){
		cin >> p[i];
	}
	ans = d[1];
	for (int i = 2; i < n; i++){
		ans = __gcd(ans, d[i]);
	}
	for (int i = 1; i <= m; i++){
		if (ans % p[i] == 0){
			cout << "YES" << endl << x[1] << " " << i;
			return 0;
		}
	}
	cout << "NO";
	return 0;
}

```

---

## 作者：activeO (赞：1)

## 题意

设置一个初始时间（自己定），要求每次一定要在 $ x_i $ 时响一次，且可以多余地响起，这个时间差得在给定的序列里面选。

## 思路

~~感觉这题不应该是绿题~~

容易发现：初始时间 a 肯定会设成第一个要求响铃的时间。

要满足每次响铃，就必须是找 $ b=\gcd (x_i-a) $ 的因数 $ (i=1,2,...n) $，对于给出的 $ p_i $ 如果 $ p_i\bmod b = 0 $ 就可以直接输出了。

## 代码

**注：变量名与上文略有不同。**

```cpp
#include <bits/stdc++.h>//详见上文，祝大家学习愉快！

#define int long long

using namespace std;

const int maxn=3e5+10;
int a[maxn];

int gcd(int x,int y){
	if(y==0) return x;
	return gcd(y,x%y);
}

signed main(){
	
	int n,m;
	
	scanf("%lld %lld %lld",&n,&m,&a[1]);
	
	int x=a[1],y=0;
	
	for(int i=2;i<=n;i++){
		scanf("%lld",&a[i]);
		y=gcd(a[i]-x,y);
	}
	
	for(int i=1;i<=m;i++){
		int z;
		scanf("%lld",&z);
		if(y%z==0){
			printf("YES\n%lld %lld\n",x,i);
			return 0;
		}
	}
	
	puts("NO");
	
	return 0;
}
```


---

## 作者：rqzhangzehao (赞：0)

## 题目分析
第二行输入了每次闹钟响的时间，第三行输入了间隔时间。而 $x_i$ 和 $p_i$ 都非常大，所以无法暴力。后来转念一想，任意一个 $p_i$ 如果是他们的最大公因数，就输出 `Yes`，否则就输出 `NO`，这道题的核心就是求最大公因数。

## 题目解法
其实分析完题目，就大致知道怎么写了。本题就是求这些时间间隔之差的最大公因数。最后再循环枚举 $p_i$ 能否被他们的最大公因数整除，能就输出 `YES`，然后输出 $x_1$ 和当前的 $p_i$ 就可以结束了，否则输出 `NO`。

## AC 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	int a;
	cin>>a;
	int gcd=0;
	for(int i=1;i<n;i++){
		int x;
		cin>>x;
		if(x-a==0)gcd=a;
		else gcd=__gcd(gcd,abs(x-a));
	}
	for(int i=1;i<=m;i++){
		int p;
		cin>>p;
		if(gcd%p==0){
			cout<<"YES\n"<<a<<" "<<i;
			return 0;
		}
	}
	cout<<"NO";
}
```

---

## 作者：RioFutaba (赞：0)

## 思路
首先闹钟肯定是在第一个时间点响的，即 $y=x_1$。

如果要让闹钟在 $x_i$ 和 $x_{i+1}$ 这两个时间点响，那么有 $p_j  \mid (x_{i+1}-x_i)$。所以我们需要找到一个 $j$，使得对于所有 $1\le i<n$，有 $p_j \mid(x_{i+1}-x_{i})$。枚举 $j$ 即可。

可这样的时间复杂度是 $O(nm)$ 的。所以我们构建 $x$ 的差分数组 $b$，再求 $\displaystyle g=\gcd_{i=2}^{n} b_i$，再枚举并判断每一个 $p_j$ 是否满足 $p_j \mid g$ 即可。时间复杂度为 $O(n+m)$。

因为 $1 \le x_i,p_i \le 10^8$，所以要开 long long。

代码：


```cpp
#include <iostream>
#include <algorithm>
using namespace std;

#define ll long long
const int maxn=3e5+5,maxm=3e5+5;
int n,m,ans;
ll x[maxn],p[maxm],b[maxn],g;
int main(){
	cin >> n >> m;
	for(int i=1;i<=n;i++){
		cin >> x[i];
		b[i]=x[i]-x[i-1];//差分数组
		if(i==2) g=b[i];//初始时g=b[2]
		g=__gcd(g,b[i]);
	}
	for(int i=1;i<=m;i++){
		cin >> p[i];
		if(g%p[i]==0) ans=i;//满足要求
	}
	if(ans){
		cout << "YES\n";
		cout << x[1] << " " << ans << "\n";
	}else cout << "NO\n";	
	return 0;
}
```

---

## 作者：Furina_Saikou (赞：0)

# 思路

我们先看 $x_1$ 到 $x_2$ 的情况，要想在闹钟响的时间中同时包含这两个点，我们可以将起始时间设为 $x_1$，那么响铃的间隔时间 $p$ 显然应为 $x_1$ 到 $x_2$ 经过的时间的因子，即 $p | (x_2-x_1)$。满足了 $x_1$ 到 $x_2$ 的情况，再看 $x_2$ 到 $x_3$ 的情况，由于 $x_1$ 到 $x_2$ 是满足的，所以新的起点其实就是 $x_2$，这样一来，就是相同的问题了，对于后面的情况也适用，所以我们就将题目转化为了在 $p_i$ 中寻找一个下标 $j$ 使得 $\forall a_i,p_j \mid a_i$，其中 $a_i=x_{i+1}-x_{i}(i<n)$，即相邻两个时间点的间隔。

判断 $p_j$ 是否是所有 $a_i$ 的因子，只需要预处理出所有 $a_i$ 的最大公因子，再 $O(1)$ 判断 $p_j$ 能不能整除这个最大公因子就行，总时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=415411;
int n,m,x[N],p[N],gcds;
signed main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>x[i];
        if(i==1)continue;
        gcds=i==2?x[i]-x[i-1]:__gcd(gcds,x[i]-x[i-1]);
    }
    for(int i=1;i<=m;i++)
    {
        cin>>p[i];
        if(gcds%p[i]==0)
        {
            cout<<"YES\n"<<x[1]<<" "<<i;
            return 0;
        }
    }
    cout<<"NO";
	return 0;
}
```

---

## 作者：许多 (赞：0)

基础数论题

前置知识：辗转相除法。

首先一个很显然的性质，当 $y=x_1$ 的时候一定是最优的（谁家好人明明没事还定个闹钟啊）。

### 先考虑一个小问题

如果一个闹钟响了之后要过 4 分钟再响一次，响完第二次后过 6 分钟要再响一次，那闹钟间隔**最大**可以是多少呢？

明显这个答案是 2，也就是 $\gcd(4,6)$。

如果一个闹钟响了之后要过 $x_1$ 分钟再响一次，响完第二次后过 $x_2$ 分钟要再响一次，那闹钟间隔**最大**就是 $\gcd(x_1,x_2)$。

### 回到题目

那这个题的**最大**间隔就是 $\gcd(x_2-x_1,x_3-x_2,\dots,x_n-x_{n-1})$，我们设他为 $ans$。

现在最大间隔求出来了，只要 $p_i\mid ans$，那么这个间隔就是合法的，如果对于所有 $p_i$，$p_i\nmid ans$，则没有答案。

# Code
```cpp
#include<bits/stdc++.h>
#include<cstdio>
#define N 333333
#define LL long long
using namespace std;
inline LL read(){
    LL x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*f;
}
LL gcd(LL x,LL y){//辗转相除法
	if(y==0)return x;
	return gcd(y,x%y);
}
LL n,m,y,ans;
LL x[N],p[N];
int main(){
    n=read();m=read();
    for(LL i=1;i<=n;i++)
        x[i]=read();
    for(LL i=1;i<=m;i++)
        p[i]=read();
    y=x[1];
    ans=x[2]-x[1];
    for(LL i=2;i<n;i++)
        ans=gcd(ans,x[i+1]-x[i]);
    for(LL i=1;i<=m;i++)
        if(ans%p[i]==0){
            printf("YES\n%lld %lld",y,i);
            return 0;
        }
    printf("NO");
    return 0;
}
```


---

## 作者：ljk8886 (赞：0)

# 题目大意
找到一组 $y$ 和 $p_{j}$ 满足闹钟每一个时间点都响。若没有，输出 `NO`。
# 题目分析
首先，我们可以看出 $y$ 肯定是 $x_{1}$。其次，$p$ 一定是每个时间点与第一个时间点的差的最大公因数，我们可以用辗转相除法求出最大公因数。最后，我们只需要循环枚举每一个合适的间隔，找到了，就输出 `YES`、初始时间以及间隔的编号，反之，输出 `NO`。

## 辗转相除法
```cpp
int gcd(int a,int b)//辗转相除法
{
    int r=a%b;
    while(r!=0)
    {
        a=b;
        b=r;
        r=a%b;
    }
    return b;
}
```

# 完整代码
```cpp
#include<iostream>
using namespace std;
const int N=3e5+5;
#define int long long//开long long
int gcd(int a,int b)//辗转相除法
{
    int r=a%b;
    while(r!=0)
    {
        a=b;
        b=r;
        r=a%b;
    }
    return b;
}
int x[N],p[N],c[N],n,m;
signed main()
{
    cin>>n>>m;
    cin>>x[1];
    for(int i=2;i<=n;i++)
    {
        cin>>x[i];
        c[i-1]=x[i]-x[1];//计算差
    }
    for(int i=1;i<=m;i++)
    {
        cin>>p[i];
    }
    int g=c[1];//计算最大公因数
    for(int i=2;i<n;i++)//从2到n-1逐个计算
    {
        g=gcd(g,c[i]);
    }
    for(int i=1;i<=m;i++)
    {
        if(g%p[i]==0)//如果有这种间隔，就输出
        {
            cout<<"YES"<<endl;
            cout<<x[1]<<" "<<i<<endl;//初始时间必为第一个时间点
            return 0;
        }
    }
    cout<<"NO"<<endl;//如果没有这种间隔，输出NO
    return 0;
}
```

---

## 作者：ModestCoder_ (赞：0)

显而易见一个$p$合法的充要条件是所有$x$在$modp$意义下同余

很难做，再想想

既然同余的话是不是两个相减就是$p$的倍数

那么又因为$x$递增，把相邻$x$的差的$gcd$求出来

看看哪个$p$整除那个$gcd$就好了

Code：

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
LL n, m, x, y, X;

inline LL read(){
	LL s = 0, w = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') w = -1;
	for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
	return s * w;
}

LL gcd(LL m, LL n){ return !n ? m : gcd(n, m % n); }

int main(){
	n = read(), m = read();
	X = x = read(), y = read(), x = y - x;
	for (int i = 3; i <= n; ++i){
		LL z = read();
		x = gcd(x, z - y), y = z;
	}
	for (LL i = 1; i <= m; ++i){
		LL z = read();
		if (x % z == 0) return printf("YES\n%lld %lld\n", X, i), 0;
	}
	puts("NO");
	return 0;
}
```


---

## 作者：冒泡ioa (赞：0)

> [博客链接](http://bubbleioa.top/archives/872)

我们要找到一个 x和d 使得 $x+kd = a_i$  k为正整数

如果我们的时间累积到 $a_i$ 了，那么我们其实就是要满足 $a_i+kd=a_{i+1}$ 即 $a_{i+1}-a_i=kd$

所以我们就是要用一个间隔来遍历到所有时间点，这个间隔显然是所有相邻时间间隔的gcd，记为d

然后看看第二行里面有没有d的约数，有的话就输出

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=300003;
int n,m;
ll x,d,z;

ll gcd(ll a,ll b){
	return b?gcd(b,a%b):a;
}

int main(){
	scanf("%d%d",&n,&m);
	scanf("%lld",&x);
	for (int i=1;i<n;i++) {
		scanf("%lld", &z);
		d=gcd(d,abs(z-x));
	}
	for(int i=1;i<=m;i++){
		ll p;cin>>p;
		if(d%p==0){
			printf("YES\n%lld %d",x,i);
			return 0;
		}
	}
	printf("NO");
	return 0;
}
```

---

## 作者：Rainy_chen (赞：0)

对于给定的$n$个时刻$x_i$ 我们要求一个间隔$p$能够满足
$$p\mid x_{i+1}-x_i(0<i<n)$$
那么对于给定的$n$个时刻 我们先求出两两之间的差$d_i$  
之后很显然的有$p \mid gcd(d_1,d_2\dots,d_{n-1})$  
所以我们求出后面这一坨东西 之后再枚举一下给定的所有$p$是否有满足条件的即可  

```cpp
#include<bits/stdc++.h>

using namespace std;
typedef long long int_t;

int_t read(){
    int_t x=0;char ch=0;
    while(!isdigit(ch))ch=getchar();
    while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
    return x;
}

int_t gcd(int_t a,int_t b){
    return b?gcd(b,a%b):a;
}

int main(){
    int_t n = read(),m = read(),lx = read(),pr=-1;
    int_t fans = lx;
    for(int_t i=2;i<=n;i++){
        int_t x = read();
        if(pr == -1)pr = x-lx;
        else pr = gcd(pr,x-lx);
        lx = x;
    }
    for(int_t i=1;i<=m;i++){
        int_t p = read();
        if(pr % p == 0){
            cout<<"YES\n"<<fans<<" "<<i;
            return 0;
        }
    }
    cout<<"NO";
}
```

---

