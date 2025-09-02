# Supermarket

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4062

[PDF](https://uva.onlinejudge.org/external/13/p1316.pdf)

## 样例 #1

### 输入

```
4 50 2 10 1 20 2 30 1
7 20 1 2 1 10 3 100 2 8 2 5 20 50 10```

### 输出

```
80 
185```

# 题解

## 作者：LlLlCc (赞：16)

  看了题解，感觉大多都用堆和并查集，那我就来一发不一样的，动态规划（~~我不会告诉你我只会dp~~）
  
  先看看数据，嗯，n<=10000,n方刚好卡过去。
  
  我们先不管那个时间条件，每个物品只能取一次，有自己的价值，还有代价（取这件物品要耗1个单位时间）。这不就是一道典型的01背包吗?
  
  代码：
  ```
f[j]=max(f[j],f[j-1]+c[i])
```

现在，我们再来思考一下加入时间限制后转移方程应该是怎样的。首先，根据题目描述，我们肯定会知道，每个物品只能在规定的时间取，过了就不能取了。再思考一下，发现每个物品只会影响到在他规定时间内的状态，也就是j这层枚举空间的循环只需要到他过期的时间d[i]就行了，因为后面的取不到第i个物品。

因为每个物品只能取一次，倒着枚举这层j就行了（不懂的可以看看《背包九讲》）

代码：
```
for (int i=1;i<=n;i++)
    for (int j=a[i].v;j;j--)
      f[j]=max(f[j],f[j-1]+a[i].c)
```


但是！

这样还是不行，为什么呢？

我们拿个样例来说明一下：

2

3 2

5 1

按照我们刚才的思路，来模拟一遍：

f：3 ， 3

f：5 ， 3

？？？？？

这和我们推算出的答案不符，这又是为什么呢？

再观察一下这个转移方程，我们每个物品都是枚举到自己的规定时间，而规定时间后的就不受影响了，所以就可能更新不了前面物品的状态，可能更新不了答案。

这该怎么解决呢？

想想，之所以更新不了之前物品的状态是因为该物品的规定时间比前面物品短，那么我们只要排序一趟不就完美解决了吗？

代码如下：
```
#include<bits/stdc++.h>
#define maxn 10005
using namespace std;
int f[maxn],n,Ans;
struct lc{
    int v,c;
    bool operator <(const lc b)const{return v<b.v;}
}a[maxn];
inline int read(){
    int ret=0;char ch=getchar();
    while (ch<'0'||ch>'9') ch=getchar();
    while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
    return ret;
}
int main(){
	while (cin>>n){
	memset(f,0,sizeof f);
    for (int i=1;i<=n;i++) a[i].c=read(),a[i].v=read();
    sort(a+1,a+n+1);Ans=0;
    for (int i=1;i<=n;i++)
    for (int j=a[i].v;j;j--) f[j]=max(f[j],f[j-1]+a[i].c),Ans=max(Ans,f[j]);
    printf("%d\n",Ans);
}
    return 0;
}
```

谢谢支持！！！

---

## 作者：高天 (赞：14)

 首先有一个很明显的贪心思路。
 
 就是将商品按照日期从先到后排序，然后遍历每一个商品，如果当前这个商品过期时间之前的每一天没有全部安排完，那就将这个商品选中。
 
 如果这个商品过期时间之前已经满了，那就在前面挑一个价值最小的商品换出来，然后再将当前这个商品放回去。因此维护一个堆就可以了。
 

但是这题还可以用并查集来思考，用并查集来维护每一个数组被使用的情况。
        
即先将商品按照利润排序，然后贪心的先将利润大的商品卖出。
        
因此我们需要判断对于当前这个商品来说，
        
过期日期之前是否还有空余天数来将这个商品卖出，
        
因此可以用并查集来维护数组中的每一个位置。

代码：

```cpp
//商品-并查集
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

const int N = 10005;
struct Node {
	int val, day;
	bool operator < (const Node &next) const {
		return val > next.val;
	}
} product[N];

int n, father[10005];

int find(int x) {
	if(father[x] == x)
		return x;
	return father[x] = find(father[x]);
}
int main() {
	while(cin >> n) {
		int maxDay = 0;
		for(int i = 1; i <= n; i++) {
			cin >> product[i].val >> product[i].day;
			maxDay = max(maxDay, product[i].day);
		}
		sort(product + 1, product + n + 1); //排序
		for(int i = 1; i <= maxDay; i++) { //并查集初始化
			father[i] = i;
		}
		int ans = 0;
		for(int i = 1; i <= n; i++) {
			int target = find(product[i].day); //能卖第i个物品的天数 target
			if(target > 0) {
				ans += product[i].val;
				father[target] = target - 1;
			}
		}
		cout << ans << endl;
	}
	return 0;
}
```


---

## 作者：123ZDQ (赞：12)

这道题和P2949非常相似。

### 法一（堆）

以结束时间从小到大排序，贪心地选择当前天数t能卖出的最有价值的t个商品，用小根堆维护，复杂度O(NlogN)


### 法二（并查集）

（这题和P2949的区别是D和N同阶，且天数限制就是Dmax）

考虑另一种贪心思路：以价值从大到小排序，考虑**先卖出价值大的商品**，并且对于每个商品都在过期前尽可能晚卖掉，即**占用较晚的时间**。显然对于某一个商品，将时间调前，答案不会更优

可以用并查集维护**日期的占用情况**

- 初始时每一天为一个集合
- 对于某个商品的di，查询di的树根，记为**r**
- 若**r**>0，将商品在第**r**天卖出，并合并**r**和**r-1**，令**r-1**为**r**的父节点，累加答案

每一个日期所在集合的**root**就是从它开始往前数（包括它自己）第一个空闲的日期。

使用路径压缩优化的并查集，总复杂度O(NlogN）

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int N=10010;
int n;
struct work{int d,p;}w[N];
int f[N];
int ans;

bool cmp(const work &x,const work &y){return x.p>y.p;}

int find(const int &x){
    if(f[x]<0)return x;
    return f[x]=find(f[x]);
}

int main(){
    while(scanf("%d",&n)!=EOF){
        ans=0;memset(f,-1,sizeof f);//初始化
        for(int i=1;i<=n;i++)scanf("%d%d",&w[i].p,&w[i].d);
        sort(w+1,w+1+n,cmp);//按价值从大到小排序
        for(int i=1,r;i<=n;i++)
            if((r=find(w[i].d))>0)//当前di的root即为最晚能卖出的时间，若为0就卖不了
            	{ans+=w[i].p;f[r]=r-1;}//若不为0，卖掉，统计答案，把该日期指向“前一个空的日期”
        printf("%d\n",ans);
    }
}
```


---

## 作者：陷语 (赞：7)

## Supermarket

**题目大意：**

超市有n种商品，每个商品都有一个利润和保质期，超市每天只可以卖一种商品，求超市在保质期内卖出商品可获得的最大利益。

**思路：**

读完题目我们的脑海里一般都会浮现出一个想法，就是在最大的保质期时间内找出利润最大的商品卖掉，这个贪心思路是正确的，但是如何实现呢？通过思考我们会发现我们的每一个选择都会被商品的保质期影响，即我们必须在商品的保质期内卖出商品，所以我们可以将保质期与可选择的次数相结合，得到以下贪心思路：

将每种商品的保质期按从小到大顺序排序，得到一个有序的时间。

使用小根堆维护已经选择商品的价值，然后继续选择商品，这时会有这两种情况：

1.当前商品的保质期大于已经选择商品的次数，直接将此商品加入选择之中；

2.当前商品的保质期等于已经选择商品的次数，将这个商品的价值与小根堆的堆顶作比较，如果大于即替换，否则不变。

**证明：**

设：x1 < x2 > x3，保质期分别为1 1 2；

当选择为空时，直接选择x1，当选择一种保质期为1天时，将x2和x1作比较，发现x2 > x1，将x1替换。

很明显可以发现当前局部最优并不会影响全局最优。


**附上代码：**

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;
const int N = 10100;

struct goods{
    int val, day;
    bool operator < (const goods a) const {
        return day < a.day;
    }
} a[N];

struct cmp{
    int val;
    bool operator < (const cmp a) const {
        return val > a.val;
    }
};

int n, ans;

int main() {
//	freopen("in.txt", "r", stdin);
    while(cin >> n) {
        ans = 0;
        memset(a, 0, sizeof(a));
        priority_queue <cmp> que;
        
        for(int i = 1; i <= n; ++i) scanf("%d %d", &a[i].val, &a[i].day);
        sort(a + 1, a + 1 + n);//按时间从小到大排序 
        
        for(int i = 1; i <= n; ++i) {
            if(a[i].day > que.size()) que.push((cmp) {a[i].val});
            else if(a[i].day == que.size() && a[i].val > que.top().val) {
                que.pop();
                que.push((cmp) {a[i].val});
            }
        }
        
        while(!que.empty()) {
            ans += que.top().val;
            que.pop();
        }
        printf("%d\n", ans);
    }
    return 0;
}
```

需要注意的是，这题在while()里面用~scanf会出问题，使用cin则不会，~~这就是我WA了n的原因……~~

---

## 作者：一只书虫仔 (赞：6)

[UVA1316 Supermarket](https://www.luogu.com.cn/problem/UVA1316)

#### Description

> 给定 $n$ 个物品，每个物品都有价值 $p_i$ 和过期时间 $d_i$，卖掉一个物品可获得他的价值，要用 $1$ 的时间。           
> 求最大收益。            
> $0 \le n \le 10^4$，$1 \le p_i,d_i \le 10^4$

#### Solution

并查集。

首先读入，然后按照价值排序。

接下来就是并查集的初始化工作，我 的 父 亲 是 我。（当然直接让父亲是 $-1$ 也行）

接下来就是按照过期时间找祖宗，记得找的循环要开到 $10^4$。

每次运行一次 $\text{get}$ 来判断有没有祖宗。（即现在这个过期时间有没有物品）

然后对答案进行累加，记得卖掉要用时间的！

最后输出答案即可。

要注意的几点：

1. 记得压缩路径
2. UVA 毒瘤读入，所以要用 `while (scanf("%d", &n) != EOF)`（当然 `while (~scanf("%d", &n))` 也可以）

因为我这个 UVA 号有 bug，所以无法判断这种读入可不可以过。（听说要用 cin，没尝试过）

#### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

struct node {
	int p, d;
} e[10086];

int father[100086];

int get (int cur) {
	if (father[cur] == cur) return cur;
	father[cur] = get(father[cur]);
	return get(father[cur]);
}

bool cmp (node u, node v) {
	return u.p > v.p;
}

int main () {
	int n;
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; i++)
			scanf("%d%d", &e[i].p, &e[i].d);
		sort(e + 1, e + n + 1, cmp);
		for (int i = 1; i <= n; i++)
			father[i] = i;
		int ans = 0;
		for (int i = 1; i <= 10000; i++)
			if (get(e[i].d)) {
				ans += e[i].p;
				father[get(e[i].d)] = get(e[i].d) - 1;
			}
		printf("%d\n", ans);
	}
	return 0;
}
```

By Shuchong           
2020.7.26

---

## 作者：Viva_Hurricane (赞：4)

```
看了一下其他的题解，~~发现都看不懂~~，发现都很牛逼（nlogn）。
于是本蒟蒻决定发一个n^2的贪心。
主要思路：
1.既然要使利润最高，那每天都要卖出最好的，但是从第一天开始算的话会影响到之后的，所以我们从最后一天开始。
2.每一天都卖出能卖出的商品中利润最高的。

#include<cstdio>
#include<algorithm>
using namespace std;
int n;
int maxn,m;//maxn存每组商品中最长的保质期，m存每天能卖出的最大价值的商品。
int ans;
bool f[10010];
struct item{
	int v;//利润。
	int t;//保质期。
};
item g[10010];
bool cmp(item a,item b){
	return a.t>b.t;
}
int main(){
	while(scanf("%d",&n)!=EOF){
		maxn=0;//对于T组输入每一组都要初始化。
		m=0;
		ans=0;
		for(int i=1;i<=n;i++){
			scanf("%d%d",&g[i].v,&g[i].t);
			f[i]=true;//f[i]==true表示第i件商品没有被卖出。
			if(g[i].t>maxn)
				maxn=g[i].t;//找出保质期最长的那一个。
		}
		sort(g+1,g+n+1,cmp);//按保质期从大到小排序。
		for(int i=maxn;i>0;i--){
			int k;//记录要卖出的商品。
			for(int j=1;j<=n&&g[j].t>=i;j++){
            	//                 /\
                //保质期必须要大于等于当前的日期才能卖。
				if(f[j]==true&&g[j].v>m){
                	//找出利润最大的那个。
					k=j;
					m=g[j].v;
				}
			}
			f[k]=false;//这件商品已经卖出去了。
			ans+=m;
			m=0;
		}
		printf("%d\n",ans);
	}
	return 0;
}

请大家不要抄袭。
如果时间复杂度算错了请大家不要在意。
如果不喜欢可以去看看并查集或堆的题解。
```

---

## 作者：Rye_Catcher (赞：2)

- 题目链接：

   https://www.luogu.org/problemnew/show/UVA1316
   
- 思路：

   根据题目意思，我们需要用到贪心的思想，越晚过期的商品当然是越晚卖好。同时你假如有多个商品**必须**在同一天卖出，当然是卖收益多的好。
   
   于是我们就有以下方法：首先将每个商品的过期时间按从小到大排序，同时建立一个小根堆，然后遍历这些商品。
   
   如果商品过期时间大于堆中商品个数，说明前面还有些天是没有卖东西的，当然可以把这个商品插入堆中。
   
   类似的，如果商品过期时间等于堆中商品个数，就比较此商品的收益和堆顶的收益哪个大。如果堆顶的收益小，就把他POP出堆顶，然后将此商品插入到堆中；相反，如果堆顶的收益大，那就不进行操作。
   
   
- 代码：

```
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cctype>
using namespace std;
const int maxn=10008;
struct Goods{
    int p,d;
}s[maxn];
struct Small_Heap{
    int n,heap[maxn];
    inline void up(int fa){
        while(fa>1){
            if(heap[fa]<heap[fa>>1]){
                swap(heap[fa],heap[fa>>1]);
                fa=fa>>1;
            }
            else break;
        }return ;
    }
    inline void insert(int v){
        heap[++n]=v;
        up(n);
        return ;
    }
    inline void down(int fa){
        int s=fa<<1;
        while(s<=n){
            if(s<n && heap[s]>heap[s+1])s++;
            if(heap[s]<heap[fa]){
                swap(heap[s],heap[fa]);
                fa=s,s=fa<<1;
            }
            else break;
        }return ;
    }
    inline void extract(){
        heap[1]=heap[n--];
        down(1);
    }
    inline int GetTop(){
        return heap[1];
    }
}a;
inline bool cmp(const Goods &a,const Goods &b){
    return a.d<b.d;
}
template<class T>inline void read(T &x){
    x=0;int ne=0;char c;
    while(!isdigit(c=getchar()))ne=c=='-';
    x=c-48;
    while(isdigit(c=getchar()))x=(x<<3)+(x<<1)+c-48;
    x=ne?-x:x;
    return ;
}
int main()
{
    int n,x;
    while(cin>>n){
      int ans=0;  //堆中商品个数
      for(register int i=1;i<=n;i++){
        read(s[i].p),read(s[i].d);
      }
      sort(s+1,s+1+n,cmp);
//	  for(register int i=1;i<=n;i++)cout<<s[i].p<<' '<<s[i].d<<endl;
      for(register int i=1;i<=n;i++){
          if(s[i].d==a.n){
            if(s[i].p>a.GetTop()){
               a.extract();
               a.insert(s[i].p);			   
            }  
          }
          else if(s[i].d>a.n){
              a.insert(s[i].p);
          }
      }
      for(register int i=1;i<=a.n;i++){
       //   cout<<a.heap[i]<<endl;
          ans+=a.heap[i];
          a.heap[i]=0;
      }a.n=0;
      printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：fanfansann (赞：1)

贪心+二叉堆优化
贪心策略：对于 $t$ 天,我们需要在保证不卖出过期商品的前提下,卖出利润前 $t$ 大的商品。
因此我们可以把商品按照过期时间排序,然后建立一个小根堆,对于每一个数而言,如果说它的过期时间大于当前小根堆的个数,那么我们可以直接将这个货物的价值加入进来,如果说当前过期时间等于这个小根堆堆内的个数,那么我们就需要对比一下,如果说这个货物的价值,是高于小根堆的堆顶的话,那么我们就将小根堆堆顶弹出,然后push我们这个新货物,因为新货物明显是更加优于堆顶的老货物的，因为每次都选择最优的选项，保证了算法的正确性。

注意输入的时候如果用`while(scanf("%d",&n)!=EOF)`就会TLE，~~垃圾UVA~~
```cpp

#include<iostream>
#include<bits/stdc++.h>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<queue>
#include<bitset>
#include<limits.h>
#define ls (p<<1)
#define rs (p<<1|1)
#define mid (l+r>>1)
#define over(i,s,t) for(register int i = s;i <= t;++i)
#define lver(i,t,s) for(register int i = t;i >= s;--i)
//#define int __int128
using namespace std;
#undef mid
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> PII;

const int N = 1e5+7;
const ll mod = 1e9+7;
const ll INF = 1e15+7;
const double EPS = 1e-10;
const int base = 131;

int n,m;
PII a[N];
priority_queue<int,vector<int>,greater<int> >p;
int main()
{
    while(cin>>n)
    {
        if (n==0)
        {
            puts("0");
            continue;
        }
        for(int i=1; i<=n; i++)
        {
            scanf("%d%d",&a[i].second,&a[i].first);
        }
        sort(a+1,a+1+n);
        for(int i=1; i<=n; i++)
        {
            if (a[i].first>p.size())
                p.push(a[i].second);
            else if(a[i].first==p.size() && a[i].second>p.top())
            {
                p.pop();
                p.push(a[i].second);
            }
        }
        long long ans=0;
        while(!p.empty())
        {
            ans+=p.top();
            p.pop();
        }
        printf("%lld\n",ans);
    }
    return 0;
}

```



---

## 作者：ZRHan (赞：1)

**优先队列+贪心**

贪心策略：从第10000天开始，每天尽量选没过期的最贵的就行了。


对于第i天最贵的商品：

1.如果把这个最贵的留给前面（前面指第1~i-1天）去选：因为从前往后可选的商品不断减少，前面说不定可以选更贵的，所以留给前面不如留给第i天。

2.如果这个最贵商品既不留给前面，第i天也不选，那结果肯定不如第i天选最贵的。

**Cpp**
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int maxn = 1e4+5, inf = 0x3f3f3f3f;

struct node{
	int p, d;
	
	static inline bool cmp(node &a, node &b)
	{
		return a.d < b.d;//把过期时间排序 
	}
	
	bool operator< (node b) const
	{
		return p < b.p;//优先队列价值排序 
	}
	
} num[maxn];
priority_queue<node, vector<node>, less<node> > q;

int n;
int main()
{
	while(cin >> n)  //while(scanf("%d", &n) != -1)会迷之TLE 
	{
		while(!q.empty()) q.pop();
		
		
		int maxd = -inf;
		for(int i=1; i<=n; ++i)
		{
			scanf("%d%d", &num[i].p, &num[i].d);
			maxd = max(num[i].d, maxd);//记录最大过期时间 
		}
		sort(num+1, num+n+1, node::cmp);
		int j = n;
		
		int ans = 0;
		for(int i=maxd; i>=1; --i)
		{
			while(j>0 && num[j].d >= i) q.push(num[j]), --j;
            //令num[j]后面的过期时间都大于当前时间，并把它们入队。也就是说队列里都是第i天可选的
			if(!q.empty()) ans += q.top().p, q.pop();//第i天选了该商品，1~i-1天就不能再选了，所以出队
		}
		
		printf("%d\n", ans);
	}
	return 0;
}
```


---

## 作者：黄城焱 (赞：1)

写过智力大冲浪吗？

其实这道题可以用与其差不多的思想。

先用一个sort按价值降序排列。

bool com(const jj &x,const jj &y)
{
    return x.f>y.f;
}

sort(a+1,a+n+1,com);

现在是核心思想了。从可用天开始如果这个商品还没买出去，因为已经是目前最大价值，所以就把找到的商品买出。

	for(i=1;i<=n;i++)
	{
		for(j=a[i].t;j>=1;j--)
		{
			if(z[j]==0)
			{
				z[j]=1;
				a[i].f=0;
				break;
			}
		}
	}
所以说总代码如下：
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
struct jj
{
	int t,f;
}a[10000];
bool z[10000]={0};
bool com(const jj &x,const jj &y)
{
    return x.f>y.f;
}
int main()
{
	int n,i,j;
	while(cin>>n)
	{
		int s=0;
		memset(a,0,sizeof(a));
		memset(z,0,sizeof(z));
	for(i=1;i<=n;i++)
	{
	    cin>>a[i].f>>a[i].t;
	    s+=a[i].f;
	}
	sort(a+1,a+n+1,com);
	for(i=1;i<=n;i++)
	{
		for(j=a[i].t;j>=1;j--)
		{
			if(z[j]==0)
			{
				z[j]=1;
				a[i].f=0;
				break;
			}
		}
	}
	for(i=1;i<=n;i++)
	s-=a[i].f;
	cout<<s<<endl;
	}
	return 0;
}
```


---

## 作者：abc_de (赞：0)

#  动态规划
其实这道题有点像01背包，思路大体都是一样的。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,dp[10001];
struct A{
	int sy;//价格
	int tim;//时间
}heap[10001];
bool cmp(A x,A y){//排序
	if(x.tim!=y.tim) return x.tim<y.tim;//优先比较时间
	 return x.sy>y.sy;//否则比价格
}
int main(){
	int ans=0;
	while(cin>>n){
		memset(dp,0,sizeof(dp));//不要忘记初始化
		for(int i=1;i<=n;i++)
		 cin>>heap[i].sy>>heap[i].tim;
		sort(heap+1,heap+n+1,cmp);//排序
		ans=0;//初始化
		for(int i=1;i<=n;i++){
			for(int j=heap[i].tim;j>0;j--){//把之前算的结果算一下
		   	 dp[j]=max(dp[j],dp[j-1]+heap[i].sy);//就看是加上大,还是不加大
		   	 ans=max(ans,dp[j]);
		   }
		}
		cout<<ans<<endl;/输出
	}
	return 0;
}
```


---

## 作者：STOcjyORZ (赞：0)

题目大意：有n件商品，对于每件商品有一个价值和有效日期，过了有效日期的商品不能再出售，每天可以卖出一件商品，问说最大利润是多少。

------------
这个题的贪心＋并查集是一种极为巧妙地办法：
1. 并查集维护的是**一个数组中位置的占用情况**。
1. 而对于贪心，策略便是**优先考虑卖出利润大的商品，并且对每个商品在他过期之前尽量晚卖出**——占用较晚的时间，则对剩下的商品具有决策包容性。


------------
   因此建立一个关于天数的并查集，利用并查集的路径压缩，可以快速找到最晚能卖出的时间（从过期时间往前数的第一个**空闲时间**）

详细细节如下：

```cpp
/**/
using namespace std;
const int N = 10005;
struct state {
	int pi, di;
}s[N];
int n, v[N];
bool cmp(const state& a, const state& b) {
	return a.pi > b.pi;
}
int find(int x) {
	return v[x] == -1 ? x : v[x] = find(v[x]);
}
void init() {
	memset(v, -1, sizeof(v));
	for (int i = 0; i < n; i++) scanf("%d%d", &s[i].pi, &s[i].di);
	sort(s, s + n, cmp);
}
int solve() {
	int ans = 0;
	for (int i = 0; i < n; i++) {
		int k = find(s[i].di);
		if (k) {
			ans += s[i].pi;
			v[k] = k - 1;
		}
	}
	return ans;
}
int main() {
	while (scanf("%d", &n) == 1) {
		init();
		printf("%d\n", solve());
	}
	return 0;
}
```


---

