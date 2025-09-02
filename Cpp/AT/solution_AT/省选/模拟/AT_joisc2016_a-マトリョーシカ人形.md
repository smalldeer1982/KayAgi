# マトリョーシカ人形

## 题目描述

你开了一家卖套娃的店。因此，你向厂家订购了 $N$ 个套娃，这些娃娃被编号为 $1$ 到 $N$，其中第 $i$ 个套娃是一个的直径为 $R_i$ 高度为 $H_i$ 的圆柱体。每个套娃都只能套高和直径严格比它小的套娃。同时只要满足条件，套娃可以嵌套多次。\
有一天，你收到了厂家的来电，告诉你你预定的 $N$ 个娃娃不能一次性全部做完。所以第一批只会送达直径大于等于 $A$ 并且高度小于等于 $B$ 的所有套娃。你需要预先安排出一个方案，使送来的套娃经过若干次嵌套后，没有被套的套娃数量最小。\
由于厂家经常搞事情，所以他会改变 $A$ 和 $B$ 的值，总共 $Q$ 次，因此你需要对每对 $(A,B)$ 都作出回答，询问之间互不干扰。

## 说明/提示

对于全部的数据，$1≤N,Q≤2×10^5,1≤Ri,Hi,Ai,Bi≤10^9$。\
具体子任务限制及得分情况如下表：
|编号|限制|
|-----------:|-----------:|
|1|$N≤10,Q=1$|
|2|$N≤100,Q=1$|
|3|$N,Q≤2000$|
|4|无追加限制|

# 题解

## 作者：NXYorz (赞：5)

考虑这样的套路：对于某一轴排序(当做时间轴)， 然后用数据结构去优化另一个维度。

因为考虑到树状数组很多时候就是与时间轴有关系， 所以考虑树状数组， 而树状数组经
常伴随离散化， 因此这里要离散化。

可以这样构造解：
$A$ 优先从从大到小排序(时间轴)， $B$ 从小到大排序， 需要维护的： 是对于每一个点而言，
如果把这个点当做询问， 答案是什么。 也就是看把点强制转化成询问， 看他的结果是多
少。

可以这样略微证明：

首先对于每一个娃子， 都不可能将在它前面出现的装进去。

对于每一个在当前的娃子之前出现并且高度比当前的娃子高，那么当前的娃子可以被这
个娃子装进去。也就是说这个娃子是不会影响高度大于它并且出现时间比他早的娃子的
答案的。

同理对于每一个在当前的娃子之后出现并且比当前的娃子小的娃子，首先当前娃子是不
会影响这个娃子的答案， 因为他的高度大而且时间晚， 而这个娃子是不可以被当前娃子
装起来的。

因此我们这样做就不会影响其他的点， 于是我们就可以愉快的处理它本身了：

因为这个点后面的高度大， 所以不用管， 而前面出现的点又都是这个点装不下的。 我们
就可以看前面的点最大的答案是多少， 也就是除去当前的点， 前面的那些符合询问条件
的点装起来需要几个， 最后加上这个点本身$+1$ 即可。

现在我们把这些放到另一个维度上来,

![图1](https://cdn.luogu.com.cn/upload/image_hosting/y0pe8czi.png)





这个娃子第一个放， 因此当前如果要把高度范围包括这个娃子的高度， 答案就是 $1$。 然
后我们接着插：

![图2](https://cdn.luogu.com.cn/upload/image_hosting/a5ngrkab.png)


对于这个新的娃子， 能够被老的娃子套住。 所以如果高度范围允许老娃子的话， 答案是
$1$， 如果不允许老娃子但是包括新娃子， 答案也是 $1$。 我们接着插：

![图3](https://cdn.luogu.com.cn/upload/image_hosting/abpf2dyd.png)


接着插入 $3$ 号， 此时 $1$ 号是可以装下 $2$ 号和 $3$ 号的， 但是由于 $2$ 号不能装下 $1$ 号($2$ 比 $1$晚)， 所以如果询问范围包括 $1$ 号， 答案是 $2$。 如果询问不包括一号但是包括另外两个，答案也是 $2$。

如果你用树状数组写过 $LIS$， 就可以发现这是最长不下降子序列了。
如果把这些点还原到二维坐标轴上就是这样：

![图4](https://cdn.luogu.com.cn/upload/image_hosting/p3jopp6r.png)

```cpp

#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 2e5+5;
int n,q,maxn;
int ans[N];
struct JZ {
	int h;
	int r;
	int num;
	bool operator < (const JZ b) const {
		if(r != b.r) return r > b.r;
		return h < b.h;
	}
} a[N],qu[N];
inline int max(int x , int y) {
	return x > y ? x : y;
}
struct Sig {
	int c[N * 2];
	inline int lowbit(int x) {
		return x & -x;
	}
	void Updata(int x , int d) {
		while(x <= maxn) {
			c[x] = max(c[x] , d);
			x += lowbit(x);
		}
	} int check(int x) {
		int tot = 0;
		while(x) {
			tot = max(tot , c[x]);
			x -= lowbit(x);
		} return tot;
	}
} tr;
int b[N*2],L;
inline void lsh() {
	for(int i = 1 ; i <= n ; i++)
		b[i] = a[i].h;
	for(int i = 1 ; i <= q ; i++)
		b[i + n] = qu[i].h;
	sort(b + 1 , b + 1 + n + q);
	L = unique(b + 1 , b + 1 + n + q) - b - 1;
	for(int i = 1 ; i <= n ; i++) {
		a[i].h = lower_bound(b + 1 , b + 1 + L , a[i].h) - b;
		maxn = max(maxn , a[i].h);
	} for(int i = 1 ; i <= q ; i++) {
		qu[i].h = lower_bound(b + 1 , b + 1 + L , qu[i].h) - b;
		maxn = max(maxn , qu[i].h);
	}
} signed main() {
//	freopen("doll.in","r",stdin);
//	freopen("doll.out","w",stdout);
	scanf("%d%d",&n,&q);
	for(register int i = 1 ; i <= n ; i++)
		scanf("%d%d",&a[i].r,&a[i].h);
	for(register int i = 1 ; i <= q ; i++) {
		scanf("%d%d",&qu[i].r,&qu[i].h);
		qu[i].num = i;
	} sort(a + 1 , a + 1 + n);
	sort(qu + 1 , qu + 1 + q);
	lsh();
	int loc = 1;
	for(register int i = 1 ; i <= n ; i++) {
		while(qu[loc].r > a[i].r && loc <= q) {
			int k = tr.check(qu[loc].h);
			ans[qu[loc].num] = k;
			loc++;
		} while(qu[loc].r == a[i].r && loc <= q) {
			if(qu[loc].h < a[i].h) {
				ans[qu[loc].num] = tr.check(qu[loc].h);
				loc++;
			} else break;
		} tr.Updata(a[i].h , tr.check(a[i].h) + 1);
	} while(loc <= q) {
		ans[qu[loc].num] = tr.check(qu[loc].h);
		loc++;
	} for(register int i = 1 ; i <= q ; i++)
	printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：AutomatiC__ (赞：3)

提供一个不需要任何数据结构的做法。

对于题目中“套娃”这样的二维偏序关系，通常考虑将一维排序，另一维特殊处理。

考虑单个询问，若套娃已经按照直径 $R_i$ 升序排序，则每一个递增子序列对应的都是一组从左到右套在一起的套娃，故没有被套的套娃就是递增子序列的数量。

由 Dilworth 定理知，最小链覆盖即为最长反链，所以对于每个询问，我们需要求出最长单调不升子序列。

注意到原序列的最长单调不升子序列等价于翻转序列的最长单调不降子序列，故我们将套娃按照直径 $R_i$ 降序排序，二分求 LIS，即可得到一个 $\mathcal{O}(QN \log N)$ 的在线做法。

若我们离线后按照直径 $A_i$ 降序排序询问，可以得到一个显然的扫描线模型，但在这题并不需要使用数据结构。

回想二分求 LIS 的过程，$dp_i$ 的意义是长度为 $i$ 的递增子序列结尾的最小值，而按照直径排序后的询问实际上是在询问使用高度不超过 $B_i$ 的套娃能够组成的 LIS，与 $dp$ 数组的含义极其类似。

注意到求 LIS 的过程中一定有 $dp_i \geq dp_{i - 1}$，故询问高度不超过 $B_i$ 的套娃能够组成的 LIS 等价于求出最后一个使得 $dp_j \leq B_i$ 的 $j$，也就是一段前缀，二分即可。

[代码。](https://atcoder.jp/contests/joisc2016/submissions/42839795)

由于不使用数据结构，随手交了几发都是你谷最优解（。

---

## 作者：Graphcity (赞：2)

另一种做法。

如果没有 $A,B$ 的限制该怎么做？考虑贪心，先将所有 $(r,h)$ 按照 $h$ 升序第一关键字，$r$ 降序第二关键字的顺序排序。用一个 multiset 维护当前所有没有套住的套娃的 $r$ 集合。每次加入一个套娃 $(r',h')$ 时，找到集合中 $r'$ 的前驱然后将它套住，同时从集合中删除。套娃完成后往集合中加入 $r'$。显然这样做是最优的。

接下来加入 $A,B$ 的限制。注意到贪心算法中，我们每次套的 $r$ 都尽量大，$h$ 都尽量在前面，所以在有限制的情况下决策仍然跟原来的贪心是一致的。问题转化成对决策的计数，是一个简单的二维数点。时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e5;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,m,ans[Maxn+5];
struct Group{int r,h;} a[Maxn+5];
vector<pair<int,int>> qr[Maxn+5];
vector<int> v[Maxn+5],w;

struct BIT
{
    int t[Maxn+5];
    #define lowbit(x) (x&-x)
    inline void Add(int x) {while(x) t[x]++,x-=lowbit(x);}
    inline int Count(int x) {int res=0; while(x<=n) res+=t[x],x+=lowbit(x); return res;}
} T1,T2;

int main()
{
    n=read(),m=read();
    For(i,1,n) a[i].r=read(),a[i].h=read(),w.push_back(a[i].r);
    sort(w.begin(),w.end()),w.erase(unique(w.begin(),w.end()),w.end());
    sort(a+1,a+n+1,[](Group x,Group y){return x.h<y.h || (x.h==y.h && x.r>y.r);});
    For(i,1,m)
    {
        int x=read(),y=read(),l=0,r=n;
        while(l<r)
        {
            int mid=(l+r+1)/2;
            if(a[mid].h<=y) l=mid; else r=mid-1;
        } qr[l].emplace_back(x,i);
    }
    multiset<int> st;
    For(i,1,n)
    {
        int r=a[i].r; auto it=st.lower_bound(r);
        if(!st.empty() && it!=st.begin())
            --it,v[i].push_back(*it),st.erase(it);
        st.insert(r);
    }
    For(i,1,n) a[i].r=lower_bound(w.begin(),w.end(),a[i].r)-w.begin()+1;
    For(i,1,n)
    {
        T1.Add(a[i].r);
        for(auto j:v[i]) j=lower_bound(w.begin(),w.end(),j)-w.begin()+1,T2.Add(j);
        for(auto [j,id]:qr[i])
        {
            j=lower_bound(w.begin(),w.end(),j)-w.begin()+1;
            ans[id]=T1.Count(j)-T2.Count(j);
        }
    }
    For(i,1,m) printf("%d\n",ans[i]);
    return 0;
}
```



---

## 作者：Lates (赞：2)

对于 $R_i < R_j, H_i < H_j$，连一条有向边 $(i,j)$，这样会形成一个 DAG。

问最小链覆盖，那么根据 Dirworth 即为求最长反链大小。

可以按 $R_i$ 降序排序后，即求最长不上升子序列长度。

这样用扫描线维护 $A\le R_i$。

设 $dp[i]$ 表示排序后以 $R_i$ 结尾的答案。

用树状数组维护前缀最大值，表示 dp 数组的最大值。

每次 $dp[i]=dp[j]+1$ 更新一个前缀。

```cpp
#include <bits/stdc++.h>
#include <assert.h>
using namespace std;
inline int read(){
	register int x=0,f=0,ch=getchar();
	while('0'>ch||ch>'9')f^=ch=='-',ch=getchar();
	while('0'<=ch&&ch<='9')x=x*10+(ch^'0'),ch=getchar();
	return f?-x:x;
}
const int MAX = 2e5+5;
int n,m,test;

struct Q{
	int A,B,id;
}q[MAX];
struct node {
	int h,r;
}e[MAX]; 

int lsh[MAX << 1], V;
int C[MAX << 1], ans[MAX];
inline int ask(int x) {
	int ret = 0; 
	for(;x;x-=(x&-x)) ret = max(ret, C[x]);
	return ret;
} 
inline void add(int x,int v){
	for(;x<=V;x+=(x&-x)) C[x] = max(C[x], v);
}
signed main(){ 
//freopen("in.in","r",stdin);
	n=read(),test=read();
	for(int i=1;i<=n;++i) e[i].r = read(), e[i].h = read(), lsh[++V] = e[i].h;
	for(int i=1;i<=test;++i) {
		q[i].A = read(),q[i].B = read();
		q[i].id = i;
		lsh[++V] = q[i].B;
	}
	sort(lsh+1,lsh+1+V), V = unique(lsh+1,lsh+1+V)-lsh-1;
	
	for(int i=1;i<=n;++i) e[i].h = lower_bound(lsh+1,lsh+1+V, e[i].h) - lsh;
	for(int i=1;i<=test;++i) q[i].B = lower_bound(lsh+1,lsh+1+V, q[i].B) - lsh; 
	
	sort(q+1,q+1+test,[&](Q a, Q b) { return a.A == b.A ? a.B < b.B : a.A > b.A; });
	sort(e+1,e+1+n, [&](node a,node b) { return a.r == b.r ? a.h < b.h : a.r > b.r; });
	
	int j = 1;
	for(int i=1;i<=test;++i) {
		while(j <= n && q[i].A <= e[j].r) {
			// 在点 e[j].h 加入 
			int t = ask(e[j].h);
			add(e[j].h, t + 1);
			++j;
		}
		ans[q[i].id] = ask(q[i].B);
	}
	for(int i=1;i<=test;++i) printf("%d\n",ans[i]);
	return 0;
}



```


---

