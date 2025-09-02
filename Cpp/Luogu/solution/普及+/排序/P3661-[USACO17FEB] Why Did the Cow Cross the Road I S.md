# [USACO17FEB] Why Did the Cow Cross the Road I S

## 题目描述

Farmer John 的奶牛们正在学习如何有效地过马路。回想起古老的“鸡为什么要过马路？”笑话，他们认为鸡一定是过马路的专家，于是去寻找鸡来帮助它们。

事实上，鸡是非常忙碌的生物，它们只有有限的时间来帮助奶牛。农场上有 $C$ 只鸡（$1 \leq C \leq 20,000$），方便地用编号 $1 \ldots C$ 标识，每只鸡 $i$ 只愿意在确切的时间 $T_i$ 帮助一头奶牛。奶牛们从不着急，它们的日程安排更加灵活。农场上有 $N$ 头奶牛（$1 \leq N \leq 20,000$），方便地用编号 $1 \ldots N$ 标识，其中奶牛 $j$ 能够在时间 $A_j$ 到时间 $B_j$ 之间过马路。考虑到“伙伴系统”是最好的方式，每头奶牛 $j$ 理想情况下希望找到一只鸡 $i$ 来帮助她过马路；为了使它们的日程安排兼容，$i$ 和 $j$ 必须满足 $A_j \leq T_i \leq B_j$。

如果每头奶牛最多只能与一只鸡配对，每只鸡也最多只能与一头奶牛配对，请计算可以构建的最大奶牛-鸡配对数。

## 样例 #1

### 输入

```
5 4
7
8
6
2
9
2 5
4 9
0 3
8 13```

### 输出

```
3```

# 题解

## 作者：Cutest_Junior (赞：15)

## 题解 P3661 【[USACO17FEB]Why Did the Cow Cross the Road I S】

### 题意

+ $m$ 个点，$n$ 个区间（闭区间）；
+ 点和区间一一匹配（点在区间中）；
+ 求最多能匹配上的对数。

### 贪心

1. 对区间按右端点的位置升序排列；
1. 对于每个区间，找到位置最小的还没匹配的点，相互匹配。
1. 统计对数。

#### 证明

设有两个区间 $\left[l1,r1\right]$，$\left[l2,r2\right]$，有两个点被第一个区间包含 $d1,d2$。

目前已知：

1. $r1\le r2$ （已排序）；
1. $l1\le d1<d2\le r1$。

若 $l2<d1$:

> 任意两个都可以相互匹配，第一个区间选哪个都不影响结果。

若 $d1\le l2\le d2$：

> 第二个区间只能与 $d2$ 匹配，第一个区间与 $d1$ 匹配更优。

若 $d2<l2$：

> 第二个区间无法匹配，第一个区间选哪个都不影响结果。

综上所述，第一个区间与较小的点匹配，一定不会更劣。

### 代码

```cpp
# include <cstdio>
# include <algorithm>

using namespace std ;

const int N = 20005 ;

int chicken [ N ] ;
bool visit [ N ] ;

struct Cow
{
    int l , r ;
};

bool operator < ( Cow a , Cow b ) // 按右端点升序排序
{
    return a . r < b . r ;
}

Cow cow [ N ] ;

int read ( ) // 事实上在本题优化不大，但还是加上
{
    int a = 0 ;
    char c = getchar ( ) ;
    
    while ( c < '0' || c > '9' )
    {
        c = getchar ( ) ;
    }
    
    while ( c >= '0' && c <= '9' )
    {
        a = a * 10 + c - '0' ;
        c = getchar ( ) ;
    }
    
    return a ;
}

int main ( )
{
    int n = read ( ) , m = read ( ) ;
    
    for ( int i = 1 ; i <= n ; ++ i )
    {
        chicken [ i ] = read ( ) ;
    }
    
    sort ( chicken + 1 , chicken + n + 1 ) ;
    
    for ( int i = 1 ; i <= m ; ++ i )
    {
        cow [ i ] . l = read ( ) ;
        cow [ i ] . r = read ( ) ;
    }
    
    sort ( cow + 1 , cow + m + 1 ) ;
    
    int ans = 0 ;
    
    for ( int i = 1 ; i <= m ; ++ i )
    {
        for ( int j = 1 ; j <= n ; ++ j )
        {
            if ( chicken [ j ] < cow [ i ] . l ) // 还没进区间就下一个
            {
                continue ;
            }
            
            if ( chicken [ j ] > cow [ i ] . r ) // 过了区间就直接结束
            {
                break ;
            }
            
            if ( visit [ j ] ) // 因为要一一对应，已经匹配过的就不能再匹配了
            {
                continue ;
            }
            
            ++ ans ;
            visit [ j ] = 1 ;
            break ;
        }
    }
    
    printf ( "%d" , ans ) ;
}
```

上述做法跑了 $1.76s$。

极慢极慢。

然后某学长给我提供了一个 $O\left(N\log N\right)$ 的做法。

### $O\left(N\log N\right)$ 做法

由于点是有序的，那么就可以用二分进行优化。

但是，一个区间内的点理论上有也 $n$ 个，如果前 $n-1$ 个点都被选过，则这个算法就又退化回 $O\left(N^2\right)$ 了。

考虑选完就删点，但是数组删点复杂度为 $O\left(N\right)$，于是又退化回$O\left(N^2\right)$ 了。（~~我太难了~~）

考虑数据结构优化，需要一个数据结构，可以保持数据有序，可以二分，可以在 $O\left(\log N\right)$ 时间内删点。

某学长想出了 STL 里的 multiset。

代码来自@[zzl_05](https://www.luogu.com.cn/user/105230)

```cpp
#include <cstring>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <set>
using namespace std;
#define ll long long
#define ri register int

char buf[1 << 20], *p1, *p2;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2)?EOF: *p1++)
inline int read() {
	ri v = getchar();int f = 1,t = 0;
	while (!isdigit(v)) {if (v == '-')f = -1;v = getchar();}
	while (isdigit(v)) {t = t * 10 + v - 48;v = getchar();}
	return t *= f;
}

const int N = 20010;

//1.区间排序，对于每个r_i找一个最近的前面的点x_j，如果x_j<l_i，就肯定不行，反之行，也弹掉
multiset <int> s;

struct inter {
    int l,r;
    friend inline bool operator < (const inter & a,const inter &b) {
        return a.r == b.r ? a.l > b.l : a.r < b.r;
    }
}a[N];

int n,m,x[N],ans;
multiset<int>::iterator it;

signed main() {
    n = read(),m = read();
    for (int i = 1;i <= n;++i) x[i] = read(),s.insert(x[i]);
    for (int i = 1;i <= m;++i) a[i].l = read(),a[i].r = read();
    sort(a+1,a+1+m);
    //for (int i = 1;i <= m;++i) printf("%d %d\n",a[i].l,a[i].r);
    for (int i = 1;i <= m;++i) {
        it = s.lower_bound(a[i].l);
        //printf("%d\n",*it);
        if (it != s.end()) {
            if (*it <= a[i].r) ++ans,s.erase(it);
        }
    }
    printf("%d\n",ans);
	return 0;
}
```

### update

$2020.10.1$ 初稿。

$2020.10.21$ 修改如下。

>in 《证明》。

>> 目前已知：

>> 1. $r1\le r2$ （已排序）；
>> 1. $l1\le d1<d2\le r1$。

>原来写成：

>> 目前已知：

>> 1. $r1\le r2$ （已排序）；
>> 1. $r1\le d1<d2\le r1$。

>已修改。(感谢@[zzl_05](https://www.luogu.com.cn/user/105230)指出)

>---

>添加《$O\left(N\log N\right)$ 做法》一部分。（感谢@[zzl_05](https://www.luogu.com.cn/user/105230)提供 idea 和代码）

非常抱歉在短时间内提交两次题解，还望管理大大通过。

---

## 作者：StudyingFather (赞：15)

先考虑一个朴素的贪心做法。

我们将 $ T_i $ 排序，对于每个 $ T_i $，将其与满足条件且右端点最靠左的区间进行匹配。

这样的复杂度是 $ O(nc) $ 的，~~听说有人过了~~，但这样的解法其实还有很大优化空间。

我们将区间按左端点为关键字排序，建立一个以右端点为关键字的小根堆。

对于每个 $ T_i $，我们将所有左端点小于 $ T_i $ 的区间插入堆（这些区间都将成为候选的可安排区间），接着将所有右端点小于 $ T_i $ 的区间从堆中弹出（因为 $ T_i $ 递增，未来这些区间也不可能被安排）。

执行完上面几步后，堆顶的区间正满足上面朴素做法中的“满足条件且右端点最靠左的区间”，可以与当前 $ T_i $ 匹配。

该算法的复杂度是 $ O(n \log n) $。

```cpp
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
struct seg
{
 int l,r;
 bool operator<(const seg&a)const
 {
  return r>a.r;
 }
}s[20005];
int a[20005],vis[20005];
priority_queue<seg> q;
bool cmp(const seg&a,const seg&b)
{
 return a.l<b.l;
}
int main()
{
 int c,n;
 scanf("%d%d",&c,&n);
 for(int i=1;i<=c;i++)
  scanf("%d",&a[i]);
 sort(a+1,a+c+1);
 for(int i=1;i<=n;i++)
  scanf("%d%d",&s[i].l,&s[i].r);
 sort(s+1,s+n+1,cmp);
 int cur=1,ans=0;
 for(int i=1;i<=c;i++)
 {
  while(cur<=n&&s[cur].l<=a[i])
   q.push(s[cur++]);
  while(!q.empty()&&q.top().r<a[i])
   q.pop();
  if(!q.empty())ans++,q.pop();
 }
 printf("%d\n",ans);
 return 0;
}
```


---

## 作者：yeshubo_qwq (赞：6)

## 思路
贪心加枚举。

显然让鸡按有空时间排序，让牛按最晚时间排序，进行枚举匹配一定最优。

然后枚举每一头牛，再枚举鸡，看有没有可以匹配的。

具体细节见代码。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
    int l,r;
}a[20001];
bool cmp(node x,node y){//按最晚时间排序 
    return x.r<y.r;
}
int n,m,i,j,t[20010],k,ans;
int main(){
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++)scanf("%d",&t[i]);
    sort(t+1,t+n+1);
    for(i=1;i<=m;i++)scanf("%d%d",&a[i].l,&a[i].r);
    sort(a+1,a+1+m,cmp);
    k=n;
    for(j=1;j<=m;j++){//枚举牛 
        for(i=1;i<=n;i++)//枚举鸡 
            if(a[j].l<=t[i]&&t[i]<=a[j].r){//可以匹配 
                t[i]=-1;//匹配成功把时间设成-1防止重复匹配 
                k--;//未匹配鸡-1
                ans++; 
                break;//匹配成功就退出 
            }
        if(k==0)break;//优化：鸡用完了就结束 
    }
    printf("%d",ans);
    return 0;
}
```


---

## 作者：曹老师 (赞：5)

~~来个炒鸡简单的解法~~

**牛按照B排序！牛按照B排序！牛按照B排序！**

可以理解Bi 为牛的紧急程度

（第一次做的时候是按照A排序 结果过了50

牛越紧急 我们就越把最开始的鸡给它

哦对了 还要把鸡升序排序

**不必二分！！！**

拿出牛来找鸡 被找过就标记 不满足就返回（详细看代码

时间复杂度 O(n*m) ~~亲测能AC！~~

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#define MAXN 100005
#define LL long long
#define INF 2147483647
#define MOD 1000000007
#define free(s) freopen("s.txt","r",stdin);
#define lowbit(x) ((x&(-x))) 
#define debug(x) cout<<x<<endl;
using namespace std;
const int L=20005;
struct node{
    int l,r;
};
bool cmp(const node &a,const node &b)
{
    return a.r<b.r;
}
node cow[L];
int n,m,T[L],v[L],ans;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&T[i]);
    for(int i=1;i<=m;i++)
        scanf("%d%d",&cow[i].l,&cow[i].r);
    sort(T+1,T+n+1);
    sort(cow+1,cow+m+1,cmp);
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
        {
            if(T[j]>=cow[i].l&&T[j]<=cow[i].r&&!v[j])
            {
                ans++;
                v[j]=1;
                break;
            }
            if(T[j]>cow[i].r)
                break;			
        }

    printf("%d",ans);
    return 0;
} 
```

---

## 作者：X_o_r (赞：4)

(Analysis by Nick Wu) 

Let's consider the chicken that has the earliest time preference for helping a cow out. If no cow wants to cross at that time, then we can ignore that chicken. Otherwise, we have some cows that we can assign to that chicken. Intuitively, we want to assign that chicken to the cow that stops wanting to cross the road the earliest, as this gives us the most flexibility to assign chickens to cows in the future. 

翻译：让我们考虑一下最早期帮助一头母牛的鸡。如果没有一只母牛想在那个时候交叉，那么我们可以忽略那只鸡。否则，我们有一些奶牛，我们可以分配给那只鸡。直觉上，我们想要把这只鸡分配给那只停止想要越过马路的牛，因为这给了我们最大的灵活性，以便今后将鸡分配给母牛。

Here is Brian Dean's code.






```cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
typedef pair<int,int> pii;
multiset<int> chickens;
vector<pii> cows;
int C, N;
int main(void)
{
  ifstream fin("helpcross.in");
  ofstream fout("helpcross.out");
  fin >> C >> N;
  int x, y, total=0;
  for (int i=0; i<C; i++) { fin >> x; chickens.insert(x); }
  for (int i=0; i<N; i++) { fin >> x >> y; cows.push_back(pii(y,x)); }
  sort (cows.begin(), cows.end());
  for (int j=0; j<N; j++) {
    auto which_chicken = chickens.lower_bound(cows[j].second);
    if (which_chicken != chickens.end() && *which_chicken <= cows[j].first) {
      total++;
      chickens.erase(which_chicken);
    }
  } 
  fout << total << "\n";
  return 0;
}
```
（搬运至USACO：http://usaco.org/current/data/sol\_helpcross\_silver\_feb17.html）
其实这道题是一道典型的贪心题，先按线段右端点排序，然后利用堆或者集合尽量满足每一个点就好了


---

## 作者：MC_Launcher (赞：3)

#### 第一眼我一看以为这是个橙题

恩没错，把牛和鸡都按左端点排序然后贪心一下就行

结果呢，我获得了~~50分的~~好成绩

思路：先按牛左端点排序并把鸡排序，然后将牛和鸡都从一开始记录，如果这只牛的左端点比鸡的时间要晚，那么继续遍历下一只鸡，否则遍历下一只牛。如果鸡和牛符合，都加一，都遍历下一个

但是$50tps$，为什么呢？

肯定是有某种情况，如果一只牛把另一只牛时间覆盖住了，如图

![](https://cdn.luogu.com.cn/upload/image_hosting/hmrn33m3.png)

因此我没了？那怎么办呢？

这题瞬间又变绿了（雾

那是遍历方式的问题啊，我看看暴力能不能过，诶，居然又是50分（AC后试的），这，排序方式还有问题诶，应该按右端点排序。

为什么呢？结束时间越早的牛也就越急着过马路（~~牛也不一定要过马路啊~~），那么将符合的鸡分配给更紧急的牛显然是更优的，因为剩下的那只牛还有更多的时间，也就可能有更多选择（~~你的可能无限~~）

然后呢就AC了，还没开氧气，有时候也不要多看题解，数据可能很水啊。

上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct cow
{
	int left,right;//牛，左端点，右端点
};
bool cmp(cow a,cow b)
{
	return a.right<b.right;//按右端点排序
}
int main()
{
	int n,c;//rt
	cin>>c>>n;
	cow a[20001];//牛结构体数组
	int b[20001];//鸡数组
	for(int i=1;i<=c;i++)cin>>b[i];
	for(int i=1;i<=n;i++)cin>>a[i].left>>a[i].right;
	sort(a+1,a+n+1,cmp);//排序
	sort(b+1,b+c+1);
	int ans=0;
	for(int i=1;i<=n;i++)//遍历牛
	{
		for(int k=j;k<=c;k++)//遍历鸡
		{
			if(a[i].left<=b[k]&&a[i].right>=b[k])//如果满足题目条件就ans++
			{
				ans++;
				j=k+1;
				break;
			}
		}
	}
	cout<<ans;//输出
}
```
这个还是因为数据太水才能过，有没有更好一点的？

我太菜了，目前还没发现...

#### 题解千万条，理解第一条。直接抄题解，棕名两行泪




---

## 作者：MyukiyoMekya (赞：2)

这题怎么贪心其他题解已经说得很清楚了，这里就不就说明，但是我发现我们维护鸡的时候要实现一种这样的数据结构：

有一个数组 $a$ 。

1. 删除某个 x
2. 查询 $\ge y$ 的最小的 $x$

很显然可以用平衡树对吧，但是我们可以用二分来解决它。

一个朴素的思想就是先把 $a$ 排个序，然后删除就打个标记，然后每次二分如果答案被标记就往后跳到没标记位置。

很显然，把 $a$ 中数字全弄成一样等一些毒瘤数据可以把它卡成平方复杂度。

然后我们发现其实可以用并查集来优化往后跳这个操作，一开始所有点的父亲全部指向自己，然后二分出一个位置就直接去比较他的根，如果可以就把这个根往后指（就是删除操作）。

注意先要去重一下，然后记个出现次数 cnt。

复杂度依然是 $\mathcal O(n\log n)$ ，但是比 set 和堆啥的常数小很多，所以没怎么特地卡常就拿到了最优解（开了O2）。

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
#define ln puts("")
using namespace std;
const int MaxN=20050;
struct Node
{
	int l,r;
	inline bool operator < (const Node &nt) const
	{
		return r<nt.r;
	}
}a[MaxN];
template <class t> inline void read(t &s){s=0;
reg int f=1;reg char c=getchar();while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
while(isdigit(c))s=(s<<3)+(s<<1)+(c^48),c=getchar();s*=f;return;}
template<class t,class ...A> inline void read(t &x,A &...a){read(x);read(a...);}
template <class t> inline void write(t x){if(x<0)putchar('-'),x=-x;
int buf[21],top=0;while(x)buf[++top]=x%10,x/=10;if(!top)buf[++top]=0;
while(top)putchar(buf[top--]^'0');return;}
int f[MaxN],b[MaxN],cnt[MaxN];
inline int getf(int x)
{
	return f[x]==x?x:f[x]=getf(f[x]);
}
signed main(void)
{
	int n,m;read(n,m);
	for(int i=1;i<=n;++i)
		read(b[i]);
	sort(b+1,b+n+1);
	cnt[1]=1;
	{
		reg int top=1;
		for(int i=2;i<=n;++i)
			if(b[i]!=b[i-1])
				b[++top]=b[i],cnt[top]=1;
			else
				++cnt[top];
		n=top;
	}
	for(int i=1;i<=n+1;++i)
		f[i]=i;
	b[n+1]=1e9;
	for(int i=1;i<=m;++i)
		read(a[i].l,a[i].r);
	sort(a+1,a+m+1);
	reg int Ans=0;
	for(int i=1;i<=m;++i)
	{
		reg int l=1,r=n,ans=n+1,mid;
		while(l<=r)
		{
			mid=(l+r)>>1;
			if(b[mid]>=a[i].l)
				ans=mid,r=mid-1;
			else
				l=mid+1;
		}
		if(b[getf(ans)]<=a[i].r)
		{
			++Ans,--cnt[getf(ans)];
			if(!cnt[getf(ans)])
				f[getf(ans)]=getf(ans)+1;
		}
	}
	write(Ans),ln;
	return 0;
}
```



---

## 作者：MVP_Harry (赞：2)

萌新刚学平衡树，这里提供一个平衡树的解法。

这道题其实可以大致分为两个部分。

- 贪心（区间问题）
- $O(logn)$的查询

对于第一步来说，我们先对每条线段以右端点为关键词排序。然后对于第$i$只牛，贪心地选择还没有被选择过的鸡中，$A_i \le T_j$，且$T_j - A_i$最小。

证明如下：否则假设对第$i$只牛，选择$T_k \ge A_i$，且$\exists A_i \le T_j < T_k$。观察到如果区间$P$覆盖区间$Q$，则不影响结果；否则，因为我们已经排过序了，$A_i$的时间较小，则很明显选择满足条件的最小时间不会对结果产生负面影响，因此，贪心是正确的。

于是，我们接下来考虑如何高效地查找这样的$T_j$。其他几位大佬已经提过了几种简便的方法，这里我提供一个平衡树的解法。其实这颗平衡树只需要支持insert, delete和查询后继即可，不过我们这里要对后继进行一个小修改（大于等于而不是大于，类似于```lower_bound```和```upper_bound```的区别）

```
int suc(int p, int x) {
	if (!p) return INF;
	if (v[p] < x) return suc(son[p][1], x);
	else return min(v[p], suc(son[p][0], x));
}
```

```main```函数主题框架如下：

```
int main() {
	ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> C >> N; //同题目
    rep(i, 1, C) { int temp; cin >> temp; ins(R, temp); } //鸡的时间，直接调用insert函数
    rep(i, 1, N) cin >> T[i].l >> T[i].r; //牛的左端点和右端点
    sort(T + 1, T + N + 1, cmp); //排序
    int ans = 0;
    rep(i, 1, N) {
    	int l = T[i].l, r = T[i].r;
		int res = suc(R, l); //后继
		if (res <= r) {
			++ans;
			del(R, res); //如果后继满足条件，删除这个点
		}    	
    }
    cout << ans << endl;
	return 0;
}
```

如果有兴趣的话，可以参考我的Treap代码：

```
int sum = 0, R = 0;
int size[maxn], v[maxn], num[maxn], rd[maxn], son[maxn][2];

void pushup(int p) {
	size[p] = size[son[p][0]] + size[son[p][1]] + num[p];
}

void rotate(int &p, int d) { //d = 0 -> 左旋
	int k = son[p][d ^ 1]; //p的右儿子
	son[p][d ^ 1] = son[k][d]; //p的右儿子变成了k的左儿子
	son[k][d] = p; //把k的左儿子变成p
	pushup(p), pushup(k); //更新p和k
	p = k; //换根
}

void ins(int &p, int x) { //insert 
	if (!p) {
		p = ++sum;
		size[p] = num[p] = 1;
		v[p] = x;
		rd[p] = rand();
		return ;
	} 
	if (v[p] == x) {
		++num[p], ++size[p];
		return ;
	}
	int d = (x > v[p]);
	ins(son[p][d], x);
	if (rd[p] < rd[son[p][d]]) rotate(p, d ^ 1);
	pushup(p);
}

void del(int &p, int x) {
	if (!p) return ;
	if (x < v[p]) del(son[p][0], x);
	else if (x > v[p]) del(son[p][1], x);
	else {
		if (!son[p][0] && !son[p][1]) {
			--num[p], --size[p];
			if (num[p] == 0) p = 0;
		} else if (son[p][0] && !son[p][1]) {
			rotate(p, 1);
			del(son[p][1], x);
		} else if (!son[p][0] && son[p][1]) {
			rotate(p, 0);
			del(son[p][0], x);
		} else {
			int d = (rd[son[p][0]] > rd[son[p][1]]);
			rotate(p, d);
			del(son[p][d], x);
		}
	}
	pushup(p);
}

int suc(int p, int x) {
	if (!p) return INF;
	if (v[p] < x) return suc(son[p][1], x);
	else return min(v[p], suc(son[p][0], x));
}
```

---

## 作者：_easy_ (赞：1)

## 思路
此题不难想到直接枚举每一个鸡和牛。如果有合适的就直接匹配就行了。只是排序的时候要记住是按长度来排序，于是不难写出排序的部分：
```cpp
bool cmp(node a,node b){
	return a.c<b.c;//c为长度
}
```
然后是枚举部分：
```cpp
for(int i=1;i<=c;i++){
		for(int j=1;j<=n;j++){
			if(b[j].l<=a[i]&&b[j].r>=a[i]&&!d[i]&&!e[j]){
				ans++;
				d[i]=e[j]=1;
			}
		}
	}
```
最后只需要把这些合并起来就行了。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int c,n,a[20005],cnt=1,ans;
bool d[20005],e[20005],r;
struct node{
	int l,r,c;
}b[20005];
bool cmp(node a,node b){
	return a.c<b.c;
}
int main(){
	cin>>c>>n;
	for(int i=1;i<=c;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i].l>>b[i].r;
		b[i].c=b[i].r-b[i].c;
	}
	sort(a+1,a+c+1);
	sort(b+1,b+n+1,cmp);
	for(int i=1;i<=c;i++){
		for(int j=1;j<=n;j++){
			if(b[j].l<=a[i]&&b[j].r>=a[i]&&!d[i]&&!e[j]){
				ans++;
				d[i]=e[j]=1;
			}
		}
	}
	cout<<ans;
	return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/57093724)

---

## 作者：Violet___Evergarden (赞：0)

# 题意
用 $n$ 个区间去匹配 $c$ 个点，点要在区间之间，每个区间只能匹配一个点，每个点只能被一个区间匹配，问的最多能匹配多少对？
# 思路
将点 $t_1,t_2\cdots t_c$ **从小到大**排序，区间按左边界 $a_1,a_2\cdots a_n$ **从小到大**排序。建立一个**小根堆**，对于每个点 $t_i$，在 $a_j \leq t_i$，即**左边界满足条件的情况下，将右边界入堆**。若 $b_j<t_i$，则这个区间不能配对，将它从堆中删除。对于每个满足要求的右区间 $b_p,b_{p+1}\cdots b_q$，我们要**选择右边界最小的区间**，也就是小根堆中的第一个区间，即 $b_p$，这样可以**使机会较小的区间先匹配**，让答案更优。
# AC CODE
思路懂了实现就简单了~
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
const int kMaxN=2e4+1;
int a[kMaxN],ans;
struct COW
{
  int l,r;
}cow[kMaxN];
int c,n;
int hp[kMaxN],num;//手写堆yyds
void Up(int x)//堆的上浮函数
{
  int now1=x;
  while(now1/2)
  {
    int now2=now1;
    now1/=2;
    if(hp[now1]>hp[now2])swap(hp[now1],hp[now2]);
    else break;
  }
}
void Down(int x)//堆的下沉函数
{
  int now1=x;
  while(now1*2<=num)
  {
    int now2=now1;
    now1*=2;
    if(now1+1<=num&&hp[now1+1]<hp[now1])now1++;
    if(hp[now2]>hp[now1])swap(hp[now2],hp[now1]);
    else break;
  }
}
void Push(int x)//堆的插入函数
{
  hp[++num]=x;
  Up(num);//将加入的数上浮使其满足堆性质
}
void Pop(int x)//堆的删除函数
{
  swap(hp[x],hp[num]);//将删除的数与最后一个数交换
  num--;//删除这个数
  Down(x);//因为我们将最后一个数往前换了，所以要将交换后在位置x的数下沉使其满足堆性质
}
bool cmp(COW x,COW y)
{
  return x.l<y.l;
}
int main()
{
cin>>c>>n;
for(int i=1;i<=c;i++)
{
  cin>>a[i];
}
for(int i=1;i<=n;i++)
{
  cin>>cow[i].l>>cow[i].r;
}
sort(a+1,a+c+1);
sort(cow+1,cow+n+1,cmp);//将区间和点排序
for(int i=1,j=1;i<=c;i++)//枚举每个点
{
  for(;j<=n&&cow[j].l<=a[i];j++)
  {
    Push(cow[j].r);//将左区间满足要求的区间的有区间的入堆
  }
  for(;num&&hp[1]<a[i];)//当前的对顶不能满足条件时
  {
    Pop(1);//将不满足要求的区间删除
  }
  if(num)//将不满足条件的去掉后，剩下的对顶一定是满足要求且右区间最小的
  {
    ans++;//统计答案
    Pop(1);//这个区间已经匹配过点了所以要将它删除
  }
}
cout<<ans;
return 0;
}
```
# 时间复杂度
给点排序的时间是 $O(c\log(c))$。

给区间排序的时间是 $O(n\log(n))$。

枚举点的时间是 $O(c)$。

用堆维护 $n$ 个区间是的时间是 $O(n\log(n))$。

所以总时间复杂度是 $O(c\log(c)+n\log(n))$，轻松AC。

---

