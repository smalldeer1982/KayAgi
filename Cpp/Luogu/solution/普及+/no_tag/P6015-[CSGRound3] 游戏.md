# [CSGRound3] 游戏

## 题目背景

小 Y 和小 Z 是一对好朋友，他们在玩一个游戏。**游戏只有一个回合**。

## 题目描述

有一个牌堆，一共有 $n$ 张牌，第 $i$ 张牌上有一个数 $a_i$，其中第一张牌是堆顶。

小 Z 先取牌，他可以从堆顶开始取连续若干张牌（**可以取 $0$ 张**），取完的牌拿在手上，也就是不在牌堆里了。

然后小 Y 取牌，同样，她也可以从堆顶开始取连续若干张牌（**可以取 $0$ 张**）。

如果一个人手上的牌的数字和大于 $X$，那么他的分数就是 $0$，否则分数就是数字和。

分数高的人获胜，**如果一样高，则无人获胜**。

小 Z 为了获胜，使用了透视挂，即他知道牌堆里每张牌上写的数。

现在问你对于满足 $1 \leq X \leq K$ 的所有整数 $X$，哪些可以使得小 Z 有必胜策略，即小 Z 取完后，不管小 Y 怎么取都一定会**输**。

## 说明/提示

**【样例解释】**

$X=1,2,3$ 时，小 Z 取一张牌，小 Y 不管怎么取都是零分。

$X=4$ 时，小 Z 如果取 $1$ 张，那么小 Y 取 $1$ 张小 Y 就赢了；否则小 Z 只能是零分。

$X=5$ 时，小 Z 如果取 $1$ 张，那么小 Y 取 $1$ 张小 Y 就赢了；小 Z 如果取了 $2$ 张，小 Y 也取 $2$ 张，平局；否则小 Z 只能是零分。

---

**【数据范围】**

**本题采用捆绑测试。**

- Subtask 1（3 points）：$n = 1$。
- Subtask 2（14 points）：$K= 1$。
- Subtask 3（20 points）：$n,K \le 100$。
- Subtask 4（33 points）：$n , K \le 3333$。
- Subtask 5（30 points）：无特殊限制。

对于 $100\%$ 的数据，$1\leq n,K \leq 10^6$，$1\leq a_i \leq K$。



## 样例 #1

### 输入

```
5
1 4 3 2 2
5
```

### 输出

```
3
1 2 3
```

# 题解

## 作者：StudyingFather (赞：23)

设 $a_i$ 的前缀和为 $s_i$，小 Z 取走了前 $p$ 张牌，小 Y 和小 Z**一共**取走了 $q$ 张牌。

则小 Z 的点数为 $z=s_p$，小 Y 的点数为 $y=s_q-s_p$。

小 Y 为了自己不输，他的点数不能小于小 Z 的点数，但也不能太大（超过上限就不划算了）。最理想的情况是，小 Y 如果少取一张牌，他的点数就小于小 Z 了。

在这种情况下，为了能让小 Z 胜出，只需让上限 $x$ 小于 $y$ 就行。

---

现在问题是对于每个 $p$，我们需要找到相应的 $q$，找到了 $q$，$y$ 就算出来了。

可以二分找，时间复杂度是 $O(n \log n)$ 的。

更快的方式是双指针，即移动 $p$ 的时候，同时将 $q$ 向右移动，直到 $q$ 到达我们需要的位置。时间复杂度为 $O(n)$，比二分的方法更优。

下面是笔者在比赛时写的 $O(n \log n)$ 的二分做法。

```cpp
#include <iostream>
using namespace std;
long long a[1000005],res[1000005];
int main()
{
 ios::sync_with_stdio(false);
 int n,k,ans=0;
 cin>>n;
 for(int i=1;i<=n;i++)
 {
  cin>>a[i];
  a[i]+=a[i-1];
 }
 cin>>k;
 for(int i=1;i<=n;i++)
 {
  if(a[i]>=k)break;
  int p=lower_bound(a+1,a+n+1,2*a[i])-a;
  if(p==n+1||a[p]-a[i]>k)
  {
   res[a[i]]++;
   res[k+1]--;
   break;
  }
  res[a[i]]++;
  res[a[p]-a[i]]--;
 }
 for(int i=1;i<=k;i++)
 {
  res[i]+=res[i-1];
  if(res[i])ans++;
 }
 cout<<ans<<endl;
 for(int i=1;i<=k;i++)
  if(res[i])cout<<i<<' ';
 return 0;
}
```


---

## 作者：Hexarhy (赞：13)

一道好题，不涉及高深算法，主要练练思维。给出题人赞一个。

但是考场上想到 AC 做法真不容易。

而且细节还非常多。我 debug 了好久啊……

----------

### 解题思路

为了方便，姑且把小 Z 叫做我方，小 Y 叫做对方。且某些变量的范围如果显然则不写明。

乍一看没头绪？先抓住游戏的特点来分析。

注意只有**一个回合**，就是我方摸一次，对方摸一次就停止。

首先看看**不取**的情况：

我方不取，分数为 $0$。而 $0$ 已经是最低分，要么平局要么输，我方一定不会赢。**因此不必考虑不取的情况。**

----------

接着看到**连续**取牌——想到了区间和。
 
那么记 $S_{i,j}$ 表示区间 $[i,j]$ 数列 $a$ 的和。

由于**连续**取牌，若我方取 $x$ 张牌，对方随后取了$y$，则我方点数和为 $S_{1,x}$，对方点数和为 $S_{x+1,y}$。此时双方共取牌 $x+y$ 张，总共和为 $S_{1,y}$。

由于只有两人取牌，显然有下列式子：

$$S_{1,y}=S_{1,x}+S_{x+1,y}$$

即，

$$S_{1,y}-S_{1,x}=S_{x+1,y}$$

获胜条件可以表示为下列式子：

$$0\le S_{x+1,y}< S_{1,x}\le X\le K$$

**注意一句话：**

> 如果一样高，则无人获胜。

**明确本题要求的是我方必赢，因此平局算输**。注意原式的等号。

简单变形一下（省略某些条件）：

$$S_{1,y}-S_{1,x}< S_{1,x}\le X$$

即，

$$\begin{cases}S_{1,y}< 2S_{1,x} \\ S_{1,x}\le X\le K \end{cases}$$

别忘了，当 $S_{1,y}-S_{1,x}>X$ 时，也是我方获胜。

------------

那么现在尝试通过某种算法来满足上述条件。

$S$ 可以预先用**前缀和**求出，时间复杂度 $O(n)$。

对于 $x$，可以枚举不超过 $K$ 的 $S_{1,x}$，时间复杂度 $O(n)$。

对于 $y$，显然如果还用枚举，总时间复杂度达到 $O(n^2)$，果断舍弃。

但是别忘了，前缀和具有**单调性**。考虑二分查找 $y$。

如果存在 $y$ 满足 $S_{1,y}\ge 2S_{1,x}$ 且 $S_{1,y}-S_{1,x}\le X$ 的，那么我方必定不赢，这不是我们想要的取牌方案。

否则，不存在 $y$ 能使对方获胜。接下来就简单的讨论一下 $y$ 的情况，来决定 $X$ 所在的取值范围。

- 肯定的是，对于 $S_{1,y}=2S_{i,x}$，不考虑即可。因为这是平局，我方不能赢。

- 那么如果 $S_{1,y}<2S_{1,x}$，在 $[S_{i,x},1,K]$ 的范围内的整数，都是我们想要的 $X$。

- 如果是$S_{1,y}>2S_{1,x}$，那么在 $[S_{1,x},\min \{S_{1,y}-S_{1,x},K+1\})$ 的范围内的整数，也都是我们想要的 $X$。我们只需要让 $S_{1,y}-S_{1,x}>X$，变为 $0$ 分即可。

**注意上述区间的左右端点。**

那么，如果忽略统计答案时的时间复杂度，则为 $O(n\log n)$。~~实际上有点玄学~~

----------

### 另一种思路

![](https://cdn.luogu.com.cn/upload/image_hosting/pmbck196.png)

事实上，在前缀和单调性的基础上，我们可以采取比二分更快的方法——$\text{two-pointers}$。

因此正解时间复杂度为 $O(n)$。

详细内容请~~出门右转~~看其他地方的题解。

---------

### 实现细节

大部分是关于 STL 使用的，如果您不使用 STL 可略过。

- 在上述思路中，显然我们**不能保证统计的答案数组的是有序的且不重复**。那么必须使用桶记数或者用`vector`在`sort()`过后用`unique()`去重并用`erase()`删除多余元素。当然可以直接用`set`，但是复杂度会加多一个 $\log$，因为其内部是平衡树实现的。这里使用`vector`。

- 上述 STL 函数都是**左闭右开**。这是应有的常识。

- 建议前缀和开`long long`。

- 请注意二分时，如果采用 STL，请使用`lower_bound()`而非`upper_bound()`。因为如果使用后者，**平局的情况会被认为是** $S_{1,y}<2S_{1,x}$，返回值两者均为“未找到”。

- 使用`lower_bound()`，返回值“未找到”**并不总是**容器的`end()`，而是填入参数的第二项。具体见代码。

- `unique()`只能**移动连续**的重复元素到容器**末尾**，使其不重复，并不能做到完全去重或删除。因此需要先`sort()`排序后再`erase()`。

- 由于使用了大量的 STL，且读入较多，请务必**开启 O2 优化**。两者实际运行时间相差极大！

附：[开了 O2 的评测记录](https://www.luogu.com.cn/record/29836402) 和 [不开 O2的评测记录](https://www.luogu.com.cn/record/29836417)。

-----------

### 参考代码

~~丑陋码风以及压行请见谅~~

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
ll n,k;
vector<ll> ans;
int main()
{
	scanf("%lld",&n);
	vector<ll> a(n+2),s(n+2);//动态开数组
	for(ll i=1;i<=n;i++)
	{
	 	scanf("%lld",&a[i]);
		s[i]=s[i-1]+a[i];//求出前缀和
	}
	scanf("%lld",&k);
	for(ll x=1;x<=n && s[x]<=k;x++)
	{
		const auto iter=lower_bound(s.begin()+1,s.begin()+1+n,s[x]*2LL);//二分
		for(ll i=s[x];i<=k && (iter==s.begin()+1+n?true:i<*iter-s[x]);i++)//这里压行了，文末有解释
		 ans.push_back(i);
	}
    //下面是处理ans数组。
	sort(ans.begin(),ans.end());
	ans.erase(unique(ans.begin(),ans.end()),ans.end());
	printf("%lld\n",ans.size());
	for(auto i:ans)
	 printf("%lld ",i);
	return 0;
}
```
**部分代码解释**

```cpp
for(ll i=s[x];i<=k && (iter==s.begin()+1+n?true:i<*iter-s[x]);i++)
```
这句话通过`?:`来实现上文的分类讨论。

在上文中，可以发现两种情况的区间 $[S_{i,x},1,K]$ 以及 $[S_{1,x},\min \{S_{1,y}-S_{1,x},K+1\})$ 下界是一样的。

因此只需改变上界即可。而且无论是哪两种情况，都必须要保证 $X\le K$。

当然为了方便，你依然可以分开打代码。

---

## 作者：Sai0511 (赞：10)

发一个我比赛时瞎搞的做法...   
我可能是全世界唯一一个用了二次二分$+$二次枚举的人，  
如果不是全场最慢我女装。   
对于一个$\text{X}$，我们可以在$O(\text{log}n)$的时间复杂度内用二分算出小$\text{Z}$可以取到的最多的牌。  
接下来有一个贪心：那就是小$\text{Y}$**一定**取他可以取到的最多的牌。($\forall \text{a}_i \geq1$，故正确性显然)。这个值也可以用二分在$O(\text{log}n)$ 的时间复杂度内求出来。    
然后我们就有一个可以过前$\text{4}$个$\text{subtasks}$的做法，可以获得$\text{70}$分的高分：枚举小$\text{Z}$选了几张牌，然后二分求出小$\text{Y}$选了几张牌，两个值比较一下，如果小$\text{Z}$的分高于小$\text{Y}$的分，那$\text{X}$就是一个答案。   
考虑满分做法：  
~~通过观察得知~~，有一个神奇的性质：若$\text{X}$可行，设当前小$\text{Z}$取了$\text{p}$张牌，$p$**一定大于$\text{X}-\text{1}$时小$\text{Z}$失败时取得最大牌数$\text{q}$。**  
为什么？因为在$\text{X}-\text{1}$时小$\text{Z}$都失败了，到了$\text{X}$时小$\text{Y}$取的牌只会**单增不减**，故**一定失败**。  
加上这个优化就可以通过了。  
代码：  
```cpp
#include <bits/stdc++.h>

typedef long long ll;
const int N = 1e6 + 10;
int n, m, i, j, k, tot, p;
ll sum[N], ans[N];

int main() {
  scanf("%d", &n);
  for (int i = 1, a; i <= n; i++) scanf("%d", &a), sum[i] = sum[i - 1] + a;
  scanf("%d", &k), p = 1;
  for (int x = 1; x <= k; x++) {
    int l = 1, r = n, posA = 0;
    while (l <= r) {
      int mid = (l + r) >> 1; 
      ll s = sum[mid];
      if (s <= x) posA = mid, l = mid + 1;
      else r = mid - 1; 
    }
    bool flag = 1;
    for (int i = p; i <= posA; i++) {
      ll scoreA = sum[i];
      l = i + 1, r = n; int posB = 0;
      while (l <= r) {               
        int mid = (l + r) >> 1; 
        ll s = sum[mid] - sum[i];
        if (s <= x) {
          posB = mid, l = mid + 1;
          if (s >= scoreA) break;
        } else r = mid - 1; 
      }
      ll scoreB = posB == 0 ? 0 : sum[posB] - sum[i];
      if (scoreA > scoreB) { flag = 0; p = i; ans[++tot] = x; break; }
    }
    if (flag) p = posA;
  }
  printf("%d\n", tot);
  for (int i = 1; i <= tot; i++) printf("%d ", ans[i]);
  return 0;   
}
```

---

## 作者：YellowBean_Elsa (赞：7)

## 好坑啊啊啊！！！

这题思路比较比较简单，就是坑有点多。

想象小Z取得牌从顶到第i张，我们可以算出X在某一个连续区间中时，小Z必胜

然后把这些区间求个并集就行了

**（区间求并细节好多啊比赛时差点没调出来QwQ，结果把第四题时间给占完了）**

直接看代码吧，有详细注释

```cpp
//coder: FeliksYB, an AKer of IMO
//Orz std::sacredYukiJZY
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e6+5;
inline int read(){
	int x=0;char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
	return x;
}inline ll Max(ll x,ll y){
	if(x>y)return x;
	return y;
}inline ll Min(ll x,ll y){
	if(x<y)return x;
	return y;
}int n,a[N];
ll sum[N];//前缀和 
ll mn[N],mx[N],ans;
ll k;
struct segment{
	ll l,r;
	bool operator < (const segment &A)const{
		if(l!=A.l)return l<A.l;
		return r<A.r;
	}
}seg[N];//区间（见下文） 
int cnt,p=1;
ll L,R;
bool avl[N];//一个数是否可行 
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		sum[i]=sum[i-1]+a[i];
	}k=(ll)read();
	for(int i=1;i<=n;i++){//对于小Z取前i张牌时，哪段区间可作为X; 
		mn[i]=sum[i];//不能让小Z被清0
		//二分找到第一个使小Y牌数字和更大（或相等）的位置，
		//要使这个位置一取到就 > X，清0; 
		int j=lower_bound(sum+1,sum+n+1,(sum[i]<<1))-sum;
		if(j==n+1)mx[i]=k;//如果全取也不行，就把区间右端点赋成最大 
		else mx[i]=Min(k,sum[j]-sum[i]-1);//不要让区间超出k 
	}//把区间整理成结构体，按左端点小到大排序 
	for(int i=1;i<=n;i++){
		if(mn[i]>mx[i] || mn[i]>k)continue;
		seg[++cnt].l=mn[i];
		seg[cnt].r=mx[i];
	}//特判 
	if(cnt==0){
		puts("0");
		return 0;
	}sort(seg+1,seg+cnt+1);
	//区间并集板子
	//L，R记录并起来的一段连续区间两端点 
	while(p<=cnt){
		L=seg[p].l,R=seg[p].r;p++;
		while(p<=cnt && seg[p].l<=R)R=Max(R,seg[p++].r);
		for(int j=L;j<=R;j++)avl[j]=1,ans++;
	}printf("%lld\n",ans);
	for(int i=1;i<=k;i++)
		if(avl[i])printf("%d ",i);
	return 0;
}
```


---

## 作者：littleKtian (赞：6)

~~这是……黑杰克？（~~

------------------------------

考虑对于每种小 Z 取牌的方案，有多少个 $X$ 使得小 Z **必胜**

记 $p[i]=\sum_{j=1}^ia[j]$，$t$ 为所有满足 $p[t]-p[i] \geq p[i]$ 的正整数中最小的一个

可以发现所有在 $\Big[p[i],p[t]-p[i]\Big)$ 区间内的 $X$ 都满足要求（此时小 Z 分数即为 $p[i]$，如果小 Y 取牌数小于 $t-i$，得分就会小于小 Z，否则就会爆牌导致小 Y 得分为0，不管怎样小 Z 一定获胜）

最终答案就是所有区间的并集

因为在枚举 $i$ 的过程中 $t$ 只会向后移动，所以可以用二分或者从上一次的位置直接向后移动

求区间的并集可以利用差分解决

注意特判 $t > n$ 的情况

复杂度 $O(n\log n)$ 或 $O(n)$（取决于找 $t$ 的方式）

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,x[2000005],t,tot,ans[1000005];
ll k,p[1000005];
ll dr()
{
	ll xx=0;char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')xx=(xx<<1)+(xx<<3)+ch-'0',ch=getchar();
	return xx;
}
int main()
{
	n=dr();
	for(int i=1;i<=n;i++)p[i]=p[i-1]+dr();
	k=dr(),t=0;
	for(int i=0;i<=n;i++)
	{
		if(p[i]>k)break;
		while(t<=n&&p[t]<(p[i]<<1))++t;
		++x[p[i]];if(t<=n)--x[p[t]-p[i]];
	}
	for(int i=1;i<=k;i++)
	{
		x[i]+=x[i-1];
		if(x[i])ans[++tot]=i;
	}
	printf("%d\n",tot);
	for(int i=1;i<=tot;i++)printf("%d ",ans[i]);
}
```


---

## 作者：xh39 (赞：5)

100pts做法是37pts的优化,所以请先看37pts

在本篇题解中,没有考虑不取的情况。因为如果第一个人不取,第二个人也可以不取,所以就达成了平局。没有必胜策略。

当然是暴力枚举x,以及第一个人和第二个人分别取到的多少。

计算区间和需用到前缀和。所以请先学习前缀和。

代码中为了计算前缀和和其它操作方便,数组下标从1开始。

37pts.code: //时间复杂度不固定,所以只被卡了3个点(#14,#15,#28)。但由于那捆绑测试,仍然只有37分。
```cpp
#include<iostream>
using namespace std;
int a[1000005],s[1000005];
int kkksc03[1000005],top=0;
int main(){
	int n,i,j,k,kk,Max=0; //kk才是题目中的k,程序中的k是循环控制变量。
	cin>>n;
	for(i=1;i<=n;++i){
		scanf("%d",a+i);
		s[i]=s[i-1]+a[i]; //计算前缀和。
	}
	cin>>kk;
	for(i=1;i<=kk;++i){ //i枚举x
		for(j=1;j<=n;++j){ //j枚举第一个人从1取到k。
			if(s[j]>i){ //优化,题目保证a[i]>=1,如果已经超过了,再进行数值更大了,还会>i,再继续也没意义了。
				break;
			}
			Max=0; //赋一个极小值。
			for(k=j+1;k<=n;++k){ //枚举第二个人。
				if(s[k]-s[j]>i){ //已经超过,优化,同上。
					break;
				}
				Max=max(Max,s[k]-s[j]); //采取第二个人的最优方式来跟第一个人比,如果比过了,才算有必胜策略。
			}
			if(s[j]>Max){
				kkksc03[top++]=i; //先把答案丢到一个数组里面,因为我们要提前输出答案个数。
				break;
			}
		}
	}
	cout<<top<<endl;
	for(i=0;i<top;++i){
		printf("%d ",kkksc03[i]);
//		cout<<kkksc03[i]<<" ";
	}
	cout<<endl;
	return 0;
}
```
然后,我们会发现,随着x的增长,第一个人取的牌不会减少,所以我们枚举j的时候,j不应该从0开始,而是从上一次的开始。

优化过后,有了70pts

我们又发现,随着j的增长,如果k肯定也会随之而上升(至少不下降)。所以k也不应该从头开始枚举。

因为j,k递增,所以虽然有3重循环,可时间复杂度为O(k)。

100pts.code: //大部分注释都在37pts.code里面了,这里就不再多说。只补充了小部分注释。
```cpp
#include<iostream>
using namespace std;
int a[1000005],s[1000005];
int kkksc03[1000005],top=0;
int main(){
	int n,i,j=1,k=2,kk,Max=0; //j,k记得初始化。这是数组下标从1开始的初始化。
	cin>>n;
	for(i=1;i<=n;++i){
		scanf("%d",a+i);
		s[i]=s[i-1]+a[i];
	}
	cin>>kk;
	for(i=1;i<=kk;++i){
		for(;j<=n;++j){
			if(s[j]>i){
				--j; //因为这个不符合要求,所以肯定要减少1,才能符合要求,继续枚举。
				break;
			}
			Max=0;
			for(;k<=n;++k){
				if(s[k]-s[j]>i){
					--k; //不符合要求,同上。
					break;
				}
				Max=max(Max,s[k]-s[j]);
			}
			if(s[j]>Max){
				kkksc03[top++]=i;
				break;
			}
		}
	}
	cout<<top<<endl;
	for(i=0;i<top;++i){
		printf("%d ",kkksc03[i]);
//		cout<<kkksc03[i]<<" ";
	}
	cout<<endl;
	return 0;
}
```
虽然我没有严谨的证明,但我希望大家都看懂了。

---

## 作者：chenxinyang2006 (赞：3)

这道题还是挺有意思的，看似是个博弈题，竟然关联到了差分

易发现以下几点：

* 小Z拿的牌一定是序列的一个**前缀**

* 小Z有必胜策略，当且仅当去掉小Z拿的牌后，**最大**的一个和$\le x$的前缀，和比小Z拿的牌小

* 若小Z的分数为0，那么他必定不赢，所以**拿的前缀和$\le x$**

然后70分就到手了，枚举每一个$x$，然后枚举每一个前缀，二分出最大的小Y拿的区间，时间复杂度$O(nk\ log(n))$

然后怎么做呢？

一开始我认为，小Z拿的前缀一定是最大的，结果就是：

![](https://cdn.luogu.com.cn/upload/image_hosting/uuhrlapb.png)

所以，对于每个$x$，小Z的前缀选了哪个并没有什么规律

但是，一共也只有$n$个前缀，是否可以从这里入手呢？

对于每个前缀，由于不知道$x$是多少，所以我们无法确定小Y的和最大是多少。但是我们可以知道，这个前缀面对小Y的哪一些选择会赢，这个可以二分得到

接下来，我们需要知道在那些$x$下，小Y最优只能选这个。这样，对于这些$x$，这个前缀可以使小Z必胜

假设当前的前缀是$[1,i]$，$sum(i + 1,j) < sum(1,i)$且$j$最大

$j$是小Y的最优选择，仅当$sum(i + 1,j + 1) > x$

反过来，$x < sum(i + 1,j + 1)$，这样就有了$x$的上界

$x$的下界也很显然，是$max(sum[1,i],sum[i + 1,j])$，根据定义，$sum(1,i) > sum(i + 1,j)$，所以$sum[1,i] < x$

这样遍历每个前缀，我们就有了一些区间，表示在这些区间内的$x$必胜

然后怎么判断$x$被不被覆盖呢？

~~我会线段树！线段树NB！~~

由于本题数据$10 ^ 6$，线段树显然会死，简化一下目前的问题：

给一个长为$k$的序列，$n$次区间加，加完后$k$次单点查询

这个显然可以差分一下，设$v_i$是答案序列，$c_i = v_i - v_{i - 1}$

那么区间$[x,y]$加$k$，实际上就是$c_x += k,c_{y + 1} -= k$(根据定义得到，十分显然)

最后查询的时候，前缀和还原一下就行了

```cpp
#include <cstdio>
#define min(a,b) (((a) < (b)) ? (a) : (b))

namespace IO{
	inline void read(int &x){
		x = 0;
		char ch = getchar();
		while(ch < '0' || ch > '9') ch = getchar();
		while(ch >= '0' && ch <= '9'){
			x = x * 10 + ch - '0';
			ch = getchar();
		}
	}
	void W(int x){
		if(x > 9) W(x / 10);
		putchar(x % 10 + '0');
	}
	inline void write(int x){
		if(x < 0){
			putchar('-');
			x = -x;
		}
		W(x);
	}
};
using namespace IO;

#define ll long long
int n,k;
int a[1000005];
ll pre[1000005];
int c[1000005],b[1000005];

int cnt;
int ans[1000005];

int main(){
	read(n);
	for(int i = 1;i <= n;i++){
		read(a[i]);
		pre[i] = pre[i - 1] + a[i];
	}
	pre[n + 1] = 1ll << 63;//显然，如果j = n，那么x根本没有上界，所以用一个很大的数代替
	read(k);
	int j = 0;
	for(int i = 1;i <= n;i++){
		while(pre[j + 1] - pre[i] < pre[i] && j + 1 <= n) j++;//双指针法，显然对于每个i，j是不减的，所以每次可以在上次的基础上暴力往右边找，复杂度正确，均摊O(1)
		if(pre[i] <= k){
			c[pre[i]]++;
			c[min(pre[j + 1] - pre[i] - 1,k) + 1]--;
		}
		//区间加(pre[i],pre[j + 1] - pre[i] - 1)
	}
	for(int i = 1;i <= k;i++){
		b[i] = b[i - 1] + c[i];
		if(b[i] > 0) ans[++cnt] = i;
	}
	write(cnt);
	putchar('\n');
	for(int i = 1;i <= cnt;i++){
		write(ans[i]);
		putchar(' ');
	}
	return 0;
}
```

本题输入$10 ^ 6$个数，输出$10 ^ 6$个数，建议使用快速IO板子

---

## 作者：Lskkkno1 (赞：1)


### 题目概述

给定长度为 $n$ 的一个数列，两个人依次进行**一次**操作（只进行一次）

每次操作选择一段**前缀**（拿出来），并且前缀和不能大于 $X$

问对于所有的 $X \le K$，有哪些$X$，满足存在一种方案，使得第一个人取出来的**前缀和**大于第二个人取出来的**前缀和**

$n, K \le 10^6$

### 正解

发现到 $n$，$K$ 都很大，如果依次确定每一个 $X$ 好像不太可行

考虑通过两个人选择的位置来决定 $X$ 范围

设第一个人选择的位置是 $l$，第二个人选择的位置是 $r$，($l \le r$，第二个人取牌的位置要在第一个人后面)

第一个人拿出来牌的前缀和是 $psum_l$，第二个人拿出来牌的前缀和为 $psum_r$

按照题意必须要满足 $psum_r - psum_l < psum_l$，即第二个人取出来的前缀和要小于第一个人的前缀和

选定的 $l$ 其实是确定了 $X$ 的一个**下界**，而上界则是 $r$ 来确定的

由于第二个人肯定是要选到最大的位置的，而且还不能比 $X$ 大，所以 $r$ 是再选一个都要大于 $X$ 的，或者说 $r = n$

则 $X$ 满足 $psum_l \le X \le psum_{r+1} - psum_l - 1$

对于每一个 $l$，都能确定一个最大的 $r$，且 $r$ 满足单调性 ：即 $l$↑，$r$↑

统计答案时，确定了可行的 $X$ 的范围后可以**开桶差分**来标记答案

$\color {DeepSkyblue} Code$

```cpp
#include <bits/stdc++.h>
#define N 1000005

using namespace std;

int n, k;
int dif[N];
long long psum[N];

inline int read() {
	int x = 0; char ch = getchar();
	while(!isdigit(ch)) ch = getchar();
	while(isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	return x;
}

int main() {
	n = read();
	for(int i = 1; i <= n; ++i)
		psum[i] = read() + psum[i - 1];
	k = read();
	
	for(int l = 1, r = 1; l <= n && psum[l] <= k; ++l) {
		while(r < n && psum[r + 1] - psum[l] < psum[l])
			++r;
		if(r == n) {
			++dif[psum[l]];
			break;
		}
		int cl = psum[l], cr = psum[r + 1] - psum[l] - 1;
		if(cl <= cr) {
			++dif[cl];
			if(cr + 1 <= k) --dif[cr + 1];
		}
	}
	
	int ans = 0;
	for(int i = 1; i <= k; ++i) {
		dif[i] += dif[i - 1];
		if(dif[i]) ++ans;
	}
	
	printf("%d\n", ans);
	for(int i = 1; i <= k; ++i)
		if(dif[i])
			printf("%d ", i);
	putchar('\n');
	return 0;
}
```

---

## 作者：万万没想到 (赞：1)

原题传送门：[P6015 游戏](https://www.luogu.com.cn/problem/P6015)

## 题目简介
给出 $n$ 个元素，和上限 $k$ 。求出对于$1 \leq X \leq K$中，所有能够有一种方法对于取两段连续的元素，第一段从第一个元素开始取，第二段从第一段后面一个元素开始取，第二段元素和永远小于第一段元素和。注意：两段的元素都需要小于等于 $X$ ，并且只需要满足有一种第一段的取法符合要求的 $X$ 即可。

数据范围：对于 $100\%$ 的数据， $1 \leq n,K \leq 10^6,1 \leq a_i \leq K$。 

## 解题思路：

我们会想到两段的边界情况，设第一段为 $sum1$ ，第二段为 $sum2$ ，则边界为 $min( sum2 ) \geq sum1$ ，意思为第二段比第一段大的最小的非法情况，那么 $max(sum2) < sum1$ 就是此时的最大合法情况。

这时，我们就会想到，对于此 $sum2$ ，再减去一，就是合法情况，就是合法的 $X$ 。同理， $sum1$ 也是合法情况，那么答案就是区间 $(sum1,sum2-1)$ 。

至此，我们就找到了正解，对于 $sum1$ 进行枚举 $n$ 次，对于 $sum2$ 就从上一个 $sum1$ 的 $sum2$ 继续算，对于记录合法解，笔者用的是差分，时间复杂度约为 $O(n)$ 。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[1000005],ans,vis[1000005];
long long sum[1000005];
int main(){
	scanf("%d",&n);
	for(register int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		sum[i]=sum[i-1]+a[i];
	}
	scanf("%d",&k);
	int head=1,tail=1;
	long long sum1=a[1],sum2=a[1];
	for(register int i=1;i<=n;++i){
		sum1=sum[i],head=i,sum2-=a[i];
		if(sum1>k)break;
		while(tail<=n&&sum[tail]-sum[head]<sum1)++tail;
		sum2=sum[tail]-sum[head];
		vis[sum1]++,vis[sum2]--;
	}
	for(register int i=1;i<=k;++i){
		vis[i]+=vis[i-1];
		if(vis[i]>0)++ans;
	}
	printf("%d\n",ans);
	for(register int i=1;i<=k;++i){
		if(vis[i]>0)printf("%d ",i);
	}
	printf("\n");
	return 0;
}
```


---

## 作者：老咸鱼了 (赞：1)

从题面可以看出来这是一个枚举题，但是如果每次都重新直接从头到尾枚举会超时，所以我们要从上一次枚举的截至的状态开始。

注意题目说的可以不选，这就意味着小Z可以不拿满。所以我们也要枚举一下小Z没拿满的情况。

时间复杂度大约是O(n+T)
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,s,t,T;
int a[1111111],sa,sb,j,k,ans;
bool vis[1111111]={0};
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	scanf("%d",&T);
	for(int i=1;i<=T;i++){
		while(1){			
			while(k<=n&&sb+a[k+1]<=i){
				k++;sb+=a[k];
			}
			if(sa>sb){//只要存在一种小Z比小Y大的情况就可以了，因为我们是从少往多枚举的，所以不用担心会出现没有枚举到的情况。
				vis[i]=true,ans++;break;
			}
			if(j>n||sa+a[j+1]>i)
			break;
            j++;
            sa+=a[j];
            sb-=a[j];//因为小Z拿了所以小Y就不能拿了，又因为是从头到尾枚举，所以减去这个值就相当于小Y不能拿这个了。
		}
	}
	printf("%d\n",ans);
	for(int i=1;i<=T;i++)
	if(vis[i])printf("%d ",i);
	return 0;
}
```

---

## 作者：KillerXu (赞：0)

这题做法好像还挺多的，简单讲讲几个比赛时想出的思路。

最暴力的思想是$O(n^3)$枚举，枚举$X$，枚举小Z取的牌，枚举小Y取的牌，可以通过前三个$subtask$。

然后想到一个假贪心，枚举$X$，然后小Z在不超过$X$的情况下尽可能取大，小Y也在不超过$X$的情况下尽可能取大，复杂度是$O(n^2)$，但显然这个贪心正确性是没有保证的，实际得分大概$30$左右。

接着想到结合上述两种思想，**首先一切取牌都满足小Z和小Y取牌价值总和不超过K**，先去枚举小Z取的牌，我们记取到的牌价值总和为$sum1$，然后记小Y取的牌价值总和为$sum2$，存在 $sum1 < sum2$ 和 $sum1 > sum2$两种情况。

依然先贪心一下，小Y还是去找找有没有超过小Z的机会：

如果没有，那么我们记录下最大的满足 $sum1 > sum2$ 的$sum2$，此时，我们只要保证小Z的价值不爆成$0$，即当$sum1 \le X \le K$时，小Z必胜。

如果有，那么我们记录下**最小的**满足 $sum1 < sum2$ 的 $sum2$，此时，我们只要让小Y爆成$0$，即当$sum1 \le x < sum2$时，小Z必胜。

复杂度最差是$O(n^2)$，我们观察到，$sum1$单调递增，所以每次小Z多取一张，小Y必定比上次取更多的牌，所以用一下尺取法，每次直接从小Y上次所取的最后一张牌向后枚举，再配合前缀和即可。

```cpp
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <algorithm>

#define N 1000005

using namespace std;

int a[N];
int n , k;
int b[N];

long long sum[N];
int ans = 0;

int main(){
    cin >> n;
    for(int i = 1; i <= n; i++) { scanf("%d" , &a[i]); sum[i] = sum[i - 1] + a[i]; }
    cin >> k;
    int tot1 = 0;
    int j = 2;
    for(register int i = 1; i <= n; i++){
            if(tot1 + a[i] > k) break;
            tot1 += a[i];
            int tot2 = 0 ,flag = 0;
            for(;j <= n; j++){
                  if(sum[j] - sum[i] > k) {flag = 1; break;}
                  if(sum[j] - sum[i] >= tot1) break;
            }
            if(flag) j--;//注意一下这个地方，已经超出K了再跳出，所以只能取到上一张
            tot2 = sum[j] - sum[i];
            if(tot2 < tot1) for(int j = tot1; j <= k; j++) b[j] = 1; else
            for(int j = tot1; j < tot2; j++) b[j] = 1;
    }
    
    for(int i = 1; i <= k; i++) if(b[i]) ans++;
    cout << ans << "\n";
    for(int i = 1; i <= k; i++) if(b[i]) cout << i << " ";
    return 0;
}
                    
                    
                    

```

---

## 作者：BFqwq (赞：0)

# P6015
~~比赛的时候三秒出思路，调了一个小时qaq~~
## 特判
当 $n=1$ 的时候，小Z的最佳策略一定是拿走，因此只要 $X>=a_1$ 就有必胜策略。

当 $K=1$ 的时候，除非第一张牌是 $1$ 且第二张牌不是 $1$ 或者只有 $1$ 张牌必胜。
## 非正解
看到这道题，第一想法一定是枚举 $X$ （虽然我不是）。

当 $X$ 已知的时候，我们可以考虑小Z拿几张牌。显然小Z的数字不能超过 $X$。

然后对应的去寻找，对于每一个小Z的数字，小Y是否有可能拿到比小Z多且不超过 $X$ 的数字。

不妨令小Z，小Y的数字分别为 $sum_z$ 和 $sum_y$，

就转化成
$$\exists sum_{z1} \leq X \ \operatorname{s.t.}\forall sum_y \in [1,sum_{z1})\cup(X,+\infty)$$

不过由于需要枚举 $X$ 顾复杂度会达到 $\operatorname{O}(Kn^2)$ （理论上界），能过Subtask 3。

## 优化
我们可以使用一个前缀和进行处理，

令 $i$ 位置的前缀和为 $sum_i$，那么 $sum_y$ 的计算就成为了

$$sum_y=sum_i-sum_{z1}$$

显然，对于 $sum_y$ 的寻找，是具有单调性的。

我们只需要找到一个不能满足条件的 $sum_y$，也就是 $\exists sum_{z1}\le sum_{y1}\le X$，

就可以宣告这一个 $sum_{z1}$ 不满足条件。

那么我们可以考虑将查找的过程二分（因为在前缀和之后 $sum_y$ 单调）。

这样复杂度上界就变成了 $\operatorname{O}(Kn\log n)$，也许可以过Subtask 4。
## 正解
那么显然，这个题枚举 $X$ 这条路行不通。

这个时候我们就考虑枚举 $sum_z$。

对于每个 $sum_z$，显然存在某个 $sum_{y1},sum_{y2} \operatorname{s.t.}sum_{y1}<sum_{z}\le sum_{y2}$。

（其中 $sum_{y1}$ 与 $sum_{y2}$为两个相邻的前缀，也就是 $sum_{y1}$ 小Y会输且再往后加一个数就小Y会赢了）

那么如果 $X\in [sum_z,sum_{y2})$，也就是 $sum_{y2}$ 爆了，

那么相当于 $sum_z$ 就成了一个必胜的数。

特别的，要是小Y取完了剩下的所有牌都超不过 $sum_z$，则 $X\in [sum_z,K})$就都有必胜策略了。

然后再用一个前缀和记录一下可行的 $X$。

对于查询 $sum_{y1}$ 我们可以使用二分，这样的复杂度就是 $\operatorname{O}(n\log n)$，就可以过了。

不过我们发现当 $sum_z$ 增大时 $sum_{y1}$ 只会增大不会减小，

所以我们还可以使用双指针来维护，

减小码量，并将复杂度降为 $\operatorname{O}(n)$。

## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	register int x=0;
	register bool f=0;
	register char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return f?-x:x;
}
void write(int x){
    if(x<0) putchar('-'), x=-x;
    if(x>=10) write(x/10);
    putchar('0'+x%10);
}
const int maxn=1000005;
int num[maxn],sum[maxn],n,k,sum1,sum2,r,ans;
signed main(){
	n=read();
	for(int i=1;i<=n;i++) num[i]=read();
	k=read();
	sum2=num[1];r=2;
	if(n==1){
		for(int i=num[1];i<=k;i++) ans++;
		cout<<ans<<endl;
		for(int i=num[1];i<=k;i++)printf("%d ",i);
		return 0;
	}
	//if(sum2!=1) sum[1]++,sum[sum2]--;
	for(int i=1;i<=n;i++){
		sum1+=num[i];sum2-=num[i];
		while(r<=n&&sum2<sum1){
			sum2+=num[r];r++;
		}
		//cout<<i<<" "<<r<<" "<<sum1<<" "<<sum2<<endl;
		if(sum1<sum2){
			sum[min(sum1,k+1)]++;sum[min(k+1,sum2)]--;
			//cout<<min(sum1,k+1)<<" "<<min(k+1,sum2)<<endl;
		}
		if(sum1>sum2&&r==n+1){
			//cout<<min(sum1,k+1)<<endl;
			sum[min(sum1,k+1)]++;
		}
		//if(sum1>=k) break;
	}
	for(int i=1;i<=k;i++){
		sum[i]+=sum[i-1];
		if(sum[i]>0) ans++;
	}
	printf("%d\n",ans);
	for(int i=1;i<=k;i++){
		if(sum[i]>0) printf("%d ",i);
	}
	return 0;
}
```














---

## 作者：Yt_pY (赞：0)

### 题意：

两个人分别取两次剩余序列的前缀，且前缀和小于等于 $X$。问有多少个 $X$ 使得：第一次一定存在一个前缀，取掉之后第二个前缀一定小于它。

### 题目分析：

前 70 分不多说了，主要是最后的 30 分非常厉害。

这道题最重要的就是这步转化：

枚举 $X$，判断是否有一个前缀有必胜策略（70分）
$\rightarrow$ **枚举前缀，找有哪些满足条件的 $X$**（100分）。

关键代码：

```
for(int i=1;i<=n;i++)
{
	if(s[i]>k)break;
	if(s[n]-s[i]<s[i])
	{
		c[s[i]]++;
		continue;
	}
	int p=lower_bound(s+1,s+n+1,2*s[i])-s;
	c[s[i]]++,c[s[p]-s[i]]--;
}
```

$s$ 是前缀和数组，$c$ 是 $X$ 能取得范围的差分数组。

- 如果 $s[i]>k$，说明不能再选前缀了，直接 break。

- 如果当前的前缀使得：剩下的数全取也不能大于它，说明 $X$ 从 $s[i]$ 开始都可以取。

- 不然就用二分，找出第一个位置 $p$ 使得 $s[p]-s[i]\ge s[i]$ ，如果 $X$ 取了大于等于 $s[p]-s[i]$ 的数，则第二个前缀就可以在不大于 $X$ 的情况下大于等于第一个前缀，没有必胜策略。所以此时 $X$ 的范围就是 $[s[i],s[p]-s[i])$。

差分之后统计答案即可。

### 完整代码：
```
#include<bits/stdc++.h>
#define maxn 1000005
#define ll long long
using namespace std;
int n,k;
ll a[maxn],s[maxn];
int c[maxn],ans[maxn],num;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		s[i]=s[i-1]+a[i];
	}
	scanf("%d",&k);
	for(int i=1;i<=n;i++)
	{
		if(s[i]>k)break;
		if(s[n]-s[i]<s[i])
		{
			c[s[i]]++;
			continue;
		}
		int p=lower_bound(s+1,s+n+1,2*s[i])-s;
		c[s[i]]++,c[s[p]-s[i]]--;
	}
	for(int i=1;i<=k;i++)c[i]+=c[i-1];
	for(int i=1;i<=k;i++)
		if(c[i]!=0)ans[++num]=i;
	printf("%d\n",num);
	for(int i=1;i<=num;i++)printf("%d ",ans[i]);
	printf("\n");
	return 0;
}
```

---

## 作者：wanghanjun (赞：0)

先在开头说一声，这里面的m代表题目里的K，原因见代码

假设小Z先取了i张牌，那么，小Y要保证自己的数不比小Z小，就必须取至少$f[i]$张牌，如果用$sum[i]$来表示前缀和，那么f[i]满足$sum[f[i]]-sum[i]>sum[i]$且$sum[f[i]-1]-sum[i]<=f[i]$

不难发现，$f[i]$的取值范围是1到n之间的整数且$f[i]$单调不减（即$f[i+1]>=f[i]$），于是我们可以从1到n枚举i，并且用j记录当前f[i]的值。具体实现见代码。

对于每个i，满足$sum[i]<=X<sum[f[i]]-sum[i]$的X必然满足要求，然后开一个数组，$c[x]$，表示有多少个i满足$sum[i]<=x<sum[f[i]]-sum[i]$。若X每个i都不满足，即$c[x]=0$，则X一定不满足。

如果用上述方法暴力求c[x]肯定会超时，可以只求c[x]的差分数组最后再根据其差分数组求出原数组就完成了。一些细节参见代码。

别忘了统计ans。

放代码：
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long ll;
const int MAXN=1000005;
ll a[MAXN],f[MAXN],s[MAXN],c[MAXN],n,m,ans=0;
//避免炸int，好像不开long long也行

int main(){
	memset(f,-1,sizeof(f));
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		s[i]=s[i-1]+a[i];
	}
	scanf("%lld",&m);
	for(ll i=1,j=1;i<=n;i++){
		if(s[i]>m){
			break;
		}//超出部分不用统计，避免RE
		while(s[i]>s[j]-s[i]&&j<=n){
			j++;
		}
		if(s[i]<=s[j]-s[i]){
			f[i]=j;
			c[s[i]]++;
			c[min(m+1,s[j]-s[i])]--;
			//也是忽略超出部分
		}
		else{
			c[s[i]]++;
			//如果f[i]不存在，则i后面所有点数加起来都没有s[i]大，满足X>=s[i]的X一定成立
			break;
		}
	}
	for(ll i=1;i<=m;i++){
		c[i]=c[i-1]+c[i];
		if(c[i]>0){
			ans++;
		}
	}
	printf("%lld\n",ans);
	for(ll i=1;i<=m;i++){
		if(c[i]>0){
			printf("%lld ",i);
		}
	}
	return 0;
}
```
~~先前缀和再差分（逃）~~

---

## 作者：Carlota (赞：0)

~~生平第一次AC月赛T3~~

~~乡下人非常激动~~

~~发一篇题解以示心中的激动之情~~

------------

## 题解[【P6015 游戏】](https://www.luogu.com.cn/problem/P6015)

建议自己先读一遍题目再来看题解

**题意简化：**

一个由 $n$ 个数组成的有序数列，$A$ 取前 $i$ 个数，$B$ 取第 $i+1$ 至第 $i+j$ 个数

分别算出两人各自取到的数字之和 $x$ 与 $y$

再次读题：

“如果一个人手上的牌的数字和大于 $k$，那么他的分数就是 $0$，否则分数就是数字和。”

**可简单理解为$2$项要求：**

1、$x$ 小于等于一个常量 $k$  
2、$y$ 要么严格小于 $x$ ，要么严格大于 $k$

求给定范围内**保证**符合要求的 $k$ 值（即无论 $B$ 怎么取，均同时符合两项要求）

------------

**算法分析：**

输入举例：（输入输出格式请自己读题）
```
5
5 4 3 2 2
10
```

输出举例：
```
4
5 6 9 10
```

以上述数据为例进行分析：

- （1）当 $A$ 只取第一个数 $5$ 时：
  
  由第一项要求可得（以下简写为【1】，【2】同理），$k≥5$ 。此时，
  
  - （1-1）当 $B$ 只取 $4$ 时：
    
    因为 $4<5$ ，因此必然满足【2】，对于 $k$ 没有约束
    
  - （1-2）当 $B$ 取 $4+3$ 时：
    
    因为 $7>5$ ，要想满足【2】，必然要严格大于 $k$ ，因此 $k<7$
    
  **第一组答案出现了**：$5≤k<7$ ，$k=5$或$6$
  
- （2）当 $A$ 取 $5+4$ 时：

  由【1】得 $k≥9$。此时我们发现，$9$ 大于数列总和的一半，因此 $B$ 无论怎么取都会输（~~想一想，为什么？~~）

- 以此类推

------------

回头看这道题目，“取连续若干张牌”让你想到了什么算法？

**前缀和**

我们来算出这个例子的前缀和：
```
5 9 12 14 16
```
对应上文的情况（1），我们可以发现，有效 $k$ 范围与 $5$ 和 $12$ 两个数字有关

**而$12$恰好是数列中比$5$的两倍大的数字中最小的！（即 $2×5$ 的后继）**

------------

**初步猜想：**

对 $n$ 个数进行循环（第 $i$ 个数的前缀和的值记为 $a_i$ ），每次取出 $a_i$ 与 $2×a_i$ 的后继，计算区间进行输出

大家多试几组数据就会发现，这个猜想似乎是正确的

下面~~给出证明~~开始瞎掰：

设 $A$ 取出 $m$ 个数，$B$ 取出 $n$ 个数，则 $A$ 的总和为 $a_m$ ，$B$ 的总和为 $a_n-a_m$ ，称之为 $t$。

要使 $t<a_m$ ，必然有 $a_n-a_m<a_m$ ，即 $2a_m>a_n$ ，因此 $2a_m$ 的后继是上界（不包含）（~~想一想，为什么？~~）

------------

**算法实现**

首先我们要用到前缀和

然后结合刚才的分析，我们还需要求后继

“求后继”这一操作让你想到了什么算法？

**二分搜索**

~~二分属于入门知识，这里就不细讲了~~

**一个注意点**

题目要求有序输出，因此记录答案后要经历一次排序再输出

## $Code$：
```cpp
#include<bits/stdc++.h>
#define int long long//不开ll见祖宗，RE成70分
using namespace std;
int n,k,a[1000010],sum[1000010],ans[1000010],top,l,r;
bool vis[1000010];
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		sum[i]=sum[i-1]+a[i];
	}
	sum[n+1]=10e18;//手动添加一个尾数，防止后继在数组里找不到这种情况发生
	scanf("%lld",&k);
	for(int i=1;i<=n;i++){
		l=1;r=n+1;
		while(l<r){
			int mid=(l+r)>>1;
			if(sum[mid]>2*sum[i])
			r=mid;
			else if(sum[mid]<2*sum[i])
			l=mid+1;
			else{//恰好相等的要舍去，因为题目要求的是“严格大于”
				r=0;
				break;
			}
		}
		for(int j=sum[i];j<sum[r]-sum[i]&&j<=k;j++){
			if(!vis[j]){//因为13行加了尾数，因此答案可能重复，需要手动去重
				ans[++top]=j;
				vis[j]=true;
			}
		}
	}
	sort(ans+1,ans+top+1);//一定要排序！！！
	printf("%lld\n",top);
	for(int i=1;i<=top;i++){
		printf("%lld ",ans[i]);
	}
	return 0;
}
```


---

## 作者：Kevin_Wa (赞：0)


## T3 游戏

### 题意解析

给你一串数列，让你在数列取前$x$个（数字和不超过$k$），使你从$x+1$无论怎么取数字和都要比前面的数字和要小或比$k$大。求有几个k满足条件。

首先暴力做法即枚举所有的k，然后判断是否可行即可，时间复杂度$O(n^2)$，期望得分$70$分。

> 不一定将前面所有数取到满足当前k最大，是最优的。可能少取即可会更优。

> 十年$OI$一场空，不开$longlong$见祖宗。

最后我们的~~正解~~（本人不能保证是正解，可能是出题人~~毒瘤~~良心没卡）隆重登场。。。（一片混沌。。。）

我们先用一个前缀和以便能$O(1)$求出区间内的和。然后线性扫描讨论小$Z$可能取到数值的所有情况记为$x$。在往后二分找到比他大的最小的一个值记为$sum$，当前情况满足条件的$k$即为$x$到$sum-1$。每次情况记录即可。

### $Code$

```cpp
#include<bits/stdc++.h>
//#pragma GCC optimize("Ofast")
#define N 1001000
using namespace std;
int a[N],ans[N],n,k,j,t,sum,p,f[N];
long long b[N];
template <typename T> void read(T &x) {
x = 0; char c = getchar();int f=1;
for (; !isdigit(c); c = getchar())if (c=='-') f=-1;
for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
x*=f;
}
int main()
{
	read(n);
	b[0]=0; 
	for (int i=1;i<=n;i++)
	  read(a[i]),b[i]=b[i-1]+a[i];
	read(k);
	for (int i=1;i<=n;i++)
	  {
	  	if (b[i]>k) break;
	  	sum=n;
	  	int t=i+1,w=n;
	  	while (t<=w)
	  	  {
	  	  	int mid=(t+w)/2;
	  	  	if (b[i]<=b[mid]-b[i])
	  	  	  {
	  	  	  	sum=mid;
	  	  	  	w=mid-1;
				  }
			else t=mid+1;
			}
		int l=b[i],r=b[sum]-b[i]-1;
		if (r>k) r=k;
		if (b[n]-b[i]<b[i]) r=k;
		for (int j=l;j<=r;j++)
		  {
		  	if (f[j]==0) p++;
		  	f[j]=1;
		  }
	  }
	printf("%d\n",p);
	for (int j=1;j<=k;j++)
	  if (f[j]) printf("%d ",j);
	
	return 0;
 } 
```


---

