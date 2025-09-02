# Compressed Bracket Sequence

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1556C/3e1271d095f65d6764f1796fd73b8947fda1c3d9.png)William has a favorite bracket sequence. Since his favorite sequence is quite big he provided it to you as a sequence of positive integers $ c_1, c_2, \dots, c_n $ where $ c_i $ is the number of consecutive brackets "(" if $ i $ is an odd number or the number of consecutive brackets ")" if $ i $ is an even number.

For example for a bracket sequence "((())()))" a corresponding sequence of numbers is $ [3, 2, 1, 3] $ .

You need to find the total number of continuous subsequences (subsegments) $ [l, r] $ ( $ l \le r $ ) of the original bracket sequence, which are regular bracket sequences.

A bracket sequence is called regular if it is possible to obtain correct arithmetic expression by inserting characters "+" and "1" into this sequence. For example, sequences "(())()", "()" and "(()(()))" are regular, while ")(", "(()" and "(()))(" are not.

## 说明/提示

In the first example a sequence (((()(()))( is described. This bracket sequence contains $ 5 $ subsegments which form regular bracket sequences:

1. Subsequence from the $ 3 $ rd to $ 10 $ th character: (()(()))
2. Subsequence from the $ 4 $ th to $ 5 $ th character: ()
3. Subsequence from the $ 4 $ th to $ 9 $ th character: ()(())
4. Subsequence from the $ 6 $ th to $ 9 $ th character: (())
5. Subsequence from the $ 7 $ th to $ 8 $ th character: ()

In the second example a sequence ()))(()(()))) is described.

In the third example a sequence ()()(()) is described.

## 样例 #1

### 输入

```
5
4 1 2 3 1```

### 输出

```
5```

## 样例 #2

### 输入

```
6
1 3 2 1 2 4```

### 输出

```
6```

## 样例 #3

### 输入

```
6
1 1 1 1 2 2```

### 输出

```
7```

# 题解

## 作者：maruize (赞：7)

## CF1556C

首先考虑将括号作为折线，左括号段对应一段斜向上的直线（上坡），右括号向下（下坡）。

像这样:

![1](https://cdn.luogu.com.cn/upload/image_hosting/kls8ha7p.png)

观察这段折线，容易发现一段合法序列，就像上面绿色的一段一样，两端点齐平且为整个绿段的最低的（即中间没有大“山谷”凹下来）。

考虑每个下坡，计算以祂结尾的答案。

对于下坡上每一个点，向右水平碰到的第一个点一定是祂对应的一个右端点。

同时如果碰到的点是拐点（即继续向右不会和轮廓线直接相交而是相切），可以继续向左走。

在折线图上画一画，可以发现一个下坡跟若干个上坡匹配。

![2](https://cdn.luogu.com.cn/upload/image_hosting/hso8kn5n.png)

可以发现，设绿箭头指的山峰高 $h$ ，则不包括空心蓝点的区间有 $h-\max(h-a_i,low)$ ，
其中 $low$ 指前面最低的山谷。

这是第一类贡献，考虑蓝点的贡献。

再看一张图

![3](https://cdn.luogu.com.cn/upload/image_hosting/0mecqfnb.png)


所有空心蓝点都在山谷里

我们从左往右依次看每一个山谷，向右扫到当前考虑的下坡都没有阻拦，即祂后面山谷的海拔都比祂高，且海拔 $\ge$ 下坡右端点，那么祂有 $1$ 的第二类贡献。

可以发现这个能用单调栈维护。

维护一个单增的栈，栈内的元素是可能做二类贡献的点，即扫过的部分中后面山谷的海拔都比自身高的山谷。

扫到一个元素，先算二类贡献答案，即栈内海拔 $\ge h-a_i$ 的元素。

再维护单调栈，发现正好需要弹掉 $> h-a_i$ 的元素。

注意要把海拔相等的点压起来，否则复杂度有问题。

时间复杂度 $O(n)$ 。

---

$\color{orange}{code}\color{green}{:}$

```cpp
//h[i]即海拔。
//st[*].fs:海拔。
//st[*].sc:这个海拔点的个数。
int ans=0;
for(int i=1;i<n;i+=2){
	ans+=h[i]-max(h[i]-a[i+1],st[1].fs);
	while(top>0&&st[top].fs>h[i+1]){
		if(top>1)ans+=st[top].sc;//注意low这个点
		top--;
	}
	if(st[top].fs!=h[i+1])st[++top]=pii(h[i+1],1);
	else ans+=st[top].sc,st[top].sc++;
}
printf(ans);
```


---

## 作者：Zxsoul (赞：5)

CF1556C Compressed Bracket Sequence 题解

>题解中含图片，以认真绘制，感觉可以看懂。

想必 CF 的官方题解并不是那么醒目，希望您可以在这看懂。(~~当然对于部分人来说，这题是那么的显然~~

首先一个显眼的性质是任何序列数量都不为零，这个表明每一对左右括号序列至少产生一的贡献。

此时假设给出 $c_x$ 的左括号，$c_y$ 的右括号。要求 $c_x>c_y$ ，对于这数对 $(x,y)$ 产生的括号一定是包含关系即：$((()))$ 类似这样，只不过左括号多了 $c_x-c_y$ 个。

我们设多的为 $res$，考虑 $res$ 可产生贡献的所有情况

- 显然不能再当前数对 $(x,y)$ 产生贡献
- 对后面新的数对且右括号多的与之匹配产生贡献

如下图为第二种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/sr6ng6qn.png)

此时的左括号跑去和后面的右括号匹配，这意味着他 **跨过了** 至少两个数对，即：`(()) ()` ，此时会产生**额外的组合贡献**。

**如何统计组合贡献？**

经观察发现，对于位置 $i$ 最多产生 $n-i$ 个组合贡献。**判断的条件是：** 每当一个左括号跨越了至少两个数对并且去和一个**新**的未到达过的数对右括号匹配时，产生一的组合贡献。

有点绕，重点是跨越和新的数对。

那么我们就可以枚举每一个数对的左括号，依次往后看能产生多少组合贡献，然后就可以了。

**代码细节**

请先看过代码。

 ```c
 int res=a[i]-1;
 ```

$-1$ 是保证在属于自己的数对时，不产生组合贡献，因为下面的操作是一直计算当前数对的左括号和后面数对的右括号产生的组合贡献，对于自己的左右括号匹配时不产生组合贡献，所以 $-1$ 相互抵消掉。

```c
ans+=max(0ll,res-max(0ll,tot-a[j])+1ll);
```

AC 代码：

```c
#include <iostream>
#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;
const int B=2000;
int a[B];
int n;
int read() {int x;scanf("%lld",&x); return x;}
signed main()
{
	n=read();
	for (int i=1;i<=n;i++)
	{
		a[i]=read();
	}
	int ans=0;
	for (int i=1;i<=n;i+=2)
	{
		int res=a[i]-1;
		int tot=a[i];
		for (int j=i+1;j<=n;j+=2)
		{
			ans+=max(0ll,res-max(0ll,tot-a[j])+1ll);
			tot-=a[j];
			if (tot<0) break;
			res=min(tot,res);
			tot+=a[j+1];
		}
	}
	printf("%lld",ans);
} 
```
也许我列的性质没有很好的融合在一起使得读者能够懂的显然，但是每一条性质都是有用的，如果不懂，请读者自行理解这些性质。


---

## 作者：pufanyi (赞：3)

整一个 $\texttt{O}(n)$ 的题解吧。

我们分两种情况考虑合法的括号序列：

1. 去掉最左边的 `'('` 和最右边的 `')'` 仍是合法括号序列的字符串（假设空串也合法），比如 `(()()((())))`；
2. 去掉最左边的 `'('` 和最右边的 `')'` 不是合法括号序列的字符串，比如 `()((())())`。

我们可以定义第一种括号序列是“独立的”，也就是说她不能被分裂成两个合法括号串；而第二种括号序列是“不独立的”，也就是说，她能被分裂成两个合法的括号串。

我们考虑把两种字符串分开考虑。很显然，每个 `')'`，只能作为一个独立括号串的右端点，所以我们统计这部分是非常容易的：跑一遍栈，和平时一样，只是批量地压栈和弹栈，记录弹出的 `'('` 次数，即是这部分的答案。

对于非独立的情况，我们考虑在计算独立串的时候同时统计他们，不难发现在对于一个独立串，将此串作为真后缀的非独立串个数即使他左边的连续独立串个数即可，并且我们只要发现出现 `)(` 的时候才会有非独立串出现，我们考虑在栈中加标记，记录一下出现 `)(` 的时候其左边连续独立串的个数即可。

具体实现的话，我们开一个栈，栈中压入 `pair`，$\left<x,1\right>$ 表示有 $x$ 个连续的 `'('`，$\left<x,0\right>$ 表示这里出现了一个 `)(`，这个 `)(` 左边还有几个连续的独立串。压入就直接压连续的 `'('` 即可，而弹栈的时候遇到 $\left<x,1\right>$，就统计独立串，遇到 $\left<x,0\right>$ 就统计一下非独立串。

考虑到大部分选手应该都不是很熟悉 `python`，窝把代码做了尽量详细的注释，应该差不多能看懂了 qaq。

```python
n = int(input())
aa = list(map(int, input().split())) # 读入数组
ans = 0
stk = [] # 栈
for i in range(n): # [0, n)
  if not stk: # 栈非空
    stk.append([0, 1]) # push
  if i & 1:
    while aa[i] and stk:
      if stk[-1][1] == 0:
        stk.pop()
      if stk:
        now = stk.pop()
        sub = min(now[0], aa[i])
        aa[i] -= sub
        now[0] -= sub
        ans += sub
        if now[0]:
          stk.append(now)
        if stk and stk[-1][1] == 0:
          ans += stk[-1][0]
    if aa[i]:
      stk.append([0, 1])
    else:
      if not stk:
        stk.append([0, 0])
      if stk[-1][1] == 0:
        stk[-1][0] += 1
      else:
        stk.append([1, 0])
  else:
    if stk[-1][1] == 0:
      stk.append([0, 1])
    stk[-1][0] += aa[i]
print(ans)
```

---

## 作者：cmll02 (赞：3)

$n\le 1000$，考虑用 $n^2$ 算法。

枚举最左边和最右边的括号分别在哪个位置，那么中间的部分已经被确定了。

我们只需要知道端点取在哪里。

![](https://cdn.luogu.com.cn/upload/image_hosting/4826zj41.png)

如上图左右端点有三种取法。

我们再考虑合法的括号序列的条件：

1. 左右括号数量相等；
2. 任何位置左边的左括号数量不小于右括号数量。

我们固定左端点，每次向右扩展，同时算出最左边端点至少选多少个才能满足条件 $2$。

再维护一个左右括号的数量差。

这样就能算出能选多少个了。

代码见 [link](https://codeforces.com/contest/1556/submission/127356816)。

---

## 作者：vectorwyx (赞：2)

来一篇单调栈做法的 $O(n)$ 题解。

我们把连续 $a$ 个左括号看做上升 $a$ 个单位长度的折线；把连续 $b$ 个右括号看做下降 $b$ 个单位长度的折线。这样就把 $c$ 序列转为了一张连续的有 $n+1$ 个拐点的折线图。为了方便，我们把左边是下降折线右边是上升折线的拐点称为**山谷**，其余拐点称为**山峰**。如果两个点落在折线上，且其相连形成的线段正下方没有任何东西，这两个点就是**匹配**的。所求即为这张折线图中的所有匹配的数量。

显然左端点一定在上升折线上，右端点一定在下降折线上。考虑固定右端点，计算左端点的贡献。从左往右处理每一条下降折线上的所有点，想象有一条扫描线从当前下降折线对应的山谷开始往上扫，令当前最低点（即最低山谷）的高度为 $low$，这条下降折线是从高度 $h$ 下降至高度 $h'$，那么这条折线上高度位于 $[max(low,h'),h]$ 的点都会对答案产生至少 $1$ 的贡献，其余点无贡献。我们把每个点的所有匹配中左端点最靠左的匹配看为平凡的，其余匹配看做非平凡的。不难发现平凡匹配的左端点要么为最低点，要么不是拐点。而非平凡匹配的左端点只可能为山谷。

平凡匹配的贡献即为 $[max(low,h'),h]$ 区间的长度。对于非平凡匹配，只有那些满足右边没有更低的山谷的山谷才可能产生 $1$ 的贡献。换句话说，高度更低的山谷会遮挡前面更高的山谷，那些被遮挡的山谷就不会再产生贡献了。而对于一个没被遮挡的山谷，如果它的高度位于当前折线的高度范围 $[h',h]$，那它一定会产生 $1$ 的贡献。这是一个天然的**单调栈结构**，我们可以用单调栈处理出当前未被遮挡的山谷。由于当前的折线是从 $h$ 到 $h'$，那么前一个山谷的高度一定小于 $h$，故未被遮挡的山谷的高度一定都小于 $h$，我们只需要看有多少个山谷的高度大于等于 $h'$。而 $h'$ 又恰好是我们要新加进来的山谷，所以可以**边弹栈边计算贡献**。复杂度 $O(n)$。注意要把高度相同的山谷缩在一起，然后高度最低的山谷可能会在平凡匹配和非平凡匹配中都被计算一遍，需要加个特判。

代码如下：（点个赞再走吧QAQ）
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
#include<queue>
#include<map>
#define pii pair<ll,int>
#define pb push_back
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define db double
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;
inline int read(){int x=0,fh=1; char ch=getchar(); while(!isdigit(ch)){if(ch=='-') fh=-1; ch=getchar();} while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0'; ch=getchar();} return x*fh;}
inline void out(int *a,int l,int r){fo(i,l,r) printf("%d ",*(a+i));puts("");}

const int N=1005;
int a[N],top,n;
ll ans,h;
pii stk[N];
//注意开 ll！
//先把向下的折线上的每个点与它能匹配到的最左边的点视为一组，它们的贡献是平凡的
//同时除非这个最左边的点是最低的山谷，否则它们一定不是山谷处 
//继续考虑不平凡的贡献，显然是每个恰好切到扫描线的山谷会多 1 的贡献
//注意到这样的山谷恰好就是未被遮挡的且高度大于等于向下的折线新形成的山谷的个数，而这些会产生贡献的山谷又会被新山谷所遮挡
//这是一个天然的单调栈结构，弹栈时即可处理掉不平凡的贡献 
//注意最低点的山谷可能作为 最左边点 和 高度大于等于新山谷的山谷 同时被计算贡献，此时要排除一种 
//还有一点是，由于新山谷是从 h->h-a[i]，所以它的前一个山谷的高度一定 <h，不会计入不合法的山谷 

int main(){
	cin>>n;
	fo(i,1,n) a[i]=read();
	stk[++top].first=0;
	stk[top].second=1;
	h=a[1];
	fo(i,2,n+1){
		//printf("%d,%d\n",i,h);
		//fo(j,1,top) printf("(%d,%d) ",stk[j].first,stk[j].second);puts("");
		if(i&1){	
			while(top&&h<stk[top].first) ans+=stk[top].second,top--;
			if(!top||h!=stk[top].first) stk[++top]=make_pair(h,1);
			else ans+=stk[top].second,stk[top].second++;
			h+=a[i];
		} 
		else{
			//ans+=max(h-max(stk[1].first,h-a[i])-(stk[1].first==h-a[i]),0);
			if(stk[1].first>=h-a[i]) ans+=max(h-stk[1].first-1,0ll);
			else ans+=a[i];
			h-=a[i];
		}
	}
	cout<<ans;
	return 0;
}
/*
3
1 3 39
-------------------------------------------------
1
*/
```


---

## 作者：Cry_For_theMoon (赞：2)

[传送门](https://codeforces.com/contest/1556/problem/C)

作为 C 质量很高。

#### 分析：

容易想到枚举最左边的括号在 $c$ 中的下标 $l$，枚举最右边的括号在 $c$ 中的位置 $r$，注意到 $l$ 必须为奇数，$r$ 必须为偶数。然后计算 $[l,r]$ 的答案。

首先注意到一个事实，如果 $l=r-1$ 那么答案应该为 $\min\{c_l,c_r\}$ 个，否则意味着 $(l,r)$ 区间是有数的。

一个合法括号串的定义是，如果我们把左括号视作 $+1$，右括号视作 $-1$，那么对其做前缀和 $s$，设长度为 $n$，则有：

- $\forall 1\le i\le n,s_i \ge 0$。

- $s_n=0$。

我们考虑在 $c_l$ 中选择若干个，在 $c_r$ 中选择若干个，使得最后的串满足上面的约束。注意到为了不让第一个约束失效，我们必须选择若干个 $c_l$ 里的左括号。比如说 ```(((```，```))```，```((```，```))))```。$l$ 是第一个，$r$ 是第四个。那么注意到必须在第一个位置选择两个左括号使得其后面的每个前缀和非负。

具体地，设 $s_{i,j}$ 是 $[i,j]$ 的和，$minn_{i,j}=\min\{s_{i,k}|i\le k\le j\}$，那么，在 $minn_{l+1,r-1} < 0$ 的时候，$c_l$ 处必须选择 $|minn_{l+1,r-1}|$ 个左括号。

然后此时我们能计算出当前的 $[l,r-1]$ 的和，记为 $sum$，那么 $c_r$ 处必须选择  $sum$ 个右括号。

那么更新完 $c_l,c_r$ 的值后，答案就是 $\max\{c_l,c_r\}+1$（考虑更新完后本身就是一个合法串所以 $+1$）。

```
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const ll MAXN=1e3+10,INF=1e18;
ll n,c[MAXN],sum[MAXN][MAXN],minn[MAXN][MAXN];
ll ans;
ll solve(ll l,ll r){
	if(l==r-1){
		return min(c[l],c[r]);
	}
	ll mn=minn[l+1][r-1],s=sum[l+1][r-1];
	l=c[l];r=c[r]; 
	if(mn<0){
		if(l<abs(mn))return 0;
		l+=mn;
		s-=mn;
	}
	if(s<0)return 0;
	if(r<s)return 0;
	r-=s;
	return min(l,r)+1;
}
int main(){
	cin>>n;
	rep(i,1,n){
		cin>>c[i];
	}
	rep(i,1,n){
		rep(j,i,n){
			sum[i][j]=sum[i][j-1];
			if(odd(j))sum[i][j]+=c[j];
			else sum[i][j]-=c[j];
			if(j==i)minn[i][j]=sum[i][j];
			else minn[i][j]=min(minn[i][j-1],sum[i][j]);
		}
	}
	rep(l,1,n){
		if(even(l))continue;
		rep(r,l+1,n){
			if(odd(r))continue;
			ans+=solve(l,r);
		}
	}
	cout<<ans<<endl;
}
```

---

## 作者：NXYorz (赞：2)

[题目链接](https://www.luogu.com.cn/problem/CF1556C)

-----------

#### 题目大意

给定长度为 $n$ 的序列 $a_n$，奇数位代表 ```(```，偶数为代表 ```)```。
数量即为 $a_i$ 的数值大小。求合法的括号连续子序列有多少。

---------
#### 分析

~~括号树的好兄弟~~。

发现对于每一个 ```)```：

- 如果与其相邻的 ```(``` 的数量大于它，即 ```...((())....``` 的情况。产生的贡献是 ```)``` 的数量。
- 如果与其相邻的 ```(``` 的数量等于它，即 ```...((()))...``` 的情况。产生的贡献是 ```)``` 的数量加上与该合法括号串相邻的合法括号串的数量。在刚才的例子中，左边的省略号有可能为 ```..()()((()))...```。在这种情况下，该合法括号串相邻的合法括号串的数量为 $3$。
- 如果与其相邻的 ```(``` 的数量小于它，即 ```...(()))....``` 的情况。产生的贡献为 ```(``` 的数量加上与该合法括号串相邻的合法括号串的数量。理由同上。但是要注意的是此时依旧剩下若干 ```)```没有匹配，但是容易发现第一种情况会剩下若干 ```(```，因此只需要往前枚举 ```(``` 重复以上三种情况即可。

注意维护合法括号串相邻的合法括号串的数量。

### $\texttt{Code}$
```cpp
#include<bits/stdc++.h>

using namespace std;
const int N = 1e3 + 10;

int a[N];
long long sum[N];

int main()
{
    freopen("aa.in","r",stdin);
    int n; scanf("%d",&n);
    for(int i = 1;  i <= n; i++)
        scanf("%d",&a[i]);
    
    long long ans = 0;
    for(int i = 1; i <= n; i++)
    {
        if(i & 1) continue; int tot = a[i];
        for(int j = i - 1; j >= 1; j -= 2)
        {
            if(!tot) break;
            if(!a[j]) continue;
            if(tot < a[j]) 
            {
                ans += tot;
                a[j] -= tot;
                sum[i]++;break;
            }
            if(tot == a[j])
            {
                ans += tot + sum[j - 1];
                sum[i] += 1 + sum[j - 1];
                a[j] = 0;break;
            }
            // tot > a[j]
            tot -= a[j]; 
            ans += a[j] + sum[j - 1];
            a[j] = 0;
        }
    }
    printf("%lld",ans); return 0;
}
```

---

## 作者：frank15 (赞：1)

纪念拿到最优解，写一篇题解。

首先这题我们有一个很显然的想法：设一个 $sum$ 表示当前有多少个左括号未匹配。当我们到一个奇数位置时 $sum$ 加上 $c_i$ ,否则$sum$ 减去 $c_i$，$ans$ 加上 $c_i$。

但这样有一种情况我们就会算漏。考虑这样一个括号序列 $ \text{()()}$，按照我们 上面的算法得到的 答案是 $2$，但实际有  $ \text{()}$、$ \text{()}$、$ \text{()()}$ 这三个合法序列。

为社么会错呢？因为我们在用上面算法的时候默认计算的序列都是首尾配对的即类似  $\text{(s)}$ 这样的序列，我们漏掉了$\text{(s)(s)}$ 这样的序列。因此，我们可以再设一个数组 $f$，$f_i$ 表示**以 $i$ 结尾的合法序列**，即把 $c_i$ 个右括号都匹配完后，构成的合法序列数就为 $f_i$，每次更新 $ans$ 的时候再加上 $f_i$ 就好了。

那么设 $pre$ 为与 $c_i$ 中最后一个括号匹配的位置,若 $c_i$ 没用完则不更新 
$$
	
  f_i = \begin{cases}
f_{\text{pre}}+1 & \text{pre}>0\\
0 & \text{otherwise.}
\end{cases}
$$

那么这道题就做完了，接下来是代码时间 

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=1e3+5;
ll ans,f[maxn];
int n,tot;
int c[maxn],st[maxn];//开个栈来记录还有左括号的位置
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&c[i]);
	for(int i=1;i<=n;i++){
		if(i&1)
			st[++tot]=i;
		else{
			int las=0;
			for(int j=tot;j>=1;j--){
				if(c[i]>=c[st[j]]){
					las=st[j]-1;//las会被不断更新，直到c[i]被减到0。
					ans+=c[st[j]]+f[st[j]-1];
					c[i]-=c[st[j]];
					c[st[j]]=0;
					--tot;
				}
				else{
					ans+=c[i];
					c[st[j]]-=c[i];
					c[i]=las=0;//如果在匹配的时候，pre还有i没了，此时不能从f[las]转移过来
					if(!c[st[j]])
						--tot;
					break;
				}
				if(!c[i])
					break;
			}
			if(!c[i])
				f[i]=f[las]+1;//如果右括号都用完了就更新f
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：LoveLonelyTime (赞：1)

# 区间DP解法

考虑两个 DP 数组：

- $\text{open}[l][r]$ 数组表示由区间 $[l,r]$ 组成的括号序列还需要多少个 "(" 才能使其区间内所有 ")" 都闭合。
- $\text{close}[l][r]$ 数组表示由区间 $[l,r]$ 组成的括号序列还需要多少个 ")" 才能使其区间内所有 "(" 都闭合。

我们考虑区间 $[l,r]$ 和 $[l + 1,r]$的转移关系：

1. 如果 $l$ 是奇数，则对 $\text{open}$ 有贡献：

- 如果 $\text{arr}[l] \geq \text{open}[l + 1][r]$ ，那么 $\text{arr}[l]$ 能闭合所有的 $\text{open}[l + 1][r]$，同时还要将多于的算进 $\text{close}$ 中，即 $\text{open}[l][r] = 0,\text{close}[l][r] = \text{close}[l + 1][r] + \text{arr}[l] - \text{open}[l + 1][r]$。
- 如果 $\text{arr}[l] \lt \text{open}[l + 1][r]$ ，那么 $\text{arr}[l]$ 就不能完全闭合$\text{open}[l + 1][r]$，即 $\text{open}[l][r] = \text{open}[l + 1][r] - \text{arr}[l],\text{close}[l][r] = \text{close}[l + 1][r]$。

2. 如果如果 $l$ 是偶数，则对 $\text{open}$ 无贡献，此时 $\text{close}[l][r] = \text{close}[l + 1][r],\text{open}[l][r] = \text{open}[l + 1][r] + \text{arr}[l]$

之后，枚举 $l$ 和 $r$ ，使得 $l$ 是奇数， $r$ 是偶数。考虑 $l,r$ 对答案的贡献：

如果$\text{arr}[l] \geq open[l + 1][r - 1]$ 并且 $\text{arr}[r] \geq close[l + 1][r - 1]$ ，那么说明边界有足够的括号对去闭合区间内的括号对，此时我们找到了最小的边界。之后计算最大扩展即可。

```cpp
ans += min(arr[r] - close[l + 1][r - 1], arr[l] - open[l + 1][r - 1]);
```

最后还需要判断一下非空区间对答案的贡献即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXT = 1005;

ll arr[MAXT];
int n;
ll open[MAXT][MAXT];
ll close[MAXT][MAXT];

void solve()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }

    for (int len = 1; len <= n; len++)
        for (int st = 1; st + len - 1 <= n; st++)
        {
            int ed = st + len - 1;
            if (st & 1)
            {
                if (arr[st] >= open[st + 1][ed])
                {
                    open[st][ed] = 0;
                    close[st][ed] = close[st + 1][ed] + arr[st] - open[st + 1][ed];
                }
                else
                {
                    close[st][ed] = close[st + 1][ed];
                    open[st][ed] = open[st + 1][ed] - arr[st];
                }
            }
            else
            {
                close[st][ed] = close[st + 1][ed];
                open[st][ed] = open[st + 1][ed] + arr[st];
            }
        }
    ll ans = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j < i; j++)
        {
            if (!(i & 1) && (j & 1) && close[j + 1][i - 1] <= arr[i] && open[j + 1][i - 1] <= arr[j])
            {
                ans += min(arr[i] - close[j + 1][i - 1], arr[j] - open[j + 1][i - 1]);
                if (close[j + 1][i - 1] != 0 || open[j + 1][i - 1] != 0)
                    ans++;
            }
        }
    }
    cout << ans << endl;
}

int main()
{
    solve();
    return 0;
}
```

---

