# [ABC147F] Sum Difference

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc147/tasks/abc147_f

長さ $ N $ の整数列 $ A $ があり、$ A_1\ =\ X,\ A_{i+1}\ =\ A_i\ +\ D\ (1\ \leq\ i\ <\ N\ ) $ が成り立っています。

高橋君はこの整数列の要素をいくつか選んで取り、残り全てを青木君が取ります。$ 2 $ 人のどちらかが全てを取ることになっても構いません。

高橋君の取った数の和を $ S $, 青木君の取った数の和を $ T $ としたとき、$ S\ -\ T $ として考えられる値は何通りあるでしょうか。

## 说明/提示

### 制約

- $ -10^8\ \leq\ X,\ D\ \leq\ 10^8 $
- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- 入力は全て整数である

### Sample Explanation 1

$ A $ は $ (4,\ 6,\ 8) $ です。 (高橋君, 青木君) の取り方は、 $ ((),\ (4,\ 6,\ 8)),\ ((4),\ (6,\ 8)),\ ((6),\ (4,\ 8)),\ ((8),\ (4,\ 6))),\ ((4,\ 6),\ (8))),\ ((4,\ 8),\ (6))),\ ((6,\ 8),\ (4))),\ ((4,\ 6,\ 8),\ ()) $ の $ 8 $ 通りあります。 $ S\ -\ T $ はそれぞれ $ -18,\ -10,\ -6,\ -2,\ 2,\ 6,\ 10,\ 18 $ であるので、値の種類数は $ 8 $ です。

### Sample Explanation 2

$ A $ は $ (3,\ 0) $ であり、$ S\ -\ T $ として考えられる値は $ -3,\ 3 $ で、種類数は $ 2 $ です。

## 样例 #1

### 输入

```
3 4 2```

### 输出

```
8```

## 样例 #2

### 输入

```
2 3 -3```

### 输出

```
2```

## 样例 #3

### 输入

```
100 14 20```

### 输出

```
49805```

# 题解

## 作者：fengenrong (赞：10)

### 题意
在一个等差数列中取出若干个元素，求取出的元素与未取出的元素的差值有多少种可能。
### 思路

首先，我们有一个式子：
$$w(i)=\sum_{i \in S}A_i-\sum_{i \notin S}A_i$$
不难看出，该式可以变为：
$$w(i)=2\times \sum_{i \in S}A_i-\sum_{i=1}^{n}A_i$$
其实，$\sum_{i=1}^{n}+A_i$ 和 $2$ 是一个定值，所以我们只需求出 $\sum_{i \in S}A_i$ 的不同和即可。

不难看出 $A_i=X+(i-1)\times num$，其中 $X$ 为首项，$num$ 为公差。

所以，假如我们选取了 $t$ 个数，那它们的总和必定为 $tX+num \times s$。

而 $s$ 如何求？

不难看出，最小的肯定是选前 $t$ 个，最大的则是选后 $t$ 个，所以 $s$ 的范围为 $[\frac{t\times(t-1)}{2}
,\frac{(2n-1-t)\times t}{2}]$。

但是，我们还需要考虑覆盖的情况，也就是：
$$t_i\times x+k_i\times num=t_j\times x+k_j\times num$$
移项得：
$$(t_i-t_j)\times x=(k_j-k_i)\times num$$
可推出：
$$num \mid (t_i-t_j)\times x$$
可得 $t_i \times x$ 与 $t_j \times x$ 对模 $num$ 同余。

所以，我们可以直接把 $t_i \times x$ 和 $t_j \times x$ 余数相等的放到一起，求一下区间覆盖即可。
### Code
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,x,num,ans;
struct node{
    int l,r;
    bool operator<(const node& x)const{return l<x.l;}
};
vector<node> v[2000005];
map<int,int> M;
int cnt;
signed main(){
    scanf("%lld%lld%lld",&n,&x,&num);
    if(!num){
        if(!x) puts("1");
        else printf("%lld\n",n+1);
        return 0;
    }
    for(int t=0;t<=n;t++){
        if(!M[t*x%num]) M[t*x%num]=++cnt;
        v[M[t*x%num]].push_back({t*(t-1)/2+(t*x/num),(2*n-1-t)*t/2+(t*x/num)});
    }
    for(int i=1;i<=cnt;i++){
        sort(v[i].begin(),v[i].end());
        int L=v[i][0].l,R=v[i][0].r;
        for(int j=1;j<v[i].size();j++){
            if(v[i][j].l<=R) R=max(v[i][j].r,R);
            else ans+=(R-L+1),L=v[i][j].l,R=v[i][j].r;
        }
        ans+=(R-L+1);
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Acfboy (赞：9)

模拟赛做到的，结果两个小时都没想出来。

题目要求一个人在等差数列中选一些数，另一个人选剩下的，求他们选的数差的不同个数。

那么设一个人选的和为 $w$, 总和是 $sum$, 两个人的差就是 $2w-sum$, 因为 $sum$ 不变，所以只要求出 $w$ 的不同个数就可以了。  

设一个人选的数的下标集合是 $T$, 那么 $w = x|T| + \sum_{i \in T} (i-1)d$，将 $d$ 提出，再设 $k = |T|, v = \sum_{i \in T} (i-1)$, 式子变成了 $w = kx + vd$。再想想 $v$ 的取值范围，因为 $i-1$ 是在 $[0, n-1]$ 之间连续的，所以我们非常好确定 $v$ 的范围，就是 $[\sum_{i=0}^{k-1}i,\  i\cdot n - \sum_{i=1}^ki]$。

考场上想到也许可以容斥，先把这所有的区间内的个数都加起来，然后找到类似 $k_1 d = k_2 x$ 的式子去把重复的给减掉，但是这样细节繁多，而且时间上也过不去。

然后就是本题的关键想法：$kx + vd$ 在模 $d$ 意义下肯定是相同的。这意味着可以按 $kx$ 分类，不同类中的肯定是不同的，所以只要处理 $kx$ 模 $d$ 相同的行的数就可以了。  
我们可以把所有 $kx$ 模 $d$ 相同的数转换成数轴的一段。因为同一行的数都间隔 $d$, 那么同一行就可以直接用 $v$ 的值来表示，至于处理不同行，只需要将 $v$ 的左右端点都加上 $\frac{kx}{d}$ 就可以了。

然后就变成了简单的线段求并。

代码。

```cpp
#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>
#define int long long
int n, x, d, ans;
typedef std::vector<std::pair<int, int> > twt;
std::map<int, twt> map;
signed main() {
	scanf("%lld%lld%lld", &n, &x, &d);
	if(x == 0 && d == 0) return puts("1"), 0;
	if(x != 0 && d == 0) return printf("%lld\n", n+1), 0;
	if(d < 0) x = -x, d = -d;
	for(int i = 0; i <= n; i++) {
		int t = i*x, L = (i-1)*i/2+t/d, R = i*n-(i+1)*i/2+t/d;
		t %= d;
		if(t < 0) t += d;
		map[t].push_back(std::make_pair(L, R));
	}
	for(std::map<int, twt>::iterator it = map.begin(); it != map.end(); it++) {
		twt tmp = (*it).second;
		if(!tmp.size()) continue;
		std::sort(tmp.begin(), tmp.end());
		int l = tmp[0].first, r = tmp[0].second;
		for(int j = 1; j < (signed)tmp.size(); j++) 
			if(tmp[j].first > r) ans += r-l+1, l = tmp[j].first, r = tmp[j].second;
			else r = std::max(r, tmp[j].second);
		ans += r-l+1;
	}
	printf("%lld", ans);
}
```

---

## 作者：xtx1092515503 (赞：2)

挺好的一道题。

（翻译翻译的挺好的，我就按照翻译来写吧）

首先，一个直观的想法就是枚举这个$S$里面有多少个数，即$|S|$。这样子，我们就能找出这个$w(S)$中包含多少个首项$X$，即$|S|-|T|=|S|-(N-|S|)=2|S|-N$（个）。当然，首项的数量可以为负，就相当于减去多少个首项。

找到出现了多少个首项，我们就可以计算出出现多少个项数的范围。即，在最终的$w(S)$中，$D$最多可以有多少个，最少可以有多少个。

为了找到这个范围，我们先对这个序列做一些处理：

首先，如果$D=0$，可以直接特判掉，即当$X=0$时，无论怎么选都有$w(S)=0$；当$X\neq 0$时，共有$N+1$种方案，即$|S|=0\dots N$。

如果$D<0$，我们可以强制令$D>0$。这个的解决方案是翻转序列，即将$X$赋成$X+(N-1)D$，$D$赋成$-D$。

在处理后，我们保证了$D>0$。

显然，这时，$D$最多的情况就是$S$包含后$|S|$个数，而$T$包含前$N-|S|$个数。这个数量就可以直接等差数列求和套公式算出来。

而最少的方案则相反，$S$包含前$|S|$个数，而$T$包含后$N-|S|$个数。

我们把下界设为$dw$，上界设为$up$。

是否$[dw,up]$间每一种$D$的数量都可以被取到呢？好像不是吧。如果我们把$S$中某个数同$T$中某个数交换，最终$w(S)$的变化肯定是$2$的倍数。因此，我们只能取到$[dw,up]$中所有模$2$同余于$dw$和$up$的值，共$\dfrac{up-dw}{2}+1$个。

当然，到这里为止，我们离做完这道题还差得远的呢。毕竟，在$|S|$不同时的这$\dfrac{up-dw}{2}+1$个数中，可能存在相同的。那怎么办呢？

考虑到这$[dw,up]$的意义是$D$**的数量**。则它的实际值的范围为$[dw*D,up*D]$。并且，这个值是每隔$2D$个数出现一次。

哦，我们好像忘了那些$N$。修改一下，是$[dw*D+X(2|S|-N),up*D+X(2|S|-N)]$，还是每隔$2D$个数出现一次。

等等，每隔$2D$个数？是否可以在模$2D$的同余系下操作呢？

好像还真行。我们找出$X(2|S|-N)$在模$2D$下的同余值，然后，那个上下界$[dw,up]$就可以同除以$2$变成一段真正的区间。这样，我们在每个剩余系下分别讨论，求这些区间的并集即可。

先贴出求区间的代码：

```cpp
for(int i=0;i<=n;i++){
	int j=n-i;
	int base=a*(i-j);
	int up=suf(i)-pre(j);
	int dw=pre(i)-suf(j);
	base+=dw*d;
	int id=base%(2*d);
	if(id<0)id+=2*d;
	int x=(base-id)/(2*d),y=x+(up-dw)/2;
	mp[id].push_back(make_pair(x,y));
}
```
其中，$\operatorname{pre}(x)$计算了前$x$个数中$D$的数量，$\operatorname{suf}(x)$计算了后$x$个数中$D$的数量。因为$2D$过大开不下那么大的数组，但有值的同余系数量不会超过$N$个，因此就用 ```std::map<int,vector<pair<int,int>>>```来存储。

然后求区间并的部分应该不用讲吧……会来做ABC的F题的人应该都会这种东西……吧？

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a,d,res;
map<int,vector<pair<int,int> > >mp;
int pre(int x){//the number of d's in the prefix x numbers
	return x*(x-1)/2;
}
int suf(int x){//the number of d's in the suffix x numbers
	return (2*n-1-x)*x/2;
}
vector<pair<int,int> >v;
signed main(){
	scanf("%lld%lld%lld",&n,&a,&d);
	if(d==0){
		if(!a)puts("1");
		else printf("%lld\n",n+1);
		return 0;
	}
	if(d<0)a+=(n-1)*d,d=-d;
	for(int i=0;i<=n;i++){
		int j=n-i;
		int base=a*(i-j);
		int up=suf(i)-pre(j);
		int dw=pre(i)-suf(j);
		base+=dw*d;
		int id=base%(2*d);
		if(id<0)id+=2*d;
		int x=(base-id)/(2*d),y=x+(up-dw)/2;
		mp[id].push_back(make_pair(x,y));
	}
	for(map<int,vector<pair<int,int> > >::iterator it=mp.begin();it!=mp.end();it++){
		v=it->second;
		sort(v.begin(),v.end());
		int rb=-1e18;
		for(int i=0;i<v.size();i++){
			rb=max(rb,v[i].first);
			res+=max(0ll,v[i].second-rb+1);
			rb=max(rb,v[i].second+1);
		}
	}
	printf("%lld\n",res);
	return 0;
} 
```


---

## 作者：ziyistudy (赞：1)

模拟赛第一次过 $2400$ 的题目，~~太有实力了！~~

看到等差数列先把通项写出来：$A_n=X+(n-1)D$。

把前面和后面分开考虑。

$$\begin{aligned} w(S)&=X(\operatorname{size(S)}-(n-\operatorname{size(S)}))+D(k-(\frac{n(n-1)}{2}-k)) \\ &=X(2\times \operatorname{size(S)}-N)+D(2k-\frac{n(n-1)}{2})\end{aligned}$$

上面 $\operatorname{size(S)}$ 为集合 $S$ 的大小，$k=\sum_{i\in S}(i-1)$ ，表示集合 $S$ 中 $D$ 的个数。

考虑枚举 $\operatorname{size(S)}$，令 $i=\operatorname{size(S)}$。则 $w(S)=X(2i-N)+D(2k-\frac{n(n-1)}{2})$。不难发现 $\frac{(i-1)i}{2} \leq k \leq \frac{(2n-i-1)i}{2}$（最小为从 $0$ 个 $D$ 开始选，最大为从 $n-1$ 个 $D$ 开始选，中间均可取到）。

发现其实这个式子中有很多是定值，不影响去重，可以去掉。简化后变为 $w(S)=iX+kD$。

$w(S)$ 为公差为 $D$ 的等差数列，直接对 $D$ 取模，得到 $w(S)=pD+q$（$p$ 为商，$q$ 为余数，$0\leq q<D$）。显然对于 $q$ 不同的 $w(S)$ 不会出现重复，对于 $q$ 相同的 $w(S)$，判断两个 $w(S)$ 中 $p$ 取值范围的交集有多少，减掉即可。

```cpp
#include<bits/stdc++.h>
#define int long long
const int MOD=1e9+7;
using namespace std;
struct node
{
	int l,r;
};
map<int,node> M;
int check(int l,int r,int L,int R)
{
	if(r<L){
		return 0;		
	}
	if(l<=L){
		return min(R-L+1,r-L+1);
	}
	if(R<l) {
		return 0;	
	}
	return min(R-l+1,r-l+1);
}
node merge(int l,int r,int L,int R)
{
	if(r<L){
		return {L,R};		
	}
	if(l<=L){
		return {l,max(r,R)};
	}
	if(R<l) {
		return {L,R};
	}
	return {L,max(r,R)};
}
signed main()
{
	int n,x,d;cin>>n>>x>>d;
	if(d==0&&x==0) {cout<<1<<endl;return 0;}
	if(d==0) {cout<<n+1<<endl;return 0;}
	int ans=0;
	for(int i=0;i<=n;i++){
		int cnt,cnt1=(i*x)%d;
		if(cnt1<0) cnt1+=d;
		cnt=(i*x-cnt1)/d;
		if(M.find(cnt1)!=M.end()){
			node now=M[cnt1];
			int L=cnt+(i-1)*i/2,R=cnt+(2*n-i-1)*i/2;
			ans+=R-L+1-check(now.l,now.r,L,R);
			M[cnt1]=merge(now.l,now.r,L,R);
		}
		else {
			ans+=((2*n-i-1)*i/2-(i-1)*i/2+1);
			M[cnt1]={cnt+(i-1)*i/2,cnt+(2*n-i-1)*i/2};			
		}
	}
	cout<<ans<<endl;
}
```

---

## 作者：AC_love (赞：0)

令 $A$ 数列 $N$ 项和为 $s$，有：

$$\sum_{i \not \in S}A_i = s - \sum_{i \in S}A_i$$

则原式可以转化为：

$$w(S) = 2\sum_{i \in S}A_i - s$$

$s$ 是个定值，那么显然 $w(S)$ 的不同取值的个数等于 $\sum_{i \in S}A_i$ 的不同取值个数。

只要考虑这个怎么求就可以了。

考虑枚举选了几项，设选了 $n$ 项，则取到的值形如 $nX + mD$。

考虑这个 $m$ 有多少种取值。最小的 $m$ 是取前 $n$ 项，为 $\sum_{i = 0}^{n - 1}i$，即 $\dfrac{n(n - 1)}{2}$。最大的 $m$ 是取后 $n$ 项，为 $\sum_{i = N - n}^{N - 1}i$，即 $\dfrac{n(2N - n - 1)}{2}$。这中间所有的 $m$ 都能取到。

但同时我们发现，$n$ 不同时，$nX + mD$ 的值也有可能相同。对于 $n_1 \neq n_2$，当且仅当 $n_1X \equiv n_2X \pmod D$ 时，$n_1X + mD$ 与 $n_2X + mD$ 的值可能相等，此时我们认为 $n_1$ 和 $n_2$ 可以被划分成一个类别。我们把所有 $n$ 划分成若干个类别之后，对于每个类别内部分别做区间覆盖即可。不同类别之间的 $n$ 不可能相等，所以最后我们只要把每个类别的答案加起来就可以了。

注意对 $D = 0$ 进行特判。

[code](https://atcoder.jp/contests/abc147/submissions/65559532)

---

## 作者：_Yonder_ (赞：0)

先对题目进行小转化：

$$w(S)=\sum_{i\in S}a_i-\sum_{i\not\in S}a_i=2\sum_{i\in S}a_i-\sum a_i$$

因为 $2,\sum a_i$ 为定值，所以求 $w(S)$ 的种类数就相当于求 $\displaystyle\sum_{i\in S}a_i$ 的种类数。

注意到 $n\le2\times10^5$，考虑在 $n$ 上搞动静。

令 $a_i=x+(i-1)d,s=\sum_{i\in S}A_i$。

枚举 $a_i$ 不太现实，因为其会涉及到大量的容斥，于是考虑枚举选多少个数，那么 $s=tx+cd$，$c\in[\frac{t(t-1)}{2},\frac{t(2n-t-1)}{2}]$。

还没完，我们还得减去不同 $t$，相同 $s$ 的贡献，即：

$$t_0x+c_0d=t_1x+c_1d$$
$$(t_0-t_1)x=(c_1-c_0)d$$

所以 $d\mid(t_0-t_1)x$，把模 $d$ 同余的 $tx$ 放一起求并即可。

抽象的，每个 $t$ 的 $s$ 会构成一条数轴。因为产生重复的贡献需模 $d$ 同余，所以我们将这些数轴全部左移 $tx\bmod d$ 位，为方便计算，再将这些数全部除上 $d$，就可以求并了。

---

## 作者：Empty_Dream (赞：0)

## 题面

[题目传送门](https://atcoder.jp/contests/abc147/tasks/abc147_f)

## 分析

考虑转换一下式子：
$$
w(S)=\sum_{i\in S}A_i-\sum_{i\not\in S}A_i \\
$$
因为有：
$$
\sum_{i\in S}A_i + \sum_{i\not\in S}A_i=\sum_{i=1}^{N} A_i
$$
不难得出：
$$
w(S)=2\times \sum_{i\in S}A_i-\sum_{i=1}^{N} A_i
$$
第一步转换完成了，后面 $\sum_{i=1}^NA_i$ 是定值，所以总可能性就变成了前面一部分的种数。

再考虑每个数的表示方式：
$$
A_i=X+(i-1)\cdot D
$$
所以等差数列中 $p$ 项的和可以表示为，其中 $k$ 是所选数下标减 $1$ 的和：
$$
s=p\cdot X + k \cdot D
$$
稍微手玩一下可以发现一个性质，在 $p$ 不变的情况下，$k$ 的取值范围是一个连续的区间。具体的，$k\in[\frac{(i-1)\cdot i}{2},\frac{(2\cdot n-i-1)\cdot i}{2}]$。

很明显这样算会有重复，考虑什么情况会有重复发生，不难想到，如果满足如下式子就有可能会有重复：
$$
p_i \cdot X+k_i\cdot D =p_j\cdot X+k_j\cdot D\\
p_i\cdot X \equiv p_j \cdot X (\bmod D)
$$
形象的，每一个和都是由 $X$ 的倍数加上 $D$ 的倍数构成的，而对于 $p$ 相同 $k$ 不同的和也是一个等差数列，所以这个等差数列的“首项”和另外一个的模 $D$ 同余的话那就有可能重复。如果已经满足上述条件了，那就可以到下一步判断两个等差数列是否有交集了，可以当作**线段**之间有没有重合部分去做（因为公差一样又同余所以可以比较边界判断有没有重合）。

为了方便，我们可以采取类似离线的方式，把每一条线段记录下来，按左端点排序（左端点指的是 $p$ 固定下 $k$ 取最小的 $s$，右端点同理），新产生的贡献肯定是在之前线段的最右端点往右的部分才有贡献，所以只用记录端点最靠右的一段连续区间，每次比较一下记录贡献和维护这个区间。

对于贡献的记录就是类似等差数列的方法，用求项数的方法求就好，注意有时候要处理边界。

一切看似都如此顺利，但是当 $p<0$ 时好像就挂了，没关系，对于样例二输出一下运行时的参数，发现有些线段的左端点和右端点反了（事实上是全部），那么在记录线段的时候特判一下反转掉就行。但是还是挂了，我们发现算贡献等差数列求项数除了一个负的公差，很简单，加个绝对值就行。~~简简单单就过了。~~

反转其实是为了保证上面可以简单维护区间。

## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
#define pii pair<int, int>
#define fir first
#define sec second
#define endl '\n'
#define memset(a, b) memset(a, b, sizeof(a))
using namespace std;

const int N = 2e5 + 5, M = 10 + 5;
const int mod = 998244353;

int n, x, d, ans;
map<int, vector<pii>> mp;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> x >> d;
    if (d == 0 && x == 0) return cout << 1, 0;
    if (d == 0) return cout << n + 1, 0;                                        
    for (int i = 0; i <= n; i++){
        int tmp = i * x % d;
        int st = (i - 1) * i / 2, ed = (n - i + n - 1) * i / 2;
        if (d < 0) swap(st, ed);//小小操作一下，让左端点比右端点小
        mp[tmp].push_back({st * d + i * x, ed * d + i * x});//记录每一条线段
    }
    for (auto it : mp){
        sort(it.sec.begin(), it.sec.end());//按左端点排序
        int l = it.sec[0].fir, r = it.sec[0].sec;
        ans += (r - l) / abs(d) + 1;//初始先放进来一条线段
        for (int j = 1; j < it.sec.size(); j++){
            int tl = it.sec[j].fir, tr = it.sec[j].sec;//不断取出来一条线段取维护这个“最右线段”
            if (tl <= r) ans += max(tr - r, 0ll) / abs(d), r = max(r, tr);//有重合，算上最右端点往右的贡献
            else ans += (tr - tl) / abs(d) + 1, l = tl, r = tr;//没重合，直接加上这一段的贡献
            //                      因为上面保证了左端点比右端点小，所以公差也必须是正的
        }
    }
    cout << ans;
    return 0;
}
```

---

