# [JOI 2023 Final] 宣传 2 / Advertisement 2

## 题目描述

JOI 王国有 $N$ 位居民，编号从 $1$ 到 $N$。居民 $i$ ($1 \le i \le N$) 住在实数轴上的坐标 $X_i$ 处，其**影响力**为 $E_i$。可能有多个居民住在同一坐标处。拥有较大影响力的居民具有较高的广告潜力，但这样的居民在购买书籍时很谨慎。

Rie 出版了一本信息学的书。为了鼓励更多人购买这本书，她可以向一些居民赠送这本书的副本。如果她向居民 $i$ ($1 \le i \le N$) 赠送了一本书，居民 $i$ 将获得 Rie 的书。此外，在尚未获得书的居民中，满足以下条件的每位居民 $j$ ($1 \le j \le N$) 都会购买一本书并获得它。

- 居民 $i$ 和居民 $j$ 在实数轴上的距离小于或等于 $E_i - E_j$。换句话说，满足 $|X_i - X_j| \le E_i - E_j$。

如果所有居民都阅读了 Rie 的书，信息学奥林匹克将得到极大的认可。编写一个程序，计算需要向多少位居民赠送 Rie 的书，才能使 JOI 王国的所有居民都获得 Rie 的书。

## 说明/提示

## 样例

### 样例 1

例如，如果 Rie 按以下方式赠送书，JOI 王国的所有居民将获得 Rie 的书。

- Rie 向居民 3 赠送了一本书。
  - 因为 $|X_3 - X_1| = 1$ 且 $E_3 - E_1 = 2$，居民 1 会购买一本 Rie 的书并获得它。
  - 因为 $|X_3 - X_2| = 1$ 且 $E_3 - E_2 = 1$，居民 2 会购买一本 Rie 的书并获得它。
  - 因为 $|X_3 - X_4| = 3$ 且 $E_3 - E_4 = -1$，居民 4 不会购买 Rie 的书。
  因此，居民 1、2、3 将获得 Rie 的书。
- Rie 向居民 4 赠送了一本书。由于除了居民 4 之外的所有居民都已经获得了 Rie 的书，最终 JOI 王国的所有居民都获得了 Rie 的书。

由于不可能向少于两位居民赠送书以使 JOI 王国的所有居民都获得 Rie 的书，因此输出 2。

此样例输入满足子任务 2、3、4 的约束。

### 样例 2

此样例输入满足所有子任务的约束。

### 样例 3

此样例输入满足子任务 2、3、4 的约束。

## 约束

- $1 \le N \le 5 \times 10^5$。
- $1 \le X_i \le 10^9$ ($1 \le i \le N$)。
- $1 \le E_i \le 10^9$ ($1 \le i \le N$)。
- 给定值均为整数。

## 子任务

1. (10 分) $E_1=E_2=\cdots=E_N$。
2. (23 分) $N \le 16$。
3. (36 分) $N \le 10^3$。
4. (31 分) 无额外约束。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4
4 2
2 3
3 4
6 5
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
7 10
10 10
7 10
```

### 输出

```
2
```

## 样例 #3

### 输入

```
10
31447678 204745778
430226982 292647686
327782937 367372305
843320852 822224390
687565054 738216211
970840050 766211141
563662348 742939240
103739645 854320982
294864525 601612333
375952316 469655019
```

### 输出

```
5```

# 题解

## 作者：djh0314 (赞：10)

[**传送门**](https://www.luogu.com.cn/problem/P9350)         

## 题意
在一个数轴上有 $n$ 个人，第 $i$ 个人位于坐标 $X_i$，权值为 $E_i$。我们要送给一些人书，当 $i$ 收到了一本书，那么对于所有 $j$，满足 $\left | X_i-X_j \right | \le E_i-E_j$，那么 $j$ 会去买一本书。问最少送几个人书会使得所有人都有一本书。

## 切分

### 部分分 1（特殊性质）
所有的 $E_i$ 都相等，说明除了在同一个点的人，其他任何人无法进行传递，记录一共有多少个不同坐标即为答案。

### 部分分 2（$n\le16$） 
对于这个部分分，明显是让我们以二进制枚举来解决，枚举每一种状态，判断是否可行，最后在可行的方案间取 min。

### 部分分 3（$n\le 10^3$）
观察我们的判断的式子，我们可以分析出两个性质：
1. 我们只有可能由一个 $E_i$ 更大的转移到更小的，
2. 倘若 $i$ 能影响到 $j$，$j$ 能影响到 $k$，$k$ 必然也能直接被 $i$ 影响。这也代表，倘若我们当前点已经被影响，我们不需要再选择当前点。

由此，我们可以从 $E$ 值由大到小排序，假如当前点没有被影响过，那么枚举每个点，观察是否能被影响。否则跳过。
~~~cpp
int tot=0;
for(int i=1;i<=n;++i) {
    if(vis[i]) continue;
    ++tot;
    for(int j=i+1;j<=n;++j)
        if((a[i].E-a[j].E)>=(abs(a[i].x-a[j].x))) 
            vis[j]=1;
}
cout<<tot;	
~~~

时间复杂度：$O(n^2)$。

## 正解
对于这种绝对值的式子题，我们应当在第一时间想到把绝对值拆掉，有很多的题目都可以通过这样的方式转化成二维偏序，三维偏序问题。对于此题，我们也用拆绝对值的方式。

我们可以得到：$X_i-X_j  \le E_i-E_j \operatorname{and} X_j-X_i  \le E_i-E_j $。           
再将下标相同的放在同一边：$E_j-X_j  \operatorname{and}  E_j+X_j  \le E_i+X_i$。                      
令 $x_i=E_i+X_i$，$y_i=E_i-X_i$，   
以此在二维坐标上标记这些点（是否离散化皆可，但是图上以离散化更加明显）。    
以样例一为例（省去了离散化的过程），
![](https://cdn.luogu.com.cn/upload/image_hosting/quqfkg8q.png)
也许这还不够明显，再看看样例三的构图，
![](https://cdn.luogu.com.cn/upload/image_hosting/jv31u4qo.png)

应该明显吧，我们最后的取的点必然不能被其他点所覆盖，这也就导致，我们最后取得点将会构成一个单调下降的序列。

由此，我们用一个单调栈维护，最后答案就是留下来的数的数量。
~~~cpp

sort(a+1,a+n+1);
for(int i=1;i<=n;++i) {
	while(top&&a[q[top]].y<=a[i].y) --top;
	q[++top]=i;
} 
cout<<top;
~~~
时间复杂度：$O(n\log {}{n})$。
#### 总结一下，我们的正解先将原来的输入转化，然后以 $x$ 排序再求一个单调栈即可，建议评绿，tag 为单调栈。

---

## 作者：白简 (赞：5)

### 题目大意
在一个数轴上有 $n$ 个人，第 $i$ 个人位于坐标 $X_i$，权值为 $E_i$。我们要送给一些人书，当 $i$ 收到了一本书，那么对于所有 $j$，满足 $\left | X_i-X_j \right | \le E_i-E_j$，那么 $j$ 会去买一本书。问最少送几个人书会使得所有人都有一本书。
### 思路
我们可以考虑把题目中给出的限制转化一下。
$$
\begin{aligned}
 \left | X_i-X_j \right | \le E_i-E_j
& \Longleftrightarrow X_i-X_j\leq E_i - E_j \land X_j - X_i \leq E_i-E_j \\
& \Longleftrightarrow E_j-X_j\leq E_i - X_i \land X_j+E_j\leq X_i+E_i
\end{aligned}
$$
那么我们考虑把每个居民转化成平面直角坐标系中的一个点。

我们用 $E-X$ 当作横坐标，$E+X$ 当作纵坐标，显然我们可以发现，从原点到这个居民所在点形成的矩形是该居民影响的范围。

我们还可以发现，从左到右看，选取的点的纵坐标是单调递减的，因为如果某个点右上方还有一个点，我们会直接选择那个点而放弃当前点。

按照纵坐标从上往下扫，如果一个点的横坐标大于目前扫过的最大的横坐标时，会对答案产生贡献。
### Code
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 705000;

int n;

long long ans = 0;

struct Resident{
    long long x,y;
}t[N];

bool cmp(Resident a,Resident b) {
    if(a.y == b.y)
        return a.x > b.x;
    return a.y > b.y;
}

int main() {
    cin >> n;

    long long X,E;
    for(int i = 1;i <= n; i++) {
        cin >> X >> E;

        t[i].x = E - X;
        t[i].y = E + X;
    }

    sort(t + 1,t + n + 1,cmp);

    long long Max = LLONG_MIN >> 4;
    for(int i = 1;i <= n; i++) {
        if(t[i].x > Max)
            ans ++;
        
        Max = max(Max,t[i].x);
    }

    cout << ans << "\n";
    return 0;
}
```

---

## 作者：Hanzelic (赞：3)

# [题目链接](https://www.luogu.com.cn/problem/P9350)
这应该算是一个惯用思路吧，看到绝对值就考虑把它拆开来计算   
将 $\left|X_i-X_j\right|\le E_i-E_j$ 拆开得到：  
$\begin{cases}E_i+X_i\ge E_j+X_j\\E_i-X_i\ge E_j-X_j\end{cases}$  
我们可以将其放到一个二维平面上，令 $x_i=E_i+X_i$，$y_i=E_i-X_i$，这样我们可以得知，只要 $x_i\ge x_j$ 且 $y_i\ge y_j$，那么 $i$ 就会包含 $j$，这时我们可以想到按照 $x$ 的大小来排序，同时用单调栈来维护 $y$，最终形成一个单调下降序列，此时栈中元素的个数即是答案。  
#### 代码
```cpp
#include<bits/stdc++.h>
#define M 500005
#define int long long
using namespace std;
struct edg{
	int x,y;
}nb[M];
int n,m,a,b,c,top;
int stk[M];
bool cmp(edg a,edg b){
	if(a.x!=b.x)return a.x<b.x;
	return a.y<b.y;
}
signed main(){
	scanf("%lld",&n);
	for(int q=1;q<=n;q++){
		scanf("%lld%lld",&a,&b);
		nb[q].x=a+b,nb[q].y=b-a;
	}
	sort(nb+1,nb+n+1,cmp);
	for(int q=1;q<=n;q++){
		while(top&&nb[stk[top]].y<=nb[q].y)top--;
		stk[++top]=q;
	}
	printf("%lld\n",top);
	return 0;
}
```


---

## 作者：5k_sync_closer (赞：2)

边 $i\to j$ 存在，当且仅当 $i$ 买书后 $j$ 也会买，

发现去重后连出的图一定是 DAG，所以只需要让入度为零的人买书，问题变为统计每个点的入度。

$x_i\ge x_j$ 时边 $i\to j$ 存在，当且仅当 $e_i-x_i\ge e_j-x_j$，则 $j$ 的，来自 $x_i\ge x_j$ 的 $i$ 的入度为 $x_i\ge x_j,e_i-x_i\ge e_j-x_j$ 的 $i$ 的个数，二维数点即可。

$x_i\le x_j$ 时边 $i\to j$ 存在，当且仅当 $e_i+x_i\ge e_j+x_j$，则 $j$ 的，来自 $x_i\le x_j$ 的 $i$ 的入度为 $x_i\le x_j,e_i+x_i\ge e_j+x_j$ 的 $i$ 的个数，二维数点即可。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define H(x) lower_bound(v, v + m, x) - v + 1
using namespace std;
struct S
{
    int x, e;
} a[1000050];
int n, m, q, c[1000050], v[1000050], d[1000050];
bool B(S a, S b) { return a.x < b.x; }
bool E(S a, S b) { return a.x == b.x && a.e == b.e; }
void M(int x)
{
    for (; x; x &= x - 1)
        ++c[x];
}
int Q(int x)
{
    int q = 0;
    for (; x <= m; x += x & -x)
        q += c[x];
    return q;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d%d", &a[i].x, &a[i].e);
    sort(a + 1, a + n + 1, B);
    n = unique(a + 1, a + n + 1, E) - a - 1;
    for (int i = 1; i <= n; ++i)
        v[m++] = a[i].e + a[i].x;
    sort(v, v + m);
    m = unique(v, v + m) - v;
    for (int i = 1, z; i <= n; ++i)
        d[i] += Q(z = H(a[i].e + a[i].x)), M(z);
    memset(c, m = 0, sizeof c);
    for (int i = 1; i <= n; ++i)
        v[m++] = a[i].e - a[i].x;
    sort(v, v + m);
    m = unique(v, v + m) - v;
    for (int i = n, z; i >= 1; --i)
        d[i] += Q(z = H(a[i].e - a[i].x)), M(z);
    for (int i = 1; i <= n; ++i)
        q += !d[i];
    printf("%d", q);
    return 0;
}
```


---

## 作者：jijidawang (赞：2)

不难发现将每个居民的 $X_i,E_i$ 看成二维平面上的一个点 $(X_i,E_i)$，那么满足 $|X_i-x|\le E_i-y$ 的 $(x,y)$ 在二维平面上表现为 $(X_i,E_i)$「右侧」的直角三角形。形式化的，半平面 $y-x\le E_i+X_i$ 和半平面 $x+y\le E_i+X_i$ 的交。 
 
那么连完边后图是一个 DAG，不难发现答案就是入度为 0 的点的个数，根据以上结论，对于点 $(i,j)$，有边 $i\to j$ 当且仅当 $(X_j,E_j)$ 在 $(X_i,E_i)$ 右侧的直角三角形内，也就是 $(X_i,E_i)$ 在 $(X_j,E_j)$ 左侧的直角三角形内。从而问题变成计数某点左侧直角三角形点的个数。

可以将「左侧的直角三角形」看成一侧的曼哈顿距离，那么使用变换：曼哈顿距离转切比雪夫距离 $(x,y)\to(x+y,x-y)$，这样的区域就变成一个矩形，问题也即变为二维数点。这是我们熟悉的问题，扫描线即可解决。

时间复杂度 $O(n\log n)$，可以通过。

---

## 作者：free_fall (赞：2)

看到题目首先想到一种贪心：

按照 $E_i$ 从大到小排序，当前居民若没有书就送他一本，答案加一，然后暴力标记所有这个人可以影响到的人，之后不再搜索。

这种做法的时间复杂度是 $O(n^2)$，会超时，考虑优化。

先拆分式子：

$|X_i-X_j| \le E_i-E_j$

$X_i-X_j \le E_i-E_j$ 且 $X_j-X_i \le E_i-E_j$

$E_i-X_i \ge E_j-X_j$ 且 $X_i+E_i \ge X_j+E_j$

于是我们可以建立坐标系，$E_i-X_i$ 为横坐标，$E_i+X_i$ 为纵坐标，从上往下扫，当一个点的 $x$ 坐标小于等于当前扫过的点中最大的 $x$ 坐标时对答案没有贡献，否则答案加一。

时间复杂度为 $O(n \log n)$。
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5,inf=0x3f3f3f3f3f3f3f3f;
int n,ans,now=-inf;
struct kk{
	int x,y;
	bool operator<(const kk &o)const{
		if(y==o.y)return x>o.x;
		return y>o.y;
	}
}a[N];
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		int x,e;
		scanf("%lld%lld",&x,&e);
		a[i]={e-x,e+x};
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		if(a[i].x>now)ans++;
		now=max(now,a[i].x);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：int_R (赞：1)

[P9350 [JOI 2023 Final] Advertisement 2](https://www.luogu.com.cn/problem/P9350)

做法相较先前题解做法有点暴力易想。

首先是可以想到，影响力（$E_i$）值最大的肯定不是购买的，因为没有人可以影响到他。

以此类推，我们可以将这些人按 $E_i$ 值降序排序，依次考虑当前这个人是否需要被赠送。即如果这个人不能被前面被赠送过的人所影响，就要赠送给他。正确性易证。

考虑如何快速判断，见绝对值尝试拆绝对值。

$$|X_i-X_j|\leq E_i-E_j$$

$$
\begin{cases}
X_j+E_j\leq X_i+E_i &(X_i\leq X_j)\\X_j-E_j\geq X_i-E_i &(X_i\geq X_j)
\end{cases}
$$

就变成了单点取 max（min），区间查 max（min）。

具体的，我们考虑开两颗权值线段树，每次如果新赠送给了一个人，就是在第一颗线段树上 $X_i$ 的位置与 $X_i+E_i$ 取最大值，在第二颗线段树上 $X_i$ 的位置与 $X_i-E_i$ 取最小值。

判断则只需要查询第一颗线段树上 $(0,X_i]$ 的最大值是否大于 $X_i+E_i$，第二颗线段树上 $[X_i,+\infty)$ 的最小值是否小于 $X_i-E_i$。

总时间复杂度 $O(n\log W)$，$W$ 为值域，即 $10^9$。可以通过先离散化做到 $O(n\log n)$。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=5e5+10,INF=2e9+10;
int n,ans;
struct node{int x,e;}p[MAXN];
struct tree1
{
    struct tree{int num,ls,rs;}t[30000000];int cnt=1;
    inline void push_up(int p){t[p].num=max(t[t[p].ls].num,t[t[p].rs].num);}
    inline void change(int l,int r,int p,int x,int z)
    {
        if(l==r){t[p].num=max(t[p].num,z);return ;}
        int mid=(l+r)>>1;
        if(x<=mid) change(l,mid,t[p].ls?t[p].ls:t[p].ls=++cnt,x,z);
        else change(mid+1,r,t[p].rs?t[p].rs:t[p].rs=++cnt,x,z);
        push_up(p);return ;
    }
    inline int query(int l,int r,int p,int x,int y)
    {
        if(x<=l&&y>=r) return t[p].num;
        int mid=(l+r)>>1,ans=0;
        if(x<=mid&&t[p].ls) ans=max(ans,query(l,mid,t[p].ls,x,y));
        if(y>mid&&t[p].rs) ans=max(ans,query(mid+1,r,t[p].rs,x,y));
        return ans;
    }
}a;
struct tree2
{
    struct tree{int num,ls,rs;}t[30000000];int cnt=1;
    inline void push_up(int p)
    {
        if(!t[p].ls) t[p].num=t[t[p].rs].num;
        if(!t[p].rs) t[p].num=t[t[p].ls].num;
        if(t[p].ls&&t[p].rs) t[p].num=min(t[t[p].ls].num,t[t[p].rs].num);
        return ;
    }
    inline void change(int l,int r,int p,int x,int z)
    {
        if(l==r){t[p].num=min(t[p].num,z);return ;}
        int mid=(l+r)>>1;
        if(x<=mid)
        {
            if(!t[p].ls) t[p].ls=++cnt,t[cnt].num=INF;
            change(l,mid,t[p].ls,x,z);
        }
        else
        {
            if(!t[p].rs) t[p].rs=++cnt,t[cnt].num=INF;
            change(mid+1,r,t[p].rs,x,z);
        }
        push_up(p);return ;
    }
    inline int query(int l,int r,int p,int x,int y)
    {
        if(x<=l&&y>=r) return t[p].num;
        int mid=(l+r)>>1,ans=INF;
        if(x<=mid&&t[p].ls) ans=min(ans,query(l,mid,t[p].ls,x,y));
        if(y>mid&&t[p].rs) ans=min(ans,query(mid+1,r,t[p].rs,x,y));
        return ans;
    }
}b;
inline bool cmp(node x,node y){return x.e>y.e;}
int main()
{
    cin.tie(0),cout.tie(0);
    ios::sync_with_stdio(0);
    cin>>n;b.t[1].num=INF;
    for(register int i=1;i<=n;++i) cin>>p[i].x>>p[i].e;
    sort(p+1,p+1+n,cmp);
    for(register int i=1;i<=n;++i)
    {
        if(a.query(1,1e9,1,1,p[i].x)>=p[i].x+p[i].e) continue;
        if(b.query(1,1e9,1,p[i].x,1e9)<=p[i].x-p[i].e) continue;
        ++ans;
        a.change(1,1e9,1,p[i].x,p[i].x+p[i].e);
        b.change(1,1e9,1,p[i].x,p[i].x-p[i].e);
    }
    cout<<ans<<'\n';return 0;
}
```


---

## 作者：User_Unauthorized (赞：0)

## 题解

JOI 王国有 $N$ 位居民，从 $1$ 到 $N$ 编号。居民 $i$（$1\le i\le N$）居住在数轴上坐标 $X_i$ 处，其**影响力**为 $E_i$。同一个坐标可能住了多于一位居民。居民的影响力越高，广告效应也越高，但买书也越谨慎。

Rie 出版了一本关于信息学的书。为了让更多人购买这本书，她可以给一些居民送书。如果她给居民 $i$（$1\le i\le N$）送了一本书，除了居民 $i$ 将得到一本 Rie 的书外，在还没有得到这本书的居民中，每一个满足以下条件的居民 $j$（$1\le j\le N$）都会购买这本书：

- 居民 $i$ 和居民 $j$ 在数轴上的距离小于或等于 $E_i - E_j$。换句话说，$|X_i - X_j| \le E_i - E_j$ 成立。

如果所有的居民都读了 Rie 的书，信息学竞赛将得到极大的认可。请写一个程序，计算 Rie 最少将书赠送给多少位居民，就可以让 JOI 王国的所有居民都会得到 Rie 的书。

## 题解

考虑转化题目中的限制式

$$\left\lvert X_i - X_j\right\rvert \le E_i - E_j$$

首先拆开绝对值

$$X_i - X_j \le E_i - E_j \land X_j - X_i \le E_i - E_j$$

接下来移项

$$E_j - X_j \le E_i + X_i \land X_j + E_j \le E_i + X_i$$

考虑其几何意义，对于第 $i$ 个人 $\left(E_i, X_i\right)$，将 $E_i - X_i$ 看作横坐标，将 $E_i + X_i$ 看作纵坐标。将点 $\left(E_i - X_i, E_i + X_i\right)$ 放到笛卡尔坐标系上，再结合限制式可以发现会受这个人影响的对应点处于该点和原点构成的矩形内。

考虑用尽可能少的点和原点组成的举行覆盖所有点，可以发现最终答案的断点一定是纵坐标随横坐标递增而递减的，使用单调栈维护即可。

## Code
```cpp
#include <bits/stdc++.h>

typedef int valueType;
typedef std::pair<valueType, valueType> ValuePair;
typedef std::vector<ValuePair> PairVector;
typedef std::stack<ValuePair> Stack;

int main() {
    valueType N;

    std::cin >> N;

    PairVector source(N);

    for (auto &iter: source) {
        valueType X, E;

        std::cin >> X >> E;

        iter = std::make_pair(E - X, E + X);
    }

    std::sort(source.begin(), source.end());

    Stack stack;

    for (auto const &iter: source) {
        while (!stack.empty() && stack.top().second <= iter.second)
            stack.pop();

        stack.push(iter);
    }

    std::cout << stack.size() << std::endl;

    return 0;
}
```

---

## 作者：AkeRi (赞：0)

# Description
略。

# Solution
转化题。

我们把整个坐标抽象成二维平面，$x_i$ 为横坐标，$e_i$ 为纵坐标。

## 10pts

$e_i$ 均相等，则任意两点的 $\Delta e$ 均为 $0$，也就是说只能覆盖自己。

输出有多少个坐标有人即可。

## 33pts

爆搜，枚举每个人的选择情况并判断。时间复杂度 $\text{O}(n^2\times 2^n)$。

## 69pts
考虑拆式子。
 $$ \lvert x_i-x_j\rvert\le e_i-e_j$$
即
 $$x_i-x_j\le e_i-e_j \text{ and } x_j-x_i\le e_i-e_j$$
也就是
 $$ x_i-e_i\le x_j-e_j\text{ and } x_j+e_j\le x_i+e_i$$
 
我们令 $a_i=x_i-e_i,b_i=x_i+e_i$，则有
$$a_i\le a_j \text{ and } b_j\le b_i$$

考虑这样一个贪心：我们给书一定给**当前没有**书的居民中，$a_i$ 最小中，$b_i$ 最大的那一个。

找到这个点，将满足条件的打上标记，暴力判断是否完成即可。

时间复杂度 $\text{O}(n^2)$。

## 100pts

我们其实不需要打标记判断，直接根据 $b_i$ 的值更新即可。

统计答案复杂度 $\text{O}(n)$，排序复杂度 $\text{O}(n\log n)$。

```cpp
int x[KI],E[KI];
std::pair<int,int>p[KI];
int _;
bool mys(std::pair<int,int> A,std::pair<int,int> B)
{
    return A.first==B.first?A.second>B.second:A.first<B.first;
}
int main()
{   
    int n=read();
    for(int i=1;i<=n;i++) x[i]=read(),E[i]=read();
    for(int i=1;i<=n;i++)
    {
        p[++_].first=x[i]-E[i];
        p[_].second=x[i]+E[i];
    }
    std::sort(p+1,p+_+1,mys);
    int max=-INT_MAX,ans=0;
    for(int i=1;i<=_;i++) if(max<p[i].second) max=p[i].second,ans++;
    std::cout<<ans<<'\n';
}
```

---

