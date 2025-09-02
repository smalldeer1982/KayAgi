# DZY Loves Modification

## 题目描述

As we know, DZY loves playing games. One day DZY decided to play with a $ n×m $ matrix. To be more precise, he decided to modify the matrix with exactly $ k $ operations.

Each modification is one of the following:

1. Pick some row of the matrix and decrease each element of the row by $ p $ . This operation brings to DZY the value of pleasure equal to the sum of elements of the row before the decreasing.
2. Pick some column of the matrix and decrease each element of the column by $ p $ . This operation brings to DZY the value of pleasure equal to the sum of elements of the column before the decreasing.

DZY wants to know: what is the largest total value of pleasure he could get after performing exactly $ k $ modifications? Please, help him to calculate this value.

## 说明/提示

For the first sample test, we can modify: column 2, row 2. After that the matrix becomes:

`<br></br>1 1<br></br>0 0<br></br><br></br>`For the second sample test, we can modify: column 2, row 2, row 1, column 1, column 2. After that the matrix becomes:

`<br></br>-3 -3<br></br>-2 -2<br></br><br></br>`

## 样例 #1

### 输入

```
2 2 2 2
1 3
2 4
```

### 输出

```
11
```

## 样例 #2

### 输入

```
2 2 5 2
1 3
2 4
```

### 输出

```
11
```

# 题解

## 作者：交警 (赞：15)

# $Code$ $Forces$ $CF446B$
### $NanyaOIer : y2j$
#### $2019.10.31$ 
### $Time$ $Limit$ $:$ $2.00s$  
### $Memory$ $Limit$ $:$ $256MB$
魔改警告！！！
## $Background$
### 丛哥喜欢花
## ❀ ❀ ❀ ❀ ❀ ❀ ❀ ❀ ❀ ❀ 
## $Description$
丛哥家的后花园有一个花阵（$n * m$）。有一天，由于丛哥的家住在热带地区，热带气旋现象普遍发生，台风出现的次数很频繁，丛哥家的后花园经常刮台风。这个台风一共会刮 $k$ 次，它每刮一次台风都只能吹落一行或者一列上的花的 $p$ 片花瓣，而每次刮风，台风获得的分数为刮风之前一行或者一列上的花瓣的数量。 每刮一次台风，丛哥都会特别高兴，所以每次刮台风的时候丛哥获得的喜悦值与台风获得的分数相等。求丛哥能够获得的最大喜悦值。
## $Simplified$ $Description$
给一个 $n * m$ 大小的矩阵，共 $k$ 次操作，每次操作可以将一行或者一列减少 $p$，得到的分数为修改之前一行或者一列的元素和，求分数的最大值。
## $Input$
第一行包含四个整数 $n,$ $m,$ $k,$ $p$ ，含义在题意中已经给定。  
接下来 $n$ 行，每行 $m$ 个整数，表示这个矩阵。
## $Output$
一行一个整数，表示最大分数（最大喜悦值）。
## $Sample$ $Input1$
```
2 2 2 2
1 3
2 4
```
## $Sample$ $Output1$
```
11
```
## $Sample1$ $Explaination$
1.对于第二行进行操作，分数：$2 + 4 = 6$  
```1 3```  
```0 2```  
2.对于第二列进行操作，分数：$2 + 3 = 5$

得到的总分数：$6 + 5 = 11$
## $Sample$ $Input2$
```
2 2 5 2
1 3
2 4
```
## $Sample$ $Output2$
```
11
```
## $Sample2$ $Explainaion$
1.对于第二列进行操作，分数：$3 + 4 = 7$  
```1 1```  
```2 2```  
2.对于第二行进行操作，分数：$2 + 2 = 4$  
```1 1```  
```0 0```  
3.对于第一行进行操作，分数：$1 + 1 = 2$  
```-1 -1```  
```0 0```  
4.对于第一列进行操作，分数：$0 + (-1) = -1$  
```-3 -1```  
```-2 0```  
5.对于第二列进行操作，分数：$0 + (-1) = -1$  
```-3 -3```  
```-2 -2```  
## $Data$ $Constraint$
$1 ≤ n, m ≤ 10^3$ $,$ $1 ≤ k ≤ 10^6$ $,$ $1 ≤ p ≤ 100$
## $Tips$
！！！丛哥家的花很厉害，花瓣数量可以为负  
至于为什么刮一次台风丛哥的喜悦值会增加，因为在刮完所有的台风以后，他又可以**?种?新?花?**了  
建议使用 $long$ $long$ 型，以防爆 $int$ 。
## $Solution$
---
> **性质一：答案只跟处理的对象有关，与顺序无关。**  

#### 证明（强烈建议洛谷优化markdown，我的图表显示有问题，所以才换了截图）
首先，如果两者都是对于不同一列或者一行操作，并没有相交的元素，每次操作互不影响，不方便证明，此处使用在两次操作下分别对于某一行和某一列进行操作。  
![1.png](https://i.loli.net/2019/10/31/aFdyVgjQI74AeoR.png)

在这个矩阵下，我们对于最后一行和最后一列进行处理。
#### 先处理最后一行，再处理最后一列。
##### 最后一行的处理：
![2.png](https://i.loli.net/2019/10/31/syVPjgpKn6B19fN.png)  
$Score1 = a[n][1] + a[n][2] + ... + a[n][m-1] + a[n][m];$
#####  最后一列的处理： 
![3.png](https://i.loli.net/2019/10/31/14FJYDKOkdLhe87.png)  
$Score1 = a[n][1] + a[n][2] + ... + a[n][m-1] + a[n][m] +$ $(a[1][m] + a[2][m] + ... + a[n-1][m] + a[n][m] - k);$（**加括号的为新增部分**）

####  先处理最后一列，再处理最后一行 

#####  最后一列的处理：  

![4.png](https://i.loli.net/2019/10/31/Ey8nTeQDBGbk7j3.png)  
$Score2 = a[1][m] + a[2][m] + ... + a[n-1][m] + a[n][m];$

#####  最后一行的处理： 

![5.png](https://i.loli.net/2019/10/31/CSnf6xZPADiVJGk.png)  

$Score2 = a[1][m] + a[2][m] + ... + a[n-1][m] + a[n][m] + ( a[n][1] + a[n][2] + ... + a[n][m-1] + a[n][m] - k );$（**加括号的为新增部分**）  
**因为$Score1 = Score2$**  
**所以，顺序的改变对于分数和处理后的状态是不产生影响的。** 

####  证毕 

---

>   **性质二：对于和最大的每一行或者每一列进行操作，所得分数最大**  

####  证明： 

 **无需证明** 

####  证毕 

---

>  **性质三：每次查询的答案应该减去横向处理的操作次数 $i$ 和纵向处理的操作次数 $k-i$的乘积与 $p$ 的乘积 （ 减去$i * ( k - i ) * p$ ）**  

####  证明： 

 **在横向处理完成后，每一次纵向的操作都会与横向处理的操作相交，相应的应该减去相交的次数乘以 $p$ 。这一点我们在程序中方便体现。**   

####  证毕 

---

####   在讲述完以上性质之后，我们可以开始讲这道题的思路  
假设总共 $k$ 次的操作全部都为横向操作，那么肯定要使用贪心的思想，每次都操作当前状态下和最大的一行，用一个一位数组存下每一步的分数。  
再假设总共 $k$ 次的操作全部都为纵向操作，那么每次都操作当前状态下和最大的一列，同样用另一个一位数组存下每一步的分数。  
最后再进行查询，因为总共是 $k$ 次操作，所以只用看成 $i$ 次横向操作和 $k-i$ 次纵向操作即可。  
不过查询的时候要注意：横向与纵向操作会有相交的部分，每相交一次就减去 $p$ ，总共减去 $( k - i ) * i * p$ 即为答案。  
预处理复杂度 $O ( n * m )$ ，查询复杂度为 $O ( k )$，可以顺利通过此题。

## $std$
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e3 + 5;

inline long long read() {
	register long long f = 1, sum = 0;  register char ch = getchar();
	while ( !isdigit(ch) ) { if ( ch == '-' ) f = -1; ch = getchar(); }
	while ( isdigit(ch) ) { sum = (sum<<1) + (sum<<3) + (ch^48); ch = getchar(); }
	return f * sum;
}

long long n, m, k, p, ans;
long long a[N][N];
long long row[N*N], column[N*N];

priority_queue < long long > row_q, column_q;  //性质二：用优先队列来维护

signed main() {
	n = read(), m = read(), k = read(), p = read();
	for ( register int i = 1 ; i <= n ; i ++ )
		for ( register int j = 1 ; j <= m ; j ++ )
			a[i][j] = read();
	/*<-------------------↓以下为预处理（体现性质一）↓------------------->*/
	for ( register int i = 1 ; i <= n ; i ++ ) { 
		register long long add = 0;
		for ( register int j = 1 ; j <= m ; j ++ ) {
			add += a[i][j];
		} row_q.push ( add );  //把每一行的和加入行的优先队列(row_q)
	} for ( register int i = 1 ; i <= m ; i ++ ) {
		register long long add = 0;
		for ( register int j = 1 ; j <= n ; j ++ ) {
			add += a[j][i];
		} column_q.push ( add );  //把每一列的和加入列的优先队列(column_q)
	} for ( register int i = 1 ; i <= k ; i ++ ) {  //每次处理和最大的行，并且将处理过后的行加入行的优先队列(row_q)
		register long long xx = row_q.top();
		row_q.pop();
		row[i] = row[i-1] + xx;
		xx -= m * p;
		row_q.push ( xx );
	} for ( register int i = 1 ; i <= k ; i ++ ) {  //每次处理和最大的列，并且将处理过后的列加入列的优先队列(column_q)
		register long long xx = column_q.top();
		column_q.pop();
		column[i] = column[i-1] + xx;
		xx -= n * p;
		column_q.push ( xx );
	}
	/*<-------------------↑以上为预处理（体现性质一）↑------------------->*/
	for ( register int i = 0 ; i <= k ; i ++ )
		ans = max ( ans, column[k-i] + row[i] - i * ( k - i ) * p );
		//每次更新答案时应减去 i * ( k - i ) * p   （体现性质三）
	printf ( "%lld\n", ans );
	return 0;
}

```
#  $End$ 
# ❀ ❀ ❀ ❀ ❀ ❀ ❀ ❀ ❀ ❀

---

## 作者：fuqingchen (赞：7)

# 原题链接


[CF446B DZY Loves Modification](https://www.luogu.com.cn/problem/CF446B)

# 题目简述

给出一个 $n \times m$ 的矩阵，并进行 $k$ 次操作，每次操作将矩阵的一行或一列的所有元素的值减 $p$，得到的分数为这次修改之前这一列或一行的元素和，求分数最大值。

# 解题思路

首先发现一个性质：最终答案与减的顺序无关，于是我们就可以将每一行的和与每一列的和分别存在两个堆里，然后不断将最大一行的和取出并减 $k$ 加入堆中，重复此操作，在中间记录减 $i$ 次的答案，最后枚举要减几次，取最大值就是答案。

# 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, m, k, p, res = -1e18, t1[1000010], t2[1000010], a[1010][1010], sum;
priority_queue<int> line;//存每一行的和，方便logn求出最大值
priority_queue<int> col;//存列的和
signed main() {
	scanf("%lld%lld%lld%lld", &n, &m, &k, &p);
	for (int i = 1; i <= n; ++i) {
		sum = 0;
		for (int j = 1; j <= m; ++j) {
			scanf("%lld", &a[i][j]);
			sum += a[i][j];
		}
		line.push(sum);
	}
	for (int j = 1; j <= m; ++j) {
		sum = 0;
		for (int i = 1; i <= n; ++i) sum += a[i][j];
		col.push(sum);
	}
	for (int i = 1; i <= k; ++i) {
		int u = line.top();
		line.pop();
		t1[i] = t1[i - 1] + u;
		line.push(u - m * p);
	}
	for (int i = 1; i <= k; ++i) {
		int u = col.top();
		col.pop();
		t2[i] = t2[i - 1] + u;
		col.push(u - n * p);
	}
	for (int i = 0; i <= k; ++i) res = max(res, (t1[i] + t2[k - i] - (k - i) * i * p));//枚举要删几次
	printf("%lld", res);
	return 0;
}
```

---

## 作者：Demoe (赞：5)

[$\large\text{题目传送门}$](https://www.luogu.com.cn/problem/CF446B)

## $\text{Description}$

- 给定一个 $n\times m$ 的矩阵，进行 $k$ 次操作，每次操作可任选一行或一列，对答案加上当前这行/列的权值和，接着对当前这行/列每个元素减去 $p$。
- 问答案最大值。

## $\text{Solution}$

一开始有个很简单的贪心想法，就是每次取行列中总和最大的那个。

然后你冲了一发，发现你挂了。

[WA on #4](https://www.luogu.com.cn/record/58893982)。

然后其实你发现行列是对互相有后效影响的。

比如当你最大值又有行又有列，你是选哪个呢？

那么考虑到行或者列自己是不影响的。

那么考虑行列分开贪心，贪心策略同上。

令 $l_i$ 为行选了 $i$ 个最大答案，$r_i$ 为列。

显然有 $ans=\max_{i=0}^k\{l_i+r_i-i\times(k-i)\times p\}$，这时你把行列拆开就可以直接算出行列之间相互影响，保证了贪心的正确性。

记得开 long long。

贪心随便拿个东西存一下就行了，我整了个 multiset，时间复杂度 $O(k\log\max(n,m))$。

## $\text{Code}$

```cpp
const int N=1e3+5,K=1e6+5;
int n,m,k,p,a[N][N],l[K],r[K],sl[N],sr[N],ans=-1e18;
multiset<int> L,R;
#define IT multiset<int>::iterator

// ----------  ---------- //

signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	rd(n);rd(m);rd(k);rd(p);
	for(re i=1;i<=n;++i)
		for(re j=1;j<=m;++j) rd(a[i][j]),sl[i]+=a[i][j],sr[j]+=a[i][j];
	for(re i=1;i<=n;++i) L.insert(sl[i]);
	for(re i=1;i<=m;++i) R.insert(sr[i]);
	for(re i=1;i<=k;++i){
		IT it=L.end();--it;int res=*it;l[i]=l[i-1]+res;L.erase(it);L.insert(res-p*m);
		it=R.end();--it;res=*it;r[i]=r[i-1]+res;R.erase(it);R.insert(res-p*n);
	}
	for(re i=0;i<=k;++i) ans=max(ans,l[i]+r[k-i]-i*(k-i)*p);
	wr(ans);puts("");
	return 0;
}

// ---------- Main ---------- //
```

---

## 作者：xiaozeyu (赞：5)

**怎么都在写优先队列啊，我来换种写法**



------------

**题意**

现在你的面前有一人 N*M 的矩阵，你需要进行恰好 K 次操作。每次操作你可以选择其中一行或者其中一列，将其中的元素全部累加到 ans 里去。然后把选中的这些数全部减去 P。

问 ans 最大是多少。

【输入格式】

第一行一共四个数，分别为 N,M，K,P。

接下来给出一个 N 行 M 列的矩阵 Ai,j。

【输出格式】

一个整数表示 ansmax。



------------

我第一眼的反应这直接Dp出得了答案啊

**用前缀和求出每一行，每一列的总和**

因为一次取一行/列，所以只要处理前缀和

每次取最大的行/列

这时我们会面临一个问题，该取最大行还是最大列

如果最大行与最大列一样怎么办？

是不是该比较次大行与次大列？

如果还相同(⊙o⊙)?

陷入了沉思

模拟了几下

**发现：结果与顺序是无关的**

写了一下代码：

```cpp
	sort(sumi+1,sumi+n+1);
	sort(sumj+1,sumj+m+1);
	For(i,1,k)
	{
		dp[1][i]=dp[1][i-1]+sumi[n];
		sumi[n]=sumi[n]-m*p;
		x=n;
		while(sumi[x]<sumi[x-1]&&x-1>0)
		{
			swap(sumi[x],sumi[x-1]);
			x--;
		}
	}
	For(j,1,k)
	{
		dp[0][j]=dp[0][j-1]+sumj[m];
		sumj[m]=sumj[m]-n*p;
		x=m;
		while(sumj[x]<sumj[x-1]&&x-1>0)
		{
			swap(sumj[x],sumj[x-1]);
			x--;
		}
	}
```

分别对行的与列的预处理

先进行排序

每次取走最大的，减去每次的损耗，再放回去排序

得到了DP式

$DP_{1,i}=DP_{1,i-1}+sumi_n$

$DP_{0,j}=DP_{0,j-1}+sumj_m$

第一维中 1存的是关于行的，0是关于列的

最后处理时，要从$0\to k $ 枚举

对于行取了$i$次时，对于列就取了$k-i$次

总损耗就为$i\times (k-i )*p$

```cpp
ans=max(ans,max(dp[1][i]+dp[0][k-i]-(k-i)*i*p,dp[0][i]+dp[1][k-i]-(k-i)*i*p));

```
交上去后，TLE

为什么？

各位看下范围：

![](https://cdn.luogu.com.cn/upload/image_hosting/8zb52fzj.png)

我的脑海中曾经做过的一样的题目：

![](https://cdn.luogu.com.cn/upload/image_hosting/uyb2bnhm.png)

$k\leq10^6$ ，必须要优化

下面引入了我们的 multiset



------------

**什么是 multiset**

set和multiset会根据特定的排序将元素排序。

两者不同之处在于，multisets允许元素重复，而set不允许重复。

但是存取有限制：

不提供直接用来存取元素的任何操作元素

通过迭代器进行元素的存取

这里用到的几个操作：

insert()  在集合中插入元素

erase() 删除集合中的元素

end() 返回指向最后一个元素的迭代器

clear() 清除所有元素

添加greater<int> 会使得排序为降序排序,更大的在前面。

不加第二个参数，会默认为是less<int>，即按升序排序。
  
multiset会对插入的元素进行自动排序
  
这直接满足了我们这道题目的需求
  
  

------------

 
```cpp
  
#include<bits/stdc++.h>
using namespace std;
#define For(i,a,b)	for(int i=a;i<=b;i++)
#define Rep(i,a,b)	for(int i=a;i>=b;i--)
inline long long read()
{
	char c=getchar();long long x=0;bool f=0;
	while(!isdigit(c))f^=!(c^45),c=getchar();
	while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f)x=-x;return x;	
}
long long ans,L[1000005],R[1000005];
int N,M,K,P,A[1005][1005];
multiset<long long> G;
int	main()
{
	N=read();M=read();K=read();P=read();
	For(i,1,N)
		For(j,1,M)
			A[i][j]=read();
	G.clear();
	For(i,1,N)
	{
		int t=0;
		For(j,1,M)
		t+=A[i][j];
		G.insert(t);
	}
	For(i,1,K)
	{
		multiset<long long>::iterator x=--(G.end());
		long long t=*x;
		G.erase(x);
		G.insert(t-M*P);
		L[i]=L[i-1]+t;
	}
	G.clear();
	For(j,1,M)
	{
		int t=0;
		For(i,1,N)
			t+=A[i][j];
		G.insert(t);
	}
	For(i,1,K)
	{
		multiset<long long>::iterator x=--(G.end());
		long long t=*x;
		G.erase(x);
		G.insert(t-N*P);
		R[i]=R[i-1]+t;
	}
	ans=-(1ll<<60);
	For(i,0,K)
		ans=max(ans,L[i]+R[K-i]-1ll*i*(K-i)*P);
	printf("%lld\n",ans);
}  
  
```
  


------------

**其余几个注意点:**
  
$ans$要先赋予很小的值如代码中的，不然在处理过程中会有更小的最大值没被赋予（要用完操作次数）
  
N与M在操作中不能反（模拟赛中丢了AC）
  
感谢管理的审核
  

---

## 作者：白简 (赞：1)

### 题目大意
给出一个 $n \times m$ 的矩阵，并进行 $k$ 次操作，每次操作将矩阵的一行或一列的所有元素的值减 $p$，得到的分数为这次修改之前这一列或一行的元素和，求分数最大值。
### 思路
先说一下假贪心为什么是错的。

有一个很显然的贪心思路，分别用两个堆分别维护行与列的和，每次在两个堆的堆顶选最大的。

这种思路显然是错误的，我们直接给出一个组 hack 数据：


```
2 6 6 1
1 1 1 1 1 1
1 1 1 1 1 1
```

如果采用假贪心会导致先选择两个行，答案为 $8$；但如果选择六列，答案为 $18$。


我们从每个格子的角度去考虑，假设我们已知这个格子被选了 $x$ 次，那么它的贡献应当是 $a+ a - p + a - 2p + \dots + a - (x - 1)p$。我们发现贡献与这个格子是在行中被选中还是在列中被选中无关，那么我们就可以假设先操作所有的行，再操作所有的列。

我们还是把行和列分开贪心，记 $ansLine_i$ 表示行选了 $i$ 个的最大答案，$ansRow_i$ 为列的，同理。

那么显然有

$$ans=\max_{i=0}^{k} \left\{ Line_i + Row_i-i\times p (k-i) \right\}$$

### Code
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1255;
const int M = 1005000;

long long n,m,k,p;

long long a[N][N];

long long ans = LLONG_MIN + 114514;

priority_queue<long long> queLine,queRow;
// Sum of Line or Row
long long ansLine[M],ansRow[M];

int main() {
    ios::sync_with_stdio(false);
    
	cin >> n >> m >> k >> p;
    
    for(int i = 1;i <= n; i++) 
        for(int j = 1;j <= m; j++) 
            cin >> a[i][j];
    
    long long LineSum = 0;
    for(int i = 1;i <= n; i++) {
        LineSum = 0;
        
        for(int j = 1;j <= m; j++) 
            LineSum += a[i][j];
            
        queLine.push(LineSum);
    }
    
    long long RowSum = 0;
    for(int i = 1;i <= m; i++) {
        RowSum = 0;
        
        for(int j = 1;j <= n; j++) 
            RowSum += a[j][i];
            
        queRow.push(RowSum);
    }
	
    for(int i = 1;i <= k; i++) {
        long long Line,Row;
        Line = queLine.top();
        Row = queRow.top();
        
        queLine.pop();
        queRow.pop();
        
        ansLine[i] = ansLine[i - 1] + Line;
        ansRow[i] = ansRow[i - 1] + Row;

        queLine.push(Line - p * m);
        queRow.push(Row - p * n);
    }

    for(int i = 0;i <= k; i++)
        ans = max(ans,ansLine[i] + ansRow[k - i] - 1ll * i * (k - i) * p);

    cout << ans << "\n";
    return 0;
}
```

---

## 作者：Utilokasteinn (赞：1)

## [CF446B](https://www.luogu.com.cn/problem/CF446B)

如果你 $\tt Wa\;on\;\#4$，是因为再进行操作时，有多个相同的最大值。

举个例子，行最大值只有 $1$ 个，列最大值有 $100$ 个，而你现在只能进行 $100$ 次操作，若进行行操作显然是不合算的，所以答案是错的。

而你又显然不好维护又几个最大值什么的。当然，如果你想写平衡树也行（

现在进入正题。

首先分析题目，发现操作顺序是不会影响答案的。

这个很好证明。

对于两次操作 $X$ 和 $Y$，若都是行操作或者都是列操作，那么肯定不会互相影响。

如果 $X$ 和 $Y$ 为不同的操作，设 $X$ 是对第 $x$ 行进行操作，$Y$ 是对第 $y$ 列进行操作。

在没有交换顺序的时候贡献为（第 $x$ 行的数的和）加上（第 $y$ 列的数的和）再减去 $p$，$p$ 就是重合的那个地方减去的。

交换后显然答案是（第 $y$ 列的数的和）加上（第 $x$ 行的数的和）再减去 $p$，交换前后两者显然相等。

所以我们只需要考虑连续进行若干次行操作再连续进行若干次列操作如何使贡献最大。

因为行操作互不影响，列操作也互补影响，只需要维护一个堆，就可以求出 $i$ 次（$0\le i\le k$）行或列操作的最大贡献，最后枚举操作次数找最大答案。

代码如下：


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read()
{
	int s=0,f=1;char c=getchar();
	for(;!isdigit(c);c=getchar())
		if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())
		s=s*10+c-'0';
	return s*f;
}
int n,m,k,v,a[1005][1005];
priority_queue<int>q1,q2;
int tag1,tag2;
ll ans1[1000005],ans2[1000005],ans=-9e18;
int main()
{
	n=read(),m=read(),k=read(),v=read();
	for(int i=1;i<=n;i++)
	{
		int sum=0;
		for(int j=1;j<=m;j++)
			a[i][j]=read(),sum+=a[i][j];
		q1.push(sum);
	}
	for(int i=1;i<=m;i++)
	{
		int sum=0;
		for(int j=1;j<=n;j++)
			sum+=a[j][i];
		q2.push(sum);
	}
	for(int i=1;i<=k;i++)
	{
		int maxn1=q1.top(),maxn2=q2.top();
		q1.pop(),q2.pop();
		ans1[i]=ans1[i-1]+maxn1;
		ans2[i]=ans2[i-1]+maxn2;
		q1.push(maxn1-m*v);
		q2.push(maxn2-n*v);
	}
	for(int i=0;i<=k;i++)
		ans=max(ans,ans1[i]+ans2[k-i]-1ll*i*(k-i)*v);
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：耶耶小朋友 (赞：1)

## 题解 [CodeForces - 447D]DZY Loves Modification

### 方法：贪心

这题我们可以用贪心解决。

我们发现行与列之间是独是可以分开考虑的，两者没有关系，选择一行队列的影响是一样的。

我们预处理两个数组 $sum1$ 和 $sum2$，$sum1_{i}$ 表示选 $i$ 行的最大值，$sum2_{i}$ 表示选 $i$ 列的最大值。

我们也同样预处理出两个大根堆 $x$ 和 $y$ ，先将每行的快乐值丢进 $x$ 中，之后取最大值，更新 $sumi$（$sumi_{i} = sumi_{i - 1} +$ 最大值），再减去 $p$ * 列数 重新插回 $x$ 中。

列同理。

最后用 $i$ 从 $0$ 到 $k$ 枚举，找到 $sum1[i] + sum2[k - i] - i * (k - i) * p$ 的最大值。

$sum1[i]$：选 $i$ 行的最大值。

$sum2[k - i]$ ：选剩余次数的列的最大值。

$i * (k - i) * p$：行对列的影响（$i * p$）和列对行的影响（$(k - i) * p$）。

具体见代码。

## Code:

``` cpp
#include<bits/stdc++.h>
using namespace std;
//考虑unsigned long long
typedef long long ll;
const int N = 1010;
ll a[N][N];
const int M = 1000010;
ll sum1[M],sum2[M];

priority_queue<ll> x,y;
int main () {
	std::ios::sync_with_stdio(false);
	ll n,m,k,p;
	cin >> n >> m >> k >> p;
	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= m;j++) {
			cin >> a[i][j];
		}
	}
	//每行的初始快乐值 
	for (int i = 1;i <= n;i++) {
		ll sum = 0;
		for (int j = 1;j <= m;j++) {
			sum += a[i][j];
		}
		//插入 
		x.push(sum);
	}
	//每列的初始快乐值 
	for (int i = 1;i <= m;i++) {
		ll sum = 0;
		for (int j = 1;j <= n;j++) {
			sum += a[j][i];
		}
		//插入 
		y.push(sum);
	}
	for (int i = 1;i <= k;i++) {
		//最大值 
		int op = x.top();
		x.pop();
		//更新 
		sum1[i] = sum1[i - 1] + op;
		//插回 
		x.push(op - p * m); 
	}
	for (int i = 1;i <= k;i++) {
		//最大值 
		int op = y.top();
		y.pop();
		//更新 
		sum2[i] = sum2[i - 1] + op;
		//插回 
		y.push(op - p * n);
	}
	ll mx = -0x3f3f3f3f3f3f;
	//取最大值 
	for (int i = 0;i <= k;i++) {
		mx = max(mx,sum1[i] + sum2[k - i] - i * (k - i) * p); 
	}
	cout << mx;
	return 0;
}

```

$The\ end.$



---

## 作者：Linune_Gump (赞：1)

# [CF446B DZY Loves Modification](https://www.luogu.com.cn/problem/CF446B) 题解

## 解释题意
~~不得不吐槽这个翻译太简单了。~~

给定一个二维矩阵。在这个二维矩阵上对某一行或一列上的每一个元素都减去给定的$p$，减去了$k$行或列，并把减去的那行或列上的值的和记为该操作的贡献。求最大的贡献总和。
## 分析题目
看到“最大”的字眼，一般考虑贪心和动归。
此题应当采用贪心算法。  
既然是行或列总和记为贡献，因此肯定要考虑前缀和。

## 思路1
维护行列的前缀和并排序，取最大的一个前缀和并删去一个之后重新排序，一直操作$k$次，并维护每次的愉悦值。
（这种做法非常的麻烦，很容易超时，蒟蒻我写了一半就放弃了，这里就不给代码了）
## 思路2
需要思考这样一个问题：每一次操作是否对下一次操作有影响？  
很容易发现，没有影响。
因为删去一行/列只是减去一行的操作，对其他行列没有影响。  
因此，可以维护两个数组$ans$_ $hang$和$ans$_ $lie$。一个是行，一个是列，分别操作若干次并存储。  
其中ans[i]表示选择i所能产生的最大价值
### 去重
需要注意的是，如果两个位置重合了，那么原来的位置就被减去了一个$p$，如果选了i个行和$k - i$个列，则重合面积就是$i(k - i)$  
重合部分需要减去。
### 排序
为了速度，排序部分采用堆（能做这题的大佬，相信不需要我讲什么是堆了）

### 代码部分
```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
const int N = 2010;

priority_queue<long long> q_hang, q_lie;
long long n, m, k, p;
long long hang[N], lie[N];
long long ans_hang[N * N], ans_lie[N * N];
long long ans = -1e14;//由于可以减到负值，因此ans的初始值需要为负无穷

int main()
{
	scanf("%d%d%d%d",&n, &m, &k, &p);
	long long x;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
		{
			scanf("%lld",&x);
			hang[i] += x;
			lie[j] += x;
		}
	}
	for(int i = 0; i < n; i++)
		q_hang.push(hang[i]);
	for(int i = 0; i < m; i++)
		q_lie.push(lie[i]);
	for(int i = 1; i <= k; i++)//最坏情况全选横着的，所以最多做k次
	{
		x = q_hang.top();
		ans_hang[i] = ans_hang[i - 1] + x;
		q_hang.pop();
		q_hang.push(x - m * p);
	}
	for(int i = 1; i <= k; i++)
	{
		x = q_lie.top();
		ans_lie[i] = ans_lie[i - 1] + x;
		q_lie.pop();
		q_lie.push(x - n * p);
	}
	for(int i = 0; i <= k; i++)
		if(ans < ans_hang[i] + ans_lie[k - i] - 1LL * i * (k - i) * p)
			ans = ans_hang[i] + ans_lie[k - i] - 1LL * i * (k - i) * p;
	printf("%lld\n",ans);
	return 0;
}
```

---
# ----完结撒花，抄袭可耻-----

---

## 作者：Sonnety (赞：0)

## 普通贪心思路

就是不计后果的贪心，取行最大值和列最大值，比较谁更大就取谁，并减 $k$ 重新比较入堆，若相等就取使得减少的最小的。

```
#include<bits/stdc++.h>
#define int long long
#define MYMIN -200708310309393939 
using namespace std;
namespace Testify{
    inline int read(){
        int f(1),x(0);
        char ch=getchar();
        for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
        for(;isdigit(ch);ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
        return f*x;
    }
    inline void Write(int x){
        if(x>9) Write(x/10);
        putchar(x%10+48);
    }
    inline void write(int x){
        if(x<0) putchar('-'),x=-x;
        Write(x);
        putchar('\n');
    }
}
using namespace Testify;
int n,m,k,p,Tempestissimo(0);
const int N=10005;
int op[N][N];
struct node{
    int val;
    friend inline bool operator<(const node &a,const node &b){
        return a.val>b.val;
    }
}hang[(int)1e6+50],lie[(int)1e6+50];
int tot; 
int maxhang=MYMIN,maxlie=MYMIN,wherehang,wherelie;
signed main(void){
//	freopen("shuju.in","r",stdin);
//	freopen("data.out","w",stdout);
    n=read(),m=read(),k=read(),p=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            op[i][j]=read();
            hang[i].val+=op[i][j];
        }
    }
     for(int j=1;j<=m;++j){
        for(int i=1;i<=n;++i){
            lie[j].val+=op[i][j];
        }
    }
    for(register int i=1;i<=n;i++){
        if(maxhang<hang[i].val){
            maxhang=hang[i].val;
            wherehang=i;
        }
    }
    for(register int i=1;i<=m;i++){
        if(maxlie<lie[i].val){
            maxlie=lie[i].val;
            wherelie=i;
        }
    }
    while(k--){
        if(maxhang>maxlie||(maxhang==maxlie&&n>m)){
            Tempestissimo+=maxhang;
            maxhang=MYMIN;
            hang[wherehang].val-=p*m;
            for(register int i=1;i<=m;i++){
                lie[i].val-=p;
            }
            maxlie-=p;
            for(register int i=1;i<=n;i++){
                if(maxhang<hang[i].val){
                    maxhang=hang[i].val;
                    wherehang=i;
                }
            }
        }
        else if(maxhang<maxlie||((maxhang==maxlie&&n<=m))){
            Tempestissimo+=maxlie;
            maxlie=MYMIN;
            lie[wherelie].val-=p*n;
            for(register int i=1;i<=n;i++){
                hang[i].val-=p;
            }
            maxhang-=p;
            for(register int i=1;i<=m;i++){
                if(maxlie<lie[i].val){
                    maxlie=lie[i].val;
                    wherelie=i;
                }
            }
        }
    }
    cout<<Tempestissimo<<endl;
    return 0;
}
```

## 分析错误

但是这个思路拿不了满分，为什么呢？

hack：

input：

```
2 3 3 9
0 7 9
5 6 0
```

output:
```
27
```

经过手模，我们发现了该算法的错误：

在第一次选的时候，本算法选了贡献较大的第一行：`0 7 9`。

但是我们也可以选择第二列：
```
7
6
```

这样我们的算法似乎更优：$16-13=3$。

但是在第二次选择的时候，本算法选择了第二列：

```
-2
6
```

而我们可以选择第三列：
```
9
0
```

这样两种选法的贡献就被反超：$9-4=5>3$。

所以说，我们需要枚举所有的可能情况再选择最优方案，最初的最优不等于最优，如果仍然以这个思路去做，时间复杂度不会小于 $O(n^2)$。

因此我们考虑不再动态修改。

当我们选择了 $i$ 列，就应该选择 $k-i$ 行，然后再考虑它们因删去 $p$ 造成的贡献损失。

预处理时间复杂度 $O(n\times m+2k \log_k)$，查询复杂度 $O(k)$。
  
注意：

* 数据有负数，$ans$ 初始值要极小数

[Code](https://codeforces.com/contest/446/submission/218458926)

---

## 作者：songhongyi (赞：0)

考虑弱化版问题：只有行的操作。

显然可以贪心，按照每行的和从大到小取，并动态地维护。正确性通过调整易证。

那么考虑原问题，我们期望它的行列独立，但是每次列的操作位置会影响这次的贡献。感觉这不太好办。

但如果我们从每个格子的角度考虑问题，若我们已知其被选择了 $s$ 次，其贡献应该为 $a+a-p+a-2p+\cdots+a-\left(s-1\right)p$。可以发现这件事情**与这个格子是在行中选中还是列中选中无关**。因此我们不妨令所有行操作先进行，列操作后进行。

我们可以预处理出行和列独立 $i$ 次操作后的贡献 $f_i,g_i$。这部分的方法与开头的弱化版问题相同。

计算答案时，枚举选用行操作的次数 $i$，则答案为 $ f_i+g_{k-i}+i\left(k-i\right)\cdot p$。其中 $i\left(k-i\right) \cdot p$ 是重复的贡献，即 $k-i$ 次列操作，每次列操作都忽略的所有的 $i$ 次行操作减少的部分 $i \cdot p$。

这样我们解决了问题。忽略输入和求和，复杂度为 $O\left(n \log n + k\right)$。



---

## 作者：Hisaishi_Kanade (赞：0)

首先，想到一个很神秘的贪心：每次挑出和最大的一行或一列，对其进行操作。

但是它是错的。

那么这是否给了我们启发，**行列一起贪心不可行，那我分开贪心呢**？

我们设立两个辅助数组，初始 $row_{i}=\sum\limits_{j=1}^m a_{i,j}$，$col_{j}=\sum\limits_{i=1}^n a_{i,j}$。

定义 $f_{0,i}$ 表示在不考虑列的情况下，对行进行 $i$ 次操作所得最大分数。

显然 $f_{0,0}=0$ 考虑如何求出 $f_{0,1},f_{0,2},\cdots,f_{0,k-1},f_{0,k}$。

不难想到一个贪心策略，每次在 $row$ 数组中找到最大的值 $row_{pos}$ 转移 $f_{0,i}=f_{0,i-1}+row_{pos}$，再对这一行操作——即 $row_{pos}\gets row_{pos}-m\times p$。


类似地定义 $f_{1,i}$ 表示在不考虑行的情况下，对列进行 $i$ 次操作所得最大分数。类似地用 $col$ 转移。

发现需要一个快速找到最大值，对最大值进行修改的数据结构，堆就可以胜任。

最后考虑如果从 $f_{0/1,i}$ 推得答案。

容易发现，$i$ 行 $k-i$ 列的相交次数共有 $i\times(k-i)$ 个，则 $ans=\max\{f_{0,i}+f_{1,k-i}-i\times(k-i)\times p\}$。

```cpp 
#include <queue>
#include <vector>
#include <algorithm>
int n,m,k,p,i,j;
std::priority_queue<long long> q;
long long f[2][1000005],row[1005],col[1005],a[1005][1005];
int main()
{
	int t=1;
	while(t--)
	{
		long long ret=-(1ll<<60),delta,mid;
		n=read();m=read();
		k=read();p=read();
		for(i=1;i<=k;++i)
			f[0][i]=f[1][i]=0;
		for(i=1;i<=n;++i)
			row[i]=0;
		for(i=1;i<=m;++i)
			col[i]=0;
		for(i=1;i<=n;++i)
			for(j=1;j<=m;++j)
				a[i][j]=read();
		for(i=1;i<=n;++i)
			for(j=1;j<=m;++j)
				row[i]+=a[i][j];
		for(i=1;i<=n;++i)
			for(j=1;j<=m;++j)
				col[j]+=a[i][j];
		while(!q.empty())
			q.pop();
		for(i=1;i<=n;++i)
		{
			q.push(row[i]);
		}
		delta=m*p;
		for(i=1;i<=k;++i)
		{
			f[0][i]=f[0][i-1]+q.top();
			mid=q.top();
			q.pop();
			q.push(mid-delta);
//			printf("%lld\n",q.top());
		}
		while(!q.empty())
			q.pop();
		for(i=1;i<=m;++i)
		{
			q.push(col[i]);
		}
		delta=n*p;
		for(i=1;i<=k;++i)
		{
			f[1][i]=f[1][i-1]+q.top();
			mid=q.top();
			q.pop();
			q.push(mid-delta);
		}
		for(i=0;i<=k;++i)
		{
			ret=std::max(ret,f[0][i]+f[1][k-i]-1ll*i*(k-i)*p);
		}
		printf("%lld\n",ret);
	}
	return 0;
}
```

---

