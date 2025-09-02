# Flipper

## 题目描述

给你一个长度为 $ n $ 的数列 $ p $。

一个数列是 $ 1 $ 到 $ n $ 按某一顺序组成的阵列。例如，$ {2,3,1,5,4} $ 是一个数列，而 $ {1,2,2} $ 不是（因为 $ 2 $ 出现了两次），$ {1,3,4} $ 也不是一个数列（因为 $ n=3 $，但数列中包含 $ 4 $）。

对于数列 $ p $，进行一次如下操作：

- 选择一个区间 $ [l, r] $（$ 1\le l\le r\le n $，一个区间是一串连续的数 $ {p_l, p_{l+1}, \ldots, p_{r-1}, p_r} $），并将它反转过来。反转一个区间即交换如下的数对 $ (p_l, p_r),(p_{l+1}, p_{r-1}),\dots,(p_{l + i}, p_{r - i}) $（其中 $ l + i \le r - i $）。
- 交换前缀和后缀：$ [r+1, n] $ 和 $ [1, l - 1] $（注意：这些区间可能是空的）。

例如，给定 $ n = 5, p = \{2, \color{blue}{3}, \color{blue}{1}, 5, 4\} $，如果你选择区间 $ [l = 2, r = 3] $，反转区间以后 $ p = \{\color{green}{2}, \color{blue}{1}, \color{blue}{3}, \color{green}{5}, \color{green}{4}\color{black}\} $。接着交换区间 $ [4, 5] $ 与 $ [1, 1] $。得到 $ p = \{\color{green}{5}, \color{green}{4}, 1, 3, \color{green}{2}\color{black}\} $。可以证明这是操作后该排列的字典序的最大可能结果。

你需要输出通过一次所述操作后可以得到的字典序最大数列。

如果存在一个 $ i $（$ 1 \le i \le n $），使 $ a_j = b_j $ 对于 $ 1 \le j < i $ 且 $ a_i > b_i $，那么一个数列 $ a $ 的字典序大于数列 $ b $ 的字典序 。

## 说明/提示

对于 $ 100\% $ 的数据，$ 1 \le t \le 1000 $，$ 1 \le n \le 2000 $，保证每次 $ T $ 组测试数据的 $ n $ 之和不超过 $ 2000 $。

## 样例 #1

### 输入

```
9
5
2 3 1 5 4
9
4 1 6 7 2 8 5 3 9
4
4 3 2 1
2
2 1
6
3 2 4 1 5 6
7
3 2 1 5 7 6 4
10
10 2 5 6 1 9 3 8 4 7
4
4 2 1 3
1
1```

### 输出

```
5 4 1 3 2 
9 4 1 6 7 2 8 5 3 
3 2 1 4 
1 2 
6 5 3 2 4 1 
7 6 4 5 3 2 1 
9 3 8 4 7 1 10 2 5 6 
3 4 2 1 
1```

# 题解

## 作者：fengxiaoyi (赞：14)

[本文章同步发表于博客园](https://www.cnblogs.com/fengxiaoyi/p/17417930.html)

### 思路

这是一道水题，但细节很多......

首先，要求字典序最大，显然就想到了让最大的数字在第一位。

于是就进一步得出了应该让最大数字在翻转区间的后一位，初步得出了以下思路：

- 找到最大的数（$n$）所在位置 $r$，将 $r-1$；
- 贪心的寻找 $r-1$ 以前第一个比 $p_1$ 小的位置 $l$；
- 将 $l+1$；
- 输出区间。

#### 第一个细节

当然，这是有问题的，因为如果 $r=n$，则也有翻转区间 $[n,n]$ 的可能（参考第 $2$ 个样例）。

所以，当 $r=n$ 时，我们不进行 $r-1$ 这个操作。

#### 第二个细节

但这仍然有问题，如果 $r=1$ 时，翻转区间将是 $[l,0]$，这个操作是无效的，于是可以想一下，哪个排列开头在不是最大的数时字典序最大呢？

那只能以 $n-1$（次大的数）作为开头了。

我们就要寻找 $n-1$ 所在位置，再重复以上操作。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,p[2010];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		int l,r;
		for(int i=1;i<=n;i++){
			scanf("%d",&p[i]);
			if(p[i]==n) r=i;
		}
		if(r==1){
			for(int i=1;i<=n;i++){
				if(p[i]==n-1) r=i;
			}
		}
		if(r!=n) r--;
		l=r;
		for(int i=r-1;i>=1;i--){
			if(p[i]>p[1]) l--;
			else break;
		}
		for(int i=r+1;i<=n;i++) printf("%d ",p[i]);
		for(int i=r;i>=l;i--) printf("%d ",p[i]);
		for(int i=1;i<l;i++) printf("%d ",p[i]);
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：Coffee_zzz (赞：4)

### 分析

看到 $\sum n \le 2000$，直接思考 $O(n^2)$ 的做法。

要让 $p$ 的字典序尽可能大，我们考虑 $p$ 中的最大值 $p_{max}$。

- 若 $p_{max}$ 不为 $p$ 的第一项，则考虑将其通过操作移动到第一项。我们可以对 $[1,max-1],[2,max-1],\cdots,[max-1,max-1]$ 中的一个进行操作，这样 $p_{max}$ 就会被移动到 $p$ 的第一项。我们记录下这 $max-1$ 种方案的字典序，取最大值即可。需要注意，若 $p_{max}$ 为 $p$ 的最后一项即 $max=n$，对区间 $[max,max]$ 进行操作也可以使 $p_{max}$ 移动到 $p$ 的第一项。

- 若 $p_{max}$ 为 $p$ 的第一项即 $max=1$，则在进行一次操作后，$p_{max}$ 一定无法作为 $p$ 的第一项，因为会被移动到其他位置。那我们考虑让 $p$ 中第二大的元素 $p_{sec}$ 移动到 $p$ 的第一项，按照上面的方法移动 $p_{sec}$ 即可。

### 代码

```c++
#include <bits/stdc++.h>

using namespace std;
namespace IO{
	char ibuf[(1<<20)+1],*iS,*iT;
	#if ONLINE_JUDGE
	#define gh() (iS==iT?iT=(iS=ibuf)+fread(ibuf,1,(1<<20)+1,stdin),(iS==iT?EOF:*iS++):*iS++)
	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read(){
		reg char ch=gh();
		reg long long x=0;
		reg char t=0;
		while(ch<'0'||ch>'9')   t|=ch=='-',ch=gh();
		while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=gh();
		return t?-x:x;
	}
}
using IO::read;

const int N=2005;
int p[N],a[N],ans[N],n,ma;
void check(int l,int r){
	int cnt=0;
	for(int i=r+1;i<=n;i++) a[++cnt]=p[i];
	for(int i=r;i>=l;i--) a[++cnt]=p[i];
	for(int i=1;i<l;i++) a[++cnt]=p[i];
	for(int i=1;i<=n;i++){
		if(ans[i]>a[i]) return;
		if(ans[i]<a[i]){
			for(int i=1;i<=n;i++) ans[i]=a[i];
			return;
		}
	}
}
void solve(){
	n=read(),ma=0;
	for(int i=1;i<=n;i++) p[i]=read();
	for(int i=2;i<=n;i++) if(p[i]>p[ma]) ma=i;
	for(int i=1;i<ma;i++) check(i,ma-1);
	check(ma,ma);
	for(int i=1;i<=n;i++) cout<<ans[i]<<' ';
	cout<<endl;
	for(int i=1;i<=n;i++) ans[i]=0;
}
signed main(){
	int T=read();
	while(T--) solve();
	return 0;
}
```

---

## 作者：封禁用户 (赞：2)

## 分析

一道构造题。

为了使答案最大，我们就要先使最高位最大，所以我们的优先策略就是把除第一位以外的最大值和它后面的数字提前。

接下来我们就要分情况讨论：第一种，该最大值在最后一位，即后面没有多余的数字。这时候我们就可以找区间 $l,r$，从最大值的前面一个开始找。又因为最大值要么是 $r$，要么是 $r+1$，所以我们只需要将这个区间的每一位与第一位的数字进行比较，一旦小于第一位，就表明此时的区间不是最优的，即将现在的 $l-1$ 是最优的。第二种，该最大值不是最后一位。那么现在的区间的 $r$ 就只能是最大值的前一位了，所以那一位必须在区间内。但是，其他的我们就没有限制，和第一种情况一样找最优的即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n;
const int N=1e5+10;
int a[N];
signed main()
{
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		if(n==1) cout<<a[1]<<endl;
		else
		{
			int maxx=0;
			int maxid=0;
			for(int i=2;i<=n;i++)//找最大值
			{
				if(a[i]>maxx) maxx=a[i],maxid=i;
			}
			if(maxid==n)//情况1
			{
				cout<<a[maxid]<<" ";
				while(a[maxid-1]>a[1]) cout<<a[maxid-1]<<" ",maxid--;//因为我们从后往前找，所以这里翻转之后可以直接输出
				for(int i=1;i<maxid;i++) cout<<a[i]<<" ";//输出剩下的	
			}
			else//情况2
			{
				for(int i=maxid;i<=n;i++) cout<<a[i]<<" ";
				cout<<a[maxid-1]<<" ",maxid--;//右端点确定的值
				while(a[maxid-1]>a[1]) cout<<a[maxid-1]<<" ",maxid--;//同情况1
				for(int i=1;i<maxid;i++) cout<<a[i]<<" ";//输出剩下的
			}
			cout<<endl;			
		}
 
	}
}
```

---

## 作者：I_am_kunzi (赞：2)

# CF1833D 题解

### 题目大意

有 $ t $ 组测试数据，其中每组有以下的输入输出。

> 给定一个排列，选取 $ l , r$，并交换 $ [r + 1 , n] $ 和 $ [1 , l - 1]$，中间放上 $ [l , r] $ 的数倒序排列后的结果，现在求出交换后形成的字典序最大的数组排列。

其中，有 $ 1 \le t \le 10 ^ 3 , 1 \le n \le 2 \times 10 ^ 3 , 1 \le p_i \le n , \sum n \le 2 \times 10 ^ 3$。

### 题目分析

发现 $ n \le 2000$，于是先想 $ O(n ^ 2) $ 做法。我们不难发现，要想使字典序最大，就必然要使最大数在最前面，但是如果最大数本来就在第一位，则字典序最大的排列只能是让第二大数在最前面。

此时，我们可以确定 $ r $ 的值，这样即可使交换 $ [r + 1 , n] $ 和 $ [1 , l - 1] $ 时使最大数或第二大数排到最前的位置，此时有 $ r = x - 1$，其中 $ x $ 为最大或第二大数的位置；值得注意的是，当 $ x = n $ 时，则需对 $ [n , n] $ 区间进行操作，才能使最大值移动到最前方的位置；至于确定 $ l $ 的值，我们可以进行暴力枚举，一重循环枚举，一重循环计算，最后取字典序最大的即可。

### 代码时间

```cpp
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;
int a[2005];
int now[2005];
int ans[2005];
void pd(int l , int r , int n) //pd 函数用来计算 [l , r] 区间的操作结果，并存到 now 数组中，同时更新 ans 数组 
{
	int flag = 0; //now 数组中的下标位置，这里初始成 0，下面就要 ++flag，先自加再调用 
	for(int i = r + 1 ; i <= n ; i++) //交换 [r + 1 , n] 与 [1 , l - 1] 
	{
		now[++flag] = a[i];
	}
	for(int i = r ; i >= l ; i--) //中间加上倒着的 [l , r] 
	{
		now[++flag] = a[i];
	}
	for(int i = 1 ; i <= l - 1 ; i++) //交换 [r + 1 , n] 与 [1 , l - 1] 
	{
		now[++flag] = a[i];
	}
	for(int i = 1 ; i <= n ; i++)
	{
		if(ans[i] < now[i]) // ans 的靠前位更小。则字典序更小，进行交换操作并返回 
		{
			for(int i = 1 ; i <= n ; i++)
			{
				ans[i] = now[i];
			}
			return ;
		}
		if(ans[i] > now[i]) //ans 的靠前位更大，则字典序更大，不需要继续比较了，直接返回 
		{
			return ;
		}
	}
	return ;
}
signed main()
{
	int t;
	cin >> t;
	while(t--)
	{
		memset(now , 0 , sizeof(now)); //memset 初始化操作 
		memset(ans , 0 , sizeof(ans));
		memset(a , 0 , sizeof(a));
		int n , maxwz = 0; //maxwz 存储最大值或第二大值的位置 
		cin >> n;
		for(int i = 1 ; i <= n ; i++)
		{
			cin >> a[i];
			if(i != 1) //不是首位，那么就更新 maxwz 
			{
				maxwz = (a[i] > a[maxwz] ? i : maxwz);
			}
		}
		for(int i = 1 ; i < maxwz ; i++) //判断 [i , maxwz - 1] 区间，并更新最大值 
		{
			pd(i , maxwz - 1 , n);
		}
		pd(maxwz , maxwz , n); //判断 [maxwz , maxwz] 区间，并更新最大值 
		for(int i = 1 ; i <= n ; i++)
		{
			cout << ans[i] << ' ';
		}
		cout << endl;
	}
    return 0;
}
```

---

## 作者：Scorilon (赞：2)

赛场上思路出来了但是代码没调出来。

首先考虑右端点，很明显，要让操作后的序列字典序尽量地大，那么就要使操作后的序列第一个数尽量地大，考虑 $n$ 或 $n-1$，如果 $n$ 在原序列的第一个位置，那么此时无论怎么调整都无法使得它在新序列的第一个位置，此时就要考虑让 $n-1$ 在新序列的第一个位置，和 $n$ 不在原序列的第一个位置类似，我们只要找到在原序列中的位置，然后 $r$ 取这个位置的前一个即可。很明显，如果该数在原序列的末尾，那么 $r$ 就应是 $n$.

概述着说，就是右端点要找到 $[2,n]$ 中最大的数，若在末尾，则 $r=n$，反之 $r$ 为最大数的前一个数。

接着考虑左端点，我们可以将新序列写成如下形式 $r+1 \dots n \dots r \dots l \dots 1 \dots l-1$，那么可以发现，当我们确定了右端点时，$r+1\dots n$ 这一段就是确定了的，接下来就是要让 $r \dots l \dots 1 \dots l-1$ 这一段尽量的大。因此我们首先要考虑让 $l$ 尽量地大，那么很明显，若存在 $a_i>a_{l-i}$，那么此时 $l$ 取 $i$ 会是更优解。可以画图理解。

时间复杂度将近 $O(n)$，通过本题绰绰有余。

```cpp
#include <cstdio>
#include <iostream>

using namespace std;

int t;
int n;
int a[2005];

int main() {
	scanf("%d",&t);
	while(t--) {
		scanf("%d",&n);
		int opt=0;
		for(int i=1;i<=n;i++) {
			scanf("%d",&a[i]);
			if(i>1&&a[i]>a[opt]) opt=i;//寻找[2,n]中最大数所在位置
		}
		if(n==1) {
			printf("%d\n",a[1]);
			continue;
		}
		int l=opt-1;
		int r=opt-1;//确定右端点
		if(opt==n) l=opt,r=opt;//同上
		for(int i=r-1;i>=1;i--) {//寻找最优左端点
			if(a[i]>=a[l-i]) l=i;
			else break;
		}
		for(int i=r+1;i<=n;i++) printf("%d ",a[i]);
		for(int i=r;i>=l;i--) printf("%d ",a[i]);
		for(int i=1;i<=l-1;i++) printf("%d ",a[i]);
		printf("\n");
	}
	return 0;
}
```

---

## 作者：sto_5k_orz (赞：1)

首先，新的序列是

$[r+1,n]+[r,l]+[1,l-1]$

$r$ 肯定在 $n$ 的位置的前一个，这样第一个元素就是 $n$。

但是有可能 $n$ 在第一个元素，那么 $r$ 就是在 $n$ 的位置的前一个。

剩下的就是枚举 $l$，暴力求下来所有排列。

可以考虑用结构体存储下排列，重载运算符，然后用 `set` 进行比较大小即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define I inline
#define W while
#define gc getchar
#define pc putchar
#define int long long
namespace SlowIO {
	I int read() {
		int x = 0, f = 1; char ch = gc();
		W(ch < '0' || ch > '9') {if(ch == '-') f = -f; ch = gc();}
		W(ch >= '0' && ch <= '9') x = x * 10 + (ch ^ 48), ch = gc();
		return x * f;
	}
	I void Read(int &x) {x = read();}
	I void Read(int &x, int &y) {Read(x), Read(y);}
	I void write(int x) {
		if(x < 0) pc('-'), x = -x;
		if(x > 9) write(x / 10);
		pc(x % 10 + '0');
	}
	I void writeln(int x) {write(x); pc('\n');}
	I void Write(int x) {write(x); pc(' ');}
} using namespace SlowIO;
const int N = 2010; int n; int a[N];
struct per {
	int p[N];
	bool operator < (const per &cmp) const {
		for(int i = 1; i <= n; i++) {
			if(p[i] < cmp.p[i]) return 1;
			if(p[i] > cmp.p[i]) return 0;
		}
	}
};
per get(int l, int r) { per ans; int t = 0;
	for(int i = r + 1; i <= n; i++) ans.p[++t] = a[i];
	for(int i = r; i >= l; i--) ans.p[++t] = a[i];
	for(int i = 1; i < l; i++) ans.p[++t] = a[i];
//	printf("test l = %d, r = %d\n", l, r);
//	for(int i = 1; i <= t; i++) Write(ans.p[i]); pc('\n');
	return ans;
}
set<per> st;
signed main() {
	int t; Read(t); W(t--) { st.clear();
		Read(n); int pos = 0; for(int i = 1; i <= n; i++) {Read(a[i]); if(a[i] == n) pos = i - 1;}
		if(pos == 0) {for(int i = 1; i <= n; i++) if(a[i] == n - 1) pos = i - 1;}
		
		st.insert(get(pos + 1, pos + 1)); for(int l = 1; l <= pos; l++) st.insert(get(l, pos));
		per ans = *(--st.end()); for(int i = 1; i <= n; i++) Write(ans.p[i]); pc('\n');
	}
	return 0;
}
```

---

## 作者：__Dist__ (赞：0)

### 题目描述

[原题](https://www.luogu.com.cn/problem/CF1833D)

### 思路讲解

数据范围较小，考虑暴力求解。

仔细观察数据，略微思考，可以得到规律：要想使字典序最大，就得让最大的数在最前面。但如果第一个数就是最大的，那我们只能让第二大的值在最前面。我们设打头的数为 $ k $。

由上面的规律我们可以得到 $ r $ 的值，从而交换 $ [r+1 , n] $ 和 $ [1,l-1] $ 这两个区间（必然会出现 $ r=k-1 $）。还有一个细节，就是 $ k=n $ 时，需要操作 $ [n,n] $ 这个区间，才能达到目的。

暴力的对象就是 $ l $。我们设计一个函数进行交换操作，暴力 $ l $ 的位置，进行计算，找到字典序最大的方案。

### 代码环节

```cpp
#include<iostream>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<iomanip>
#include<cstdio>
#include<stack>
#include<queue>
#include<map>
#include<vector>
using namespace std;
int a[10005];
int p[10005];//暂时储存
int ans[10005];
int n,T;
void check(int l,int r){
	for(int i=r+1;i<=n;i++) p[++p[0]]=a[i];//[r+1,n]区间
	for(int i=r;i>=l;i--) p[++p[0]]=a[i];//倒着的[l,r]区间
	for(int i=1;i<l;i++) p[++p[0]]=a[i];//[1,l-1]区间
	for(int i=1;i<=n;i++){//更新ans
		if(ans[i]<p[i]){//若ans字典序小了
			for(int i=1;i<=n;i++) ans[i]=p[i];
			return ;//直接结束
		}
		if(ans[i]>p[i])//ans字典序更大
			return;//结束比较
	}
}
int main(){
	cin>>T;
	while(T--){
		cin>>n;
		memset(a,0,sizeof a);
		memset(p,0,sizeof p);
		memset(ans,0,sizeof ans);//清空
		int k=0;//最大/第二大值的位置
		cin>>a[1];
		for(int i=2;i<=n;i++){
			cin>>a[i];
			if(a[i]>a[k]) k=i;
		}
		for(int i=1;i<k;i++){
			check(i,k-1);//枚举l并更新ans
		}
		check(k,k);//特判
		for(int i=1;i<=n;i++) cout<<ans[i]<<' ';
		puts("");
	}
	return 0;
}
```


---

## 作者：Light_az (赞：0)


# 题意

对于一个数列，我们定义一种操作：

选择一个区间 $[l,r]$，将该区间的数进行翻转操作。

然后将区间 $[1,l-1]$ 和 $[r+1,n]$ 的数交换。

现在问操作一次后能够得到最大的字典序的数列是什么？

# 分析

考虑暴力代码，每次枚举 $[l,r]$ 区间，与最优解进行比较得到最大字典序的数列。

可以得到 $O(n^2)$ 的暴力代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define F(i,j,n) for(int i=j;i<=n;i++)
#define B(i,j,n) for(int i=j;i>=n;i--)
#define Tr(v,e) for(int v:e)
#define D double
#define ps push_back
#define Test ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr)
using namespace std;
const int N=1e6+10,NN=1e4+10;
ll n,m,k,x,y,u,v,w,cnt=0,t=0,l,r,len,T;
ll mn=INT_MAX,mx=0,Mod,id=1;
string s1,s2;
ll a[N],b[N],ans[N];
void copy(){
	F(i,1,n) ans[i]=b[i];
}
bool check(){
	F(i,1,n){
		if(b[i]<ans[i]) return 0;
		if(b[i]>ans[i]) return 1;
	} 
	return 1;
}
void make(ll l,ll r){
	ll t=0;
	F(i,r+1,n) b[++t]=a[i];
	B(i,r,l) b[++t]=a[i];
	F(i,1,l-1) b[++t]=a[i];
	if(check()) copy();
}
int main(){
	Test;
	cin>>T;
	while(T--){
		cin>>n;
		F(i,1,n) cin>>a[i],ans[i]=0;
		F(l,1,n) F(r,l,n){
			make(l,r);
		} 
		F(i,1,n) cout<<ans[i]<<" ";
		cout<<"\n";
	}
 
	return 0;
}
```

然后继续考虑优化，得到一下结论：

- 记数列中最大值的编号是 $i$，当 $i \ne 1$ 时，交换操作一定在 $i-1$ 或 $i$ 或 $i+1$ 上。

因为字典序最大的第一位一定是最大值，因此每次交换一定和最大值的位置有关。

在暴力的基础上对区间 $[l,r]$ 进行特判，保证交换后最大值一定在第一位，得到一下代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define F(i,j,n) for(int i=j;i<=n;i++)
#define B(i,j,n) for(int i=j;i>=n;i--)
#define Tr(v,e) for(int v:e)
#define D double
#define ps push_back
#define Test ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr)
using namespace std;
const int N=1e6+10,NN=1e4+10;
ll n,m,k,x,y,u,v,w,cnt=0,t=0,l,r,len,T;
ll mn=INT_MAX,mx=0,Mod,id=1;
string s1,s2;
ll a[N],b[N],ans[N];
void copy(){
	F(i,1,n) ans[i]=b[i];
}
bool check(){
	F(i,1,n){
		if(b[i]<ans[i]) return 0;
		if(b[i]>ans[i]) return 1;
	} 
	return 1;
}
void make(ll l,ll r){
	ll t=0;
	F(i,r+1,n) b[++t]=a[i];
	B(i,r,l) b[++t]=a[i];
	F(i,1,l-1) b[++t]=a[i];
	if(check()) copy();
}
int main(){
	Test;
	cin>>T;
	while(T--){
		mx=0;
		cin>>n;
		F(i,1,n){
			cin>>a[i],ans[i]=0;
			if(a[i]>mx) mx=a[i],id=i;
		} 
		F(l,1,n) F(r,l,n){
			if(id!=1&&abs(l-id)>1&&abs(r-id)>1) continue;// 不在 i-1,i,i+1 上
			if(l>1&&r<n&&a[l-1]>a[r+1]) continue;// 交换后字典序更小
			make(l,r);//暴力
		} 
		F(i,1,n) cout<<ans[i]<<" ";
		cout<<"\n";
	}
 
	return 0;
}
```


---

## 作者：Furina_Hate_Comma (赞：0)

一道思维题。

首先，为了让字典序最大，我们要让开头最大。

于是选择的区间右端点在最大值之前。

那么接下来我们考虑模拟一下结果。

原序列：$2\ 3\ 1\ 5\ 4$。

左端点定为 $1$。

则枚举左端点有下可能：

$5\ 4\ 1\ 2\ 3$

$5\ 4\ 1\ 3\ 2$

不难发现如果当前左端点大于第一个数，则左端点可以扩大 $1$。

注意如果最大值在首位，要换成次大值。

code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[500000];
int find_max(int l,int r){
	int mi,ma=-1;
	for(int i=l;i<=r;i++){
		if(a[i]>ma){
			ma=a[i];
			mi=i;
		}
	}
	return mi;
}
signed main()
{
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		int k1=find_max(1,n);
		if(n==1){
			cout<<1<<'\n';
			continue;
		}
		if(k1==1)
			k1=find_max(2,n);
		if(k1==n){
			if(a[1]>a[n-1]){
				cout<<a[n]<<' ';
				for(int i=1;i<n;i++)cout<<a[i]<<' ';
				cout<<endl;
				continue;
			}
		}
		for(int i=k1;i<=n;i++)cout<<a[i]<<' ';
		int k2=k1-2;k1--;
		while(a[k2]>=a[1])k2--;
		for(int i=k1;i>k2;i--)cout<<a[i]<<' ';
		for(int i=1;i<=k2;i++)cout<<a[i]<<' ';
		cout<<endl;
	}
    return 0;
}
```

---

