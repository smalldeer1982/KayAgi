# [ARC167A] Toasts for Breakfast Party

## 题目描述

# [ARC167A] Toasts for Breakfast Party


[problemUrl]: https://atcoder.jp/contests/arc167/tasks/arc167_a

浴谷的站长 kkkscO2 最近购买了 $N$ 片烤绿鸟味的扩散性百万甜面包。第 $i$ 片面包的美味值是 $a_i$。又有 $M$ 个盘子，每个盘子可以装**最多**两片面包，盘子可以空着。

定义 $b_i$ 为盘子 $i$ 里的面包的美味值的和的平方，若盘子里没有面包则 $b_i$ 为 $0$。若只有一个面包，则 $b_i$ 为该面包的美味值的平方。

求所有合法的 $\sum_{1 \le i \le M}b_i$ 的最小值。$\frac{N}{2} \le M \le N$。

## 说明/提示

- $ 1\leq\ N\leq\ 2\times\ 10^{5} $
- $ \frac{N}{2}\leq\ M\leq\ N $
- $ 1\leq\ A_{i}\leq\ 2\times\ 10^{5} $
- 保证输入的都是整数
 
### 样例1解释

我们将第 $1$ 片和第 $2$ 片面包放在第一个盘子里，第 $3$ 片和第 $4$ 片面包放在第二个盘子里。第 $5$ 片单独放在最后一个盘子里。此时的答案 $\sum_{1 \le i \le M}b_i =(1+1)^{2} + (1+6)^{2} + 7^2 = 102$。没有比该方案更优的结果。注意不能将第 $1$ 片，第 $2$ 片和第 $3$ 片放在同一个盘子里。

## 样例 #1

### 输入

```
5 3
1 1 1 6 7```

### 输出

```
102```

## 样例 #2

### 输入

```
2 1
167 924```

### 输出

```
1190281```

## 样例 #3

### 输入

```
12 9
22847 98332 854 68844 81080 46058 40949 62493 76561 52907 88628 99740```

### 输出

```
61968950639```

# 题解

## 作者：f_hxr_ (赞：13)

## [谷谷传送门](https://www.luogu.com.cn/problem/AT_arc167_a) [AT 传送门](https://atcoder.jp/contests/arc167/tasks/arc167_a)

# 题目大意

有 $N$ 片烤绿鸟味的扩散性百万甜面包。第 $i$ 片面包的美味值是 $a_i$。又有 $M$ 个盘子，每个盘子可以装**最多**两片面包，盘子可以空着。

定义 $b_i$ 为盘子 $i$ 里的面包的美味值的和的平方，若盘子里没有面包则 $b_i$ 为 $0$。若只有一个面包，则 $b_i$ 为该面包的美味值的平方。

求所有可能的 $\sum_{1 \le i \le M}b_i$ 的最小值。$\frac{N}{2} \le M \le N$。

# 解析

我们先做一个预处理：把只装有一个面包的盘子看成有一个普通面包**和一个美味值为 $0$ 的空气面包**的盘子，把空盘子看成**装有两个空气面包**的盘子。

这样做有什么好处呢？这样做不会影响答案的正确性，而且可以避开特判只有一个面包的情况。所有情况，不管是一个，两个还是没有面包，都一视同仁。

注意为了使面包一一配对，算上空气面包一共要有 $2M$ 个面包。

回到正题。我们令盘子 $i$ 的第一块面包的美味值为 $X_i$，第二块面包的美味值为 $Y_i$。则：

$$\sum_{1 \le i \le M}b_i = \sum_{1 \le i \le M}(X_i + Y_i)^2$$

将等式右边用完全平方公式展开得：

$$\sum_{1 \le i \le M}b_i = \sum_{1 \le i \le M}X_i^2 + Y_i^2+2X_iY_i$$

将求和符号提出来:

$$\sum_{1 \le i \le M}b_i = \sum_{1 \le i \le M}X_i^2 + Y_i^2 + \sum_{1 \le i \le M}+2X_iY_i$$


由于 $X_i$，$Y_i$ 都是给出的定值，所以 $X_i^2 + Y_i^2$ 也是定值。$\sum_{1 \le i \le M}X_i^2 + Y_i^2$ 也是定值。只需要令 $\sum_{1 \le i \le M}+2X_iY_i$ 最小，也就是 $X_i$ 与 $Y_i$ 的积最小即可。

考虑贪心。对于一个很大的数，为了使积尽量小，我们需要找一个尽量小的数与之相乘。如果有空盘子，那当然是放在空盘子里为最好，也就相当于与一个空气面包的美味值相乘（此时 $X_i \times Y_i $ 为 $0$）。

我们将原序列加上补上的“空气面包”一起从小到大或从大到小排序，用两个分别指向序列开头和末尾的指针依次相乘即可。

### codes：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL N,M,a[400005],ans;
int main(){
	cin>>N>>M;
	for(int i=1;i<=N;i++)cin>>a[i],ans+=a[i]*a[i];
	sort(a+1,a+M*2+1);
	LL LHQ=1,RMQ=M*2;
	while(LHQ<=RMQ)ans+=a[LHQ]*a[RMQ]*2,LHQ++,RMQ--;
	cout<<ans;
	return 0;
} 
```

---

## 作者：大眼仔Happy (赞：8)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc167_a)

## 简要题意

给定 $n$ 个吐司，分到 $m$ 个盘子中，要求每个盘子最多只能放 $2$ 个，而每个吐司又必须放在一个盘子中。设 $b_i$ 表示第 $i$ 个盘子中的吐司的美味值的总和，求 $\sum b_i^2$ 最小。

## 分析

考虑将所有的盘子全部放满，具体就是加入美味值为 $0$ 的吐司使得吐司的数量变为 $2m$。现在每个盘子中都有两个吐司，设美味值为 $x_i,y_i$。则这个盘子的贡献为 $(x_i+y_i)^2=x_i^2+y_i^2+2x_iy_i$。发现不管怎么放置吐司，$x_i^2+y_i^2$ 的总和都是不变的，影响的只是后面的部分。后面的部分贪心即可，即美味值大的与美味值小的分在一起。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e5+5;
#define ll long long
ll inline read()
{
	ll num=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){num=(num<<3)+(num<<1)+(ch^48);ch=getchar();}
	return num*f;
}
int n,m;
ll a[N],ans;
int main(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+2*m+1);
	for(int i=1;i<=2*m;i++)ans+=a[i]*a[i];
	for(int i=1;i<=m;i++)ans+=2*a[i]*a[2*m-i+1];
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：zhangjiting (赞：4)

## 题意

有 $n$ 片面包，每个面包有一个分数，要求你放在 $m$ 个盘子里，放置要求如下：

1. 全部放完。
1. 一个盘子里最多放两片。

设一个数为所有盘子里面包分数之和的平方再相加，你的任务是使这个数最小。

## 思路

贪心。

既然要求平方之和最小，也就是说要求每个盘子里的分数尽量相等。

那么我们就可以想到分数小的面包两两放在一个盘子里，分数大的面包单独放在一个盘子里。

显而易见，一个盘子放一个，多出来的就是需要和其他面包配对的，所以，我们只需要在数组排序后的前 $2 \times (n-m)$ 片面包进行配对，每次选择其中最大的一个和最小的一个放在一起。最后把剩下的 $n-2 \times (n-m)$ 片面包单独放在剩余的盘子里。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int b[200005],top,a[200005],ans;
signed main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	int x2=max(n-m,0ll);
	int x=x2*2;
	int r=x;
	int l=1;
	for(int i=1;i<=x2;i++) b[++top]=a[l++]+a[r--];
	for(int i=x+1;i<=n;i++){
		b[++top]=a[i];
	}
	for(int i=1;i<=n;i++) ans+=b[i]*b[i];
	cout<<ans;
	return 0;
}

```


---

## 作者：watcher_YBH (赞：3)

# 题目翻译：
有 $n$ 个吐司，$m$ 个盘子。每个吐司有一个美味度 $a_i$，每个盘子可以放一个或两个吐司，每个盘子的不平衡度为这个盘子中，所装的吐司的美味度相加的平方。求出所有盘子的不平衡度的和的最小值。
# 思路：
首先，我们可以用贪心的思路去做。我们先将 $a_i$ 从小到大的排序，那么一定会有 $n-m$ 个盘子中放着两个吐司（先将每个盘子放一个吐司，那么多出来的 $n-m$ 个吐司只能和其他吐司重着放），所以一共有 $2 \times (n-m)$ 个吐司会存放在 $n-m$ 个盘子中，如果要使这几盘子的不平衡度的和最小，那么在最优情况下，就是将 $a_1 \sim a_{2 \times (n-m)}$ 个数分配进 $n-m$ 个盘子中（从小到大排序过的），再讲 $a_1 \sim a_{2 \times (n-m)}$ 首尾相配就能使这部分的不平衡度的和最小。另外，剩下几个较大数单独存入一个盘子也能使不平衡度的和最小。
# 代码：
```cpp
#include<bits/stdc++.h>
#define int long long// 开long long 
#define max(a,b) ((a)>(b)?a:b)
#define min(a,b) ((a)<(b)?a:b)
using namespace std;
const int MAX = 2e5+5;
int n,m;
int a[MAX];
signed main(){
	cin>>n>>m;
	for(int i = 1; i<=n; i++) cin>>a[i];
	sort(a+1,a+n+1);// 从小到大排序 
	int ans = 0;// 答案 
	for(int i = 1; i<=n-m; i++)// a_i ~ a_2(n-m) 首尾相配 
		ans += (a[i]+a[(n-m)*2-i+1])*(a[i]+a[(n-m)*2-i+1]);
	for(int i = (n-m)*2+1; i<=n; i++)// 剩下的单独存 
		ans += a[i]*a[i];
	cout<<ans;// 输出答案 
	return 0;
}

```


---

## 作者：CrTsIr400 (赞：2)

## ARC167A

### 题意

我们有 $N$ 片吐司和 $M$ 个盘子。$M$ 是 $[\frac{N}{2},N]$ 之间的整数。

第 $i$ 片吐司的美味程度为 $A_{i}$。把 $N$ 片吐司放在 $M$ 个盘子上，满足以下两个条件：

- 每个盘子**最多**可以放**两片**吐司。

- 每一片吐司都在某个盘子里。

设 $B_{j}$ 为第 $j$ 个盘子上烤面包的美味程度之和（如果盘子上没有烤面包，则为 $0$）。

那么，设**不平衡度**为 $\sum_{j=1}^{M} B_{j}^{2}$。求不平衡度的最小值。

### 题解

因为吐司没有顺序之分，所以我们给 $A$ 从小到大排序。

有一个很显然的结论，不能留空盘子。因为两片叠起来一定比分别放不优。

首先设 $q$ 为配对组数，显然 $q=n-m$。

然后数学直觉告诉我一个结论：拿第 $1$ 个和第 $2q$ 个配对，第二个和第 $2q-1$ 个配对，依此类推……

剩下不配对的单独放一个盘子里面。

于是很神奇，过了所有样例，一发就过了。

```cpp
#include<bits/stdc++.h>
#define fo(i,a,b) for(auto i(a),_ed(b);i<=_ed;++i)
#define gch(k) for(;(k);CH=getchar())
using namespace std;using I=int;using LL=long long;using V=void;I FL,CH;LL in(){LL a=0;FL=1;gch(!isdigit(CH))FL=(CH=='-')?-1:1;gch(isdigit(CH))a=a*10+CH-'0';return a*FL;}
LL sq(I x){
	return 1ll*x*x;}
LL ans=0;
const I N=2e5+10;
I n,m,a[N];
I main(){n=in();m=in();
	I q=n-m;m=q;
	fo(i,1,n)a[i]=in();
	sort(a+1,a+n+1);
	fo(i,1,n-m*2)ans+=sq(a[n-i+1]);
	I i,j;
	for(i=1,j=m*2;i<j;++i,--j)
		ans+=sq(a[i]+a[j]);
//	if(i==j)ans+=sq(a[i]);
	printf("%lld\n",ans);
	return 0;}
```

考虑证明结论的正确性。

+ 首先需要证明选择最小的 $2q$ 个是最优的。
  + 前面 $2q$ 个数字是配对的，所以数字 $a$ 对答案的贡献是形如 $(a+b)^2$ 的形式的。
  + 可知 $A_i\ge 1$，所以 $(a+b)^2>a^2$。
  + 拿一个比 $a$ 大的 $c$ 和 $a$ 交换比 $a$ 是否更优？
  + 发现 $(a+b)^2+c^2-(c+b)^2-a^2=2ab-2cb=2b(a-c)<0$。
  + 所以，观察这个式子小于 $0$，可得：$(a+b)^2+c^2<(c+b)^2-a^2$。
  + 于是选择最小的 $2q$ 个数字一一配对最优。
+ 其次需要证明对于这 $2q$ 个数字的大小匹配方案最优。
  + 同样也是采用交换不等式证明。
  + 设 $a\le b\le c\le d$，那么需要证明 $(a+d)^2+(b+c)^2\le (a+c)^2+(b+d)^2$。
  + 转化一下，变成了 $ad+bc\le ac+bd$。
  + 则 $a(d-c)\le b(d-c)$，符合 $a\le b\le c\le d$ 的事实。
  + 于是这个方案是最优的。

于是我们的证明就证完了。

---

## 作者：shipeiqian (赞：2)

# ARC167A 题解

## 题意

有 $m$ 个数，要将它们分成 $n$ 组，每组至多 $2$ 个数。求出每组中数字之和的平方的最小值。

## 思路

如果让一些数字与很大的数字相加，结果必然会更大，尽量要把大的数字单独放，所以要把最大的 $2n-m$（$2n$ 是指每组都放满，减去 $m$ 就是多出来的位置）个数单独放，余下的数（$m-(2n-m)$ 个）必然为偶数个，因此可以将它们小的和大的组成一组，平方和就能最小。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5;//十年oi一场空，数组开小见祖宗
ll n,m,a[N];
int main(){
	cin >>n >>m;
	ll ans=0;
	for(int i=1;i<=n;i++)cin >>a[i];
	sort(a+1,a+1+n);
	ll diff=m*2-n;//单独放置的数量
	for(int i=n;i>=n-diff+1;i--){
		ans+=a[i]*a[i];//单独的就直接平方
	}
	n-=diff;
	for(int i=1;i*2<=n;i++){
		ans+=(a[i]+a[n-i+1])*(a[i]+a[n-i+1]);//剩下的小的和大的放一起
	}
	cout <<ans <<"\n";
    return 0;
}
```

---

## 作者：Sirkey (赞：2)

第一次打 ARC 就遇到了这么简单的题目。

更据题目描述，我们可以很轻松的得到一个贪心策略。

我们将原数组排序，如果刚好两个放一个盘子里刚好放完，就可以直接首尾放一个。

如果盘子还有剩的，我们可以考虑大的分出来，分到刚好可以放完的时候，再进行上面的操作。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define FOR(i,a,b) for(ll i=(a); i<=(b); ++i)
#define ROF(i,a,b) for(ll i=(a); i>=(b); --i)
#define tell(ans) out(ans),printf("\n");
#define say(ans) out(ans),printf(" ");
#define pb push_back
#define mid (l+r)>>1
//
//
//
using namespace std;
inline ll read() {
	ll f=0,t=0;
	char c=getchar();
	while(!isdigit(c)) t|=(c=='-'),c=getchar();
	while(isdigit(c)) f=(f<<3)+(f<<1)+c-48,c=getchar();
	return t?-f:f;
}
inline void out(ll x) {
	if(x<0) putchar('-');
	if(x>9) out(x/10);
	putchar('0'+x%10);
}
ll a[500005];
int main() {
	ll n=read(),m=read();
	FOR(i,1,n) a[i]=read();
	sort(a+1,a+n+1);
	ll p=0;
	__int128 sum=0;
	ROF(i,n,n/2) {
		if(m<=n/2+(n%2)) break;
//		cout<<a[n]<<" "<<m<<" "<<n<<endl;
		sum+=a[n]*a[n],n-=1,m-=1;
	}
	if(n&1) sum+=a[n]*a[n],n-=1;
	FOR(i,1,n/2) {
		p=a[i]+a[n-i+1];
		sum+=p*p;
	}
	out(sum);
	return 0;
}

```
——end——

---

## 作者：STARSczy (赞：1)

吐槽一下，这题的题面翻译真的太那个了，一看就是一个带着很多不良风气的人写的。

# 思路：
先把 $a_i$ 排序。由于 $m \leq n$，因此如果一个面包一个盘子的话，一定有 $(n-m)$ 个面包是分不了的，因此这些剩余的面包要和一些面包共盘子。为了使答案最小，要找尽可能小的面包这些面包共盘子，也就是在前 $(n-m)\times 2$ 个面包中，第一个和最后一个一起，第二个和倒数第二个一起，以此类推。

# 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e6+10,mod=1e9+7;
inline int read(){
	int c,w=0,n=0;
	while((c=getchar())<'0'||'9'<c) w=c=='-';
	do n=n*10+c-'0';while('0'<=(c=getchar())&&c<='9');
	return w?-n:n;
}
inline int write(int n){
	if(n<0) putchar('-'),n=-n;
	if(n>9) write(n/10);
	putchar(n%10+'0');
	return n;
}

int n=read(),m=(n-read())<<1,a[maxn],ans;

signed main(){
	for(int i=1;i<=n;++i) a[i]=read();
	sort(a+1,a+n+1);//排序
	for(int l=1,r=m;l<r;++l,--r) ans+=(a[l]+a[r])*(a[l]+a[r])/*分配两个的盘子*/;
	for(int i=m+1;i<=n;++i) ans+=a[i]*a[i];//剩下的盘子
	write(ans);
	return 0;
}
```

---

## 作者：indream (赞：0)

# \[ARC167A] Toasts for Breakfast Party 题解
[原题](https://www.luogu.com.cn/problem/AT_arc167_a) | [AC 记录](https://www.luogu.com.cn/record/133826144)

题意比较清晰，这里就不过多赘述。
## 思路
贪心题。~~第一次看见红色贪心。~~

我们可以把 $2m - n$ 个“缺失”的吐司当成美味值为 0 的吐司看待，毕竟不影响结果，这样每个盘子里都有 2 个吐司。此时，根据完全平方公式，$b_i =(a_i + a_j)^2 = a_i^2 + a_j^2 + 2 a_i a_j$。显然，这里的 $\sum_{i=0}^n a_i^{2}$ 不是我们能决定的，所以我们只需令每个 $2 a_i a_j$ 最小即可。小学老师说过：和一定，差小积大，差大积小。

据此，我们可以对 $a$ 数组从小到大排序后，处理从左右分别往中间算 $2 a_i a_j$ 即可(在输入时可先处理好 $a_i^2$)。从大到小排序理论上也可以，但我想没人愿意重写 $cmp$ 函数的。

注意， 开数组时由于需要 $2m$ 的量，故大小要 $4 \times 10^5$；由于 $(2 \times 10^5)^2$ 会爆 `int`，所以开 `long long`。
## 代码
~~只要 16 行代码，爽！~~
```cpp
#include<bits/stdc++.h>
using namespace std;
unsigned long long a[400005],n,m,ans;
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m;
    for(int i=0;i<n;i++){
        cin>>a[i];
        ans+=a[i]*a[i];
    }
    sort(a,a+2*m);
    for(int l=0,r=2*m-1;l<r;l++,r--)//l左指针，r右指针
        ans+=2*a[l]*a[r];
    cout<<ans;
    return 0;
}
```

---

## 作者：LYY_yyyy (赞：0)

显然将数组排序不影响结果。排序后，我们假设有 $n$ 个盘子，将面包一一放进盘子中。之后考虑每次将两个盘子合并（注意每个盘子只能合并一次），总共 $n-m$ 次，就可以放进 $m$ 个盘子里。我们考虑 $n$ 个盘子时，答案为 $\sum_{i=1}^{n}a_i^2$。每次合并，相当于把 $a^2+b^2$ 变成 $(a+b)^2$，显然会多出来 $2\times a\times b$ 的不平衡度。换言之，设每次合并的两个盘子中的值为 $u$ 和 $v$，我们要最小化 $\sum_{i=1}^{n-m}2\times u_i\times v_i$。根据贪心思想，我们将前 $2\times(n-m)$ 个的盘子取出来合并，每次合并头尾，这样可以最小化答案。这可以通过调整法证明一定不劣。代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[200010]; 
int main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);long long ans=0;
	cin>>n>>m;for(int i=1;i<=n;i++) cin>>a[i],ans+=a[i]*1ll*a[i];sort(a+1,a+n+1);
	int p=n-m;
	for(int i=1;i<=p;i++) ans+=2ll*a[i]*a[2*p-i+1];
	cout<<ans;
	return 0;
}
```

---

## 作者：kkxacj (赞：0)

[[ARC167A] Toasts for Breakfast Party](https://www.luogu.com.cn/problem/AT_arc167_a)

#### 思路

考虑贪心，可以先对数组排序，让第 $i$ 小的和第 $i + 1$ 小的在一起，不过如果有多的盘子尽量把大的分开放，然后就行了。

**code**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[300010],o = 1,o1;
long long ans2,t2[300010];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++) scanf("%d",&a[i]);
	sort(a + 1,a + 1 + n);
	o = 1;
	for(int i = 1;i <= n;i += 2) m--,t2[o++] = a[i];
	o1 = 1;
	if(n % 2 == 1) n--;
	for(int i = n;i >= 1;i -= 2)
	{
		if(m) m--,ans2 += a[i];//有多的盘子就将大的分开 
		else t2[o1] += a[i];
		o1++;
	}
	for(int i = 1;i <= o;i++) ans2 += t2[i] * t2[i];
    printf("%lld",ans2);
	return 0;
}
```



---

