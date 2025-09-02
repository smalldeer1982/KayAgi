# Artem and Array 

## 题目描述

给定长度为 $n$ 的数组 $a$ ，你需要进行 $n$ 次操作：删去某一元素 $a_i$ ，并获得 $\min\{a_{i-1}, a_{i+1}\}$ 的分数。若不存在 $a_{i-1}$ 或 $a_{i+1}$，则此次操作不得分。

请你计算至多能得到多少分。

## 样例 #1

### 输入

```
5
3 1 5 2 6
```

### 输出

```
11
```

## 样例 #2

### 输入

```
5
1 2 3 4 5
```

### 输出

```
6
```

## 样例 #3

### 输入

```
5
1 100 101 100 1
```

### 输出

```
102
```

# 题解

## 作者：LittleMoMol (赞：12)

## 前言
思路很妙，在此我详细解释一下每一步操作背后的原因。

[欢迎博客食用](https://www.cnblogs.com/LittleMoMol-kawayi/p/Solution_Luogu_CF442C.html)

## 大致流程
1. 从前往后读入数组 $a$，对于一个下标 $pos$，若其满足 $a[pos-1] \ge a[pos]$ 且 $a[pos] \le a[pos+1]$，那么将答案 $ans+= \min(a[pos-1],\ a[pos+1])$，并删除 $a[pos]$。
2. 将 $a$ 数组中剩余数按从小到大排序，若 $a$ 数组中还剩下 $n$ 个数，那么让 $ans$ 再加上 $a$ 的前 $n-2$ 项即为答案。

## 理论基础

### 对于第一步

#### 为什么要找“V”型？

我们令 $a[pos-1] \ge a[pos]$ 且 $a[pos] \le a[pos+1]$，那么如果我们不删除 $a[pos]$ 而去删除 $a[pos-1]$ 或 $a[pos-1]$，那么得到的价值**最大也只能是** $a[pos]$；然而若删除 $a[pos]$，那么得到的价值为 $\min(a[pos-1], a[pos+1])$，由于 $a[pos-1]$ 和 $a[pos+1]$ 必然都是**大于等于** $a[pos]$ 的，所以删除 $a[pos]$ 更优。

#### 为什么见到一个“V”型就可以直接删除？

这个困扰了我许久，最终找到了答案。我们令“V”型三元组为 $(x,y,z)$，其中 $a[x] \ge a[y],\ a[y] \le a[z]$，那么可以发现**任意两个“V”型三元组的 $y$ 不可能相邻（除了这两个 $y$ 相等）**。

如果 $y$ 不相等，那么**每一个“V”型是互不影响的**，所以你先删哪个后删哪个效果是一样的。

如果 $y$ 相等，比如 $(x,\ y,\ y,\ y,\ z)$，容易发现你先删哪一个 $y$ 所获得的价值是一样的，都是 $a[y]$，那么顺序仍然不影响结果。

注意：**每一次删除可能不止删一个 $y$**

### 对于第二步

#### 单峰

你会发现剩下的 $a$ 数组中是**没有“V”型**的，这很显然。进一步地，它还是单峰的，如果说大白话，那就是“它下去了就上不来了”，因为**如果下去再上来，那么拐点处和其左右相邻的点构成一个“V”型**，这就矛盾了！

#### 不可能取到 $a$ 中的最大值和次大值

最大值肯定取不到，因为有次大值拖着后退呢~

次大值也取不到，为什么？**反证法**！如果可以取到次大值，那么必然存在一个下标 $pos$ 使得 $a[pos]$ 在最大值和次大值中间，那它们岂不是构成了“V”型？！矛盾！！

#### 能否将最大值和次大值之外的所有值都取一遍？

先举一个例子，直接上图！

[![vsbEzq.png](https://s1.ax1x.com/2022/08/20/vsbEzq.png)](https://imgse.com/i/vsbEzq)

（纵坐标即为对应值的大小）

- 删 $D$ 取 $C$
- 删 $C$ 取 $B$
- 删 $I$ 取 $F$
- 删 $F$ 取 $G$
- 删 $G$ 取 $H$
- 删 $B$ 取 $A$
- 最后删 $A,H$

大致方法就是永远删最上面的，即可保证。严格证明我也不会，~~感性理解叭~~。

#### 为什么最优解是将除了最大值和次大值之外的所有值都取一遍？

因为只能取除了最大值和次大值之外的值，所以我们只需证明，重复取同一个值只会使答案更劣。

对于一个下标 $pos$ 以及其对应的值 $a[pos]$，每一次删数操作，如果所删的数小于 $a[pos]$，那么这个操作对答案的贡献不可能是 $a[pos]$，这种情况就无需讨论了。

如果所删的数大于等于 $a[pos]$，那么 $a[pos]$ 是可以作为答案的贡献的。我们考虑如果删了两个数，对答案的贡献均为 $a[pos]$，那么这两个数必然是相邻的，而如果所删的两个数是相邻的，那么我们可以将这两个数删去的顺序换一下，答案一定不会变差，举个具体例子。

比如上面那张图，我们先删 $I$，再删 $D$，这两次操作的贡献都是 $F$ 对应的值；而如果我们先删 $D$，再删 $I$，贡献则为 $I+F$，更优。

## Code

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 5e5, INF = 0x3f3f3f3f;

int n, m;
int a[N];
LL ans;

int read()
{
	int s = 0, w = 1;
	char c = getchar();
	while (c < '0' && c > '9')
	{
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
	{
		s = s * 10 + c - '0';
		c = getchar();
	}
	
	return s * w;
}

int main()
{
	n = read();
	a[1] = read(), a[2] = read();
	
	if (n == 1)
	{
		cout << 0 << endl;
		return 0;
	}
	
	for (int i = 3; i <= n; i ++ )
	{
		cin >> a[i];
		while (a[i - 2] >= a[i - 1] && a[i - 1] <= a[i] && i >= 2)
		{
			ans += min(a[i - 2], a[i]);
			a[i - 1] = a[i];
			n -- ;
			i -- ;
		}
	}
	
	sort(a + 1, a + 1 + n);
	for (int i = 1; i <= n - 2; i ++ ) ans += a[i];
	
	cout << ans << endl;
	
	return 0;
}
```

## 后语

我自己曾经说过：“严谨的证明是好的，囫囵吞枣只去追求刷题量是可耻的。”~~（尽管我也经常囫囵吞枣）~~

反正是终于整完了！肝了好久，盼君一赞~

完结撒花！

---

## 作者：撤云 (赞：10)

[广告](https://www.cnblogs.com/hbxblog/p/11410296.html)

### $Solution$

观察发现如果一个数两边都比他大，删掉他可以保证最优，这个应该是显然的。这个东西用单调栈维护一下，最后剩下的就是个单调递减或单调递增的数列，从小到大排个序取前面$n-2$个,$n$为数列长度

### $Code$

```cpp
#include<bits/stdc++.h>
#define int long long
#define rg register
#define file(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout);
using namespace std;
int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') f=(c=='-')?-1:1,c=getchar();
	while(c>='0'&&c<='9') x=x*10+c-48,c=getchar();
	return f*x;
}
const int N=5e5+10;
stack<int> s;
int a[N];
main(){
	int n=read(),ans=0,x,y,tot=0;
	for(int i=1;i<=n;i++){
		a[i]=read();
		while(s.size()>=2){
			x=s.top(),s.pop(),y=s.top();
			if(y>=x&&x<=a[i]) ans+=min(a[i],y);
			else {s.push(x);break;}
		}
		s.push(a[i]);
	}
	while(!s.empty())
		a[++tot]=s.top(),s.pop();
	sort(a+1,a+1+tot);
	for(int i=1;i<tot-1;i++)
		ans+=a[i];
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Austin0116 (赞：10)

# 前言

一道挺简单的紫题。

# 分析

有一个显然的贪心方法：若 $a_i \le a_{i-1}$ 且 $a_i \le a_{i+1} $ 就可以将 $a_i$ 删除，并将分数加进答案中。此过程可以用链表实现。剩下的数就可以将其从小到大排序，设剩下的数组长度为 $n$ ，答案加上 $ \displaystyle \sum_ {i = 1}^{n - 2} a_i $ 。

时间复杂度 $O(n \log n)$

# 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[500005],c[500005],cnt,fl=1;
long long sum;
struct ha{//链表
	int pre,nxt,da;
};
ha b[500005];
inline void add(int u,int v){
	b[u].pre=b[v].pre;
	b[v].pre=u;
	b[u].nxt=v;
	b[b[u].pre].nxt=u;
	b[u].da=a[u];
}
inline void del(int u){
	b[b[u].pre].nxt=b[u].nxt;
	b[b[u].nxt].pre=b[u].pre;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		add(i,0);
	} 
	while(fl){//链表模拟
		fl=0;
		for(int i=b[0].nxt;i;i=b[i].nxt) if(b[b[i].pre].da>=b[i].da&&b[b[i].nxt].da>=b[i].da&&b[i].nxt!=b[i].pre){
			sum+=min(b[b[i].pre].da,b[b[i].nxt].da);
			del(i);
			fl=1;
		}
	} 
	for(int i=b[0].nxt;i;i=b[i].nxt) c[++cnt]=b[i].da;
	sort(c+1,c+1+cnt);
	for(int i=1;i<cnt-1;i++) sum+=c[i];
	printf("%lld",sum);
	return 0;
}
```

---

## 作者：Louis_lxy (赞：5)

一个很水的贪心。

显然我们有一个结论：如果有 $a_i\le a_{i-1}$ 且 $a_i\le a_{i+1}$。那么此时一定要删除 $a_i$。因为此时删除 $a_i$ 得到的答案一定大于等于它本身，如果删除它相邻的数只能得到它本身。

然后我们考虑使用链表处理，删除时直接删掉这个节点即可。

注意如果删掉了这个节点，有可能又可以删掉前一个结点了，所以当前的指针要指向前一个结点，对于每次不满足，都指向后一个节点。

剩下的就对除了最大值和次大值求和即可，因为显然不可能删除最大值，因为此时已经没有比他大的两个数了，而次大值显然也无法达到，因为此时最多只有最大值比它大，其他比它大的数已经用贪心处理了。

AC 记录：https://www.luogu.com.cn/record/168240152

---

## 作者：zengxuheng (赞：5)

# 前言
很明显的思维题，思路出来了，代码就很短。

# $Solution$:
## 第一阶段：

从题目中可以发现：
有一个贪心策略，如果 $a_{i-1} \ge a_i \le a_{i+1}$，那么删去 $a_i$ 是最优的（我们称之为 $V$ 字型）。

为什么这个贪心策略是最优的？

从题目中得知，在 $a_{i-1} \ge a_i \le a_{i+1}$ 的 $V$ 字形的情况下删去了 $a_i$，则我们得到的分值为 $min(a_{i-1},a_{i+1})$，大于等于 $a_i$。若不删去 ，则得到的分值最大为 $a_i$。说明在出现 $V$ 字形的情况下删去 $a_i$ 是最优的。

我们开一个栈每进入一个数就判断有没有 $V$ 字形，如果出现了就删掉中间的那个数并记录分数，这就是第一阶段的答案。
```
int top=0;
for(int i = 1;i <= n;i++){
    cin>>x;
    while(top>1&&a[top-1]>=a[top]&&x>=a[top]){
        ans+=min(a[--top],x);
    }
    a[++top]=x;
}
```
## 第二阶段：

当然不太可能整个 $a$ 数组全都是 $V$ 字形，也会有一些没有 $V$ 字形的，或者说加完 $V$ 字形的分之后剩下的数。

例如样例：
```
5
1 100 101 99 1
```
没有一个 $V$ 字形。

不难看出，操作完成后一定会剩下两个数无法继续操作。我们想要使得拿到的数的和最大化，就要想尽量拿到比较大的数。

如果想拿 $a$ 数组中的最大值，我们不难发现没有一种方法能拿到最大值。因为它是最大值而每次加分都是选用两个数中的较小值。

那次大值呢？

我们尝试一下发现其实也是不行的。

假如次大值是 $a_{i-1}$，$a_{i+1}$ 只能大于等于次大值，否则 $min$ 操作无法选中 $a_{i-1}$。而 $a_i$ 又只能小于等于 $a_{i-1}$ 和 $a_{i+1}$ 否则 $a_{i-1}$ 的次大值的位置就保不住了，也就不满足条件。

如果满足了条件又可以发现他成为了 $V$ 字形，会在贪心那部分就清除了，不应出现在这里。

接着把 $a$ 数组除最大值和次大值以外的数求和就是第二阶段的答案了。

又有人要问了：为什么不能选两次一样的数字，非要把 $a$ 数组除最大值和次大值以外的数求和，不能加上几次重复的数值吗？

我们来证明一下。

假设有这样一组没有 $V$ 字形的数据：
```
5
1 2 3 4 5
```
为了加两次重复的我们可以先删除 $3$，加上 $2$ 分，再删除 $4$，加上 $2$ 分，共 $4$ 分。可是它就是最优解吗？不难看出我们可以选择先删除 $4$，加 $3$ 分，再删除 $3$，加 $2$ 分，共 $5$ 分。大家都知道 $5 > 4$，加重复的数值不能获得更多的分反而获得的分更少了，即证。

最后把第一阶段的答案加上第二阶段的答案就是题目要求的答案了。

思路搞清楚了，那么下一步就是~~你们最爱的~~代码了：
```
#include<bits/stdc++.h>
using namespace std;

int n,x,a[5000010];
long long ans;

int main() {
	cin>>n;
	int top=0;
	for(int i = 1;i <= n;i++){
		cin>>x;
		while(top>1&&a[top-1]>=a[top]&&x>=a[top]){
			ans+=min(a[--top],x);
		}
		a[++top]=x;
	}
	sort(a+1,a+top+1);
	for(int i = 1;i <= top-2;i++)ans+=a[i];
	cout<<ans<<'\n';
}
```
**完结撒花**

---

## 作者：封禁用户 (赞：3)

感觉应该是评不到紫的。

一个比较简短的贪心题。我们先尝试发掘一些性质，首先显然两端的数肯定是不会删的（删了就会导致少一个能加的数），然后是一个比较重要的结论：如果一个数小于**等于**他左右两边的数，那么先删他肯定是最优的。把这一类的数删完以后我们就将剩余的 $m$ 个数从小到大排序然后加上前 $m-2$ 个数就是答案。

这个结论手玩一下样例就能猜出来，我们可以感性理解一下：如果我们先删的是这一类数两边的数，那么得到的答案肯定是比先删特殊数的答案要小的。

现在的问题是怎么维护这一类特殊的数，其实并不需要用什么数据结构的。我们把某一个位置的数删了以后珂以把他设成 $-inf$，然后我们设一个 $last[i]$ 记录 $i$ 前面第一个值大于 $0$ 的位置，设当前左中右三个位置分别为 $pos1,pos2,i$，如果当前可以更新那么把 $a[pos2]$ 赋成 $-inf$，然后因为删完 $pos2$ 可能会让原来的 $pos1$ 变成特殊的数，所以我们要循环来不断向前迭代：$last[i]=pos1,pos2=pos1,pos1=last[i]$，如果当前的 $pos2$ 不是特殊的数了就退出。这样子比起我们原来直接暴力一个一个往前找就快多了。

[code](https://codeforces.com/contest/442/submission/231083512)

---

## 作者：Daidly (赞：2)

贪心分析：

尝试画出数列的增减图像，可以发现若有凹陷下去的点，删它最优。

因为对于 $a_{i-1}\ge a_i\leq a_{i+1}$，删去 $a_i$ 所得到的分数一定比 $a_i$ 作为 $\min$ 中元素所得分数不少。

所以每次取这样的 $a_i$ 删去，考虑删去后的影响，只会影响到前后两个。

使用链表维护，每次删去 $a_i$ 后向前便利其前继直至不能满足上述删去条件为止，然后继续向后继遍历。可以发现时间复杂度约为 $O(n)$。

删完这样的 $a_i$ 之后，数列图像呈先递增后递减的形状，也有可能只有递增或递减。

考虑最大值，我们取不到。

考虑次大值，还是取不到。

考虑第三大值，似乎能取到，分析两种情况：

$1\ 2\ 4\ 5\ 3\ 2\ 1$

最大值为 $5$。次大值为 $4$，第三大值为 $3$，分居最大值两侧，考虑删去最大值，即可取到第三大值。

$1\ 3\ 4\ 5\ 2\ 2\ 1$

最大值为 $5$。次大值为 $4$，第三大值为 $3$，在最大值同一侧，考虑删去次大值，即可取到第三大值。

所以，在此先递增后递减的序列中，除了最大和次大值，其他我们都能取到。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}

const int MAXN=5e5+5;
int n,a[MAXN],sum,l[MAXN],r[MAXN]={1},max1,max2;

signed main(){
	n=read();
	for(int i=1;i<=n;++i)a[i]=read(),l[i]=i-1,r[i]=i+1;
	for(int i=r[1];i<=n;i=r[i]){
		if(a[l[i]]>=a[i]&&a[i]<=a[r[i]]){
			sum+=min(a[l[i]],a[r[i]]);
			r[l[i]]=r[i],l[r[i]]=l[i];
			int tmp=l[i];
			while(a[l[tmp]]>=a[tmp]&&a[tmp]<=a[r[tmp]]){
				sum+=min(a[l[tmp]],a[r[tmp]]);
				r[l[tmp]]=r[tmp],l[r[i]]=l[tmp];
				tmp=l[tmp];
			}
		}
	}
	for(int i=r[0];i<=n;i=r[i]){
		if(a[i]>max1){
			max2=max1;max1=a[i];
		}else if(a[i]>max2)max2=a[i];
		sum+=a[i];
	}
	cout<<sum-max1-max2;
	return 0;
}
```

---

## 作者：do_while_true (赞：2)

考虑三个相邻的元素 $x,y,z$ 满足 $y\leq x,z$，则三者先删除 $y$​ 更优。

假设最左侧和最右侧有两个不能删除的 $0$，发现和原问题等价，这样就不需要讨论边界情况了。

考虑反证，不失一般性假设先删除 $x$．对于任意一种先删除 $x$ 的策略，在删除 $x$ 的时候先删除 $y$ 一定不劣：

假设现在序列是 $...,v,x,y,z,...$：

- 如果先删除 $x$，对答案贡献是 $\min(v,y)$，剩余序列为 $...,v,y,z,...$；
- 如果先删除 $y$，对答案贡献是 $\min(x,z)$，剩余序列为 $...,v,x,z,...$．

注意到 $\min(v,y)\leq y\leq \min(x,z)$，以及序列中的数越大答案越大，所以后者相比前者不劣。

然后变成双调的，答案为 $n-2$ 小的数的和。虽然前面编出来证明了，这里的构造还是[w23c3c3](https://www.luogu.com.cn/discuss/369356)教我的/ll

性质：最大值和次大值一定不会对答案做贡献，所以它们具体取值对答案无所谓，存在的意义仅为比其他所有的都大。

充分：给出一种构造，如果第三大值在最大值旁边，则删去最大值，否则第三大值在次大值旁边，删去次大值，递归成子问题。

必要：尝试构造，发现一个数如果对答案贡献 $x$ 次，那么一定有一个比它大的数少贡献 $(x-1)$ 次，所以每个数仅贡献一次最优。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<set>
#define pb emplace_back
#define mp std::make_pair
#define fi first
#define se second
typedef long long ll;
typedef long double ld;
typedef std::pair<int, int> pii;
typedef std::pair<ll, int> pli;
typedef std::pair<ll, ll> pll;
typedef std::vector<int> vi;
typedef std::vector<pii> vpii;
typedef std::vector<ll> vll;
const ll mod = 998244353;
ll Add(ll x, ll y) { return (x+y>=mod) ? (x+y-mod) : (x+y); }
ll Mul(ll x, ll y) { return x * y % mod; }
ll Mod(ll x) { return x < 0 ? (x + mod) : (x >= mod ? (x-mod) : x); }
ll cadd(ll &x, ll y) { return x = (x+y>=mod) ? (x+y-mod) : (x+y); }
template <typename T> T Max(T x, T y) { return x > y ? x : y; }
template <typename T> T Min(T x, T y) { return x < y ? x : y; }
template <typename T>
T &read(T &r) {
	r = 0; bool w = 0; char ch = getchar();
	while(ch < '0' || ch > '9') w = ch == '-' ? 1 : 0, ch = getchar();
	while(ch >= '0' && ch <= '9') r = r * 10 + (ch ^ 48), ch = getchar();
	return r = w ? -r : r;
}
const int N = 500010;
int n, a[N], l[N], r[N], vis[N], b[N], mx, bmx;
ll ans;
std::queue<int>q;
bool check(int x) {
	return x && !vis[x] && a[x] <= a[l[x]] && a[x] <= a[r[x]];
}
signed main() {
	read(n);
	for(int i = 1; i <= n; ++i) read(a[i]), l[i] = i-1, r[i] = i+1; r[n] = 0;
	for(int i = 2; i < n; ++i)
		if(check(i))
			q.push(i), vis[i] = 1;
	while(!q.empty()) {
		int x = q.front(); q.pop();
		ans += Min(a[l[x]], a[r[x]]);
		r[l[x]] = r[x]; l[r[x]] = l[x];
		if(check(l[x])) q.push(l[x]), vis[l[x]] = 1;
		if(check(r[x])) q.push(r[x]), vis[r[x]] = 1;
	}
	for(int i = 1; i <= n; ++i)
		if(!vis[i]) {
			ans += a[i];
			if(a[i] >= mx) bmx = mx, mx = a[i];
			else bmx = Max(bmx, a[i]);
		}
	printf("%lld\n", ans-mx-bmx);
	return 0;
}
```

---

## 作者：tribool4_in (赞：2)

水紫，做法感觉比较自然。（文中下标表示在当前序列中而非原序列中）

首先发现删除边界一定不优。猜一手贪心选取 $\min(a_{i-1},a_{i+1})$ 最大的先删，于是会 WA on test 4，发现这样可能会误删较大的数从而出错。

于是考虑应该删怎样的数字，容易想到全局最小值 $a_p$。如果 $a_p$ 不在边界上，则直接删除它一定优，因为如果不删，$a_p$ 作为全局最小可能会影响到后面的贡献。于是答案加上 $\min(a_{p-1},a_{p+1})$ 并将其删除。如果 $a_p$ 在边界上，则直接删除 $a_p$ 会没有贡献；不妨假设 $a_p$ 为左边界，可以发现也不应删除 $a_{p+1}$，因为此时 $a_p$ 会对后续产生大于 1 次影响，不优。于是想象将 $a_{p+1}$ 作为新的左边界，一直做到只剩 $a_p,a_{p+1},a_r$，此时再删除 $a_{p+1}$，这样 $a_p$ 只会产生一次贡献。于是可以先处理最后这次贡献，实现上相当于删除 $a_p$ 并答案加上 $a_p$。

前驱后继用链表维护，最小值用 `priority_queue` 维护。

代码很短。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 5e5 + 10;
int n, m, a[N], pre[N], nxt[N];
priority_queue<pair<int, int>> t;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n; m = n;
    for (int i = 1; i <= n; i++) cin >> a[i], pre[i] = (i == 1 ? 0 : i - 1), nxt[i] = (i == n ? 0 : i + 1);
    for (int i = 1; i <= n; i++) t.emplace(-a[i], i);
    ll ans = 0;
    for (int i = 1; i <= n - 2; i++) {
        int p = t.top().second;
        t.pop();
        if (pre[p] && nxt[p]) ans += min(a[pre[p]], a[nxt[p]]);
        else ans += a[p];
        nxt[pre[p]] = nxt[p], pre[nxt[p]] = pre[p];
    }
    cout << ans << '\n';
    return 0;
}
```

---

## 作者：lc_lca (赞：2)

对于这种每次操作随机的题目，要考虑一个元素被删除的时候的情况

例如说，一个元素i被删除，那么假设i左边是a，右边是b，ans就+=min(a,b);

而删除的那个数是不会被统计到答案里面的，那么如果这个删除的数很小是不划算的，因为a<=i的时候，删i能获得a的贡献，但是删a能获得i的贡献，显然删a更优秀。

所以对于相邻的三个元素a,i,b,假如i比a，b都小，那么立即删除i，因为你现在不删，删除a的时候还要考虑i的情况，那么要么答案加上i，要么加上比i还小的数值，得不偿失。现在就删除i，加上的是a,b中的最小值，比i要大

在经过这样一遍扫之后，其实整个数列就会是一个单调数列

例如1，2，3，4，5

因为如果不单调，那么就说明会有一个阻碍的

例如1 2 3 2 5

然而这类情况不会出现，因为第一遍扫的时候已经把第二个2删除了

扫完之后，从小到大的前n-2个就是答案，原因说一下

1 2 3 4 5 ←对于这个数列，首先5是不会被统计到的，删除5也是不可能的（删除5只能获得0的贡献，不如删除4还有3的贡献）。删除4获得3的贡献，删除3获得2的贡献，删除2获得1的贡献。

当然题目中要求删除干净，那就删除1，5（反正没贡献）

总结：对于n次操作，每次都在n个元素中随机位置操作的题目，考虑一个元素被操作的时候满足的情况。并且比较连续元素ai,ai+1,ai+2,ai+3,ai+4,ai+5中，ai+2被删除和ai+3被删除什么时候更好

代码不给了

---

## 作者：G1yu (赞：2)

## [CF442C Artem and Array](https://www.luogu.com.cn/problem/CF442C)题解

## 题意

给你一个数组 $a$ 你能删除 $a$ 中任意一元素 $a_i$ 并获得 $\min(a_{i-1},a_{i+1})$ 的分数，问最多拿多少分。

## 思路

我们发现，当 $a_{i-1} \ge a_i \le a_{i+1} $ 时，删去 $a_i$ 才能获得最多分，不然删 $a_{i-1}$ 或 $a_{i+1}$ 都有可能获得小于它们的 $a_i$ 的分数。我们先删去所有满足此性质的数，可以得到一个由一段单调上升与单调下降序列组成的数组，此时不断删除最大值就能一直得到次大值的得分，因为最大值怎么也取不到，故此为最优策略。见图。

![这里是描述图片](https://cdn.luogu.com.cn/upload/image_hosting/3h9tug8a.png)

## 实现

可以先用手写栈来模拟，每读入元素判断它能否与栈顶和栈顶之下的值满足 $a_{i-1} \ge a_i \le a_{i+1} $ 的不等式，这里 $a_i$ 就是栈顶，计算之后将新读入的值加入栈中。在完成后对栈进行排序（这里只能用手写栈了），令栈数组为 $\text{stk}$，那么 $\sum_{i=1}^{n-2} \text{stk}_i$ 的值既是答案。详细过程请见代码。

## AC Code

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N=3e5+5;
int n,stk[N],tt = 0;
ll ans;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	for(int i = 1;i <= n; i++){
		int x;
		cin>>x;
		
		while(tt && stk[tt-1] >=stk[tt]&&stk[tt] <= x){ ans += min(stk[--tt],x);} // 判断
		stk[++tt] = x; //入栈
	}
	sort(stk+1,stk+tt+1); // 排序
	for(int i=1;i<tt-1;i++){
		ans+=stk[i]; 
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Mason123456 (赞：1)

### 思路

思维好题。

---

首先，要怎么选再能利益最大？

那我肯定要让点 $a_i$ 被删了也不可惜，又能获得更多的利益。换句话说，要求 $a_i$ 尽可能小，$a_{i-1},a_{i+1}$ 尽可能大，那就是一个类似于倒 V 型的三元组 $(a_{i-1}, a_i, a_{i+1})$，要求 $a_{i-1} \ge a_i \le a_{i+1}$。

---

于是我就要尽可能多的删除形似 V 的三元组 $(a_{i-1}, a_i, a_{i+1})$。

这里可以用栈处理。

```cpp
for(int i = 1;i <= n;i++){
    cin >> a[i];
    while(tp >= 2 && s[tp-1] >= s[tp] && s[tp] <= a[i]){
        ans += min(s[tp - 1], a[i]);
        tp--;
    }
    s[++tp] = a[i];
}
```

其中，`tp` 表示栈顶下表，`s` 则是手写栈。$s$ 表示 $a$ 的前 $i-1$ 项，没有被删去的值。$s_{tp-1}$ 则表示 $a$ 的前 $i-1$ 项，从右数第二个没被删去的值。那这就好理解了，三元组 $(a_{i-1}, a_i, a_{i+1})$ 变成了 $(s_{tp-1}, s_{tp}, a_i)$。贪心即可。

可是并不是所有的值都是 V 字型的。

---

我们还要处理剩下的值。

我们发现，当我们处理完所有的 V 字型三元组后，任意三元组的大小关系只有三种情况：

1. 三个数单调递增：$a_{i-1} < a_i < a_{i+1}$。
2. 三个数单调递减：$a_{i-1} > a_i > a_{i+1}$。
3. 呈倒 `^` 字型：$a_i < a_i > a_{i+1}$。

也就是说，现在数组被我们搞成**一个**大的 `^` 字，甚至可能完全是严格单调的。

证明：若结果不是一个 `^` 字型：

1. 若出现了多个 `^`，则两个相邻的 `^` 间出现了 V 字型，所以只能有一个 `^`。
2. 若 `^` 的两条“边” 出现了转折点，则也会出现 V 字型，所以“边” 只能单调。

---

要处理 `^` 字，我们看三元组 $a_{i-1} < a_i < a_{i+1}$ 这一部分。其贡献为 $a_{i-1}$。于是我们发现，当在一条单调的序列中，其贡献是唯一确定的。我们只需要每次多选上方的点，这样贡献更高，删去的点还不影响其他贪心操作。

若在一条单调递增的序列中，每次尽量选 $a_i$ 大的数（也就是越靠后的数）进行操作，其贡献就是 $a_{i-1}$，再选择 $a_{i-1}$ 操作，其贡献就是 $a_{i-2}$。以此类推。由于最右边的点不能选（因为没有再右边的点），第 $n-1$ 个点的贡献是 $a_{n-2}$，所以答案就是 $\sum_{i = 1}^{n-2}a_i$。

单调递减同理。

---

来看代码：

```cpp
for(int i = 1;i <= tp - 2; i++){
    ans += s[i];
}
```

emm… 这应该不用解释了。

### Code

需要讲一些细节。

在 `^` 中，注意到若左边的单调递增序列没有选最高点，右边就要选了，这样才有更优解。于是代码中直接将所有的 `^` 中的元素排序，选其前 $\text{tp}-2$ 项即可。这里的 $\text{tp}$ 指 V 型操作后剩下的元素个数。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e5 + 5;
int a[N], s[N], tp = 0;
signed main(){
    int n;
    ll ans = 0;
    cin>>n;
    for(int i = 1;i <= n;i++){
        cin >> a[i];
        while(tp >= 2 && s[tp-1] >= s[tp] && s[tp] <= a[i]){
            ans += min(s[tp - 1], a[i]);
            tp--;
        }
        s[++tp] = a[i];
    }
    sort(s + 1, s + tp + 1);
    for(int i = 1;i <= tp - 2; i++){
        ans += s[i];
    }
    cout<<ans<<"\n";
    return 0;
}
```

---

## 作者：Forg1weN (赞：1)

求得分最大化，就要求每一步删去的时候是否存在其他步优于此步。

在数列长度 $n\ge 2$ 时删去数列首尾显然不优秀，无贡献同时导致其他数无贡献。

简单推理得，一个数与其相邻得两个数得数量关系只有 $4$ 种，将等于归到大于或小于中的一种，然后易得。

显然不优秀的情况为：$a_{i-1}\ge a_i$ 且 $a_i \le a_{i+1}$，理由如下：

若 $a_{i+1}\ge a_{i+2}$，则先删去 $a_{i+1}$ 再删去 $a_i$ 的贡献为 $\min(a_i,a_{i+2})+\min(a_{i+2},a_{i-1})$，而删去 $a_i$ 再删去 $a_{i+1}$ 的贡献为 $\min(a_{i-1},a_{i+1})+\min(a_{i-1},a_{i+2})$，而经过简单枚举可得：$\min(a_i,a_{i+2})\le \min(a_{i-1},a_{i+1})$。

若反之，$a_{i+1}\le a_{i+2}$，则正确性显然。

综上所述，满足如上条件的数时一定可以先删除的。

最后剩下来的数列形状，一定是一段单调上升接一段单调递减，形如一座山峰，但两边的山坡可能有一边消失，这样子的话一定是左右两个最小的数不删，便可得最大值，由上类似可证明。

删除数据的复杂度是 $O(n)$，但是用数据结构要考虑其本身的复杂度，例如快速排序。

---

## 作者：XL4453 (赞：1)



------------
题目分析：

本题可以考虑使用贪心。

首先填“坑”。显然，对于一个左右两边的数都比当前值大的，可以直接将其删掉。否则在删左右两边的数的时候这个值一定不会提供更优解。

将所有的“坑”填完之后，原来的序列就变成了一个单峰序列（注意单调序列只是其中的一种特殊情况）。对于这个序列，最优的第一步删法是将峰顶删掉，这样就是在可能能取的值中最大的和次大的中的去一个较小值，是理论最大值。

然后可以发现，将一个峰顶删除后，序列仍然是一个单峰序列（但可能是不严格的，即峰顶两元素相等），那么重复删除峰顶直到序列删完为止就可以得出答案了。

------------

实现上：

可以用堆来维护比两边都小的数，理论能过但效率不算太高。更优的解法是用栈维护单峰序列，遇到破坏单峰的直接向前弹栈，直到满足单峰。

最后的取值也可以模拟做，然而效率依然不高。更优的解法是将整个栈中的元素排序，直接取前 $n-2$ 个即可。因为按照最优解法一定能将从倒数第二个值开始到第一个值取且仅取一次。



------------
代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
long long min(long long a,long long b){if(a<b)return a;return b;}
int st[500005],top,n,x;
long long ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		while(top>=2){
			if(st[top-1]>=st[top]&&st[top]<=x){
				ans+=min((long long)st[top-1],(long long)x);
				top--;
				continue;
			}
			break;
		}
		top++;
		st[top]=x;
	}
	sort(st+1,st+top+1);
	for(int i=1;i<=top-2;i++)
	ans+=(long long)st[i];
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：S08578 (赞：0)

[题目传送门](http://codeforces.com/problemset/problem/442/C)

## 思路

一道明显的贪心题。

我们不难发现，如果 $a_i \le a_{i-1}$ 并且 $a_i \le a_{i+1}$，那么删去 $a_i$ 是最优的。

若删去 $a_i$，则我们得到的分值为 $\min( a_{i-1},  a_{i+1} )$，比 $a_i$ 大。若不删去 $a_i$，则得到的分值最大为 $a_i$。说明在 $a_i \le a_{i-1}$ 并且 $a_i \le a_{i+1}$ 的情况下，删去 $a_i$ 是最优的。

显然，剩下的序列分为三种情况：单调上升，单调下降或者是倒 V 型。

不难发现，无论如何删，序列的最大值和次大值的分数不可能取到。

若能取到最大值的分数，则必定有两个数比最大值大，不符实际。次大值同理。

所以，我们将答案还要加上 $\sum\limits_{i = 1}^{n-2} a_i$。（$a$ 序列为删完的序列）

我们可以用栈来实现。

## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<stack>
using namespace std;
#define int long long
const int N=5e5+55;
int a[N],vis[N];
int tot,res;
stack<int> st;
signed main(){
    int n;
    cin>>n;
    
    for(int i=1;i<=n;i++){
        int d;
        cin>>d;
        while(st.size()>=2){
            int x=st.top();//栈顶
            st.pop();
            int y=st.top();//栈的第二个
            if(x<=y&&x<=d){//这里是<=而不是<!!!!
                res+=min(y,d);
            }
            else{
                st.push(x);
                break;
            }
        }
        st.push(d);
    }
    while(!st.empty()){
        tot++;
        a[tot]=st.top();
        st.pop();
    }
    sort(a+1,a+tot+1);
    for(int i=1;i<=tot-2;i++) res+=a[i];
    cout<<res<<endl;
    return 0;
}


```

---

## 作者：forest114514 (赞：0)

### CF442C Artem and Array

偏易的紫题

显然的贪心性质：如果存在一个数 $a_i$ 满足 $a_{i-1}\ge a_i\le a_{i+1}$ 优先删 $a_i$。

最后剩下的单峰序列就从峰删，答案是排序后的前 $n-2$ 小值。

至于消去 $a_{i-1}\ge a_i\le a_{i+1}$ 的所有 $a_i$，~~这么单调的东西就用单调栈啊~~。

时间复杂度为 $O(N)$（~~只消去最大和次大值还要排序？~~）

CODE：

```cpp
#include<bits/stdc++.h>
//#pragma GCC optimize("Ofast")
#define re register
#define il inline
#define gc() getchar()
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define repp(i,a,b) for(re int i=a;i<b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
#define tep(i,x) for(re int i=head[x];~i;i=ne[i])
#define ls(x) x<<1
#define rs(x) x<<1|1
#define eps (1e-9)
#define inf 0x3f3f3f3f
#define INF 1e18+100
#define pii pair<int,int>
#define mp(i,j) make_pair(i,j)
#define pb push_back
#define fi first
#define sc second
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
template<typename T> inline void read(T &x){
	bool f=1;x=0;char ch=gc();
	while(ch<'0'||ch>'9'){if(ch=='-')f=0;ch=gc();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch&15),ch=gc();
	x=f?x:-x;
}
template<typename T> inline void write(T x){
	if(x<0) putchar('-'),x=-x;
   	if(x>9) write(x/10);
   	putchar(('0'+x%10));
}
template <typename T,typename ...Args> inline
void read(T &x,Args &...args){read(x);read(args...);}
template<typename T> inline void write(T x,char c){write(x),putchar(c);}
const int N=5e5+100;
int n,a[N],st[N],top;
LL ans;
signed main(){
	//ios::sync_with_stdio(false);
	//cin.tie(0);cout.tie(0);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	read(n);
	rep(i,1,n){
		read(a[i]);
		while(top>=2){
			int x=st[top--];
			if(x<=st[top]&&x<=a[i]) ans+=min(st[top],a[i]);
			else {
				st[++top]=x;break;
			}
		}
		st[++top]=a[i];
	}
	int maxx=0,mp;
	rep(i,1,top) if(st[i]>maxx) mp=i,maxx=st[i];
	st[mp]=0,maxx=0;
	rep(i,1,top) if(st[i]>maxx) mp=i,maxx=st[i];
	st[mp]=0;
	rep(i,1,top) ans+=st[i];
	write(ans,'\n');
	return 0;
}
```



---

