# [USACO18OPEN] Out of Sorts S

## 题目描述

留意着农场之外的长期职业生涯的可能性，奶牛 Bessie 开始在不同的在线编程网站上学习算法。

她到目前为止最喜欢的算法是“冒泡排序”。这是 Bessie 的对长度为 $N$ 的数组 $A$ 进行排序的奶牛码实现。

```
sorted = false
while (not sorted):
   sorted = true
   moo
   for i = 0 to N-2:
      if A[i+1] < A[i]:
         swap A[i], A[i+1]
         sorted = false
```
显然，奶牛码中的“moo”指令的作用只是输出“moo”。奇怪的是，Bessie 看上去执着于在她的代码中的不同位置使用这个语句。

给定一个输入数组，请预测 Bessie 的代码会输出多少次“moo”。

## 说明/提示

供题：Brian Dean

## 样例 #1

### 输入

```
5
1
5
3
8
2```

### 输出

```
4
```

# 题解

## 作者：t14Zack (赞：36)

好吧，我承认这题我开始想简单了  
我直接按照伪代码改过来的，结果只过了可怜的5个点……  
错误代码：  
```cpp
#include <cstdio>
int a[100010];
int main() {
    int n, t, ans = 0;
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    bool sorted = false;
    while(sorted == false) {
        sorted = true;
        ans++;
        for (int i = 0; i <= n-2; i++)
            if(a[i+1] < a[i])
                t = a[i+1], a[i+1] = a[i], a[i] = t, sorted = false;
    }
    printf("%d\n", ans);
    return 0;
}
```  
  
这题我们应该自己把输出moo的次数算出来，而不能直接用它给的伪代码。  
那我们就用样例1 5 3 8 2来说明自己如何找出moo的次数：  
1 3 5 2 8  
1 3 2 5 8  
1 2 3 5 8  
1 2 3 5 8  
我们发现，2向左移的最多。  
再举几个例子 1 9 5 8 3 2：  
1 5 8 3 2 9  
1 5 3 2 8 9  
1 3 2 5 8 9  
1 2 3 5 8 9  
2向左移的最多。   
再如：9 1 3 7 2：  
1 3 7 2 9  
1 3 2 7 9  
1 2 3 7 9  
1 2 3 7 9  
1在向左移，但2向左移的最多。   
从这几个例子中，我们可以发现： _ moo的次数就是往左移的最多的次数_ **+1**。  
如：9 1 3 7 2中，1左移了1个，而2左移了了3个，结果就是3+1=4次。  
为什么要+1呢？**因为添加1来说明排序时进行代码中的最后一次迭代**，也就是我每次最后写2次排好序的序列的原因。  
我们可以再用样例来说明一下怎样算出向左移的最多的个数:  
1 5 3 8 2  
转换成：  
0 1 2 3 4  
接着排序，2个序列为：  
1 2 3 5 8  
0 4 2 1 3  
设第2个数组为a，max{a-当前位置}  就是向上冒的最多的了，最后再+1就行了。  
上代码：  
```cpp
#include <cstdio>
#include <algorithm>
struct node {
	int in;
	int zhi;
} a[100000];
bool cmp (const node &a, const node &b) {
	return a.zhi < b.zhi || (a.zhi == b.zhi && a.in < b.in);
}
int max(int a, int b) {return a < b ? b : a;}
int main() {
	int n, ans = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i].zhi), a[i].in = i;
	std::sort(a, a+n, cmp);
	for (int j = 0; j < n; j++)
		ans = max(ans, a[j].in-j);
	printf("%d\n", ans+1);
}
```

---

## 作者：ljc20020730 (赞：32)

对于这道题目的本质，多数题解没有给出说明。

本题求出冒泡排序需要几趟。

考虑一次冒泡排序的交换，减小对应1个位子上的1个逆序对。

但是对于每一个位子所需要减小的逆序对数量是不一样的。

对于每一趟，消去每一个位子上1个逆序对
。
所以趟数就是每个位子上的数产生逆序对数的最大值。

最后的+1指的是即使上一次已经消除所有逆序对了，我们并不知道数组有序了，所以判断最后一遍查看是否有序。

考虑树状数组维护$O(n log_2 n)$

**诚然，本题是一个结论题，请不要使用“举例法”证明结论正确性。**

和善的树状数组代码如下：

```
# include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int a[N],tmp[N],c[N];
int n,T;
void update(int x){for (;x<=n;x+=x&-x)c[x]++;}
int query(int x){int ret=0;for (;x;x-=x&-x) ret+=c[x];return ret;}
int main()
{
	scanf("%d",&n); tmp[0]=n;
	for (int i=1;i<=n;i++) scanf("%d",&a[i]),tmp[i]=a[i];
	sort(tmp+1,tmp+tmp[0]+1);
	T=unique(tmp+1,tmp+1+tmp[0])-tmp-1;
	int ans=0;
	for (int i=1;i<=n;i++) {
		int w=lower_bound(tmp+1,tmp+1+T,a[i])-tmp;
		update(w);
		ans=max(i-query(w),ans);
	}
	printf("%d\n",ans+1);
	return 0;
}
```

---

## 作者：hs_black (赞：14)

### [博客](https://www.luogu.org/blog/hs-black/mao-pao-pai-xu-shen-ru-li-xie)内食用效果更佳

题意即进行多少次冒泡排序

对于一个序列, 我们称之为有序的, 当且仅当对于任意一个位置前面没有比它大的数(可以模拟一下)

对于冒泡排序有一个小性质: 每一次都会把序列未排好序的最大数"沉底", 即推到序列尾部

比如:6 1 2 3 4 5 进行一次为 1 2 3 4 5 6

那么对于位置i, 冒泡排序进行到i-1时, $a_{i-1}$为前i1个数中最大的一个, 如果它大于$a_i$那么它就会到$a_i$的后面

由此可推知, 每一次位置i前都会将一个比$a_i$大的数推至其后, 直至没有比它大的

那么我们对每位置求一下它前面有几个比它大就好啦(注意要将答案加一)

具体来说先进行离散化, 再树状数组求解即可

代码:

```c++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 100500;
int d[N], n;
int read(void) {
	int x = 0;
	char c = getchar();
	while (!isdigit(c)) c = getchar();
	while (isdigit(c)){
		x = (x << 3) + (x << 1) + c - '0';
		c = getchar();
	}
	return x;
}
struct node{
	int val, pos;
	bool operator < (const node &i) const{
		if (val == i.val) return pos < i.pos;
		return val < i.val;
	}
}p[N];
inline int low(int x) {
	return x & -x;
}
int get(int x) {
	int tmp = 0;
	for (;x;x -= low(x)) tmp += d[x];
	return tmp;
}
void add(int x) {
	for (;x <= n; x += low(x)) d[x]++;
}
bool cmp(node i,node j) {
	return i.pos < j.pos;
}
int main() {
	n = read();
	for (int i = 1;i <= n; i++) p[i] = (node){read(),i};
	sort(p + 1,p + n + 1);
	for (int i = 1;i <= n; i++) p[i].val = i;
	sort(p + 1,p + n + 1, cmp);
	int ans = 0;
	for (int i = 1;i <= n; i++) {
		add(p[i].val);
		ans = max(ans, i - get(p[i].val));
	}
	printf ("%d\n", ans+1);
	return 0;
}
```



---

## 作者：zjjws (赞：11)

操作为：从前往后找到第一个不符合排序的数，将它往后移动直到遇到一个比它大的数停止。然后从这个比它大的数为起点开始，重复上述操作

也就是说，这个操作每次可以将这段区间看成 $k$ 段，每一段如以下形式：

$$x_1,x_2,x_3,\dots,x_{i-1},x_i,x_{i+1},\dots,x_j$$

满足：

$\begin{cases}\forall p\in[1,i-1],x_p\le x_{p+1}\\\forall p\in[i+1,j],x_p<x_i \end{cases}$

那么这个 $x_i$ 就会被移动到 $j+1$ 的位置。

如何更简便地表示呢？

设 $r_i$ 表示 $x_i$ 后面第一个大于自己的数的下标 $-i-1$，则如果满足：

$$\forall p\in[1,i-1],r_p=0$$

则 $x_i$ 这个数往后**飞跃** $r_i$ 的距离，举个例子，序列变化一次如下：

$$1,2,3,4,5,4,2,3,1,7,8$$

$$1,2,3,4,4,2,3,1,5,7,8$$

考虑这个操作过后， $r$ 数组的变化，先再放一遍刚刚的序列：

$$x_1,x_2,x_3,\dots,x_{i-1},x_i,x_{i+1},\dots,x_j$$

$x_{i-1}$ 对应的飞跃值要重新计算，$x_i$ 飞跃完以后飞跃值 $r$ 变成 $0$。


$$1,2,3,4,4,2,3,1,5,7,8$$


$$1,1,2,3,4,4,2,3,5,7,8$$

可是**重新计算**这个部分很明显吃不消，我们现在转换一个视角，从每个数的角度去看。

设有一次操作，**飞跃点**分别为 $x_1,x_2,\dots x_k$。

由前面我们知道，各个飞跃点的**起点终点构成的区间**是互不相交的（因为下一个飞跃点是从当前飞跃点的终点 $+1$ 的位置开始找的，还没理解的话 $\dots$ 再看看前面吧），且飞跃点满足点权递增。


设每个飞跃点的终点分别为 $y_1,y_2,\dots,y_k$，设下标为 $i$ 点的权值表示为 $f(i)$

![](https://cdn.luogu.com.cn/upload/image_hosting/i5bsdano.png)

如上图，我们可以知道写出一些真命题：

$\begin{cases}\forall i\in[1,k],p\in(x_i,y_i],f(p)<f(x_i)\\\forall i\in[0,k),p\in[y_i,x_{i+1}),f(p)\le f(p+1) \end{cases}$

其中 $y_0=1$。

那么就很容易看出来了，对于每个非飞跃点来说：

$\operatorname A:$ 它在某个区间内，此时和它有关的逆序对减少一个，逆序对总个数 $-1$。

$\operatorname B:$ 它不在某个区间内，此时易证，它前面已经没有比它权值大的点了。

包括每个飞跃点，我们也可以将它看作不在区间内，因为它们也满足前面没有权值比它大的点。

那么每次操作就是，对于点 $x$，如果 $\exists i\in[1,x),f(i)>f(x)$ ，则 $x$ 的逆序对个数 $-1$。

注：这句话中的逆序对指的是当前点 $x$ 和 **前面**的所有点组成的逆序对，下面也这样简略表示。

那么考虑每个点，它和前面组成的逆序对个数，找到一个最大值就是最终的答案。

当然不能 $n^2$ 暴力跑，值域 $10^9$ 的话如果要用树状数组需要离散化，当然上归并排序应该也没问题。

树状数组（开 $\operatorname O(2)$ 的话 $91$ms ）：

```cpp
#include <bits/stdc++.h>
#define LL long long
#define max(a,b) a>b?a:b
using namespace std;
const int MAX=1e5+3;
struct milk
{
    int s,num;
}a[MAX];
int b[MAX];
int s[MAX];
int nam;
inline int lowbit(int x){return x&(-x);}
inline int cheak(int x)
{
    int sum=0;
    for(int i=x;i>0;i-=lowbit(i))sum+=s[i];
    return sum;
}
inline void add(int x)
{
    for(int i=x;i<=nam;i+=lowbit(i))s[i]++;
    return;
}
inline bool myru(milk x,milk y){return x.s>y.s;}
LL rin()
{
    LL s=0;
    char c=getchar();
    bool bj=0;
    for(;(c>'9'||c<'0')&&c!='-';c=getchar());
    if(c=='-')c=getchar(),bj=true;
    for(;c>='0'&&c<='9';c=getchar())s=(s<<1)+(s<<3)+(c^'0');
    if(bj)return -s;
    return s;
}
int main()
{
    int i,j;
    int n=rin();
    for(i=1;i<=n;i++)a[i].s=rin(),a[i].num=i;
    sort(a+1,a+n+1,myru);
    for(i=1;i<=n;i=j+1)
    {
        nam++;
        for(j=i;j<n&&a[j+1].s==a[i].s;j++)b[a[j+1].num]=nam;
        b[a[i].num]=nam;
    }
    int ans=0;
    for(i=1;i<=n;i++)ans=max(ans,cheak(b[i]-1)),add(b[i]);
    printf("%d",ans+1);
    return 0;
}
```


归并（开 $\operatorname O(2)$ 的话 $96$ms ）：

```cpp
#include <bits/stdc++.h>
#define LL long long
#define max(a,b) a>b?a:b
using namespace std;
const int MAX=1e5+3;
int a[MAX];
int b[MAX];
int s[MAX];
int sum[MAX];
inline void bing(int l,int r)
{
    if(l==r)return;
    int mid=(l+r)>>1;
    bing(l,mid);
    bing(mid+1,r);
    int i=l,j=mid+1,k=l;
    for(;i<=mid&&j<=r;k++)
    if(a[i]>a[j])s[k]+=(mid-i+1),s[k]+=sum[j],b[k]=a[j],j++;
    else b[k]=a[i],s[k]+=sum[i],i++;
    for(;i<=mid;i++)b[k]=a[i],k++;
    for(i=l;i<k;i++)a[i]=b[i],sum[i]=s[i],s[i]=0;
    return;
}
LL rin()
{
    LL s=0;
    char c=getchar();
    bool bj=0;
    for(;(c>'9'||c<'0')&&c!='-';c=getchar());
    if(c=='-')c=getchar(),bj=true;
    for(;c>='0'&&c<='9';c=getchar())s=(s<<1)+(s<<3)+(c^'0');
    if(bj)return -s;
    return s;
}
int main()
{
    int i,j;
    int n=rin();
    for(i=1;i<=n;i++)a[i]=rin();
    bing(1,n);
    
    int ans=0;
    for(i=1;i<=n;i++)ans=max(ans,sum[i]);
    printf("%d",ans+1);
    return 0;
}
```


---

## 作者：龙啸空 (赞：6)

解释一下：在最后面的数每趟只能向前走一个数，需要n趟达到自己的位置。
代码为敬：
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int cnt = 0;
struct Node
{
	int id;
	int num;
}ins[1000000];
bool cmp(Node a, Node b)
{
	return a.num < b.num;
}
int main()
{
	cin >> cnt;
	for (int i = 0; i < cnt; i++)
	{
		cin >> ins[i].num;
		ins[i].id = i;
	}
	stable_sort(ins, ins + cnt, cmp);
	int maxn = 0;
	for (int i = 0; i < cnt; i++)
	{
		if(ins[i].id-i>maxn)
			maxn =  ins[i].id - i;
	}
	cout << maxn + 1;
    return 0;
}
```

---

## 作者：liuyanxi2 (赞：5)

嗯，这道题我一开始想简单了，以为就直接套伪代码就过了，然后呢
就10分

所以这道题不能直接套伪代码，要自己算moo了多少次，然而怎么算呢，我们先看样例：

1 5 3 8 2

很显然，经过排序后是这样的：

1 2 3 5 8

冒泡排序的核心就是一个一个地排序到底，所以我们只用分别看没一个点即可

样例是这样的：

1：动了0步

2：动了3步

3：动了0步

5：动了2步

8：动了1步

所以很显然2动的最多，所以ans就是3

如果你这么写，你可以得到100mod10的好成绩

那么为什么呢，**添加1说明排序时进行代码中的最后一次迭代，所以+1是不能少的。
**
但是这道题还有一个坑，就是在排序的时候，如果你是这么写的：

```
bool cmp(cow q,cow w)
{
	return q.num<w.num
}
```

那么你就只有80分了，**因为在这里每个数可能出现多次，所以你要让原位置靠后的排序时靠前。**
正确的排序应该是这样的

```cpp
bool cmp(cow q,cow w)
{
	return q.num<w.num ||(q.num==w.num&&q.id<w.id);
}
```

好了，看满分代码吧：


```
#include<bits/stdc++.h>
using namespace std;
long long b,c[100001],i,j,k,ans,n,m;
struct cow
{
	long long id,num;
}a[100001];
long long lowbit(long long q)
{
	return q&(-q);
}
void upsate(long long q,long long w)
{
	while(q<=n)
	{
		c[q]+=w;
		q+=lowbit(q);
	}
}
long long getsum(long long q)
{
	long long sum=0;
	while(q>0)
	{
		sum+=c[q];
		q-=lowbit(q);
	}
	return sum;
}
bool cmp(cow q,cow w)
{
	return q.num<w.num ||(q.num==w.num&&q.id<w.id);
}
int main ( )
{
//	freopen("P4378_7.in","r",stdin);
	cin>>n;
	for(i=1;i<=n;i++)
	cin>>a[i].num,a[i].id=i;
	sort(a+1,a+n+1,cmp);
//	for(i=1;i<=n;i++)
//	cout<<a[i].num<<' ';
	for(i=1;i<=n;i++)
	ans=max(ans,a[i].id-i);
	cout<<ans+1;
	return 0 ;
}
```


~~本弱第一次写题解，如果有错，请各位大佬指出~~

---

## 作者：HsKr (赞：4)

此题即求$i$与$i+j(i+j<=n)$造成的逆序对数量的最大值+1（最后的while循环还要再查一遍）。

众所周知，逆序对可以使用树状数组来做。

此中需要使用离散化，简单介绍一下：

```1,233,666,114514,66662333,2147483647```这几个数，也可以用```1,2,3,4,5,6```来表示，这样做其中的大小关系不变，原来的逆序对还是逆序对，原来不是的还不是，但是却将需要树状数组的空间缩小了（不然题目要开$10^9$大小的树状数组，肯定MLE了）。

注释代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define int long long
#define lowbit(x) ((x)&(-(x)))
using namespace std;
const int MAXN=500010;
int n,c[MAXN],ans=0,rank[MAXN];
struct node{
	int x,id;
}a[MAXN];
bool cmp(node a,node b){
	if(a.x==b.x) return a.id<b.id;
	return a.x<b.x;
}
void add(int x){//将a[x]++ 
    for(int i=x;i<=n;i+=lowbit(i)){
        c[i]++;
    }
}
int sum(int x){//求a[1...x]，即x前面与x造成顺序对的数量 
    int ret=0;
    for(int i=x;i;i-=lowbit(i)){
        ret+=c[i];
    }
    return ret;
}
bool cmp2(node a,node b){
	return a.id<b.id;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].x;
		a[i].id=i;
	}
	sort(a+1,a+n+1,cmp);//第一次按值排序，记录大小关系 
	for(int i=1;i<=n;i++){//排完序后记录，大小即为当前编号 
		a[i].x=i;
	}
	sort(a+1,a+n+1,cmp2);//第二次按值（离散化后的）排序 
	for(int i=1;i<=n;i++){//值大的肯定先插入进去，前面的一定是顺序对 
		add(a[i].x);//插入树状数组 
		ans=max(ans,i-sum(a[i].x));//求本组能造成多少逆序对，求后面的逆序对等于总数减去前面的顺序对 
	}
	cout<<ans+1<<endl;//+1是因为还要再查一遍 
	return 0;
}
```

---

## 作者：zhengrunzhe (赞：4)

~~我懒得离散化，我就写了个treap~~

题目实质就是求所有数前面比它大的数的个数的最大值+1

$$\max_{i=1}^{i<=n}\left \{\sum_{j<i,a[j]>a[i]}1 \right \}$$

这是个简单二维偏序

然后就写个treap，按顺序插入，每次查treap里有多少个数>x，连离散化都不用
```cpp
#include<cstdio>
#include<cstdlib>
template<class type>inline const type max(const type &a,const type &b)
{
	return a>b?a:b;
}
template<class type>inline const void read(type &in)
{
	in=0;char ch=getchar();bool f=0;
	while (ch<48||ch>57){if (ch=='-')f=1;ch=getchar();}
	while (ch>47&&ch<58)in=(in<<3)+(in<<1)+(ch&15),ch=getchar();
	if (f)in=-in;
}
const int N=1e5+10;
class Treap
{
	private:
		struct tree
		{
			int size,priority,cnt,key;
			tree *son[2];
			inline const void pushup()
			{
				size=son[0]->size+cnt+son[1]->size;
			}
		}*root,memory_pool[N],*tail,*null;
		inline const void init()
		{
			tail=memory_pool;
			null=tail++;
			root=null->son[0]=null->son[1]=null;
		}
		inline tree *spawn(int key)
		{
			tree *p=tail++;
			p->key=key;
			p->size=p->cnt=1;
			p->priority=rand();
			p->son[0]=p->son[1]=null;
			return p;
		}
		inline const void rotate(tree *&fa,const bool f)
		{
			tree *p=fa->son[f];
			fa->son[f]=p->son[f^1];
			p->son[f^1]=fa;
			fa->pushup();(fa=p)->pushup();
		}
		inline const void insert(tree *&p,int key)
		{
			if (p==null)return p=spawn(key),void();
			if (p->key==key)return p->cnt++,p->pushup();
			bool f=p->key<key;
			insert(p->son[f],key);
			p->pushup();
			if (p->son[f]->priority>p->priority)rotate(p,f);
		}
		inline const int greater(tree *p,const int key)
		{
			if (p==null)return 0;
			if (p->key==key)return p->son[1]->size;
			if (key>p->key)return greater(p->son[1],key);
			return greater(p->son[0],key)+p->son[1]->size+p->cnt;
		}
	public:
		inline Treap(){init();}
		inline const void insert(int x)
		{
			insert(root,x);
		}
		inline const int greater(int x)
		{
			return greater(root,x);
		}
}T;
int n,ans;
int main()
{
	read(n);
	for (int x;n--;)
		read(x),
		T.insert(x),
		ans=max(T.greater(x),ans);
	printf("%d\n",ans+1);
	return 0;
}
```

---

## 作者：Jyf624761709 (赞：3)

	这题楼上大佬都用排序过的(orz),本蒟蒻写了一个树状数组，其实思路本质差不多。

**思路**：用树状数组记录一个数前有多少个大于它的数(设数量为t)，因为前面这些大的数肯定会跑到当前数的后面，且只有这些数会跑到当前数的后面，所以这个点肯定只会被更新t次。而冒泡排序会在所有数都被更新完后停止，所以只要在所有的t中取最大值就是答案了。

-----------------------------------------------分割线--------------------------------------------------

贴上蒟蒻的代码:
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
#include<map>
#include<set>
#include<cmath>
typedef long long ll;
using namespace std;
const int inf=2147483647;
const int ine=-2147482647;
#define m(a) memset(a,0,sizeof(a))
#define I inline
#define R register
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define lb(x) (x&-x)
#define gc() getchar()
#define EL putchar(10)
#define SP putchar(32)
//char ss[1<<17],*A=ss,*B=ss;I char gc(){return A==B&&(B=(A=ss)+fread(ss,1,1<<17,stdin),A==B)?EOF:*A++;}
template <typename _Tp> I void _(_Tp &x);
template <typename _Tq> I void wr(_Tq x);
I ll mx(ll a,ll b){return a>b?a:b;}I int mn(int a,int b){return a<b?a:b;}
map<int,int>p;
int n,a[100010],t[100010],m;
ll tr[100010],ans;
I void update(int x){
    while(x<=m) ++tr[x],x+=lb(x);
}
//记录每个数出现次数
I ll query(int x){
    R ll s=0;
    while(x>0) s+=tr[x],x-=lb(x);
    return s;
}
int main(){
    _(n);
    for(R int i=1;i<=n;++i)
        _(a[i]),t[i]=a[i];//_()是读入
    sort(t+1,t+1+n);
    m=unique(t+1,t+1+n)-t-1;
    for(R int i=1;i<=m;++i)
        p[t[i]]=i;
    for(R int i=1;i<=n;++i) a[i]=p[a[i]];
    /*因为最大的数会达到1e9，所以要离散化一下*/
    update(a[1]);
    for(R int i=2;i<=n;++i){
        update(a[i]);
        ans=mx(ans,query(m)-query(a[i]));
        /*之前比它大的数的数量*/
    }
    wr(ans+1);
    return 0;
}
template <typename _Tp>
  I void _(_Tp &x){
      _Tp w=1;char c=0;x=0;
      while (c^45&&(c<48||c>57)) c=gc();
      if (c==45) w=-1, c=gc();
      while(c>=48&&c<=57) x=(x<<1)+(x<<3)+(c^48),c=gc();
      x*=w;
  }
template <typename _Tq>
    I void wr(_Tq x){
        if(x<0)
            putchar(45),x=-x;
        if(x<10){
            putchar(x+48);
            return;
        }
        wr(x/10);
        putchar(x%10+48);
    }

```

---

## 作者：キリ卜 (赞：3)

冒泡排序，是一种较简单的排序方法，就是重复地走访过要排序的元素列，依次比较两个相邻的元素，如果他们的顺序（如从大到小、首字母从A到Z）错误就把他们交换过来。

Bessie的代码翻译后即为：
```cpp
sorted=0;
while(sorted==0){
	sorted=1;
	printf("moo");
	for (int i=0;i<=n-2;i++)
   if(A[i+1]<A[i])
	swap(A[i],A[i+1]),sorted = false;
}
```
转化后应该非常容易懂了，虽说这个算法比较简单，但效率就不怎么样了。
必须是不断刷，事件复杂度取决于不同的情况了。

1 , 5 , 3 , 8 , 2 --------[ 初始数组 ]

1 , 3 , 5 , 2 , 8 --------------------[ 1 ]

1 , 3 , 2 , 5 , 8 --------------------[ 2 ]

1 , 2 , 3 , 5 , 8 --------------------[ 3 ]

1 , 2 , 3 , 5 , 8 --------------------[ 4 ]

通过观察样例及自己举的例子（这里就不多举例了），我们发现了一个规律，那就是，输出 moo 的次数等于修改最多次的那个数的修改次数+1，为啥要+1呢？因为在最后一次修改后，sorted 的值依然是 0 .所以要再刷一次。

那么输出 moo 的次数清楚了，题目就好解决了：

```cpp
#include<bits/stdc++.h>
using namespace std;
int ans=-1,n;
struct MOO{
    int x,id;
    bool operator <(const MOO b)const{return x<b.x||(x==b.x&&id<b.id);}
}a[100005];
inline int read(){
    int ret=0,f=1;
    char ch=getchar ();
    while (!isdigit(ch)){
        if (ch=='-') f=-f;
        ch=getchar();
    }
    while (isdigit(ch))
    ret=(ret<<1)+(ret<<3)+ch-'0',ch=getchar();
    return ret*f;
}
int main(){
//    freopen("moo.in","r",stdin);
//    freopen("moo.out","w",stdout);
    n=read();
    for (int i=1;i<=n;i++) a[i].x=read(),a[i].id=i;
    sort(a+1,a+1+n);
    for (int i=1;i<=n;i++) ans=max(ans,a[i].id-i);
    printf("%d\n",ans+1);
    return 0;
}
```


---

## 作者：封禁用户 (赞：1)

这道题很容易想到用树状数组的逆序对做,但是需要离散化。做这道题之前可以先做一做[P1908](https://www.luogu.com.cn/problem/P1908),不懂逆序对离散化的可以上网搜。

逆序对的离散化有两点需要注意:一是要排序;二是要去重(不去重的话#$7$会WA ~~我在这被卡了好久~~ )

具体注释见代码:

```cpp
#include<bits/stdc++.h>
//#define chenkeqi return
//#define AK 0
//#define PJz ;
using namespace std;
long long m,n,ans,c[100005];
struct edge
{
	long long a,id,id1;
}e[100005];//定义结构体,逆序对的离散化需要
long long lowbit(long long x)
{
	return x&(-x);
}
void adde(long long pos)
{
	for(long long i=pos;i<=n;i+=lowbit(i))
		c[i]++;
}
long long q(long long pos)
{
	long long ans=0;
	for(long long i=pos;i>=1;i-=lowbit(i))
		ans=ans+c[i];
	return ans;
}//以上是树状数组的模板
bool cmp1(const edge &a,const edge &b)
{
	if(a.a!=b.a)
		return a.a<b.a;
	else
		return a.id<b.id;
}//第一次排序,注意去重
bool cmp2(const edge &a,const edge &b)
{
	return a.id<b.id;
}//第二次排序就不需要去重了,因为已经没有重复的值了
int main()
{
	scanf("%lld",&n);
	for(long long i=1;i<=n;i++)
	{
		scanf("%lld",&e[i].a);
		e[i].id=i;
	}
	sort(e+1,e+n+1,cmp1);//离散化前的排序
	for(long long i=1;i<=n;i++)
		e[i].id1=i;//现在的e[i].id1相当于之前的e[i].a,因为此时e[i].a已经排好序了,这样做可以使空间缩小,然而并不影响后面的操作
	sort(e+1,e+n+1,cmp2);//离散化后的排序
	for(long long i=1;i<=n;i++)
	{
		adde(e[i].id1);//树状数组基本操作:建立树状数组
		ans=max(ans,i-q(e[i].id1));//能够成多少逆序对,注意取max
	}
	ans++;//ans要加1,因为最后还要循环一遍
	printf("%lld",ans);
	//chenkeqi AK PJz
	return 0;
}

```


---

## 作者：IL杰佣 (赞：0)

这道题归根结底是一道数论题。

首先我来阐述一下题意，有些小伙伴可能对这道题的意思有点蒙，~~不必在意~~他的这个伪代码，~~毕竟这样做要TLE~~。

先把每一个数字看做独立的，冒泡只不过一次一次的比较，而本题的目的就是想求出往前移动次数最多的数字。

题目懂得了，可是代码要怎么实现呢。

先看看数据范围（1<=n<=100,000），嗯。。不大也不小，但最多也只能O(n)了

那我们就来想想，如何在O(n)的复杂度中解决了。

_first：_ 先用结构体定义输入的数字，数字的编号，--以及排序后的编号（其实也不用，只是这样思路更清晰些）

_second：_ 将结构体进行快排（sort），排序后再将id2附上i值，做差再 +1 就可以计算出每一个数字经过冒泡排序的次数了。

这道题其实不难，只是在理解题意上要花一点小小的功夫。

## 代码秀起来(有超详细注释）

------------
```cpp
#include<bits/stdc++.h>
using namespace std;
struct nu	//结构体定义
{
	int x;		//存储每一个输入
	int id1;	//sort 排序前的编号
	int id2;	//sort 排序后的编号
}t[1100000];
int cmp(nu a,nu b)		//注意！！！
{
	if(a.x!=b.x)		//在判定时有可能有相同的数字
	return a.x<b.x;
	return a.id1<b.id1;	//既然数字相同就要判定编号的前后了（最初在这里丢了10分555~）
}
int main()
{
	int n,a,maxn=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>t[i].x;
		t[i].id1=i;		//给 id1 附上编号
	}
	sort(t+1,t+n+1,cmp);		//sort 快排
	for(int i=1;i<=n;i++)
	{
		t[i].id2=i;				//将 id2 附上编号
		a=t[i].id1-t[i].id2;		//a 存储编号差值，既是移动次数
		maxn=max(maxn,a);		//比较最大的移动次数，记录
	}
	cout<<maxn+1;
	return 0;
}
```
如果dalao觉得蒟蒻写的还阔以，可否 _**点赞**_ ~~关注三连~~ _**QWQ**_ 

---

## 作者：OfstAutomataMachine (赞：0)

首先，拿到题目看到冒泡排序我就莫名有心理阴影

我想到了NO**I** **O**NL**I**NE tg的[冒泡排序](https://www.luogu.com.cn/problem/P6186)，又想到了rm1的一黄两紫……

看了一下难度，黄，海星。

进入正题：显而易见，经过手玩样例，可以发现如果没有2从第5位变成第2位，就不是4而是3。

见下图

![](https://cdn.luogu.com.cn/upload/image_hosting/1wi3l061.png)

如果不知道我在说什么鬼，请移步到金组的同名题目。

好了，可以看出，如果 $a_i$ 想挪到第 $j$ 位且 $j<i$ ,那么必须要冒泡 $(i-j)$ 次，答案就是 $(i-j+1)$。

所以，找到所有这样的i，j，求 $(i-j+1)$ 的最大值。

喜闻乐见的代码：
```
#include<bits/stdc++.h>
using namespace std;
struct node{
	int id,num;
} a[100001]; 
bool cmp(node x,node y)
{
	return x.num<y.num||(x.num==y.num&&x.id<y.id);
}
int n,ans;
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout); 
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		a[i].id=i;
		cin>>a[i].num;
	}
	sort(a+1,a+1+n,cmp);
//	for(int i=1;i<=n;i++)
//		cout<<a[i].num;
	for(int i=1;i<=n;i++)
		ans=max(ans,a[i].id-i);
	cout<<ans+1;
	return 0;
}
```


---

