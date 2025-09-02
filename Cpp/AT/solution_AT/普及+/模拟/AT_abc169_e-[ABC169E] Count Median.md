# [ABC169E] Count Median

## 题目描述

有 $N$ 个整数 $X_1, X_2, X_3,\cdots,X_N $，满足 $A_i \le X_i \le B_i$。

求 $X_1，X_2,\cdots,X_N$ 的中位数可能的不同值的数量。

## 样例 #1

### 输入

```
2
1 2
2 3```

### 输出

```
3```

## 样例 #2

### 输入

```
3
100 100
10 10000
1 1000000000```

### 输出

```
9991```

# 题解

## 作者：FL_sleake (赞：7)

### 题意简述

有 $N$ 个整数 $X_1, X_2, X_3,\cdots,X_N $，满足 $A_i \le X_i \le B_i$。

求 $X_1,X_2,\cdots,X_N$ 的中位数可能的不同值的数量。

### 解题思路

看到一些题解的 $N$ 为偶数时输出：

$$B_{n/2+1}+B_{n/2}-(A_{n/2+1}+A_{n/2})+1$$

有点懵，自己推了一下，估计是我脑回路和正常人不太一样吧。

当所有的 $X_i=A_i$ 时，中位数能取到最小值，我们设最小值为 $ans_1$。同理，所有 $X_i=B_i$ 时，中位数能取到最大值，我们设最大值为 $ans_2$。于是我们就确定了中位数的取值范围。后续的讨论默认已将 $A,B$ 排序。

$N$ 为奇数时，中位数一定是一个整数。而且我们可以通过调节 $X_i$，使得中位数变为 $ans_1$ 到 $ans_2$ 中的任意一个整数。所以此时答案为 $ans_1-ans_2+1$，其中 $ans_1=A_{n/2+1}$，$ans_2=B_{n/2+1}$。接下来重点说说偶数的情况。

$N$ 为偶数时，中位数可以是一个整数，也可以是一个整数加上 $0.5$。所以此时的中位数为介于 $ans_1$ 到 $ans_2$ 之间的，且为整数或者整数加上 $0.5$ 的数。我们来推一下式子（偶数情况下）。

根据 $ans_1$ 和 $ans_2$ 的定义，我们有：

$$ans_1= \frac{A_{n/2+1}+A_{n/2}}{2}$$

$$ans_2= \frac{B_{n/2+1}+B_{n/2}}{2}$$

最终答案就相当于一个公差为 $0.5$ 的等差数列介于 $ans_1$ 和 $ans_2$ 之间的项数，即：

$$ans= \frac{(ans_2-ans_1)}{0.5} +1=(ans_2-ans_1)\times2+1$$

然后把括号拆开，将 $ans_1,ans_2$ 代入，再移项，就得到了开头所说的：

$$ans=B_{n/2+1}+B_{n/2}-(A_{n/2+1}+A_{n/2})+1$$

### 代码示例

```cpp
#include<bits/stdc++.h>
using namespace std; 
#define int long long
int n,a[200010],b[200010]; 
signed main() {
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	if(n%2==1) cout<<b[n/2+1]-a[n/2+1]+1<<endl;
	else cout<<(b[n/2+1]+b[n/2])-(a[n/2+1]+a[n/2])+1<<endl;
	return 0;
}
```

---

## 作者：shinkuu (赞：1)

我不会做纸张题。

应该可以说是一个挺 Educational 的 skill。

首先考虑中位数的范围，明显是全取最小值的中位数到全取最大值的中位数。

通过一系列口胡容易发现，在这个范围内的整数（对于 $N$ 为偶数还有 $\frac{x}{2}$，$x$ 为整数）都可以通过增大其中的某一个数来得到。

然后数有多少个符合条件的数即可。

code：

```cpp
int n,e[N],d[N];
void solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&e[i],&d[i]);
	}
	sort(e+1,e+n+1);
	sort(d+1,d+n+1);
	if(n&1){
		printf("%d\n",max(0,d[(n+1)/2]-e[(n+1)/2]+1));
	}else{
		printf("%d\n",max(0,d[n/2]+d[n/2+1]-e[n/2]-e[n/2+1]+1));
	}
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)solve();
}
```

---

## 作者：Mierstan085 (赞：0)

CYEZ 模拟赛基本上 vp 了这一场，这题到时场切了，很好玩。

在对 $A, B$ 排序后考虑分类讨论：

1. $n$ 为奇数的情况下，显然，除了 $X_{(n+1)\div2}$，其他的并没有用，于是在这种情况下，答案的个数为 $B_{(n+1)\div2} - A_{(n+1)\div2} + 1$。
2. $n$ 为偶数的情况下就比较的有意思。容易发现，这种情况下的中位数要么是整数，要么是整数加二分之一。于是计算上下界，发现为 $[\frac{A_{n\div2} + A_{n\div2+1}}{2}, \frac{B_{n\div2} + B_{n\div2+1}}{2}]$，于是答案为 $(B_{n\div2} + B_{n\div2+1}) + (A_{n\div2} + A_{n\div2+1}) - 1$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 5;
int a[N], b[N];

signed main(){
	// freopen("count.in", "r", stdin);
	// freopen("count.out", "w", stdout);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i ++) cin >> a[i] >> b[i];
	sort(a + 1, a + n + 1); sort(b + 1, b + n + 1);
	cout << (
			n % 2 == 1
	 	? 	(b[n / 2 + 1] - a[n / 2 + 1] + 1) 
		: 	((b[n / 2 + 1] + b[n / 2]) 
		-	(a[n / 2 + 1] + a[n / 2]) + 1)
	);
}
```

~~CYEZ 什么唐诗键盘。~~

---

## 作者：Tang_poetry_syndrome (赞：0)

## [ABC169E] Count Median

[洛谷题面](https://www.luogu.com.cn/problem/AT_abc169_e) [Atcoder 题面](https://atcoder.jp/contests/abc169/tasks/abc169_e)

### 思路

将 $A,B$ 排序，没有区间重合下，设序列 $X$ 的中位数为 $Medium(X)$，容易得出中位数区间在全取最小值的中位数到全取最大值的中位数，答案区间即为 $[Medium(A),Medium(B)]$。  
特别的，当序列长度为偶数时，中位数有两个，考虑分类讨论，我们默认 $A,B$ 经过了排序，即：  
1.  长度为奇数，则区间为 $B_{(n+1)\div2}-A_{(n+1)\div2}$。  

2. 长度为偶数，则区间为 $B_{n\div2}-A_{n\div2}$ 与 $B_{n\div2+1}-A_{n\div2+1}$。  

最后考虑是否会出现区间长度为负数的情况：设中位数下标为 $\lfloor \frac{n+1}{2} \rfloor$，使区间长度为负数，需让在区间 $[1,\lfloor \frac{n-1}{2} \rfloor]$ 的区间起点数少于区间终点数，但区间起点显然在终点之前，因此不会出现区间长度为负的情况。  

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define f(i,j,k) for(register int i=j;i<=k;i++)
#define g(i,j,k) for(register int i=j;i>=k;i--)
#define pb push_back
#define endl '\n'
const int N=1e6+10,mod=1e9+7;
ll n,a[N],b[N];
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
    f(i,1,n)cin>>a[i]>>b[i];
    sort(a+1,a+n+1);
    sort(b+1,b+n+1);
    if(n%2==0)cout<<b[n/2]+b[n/2+1]-a[n/2]-a[n/2+1]+1;
    else cout<<b[(n+1)/2]-a[(n+1)/2]+1;
	return 0;
}

```

[提交记录](https://atcoder.jp/contests/abc169/submissions/46467498)

---

## 作者：Erica_N_Contina (赞：0)

# [ABC169E] Count Median



没什么难度的题目。

## 思路

我们分情况看看。

首先是以下情况，没有区间重合，很容易知道我们把 $A$ 排序，$B$ 排序，答案区间即为 $ [A$ 中的中位数，$B$ 中的中位数 $]$。


现在区间有重叠，我们发现答案区间还是为 $[A$ 中的中位数，$B$ 中的中位数 $]$。


所以本题的答案区间就是 $[A$ 中的中位数，$B$ 中的中位数 $]$。

特别低，如果区间有偶数个，则一个是中间两个区间都是答案区间。即答案区间应该为 $[A_{n\div 2},B_{n\div 2}][A_{n\div 2+1},B_{n\div 2+1}]$。

## 思考

区间的长度有没有可能是负数？即 $A$ 中的中位数 $>B$ 中的中位数的情况有没有可能出现？

很显然是不可能的。假设一个中位数的下标为 $n\div 2$，那么要出现上面的情况，我们就要让 $n\div 2$ 左边的区间起点数量少于区间终点数量。然鹅我们又知道每个区间的起点一定在终点前面，所以这种情况不存在。

## 代码

```C++

ll n,m,ans;
ll a[N],b[N];

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
	}
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	if(n%2){
		cout<<b[n+1>>1]-a[n+1>>1]+1<<endl;
	}else{
		cout<<b[n>>1+1]+b[n>>1]-a[n>>1+1]-a[n>>1]+1<<endl;
	}
	return 0;
}

```






---

## 作者：jnxx_zhuyueqi (赞：0)

本蒟蒻的第一篇题解，希望各位支持。

这道题只需要把 $a$ 数组和 $b$ 数组分别排序，再按照题目描述输出中位数即可，本质上是模拟题，算上排序时间复杂度 $O(n \log n)$。

因为这题太简单，所以加上一个手写的快读快写。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define getchar_unlocked getchar
int a[200005],b[200005],n,cnt,ans,len;
int scan(){
    int k=0,f=1;
    char c=getchar_unlocked();
    while(c<'0'||c>'9'){
        if(c=='-') f=-f;
        c=getchar_unlocked();
    }
    while(c>='0'&&c<='9'){
    	k=k*10+c-'0';
		c=getchar_unlocked();
	}
    return k*f;
}
void print(int x){
    if(x<0){
    	putchar('-');
		x=-x;
	}
    if(x<10) putchar(x+'0');
    else{
    	print(x/10);
		putchar(x%10+'0');
	}
}
int main(){
	//freopen("count.in","r",stdin);
	//freopen("count.out","w",stdout);
	n=scan();
	for(int i=1;i<=n;i++) a[i]=scan(),b[i]=scan();
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	if(n%2==0){
		print(b[n/2]+b[n/2+1]-a[n/2]-a[n/2+1]+1);
	}else{
		print(b[(n+1)/2]-a[(n+1)/2]+1);
	}
	return 0;
}
```

---

## 作者：Symbolize (赞：0)

# $\tt{Solution}$

很多时候还是不能被题目的定义给捆绑了，就像这道题，虽说 $a_i,b_i$ 共同限制一个数，但不意味着，它们不能分开来排序。回到题目，要想要知道个数，那首先不难证明，最大的可能与最小的可能之间的所有整数都是可能的，而形如 $\frac{2k+1}{2}$ 的在最大可能与最小可能之间的数，在 $n$ 为偶数的时候可能，因为只有当有两个数的平均的时候才出现这种情况。

接下来思考如何求范围，那实际上可以吧两个限制拆开，分别来求，排个序，直接取中位数就完了，最后计算中间有多少个可以取的答案就不细讲了，分类讨论即可，详情可以看代码。

```cpp
/*
	Luogu name: Symbolize
	Luogu uid: 672793
*/
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(register int i=l;i<=r;++i)
#define rep2(i,l,r) for(register int i=l;i>=r;--i)
#define rep3(i,x,y,z) for(register int i=x[y];~i;i=z[i])
#define rep4(i,x) for(auto i:x)
#define debug() puts("----------")
const int N=2e5+10;
const int inf=0x3f3f3f3f3f3f3f3f;
using namespace std;
int n,a[N],b[N];
int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return f*x;
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	n=read();
	rep1(i,1,n) a[i]=read(),b[i]=read();
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	int ans;
	if(n&1) ans=b[n/2+1]-a[n/2+1]+1;
	else ans=b[n/2+1]+b[n/2]-a[n/2+1]-a[n/2]+1;//计算中位数的除2，与小数带来的翻倍计算抵消了 
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：UperFicial (赞：0)

合法的中位数一定是一段连续的区间，那么我们可以求出这个区间的左右端点，也就是最小/最大可能的中位数。

贪心考虑，要使中位数尽量小，肯定是每个数都取最小，那么左端点即为 $a$ 的中位数，同理，要使中位数尽量大，那么右端点即为 $b$ 的中位数。

那么就只需要分 $n$ 的奇偶性讨论一下中位数的位置即可。

---

