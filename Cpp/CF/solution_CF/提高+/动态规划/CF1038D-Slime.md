# Slime

## 题目描述

### 题目大意：
有$n$只史莱姆qwq，每只史莱姆有一个分数，每次一只史莱姆可以吞掉左边的或者右边的相邻史莱姆（要是有的话），然后ta的分数会减去被吞的史莱姆的分数，问最后剩下的史莱姆分数最大为多少

## 样例 #1

### 输入

```
4
2 1 2 1
```

### 输出

```
4```

## 样例 #2

### 输入

```
5
0 -1 -1 -1 -1
```

### 输出

```
4```

# 题解

## 作者：Legitimity (赞：6)

首先我们要考虑一下一只史莱姆只能吞左右的两只，稍微思考一下会发现这个限制一点用都没有，因为只要调整吃的顺序就能让任意两种史莱姆“间接”的吃和被吃。

那么就直接考虑没有限制。我们可以发现，吃史莱姆就相当于把被吃的史莱姆的符号改变，经过 $n-1$ 轮吃和被吃的关系后就相当于把这个序列中的一些数的符号改变。

具体能改变多少呢？第 $i$ 轮会改变 $i$ 只，总共改变了:
 $ \sum^{n-1}_{i=1}i=\frac{n\times (n-1)}{2}$  次，但总共只有 $n$ 个数，多余的符号会互相抵消。而我们发现这个数总是奇数，那么抵消之后至多改变 $n-1$ 个数的符号，至少改变 $1$ 个数的符号。
 
 那么问题就转化为改变序列 $a$ 中 $k\in[1,n)$ 个数的符号，使得 $\sum^n_{i=1}a_i$ 最大，排序之后扫一遍就行了。
 
 代码（别忘了特判 $n=1$）：
 ```cpp
#include<bits/stdc++.h>
using namespace std;
#define rg register
#define ll long long
#define inf 0x7f7f7f7f
inline ll read(){
	rg ll ret=0,f=0;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=1;ch=getchar();}
    while(isdigit(ch)){ret=ret*10+ch-48;ch=getchar();}
    return f?-ret:ret;
}
ll n,a[500005],ans;
int main(){
    n=read(); 
    for(rg int i=1;i<=n;++i)
    	a[i]=read();
    if(n==1) return 0*printf("%lld",a[1]);
    sort(a+1,a+1+n);
    ans+=-a[1];
    for(rg int i=2;i<n;++i) ans+=max(-a[i],a[i]);
    ans+=a[n];
    printf("%lld",ans);
    return 0;
}
```


---

## 作者：斜揽残箫 (赞：3)

## Description

一个序列中不断取出两个数 $A,B$ 进行 $A - B$，再把 $A - B$ 丢进去，最大化最后剩下的一个数。

好像是比赛原题，题还没加先来写一下这篇。

## Solution

首先左右两边不是左右两只史莱姆，而是左右两边所有的。

我们显然要得出一个最大数，一个最小数，使得答案最大。

因为有正数和负数，要分类讨论 ： 

先假设一个由小到大的序列 $A$。

+ 全为非负数

我们可以先排序，用最小的那一只减去除最大的以外的所有数，最后再用最大的减去这个数的，即 ： 

$$
\begin{aligned}
Ans &= A_n - (A_1 - \sum_{i = 2} ^ {n - 1}A_i)\\&=\sum_{i = 2} ^ n - A_1
\end{aligned}
$$

因为现在整个序列全为正数，我们要确保最大，因为大的数字对答案贡献大，不能枚举相邻两项来是答案减小，构造一个负数，来用它减去除最大的以外的全部正数，就可以得到最小的解，再用最大的数减去即可。

+ 全为负数

和全为正数一样，我们可以反过来想，我们能不能用两个最大的数构造一个正数，再用这个数减去其他数，答案是肯定的，即

$$
\begin{aligned}
Ans &= (A_n - A_{n - 1}) - \sum_{i = 1} ^ {n - 2}A_i \\ &= A_n - \sum_{i = 1} ^ {n - 1}A_i
\end{aligned}
$$

证明同上。

+ 数有正有负

我们发现这种情况下，我们完全可以用所有负数减去除最大值以外的所有正数，再用最大数一一减去这些负数。

假设到从 $1 \cdots j$ 为负数，从 $j + 1 \cdots n$ 为正数。

$$
\begin{aligned}
Ans &= A_{n} - (\sum_{i = 1} ^ jA_i - \sum_{i = j + 1} ^ {n - 1}A_i)\\&= \sum_{i = j + 1} ^ nA_i - \sum_{i = 1} ^ j A_i\\&=\sum_{i = 1} ^ n \left|A_i\right
|\end{aligned}
$$

实在看不懂可以自己手膜一下。

还有就是要判断一个数的情况，这种情况下只能输出原数。

## Code
```cpp
#include <cstdio>
#include <cmath>
#include <iostream>
#include <cstring>
#include <algorithm>
#define int long long
using namespace std;
const int Maxk = 500010;
int a[Maxk],Ans,n,sum,tot;
inline int read()
{
	int s = 0, f = 0;char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
	return f ? -s : s;
}
int Abs(int x) {return x > 0 ? x : -x;}
signed main()
{
  n = read();
  for(int i = 1;i <= n;i ++) {
    a[i] = read();
    sum += a[i];
    tot += Abs(a[i]);
  }
  if(n == 1) {
    cout << a[1] << endl;
    return 0;
  }
  sort(a + 1,a + n + 1);
  if(a[1] >= 0) Ans = sum - a[1] - a[1];
  else if(a[n] < 0) Ans = a[n] + a[n] - sum;
  else Ans = tot;
  cout << Ans << endl;
  return 0;
}
```


---

## 作者：flora715 (赞：3)

### 题意
有n个史莱姆，每一个史莱姆都可以吃掉相邻的史莱姆，使得自己的值改变。当x吃掉y的时候，x的值变为x-y，问最后所剩下的史莱姆最大是多少。

### 分析

1.如果序列中全部都是正数：
```cpp
假设a2<a1,被减去的最小值为a2-a1,a2-a1-a3,a2-a1-a3-a4...
直到ans=an-(a2-a1-a3-a4-...-a(n-1))=sum-2*a2。
```
a2取序列中的min即可。

2.如果序列中全部是负数：
```cpp
ans=a2-a1-a3-a4-...-a(n-1)-an=(-sum)+2*a2。
```
发现ans=所有数的绝对值的和减去2*max(为负数)

既有正数又有负数的时候：输出所有元素的绝对值的和。

注意：对于n等于1和2的情况，要特判。

### 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<deque>
#include<cmath>
using namespace std;
typedef long long ll;

void reads(ll &x){ //读入优化（正负整数）
	int fx=1;x=0;char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')fx=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
	x*=fx; //正负号
}

const int maxn=500019;

ll a[maxn];
 
int main(){
	ll n,sum=0; reads(n);
	ll minn=0x3f3f3f3f,maxx=-0x3f3f3f3f;
	for(ll i=0;i<n;i++){
		reads(a[i]); sum+=abs(a[i]);
		minn=min(minn,a[i]); maxx=max(maxx,a[i]);
	}
	if(n==1){ cout<<a[0]<<endl; return 0; }
	if(n==2){ cout<<max(a[0]-a[1],a[1]-a[0])<<endl; return 0; }
	if(minn>0) sum-=2*minn; //全是正数
	else if(maxx<0) sum-=2*abs(maxx); //全是负数
	cout<<sum<<endl; return 0; //如果有正数也有负数，直接取sum
}
```

---

## 作者：VenusM1nT (赞：2)

结论题。  
声明：本题解定义 $0\in \mathbb{Z}^+$，即 $0$ 也是一个正数。  
首先考虑一般情况下，即一些负数和一些正数的情况，假定整数有 $m$ 个，那么可以用一个负数减去 $m-1$ 个正数，再用剩下的 $1$ 个正数减去所有负数。尽管具体操作可能并不如上述那么简洁，但要求的只是答案而已，即为 $\sum|a_i|$。  
此时出现两种特殊情况：全为正数 和 全为负数，略加思考发现必须舍弃其中一个数的贡献才能获得最大贡献，于是选择舍弃绝对值最小的数，将其贡献减去，加上剩下数的贡献即可。  
注意特判 $n=1$ 的情况。
```cpp
#include<bits/stdc++.h>
#define MAXN 500005
#define reg register
#define inl inline
#define int long long
using namespace std;
int n,a[MAXN],ans,z;
signed main()
{
	ios::sync_with_stdio(0);
	cin>>n;
	for(reg int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]>=0) z++;
	}
	if(n==1)
	{
		cout<<a[1]<<endl;
		return 0;
	}
	sort(a+1,a+n+1);
	if(!z || z==n)
	{
		if(!z)
		{
			for(reg int i=1;i<=n-1;i++) ans-=a[i];
			ans+=a[n];
		}
		else if(z==n)
		{
			for(reg int i=2;i<=n;i++) ans+=a[i];
			ans-=a[1];
		}
	}
	else for(reg int i=1;i<=n;i++) ans+=abs(a[i]);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：傅思维666 (赞：1)

## 题目大意：

一个数列，相邻的数可以相减，问减到最后一个数后最后的那个数可能的最大值是多少。

## 题解：

这是一道数学推导问题：

首先我们分类讨论：这题一共有三种大的情况：

全是正数，全是负数，有正数也有负数。

我们来看：

假如有正有负，那么我们可以用负数减去正数，让其越减越小，但绝对值越大，最后用正数减去，就能得到最大的值，这样我们虽然一直在减来减去，但是绝对值一直没有变，最后输出的答案也是“没有损耗”的，所以，假如**有正有负**，最后的答案就应该是**所有数绝对值的和**。

假如全是正数，那么我们通过刚才的推理考虑，一定要产生负数，最后用正数减去负数得到一个更大的正数，所以我们尽可能地用小的减去大的。同理，如果全是负的，就用大的减去小的。所以，假如**全正全负**，最后的答案就应该是**所有数绝对值的和减去所有数中绝对值最小的数的二倍**。



代码：（注意特判n=1的情况）

```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
#define ll long long
using namespace std;
int n;
int pos,neg;
ll sum,minn=1e9;
int main()
{
    scanf("%d",&n);
    if(n==1)
    {
        ll a;
        scanf("%lld",&a);
        printf("%lld",a);
        return 0;
    }
    for(int i=1;i<=n;i++)
    {
        ll a;
        scanf("%lld",&a);
        if(a>0)
            pos++;
        if(a<0)
            neg++;
        sum+=abs(a);
        minn=min(minn,abs(a));
    }
    if(pos>0 && neg>0)
        printf("%lld",sum);
    else
        printf("%lld",sum-minn*2);
    return 0;
}
````

---

## 作者：vincentcn512 (赞：1)

**只有一组**相邻两数只能求差的绝对值，**其他数都可以**取绝对值求和。所以暴力跑两遍for循环应该是最好理解的了。


------------
注意**n==1**的情况


------------
```cpp
#include<bits/stdc++.h>
#define gc() getchar()//caution!!!
#define ll long long
using namespace std;
template<class T>
inline void read(T &aa) {
  register T k=0,f=1;
  register char c=gc();
  for (;!isdigit(c);c=gc()) if(c=='-')f=-1;
  for (;isdigit(c);c=gc()) k=(k<<3)+(k<<1)+(c-'0');
  aa=k*f;
}
ll a[500005];
ll b[500005];
ll n,m;
ll sum;
ll ans=0;
int main(){
	read(n);
	int maxn;
	if(n==1){
		read(ans);
		printf("%lld",ans);
		return 0;
	}
	for(int i=1;i<=n;++i){
		read(a[i]);
		b[i]=abs(a[i]);
		sum+=b[i];
	}
	for(int i=1;i<n;++i){
		ans=max(ans,sum-(b[i]+b[i+1])+abs(a[i]-a[i+1]));
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Dispwnl (赞：1)

发现每个分数结果中只有正负性变化，所以考虑不同情况符号该怎么分配

- 如果全是正数，肯定要有一个数变成负数，然后求和，所以最大分数就是总和减去最小的正数
- 如果全是负数，肯定要有一个数不变，其他数取正，然后求和，所以最大分数就是绝对值总和加上最大的负数
- 如果有正有负，可以综上考虑，正数可以被负数同化成负数，而负数情况中不变的数可以随意选一个正数，所以最大分数就是所有史莱姆绝对值的和

比赛时忘加了负数情况然后漂亮的$fst$了QAQ

代码：
```
# include<iostream>
# include<cstring>
# include<cstdlib>
# include<cstdio>
# include<algorithm>
# define LL long long
using namespace std;
const int MAX=5e5+1;
int n,minn=1e9,maxn=-1e9;
LL ans;
int a[MAX];
int main()
{
	scanf("%d",&n);
	bool fl=0,fl1=0;
	for(int i=1;i<=n;++i)
	  {
	  	scanf("%d",&a[i]),ans+=abs(a[i]);
	  	if(a[i]<0) fl=1,maxn=max(maxn,a[i]);
	  	else fl1=1,minn=min(minn,a[i]);
	  }
	if(n==1) return printf("%d",a[1]),0;
	if(!fl) return cout<<ans-2*minn,0;
	if(!fl1) return cout<<ans+2*maxn,0;
	if(fl&&fl1) return cout<<ans,0;
}
```

---

## 作者：Durancer (赞：0)

### 前言

这是一道比赛题的原题（确信，但是我只推出了最终结论的前身。

### 思路

分情况讨论

1、全都是正数

因为是减法操作，那么我们就尽量的使数的贡献全部加进去，如果不可以，那么就使损耗降到最小。

注意看题面这是广义的左右方向。

那么选排序是重点。

我们看序列（升序排列）特别鸣谢 Szt 的数据支持：

$$\langle 1,5,6,10\rangle$$

一开始，我们要是更大的数尽量多的对答案有贡献，所以可以考虑先把小的数的贡献减少，以此来增加大数的贡献，很显然，是减法，那么减到最后一个数之前，我们要尽量是除了最后以外的那些数的减法运算的结果小，因为是减法，所以越小到最后贡献值就更大 （最好是负数，贡献全部）

那么就取 $1,5$，因为要向负数迈进，所以要小数被大数减去。

$$num=1-5=-4$$

至于减到最后一个数之前，一定要是这个数 $num$ 变得更小，那么就直接让 $num$ 被 $a_2…a_{n-1}$ 减去。

最终的出来的是 $num=-10$ 此时 $6$ 的贡献是达到了最大，因为最后要构造最大值，那么最后一次运算一定是大数减小数。

所以有：

$$ans=10-(-10)=20$$ 

可以证明这是最大的。

化成广义的式子就是：

$$ans=a_n-(a_1-a_2-…-a_{n-1})$$

$$ans=-a_1+a_2+……a_{n}=-a_1-a_1+a_1+a_2+…+a_n$$

$$ans=sum-2\times a_1$$

2、全部都是负数

还是按照上面的思路来，这一次是使绝对值大的数贡献的越多，那么就把绝对值最小的两个数都做减法运算。也就是最大的两个数。

因为要是除了这两个数之外的所有数的贡献达到最大，那么肯定是大的减去小的构造一个正数，然后其他的减负运算时就可以全部贡献他的绝对值了。

广义的式子就是：

$$ans=a_n-a_{n-1}-a_{n-2}-…-a_1$$

$$ans=a_n+a_n-a_n-a_{n-1}-…a_1$$

$$ans=-sum+2\times a_n $$

3、其他情况

可以知道，如果出现 $0$ 不管是有正数还是负数，都可以把他们的绝对值全部贡献上去，所以直接是数列绝对值的总和

### 代码实现

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<stack>
#include<map>
#include<cmath>
#define int long long 
using namespace std;
const int N=5e5+9;
int a[N];
int n;
int ans;
bool sun,moon;//正负 
int read()
{
	int f=1,x=0;
	char s=getchar();
	while(s<'0'||s>'9')
	{
		if(s=='-')
			f=-1;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+(s^'0');
		s=getchar();
	}
	return f*x;
}
signed main()
{
	n=read();
	int tol=0; 
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		if(a[i]<0) moon=true;
		if(a[i]>0) sun=true;
		tol+=abs(a[i]);
	}
	sort(a+1,a+1+n);
	if(n==1) cout<<a[1]<<endl;
	else if(n==2) cout<<max(a[1]-a[2],a[2]-a[1])<<endl;
	else 
	{
		if(sun&&!moon)//全为正
		{
			//cout<<tol<<endl;
			printf("%lld\n",tol-2*a[1]);
			return 0;	
		} 
		if(moon&&!sun)//全为负数
		{
			printf("%lld\n",tol+2*a[n]);
			return 0;
		} 
		else //都有
		{
			printf("%lld\n",tol);
			return 0;
		} 
	}
	return 0;
} 
```



---

## 作者：_lfxxx_ (赞：0)

**题目传送门：[CF1038D Slime](https://www.luogu.com.cn/problem/CF1038D)**
### 题意：
有一个长度为 $n$ 的序列 $v$ ，每次可以将两个数 $a$ , $b$ （相邻的限制条件其实没用，因为我们可以让两个数间接的相减）替换成 $a-b$ 。问当还剩一个数时，最大数是多少。
### 思路：
不难看出，这道题要用贪心解决。因为 $a-b$ 相当于 $a+(-b)$ ，说明你必须将这个数列中的 $1$ 个数变号， $1$ 个数不变号（除序列中只有 $1$ 个数外）。要想使值最大，就要让变号的数尽量小，不变号尽量大，其他全取绝对值。

也许上面的内容有些难懂，我来结合样例说明一下。

```
4
2 1 2 1
```
这里面最小的是 $1$ ，最大是 $2$ ，其他为 $1$ 和 $2$ 。

那么答案就为 $-1+2+|1|+|2|$ 即为 $4$ 。

至于如何加减我们不需要考虑，因为总有一种方法能有这样的效果。

如果序列中只有 $1$ 个数，那么答案就为那个数。

当你理解上面的内容后，这道题就变得十分简单了。
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[500001];
int main(){
	int n;
	long long ans;
	cin>>n;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
    if(n!=1){//不是1
	    sort(a+1,a+1+n);//排序为了找到最大数与最小数
	    ans=a[n]-a[1];
	    for(int i=2;i<n;i++)
		    ans+=abs(a[i]);//其他全加上它们的绝对值
    }
    else//是1
        ans=a[1];
	cout<<ans<<endl;
	return 0;
}
```


---

