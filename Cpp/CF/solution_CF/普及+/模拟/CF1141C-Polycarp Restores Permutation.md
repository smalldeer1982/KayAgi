# Polycarp Restores Permutation

## 题目描述

An array of integers $ p_1, p_2, \dots, p_n $ is called a permutation if it contains each number from $ 1 $ to $ n $ exactly once. For example, the following arrays are permutations: $ [3, 1, 2] $ , $ [1] $ , $ [1, 2, 3, 4, 5] $ and $ [4, 3, 1, 2] $ . The following arrays are not permutations: $ [2] $ , $ [1, 1] $ , $ [2, 3, 4] $ .

Polycarp invented a really cool permutation $ p_1, p_2, \dots, p_n $ of length $ n $ . It is very disappointing, but he forgot this permutation. He only remembers the array $ q_1, q_2, \dots, q_{n-1} $ of length $ n-1 $ , where $ q_i=p_{i+1}-p_i $ .

Given $ n $ and $ q=q_1, q_2, \dots, q_{n-1} $ , help Polycarp restore the invented permutation.

## 样例 #1

### 输入

```
3
-2 1
```

### 输出

```
3 1 2 ```

## 样例 #2

### 输入

```
5
1 1 1 1
```

### 输出

```
1 2 3 4 5 ```

## 样例 #3

### 输入

```
4
-1 2 2
```

### 输出

```
-1
```

# 题解

## 作者：luojien (赞：4)

# CF1141C Polycarp Restores Permutation

## 思路整理

### 题目分析

这是一道非常简单（~~指调了一下午~~）的前缀和水题。只要找好公式很快就可以 AC。

### 解题思路

根据题意，$p$ 数组的元素之和在 $n$ 一定的情况下是不会变的。因此，可推出：

$r_1 = q_1 = p_2 - p_1$

$q_2 = p_3 - p_2, r_2 = q_1 + q_2 = p_3 - p_1$

$q_3 = p_4 - p_3, r_3 = q_1 + q_2 + q_3 = p_4 - p_1$

$\dots$

$q_{n - 1} = p_n - p_{n - 1}, r_{n - 1} = \sum\limits_{i=1}^{n}q_i = p_n - p_1$

因此，可得出 $\sum\limits_{i=1}^{n-1}r_i = \sum\limits_{i=2}^{n}p_i - (n - 1)p_1 = \sum\limits_{i=1}^{n}p_i - n \times p_1$。

于是 $n \times p_1 = \frac{n \times (n + 1)}{2} - \sum\limits_{i=1}^{n-1}r_i$。

综上所述，我们可以求出 $p_1$，根据 $p_1$ 的值可得出：$p_i = r_{i - 1} + p_1$。

进行上述操作后，对数组 $p$ 进行排序，此时若 $p$ 为排列数组，那么 $p_i = i$ 应当成立。

## AC代码

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int main() {
    ll n;
    cin >> n;
    int q[n] = {};
    ll r[n] = {};
    ll sum = 0;
    ll rSum = 0;
    for (int i = 1; i <= n - 1; i++) {
        scanf("%d", &q[i]);
        sum += q[i];
		r[i] = sum;
		rSum += r[i];
    }
    ll S = (n * (n + 1)) >> 1;
    ll k = S - rSum;
    if(k % n != 0){
    	printf("-1");
    	return 0;
	}
	int p[n + 1] = {};
	int pp[n + 1] = {};
	p[1] = k / n;
	pp[1] = p[1];
    for(int i = 2; i <= n; i++){
	    p[i] = r[i - 1] + p[1];
	    pp[i] = p[i];
	}
	sort(p + 1, p + n + 1);
	for(int i = 1; i <= n; i++){
		if(p[i] != i){
			printf("-1");
			return 0;
		}
	}
	for(int i = 1; i <= n; i++){
		printf("%d ", pp[i]);
	}
    return 0;
}
```

---

## 作者：wlzhouzhuan (赞：4)

本题预处理前缀和$qwq[i].s=qwq[i-1].s+a[i]$，同时记录前缀数组的$qwq[i].id=i$，

显然，$qwq[i].s=\sum_{k=1}^{i}a[i]=p[i]-p[1]$

之后我们将$qwq$数组排个序，$qwq[i].s$越小的意味着$p[i]$越小，所以给答案$p[qwq[i].id]=i$即可。

个人认为本方法特别优秀，欢迎$dalao$来D。

$Code:$

```cpp
#include <bits/stdc++.h>
using namespace std;

#define RE register
#define rep(i, l, r) for (RE int i = l; i <= r; i++)
#define req(i, l, r) for (RE int i = l; i >= r; i--)
#define For(i, l, r) rep(i, l, r - 1)

void read(int &x) {
    x = 0; int f = 1;
    char op = getchar();
    while (!isdigit(op)) {
        if (op == '-') f = -1;
        op = getchar();
    }
    while (isdigit(op)) {
        x = 10 * x + op - '0';
        op = getchar();
    }
    x *= f;
}

const int N = 400005;
struct ele {
	int s, id;
	bool operator < (const ele b) const {
		return s < b.s;
	}
}qwq[N];
int a[N], ans[N], n;
int vis[N];

bool check() {
	int cha = 0;
	rep(i, 2, n) {
		if (ans[i] - ans[i - 1] != a[i])
			return 0;
	}
	return 1;
}

int main() {
	read(n);
	qwq[1].s = 0, qwq[1].id = 1;
	rep(i, 2, n) {
		read(a[i]);
		qwq[i].s = qwq[i - 1].s + a[i];
		qwq[i].id = i;
	}
	sort(qwq + 1, qwq + n + 1);
	for (int i = 1; i <= n; i++)
		ans[qwq[i].id] = i;
	
	if (check()) {
		for (int i = 1; i <= n; i++)
			printf("%d ", ans[i]);
		putchar('\n');
	}
	else puts("-1");
	return 0;
}
```

---

## 作者：wasa855 (赞：2)

### 二分   
对于每次check，如果出现一样的数，说明是不行的，如果有一个数 $<1$ ，说明原始的数太小了，如果有一个数 $>n$ ，说明原始的数太大了，如果 $l>r$ 了还没有满足条件的数，说明是 $-1$ ，因为既有 $<1$ 的数，又有 $>n$ 的数。   
最后输出满足条件的结果就可以了。   
代码：   
``` cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005];
bool used[200005];
int n;
int judge(int x)
{
	memset(used,false,sizeof(used));
	used[x]=true;
	for(int i=1;i<n;i++)
	{
		x+=a[i];
		if(x<1)
		{
			return 1;
		}
		if(x>n)
		{
			return 0;
		}
		if(used[x]==true)
		{
			cout<<"-1\n";
			exit(0);
		}
		used[x]=true;
	}
	return 2;
}
int main()
{
	cin>>n;
	for(int i=1;i<n;i++)
	{
		scanf("%d",&a[i]);
	}
	int l=1,r=n,mid,ans=-1;
	while(l<=r)
	{
		mid=(l+r)>>1;
		int ind=judge(mid);
		if(ind==1)
		{
			l=mid+1;
		}
		if(ind==0)
		{
			r=mid-1;
		}
		if(ind==2)
		{
			ans=mid;
			break;
		}
	}
	if(ans==-1)
	{
		cout<<"-1\n";
		return 0;
	}
	cout<<ans<<" ";
	for(int i=1;i<n;i++)
	{
		ans+=a[i];
		printf("%d ",ans);
	}
	return 0;
}
```

---

## 作者：zhy12138 (赞：2)

本文同步发表于[我的博客](https://zhy12138.github.io/2019/03/24/CF-1141-div3/)

题目给定条件 $q_i=p_{i+1}-p_i$

在$q$上求前缀和后可得 $q_i=p_{i+1}-p_1$

然后可以得到:
$$\sum^{n-1}_{i=1}q_i=\sum^n_{i=2}p_i-p_1*(n-1)$$

emmmm,似乎有些难看，那这样呢？

$$\sum^{n-1}_{i=1}q_i=\sum^n_{i=1}p_i-p_1*n$$

这样想法就简单了，由上式求得$p_1$，然后由$p_1$求得$p$数组，再检验就行了

注：注意开`long long`

```cpp
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<algorithm>
#include<ctime>
#define ll long long
using namespace std;
inline int read()
{
    int kkk=0,x=1;
    char c=getchar();
    while((c<'0' || c>'9') && c!='-')
        c=getchar();
    if(c=='-')
        c=getchar(),x=-1;
    while(c>='0' && c<='9')
        kkk=(kkk<<3)+(kkk<<1)+(c-'0'),c=getchar();
    return kkk*x;
}
long long sum,n,q[200001],a[200001],b[200001];
int main()
{
	n=read();
	for(register int i=1;i<n;++i)
		q[i]=q[i-1]+read(),sum+=q[i];
	long long t=n*(n+1)/2;
	long long rest=t-sum;
	if(rest%n!=0)
	{
		puts("-1");
		return 0;
	}
	long long p1=rest/n;
	a[1]=b[1]=p1;
	for(register int i=2;i<=n;++i)
		a[i]=b[i]=(q[i-1]+p1);
	sort(a+1,a+n+1);
	if(a[1]!=1)
	{
		puts("-1");
		return 0;
	}
	for(register int i=2;i<=n;++i)
		if(a[i]-a[i-1]!=1)
		{
			puts("-1");
			return 0;
		}
	for(register int i=1;i<=n;++i)
		printf("%lld ",b[i]);
    return 0;
}
```

---

## 作者：Yexo (赞：1)

一道水绿。
## Solution
大致方向：数学加桶排。

题目分析：由题可知 $q_i = p_{i+1} - p_i $，发挥你小学二年级就学过的知识可以推导出 $q_i+p_i = p_{i+1}$，所以我们可以设 $p_1=1$，那么就可以推导出序列 $p$ 中所有的值。因为要考虑是序列  $p$ 是否为 $1 ∼ n$ 的一个排列，可以找出目前序列最小值 $minx$，求 $1 - minx$ 即可。过程中可用桶排记录，最后枚举查询该序列是否合法。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
long long p[N];
int temp[N];
int n,q;
long long idx;
long long minx=1;
int main(){
    p[1]=1;
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        scanf("%d",&q);
        p[i+1]=q+p[i];
        minx=min(minx,p[i+1]);
    }
    idx=1-minx;
    for(int i=1;i<=n;i++){
        p[i]+=idx;
        if(p[i]>n){
            printf("-1");
            return 0;
        }
        temp[p[i]]++;
    }
    for(int i=1;i<=n;i++){
        if(temp[i]!=1){
            printf("-1");
            return 0;
        }
    }
    for(int i=1;i<=n;i++) printf("%d ",p[i]);
}
```

---

## 作者：da32s1da (赞：1)

首先根据差分，找到比$p_1$大的最大的位置，这个位置一定是$n$。

然后顺着差分递推过去就好了。

```cpp
#include<cstdio>
const int N=2e5+50;
int n,a[N],b[N],vis[N],x,y,z;
int main(){
    scanf("%d",&n);
    z=1;
    for(int i=2;i<=n;i++){
        scanf("%d",&a[i]);
        x+=a[i];
        if(y<x)y=x,z=i;
    }
    b[z]=n;vis[n]=1;
    //最大的是n
    for(int i=z+1;i<=n;i++){
        if(b[i-1]+a[i]<=0||b[i-1]+a[i]>n||vis[b[i-1]+a[i]]){puts("-1");return 0;}//判无解
        b[i]=b[i-1]+a[i];vis[b[i]]=1;
    }
    //向右递推
    for(int i=z;i>=2;i--){
        if(b[i]-a[i]<=0||b[i]-a[i]>n||vis[b[i]-a[i]]){puts("-1");return 0;}//判无解
        b[i-1]=b[i]-a[i];vis[b[i-1]]=1;
    }
    //向左递推
    for(int i=1;i<=n;i++)printf("%d ",b[i]);
}
```

---

## 作者：_6_awa (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1141C)

题目大意：构造一个全排列 $p$ 满足 $q_i = p_{i + 1} - p_i$。

题目分析：这题可以用桶和贪心来做。具体是什么呢？我们可以先设第一个数为 $x$，根据 $q_i$，我们很快就能用 $x$ 来表示其他的数。此时，我们只要判断最大数与最小数的差是否 $< n$ 以及是否有重复就行了。此时如果可行，最小的数就是 $1$，以大小来排列。这样，一个全排列就解出来了。

### AC Code:

```cpp
#include <iostream>
using namespace std;
int n,a[200005],b[200005],c[500005],minn,maxx;
int main()
{
    cin >> n;
    b[1] = n,minn = maxx = n,c[n] = 1;//这里将第一个数设为n
    for(int i = 2;i <= n;i ++)
    {
        cin >> a[i],b[i] = b[i - 1] + a[i];
        minn = min(minn,b[i]);
        maxx = max(maxx,b[i]);
        if(b[i] < 1 || b[i] >= 2 * n || maxx - minn >= n)//如果任意一个数<1或>2*n则差太大不符合条件
        {
            cout << -1;
            return 0;
        }
        if(c[b[i]])
        {
            cout << -1;
            return 0;
        }
        c[b[i]] = 1;
    }
    for(int i = 1;i <= n;i ++)cout << b[i] - minn + 1 << " ";//最后输出
}

---

## 作者：1saunoya (赞：1)

># $problem$
>## [更好的阅读体验](https://www.cnblogs.com/qf-breeze/p/10564198.html)
>这题的大致意思就是已知数值差值 求1-n的排列

~~~
如果能构成排列 则输出这个排列。如果不能则输出-1
排列的值都是 大于1 而小于n的 而且没有相同的数字。
~~~
>这题最关键的是 怎么输出这个序列 有的是存在负数的。


>那么 考虑一下排列都是从1到n的对不对。
>取序列的最小值 然后用$1 - Min$即是整个序列应该加上的数值。
>首先考虑判重。 用数组 或者用$map or set$ 。
>都是不错的方法。

~~~
#include <bits/stdc++.h>
using namespace std;
typedef long long LL ;
inline LL In() { LL res(0),f(1); register char c ;
    while(isspace(c=getchar())) ; c == '-'? f = -1 , c = getchar() : f = 1 ;
    while(res = (res << 1) + (res << 3) + (c & 15) , isdigit(c=getchar())) ; return res * f ;
}
int n ;
int p[200000+5] ;
int res[200000+5] ;
set<int> s;//判重
signed main(){
    n = In() ;
    for(register int i=1;i<=n-1;i++) p[i] = In() ;
    res[1] = 0 ;
    for(register int i=2;i<=n;i++) res[i] = res[i-1] + p[i-1] ;//计算前缀和
    int Min = 0x7f7f7f7f;
    for(register int i=1;i<=n;i++){
        Min = min(res[i],Min);
        if(s.count(res[i])==0) s.insert(res[i]) ;//插入数值
        else {
            cout << -1 << endl ;//如果存在重复的数值则不可能构成排列。
            return 0 ;
        }
    }
    //cout << Min << endl ;
    int c = 1 - Min ;
    bool f = false;
    for(register int i=1;i<=n;i++) {
        if(res[i] + c > n) {//如果大于n则不能构成 也是输出-1
            cout << -1 << endl ;
            return 0 ;
        }
    }
    
    for(register int i=1;i<=n;i++) {
        cout << res[i] + c << ' ' ;
    }
    return 0 ;
}
~~~

---

## 作者：copper_ingot (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1141C)

[不一定更好的阅读体验](https://www.luogu.com.cn/blog/cooooooooper/solution-cf1141c)

以下设 $q$ 为 $q_2,q_3,\dots,q_n$。

这一题的 $q$ 数组可以看做是 $p$ 的差分数组的第 $2$ 到 $n$ 位。

但是，$q$ 的第一位没有给出，所以先设其为 $0$。

这样，我们就可以对 $q$ 做一次前缀和得到一个数组 $pre$。

虽然 $pre$ 里面可能有负数，但 $pre$ 里面的每个数 $pre_i$ 都只比 $p_i$ 少一个常数，就是 $p_i$ 原本的差分数组的第一位，也就是原来的 $q_1$。因为系统没有给出，所以我们把它设为了 $0$。

现在我们给 $pre$ 排序，并检验 $pre$ 是否是连续整数。对于每个 $pre_i$，如果 $i < n$ 且 $pre_i = pre_{i + 1} - 1$，那么这一位就是合法的，把 $pre_i$ 改为 $i$。如果遇到不合法的情况直接输出 $-1$。

经过一番操作后，$pre$ 变成了一串从 $1$ 到 $n$ 的连续自然数。

最后把 $pre$ 按原来的顺序排好，就得到了最终的 $p$ 排列。

代码贴上：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, q[200001];
struct perm{int pre, id;}p[200001];
bool cmp(perm a, perm b){return a.pre < b.pre;}
bool cmp2(perm a, perm b){return a.id < b.id;}
int main(){
	scanf("%d", &n);
	for (int i = 2; i <= n; i++){scanf("%d", &q[i]); p[i].pre = p[i - 1].pre + q[i], p[i].id = i;}//求前缀和的同时记录原来的顺序
	p[1].id = 1, p[1].pre = 0;//别忘了有p1
	sort(p + 1, p + n + 1, cmp);
	for (int i = 1; i < n; i++){
		if (p[i].pre == p[i + 1].pre - 1) p[i].pre = i;
		else{puts("-1"); return 0;}
	}//进行检验
	p[n].pre = n;
	sort(p + 1, p + n + 1, cmp2);
	for (int i = 1; i <= n; i++) printf("%d ", p[i].pre);
	return 0;
}
```

---

## 作者：cppcppcpp3 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1141C)。

## Solution

极简单的绿。

给出原数组的差分数组，让你求原数组是否是 $[1,n]$ 的一个排列。

那么先对差分数组做前缀和，得到原数组所有项都减去 $d$ 的一个结果，称其为数组 $a$。

对 $a$ 排序，则此时 $a_1$ 对应的值就是原来的最小值，所以可以得到复原加上的 $d=1-a_1$。

此时使 $a_i \leftarrow a_i+d$，即得到原数组。

判断原数组是否合法：判断是否有重复元素、是否有 $a_i<1$ 或 $a_i>n$。

然后按排序前的顺序输出 $a_i$，做完了。

复杂度 $O(n \log n)$，瓶颈在排序。具体见代码。

```cpp
#include<bits/stdc++.h>
#define il inline
using namespace std;
const int N=2e5+5;

il int wrd(){
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1; c=getchar();}
	while(isdigit(c)){x=x*10+c-48,c=getchar();}
	return x*f;
}

int n,b[N],d,q[N];
bool vis[N];

struct node{
	int x,id;
	bool operator < (const node &a) const{
		return x<a.x;
	}
}a[N];

main(){
	n=wrd();
	for(int i=2;i<=n;++i) b[i]=wrd(),a[i]=node{a[i-1].x+b[i],i};
	a[1].id=1;
	sort(a+1,a+n+1);
	for(int i=1;i<=n;++i) q[a[i].id]=i;
	
	d=1-a[1].x;
	for(int i=1;i<=n;++i);
	for(int i=1;i<=n;++i){
		a[i].x+=d;
		if(a[i].x<1 || a[i].x>n || vis[a[i].x]) return puts("-1"),0;
		vis[a[i].x]=1;
	}
	for(int i=1;i<=n;++i) printf("%d ",a[q[i]].x);
	return 0;
}
```

---

## 作者：fengxiaoyi (赞：0)

### 我的思路

这题的一个算式 $q_{i}=p_{i+1}-p_{i}$ 让我想到了差分，但是再一看，没有第一项，没办法倒推。

但是，想到 $p_i=\displaystyle\sum_{j=1}^iq_j$，但没有第一项，那我们先把第一项的值空出来，再求出 $p$ 数组。

接着，把 $p$ 数组的值加起来得到 $k$，由于 $p$ 数组是一个排列，所以和一定是 $n\times (n+1)\div 2$，然后判断 $n\times (n+1)\div 2\bmod k$ 是否 $=0$，如果否，输出 `-1`。

如果是，那么把 $p_i$ 加上 $n\times (n+1)\div 2$，$O(n)$ 遍历一遍是不是一个排列（~~我在这里调了好久~~），如果不是，输出 `-1`，否则，输出这个 $p$ 数组。

### 代码

```cpp
#include<bits/stdc++.h>
namespace Cmath{
	long long fpow(long long a,long long b,const int k){
		long long sum=1,A=a;
		while(b){
			if(b&1)
				sum=sum*A%k;
			A=A*A%k;
			b>>=1;
		}
		return sum;
	}
	void cmax(long long &a,long long b){
		a=std::max(a,b);
	}
	void cmin(long long &a,long long b){
		a=std::min(a,b);
	}
}
namespace _fast{
	bool print(long long _a,bool _f){
		if(_a<0){
			putchar('-');
			print(-_a,_f|1);
			if(!_f) putchar('\n');
			return 1;
		}
		if(_a<10){
			putchar(_a+'0');
			if(!_f) putchar('\n');
			return 1;
		}
		print(_a/10,_f|1);
		putchar(_a%10+'0');
		if(!_f) putchar('\n');
		return 1;
	}
	void wrap(){
		putchar('\n');
	}
	void _space(){
		putchar(' ');
	}
}
using namespace std;
using namespace Cmath;
using namespace _fast;
int n,p;
long long sum[200010],k,q[200010];
map<int,bool>m;
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		scanf("%d",&p);
		sum[i]=sum[i-1]+p;
		k+=sum[i];
	}
	if((1ll*n*(n+1)/2-k)%n!=0) return !print(-1,0);
	k=(1ll*n*(n+1)/2-k)/n;
	for(int i=0;i<n;i++){
		q[i]=sum[i]+k;
		if(q[i]<1||q[i]>n||m[q[i]]) return !print(-1,0);
		m[q[i]]=1;
	}
	for(int i=0;i<n;i++) print(q[i],1),_space();
	return 0;
}
```


---

## 作者：Eason_AC (赞：0)

## Content
给定一个长度为 $n-1$ 的序列 $q$，问你是否能找到一个 $1\sim n$ 的排列 $p$，使得 $\forall i\in[1,n)$，$q_i=p_{i+1}-p_i$。

**数据范围：$2\leqslant n\leqslant 2\times 10^5$，$-n<q_i<n$。**
## Solution
首先我们不难知道，设 $S_i=\sum\limits_{j=1}^i q_j$，那我们不难知道，**$S_i$ 越小，第 $i+1$ 个数就越小**。因此我们考虑前缀和处理下，找到能使得 $S_i$ 最小的 $i$，然后不难发现 $p_{i+1}=1$，再从 $p_{i+1}$ 开始暴力往前往后直接推出原来的数列，最后再判断 $1\sim n$ 是否在这个数列中都恰好出现过一次即可。
## Code
```cpp
int n, cha[200007], a[200007], sum, ans, id1 = 1;
map<int, int> vis;

int main() {
    n = Rint;
	F(i, 1, n - 1) {
		cha[i] = Rint, sum += cha[i];
		if(sum < ans) ans = sum, id1 = i + 1;
	}
	a[id1] = 1;
	R(i, id1 - 1, 1) a[i] = a[i + 1] - cha[i];
	F(i, id1 + 1, n) a[i] = a[i - 1] + cha[i - 1];
	F(i, 1, n) {
		if(vis[a[i]]) return printf("-1"), 0;
		vis[a[i]] = 1;
	}
	F(i, 1, n) if(!vis[i]) return printf("-1"), 0;
	F(i, 1, n) write(a[i]), putchar(i == n ? '\n' : ' ');
    return 0;
}
```

---

