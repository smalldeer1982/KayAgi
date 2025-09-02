# Insertion Sort

## 题目背景

Petya is a beginner programmer. He has already mastered the basics of the C++ language and moved on to learning algorithms. The first algorithm he encountered was insertion sort. Petya has already written the code that implements this algorithm and sorts the given integer zero-indexed array $ a $ of size $ n $ in the non-decreasing order.

```cpp
for (int i = 1; i < n; i = i + 1)
{
    int j = i; 
    while (j > 0 && a[j] < a[j - 1])
    {
        swap(a[j], a[j - 1]); // swap elements a[j] and a[j - 1]
        j = j - 1;
    }
}
```

Petya uses this algorithm only for sorting of arrays that are permutations of numbers from $ 0 $ to $ n-1 $ . He has already chosen the permutation he wants to sort but he first decided to swap some two of its elements. Petya wants to choose these elements in such a way that the number of times the sorting executes function swap, was minimum. Help Petya find out the number of ways in which he can make the swap and fulfill this requirement.

It is guaranteed that it's always possible to swap two elements of the input permutation in such a way that the number of swap function calls decreases.

## 题目描述

Petya is a beginner programmer. He has already mastered the basics of the C++ language and moved on to learning algorithms. The first algorithm he encountered was insertion sort. Petya has already written the code that implements this algorithm and sorts the given integer zero-indexed array $ a $ of size $ n $ in the non-decreasing order.

`for (int i = 1; i < n; i = i + 1)<br></br>{<br></br>   int j = i; <br></br>   while (j > 0 && a[j] < a[j - 1])<br></br>   {<br></br>      swap(a[j], a[j - 1]); // swap elements a[j] and a[j - 1]<br></br>      j = j - 1;<br></br>   }<br></br>}<br></br>`Petya uses this algorithm only for sorting of arrays that are permutations of numbers from $ 0 $ to $ n-1 $ . He has already chosen the permutation he wants to sort but he first decided to swap some two of its elements. Petya wants to choose these elements in such a way that the number of times the sorting executes function swap, was minimum. Help Petya find out the number of ways in which he can make the swap and fulfill this requirement.

It is guaranteed that it's always possible to swap two elements of the input permutation in such a way that the number of swap function calls decreases.

## 说明/提示

In the first sample the appropriate pairs are $ (0,3) $ and $ (0,4) $ .

In the second sample the appropriate pairs are $ (0,4) $ , $ (1,4) $ , $ (2,4) $ and $ (3,4) $ .

## 样例 #1

### 输入

```
5
4 0 3 1 2
```

### 输出

```
3 2
```

## 样例 #2

### 输入

```
5
1 2 3 4 0
```

### 输出

```
3 4
```

# 题解

## 作者：lenlen (赞：14)

### Problem

题目大意：给定一个序列，你可以先交换两个数，问操作过后使冒泡排序最小的交换次数与方案数。

数据范围： $n \leq 5000$。

### Solution

首先我们要明确一点，一个序列的冒泡排序次数最小就是逆序对个数，这个地方不知道的建议去学一下冒泡排序。

其实这个题你看到数据范围，就知道不用想太多了。

首先我们可以处理出来整个序列不交换的逆序对个数 $sum$，然后我们可以预处理两个数组 $f_{i,j},g_{i,j}$。

其中 $f_{i,j}$ 表示第 $i$ 位之前有多少个数大于 $a_j$， $g_{i,j}$ 则表示第 $i$ 位之前有多少个数小于 $a_j$，转移方程就很显然了：

$$f_{i,j}=f_{i-1,j}+[a_j<a_i]$$

$$g_{i,j}=f_{i-1,j}+[a_j>a_i]$$

$[k]$ 表示 $k$ 是否为真，真的话返回 $1$。

然后我们可以枚举交换的两个数 $l,r$，然后可以 $O(1)$ 求出交换 $a_l,a_r$ 之后的逆序对个数。计算方法如下：

$$ans=\max\limits_{l=1}^n \max\limits_{r=l+1}^n (sum+(f_{r,l}-f_{l,l})-(g_{r,l}-g_{l,l})-(f_{r,r}-f_{l,r})+(g_{r,r}-g_{l,r}))$$

计算运用到的方法类似于前缀和的思想，我们拿其中的 $(f_{r,l}-f_{l,l})$ 举个例子， $f_{r,l}$ 表示 $[1,r]$ 中有多少个数大于 $a_l$， $f_{l,l}$ 表示 $[1,l]$ 中有多少个数大于 $a_l$，那么 $(f_{r,l}-f_{l,l})$ 表示 $[l+1,r]$ 中有多少个数大于 $a_l$，可以考虑，其中有多少个数大于 $a_l$ 意味着交换完之后会增加多少对逆序对，所以要加上该值。其他情况同理，自己去推一下。

时间复杂度 $O(n^2)$。

### Code

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5002;//不知道为什么，稍微开大一点就MLE了
int n,a[N],b[N],c[N];
int f[N][N],g[N][N],sum,ans=1e9+7,cnt;
void cdq(int l,int r) //cdq求逆序对，也就是归并求逆序对
{
    if(l==r) return ;
    int mid=l+r>>1;
    cdq(l,mid),cdq(mid+1,r);
    int i,j,num=l-1;
    for(i=mid+1,j=l;i<=r;i++)
    {
        while(b[j]<b[i]&&j<=mid) c[++num]=b[j++];
        sum+=mid-j+1;
        c[++num]=b[i];
    }
    while(j<=mid) c[++num]=b[j++];
    for(int i=l;i<=r;i++) b[i]=c[i];
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),++a[i],b[i]=a[i];
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++) f[j][i]=f[j-1][i]+(a[i]<a[j]),g[j][i]=g[j-1][i]+(a[i]>a[j]);//预处理
    cdq(1,n);
    ans=sum,cnt=1;
    for(int l=1;l<=n;l++)
    for(int r=l+1;r<=n;r++)
    {
        if(ans>sum+(f[r][l]-f[l][l])-(g[r][l]-g[l][l])-(f[r][r]-f[l][r])+(g[r][r]-g[l][r])) 
        {
            ans=sum+(f[r][l]-f[l][l])-(g[r][l]-g[l][l])-(f[r][r]-f[l][r])+(g[r][r]-g[l][r]);
            cnt=1;//记录个数很简单了，遇到相同的就+1，不同的就=1，并且更改值
        }
        else if(ans==sum+(f[r][l]-f[l][l])-(g[r][l]-g[l][l])-(f[r][r]-f[l][r])+(g[r][r]-g[l][r])) ++cnt;
    }
    printf("%d %d\n",ans,cnt);
}
```




---

## 作者：李34 (赞：7)

前面两位大佬用的都是 $O( n^2 \log n)$ 的树状数组解法，所以我想提出一个$ O(n^2) $ 的解法，欢迎指出问题。

首先，冒泡排序（或是英文题面中的插入排序）需要交换的次数就是逆序对的个数。

怎么证明呢？其实很好理解。我们假设所有数都加上了 $1$ ，也就是原数组变成了 $1...n$ 的一个排列。当你交换 $a_i$ 和 $a_{i+1}$ 时，这两个数肯定是一对逆序对。而同时这两个数又是挨在一起的，所以 $1...i-1$ 的所有数往后的逆序对不会改变， $i+2...n$ 往前的逆序对也不会改变，相当于就干掉了一个逆序对。所以每次交换干掉一个逆序对，也就是说逆序对的个数就是要交换的个数。

那么怎么求逆序对呢？对于本题的数据量暴力就行了。

同时我们可以通过递推记录一个 $L$ 数组和 $R$ 数组，其中 $L_{i,j}$ 表示前 $i$ 个数小于 $j$ 的个数， $R_{i,j}$ 表示前 $i$ 个数大于 $j$ 的个数。

递推关系式为：
> $L_{i,j}=L_{i-1,j}+[A_i<j]$  
$M_{i,j}=M_{i-1,j}+[A_i>j]$

其中 $[x]$ 当表达式 $x$ 为真是为 $1$ ，否则为 $0$ 。

记录完了之后我们就暴力枚举所有要交换的 $(i,j)$ 。对于每个 $(i,j)$ ，答案就是  
> $ori$  
$-M_{i-1,A_i}-M_{j-1,A_j}-L_{j-1,A_i}+L_{i,A_i}$  
$+M_{i-1,A_j}+M_{j-1,A_i}+L_{j-1,A_j}-L_{i,A_j}$

其中 $ori$ 表示原数组的逆序对总数。

有点类似于前缀和的思想。

然后我们发现，好像连逆序对都顺便求好了，第 $i$ 个数贡献的逆序对就是 $M_{i-1,A_i}$

然后就完成了。所以这道题其实就直接暴力就行了。

其实树状数组很快，所以 $O( n^2 \log n)$ 的算法不一定比这个慢。

$Code:$

```cpp
#include<cstdio>
const int N=5e3+1;
int n,ori,A[N],L[N][N],M[N][N];
signed main(){
	scanf("%d",&n);
	for (int i=1;i<=n;++i){
		scanf("%d",&A[i]);++A[i];
		for (int j=1;j<=n;++j){
			L[i][j]=L[i-1][j]+(A[i]<j);
			M[i][j]=M[i-1][j]+(A[i]>j);
		}//递推求两个数组。
		ori+=M[i][A[i]];
		//计算逆序对。
	}
	int ans=ori,ansk=0;
	for (int i=1;i<=n;++i){
		for (int j=i+1;j<=n;++j){
			int p=ori-M[i-1][A[i]]-M[j-1][A[j]]-L[j-1][A[i]]+L[i][A[i]]
			         +M[i-1][A[j]]+M[j-1][A[i]]+L[j-1][A[j]]-L[i][A[j]];
			//计算：减掉原来的，加上现在的。
			if (ans>p) ans=p,ansk=1;
			else if (ans==p) ++ansk;
		}
	}
	printf("%d %d",ans,ansk);
	return 0;
}
```

---

## 作者：火羽白日生 (赞：3)

$\texttt{update:}$ 修改了笔误。

由于冒泡排序交换相邻元素的次数就是序列中逆序对的个数，所以原问题可以转化为：

> 有一个长为 $n$ 的序列 $a_{1\dots n}$，可以进行一次操作来交换序列中的两个数 $a_i,a_j$，求操作后序列逆序对的个数的最小数及其方案数。

设 $f_{i,j}$ 为 $j\sim n$ 中小于 $a_i$ 的数的个数，$g_{i,j}$ 为 $1\sim j-1$ 中大于 $a_i$ 的数的个数，$org$ 为原序列中逆序对个数。

用树状数组维护一个桶，那么这些东西都可以用树状数组预处理出来。

为了让逆序对个数更少，我们默认交换的数 $a_i,a_j$ 满足 $i<j$ 并且 $a_i>a_j$。

那么有：

$$ans=org-f_{j,j}+f_{j,i}-g_{j,j}+g_{j,i}-f_{i,i}+f_{i,j}-g_{i,i}+g_{i,j}+1$$

然后直接更新答案就行了。

$\texttt{Code:}$

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define rint register int
using namespace std;
namespace IO{
	#define File(x,y) freopen(#x,"r",stdin),freopen(#y,"w",stdout);
	inline int read(){
		int w=0,f=1; char ch=getchar();
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
		while(ch>='0'&&ch<='9'){w=(w<<3)+(w<<1)+(ch^48); ch=getchar();}
		return w*f;
	}
	inline void write(int x){
  		static int sta[35]; int top=0;
  		do{sta[++top]=x%10,x/=10;}while(x);
  		while(top) putchar(sta[top--]+48); puts("");
	}
}
using namespace IO;
namespace CL{
	#define fill(x,y) memset(x,y,sizeof(x))
	#define copy(x,y) memcpy(y,x,sizeof(x))
	
	const int maxn=5e3+5;
	
	int n,org,ans=0x3f3f3f3f,cnt;
	int a[maxn],b[maxn],f[maxn][maxn],g[maxn][maxn];
	namespace BIT{
		#define lowbit(x) x&-x
		int c[maxn];
		inline void init(){fill(c,0);}
		inline void add(int x){
			while(x<=n){c[x]++; x+=lowbit(x);}
		}
		inline int query(int x){
			int res=0;
			while(x){res+=c[x]; x-=lowbit(x);}
			return res;
		}
	}using namespace BIT;
	
	inline int main(){
		n=read();
		for(int i=1;i<=n;i++) a[i]=read()+1;
		for(int i=n;i>=1;i--) org+=query(a[i]),add(a[i]);
		for(int i=1;i<=n;i++){
			init();
			for(int j=n;j>=1;j--) f[i][j]=query(a[i]),add(a[j]);
			for(int j=i-1;j>=1;j--) f[i][j]--;
		}//a[i+1~n] < a[i]
		for(int i=1;i<=n;i++) b[i]=n-a[i]+1;
		for(int i=1;i<=n;i++){
			init();
			for(int j=1;j<=n;j++) g[i][j]=query(b[i]),add(b[j]);
			for(int j=i+1;j<=n;j++) g[i][j]--;
		}//a[1~i-1] > a[i]
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++){
				if(a[i]<a[j]) continue;
				int tmp=org-f[j][j]+f[j][i]-g[j][j]+g[j][i]-f[i][i]+f[i][j]-g[i][i]+g[i][j]+1;
				if(tmp<ans) ans=tmp,cnt=1;
				else if(tmp==ans) cnt++;
			}
		printf("%d %d\n",ans,cnt);
		return 0;
	}
}
signed main(){return CL::main();}
```

---

## 作者：Lagerent (赞：2)

[题面。](https://codeforces.com/problemset/problem/362/C)

冒泡排序需要交换次数即为区间逆序对个数。

发现数据范围允许 $O(n ^ 2)$ 做法，于是自然的想法是枚举交换位置 $a_l, a_r$ 考虑对原来答案的影响。瓶颈在于如何 $O(1)$ 计算影响。

考虑我们交换完 $a_l, a_r$ 后，
- 原来在区间 $[l, r]$ 内比 $a_l$ 大的数与 $a_l$ 没有组成逆序对，但交换过后会形成新的逆序对；
- 原来在区间 $[l, r]$ 内比 $a_l$ 小的数与 $a_l$ 组成了逆序对，但交换过后不再是；
- 原来在区间 $[l, r]$ 内比 $a_r$ 小的数与 $a_r$ 没有组成逆序对，但交换过后会形成新的逆序对；
- 原来在区间 $[l, r]$ 内比 $a_r$ 大的数与 $a_r$ 组成了逆序对，但交换过后不再是。

所以我们只需要算这四个地方。发现可以通过前缀和预处理出来。

那这个题就做完了。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define gc getchar
#define rep(a, b, c) for(int (a) = (b); (a) <= (c); ++ (a))
#define per(a, b, c) for(int (a) = (b); (a) >= (c); -- (a))
using namespace std;

inline int rd() {
	int x = 0, f = 1; char ch = gc();
	while(ch < '0' || ch > '9') {if(ch == '-') f = -1; ch = gc();}
	while(ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gc();
	return x * f;
}

const int N = 5010;

int n, a[N], s;
int f[N][N], g[N][N];
/*
f[i][j] 表示 [1, i] 中比 a[j] 小的数的个数。 
*/

int main() {
	n = rd(); 
	rep(i, 1, n) a[i] = rd();
	rep(i, 1, n) {
		rep(j, 1, n) {
			if(i < j && a[i] > a[j]) ++ s;
			f[j][i] = f[j - 1][i] + (a[j] < a[i]);
			g[j][i] = g[j - 1][i] + (a[j] > a[i]);
		}
	}
	int res = s, cnt = 0;
	rep(l, 1, n - 1) {
		rep(r, l + 1, n) {
			int t = s + (g[r][l] - g[l][l]) - (f[r][l] - f[l][l]) + (f[r][r] - f[l][r]) - (g[r][r] - g[l][r]);
			if(t < res) {
				res = t;
				cnt = 1;
			}
			else if(t == res) ++ cnt;
		}
	}
	printf("%d %d\n", res, cnt);
	return 0;
}
/*
+ [l, r] 中比 al 大的数
- [l, r] 中比 al 小的数
+ [l, r] 中比 ar 小的数
- [l, r] 中比 ar 大的数 
*/
```

---

## 作者：haoguhao (赞：1)

## 前言
问题本质上也就是：
>交换两个数，问减少最多逆序对数后还有几个逆序对。

只是考试的时候考了一个：

> 给定⼀个⻓为 $n$ 的排列，可以进⾏下⾯的操作⾄多⼀次；交换两个数的位置。问最多能使排列的逆序对数减少多少。

数据范围是 $O(n \log n)$，~~所以我相信本题应该是有 $O(n \log n)$ 做法的~~，但是被我瞎搞只搞出来第一个答案，第二个答案搞出不来，都快来集思广益。
## 做法
当时在考场时是打了一个 $O(n^2)$ 的做法的，在这里也非常适用，先统计出原序列的逆序对数 $cnt$，然后我们定义一个 $b_{i,j}$ 表示把 $i$ 换到 $j$ 时所减少的逆序对个数，互相交换后减少的逆序对个数就是 $b[i][j]-b[j][i]$ 了，用 $ans$ 记录最小值，但 $ans$ 必须减去 $1$，因为交换 $i,j$ 时算了两次，得剪掉一次，也所以答案就是 $cnt-(ans-1)$，方案数直接统记即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
template<class T>//快读 
inline void read(T &n){
	n=0;
	bool f=0;
	char c=getchar();
	while(c<'0' || c>'9') {if(c=='-') f=1;c=getchar();}
	while(c>='0' && c<='9') n=(n<<1)+(n<<3)+(c^48),c=getchar();
	if(f) n=-n;
}
int n,ans,cnt;
const int MAXN=	5005;
int a[MAXN],b[MAXN][MAXN];
int main(){
	read(n);
	for(register int i=1;i<=n;i++) read(a[i]);
	//i过去产生的贡献 
	for(register int i=1;i<=n;i++){
		int d=0;//记录当前有多少个逆序对 
		for(register int j=i+1;j<=n;j++){
			if(a[i]>a[j]) d++/*如果是逆序对，交换后肯定会减少逆序对*/,cnt++;//cnt统计总共的逆序对 
			else if(a[i]<a[j]) d--;//如果不是逆序对，交换后肯定会增加逆序对 
			b[i][j]=d;//记录i和j换产生的贡献 
		} 
	} 
	//j过来产生的贡献 
	for(register int i=n;i>=1;i--){
		int d=0;
		for(register int j=i-1;j>=1;j--){
			if(a[i]>a[j]) d++;/*如果不是逆序对，交换后肯定会增加逆序对*/
			else if(a[i]<a[j]) d--;	/*如果是逆序对，交换后肯定会减少逆序对*/				
			b[i][j]=d; //记录j换过去产生的贡献 
		} 
	} 	
	for(register int i=1;i<=n;i++){
		for(register int j=i+1;j<=n;j++){
			ans=max(b[i][j]-b[j][i],ans);//统计答案 
		}
	}
	int res=0;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(b[i][j]-b[j][i]==ans) res++;//统计答案 
		}
	}
	cout<<cnt-ans+1<<' '<<res;//输出 
}
```
## 瞎搞
只有第一个答案是对的，统计方案数想不出来。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
#define gc getchar
inline int rd() {
	int x = 0, fg = 1;
	char ch = gc();
	while (ch < '0' || ch > '9') { if (ch == '-') fg = -1; ch = gc();}
	while (ch >= '0' && ch <= '9') {x = (x << 1) + (x << 3) + ch - '0';ch = gc();}
	return x * fg;
}
int n;
int a[N], p[N];
int sl[N], tl, sr[N], tr, t[N] ,tong[10000008], b[N];
int ans;
int L, R, cnt, cn;
void merge_sort(int a[],int l,int r){
	if(l==r) return ;
	int mid=(l+r)/2;
	merge_sort(a,l,mid);merge_sort(a,1+mid,r);
	for(int i=l,j=l,k=mid+1;i<=r;i++){
		if(j==mid+1) t[i]=a[k++];
		else if(k==r+1){
			t[i]=a[j++];
			cn+=k-mid-1;
		} 
		else {
			if(a[j]<=a[k]){
				t[i]=a[j++];
				cn+=k-mid-1;
			} 
			else t[i]=a[k++];
		}
	}
	for(int i=l;i<=r;i++) a[i]=t[i];
}
inline void mvL(int x, int o) {
	for (int i = sl[x]; i < sl[x+1]; i++) {
		if (a[i] < a[sl[x]]) cnt -= o;
		if (a[i] > a[sr[R]]) cnt -= o;
	}
	for (int i = a[sl[x]]; i < a[sl[x+1]]; i++) {
		if (p[i] >= sl[x+1] && p[i] <= sr[R]) cnt += o;
	}
	L += o;
}
inline void mvR(int x, int o) {
	for (int i = sr[x]; i > sr[x-1]; i--) {
		if (a[i] < a[sl[L]]) cnt -= o;
		if (a[i] > a[sr[x]]) cnt -= o;
	}
	for (int i = a[sr[x]]; i > a[sr[x-1]]; i--) {
		if (p[i] >= sl[L] && p[i] <= sr[x-1]) cnt += o;
	}
	R -= o;
}
void solve(int ql, int qr, int l, int r) {
	int mid = (ql + qr) >> 1;
	while (L > l) mvL(L - 1, -1);
	while (R < mid) mvR(R + 1, -1);
	while (L < l) mvL(L, 1);
	while (R > mid) mvR(R, 1);
	int p = l, res = -1e9;
	for (int i = l; i <= r && sl[i] <= sr[mid]; i++) {
		while (L < i) mvL(L, 1);
		int val = 2 * (cnt + sl[L] - sr[R]) - 1;
		if (res < val) res = val, p = i;
		ans = max(ans, val);
		if(val==ans) tong[ans]++,ans=val; 
	}
	if (ql < mid) solve(ql, mid - 1, l, p);
	if (qr > mid) solve(mid + 1, qr, p, r);
}
signed main(){
	n = rd();
	for (int i = 1; i <= n; i++ ) a[i] = rd(), b[i] = a[i], p[a[i]] = i;
	merge_sort(b,1,n);
	for (int i = 1; i <= n; i++) {
		while (tr && a[sr[tr]] > a[i]) tr--;
		sr[++tr] = i;
	}
	for (int i = n; i >= 1; i--) {
		while (tl && a[sl[tl]] < a[i]) tl--;
		sl[++tl] = i;
	}
	reverse(sl + 1, sl + 1 + tl);
	L = 1, R = tr;
	for (int i = sl[L]; i <= sr[R]; i++) {
		if (a[i] > a[sr[R]]) cnt++;
		if (a[i] < a[sl[L]]) cnt++;
	}
	solve(1, tr, 1, tl);
	printf("%d %d",cn-ans,tong[ans]);
	return 0;
}

```
## 后记
其实评绿还是有点太高了，这可是我们比赛的第一题，我们考题还要再这题的基础上甚至还要扫描线优化，那不得紫题。

---

## 作者：LlLlCc (赞：1)

## 题目翻译：
给出一个长度为$N$的无序序列，序列为$0$到$N-1$的排列，现在需要你用冒泡排序来将序列排成从小到大有序的序列

你可以执行一次交换两个元素$i,j(i\neq j,1\le i\leq n)$，使得执行冒泡排序时，交换相邻元素的次数最少

要你求出交换相邻元素的最少次数和满足交换相邻元素的次数最少的方案数

结合样例就明白了

## 题解
如果了解冒泡排序的性质就会知道，冒泡排序交换相邻元素的次数就是序列中逆序对的个数

所以问题就转化成了交换两个元素使得序列中逆序对总数最少

不妨设两个数组：

$\large f_{i,j}:$ 第$j$个数后面，有几个数小于第$i$个数

$\large Num_{i,j}:$ 第$i$个数前面，有几个数大于第$j$个数

这两个数组都可以用树状数组提前预处理

然后我们枚举交换的两个元素$i,j$，我们考虑交换后总逆序对数的变化

- 对于第$i$个元素，总数$-f_{i,i}+f_{i,j}-Num{i,i}+Num{i,j}$

- 对于第$j$个元素，总数$-f_{j,j}+f_{j,i}-Num{j,j}+Num{j,i}$

因为如果$a_i>a_j$，那么这样会重复减，所以要再补上$1$

## code
```
#include<bits/stdc++.h>
#define maxn 5005
using namespace std;
int n,a[maxn],f[maxn][maxn],Num[maxn][maxn],Ans,c[maxn],Now,tot,Cnt,b[maxn];
inline int read(){
	int ret=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
	return ret;
}
inline void Change(int x){for (;x<=n;x+=x&-x) c[x]++;}
inline int Get(int x){int sum=0;for (;x;x-=x&-x) sum+=c[x];return sum;}
int main(){
	n=read();
	for (int i=1;i<=n;i++) a[i]=read()+1;
	for (int i=n;i;i--) Ans+=Get(a[i]),Change(a[i]);
	for (int i=1;i<=n;i++){
		memset(c,0,sizeof c);
		for (int j=n;j;j--) f[i][j]=Get(a[i]),Change(a[j]);
	    for (int j=i-1;j;j--) f[i][j]--;
	}
	for (int i=1;i<=n;i++) b[i]=n+1-a[i];
	for (int i=1;i<=n;i++){
		memset(c,0,sizeof c);
		for (int j=1;j<=n;j++) Num[i][j]=Get(b[i]),Change(b[j]);
	    for (int j=i+1;j<=n;j++) Num[i][j]--;
	}
	Cnt=Ans;
	for (int i=1;i<=n;i++)
	for (int j=i+1;j<=n;j++){
		Now=Cnt-f[i][i]+f[i][j]-f[j][j]+f[j][i]-Num[j][j]+Num[j][i]-Num[i][i]+Num[i][j];
		if (a[i]>a[j]) Now++;
		if (Now==Ans) tot++;
		if (Now<Ans) Ans=Now,tot=1;
	}
	printf("%d %d",Ans,tot);
	return 0;
}
```


---

## 作者：Penguin_Chen (赞：0)

### 题目大意

给定一个长度为 $n$ 的排列 $A$，问交换两数的位置，最多能使逆序对的数量减少多少，以及相对应的方案数（这是模拟赛的弱化版诶）

### 思路

#### 100 pts（$n^2$）~~模拟赛只有 50 pts~~

首先，开两个二维数组， $f1[i][j]$ 表示 $i$ 与 $j$ 互换位置时对于 $i$ 减少的逆序对数量（也可以是增加），$f2[i][j]$ 与 $f1[i][j]$ 同理，不过是对于 $j$ 来说的。

接下来考虑转移，对于 $f1[i][j]$，如果 $a[i]>a[j]$（$i<j$），那么 $f1[i][j]=f1[i][j-1]+1$，否则，$f1[i][j]=f1[i][j-1]-1$。

$f2$ 同理，如果 $a[i]>a[j]$，那么 $f2[i][j]=f2[i+1][j]+1$，否则，$f2[i][j]=f1[i+1][j]-1$（这里的遍历顺序是从大到小，可以自己思考一下为什么）。

~~不要用 `#define int long long`，会 MLE。~~
##### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e3+1;
int n,ans,ans_num,cnt;
int a[maxn];
int f1[maxn][maxn];//i减少的逆序对 
int f2[maxn][maxn];//j减少的逆序对 
int main()
{
	//freopen("2457.in","r",stdin);
	//freopen("2457.out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;++i)cin>>a[i];
	for(int i=1;i<=n;++i)
		for(int j=i+1;j<=n;++j)
			if(a[i]>a[j])++cnt;//总的逆序对数量
		
	for(int i=1;i<=n;++i)//前面有解释
		for(int j=i+1;j<=n;++j)
		{
			if(a[i]>a[j])
				f1[i][j]=f1[i][j-1]+1;
			else
				f1[i][j]=f1[i][j-1]-1;
		}
	for(int i=n;i>=1;--i)//同上
		for(int j=i+1;j<=n;++j)
		{
			if(a[i]>a[j])
				f2[i][j]=f2[i+1][j]+1;
			else
				f2[i][j]=f2[i+1][j]-1;
		}
	
	for(int i=1;i<=n;++i)//寻找最大值
		for(int j=i+1;j<=n;++j)
			ans=max(ans,f1[i][j]+f2[i][j]);
	for(int i=1;i<=n;++i)//统计方案数
		for(int j=i+1;j<=n;++j)
			if(f1[i][j]+f2[i][j]==ans)++ans_num;
	
	cout<<cnt-(ans-1)<<' '<<ans_num<<endl;
	return  0;
}
```

---

## 作者：NaN_HQJ2007_NaN (赞：0)

不难的一道题，有些大佬想复杂了。

显然，交换的次数等于逆序对的个数，我们要找到有多少种交换方法使得交换后的逆序对个数最小。

观察到 $n\le5000$，考虑直接暴力。

定义 $b_{i,j}$ 为交换 $i,j$ 两个元素后逆序对的变化量。

然后发现这和下标在 $[i,j]$ 中的数与 $a_i,a_j$ 的大小关系有关。

对于与 $a_i$ 相关的，正向循环计算；对于与 $a_j$ 相关的，反向循环计算。

复杂度 $O(n^2)$。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5000+5;
int n,b[N][N],a[N],cnt,d,d2;
int main(){
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
  cin>>n;
  for(int i=1;i<=n;++i)cin>>a[i];
  for(int i=1;i<=n;++i){
    d=0,d2=0;
    for(int j=i+1;j<=n;++j){
      if(a[j]<a[i])++d,++cnt;
      else ++d2;
      b[i][j]-=d;b[i][j+1]+=d2;
    }
    d=d2=0;
    for(int j=i-1;j>=1;--j){
      if(a[j]<a[i])++d;
      else ++d2;
      b[j][i]+=d;b[j-1][i]-=d2;
    }
  }
  int minn=1e9,c=0;
  for(int i=1;i<=n;++i)for(int j=i+1;j<=n;++j)minn=min(minn,b[i][j]);
  for(int i=1;i<=n;++i)for(int j=i+1;j<=n;++j)if(b[i][j]==minn)++c;
  cout<<cnt+minn<<" "<<c<<endl;
  return 0;
}

```


---

## 作者：BigJoker (赞：0)

线性 DP

设 $f_{i.j}$ 表示前 $i$ 个数有多少个数小于 $j$，$g_{i,j}$ 表示前 $i$ 个数有多少个数大于 $j$

这个很好 dp，前缀和就好了。

$f_{i,j}=f_{i-1,j}+[a_i<j]$

$g$ 同理。

设 $sf(l,r,i)=f_{r,i}-f_{l-1,i}$ 表示区间 $[l,r]$ 中有多少个数小于 $j$

设 $sg(l,r,i)=g_{r,i}-g_{l-1,i}$ 表示区间 $[l,r]$ 中有多少个数大于 $j$

然后考虑 $\Theta(n^2)$ 枚举交换的两个点 $l,r$，$\Theta(1)$ 查询逆序对数量，假设为修改前的逆序对数量为 $s$，假设增量为 $\Delta$，注意可能为负数。将 $l,r$ 交换后，$[l,r]$ 内原本小于 $a_l$ 的数现在移动到了 $l$ 的右侧，就要减去，原本大于 $a_l$ 就要加上；$r$ 同理

那么 $\Delta=sg(l,r,a_l)-sf(l,r,a_l)-sg(l,r,a_r)+sf(l,r,a_r)$，然后将答案和 $s+\Delta$ 取最小值即可。

---

