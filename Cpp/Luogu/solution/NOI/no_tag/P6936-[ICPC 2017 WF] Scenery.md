# [ICPC 2017 WF] Scenery

## 题目描述

![](https://cdn.luogu.com.cn/upload/image_hosting/jnez9lpt.png)

图片由 John Fowler、Carol Highsmith 和 Richard Woodland 提供。

你决定在前往拉皮德城的旅行中花一天时间拍摄南达科他州的荒地，这里因其壮观而独特的地貌而闻名。你是一位业余摄影师，但对光照条件非常讲究。

经过仔细研究，你找到了一个美丽的拍摄地点，周围是如画的风景。你确定了希望从这个地点拍摄的各种景观特征。对于每个特征，你都确定了太阳位置理想的最早和最晚时间。然而，由于需要重新定位三脚架和相机以及你的完美主义，拍摄每张照片都需要相当长的时间。因此，你想知道是否有可能在一天内成功拍摄所有这些特征。

## 说明/提示

时间限制：6 秒，内存限制：512 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
2 10
0 15
5 20
```

### 输出

```
yes
```

## 样例 #2

### 输入

```
2 10
1 15
0 20
```

### 输出

```
no
```

## 样例 #3

### 输入

```
2 10
5 30
10 20
```

### 输出

```
yes
```

# 题解

## 作者：极寒神冰 (赞：13)

~~一个想法，不知道对不对，就是这个翻译有些细小的偏差~~

令每张照片的可以拍摄开区间为 $Q_i=(a_i,b_i)$，实际拍摄的开区间 $P_i=(x_i,x_i+t)$，需要有 $P_i\subseteq Q_i$，且 $P_i$ 两两不交。

首先可以想到各种~~一眼就是错的~~贪心。

假设现在有 $t=3,Q_1=(0,7),Q_2=(1,4)$。

然后现在从左往右扫，考虑怎么求出 $P_1$。

假如直接贪心把 $(0,3)$ 填上，那么此时 $(1,3)$ 就被覆盖，$P_2$ 无解。

因此，由于问题也只是求是否有解且 $t$ 固定，$Q_2$ 成立也就当且仅当不存在一个 $P_i$ 的左端点在 $(-2,1)$ 中。称这个为 $Q_2$ 禁止区间。

一般化的，对于一个指标集 $S=\{i_1,i_2,\cdots,i_k\}$，设一组合法的方案的区间簇为 $\{P_{i_j}\},i\le j \le k$。其左端点 $\inf(\cup P_i)=N$，左端点 $\inf(\cup Q_i)=M$。则 $S$ 的禁止区间 $F_S=(N-t,M)$。

可以发现，如果存在一组合法方案 $P$，则所有区间的左端点 $a_i=\inf P_i$ 不属于任意一个禁止区间。

然后继续考虑贪心：记所有禁止区间的并集为 $F_x$，从左往右扫，扫的时候跳过 $F_x$ 中的所有点。如果找到某个 $a\ge\inf Q_i$，找到未匹配区间中 $\sup Q_i$ 最小的。然后 $P_i=(a,a+t)$，然后继续从 $a+t$ 开始扫。这样一定可以构造出一组合法的解。

证明可以考虑归纳。。

但是这样子禁止区间高达 $2^n$ 种，考虑减少所需要的禁止区间数量。

令 $S=\{i_1,i_2,\cdots,i_k\}$，$\inf(\cup Q_i)=L,\sup (\cup Q_i)=R$。

如果存在 $x\not\in S$ 满足 $\inf Q_x\ge L$。将 $x$ 加入 $S$ 后，由于需要的区间多了一个 $P_x\subseteq (L,+\infty)$，所以 $\inf ((\cup P_i)\cup P_x)\le \inf(\cup P_i)=N$，$F_S\subseteq F_{S\cup \{x\}}$。

所以事实上 $F_S$ 对禁止区间的并集没有任何贡献，所需要考虑的禁止区间只有 $\mathcal O(n)$ 个：即对于每一个 $a_i$，所有左端点 $\ge a_i$ 的区间构成的集合的禁止区间。（下面的 $F_i$ 表示用上面这句定义的禁止区间）。

考虑按照左端点排序，假设 $a_i<a_{i+1}$。

依次对 $i=n,n-1,\cdots,2,1$ 计算 $F$。

根据前面从左往右的贪心，此时从右往左同样也是对的，答案就是最大的左端点 $N$。

但是这样会出现当前位置不在禁止区间内，但是也没有区间可以匹配。此时可以将这整个问题分成两个更小的子问题，如果出现不可分割的子问题，可以发现一定不存在这种情况。

因此考虑对每一对 $(i,R)$ 维护出只考虑左端点 $\ge a_i$，右端点 $\le R$ 的区间，只考虑不经过禁止区间，不考虑是否有区间匹配，匹配完之后终点数量。

因此

$$
\inf F_i=\min \left(a_i,\min\limits_{a_i\le R} (dp_{i,R}-t) \right)
$$

然后考虑从 $(i+1,R)$ 转移到 $(i,R)$，因为 $F_i$ 的右端点 $a_i$ 随着 $i$ 递减而递减，因此可以通过双指针跳过禁止区间。

具体，先令 $dp_{i,R}=dp_{i+1,R-t}$，然后由于禁止区间控制的是左端点，因此依次用双指针检验每个 $i$，若当前 $x<a_i$，则对 $\inf F_i$ 取 $\min$ 即可。

判断无解时，就是看 $f_{i,R}$ 是否 $\ge a_i$。

时间复杂度 $\mathcal O(n^2)$

```cpp
#include<bits/stdc++.h>
#define R(i,a,b) for(int i=(a),i##E=(b);i<=i##E;i++)
#define L(i,a,b) for(int i=(b),i##E=(a);i>=i##E;i--)
using namespace std;
int n,t;
pair<int,int>a[11111];
int rr[11111],to[11111],now[11111];
int dp[11111];
inline int ckmin(int &x,const int y)
{
	return x>y?x=y,1:0;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin>>n>>t;
	R(i,1,n)
	{
		cin>>a[i].first>>a[i].second;
		rr[i]=a[i].second;
	}
	R(i,1,n) now[i]=n;
	sort(a+1,a+n+1),sort(rr+1,rr+n+1);
	R(i,1,n) dp[i]=rr[i],to[i]=1<<30;
	L(i,1,n) 
	{
		int r=n;
		for(;rr[r]>=a[i].second;--r)
		{
			dp[r]-=t;
			for(;i<now[r]&&dp[r]<a[now[r]].first;--now[r]) ckmin(dp[r],to[now[r]]);
			if(dp[r]<a[i].first) return cout<<"no"<<endl,0;
			ckmin(to[i],dp[r]-t);
		}
	}
	cout<<"yes"<<endl;
}
```

---

## 作者：zhouhuanyi (赞：3)

提供一个 $O(n^2\alpha(n))$ 的做法。

这种匹配问题如果直接寻找最优的匹配方式是困难的，因为 $\geqslant k$ 的限制，当前匹配的点会对之后的产生不小的影响。但是如果我们 $\text{fix}$ 好了一个选择的升序位置序列 $a$，想要判定其是否合法是容易的，需要以下两个条件：

$1.$ 对于 $i\in [1,n-1]\cap Z$，$a_{i+1}-a_{i}\geqslant k$。

$2.$ 对于一个区间的子集 $S$，其并集 $N(S)$ 中 $a$ 的元素个数要大于等于 $|S|$，而我们仅需 $\text{check}$ 并集为一个区间的就合法，所以可以得到 $O(n^2)$ 个区间有关的约束。

实际上可以发现现在只有对前缀和的约束了($1$ 相当于限制 $s_{i}-s_{i-k}\leqslant 1$)，但由于值域比较大，需要离散化，此时相当于 $s_{y}-s_{x}\leqslant \lceil\frac{y-x}{k}\rceil$。

直接跑最短路肯定不行，但是我们连出的边其实很有性质，可以对 $\text{Bellman ford}$ 算法进行优化，关键在于优化 $\geqslant k$ 与 $\text{Hall}$ 定理得到的若干个区间约束的部分：

$1.$ $\geqslant k$ 的 $\lceil\frac{y-x}{k}\rceil$ 可以写为 $\lfloor\frac{y}{k}\rfloor-\lfloor\frac{x}{k}\rfloor+[y\mod k> x\mod k]$，此时由于后面的式子至多贡献 $1$，保留 $dp_{x}-\lfloor\frac{x}{k}\rfloor$ 最小其次 $x\mod k$ 最大的状态一定最优。

$2.$ $s_{y}-s_{x}\geqslant [x,y]$ 内的区间个数，这个倒序扫描后实际上就是后缀 $-1$，在前面添加元素，与查询全局最小值，这个是反向决策单调性，后面的元素比前面优了就一直会比前面优，此时可以用并查集合并两个元素，在并查集上的每一个元素存下单调栈的差分数组，每次修改时使对应并查集的差分数组 $-1$，如果一个位置的差分数组 $<0$，则可以将前面的一个元素合并到后面。

复杂度 $O(n^2\alpha (n))$，由于并查集常数较大，需要加一些减枝才能通过。

---

## 作者：jiazhichen844 (赞：1)

[链接](https://www.luogu.com.cn/problem/P6936)

我们记 $[a,b]$ 为数轴上从 $a$ 走到 $b$ 的闭区间，同理定义 $(a,b)$ 为从 $a$ 到 $b$ 的开区间，特殊的，若 $a>b$，$[a,b],(a,b)$ 都为空。

诶不是，这是不是直接贪贪就绷住了……诶不对，怎么贪啊？

一种想法是：我们设当前还未拍的照片对应的区间是 $[a_i,b_i]$，选择 $b_i$ 最小的区间，去拍 $[a_i,a_i+t]$，显然这是错误的。

这个问题最早在 1981 年被 Garey，Johnson，Simons 和 Tarjan 解决并证明，以下是他们给出的做法。

考虑一件事情，若存在区间 $[a_i,b_i]$，则 $[a_i,b_i-t]$ 中间要开始拍，若存在一张照片在 $(b_i-2t,a_i)$ 间开始拍，一定会在 $b_i-t$ 刻之后结束，整个 $[a_i,b_i-t]$ 区间都被使用，无法开始拍摄，所以 $(b_i-2t,a_i)$ 区间中禁止 **开始** 拍摄。

像 $(b_i-2t,a_i)$ 这样的区间被称为禁止区间，禁止区间中不能开始拍摄，但可以有一张照片从之前开始拍，一直拍到区间内部。

但是，考虑两个照片的区间 $[a_x,b_x],[a_y,b_y](a_x<a_y)$，其中 $[a_y,b_y]$ 已经产生一个禁止区间 $(b_y-2t,a_y)$，假设这两个区间最晚的开始拍摄（任意一张照片开始拍摄都视为开始拍摄，且开拍时间无法在已知的禁止区间内）时间为 $k$，则同理，$(t-k,a_x)$ 之间也无法开始拍摄（否则会影响这两张照片），这个区间也是禁止区间。

容易发现，任意一个照片的集合 $S$ 都会产生一个禁止区间 $(l_S,\min\limits_{i\in S}a_i)$，这样看来，禁止区间似乎是 $2^n$ 个的？

我们考察禁止区间间的包含关系，发现本质不同的右端点只有 $n$ 个，于是本质上只有 $O(n)$ 个禁止区间。

我们从大往小枚举 $a_i$，维护 $l_i$ 为以 $a_i$ 为右端点的禁止区间的左端点，同时维护 $st_i$ 为若只考虑 **从右到左数** 第 $i$ 个右端点以前的照片区间，拍完已枚举过的照片的最晚开始拍摄时间。

如何维护此信息？$l_i$ 就每次取 $\min$ 即可，$st_i$ 较复杂，因为可能会因为方案在禁止区间内开始而出问题，所以我们做双指针，维护 $p_i$ 为当前处理到了哪个禁止区间，这个是不难的。

如果扫每个 $a_i$ 时都不存在 $st_j<a_i$ 即一定合法（相当于我们已经构造出方案），否则无解（已矛盾，为何无其他解我不会证）。

挂一下原题解：[solution](https://www.csc.kth.se/~austrin/icpc/finals2017solutions.pdf)。

时间复杂度 $O(n^2)$，在于枚举 $i$ 时维护的 $st$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,t;
struct node
{
    int l,r;
    bool operator < (const node a) const
    {
        if(l==a.l)
            return r<a.r;
        return l<a.l;
    }
}a[10005];
int r[10005],l[10005],st[10005],p[10005];
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>t;
    for(int i=1;i<=n;i++)
        cin>>a[i].l>>a[i].r,r[i]=a[i].r;
    sort(r+1,r+n+1,greater<int>()),sort(a+1,a+n+1);
    for(int i=1;i<=n;i++)
        l[i]=a[i].l,st[i]=r[i],p[i]=n;
    for(int i=n;i>=1;i--)
    {
        for(int j=1;j<=n;j++)
        {
            if(r[j]>=a[i].r)
            {
                st[j]-=t;
                while(p[j]>i&&st[j]<a[p[j]].l)
                {
                    st[j]=min(st[j],l[p[j]]);
                    p[j]--;
                }
                if(st[j]<a[i].l)
                {
                    cout<<"no\n";
                    return 0;
                }
                l[i]=min(l[i],st[j]-t);
            }
        }
    }
    cout<<"yes\n";
}
```

---

## 作者：封禁用户 (赞：0)

这是一道论文题 qaq，还是比较推荐直接去读题解的原文，毕竟感觉我写的没有解释清楚。

首先考虑一种 naive 的贪心，每次在当前能照的相片中选一个结束时间最早的照他会在什么情况下错：存在一个相片在这个时候还不能照，但等这张照片照完后这个相片已经过了他的结束时间把这个错的情况拓展到更一般的情况，就是存在一组相片，我们如果要成功照完他们全部，最迟要在 $C$ 时刻开始处理这些相片，最早能在 $s$ 时刻处理这些相片，照一张相片耗时 $T$，那么我们不能在 $(C−T,s)$ 这个时间段内处理任何一张相片，否则这组相片一定不能在 $C$ 时刻前得到处理，则一定会有相片拍不成。

我们记这些  $(C−T,s)$ 区间为 forbidden 区间，就是不能拍摄的时间段，那么只要我们处理出所有这样的时间段，在考虑这些时间段内不拍摄的情况下去执行原来那个 naive 的贪心，就能保证贪心的结果是最优的。

复杂度 $O(n^2)$。

```cpp
#include<set>
#include<map>
#include<deque>
#include<queue>
#include<stack>
#include<cmath>
#include<ctime>
#include<bitset>
#include<string>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<climits>
#include<complex>
#include<iostream>
#include<algorithm>
#define ll long long
using namespace std;

inline void down(int &a,const int &b){if(a>b)a=b;}
const int maxn = 10010;

int n,T;
struct node
{
    int l,r;
    friend inline bool operator <(const node x,const node y){return x.l==y.l?x.r<y.r:x.l<y.l;}
}a[maxn];
int L[maxn],ln,R[maxn],rn;
int pre[maxn],fb[maxn],nowl[maxn];

void NIE(){ puts("no"); exit(0); }

int main()
{
    scanf("%d%d",&n,&T);
    for(int i=1;i<=n;i++)
    {
        int l,r; scanf("%d%d",&l,&r); r-=T;
        L[i]=l,R[i]=r;
        a[i].l=l,a[i].r=r;
    }
    sort(L+1,L+n+1);
    for(int i=1;i<=n;i++) if(i==1||L[i]!=L[i-1]) L[++ln]=L[i];
    sort(R+1,R+n+1);
    for(int i=1;i<=n;i++) if(i==1||R[i]!=R[i-1]) R[++rn]=R[i];

    for(int i=1;i<=ln;i++) fb[i]=L[i];
    for(int i=1;i<=rn;i++) pre[i]=R[i]+T,nowl[i]=ln;
    sort(a+1,a+n+1); int il=ln;
    for(int i=n;i>=1;i--)
    {
        int ni=i-1;for(;ni>=1&&a[ni].l==a[i].l;ni--);ni++;
        int nowj=i;
        for(int j=rn;j>=1&&R[j]>=a[i].l;j--)
        {
            while(nowj>=ni&&a[nowj].r>R[j]) nowj--; 
            if(nowj<ni) break;
            int c=nowj-ni+1;

            int &k=pre[j],&ki=nowl[j];
            while(c)
            {
                c--,k-=T;
                while(k>=a[i].l)
                {
                    while(L[ki-1]>k&&fb[ki]>=k) ki--;
                    if(k<L[ki]&&k>fb[ki]) k=fb[ki];
                    else break;
                }
                if(k<a[i].l) NIE();
            }
            down(fb[il],k-T);
        }
        i=ni; il--;
    }
    puts("yes");

    return 0;
}
```

---

