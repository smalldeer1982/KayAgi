# loidc，看看海

## 题目背景

loidc 喜欢大海。在他放假的时候他经常一个人跑到海边独自玩耍。

在浪花的冲击下，他可以忘记打代码的烦躁，真是惬意极了。

虽然今天是周六，但今天可是 $2014$ 年 $11$ 月 $8$ 日，NOIP 2014 复赛 Day 1。在早晨放松之余他可不能忘掉 OI 知识。

## 题目描述

loidc 准备带着 LOI 的队员们考完试后到海边玩耍。所以他想写一个程序让队员们了解在一段时间内海浪的情况。

他的命令是这样输入的：

$$\texttt{x y k}$$

这是要询问在时间 $[x,y]$ 内海浪高度第 $k$ 小的单位时刻是那个时刻。

但是在他刚准备打开 Dev-pas++ 的时候，loidc 发现他的电脑坏掉了。于是一向喜欢偷懒的他就向你求助。他希望你能在 $1$ 秒内完成程序的运行。

当然 loidc 会提前告诉你所有时段海浪的高度，这点你放心。至于他是如何得到的，这就不得而知了。

## 说明/提示

对于 $30\%$ 的数据，$n,m \le 200$。

对于 $100\%$ 的数据，$1 \le n,m \le 4000$，$1 \le a_i \le 10^5$ 且 $a_i$ 两两不等，$1 \le x \le y \le n$，$1 \le k \le y-x+1$。

## 样例 #1

### 输入

```
5
1 2 3 4 5
3
2 4 2
1 5 1
3 3 1
```

### 输出

```
3
1
3
```

# 题解

## 作者：communist (赞：18)

## 楼下各位大佬都用的排序和杨颙大定理，蒟蒻的我怎么也不会做（瑟瑟发抖），那么，就来一发主席树吧。
### 我们知道线段树可以维护区间，平衡树可以维护值域
### 那么，我们可以用线段树套平衡树来解决这个区间值域的问题
## 线段树套平衡树~~（令人窒息的操作）~~
### 好在权值线段树也可以维护值域，
### 我们只要建n棵线段树维护前缀和，然后作差就好
### 考虑空间限制，我们需要让这些线段树共用一些节点，再搞一搞离散化，~~其实这题的数据范围不用~~
# 一颗主席树华丽登场
## 时间复杂度O(nlogn),空间复杂度O(nlogn)
### 上代码：
```
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=5010;
struct tree{
    int v,ls,rs;
}a[15*maxn];
int n,m,rt[maxn],cnt,mp[maxn],v[maxn],out[maxn];
void insert(int pre,int cur,int p,int l,int r)    //插入
{
    if(l==r)
    {
        a[cur].v=a[pre].v+1;
        return;
    }
    int m=(l+r)>>1;
    if(p<=m)
    {
        a[cur].ls=++cnt;    //新建节点
        a[cur].rs=a[pre].rs;    //共用节点
        insert(a[pre].ls,a[cur].ls,p,l,m);
    }
    else
    {
        a[cur].rs=++cnt;
        a[cur].ls=a[pre].ls;
        insert(a[pre].rs,a[cur].rs,p,m+1,r);
    }
    a[cur].v=a[a[cur].ls].v+a[a[cur].rs].v;    //push up
}
int kth(int x,int y,int k,int l,int r)    //查询k小值
{
    if(l==r)
        return l;
    int m=(l+r)>>1;
    int num=a[a[y].ls].v-a[a[x].ls].v;    //前缀和
    if(num>=k)    //第k小在左子树
        return kth(a[x].ls,a[y].ls,k,l,m);
    else    //在右子树
        return kth(a[x].rs,a[y].rs,k-num,m+1,r);
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&v[i]);
        mp[i]=v[i];
    }
    sort(mp+1,mp+n+1);    //特色离散化
    cin>>m;
    for(int i=1;i<=n;i++)
    {
        v[i]=lower_bound(mp+1,mp+n+1,v[i])-mp;
        out[v[i]]=i;
        rt[i]=++cnt;
        insert(rt[i-1],rt[i],v[i],1,n);
    }
    for(int i=1;i<=m;i++)
    {
        int x,y,k;
        scanf("%d%d%d",&x,&y,&k);
        printf("%d\n",out[kth(rt[x-1],rt[y],k,1,n)]);
    }
    return 0;
}
```

---

## 作者：人生人生 (赞：8)

# 本人太菜，只会sort，什么主席树，splay，都不会用。
我们定义一个结构体，分别用来存海浪的时间和高度。
接下来，我们把结构体按照高度从小到大sort一遍，保证单调性。
这时，对于每一个询问，我们都用一个计数器，将每一个海浪扫一遍。
如果此海浪的时间在x和y之间，就计入计数器。
当扫的过程中计数器到达了z时，就记下当前波浪的时间，并跳出。
时间复杂度为O(NM)。（当然像这种低级方法只能做到这样了！）
代码：
```
#include<bits/stdc++.h>
using namespace std;
struct no{
	int num,sum;
}a[4001];
int n,q,m,ans[4001],x,y,z;
bool cmp(no x,no y)
{
	return x.sum<y.sum;
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i].sum);
		a[i].num=i;
	}
	sort(a+1,a+n+1,cmp);
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		int u=0;
		scanf("%d%d%d",&x,&y,&z);
		for(int j=1;j<=n;j++)
		{
			if(a[j].num>=x&&a[j].num<=y)
			u++;
			if(u==z)
			{
				ans[i]=a[j].num;
				break;
			}
		}
	}
	for(int i=1;i<=m;i++)
	printf("%d\n",ans[i]);
	return 0;
}
```


---

## 作者：AubRain (赞：6)

一看到这道题，我就知道是

~~替罪羊树上用sb块状链表维护Toptree上的最小费用最大流和可持久化仙人掌，算出来在基尔霍夫矩阵中反演后跑一遍fft维护的插头DP~~（雾）



看着楼下各种暴力大佬，我深感
## 我太菜了

只会用

# 莫队 套 splay

乱搞

时间复杂度： $O(n$√$nlogn)$

空间复杂度： $O(n)$

和主席树相比，时间复杂度多了一个 √$n$

### 但这支持单点修改！

于是用带修改的莫队就可以做动态区间k大了

做法：

莫队分块暴力修改到当前询问的区间，然后直接splay查询第k大就行了

### ~~于是潇潇洒洒随手一敲233行代码~~

代码：

```
#include<bits/stdc++.h>
#define N 200005
using namespace std;

int w[N],l=1,r,p[N];
int n,m,sz,root,B;
struct nd
{
    int id,l,r,k,ans;
}a[N];
int f[N],key[N],cnt[N],size[N],ch[N][2];

inline void read(int &x)
{
    x=0;int w=0;char ch=0;
    while(!isdigit(ch)) ch=getchar(),w|=ch=='-';
    while( isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    x=w?-x:x;
}

inline int get(int x)
{
    return ch[f[x]][1]==x;
}

inline void clear(int x)
{
    size[x]=ch[x][1]=ch[x][0]=f[x]=cnt[x]=key[x]=0;
}

inline void update(int x)
{
    if(!x) return ;
    size[x]=cnt[x];
    if(ch[x][0]) size[x]+=size[ch[x][0]];
    if(ch[x][1]) size[x]+=size[ch[x][1]];
}

inline void rotate(int x)
{
    int old=f[x];
    int old_f=f[old];
    int k=get(x);

    ch[old][k]=ch[x][k^1];
    f[ch[old][k]]=old;

    ch[x][k^1]=old;
    f[old]=x;
    f[x]=old_f;

    if(old_f)
        ch[old_f][ch[old_f][1]==old]=x;

    update(old);
    update(x);
}

inline int splay(int x)
{
    for(int fa;(fa=f[x]);rotate(x))
        if(f[fa])
            rotate(get(x)==get(fa)?fa:x);
    root=x;
}

inline int find(int v)
{
    int ans=0,now=root;
    while(1)
    {
        if(v<key[now])
            now=ch[now][0];
        else
        {
            if(ch[now][0])
                ans+=size[ch[now][0]];
            if(v==key[now])
            {
                splay(now);
                return ans+1;
            }
            ans+=cnt[now];
            now=ch[now][1];
        }
    }
}

inline int find_kth(int x)
{
    int now=root;
    while(1)
    {
        if(ch[now][0]&&x<=size[ch[now][0]])
            now=ch[now][0];
        else
        {
            int t=cnt[now];
            if(ch[now][0])
                t+=size[ch[now][0]];
            if(x<=t) return key[now];
            x-=t;
            now=ch[now][1];

        }
    }
}

inline void insert(int v)
{
    if(!root)
    {
        root=++sz;
        key[sz]=v;
        cnt[sz]=size[sz]=1;
        ch[sz][0]=ch[sz][1]=f[sz]=0;
        return ;
    }
    int now=root,fa=0;
    while(1)
    {
        if(key[now]==v)
        {
            cnt[now]++;
            update(now);
            update(fa);
            splay(now);
            return ;
        }
        fa=now;
        now=ch[now][key[now]<v];
        if(now==0)
        {
            f[++sz]=fa;
            key[sz]=v;
            cnt[sz]=size[sz]=1;
            ch[sz][0]=ch[sz][1]=0;
            ch[fa][key[fa]<v]=sz;
            update(fa);
            splay(sz);
            return ;
        }
    }
}

inline int pre()
{
    int now=ch[root][0];
    while(ch[now][1])
        now=ch[now][1];
    return now;
}

inline int next()
{
    int now=ch[root][1];
    while(ch[now][0])
        now=ch[now][0];
    return now;
}

inline void del(int v)
{
    int pp=find(v);
    int x=root;
    if(cnt[x]>1) {cnt[x]--;return ;}
    if(!ch[x][0]&&!ch[x][1]){clear(x);root=0;return ;}
    if(!ch[x][0])
    {
        root=ch[x][1];
        f[root]=0;
        clear(x);
        return ;
    }
    if(!ch[x][1])
    {
        root=ch[x][0];
        f[root]=0;
        clear(x);
        return ;
    }
    int prev=pre();
    splay(prev);
    f[ch[x][1]]=root;
    ch[root][1]=ch[x][1];
    clear(x);
    update(root);
}

bool cmp(nd a,nd b)
{
    return a.l/B==b.l/B ? a.r<b.r:a.l<b.l;
}
bool fcmp(nd a,nd b)
{
    return a.id<b.id;
}

void add(int x,int i)
{
    if(i==1) insert(w[x]);
    else del(w[x]);
}
void work()
{
    for(int i=1;i<=m;i++)
    {
        while(l<=r+1)
        {
            if(l==a[i].l and r==a[i].r) break;
            while(r<a[i].r) add(++r, 1);
    	    while(r>a[i].r) add(r--,-1);
    	    while(l<a[i].l) add(l++,-1);
    	    while(l>a[i].l) add(--l, 1);
        }
        a[i].ans=find_kth(a[i].k);
    }
}
int main()
{
    read(n);
    for(int i=1;i<=n;i++)
        read(w[i]),p[w[i]]=i;
    read(m);B=sqrt(m);
    for(int i=1;i<=m;i++)
        read(a[i].l),read(a[i].r),read(a[i].k),a[i].id=i;
    sort(a+1,a+1+m,cmp);
    work();
    sort(a+1,a+1+m,fcmp);
    for(int i=1;i<=m;i++)
        printf("%d\n",p[a[i].ans]);
    return 0;
}
```

---

## 作者：不到前10不改名 (赞：5)

第一种是快排，不过这题保证各个时刻海浪高度均不相同，所以也能过
```
#include<stdio.h>
int a[4001],d[4001];
int q(int b,int c)
{ 
  int i=b,j=c,t;
  int p=a[(b+c)/2];
  while(i<=j)
  {while(a[i]<p)
  {i++;}
  while(a[j]>p)
  {j--;}
  if(i<=j)
  {t=a[i];
  a[i]=a[j];
  a[j]=t;
  t=d[i];
  d[i]=d[j];
  d[j]=t;
  i++;
  j--;}}
  if(b<j)
  {q(b,j);}
  if(i<c)
  {q(i,c);}
  return 0;
  }//手写快排，不要吐槽我不用sort，我是纯c
int main()
{  
   int n,x,k,i,y,m,j;
   scanf("%d",&n);
   for(i=1;i<=n;i++)
   {scanf("%d",&a[i]);
   d[i]=i;}
   q(1,n);
   scanf("%d",&m);
   for(j=1;j<=m;j++)
   {scanf("%d%d%d",&x,&y,&k);
   int t=0;
   for(i=1;i<=n;i++)
   {if(x<=d[i]&&d[i]<=y)
   {t++;}//累加，也没什么好讲的
   if(t==k)
   {printf("%d\n",d[i]);
   break;}}}
   return 0;
   }
下面是选排，即使相同也能过
#include<stdio.h>
int main()
{
   int n,x,k,i,y,m,j,t,a[4001],d[4001];
   scanf("%d",&n);
   for(i=1;i<=n;i++)
   {scanf("%d",&a[i]);
   d[i]=i;}
   for(i=1;i<=n;i++)
   {k=i;
   for(j=i+1;j<=n;j++)
   if(a[k]>a[j])
   k=j;
   if(k!=i)
   {t=a[i];
   a[i]=a[k];
   a[k]=t;//选排都不会就没得说了
   t=d[i];
   d[i]=d[k];
   d[k]=t;}}
   scanf("%d",&m);
   for(j=1;j<=m;j++)
   {scanf("%d%d%d",&x,&y,&k);
   int t=0;//t每次都要清0，别的都和上面一样
   for(i=1;i<=n;i++)
   {if(x<=d[i]&&d[i]<=y)
   {t++;}
   if(t==k)
   {printf("%d\n",d[i]);
   break;}}}
   return 0;
}``` 


---

## 作者：mzycjjc (赞：3)

## **输出的是时刻！！！**
题目大意：给定一串数，求这串数中从第 $x$ 个数到第 $y$ 个数中第 $k$ 小的数。

基本策略：先从这串数中取出从 $x$ 到 $y$ 的一串数（时刻和高度都要取），再在这一串数中找到第 $k$ 小的高度，最后输出第 $k$ 小的高度所对应的时刻 ，没有什么特别的算法（**记得吸氧加速,否则会超时**）。
 

**附上蒟蒻的暴力代码：**
 
```cpp
#include<bits/stdc++.h>
using namespace std;
struct ll{  		//结构体，sk时刻，gd高度
	long long sk,gd;
}a[10000],b[10000];
bool cmp(ll xx,ll yy)
{
	return xx.gd<yy.gd;
}
long long n,m;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)	
	{
		cin>>a[i].gd;
		a[i].sk=i;
	}
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		long long x,y,k;
		long long tt=0;  //用tt记录b数组的长度，排序时更方便
		cin>>x>>y>>k;
		for(int j=x;j<=y;j++)
		{
			tt++;		   
			b[tt].gd=a[j].gd;
			b[tt].sk=a[j].sk;  //取出高度和时刻
		}
		sort(b+1,b+tt+1,cmp);
		cout<<b[k].sk<<endl;  //输出
		memset(b,0,sizeof(b));  //记得清空b数组
	}
	return 0;
}
``` 

---

## 作者：NATO (赞：1)

### 主要思想：

每输入一次就取出该区间的所有数，并快速排序，然后输出第 $k$ 位数就行了。（必须吸氧优化）

### 注意点：

输出是海浪高度。

#### 参考代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct px
{
	ll id,sum;
}a[4005],b[4005];
bool cmp(px a,px b)
{
	return a.sum<b.sum;
}
ll n,m;
int main()
{
	cin>>n;
	for(ll i=1;i<=n;++i)
	cin>>a[i].sum,a[i].id=i;
	cin>>m;
	for(ll i=1;i<=m;++i)
	{
		ll x,y,k;
		cin>>x>>y>>k;
		ll tt=0;
		for(ll j=x;j<=y;++j)
		{
		++tt;	
		b[tt].id=a[j].id;
		b[tt].sum=a[j].sum;
		}
		sort(b+1,b+1+tt,cmp);
		cout<<b[k].id<<endl;
	}
}
```


---

## 作者：5k_sync_closer (赞：1)

# P2310
看用pair的挺少的
# first_version
```cpp
#include <iostream>
#include <algorithm>
#include <utility>
#include <cstring>
using namespace std;
int n, m, ans[4001], x, y, k;pair<int, int> a[4001];
bool comp(pair<int, int> a, pair<int, int> b)
{
	return a.second < b.second;
}
int main()
{
	ios::sync_with_stdio(0);
	cin >> n;
	for(register int i(1);i <= n;++i)
		cin >> a[i].second, a[i].first = i;
	cin >> m;
	for(int i(1);i <= m;++i)
	{
		cin >> x >> y >> k;
		pair<int, int> t[4001];memset(t, 0, sizeof t);
		for(register int j(x), jj(1);j <= y;++j, ++jj)
			t[jj].first = a[j].first, t[jj].second = a[j].second;
		sort(t + 1, t + y - x + 2, comp);
		ans[i] = t[k].first;
	}
	for(register int i(1);i <= m;++i)
		cout << ans[i] << endl;
	return 0;
}
```
暴力应该不用讲了吧
T了7个点 吸氧6.21s能过(只是为了和第二种对比)
但是没有利用pair的性质
# second_version
```cpp
#include <iostream>
#include <algorithm>
#include <utility>
#include <cstring>
using namespace std;
int n, m, ans[4001], x, y, k;pair<int, int> a[4001];
int main()
{
	ios::sync_with_stdio(0);
	cin >> n;
	for(register int i(1);i <= n;++i)
		cin >> a[i].first, a[i].second = i;
	cin >> m;
	for(int i(1);i <= m;++i)
	{
		cin >> x >> y >> k;
		pair<int, int> t[4001];
		for(register int j(x), jj(1);j <= y;++j, ++jj)
			t[jj] = a[j];
		sort(t + 1, t + y - x + 2);
		ans[i] = t[k].second;
	}
	for(register int i(1);i <= m;++i)
		cout << ans[i] << endl;
	return 0;
}
```
pair的性质:比较时先比第一关键字再比第二关键字
因为这题海浪高度保证不一样 所以只会比第一关键字

~~但还是T了7个点~~吸氧4.67s
比第一种快1.5秒左右
# third_version
```cpp
#include <iostream>
#include <algorithm>
#include <utility>
#include <cstring>
using namespace std;
int n, m, ans[4001], x, y, k;pair<int, int> a[4001];
int main()
{
	ios::sync_with_stdio(0);
	cin >> n;
	for(register int i(1);i <= n;++i)
		cin >> a[i].first, a[i].second = i;
	sort(a + 1, a + 1 + n);
	cin >> m;
	for(int i(1);i <= m;++i)
	{
		cin >> x >> y >> k;int t(0); //计数器
		for(register int j(1);j <= n;++j) //扫一遍
			if(x <= a[j].second && a[j].second <= y) //找到第k个范围内的值
			{
				t++;
				if(t == k)
				{
					ans[i] = a[j].second;
					break; //不用继续扫了
				}
			}
	}
	for(register int i(1);i <= m;++i)
		cout << ans[i] << endl;
	return 0;
}
```
242ms 吸氧109ms
只需要sort一次
```cpp
#include <iostream>
#include <limits.h>
using namespace std;
int main()
{
	int rp = INT_MIN;
	do rp++; while(rp != INT_MAX);
  	if(rp > 999999999) cout << "I AK CSP!";
 	return 0;
}
```


---

## 作者：NotaKoala (赞：1)

本蒟蒻连主席树都不会打，只好用分块写了

如果$x$是第$k$个数，那么一定有

- 在区间中不超过$x$的数不少于$k$个
- 在区间中小于$x$的数有不到$k$个

如果可以快速求出去建立不超过$x$的数的个数，就可以对x进行二分搜索求出第$k$个数是多少。

大约每$\sqrt{n}$个数放一个桶里，对每个桶排序。

- 对完全包含在区间里的桶，用二分搜索
- 对不完全包含的就直接暴力统计

复杂度大概似乎是$O(nlogn + m\sqrt{n} log n)$


```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

const int B = 35; // size of bucket
const int MAX_N = 4e3 + 5;
const int MAX_M = 4e3 + 5;
const int MAX_P = 100000 + 5;

int N;
int A[MAX_N]; 
int I[MAX_M], J[MAX_M], K[MAX_M];

int nums[MAX_N]; 			   // 对A排序后的结果 
vector<int> bucket[MAX_N / B]; // 每个桶排序之后的结果 

int P[MAX_P];

void solve() {
    for (int i = 0; i < N; i++) {
        bucket[i / B].push_back(A[i]);
        nums[i] = A[i];
    }
    sort(nums, nums + N);
    
    for (int i = 0; i < N / B; i++) sort(bucket[i].begin(), bucket[i].end());
    
    for (int i = 0; i < M; i++) {
        int l = I[i] - 1, r = J[i], k = K[i];
        
        int lb = -1, ub = N - 1;
        while (ub - lb > 1) {
            int md = (lb + ub) / 2;
            int x = nums[md];
            int tl = l, tr = r, c = 0;
            
            while (tl < tr && tl % B != 0) if (A[tl++] <= x) c++;
            while (tl < tr && tr % B != 0) if (A[--tr] <= x) c++;
            
            while (tl < tr) {
                int b = tl / B;
                c += upper_bound(bucket[b].begin(), bucket[b].end(), x) - bucket[b].begin();
                tl += B;
            }
            
            if (c >= k) ub = md;
            else lb = md;
        }
        
        printf("%d\n", P[nums[ub]]);
    }
}

int read() {
    register int x = 0, s = 1;
    register char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-') s= -1;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * s;
} 

int main() {
    N = read();
    for (int i = 0; i < N; i++) A[i] = read(), P[A[i]] = i + 1;
    M = read();
    for (int i = 0; i < M; i++) I[i] = read(), J[i] = read(), K[i] = read();
    solve();
    return 0;
}
```


---

## 作者：石破天惊 (赞：1)

这道题的核心就两个——排序+枚举

我写了一个子函数(void)，用于处理枚举，

void f(int x,int y,int k)

(x，y为本次询问中的区间头和尾，k为区间范围)

函数入口：

f(int l[i][1],int l[i][2],int l[i][2]-l[i][1]+1){

为在区间范围内排序，我还开了一个临时数组

b[10000]

接着调用快排（记得加头文件哦！）

int cmp(const void \*a, const void \*b){

    return(\*(int \*)a-\*(int \*)b);

}
然后输出该区间的要求值k。


---

## 作者：hfctf0210 (赞：1)

这道题，其实是显然的，就可以用**杨颙大定理**来做：

杨颙大定理：**对于任意一段长度不小于k的区间，若满足ai<ai+1<…<ar，都有第k小的数为ai+k-1**……用杨颙的话来解释，**这是显然的**

所以程序就相当好写：

杨颙大定理：

```cpp
cin>>a>>n>>m>>x;
    if(x<=2)
    {
        cout<<a;
        return 0;
    }
    if(x==n)
    {
        cout<<0;
        return 0;
    } 
    int i,j,t1,t2,t,s,ans;
    for(i=1;i<=a;i++)
    {
        s=t1=a;t2=i;
        for(j=3;j<n;j++)
        {
            t=t1+t2;
            s+=t1;
            t1=t2;
            t2=t;
            if(j==x)
            ans=s; 
        }
        if(s==m)
        break;
    }
    if(ans>=1000000)
     cout<<8;
    else cout<<ans<<endl;
```
如果遇到特殊情况(l=r或者al>al+1>…>ar)用特判法
**这道题是显然的……**


---

