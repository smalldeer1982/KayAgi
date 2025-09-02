# [IOI 2011] ricehub

## 题目描述

乡间有一条笔直而长的路称为“米道”。沿着这条米道上$R$  块稻田，每块稻田的坐标均为一个 $1$ 到 $L$ 之间(含 $1$ 和 $L$ )的整数。这些稻田按照坐标以不减的顺序给出，即对于 $0 \le i < R$，稻田 $i$ 的坐标 $X[i]$ 满足 $1 \le X[0] \le \cdots \le X[R-1] \le L$。

注意：可能有多块稻田位于同一个坐标上。

我们计划建造一个米仓用于储存尽可能多的稻米。和稻田一样，米仓将建在米道上，其坐标也是一个 $1$ 到 $L$ 之间的整数（含 $1$ 和 $L$）。这个米仓可以建在满足上述条件的任一个位置上，包括那些原来已有一个或多个稻田存在的位置。

在收获季节，每一块稻田刚好出产一滿货车的稻米。为了将这些稻米运到米仓，需要雇用一位货车司机来运米。司机的收费是每一满货车运送一个单位的距离收取 $1$ 元。換言之，将稻米从特定的稻田运到米仓的费用在数值上等于稻田坐标与米仓坐标之差的绝对值。

不幸的是，今年预算有限，我们至多只能花费 $B$ 元运费。你的任务是要帮我们找出一个建造米仓的位置，可以收集到尽可能多的稻米。

## 说明/提示

对于 $100\%$ 的数据，$1 \le R \le 10^5$，$1 \le L \le 10^9$，$ 0 \le B \le 2 \times 10^{15}$。

## 样例 #1

### 输入

```
5 20 6
1
2
10
12
14```

### 输出

```
3```

# 题解

## 作者：Jameswood (赞：13)

## 题目大意

在一个数轴上，有给定数量和位置的点（可以重合，位置恒正且为整数）。你的任务是选取其中的一个点作为比较点。之后在给出的点中选择一部分，使得选择的点的总数尽可能大，且它们到你所选择的比较点的距离之和（费用）小于等于题目给出的上限 $B$。你需要输出可选择点的总数的最大值（收获的农田数目的最大值）。

---

## 阅前必读

事先声明：
1. 本篇题解偏新手向，大佬们只需阅读概要部分即可。

2. 作者是一只菜菜的木头酱，如有异议/错误欢迎提出/指出 QAQ 。


本篇题解提供以下三种做法：
1. 暴力模拟【都会做吧……先不讲了，有需要下方留言，看到会更新的】
2. 前缀和+二分答案【时间复杂度 $O(nlogn)$】 【正解】
3. 前缀和+双向指针【时间复杂度 $O(n)$】 【理论最优解】

前置数学知识：[绝对值不等式](https://www.luogu.com.cn/paste/4m8tzxcf) 、 [绝对值的几何意义](https://www.luogu.com.cn/paste/yg0h8dls)

综合难度评定：普及＋/提高 中较难的一类，如果真的要思考的很透彻的话个人认为可以够到一点点省选难度（绝对值不等式【中位数】 + 前缀和 + 二分答案 + 原题面英文理解困难）

---

## 详细解答

本题的关键在于**如何快速地在选择两个给定点后计算出这一区间内所有给定点到区间内任一比较点距离之和的最小时的花费**。这里将运用[绝对值不等式](https://www.luogu.com.cn/paste/4m8tzxcf)进行说明。（链接内提供说明和证明）

对于已经确定的某一区间，设其中包含的给定点为 $a_1,a_2, $ ... $, a_{m-1},a_m$ （ 其中 $a_1\leq a_2 \leq ... \leq a_{m-1} \leq a_m$ ）

那么对于选中的比较点 $a_k$ （$1\leq k \leq m$） 。其距离之和（总花费）可以表示为 $\vert a_k-a_1\vert+\vert a_k-a_2 \vert + ... + \vert a_{m-1}-a_k \vert + \vert a_m - a_k\vert$ （参考：[绝对值的几何意义](https://www.luogu.com.cn/paste/yg0h8dls)）

当 $m$ 为偶数时，我们对其从首尾开始两两分组，即：

$(\vert a_k-a_1\vert+\vert a_m-a_k \vert) + ... + ( \vert a_k-a_{\frac{m}{2}} \vert + \vert a_{\frac{m}{2}+1} - a_k\vert)$  ①

接下来对每一组使用绝对值不等式，可以得到：

① $ \geq( a_m-a_1 ) + ( a_{m-1}-a_2 ) ... + (  a_{\frac{m}{2}+1} - a_{\frac{m}{2}} )$ 

等号当且仅当在 $(a_k-a_{\frac{m}{2}}) \times (a_{\frac{m}{2}+1} - a_k)\geq0$ ，即$a_{\frac{m}{2}}\leq a_k \leq a_{\frac{m}{2}+1}$时成立

（注：当发现无法把某一组中的 $a_k$ 消掉时说明你没有理解绝对值不等式的真正含义，解决方法可以简单地把其中一个在绝对值符号内乘以负一）

当 $m$ 为奇数时，我们可以把第 m/2+1 项单独提出，之后就能进行类似的操作，得到 总费用 $ \geq( a_m-a_1 ) + ( a_{m-1}-a_2 ) ... + (  a_{m/2+2} - a_{m/2} )$  ，注意需要将取等条件修改为 $a_k=a_{m/2+1}$ 即可。

$\color{red}\colorbox{#f8f8f9}{综上所述}$，我们可以得到：在选定的以两个给定点 $a_1$ 、$a_m$ 为端点的闭区间内，当比较点 $a_k = a_{m/2+1}$ 时，给定点的数目将会取到最大值，其值如上述。只需要对给定点的坐标之和使用[**前缀和维护**](https://www.luogu.com.cn/paste/664z5z95)，即可做到 $O(n)$ 查询（注：我认为如果到此步各位没有理解困难的话应该可以推出利用前缀和快速求区间费用的通式QAQ，没什么想法的先把 ① 再读一边，然后还不行就点链接，有详细说明）。

接下来我们开始寻找符合要求的区间，如果只求通过的话，可以运用二分思想。依次从 $x_1$ 开始一直遍历到 $x_R$ 查找区间的左端点，之后二分查找每一个左端点 $x_i$ 对应的右端点 $x_j$ 使得收获的农田最多。

代码如下：

```cpp
#include<cstdio>
#include<cstdlib>
using namespace std;
const int SIZE=1e5+5;
long long R,L,B,ans,mid;
long long x[SIZE],sum[SIZE];
inline long long max(long long a,long long b){
	if(a>b) return a;
	else return b;
}
long long check(long long l,long long r){
	mid=l+r>>1;
	return x[mid]*(mid*2-l-r)+sum[l-1]+sum[r]-sum[mid]-sum[mid-1];
}
int main(){
	scanf("%lld%lld%lld",&R,&L,&B);
	for(long long i=1;i<=R;i++){
		scanf("%lld",&x[i]);
		sum[i]=sum[i-1]+x[i];
	}
	long long l,r,mid,k;
	for(long long i=1;i<=R;i++){
		l=i;r=R;
		while(l<=r){
			mid=l+r>>1;
			if(check(i,mid)<=B){
				l=mid+1;k=mid;
			}
			else r=mid-1;
		}
		ans=max(ans,k-i+1);
	}
	printf("%lld",ans);
	return 0;
}
```

附[通过记录](https://www.luogu.com.cn/record/40865413)

而对于双向指针，其思想也相当简单。初始时选定区间 $[x[1],x[1]]$（此时花费为0，肯定满足要求）。 接下来把第二个 $x[1]$ 的下标右移，每右移一次判断一次。当总花费超过 $B$ 时则将第一个 $x[1]$ 的下标右移一，然后再判断总花费是否满足要求，是则右移右端点，否则右移左端点，以此类推，得到结果。（其正确性基于输入的 $x_i$ 单调递增，故右端点不需要在左端点右移后左移）

```cpp
#include<cstdio>
#include<cstdlib>
using namespace std;
const int SIZE=1e5+5;
long long R,L,B,ans,mid;
long long x[SIZE],sum[SIZE];
inline long long max(long long a,long long b){
	if(a>b) return a;
	else return b;
}
long long check(long long l,long long r){
	mid=l+r>>1;
	return x[mid]*(mid*2-l-r)+sum[l-1]+sum[r]-sum[mid]-sum[mid-1];
}
int main(){
	scanf("%lld%lld%lld",&R,&L,&B);
	for(long long i=1;i<=R;i++){
		scanf("%lld",&x[i]);
		sum[i]=sum[i-1]+x[i];
	}
	for(long long l=1,r=1;l<=R;l++){
		while(r<R&&check(l,r+1)<=B) ++r;
		//此处r忽略了 [x[1],x[1]] 的区间，并以 r+1 和 r<R作为判断依据
		//是为了便于计算ans
		ans=max(ans,r-l+1);
	}
	printf("%lld",ans);
	return 0;
}
```

附[通过记录](https://www.luogu.com.cn/record/40865445)

代码中与详解不同的部分已用注释阐明。本题的重难点其实是在 check 函数里，请各位小心，不要错估其难度所在。

最后：如有疑问欢迎提出，木头酱看到后会回复在评论区。

以上，希望这篇题解能够帮到泥们QWQ

---

## 作者：CYZZ (赞：6)

**[题目传送门](https://www.luogu.com.cn/problem/P5844)**
# 题意简明

在数轴上有 $R$ 个整点（可重叠）。现在我们要选取其中的一个点作为中心点，并在其余点中选若干个。满足中心点到其余点的距离之和小于等于 $B$。且使选出的点的数量尽量多。输出这个最大值。

# 思路分析

第一眼看到这个题我想到了一个简单的数学结论（此处不作证明）：

数轴上有 $n$ 个点，坐标分别为 $ x_1,x_2,\ldots ,x_n $，且 $ x_1 \le x_2 \le \ldots \le x_n $。任取一点 $ k $ 使得该点到其余点的距离之和，即 $\sum\limits_{i=1}^n\left\vert x_i-x_k\right\vert$ 最小。则有
$ \begin{cases}
x_k=x_\frac{1+n}{2} & n \equiv 1 \pmod 2\\
x_k \in \left[x_\frac{n}{2},x_\frac{n}{2}+1\right] & n \equiv 0 \pmod 2\\
\end{cases} $。

此时，$sum_\text{min}=\sum\limits_{i=1}^n\left\vert x_i-x_k\right\vert=\sum\limits_{i=1}^{\left\lfloor\frac{n}{2}\right\rfloor} \left\vert x_i-x_{n-i}\right\vert$，取到最小值。

根据以上结论，我们不难发现：在区间 $ \left[x_l,x_r\right] $ 内，取中间点 $x_k=x_{\frac{l+r}{2}}$时，$ sum$ 值最小。此时 $ sum= \sum\limits_{i=l}^{\left\lfloor\frac{l+r}{2}\right\rfloor}  \left\vert x_i-x_{n-i}\right\vert=(x_r+x_{r-1}+\cdots+x_{\left\lfloor\frac{l+r}{2}\right\rfloor+1})-(x_l+x_{l+1}+\cdots+x_{\left\lfloor\frac{l+r}{2}\right\rfloor}) $，考虑使用前缀和维护区间坐标之和。具体代码实现如下：
```cpp
bool check(ll l,ll r)
{
    ll mid=(l+r)/2;
    return ((sum[r]-sum[mid])-(sum[mid-1]-sum[l-1])-a[mid]*((r-l)&1))<=v;//代码核心 
    //若r-l+1为偶数，即r-l为奇数时，少减了a[mid]。 
}
```
这里给出双指针的代码：左右指针 $ i,j $ 初值为 $ 1,0 $，左指针每次向右移动一格，然后右指针不断往右移。若 $\left[x_i,x_j\right]$ 求出的 $ sum_\text{min} \le B$，则取该区间的所有点满足条件。直到找到符合条件的最大 $j$，更新答案。最后注意一下要开 $\text{long long}$ 的问题即可。
# 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll n,m,v,a[100005],sum[100005],ans=-1;
bool check(ll l,ll r)
{
    ll mid=(l+r)/2;
    return ((sum[r]-sum[mid])-(sum[mid-1]-sum[l-1])-a[mid]*((r-l)&1))<=v;//代码核心 
    //若r-l+1为偶数，即r-l为奇数时，少减了a[mid]。 
}
int main()
{
    scanf("%lld%lld%lld",&n,&m,&v);
    for(ll i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
        sum[i]=sum[i-1]+a[i];
    }
    for(ll l=1,r=0;l<=n;l++)
    {
        while(r<n&&check(l,r+1))
            r++;
        ans=max(ans,r-l+1);
    }
    printf("%lld",ans);
    return 0;
}
```
 希望本篇题解可以帮到大家！！！

---

## 作者：zhangjiting (赞：3)

## 题目大意
在数轴上有 $R$ 个整点（可重叠）。现在我们要选取其中的一个点作为中心点，并在其余点中选若干个。满足中心点到其余点的距离之和小于等于 $B$。且使选出的点的数量尽量多。输出这个最大值。
## 二分答案
有一个结论 $1 \sim len$ 最好的米仓选址肯定是 $len \div 2$。

当选址 $pos$ 移到 $poss=pos+1$ 时
 $tot$ 相对于原来有如下变化，假设 $l \sim i$ 长度为 $len$，$i=len+1 \sim n$，显然 $l=i-len+1$。
 
```tot-=a[poss-(len&1)]-a[l-1]```

```tot+=a[i]-a[poss]```

这个变化是通过奇偶分类讨论得到，可以画一下。然后就可以 $O(n)$ 判断是否有 $\le B$ 的方案。

## 代码如下
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 1000005;

int n,m,b,a[N],s[N];

int check(int l,int r)
{
    int mid=(l+r)/2;
    return s[r]-s[mid]-(r-mid)*a[mid]-s[mid]+s[l-1]+(mid-l+1)*a[mid];
}

signed main()
{
    cin>>n>>m>>b;
    for(int i=1;i<=n;i++) cin>>a[i], s[i]=s[i-1]+a[i];
    int j=1,ans=0;
    for(int i=1;i<=n;i++)
    {
        while(j<n && check(i,j+1)<=b) ++j;
        if(check(i,j)<=b) ans=max(ans,j-i+1);
    }
    cout<<ans<<endl;
    return 0;
}

```


---

## 作者：ni_ju_ge (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P5844)
## 思路
可以想到七上的一个数学知识：有 $n$ 个数 $a_{1\sim n}$（设序列 $a$ 单调递增），若要求一个数 $k$ 使得 $k$ 与所有 $a_i$ 的差的绝对值最小，那么：
 - 若 $a\bmod 2=0$，$k=a_{\frac{n}{2}}\sim a_{\frac{n}{2}+1}$；
 - 若 $a\bmod 2=1$，$k=a_{\frac{n+1}{2}}$。

这个结论很好证，这里就留给读者练习了。

这题显然可以用到这个结论，考虑求出 $k$（即粮仓坐标），然后用 $\ge k$ 的稻田坐标减去 $\le k$ 的稻田坐标，就可以得到这些稻田到粮仓距离之和了。

可以使用前缀和维护稻田坐标之和，然后使用双指针，一个代表区间左端点编号，另一个代表右端点编号，计算区间内稻田到粮仓距离最小和并判断是否超过 $B$，最后更新答案即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[114514],s[114514],b,r;
int n,z,ans;
long long lsum(int x,int y) {//计算距离最小和
	int mid=(x+y)/2;
	long long su=(s[y]-s[mid])-(s[mid-1]-s[x-1]);
	if((y-x)%2==1) su-=a[mid];//若y-x为奇数就少减了一个a[mid]
	return su;
}
int main() {
	cin>>n>>z>>b;
	for(int i=1;i<=n;i++) {
		cin>>a[i];
		s[i]=s[i-1]+a[i];//前缀和
	}
	int l=1,r=0;
	while(l<=n) {
		while(r<n&&lsum(l,r+1)<=b) {//更新右端点
			r++;
		}
		ans=max(ans,r-l+1);//更新答案
		l++;//更新左端点
	}
	cout<<ans;
}
```

---

## 作者：zong15632539rongjuan (赞：1)

#### 题意
有 $R$ 个点，每个点的位置是 $X_i$，在 $L$ 以内的位置选一个总点，选择其他点与总点的距离不超过 $B$，求最多选择点的数量。
#### 题目分析
##### 主要思路
###### 算法
- 前缀和。
- 二分答案。
###### 时间复杂
时间复杂度为 $O(R+R\times\log{R})$。
###### 过程分析
可以参考来源 Jameswood 的云剪贴板[绝对值不等式](https://www.luogu.com/paste/4m8tzxcf)。  
中位数：$X_{(l-r+1)\div2}$。
- 求一个区间内所有的点距离某一个点的值的和。
  - $(l-r+1)$ 是偶数：$|X_{mid}-X_l|+|X_{mid}-X_{l+1}|+……+|X_{mid}-X_{r}|=(|X_{mid}-X_l|+|X_r-X_{mid}|)+(|X_{mid}-X_{l+1}|+|X_{r-1}-X_{mid}|)+……+(|X_{mid}-X_{(l+r)\div2}|+|X_{(l+r )\div2+1}-X_{mid}|)\ge|X_{mid}-X_l+X_r-X_{mid}|+|X_{mid}-X_{l+1}+X_{r-1}-X_{mid}|+……+|X_{mid}-X_{(l+r)\div2}+X_{(l+r )\div2+1}-X_{mid}|=(X_r - X_l)+(X_{r-1}-X_{l+1})+……+(X_{(l+r)\div2+1}-X_{(l+r)\div2})=(X_r+X_{r-1}+……+X_{(l+r)\div2+1})-(X_l+X_{l+1}+X_{(l+r)\div2})$。
  - $(l-r+1)$ 是奇数，同偶数思路，取出中位数：$(X_r+X_{r-1}+……+X_{(l+r)\div2+2})-(X_l+X_{l+1}+X_{(l+r)\div2})$。
  - 消除奇偶：$2\times mid-l-r$。  
  - 所以，$sum=\sum_{i=mid+1}^{r} X_i-\sum_{i=l}^{mid-1} X_i+X_{mid}\times(2\times mid-l-r)$。
#### 详细解法
1. 赋值。
2. 求 $X$ 数组前缀和。
3. 枚举左端点，二分答案右端点，答案取最长区间。
4. 输出最多稻米数。
#### 代码
```
#include <cstdio>
#define ll long long
using namespace std;
const int max_R = 110000;
int R, L, X[max_R], l, r, my_ll, rr, QAQ;
ll B, ans, ps[max_R];
bool check(ll mid) {
    return ps[rr] - ps[mid] - ps[mid - 1] + ps[my_ll - 1] 
        + (ll)X[mid] * 2 * mid - (ll)X[mid] * my_ll 
        - (ll)X[mid] * rr <= B;
}
int main() {
    scanf("%d%d%lld", &R, &L, &B);
    for (int i = 1; i <= R; ++i) scanf("%d", &X[i]);
    ps[1] = X[1];
    for (int i = 2; i <= R; ++i) 
        ps[i] = ps[i - 1] + (long long)X[i];
    for (int i = 1; i <= R; ++i) {
        l = i;
        r = R;
        while (l <= r) {
            int mid = (l + r) >> 1;
            my_ll = i;
            rr = mid;
            if (check((i + mid) / 2) == true) {
                l = mid + 1;
                QAQ = mid;
            } else
                r = mid - 1;
        }
        if (QAQ - i + 1 > ans)
            ans = QAQ - i + 1;
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：alex_liu (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P5844)

## 分析

首先贪心想到对于一个区间，将谷仓建在中位数最优。

求最大收集稻米数，考虑二分稻米数，枚举左端点，此时时间复杂度已为 $O(n\log n)$，需要 $O(1)$ 计算贡献。

先前缀和预处理前 $i$ 个坐标和 $sum_i$，设当前区间左右端点为 $l,r$，则考虑将区间分成左右两块计算贡献，公式为：
$res=now\times (mid-l)-(sum_{mid-1}-sum_{l-1})-now\times (r-mid)+(sum_r-sum_{mid})$

其中 $now$ 为区间中位数。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
int n,m,b,sum[100005],a[100005],ans=-1;
bool check(int x){
	for(int i=1;i<=n-x+1;i++){
		int l=i,r=i+x-1,mid=l+r>>1,now=a[mid];
		int res=now*(mid-l)-(sum[mid-1]-sum[l-1])+(sum[r]-sum[mid])-now*(r-mid);
		if(res<=b)return 1;
	}
	return 0;
}
signed main(){
	n=read(),m=read(),b=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		sum[i]=sum[i-1]+a[i];
	}
	int l=1,r=n+1;
	while(l<r){
		int mid=l+r>>1;
		if(check(mid))l=mid+1,ans=max(ans,mid);
		else r=mid;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：SilverLi (赞：0)

[ricehub の 传送门](https://www.luogu.com.cn/problem/P5844)

考虑二分枚举稻田数 $x$。

循环来枚举想收割的 $x$ 个稻田中最左边的那个稻田位置 $l$，然后通过 $x$ 推出 $r$ 和 $mi$（最右边的位置和中间位置）。

谷仓在中间时为最优解（这个去试试画出来想）所以谷仓位置为 $mi$。

那么我们枚举的这段区间的费用是多少呢？可以先循环来计算，但之前的枚举已经是 $O(n\log{n})$ 了，所以可以用**前缀和**来实现。

首先设费用为 $sum$，$f_i$ 表示 $1\sim i$ 块稻田的坐标和，$a$ 数组表示每块稻田的坐标，变量 $now$ 来表示米仓的坐标（就是 $a_{now}$），则公式为 $sum=now\times (mi-l)-(f_{mi-1}-f_{l-1})+(f_r-f_{mi})-now\times (r-mi)$。 

因为我们需要把区间分成左右两边来做，左边的费用为 $now-a_l+now-a_{l+1}+now-a_{l+2}+\dots +now-a_{mi-1}$。

我们可以发现它是有多个 $now-a_x$ 组合而成，并且有 $mi-l$ 项，则式子变为 $now\times (mi-l)-(a_l+a_{l+1}+a_{l+2}+....+a_{mi-1})$。

那么 $a_l+\dots+a_{mi-1}$ 即为第 $l$ 块稻田到第 $mi-1$ 块稻田的坐标之和，可以直接用前缀和直接表示为 $f_{mi-1}-f_{l-1}$，左边的式子最终成为 $now\times (mi-l)-(f_{mi-1}-f_{l-1})$，同理右边的式子也可以这样推出来。

算出 $sum$ 后只要比 $B$ 元小，就成立了，否则不成立。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
long long f[100010],now,k,ans,a[100010],sum,n,l,b,lef,righ,mid;
bool check(long long x){
  int i,l,r,mi;
  for (i=1;i<=n-x+1;++i){
      l=i;//最左边的稻田
		r=i+x-1;//最右边的稻田
		mi=(l+r)/2;//米仓
      now=a[mi];//米仓坐标
      sum=now*(mi-l)-(f[mi-1]-f[l-1])+(f[r]-f[mi])-now*(r-mi);
//式子的具体推法已经写在上面了
      if (sum<=b) return true;
  }
  return false;
}
int main(){
 cin>>n>>l>>b;
 for (int i=1;i<=n;++i) cin>>a[i];
 f[0]=0;
 for (int i=1;i<=n;++i) f[i]=f[i-1]+a[i];//前i个稻田的坐标之和
 lef=0;
 righ=n+1;
 ans=0;
 while (lef<=righ) {//枚举有几块稻田能收割
     mid=(lef+righ)/2;
     if (check(mid)==true){
       lef=mid+1;
       if (ans<mid) ans=mid;
     }
     else righ=mid-1;
  } 
  cout<<ans<<endl;
  return 0;
}
```

---

## 作者：封禁用户 (赞：0)

~~感觉就是简单的前缀和~~。

## 题目大意

在一条路上有 $R$ 个点，并且这些点可以重叠。要求我们选取其中的一个点作为中心，并在其余点中选若干个。满足中心点到其余点的距离之和 $5\leq B$ 且使选出的点的数量尽量多。输出这个 $\max$ 值。

## 题目解析

此题最重要的地方是找中间点，多次找中间点的话，一个一个找很麻烦，所以用函数代替，函数代码用前缀和维护坐标。

代码如下（比较紧）：

```cpp
bool func(long long l,long long r){long long zj=(l+r)/2;return ((numb[r]-numb[zj])-(numb[zj-1]-numb[l-1])-a[zj]*((r-l)&1))<=v;}

```
所以最终代码的大意是：指针不断往右移。若 $X_i,X_j$ 求出的 $sum$ 最小值 $\leq$ B，则取该区间的所有点满足条件。直到找到符合条件的最大的 $j$ 就更新答案即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,v,a[100050],numb[100050],cnt=-1;
bool func(long long l,long long r){long long zj=(l+r)/2;return ((numb[r]-numb[zj])-(numb[zj-1]-numb[l-1])-a[zj]*((r-l)&1))<=v;}
int main(){
    cin>>n>>m>>v; 
    for(long long i=1;i<=n;i++){
        cin>>a[i];numb[i]=numb[i-1]+a[i];}
    for(long long l=1,r=0;l<=n;l++){while(r<n&&func(l,r+1))r++;cnt=max(cnt,r-l+1);}
    cout<<cnt;
    return 0;
}

```
~~I AK IOI!~~


---

## 作者：A_Pikachu (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/P5844)
（如果 $\LaTeX$ 炸了，请到博客[观看](https://www.luogu.com.cn/blog/thats-me/ti-jie-p5844-ioi2011ricehub)）

$\Large\mathscr{Part\,\,1\;\;}\text{基本思路}$

其实看到这题一般会想到一个小学奥数结论：

对于任意有 $n$ 个节点的线段，其坐标分别是 $x_1,x_2, \cdots ,x_n$，且 $x_1 \leq x_2 \leq \cdots \leq x_n$。在线段上任取一点 $k$，使 $S=\displaystyle\sum_{i=1}^{n}|x_i-x_k|$ 取到最小值时，$ \begin{cases}x_k=x_{\frac{n+1}{2}},n \equiv 1\ (\bmod 2)\ ; \\x_k \in [x_{\frac{n}{2}},x_{\frac{n}{2}+1}],n \equiv 0\ (\bmod 2).\end{cases}$，此时 $S_{min}=\displaystyle\sum_{i=1}^{\lfloor\frac{n}{2}\rfloor}x_{n-i}-x_i$。

我们可以将开设仓库看成开设稻田，那么我们能发现需要钱数随着开设稻田数的增加而增加，而在开设稻田数一定时使运送钱数最少的方法中稻田都是连续的，所以想到对开设稻田数进行二分，每次判断合法情况时则取连续的判断稻田数求出钱数。

但发现暴力求钱数复杂度 $\Theta(n)$，我们考虑对其优化。观察求得 $S_{min}$ 的公式，发现对其进行转移时改变的坐标下标是一定的，令 $aim$ 为判断数量，当前下标为 $i$，则 $ans=lastans+x_i-x_{i-\lfloor \frac{aim}{2}\rfloor}+x_{i-aim}-x_{i-\lfloor \frac{aim+1}{2}\rfloor}$，所以我们只需求出第一段所需钱数再不断进行转移即可，判断是否合法就为判断 $ans\leq B$。

$\Large\mathscr{Part\,\,2\;\;}\text{Code\qquad}$

```cpp
#include <cstdio>
const int N=1e5+5;
int r,l,ans,x[N];
long long b;
int max(int x,int y){return (x>y?x:y);}
bool ck(int aim){
	long long y=0;
	for(int i=1; i<=aim>>1; i++){ // 先求出第一段答案
		y+=x[aim-i+1]-x[i];
	}
	if(y<=b) return true;
	for(int i=aim+1; i<=r; i++){ // 不断转移
		y+=x[i]-x[i-(aim>>1)]+x[i-aim]-x[i-(aim+1>>1)];
		if(y<=b) return true; // 判断合法
	}
	return false;
}
int bs(int lf,int rt){ // 二分开设稻田数
	int md=(lf+rt)>>1,res=-1;
	while(lf<=rt){
		if(ck(md)) res=md,lf=md+1;
		else rt=md-1;
		md=(lf+rt)>>1;
	}
	return res;
}
int main(){
	scanf("%d%d%lld",&r,&l,&b);
	for(int i=1; i<=r; i++) scanf("%d",x+i);
	ans=bs(1,r);
	printf("%d\n",ans);
	return 0;
}
```

时间复杂度 $\Theta(n \log_2 n)$，自然 [$\text\color{green}{AC}$](https://www.luogu.com.cn/record/43099217)！

---

