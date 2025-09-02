# [COCI 2020/2021 #1] 3D Histogram

## 题目背景

~~原题目背景其实是一个出毒瘤题的套路，有兴趣的同学可以去看看，这里懒得翻译了~~

## 题目描述

在一个三维直方图中，放入 $n$ 个三维块，这些三维块的宽度均为 $1$，且能使得在正面看是一个从左到右分别高度为 $a_i$ 的二维直方图，在上面看是一个从左到右分别高度为 $b_i$ 的二维直方图。

求在直方图中能放入的最大体积长方体的体积是多少，长方体的所有边均要与三维块的长宽高平行。

## 说明/提示

#### 样例 1 解释

描述的直方图如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/z2txhsvt.png)

能放入的最大长方体体积为 $2 \times 4 \times 3=24$。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（20 pts）：$1 \le n \le 2000$。
- Subtask 2（90 pts）：$1 \le n \le 2 \times 10^5$。

对于 $100\%$ 的数据，$1 \le a_i,b_i \le 10^6$。

**本题满分 $110$ 分。**

#### 说明

翻译自 [Croatian Open Competition in Informatics 2020 ~ 2021 Round 1 C 3D Histogram](https://hsin.hr/coci/archive/2020_2021/contest1_tasks.pdf)。

## 样例 #1

### 输入

```
5
5 3
4 4
2 1
3 2
1 5```

### 输出

```
24```

## 样例 #2

### 输入

```
6
3 1
2 1
2 2
2 3
1 1
2 2```

### 输出

```
8```

## 样例 #3

### 输入

```
5
15 19
5 6
1 13
3 7
1 2
```

### 输出

```
285```

# 题解

## 作者：DrBit (赞：5)

[题面链接](https://www.luogu.com.cn/problem/P7164)

这里介绍一下官方题解的做法

考虑分治，那么重点就来到了怎么计算横跨区间中点的贡献

设 $f(i,j)$ 表示区间 $[i,j]$ 内 $a$ 的最小值，$g(i,j)$ 表示区间 $[i,j]$ 内 $b$ 的最小值。

那么一个区间 $[l,r]$ 的贡献就是 $f(l,r) \times g(l,r) \times (r-l+1) $。

设分治区间中点为 mid，接下来对 $f(i,j)$ 和 $g(i,j)$ 的来源做讨论：

1. 两者都来自 mid 左边
2. 两者都来自 mid 右边
3. f 的最小值来自左边，g 的最小值来自右边
4. g 的最小值来自左边，f 的最小值来自右边

其中情况 1 和情况 2 很好处理，双指针扫一遍即可。对于每一个确定的 l 找到一个 r 使得 $f(mid+1,r)$ 和 $g(mid+1,r)$ 恰好大于 $f(l,mid)$ 和 $g(l,mid)$。因为随着 l 的左移 $f(l,mid)$ 和 $g(l,mid)$ 都是单调减少的所以 r 单调往右能走多远走多远即可。

难点在于情况3、4的处理，这里以情况3为例：

拆一下铈子:
$$ f(l,mid) \times g(mid+1,r) \times (r-l+1) = $$
$$ -l \times f(l,mid) \times g(mid+1,r) + (1+r) \times f(l,mid) \times g(mid+1,r) = $$
$$((l \times f(l,mid)) , f(l,mid)) \cdot (-g(mid+1,r) , (1+r) \times (g(mid+1,r)) $$

因为对于每一个确定的 l ，r 的取值范围是固定的（方法和上面情况1、2类似），所以我们要快速求出在区间内与 l 的那个向量作点积的值最大的 r 的那个向量。

然后我们发现了[这道题](https://www.luogu.com.cn/problem/P3309)

算一下复杂度：分治+线段树维护凸包+三分，$O(N\log^3N)$，肯定是过不去的。

然后我们发现，$l \times f(l,mid)$ 和 $f(l,mid)$ 都是随着 l 单调递减的，所以说 l 对应的向量在不断地逆时针转动，所以线段树维护的每个区间内的最优解也应该是单调地逆时针转动（思考一下为什么）。对于每次分治求解，我们对线段树的每个节点记录一下上次查询得到的最优值的位置，单调地向一个方向移动，这样我们就省去了三分的复杂度，$O(N\log^2N)$成功 AC。

~~本人人傻常数大，开了 O2 才勉强过了的样子，代码十分不建议参考~~

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ls (x << 1)
#define rs ((x << 1) | 1)
#define int long long 
using namespace std;
const int MAXN = 2e6 + 50;
const int MAXM = 25;
const int INF = 0x3f3f3f3f3f3f3f3f;
int w[MAXN], h[MAXN], minw[MAXN][MAXM], minh[MAXN][MAXM];
int idx[MAXN], lg[MAXN];
int N;
struct node
{
    int x, y;
    node(){}
    node(int a, int b)
    {
        x = a;
        y = b;
    }
    bool operator<(const node &tmp) const
    {
        return (x == tmp.x) ? y < tmp.y : x < tmp.x;
    }
    node operator+(const node &tmp) const
    {
        return node(x + tmp.x, y + tmp.y);
    }
    node operator-(const node &tmp) const
    {
        return node(x - tmp.x, y - tmp.y);
    }
    int operator*(const node &tmp) const
    {
        return x * tmp.y - y * tmp.x;
    }
} s[MAXN * 10], po[MAXN], q[MAXN * 2], p[MAXN];
int tot, ans;
struct SegT
{
    int lt[MAXN * 4], rt[MAXN * 4], pos[MAXN * 4];
    void build(int x, int l, int r)
    {
        int cnt = 0;
        for (int i = l; i <= r; ++i)
            p[++cnt] = po[i];
        // sort(p + 1, p + cnt + 1);
        int top = 0;
        for (int i = 1; i <= cnt; ++i)
        {
            while (top > 1 && (q[top] - q[top - 1]) * (p[i] - q[top]) >= 0)
                top--;
            q[++top] = p[i];
        }
        lt[x] = tot + 1;
        for (int i = 1; i <= top; ++i)
        {
            s[++tot] = q[i];
            q[i] = node(0, 0);
        }
        rt[x] = tot;
        pos[x] = rt[x];
    }
    void update(int x, int l, int r, int t)
    {
        if (r == t)
            build(x, l, r);
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        if (t <= mid)
            update(ls, l, mid, t);
        else
            update(rs, mid + 1, r, t);
    }
    bool check(int x, node t)
    {
        return (s[x - 1].x * t.x + s[x - 1].y * t.y >= s[x].x * t.x + s[x].y * t.y);
    }
    int calc(int x, node t)
    {
        int now = pos[x];
        while (check(now, t) && now > lt[x])
            now--;
        pos[x] = now;
        return s[now].x * t.x + s[now].y * t.y;
    }
    int query(int x, int l, int r, int tl, int tr, node t)
    {
        if (tl > r || tr < l)
            return -INF;
        if (tl <= l && tr >= r)
            return calc(x, t);
        int mid = (l + r) >> 1;
        return max(query(ls, l, mid, tl, tr, t), query(rs, mid + 1, r, tl, tr, t));
    }
} T;
void rmqpre()
{
    for (int i = 1; i <= N; ++i)
    {
        minw[i][0] = w[i];
        minh[i][0] = h[i];
    }
    for (int j = 1; j <= 20; ++j)
        for (int i = 1; i <= N; ++i)
        {
            minw[i][j] = min(minw[i][j - 1], minw[i + (1 << (j - 1))][j - 1]);
            minh[i][j] = min(minh[i][j - 1], minh[i + (1 << (j - 1))][j - 1]);
        }
}
inline int geth(int l, int r)
{
    int len = r - l + 1;
    int k = lg[len];
    return min(minh[l][k], minh[r - (1 << k) + 1][k]);
}
inline int getw(int l, int r)
{
    int len = r - l + 1;
    int k = lg[len];
    return min(minw[l][k], minw[r - (1 << k) + 1][k]);
}
void calc1(int l, int r)
{
    int mid = (l + r) >> 1;
    int lt = mid;
    int rt = mid;
    while (lt >= l)
    {
        while (getw(mid + 1, rt + 1) >= getw(lt, mid) && geth(mid + 1, rt + 1) >= geth(lt, mid) && rt < r)
            rt++;
        if (rt > mid)
            ans = max(ans, (rt - lt + 1) * getw(lt, mid) * geth(lt, mid));
        lt--;
    }
}
void calc2(int l, int r)
{
    int mid = (l + r) >> 1;
    int lt = mid + 1;
    int rt = mid + 1;
    while(rt <= r)
    {
        while (getw(lt - 1, mid) >= getw(mid + 1, rt) && geth(lt - 1, mid) >= geth(mid + 1, rt) && lt > l)
            lt--;
        if (lt < mid + 1)
            ans = max(ans, (rt - lt + 1) * getw(mid + 1, rt) * geth(mid + 1, rt));
        rt++;
    }
}
void clear(int l, int r)
{
    tot = 0;
}
void calc3(int l, int r)//w->r,h->l
{
    int mid = (l + r) >> 1;
    int tt = 0;
    clear(l, r);
    for (int i = mid + 1; i <= r; ++i)
    {
        po[++tt] = node(-getw(mid + 1, i), getw(mid + 1, i) * (1 + i));
        T.update(1, 1, N, tt);
    }
    int lt = mid;
    int rt = mid;
    for (int i = mid; i >= l; --i)
    {
        while (getw(mid + 1, lt + 1) >= getw(i, mid) && lt < r)
            lt++;
        while (geth(mid + 1, rt + 1) >= geth(i, mid) && rt < r)
            rt++;
        if (rt > mid && rt > lt)
        {
            ans = max(ans, T.query(1, 1, N, lt - mid + 1, rt - mid, node(i * geth(i, mid), geth(i, mid))));
            // cout << mid << " " << i << ":" << lt << " " << rt << ":" << ans << " " << endl;
        }
    }
}
void calc4(int l, int r)//h->r,w->l
{
    int mid = (l + r) >> 1;
    int tt = 0;
    clear(l, r);
    for (int i = mid + 1; i <= r; ++i)
    {
        po[++tt] = node(-geth(mid + 1, i), geth(mid + 1, i) * (1 + i));
        T.update(1, 1, N, tt);
    }
    int lt = mid;
    int rt = mid;
    for (int i = mid; i >= l; --i)
    {
        while (geth(mid + 1, lt + 1) >= geth(i, mid) && lt < r)
            lt++;
        while (getw(mid + 1, rt + 1) >= getw(i, mid) && rt < r)
            rt++;
        if (rt > mid && rt > lt)
        {
            ans = max(ans, T.query(1, 1, N, lt - mid + 1, rt - mid, node(i * getw(i, mid), getw(i, mid))));
            // cout << mid << " " << i << ":" << lt << " " << rt << ":" << ans << endl;
        }
    }
}
void solve(int l, int r)
{
    if (l == r)
    {
        ans = max(w[l] * h[l], ans);
        return;
    }
    int mid = (l + r) >> 1;
    solve(l, mid);
    solve(mid + 1, r);
    calc1(l, r);
    calc2(l, r);
    calc3(l, r);
    calc4(l, r);
}
signed main()
{
    // freopen("test.in", "r", stdin);
    scanf("%lld", &N);
    for (int i = 1; i <= N; ++i)
        scanf("%lld%lld", &h[i], &w[i]);
    rmqpre();
    lg[1] = 0;
    for (int i = 2; i <= N; ++i)
        lg[i] = lg[i >> 1] + 1;
    ans = 0;
    solve(1, N);
    printf("%lld\n", ans);
    return 0;
}

```


---

## 作者：xiaofu15191 (赞：3)

提供一种非常奇怪的方法。

很容易想到 $O(n^2)$ 的暴力：枚举左右端点，取中间的 $a_i$ 与 $b_i$ 最小值算面积。

考虑目前搜到左端点为 $i$，右端点为 $j$ 的情况。显然 $a_i \times b_i$ 的值单调不增。令 $s=a_i \times b_i$，每次更新答案之后，我们将 $j$ 跳到 $ans \div s+i-1$ 处，即最早的一个可能更新答案的点。由于数据水就过了。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const long long INF=1145141919810;
long long a[200010],b[200010],f_a[200010][20],f_b[200010][20];
long long find_a(long long l,long long r)
{
	long long q=log2(r-l+1);
	return min(f_a[l][q],f_a[r-(1<<q)+1][q]);
}
long long find_b(long long l,long long r)
{
	long long q=log2(r-l+1);
	return min(f_b[l][q],f_b[r-(1<<q)+1][q]);
}
int main()
{
	long long n;
	scanf("%lld",&n);
	for(long long i=1;i<=n;i++)
		scanf("%lld%lld",&a[i],&b[i]);
	for(long long i=n;i>=1;i--)
	{
		f_a[i][0]=a[i];
		for(long long j=1;i+(1<<j)-1<=n;j++)
			f_a[i][j]=min(f_a[i][j-1],f_a[i+(1<<(j-1))][j-1]);
	}
	for(long long i=n;i>=1;i--)
	{
		f_b[i][0]=b[i];
		for(long long j=1;i+(1<<j)-1<=n;j++)
			f_b[i][j]=min(f_b[i][j-1],f_b[i+(1<<(j-1))][j-1]);
	}
	long long ans=0;
	for(long long i=1;i<=n;i++)
		for(long long j=i;j<=n;j++)
		{
			long long tmp=find_a(i,j)*find_b(i,j);
			ans=max(ans,tmp*(j-i+1));
			j=(long long)(ans/tmp)+i-1;
		}
	printf("%lld\n",ans);
}
```

> 注：实际上这种做法是可以被卡掉的，[生成器](https://www.luogu.com.cn/paste/5xdi12xj)。但是目前最优解的第一页都是这种做法，且快于计算几何正解。

> 且[这篇题解](https://www.luogu.com.cn/article/ujaqadl5)在这个数据生成器生成的数据下也会被卡。

---

## 作者：letitdown (赞：2)

发现题解区没有本做法于是来发一篇~

题目大意就是让求 

$$\max\limits_{j\leq i}\{(i-j+1)\min\limits_{k=j}^ia_k\min\limits_{k=i}^jb_k\}$$

那么我们考虑把上面的式子拆成三项相乘，移动指针 $i$ 维护每个指针 $j$ 到它的答案，每次取 max 即可。

切换一下变量名，设 $av$ 为题目中给出的 $a$ 数组，$a_j$ 为 $\min\limits_{k=j}^{i}av_k$，剩下两个数组类似。

首先接着让我们拆一下式子。下面钦定 $j\geq k$，则$a_j\geq a_k,b_j\geq b_k$。

如果令 $v_i=a_i\times b_i$，则若对于当前的 $i$，$ans_j\geq ans_k$，有：

$$(i-j+1)v_j\geq (i-k+1)v_k$$
$$(v_j-v_k)(i+1)\geq jv_j-kv_k$$
$$i+1\geq \frac{jv_j-kv_k}{(v_j-v_k)}$$

容易看出，只要我们维护出一个凸包就可以求最值了。

那么如何维护呢？

我们使用单调栈求出对于当前的 $i$，第二项需要改变的范围 $[l_1,i]$，第三项需要改变的范围 $[l_2,i]$，在下图中讨论 $l_1\leq l_2$的情况，$l_2\leq l_1$ 的情况类似。位置关系如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/ttsbm0z6.png)

对于修改操作：

对于 $j\in[l_1,l_2)$ 要将所有的 $a_j\to av_i$，对于 $j\in[l_2,i]$ 要将所有的 $a_j\to av_i,b_j\to bv_i$。

区间赋值大家都会，问题是如何维护凸包。修改后显然有对于 $j\in[l_2,i]$ 只有 $l_2$ 这个位置可能在凸包上继续存在，所以把别的位置都删掉就行了。对于 $j\in[l_1,l_2)$ 有任意 $a_j$ 相等，那么接上上面的式子，有：

$$i+1\geq \frac{ja_jb_j-ka_kb_k}{a_jb_j-a_kb_k}$$
$$i+1\geq \frac{jb_j-kb_k}{b_j-b_k}$$

发现凸包和 $a$ 无关，于是我们另外维护一个 $b$ 的凸包，求答案时乘上一个 $a$ 就可以了。

相对应的另一种情况我们也要维护 $a$ 的凸包，但是在上面的情况中显然有对于 $j\in[l_1,l_2)$ 只有 $l_1$ 这个位置可能在凸包上继续存在。于是把别的位置都删掉就行了。

剩下部分不用动。然后我们直接在凸包上二分就行了......吗？

如果用线段树这样做，一个父节点无法轻易合并两个子节点信息。所以我们考虑分块。设块长为 $B$。

对于散块修改，我们暴力重构，复杂度 $O(B)$，整块打上区间赋值标记即可，复杂度 $O(\frac{n}{B})$ 。

对于查询操作，散块可以暴力取最值，复杂度 $O(B)$ ，整块可以在凸包上二分，复杂度 $O(\frac{n}{B}\log n)$。

那么总复杂度就是 $O(n(B+\frac{n}{B}\log n))$ 的，容易发现当 $B$ 取到 $\sqrt{n\log n}$ 时理论复杂度最优，为 $O(n\sqrt{n\log n})$。

上面讨论的是时间复杂度，而空间复杂度由于只需要对每个块开块长的凸包，是 $O(n)$ 的。~~爆标了~~


### Code

```cpp

#include<cassert>
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
namespace EMT{
	typedef long long ll;typedef long double db;
	#define pf printf
	#define F(i,a,b) for(int i=a;i<=b;i++)
	#define D(i,a,b) for(int i=a;i>=b;i--)
	inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
	inline void file(){freopen("cuboid.in","r",stdin);freopen("cuboid.out","w",stdout);}
	inline ll max(ll a,ll b){return a>b?a:b;}inline int min(int a,int b){return a<b?a:b;}
	inline void pi(int x){pf("%d ",x);}inline void pn(){pf("\n");}
	const int N=2e5+10,B=200;const db inf=1e18;
	struct dp{ll x,y;db K;friend bool operator <(dp a,dp b){return a.K<b.K;}}s[N/B+10][3][B+10];
	int top[N/B+10][3],bel[N],L[N/B+10],R[N/B+10],n,a[N],b[N],av[N],bv[N],lz1[N/B+10],lz2[N/B+10],nw;ll ans;
	inline db slope(dp &a,dp &b){return (db)(a.y-b.y)/(db)(a.x-b.x);}
	inline void down(int x){
		int lim=min(nw,R[x]);
		if(lz1[x]){F(i,L[x],lim)a[i]=lz1[x];lz1[x]=0;}
		if(lz2[x]){F(i,L[x],lim)b[i]=lz2[x];lz2[x]=0;}
	}
	inline void build(int x){
		int lim=min(nw,R[x]);
		top[x][0]=0;
		F(i,L[x],lim){
			if(i>L[x]&&a[i]==a[i-1])continue;
			dp p={a[i],1ll*i*a[i],0};
			while(top[x][0]>1&&slope(s[x][0][top[x][0]-1],p)<=s[x][0][top[x][0]-1].K)top[x][0]--;
			if(top[x][0])s[x][0][top[x][0]].K=slope(s[x][0][top[x][0]],p);s[x][0][++top[x][0]]=p;
		}s[x][0][top[x][0]].K=inf;
		top[x][1]=0;
		F(i,L[x],lim){
			if(i>L[x]&&b[i]==b[i-1])continue;
			dp p={b[i],1ll*i*b[i],0};
			while(top[x][1]>1&&slope(s[x][1][top[x][1]-1],p)<=s[x][1][top[x][1]-1].K)top[x][1]--;
			if(top[x][1])s[x][1][top[x][1]].K=slope(s[x][1][top[x][1]],p);s[x][1][++top[x][1]]=p;
		}s[x][1][top[x][1]].K=inf;
		top[x][2]=0;
		F(i,L[x],lim){
			if(i>L[x]&&1ll*a[i]*b[i]==1ll*a[i-1]*b[i-1])continue;
			dp p={1ll*a[i]*b[i],1ll*i*a[i]*b[i],0};
			while(top[x][2]>1&&slope(s[x][2][top[x][2]-1],p)<=s[x][2][top[x][2]-1].K)top[x][2]--;
			if(top[x][2])s[x][2][top[x][2]].K=slope(s[x][2][top[x][2]],p);s[x][2][++top[x][2]]=p;
		}s[x][2][top[x][2]].K=inf;
	}
	inline void change1(int l,int r,int tp,int v){
		if(bel[l]==bel[r]){
			down(bel[l]);
			F(i,l,r)if(tp==1)a[i]=v;else b[i]=v;
			build(bel[l]);
		}else{
			down(bel[l]),down(bel[r]);
			F(i,l,R[bel[l]])if(tp==1)a[i]=v;else b[i]=v;
			F(i,L[bel[r]],r)if(tp==1)a[i]=v;else b[i]=v;
			build(bel[l]),build(bel[r]);
			F(i,bel[l]+1,bel[r]-1){
				if(tp==1){
					lz1[i]=v;
					s[i][0][top[i][0]=1]={v,1ll*L[i]*v,inf};
				}else{
					lz2[i]=v;
					s[i][1][top[i][1]=1]={v,1ll*L[i]*v,inf};
				}
			}
		}
	}
	inline void change2(int l,int r,int v1,int v2){
		if(bel[l]==bel[r]){
			down(bel[l]);
			F(i,l,r)a[i]=v1,b[i]=v2;
			build(bel[l]);
		}else{
			down(bel[l]),down(bel[r]);
			F(i,l,R[bel[l]])a[i]=v1,b[i]=v2;
			F(i,L[bel[r]],r)a[i]=v1,b[i]=v2;
			build(bel[l]),build(bel[r]);
			F(i,bel[l]+1,bel[r]-1){
				lz1[i]=v1,lz2[i]=v2;
				s[i][0][top[i][0]=1]={v1,1ll*L[i]*v1,inf};
				s[i][1][top[i][1]=1]={v2,1ll*L[i]*v2,inf};
			}
		}
	}
	inline ll clac(dp &p,int v){
		return 1ll*v*p.x-p.y;
	}
	inline void ask(int l,int r,int v){
		if(bel[l]==bel[r]){
			down(bel[l]);
			F(i,l,r)ans=max(ans,1ll*a[i]*b[i]*(nw-i+1));
		}else{
			down(bel[l]),down(bel[r]);
			F(i,l,R[bel[l]])ans=max(ans,1ll*a[i]*b[i]*(nw-i+1));
			F(i,L[bel[r]],r)ans=max(ans,1ll*a[i]*b[i]*(nw-i+1));
			F(i,bel[l]+1,bel[r]-1){
				if(lz1[i]){
					int x=std::lower_bound(s[i][1]+1,s[i][1]+top[i][1]+1,(dp){0,0,(db)v})-s[i][1];
					if(x<=top[i][1])ans=max(ans,1ll*lz1[i]*clac(s[i][1][x],v));
					if(x+1<=top[i][1])ans=max(ans,1ll*lz1[i]*clac(s[i][1][x+1],v));
					if(x-1)ans=max(ans,1ll*lz1[i]*clac(s[i][1][x-1],v));
				}else if(lz2[i]){
					int x=std::lower_bound(s[i][0]+1,s[i][0]+top[i][0]+1,(dp){0,0,(db)v})-s[i][0];
					if(x<=top[i][0])ans=max(ans,1ll*lz2[i]*clac(s[i][0][x],v));
					if(x+1<=top[i][0])ans=max(ans,1ll*lz2[i]*clac(s[i][0][x+1],v));
					if(x-1)ans=max(ans,1ll*lz2[i]*clac(s[i][0][x-1],v));
				}else{
					int x=std::lower_bound(s[i][2]+1,s[i][2]+top[i][2]+1,(dp){0,0,(db)v})-s[i][2];
					if(x<=top[i][2])ans=max(ans,clac(s[i][2][x],v));
					if(x+1<=top[i][2])ans=max(ans,clac(s[i][2][x+1],v));
					if(x-1)ans=max(ans,clac(s[i][2][x-1],v));
				}
			}
		}
	}
	inline short main(){
		n=read();
		F(i,1,n)av[i]=read(),bv[i]=read(),bel[i]=(i-1)/B+1;
		F(i,1,bel[n])L[i]=R[i-1]+1,R[i]=min(n,i*B);
		static int sta1[N],top1,sta2[N],top2;
		F(i,1,n){
			nw=i;
			while(top1&&av[sta1[top1]]>=av[i])top1--;
			int l1=sta1[top1]+1;sta1[++top1]=i;
			while(top2&&bv[sta2[top2]]>=bv[i])top2--;
			int l2=sta2[top2]+1;sta2[++top2]=i;
			if(l1<l2)change1(l1,l2-1,1,av[i]);
			if(l2<l1)change1(l2,l1-1,2,bv[i]);
			change2(max(l1,l2),i,av[i],bv[i]);
			if(i==R[bel[i]])build(bel[i]);
			ask(1,i,i+1);
		}pf("%lld\n",ans);
		return 0;
	}
}
signed main(){return EMT::main();}

```

可能最近 Ynoi 做多了，导致一看到数据结构题就往根号上想...

有没有好哥哥能把复杂度里面的 $\log n$ 去掉啊！

---

## 作者：MatrixGroup (赞：1)

>凸包加线段树，码量越写越绷不住。
>
>线段树加凸包，常数遇水变大变高。

## 题意

给定长度均为 $n$ 的序列 $a$ 和 $b$，求 $\max\limits_{1\le l\le r\le n}(r-l+1)\cdot(\min\limits_{i=l}^ra_i)\cdot(\min\limits_{i=l}^rb_i)$。

$n\le2\times10^5$

## 题解

考虑分治。只需考虑 $l\in [L,M],r\in (M,R]$ 的答案。

对于每个 $i\in [L,M]$，预处理 $c_i=\min\limits_{j=i}^Ma_i,d_i=\min\limits_{j=i}^Mb_i$。对于每个 $i\in(M,R]$，预处理 $c_i=\min\limits_{j=M+1}^ia_i,d_i=\min\limits_{j=M+1}^ib_i$。那么问题转化为最大化 $\min(c_l,c_r)\min(d_l,d_r)(r-l+1)$。

由于对称性，不妨设 $c_l\le c_r$。分两种情况：

- $d_l\ge d_r$
- $d_l\le d_r$（注意 $d_l=d_r$ 时两种都计算没有问题）

在每种情况中，固定 $l/r$，符合要求的 $r/l$ 都是一个区间。

如果是 $c_l\le c_r,d_l\le d_r$，那么答案是 $c_ld_l(r-l+1)$，只需最大化 $r$ 即可。

如果 $c_l\le c_r,d_r\ge d_l$，那么答案是 $c_ld_r(r+1)-c_ld_rl$。

这是一个点积的形式。考虑用线段树维护 $(-c_ll,c_l)$ 的凸包，二分查询与 $(d_r,(r+1)d_r)$ 点积最大的即可。复杂度 $O(n\log^3n)$，无法通过。

注意到 $(d_r,(r+1)d_r)$ 斜率是单调的。因此最优决策点也是单调的。双指针维护即可。复杂度 $O(n\log^2n)$。

本题细节略多，可以参考[代码](https://loj.ac/s/1908340)。

---

## 作者：vectorwyx (赞：1)

这题似乎也很套路。实际上是求 $\max_{l\le r}\min a[l,r]\times\min b[l,r]\times(r-l+1)$ 。最开始想的是最值分治，但是最值分治的弊端在于为了保证复杂度只能扫更短的那一边，只要复杂度与更长的那一边的长度挂钩就寄飞了。而这题是致命的两个数组的 $\min$，最值分治只能限制一个数组，另一个数组的 $\min$ 的位置可以随心所欲，所以复杂度不太可能与更长的那一边脱钩。

最值分治大失败，我们去想最朴实的按中点分治，发现赢麻了。考虑 $a,b$ 的 $\min$ 分别在哪边取得，如果都在同一边那么另一边的长度是两个形如 $\le x,\le y$ 的限制，$x,y$ 都具有单调性，在 $a,b$ 的最小值均已确定后显然长度越大越优，拿双指针扫一遍就好。而如果是一左一右，不妨设 $a$ 的 $\min$ 在左边取得，$b$ 的 $\min$ 在右边取得。枚举左边的长度 $k$，不难看出右边的合法位置组成了一段区间 $[L,R]$。记 $A_i=\min a[M-i+1,M],B_i=\min b[M+1,M+i]$（$M$ 为分治中点的下标），当前长度 $k$ 的贡献即为 $\max_{i=L}^R A_kB_i(i+k)$，于是目标变为求 $\max_{i=L}^R B_ii+B_ik\iff \max_{i=L}^R (B_ii,B_i)\cdot(1,k)$。即一段区间内的所有函数的最值，可以用线段树套李超树维护，每一层的复杂度为 $O(n\log^2n)$，总复杂度 $O(n\log^3n)$。注意到 $k$ 是递增的，因此最优解在上凸壳上不断**向左移动**，用线段树维护上凸壳，每个线段树结点额外维护一个最优解指针就可以做到每层 $O(n\log n)$，总时间复杂度 $O(n\log^2n)$，空间复杂度 $O(n\log n)$。

代码如下（人傻常数大，不吸氧跑不过去/qd）：
```cpp
//author:望远星
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define mk make_pair
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define uint unsigned int
#define ull unsigned long long
#define umap unordered_map
#define db double
#define fo(i,x,y) for(int i=x;i<=y;++i)
#define go(i,x,y) for(int i=x;i>=y;--i)
#define ptc putchar
#define emp emplace
using namespace std;
ll seed=chrono::system_clock::now().time_since_epoch().count();
mt19937 rnd(seed);
inline int rm(int x,int y){return (int)(rnd()%(y-x+1ll)+x);}
inline int read(){int ch=getchar(),x=0,f=1;while(!isdigit(ch)){if(ch==(int)('-'))f=-1;ch=getchar();}while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void out(int *a,int l,int r){fo(i,l,r) cout<<*(a+i)<<' ';puts("");}

const int N=2e5+5,V=1e6+1;
int n,a[N],b[N],A[N],B[N];
ll ans;//nV^2

struct vec{
	ll x;//x:ai*i,bi*i,1 <=10^12
	int y;//y:ai,bi,k <=10^6
	vec(){x=0,y=0;}
	vec(ll X,int Y){x=X,y=Y;} 
}ve[N];
vec operator+(const vec &x,const vec &y){return vec(x.x+y.x,x.y+y.y);}
vec operator-(const vec &x,const vec &y){return vec(x.x-y.x,x.y-y.y);}
ll operator*(const vec &x,const vec &y){return x.x*y.x+(ll)x.y*y.y;} 
bool operator/(const vec &x,const vec &y){return x.x*y.y<=x.y*y.x;}
bool operator<(const vec &x,const vec &y){return x.x<y.x;} 

namespace Seg{
struct Node{
	vector<vec> ve,stk;
	ull top,id;//这里用 ull 应该不会出事吧QAQ 
	void play_it(){
		top=0;
		for(auto i:ve){
			while(top>1&&(stk[top]-stk[top-1])/(stk[top]-i)) top--;
			stk[++top]=i;
		}
		id=top;
		//printf("top=%d\n",top);
	}
	ll ask(int k){//询问 (1,k) 与 stk 中向量乘积的最大值，k 单增
		//printf("ask(%d) %llu,%llu\n",k,id,top);
		vec qwq=vec(1,k);
		//ll ret=0;
		//fo(i,1,top) big(ret,qwq*stk[i]);
		//for(auto i:ve) big(ret,qwq*i);
		//return ret;
		while(id>1&&stk[id-1]*qwq>=stk[id]*qwq) --id;
		return stk[id]*qwq; 
	}
}tr[N<<2];
#define ls(x) x<<1
#define rs(x) x<<1|1
void build(int x,int l,int r){
	//printf("build(%d,%d,%d)\n",x,l,r);
	tr[x].ve.clear();tr[x].ve.resize(r-l+1);
	tr[x].stk.resize(r-l+2);
	if(l==r){
		tr[x].ve[0]=ve[l];
		tr[x].play_it();
		return; 
	}
	int mid=(l+r)>>1;
	build(ls(x),l,mid);
	build(rs(x),mid+1,r);
	merge(tr[ls(x)].ve.begin(),tr[ls(x)].ve.end(),tr[rs(x)].ve.begin(),tr[rs(x)].ve.end(),tr[x].ve.begin());
	//cout<<x<<":";for(auto i:tr[x].ve) printf("(%lld,%d) ",i.x,i.y);puts("");
	tr[x].play_it();
}
ll ask(int x,int l,int r,int L,int R,int k){
	//printf("ask(%d,%d,%d,%d,%d,%d)\n",x,l,r,L,R,k);
	if(l>=L&&r<=R) return tr[x].ask(k);
	int mid=(l+r)>>1;
	if(R<=mid) return ask(ls(x),l,mid,L,R,k);
	if(L>mid) return ask(rs(x),mid+1,r,L,R,k);
	return max(ask(ls(x),l,mid,L,R,k),ask(rs(x),mid+1,r,L,R,k));
}
}
using namespace Seg;


void divi(int l,int r){
	//printf("divi(%d,%d)\n",l,r);
	if(l==r){
		big(ans,(r-l+1ll)*a[l]*b[l]);
		return;
	}
	int mid=(l+r)>>1,L=mid+1,R=mid,mna=V,mnb=V;
	//mina,minb 均在左边
	go(i,mid,l){
		sml(mna,a[i]),sml(mnb,b[i]);
		while(R<r&&a[R+1]>=mna&&b[R+1]>=mnb) ++R;
		big(ans,(R-i+1ll)*mna*mnb);
	}
	//mina,minb 均在右边
	mna=mnb=V;
	fo(i,mid+1,r){
		sml(mna,a[i]),sml(mnb,b[i]);
		while(L>l&&a[L-1]>=mna&&b[L-1]>=mnb) --L;
		big(ans,(i-L+1ll)*mna*mnb);
	}
	int Rlen=r-mid;
	//mna 在左边，mnb 在右边
	L=R=mid;mna=mnb=V;
	B[0]=V;fo(i,1,Rlen) B[i]=min(B[i-1],b[i+mid]),ve[i]=vec((ll)B[i]*i,B[i]);
	build(1,1,Rlen);
	go(i,mid,l){
		sml(mna,a[i]),sml(mnb,b[i]);
		while(L<=r&&B[L-mid]>mnb) ++L;
		while(R<r&&a[R+1]>mna) ++R;
		if(L>R) continue;
		big(ans,mna*ask(1,1,Rlen,L-mid,R-mid,mid-i+1));
	}
	//mnb 在左边，mna 在右边 
	L=R=mid;mna=mnb=V;
	A[0]=V;fo(i,1,Rlen) A[i]=min(A[i-1],a[i+mid]),ve[i]=vec((ll)A[i]*i,A[i]);
	build(1,1,Rlen);
	go(i,mid,l){
		sml(mna,a[i]),sml(mnb,b[i]);
		while(L<=r&&A[L-mid]>mna) ++L;
		while(R<r&&b[R+1]>mnb) ++R;
		if(L>R) continue;
		big(ans,mnb*ask(1,1,Rlen,L-mid,R-mid,mid-i+1));
	}
	divi(l,mid);
	divi(mid+1,r);
}

signed main(){
	cin>>n;//if(n>=100000) return 0;
	fo(i,1,n) a[i]=read(),b[i]=read();
	divi(1,n);
	//divi(1,3);
	//divi(1,4);
	cout<<ans;
	return 0;
}
/*
-------------------------------------------------
*/
```


---

## 作者：aleph_ (赞：0)

一个比较神奇的做法。

### 题目大意

求 $\max\{(r-l+1)(\min_{k=l}^r a_k)(\min_{k=l}^r b_k)\}$。

### 思路

首先不难想到 $O(n^2)$ 的做法：枚举两个端点 $l$，$r$，ST表维护区间最小值即可。

考虑优化，设当前搜出的两个区间最小值的乘积为 $\text{prod}$，那么固定左端点，若想答案更优，区间长度至少是 $\lfloor\frac{\text{ans}}{\text{prod}}\rfloor$ 才行（因为固定左端点的话，右端点往右只会使区间最小值变小）。所以我们可以把右端点跳到 $\lfloor\frac{\text{ans}}{\text{prod}}\rfloor+l-1$ 的位置，继续搜就可以了。

再乱搞一下，随机左端点枚举顺序，轻松卡过。

### Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=200005;
int n,prod,a[N],b[N],lg[N],f1[N][25],f2[N][25];
void st(){
    for(int j=1;j<=20;j++){
        for(int i=1;i<=n;i++){
            if(i+(1<<(j-1))>n) break;
            f1[i][j]=min(f1[i][j-1],f1[i+(1<<(j-1))][j-1]);
            f2[i][j]=min(f2[i][j-1],f2[i+(1<<(j-1))][j-1]);
        }
    }
}
int query1(int l,int r){
    int k=lg[r-l+1];
    return min(f1[l][k],f1[r-(1ll<<k)+1][k]);
}
int query2(int l,int r){
    int k=lg[r-l+1];
    return min(f2[l][k],f2[r-(1ll<<k)+1][k]);
}
vector<int> tmp;
signed main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    memset(f1,0x3f,sizeof(f1));
    memset(f2,0x3f,sizeof(f2));
    cin>>n;
    lg[0]=-1;
    for(int i=1;i<=n;i++){
        lg[i]=lg[i>>1]+1;
        cin>>a[i]>>b[i];
        f1[i][0]=a[i];
        f2[i][0]=b[i];
        tmp.push_back(i);
    }
    st();
    int ans=0;
    for(int l:tmp){
        for(int r=l;r<=n;r++){
            prod=query1(l,r)*query2(l,r);
            ans=max(ans,prod*(r-l+1));
            r=ans/prod+l-1;
        }
    }
    cout<<ans<<endl;
}
```

---

