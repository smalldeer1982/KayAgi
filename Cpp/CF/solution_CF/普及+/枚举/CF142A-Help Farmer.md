# Help Farmer

## 题目描述

原本有A×B×C块干草，被偷走若干块后，剩下N块，刚好等于(A−1)×(B−2)×(C−2)。现在已知N的值，不知道ABC的值，求被偷走的干草的最小值和最大值。

## 样例 #1

### 输入

```
4
```

### 输出

```
28 41
```

## 样例 #2

### 输入

```
7
```

### 输出

```
47 65
```

## 样例 #3

### 输入

```
12
```

### 输出

```
48 105
```

# 题解

## 作者：xukuan (赞：5)

文章翻译（由于我被禁言，只能在此翻译 此翻译由我的教练翻译，请不要对我加贡献）

题目描述

原本有A×B×C块干草，被偷走若干块后，剩下N块，刚好等于(A−1)×(B−2)×(C−2)。现在已知N的值，不知道ABC的值，求被偷走的干草的最小值和最大值。

输入输出格式

输入格式

第一行，一个整数n。

输出格式

第一行，两个整数，分别表示最小值和最大值。

Input Sample 1

4

Output Sample 1

28 41

Input Sample 2

7

Output Sample 2

47 65

Input Sample 3

12

Output Sample 3

48 105

———————————————————————————————————

题解正文：

思路：暴力枚举题中(a-1)×(b-1)×(c-1)

说明：本代码中a,b,c与题目中a,b,c含义不同,具体见代码

四个优化：

1：n%a==0;

2：n%b==0；

3：n%(a*b)==0;

4:如果x%y==0 那么x%(x%y)==0

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#define ll long long
//等同于typedef long long ll
using namespace std;

ll n,maxx,minn=214748364700;//有一个输出比2147483647还要大！！
//maxx代表最大值,minn代表最小值

inline void work(ll a,ll b){
	if(n%(a*b)!=0) return;
    //a*b必须是n的约数
    //优化3：n%(a*b)==0
	ll c=n/(a*b);//算出c的值
	ll k=(a+1)*(b+2)*(c+2)-a*b*c;//被偷走的干草数
	maxx=max(maxx,k);//更新最大值
	minn=min(minn,k);//更新最小值
	
    //以下两个程序用途同上(a,b,c的位置不确定)
	k=(a+2)*(b+1)*(c+2)-a*b*c;
	maxx=max(maxx,k);
	minn=min(minn,k);
	
	k=(a+2)*(b+2)*(c+1)-a*b*c;
	maxx=max(maxx,k);
	minn=min(minn,k);
}

int main(){
	cin>>n;
	for(ll a=1; a<=(long long)pow(1.0*n,1.0/3)+1; a++){
    //结果必须用(long long)pow(1.0*n,1.0/3)+1
    //用sqrt(n)+1会TLE
    //用(long long)pow(1.0*n,1.0/3)会WA
		if(n%a==0)//优化1：n%a==0
		for(ll b=1; b*b<=n/a; b++){
			if(n%b==0){//优化2：n%b==0，可以不用
             //优化4:如果x%y==0 那么x%(x%y)==0
             	work(a,b);
				work(a,n/b);
				work(n/a,b);
				work(n/a,n/b);
			}
		}
	}
	cout<<minn<<' '<<maxx<<endl;
	return 0;
}
```


---

## 作者：tanghairong (赞：2)

简单的模拟即可

由于 $10^9$ 的因数个数 $n$ 不能满足 $O(n^3)$ 的时间复杂度，故只能尝试使用 $O(n^2)$ 方法。

设 $x$、$y$、$z$ 表示一组满足 $x\times y\times z=n$ 的数。

容易发现，当确定 $n$ 的两个因子 $x$ 和 $y$ 之后，其另外一个因子 $z$ 也就确定了。

由于 $x$、$y$、$z$ 的位置可互换，故对于每一组 $x,y,z$，设此时被偷走的干草值为 $k$，$k$ 有三种取值：

+ $(x+1)\times (y+2)\times (z+2)-n$

+ $(y+1)\times (x+2)\times (z+2)-n$

+ $(z+1)\times (x+2)\times (y+2)-n$

在这三种取值中取最值尝试更新即可。

注意事项：

+ 开 ```long long```（极限数据显然会超 ```int```）

+ 记得判断 $x$、$y$、$z$ 是否都是 $n$ 的因数。

code（就不加注释了）：

```
#include<iostream>
#define int long long
using namespace std;
signed main(){
    int n,maxn=0,minn=1e16;
    cin>>n;
    for(int x=1;x*x*x<=n;x++){
        if(n%x!=0)continue;
        for(int y=1;x*y*y<=n;y++){
            if((n/x)%y!=0)continue;
            int z=n/x/y,k;
            k=(x+1)*(y+2)*(z+2)-n;
            maxn=max(maxn,k);minn=min(minn,k);
            k=(y+1)*(x+2)*(z+2)-n;
            maxn=max(maxn,k);minn=min(minn,k);
            k=(z+1)*(x+2)*(y+2)-n;
            maxn=max(maxn,k);minn=min(minn,k);
        }
    }
    cout<<minn<<" "<<maxn;
    return 0;
}

```

---

## 作者：VenusM1nT (赞：2)

想多了，看到题面以为是道结论题。  
![一姬海滩派对表情1.png](https://i.loli.net/2020/10/26/lYDh4FAm1CTgW27.png)  
然后找了一下规律，发现最大值恒为 $9\times (n+1)-n$，此处可以考虑形如已知 $xy=r$ 求 $x$ 最大值的情况，肯定是一个极大一个极小，放到这题也是一样，而两个 $+2$ 肯定是给 $1$ 的贡献更大，所以答案就是上面那个式子。  
然后尝试推最小值，依然考虑上面那个 $xy=r$，肯定是 $x,y$ 最相近的时候取到最小，那么问题来了：这个最相近怎么取  
![杏树契约表情2.png](https://i.loli.net/2020/10/26/YNHr3dfAMnmX6ta.png)  
因为有三个数，所以并不会，转而考虑枚举因数，根据网上查阅发现 2e9 内数最多有约 1500 个因数，所以 $\text{O}(m^2)$ 是可以接受的，于是枚举两个因数，唯一确定第三个数，取最小值即可。  
~~貌似 1e18 以内最多有 1e5 个因数，如果哪位可以找到最小值的结论就可以出增强版了（可能已经有了也说不定）~~
```cpp
#include<bits/stdc++.h>
#define N 100000
#define reg register
#define inl inline
#define int long long
using namespace std;
int n,a[N+5],tot,ans=1e18,Ans;
signed main()
{
	scanf("%lld",&n);
	Ans=3*3*(n+1)-n;
	a[++tot]=1;
	a[++tot]=n;
	for(reg int i=2;i<=(int)(sqrt(n));i++)
	{
		if(!(n%i))
		{
			a[++tot]=i;
			if(i*i!=n) a[++tot]=n/i;
		}
	}
	for(reg int i=1;i<=tot;i++)
	{
		for(reg int j=1;j<=tot;j++)
		{
			reg int x=a[i],y=a[j],z=n/a[i]/a[j];
			if(n%(x*y)) continue;
			if(x*y*z!=n) continue;
			ans=min(ans,(x+1)*(y+2)*(z+2));
		}
	}
	ans-=n;
	printf("%lld %lld\n",ans,Ans);
	return 0;
}
```

---

## 作者：LevenKoko (赞：2)

思路:将n分解出它的约数，记在数组YS中，所以（a+1），（b+2）,(c+2)一定是YS数组中的某个数。然后暴力枚举（时间复杂度为O（n的约数的个数^2））

具体解释见代码
```
#include<iostream>
#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;
typedef long long ll;
inline long long read()
{
	char chr=getchar();
	long long f=1,ans=0;
	while(!isdigit(chr)) {if(chr=='-') f=-1;chr=getchar();}
	while(isdigit(chr))  {ans=ans*10;ans+=chr-'0';chr=getchar();}
	return ans*f;

}
long long  n;

long long ys[10005],tot=0;

void fj(long long x)
{
	for(int i=1;i*i<=x;i++)
	{
		if(x%i==0) ys[++tot]=i,ys[++tot]=x/i;
		if(i*i==x) --tot;
	}
}//fj用来分解，将n分解成各个因子
long long maxn=-(ll(1)<<60),minn=(ll(1)<<60);//用来存最大最小值
int main()
{
	n=read();
	fj(n);
	for(ll i=1;i<=tot;i++)//tot为约数总数；
	{
		for(ll j=1;j<=tot;j++)
		{
			ll a=ys[i],b=ys[j],c=n/a/b;//因为a,b确定后，c一定确定；
			if(a*b*c!=n) continue;
			maxn=max((long long)(a+1)*(b+2)*(c+2)-n,maxn);
			minn=min((long long)(a+1)*(b+2)*(c+2)-n,minn);//分别取最大最小值
		}
	}
	cout<<minn<<" "<<maxn;
	return 0;
}
```


---

## 作者：cqbztz2 (赞：1)

# [题目传送门](https://www.luogu.com.cn/problem/CF142A)

# 前言：

~~这题数据是真的坑~~

# 思路：

思路就是暴力枚举 $ n $ 的因数 $ a,b,c $，没啥好讲的 ~~(上面的大佬都把思路讲完了)~~，但是在循环 $ a,b $ 后就不需要循环 $ c $，复杂度为 $ O(n^2) $，然后用 $ ma $ 和 $ mi $ 存储最大和最小值就  AC  了。

# 代码:

```cpp
  #include<bits/stdc++.h>
  using namespace std;
  long long n,ma=-1,mi=0x3f3f3f3f3f3f3f3f;
  int main(){
      cin>>n;
      for(long long a=1;a*a*a<=n;a++){
          if(n%a==0){
              for(long long b=a;b*b<=n/a;b++){
                  if((n/a)%b==0){
                      long long c=n/a/b,t;
                      t =(a+1)*(b+2)*(c+2);
                      if(t<mi){
                          mi=t;
                      }
                      if(t>ma){
                          ma=t;
                      }
                      t=(b+1)*(a+2)*(c+2);
                      if(t<mi){
                          mi=t;
                      }
                      if(t>ma){
                          ma=t;
                      } 
                      t=(c+1)*(a+2)*(b+2);
                      if(t<mi){
                          mi=t;
                      }   
                      if(t>ma){
                          ma=t;
                      }
                  }
              }
          }
      }
      cout<<mi-n<<" "<<ma-n;
      return 0;
  }
```


---

## 作者：0xFF (赞：1)

#### 题目简述


------------

给定一个 $n = i \cdot j \cdot k$ 求 $(i+1) \cdot (j+2) \cdot (k+2) - n$ 的最小值和最大值。

#### 题目分析


------------

由于 $n$ 非常小，可以考虑直接枚举 $n$ 的所有因数，比较大小即可。


####  代码实现


------------

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
const int maxn = 1e4 + 5;
using namespace std;
typedef long long ll;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
    return x*f;
}
ll n;
ll fac[maxn],tot = 0;
void Get(ll x){
	for(int i=1;i*i <= x;i++){
		if(x % i == 0) fac[++tot] = i , fac[++tot] = x/i;
		if(i*i == x) tot--;
	}
} 
long long ans1 = (ll(1)<<60),ans2 = -(ll(1)<<60);
int main(){
	n= read(); 
	Get(n); 
	for(ll i=1;i<=tot;i++){
		for(ll j=1;j<=tot;j++){
			ll a = fac[i] , b = fac[j] , c = n/a/b;
			if(a*b*c != n) continue;
			ans1 = min((ll)(a+1)*(b+2)*(c+2)-n,ans1);
			ans2 = max((ll)(a+1)*(b+2)*(c+2)-n,ans2);			
		}
	}
	printf("%lld %lld",ans1,ans2); 
	return 0;
}
```


---

## 作者：yzh_Error404 (赞：0)

看到 $n\leqslant 10^9$ 时，我差点以为这是一道数学题。

事实证明，我想多了。

通过打表不难发现， $10^9$ 内约数最多都只有 $1536$ 个，完全可以 $O(n^2)$ 跑过。

所以先把所有约数预处理出来，然后枚举两个约数，统计最大最小值即可。

因为 $n$ 是剩下的数量，所以最后统计出的答案要减去 $n$。

代码实现：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int INF=0x7f7f7f7f7f7f7f;
int n;
vector<int>v;
int maxn=-INF,minn=INF;
signed main()
{
    scanf("%lld",&n);
    for(register int i=1;i<=sqrt(n);i++)
        if(n%i==0)
        {
            v.push_back(i);
            if(n/i!=i)v.push_back(n/i);
        }
    for(register int i=0;i<v.size();i++)
        for(register int j=0;j<v.size();j++)
        {
            int k=n/(v[i]*v[j]);
            if(n%(v[i]*v[j])!=0)continue;
            maxn=max(maxn,(v[i]+1)*(v[j]+2)*(k+2));
            minn=min(minn,(v[i]+1)*(v[j]+2)*(k+2));
        }
    printf("%lld %lld",minn-n,maxn-n);
    return 0;
}
```

---

## 作者：LKY928261 (赞：0)

## 题目分析

本题实际难度应为**普及-**。

#### 解题思路

首先，以 $\sqrt{n}$ 的复杂度求出 $n$ 的全部因子。

接下来，双重循环枚举每个因子，记录最大/最小值。

注意，在枚举时需要加以判断是否符合题意，否则可能出错。

#### 时空复杂度

时间复杂度：$O(x^2)$

空间复杂度：$O(x)$

其中 $x$ 表示 $n$ 的因子个数。

 _P.S._ ：由于 $n$ 的范围只有 $1 \leq n \leq 10^9$ ，而在此范围内的 $x$ 最多不到 2000，所以直接暴力搜索不会超时。

## 参考代码

本人的代码非常精简，欢迎借(chao)鉴(xi)。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,s=9e18,k,t,a[10005],i,j;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(i=1;i<=sqrt(n);i++)if(n%i==0)a[t++]=i,a[t++]=n/i;
	if(sqrt(n)==int(sqrt(n)))t--;
	for(i=0;i<t;i++)for(j=0;j<t;j++){
		if(n/a[i]/a[j]*a[i]*a[j]!=n)continue;//判断是否符合
		s=min(s,(a[i]+1)*(a[j]+2)*(n/a[i]/a[j]+2));
		k=max(k,(a[i]+1)*(a[j]+2)*(n/a[i]/a[j]+2));
	}
	cout<<s-n<<' '<<k-n<<"\n";//不要忘记减去原有个数
	//本人从不打return 0;
}
```

---

## 作者：Astatinear (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF142A)

### 思路

**求所有因子 + 暴力枚举**

这个题目的简要题意就是说给一个等式 $n=(a-1)\times (b-2)\times (c-2)$，其中 $n$ 为定值，$a,b,c$ 为正整数，让你求 $a\times b\times c -n$ 的最大值。

我们为了让上述等式成立，不难想到将 $n$ 的所有因子求出来，然后来暴力枚举 $a,b,c$。但我们又可以发现，如果我们知道了 $a,b$，那么 $c$ 是可以直接求出来的。所以此时我们只需要枚举 $a,b$ 即可。

我们假设一个数有 $x$ 个因子，则此时时间复杂度为 $x^2$。

我们在求每个数有多少因子时，只需要枚举前 $\sqrt n$ 个，如果 $n\bmod i=0$ 那么他的因子就会有 $n,\frac {n}{i}$，当然这里要特判 $i\times i=n$ 的情况。不难看出，一个数最多有 $2\times \sqrt n$ 个因子。再加上数越大，他的因子个数就远远达不到 $2\times \sqrt n$ 这么多个，所以 $x^2$ 这样的复杂度是可以接受的。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//long long
int a[100005],cnt;
int n;
int maxx,minn=LONG_LONG_MAX;//记得开 long long 
signed main()
{
	cin>>n;
	//下面是分解因子 
	for(int i=1;i*i<=n;++i)
	{
		if(n%i==0)
		{
			a[++cnt]=i;a[++cnt]=n/i;
			if(i*i==n)
			--cnt;
		}
	}
	//暴力枚举 
	for(int i=1;i<=cnt;++i)
	{
		for(int j=1;j<=cnt;++j)
		{
			if(n%(a[i]*a[j]))//如果不能整除 a[i]*a[j]，那么就求不出 c,所以 continue
			continue;
			//由于是求偷走去多少，减去 n，再来求最大最小值。 
			maxx=max((a[i]+1)*(a[j]+2)*(n/a[i]/a[j]+2)-n,maxx);
			minn=min((a[i]+1)*(a[j]+2)*(n/a[i]/a[j]+2)-n,minn);
		}
	}
	cout<<minn<<" "<<maxx<<endl;//直接输出。
	return 0;//return 0是 一种好的素养， 
}
```

---

## 作者：IvanZhang2009 (赞：0)

题目可以转换为：

已知 $N=i\cdot j\cdot k$，求 $(i+1)\cdot(j+2)\cdot(k+2)-N$ 的最小值和最大值。

因为 $N$ ~~很小~~，只有 $10^9$，则可以考虑枚举 $i$，$j$，若可以整除，则算出 $k$，再比较大小。注意结果要减 $N$。

代码：
```cpp
int n;
cin>>n;
int maxn=-1;
int mini=1e18;
for(int i=1;i*i<=n;i++)
if(n%i==0){
	for(int j=1;j*j<=n/i;j++)
	if((n/i)%j==0){
		int k=n/i/j;
		int x=(k+1)*(i+2)*(j+2);
		maxn=max(maxn,x);
		mini=min(mini,x);
		x=(k+2)*(i+1)*(j+2);
		maxn=max(maxn,x);
		mini=min(mini,x);
		x=(k+2)*(i+2)*(j+1);
		maxn=max(maxn,x);
		mini=min(mini,x);
	}
}
cout<<mini-n<<' '<<maxn-n<<endl;
```

---

