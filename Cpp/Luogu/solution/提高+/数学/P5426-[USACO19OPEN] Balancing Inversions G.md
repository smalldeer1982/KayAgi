# [USACO19OPEN] Balancing Inversions G

## 题目描述

Bessie 和 Elsie 在一个长为 $2N$ 的布尔数组 $A$ 上玩游戏（$1 \leq N \leq 10^5$）。Bessie 的分数为 $A$ 的前一半的逆序对数量，Elsie 的分数为 $A$ 的后一半的逆序对数量。逆序对指的是满足 $A[i] = 1$ 以及 $A[j] = 0$ 的一对元素，其中 $i < j$。例如，一段 $0$ 之后接着一段 $1$ 的数组没有逆序对，一段 $X$ 个 $1$ 之后接着一段 $Y$ 个 $0$ 的数组有 $XY$ 个逆序对。

Farmer John 偶然看见了这一棋盘，他好奇于可以使得游戏看起来成为平局所需要交换相邻元素的最小次数。请帮助 Farmer John 求出这个问题的答案。


## 说明/提示

在这个例子中，初始时前一半有 $1$ 个逆序对，后一半有 $3$ 个逆序对。交换了第 $5$ 和第 $6$ 个数之后，两个子数组均有 $0$ 个逆序对。

## 样例 #1

### 输入

```
5
0 0 0 1 0 1 0 0 0 1```

### 输出

```
1```

# 题解

## 作者：littlewyy (赞：24)

[题目链接](https://www.luogu.org/problemnew/show/P5426)

##### 题意

给定1个长度为$2n$的01数组。你可以交换相邻的元素。询问最少交换次数，使得前$n$个元素组成的子数组中的逆序对个数等于后$n$个元素组成的子数组中的逆序对个数。$1 \leq n\leq 10^5$

##### 题解

普通的数组中，数的种类繁多，逆序对的求解及动态维护是很复杂的情况。

考虑利用**01数组**的性质，探寻逆序对个数的**本质**。

对于1个长度为n的子数组而言，它的逆序对个数的计算方法为，对于每个1，累加其后0的个数。而该0的个数又只与该1的下标、其后1的个数有关。

不妨采用**数学方法**进行**化简**。

设长度为$n$的数组中，所有1出现的位置为$a_i$，总共有$x$个1。

则逆序对总数为$n-a_1-(x-1) + n-a_2-(x-2) + ...+n-an-(x-x) = xn - \frac{x(x-1)}{2}-\sum_{i=1}^xa_i$

应用到两个子数组逆序对个数相等的情况，则$xn - \frac{x(x-1)}{2}-\sum_{i=1}^xa_i =  yn - \frac{y(y-1)}{2}-\sum_{i=1}^yb_i$

进一步化简，可得$\frac{\sum a_i-\sum b_i}{y-x}=k$，其中常数$k=\frac{x+y-1-2n}{2}$

因此，只要我们确定了$x$与$y$的大小，即可确定目标的左右坐标和差；也可以确定左右2个子数组各自坐标和的变化范围（全部最靠左/全部最靠右）；因此容易判断目标是否可能实现。

不妨**枚举**$x$，则$y$易求。在求解该情况下达成目标的最小交换次数。

交换情况看似复杂，不妨**分步思考**。

首先，进行必要的交换，使得左数组中有$x$个1，右数组中有$y$个1。

设$move = x - lefNum$，即新的左数组中1的个数与原1的个数的差值，$move > 0$表示应将$move$个1从右数组中过渡到左数组；$move <0$则表示应将$-move$个1从左数组中转移到右数组。下文仅讨论$move>0$的情况，$move < 0$也是同理。

过渡的途径唯一：交换第$n$与第$n+1$位。因此，只有它们分别为0 1时，1次交换才有意义，能达成过渡的目的。

如果要继续过渡，则应将第$n$位的1向左交换。综合$move$个元素进行过渡的情况，发现本质是：左边数组末尾空出$move$个0，右边数组将$move$个1集中到最左端，再将它们顺次过渡。

如何以最少的步数空出$move$个0？经过数学推导，只需找到从右往左的第$move$个0的位置，将原本该位置以后的1从该位开始顺次排列。步数即为这些1的目标位置和与原位置和的差值。通过简单的预处理可以快速求解。

如何以最少的步数将$move$个1集中到最左端？同理，找到第$move$个1的位置，原位置和减去目标位置和即可。

再者，要以最少的位置实现目标的坐标和差。

不难想到，任何1个子数组的坐标和要改变1，只需将某个与0相邻的1交换1次。因此其坐标和变化范围内的任何1个值都可以达到，且每改变1只需交换1次。因此，计算将元素成功过渡后的坐标和差，将其与目标的坐标和差的差值累加入本次答案中。

时间复杂度：$O(n)$。[代码见此](https://github.com/littlewyy/OI/blob/master/2915.cpp)

##### 回顾与思考

问题较为奇怪烦琐时，不妨利用其性质简化问题，探寻其性质。

在面对复杂问题时要有分步思考的意识和耐心，才能抵达真理的彼岸。







---

## 作者：NaN_HQJ2007_NaN (赞：9)

来一篇简单易懂的良心题解。

![](https://cdn.luogu.com.cn/upload/image_hosting/h4jxll0b.png)

由于数值不是 $0$ 就是 $1$，我们可以考虑将逆序对的统计方式化简。

以左区间为例，设 $x$ 为 $1$ 的个数，$p_i$ 为第 $i$ 个 $1$ 的坐标，则逆序对个数为 $\sum\limits_{i=1}^{x}n-p_i-(x-i)$。也就是 $(n-x)\cdot x+\frac{x\cdot (x+1)}{2}-\sum\limits_{i=1}^{x}p_i$。

右区间同理。

题目要求两个区间的逆序对个数相同，所以我们把两个式子联立起来。

$(n-x)\cdot x+\frac{x\cdot (x+1)}{2}-\sum\limits_{i=1}^{x}p_i=(n-y)\cdot y+\frac{y\cdot (y+1)}{2}-\sum\limits_{i=1}^{y}p2_i$

令 $val(d)=(n-d)\cdot d+\frac{d\cdot (d+1)}{2}$。

则 $\sum\limits_{i=1}^{x}p_i-\sum\limits_{i=1}^{y}p2_i=val(x)-val(y)$。

现在考虑怎么把 $t$ 个 $1$ 从左区间移动到右区间。（右到左同理）

我们可以把左区间最右边的 $t$ 个 $1$ 移到左区间最靠右的 $t$ 个位置，再把右区间最左边的 $t$ 个 $0$ 移到右区间最靠左的 $t$ 个位置，接着再用 $t^2$ 次交换调换 $01$ 的位置即可。

而将若干个 $0$ 或 $1$ 移到某一端的交换次数可以通过预处理 $O(1)$ 计算出来。

定义 $sl0_i$ 表示左区间最靠右的 $i$ 个 $0$ 的坐标之和，$sr0_i$ 表示右区间最靠左的 $i$ 个 $0$ 的坐标之和。（$sl1_i$ 和 $sr1_i$ 同理）

接下来我们枚举完成所有交换操作后左区间 $1$ 的个数 $x'$，然后调整若干个 $1$ 所在的区间，再在区间内进行微调使两边 $1$ 的坐标的差值符合要求。

令 $c=|x-x'|$。

如果 $x'<x$，则交换次数为 

$\frac{(n - c + 1 + n) \cdot c}{2} - sl1_c + sr0_c - \frac{c \cdot (c + 1)}{2} + c^2 + |sl1_x - sl1_c - sr1_y - sr0_c - val(x') + val(y + c)|$

否则，交换次数为

$\frac{(n - c + 1 + n) \cdot c}{2} - sl0_c + sr1_c - \frac{c \cdot (c + 1)}{2} + c ^ 2 + |sl1_x + sl0_c - sr1_y + sr1_c - val(x') + val(y - c)|$

最后取个最小值就行了。

### code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
ll n, a[N], b[N], x = 0, y = 0, sl0[N], sl1[N], sr0[N], sr1[N], minn = 1e9, tot;
int val(int d) {return (n - d) * d + d * (d + 1) / 2;}
int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) {cin >> a[i]; if (a[i]) ++x;}
	for (int i = 1; i <= n; ++i) {cin >> b[i]; if (b[i]) ++y;}
	tot = 0; for (int i = n; i >= 1; --i) {if (!a[i]) sl0[tot + 1] = sl0[tot] + i, ++tot;}
	tot = 0; for (int i = 1; i <= n; ++i) {if (!b[i]) sr0[tot + 1] = sr0[tot] + i, ++tot;}
	tot = 0; for (int i = n; i >= 1; --i) {if (a[i]) sl1[tot + 1] = sl1[tot] + i, ++tot;}
	tot = 0; for (int i = 1; i <= n; ++i) {if (b[i]) sr1[tot + 1] = sr1[tot] + i, ++tot;}
	for (int xx = 0; xx <= x + y; ++xx) {
		if (xx > n || x + y - xx > n) continue;
		ll c, num;
		if (xx < x) {
			c = x - xx;
			num = (n - c + 1 + n) * c / 2 - sl1[c] + sr0[c] - c * (c + 1) / 2 + c * c + abs(sl1[x] - sl1[c] - sr1[y] - sr0[c] - val(xx) + val(y + c));
		} else {
			c = xx - x;
			num = (n - c + 1 + n) * c / 2 - sl0[c] + sr1[c] - c * (c + 1) / 2 + c * c + abs(sl1[x] + sl0[c] - sr1[y] + sr1[c] - val(xx) + val(y - c));
		}
		minn = min(minn, num);
	}
	cout << minn << endl;
	return 0;
}
```

这么良心的题解，点个赞再走吧 QWQ

---

## 作者：Unordered_OIer (赞：7)

# P5426 题解
貌似我的分析方式不是太一样？
## 题意
一个$2N$长的$0-1$序列交换多少次相邻数，才能使左边$N$个和右边$N$个逆序对数相同？
## 解答
先设左边的比右边的逆序对个数大。（左边的逆序对个数记为$L$，右边的记为$R$）
那么很容易得到：
$$T=L-R>0$$

把第$N$个和第$N+1$个数交换记作“b类交换”，其他都是“a类交换”。  
那么如果我们不用“b类交换”呢？最少要交换$\color{red}{T}$次。

现在的目标很明确：用“b类交换”减少$T$。  
b类交换怎么交换最好？
1. 把左边的$1$和右边的$0$交换
2. 把左边最右的$1$和右边最左的$0$交换

步骤就是：
1. 把左边最右的$1$移动到末尾
2. 把右边最左的$0$移动到开头
3. 交换

然后我们来考虑b类交换对原序列产生的影响。  
先看这样一个序列：
$$xxxxx\ \ 1\ \ (i)0...0(N-1)|1(N)...1\ \ 0\ \ (j)xxxxx$$
交换成这样：
$$xxxxx\ \ 0\ \ (i)0...0(N-1)|1(N)...1\ \ 1\ \ (j)xxxxx$$

这次“b类变换”操作用了多少步？逆序对差$T$怎么改变？  
$$\color{red}{现在总步数=当前步数+|逆序对之差|}$$

那么我们枚举b类交换次数就可以了。

$\huge{C}ode$
```cpp
int i=n,j=1;
11 cost=0, L=inva, R=invb;
while(1){
	while(i>=1&&a[i]!=1)i--;
	while(j <=n&&b[j]!=0) j++;
	if(i<1|| j>n) break;
	cost+=n+j-i;
	L=L-(n-i)+lefone0[i-1];
	R=R-(j-1)+rigzero1[j+1];
	ans=min(ans , abs(L-R)+cost);
	i--,j++;
}
L=inva, R=invb;
i=n; j=1; cost=0;
while(1){
	while(i>=1&&a[i]!=0)i-- ;
	while(j<=n&&b[j]!=1) j++;
	if(i<1 | |j>n)break ;
	cost+=n+j -i ;
	L=L-lefone0[i], R=R-rigzero1[j];
	ans=min(ans, abs(L-R)+cost);
	i-- ,j++;
}
```
注意代码里有坑  
逆序对快速求就用$BIT$就行了。

---

## 作者：Prean (赞：4)

注意到交换两个不同的元素一定会改变逆序对的数量且变化量为 $1$，所以对于答案有一个明显的上界是左边逆序对数量和右边逆序对数量之差的绝对值。

但是有的元素会跨越中点，所以考虑枚举有多少个 $0,1$ 跨过了中点，能够计算出此时左边和右边分别的逆序对数量。

于是像上述那样处理一下，枚举跨过中点的元素，然后算逆序对之差的绝对值即可。复杂度可以做到 $O(n)$。

注意计算逆序对的时候的细节。
```cpp
#include<cstdio>
#include<cctype>
namespace SOLVE{
	typedef long long ll;
	const int M=2e5+5;
	int n,a[M];ll lans,rans;int l1,l2,t1[M],c1[M],t2[M],c2[M];
	inline void swap(int&a,int&b){
		int c=a;a=b;b=c;
	}
	inline ll abs(const ll a){
		return a>0?a:-a;
	}
	inline ll min(const ll&a,const ll&b){
		return a>b?b:a;
	}
	inline ll calc(const int&L,const int&R){
		ll ans(0);int sum(0);for(int i=L;i<=R;++i)a[i]?++sum:ans+=sum;return ans; 
	}
	inline int read(){
		int n(0);char s;while(!isdigit(s=getchar()));while(n=n*10+(s&15),isdigit(s=getchar()));return n;
	}
	inline ll Solve1(){
		ll ans(abs(lans-rans)),ls(0),rs(0),s1(0),s2(0);l1=l2=0;
		for(int i=n;i>=1;--i)if(!a[i])++l1,t1[l1]=i;for(int i=1;i<=l1;++i)c1[i]=t1[i]-1-(l1-i);
		for(int i=n+1;i<=n*2;++i)if(a[i])++l2,t2[l2]=i;for(int i=1;i<=l2;++i)c2[i]=2*n-t2[i]-(l2-i);
		for(int i=1;i<=l1&&i<=l2;++i){
			ls+=c1[i],rs+=c2[i];s1+=n-i+1-t1[i];s2+=t2[i]-n-i;
			ans=min(ans,abs((lans-ls)-(rans-rs))+s1+s2+1ll*i*i);
		}
		return ans;
	}
	inline ll Solve2(){
		ll ans(abs(lans-rans)),ls(0),rs(0),s1(0),s2(0);l1=l2=0;
		for(int i=n;i>=1;--i)if(a[i])++l1,t1[l1]=i;for(int i=1;i<=l1;++i)c1[i]=n-t1[i]-(i-1);
		for(int i=n+1;i<=n*2;++i)if(!a[i])++l2,t2[l2]=i;for(int i=1;i<=l2;++i)c2[i]=t2[i]-n-1-(i-1);
		for(int i=1;i<=l1&&i<=l2;++i){
			ls+=c1[i],rs+=c2[i];s1+=n-i+1-t1[i];s2+=t2[i]-n-i;
			ans=min(ans,abs((lans-ls+1ll*i*(l1-i))-(rans-rs+1ll*i*(l2-i)))+s1+s2+1ll*i*i);
		}
		return ans;
	}
	inline void main(){
		n=read();for(int i=1;i<=n*2;++i)a[i]=read();lans=calc(1,n);rans=calc(n+1,n*2);
		ll c1,c2;c1=Solve1();c2=Solve2();printf("%lld",c1>c2?c2:c1);
	}
}
signed main(){
	SOLVE::main();
}
```

---

## 作者：zjjws (赞：4)

因为这里只有 $0$ 和 $1$，**逆序对**这个定义很明显就应当简化。

设一段区间有 $k$ 个 $1$，第 $i$ 个 $1$ 的位置为 $x_i$，每个 $1$ 的序号按 $x_i$ 从小到大，这段区间的逆序对个数为：

$$\sum_{i=1}^k(n-x_i)-(k-i)$$

$$=(n-k)\times k+\frac{(k+1)\times k}{2}-\sum_{i=1}^k x_i$$

对于两个序列逆序对个数相等，设前一个序列有 $l$ 个 $1$，第 $i$ 个 $1$ 的位置为 $x_i$；后一个序列有 $r$ 个 $1$，第 $i$ 个 $1$ 的位置为 $y_i$。

则有：

$$(n-l)\times l+\frac{(l+1)\times l}{2}-\sum_{i=1}^lx_i=(n-r)\times r+\frac{(r+1)\times r}{2}-\sum_{i=1}^ry_i$$

可以发现 $\sum$ 前面的东西只跟 $l$ 或 $r$ 有关，也就是说两序列坐标和的差值可以通过 $l$ 和 $r$ 算出来。

而在本题中 $l+r$ 是固定的数值，所以可以枚举 $l$，然后问题就在于这怎么以最小代价去维护两边 $1$ 的个数。

维护策略为：

多余的最靠近另一个序列的若干个 $0$ 或 $1$，进行移动分别到达另一个序列。

可以用交换证明法（忘记了叫什么名字，也可以看作是反证法）证明其最优性。

至于我为什么不写，因为文字叙述比脑内 yy 麻烦很多。

到这里为止基本都是和 @littlewyy 的思路相同的，但是实际实现上，@littlewyy 是按照前面那个求逆序对的公式去做的，而我只用这个公式求了下初始序列的逆序对个数，之后就没有用过了。

但是预处理用到的那些数组确实很方便（我还另外记录了每个 $0$ 的位置）

每次操作是将左边的最后一个 $1$，右边的第一个 $0$，插入另一个序列的头或尾，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/9a2czj8h.png)

设操作的 $1$ 和 $0$ 分别称作 $i$ 和 $j$，左侧的序列为 $X$，右侧的序列为 $Y$。

有以下性质：

$i$ 后面的都是 $0,j$ 前面都是 $1$（自己序列中）。

变化的逆序对数分成四个部分：

$1.\ i$ 和 $X$ 中 $i$ 后面的 $0$ 组成的逆序对应减去。

$2.\ j$ 和 $Y$ 中 $j$ 前面的 $1$ 组成的逆序对应减去。

$3.\ j$ 后面的 $0$ 和移动后的 $i$ 组成新的逆序对。

$4.\ i$ 前面的 $1$ 和移动后的 $j$ 组成新的逆序对。

在我们已经记录下每个 $0$ 和 $1$ 的位置的时候，每个操作的影响都是可以 $\operatorname O(1)$ 算出来的。

$X$ 中的 $0$ 和 $Y$ 中的 $1$ 的交换可以自己推一下。

这样是常数极小的 $\operatorname O(n)$ 实现，也跑了个最优解。

代码附下：

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAX=1e5+3;
int x[MAX];
int y[MAX];
int x_z[MAX];
int y_z[MAX];
LL n;
LL rin()
{
    LL s=0;
    char c=getchar();
    bool bj=0;
    for(;(c>'9'||c<'0')&&c!='-';c=getchar());
    if(c=='-')c=getchar(),bj=true;
    for(;c>='0'&&c<='9';c=getchar())s=(s<<1)+(s<<3)+(c^'0');
    if(bj)return -s;
    return s;
}
int main()
{
    n=rin();
    LL l,r;
    LL l_z,r_z;
    l=r=l_z=r_z=0;
    for(int i=1;i<=n;i++)
    {
        char c=getchar();
        for(;c!='0'&&c!='1';c=getchar());
        if(c=='1')x[++l]=i;
        else x_z[++l_z]=i;
    }
    for(int i=1;i<=n;i++)
    {
        char c=getchar();
        for(;c!='0'&&c!='1';c=getchar());
        if(c=='1')y[++r]=i;
        else y_z[++r_z]=i;
    }
    LL l_s,r_s;
    LL ans;
    l_s=(n-l)*l+((l+1)*l>>1);
    r_s=(n-r)*r+((r+1)*r>>1);
    for(int i=1;i<=l;i++)l_s-=x[i];
    for(int i=1;i<=r;i++)r_s-=y[i];
    if(l_s==r_s)
    {
        printf("0");
        return 0;
    }
    ans=abs(l_s-r_s);
    LL s_l=l_s,s_r=r_s;
    LL cost_s=0;
    for(int i=l,j=1;i>0&&j<=r_z;i--,j++)
    {
        //i为左边的最后一个1,j为右边的第一个0
        s_l-=(n-x[i]);
        s_l+=(i-1);
        s_r-=(y_z[j]-1);
        s_r+=(r_z-j);
        cost_s+=(n-x[i])+y_z[j];
        if(cost_s>=ans)break;
        ans=min(ans,cost_s+abs(s_l-s_r));
    }
    s_l=l_s;s_r=r_s;
    cost_s=0;
    for(int i=l_z,j=1;i>0&&j<=r;i--,j++)
    {
        //i是左边最后一个0，j是右边第一个1
        s_l-=(x_z[i]-i);
        s_r-=(n-y[j])-(r-j);
        cost_s+=(n-x_z[i])+y[j];
        if(cost_s>=ans)break;
        ans=min(ans,cost_s+abs(s_l-s_r));
    }
    printf("%lld",ans);
    return 0;
}
```


---

## 作者：Rainy_chen (赞：4)

## 题意
给出一个长度为 $2n$ 的 $01$ 序列，我们定义「左边」为前 $n$ 个数的序列，「右边」为后 $n$ 个数的序列。  
你需要求出最少进行几次交换才能使左边和右边的逆序对数相同。  

$1\le n\le10^5$
## 题解
首先我们考虑永远不会交换 $n,n+1$ 这两个位置的数时该怎么统计答案。  

当原序列存在一对相邻的 $0,1$ 时，若 $0$ 在前，则交换这两个数会让序列的逆序对数 $+1$，反之，则 $-1$。容易发现实际上除非原序列构成了形如 $aaaaaabbbbbb$ 的形状的话，我们是总有办法通过 $1$ 次交换来使得逆序对数发生 $1$ 的改变。

同时，基于上面这个性质，我们会发现总是可以将一个序列的逆序对数量操作到某个和这个序列中 $1$ 的数量有关的区间内。  

这意味着我们如果不交换 $n,n+1$，那就只需要考虑左右两边的逆序对数，记为 $x,y$，然后令逆序对数多的那一边不断操作直到两边相同为止，这时答案是 $\mathrm {abs}(x-y)$。  

但是不交换 $n,n+1$ 却依然能获得最优解的概率并不高，所以我们还是要考虑需要交换的情况。  

很明显的，需要交换 $n,n+1$ 当且仅当我们想让左右两边的 $1$ 的数量发生变化。  

因此我们考虑枚举左右两边的每一个 $1$，然后尝试将它交换到另一边，然后统计答案案。这里我们以想要将左边的 $1$ 交换到右边为例。  

我们定义 $pre[i][j],las[i][j],cnt[i][j]$ 分别为 $i$ 这一边中第一个出现的 $j$ 的位置，$i$ 这一边中最后一个出现的 $j$ 的位置，$i$ 这一边中 $j$ 的出现次数。  

那么尝试将一个 $1$ 放到右边时，我们当然是想要让左边的最后一个 $1$ 交换到 $n$，将右边的第一个 $0$ 交换到 $n+1$，再交换 $n,n+1$。  
于是我们可以计算出这样做的代价就是 $n-las[0][1]+pre[1][0]$。  

但是我们只是仅仅计算出了交换的代价而已，交换的过程中还会对左右两边的逆序对数产生影响。

对于左边来说，其逆序对数发生的变化是：最后一个 $1$ 被放到了 $n$ 这个位置，$n$ 这个位置变成了 $0$，前者会使逆序对数减少 $n-las[0][1]$，后者会使逆序对数增加 $cnt[0][1]-1$。  

剩下三种情况（从左边把 $1$ 换到右边时右边的变化，从右边把 $1$ 换到左边时左右两边的变化）可以尝试自己讨论一下，难度并不大。  

注意一下尝试从左边换 $1$ 到右边和从右边换 $1$ 到左边中间需要还原一下数据。  

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long int_t;

int_t read() {
    int_t x = 0, w = 1; char ch = 0;
    while(!isdigit(ch)) {ch = getchar(); if(ch == '-') w = -1;}
    while(isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
    return x * w;
}

const int_t maxn = 100010;

int_t A[maxn], B[maxn];
queue<int_t> pre[2][2];
stack<int_t> las[2][2];

int main() {
    int_t n = read();
    for(int_t i=1;i<=n;i++) A[i] = read();
    for(int_t i=1;i<=n;i++) B[i] = read();
    int_t x = 0, y = 0, tmp = 0, tans = 0;
    for(int_t i=1;i<=n;i++) if(A[i]) ++tmp; else x += tmp; 
    tmp = 0;
    for(int_t i=1;i<=n;i++) if(B[i]) ++tmp; else y += tmp;
    int_t cnt[2][2] = {0}, tx = x, ty = y;
    for(int_t i=1;i<=n;i++) ++cnt[0][A[i]], pre[0][A[i]].push(i), las[0][A[i]].push(i);
    for(int_t i=1;i<=n;i++) ++cnt[1][B[i]], pre[1][B[i]].push(i), las[1][B[i]].push(i); 
    int_t ans = abs(x-y);
    while(cnt[0][1] && cnt[1][0]) {
        tans += pre[1][0].front() + n - las[0][1].top();
        x = x - n + las[0][1].top() + cnt[0][1] - 1;
        y = y - pre[1][0].front() + cnt[1][0];
        las[0][1].pop(); pre[1][0].pop(); cnt[0][0]++; cnt[0][1]--; cnt[1][0]--; cnt[1][1]++;
        ans = min(ans, abs(x-y) + tans);
    } 
    tans = cnt[0][1] = cnt[1][0] = cnt[0][0] = cnt[1][1] = 0;
    for(int_t i=1;i<=n;i++) ++cnt[0][A[i]];
    for(int_t i=1;i<=n;i++) ++cnt[1][B[i]];
    x = tx; y = ty;
    while(cnt[0][0] && cnt[1][1]) {
        tans += pre[1][1].front() + n - las[0][0].top();
        y = y - cnt[1][0] + pre[1][1].front() - 1; 
        x = x - cnt[0][1] + n - las[0][0].top();
        pre[1][1].pop(); las[0][0].pop(); cnt[0][0]--; cnt[0][1]++; cnt[1][0]++; cnt[1][1]--;
        ans = min(ans, abs(x-y) + tans);
    }
    cout << ans;
}
```
## 证明
*这部分写的比较复杂，因此我们放到最后来说*  

首先我们最初所说的那个有关于 $\mathrm{abs}(x-y)$ 的结论，容易发现你无论如何交换，都不可能在一次交换中让逆序对数产生大于 $1$ 的变化，因为你的交换只会影响所交换两个数之间的位置关系，无法影响到其他数，那么 $\mathrm{abs}(x-y)$ 就是交换次数的下界了。  

其次是另一个问题，我们如何保证在交换 $1$ 的时候不会产生冗余的操作？换句话说，我怎么知道先把 $1$ 换来换去是不是最优解？~~手模发现不可能~~

我们需要知道的是，实际上我们是在枚举左右两边 $1$ 的数量，只是直接这么做比较麻烦所以改为尝试将 $1$ 换边而已。那么当我们确定左右两边中 $1$ 的数量以后，我们也就能确定需要交换多少个 $1$ 了。  

我们在题解中进行的交换实际上是将与中间最近的数个 $1$ 交换到另一侧，这一部分的操作是必须进行的，而且代价不会变少，在其他合法方案中也是必须进行的，差别只是进行的时间。  

而为什么换最靠中间的数个 $1$ 是最优的，我们可以考虑反证，如果换这几个 $1$ 不是最优的，那么我们依然需要换足够数量的 $1$，只能从不那么靠近中间的 $1$ 中代替。  

考虑某个在原方案中需要交换的第 $i$ 个 $1$，现在它不能被交换，而要去交换另一个比这个 $1$ 靠外的 $1$。在交换的过程中，总会使得存在一个时间，我们需要交换这两个 $1$，而我们知道交换两个 $1$ 的操作一定是冗余的，因此这样的操作方案一定不会是最优秀的。

---

## 作者：Mirasycle (赞：1)

首先交换相邻不同 $01$ 之后逆序对变化是 $1$。设左右逆序对个数为 $n_1,n_2$，所以有一种方案是对于左边或者右边内部调整，次数是 $\lvert n_1-n_2\rvert$。

发现如果我们跨过中点移动，变化量可能会很大，使得答案更优。

这里分为 $01$ 交换和 $10$ 交换，不难发现只有可能选其中的一种来调整（一次 $01$，一次 $10$ 就复原了），下面以 $01$ 交换为例。

我们暴力枚举交换次数，也就是说不断把左边的 $0$ 和右边的 $1$ 拉过去交换，每次交换之后用当前的移动次数 $+\lvert n_1-n_2\rvert$ 更新答案。注意每次选择是最靠近中轴线的 $0$ 和 $1$ 出来交换。 

时间复杂度 $O(n)$。


```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define fi first
#define se second
#define mp make_pair
using namespace std;
typedef long long ll;
const int maxn=2e5+10;
void cmax(ll &x,ll y){ x=x>y?x:y; }
void cmin(ll &x,ll y){ x=x<y?x:y; }
int n,a[maxn],b[2][2],c[2][2];
vector<int> vec[2][2];
ll n1,n2,tn1,tn2,ans=0; int cnt=0;
int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n;
	for(int i=1;i<=2*n;i++) cin>>a[i];
	for(int i=n;i>=1;i--) vec[0][a[i]].pb(i),c[0][a[i]]++;
	for(int i=n+1;i<=2*n;i++) vec[1][a[i]].pb(i),c[1][a[i]]++;
	for(int i=1;i<=n;i++) cnt+=a[i],n1+=(a[i]==0)*cnt; cnt=0;
	for(int i=n+1;i<=2*n;i++) cnt+=a[i],n2+=(a[i]==0)*cnt;
	ans=abs(n1-n2);
	// swap 0,1
	for(int i:{0,1}) for(int j:{0,1}) b[i][j]=c[i][j];
	tn1=n1; tn2=n2; ll cur=0;
	for(int i=0;i<min(vec[0][0].size(),vec[1][1].size());i++){
		int p1=vec[0][0][i],p2=vec[1][1][i];
		int dl=n-p1,dr=p2-n-1;
		cur+=dl+dr+1; n1+=dl-c[0][1]; n2+=dr-c[1][0];
		cmin(ans,cur+abs(n1-n2));
		c[0][1]++; c[0][0]--;
		c[1][0]++; c[1][1]--;
	}
	//swap 10
	for(int i:{0,1}) for(int j:{0,1}) c[i][j]=b[i][j]; 
	n1=tn1; n2=tn2; cur=0;
	for(int i=0;i<min(vec[0][1].size(),vec[1][0].size());i++){
		int p1=vec[0][1][i],p2=vec[1][0][i];
		int dl=n-p1,dr=p2-n-1;
		cur+=dl+dr+1; n1+=c[0][1]-dl; n2+=c[1][0]-dr;
		cmin(ans,cur+abs(n1-n2));
		c[0][1]--; c[0][0]++;
		c[1][1]++; c[1][0]--; 
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：_Imaginary_ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P5426)

## 题意概述

- 给定一个长度为 $2\times n$ 的布尔数列，求交换的最小次数，使得左右两个长度为 $n$ 的数列的逆序对的数量相同。

## 思考

首先，我们令 $\Delta=f(1,n)-f(n+1,2\times n)$, 其中 $f(i,j)$ 表示这个数列下标在 $i$ 和 $j$ 之间的这个子数列的逆序对数，那么答案就是使 $\Delta=0$ 的最小次数。举个例子：

```
5
0 0 0 1 0 1 0 0 0 1
```

在左边 $n$ 个数中，互相交换位置，改变的逆序对数 $\delta=\pm 1$。

但是，在中间的 `0 1 ` 交换就会造成较大的变动。

具体的，左侧的所有 1 与第 $n$ 号位置的 0 组成的逆序对消失了，同时第 $n+1$ 号位的新的 1 与后面所有的 0 会产生新的逆序对。

所以，$\Delta$ 改变的数量为：$\text{Left1}+\text{Right1}-n=sum-n$。其中 $sum$ 为整个数列中 1 的个数，即数列元素之和。

但是，如果中间的两个元素一样怎么办？再看一个例子：

```
5
0 1 0 1 1 0 0 0 1 1
```

当然，最优方法显然并不涉及到中间两者的交换，仅供演示。

我们考虑将**最靠近 $n$ 的左侧第一个 0** 与**最靠近 $n+1$ 的右侧第一个 1** 分别换到 $n$ 和 $n+1$ 两个位置，再进行一次交换。此时记录这次交换所需要的次数，以及交换后 $\Delta$ 的值。

所以，这种交换的次数最多为左侧 0 的个数，即不超过 $n$，可以直接进行枚举。

同样的，我们对于另一种操作，也进行差不多的枚举。

时间复杂度 $\Theta(n)$，似乎很容易被 $10^5$ 的数据范围骗到。

## CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=200005;
int x[N],y[N],z[N],n;
ll ans,ansL,ansR;
int L0[N],L1[N],R0[N],R1[N];
int L0siz=0,R1siz=0,R0siz=0,L1siz=0;
ll sum=0;
void merge_sort(int L,int R)
{
    ans=0;
    int zr=0;
    for(int i=R;i>=L;i--)
    {
        if(!x[i]) zr++;
        else ans+=zr;
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=2*n;i++)
	{
		scanf("%d",&x[i]);
		sum+=x[i];
	}
    merge_sort(1,n);
    ansL=ans;
    merge_sort(n+1,2*n);
    ansR=ans;
    ll Dt=ansL-ansR;
    if(Dt==0)
    {
        printf("0");
        return 0;
    }
    for(int i=1;i<=n;i++)
    {
        if(x[i]==0) L0[++L0siz]=i;
        else L1[++L1siz]=i;
    }
    for(int i=2*n;i>=n+1;i--)
    {
        if(x[i]==1) R1[++R1siz]=i;
        else R0[++R0siz]=i;
    }
    ll ans=abs(Dt);
    ll step=0;
    while(L0siz>0&&R1siz>0)
    {
        int LL=L0[L0siz],RR=R1[R1siz];
        int tmp=(n-LL)-(RR-n-1)-(sum-n);
        Dt+=tmp;
        step+=(n-LL)+(RR-n-1)+1;
        L0siz--;
        R1siz--;
        ans=min(ans,abs(Dt)+step);
    }
    Dt=ansL-ansR;
	step=0;
	while(L1siz>0&&R0siz>0)
	{
	    int LL=L1[L1siz],RR=R0[R0siz];
	    int tmp=(n-LL)-(RR-n-1)-(sum-n);
	    Dt-=tmp;
	    step+=(n-LL)+(RR-n-1)+1;
	    L1siz--;
	    R0siz--;
	    ans=min(ans,abs(Dt)+step);
    }
    printf("%lld",ans);
    return 0;
}
```





---

