# A Twisty Movement

## 题目描述

A dragon symbolizes wisdom, power and wealth. On Lunar New Year's Day, people model a dragon with bamboo strips and clothes, raise them with rods, and hold the rods high and low to resemble a flying dragon.

A performer holding the rod low is represented by a $ 1 $ , while one holding it high is represented by a $ 2 $ . Thus, the line of performers can be represented by a sequence $ a_{1},a_{2},...,a_{n} $ .

Little Tommy is among them. He would like to choose an interval $ [l,r] $ ( $ 1<=l<=r<=n $ ), then reverse $ a_{l},a_{l+1},...,a_{r} $ so that the length of the longest non-decreasing subsequence of the new sequence is maximum.

A non-decreasing subsequence is a sequence of indices $ p_{1},p_{2},...,p_{k} $ , such that $ p_{1}<p_{2}<...<p_{k} $ and $ a_{p1}<=a_{p2}<=...<=a_{pk} $ . The length of the subsequence is $ k $ .

## 说明/提示

In the first example, after reversing $ [2,3] $ , the array will become $ [1,1,2,2] $ , where the length of the longest non-decreasing subsequence is $ 4 $ .

In the second example, after reversing $ [3,7] $ , the array will become $ [1,1,1,1,2,2,2,2,2,1] $ , where the length of the longest non-decreasing subsequence is $ 9 $ .

## 样例 #1

### 输入

```
4
1 2 1 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
10
1 1 2 2 2 1 1 2 2 1
```

### 输出

```
9
```

# 题解

## 作者：浅色调 (赞：26)

### Solution：

　　本题水考的T3，一道思维题。

　　因为$a_i$只有$1,2$两种可能，于是我们可以确定的是答案一定是：$[1,1,1,…]\;[2,2,2…]\;[1,1,1…]\;[2,2,2…]$这样的四段子序列（每一段都允许为空），使得第二、三段所在区间翻转得到答案（不翻转可以理解为二、三段为空序列）。

　　**解法一：**

　　　　我们可以从左往右做前缀和$ct1[i]$表示$[1,i]$出现的$1$的个数，同理做出后缀和$ct2[i]$表示$[i,n]$出现的$2$的个数。然后我们枚举断点$k,k\in[1,n+1]$（即二、三段的分界点），设一、二段的分界点为$p,p\in[1,k]$，三、四段的分界点为$q,q\in[k,n+1]$，那么显然答案为$(ct1[p-1])+(ct2[p]-ct2[k])+(ct1[q-1]-ct1[k])+(ct2[q])$，式子中括号括起来的为一段，这个式子可以化为$(ct1[p-1]+ct2[p]+ct1[q-1]+ct2[q])-(ct1[k]+ct2[k]),p\in[1,k],q\in[k,n+1]$，注意到对于一个确定的$k$，我们要最大化前面括号的式子，而前者可以用线段树维护下$ct1[i-1]+ct2[i]$，那么只用枚举$k$，再两次区间最大值查询，更新答案就好了。

　　　　时间复杂度$O(n\log n)$。

　　**代码：**
  ```cpp
/*Code by 520 -- 10.20*/
#include<bits/stdc++.h>
#define il inline
#define ll long long
#define RE register
#define For(i,a,b) for(RE int (i)=(a);(i)<=(b);(i)++)
#define Bor(i,a,b) for(RE int (i)=(b);(i)>=(a);(i)--)
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
using namespace std;
const int N=1000005;
int n,ans,ct1[N],ct2[N],a[N],ppx[N];
struct SGT{
    int maxn[N<<2];
    il void pushup(int rt){maxn[rt]=max(maxn[rt<<1],maxn[rt<<1|1]);}
    void build(int l,int r,int rt){
        if(l==r) {maxn[rt]=ppx[l];return;}
        int m=l+r>>1;
        build(lson),build(rson);
        pushup(rt);
    }
    int query(int L,int R,int l,int r,int rt){
        if(L<=l&&R>=r) return maxn[rt];
        int m=l+r>>1,res=0;
        if(L<=m) res=max(res,query(L,R,lson));
        if(R>m) res=max(res,query(L,R,rson));
        return res;
    }
}T;

int main(){
    scanf("%d",&n); int t1,t2;
    For(i,1,n) scanf("%d",a+i),ct1[i]=ct1[i-1]+(a[i]==1);
    Bor(i,1,n) ct2[i]=ct2[i+1]+(a[i]==2);
    For(i,1,n+1) ppx[i]=ct1[i-1]+ct2[i];
    T.build(1,n+1,1);
    For(k,1,n+1) {
        t1=T.query(1,k,1,n+1,1),t2=T.query(k,n+1,1,n+1,1);
        ans=max(ans,t1+t2-ct1[k-1]-ct2[k]);
    }
    cout<<ans;
    return 0;
}
```
$\quad\;\;$**解法二：**

　　　　我们~~显然（事实上考试只想出了解法一）~~可以用DP来维护每段的最大值。

　　　　定义状态$f[i][1]$表示前$i$个数中前一段的答案，$f[i][2]$表示前$i$个数中前两段的答案，$f[i][3]$表示前$i$个数中前三段的答案，$f[i][4]$表示前$i$个数中前四段的答案。

　　　　那么不难得到状态转移方程：

　　　　$f[i][1]=f[i-1][1]+(a_i==1)$

　　　　$f[i][2]=max(f[i-1][1],f[i-1][2]+(a_i==2))$

　　　　$f[i][3]=max(f[i-1][2],f[i-1][3]+(a_i==1))$

　　　　$f[i][4]=max(f[i-1][3],f[i-1][4]+(a_i==2))$

　　　　显然第一维是可以压掉的,时间复杂度$O(n)$。

　　**代码：**
  
  ```cpp
/*Code by 520 -- 10.20*/
#include<bits/stdc++.h>
#define RE register
#define For(i,a,b) for(RE int (i)=(a);(i)<=(b);(i)++)
using namespace std;
int n,x,f[5];

int main(){
    scanf("%d",&n);
    For(i,1,n) 
        scanf("%d",&x),
        f[1]+=(x==1),
        f[2]=max(f[1],f[2]+(x==2)),
        f[3]=max(f[2],f[3]+(x==1)),
        f[4]=max(f[3],f[4]+(x==2));
    cout<<f[4];
    return 0;
}
```
$\quad\;\;$欢迎来踩博客：[five20](https://www.cnblogs.com/five20/p/9862456.html)（蒟蒻写题解不易，转载请注明出处，万分感谢！～）
  

---

## 作者：蒟蒻丁 (赞：10)

这题又开阔了我的眼界

不考虑翻转这个条件，a[i]只有1和2时，就很是快乐

最长不下降子序列肯定长这样

$11……22……$

我们处理一下，把1和2放在两组中

$[11……][22……]$

定义 $f[i][j]$ (j为1或2)为前i个点，第i个点属于第j组
$$f[i][1]=f[i-1][j]+(a[i]==1)$$
$$f[i][2]=max(f[i-1][1],f[i-1][2]+(a[i]==2))$$
考虑一下翻转,比如

$1112212211212222$

它翻转后的最长不下降子序列是

$11111122222222$

（翻转区间 $4、12$）
要是我们翻转回来，这个序列就变成了

$11122221112222$

发现它可以分为4组
$[111][2222][111][2222]$ (毕竟这样的话交换23区间就变成了上面的情况了)

所以就可以列出方程
$$f[i][1]=f[i-1][1]+(a[i]==1)$$
$$f[i][2]=max(f[i-1][1],f[i-1][2]+(a[i]==2)$$
$$f[i][3]=max(f[i-1][2],f[i-1][3]+(a[i]==1)$$
$$f[i][4]=max(f[i-1][3],f[i-1][4]+(a[i]==2)$$

然后我们压掉第一维就可

提供一个理解思路（以 $f[i][2]$ 为例）

1.从 $f[i-1][1]$ 转移：开启一个新的组

2.从 $f[i-][2]$ 转移：往已经开启的组添加一个数
```
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;
ll n,m,f[10],ans;

int main(){
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++){
		ll a1;
		scanf("%lld",&a1);
		f[1]+=(a1==1);
		f[2]=max(f[1],f[2]+(a1==2));
		f[3]=max(f[2],f[3]+(a1==1));
		f[4]=max(f[3],f[4]+(a1==2));
	}
	cout<<f[4];
}
```


---

## 作者：Karry5307 (赞：6)

### 题意

给定一个长度为 $n$ 且只包含 $1$ 或 $2$ 的序列 $a$，你可以翻转一次序列的某个区间，求翻转后最长不降子序列的长度。

$\texttt{Data Range:}n\leq 2000$

### 题解

这题应该随便写吧，$n$ 开到 $2\times 10^6$ 都无所谓了，做完之后看了看题解区发现没人思路跟我一样，所以来写一下。

考虑最终的序列只可能分成四段区间，第一段选 $1$，第二段选 $2$，第三段选 $1$，第四段选 $2$，然后翻转中间两段。注意这四段中任何一段都可以为空。

然后考虑枚举第二段和第三段的分界线，这样两边都是先选一些 $1$ 再选一些 $2$。

考虑 DP。借用 P6009 的思路，设 $f_{i,j}$ 表示 $1\sim i$ 中最后一段选 $j$ 的最长不降子序列长度，$g_{i,j}$ 表示 $i\sim n$ 中最后一段选 $j$ 的最长不降子序列长度，于是有如下转移：

$$f_{i,j}=\begin{cases}f_{i-1,j}&,a_i\neq j\\f_{i-1,1}+1&,a_i=j=1\\\max(f_{i-1,1},f_{i-1,2}+1)&,a_i=j=2\end{cases}$$

以及

$$g_{i,j}=\begin{cases}g_{i+1,j}&,a_i\neq j\\\max(g_{i+1,1},g_{i+1,2})+1&,a_i=j=1\\g_{i+1,2}+1&,a_i=j=2\end{cases}$$

最后枚举一下分界线，答案为 $\max(f_{i,2}+g_{i+1,1})$，时间复杂度 $O(n)$。不知道为什么这个题打了一个线段树的 tag。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e5+51; 
ll n,res;
ll x[MAXN],f[MAXN][3],g[MAXN][3];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
int main()
{
	n=read();
	for(register int i=1;i<=n;i++)
	{
		x[i]=read();
	}
	for(register int i=1;i<=n;i++)
	{
		f[i][1]=f[i-1][1],f[i][2]=f[i-1][2];
		x[i]==1?f[i][1]++:f[i][2]=max(f[i][1],f[i][2])+1;
	}
	for(register int i=n;i;i--)
	{
		g[i][1]=g[i+1][1],g[i][2]=g[i+1][2];
		x[i]==2?g[i][2]++:g[i][1]=max(g[i][1],g[i][2])+1;
	}
	for(register int i=0;i<=n;i++)
	{
		res=max(res,f[i][2]+g[i+1][1]);
	}
	printf("%d\n",res);
}
```

---

## 作者：2huk (赞：4)

[Codeforces Round 462 (Div. 1) A - A Twisty Movement](https://codeforces.com/problemset/problem/933/A)

## 题目描述

给定一个由 $1$ 和 $2$ 组成的序列，你可以进行至多一次操作，翻转其中的一个区间内的数。求翻转后的序列的最长非降子序列。

$n \le 2000, a_i \in \{1, 2\}$

## 分析

考虑 `DP`。

由于序列只有两个数，那么最终的非降子序列一定是 $\{1, 1, \dots 1, 2, 2, \dots, 2\}$ 这样的形式。可以这样表示：$[1][2]$，表示分别由 $1$ 和 $2$ 组成的序列。其中这两个部分可能为空。

如果翻转后得到 $[1][2]$，那么翻转前的子序列应该是 $[1][2][1][2]$ 的形式，使得交换中间两个子序列后变成非降子序列。同样的，这些序列也可以为空。

因为最多交换一次，所以题目变成了找原序列的最长子序列，且形式为 $[1][2][1][2]$。

一共有 $4$ 部分，分别将其标号为 $0 \sim 3$。设状态 $f_{i, j}(j \in [0, 3])$ 表示序列前 $i$ 个数中，选择前 $j$ 个序列的最长长度。接下来考虑转移。

- $f_{i, 0}$，前 $0$ 个部分：

  如果第 $i$ 个数为 $1$，那么可以把这个数和以前的拼起来。答案为 $f_{i - 1, 0} + 1$。

  否则，如果第 $i$ 个数为 $2$，那么这个数不可以作为第 $0$ 部分。答案为 $f_{i - 1, 0}$。

  因此 $f_{i, 0} = \left\{\begin{matrix} f_{i - 1, 0} + 1 & (a_i = 1)\\ f_{i - 1, 0} & (a_i = 2)\end{matrix}\right.$。

- $f_{i, 1}$，前 $1$ 个部分。

  如果第 $1$ 个部分为空，那么答案为 $f_{i, 0}$。以下都是不空的情况。

  如果第 $i$ 个数为 $2$，那么可以把这个数和以前的拼起来。答案为 $f_{i - 1, 1} + 1$。

  否则，如果第 $i$ 个数为 $1$，那么这个数不可以作为第 $1$ 部分。答案为 $f_{i - 1, 1}$。

  因此 $f_{i, 1} = \left\{\begin{matrix} \max(f_{i, 0}, f_{i - 1, 1} + 1) & (a_i = 2)\\ \max(f_{i, 0}, f_{i - 1, 1}) & (a_i = 1)\end{matrix}\right.$。

- $f_{i, 2}$，前 $2$ 个部分。

  如果第 $2$ 个部分为空，那么答案为 $f_{i, 1}$。以下都是不空的情况。

  如果第 $i$ 个数为 $1$，那么可以把这个数和以前的拼起来。答案为 $f_{i - 1, 2} + 1$。

  否则，如果第 $i$ 个数为 $2$，那么这个数不可以作为第 $2$ 部分。答案为 $f_{i - 1, 2}$。

  因此 $f_{i, 2} = \left\{\begin{matrix} \max(f_{i, 1}, f_{i - 1, 2} + 1) & (a_i = 1)\\ \max(f_{i, 1}, f_{i - 1, 2}) & (a_i = 2)\end{matrix}\right.$。

- $f_{i, 3}$，前 $3$ 个部分。

  如果第 $3$ 个部分为空，那么答案为 $f_{i, 2}$。以下都是不空的情况。

  如果第 $i$ 个数为 $2$，那么可以把这个数和以前的拼起来。答案为 $f_{i - 1, 3} + 1$。

  否则，如果第 $i$ 个数为 $1$，那么这个数不可以作为第 $3$ 部分。答案为 $f_{i - 1, 3}$。

  因此 $f_{i, 3} = \left\{\begin{matrix} \max(f_{i, 2}, f_{i - 1, 3} + 1) & (a_i = 2)\\ \max(f_{i, 2}, f_{i - 1, 3}) & (a_i = 1)\end{matrix}\right.$。

最后答案为 $f_{n, 3}$。

[$\text{Code}$](https://www.luogu.com.cn/paste/9m594pwq)



---

## 作者：gesong (赞：2)

题目传送门：[CF933A](https://www.luogu.com.cn/problem/CF933A)。
# 思路
这道题一看就是**线性 dp**。

由于这道题 $1 \le a_i \le 2$ 所以，我们发现最长不下降子序列一定是 $[1,1,1,...,1,2,2,2,...2]$ 所以我们可以把他分成四段：$[1,1,1,...][2,2,2,...][1,1,1,...][2,2,2,...]$ 然后用 $0$ $1$ $2$ $3$ 表示，于是我们就可以 dp 了。

**状态表示**： $f_{i,j}$ 表示现在到了第 $i$ 个数，且现在是第 $j$ 段，且 $1\le i\le n $ $0\le j\le 3$。

**状态转移**：

$f_{i,0}$

由于是第 $0$ 段，所以只能从前一项转移即 $f_{i-1,0}$ 最后加上判断 $a_i$ 是否是 $1$ 即可。

所以转移方程是：$f_{i,0}=f_{i-1,0}+(a_i=1)$。

$f_{i,1}$

由于是第 $1$ 段，所以可以从 $f_{i,0}$ 进行转移，最后与自己前一项转移加上判断 $a_i$ 是否是 $2$ 取最大值。

所以转移方程是：$f_{i,1}=\max(f_{i,0},f_{i-1,1}+(a_i=2))$。

$f_{i,2}$

由于是第 $2$ 段，所以可以从 $f_{i,1}$ 进行转移，最后与自己前一项转移加上判断 $a_i$ 是否是 $1$ 取最大值。

所以转移方程是：$f_{i,2}=\max(f_{i,1},f_{i-1,2}+(a_i=1))$。

$f_{i,3}$

由于是第 $3$ 段，所以可以从 $f_{i,2}$ 进行转移，最后与自己前一项转移加上判断 $a_i$ 是否是 $2$ 取最大值。

所以转移方程是：$f_{i,3}=\max(f_{i,2},f_{i-1,3}+(a_i=2))$。

最后答案就是最后一项的第 $3$ 段即为 $f_{n,3}$。

# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int f[2001][4],a[1234567]; 
main(){
	int n;
	cin>>n;
	for (int i=1;i<=n;i++) cin>>a[i];
	for (int i=1;i<=n;i++){//转移方程
		f[i][0]=f[i-1][0]+(a[i]==1);
		f[i][1]=max(f[i][0],f[i-1][1]+(a[i]==2));
		f[i][2]=max(f[i][1],f[i-1][2]+(a[i]==1));
		f[i][3]=max(f[i][2],f[i-1][3]+(a[i]==2));
	}
	cout <<f[n][3];
    return 0;
}
```

---

## 作者：NaVi_Awson (赞：2)

## Description

[题库链接](http://codeforces.com/problemset/problem/933/A)

给你一个长度为 $n$ 的只含有 $1,2$ 的序列。你可以选择其中的一段 $[l,r]$ ，将区间翻转，翻转后使得单调不下降序列最长。求最长长度。

$1\leq n\leq 2000$

## Solution

考虑线段树维护一系列矩阵，分别表示区间内所选的数字由 $1\rightarrow 1,1\rightarrow 2,2\rightarrow 1,2\rightarrow 2$ 变化的最长不下降序列的长度。

我们枚举翻转区间的左右端点，线段树上分三段查询。再在三段区间间讨论即可。

## Code

```cpp
//It is made by Awson on 2018.2.14
#include <bits/stdc++.h>
#define LL long long
#define dob complex<double>
#define Abs(a) ((a) < 0 ? (-(a)) : (a))
#define Max(a, b) ((a) > (b) ? (a) : (b))
#define Min(a, b) ((a) < (b) ? (a) : (b))
#define Swap(a, b) ((a) ^= (b), (b) ^= (a), (a) ^= (b))
#define writeln(x) (write(x), putchar('\n'))
#define lowbit(x) ((x)&(-(x)))
using namespace std;
const int N = 2000;
void read(int &x) {
    char ch; bool flag = 0;
    for (ch = getchar(); !isdigit(ch) && ((flag |= (ch == '-')) || 1); ch = getchar());
    for (x = 0; isdigit(ch); x = (x<<1)+(x<<3)+ch-48, ch = getchar());
    x *= 1-2*flag;
}
void print(int x) {if (x > 9) print(x/10); putchar(x%10+48); }
void write(int x) {if (x < 0) putchar('-'); print(Abs(x)); }

int n, a[N+5], sum2, ans;
struct mat {
	int a[2][2];
	mat() {a[0][0] = a[0][1] = a[1][0] = a[1][1] = 0; }
	mat operator * (const mat &b) const {
		mat ans;
		ans.a[0][0] = a[0][0]+b.a[0][0];
		ans.a[0][1] = Max(a[0][0]+b.a[0][1], a[0][1]+b.a[1][1]);
		ans.a[1][0] = Max(a[1][1]+b.a[1][0], a[1][0]+b.a[0][0]);
		ans.a[1][1] = a[1][1]+b.a[1][1];
		return ans;
	}
};
struct Segment_Tree {
	mat sgm[(N<<2)+5];
	#define lr(o) (o<<1)
	#define rr(o) (o<<1|1)
	void build(int o, int l, int r) {
		if (l == r) {
			if (a[l] == 1) sgm[o].a[0][0] = sgm[o].a[1][0] = 1;
			else sgm[o].a[0][1] = sgm[o].a[1][1] = 1;
			return;
		}
		int mid = (l+r)>>1;
		build(lr(o), l, mid), build(rr(o), mid+1, r);
		sgm[o] = sgm[lr(o)]*sgm[rr(o)];
	}
	mat query(int o, int l, int r, int a, int b) {
		if (a <= l && r <= b) return sgm[o];
		int mid = (l+r)>>1;
		if (b <= mid) return query(lr(o), l, mid, a, b);
		if (a > mid) return query(rr(o), mid+1, r, a, b);
		return query(lr(o), l, mid, a, b)*query(rr(o), mid+1, r, a, b);
	}
}T1;

void work() {
	read(n);
	for (int i = 1; i <= n; i++) read(a[i]), sum2 += (a[i] == 2);
	if (sum2 == n || sum2 == 0) {writeln(n); return; }
	T1.build(1, 1, n); ans = Max(T1.sgm[1].a[0][0], T1.sgm[1].a[0][1]); ans = Max(ans, T1.sgm[1].a[1][1]);
	for (int l = 1; l <= n; l++) for (int r = l+1; r <= n; r++) {
		mat a, b, c;
		if (l != 1) a = T1.query(1, 1, n, 1, l-1);
		b = T1.query(1, 1, n, l, r);
		if (r != n) c = T1.query(1, 1, n, r+1, n);
		ans = Max(ans, a.a[0][1]+b.a[1][1]+c.a[1][1]);
		ans = Max(ans, a.a[0][0]+b.a[1][0]+c.a[1][1]);
		ans = Max(ans, a.a[0][0]+b.a[0][0]+c.a[0][1]);
	}
	writeln(ans);
}
int main() {
	work(); return 0;
}
```

---

## 作者：_sh1kong_ (赞：1)

由于 $a_i \le 2$，那么答案的序列必定为 $[1, 1, \ldots][2, 2, \ldots][1, 1, \ldots][2, 2, \ldots]$（每一段都可以为空），接着我们便可以翻转第二段和第三段子序列，得到最佳答案。

### 做法：

很简单的一个线性 dp。

状态定义：我们定义 ${dp_i}_j$ 为现在到了第 $i$ 个数，第 $j$ 段子序列。 

状态转移：
$$
\begin{cases}
{dp_i}_0 = {dp_{i - 1}}_0 + [a_i = 1]\\
{dp_i}_1 = \max\{{dp_i}_0, {dp_{i - 1}}_1 + [a_i = 2]\}\\
{dp_i}_2 = \max\{{dp_i}_1, {dp_{i - 1}}_2 + [a_i = 1]\}\\
{dp_i}_3 = \max\{{dp_i}_2, {dp_{i - 1}}_3 + [a_i = 2]\}\\
\end{cases}
$$

时间复杂度 $\mathcal{O}(N)$。

### 代码：

```cpp
#include <bits/stdc++.h>

const int N = 2e3 + 5, M = 7, K = 27;

using namespace std;

int n;

int d[N], f[5];

signed main()

{
	cin >> n;
	for (int i = 1; i <= n; i ++ ) cin >> d[i];
	for (int i = 1; i <= n; i ++ )
	{
		f[1] += (d[i] == 1);
		f[2] = max(f[1], f[2] + (d[i] == 2));
		f[3] = max(f[2], f[3] + (d[i] == 1));
		f[4] = max(f[3], f[4] + (d[i] == 2));
	}
	cout << f[4];
}
```

---

## 作者：Ba_creeper (赞：1)

#### 题目分析
这题乍一看不好想，但是看到 $1 \leq a_i \leq 2$ 时，便发现有玄机。

可得知最终答案是在 $[1,1,1,...][2,2,2,...][1,1,1,...][2,2,2,...]$ 这样的序列中，通过翻转第 $2$，$3$ 个序列之后得出。

我们可以用动态规划来维护每一段的最大值。

定义 $f[i][j]$ 为前 $i$ 个数中前 $j$ 段的答案。

对于序列

$111112222$

可以将其按上面分成两组。

合理运用一下判等，

则有

$$
f[i][1]=f[i-1][j]+(a[i]==1)
$$

$$
f[i][2]=max(f[i−1][1],f[i−1][2]+(a[i]==2))
$$

对于序列

$12212211212$

得到最终答案时的最长不下降子序列是：

$111122222$

在此基础上翻转回去，则为：

$122221112$

发现它符合上面的按 $4$ 个组的分组形式。

则有

$$
f[i][3]=max(f[i−1][2],f[i−1][3]+(a[i]==1)
$$

$$
f[i][4]=max(f[i−1][3],f[i−1][4]+(a[i]==2)
$$

观察，发现状态转移方程可以压掉第一维。

#### 核心代码
```cpp
ll n,ans,f[12];
int main()
{
    n=read();
    for (ll i = 1; i <= n; i++)
    {
        ll tmp;
        scanf("%lld", &tmp);
        f[1] += (tmp == 1);
        f[2] = max(f[1], f[2] + (tmp == 2));
        f[3] = max(f[2], f[3] + (tmp == 1));
        f[4] = max(f[3], f[4] + (tmp == 2));
    }
    printf("%lld\n",f[4]);
    return 0;
}
```


---

## 作者：ZHANGyutao123 (赞：0)

## 题目链接：[CF933A A Twisty Movement](https://www.luogu.com.cn/problem/CF933A)


# 题目描述：

有一个长度为 $n$ 的序列 $a_1,a_2,...,a_n$，其中元素为 $1$ 或 $2$。请找到长度最长的连续子序列，使得将其翻转后，该序列满足非降序列。

# 思路：

我们考虑 DP：

设 $dp_{i,j}$ 表示考虑前 $i$ 个位置，以 $j$ 结尾的不下降子序列最长长度。

考虑到只有 $1$ 和 $2$ 两种数字，不妨将其映射到状态空间上：

- $dp_{i,0}$ 表示前 $i$ 个数，以 $1$ 结尾的最长非降序列的长度，但是还没有操作过。
- $dp_{i,1}$ 表示前 $i$ 个数，以 $2$ 结尾的最长非降序列的长度，但是还没有操作过。
- $dp_{i,2}$ 表示前 $i$ 个数，以 $1$ 结尾的最长非降序列的长度，已经操作过一次。
- $dp_{i,3}$ 表示前 $i$ 个数，以 $2$ 结尾的最长非降序列的长度，已经操作过一次。

由题目可知，以 $1$ 或 $2$ 结尾有两个状态，又因为翻转区间无非有两种情况，所以：

- 区间内原有 $1$ 的个数为 $k_1$， $2$ 的个数为 $k_2$，则翻转之后，原有 $1$ 的个数变为 $k_2$， $2$ 的个数变为 $k_1$，反之亦然。
- 区间内只有一种数，则翻转区间对该数的影响相当于没有翻转。

那么状态转移方程就可以列出：

- $dp_{i,0} = dp_{i - 1,0}+[a_i=1]$
- $dp_{i,1} = \max(dp_{i,0},dp_{i-1,1}+[a_i=2])$
- $dp_{i,2} = \max(dp_{i,1},dp_{i-1,2}+[a_i=1])$
- $dp_{i,3} = \max(dp_{i,2},dp_{i-1,3}+[a_i=2])$

最终所求答案就是 $dp_{n,3}$。
# 代码
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 2010;
int n;
int seq[N]; // 存储序列
int dp[N][4]; // dp数组
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> seq[i]; // 读入序列
	for (int i = 1; i <= n; i++) {
		// 转移
		dp[i][0] = dp[i - 1][0] + (seq[i] == 1); 
		dp[i][1] = max(dp[i][0], dp[i - 1][1] + (seq[i] == 2)); 
		dp[i][2] = max(dp[i][1], dp[i - 1][2] + (seq[i] == 1)); 
		dp[i][3] = max(dp[i][2], dp[i - 1][3] + (seq[i] == 2)); 
	}
	cout << dp[n][3]; // 输出dp[n][3]，即前n个数中，以2为结尾的最长不下降子序列长度
	return 0;
}
```


---

## 作者：aimcf (赞：0)

$\color{blue}{\texttt{Difficulty : 1800}}$

DP。

$f_{i,1/2/3/4}$ 表示 $1\sim i$ 区间里前 $1/2/3/4$ 段的最长长度。

那么有：

如果 $a_i=1$，那么 $f_{i,1}=f_{i-1,1}+1$，$f_{i,3}=\max(f_{i-1,3}+1, f_{i-1,2})$。

否则，$f_{i,2}=\max(f_{i-1,2}+1,f_{i-1,1})$，$f_{i,4}=\max(f_{i-1,4}+1,f_{i-1,3})$。

其他情况 $f_{i,1/2/3/4}$ 不变。

答案是 $\max f_{i,4}$。

时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int f[5];
int main(){
  int n;
  cin>>n;
  for(int i=1;i<=n;i++){
    int x;
    cin>>x;
    if(x==1){
      f[1]=f[1]+1;
      f[2]=max(f[1],f[2]);
      f[3]=max(f[2],f[3]+1);
      f[4]=max(f[3],f[4]);
    }
    else{
      f[1]=f[1];
      f[2]=max(f[2]+1,f[1]);
      f[3]=max(f[3],f[2]);
      f[4]=max(f[4]+1,f[3]);
    }
  }
  cout<<f[4]<<'\n';
}
```



---

## 作者：hmh100211 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF933A)

###### 题外话：
###### ~~本蒟蒻基本不会 dp，所以写篇题解巩固下~~

------------

## 题意分析：

题意很简单，给定一个长度为 $ n $ 的序列 $ a $，可以翻转一个区间的数，求翻转后的序列的最长不下降子序列的长度。

这题的数据范围要注意一下:

$$ n \le 2000,1 \le a_i \le 2 $$

$ 1 \le a_i \le 2 $，也就是说 $ a_i $ 只能为 $ 1 $ 或 $ 2 $。

那么很显然，一个位置的最长不下降子序列只有四种情况：

- 以 $ 1 $ 结尾，未翻转。

- 以 $ 2 $ 结尾，未翻转。

- 以 $ 1 $ 结尾，已翻转。

- 以 $ 2 $ 结尾，已翻转。

## 思路：

因为只有四种情况，所以定义一个二维数组 `dp` 来储存，$ dp_{i,j} $ 表示前 $ i $ 个数最长不下降子序列的第 $ j $ 种情况。

那么就可以推出状态转移方程了：

以 $ 1 $ 结尾，未翻转：
$$ dp_{i,0}=dp_{i-1,0}+(a_i=1) $$

以 $ 2 $ 结尾，未翻转：
$$ dp_{i,1}=\max(dp_{i,0},dp_{i-1,1}+(a_i=2)) $$

以 $ 1 $ 结尾，已翻转：
$$ dp_{i,2}=\max(dp_{i,1},dp_{i-1,2}+(a_i=1)) $$

以 $ 2 $ 结尾，已翻转：
$$ dp_{i,3}=\max(dp_{i,2},dp_{i-1,3}+(a_i=2)) $$

题目要求的是翻转后的序列的最长不下降子序列的长度，很显然，以 $ 2 $ 结尾的最长不下降子序列一定比以 $ 1 $ 结尾的最长不下降子序列长，那么最终结果就是 $dp_{n,3}$。

# AC Code：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,a[2222],dp[2222][5];
int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	//上面这段不用管 
	cin>>n; //读入a序列长度 
	for(int i=1;i<=n;i++){
		cin>>a[i]; //读入a序列 
	}
	for(int i=1;i<=n;i++){ //根据方程状态转移 ，注意下标从1开始，避免数组越界 
		dp[i][0]=dp[i-1][0]+(a[i]==1);
		dp[i][1]=max(dp[i][0],dp[i-1][1]+(a[i]==2));
		dp[i][2]=max(dp[i][1],dp[i-1][2]+(a[i]==1));
		dp[i][3]=max(dp[i][2],dp[i-1][3]+(a[i]==2));
	}
	cout<<dp[n][3]; //输出答案 
	return 0;
}
```


# [AC](https://www.luogu.com.cn/record/118547831)

---

