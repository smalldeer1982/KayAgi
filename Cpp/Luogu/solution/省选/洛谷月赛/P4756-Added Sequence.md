# Added Sequence

## 题目描述

小$L$发明了一种新的数据结构，并将其命名为$L$数组。$L$数组的作用是可以在$O(1)$时间内将整个数组加上或减去一个数。现在给你一个长度为$N$的数组$a$，他想用$L$数组来挑战你的计算能力。

定义$f(i,j)=|\sum_{p=i}^{j} a_p|$其中$|x|$表示$x$的绝对值。

定义一个数组的美丽度为$\max_{1 \le i \le j \le N} f(i,j)$，每当他将整个数组加上$x$ ，请你回答此时的美丽度。

注意，你的算法必须为在线的。

## 说明/提示

四次加上的数字分别为-7，-4，-2，1。

$1 \le N,M \le 200000$

$|a_i| \le 200000$

$0 \le x_i \le 800000$

## 样例 #1

### 输入

```
4 4
4 5 6 7
1
15
0
12```

### 输出

```
6
6
14
26
```

# 题解

## 作者：FlierKing (赞：18)

考虑最大的$f(i,j)=| \sum_{p=i}^j a_p |$本质是什么

换为前缀和的形式 $f(i,j)=|pre_j - pre_i|$

将绝对值拆掉 $$f(i,j)=\left\{\begin{matrix} pre_j-pre_i & if\ pre_{j}>pre_{i}\\ pre_i-pre_j & if\ pre_{j} \le pre_{i} \end{matrix}\right.$$

所以$\max_{1 \le i \le j \le n} f(i,j)$

$=\max pre_i - \min pre_j$

如果给整个数组加上 $x$，那么 $pre'_i=pre_i+ix$

那么当我们确定了整个数组加上的数字$x$，我们就能确定每个位置的前缀和，考虑如何求出最大的前缀和和最小的前缀和。

这个是个一次函数的形式，我们可以将前面的 $n+1$ 个一次函数加入坐标系，维护一个下凸包表示整个数组加上$x$时最大的前缀和，维护一个上凸包表示最小的前缀和。

这个是样例的图，其中紫色的为5条一次函数，黄色的为下凸包，红色的为下凸包。那么当我们要求整个数组加上$h$的答案时，$x$坐标为$h$的下凸包的$y$坐标减去$x$坐标为$h$的上凸包的$y$坐标得到的差即为询问的答案。

![](https://cdn.luogu.com.cn/upload/pic/23616.png)

那么我们维护凸包，记下凸包上每条线段两端的位置后，我们可以二分横坐标$h$是在哪个线段上，求出相应的$y$值。

最后上凸包的值-下凸包的值即为答案。

时间复杂度为$O(n\ log\ n)$

```cpp
#include <bits/stdc++.h>
#define MN 200005
#define ll long long
using namespace std; 
    int n,m,l,r,mid,a,b,x;
    ll s[MN],mx[MN],mxn,mn[MN],mnn,pre;
    double mxp[MN],mnp[MN];
inline int read()
{
    int x=0,f=1;char c;
    while((c=getchar())<'0'||c>'9')if(c=='-')f=-1;
    for(;c>='0'&&c<='9';c=getchar())x=x*10+c-'0';
    return x*f;
}
inline double cal(int a,int b){return double(s[b]-s[a])/(a-b);}
int main()
{
    n=read();m=read();
    for(int i=1;i<=n;i++)
    {
        s[i]=s[i-1]+read();
        while(mxn&&cal(i,mx[mxn])<=cal(i,mx[mxn-1]))--mxn;mx[++mxn]=i;
        while(mnn&&cal(i,mn[mnn])>=cal(i,mn[mnn-1]))--mnn;mn[++mnn]=i;
    }
    for(int i=1;i<=mxn;i++)mxp[i]=cal(mx[i],mx[i-1]);
    for(int i=1;i<=mnn;i++)mnp[i]=cal(mn[i],mn[i-1]);
    while(m--)
    {
        x=(read()+pre)%(4*n+1)-2*n;
        if(x<=mxp[1])a=0;
        else for(l=1,r=mxn;l<=r;)
        {
            mid=(l+r)>>1;         
            if(x>=mxp[mid])a=mx[mid],l=mid+1;
            else r=mid-1;
        }
        if(x>=mnp[1])b=0;
        else for(l=1,r=mnn;l<=r;)
        {
            mid=(l+r)>>1;
            if(x<=mnp[mid])b=mn[mid],l=mid+1;
            else r=mid-1;
        }
        printf("%lld\n",pre=(ll)(a-b)*x+s[a]-s[b]);
    }
    return 0;
}
```

---

## 作者：Trinity (赞：6)

# P4756 Added Sequence 2018洛谷7月月赛 T5
## 题目描述
定义
$~~~~~~~~~~f(i,j)=∣\sum_{p=i} ^j a_p∣$   
其中 $|x|$ 表示 $x$ 的绝对值。  
定义一个数组的美丽度为 $ max_{1\leq i\leq j\leq N}f(i,j)$。  
每当他将整个数组加上 $x$ ，请你回答此时的美丽度。  
~~注意，你的算法必须为在线的。~~( 编者手动删除 ）
## 分析
$1$ . 看到两个式子不要慌，先化简再说。  
$2$ . 这一题需要计算几何中的**凸包**知识，如果没有学过的可以看一看我的另一篇[二维凸包](https://www.luogu.org/blog/cyx-TombRaider/p2742-mu-ban-er-wei-tu-bao-by-hydranazis)，当然也可以先打40分的暴力。
## 解答
数学部分：  
$~~~~~~~~~~~~~~~~~~~~~~~~f(i,j)=$ $a_i$到$a_j$的和的绝对值 $=|pre_j-pre_i |$  
显然，当且仅当 $pre_i$和 $pre_j$ 中一个最小，一个最大时，$f(i,j)$才可以取到最值：
$~~~~~~~~~~~~~~~~~~~~~~~~max(f(i,j))=max(pre_i)-min(pre_j)$  
那么，整个数组加上 $x$ 使得前缀和数组加上区间和，发现是个一次函数的形式：  
$~~~~~~~~~~~~~~~~~~~~~~~~pre_i^\prime=pre_i+i\times x$   
然后$max(f(i,j))$就是图形的最大减去最小 
![](https://cdn.luogu.com.cn/upload/pic/24933.png)
那么你就会问，你这个题解不就是和上面的一样吗！  
继续看,我们求相邻两条直线的交点的坐标：  
$~~~~~~~~~~~~~~~~~~~~~~~~pre_i+i\times x=pre_{(i+1)}+(i+1)\times x$  
化简得：  
$~~~~~~~~~~~~~~~~~~~~~~~~x=pre_i-pre_{(i+1)}=-a_{(i+1)}$  
这个式子可以减小我们的计算量。  
通过二维凸包的分别对上和下的维护，我们再来二分 $x$ 在凸包上的位置即可算出。  
其实题目中的强制在线是假的，数据范围$-2n $~$ 2n$, 完全可以实现（ 有巨佬[newbie314159](https://www.luogu.org/space/show?uid=54979)已经成功实现，去围观一下 ）
OK，如果不会凸包就看下代码：
```cpp
// luogu-judger-enable-o2
#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <vector>
#include <stack>
#define N 300001
#define inf 2147483647
#define LL long long
#define mod 99999997
#define ls (p*2)
#define rs (p*2+1)
using namespace std;
inline LL read()
{
  LL f=1,x=0;char ch=getchar();
  while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
  while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
  return f*x;
}
LL n,m,x[N],pre[N],a[N],max_st[N],max_top=1,min_st[N],min_top=1,maxi,mini,maxx,minn,l,r,mid;//st->储存凸包直线的栈，top->栈顶，i->二分时在凸包的哪一部分，x->最大和最小值。
inline bool judge_slope(int a,int b,int c)
{
  return (pre[a]-pre[b])*(b-c)<=(pre[b]-pre[c])*(a-b);//计算斜率，我喜欢用变形后用乘法，不掉精。
}
int main()
{
  n=read(),m=read();
  for(int i=1;i<=n;i++)pre[i]=pre[i-1]+(a[i]=read());
  for(int i=1;i<=n;i++)
  {
    while(max_top>1&&judge_slope(max_st[max_top-1],max_st[max_top],i))max_top--;
    max_st[++max_top]=i;
    while(min_top>1&&!judge_slope(min_st[min_top-1],min_st[min_top],i))min_top--;
    min_st[++min_top]=i;//标准的凸包维护。
  }
  //for(int i=1;i<=max_top;i++)cout<<max_st[i]<<' ';cout<<endl;
  //for(int i=1;i<=min_top;i++)cout<<min_st[i]<<' ';cout<<endl;
  for(int i=1;i<=m;i++)
  {
    x[i]=read();
    x[i]=(x[i]+x[i-1])%(4*n+1)-2*n;//别忘了加上上一次的。
    //cout<<x[i]<<endl;
    l=2,r=max_top,maxi=0;
    while(l<=r)
    {
      mid=(l+r)/2;
      //cout<<"mid "<<mid<<endl;
      if((double)(pre[max_st[mid-1]]-pre[max_st[mid]])/(double)(max_st[mid-1]-max_st[mid])>=-x[i])//为什么是-x，因为我所有的直线全部是反着建的。
        maxi=mid,l=mid+1;
      else r=mid-1;
    }
    //cout<<endl;
    maxx=pre[max_st[maxi]]+x[i]*max_st[maxi];
    //cout<<"max:"<<maxx<<endl;
    l=2,r=min_top,mini=0;
    while(l<=r)
    {
      mid=(l+r)/2;
      //cout<<"mid "<<mid<<endl;
      if((double)(pre[min_st[mid-1]]-pre[min_st[mid]])/(double)(min_st[mid-1]-min_st[mid])<=-x[i])
        mini=mid,l=mid+1;
      else r=mid-1;
    }
    minn=pre[min_st[mini]]+x[i]*min_st[mini];//带入。
    //cout<<"min:"<<minn<<endl;
    //x[i]=fabs(maxx-minn);
    //cout<<"x: "<<x[i]<<endl;
    printf("%lld\n",x[i]=fabs(maxx-minn));//一定要取绝对值。
  }
  return 0;
}

```
## 总结
完全搞懂这个毒瘤题的凸包花了我一个星期的时间，才把这道题打完。但是一看大家交的代码，呵呵~~

---

## 作者：asd_a (赞：2)

这道题可以用李超线段树做，不会的同学请出门左转，~~重学小学二年级~~  
可以发现这道题就是求最大前缀和和最小前缀和然后做差即可  
一个点的前缀和与全局加的数是一个一次函数，
求其最大值和最小值就是李超树的模板
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
struct line{
	long long k,b;
	line(long long x=0,long long y=0){k=x;b=y;}
	inline long long operator()(long long x){return k*x+b;}
}p[N];
struct lct{
	#define ls (now<<1)
	#define rs (now<<1|1)
	#define mid (lef+rig>>1)
	#define lc ls,lef,mid
	#define rc rs,mid+1,rig
	#define nc now,lef,rig
	int tr[N<<2];
	void ins(int x,int now=1,int lef=-1e6,int rig=1e6){
		if(!tr[now]){tr[now]=x;return ;}
		if(p[x](mid)>p[tr[now]](mid))swap(x,tr[now]);
		if(p[x](lef)>p[tr[now]](lef))ins(x,lc);
		if(p[x](rig)>p[tr[now]](rig))ins(x,rc);
	}long long ask(int x,int now=1,int lef=-1e6,int rig=1e6){
		if(!tr[now])return -1e18;
		long long ans=p[tr[now]](x);
		if(x<=mid)ans=max(ask(x,lc),ans);
		else ans=max(ask(x,rc),ans);
		return ans;
	}
	#undef ls
	#undef rs
	#undef mid
	#undef lc
	#undef rc
	#undef nc
}A,B;
int n,m;
long long sum,lastans;
int main(){
	scanf("%d%d",&n,&m);n++;A.ins(1);B.ins(n+1);
	for(int x,i=2;i<=n;i++){
		scanf("%d",&x);sum+=x;
		p[i]=line(i-1,sum);p[i+n]=line(-i+1,-sum);
		A.ins(i);B.ins(i+n);
	}for(int x;m--;){
		scanf("%d",&x);
		x=(x+lastans)%(4*n-3)-2*n+2;
		printf("%lld\n",lastans=A.ask(x)+B.ask(x));
	}return 0;
}
```

---

## 作者：mrsrz (赞：1)

这题就是一个全局加全局最大子段和。绝对值可以通过正负两种情况合并把它去掉。

题目中的强制在线，实际上值域范围只有$-2n\sim 2n$，可以全部询问出来。于是可以离线。

如果做过[\[Ynoi2015\]世上最幸福的女孩](https://www.luogu.org/problemnew/show/P5073)或者[\[Ynoi2018\]末日时在做什么?有没有空?可以来拯救吗?](https://www.luogu.org/problemnew/show/P4680)的话，应该对这种东西比较敏感。

我们令$(i,mx)$表示长度为$i$时，其最大子段和为$x$，则其全局加上一个数后，能取到最大值的点一定在这样的点构成的凸包上。

求这个凸包就可以用到经典的算法，分治+闵可夫斯基和合并凸包了。

即令$L$表示左半边的最大子段和凸包，$R$表示右半边的最大子段和凸包，$s$表示左半边的后缀和凸包，$p$表示右半边的前缀和凸包。

则跨越中点的最大子段和信息可以以通过$s$和$p$中的点两两相加得到，而这个点集的凸包就通过闵可夫斯基和得到。然后再和$L,R$分别合并即为整个区间的凸包。总复杂度$O(n\log n)$。详细的也可以参考上面两道Ynoi的题解。

然后由于资瓷离线了，可以看成加的数单调递增，那么取到最大值的点也是单调的，于是直接用一个指针在凸包上扫即可。总复杂度$O(n)$。

于是询问可以$O(1)$解决。总复杂度$O(m)$。

总时间复杂度$O(n\log n+m)$，相比用前缀凸包直接相减，这个东西还是比较慢的，而且可能比较难写~~，但好想~~。

## Code：
```cpp
#include<vector>
#include<iostream>
using namespace std;
const int N=2e5+5;
typedef long long LL;
struct hull{
	struct point{
		int x;LL y;
		inline point operator-(const point&b)const{return(point){x-b.x,y-b.y};}
		inline point operator+(const point&b)const{return(point){x+b.x,y+b.y};}
	};
	inline int cross(const point&a,const point&b){return a.x*b.y>a.y*b.x?1:(a.x*b.y==a.y*b.x?0:-1);}
	vector<point>vec;
	int it;
	inline hull(){it=0;}
	inline void insert(const point&a){
		while(vec.size()>1)
		if(cross(a-vec[vec.size()-2],vec.back()-vec[vec.size()-2])<=0)vec.pop_back();else break;
		vec.push_back(a);
	}
	inline void insert(int x,LL y){insert((point){x,y});}
	hull operator*(const hull&b){
		hull c;
		int i1=0,i2=0;
		while(i1!=vec.size()-1||i2!=b.vec.size()-1){
			point pr=vec[i1]+b.vec[i2];
			c.vec.push_back(pr);
			if(i1==vec.size()-1)++i2;else
			if(i2==b.vec.size()-1)++i1;else{
				const point b1=vec[i1+1]+b.vec[i2],b2=vec[i1]+b.vec[i2+1];
				if(cross(b1-pr,b2-pr)<0)++i1;else ++i2;
			}
		}
		c.vec.push_back(vec.back()+b.vec.back());
		return c;
	}
	inline LL query(int x){
		while(it!=vec.size()-1)
		if((LL)vec[it].x*x+vec[it].y>(LL)vec[it+1].x*x+vec[it+1].y)break;else++it;
		return(LL)vec[it].x*x+vec[it].y;
	}
}h;
int n,m,a[N];
void merge(hull a,hull b,hull&c){
	c.it=0,c.vec.clear();
	int i1=0,i2=0;
	while(i1!=a.vec.size()&&i2!=b.vec.size())
	if(a.vec[i1].x<b.vec[i2].x)c.insert(a.vec[i1++]);else c.insert(b.vec[i2++]);
	while(i1!=a.vec.size())c.insert(a.vec[i1++]);
	while(i2!=b.vec.size())c.insert(b.vec[i2++]);
}
void build(int l,int r,hull&mx){
	if(l==r)mx.insert(0,0),mx.insert(1,a[l]);else{
		hull L,R;
		const int mid=l+r>>1;
		build(l,mid,L),build(mid+1,r,R);
		merge(L,R,mx);
		L=hull(),R=hull();
		LL x=0;
		L.insert(0,0),R.insert(0,0);
		for(int i=mid;i>=l;--i)L.insert(mid-i+1,x+=a[i]);
		x=0;
		for(int i=mid+1;i<=r;++i)R.insert(i-mid,x+=a[i]);
		merge(mx,L*R,mx);
	}
}
LL ans[N*4];
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i)cin>>a[i],a[i]-=2*n;
	build(1,n,h);
	for(int i=0;i<=4*n;++i)ans[i]=h.query(i);
	for(int i=1;i<=n;++i)a[i]+=4*n,a[i]*=-1;
	h=hull();
	build(1,n,h);
	for(int i=0;i<=4*n;++i)ans[4*n-i]=max(ans[4*n-i],h.query(i));
	for(LL pre=0;m--;){
		int x;
		cin>>x;
		x=(x+pre)%(4*n+1)-2*n;
		cout<<(pre=ans[x+2*n])<<'\n';
	}
	return 0;
}
```

---

## 作者：waaadreamer (赞：1)

怎么感觉大家都是算半平面交做的这道题啊……（难道是自己太菜了？）

这道题应该可以用裸的凸包+三分水过

这道题上来就可以发现是前缀和减一下做，对于每个询问，我们需要做的是区间加下标的操作，显然区间加下标不会破坏凸包的凸性。

因此我们可以在一开始以(下标，前缀和)建点分别求出上凸包和下凸包，这样每次的最大值必然在上凸包上，最小值必然在下凸包上。三分一下就可以做完了。总复杂度O(nlogn)

PS:这道题比较水，如果改一下呢？如果不是所有数字一起加上x，而是每次一段区间中加上x，怎么破？

可以考虑分块维护凸包，这样只有两个操作：区间加下标，区间加常数，显然都可以在块上打标记。查询的话零散块暴力，其他块三分一下，总复杂度可以做到O(n*sqrt(nlogn))。（当然这只是我的想法，可能有更好的算法，欢迎大佬们指导本蒟蒻）。
我凸包和三分写的很丑，都不敢拿出来了……
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 200005, maxr = 10000000;
ll sum[maxn];
int que[maxn], up[maxn], down[maxn], n, m, cnt1, cnt2;
double slope(int a, int b){
	return (sum[a] - sum[b]) * 1.0 / (a - b);
}
char prt[maxr]; int ppos;
void print(ll x, char c){
	if(x > 0){
		static char sta[20];
		int tp = 0;
		for(; x; x /= 10) sta[tp++] = x % 10 + '0';
		while(tp > 0) prt[ppos++] = sta[--tp];
	} else prt[ppos++] = '0';
	prt[ppos++] = c;
}
int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++){
		int t; scanf("%d", &t);
		sum[i] = sum[i - 1] + t;
	}
	int ta = 0; ll la = 0;
	for(int i = 0; i <= n; i++){
		while(ta >= 2 && slope(que[ta], que[ta - 1]) < slope(que[ta - 1], i)) --ta;
		++ta, up[ta] = que[ta] = i;
	}
	cnt1 = ta, ta = 0;
	for(int i = 0; i <= n; i++){
		while(ta >= 2 && slope(que[ta], que[ta - 1]) > slope(que[ta - 1], i)) --ta;
		++ta, down[ta] = que[ta] = i;
	}
	cnt2 = ta;
	while(m--){
		int x; scanf("%d", &x);
		x = (x + la) % (4 * n + 1) - 2 * n;
		int l = 1, r = cnt1;
		while(l + 3 <= r){
			int k = (r - l + 1) / 3, m1 = l + k, m2 = r - k;
			if((ll)up[m1] * x + sum[up[m1]] > (ll)up[m2] * x + sum[up[m2]]) r = m2;
			else l = m1;
		}
		ll res = 0, mn = 1E17;
		for(int i = l; i <= r; i++) res = max(res, (ll)up[i] * x + sum[up[i]]);
		l = 1, r = cnt2;
		while(l + 3 <= r){
			int k = (r - l + 1) / 3, m1 = l + k, m2 = r - k;
			if((ll)down[m1] * x + sum[down[m1]] < (ll)down[m2] * x + sum[down[m2]]) r = m2;
			else l = m1;
		}
		for(int i = l; i <= r; i++) mn = min(mn, (ll)down[i] * x + sum[down[i]]);
		print(la = res - mn, '\n');
	}
	fwrite(prt, 1, ppos, stdout);
	return 0;
}
```
加个输入输出优化还是蛮快的……

---

