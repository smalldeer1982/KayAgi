# Bindian Signalizing

## 题目描述

**题面大意**

给定一个圆和圆弧上的 $n$ 座山，每座山上有一名看守员，若连接两名看守员的圆弧（注：圆弧有左右两条，任意一条满足即可）两条中没有比（这两个看守员所在的）两座山中任何一座更高的山，则这两名看守人彼此能看到各自的信号。现在给定 $n$ 座山的高度，求能够看到彼此信号的成对看守人的数量

## 样例 #1

### 输入

```
5
1 2 4 5 3
```

### 输出

```
7
```

# 题解

## 作者：Loner_Knowledge (赞：27)

这是一道动态规划题

---

题意是有`n`座山组成一个环，两座山互相能看到的要求是相连的圆弧上没有任何其他的山高度比它们高，求能看到的山的组数。考虑一组山，我们让高度较小且的位置最靠左的那一座山负责贡献答案。

先把这个环变成一条链，把最高的山作为第一个山，按照顺序复制序列，再在最后接上一个最高的山。

设`left[i]`表示`i`左边第一个比`i`高的位置，`right[i]`表示`i`右边第一个比`i`高的位置，`count[i]`表示在`i`到`right[i]`的左开右闭区间内高度等于`i`的山的数目，那么每座山能看到的山的组数至少有`count[i]`组和`(i,l[i])`与`(i,r[i])`这两组，不过当`l[x]=0`且`r[x]=n`时其实是一组，注意判断。

于是问题就变成了求`left`数组、`right`数组和`count`数组，可以通过动态规划的思想来做。

注意**数据范围**，答案要用$long\ long$，$long\ long$在`CodeForces`要用`"%I64d"`输出。（当然如果你用`cout`另说）

```cpp
#include<cstdio>
int t[1000002],h[1000002],l[1000002],r[1000002],cnt[1000002];
int main() {
	int n,p=0;
	long long ans=0;
	scanf("%d",&n);
	for(int i=0;i<n;++i)
		scanf("%d",t+i);
	for(int i=1;i<n;++i)
		if(t[i]>t[p])			//寻找最大值
			p=i;
	for(int i=0;i<=n;++i)
		h[i]=t[(i+p)%n];		//转环为链
	for(int i=1;i<=n;++i) {
		l[i]=i-1;					//初始化为i左边第一个
		while(l[i]&&h[i]>=h[l[i]])
			l[i]=l[l[i]];			//满足条件便递推
	}
	for(int i=n-1;i>=0;--i) {
		r[i]=i+1;						//初始化为i右边第一个
		while(r[i]<n&&h[i]>h[r[i]])
			r[i]=r[r[i]];				//满足条件便递推
		if(r[i]<n&&h[i]==h[r[i]]) {
			cnt[i]=cnt[r[i]]+1;			//递推count数组
			r[i]=r[r[i]];
		}
	}
	for(int i=0;i<n;++i) {
		ans+=cnt[i];			//至少能看到的组数
		if(h[i]<h[0]) {
			ans+=2;				//另外的两组
			if(!l[i]&&r[i]==n)
				ans--;			//特判是同一组的情况
		}
	}
	printf("%I64d\n",ans);
	return 0;
}
```

---


---

## 作者：zrzring (赞：21)

[更好的阅读体验](http://zrzring.cn/index.php/archives/254)

> 题意：给定一个n个点构成的环，每个点有个高度，求点对个数，点对需满足它们相连通的两条路径中没有比它们更高的点

一个单调栈dp调了我一晚上加一中午

首先破环成链，不能单纯加倍，这样有的地方会算两次有的地方会算一次

但是鉴于特殊性质，最高的地方不可逾越，而且环映射到链上时可以循环位移，所以把最高的作为第一个位置，这样中间的位置只能按照序列的顺序去找连通的点，而不用考虑环了

之后就是一个普通的单调栈了，注意细节即可

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <queue>

#define int long long

using namespace std;

void file() {
    freopen("std.in", "r", stdin);
    freopen("wa.out", "w", stdout);
}

const int N = 1e6 + 10, M = 2e6 + 10, inf = 1e9;

inline int read() {
    bool sym = 0; int res = 0; char ch = getchar();
    while (!isdigit(ch)) sym |= (ch == '-'), ch = getchar();
    while (isdigit(ch)) res = (res << 3) + (res << 1) + (ch ^ 48), ch = getchar();
    return sym ? -res : res;
}

int n, m, t[N], h[N], s[N], cnt[N], top;

signed main() {
    n = read(); int mx = 0, pos;
    for (int i = 1; i <= n; i++) {
        t[i] = read(); if (t[i] > mx) {pos = i; mx = t[i];}
    }
    int p = 0, ans = n - 1;
    for (int i = pos + 1; i <= n; i++) h[++p] = t[i];
    for (int i = 1; i < pos; i++) h[++p] = t[i];
    top = 0;
    for (int i = 1; i <= p; i++) {
        while (s[top] < h[i] && top) ans += cnt[top--];
        if (s[top] != h[i]) s[++top] = h[i], cnt[top] = 0; ans += cnt[top]++;
    }
    while (top > 1) ans += cnt[top--]; cout << ans;
    return 0;
}
```



---

## 作者：李柯欣 (赞：10)

题目传送门：[CF5E](https://www.luogu.com.cn/problem/CF5E)。

[更好的阅读体验？](https://www.luogu.com.cn/blog/likexin/solution-cf5e)

## 题目大意：

> 有 $n$ 座围成一个环的山，每座山上都有一个看守员。两个看守员能够相互看到当且仅当连接他们所在的山的两条弧中任意一条上没有比他们更高的山，问有多少对看守员能够相互看到。

说了这么多，其实是把 [P1823](https://www.luogu.com.cn/problem/P1823) 里的队列变成了首尾相接的一个圆，其他没有任何变化。

建议先去做一下 P1823。

## 思路：

根据我们的经验，遇到环就一定要 **拆环为链** 。

但是拆环有很多方式，怎么拆才是重点。

分析一下样例，我们很快发现：对于最高峰而言，它左右两侧比他低的山是不能跨过他互相看到的。

也就是说，两两相连的山中，连线是不会跨过最高峰的。

那么我们在拆的时候就把最高峰作为第一座山，后面的山按顺序依次位移。

但是如果有多个最高峰，我们就取第一个（取最后一个也应该没问题）作为第一座山（因为最高峰之间也可以相互看到）。

剩下的就是单调栈的板了，把拆出来的链当做普通队列来处理，用单调栈处理山之间是否可以相互看到，这部分直接用 P1823 的代码即可。

但是当然没有完，考虑以下样例：

```txt
4
1 1 2 2
```

如果单纯地按照以上思路去做，那么得到的答案就会是 $4$，然而正确答案是 $6$。

为什么呢？

因为把它拆成链是这样的（把第一个最高峰当做第一座山）：

$2$ $2$ $1$ $1$

手推一下步骤后发现第一座山和第三、四座山都看不到，可是如果在环上，是可以通过另一条弧看到的。

发现这个问题只会出现在第一座山和其他山之间，那么再特判一下这种情况即可。

最后注意答案会爆 int，ans 要开 long long 的。

## 代码：

```cpp
#include<iostream>
using namespace std;
int a[1000001];
int aa[1000001];
int s[1000001];
int w[1000001];
bool pc[1000001];
int top=0;
int main(){
	//读入。
	int n;
	cin>>n;
	int maxx=-100001;
	int wz=0;
	for(int i=1;i<=n;i++){
		cin>>aa[i];
		if(aa[i]>maxx){//找到第一个最高峰。
			maxx=aa[i];
			wz=i;
		}
	}
   	//按顺序位移到 a 数组里。
	int now=0;
	for(int i=wz;i<=n;i++){
		a[++now]=aa[i];
	}
	for(int i=1;i<=wz;i++){
		a[++now]=aa[i];
	}
	long long ans=0;
	for(int i=1;i<=n;i++){//单调栈处理，搭配 P1823 食用。
		w[i]=1;
		while(top>0&&a[s[top]]<=a[i]){
			ans+=w[s[top]];
			if(a[s[top]]==a[i]){
				w[i]+=w[s[top]];
			}
			top--;
		}
		if(top){
			ans+=1;
			if(s[top]==1){ //这个位置和第一座山匹配过了，方便后面的特判。
				pc[i]=1;
			} 
		}
		s[++top]=i;
	}
	int m=0;
	for(int i=n;i>1;i--){//从后往前处理，发现算漏了就给 ans + 1。
		if(pc[i]==0&&a[i]!=a[1]&&a[i]>=m){ 
			ans++;
		}
		m=max(a[i],m);
	}
	cout<<ans;//输出。
	return 0;
}

```

[ AC 记录](https://www.luogu.com.cn/record/81020550)。

---

## 作者：kczno1 (赞：7)

先来考虑如果是链,且是一个排列怎么做.

先枚举右端点$r$

因为一个条件是$(l,r)$的数都$<=a[r]$

所以求出他左边第一个比他大的点$le$

那么显然$l$属于$[le,r]$是上面那个条件的充要条件.

现在考虑另一个条件是$(l,r)$的数都$<=a[l]$

即从$1$枚举至$r-1$,用单调栈维护后缀$max$,$l$在单调栈上.

那么显然用个单调栈就解决了问题.

环的话就是用$aa$(即复制一份)的答案-$a$的答案
(还得减掉两个方向都满足条件的$pair$,求个最大次大就可以了)

存在相同的数的话记个$cnt$就可以了

$upd$:把最大值提到最前面+特判$(1,i)$也可以转化成链，即下面的代码。

```cpp
//by kcz 1552920354@qq.com
//if you find any bug in my code
//please tell me
#include<bits/stdc++.h>
using namespace std;

template <typename T> void chmin(T&x,const T &y)
{
    if(x>y)x=y;
}
template <typename T> void chmax(T &x,const T &y)
{
    if(x<y)x=y;
}
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned short us;
typedef unsigned int ui;
typedef pair<int,int> pii;
#define rep(i,l,r) for(int i=l;i<=r;++i)
#define per(i,r,l) for(int i=r;i>=l;--i)
#define pb push_back
#define mp make_pair
#define gc (c=getchar())
int read()
{
    char c;
    while(gc<'-');
    if(c=='-')
    {
        int x=gc-'0';
        while(gc>='0')x=x*10+c-'0';
        return -x;
    }
    int x=c-'0';
    while(gc>='0')x=x*10+c-'0';
    return x;
}
#undef gc

ll sqr(const ll &x)
{
    return x*x;
}
const int N=1e6+5;
int a[N],a0[N];
pii st[N];int top;
ll solve(int n)
{
    top=1;st[1]=mp(a[1],1);
    ll ans=0;
    rep(i,2,n)
    {
        while(top&&st[top].first<a[i]){ans+=st[top].second;--top;}
        if(st[top].first==a[i])
        {
            ans+=st[top].second+bool(top>1);
            ++st[top].second;
        }
        else 
        {
            ++ans;
            st[++top]=mp(a[i],1);
        }
    }
    static bool have[N];
    int mx=0;
    rep(i,2,n)
    {
        if(a[i]>=mx){have[i]=1;mx=a[i];}
    }
    mx=0;
    per(i,n,2)
    if(a[i]>=mx)
    {
        ans+=!have[i];
        mx=a[i];
    }
    return ans;
}
int main()
{
  //  freopen("1.in","r",stdin);//freopen("1.out","w",stdout);
    int n;
    cin>>n;
    rep(i,1,n)a0[i]=read();
    int mxi=1;
    rep(i,2,n)
    if(a0[i]>a0[mxi])mxi=i;
    int top=0;
    rep(i,mxi,n)a[++top]=a0[i];
    rep(i,1,mxi-1)a[++top]=a0[i];
    cout<<solve(n);
}



```

---

## 作者：xtx1092515503 (赞：5)

这题实际上可以不写DP的（虽然我一开始的想法也是单调栈DP……）

首先，我们可以按照高度从大到小依次添加进每一个塔。因为对于某一个塔$x$，所有会与它产生关系的塔可以分成三类：比它高的，比它矮的，和它一样高的。

对于和比它矮的塔之间的关系，我们在加入比它矮的塔时再讨论。则我们现在只需要关注所有高度大于等于它的塔。

当我们加入这个塔时，所有比它高的塔，最多只有两个能和它产生关系，就是位置紧贴它的两个比它高的塔（当然，在比它高的塔只有一个时，则只有一个）。

而所有与它高度相等的塔中，如果它们处于同一对高塔之间，则它们两两之间都会产生关系。

在代码实现时，我们可以首先找到高度最高的塔，以它为$0$号塔开始重编号，这样就保证对于任何非$0$号塔一定至少能找到一个比它编号小的且比它高的塔。

代码（附有英文注释）：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,mxp,res;
pair<int,int>p[1001000];
set<int>s;
signed main(){
	scanf("%lld",&n);
	for(int i=0;i<n;i++){
		scanf("%lld",&p[i].first);
		if(p[mxp].first<p[i].first)mxp=i;
	}
	for(int i=0;i<n;i++)p[i].second=(i-mxp+n)%n,p[i].first*=-1;
	sort(p,p+n);
	for(int i=0,j=0;i<n;){
		while(j<n&&p[j].first==p[i].first)j++;//all the towers in section [i,j) have the same height 
		int sz=s.size(),cnt=0,prev=-1;
		if(!sz)res+=(j-i)*(j-i-1)/2;//in this case, all the towers in section [i,j) are the tallest. So any pair among them is valid.
		else for(int k=j-1;k>=i;k--){
			int cur=*(--s.lower_bound(p[k].second));
			if(cur!=prev)prev=cur,res+=cnt*(cnt-1)/2+cnt*min(sz,2ll),cnt=0;//all the towers which has the same prev are in the same section; Pairs among them and connections with boundaries are valid.
			cnt++;
		}
		res+=cnt*(cnt-1)/2+cnt*min(sz,2ll),cnt=0;//cnt*(cnt-1)/2: pairs among them;cnt*min(sz,2ll): two connections with boundaries
		for(int k=i;k<j;k++)s.insert(p[k].second);
		i=j;
	}
	printf("%lld\n",res);
	return 0;
}
```


---

## 作者：小木虫 (赞：4)

看了一圈好像没有一样的解法 qwq ，那我就来水一发单调栈+树状数组的题解罢 。 



------------

**对于这道题，我们第一眼看上去就可以立马想到一个算法：单调栈**  
因为这道题是有部分隐含信息的：  
（这道题要求 pair 的数量，所以对于每一个节点算它前面的节点就行了。）  
对于任何节点，它所能照到的节点必然是没有被阻挡的（废话）并且是小于等于当前节点的高度的**或者**是大于此节点高度的第一个节点。  
图解：（柱子高度代表山的高度，红色的柱子代表能照到的，黑色表示不能）  
![](https://cdn.luogu.com.cn/upload/image_hosting/4a3bqofr.png)
阻挡的问题我们可以使用单调栈来解决，但是高度的问题暂时不能解决。  
于是我们想到：可以用树状数组来记录在单调栈内的每个高度的山的数量啊！  
一看数据： 1e9  emmm...  
离散化是个好东西，我们将山进行排序，给每座山通过离散化的方式重新赋值一个高度。  
接下来只剩最后一个问题了：环要如何处理？  
其实就跟几位楼上大神说的一样，将最高的一座山作为起点，因为没有任何人的视线能够越过它！我们在最后再对第一座山做一次环的特判：将栈内的元素一一弹出，如果这个节点之前就已经在正方向圆弧上与最高山配过对了，那么就无视它，否则答案 +1 。  
code:
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int h[1000005];
int c[1000005];
int Stack[1000005];
int size;
//单调栈和栈顶 
long long ans;
//记得开long long啊 
int MAX,adr,tot;
int num[1000005];//记录每座山离散化之后的高度 
bool vis[1000005];//记录这座山之前有没有与最高山配过对 
struct node{
	int x,y;
}S[1000005];//用来离散化的结构体 
int cnt;
bool cmp(node a,node b){
	return a.x<b.x;
}
long long tree[1000005];
//树状数组模板qwq 
int lowbit(int x){return x&(-x);} 
void update(int x,int add){
	while(x<=cnt){
		tree[x]+=add;
		x+=lowbit(x);
	}
}
int query(int x){
	int ans=0;
	while(x!=0){
		ans+=tree[x];
		x-=lowbit(x);
	}
	return ans;
}
int q1,q2,q3;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>h[i];
		if(h[i]>=MAX){
			MAX=h[i];
			adr=i;
			//记录最高峰的位置 
		}
	}
	tot=n;
	//断环 
	for(int i=adr;i>=1;i--){
		c[tot--]=h[i];
	}
	for(int i=n;i>adr;i--){
		c[tot--]=h[i];
	}
	//离散化 
	for(int i=1;i<=n;i++){
		S[i].x=c[i];
		S[i].y=i;
	}
	sort(S+1,S+n+1,cmp);
	for(int i=1;i<=n;i++){
		if(S[i].x!=S[i-1].x)++cnt;
		num[S[i].y]=cnt;
	}
	vis[n]=true;
	for(int i=n;i>=1;i--){
		//为了常数优化不得不用变量代替直接的函数调用，需要的可以把它变回来（会TLEQWQ 
		q1=query(num[i]);
		q2=query(cnt);
		q3=query(cnt-1);
		ans+=q1;//加上小于等于此山峰高度的栈内山峰 
		if(num[i]==cnt){//如果它是可能不唯一的最高峰 
			vis[i]=true;
		}
		if(q2-q1){//判断栈内有没有比目前山峰更高的山峰 
			if((q3-q1==0)&&q2-q3==1){//特判第一座高于目前山峰的山峰 是否是最高峰 
				vis[i]=true;
			}
			ans++;//加上一个方案数 
		}
		while(size>=1&&c[Stack[size]]<c[i]){
			//弹出被遮挡的山峰（单调栈） 
			update(num[Stack[size]],-1);//将此山峰高度的山峰数量-1 
			size--;
		}
		//将目前山峰加入栈内 
		Stack[++size]=i;
		update(num[i],1);//将此山峰高度的山峰数量+1 
	}
	for(int i=size;i>=1;i--){//环の特判 
		if(vis[Stack[i]])continue;//假如之前配过对了就跳过 
		ans++;
	}
	cout<<ans;
	return 0;
}
```



---

## 作者：Hasinon (赞：3)

主要探讨一下本题中环带来的影响。  
结论是只有当最高峰唯一的时候才需要去重——求过。
（起码按照我的算法 : ） ）

## Part1
我们先尝试什么都不管，对于一座山,向右边扫，找合法山且高度小于等于它，向左边扫，找合法山且高度小于它。  
**只管右边的相等高度山，是为了防止一对高度相等的山算两遍的情况**   


我们可以把原环复制个五遍，然后在最中间的地方随便选一个起点，一个单调队列维护一个递减数组，左右都扫一下，实现统计。  

显然，很多细节，但这个方法之后可以得到改良 ：)。

## Part2
但是显然，有些山可能从左边扫合法，从右边扫也合法。如何去重？  

对于只有一座最高峰的时候：  

这是以最高峰向左右扫的合法山，左绿箭头代表向左扫可合法，右红箭头代表向右扫可合法。
![](https://cdn.luogu.com.cn/upload/image_hosting/yp7qn9sg.png)  
通过 Part 1 我们的单调队列做法可以发现，向左扫，找到的合法山中最右边，同时也是最高的那几座山，在向右扫的时候也会被扫到，所以减去它们的重复贡献即可。

至于其他山峰，因为最高峰始终高于他们，向左扫的合法山不可能在最高峰的左边，向右扫同理。所以向左扫和向右扫不会有交集。  

对于有很多座最高峰的时候：（这种时候的非最高峰情况同上，skip）  
![](https://cdn.luogu.com.cn/upload/image_hosting/b2ojfv1r.png)

对于从左往右数的第一座最高峰，合法山情况如图，所以其他最高峰会被它多次贡献答案..吗？  

一对高度相等的山算两遍，是能够被去重的。  

所以这种情况不会算重。


## 后记

好了，去重也讨论完了，我们把用单调队列算答案的地方优化一下。  

发现只有向右扫的时候，我们需要统计小于等于它的合法山，而向左扫只需要管小于，所以对于第 $i$ 座山，向右扫到一座最高峰，后面的山就不会再对第 $i$ 座山贡献答案了。

所以向右扫从任意最高峰的左边开始扫 $n$ 座，向右扫从任意最高峰的右边开始扫 $n$ 座就可以了。

是代码
```cpp
// By Hasinon,the juruo who's waiting for AFO life.
/*Mlm:  Tlm:*/
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define mid ((l+r)>>1)
#define FOR(i,a,b) for(int i=(a); i<=(b); ++i)
#define ROF(i,a,b) for(int i=(a); i>=(b); --i)
using namespace std;
struct node{
	ll x,z;
};
const ll N=1e6;
ll a[N*3+10];
deque<node> q;
int main() {
//	freopen("CF5E.in","r",stdin);
//	freopen("CF5E.out","w",stdout);
	ll n=gt(),ans=0,cnt=0;
	FOR(i,1,n) a[i]=gt();
	FOR(i,n+1,n*2) a[i]=a[i-n];
	ll st=0,mmax=0;
	FOR(i,1,n*2){
		if(mmax<=a[i]){
			mmax=a[i];
			st=i;
		}
	}
//	printf("st:%lld\n",st);
	ROF(i,st-1,st-n){
		ll lans=0;
		while(q.size()&&q.front().x<a[i]){
			lans+=q.front().z;
			q.pop_front();	
		} 
		if(q.front().x==a[i]){
			lans+=q.front().z;	
		} 
		ans+=lans;
//		printf("%lld\n",lans);
		if(q.size()&&q.front().x==a[i]){
			++q.front().z;
		}
		else q.push_front((node){a[i],1});
	}
//	printf("ans1:%lld\n",ans);
	q.clear();
	FOR(i,n*2+1,n*3) a[i]=a[i-n];
	FOR(i,st+1,st+n-1){
		ll lans=0;
		while(q.size()&&q.front().x<a[i]){
			lans+=q.front().z;
			q.pop_front();	
		} 
		ans+=lans;
		if(q.size()&&q.front().x==a[i]){
			++q.front().z;
		}
		else q.push_front((node){a[i],1});
	}
	ll lans=0;
	while(q.size()>=2&&q.front().x<a[st+n]){
		lans+=q.front().z;
		q.pop_front();	
	} 
	ans+=lans;
	printf("%lld",ans);
}



```



---

## 作者：Imiya (赞：2)

看到本题立马想到[笛卡尔树](https://oi-wiki.org/ds/cartesian-tree/)。

先考虑把环转换成线性，对于这个例子 `1 5 3 4 2`，发现可以环拆成 `5 3 4` 和 `4 2 1 5` 两个序列，使两者互不影响，也就是根据最大值和次大值分成两部分。那么环的问题就解决了。

暂时不考虑有重复数字，对于一串从环中拆出来的数 `5 1 3 2 4`，把它挂进一个大根笛卡尔树中（如下）。因为笛卡尔树的性质，显然一个数可以和**左子节点的右链**或**右子节点的左链**中的点组成符合条件的数对。

即 $5$ 到 $1,3,4$；$4$ 到 $3,2$；$3$ 到 $1,2$。

由于每一个点的左右链大小可以总共 $O(n)$ 的时间求出，所以这个方案看起来是可行的。

![](https://cdn.luogu.com.cn/upload/image_hosting/spdbi5kg.png)

考虑一下重复数字，发现事情稍微变得棘手起来，实际上我也在这方面用了最多时间。发现一个性质，笛卡尔树单调栈建树后，若一堆数相同且中间没有更大的数，那么这堆数一定在一条链上且方向固定（左链还是右链取决于是否取等于）。

下图是序列为 `2 2 2 1 1 4 1` 且单调栈建树取等于时（当然你也可以自己构造成类似的样子）的笛卡尔树。

![](https://cdn.luogu.com.cn/upload/image_hosting/aexx63q5.png)

再回顾一下使用笛卡尔树求解的原理，即求与给定结点中间没有更大点的点集大小，那么显然与给定结点的子结点键值相同，且在同一条链上的点集一定属于所要求的点集。所以只需要 dfs 时再记录一个与当前结点键值相同且在一条链上的点集大小，与左右链大小合并一下即可。

时间复杂度是 $O(n)$ 的，但常数大了些，跑得不如单调栈 dp 快 qwq。当然也可以加一个缩点小优化，但实测快不到哪里去就是。

代码

```cpp
#include<iostream>
#include<cstring>
#define int long long
using namespace std;
const int N=1000100;
int b[N];
int n,a[N];
inline int read(){
    int r=0,i=getchar();
    while(i<'0'||i>'9')i=getchar();
    while(i>='0'&&i<='9')r=(r<<1)+(r<<3)+(i^48),i=getchar();
    return r;
}
int id1=0,id2=0;
void init(){
    cin>>n;
    for(int i=1;i<=n;i++){
        a[i]=read();
        if(a[i]>a[id1])id1=i;
    }
    for(int i=id1+1;i<=n;i++){
        if(a[i]>=a[id2])id2=i;
    }
    for(int i=1;i<id1;i++)if(a[i]>=a[id2])id2=i;
}
int ls[N],rs[N],stk[N],top,lc[N],rc[N],t[N];
void dfs(int id){
    if(!id)return;
    dfs(ls[id]);dfs(rs[id]);
    if(b[id]==b[ls[id]])t[id]=t[ls[id]]+1;
    else t[id]=1;
    //记录左链上相同的数的数量并入右链。
    lc[id]=lc[ls[id]]+1;
    rc[id]=rc[rs[id]]+t[id];
}
inline int get(int l,int r){
    memset(ls,0,sizeof(ls));
    memset(rs,0,sizeof(rs));
    memset(lc,0,sizeof(lc));
    memset(rc,0,sizeof(rc));
    memset(stk,0,sizeof(stk));
    memset(b,0,sizeof(b));
    memset(t,0,sizeof(t));
    top=0;
    int k=0,res=0;
    if(l<=r)
        for(int i=l;i<=r;i++)
            b[++k]=a[i];
    else{
        for(int i=l;i<=n;i++)
            b[++k]=a[i];
        for(int i=1;i<=r;i++)
            b[++k]=a[i];
    }
    for(int i=1;i<=k;i++){
        int lst=0;
        while(top&&b[stk[top]]<=b[i])lst=stk[top--];
        //此处取了等于，所以同一个子树中相同的数连续分部在左链上。
        ls[i]=lst;
        if(top)rs[stk[top]]=i;
        stk[++top]=i;
    }
    dfs(stk[1]);
    for(int i=1;i<=k;i++)
        res+=rc[ls[i]]+lc[rs[i]];
    return res;
}
signed main(){
//    freopen("read.in","r",stdin);
    init();
    cout<<get(id1,id2)+get(id2,id1)-1;
    return 0;
}
```

---

## 作者：QianianXY (赞：2)

## 前置知识

- [单调栈](https://www.luogu.com.cn/problem/P5788)

本文默认读者已熟练掌握此算法。

## **题目分析**

可以先考虑山不在圆上，而是在一条直线上。这样显然是一个单调栈板子。

难点在于题目的模型是环，因此可以使用破环为链的技巧。

如何破环？有一个显然的性质，**任意两座可以通讯的山之间，必然不经过最高的山**。（假设最高的山只有一座）

所以可以找出最高的山，以它为链头，按顺序组成一条链。

举个例子：

```
样例
1 2 4 5 3 (环）

5 3 1 2 4 (链）
```

现在直接用单调栈算就完事了吗？不。

```
3 5 2 4 6（环）

6 3 5 2 4（链）
```

在这组数据当中，直接计算的结果是 $6$，但答案是 $7$。原因是直接计算漏了 $4 \rightarrow 6$ 这一对。

解决方案：定义数组 $c_i$，标记是否在单调栈中与链头配对过。如果没有，则倒序判断是否可以从另一方向绕过去与链头配对。

```cpp
int c[N], maxn = 0;
for (rei i = n; i > 1; i--)
{
	if (b[i] >= maxn && !c[i]) ans++; //与链头配对成功
	maxn = max(maxn, b[i]);
}

// maxn: 链尾到i点间（不含i点）最高的山高
// b[i] >= maxn: i点与链头间没有阻隔
```

时间复杂度 $O(n)$。

不经过刻意卡常，截至本题解提交前，该代码在300多份提交中排第八。

## **code**

```cpp
#include <bits/stdc++.h>
#define rei register int
#define N 1000010
using namespace std;
typedef long long ll;

ll n, a[N], st[N], top, ans, maxn, b[N], c[N];
struct node {int res, sum;} d[N]; // res: 自己左边可配对的山数量   
								  //sum：单调栈中相同高度的山数量 

template <typename T> inline void read(T &x)
{
	x = 0; ll f = 1; char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -f; ch = getchar();}
	while (isdigit(ch)) {x = x * 10 + ch - 48; ch = getchar();}
	x *= f;
}

int main()
{
	read(n);
	for (rei i = 1; i <= n; i++) 
	{
		read(a[i]);
		if (a[maxn] < a[i]) maxn = i; // 找最高山 
	}
	for (rei i = 1; i <= n; i++) b[i] = a[(i + maxn - 2) % n + 1]; // 破环为链 
	for (rei i = 1; i <= n; i++)
	{
		d[i].sum = 1;
		while (top && b[i] >= b[st[top]])
		{
			if (b[i] == b[st[top]]) d[i].sum += d[st[top]].sum;
			d[i].res += d[st[top]].sum; top--;
		} 
		if (top && b[i] < a[maxn]) d[i].res++;
		if (top == 1 && d[st[top]].sum == 1 || b[i] == a[maxn]) c[i] = 1; // 不需要再次和链头配对 
		st[++top] = i;
		ans += d[i].res;
	}
	maxn = 0;
	for (rei i = n; i > 1; i--)
	{
		if (b[i] >= maxn && !c[i]) ans++;
		maxn = max(maxn, b[i]);
	}
	printf("%lld", ans);
	return 0;
}
```


---

## 作者：黎明行者 (赞：2)

【题目分析】

先不要考虑这是一个烦人的环，假设题目改成：所有的山排成一行，该怎么做？

可以统计每座山向右可以看到几座山。

简单分析一下：对于第 $i$ 座山，他一定可以看到 $i+1$，因为中间根本没有任何遮挡。再假设 $h[i+1]\leq h[i]$，这样只要 $h[i+2]\leq h[i+1]$ , $i$ 就可以看见 $i+2$。

所以 $i$ 对于任意$j(i<j,h[i]\geq h[j])$，可以$i$看见$j$的充要条件就是任意 $k(i<k<j)$ 有 $h[j]\geq h[k]$。

关键的一步来了，对于每一个$i$，找到最小的 $j$ 满足 $h[j]\geq h[i]$ 记作 $nhe[i]$ 找到最小的$j$满足 $h[j]<h[i]$ 记作 $nh[i]$ 。

这一步可以用单调栈完成。

然后对于每一个 $i$，我们从 $i$ 向 $nhe[i]$ 连一条边。

可以发现：所有的边会形成一个森林。因为每一条边一定向右，因此不会有环，而每一个点只有一个出度，这个出度指向的点可以当作它的父亲。

为了方便处理，在最后（第 $n+1$ 个位置）加一座珠穆朗玛峰（看作无限高）。这样森林一定会合并成一棵树。

从一个点 $i+1(i< n)$ 开始沿着边走，一定可以走到 $nh[i]$。

在这一走的过程中，经过的山就是$i$向右可以看到的所有山。由于这是一棵树，经过的点数可以用 $nh[i]$ 和 $i+1$ 的深度差算出来。

接下来考虑这个烦人的环。常见的方法就是把原数组复制一份放在后面。在这个数组上用刚才的方法建立一棵树。

这样看起来好像问题就解决了，只要按照刚才的方法统计就好了。

实际上还有亿点细节等着处理。

比如原数组是
${1,2,3,4,1}$，

那么复制，然后加一个无穷高的山以后就是 ${1,2,3,4,1,1,2,3,4,1,+\infty }$

这样会出现 $nhe[4]=11$，但从5开始走，走到9就该停了，走到11就已经走过了。这里就要特殊处理一下。

还有由于这是一个环，那么有的二元组会被统计两次，因为它们在两个方向都可以互相看到。好在这些二元组很少，只有最高的那些山才可以互相在两个方向看见。

具体来讲，就是如果最高的那一批山之间一定可以在两个方向互相看到。如果最高的山只有一座，那么它和所有的次高山也会被统计两次。其他情况都只会统计一次。所以我们只需要统计最高的山的数量和次高山的数量就可以轻轻松松地去掉这些重复统计的部分。

【代码】

```cpp

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

typedef long long ll;
const int N=2e6+6,INF=0x7fffFFFF;

int n;
int h[N],nhe[N],nh[N];
int stk[N],top=0;

int read()
{
	int res=0; char ch=getchar();
	while (ch<'0'||'9'<ch) ch=getchar();
	while ('0'<=ch&&ch<='9') res*=10,res+=ch-'0',ch=getchar();
	return res;
}
struct Edge
{
	int t,nxt;
	Edge(int t,int nxt) : t(t),nxt(nxt) {}
	Edge() {nxt=-1;}
};
struct Graph
{
	int cnt,hd[N],dep[N];
	Edge ed[N];
	Graph()
	{
		memset(hd,-1,sizeof(hd));
	}
	void addEdge(int x,int y) {ed[++cnt]=Edge(y,hd[x]); hd[x]=cnt;}
	void dfs(int x)//needs preing
	{
		for (int i=hd[x];i!=-1;i=ed[i].nxt)
		{
			int y=ed[i].t;
			dep[y]=dep[x]+1;
			dfs(y);
		}
	}
};
Graph gra;
int main()
{
	//freopen("data.in","r",stdin);
	n=read();
	for (int i=1;i<=n;i++) h[i]=h[i+n]=read();
	int n2=n<<1; h[n2+1]=INF;
	for (int i=1;i<=n2+1;i++)
	{
		while (top && h[stk[top]]<=h[i])
			nhe[stk[top--]]=i;
		stk[++top]=i;
	}
	top=0;
	for (int i=1;i<=n2+1;i++)
	{ 	
		while (top && h[stk[top]]<h[i]) nh[stk[top--]]=i;
		stk[++top]=i;
	}
	for (int i=1;i<=n2;i++) gra.addEdge(nhe[i],i);
	gra.dep[n2+1]=1;//pre
	gra.dfs(n2+1);
	ll ans=0;
	for (int i=1;i<=n;i++)
	{
		int tl=nh[i];
		if (tl==n2+1) tl=i+n,ans--;
		ans+=gra.dep[i+1]-gra.dep[tl]+1;
	}
	ll mxh=0,mxn=0,mxh2=0,mxn2=0;
	for (int i=1;i<=n;i++) if (mxh<h[i]) mxh=h[i];
	for (int i=1;i<=n;i++) if (mxh2<h[i] && h[i]!=mxh) mxh2=h[i];
	for (int i=1;i<=n;i++) if (h[i]==mxh) mxn++; else if (h[i]==mxh2) mxn2++;
	ans-=(mxn*(mxn-1))/2;
	if (mxn==1) ans-=mxn*mxn2;
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：zyc____ (赞：2)

## CF5E

### 进入正题

### 题意

大致意思是给一个环，环上有n个点，如果每两个点之间没有比这两个点大的点，则这两个点能连一条线，问最多能连几条线。

### 分析

假设对于i，我们已经计算出了left[i], right[i], same[i]，其中left[i]表示i左侧比第一个比i高的位置，right[i]表示i右侧第一个比i高的位置，same[i]表示从i到right[i]的左开右闭区间内高度等于i的山的数目。简而言之，left和right是位置，而same是数目。

那么对于一座山i而言，它可以和left[i] 和 right[i]都构成能互相看见的pair，并且和i到right[i]之间所有高度等于i的山构成能互相看见的pair。

所以问题就是计算left数组、right数组和same数组。

### AC代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=1000010;
int a[maxn],b[maxn],lef[maxn],rig[maxn],c[maxn],n,mid,ma=-1;
ll ans;
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
        if(a[i]>ma)
        {
            ma=a[i];
            mid=i;
        }
    }
    mid--;
    for(int j=1;j<=n;j++)
        b[j]=a[(mid+j)%n];   
    lef[1]=1;
    for(int i=2;i<=n;i++)
    {
        lef[i]=i-1;
        while(lef[i]>1&&b[lef[i]]<=b[i])
            lef[i]=lef[lef[i]];
    }
    for(int i=n;i>=1;i--)
    {
        rig[i]=i+1;
        while(rig[i]<=n&&b[rig[i]]<b[i])
            rig[i]=rig[rig[i]];
        if(rig[i]<=n&&b[rig[i]]==b[i])
        {
            c[i]=c[rig[i]]+1;
            rig[i]=rig[rig[i]];
        }
    }
    for(int i=2;i<=n;i++)
    {
        ans+=c[i]+2;
        if(lef[i]==1&&rig[i]==n+1)
            ans--;
    }
    printf("%lld\n",ans);
  return 0;
}
```


---

## 作者：LCuter (赞：1)

## CF5E 题解

##### $\text{Description}$

环上有 $n$ 个点，每个点有高度，定义两个点能互相看到当且仅当存在一段端点为该两点的**圆弧**内任意点高度都不超过该两点。求能相互看见的点对数。

$1\le n\le 10^6$

##### $\text{Solution}$

首先对高度离散化。

由于环可以任意循环移位，我们任取某一个最大值作为这个环的首端，这样除了最大值，其它任意元素绕一圈回来都只能撞到最大值，无法继续前进。

接下来考虑将能相互看见的点分两类。第一类是两点高度相同，对此我们可以按高度从大到小进行计算，让高于它的节点将环分成若干段，对于每段分别计算答案；第二类是两点高度不同，我们考虑在高度较低的点计算，这样只需考虑左右第一个高度大于它的点，同样从大到小计算，二分出左右的值，注意在环上可能这两个点都是环的第一个点，需要减去重复的值。

上述过程可以通过 `std::set` 维护，时间复杂度 $\mathcal O(n\log n)$。

##### $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define REG register
using namespace std;
typedef long long ll;
const int N=1e6+10;
inline void read(int& x){
    static char c;
    while(!isdigit(c=getchar()));x=c^48;
    while(isdigit(c=getchar()))x=(x*10)+(c^48);
}

int n,M,C;
int T[N],srt[N],H[N];
vector<int> Pos[N];
set<int> Occ;
set<int>::iterator it;

ll Ans;

inline void Work(){
    read(n);
    for(REG int i=1;i<=n;++i) read(T[i]),srt[i]=T[i];
    sort(srt+1,srt+n+1),C=unique(srt+1,srt+n+1)-srt-1;
    for(REG int i=1;i<=n;++i){
        T[i]=lower_bound(srt+1,srt+C+1,T[i])-srt;
        if(T[i]>T[M]) M=i;
    }
    for(REG int i=1;i<=n;++i) H[i]=T[(M+i-2)%n+1],Pos[H[i]].push_back(i);
    Occ.insert(n+1);
    for(REG int i=C;i;--i){
        int cnt=0,lst=0;
        for(int P:Pos[i]){
            it=Occ.lower_bound(P);
            if((*it)^lst) Ans+=1ll*cnt*(cnt-1)/2,cnt=1,lst=*it;
            else ++cnt;
            if(i==C) continue;
            if(*it<=n) Ans+=2;
            else
                if(*(--it)==1) ++Ans;
                else Ans+=2;
        }
        Ans+=1ll*cnt*(cnt-1)/2;
        for(int P:Pos[i]) Occ.insert(P);
    }
    printf("%lld\n",Ans);
}

int main(){Work();}
```



---

## 作者：Durancer (赞：1)

### 前置知识

- 线性DP

- 单调栈

### 思路

在环上做肯定不好做，所以考虑如何转换成一个合法的链型结构。

我们发现，由**一个**最高点分开的两部分是互不影响的，假设一个最高的的位置是 $\text{pos}$ ，那么就可以组成一个 $\text{pos}+1\to n\to \text{pos-1}$ 的一个链，这样就可以做到不重不漏的计数了，剩下的就是一个简单的单调栈。

简单讲一讲如何用单调栈实现它：

用的是栈顶到栈底递增的单调栈。

加入一个元素的时候，栈顶不够高就直接弹出，顺便加上它的值，知道比当前这个高或者相同为止，因为那些比当前矮的，对后面的不会有贡献了，所以就直接加上扔掉即可。

这样就可以一步步得出不重不漏的结果了。

### 代码实现

```cpp
/*

	断环成链，干干干 

*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<stack>
#include<vector>
#include<algorithm>
#include<cmath>
#define int long long
using namespace std;
const int N=1e6+9;
const int M=1e6+9;
int a[N],h[N],m;
int n;
int stk[N],top;
int cnt[N];//记录
int maxn,pos;
int ans; 
int read()
{
	int f=1,x=0;
	char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=(x<<1)+(x<<3)+(s^'0');s=getchar(); }
	return f*x;
}
void Prepare()
{
	for(int i=pos+1;i<=n;i++)
		h[++m]=a[i];
	for(int i=1;i<=pos-1;i++)
		h[++m]=a[i];
}
void DP()
{
	for(int i=1;i<=m;i++)
	{
		while(stk[top]<h[i] and top!=0)
		{
			ans+=cnt[top];
			top--;
		}
		if(stk[top]!=h[i])
		{
			stk[++top]=h[i];
			cnt[top]=0;
		}
		ans+=cnt[top];//记录这个总共有多少个，重复的不用加入 
		cnt[top]++;//判断相同的个数 
	}
}
signed main()
{
	n=read();
	ans=n-1;//相邻的 
	for(int i=1;i<=n;i++)	
	{
		a[i]=read();
		if(a[i]>maxn)
		{
			pos=i;
			maxn=a[i];
		}
	}
	Prepare();
	DP();
	while(top>1)//最高的不需要加 
	{
		ans+=cnt[top];
		top--;
	}
	cout<<ans<<endl;
	return 0;
} 

```

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2400}$
---
### 解题思路：

就是一个单调栈的题目放在了环上。

可以发现，对于绝大多数的山峰而言，其实依然只有一条观察的路径路径可以选择，也就是没有最高峰的那一条路径。那么从这个角度出发可以将这个环从一个最高峰的位置断开成一条链。

然后考虑具体的单调栈做法。对于一个山峰，如果在其后面有一个比它还要高的山峰，那么这个山峰无论如何都不可能再产生更多的方案，可以直接删除。那么也就是维护了一个高度单调不增的单调栈。除了相邻的看到之外，每一次弹出的时候也就相当于“看到了”，在方案数上累加即可。处理时还要注意相同高度是可以相互看到的。（其实就是正常的单调栈，没啥区别。）

最后对于作为断开点的最高峰需要额外计算一次代价，因为这这位置是可以从另一侧看到的，而在之前的处理中只计算了一次。

方案数较多，开 $\text{long long}$。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
const int MAXN=1000005;
int n,a[MAXN],top,st[MAXN],maxn,maxi,cnt[MAXN],b[MAXN],ans,v[MAXN];
signed main(){
	scanf("%I64d",&n);
	for(int i=1;i<=n;i++)scanf("%I64d",&a[i]);
	for(int i=1;i<=n;i++)if(a[i]>maxn)maxn=a[i],maxi=i;
	for(int i=maxi+1;i<=n;i++)b[i-maxi]=a[i];
	for(int i=1;i<maxi;i++)b[n-maxi+i]=a[i];
	for(int i=1;i<n;i++){
		while(st[top]<b[i]&&top>0)ans+=cnt[top],top--;
		
		if(st[top]==b[i])cnt[top]++,ans+=cnt[top]-1+(cnt[top-1]>=1);
		else ans+=(cnt[top]>=1),cnt[++top]=1,st[top]=b[i];
	}
	maxn=0;
	for(int i=1;i<n;i++){
		if(b[i]>=maxn)v[i]=1;
		maxn=max(maxn,b[i]);
	}
	maxn=0;
	for(int i=n-1;i>=1;i--){
		if(b[i]>=maxn)v[i]=1;
		maxn=max(maxn,b[i]);
	}
	for(int i=1;i<=n;i++)
	ans+=v[i];
	printf("%I64d\n",ans);
	return 0;
}
```


---

## 作者：Tony102 (赞：0)

[Link](https://www.luogu.com.cn/problem/CF5E)

[51nod 1482](https://www.51nod.com/Challenge/Problem.html#problemId=1482)

[My Blog](https://tony102.com/archives/128/)


## Sol

首先断环成链。

我有一个很 naive 的做法，通过双指针，建立线段树，每次挪动左右指针时询问当前区间的最大值是否 $\leq$ 左右指针的高度，统计答案。

这样过不去 $n \leq 3 \times 10^6$ 的数据。但是发现，用线段树查这个最小值这个操作非常愚蠢。

最高的山无论如何都会挡住别的山。我们以最高的山作为第一座山，其余的山按照原顺序排列。因为最高的山不会有除了相邻的不会有任何中间还有跨度的两座山对答案有贡献。

我们设 $l_i$ 表示往左第一个比 $i$ 高的位置，$r_i$ 即往右同理的位置。那么就有 $(i,l_i)$ 和 $(i, r_i)$ 两组。注意在 $(l_i, r_i]$ 这个区间中与 $i$ 高度相等的山也要给答案贡献。

求 $l_i$ 和 $r_i$ 可以用一个单调栈来实现，最后因为顺时针和逆时针都可以统计答案，断环成链之后相当于正着做一遍反着做一遍就行了。



## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int SIZE = 3e6 + 5;

int n, m;
int a[SIZE], b[SIZE], sta[SIZE], l[SIZE], r[SIZE], tag[SIZE];

namespace GTR {
	const int bufl = 1 << 15;
	char buf[bufl], *s = buf, *t = buf;
	inline int fetch() {
		if (s == t) { t = (s = buf) + fread(buf, 1, bufl, stdin); if (s == t) return EOF; }
		return *s++;
	}
	inline int read() {
		int a = 0, b = 1, c = fetch();
		while (c < 48 || c > 57) b ^= c == '-', c = fetch();
		while (c >= 48 && c <= 57) a = (a << 1) + (a << 3) + c - 48, c = fetch();
		return b ? a : -a;
	}
} using GTR::read;

int main() {
    n = read(); int mx = 0;
    for (int i = 1; i <= n; ++ i) {
        a[i] = read();
        if (a[mx] < a[i]) mx = i;
    }
    for (int i = mx; i <= n; ++ i) b[++ m] = a[i];
    for (int i = 1; i < mx; ++ i) b[++ m] = a[i];
    int top = 0;
    for (int i = 2; i <= n; ++ i) {
        while (top && b[i] >= b[sta[top]]) -- top;
        l[i] = sta[top], sta[++ top] = i;
    }
    sta[top = 0] = n + 1;
    for (int i = n; i >= 2; -- i) {
        while (top && b[i] >= b[sta[top]]) {
            if (b[i] == b[sta[top]]) tag[i] = tag[sta[top]] + 1;
            -- top;
        }
        r[i] = sta[top], sta[++ top] = i;
    }
    LL ans = 0; mx = 0;
    for (int i = 2; i <= n; ++ i) {
        if (l[i] > 0) ++ ans;
        if (r[i] <= n) ++ ans;
        ans += tag[i];
    }
    memset(tag, 0, sizeof(tag));
    for (int i = 2; i <= n; ++ i) {
        if (b[i] >= mx) tag[i] = 1;
        mx = std::max(mx, b[i]);
    }
    mx = 0;
    for (int i = n; i >= 2; -- i) {
        if (b[i] >= mx) tag[i] = 1;
        mx = std::max(mx, b[i]);
    }
    for (int i = 2; i <= n; ++ i) ans += tag[i];
    printf("%lld\n", ans);
    return 0;
}
```



---

