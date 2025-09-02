# Petr and Permutations

## 题目描述

Petr likes to come up with problems about randomly generated data. This time problem is about random permutation. He decided to generate a random permutation this way: he takes identity permutation of numbers from $ 1 $ to $ n $ and then $ 3n $ times takes a random pair of different elements and swaps them. Alex envies Petr and tries to imitate him in all kind of things. Alex has also come up with a problem about random permutation. He generates a random permutation just like Petr but swaps elements $ 7n+1 $ times instead of $ 3n $ times. Because it is more random, OK?!

You somehow get a test from one of these problems and now you want to know from which one.

## 说明/提示

Please note that the sample is not a valid test (because of limitations for $ n $ ) and is given only to illustrate input/output format. Your program still has to print correct answer to this test to get AC.

Due to randomness of input hacks in this problem are forbidden.

## 样例 #1

### 输入

```
5
2 4 5 1 3
```

### 输出

```
Petr
```

# 题解

## 作者：pufanyi (赞：14)

都是$O(n\log n)$的？  
我来一发$O(n)$的。  
首先我们考虑怎么快速还原这个序列。  
很显然的一个贪心策略就是假设序列为$\{a_i\}$，不断把$a_{a_i}$与$a_i$交换直到$a_i=i$。  
这样做我们发现交换次数是$O(n)$级别的。  
然后我们发现要一个序列交换后形成交换前的序列交换次数只能是偶数。所以该交换次数与`Petr`或`Alex`的奇偶性相同。  
于是只要判一下奇偶即可。  
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 1000005;

int aa[maxn];

int main()
{
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%d", &aa[i]);
    int ans = 0;
    for(int i = 1; i <= n; ++i)
    {
        while(aa[i] != i)
        {
            swap(aa[aa[i]], aa[i]);
            ans++;
        }
    }
    if((n & 1) == (ans & 1)) // 判断奇偶性相同
        puts("Petr");
    else
        puts("Um_nik");
    return 0;
}
```

---

## 作者：Mr_Wu (赞：7)

![](https://cdn.luogu.com.cn/upload/pic/8795.png)

-------------

首先，我们需要一个引理：**交换序列的任意两元素，序列的逆序数的奇偶性必定发生改变。**

如何证明？

~~反正我不会证我是手推瞎猜的~~

------------

显然$3n$与$7n+1$的奇偶性不同。

那么$Petr$和$Alex$交换后的序列逆序数奇偶性也不同。

算出给定序列逆序数，判断奇偶性即可。

这里$n<=10^6$，普通的$O(n^2)$算法肯定不行啊。

树状数组$O(n\log{n})$。

------------

我们记$x[i]$为$a[1],a[2],...,a[n-1]$中比$a[i]$大的数的个数，例如序列

$1,4,2,5,3$

记$x[1]=0, x[2]=0, x[3]=1, x[4]=0, x[5]=2$

那么逆序数个数就是$x[1]+x[2]+...+x[n]$，在这里就是$3$。（这里的逆序数是指数对$(i,j)$满足$i<j$且$a[i]>a[j]$的）

开一个桶，从$1$到$n$循环，每次记$x[i]=sum(a[i],n)$，然后$bucket[i]=1$.

我们来模拟这个过程，以上文提到的序列为例。

$i=1$时：$a[i]=1$，桶为$0,0,0,0,0$，$x[i]=0$

$i=2$时：$a[i]=4$，桶为$1,0,0,0,0$，$x[i]=0$

$i=3$时：$a[i]=2$，桶为$1,0,0,1,0$，$x[i]=1$

$i=4$时：$a[i]=5$，桶为$1,1,0,1,0$，$x[i]=0$

$i=5$时：$a[i]=3$，桶为$1,1,0,1,1$，$x[i]=2$

最后累加，得出逆序数。

可这跟树状数组有什么关系？

每次求和就是区间求和，$bucket[i]=1$就是单点修改。

至于树状数组是什么...qwq

------------

参考代码：

```cpp
#include <cstdio>

const int MAXN = 1000005;
int tree[MAXN], n, a[MAXN], ans = 0;

int lowbit(int x)
{
	return x & -x;
} //lowbit qwq

void insert(int pos, int k)
{
	if (pos < 1) return;
	while (pos <= n)
	{
		tree[pos] += k;
		pos += lowbit(pos);
	}
} //单点修改

int query(int pos)
{
	int ret = 0;
	while (pos)
	{
		ret += tree[pos];
		pos -= lowbit(pos);
	}
	return ret;
} //(1-pos)的查询，查询[l,r]的和用query(r)-query(l-1)

int main()
{
	scanf("%d", &n);
	int i;
	for (i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (i = 1; i <= n; i++)
	{
		ans = (ans + query(n) - query(a[i] - 1)) % 2; 
        //直接记录答案的奇偶性了，query(n)-query(a[i]-1)是sum(a[i],n)
		insert(a[i], 1);
        //单点修改
	}
	ans %= 2;
	if ((ans - 3 * n) % 2 == 0) printf("Petr"); //奇偶性判断
	else printf("Um_nik");
	return 0;
}
```

------------

$qwq$

---

## 作者：duyi (赞：5)

分享一个的乱搞做法。

从感觉上来说，$3n$ 次随机的排列会比 $7n + 1$ 次随机的排列更“**有序**”一些。那么我们怎么衡量这个“有序”的程度呢？

经过尝试，我们发现了一个可以量化的指标：

$$
f(p) = \sum_{i = 1}^{n}[p_i = i]
$$

直觉上容易看出，随机的次数越多，排列应该越无序，$f(p)$ 应该越小。所以 $3n$ 次随机的排列，$f(p)$ 值是明显大于 $7n + 1$ 次随机的（$n$ 越大越明显，读者可以自己进行一些尝试）。

事实上，只要 $f(p) > 2$ 我们就判为 $3n$ 次随机，$f(p)\leq 2$ 我们就判为 $7n + 1$ 次随机。特判样例后，可以通过本题。

代码如下：

```cpp
int n, p[MAXN + 5];

int main() {
	cin >> n;
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		cin >> p[i];
		ans += (p[i] == i);
	}
	if (n == 5 || ans > 2) {
		cout << "Petr" << endl;
	} else {
		cout << "Um_nik" << endl;
	}
	return 0;
}
```

其实，顺着这个思路，我们可以做更进一步的探究。考虑如下问题：

> 一个排列 $p$，初始时是 $1,2,\dots ,n$。现在进行 $m$ 次操作，每次随机两个不同的位置，交换它们的值。问 $m$ 次操作后 $p_i = i$ 的位置 $i$ 的数量的期望。

因为在排列里，每个位置是等价的，所以根据期望的线性性，我们只需要算出最终 $1$ 在原位的概率（即 $p_1 = 1$ 的概率），再乘以 $n$ 就是答案了。

于是可以考虑 DP。设 $\mathrm{dp}(i, 0/1)$ 表示第 $i$ 次操作后，$1$ 是/否在原地的概率。转移比较简单。

通过这个 DP 可以算出，$n = 1000$ 时，$3n$ 次随机得到的 $f(p)$ 的期望是 $3.44667$，而 $7n + 1$ 次随机得到的 $f(p)$ 值的期望是 $1.00081$。所以上述做法还是很有道理的。







---

## 作者：大菜鸡fks (赞：4)

每次交换一对元素，逆序对数会+1，或-1

设最后逆序对数为k，k=x-y, x+y=3n

这个方程有解就是当3n+k为偶数时，那么自然的，n和k奇偶性相同时x有整数解

那么怎么做就一目了然了

```cpp
#include<cstdio>
using namespace std;
const int N=1e6+5;
int bit[N],sum,n,a[N];
inline void init(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
}
inline int lowbit(int x){
	return x&(-x);
}
inline void upd(int x,int v){
	for (;x<=n;bit[x]+=v,x+=lowbit(x));
}
inline int query(int x){
	int tmp=0;
	for (;x;tmp+=bit[x],x-=lowbit(x));
	return tmp;
}
inline void solve(){
	for (int i=n;i;i--){
		sum+=query(a[i]);
		upd(a[i],1);
	}
	sum&=1; n&=1;
	if (sum==n) puts("Petr"); else puts("Um_nik");
}
int main(){
	init();
	solve();
	return 0;
} 
```

---

## 作者：xiaoshumiao (赞：2)

每把序列打乱一次，序列的逆序对数会改变奇偶性（要么 $+1$ 要么 $-1$）。因此把序列打乱 $i$ 次，记当前的逆序对数为 $x$，则 $x \bmod 2=i \bmod 2$。

而 $3n$ 和 $7n+1$ 的奇偶性是不一样的，所以逆序对数也不一样。直接求出逆序对数量并判断即可。
```cpp
#include<cstdio>
using namespace std;
const int N=1e6+10; int a[N],arr[N]; long long ans;
void merge(int l,int mid,int r) {
  int i=l,j=mid+1;
  for(int k=l;k<=r;k++) {
  	if(i>mid) arr[k]=a[j],j++;
  	else
  	  if(j>r) arr[k]=a[i],i++;
  	  else
  	    if(a[i]<=a[j]) arr[k]=a[i],i++;
  	    else ans+=mid-i+1,arr[k]=a[j],j++;
  }
  for(int k=l;k<=r;k++) a[k]=arr[k];
}
void mergesort(int l,int r) {
  if(l>=r) return;
  int mid=(l+r)>>1;
  mergesort(l,mid),mergesort(mid+1,r),merge(l,mid,r);
}
int main() {
  int n; scanf("%d",&n);
  for(int i=1;i<=n;i++) scanf("%d",&a[i]);
  mergesort(1,n);
  printf((ans&1)==(3*n&1)?"Petr":"Um_nik");
  return 0;
}
```

---

## 作者：PDAST (赞：1)

## 题意
有一个长度为 $N$ 由 $1$ 至 $N$ 组成的升序数列，有两个人可能会对其操作，Petr 会对其操作 $3 \times N$ 次，Alex 会对其操作 $7 \times N + 1$ 次，每次操作为随机交换其中两个数，问是谁操作了（只有一个人会操作）
## 思路
和其他题解不同，这篇题解使用 dfs 解决问题，我们从头开始，挨个枚举，只要没被访问过就进入 dfs 搜索，搜索的内容本质上来说是通过递归的方式向上寻找这个数的“源头”，即找这个数原本在哪个位置，现在在哪，每次往上递归，只要经过就设为零，如果再次经过则累加器增加刚才走过的数的数量。
## code
[AC记录](https://www.luogu.com.cn/record/150289284)
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,sum;
int a[1000001],vis[1000001];
void search(int num,int cnt){
	if(vis[num]){
		sum+=cnt-1;
		return;
	}
	vis[num]=1;
	num=a[num];
	search(num,cnt+1);
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		if(!vis[i])search(i,0);
	}
	n*=3;
	if(n%2!=sum%2)cout<<"Um_nik";
	else cout<<"Petr";
	return 0;
}
```

---

## 作者：liuyr1234 (赞：1)

一个奇怪的方法
# 题意
有一个 $1\sim n$ 的排列，可能由 Petr 打乱或由 Alex 打乱。告诉你最终序列，问是否是 Petr 打乱了，如果是输出 Petr，反之输出 Um_nik
## [题目链接CF986B](https://www.luogu.com.cn/problem/CF986B)
## 解析
在序列有序的情况下连续交换两个相同的数等同于不交换，很明显 $3n$ 和 $7n+1$ 为一奇一偶，所以3n减去交换为有序数列的次数如果为二的倍数就等同于交换了 $3n$ 次，否则为 $7n+1$ 次。

## Code：
```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cmath>
#include<queue>
#include<algorithm>
#define MAXN 1000860

using namespace std;

int t,n,a[MAXN];
int ans;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int l=0;
	while(l<=n){
		if(a[l]==l){
			l++;
		}
		else{
			int x;
			x=a[l];
			a[l]=a[a[l]];
			a[x]=x;
			ans++;//求一共交换ans次变为有序数列 
		}
	}
	int x,y;
	x=3*n-ans;
	if(x%2==0){//查看剩余交换是否为无用交换
		cout<<"Petr";
	}
	else{
		cout<<"Um_nik";
	}
	return 0;
}
```

---

## 作者：Aw顿顿 (赞：1)

一道很简单的题目。

## 题意

起初有两个 $1\sim n$ 的排列，一个由 Petr 打乱，一个由 Alex 打乱。告诉你最终序列，问是否是 Petr 打乱了，如果是输出 `Petr`，反之输出 `Um_nik`。

两者每次操作可以交换两个数，使得两者交换结果不一样的因素在于，Petr 可以交换 $3n$ 次而 Alex 可以交换 $7n+1$ 次。

## 解析

你会发现 $3n$ 和 $7n+1$ 的奇偶性显然不一样。每一次操作都会让序列的逆序对数量 $+1$ 或者 $-1$，而最后只要在结果处判断奇偶性即可。

逆序对如果 $O(n^2)$ 求，是会超时的。题解区中大多使用了树状数组，那么我这里给出一种归并排序实现的逆序对数量求取。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,b[1000005],ans;
int p[1000005];
void msort(int s,int t){
    if(s==t)return;
    int mid=(s+t)>>1;
    msort(s,mid);msort(mid+1,t);
    int i=s,k=s,j=mid+1;
    while(i<=mid&&j<=t){
        if(b[i]<=b[j]){
            p[k]=b[i];
            ++k;++i;
        }else{
            p[k]=b[j];
            ++k;++j;
            ans=(ans+mid-i+1);
        }
    }while(i<=mid){
        p[k]=b[i];
        ++k;++i;
    }while(j<=t){
        p[k]=b[j];
        ++k;++j;
    }for(int i=s;i<=t;i++)
	    b[i]=p[i];
}int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&b[i]);
	msort(1,n);
	if((ans-3*n)%2==0)puts("Petr");
	else puts("Um_nik");
	return 0;
}
```

不才拙笔，多多指教。

---

## 作者：201012280925LSY (赞：0)

## 题意
给出一个长度为 $N$ 的排列，能不能用 $3N$ 次交换或 $7N+1$ 次交换任意两个数使得一个自然数列变成这一个排列。

## 思路
我们抽象一下题意：对于这一个排列，能不能通过 $3N$ 次交换或 $7N+1$ 次交换使得它变成自然数列。

所以我们可以计算出变成自然数列的次数 $sum$，然后如果想要使它保持为这个自然数列。那么我们每次交换同样的两个数，就能保持数列，然后再用 $3N-sum$，判断是否为偶数。是为 `Petr`，不是为 `Um_nik`。

因为如果 $3N$ 为偶数，所以 $N$ 为偶数，则 $7N+1$ 为奇数。但如果 $3N$ 为奇数，所以 $N$ 为奇数，则 $7N+1$ 为偶数。所以 $3N-sum$ 不是偶数，那么 $7N+1-sum$ 必为偶数。

具体见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[1000010],sum,b[1000010];//b数组表示数i在第b[i]位
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],b[a[i]]=i;
	for(int i=1;i<=n;i++)//计算变成自然数列的次数
	{
		if(a[i]!=i)
		{
			long long h=b[i];//交换
			swap(a[h],a[i]);
			b[i]=i;
			b[a[h]]=h;
			sum++;
		}		
	}
	if((3*n-sum)%2==0)cout<<"Petr";//判断
	else cout<<"Um_nik";
	return 0;
}
```

---

## 作者：Akiyama_mzk (赞：0)

# Preface

安利[博客](https://www.luogu.com.cn/user/954640#article)与[大号](https://www.luogu.com.cn/user/954640#main)。

[前置芝士](https://www.luogu.com.cn/article/b75mv46d)。

# Introduction

首先，我们需要知道，交换序列的任意两元素，序列的逆序数的奇偶性必定发生改变。

证明：

令 $p_1<p_2$。

当 $p_2=p_1+1$ 时（交换相邻两个数），这一对数相对顺序改变，所以逆序对数加一或减一，逆序对奇偶性改变。

若不然，令 $l=|p_1-p_2|-1$，则先通过 $l+1$ 次操作将 $p_1$ 移动到 $p_2$ 位置上，再用 $l$ 次操作将 $p_2$ 移动到 $p_1$ 位置，共 $2l+1$ 次操作。

命题获证。

又因为 $3n$ 与 $7n+1$ 奇偶性不同，两人交换后的序列逆序数奇偶性也不同。

算出序列逆序数，判断奇偶性即可。

逆序对可用树状数组维护，时间复杂度 $O(n\log n)$。

# Code

```cpp
#include<bits/stdc++.h> 
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
	x=x*10+ch-'0';
	ch=getchar();
}
	return x*f;
}
void write(int x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
		write(x/10);
	putchar(x%10+'0');
	return;
}
int m,op,x,y;
long long last_val,now_val,k;
int a[1000001],rnk[1000001],tree[1000001],n;
int lowbit(int x){
	return (x)&(-x);
}
void update(int x,int d){
	while(x<=n){
		tree[x]+=d;
		x+=lowbit(x);
	} 
}
int query(int x){
	int sum=0;
	while(x){
		sum+=tree[x];
		x-=lowbit(x);
	}
	return sum;
}
long long ans;
bool cmp(int x,int y){
	if(a[x]==a[y]) return x>y;
	return a[x]>a[y];
}
signed main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	for(int i=n;i>=1;i--){
		ans+=query(a[i]); 
		update(a[i],1);
	}
	ans%=2;
	n&=1;
	if(ans==n){
		printf("Petr");
	}
	else printf("Um_nik"); 
	return 0;
}
```

---

## 作者：2021zjhs005 (赞：0)

> 交换序列中任意两个元素，就会使得序列的逆序对个数增加 $1$ 或减少 $1$（修改序列的奇偶性），仅当交换的两数 $a_i$，$a_j$ 满足 $a_i \ne a_j$。

对于任意 $i$，$j$，$a_i\ne a_j$ 是一定满足的，因为序列 $a$ 是 $1\sim n$ 的排列。

有了这些，我们可以发现：$3\times n$ 和 $7\times n + 1$ 的奇偶性不相同，具体如下：

- $n\bmod 2 =1 $，$3\times n$ 为奇数，$7\times n + 1$ 为偶数。

- $n\bmod 2 = 0$，$3\times n$ 为偶数，$7\times n + 1$ 为奇数。

因此，只要求出逆序对的个数为 $ans$，再判断 $ans$ 和哪个的奇偶性一样，答案就出来了。

可以用树状数组维护，时间复杂度为 $\mathcal O(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rrep(i,x,y) for(int i=x;i>=y;i--)
#define pr printf
#define lowbit(x) x & (-x)
inline int read() {
	int s = 0, w = 1;
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') w = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		s = (s << 1) + (s << 3) + (c ^ 48);
		c = getchar();
	}
	return s * w;
}
const int N = 5e5 + 10;
int n, ans, tree[N];
struct node {
	int num, pos;
};
node a[N];
inline bool cmp(node s1, node s2) {
	return s1.num < s2.num;
}


inline int query(int k) {
	int sum = 0;
	for (; k > 0; k -= lowbit(k)) sum += tree[k];
	return sum;
}
inline void update(int k) {
	for (; k <= n; k += lowbit(k)) tree[k]++;
}

signed main() {
	n = read();
	for (int i = 1; i <= n; ++i) {
		a[i].num = read();
		a[i].pos = i;//其实也可以不离散化。
	}
	stable_sort(a + 1, a + 1 + n, cmp);
	for (int i = n; i > 0; --i) {
		ans += query(a[i].pos - 1);
		update(a[i].pos);
	}
	if((ans & 1) == ((7 * n + 1) & 1)) pr("Um_nik\n");//和 Alex 操作次数的奇偶性相同，答案为 Um_nik。
    else pr("Petr\n");//否则答案为 Petr。
	return 0;
}
```

---

## 作者：Cerydra (赞：0)

学校比赛出了这题，说说做法。

想了想，发现如果你对两个元素进行交换操作两次，那么就等于没有换，结合 $3n$ 和 $7n + 1$，所以想到了奇偶性。

先用一个最优的策略求出交换次数：假如给出的序列第 $i$ 项是 $a_{i}$，你当前的序列是第 $i$ 项是 $b_{i}$，最优策略肯定是寻找一个 $j$，使得 $b_{j}=a_{i}$，然后把 $b_{i}$ 与 $b_{j}$ 交换。寻找 $j$ 的过程是 $O(n)$ 的，会炸，所以开了一个 $c$ 数组，方便寻找，作用是反向映射。$b_{i}=j$，$c_{j}=i$。

求出了交换次数就判定奇偶。因为 `Alex` 的操作数是 $7n + 1$，所以这两个交换次数的奇偶性肯定不一样。

#### 代码

[AC 记录](https://www.luogu.com.cn/record/150653261)

```
#include<bits/stdc++.h>
using namespace std;
int a[1000005],b[1000005],c[1000005];
signed main() {
	int n,ans=0;
	cin >> n;
	for(int i=1;i<=n;i++){
		cin >> a[i];
		b[i]=i;
		c[i]=i;
	}
	for(int i=1;i<=n;i++){
		if(a[i]==c[i])continue;
		swap(b[a[i]],b[c[i]]);
		c[b[c[i]]]=c[i];//修改
		c[i]=a[i];
		ans++;//更新答案
	}
	if(ans%2==3*n%2){
		cout<<"Petr";
	}else{
		cout<<"Um_nik";
	}
	return 0;
}
```

---

## 作者：I_will_AKIOI (赞：0)

我们发现 $3n$ 与 $7n+1$ 的奇偶性肯定是不同的。当 $n$ 为奇数时，$3n$ 为奇数、$7n+1$ 为偶数。当 $n$ 为偶数时则反过来。

我们考虑从奇偶性入手来解决此题。发现将这个排列排序所需要的步数的奇偶性是相同的。

我们假设最少需要 $n$ 步可以排序。如果我们当前的操作是“正确”的，则 $n$ 不变，否则因为我们多操作了一步，还得再用一步给他变回来，所以  $n\leftarrow n+2$。奇偶性不变。其实也很好理解：先用最少步数排序后，然后不断交换两个数来“消耗步数”，这里一定会进行偶数次交换操作，所以奇偶性不变。

接下来我们考虑如何给他排序。根据贪心算法，我们在第 $i$ 步时需要将 $i$ 这个数字放到 $a_i$ 上。当然，如果已经放好，则不需要操作。

所以用 $a$ 记录每个数，$vis$ 记录每个数的位置。每次操作将 $a_{vis_i}$ 放到 $a_i$ 上。然后交换他们的位置。这一步操作有点麻烦，需要细心模拟。

最后看 $n$ 的奇偶性和步数的奇偶性是否一致即可。

```
#include<bits/stdc++.h>
using namespace std;
int n,cnt,a[1000001],vis[1000001];
int main()
{
  ios::sync_with_stdio(0);
  cin>>n;
  for(int i=1;i<=n;i++) cin>>a[i],vis[a[i]]=i;//记录位置
  for(int i=1;i<=n;i++)
  {
  	if(a[i]!=i)
  	{
  	  swap(vis[i],vis[a[i]]);//交换两个数的位置
  	  swap(a[i],a[vis[a[i]]]);//由于前面交换了 vis，所以这里 vis[a[i]] 相当于 vis[i]
  	  cnt++;
	}
  }
  if(n%2==cnt%2) cout<<"Petr";//奇偶性相同
  else cout<<"Um_nik";
  return 0;
}
```

---

## 作者：caoshuchen (赞：0)

# [Petr and Permutations](https://www.luogu.com.cn/blog/caoshuchen/petr-and-permutations-zhong-zhuai)

## 题意

就是有**两个**序列，开始都是从 $1\to n$ 顺序排列，现在 Petr 对第一个序列进行 $3n$ 次操作，Alex 对第二个序列进行 $7n+1$ 次操作，每次都是将两个数互换位置。

现在给出了最终打乱结果，问是 Petr 打乱的还是 Alex 打乱的，若是 Petr 输出 `Petr` 否则输出 `Um_nik`。

## 思路

如果学过逆序对，最先想到的一般都是它，那么我们就先讲讲它的做法：

我们发现 $3n$ 与 $7n+1$ 的奇偶性不一样，那么这说明，我们只需要找到逆序对的奇偶特征即可，然后再根据 $3n$ 与 $7n+1$ 判断是谁打乱的。

首先我们想到，交换两个数时的情况与对应的奇偶特征，如下：

$$\{[1],2,3,4,5,6,[7]\}$$

$$\downarrow$$

$$\{7,2,3,4,5,6,1\}$$

此时我们发现，对于交换的两个数，小的那个交换后到右边，那么它前面所有一直到它原本的位置（包括原本位置）的所有元素都大于了它，所以要加上这些数，然后发现较大那个也是同理，但注意去重，不要算两次首尾，最终发现，假设交换的两个位置之间夹着的元素个数为 $x$，那么逆序对增加量为 $2x+1$ 则每次交换，逆序对奇偶性都会发生改变。

这完了吗？不，没完，其实这个证明是**错误的**！为什么呢？因为还有可能若干个交换的位置互相交叠，如 $1,5$ 换，$3,7$ 换，等等。当两个重叠时还好处理，但到了更多就很难证明了，所以我们使用代数的方法证明，如下：

$$\{...,a,...,b,...\}$$
$$\downarrow$$
$$\{...,b,...,a,...\}$$

请观察一下，我们其实可以发现，不关于 $a,b$ 的逆序对是不会改变的，而交换的前后，在这两个元素围出的区间以外，逆序对的个数是不变的，因为在区间之前的元素，大于 $a,b$ 的依然大于，位置也依然小于 $a,b$ 的；在区间之后的元素，小于 $a,b$ 的依然小于，位置也依然大于 $a,b$ 的，所以没有变化。

但在区间内，有什么样的变化呢？我们设：

在 $a,b$ 之间（不包括 $a,b$）的数的个数为 $len$

区间内**小于** $a$ 的个数为 $x$，则**大于**它的个数为 $len-x$

区间内**大于** $b$ 的个数为 $y$，则**小于**它的个数为 $len-y$

那么原本这个区间关于 $a,b$ 的逆序对个数为 $x+y$ 而交换后关于 $a,b$ 的逆序对个数就变为 $2len-(x+y)$ 其实这里我们已经看出来了，它的奇偶性不变，实在不行可以列个表，如下：

![表格](https://cdn.luogu.com.cn/upload/image_hosting/o1iobk8i.png)

所以奇偶性不变，最后别忘了，由于 $a,b$ 交换后，它们之间的逆序对关系也会改变：$a>b$ 时，转换后逆序对减一；$a<b$ 时，转换后逆序对加一。所以最终奇偶性是都会改变的。

所以我们只需要判断逆序对个数的奇偶性是否等于 $3n$ 的奇偶性即可，效率 $O(n\log_2n)$。

---

还有一种方法，主要思路来源于 @ [pufanyi](https://www.luogu.com.cn/user/84088) 的题解（感谢），但证明与推导过程有些差异，再此也是讲一下。

我们如果说能计算出你复原的次数，就可以直接进行判断奇偶性，不用再求逆序对了，因为对于每一种情况，它变换所需要的步数的奇偶性是唯一确定的，为什么呢？我想了一会，没有想到很好的思路，只能再用逆序对的奇偶变换来佐证：

我们想一下，如果说我们已经变出了一个序列，需要 $x$ 步，那么我们只需要不断的重复交换固定的两个元素 $2k$ 次，它的序列就依然会回复成现状，如下：

$$\{3, 5, 4, 7, 6, 2\}$$

$$\downarrow$$

$$\{3, 2, 4, 7, 6, 5\}$$

$$\downarrow$$

$$\{3, 5, 4, 7, 6, 2\}$$

如果我们转换到这个序列操作次数未用完，那就这样进行若干次这样的操作即可，直到操作次数用完，而我们发现操作次数奇偶性是不会改变的，所以可以直接对它进行判断。

那么会不会说：可以进行奇数次操作变回来呢？如果这样的话，那我们就无法判断是谁打乱而来的了！其实是不会发生的，你想想如果这样的话就没有答案了，谁都有可能，这题就是错题了，但还是给出一个让人信服的证明：

如果进行奇数次操作让它变回来了，那么它的逆序对奇偶性也就变换了奇数次，则最终逆序对奇偶性就发生了改变，那就很明显了：原本你的逆序对个数是奇数，转了一圈回来变偶数了，不可能的嘛。所以通过一个反证，我们说明了这件事。

所以我们只需要知道序列要变换多少次能变回成 $1\to n$ 即可。

我们可以设计一个数组 $t$ 存储每一个值目前所在的位置，然后依次从 $1\to n$ 交换位置 $t_i$，$i$ 上的数，然后更新 $t_{a_i}$ 与 $a_i$ 即可，如果 $t_i = i$ 那么就不用交换，也不用累计答案，否则就交换并累计，最后再进行判断，看看是谁打乱的即可，效率 $O(n)$。

## Code

### 思路 $1$

```c++
#include <bits/stdc++.h>
using namespace std;

int n;
int a[1000005];
int t[1000005];

int slv(int l, int r) {
	if (l + 1 >= r)
		return 0;
	int mid = (l + r) / 2;
	int ans = (slv(l, mid) + slv(mid, r)) % 2;
	for (int i = l, j = mid; i < mid; i++) {
		while (j < r && a[j] < a[i]) j++;
		ans = (ans + j - mid) % 2;
	}
	int cur = l;
	for (int i = l, j = mid; i < mid; i++) {
		while (j < r && a[j] < a[i]) t[cur++] = a[j++];
		t[cur++] = a[i];
	}
	for (int i = mid; i < r; i++)
		if (a[i] > a[mid - 1])
			t[cur++] = a[i];
	for (int i = l; i < r; i++)
		a[i] = t[i];
	return ans % 2;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		scanf("%d", a + i);
	int k = slv(1, n + 1);
	if (k % 2 == n % 2)
		cout << "Petr" << endl;
	else
		cout << "Um_nik" << endl;
	return 0;
}
```

### 思路 $2$

```c++
#include <bits/stdc++.h>
using namespace std;

int n;
int a[1000005];
int t[1000005];

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		scanf("%d", a + i), t[a[i]] = i;
	int k = 0;
	for (int i = 1; i <= n; i++) {
		if (t[i] != i) {
			int ai = a[i];
			k++, swap(a[i], a[t[i]]), swap(t[i], t[ai]);
		}
	}
	if (k % 2 == n % 2)
		cout << "Petr" << endl;
	else
		cout << "Um_nik" << endl;
	return 0;
}
```

---

