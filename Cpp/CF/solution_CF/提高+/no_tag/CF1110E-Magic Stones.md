# Magic Stones

## 题目描述

Grigory 有 $n$ 块魔法石，编号从 $1$ 到 $n$。第 $i$ 块石头的电量为 $c_i$。

有时 Grigory 会感到无聊，他会选择某一块内部的石头（即编号为 $i$，满足 $2 \le i \le n - 1$），然后将其与相邻的石头进行同步。同步后，被选中的石头会失去自身的电量，但会获得相邻两块石头的电量。也就是说，其电量 $c_i$ 会变为 $c_i' = c_{i + 1} + c_{i - 1} - c_i$。

Grigory 的朋友 Andrew 也有 $n$ 块石头，其电量分别为 $t_i$。Grigory 想知道，是否存在一系列（可以为空）同步操作，能够将 Grigory 的所有石头的电量变为 Andrew 的石头的电量，即对于所有 $i$，将 $c_i$ 变为 $t_i$？

## 说明/提示

在第一个样例中，可以进行如下同步操作（下标从 $1$ 开始）：

- 首先同步第三块石头：$[7, 2, \mathbf{4}, 12] \rightarrow [7, 2, \mathbf{10}, 12]$。
- 然后同步第二块石头：$[7, \mathbf{2}, 10, 12] \rightarrow [7, \mathbf{15}, 10, 12]$。

在第二个样例中，无论对第二块石头进行多少次操作，其电量都不会发生变化。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
7 2 4 12
7 15 10 12
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
3
4 4 4
1 2 3
```

### 输出

```
No
```

# 题解

## 作者：StudyingFather (赞：21)

神仙结论题。

首先如果 $c_1 \neq t_1$ 或者 $c_n \neq t_n$ 那显然不行。

排除了这种情况后，我们来看看一次操作会造成怎样的变化。

设 $a_i=c_{i+1}-c_i$。

原来的 $a_i$ 是这样的：$a_i=c_{i+1}-c_i$，$a_{i-1}=c_i-c_{i-1}$。

现在我们将 $c_i$ 变成 $c_{i+1}+c_{i-1}-c_i$，这时候的 $a_i$ 变成了：$a_i=(c_{i+1}+c_{i-1}-c_i)-c_{i-1}=c_{i+1}-c_i$，$a_{i+1}=c_{i+1}-(c_{i+1}+c_{i-1}-c_i)=c_i-c_{i-1}$。

我们发现两个 $a_i$ 互换了。

于是问题就变成了：给两个差分数组，每次操作可以将其中一个数组的相邻两个元素互换，问能不能让两个数组相等。

这个就很简单了。

```cpp
// Problem : E. Magic Stones
// Contest : Codeforces Global Round 1
// URL : https://codeforces.com/contest/1110/problem/E
// Author : StudyingFather
// Site : https://studyingfather.com
// Memory Limit : 256 MB
// Time Limit : 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cp-editor)

#include <iostream>
#include <algorithm>
using namespace std;
int a[100005],b[100005],c[100005],d[100005];
int main()
{
 int n;
 cin>>n;
 for(int i=1;i<=n;i++)
  cin>>a[i];
 for(int i=1;i<=n;i++)
  cin>>b[i];
 if(a[1]!=b[1]||a[n]!=b[n])
 {
  cout<<"No"<<endl;
  return 0;
 }
 for(int i=1;i<n;i++)
 {
  c[i]=a[i+1]-a[i];
  d[i]=b[i+1]-b[i];
 }
 sort(c+1,c+n);
 sort(d+1,d+n);
 for(int i=1;i<n;i++)
  if(c[i]!=d[i])
  {
   cout<<"No"<<endl;
   return 0;
  }
 cout<<"Yes"<<endl;
 return 0;
}
```

---

## 作者：ChthollyTree (赞：4)

题意：

给定一个长度为n的序列c 对于一个位置 i（1 < i < n）

可以进行如下变换操作

$c_{i}'$ = $c_{i+1} + c_{i-1} - c_{i}$

问是否可以经过若干次操作变成序列t

作c序列的差分数组

就是定义 $a_{i}$ = $c_{i} - c_{i-1}$

我们会发现

对于 $c_{i}$ 的一次变换，交换的差分数组的两个数

如$c_{i}'$ = $c_{i+1} + c_{i-1} - c_{i}$ 操作后

本来差分数组是 $c_{i}-c_{i-1}$ ,$c_{i+1}-c_{i}$ ,

如今原序列变为 $c_{i-1}$ ， $c_{i+1} + c_{i-1} - c_{i}$，$c_{i+1}$

则手算可得差分数组为  $c_{i+1}-c_{i}$,$c_{i}-c_{i-1}$ ,

这样就求出c,t的差分数组就行了

注意因为1，n无法更改，要特判

```
#include<bits/stdc++.h>
using namespace std;

#define MAXN 100005 
int n,m;
int a[MAXN],b[MAXN];
int c[MAXN],d[MAXN];

void rd()
{
	scanf("%d",&n);
	for(int i = 1; i <= n; i ++)
		scanf("%d",&a[i]); 
	for(int i = 1; i <= n; i ++)
		scanf("%d",&b[i]);
}

int main()
{
	rd();//
	if(a[1] != b[1])
	{//
		cout<<"No";//
		return 0;
	}
	if(a[n] != b[n])
	{
		cout<<"No";
		return 0;
	}
	for(int i = 2; i <= n; i ++)
	{
		c[i-1] = a[i] - a[i-1];
		d[i-1] = b[i] - b[i-1];
	}
	sort(c+1,c+n);//
	sort(d+1,d+n);//
	for(int i = 1; i < n; i ++)
		if(c[i] != d[i])
			{//
				cout<<"No";//
				return 0;//
			}//
	cout<<"Yes";//
	return 0;//
}//
/*
4
7 2 4 12
7 15 10 12

4
1 2 2 4
1 1 3 4
*/
```



---

## 作者：C　C　A (赞：2)

$$\Large \rm E-Magic~Stones$$

$\quad$考虑对交换的式子移项，有 ：

$$\begin{cases}
    c_i'-c_{i-1}=c_{i+1}-c_i\\c_i-c_{i-1}=c_{i+1}-c_i'
\end{cases}$$

$\quad$发现其为差分形式，且将原数组差分后相当于交换差分数组的相邻两项，故直接将 $S$ 和 $T$ 的差分数组求出来，判断其是否一一对应即可。

$\quad$时间复杂度 $\Theta(n).$

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i, l, r) for (int i = l; i <= r; i++)

const int N = 1e5 + 10;

int n, s[N], t[N], cs[N], ct[N];

int main () {
	
	scanf("%d", &n);
	rep(i, 1, n) scanf("%d", &s[i]), cs[i] = s[i] - s[i - 1];
	rep(i, 1, n) scanf("%d", &t[i]), ct[i] = t[i] - t[i - 1];
	
	sort(cs + 2, cs + n + 1), sort(ct + 2, ct + n + 1);
	if (s[1] != t[1] || s[n] != t[n]) return puts("No"), 0;
	rep(i, 2, n) if (cs[i] != ct[i]) return puts("No"), 0;
	puts("Yes");
	
	return 0;
}
```

---

## 作者：Warriors_Cat (赞：2)

一道结论题，主要的还是找性质。

### $Solution:$

每次变动只牵扯了 $3$ 个数，所以我们先考虑一下三个数的情况。

假设有三个连续的数 $(x, y, z)$ 变成了 $(x, x + z - y, z)$。

没啥规律，于是无脑差分一下：

$(y - x, z - y)$ 变成了 $(z - y, y - x)$。

发现差分序列只是交换了一下两个数的位置而已！

于是我们只需要判断两个差分序列组成的两个可重集是不是同一个可重集就行了。

注意特判首项和末项。

### $Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
inline int read(){
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
	return x * f;
}
const int N = 100010;
int n, c[N], t[N], a[N], b[N];
int main(){
	n = read();
	for(int i = 1; i <= n; ++i) c[i] = read();
	for(int i = 1; i <= n; ++i) t[i] = read();
	if(c[1] != t[1] || c[n] != t[n]) return puts("No") & 0;//特判
	for(int i = 1; i < n; ++i) a[i] = c[i + 1] - c[i], b[i] = t[i + 1] - t[i];
	sort(a + 1, a + n + 1); sort(b + 1, b + n + 1);
	for(int i = 1; i < n; ++i) if(a[i] != b[i]) return puts("No") & 0;
	puts("Yes"); return 0;
}
```


---

## 作者：Kendrick_Z (赞：1)

首先翻译下题目：

题目大意：

给定一个序列，每次可以对序列中除了1，n的数进行如下操作：

c[i]'=c[i+1]+c[i-1]-c[i]

问这个式子是否能转为目标序列

我们把这个移项

c[i]'-c[i-1]=c[i+1]-c[i]

那么我们就得到了

cf[i']=cf[i+1]

所以每次操作对于差分数列的值没有发生改变 改变的只有 位置 也就是交换一下位置

那么我们把两个数列进行差分操作 然后我们排序后比对

判断下是否一样即可

但是前面说了 1，n无法操作

那么我们就要特判一下1的值即可

不过n的值好像是不需要判断（最好还是判断）

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1E6;
int cf[N],d[N],a[N],b[N],n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		cf[i]=a[i]-a[i-1]; 
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&b[i]);
		d[i]=b[i]-b[i-1];
	}
	sort(d+1,d+n+1);
	sort(cf+1,cf+n+1);
	if(a[1]!=b[1]){
		puts("No");
		return 0;
	}
	for(int i=1;i<=n;i++){
		if(d[i]!=cf[i]) {
			puts("No");
			return 0;
		}
	} 
	puts("Yes");
	
	return 0;
} 
```


---

## 作者：fjy666 (赞：1)

### 0x01 思路
我们考虑这个序列的什么是不变的。  
$A_{i-1},A_i,A_{i+1}$  
相邻两项之差：$A_i-A_{i-1},A_{i+1}-A_i$  
对 $A_i$ 进行一次操作，数组变成  
$A_{i-1},A_{i-1}+A_{i+1}-A_i,A_{i+1}$  
相邻两项之差：$A_{i+1}-A_i,A_i-A_{i-1}$  
我们惊喜地发现：所有差的值都不变，只是位置变了！  
那我们比较它们每个元素的差是否相同就行了！  
**但是，有一个例外！**  
$1<i<n$，第 $1$ 和 $n$ 个元素不能改变！  
我们还要特判一下它们是否相等。  
因为题目并没有让我们输出怎么操作，  
所以这样就可以 AC 本题。

怎么判断两个序列的元素是否相等？  
很简单， `std::sort` 排序一下再比较即可。  
若要追求速度，还可以使用基数排序等方式，  
但在本题， `std::sort` 即可 AC。  
时间复杂度：$\Theta(n\times\log n)$

------------
### 0x02 代码 
```cpp
#include <cstdio>
#include <algorithm>
#define fo(i_,j_,k_) for(int i_=j_;i_<=k_;++i_)
#define fr(i_,j_,k_) for(int i_=j_;i_>=k_;--i_)
#define It(type_) type_::iterator
#define rg register
#define rtn return
#define il inline

typedef long long ll;
const int kMaxn = 200000+5;
int a[kMaxn],b[kMaxn];
int a_[kMaxn],b_[kMaxn];

int main()
{
	int n;
	scanf("%d",&n);
	fo(i,1,n)
		scanf("%d",a+i);
	fo(i,1,n)
		scanf("%d",b+i);
	fo(i,1,n)
		a_[i] = a[i+1]-a[i];
	fo(i,1,n)
		b_[i] = b[i+1]-b[i];
	bool flag = (a[1]==b[1]) && (a[n]==b[n]);
	std::sort(a_+1,a_+n);
	std::sort(b_+1,b_+n);
	fo(i,1,n-1)
		if(a_[i]!=b_[i])
			flag=false;
	if(flag)puts("Yes");
	else puts("No");
    rtn 0;
}
```

---

## 作者：Emp7iness (赞：0)

首先可以发现如果 $c_1 \ne t_1$ 或者 $c_n \ne t_n$ 的话肯定是不可行的。

在此基础上，如果我们对 $c_i$ 进行一次操作，那我们可以发现原数组中 $c_{i-1} ,  c_i , c_{i+1}$ 三项的值变成了 $c_{i-1} ,  c_{i-1}+c_{i+1}-c_i , c_{i+1}$，而它的差分数组（设差分数组为 $d$，且 $d_i=c_{i}-c_{i-1}$）$d_i , d_{i+1}$ 两项的值从 $c_{i}-c_{i-1} , c_{i+1}-c_{i}$ 变成了 $(c_{i-1}+c_{i+1}-c_i)-c_{i-1} , c_{i+1}-(c_{i-1}+c_{i+1}-c_i)$，即 $c_{i+1}-c_{i} , c_{i}-c_{i-1}$。

所以可以发现如果我们对 $c_i$ 进行一次操作，那么它的差分数组 $d$ 中的 $d_i , d_{i+1}$ 两项的值被**交换**了。

所以原问题被转化成：给定两个长度为 $n$ 的数组（设为 $a,b$），选择一个 $i$ 使 $1<i<n$（可以选择任意多次），交换 $a_i , a_{i+1}$，判断能否将数组 $a$ 变为数组 $b$。

我们可以将 $a,b$ 数组分别排序，判断排序后的两数组是否相同，如果相同则可行，反之亦然。此做法的正确性不难证明。

所以这个问题就解决了。

代码：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
const int N=1e5+5;
int n,f,a[N],b[N],c[N],d[N];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>a[i],c[i]=a[i]-a[i-1]; //差分
	for(int i=1;i<=n;i++)	cin>>b[i],d[i]=b[i]-b[i-1];
	if(a[1]!=b[1]||a[n]!=b[n]) //特判
	{
		cout<<"No";
		return 0;
	}
	sort(c+1,c+n+1); //排序
	sort(d+1,d+n+1);
	for(int i=1;i<=n;i++)
	{
		if(c[i]!=d[i])
		{
			f=1;
			break;
		}
	}
	if(!f)	cout<<"Yes";
	else	cout<<"No";
	return 0;
}
```


---

## 作者：Coros_Trusds (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15618990.html)

神仙题

# 题目大意

一次操作选择 $1 \lt i\lt n$，使 $c_i$ 变为 $c_i'$，$c_i'=c_{i+1}+c_{i-1}-c_i$。

是否能做若干次操作，使每个 $c_i$ 和 $t_i$ 相等？

# 题目分析

NOIP 2021 方差和这道题差不多。

差分，是前缀和的逆运算。形式化来说，长度为 $n$ 的序列 $a$ 的差分序列 $c$ 满足：

$i=1$ 时，$c_i=a_i$；

$2\le i\le n$ 时，$c_i=a_i-a_{i-1}$。

--------

首先发现，如果 $c_1\neq t_1$ 或 $c_n\neq t_n$，显然不可能，直接输出 $\verb!No!$ 即可。

--------

考虑原序列中的一段 $c_{i-1},c_i,c_{i+1}$，差分后，差分序列为：$c_{i-1}-c_{i-2},c_{i}-c_{i-1},c_{i+1}-c_i$。

进行一次操作后：$c_{i-1},c_{i-1}+c_{i+1}-c_i,c_{i+1}$，差分一下，发现此时为：$c_{i-1}-c_{i-2},c_{i+1}-c_i,c_i-c_{i-1}$。

发现差分序列中的数没有变，但是位置发生了变化。

同理可得，序列 $c$ 无论经过多少次操作，差分序列内的数都没有变，改变的惟有顺序。

所以我们求出序列 $c,t$ 的差分序列 $ca,ct$ 后，排序比较是否一致即可。

时间复杂度 $\operatorname{O}(n\log n)$。

# 代码

```cpp
//2021/11/29

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <cstdio>

#include <climits>//need "INT_MAX","INT_MIN"

#include <algorithm>

#define enter() putchar(10)

#define debug(c,que) cerr<<#c<<" = "<<c<<que

#define cek(c) puts(c)

#define blow(arr,st,ed,w) for(register int i=(st);i<=(ed);i++)cout<<arr[i]<<w;

#define speed_up() std::ios::sync_with_stdio(false)

#define endl "\n"

#define Input_Int(n,a) for(register int i=1;i<=n;i++)scanf("%d",a+i);

#define Input_Long(n,a) for(register long long i=1;i<=n;i++)scanf("%lld",a+i);

namespace Newstd
{
	inline int read()
	{
		int x=0,k=1;
		char ch=getchar();
		while(ch<'0' || ch>'9')
		{
			if(ch=='-')
			{
				k=-1;
			}
			ch=getchar();
		}
		while(ch>='0' && ch<='9')
		{
			x=(x<<1)+(x<<3)+ch-'0';
			ch=getchar();
		}
		return x*k;
	}
	inline void write(int x)
	{
		if(x<0)
		{
			putchar('-');
			x=-x;
		}
		if(x>9)
		{
			write(x/10);
		}
		putchar(x%10+'0');
	}
}

using namespace Newstd;

using namespace std;

const int MA=100005;

int a[MA],b[MA];

int sua[MA],sub[MA];

int n;

int main(void)
{
	n=read();
	
	Input_Int(n,a);
	
	Input_Int(n,b);
	
	if(a[1]!=b[1] || a[n]!=b[n])
	{
		puts("No");
		
		return 0;
	}
	
	sua[1]=a[1],sub[1]=b[1];
	
	for(register int i=2;i<=n;i++)
	{
		sua[i]=a[i]-a[i-1];
		
		sub[i]=b[i]-b[i-1];
	}
	
	sort(sua+1,sua+n+1);
	
	sort(sub+1,sub+n+1);
	
	for(register int i=1;i<=n;i++)
	{
		if(sua[i]!=sub[i])
		{
			puts("No");
			
			return 0;
		}
	}
	
	puts("Yes");
	
	return 0;
}
```

---

## 作者：_easy_ (赞：0)

# 思路
首先可以发现进行一次题目中的操作，可以使原数组的差分数组的进行操作的位置与前面一项交换。所以只需要判断两个题目中的数组的差分数组排序后是否一样就行了。下面给出证明。

假设相邻三项分别为 $a,b,c$。我们操作 $b$ 时，$b$ 会变成 $a+c-b$。所以差分数组就会由 ${a-b,b-c}$ 变成 ${-c+b,a-b}$，也就是交换了进行操作的位置与前面一项，也就是第一项与第二项。

**注意**：这个操作不能改变首尾两项，所以要特断两个数组的首位两项是否一样，不一样就输出 $No$。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[100005],b[100005],c[100005],d[100005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		b[i]=a[i]-a[i-1];
	}
	b[1]=INT_MAX;//去除第一项，因为第一项不属于差分数组
	for(int i=1;i<=n;i++){
		cin>>c[i];
		d[i]=c[i]-c[i-1];
	}
	d[1]=INT_MAX;//与上面同理
	if(a[1]^c[1]||a[n]^c[n]){
		cout<<"No";
		return 0;
	}//特判
	sort(b+1,b+n+1);
	sort(d+1,d+n+1);
	for(int i=1;i<n;i++){
		if(b[i]^d[i]){
			cout<<"No";
			return 0;
		}
	}
	cout<<"Yes";
	return 0;
}

```

---

## 作者：_AKIOI_ (赞：0)

## 题意简述

略

## 题目分析

首先：易发现首位和尾位的值无法被改变值，如果这两个位置的值不同，必定无解。

再观察: 
定义:   $1 < i < n$

先写出原来序列:

$c[1]  c[2]  ...  c[i-1]  c[i]  c[i+1]  ...  c[n-1]  c[n]$

再改变$c[i]$后序列:

$c[1]  c[2]  ...  c[i-1]  c[i+1]+c[i-1]-c[i]  c[i+1] ...c[n]$

我们不妨定义:   $a[i] = c[i]-c[i-1]$


原来的$a[i]$：     $...... c[i-1]-c[i-2]  c[i]-c[i-1]  c[i+1]-c[i]  c[i+2]-c[i+1]    ......$


改变$c[i]$后的$a[i]$:

$...  c[i-1]-c[i-2]  c[i+1]-c[i]  c[i]-c[i-1]  c[i+2]-c[i+1]    ......$

易发现：交换了原来 $c[i]$ 左右两边的差分数组。

即：一次操作的本质是交换两边的差分数组。 
因为首位和尾位必定相同（否则无解），

且：$c[2]=c[1]+a[2],c[3]=c[2]+a[3]......c[n-1]=c[n-2]+a[n-1]$

若最终能变成相同序列：只要两个序列的 $a[i]$ (差分数组）能通过交换后变为相等，就可以。 
判断是否相同的最简单的方式：排序+线扫 
```
#include<bits/stdc++.h>
using namespace std;
int n;
int c[200005];
int t[200005];
int x[200005];//c的差分数组 
int y[200005];//t的差分数组 
signed main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",c+i);
	for (int i=1;i<=n;i++) scanf("%d",t+i);
	if (c[1]!=t[1]||c[n]!=t[n]) return puts("No"),0;
	for (int i=1;i<=n;i++) x[i]=c[i]-c[i-1],y[i]=t[i]-t[i-1];//求差分数组
	sort(x+1,x+n+1);
	sort(y+1,y+n+1);
	for (int i=1;i<=n;i++) if (x[i]!=y[i]) return puts("No"),0;
	puts("Yes");
    	return 0;
}
```


---

## 作者：MILLOPE (赞：0)

## my blog
[my blog](https://blog.csdn.net/qq_34493840/article/details/95019556)
## 题目
>[题目传送门](https://www.luogu.org/problemnew/show/CF1110E)
![在这里插入图片描述](https://img-blog.csdnimg.cn/2019070719260796.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM0NDkzODQw,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20190707192701127.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM0NDkzODQw,size_16,color_FFFFFF,t_70)

## 题解
- 定义：
$$d_i = c_i - c_{i-1}$$
- 对于每次操作
$$c_i' = c_{i+1} + c_{i-1} - c_i$$ 
- $$d_i'=c_i'-c_{i-1}=c_{i+1}+c_{i-1}-c_i-c_{i-1}=d_{i+1}$$
- $$d_{i+1}'=c_{i+1}-c_i'=c_{i+1}-(c_{i+1}+c_{i-1}-c_i)=d_i$$
- 我们可以发现对于一次操作，就相当于将相邻两个数的查分数组交换位置，我们只需判断原系列和目标序列的查分序列是否相同即可。
- 因为序列的开头和结尾不能操作(若$c_1$为序列开头则$c_0$不在此序列中，$c_n$同理)，所以若开头结尾不同，则无解。

## code
```cpp
#include <bits/stdc++.h> 
using namespace std; 
const int maxn = 2e5 + 100; 
typedef long long LL; 

template <typename T> 
inline void read(T &s) {
	s = 0; 
	T w = 1, ch = getchar(); 
	while (!isdigit(ch)) { if (ch == '-') w = -1; ch = getchar(); }
	while (isdigit(ch)) { s = (s << 1) + (s << 3) + (ch ^ 48); ch = getchar(); }
	s *= w; 
}

int n; 
int a[maxn], t[maxn]; 
int ca[maxn], ct[maxn]; 

int main() {
//	freopen("1.in", "r", stdin); 
	read(n); 
	for (int i = 1; i <= n; ++i) read(a[i]); 
	for (int i = 1; i <= n; ++i) read(t[i]); 
	
	if (a[1] ^ t[1] || a[n] ^ t[n]) {
		puts("No"); 
		exit(0); 
	}
	
	for (int i = 1; i <= n; ++i) {
		ca[i] = a[i] - a[i - 1]; 
		ct[i] = t[i] - t[i - 1]; 
	}
	sort(ca + 1, ca + n + 1); 
	sort(ct + 1, ct + n + 1); 
	for (int i = 1; i <= n; ++i) {
		if (ca[i] ^ ct[i]) {
			puts("No"); 
			exit(0); 
		}
	}
	puts("Yes"); 
	return 0; 
}
```
 

---

## 作者：onglu (赞：0)

## 题意  
给定两个长度为$n$的序列，我们可以对第一个序列进行操作，每次可以选定第$2\le i \le n-1$个元素$c_i$，把它的值变为$c_{i-1}+c_{i+1}-c_{i}$。  
问经过若干次操作之后能不能变成第二个序列。  
## 分析  
首先两端的元素是不能操作的，那么就要求两端的元素必须一样。  

然后我们看每次操作改变了什么。  

大力找，发现每次操作之后差分数组上相邻两个位置发生了交换。  

那么我们对两个序列的差分数组进行排序，判断它们是不是一样就可以了。  
## 代码  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+1009;
int read(){
	char c;int num,f=1;
	while(c=getchar(),!isdigit(c))if(c=='-')f=-1;num=c-'0';
	while(c=getchar(), isdigit(c))num=num*10+c-'0';
	return f*num;
}
int n,a[N],b[N];
int aa[N],bb[N];
int main()
{
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	if(a[1]!=b[1]||a[n]!=b[n]){
		cout<<"No"<<endl;
		return 0;
	}
	for(int i=2;i<=n;i++){
		aa[i]=a[i]-a[i-1];
		bb[i]=b[i]-b[i-1];
	}
	sort(aa+2,aa+n+1);
	sort(bb+2,bb+n+1);
	for(int i=2;i<=n;i++){
		if(aa[i]!=bb[i]){
			cout<<"No"<<endl;
			return 0;
		}
	}
	cout<<"Yes"<<endl;
	return 0;
}


```

---

## 作者：xukuan (赞：0)

声明：本题解有参考[这场比赛的官方题解](https://codeforces.com/blog/entry/65079)

思路是差分，很难想

令d[i]=c[i+1]-c[i],e[i]=t[i+1]-t[i] i被包含在[1,n)

改变c[i] i被包含在[2,n) 得

d′[j−1]=c′[j]−c[j−1]=(c[j+1]+c[j−1]−c[j])−c[j−1]=c[j+1]−c[j]=d[j]

d′[j]=c[j+1]−c′[j]=c[j+1]−(c[j+1]+c[j−1]−c[j])=c[j]−c[j−1]=d[j−1]

其中x'[j]表示x[j]操作之后的值

我们可以发现，对c数组进行一次操作的实质就是交换d数组的相邻两个数

得到结论

如果c[1]!=t[1],肯定无解

当c[1]==t[1]时，统计d和e中每个数出现的次数，不同则无解，相同则有解

这里不用判断c[n]和t[n]是否相等，因为当c[1]==t[1]时，如果c[n]!=t[n],d数组与e数组一定不同

代码：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
#define MAX 1000010
using namespace std;

ll n,c[MAX],t[MAX],d[MAX],e[MAX],ans;
map<ll,ll> D,E;

int main(){
	cin>>n;
	for(ll i=1; i<=n; i++) scanf("%lld",&c[i]);
	for(ll i=1; i<=n; i++) scanf("%lld",&t[i]);
	for(ll i=1; i<n; i++) d[i]=c[i+1]-c[i];//算出c数组之间的差距
	for(ll i=1; i<n; i++) e[i]=t[i+1]-t[i];//算出t数组之间的差距
	if(c[1]!=t[1]){//第一个数不相同
		printf("No");
		return 0;
	}
	
	for(ll i=1; i<n; i++){
		D[d[i]]++; E[e[i]]++;//统计差分的数组中每一个数出现的差距
	}
    
    //判断，有不同就输出No
	for(ll i=1; i<n; i++){
		if(D[d[i]]!=E[d[i]]){
			printf("No");
			return 0;
		}
	}
	for(ll i=1; i<n; i++){
		if(D[e[i]]!=E[e[i]]){
			printf("No");
			return 0;
		}
	}
	printf("Yes");//没有不同，输出Yes
    return 0;
}
```

---

