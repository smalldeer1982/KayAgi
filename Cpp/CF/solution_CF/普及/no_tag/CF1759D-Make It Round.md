# Make It Round

## 题目描述

给定 $n$ 和 $m$, 我们可以把 $n$ 变为 $n\cdot k(1\leq k\leq m,k∈N^{*})$, 请输出末尾 $0$ 的个数最多的 $n\cdot k$。  
- 例如, $481000$ 比 $1000010$ 末尾 $0$ 的个数更多。
- 如果有多个末尾 $0$ 个数最多的 $n\cdot k$, 则输出其中最大的一个。  
- 如果不存在末尾 $0$ 个数更多的 $n\cdot k$, 则输出 $n\cdot m$。

## 样例 #1

### 输入

```
10
6 11
5 43
13 5
4 16
10050 12345
2 6
4 30
25 10
2 81
1 7```

### 输出

```
60
200
65
60
120600000
10
100
200
100
7```

# 题解

## 作者：linyihdfj (赞：10)

## CF1759D Make It Round
想要更优质的阅读体验，就来[这里](https://www.cnblogs.com/linyihdfj/p/16893607.html)吧。
### 题目分析：
我们知道 $10 = 2\times 5$，所以有多少个 $0$ 就相当于有多少个 $2 \times 5$ 也就是 $2$ 和 $5$ 的指数的 $\min$。

那么就考虑直接枚举有多少个 $2 \times 5$，然后和原来就有的抵消一下，假设剩下的乘积为 $x$，那么只要 $x \le m$ 那么就意味着是合法的。

但是因为题目要求在 $0$ 最多的情况下最大，也就是找到 $[1,m]$ 中 $x$ 的最大的倍数，也就是 $\lfloor \dfrac{m}{x} \rfloor \times x$，用这个数乘以原数就是答案了。
### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	int t;
	scanf("%lld",&t);
	while(t--){
		int n,m;scanf("%lld%lld",&n,&m);
		for(int i=18; i>=0; i--){
			int tmp = n;
			int tw = i,fi = i;
			while(tmp % 2 == 0 && tmp)	tw--,tmp /= 2;
			while(tmp % 5 == 0 && tmp)	fi--,tmp /= 5;
			int ans = 1;
			while(tw > 0)	ans = ans * 2,tw--;
			while(fi > 0)	ans = ans * 5,fi--;
			if(ans <= m){
				int p = m / ans * ans;
				printf("%lld\n",p * n);
				break;
			}
		}
	}
	return 0;
}
```

---

## 作者：wuyonghuming (赞：6)

### 分析：
一个数末尾出现零，取决于因子 $10$ 的个数，而因子 $10$ 的个数，取决于它有的因子 $2$ 和因子 $5$ 的个数，因为 $5×2=10$ ，所以 $0$ 的个数为因子 $2$ 和因子 $5$ 数量**较少**的个数。

想要让一个数的因子 $10$ 更多，有三种方法。**且每一种方法能且仅能为它增多一个零**。

1.直接将这个数乘 $10$。

2.如果这个数还剩下因子 $5$ ，乘 $2$ 给它凑一个 $10$。

3.如果这个数还剩下因子 $2$ ，乘 $5$ 给它凑一个 $10$。

这三种方法肯定优先采用第二种或者第三种，因为乘的数较小，增长的速度就慢，就可以多操作。
### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
unsigned long long in(){unsigned long long a=0,f=1;char b=getchar();while(b<'0'||b>'9'){if(b=='-')f=-1;b=getchar();}while(b>=48&&b<=57){a=a*10+b-'0';b=getchar();}return a*f;}
void out(unsigned long long a){if(a<0){putchar('-');a*=-1;}if(a>9)out(a/10);putchar(a%10+48);}
int main()
{
	int t=in();
	while(t--)
	{
		unsigned long long n=in(),m=in(),five=0,two=0,x=n,ans=1;
		while(x%10==0)//去掉10
			x/=10;
		while(x%2==0)//统计多余的2
		{
			x/=2;
			two++;
		}
		while(x%5==0)//统计多余的5
		{
			x/=5;
			five++;
		}
		while(five||two)
		{
			if(five>0)//剩下5，凑一个2
			{
				five--;
				if(ans*2<=m)
					ans*=2;
				else
					break;
			}
			else
			{
				two--;
				if(ans*5<=m)//剩下2，凑一个5
					ans*=5;
				else
					break;
			}
		}
		ans*=n;//计算当前数的大小
		while(ans*10<=n*m)//能再乘几个十就乘几个
			ans*=10;
		out(n*m/ans*ans);//求范围内最大能整除ans的
		puts("");
	}
	return 0; 
}
```


---

## 作者：Nanani (赞：4)

## 考虑贪心
根据题意，我们想要 $k$ 不小于 $m$ 的情况下 $n\times k$ 末尾 $0$ 尽可能多且数字尽可能大的数。

把数字 $n$ 因式分解，看能拆出来多少个 $10$ ，$2$ 和 $5$ 。$10$ 不用动，给 $5$ 凑 $2$，给 $2$ 凑 $5$。为了让末尾的 $0$ 尽可能多，所以我们用 $2$ 凑，即在数字尽可能小的情况下使末尾 $0$ 尽可能多。考虑完凑 $0$ 再考虑还能不能使数更大，即乘一个尽可能大的常数。

代码如下

------------

```cpp
//by 72
#include<bits/stdc++.h>
#define N 2000005
#define int long long
using namespace std;
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')x=10*x+c-'0',c=getchar();
	return x*f;
}
int n,t,m;
signed main()
{
	t=read();
	for(;t;t--)
	{
		n=read(),m=read();
		int x=n,y=m,c10=0,c5=0,c2=0,bs=1,k=1;
		while(!(x%10))x/=10,c10++;
		while(!(x%2))x/=2,c2++;
		while(!(x%5))x/=5,c5++;//分别拆出10 2 5
		while(bs*2<=m&&c5>0){bs*=2;c5--;}
		while(bs*5<=m&&c2>0){bs*=5;c2--;}
		while(bs*10<=m)bs*=10;//先考虑还能不能补0
	   for(int i=2;;i++)if(bs*i>m){
         bs*=(i-1);break;//还能乘一个常数就继续乘
      }
		cout<<bs*n<<"\n";
	}
	return 0; 
}
//以上 
//小q好困 QAQ 

```


---

## 作者：honglan0301 (赞：2)

## 题意简述
给定正整数 $n,m$, 求一个正整数 $k$ 满足 $1\leq k \leq m$, 使得 $n\cdot k$ 末尾 $0$ 的个数最多，在此条件下再让 $n\cdot k$ 最大，输出这个 $n\cdot k$。

## 题目分析
显然，记一个数含质因子 $2$ 的个数为 $a$, 含质因子 $5$ 的个数为 $b$, 那么它末尾 $0$ 的个数就是 $\min(a,b)$。于是我们让 $k$ 从 $1$ 开始，每次乘以 $n$ 中较少的那个质因子，直到 $k>m$ 或 $n\cdot k$ 含质因子 $2$ 与 $5$ 的个数相等。之后再让 $k$ 不断乘以 $10$, 直到 $k>m$ 就能得到末尾 $0$ 个数最多的 $n\cdot k$。  

因为题目还要求在此基础上 $n\cdot k$ 最大，那么让 $k$ 再乘以 $\lfloor {m/k} \rfloor $ 就好了。  

## 代码
（记得开 long long)
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
long long t,n,m,k,sum2,sum5;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		sum2=0;
		sum5=0;
		k=1;
		for(int nnow=n;nnow%2==0;nnow/=2)//求n中质因子2的数量 
		{
			sum2++;
		}
		for(int nnow=n;nnow%5==0;nnow/=5)//5的数量 
		{
			sum5++;
		}
		while(sum2<sum5&&k*2<=m)
		{
			k*=2;
			sum2++;
		}
		while(sum5<sum2&&k*5<=m)
		{
			k*=5;
			sum5++;
		}
		while(k*10<=m)//找到要求的k 
		{
			k*=10;
		}
		k*=(m/k);
		cout<<n*k<<endl;
	}
}
```


---

## 作者：隐仞Mrsu (赞：0)

# 分析一下

~~补题的时候，本想用分类讨论写的，结果把自己绕晕了，浪费许多时间。~~

所以，让我们一起愉快地分析一下枚举法。

考虑到后缀零可以由 $2$ 乘上 $5$ 得到。

因此，令从 $n$ 中提取的 $2$ 因子有 $p_0$ 个，提取的 $5$ 因子有 $q_0$ 个；从 $k$ 中提取的 $2$ 因子有 $p$ 个，提取的 $5$ 因子有 $q$ 个。

题目要我们选一个最佳的 $k$，使得 $\min\{p_0+p,q_0+q\}$ 最大化。

由于 $n$ 给定，因此 $p_0,q_0$ 已知，所以我们只需从 $1$ 到 $m$ 中枚举 $k$，从而选出最佳的 $k$。但如果一个一个地枚举的话，会超时。

考虑到对结果有影响的 $k$ 应该是 $2$ 或者 $5$ 的倍数。因此，我们考虑枚举 $k$ 所含的因子 $2$ 与 $5$ 的个数。

由于 $2^{30}>10^{9}$ 且 $5^{13}>10^{9}$，所以我们只需从 $0$ 到 $30$ 枚举因子 $2$ 的个数，从 $0$ 到 $13$ 枚举因子 $5$ 的个数即可。

又因为两数能得到相同个数后缀零时，题目要求取数值本身更大的数。所以我们应该先把当前枚举到的数再乘上一个 $t$，使数值在 $m$ 以内最大化，再进行判断。

# 代码
```cpp
#include<bits/stdc++.h>
#define LL long long 
using namespace std;
LL _,d2[61],d5[61],l2,l5,a,b,T;
LL mx(LL x,LL y){
	//对比x和y哪个更优
	LL X=x*a,Y=y*a,nx=0,ny=0;
	while(X%10==0)X/=10,nx++;
	while(Y%10==0)Y/=10,ny++;
	if(nx==ny){
		if(x>y)return x;
		else return y;
	}
	if(nx>ny)return x;
	else return y;
}
void work(){
	cin>>a>>b;
	LL res=b;
	for(LL i=0;i<=l2;i++){
		for(LL j=0;j<=l5;j++){
			LL d=d2[i]*d5[j]; 
			if(d>b)break;
			LL t=b/d;
			d*=t;//使当前数值在范围内最大化
			res=mx(res,d);//更新答案
		}
	}
	cout<<a*res<<'\n';
}
int main(){
	ios::sync_with_stdio(false);
	cin>>_;
    //预处理
	LL num=2;
	d2[0]=d5[0]=1;
	for(;num<=1e9;num*=2){
		l2++;
		d2[l2]=num;
	}
	num=5;
	for(;num<=1e9;num*=5){
		l5++;
		d5[l5]=num;
	}
	while(_--){
		work();
	}
} 
```


---

## 作者：RoyWu1207 (赞：0)

~~题意很简单，相信大家都懂了。~~

要使 $n \cdot k$ 末尾有尽可能多的零，也就是说要有更多的因子 $10$。（即尽可能多的因子 $2$ 和 $5$）

$n$ 是给定的，先求 $n$ 的质因子个数。

接下来进行分析。

若 $n$ 的质因子 $2$ 个数较多，则要从 $m$ 中取更多的 $5$，反之亦然。

最后再取因子 $10$。

取完后剩下的数可以让这个数更大（因为 $2$ 和 $5$ 在此前的操作中已经取尽）。

判断能否有更多的零，可以通过额外变量计算零的个数进行比较。

具体见 AC Code：

```
#include <bits/stdc++.h>
#define int long long

using namespace std;

signed main() {
    int t; cin >> t;
    while (t--) {
        int n, m, nsum2 = 0, nsum5 = 0, zw, s; cin >> n >> m;
        int tmpn = n;
        while (tmpn % 2 == 0)
            tmpn /= 2, nsum2++;
        while (tmpn % 5 == 0)
            tmpn /= 5, nsum5++;
        s = tmpn;
        tmpn = m;
        zw = min(nsum2, nsum5);
        if (nsum2 > nsum5) {
            int sum5 = 0;
            while (tmpn > 5 && nsum5 + sum5 < nsum2)
                tmpn /= 5, sum5++;
            while (tmpn > 10)
                tmpn /= 10, nsum2++, nsum5++;
            nsum5 += sum5;
        } else if (nsum2 < nsum5) {
            int sum2 = 0;
            while (tmpn > 2 && nsum2 + sum2 < nsum5)
                tmpn /= 2, sum2++;
            while (tmpn > 10)
                tmpn /= 10, nsum2++, nsum5++;
            nsum2 += sum2;
        } else
            while (tmpn > 10)
                tmpn /= 10, nsum2++, nsum5++;
        if (zw >= min(nsum2, nsum5))
            cout << n * m << endl;
        else    
            cout << s * (int)pow(2, nsum2) * (int)pow(5, nsum5) * tmpn << endl;
    } return 0;
}
```


~~代码可能很烂~~，请大神指教！

---

## 作者：许多 (赞：0)

题意简述：

给定 $n$ 和 $m$ 两个数，找到一个数 k 满足在保证 $n \times k$ 结尾 $0$ 的个数最多的前提下尽可能的大，且 $1 \le k \le m$，输出 $n \times k$ 的值。

如果 $n \times 2$ 在结尾能多一个零，且当前乘的总数小于 $m$，则乘一个 $2$。

同理。如果 $n \times 5$ 在结尾能多一个零，且当前乘的总数小于 $m$，则乘一个 $2$。

然后我们尽可能多的乘 $100$，这样我们便构建出了结尾 $0$ 的个数最多。

最后，我们再乘上 $m/$ 刚刚我们乘的总数，即是答案。

光看文字可能有点难懂，我们来到代码阶段。

# 代码

```cpp
#include<bits/stdc++.h>
#include<cstdio>
#define LL long long
inline LL read(){
    LL x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*f;
}
LL j0(LL now){//计算now后面0的个数
    int i=0;
    while(now%10==0)now/=10,i++;
    return i;
}
using namespace std;
LL t,n,m;
int main(){
    t=read();
    while(t--){
        int n2=1,M;
        n=read();m=read();
        M=j0(n);
        while(j0(n*(1<<n2))>M&&(1<<n2)<=m)M=j0(n*(1<<n2)),n2++;
        n2--;
        n*=1<<n2;
        m/=1<<n2;
        n2=1;
        while(j0(n*(long long)pow(5,n2))>M&&(long long)pow(5,n2)<=m)M=j0(n*(long long)pow(5,n2)),n2++;
        n2--;
        n*=(long long)pow(5,n2);
        m/=(long long)pow(5,n2);
        while(m>=10)n*=10,m/=10;
        n*=m;
        printf("%lld\n",n);
    }
    return 0;
}
```

~~鄙人不会快速幂。~~

---

## 作者：云裳 (赞：0)

**思路**

因为 $10=2\times5$，

所以要使得 $n\cdot k $ 的末尾 $0$ 的个数最多，就是要使得 $n\cdot k$ 中 $2$ 的因数的个数和 $5$ 的因数的个数中**较少的那一项尽可能多**。

然后我们设 $k$ 一开始等于 $1$，而我们的程序就是来求 $k$ 的，最终的答案就是 $n\cdot k $。

因此我们有了以下步骤：

1. 求出 $n$ 中 $2$ 和 $5$ 的因数个数。
2. 将 $k$ 不断乘上因数 $2$ 和 因数 $5$ 中个数较小的那一项（如果 $k$ 没有超过 $m$ 的话），使得因数 $2$ 和 因数 $5$ 的个数一样。
3. 将 $k$ 不断乘上 $10$（如果 $k$ 没有超过 $m$ 的话）。
4. 用**二分**求出 $k$ 再不超过 $m$ 的情况下最多还可以再乘上 $x$。


------------

那为什么是第二步在前，第三步在后呢？

因为第二步是用了 $\frac{x}{2} $ 或 $\frac{x}{5}$ 的代价，受益为末尾增加一个 $0$ 。

而第三步是用了 $\frac{x}{10}$ 的代价，受益也为末尾增加一个 $0$ 。

因此第二步无论如何都不会劣与第三步，所以要先执行第二步。



------------
**代码**

```cpp
void solve() {
  ll t;
  cin >> t;
  while (t--) {
    ll n, m;
    ll two = 0, five = 0, ans = 1;
    // two 为 n 中因数2的个数，five 为 n 中因数5的个数，ans 就是题目中所求的 k
    cin >> n >> m;
    ll k = n;
    while (k % 2 == 0)
      k /= 2, two++;//求因数2的个数
    while (k % 5 == 0)
      k /= 5, five++;//求因数5的个数
    while (ans * 5 <= m && five < two)
      ans *= 5, five++;//是因数5的个数与因数2的个数相匹配
    while (ans * 2 <= m && two < five)
      ans *= 2, two++;//同上
    while (ans * 10 <= m)
      ans *= 10;
    ll l = 1, r = m, x = 1;//最少乘上1，最多乘上m（当末尾0的个数不能再增加时就会乘上m）
    while (l <= r) {
      ll mid = (l + r) / 2;
      if (ans * mid <= m)
        l = mid + 1, x = mid;
      else
        r = mid - 1;
    }
    ans *= x;
    cout << n * ans << "\n";
  }
}
```



---

## 作者：yeshubo_qwq (赞：0)

## Solution

一个数的末尾出现 $0$，只跟因数 $2,5$ 的个数有关。

$m\le 10^9$ 而 $2^{30}>10^9,5^{13}>10^9$，因此，我们枚举乘的倍数中分别含有几个因子 $2,5$ 即可，注意要最大末尾 $0$ 的数量，其次再是最大化结果的值。

## Code

赛时写的，非常丑。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m,x,y,s2,s5,s2_,s5_,add_s2,add_s5,ls;
int qpow(int x,int y){
	int res=1;
	while (y){
		if (y&1) res=res*x;
		x=x*x,y>>=1;
	}
	return res;
}
void go(){
	int mx;
    cin>>n>>m,mx=0; 
    x=n,s2=0,s5=0;
    while (x%2==0) x/=2,s2++;
    while (x%5==0) x/=5,s5++;
    int bc1=s2,bc2=s5;
    int mx_rnd=min(s2,s5);
    for (int i=0,ss=1;ss<=m;i++,ss*=2)
    	for (int j=0,sss=1;ss*sss<=m;j++,sss*=5){
    		s2=bc1,s5=bc2;
    		s2_=i,s5_=j;
//    		cout<<i<<' '<<j<<' '<<s2<<' '<<s5<<'\n';
    		x=m/(ss*sss);
		    ls=x;
		    add_s2=0,add_s5=0;
		    if (s2<s5){
		    	x=s5-s2;
		    	y=min(s2_,x);
		    	add_s2+=y;
		    	s2_-=y;
			}
			else if (s2>s5){
				x=s2-s5;
		    	y=min(s5_,x);
		    	add_s5+=y;
		    	s5_-=y;
			}
			x=min(s2_,s5_);
			add_s2+=x,add_s5+=x;
			s2_-=x,s5_-=x;
			ls*=qpow(2,s2_)*qpow(5,s5_);
			int qwq=n*qpow(2,add_s2)*qpow(5,add_s5)*ls,rnd=min(add_s2+s2,add_s5+s5);
			if (rnd>mx_rnd) mx_rnd=rnd,mx=qwq;
			else if (rnd==mx_rnd) mx=max(mx,qwq);
//			mx=max(mx,n*qpow(2,add_s2)*qpow(5,add_s5)*ls);
		}
	if (!mx) mx=n*m;
	cout<<mx<<'\n';
}
signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int tests=1;
    cin>>tests;
    while (tests--) go();
    return 0;
}
```


---

## 作者：smallpeter (赞：0)

一道有趣的~~简单~~数论题。

# 题目大意

有 $t(t\le10^4)$ 组询问，每组询问两个正整数 $n,m(n,m\le10^9)$。现在你可以选择一个数 $k(1\le k\le m)$，使得 $k\times n$ 的权值最大，如果有多个数权值相等，输出最大的那个。一个数的权值定义为其后缀连续 0 的个数。

# 解题思路

我们设 $n=2^{p_1}\times 5^{p_2}\times x_1$，$k=2^{p_3}\times 5^{p_4}\times x_2$，其中 $x_1,x_2$ 不是 2 或 5 的倍数。不难发现一个数的权值只跟质因数 2、5 有几个相关。此时 $n\times k$ 的权值为 $\min(p_1+p_3,p_2+p_4)$。由于 $n$ 是确定的，那么现在就应该确定 $k$ 怎么选，使得其权值最大。

## $p_1\ge p_2$

此时 $n$ 中质因数 2 的个数比 5 多。那么我们在这个基础上添加质因数 2 的数量也不会对权值造成影响。我们先添加质因数 5 的个数，如果将质因数 5 提升到与 2 相同的个数需要的数量，$m$ 不足以提供，那么就能提供多少是多少。否则我们先让质因数 5 的个数配到与 2 相等，再同时给 2 和 5 提供。还是那个道理，如果只提供 2 或者 5，那么多于出来的 2 或 5 不会对权值造成影响，不如把多出来的部分同时提供给 2 和 5（提供到无法再同时给的时候就另外说）。

## $p_1< p_2$

此时 $n$ 中质因数 5 的个数比 2 多。那么我们在这个基础上添加质因数 5 的数量也不会对权值造成影响。我们先添加质因数 2 的个数，如果将质因数 2 提升到与 5 相同的个数需要的数量，$m$ 不足以提供，那么就能提供多少是多少。否则我们先让质因数 2 的个数配到与 5 相等，再同时给 2 和 5 提供。剩余部分跟上面的情况一样，就不再重复。

记得提供完之后判断是否还能进一步提升值的大小。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define LL long long

LL t,n,m;

LL answ(LL w){//计算w只保留第一位，其他位都变成0的值
	LL sum=0,s=1;
	for(;s*10<=w;) s*=10;
	LL xx=w/s;
	return xx*s;
}

int main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld%lld",&n,&m);
		LL sum1=0,sum2=0;//sum1求的是n中质因数2的个数，sum2求的是n中质因数5的个数
		LL nn=n,mm=n;
		while(nn%2==0&&nn>=1){
			sum1++;
			nn/=2;
		}
		while(mm%5==0&&mm>=1){
			sum2++;
			mm/=5;
		}
		LL sum3,i;
		if(sum1<sum2){
			for(sum3=1,i=0;sum3*2<=m&&i<sum2-sum1;i++) sum3*=2;
			if(i==sum2-sum1){//足够提供
				m/=sum3;
				printf("%lld\n",n*sum3*answ(m));
			}
			else{//不足以提供
				printf("%lld\n",sum3*n);
			}
		}
		else{
			for(sum3=1,i=0;sum3*5<=m&&i<sum1-sum2;i++) sum3*=5;
			if(i==sum1-sum2){//足以提供
				m/=sum3;
				printf("%lld\n",n*sum3*answ(m));
			}
			else{//不足以提供
				for(LL ii=4;ii>=2;ii--){
					if(ii*sum3<=m){//仍有剩余
						sum3*=ii;
						break;
					}
				}
				printf("%lld\n",sum3*n);
			}
		}
	}
}
```

---

