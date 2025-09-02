# Interacdive Problem

## 题目描述

This problem is interactive.

We decided to play a game with you and guess the number $ x $ ( $ 1 \le x < n $ ), where you know the number $ n $ .

You can make queries like this:

- + c: this command assigns $ x = x + c $ ( $ 1 \le c < n $ ) and then returns you the value $ \lfloor\frac{x}{n}\rfloor $ ( $ x $ divide by $ n $ and round down).

You win if you guess the current number with no more than $ 10 $ queries.

## 说明/提示

In the first sample initially $ x = 2 $ . After the first query $ x = 3 $ , $ \lfloor\frac{x}{n}\rfloor = 1 $ .

In the second sample also initially $ x = 2 $ . After the first query $ x = 3 $ , $ \lfloor\frac{x}{n}\rfloor = 0 $ . After the second query $ x = 4 $ , $ \lfloor\frac{x}{n}\rfloor = 0 $ . After the third query $ x=5 $ , $ \lfloor\frac{x}{n}\rfloor = 1 $ .

## 样例 #1

### 输入

```
3

1```

### 输出

```
+ 1

! 3```

## 样例 #2

### 输入

```
5

0

0

1```

### 输出

```
+ 1

+ 1

+ 1

! 5```

## 样例 #3

### 输入

```
10

0

0

1

2```

### 输出

```
+ 2

+ 2

+ 3

+ 8

! 20```

# 题解

## 作者：AFewSuns (赞：6)

**CF764 Div.3（VP） 做题记录**

- A. plus One on the Subset

- B. Make AP

- C. Division by Two and Permutation

- D. Palindromes Coloring

- E. Masha-forgetful

- $\color{red}\texttt{F. Interacdive Problem}$

- G. MinOr Tree

### 题目大意

交互题，一开始有一个值 $x$。你可以询问不超过 $10$ 次，每次询问如下：

`+ c` 表示将 $x \leftarrow x+c$，然后程序会返回给你 $\lfloor\frac{x}{n}\rfloor$ 的值。你要保证 $1 \leq c < n$。

最后输出 `! x` 表示你得到了这个 $x$ **最终**的值。

比如 $x=2,n=3$ 时，你输出了 `? 2`，会返回 $1$，此时如果得到答案应输出 `! 4`

$1 \leq x < n,2 < n \leq 1000$

### 题目分析

我们稍微改一下题面，如果 `+ c` 不会改变 $x$ 的值，而是返回 $\lfloor\frac{x+c}{n}\rfloor$ 呢？

因为 $1 \leq x < n$，所以 $\lfloor\frac{x}{n}\rfloor=0$。当 $\lfloor\frac{x+c}{n}\rfloor=1$ 时，说明 $x+c \geq n$，$x \geq n-c$。

我们可以利用这个性质二分，令 $c=n-mid$，如果返回 $1$ 说明 $x \geq mid$，否则 $x < mid$。这样也能保证 $1 \leq c < n$,询问次数为 $\log x$ 次，不超过 $10$ 次。

回到原题，$x$ 实际上是在不断变化的，所以 $\lfloor\frac{x}{n}\rfloor$ 也在变化，我们不能单纯的令 $c = n-mid$。难道二分就不行了吗？

实际上，我们所用到的是 $\lfloor\frac{x}{n}\rfloor$ 与 $\lfloor\frac{x+c}{n}\rfloor$ 的变化。假设 $\lfloor\frac{x}{n}\rfloor=k$，如果 $\lfloor\frac{x+c}{n}\rfloor$ 返回了 $k+1$，我们一样能够判断出 $x$ 与 $mid$ 的关系。

为了避免歧义，我们令 $x_0$ 为一开始要猜的数。因为 $x_0$ 始终不变，所以我们的目的其实是在二分 $x_0$。

假设 $x$ 在原来的基础上增加了 $sum$，即 $x=x_0+sum$，这个 $sum$ 我们是可以确定的。为了确定 $x_0$ 与 $mid$ 的关系，我们需要让 $mid+sum+c=(k+1)\times n$，同时为了保证 $1 \leq c < n$，我们令 $c=(-mid-sum) \bmod n$。这时 $mid$ 就成了变化的分界点。

判断返回的值是否等于 $\frac{mid+sum+c}{n}$ 即可，最后的答案为 $x_0+sum$。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define fl fflush(stdout)//记得清空缓存 
using namespace std;
ll n,sum=0;
int main(){
	scanf("%lld",&n);
	ll l=1,r=n;
	while(l<r){
		ll mid=(l+r+1)>>1,c=(10000*n-mid-sum)%n,tmp;//确定 c=(-mid-sum) mod n 
		printf("+ %lld\n",c);
		fl;
		scanf("%lld",&tmp);
		if(tmp==(mid+sum+c)/n) l=mid;//如果相等，那么x0>=mid 
		else r=mid-1;
		sum+=c;
	}
	printf("! %lld",l+sum);//记得要加上sum 
	fl;
	return 0;
}
```

---

## 作者：清烛 (赞：3)

## Description
交互题，猜数字。给定一个正整数 $n$（$2 < n\le 1000$），要猜一个整数 $x$ 满足 $1\le x < n$。可以进行如下操作：

- `+ c`，使得 $x:=x + c$，然后交互器返回 $\displaystyle\left\lfloor\frac{x}{n}\right\rfloor$ 的值。
- `! x`，输出答案，**当前的** $x$ 的值。

最多 $10$ 次询问。
## Solution
是一道比较清新的二分交互！

直觉告诉我们，$2^{10} = 1024$，所以我们考虑二分出这个 $x$，我们只需要每次对二分左右端点同时加上我们给交互库加上的 $c$ 就可以了。

我们的思路是尽可能把当前的 $x$ 往其上面的第一个 $n$ 的倍数去凑，所以每次二分的时候加上的都是 $n - mid\bmod n$。然后就可以根据交互库返回的值来一步步框死范围。

## Implementation
```cpp
int add(int x) {
    cout << "+ " << x << endl;
    int res; cin >> res;
    return res;
}

int main() {
    int n; cin >> n;
    int l = 1, r = n;
    while (l < r - 1) {
        int mid = (l + r) >> 1;
        int a = n - mid % n;
        int res = add(a);
        l += a, r += a, mid += a;
        if (res == l / n) r = mid;
        else l = mid; 
    }
    cout << "! " << l << endl;
    return 0;
}
```

---

## 作者：rui_er (赞：2)

显然 $10\approx\log_210^3$，因此可以盲猜二分（

正经一点，每次询问后我们就知道了 $\lfloor\frac{x}{n}\rfloor$，另外 $n$ 在一开始给出，我们就只需要知道 $x\bmod n$ 了。

假设我们知道 $x\bmod n$ 在区间 $[l,r)$ 中（显然初始时 $l=0,r=n$），我们需要知道它到底在 $m=\lfloor\frac{l+r}{2}\rfloor$ 的哪一边。令 $k=n-m$，我们可以使 $x\gets x+k$，这样如果余数在 $[l,m)$，那么商数不会变，否则会增加一。利用这个性质，我们就可以二分出余数，从而求出 $x$ 的值了。

实现的时候跟上面有一点不同，但总体思路差不多，可以参考一下：

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
#define debug printf("Running %s on line %d...\n",__FUNCTION__,__LINE__)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;

int n;
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}
int ask(int x) {
	printf("+ %d\n", x);
	fflush(stdout);
	scanf("%d", &x);
	return x;
}
void give(int x) {
	printf("! %d\n", x);
	fflush(stdout);
}

int main() {
	scanf("%d", &n);
	int L = 1, R = n;
	while(L + 1 < R) {
		int M = (L + R) >> 1;
		int diff = n - M % n;
		if(ask(diff) == (L + diff) / n) R = M;
		else L = M;
		L += diff; R += diff;
	}
	give(L);
	return 0;
}
```

---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 2000}$

---
### 解题思路：

显然是二分，关键是如何二分。

首先可以确定二分的上界 $n-1$，下界为 $1$。考虑判断实际的数与二分中点 $mid$ 的大小关系，设当前已经相对原来的数增加了 $tot$，则如果加上 $n-((tot+mid)\bmod n)$ 如果当前数不比 $mid$ 小，则会相对之前的答案增加一（一开始什么都没有的时候答案是 $0$），否则就说明当前数比 $mid$ 小。

这样每一次的范围缩小一半，几乎是卡着上限过去的，需要注意细节。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
int l,r,n,mid,tot,ans,last,p;
int main(){
	scanf("%d",&n);
	l=1;r=n-1;p=1;
	while(l<=r){
		mid=(l+r+1)/2;
		printf("+ %d\n",n-(tot+mid)%n);
		fflush(stdout);
		scanf("%d",&ans);
		if(ans>last)p=mid,l=mid+1;
		else r=mid-1;
		tot+=n-(tot+mid)%n;
		last=ans;
	}
	printf("! %d\n",tot+p);
	return 0-0;
}
```



---

## 作者：Day_Tao (赞：0)

有意思的交互题。

这个数据范围显然二分，接着我们考虑如何二分。

我们设 $[l,r]$ 为模 $n$ 意义下当前 $x$ 可以确定的取值区间，$mid$ 为 $\lfloor\frac{l+r}{2}\rfloor$，$res$ 为当前的 $\lfloor\frac{x}{n}\rfloor$ 。考虑加上一个数可以区分出 $[l,mid]$ 和 $[mid+1,r]$，这个数我们就选择 $n-mid-1$。对于 $[l,mid]$ 返回的 $res$ 仍然不变，对于 $[mid+1,r]$ 返回的 $res$ 会增加 $1$。这两种情况分别对应的区间为 $[l+n-mid-1,\frac{r+n-mid-1+l+n-mid-1}{2}]$ 和 $[0,r-mid-1]$。就做完了。

code：

```cpp
int n,l,r,res;inline int qu(int x){pc('+'),pc(' '),cout<<x<<endl,cin>>x;return x;}
inline void an(int x){pc('!'),pc(' '),cout<<x<<endl;}
inline void SOLVE(){
	n=rd(),l=1,r=n-1;while(l<r){
		int mid=(l+r)>>1,x=qu(n-mid-1);
		if(x>res)res=x,l=0,r=r-mid-1;
		else l+=n-mid-1,r+=n-mid-1,r=(l+r)>>1;
	}an(l+res*n);
	return ;
}
```

---

## 作者：Wind_love (赞：0)

# CF1624 F Interacdive Problem
CF 2000 分。  
先简述下思路：  
其实就是每次存储下加进去的值，  
然后通过对方的返回 计算下一次加入的值。  
这里的二分是通过控制加的值逐渐向答案靠近的。  
假设 $x$ 加了 $plus$，则我们需要让 $mid+plus+c=(k+1)\times n$，为了符合题目要求，让 $c=(-mid-plus)\bmod n$ 最后判断是否为 $\frac{mid+plus+c}{n}$ 即可，答案别忘了加 $plus$。
## 代码如下
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;//命名空间
int main(){
    int n;//定义题目中的n
    scanf("%d",&n);
    int sum=0;//这里的sum是储存增加的值
    int l=1,r=n;//二分的左右指针
    while(l<r){//1到n的二分查找
        int mid=(l+r+1)/2;//mid向大数靠近 
        int temp=(114514*n-mid-sum)%n;//114514*n是为了让temp在结果不变的情况下不为负数
        printf("+ %d\n",temp);//输出加的数
        fflush(stdout);//交互题特性 清空缓存
        int t;
        scanf("%d",&t);
        if(t==(mid+sum+temp)/n)l=mid;//套二分板子
        else r=mid-1;
        sum+=temp;//记录加了多少
    }
    printf("! %d\n",l+sum);//输出查找结果 记得加上加的数
    fflush(stdout);
    return 0;
}
```

---

## 作者：Wei_Han (赞：0)

虽然每次询问都会增加 $x$ 的值，但我们已知这个值为多少，就可以直接减去，这样就能够得到 $x$ 的大小关系了。（虽然也没什么必要）

有了这个结论，我们就可以直接根据 $n$ 二分增加的值，不考虑之前增加的值，如果 $\left \lfloor \frac{x+mid}{n} \right \rfloor$ 相比于 $\left \lfloor \frac{x}{n} \right \rfloor$ 增加了，说明此时 $x\geq n-mid$ 反之 $x<n-mid$ 就可以进一步缩小范围了，当然，还是需要每次将 $x$ 增加 $mid$ 的，如果增加后超过 $n$ 再取模掉就好了。

由于 $n\leq 10^3$，二分和查询次数不会超过 $10$，可以通过，记得交互题刷新缓冲区。

时间复杂度 $O(\log n)$。
### Code
```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define pr printf("\n")
#define pp printf(" ")
#define pii pair<ll,ll>
#define mem(aa,bb) memset(aa,bb,sizeof(aa))
#define fo(a,i,b) for(ll i = a ; i <= b ; i ++ )
#define Fo(a,i,b) for(ll i = a ; i >= b ; i -- )
using namespace std;
typedef long long ll;
typedef double db;
const ll N=3e5+5;
void read(ll &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
void wr(ll x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}
ll n,cnt,tot,x;
inline bool check(ll mid)
{
	mid=(mid+tot)%n;
	cout<<"+ "<<n-mid<<endl;
	tot+=(n-mid);	
	cin>>x;
	if(x>cnt) return 1;
	return 0;
}
int main(){
	cin>>n;
	ll l=1,r=n;
	while(l<r){
		ll mid=(l+r+1)>>1;
		if(check(mid)) l=mid;
		else r=mid-1;
		cnt=x;
	}	
	cout<<"! "<<l+tot;
	return 0;
}
``````

---

## 作者：DaiRuiChen007 (赞：0)

# CF1624F 题解



## 思路分析

假设每次询问操作不会改变 $x$ 的值，而是返回 $\left\lfloor\dfrac {x+c}n\right\rfloor$ 的值。

显然，对于一个询问 `+ c`，返回 $0$ 当且仅当 $x+c<n$，而返回 $1$ 当且仅当 $x+c\ge n$，考虑二分出最小的 $c$ 使答案为 $1$，那么 $x=n-c$，由于 $c\in[1,n)$，所以需要操作次数为 $\log_2n\le 10$ 次。

接下来考虑这道题，假设初始 $x$ 值为 $x_0$，设当前所有操作的 $c$ 之和为 $S$，那么假如我们仍然想比较 $x+c$ 和 $n$ 的大小，那么设上一次操作的答案为 $k$，则我们需要找到一个 $q$ 使得 $x+S+q\ge (k+1)\times n\iff x+c\ge n$，移项比较可得 $q=c-(S-k\times n)=(c-S)\bmod n$，因此每次询问 $(c-S)\bmod n$ 继续采用原来的二分策略即可。

时间复杂度 $\Theta(\log n)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(int x) {
	cout<<"+ "<<x<<endl;
	int ret; cin>>ret; return ret;
}
int n,sum=0,lst=0;
inline bool check(int k) {
	int q=(k+n-sum%n)%n,p=read(q);
	sum=(sum+q);
	if(p>lst) {
		lst=p;
		return true;
	}
	return false;
}
signed main() {
	cin>>n;
	int l=1,r=n-1,res=0;
	while(l<=r) {
		int mid=(l+r)>>1;
		if(check(mid)) res=mid,r=mid-1;
		else l=mid+1;
	}
	cout<<"! "<<n-res+sum<<endl;
	return 0;
}
```



---

## 作者：Disjoint_cat (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1624F)

### 首先提示：每次操作是把 $x$ 的值加上 $c$，输出的是 _最后_ $x$ 的值。

首先发现 $2^{10}\approx1000$，所以我们想这肯定就是二分了。

**说明：为了简化计算，以下假定** $n=1000$。此时，$l=1$，$r=999$。

考虑把当前的 $x$ 加上一个值，然后把 $l$ 和 $r$ 也加上这个值（因为 $x$ 变化了），使返回值正好能够二分范围，这样就可以根据 $x$ 除以 $1000$ 的商来二分答案。如果返回的数值与 $\left\lfloor \dfrac{l}{1000}\right\rfloor$ 相等，就说明 $x<mid$，则 $r\leftarrow mid-1$，否则 $l\leftarrow mid+1$。

问题是，$x$ 到底应该加上多少呢？以第一次询问为例，此时的 $mid=500$。很明显，要想二分，就要让 $1000\mid mid$。所以把 $mid$ 加到比它大的 $1000$ 的倍数就可以了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l,r,mid,ans,lans;
int main()
{
	cin>>n;
	l=1,r=n-1;
	while(l<r)
	{
		mid=n*(ans+1)-(l+r)/2-1;
		printf("+ %d\n",mid);
		fflush(stdout); //别忘了flush
		l+=mid,r+=mid;
		cin>>ans;
		lans=l/n;
		if(ans==lans)r=(ans+1)*n-1;
		else l=ans*n;
	}
	printf("! %d\n",l);
	fflush(stdout);
	return 0;
}
```

---

