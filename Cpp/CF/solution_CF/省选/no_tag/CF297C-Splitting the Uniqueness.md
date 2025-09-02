# Splitting the Uniqueness

## 题目描述

Polar bears like unique arrays — that is, arrays without repeated elements.

 You have got a unique array $ s $ with length $ n $ containing non-negative integers. Since you are good friends with Alice and Bob, you decide to split the array in two. Precisely, you need to construct two arrays $ a $ and $ b $ that are also of length $ n $ , with the following conditions for all $ i $ $ (1<=i<=n) $ :

- $ a_{i},b_{i} $ are non-negative integers;
- $ s_{i}=a_{i}+b_{i} $ .

Ideally, $ a $ and $ b $ should also be unique arrays. However, life in the Arctic is hard and this is not always possible. Fortunately, Alice and Bob are still happy if their arrays are almost unique. We define an array of length $ n $ to be almost unique, if and only if it can be turned into a unique array by removing no more than ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF297C/c5d8ea1c11ba761a920db324eef984cdbae28ef7.png) entries.

For example, the array $ [1,2,1,3,2] $ is almost unique because after removing the first two entries, it becomes $ [1,3,2] $ . The array $ [1,2,1,3,1,2] $ is not almost unique because we need to remove at least $ 3 $ entries to turn it into a unique array.

So, your task is to split the given unique array $ s $ into two almost unique arrays $ a $ and $ b $ .

## 说明/提示

In the sample, we can remove the first two entries from $ a $ and the second entry from $ b $ to make them both unique.

## 样例 #1

### 输入

```
6
12 5 8 3 11 9
```

### 输出

```
YES
6 2 6 0 2 4
6 3 2 3 9 5```

# 题解

## 作者：Aiopr_2378 (赞：5)

## 题目大意：

给定 $n$ 个互不相同的非负整数数列 $s$ 。构造两个非负整数数列 $a$ 与 $b$。使得 $a_i+b_i=s_i$。使得每个数列最多有 $\left\lfloor\dfrac{S}{3}\right\rfloor$ 个数重复。

其中，$n\leq10^5\;,\;0\leq s_i\leq10^9$。

## 构造方法：

我们分成三段考虑问题。我们的目标是至多让 $\left\lfloor\dfrac{S}{3}\right\rfloor$ 个数重复。我们可以按照如下方法构造：

将 $s[i]$ 按照数值大小排序后，设 $k=\left\lceil\dfrac{S}{3}\right\rceil$，

- 对于第一段，即 $1\leq i\leq k$时，我们构造

$$a_i=i-1$$

$$b_i=s_i-a_i$$

- 对于第二段，即 $k+1\leq i\leq n-k$ 时，我们构造

$$b_i=i-1$$

$$a_i=s_i-b_i$$

- 对于第三段，即 $n-k+1\leq i\leq n$ 时，我们构造

$$b_i=n-i$$

$$a_i=s_i-b_i$$

如果上面的形式不直观，可以看下面的图片辅助理解。

红色表示 $a_i$，蓝色表示 $b_i$，可以看到，最多有 $\left\lfloor\dfrac{S}{3}\right\rfloor$ 个重复。

![](https://cdn.luogu.com.cn/upload/image_hosting/jluomc4n.png)

## 参考代码：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
#define MAXN 100005
struct node{
    int a,b,c,id;
}s[MAXN];
int n;
bool cmp(node x,node y){
    return x.a<y.a;
}
bool cmp2(node x,node y){
    return x.id<y.id;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>s[i].a;
        s[i].id=i;
    }
    sort(s+1,s+1+n,cmp);
    int t=n/3+(n%3!=0);
    for(int i=1;i<=t;i++){
        s[i].b=i-1;
        s[i].c=s[i].a-s[i].b;
    }
    for(int i=t+1;i<=n-t;i++){
        s[i].c=i-1;
        s[i].b=s[i].a-s[i].c;
    }
    for(int i=n-t+1;i<=n;i++){
        s[i].c=n-i;
        s[i].b=s[i].a-s[i].c;
    }
    sort(s+1,s+1+n,cmp2);
    puts("YES");
    for(int i=1;i<=n;i++) cout<<s[i].b<<" ";
    puts("");
    for(int i=1;i<=n;i++) cout<<s[i].c<<" ";
    return 0;
}
```


---

## 作者：AsunderSquall (赞：3)

闲得无聊想做构造，然后 xyf 就给我推了这道题，来水一篇题解。  

## 题意  
给一个互不相同的非负整数序列 $\{s_n\}$，让你构造非负整数序列 $\{a_n\},\{b_n\}$，$s.t. \ s_i=a_i+b_i$，$a$ 序列和 $b$ 序列里都至少有 $\left \lfloor \dfrac {2n} 3 \right \rfloor$ 个互不相同的数。  

## 题解  
我们把 $n$ 补全成 $3$ 的倍数方便讨论，设 $n=3k$。  
首先我们考虑 $s_i=i-1$ 该怎么做。  

理性感觉一下，我们想要把 $\left \lceil \dfrac {n} 3 \right \rceil$ 的相同的数给用满，比如说，都是 0。  

稍微手玩一下可以玩出这个构造方案：  
$$a[1]\text{\textasciitilde} a[k]=0$$
$$b[1]\text{\textasciitilde} b[k]=0,1,\cdots k-1 $$
$$a[k+1]\text{\textasciitilde} a[2k]=k ,k+1,\cdots 2k-1$$
$$b[k+1]\text{\textasciitilde} b[2k]=0$$
$$a[2k+1]\text{\textasciitilde} a[3k]=k-1,k-2,k-3 \cdots 0$$
$$b[2k+1]\text{\textasciitilde} b[3k]=k+1,k+3,k+5 \cdots 3k-1$$   

这个方案是合法的。  

那么我们拓展到一般情况，先把 $\{s_n\}$ 排序。  
我们注意到钦定一些数为 0 的实际作用是让这些位置的另外一个数组不重复，而且全部都是 $0$ 都是重复的数（**指和其他位置选的数字重复，如 $a[3k]=0$ 和 $b[1]=0$**），不会变得更劣了。  
那么我们有 $s_i\ge i-1$，所以把另外一个数组按照原来那样放，原来钦定 0 的数组变成差值，一定不会变劣。

$$b[1]\text{\textasciitilde} b[k]=0,1,\cdots k-1 $$
$$a[1]\text{\textasciitilde} a[k]=s[i]-b[i]$$
$$a[k+1]\text{\textasciitilde} a[2k]=k ,k+1,\cdots 2k-1$$
$$b[k+1]\text{\textasciitilde} b[2k]=s[i]-a[i]$$  

至于最后 $k$ 个数，我们继续沿用原来的 $a$，可以证明这是对的，下面给出证明：  
$$a[2k+1]\text{\textasciitilde} a[3k]=k-1,k-2,k-3 \cdots 0$$
$$b[2k+1]\text{\textasciitilde} b[3k]=s[i]-b[i]$$   
首先，显然 $a[k+1]\text{\textasciitilde} a[3k]$ 已经有 $2k$ 个不同的数了，所以 $\{a\}$ 满足题意。  
然后 $a[2k+1]\text{\textasciitilde} a[3k]$ 递减，而 $s[2k+1]\text{\textasciitilde} s[3k]$ 递增，所以 $b[2k+1]\text{\textasciitilde} b[3k]$ 必然递增。  
最后 $b[2k+1]\ge 2k-(k-1)=k+1>k-1$  
所以 $b[1]\text{\textasciitilde} b[k],b[2k+1]\text{\textasciitilde} b[3k]$ 互不重复。  

代码：  
```cpp
int n,m;
int a[N],b[N];
struct Node{int x,id;}s[N];
bool cmp(Node x,Node y){return x.x<y.x;}
signed main()
{
	rd(n);for (int i=1;i<=n;i++) rd(s[i].x),s[i].id=i;m=n;
	sort(s+1,s+n+1,cmp);
	if (n%3==1) s[++n].x=s[n-1].x+1;
	if (n%3==2) s[++n].x=s[n-1].x+1;
	int k=n/3;
	for (int i=1;i<=k;i++) b[s[i].id]=i-1,a[s[i].id]=s[i].x-b[s[i].id];
	for (int i=k+1;i<=2*k;i++) a[s[i].id]=i-1,b[s[i].id]=s[i].x-a[s[i].id];
	for (int i=2*k+1;i<=3*k;i++) a[s[i].id]=3*k-i,b[s[i].id]=s[i].x-a[s[i].id];
	puts("YES");
	for (int i=1;i<=m;i++) cout<<a[i]<<" ";cout<<endl;
	for (int i=1;i<=m;i++) cout<<b[i]<<" ";
}
```

---

## 作者：Mevinsp (赞：3)

构造！

## 题意

给你一个元素互不相同的序列 $s$，让你给出序列 $a$，$b$ 使得 $a_i + b_i = s_i$，并且 $a$ 序列和 $b$ 序列中各有 $\left\lfloor\dfrac{2n}{3}\right\rfloor$ 个不同的元素。

## 题解

看到这一题，第一反应是取 $a_i = s_i,b_i = 0$，可惜第二眼就看到了
>一个数列S被称为近似不同当且仅当可以移去不超过S/3上取整后互不相同。

（即 $a$ 序列和 $b$ 序列中各有 $\left\lfloor\dfrac{2n}{3}\right\rfloor$ 个不同的元素。）

那么还是老老实实构造吧（

由题意， 我们要将每个 $s[i]$ 分成两段，一段给 $a[i]$，一段给 $b[i]$。

那么我们先将 $s$ 从小到大排个序。

由于我们要让 $\left\lfloor\dfrac{2n}{3}\right\rfloor$ 个元素是不同的，那么不妨将 $s$ 分为三段，设 $k = \left\lceil\dfrac{n}{3}\right\rceil$。

1. $1 \leqslant i\leqslant k$

	由题意，$s$中的元素是互不相同的。所以我们不妨让
    
    $a_i=i$
    
    $b_i=s_i-a_i$
    
   这样就可以保证这一段内的 $a$ 与 $b$ 各自互不相同。
  
2. $k+1 \leqslant i\leqslant n-k$

	类似上面，我们构造
    
    $b_i=i$
    
    $a_i=s_i-b_i$
    
   这样也可以保证这一段内的 $a$ 与 $b$ 各自互不相同。
   
3. $n-k+1 \leqslant i\leqslant n$

	对于这一段，如果我们还是按照前面一样，就有可能出现不符合 $a$ 序列和 $b$ 序列中各有 $\left\lfloor\dfrac{2n}{3}\right\rfloor$ 个不同的元素的条件。所以我们这样构造：
    
    $b_i=n-i$
    
    $a_i=s_i-b_i$
    
    可以保证其正确性。
    
那么这样也就构造完毕了。

由于最后顺序要排回来，所以用到了结构体。

## 参考代码

```
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5; 
int t,n;
struct Node {
	int s,a,b,x;
}k[N];
bool cmp1(Node p,Node q) {
	return p.s<q.s;
}
bool cmp2(Node p,Node q) {
    return p.x<q.x;
}
int main() {
	scanf("%d",&n);
	if(n%3!=0)
		t=n/3+1;
	else
		t=n/3;
	for(int i=1;i<=n;i++)
		scanf("%d",&k[i].s);
	for(int i=1;i<=n;i++)
		k[i].x=i; 
	sort(k+1,k+n+1,cmp1);
	for(int i=1;i<=t;i++) {
		k[i].a=i-1;
		k[i].b=k[i].s-k[i].a;
	}
	for(int i=t+1;i<=n-t;i++) {
		k[i].b=i-1;
		k[i].a=k[i].s-k[i].b;
	}
	for(int i=n-t+1;i<=n;i++) {
		k[i].b=n-i;
		k[i].a=k[i].s-k[i].b;
	}
	sort(k+1,k+1+n,cmp2);
	puts("YES");
	for(int i=1;i<=n;i++)
		printf("%d ",k[i].a);
	puts("");
	for(int i=1;i<=n;i++)
		printf("%d ",k[i].b);
	return 0;
}
```


---

## 作者：tuyongle (赞：3)

此题考虑直接构造出数列：

令T为n/3上取整（n为序列长度） 

s[i].val记录值，s[i].num记录下标，后将s数组排序

对于1<=i<=T，

构造a[i].num=b[i].num=s[i].num，

a[i].val=i-1,b[i].val=s[i].val-a[i].val

对于T+1<=i<=n-T，

构造a[i].num=b[i].num=s[i].num，

b[i].val=i-1,a[i].val=s[i].val-b[i].val

对于n-T+1<=i<=n，

构造a[i].num=b[i].num=s[i].num，

b[i].val=n-i,a[i].val=s[i].val-b[i].val

将a[i]，b[i]按num排一遍序即可

显然，a与b满足题意（a[T+1]~a[n]互不相等，b[T+1]~b[n-T+1]也互不相等）

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int MXn=1000010;
struct stru{int val,num;}s[MXn],a[MXn],b[MXn];
int n;
bool cmp1(const stru &x,const stru &y){
    return x.val<y.val;
}
bool cmp2(const stru &x,const stru &y){
    return x.num<y.num;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    scanf("%d",&s[i].val),s[i].num=i;
    sort(s+1,s+n+1,cmp1);
    int T=(n%3)?n/3+1:n/3;
    for(int i=1;i<=T;++i){
        a[i].num=b[i].num=s[i].num;
        a[i].val=i-1,b[i].val=s[i].val-a[i].val;
    }
    for(int i=T+1;i<=n-T;++i){
        a[i].num=b[i].num=s[i].num;
        b[i].val=i-1,a[i].val=s[i].val-b[i].val;
    }
    for(int i=n-T+1;i<=n;++i){
        a[i].num=b[i].num=s[i].num;
        b[i].val=n-i,a[i].val=s[i].val-b[i].val;
    }
    sort(a+1,a+n+1,cmp2);
    sort(b+1,b+n+1,cmp2);
    printf("YES\n");
    for(int i=1;i<=n;++i)
    printf("%d%c",a[i].val,i==n?'\n':' ');
    for(int i=1;i<=n;++i)
    printf("%d%c",b[i].val,i==n?'\n':' ');
    return 0;
}
```



---

## 作者：scp020 (赞：1)

# CF297C Splitting the Uniqueness 题解

非常好构造题，使我的草稿纸旋转。

## 解法

我们记输入的数组为 $a$，需要输出的两个数组为 $b,c$（因为当时起变量名起的）。

考虑利用 $a_i$ 互不相同的性质。

先将 $a_i$ 升序排序。因为题中保证 $a_i$ 互不相同，所以相邻两数的差至少为 $1$，从而 $a_i \ge i - 1$。

考虑到最多有 $\lceil \dfrac{n}{3} \rceil$ 个重复数字，即为需要至少有 $\lfloor \dfrac{2n}{3} \rfloor$ 种不同数字。我们可以将整个数组等分为 $3$ 段，分别是 $[1,\lfloor \dfrac{n}{3} \rfloor ]$，$(\lfloor \dfrac{n}{3} \rfloor,\lfloor \dfrac{2n}{3} \rfloor]$，$(\lfloor \dfrac{2n}{3} \rfloor,n]$。具体构造如下图。

![图片](https://cdn.luogu.com.cn/upload/image_hosting/qhimb2ko.png)

为什么这么构造是对的？

显然对于 $c$ 数组，第二段和第三段的数互不相同，满足至少有 $\lfloor \dfrac{2n}{3} \rfloor$ 种不同数字。考虑为什么 $b$ 数组至少有 $\lfloor \dfrac{2n}{3} \rfloor$ 种不同数字。

观察第一段和第三段，因为 $a_i \ge i-1$，所以第三段的第一个 $a_i$ 满足 $a_i \ge \dfrac{2n}{3}$，而 $n - \lfloor \dfrac{2n}{3} \rfloor -1 = \lceil \dfrac{n}{3} \rceil - 1$，所以 $c_i$ 满足 $c_i \ge \dfrac{n}{3}$，而在第三段 $a$ 单调上升，$c$ 单调下降，所以 $b$ 单调上升，所以 $b$ 数组在第一段和第三段互不相同。

## 代码

```cpp
#include<bits/stdc++.h>
namespace fast_IO
{
    /**
     * 没啥用的快读快写
    */
};
using namespace fast_IO;
int n,b[100010],c[100010],fir,sec;
struct node
{
    int val,ord;
    inline bool operator<(const node rhs) const
    {
        return val<rhs.val;
    }
};
node a[100010];
int main()
{
    in>>n,fir=n/3,sec=n*2/3;
    for(int i=1;i<=n;i++) in>>a[i].val,a[i].ord=i;
    std::sort(a+1,a+n+1);
    for(int i=1;i<=fir;i++) b[a[i].ord]=i-1,c[a[i].ord]=a[i].val-b[a[i].ord];
    for(int i=fir+1;i<=sec;i++) c[a[i].ord]=i-1,b[a[i].ord]=a[i].val-c[a[i].ord];
    for(int i=n;i>sec;i--) c[a[i].ord]=n-i,b[a[i].ord]=a[i].val-c[a[i].ord];
    out<<"YES\n";
    for(int i=1;i<=n;i++) out<<b[i]<<' ';
    out<<'\n';
    for(int i=1;i<=n;i++) out<<c[i]<<' ';
    fwrite(Ouf,1,p3-Ouf,stdout),fflush(stdout);
    return 0;
}
```

---

## 作者：CJR2010 (赞：0)

考虑转换限制

重复数的个数 $\le k=\lceil\frac{n}{3}\rceil$

等同于 不重复数的个数 $\ge n-k$

简单想想发现这 $n-k$ 个数如果是 $[0,...,n-k-1]$ 这样一个排列很优啊

重复的数就直接往排列上撞就好了

考虑如下构造

设 $k=\lceil\frac{n}{3}\rceil$

第一段 $1\le i\le k$

$a_i=i-1(0,...,k-1),b_i=s_i-a_i(\in [0,?])$

第二段 $k+1\le i\le n-k$

$b_i=i-1(k,...,n-k-1),a_i=s_i-b_i(\in [0,?])$

第三段 $n-k+1\le i\le n$

设 $x_i=s_i-(i-1)$ 可以知道 $0\le x_i\le x_{i+1}$

$b_i=n-i(0,...,k-1),a_i=s_i-b_i(=x_i+2i-n-1)$

因为 $x_i\le x_{i+1},(2i-n-1)< (2(i+1)-n-1)$ 所以 $a_i< a_{i+1}$

$a_{n-k+1}=x_i+n-2k+1$ 可以证明 $>k-1$

---

计算一下可以保证

$a$ 内有 $2k$ 个不同数

$b$ 内有 $n-k$ 个不同数

满足条件

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x3f3f3f3f3f3f3f3fll
#define For(i,l,r) for(int i=(l);i<=(r);++i)
#define Rof(i,l,r) for(int i=(l);i>=(r);--i)
bool M_S;
const int N=100005;
int n,s[N],p[N],a[N],b[N];
void MAIN(){
	cin>>n;int k=(n-1)/3+1;
	For(i,1,n) cin>>s[i],p[i]=i;
	sort(p+1,p+n+1,[](int A,int B){return s[A]<s[B];});
	For(_,1,k){
		int i=p[_];
		a[i]=_-1,b[i]=s[i]-a[i];
	}
	For(_,k+1,n-k){
		int i=p[_];
		b[i]=_-1,a[i]=s[i]-b[i];
	}
	For(_,n-k+1,n){
		int i=p[_];
		b[i]=n-_,a[i]=s[i]-b[i];
	}
	cout<<"YES\n";
	For(i,1,n) cout<<a[i]<<" ";cout<<"\n";
	For(i,1,n) cout<<b[i]<<" ";cout<<"\n";
}
bool M_T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	double T_S=clock();MAIN();double T_T=clock();
	cerr<<"T:"<<(T_T-T_S)/CLOCKS_PER_SEC<<"s ";
	cerr<<"M:"<<(&M_S-&M_T)/1048576<<"MiB\n";
	return 0;
}
```

---

## 作者：ethan0328 (赞：0)

## 思路

有一个比较牛的构造。

考虑将序列 $s$ 排序后平均分为 $3$ 段。

- 对于第 $1$ 段，构造 $a_i=i$，$b_i=s_i-a_i$。

- 对于第 $2$ 段，构造 $b_i=i$，$a_i=s_i-b_i$。

- 对于第 $3$ 段，构造 $b_i=n-i$，$a_i=s_i-b_i$。

解释一下为什么这是对的。

对于 $b$，显然第 $2$ 段和第 $3$ 段的是两两不同的，符合要求。

对于 $a$，第 $1$ 段和第 $3$ 段内部一定是单调递增的，而第 $3$ 段所有数一定大于第 $1$ 段，所以两两不同，符合要求。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct node
{
	int v,id;
};
int n,k;
node a[N],b[N],s[N];
bool cmp1(node x,node y)
{
	return x.v<y.v;
}
bool cmp2(node x,node y)
{
	return x.id<y.id;
}
signed main()
{
	cin>>n;
	k=n/3+(n%3? 1:0);
	for(int i=1;i<=n;i++)
	{
		cin>>s[i].v;
		s[i].id=i;
	}
	sort(s+1,s+1+n,cmp1);
	for(int i=1;i<=k;i++)
	{
		a[i].id=b[i].id=s[i].id;
		a[i].v=i-1;b[i].v=s[i].v-a[i].v;
	}
	for(int i=k+1;i<=n-k;i++)
	{
		a[i].id=b[i].id=s[i].id;
		b[i].v=i-1;a[i].v=s[i].v-b[i].v;
	}
	for(int i=n-k+1;i<=n;i++)
	{
		a[i].id=b[i].id=s[i].id;
		b[i].v=n-i;a[i].v=s[i].v-b[i].v;
	}
	sort(a+1,a+1+n,cmp2);
	sort(b+1,b+1+n,cmp2);
	cout<<"YES\n";
	for(int i=1;i<=n;i++)
	{
		cout<<a[i].v<<" ";
	}
	cout<<"\n";
	for(int i=1;i<=n;i++)
	{
		cout<<b[i].v<<" ";
	}
}
```

---

