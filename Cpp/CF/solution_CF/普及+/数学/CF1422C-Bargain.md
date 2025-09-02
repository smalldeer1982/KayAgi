# Bargain

## 题目描述

Sometimes it is not easy to come to an agreement in a bargain. Right now Sasha and Vova can't come to an agreement: Sasha names a price as high as possible, then Vova wants to remove as many digits from the price as possible. In more details, Sasha names some integer price $ n $ , Vova removes a non-empty substring of (consecutive) digits from the price, the remaining digits close the gap, and the resulting integer is the price.

For example, is Sasha names $ 1213121 $ , Vova can remove the substring $ 1312 $ , and the result is $ 121 $ .

It is allowed for result to contain leading zeros. If Vova removes all digits, the price is considered to be $ 0 $ .

Sasha wants to come up with some constraints so that Vova can't just remove all digits, but he needs some arguments supporting the constraints. To start with, he wants to compute the sum of all possible resulting prices after Vova's move.

Help Sasha to compute this sum. Since the answer can be very large, print it modulo $ 10^9 + 7 $ .

## 说明/提示

Consider the first example.

Vova can choose to remove $ 1 $ , $ 0 $ , $ 7 $ , $ 10 $ , $ 07 $ , or $ 107 $ . The results are $ 07 $ , $ 17 $ , $ 10 $ , $ 7 $ , $ 1 $ , $ 0 $ . Their sum is $ 42 $ .

## 样例 #1

### 输入

```
107```

### 输出

```
42```

## 样例 #2

### 输入

```
100500100500```

### 输出

```
428101984```

# 题解

## 作者：FutaRimeWoawaSete (赞：6)

算是比较简单的 $C$ 了吧。      

首先我们很明显可以按位考虑，由于删除的数是连续的，所以如果当前这一位被删去了的话肯定就没贡献，所以分类讨论每一位：      

- 删去的数是前面的一段连续数      
- 删去的数是后面的一段连续数     
- 删去的数包含了当前位，此时没贡献        

我们首先看只删前面，此时我们发现不管前面怎么删，此时我们当前位的贡献是固定的，所以只要知道前面有多少种删法就可以了，这个很明显 $i \times (i - 1) / 2$ 。        

接着我们看只删后面，很类似前面，不过这里要考虑后面剩余位数对答案的影响，如果只剩一位就 $1$ 种情况，两位就 $2$ 种情况，把 $0$ 提到我们计算数里面就是 $1 , 20 , 300 ……$ 从后往前算的时候累加一下这玩意儿就好了。          

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int Len = 1e5 + 5;
const long long mod = 1e9 + 7;
char s[Len + 5];
long long ans,sum,p = 1;
int main()
{
	scanf("%s",s + 1);
	int lens = strlen(s + 1);
	for(int i = lens ; i >= 1 ; i --)
	{
		long long Now = 1LL * i * (i - 1) / 2;
		ans = (ans + p * (s[i] - '0') % mod * Now % mod) % mod;//只删前面 
		ans = (ans + sum * (s[i] - '0') % mod) % mod;//只删后面 
		sum = (sum + (lens - i + 1) * p % mod) % mod;
		p = p * 10 % mod;
	}
	printf("%lld\n",ans);
	return 0;	
}
```

---

## 作者：7KByte (赞：5)

算贡献。

为了清晰明了，我们将贡献分两次算。

第一遍。我们顺序枚举删除区间的左端点，然后计算左端点的左边部分的贡献。由于左端点个数为$N$，所以这里时间复杂度为$\rm O(N)$。

第二遍。我们倒叙枚举删除区间的右端点，然后计算右端点的右边部分的贡献。
由于右端点个数为$N$，所以这里时间复杂度也是$\rm O(N)$。

因为我们删除一个区间后，对答案的贡献为区间左端点的左边和区间右端点都右边。所以两遍计算可以不重不漏地统计所有情况。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define int long long 
#define N 100005
#define P 1000000007
using namespace std;
char s[N];int n,ans,c[N],d[N];
signed main(){
	scanf("%s",s+1);
	n=strlen(s+1);
	int sum=0;
	c[0]=d[0]=1;
	rep(i,1,N-5)c[i]=(c[i-1]*10+1)%P,d[i]=d[i-1]*10%P;
	rep(i,1,n-1){
		sum=(sum*10+s[i]-'0')%P;
		ans+=sum*c[n-i-1]%P;
	}
	sum=0;
	pre(i,n,2){
		sum=(sum+(s[i]-'0')*d[n-i])%P;
		ans+=sum*(i-1)%P;
	}
	printf("%lld\n",ans%P);
	return 0;
}
```

---

## 作者：Werner_Yin (赞：1)

[更好的阅读体验](https://www.cnblogs.com/werner-yin/p/-solution-CF1422-C.html)

## 题意

给你一个数 $a$(长度为 $|a|$ ) ,你可以从这个数中选择一段子串并删掉，两端再拼成一个新数，问所有可能的新数的和$\mod 10^9+7$

$\texttt{Data Range:}$

$|a| <= 10^5$ 

## 变量声明

$a = a_1a_2a_3\dots a_n$ 

$n$  ： $|a|$

## 思路

> $|a| <= 10^5$ 

看一下范围，~~暴力是不可能的了~~

那就要分别考虑每个数位对答案的贡献。

假设当前数位为第 $k$ 位，

那么删去的串一定在第 $k$ 位前或者后面。

#### 在第  $k$  位前

产生的新数中，$a_k$ 后面一定有 $n-k$ 位，对答案的贡献为 $10^{n-k} * a_k$ 

这种数有 $\dbinom{k}{2}$ 个

总贡献为 $\dbinom {k}{2} * 10^{n-k} * a_k$ 

#### 在第 $k$ 位后

产生的新数中，$a_k$ 后面的位数与在后面删去的个数有关．

若在后面删去 $x(x \leq n-k)$ 位， 这种数对答案的贡献为 $10^{n-k-x} * a_k$ ，

共有 $n-k-x+1$ 种。

$\therefore$ 对答案的贡献为 $10^{n-k-x} * a_k *(n-k-x+1)$ 

**这种情况总的对答案贡献为**

$\sum\limits_{x=1}^{n-k} 10^{n-k-x} * a_k *(n-k-x+1)$

直接这么算，肯定要超时了，我们注意到：

$10^{n-k-x}$ 

$n-k-x+1$

也就是说，对于每项，都可以表示为 $10^t * (t+1) * a_k$ 。

而只有 $a_k$ 是不确定的，

因此，我们维护一个数组，只记录各项 $a_k$ 的和，到时候再乘上 $10^{n-k-x} *(n-k-x+1)$ 就可以了。

又因为 $x \in [1,n-k]$ ,每次处理 $a_k$ 都是一次区间加，而最后计算结果时是一位一位的求值，维护一个差分数组就行了。

## 代码 

头文件、快读等自由脑补

```cpp
#define ll long long

using namespace std;

const int MAXN = 1e5+10;
const int mod = 1e9+7;

int n = 0;
ll a[MAXN],c[MAXN],p10[MAXN],ans = 0;

int main (){
    while(scanf("%1lld",&a[n+1]) == 1) n++;
    p10[0] = 1;
    for(int i = 1;i <= n;i++) p10[i] = p10[i-1] * 10 % mod;
    //p10[i] 10^i
    for(ll i = 1;i <= n;i++){
		ans += (i*(i-1)/2)%mod * p10[n-i] %mod* a[i]%mod;
		if(ans >= mod) ans %= mod;
        //在第i位前
		c[n-i+1] = (c[n-i+1]-a[i])%mod;
		c[1] = (c[1]+a[i])%mod;
        //根据推导，对数组进行区间加（实际上是对差分数组修改）
    }
    ll te = 0;
    for(int i = 1;i <= n;i++){
		te = (te+c[i])%mod; //还原数组
		ans = (ans + te * p10[i-1] % mod * i%mod)%mod; //计算第二部分答案
    }
    printf("%lld",ans%mod);
    return 0;
}

```



---

## 作者：sodak (赞：0)

## 分析

~~根据题意~~，手玩样例，会发现发现，每个数对答案会造成两种贡献，一种是删去这个数后面（低位）的数，结果对答案造成的贡献，一种是删去这个数前面（高位）的数，结果对答案造成的贡献，如果删去的数包括改位，则不造成贡献，不用考虑，分情况讨论一下

* 删去这个数前面的数，对这个数造成的贡献没有影响，所以，第i未所造成的贡献就是$(C_{n-i}^{2}+n-i)*10^i$,模拟一下就能出来，应该挺好想的

* 删去这个数后面的数，易发现，每一位上的数的贡献次数，取决于这是第几位，拿$1234$来解释一下，个位后面没有数，所以$4$的贡献次数为$0$,十位后面有一个数，所以只能删一次，所以$3$的贡献为$1$,百位后面有两个数，可以考虑删一个或者删两个，删一个的贡献为$2*10$，删两个的贡献为$1$,所以$2$的贡献为$21$,千位后面有三个数，可以考虑删去一个，两个或者三个，方案数分别为$3$，$2$，$1$，所以贡献为$321$，处理到这里就很容易发现答案了，用数组记录一下，递退一下就行了，因为数据范围很小，随便搞搞就行了

## 代码
```cpp

#include<bits/stdc++.h>
#define gc getchar()
#define ll long long
#define int long long
#define getch while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=gc;}
#define getnu while(ch>='0'&&ch<='9'){s=(s<<1)+(s<<3)+ch-'0';ch=gc;}
using namespace std;
inline int read(){int s=0,f=1;char ch=gc;getch;getnu;return s*f;}
const int maxn=1e5+10,mod=1e9+7;
char s[maxn];
ll  g[maxn],a[maxn],sum[maxn];
ll qpow(ll a,ll b,ll res=1){
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod;b>>=1;
	}
	return res;
}
signed main(){
	scanf("%s",s+1);
	int n=strlen(s+1);
	for(int i=n;i>=1;i--)a[n-i+1]=s[i]-'0';
	int base=1;
	for(int i=2;i<=n;i++){
		g[i]=g[i-1];
		g[i]=(g[i]+base*(i-1)%mod)%mod;
		base=base*10%mod;
	}
	for(int i=1;i<=n;i++)sum[i]=(sum[i-1]+i)%mod;
	ll ans=0;
	for(int i=1;i<=n;i++){
		ans=(ans+a[i]*g[i]%mod)%mod;
		ans=(ans+a[i]*qpow(10,i-1)%mod*sum[n-i]%mod)%mod;
	}
	printf("%lld\n",ans);
}


```



---

## 作者：jerry3128 (赞：0)

对于每个数我们计算它在各位对答案的贡献 

先算它在原数中本来的位置，即删除区间在他左边的，排列一下就搞出来 

后算它被减掉位数后的。 
因为删除的子串是连续的，所以一个点的贡献被改变只会是它右边的子串被删除。 
设上一位的贡献为x次乘上一位的权值，因为这一位可以比上一位多删一个数，即上一位。
所以这一位的贡献为 $x +i \times 10^{i-1}$
```
#include<bits/stdc++.h>
using namespace std;
int p1=1000000,p2=0;
char buf[1000005],wb[1000005];
//int gc() {
//	if(p1>=1000000)fread(buf,1,1000000,stdin),p1=0;
//	return buf[p1++];
//}
#define gc getchar
long long getint() {
	long long ret=0,flag=1;
	char c=gc();
	while(c<'0'||c>'9') {
		if(c=='-')flag=-1;
		c=gc();
	}
	while(c<='9'&&c>='0') {
		ret=(ret<<3)+(ret<<1)+c-'0';
		c=gc();
	}
	return ret*flag;
}
void pc(char x) {
	if(p2>=1000000)fwrite(wb,1,1000000,stdout),p2=0;
	wb[p2++]=x;
}
void wrt(long long x) {
	if(x<0)pc('-'),x=-x;
	int c[24]= {0};
	if(!x)return pc('0'),void();
	while(x)c[++c[0]]=x%10,x/=10;
	while(c[0])pc(c[c[0]--]+'0');
}
#define mod (long long)(1e9+7)
char c[100005];
long long ans=0,sum=0;
long long ksm(long long a,long long b) {
	long long ret=1;
	while(b) {
		if(b&1)ret=ret*a%int(1e9+7);
		a=a*a%int(1e9+7);
		b>>=1;
	}
	return ret;
}
int main() {
	scanf("%s",c+1);
	int len=strlen(c+1);
	long long data=0;
	for(int i=1; i<=len; i++) {
		int val=(c[len-i+1]-48);
		ans=(ans+val*ksm(10,i-1)%mod*(1ll*(len-i)*(len-i-1)/2%mod+len-i)%mod)%mod;
//		cout<<i<<":"<<0<<" "<<val*ksm(10,i-1)%mod*((len-i)*(len-i)/2%mod+len-i)%mod<<endl;
//		long long nt=0;
//		for(int j=1; j<i; j++) {
//			ans=(ans+val*ksm(10,i-j-1)%mod*(i-j)%mod)%mod;
////			cout<<i<<":"<<j<<" "<<val*ksm(10,i-j-1)%mod*(i-j)%mod<<endl;
//			nt=(nt+ksm(10,i-j-1)%mod*(i-j)%mod)%mod;
//		}
//		cout<<"I:"<<i<<":"<<nt<<" "<<data<<endl;
		ans=(ans+val*data%mod)%mod;
		data=(data+i*ksm(10,i-1)%mod)%mod;
	}
	wrt(ans),pc('\n');
	fwrite(wb,1,p2,stdout);
	return 0;
}
```

---

