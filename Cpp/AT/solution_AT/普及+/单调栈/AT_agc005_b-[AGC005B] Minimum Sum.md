# [AGC005B] Minimum Sum

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc005/tasks/agc005_b

すぬけ君はある日友人から長さ $ N $ の順列 $ a_1,\ a_2,\ ...,\ a_N $ を貰いました。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_agc005_b/7385c80af4629f5f6d11fed58e1b38d3c006d06d.png)

を求めてください。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ ≦\ 200,000 $
- $ (a_1,\ a_2,\ ...,\ a_N) $ は $ (1,\ 2,\ ...,\ N) $ を並び替えたものである

## 样例 #1

### 输入

```
3
2 1 3```

### 输出

```
9```

## 样例 #2

### 输入

```
4
1 3 2 4```

### 输出

```
19```

## 样例 #3

### 输入

```
8
5 4 8 1 2 6 7 3```

### 输出

```
85```

# 题解

## 作者：Leianha (赞：22)

## 单调栈

这是某次olinr巨佬给我们出的考试题。首先暴力$O(n^2)$是不能过的(~~废话~~)，我们考虑每一个数值对答案的贡献，也就是ta能当最小值的序列个数。

倘若ta能成为最小值，那么也就是在这个数列里没有比ta大的数值，这也就转化为了求出右边第一个比ta小的值的位置和左边第一个比ta小的值的位置的问题。这完全珂以用单调栈来完成，每次栈顶的元素被弹出的值的位置就是我们所求的被弹的元素的右边第一个比ta小的值的位置。当前元素不在弹出栈顶元素的时候，我们就求出了当前的元素的左边第一个比ta小的值的位置。因为每一个数值仅仅进了一次栈，所以时间复杂度是$O(n)$.(~~不要脸的搬了自己的另一篇博客里的话~~).

当然，你可以会只处理每一个元素的r[i],在随机数据下影响不大，但是在精心的数据下每次的转移接近为1，时间复杂度飙升到了$O(n^2)$,会有两个点超时，所以最好同时处理l[i]和r[i].

下面是超时2个数据点的代码
```cpp
#include<iostream>
#include<cstdio>
#define int long long
using namespace std;
int n,top,minn;
const int N=1000010;
int a[N],zhan[N],r[N];
long long ans;
signed main()
{
	cin>>n;
	for(int i=1;i<=n;++i)scanf("%lld",&a[i]);
	for(int i=1;i<=n;++i)r[i]=n+1;
	for(int i=1;i<=n;++i)
	{
		while(top&&a[zhan[top]]>a[i])r[zhan[top--]]=i;
		zhan[++top]=i;
	}
	for(int i=1;i<=n;++i)
	{
		minn=i;
		while(minn<=n)
		{
			ans+=(r[minn]-minn)*a[minn];
			minn=r[minn];
		}
	}
	cout<<ans;
	return 0;
}
/*
8
5 4 8 1 2 6 7 3
*/
```
下面是满分代码
```cpp
#include<iostream>
#include<cstdio>
#define int long long
using namespace std;
int n,top,minn;
const int N=1000010;
int a[N],zhan[N],r[N],l[N];
long long ans;
signed main()
{
	cin>>n;
	for(int i=1;i<=n;++i)scanf("%lld",&a[i]);
	for(int i=1;i<=n;++i)r[i]=n+1,l[i]=0;
	for(int i=1;i<=n;++i)
	{
		while(top&&a[zhan[top]]>a[i])r[zhan[top--]]=i;
		l[i]=zhan[top];
		zhan[++top]=i;
	}
	for(int i=1;i<=n;++i)ans+=(r[i]-i)*(i-l[i])*a[i];
	cout<<ans;
	return 0;
}
/*
8
5 4 8 1 2 6 7 3
*/
```
有兴趣的童鞋珂以写一下[类似的题目](https://www.luogu.org/problem/P2659)

---

## 作者：_jimmywang_ (赞：8)

好久没发题解了，应机房巨佬要求，来发一篇鬼畜的**平衡树**的题解。

#### 首先声明，平衡树做法的 $O(n \log n)$ 不及单调栈的 $O(n)$ 优。

~~所以会正解的同学们可以过来康康。~~

------------
首先，对于这种子段权值求和的东西，一般考虑拆贡献。

发现题目里说给出的序列是 $n$ 的全排列，所以考虑对每个数计算贡献。

如果当前的数是1，那么权值应该是`包含1的子段数`$\times 1$。

同理，若当前考虑2，那权值是`包含2但不包含1的子段数`$\times 2$。

以此类推。

发现还是不太好搞，怎么办？

每处理一个数，就把它的位置记录下来，考虑下一个数时合法子段的区间一定在`这个数的位置的前一个记录过的位置到这个数的位置的后一个记录过的位置`之间。

稍微转化一下，其实就是**前驱**和**后驱**。

于是想到平衡树。

还有一个问题：一个区间内包含某个位置的数的子段数如何计算？

这个很简单：考虑这个数之前选多少个，与这个数之后选多少个，乘法原理乘起来。

于是做完了。

Tips:一开始要先插入 $0$ 和 $n+1$，要不然1会没法处理。

这里代码使用`fhq-treap`实现，代码如下：
```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define f(i,a,b) for(int i=a;i<=b;i++)
inline ll rd() {
	ll x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return x*f;
}
#define d rd()
#define pb push_back
const ll N=200010;
ll ch[N][3],val[N],rnd[N],sz[N],cnt;
inline void upd(ll p){sz[p]=1+sz[ch[p][0]]+sz[ch[p][1]];}
inline void split(ll p,ll xx,ll &x,ll &y){
	if(!p){x=y=0;return;}
	else if(val[p]<=xx)x=p,split(ch[p][1],xx,ch[p][1],y);
	else y=p,split(ch[p][0],xx,x,ch[p][0]);
	upd(p);
}
inline ll merge(ll A,ll B){
	if(!A||!B)return A+B;
	if(rnd[A]<rnd[B]){ch[A][1]=merge(ch[A][1],B);upd(A);return A;}
	else{ch[B][0]=merge(A,ch[B][0]);upd(B);return B;}
}
inline ll node(ll x){
	sz[++cnt]=1,val[cnt]=x,rnd[cnt]=rand();
	return cnt;
}
ll n,rt;
ll x,y,z;
ll ans;
inline void ins(ll a){split(rt,a,x,y);rt=merge(merge(x,node(a)),y);}
inline ll kth(ll root,ll a){while(1){
		if(a<=sz[ch[root][0]])root=ch[root][0];
		else if(a==sz[ch[root][0]]+1)return root;
		else a-=sz[ch[root][0]]+1,root=ch[root][1];
	}
}
inline ll pre(ll root,ll a){split(rt,a-1,x,y);ll ans=kth(x,sz[x]);rt=merge(x,y);return ans;}
inline ll nxt(ll root,ll a){split(rt,a,x,y);ll ans=kth(y,1);rt=merge(x,y);return ans;}
struct nodde{ll x,id;}a[200010];
bool cmp(nodde a,nodde b){return a.x<b.x;}
int main(){srand(time(0));
	n=d;f(i,1,n)a[i].x=d,a[i].id=i;
	sort(a+1,a+n+1,cmp);
	ins(0),ins(n+1);
	f(i,1,n){
		ll p=val[pre(rt,a[i].id)];
		ll q=val[nxt(rt,a[i].id)];
		ll pos=a[i].id;
		ans+=i*(pos-p)*(q-pos);
		ins(a[i].id);
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：rui_er (赞：8)

用并查集来贪心。

我们可以把数列抽象成一条 $n+1$ 点 $n$ 边的链，$i$ 与 $i+1$ 之间的边权为 $a_i$。同时初始化一个有 $n+1$ 个点的并查集，需要记录每个集合的大小。

考虑一条边做出贡献的条件是什么，就是这条边是路径上边权最小的。因此我们将所有边按边权从大到小排序，然后按顺序枚举每一条边，根据它连接的两个连通块的大小和它的边权计算贡献，之后把这条边加到图中（也就是合并它连接的两个连通块）。

由于我们按边权降序枚举，显然在加入一条边时，过这条边的每条路径的最小边权都由这条边贡献。

时间复杂度为 $\mathcal{O}(n\log n)$。

[提交记录](https://atcoder.jp/contests/agc005/submissions/30545087)

---

## 作者：Fuko_Ibuki (赞：6)

又是一道单调求解的高妙题目.  
考虑每一个数在哪些区间内能够有贡献.  
对于$a[i]$来说,当它是区间内最小值时,它有贡献.  
那么很明显,我们对于每一个$a[i]$找出它左边最远能到的比它大的位置$l[i]$和它右边能到的最远的比它大的位置$r[i]$,那么能够使$a[i]$成为最小值的区间的个数是$(r[i]-i+1)\times (i-l[i]+1).$  
由于每一个区间必然有一个最小值,只要把每个数的贡献都加起来就是最后的答案了.  
那么$l[i]$和$r[i]$该如何$O(n)$求?  
我们利用已经求出来的答案,就像kmp一样.
怎么解释?  
如果$a[i-1]$比$a[i]$大,那么$l[i]$不可能比$l[i-1]$大.这个应该可以理解吧.  
那么我们就可以利用前面的答案辅助求出$l[i]$和$r[i]$并且还能够让复杂度均摊在$O(n)$了.  
主程序如下.
```cpp
int main() {
  int i,n=read();
  for (i=1;i<=n;++i) a[i]=read();
  for (i=1;i<=n;++i) {
    for (l[i]=i;l[i]>1&&a[l[i]-1]>a[i];l[i]=l[l[i]-1]);
  } 
  for (i=n;i;--i) {
    for (r[i]=i;r[i]<=n&&a[r[i]+1]>a[i];r[i]=r[r[i]+1]);
  }
  ll llx=0;
  for (i=1;i<=n;++i) llx+=1ll*a[i]*(i-l[i]+1)*(r[i]-i+1);
  write(llx);
}
```
谢谢大家.

---

## 作者：流逝丶 (赞：6)

我们发现，如果要枚举一个区间，那么至少也是$O(n^2)$的

题目让我们求所有最小值的和

那么我们不妨$O(n)$去枚举序列，然后考虑每一个元素对答案的贡献

显然是当前这个值作为最小值的区间个数$*$这个值

于是我们对于序列的每个值，考虑以它作为区间最小值的区间个数

既然它是区间的最小值，那么显然这个区间没有比它更小的了

所以这个区间的活动范围就是这个数左边第一个比它小的数的位置$+1$到这个数的位置

举个锤子

1 3 5 2 4 8 9 8

以$2$作为最小值，显然$l$的活动范围是$[2,4]$

因为$1$不能在这个区间里，如果在这个区间里，那$2$就不是最小值，而且，$2$必须在这个区间里，因为我们统计的是2作为区间最小值的区间个数

$r$同理

于是，我们的问题就变成了对于每个数，如何快速知道左右两边第一个比它小的数的位置？？

单调栈啊

求出了l和r的范围，然后乘法原理就知道有多少个区间啦，然后直接统计就行了

值得注意的是，对于重复的数的处理

比如

2 2 2 2 2

有些区间会算重复

其实也很简单，让l和r的边界一个是小于，一个是小于等于就行了

比如第三个2，可以在左边找第一个小于2的，那么你l的左边界就是1，在右边找第一个小于等于2的，那么你的r就是3，这样就不会重复了

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cctype>
#define LL long long
LL in() {
    char ch; LL x = 0, f = 1;
    while(!isdigit(ch = getchar()))(ch == '-') && (f = -f);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 1) + (x << 3) + (ch ^ 48));
    return x * f;
}
template<class T> bool chkmax(T &a, const T &b) { return a < b? a = b, 1 : 0; }
template<class T> bool chkmin(T &a, const T &b) { return b < a? a = b, 1 : 0; }
const int maxn = 1e6 + 10;
const int inf = 0x7fffffff;
class stack {
    protected:
        int st[maxn], tp;
    public:
        stack() { tp = 0; }
        void clear() { tp = 0; }
        int top() { return st[tp]; }
        void pop() { tp--; }
        bool empty() { return !tp; }
        void push(int x) { st[++tp] = x; }
}T;
int n;
LL ans, a[maxn];
int l[maxn], r[maxn];
int main() {
    n = in();
    for(int i = 1; i <= n; i++) a[i] = in();
    a[0] = a[n + 1] = -inf;
    T.push(0);
    for(int i = 1; i <= n; i++) {
        while(!T.empty() && a[i] <= a[T.top()]) T.pop();
        l[i] = T.top(); T.push(i);
    }
    T.clear(); T.push(n + 1);
    for(int i = n; i >= 1; i--) {
        while(!T.empty() && a[i] < a[T.top()]) T.pop();
        r[i] = T.top(); T.push(i);
    }
    for(int i = 1; i <= n; i++) ans += 1LL * (i - l[i]) * (r[i] - i) * a[i];
    printf("%lld\n", ans);
    return 0;
}
```


---

## 作者：peterwuyihong (赞：6)

机房人写出了鬼畜 $\text{fhq Treap}$，于是威逼那位巨佬写题解的时候我也来一发

单调栈对于悬线法正如白话文对文言文，晦涩难懂

考虑使用悬线法

记 $l_i,r_i$ 分别为从 $i$ 扩展，最小的 $l,r$ 并满足 $[l,r]$ 这段区间里的数都大于等于 $a_i$ 

### 流程
1. 初始化 $l_i←i$

2. 考虑到利用已经算出来的信息，顺序遍历，若当前 $a_i<a_{l_i-1}$，就 $l_i←l_{l_i-1}$

3. 由于要利用已经算出来的信息，算 $r$ 的时候要倒序遍历，同理

4. 然后就简单数学算一下子段个数就行了

```cpp
cin>>n;
for(int i=1;i<=n;i++)cin>>a[i],l[i]=r[i]=i;
for(int i=1;i<=n;i++)
	while(l[i]>1&&a[i]<a[l[i]-1])l[i]=l[l[i]-1];
for(int i=n;i;i--)
	while(r[i]<n&&a[i]<a[r[i]+1])r[i]=r[r[i]+1];
long long ans=0;
for(int i=1;i<=n;i++)ans+=(long long)a[i]*(i-l[i]+1)*(r[i]-i+1);
cout<<ans<<endl;
```


---

## 作者：Otomachi_Una_ (赞：2)

# 没学过单调栈的可以看这里

本题解将不采用单调栈求区间。

首先这一题，明显 $O(n^2)$ 会被卡死，考虑优化。

算出每个数对答案的贡献，为左区间第一个比她大的数，右区间第一个比她大的数与这个数的位置差的乘积再乘上这个数的数值,即：

$$gongxian=a_i\times(i-l_i)\times(r_i-i)$$

现在的问题转为求左右第一个比她大的数。

用优先队列 $q$ 记录当前还没有分配到答案的数值，位置，对于新加入队列的直接判断队首是否比她大，如果是，更新该位置的左右区间数值，并队首出队，不然停止循环。

## _Code_
```cpp
#include <iostream>
#include <string>
#include <queue>
using namespace std;
#define ll long long
const int MAXN=2e5+5;
int n;
ll a[MAXN];
ll l[MAXN],r[MAXN];
ll ans=0;
priority_queue<pair<int,int> > q;
void left(){
	for(int i=1;i<=n+1;i++){
		while(!q.empty()&&q.top().first>=a[i]){
			l[q.top().second]=i;
			q.pop();
		}
		q.push(make_pair(a[i],i));
	}
	q.pop();
	return;
}
void right(){
	for(int i=n;i>=0;i--){
		while(!q.empty()&&q.top().first>=a[i]){
			r[q.top().second]=i;
			q.pop();
		}
		q.push(make_pair(a[i],i));
	}
	q.pop();
	return;
}
int main(){
    cin>>n;
    a[0]=a[n+1]=-1;
    for(int i=1;i<=n;i++)
    	cin>>a[i];
    left();
    right();
    for(int i=1;i<=n;i++)
    	ans+=a[i]*(i-l[i])*(r[i]-i);
    cout<<ans<<endl;
    AK Atcoder RP++;
}
```


---

## 作者：Starlight_Glimmer (赞：2)

~~看到这道题的第一反应是线段树~~

然而小蒟蒻只会粘板 洋洋洒洒的代码实在是望而生畏

在Atcoder上浪了一波 看到tourist巨佬的程序 昨天晚上脑子有点挂机 没怎么看懂 今天早上爬起来看 实在是妙啊 不愧是巨佬



------------

首先有一个巧妙的转化思想

就是枚举区间找最小值的复杂度很高 但我们可以去找每一个元素的“贡献区间”  而且这种关系是一一对应的 即是没有两个元素 对应同一个区间

后面的找区间和统计答案等细节就在程序里面的注释里了

统计区间个数这个可以琢磨一下，有点组合的意味，求到了“最大影响区间”之后，相当于确定了左右端点的最值，还要包含当前这个元素，左右端点就可以分别在当前元素的左边和右边滑呀滑。

```cpp
#include<cstdio>
#define MAXN 200005
#define LL long long
int n,a[MAXN],pos[MAXN],pr[MAXN],ne[MAXN];
LL ans;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		pos[a[i]]=i;
	}
	for(int i=0;i<=n+1;i++)
		pr[i]=i-1,ne[i]=i+1;//pr是i的影响区间的左端点(不含) ne是右端点(不含) 注意是不含！！！
	for(int i=n;i>=1;i--)//n的排列 倒着来
	{
		int j=pos[i];
		ans+=1LL*i*(j-pr[j])*(ne[j]-j);//统计区间个数时要注意端点时不含的
		pr[ne[j]]=pr[j];
		ne[pr[j]]=ne[j];
		//核心 用当前这个值依次更新其它数的影响区间 很巧妙
		//由于是倒着来的，那么如果被更新的值要大于当前数，则没有影响，因为被更新的贡献已经算完了
		//所以就假设这些数都小于当前数 而当前数的影响区间内的所有数都要大于它自己，也大于被更新数，所以可以更新区间
	}
	printf("%lld\n",ans);
}
```

---

## 作者：AsunderSquall (赞：2)



# 题意  
给出一个长度为 $n$ 的排列，求  
$$\sum_{l=1}^n \sum_{r=l}^n \min(a_l,a_{l+1},\cdots a_r)$$  

# 题解  
这个做法时间复杂度是 $\mathcal O(n)$ 的，但是空间复杂度是 $\mathcal O(n \log n)$ 的。。。  
~~你看这个人就是逊连AGCB都想不出正解~~  

首先一眼看出应该算出每个数的贡献。  
考虑数 $k$ 的贡献，应该是算有几个区间覆盖到了它，且它是最小值。  
设覆盖 $k$ 且 $k$ 为最小值的最长区间为 $[l,r]$，$k$ 的位置是 $p$。  
那么 $k$ 的贡献即为 $(p-l+1)\times (r-p+1) \times k$。  
怎么快速求这个区间？  
本人只会无脑分治。  
我们考虑做一段区间 $[l,r]$，是 $k$ 的这个区间。那么找到 $k$ 的位置 $p$ 后可以直接计算贡献。而 $[l,p-1]$ 这段区间的最小值 $k_1$ 肯定大于 $k$，而$a_{l-1}<k<k_1$，所以 $[l,p-1]$ 是 $k_1$ 的这段区间。  
那么递归求解就行了。  
我们开一个 $pos$ 数组，记录每个值在数组中的位置，然后再开个 st表，就可以 $\mathcal O(1)$ 处理一段区间，再递归下去。  
递归次数是 $\mathcal O(n)$ 的。  
```cpp
#include<bits/stdc++.h>
#define int long long 
#define rd(x) x=read()
using namespace std;
const int N=2e5+5;
inline int read(){int x=0,f=1;char ch=getchar();while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
int n,ans;
int a[N],pos[N];
int Min[N][20];
void init()
{
	for (int i=1;i<=n;i++) Min[i][0]=a[i];
	for (int j=1;j<=19;j++)
		for (int i=1;i<=n-(1<<j)+1;i++) Min[i][j]=min(Min[i][j-1],Min[i+(1<<j-1)][j-1]);
}
int MIN(int l,int r)
{
	int L=r-l+1;
	for (int j=0;j<=19;j++) if ((1<<j)>L) {L=j-1;break;}
	return min(Min[l][L],Min[r-(1<<L)+1][L]);
}
inline void solve(int l,int r)
{
	if (r<l) return;
	if (l==r) {ans+=a[l];return;}
	int k=MIN(l,r);
	int p=pos[k];
	ans+=(p-l+1)*(r-p+1)*k;
	solve(l,p-1);solve(p+1,r);
}
signed main()
{
	rd(n);
	for (int i=1;i<=n;i++) {rd(a[i]);pos[a[i]]=i;}
	init();
	solve(1,n);
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：WuhenGSL (赞：1)

以序列中的数字为边权建图，最终建成一个有 $n+1$ 个点 $n$ 条边的链。那么问题就转化成了图上所有路径中的最小值之和。

从大到小遍历边，同时维护并查集，这样能保证当前处理的边一定是联通两个集合的最小边，这个边权对答案的贡献就是 $size[x] \times size[y] \times val$

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cctype>
#define N 200010
#define int long long
using namespace std;
int n,fa[N],siz[N];
struct graph{
	int u,v,w;
}e[N];
bool cmp(const graph &a,const graph &b)
{
	return a.w>b.w;
}
int find(int x)
{
	if(fa[x]==x)return x;
	else return fa[x]=find(fa[x]);
}
void merge(int x,int y)
{
	x=find(x),y=find(y);
	siz[y]+=siz[x];
	fa[x]=y;
}
signed main()
{
	cin>>n;
	for(int i=1;i<=n+1;++i)fa[i]=i,siz[i]=1;
	for(int i=1;i<=n;++i)
	{
		e[i].u=i,e[i].v=i+1;cin>>e[i].w;
	}
	sort(e+1,e+1+n,cmp);
	int ans=0;
	for(int i=1;i<=n;++i)
	{
		ans+=siz[find(e[i].u)]*siz[find(e[i].v)]*e[i].w;
		merge(e[i].u,e[i].v);
	}
	cout<<ans;
	return 0;
}
```

---

