# 「SFMOI Round I」Strange Dino Game

## 题目背景

[English statement](https://www.luogu.com.cn/problem/T517979). **You must submit your code at the Chinese version of the statement.**


![](https://cdn.luogu.com.cn/upload/image_hosting/59joca92.png?x-oss-process=image/resize,m_lfit,h_600)

![](https://cdn.luogu.com.cn/upload/image_hosting/iyhol5l6.png?x-oss-process=image/resize,m_lfit,h_600)

Watersphere 同学在家没网了，只好玩起了 dino 游戏，但是他很菜，一玩到后面就头晕眼花，所以想让你编个程序帮助他拿到更高分，于是有了这题。

本题的游戏背景是 [Dino](https://dinosaur.game)。可以考虑点击链接游玩，以便更好理解题意。

## 题目描述


我们将问题放在二维平面上描述。我们给出一些游戏要素：

- 玩家：Dino。可以将其视为一个点。
- 障碍物：
    - 仙人掌：形如 $(x_i',0),(x_i',h_i)$ 的线段。
    - 飞鸟：形如 $(x_i,d_i),(x_i,u_i)$ 的线段。
- 游戏结束：Dino 与障碍物上的任意一点（包括线段端点）重合时，游戏结束。
- 起点：原点 $(0,0)$。
- 终点：使游戏结束的位置，位于第一象限（或 $x$ 轴上）。可能不存在（即游戏能无限进行）。
- 游戏分数：终点的 $x$ 坐标。终点不存在时定义为无穷大。
- 跳跃参数：正整数 $d,h$。
- 步行：Dino 在 $x$ 轴上沿着 $x$ 轴正方向移动。
- 跳跃：当 Dino 在 $x$ 轴上时，可以进行一次跳跃。以起跳点为原点，跳跃轨迹为
    $$f(x) = \begin{cases}
    \displaystyle  \frac{h}{d}x & x\in [0, d)  \\
    \displaystyle-\frac{h}{d}x+2h  & x\in [d, 2d)  \\
    \end{cases}$$
    - 需要注意的是，由上述定义可以推出：**在一次跳跃后落地的瞬间进行第二次跳跃是合法的。**
    - 需要注意的是，可以在任意**实数点**（只要在 $x$ 轴上）处开始跳跃。也就是说，跳跃不一定在整点开始。
    
下图展示了 $d=2,h=6$ 时的一次跳跃。

![](https://cdn.luogu.com.cn/upload/image_hosting/1gxrno9x.png?x-oss-process=image/resize,m_lfit,h_400)

在一局游戏中，Dino 从起点出发向 $x$ 轴正方向移动。目标是最大化得分，即尽量避开障碍物，使自己移动的距离尽量长。

每一时刻，Dino 只能做一件事：步行，或跳跃。当且仅当 Dino 在 $x$ 轴上时可以进行跳跃。

形式化地说，Dino 的行为可以被描述为一个长度为 $(k+1)$ 的实数二元组序列 $[(x_0,t_0),(x_1,t_1),\cdots,(x_k,t_k)]$，满足：

- $x_0=0$；
- $t_i\in \{0,1\}$；
- $\forall 0\le i\lt k$, $x_i\lt x_{i+1}$；
- $t_i=1,i\lt k\implies x_{i+1}-x_i\ge 2d$；(二段跳是不允许的)
- $\forall 0\le i\lt k$, $t_i=t_{i+1}\implies t_i=t_{i+1}=1$。

当 $t_i=0$ 时，我们定义 Dino 在 $x_i$ **进入步行状态**，否则定义 Dino 在 $x_i$ **进入跳跃状态**。

当 Dino 与障碍物重合时，游戏结束。此时 Dino 在的位置为终点，得分为终点的 $x$ 坐标。

已知有 $b$ 只飞鸟和 $c$ 个仙人掌，求出 Dino 的最大得分。特别地，得分可以为无穷大。

可参阅样例解释的图片。

## 说明/提示


样例 $1$ 解释：  

- 对于第 $1$ 组数据，dino 无论如何也无法跳过连续的两株高为 $2$ 的仙人掌，答案即为第二株仙人掌的 $x$ 轴坐标。
- 对于第 $2$ 组数据，dino 可以在原点直接起跳跳过唯一的一只鸟，也完全可以不起跳从飞鸟下方走过。

其中第一组数据的解释如下所示，红线代表飞鸟，绿线代表仙人掌，粉线代表 Dino 的轨迹。

![](https://cdn.luogu.com.cn/upload/image_hosting/ge17so5a.png?x-oss-process=image/resize,m_lfit,h_400)

### 数据范围

**本题采用捆绑测试。**

- Subtask 1（5 pts）：$c=0$；
- Subtask 2（5 pts）：$b,c \le 10$；
- Subtask 3（20 pts）：$b=0$；
- Subtask 4（20 pts）：$1 \le d,h,x_{b_i},d_i,u_i,x_i',h_i \le 10^5$;
- Subtask 5（40 pts）：无特殊限制。
- Subtask 6（10 pts）：无特殊限制。

对于 $100\%$ 的数据，保证：
- $1 \le T \le 10$；
- $0 \le b,c \le 2\times 10^4$；
- $1 \le d,h,x_{b_i},d_i,u_i,x_i',h_i\le 10^9$；
- $d_i\le u_i$。

## 样例 #1

### 输入

```
2
1 3
1 2
1 2 1
2 2
3 2
1000000000 1000000000
1 0
114514 1919 810```

### 输出

```
3
Dino!```

## 样例 #2

### 输入

```
1
8 16
8 3
5 18 13
4 20 10
6 13 1
2 17 11
1 11 6
5 1 1
2 6 3
1 16 1
7 20
7 13
3 2```

### 输出

```
6```

## 样例 #3

### 输入

```
1
5 5
1 2
5 5 1
6 1
16 3```

### 输出

```
16```

## 样例 #4

### 输入

```
1
5 5
1 4
19 10 8
4 1
15 1
22 2
20 1```

### 输出

```
22```

# 题解

## 作者：Nineyx (赞：12)

首先可以二分答案，这样就只要判定能否避开所有障碍。

dino 每次跳跃一定至少跨过一个仙人掌，否则可以不跳。仙人掌把整个数轴分成若干段，考虑从右往左 dp，$dp[i]$ 表示若 dino 从第 $i$ 段左端点出发，能使 dino 避开后面所有障碍的最靠右的起跳点。

考虑如何转移。所有障碍都对 dino 的起跳点作出了限制，即对于每个障碍，dino 不能在某一个或两个闭区间内起跳。取这些区间并集的补集就得到 dino 可以起跳的区间集合。从右往左枚举每一个可起跳的开区间 $(l,r)$，$(l,r)$ 和 $(l+2d,r+2d)$ 分别属于同一个被仙人掌划分成的段内，设这两段编号分别为 $i,j (i<j)$。若 $j$ 是最后一段（即后面没有仙人掌），则 $dp[i] \gets \max(dp[i],r)$；否则若 $l+2d < dp[j]$，则 $dp[i] \gets \max(dp[i],\min(r,dp[j]-2d))$。最后看 $dp[1]$ 是否 $> 0 $ 即可（注意由于可起跳的区间是开区间，这里的 dp 值均不能取到，因此必须 $>0$ 才合法，同理前面 $l+2d$ 必须小于 $dp[j]$）。

实现上为了避免浮点数的精度问题，可以把所有障碍物的横坐标和跳跃参数 $d$ 乘上 $h$，这样限制区间和可起跳区间的端点均为整数。

设 $n=b+c$，根据具体实现，总时间复杂度为 $O(Tn\log^2n)$ 或 $O(Tn\log n)$。

以下代码时间复杂度为 $O(Tn\log^2n)$。

```cpp
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int maxn=2e4+5;
struct B{
	ll x,l,r;
}bs[maxn];
struct C{
	ll x,h;
}tc[maxn],cs[maxn];
struct L{
	ll l,r;
}li[maxn*4],la[maxn*4];
int rc,pc,cl,ca;
ll f,h,b,c,mr[maxn];
bool cmpc(C x,C y){return x.x<y.x;}
bool cmpl(L x,L y){return x.l<y.l;}
void init(){
	rc=0;
}
void initc(ll x){
	cl=pc=ca=0;
	while(pc<rc&&cs[pc+1].x<x) pc++;
}
void qd(ll x,ll l,ll r)
{
	if(l>h) return;
	ll dr=x-l*f,dl=x+l*f-f*h*2,ur=x-r*f,ul=x+r*f-f*h*2;
	if(h<=r) li[++cl]=(L){dl,dr};
	else li[++cl]=(L){dl,ul},li[++cl]=(L){ur,dr};
}
int fd(ll x){
	int l=1,r=rc,re=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(cs[mid].x<=x) re=mid,l=mid+1;
		else r=mid-1;
	}
	return re+1;
}
bool ck(ll x)
{
	initc(x);
	for (int i=1;i<=pc;i++) qd(cs[i].x,0,cs[i].h),mr[i]=-1;
	for (int i=1;i<=b;i++) if(bs[i].x<x) qd(bs[i].x,bs[i].l,bs[i].r);
	sort(li+1,li+cl+1,cmpl);
	ll pr=0;
	for (int i=1;i<=cl;i++)
	{
		if(li[i].l>pr) la[++ca]=(L){pr,li[i].l};
		pr=max(pr,li[i].r);
	}
	mr[pc+1]=3e18;
	for (int i=ca;i;i--)
	{
		ll px=fd(la[i].l),nx=min(pc+1,fd(la[i].l+f*h*2));
		if(px==nx) continue;
		if(nx==pc+1) mr[px]=max(mr[px],la[i].r);
		else if(la[i].l+f*h*2<mr[nx]) mr[px]=max(mr[px],min(la[i].r,mr[nx]-f*h*2));
	}
	return mr[1]>0;
}
void solve()
{
	cin>>f>>h>>b>>c;init();
	for (int i=1;i<=b;i++) cin>>bs[i].x>>bs[i].r>>bs[i].l,bs[i].x*=h;
	for (int i=1;i<=c;i++) cin>>tc[i].x>>tc[i].h,tc[i].x*=h;
	sort(tc+1,tc+c+1,cmpc);
	for (int i=1;i<=c;i++)
		if(tc[i].x!=tc[i-1].x) cs[++rc]=(C){tc[i].x,tc[i].h};
		else cs[rc].h=max(cs[rc].h,tc[i].h);
	ll l=2,r=1e9+1,re=1;
	while(l<=r){
		ll mid=(l+r)>>1;
		if(ck(mid*h)) re=mid,l=mid+1;
		else r=mid-1;
	}
	if(re==1e9+1) cout<<"Dino!"<<endl;
	else cout<<re<<endl;
}
int main()
{
	int t;cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：Y_zhao111 (赞：8)

### Description

题目传送门：[P11147 「SFMOI Round I」Strange Dino Game](/problem/P11147)。

一道很好的模拟题，~~建议做完后去做猪国杀~~。

题目中给定了 Dino 游戏的地图，分别有两种障碍物：

+ $b$ 只飞鸟。
+ $c$ 株仙人掌。

**注意它们都是垂直于 $x$ 轴的线段，且都位于第一象限或 $x$ 轴上**。

我们可以操纵 Dino **跳跃**（当 Dino 在 $x$ 轴上）或者（沿着 $x$ 轴）**步行**。

尽量避开障碍物，**跳跃形如两段一次函数**。

将 Dino 视为一个点，当 Dino 与障碍重合时游戏结束，得分为此时 Dino 位置的 $x$ 坐标，求出 Dino 得分的最大值。

最大值可以为正无穷（`Dino!`）。

**注意线段可能退化成一个点。**

### Analysis

先找到可以起跳的区间。
> 
>将每一株仙人掌确定一个**保证不能起跳**的闭区间。
>
>令闭区间为 $\left[s_i,t_i\right]$，对于飞鸟，区间的数量可能在 $0\sim2$ 之间。
>
>对这些区间的**并集取补集**，就能得到可以起跳的区间。

给出结论：我们应当**让 Dino 在跳过仙人掌后尽量早地落地**，这样就可以做出更多的决策，显然这种方案是更优的。

按照上面的结论模拟即可，时间复杂度在 $\mathcal{O}{(n \log n)}$。

具体的来讲这个结论：

+ 我们将不能起跳的区间端点加入起跳决策点集合中，模拟起跳过程。
+ 在**落地点未被不能起跳区间覆盖**的情况下，起跳后若能成功落地，则将落地点加入起跳决策点集合中。

在模拟跳跃的过程中判断是否与障碍物相撞即可。

----

总的时间复杂度是 $\mathcal{O}{(n \log n)}$ 或者 $\mathcal{O}{(n \log^2 n)}$。

时限 $3s$，应该大概也许左右不用卡常（反正我没卡）。

特别注意一点，最后 $10$ 分特别恶心，卡精度，别用 `double`。

### Code

只给出主函数部分。


```cpp
int main()
{
    long long i, j, sum, t1, t2, _1, _2, T;
    scanf("%lld", &T);

    while (T--)
    {
        scanf("%lld %lld", &f, &h);
        scanf("%lld %lld", &n, &m);

        cnt = 0;
        for (i = 1; i <= n; ++i)
        {
            scanf("%lld %lld %lld", &b[i].x, &b[i].hr, &b[i].hl);

            if (b[i].hl > h)
                continue;

            b[i].hr = min(h, b[i].hr);

            s[++cnt] = func1(b[i].hl, b[i].x), s[++cnt] = func2(b[i].hl, b[i].x),
            s[++cnt] = func1(b[i].hr, b[i].x), s[++cnt] = func2(b[i].hr, b[i].x);
        }

        for (i = 1; i <= m; ++i)
        {
            scanf("%lld %lld", &c[i].x, &c[i].hr);
            c[i].hl = 0, c[i].hr = min(c[i].hr, h);

            s[++cnt] = func1(c[i].hl, c[i].x), s[++cnt] = func2(c[i].hl, c[i].x),
            s[++cnt] = func1(c[i].hr, c[i].x), s[++cnt] = func2(c[i].hr, c[i].x),
            s[++cnt] = (c[i].x * h) * 2ll;

            d[i] = (c[i].x * h) * 2ll;
        }

        sort(s + 1, s + cnt + 1);
        cnt = unique(s + 1, s + cnt + 1) - (s + 1);

        for (i = 1; i <= n; ++ i)
        {
            if (b[i].hl > h)
                continue;

            t1 = func1(b[i].hl, b[i].x), t2 = func1(b[i].hr, b[i].x);
            _1 = lower_bound(s + 1, s + cnt + 1, t1) - s;
            _2 = lower_bound(s + 1, s + cnt + 1, t2) - s;

            if (_1 > _2)
                swap(_1, _2);

            arr1[_1].push_back(b[i].x);
            arr2[_2].push_back(b[i].x);

            t1 = func2(b[i].hl, b[i].x), t2 = func2(b[i].hr, b[i].x);

            _1 = lower_bound(s + 1, s + cnt + 1, t1) - s;
            _2 = lower_bound(s + 1, s + cnt + 1, t2) - s;

            if (_1 > _2)
                swap(_1, _2);

            arr1[_1].push_back(b[i].x);
            arr2[_2].push_back(b[i].x);
        }

        for (i = 1; i <= m; ++i)
        {
            t1 = func1(c[i].hl, c[i].x), t2 = func1(c[i].hr, c[i].x);

            _1 = lower_bound(s + 1, s + cnt + 1, t1) - s;
            _2 = lower_bound(s + 1, s + cnt + 1, t2) - s;

            if (_1 > _2)
                swap(_1, _2);

            arr1[_1].push_back(c[i].x);
            arr2[_2].push_back(c[i].x);

            t1 = func2(c[i].hl, c[i].x), t2 = func2(c[i].hr, c[i].x);

            _1 = lower_bound(s + 1, s + cnt + 1, t1) - s;
            _2 = lower_bound(s + 1, s + cnt + 1, t2) - s;

            if (_1 > _2)
                swap(_1, _2);

            arr1[_1].push_back(c[i].x);
            arr2[_2].push_back(c[i].x);

            _1 = lower_bound(s + 1, s + cnt + 1, 2ll * c[i].x * h) - s;
            flag[_1] = 1;
        }

        sort(d + 1, d + m + 1);
        m = unique(d + 1, d + m + 1) - (d + 1);

        ans = sum = 0, vis[1] = minl[1] = 1, j = 1;

        for (i = 1; i <= m; ++i)
        {
            if (vis[i])
            {
                while (s[j] <= minl[i] && j <= cnt)
                {
                    for (auto t : arr1[j])
                    {
                        st.insert(t);
                        ++sum;
                    }

                    for (auto t : arr2[j])
                    {
                        it = st.find(t);
                        st.erase(it);
                        --sum;
                    }
                    ++j;
                }

                if (!sum)
                {
                    _1 = upper_bound(d + 1, d + m + 1, minl[i] + 4ll * f * h) - d;
                    if (!vis[_1])
                        vis[_1] = 1, minl[_1] = minl[i] + 4ll * f * h;
                }

                else
                {
                    it = st.begin();
                    ans = max(ans, (*it));
                }

                while ((!flag[j]) && j <= cnt)
                {
                    for (auto t : arr1[j])
                    {
                        st.insert(t);
                        ++sum;
                    }

                    for (auto t : arr2[j])
                    {
                        it = st.find(t);
                        st.erase(it);
                        --sum;
                    }

                    if (!sum)
                    {
                        _1 = upper_bound(d + 1, d + m + 1, s[j] + 1ll + 4ll * f * h) - d;
                        if (!vis[_1])
                            vis[_1] = 1, minl[_1] = s[j] + 1ll + 4ll * f * h;
                    }

                    else
                    {
                        it = st.begin();
                        ans = max(ans, (*it));
                    }

                    ++j;
                }

                for (auto t : arr1[j])
                {
                    st.insert(t);
                    ++sum;
                }

                for (auto t : arr2[j])
                {
                    it = st.find(t);
                    st.erase(it);
                    --sum;
                }
                ++j;
            }

            else
            {
                while ((!flag[j]) && j <= cnt)
                {
                    for (auto t : arr1[j])
                    {
                        st.insert(t);
                        ++sum;
                    }

                    for (auto t : arr2[j])
                    {
                        it = st.find(t);
                        st.erase(it);
                        --sum;
                    }

                    ++j;
                }

                for (auto t : arr1[j])
                {
                    st.insert(t);
                    ++sum;
                }

                for (auto t : arr2[j])
                {
                    it = st.find(t);
                    st.erase(it);
                    --sum;
                }

                ++j;
            }
        }

        for (i = m + 1; i >= 1; --i)
        {
            if (vis[i])
            {
                maxvis = i;
                break;
            }
        }

        if (maxvis == m + 1)
            printf("Dino!\n");

        else
        {
            ans = max(ans, d[maxvis] / (h * 2ll));
            printf("%lld\n", ans);
        }

        for (i = 1; i <= cnt; ++i)
        {
            s[i] = flag[i] = 0;
            arr1[i].clear();
            arr2[i].clear();
        }

        for (i = 1; i <= m + 1; ++i)
            d[i] = minl[i] = vis[i] = 0;

        st.clear();
    }
    return 0;
}
```

---

