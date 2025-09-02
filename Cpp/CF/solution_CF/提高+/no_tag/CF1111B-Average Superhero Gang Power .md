# Average Superhero Gang Power 

## 题目描述

每个超级英雄都被 Felicity 委员会赋予了一个能力值。复仇者团队希望通过执行某些操作来最大化他们团队中超级英雄的平均能力值。

最初，复仇者团队中有 $n$ 个超级英雄，他们的能力值分别为 $a_1, a_2, \ldots, a_n$。在一次操作中，他们可以移除一个超级英雄（前提是团队中至少还剩下两人），或者将某个超级英雄的能力值增加 $1$。他们最多可以执行 $m$ 次操作。此外，对某个特定超级英雄最多只能进行 $k$ 次操作。

你能帮助复仇者团队最大化他们团队的平均能力值吗？

## 说明/提示

在第一个样例中，最大平均值可以通过删除第一个元素并将第二个元素增加 $4$ 次获得。

在第二个样例中，一种获得最大平均值的方法是删除第一个和第三个元素，并分别将第二个和第四个元素增加 $2$ 次。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 4 6
4 7
```

### 输出

```
11.00000000000000000000
```

## 样例 #2

### 输入

```
4 2 6
1 3 2 3
```

### 输出

```
5.00000000000000000000
```

# 题解

## 作者：cff_0102 (赞：3)

每次删除必定删最小的，所以先对每个能力值进行排序。

然后直接从 $0$ 到 $n-1$ 枚举删去排序后前 $i$ 小的人（如果 $m\ge i$）的情况。计算出剩下的操作全用在加能力值上的话最终的答案，然后在最后取 $\max$。

不过注意每次加的时候也不一定能把 $m$ 次操作加满。把前 $i$ 个人删掉后，还剩下 $m-i$ 次操作，而剩下的 $n-i$ 个人一共只能加 $k\times(n-i)$ 个能力值。此时最终在剩下的人上加的能力值应该是 $\min(m-i,k\times(n-i))$。此时的答案应该是 $\min(m-i,k\times(n-i))$ 加上后 $n-i$ 个人的能力值之和，最后再除以 $n-i$。

如何快速求出后 $n-i$ 个人的能力值之和？先在读入的时候求出这 $n$ 个人的能力值之和，然后到后面枚举时直接计算出前 $i$ 个人的能力值之和，最后一减就能得出了。

不过注意能力值之和可能爆 `int`，需要开 `long long`，并且最好全部开 `long long`（因为有 $k\times(n-i)$ 这个算式，我刚开始因为这个 WA 了）。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1919810];
int main(){
	long long n,k,m;
    cin>>n>>k>>m;
    long long sn=0;//计算全部 n 个数的和 
    for(int i=1;i<=n;i++){
    	cin>>a[i];
		sn+=a[i];
	}
    sort(a+1,a+n+1);
    long long si=0;//计算前 i 个数的和
    long double ans=-1;//存储最终答案，空间不会爆，精度越大越好
    a[0]=0;
    for(int i=0;i<n;i++){//或者 i<=n-1 更容易理解
		if(i>m)break;//m 次操作根本无法把前 i 个数删了 
        si+=a[i];//a[0]=0
        ans=max(ans,(long double)(min(m-i,k*(n-i))+sn-si)/(n-i));//min(m-i,k*(n-i)) 是能够增加的能力值，min(m-i,k*(n-i))+sn-si 是最终的能力值之和，(long double)(min(m-i,k*(n-i))+sn-si) 将和强转为 long double，(long double)(min(m-i,k*(n-i))+sn-si)/(n-i) 是最终的能力值平均值 
    }
    printf("%.100Lf",ans);//输出并保留 100 位小数 
    return 0;
}
```

这道题测试点很多，足足有 $121$ 个，我用 RMJ 测了 $4$ 分钟才测出结果。

---

## 作者：Zechariah (赞：3)

理解题意后，这题就很好做了。  
枚举删除多少人，结果取最大，注意题目中给出的一些限制：操作数$m$、每个人最多加$k$次，最终要至少剩一人
```cpp
#include <bits/stdc++.h>
#define jh(x,y) x^=y^=x^=y
#define rg register
#define inl inline
typedef long long ll;
const int N = 1e5 + 5, mod = 10007;
using namespace std;
namespace fast_IO {
    inl ll read()
    {
        rg ll num = 0;
        rg char ch;
        rg bool flag = false;
        while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
        if (ch == EOF)return ch; if (ch == '-')flag = true; else num = ch ^ 48;
        while ((ch = getchar()) != ' '&&ch != '\n'&&ch != '\r'&&~ch)
            num = (num << 1) + (num << 3) + (ch ^ 48);
        if (flag)return -num; return num;
    }
    inl int chread(rg char s[])
    {
        rg int len = 0;
        rg char ch;
        while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
        s[len++] = ch;
        while ((ch = getchar()) != ' '&&ch != '\n'&&ch != '\r'&&~ch)
            s[len++] = ch;
        s[len] = 0;
        return len;
    }
    inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
    inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
    void write(rg long long x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
};
int a[N];

int main(void)
{
    rg int n = fast_IO::read(), k = fast_IO::read(), m = fast_IO::read();
    rg double sum = 0, ans = 0;
    for (rg int i = 1; i <= n; ++i)a[i] = fast_IO::read();
    sort(a + 1, a + n + 1);
    for (rg ll i = n - 1; i >= 0; --i)
    {
        sum += a[i + 1];
        if (i <= m)ans = max(ans, (sum + min(m - i, (n - i)*k)) / (n - i));
    }
    printf("%.6f", ans);
    return 0;
}

```

---

## 作者：蒟蒻酱 (赞：2)

  给你n个数，你可以随便搞它m次，每次可以给一个数加1或者去掉它，问最大平均值。

不知道其他大佬怎么想，反正排完序之后枚举删去前i个数覆盖答案即可。

代码：
```cpp
#include<bits/stdc++.h>
#define ri register int
using namespace std;
typedef long long ll;
inline int doo(){
	int ans=0;
	char ch=getchar();
	while(!isdigit(ch))
		ch=getchar();
	while(isdigit(ch))
		ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
	return ans;
}

const int N=1e5+5;
ll a[N];
ll anss[N];
int n,k,m;
int main(){
	n=doo(),k=doo(),m=doo();
	for(ri i=1;i<=n;++i)
		a[i]=doo();
	sort(a+1,a+n+1);
	for(ri i=1;i<=n;++i)
		anss[i]=anss[i-1]+a[i];
	double ans=0.0;
	for(ri i=1;i<=min(n,m+1);++i)
	{
		ll up=min((ll)m-i+1,(ll)(n-i+1)*k);
		ans=max(ans,1.0*(anss[n]-anss[i-1]+up)/(n-i+1));
	}
	printf("%.10lf\n",ans);
	return 0;
}
```


---

## 作者：pipiispig (赞：2)

###
模拟+贪心（类似于dp的神奇贪心）

这个题是个类似于dp的贪心，如果想删除一个元素来增加平均值，它应该是当前集合中最小的元素。如果删除了i个元素，那么对于剩余的n-i个元素，最大增量可以是
min（m-i，k（n-i））；通过模拟这样的操作就可以的得到最大值；
很重要的一点是这个题卡精度！！！反正我没用long doule被别人hack了一次QwQ;
```
#include <bits/stdc++.h>
using namespace std;
inline int read(){
    long long f=1,x=0;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=x*10+c-'0';
        c=getchar();
    }
    return f*x;
}
long long s[100010];long long ans;
long double ans1;
int main(){
    long long n=read(),k=read(),m=read();
    for(int i=1;i<=n;i++)s[i]=read(),ans+=(long long)s[i];
    sort(s+1,s+n+1);
    ans1=(long double)(ans+min(m,n*k))/(long double)(n);
    for(int i=1;i<=min(n-1,m);i++){
        ans-=(long long)s[i];
        long long tp=ans+(long long)min((n-i)*k,m-i);
        ans1=max((long double)ans1,(long double)tp/(long double)(n-i));
    } 
    cout<<fixed<<setprecision(15)<<ans1<<endl;//就是格式化，也可以用printf代替QwQ
    return 0;
}
```

---

## 作者：skyskyCCC (赞：1)

## 前言。
很明显的模拟，注意精度即可。
## 分析。
要使所有剩下的人的能力值的平均值尽可能大，我们就要尽可能将数小的去掉，然后将大数再次加大，此时我们可以通过排序，以 $a_i$ 的大小为关键字，然后去判断这个数的取舍情况。

排好序后，我们首先依次统计从 $a_1$ 到 $a_n$ 的所有数的前缀和，方便以后计算。

考虑删除操作，首先因为对于较小的数我们可以考虑删除，因为很明显删除较大的数对平均值的影响肯定大于较小的数，所以排序后我们选择删除前 $Q$ 个数。

考虑到剩下的数可以每个一直加 $1$ 直到 $k$ 所以肯定有人考虑贪心。但明显，比较的数需要考虑当前操作对全局的影响，这个贪心策略显然不是我们平常用的简单贪心了，而要实时维护最优解，处理起来需要复杂地维护，不可取，所以考虑模拟。我们删除前 $Q$ 个人后，因为一次删除 $m$ 减去一，所以我们还剩下 $m-Q$ 次操作，此时我们将剩下的数可以总共加上 $k\times 1\times\left(n-Q\right)$ 个数，那么此时剩下的人可以加上的数为 $m-Q$ 和 $k\times \left(n-Q\right)$ 的最小值，所以此时整个序列的和就是这个最小值加上没有被删除的人后面 $n-Q$ 个人的能力值之和。然后将这个和除以 $n-Q$ 即人数即为平均值。

考虑到不能在每次进行上述过程中重复计算，我们前面设立的前缀和就可以派上用场了，可以迅速找到我们需要的区间内的能力值之和。

注意到所有输入较大，请妥善处理数据范围。

代码如下，仅供参考：
```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdio>
using namespace std;
long long n,k,m,a[100005];
long long sum[100005];
double ans;
int main(){
	cin>>n>>k>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	} 
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1]+a[i];
	}
	long long len=min(n,m+1);
	for(int i=1;i<=len;i++){
		long long tot=min((long long)m-i+1,(long long)(n-i+1)*k);
        //cout<<"pd: "<<i<<" "<<tot;
		ans=max(ans,1.0*(sum[n]-sum[i-1]+tot)/(n-i+1));
        //cout<<" "<<ans<<"\n";
	}
	printf("%.20lf\n",ans);
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：FReQuenter (赞：1)

## 思路

首先排序，然后枚举删除的数的数量，再计算剩下的数之和加上最大可用魔法次数算平均数。因为是算平均数，所以每个数最多加上 $k$ 可以理解为一个数加上剩下数的数量 $\times k$，其它数不改变。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,m,sum,as,a[1000005];
double ans;
signed main(){
    cin>>n>>k>>m;
    for(int i=1;i<=n;i++) cin>>a[i],as+=a[i];
    sort(a+1,a+n+1);
    for(int i=0;i<=min(n-1,m);i++){
        sum+=a[i];
        int rstsum=as-sum,rsm=m-i;
        ans=max(ans,(rstsum+min(k*(n-i),rsm))*1.0/(n-i));
    }
    cout<<fixed<<setprecision(10)<<ans;
    return 0;
}
```

---

## 作者：0xFF (赞：1)

#### 题目大意


------------
给出 $n$ 个人的能力值，你可以操作 $m$ 次，每次可以删去一个人或者给这个人的能力值加 $1$，对于每个人的操作次数不能超过 $k$ 次。

#### 思路分析


------------
先按照能力值排序，枚举每一个人的所有情况（能力值增加 $1$~$k$ 或删去），取最大值即可。

#### 代码实现


------------
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#define int long long
using namespace std;
const int N = 100010;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
    return x*f;
}
int a[N];
int pre[N];
signed main(){	
	int n = read() , k = read() , m = read();
	for(int i=1;i<=n;i++){
		a[i] = read();
	} 
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		pre[i] = pre[i-1] + a[i];
	}
	double ans = 0.0;
	for(int i=1;i<=min(n,m+1);i++){
		int inc = min(m - i + 1 , (n - i + 1) * k);
		ans = max(ans,1.0*(pre[n] - pre[i-1] + inc) / (n - i + 1));
	}
	printf("%.8lf\n",ans);
	return 0;
}
```


---

## 作者：Nahia (赞：0)

题目传送门：（[洛谷](https://www.luogu.com.cn/problem/CF1111B)）（[Codeforces](https://codeforces.com/problemset/problem/1111/B)）

~~[可能更好的食用体验](https://www.luogu.com.cn/article/hlk2wzht)~~

## 题意
有 $n$ 名炒鸡英雄，每次可以将一名炒鸡英雄踢出团队或者给一名英雄增加一点能力值。给定人数 $n$，每个人最多的操作数 $k$ 和最大总操作数 $m$，求最后所有剩下的人的平均能力值的最大值。

## 思路
每次踢一个人必定踢最小的（~~不然你就要被请出委员会了~~），而加能力值加到谁身上又没有区别，所以说先计算出全加能力值后的平均能力值，再一个个枚举踢人后的平均能力值，一直取最大值就可以。

## solution
先排个序，计算出现在的平均能力值，之后再一个个枚举就可以了（注意保留小数位）。

## AC Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int a[N];
int main(){
	int n,k,m;
	long long sum = 0;
	cin>>n>>k>>m;
	for(int i = 1;i<=n;i++){
		cin>>a[i];
		sum+=a[i];
	}
	
	sort(a+1,a+n+1);
	int rest = n;
	double ans = 1.0*(sum+min(1ll*k*rest,1ll*m))/rest;
	
	for(int i = 1;i<=n;i++){
		sum-=a[i];
		m--;
		if(m<0) break;
		rest--;
		ans = max(ans,1.0*(sum+min(1ll*k*rest,1ll*m))/rest);
	}
	printf("%.10lf\n",ans);
	return 0;
}

```

## 结语
完结撒花！（如有不严谨之处还望大佬们帮忙指出）

---

## 作者：ZLCT (赞：0)

# CF1111B Average Superhero Gang Power
## 题目翻译
给定 $n$ 个数，可以进行 $m$ 次操作，每次都可以选择删除一个数或者把一个数 $+1$，其中每个数最多执行 $k$ 次 $+1$ 操作。问最后的平均值最大多少。
## solution
由于我们不可能对要删除的数进行 $+1$ 操作，所以我们可以钦定先进行删除操作。\
那么假设现在我们确定了进行 $x$ 次删除操作，我们考虑如何才能使答案更优。\
首先此时的总数（分母）是固定的，那我们可以把总和（分子）分成两部分：一部分是进行 $+1$ 操作添加的贡献，一部分是剩下 $n-x$ 个数原有的贡献。\
由于无论我们如何选剩下的数字，$+1$ 操作的贡献都是 $\min(m-x,k\times (n-x))$，所以我们剩下的数字肯定是越大越好，这样我们就可以先把数按升序排序，这样一定是取后 $n-x$ 个数。\
那么我们现在就可以去枚举 $x$ 并计算此时的答案，最终取最大值即可。\
现在还有一个小问题，如果每次都取后 $n-x$ 个，那时间复杂度会爆，这一点我们可以利用前/后缀和优化，也可以从小到大枚举 $x$，这样每次的数字和就只需要减去新删除的数就行了，甚至你直接开个树状数组或线段树也是可以的。\
总而言之这个题的处理还是比较简单随意的。
## code
```cpp
#include<bits/stdc++.h>
#define int long long
#define ld long double
using namespace std;
const int N=1e5+666;
int n,m,k,a[N],sum;
ld ans;
signed main(){
    cin>>n>>k>>m;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        sum+=a[i];
    }
    sort(a+1,a+1+n);
    ans=(ld)(sum+min(m,k*n))/(ld)n;
    for(int i=1;i<=min(n-1,m);++i){
        sum-=a[i];
        ans=max(ans,((ld)sum+(ld)min(m-i,k*(n-i)))/(ld)(n-i));
    }
    printf("%.10Lf\n",ans);
    return 0;
}
```

---

## 作者：_JF_ (赞：0)

[Link](https://www.luogu.com.cn/problem/CF1111B)

来一个细节很多，时间复杂度又劣的唐氏做法。

但是感觉比较容易想到，但是细节确实多。

观察到这个东西明显具有单调性，如果平均值越高，你要改的就越多，直接二分。

然后思考 `check`。

先对 $a$ 排序，考虑二分到了一个 $x$，分两种情况。

- 对于 $a_i>x$，我们把多的部分拿出来，记为 `sum`。
- 对于 $a_i<x$，我们贪心的从大到小把 `sum` 尽可能的丢给它。

如果丢不了？

我们还是贪心考虑，注意到我们对一个数加 $x$，相当于对平均数加上 $\frac{x}{len}$，所以我们可以整体考虑。

我们观察到对小的数加到平均数，需要耗费较多的操作，那我们枚举前 $x$ 个小的数去删除，剩下的数用加 $1$ 操作。判断次数和 $m$ 的关系即可。

细节特别多，可以结合代码进行观看。

在 `check` 时候又排序了一次，实现并不怎么精细，时间复杂度 $O(n \log^2 n)$。

都快做破防了，被 `conner case` 创没了/ll。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
#define double long double 
double b[N],c[N],a[N],G[N],s[N];
int n,k,m;
bool check(double x){
	double sum=0; int tot=0,lst=0,prelst=0;
	for(int i=1;i<=n;i++)	a[i]=b[i];
	for(int i=1;i<=n;i++)	c[i]=(double)(a[i])-x;
	if(c[n]<0){
		if(ceil(x-(double)(a[n]))>k)	return false;
		tot+=ceil(x-(double)(a[n])),c[n]=(a[n]+tot-x),prelst=tot;
		if(tot>m)	return  false;
	}
	for(int i=n;i>=1;i--){
		if(c[i]>=0)	sum+=c[i];
		else{lst=i; break;}
	}
	for(int i=lst;i>=1;i--){
		if(sum>=abs(c[i])){sum-=abs(c[i]),c[i]=0; continue;}	
		else if(sum<abs(c[i])&&sum>0)	c[i]+=sum,a[i]+=sum,sum=0;
		tot++;	
	}	
	if(tot<=m) return true;
	int dus=0; tot=prelst;
	for(int i=1;i<=n;i++){
		if(c[i]>=0)	break;
		if(ceil(abs(c[i]))>k)	tot++;
		else G[++dus]=a[i];
	}
//	for(int i=1;i<=dus;i++)	cout<<G[i]<<" ";
//	cout<<endl;
	sort(G+1,G+dus+1);
	for(int i=1;i<=dus;i++)	s[i]=s[i-1]+G[i];
	for(int i=0;i<=dus;i++){
		double pre=dus-(i+1)+1,eps=1e-7;
		double Lst=pre*x-(s[dus]-s[i]);
		int prenow=Lst;
//		cout<<Lst<<endl;
		if((pre*x-(s[dus]-s[i])-(double)prenow)>eps)	Lst=Lst+1.0;
		int now=i+tot+(int)Lst;
		if(now<=m)	return true;
	}
	return false;
}
//#define check(x) [&](){bool t=check(x);printf("x %Lf =%d\n",x,t);return t;}()
void Slove(){
	double l=0.0,r=1e9+10;
	while(abs(r-l)>1e-10){
		double mid=(l+r)/2;
		if(check(mid))	l=mid;
		else	r=mid;
	}
	cout<<fixed<<setprecision(15)<<l<<endl;
}
int main(){
	cin>>n>>k>>m;
	for(int i=1;i<=n;i++)	cin>>b[i];
	sort(b+1,b+n+1);
	Slove();
//	cout<<check(2.6666666667);
	return 0;
}
/*
3 3 2
2 2 2


*/ 
```

---

