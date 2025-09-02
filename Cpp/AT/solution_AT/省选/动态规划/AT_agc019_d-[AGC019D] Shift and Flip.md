# [AGC019D] Shift and Flip

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc019/tasks/agc019_d

$ 0 $ と $ 1 $ からなる同じ長さの二つの文字列 $ A\ =\ A_1\ A_2\ ...\ A_n $ と $ B\ =\ B_1\ B_2\ ...\ B_n $ があります。

あなたは、以下の操作を任意の順序で何度でも行って $ A $ を変化させることができます。

- $ A $ を一文字左にシフトする（すなわち、$ A\ =\ A_1\ A_2\ ...\ A_n $ として $ A $ を $ A_2\ A_3\ ...\ A_n\ A_1 $ に置き換える）。
- $ A $ を一文字右にシフトする（すなわち、$ A\ =\ A_1\ A_2\ ...\ A_n $ として $ A $ を $ A_n\ A_1\ A_2\ ...\ A_{n-1} $ に置き換える）。
- $ B_i\ =\ 1 $ であるような $ i $ をいずれか一つ選び、$ A_i $ を反転する（すなわち、$ A_i\ =\ 1\ -\ A_i $ とする）。

あなたの目標は文字列 $ A,\ B $ を一致させることです。

これに必要な最小の操作回数を出力してください。ただし、これが不可能である場合は $ -1 $ と出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ |A|\ =\ |B|\ \leq\ 2,000 $
- $ A,\ B $ は $ 0 $ と $ 1 $ からなる。

### Sample Explanation 1

目標を達成する最短の操作列を一つ示します。 - $ A_1 $ を反転: $ A\ =\ 0010 $ - $ A $ を左にシフト: $ A\ =\ 0100 $ - $ A_1 $ を再度反転: $ A\ =\ 1100 $

### Sample Explanation 2

$ A $ の唯一のビットを反転させる方法はありません。

### Sample Explanation 3

目標を達成する最短の操作列を一つ示します。 - $ A $ を右にシフト: $ A\ =\ 01101 $ - $ A_5 $ を反転: $ A\ =\ 01100 $ - $ A $ を左にシフト: $ A\ =\ 11000 $ - $ A $ を再度左にシフト: $ A\ =\ 10001 $

### Sample Explanation 4

$ A_1 $, $ A_3 $, $ A_4 $, $ A_6 $, $ A_7 $ を任意の順序で反転すればよいです。

## 样例 #1

### 输入

```
1010
1100```

### 输出

```
3```

## 样例 #2

### 输入

```
1
0```

### 输出

```
-1```

## 样例 #3

### 输入

```
11010
10001```

### 输出

```
4```

## 样例 #4

### 输入

```
0100100
1111111```

### 输出

```
5```

# 题解

## 作者：myee (赞：16)

### 前言

爆标了。可以用 FFT 优化到 $O(n\log n)$，或者用 `bitset` 优化到 $O(n^2/w)$。

### 思路

首先，无解当且仅当 $B_i\equiv0$ 且存在 $A_i=1$。

**总可以发现，任意一种最优路线均形如向左共 $l$ 步，向右共 $r$ 步，终点在起点左 / 右 $p$ 的位置。**

用调整法容易证明，答案为 $2r+2l-p+\text{终点处未匹配对数目}$，其中「未匹配对」定义为 $0$ 与 $1$ 在同一下标处，或者 $1$ 和 $0$ 在同一下标处。

我们不妨枚举终点，然后最小化 $l+r$。

**那么，一个方案合法当且仅当任何一个 $A_i=1$ 的数都曾经到过 $B_i=1$ 的位置（包括终点）。**

从而可以转化成不多于 $n$ 条限制，每条形如 $l\ge l_j\lor r\ge r_j$ 的形式，其中 $l_j/r_j$ 表示如果只向左 / 右，其至少多远到达 $B$ 中的 $1$；向左还有限制时为 $l\ge p$，向右时为 $r\ge p$；最后再加上 $l\ge0$ 与 $r\ge0$ 两条基本限制。

这样我们就是进行如下规划：

$$\min z=x+y$$

$$s.t.\begin{cases}A_1=0\lor x\ge l_1\lor y\ge r_1\\A_2=0\lor x\ge l_2\lor y\ge r_2\\\vdots\\A_n=0\lor x\ge l_n\lor y\ge r_n\\x\ge[\text{终点向左走}]p\\y\ge[\text{终点向右走}]p\end{cases}$$

考虑用**图解法**解规划。

我们把这些限制通通画到二维平面上，就是若干个 $3/4$ 平面与两个半平面取交，求其上最小 $x+y$。

注意到 $z=x+y$ 在 $z$ 为定值时为一斜线，我们考虑找轮廓线上的最小合法点即可。

这个可以直接桶排然后单调栈处理。总复杂度 $O(n^2)$。

如果注意到前面的若干限制是始终不变的，此题实际上可以用扫描线做到更优复杂度！

由于要对前面的「未匹配对数目」贡献使用 FFT 加速计算，总复杂度将为 $O(n\log n)$ 的。

### Code

实现了扫描线的写法。

没写 FFT，所以是 $O(n^2)$ 的。写个卷积就是 $O(n\log n)$ 的了。（好吧其实可以用 `atcoder.h`）

这里是核心代码。

```cpp
uint n=0,cnt1=0,cnt2=0;scanf("%s%s",C1,C2);
while(C1[n])cnt1+=C1[n]=='1',cnt2+=C2[n]=='1',n++;
if(!cnt1)return printf("%u\n",cnt2),0;
if(!cnt2)return puts("-1"),0;
if(cnt2==n)return printf("%u\n",n-cnt1),0;
for(uint i=0;i<n;i++)L[i]=R[i]=C2[i]=='1'?0:1e9;
for(uint i=0;i<2;i++)for(uint j=0;j<n;j++)_min(L[j],L[j?j-1:n-1]+1);
for(uint i=0;i<2;i++)for(uint j=n-1;~j;j--)_min(R[j],R[j<n-1?j+1:0]+1);
std::vector<std::pair<uint,uint> >V{{0,n},{n,0}},User;
for(uint i=0;i<n;i++)if(C1[i]=='1')V.push_back({L[i],R[i]});
std::sort(V.begin(),V.end());
for(auto s:V){
    while(User.size()&&User.back().second<=s.second)User.pop_back();
    User.push_back(s);
}
V=User;
LAns[n]=RAns[n]=n;
for(uint i=n-1,j=V.size()-1;~i;i--){
    LAns[i]=std::min(LAns[i+1],i+V[j].second);if(V[j-1].first==i)j--;
}
for(uint i=n-1,j=0;~i;i--){
    RAns[i]=std::min(RAns[i+1],i+V[j].first);if(V[j+1].second==i)j++;
}
for(uint i=0;i<n;i++)LAns[i]=2*LAns[i]-i,RAns[i]=2*RAns[i]-i;
for(uint i=0;i<n;i++)for(uint j=0;j<n;j++)LAns[i]+=C1[j]!=C2[(j+n-i)%n]; // 可以 FFT 优化
for(uint i=0;i<n;i++)for(uint j=0;j<n;j++)RAns[i]+=C1[j]!=C2[(j+i)%n]; // 可以 FFT 优化
printf("%u\n",std::min(*std::min_element(LAns,LAns+n),*std::min_element(RAns,RAns+n)));
```




---

## 作者：封禁用户 (赞：11)


[AGC019D](https://www.luogu.com.cn/problem/AT_agc019_d)

## 思路

分讨是好习惯。观察到 $n \le 2000$，所以直接大力分讨再进行一个枚举即可。

假设串 $B$ 没有 ``1``，进行特判即可，那么接下来我们就可以直接讨论串 $B$ 至少有一个 ``1`` 的情况了。

前两个操作可以把串 $A$ 左右移动，则设 $A$ 最终的状态为向右移动 $k$ 位。（当 $k$ 为负时，即向左运动）

考虑最坏的情况，就是串 $A$ 的每一位都与串 $B$ 不同，需要进行 $n$ 次取反操作，然后再把取反后的串 $A$ 移到串 $B$ 对应的位置。这是基于移动的，所以可以证明 $k\in\begin{bmatrix}1-2n,2n-1\end{bmatrix}$。这样就可以对 $k$ 进行枚举了。

对于取反操作的限制条件，可以预处理出 $2$ 个值：至少要右移 $r_i$ 位才能在到串 $B$ 中找到一个满足 $B_i = 1$ 的和至少要左移 $l_i$ 位才能在到串 $B$ 中找到一个满足 $B_i = 1$ 的。

设走过的区间端点 $L,R$，若 $L \le l_i$ 或 $r_i \le R$，那么处理 $A_i$ 时在移位过程中就可以取反，不需要格外的移位。(即：多一次操作)

不满足条件的点需要额外的移位操作，记录下 $\left| L-l_i \right|$ 和 $\left| r_i-R \right|$。因为要最小的移动又要包含所有的区间，所以要取最大的区间边界，为了方便统计，我们先对 $\left| L-l_i \right|$ 这一维排序，使得对于每个 $i$ 的前缀最大，再处理一个后缀最大的 $\left| r_i-R \right|$，合起来就是所求的，取最小值即可。

这里答案要 $\times 2$ 的，因为一来一回嘛……

最终时间复杂度 $\mathcal{O(n^2 \log n)}$。

此外，需要注意的是，在判断 $A_i$ 和 $B_i$ 是否相同时要注意，由于 $k$ 可能是负数，所以在取模的时候要小心出现负下标。

代码可读性差就不放了。

---

## 作者：xtx1092515503 (赞：8)

本题可以分3步解决：

### 1）证明除非$b$中全是$0$，否则必有解。

显然，如果$b$中有一个位置为$1$，则可以来回移动$a$，让每个$a$中的$1$都移到$b$中某个$1$处消成$0$。当$a$变成全$0$数组后，只要在$b$中每个$1$处消一下，即可得到一个解。

而当$b$全为$0$时，除非$a$也全为$0$，否则无解。

### 2）证明$a$的移动必定是（向左$\rightarrow$向右回到原点$\rightarrow$再向右），或者相反。

证明如下（接下来所有运算都在模$n$意义下进行）：

设$\Delta$为最终的位移量($\Delta<0$为先向右再向左；否则，为先向左再向右。证明中默认为$\Delta\geq0$），即全部操作完后，还要移动$|\Delta|$次达到合法状态。

再设$L$为左移长度，$R$为**过原点后**右移长度。

则对于每个要修改的$a_i$，都必须有$\exists j\in[i-L,i+R]$，满足$b_j=1$。

则满足此条件的任何$L$与$R$即标志着一组合法解。

### 3）找出最优的$L$与$R$

枚举$\Delta$（代码中为$i$)。

我们设$Lp_i$为最小的$j$，使得$b_{i-Lp_i}$为$1$

同理，$Rp_i$为最小的$j$，使得$b_{i+Rp_i}$为$1$

则要求$min(L+R)$，并满足$\forall i$，有$Lp_i\leq L$或$Rp_i\leq R$

则在枚举$\Delta$时，我们求出所有失配的点存在$Mis$数组内。

将$Mis$中的点抽象为点$(Lp_i,Rp_i)$，并按照$Rp$排序。则记录排序后$Lp$的后缀最大值存于数组$Suf$中，显然，当枚举每个$i$时，一组合法解即为$(L=Suf_{i+1},R=Rp_i)$。

显然，除去排序后，复杂度为$O(n^2)$。而又有$\forall i,Rp_i<n$，因此可以用$O(n)$的桶排。

则总复杂度为$O(n^2)$，可以通过。

**注意！！！“向左$\rightarrow$向右回到原点$\rightarrow$再向右”只是一般情况，还有特殊情况（一路向左/右，不回头），应当考虑。**

总结：最大的瓶颈在于发现性质 2)。发现后也要经过思考才能应用它。

代码(附有英文注释)：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,Lp[2010],Rp[2010],Mis[2010],buc[2010],tmpMis[2010],mn=0x3f3f3f3f,Suf[2010];
char tms[2010];
bool a[2010],b[2010],s1,s2;
void Sort(){//use a bucket sort to let the complexity of sorting become O(n)
	for(int i=0;i<=n;i++)buc[i]=0;
	for(int i=1;i<=Mis[0];i++)buc[Rp[Mis[i]]+1]++;
	for(int i=1;i<=n;i++)buc[i]+=buc[i-1];
	for(int i=1;i<=Mis[0];i++)tmpMis[++buc[Rp[Mis[i]]]]=Mis[i];
	for(int i=1;i<=Mis[0];i++)Mis[i]=tmpMis[i];
}
int main(){
	scanf("%s",tms),n=strlen(tms);
	for(int i=0;i<n;i++)a[i]=tms[i]-'0';
	scanf("%s",tms);
	for(int i=0;i<n;i++)b[i]=tms[i]-'0';
	memset(Lp,0x3f3f3f3f,sizeof(Lp)),memset(Rp,0x3f3f3f3f,sizeof(Rp));
	for(int i=0;i<n;i++)for(int j=0;j<n;j++)if(b[j])Lp[i]=min(Lp[i],(i-j+n)%n),Rp[i]=min(Rp[i],(j-i+n)%n);
	for(int i=0;i<n;i++)s1|=a[i],s2|=b[i];//check if there's no '1' in array b. If so, only if there's no '1' in array a, it is unable to get a proper answer.
	if(!s2){
		if(!s1)puts("0");
		else puts("-1");
		return 0;
	}
	for(int i=0;i<n;i++){//numerate the end position of a_i
		Mis[0]=0;
		for(int j=0,k=i;j<n;j++,k++,k%=n)if(a[k]!=b[j])Mis[++Mis[0]]=k;//find the mismatched positions
		Sort();
		Suf[Mis[0]+1]=0;
		for(int j=Mis[0];j;j--)Suf[j]=max(Suf[j+1],Lp[Mis[j]]);//suffix maximum
		mn=min(mn,max(i,Suf[1])*2-i+Mis[0]);//only go left/right situations
		mn=min(mn,(Suf[1]+(n-i)%n)*2-(n-i)%n+Mis[0]);
		for(int j=1;j<=Mis[0];j++){
			mn=min(mn,(Rp[Mis[j]]+max(i,Suf[j+1]))*2-i+Mis[0]);
			mn=min(mn,(Suf[j+1]+max((n-i)%n,Rp[Mis[j]]))*2-(n-i)%n+Mis[0]);
		}
	}
	printf("%d\n",mn);
	return 0;
}
```


---

## 作者：xcyle (赞：6)

这是一道考察基本功的题。

首先，容易想到枚举最终的“对齐方式”，也就是在经过许多次修改操作以及左右移操作后，A一共左移了多少位与B对齐

在对齐方式确定的情况下，显然第三个操作的次数已经固定，即A与B不同的位置个数

现在要最小化前两个操作的次数和

显然在最优方案中A的移动是分为两段：先一堆左移，再一堆右移（或者倒过来），因为我们把它看成B的左右移，那么可以修改的位置就是每次移动之后所有1的位置的并集，而重复到一种移动状态显然不会让集合元素增加

考虑到枚举左右移的最远位置与枚举对齐方式，时间$O(n^3)$，需要优化

考虑到在枚举对齐方式后，每一个需要修改的地方都需要被B的左右移（上文提及将A的左右移转化为B的左右移）覆盖到，因此每个位置可以独立出来

设$l_i$表示最少向左边移动多少次才能让B覆盖到$i$位置，$r_i$同理。那么前两个操作的次数和就是所有需要修改的位置的$r$取max减去$l$取min

对于预处理$l,r$显然是$O(n^2)$的，因为你只需要暴力枚举左右移时的1的位置的并集

---

## 作者：hegm (赞：2)

### [[AGC019D] Shift and Flip](https://www.luogu.com.cn/problem/AT_agc019_d)

尝试手摸几次发现修改方案有迹可循。

考虑枚举最终情况下会挪移几次（即 $i$ 位置最后会处在位置 $i+x$）。（以下默认 $i$ 向右移动，向左同理即可）

考虑双方关系，如果 $a_i=b_{i+x}$ 那么无需多考虑。

如果 $a_i=0$ 并且 $b_{i+x}=1$ 那么在挪移结束的时候进行操作 $3$ 即可。

如果 $a_i=1$ 并且 $b_{i+x}=0$ 这种情况有些复杂度，如果在挪移过程中经过过 $b_{j}=1$ 的位置，那么在内个时刻进行操作 $3$ 即可。

那么还剩下一些位置，他们在此过程中无法从 $1$ 变为 $0$。这个集合为 $S$。

那么考虑如何改变他们，我们可以在一开始时刻反向移动，或者在最后时刻额外移动一些。

因此对于每一个满足如上条件的位置 $i$，我们需要求出 $fr_i,tl_i$ 表示 $b_j=1,j<i$ 的最近位置距离，$tl_i$ 同理。

那么对于每一个 $i$ 我们需要在 $fr_i,tl_i$ 中抉择。

所以我们的额外贡献就是选出 $T\subseteq  S$，$\max\limits_{i\in T}fr_i+\max\limits_{i\in (S\smallsetminus T)} tl_i$。

这个可以在排序后扫描线即可。

不考虑排序复杂度（可以桶排）那么整体做法为 $O(n^2)$。

### $\text{CODE}$

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define make make_pair
#define pii pair<int,int>
#define N 4005
#define inf 1000000000
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
char a[N],b[N];
int n,f[N],ans=inf,lst[N],nxt[N];
int get(int l,int r)
{
	return f[r]-f[l-1];
}
pii p[N];
bool cmp(pii a,pii b)
{
	if(a.fi==b.fi)return a.se<b.se;
	return a.fi>b.fi;
}
void solvel(int x)
{
	int pos=x,cnt=0;
	for(int i=1;i<=n;i++)
	{
		if(b[i+x]=='1'&&a[i]=='0')pos++;
		if(b[i+x]=='0'&&a[i]=='1')
		{
			pos++;
			if(get(i,i+x)==0)p[++cnt]={lst[i+n],nxt[i+x]};
		}
	}
	sort(p+1,p+1+cnt,cmp);
	int mx=0;p[cnt+1].fi=0;
	for(int i=1;i<=cnt+1;i++)
	{
		ans=min(ans,pos+(mx+p[i].fi)*2);
		mx=max(mx,p[i].se);
	}
}
void solver(int x)
{
	int pos=-x,cnt=0;
	for(int i=n+1;i<=2*n;i++)
	{
		if(b[i+x]=='1'&&a[i]=='0')pos++;
		if(b[i+x]=='0'&&a[i]=='1')
		{
			pos++;
			if(get(i+x,i)==0)p[++cnt]={lst[i+x],nxt[i-n]};
		}
	}
	sort(p+1,p+1+cnt,cmp);
	int mx=0;
	p[cnt+1].fi=0;
	for(int i=1;i<=cnt+1;i++)
	{
		ans=min(ans,pos+(mx+p[i].fi)*2);
		mx=max(mx,p[i].se);
	}
}
signed main()
{
	scanf("%s",a+1);
	scanf("%s",b+1);
	n=strlen(a+1);
	int awa=0,qwq=0;
	for(int i=1;i<=n;i++)
	{
		awa+=a[i]-'0';
		qwq+=b[i]-'0';
	}
	if(!qwq&&awa)
	{
		cout<<"-1\n";
		return 0;
	}
	for(int i=1;i<=n;i++)b[i+n]=b[i];
	for(int i=1;i<=n;i++)a[i+n]=a[i];
	for(int i=1;i<=2*n;i++)
	{
		f[i]=f[i-1]+b[i]-'0';
	}
	for(int i=1;i<=2*n;i++)
	{
		lst[i]=lst[i-1]+1;
		if(b[i]=='1')lst[i]=0;
	}
	for(int i=2*n;i>=1;i--)
	{
		nxt[i]=nxt[i+1]+1;
		if(b[i]=='1')nxt[i]=0;
	}
	for(int i=1;i<=n;i++)solvel(i-1);
	for(int i=1;i<=n;i++)solver(1-i);
	cout<<ans<<"\n";
	return 0;
}

```

---

## 作者：WESTRAIN (赞：1)

-[[AGC019D] Shift and Flip
](https://www.luogu.com.cn/problem/AT_agc019_d)

直观感受：看到三种操作以及左右移，想到了变成环，在环上进行操作。希望在环上找到最优策略，但这种思维方式忽略了数据范围 $(n \le2000)$，显然并不是给出最优的结论，跑偏。

正确思路：已经想到了左右移操作不需要考虑顺序，所以应进一步简化为先往左移动 $L$ 步，再往右移动 $R$ 步，（反之亦然）枚举最终状态找到最优答案。但是这样统计答案需要 $\mathcal O(n)$，总复杂度为 $\mathcal O(n^3)$, 因此考虑优化。

更换枚举顺序，先枚举最终往右多少步，看看有哪些点需要更改，再找出最少需要往左移动多少步，预处理即可。代码如下：
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
char a[2005],b[2005];
int n,pre[2005],nxt[2005],ans=1e9,mx[2005];
void solve(){
	for(int i=0;i<n;i++){
		pre[i]=nxt[i]=0;
		for(int p=0;p<n;pre[i]++,p++) if(b[(i-p+n)%n]=='1') break;
		for(int p=0;p<n;nxt[i]++,p++) if(b[(i+p)%n]=='1') break;
	}
	for(int i=0;i<n;i++){
		int tot=0;
		memset(mx,0,sizeof(mx));
		for(int p=0;p<n;p++) if(a[p]!=b[(p+i)%n])
			tot++,mx[pre[p]]=max(mx[pre[p]],nxt[p]-i);
		int mn=1e9,cnt=0;
		for(int p=n-1;~p;p--)
			mn=min(mn,cnt+p),cnt=max(cnt,mx[p]);
		ans=min(ans,2*mn+i+tot);
	}
}
int main(){
	scanf("%s%s",a,b);
	n=strlen(a);
	int suma=0,sumb=0;
	for(int i=0;i<n;i++) suma+=a[i]-'0',sumb+=b[i]-'0';
	if(!sumb&&!suma) return puts("0"),0;
	if(!sumb) return puts("-1"),0;
	solve();
	for(int i=0;i+i<n;i++) swap(a[i],a[n-i-1]),swap(b[i],b[n-i-1]);
	solve();
	printf("%d",ans);
	return 0;
}
```


---

## 作者：daniEl_lElE (赞：0)

首先预处理出 $A$ 每个位置想要翻转至少逆时针/顺时针转多少，分别设为 $c_i,d_i$。

考虑最后 $A$ 顺时针移动 $x$ 距离匹配 $B$。可以找到所有需要翻转的位置。每个位置要么逆时针转 $c_i$，要么顺时针转 $d_i$。

考虑双指针，对于每个逆时针转的距离找到最少顺时针转多少。枚举两种转法（先顺再逆/先逆再顺）然后分别找到转到目标状态（即顺时针 $x$）的距离。将所有答案取 $\min$ 即可。

总复杂度 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
#define lowbit(i) (i&(-i))
using namespace std;
int lst[2005],nxt[2005];
vector<int> tagl[2005],tagr[2005];
int cnt[2005],tot,n;
int qdist(int i,int j){
	return min(llabs(j-i),n-llabs(j-i));
}
signed main(){
	string s; cin>>s;
	string t; cin>>t;
	n=s.size();
	bool s0=1,t0=1;
	for(int i=0;i<n;i++) s0&=(s[i]=='0'),t0&=(t[i]=='0');
	if(t0){
		if(s0) cout<<0;
		else cout<<-1;
		return 0;
	}
//	cout<<"OK";
	for(int i=0;i<n;i++){
//		cout<<i<<" ";
		int now=i;
		while(t[now]!='1'){
			lst[i]++;
			now=(now+n-1)%n;
		}
		now=i;
		while(t[now]!='1'){
			nxt[i]++;
			now=(now+1)%n;
		}
	}
//	cout<<"OK";
	int minv=1e9;
	for(int cyc=0;cyc<n;cyc++){
		for(int i=0;i<n;i++) tagl[i].clear(),tagr[i].clear();
		int cg=0;
		for(int i=0;i<n;i++) if(s[i]!=t[(i+cyc)%n]) cg++,tagl[lst[i]].push_back(i),tagr[nxt[i]].push_back(i);
		memset(cnt,0,sizeof(cnt));
		for(int i=0;i<n;i++) for(auto v:tagl[i]) tot+=(!cnt[v]),cnt[v]++;
		int atot=tot;
		minv=min(minv,cg+n-1+qdist(1,cyc));
		int posr=0; for(auto v:tagr[0]) tot+=(!cnt[v]),cnt[v]++;
		for(int i=n-1;i>=1;i--){
			for(auto v:tagl[i]) cnt[v]--,tot-=(!cnt[v]);
			while(tot!=atot){
				posr++;
				for(auto v:tagr[posr]) tot+=(!cnt[v]),cnt[v]++;
			}
			minv=min(minv,min(cg+(i-1)*2+posr+qdist(posr,cyc),cg+posr*2+(i-1)+qdist((n-(i-1))%n,cyc)));
		}
	}
	cout<<minv;
	return 0;
}
```

---

