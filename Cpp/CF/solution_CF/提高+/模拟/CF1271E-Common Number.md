# Common Number

## 题目描述

At first, let's define function $ f(x) $ as follows: $ $$$ \begin{matrix} f(x) & = & \left\{ \begin{matrix} \frac{x}{2} & \mbox{if } x \text{ is even} \\ x - 1 & \mbox{otherwise } \end{matrix} \right. \end{matrix}  $ $ </p><p>We can see that if we choose some value  $ v $  and will apply function  $ f $  to it, then apply  $ f $  to  $ f(v) $ , and so on, we'll eventually get  $ 1 $ . Let's write down all values we get in this process in a list and denote this list as  $ path(v) $ . For example,  $ path(1) = \[1\] $ ,  $ path(15) = \[15, 14, 7, 6, 3, 2, 1\] $ ,  $ path(32) = \[32, 16, 8, 4, 2, 1\] $ .</p><p>Let's write all lists  $ path(x) $  for every  $ x $  from  $ 1 $  to  $ n $ . The question is next: what is the maximum value  $ y $  such that  $ y $  is contained in at least  $ k $  different lists  $ path(x) $ ?</p><p>Formally speaking, you need to find maximum  $ y $  such that  $ \\left| \\{ x ~|~ 1 \\le x \\le n, y \\in path(x) \\} \\right| \\ge k$$$.

## 说明/提示

In the first example, the answer is $ 5 $ , since $ 5 $ occurs in $ path(5) $ , $ path(10) $ and $ path(11) $ .

In the second example, the answer is $ 4 $ , since $ 4 $ occurs in $ path(4) $ , $ path(5) $ , $ path(8) $ , $ path(9) $ , $ path(10) $ and $ path(11) $ .

In the third example $ n = k $ , so the answer is $ 1 $ , since $ 1 $ is the only number occuring in all paths for integers from $ 1 $ to $ 20 $ .

## 样例 #1

### 输入

```
11 3
```

### 输出

```
5
```

## 样例 #2

### 输入

```
11 6
```

### 输出

```
4
```

## 样例 #3

### 输入

```
20 20
```

### 输出

```
1
```

## 样例 #4

### 输入

```
14 5
```

### 输出

```
6
```

## 样例 #5

### 输入

```
1000000 100
```

### 输出

```
31248
```

# 题解

## 作者：Lynkcat (赞：8)

看起来好像没有人写我这种阴间做法，场上调了 1.5h 已经自闭了。

有两种情况：

$ans$ 是 $n$ 二进制的一个前缀。

$ans$ 是 $n$ 二进制一个前缀将最后一个 $1$ 改为 $0$ 后往后加 $1$ 或 $0$ 。

第一种情况直接判断即可，方案数可以自行推导。

第二种情况枚举到一个 $1$ 后将其改为 $0$，然后往后能加 $1$ 就加否则判断能否加 $0$ 不行的话就退出，同样其中的方案数留给读者自行推导。

不难证明这两种情况涵盖了所有合法的值。

```c++
//QwQcOrZ yyds!!!
#include<bits/stdc++.h>
#define ll long long
#define F(i,a,b) for (int i=(a);i<=(b);i++)
#define R(i,a,b) for (int i=(a);i<(b);i++)
#define D(i,a,b) for (int i=(a);i>=(b);i--)
#define go(i,x) for (int i=head[x];i;i=e[i].nx)
#define IOS ios::sync_with_stdio(false)
#define mp make_pair
#define pb push_back
#define pa pair < int,int >
#define fi first
#define se second
#define re register
#define be begin()
#define en end()
#define sqr(x) ((x)*(x))
#define ret return puts("-1"),0;
#define put putchar('\n')
#define inf 1000000005
#define mod 998244353
#define int ll
//#define N
using namespace std;
inline char gc(){static char buf[1000000],*p1=buf,*p2=buf;return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;}
#define gc getchar
inline ll read(){char c=gc();ll su=0,f=1;for (;c<'0'||c>'9';c=gc()) if (c=='-') f=-1;for (;c>='0'&&c<='9';c=gc()) su=su*10+c-'0';return su*f;}
inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll x){write(x),putchar(' ');}
inline void writeln(ll x){write(x);putchar('\n');}
int n,m,a[105];
set<int>S;
signed main()
{
	n=read();m=read();
	for (int i=0;i<64;i++)
		a[i]=(n>>i)%2;	
	for (int i=0;i<64;i++)
	{
		int s=(1ll<<(i))-1;
		if (!a[i]) s+=(1ll<<(i))-1;
		s+=n-((n>>i)<<i)+1;
		int now=n>>i;
		if (s>=m)
		{
			S.insert((n>>i));
		}
		if (!a[i]) continue;
		s=(1ll<<(i))-1;
		if (a[i]) s+=n-((n>>i)<<i)+1;
		s+=((1ll<<i)-1)*2+1;
		int pp=(n>>(i+1))<<1;
		if (s>=m)
		{
			for (int now=i-1;now>=0;now--)
			{
				if (((1ll<<(now))-1)*2>=m) pp*=2,pp+=1;
				else
					if (((1ll<<(now+1))-1)*2>=m) pp*=2;
					else break;
			}
			S.insert(pp);
		}	
	}
	writeln(*S.rbegin());
}
/*

*/

```

---

## 作者：SevenDawns (赞：6)

[博客地址](https://www.cnblogs.com/huangchenyan/p/12045964.html)

------------

首先考虑画出不同函数值迭代转移的关系，要注意考虑连边是否能成立，也就是满不满足函数的定义域

![](https://cdn.luogu.com.cn/upload/image_hosting/sx3ht041.png)

首先观察上图，可以发现如果$y$是偶数，节点$y$的左子树存在

但如果$y$是奇数，节点$y$的左子树不存在，因为$y+1$是偶数，不满足$f(x)=x-1$的定义域

并且右子树的所有节点都存在，因为都是奇数，如下图

![](https://cdn.luogu.com.cn/upload/image_hosting/7u9e9fnm.png)

那么现在统计一个定值$y$在$1-n$中经过$y$的$path$数，就是以$y$为根这棵树结点值小于等于$n$的节点数

观察可以发现，这些节点的值有规律

对于$2^{k}y$级别，树上的范围为$2^{k}y$到$2^{k}y+2^{k+1}-1$

那么可以在$log$的时间求出来

奇数的也是同理，$2^{k}y$到$2^{k}y+2^{k}-1$

但题目要求的是最大的$y$

那么可以分奇数偶数分别二分求解



```cpp
#include <bits/stdc++.h>
#define ll unsigned long long
#define inf (int)1e9
#define m_k make_pair
using namespace std;
ll n,k,z[63],ans;
bool check(ll mid)
{
    if (mid==1)
      return 1;
    ll cnt=0;
    if (mid%2==1)
    {
        for (int i=0;i<=62;i++)
        {
            if (z[i]*mid>n)
              break;
            if (z[i]*mid+z[i]-1<n)
              cnt+=z[i];
            else
            {
                cnt+=n-z[i]*mid+1;
                break;
            }
        }
    }
    else
    {
        for (int i=0;i<=62;i++)
        {
            if (z[i]*mid>n)
              break;
            if (z[i]*mid+z[i+1]-1<n)
              cnt+=z[i+1];
            else
            {
                cnt+=n-z[i]*mid+1;
                break;
            }
        }
    }
    if (cnt>=k)
      return 1;
    else
      return 0;
}
int main()
{
    scanf("%lld%lld",&n,&k);
    if (k==n)
    {
        printf("1\n");
        return 0;
    }
    z[0]=1;
    for (int i=1;i<=62;i++)
      z[i]=z[i-1]*2;
    ll l,r;
    l=0;r=(n-1)/2;
    while (l<r)
    {
        ll mid=l+((r-l+1)>>1);
        if (check(2*mid+1))
          l=mid;
        else
          r=mid-1;
    }
    ans=2*l+1;
    l=0;r=n/2;
    while (l<r)
    {
        ll mid=l+((r-l+1)>>1);
        if (check(2*mid))
          l=mid;
        else
          r=mid-1;
    }
    ans=max(ans,2*l);
    printf("%lld\n",ans);
}
```


---

## 作者：Pengzt (赞：5)

[CF1271E](https://www.luogu.com.cn/problem/CF1271E)

简单题。

首先直接从 $k$ 入手是不好做的，于是从每个值进行考虑。

发现能到达 $x$ 的点有两种情况，分类讨论一下。

$x$ 为奇数时，上一个数一定是 $2x$。

$x$ 为偶数时，上一个数为 $x+1$ 或 $2x$。

奇数一次过后就会变为偶数，所以对偶数再推一步 $2x+2,2x+1,4x$。

发现前两项和后一项成倍数的关系，对前两项再做一遍，使得 $x$ 前面的系数相同 $2x+3,4x+4,4x+2$。把所有的数塞到一个集合里面就可以发现一些了：$\{x,x+1,2x,2x+1,2x+2,2x+3,4x+1,4x+2,4x+4\dots\}$。$4x$ 和 $2x$ 那里不是很像是因为还没有将所有的 $2x+k$ 再推一步。

结论就容易得到了，即对于偶数 $x$，$2^kx$ 这一层会有 $2^{k+1}$ 个数有贡献，暴力计算就可以。

显然的，在 $x$ 为偶数时是有单调性的。奇数同理。虽然当 $x$ 为偶数时，$x\in path_j$ 的 $j$ 的个数一定不劣于奇数的情况。但因为是求最后的 $x$ 的 $\max$，所以奇数是有可能成为答案的，两遍二分即可。

代码：
```cpp
ll n,k;
ll check(ll x){
	int base=0;ll res=0;
	if(x&1){
		int len=0;
		for(;(x<<base)<=n;base++,len++)res+=min((x<<base)+(1ll<<len)-1,n)-(x<<base)+1;
	}else{
		int len=1;
		for(;(x<<base)<=n;base++,len++)res+=min((x<<base)+(1ll<<len)-1,n)-(x<<base)+1;
	}
	return res;
}
int main(){
	cin>>n>>k;
	ll l=1,r=n/2+(n&1);
	while(l<=r){
		ll mid=(l+r)>>1;
		if(check(2*mid)>=k)l=mid+1;
		else r=mid-1;
	}
	ll res=r*2;
	l=1,r=n/2+(n&1);
	while(l<=r){
		ll mid=(l+r)>>1;
		if(check(2*mid-1)>=k)l=mid+1;
		else r=mid-1;
	}
	res=max(res,r*2-1);
	cout<<res<<"\n";
    return 0;
}
```

---

## 作者：TernaryTree (赞：4)

观察一棵按层编号的完全二叉树，发现结点 $x$ 的左儿子为 $2x$，右儿子为 $2x+1$（经典结论）。也就是说对于一个结点 $x$，它的父亲是 $\left\lfloor\dfrac x2\right\rfloor$。

摆两个结论：

- 一个值 $x$ 如果在这棵树上出现过，则其子树内所有结点一定会经过 $x$。

- 一个**偶数** $x$ 如果在这棵树上出现过，则 $x+1$ 的子树内所有结点一定会经过 $x$。

并且观察可以发现：

- 当 $x$ 为奇数时，任意结点 $y$ 如果不在 $x$ 子树内则 $y$ 不经过 $x$。

- 当 $x$ 为偶数时，任意结点 $y$ 如果既不在 $x$ 子树内又不在 $x+1$ 子树内则 $y$ 不经过 $x$。

所以一个值 $x$ 在表中出现的次数为：

$$
g(x)=
\begin{cases}
siz_x&(x\bmod 2=1)\\
siz_x+siz_{x+1}&(x\bmod 2=0)
\end{cases}
$$

---

需要快速计算 $siz_x$。

显然完全二叉树的任何子树皆为完全二叉树。则对于每层统计答案，并特殊计算最后一层答案即可。

```cpp
int solve(int x) {
    if (x == 0) return 4e18;
    if (x > n) return 0;
    int i = 1, t = 1; // 枚举 i 为二叉树上与原结点的深度差
    while ((x << i) <= n) {
        if (((x << i) | ((1ll << i) - 1)) > n) t += n - (x << i) + 1; // 最后一层
        else t += (1ll << i); // 中间层
        ++i;
    }
    return t;
}
```

---

最大值，使用二分。

注意到对于所有 $g(x)$ 不存在单调性，但是考虑 $siz_x$ 存在单调性，于是对奇数二分一次，对偶数二分一次即可。

```cpp
int l = 1, r = 1e18;
while (l <= r) {
    int y = l + r >> 1, z = solve(y << 1) + solve(y << 1 | 1);
    if (z >= k) l = y + 1; 
    else r = y - 1;
}
ans = max(ans, r << 1);
l = 1, r = 1e18;
while (l <= r) {
    int y = l + r >> 1, z = solve(y << 1 | 1);
    if (z >= k) l = y + 1; 
    else r = y - 1;
}
ans = max(ans, r << 1 | 1);
cout << ans << endl;
```

---

## 作者：formkiller (赞：3)

### Problem ：
- 给出 N 和 k 

- 定义函数f(x)为

$  f(x)=
\begin{cases}
{x-1}& {x \bmod  2==1}\\
x\; / \;2& {x \bmod  2==0}
\end{cases}$

- 定义一个数的路径 $path(x)$ 为 $x$ 不断执行 $f(x)$ 最后到达 $1$ 的过程

- 求一个数 $a$ 使得 $a$ 在 $path(x),x \in [1,N] $中出现次数大于等于 $k$ ，并使 $a$ 最大化



------------


### Solution :

不难理解，如果 $a$ 出现在 $path(x)$ ，那么 $a$ 也一定会出现在 $path(2  \cdot x)$ 中 ，当 $x \bmod 2 == 0$ 时， $a$ 也一定会出现在  $path(x+1)$  中

如果我们把他们的关系抽象理解，就会发现他们相当于一棵树， $x$ 的父亲就是 $f(x)$ ， $x$ 的一个儿子是 $2 \cdot x$ （如果 $x \bmod 2 == 0$ ， $x$ 的第二个儿子是 $x + 1$）

于是问题就转成了在树上求一颗子树使得子树的大小 $>=k$ 

我们先考虑如何计算以 $x$ 为根的子树，为了方便表达，我们记为 $calc(x)$ 

我们先来考虑 $2 \cdot x$ 的情况，因为  $2 \cdot x$ 一定是 $x$ 的儿子，并且把他们看成 $2$ 进制下的大小关系，他们就相当于一个左移右移一位的关系

如果我们把 $(x \cdot 2)$ 和 $(x \cdot 2 + 1)$ 关于 $x$ 作比较，可以发现  $(x \cdot 2)$ 等价于 $x$ 左移一位， $(x \cdot 2 + 1)$   等价于 $x$ 左移一位再 $+1$

如果去掉前导零，我们发现在 $(x)_2$ 的右边插入一个 $0/1$ ，就得到了
 $(x \cdot 2)_2$ 和 $(x \cdot 2 + 1)_2$ 
 
 这样一来，我们就相当于一直往 $(x)_2$ 右边插入 $0/1$ ，直到这个数大于 $N$

由于是在二进制意义下进行的操作，所以我们把 $N$ 和 $x$ 先拆开，同时记录他们的长度 $n $ 和 $m$ 

假设往 $x$ 的右边插入了 $k$ 位数字，那么 $x$ 的长度变为 $m + k$

我们这里分情况讨论：

- 当 $m + k < n$ 的时候，$x$ 的位数比 $N$ 的位数要小，所以无论插入的这些 $0/1$ 如何排列， 一定会有 $x$ $< N$ ，所以就会产生 $2^k$ 种可能性（即 $2^k$ 个点）

- 当 $m + k = n$ 的时候，我们考虑 $x$ 和 $N$ 的大小关系。我们发现如果把 $N$ 的前 $n$ 项单独组成一个数 $y$，那么 $x$ 和 $y$ 的位数相同。若原始的 $x$ 比 $y$ 要大，那么就算往 $x$ 的右边填入 $k$ 个 $0$，所得的数依然会比 $N$ 要大，因此他无法组成满足条件的数；若原始的 $x$ 比 $y$ 要小，那么就算往 $x$ 的右边填入 $k$ 个 $1$，所得的数依然会比 $N$ 要小，因此他可以得到 $2^k$ 个满足条件的数。

- 当 $m + k = n$ 且 $x = y$ 的时候，为了使所得的数不超过 $N$ ，填进去的数应该不大于 $N$ 的第 $m+1$ 到 $n$ 位

对于第三点举个栗子：

$x = (101)_2$

$N = (10110)_2$

所以满足条件的数有$(10100)_2$ $(10101)_2$ $(10110)_2$

等价于 $N$ 的 $m+1$ 到 $N$ 位的 $(10)_2$ 位的大小（当然要记得$+1$，因为有一个 $(00)_2$要算在里面）


对于 $x$ 是偶数的情况只要算完 $calc(x)$ 之后再加上 $calc(x+1)$即可

由于 $x$ 的奇偶性的差异，导致 $calc(x)$ 和 $calc(x+1)$ 差距很大，但同奇偶的 $calc(x)$ 和 $calc(x+2)$ 差异性较小，所以我们分别二分奇数和偶数，最后再取两者的最大值


------------


代码就只贴计算子树大小的部分，二分应该蛮好写的，就不贴了

~~昨晚Div 2死肝这道题，然后就掉分了。。。~~

### Code :

```cpp
//a数组代表N,在主程序里已经拆开了，b数组代表x，n是a数组的长短，m是b数组的长短
inline LL th(LL x) {return (x%2==0)?x/2:x-1;}
LL check(LL x)
{
	LL s=1;
	m=0;
	for (LL i=x;i;i>>=1) b[++m]=i%2; //拆开
	for (int i = 1; i <= m/2; ++i) swap(b[i],b[m-i+1]);
	LL w=1;
	for (int i = 1; i <= m; ++i)
	{
		if (w==1) 		w=(b[i]>a[i])?2:(b[i]==a[i]); //判断大小，w=2代表y>x,w=1代表y=x,w=0代表y<x,
	}
	if (w==1)
	{
 		LL ss=0,sss=1;		
		for (int i = m + 1; i <= n; ++i) ss=ss<<1|a[i],s+=sss,sss<<=1;
		s+=ss;
	}
	else
	{
 		 if (w==2) --w;
		LL ss=1;
		for (int i = m + 1; i <= n - w; ++i) ss<<=1,s+=ss;
	}
	if (!(x&1)) s+=check(x+1);
	return s;
}
```

---

## 作者：gyh20 (赞：3)

观察题面，可知，奇数的函数值是不降的，偶数的函数值也是不降的。

二分奇数和偶数，再用$log(n)$的时间求出当前的值(可以找规律)。

最后看奇数和偶数哪一个小即可。

```cpp
#include<cstdio>
#include<iostream>
#define re register
using namespace std;
unsigned long long n,k,ans,ans1;
int main(){
 scanf("%llu%llu",&n,&k);
 unsigned long long l=1,r=n/2;
 while(l<=r){
 	unsigned long long mid=((l+r)>>1),tmp,ll,q=0;
 	tmp=2;
 	ll=mid*2;
 	while(ll+tmp<=n){
 		ll<<=1;
 		q+=tmp;
 		tmp<<=1;
	 }
	 if(n>=ll)
	 q+=n-ll+1;
	 if(q>=k)l=mid+1,ans=mid*2;
	 else r=mid-1;
 }
 l=1;
 r=(n+1)/2;
  while(l<=r){
 	unsigned long long mid=((l+r)>>1),tmp,ll,q=0;
 	tmp=1;
 	ll=mid*2-1;
 	while(ll+tmp<=n){
 		ll<<=1;
 		q+=tmp;
 		tmp<<=1;
	 }
	 if(n>=ll)
	 q+=n-ll+1;
	 if(q>=k)l=mid+1,ans1=mid*2-1;
	 else r=mid-1;
 }
 if(ans>ans1)printf("%llu",ans);
 else printf("%llu",ans1);
}
```


---

## 作者：破壁人五号 (赞：2)

## 题意

- 定义 $f(x)$：

$$f(x)=\begin{cases}
\dfrac{x}{2}& x\equiv 0\pmod 2\\
x-1& \text{otherwise}
\end{cases}$$

- 显然对于正整数 $v$，反复对其求 $f$ 值最后会到达 $1$，把中途得到的所有 $f(v)$ 连同 $v$ 按顺序记为 $path(v)$，如 $path(15)=[15,14,7,6,3,2,1]$

- 问：在 $path(i)\ (1\leq i\leq n)$ 中出现至少 $k$ 次的数中最大的一个。

## 题解

考虑二进制数 $(\overline{S})_2$：
- 假如 $S$ 为奇数，$path(x)$ 包含 $S$ 的数只有 $x=(\overline{S\dots})_2$；
- 假如 $S$ 为偶数，则还要算上 $S'=S+1$ 对应的 $x=(\overline{S'\dots})_2$。

记 $g(S)$ 为 $[1,n]$ 中二进制下最高几位为 $S$ 的数的个数，则很容易求出 $g$：

```cpp
#define ll long long
ll calc(ll x){
    ll ans=0,t=1;
    while(x<=n){
        ans+=min(t,n-x+1);
        x<<=1;
        t<<=1;
    }
    return ans;
}
```

感性理解，$g$ 是单调的。所以这道题可以分奇数（判断 $g(i)$ 与 $k$ 的关系）和偶数（判断 $g(i)+g(i+1)$ 与 $k$ 的关系）二分。

二分奇数的必要性似乎不是很大，但不二分奇数的话应该要处理不少细节。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll getint(){
    ll ans=0,f=1;
    char c=getchar();
    while(c>'9'||c<'0'){
        if(c=='-')f=-1;
        c=getchar();
	}
    while(c>='0'&&c<='9'){
        ans=ans*10+c-'0';
        c=getchar();
    }
    return ans*f;
}
ll k,n;
ll calc(ll x){
    ll ans=0,t=1;
    while(x<=n){
        ans+=min(t,n-x+1);
        x<<=1;
        t<<=1;
    }
    return ans;
}
 
int main(){
    n=getint();
    k=getint();
    ll x=-1;
    {
        ll l=1,r=n/2,mid=0,ans=-1;
        while(l<=r){
            mid=l+r>>1;
            if(calc(mid*2)+calc(mid*2+1)>=k){
                ans=mid*2;
                l=mid+1;
            }else{
                r=mid-1;
            }
        }
        x=max(ans,x);
    }
    {
        ll l=1,r=(n+1)/2,mid=0,ans=-1;
        while(l<=r){
            mid=l+r>>1;
            if(calc(mid*2-1)>=k){
                ans=mid*2-1;
                l=mid+1;
            }else{
                r=mid-1;
            }
        }
        x=max(ans,x);
    }
    cout<<x;
    return 0;
}
```


---

## 作者：Find_Yourself (赞：1)

找规律。

我们看有哪些数的 $path$ 经过 $x$。

当 $x$ 为奇数时，有：$x,2x,2x+1,4x,4x+1,4x+2,4x+3...$

当 $x$ 为偶数时，有：$x,x+1,2x,2x+1,2x+2,2x+3,4x,4x+1...$

规律很明显，不解释。

因为当 $x$ 为奇数和 $x$ 为偶数时都分别具有单调性，所以可以做两次二分，再在 $O(\log n)$ 的复杂度内算出有多少个数的 $path$ 进过它即可。

总复杂度 $O(\log^2 n)$。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,k;
ll get(ll x){
  ll cnt=0;
  for(ll i=x,mi=(x%2?1:2);i<=n;i*=2,mi*=2)cnt+=min(mi,n-i+1);
  return cnt;
}
int main(){
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
  cin>>n>>k;
  ll l=1,r=n/2,ans=0,ans2=0;
  while(l<=r){
    ll mid=(l+r)/2;
    if(get(mid*2)>=k)ans=mid*2,l=mid+1;
    else r=mid-1;
  }
  l=0,r=(n-1)/2;
  while(l<=r){
    ll mid=(l+r)/2;
    if(get(mid*2+1)>=k)ans2=mid*2+1,l=mid+1;
    else r=mid-1;
  }
  cout<<max(ans,ans2)<<endl;
  return 0;
}

```


---

## 作者：caidzh (赞：1)

~~好像。。是一个很蠢的2E，20分钟不到就做完了~~

首先我们发现二进制意义下考虑$f$函数的含义会非常舒服

举个例子，比如$4(100)$这个数，它可以由：$100+'...'$得来，也可以由$101+'...'$（把它当成一个字符串拿来相加，得到另一个二进制数）

而奇数不存在第一种情况

注意到分奇偶后一个数可以由多少个数得到这玩意儿存在单调性，而题目问我们的是二分的经典问题，所以我们判断这题就是分奇偶二分一下

接下来的问题是：怎么计算一个数可以由多少个数得到

我们发现固定了数字位数后，接下来就是考虑$'...'$这个确定位数的数有几种取值，这非常容易，不再赘述

代码实现：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#define int LL
#define db double
#define INF 2147483647
#define LLINF 9223372036854775807
#define LL long long
using namespace std;
int inline read(){
    int num=0,neg=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')neg=-1;c=getchar();}
    while(isdigit(c)){num=(num<<3)+(num<<1)+c-'0';c=getchar();}
    return num*neg;
}
int n,k;
int f(int x){
	int ans=1,p=1;
	while((x<<1ll)<=n){
		if((x<<1ll)+p<=n)ans+=(p+1ll);
		else ans+=n-(x<<1ll)+1ll;
		x<<=1ll;p=p*2ll+1ll;
	}return ans;
}
int calc(int x){
	if(x&1)return f(x);
	else return f(x)+f(x|1ll);
}
int even(){
	int l=0,r=n/2ll;
	while(l<r){
		int mid=l+r+1ll>>1ll;
		if(calc(2ll*mid)>=k||mid==0)l=mid;
		else r=mid-1;
	}return 2ll*l;
}
int odd(){
	int l=0,r=(n-1ll)/2ll;
	while(l<r){
		int mid=l+r+1>>1;
		if(calc(2ll*mid+1ll)>=k)l=mid;
		else r=mid-1;
	}return 2ll*l+1ll;
}
signed main()
{
	n=read();k=read();int ans=0;
	ans=max(ans,even());ans=max(ans,odd());
	cout<<ans;return 0;
}
```


---

## 作者：TheShadow (赞：1)

# Solution

打出对于一个数 $k$ ，会对它有贡献的 $x$ 的表。

我们可以发下这样一个规律：

- 如果 $k$ 是奇数，那么对它有贡献的值被分为了若干段，其中第 $i$ 段的长度为 $2^{i-1}$ ，开头的值为 $k\cdot2^{i-1}$ 。

- 如果 $k$ 是偶数，那么对它有贡献的值被分为了若干段，其中第 $i$ 段的长度为 $2^i$ ，开头的值为 $k\cdot2^{i-1}$ 。

奇偶分开考虑。

我们设 $g(x)$ 为 $x$ 被包含的次数，显然对于奇数和偶数来说，都分别是单调递减的。

所以我们直接二分出最大的奇数和最大的偶数然后取个 $\max$ 即可。

# Code

```cpp
#include<bits/stdc++.h>
#define del(a,i) memset(a,i,sizeof(a))
#define ll long long
#define inl inline
#define il inl void
#define it inl int
#define ill inl ll
#define re register
#define ri re int
#define rl re ll
#define lowbit(x) (x&(-x))
#define INF 0x3f3f3f3f
using namespace std;
template<class T>il read(T &x){
	int f=1;char k=getchar();x=0;
	for(;k>'9'||k<'0';k=getchar()) if(k=='-') f=-1;
	for(;k>='0'&&k<='9';k=getchar()) x=(x<<3)+(x<<1)+k-'0';
	x*=f;
}
template<class T>il _print(T x){
	if(x/10) _print(x/10);
	putchar(x%10+'0');
}
template<class T>il print(T x){
	if(x<0) putchar('-'),x=-x;
	_print(x);
}
ll mul(ll a,ll b,ll mod){long double c=1.;return (a*b-(ll)(c*a*b/mod)*mod)%mod;}
it qpow(int x,int m,int mod){
	int res=1,bas=x;
	while(m){
		if(m&1) res=(1ll*res*bas)%mod;
		bas=(1ll*bas*bas)%mod,m>>=1;
	}
	return res;
}
ll n,k,ans;
inl bool chk_odd(ll lim){
	ll get=0,bas=1,val=lim*2+1;
	for(ri i=1;i<=60;++i,bas*=2){
		ll start=val*bas;
		double st=1.*val*bas;
		if(st>n) break;
		get+=min(bas,n-start+1);
	}
	return get>=k;
}
il Solve_Odd(){
	ll l=0,r=(n&1)?n/2:n/2-1;
	while(l<r){
		ll mid=(l+r)/2;
		if(chk_odd(mid+1)) l=mid+1;
		else r=mid;
	}
	if(l==r&&chk_odd(l))
		ans=max(ans,2*l+1);
}
inl bool chk_even(ll lim){
	ll get=0,bas=1,val=lim*2;
	for(ri i=1;i<=60;++i,bas*=2){
		ll start=val*bas;
		double st=1.*val*bas;
		if(st>n) break;
		get+=min(bas*2,n-start+1);
	}
	return get>=k;
}
il Solve_Even(){
	ll l=1,r=n/2;
	while(l<r){
		ll mid=(l+r)/2;
		if(chk_even(mid+1)) l=mid+1;
		else r=mid;
	}
	if(l==r&&chk_even(l))
		ans=max(ans,2*l);
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n),read(k);
	Solve_Odd(),Solve_Even();
	print(ans);
	return 0;
}
```


---

## 作者：1234567890sjx (赞：0)

Duel 到的，不到 $20$ min 切。首先考虑猜一手结论：若 $i-1$ 满足条件，则 $i$ 一定满足条件。但是这很显然是错的。

先考虑判断 $i$ 数是否是合法的。那么只需要计数 $1\sim n$ 中有多少个数的 $\text{path}$ 能够经过 $i$。

首先 $i\in\text{path}_i$。如果 $2\mid i$ 则 $i+1\in\text{path}_i$。

然后考虑 $j$ 能够到达 $i$ 的条件。（$j>i+1$）容易发现对 $j$ 执行一次操作之后：

+ 如果 $2\mid j$ 则 $j\leftarrow\frac{j}{2}$。
+ 如果 $2\nmid j$ 则 $j\leftarrow j-1$。（$1$）

在二进制上考虑：若 $j$ 二进制表示的最后一位是 $1$ 那么将这一位置为 $0$，否则删去这一位。倒过来思考，对于 $i$ 有哪些 $j$ 能到达。把 $i,j$ 都用二进制表示出来。除了上面提到的两个特殊情况，若 $i$ 能被 $j$ 所表示，则 $i$ 的二进制表示一定是 $j$ 的二进制表示的一个前缀。于是直接随便枚举一下当前 $j$ 二进制表示的长度然后直接 $O(1)$ 算出可以被表示的区间，就可以 $O(\log n)$ 判定答案了。

但是此时仍是 $O(n\log n)$ 的。考虑一开始提到的猜测，虽然她是错的，但是考虑到（$1$），发现偶数比奇数多情况，但是奇偶性相同的情况下单调性是存在的。于是对奇数偶数分别做二分，可以做到 $O(\log^2n)$ 通过该题。

```cpp
int n, k;
void run() {
    n = read(), k = read();
    int l = 2, r = (n - k + 1) / 2 * 2, best = 1;
    while (r - l >= 0) {
        int mid = (l / 2) + (r / 2) >> 1, cnt = 1, x = mid, nw = 1;
        x <<= 1, mid <<= 1;
        if (x % 2 == 0 && x != n) ++cnt, nw <<= 1; x <<= 1;
        while (x <= n) {
            int ff = x + (1ll << nw) - 1;
            if (ff <= n) cnt += (1ll << nw);
            else cnt += n - x + 1;
            x <<= 1; ++nw;
        }
        // cout << "qwq " << l << ' ' << r << ' ' << mid << ' ' << cnt << '\n';
        if (cnt >= k) best = mid, l = mid + 2;
        else r = mid - 2;
    }
    l = 3, r = (n - k + 1) / 2 * 2 + 1;
    if (r > n) r -= 2; while (r - l >= 0) {
        int mid = (l / 2) + (r / 2) >> 1, cnt = 1, x = mid, nw = 1;
        mid = mid << 1 | 1, x = x << 1 | 1;
        if (x % 2 == 0 && x != n) ++cnt, nw <<= 1; x <<= 1;
        while (x <= n) {
            int ff = x + (1ll << nw) - 1;
            if (ff <= n) cnt += (1ll << nw);
            else cnt += n - x + 1;
            x <<= 1; ++nw;
        }
        if (cnt >= k) best = max(best, mid), l = mid + 2;
        else r = mid - 2;
    }
    cout << best << '\n';
}
```

---

## 作者：fanypcd (赞：0)

感觉正向思考多少个数的 path 里有 $x$ 不太可行。

那么反过来，倒着模拟 $f(x)$ 的过程，即：

$f'(x)=\begin{cases} x\times2&x \bmod 2 = 1\\ \ x\times2\ or\ x+1&x \bmod 2 = 0 \end{cases}$

画一下，发现需要分 $x$ 是奇数 / 偶数的情况讨论。

---

- 若 x 形如 $2k + 1$：

	我们根据拓展到的数中 $k$ 的系数来分层：

	第零层：$x$
   
   第一层：$2x,2x+1$
   
   第二层：$4x,4x+1,4x+2,4x+3$
   
   $\cdots$
   
归纳一下：第 $i$ 层有自 $x \times 2^i$ 开始的连续 $2^i$ 个正整数。

---

- 若 $x$ 形如 $2k$：

	那就相当于有 $x,x+1$ 两个数分别进行形如 $x=2k+1$ 的拓展。容易发现它们能拓展到的数是不相同的。

---

于是我们可以设计 calc 函数计算 $x$ 按奇数的拓展方法（不能到 $x+1$）能拓展到的数的个数（$n$ 已经给定）。

1. 若 $x > n$，则返回 0。

2. 计算出最后一个形如 $x \times 2^{i+1}$ 的不超过 $n$ 的数对应的 $i$（可以直接用 ```i = floor(log2(n / x))``` 求得）。

3. 那么前面 $i$ 层共 $2^i-1$ 个数是可以全部拓展到的，计入答案。

4. 第 $i+1$ 层的 $2^i$ 个数中可能有部分超出范围。如果 $n \in [x \times 2^i,x \times 2^i + 2^i - 1]$，则能拓展到的最大值就是 $n$，个数为 $n - x \times 2^i + 1$；否则全部能拓展到，个数为 $2^i$。即在 $n-x\times 2^i + 1$ 和 $2^i$ 中取最小值。

---

具体实现如下：

```cpp
int calc(int x)
{
	if(x > n)
	{
		return 0;
	}//x 大于 n 显然没有一个数。
	int lg = floor(log2(n / x));//否则计算出最后一个形如 
	return ((1ll << lg) - 1) + min(n - x * (1ll << lg) + 1, (1ll << lg));
}
```

如果 $x$ 是奇数，那么 $x$ 能拓展到的数有 $calc(x)$ 个。

如果 $x$ 是偶数，那么 $x$ 能拓展到的数有 $calc(x) + calc(x+1)$ 个。

分答案为奇偶来二分即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline void read(int &x)
{
	x = 0;
	int f = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9')
	{
		f |= ch == '-';
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	x = f ? -x : x;
	return;
}
int n, k;
int calc(int x)
{
	if(x > n)
	{
		return 0;
	}
	int lg = floor(log2(n / x));
	return ((1ll << lg) - 1) + min(n - x * (1ll << lg) + 1, (1ll << lg));
}
signed main()
{
	read(n), read(k);
	int l, r, mid, ansodd = 1, anseve = 0;
	l = 0, r = n >> 1;
	while(l <= r)
	{
		mid = (l + r) >> 1;
		if(calc((mid << 1) + 1) >= k)
		{
			ansodd = (mid << 1) + 1;
			l = mid + 1;
		}
		else
		{
			r = mid - 1;
		}
	}
	l = 1, r = n >> 1;
	while(l <= r)
	{
		mid = (l + r) >> 1;
		if(calc(mid << 1) + calc((mid << 1) + 1) >= k)
		{
			anseve = mid << 1;
			l = mid + 1;
		}
		else
		{
			r = mid - 1;
		}
	}
	printf("%lld", max(ansodd, anseve));
	return 0;
}
```

---

