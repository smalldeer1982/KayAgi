# 「ALFR Round 4」C 粉碎

## 题目描述

斌宝在玩纸牌。起初，他有 $n$ 张牌，第 $i$ 张牌的点数为 $A_i$。

斌宝会重复执行 $n$ 轮以下操作，第 $i$ 轮操作如下：

1. 斌宝需要选择将第 $i$ 张牌置于牌堆的最左边或者最右边；
2. 若牌堆中存在两张点数相同的牌，则斌宝会**立即**将两张牌之间的所有牌从牌堆取出，扔进碎纸机（包括这两张牌本身）。

总是会先执行插入操作再执行粉碎操作。

牌堆初始为空。

你需要告诉斌宝他最多能粉碎多少张牌。

## 说明/提示

### 样例解释

初始牌堆：$\{\}$

放入 $1$：$\{1\}$；

放入 $3$：$\{1,3\}$；

放入 $3$：$\{3,1,3\}$，然后粉碎：$\{\}$；

放入 $1$：$\{1\}$；

放入 $2$：$\{1,2\}$；

放入 $1$：$\{1,2,1\}$，然后粉碎：$\{\}$；

放入 $2$：$\{2\}$；

放入 $2$：$\{2,2\}$，然后粉碎：$\{\}$；

所有牌均被粉碎。

### 数据范围

| 子任务 | 分值 | 限制 |
| :----------: | :----------: | :----------: |
| $0$ | $20$ | $n\le 20$|
| $1$ | $20$ | $T=1,n=10^3$ 且 $A_i$ 在 $[1,n]$ 内随机生成 |
| $2$ | $40$ | $n\le10^3$ |
| $3$ | $20$ | - |

对于 $100\%$ 的数据，$1\le T\le5$，$1\le n\le5\times10^5$，$1\le A_i\le n$。

## 样例 #1

### 输入

```
4
8
1 3 3 1 2 1 2 2
8
3 2 2 1 2 1 2 1
6
1 2 1 2 1 2
6
1 2 3 4 5 6```

### 输出

```
8
7
6
0```

# 题解

## 作者：sdyzpf (赞：14)

### 思路

出题人题解。首先思考一个结论，最优的粉碎方案一定是粉碎整个序列的一段前缀，欲证明该结论，只需考虑最后一次粉碎操作即可。如果一对能匹配上的牌分别出现在原序列的 $l$ 和 $r$ 两个位置，则我们可以通过操作把 $[1,r]$ 的牌全粉碎掉。所以，计算最多能粉碎多少张牌，可以转化成求出最后一张可以匹配的牌的位置。

令 $dp_i$ 表示把 $[1,i-1]$ 中所有和 $a_i$ 相等的牌全部粉碎掉的可行性，其中 $dp_i=0$ 表示不可行， $dp_i=1$ 表示可行。令 $pre_i$ 表示上一张和 $a_i$ 相等的牌的位置。注意到，作为更晚出现的牌，$i$ 只有可能和 $pre_i$ 进行匹配，所以 $i$ 是一对可以匹配的牌中更晚被插入的那张，当且仅当 $dp_{pre_i}=1$。

考虑如何进行转移。$dp_i=[pre_i能否在i之前被粉碎]$。$pre_i$ 被粉碎有两种方式，一种是与 $pre_{pre_i}$ 匹配，另一种是被 $j\in(pre_i,i)$ ，$j$ 与 $pre_j$ 匹配粉碎掉了。两种方式分别对应以下两种转移：
$$
dp_i|=dp_{pre_{pre_i}}
$$

$$
dp_i|=dp_{pre_j},j\in(pre_i,i)
$$

合并一下就是：
$$
dp_i|=dp_{pre_j},j\in[pre_i,i)
$$
此时我们已经得到的 $O(n^2)$ 的做法，优化也是容易的，前缀和优化即可，转移如下：
$$
c_i=c_{i-1}+f_{pre_i}
$$

$$
dp_i=[c_{pre_i-1}<c_{i-1}]
$$

 于是我们得到了 $O(n)$ 做法。

### 代码

``` cpp
#include <bits/stdc++.h>
using namespace std;

int a[500010],d[500010],p[500010],c[500010];
bool f[500010];

int main(){
    int t,n,ans;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);ans=0;
        memset(d,0,sizeof(d));
        for(int i=1;i<=n;i++)
            scanf("%d",a+i),p[i]=d[a[i]],d[a[i]]=i;
        for(int i=1;i<=n;i++){
            f[i]=(c[p[i]-1]<c[i-1]||!p[i]);
            c[i]=c[i-1]+(int)f[p[i]];
			if(f[p[i]])ans=i;
        }
		printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：szh_AK_all (赞：5)

验题人题解。

## 分析
考虑贪心。

对于每次加进来的牌的点数，可以用一个数组记录下他的匹配情况，设 $b_i$ 表示点数为 $i$ 的牌还有多少张未匹配，注意到点数相同的牌两两匹配，并且每当存在 $2$ 张相同的牌时，这 $2$ 张牌一定会被粉碎掉。所以在正常情况下，$b_i$ 的值为 $0$ 或者 $1$。

对于每个加进来的点数为 $A_i$，若 $b_{A_i}$ 不为 $0$，则代表可以有牌与这张牌匹配，那么匹配就可以有两种作用，下面分类讨论。

第一种作用：这张牌与另一张点数相同的牌一个在排队最左边，一个在最右边，显然这是容易做到的，那么这样就可以消掉 $i$ 张牌。

第二种作用：可以特意将这两张牌夹着某张编号为 $j$ 的牌（前提是 $j<i$ 且 $A_j\ne A_i$，以及 $j$ 没被匹配过，这是显然的），那么这样有什么用呢？这个匹配方式使用或不使用，代表着在以后得时刻点数为 $A_j$ 的牌是否有未匹配的，那么既然可以保证 $b_{A_j}$ 为我想要的值，并且 $b_{A_j}$ 不为 $0$ 时才是有用的，那么不妨直接设 $b_{A_j}$ 为无穷大（这是因为对于新加入的点数 $x$，若 $b_x$ 不为 $0$ 则按照一开始所提及的匹配情况，程序会令 $b_x$ 减一）。

然后就是，多测不清空，爆龄两行泪。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[500005], b[500005], p[500005], gan[500005];

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		for (int i = 1; i <= n; i++)
			cin >> a[i];
		int ans = 0;
		int k = 0;
		for (int i = 1; i <= n; i++) {
			if (b[a[i]]) {
				ans = i;
				p[i] = 1;//匹配过
				for (int j = i - 1; j >= 1; j--) {
					if (gan[j])
						break;
					gan[j] = 1;
					if (!p[j] && a[j] != a[i])
						b[a[j]] = 1000000000;
				}
				b[a[i]]--;
			} else
				b[a[i]]++;
		}
		for (int i = 1; i <= n; i++)
			b[a[i]] = p[i] = gan[i] = 0;
		cout << ans << '\n';
	}
	return 0;
}
```
可以发现，这份代码里用了一个“前缀优化”，就是由于每次修改是要修改一个前缀，而以前被修改过的地方就无需再进行修改了，这样就可以保证每个位置最多只会被修改一次，复杂度是 $O(n)$ 的。

其实，这个优化还有一个精到之处，由于对于每次可以匹配、发挥作用的位置 $i$，它可以影响前 $i-1$ 个位置，那么对于另一个可以匹配的位置 $j(j>i)$，它是否可以影响前 $(i-1)$ 个位置呢？答案是不能，因为可以看做前 $i-1$ 个位置是 $i$ 所占据的地盘，那么在前 $j-1$ 个位置中没被占据的位置才是属于 $j$ 的。所以这个优化也保证了正确性。

---

## 作者：luxiaomao (赞：4)

## [P11013](https://www.luogu.com.cn/problem/P11013) 有趣的 DP 题

赛时竟然场切蓝了，蒟蒻泪目。

细节向题解，大家也可以直接读结论和公式。

## Problem

有 $n$ 张牌，第 $i$ 张牌点数为 $A_i$。

初始时有一个空队列。每次将第 $i$ 张牌插入队列的左边或右边，如果插入后队列中存在两张点数一样的牌，则将这两张牌以及它们中间的牌全部删去。

问最多能粉碎多少张牌。

## Solution

我们先考虑 $n \le 10^3$ 的部分，考虑 $O(n^2)$ 的 DP。

首先分析一下题目：

我们先 $O(n)$ 记出每张牌 $i$ 前面跟它最近的相同牌 $las_i$。有一个性质：

> 如果牌 $i$ 引发了删除，那只能是和 $las_i$ 一起引发的。
>
> 为什么？记 $j = las_i$，$k = las_j$。如果 $i$ 和 $k$ 一起引发了删除，那么显然 $k$ 能一直保留到 $i$ 而没被删掉。既然如此，$j$ 加入队列的时候定然会和 $k$ 引发删除，所以 $i$ 无法和 $k$ 一起引发删除。
>
> 综上，如果牌 $i$ 引发了删除，那只能是和牌 $j$，即 $las_i$ 一起引发的。

好，有了这一步，我们继续。

这题的关键在于，牌 $i$ 能否引发删除？如果可以，那么只要把 $las_i$ 放在最左，$las_i$ 和 $i$ 之间的牌都放在最右，$i$ 也放在最右，就能保证把 $1$ 到 $i$ 之间的所有牌都删去。

我们记 $f_{i,0}$ 为“前 $i$ 张牌，第 $i$ 张牌引发删除剩下的最小牌数”，显然如果 $i$ 能引发删除，$f_{i,0} = 0$。

记 $f_{i,1}$ 为“前 $i$ 张牌，第 $i$ 张牌没有引发删除剩下的最小牌数”，显然如果 $i$ 不能引发删除，$f_{i,1} = \min\{f_{i-1,0},f_{i-1,1}\}+1$。

答案就是 $n-\min\{f_{n,0},f_{n,1}\}$。

**然而，有这么简单吗？**

我们来看一组样例：

```
1
4
5 9 5 9
```

显然答案为 $4$，但是按照我们刚才的思路，第二个 $5$ 会把所有牌都贪心地删掉，导致最后一个 $9$ 无法引发删除，得到 $3$ 的错误答案。

之所以出错，是因为第一个 $9$ 其实可以被删，也可以不被删，我们粗略地以为它绝对被删掉了。

那我们记 $flag_i$：

- $flag_i = 0$，表示牌 $i$ 绝对会被删去。

- $flag_i = 1$，表示牌 $i$ 绝对会被保留。
 
- $flag_i = 2$，表示牌 $i$ 可以被删去，也可以保留。

然后转移方程这么写：

```cpp
flag[0] = 0;
for(int i = 1;i <= n;i++)
{
	int j = las[i];
	if(flag[j] == 0)//如果j被删去，那i只能保留。 
	{
		flag[i] = 1;
		f[i][1] = min(f[i-1][0],f[i-1][1])+1;
	}
	if(flag[j] == 1)//如果j被保留，那i只能引发删除。 
	{
		flag[i] = 0;
		f[i][0] = 0;
		for(int k = 1;k < i;k++)//注意这里。
			if(flag[k] == 1 && k!=j)flag[k] = 2; 
	}
	if(flag[j] == 2)//如果j可留可不留，那么i也可留可不留。 
	{
		flag[i] = 2;
		f[i][0] = 0;
		f[i][1] =  min(f[i-1][0],f[i-1][1])+1;
		for(int k = 1;k < i;k++)//注意这里。
			if(flag[k] == 1)flag[k] = 2; 
	}
}
```

这样就用 $O(n^2)$ 的时间复杂度得到了 80 pts 的好成绩。

那么如何优化？根据 $T\le5,n \le 5 \times 10^5$ 的数据，要用接近 $O(n)$ 的时间复杂度。

请看上面代码两段 `//注意这里。` 的地方，本质上就是把前 $i$ 张牌中 $flag_k = 1$ 的置为 $flag_k = 2$。

那我们新建一个变量 $kill$（谁教你这么起名的），表示前 $kill$ 张牌中 $flag_k = 1$ 的置为 $2$。

当调用到一张牌时，再看看它的 $flag$ 是否需要修改即可。

具体实现请看代码。

## Code

```cpp
#include<bits/stdc++.h>
#define N 500005
using namespace std;

int T,n,a[N];
int now[N],las[N];
int flag[N],f[N][2];

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		int kill = 0;
		scanf("%d",&n);
		for(int i = 1;i <= n;i++)now[i] = 0,f[i][0] = f[i][1] = 1e9;
		for(int i = 1;i <= n;i++)
		{
			scanf("%d",&a[i]);
			las[i] = now[a[i]];
			now[a[i]] = i;
		}
		flag[0] = 0;
		for(int i = 1;i <= n;i++)
		{
			int j = las[i];
			if(j <= kill && flag[j] == 1)flag[j] = 2;
			if(flag[j] == 0)
			{
				flag[i] = 1; 
				f[i][1] = min(f[i-1][0],f[i-1][1])+1;
			}
			if(flag[j] == 1)
			{
				flag[i] = 0;
				f[i][0] = 0;
				kill = i;
			}
			if(flag[j] == 2)
			{
				flag[i] = 2;
				f[i][0] = 0;
				f[i][1] = min(f[i-1][0],f[i-1][1])+1;
				kill = i;
			}
		}
		printf("%d\n",n-min(f[n][0],f[n][1]));
	}
	return 0;
}
```

写作不易，感谢阅读。

---

## 作者：aeiouaoeiu (赞：2)

定义 $\text{pre}_i$ 表示满足 $1\le j<i,a_j=a_i$ 的最大的 $j$。

如何消除一个前缀 $[1,i]$？我们将 $\text{pre}_i$ 放到左边，将 $\text{pre}_i<j\le i$ 放到右边，于是可以消除 $[1,i]$。

问题就在于 $\text{pre}_i$ 是否会与 $\text{pre}_{\text{pre}_i}$ 匹配并被消去，我们需要一个 $j$ 使得 $\text{pre}_{\text{pre}_i}\le j<\text{pre}_i$ 并且 $[1,j]$ 可以被消去。

于是我们可以进行 dp。设 $f_i$ 表示 $[1,i]$ 是否可以被消去。到 $f_i$ 时，从 $f_{\text{pre}_{\text{pre}_i}}$ 到 $f_{\text{pre}_i-1}$ 转移即可。

显然，若消去一个前缀 $[1,i]$ 后还可以再消去一个 $[i+1,j]$，则 $[1,j]$ 也可以被消去。所以答案即为满足 $f_i=1$ 的最大的 $i$。

$f$ 可以通过前缀和优化转移，时间复杂度 $\mathcal{O}(n)$。

赛时脑瘫写了个树状数组优化。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=500007,ee=1e18;
ll n,a[maxn],buc[maxn],pre[maxn],f[maxn];
struct Tree{
	ll val[maxn];
	void upd(ll x,ll k){for(;x<=n;x+=x&(-x)) val[x]+=k;}
	ll sum(ll x){ll E=0; for(;x;x-=x&(-x)) E+=val[x]; return E;}
}tree;
int main(void){
	//freopen("data.in","r",stdin);
	ios::sync_with_stdio(0),cin.tie(0);
	ll T=1; cin>>T;
	for(;T--;){
		for(int i=1;i<=n;i++) buc[i]=pre[i]=0;
		memset(tree.val,0,sizeof(tree.val));
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i]; f[i]=0,pre[i]=buc[a[i]];
			buc[a[i]]=i;
		}
		for(int i=1;i<=n;i++){
			if(!pre[i]) continue;
			if(!pre[pre[i]]){f[i]=1; tree.upd(i,1); continue;}
			if(tree.sum(pre[i]-1)-tree.sum(pre[pre[i]]-1)) f[i]=1,tree.upd(i,1);
		}
		//for(int i=1;i<=n;i++) cout<<f[i]<<" "; cout<<"\n";
		f[0]=1;
		for(int i=n;i>=0;i--)if(f[i]){cout<<i<<"\n"; break;}
	}
	return 0;
}
```

---

## 作者：_O_v_O_ (赞：1)

赛时没切导致等级分在一个刚好比 1600 高一点的位置，亏大了。

好题啊。

文中粉碎写成消除了，请读者自行理解。

首先，先思考一下消的方式。

很显然假如存在 $(i,j)$ 满足 $i<j$ 且 $a_i=a_j$ 且 $i\sim j$ 没有 $k$ 满足 $a_k=a_i$，那么可以在到 $i$ 时把 $i$ 放在最左边，到 $j$ 时把 $j$ 放在最右边，那么这样就能把 $1\sim j$ 全部消完。

那么就能得出结论：每次消除掉的绝对是序列的一段前缀。

那么我们就设 $dp_i$ 为能否消掉序列的 $1\sim i$ 项，设 $pre_i$ 为上一个与 $a_i$ 相同的值，那么 $a_i$ 只能与 $pre_i$ 匹配。

那么 $dp_i=1$ 的条件当且仅当 $pre_i$ 未被消除，而 $pre_i$ 在何种条件下会保留呢？很显然没被 $pre_{pre_i}$ 消除且没被一个位于 $[pre_i,i]$ 的 $j$ 消除。

那么这两种转移分别是：

$$dp_i=\max\{dp_{pre_{pre_i}},\max_{j=pre_i+1}^{i-1} dp_{pre_j}\}$$

等价于：

$$dp_i=\max_{j=pre_i}^{i-1} dp_{pre_j}$$

很显然这一大坨东西是可以用线段树优化的，没写过所以不知道能不能过。但是我们要 $O(n)$ 做法，所以考虑前缀和优化。

我们设 $f_i=f_{i-1}+dp_{pre_i}$，很显然判断一段区间 $[l,r]$ 内 $dp_{pre_i}$ 是否全不为 $0$ 只用判断 $f_r\neq f_{l-1}$ 即可。

那么最终的 dp 式子就是：

$$dp_i=[f_{i-1}\neq f_{pre_i-1}]$$ 

代码是简单的：


```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=5e5+5;
int T,n,a[N],d[N],p[N],c[N],f[N],ans;

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>T;while(T--){
		ans=0;cin>>n;
		memset(d,0,sizeof(d));
		for(int i=1;i<=n;i++){
			cin>>a[i];
			p[i]=d[a[i]];
			d[a[i]]=i;
		}
		for(int i=1;i<=n;i++){
			f[i]=(c[p[i]-1]!=c[i-1]||!p[i]);
			c[i]=c[i-1]+f[p[i]];
			if(f[p[i]]) ans=i;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Kendieer (赞：1)

扫描了一圈题解，发现大部分和我的思路不一样，这里分享一下我的思路。

## 思路

对于每一张卡牌，我们可以记录两种状态: 存在牌堆，不存在牌堆。

对于每一次插入，我们存在两种简单情况:

+ 场上不存在时，即确认场上对应卡牌数量为 $0$ 时，对应数量 $+1$。
+ 场上存在一张时，对应的卡牌数量 $-1$。

上述的情况为能准确确认卡牌状态的情况，但事实上很多卡牌的状态无法准确确认。

我们对于每次消除，能否准确令剩余牌堆中**任意指定**卡牌(不包含自身)被消除?\
其实只要放被消除区间的另一侧即可。

于是我们可以知道一个结论: 对于一张能够被消除的卡牌，我们可以任意决定这张卡牌是否存在牌堆中，我们可以用 $-1$ 标记这种不确定状态。

对于任意状态为 $-1$ 的卡牌，这种卡牌后续继续出现同种卡牌，我们可以令之前的状态为 $1$，使当前状态为 $0$，使中间所有卡牌标记为 $-1$；也可以令之前状态为 $0$（即被之前卡牌的消除），当前为 $1$，依然为不确定状态。

因此，我们总结出：对于每次消除，如果当前这种牌状态为为 $1$，即可以准确确认有且仅有一张，我们修改其为 $0$，如果状态为 $-1$，则不变。

所有操作结束后，我们可以令所有 $-1$ 状态的卡牌变为 $0$，最终剩余卡牌数量就是状态为 $1$ 的卡牌数量。

## 实现思路

开一个容量为 $n$ 的桶，用于标记状态。

然后使用双指针扫描卡牌，右指针为牌堆内的新卡牌，左指针为更新状态指针。

时间复杂度为 $O(n)$。

**多组测试数据记得清空。**

## 参考代码

``` cpp
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
#define rep(i,a,b) for(ll i=a;i<b;i++)
#define repr(i,a,b) for(ll i=b-1;i>=a;i--)
typedef long long ll;
typedef unsigned long long ull;

ll qread(){
    int ch = getchar();
    ll s=1,r=0;
    while(ch=='\r'|| ch == '\n' || ch == ' ')
        ch = getchar();
    if (ch == '-'){
        s=-1;
        ch=getchar();
    }
    while(ch>='0'&& ch <= '9'){
        r=r*10+ch-'0';
        ch = getchar();
    }
    return r*s;
}

template <typename ... Args>
void qread(Args&&... e){
    ((e=qread()),...);
}

const int maxn = 5e5+7;

int mp[maxn];

void solve(){
    int n = qread();
    int arr[n];
    ll ans = 0;
    rep(i,0,n){
        arr[i] = qread();
    }
    rep(i,0,n+1){
        mp[i] = 0;
    }
    int l = 0;
    rep(r,0,n){
        if (mp[arr[r]] == 1 || mp[arr[r]] == -1){
            int type = mp[arr[r]];
            while(l <= r){
                ans ++;
                mp[arr[l]]=-1;
                l++;
            }
            if (type == 1){
                mp[arr[r]] = 0;
            } else {
                mp[arr[r]] = -1;
            }
        } else {
            mp[arr[r]] = 1;
        }
    }
    cout << ans << endl;
}

int main(){
    int n = qread();
    while (n--)
        solve();
    return 0;
}
```

---

## 作者：FreedomKing (赞：1)

### 思路

考虑使粉碎掉的纸牌数量最大化的贪心策略，若有一对未被粉碎的点数相同的纸牌 $i,j,(i<j)$ 未被粉碎，则可以先将纸牌 $i$ 加入到牌堆的一侧，$i+1$ 到 $j$ 的所有纸牌都加入到另一侧，可以粉碎所有 $1$ 到 $j$ 之间的纸牌。

能粉碎纸牌当且仅当存在这么一对没有被粉碎的点数相同的纸牌，所以推导出被粉碎掉的纸牌只能是原序列的一段前缀的性质。

考虑记 $pre_i$ 表示第 $i$ 张纸牌前的第一个与其拥有相同点数的纸牌的位置，$f_i=1$ 表示第 $i$ 张纸牌可以**暂时**不被粉碎，$maxn$ 表示前 $maxn$ 张纸牌都能被粉碎。

考虑分讨：

- 若第 $pre_i$ 张纸牌既可以粉碎也可以暂时保留，则第 $i$ 张纸牌也可以选择粉碎或暂时保留，更新 $f_i=1,maxn=i$。

- 若第 $pre_i$ 张纸牌不能被粉碎，则第 $i$ 张纸牌必然会与 $pre_i$ 粉碎，按照上文的策略直接更新 $maxn=i$。

- 若第 $pre_i$ 张牌不能被暂时保留，则第 $i$ 张纸牌一定能被暂时保留下来，只更新 $f_i=1$。

时间复杂度 $O(n)$，可以通过。代码目前是最优解第四，记的 $f$ 我感觉是可以优化掉的但是懒得优化了。

### AC Code

```cpp
#include<bits/stdc++.h>
//#pragma GCC optimize("Ofast")
bool M1;
#define look_memory cerr<<abs(&M2-&M1)/1024.0/1024<<" MB\n"
#define look_time cerr<<(clock()-Time)*1.0/CLOCKS_PER_SEC<<'\n'
#define File(_) freopen(_".in","r",stdin);freopen(_".out","w",stdout)
//#define int long long
using namespace std;
namespace FreedomKing_qwq{};
using namespace FreedomKing_qwq;
const int N=5e5+5,mN=3e4+5,mod=1e9+7;
namespace FreedomKing_qwq{
#define Time 0
#define lowbit(_) (_&-_) 
	struct Tree{
		int tree[N];
		inline void add(int x,int j){
			for(int i=1;i<=x;i+=lowbit(i)) tree[i]+=j;
			return;
		}
		inline int query(int x){
			int ans=0;
			for(int i=x;i>1;i-=lowbit(i)) ans+=tree[i];
			return ans;
		}
	};
	struct Dset{
		int fa[N];
		inline void init(int x){
			for(int i=1;i<=x;i++) fa[i]=i;
			return;
		}
		inline int find(int x){
			return (fa[x]==x?x:fa[x]=find(fa[x]));
		}
		inline void update(int x,int y){
			x=find(x);y=find(y);
			fa[y]=x;
			return;
		}
	};
#define lc (p<<1)
#define rc (p<<1|1)
	inline int qread(){
#define qr qread()
		int x=0,c=getchar(),t=1;
		while(c<'0'||c>'9'){
			t^=(c=='-');
			c=getchar();
		}
		while(c>='0'&&c<='9'){
			x=(x<<3)+(x<<1)+c-'0';
			c=getchar();
		}
		return (t?x:-x);
	}	
	inline void qwrite(int x){
#define qw(_) qwrite(_)
#define qws(_) qw(_),putchar(' ')
#define qwe(_) qw(_),putchar('\n')
		if(x<0) x=-x,putchar('-');
		if(x>9) qwrite(x/10);
		putchar(x%10+'0');
		return;
	}
	inline int qpow(int x,int p,int mod){
		x=(p?x:1);
		mod=(mod?mod:LONG_LONG_MAX);
		int t=1;
		while(p>1){
			if(p&1) t=(t*x)%mod;
			x=(x*x)%mod;
			p>>=1;
		}
		return (x*t)%mod;
	}
	inline int gcd(int x,int y){return (x%y==0?y:gcd(y,x%y));}
	inline int lcm(int x,int y){return (x/gcd(x,y)*y);}
#define pf(_) ((_)*(_))
}
int a[N],pre[N],lst[N],maxn;
bool f[N];
bool M2;signed main(){
	int T=qr;
	while(T--){
		int n=qr;
		memset(pre,0,sizeof(pre));
		memset(lst,0,sizeof(lst));
		memset(f,false,sizeof(f));
		for(int i=1;i<=n;i++){
			a[i]=qr;
			pre[i]=lst[a[i]];
			lst[a[i]]=i;
		}
		maxn=0;
		for(int i=1;i<=n;i++){
			if(!pre[i]){
				f[i]=true;
				continue;
			}
			if(f[pre[i]]&&pre[i]<=maxn){
				maxn=i;
				f[i]=true;
			}
			if(f[pre[i]]&&(pre[i]>maxn)) maxn=i;
			if(!f[pre[i]]&&pre[i]<=maxn) f[i]=true;
		}
		qwe(maxn);
	}
	return 0;
}
```

---

## 作者：wcy110614 (赞：0)

定义 $prv[i]$ 是最大的满足 $a[j]=a[i]$ 并且 $j\leq i$ 的 $j$ 。也就是左边的和 $i$ 相等的第一个 $j$。

先考虑朴素的 $dp$： $f[i]$ 表示 $prv[i]$ 是否能被消掉，如果 $f[i]=1$ 那么就可以消掉。所以 $f[prv[i]]=1$ 时 $prv[i]$ 可以保留下来。

既然 $prv[i]$ 可以保留下来，那么一定存在一种方案可以使得 $prv[i]$ 和 $i$ 正好可以消掉 $[1-i]$ 的所有牌。此时 $ans=i$。

所以统计答案：$ans=\max_{i=1}^n i\qquad (f[prv[i]]=1)$。

考虑 $f[i]$ 的转移。分类讨论如下：

1. $prv[i]$ 和 $prv[prv[i]]$ 可以消掉，这时 $f[i]=1$。

2. $prv[i]$ 可以被中间存在的 $j$ 夹起来消掉，也就是有一个 $j$ 可以和 $prv[j]$ 消掉。

只要有一种成立，那么 $i$ 就可以被留下来。

综上所述，方程如下：

$$f[i]= \max_{p[i] \leq j < i} f[p[j]]\qquad$$


当然，这种做法是 $\mathcal{O(n^2)}$ 的。

代码如下：

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=5e5+10;
int a[N],p[N],la[N],c[N],f[N];
int n,T;
void solve(void){
	int ans=0;
	memset(la,0,sizeof la);
	memset(f,0,sizeof f);
	cin>>n;
	for(int i=1;i<=n;++i)cin>>a[i],p[i]=la[a[i]],la[a[i]]=i;
	for(int i=1;i<=n;++i){
		for(int j=p[i];j<i;++j)/*printf("f [ %d ] |= f[ %d ] ( %d )\n",i,p[j],f[p[j]]),*/f[i]|=f[p[j]];
		if(p[i]==0)f[i]=1;
	}
	for(int i=1;i<=n;++i)if(f[p[i]])ans=max(ans,i);
	return cout<<ans<<"\n",void();
}
int main(){
    cin>>T;
	while(T--)solve();
	return 0;
}
```

考虑优化。记录一个前缀和 $c[i]$，这样转移就会变成 $\mathcal{O(1)}$ 的。

这样代码总复杂度就是 $\mathcal{O(n)}$ 的。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=5e5+10;
int a[N],p[N],la[N],c[N],f[N];
int n,T;
void solve(void){
	int ans=0;
	memset(la,0,sizeof la);
	memset(c,0,sizeof c);
	memset(f,0,sizeof f);
	cin>>n;
	for(int i=1;i<=n;++i)cin>>a[i],p[i]=la[a[i]],la[a[i]]=i;
	for(int i=1;i<=n;++i){
		f[i]|=(c[p[i]-1]<c[i-1]);
		if(p[i]==0)f[i]=1;
		c[i]=c[i-1]+f[p[i]];
	}
	for(int i=1;i<=n;++i)if(f[p[i]])ans=max(ans,i); 
	return cout<<ans<<"\n",void();
}
int main(){
	cin>>T;
	while(T--)solve();
	return 0;
}
```

---

## 作者：ELECTRODE_kaf (赞：0)

用 $pre_{i}$ 记录 $a_{i}$ 的前驱，$ans$ 记录可以被删除的数中最靠右的一个的下标。

首先，如果 $a_{i}$ 可以被删除，那么 $a_{j}(1 \le j < n-1)$ 也一定可以被删除。简证：因为 $a_{i}$ 前后有同一个数字 $a_{l}=a_{r}$，所以只需要把 $a_{l}$ 放在最左侧，$a_{r}$ 放在最右侧就行。

按顺序放置意味着每个数字只会和它的前驱配对。

用 $dp_{i,0/1}$ 表示 $a_{i}$ 能否被删除 / 保留。

如果 $a_{i}$ 没有前驱，那么 $dp_{i,0}=0,dp_{i,1}=1$。（只能保留）

如果 $a_{i}$ 有前驱：

如果 $pre_{i}$ 可以被删除，也可以被保留，那么 $dp_{i,0}=dp_{i,1}=1$，并将 $ans$ 更新至 $i$。（当前数同样既可以被删除，也可以被保留）

如果 $pre_{i}$ 只可以被删除，那么 $dp_{i,0}=0,dp_{i,1}=1$。（只能保留）

如果 $pre_{i}$ 只可以被保留，那么 $dp_{i,0}=1,dp_{i,1}=0$，并将 $ans$ 更新至 $i$。（只能删除）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,x,y) for(ll i=x;i<=y;i++)

const ll N=6e5;
ll q,n,a[N],bu[N],pre[N],dp[N][2],ans;

void ini() {
	rep(i,1,n) {
		bu[i]=-1;
	}

	dp[1][0]=0;
	dp[1][1]=1;
	ans=0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>q;

	while(q--) {
		cin>>n;
		ini();

		rep(i,1,n) {
			cin>>a[i];
			pre[i]=bu[a[i]];
			bu[a[i]]=i;
		}

		rep(i,2,n) {
			if(pre[i]==-1) {
				dp[i][0]=0;
				dp[i][1]=1;
			}else if((dp[pre[i]][0]||ans>=pre[i])&&dp[pre[i]][1]){
				dp[i][0]=dp[i][1]=1;
				ans=i;
			}else if((dp[pre[i]][0]||ans>=pre[i])){
				dp[i][0]=0;
				dp[i][1]=1;
			}else{
				dp[i][0]=1;
				dp[i][1]=0;
				ans=i;
			}
		}
		
		cout<<ans<<'\n';
	}
}
```

---

## 作者：Fasfree (赞：0)

# 题解：P11013 「ALFR Round 4」C 粉碎

## 简要题意

给出一个包含 $n$ 个整数的数列 $A$，依次将数字加入一个双端队列中。对于每个数字，可以选择从队首或队尾加入。当队列中出现相同数字时，它们之间的所有数字将被消去（包括相同数字本身），求能够消去的最大数字个数。


## 思考

通过题意，可得到以下结论：

> 对于 $A_i = A_j （i < j，不存在h < i，使A_h = A_i）$ ，一定存在一个操作方案，使 $A_{1...j}$ 均被消去。

由于我们显然能够将其他整数通过操作在队列中置于 $A_i, A_j$ 中间，因此我们不需要关心 $A_{1...j}$ 中间出现过哪些其他相同整数。

而求能够消去的最大数字个数自然转化为求最靠近 $A$ 末尾的两个**能够相互匹配**的数字。

## 解决问题

当操作至第 $i$ 个整数 $A_i$ 时，有以下3种情况：

+ 在此之前队列中未曾出现过 $A_i$。

+ 队列中出现过 $A_i$，但是尚无另一个 $A_i$ 与其匹配。

+ 队列中出现过 $A_i$，且已被上上个操作过的 $A_i$ 成功匹配。


### 情况1

加入 $A_i$ 不会导致任何整数被消去。

### 情况2

根据前文结论，加入 $A_i$ 后，我们可以将 $A_{1...i}$ 全部消去，随后更新答案。

### 情况3

此时问题变得麻烦了一些，如果我们按照情况1中的做法将这个 $A_i$ 视为队列中一个新的数字显然不一定是最优的。也许通过操作使上一个 $A_i$ 与本次操作的 $A_i$ 匹配，然后消去 $A_{1...i}$ 更优。



---


记 $pre_a$ 为 $A$ 中上一个整数 $a$ 的位置或 $A$ 中上一对成功匹配的 $a$ 的第一个整数的位置。

$isp_a = 1/0$ 表示上一个 $a$ 是否已成功匹配。 

$lsp_a$ 表示上一对成功匹配的 $a$ 的第二个整数的位置。

$cbr_i = 1/0$ 表示 $A_i$ 是否**能够**被消去。

$who_i = b$ 表示 $A_i$ 在操作顺序中**最早**可被 $A_b$ 消去。

$lst$ 表示上一个能被消去的整数在 $A$ 中的位置。

考虑第三种情况：

如果需要让本次的 $A_i$ 与上一个已经配对的 $A_i$重新配对，显然只能设法将上上个 $A_i$ 通过操作消去。

记 $A_i$ 为 $f$，对于 $pre_{f}$ 与 $lsp_{f}$，我们能够消去$pre_{f}$并保留 $lsp_{f}$，当且仅当：

$$
  \begin{cases}
  cbr_{pre_f} = 1\\
   who_{pre_f} \neq who_{lsp_f}
  \end{cases}
$$

前一个很好理解，后一个通俗的说，就是 $pre_f$ 必须在通过与 $lsp_f$ 相遇被消去前就能被其他数字消去，原因显然。

证明这样做不会使答案更劣也很简单，因为这样操作后，对于下一个 $f$，显然 $who_{pre_f} \neq who_{lsp_f}$。

到这里解法就已经完备了，最终时间复杂度 $O(n)$。

# AC code


```cpp
//
// Created by 32373 on 2024/8/30.
//

#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const ll N=500005;
ll n;
ll seq[N], cbr[N], lst, pre[N], isp[N], lsp[N], ans, who[N];


int32_t main(){
    ll t;
    scanf("%lld", &t);
    while (t--) {
        lst = 1, ans=0;
        scanf("%lld", &n);
        for (ll x = 1; x <= n; ++x) {
            scanf("%lld", &seq[x]);
            cbr[x] = 0;
            pre[x] = 0;
            isp[x] = 0;
            lsp[x] = 0;
            who[x] = 0;
        }
        for (ll x=1;x<=n;++x){
            if (not pre[seq[x]]){
                pre[seq[x]] = x;
                isp[seq[x]] = 0;
                continue;
            }
            if (not isp[seq[x]]){
                for (; lst <= x; ++lst){
                    cbr[lst] = 1;
                    who[lst] = x;
                }
                ans = x;
                isp[seq[x]] = 1;
                lsp[seq[x]] = x;
            } else {
                if (cbr[lsp[seq[x]]] and who[lsp[seq[x]]] != who[pre[seq[x]]]){
                    pre[seq[x]] = lsp[seq[x]];
                    for (; lst <= x; ++lst){
                        cbr[lst] = 1;
                        who[lst] = x;
                    }
                    lsp[seq[x]] = x;
                    ans = x;
                    isp[seq[x]] = 1;
                } else {
                    isp[seq[x]] = 0;
                    pre[seq[x]] = x;
                }
            }
        }
        printf("%lld\n", ans);
    }
}
```

---

