# [ARC189B] Minimize Sum

## 题目描述

数轴上有 $N$ 个棋子，最初所有棋子都放置在不同的坐标上，第 $i$ 个棋子放置在坐标 $X_i$ 上。

你可以进行以下操作若干次（可以为 $0$ 次）：

- 选择一个 $i$ 满足 $1\le i\le N-3$，并设 $M$ 为 $X_i$ 与 $X_{i+3}$ 的中点坐标。

- 然后，分别将坐标为 $X_{i+1}$ 与 $X_{i+2}$ 的两颗棋子放在原坐标关于 $M$ 对称的坐标，最后，使坐标较小的棋子的坐标为 $X_{i+1}$，另外一个棋子的坐标为 $X_{i+2}$。

- 可以证明无论如何重复操作，所有的棋子都放置在不同的坐标处。

请找出若干次操作后，$\sum_{i=1}^N X_i$ 的最小值。

## 样例 #1

### 输入

```
4
1 5 7 10```

### 输出

```
21```

## 样例 #2

### 输入

```
6
0 1 6 10 14 16```

### 输出

```
41```

# 题解

## 作者：ARIS2_0 (赞：9)

在 2024 年 12 月 8 日 19:50，小 S 准备征战 ARC189，找回属于自己的荣誉。

开赛了，小 S 看着颇似 NOIP2024 T2 的 ARC189 A ~~，想到自己赛时做 T2 的似样子~~，果断放弃了 A，转而去看 B。

他看懂了 B 的大致题意：

>数轴上有 $N$ 个棋子，最初所有棋子都放置在不同的坐标上，第 $i$ 个棋子放置在坐标 $X_i$ 上。
>
>你可以进行以下操作若干次（可以为 $0$ 次）：
>
>- 选择一个 $i$ 满足 $1\le i\le N-3$，并设 $M$ 为 $X_i$ 与 $X_{i+3}$ 的中点坐标。
>
>- 然后，分别将坐标为 $X_{i+1}$ 与 $X_{i+2}$ 的两颗棋子放在原坐标关于 $M$ 对称的坐标，最后，使坐标较小的棋子的坐标为 $X_{i+1}$，另外一个棋子的坐标为 $X_{i+2}$。
>
>- 可以证明无论如何重复操作，所有的棋子都放置在不同的坐标处。
>
>请找出若干次操作后，$\sum_{i=1}^N X_i$ 的最小值。

小 S 感觉这可能是一道类似 NOIP2024 T1 的神秘贪心。

小 S 思考了一下，发现了一个好到令他上窜下跳的性质：

如果对 $i$ 进行操作，根据小学数学知识，$X_{i+1}$ 和 $X_{i+2}$ 对 $X_i$ 与 $X_{i+3}$ 的中点进行对称，得到的是 $X_i+X_{i+3}-X_{i+1}$ 和 $X_i+X_{i+3}-X_{i+2}$。因为 $X_{i+1}<X_{i+2}$，所以 $X_i+X_{i+3}-X_{i+2}<X_i+X_{i+3}-X_{i+1}$。

所以，操作可以等效于：

> 选择一个 $i$ 满足 $1\le i\le N-3$，**同时进行** $X_i+X_{i+3}-X_{i+2}\to X_{i+1}$，$X_i+X_{i+3}-X_{i+1}\to X_{i+2}$ 的操作。

可是，小 S 做到这就不会了。他打了若干发贪心，都以 AC 15 WA 17 告终。他的 ARC189 之战，以 B 题 -10 结束了。

晚上，小 S 在床上想着，要不要就此退役算了。

突然，他好像想到了什么：

如果他将原数组做差，生成一个数列 $P_1.,P_2,\dots,P_{N-1}$ 满足 $P_i=X_{i+1}-X_i$。

那么，对于 $i$ 的操作，等效于将 $P_i$ 与 $P_{i+2}$ 交换！

>证明：
>
>设操作前的 $X$ 为 $OX$，操作前的 $P$ 为 $OP$。
>
>则:
>
>- $P_i=X_{i+1}-X_i=OX_i+OX_{i+3}-OX_{i+2}-X_i=OX_{i+3}-OX_{i+2}=OP_{i+2}$
>
>- $P_{i+1}=X_{i+2}-X_{i+1}=OX_i+OX_{i+3}-OX_{i+1}-OX_i-OX_{i+3}+OX_{i+2}=OX_{i+2}-OX_{i+1}=OP_{i+1}$
>
>- $P_{i+2}=X_{i+3}-X_{i+2}=X_{i+3}-OX_i-OX_{i+3}+OX_{i+1}=OX_{i+1}-OX_i=OP_i$
>
>其他的 $P_i$ 显然不受影响。

那么，小 S 想到，要让 $\sum_{i=1}^N X_i$ 最小，**等效于让 P 的字典序最小**。

而每次对于 $i$ 的操作可以交换 $P_i$ 与 $P_{i+2}$，那么，**所有 $i$ 为奇数的 $P_i$ 之间可以自由交换，所有 $i$ 为偶数的 $P_i$ 之间也可以自由交换**。

此时，小 S 心里已经知道这题怎么做了：

>
> 将 $P$ 计算出来后，将 $P_1,P_3,\dots,P_{\lceil \frac{n-1}{2}\rceil -1}$ 排序，从小到大放进 $P_1,P_3,\dots,P_{\lceil \frac{n-1}{2}\rceil -1}$ 里面，再将 $P_2,P_4,\dots,P_{\lfloor \frac{n-1}{2}\rfloor}$ 排序，也从小到大放进 $P_2,P_4,\dots,P_{\lfloor \frac{n-1}{2}\rfloor}$ 里。
>
>最后，按 $P$ 重新生成 $X$，计算 $\sum_{i=1}^N X_i$，就做完了。

**可是，这个时候知道怎么做又有什么用呢？** 比赛已经结束了，小 S 已经不能获得他失去的分数了，就像他在 NOIP2024 赛场上想出了 T1 正解，却只得到了 60pts。

看着那些 204pts 的同学，小 S 笑着摇了摇头。

也许，这就是小 S 每天殷切地对着卫星许愿的原因吧。

**S.A.T.E.L.L.I.T.E**.

### AC Code

因为个人习惯，代码中数组 $a$ 对应题目中数组 $x$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int inf=1e16,maxn=2e5+10;
int a[maxn],p[maxn],p1[maxn],p2[maxn];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<n;i++)p[i]=a[i+1]-a[i];
	for(int i=1;i<n;i++){
		if(i%2)p1[(i+1)/2]=p[i];
		else p2[i/2]=p[i];
	}
	sort(p1,p1+(int)ceil((n-1)*1.0/2)+1);
	sort(p2,p2+(n-1)/2+1);
	for(int i=1;i<n;i++){
		if(i%2)p[i]=p1[(i+1)/2];
		else p[i]=p2[i/2];
	}
	int ans=a[1];
	for(int i=2;i<=n;i++)a[i]=a[i-1]+p[i-1],ans+=a[i];
	cout<<ans;
	return 0;
}
```

---

## 作者：MspAInt (赞：1)

再睁眼，回到了 CSP-S 的考场上。哇那可真是太好了。我一定不会再【数据删除】了。于是我跳起来站在桌子上环视一圈——

---

看起来十分十分的复杂，先仔细的看一看。

发现将 $z$ 对 $x,y$ 的中点对称是 $x+y-z\to z$，并且题目中操作后 $x_{i+1},x_{i+2}$ 大小关系反转。

取出 $x_i,x_{i+1},x_{i+2},x_{i+3}$，然后写出来 $x_{1\sim4}$ 变成：

$x_i,x_i+x_{i+3}-x_{i+2},x_i+x_{i+3}-x_{i+1},x_{i+3}$

令差分数组为 $\{y_n\}$：

$y_i=x_i-x_{i-1},y_{i+1}=x_{i+3}-x_{i+2},y_{i+2}=x_{i+2}-x_{i+1},y_{i+3}=x_{i+1}-x_i$

发现是把差分数组交换，除 $y_1$ 外奇数位和偶数位分别可以自由交换。为使 $\sum_{i=1}^n\sum_{j=1}^i y_j$ 最小，奇偶位分离升序，算答案。

Code:

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;

const int N=2e5+10;
int n;
LL a[N],b[N],c[N];
LL sum,ans;

signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
    for(int i=n;i>=1;i--)a[i]-=a[i-1];
    for(int i=2;i<=n;i++)if(i&1)b[i/2]=a[i];else c[i/2]=a[i];
    sort(b+1,b+(n-1)/2+1);sort(c+1,c+n/2+1);
    sum=ans=a[1];
    for(int i=2;i<=n;ans+=sum,i++)if(i&1)sum+=b[i/2];else sum+=c[i/2];
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：dingxiongyue (赞：1)

# 题解：[ARC189B] Minimize Sum  

## Description：
给定一个一维坐标系及升序排列的坐标序列 $a$，可以对序列 $a$ 进行以下操作若干次：选取 $4$ 个**连续**的坐标点，将第二、三个点关于第一、四点的**中点**对称，得到新的序列。求 $\sum_{i=1}^n a_i$。  
## Analysis：
对于一次操作，若选取 $a_i$、$a_{i+1}$、$a_{i+2}$、$a_{i+3}$ 这四个点，则有：  
 $$
 \begin{cases}
 \frac {a_{i+1}^\prime + a_{i+2} } {2} = \frac {a_i + a_{i+3}} {2} \\
 \frac {a_{i+2}^\prime + a_{i+1} } {2} = \frac {a_i + a_{i+3}} {2}
 \end{cases}
 $$
即：
 $$
\begin{cases}
a_{i+1}^\prime = a_i+a_{i+3}-a_{i+2} \\
a_{i+2}^\prime = a_i+a_{i+3}-a_{i+1}
\end{cases}
 $$
 新序列变为了：$a_i$、$a_{i+1}^\prime$、$a_{i+2}^\prime$、$a_{i+3}$。  

 即：$a_i$、$a_i+a_{i+3}-a_{i+2}$、$a_i+a_{i+3}-a_{i+1}$、$a_{i+3}$。 
 
 所以操作后的坐标数组的**差分数组**就变成了：
 $$
\begin{cases}
d_i^\prime=a_i - a_{i-1}\\
d_{i+1}^\prime=(a_i+a_{i+3}-a_{i+2})-a_i\\
d_{i+2}^\prime=(a_i+a_{i+3}-a_{i+1}) - (a_i+a_{i+3}-a_{i+2})\\
d_{i+3}^\prime=a_{i+3}-(a_i+a_{i+3}-a_{i+1})
\end{cases}
 $$
即：
 $$
\begin{cases}
d_i^\prime=d_i \\
d_{i+1}^\prime=d_{i+3} \\
d_{i+2}^\prime=d_{i+2} \\
d_{i+3}^\prime=d_{i+1}
\end{cases}
 $$
 发现二、四点的差分数值互换了，于是可以得到结论：  
   
 坐标的差分数组中**奇偶性**相同的位置数值可以互换。   
 
 又因为：
 $$
ans=\sum_{i=1}^{n} a_i = \sum_{i=1}^{n} \sum_{j=1}^{i} d_j
 $$
要**最小化** $ans$，只需将差分数值更小的尽量放在前面即可。  

## Code：
最后附上 [AC](https://www.luogu.com.cn/record/194335765) 代码：
```cpp
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;
const int N = 2e5 + 10;
int n;
int ans;
int a[N];
int d[N], s[N];
int d1[N], d2[N];
inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch)) {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (isdigit(ch)) {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}

inline void write(int x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

signed main() {
	n = read();
	for (int i = 1; i <= n; i++)
		a[i] = read(), d[i] = a[i] - a[i - 1];
	for (int i = 1; i <= n; i++) {
		if (i & 1) d1[i / 2] = d[i];
		else d2[i / 2] = d[i];
	}
	sort(d1 + 1, d1 + 1 + (n - 1) / 2);
	sort(d2 + 1, d2 + 1 + n / 2);
	for (int i = 1; i <= n; i++) {
		if (i & 1) d[i] = d1[i / 2];
		else d[i] = d2[i / 2];
	}
	for (int i = 1; i <= n; i++) {
		s[i] = s[i - 1] + d[i];
		ans += s[i];
	}
	write(ans);
	printf("\n");
	return 0;
}
```

---

## 作者：dengchengyu (赞：1)

## arc189_b

题目大意：数轴上有 $n$ 个点 $x_i$，每次可以选择连续递增四个点，记 $M$ 为第一个和第四个点的中点，把第二个和第三个点关于 $M$ 对称，问不断操作，点坐标和最小是多少。

这道题赛时往贪心的方向想了，一直不会做。没想到在洛谷上评了绿。

考虑操作一次后，差分数组的变化。

记 $d_i=a_i-a_{i-1}(2\le i\le n)$。

那么选择 $i\sim i+3$ 操作以后，就从 $[a_i][a_{i+1}][a_{i+2}][a_{i+3}]$，变成了 $[a_i][a_i+a_{i+3}-a_{i+1}][a_i+a_{i+3}-a_{i+2}][a_{i+3}]$，注意第二项比第三项大，所以是 $[a_i][a_i+a_{i+3}-a_{i+2}][a_i+a_{i+3}-a_{i+1}][a_{i+3}]$。

那么，差分数组就从 $d_{i+1},d_{i+2},d_{i+3}$ 变成了 $d_{i+3},d_{i+2},d_{i+1}$，相当于交换第一个和第三个差分。

发现对于奇偶性相同的位置，我们可以随便交换。

那么由于让和最小，所以要让前面的差分尽可能小，于是对奇数位的差分和偶数位的差分分别排序即可。

时间复杂度 $O(n\log n)$。

AC 代码：

```cpp
const int N=2e5+5;
int a[N];
int d1[N],d2[N];
int n;
int d[N];
signed main(){
	cin>>n;
	fo(i,1,n){
		cin>>a[i];
		d[i]=a[i]-a[i-1];
		if(i&1)d1[i/2]=d[i];
		else d2[i/2]=d[i];
	}
	sort(d1+1,d1+1+(n-1)/2);
	sort(d2+1,d2+1+n/2);
	fo(i,1,n){
		if(i&1)d[i]=d1[i/2];
		else d[i]=d2[i/2];
	}
	ll ans=a[1];
	fo(i,2,n){
		a[i]=a[i-1]+d[i];
		ans+=a[i];
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：win114514 (赞：1)

场上被创死了。

### 思路

考虑一次操作会造成什么影响。

加入操作的是：

$$
x_1,x_2,x_3,x_4
$$

它们会变成：

$$
x_1,x_1+x_4-x_3,x_1+x_4-x_2,x_4
$$

发现没有什么规律。

考虑它们的差分序列：

$$
x_1,x_4-x_3,x_3-x_2,x_2-x_1
$$

改变为交换 $2,4$ 的差分。

那么修改就变成很简单的形式了。

奇偶分别排序即可。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

int n;
int a[200010];

signed main() {
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = n; i >= 1; i--) a[i] = a[i] - a[i - 1];
  vector<int> ji;
  vector<int> ou;
  for (int i = 2; i <= n; i++) {
    if (i % 2 == 1) ji.push_back(a[i]);
    if (i % 2 == 0) ou.push_back(a[i]);
  }
  sort(ji.begin(), ji.end());
  sort(ou.begin(), ou.end());;
  int ns = a[1] * n;
  for (int i = 0; i < ji.size(); i++) {
    ns += (n - 2 * i - 2) * ji[i];
  }
  for (int i = 0; i < ou.size(); i++) {
    ns += (n - 2 * i - 1) * ou[i];
  }
  cout << ns << "\n";
}
```

---

## 作者：Drifty (赞：1)

这题是被 hgcnxn 教会的，hgcnxn orz 喵喵喵。

我们记 $X$ 的差分为 $d$。

通过手玩发现，对 $i$ 至 $i + 3$ 进行一次操作其实等价于交换 $d_i, d_{i + 2}$。证明是显然的。

那么我们把奇偶位拆开来分讨，显然我们希望前面的 $d$ 尽可能小，又注意到我们可以随便交换，那么分别排一下序加起来，做完了。[AC Record.](https://atcoder.jp/contests/arc189/submissions/60604279)

---

## 作者：RAND_MAX (赞：0)

简单题啊，但是本人场上写了 20min，怎么会是呢。

考虑一次操作的本质即为将差分数组上第 $i$ 位与 $i+2$ 位交换。我们要让坐标和最小即让差分数组尽量单调不降，否则不优。我们只需将差分数组的奇数位与偶数位分别从小到大排序即可。

代码实现容易，注意加上第一个点的坐标。
```cpp
#include<bits/stdc++.h>
#define int long long
#define gc getchar
//char buf[1<<20],*p1,*p2;
//#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
#define R read()
using namespace std;
int read()
{
	int x=0,f=1;
	char c=gc();
	while(c>'9'||c<'0'){if(c=='-') f=-1;c=gc();}
	while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+c-48,c=gc();
	return x*f;
}
void write(int x,char xx)
{
	static int st[35],top=0;
	if(x<0){x=-x;putchar('-');}
	do
	{
		st[top++]=x%10,x/=10;
	}while(x);
	while(top) putchar(st[--top]+48);
	putchar(xx);
}
#define N 500010
int n,a[N],sum,c[N],ans;
vector<int>v1,v2,v;
signed main()
{
	n=R;
	for(int i=1;i<=n;i++) a[i]=R;
	for(int i=1;i<n;i++)
	{
		c[i]=a[i+1]-a[i];
	}
	for(int i=1;i<n;i+=2) v1.push_back(c[i]);
	for(int i=2;i<n;i+=2) v2.push_back(c[i]);
	sort(v1.begin(),v1.end()),sort(v2.begin(),v2.end());
	for(int i=1;i<n;i++)
	{
		if(i&1) v.push_back(v1[i>>1]);
		else v.push_back(v2[i-1>>1]);
	}
	sum=ans=a[1];
	for(int i:v) sum+=i,ans+=sum;
	write(ans,'\n');
 	return 0;
}
```

---

## 作者：隔壁泞2的如心 (赞：0)

这 题 绝 对 没 有 蓝 吧

设差分数组 $D_i=X_{i+1}-X_i$，则题目中的操作相当于交换 $D_i$ 和 $D_{i+2}$。

假如存在 $D_i>D_{i+2}$，那么交换它们答案一定变小，因此 $D$ 的奇偶项分别有序时答案最小。直接对奇偶项分别排序计算答案即可。

---

## 作者：LaDeX (赞：0)

> 数轴上有 $n$ 个点 $x_1,x_2,\cdots,x_n$，你可以进行以下操作任意次（可以不操作）：
> - 每次选取一个整数 $i$，满足 $1\leq i\leq n - 3$，设 $m$ 为将点升序排列后第 $i$ 个点与第 $i+3$ 个点的中点，那么将升序排列后第 $i + 1$ 个点与第 $i+2$ 个点分别变成其关于 $m$ 的对称点。
> 
> 请最小化最终得到的点的坐标之和。

我们默认这个序列是有序的，那么我们假设一次操作中这四个数分别是 $a,b,c,d$，那么操作完他们分别变成了（注意操作完之后第二个数会大于第三个数，要交换这两个数保证有序。）：

$$a,b,c,d \rightarrow a,a+d-c,a+d-b,d.$$

那么这里看似没什么关系，这里有一个类似 [P7962 [NOIP2021] 方差](https://www.luogu.com.cn/problem/P7962) 的转化，我们考虑这个序列的差分，也就是考虑上面那两个子段的差分，那么差分有以下变化:

$$b-a,c-b,d-c\rightarrow d-c,c-b,b-a.$$

我们发现，这一次操作的本质就是交换了间隔一个数的差分值，差分值是不变的，但是顺序改变，显然差分值越小的放在前面，总和越小，因为越前面的数造成最终答案贡献的数量越大，所以越小的数放在前面最优。

所以考虑怎样得到最优的方案。我们发现，相隔一个数的交换，使越小的放越前面，等价于对下标分别为奇数和偶数的两个子数组分别排序然后合并成原来数组。所以就做完了。最后根据差分数组和序列第一个数还原出原数组，然后求和即可。

[My submission.](https://atcoder.jp/contests/arc189/submissions/60593950)

---

## 作者：A2_Zenith (赞：0)

有点脑电波的题，但也是成功对上了。

---

首先考虑我们对 $i$ 操作了一次，发现 $|x_{i+2}-x_{i+1}|$ 没变。这启示我们从差分数组的视角来考虑问题。

设 $d_i = x_{i+1}-x_i$，下标从 $1 \sim n-1$。对于一个这样的差分数组，答案是 $n \times x_1 + \sum\limits_{i=1}^{n-1}(n-i)d_i$。

然后进一步发掘题目性质，发现对 $i$ 进行操作本质上是交换了 $d_i$ 与 $d_{i+2}$。

考虑对差分数组奇偶分项，因为奇偶性不同的两项显然不会互相影响。分成两个数组。然后你可以任意交换这两个数组内的元素了。

由经典贪心，肯定是要将小的项放到前面才能使结果更小。做完了。时间复杂度是 $n \log n$。


```cpp
#include<bits/stdc++.h>
#define int long long
#define PII pair<int,int>
#define fir first
#define sec second
#define mp make_pair
#define endl '\n'
using namespace std;
const int maxn=5e5+7;
const int mod=998244353;
int n;
int x[maxn];
int d[maxn];
int o[maxn];
int e[maxn];
signed main(){ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    #endif
    cin>>n;
    for(int i=1;i<=n;i++)cin>>x[i];
    for(int i=1;i<n;i++)d[i]=x[i+1]-x[i];
    int n1=0,n2=0;
    for(int i=1;i<n;i++){
        if(i&1)o[i+1>>1]=d[i],n1=max(n1,i+1>>1);
        else e[i>>1]=d[i],n2=max(n2,i>>1);
    }
    sort(o+1,o+n1+1);
    sort(e+1,e+n2+1);
    for(int i=1;i<=n1;i++)d[i*2-1]=o[i];
    for(int i=1;i<=n2;i++)d[i*2]=e[i];
    int ans=n*x[1];
    for(int i=1;i<n;i++)ans+=(n-i)*d[i];
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：晴空一鹤 (赞：0)

欢歌载舞，交换差分，共同庆祝！

由于原序列有序，而题目给的操作并不会破坏序列的有序性，因此所有操作都将在有序序列上进行。

考虑两个数的平均数离这两个数一样远，而对称前后的数离对称中心一样远，两个减一下差相同，因此中间靠左的数离左端数的距离与变换后离右端数的距离是一样的，中间靠右的数同理。因此操作等价于交换第 $i$ 项与第 $i+2$ 差分。

容易观察到位置奇偶不同的差分项不能交换，而奇偶相同的差分项可以任意交换相邻两项，等价于冒泡排序，我们可以把这些差分项排列成任意我们想要的样子。

题目要求最小的和，也就是差分的前缀和的前缀和，拆一下可以发现系数单调递减，因此把奇差分项和偶差分项分别升序排列即可。

代码非常简单，有一种方差的美。（


```cpp
//让差分来吧
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=2e5;
ll n,a[N+5],cf1[N+5],sum,cf2[N+5];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
	cin>>a[i];
	if(i%2==1)
	cf1[i/2]=a[i]-a[i-1];
	else cf2[i/2]=a[i]-a[i-1];
	}
	sort(cf1+1,cf1+n/2+1-(n%2==0));
	sort(cf2+1,cf2+n/2+1);sum=a[1];
	for(int i=2;i<=n;i++){
	if(i%2==0)
	a[i]=a[i-1]+cf2[i/2];
	else
	a[i]=a[i-1]+cf1[i/2];
	sum+=a[i];
	}
	cout<<sum<<"\n";
} 
```

---

