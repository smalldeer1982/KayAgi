# DIFERENC - DIFERENCIJA

## 题目描述

Mirko discovered what Slavko did in previous task, and decided to deal with something completely

# 题解

## 作者：YudeS (赞：5)

题目大意

一个序列的值被定义为，其中的最大值减最小值，给定一个序列，求给定序列的所有子序列的值的和



------------

也就是要求

$$\sum\limits_{i=1}^{n}\sum\limits_{j=i}^{n}\max\limits_{i\leqslant k\leqslant j}a_k-\min\limits_{i\leqslant k\leqslant j}a_k$$

这样看来$n^2$枚举区间是跑不掉了，$n<=3e5$又怎么过得了呢？

我们可以这样考虑：

我们把最大值和最小值拆开

$$\sum\limits_{i=1}^{n}\sum\limits_{j=i}^{n}\max\limits_{i\leqslant k\leqslant j}a_k-\sum\limits_{i=1}^{n}\sum\limits_{j=i}^{n}\min\limits_{i\leqslant k\leqslant j}a_k$$

如果能把两部分单独算出来也可以

如果我们只考虑一个数对那些区间产生影响仿佛会简单一点

以最大值为例

我们找到前面第一个比$a_i$大的，和后面第一个比$a_i$大的位置，设为$j1,j2$，发现只有$j1$到$j2$之间$a_i$才是最大值，那么$a_i$对答案的影响应为

$$a_i*\left[ i-(j1+1)+1\right]*\left[(j2-1)-i+1\right]$$

其中$\left[ i-(j1+1)+1\right]*\left[(j2-1)-i+1\right]$是这一段包含$i$的子区间个数，相当于以$i$为分界，在左部分选一个左端点，在右边选一个右端点；

这当然包含了$[i,i]$这个区间，但因为算最小值时也会算到，并不会产生影响

那我们的主要问题就是如何求解$j1$和$j2$了

听起来可二分

这种问题我们可以用单调栈$O(n)$处理

对于求最大值，我们维护一个单调递减的栈，每个数前面第一个比它大的数，就是适当弹完栈后的栈顶，而当一个数被弹栈时，就可以计算贡献，因为它后面第一个比它大的数就是，将它弹栈的$a_i$

时间复杂度是$O(n)$

记得要开$longlong$

$Code$
```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define ll long long
using namespace std;

const int N=300005;

int n;
int a[N];
int st[N],top,w[N];
ll ans;

inline int read()
{
	int x=0,fl=1;char st=getchar();
	while(st<'0'||st>'9'){ if(st=='-')fl=-1; st=getchar();}
	while(st>='0'&&st<='9') x=x*10+st-'0',st=getchar();
	return x*fl;
}

int main()
{
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	
	top=1;
	st[1]=1;
	a[n+1]=100000001; //加入一个极大值，保证最后栈被弹空 
	for(int i=2;i<=n+1;i++)
	{
		if(a[i]<=a[st[top]])
		{
			w[i]=st[top]; //w[]表示前面第一个比它大的位置 
			st[++top]=i;
		}
		else
		{
			while(top>0&&a[st[top]]<a[i]) //适当弹栈 
			{
				ans+=(ll)a[st[top]]*(st[top]-w[st[top]]-1+1)*(i-1-st[top]+1); //计算贡献 
				top--;
			}
			w[i]=st[top];
			st[++top]=i;
		}
	}
	
	top=1;
	memset(w,0,sizeof w);
  	st[1]=1;
  	a[n+1]=-1;
	for(int i=2;i<=n+1;i++)
	{
		if(a[i]>=a[st[top]])
		{
			w[i]=st[top];
			st[++top]=i;
		}
		else
		{
			while(top>0&&a[st[top]]>a[i])
			{
				ans-=(ll)a[st[top]]*(st[top]-w[st[top]]-1+1)*(i-1-st[top]+1);
				top--;
			}
			w[i]=st[top];
			st[++top]=i;
		}
	}
	
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：rui_er (赞：4)

~~我绝不会告诉你们这题与 P6503 是双倍经验的~~，好了，不扯了，下面开始正文。

这题要求 $\sum_{i=1}^n\sum_{j=i}^n\max_{i\le k\le j}a_k-\min_{i\le k\le j}a_k$，看到最小值与最大值，想到单调栈。

单调栈具体可不可以呢？当然是可以的。我们这里同时维护两个单调栈，递增和递减，就可以了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 3e5+5;

ll n, a[N], x[N], y[N], S, ans;
stack<ll> mi, ma;

int main()
{
    scanf("%lld", &n);
    for(ll i=1;i<=n;i++) scanf("%lld", &a[i]);
    mi.push(a[1]);
    ma.push(a[1]);
	x[1] = y[1] = 1;
	ans = S = 0;
    for(ll i=2;i<=n;i++)
	{
        ll tmp = 1;
        while(!mi.empty() && mi.top() <= a[i])
		{
			S -= mi.top() * x[mi.size()];
			tmp += x[mi.size()];
			mi.pop();
		}
		mi.push(a[i]);
		x[mi.size()] = tmp;
		S += a[i] * tmp;
        tmp = 1;
        while(!ma.empty() && ma.top() >= a[i])
		{
			S += ma.top() * y[ma.size()];
			tmp += y[ma.size()];
			ma.pop();
		}
		ma.push(a[i]);
		y[ma.size()] = tmp;
		S -= a[i] * tmp;
        ans += S;
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：Martian148 (赞：2)

# Link
[SP10622 DIFERENC - DIFERENCIJA](https://www.luogu.com.cn/problem/SP10622)

# Solve

我们可以把最大值和最小值分开来考虑，于是对于每个$a[i]$，我们统计出$a[i]$作为最大值和最小值的范围，从而算出$a[i]$对答案的贡献

$pre\underline{~}min$表示前面第一个比$a[i]$小的，$nxt\underline{~}min$表示后面第一个比$a[i]小的$，那么$a[i]$作为$max$的范围就是$pre\underline{~}min+1~nxt\underline{~}min-1$，$pre$和$nxt$数组用单调栈很容易处理出来，对答案的贡献就是$(i-pre\underline{~}min) \ast (nxt\underline{~}max-i)\ast a[i]$

计算$min$的时候同理

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=300005,INF=1<<30;
int N,pre_min[maxn],pre_max[maxn],nxt_min[maxn],nxt_max[maxn],top,c[maxn];
LL ans;
struct AS{
	int x,id;
}a[maxn],p[maxn];
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch<='9'&&ch>='0')ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
int main(){
	freopen("diferencija.in","r",stdin);
	freopen("diferencija.out","w",stdout);
	N=read();
	for(int i=1;i<=N;i++)a[i].x=read(),a[i].id=i;
	p[top=1]=(AS){0,0};for(int i=1;i<=N;i++){while(top>0&&p[top].x>=a[i].x)top--;pre_min[i]=p[top].id;p[++top]=a[i];}
	p[top=1]=(AS){INF,0};for(int i=1;i<=N;i++){while(top>0&&p[top].x<=a[i].x)top--;pre_max[i]=p[top].id;p[++top]=a[i];}
	p[top=1]=(AS){0,N+1};for(int i=N;i;i--){while(top>0&&p[top].x>a[i].x)top--;nxt_min[i]=p[top].id;p[++top]=a[i];}
	p[top=1]=(AS){INF,N+1};for(int i=N;i;i--){while(top>0&&p[top].x<a[i].x)top--;nxt_max[i]=p[top].id;p[++top]=a[i];}
	for(int i=1;i<=N;i++){ans+=((LL)(nxt_max[i]-i)*(i-pre_max[i])-(LL)(nxt_min[i]-i)*(i-pre_min[i]))*(LL)a[i].x;}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：辰星凌 (赞：2)

# **【题解】Diferenc-Diferencija [SP10622]**

[广告](https://www.cnblogs.com/Xing-Ling/p/11627826.html)

**传送门：[$\text{Diferenc-Diferencija}$](https://www.luogu.org/problem/SP10622) [$\text{[SP10622]}$](https://www.luogu.org/jump/spoj/10622)**

## **【题目描述】**

**序列的值**被定义成其中**最大的元素**减去**最小的元素**。如序列 $(3,1,7,2)$ 的值为 $7-1=6$, 序列 $(42,42)$ 的值为 $42-42=0$。

现给定一长为 $n$ 的序列 $a$，求出**所有连续子序列**的值的和。


-------

## **【分析】**

先将子区间的右端点固定为 $r$，此时一共有 $r$ 个左端点 $(l \in [1,r])$ 可与之组成连续子序列，用 $f_1[l]$ 表示 $max \{a[j]\}(j \in [l,r])$ ，$f_2[l]$ 表示 $min \{a[j]\}(j \in [l,r])$ 。于是以 $i$ 为右端点 $r$ 的子区间贡献和为 $\sum_{l=1}^{r} (f_1[l]-f_2[l])$，即 $\sum_{l=1}^{r} f_1[l] - \sum_{l=1}^{r} f_2[l]$ 。我们可以分开算 $f_1,f_2$ 的总和。

当右端点移至 $r+1$ 时，需要用 $a[r+1]$ 来更新 $f_1,f_2$，可以直接扫描 $[1,r]$，但时间不过不了关。

随着 $l$ 的减小，$f_1[l]=max(a[l],f_1[l+1])$，可以发现 $f_1[l]$ 是单调不下降的，同理 $f_2[l]$ 单调不上升。

随着 $r$ 的增大，$f_1[l]=max(f_1[l],a[r+1])$，可以发现 $f_1[l]$ 仍是单调不下降的，同理 $f_2[l]$ 单调不上升。

然后我们就会发现一个现象：每次新加进来一个数 $a[r+1]$ 时，它会将以 $r+1$ 结尾的一段连续的区间 $f_1[l],f_2[l](l \in [?,r+1])$ 全部赋值为 $a[r+1]$，而且被覆盖掉的原数对这之后的区间不再有任何贡献。

于是我们可以用两个单调栈分别维护 $f_1,f_2$，由于下标也是单调递增，所以可以将 $f$ 值相同的合并起来，用 $g$ 记录 $f$ 相同的下标个数，另设一个变量 $S$ 表示以 $i$ 为右端点的贡献和，当加入新的 $a[r]$ 时就不断弹走队尾直至保持单调时结束，同时更新 $S$，最后累加答案即可。

## **【Code】**

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=3e5+2;
int n,t1,t2,a[N],f1[N],f2[N],g1[N],g2[N];LL S,ans;
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
int main(){
    in(n);
    for(Re i=1;i<=n;++i)in(a[i]);
    f1[++t1]=a[1],f2[++t2]=a[1],g1[t1]=g2[t2]=1,ans=S=0;//初始化入队
    for(Re i=2;i<=n;++i){
        Re tmp=1;//f1[i]和f2[i]都一定会被覆盖，所以初始化为1
        while(t1&&f1[t1]<=a[i])S-=(LL)f1[t1]*g1[t1],tmp+=g1[t1--];//更新最大值
        f1[++t1]=a[i],g1[t1]=tmp,S+=(LL)a[i]*tmp;
        tmp=1;
        while(t2&&f2[t2]>=a[i])S+=(LL)f2[t2]*g2[t2],tmp+=g2[t2--];//更新最小值
        f2[++t2]=a[i],g2[t2]=tmp,S-=(LL)a[i]*tmp;
        ans+=S;//累加答案
    }
    printf("%lld\n",ans);
    return 0;
}
```



---

## 作者：__Star_Sky (赞：1)

## Description
求 $\sum\limits_{i=1}^{n}\sum\limits_{j=i}^{n}(\max\limits_{k=i}^{j}a_k-\min\limits_{k=i}^{j}a_k)$。

其中 $n\le3\times 10^{5}$。
## Solution
### 解法一
$O(n^2)$ 的朴素算法是很容易想到的：首先外层循环枚举每个左端点，内层循环枚举右端点的同时维护区间内的最大值和最小值即可。

这样的朴素算法很难继续优化，主要是因为枚举的是区间。区间个数太多并且很难一起处理。于是可以考虑枚举每一个数的贡献。

显然有
$$\sum\limits_{i=1}^{n}\sum\limits_{j=i}^{n}(\max\limits_{k=i}^{j}a_k-\min\limits_{k=i}^{j}a_k)$$
$$=\sum\limits_{i=1}^{n}\sum\limits_{j=i}^{n}\max\limits_{k=i}^{j}a_k-\sum\limits_{i=1}^{n}\sum\limits_{j=i}^{n}\min\limits_{k=i}^{j}a_k$$
因此原问题可以分成最大值之和与最小值之和两个几乎等价的子问题，这里只讨论最大值的部分。对于每个数 $a_i$，能产生贡献的区间只有 $[l_i+1,r_i-1]$，其中 $l_i$ 表示 $a_i$ 左边第一个大于 $a_i$ 的数的下标，$r_i$ 表示 $a_i$ 右边第一个大于 $a_i$ 的数的下标。在这个区间内所有包含 $a_i$ 的子区间的区间最大值都是 $a_i$。这样的子区间共有 $(i-l_i)\times(r_i-i+1)$ 个，因此 $a_i$ 能产生的贡献就是 $a_i\times(i-l_i)\times(r_i-i+1)$。使用单调栈即可在 $O(n)$ 的时间内求出 $l_i$ 和 $r_i$。

最小值的部分同理。

时间复杂度 $O(n)$。

### 解法二
考虑动态规划。这里我们仍然是只讨论最大值的部分。设 $f_i$ 表示所有以 $a_i$ 结尾的子序列中的最大值的和。状态转移方程:
$$f_i=f_{l_i}+(i-l_i)\times a_i$$
其中 $l_i$ 表示 $a_i$ 左边第一个大于 $a_i$ 的数的下标。如果不存在这样的数，$l_i$ 就等于 $0$。根据 $l_i$ 的定义，显然有 $a_i=\max\limits_{j=l_i+1}^{i}a_j$，也就是说，所有左端点位于 $[l_i+1,i]$，右端点为 $i$ 的子序列中的最大值都是 $a_i$，$a_i$ 的贡献就是 $(i-l_i)\times a_i$。由于 $a_i<a_{l_i}$，$a_i$ 不会对左端点位于 $[1,l_i]$ 的子序列产生任何影响，那一部分的贡献就是 $f_{l_i}$。

在枚举 $i$ 的同时用单调栈维护一下 $l_i$ 即可。最小值的部分同理。

时间复杂度 $O(n)$。

这里给出了解法二的代码实现。
## Code
```
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N=3e5+10;
const int INF=0x3f3f3f3f;
int a[N];
int sta[N],top;
LL f[N];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	top=0,a[0]=INF;
	LL ans=0;
	for(int i=1;i<=n;i++)
	{
		while(a[i]>=a[sta[top]]) top--;
		LL x=sta[top];
		f[i]=f[x]+(i-x)*a[i],ans+=f[i];
		sta[++top]=i;
	}
	top=0,a[0]=0;
	memset(f,0,sizeof(f));
	for(int i=1;i<=n;i++)
	{
		while(a[i]<=a[sta[top]]) top--;
		LL x=sta[top];
		f[i]=f[x]+(i-x)*a[i],ans-=f[i];
		sta[++top]=i;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：reclusive (赞：1)

[my blog](https://www.cnblogs.com/reclusive2007/p/17755886.html)

## 题目描述

给出一个长度为 $n$ 的序列 $a_i$，求出下列式子的值：

$$\sum_{i=1}^n \sum_{j=i}^n (\max \limits_{i \le k \le j} a_k-\min \limits_{i \le k \le j}a_k)$$

即定义一个子序列的权值为序列内最大值与最小值的差。求出所有连续子序列的权值和。

## 具体思路

暴力思路很好想，就是按照式子来打，然后区间最大值和区间最小值可以用数组预处理一下。

时间复杂度：$O(n^2)$。

那么我们发现，如果我们的两个求和不拆掉那么时间复杂度就不正确，那么思路就很显然：计算每个 $a_i$ 算了多少遍。

可以考虑将 $a_i$ 看成一个宽度为 $1$，高度为 $a_i$ 的矩形。

![image](https://cdn.luogu.com.cn/upload/image_hosting/p66ictq4.png?x-oss-process=image)


如图所示，我们来考虑上图中红色部分作为最大值被计算了多少次。

- 当 $i=2$，当 $j=3,4$ 时 $a_3$ 被计算了一次。

- 当 $i=3$，当 $j=3,4$ 时 $a_3$ 被计算了一次。

那我们发现，$i$ 这一层循环 $a_k$ 被计算的次数是 $k$ 到上一个比它大的位置，而 $j$ 这一层循环 $a_k$ 被计算的次数时 $k$ 到下一个比它大的位置。

设 $i$ 这层循环计算的次数是 $l_k$，$j$ 这层循环计算的次数是 $r_k$。

$$ans=\sum_{k=1}^n l_k \times r_k \times a_k$$

如果我们暴力枚举每一个点，然后暴力找上一个比它大的位置以及下一个比它大的位置，时间复杂度：$O(n^2)$。

这不没优化吗？

上面这个图，显然就很有单调栈的味道。

从左往右依次枚举每一个点，维护一个单调下降的栈，如果当前的点比栈顶要大，那么更新栈顶的信息，同时将栈顶踢出栈。

然后我们就愉快的解决了这个问题。

维护最小值也是同样的道理。

时间复杂度：$O(n)$。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5;
const int inf=0x3f3f3f3f;
int top,sta[N],l[N],r[N],a[N];
signed main(){
	int n;scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	top=1;sta[top]=1;
	l[1]=1;
	for(int i=2;i<=n;i++){
		while(top&&a[i]>a[sta[top]]){
			r[sta[top]]=i-sta[top];
			top--;
		}
		l[i]=i-sta[top];
		sta[++top]=i;
	}
	a[n+1]=inf;
	while(top&&a[n+1]>a[sta[top]]){
		r[sta[top]]=n+1-sta[top];
		top--;
	}
	int maxn=0;
	for(int i=1;i<=n;i++){
		maxn=maxn+l[i]*r[i]*a[i];
	}
	top=1;sta[top]=1;
	l[1]=1;
	for(int i=2;i<=n;i++){
		while(top&&a[i]<a[sta[top]]){
			r[sta[top]]=i-sta[top];
			top--;
		}
		l[i]=i-sta[top];
		sta[++top]=i;
	}
	a[n+1]=0;
	while(top&&a[n+1]<a[sta[top]]){
		r[sta[top]]=n+1-sta[top];
		top--;
	}
	int minn=0;
	for(int i=1;i<=n;i++){
		minn=minn+l[i]*r[i]*a[i];
	}
	printf("%lld",maxn-minn);
	return 0;
}
```

---

## 作者：Durancer (赞：1)

#### 前言

用单调栈做即可，有一个很妙的方法，设一个有大到小的单调栈，求最大值的时候正常求，当求最小值的时候，可以考虑把数组全部取反，变成反向的求最大值，代码量减少

#### 思路

题意可以转化为

$$\sum_{i=1}^{n}\sum_{j=i}^{n} max_{i\leq k \leq j} \ a_k-\sum_{i=1}^{n}\sum_{j=i}^{n} min_{i\leq k \leq j} \ a_k$$

那么如何用一个从小到大的单调栈来维护他呢

首先，一个一个加是不现实的，所以要考虑一段一段的加进去，用单调栈来维护一段内的最大值最小值

这里仅仅叙述最大值和的求法，因为最小值和用相反的数组来求，所以原理是一模一样的

1、考虑出栈时候的操作

因为入栈是按照顺序入栈的，所以所在的栈的位置越靠前，出现的就越早，并且出现时间是按照升序排列的

那么假设栈顶元素小于当前的元素，那么从栈顶元素到当前元素这一段内的最大值可以用当前的元素来表示。

那么此时，就要考虑把栈第二的元素到栈顶元素这一段用栈顶元素当最大值来表示的值给删去，因为从栈顶第二的元素到当前元素的这一段位置来说，可以用当前元素来表示，所以就要加上（当前位置-第二元素位置） $\times $ 当前元素值。

那么根据这个来一步步用乘法的方式来求得最大值和最小值的和。

#### 代码

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<map>
#include<cmath>
#define int long long
using namespace std;
const int N=3e5+9;
int ans=0,mid;//作为中介 
int a[N];
int n;
int q[N],head=1;
int stk[N];
int calc()
{
    head=1;
    int now=0;
    int sum=0;
    for(int i=1;i<=n;i++)
    {
        while(head>1&&a[q[head]]<a[i])
        {
            now-=(q[head]-q[head-1])*a[q[head]];
            head--;//不为最大值，不扩展了 
        }
        now+=(i-q[head])*a[i];//求出这个可以做多长时间的最大值
        sum+=now;
        q[++head]=i;//添进去 
    }
    return sum;
}
signed main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
        scanf("%lld",&a[i]);
    ans+=calc();
    for(int i=1;i<=n;i++)
        a[i]*=(-1);
    ans+=calc();//最小值变成最大值 
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：Silent_E (赞：1)

分治思想，找区间最大以及它的位置，用线段树或st表维护，计算贡献后划分成更小区间，递归进行。复杂度$O(nlog n)$（虽然有$O(n)$的单调栈做法。。。）
```cpp
//线段树写法
#include<cstdio>
#include<cstdlib>
#define int long long
#define ll long long
const int N = 300000 + 5; 
const int INF = 0x7fffffff;
inline int read(){
	int f = 1, x = 0; char ch;
	do { ch = getchar(); if (ch == '-') f = -1; } while (ch < '0' || ch > '9');
	do {x = (x << 3) + (x << 1) + ch - '0'; ch = getchar(); } while (ch >= '0' && ch <= '9'); 
	return f * x;
}
inline void hand_in() {
	freopen("diff.in", "r", stdin);
	freopen("diff.out", "w", stdout);
}

struct Sakura {
	ll val;
	int pos;
};

inline ll max(ll a, ll b) { return a < b ? b : a; }

inline ll min(ll a, ll b) { return a < b ? a : b; } 

int n; ll sum;
struct Segment_Tree {
	struct Node {
		int l, r;
		int mn, mx;
		int p_mn, p_mx;
	}tr[N << 2];

	#define ls (p << 1)
	#define rs ((p << 1) | 1)	

	inline void push_up(int p) {
		if (tr[ls].mx > tr[rs].mx) {
			tr[p].mx = tr[ls].mx, tr[p].p_mx = tr[ls].p_mx;
		}
		else {
			tr[p].mx = tr[rs].mx, tr[p].p_mx = tr[rs].p_mx;
		}
		
		if (tr[ls].mn < tr[rs].mn) {
			tr[p].mn = tr[ls].mn, tr[p].p_mn = tr[ls].p_mn;
		}
		else {
			tr[p].mn = tr[rs].mn, tr[p].p_mn = tr[rs].p_mn; 
		}
	}

	inline void build(int p, int l, int r) {
		tr[p].l = l, tr[p].r = r;
		if (tr[p].l == tr[p].r) {
			tr[p].mn = tr[p].mx = read();
			tr[p].p_mn = tr[p].p_mx = l;
			return;
		}
		int mid = (l + r) >> 1;
		build(ls, l, mid), build(rs, mid + 1, r);
		push_up(p);
	}

	inline Sakura ask_mx(int p, int l, int r) {
		if (l <= tr[p].l && tr[p].r <= r) {
			Sakura tp;
			tp.val = tr[p].mx, tp.pos = tr[p].p_mx;
			return tp;
		}
		int mid = (tr[p].l + tr[p].r) >> 1;
		Sakura s, tps;
		s.val = 0;
		if (l <= mid) {
			tps = ask_mx(ls, l, r);
			if (tps.val > s.val) s = tps;
		}
		if (r > mid) {
			tps = ask_mx(rs, l, r);
			if (tps.val > s.val) s = tps;
		}
		return s;
	}

	inline Sakura ask_mn(int p, int l, int r) {
		if (l <= tr[p].l && tr[p].r <= r) {
			Sakura tp;
			tp.val = tr[p].mn, tp.pos = tr[p].p_mn;
			return tp;
		}
		int mid = (tr[p].l + tr[p].r) >> 1;
		Sakura s, tps;
		s.val = INF;
		if (l <= mid) {
			tps = ask_mn(ls, l, r);
			if (tps.val < s.val) s = tps;
		}
		if (r > mid) {
			tps = ask_mn(rs, l, r);
			if (tps.val < s.val) s = tps;
		}
		return s;
	}

	inline void find(int l, int r) {
		if (l >= r) return;
		Sakura s = ask_mx(1, l, r);
		sum += s.val * (ll)((r - s.pos + 1) * (s.pos - l + 1) - 1);
		find(l, s.pos - 1), find(s.pos + 1, r); 
	}

	inline void delt(int l, int r) {
		if (l >= r) return;
		Sakura s = ask_mn(1, l, r);
		sum -= s.val * (ll)((r - s.pos + 1) * (s.pos - l + 1) - 1);
		delt(l, s.pos - 1), delt(s.pos + 1, r);
	}
}sg;

signed main(){
//	hand_in();
	n = read();
	sg.build(1, 1, n);
	sg.find(1, n);
//	printf("%lld\n", sum);
	sg.delt(1, n);
	printf("%lld\n", sum);
	return 0;
}
```
单调栈就维护每个点向前（向后）第一个比它大（小）的位置在哪，然后对每个点统计它的贡献。
```cpp
//单调栈写法
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define ll long long
#define ull unsigned long long
#define debug() puts("FBI WARNING!")
using namespace std;
const int P1 = 1926715;
const int P2 = 2333737;
const int N = 300000 + 5; 
const int BASE = 2333;
const int INF = 0x7fffffff;
inline int read(){
	int f = 1, x = 0; char ch;
	do { ch = getchar(); if (ch == '-') f = -1; } while (ch < '0' || ch > '9');
	do {x = (x << 3) + (x << 1) + ch - '0'; ch = getchar(); } while (ch >= '0' && ch <= '9'); 
	return f * x;
}
inline void hand_in() {
	freopen("dif.in", "r", stdin);
	freopen("dif.out", "w", stdout);
}

int n, a[N], sta[N], top, l[N], r[N];
ll sum;
int main(){
//	hand_in();
	n = read();
	for (int i = 1;i <= n; ++i) a[i] = read();

	a[0] = a[n + 1] = INF;	

	top = 0, sta[0] = 0;
	for (int i = 1;i <= n; ++i) {
		while (top && a[sta[top]] <= a[i]) top --;
		l[i] = i - sta[top];
		sta[++top] = i;
	}
	top = 0, sta[0] = n + 1;
	for (int i = n;i >= 1; --i) {
		while (top && a[sta[top]] < a[i]) top --;
		r[i] = sta[top] - i;
		sta[++top] = i;
	}
	for (int i = 1;i <= n; ++i) sum += (ll)a[i] * l[i] * r[i];

	top = 0;
	a[0] = a[n + 1] = -INF;
	sta[0] = 0;
	for (int i = 1;i <= n; ++i) {
		while (top && a[sta[top]] >= a[i]) top --;
		l[i] = i - sta[top];
		sta[++top] = i;
	}

	top = 0;
	sta[0] = n + 1;
	for (int i = n;i >= 1; --i) {
		while (top && a[sta[top]] > a[i]) top --;
		r[i] = sta[top] - i;
		sta[++top] = i;
	}

	for (int i = 1;i <= n; ++i) sum -= (ll)a[i] * l[i] * r[i];

	printf("%lld", sum);
	return 0;
}
```

---

## 作者：Inui_Sana (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/SP10622)

解题思路：单调栈

题意即为求 $\sum\limits_{i=1}^n\sum\limits_{j=i}^n\max\limits_{i\leq p\leq j}a_p-\min\limits_{i\leq q\leq j}a_q$，直接枚举的话，少说 $O(n^2)$，肯定是过不了的。

此时，我们不妨换种思路：求出每个数是多少个区间的最大值或最小值。而要求这个，就需要找到它之前和之后离它最近的大于它和小于它的数。这可以用单调栈在 $O(n)$ 的时间内做到。设第 $i$ 个数之前第一个大于它的数下标为 $fg_i$，第一个小于它的数下标为 $fl_i$，之后第一个大于它的数下标为 $bg_i$，第一个小于它的数下标为 $bl_i$，那么根据乘法原理，可以得出 $ans=\sum\limits_{i=1}^n (a_i\times((i-fg_i)\times(bg_i-i)-(i-fl_i)\times(bl_i-i)))$。

code:（ps：由于代码习惯，代码内变量和数组名与文中不同，但不影响理解，且在代码中 ```define int long long```）

```cpp
int n,m,ans,e[maxn],res[maxn][2][2];
int top1,top2,st1[maxn],st2[maxn];
void solve(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&e[i]);
	for(int i=1;i<=n;i++){
		while(top1&&e[st1[top1]]<e[i])res[st1[top1--]][1][1]=i;
		res[i][0][1]=st1[top1];
		st1[++top1]=i;
		while(top2&&e[st2[top2]]>e[i])res[st2[top2--]][1][0]=i;
		res[i][0][0]=st2[top2];
		st2[++top2]=i;
	}
	for(int i=1;i<=n;i++){//别忘了处理它是整个序列中最大或最小数的情况（最小处理可以忽略）
		if(!res[i][1][1])res[i][1][1]=n+1;
		if(!res[i][1][0])res[i][1][0]=n+1;
	}
	for(int i=1;i<=n;i++)ans+=e[i]*((i-res[i][0][1])*(res[i][1][1]-i)-(i-res[i][0][0])*(res[i][1][0]-i));
	printf("%lld",ans);
}
```

---

## 作者：云浅知处 (赞：0)

首先把式子拆成两部分：

$$
\sum_{i=1}^n\sum_{j=i}^n\left(\max_{i\leqslant k\leqslant j}a_i-\min_{i\leqslant k\leqslant j}a_i\right)=\sum_{i=1}^n\sum_{j=i}^n\max_{i\leqslant k\leqslant j}a_i-\sum_{i=1}^n\sum_{j=i}^n\min{i\leqslant k\leqslant j}a_i
$$

这里我们考虑如何计算

$$
\sum_{i=1}^n\sum_{j=i}^n\max_{i\leqslant k\leqslant j}a_i
$$

那么最小值就是同理的。

我们考虑对每个 $a_i$ 算它的贡献。

注意到当且仅当 $a_i$ 为区间 $[l,r]$ 的最大值时，$a_i$ 才会被计算一次。

那么现在只需要计算有多少个区间 $[l,r]$ 使得 $a_i$ 为区间最大值。

设 $L$ 为满足 $l<i,a_l\geqslant a_i$ 的最大的 $l$，$R$ 为满足 $r>i,a_r>  a_i$ 的最小的 $r$，那么这样的区间个数就是 $(i-L)(R-i)$。

$L,R$ 都可以用单调栈 $O(n)$ 预处理，于是这题就做完了。

```cpp
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<stack>

#define int long long
const int MN=3e5+5;

using namespace std;

int a[MN];
int Lmax[MN],Rmax[MN],Lmin[MN],Rmin[MN];
stack<int>s;
int n;

signed main(void){

    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];

    for(int i=1;i<=n;i++){
        while(!s.empty()&&a[s.top()]<=a[i])s.pop();
        if(s.empty())Lmax[i]=0;
        else Lmax[i]=s.top();
        s.push(i);
    }

    while(!s.empty())s.pop();
    for(int i=1;i<=n;i++){
        while(!s.empty()&&a[s.top()]>=a[i])s.pop();
        if(s.empty())Lmin[i]=0;
        else Lmin[i]=s.top();
        s.push(i);
    }

    while(!s.empty())s.pop();
    for(int i=n;i>=1;i--){
        while(!s.empty()&&a[s.top()]<a[i])s.pop();
        if(s.empty())Rmax[i]=n+1;
        else Rmax[i]=s.top();
        s.push(i);
    }

    while(!s.empty())s.pop();
    for(int i=n;i>=1;i--){
        while(!s.empty()&&a[s.top()]>a[i])s.pop();
        if(s.empty())Rmin[i]=n+1;
        else Rmin[i]=s.top();
        s.push(i);
    }

    int ans=0;
    for(int i=1;i<=n;i++){
        ans=ans+a[i]*(i-Lmax[i])*(Rmax[i]-i);
        ans=ans-a[i]*(i-Lmin[i])*(Rmin[i]-i);
    }

    cout<<ans<<endl;

    return 0;
}
```

---

## 作者：Zxsoul (赞：0)

## 思路

存在子序列，区间是在不断的移动的，这样的问题一般用单调栈或单调队列（起码最近我是这样），那么怎么维护最大值和最小值呢？

$$
\sum_{i=1}^{n}\sum_{j=1}^{n}max_{i<=k<=j}\{a_k\}-min_{i<=k<=j}\{a_k\}
$$

既然是单调做法，来个数比较一下，而且还没有固定区间，像极了单调栈，所以我来讲一下原理

存在一个栈 $st[]$，由大到小递减，且栈按顺序依次入栈，假设一个在 $a_i$ 入栈，若栈顶比他小，弹出，直到找到第一个比他大的数$s $，

那么在 $s$ 到 $i$ 的区间中且不包括 $s$，区间最大值是不是 $i$,
那么在区间中可以形成几个子序列？答案是 $s-i+1$,

对于每个数我们都可以这样做，但是栈怎么维护呢？
![](https://cdn.luogu.com.cn/upload/image_hosting/y49sfved.png)

但是我们只做了当右边固定的情况，当一个最大值在子序列的中间怎么办，开个变量 $now$ 计算就好了，还不懂就模拟一下

## Code
```c
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;

const int A = 1e5 + 11;
const int B = 1e6 + 11;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

inline int read() {
  char c = getchar();
  int x = 0, f = 1;
  for ( ; !isdigit(c); c = getchar()) if (c == '-') f = -1;
  for ( ; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
  return x * f;
}

int ans,n,a[B],st[B],head;

int stack()
{
  head=1;
  int now=0,sum=0;
  for (int i=1;i<=n;i++)
  {
    while(head>1 && a[st[head]]<a[i]){
      now-=(st[head]-st[head-1])*a[st[head]];
      head--;
    }
    now+=(i-st[head])*a[i];
    sum+=now;
    st[++head]=i;
  } 
  return sum;
}

 main() {
//  freopen(".in", "r", stdin);
//  freopen(".out", "w", stdout);
  n=read();
  for (int i=1;i<=n;i++) a[i]=read();

  ans+=stack();
  for (int i=1;i<=n;i++) a[i]*=1ll*(-1);
  ans+=stack();
  printf("%lld\n",ans);
  
  fclose(stdin);
  fclose(stdout);
  return 0;
}


```

---

