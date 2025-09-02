# Restorer Distance

## 题目描述

You have to restore the wall. The wall consists of $ N $ pillars of bricks, the height of the $ i $ -th pillar is initially equal to $ h_{i} $ , the height is measured in number of bricks. After the restoration all the $ N $ pillars should have equal heights.

You are allowed the following operations:

- put a brick on top of one pillar, the cost of this operation is $ A $ ;
- remove a brick from the top of one non-empty pillar, the cost of this operation is $ R $ ;
- move a brick from the top of one non-empty pillar to the top of another pillar, the cost of this operation is $ M $ .

You cannot create additional pillars or ignore some of pre-existing pillars even if their height becomes $ 0 $ .

What is the minimal total cost of restoration, in other words, what is the minimal total cost to make all the pillars of equal height?

## 样例 #1

### 输入

```
3 1 100 100
1 3 8```

### 输出

```
12```

## 样例 #2

### 输入

```
3 100 1 100
1 3 8```

### 输出

```
9```

## 样例 #3

### 输入

```
3 100 100 1
1 3 8```

### 输出

```
4```

## 样例 #4

### 输入

```
5 1 2 4
5 5 3 6 5```

### 输出

```
4```

## 样例 #5

### 输入

```
5 1 2 2
5 5 3 6 5```

### 输出

```
3```

# 题解

## 作者：wsyhb (赞：15)

## 前言

本文的主要目的是**证明以最终高度为自变量，最小代价为因变量的函数是下凸函数**。

**其他题解的证明没有考虑到可能产生的 $X \le Y$ 和 $X>Y$ 的交界**（$X$ 和 $Y$ 是下文证明中的未知数）。在此基础上，**大多数题解的证明比较含糊；不含糊的[@马保国官方号](https://www.luogu.com.cn/user/150522)的题解的证明是错的**（它计算 $C'$ 的第三行漏掉了 $AN$ 这一项，得出了 $C'<0$ 这个错误结论）。

同时也希望各位读者：如果发现了本文中出现的任何错误，请立即在评论区指出或私信笔者，笔者将尽快回复和修改。

## 题解

首先，一次操作三相当于一次操作一和一次操作二，不妨令 $M=\min(M,A+R)$。

那么，执行 $X$ 次操作一和 $Y$ 次操作二的最小代价为 $(X-\min(X,Y))A+(Y-\min(X,Y))R+\min(X,Y) \cdot M$。  
(即：**将操作一和操作二尽可能配对，每对花费 $M$ 的代价**)

然后，设最终所有砖块的高度都变为了 $H$，那么上述的 $X,Y$ 应满足 $X=\sum_{h_i \le H}(H-h_i)$，$Y=\sum_{h_i>H}(h_i-H)$。  
（我们显然不会对同一砖块的高度又加又减）

设 $f(H)$ 表示最终所有砖块的高度都变为了 $H$ 的最小代价，则有：

$$f(H)=
\begin{cases}
(Y-X)R+XM & (X \le Y) \\
(X-Y)A+YM & (X > Y)
\end{cases}$$

(就是将第二段那个式子中的 $\min(X,Y)$ 用 $X$ 或 $Y$ 代替）

为了方便，**下文用 $f(H)$ 相关的变量加上一撇表示 $f(H+1)$ 相对应的变量**。

设初始高度 $\le H$ 的砖块恰有 $P$ 个，则 $X'=X+P$，$Y'=Y-(N-P)$。  

说一下 $X',Y'$ 的计算方法：**先将 $X,Y$ 式子中的 $H$ 变为 $H+1$，然后将 $h_i=H+1$ 的部分从 $Y$ 移到 $X$，就变成了 $X',Y'$。（其中 $h_i=H+1$ 的部分在 $X$ 和 $Y$ 中都为 $0$，无影响)**

令函数 $f'(H)=f(H+1)-f(H)$，分类讨论 $f'(H)$ 的值：

若 $X \le Y$ 且 $X' \le Y'$，则 

$$f(H+1)-f(H)=(Y'-X')R+X'M-(Y-X)R-XM=M \cdot P-NR \quad (1)$$

若 $X \le Y$ 且 $X'>Y'$，则 

$$f(H+1)-f(H)=(X'-Y')A+Y'M-(Y-X)R-XM=M \cdot P+(X-Y+N)A+(Y-X-N)M+(X-Y)R \quad (2)$$

若 $X>Y$ 且 $X'>Y'$，则

$$f(H+1)-f(H)=(X'-Y')A+Y'M-(X-Y)A-YM=M \cdot P+NA-NM \quad (3)$$

请注意：**随着 $H$ 的增大，$X$ 增大，$Y$ 减小，$P$ 增大，(1)(2)(3) 三种情况依次出现。**

由于 (1)(2)(3) 中**除 $P$ 以外都是定值**，所以 $f'$ 函数在 (1)(2)(3) 这三段**分别单调不降**。

(2)-(1) 得 $M \Delta P+(X-Y+N)(A+R-M)$。由于 $\Delta P \ge 0$，$X-Y+N=X'+Y'+2(N-P)>0$ 且 $M \le A+R$，所以 (2)-(1) $\ge 0$，所以 **(1)(2) 合起来也单调不降**。

(3)-(2) 得 $M \Delta P-(X-Y)(A+R-M)$。由于 $\Delta P \ge 0$，$X \le Y$，$M \le A+R$，所以 (3)-(2) $\ge 0$，所以 **(2)(3) 合起来也单调不降**。

综上所述，**$f'$ 在定义域内单调不降—— $f$ 是下凸函数**。

P.S.

学过导数的人都知道 $f'$ 就是 $f$ 的导函数（注意 $f$ 自变量为整数），而下凸函数的一种等价定义是其导函数单调不降，或表述为其二阶导函数恒 $\ge 0$。

**如果你没学过导数，可以将其简单地理解为函数 $f$ 变化量呈上升趋势，画个图就可以知道这可以判定下凸函数。**

## 代码

$O(n\log{n})$ **排序+前缀和**预处理，即可单次 $O(\log{n})$ 求得 $X$ 和 $Y$。外层套上**三分**即可以 $O(n\log_2{n}+\log_2{n}\log_{\frac{3}{2}}{10^9})$ 的时间复杂度解决本题。

P.S. 按本代码中整数三分的写法，边界条件应为 $[l,r]$ 的长度 $<3$，**若写法不同应具体情况具体处理**。

``` cpp
#include<bits/stdc++.h>
using namespace std;
int N,A,R,M;
const int max_N=1e5+5;
int h[max_N];
long long sum[max_N];
inline long long calc(int H)
{
	int p=upper_bound(h+1,h+N+1,H)-h-1;
	long long X=1ll*p*H-sum[p],Y=(sum[N]-sum[p])-1ll*(N-p)*H,c=min(X,Y);
	return A*(X-c)+R*(Y-c)+M*c;
}
int main()
{
	scanf("%d%d%d%d",&N,&A,&R,&M);
	M=min(M,A+R);
	for(int i=1;i<=N;++i)
		scanf("%d",h+i);
	sort(h+1,h+N+1);
	for(int i=1;i<=N;++i)
		sum[i]=sum[i-1]+h[i];
	int l=h[1],r=h[N];
	while(l<r)
	{
		int lmid=l+(r-l)/3,rmid=r-(r-l)/3;
		if(calc(lmid)<calc(rmid))
			r=rmid-1;
		else
			l=lmid+1;
	}
	printf("%lld\n",calc(l));
	return 0;
}
```

---

## 作者：钓鱼王子 (赞：11)

这道题是我最慌的一道题，因为和 CF 其他做法完全不一样（他们好像都是三分）。

但仔细想一想，仿佛是对的？

其实这道题和 [六省联考] 期末考试很像。

首先，令三种操作分别为 $A,B,C$（我习惯了）。

操作的顺序无法影响答案，$C$ 操作可以视为 $A+B$。

那么我们有几种情况：

$1.$全用 $A,B$，那么这样最终答案一定还和初始的某一位置上答案一样，枚举即可。

$2.$只用 $A,C$，那么只有两种情况：一直用 $C$，最后 $A$ 调整，这个就是中位数 $+$ 余数。或者在某一个位置终止，此时 $A$ 代价一定小于 $C$ 代价，否则之前更优，由于操作顺序不变，所以可以先进行所有 $C$ 操作，我们发现，当最大值变小时，答案一直变小，直到它和次大值一样的时候才会有改变，所以最终答案一定还和初始的某一位置上答案一样。

$3.$只用 $B,C$ 同上。

不可能 $A,B,C$ 都用，因为 $C$ 和 $A+B$是等价的。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
#define int long long
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int n,m,t,ans,a,b,c,d,x,y,h[100002],sum[100002],ave,kkk,kkkk;
signed main(){ans=1e18;
	n=read();a=read();b=read();c=read();
	for(re int i=1;i<=n;++i)h[i]=read();
	sort(h+1,h+n+1);
	for(re int i=1;i<=n;++i)sum[i]=sum[i-1]+h[i];ans=0;
		ave=sum[n]/n;
		for(re int i=1;i<=n;++i)if(h[i]<=ave)ans+=ave-h[i];
		ans*=c;ans+=(sum[n]-ave*n)*b;
		x=ans;ans=0;
		++ave;
		for(re int i=1;i<=n;++i)if(h[i]>=ave)ans+=h[i]-ave;
		ans*=c;ans+=(ave*n-sum[n])*a;ans=min(ans,x);
		for(re int i=1;i<=n;++i){
			x=h[i]*(i-1)-sum[i-1];
			y=sum[n]-sum[i]-h[i]*(n-i);
			if(x<y)ans=min(ans,c*x+(y-x)*b);
			else ans=min(ans,c*y+(x-y)*a);
		}
		for(re int i=1;i<=n;++i)kkk+=h[n]-h[i];
		ans=min(ans,kkk*a);
		for(re int i=1;i<=n;++i)kkkk+=h[i]-h[1];
		ans=min(ans,kkkk*b);
		for(re int i=1;i<=n;++i){
			x=h[i]*(i-1)-sum[i-1];
			y=sum[n]-sum[i]-h[i]*(n-i);
			ans=min(ans,a*x+b*y);
		}
		printf("%lld",ans);
}
```


---

## 作者：b6e0_ (赞：7)

[CF题面传送门](https://codeforces.com/contest/1355/problem/E) [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1355E) [博客食用更佳](https://www.luogu.com.cn/blog/b6e0/tijie-CF1355E)

### update 2020.5.21 增加了一种做法并讲解了 $g$ 函数的另一种实现方法。
### update 2020.6.6 更改了几个错误公式，去掉了已解决的问题，增加了单谷函数的证明。
### update 2020.10.7 修+规范了几个公式，格式改为现在的要求。
### update 2020.12.3 修三分证明的明显错误，感谢[Starlight_Glimmer](https://www.luogu.com.cn/user/41165)的指出。

首先，移动也可以为一增一减，所以先将 $M$ 与 $A+R$ 取 $\min$。

第一种做法：三分。

首先很容易想到的一个暴力方法是枚举答案，对于每一个枚举到的答案求花费比 $\min$。再继续观察，发现这个花费是一个单谷函数。证明：

设修改后的高度为 $H$，那么考虑 $H$ 和 $H+1$ 要花费的代价的差。

下面对 $X>Y$ 的情况进行讨论。

设最终所有砖块的高度为 $H$，$\sum_{h_i\le H}H-h_i$ 即需要增加的高度和为 $X$，$\sum_{h_i>H}h_i-H$ 即需要减少的高度和 $Y$，需要的代价 $C=MY+A(X-Y)$。

考虑当 $H$ 增加 $1$ 时变化了什么。设满足 $h_i\le H$ 的 $i$（$X$ 的增量）有 $\Delta X$ 个，$X'=X+\Delta X$，那么 $Y$ 就会减少 $N-\Delta X$，$Y'=Y+\Delta X-N$。需要的代价为：

$$\begin{aligned}C'&=MY'+A(X'-Y')\\&=M(Y+\Delta X-N)+A(X+\Delta X-Y-\Delta X+N)\\&=MY+A(X-Y)+M\Delta X-MN\end{aligned}$$

由于 $\Delta X<N$，所以 $M\Delta X<MN$，所以 $C$ 是单调递减的。

类似地，当 $X<Y$ 时，$C$ 是单调递增的。所以 $C$ 是单谷的。

就能想到三分法，但是在缩小 $l$ 和 $r$ 的范围时与单峰函数稍微有些不同。三分方法：

设答案为 $x$ 的花费为 $g(x)$。三分法类似于二分，对于一个区间 $[l,r]$，在里面取两个点（二分是一个） $lmid$ 和 $rmid$。如果 $g(lmid)>g(rmid)$的话，有两种情况：1.$lmid$ 和 $rmid$ 都在谷的左边；2.$lmid$ 在谷的左边，$rmid$ 在谷的右边。但无论是什么情况，$lmid$ 都在谷的左边，所以 $l=lmid$。$g(lmid)<g(rmid)$ 时类似，$r=rmid$。

当 $lmid$ 和 $rmid$ 为三等分点时，$[l,r]$ 每次缩小 $\dfrac 1 3$；当 $lmid$ 和 $rmid$ 都靠近 $\dfrac{l+r}2$ 时，每次 $[l,r]$ 缩小 $\dfrac 1 2$。所以一般在 $\dfrac{l+r}2$ 旁边取两个数作为 $lmid$ 和 $rmid$。

这儿有一个不用想三分边界的方法：取一个合适的区间大小，$[l,r]$ 小于这个长度就退出循环，然后对于这个区间中的每个数取 $\min$。区间大小可以设为 $100$。

具体细节与 $g$ 的求法看代码：

```cpp
#include<bits/stdc++.h>
using namepace std;
int n;
long long a,r,m,h[100010];
long long getans(long long mid)//g函数
{
	int i;
	long long sum1=0,sum2=0;//sum1为比mid小的所有数与mid的差，sum2为比mid大的所有数与mid的差
	for(i=0;i<n;i++)
		if(h[i]<mid)
			sum1+=mid-h[i];
		else
			sum2+=h[i]-mid;
	if(sum1>sum2)
		return min(sum2*m+(sum1-sum2)*a,sum1*a+sum2*r);//两条公式，注意这儿要取移多补少与直接加减的min
	return min(sum1*m+(sum2-sum1)*r,sum1*a+sum2*r);
}
int main()
{
	int i;
	long long le=1,ri=1e9,lm,rm,ans=1e18;
	cin>>n>>a>>r>>m;
	m=min(m,a+r);//移动也可以为一增一减
	for(i=0;i<n;i++)
		cin>>h[i];
	while(ri-le>100)//三分边界
	{
		lm=(le+ri)>>1;
		rm=((le+ri)>>1)+1;//我取的两个数是mid和mid+1
		if(getans(lm)>getans(rm))
			le=lm;
		else
			ri=rm;//注意这儿两个不能写反
	}
	for(;le<=ri;le++)
		ans=min(ans,getans(le));//对区间取min
	cout<<ans;
	return 0;
}
```

时间复杂度为 $\mathcal O(n(\log10^9+100))$。

---
第二种做法：贪心。

考虑利用贪心快速找出上文中的 $C$ 也就是代价的“谷”。发现“谷”就在 $X=Y$，也就是需要增加的高度与需要减少的高度相同时。此时最终所有砖块的高度就是 $\overline h$。为了保险，建议对上取整 $\lceil\overline h\rceil$ 和下取整 $\lfloor\overline h\rfloor$ 各求一次答案比 $\min$。这种情况的贪心策略其实就是尽量多用 $M$，因为 $M$ 已经与 $A+R$ 取 $\min$ 过了，$M\le A+R$。

但是会出现 $h$ 中大部分数都是同一个数的情况，还需要将数组里的每一个数作为答案求一次 $g$ 再比 $\min$。这时，如果用 $\mathcal O(n)$ 的 $g$ 就会超时，下面就要讲一种 $g$ 的 $\mathcal O(\log n)$ 的求法。

发现原来 $g(mid)$ 中的复杂度瓶颈在求大于和小于 $mid$ 的数与 $mid$ 的差之和。这个操作可以用二分解决。先对 $h$ 排序，然后就可以用二分找到 $mid$ 这个点，再用前缀和求出差。其实用这种做法求 $g$ 配合上面的三分可以达到更优的 $\mathcal O(n+\log^2 n)$，近似于线性做法。

代码这里就不放了。贪心的时间复杂度为 $\mathcal O(n\log n)$。

---

## 作者：关怀他人 (赞：3)

#### 三分大法好
------------

首先不难发现操作1和操作2加在一起可以达到操作3的效果，所以可以令$M=min(M,A+R)$

其次操作的顺序也是不影响答案的，可以先对原数组排序

假设最终所有砖块的高度为$H$，设当前所有高度小于$H$的砖块与$H$的差的和，即**所需要增加的总高度为**$X$，当前所有高度大于$H$的砖块与$H$的差的和，即**所需要降低的总高度为**$Y$

若$X>Y$，则我们可以先**对$Y$的高度做3操作**，再**对剩下的$(X-Y)$的高度做1操作**，那么总花费为$C(H)=A(X-Y)+MY$

若$X<Y$，同理不难得出总花费为$C(H)=R(Y-X)+MX$

现在我们对$X<Y$这种情况进行分析，**若$H$增加1**，我们考虑花费会变成什么，设当前满足$h[i] \leq H$的$i$的个数**即$H$变成$H+1$时需要增加的高度的变化量**为$\Delta h$，则$X'=X+\Delta h$，那么此时**需要减少的高度的变化量**为$N-\Delta h$，则$Y'=Y-(N-\Delta h)=Y-N+\Delta h$，不难得出
$$
\begin{aligned}
C(H+1)&=R(Y'-X')+MX'\\ 
&=R(Y-N+\Delta h-X-\Delta h)+M(X+\Delta h)\\
&=R(Y-X)+MX-RN+M\Delta h
\end{aligned}
$$

那么$C$的导数即为$C'(H)=\frac{C(H+1)-C(H)}{H+1-H}=-RN+M\Delta h$

同理当$X>Y$时$C'(H)=AN-MN+M\Delta h$

由于导数为一次函数，不难得出$C$的图像是一个类似二次函数的东西且**导数先负后正**，所以它是**单谷的**。

对于这种单谷的函数，要求它的最小值不难想到**三分法**，于是直接套三分的模板即可

最后是代码
```
#include<bits/stdc++.h>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
using namespace std;
typedef long long ll;

const int INF = 0x3f3f3f3f;
const int MAXN = 1e5 + 5;

int n;
ll A,R,M;
int h[MAXN];

ll Calc(int H){
	ll sum1 = 0,sum2 = 0;
	for(int i = 1;i <= n;i++){
		if(h[i] <= H)
			sum1 += H - h[i];
		else
			sum2 += h[i] - H;
	}
	if(sum1 <= sum2)
		return M * sum1 + R * (sum2 - sum1);
	else
		return M * sum2 + A * (sum1 - sum2);
}

int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	scanf("%d%lld%lld%lld",&n,&A,&R,&M);
	M = min(M,A + R);
	for(int i = 1;i <= n;i++)
		scanf("%d",&h[i]);
	int l = 0,r = 2e9;
	while(l + 1 < r){
		int lmid = l + (r - l + 1) / 3;
		int rmid = r - (r - l + 1) / 3;
		ll lsum = Calc(lmid);
		ll rsum = Calc(rmid);
		if(lsum > rsum)
			l = lmid;
		else
			r = rmid;
	}
	printf("%lld\n",min(Calc(l),Calc(l + 1)));
	return 0;
}



---

## 作者：一扶苏一 (赞：3)

## 【CF1355E】 Restorer Distance

### Analysis

没有证出单谷，但是搞出了另一个性质。

首先加入一块砖再撤掉一块砖也可以达到操作三的效果，所以如果 $A + R \lt M$，则令 $M = A + R$。这样就可以在可以操作 $M$ 也可以用 $A,R$ 时，先操作 $M$。

首先砖堆的顺序没有影响，所以可以将 $h$ 进行排序。

考虑枚举最终的高度 $H$，看看当 $H$ 增大 $1$ 时，答案会有什么变化。设目前比 $H$ 低的砖堆总共需要添加 $u_1$ 块砖，比 $H$ 高的砖堆总共需要渐少 $v_1$ 块砖。变化后需要添加 $u_2$ 块砖，减少 $v_2$ 块砖。不妨设变化前后都满足 $u \leq v$。

对于变化前，因为先用操作三不会更劣，所以花费为 

$$c_1 = u_1M + (v_1 - u_1)R$$​

同理，变化后的花费为 

$$c_2 = u_2M + (v_2 - u_2)R$$

考虑 $u$ 与 $v$ 的变化。设变化前共有 $w$ 堆石子的数量**不大于**（而不是小于）$H$，那么变化后这 $w$ 堆石子的高度一定小于 $H + 1$，剩下的石子高度一定不低于 $H + 1$，因此 $u$ 增大了 $w$，即

$$u_2 = u_1 + w$$

同理，共有 $(n - w)$ 堆石子的高度严格大于 $H$，变化后这些需求都减掉了 $1$，因此

$$v_2 = v_1 - (n - w) = v_1 + w - n$$

把 $u2$ 和 $v2$ 的表达式带回 $c_2$，得到

$$\begin{aligned}c_2 &= u_2M + (v_2 - u_2)R \\ &= (u_1 + w)M + (v_1 + w - n - u_1 - w)R \\ &= u_1M + wM + (v_1 - u_1)R - nR \\ &= c_1 + wM - nR\end{aligned}$$

那么花费差为 $c_2 - c_1 = wM - nR$。

注意到 $nR$ 和 $M$ 都是常数。因此花费差只取决于 $w$ 的取值。而当我们的 $H$ 不在任何一个 $h_i$ 附近（这里附近指的是相差不超过 $1$）时，当 $H$ 增大时，$w$ 不会产生改变，换句话说，此时当 $H$ 增大 $1$，$c_2 - c_1$ 是一个不变量。因此当 $H$ 不在任何一个 $h_i$ 附近时，高度与花费是一个线性关系。而在一次函数截取一个线段，其最值只会在两端点处取到。因此这种情况下最值只可能在 $h_i - 1$ 与 $h_i + 1$ 处取到。分别对这两个高度求对应花费即可。

当变化前后都满足 $u > v$ 时同理可以得到 $c_2 - c_1 = An + M(w - n)$。同样不在 $h_i$ 附近时，花费与高度是线性关系，因此同样也在 $h_i - 1$ 与 $h_i + 1$ 处求花费即可。

p.s. 两种情况的式子推出来好像差异比较大，我不清楚我推错没有，检查了一遍大概没问题，推错了请告诉我。

使 $w$ 变化的只有这 $n$ 个高度，对于这 $n$ 个高度，还需要再求一次花费。

注意到上面的讨论都是针对变化前后 $u, v$ 大小关系不变的情况。当 $H$ 增大时，$u$ 单调不降，$v$ 单调不升。因此二者只在某一个高度会从 $u \leq v$ 变成 $u \gt v$。这个位置显然是可以二分的。我们二分求出这个位置，再求出这个位置附近的花费，全局最小值只会从上述几个位置取到，对于上述花费取最小值即可。

时间复杂度 $O(n \log^2n)$。这里多了一个 $\log n$ 是因为我实现二分时 `check` 需要一个 $\log n$ 的复杂度，如果希望理性愉悦，可以先二分出变化位置位于哪两个 $h$ 之间，再在范围内二分，这样可以做到一个 $\log n$。

### Code

```cpp
namespace Fusu {

const int maxn = 100005;

int n, x, y, z;
ll ans = 1ll << 62;
ll a[maxn], b[maxn];

ll calc(const ll h);
bool check(const ll h);

void Main() {
  qr(n); qr(x); qr(y); qr(z);
  qra(a + 1, n);
  if (z > (x + y)) z = x + y;
  std::sort(a + 1, a + 1 + n);
  for (int i = 2; i <= n; ++i) {
    b[i] = a[i];
    a[i] += a[i - 1];
  }
  b[1] = a[1];
  for (int i = 1; i <= n; ++i) {
    ans = std::min({ans, calc(b[i]), calc(b[i] - 1), calc(b[i] + 1)});
  }
  ll p = a[n];
  for (ll l = 0, r = b[n], mid = (l + r) >> 1; l <= r; mid = (l + r) >> 1) if (check(mid)) {
    l = (p = mid) + 1;
  } else {
    r = mid - 1;
  }
  ans = std::min({ans, calc(p), calc(p - 1), calc(p + 1)});
  qw(ans, '\n');
}

inline bool check(const ll h) {
  int i = std::lower_bound(b + 1, b + 1 + n, h) - b - 1;
  ll u = a[i], v = a[n] - a[i];
  u = h * i - u; v = v - (h * (n - i));
  return u <= v;
}

ll calc(const ll h) {
  if (h > b[n]) return 1ll << 62;
  if (h < b[1]) return 1ll << 62;
  int i = std::lower_bound(b + 1, b + 1 + n, h) - b - 1;
  ll u = a[i], v = a[n] - a[i];
  u = h * i - u; v = v - (h * (n - i));
  ll ta = 0, t = std::min(u, v);
  ta = t * z;
  ta += (u - t) * x + (v - t) * y;
  return ta;
}

} // namespace Fusu
```



---

## 作者：7KByte (赞：3)

前面题解的思路已经很清楚了，但这里提供一个更便捷的实现方式。

三分×，二分√。

虽然我们不能微分，但是可以把单位长度$1$看为最小的，即$\Delta x$。

这样我们就可以求导二分。

```check(x)```函数直接返回函数在$x$处的切线斜率正负。

这样我们就优美的实现了三分。直接全局二分，不需要再对每个$h$做一遍。

这样我们的代码就非常简洁，时间复杂度$\rm O(N\ log\ N)$

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 100005
#define int long long
using namespace std;
int n,X,Y,Z,a[N];
int calc(int x){
	int l=0,ls=0,r=0,rs=0;
	rep(i,1,n)if(a[i]>x)r++,rs+=a[i];else l++,ls+=a[i];
	l=x*l-ls;r=rs-x*r;
	int res=min(l,r);
	return min(l*X+r*Y,res*Z+(l-res)*X+(r-res)*Y);
}
bool check(int x){
	return calc(x)<calc(x+1);
}
void solve(){
	scanf("%lld%lld%lld%lld",&n,&X,&Y,&Z);
	rep(i,1,n)scanf("%lld",&a[i]);
	int l=1,r=1e9,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%lld\n",min(calc(ans),min(calc(ans-1),calc(ans+1))));
}
signed main(){
	solve();
}
```

---

## 作者：Starlight_Glimmer (赞：2)

[My Blog](https://www.cnblogs.com/lyttt/p/14077102.html)

[题目链接](https://codeforces.com/problemset/problem/1355/E)

### 题目解析

~~好萎靡呀，又是除了我全场都会系列~~

~~为啥要思维定势死磕dp咧（主要是想到了一个类似的题用dp做的 但其实完全不一样啊~~

~~讲个笑话：我看出来了长得像二次函数，但是没想到三（啊 我写的san 好像跟删除线叠了）分~~

------

首先，如果固定一个所有砖块最后的高度$h$，我们可以在$O(n)$复杂度内算出需要的代价。

具体来说，如果$M>=R+A$，那操作三就不用。否则，我们扫一遍可以知道每块砖变成目标值需要多少次操作一/操作二，把操作一和操作二尽量配对成操作三，剩下的单独操作就可以了。（当然，在写法上，可以直接把$M=min(M,R+A)$，然后直接算，不判断（押个韵

然后，我们就得到了一个$range_h\times n$的零分优秀算法。

------

稍微优秀一点，可以将初始高度排序，然后预处理一下前缀和，每次就可以$O(1)$得出一个$h$的代价。

这个时候我们盲猜：如果$M$比较大（具体指$M>=R+A$），也就是不用操作三，那么操作一和操作二的个数没有影响（这个意思是说，不需要尽量让操作一和操作二的数量平均然后去凑更多的操作三，如果操作三更优的话，说不定可以改变一下$h$，凑更多的操作三出来，结果更优），所以最终的这个$h$一定是初始的$n$个之一；但如果$M$比较小，就不一定了。但是我们考虑到要尽量凑操作三出来，所以最后的$h$会落在平均数的附近，枚一枚就好喏。

然后，结合前面的预处理，我们就得到了一个看起来不太靠谱，但实际上可以满分的$O(n)$优秀算法。

------

最后，说一下我是怎么觉得它是一个类似于二次函数的东西的呢？

**感性理解**：

之前相当于是我们把操作三变成了操作一和操作二，你贪心地想，如果操作一代价大于操作二代价，那$h$要选小一点，否则选大一点，但是选太小或者太大也不太行的样子。因为操作数变多了，加起来可能反而不优。举个例子，假如是操作一代价大于操作二代价，而我如果把$h$选很小，我每把$h$减小$1$，右边的数需要更多的操作二，左边的数需要更小的操作一，但是右边的数比左边的数要多，加起来的总代价可能还不如我右边少几次操作二，左边多几次操作一来得好。（更何况还有操作一和操作二数量更接近凑更多操作三出来使答案更优的情况）而这玩意儿就很像初中的二次函数应用题，提高价格顾客变少的那种问题，总括来说就是：$y$是$x$的一次函数，总收益/代价是$W=xy$可能再加减乘除个常数什么的，不过那不重要，重要的是$W$最终是$x$的二次函数。

**理性理解**：

设最终的高度为$h$，需要增加$a$次，减少$b$次，我们和$h+1$比较（求个斜率什么的），就可以知道增减情况和变化率。设$h$变为$h+1$时的操作一的变化量为$x$，则新的$a'=a+x$，而$x$为所有砖块中高度小于等于$h$的砖块的个数，那么操作二的变化量为$n-x$,则$b'=b-(n-x)=b+x-n$

1. $a<b$时：$W=a\times M+(b-a)\times R$，$W'=(a+x)\times M+(b-a-n)\times R，delta=xM+(x-n)R=xM-nR$（分母除以$(h+1-h)$就是斜率，所以这玩意儿就是斜率，或者说导数）
2. $a>b$时：$W=b\times M+(a-b)\times A$,$W'=(b+x-n)M+(a-b+n)A，delta=(x-n)M+nA=xM-nM+nA$

那么关于$h$的函数$W$的斜率是一个一次函数（说准确点是分段函数），$x$是随$h$的增大而增大的分段函数。而且斜率逐渐变大，（先负后正，刚开始$x$很小的时候，$xM<nR$）的一次函数，所以应该是类似于开口朝上的二次函数，不过因为$x$是整数，并且它关于$h$不是连续变化的，所以斜率也不是连续变化的，而是在一段区间内斜率一样，那么$W$就是一个下凸包（是一截一截的，而不是二次函数那样比较光滑的曲线）。

但是由于我对三分这个算法太不熟悉了，所以并没有想到它嘤嘤嘤。

事实上，我们之前说了斜率是一次函数，那么可以还对斜率进行二分。实际上，三分和二分斜率是等价的，因为单峰函数的斜率是单调的，并且在最值斜率为$0$。

然后，你就得到了一个看以来要靠谱一些的满分做法。

（我是不是跟分治有仇啊$qwq$ 儒略历那道题用二分要简单多了 但我就是没有想到二分 然后直接计算模拟硬刚 最后惨挂$60pts\ qwq$

------

### ►Code View

```cpp
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;
#define N 100005
#define M 200005
#define MOD 998244353
#define INF 0x3f3f3f3f3f3f3f3f
#define LL long long
LL rd()
{
	LL x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1; c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48); c=getchar();}
	return f*x;
}
int n;
LL a,r,m,h[N],ans=INF;
LL opt1,opt2;
void calc(int i,int j)
{
	if(h[i]==j) return ;
	if(h[i]<j) opt1+=j-h[i];
	else opt2+=h[i]-j;
}
LL work()
{
	if(m<a+r)
	{
		LL k=min(opt1,opt2),res=0;
		res=k*m,opt1-=k,opt2-=k;
		if(opt1) res+=opt1*a;
		if(opt2) res+=opt2*r;
		return res;
	}
	else return opt1*a+opt2*r;
}
LL f(LL het)
{
	opt1=opt2=0; 
	for(int i=1;i<=n;i++)
		calc(i,het);
	return work();
}
int main()
{
	//freopen("bricks.in","r",stdin);
	//freopen("bricks.out","w",stdout);
	n=rd(),a=rd(),r=rd(),m=rd();
	for(int i=1;i<=n;i++)
		h[i]=rd();
	sort(h+1,h+n+1);
	int l=h[1],r=h[n];
	while(l+10<r)
	{
		int lmid=l+(r-l)/3,rmid=r-(r-l)/3;
		LL lans=f(lmid),rans=f(rmid);
		if(lans>rans) l=lmid;
		else r=rmid;
	}
	LL ans=INF;
	for(int i=l;i<=r;i++)
		ans=min(ans,f(i));
	printf("%lld\n",ans);
	return 0;
}
/*
3 100 100 1 
1 3 8
*/
```

---

## 作者：zhou_ziyi (赞：2)

### 思路
好像还没有人写三分，那我就来水一篇三分的题解。
我们可以选择三分平均高度，通过 `check` 函数得到对应的最小代价，我将在代码中给出详细的注释。
### Code
```cpp
#include <cstdio>
#include <iostream>
#define int long long
using namespace std;
const int MAXN = 1e5 + 5, INF = 1e9;
int n, A, R, M;
int a[MAXN];
int l = -INF, r = INF; //左端点和右端点的初始化
int check(int x) {//贪心
	int s1 = 0, s2 = 0, ans = 0;
	for (int i = 1; i <= n; i++)//求得总共需要加多少砖，减多少砖
		if (a[i] >= x) 
			s1 += a[i] - x;
		else
			s2 += x - a[i];//其实也可以用绝对值
	int m = min(s1, s2);
	ans += m * M, s1 -= m, s2 -= m;使用操作三
	if (s1)
		ans += s1 * R;操作2
	if (s2)
		ans += s2 * A;操作3
	return ans;得到进行多次操作后达到高度x的代价
}
signed main() {
	scanf("%lld %lld %lld %lld", &n, &A, &R, &M);
	M = min(M, A + R); //操作3的代价大于1和2的和，那就用这个和更新操作3的代价
	for (int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	while (l + 2 < r) { //三分的板子
		int m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
		if (check(m1) < check(m2)) 
			r = m2;
		else
			l = m1;
	}
	printf("%lld", check(l + r >> 1)); //玄学输出
	return 0;
}
```

---

## 作者：IRipple (赞：2)

**模拟退火大法好**

众所周知，模拟退火算法可以使用$O(?)$的复杂度解决多峰函数最值的问题。因此这个题目依然可以使用模拟退火来解决。

不会这个算法的同学建议先去学习一下[模拟退火算法入门](http://i-ripple.xyz/%e6%a8%a1%e6%8b%9f%e9%80%80%e7%81%ab%e7%ae%97%e6%b3%95%e5%85%a5%e9%97%a8/)，已经会的同学听我细细道来。

## 一、预处理

首先，我们需要进行预处理，降低退火过程中产生新解的复杂度。

对于输入的墙的高度$a[i]$我们可以先进行排序，并且求出前缀和$sum[i]$。
```cpp
for(int i=1;i<=n;i++){
	cin>>a[i];
}
sort(a+1,a+n+1);
for(int i=1;i<=n;i++){
	sum[i]=sum[i-1]+a[i];
}
```
当我们每次产生一个新的砖块高度 $x$ 时，我们需要快速计算出所需的代价。这时，我们可以先对排序过的$a[i]$二分查找新的高度 $pos$。

在这个新高度之前的墙需要抬高的总高度= $x*pos-sum[pos]$ 

在这个新高度之后的墙需要降低的总高度= $(sum[n]-sum[pos])-x*(n-pos)$

之后，如果$M>A+R$ 那么我们只使用前两种操作；如果$M≤A+R$那么我们先尽可能进行$M$操作余下的分别计算。
```cpp
int cal(int x){//假定墙的高度为x
	fans=0;//fans代表总共花费的代价
	pos=lower_bound(a+1,a+n+1,x)-a;//二分查找抬高与下降的平衡点
	pos--;
	xx=abs(x*pos-sum[pos]);
	yy=abs((sum[n]-sum[pos])-x*(n-pos));//计算抬高高度和下降高度
	if(M>A+R){//不使用M操作
		fans=A*xx+R*yy;
	}
	else{//优先使用M操作
		fans=min(xx,yy)*M;
		if(xx>yy){
			fans+=A*(xx-yy);
		}
		else{
			fans+=R*(yy-xx);
		}
	}
	return fans;
}
```
综上，我们优化单次计算约为$O(log n)$级别的时间复杂度，这为进行尽可能多次的模拟退火提供了充裕的时间。
## 二、模拟退火
通过 随机数×温度 产生一个新的最终墙面高度，如果该高度对应的答案严格小于已有答案，则采用之；反之，则以一定概率接受非最优解

```cpp
void SA(){
	double T=1926087;//初始温度
	int x=0;//最终墙面高度
	while(T>1e-14){
		int new_x=x-(rand()*2-RAND_MAX)*T;//给出一个新的墙面高度
		if(new_x<0) continue;//注意，墙面高度不可以是负数
		int new_ans=cal(new_x);//计算开销
		int dE=new_ans-ans;
		if(dE<0){//优于已有解，接受之
			x=new_x;
			ans=new_ans;
		}
		else if(exp(-dE/T)*RAND_MAX>rand()){//一定概率接受非最优解
			x=new_x;
		}
		T*=0.99993;//降温系数
	}
}
```
关于参数问题，引用一下M_sea在洛谷日报的叙述：
> Q：答案不是最优的怎么办？

> A：有以下几种方法：调大 $\Delta$、调整 $T_0$和 $T_k$，以及多跑几遍SA。

> 当您的程序跑的比较快时，可以选择多跑几遍SA，或者调大 $\Delta$，从而增大得到最优解的概率。

> $T_0$和 $T_k$的值需要根据值域对应调整，从而保证每次随机出的变化幅度不会跑太远。

> Q：还是跑不出最优解怎么办？

> A：那可能是您太非了。尝试更换随机数种子，或者 $srand(rand())$，总之，总有可能跑出正解。

> Q：我是非酋，交了两页也没有用模拟退火AC，怎么办？

> A：~~您还是选择打正解吧。~~

完整代码如下：
```cpp
//XCPC RP++
#include<bits/stdc++.h>
#define int long long//注意开long long
using namespace std;
int n,A,R,M;
int a[100100],sum[100100];
int pos;
int xx,yy;
int fans;
int ans=1e18;
int cal(int x){
	fans=0;
	pos=lower_bound(a+1,a+n+1,x)-a;
	pos--;
	xx=abs(x*pos-sum[pos]);
	yy=abs((sum[n]-sum[pos])-x*(n-pos));
	if(M>A+R){
		fans=A*xx+R*yy;
	}
	else{
		fans=min(xx,yy)*M;
		if(xx>yy){
			fans+=A*(xx-yy);
		}
		else{
			fans+=R*(yy-xx);
		}
	}
	return fans;
}
void SA(){
	double T=1926087;
	int x=0;
	while(T>1e-14){
		int new_x=x-(rand()*2-RAND_MAX)*T;
		if(new_x<0) continue;
		int new_ans=cal(new_x);
		int dE=new_ans-ans;
		if(dE<0){
			x=new_x;
			ans=new_ans;
		}
		else if(exp(-dE/T)*RAND_MAX>rand()){
			x=new_x;
		}
		T*=0.99993;
	}
}
signed main(){
	srand(time(0));
	cin>>n>>A>>R>>M;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1]+a[i];
	}
	SA();
	SA();
	SA();
	cout<<ans<<endl;
	return 0;
}
```





---

