# [ARC168A] <Inversion>

## 题目描述

给定一个由 `<` 和 `>` 组成的长度为 $N-1$ 的字符串 $S$。

我们称长度为 $N$ 的数列 $x=(x_1, x_2, \cdots, x_N)$ 满足以下条件时为**好数列**：

- 对于每个 $i$（$1 \leq i \leq N-1$），如果 $S$ 的第 $i$ 个字符是 `<$，则 $x_i < x_{i+1}$；如果是 `>$，则 $x_i > x_{i+1}$。

请你求出好数列的逆序对数可能的最小值。

数列的逆序对数定义为：对于长度为 $n$ 的数列 $x=(x_1, x_2, \cdots, x_n)$，逆序对数是满足 $1 \leq i < j \leq n$ 且 $x_i > x_j$ 的整数对 $(i, j)$ 的个数。

## 说明/提示

## 限制条件

- $2 \leq N \leq 250000$
- $S$ 是由 `<` 和 `>` 组成的长度为 $N-1$ 的字符串。
- 输入的所有值均为整数。

## 样例解释 1

如果取 $x=(1,2,1,2)$，这是一个好数列。此时 $x$ 的逆序对数为 $1$。不存在逆序对数为 $0$ 的好数列，因此答案为 $1$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
<><```

### 输出

```
1```

## 样例 #2

### 输入

```
2
<```

### 输出

```
0```

## 样例 #3

### 输入

```
10
>>>>>>>>>```

### 输出

```
45```

## 样例 #4

### 输入

```
30
<<><>>><><>><><><<>><<<><><<>```

### 输出

```
19```

# 题解

## 作者：封禁用户 (赞：1)

题目开始讲解前，我先解释一下逆序对是什么。

逆序对就是在一个序列中前面的数大于后面的数就叫逆序对。


正文开始：

那既然已经已经了解了逆序对，那我们看题目，他要求出逆序对的个数。那是大于的情况就很好办，就是求一个长度为 $x$ 的排列组合，但是顺序不能变，所以就可以用高斯求和来求出来逆序对个数。

那如果是小于的情况，那么到当前这个位置的逆序对个数就是前面大于情况的逆序对个数。因为当前是大于，他破坏了前面大于情况组成逆序对的情况。（对了，统计大于符号的变量要清 $0$）

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, t, sun; 
string s;

int main()
{
	cin >> n;
	cin >> s;
	for(int i = 0; i < n - 1; i ++) if(s[i] == '>') t ++; else sun += ((t + 1) * t / 2), t = 0;
	cout << sun + (t + 1) * t / 2;
	return 0;
}
```

---

## 作者：lailai0916 (赞：1)

## 原题链接

- [洛谷 AT_arc168_a [ARC168A] <Inversion>](https://www.luogu.com.cn/problem/AT_arc168_a)

## 解题思路

构造一个最优的序列，然后归并排序求逆序对。

为了使逆序对数量尽可能少，就要让后面的数尽可能大。

1. 令 $x_1=0$。

2. 对于每个 $k\in[1,n-1]$ 分类讨论：
  
- 如果 $s_k$ 为 `>`，即 $x_k>x_{k+1}$：$x_{k+1}$ 比 $x_k$ 小，但又要尽可能大，可以让 $x_{k+1}\gets x_k-1$。
- 否则 $s_k$ 为 `<`，即 $x_k<x_{k+1}$：$x_{k+1}$ 要尽可能大，可以让 $x_{k+1}\gets x_k+\infty$。

3. 这里的 $\infty$ 是相对于数据范围 $250000$ 的，多个 $\infty$ 允许叠加，且 $2\cdot\infty\gg\infty\gg0$。 

4. 最后用归并排序求 $x_i$ 的逆序对数量。

## 参考代码

```cpp
#include <bits/stdc++.h>
#define mid (l+r>>1)
using namespace std;

using ll=long long;
const int N=250005;
const int inf=0x3f3f3f3f;
ll a[N],b[N];
ll ans=0;
void msort(int l,int r)
{
	if(l==r)return;
	msort(l,mid);
	msort(mid+1,r);
	int p1=l,p2=mid+1,k=l;
	while(p1<=mid&&p2<=r)
	{
		if(a[p1]<=a[p2])
		{
			b[k++]=a[p1++];
		}
		else
		{
			b[k++]=a[p2++];
			ans+=mid-p1+1;
		}
	}
	while(p1<=mid)b[k++]=a[p1++];
	while(p2<=r)b[k++]=a[p2++];
	for(int i=l;i<=r;i++)a[i]=b[i];
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	string s;
	cin>>n>>s;
	for(int i=0;i<n-1;i++)
	{
		if(s[i]=='>')a[i+1]=a[i]-1;
		else a[i+1]=a[i]+inf;
	}
	msort(0,n-1);
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：yduck (赞：1)

蒟蒻第一篇正式提交的题解。首先可以观察发现，若一个序列全是 `>`，那么答案就是序列的长度 $\frac{(len + 1) \times len}{2}$。那么从左往右扫，统计连续的 `>` 的长度 $tmp$，如果碰到了 `<`，那么可以直接令答案累加 $\frac{(tmp + 1) \times tmp}{2}$，并令 $tmp = 0$ 即可。最后输出就完啦。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define N 250010

int n;
char a[N];

signed main(){
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    cin >> a + 1;
    int tmp = 0, ans = 0;
    for(int i = 1; i < n; i ++){
        if(a[i] == '>'){
            tmp++;
        }
        else{
            ans += (tmp + 1) * tmp / 2;
            tmp = 0;
        }
    }
    if(tmp){
        ans += (tmp + 1) * tmp / 2;
    }
    cout << ans;
    return 0;
}
```


---

## 作者：Shadow_T (赞：1)

第一次打 ARC 只解出一道题的菜狗，写篇题解留念。

考虑贪心，我们可以倒过来计算，对于每出现一个大于，便等于后面那个加 $1$，即 $a_i=a_{i+1}+1$。因为这样可以使这个值尽量小，减少和后面的数造成逆序对。对于小于号，我们要让这个数比后面的数小，那么显然，这个数也要和后面的数拉开大距离，才可以减少逆序对。所以，可以直接将这个数等于后面那个数减去 $10^9$，其实减去的数只要大于 $250000$ 就可以，这里是随便取的。

最后就是给构造出来的 $a$ 跑一遍用分治 $O(n \log n)$ 算的逆序对，输出逆序对数量即可。

感觉做法有点奇怪。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=250010;
int inf=1e9;
int a[maxn],c[maxn];
int cf[maxn];
long long ans;
void Sort(int l,int r)
{
    if(l==r) return;
    int mid=(l+r)/2,i=l,j=mid+1,k=l;
    Sort(l,mid);
	Sort(mid+1,r);
    while(i<=mid&&j<=r)
    if(a[i]<=a[j])
    c[k++]=a[i++];
    else c[k++]=a[j++],ans+=mid-i+1;
    while(i<=mid) c[k++]=a[i++];
    while(j<=r) c[k++]=a[j++];
    for(int i=l;i<=r;i++) a[i]=c[i];
}
signed main()
{
	int len;
	cin>>len;
	len--;
	string s;
	cin>>s;
	a[len]=inf;
	for(int i=len-1;i>=0;i--)
	if(s[i]=='>') a[i]=a[i+1]+1;
	else 
	{
		a[i]=--inf;
		int sum=1e9;
		int I=i;
		I--;
		while(I>=0&&a[I]=='>')
		I--;
		I++;
		a[i]-=sum;
		inf=a[i];
		for(int j=i-1;j>=I;j--)
		a[i]=a[i+1]+1;
		i=I;
	}
	Sort(0,len);
	cout<<ans<<"\n";
}
```

---

## 作者：zxy1919810 (赞：1)

# [ARC168A] <Inversion> 题解
[题目传送门](https://www.luogu.com.cn/problem/AT_arc168_a)
## 思路
发现：连续 $n$ 个**大于号**可以贡献的逆序对个数为↓↓↓
$$\frac{n \cdot (n+1)}{2}$$

所以我们就可以直接扫描字符串。
## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string s;
int ans;
signed main(){
	cin>>s>>s;  //第一次输入的n没用
	s+='<';  //防止越界
	for(int i=0;i<s.size();i++)
		if(s[i]=='>'){   //查找开始
			int j=i+1;   //从i+1开始查找
			while(s[j]!='<')j++;   //查找连续的大于号数量，为j-i个
			ans+=(j-i)*(j-i+1)/2;   //ans累加
			i=j;   //跳过这些大于号，以免重复计算
		}
	cout<<ans;
	return 0;
}
```

---

## 作者：xzz_0611 (赞：0)

[题目传送门](/problem/AT_arc168_a)
## [逆序对](https://baike.baidu.com/item/%E9%80%86%E5%BA%8F%E5%AF%B9/11035554)
在一个**没有重复数值**的序列 $a$ 之中，如果存在一组下标 $i$ 和 $j$ 使得 $i<j$，那么当 $a_i>a_j$ 时，就称 $a_i$ 和 $a_j$ 是序列 $a$ 中的一组逆序对。
## 思路
显然，对于**连续**的 $x$ 个 `>`，会产生 $\displaystyle\sum_{i=1}^{x}i$ 个逆序对，利用高斯求和转换成 $\displaystyle\frac{x\times(x+1)}{2}$。

所以只要从左至右一步步判断 $S$ 的字符，如果其是：
- `>`：累加 `>` 的个数（为方便表示，设其为 $x$）。
- `<`：将答案累加 $\displaystyle\frac{x\times(x+1)}{2}$ 并将 $x$ 清 $0$。

最后输出答案即可。
## Code
```cpp
#include<iostream>
#define int long long//不开long long见祖宗
using namespace std;
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	int n,sum=0,ans=0;
	string str;
	cin>>n>>str,--n;
	for(int i=0;i<n;++i) {
		if(str[i]=='>') ++sum;//累加
		else ans+=(sum+1)*sum/2,sum=0;//累加答案并清0
	}
	cout<<ans+(sum+1)*sum/2;//还要把最后的累加起来
	return 0;
}
```

---

## 作者：FreedomKing (赞：0)

简单数学题。

### 思路

因为要求的是**能**表示的逆序对数，也就是给出的序列中能确定的逆序对数，所以直接对个最长 `>` 段分开讨论贡献即可。由小学数学知，连续 $cnt$ 个 `>` 可以产生的贡献为 $\tfrac{cnt\times(cnt+1)}{2}$，加和统计每一 `>` 的最长连续段的贡献即可。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,mN=1e4+5,mod=1e9+7;
namespace FreedomKing_qwq{};
using namespace FreedomKing_qwq;
namespace FreedomKing_qwq{
	inline int qread(){
#define qr qread()
		int x=0,c=getchar(),t=1;
		while(c<'0'||c>'9'){
			t^=(c=='-');
			c=getchar();
		}
		while(c>='0'&&c<='9'){
			x=(x<<3)+(x<<1)+c-'0';
			c=getchar();
		}
		return (t?x:-x);
	}
	inline void qwrite(int x){
#define qw(_) qwrite(_)
#define qws(_) qw(_),putchar(' ')
#define qwe(_) qw(_),putchar('\n')
		if(x<0) putchar('-'),x=-x;
		if(x>9) qw(x/10);
		putchar(x%10+'0');
		return;
	}
	inline int qpow(int x,int p,int mod){
		x=(p!=0?x:1);
		mod=(mod?mod:LONG_LONG_MAX);
		if(p<0) return qpow(qpow(x,-p,mod),mod-2,mod);
		int t=1;
		while(p>1){
			if(p&1) t=(t*x)%mod;
			x=(x*x)%mod;
			p>>=1;
		}
		return (x*t)%mod;
	}
	//	inline int max(int x,int y){return (x>y?x:y);}
	inline int min(int x,int y){return (x<y?x:y);}
	inline int gcd(int x,int y){return (x%y==0?y:gcd(y,x%y));}
	inline int lcm(int x,int y){return (x/gcd(x,y)*y);}
}
int ans,cnt;
signed main(){
	int n=qr;
	for(int i=2;i<=n;i++){
		char c;
		cin>>c;
		if(c=='>') cnt++;
		else{
			ans+=(cnt*(cnt+1)>>1);
			cnt=0;
		}
	}
	qw((ans+(cnt*(cnt+1)>>1)));
	return 0;
}
```

---

## 作者：chl090410 (赞：0)

## The Solution to AT_arc168_a Inversion

### 题目大意

有一个长度为 $N-1$ 的、由 $<$ 与 $>$ 组成的字符串，构造数组 $x$，使得若 $s_i=>$，则 $x_i>x_{i+1}$，否则 $x_i<x_{i+1}$。

### Solution

若字符串 $s$ 中连续 $k$ 个元素均为 $>$，则 $x$ 数组中这 $k$ 个元素一定单调递减，就会产生 $\dfrac{k\times(k+1)}{2}$ 组逆序对，因为要求逆序对总数的最小值，所以除了元素单调递减的子段外，其余地方不要再出现逆序对。

- 具体实现方法：遍历字符串 $s$，若 $s_i=>$，就让统计序列长度的变量 $k$ 加 $1$，否则让统计逆序对数量的变量 $ans+\dfrac{k\times(k+1)}{2}$。

最后输出 $ans$ 即可。

### Accode如下：

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,ans;
char c;
signed main(){
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>c;
		if(c=='>'){
			k++;
		}else{
			ans+=(k*(k+1)/2);
			k=0;
		}
	}
	cout<<ans+k*(k+1)/2;
	return 0;
}

---

## 作者：2huk (赞：0)

# A - Inversion

## Description

给定一个长度为 $n - 1$ 的字符串 $s$，由字符 $\texttt <$ 和 $\texttt >$ 组成。

请你构造一个长度为 $n$ 的序列 $\{x_n\}$，满足以下条件，并使得其逆序对数量最少。

- 对于每个 $1 \le i < n$，如果 $s_i = \texttt <$，则 $x_i < x_{i + 1}$；否则如果 $s_i = \texttt >$，则 $x_i > x_{i + 1}$。

求最小的逆序对数量。

$2 \le n \le 2.5 \times 10^5$。

## Solution

考虑贪心的将所有的数字求出。

首先可以发现，题目中给的要求都是对于两个**相邻**的元素而言的，那么我们应该在满足当前的条件下让后面的答案最优。具体而言，对于这样一个例子：
$$
s = \{\texttt{<>><<<<<<}\cdots\}
$$
对于 $x_2$ 而言，它需要比 $x_1$ 和 $x_3$ 都大。这时可以发现 $x_1$ 的与 $x_3$ 之间的关系并不明确。而我们希望让答案的逆序对数量最小，也就是希望尽量 $x_1 < x_3$。可以发现这件事请是可以完成的，我们只需要令 $\left\{\begin{matrix}x_1= 1 \\x_2= 3 \\x_3= 2\end{matrix}\right.$ 即可。

这时发现，对于第 $4$ 个及往后的要求，答案中必定会产生逆序对而使答案变劣。那么我们考虑这样做：既然已经有 $x_2 > x_3$ 这个事实了，也就是说这里必定会产生一个逆序对，那么我们不妨让 $x_3$ 变得大一些，将损失降到最小，然后对于后面的计算就可以避免产生**可以被避免**的逆序对了。可以发现最大的可以满足条件的 $x_3$ 为 $x_2 - 1$。

同理，既然已经有了 $x_1 < x_2$ 这个事实，也就是这个条件对答案十分有利，那么我们就让它**造福后世**，即 $x_2$ 变得大一些，这样对于后面的计算也可以避免产生**可以被避免**的逆序对了。不妨令 $x_2 = x_1 + N$，这里的 $N$ 为一个较大值，不妨为 $10^9$。

也就是说我们可以这样做：
$$
x = \{1, 100, 99, 98, 200, 199, 198, 197, \cdots\}
$$
可以由上述得到这样一个贪心策略：

- 若 $s_i = \texttt <$，则 $x_i = x_{i - 1} + N$。
- 若 $s_i = \texttt >$，则 $x_i = x_{i - 1} - 1$。

可以证明，也可以凭直觉，这样构造出的 $x$ 一定是逆序对最少的。最后再求出 $x$ 中的逆序对数量即可。

## Code

求逆序对我用的 `map` 维护的树状数组：<https://atcoder.jp/contests/arc168/submissions/47767743>。



---

## 作者：Red_river (赞：0)

### 题目分析

首先我们可以知道，这道题其实就是由逆序对演变而来的。以此类推，我们可以发现，当一个位置是小于号时，我们就需要加一，也就是当前连续不间断地小于号个数。而当当前位置是一个大于号的时候，我们就需要统计答案了，公式如下：
$$ Ans= \frac{n \cdot (n+1)}{2}$$

$n$ 也就是当前位置连续不间断地小于号个数。

#### CODE
```cpp
#include<bits/stdc++.h>
#define int long long                //记得开long long(ll) 
#define wh(x) write(x),putchar('\n')
#define A printf("Aoki")
#define T printf("Takahashi")

using namespace std;
char a;
int n,m,k,jk,sum,num,ans;

void read(int &x)
{
	x=0;int ff=1;char ty;
	ty=getchar();
	while(!(ty>='0'&&ty<='9'))
	{
		if(ty=='-') ff=-1;
		ty=getchar();
	}
	while(ty>='0'&&ty<='9')
	x=(x<<3)+(x<<1)+ty-'0',ty=getchar();
	x*=ff;return;
}

void write(int x)
{
	if(x==0){
		putchar('0');return;
	}
	if(x<0){
		x=-x;putchar('-');
	}
	char asd[201];int ip=0;
	while(x) asd[++ip]=x%10+'0',x/=10;
	for(int i=ip;i>=1;i--) putchar(asd[i]);
	return;
}

signed main()                              //用了 #define 就要用signed了 
{
	read(n);
	for(int i=1;i<=n;i++)                  //字符串长度 
	{
		scanf("%c",&a);                    //其实可以每次只输入一个字符 
		if(a=='>') sum++;                  //当条件成立时，个数加一 
		else ans+=(sum*(sum+1))/2,sum=0;   //不成立的话加上方案数 
	}
	return wh(ans),0;                      //输出ans并结束等于wh(ans);return 0; 
	return 0;
}
```

---

## 作者：XYQ_102 (赞：0)

## 题意
读入一个由 `<` 和 `>` 构成的字符串，在最开始，最后，字符之间可以填上任意数字，任意两个相邻数字之间必须满足字符代表的大小关系。求问最后填入的数字组成的数组最少有多少对逆序对。
## 思路
`<` 可以不去考虑，因为不会对答案造成影响。

`>` 如果不是在连续段内，也可以不去考虑，因为最优解必然是这部分贡献为 `0` 的。只需要考虑连续的 `>` 个数求解即可。

---

## 作者：abensyl (赞：0)

原题：[[ARC168A] <Inversion>](https://www.luogu.com.cn/problem/AT_arc168_a)。

## 思路

考虑为了出现尽可能少逆序对，我们希望能让后面的数字大于前面的数字。

那么显然地，我们希望尽可能多的前数小于后数的关系，考虑一个问题，小于号的意义是什么？

小于号的意义在于，如果对于构造出的数组中的两数 $a_i$ 和 $a_{i+1}$ 呈现小于关系，那么为了使得逆序对少，我们显然是会利用这个小于号，使得 $[1,i]$ 中的所有数字都小于 $[i+1,n+1]$ 中的所有数字。

那么，通过这种构造方式可以知道，只有连续的大于号才会制造出逆序对，对于连续的 $k$ 个大于号，会对于答案产生 $k\times(k+1)\over 2$ 的贡献。

总的答案就是所有连续大于号对于答案的贡献和。

[我的 AC 代码](https://atcoder.jp/contests/arc168/submissions/47878716)。

---

## 作者：Xiphi (赞：0)

观察发现，形成逆序对的一定是一段连续的 `>` 中，每个 `>` 后连续的 `>` 数量之和，包括自己。双指针维护即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
string s;
long long ans,n,l=1,r=0;
signed main(){
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    cin>>s;
    for(int i=0;i<n-1;++i){
    	if(s[i]!='>') continue;
		r=max(i,r);
		int flag=0;
		while(s[r]=='>') r++,flag=1;
		r-=flag;
		ans+=r-i+1;
	}
	cout<<ans;
	return 0;
}




```

---

