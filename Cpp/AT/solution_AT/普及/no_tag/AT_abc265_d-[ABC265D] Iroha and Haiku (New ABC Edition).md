# [ABC265D] Iroha and Haiku (New ABC Edition)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc265/tasks/abc265_d

長さ $ N $ の数列 $ A=(A_0,\ldots,A_{N-1}) $ があります。  
次の条件を全て満たす整数の組 $ (x,y,z,w) $ が存在するか判定してください。

- $ 0\ \leq\ x\ <\ y\ <\ z\ <\ w\ \leq\ N $
- $ A_x\ +\ A_{x+1}\ +\ \ldots\ +\ A_{y-1}\ =\ P $
- $ A_y\ +\ A_{y+1}\ +\ \ldots\ +\ A_{z-1}\ =\ Q $
- $ A_z\ +\ A_{z+1}\ +\ \ldots\ +\ A_{w-1}\ =\ R $

## 说明/提示

### 制約

- $ 3\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- $ 1\ \leq\ P,Q,R\ \leq\ 10^{15} $
- 入力に含まれる値は全て整数である

### Sample Explanation 1

$ (x,y,z,w)=(1,3,6,8) $ が条件を満たします。

## 样例 #1

### 输入

```
10 5 7 5
1 3 2 2 2 3 1 4 3 2```

### 输出

```
Yes```

## 样例 #2

### 输入

```
9 100 101 100
31 41 59 26 53 58 97 93 23```

### 输出

```
No```

## 样例 #3

### 输入

```
7 1 1 1
1 1 1 1 1 1 1```

### 输出

```
Yes```

# 题解

## 作者：Tooler_Yang (赞：8)



这道题目就是让我们求能不能在数列 $A$ 中找到连续的三段使这三段的和分别是 $P$，$Q$，$R$。

这道题目拿到手，第一感应该是去枚举这四个边界，然后用前缀和求和。

复杂度：$O(n^4)$


```cpp
// Problem: AT_abc265_d [ABC265D] Iroha and Haiku (New ABC Edition)
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_abc265_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Writing time:2022-10-24 18:43:44

#include<bits/stdc++.h>
using namespace std;
int a[200001];
int sum[200001];
int main(){
	int n,p,q,r;
	cin>>n>>p>>q>>r;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum[i]=sum[i-1]+a[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			if(sum[j]-sum[i-1]==p){
				for(int k=j;k<=n;k++){
					if(sum[k]-sum[j-1]==q){
						for(int w=k;w<=n;w++){
							if(sum[w]-sum[k-1]==r){
								cout<<"Yes";
								return 0;
							}
						}
					}
				}
			}
		}
	}
	cout<<"No";
	return 0;
}
```
只是可惜 $n\le 2 \times10^5$，就算是 $O(n^2)$ 也过不了。

---

首先，这道题目一定要用前缀和，不然就有一个 $O(n)$ 葬送在求区间和里面了。

设我们已经找到了一个前缀和序列 `sum`，使得 $sum_i=sum_{i-1}+a_i$。

然后我们就要思考，既然是连续的三个区间，那如果我能找到三个区间的左端点 $x$，然后再看看右边有没有一个点 $y$，使得 $sum_y-sum_{x-1}=P$，再找一个点 $z$ 使 $sum_z-sum_{x-1}=Q$，同理找到 $w$ 使 $sum_w-sum_{x-1}=R$，那是不是说明这样的四元组 `(x,y,z,w)`，是可以找到的。

但是这样和上面的代码有什么区别呢？

代码没有区别，但是思想有区别。

我们可以尝试用一个STL 容器来记录所有的 `sum`，这样当我们找后面的 $sum_{y,z,w}$ 时，只需要用 STL 里面自带的函数 `find`，就可以啦。

那是哪个容器呢？

显然的，应该用 `set`，它有 `insert` 插入功能，还有 `find` 查询功能。

然后再用 `auto` 或者 `iterator` 迭代器遍历每一个节点的 `sum` 就可以啦。

`auto` 版
```cpp
// Problem: AT_abc265_d [ABC265D] Iroha and Haiku (New ABC Edition)
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_abc265_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Writing time:2022-10-24 18:43:44

#include<bits/stdc++.h>
using namespace std;
long long a[200001];
long long sum;
set<long long> st({0});
int main(){
	long long n,p,q,r;
	cin>>n>>p>>q>>r;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum+=a[i];
		st.insert(sum);
	}
	for(auto x:st){
		if(st.find(x+p)!=st.end()&&st.find(x+p+q)!=st.end()&&st.find(x+p+q+r)!=st.end()){
			cout<<"Yes"<<"\n";
			return 0;
		}
	}
	cout<<"No"<<"\n";
	return 0;
}
```
`iterator` 版
```cpp
// Problem: AT_abc265_d [ABC265D] Iroha and Haiku (New ABC Edition)
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_abc265_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Writing time:2022-10-24 18:43:44

#include<bits/stdc++.h>
using namespace std;
long long a[200001];
long long sum;
set<long long> st({0});
int main(){
	long long n,p,q,r;
	cin>>n>>p>>q>>r;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum+=a[i];
		st.insert(sum);
	}
	for(set<long long>::iterator it=st.begin();it!=st.end();it++){
		if(st.find(*it+p)!=st.end()&&st.find(*it+p+q)!=st.end()&&st.find(*it+p+q+r)!=st.end()){
			cout<<"Yes"<<"\n";
			return 0;
		}
	}
	cout<<"No"<<"\n";
	return 0;
}
```
最后复杂度应该都是 $O(nlogn)$。

---

## 作者：lsz_ (赞：3)

### 写在前面

这题记得开 `long long`！！！

### 题目大意

给定一个长度为 $N$ 的序列 $A=(A_0,A_1...A_{N-1})$，找到一组 $(x,y,z,w)(0\leq x<y<z<w\leq N)$ 使得

$\sum\limits_{i=x}^{y-1}A_i=P \sum\limits_{i=y}^{z-1}A_i=Q \sum\limits_{i=z}^{w-1}A_i=R$。

### 思路

吃惊地发现 $\forall 1\leq A_i$，所以这题就非常容易的想到了 **前缀和**。

先假设 $B_x=\sum\limits_{i=1}^{x}A_i$。

对于每个在 $B$ 数组的 $x$ 而言，只要 $x+P,x+P+Q,x+P+Q+R$ 都在 $B$ 数组里则就可以输出 `Yes`，若果找不到符合条件的 $x$，则输出 `No`。

那么有了这样的思路，就可以先暴力枚举 $x$，再 ~~二分查找~~ 用 **set** 查找剩下的三个数，如果不会 set 就用二分吧。

### 代码

```
#include<bits/stdc++.h>
#define LL long long
using namespace std;
LL n,p,q,r,i,x,sum;
set<LL>st;
int main()
{
	st.insert(0);
	cin>>n>>p>>q>>r;
	for(i=1;i<=n;i++)
	{
		cin>>x;
		sum+=x;
		st.insert(sum);
	}
	for(auto a:st)
	{
		if(st.find(a+p)!=st.end()&&st.find(a+p+q)!=st.end()&&st.find(a+p+q+r)!=st.end())
		{
			cout<<"Yes";
			return 0;
		}
	}
	cout<<"No";
	return 0;
}
```

---

## 作者：Exp10re (赞：2)

## 总体思路

怎么题解区都是用 ```set``` 的，这里提供一种尺取做法。

考虑对于原数列中的第 $l$ 个数，维护使得 $A_l+A_{l+1}+\cdots+A_{r-1}$ 分别等于 $P,Q,R$ 的每一个 $r$，当然，也可能没有相对应的 $r$。

接下来我们枚举 $0 \cdots n-1$ 之中的每一个位置 $x$，判断是否有相对应的 $y$ 使得 $A_x+A_{x+1}+\cdots+A_{y-1} = P$，如果有，判断是否有相对应的 $z$ 使得 $A_y+A_{y+1}+\cdots+A_{z-1}= Q$，接下来用同样的方式判断是否有相对应的 $w$ 使得 $A_z+A_{z+1}+\cdots+A_{w-1}=R$ 等于 $R$。如果都有，那么 $x,y,z,w$ 就是满足条件的一组解。

如果遍历完 $0 \cdots n-1$ 中的所有位置 $x$ 都没有相对应的解，那么就认为是无解。

## 实现细节：关于维护

在维护的过程中考虑使用尺取法，相比于 ```set``` 做法可以省下一个 $\log n$ 的时间复杂度。

假设我们现在正在维护和为 $P$ 的区间（当然 $Q$ 和 $R$ 同理），则考虑维护两个指针 $L$ 和 $R$，接下来：

- 如果 $A_L+A_{L+1}+\cdots+A_{R-1} \lt P$，尝试不断右移 $R$。
-  $A_L+A_{L+1}+\cdots+A_{R-1} \lt P$，那么 $R$ 是在 $L$ 位置的一个和为 $P$ 的解，记录它。
-  $A_L+A_{L+1}+\cdots+A_{R-1} \gt P$，那么继续右移 $R$ 也不会再有解了。撤销上一步右移 $R$ 的操作，记录在 $L$ 位置和为 $P$ 的情况无解，然后尝试右移 $L$。
- 如果在移动过程中 $R \gt n$，那么显然 $L$ 以及大于 $L$ 的所有位置都无解。

使用尺取法维护出所有解之后跑一遍上面的判断就能出结果了。

尺取法时间复杂度为 $O(n)$（因为两个指针都只需要跑一遍 $0 \cdots n-1$ ），判断时间复杂度也为 $O(n)$，总时间复杂度为 $O(n)$。

理论上严格优于 ```set``` 和二分做法……但是时间就是跑不过 ```set``` 和二分做法的代码……

## 代码

代码有注释，可以搭配注释食用。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=200030;
long long n,num[4],a[MAXN],p[4][MAXN];
void ruler(long long t)
{
	long long l,r,cnt;
	l=-1;
	r=-1;
	cnt=0;
	for(l=0;l<n;l++)
	{
		cnt-=a[l-1];
		while(cnt<num[t]&&r<=n)//不断尝试右移 R 直到总和大于或等于 P/Q/R 
		{
			r++;
			if(r>n)
			{
				break;
			}
			cnt+=a[r];
		}
		if(r>n)
		{
			p[t][l]=-1;//无解 
		}
		else if(cnt>num[t])
		{
			cnt-=a[r];
			r--;
			p[t][l]=-1;//无解，撤销上一步操作（以免影响下一个L的判断 
		}
		else
		{
			p[t][l]=r+1;//有解，记录。 
		}
	}
	p[t][n]=-1;//避免搜索出界 
	return;
}
int main()
{
	long long i,ta,tb;
	scanf("%lld%lld%lld%lld",&n,&num[1],&num[2],&num[3]);//num 1 2 3 分别是 P Q R 
	for(i=0;i<n;i++)
	{
		scanf("%lld",&a[i]);
	}
	ruler(1);
	ruler(2);
	ruler(3);
	for(i=0;i<n;i++)
	{
		if(p[1][i]!=-1)
		{
			ta=p[1][i];
			if(p[2][ta]!=-1)
			{
				tb=p[2][ta];
				if(p[3][tb]!=-1)
				{
//					printf("%lld %lld %lld %lld",i,ta,tb,p[3][tb]);
					printf("Yes");
					return 0;
				}
			}
		}
	}
	printf("No");
	return 0;
}
```

---

## 作者：Fkxxx (赞：2)

### 题意

给出一串数，请尝试在这串数中找到三段**连续**的子段，使得这三个子段的和分别为 $P$、$Q$ 和 $R$。问：是否可行？

### 思路

通过观察，我们可以发现，其实我们可以根据题目的要求写出一段关系式：

$A+P+Q+R+B$（其中 $A$ 表示被选子段前面没被选的子段和，其中 $B$ 表示被选子段后面没被选的子段和）

接下来，我们把这个式子带入前缀和，就会发现，如果我们知道了这三个子段中任意一个的一个端点，通过以下推导式，就能得到是否可行。

前缀和为 $S_{i} + P$ 的 $x$ 存在，且前缀和为 $S_{i} + Q + R$ 的 $x$ 存在，且前缀和为 $S_{i} + P + Q + R$ 的 $x$ 存在。

### 代码实现

所以，在代码实现时，我们寻找前缀和为 $a$ 的 $x$ 是否存在时，传统的方法是用 `map` 实现，但是，我用了另一种容器： `set`。我对 `set` 的理解是：集合。

本次我使用到 `set` 的功能是：`insert`、`find` 和 `end`。

- `insert`：在集合里插入某个元素。
- `find` 和 `end` ：我们可以用 `st.find( a ) != st.end()` 判断元素 `a` 是否在集合中存在。

### AC CODE

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n , a[200005] , s1 , s2 , s3 , sum ;
set<int> st( {0} ) ;
signed main(){
	cin >> n >> s1 >> s2 >> s3 ;
	for( int i = 1 ; i <= n ; i ++ ){
		cin >> a[i] ;
		sum += a[i] ;
		st.insert( sum ) ;
	}
	for( auto i : st ){
		if( st.find( i + s1 ) != st.end() && st.find( i + s1 + s2 ) != st.end() && st.find( i + s1 + s2 + s3 ) != st.end() ){
			cout << "Yes\n" ;
			return 0 ;
		}
	}
	cout << "No\n" ;
	return 0 ;
}
```

---

## 作者：FXT1110011010OI (赞：2)

# 题意简述

- 给定长度为 $n$ 的序列 $A = A_{0 \ldots N - 1}$ 以及三个整数 $P, Q, R$。
- 求序列中是否存在连续的三个区间，满足它们的区间之和分别是 $P, Q, R$。
- $3 \leq N \leq 2 \times 10 ^ 5$，$1 \leq A_i \leq 10 ^ 9$，$1 \leq P, Q, R \leq 10 ^ {15}$。

# 题目分析

看到题目，第一思路应该是枚举四个边界，用前缀和判断是否满足要求。但显然，这种 $O(N ^ 4)$ 暴力无法通过 $2 \times 10 ^ 5$ 的数据，会超时。

考虑其他方法。思考：如果把三个整数 $P, Q, R$ 改为只有一个整数 $P$，求序列中是否存在连续区间，满足此区间的和是 $P$，应该怎么做？有前缀和、双指针两种 $O(N)$ 的解法，这里我选择双指针。

用双指针，能在 $O(N)$ 的时间复杂度内算出 $A$ 数组中所有和为 $P$ 的子段，用一个数组 $s$ 记录：若存在以 $A_i$ 开头的子段满足“和为 $P$” 的要求，则 $s_i$ 表示子段结尾的下标；若不存在，则 $s_i = 0$。

同理，可以分别求出 $A$ 数组中所有和为 $P, Q, R$ 的子段，开三个数组 $s1, s2, s3$，分别表示计算和为 $P, Q, R$ 的子段时所记录的 $s$ 数组。

接着枚举 $0 \sim N - 1$，表示第一个子段的开头下标。假设当前枚举到下标 $i$，若 $s1_i$ 不为 $0$，即存在以 $i$ 为开头的子段满足“和为 $P$” 的要求，那么第二个子段的开头就是 $s1_i + 1$，同理判断 $s2_{s1_i + 1}$ 是否为 $0$，若不为 $0$ 满足，再判断 $s3$。如果都满足要求，就说明可以找出满足题目要求的三个区间，输出 `Yes`。

如果以那个下标为开头都无法满足要求，说名不存在满足要求的连续区间，输出 `No` 即可。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const LL N = 2e5 + 10;

LL a[N];
LL s1[N], s2[N], s3[N];

int main()
{
    LL n, p, q, R, s = 0;
    scanf("%lld%lld%lld%lld", &n, &p, &q, &R);
    for (LL i = 1; i <= n; i ++ )
    {
        scanf("%lld", &a[i]);
        s += a[i];
    }
    if (p > s || q > s || R > s)
    {
        printf("No\n");
        return 0;
    }
    for (LL l = 1, r = 0, sum = 0; l <= n; sum -= a[l], l ++ )
    {
        while (r <= n && sum < p) r ++ , sum += a[r];
        if (sum == p) s1[l] = r;
    }
    for (LL l = 1, r = 0, sum = 0; l <= n; sum -= a[l], l ++ )
    {
        while (r <= n && sum < q) r ++ , sum += a[r];
        if (sum == q) s2[l] = r;
    }
    for (LL l = 1, r = 0, sum = 0; l <= n; sum -= a[l], l ++ )
    {
        while (r <= n && sum < R) r ++ , sum += a[r];
        if (sum == R) s3[l] = r;
    }
    for (LL i = 1; i <= n; i ++ )
    {
        if (!s1[i]) continue;
        if (!s2[s1[i] + 1]) continue;
        if (!s3[s2[s1[i] + 1] + 1]) continue;
        printf("Yes\n");
        return 0;
    }
    printf("No\n");
    return 0;
}
```

---

## 作者：Littlestr (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc265_d)

## $1)$ 理解题意

#### 题目要求 $x,y,z,w$ ，使 $\sum\limits_{i=x}^{y-1}a[i] = P,\sum\limits_{i=y}^{z-1}a[i] = Q,\sum\limits_{i=z}^{w-1}a[i] = R$ 
 
可以发现，这里的 $x$ 、 $y$ 、$z$ 是连续的，所以题意也可以写成：

### 求三个连续的块，使每个块内的和分别等于 $P$ 、$Q$ 、$R$ 。

这里的**连续**是这题的关键，说明这要确定一个块，就可以确定下一个块的起点。
 
 ----
 
## $2)$ 找出特征
 
对于这些块有性质：如果假设已经确定了第一个块 $(l_{1},r_{1})$ ；

下一个块就是 $(r_{1}+1,r_{2})$ ， 其中 $r_{1}+1\le r_{2} \le n$ $($ 不考虑第三个块 $)$  。

-----

## $3)$ 代码实现 

对于 $l_{1}$，我们只能枚举。

对于 $r_{1}$，需要找到一个满足条件的点。

显然，暴力枚举 $r_{1}$ 是一个正确的方向，但是会超时。

这里为方便，令 $s[i] = \sum\limits_{j=1}^{i}a[i]$，因为 $1\le a[i]$，所以每一个 $s[i]$  都满足 $s[i-1]\le s[i]$

这就满足了一个**单调性**，我们要求的是一个定值，就可以直接二分查找下一个 $r_{1}$ ， 使这次的 $(l_{1},r_{1})$ 满足：

$\sum\limits_{i=l_{1}}^{r_{1}}a[i] = P $

因为已经求出了前缀和 $s$ ， 所以这个柿子又变成了：

$s[r_{1}] - s[l_{1}-1] = P$ 

那么代码的结构就是二分查找 $r_{1}$ 、$r_{2}$ 、$r_{3}$ ，下一个查找对象的起点是当前查找对象的终点$+1$，如果有一次没找到，那么就直接下一次。

复杂度大约为 $O(n$ $\log$  $n)$。

----

$Code$

```cpp

#include<bits/stdc++.h>
#define int long long

using namespace std;

inline int read(){
	int flag = 1,ans = 0;
	char s = getchar();
	while (s>'9' || s<'0'){
		if (s == '-') flag = -1;
		s = getchar();
	}
	while (s<='9' && s>='0'){
		ans*=10;
		ans+=s-'0';
		s = getchar();
	}
	return ans * flag;
}

const int N = 2e5+10;

int n,m,a[N],p,q,r,f[N];

int Find(int tmp,int flag){
	int mid,l = tmp,r = n;
	while (l<=r){
		mid = l + r >> 1;
		if (f[mid]-f[tmp-1] == flag){
			return mid;
		}
		if (f[mid]-f[tmp-1]>flag){
			r = mid-1;
		}
		if (f[mid]-f[tmp-1]<flag){
			l = mid+1;
		}
	}
	return -1;
}

signed main(){
	n = read();
    p = read();
    q = read();
    r = read();
	for (int i = 1;i<=n;++i){
		a[i] = read();
		f[i] = f[i-1]+a[i];
	}
	for (int i = 1;i<=n;++i){
		int pos = Find(i,p);
		if (pos == -1) continue;
		pos = Find(pos+1,q);
		if (pos == -1) continue;
		pos = Find(pos+1,r);
		if (pos == -1) continue;
		puts("Yes");
		return 0;
	}
	puts("No");
	return 0;
}

```

---

## 作者：Moon_Wind (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc265_d)

**前言**：

因为本题是老师给我们考思维训练的题。赛场上过了，发题解纪念一下。

------------

**题意简述**：

有一个长度为 $n$ 的序列，要求我们判断有没有连续的 $3$ 段使这 $3$ 段的和分别是 $P,Q,R$。

**解题思路**：

看到这个题目，我们首先想到的肯定是分别枚举 $x,y,z$ 和 $w$。而看一眼数据范围，$O(n^4)$ 的暴力很明显不能通过本题或拿到高分的。

我们可以尝试去进行优化，只枚举 $x$。显而易见的，因为 $a_i\ge 1$，所以这里会具有单调性。可以尝试用二分来求出剩下三个点。

**代码部分**：


------------
```cpp
#include<bits/stdc++.h>
#define int long long//要开long long。
using namespace std;
int n,q,p,a[200001],ll,sum[200001];
inline int check(int u,int o,int qq){//二分。
	int mid=(u+o)>>1;
	int l=u,r=o+1;//r记得加1。
	while(l+1<r){
		mid=(l+r)>>1;
		if(sum[mid]-sum[u-1]>qq) r=mid;//如果总和小于所要求的。
		else l=mid;//如果总和大于所要求的。
		
	}
	return l;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie();cout.tie(0);
	cin>>n>>q>>p>>ll;
	int y=q+p+ll;
	for(int i=1;i<=n;i++){
	    cin>>a[i]; 
	    sum[i]=sum[i-1]+a[i];//记录前缀和。
	} 
	for(int i=1;i<=n;i++){//枚举x。
		if(sum[n]-sum[i-1]<y) break;
		int m=check(i,n,y);//求出w。
	    if(sum[m]-sum[i-1]==y){
	    	int m1=check(i,m,q);//求出x。
	    	if(sum[m1]-sum[i-1]==q){
	    		int m2=check(m1+1,m,p);//求出y。
	    		if(sum[m2]-sum[m1]==p){
	    			cout<<"Yes";
					return 0; 
				}
			}
		}
	}
	cout<<"No"; 
	return 0;
}
```


---

## 作者：guanyf (赞：0)

### 题意
- 给定长度为 $N$ 的序列 $A$，求是否存在 $x,y,z,w$ 使得：

$$\sum_{i=x}^{y-1}A_i = P \qquad \sum_{i=y}^{z-1}A_i = Q \qquad \sum_{i=z}^{w-1}A_i = R$$

- $3 \le N \le 2 \times 10^5$

### 暴力
直接枚举 $x,y,z,w$，再计算和判断是否符合要求。由于计算和这一过程可以用[**前缀和**](https://zhuanlan.zhihu.com/p/436526162)优化，因此时间复杂度是 $\operatorname{O}(N^4)$。

------------

## $\text{Solution}$
### 分析、思路
观察暴力最耗费时间的地方：每次枚举 $x$ 都需要重新枚举 $y,z,w$。由于 $x$ 右移的过程是具有单调性的，且每次 $x$ 都是平滑的变化的，因此我们可以记录出它们上次的位置，再根据 $x$ 的移动来确定 $y,z,w$。

但是这样太麻烦了，怎么办？通过刚才的分析，我们知道了 $x$ 移动的过程是具有单调性的。$x$ 之所以会具有单调性，是因为**前缀和具有单调性**。设前置和数组为 $s$，我们可以找到第一个前缀和等于 $s_x + P$ 的位置 $y$，再找到第一个前缀和等于 $s_y + Q$ 的位置 $z$，接着找到第一个前缀和等于 $s_z + R$ 的位置 $w$。当这些位置都能找到时，输出 `Yes`；当没有一个符合条件的 $x,y,z,w$ 时，则输出 `No`。

时间复杂度：$\operatorname{O}(N\log N)$。

#### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 2e5 + 5;
int n, a[MAXN], x, y, z, cnt, s[MAXN];
signed main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> x >> y >> z;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], s[i] = s[i - 1] + a[i];
  }
  for (int i = 1; i <= n; i++) {
    int id_1 = lower_bound(s + i, s + 1 + n, x + s[i - 1]) - s;
    if (s[id_1] == x + s[i - 1]) {
      int id_2 = lower_bound(s + id_1 + 1, s + 1 + n, y + s[id_1]) - s;
      if (s[id_2] == y + s[id_1]) {
        int id_3 = lower_bound(s + id_2 + 1, s + 1 + n, z + s[id_2]) - s;
        if (s[id_3] == z + s[id_2]) {
          cout << "Yes", exit(0);
        }
      }
    }
  }
  cout << "No";
  return 0;
}
```


---

## 作者：lwx20211103 (赞：0)



## 简要题意

给你 $N,P,Q,R$ 四个数字，$N$ 代表数组长度，再给出一个数组，求是否存在一段**连续**的三个区间，区间之和分别是 $P,Q,R$。

题目要点：定数组为 $a$，$a_i \in \mathbb{Z^+},a_i \leq 10^9$。

$1 \leq P,Q,R \leq 10^{15}$。

说明 $P,Q,R$ 要开 `long long`。

## 题目分析

区间和，那一定涉及到前缀和。简单介绍一下前缀和，前缀和就是从第一个数开始，从前往后加起来。比如 $[1,2,3,4,5]$ 的前缀和就是 $[1,3,6,10,15]$，前缀和可以离线求区间和，预处理时间复杂度 $\Theta(n)$，查询复杂度 $\Theta(1)$。

代码：
```cpp
for (int i = 1; i <= n; i++)
{
   sum[i] = sum[i - 1] + a[i];//sum：前缀和数组
}
```

这样，我们可以先预处理数组，然后遍历一遍前缀和数组，枚举每个数字，如果每个数字加上 $P,Q,R$ 这三个数字的和都在前缀和数组内，就代表有结果，输出 `Yes`，否则 `No`。

因为数字均为正整数，所以前缀和数组单调递增，可以用二分查找或者 `std::set`，遍历一遍数组的时间复杂度为 $\Theta(n)$，二分查找的时间复杂度为 $\Theta(\log n)$，所以时间复杂度为 $\Theta(n\log n)$，而 $n \leq 2 \times 10^5$，可以解决问题。

## 代码区

STL 版：

```cpp
#include <bits/stdc++.h>
using namespace std;

long long tot;//不开龙龙见祖宗
set<long long> s({0});//这里一定要有这个，不然过不去

int main()
{
    long long n, p, q, r;
    cin >> n >> p >> q >> r;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        tot += x;
        s.insert(tot);
    }
    for (auto &&i : s)//c++11的新特性
    {
        if (s.find(i + p) != s.end() && s.find(i + p + q) != s.end() && s.find(i + p + q + r) != s.end())
        {
            cout << "Yes";
            return 0;
        }
    }
    cout << "No";
    return 0;
}

```


---

## 作者：Strelitzia_ (赞：0)

## 题目大意

给出一个序列 $\{a_n\}$ 和四个数 $p,q,r$，问是否存在 $x,y,z,w$ 使得 $1\le x<y<z<w\le n$ 且 $\displaystyle\sum_{i=x}^{y-1}a_i=p,\ \displaystyle\sum_{i=y}^{z-1}a_i=q,\displaystyle\sum_{i=z}^{w}a_i=r$。

这里 $\displaystyle\sum_{i=x}^{y-1}a_i=a_x+a_{x+1}+\dots+a_{y-1}$。

------------
## 思路

涉及到没有修改的区间和，我们首先想到前缀和。注意到 $1\le a_i$，我们做出来的前缀和还是具有单调性的。那么我们只要确定一个左端点 $i$、一个要查询的数值 $x$，就可以利用二分查找找到右侧的一个端点 $j$ 使得 $sum_{j-1}-sum_{i-1}=x$ 了。

于是我们的思路大致确定了：做出前缀和数列 $\{s_n\}$，枚举左端点 $x$，二分查找是否存在 $y$ 使得 $s_{y-1}-s_{i-1}=p$。存在的话我们就成功确定了 $y$。对于剩下的端点也这样查找。若四个点都确定了，就说明有解。

代码如下：

```cpp
int a[N],s[N],n,p,q,r;
signed main(){
	n=read(),p=read(),q=read(),r=read();
	for(int i=1;i<=n;i++) a[i]=read(),s[i]=s[i-1]+a[i];
	for(int i=1;i<=n;i++){
		int now1=lower_bound(s+1,s+n+1,p+s[i-1])-s;
//		printf("%lld now 1 %lld equal to %lld\n",i,now1,s[now1]-s[i-1]);
		if(s[now1]-s[i-1]!=p) continue;
		int now2=lower_bound(s+1,s+n+1,q+s[now1])-s;
//		printf("now 2 %lld\n",now2);
		if(s[now2]-s[now1]!=q) continue;
		int now3=lower_bound(s+1,s+n+1,r+s[now2])-s;
//		printf("now 3 %lld\n",now3);
		if(s[now3]-s[now2]!=r) continue;
		return puts("Yes"),Strelitzia_H;
	}return puts("No"),Strelitzia_H;
}
```

---

## 作者：_zzzzzzy_ (赞：0)

## 思路

因为没有负数，所以 $a$ 数组的前缀和是单调上升的，那么我们就可以用一个数组来表示 $a$ 数组的前缀和那么就可以用二分查找的方法来进行查找答案了。

这里可以用 `vector` 来进行查找，但因为简便就用了 `set` 来进行查找。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,p,q,r,cnt;
set<int>a={(0)};
signed main() {
	cin>>n>>p>>q>>r;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		cnt+=x;
		a.insert(cnt);
	}
	for(auto k:a){
		if(a.find(k+p)!=a.end()){
			if(a.find(k+p+q)!=a.end()){
				if(a.find(k+p+q+r)!=a.end()){
					cout<<"Yes\n";
					return 0;
				}
			}
		}
	}
	cout<<"No\n";
	return 0;
}
```

---

