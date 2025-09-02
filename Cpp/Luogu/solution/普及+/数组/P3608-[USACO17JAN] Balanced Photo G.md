# [USACO17JAN] Balanced Photo G

## 题目描述

FJ 正在安排他的 $N$ 头奶牛站成一排来拍照（$1\le N \le 10^5$）。序列中的第 $i$ 头奶牛的高度是 $h_i$，且序列中所有的奶牛的身高都不同。

就像他的所有牛的照片一样，FJ希望这张照片看上去尽可能好。他认为，如果 $L_i$ 和 $R_i$ 的数目相差 $1$ 倍以上，第 $i$ 头奶牛就是不平衡的（$L_i$ 和 $R_i$ 分别代表第 $i$ 头奶牛左右两边比她高的奶牛的数量）。也就是说，如果 $L_i$ 和 $R_i$ 中的较大数大于较小数的 $2$ 倍，第 $i$ 头奶牛就是不平衡的。FJ 不希望他有太多的奶牛不平衡。

请帮助 FJ 计算不平衡的奶牛数量。

## 样例 #1

### 输入

```
7
34
6
23
0
5
99
2```

### 输出

```
3```

# 题解

## 作者：nihanchu (赞：19)

（我是去原来官网上一个个单词翻译地看了别人的题解，才弄懂这道题目，所以讲的繁琐或者是有错误还请见谅）

这道题显而易见的是O(n^2)的算法，加一个快排处理以后，复杂度也是O(n^2/2)，那么我们如何来优化呢？

首先我们先将所有的数据从大到小去排列，其中第k大的数在原本的奶牛序列中的序号为i,一个f[k]数组来表示现在第k大的数有无被进行以下的处理过，若已进行，则为1，否则为0.

我们按原本的数组顺序来枚举奶牛，做完以后，这头奶牛所对应的f[k]就为1，这样就能够保证当前f[k]为1的奶牛在原序列中一定在f[k]为0的奶牛的左边，那么在当前枚举的奶牛（对应f[k1]）左边还比他高的的奶牛（假设此奶牛在排序后的队列中序号为k1，那么它对应的就是f[k1]）,f[k1]一定为1，及一定已经被枚举过了，而且k1<k.(因为排序，所以左边的更大)，所以在左边还比他高的奶牛就为f[1]~f[k]中值为1的数量，即f[1]~f[k]的和，即为会更新的前缀和，那么这其实就是一个单点修改+区间查询，用树状数组来维护f数组即可（代码短一些，当然想写线段树也可以！）

好啦，具体情况就在程序的注释中写吧。

参考程序

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct cow{
    int v,t;
}a[200000];
bool cmp(const cow&x,const cow&y)
{
    return (x.v>y.v);
}
inline int read()
{
    char ch=getchar();
    int f=1,x=0;
    while(!(ch>='0'&&ch<='9')){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+(ch-'0');ch=getchar();}
    return x*f;
}
int b[200000],f[200000],n,l,r,ans;
int lowbit(int x)
{
    return (x&-x);
}
//单点更新
void update(int x,int v)
{
    while (x<=n)
    {
        f[x]+=v;
        x+=lowbit(x);
    }
}
//查询前缀和
int query(int x)
{
    int sum=0;
    while (x>0) 
    {
      sum+=f[x];
      x-=lowbit(x);
    }
    return sum;
}
int main()
{
  scanf("%d",&n);
  for (int i=1;i<=n;i++) 
  {
       a[i].v=read();//输入奶牛的身高
    a[i].t=i;//奶牛在原序列中的编号    
  }
  sort(a+1,a+1+n,cmp);//身高从大到小排序
  for (int i=1;i<=n;i++) b[a[i].t]=i;//记录这头奶牛在排序后的编号
  for (int i=1;i<=n;i++)
  {
      l=query(b[i]);//查询左边比它大的奶牛数量，即f[k1]已为1，且k1<k;
      r=b[i]-l-1;//右边比它的数量
      if ((l*2<r)||(r*2<l)) ans++;//记录不平衡数量
      update(b[i],1);//更新，这头奶牛已经被枚举过了
  }
  printf("%d\n",ans);
  return 0;
}
```

---

## 作者：小蒟蒻皮皮鱼 (赞：16)

一道树状数组的裸题。

值得一提的是题目的翻译貌似有点问题。

>如果L[i]和R[i]的数目相差2倍以上的话，第i头奶牛就是不平衡的。（L[i]和R[i]分别代表第i头奶牛左右两边比她高的数量）。如果L[i]和R[i]中较大者比较小者的数量严格多两倍的话，这头奶牛也是不平衡的

题目中这段话的意思其实是$max(l[i], r[i]) > 2 * min(l[i], r[i])$，不要被误导了。

接下来是正题。

首先看到这道题，不难想到$O(n^2)$的暴力做法，即枚举，但是这样显然会超时，需要优化。

我们发现，题目中要求的东西其实就是一个点左边和右边比他大的点的数量，所以我们枚举的时候其实是浪费了很多时间的，因为一个点的信息并非和其他点没有关联，我们想想怎么能够利用这些信息。

对于一个序列中的某个数，只有比他大的数才会产生影响，所以一个很显然的想法是先从大到小排序。

考虑排序以后，当你操作到$a[i]$这个数时，比他大的数一共有$n-i$个，也就是说只要你求出这个点左边比他大的数的数量，就可以求出右边的数量。那么你在插入这个数时产生的贡献就是把这个数后面的比他小的数的答案+1。

举个例子，现在有序列3 2 5 1

当你插入3时，2和1的答案都会+1

那么其实就是求一个单点修改的前缀和，每次插入一个数就把这个位置的值从0变成1，然后对于某一个位置$i$，左边比他大的数就只需要查询一个前缀和就行了。

用树状数组维护，代码也很简洁。


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000005;
struct sCow
{
	int iH, iBh;
}Cow[N];
bool cmp(sCow x, sCow y){return x.iH > y.iH;}
int iSum[N], n;
int lowbit(int x) {return x & -x;}
void Add(int x, int k){for(; x <= n; x += lowbit(x)) iSum[x] += k;}
int Query(int x){int ans = 0;for(; x; x -= lowbit(x)) ans += iSum[x];return ans;}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &Cow[i].iH), Cow[i].iBh = i;
	sort(Cow + 1, Cow + 1 + n, cmp);
	int iAns = 0;
	for(int i = 1; i <= n; i++)
	{
		Add(Cow[i].iBh, 1);
		int l = Query(Cow[i].iBh - 1);
		int r = i - l - 1;
		if(max(l, r) > 2 * min(l, r)) iAns++;
	}
	cout<<iAns;
}
```


---

## 作者：Starria的脑残粉 (赞：5)

好久不打高级数据结构了

然后就打了个主席树

然后就a了

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l[5000000],r[5000000],a[5000000],sum[5000000],x,y,ans,kk;
int putit(int x,int y,int z,int ll,int rr){//加入元素
    sum[x]=sum[y];if (ll==rr){sum[x]++;return x;}int m=(ll+rr)/2;
    if (z<=m){l[x]=putit(++kk,l[y],z,ll,m);r[x]=r[y];}
    if (z>m){r[x]=putit(++kk,r[y],z,m+1,rr);l[x]=l[y];}
    sum[x]=sum[l[x]]+sum[r[x]];return x;
}int findit(int x,int y,int z,int ll,int rr){//删除元素
    if (ll==z)return sum[y]-sum[x];
    int m=(ll+rr)/2;if (!y)return 0;
    if (z<=m)return sum[r[y]]-sum[r[x]]+findit(l[x],l[y],z,ll,m);
        else return findit(r[x],r[y],z,m+1,rr);
}
signed main(){
    ios::sync_with_stdio(false);
    cin>>n;kk=n;for (int i=1;i<=n;i++)cin>>a[i],putit(i,i-1,a[i],0,1e9);
    for (int i=1;i<=n;i++){
        x=findit(0,i-1,a[i]+1,0,1e9);y=findit(i,n,a[i]+1,0,1e9);if (x<y)swap(x,y);
                    //找出在i左边的比i大的元素和在i右边比i大的元素并且形成有序点对
        if (2*y<x)ans++;//这里题面翻译有误
    }cout<<ans<<endl;
}
```

---

## 作者：Shikita (赞：4)

# 好吧我又来发题解了，其实也就是一个慢慢调试代码的结果
题目意思:给定一个序列，求左右两边大于每个数的的个数，再比较两者关系（不过这个并不是重点）

## 代码
```
#include<bits/stdc++.h>
using namespace std;
int n,ans=0;
int h[100005];
int c[100005];
inline int read()
{
    int x=0;
    char c=getchar();
    bool flag=0;
    while(c<'0'||c>'9') {if(c=='-')flag=1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x+(x<<2)<<1)+ c-'0';c=getchar();}
    return flag?-x:x;
}
int main()
{
	n=read();
	for(int i=1;i<=n;++i) h[i]=read();
	for(int i=1;i<=n;++i)
	{
		int l=0,r=0;
		for(int j=1;j<=i;++j) if(h[i]<h[j]) l++;
		for(int j=i;j<=n;++j) if(h[i]<h[j]) r++;
		//cout<<i<<" "<<l<<" "<<r<<endl;
		if(min(l,r)*2<max(l,r)) ans++;
	}
	cout<<ans<<endl;
	return 0;
}
```
显而易见暴力是绝对过不去的毕竟数据 100,000而且还是O（N^2）的暴力
即使如此我还是骗到了60分
于是感觉数据水（事实证明这是错觉）
然后又加了一点小优化
```
#include<bits/stdc++.h>
using namespace std;
int n,ans=0;
struct node{int x,y;}a[100005];
inline int read()
{
    int x=0;
    char c=getchar();
    bool flag=0;
    while(c<'0'||c>'9') {if(c=='-')flag=1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x+(x<<2)<<1)+ c-'0';c=getchar();}
    return flag?-x:x;
}
bool cmp(node x,node y)
{
	return x.x>y.x;
}
int main()
{
	n=read();
	for(int i=1;i<=n;++i) 
	a[i].x=read(),a[i].y=i;
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;++i)
	{
		int l=0,r=0;
		for(int j=1;j<i;++j) 
		{
			if(a[i].y>a[j].y) l++;
			else r++;
		}
		if(min(l,r)*2<max(l,r)) ans++;
	}
	cout<<ans<<endl;
	return 0;
}
```
这里加上了一个sort，比起之前的好像复杂度大概是O（NlogN）（在下对复杂度判断实在不行，万一错了请大佬斧正）
然而这样子就有70分了???
于是开始认真想一下算法
毕竟看样子暴力肯定行不通因为T掉3个点都是1900+ms
然后又想到前缀和，于是~~非常顺利~~想到了树状数组
```
#include<bits/stdc++.h>
#pragma GCC optimize(2)
#pragma GCC optimize(3)
using namespace std;
int n,ans=0;
struct node{int x,y;}a[100005];
int c[100005];
inline int read()
{
    int x=0;
    char c=getchar();
    bool flag=0;
    while(c<'0'||c>'9') {if(c=='-')flag=1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x+(x<<2)<<1)+ c-'0';c=getchar();}
    return flag?-x:x;
}
bool cmp(node x,node y)
{
	return x.x>y.x;
}
int ask(int x)
{
	int cnt=0;
	for(;x;x-=x&-x) cnt+=c[x];
	return cnt;
}
void add(int x,int y)
{
	for(;x<=n;x+=x&-x) c[x]+=y;
}
int main()
{
	n=read();
	for(int i=1;i<=n;++i) 
	a[i].x=read(),a[i].y=i;
	sort(a+1,a+1+n,cmp);
	
	add(a[1].y,1);
	for(int i=2;i<=n;++i)
	{
		int l=ask(a[i].y);
		int r=i-l-1;
		if(min(l,r)*2<max(l,r)) ans++;
		add(a[i].y,1);
	}
	cout<<ans<<endl;
	return 0;
}
```
这里思路也是延续了暴力优化（第二个代码）
先根据大小排序，那么保证数列递减
从前往后遍历，那么处理到的点只和该点之前的点有关（毕竟后面的比他小就不需要处理了），先计算在该点之前（即该点左边）有多少个节点，那么该点右边的节点就是比他大的节点的总和减去前面的节点，这样子就可以少计算一遍，省下来不少时间。而且注意，树状数组查询前缀和是1~x的总和，所以这里应该先计算再加入点，或者先加点再-1都可以
好了蒟蒻我废话也不多说了，就写到这里吧
如有纰漏及错误之处，望各位大佬谅解斧正，谢谢

---

## 作者：Chaos1018 (赞：3)

~~没有一个人写平衡树吗？~~


------------
我太菜了，不会写线段树or树状数组,只能~~copy~~复习fhq_treap板子辣.


题意就是问有多少头牛左边比他高的数量和右边比他高的数量之差的绝对值，大于Min(左边比他高的数量，右边比他高的数量)。

看到这道题，第一想法就是把左右两边比他大的直接求出来再比较。但显然，直接暴力算是会超时的 ~~不用我说都知道啊~~所以要用数据结构来优化。这里我用的是平衡树。


先考虑算左边，对于每头牛，直接在平衡树里查询多少比他大的（即排名），再把这头牛插入平衡树，重复这种操作。右边也十分简单，建一个数组，把原序列反着存进去，再做一次与左边一毛一样的操作就可以了。


最后输出时直接比较两个大小就可以Ａ了。




------------

上代码


```
#include <bits/stdc++.h>
using namespace std;
const int MAX=1e5+10;
//fhq_treap 练手 
int son[MAX][2],rd[MAX],size[MAX],vis[MAX],root,tot,x,y,z; 
template <typename T> inline void read(T &a){
    T w=1;a=0;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()){
        if(ch == '-') w=-1;
    }
    for(;isdigit(ch);ch=getchar()){
        a=(a<<3)+(a<<1)+(ch^48);
    }
    a*=w;
}
inline int new_node(int m){
    size[++tot]=1;vis[tot]=m;
    rd[tot]=rand();
    return tot;
}

inline void up(int now){
    size[now]=size[son[now][0]]+size[son[now][1]]+1;
}

void split(int now,int k,int &a,int &b){
    if(!    now){
        a=b=0;return ;
    }
    if(vis[now]<=k)
       a=now,split(son[now][1],k,son[now][1],b);
    else 
       b=now,split(son[now][0],k,a,son[now][0]);
    up(now);
}

int merge(int a,int b){
    if(!a || !b){
        return a+b;
    }
    if(rd[a]<rd[b]){
        son[a][1]=merge(son[a][1],b);up(a);return a;
    }
    else{
        son[b][0]=merge(a,son[b][0]);up(b);return b;
    }
}

int k_th(int now,int k){
    while(1){
        if(k<=size[son[now][0]])now=son[now][0];
        else if(k==size[son[now][0]]+1) return now;
        else{
            k-=size[son[now][0]]+1;now=son[now][1];
        }
    }
}
//fhq_treap基本操作
int a[MAX],b[MAX];
int Ans1[MAX],Ans2[MAX];
int n;

int main(){
    srand(1710);
    read(n);
    for(register int i=1;i<=n;++i){
        read(a[i]);b[n-i+1]=a[i];
    }
    for(register int i=1;i<=n;++i){
        split(root,a[i]-1,x,y);
        Ans1[i]=i-size[x]-1;
        root=merge(x,y);
        split(root,a[i],x,z);
        root=merge(merge(x,new_node(a[i])),z);//查询排名与插入
    }
    memset(vis,0,sizeof(vis));  
    memset(size,0,sizeof(size));
    memset(son,0,sizeof(son));
    memset(rd,0,sizeof(rd));   tot=x=y=z=root=0;
    for(register int i=1;i<=n;++i){
        split(root,b[i]-1,x,y);
        Ans2[i]=i-size[x]-1;
        root=merge(x,y);
        split(root,b[i],x,z);
        root=merge(merge(x,new_node(b[i])),z);//反着再来一遍
    }
    int ans=0;
    for(register int i=1;i<=n;++i){
        int X=Ans1[i],Y=Ans2[n-i+1];
//      cout<<X<<" "<<Y<<endl;
        if(X<Y) swap(X,Y);
        if(X > Y*2) ans++;//直接比较即可
    }
    cout<<ans;
}
```


---

## 作者：曹老师 (赞：3)

**知识点：BIT**

~~好裸的一个BIT求逆序对~~

题解中好多说倒过来求一遍正序对？

其实不然 求得逆序对 正序对O(1)不就出来了吗

**时间复杂度：O(nlogn)**

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<set>
#define MAXN 100005
#define LL long long
#define INF 2147483647
#define MOD 1000000007
#define free(s) freopen("s.txt","r",stdin);
#define lowbit(x) ((x&(-x))) 
#define debug(x) cout<<x<<endl;
using namespace std;
const int L=100005;
struct node{
	int high,num;
};
node cow[L];
int n,bit[L],c[L],ans;
bool cmp(const node &a,const node &b)
{
	return a.high>b.high;
}
int query(int x)
{
	int sum=0;
	for(int i=x;i>=1;i-=lowbit(i))
		sum+=bit[i];
	return sum;
}
void update(int x,int v)
{
	for(int i=x;i<=n;i+=lowbit(i))
		bit[i]+=v;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&cow[i].high);
		cow[i].num=i;
	}
	sort(cow+1,cow+n+1,cmp);
	for(int i=1;i<=n;i++)
		c[cow[i].num]=i;//离散化
	for(int i=1;i<=n;i++)
	{
		int l=query(c[i]),r=c[i]-l-1;
		update(c[i],1);
		if(l>r*2||r>2*l)
			ans++;
	}
    printf("%d",ans);
	return 0;
}
```

---

## 作者：hongzy (赞：3)

好像和逆序对没多大关系，但是思想差不多。先按值从大到小排序离散，然后每次查询得到l(i)和r(i)，累加答案，并把这个点加入树状数组.

思路应该非常清楚了，以下为代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

struct Data {
	int a, i;
} A[100001];
bool cmp(Data a, Data b) {return a.a > b.a;}

int n, cnt, c[100001];

void update(int x, int f) {
	for(; x<=n; x += x&-x) c[x] += f;
}
int query(int x) {
	int s = 0;
	for(; x; x -= x&-x) s += c[x];
	return s;
}

int main() {
	scanf("%d", &n);
	for(int i=1; i<=n; i++)
		scanf("%d", &A[A[i].i = i].a);
	sort(A+1, A+n+1, cmp);
	for(int i=1; i<=n; i++) {
		int l = query(A[i].i-1), r = query(n) - query(A[i].i);
		if(max(l, r) > min(l, r) * 2) cnt ++; 
		update(A[i].i, 1);
	}
	printf("%d\n", cnt);
	return 0;
}

```

---

## 作者：Drug__Lover (赞：3)

**树状数组求逆序对**

**这道题是求一个点前面的逆序对和后面的（正序对？）**

**对于普通的树状数组我们用的是求前缀，但是只要将lowbit加减一换就可以求后缀了**

**这样我们开两个树状数组**

**分别用前缀的方法来求前面的逆序对和后缀的方法求正序对**



```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#define maxn 100100
using namespace std;
int c[maxn],c1[maxn];
int n;
int sum;
int l[maxn],r[maxn];
int add1(int x,int k)
{
    for(int i=x;i<=n;i+=i&(-i)) c[i]+=k;
}
int query1(int x)
{
    int sum=0;
    for(int i=x;i>0;i-=i&(-i)) sum+=c[i];
    return sum;
}
int add2(int x,int k)
{
    for(int i=x;i>0;i-=i&(-i)) c1[i]+=k;
}
int query2(int x)
{
    int sum=0;
    for(int i=x;i<=n;i+=i&(-i)) sum+=c1[i];
    return sum;
}
struct node
{
    int num,high;
}a[maxn];
int cmp1(node x,node y)
{
    return x.high>y.high;
}
int cmp2(node x,node y)
{
    return x.high>y.high;
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++) scanf("%d",&a[i].high),a[i].num=i;
    sort(a+1,a+1+n,cmp1);
    for(int i=1;i<=n;i++)
    {
        add1(a[i].num,1);
        l[a[i].num]=query1(a[i].num-1);   //求前面的比它小的
    }
    sort(a+1,a+1+n,cmp2);
    for(int i=1;i<=n;i++)
    {
        add2(a[i].num,1);
        r[a[i].num]=query2(a[i].num+1);      //后缀，求后面的比它大的
    }
    for(int i=1;i<=n;i++)
    {
        int k1=min(l[i],r[i]);
        int k2=max(l[i],r[i]);
        if(k2>k1*2) sum++;
    }
    cout<<sum<<endl;
    return 0;
}
```

---

## 作者：LordLeft (赞：2)

~~智力不够，二分答案来凑~~

这个题目是让我们求有多少的数$i$，使得$2\times max(\text{i左边比他大的数量},\text{i右边比他大的数量})>min(\text{i左边比他它的数量},\text{i右边比他大的数量})$

换句话说，就是要求一个数左边有几个数比他大，右边有几个数比他大。

显然平衡树是可以做的，~~但是太难了我不会打~~

然后各位大佬都会树状数组$O(n \log n)$求解

鄙人不才，给大家讲一种$O(n \log n^2)$的做法

首先，对于一个区间，假如这个区间内第$K$大的数比$a_i$大，那么区间里就会有$K$个数比$a_i$大，这个还是蛮显然的

那么，我们就可以二分出一个最大的使得$\text{区间第}K\text{大} \leq a_i$的$K$，那么答案就是区间长度减去这个$K$

区间第$K$大直接划分树维护一下就好了，当然也可以主席树，~~可惜我也不会~~

代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
using namespace std;
int read(){
	int w=0;
	bool s=0;
	char c=getchar();
	while(!isdigit(c)){
		s=(c=='-');
		c=getchar();
	}
	while(isdigit(c)){
		w=w*10+c-'0';
		c=getchar();
	}
	return s?-w:w;
}
const int N=100005,M=20;
int n,m;
int a[N];
//划分树
struct Tree{
	#define mid ((le+ri)>>1)
	#define lson le,mid,dep+1
	#define rson mid+1,ri,dep+1
	struct Node{
		int num[N],toleft[N];
	};
	Node t[M];
	int sorted[N];
	void build(int le,int ri,int dep){
		if(le==ri){
			return;
		}
		int key=sorted[mid];
		int equ=mid-le+1;
		for(int i=le;i<=ri;i++){
			if(t[dep].num[i]<key){
				equ--;
			}
		}
		int tl=0;
		int it1=le-1,it2=mid;
		for(int i=le;i<=ri;i++){
			int now=t[dep].num[i];
			if(now<key||(now==key&&equ)){
				if(now==key){
					equ--;
				}
				tl++;
				t[dep+1].num[++it1]=now;
			}
			else{
				t[dep+1].num[++it2]=now;
			}	
			t[dep].toleft[i]=tl;	
		}
		build(lson);
		build(rson);
	}
	int query(int le,int ri,int dep,int x,int y,int z){
		if(le==ri){
			return t[dep].num[le];
		}
		int tl=0,del=t[dep].toleft[y];	
		if(le!=x){
			tl=t[dep].toleft[x-1];
			del-=tl;
		}	
		int nx,ny;	
		if(del>=z){
			nx=le+tl;
			ny=nx+del-1;
			return query(lson,nx,ny,z);
		}
		else{	
			nx=mid+1+x-tl-le;
			ny=nx+y-x-del;
			return query(rson,nx,ny,z-del);
		}	
	}	
};
Tree T;
//二分答案
int find(int x,int y,int z){
	int res=0;
	int tmp;
	int le=1,ri=y-x+1;
	while(le<=ri){
		tmp=T.query(1,n,0,x,y,mid);
		if(tmp<=z){
			res=mid;
			le=mid+1;
		}
		else{
			ri=mid-1;
		}
	}
	return res;
}
int ans=0;
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		T.t[0].num[i]=a[i];
		T.sorted[i]=T.t[0].num[i];
	}
	sort(T.sorted+1,T.sorted+1+n);
	T.build(1,n,0);
	int x,y,z;
	for(int i=1;i<=n;i++){
		int L=0,R=0;
		if(i!=1){
			x=1,y=i-1,z=a[i];
			int k=find(x,y,z);
			L=y-x+1-k;
		}
		if(i!=n){
			x=i+1,y=n,z=a[i];
			int k=find(x,y,z);
			R=y-x+1-k;
		}
		if((L>2*R)||(R>2*L)){
			ans++;
		}
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：TLE_Automat (赞：1)

### **蒟蒻第二篇题解,大佬勿喷** !!!
~~(第一篇题解没过qaq)~~

[题目传送门](https://www.luogu.com.cn/problem/P3608)

进入正题：

我看各位大佬没有用离散化的，就来补一篇题解qwq。
本题思路：离散化+树状数组。

首先,我们看数据范围 $n<=10^5$ 明确这题要么 $O(n)$ ，要么nlogn，显然，如果 $O(n)$ 的话，肯定直接 $n<=10^6$ ，所以我们就考虑 $nlogn$ 的算法。

1. 我们要干什么:维护出一头牛左边比它高的牛的个数  $l_i$ 和右边比它高的牛的个数 $r_i$ ，我们就先考虑怎样维护出 $l_i$ 。

2. 既然要统计出 $l_i$，我们自然会考虑到前缀和，我们可以设树状数组 $d_i$ 表示身高比 $i$ 矮的牛的个数。(**注意：是身高比 $i$ 这个值矮
，而不是比h[i]矮**。)

3. 这样我们就能跑一个for循环维护出 $l_i$ ，详见代码：

```cpp
for(int i=1;i<=n;i++)
{
	l[i]=query(max_h)-query(h[i]);//身高比最高的矮的个数-身高比h[i]矮的个数=身高比h[i]高的牛的个数
	update(h[i],1);
}
```

4. 同理，我们也能维护出 $r_i$，直接memset一下，再反过来跑就行了。

5. 现在，我们发现了一个问题: $d_i$ 是身高比 $i$ 矮的奶牛的个数，但奶牛的身高 $<=10^9$ 。(~~FJ:没听说过纳米是什么吗？~~) 而我们发现数据范围 $n<=10^5$ ，这说明了什么，数据很分散，因为我们只关心奶牛高度的排名，所以我们就把奶牛的身高离散化一下，再用树状数组做就行了。

6. 然后，就没有然后了，我们就做完了。
----

$Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <map>
#include <set>

using namespace std;

int n,cnt;
int h[100010];
int ppp[100010];
int d[100010];
int l[100010];
int r[100010];
map<int,int> mp;

inline int lowbit(int x)
{
	return x&-x;
}

inline void update(int x,int v)
{
	while(x<=n)
	{
		d[x]+=v;
		x+=lowbit(x);		
	}
}

inline int query(int x)
{
	int res=0;
	while(x)
	{
		res+=d[x];
		x-=lowbit(x);
	}
	return res;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&h[i]);
		ppp[i]=h[i];
	}
	sort(ppp+1,ppp+n+1);
	for(int i=1;i<=n;i++)
	{
		if(!mp[ppp[i]])
		{
			mp[ppp[i]]=++cnt;
		}
	}
	for(int i=1;i<=n;i++)
	{
		h[i]=mp[h[i]];
	}
	for(int i=1;i<=n;i++)
	{
		l[i]=query(n)-query(h[i]);
		update(h[i],1);
	}
	memset(d,0,sizeof(d));
	for(int i=n;i>=1;i--)
	{
		r[i]=query(n)-query(h[i]);
		update(h[i],1);
	}
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		int da=max(l[i],r[i]);
		int xiao=min(l[i],r[i]);
		if(da>2*xiao)
		{
			ans++;
		}
	}
	printf("%d",ans);
	return 0;
}

```

如有疑问或错误，请私信蒟蒻，欢迎大佬前来指教。

附注：蒟蒻写题解不易，转载请注明出处。







---

## 作者：jzqjzq (赞：1)

其实本质上就是找一下逆序对数量嘛

所以把原数列离散化之后我们正着和倒着找一遍逆序对（倒着是正序对？）就可以在2\*nlogn的时间内求出所有的l[i]和r[i]

这可以直接用树状数组解决，然后暴力判断即可

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
#include<cstdlib>
#include<set>
#include<map>
#include<string>
#include<ctime>
#include<queue>
#include<vector>
using namespace std;
int n,a[100001],b[100001],l[100001],r[100001],f[100001];
inline int lowbit(int x){return x&-x;}
inline void add(int x){for(;x<=n;x+=lowbit(x))f[x]++;}
inline int sum(int x){int ans=0;for(;x;x-=lowbit(x))ans+=f[x];return ans;}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]),b[i]=a[i];
    sort(b+1,b+n+1);
    for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+n+1,a[i])-b;//离散化
    for(int i=1;i<=n;i++)l[i]=i-1-sum(a[i]),add(a[i]);//正着找逆序对
    memset(f,0,sizeof f);
    for(int i=n;i;i--)r[i]=n-i-sum(a[i]),add(a[i]);//倒着照正序对
    int ans=0;
    for(int i=1;i<=n;i++){
        if(l[i]==0&&r[i]==0)continue;
        if(!l[i]||!r[i])ans++;//特判0的情况
        else{
            int xx=max(l[i],r[i]),yy=min(l[i],r[i]);
            if(xx/yy>2)ans++;
            else if(xx/yy==2&&yy*2!=xx)ans++;
        }
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：_wkjzyc (赞：0)

(快CSP了，正好来复习一下树状数组的板子。)

---

以求L数组为例。先离散化预处理，之后就可以用桶数组arr[i]表示第i个数是否出现。

由于处理会按照h从大到小的顺序进行，所以当统计到h[i]时，前缀和sum[i-1]就是原下标所对应的L值。相对地，R数组对应的就是后缀和。

这一信息，相当于单点修改区间求和，使用树状数组维护。

$ O(n\log n)$处理L与R，再统计答案。

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN=100005;
int n,l[MAXN],r[MAXN],arr[MAXN],ans;
struct data {
	int h,order;
}a[MAXN];
double divi;

int lowbit(int x) {return x&(-x);}
int sum(int x) {int ret=0;for(int i=x;i;i-=lowbit(i)) ret+=arr[i];return ret;}
void add(int x,int num) {for(int i=x;i<=n;i+=lowbit(i)) arr[i]+=num;}
bool comp2(data d1,data d2) {return d1.h>d2.h;}

int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i].h),a[i].order=i;
	sort(a+1,a+1+n,comp2);
	for(int i=1;i<=n;i++) add(a[i].order,1),l[a[i].order]=sum(a[i].order-1);
	memset(arr,0,sizeof(arr));
	for(int i=1;i<=n;i++) add(a[i].order,1),r[a[i].order]=sum(n)-sum(a[i].order);
	for(int i=1;i<=n;i++) divi=(double)l[i]/(double)r[i],ans+=(divi>2||divi<0.5);
	printf("%d",ans);
	return 0;
}
```



---

## 作者：两年打铁 (赞：0)

诚然，$O(n^2)$的做法可以水过去，不过蒟蒻水了一发树状数组。
树状数组复杂度为$O(NlogN)$,非常完美。

我们先离散化数组，改用第几大来代替每次按原输入的数组，那么我们只要用树状数组来维护有几个比这个数大就行了，不过对于从左到右和从右到左，我们需要做两遍。代码（除了我的快读快输）也很短。

```
#include<bits/stdc++.h>
#define swap mswap
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
using namespace std;
void swap(int &x,int &y)
{
    x^=y^=x^=y;
}
void read(int &x)
{
    x=0;
    char ch=getchar();
    int pd=1;
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
        {
            pd=-pd;
        }
        ch=getchar();
    }
    while(ch<='9'&&ch>='0')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    x*=pd;
}
void write(const int &x)
{
    char f[100001];
    int s=0;
    int tmp=x;
    if(tmp==0)
    {
        putchar('0');
        return;
    }
    if(tmp<0)
    {
        tmp=-tmp;
        putchar('-');
    }
    while(tmp>0)
    {
        f[s++]=tmp%10+'0';
        tmp/=10;
    }
    while(s>0)
    {
        putchar(f[--s]);
    }
}

const int N=1e5+10;
int n,c[N],a[N],b[N];
int l[N],r[N];
int lowbit(int &x)
{
	return x&(-x);
	
}


void add1(int x)
{
	while(x<=n)
	{
		c[x]++;
		x+=lowbit(x);
	}
}
void add2(int x)
{
	while(x>0)
	{
		c[x]++;
		x-=lowbit(x);
	}
}


int query1(int x)
{
	int ans=0;
	while(x>0)
	{
		ans+=c[x];
		x-=lowbit(x);
	}
	return ans;
}

int query2(int x)
{
	int ans=0;
	while(x<=n)
	{
		ans+=c[x];
		x+=lowbit(x);
	}
	return ans;
}
inline bool cmp(const int &x,const int &y)
{
	return x>y;
 } 
int main()
{
    read(n);
    for(register int i=1;i<=n;++i)
    {
        read(a[i]);
        b[i]=a[i];
    }
    sort(b+1,b+n+1);
    int cnt=unique(b+1,b+n+1)-b-1;
    for(register int i=1;i<=n;++i)
    {
        int j=lower_bound(b+1,b+cnt+1,a[i])-b;
		add2(j);
        l[i]=query2(j+1);
    }
    memset(c,0,sizeof(c));
	for(register int i=n;i>=1;--i)
	{
		int j=lower_bound(b+1,b+cnt+1,a[i])-b;
		add2(j);
		r[i]=query2(j+1);
	}
	int aa=0;
	for(register int i=1;i<=n;++i)
	{
		if(max(l[i],r[i])>2*(min(l[i],r[i])))
		{
			aa++;
		}
	}
	write(aa);
}
```


---

