# Painting the Array I

## 题目描述

### 题意

  **本题与 CF1480D2 的唯一区别是本题询问最大可能解.**

  给定一个数组 $a$, 你将将 $a_i$ 染为 $b_i$ 色, 其中 $b$ 是由你指定的一个 **01 数组**. 将 $a$ 数组中被染成 0 色的数字取出来并依在 $a$ 中出现的顺序排列, 组成数组 $a^{(0)}$. 同理, 将 $a$ 数组中被染成 1 色的数字取出来并依在 $a$ 中出现的顺序排列, 组成数组 $a^{(1)}$. 我们定义 $seg(c)$ 是一个正整数, 其中 $c$ 是一个数组, $seg(c)$ 的值为在我们将 $c$ 中相邻的所有相同元素合并后, $c$ 数组的大小. 例如, $seg([1, 1, 4, 5, 1, 4]) = |[1, 4, 5, 1, 4]|=5$. 最大化 $seg(a^{(0)})+seg(a^{(1)})$.

## 样例 #1

### 输入

```
7
1 1 2 2 3 3 3```

### 输出

```
6```

## 样例 #2

### 输入

```
7
1 2 3 4 5 6 7```

### 输出

```
7```

# 题解

## 作者：wsyhb (赞：12)

## 题意简述

定义连续段 $seg(c)$：将序列 $c$ 中的相邻的相同元素合并后的长度。

给定长度为 $n$ 的序列 $a_1,a_2,\cdots,a_n$，要求将其分成两个不相交的子序列 $a^{(0)}$ 和 $a^{(1)}$，使得 $seg(a^{(0)})+seg(a^{(1)})$ **最大**，求这个**最大值**。（也可理解为给第 $i$ 个元素涂上颜色 $b_i$，其中 $b_i=0$ 或 $b_i=1$，然后将颜色为 $0$ 和颜色为 $1$ 的元素分别从左到右取出）

**数据范围**：$n \le 10^5$，$1 \le a_i \le n$

## 分析 + 题解

题目可以看作有两个队列 $s$ 和 $t$，从左到右依次选择每个元素是加入 $s$ 队尾，还是加入 $t$ 队尾，使得最后 $seg(s)+seg(t)$ 最大。

设当前 $s$ 队尾元素为 $x$，$t$ 队尾元素为 $y$，要加入的元素为 $z$（为了方便，一开始 $x=y=0$），我们给出下列**贪心**策略：

1. 若 $z$ 与 $x,y$ 中的至少一个相等，我们将 $z$ 加入当前队尾不为 $z$ 的队列。（若 $z=x=y$，可任意选择）

2. 若 $z$ 不与 $x,y$ 中的任意一个相等，我们将 $z$ 加入 $s$ 当且仅当 $next(x)<next(y)$。其中 $next(x)$ 表示 $x$ 这种值下一次出现的位置，若之后没有出现 $next(x)=n+1$。

**感性理解**：

1. 如果不这样做的话，那之后一次对于相等的 $z$ 这样做，答案相同，效果等价；（效果指操作后 $x=y=z$）若之后一次都没有对相等的 $z$ 这样做，答案减少 $1$；

2. 为了让 $x$ 和 $a_{next(x)}$ 不要连成一段，用与它们都不同的 $z$ 隔开，而 $y$ 和 $a_{next(y)}$ 之后更有可能被其他元素隔开。

**理性证明**：

**分类讨论**即可发现这样的策略不会比其他的答案差，比较冗长，此处略。（可以看一下[官方题解的证明](https://codeforces.com/blog/entry/87598)，建议看 "An Intutive Proof"，更加直观）

## 代码

预处理 `Next` 数组然后模拟即可。

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int max_n=1e5+5;
int a[max_n],id[max_n],Next[max_n];
typedef pair<int,int> P;//前一个是元素的值，后一个是元素的编号
vector<P> w,b;
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",a+i);
		id[i]=n+1;//注意初始化
	}
	for(int i=n;i>=1;--i)
	{
		Next[i]=id[a[i]];
		id[a[i]]=i;
	}
	w.push_back(P(0,n+1));
	b.push_back(P(0,n+1));
	int ans=0;
	for(int i=1;i<=n;++i)
	{
		if(a[i]==w.back().first)
		{
			if(a[i]!=b.back().first)
				++ans;
			b.push_back(P(a[i],Next[i]));
		}
		else if(a[i]==b.back().first)
		{
			++ans;
			w.push_back(P(a[i],Next[i]));
		}
		else
		{
			++ans;
			if(w.back().second<b.back().second)
				w.push_back(P(a[i],Next[i]));
			else
				b.push_back(P(a[i],Next[i]));
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：2huk (赞：5)

> 给定一个长度为 $n$ 的序列 $a$。请你将其划分成两个序列 $a^{(0)}$ 和 $a^{(1)}$，使得 $\operatorname{seg}(a^{(0)}) + \operatorname{seg}(a^{(1)})$ 的值最大。
>
> 对于一个序列 $a$ 而言，定义 $\operatorname{seg}(a)$ 表示为在我们将 $a$ 中相邻的所有相同元素合并后，$a$ 数组的大小。

简单贪心。

我们用两个队列维护当前的 $a^{(0)}$ 和 $a^{(1)}$。那么考虑当前枚举的 $a_i$ 应当放入哪个队列中。

可以发现一个性质，答案的计算只与两个队列中的相邻两项有关。因此我们在考虑将 $a_i$ 放入哪个队列里时只需要看它的队尾元素即可。

不妨令 $t^{(0)}$ 表示当前 $a^{(0)}$ 队列的队尾，$t^{(1)}$ 表示当前 $a^{(1)}$ 队列的队尾。分情况讨论：

- $a_i = t^{(0)}$  且 $a_i = t^{(1)}$：放入哪个队列中对后续影响都是相同的；

- $a_i = t^{(0)}$ 且 $a_i \ne t^{(1)}$：放入 $a^{(1)}$ 队列中显然更优；

- $a_i \ne t^{(0)}$ 且 $a_i = t^{(1)}$：放入 $a^{(0)}$ 队列中显然更优；

- $a_i \ne t^{(0)}$ 且 $a_i \ne t^{(1)}$：

  凭直觉而言可能是放入哪个队列中都可以，实际不然，我们要考虑它对后续答案的影响。

  ![](https://cdn.luogu.com.cn/upload/image_hosting/6swcke98.png)

  

  如果此时将 $a_i = 1$ 和 $a_{i + 1} = 3$ 放入队列 $a^{(0)}$，那么 $a_{i + 2} = 3$ 此时放入哪个队列中都不会更优。

  ![](https://cdn.luogu.com.cn/upload/image_hosting/xhrrbaxu.png)

  那么应该怎么做呢？

  因为 $a_{i + 1} = t^{(1)}$，所以我们希望把 $a_i$ 先放入 $a^{(1)}$ 中，让 $a_i$ 把 $t^{(1)}$ 和 $a_{i + 1}$ 隔开，这样就更优了。

  我们可以维护 $ne_i$ 表示 $i$ 之后第一个与 $a_i$ 相等的位置 $j$。那么我们只需要判断 $ne_{t^{(0)}}$ 和 $ne_{t^{(1)}}$ 谁更小，就放在哪个队列里。相当于是哪个队列当前更危险，就放在哪个队列中。

根据这样的策略计算即可。

[代码](https://www.luogu.com.cn/paste/dfkut80l)。



---

## 作者：xz001 (赞：3)

- 首先我们发现只有相邻两个元素是有关系的，所以我们用两个栈分别维护 $a^{(0)}$ 和 $a^{(1)}$ 中的元素下标。
- 然后我们依次插入元素，对于每个元素，我们判断一下：
    - 如果这个元素与其中一个元素相等但与另一个元素不同（指其指向的元素），则将其丢进与其不同的那个栈里。
    - 如果都相同的话，随便找一个更新一下下标即可。
    - 如果都不同，为了让元素数量尽量大，肯定是要防止两个元素碰撞的，因此我们看看两个栈顶所对应的元素在其之后第一个与其相等的元素的位置，找一个小的插入即可（打个比方，有两个敌人正在靠近你，你肯定是先防离你近的那个敌人）。
- 然后输出两个栈的长度之和即可。
- 然后我们就以 $O(n)$ 的复杂度切了此题，代码如下。

```cpp
#include <bits/stdc++.h>

using namespace std;

// define
#define re register
#define fi first
#define se second
#define il inline
#define co const
#define ls (u << 1)
#define rs (u << 1 | 1)
#define fup(x, l, r) for (re int x = (l), eNd = (r); x <= eNd; ++ x )
#define fdw(x, r, l) for (re int x = (r), eNd = (l); x >= eNd; -- x )
#define int long long

int s1[1000005], s2[1000005], top1, top2, n, a[1000005], nxt[1000005], p[1000005];

signed main() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++ i) scanf("%lld", a + i);
    for (int i = n; i >= 1; -- i) { //预处理每个元素后方第一个与其相同的元素的位置
    	nxt[i] = p[a[i]] ? p[a[i]] : n + 1;
    	p[a[i]] = i;
	}
	nxt[0] = n + 1;
	for (int i = 1; i <= n; ++ i) {
		if (a[i] == a[s1[top1]]) {
			if (a[i] != a[s2[top2]]) {
				s2[ ++ top2] = i;
			}
			s1[top1] = i;
		} else if (a[i] == a[s2[top2]]) {
			s1[ ++ top1] = i;
		} else {
			if (nxt[s1[top1]] < nxt[s2[top2]]) {
				s1[ ++ top1] = i;
			} else {
				s2[ ++ top2] = i;
			}
		}
	}
	printf("%lld", top1 + top2);
	return 0;
}


```

---

## 作者：walk_alone (赞：3)

D1,D2两题共一发题解写了。这俩代码巨像。

两题的本质都是**贪心**，D1问的是最大值，D2问的是最小值。约定：数值存储数组为$a$，黑白两子列当前最后一个元素的数值分别为$a[x],a[y]$。之所以这样存储是因为便于修改。显然我们不关心这个数值是从哪里取得的而关心这个数值本身是多少，因而可以考虑使用**这个数值对应于原数列的一个下标**来表示这个数值。当前待插入的元素为$a[i]$。$nxt[i]$即$next[i]$，代表数值$a[i]$下一次出现的地方，用链式前向星计算和维护。

先来考虑最大值的情况：

1.当$a[i]$与$a[x],a[y]$有相同数值。出于贪心原理，显然当前这个元素会尽可能地与数值不同的子列组合。因为如果放在另一边，当前步骤就会损失一个答案，对之后答案也不会起到什么积极的贡献——插入一个数至多只会增加1。

这样做的结果是**黑白子列最后一个元素的数值都相同了**——$a[i] \neq a[x]$时进入黑子列，黑子列最后一个元素变成$a[i]$，与$a[y]$相等；$a[i] \neq a[y]$同理。当两个都相同的时候更加是这样，不过这种情况下，对答案也没有贡献了。因而这个部分的代码可以被浓缩成这样：

```cpp
if (a[i] == a[x] || a[i] == a[y])//至少与一个相等
{
    ans += x!=y;//若x等于y则a[x]=a[y]。这种情况对应于黑白子列最后一个元素的数值都相同，ans不会增加。其余情况均会增加。
    x=y=i;//经过这个操作之后，数值变成相同的。
    continue;
}
```
2.$a[i]$与$a[x],a[y]$都不相等。这个情况是最头疼的情况。考虑一个贪心：如果$a[x]$的下一位元素$next[a[x]]$的位置比$a[y]$先，那么优先放入$a[x]$对应的黑子列中。因为，如果$a[x]$前面还有其他的数值，那么这样做与不这么做显然对答案贡献相同——它们均不会造成前面的$a[x]$与后面的$a[x]$合并；但是如果前面没有任何其他的元素，不这么做就会导致**前后的$a[x]$被合并**，答案损失1。因而，我们这么贪心是最优的。对应代码如下：

```cpp
ans++;//该数必然会造成一个贡献。
if (nxt[x] < nxt[y])//a[x]的下一个数更近，则往黑子列填
    x = i;
else
    y = i;
```
而最小值刚好就是反过来——尽可能地让前后合并。

因而，如果与黑子列的最后一个数值相等，则合并到黑子列去；与白子列最后元素相等则去白子列。

```cpp
if (a[i] == a[x])
{
    x = i;
    continue;
}
if (a[i] == a[y])
{
    y = i;
    continue;
}
```

都相等无所谓：随便找一个合并就行了。

如果都不相等，则又和前面相似——考虑后面对答案的影响了。最大值是尽可能地不合并，这里就是要尽可能地合并。因而，谁的$next$越近越可能合并，贪心证明同上。

```cpp
ans++;//必然要产生贡献了，但是尽可能让后面不产生贡献
if (nxt[x] < nxt[y])
    y = i;
else
    x = i;
```
剩下部分两个代码完全一样，就是链式前向星的基本操作了。

---

## 作者：创世游戏科技 (赞：2)

# Painting the Array I

### 思路

本题要求的就是把一个序列分成两个不重合的子序列，使其相邻的所有相同元素最少。也就是最大化  $ seg(a^{(0)})+seg(a^{(1)}) $。
如何确定一个元素应该进入哪个子序列呢？我们可以定义两个子序列 $a1,a2$，它们最后一个元素分别为 $s,t$。

感性理解。显然，当一个元素如果与 $s,t$ 中的任何一个相同的时候，我们应该把它加入另一个序列中，因为只有这样才能使结果更大。

对于另一种情况，一个元素与 $s,t$ 任何一个都不相同。感性的理解一下。一个元素 $a_i$ 与下一个与这个元素数值相同的元素应该被不同的元素隔开。

**对于 $x,y$ 来说，当 $nxt_x<nxt_y$ 时, $y$ 与 $nxt_y$ 之间更容易被其它元素隔开。$x$ 与 $nxt_x$ 之间更不容易被其它元素隔开。**
这里的 $nxt_i$ 是表示在 $a_i$ 后面第一个与 $a_i$ 相同的元素。

所以加入更不容易被隔开的一定能使结果更优。且一定是最终结果的最优，所以说可以采用贪心的策略。

### 代码

```c
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int last[1000001],nxt[1000001],a[1000001],tot1,tot2,n,ans;
//nxt[i]是表示a[nxt[i]]=a[i]的最小数
int a1[1000001],a2[1000001];
int main(){
	cin>>n;
    nxt[0]=n+1;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)last[a[i]]=n+1;
	//倒序求出nxt,细节:last一定要设为n+1,才能使最后一个元素nxt为n+1
	for(int i=n;i>=1;i--){
		nxt[i]=last[a[i]];
		last[a[i]]=i;
	}
	
	for(int i=1;i<=n;i++){
	    //有一个相同
		if(a[i]==a[a1[tot1]]){
			a2[++tot2]=i;
		}else if(a[i]==a[a2[tot2]]){
			a1[++tot1]=i;
		}else{
		    //没有相同
			if(nxt[a1[tot1]]<nxt[a2[tot2]]){
				a1[++tot1]=i;
			}else a2[++tot2]=i;
		}
	}
	//统计答案
	for(int i=1;i<=tot1;i++)if(a[a1[i]]!=a[a1[i-1]])ans++;
	for(int i=1;i<=tot2;i++)if(a[a2[i]]!=a[a2[i-1]])ans++;
	cout<<ans;
	return 0;
}
```

---

## 作者：K_Madoka (赞：1)

## 题意

把数组 $a$ 分成两个不相交的子数组 $a^0$ 和 $a^1$。

定义 $seg(a)$ 为数组 $a$ 中不同的连续段。

例如 $[1,1,2,2,3,3,3,2]$ 的 $seg$ 为 $4$ ，为 $[1,2,3,2]$。

现要求分出来的 $seg(a^0) + seg(a^1)$ 最大。

## 解法

这种题目看上去是个dp，但实际上贪心会更好做一些。

我们如果要考虑分出来的子数组对 $seg$ 的贡献，实际上只用考虑子数组当前取到的数。

我们设当前 $a^0$ 取到的数的位置是 $a0$ ，当前 $a^1$ 取到的数的位置是 $a1$。

目前要考虑 $a_i$ 是放在 $a^0$ 里还是 $a^1$ 里。
 
现在可以把不同的情况分一下类：

$1.$ $a_{a0} = a_{a1}$

这时候把 $a_i$ 放到任意一边都可以。

$2.$ $a_{a0}\neq a_i$ 且 $a_{a1} = a_i$

这个时候显然放到 $a^0$ 里比 $a^1$ 更有优势，因为有贡献。

$3.$ $a_{a1}\neq a_i$ 且 $a_{a0} = a_i$

这个时候显然放到 $a^1$ 里比 $a^0$ 更有优势，因为有贡献。

$4.$ $a_{a0}\neq a_i$ 且 $a_{a0} \neq a_i$

这个时候貌似放到哪边都行，其实不然。

设 $nxt_{a0}$ 为下一个 $a_{a0}$ 出现的位置， $a1$ 同理。

可以感性地了解一下，当此时 $nxt_{a0}<nxt_{a1}$ 的时候，如果不把 $a_i$ 放进 $a_0$ 中，$a_{a_0}$ 离下一个相同的数更近了，这样更加的危险，对结果是不利的，所以这里放进 $nxt$ 小的更优。

这里只是简单的理解一下，详细的证明过程可以看[官方题解](https://codeforces.ml/blog/entry/87598)。

```cpp
#define MAXN 100010
ll n,a[MAXN],nxt[MAXN],lst[MAXN],a0,a1;
int main(){
	n=readll();
	for(int i=1;i<=n;i++)a[i]=readll();
	nxt[0]=n+1;
	for(int i=1;i<=n;i++)lst[a[i]]=n+1;
	for(int i=n;i>=1;i--){
		nxt[i]=lst[a[i]];
		lst[a[i]]=i;
	}
	ll ans=0;
	for(int i=1;i<=n;i++){
		if(a[a0]!=a[i]&&a[a1]!=a[i]){
			if(nxt[a0]<nxt[a1])a0=i;
			else a1=i;
			ans++;
		}
		else if(a[i]!=a[a0])a0=i,ans++;
		else if(a[i]!=a[a1])a1=i,ans++;
		else a0=i,a1=i;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：AK_400 (赞：0)

考虑一个贪心：记当前最后一个染黑色的为 $x$，最后一个染白色的为 $y$，下一个要染的是 $z$，那么如果 $x=z$ 就染白，否则染黑。

这显然是错的，会被这样一组数据 hack：$1,1,2,3,1,1$，上述做法会染成 $a^{(0)}=[1,2,3,1],a^{(1)}=[1,1]$。

但是我们把这种情况特判：记 $a,b$ 为当前染的数的上一个长度大于一的相同元素连续段的元素和下一个长度大于一的相同元素连续段的元素，那么当 $a=b,z\ne a,x=a\vee y=a$ 时，我们将上述做法改为以下做法：

若 $x\ne a$，将当前元素染成白色，否则染成黑色。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[100005],ans;
vector<pair<int,int>>b;//连续段
vector<int>db;//长度大于一的连续段的元素
void slv(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    int cnt=1;
    for(int i=2;i<=n;i++){
        if(a[i]!=a[i-1]){
            b.push_back({a[i-1],cnt});
            if(cnt!=1)db.push_back(a[i-1]);
            cnt=1;
        }
        else cnt++;
    }
    b.push_back({a[n],cnt});
    if(cnt!=1)db.push_back(a[n]);
    int pos=-1;
    int lst1=0,lst2=0;
    for(int i=0;i<b.size();i++){
        if(pos==-1){
            if(b[i].second==1)ans++;
            else {
                ans+=2;
                pos++;
                lst1=lst2=b[i].first;
            }
            continue;
        }
        if(pos==db.size()-1){
            ans++;
            continue;
        }
        if(b[i].second!=1){
            ans+=(b[i].first!=lst1);
            ans+=(b[i].first!=lst2);
            lst1=lst2=b[i].first;
            pos++;
            continue;
        }
        if(db[pos]!=db[pos+1]){
            ans++;
            continue;
        }
        if(lst1!=db[pos]&&lst2!=db[pos]){
            ans++;
            continue;
        }
        if(b[i].first==db[pos]){
            ans++;
            if(lst1!=db[pos]){
                lst1=b[i].first;
            }
            else lst2=b[i].first;
            continue;
        }
        if(lst1==db[pos])lst1=b[i].first;
        else lst2=b[i].first;
        ans++;
    }
    cout<<ans<<endl;
}
signed main(){
    slv();
    return 0;
}
```

---

## 作者：lightup37 (赞：0)

### CF1480D1

### 题意

  **本题与 CF1480D2 的唯一区别是本题询问最大可能解.**

  给定一个数组 $a$, 你将将 $a_i$ 染为 $b_i$ 色, 其中 $b$ 是由你指定的一个 **01 数组**. 将 $a$ 数组中被染成 0 色的数字取出来并依在 $a$ 中出现的顺序排列, 组成数组 $a^{(0)}$. 同理, 将 $a$ 数组中被染成 1 色的数字取出来并依在 $a$ 中出现的顺序排列, 组成数组 $a^{(1)}$. 我们定义 $seg(c)$ 是一个正整数, 其中 $c$ 是一个数组, $seg(c)$ 的值为在我们将 $c$ 中相邻的所有相同元素合并后, $c$ 数组的大小. 例如, $seg([1, 1, 4, 5, 1, 4]) = |[1, 4, 5, 1, 4]|=5$. 最大化 $seg(a^{(0)})+seg(a^{(1)})$.

### 输入格式

  第一行包括一个正整数 $n(1\leq n\leq 10^5)$.

  第二行包括 $n$ 个正整数 $a_1, a_2, \cdots,a_n(1\leq a_i\leq n)$.

### 输出格式

  仅输出一个正整数, 代表最大的 $seg(a^{(0)})+seg(a^{(1)})$.

### 解法

  我们考虑贪心. 假设现在是第 $k$ 位, 考虑将其加入 $a^{(0)}$ 或者 $a^{(1)}$. 我断言我们将会将其加入 $a^{(0)}$, 当且仅当 $a^{(0)}$ 的最后一位等于 $a_k$, 或者 $a^{(0)}$ 的最后一位在 $a$ 中下一次出现的位置**不大于** $a^{(1)}$ 的最后一位在 $a$ 中下次出现的位置. 否则, 如果我们将 $a_k$ 加入 $a^{(0)}$, 则一定不优于我们将 $a_k$ 加入 $a^{(1)}$, 因为我们将其加入 $a^{(1)}$ 选择更多.

### 代码

```cpp
#include<bits/stdc++.h>
#define f(i,x,y) for(int i=x, i##end=y; i<=i##end; ++i)
#define d(i,x,y) for(int i=y, i##end=x; i>=i##end; --i)
#define ll long long
char ch;
int rd() {
  int f=1, x=0; ch=getchar();
  while(!isdigit(ch)) { f=((ch=='-')?-1:f); ch=getchar(); }
  while(isdigit(ch)) { x=x*10+ch-'0'; ch=getchar(); }
  return x*f;
}
void rd(int& x) { x=rd(); }
using namespace std;
#define _ 1000005
int a[_], a0[_], a1[_], n, tot0, tot1;
int pos0[_], pos1[_], nxt[_], Nxt[_], ans;
std::vector<int> pos[_];
int main() {
  rd(n); f(i,1,n) rd(a[i]); d(i,1,n) { nxt[i]=Nxt[a[i]] ? Nxt[a[i]] : n+1; Nxt[a[i]]=i; } nxt[0]=n+1;
	f(i,1,n) {
		int xp=nxt[pos0[tot0]], yp=nxt[pos1[tot1]];
		if(a0[tot0] == a[i]) xp=n+2;
		if(a1[tot1] == a[i]) yp=n+2;
		if(xp <= yp) { ans+=(a0[tot0]!=a[i]); a0[++tot0]=a[i]; pos0[tot0]=i; }
		else { ans+=(a1[tot1]!=a[i]); a1[++tot1]=a[i]; pos1[tot1]=i; }
	}
	printf("%d\n", ans);
  return 0;
}
```

---

