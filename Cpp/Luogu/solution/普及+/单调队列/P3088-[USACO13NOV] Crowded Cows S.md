# [USACO13NOV] Crowded Cows S

## 题目描述

Farmer John's N cows (1 <= N <= 50,000) are grazing along a one-dimensional fence.  Cow i is standing at location x(i) and has height h(i) (1 <= x(i),h(i) <= 1,000,000,000).

A cow feels "crowded" if there is another cow at least twice her height within distance D on her left, and also another cow at least twice her height within distance D on her right (1 <= D <= 1,000,000,000).  Since crowded cows produce less milk, Farmer John would like to count the number of such cows.  Please help him.

FJ有 $N(1\le N\le50000)$ 头奶牛沿着一维的栅栏吃草，第 $i$ 头奶牛在目标点 $x_i$ ，它的身高是 $h_i (1 \le x_i,h_i\le10^9)$。

当一头奶牛左边 $D(1\le D\le10^9)$ 距离内且右边 $D$ 距离内有身高至少是它的两倍的奶牛，它就会觉得拥挤。

请计算觉得拥挤的奶牛的数量。


## 说明/提示

There are 6 cows, with a distance threshold of 4 for feeling crowded.  Cow #1 lives at position x=10 and has height h=3, and so on.


The cows at positions x=5 and x=6 are both crowded. 



## 样例 #1

### 输入

```
6 4 
10 3 
6 2 
5 3 
9 7 
3 6 
11 2 
```

### 输出

```
2 
```

# 题解

## 作者：jzqjzq (赞：29)

楼下STL的nlogn做法也很巧妙啊

这里说一下O(n)的单调队列做法

首先每个元素肯定要按照位置排序，然后依次进队，判断如果队尾的数大小小于要进队的数，那就把队尾弹出，直到队尾的数大于等于要进队的数

这是为了维护单调性

然后再判断如果队头的数位置的差值大于d，出队，直到差值小于d，此时队头的数为单调队列内的合法最大值

因此只要将要进队的数与目前的队头元素比较即可

这样维护了前面的，后面的反一下就好了

时间复杂度：因为每个元素最多进队出队一次，所以是O(n)的

```cpp
#include<bits/stdc++.h>
using namespace std;
struct ppap{
    int x,y;
}a[100001];
ppap qq[100001];
bool q[100001],h[100001];
inline bool cmp(ppap a,ppap b){return a.x<b.x;}
int main()
{
    int n,d;scanf("%d%d",&n,&d);
    for(int i=1;i<=n;i++)scanf("%d%d",&a[i].x,&a[i].y);
    sort(a+1,a+n+1,cmp);
    int l=1,r=0;
    for(int i=1;i<=n;i++){
        while(l<=r&&qq[r].y<a[i].y)r--;
        qq[++r]=a[i];
        while(l<=r&&qq[l].x<a[i].x-d)l++;
        if(qq[l].y>=a[i].y*2)q[i]=1;
    }
    memset(qq,0,sizeof qq);l=1;r=0;
    for(int i=n;i;i--){
        while(l<=r&&qq[r].y<a[i].y)r--;
        qq[++r]=a[i];
        while(l<=r&&qq[l].x>a[i].x+d)l++;
        if(qq[l].y>=a[i].y*2)h[i]=1;
    }
    int ans=0;
    for(int i=1;i<=n;i++)if(q[i]&&h[i])ans++;
    printf("%d",ans);
    return 0;
}
```

---

## 作者：一只书虫仔 (赞：15)

#### Description

> 给定一个长度为 $n$ 的序列 $a_i$，求有多少个位置满足左边和右边 $d$ 个数中 **都** 有大于等于 $2 \times a_i$ 的数。

#### Solution

~~这题我们教练 10min AC，帮我调试用了 1h，教练说都要疯了~~        
~~于是教练让我写一个做题心得，我就来顺便写一个题解力~~

一看到所谓长度为 $d$ 的区间，那么肯定就是单调队列了。

题目所说的就是查找一个位置左边和右边的长度为 $d$ 的区间，那么我们可以这么查询最大值，如果最大值比 $2 \times a_i$ 大，那么肯定就存在。

注意，题目说的是左右两边的区间 **都** 存在，所以左右我们都需要查询一遍，然后取一个 $\rm and$。

小细节（也就是教练让我写的做题心得那一部分）：

- 在最开始要先双关键词对 $x[i]$ 排序，这样方便之后进行距离特判。
- 缺少的部分不要用 $0$ 填充，可以直接计算距离，否则可能会 TLE。
- 计算距离的时候从左到右计算有没有超出范围是 $x[\text{front}(ind)]<x[i]-d$，从右到左计算有没有超出范围是 $x[\text{front}(ind)]>x[i]+d$。
- 注意 $2 \times a_i$ 要和最后单调队列跑完之后的 $\text{front}(q)$ 进行比较，如果在过程中比较会有逻辑错误。

#### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

struct fjrtxdy {
	int x, h;
} a[50086];

bool fjrakioi (fjrtxdy fjr, fjrtxdy akioi) {
	return fjr.x < akioi.x;
}

deque <int> q;
deque <int> ind;

bool ans1[50086];
bool ans2[50086];

int main () {
	int n, d;
	scanf("%d%d", &n, &d);
	for (int i = 1; i <= n; i++) scanf("%d%d", &a[i].x, &a[i].h);
	sort(a + 1, a + n + 1, fjrakioi);
	int cnt = 0;
   bool qwq = true;
	for (int i = 1; i <= n; i++) {
		while (!ind.empty() && a[ind.front()].x < a[i].x - d) {
			q.pop_front();
			ind.pop_front();
		}
        while (qwq) ;
		while (!q.empty()) {
			int tmp = q.back();
			if (tmp <= a[i].h) {
				q.pop_back();
				ind.pop_back();
			}
			else break;
		}
		q.push_back(a[i].h);
		ind.push_back(i);
		if (q.front() >= a[i].h * 2) ans1[i] = true;
	}
	q.clear(), ind.clear();
	for (int i = n; i >= 1; i--) {
		while (!ind.empty() && a[ind.front()].x > a[i].x + d) {
			q.pop_front();
			ind.pop_front();
		}
		while (!q.empty()) {
			int tmp = q.back();
			if (tmp <= a[i].h) {
				q.pop_back();
				ind.pop_back();
			}
			else break;
		}
		q.push_back(a[i].h);
		ind.push_back(i);
		if (q.front() >= a[i].h * 2) ans2[i] = true;
	}
	for (int i = 1; i <= n; i++)
		if (ans1[i] && ans2[i])
			cnt++;
	printf("%d\n", cnt);
	return 0;
}
```

---

## 作者：yangzechenc (赞：9)

一道单调队列题 ~~然而我WA了3次 QAQ~~

首先我们将奶牛们按X排序。考虑奶牛i，如果所有Xj∈[Xi-d，Xi+d]的奶牛j，其中最大的Hj＜Hi×2，那么显然奶牛i是不会觉得拥挤的。接下来我们考虑如何求这个最大的Hj。我一看 ~~哇光头XD~~ 这玩意长得真像滑窗iwi！于是我们考虑：正这做一遍，对每个i找出Xj∈[Xi-d,Xi]的最大Hj；然后再倒着做一遍，对每个i找出Xj∈[Xi，Xi+d]的最大Hj。

code：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct Lin{
    int x,h;
}; 
Lin data[50010];
int n,d;
int q[50010],l,r;
bool cnt[50010];
inline int cmp(const Lin &A,const Lin &B){
    return A.x<B.x;
}
int main(){
    scanf("%d%d",&n,&d);
    for (int i=1;i<=n;i++)
        scanf("%d%d",&data[i].x,&data[i].h);
    sort(data+1,data+n+1,cmp);
    l=r=0;
    for (int i=1;i<=n;i++){
        while (data[i].x-d>data[q[l]].x&&l<=r)	l++;
        if (data[q[l]].h>=(data[i].h<<1))	cnt[i]=1;
        while (data[i].h>data[q[r]].h&&l<=r)	r--;
        q[++r]=i;
    }
    int ans=0;
    l=r=0;
    memset(q,0,sizeof(q));
    data[n+1].h=data[n+1].x=0;
    for (int i=n;i>=1;i--){
        while (data[i].x+d<data[q[l]].x&&l<=r)	l++;
        cnt[i]&=(data[q[l]].h>=(data[i].h<<1));
        if (cnt[i]){
        //	cout<<i<<' ';
            ans++;
        }
        while (data[i].h>data[q[r]].h&&l<=r)	r--;
        q[++r]=i;
    }
    cout<<ans<<endl;
    return 20030109;//防抄袭：挂cp生日:D
}
```

---

## 作者：zhengrunzhe (赞：5)

~~这是一道单调队列的题目，但是n才五万，而且我懒得写离散化，然后我就写了个平衡树~~

显然这是一个二维偏序问题

对于每个奶牛$i$，如果它是拥挤的，则有:

$$max _{x[i]-d<=x[j]<x[i]} \left \{h[j] \right \}>=2h[i] \ \& \ max _{x[i]<x[j]<=x[i]+d} \left \{h[j] \right \}>=2h[i]$$

这个玩意显然可以单调队列，离散化+线段树，然后我写了个$Fhq Treap$

```cpp
#include<cstdio>
#include<cstdlib>
template<class type>inline const void read(type &in)
{
	in=0;char ch=getchar();bool f=0;
	while (ch<48||ch>57){if (ch=='-')f=1;ch=getchar();}
	while (ch>47&&ch<58)in=(in<<3)+(in<<1)+(ch&15),ch=getchar();
	if (f)in=-in;
}
template<class type>inline const void write(type out)
{
	if (out>9)write(out/10);
	putchar(out%10+48);
}
template<class type>inline const void writeln(type out)
{
	if (out<0)putchar('-'),out=-out;
	write(out);
	putchar('\n');
}
template<class type>inline const type max(const type &a,const type &b)
{
	return a>b?a:b;
}
const int N=5e4+10;
class Fhq_Treap
{
	private:
		struct tree
		{
			int mx,key,val,priority;
			tree *lson,*rson;
			inline const void pushup()
			{
				mx=max(val,max(lson->mx,rson->mx));
			}
		}*root,memory_pool[N],*tail,*null;
		inline const void init()
		{
			tail=memory_pool;
			null=tail++;
			null->lson=null->rson=null;
			root=null;
		}
		inline tree *spawn(int key,int val)
		{
			tree *p=tail++;
			p->key=key;
			p->mx=p->val=val;
			p->priority=rand();
			p->lson=p->rson=null;
			return p;
		}
		inline const void split(tree *p,int key,tree *&a,tree *&b)
		{
			if (p==null)return a=b=null,void();
			if (key<p->key)b=p,split(p->lson,key,a,b->lson);
			else a=p,split(p->rson,key,a->rson,b);
			p->pushup();
		}
		inline tree *merge(tree *a,tree *b)
		{
			if (a==null&&b==null)return null;
			if (a==null)return b;
			if (b==null)return a;
			if (a->priority<b->priority)return a->rson=merge(a->rson,b),a->pushup(),a;
			return b->lson=merge(a,b->lson),b->pushup(),b;
		}
	public:
		inline Fhq_Treap(){init();}
		inline const void insert(int key,int val)
		{
			tree *a,*b;
			split(root,key,a,b);
			root=merge(a,merge(spawn(key,val),b));
		}
		inline const int query(int l,int r)
		{
			tree *a,*b,*c;
			split(root,r,a,b);
			split(a,l-1,a,c);
			int mx=c->mx;
			root=merge(a,merge(c,b));
			return mx;
		}
}fhq;
int n,d,h[N],x[N],ans;
int main()
{
	read(n);read(d);
	for (int i=1;i<=n;i++)read(x[i]),read(h[i]),fhq.insert(x[i],h[i]);
	for (int i=1;i<=n;i++)
	ans+=fhq.query(x[i]-d,x[i]-1)>=h[i]*2&&fhq.query(x[i]+1,x[i]+d)>=h[i]*2;
	writeln(ans);
	return 0;
}
```

---

## 作者：zhy137036 (赞：4)

[P3088](/problem/P3088)

# 单调队列

先看板题：[P1886](/problem/P1886)

单调队列用队列实现，每次窗口向右滑动时，新进来的元素就入队。

我们手模一下这组数据（以最大值为例）：

```plain
5 3
3 5 4 2 1
```

先将 $3$ 入队：

![](https://cdn.luogu.com.cn/upload/image_hosting/jjnu2hu9.png)

再将 $5$ 入队。这时因为 $5$ 比 $3$ 大，而且 $5$ 后进来，“退役”得比 $3$ 晚，所以在一切情况下都不比 $3$ 差，**$3$ 已经没用了**，所以弹出 3 再将 5 入队：

![](https://cdn.luogu.com.cn/upload/image_hosting/cj6t996h.png)

接下来将 $4$ 入队。虽然 $4$ 比 $5$ 小，但是因为后进来，可能在 $5$“退役”之后能成为最大值，所以入队：

![](https://cdn.luogu.com.cn/upload/image_hosting/c3iywi73.png)

再将 $2$ 入队，同理：

![](https://cdn.luogu.com.cn/upload/image_hosting/73nbemc0.png)

再将 $1$ 入队，注意这时 $5$ 已经“退役”了，所以弹出：

![](https://cdn.luogu.com.cn/upload/image_hosting/8j202xug.png)

**注意到整个过程中最大值都是最左边的值。**

# 本题思路

这道题中并不关心有多少个超过两倍高度的，也不关心超过多少，所以想到维护区域内最高的牛，与这头牛身高的两倍比较。可以用单调队列维护。

但是这只能解决一头牛左边有没有足够高的牛，所以还要从右到左再来一遍。

```cpp
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
struct Cow{
	int x,h;
	bool operator<(Cow a){//为了排序
		return x<a.x;
	}
}cow[50010];
int n,d;
deque<Cow>dq;//单调队列要用双端队列
int pushleft(int x){
	while(!dq.empty()&&dq.back().h<=cow[x].h)//空了就不能再弹了
		dq.pop_back();
	dq.push_back(cow[x]);
	while(!dq.empty()&&dq.front().x+d<cow[x+1].x)//判断是否“退役”，注意刚压入的牛也可能马上“退役”，所以要判空
		dq.pop_front();
	return dq.empty()?0:dq.front().h; //因为上述原因，如果空了返回0，保证不会让牛错误地感到拥挤
}
int pushright(int x){
	while(!dq.empty()&&dq.back().h<=cow[x].h)
		dq.pop_back();
	dq.push_back(cow[x]);
	while(!dq.empty()&&dq.front().x-d>cow[x-1].x)
		dq.pop_front();
	return dq.empty()?0:dq.front().h; 
}
bool crowd[50010];//是否觉得拥挤，true表示宽敞，false表示拥挤
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>d;
	for(int i=1;i<=n;i++)
		cin>>cow[i].x>>cow[i].h;
	sort(cow+1,cow+n+1);
	for(int i=1;i<n;i++)
		if(pushleft(i)<2*cow[i+1].h)
			crowd[i+1]=1;//如果低于2倍身高就不觉得拥挤
	dq.clear();//注意清空
	for(int i=n;i>1;i--)
		if(pushright(i)<2*cow[i-1].h)
			crowd[i-1]=1;
	int ans=0;
	for(int i=2;i<n;i++)//两端的两头牛不可能觉得拥挤
		ans+=int(!crowd[i]);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Henry_he (赞：4)

楼下dalao们的方法实在是666~

作为蒟蒻的我居然用枚举过了这道题（想练算法的dalao们请见楼下）

代码:

```cpp
var x,h:array[1..500000]of longint;
    a,b:array[1..500000]of boolean;
    n,i,m,ans,j:longint;
procedure sort(l,r:longint);
var i,j,k,y:longint;
begin
  i:=l;
  j:=r;
  k:=h[(i+j)div 2];
  repeat
    while h[i]>k do
      inc(i);
    while h[j]<k do
      dec(j);
    if i<=j then
    begin
      y:=h[i];
      h[i]:=h[j];
      h[j]:=y;
      y:=x[i];
      x[i]:=x[j];
      x[j]:=y;
      inc(i);
      dec(j);
    end;
  until i>j;
  if i<r then sort(i,r);
  if l<j then sort(l,j);
end;
begin
  readln(n,m);
  fillchar(a,sizeof(a),false);
  fillchar(b,sizeof(b),false);
  for i:=1 to n do//读入，就不提了
    readln(x[i],h[i]);
  sort(1,n);//按照身高对牛牛们排序
  for i:=1 to n do//枚举每一头牛
    for j:=1 to i-1 do//枚举所有比 i 牛高的牛
    begin
      if h[j]<2*h[i] then break;//如果当前 牛不能比 i 牛的两倍高，那后面的牛更不可能
      if abs(x[i]-x[j])<=m then//判断是否在范围内
      begin
        if x[i]>x[j] then b[i]:=true;//判断在左边还是在右边
        if x[i]<x[j] then a[i]:=true;
      end;
      if (a[i])and(b[i]) then//如果左右都有就累加，查找下一头牛
      begin
        inc(ans);
        break;
      end;
    end;
  writeln(ans);//输出，hehehe
end.

```

---

## 作者：RAYMOND_7 (赞：3)

### 作为最优解我来发个题解

### 单调队列不是O(n)的吗?加上排序应该也很快啊

### 但是线段树也不慢，像我就轻轻松松拿了个rk1

### 不过楼顶那篇题解跑的好快啊，62ms又破了我纪录

闲话少叙，进入正题


------------
线段树作为最优的一种可以动态的访问区间最值的数据结构，比树状数组更快，比Spare Table使用更广泛（带修），比单调队列更具有随机访问性质，不需要滑动窗口这样询问有一定规律。

线段树绝对是最强力的数据结构，权值线段树可以吊打平衡树，函数式线段树/可持久化线段树可以碾压树状数组套平衡树（少至少一个log）,极端的，替罪羊树套权值线段树可以爆锤块状链表套权值块状数组（$nlog²n < n√n$）

此题的数据规模较大，暴力肯定死翘翘，卡过去的是神仙。

```
x(i)太大，又不好离散化，我们考虑用lower_bound/
upper_bound来定位区间端点。

不过要先排个序，把节点简单用数组下标离散一下，把线段树的位置定好，然后单点修改或整体建树。

查询i时找h[i]-D~h[i]+D区间，二分一下即可。

找到区间后找一个最大值S（线段树维护）。

如果S>=h[i]*2,则ans++。

最后输出ans。
```
喜闻乐见的代码。

很多地方是可以优化的（我太懒了不想再优化），大家试试能不能卡卡常破纪录。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
void read(int &x){
	char c=getchar();
	int k=1;
	while(c<'0'||c>'9') {if(c=='-') k=-1;c=getchar();}
	for(x=0;c>='0'&&c<='9';c=getchar())
	x=x*10+c-'0';
	x*=k;
}
const int N=200005;
int n,p,q,m,k,y,x,s,ans,c,mx,d,b[N];
struct fox{
	int wei,high;
}a[N*4];
bool operator<(fox x,fox y){
	return x.wei<y.wei;
}
int tree[N];
inline void change(int k,int l,int r,int x,int y){
	if(l>x||r<x) return;
	if(l==x&&l==r){
		tree[k]=y;
		return;
	}
	int mid=l+r>>1;
	change(k<<1,l,mid,x,y);
	change(k<<1|1,mid+1,r,x,y);
	tree[k]=max(tree[k<<1],tree[k<<1|1]);
}
inline int query(int k,int l,int r,int x,int y){
	if(l>r) return 0;
	if(l>y||r<x) return 0;
	if(x<=l&&r<=y) return tree[k];
	int mid=l+r>>1,s=query(k<<1,l,mid,x,y);
	s=max(query(k<<1|1,mid+1,r,x,y),s);
	return s;
}
int main(){
	read(n);read(m);
	for(register int i=1;i<=n;i++){
		read(a[i].wei);read(a[i].high);
	}
	sort(a+1,a+n+1);
	for(register int i=1;i<=n;++i){
		change(1,1,n,i,a[i].high);
		b[i]=a[i].wei;
	}
	for(register int i=1;i<=n;i++){
		p=q=b[i];
		p-=m;p=max(p,0);
		q+=m;
		k=lower_bound(b+1,b+n+1,p)-b;
		c=upper_bound(b+1,b+n+1,q)-b-1;//-1很重要
		s=query(1,1,n,k,i);d=query(1,1,n,i,c);
		if(min(s,d)>=a[i].high*2){
			ans++;
		}
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：EarthGiao (赞：3)

## 【思路】
单调队列    
### 【题目分析】 
每一头牛都有两边的d长度的的区间     
只要两边的区间内都有大于等于这头牛两倍身高的牛    
那他就会觉得拥挤     
求觉得拥挤的牛的数量     

### 【前缀思想】
有身高至少是它的两倍的奶牛？     
这完全可以之比较最高的那头奶牛啊？    
只要最高的比他的两倍高    
那就至少是有的了    
如果最高的不如他的两倍高    
那一定没有比他两倍高的    
所以比较最高的就可    
区间最大值？     
当然是单调队列    
但是两个区间？    
那就两个单调队列！    

### 【最终思路】
顺着扫一遍处理出每一个点左边区间内    
最高的那头牛    
倒着扫一遍处理出每一个点右边区间内    
最高的那头牛   
（这里区间指的都是合法区间即长度小于等于d的区间）       
然后在扫一遍每一个点    
看看是不是两倍都有比自己的身高高两倍的牛       
如果有那就计数    
如果没有那就继续      
## 【完整代码】
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<deque>
using namespace std;
const int Max = 50004;
struct node
{
	int x;
	int h;
}a[Max];
bool cmp(const node x,const node y)
{
	return x.x < y.x;
}
deque<node>q1,q2;
int l[Max],r[Max];
int main()
{
//	freopen("cow.in","r",stdin);
	int n,d;
	cin >> n >> d;
	for(register int i = 1;i <= n;++ i)
		cin >> a[i].x >> a[i].h;
	sort(a + 1,a + 1 + n,cmp);
	for(register int i = 1;i <= n;++ i)
	{
		while(!q1.empty() && a[i].x - q1.front().x > d)
			q1.pop_front();
		if(!q1.empty())
			l[i] = q1.front().h;
		else
			l[i] = 0;
		while(!q1.empty() && a[i].h > q1.back().h)
			q1.pop_back();
		q1.push_back(a[i]);
	}
	for(register int i = n;i >= 1;i --)
	{
		while(!q2.empty() && q2.front().x - a[i].x > d)
			q2.pop_front();
		if(!q2.empty())
			r[i] = q2.front().h;
		else
			r[i] = 0;
		while(!q2.empty() && a[i].h > q2.back().h)
			q2.pop_back();
		q2.push_back(a[i]);
	}
	int js = 0;
	for(register int i = 1;i <= n;++ i)
		if(l[i] >= a[i].h * 2 && r[i] >= a[i].h * 2)
			js ++;
	cout << js << endl;
	return 0;
}
```

---

## 作者：YosemiteHe (赞：2)

单调队列。因为要保证队首是最高的奶牛，所以这是一个单调递减队列。

用结构体存储 $x_i, h_i$，然后以坐标从小到大排一遍序。

因为每一头牛需要满足

> **左边D距离内而且右边D距离内**有身高至少是它的两倍的奶牛

所以需要从左往右，从右往左重复扫两次，标记了两次的奶牛就会觉得拥挤。

然后就可以AC了。

Code：
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 50005;
struct node {
    int x, y;
}a[N];
bool cmp(const node &a, const node &b) { //坐标从小到大排序
    return a.x < b.x;
}
int n, d, q[N], h = 1, t = 1, f[N], ans;
int main(void) {
    scanf("%d%d", &n, &d);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &a[i].x, &a[i].y);
    }
    sort(a + 1, a + 1 + n, cmp);//排序
    for (int i = 1; i <= n; ++i) { //从左往右扫一遍
        while (h <= t && a[q[h]].x < a[i].x - d) {
            h++;
        }
        if (a[i].y * 2 <= a[q[h]].y) f[i]++;
        while (h <= t && a[q[t]].y <= a[i].y) {
            t--;
        }
        q[++t] = i;
    }
    h = 1, t = 1;//初始化head和tail
    memset(q, 0, sizeof(q));//初始化单调队列
    for (int i = n; i >= 1; --i) { //然后从右往左扫一遍
        while (h <= t && a[i].x + d < a[q[h]].x) {
            h++;
        }
        if (a[i].y * 2 <= a[q[h]].y) f[i]++;
        while (h <= t && a[q[t]].y < a[i].y) {
            t--;
        }
        q[++t] = i;
    }
    for (int i = 1; i <= n; ++i) {
    	if (f[i] == 2) ans++;//统计标记了两次的奶牛的个数
	}
    printf("%d\n", ans);
    return 0;
}
```

Tks.

---

## 作者：VioletIsMyLove (赞：2)

这题我的想法是 $RMQ$ 。 $RMQ$ 刷区间内的最大值嘛，然后对于每个点，只要左边的区间的最大值大于自身，那就把左边区间的左边界往右拱一拱，拱的过程用二分 $\log_2(n)$ 的时效来实现，右边的区间做法和左边一样啊，区间越小越好嘛，然后如果左区间的左端点到自身的距离小于等于 $k$ ，右区间的右端点到自身的距离也小于 $k$，$ans$ 就加加，最后输出 $ans$ 就ok了。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
struct ZS{
	int x,h;
	bool operator <(const ZS b)const{return x<b.x;}
}a[50005];
int n,d,ans;
int b[50005][20];
int find(int x){
	int L=1,R=x,mid,cnt=1<<30;
	while(L<=R){
		mid=(R-L>>1)+L;
		if(a[mid].x>=a[x].x-d)cnt=min(cnt,mid),R=mid-1;
		else L=mid+1;
	}
	return cnt;
}
int find_(int x){
	int L=x,R=n,mid,cnt=0;
	while(L<=R){
		mid=(R-L>>1)+L;
		if(a[mid].x<=a[x].x+d)cnt=max(cnt,mid),L=mid+1;
		else R=mid-1;
	}
	return cnt;
}
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch)){ret=ret*10+ch-'0';ch=getchar();}
	return ret*f;
}
int main(){
	n=read();d=read();
	for(int i=1;i<=n;i++)a[i].x=read(),a[i].h=read();
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++)b[i][0]=a[i].h;
	for(int j=1;j<=18;j++)
		for(int i=1;i<=n;i++)if(i+(1<<j-1)<=n)b[i][j]=max(b[i][j-1],b[i+(1<<j-1)][j-1]);
	for(int i=1;i<=n;i++){
		int l=find(i),r=find_(i);
		int x=log2(i-l+1),y=log2(r-i+1);
		int L=max(b[l][x],b[i-(1<<x)+1][x]),R=max(b[i][y],b[r-(1<<y)+1][y]);
		if(L>=2*a[i].h&&R>=2*a[i].h)ans++;
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：Expecto (赞：2)

stl大法好


搞两个multiset，记为左边的点和右边的点，左边的集合不断删点，右边的不断入点，每次判断下是否crowded。


```cpp
#include<bits/stdc++.h>
using namespace std;
pair<int,int> q[50050];
multiset<int > x,y;
int main(){
    int n,d;
    scanf("%d%d",&n,&d);
    for (int i=0;i<n;i++)
        scanf("%d%d",&q[i].first,&q[i].second);
    sort(q,q+n);
    int k=0,j=0,ans=0;
    for (int i=0;i<n;i++){
        while (k<n && q[i].first+d>=q[k].first)
            y.insert(q[k++].second);
        while (q[i].first-d>q[j].first)
            x.erase(x.find(q[j++].second));
        x.insert(q[i].second);
        if (*--x.end()>=q[i].second*2 && *--y.end()>=q[i].second*2) 
            ans++;
        y.erase(y.find(q[i].second));
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：mango09 (赞：1)

[传送门](https://www.luogu.com.cn/problem/P3088)


[更~~坏~~好的阅读体验](https://www.luogu.com.cn/blog/305532/post-ti-xie-p3088-post)

**思路**

> 当一头奶牛左边D距离内而且右边D距离内有身高至少是它的两倍的奶牛

不难想到使用**单调队列**（机房大佬~~Canstant0x5F3759DF~~使用的线段树我是不会）

从左到右、从右到左各扫一遍即可。

**代码**

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
#define int long long
using namespace std;

const int MAXN = 5e4 + 5;

int n, d, cnt;
bool ans1[MAXN], ans2[MAXN];
deque<int> q;

struct cow
{
	int x, h;
	bool operator <(const cow &p)const
	{
		return x < p.x;
	}
}a[MAXN];

signed main()
{
	scanf("%lld%lld", &n, &d);
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld%lld", &a[i].x, &a[i].h);
	}
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++)
	{
		while (!q.empty() && a[q.back()].h < a[i].h)
		{
			q.pop_back();
		}
		while (!q.empty() && a[i].x - a[q.front()].x > d)
		{
			q.pop_front();
		}
		q.push_back(i);
		if (a[q.front()].h >= (a[i].h << 1)) //等价于a[i].h * 2
		{
			ans1[i] = true;
		}
	}
	q.clear();
	for (int i = n; i; i--)
	{
		while (!q.empty() && a[q.back()].h < a[i].h)
		{
			q.pop_back();
		}
		while (!q.empty() && a[q.front()].x - a[i].x > d)
		{
			q.pop_front();
		}
		q.push_back(i);
		if (a[q.front()].h >= (a[i].h << 1))
		{
			ans2[i] = true;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		if (ans1[i] && ans2[i]) //如果两个同时满足
		{
			cnt++;
		}
	}
	printf("%lld", cnt);
	return 0;
}
```


---

## 作者：SunsetSamsara (赞：1)

这题可以用线段树 $+$ 二分解决

首先，既然是左边 $D$ 距离与右边 $D$ 距离之内，就可以二分左边 $D$ 距离的下标与右边 $D$ 距离的下标，然后查询线段树中的最大值，判断是不是**大于等于** $2$ 倍的高度即可。

二分一定要注意边界，同时不能直接用两个 `lower_bound` 寻找下标，除非排序两趟，一趟正着排一趟反着排。

线段树注意是取**最大值**而不是最小值。

最后放上~~难得的 亿--遍A的~~代码:

```cpp
#include<stdio.h>
#include<algorithm>
using namespace std;
struct Node{
	int l,r;
	int data;
	Node *ls,*rs;
	void PushUp(){data=max(ls?ls->data:0x7f7f7f7f,rs?rs->data:0x7f7f7f7f);}
};
Node A[200001];
struct QYB_AK_IOI{
	int X,H;
}cs[50001];
bool cmp(QYB_AK_IOI a,QYB_AK_IOI b){return a.X<b.X;}
bool cmp1(QYB_AK_IOI a,QYB_AK_IOI b){return a.X>b.X;}
bool cmp2(QYB_AK_IOI a,QYB_AK_IOI b){return a.X<b.X;}
int N,D;
void BuildT(int id,int l,int r){
	A[id].l=l;
	A[id].r=r;
	if(l==r){
		A[id].data=cs[l].H;
		return;
	}
	A[id].ls=A+(id<<1);
	A[id].rs=A+(id<<1|1);
	int mid=(l+r)>>1;
	BuildT(id<<1,l,mid);
	BuildT(id<<1|1,mid+1,r);
	A[id].PushUp();
}
int Query(int id,int l,int r){
	if(A[id].l==l&&A[id].r==r)return A[id].data;
	int mid=(A[id].l+A[id].r)>>1;
	if(r<=mid)return Query(id<<1,l,r);
	else if(mid<l)return Query(id<<1|1,l,r);
	else return max(Query(id<<1,l,mid),Query(id<<1|1,mid+1,r));
}
int main(){
	scanf("%d%d",&N,&D);
	for(int i=1;i<=N;++i)
		scanf("%d%d",&cs[i].X,&cs[i].H);
	sort(cs+1,cs+N+1,cmp);
	BuildT(1,1,N);
	int pre,nxt;
	int ans=0;
	int l,r,mid;
	for(int i=2;i<N;++i){
		l=1;r=N;mid=(l+r)>>1;
		while(l<r){
			if(cs[mid].X<cs[i].X-D)l=mid+1;
			else r=mid;
			mid=(l+r)>>1;
		}
		pre=l;
		l=1;r=N;mid=(l+r)>>1;
		while(l<r){
			if(cs[mid].X<cs[i].X+D)l=mid+1;
			else r=mid;
			mid=(l+r)>>1;
		}
		nxt=l;
		int x,y;
		x=Query(1,pre,i-1);
		y=Query(1,i+1,nxt);
		if(Query(1,pre,i-1)>=2*cs[i].H&&Query(1,i+1,nxt)>=2*cs[i].H)
			++ans;
	}
	printf("%d\n",ans);
}
```

---

## 作者：神眷之樱花 (赞：1)

## 解析
这道题就是一道单调队列的模板题，题意很简单，与纯模板相比，这道题输入中奶牛的位置是打乱的，所以我们可以用结构体加快排将奶牛的位置由大到小排个序。
## 单调队列在此题中的应用
因为每头牛必须两边都有身高是它两倍的牛才会感到拥挤，所以我们不难想到连续用两次单调队列。一次顺序，一次逆序。
## 什么是单调队列？！
简单说一下，我们用数组模拟队列，当然也可以用 $STL$，用队头存身高最高的奶牛的编号，如果它不在当前枚举的奶牛的距离内，就让它出队，如果当前奶牛的身高大于队尾的奶牛的身高，就将队尾小于这头奶牛身高的奶牛出队，执行完这些操作后，让当前的奶牛入队，再枚举下一头奶牛。
## 注意
当逆序枚举时，范围的判断与顺序时有所不同。
```cpp
while(head<=tail&&a[q[head]].dir>a[i].dir+d) head++;
```
## AC代码
```

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5*1e5+5;
inline int read()
{
	int x=0,flag=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')flag=0;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-48;ch=getchar();}
	return flag?x:-x;
}
struct node{
	int dir,h;
}a[N];
int q[N],f[N],n,d,head=1,tail=1,tot=0;
double nb;
bool cmp(node x,node y)
{
	return x.dir<y.dir;
}
int main()
{
	n=read();d=read();
	for(int i=1;i<=n;i++)
	{
		a[i].dir=read();
		a[i].h=read();
	}
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++)
	{
		while(head<=tail&&a[q[head]].dir<a[i].dir-d) head++;
		while(head<=tail&&a[q[tail]].h<=a[i].h) tail--;
		q[++tail]=i;
		nb=1.0*a[q[head]].h/2;//注意这个细节，能避免爆数据范围的问题
		if(nb>=a[i].h) f[i]++;
	}
	head=1;tail=1;
	memset(q,0,sizeof(q));
	for(int i=n;i>=1;i--)
	{
		while(head<=tail&&a[q[head]].dir>a[i].dir+d) head++;
		while(head<=tail&&a[q[tail]].h<=a[i].h) tail--;
		q[++tail]=i;
		nb=1.0*a[q[head]].h/2;//一般用除法代替乘法
		if(nb>=a[i].h&&f[i]==1) tot++; 
	}
	printf("%d",tot);
	return 0;
}
```


---

## 作者：rfsfreffr (赞：1)

# 题意:

```cpp
有n个奶牛在吃草，它们有两个属性，高度和坐标

当一个奶牛左边D距离内有一个身高至少为它两倍的奶牛且它右边D距离内也有一个身高至少为他两倍的奶牛,它就会感到拥挤

求有多少个奶牛会感到拥挤。
```
# 解析：

首先用一个结构体来存储奶牛的两个属性。

然后再以坐标大小排序，知道奶牛们的谁前谁后

## 解法一

我们可以用RMQ来计算区间内的奶牛高度的最大值。

对于每个奶牛，可以先用二分确定，距离它小于D的奶牛们的编号范围。

在判断这个区间的奶牛高度的最大值，是否超过当前奶牛的高度的两倍。

**这种方法复杂，代码较难实现，但效率为$O(nlogn)$可以通过此题**

## 解法二

可以直接使用单调队列来维护想取到的最大值。

我的想法是扫两遍，正着一遍，反着一遍。正这时取自己前面合法的最大值，反着时取自己后面合法的最大值，若此最大值大于当前奶牛高度的两倍，$ans_i$++,如果$ans_i=2$,则该奶牛会感到拥挤。

最后再统计有多少个$ans_i=2$的奶牛，输出即可

# 代码:

```cpp
#include <bits/stdc++.h>
using namespace std;
struct oi {
	int h,x;
} a[100001];
bool cmp(oi x,oi y) {
	return x.x<y.x;
}
int ans[100001],sum;
int n,d;
deque<int>q,p;
int main() {
	cin>>n>>d;
	for(int i=1; i<=n; i++) scanf("%d%d",&a[i].x,&a[i].h);
	sort(a+1,a+1+n,cmp);//按坐标排序
	q.push_back(a[1].h);
	p.push_back(1);
	for(int i=1; i<=n; i++) {
		while(!p.empty()&&a[i].x-a[p.front()].x>d) {//单调队列维护，如果队首的坐标与自己相差大于d，则直接弹出
			q.pop_front();
			p.pop_front();
		}
		while(!q.empty()&&a[i].h>q.back()) {//从后面压入，将所有比自己小的数字弹出，以达到维护最大值的目的
			q.pop_back();
			p.pop_back();
		}
		q.push_back(a[i].h);
		p.push_back(i);
		if(q.front()>=a[i].h*2) {//统计答案
			ans[i]++;
		}
	}
	while(!q.empty()) q.pop_back(),p.pop_back();//清空队列
	for(int i=n; i>=1; i--) {//反着扫一遍
		while(!p.empty()&&a[p.front()].x-a[i].x>d) {
			q.pop_front();
			p.pop_front();
		}
		while(!q.empty()&&a[i].h>q.back()) {
			q.pop_back();
			p.pop_back();
		}
		q.push_back(a[i].h);
		p.push_back(i);
		if(q.front()>=a[i].h*2) {
			ans[i]++;
		}
	}
	for(int i=1; i<=n; i++) if(ans[i]==2) sum++;//统计感到拥挤奶牛的个数
	cout<<sum<<endl;//输出答案
	return 0;
}
/*
6 4
3 6
5 3 
6 2
9 7
10 3
11 2
*/
```
时间复杂度为$O(n)$且较好视线，是这类题目的首选做法

---

## 作者：Bazoka13 (赞：1)

[关于pbds](https://baijiahao.baidu.com/s?id=1610302746201562113&wfr=spider&for=pc)

直接扔了四棵平衡树过了（赞美$pbds$）。
使用pbds库自带的平衡树，前两棵从左向右，另外两棵相反。

前两棵的做法：
一棵插入（坐标，高度）按坐标排序，一棵插入（高度，坐标）按高度排序，每遍历到一头牛，就分别插入两棵树中，同时处理第一棵树，删除坐标最小的点直到当前树中的最小坐标在当前遍历到的牛的坐标的左侧$D$范围内，因为存的时候利用$pair$存了高度，同时也可以删掉另一棵树中的相应数据，之后找出第二棵树中高度的最大值是否是当前牛身高的两倍以上，如果是就标记。

从右到左同理。

被标记两次的即为符合要求的，计数即可。

```cpp
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define ll long long
#define il inline
tree<pair<int,int>, null_type, less<pair<int,int> >, rb_tree_tag,tree_order_statistics_node_update> rbt;
tree<pair<int,int>, null_type, less<pair<int,int> >, rb_tree_tag,tree_order_statistics_node_update> rbt2;
tree<pair<int,int>, null_type, greater<pair<int,int> >, rb_tree_tag,tree_order_statistics_node_update> rbt3;
tree<pair<int,int>, null_type, less<pair<int,int> >, rb_tree_tag,tree_order_statistics_node_update> rbt4;
il ll read(){
    char c=getchar();
    ll f=1,x=0;
    while(c<'0'||c>'9'){
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^'0');
        c=getchar();
    }
    return x*f;
}
const int N = 5e5+5;
struct cow{
    ll x,h;
}c[N];
bool cmp(cow a,cow b){
    return a.x<b.x||(a.x==b.x&&a.h<b.h);
}
int vis[N];
ll n,d;
signed main(){
    n=read();
    d=read();
    int sz=0;
    for(int i=1;i<=n;i++){
        c[i]={read(),read()};
    }
    sort(c+1,c+1+n,cmp);
    //从左到右
    for(int i=1;i<=n;i++){
        rbt.insert(pair<int,int>(c[i].x,c[i].h));//坐标，高度
        rbt2.insert(pair<int,int>(c[i].h,c[i].x));//高度，坐标
        sz++;
        if(i==1)continue;
        int pos=rbt.find_by_order(0)->first;//找到坐标最小值
        while(abs(pos-c[i].x)>d){//开始删点
            sz--;
            int ht=rbt.find_by_order(0)->second;//找高度，方便在第二棵树里删除
            rbt2.erase(make_pair(ht,pos));
            rbt.erase(rbt.find_by_order(0));
            pos=rbt.find_by_order(0)->first;
        }

        int ma=rbt2.find_by_order(sz-1)->first;//找高度最大值

        if(ma>=2*c[i].h){
           vis[i]=1;//标记
        }
    }
    //从右到左
    sz=0;
    int ans=0;
    for(int i=n;i>=1;i--){
        rbt3.insert(pair<int,int>(c[i].x,c[i].h));
        rbt4.insert(pair<int,int>(c[i].h,c[i].x));
        sz++;

        if(i==n)continue;
        int pos=rbt3.find_by_order(0)->first;
        while(abs(pos-c[i].x)>d){
            sz--;
            int ht=rbt3.find_by_order(0)->second;
            rbt4.erase(make_pair(ht,pos));
            rbt3.erase(rbt3.find_by_order(0));
            pos=rbt3.find_by_order(0)->first;
        }
        int ma=rbt4.find_by_order(sz-1)->first;
        if(ma>=2*c[i].h&&vis[i]==1){
            ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：加勒比·史努比 (赞：1)

### Solve

手动模拟一下队列就行。

1.一个递减的单调队列，保证队首是最近最高的“奶牛”（最高优先）

2.依次遍历，如果队首的比他高两倍以上，就把他标记下来；否则就不标。

3.从左到右，从右到左，重复两次，有两次标记的就是“Crowded Cows"。

####  Tips：

为什么如此标记呢？

首先，我们保证了队首是最近最高的“奶牛”。所以如果队首都没有他高，那就没有比他高的的了（最起码他前面没有了）。而第二次遍历就是解决他后面是否有比他高的“奶牛”（上文的“高”都是指高出两倍及以上）。

具体见代码

### Code

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;  //标准开头
const int N=500001;
int n,m;  //n==n,m==d
int q[N][3];  //核心队列
struct note{
	int x,h,r;
}d[N];  //d存储每头“奶牛”的信息——位置（x），高度（h)，序号(r)（序号可以方便标记）
bool vis[N][3];  //标记小能手
int ans;   //答案
int head=1,tail=1;  //head——队首，tail——队尾
bool cmp(const note &a,const note &b){  //按位置从小到大排
	return a.x<b.x;
}
int main()
{
	memset(q,0,sizeof(q));
	memset(vis,false,sizeof(vis));
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>d[i].x>>d[i].h,d[i].r=i;
	sort(d+1,d+1+n,cmp);  //sort快排，其实也可以换成其他的方法，只要不影响结果
	q[head][0]=d[1].r;
	q[head][1]=d[1].x;
	q[head][2]=d[1].h;
	for(int i=2;i<=n;i++){
		while(q[head][1]<d[i].x-m&&head<=tail) head++;  //如果队首的位置已经超出了当前“奶牛”的范围，那么队首就没有“利用价值”了，甚至会影响正常标记，所以必须删去（其实删去不是真正的删去，只是头指针后移）。
		if(q[head][2]>=d[i].h*2) vis[d[i].r][1]=true;  //标记
		while(q[tail][2]<d[i].h&&tail>=head) tail--;  //队列更新
		tail++;
		q[tail][0]=d[i].r;
		q[tail][1]=d[i].x;
		q[tail][2]=d[i].h;
	}
	head=1;
	tail=1;
	memset(q,0,sizeof(q));
	q[head][0]=d[n].r;
	q[head][1]=d[n].x;
	q[head][2]=d[n].h;
	for(int i=n-1;i>=1;i--){  //再来一遍
		while(q[head][1]>d[i].x+m&&head<=tail) head++;
		if(q[head][2]>=d[i].h*2) vis[d[i].r][2]=true;
		while(q[tail][2]<d[i].h&&tail>=head) tail--;
		tail++;
		q[tail][0]=d[i].r;
		q[tail][1]=d[i].x;
		q[tail][2]=d[i].h;
	}
	for(int i=1;i<=n;i++){  //注意是两次标记都有，才是“Crowded Cows”
		if(vis[i][1]==true&&vis[i][2]==true) ans++;
	}
	cout<<ans;  //完美输出
	return 0;
}
```

---

## 作者：Michael123456 (赞：1)

看到楼下都是单调队列/set的做法，居然没有优先队列的，本蒟蒻来一发。

主要是正反两边过来扫一遍，判断这个点是否符合。

Talk is easy.AC code: 

```cpp
#include<cstdio>
#include<queue>
#include<map>
#include<algorithm>
#include<cmath>
using namespace std;
#define maxn 50000+10 
#define P(x,y) make_pair(x,y)
struct Heapnode{
    int x,h;
}e[50000+10];
int n,d,ans;
short a[maxn];
priority_queue<pair<int,int> >Q;
int read()
{
    char r=1;int s=0;
    char c=getchar();
    while((c<'0'||c>'9')&&c!='-')c=getchar();
    if(c=='-'){r=-1;c=getchar();}
    while(c>='0'&&c<='9')s=(s<<1)+(s<<3)+(c^'0'),c=getchar();
    return s*r;
}
inline bool cmp(const Heapnode &a,const Heapnode &b){return a.x<b.x;}

int main()
{
    n=read();d=read();
    for(int i=1;i<=n;i++)e[i].x=read(),e[i].h=read();
    sort(e+1,e+1+n,cmp);//排序
    //正向判断是否在左边有满足的点
    for(int i=1;i<=n;i++)
    {
        while(!Q.empty()&&e[i].x-Q.top().second>d)  Q.pop();//超出d范围的出队
        if(!Q.empty()&&Q.top().first>=e[i].h*2) a[i]=true;//注意：一定要队列非空，否则没有满足条件的牛
        Q.push(P(e[i].h,e[i].x));//注意顺序
    }
    while(!Q.empty() )Q.pop(); //清队
    //反向过来做，思想跟上一段大致一样，但也有不同
    for(int i=n;i>=1;i--)
    {
        while(!Q.empty()&&abs(e[i].x-Q.top().second)>d) Q.pop();//注意是绝对值，因为此时是小减大
        if(!Q.empty()&&Q.top().first>=e[i].h*2)a[i]=a[i]&&1;//要两边都满足才行
        else a[i]=0;//这一行不要漏，小心
        Q.push(P(e[i].h,e[i].x));
    }
    for(int i=1;i<=n;i++)ans+=a[i];
    printf("%d",ans);
    return 0;
}
```

---

## 作者：zhzh2001 (赞：1)

## 思路


这题其实有很多方法，但是我最先想到的是按照奶牛的高度排序处理。而且这种方法也可以做被困在干草堆（金）。


首先按照奶牛的高度降序排序，在处理一只奶牛时，把大于等于它的高度的2倍的奶牛的位置放进set中，再判断一下set中的位置在当前奶牛两边的位置是否小于等于d，计入答案即可。


时间复杂度$O(N\log N)$，与其他方法相同，但常数比单调队列大。因为后者只要用到sort，比set常数小得多。


## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=50005;
pair<int,int> cow[N];
int main()
{
    int n,d;
    cin>>n>>d;
    for(int i=1;i<=n;i++)
        cin>>cow[i].second>>cow[i].first;
    sort(cow+1,cow+n+1);
    set<int> pos;
    int j=n,ans=0;
    for(int i=n;i;i--)
    {
        for(;j&&cow[j].first>=cow[i].first*2;j--)
            pos.insert(cow[j].second);
      //插入高度大于等于当前高度2倍的奶牛
        set<int>::iterator it=pos.lower_bound(cow[i].second);
      //找到右边的奶牛
        ans+=it!=pos.end()&&*it-cow[i].second<=d&&it--!=pos.begin()&&cow[i].second-*it<=d;
      //判断两边是否满足条件
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Paris_Bentley (赞：0)

个人感觉这个题目如果想到单调队列的方法就不难了。需要把两侧的拥挤分别判断，即先要看看前面是否拥挤，再判断后面是否拥挤，如果某一点前后拥挤则可以计数。

核心思想是：
1.先从前往后维护一个单调递减的队列，每次新元素入队时，判断队首元素是否大于等于二倍新元素，如果是，就证明这头牛前面很拥挤，标注一下。
2.从后向前再维护一个单调递减队列，方案同上，如果这里也拥挤ans++。

代码如下，有轻标注：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,d,ans;
struct cow
{
    int x,h;//位置和高度
};
deque <cow> dmax;
cow c[50005];
bool f[50005];
bool cmp(cow b,cow a)
{
    if (a.x!=b.x)return (a.x>b.x);
    else return (a.h>b.h);
}
int main()
{
    scanf("%d%d",&n,&d);
    for (int i=1;i<=n;i++)
        scanf("%d%d",&c[i].x,&c[i].h);
    sort(c+1,c+n+1,cmp);//从小到大 
    for (int i=1;i<=n;i++)
    {
    	int nx,nh;
    	nx=c[i].x;
    	nh=c[i].h;
		while(!dmax.empty()&&dmax.back().h<nh)
			dmax.pop_back();
		while(!dmax.empty()&&dmax.front().x<nx-d)
			dmax.pop_front(); 
		
		dmax.push_back((cow){nx,nh});
		if(dmax.front().h>=2*nh)
			f[i]=true;
	}
	while(!dmax.empty())//清空队列 
		dmax.pop_front();
	for (int i=n;i>=1;i--)
    {
    	int nx,nh;
    	nx=c[i].x;
    	nh=c[i].h;
		while(!dmax.empty()&&dmax.back().h<nh)
			dmax.pop_back();
		while(!dmax.empty()&&dmax.front().x>nx+d)
			dmax.pop_front(); 
		dmax.push_back((cow){nx,nh});
		if(dmax.front().h>=2*nh)//后面拥挤，如果这只牛前面也拥挤，就多一个ans. 
		{
			if(f[i]) 
				ans++;
		}
	}
	cout<<ans<<endl;
    return 0;
}
```


---

## 作者：B_1168 (赞：0)

这题好坑啊，因为分块一个小小的位置问题居然卡了蒟蒻十几个提交记录……

有趣的是，本题在洛谷上如通入臭氧，可将rmq部分替代为$O(n)$暴力强卡过去，但是在USACO服务器上会T掉一个点

具体的来说，蒟蒻使用排序，`std::lower_bound/upper_bound`和`map`使得我们能用低于$O(n)$的时间代价确定每头奶牛左右$d$单位距离范围内最远奶牛的编号；留意到`upper_bound`函数在奶牛距离编号最大的奶牛距离不足$d$时会越界从而返回$0$，使用三目运算符特判，~~造就了那坨长得不成样的调试语句~~

剩下的……就是标准的分块rmq模板啦！如果对各数不甚理解的话，可输出分析（滑稽）

```cpp
#include<bits/stdc++.h>
#define maxn 50005
using namespace std;

int ans,len,n,d,p[maxn],val[maxn],be[maxn];

map<int,int>mp;

struct cows{
	int x,h;
}c[maxn];

bool cmp (cows l, cows r){
	return l.x<r.x;
}

inline int query(int from,int to){
    int cnt=-(1<<30);
    for(register int i=from;i<=min(to,be[from]*len);i++) cnt=max(cnt,c[i].h);
    if(be[from]!=be[to]){
        for(register int i=(be[to]-1)*len+1;i<=to;i++) cnt=max(cnt,c[i].h);
    }
    for(register int i=be[from]+1;i<=be[to]-1;i++) cnt=max(cnt,val[i]);
    return cnt;
}

int main(){
//	freopen("crowded.in","r",stdin);
//	freopen("crowded.out","w",stdout);
	scanf("%d%d",&n,&d);
	len=sqrt(n);
	for(int i=1;i<=n;i++)be[i]=(i-1)/len+1;
	for(int i=1;i<=n;i++){
		scanf("%d%d",&c[i].x,&c[i].h);
		p[i]=c[i].x;
	}
	sort(c+1,c+n+1,cmp);
	sort(p+1,p+n+1);
	for(int i=1;i<=n;i++){
		mp[c[i].x]=i;
		val[be[i]]=max(val[be[i]],c[i].h);//THIS STEP MUST BE DONE AFTER SORTING
	}
	for(int i=2;i<n;i++){ 
//		printf("%d %d %d %d %d %d\n",mp[*lower_bound(p+1,p+n+1,p[i]-d)],i,mp[*upper_bound(p+1,p+n+1,p[i]+d)]?mp[*upper_bound(p+1,p+n+1,p[i]+d)]-1:n,query(mp[*lower_bound(p+1,p+n+1,p[i]-d)],i),query(i,mp[*upper_bound(p+1,p+n+1,p[i]+d)]?mp[*upper_bound(p+1,p+n+1,p[i]+d)]-1:n),2*c[i].h);
		if(query(mp[*lower_bound(p+1,p+n+1,p[i]-d)],i)>=2*c[i].h && query(i,mp[*upper_bound(p+1,p+n+1,p[i]+d)]?mp[*upper_bound(p+1,p+n+1,p[i]+d)]-1:n)>=2*c[i].h) {
			ans++;
//			printf("%d\n",i);
		}
	}
	printf("%d\n",ans);
}
```

感谢管理审核！

~~这题好毒瘤啊~~

---

## 作者：chenguanghui (赞：0)

离散化+线段树
（包含区间修改，向上更新，建树，区间查询等操作）
先建树，再对输入部分进行排序，记录first（离散操作）之后就好操作了
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=5e4;

namespace segment_tree
{
	
	template<class T>
	inline void sum_merge(T &a,T &b,T &c)
	{
		a=b+c;
	}
	
	template<class T>
	inline void sum_lazy_down(T &a,T &b,int n)
	{
		a+=b*n;
	}
	
	template<class T>
	inline T sum_ask_merge(T a,T b)
	{
		return a+b;
	}
	
	template<class T>
	inline void min_merge(T &a,T &b,T &c)
	{
		a=min(b,c);
	}
	
	template<class T>
	inline void min_lazy_down(T &a,T &b,int n)
	{
		a+=b;
	}
	
	template<class T>
	inline T min_ask_merge(T a,T b)
	{
		return min(a,b);
	}
	
	template<class T>
	inline void max_merge(T &a,T &b,T &c)
	{
		a=max(b,c);
	}
	
	template<class T>
	inline void max_lazy_down(T &a,T &b,int n)
	{
		a+=b;
	}
	
	template<class T>
	inline T max_ask_merge(T a,T b)
	{
		return max(a,b);
	}
	
	template<class T>
	struct tnode
	{
	    T sum,lazy;
	    int l,r;
	};
	
	template<class T>
	class Segment_Tree
	{
	public:
		void(*merge)(T &parent,T &child1,T &child2);//合并时的规则 
		void(*lazy_down)(T &value,T &lazy_value,int segment_length);//懒标记下传时的规则 
		T(*ask_merge)(T child1,T child2);//询问合并时的规则 
		 
		void sum_mode()
		{
			//求和模式 
			merge=sum_merge;
			lazy_down=sum_lazy_down;
			ask_merge=sum_ask_merge;
		}
		
		void min_mode()
		{
			//求最小模式
			merge=min_merge;
			lazy_down=min_lazy_down;
			ask_merge=min_ask_merge;
		}
		
		void max_mode()
		{
			//求最大模式
			merge=max_merge;
			lazy_down=max_lazy_down;
			ask_merge=max_ask_merge;
		}
		
		
	    void pushdown(int root)
	    {
	    	//下传 
	        if(t[root].lazy!=0)
	        {
	        	lazy_down(t[root].sum,t[root].lazy,t[root].r-t[root].l+1);
	            if(t[root].l!=t[root].r)
	            {
	                int ch=root<<1;
	                t[ch].lazy+=t[root].lazy;
	                t[ch+1].lazy+=t[root].lazy;
	            }
	            t[root].lazy=0;
	        }
	    }
	    
	    void update (int root)
	    {
	    	//上更新 
	        int ch=root<<1;
	        pushdown(ch);
	        pushdown(ch+1);
	        merge(t[root].sum,t[ch].sum,t[ch+1].sum);
	    }
	    
	    void build(int l,int r,int root=1)
	    {
	    	//建树 
	        t[root].l=l;
	        t[root].r=r;
	        t[root].sum=t[root].lazy=0;
	        if(l!=r)
	        {
	            int mid=(l+r)>>1;
	            int ch=root<<1;
	            build(l,mid,ch);
	            build(mid+1,r,ch+1);
	            update(root);
	        }
	    }
	    
	    void change(int l,int r,T delta,int root=1)
	    {
	    	//区间修改 
	    	if(l>r)
	    		return ;
	        if(l==t[root].l&&r==t[root].r)
	        {
	            t[root].lazy+=delta;
	            pushdown(root);
	            return;
	        }
	        int mid=(t[root].l+t[root].r)>>1;
	        int ch=root<<1;
	        if(r<=mid)
				change(l,r,delta,ch);
	        else if(l>mid)
				change(l,r,delta,ch+1);
	        else 
			{
				change(l,mid,delta,ch);
				change(mid+1,r,delta,ch+1);
			}
	        update(root);
	    }
	    
	    T ask(int l,int r,int root=1)
	    {
	    	//区间查询 
	    	if(l>r)
	    		return 0;
	        pushdown(root);
	        if(t[root].l==l&&t[root].r==r)
	        {
	            return t[root].sum;
	        }
	        int mid=(t[root].l+t[root].r)>>1;
	        int ch=root<<1;
	        if(r<=mid)
				return ask(l,r,ch);
	        else if(l>mid)
				return ask(l,r,ch+1);
	        else 
				return ask_merge(ask(l,mid,ch),ask(mid+1,r,ch+1));
	    }
	    
	private:
		tnode<T> t[4*MAXN];
	};		
} 

using namespace segment_tree;
Segment_Tree<int> sg;

const int N=5e4+5;
pair<int,int> a[N];
int b[N];
int n,d,m; 

int main()
{
	scanf("%d%d",&n,&d);
	sg.max_mode();
	sg.build(1,n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&a[i].first,&a[i].second);
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
	{
		b[++m]=a[i].first;
		sg.change(m,m,a[i].second);
	}
	int cnt=0;
	for(int i=1;i<=m;i++)
	{
		int now=b[i];
		int pre=max(0,now-d),nxt=now+d;
		int left=lower_bound(b+1,b+m+1,pre)-b;
		int right=upper_bound(b+1,b+m+1,nxt)-b-1;
		int left_max=sg.ask(left,i);
		int right_max=sg.ask(i,right);
		if(left_max>=a[i].second*2&&right_max>=a[i].second*2)
			cnt++;
	}
	printf("%d\n",cnt);
	
    return 0;
}


```


---

## 作者：Ofnoname (赞：0)

比较裸的单调队列题。与[P1901 发射站](https://www.luogu.org/problemnew/show/P1901)比较类似

排序，用单调队列从左扫到右，找到每一头奶牛左边D距离以内的最高奶牛并判断(每次当队中最高最靠左的奶牛与现在的奶牛距离超过D时就把他出队，保证队首是最高最靠左且距离在D以内的奶牛)。

由于两边都要判断，所以还要从右向左再扫一遍，左右都拥挤的奶牛才会贡献答案。

排序可以使用基数排序，比sort快一点点。对基数排序思想不清楚的同学可以去看一看洛谷日报。

```cpp
#include <bits/stdc++.h>
#define Getchar() (p1==p2 && (p2=(p1=io)+fread(io,1,1<<21,stdin),p1==p2)?EOF:*p1++)//快读
#define MAX (50000+50)
using namespace std;

struct Node{
	int x,h;
}d[MAX],b[MAX];//d是输入,b用于基数排序

char io[1<<21],*p1=io,*p2=io;//用于快读
int N,D,L=1,R,Q[MAX],T[1<<17],ans[MAX];
//L,R,Q是单调队列，T用于排序，ans用于统计答案。

inline void read(int &a)//快读
{
    register char c=Getchar(); 
    for (a=0; c<'0'||'9'<c; c=Getchar());
    for (; '0'<=c && c<='9'; c=Getchar())
        a=(a<<3)+(a<<1)+(c^48);
}

void Rsort()//基数排序
{
    for (register int i=1; i<=N; i++)
		T[(d[i].x&0xffff)+1]++;
	for (register int i=1; i<=0xffff; i++)
		T[i]+=T[i-1];
	for (register int i=1; i<=N; i++)
		b[++T[(d[i].x&0xffff)]]=d[i];
	memset(T,0,sizeof(T));
	for (register int i=1; i<=N; i++)
		T[(b[i].x>>16)+1]++;
	for (register int i=1; i<=0xffff; i++)
		T[i]+=T[i-1];
	for (register int i=1; i<=N; i++)
		d[++T[(b[i].x>>16)]]=b[i];
}

int main()
{
    read(N); read(D);
	for (register int i=1; i<=N; i++)
		read(d[i].x), read(d[i].h);
	Rsort();//基数排序
	for (register int i=1; i<=N; i++)
	{
		while (L<=R && d[Q[R]].h<d[i].h) R--;//当前的奶牛不够高，出队
		while (L<=R && d[Q[L]].x<d[i].x-D) L++;//最高最靠左的奶牛距离太远，出队
		Q[++R]=i;//现在的奶牛入队
		if (d[Q[L]].h>=(d[i].h<<1)) ans[i]++;//如果最高的牛高于当前的牛2倍则ans++;
	}
	memset(Q,0,N<<2); L=1; R=0;//重置，重新计数
	for (register int i=N; i>=1; i--)
	{//原理同上，符号稍有变动
		while (L<=R && d[Q[R]].h<d[i].h) R--;
		while (L<=R && d[Q[L]].x>d[i].x+D) L++;
		Q[++R]=i;
		if (d[Q[L]].h>=(d[i].h<<1)) ans[i]++;//若ans为2则该奶牛对答案有贡献
	}
	for (register int i=1; i<=N; i++)
		(*ans)+=(ans[i]>>1);//我用ans[0]统计答案（皮）
	printf("%d\n",*ans); return 0;
}
```



---

