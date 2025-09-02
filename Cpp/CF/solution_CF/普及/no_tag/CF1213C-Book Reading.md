# Book Reading

## 题目描述

有一本包含$n$页的书，页码编号从$1$到$n$。每当你读完一页并且页码能被m整除，你就会记下此页码的最后一位数字。例如，如果$n=15$且$m=5$，则可被$m$整除的页码为$5,10,15$。 他们的最后数字相应地为$5,0,5$，其总和为$10$。  
计算你写下的所有数字的总和。

## 样例 #1

### 输入

```
7
1 1
10 1
100 3
1024 14
998244353 1337
123 144
1234312817382646 13
```

### 输出

```
1
45
153
294
3359835
0
427262129093995
```

# 题解

## 作者：andyli (赞：3)

首先我们想到$Polycarp$写下的数字一定是循环的，因此我们可以计算对于所有$m$，他写下的数字的循环节里包含数字的个数以及循环节所有数字的和。进行暴力打表或手算可以发现，$m(m>10)$上述结果和$m\% 10$的结果是如出一辙，因此我们只需打表出$0\leq m<10$的上述两个值，每次输入时计算$(n,m)$对应的所有循环节里数量的总和，再循环计算除去循环节以外其他写下的数字的和，相加即为最终答案。  
代码如下：  
```cpp
#include <cstdio>

//int xhc[10] = { 0, 45, 20, 45, 20, 5, 20, 45, 20, 45 };
//int chx[10] = { 0, 10, 5, 10, 5, 2, 5, 10, 5, 10 };

int xhc[10]; // 循环节和
int chx[10]; // 循环节长度
int main()
{
    for (int i = 0; i < 10; i++) {
        int cnt = 1, sum = 0;
        for (int j = i; j; j = (j + i) % 10)
            cnt++, sum += j;
        xhc[i] = sum;
        chx[i] = cnt;
    }
    int T;
    scanf("%d", &T);
    while (T--) {
        long long n, m;
        scanf("%lld%lld", &n, &m);
        if (m % 10 == 0)
            printf("0\n");
        else {
            int id = m % 10;
            // n / m - 整除数量
			// n / m / chx[id] - 循环数量 
			// n / m % chx[id] - 去除循环部分剩余数的数量
			// n / m / chx[id] * xhc[id] - 循环部分总和
            long long ans = n / m / chx[id] * xhc[id];
            int cnt = n / m % chx[id];
            for (int i = id; cnt--; i = (i + id) % 10)
                ans += i;
            printf("%lld\n", ans);
        }
    }
    return 0;
}
```

---

## 作者：孑彧 (赞：2)

## C.Book Reading

### 题意描述

有一本包含$n$页的书，页码编号从1到$n$。每当你读完一页并且页码能被$m$整除，你就会记下此页码的最后一位数字。例如，如果$n=15$且$m=5$，则可被$m$整除的页码为5,10,15。 他们的最后数字相应地为5,0,5，其总和为10。计算你写下的所有数字的总和。

### 思路

我们首先可以计算出$1-n$中有多少个$m$的倍数，为$\lfloor\frac{n}{m}\rfloor$，然后显而易见的是，一个数的倍数的个位数是会循环的，比如说2这个数

$2\times1=2,2\times2=4,2\times3=6,2\times4=8,2\times5=10,2\times6=12...$

至此它的尾数就开始循环了，然后我们可以统计出一个循环节的长度，用$\lfloor\frac{n}{m}\rfloor$除以这个长度，然后剩下的暴力循环一遍

### 代码

```c++
#include<cstdio>
#include<iostream>
#include<cstring>
#define LL long long
using namespace std;
int a[100];
LL q,n,m;
int tot;
int main(){
	scanf("%I64d",&q);
	while(q--){
		tot=0;
		scanf("%I64d %I64d",&n,&m);
		for(int i=1;i<=100000000;i++){
			a[++tot]=(m*i)%10;
			if(tot==1){
				continue;
			}
			if(a[tot]==a[1]){
				tot--;
				break;
			}
		}
		LL x=n/m;
		LL y=x/tot;
		x=x%tot;
		LL ans=0;
		for(int i=1;i<=tot;i++){
			ans+=(y*a[i]);
		}
		for(int i=1;i<=x;i++){
			ans+=a[i];
		}
		printf("%I64d\n",ans);
	}
}
```


------------
10月12日update

由于一些奇奇怪怪的原因

我的代码里有一些符号被改了。。。

现在已经修改完毕

实测能过

---

## 作者：chino123 (赞：1)

emmm这道题不需要打表就可以做。
观察数列 我们就可以找到规律。因为只取个位数的和，所以在十进制中，我们可以将m对应的不同十进制余数先存下来。
```cpp
typedef long long ll;
ll a[11];
for(int i=0;i<10;i++)
	a[i]=m*i%10;//分别表示m在不同倍率下的个位数
ll sum=0;
for(int i=0;i<10;i++)
	sum+=a[i];//累加前十个数字 
```
设t为一共需要求和的个数数量，
除了t的个位数，剩下的数和都是sum的倍数。所以只需要处理循环后加上它们就ac了。

下面是ac代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
	int q;
	cin>>q;
	ll n,m;
	while(q--){
		ll ans=0;
		cin>>n>>m;
		ll t=n/m;/*求出有多少个数字可以被m整除*/
		ll a[11];
		for(int i=0;i<10;i++)
			a[i]=m*i%10;//分别表示m在不同倍率下的个位数 
		ll sum=0;
		for(int i=0;i<10;i++)
			sum+=a[i];//首先累加前十个数字 
		ans+=sum*(t/10);//计算除个位数字以外的和 
		for(int i=1;i<=t%10;i++)
			ans+=a[i];//最后加上个位数字的结果。 
		cout<<ans<<endl; 
	}
}
```


---

## 作者：AstaSunch_ (赞：0)

# $\tt 0x00$ 序

蒟蒻的第 $\color{red}\mathbf{26}$ 篇题解。

# $\tt 0x01$ 明

有一本页码从 $1$ 到 $n$ 的书，当你读完的这一页的页码能被 $m$ 整除，则你会记录下这个页码的个位数字，计算所有这样数字的总和。

# $\tt 0x02$ 解

我们知道，这些数字一定是循环的，并且有 $\left\lfloor\dfrac{n}{m}\right\rfloor$ 个。

我们发现，$m>10$ 时的结果和 $m\ \text{mod}\ 10$ 是一样的，所以我们只需要计算最多 $10$ 个数字就行了。

然后就剩下暴力模拟了。

# $\tt 0x03$ 文

~~代码自食其力。~~

---

## 作者：__HHX__ (赞：0)

# 算法（同余）
假设当前页码为 $k$ 并且 $(k + m) \bmod 10$ 是下一页的尾号。

因为 $k \equiv k \pmod {10}$ 并且 $m \equiv m \pmod{10}$。

故 $k + m \equiv k + m \pmod {10}$。

换句话说就是 $(k + m) \bmod 10 = (k \bmod 10 + m \bmod 10 ) \bmod 10$。

因为 $k_i = (k_{i - 1} \bmod 10 + m \bmod 10 )\bmod 10$（$k_2$ 已 $\bmod 10$），故 $k_{i + 1} = (k_i + m \bmod 10) \bmod 10$，故通项公式为 $k_{i} = (k_{i - 1} + m \bmod 10) \bmod 10$。

因为 $m \bmod 10$ 不变，所以 $(k + m \bmod 10 ) \bmod 10$ 的每个 $k$ 都对应一个值。

因为 $k$ 已 $\bmod 10$，所以只有至多 $10$ 种情况。

所以就有一个长度不超过 $10$ 的循环节。

故最后答案为 $ \lfloor {n \over len} \rfloor \times sum_{len} + sum_{n \bmod len}$。
# 代码
```cpp
#include<iostream>
#include<cstring>

using namespace std;

int xh[13], pd[13], s[13], tot;
int main() {
	int t;
	cin >> t;
	while(t--) {
		tot = 0;
		fill(pd, pd + 13, 0);
		fill(s, s + 13, 0);
		long long n , m;
		cin >> n >> m;
		if(n < m) {
			cout << 0 << endl;
			continue;
		}
		n -= n % m;
		for(long long i = m; i <= n; i += m) {
			if(pd[i % 10]) {
				break;
			}
			xh[++tot] = i % 10;
			s[tot] = s[tot - 1] + i % 10;
			pd[i % 10] = 1;
		}
		n /= m;
		cout << n / tot * s[tot] + s[n % tot] << '\n';
	}
	return 0;
}
```

---

## 作者：minVan (赞：0)

**题目大意**

求 $1$ 到 $n$ 之间所有 $m$ 的倍数的个位数（也就是最后一位数）的和。

**解题思路**

模拟、数学、循环节。

按提议模拟即可，可以发现我们让 $m \times 1, m \times 2, m \times 3, \dots, m \times 10$ 一定会出现循环节。找到循环节后，我们可以跳过很多数字，最终只需要最多计算 $10$ 个数字。

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, m, cnt, sum, ans;
bool vis[10];
ll solve(ll x) {
	ll v = x;
	while(x <= n) {
		if(vis[x % 10]) {
			return x - v;
		}
		vis[x % 10] = 1;
		sum += x % 10;
		x += v; 
	}
	return 1;
}
int main() {
	int q;
	cin >> q;
	while(q--) {
		sum = ans = cnt = 0;
		memset(vis, 0, sizeof(vis));
		cin >> n >> m;
		ll x = solve(m);
		if(x == 1) {
			sum = 0;
		} else {
			ans = sum * (n / x);
			x = n / x * x + m;
		}
		for(ll i = max(x, m); i <= n; i += m) {
			ans += i % 10;
		}
		cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：xiaozeyu (赞：0)

# 仔细一想，其实只是红/橙难度

emmmmmm，来点是个人都能懂得

其实你可以发现，每个数的末位是存在循环的

比如：

![](https://cdn.luogu.com.cn/upload/image_hosting/fhqqtnqd.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/0qlm6aje.png)

每个数在10次循环后末尾数是一样的

或者可以找到循环节（蓝色标出了）

以下各种（主要说明在第二块）



------------

**第一个**

常规%10法

要算出每一个末位数 

```cpp
for(int i=1;i*m<=n&&i<=10;i++)
{
	a[i]=(i*m)%10;
}

```

------------

1.1 

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[20];
void init()
{
	int n,m,ans=0;
	cin>>n>>m;
	for(int i=1;i*m<=n&&i<=10;i++)
	{
		a[i]=(i*m)%10;
	}
	int k=(n/m)/10;
	for(int i=1;i<=10;i++) ans+=a[i]*k;
	for(int i=1;i<=(n/m)-(k*10);i++) ans+=a[i];
	cout<<ans<<"\n";
}
signed main()
{
	int t;
	cin>>t;
	for(int i=1;i<=t;i++) init();
	return 0;
}
```



------------

1.2 这与上面同理

也可以:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int q,n,m,ans=0;
signed main()
{
	freopen("book.in","r",stdin);
	freopen("book.out","w",stdout);
	cin>>q;
	while(q--)
	{
		cin>>n>>m;
		int c,st=0;
		ans=0;
		for(int i=1;i<=10;i++)
		{
			int k=m*i;
			if(k%10==0) 
			{
				c=i;
				break;
			}
		}
		for(int i=1;i<=c;i++)
		{
			st+=(m*i)%10;
		}
		int a1=m*c;
		int a2=n/a1;
		ans+=a2*st;
		int a3=n%a1;
		int a4=a3/m;
		for(int i=1;i<=a4;i++)
		{
			ans+=(m*i)%10;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```



------------

**第二种**

找到循环节

huanz 是一个循环中末位数字总和

huanc 是一个循环中的数字个数

a 是一个循环中的每个数

ll是计算中的“媒介”

先算出循环节数

把循环节数*每个循环节末位数总和加入ans中,

即 

```cpp  
ll=n/(huanc*m);
ans+=ll*huanz;
```

把处理的数减去在上面用到的总数，即  ``` n=n-ll*(huanc*m); ```

剩下的n还可以分成ll个m，即 ``` ll=n/m; ```

枚举1-ll倍的末位数

```cpp

for(long long i=1;i<=ll;i++)
	ans+=a[i];
printf("%lld\n",ans);

```

这时你才会发现这题多么简单

------------

```cpp
#include<bits/stdc++.h>
using namespace std;
long long q,n,m,ans,huanz,huanc,a[20],ll;
int main()
{
	freopen("book.in","r",stdin);
	freopen("book.out","w",stdout);
	cin>>q;
	for(long long k=1;k<=q;k++)
	{
		ans=0;
		huanz=0;
		huanc=0;
		memset(a,0,sizeof a);
		scanf("%lld%lld",&n,&m);
		if(m>n)
		{
			printf("0\n");
			continue;
		}
		while(n>=m)
		{
			huanc++;
			a[huanc]=(huanc*m)%10;
			huanz+=a[huanc];
			if(a[huanc]==0)
				break;
		}
		if(huanz==0) 
		{
			printf("0\n");
			continue;
		}
		ll=n/(huanc*m);
		ans+=ll*huanz;
		n=n-ll*(huanc*m);
		ll=n/m;
		for(long long i=1;i<=ll;i++)
			ans+=a[i];
		printf("%lld\n",ans);
	}
}
```

------------

**第三种**

超级打表法

先用手或程序把每个数字的每个倍数算出，存下循环的内容放在一个二维数组之中

与第二种解法有相通之处

这是一种不太用脑子的方法，但是有些费手

这在比赛中可以用的

这是必须要学会的方法，在比赛中万一出现了不会正解或时间太慢，反手一个打表

细心点，发现规律基本可以概括位 5-10-5-10

------------

激动人心

只要末位就够了

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
inline int read() {
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x; return x;
}
const int biao[12][11]={
	0,0,0,0,0,0,0,0,0,0,0,
	0,1,2,3,4,5,6,7,8,9,0,
	0,2,4,6,8,0,0,0,0,0,0,
	0,3,6,9,2,5,8,1,4,7,0,
	0,4,8,2,6,0,0,0,0,0,0,
	0,5,0,0,0,0,0,0,0,0,0,
	0,6,2,8,4,0,0,0,0,0,0,
	0,7,4,1,8,5,2,9,6,3,0,
	0,8,6,4,2,0,0,0,0,0,0,
	0,9,8,7,6,5,4,3,2,1,0
};
int q,n,m;
int op(int n,int m)
{
	int res=0;
	For(i,1,n) res+=biao[m][i];
	return res;
}
signed main()
{
	freopen("book.in","r",stdin);
	freopen("book.out","w",stdout);
	q=read();
	while(q--)
	{
		n=read(); m=read();
		n/=m;
		m%=10;
		if(m==1) printf("%lld\n",n/10*45+op(n%10,m));
		if(m==2) printf("%lld\n",n/5*20+op(n%5,m));
		if(m==3) printf("%lld\n",n/10*45+op(n%10,m));
		if(m==4) printf("%lld\n",n/5*20+op(n%5,m));
		if(m==5) printf("%lld\n",n/2*5+op(n%2,m));
		if(m==6) printf("%lld\n",n/5*20+op(n%5,m));
		if(m==7) printf("%lld\n",n/10*45+op(n%10,m));
		if(m==8) printf("%lld\n",n/5*20+op(n%5,m));
		if(m==9) printf("%lld\n",n/10*45+op(n%10,m));
		if(m==0) printf("%lld\n",0);
	}
	return 0;
}
```


---

## 作者：Kizuna_AI (赞：0)

[我的博客](https://jyeric-likecoding.netlify.com)

~~C题很简单，只要会打表，轻松就AC~~

貌似也不用打表也能过，但是我发现我已经打了一般，然后就继续打了下去。

### 阅读题目时：
阅读题目大意，可以发现暴力的一个一个去查看是否满足条件是会超时的，所以我们需要进行优化，才能AC。

### 大致思路：  
1. 首先我们发现一个规律，对于每个数字的倍数来说，每10的倍数，都是一样的（这个其实很好说明，例如对于 `3*3`和`3*13`来说，最后一位就是取决于个位数*个位数的）
2. 然后，既然有第一步的规律，我们就可以尝试吧整个表给打出来。分为a数组和b数组。a数组记录每一个数的末尾数字，b数组记录每一个数的总和。  
$\color{red}{Note:}$请注意b数组的形式，不能直接模2。因为有5的特例，对于5的倍数总数来说是25而不是45，且样例并未体现出该问题。 [你可以看看我的WA code](https://codeforces.com/contest/1213/submission/59736669)
3. 最后，根据题目要求查看进行一轮（10个数）有多少个并乘以对应的b数组数值、不满足则查看进行了几个，并一一相加。

### 代码：
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int q;
ll n,m;
ll a[11][11]={{0},
			  {1,2,3,4,5,6,7,8,9,0},
			  {2,4,6,8,0,2,4,6,8,0},
			  {3,6,9,2,5,8,1,4,7,0},
			  {4,8,2,6,0,4,8,2,6,0},
			  {5,0,5,0,5,0,5,0,5,0},
			  {6,2,8,4,0,6,2,8,4,0},
			  {7,4,1,8,5,2,9,6,3,0},
			  {8,6,4,2,0,8,6,4,2,0},
			  {9,8,7,6,5,4,3,2,1,0},
			 };
ll b[11]={0,45,40,45,40,25,40,45,40,45};
int main() {
	ios::sync_with_stdio(false);
	cin>>q;
	while(q--) {
		cin>>n>>m;
		ll c=(n%(m*10ll))/m,d=n/m/10,e=m%10,ans=0; //这里的c,d,e就是体现思路中的第三步了。其中d数组代表着进行了多少轮，e数组表示末尾数是多少，c数组代表着还有进行多少轮后还有多少零头
        //何为10ll? 10ll代表着10这个数不是int类型的，而是long long类型的
		for(int i=0;i<c;i++) {
			ans+=a[e][i];
		}
		ans+=d*(b[e]);
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：兮水XiShui丶 (赞：0)

显然可以发现,题目中要求的个位数字只受要除的数的个位的影响,所以我们在求出来了倍数的个数$num$时,可以发现,个位数字的出现是有周期的,而这个周期和周期中的数字是由要除的数字的个位决定的.而因为要除的数字的个位最多只有10个,所以我们可以先预处理出每个数字的周期以及他们的和,再对多出来的部分直接暴力就可以了.

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
 
int n,m;
int ned[10],idx[10];
int sum[10][10];
 
signed main(){
	
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0); 
	
	for(int i=1;i<=9;i++){
		int now=i;
		sum[i][++idx[i]]=i;
		now+=i;
		while(now!=i){
			if(now>=10)
				now-=10;
			sum[i][++idx[i]]=now; 
			now+=i;
		}
	}
	for(int i=1;i<=9;i++)
		for(int j=1;j<=idx[i];j++)
			ned[i]+=sum[i][j];
	int T;
	cin>>T;
	
	while(T--){
		int ans=0;
		cin>>n>>m;
		int numm=n/m;
		int tmp = m;
		tmp%=10;
		if(tmp==0||numm==0){
			cout<<"0"<<endl;
			continue;
		}
		int fir = numm/idx[tmp];
		ans+=fir*ned[tmp];
	//	cout<<fir<<" "<<tmp<<endl;
		int sos=0;
		for(int i=fir*idx[tmp]+1;i<=numm;i++)
			ans+=sum[tmp][i-fir*idx[tmp]];
		cout<<ans<<endl;
	}
 
 
	return 0;
} 
//
```

---

## 作者：B_Qu1e7 (赞：0)

稍微有点难度。

题意：求$\sum_{k=1}^{\left \lfloor \frac{n}{m} \right \rfloor}(km\ mod\ 10)$

蒟蒻啥都不会，只好“打表”$QAQ$

加的是个位数，可以发现，无论是$0-9$中的哪一个数，在至少10次之后结果都会循环。

由此可得一张表
```
   0 1 2 3 4 5 6 7 8 9
1  0 1 2 3 4 5 6 7 8 9
2  0 3 6 912 5 8111417
3  0 61218141016121824
4  0102020201020202030
5  0152025201520252035
6  0212233241526272829
7  0282634322028363442
8  0363238342036423844
9  0454045402540454045
```
最后答案$ans=\left \lfloor N/(M*10) \right \rfloor*a[0][M\%10]+a[(N\%(M*10))/M][M\%10]$
```cpp
#include<cctype>
#include<cstdio>
int Q,mod[10][10]={
	{0,45,40,45,40,25,40,45,40,45},
	{0,1,2,3,4,5,6,7,8,9},
	{0,3,6,9,12,5,8,11,14,17},
	{0,6,12,18,14,10,16,12,18,24},
	{0,10,20,20,20,10,20,20,20,30},
	{0,15,20,25,20,15,20,25,20,35},
	{0,21,22,33,24,15,26,27,28,39},
	{0,28,26,34,32,20,28,36,34,42},
	{0,36,32,38,34,20,36,42,38,44},
	{0,45,40,45,40,25,40,45,40,45},
};
long long N,M,ans;
template<class T>inline void read(T &m)
{
	m=0;
	char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))m=(m<<3)+(m<<1)+(c&15),c=getchar();
}
int main()
{
	read(Q);
	while(Q--)
	{
		read(N),read(M);
		ans=((long long)(N/(M*10)))*mod[0][M%10];
		N%=(M*10);
		if(N>=M)ans+=mod[N/M][M%10];
		printf("%lld\n",ans);
	}
}
```

---

