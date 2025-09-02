# Maximum Crossings (Hard Version)

## 题目描述

本版本与另一个版本的唯一区别在于，本题中 $n \leq 2 \cdot 10^5$，且所有测试用例中 $n$ 的总和不超过 $2 \cdot 10^5$。

有一个终端，由 $n$ 个相等的线段组成，按顺序编号为 $1$ 到 $n$。有两个终端，上下各一个。

给定一个长度为 $n$ 的数组 $a$。对于所有 $i = 1, 2, \dots, n$，需要从上方终端的第 $i$ 段的某个点，拉一根直线到下方终端的第 $a_i$ 段的某个点。例如，下图展示了当 $n=7$ 且 $a=[4,1,4,6,7,7,5]$ 时的两种可能的连线方式。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1676H2/71a1fe41f3cad0f3cbda88716457eefb4e46b4ca.png)

当两根线有公共点时，称为一次“交叉”。在上图中，交叉点用红圈标出。

如果你可以最优地放置这些线，最多能有多少次交叉？

## 说明/提示

第一个测试用例如题面第二张图所示。

第二个测试用例中，唯一的连线方式会有两根线交叉，因此答案为 $1$。

第三个测试用例中，只有一根线，因此答案为 $0$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
7
4 1 4 6 7 7 5
2
2 1
1
1
3
2 2 2```

### 输出

```
6
1
0
3```

# 题解

## 作者：RE_Prince (赞：8)

# CF1676H2


一道逆序对模板题。

[link](https://www.luogu.com.cn/problem/CF1676H2)

## Sol

首先，我先给大家两条平行的线段和两条红线：

![](https://cdn.luogu.com.cn/upload/image_hosting/fb8jm0jo.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

题目保证线段是按顺序给出的。

通过观察图，我们不难发现 $4\rightarrow 3$ 这第一条线将整个图分为了两部分。

我们再看第二条线。它的 $a_i$ （下面的数）比 $4\rightarrow 3$ 这条线的 $a_i$ 要小，所以它必定穿过第一条线，形成一个交点。

那为什么呢？


答案很显然。因为线是按顺序排列的（上文提到了），所以 $5\rightarrow 2$ 这条线的 $5$ 在第一条线的 $4$ 的右边， $2$ 还比第一条线的 $3$ 小，所以在第一条线的左边。两个点一左一右，必定产生交点。

到这里结论很显然了，就是求 $a_i\geq a_j$ 的逆序对数量。

下面奉上我的归并排序代码（不会树状数组求逆序对qwq，静等大佬吊打我）：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, m, i, j, k;
const int N = 2e5 + 9;
int a[N];
int t[N];
int f = 0;
inline void merge_sort(int l, int r)
{
	int m = (l + r) / 2;
	if (l == r) return;
	else
	{
		merge_sort(l, m);
		merge_sort(m + 1, r);
	}
	int i = l;
	int j = m + 1;
	int tot = l;
	while (i <= m && j <= r)
	{
		if (a[i] >= a[j]) f += m - i + 1, t[tot++] = a[j++];
		else t[tot++] = a[i++];
	}
	while (i <= m) t[tot++] = a[i++];
	while (j <= r) t[tot++] = a[j++];
	for (int i = l; i <= r; i++) a[i] = t[i];
}
signed main()
{
	int T;
	cin >> T;
	while (T--)
	{
		memset(t, 0, sizeof(t));
		cin >> n;
		for (i = 1; i <= n; i++) cin >> a[i];
		merge_sort(1, n);
		cout << f << endl;
		f = 0;
	}
	return 0;
}
```

可能是语文不好，这篇题解我写了好长时间也感觉难以理解。大家有什么意见可以在评论区中指出。

---

## 作者：Coros_Trusds (赞：3)

# 题目分析

## $\rm{Easy~Version:}$

$\texttt1\le \texttt n\le \texttt1000$。

两个点 $i,j(i\lt j)$ 延伸出的线如果相交，肯定说明 $i$ 要到达的线段大于等于了 $j$ 要到达的线段。

为什么要等于呢，因为题目要求的是最大的交点个数，所以不妨观察下面两幅图（左图为图 $a$，右图为图 $b$）：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1676H2/71a1fe41f3cad0f3cbda88716457eefb4e46b4ca.png)

左边图 $a$ 的 $1\to 4$ 和 $3\to 4$ 这两条线段指向的线段相同，没有相交。但是我们注意到这只是图非常容易误导人，$3\to 4$ 那条线与 $4$ 号线段的交点如果再往左边一点明显就可以再创造一个交点出来嘛！这就是图 $b$ 了。

于是直接枚举点对 $i,j(i\lt j)$ 满足 $a[i]\ge a[j]$ 即可。

## 代码$-\rm Easy~Version:$

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
int a[N];
int T,n;
inline void solve() {
    cin >> n;
    for (register int i = 1;i <= n; ++ i) {
        cin >> a[i];
    }
    int ans = 0;
    for (register int i = 1;i <= n; ++ i) {
        for (register int j = i + 1;j <= n; ++ j) {
            if (a[i] >= a[j]) {
                ans ++;
            }
        }
    }
    cout << ans << "\n";
}
int main(void) {
    cin >> T;
    while (T --) {
        solve();
    }

    return 0;
}
```

## $\rm Hard~Version:$

$\texttt1\le \texttt n\le \texttt 2\times \texttt10^\texttt5$。

观察到其实就是求 $a[i]\ge a[j](i\lt j)$ 的个数，这不就是逆序对问题的变种吗！！！

树状数组维护值域就搞定了，当然也可以用归并排序或权值线段树（应该没人去写吧，坐等大佬打脸），不过树状数组码量最短，常数也较小。

## 代码$-\rm Hard~Version:$

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5,S = 2e5;
int a[N];
int T,n;
struct BIT {
    int tr[N];
    #define lowbit(x) (x & -x)
    inline void init() {
        memset(tr,0,sizeof tr);
    }
    inline void update(int x,int k) {
        for (;x <= S;x += lowbit(x)) {
            tr[x] += k;
        }
    }
    inline int query(int x) {
        int res = 0;
        for (;x;x -= lowbit(x)) {
            res += tr[x];
        }
        return res;
    }
    inline int getsum(int l,int r) {
        return query(r) - query(l - 1);
    }
    #undef lowbit
} bit;
inline void solve() {
    cin >> n;
    for (register int i = 1;i <= n; ++ i) {
        cin >> a[i];
    }
    long long ans = 0;
    for (register int i = 1;i <= n; ++ i) {
        ans += bit.getsum(a[i],n);
        bit.update(a[i],1);
    }
    cout << ans << "\n";
}
int main(void) {
    cin >> T;
    while (T --) {
        bit.init();
        solve();
    }

    return 0;
}
```

---

## 作者：_Ad_Astra_ (赞：3)

一道逆序对模板题。

考虑题目中的线段，由于左端点是有序的，而经过观察不难发现只有当某一条线段的上端点大于（因为没有等于的情况）当前的线段的上端点，而且下端点小于等于当前的线段的下端点时两线才会交叉，问题可以转换成对于 $1 \le i \lt j \le n$ 的每个 $i$ 和 $j$ ，满足 $a_j \le a_i$ 的方案数。

我们可以把这个问题分解成两部分，一部分是求$a_j = a_i$的数量，这一部分可以预处理出每个数出现的次数（记为 $b_i$ ），然后总数量即为 $\sum\limits_{i=1}^{n}\frac{b_i(b_i-1)}{2}$ 。

第二部分则是求 $a_j \lt a_i$ 的情况，也就是求逆序对的个数。我们可以定义一个数组 $c$ ，一开始初始值为 $0$ ，然后对于 $i = n,n-1,n-2,\cdots,1$ 的每一个 $i$ ，每次将 $c_{a_i}$ 增加 $1$ 。这样，以$a_i$ 为第一个数的逆序对个数就可以转换成 $\sum\limits_{j=1}^{a_i-1}c_j$ 。不难发现每次都是修改一个点，然后求一段区间和，很明显可以用线段树或树状数组解决。

code（线段树做法）：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int> 
#define fir first
#define sec second
int tt;
struct node
{
    int l,r,sum;
    node(){}
    node(int _l,int _r,int _sum)
    {
    	l=_l,r=_r,sum=_sum;
	}
}t[800010];
int n,a[200010],ans,b[200010];
void build(int rt,int l,int r)
{
    t[rt].l=l,t[rt].r=r;
    if(l==r)
    {
        t[rt].sum=0;
        return;
    }
    int mid=(l+r)/2;
    build(rt<<1,l,mid);
    build((rt<<1)+1,mid+1,r);
    t[rt].sum=t[rt<<1].sum+t[(rt<<1)+1].sum;
}//建树
int query(int rt,int l,int r)
{
    if(t[rt].l==l&&t[rt].r==r)
        return t[rt].sum;

    if(r<=t[rt<<1].r)return query(rt<<1,l,r);
    else if(l>=t[rt<<1|1].l)return query((rt<<1)+1,l,r);
    else
    {
        int ll=query(rt<<1,l,t[rt<<1].r);
        int rr=query(rt<<1|1,t[rt<<1|1].l,r);
        return ll+rr;
    }
}//查询
void add(int rt,int x,int v)
{
    if(t[rt].l==x&&t[rt].r==x)
    {
        t[rt].sum+=v;
        return;
    }
    if(t[rt<<1].r>=x)add(rt<<1,x,v);
    else if(t[rt<<1|1].l<=x)add(rt<<1|1,x,v);
    t[rt].sum=t[rt<<1].sum+t[rt<<1|1].sum;
}//修改
void solve()
{
	cin>>n;
	for(int i=1;i<=4*n;i++)t[i]=node(0,0,0);
    build(1,1,n);
    ans=0;
    for(int i=1;i<=n;i++)b[i]=0;
    for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		b[a[i]]++;
	}//记录出现次数
	for(int i=1;i<=n;i++)ans+=b[i]*(b[i]-1)/2;//求a[i]=a[j]方案数
    for(int i=n;i>=1;i--)
    {
        add(1,a[i],1);
        if(a[i]>1)ans+=query(1,1,a[i]-1);
    }//求逆序对
    cout<<ans<<endl;
}
signed main()
{
	cin>>tt;
	while(tt--)solve();
    return 0;
}
```

树状数组做法：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int> 
#define fir first
#define sec second
int tt;
int n,ans,a[200010],b[200010],c[200010];
int low_bit(int x)
{
    return x&(-x);
}
int query(int x)
{
    int s=0;
    while(x>0)
    {
        s+=c[x];
        x-=low_bit(x);
    }
    return s;
}
void add(int x,int v)
{
    while(x<=n)
    {
        c[x]+=v;
        x+=low_bit(x);
    }
}
void solve()
{
	cin>>n;
	memset(c,0,sizeof(c));
    ans=0;
    for(int i=1;i<=n;i++)b[i]=0;
    for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		b[a[i]]++;
	}
	for(int i=1;i<=n;i++)ans+=b[i]*(b[i]-1)/2;
    for(int i=n;i>=1;i--)
    {
        add(a[i],1);
        if(a[i]>1)ans+=query(a[i]-1);
    }
    cout<<ans<<endl;
}
signed main()
{
	cin>>tt;
	while(tt--)solve();
    return 0;
}
```

---

## 作者：5k_sync_closer (赞：1)

# 题意
一个终端是一排 $n$ 个连接在一起的相等的线段，有两个终端，一上一下。

有一个数组 $a_i$，代表从上面的终端中第 $i$ 条线段，到下面的终端中第 $a_i$ 条线段，有一条连线。

问这些连线最多有几个交点。
# 思路
考虑何时两条连线会有交点。

观察样例不难得到，若 $i<j$ 且 $a_i≥a_j$，则两条连线有交点。

但此时如果仍然用 [Easy version 的 $O(n^2)$ 做法](https://www.luogu.com.cn/blog/388651/solution-cf1676h1)，显然会 T 飞。

实际上，这是一个二维偏序问题，复杂度可以做到 $O(n\log n)$。

我们开一个权值树状数组，将 $a_i$ 按下标顺序插入，

每插入一个 $a_i$ 之前，查询 $[a_i,n]$ 的区间和，累计答案即可。
# 代码
```cpp
#include <cstdio>
int T, n, c[200050];long long s;
void C(int x, int k) {for(;x <= n;x += x & -x) c[x] += k;}
int Q(int x, int y)
{
    int r = 0;--x;
    for(;y > x;y -= y & -y) r += c[y];
    for(;x > y;x -= x & -x) r -= c[x];
    return r;
}
int main()
{
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d", &n);s = 0;
		for(int i = 1;i <= n;++i) c[i] = 0;
		for(int i = 1, t;i <= n;++i)
            scanf("%d", &t), s += Q(t, n), C(t, 1);
		printf("%lld\n", s);
	}
    return 0;
}
```


---

## 作者：Jerry_heng (赞：0)

（一）

题意转化为求 $i<j$ 且 $a_j\le a_i $ 的有序对 $(i,j)$ 数。 

二维偏序，容易想到用树状数组或归并排序做。

（二）

AC 代码（树状数组）。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,t,tree[200010],a[200010];
int lowbit(int x){
	return x&-x;
}
void add(int x){
	for(;x<=n;x+=lowbit(x))tree[x]++;
}
int query(int x){
	int ans=0;
	for(;x;x-=lowbit(x))ans+=tree[x];
	return ans;
}
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);
		for(int i=1;i<=n;i++)tree[i]=0,scanf("%lld",&a[i]);
		int ans=0;
		for(int i=n;i>=1;i--){
			ans+=query(a[i]);
			add(a[i]);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：yuzhuo (赞：0)

这题虽然简单，但还比较妙。

我们思考如何才能形成一个交点？

如果有从 $i$ 到 $a_i$ 和 从 $j$ 到 $a_j$ 这两条线段，我们假设 $i<j$，那么有没有交点就在于 $a_i$ 与 $a_j$ 的大小关系。

如果 $a_i<a_j$，不可能有交点。

如果 $a_i=a_j$，既有可能有交点，也有可能没有交点。（如题目中的两个图）但由于我们需要最大值，所以这个我们把它当作有交点。

如果 $a_i>b_j$，必定有交点。

我们总结一下，就是在 $i<j$ 且 $a_i\ge a_j$ 时，两条线有交点，即答案加 $1$。

很明显，这是一个逆序对的题目，又因为 $a_i<n$，所以 $a_i<2\times 10^5$，也不需要离散化，直接树状数组（也可以归并，此处不展示）求即可。

AC code:
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 7;
int T, n, a[N]; 
struct BIT {
	int t[N];
	void clear() {
		for (int i = 1; i <= n; ++i)
			t[i] = 0;
	}
	void add(int pos, int val) {
		for (int i = pos; i <= n; i += (i & -i))
			t[i] += val;
	}
	int sum(int pos) {
		int res = 0;
		for (int i = pos; i; i &= (i - 1))
			res += t[i];
		return res;
	}
} bit;
signed main() {
	cin >> T;
	while (T--) {
		cin >> n;
		bit.clear();
		for (int i = 1; i <= n; ++i)
			cin >> a[i];
		int ans = 0;
		for (int i = n; i; --i) {
			ans += bit.sum(a[i]);
			bit.add(a[i], 1);
		}
		cout << ans << endl;
	}
	
}
```

---

## 作者：Sincerin (赞：0)

[题目传送门！](https://www.luogu.com.cn/problem/CF1676H2)

[更好的阅读体验？](https://www.luogu.com.cn/blog/sincerin520/solution-cf1676h2)

## 题意

有两条相互平行的线段，每条线段都由编号为 $1$ 到 $n$ 的 $n$ 条等长的小线段构成。给定一个长度为 $n$ 序列 $a$，其中 $a_i$ 表示上方线段的第 $i$ 段中有一个点和下方线段的第 $a_i$ 段中的一个点之间有一条线段连接。求这些线段之间**最多**能产生多少交点。注意一共有 $t$ 组询问，每组答案输出占一行。

- $1 \leq t \leq 1000 \ , \ 1 \leq n \leq 2 \times 10^5.$
- $1 \leq a_i \leq n \ , \ \sum{n} \leq  2 \times 10^5.$

## 解析

首先我们要明白什么时候才会出现交点。记上方线段和下方线段分别为点集 $A$ 和 $B$，$f:A \rightarrow B$ 为 $A$ 中的点到 $B$ 中点的映射。若 $i$ 和 $j$ 为上方线段的两个点且 $i \lt j$，则当 $f(i) \geq f(j)$ 时两条对应的线段是有交点的。

![](https://cdn.luogu.com.cn/upload/image_hosting/7kiebd9o.png)

如上图 $A$ 点，当两条线段对应的端点均不在同一小段内，则对应的 $i,j$ 之间的大小关系和 $f(i),f(j)$ 之间的大小关系都很容易确定，是否能产生交点也很容易确定。

若两条线段存在端点处于同一小段内，怎么办呢？

很显然，题目要求我们最大化交点数，所以端点在同一段内的两条线段我们默认它们会产生交点即可，如图中点 $C$。

![](https://cdn.luogu.com.cn/upload/image_hosting/28uq4cs1.png)

给定的序列 $a$ 是上下小段之间的对应关系，我们按照上述过程计算，该问题就转化成了求一个序列 $a$ 中满足 $i<j$ 且 $a_i\geq a_j$ 的二元组 $(i,j)$ 的数量。

可以按照逆序对来做。

#### 1.冒泡排序

冒泡是 $\Theta(n^2)$ 的，显然过不掉这个题，但是可以看看 [Maximum Crossings (Easy Version)](https://www.luogu.com.cn/problem/CF1676H1)。


#### 2.归并排序（[P1908 逆序对](https://www.luogu.com.cn/problem/P1908)）

可以做到 $\Theta(n \log n)$ 的时间，并且可以处理较大值域的问题，可以看看[这篇题解](https://www.luogu.com.cn/blog/cpp/solution-p1908)，我在这里就不多赘述了。 

#### 3.树状数组

我们可以用值域树状数组维护截止到目前出现了多少大于等于当前 $a_i$ 值的数并统计答案，然后在当前 $a_i$ 值的出现次数上加一。这个做法也是 $\Theta(n \log n)$ 的，并且常数十分优秀。但是缺点也很明显，就是无法维护太大值域，P1908 需要进行离散化才可以通过。

至于为什么我会着重讲树状数组解法， $1 \leq a_i \leq n$ 的数据范围已经把树状数组写在脸上了好吧，直接统计即可，代码量极短（~~当然你也可以写其他又臭又长的区间数据结构~~）。

对了，都来做这个题了，不会还有人不会树状数组吧。来[看看](https://www.luogu.com.cn/problem/solution/P3374)吧！

## AC Code


```cpp
//C++20 763B 171ms 1.52MB
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std; 
#define lowbit(x) x&(-x)
const int N=200005;
int t,n,dat[N],a[N];
long long res,ans;//不开见祖宗!
inline void change(int x,int v)//单点修改 
{
	for(;x<=n;x+=lowbit(x)) 
		dat[x]+=v;
	return;
}
inline int query(int x)//单点查询前缀和
{
	res=0;
	for(;x;x-=lowbit(x)) 
		res+=dat[x];
	return res;
}
signed main(void)
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n); ans=0;//多测不清空,寄!
		for(register int i=0;i<=n;++i) dat[i]=0;//memset(0)
		for(register int i=1;i<=n;++i)
		{
			scanf("%d",&a[i]);
			ans+=query(n)-query(a[i]-1);//[a[i],n]中的数在a[i]前出现了多少个
			//也就是前i-1个数中有几个是>=a[i]的 
			change(a[i],1);//累加a[i] 
		}
		printf("%lld\n",ans); 
	}
	return 0;//完结撒花! 
}
```



---

## 作者：guanyf (赞：0)

### 题意简述
- 有两排点，第一排中的第 $i(1 \le i \le n)$ 个点会和第二排的第 $a_i$ 个点连一条边，求这些线有几个交点（交点是两排中的点也算）。

- $1 \le n \le 2 \cdot 10^5$

### 简单版
这道题有两个版本，先说简单版的理解题意。

刚看到这道题的时候不知道怎么下手，没事，分析下交点的本质是什么：我们枚举一个点 $i$，假设它是往右连边的，那么如果它和另一个点 $j$ 的边相交，则 $j$ 一定是大于 $i$，并且 $a_j \le a_i$。但如果这个点是向左连边的呢？那么它一定会被前面的一个向右连边的点统计到。

因此，直接模拟就可以了。

### 升级版
其实这道题就是求有多少个点对 $(i,j)$，使得 $i < j$ 且 $a_j \le a_i$，也就是求逆序对。你可以选择使用归并排序的思想，也可以使用权值[树状数组](https://www.luogu.com.cn/blog/388651/about-RBIT)。

权值树状数组其实就是从右往左扫一遍，然后统计右边小于等于 $a_i$ 的 $a_j$ 的个数。

#### 权值树状数组版本代码
```cpp
#include <bits/stdc++.h>
#define int long long
#define lowbit(x) (x & -x)
using namespace std;
const int MAXN = 2e5 + 5;
int T, n, a[MAXN], b[MAXN], tot, ans;
struct BIT {
  int res, a[MAXN];
  void clear(int n) { fill(a + 1, a + 1 + n, 0); }
  void update(int x) {
    for (; x <= n; x += lowbit(x)) a[x]++;
  }
  int query(int x) {
    for (res = 0; x; x -= lowbit(x)) res += a[x];
    return res;
  }
} tree;
void solve() {
  cin >> n, tree.clear(n), ans = 0;
  for (int i = 1; i <= n; i++) cin >> a[i], b[++tot] = a[i];
  sort(b + 1, b + 1 + tot), tot = unique(b + 1, b + 1 + tot) - b - 1;
  for (int i = 1; i <= n; i++) a[i] = lower_bound(b + 1, b + 1 + tot, a[i]) - b;
  for (int i = n; i >= 1; i--) ans += tree.query(a[i]), tree.update(a[i]);
  cout << ans << '\n';
}
signed main() {
  ios::sync_with_stdio(0), cin.tie(0);
  for (cin >> T; T--;) {
    solve();
  }
  return 0;
}
// 
```

#### 归并排序代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define m (l + r >> 1)
using namespace std;
const int MAXN = 2e5 + 5;
int T, n, a[MAXN], ans;
void cdq(int l, int r) {
  if (l == r) return;
  cdq(l, m), cdq(m + 1, r);
  for (int i = l, j = m + 1; i <= m; i++) {
    while (j <= r && a[j] <= a[i]) j++;
    ans += j - 1 - m;
  }
  inplace_merge(a + l, a + m + 1, a + 1 + r);
}
void solve() {
  cin >> n, ans = 0;
  for (int i = 1; i <= n; i++) cin >> a[i];
  cdq(1, n), cout << ans << '\n';
}
signed main() {
  ios::sync_with_stdio(0), cin.tie(0);
  for (cin >> T; T--;) {
    solve();
  }
  return 0;
}
```


---

## 作者：splendore (赞：0)

### 题意

给你一个正整数序列，让你求其中 $\ a_i\ge a_j\ i<j\ $ 的个数，

其实就是序列中逆序对的个数再加上 $\ a_i = a_j\ i<j\ $ 的个数，

关于逆序对的求法可见 P1908。

目前求逆序对的主流写法有树状数组和归并排序，两者时间复杂度均为$\ O(n\log n)$，但树状数组的常数小，码量短，所以更建议写树状数组。

----------

代码如下
```
#include<cstdio>
#include<cstring>
using namespace std;
const int N=210000;
int a[N],c[N];
inline int lowbit(int x){return x&-x;}
void add(int x,int k){
	while(x<N){
		c[x]+=k;
		x+=lowbit(x);
	}
}
int query(int x){
	int res=0;
	while(x>0){
		res+=c[x];
		x-=lowbit(x);
	}
	return res;
}
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int n;scanf("%d",&n);
		for(int i=1;i<=n;++i)
			scanf("%d",&a[i]);
		memset(c,0,sizeof(c));
		long long ans=0;
		for(int i=1;i<=n;++i)
			ans+=query(n)-query(a[i]-1),add(a[i],1);
		printf("%lld\n",ans);
	}
}
```

---

## 作者：DQM_Charley (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1676H2)

这是我写(~~水~~)的第一篇题解。

# 归并排序求逆序对
## 题目分析
这题让我们求两两连线后线段的最多交点数。

首先关注一下，什么时候会出现交点？

这个很容易想到：

记两条线段为 $l1$ 和 $l2$，容易发现，当 $l1$ 的上端点在 $l2$ 上端点的一侧，而 $l1$ 下端点在 $l2$ 下端点的另一侧时，二者会相交。

看起啦很简单（~~实际上也很简单~~），但有个小问题：如果二者的端点出现在了同一条线段上时怎么办？注意到题目要求我们求 _**最多**_ 交点数，那么，我们可以想象一下，在这种情况下，是可以做到二者有交点。所以，我们默认这种情况下一定会有交点，以保证结果最大（~~证略~~）。

这时候第一种思路就出现了：

## 暴力求解

我们暴力枚举每两个线段的组合，然后用如上规则判断是否会存在交点。易知，该算法复杂度约为 $O(N^2)$。

很明显会超时~~所以我连相关代码都懒得写~~。

~~但我绝对不会告诉你这种超级简单的思路可以过掉 [CF1676H1](https://www.luogu.com.cn/problem/CF1676H1)~~ 。

但作为一个有梦想的孩子，我们一定是要挑战满分的，所以：

## 逆序对
没错，如果仔细想一下的话，你会惊奇的发现，这道题其实就是在让我们求逆序对的个数。

等一下，你不会还不知道什么是逆序对吧？那就去 **[这里](https://www.luogu.com.cn/problem/P1908)** 看看吧。

但是，however，这里的逆序对有点不同：

本来逆序对是指满足 $i>j$ 且 $a[i]<a[j]$ 的二元组 $(i, j)$，但是在这里，我们说了，端点在同一条线段上时，其实也会产生交点，所以，二元组的条件转变为：

$i>j$ 且 $a[i]≤a[j]$。

好了，问题解决，~~上代码~~：

# Code
```cpp
/* 归并排序求法 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 5e5 + 5;

int n, a[N], t[N];
ll ans;

void solve(const int &, const int &);

int main()
{
	ios::sync_with_stdio(false),
	    cin.tie(0), cout.tie(0);
	int q;
	cin >> q;
	while (q--)
	{
		ans = 0;
		cin >> n;
		for (int i = 1; i <= n; i++)
			cin >> a[i];
		solve(1, n);
		cout << ans << endl;
	}
	return 0;
}

void solve(const int &l, const int &r)
{
	if (l == r) return ;
	int mid = l + r >> 1;
	solve(l, mid), solve(mid + 1, r);

	// 求逆序对数
	for (int i = l, j = mid + 1; j <= r; j++)
	{
		while (i <= mid && a[i] < a[j]) i++;
		ans += mid - i + 1;
	}
    
	//  排序
	int pl = l, pr = mid + 1, p = l;
	while (pl <= mid && pr <= r)
		t[p++] = a[pl] < a[pr] ? a[pl++] : a[pr++];
	while (pl <= mid) t[p++] = a[pl++];
	while (pr <= r) t[p++] = a[pr++];

	for (int i = l; i <= r; i++) a[i] = t[i];
}
```


---

