# Maximal Intersection

## 题目描述

给定n个闭区间,现在要求从这些闭区间中删除一个区间，使得剩下的（n-1）个区间的交集的长度最大，求这个最大值。

（p.s.：若这个区间为空集或它的左端点与右端点重合，则长度为0；否则其长度为右端点在数轴上表示的数-左端点在数轴上表示的数）

## 样例 #1

### 输入

```
4
1 3
2 6
0 4
3 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
2 6
1 3
0 4
1 20
0 4
```

### 输出

```
2
```

## 样例 #3

### 输入

```
3
4 5
1 2
9 20
```

### 输出

```
0
```

## 样例 #4

### 输入

```
2
3 10
1 5
```

### 输出

```
7
```

# 题解

## 作者：CreeperK (赞：10)

## Codeforces Round 506 Div.3 C

个人觉得我的题解是最粗暴的。。。望各位dalao斧正。

____

时隔4个多月，终于把这道题给搞懂了。。。而且还是巧合之下搞懂的。

当时我做的时候，一直在想怎么处理这个删除操作。

我就想啊，怎么也会有个贪心的策略吧，于是便是一通乱弄。

结果？四个样例都有没过的。

然后又是拼命的想啊想。。。

结果硬是搞了一个多小时没有搞出来。。。我的第一次CF就这样结束了，以两题的弱鸡成绩告终。

现在想想，其实那时自己是根本不会打CF。这种题交给我现在来打，少说一场也有三四道。（不存在的）

___

下面进入正题。

到底是怎么想出来的呢？主要是2018年12月初的一天，一个dalao同学给了我这么一道题：

>给出一个序列，全部为1~1e7的正整数。输入序列长度N以及这个序列，输出N行，第I行表示除第I个数外剩余所有数的最大公约数。$N\le 500000$。

我看到这题，第一想法就是线段树。

结果那个dalao说：“如果不要数据结构呢？”

我又看了一会儿，看到数的范围不是很大，只有1e7，就想了一个用筛表+质因数分解的做法，似乎随机数据能卡过，但如果造一些全是大质数的，那就会爆掉了。

这时，另一个dalao走了过来。听了题目，他略想了一两秒钟，给出了$O(N)$的做法：

>存储两个数组l和r，分别表示“前缀GCD”和“后缀GCD”。

>那么对于第$I(1<I<N)$个数，答案就是$gcd(l[i-1],r[i+1])$。

>对于头尾两个数，答案分别是$r[i+1]$和$l[i-1]$。

>同理，这个做法可以推广到删去$[l,r]$所有的数后剩余数的GCD的题目。

我一下子豁然开朗。干嘛非得要先把它加入GCD，然后再分离出来呢？直接避开加入的过程不就好了？

这个思想是很有用的。比如，对于星球大战那道题，它让你删边，但实际上可以离线掉，直接加边搞定。

> 记住，往往比忘掉容易。

> ————某个动漫（雾）

> 插入，往往比删除容易。

> ————我（大雾）

在很多题中，这个思路都是极其重要的。

本题也是如此。思路如下：

>记录前缀区间交和后缀区间交数组lp和rp。

>扫描两次数组，把lp和rp求出来。

>则对于每条线段，删去后的区间便是$[max(lp[i-1].l,rp[i+1].l),min(lp[i-1].r,rp[i+1].r)]$。

就这样，扫描了三遍数组，巧妙地解决了本题。

可能计算过程中，会导致左端点大于右端点，不符合区间书写标准，但是我们不用理它，因为可以把$l>r$的区间$[l,r]$看作不合法区间，长度为-1。

代码如下：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int iz=3e5+5;
int lpl[iz],lpr[iz],rpl[iz],rpr[iz];//前缀与后缀
int l[iz],r[iz];//线段们
int n;
int main(){
	scanf("%d",&n);
	memset(lpr,0x7f,sizeof(lpr));
	memset(rpr,0x7f,sizeof(rpr));
	for(int i=1;i<=n;i++){
		scanf("%d%d",&l[i],&r[i]);
		lpl[i]=max(lpl[i-1],l[i]);
		lpr[i]=min(lpr[i-1],r[i]);
	}//读入&求出lp
	for(int i=n;i>=1;i--){
		rpl[i]=max(rpl[i+1],l[i]);
		rpr[i]=min(rpr[i+1],r[i]);
	}//求出rp
	int maxn=0;//把不合法的区间和长度为0的区间排除
	for(int i=1;i<=n;i++){
		maxn=max(min(lpr[i-1],rpr[i+1])-max(lpl[i-1],rpl[i+1]),maxn);//取区间长度最大值
	}
	printf("%d",maxn);
}
```

---

## 作者：Mickey_snow (赞：5)

[CF1029C](http://codeforces.com/problemset/problem/2029/C) _Maximal Intersection_ : 暴力

题目大意：给定 $n$ 个区间，你需要在当中去掉一个，求剩下区间交的长度。这里长度是指区间右端点数值减去左端点，例如区间 $[1,2]$ 长度为 $1$.区间交指区间相交的部分，例如区间 $[2,5]$ 和区间 $[3,8]$ 的区间交为 $[3,5]$.

在这题中，$n$ 高达 $3 \times 10^5$ ，很容易让人想到贪心，去掉区间长度最小的。但是这么做是错误的，因为这个最小的区间位置是不确定的，很有可能是这样的情况：

![](https://cdn.luogu.com.cn/upload/pic/30378.png)

这种情况下，正解应该是去掉橘色的线段，而我们的贪心却去掉了黑色的。

不得不说这题的数据范围非常具有欺骗性，尽管 $n$ 最高有可能达到 $3 \times 10^5$ ，我们依然可以在 $O(N)$ 的时间复杂度内计算出一个数组 $a$, 其中 $a_i$ 代表去掉区间 $i$ 后所有区间的区间并。

这里给出合并两个区间的代码，它很好理解：

```cpp
struct cg {
	int fr, to;
};

cg Range(cg a, cg b) {
	cg ret;
	ret.fr = std::max(a.fr, b.fr); ret.to = std::min(a.to, b.to);
	return ret;
}
```

cg是为了保存一个区间写的结构体。记合并区间 $A$ 和 $B$ 为 $A \bigotimes B$ .

当我们合并一堆区间的时候，无论按照什么顺序合并，结果一定一样。换句话说，$\bigotimes$ 运算满足交换律：

$$A \bigotimes B \bigotimes C = A \bigotimes C \bigotimes B$$

假设题目给定的区间为 $b_i$ ，那么 

$$a_i = b_0 \bigotimes \cdots \bigotimes b_{i-1} \bigotimes b_{i+1} \bigotimes \cdots \bigotimes b_{n-1}$$

将这个过程分为两部分，第一部分为所有 $b_j | j < i$ ,第二部分为所有 $b_j | j > i$ .可以发现我们没有必要单独为每一个 $a$ 计算一遍这个过程，将 $a_i$ 的第一部分添加一个 $b_i$ 就是 $a_{i+1}$ 的第一部分了，按照这个思路，计算所有的第一部分时间复杂度为 $O(N)$, 第二部分也是。

```cpp
	cg now = *seg;
	for (int i = 1; i < totSeg; i++) {
		arr[i] = now;
		now = Range(now, seg[i]);
	}
	now = seg[totSeg - 1];
	for (int i = totSeg - 2; i >= 0; i--) {
		arr[i] = Range(arr[i], now);
		now = Range(now, seg[i]);
	}
```

代码中 $arr$ 就是之前提到的 $a$ 数组， $seg$ 就是之前提到的 $b$ 数组。

执行完这一过程，$a$ 数组即为满足条件的数组。最后再扫一遍，求出一个最大值即可。总的时间复杂度仍然为 $O(N)$.

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

struct cg {
	int fr, to;
};
cg seg[300500], arr[300500];

cg Range(cg a, cg b) {
	cg ret;
	ret.fr = std::max(a.fr, b.fr); ret.to = std::min(a.to, b.to);
	return ret;
}

int main()
{
	int totSeg, fr, to;

	cin >> totSeg;
	for (int i = 0; i < totSeg; i++) {
		cin >> fr >> to;
		seg[i] = { fr,to };
		arr[i] = { INT_MIN,INT_MAX };
	}

	cg now = *seg;
	for (int i = 1; i < totSeg; i++) {
		arr[i] = now;
		now = Range(now, seg[i]);
	}
	now = seg[totSeg - 1];
	for (int i = totSeg - 2; i >= 0; i--) {
		arr[i] = Range(arr[i], now);
		now = Range(now, seg[i]);
	}

	int _max = 0;
	for (int i = 0; i < totSeg; i++)
		_max=std::max(_max, arr[i].to - arr[i].fr);

	cout << _max << endl;

	//system("pause");
	return 0;
}
```

---

## 作者：fchwpo (赞：2)

我们枚举不选哪个区间然后 $O(1)$ 计算不选后的交集就可以了。
如何计算呢，我们考虑找交集的过程，即为左端点取最大值，右端点取最小值，那么直接记录一个前缀交集和一个后缀交集，不就可以计算了吗，于是本题就做完了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+5;
struct node{
	int ll,lr,rr,rl;
	int l,r;
}p[maxn];
int n;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>p[i].l>>p[i].r;
	int nowl=-1,nowr=1e9+5;
	for(int i=1;i<=n;i++){
		p[i].ll=nowl;
		p[i].lr=nowr;
		nowl=max(p[i].l,nowl);
		nowr=min(p[i].r,nowr);
	} 
	nowl=-1,nowr=1e9+5;
	for(int i=n;i;i--){
		p[i].rl=nowl;
		p[i].rr=nowr;
		nowl=max(p[i].l,nowl);
		nowr=min(p[i].r,nowr);
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		ans=max(ans,min(p[i].rr,p[i].lr)-max(p[i].ll,p[i].rl));
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：localhost (赞：2)

其实一点stl什么的都不用用到

区间交也就是$[\max(l_i),\min(r_i)]$

我们要求的就是每次删掉某个区间后其他区间的区间交

我们只需要记录最大$l_i$和次大$l_i$还有最小$r_i$和次小$r_i$

若当前要删掉的区间$[l_i,r_i],l_i$为最大L,那我们就取次大L

R同理

上代码：

```cpp
#include<bits/stdc++.h>
namespace ZDY{
    #pragma GCC optimize(3)
    #define il __inline__ __attribute__ ((always_inline))
    #define rg register
    #define ll long long
    #define ull unsigned long long
    #define db double
    #define sht short
    #define MB template <class T>il
    #define Fur(i,x,y) for(int i(x);i<=y;++i)
    #define Fdr(i,x,y) for(int i(x);i>=y;--i)
    #define fl(i,x) for(int i(head[x]),to;to=e[i].to,i;i=e[i].nxt)
    #define clr(x,y) memset(x,y,sizeof(x))
    #define cpy(x,y) memcpy(x,y,sizeof(x))
    #define fin(s) freopen(s".in","r",stdin)
    #define fout(s) freopen(s".out","w",stdout)
    #define fcin ios::sync_with_stdio(false)
    #define l2(n) ((int)(log2(n)))
    #define inf 2122219134
    MB T ABS(T x){return x>0?x:-x;}
    MB T MAX(T x,T y){return x>y?x:y;}
    MB T MIN(T x,T y){return x<y?x:y;}
    MB T GCD(T x,T y){return y?GCD(y,x%y):x;}
    MB void SWAP(T &x,T &y){T t=x;x=y;y=t;}
}using namespace ZDY;using namespace std;
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}il void in(string &ch){ch.clear();if(__)return;rg char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}ch+=c;while((c=gc())!=EOF&&!isspace(c))ch+=c;if(c==EOF)__=1;}il void in(char &ch){if(__)return;rg char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)__=1;else ch=c;}il void in(char *ch){*ch='\0';if(__)return;rg char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)__=1;*ch='\0';}template<typename T>il void in(T &x){if(__)return;rg char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}il void out(const char* s){while(*s)pt(*s++);}il void out(char* s){while(*s)pt(*s++);}il void out(char c){pt(c);}il void out(string s){for(int i=0;s[i];i++)pt(s[i]);}template<typename T>il void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>il void out(T x,arr & ... y){out(x),out(y...);}}using namespace IO;
#define N 300011
int n,ml1=0,ml2=0,mr1=inf,mr2=inf;
struct node{
    int l,r;
}a[N];
int main(){
    in(n);
    int l,r;
    Fur(i,1,n){
        in(l,r);
        a[i]={l,r};
        if(l>=ml1)ml2=ml1,ml1=l;
        else if(l>ml2)ml2=l;

        if(r<=mr1)mr2=mr1,mr1=r;
        else if(r<mr2)mr2=r;
    }
    int ans=0,L,R;
    Fur(i,1,n){
        l=a[i].l,r=a[i].r;
        if(l==ml1)L=ml2;
        else L=ml1;

        if(r==mr1)R=mr2;
        else R=mr1;
        ans=MAX(ans,R-L);
    }
    printf("%d\n",ans);
}
```

---

## 作者：l_water (赞：2)

STL库大法好！！！众所周知STL库有很多毒瘤的东西，红黑树，散列表，集合，排序，找中位数等等一些超级好用的东西，那么其实很少人用multiset了.......能用
的话也是用优先队列了QAQ，还是救救multiset哇！
```
#include<bits/stdc++.h>
#define maxn 1000010
using namespace std;
multiset<int> l,r;
int n,x[maxn],y[maxn];
int main()
{
	cin>>n;
	for(register int i=1;i<=n;i++)
	{
		cin>>x[i]>>y[i];
		l.insert(x[i]);//自动排序哦
		r.insert(y[i]);//一个记录左区间一个记录右区间
       }
	int ans=0;
	for(register int i=1;i<=n;i++)
	{
		l.erase(l.find(x[i]));//有重复区间不用set
		r.erase(r.find(y[i]));
		ans=max(ans,*r.begin()-*l.rbegin());//找到左右区间的最大和最小值，因为是迭代器所以一定要加*号表示值
		l.insert(x[i]);//加入区间
		r.insert(y[i]);
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：Jorisy (赞：1)

与 CF754D 类似，是其弱化版。

题目说去掉一个，其实就是选 $n-1$ 个。

按左端点升序后，用小根堆去维护右端点以保证区间尽量靠近。

然后记 $ans$ 为答案（最大的区间交集），当堆的元素为 $n-1$ 时更新即可。

AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;

struct node{
	int l,r,id;
	bool operator<(const node &x)const
	{
	    return l<x.l;//按左端点排序
	}
}a[1000005];
priority_queue<int,vector<int>,greater<int>>q;

int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].l>>a[i].r;
		a[i].id=i;
	}
	sort(a+1,a+n+1);
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		q.push(a[i].r);
		if(q.size()>n-1) q.pop();//个数过多，弹出即可
		if(q.size()==n-1&&ans<q.top()-a[i].l) ans=q.top()-a[i].l;//更新答案
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Zachary_260325 (赞：1)

### 这题太有意思了!~~（虽然是水题）~~忍不住想写一篇题解~~（骗经验）~~### 
分析题干，**讲述的意思是：给定n个区间，求去掉一个区间后，其它所有区间的重合部分的最大值是多少。**

看到题干，就发现了亮点——只能删除**一个**区间

那么就可以暴力找出要删除的区间了。

**~~但是怎么找啊！！！一个个试吗？？？~~**

简单来说，我的方法确实是一个个去判断。

首先求出在不删除任何一个区间的情况下，所重合的区间。

（代码实现：暴力取min和max）
```cpp
	a[0]=read();//存储每个区间左端点
	b[0]=read();//存储每个区间右端点
	l=a[0];//l,r存储现在重合的区间的左、右端;
	r=b[0];
	for(int i=1;i<n;++i)
	{
		a[i]=read();
		b[i]=read();
		l=std::max(l,a[i]);
		r=std::min(r,b[i]);
	}//因为是所有区间的重合区间,所以剩下的区间一定是最大的左端点和最小的右端点之间的区域,如果出现l>r的情况稍微特判一下把大小赋值为0就行
```
取完之后，就知道了不去除所重合的范围~~（然后输出？）~~

那么接着考虑去除的区间在什么情况下能增加其它区间的重合大小呢？

只有在其它区间都**包含**这个区间所**不包含**的一个**范围**的时候。

那么可以得出，去除的这个区间一定与边界**（至少一边）**有重合，而且和这个边界重合的区间只有这一个的时候，可以增加范围。

因此可以再扫一遍，找与边界重合的区间

```cpp
	get1=get2=-1;
	for(int i=0;i<n;++i)
	{
		if(a[i]==l)
			if(get1==-1)
				get1=i;
			else
				get1=-2;
		if(b[i]==r)
			if(get2==-1)
				get2=i;
			else
				get2=-2;
	}
```

找到可以去除的区间之后，再分别扫（至多）两遍，来确定除去这个区间，剩下区间的大小，并从两遍里面取较大的区间，最后输出即可。

```cpp
	if(get1>=0)
	{
		l=-1;
		r=1000000005;
		for(int i=0;i<n;++i)
			if(i!=get1)
			{
				l=std::max(l,a[i]);
				r=std::min(r,b[i]);
			}
	}
	ans=std::max(ans,r-l);
	if(get2>=0)
	{
		l=-1;
		r=1000000005;
		for(int i=0;i<n;++i)
			if(i!=get2)
			{
				l=std::max(l,a[i]);
				r=std::min(r,b[i]);
			}
	}
	ans=std::max(ans,r-l);
	printf("%d",ans);
```

反正还有很多可以优化的地方，比如第一遍取所有范围的重合范围时，直接取出与两个边界重合的边的编号就行，~~懒得改了~~

---

## 作者：lihongqian__int128 (赞：0)

# CF1029C Maximal Intersection题解
我们考虑求取一些区间的交集的长度的过程：右端点取最小值，左端点取最大值，相减再对 $0$ 取最大值。

再考虑删一个区间 $[l_i,r_i]$，答案为 $\max(0,\min(\min\limits_{j=1}^{i-1}r_j,\min\limits_{j=i+1}^{n}r_j)-\max(\max\limits_{j=1}^{i-1}l_j,\max\limits_{j=i+1}^{n}l_j))$。

维护左端点前缀最大值、右端点前缀最小值、左端点后缀最大值、右端点后缀最小值即可。

时间复杂度：$\Theta(n)$。

代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std ;
const int N=3e5+5;
int n,l[N],r[N],ql[N],qr[N],hl[N],hr[N],ans;
signed main()
{
    memset(qr,0x3f,sizeof qr);
    memset(hr,0x3f,sizeof hr);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>l[i]>>r[i],ql[i]=max(ql[i-1],l[i]),qr[i]=min(qr[i-1],r[i]);
    for(int i=n;i;i--)hl[i]=max(hl[i+1],l[i]),hr[i]=min(hr[i+1],r[i]);
    for(int i=1;i<=n;i++)ans=max(ans,min(qr[i-1],hr[i+1])-max(ql[i-1],hl[i+1]));
    cout<<ans;
    return 0 ;
}
```

---

## 作者：liuzhongrui (赞：0)

## 题意：

这是一道关于区间处理的问题，要求在给定一系列闭区间的情况下，通过移除一个区间使得剩余区间的交集长度最大化。

## 思路：

首先读取区间数量 $n$，然后读取每个区间的两个端点值。将左端点和右端点分别存入两个数组中，并创建两个额外的数组用于存储原始的左右端点值，以便后续操作。

接下来对左端点数组和右端点数组进行排序。这样可以帮助我们快速找到最小左端点和最大右端点。

做完上述过程后，遍历每一个区间，对于每个区间，我们尝试将其从区间集合中“移除”（实际上是在计算交集长度时忽略这个区间），然后计算剩余区间的最大交集长度。具体来说，每次迭代中：
   - 设置当前可能的最大右端点为 $b_1$（排序后的最小右端点）。
   - 设置当前可能的最小左端点为 $a_n$（排序后的最大左端点）。
   - 如果当前考察的区间的左端点恰好是 $a_n$，则将左端点更新为 $a_{n-1}$，因为这有可能扩大交集的长度。
   - 如果当前考察的区间的右端点恰好是 $b_1$，则将右端点更新为 $b_2$，同样是为了尝试扩大交集长度。
   - 更新全局最大交集长度 $len$。

最后，输出全局最大交集长度 $len$ 即可。

## 复杂度分析：

**时间复杂度**：主要由排序决定，为 $O(n \log n)$。

**空间复杂度**：使用了额外的数组存储左右端点和原始值，空间复杂度为 $O(n)$。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=3e5+10;
int n,len;
int a[N],b[N],c[N],d[N];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
		c[i]=a[i];
		d[i]=b[i];
	}
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++){
		int l=a[n],r=b[1];
		if(a[n]==c[i])l=a[n-1];
		if(b[1]==d[i])r=b[2];
		len=max(len,r-l);
	}
	cout<<len;
	return 0;
}
```

---

## 作者：BLUESKY007 (赞：0)

~~论Div3出这样巨水的送分题竟然还没多少人AC（虽说当时我也没A...其实我A了D...逃）~~  
这个题其实一点都不麻烦,排序都可以免掉(如果用$priority\_queue$的话)  
先考虑不删除区间的情况,那么答案应该由所有区间中左端点坐标最大的区间和右端点坐标最小的区间决定(手动模拟一下加入新的区间造成的更严格的约束即得),所以想在删掉一个区间后使得剩余的区间的交尽可能大只需要考虑删去左端点最大的区间和右端点最小的区间即可  
一定有人会问如果左端点最大且坐标相同的区间不是一个的时候删哪一个,其实完全不需要考虑(如果有不止一个那你删哪个都不能放宽左端点约束),右端点同理,所以我们可以直接把所有的左端点和右端点分别放入优先队列,最后讨论删除区间的情况取$max$即可  
如果左端点最大的区间和右端点最小的区间是同一个区间,那就铁定删掉这个区间就对了(谁让它是最严格的约束呢$qwq$)  
下面按照惯例放AC代码$\downarrow\downarrow\downarrow$

```cpp
#include<cstdio>//CF1029C
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<queue>

using namespace std;

int n,ansl,ansr;

struct lborder{
	int x,id;
	bool operator<(const lborder&rhs)const{
		return x<rhs.x;
	}
};

struct rborder{
	int x,id;
	bool operator<(const rborder&rhs)const{
		return x>rhs.x;
	}
};

lborder lb;rborder rb;

priority_queue<lborder>ql;priority_queue<rborder>qr;

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&lb.x,&rb.x);
		lb.id=i;
		rb.id=i;
		ql.push(lb);
		qr.push(rb);
	}
	if(ql.top().id==qr.top().id){
		ql.pop();
		qr.pop();
		printf("%d\n",max(0,qr.top().x-ql.top().x));
		return 0;
	}
	ansl=ql.top().x;
	ansr=qr.top().x;
	ql.pop();
	qr.pop();
	int ans=max(ansr-ql.top().x,qr.top().x-ansl);
	printf("%d\n",max(ans,0));
	return 0;
} 
```

---

