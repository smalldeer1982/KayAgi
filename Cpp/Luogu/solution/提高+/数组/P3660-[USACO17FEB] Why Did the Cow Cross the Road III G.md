# [USACO17FEB] Why Did the Cow Cross the Road III G

## 题目描述

Farmer John 的农场布局非常独特，主田地的外围有一条环形道路，他的奶牛白天在这里吃草。每天早上，奶牛们都会穿过这条道路进入田地，每天晚上它们又会再次穿过这条道路离开田地返回牛棚。

众所周知，奶牛是习惯性动物，它们每天都会以相同的方式穿过道路。每头奶牛进入田地的点和离开田地的点不同，并且所有这些穿过点都彼此不同。Farmer John 拥有 $N$ 头奶牛，方便地用整数 ID $1 \ldots N$ 标识，因此道路周围恰好有 $2N$ 个穿过点。Farmer John 通过顺时针扫描环形道路，记录每个穿过点的奶牛 ID，最终形成一个包含 $2N$ 个数字的序列，其中每个数字恰好出现两次。他并未记录哪些穿过点是进入点，哪些是离开点。

看着他的穿过点地图，Farmer John 好奇一天中不同奶牛对之间可能会交叉多少次。如果奶牛 $a$ 从进入点到离开点的路径必须与奶牛 $b$ 从进入点到离开点的路径交叉，那么他称奶牛对 $(a,b)$ 为“交叉”对。请帮助 Farmer John 计算交叉对的总数。

## 样例 #1

### 输入

```
4
3
2
4
4
1
3
2
1```

### 输出

```
3```

# 题解

## 作者：苟全性命 (赞：20)

## Description：

给定长度为$2N$的序列，$1\sim N$各处现过$2$次，$i$第一次出现位置记为$a_i$，第二次记为$b_i$，求满足$a_i<a_j<b_i<b_j$的对数。

$1\leqslant n\leqslant50000$

## Solution1：

把所有数对找出来，按两端点之间的距离从大到小排序，每次把左右两端点在树状数组中加一，然后把答案累加两端点之间的区间和，因为由于区间越来越小，所以两个区间要么不交，要么之前的包含之后的，要么区间相交，而只有最后一种情况会被统计，所以最后求出的就是答案。

## Code1：

```C++
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
int n;
#define MAXN 100010
struct seq
{
	int l,r;
	seq(){l = r = -1;}
}s[MAXN >> 1];
bool cmp_len(seq a,seq b){return a.r - a.l > b.r - b.l;}
int c[MAXN];
int lowbit(int x){return x & (-x);}
void add(int p){for(int i = p;i <= n * 2;i += lowbit(i))++c[i];return;}
int query(int p){int res = 0;for(int i = p;i >= 1;i -= lowbit(i))res += c[i];return res;}
int main()
{
	scanf("%d",&n);
	int a;
	for(int i = 1;i <= n * 2;++i)
	{
		scanf("%d",&a);
		if(s[a].l == -1)s[a].l = i;
		else s[a].r = i;
	}
	sort(s + 1,s + 1 + n,cmp_len);
	int ans = 0;
	for(int i = 1;i <= n;++i)
	{
		add(s[i].l);add(s[i].r);
		ans += query(s[i].r - 1) - query(s[i].l);
	}
	cout << ans << endl;
	return 0;
}
```

## Solution2：

另一种做法是按左端点排序，然后每次统计左右端点之间的标记个数，道理类似，统计上的都是合法的。

## Code2：

```C++
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
int n;
#define MAXN 100010
struct seq
{
	int l,r;
	seq(){l = r = -1;}
}s[MAXN >> 1];
bool cmp_l(seq a,seq b){return a.l < b.l;}
int c[MAXN];
int lowbit(int x){return x & (-x);}
void add(int p){for(int i = p;i <= n * 2;i += lowbit(i))++c[i];return;}
int query(int p){int res = 0;for(int i = p;i >= 1;i -= lowbit(i))res += c[i];return res;}
int main()
{
	scanf("%d",&n);
	int a;
	for(int i = 1;i <= n * 2;++i)
	{
		scanf("%d",&a);
		if(s[a].l == -1)s[a].l = i;
		else s[a].r = i;
	}
	sort(s + 1,s + 1 + n,cmp_l);
	int ans = 0;
	for(int i = 1;i <= n;++i)
	{
		add(s[i].r);
		ans += query(s[i].r - 1) - query(s[i].l);
	}
	cout << ans << endl;
	return 0;
}
```



---

## 作者：YLWang (赞：14)

震惊居然没有人用莫队

我们看到静态的区间查询问题，第一个想到的就应该是莫队

思考一下，我们可以考虑对于任意一种数字$i$,他们对答案的贡献是两个$i$之间出现个数为1的数。

当然会出现重复统计，最后/2即可。

莫队维护一下。复杂度$O(n\sqrt{n})$

```
#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define mst(a,b) memset(a,b,sizeof(a))
#define For(i, k, j) for(register int i = (k); i <= (j); i++)
#define INF (1 << 30) - 1
#define ll long long
#define reaD() read()
using namespace std;
inline int read()
{
    int num=0,flag=1;char c=' ';
    for(;c>'9'||c<'0';c=getchar()) if(c=='-') flag = -1;
    for(;c>='0'&&c<='9';num=(num<<1)+(num<<3)+c-48,c=getchar());
    return num*flag;
}
#define MAXN 200005
int a[MAXN], cnt[MAXN], n, Siz;
struct Query {
	int l, r;
	bool operator < (const Query b) const  {
		if(l / Siz != b.l / Siz) return l < b.l;
		else return r < b.r;
	}
}q[MAXN];

int ans = 0, nowans = 0;
inline void add(int val) {
	if(cnt[val] == 0) nowans++;
	if(cnt[val] == 1) nowans--;
	cnt[val]++;
}
inline void del(int val) {
	if(cnt[val] == 2) nowans++;
	if(cnt[val] == 1) nowans--;
	cnt[val]--;
}
signed main()
{
	n = read();
	Siz = sqrt(n); 
	For(i, 1, n<<1) {
		a[i] = read();
		if(!q[a[i]].l) q[a[i]].l = i;
		else q[a[i]].r = i;
	}
	sort(q + 1, q + 1 + n);
	int l = 1, r = 0;
	For(i, 1, n) {
		while(l < q[i].l) del(a[l++]);
		while(l > q[i].l) add(a[--l]);
		while(r < q[i].r) add(a[++r]);
		while(r > q[i].r) del(a[r--]);
		ans += nowans;
	}
	cout <<ans /2<< endl;
    return 0;
}



```

---

## 作者：Drug__Lover (赞：7)

**树状数组**

**我们会发现对于同样的数字出现交叉对（对于后面的那一种数字来说）当且仅当他的左端点在前面那一种数字的右面并且他的右端点也在前面那一种数字的右面**

**那么我们可以根据左端点排序**

**枚举的时候就可以保证当前这一种数字的左端点在前面那些数字的左端点的右面**

**这时候我们只要再保证当前这一种数字的右端点在前面那些数字的右端点的右面就可以了**

**那么我们就对于一种数字，把他的右端点插入树状数组**

**查询的时候查询当前这种数字L，R之间的右端点的个数就是交叉对的个数了**



```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#define maxn 100010
using namespace std;
int n;
int sum;
int c[maxn];
struct node
{
    int l,r;
}a[maxn];
int vis[maxn];
int add(int x,int k)
{
    for(int i=x;i<=n*2;i+=i&(-i)) c[i]+=k;
}
int query(int x)
{
    int sum=0;
    for(int i=x;i>0;i-=i&(-i)) sum+=c[i];
    return sum;
}
int cmp(node x,node y)
{
    return x.l<y.l;
}
int main()
{
    cin>>n;
    for(int i=1;i<=n*2;i++)
    {
        int x;
        scanf("%d",&x);
        if(!vis[x]) a[x].l=i,vis[x]=1;
        else a[x].r=i;
    }
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++)
    {
        sum=sum+query(a[i].r)-query(a[i].l-1);  //求右端点的个数 
        add(a[i].r,1);   //插入右端点 
    }
    cout<<sum<<endl;
    return 0;
}
```

---

## 作者：trsins (赞：3)

树状数组好题。

对于每一个 $x,x \in [1 , n]$，它的 $a_i,b_i$ 可以看作一个**区间**。

一看见区间，直接想到用线段树或树状数组维护。

题目所求对的 $a_i<a_j<b_i<b_j$ 相当于是有两个区间，其中一个的区间的右端点在另一区间内而另一区间的左端点在这个区间内。

还是见图吧。

![](https://s3.ax1x.com/2021/01/28/y9xm4g.png)

红色矩形表示第一个区间（$i$），蓝色的表示第二个（$j$）。

所以思路非常显然。

将数组以左端点为关键字从小到大排序，然后枚举有多少个矩阵，它的左端点在原矩阵区间内。相当于枚举有多少个矩阵它的右端点在原矩阵右边。

然后直接暴力搞肯定是不行的，$O(n^2)$ 的时间复杂度对于 $n \le 5 \times 10^4$ 无法通过。所以用数据结构维护。

维护的是**右端点**，因为左端点已经排过序了。

考虑使用哪一种数据结构。

线段树又长又臭，而这题维护的要求也不高，它所需要维护的东西完全也能用树状数组维护，所以使用又短又快的树状数组进行维护。

树状数组对右端点进行维护后，只需查找当前区间左端点右端点之间的个数即可。

计算一下时间复杂度。

我们排序左端点时用 $\mathtt{sort}$，时间复杂度 $O(n\log n)$，而我们从 $1\to n$ 对于每个数都进行查询（求右端点与左端点之间的个数）、更新，时间复杂度则是从 $1$ 至  $n$ 跑一边的 $O(n)$ 乘上树状数组维护的查询与更新，皆为 $\log n$，时间复杂度依旧 $O(n\log n)$。我们左端点与右端点所耗时间相同，都是 $O(n\log n)$。

综上，时间复杂度 $O(n\log n)$，对于此题 $n \le 5 \times 10^4$ 的数据来说非常优秀。

---

## 作者：KCID (赞：3)

#### 前言

线段树 ~~水~~ 好题

寻思着这道题用线段树不也很香吗。

#### 做法

题意相当简洁，大家都看得懂。

不难看出实际上我们要统计的答案大概可以转化为这个：

![](https://cdn.luogu.com.cn/upload/image_hosting/0lk7gm21.png)

求黄色部分以及红色部分有多少个相同的数。

but，我们思考过后，发现，实际上，我们仅仅只需要考虑，在 $a_j$ 之前的数中，有多少个 $b_i$ 是小于 $b_j$ 的，这个我们可以通过线段树很轻松的维护。

但是如果仅仅维护这个，你会发现你过不了样例（捂脸）。

因为还有一个限制： $b_i > a_j$

这怎么办啊？

不慌，用之前得到的答案减去不合法的答案即可。

什么样的答案是不合法的？也就是 $b_i < a_j$ 的，不妨再调用一下线段树，直接找 $b_i < a_j$的数有多少个即可。

每次枚举这个 $a_j$，将每次得到的答案求和即可。


```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

int n;
int a[MAXN];
int Next[MAXN];
int book[MAXN];

struct SegmentTree {
    int laz,sum,l,r;
} T[MAXN * 8];

void build(int x,int l,int r)
{
    T[x].l = l ,  T[x].r = r;
    T[x].sum = T[x].laz = 0;
    if(l == r)return ;
    int mid = (l + r) >> 1;
    build(x << 1 , l , mid);
    build(x << 1 | 1 , mid + 1 , r);
    return ; 
}

void ad(int x,int k)
{
    T[x].sum += (T[x].r - T[x].l + 1) * k;
    T[x].laz += k;
}

void pushdown(int x)
{
    if(T[x].laz == 0)return ;
    ad(x << 1 , T[x].laz);
    ad(x << 1 | 1 , T[x].laz);
    T[x].laz = 0;
    return ;
}

void change(int x,int l,int r,int k)
{
    if(T[x].l >= l && T[x].r <= r){ad(x , k);return ;}
    pushdown(x);
    int mid = (T[x].l + T[x].r) >> 1;
    if(l <= mid)change(x << 1 , l , r , k);
    if(r  > mid)change(x << 1 | 1 , l , r , k);
    T[x].sum = T[x << 1].sum + T[x << 1 | 1].sum;
    return ;
}

int GetSum(int x,int l,int r)
{
    if(T[x].l >= l && T[x].r <= r)return T[x].sum;
    pushdown(x);
    int mid = (T[x].l + T[x].r) >> 1;
    int sum = 0;
    if( l <= mid )sum += GetSum(x << 1 , l , r);
    if( r  > mid )sum += GetSum(x << 1 | 1 , l, r);
    return sum;
}

int main()
{
    cin >> n;
    for(int i = 1 ; i <= 2 * n ; i ++)cin >> a[i];
    build(1 ,1 , 2 * n);
    for(int i = 2 * n ; i >= 1 ; i --)//求出对应的"bj"
    {
        if(!book[a[i]])book[a[i]] = i;
        else Next[i] = book[a[i]];
    }
    int Ans = 0;
    for(int i = 1 ; i <= 2 * n ; i ++)
    {
        if(!Next[i])continue;//如果它不是"aj"
        Ans += GetSum(1 , Next[i] , Next[i]);//获取答案
        Ans -= GetSum(1 , i , i);//减去不合法的答案
        change(1 , Next[i] , 2 * n , 1);//更新区间
    }
    cout << Ans;
    return 0;
}
```

---

## 作者：5ab_juruo (赞：3)

看到还没有人用分治做，赶紧来水一发。

思路很简单，每一次解决区间$[l,r]$时，都从中间劈开来解决。

以样例为例：

![](https://s2.ax1x.com/2020/01/11/lI0h24.png)

实际上就是交点的数量统计。

线可以分为2类：

1. 跨越两边的线（下称“跨越线”）；
2. 只在一边的线（下称“一边线”）。

同样的，点也可以分成3类：

1. 两条线都是跨越线；
2. 一条是跨越线，一条是一边线；
3. 都是一边线。

我们就分别处理。

---

对于第2类点，直接扫描即可。

记录一个数$cnt$，表示当前有多少**层**一边线。

每遇到一条跨越线，就将答案 += $ cnt$。

第1类点比较玄学，我们单独来看：

![](https://s2.ax1x.com/2020/01/11/lIBQoV.png)

这不就是求逆序对吗？

~~啥？你连这个都不会？网上搜逆序对的应用自行学习。~~

那么第一类点呢？分治即可。

这样我们就完成了点的统计

---

# 复杂度分析

设 $T_n$ 为区间范围为 $n$ 时的时间。

则有公式：

$$
T_n=2T_{\left\lfloor\frac{n}{2}\right\rfloor}+O(n\log n)
$$

由于 $2\times \dfrac{n}{2}\log \left(\dfrac{n}{2}\right)=n(\log n-1)\sim n\log n$

所以 $T_n=\log n \times (n\log n)=O(n\log^2 n)$

虽说复杂度高了点，但还是能 AC 的。

放代码：

```
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
 
const int max_n = 50000;
 
int fst[max_n], nxt[max_n*2], mem[max_n], tmp_len;
 
int solve2(int l, int r) // 逆序对
{
    if (l == r)
        return 0;
     
//  fprintf(stderr, "   %d %d\n", l, r);
     
    if (!(~r))
        return 0;
     
    int mid = (l + r) >> 1, ans = solve2(l, mid) + solve2(mid + 1, r), lp = l, rp = mid + 1, ap = l;
     
    while (ap <= r)
    {
        if (lp <= mid && (rp > r || fst[lp] < fst[rp]))
            mem[ap++] = fst[lp++];
        else
            mem[ap++] = fst[rp++], ans += mid - lp + 1;
    }
     
    for (int i = l; i <= r; i++)
        fst[i] = mem[i];
     
    return ans;
}
 
int solve(int l, int r) // 大分治
{
    if (l == r)
        return 0;
     
    int mid = (l + r) >> 1, ans = solve(l, mid) + solve(mid + 1, r), fk; // 不要在意变量名，第1类点
     
    tmp_len = 0;
    for (int i = l; i <= mid; i++)
    {
        if (nxt[i] > mid && nxt[i] <= r)
        {
            fst[tmp_len] = nxt[i];
            tmp_len++;
        }
        else if (nxt[i] < l || nxt[i] > r)
            ans += tmp_len; // 第2类点
    }
     
    fk = tmp_len;
     
    for (int i = mid + 1; i <= r; i++)
    {
        if (nxt[i] <= mid && nxt[i] >= l)
            fk--;
        else if (nxt[i] < l || nxt[i] > r)
            ans += fk;
    }
     
    reverse(fst, fst + tmp_len); // STL大法好
     
    if (tmp_len)
        return ans + solve2(0, tmp_len - 1); // 第3类点
    else
        return ans;
}
 
int main()
{
    memset(fst, -1, sizeof(fst));
     
    int n, tmp;
     
    scanf("%d", &n);
    for (int i = 0; i < 2 * n; i++)
    {
        scanf("%d", &tmp);
         
        if (!(~fst[tmp-1]))
            fst[tmp-1] = i;
        else
            nxt[fst[tmp-1]] = i, nxt[i] = fst[tmp-1]; // 构建序列
    }
     
    printf("%d\n", solve(0, 2 * n - 1));
     
    return 0;
}
```

---

## 作者：时间圣使·凡 (赞：3)

### 前言
这里提供一种 STL 加上二分的算法（个人认为对水平较低的人更加友好，比如说我）。
### 解法:
根据题意，其实可以将数字第一次出现与第二次出现的位置当做始末位置。而始末位置可以看成对应的一条线。

两根线相交的条件就是其中一根线的起点或终点的位置在另一根线的始末位置之间，而这根线的另一个点在另一条线的始末位置之外。

在读入时用结构体记录下每一对数字的始末位置，按照起始位置从大到小排序。

按照起始位置从大到小排序，这样就保证了当前起点一定在后面的所有线的起始位置之后。

然后我们倒序维护一个单调递增的数列。

从起点最靠前的线的终点开始不断加入这个数列，从起点位置排在第二的线开始，与当前线可以相交的线的数量，就是这根线的终点如果加入数列会排在的位置与起点如果加入数列会排在的位置之差。

因为终点加入之后的位置之前的线都是符合一个点在始末位置之外的线，而起点加入之后位置之后的线都是符合一个点在始末位置之间的线，只要两点都符合的线即为合法的相交，计入答案之内。

同时，因为维护的单调递增的数列只需要两个二分就能快速找到起点与终点应该存在的位置，所以总的用时符合数据范围。

**注意需要边维护边计算，因为新插入的数字会改变原先的数列，导致如果先制造后计算的话没办法用 $O(1)$ 的时间将该点删除（当然可能也有解决办法）。**

### 代码：
```cpp
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
int n,ans=0;
struct zwh{
	int l,r;
}a[50010],b[50010];
bool cmp(zwh x,zwh y){return x.l>y.l;}
vector<int> p;
int main(){
//	freopen("cross.in","r",stdin);
//	freopen("cross.out","w",stdout);
	
	cin>>n;
	for(int i=1;i<=n*2;i++){
		int x;
		cin>>x;
		if(a[x].l) a[x].r=i;
		else a[x].l=i;//记录始末位置 
	}
	sort(a+1,a+1+n,cmp);//按照起始位置排序 
	for(int i=n;i>=1;i--){
		if(!p.size()) p.push_back(a[i].r);//第一个终点，不用计算 
		else{
			int l1=lower_bound(p.begin(),p.end(),a[i].l)-p.begin();//计算起点应该排在的位置 
			int op=lower_bound(p.begin(),p.end(),a[i].r)-p.begin();//计算终点应该排在的位置 
			p.insert(p.begin()+op,a[i].r);//插入数据，维护一个递增的数列 
			ans+=op-l1;//加入合法数据 
		}
	}
	cout<<ans<<endl;
	
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}
```


---

## 作者：genshy (赞：2)

**题意：**

给定长度为 $2N$ 的序列，$1~N$ 各处现过 $2$ 次，$i$ 第一次出现位置记为$ai$，

第二次记为$bi$，求满足$ai<aj<bi<bj$的对数.

转化一下题意：求 $a_i - b_i$ 中出现次数为 $1$ 的个数。

既然数据范围那么小，直接上莫队。

先预处理出每个数第一次出现以及第二次出现的位置。

然后就变成了我们熟悉的区间问题。就可以套用莫队的板子啦，

但最后答案要除以 二，因为 $(x,y)$ 这两个数对，你在 $x$ 这个位置会算一遍，在 $y$ 这个位置同样也会被算一遍。

可这个却只能算一遍，所以最后答案要除以二。

计算移动指针的贡献的时候，不要忘记计算移动前和移动后对现在答案的影响。

具体的细节可以看代码：

**Code**

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int N = 1e5+10;
int n,m,ans,tmp,l,r,block,x;
int pos[N],fir[N],sec[N],cnt[N],a[N];
struct node
{
    int l,r,id;
}q[N];
inline int read()
{
    int s = 0,w = 1; char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') w = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){s = s * 10 + ch - '0'; ch = getchar();}
    return s * w;
}
bool comp(node a,node b)
{
    if(pos[a.l] == pos[b.l]) return a.r < b.r;
    return pos[a.l] < pos[b.l];
}
void add(int x)
{
	if(cnt[a[x]] == 0) tmp++;//如果说当前这个数在这段区间第一次出现，对答案的贡献加1
    cnt[a[x]]++;
    if(cnt[a[x]] == 2) tmp--;//出现两次对答案没有贡献
}
void del(int x)
{
    if(cnt[a[x]] == 2) tmp++;//出现次数变为一次，就会对答案的贡献加1
    cnt[a[x]]--;
    if(cnt[a[x]] == 0) tmp--;//没有出现，对答案的贡献就会变为0
}
int main()
{
    n = read(); block = sqrt(2 * n);
    for(int i = 1; i <= 2 * n; i++)
    {
        a[i] = read();
        if(fir[a[i]] == 0) fir[a[i]] = i;//求一个数第一次以及第二次出现的位置
        else sec[a[i]] = i;
    }
    for(int i = 1; i <= 2 * n; i++) pos[i] = (i - 1) / block + 1;//分块预处理，注意是对序列分块
    for(int i = 1; i <= n; i++)
    {
        q[i].l = fir[i];
        q[i].r = sec[i];
        q[i].id = i;
    }
    sort(q+1,q+n+1,comp);
    l = 1, r = 0, tmp = 0;
    for(int i = 1; i <= n; i++)//莫队板子
    {
        while(l < q[i].l) del(l++);
        while(l > q[i].l) add(--l);
        while(r < q[i].r) add(++r);
        while(r > q[i].r) del(r--);
        ans += tmp;
    }
    printf("%d\n",ans/2);//最后不要忘记除以二
    return 0;
}
```



---

## 作者：abandentsky (赞：2)

看了那么多题解还是没懂咋写。就谈谈自己的思路：
我们以给出的测试样例为例：
3   2   4   4   1   3   2   1（这是题目的测试样例）
下面执行操作某个数字第一次出现就加正一，第二次出现就加负一。
就像这样。
3   2   4   4   1   3   2   1
+1  +1  +1  -1  +1  -1  -1  -1
现在处理3，把3的左端点和右端点求和就是（1+1+1-1+1-1=2）把2累加到答案里。之后把3的左端点和右端点的值改为0.然后处理2.把2的左端点和右端点之间的值累加就是（1+1-1+1+0-1=1）。累加到答案里。然后把所有的都处理一遍就好了。最后输出答案。

```c
#include<stdio.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#define MAXN  100005
using namespace std;

int n;
int P[MAXN],c[MAXN];
int cnt[MAXN];         //cnt[i]表示i这个数字第一次出现的位置
struct node
{
    int fir,sec;
    node(int fir=0,int sec=0):fir(fir),sec(sec){};
};
node Q[MAXN];

int lowbit(int x)
{
    return (x&((-1)*x));
}

void add(int x,int d)
{
    while(x<=n*2)
    {
        c[x]+=d;
        x+=lowbit(x);
    }
}

int sum(int x)
{
    int ans=0;
    while(x>0)
    {
        ans+=c[x];
        x-=lowbit(x);
    }
    return ans;
}

void solve()
{
    int ans=0;
    for(int i=0;i<n;i++)
    {
        ans+=sum(Q[i].sec)-sum(Q[i].fir-1);
        add(Q[i].sec,1);
        add(Q[i].fir,-1);
    }
    printf("%d\n",ans);
}

int main()
{
    scanf("%d",&n);
    memset(cnt,-1,sizeof(cnt));
    int tg=0;
    for(int i=1;i<=2*n;i++)
    {
        scanf("%d",&P[i]);
        if(cnt[P[i]]==-1)
        {
            cnt[P[i]]=i;
        }
        else
        {
            Q[tg++]={cnt[P[i]],i};
            add(cnt[P[i]],1);
            add(i,-1);
        }
    }
    solve();
    return 0;
}

```





---

## 作者：Del_Your_Heart (赞：2)

## 题目大意：

### 给定长度为$2n$的序列，$1-n$各处现$2$次，记$i$第一次出现位置为$a_i$，第二次记为$b_i$，对于每一对$i\in[1,n],j\in[1,n]$且$i!=j$，求满足$a_i<a_j<b_i<b_j$的对数。

------------

## 思路分析：
**$1^o$ $O(n^2)$ 做法：暴力枚举$i,j$，判断是否满足条件。**

期望得分：看数据强弱。对于本题$1\leq n\leq50000$显然会$TLE$。

**$2^o$ 考虑优化：本题数据范围约为$O(n \log n)$，考虑用快排进行优化。**

具体做法：按第一次出现位置作为关键词排序，循环枚举每个数字$j$，统计满足题意的数对$(i,j)$的个数即为$\sum^{n}_{j=1}\sum^{j-1}_{i=1}[a_j<b_i<b_j]$。考虑快速求出这样的$i$，用类似于树状数组的数据结构即可维护出这样的$i$的个数

我用的$zkw$线段树,似乎题解里没人用,我个人其实挺偏爱$zkw$线段树的~~zkw大法好(逃~~,看过我的[$P5149$题解](https://www.luogu.org/blog/CreeperBatter/p5149-ti-xie)和[$P4375$题解](https://www.luogu.org/blog/CreeperBatter/solution-p4375)的人应该都熟悉$zkw$线段树的用法。

时间复杂度: $O(n\log n)$

期望得分: $100pts$

**问题到这里就完美解决了。**


------------

## 代码实现:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+5;
inline int read(){
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch)){
		f|=ch=='-';
		ch=getchar();
	}
	while(isdigit(ch)){
		x=x*10+(ch^48);
		ch=getchar();
	}
	return f?-x:x;
}//快读
int n,d=1,ans=0,zkw[maxn<<2];
struct node{
	int a,b;
	node(){a=b=0;}
	bool operator< (const node& b) const{
		return a<b.a;
	}
}num[maxn<<1];
inline void update(int pos,int val){for(pos+=d;pos;pos>>=1)zkw[pos]+=val;}
inline int query(int l,int r){int ans=0;for(l=l+d-1,r=r+d+1;l^r^1;l>>=1,r>>=1){if(~l&1)ans+=zkw[l^1];if(r&1)ans+=zkw[r^1];}return ans;}
int main(){
	n=read();
	while(d<=2*n+1)
		d<<=1;
	for(register int i=1;i<=2*n;++i){
		int x=read();
		if(num[x].a)
			num[x].b=i;
		else
			num[x].a=i;
	}
	sort(num+1,num+n+1); 
	for(register int i=1;i<=n;++i){
		ans+=query(num[i].a,num[i].b);
		update(num[i].b,1);
	}
	cout<<ans;
    return 0;
}
```

---

## 作者：communist (赞：2)

### 题外话：维护区间交集子集的小套路

开两个树状数组，一个维护进入区间，一个维护退出区间

#### $Query:$

给定询问区间$l,r$和一些其他区间，求其他区间中与$[l,r]$交集非空的区间个数

用上面维护的信息表示，就是$r$（含）前进入的区间个数$-l$（不含）前退出的区间个数

### 这个题：

我们可以把它抽象为，求区间对个数，要求区间对交集非空且互不包含

尝试像上面那样解决，$l$后进入$-r$后进入保证左端点满足要求，$l$后进入$-r$前退出，右端点满足要求

但是放到一起好像就有些问题了，尝试减掉一个条件，不妨按左端点从右向左依次插入树状数组，消掉$l$后进入这个条件

这样，查询就变成了$r$前进入$-r$前退出，我们就可以顺利解决这道题了

```
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int maxn=50010;
int n,ans,a[2*maxn],c[2][2*maxn];
vector<int>v[maxn];
int lowbit(int x)
{
    return x&-x;
}
int sum(int id,int x)
{
    int ret=0;
    while(x)
    {
        ret+=c[id][x];
        x-=lowbit(x);
    }
    return ret;
}
void add(int id,int x)
{
    while(x<=2*n)
    {
        c[id][x]++;
        x+=lowbit(x);
    }
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=2*n;i++)
	{
		scanf("%d",&a[i]);
		v[a[i]].push_back(i);
	}
	for(int i=2*n;i;i--)
		if(v[a[i]][0]==i)
		{
			int r=v[a[i]][1];
			ans+=sum(0,r)-sum(1,r);
			add(0,v[a[i]][0]),add(1,v[a[i]][1]);
		}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Amphetamine (赞：2)

没有题解，赶快来一发

题其实不难，树状数组太强大啦

考虑每一个 ai,bi如果ai,bi之间有aj且没有bj则对答案的贡献+1

维护前缀和sum[p]为在p之前只出现aj,没出现bj的j的个数

若，出现ai则在ai位置上+1，出现bi则在ai的位置上-1并更新答案


ans+=sum[bi]-sum[ai-1]

...
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n;
int cnt,mk[50010];
int ans;
int a[100010];
void add(int x,int d){
    for(;x<=n*2+5;x+=(x&(-x))){
        a[x]+=d;
    }
}
int sum(int x){
    int ret=0;
    for(;x>0;x-=(x&(-x))){
        ret+=a[x];
    }
    return ret;
}
int main()
{
    n=read();
    int x;
    for(int i=1;i<=2*n;i++){
        x=read();
        if(!mk[x])mk[x]=i,add(i,1);
        else {
            add(mk[x],-1);
            ans+=sum(i)-sum(mk[x]);
        }
    }
    cout<<ans;
    return 0;
}
...
```

---

## 作者：moosssi (赞：1)

这道题我用的是莫队。

首先读题，我一开始是没有思路的，但观察一会，可以很明显地发现，对于我们所求的答案，我们可以转化为：从 $1$ 到 $n$ 的每个数，它们第一次出现的位置到第二次之间，出现的次数为一的数的个数。这不难证明，如果只出现一次，它另一个出现的位置就在区间外，这可以满足题设要求。但是，这样会重复计算，把最终答案除二即可。

转化问题后，题目就变得清晰了，我这里是用莫队完成的后续处理，会莫队的应该都懂，具体见代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
struct nod{
	int l,r;
}q[N];
int a[N],cnt[N];
int n,len,ans,res;
bool cmp(nod x,nod y){
	if(x.l/len!=y.l/len)return x.l<y.l;
	return x.r<y.r;
}
void add(int x){
	if(cnt[x]==0)res++;//这里很简单，举例即可 
	if(cnt[x]==1)res--;
	cnt[x]++;
}
void del(int x){
	if(cnt[x]==2)res++;
	if(cnt[x]==1)res--;
	cnt[x]--;
}
int main(){
	scanf("%d",&n);
	len=sqrt(n);
	for(int i=1;i<=n*2;i++){
		scanf("%d",&a[i]);
		if(q[a[i]].l)q[a[i]].r=i;//记录第一次和第二次的位置 
		else q[a[i]].l=i;
	}
	sort(q+1,q+n+1,cmp);
	int l=1,r=0;
	for(int i=1;i<=n;i++){//莫队模板 
		while(l>q[i].l)add(a[--l]);
		while(l<q[i].l)del(a[l++]);
		while(r>q[i].r)del(a[r--]);
		while(r<q[i].r)add(a[++r]);
		ans+=res;
	}
	printf("%d",ans/2);
	return 0;
}
```




---

## 作者：Saber_Master (赞：1)

[ [USACO17FEB]Why Did the Cow Cross the Road III G](https://www.luogu.com.cn/problem/P3660)

求$x_i<x_j<y_i<y_j$的$(i,j)$点对数

偏序？

算是吧

那就先按$x_i$排序，第一维就天然有序了.

然后就是求满足$x_j<y_i<y_j$的偏序对数啦

这个我们可以利用树状数组前缀和来维护，每次查询$[x_j, y_j]$中的点数，然后按$y$插入

具体详见代码

```cpp
const ll N=1e5+5;

ll n;

namespace bit{
	ll f[N<<1];
	inline void add(ll x){
		for (; x<=n<<1; x+=x&-x) ++f[x];
	}
	
	inline ll ask(ll x){
		ll res=0;
		for (; x; x-=x&-x) res+=f[x];
		return res;
	}
}

ll res;
ll pos1[N], pos2[N];
ll A[N];

inline bool cmp(ll x, ll y){
	return pos1[x]<pos1[y];
}

int main(){
	read(n);
	for (R ll i=1, num; i<=n<<1; i++){
		read(num);
		if (pos1[num]) pos2[num]=i;
		else pos1[num]=i;
	}
	for (R ll i=1; i<=n; i++) A[i]=i;
	sort(A+1, A+n+1, cmp);
	for (R ll i=1; i<=n; i++){
		res+=bit::ask(pos2[A[i]])-bit::ask(pos1[A[i]]);
		bit::add(pos2[A[i]]);
	}
	writeln(res);
} 
```


---

## 作者：zhengrunzhe (赞：1)

a[i]<a[j]<b[i]<b[j]

可以拆成b[j]>b[i]&&a[i]<a[j]<b[i]

这是一个二维偏序问题 先排序掉第一维然后遍历一遍

i是当前遍历到的 j是之前在线段树中的 用线段树查询区间和[a[i]+1,b[i]-1]即可

```cpp
#include<cstdio>
#include<utility>
#include<algorithm>
using std::sort;
using std::pair;
using std::reverse;
using std::make_pair;
typedef pair<int,int>pii;
const int N=5e4+10;
int n,ans;
pii p[N];
class Segment_Tree
{
	private:
		struct tree
		{
			int sum;
			tree *lson,*rson;
			inline const void pushup()
			{
				sum=lson->sum+rson->sum;
			}
			inline const void update(int l,int r,int pos)
			{
				if (l==r)return (void)(sum=1);
				int mid=l+r>>1;
				if (pos<=mid)lson->update(l,mid,pos);
				else rson->update(mid+1,r,pos);
				pushup();
			}
			inline const int query(int l,int r,int L,int R)
			{
				if (l>R||r<L)return 0;
				if (l>=L&&r<=R)return sum;
				int mid=l+r>>1;
				return lson->query(l,mid,L,R)+rson->query(mid+1,r,L,R);
			}
		}memory_pool[N<<3],*root,*tail;
		inline const void build(tree *&p,int l,int r)
		{
			p=tail++;
			if (l==r)return;
			int mid=l+r>>1;
			build(p->lson,l,mid);
			build(p->rson,mid+1,r);
		}
	public:
		inline Segment_Tree(){tail=memory_pool;}
		inline const void build()
		{
			build(root,1,n<<1);
		}
		inline const void update(int pos)
		{
			root->update(1,n<<1,pos);
		}
		inline const int query(int l,int r)
		{
			if (l>r)return 0;
			return root->query(1,n<<1,l,r);
		}
}sgt;
int main()
{
	scanf("%d",&n);
	for (int x,i=1;i<=n<<1;i++)scanf("%d",&x),(p[x].second?p[x].first:p[x].second)=i;
	sort(p+1,p+n+1);reverse(p+1,p+n+1);sgt.build();
	for (int i=1;i<=n;i++)
		ans+=sgt.query(p[i].second+1,p[i].first-1),
		sgt.update(p[i].second);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：JZYshuraK (赞：1)

# Why Did the Cow Cross the Road III

题解：

这个题有一个非常不一样的地方。

我记得我之前做过的长成这样的题大概都是第一个位置+1，第二个位置-1即可。

这个题我们只能对第一个位置进行操作。

如果第一次碰见了这个数，就将当前位置+1

如果是第二次碰见了这个数，我们先更新答案，然后把这个数第一个出现的位置-1即可。

Code:
```cpp
#include <bits/stdc++.h>
#define N 100010 
using namespace std; typedef long long ll;
int tr[N<<2],vis[N],a[N<<1],n;
inline char nc() {static char *p1,*p2,buf[100000]; return (p1==p2)&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;}
int rd() {int x=0; char c=nc(); while(!isdigit(c)) c=nc(); while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=nc(); return x;}
inline int lowbit(int x) {return x&(-x);}
void update(int x,int val) {for(int i=x;i<=n;i+=lowbit(i)) tr[i]+=val;}
ll query(int x) {ll ans=0; for(int i=x;i;i-=lowbit(i)) ans+=tr[i]; return ans;}
int main()
{
	ll ans=0; n=rd()*2; for(int i=1;i<=n;i++) a[i]=rd(); for(int i=1;i<=n;i++)
	if(!vis[a[i]]) update(i,1),vis[a[i]]=i;
	else ans+=query(i)-query(vis[a[i]]),update(vis[a[i]],-1);
	cout << ans << endl ;
	return 0;
}
```
推销个人blog [JZYshuraK](https://www.cnblogs.com/ShuraK/p/10238707.html)

---

## 作者：raincity (赞：0)

## 前言
虽然解法重复了，但是我觉得这篇的讲解会比较清楚一些。

## 分析
首先，$a_i,b_i$ 可以看成一个区间 $[a_i,b_i)$。

所以，题目就是求相交的区间个数。（包含关系不算相交）

按照区间左端点排序，依次加入区间，加入时累加当前区间与之前区间相交的次数。

由于按左端点排序，如果 $j<i$ 且 $[a_j,b_j)$ 与 $[a_i,b_i)$ 相交，已经有 $a_j<a_i$，只需要 $a_i<b_j<b_i$ 即可。

也就是说，需要查询区间中有多少个数，还需要单点修改，考虑树状数组。

每一次 $ans \gets ans+sum(b_i-1)-sum(a_i)$，然后 $add(b_i)$ 即可。

时间复杂度 $O(n\log n)$。

## 解决
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 100005;
int n, tree[N];
struct Segment {
	int l, r;
	bool operator <(const Segment &other) const { return l < other.l; }
}s[N];

inline void read(int &ret) {
	char ch = getchar();
	ret = 0;
	while (ch < '0' || ch > '9') ch = getchar();
	while (ch >= '0' && ch <= '9') ret = ret * 10 + ch - '0', ch = getchar();
}

inline void add(int pos) {
	while (pos <= n + n) {
		tree[pos]++;
		pos += pos & (-pos);
	}
}

inline int sum(int pos) {
	int res = 0;
	while (pos) {
		res += tree[pos];
		pos &= pos - 1;
	}
	return res;
}

int main() {
	read(n);
	for (int i = 1, x; i <= n + n; i++) {
		read(x);
		if (s[x].l)
			s[x].r = i;
		else
			s[x].l = i;
	}
	sort(s + 1, s + n + 1);
	long long ans = 0;
	for (int i = 1; i <= n; i++) {
		ans = ans + sum(s[i].r - 1) - sum(s[i].l);
		add(s[i].r);
	}
	cout << ans << endl;
	return 0;
}
```

#### THE END

---

