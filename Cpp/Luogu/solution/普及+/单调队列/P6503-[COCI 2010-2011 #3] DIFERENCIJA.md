# [COCI 2010/2011 #3] DIFERENCIJA

## 题目描述

给出一个长度为 $n$ 的序列 $a_i$，求出下列式子的值：

$$\sum_{i=1}^{n} \sum_{j=i}^{n} (\max_{i\le k\le j} a_k-\min_{i\le k\le j} a_k)$$



即定义一个子序列的权值为序列内最大值与最小值的差。求出所有连续子序列的权值和。



## 说明/提示

#### 数据规模与约定

对于 $100\%$ 的数据，保证 $2\le n\le 3\times 10^5$，$1\le a_i\le 10^8$。

#### 说明

**题目译自 [COCI2010-2011](https://hsin.hr/coci/archive/2010_2011/) [CONTEST #3](https://hsin.hr/coci/archive/2010_2011/contest3_tasks.pdf) *T5 DIFERENCIJA***。

## 样例 #1

### 输入

```
3
1
2
3```

### 输出

```
4```

## 样例 #2

### 输入

```
4
7
5
7
5```

### 输出

```
12```

## 样例 #3

### 输入

```
4
3
1
7
2```

### 输出

```
31```

# 题解

## 作者：Alex_Wei (赞：136)

> [题面传送门](https://www.luogu.com.cn/problem/P6503)。

> 题意简述：给出 $n$ 和 $a_i$，求

> $$\sum_{i=1}^n\sum_{j=i}^n\left(\max_{i\leq k\leq j}a_k-\min_{i\leq k\leq j}a_k\right)$$

提供一个不一样的思路。

---

我们设 $f_i/g_i$ 为以 $i$ 结尾的所有子序列的最大 / 最小值之和，那么答案为 $\sum f_i-g_i$。

考虑如何维护 $f,g$。

不妨设 $p_i<i$ 为满足 $a_{p_i}>a_i$ 的最大的 $p_i$（特别的，如果 $p_i$ 不存在则为 $0$），那么有转移方程 $f_i=f_{p_i}+a_i\times (i-p_i)$，$p_i$ 可以用单调栈维护。 

稍微解释一下上面的转移方程是如何得来的：

- 因为 $a_i$ 对 $p_i$ 以及 $p_i$ 以前的最大值没有影响（即 $[1,p_i]$ 与 $[1,i]$，$[2,p_i]$ 与 $[2,i]\cdots$ $[p_i,p_i]$ 与 $[p_i,i]$ 的最大值相同），所以可以直接由 $f_{p_i}$ 转移得来。
- 而根据 $p_i$ 的定义，后面 $i-p_i$ 个子序列（即 $[p_i+1,i],[p_i+2,i]\cdots,[i,i]$）的最大值为 $a_i$，所以加上 $a_i\times (i-p_i)$。
- 所以转移方程为 $f_i=f_{p_i}+a_i\times (i-p_i)$。

维护 $g$ 只需要将 $p_i$ 的定义中「$a_{p_i}>a_i$」改为「$a_{p_i}<a_i$」即可，用两个单调栈即可求出答案。

时间复杂度 $O(n)$，常数较小，代码好写，而且跑得飞快，甚至抢到了最优解（2020.8.23）。

```cpp
const int N=3e5+5;

ll n,t1,t2,ans,f[N],g[N];
pii a[N],b[N];

int main(){
	n=read();
	for(int i=1;i<=n;i++){
		ll x=read(),p;
		while(t1&&x>=a[t1].fi)t1--;
		while(t2&&x<=b[t2].fi)t2--;
		p=a[t1].se; f[i]=f[p]+x*(i-p);
		p=b[t2].se; g[i]=g[p]+x*(i-p);
		ans+=f[i]-g[i],a[++t1]=b[++t2]={x,i};
	} cout<<ans<<endl;
	return 0;
}
```

---

## 作者：云浅知处 (赞：15)

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

## 作者：Durancer (赞：9)

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

## 作者：sukimo (赞：7)

这题其实和$P1950$有异曲同工之妙。

最开始，我想到的是单调队列滑动窗口来做，滑$n$次出答案，时间$n^2$。但看看数据规模。$n$可达 $3×10^5$，看来只要和“序列两端点枚举”“分界性明确，一个一个求”扯上关系的方法，都不大可行。于是只能使用其他更快的类似“同时进行”的方法。于是考虑单调栈。题目中的式子可转化为：$\sum_{i=1}^n \sum_{j=i}^nmax\ a_k(i\le k\le j)-\sum_{i=1}^n \sum_{j=i}^nmin\ a_k(i\le k\le j)$

于是跑两遍单调栈，分别求出以每个元素作为最小值，最大值所带来的区间个数贡献。例如，若有$x$个以$a_i$为最大值的区间，则最终结果一定会加$x\times a_i$。最小值则减去。单调队列是以滑动为中心，走到哪里累积到哪里；而单调栈则可以以每一个元素为中心，一次就把该元素带来的贡献扩张完毕，自然效率大增。

最后别忘开$long\ long$！

代码：

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MX=300005;
int n,le_cnt[MX],array[MX];ll tot;struct STR{int pos,num;};stack<STR>stk;
STR pack(int pos,int num){STR a;a.pos=pos;a.num=num;return a;}
void stk_push1(){
	for(int i=1;i<=n;i++){
		while(!stk.empty()&&stk.top().num<array[i]){
		    tot+=(ll)(array[stk.top().pos])*(ll)(i-stk.top().pos)*(ll)(le_cnt[stk.top().pos]+1);stk.pop();
	    }
		le_cnt[i]=i-(stk.empty()?1:stk.top().pos+1);stk.push(pack(i,array[i]));
	}
	while(!stk.empty()){
		tot+=(ll)(array[stk.top().pos])*(ll)(n-stk.top().pos+1)*(ll)(le_cnt[stk.top().pos]+1);stk.pop();
	}
}
void stk_push2(){
	for(int i=1;i<=n;i++){
		while(!stk.empty()&&stk.top().num>array[i]){
		    tot-=(ll)(array[stk.top().pos])*(ll)(i-stk.top().pos)*(ll)(le_cnt[stk.top().pos]+1);stk.pop();
	    }
		le_cnt[i]=i-(stk.empty()?1:stk.top().pos+1);stk.push(pack(i,array[i]));
	}
	while(!stk.empty()){
		tot-=(ll)(array[stk.top().pos])*(ll)(n-stk.top().pos+1)*(ll)(le_cnt[stk.top().pos]+1);stk.pop();
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&array[i]);
	stk_push1();stk_push2();printf("%lld",tot);
	return 0;
}
```


---

## 作者：rui_er (赞：5)

~~我绝不会告诉你们这题与 SP10622 是双倍经验的~~，好了，不扯了，下面开始正文。

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

## 作者：Limitless_lmw (赞：4)

### 前置知识：

单调栈——[blog](https://blog.csdn.net/heucodesong/article/details/88286994)

---

首先转换一下这个式子：

$$
\sum_{i=1}^{n} \sum_{j=i}^{n} (\max_{i\le k\le j} a_k-\min_{i\le k\le j} a_k) 
= \sum_{i=1}^{n}\sum_{j=i}^{n} \max_{1\le k\le j} a_k - \sum_{i=1}^{n}\sum_{j=i}^{n} \min_{1\le k\le j} a_k
$$

可以发现，其实就是求每个区间的**最大值和最小值之差**的和，考虑怎么维护最大值和最小值，可以使用**单调栈**。

再考虑 $a_i$ 对 $ans$ 的贡献:

$$a_i\times[(i-maxl)\times(maxr-i)-(i-minl)\times(minr-i)]$$

其中，$a_{maxl}$ 为在 $a_i$ 左侧比 $a_i$ 大的且下标**尽量大**的元素，$a_{maxr}$ 为在 $a_i$ 右侧比 $a_i$ 大的且下标**尽量小**的元素，$a_{minl},a_{minr}$ 亦然。

原因：

想象一个子串的右端点固定在 $i$，且这个子串的最大值就是 $a_i$，那么显然左端点一定在 $a_i$ 左侧离 $a_i$ 最近的比 $a_i$ 的最大值的右侧，换句话说，即左端点一定在 $a_i$ 左侧所有比 $a_i$ 大的元素右侧。

那么左端点到右端点的长度是多少？显然是 $i-(maxl+1)+1=i-maxl$。

同理可得，一个子串的左端点固定在 $i$，且这个子串的最大值为 $a_i$，则右端点一定在 $a_i$ 右侧所有比 $a_i$ 大的元素左侧。

$minl,minr$ 同理。

那么这个问题用单调栈就方便许多了，对于 $maxl,minl$，我们**正着扫**一边数组，不断弹出和自己相比**小于等于/大于等于**的数，知道碰见比自己**大于/小于**的数或栈被清空，此时更新 $maxl,minl$ 即可。

而对于 $maxr,minr$，我们就**反着扫**一边数组，弹出比自己**小于/大于**的数，直到遇见和自己相比**大于等于/小于等于**的数或栈被清空，更新 $maxr,minr$ 即可。

最后计算贡献之和即可。

Code：

```cpp
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

#define int long long

int arr[300010];
vector<int> v;
long long ans=0;
int n;
int maxx[300010][3];
int minn[300010][3];

signed main(){
    scanf("%lld",&n);
    for(int i = 1; i<=n; i++) scanf("%lld",arr+i);
    for(int i = 1; i<=n; i++){
        while(v.size()&&arr[v.back()]<=arr[i]) v.pop_back();
        if(v.empty()) maxx[i][1]=0;
        else maxx[i][1]=v.back();
        v.push_back(i);
    }
    v.clear();
    //倒着扫
    for(int i = n; i>=1; i--){
        while(v.size()&&arr[v.back()]<arr[i]) v.pop_back();
        if(v.empty()) maxx[i][2]=n+1;
        else maxx[i][2]=v.back();
        v.push_back(i);
    }
    v.clear();
    for(int i = 1; i<=n; i++){
        while(v.size()&&arr[v.back()]>=arr[i]) v.pop_back();
        if(v.empty()) minn[i][1]=0;
        else minn[i][1]=v.back();
        v.push_back(i);
    }
    v.clear();
    //倒着扫
    for(int i = n; i>=1; i--){
        while(v.size()&&arr[v.back()]>arr[i]) v.pop_back();
        if(v.empty()) minn[i][2]=n+1;
        else minn[i][2]=v.back();
        v.push_back(i);
    }
    v.clear();
    for(int i = 1; i<=n; i++){
        ans+=(arr[i]*(i-maxx[i][1])*(maxx[i][2]-i));
        ans-=(arr[i]*(i-minn[i][1])*(minn[i][2]-i));
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Godzilla (赞：4)

### 题目大意 ：

给出一个长度为 $n$ 的序列 $a_i$ ，求出下列式子的值：

$\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}(\max{a_k}-\min{a_k}),(i \le k\le j )$

即定义一个子序列的权值为序列内最大值与最小值的差。求出所有连续子序列的权值和。

---

### 前置知识：

1.单调栈

---

### 思路：

对于区间问题，一般有两种思路：

1.枚举左端点，用 $O(1)$ 或者 $O(\log{n})$ 的复杂度算出右端点。

2.对于区间，设状态 $f(i)$ 或者 $f(i,j)$ ，考虑转移。

这道题，我是用的第2种思路。

设 $f(i)$ 表示以 $i$ 为左端点的所有区间的最大值减最小值。

考虑转移 ：

由于动态规划的性质就是重复部分算一次，那么假设 $f(i-1)$ 转移。

对比 $f(i)$ 与 $f(i-1)$ ，有那些影响呢？

无非就是 $a_i$ 更新了一些区间的最大值或者最小值。

那么可以维护两个单调队列，一个上升，一个下降，符合 $a_i$ 更新的特性。

每次算出更新的最大值与最小值的差，加上去就好了。

复杂度 ：$O(n)$ 。

---

### 定义：

$s1$ 为单调上升队列。

$s2$ 为单调下降队列。

$w1$ 为单调上升队列的宽度。

$w2$ 为单调下降队列的宽度。

---

### 代码 ：

```c++
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

#define ULL unsigned long long

using namespace std;

const int kMax=3e5+5;
const int kInf=1e9;

ULL n;
ULL a[kMax];
ULL f[kMax];

ULL ans;

ULL s1[kMax],s2[kMax];
int t1,t2;
ULL w1[kMax],w2[kMax];

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		f[i]=f[i-1];
		ULL sum=0LL,k=0;
		while(a[s1[t1]]<a[i]&&t1){
			k+=w1[t1];
			sum+=(a[i]-a[s1[t1]])*w1[t1];
			t1--;
		}
		s1[++t1]=i;w1[t1]=1+k;
		f[i]+=sum;
		sum=0LL;k=0;
		while(a[s2[t2]]>a[i]&&t2){
			k+=w2[t2];
			sum+=(a[s2[t2]]-a[i])*w2[t2];
			t2--;
		}
		s2[++t2]=i;w2[t2]=1+k;
		f[i]+=sum;
		ans+=f[i];
	}
	printf("%lld\n",ans);
	return 0;
}
```

注意开 long long 。

---

## 作者：Accelessar (赞：3)

发现题解区各位大佬大多是用单调栈做的啊，那我就来写一发悬线法。

题意是很简洁的，不再赘述。

式子可以转化成 $\left(\sum\limits_{i=1}^n\sum\limits_{j=1}^n \max\limits_{i\le k\le j} a_k\right)-\left(\sum\limits_{i=1}^n\sum\limits_{j=1}^n \min\limits_{i\le k\le j} a_k\right)$。

我们考虑以每个 $a_i$ 作为最大（小）值时可以对答案作出多少贡献：我们设以 $a_i$ 为最大（小）值的最靠左端点为 $l_i$，最靠右端点为 $r_i$，那么根据乘法原理，以 $a_i$ 为最大（小）值的区间数量就是 $(i-l_i+1)(r_i-i+1)$。

那么我们用悬线法可以分别求出以 $a_i$ 为最大值时的左右端点 $lmx_i,rmx_i$，以及以它为最小值时的左右端点 $lmn_i,rmn_i$，最后扫一遍序列累加贡献即可。

注意在求左右端点时，一边可以取等，另一边不能取等，否则如果序列中有重复元素就会重复计算。

参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fr(i,l,r) for(int i(l);i<=(r);i++)
template<typename T>inline T rd(T&a){
    #define gc getchar
    #define dg(x) (x>='0'&&x<='9')
    char c=gc();T x=0,f=1;
    for(;!dg(c);c=gc())if(c=='-')f=-1;
    for(;dg(c);c=gc())x=(x<<1)+(x<<3)+c-48;
    return a=f*x;
}template<typename T,typename...V>inline void rd(T&x,V&...v){rd(x),rd(v...);}
const int N=3e5+10;
int n;
ll a[N],lmx[N],rmx[N],lmn[N],rmn[N],ans;

int main(){
    rd(n);fr(i,1,n)rd(a[i]),lmx[i]=rmx[i]=lmn[i]=rmn[i]=i;
    fr(i,1,n)while(lmx[i]>1&&a[i]>=a[lmx[i]-1])lmx[i]=lmx[--lmx[i]];
    for(int i=n;i;i--)while(rmx[i]<n&&a[i]>a[rmx[i]+1])rmx[i]=rmx[++rmx[i]];
    fr(i,1,n)while(lmn[i]>1&&a[i]<=a[lmn[i]-1])lmn[i]=lmn[--lmn[i]];
    for(int i=n;i;i--)while(rmn[i]<n&&a[i]<a[rmn[i]+1])rmn[i]=rmn[++rmn[i]];
    fr(i,1,n)ans+=a[i]*((i-lmx[i]+1)*(rmx[i]-i+1)-(i-lmn[i]+1)*(rmn[i]-i+1));
    return cout<<ans,0;
}
```

---

## 作者：moonbowqwq (赞：2)

[题目链接](https://www.luogu.com.cn/problem/P6503)

## 题意简述

给出一个长度为 $n$ 的序列 $a = \{a_1, a_2, \ldots, a_n\}$，求其所有子序列的最大值和最小值的差的和。

数据范围与约定：$2 \leq n \leq 3 \times 10^5, 1 \leq a_i \leq 10^{18}$。

## 解题思路

显然我们可以把最大值和最小值分别统计，最后把和相减即可，这里我用的是 ST 表。

具体地，假设我们当前所在的区间为 $[l, r]$，该区间内的最值所在位置为 $k (k \in [l, r])$，那么所有左端点在 $[l, k]$ 之中且右端点在 $[k, r]$ 之中的子序列其最值都为 $a_k$，所以 $a_k$ 对答案的贡献就为 $(-1)^{[\forall i \in [l, r], a_k \leq a_i]} \times a_k \times (r - k + 1) \times (k - l + 1)$，然后我们再递归处理子区间 $[l, k - 1]$ 和 $[k + 1, r]$ 即可，累和后的结果就是答案。

## 代码实现

```
#include<bits/stdc++.h>

using namespace std;

int N,A[300005];

class Sparse_Table_Max{
private:
  int max_id[300005][20];
  int log2(int num){
    int res = -1;
    while(num > 0)
      ++res,num >>= 1;
    return res;
  }
  int Max(int a,int b){
    if(A[a] > A[b])
      return a;
    return b;
  }
public:
  void Init(){
    for(int i = 1;i <= N;++i)
      max_id[i][0] = i;
    for(int k = 1;k < 20;++k)
      for(int i = N - (1 << k) + 1;i > 0;--i)
	max_id[i][k] = Max(max_id[i][k - 1],max_id[i + (1 << k - 1)][k - 1]);
    return;
  }
  int Query(int l,int r){
    int k = log2(r - l + 1);
    return Max(max_id[l][k],max_id[r - (1 << k) + 1][k]);
  }
}STX;

class Sparse_Table_Min{
private:
  int min_id[300005][20];
  int log2(int num){
    int res = -1;
    while(num > 0)
      ++res,num >>= 1;
    return res;
  }
  int Min(int a,int b){
    if(A[a] < A[b])
      return a;
    return b;
  }
public:
  void Init(){
    for(int i = 1;i <= N;++i)
      min_id[i][0] = i;
    for(int k = 1;k < 20;++k)
      for(int i = N - (1 << k) + 1;i > 0;--i)
	min_id[i][k] = Min(min_id[i][k - 1],min_id[i + (1 << k - 1)][k - 1]);
    return;
  }
  int Query(int l,int r){
    int k = log2(r - l + 1);
    return Min(min_id[l][k],min_id[r - (1 << k) + 1][k]);
  }
}STN;

__int128 DFS1(int l,int r);
__int128 DFS2(int l,int r);

int main(){
  scanf("%d",&N);
  for(int i = 1;i <= N;++i)
    scanf("%d",&A[i]);
  STN.Init(),STX.Init();
  printf("%lld",(long long)(DFS1(1,N) - DFS2(1,N)));
  return 0;
}

__int128 DFS1(int l,int r){
  if(l > r)
    return 0;
  if(l == r)
    return A[l];
  int mid = STX.Query(l,r);
  return (__int128)(mid - l + 1) * (r - mid + 1) * A[mid] + DFS1(l,mid - 1) + DFS1(mid + 1,r);
}//get max

__int128 DFS2(int l,int r){
  if(l > r)
    return 0;
  if(l == r)
    return A[l];
  int mid = STN.Query(l,r);
  return (__int128)(mid - l + 1) * (r - mid + 1) * A[mid] + DFS2(l,mid - 1) + DFS2(mid + 1,r);
}//get min
```


---

## 作者：Zxsoul (赞：2)

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

## 作者：Martian148 (赞：2)

# Link
[P6503 [COCI2010-2011#3] DIFERENCIJA](https://www.luogu.com.cn/problem/P6503)

# Solve
这道题和SP10622相类似

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

## 作者：Cry_For_theMoon (赞：2)

&emsp;&emsp;[传送门](https://www.luogu.com.cn/problem/P6503)

&emsp;&emsp;计算贡献的所有题解都只讲到了单调栈维护每个点的最左边和最右边。但是如果真的只做到这一步是可能有问题的，考虑这组数据：$1,1,1$，发现**同一区间内因为有相同元素，导致一个区间被计算了多次**。因此相同地，我们应该还要找到一个方法，使得**每个区间被最大/最小元素计算的同时，如果有相同的，应该被最靠左/右的元素计算**，这里我们选择最靠右的。

&emsp;&emsp;以维护两侧第一个比 $a_i$ 大的为例（维护小的同理）：

&emsp;&emsp;考虑两个相同的元素，它们会被包含在一个区间当且仅当**中间没有比它们大的元素**，因此只有在单调栈出栈的时候在栈中的那些相同元素才可能与当前元素在一个区间里重复考虑。先不考虑中间依旧有相同元素的情况，因为我们只保留最靠右的，所以我们**从左往右扫的时候出栈条件是 $a_{top} <= a_i$**。然后考虑两点之间还有第三个相同点的情况，此时左边的点应该在中间那个点的时候就出栈了。因此这样做，对于左边界满足了只保留右边。

&emsp;&emsp;再考虑从右往左，此时做法应该相反，出栈条件是 $a_{top} < a_i$，这样如果一个点的右边相同元素（且中间没有比它们大的），它的右边界就是那个元素。相同地，这样也可以完美处理两点中间还有相同的第三个点的情况。

&emsp;&emsp;所以此时左右边界的维护都符合了一开始 **每个区间被最靠右的最大/小元素计算的条件**

&emsp;&emsp;所以这个出栈时取不取等其实是最重要的。

&emsp;&emsp;代码（~~4 遍几乎相同的单调栈~~）：

&emsp;&emsp;本题有 70 分要开 long long QwQ


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<stack>
using namespace std;
const int MAXN=3e5+10;
stack<int>st1,st2,st3,st4;
int n;
long long a[MAXN];
long long ans,tmp1,tmp2;
int l[MAXN],r[MAXN];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	for(int i=1;i<=n;i++){
		while(!st1.empty() && a[st1.top()] <= a[i]){
			st1.pop();
		}
		if(!st1.empty()){
			l[i] = st1.top();
		}
		st1.push(i);
	}
	for(int i=n;i>=1;i--){
		while(!st2.empty() && a[st2.top()] < a[i]){
			st2.pop();
		}
		if(!st2.empty()){
			r[i] = st2.top();
		}else{
			r[i] = n+1;
		}
		st2.push(i);
	}
	for(int i=1;i<=n;i++){
		long long llim = l[i],rlim = r[i];
		tmp1 =tmp1 + (i - llim) * (rlim - i) * a[i];
	}
	memset(l,0,sizeof l);
	memset(r,0,sizeof r);
	for(int i=1;i<=n;i++){
		while(!st3.empty() && a[st3.top()] >= a[i]){
			st3.pop();
		}
		if(!st3.empty()){
			l[i] = st3.top();
		}
		st3.push(i);
	}
	for(int i=n;i>=1;i--){
		while(!st4.empty() && a[st4.top()] > a[i]){
			st4.pop();
		}
		if(!st4.empty()){
			r[i] = st4.top();
		}else{
			r[i] = n+1;
		}
		st4.push(i);
	}
	for(int i=1;i<=n;i++){
		long long llim = l[i],rlim = r[i];
		tmp2 = tmp2 + (i-llim) * (rliWm-i) * a[i];
	}
	printf("%lld\n",tmp1-tmp2);
	return 0;
} 
```


---

## 作者：Wiueh_Plus (赞：1)

[P6503 [COCI2010-2011#3] DIFERENCIJA](https://www.luogu.com.cn/problem/P6503)

我们可以将题目中所给出的式子转化为：
$$\sum_{i=1}^{n} \sum_{j=i}^{n} \max_{i\le k\le j} a_k-\sum_{i=1}^{n} \sum_{j=i}^{n}\min_{i\le k\le j} a_k$$

也就是说现在需要求出每一个连续的子序列中的最大值和最小值。

我们不妨换一个角度思考问题，我们考虑求出每一个元素可以对答案给出的贡献。那么我们就要分别求出每一个元素在他能贡献的字序列中的最大值和最小值。

假设我们有一个序列 `1 2 5 3 4 1 0 9`，我们现在要求出第 $5$ 个元素也就是 $4$ 贡献出的最大值。显然我们可以在 $\left[4,7\right]$ 内任意取子序列，在这个区间内没有哪个数还能比 $4$ 大，所以无论怎么取 $4$ 都可以贡献最大值。

我们发现，对于序列中任意一个数 $a_i$，若要贡献出最大值，我们设从当前位置往左第一个大于 $a_i$ 的位置，为 $maxl_i$，设从当前位置往右第一个大于 $a_i$ 的位置为 $maxr_i$，那么这个区间就是 $\left[maxl_i+1,maxr_i-1\right]$。
（显然，当 $maxl$ 不存在时，默认为 $0$；当 $maxr$ 不存在时，默认为 $n + 1$。）

根据乘法原理，易得这个区间内一共有 $(maxr_i-i)\times(i-maxl_i)$ 个连续的子序列，也就是说 $a_i$ 能贡献 $(maxr_i-i)\times(i-maxl_i)$ 次最大值。

同理可得，$a_i$ 能贡献 $(minr_i-i)\times(i-minl_i)$ 次最小值。

那么 $a_i$ 可以对总的答案贡献出：
$$a_i\times((maxr_i-i)\times(i-maxl_i)-(minr_i-i)\times(i-minl_i))$$

------------

那么我们怎么能在 $2\leq n\leq 3\times10^5$ 的范围内求出每个 $a_i$ 对应的 $maxl$，$minl$，$maxr$，$minr$ 呢，显然对于这种第一次大于某个数，第一次小于某个数的要求，单调栈能可以发挥出作用了。

分别用四个单调栈维护即可。

```cpp
int n,arr[N],stk[N],top = 0;
int maxl[N],maxr[N],minl[N],minr[N];
void getmaxl(){
	top = 0;
	for (int i = n;i >= 1;i--){
		while (top && arr[i] >= arr[stk[top]]){
			maxl[stk[top]] = i;
			top--;
		}
		top++;
		stk[top] = i;
	}
}
void getminl(){
	top = 0;
	for (int i = n;i >= 1;i--){
		while (top && arr[i] <= arr[stk[top]]){
			minl[stk[top]] = i;
			top--;
		}
		top++;
		stk[top] = i;
	}
}
void getmaxr(){
	top = 0;
	for (int i = 1;i <= n;i++){
		while (top && arr[i] > arr[stk[top]]){
			maxr[stk[top]] = i;
			top--;
		}
		top++;
		stk[top] = i;
	}
	for (int i = 1;i <= n;i++){
		if (!maxr[i]){
			maxr[i] = n + 1;
		}
	} 
}
void getminr(){
	top = 0;
	for (int i = 1;i <= n;i++){
		while (top && arr[i] < arr[stk[top]]){
			minr[stk[top]] = i;
			top--;
		}
		top++;
		stk[top] = i;
	}
	for (int i = 1;i <= n;i++){
		if (!minr[i]){
			minr[i] = n + 1;
		}
	} 
}
signed main(){
	n = read();
	for (int i = 1;i <= n;i++){
		arr[i] = read();
	}
	getmaxl();
	getminl();
	getmaxr();
	getminr();
	int ans = 0;
	for (int i = 1;i <= n;i++){
		ans += arr[i] * ((maxr[i] - i) * (i - maxl[i]) - (minr[i] - i) * (i - minl[i]));
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：cwfxlh (赞：1)

# P6503题解
这道题是一道标准的单调栈模板，我们可以把 $\max$ 和 $\min$ 拆开来看。以 $\max$ 为例：    
定义 $sum[i]$ 为以 $i$ 为结尾的所有子序列的 $\max$ 之和，同时用单调栈的算法，我们可以 $\Theta(n)$ 算出每个元素左边第一个比它大的元素位置，即 $nxt[i]$ ，那么 $sum[i]$ 中的每一个子序列的最大元素要么在 $[start,nxt[i]]$ 中，要么在 $(nxt[i],i]$ 中，而 $a[nxt[i]]>a[i]$ ，所以当且仅当子序列不包含 $a[nxt[i]]$ 时，最大值才在后一段中，而后一段中的最大为 $a[i]$ ，那么 $sum[i]$ 就是两种情况之和，即：
$$sum[i]=sum[nxt[i]]+a[i]\times(i-nxt[i])$$
最后的答案只需要把 $sum_{\max}$ 求和再减去 $sum_{\min}$ 即可。  
附上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[300003],stk[300003],tot,lmn[300003],lmx[300003],ans,sum[300003];
//sum重复用了两次，lmn是左边第一个比它小的，lmx是左边第一个比它大的。 
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++)
	{
		while(tot>0&&a[stk[tot]]<=a[i])tot--;
		lmx[i]=stk[tot];
		tot++;
		stk[tot]=i;
	}
	tot=0;
	for(int i=1;i<=n;i++)
	{
		while(tot>0&&a[stk[tot]]>=a[i])tot--;
		lmn[i]=stk[tot];
		tot++;
		stk[tot]=i;
	}
	tot=0;
	for(int i=1;i<=n;i++)
	{
		sum[i]=sum[lmx[i]]+a[i]*(i-lmx[i]);
		ans+=sum[i];
	}
	for(int i=1;i<=n;i++)
	{
		sum[i]=sum[lmn[i]]+a[i]*(i-lmn[i]);
		ans-=sum[i];
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：yizcdl2357 (赞：1)

我们发现

$\sum_{i=1}^n\sum_{j=i}^n \text{max}_{k=i}^ja_k-\text{max}_{k=i}^ja_k$

$=\sum_{i=1}^n\sum_{j=i}^n \text{max}_{k=i}^ja_k-\sum_{i=1}^n\sum_{j=i}^n \text{min}_{k=i}^ja_k$

$=\sum_{i=1}^n\sum_{j=i}^n \text{max}_{k=i}^ja_k+\sum_{i=1}^n\sum_{j=i}^n \text{max}_{k=i}^j(-a_k)$

因此，只用求 $\sum_{i=1}^n\sum_{j=i}^n \text{max}_{k=i}^ja_k$ 就行了，因为求后式时只要令 $a_i\Leftarrow(-a_i)$ 即可。


------------
考虑 $a_x$ 出现了几次，记为 $num_x$。

令 $l_x$ 为满足 $y<x$ 且 $a_y>a_x$ 的最大的 $y$。

令 $r_x$ 为满足 $y>x$ 且 $a_y>a_x$ 的最小的 $y$。

则显然 $num_x=(x-l_x)\times(r_x-x)$。知道了 $num_x$ 就知道答案。

于是问题转化成了求 $l$ 和 $r$。

注意，为了防止 $l_x$ 和 $r_x$ 不存在，应在数组 $a$ 的前后各插入一个 `inf`，如下图
![](https://cdn.luogu.com.cn/upload/image_hosting/rwzjeh8m.png)

------------
对数列 $a$ 维护一个单调栈。

如果 $a_x$ 进栈时将 $a_y$ 压了出来，则 $r_y=x$。

当 $a_x$ 进栈成功时，设它在栈中的前驱为 $a_y$，则 $l_x=y$。

这样，我们在 $O(n)$ 的时间内求出了 $l$ 和 $r$。

放一下代码

```
#include<iostream>
#include<cstdio>
#include<cstring>
#define int long long
using namespace std;
int n,a[1000001];
int l[1000001],r[1000001],num[1000001],ans;
int h,t,d[1000001];
void solve()
{
	h=1;t=0;
	for(int i=1;i<=n;i++)
	{
		while(h<=t&&a[d[t]]<a[i])
			r[d[t]]=i,t--;
		if(h<=t) l[i]=d[t];
		d[++t]=i;
	}
}
main()
{
	cin>>n;
	a[1]=1145141919810;
	for(int i=2;i<=n+1;i++)
		scanf("%d",&a[i]);
	a[n+2]=1145141919810;
	n+=2;
	solve();
	for(int i=2;i<=n-1;i++)
		num[i]=(i-l[i])*(r[i]-i),
		a[i]=-a[i];
	solve();
	for(int i=2;i<=n-1;i++)
		num[i]-=(i-l[i])*(r[i]-i),
		a[i]=-a[i],
		ans+=a[i]*num[i];
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：Otomachi_Una_ (赞：1)

## 简述

- 给定 $n$ 和长度为 $n$ 的序列 $a$。

- 要求 $\sum_{i=1}^n\sum_{j=i}^n\max a_k-\min a_l$ 其中 $k,l\in [i,j]$。

## 分析

对求和进行拆解，原式等价于求

$$\sum_{i=1}^n\sum_{j=i}^n\max a_k-\sum_{i=1}^n\sum_{j=i}^n\min a_k$$

对两个部分进行单独求解。

这里以最大值之和举例，最小值之和类同。

假设最大值之和为 $S$，考虑数列中每个元素对 $S$ 做的贡献。

设第 $i$ 个元素左右第一个比它大的数的下标为 $leftmax_i$ 与 $rightmax_i$。

则当 $l\in(leftmax_i,i],r\in[i,rightmax_i]$ 中的所有下标为 $[l,r]$ 的数列中最大元素都为 $a_i$, 反之亦然。

故 $a_i$ 对 $S$ 所做的贡献为 $a_i\times(i-leftmax_i)\times(rightmax_i-i)$，其中 $leftmax_i$ 与 $rightmax_i$ 均可以用单调栈求之。

于是本题就这么愉快的结束啦 ~ 

## 代码

```cpp
#include<iostream>
#include<stack>
using namespace std;
const int MAXN=3e5+5;
int n;
long long a[MAXN];
long long leftmin[MAXN],rightmin[MAXN];
long long leftmax[MAXN],rightmax[MAXN];
long long ans=0;
stack<pair<int,int> > Q;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++){
		while(!Q.empty()&&Q.top().first>=a[i]){
			rightmin[Q.top().second]=i;
			Q.pop();
		}
		Q.push(make_pair(a[i],i));
	}
	while(!Q.empty()){
		rightmin[Q.top().second]=n+1;
		Q.pop();
	}
	
	for(int i=1;i<=n;i++){
		while(!Q.empty()&&-Q.top().first<=a[i]){
			rightmax[Q.top().second]=i;
			Q.pop();
		}
		Q.push(make_pair(-a[i],i));
	}
	while(!Q.empty()){
		rightmax[Q.top().second]=n+1;
		Q.pop();
	}
	
	for(int i=n;i>=1;i--){
		while(!Q.empty()&&Q.top().first>a[i]){
			leftmin[Q.top().second]=i;
			Q.pop();
		}
		Q.push(make_pair(a[i],i));
	}
	while(!Q.empty()){
		leftmin[Q.top().second]=0;
		Q.pop();
	}
	
	for(int i=n;i>=1;i--){
		while(!Q.empty()&&-Q.top().first<a[i]){
			leftmax[Q.top().second]=i;
			Q.pop();
		}
		Q.push(make_pair(-a[i],i));
	}
	while(!Q.empty()){
		leftmax[Q.top().second]=0;
		Q.pop();
	}
	
	for(int i=1;i<=n;i++)
		ans+=((i-leftmax[i])*(rightmax[i]-i)-(i-leftmin[i])*(rightmin[i]-i))*a[i];
	cout<<ans;
}
```
注 . 本题虽然代码很长，但是其中一大半都在单调栈，个人认为很好理解吧。

---

## 作者：zpyyy (赞：1)

事实上，本题要求的就是每个值作为最大值和最小值对答案有多少贡献  
显然会有一个坑点，如果有一个区间里有两个相同的最大或最小值，但这个值对答案的贡献只能算做一次，所以可以把相同的数看成越前面（越后面）的越大  
~~众所周知，部分单调栈的题目也可以使用链表~~  
所以直接链表搞一搞就行了，显然不需要set这种常数极大的东东  
Code: 
```cpp
#include<bits/stdc++.h>
#define ll long long
#define make(aa,bb) make_pair(aa,bb)
#define PII pair<int,int>
#define fi first
#define se second
#define lowbit(x) (x)&(-x)
#pragma GCC optimize(2)
using namespace std;
const int N=3e5+5;
ll a[N],le[N],ri[N];
ll ans;
int n,top;
int s[N];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);a[n+1]=a[0]=-1;
    le[1]=0,ri[n]=n+1;
    for(int i=1;i<=n;i++){
        int j=i-1;
        while(j){
            if(a[j]<=a[i]) j=le[j];
            else break;
        }
        le[i]=j;
    }
    for(int i=n;i>=1;i--){
        int j=i+1;
        while(j<=n){
            if(a[j]<a[i]) j=ri[j];
            else break;
        }
        ri[i]=j;
    }
    for(int i=1;i<=n;i++) ans+=(ll)(ri[i]-i)*(i-le[i])*a[i];
    memset(le,0,sizeof(le));
    memset(ri,0,sizeof(ri));
    le[1]=0,ri[n]=n+1;
    for(int i=1;i<=n;i++){
        int j=i-1;
        while(j){
            if(a[j]>=a[i]) j=le[j];
            else break;
        }
        le[i]=j;
    }
    for(int i=n;i>=1;i--){
        int j=i+1;
        while(j<=n){
            if(a[j]>a[i]) j=ri[j];
            else break;
        }
        ri[i]=j;
    }
    for(int i=1;i<=n;i++) ans-=(ll)(ri[i]-i)*(i-le[i])*a[i];
    printf("%lld",ans);
    return 0;
}
```


---

## 作者：crh1272336175 (赞：1)

### Set维护

首先要明白，不能直接暴力求解的情况下，可以把题目转化为，求每个$a[i]$作为最大值和最小值的次数。举个例子，$a[i]$作为最大值的次数为$x$，最小值的次数为$y$，那么它对答案的贡献为：$a[i]*x-a[i]*y$

至于如何维护某个值最为最大（或最小）值的次数（本博客以最大值为例），我们可以考虑从当前$a[i]$开始，往左往右分别找到第一个比它大的位置，记为$le$和$ri$，区间$[le,ri]$内数字的数量记为$a[i]$作为最大值的个数。这个可以使用$set$维护

AC代码:
```cpp
#include<bits/stdc++.h>
#pragma GCC opitimize(2)
using namespace std;
typedef long long ll;
typedef pair<ll,ll> PLL;
const int N=3e5+5;
ll n,le,ri;
ll a[N];
PLL b[N];
set<ll> s;
set<ll>::iterator it;
namespace Read
{
	inline ll read()
	{
		ll s=0,f=1; char ch=getchar();
		while(!isdigit(ch)){if(ch=='-') f=-1; ch=getchar();}
		while(isdigit(ch)) s=s*10+(ch^48),ch=getchar();
		return s*f;
	}
	inline void write(ll x)
	{
		if(x<0) putchar('-'),x=-x;
		if(x>9) write(x/10);
		putchar(x%10+'0');
	}
}using namespace Read;
inline ll solvemax()
{
	ll res=0;
	sort(b+1,b+1+n);
	reverse(b+1,b+1+n);
	s.clear();
	s.insert(0); s.insert(n+1);
	for(ll i=1; i<=n; i++)
	{
		ll id=b[i].second;
		it=s.upper_bound(id);
		ri=*it; it--; le=*it;
		res+=(ri-id)*(id-le)*b[i].first;
		s.insert(id);
	}
	return res;
}
inline ll solvemin()
{
	ll res=0;
	reverse(b+1,b+1+n);
	s.clear();
	s.insert(0); s.insert(n+1);
	for(ll i=1; i<=n; i++)
	{
		ll id=b[i].second;
		it=s.upper_bound(id);
		ri=*it; it--; le=*it;
		res+=(ri-id)*(id-le)*b[i].first;
		s.insert(id);
	}
	return res;
}
int main()
{
	n=read();
	for(ll i=1; i<=n; i++) 
	{
		a[i]=read();
		b[i].first=a[i],b[i].second=i;
	}
	write(solvemax()-solvemin());
	return 0;
}
```


---

## 作者：sprads (赞：0)

很经典的问题。

一个转化：既然我们不能枚举确定区间来计算极差，那就考虑某一个数在哪些区间里产生了贡献。

先考虑对于位置 $i$，$a_i$ 作为最大值时的贡献。可以用单调栈确定，找到左边第一个大于 $a_i$ 的数的后一位 $L$（不存在则为 $1$），右边第一个大于 $a_i$ 的数的前一位（不存在则为 $n$），它作为最大值的贡献显然是 $a_i\times(i-L+1)\times(R-i+1)$。

作为最小值时同理。

但还有一个细节值得注意：仔细想想会发现，当有重复的数时，单调栈的维护有一些问题，计算容易重复或漏算。

对于下图，两个重复的 $5$，$x$，$y$ 都代表一个大于 $5$ 的数。以 $5$ 最为最大值为例，红和绿作为**第二个** $5$ 的 $L$ 似乎都是可以的。而黄和橙作为**第一个** $5$ 的 $R$ 似乎也是可以的。

![](https://cdn.luogu.com.cn/upload/image_hosting/zuf9ltdu.png)

事实上，只要第一个 $5$ 选择红，第二个 $5$ 选择绿，$R$ 都选择橙，就可以保证不重不漏。（当然 $L$ 都选择红，第一个 $5$ 选择黄，第二个 $5$ 选择橙也是可以的。）

写代码的话其实就是判断时一边取等，另一边不取等。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 300005;
long long ans,a[N];
int n,L1[N],L2[N],t1,s1[N],t2,s2[N];
int rd(){
	int x = 0;char ch = getchar();
	while(ch < '0' || ch > '9')ch = getchar();
	while(ch >= '0' && ch <= '9'){x = x * 10 + ch - '0';ch = getchar();}
	return x;
}
int main(){
	n = rd();
	for(int i = 1;i <= n;i++){
		a[i] = rd();
		while(t1 && a[s1[t1]] < a[i])t1--;//这里不取等
		while(t2 && a[s2[t2]] > a[i])t2--;
		L1[i] = s1[t1] + 1,s1[++t1] = i,L2[i] = s2[t2] + 1,s2[++t2] = i;
	}
	t1 = t2 = 0;
	s1[0] = s2[0] = n + 1;
	for(int i = n;i >= 1;i--){
		while(t1 && a[s1[t1]] <= a[i])t1--;//这里取等，两边同时反过来也可以
		while(t2 && a[s2[t2]] >= a[i])t2--;
		ans += (long long)(a[i] * (i - L1[i] + 1) * (s1[t1] - i) - a[i] * (i - L2[i] + 1) * (s2[t2] - i));
		s1[++t1] = i,s2[++t2] = i;
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

