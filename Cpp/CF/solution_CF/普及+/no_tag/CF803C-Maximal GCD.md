# Maximal GCD

## 题目描述

You are given positive integer number $ n $ . You should create such strictly increasing sequence of $ k $ positive numbers $ a_{1},a_{2},...,a_{k} $ , that their sum is equal to $ n $ and greatest common divisor is maximal.

Greatest common divisor of sequence is maximum of such numbers that every element of sequence is divisible by them.

If there is no possible sequence then output -1.

## 样例 #1

### 输入

```
6 3
```

### 输出

```
1 2 3
```

## 样例 #2

### 输入

```
8 2
```

### 输出

```
2 6
```

## 样例 #3

### 输入

```
5 3
```

### 输出

```
-1
```

# 题解

## 作者：dz_ice (赞：7)

读完题后我们可以发现，只有当$n$能够整除序列的最大公约数$x$时，这个c长度为$k$序列才是可以被构造出来的

不过这显然不够，还要满足一个条件$n>=(x+k*x)*k/2$（高斯求和的公式），这是为什么呢？

首先假设$k=4$,当$x=3$时，我们应该尽量让序列所有数的和最小，因为序列中的数互不相同并且严格递增，那么就构造出3 6 9 12这样的一个序列，序列的和为30，那么此时如果$n=15$，显然是构造不出的，而如果$n=33$，序列可以是3 6 9 15

那么我们就可以解决这个问题，从大到小枚举$n$的因子，如果满足$n>=(x+k*x)*k/2$，就可以直接输出答案，除了最后一个数，第$i$个位置就输出$i*x$,最后一个位置就输出$n$减去前面的数的和，这样的序列一定是合法的

但是还要注意一个问题$(x+k*x)*k/2$是有可能超过long long的范围的，所以在判断的时候我们转换一下不等式，变成下面的形式
```
if((2*n)/k>=x+k*x)
```
考试的时候就是因为这个调了好久QWQ

接下来上完整代码

```
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;
long long n,k,sqr,sum,sum1,sum2,yin[50003];
int main()
{
	cin>>n>>k;
	sqr=sqrt(n);
	if((2*n)/k<1+k)
	{
		cout<<-1;
		return 0;
	}  //要特判，不然会tle 
	for(long long i=1; i<=sqr; i++)
		if(n%i==0)
		{
			sum1++,yin[sum1]=i;
			if(n/i!=i)
				sum1++,yin[sum1]=n/i;
		} //先预处理n的所有因子
	sort(yin+1,yin+sum1+1);
	for(long long i=sum1; i>=1; i--)
		if((2*n)/k>=yin[i]+k*yin[i])  //要转换不等式！不然有大问题
		{
			for(long long j=1; j<=k; j++)
				if(j!=k)
				{
					cout<<j*yin[i]<<" ";
					sum+=j*yin[i];
				}
				else
					cout<<n-sum;
			return 0;
		}
	cout<<-1;
	return 0;
}
```


---

## 作者：Jμdge (赞：2)

一眼题...


跟你说我怎么 wa 的那一发，咱手抽把 % 打成了 & 【shit

然后讲讲这题怎么思考


首先把 n 分成 k 个数，并且 k 个数公约数为 d 时，显然 n 是可以整除 d 的，那么我们可以考虑 $O(\sqrt n)$ 枚举 n 的约数来作为 k 个数的 d，然后取最大的当答案，至于输出的时候则是前面 $k-1$ 个为 $d,2d,3d,...,(k-1)d$ ，最后一个用 n 减去前面的数就可以得到了

然后考虑无解的情况： 我们可以拿最小正整数 1 来考虑，如果 k 个数的公约数是最小的 1 ，那么这 k 个数的和最小是 $k*(k+1)\over 2$ ，那么我们用这个数和 n 比大小就可以判无解了，但要注意的爆精度这个问题，我们可通过移项把乘法改成除法...

另外当枚举到一个数时我们要判这个数能否当 d ，判断的方法也就是把 n 除去 d 之后和 $k*(k+1)\over 2$ 比大小...

于是乎这道题除了我的智商以外没什么坑 0...0

# code

```
//by Judge
#include<bits/stdc++.h>
#define fp(i,a,b) for(register int i=(a),I=(b)+1;i<I;++i)
#define ll long long
using namespace std;
char sr[1<<21],z[20];int CCF=-1,Z;
inline void cmax(ll& x,ll y){if(x<y)x=y;}
inline void Ot(){fwrite(sr,1,CCF+1,stdout),CCF=-1;}
inline void print(ll x,char chr=' '){
	if(CCF>1<<20)Ot();if(x<0)sr[++CCF]=45,x=-x;
	while(z[++Z]=x%10+48,x/=10);
	while(sr[++CCF]=z[Z],--Z);sr[++CCF]=chr;
} ll n,k,ans=1;
inline bool ask(ll x){ return k+1<=x*2/k; }
int main(){ cin>>n>>k;
	if(k+1>n*2/k) return !printf("-1\n");
	if(k==1) return !printf("%I64d\n",n);
	fp(i,2,sqrt(n)) if(!(n%i)){
		if(ask(n/i)) cmax(ans,i);
		if(ask(i)) cmax(ans,n/i);
	}
	fp(i,1,k-1) print(ans*i),n-=ans*i;
	return print(n,'\n'),Ot(),0;
}
```



---

## 作者：zhfaz123 (赞：1)

读完题后显然会发现这么一个事实 $n$ 一定能被最大公约数 $m$ 整除。考虑一个更简单的问题：如何判断一个 $n$ 的因数 $x$ 是否能构成满足题目要求的单调序列。

方法很简单，先构造一个和尽可能小的单调序列，即每一项的的数都是上一项加 $x$。根据等差数列求和公式不难得出数列的和为 $\frac{xk(k-1)}{2}$。（如果和大于 $n$，显然我们要舍弃它。）但这个序列和不一定是 $n$，所以我们还要给最后一项加上 $n-\frac{xk(k-1)}{2}$，这时就是一个合法序列了。

此时很容易想到二分，先求出 $n$ 的所有因数，接着在二分求最大的满足要求的因数 $x$。

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<iomanip>
#include<stack>
#include<algorithm>
#include<queue>
#include<deque>
#include<cstring>
#include<string>
#include<set>
#include<utility>
#include<set>
#include<map>
#include<climits>
#include<unordered_set>
#include<unordered_map>
#include<bitset>
constexpr int N=1e5,M=1e4;
using namespace std;
long long n,m,k;//记得开long long
vector<long long> vc;
void inline init()//求出所有因数，vc存因数
{
    vc.reserve(55);
    vector<long long> tp;
    tp.reserve(55);
    for(long long i=1;i*i<=n;i++)
    {
        if(n%i==0)
        {
            vc.push_back(i);
            tp.push_back(n/i);
        }
    }
    for(auto i=(tp.rbegin());i!=tp.rend();i++)
    {
        vc.push_back(*i);//保证vc单调
    }
}
bool inline check(const long long& v)
{
    return ((k*(k+1))/2)*v<=n;
}//判断是否合法
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>k;
    if(k*(k+1)/2>n||k>=1e6) cout<<"-1",exit(0);//最小公约数1满足不了，就输出-1，k>1e6时显然无解
    init();
    int l=0,r=vc.size()-1;
    while(l<r)
    {
        int mid=(l+r+1)>>1;//向上取整，防止死循环
        if(check(vc[mid]))
        {
            l=mid;
        }
        else
        {
            r=mid-1;
        }
    }//二分主体
    long long sum=0;
    for(long long i=1;i<k;i++) cout<<i*vc[r]<<" ",sum+=i*vc[r];//输出前k-1项
    cout<<n-sum;//输出最后一项
    return 0;
}
```

---

## 作者：User_Unauthorized (赞：1)

## 题意
构造一个长度为 $k$，和为 $n$ 的严格单调递增序列，并最大化其最大公约数。

（$1 \le n,k \le 10^{10}$）

## 题解
首先可以发现一个事实，这个序列的最大公约数一定为 $n$ 的因子。所以我们可以考虑枚举 $n$ 的所有因子并判断其能否成为整个序列的最大公约数。假设我们现在枚举到的因子为 $x$，那么满足要求的序列各个元素一定为 $x$ 的倍数，考虑最终序列 $a_i$ 除 $x$ 后的值 $b_i$，显然 $b$ 同 $a$ 一样单调递增。

考虑一个引理，长度为 $k$ 的严格单调递增序列的和最小为 $\dfrac{k \left(k + 1\right)}{2}$，并且一定存在和大于 $\dfrac{k \left(k + 1\right)}{2}$ 的长度为 $k$ 的严格单调递增序列。证明考虑从和最小的序列情况下改变序列的几个值，使得和增加 $\Delta = sum - \dfrac{k \left(k + 1\right)}{2}$，显然直接将最后一位的值增加该差值即可满足要求，即 $b_k \leftarrow b_k + \Delta$。

所以我们以 $\mathcal{O}(\sqrt{n})$ 的复杂度枚举 $n$ 的各个因子 $d$，并找到最大的满足 $n / d \ge \dfrac{k \left(k + 1\right)}{2}$ 的因子 $D$，设 $\Delta = n - d \times \dfrac{k \left(k + 1\right)}{2}$，那么最终序列的前 $k - 1$ 项依次为 $1 \cdot D, 2 \cdot D, \cdots, \left(k - 1\right) \cdot D$，第 $k$ 项为 $k \cdot D + \Delta$。可以证明这样的序列一定合法且序列的最终长度不会超过 $\max(k, \dfrac{n}{\frac{k \left(k + 1\right)}{2}})$。

## Code
```cpp
//Codeforces - CF803C
#include <bits/stdc++.h>

typedef long long valueType;

int main() {
    valueType N, K;

    std::cin >> N >> K;

    if (N / K < (K - 10) / 2) {
        std::cout << -1 << std::endl;

        return 0;
    }

    if (N < K * (K + 1) / 2) {
        std::cout << -1 << std::endl;

        return 0;
    }

    valueType const min = K * (K + 1) / 2;
    valueType const start = std::ceil(std::sqrt((long double) N) + 10);

    valueType result = 1;

    for(valueType i = start; i >= 1; --i) {
        if (N % i == 0) {
            if (N / i >= min)
                result = std::max(result, i);

            if (i >= min)
                result = std::max(result, N / i);
        }
    }

    valueType const remain = N / result - min;

    for(valueType i = 1; i < K; ++i)
        std::cout << i * result << ' ';

    std::cout << result * (K + remain) << std::endl;

    return 0;
}
```

---

## 作者：Dr_Gilbert (赞：1)

# CF803C Maximal GCD

【题目大意】

构造一个长度为 $k$ 的严格递增正整数序列，使得所有数的和恰好为 $n$，并且所有数的最大公约数最大。如果无解输出 $-1$。

首先注意到题目要求判断无解情况，严格递增正整数序列中，和最小的显然是 $1,2,\cdots,k$ 这个等差数列，求和公式为 $S=\dfrac{k(k+1)}{2}$。这样就可以判断无解。

题目要求所有数的最大公约数最大，也就是说所有的数都是这个最大公约数的倍数。从而得到这些数的总和 $n$ 也一定是最大公约数的倍数。考虑 $n\le10^{10}$，不妨对 $n$ 进行分解，每分解到一个因子就判断是否可能为最大公约数。不难发现，若整个序列的最大公约数为 $g$，则长度为 $k$ 的序列的和最小值为 $S=g\dfrac{k(k+1)}{2}$。所以枚举到一个因子时，计算出另一个因子，将两个因子与 $\dfrac{k(k+1)}{2}$ 比较大小。若因子更大，则更新答案。最后构造时前 $k-1$ 项仍然为等差数列，最后一项为剩余，这样可以保证数列递增。更新答案的复杂度为 $O(\sqrt n)$，构造复杂度为 $O(k)$，故总复杂度为 $O(\sqrt n+k)$。显然，若存在答案，则 $k<10^5\sqrt2$，可以通过。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	int n,k,ans=0;cin>>n>>k;
	double lim=k/2.0*(k+1); // 注意精度，小心溢出
	if (n<lim){
		cout<<-1;return 0;
	}
	for (int i=1;i<=sqrt(n);i++){
		if (n%i) continue;
		int tmp=n/i;
		if (tmp>=lim) ans=max(i,ans);
		if (i>=lim) ans=max(tmp,ans);
	}
	for (int i=1;i<k;i++){
		int x=i*ans;cout<<x<<' ';
		n-=i*ans;
	}
	cout<<n;return 0;
}
```



---

## 作者：XL4453 (赞：1)

### 题目分析：

首先我们要知道那个数据范围就是用来吓人的，$10^{10}$ 根本输出不了。然而，题目说这是一个严格递增的序列，那么使得其值最小的情况就是 $1,2,3,4...$ 总和显然是 $\dfrac{n\times(n+1)}{2}$，这样一来需要输出完整答案的 $k$ 的范围就降到了 $10^5$，是没有问题的。

----------

考虑具体做法，因为要满足数列中有一个最大的最大公因数，考虑枚举这个公因数是什么，然后将总合除以这个公因数与 $\dfrac{n\times(n+1)}{2}$，即最小可能总合比较。若后者者更大，则一定不可能构造出一个符合条件的序列，否则则一定可以构造出一组满足条件的序列。

然后考虑如何构造，方法有很多，这里只介绍较为简单的一种：从一开始一直枚举到 $k-1$，用 $n$ 累减每一个数，最后将剩下值输出，可以证明，这样一定不会有重复，注意每一个数在输出时都要乘以之前求出的最大公因数。

-------
复杂度大概是这样的：枚举最大公因数 $O(\sqrt n)$，然后每一个 $O(1)$ 判断可行性，最后再用 $O(k)$（可行）或 $O(1)$（不可行）输出结果，输出时间复杂度在开头分析过了，是没有问题的。

----------
不开 long long 见祖宗

开了 long long 没改 lld 见祖宗

改了 lld 没改函数参数见祖宗

------
### 代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
long long k,n,tot,ans;
bool check(long long n){return k+1<=n*2/k;}
int main(){
	scanf("%lld%lld",&n,&k);
	if(!check(n)){printf("-1\n");return 0;}
	for(long long i=1;i*i<=n;i++){
		if(n%i==0&&check(n/i))ans=max(ans,i);
		if(n%i==0&&check(i))ans=max(ans,n/i);
	}
	for(int i=1;i<=k-1;i++){
		printf("%lld ",ans*i);
		n-=ans*i;
	}
	printf("%lld\n",n);
	return 0;
}
```


---

## 作者：daniEl_lElE (赞：0)

## 思路

比较简单的一题。

考虑严格递增这个条件，满足的最小的为 $1,2,3,4,\dots$，这是十分显然的。

使用小学学过的知识，这个序列前 $k$ 个和为 $\dfrac {k(k+1)}2$。

我们现在想要最大公约数尽可能大，其实就是求一个最大的 $x$，使得 $n$ 是 $x$ 的倍数且 $\dfrac n x$ 要大于我们的前 $k$ 个和，$\dfrac {k(k+1)}2$。意思也就是让他们 $\gcd$ 为 $x$，然后要求剩余和不能小于最小和。

然后直接枚举 $x$ 即可，复杂度 $O(d(n))$，枚举的话实际 $O(\sqrt{n})$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mp make_pair
#define s(i,j) (i-1)*n+j
using namespace std;
signed main(){
	int n,k;
	cin>>n>>k;
	if(k*(k+1)/2>n||k>=1e6){
		cout<<-1;
		return 0;
	}
	int maxv=0;
	for(int i=1;i*i<=n;i++){
		if(n%i==0){
			if(k*(k+1)/2<=i){
				maxv=max(maxv,n/i);
			}
			if(k*(k+1)/2<=n/i){
				maxv=max(maxv,i);
			}
		}
	}
	n/=maxv;
	for(int i=1;i<k;i++){
		cout<<i*maxv<<" ";
		n-=i;
	}
	cout<<n*maxv;
	return 0;
}
```

---

## 作者：xiaorui2007 (赞：0)

## 思路
设这$k$个数分别为 $a_1,a_2,\dots,a_k$，$d=\gcd(a_1,a_2,\dots,a_k)\ge1$。  
显然 $d|n$。由于题目条件，对于 $\forall i=1,2,\dots,k,a_i\ge i\times d$，且对于 $\forall i=2,3,\dots,k,a_i\ge a_{i-1}$。  
故：
$$10^{10}\ge n=\sum\limits_{i=1}^{k}{a_i}\ge d\sum\limits_{i=1}^{k}{i}=d\dfrac{k(k+1)}{2}\ge\dfrac{k(k+1)}{2}$$
## 解题方法
由上式，存在答案当且仅当 $n\ge\dfrac{k(k+1)}{2}$。但是，$\dfrac{k(k+1)}{2}\le50,000,000,005,000,000,000$，炸了`long long`。我们知道，$10^{10}\ge n$，所以可以将 $\ge10^6$ 的 $k$ 排除。  
- 求 $d_{max}$  
枚举 $n$ 的所有因数 $x$，$\le\left\lfloor\dfrac{2n}{k(k+1)}\right\rfloor$的最大 $x$ 即为所求。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,t,ma;//ma为d_max

void f(long long x)
{
    if(x<=t)
    ma=max(ma,x);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin>>n>>k;
    if(k>=1000000)//特判
    {
        cout<<-1<<endl;
        return 0;
    }
    if(n<(k*(k+1)/2))
    {
        cout<<-1<<endl;
        return 0;
    }
    t=n/(k*(k+1)/2);
    for(long long i=1;(i*i)<=n;i++)//枚举n的所有因数
        if((n%i)==0)
        {
            f(i);
            f(n/i);
        }
    for(long long i=1;i<k;n-=i*ma,i++)//输出
        cout<<i*ma<<" ";
    cout<<n<<endl;
    return 0;
}
```

---

## 作者：撤云 (赞：0)

[广告](https://www.cnblogs.com/hbxblog/p/11415065.html)
### $Solution$

令$gcd$为$x$,那么我们将整个序列$/x$,则序列的和就变成了$\frac{n}{x}$,所以$x$必定为$n$的约数所以现在就是要构造出一个序列长度为$k$,和为$\frac{n}{x}$。我们令前$k-1$个为$1,2....k-1$最后一个再用$\frac{n}{x}-$这$k-1$个的和就是最后一个数了。最后的答案就是构造出来的序列$*x$

所以我们现在就是要来判断$x$可不可行，很明显如果$(1+k)*k/2>\frac{n}{x}$的话显然不可行，反之则可以。所以我们找到最大的$x$用上述方法构造即可.

注意特判一下$k$很大的时候，有可能会乘爆

### $Code$

``` cpp
#include<bits/stdc++.h>
#define int long long
#define rg register
#define file(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout);
using namespace std;
int read(){
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9') f=(c=='-')?-1:1,c=getchar();
    while(c>='0'&&c<='9') x=x*10+c-48,c=getchar();
    return f*x;
}
int n,k,maxx,ans;
bool check(int x){
	return (1+k)*k/2<=(n/x);
}
main(){
	n=read(),k=read();
	if(k>2e5) puts("-1"),exit(0);
	for(int i=1;i*i<=n;i++){
		if(n%i!=0) continue;
		if(check(i)) maxx=max(maxx,i);
		if(check(n/i)) maxx=max(maxx,n/i);
	}
	if(!maxx) puts("-1"),exit(0);
	for(int i=1;i<=k-1;i++)
		cout<<i*maxx<<" ",ans+=i*maxx;
	cout<<n-ans;
    return 0;
}
```

---

## 作者：wyd_forever (赞：0)

一句话：注意判炸$long~long$  
  
没公约数的情况不用说了，若有设其为$p$，很明显$n$为$p$的倍数，此时可以将序列的和化为$n/p$个$p$的和，又$n/p$个最少为$k*(k+1)>>1$个，所以就得到了$n/p$的下界，则$p$的上界为$\frac{n}{k*(k+1)>>1}$，只需求在该界之下的最大的$n$的因数即可求出$p$的最大值。  
  
$tmp$之下第一个$n$的倍数可以这么求：  
```cpp  
inline long long chu(long long n,long long k)
{
	long long g=1;
	for(;n%k;k=n/k+g,g^=1);
	return g?k:n/k;
}  
```  
总的代码：  
```cpp
#include<iostream>
using namespace std;
inline long long read()
{
	long long x=0;
	char ch=getchar();
	for(;!isalnum(ch);ch=getchar());
	for(;isalnum(ch);ch=getchar()) x=x*10+ch-'0';
	return x;
}
inline long long need(long long m,long long f)
{
	long long ans=2*m-f*f+f;
	ans=ans/(2*f);
	return ans;
}
inline long long chu(long long n,long long k)
{
	long long g=1;
	for(;n%k;k=n/k+g,g^=1);
	return g?k:n/k;
}
int main()
{
//	freopen("out.cpp","w",stdout);
	long long n=read(),k=read();
	long long tmp=need(n,k);
	tmp=min(tmp,n/(k*(k+1)>>1));
	if(tmp<=0||k>2e5) puts("-1"),exit(0);
	long long p=chu(n,tmp);
	long long t=n-(k*(k+1)>>1)*p;
	for(long long j=1;j<=k-1;++j) printf("%lld ",p*j);
	printf("%lld\n",t+k*p);
	return 0;
}
```  

---

