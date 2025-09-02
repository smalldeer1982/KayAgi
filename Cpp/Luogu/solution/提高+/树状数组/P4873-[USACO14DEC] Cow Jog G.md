# [USACO14DEC] Cow Jog G

## 题目描述

Farmer John 的 $ N $ 头奶牛 $ ( 1 ≤ N ≤ 10^5 ) $ 正在一条长度无限的跑道上慢跑，每头奶牛都有一个不同的开始位置，以及不同的跑步速度。

为了方便奶牛们互相超越，整个跑道被分成了若干条赛道。在同一时刻，不可能有在同一条赛道上的两头奶牛占据相同的位置。

现在奶牛们要跑 $ T $ 分钟，在跑步过程中，他们不会改变自己所在的赛道和自己跑步的速度。FJ想要知道，为了奶牛间不会发生冲突，他需要至少准备多少条赛道。

## 样例 #1

### 输入

```
5 3
0 1
1 2
2 3
3 2
6 1```

### 输出

```
3```

# 题解

## 作者：hht2005 (赞：12)

这一题的本质其实是求牛结束位置的最长不上升子序列，其他一些篇题解都说了，但没说为什么，我在这可以给出两种有证明的思路。

**思路1**

对于两头牛，A牛和B牛，如果A牛超过了B牛，则说明A牛初始位置<=B牛初始位置且A牛结束位置>=B牛结束位置。在这种情况下，它们需要两条跑道。

同样的，如果有k头牛，第一头牛超过第二头牛，第二头牛超过第三头牛……，则说明它们的初始位置是不下降的，结束位置是不上升的。在这种情况下，它们需要k条跑道。

对于n头牛，问它们最少需要多少跑道，其实就是能满足初始位置不下降，结束位置不上升最多能选出多少头牛。由于输入以按照升序，所以我们只要考虑结束位置就行。不上升+最长=最长不上升子序列。

**思路2**
对于两头牛，A牛和B牛，如果A牛和B牛可以在同一条跑道上，则说明A牛初始位置<=B牛初始位置且A牛结束位置<=B牛结束位置，或A牛初始位置>=B牛初始位置且A牛结束位置>=B牛结束位置。

同样的，如果有k头牛，将它们按初始位置升序排列，如果它们可以在同一条跑道上，则说明它们结束位置也是升序的。

于是，题目就变成了求牛的结束位置最少能被分成多少个上升序列，就是Noip1999导弹拦截的第二问。当然，此题需要用nlogn的算法。但导弹拦截第二问的高效算法其实就是最长不上升子序列。

**code：**

两个思路代码都一样。

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
long long a[100010],c[100010],top,n,t;//会爆int
int main()
{
    long long p,v;
    scanf("%lld%lld",&n,&t);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld%lld",&p,&v);
        a[i]=p+v*t;//计算结束位置
    }
    for(int i=n;i>=1;i--)//倒过来变成最长不下降子序列，可以用upper_bound。
    {
        if(!top||a[i]>=c[top])
            c[++top]=a[i];
        else
        {
            int t=upper_bound(c+1,c+top+1,a[i])-c;
            c[t]=a[i];
        }
    }
    printf("%lld\n",top);
}
```

---

## 作者：Moon_Goddy (赞：7)

**思路：树状数组 + 离散化**

设 A 牛起点为 $l_A$，终点为 $r_A$。B 牛起点为 $l_B$，终点为 $r_B$。

容易发现，A 牛追上 B 牛当且仅当 $l_A \leq l_B \leq r_B \leq r_A$。

也就是 n 条以起点和终点为端点的线段做**线段覆盖**。

然后直接就想到了用树状数组维护。

需要注意的是，我们统计的是**最大**覆盖数而非总覆盖数。

![](https://cdn.luogu.com.cn/upload/image_hosting/gx31505d.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如这张图，此时的答案应该是 3 而不是 4 。

所以在统计答案和更新树状数组时都改成取最大就好啦。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl putchar('\n')
#define ll long long
#define en putchar(' ')
#define mp make_pair
#define yes printf("Yes!")
#define no printf("No!")
#define qwq printf("QWQ")
template<typename T>inline void read(T&x){
	x=0;char q;bool f=1;
	while(!isdigit(q=getchar()))if(q=='-')f=0;
	while(isdigit(q)){
		x=(x<<1)+(x<<3)+(q^48);
		q=getchar();
	}
	x=f?x:-x;
}
template<typename T>inline void print(T x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)print(x/10);
	putchar(x%10+'0');
}
const int N=100010;
int n,nn;
ll m;
struct node{
	ll l,r;
	bool operator <(const node&a)const {return l>a.l;} 
}e[N];
int ans;
struct TR{
	int c[N<<1];
	int lowbit(int x){return x&-x;}
	void add(int x,int d){
		while(x<=nn){
			c[x]=max(c[x],d);
			x+=lowbit(x);	
		}
	}	
	int query(int x){
		int res=0;
		while(x){
			res=max(res,c[x]);
			x-=lowbit(x);
		}
		return res;
	}
}tr;
ll lsh[N<<1];//离散化
int clsh,tot;
int main(){
	read(n);read(m);nn=n<<1;
	for(int i=1;i<=n;i++){
		read(e[i].l);
		ll v;read(v);
		e[i].r=v*m+e[i].l;
		lsh[++clsh]=e[i].l;
		lsh[++clsh]=e[i].r;
	}
	sort(lsh+1,lsh+clsh+1);
	tot=unique(lsh+1,lsh+1+clsh)-lsh-1;
	for(int i=1;i<=n;i++){
		e[i].l=lower_bound(lsh+1,lsh+tot+1,e[i].l)-lsh;
		e[i].r=lower_bound(lsh+1,lsh+tot+1,e[i].r)-lsh;
	}
	sort(e+1,e+1+n);//按照起点从大到小排序,方便树状数组统计
	for(int i=1;i<=n;i++){
		int d=tr.query(e[i].r)+1;//加上本身还需要的赛道
		ans=max(ans,d);
		tr.add(e[i].r,d);
	}
	print(ans);
	return 0;
}

```



---

## 作者：DengDuck (赞：4)

今天教练又出了一次这道题，我们考虑用另外一种思考方式得到贪心策略。

首先我们可以想一下，对于每个奶牛相当于从 $p_i$ 匀速运动至 $p_i+T\times v_i$。

我们思考两个奶牛怎么样会碰到，首先后面的奶牛记为 $j$，则 $j$ 超过 $i$ 肯定需要 $v_j>v_i$。

但是本题在时间上也有限制我们发现由于速度限制，如果 $j$ 超过了 $i$，后面 $i$ 不可能再追上 $j$，所以我们不妨算出终点进行比较。

由于起点递增，所以我们相当要保证满足 $i\leq j,p_j+T\times v_j\leq p_i+T\times v_i$ 的 $(i,j)$ 不在同一组。

因此每一组都应该满足 $i\leq j, p_i+T\times v_i\leq p_j+T\times v_j$。

发现其实就是把终点划分成最少的上升子序列，这就是一个拦截导弹问题了，可以用贪心加上二分维护。

时间复杂度为 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=3e5+5;
LL n,k,a[N],b[N],cnt,s[N];
int main()
{
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&a[i],&b[i]);
		b[i]=a[i]+b[i]*k;
	}
	for(int i=1;i<=n;i++)
	{
		LL l=1,r=cnt,ans=0;
		while(l<=r)
		{
			LL mid=(l+r)/2;
			if(s[mid]<b[i])ans=mid,r=mid-1;
			else l=mid+1;
		}
		if(ans==0)ans=++cnt;
		s[ans]=b[i];
	}
	printf("%lld",cnt);
}
```

---

## 作者：oscarlelewang (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/P4873)
## 算法：栈

先观察题目，可以发现每一个奶牛的初始位置为升序排列。

那么这样的话，先假设只有两个人，
如果第二个人最后位置比第一个人最后的位置大，那么他们就不会相交，
那么就是只用一条跑道。

如果比那个小，那么就必须要两条跑道。
再进来第三个，和刚刚一样，只是比较的对象从一个人变为这一条跑道上最小的终点。

在此同时，我们把这个跑道终点做一个上升的序列，
每次加人，就判断是不是终点比之前的远，
如果是的话就加一条跑道，不是的话就找到终点比他小且离他最近的点，维护单调性。

我们可以通过 upper_bound 来实现，但它找的是第一个    $\geq$ 它的那个数，而我们是要 $\leq$ ，所以就加一个负号，这样就可以实现了。

具体看代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,t,p,s,c;
vector<long long> a;//比数组更好的数组，用数组模拟栈
int main()
{
 cin>>n>>t;
 for(int i=1;i<=n;i++)
 {
  cin>>p>>s;
  c=-(p+s*t);//加负号以做到相反的需求
  if(a.empty()||c>=a.back())
  {
   a.push_back(c);//没一条跑道加的了它，就新加一条
  }
  else *upper_bound(a.begin(),a.end(),c)=c;
  //第一个 >= 它的那个数
 }
 cout<<a.size();//跑道数
}
 

```


---

## 作者：oimaster (赞：1)

## 题目

本题在 USACO 上的网址为 <http://usaco.org/index.php?page=viewproblem2&cpid=496>。

在洛谷上也可以查看，网址为 <https://www.luogu.com.cn/problem/P4873>。

## 思路

奶牛们在跑步的时候如果占据相同的位置，就需要把其中一头奶牛放到别的跑道上。所以我们要知道，奶牛跑到一起的原因。

如果奶牛 A 的起始位置为 $xa$、停止位置为 $ya$，奶牛 B 的起始位置为 $xb$、停止位置为 $yb$，并且 $xa<xb$。我们就可以说，当 $ya<yb$，两头奶牛就不会重合在一起，否则就一定会在某个时刻位置重合。

有了这个规律，我们就把题目变成“奶牛初始位置不下降，结束位置不上升，能找到多少头奶牛”了。

我们看见，题目中说明给我们的奶牛起始位置一定是有序且上升的。那么，“奶牛初始位置不下降”就帮我们满足了，不用考虑这一点。

“结束位置不上升”，感觉有点奇怪。这时候我们可以倒序扫描，那么“不上升”就变成了“不下降”。默认大家都会最长不下降子序列问题，所以这个问题也被解决了。

还有两个要注意的地方。第一个是 $1≤n≤100000$，所以最长不下降子序列问题要用二分方法做；第二个是一句名言：

> 十年 OI 一场空，不开 long long 见祖宗！

好了，知道了这些，就可以愉快地写代码啦！

## 代码

蒟蒻码风丑陋，勿学！
因为是在洛谷上提交，所以文件操作被我删除掉了。

```
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
int n,t;
int a[100010];
int c[100010];
int f;
signed main(){
    cin>>n>>t;
    for(int i=1;i<=n;++i){
        int x,y;
        cin>>x>>y;
        a[i]=x+t*y;
    }
    reverse(a+1,a+n+1);
    for(int i=1;i<=n;++i){
        if(c[f]<=a[i]){
            ++f;
            c[f]=a[i];
        }
        else
            *upper_bound(c+1,c+f+1,a[i])=a[i];
    }
    cout<<f<<endl;
    return 0;
}
```

---

## 作者：Naffygo (赞：1)

### 题目大意
有 $n$ 个人在跑步，他们会跑 $m$ 分钟步。每个人都有初始位置和初始速度，在跑步过程中，每个人不会更改跑道及他自己的速度。问在不会有人追上其他人的情况下，最少要几条跑道。（题目保证不会有人在同一位置，且默认按照初始位置升序读入）

### 思路
可以先求出每个人的终点位置，如果A与B能在一条跑道上（A起始位置小于B），则A的终点位置一定比B小。所以该题就是要求结束位置的最少上升子序列分割数，即最长不上升子序列数。

代码如下:（记得开 $long$ $long$ ）

```cpp
#include<bits/stdc++.h>
#define fr(i,a,b) for(register int i = a;i <= b;++i)
#define int long long
#define N 100010
using namespace std;

struct cow{
	int s,t;
	bool operator < (const cow &x)const{
		return s < x.s;
	}
}a[N];
int f[N];

inline int read(){
	int x = 0,f = 1;char c = getchar();
	while(!isdigit(c)){if(c == '-')f = -1;c = getchar();}
	while(isdigit(c)){x = x * 10 + c - '0';c = getchar();}
	return f * x;
}

signed main(){
	int n = read(),m = read();
	fr(i,1,n){
		int x = read(),y = read();
		a[i] = (cow){x,x + y * m};
	}
	memset(f,0x3f,sizeof(f));
	int now = 0;
	fr(i,1,n){
		if(a[i].t <= f[now])f[++now] = a[i].t;
		else{
			int l = 0,r = now;
			while(l < r){
				int mid = (l + r) >> 1;
				if(f[mid] >= a[i].t)l = mid + 1;
				else r = mid;
			}
			f[l] = a[i].t;
		}
	}
	printf("%lld",now);
	return 0;
}
```

---

## 作者：Celebrate (赞：1)

因为题目给出了起点速度和时间，我们就可以求出每一头奶牛所走的区间

假如有两个区间A和B 交叉在了一起

具体来说就是 A.st< B.st 而且 B.ed < A.ed 

因为每当速度快的奶牛追上速度慢的奶牛后会超过他，所以最终点就一定大于慢的奶牛到达的最终点

所以交叉在一起的区间肯定要分开路走

由此得知，我们要求的是最多层次的完全覆盖区间

 

就比如说这个图

![无](https://img-blog.csdnimg.cn/20181214134152113.PNG?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3pzeXpDbGI=,size_16,color_FFFFFF,t_70)

因为这个图最多的完全覆盖的有四层，所以需要备四条跑道，情景描述大概是这样的

奶牛1会超过234，多准备一条道

奶牛2会超过34，多准备一条道

奶牛3会超过4，多准备一条道

奶牛4要一条跑道

一共就是四条

我们先将st排序，将ed变成点权，那不就变成了求最长的不上升子序列

维护这个，首先要离散化不然肯定直接爆炸，离散以后最多2n，如果用O(N^2)的做法肯定会超时

所以就要用O（nlogn）的做法，这是废话

一开始不知道怎么做，后来看了一下别人的博客

先设当前要搜索的节点为i（离散完后又n个不同的值）

那么求的就是比i的权值大并且长度最大的那个点，因为这是数组数组，所以要记得维护哦

代码见 [MyBlog](https://blog.csdn.net/zsyzClb/article/details/85002168)

---

## 作者：JZYshuraK (赞：1)

这道题还是比较简单的。

做过银组的那个cow_jog的话开始的时候容易想成并查集，就比较GG。

首先，我们发现如果两头牛从开始到结束，相对位置没有发生改变，那么这两头牛就可以待在一个跑道上。

进而，如果两头牛起始位置和终止位置的相对位置没有改变，那么这两头牛就可以待在一个跑道上。

故我们对每个牛维护一个dic表示起始位置，dstn表示终止位置。

将所有牛按照dic排序，变成了一个以dstn为权值的序列。

我们就是求最小的上升子序列分割，而这等于最长不上升子序列，我们可以用**离散化**+**树状数组**实现（二分也是可以的）。
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 100010 
using namespace std;
typedef long long ll;
struct Node
{
	ll dic; // 表示其实位置
	ll spd; // 奶牛的速度
	ll dstn1; // 离散化之前的终止位置
	ll dstn; // 离散化之后的终止位置
	int f; // 以当前奶牛为结尾的最长不下降子序列长度
}a[N]; int tree[N<<1]; int n;
inline bool cmp_dic(const Node &x,const Node &y) {return x.dic<y.dic;}
inline bool cmp_dstn1(const Node &x,const Node &y) {return x.dstn1<y.dstn1;}
inline char nc() {static char *p1,*p2,buf[100000]; return (p1==p2)&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;}
ll rd() {ll x=0; char c=nc(); while(!isdigit(c)) c=nc(); while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=nc(); return x;}
inline int lowbit(int x) {return x&(-x);}
void update(int x,int val)
{
	for(int i=x;i>=1;i-=lowbit(i)) tree[i]=max(tree[i],val);
}
int query(int x)
{
	int ans=0; for(int i=x;i<=n+1;i+=lowbit(i)) ans=max(ans,tree[i]);
	return ans;
}
int main()
{
	n=rd(); ll t=rd();
	for(int i=1;i<=n;i++)
	{
		a[i].dic=rd(); a[i].spd=rd();
		a[i].dstn1=a[i].dic+t*a[i].spd;
	}
	sort(a+1,a+n+1,cmp_dstn1); a[0].dstn1=a[1].dstn1-1;
	int tot=0;
	for(int i=1;i<=n;i++) // 离散化
	{
		if(a[i].dstn1!=a[i-1].dstn1) tot++;
		a[i].dstn=tot;
	}
	sort(a+1,a+n+1,cmp_dic); int ans=0;
	for(int i=1;i<=n;i++) // 求最长不下降子序列
	{
		a[i].f=query(a[i].dstn)+1; update(a[i].dstn,a[i].f);
		ans=max(ans,a[i].f);
	}
	printf("%d\n",ans);
	return 0;
}
```
推销一下自己blog : [JZYshuraK](http://www.cnblogs.com/ShuraK/)

---

## 作者：Yang818 (赞：1)

## 前置知识
### Dilworth 定理

这个定理大概意思就是：

>一个序列中一种链的个数 = 这个序列中最长反链的长度

导弹拦截是一道经典的 Dilworth 定理的题目拿导弹拦截的第二问样例做个示范
>389 207 155 300 299 170 158 65

第二问要求有多少个最长不上升子序列。根据 dilworth 对偶定理，最长不上升子序列的个数=最长上升子序列的长度。

这个序列中最长上升子序列的长度是 2，所以第二问的答案是 2.

## 题目大意

有 $n$ 头奶牛，现在知道他们的起始位置，跑的速度，现在开始跑步，跑的时间为 $t$。~~其实就是告诉你结束的位置了~~现在已知起点是升序排列的。求要安排几根跑道才能使奶牛不会发生“超车现象”。

## 分析
首先在没思路的情况下，先把样例拿过来看看能怎么动动。

>0 1

>1 2

>2 3

>3 2

>6 1

现在 $t = 3$

| 序号 | 起点 | 速度 | 终点   | 安排的跑道号 |
| -----------: | -----------:   | -----------: | -----------: | -----------: |
| 1 | 0 | 1 | 3 | 1 |
| 2 | 1 | 2 | 7 | 1 |
| 3 | 2 | 3 | 11 | 1 |
| 4 | 3 | 2 | 9 | 2 |
| 5 | 6 | 1 | 9 | 2 |

通过对比，我们不难得出结论，这不就是求以终点为序列的最长上升子序列的个数吗？

其实是的，因为起点在你前面的结束之后如果还在你前面，那么你俩可以放在一个跑道里，如果结束后在你后面，那么你们在过程中肯定发生了“超车现象”。而起点正好是以升序排列的。所以就只用求求以终点为序列的最长上升子序列的个数，就是答案了。

## 代码

好了，根据 Dilworth 定理,现在需要求的就是终点这个序列中最长不上升子序列的长度。
直接 $O(n\log n)$ 时间复杂度搞定。
代码肯定30行以内。

~~代码还需要吗？~~

```cpp
#include<bits/stdc++.h>
using namespace std;

long long g_n,g_t;
long long g_a[100010];
long long g_b[100010];
long long k,a,b,ans;

int main(){
	cin>>g_n>>g_t;
	memset(g_a,0x3f,sizeof(g_a));
	g_a[0]=0;
	for(int i=1;i<=g_n;i++){
		cin>>a>>b;
		k=a+g_t*b;
		g_b[i]=k;
	}
	for(int i=g_n;i>=1;i--){		
		if(!ans||g_b[i]>=g_a[ans])
			g_a[++ans]=g_b[i];
		else{
			int p=upper_bound(g_a+1,g_a+g_n+1,g_b[i])-g_a;
			g_a[p]=g_b[i];
		}
	}
	cout<<ans;
	return 0;
}
```
望通过，谢谢



---

## 作者：普通的名字 (赞：0)

考虑第 $i,j(j<i)$ 头奶牛是否能在一条跑道上。不考虑两者中间的奶牛，假设他们已经被移到其他跑道上了。

用式子表达即为 $(v_j-v_i)t<p_i-p_j$。$p_i-p_j$ 是二者之间的距离。$v_j-v_i$ 为二者的速度差，若为负数，$j$ 就追不上 $i$，式子成立；若是正数，速度差与时间的乘积就是在时刻 $t$ 时 $j$ 与 $i$ 减少的距离，当然要小于原本的距离。小学数学不用多说。

上面的式子移项可得：$v_jt+p_j<v_it+p_i$。

发现两边的形式相似。令 $a_i=v_it+p_i$，就为 $a_j<a_i$。

就是说，$i$ 和 $j$ 要在一条跑道上，要满足 $a_j<a_i$。

我们发现这很像最长下降子序列。但是题目问的是求最少的跑道数量。

其实也一样。联想到 拦截导弹 这道题，最长下降子序列的最少数量等于最长不下降子序列的长度。

所以求一遍最长不下降子序列长度就可以了。由于 $N\le10^5$，要进行优化。代码使用了线段树优化。时间复杂度 $O(N\log N)$

代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF=9e18;
const int N=2e5+1;
int n;
ll t,a[N],b[N],f[N],ans,c[N],czn[N],tr[N<<2];
void update(int rt,int l,int r,int x,ll d)
{
    if(l==r){
        tr[rt]=max(tr[rt],d);
        return;
    }
    int mid=l+r>>1;
    if(x<=mid) update(rt<<1,l,mid,x,d);
    else update(rt<<1|1,mid+1,r,x,d);
    tr[rt]=max(tr[rt<<1],tr[rt<<1|1]);
}
ll query(int rt,int l,int r,int x,int y)
{
    if(r<x||y<l) return -INF;
    if(x<=l&&r<=y) return tr[rt];
    int mid=l+r>>1;
    return max(query(rt<<1,l,mid,x,y),query(rt<<1|1,mid+1,r,x,y));
}
int main()
{
    scanf("%d%lld",&n,&t);
    for(int i=1;i<=n;i++){
        scanf("%lld%lld",&a[i],&b[i]);
        a[i]+=b[i]*t;
        b[i]=a[i];
    }
    sort(b+1,b+1+n);
    for(int i=1;i<=n;i++){
        int pos=lower_bound(b+1,b+1+n,a[i])-b;
        a[i]=pos;
    }
    for(int i=1;i<=n;i++){
        ll x=max(1ll,query(1,1,n,a[i],n)+1);
        ans=max(ans,x);
        update(1,1,n,a[i],x);
    }
    cout<<ans;
}

```

---

## 作者：DengDuck (赞：0)

怎样判断一个奶牛是否会追上另外一头奶牛?

设奶牛甲起点是 $x_1$ ，速度是 $y_1$ 米每分钟，奶牛乙起点是 $x_2$ ，速度是 $y_2$ 米每分钟,我们想一想乙怎样才能追上甲?
 
前提是 $x_1>x_2 $，这是显然的，要是甲在乙后面，那显然是甲在追乙。

现在再想想，上述条件满足的情况下，乙什么时候能追上甲?我们易得：
$$
\frac{x_1-x_2}{y_2-y_1}
$$

题目规定了一个时间上限，所以我们得到一个不等式,以判断乙是否能追上，追上的条件是:
$$

\frac{x_1-x_2}{y_2-y_1}\leq t 

$$

变形得：
$$
x_1+t\times y_1\leq x_2+t\times y_2
$$

这是本题一个重要的性质。

现在我们给奶牛从大到小排个序，这样前提就满足了。

对于每个奶牛，我们设想前面的奶牛都没有冲突了，当前奶牛我们可以找一个合适的跑道加入，否则就再修一个。

对于每个跑道，记录最小的 $x+t\times y$ ，和当前奶牛比对，不难发现在这个过程中跑道的最小值始终具有单调性，所以可以二分查找，就这样不断插入奶牛即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline long long read() {
    char c = getchar();
    long long sum = 0,f=1;
    while (c != '-' && (c < '0' || c > '9')) c = getchar();
    if (c == '-') {
        f = -1;
        c = getchar();
    }
    do {
        sum = (sum << 3) + (sum << 1) + c - '0';
        c = getchar();
    } while (c >= '0' && c <= '9');
    return sum * f;
}
long long n,t,x,y,a[100005],b[100005],cnt,l,r,ans,mn[100005];
int main()
{
    n=read(),t=read();
    for(int i=1;i<=n;i++)
    {
        a[i]=read(),b[i]=read();
    }
    for(int i=n;i>=1;i--)
    {
        x=a[i],y=b[i];
        l=1,r=cnt,ans=0;
        while(l<=r)
        {
            long long mid=(l+r)/2;
            if(x+t*y<mn[mid])
            {
                r=mid-1;
                ans=mid;
            }
            else
            {
                l=mid+1;
            }
        }
        if(ans==0)cnt++,ans=cnt;
        mn[ans]=x+t*y;
    }
    printf("%lld",cnt);
}
```

---

## 作者：zzzty___ (赞：0)

两头牛 $i,j(i<j)$ 能相遇当且仅当 $\exists t\in[0,T]$ 使得 $p_i+v_it=p_j+v_jt$

因为任意 $p$ 两两不同，当 $v_i=v_j$ 时，显然两头牛不可能相遇.

当 $v_i\not =v_j$ 时，整理得 $t=\frac{p_j-p_i}{v_i-v_j}$

此时两头牛不能相遇当且仅当 $t<0$ 或者 $t>T$

对于两头牛不能相遇：

当 $v_i<v_j$ 时， $t<0$ ，不能相遇

当 $v_i>v_j$ 时，若不能相遇，则只能满足 $t>T$

即 $p_i+v_iT<p_j+v_jT$

又因为 $p$ 单调递增，所以 $p_i<p_j$

于是只需满足 $p_i+v_iT<p_j+v_jT$ 这一个条件时两头牛就不会相遇（ $v_i<v_j$ 时显然有上式成立）

记 $a_i=p_i+v_iT$

于是题目就变为求 $\{a_n\}$ 划分成最少的单调上升子序列的组数

根据**Dilworth**定理，这个数就等于 $\{a_n\}$ 的最长不上升子序列的长度.

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int n,T,len=0;
long long a[maxn],d[maxn];
int main(){
	cin>>n>>T;
	for(int i=1;i<=n;i++){
		long long p,v;
		cin>>p>>v;
		a[i]=p+v*T;
	}
	for(int i=1;i<=n;i++){
		if(!len||a[i]<=d[len]) d[++len]=a[i];
		else *upper_bound(d+1,d+len+1,a[i],greater<long long>())=a[i];
	}
	cout<<len<<endl;
	return 0;
}
```

---

## 作者：Zekrom (赞：0)

题目大意：  
每头牛有一个起始位置，速度（可以求出末位置），求出最小赛道数使任意两头牛在某一时刻不重合   
方法：   
1.求出初始位置，末位置并离散化   
2.将l（起始位置）升序排序，显然，若$r[i]$（当前牛）$<=$ $r[j]$（之前牛），则 $j$会追上 $i$，所以问题就转化为了对 $r[i]$求最长不下降子序列的个数$\Leftrightarrow$最长不上升个数，树状数组求解即可  
3.树状数组求最长不上升只要反个权值在哈个希（$+2N$）即可  
注意：  
### 很多人都只拿了63分    
##  ~~为什么呢？卖个关子~~   
# ~~检查longlong(从头到脚)~~ 
上代码   
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define N 100010
#include<algorithm>
using namespace std;
int n,cnt,tot;
long long b[4*N],ans,sum[4*N],T;
struct Node{
	long long x,v,y;
}a[N];
inline long long read(){
	long long x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();
	}while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();
	}return  x*f;
}
bool cmp1(Node s1,Node s2){return s1.x<s2.x;}
inline long long get(long long x){return lower_bound(b+1,b+1+tot,x)-b;}
inline void add(int x,long long y){for(;x<2*N;x+=x&-x)sum[x]=max(sum[x],y);}
inline long long ask(int x){long long ans=0;for(;x;x-=x&-x)ans=max(ans,sum[x]);return ans;}
inline long long num(long long x){return -x+2*N;}
int main(){
	n=read();T=read();
	for(int i=1;i<=n;i++){
		a[i].x=read();a[i].v=read();
		a[i].y=a[i].x+a[i].v*T;
		b[++cnt]=a[i].x;b[++cnt]=a[i].y;
	} 
	sort(b+1,b+1+cnt);tot=unique(b+1,b+1+cnt)-b-1;for(int i=1;i<=n;i++)a[i].x=get(a[i].x),a[i].y=get(a[i].y);
	sort(a+1,a+1+n,cmp1);
	memset(sum,0xcf,sizeof(sum)); 
	for(int i=1;i<=n;i++){
		long long x=ask(num(a[i].y))+1;
		ans=max(ans,x);
		add(num(a[i].y),x);
	} 
	printf("%lld\n",ans);
}
```


---

## 作者：xy_xw_for_2024 (赞：0)

这道题当时在考场上完全没有思路，然后看了一下[某大佬](https://blog.csdn.net/weixin_43904950)的博客以后才知道其实就是一个最长不上升子序列

我们把每头奶牛的终点算出来，然后与其起点比较一下，如果A的起点在B的起点前面，而A的终点在B的终点的后面，那就说明A一定在途中超过了B，这样就一定要到另外开一个跑道，而题目给的起点是递增的，所以就直接求一个最长不上升子序列就行了

还有一点，因为题目给的数据很大，需要[nlogn的最长不上升子序列](https://blog.csdn.net/qq_43890190/article/details/84862124)

 

那里面讲的不是很清楚，这里再推一遍

对于任意一个数列，我们用另一个数列dp[]来存这个数列的最长上不上升子序列的长度，从1~n依次扫过去，下面有两种情况：

1、a[i]小于dp里的最后一个（设为dp[len]），那么dp[++len]=a[i]

2、a[i]大于dp[len]，二分求出dp中最前面的一个小于a[i]的位置，然后把这个数替换成a[i]

那么有人可能会问，这样算出来的就是正解吗？把dp里的数换了这个序列不就不存在了吗？

我们那小数据试一下

例如对（2,5,1,6,4,8,3,1）

len=1,dp[]={2}
5>2,len=1,dp[]={5}
1<5,len=2,dp[]={5,1}
6>1,len=2,dp[]={6,1}
4>1,len=2,dp[]={6,4}
8>4,len=2,dp[]={8,4}
3<4,len=3,dp[]={8,4,3}
1<3,len=4,dp[]={8,4,3,1}
我们发现，从第4步开始，dp里的数列在a里已经不存在了，但是每一步的len却是对的，而答案而是4，大家可以自己算一下

而这样做的原因也很好解释

因为我们是求一个最长不上升子序列

我么就要把dp里的数尽可能的放大

这样才能给后面的数留更多的空间

然后就是代码了

代码如下：：
```
#include<cstdio>
#include<iostream>
using namespace std;
inline void read(long long &x) {
    x=0;
    char s=getchar();
    while(s<'0'||s>'9')
        s=getchar();
    while(s>='0'&&s<='9') {
        x=x*10+s-48;
        s=getchar();
    }
}
inline void pr(long long x) {
    if(x>9)
        pr(x/10);
    putchar(x%10+48);
}//快读快输不解释
long long a[100005],dp[100005],i,n,j,k,l=1,t;
inline int ef(long long x) {//二分求要替换的点
    int le=1,r=l+1,mid;
    while(le+1<r) {//这里要注意，一定是l+1小于r，不然会卡死
        mid=(le+r)/2;
        if(dp[mid]>=x)
            le=mid;
        else
            r=mid;
    }
    if(dp[le]<x)
        return le;
    else
        return r;
}
int main() {
    read(n),read(t);
    long long o;
    for(i=1;i<=n;i++)
        read(a[i]),read(o),a[i]=o*t+a[i];
    dp[1]=a[1];
    for(i=2;i<=n;i++)
        if(dp[l]>=a[i])
            dp[++l]=a[i];
        else
            k=ef(a[i]),dp[k]=a[i],l=max(l,k);//没什么好解释的吧，还是很简单
    pr(l);
}
```
[我的博客链接](https://blog.csdn.net/qq_43890190/article/details/85693796)

---

