# [ABC165C] Many Requirements

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc165/tasks/abc165_c

正整数 $ N $ , $ M $ , $ Q $ と、$ 4 $ つの整数の組 ( $ a_i $ , $ b_i $ , $ c_i $ , $ d_i $ ) $ Q $ 組が与えられます。

以下の条件を満たす数列 $ A $ を考えます。

- $ A $ は、長さ $ N $ の正整数列である。
- $ 1\ \leq\ A_1\ \leq\ A_2\ \le\ \cdots\ \leq\ A_N\ \leq\ M $

この数列の得点を、以下のように定めます。

- $ A_{b_i}\ -\ A_{a_i}\ =\ c_i $ を満たすような $ i $ についての、 $ d_i $ の総和 (そのような $ i $ が存在しないときは $ 0 $)

$ A $ の得点の最大値を求めてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 2\ <\ =\ N\ <\ =\ 10 $
- $ 1\ \leq\ M\ \leq\ 10 $
- $ 1\ \leq\ Q\ \leq\ 50 $
- $ 1\ \leq\ a_i\ <\ b_i\ \leq\ N $ ( $ i\ =\ 1,\ 2,\ ...,\ Q $ )
- $ 0\ \leq\ c_i\ \leq\ M\ -\ 1 $ ( $ i\ =\ 1,\ 2,\ ...,\ Q $ )
- $ (a_i,\ b_i,\ c_i)\ \neq\ (a_j,\ b_j,\ c_j) $ ( $ i\ \neq\ j $ のとき)
- $ 1\ \leq\ d_i\ \leq\ 10^5 $ ( $ i\ =\ 1,\ 2,\ ...,\ Q $ )

### Sample Explanation 1

$ A\ =\ \{1,\ 3,\ 4\} $ のとき、この数列の得点は $ 110 $ となります。この条件の下では $ 110 $ より高い得点を持つ数列は存在しませんから、答えは $ 110 $ です。

## 样例 #1

### 输入

```
3 4 3
1 3 3 100
1 2 2 10
2 3 2 10```

### 输出

```
110```

## 样例 #2

### 输入

```
4 6 10
2 4 1 86568
1 4 0 90629
2 3 0 90310
3 4 1 29211
3 4 3 78537
3 4 2 8580
1 2 1 96263
1 4 2 2156
1 2 0 94325
1 4 3 94328```

### 输出

```
357500```

## 样例 #3

### 输入

```
10 10 1
1 10 9 1```

### 输出

```
1```

# 题解

## 作者：flysfy_LJX (赞：10)

dfs 一遍扫过。
 
用 dfs 枚举出数列 $A$ 中的每一个数，由题意可知数列 $A$ 是递增的，所以每次从数列 $A$ 的前一个数的值开始枚举，枚举完成后求这个数列的值与当前数列的最大值作比较，最后输出最大值就行。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,q,a[55][55],ans[15],maxx=-1;
void dfs(int step)//深度优先搜索 
{
	if(step==n+1)//如果数列为满 
	{
		int sum=0;
		for(int i=1;i<=q;i++)
			if(ans[a[i][2]]-ans[a[i][1]]==a[i][3]) sum+=a[i][4]; //枚举得分 
		maxx=max(maxx,sum);//如果枚举的分数比最大的分数高,那么更新最大值 
		return;
	}
	for(int i=ans[step-1];i<=m;i++)//ans[step-1]保证数组为递增 
	{
		ans[step]=i;
		dfs(step+1);
		ans[step]=0;//回溯 
	}
}
int main()
{
	cin >> n >> m >> q;
	for(int i=1;i<=q;i++)
		cin >> a[i][1] >> a[i][2] >> a[i][3] >> a[i][4];
	ans[0]=1;//因为数列大于等于1，所以将ans[0]赋值为1 
	dfs(1);
	cout << maxx;
	return 0;
}
```


---

## 作者：YuTianQwQ (赞：8)

# 题目解析

这段代码的目标是找到一种特能赚取最高分数的序列。这个问题可以被视作一个深度优先搜索（DFS）问题。

## 解题思路

1. **读取输入**：首先，我们需要读取 $N$ $M$ 和 $Q$ 的值，然后读取每一条规则 $(a, b, c, d)$。注意，因为在 C++ 中，数组的索引是从 $0$ 开始的，所以我们需要将规则中的 $a$ 和 $b$ 的值减 $1$。

    ```cpp
    cin >> N >> M >> Q;
    for(int i = 0;i < Q;i++)
    {
        cin >> a[i] >> b[i] >> c[i] >> d[i];
        a[i]--;
        b[i]--;
    }
    ```

2. **深度优先搜索**：使用 `dfs(0,1)` 开始深度优先搜索。在 `dfs(int n, int m)` 函数中，`n` 是我们当前要设置的序列的位置，`m` 是这个位置可以选择的最小值。

    ```cpp
    dfs(0,1);
    ```

3. **计算得分**：当 $n$ 等于 $N$ 时，序列设置完成，此时我们需要计算得分并更新答案。得分计算方式是遍历所有的规则，如果满足某条规则（即序列中位置 $b$ 的元素与位置 $a$ 的元素的差等于 $c$），则得分增加 $d$。

    ```cpp
    if(n == N)
    {
        int tmp = 0;
        for(int i = 0;i < Q;i++)
        {
            if(A[b[i]] - A[a[i]] == c[i]) tmp += d[i];
        }
        ans = max(ans, tmp);
        return;
    }
    ```

4. **递归探索序列**：如果序列还未设置完成，我们就在当前位置尝试所有可能的值，并递归地对下一个位置进行同样的操作。

    ```cpp
    for(int i = m;i <= M;i++)
    {
        A[n] = i;
        dfs(n + 1, i);
    }
    ```

5. **输出结果**：完成所有可能的搜索后，输出最大得分。

    ```cpp
    cout << ans << endl;
    ```
总的来说，我们通过深度优先搜索在所有可能的序列中寻找得分最高的序列。首先尝试所有可能的值，然后递归地深入下一个位置。当一个序列完成时，我们会检查每个规则并计算得分，如果得分比当前最高得分高，我们就更新最高得分。

# ACcode:
```c++
#include <bits/stdc++.h>
using namespace std;

int N,M,Q;
int a[50],b[50],c[50],d[50];
int A[10];
int ans;

void dfs(int n,int m)
{
    if(n == N)
    {
        int tmp = 0;
        for(int i = 0;i < Q;i++)
        {
            if(A[b[i]] - A[a[i]] == c[i]) tmp += d[i];
        }
        ans = max(ans, tmp);
        return;
    }
    for(int i = m;i <= M;i++)
    {
        A[n] = i;
        dfs(n + 1, i);
    }
}

int main()
{
    cin >> N >> M >> Q;
    for(int i = 0;i < Q;i++)
    {
        cin >> a[i] >> b[i] >> c[i] >> d[i];
        a[i]--;
        b[i]--;
    }
    dfs(0, 1);
    cout << ans << endl;
    return 0;
}
```

---

## 作者：Sirkey (赞：8)

突破口在于 $n$ 和 $m$ 的取值范围。

这俩玩意小的可怜。

我们用 dfs 的方法直接构造一个序列，然后再去和每一个条件判断，加分，最后得到最大值。

重点在 dfs 的部分。$n$ 和 $m$ 的取值小，我们直接通过这两个值枚举方案。

在 dfs 中，可以理解为，一个表示第几个，另一个则是放到了几，因为整个序列递增，所以时间复杂度很小。

其他就是代码实现了：

```
#include<bits/stdc++.h>
#define ll long long
#define FOR(i,a,b) for(ll i=(a); i<=(b); ++i)
#define ROF(i,a,b) for(ll i=(a); i>=(b); --i)
#define tell(ans) out(ans),printf("\n");
#define say(ans) out(ans),printf(" ");
#define pb push_back
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
ll n,m,q,ans,a[10005],b[10005],c[10005],d[10005],tmp[100];
void dfs(int p,int s){
	tmp[p]=s;
	if(p==n){
		ll sum=0;
		FOR(i,1,q)
			if(tmp[b[i]]-tmp[a[i]]==c[i])sum+=d[i];
		ans=max(sum,ans);
		return ;
	}
	FOR(i,s,m)
		dfs(p+1,i);
	return;
}
int main() {
	n=read(),m=read(),q=read();
	FOR(i,1,q) 	a[i]=read(),b[i]=read(),c[i]=read(),d[i]=read();
	dfs(1,1); 
	cout<<ans;
    return 0;
}


```

——end——


---

## 作者：_Above_the_clouds_ (赞：6)

# 思路：
找出一个序列，使得分最高。

直接全排列，每次枚举第 $k+1$ 项的数，为了让序列从小到排列，$s_{k+1}$ 的范围就是 $s_k\sim m$。当枚举了 $n$ 个数时，计算得分，用 $ans$ 记录最大得分，最后输出即可。

# 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,q;
long long sum,ans;
int a[55],b[55],c[55],d[55],s[55];
void dfs(int k){
	if(k>n){
		sum=0; 
		for(int i=1;i<=q;i++)
			if(s[b[i]]-s[a[i]]==c[i]) sum+=d[i]; 
		ans=max(ans,sum);
		return ;
	}
	for(int i=s[k];i<=m;i++){
		s[k+1]=i;
		dfs(k+1);
	}
}
int main(){
	cin>>n>>m>>q;
	for(int i=1;i<=q;i++) cin>>a[i]>>b[i]>>c[i]>>d[i];
	s[1]=1;
	dfs(1);
	cout<<ans;
	return 0;
}

```


---

## 作者：whx2009 (赞：6)

## 本题思路：
这道题看似十分复杂，但我们可以发现他的数据范围并不是很大，那么我们就可以用 dfs 去暴力搜索 $A$ 数组中的每一个数是多少，然后根据题目加分规则算出得分，最后选出最大的即可。
## 本题代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[51],b[51],c[51],d[51],ans[51];
int ans2,n,m,q;
void dfs(int vis,int sum)
{
	if(vis>n)
	{
		int ans1=0; 
		for(int i=1;i<=q;i++)
		{
			if(abs(ans[a[i]]-ans[b[i]])==c[i]) 
			 ans1+=d[i];
		}
		ans2=max(ans2,ans1);
		return;
	}
	for(int i=sum;i<=m;i++)
	{
		ans[vis]=i;
		dfs(vis+1,i);
	}
}
int main()
{
	cin>>n>>m>>q;
	for(int i=1;i<=q;i++)
	{
		cin>>a[i]>>b[i]>>c[i]>>d[i];
	}
	dfs(1,1);
	cout<<ans2;
	return 0;
}
```


---

## 作者：Mysterious_Cat (赞：5)

## 水一篇题解
### A）题目大意：构造一个$N$项的数列$A$，保证$A_i <= A_{i+1}$，最大项$A_N$不超过$M$，一共有$Q$组要求$a_i$，$b_i$，$c_i$，$d_i$, 若满足代数式$A_{a_i} - A_{b_i} = c_i$，则$A$获得$d_i$点分，要求求出满足条件的序列的最大得分（$N <= 10$，$M <= 10$，$Q <= 50$)
### B）题目思路：因为数据很小，时间复杂度最坏$N$ * $M! = 36288000  <= 2e9$，所以直接枚举所有情况取最大值，使用DFS即可，注意是$A_i <= A_{i+1}$而非$A_i < A_{i+1}$
### 总体来说题目较为简单，读懂题意，想到DFS差不多就做完了，代码比较容易敲(~~水题~~)
# Code:
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;

int n, m, ans = 0, a[55], b[55], c[55], d[55], A[15];

void dfs(int x)
{
	if(x > n)
	{
		int res = 0;
		for(int i = 1; i <= q; i++)
			if(A[b[i]] - A[a[i]] == c[i]) res += d[i];
		ans = max(ans, res);
		return;
	}
	for(int i = A[x - 1]; i <= m; i++)
	{
		A[x] = i;
		dfs(x + 1);
		A[x] = 0;
	}
}

int main()
{
	scanf("%d %d %d", &n, &m, &q);
	for(int i = 1; i <= q; i++)
		scanf("%d %d %d %d", &a[i], &b[i], &c[i], &d[i]);
	A[0] = 1;	
	dfs(1);
	printf("%d", ans);

	return 0;
}
```


---

## 作者：_GW_ (赞：4)

## 思路

看到题的第一眼：什么鬼，这怎么做？

看到数据范围：哇，$dfs$！

做法：$dfs$ 进行到第 $i$ 层时，枚举 $A_i$ 选哪个数，选完第 $n$ 个数时再计算出得分。

让我先算算时间复杂度……

$10!\times50=18140000$，还有两秒，不需要剪枝！~~巨佬想加也行。~~

注意！数组要开到 $50$！~~也只有本蒟蒻才会犯了。~~

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=12,M=55;
int n,m,k,sum,q,res[M],num[M],ans=-1e9;
struct node{int a,b,c,d;}a[M];
bool vis[M];
void dfs(int now)
{
    if(now>n)
    {
        int val=0;
        for(int i=1;i<=q;i++)
        {
            if(res[a[i].b]-res[a[i].a]==a[i].c) val+=a[i].d;//算出此种选法的得分。 
        }
        ans=max(ans,val);//更新答案。 
        return;
    }
    for(int i=max(res[now-1],1);i<=m;i++)
    {
        res[now]=i;
        dfs(now+1);//dfs好闪，拜谢dfs！ 
    }
}
int main()
{
    cin>>n>>m>>q;
    for(int i=1;i<=q;i++) cin>>a[i].a>>a[i].b>>a[i].c>>a[i].d;//输入。 
    dfs(1);//调用大法师。 
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：Kobe_BeanBryant (赞：4)

## [题目传送门](https://www.luogu.com.cn/problem/AT_abc165_c)
### 题目大意：
给出 $ n $，$ m $，$ q $ 这三个整数，要让你构造出数组 $ a $，让数组中有 $ n $ 个元素满足条件。
### 条件：
1. 数组 $ a $ 满足所有的元素的值大于等于 $ 1 $。
2. 一个数列 $ a $ 会有一个得分，且满足 $ a_{b_i} - a_{a_i} = c_i $。

求：满足条件的 $ i $ 的 $ d_i $ 的和。
### 解题思路：
本题的数据范围并不大，所以我们可以放心的用深度优先搜索。

**深度优先搜索：**

从 $ 1 $ 到 $ q $ 之间找到满足条件二的 $ i $ 并把 $ d_i $ 累加，然后找出最大的值返回。

**主程序：**

套用函数中已经求出的最大值，输出这个最大值。
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,q,k;
long long a[55],b[55],c[55],d[55];
long long l[55];
void dfs(int x,int y){
	if(x>n){
		int ans=0;
		for(int i=1;i<=q;i++)
			if(abs(l[a[i]]-l[b[i]])==c[i])
				ans+=d[i];//找出满足条件的i，并将d[i]累加起来
		if(ans>k) k=ans;//找出最大值
		return;//返回
	}
	for(int i=y;i<=m;i++)
		l[x]=i,dfs(x+1,i);//回溯
}
int main(){
	scanf("%lld%lld%lld",&n,&m,&q);
	for(int i=1;i<=q;i++)
		scanf("%lld%lld%lld%lld",&a[i],&b[i],&c[i],&d[i]);
	dfs(1,1);//套用函数，求k满足条件的最大值
	printf("%lld\n",k);//输出k
	return 0;
}
```

---

## 作者：钓鱼王子 (赞：2)

构造一个长为 $n$ 的序列，使得 $a_i\leq a_{i+1},a_i\geq 1,a_n\leq m$。同时有 $q$ 个限制，满足相应的限制即可得到相应的得分

数据范围 $n,m\leq 10,q\leq 50$。

看到这个数据范围就想到爆搜，复杂度即为 $C_{n+m}^m\times q$（隔板法）$=$ $
O($能过$)$。

具体操作就是求出合法序列之后计算得分找最大值即可。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int n,m,q,ans,a[52],b[52],c[52],d[52],f[52];
inline void dfs(re int x){
	if(x>n){
		re int sum=0;
		for(re int i=1;i<=q;++i){
			if(f[b[i]]-f[a[i]]==c[i])sum+=d[i];
		}
		ans=max(ans,sum);
		return;
	}
	for(re int i=f[x-1];i<=m;++i){
		f[x]=i;
		dfs(x+1);
	}
}
signed main(){
	n=read(),m=read(),q=read();
	for(re int i=1;i<=q;++i){
		a[i]=read();
		b[i]=read();
		c[i]=read();
		d[i]=read();
	}
	f[0]=1;
	dfs(1);
	printf("%d",ans);
}

```


---

## 作者：_jimmywang_ (赞：1)

题意：

给定$q$个四元组$(a_i,b_i,c_i,d_i)$。

一个合法序列定义为：有$n$个数$x_1,x_2,…… x_n$，且任意$x_i$大于0且不大于$m$，并且$x_1 \leq x_2 \leq x_3 \leq …… \leq x_n$

一个合法序列的得分：对于任意$1 \leq k \leq q$,若$x[b_k]-x[a_k]=c_k$,则得分加上$d_k$

求序列的最大得分是多少。

做法：

我们发现，$n \leq 10,m \leq 10$

所以，最多也就是$10!$种序列（还不到，因为要从小到大）

于是，打一个类似全排列的东西，枚举每个序列，算每个序列的得分，求最大就行了

代码：

```
#include<bits/stdc++.h> 
using namespace std;
#define ll long long
#define f(i,a,b) for(int i=a;i<=b;i++)
inline ll read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
#define d read()
ll n,m,q,ans;
ll a[55],b[55],c[55],dd[55];
ll sq[15];
void dfs(ll u,ll st){
	if(u==n+1){
		ll k=0;
		f(i,1,q)if(sq[b[i]]-sq[a[i]]==c[i])k+=dd[i];
		ans=max(ans,k);
		return;
	}
	f(i,st,m)sq[u]=i,dfs(u+1,i);
}
int main(){
	n=d,m=d,q=d;
	f(i,1,q)a[i]=d,b[i]=d,c[i]=d,dd[i]=d;
	dfs(1,1);
	cout<<ans;
	return 0;
}
```


---

## 作者：watcher_YBH (赞：1)

# 思路：
[[题目]](https://www.luogu.com.cn/problem/AT_abc165_c)

由于这道题的数据范围不大（$2 \leq N \leq 10,1 \leq M \leq 10$），我们可以直接深搜，每次按从小到大的枚举出 $N$ 个不超过 $M$ 的数，再求出这种情况的分数，最后比较出最大值。
# 代码：
```
#include<bits/stdc++.h>
#define ll long long
#define max(a,b) ((a>b)?a:b)
#define min(a,b) ((a<b)?a:b)
using namespace std;
const int MAX = 1e5+5;
int n,m,q,ans;
int a[MAX],b[MAX],c[MAX],d[MAX],A[MAX]; 
void dfs(int x,int k){
	if(k > n){//有了n个数
		int z = 0;
		for(int i = 1; i<=q; i++)//求出分数
			if(A[b[i]]-A[a[i]] == c[i]) z+=d[i];
		ans = max(ans,z);//记录最大值
		return;
	}
	for(int i = x; i<=m; i++)
		A[k] = i,dfs(i,k+1);
}
int main(){
	cin>>n>>m>>q;
	for(int i = 1; i<=q; i++){
		cin>>a[i]>>b[i]>>c[i]>>d[i];
	}
	dfs(1,1);//深搜
	cout<<ans;//输出最大值
	return 0;
}

```


---

## 作者：PikachuQAQ (赞：1)

## Description

[Link](https://www.luogu.com.cn/problem/AT_abc165_c)


## Solution

虽然一眼繁琐，但作为惯例还是要看数据范围。

$$2 \leq n \leq 10,1 \leq m \leq 10$$

这不直接模拟爆搜？

在本题解中，令构造出的数列为 $a$，则对于 $a$ 的 $1$ 到 $n$ 位，顺序枚举 $1$ 到 $m$，如果符合要求直接记录答案取最大值。

当然，上述做法的时间复杂度为 $O(n^m)$，一定会超时。

那么我们再来观察一下题面：

$$1 \leq a_1 \leq a_2 \leq \cdots \leq a_n \leq m$$

那么，可以记录每一位选取的最大值为 $p$，下一位枚举就可以从 $p$ 开始，枚举到 $m$，满足题面要求。

时间复杂度 $O(nm!)$，可以通过本题。

## Code

```cpp
// 2023/5/25 Accept__

#include <iostream>

typedef long long ll;

using namespace std;

const int kMaxN = 57;

struct A {
	ll a, b, c, d;
} b[kMaxN];

ll n, m, q, a[kMaxN], ans, k;

inline ll max(ll x, ll y) {
	return (x > y) ? x : y;
}

void dfs(ll r, ll p) {
    if (r == n + 1) {
		for (int i = 1; i <= q; i++) {
			(a[b[i].b] - a[b[i].a] == b[i].c) && (k += b[i].d);
		}
        ans = max(k, ans), k = 0;
        return;
    }
	for (int i = p; i <= m; i++) {
		a[r] = i, dfs(r + 1, i);
	}
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m >> q;
	for (int i = 1; i <= q; i++) {
		cin >> b[i].a >> b[i].b >> b[i].c >> b[i].d;
	}
	dfs(1, 1), cout << ans << '\n';

	return 0;
}
```


---

## 作者：__HHX__ (赞：1)

# 题目大意
保证 $ 1 \le A_i \le A_{i+1}$ 构造一个序列 $A$ 使有效的 $d_i$ 和最大。

在 $A_{b_i}-A_{a_i}=c_i$ 时 $d_i$ 有效。
# 思路
## 思路推导
本人第一眼就看到数据中的 $2 \le N \le 10,1 \le M \le 10$ 。

我去,这不是我们可爱 DFS 吗？

第二眼突然发现时间复杂度 $O(10^{10})$ 。

可是别忘了时限给了我们 $2.00s$ 我们只需用我们的 DFS 就可以了。

## 限定条件
DFS 的基本框架是这样的
```cpp
void dfs(/*这里填你的参数*/){
	if(/*满足条件*/)
	{
		ans=max(ans,check());//答案判断取最大 
	}
	for(int i=st;i<=en;i++)
	{
		//状态变换 
		dfs(/*这里填你的参数*/);
		//状态还原 
	} 
}
```

此时我们只需确定 $st$ 和 $en$ 就可以了。

我们此时看到：

让你构造一个长度为 $N$ 的数列 $A$ 满足 $1 \le A_1 \le A_2 \le \dots \le A_N \le M$ 。

此时我们就确定了 $st=A_{i-1} , en=M , A_0=1$ 。

## 答案判断
至于答案判断参考文章中:

对于一个数列 $A$ 会有一个得分，是满足 $A_{b_i}-A_{a_i}=c_i$ 的 $i$ 的 $d_i$ 的和。

# 代码实现
```cpp
#include<iostream>
#include<cmath>
using namespace std;

const int MaxN=13,MaxQ=55;
int n,m,q,Max=-1;
int A[MaxN],a[MaxQ],b[MaxQ],c[MaxQ],d[MaxQ];
void dfs(int u){//u是当前位置 
	if(u>n)//不需要向上枚举了 
	{
		
		int sum=0;
		for(int i=1;i<=q;i++)
		{
			if(A[b[i]]-A[a[i]]==c[i])//答案判断 
			{
				sum+=d[i];
			}
		}
		Max=max(Max,sum);//求最大 
		return;
	}
	for(int i=A[u-1];i<=m;i++)
	{
		A[u]=i;//状态变化 
		dfs(u+1);//进入下一个数 
	}
}
int main(){
	cin>>n>>m>>q;
	for(int i=1;i<=q;i++)
	{
		cin>>a[i]>>b[i]>>c[i]>>d[i];//输入 
	}
	A[0]=1;//一定要因为此时A0就是A1前的1 
	dfs(1);//从1开始 
	cout<<Max;
	return 0;
} 
```

---

## 作者：Mu_leaf (赞：1)

## [思路]
明显的阅读理解。

我们可以通过 dfs 全排列在所有的可能性中寻找得分最高的解。

用 dfs 枚举出数列 $A$ 中的每一个数，由题意可知数列 $A$ 是递增的，所以每次从数列 $A$ 的前一个数的值开始枚举，枚举完成后求这个数列的值与当前数列的最大值作比较，最后输出最大值就行。

## [题外话]

由于本题 $m,n \leq 10$ 所以不用考虑时间复杂度。

但需要注意的是 dfs 全排列的时间复杂度是极高的，所以谨慎使用吧！

# Code：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MaxN = 20;

struct S {
  int x, y, w, num;
} a[100];

int ind[MaxN], n, m, q, ans;

int anser() {
  int ans1=0;
  for (int i = 1; i <= q; i++) {
    if (ind[a[i].y] - ind[a[i].x] == a[i].w) ans1 += a[i].num;
  }
  return ans1;
}

void dfs(int x) {
  if (x == n + 1) {
    	ans = max(ans, anser());
    	return;
  }
  for (int i = ind[x]; i <= m; i++) {
    	ind[x + 1] = i;
    	dfs(x + 1);
  }
}

signed main() {
  cin >> n >> m >> q;
  for (int i = 1; i <= q; i++) {
    cin >> a[i].x >> a[i].y >> a[i].w >> a[i].num;
  }
  ind[1] = 1;
  dfs(1);
  cout << ans << "\n";
  return 0;
}
```


---

## 作者：scp020 (赞：0)

题目翻译已经很简洁了，这里不再多说什么了。

感觉题目非常复杂，而且不知道如何最大化答案。可是看一下数据范围，$n,m \le 10$，说明这是可以爆搜的。

爆搜时用栈（这里推荐用动态数组）存储搜过的数，在搜索结束后别忘记弹出。最后搜到 $n$ 个数时就计算答案，与现有答案比较，取最大值。

时间复杂度：$(n+q) C_{n+m-1}^n$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define Getchar() p1==p2 and (p2=(p1=Inf)+fread(Inf,1,1<<21,stdin),p1==p2)?EOF:*p1++
char Inf[1<<21],*p1,*p2;
inline void read(int &x,char c=Getchar())
{
	bool f=c!='-';
	x=0;
	while(c<48 or c>57) c=Getchar(),f&=c!='-';
	while(c>=48 and c<=57) x=(x<<3)+(x<<1)+(c^48),c=Getchar();
	x=f?x:-x;
}
int n,m,q,ans;
struct require
{
	int a,b,c,d;
};
require arr[100];
vector<int> v;
inline void dfs()
{
	if(v.size()>n)
	{
		int sum=0;
		for(int i=1;i<=q;i++) sum+=(v[arr[i].b]-v[arr[i].a]==arr[i].c)*arr[i].d;
		ans=max(ans,sum);
	}else for(int i=v.back();i<=m;i++) v.push_back(i),dfs(),v.pop_back();
}
int main()
{
	read(n),read(m),read(q);
	for(int i=1;i<=q;i++) read(arr[i].a),read(arr[i].b),read(arr[i].c),read(arr[i].d);
	v.push_back(6),v.push_back(1),dfs(),cout<<ans;
	return 0;
}
```



---

## 作者：small_john (赞：0)

## 前言

今天%你赛有这道题，水一发题解。

## 思路

简单的 DFS 题目，建议降橙。

用 $x$ 记录当前的数，由于 $A$ 是升序排列的（注意是 $A_i\geq A_{i-1}$，不要看成大于），每次 $A_x$ 都在 $A_{x-1}\sim m$ 中枚举。当 $x>n$ 时，计算答案，回溯。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e2+5;
int n,m,q,a[N],b[N],c[N],d[N],A[N],ans;
int solve()//计算答案
{
	int res = 0;
	for(int i = 1;i<=q;i++)
		if(A[b[i]]-A[a[i]]==c[i])
			res+=d[i];
	return res;
}
void dfs(int x)
{
	if(x>n)
	{
		ans = max(ans,solve());//取最大
		return;
	}
	for(int i = A[x-1];i<=m;i++)
		A[x] = i,dfs(x+1);
}
signed main()
{
	cin>>n>>m>>q;
	A[0] = 1;//不加这句话见祖宗
	for(int i = 1;i<=q;i++)
		cin>>a[i]>>b[i]>>c[i]>>d[i];
	dfs(1);
	cout<<ans;
	return 0;
}
```

---

