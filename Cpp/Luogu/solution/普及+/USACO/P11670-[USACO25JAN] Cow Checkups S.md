# [USACO25JAN] Cow Checkups S

## 题目描述

Farmer John 的 $N$（$1 \leq N \leq 5 \cdot 10^5$）头奶牛站成一行，奶牛 $1$ 在队伍的最前面，奶牛 $N$ 在队伍的最后面。FJ 的奶牛也有许多不同的品种。他用从 $1$ 到 $N$ 的整数来表示每一品种。队伍从前到后第 $i$ 头奶牛的品种是 $a_i$（$1 \leq a_i \leq N$）。

FJ 正在带他的奶牛们去当地的奶牛医院进行体检。然而，奶牛兽医非常挑剔，仅愿意当队伍中第 $i$ 头奶牛为品种 $b_i$（$1 \leq b_i \leq N$）时对其进行体检。

FJ 很懒惰，不想完全重新排列他的奶牛。他将执行以下操作恰好一次。

- 选择两个整数 $l$ 和 $r$，使得 $1 \leq l \le r \leq N$。反转队伍中第 $l$ 头奶牛到第 $r$ 头奶牛之间的奶牛的顺序。

FJ 想要衡量这种方法有多少效果。求出对于所有 $N(N+1)/2$ 种可能的操作被兽医检查的奶牛数量之和。

## 说明/提示

### 样例解释

#### 样例 #1
如果 FJ 选择 $(l=1,r=1)$，$(l=2,r=2)$ 或 $(l=3,r=3)$，则没有奶牛将会被检查。注意这些操作并没有改变奶牛的位置。

以下操作会导致一头奶牛被检查。

- $(l=1,r=2)$：FJ 反转第一头和第二头奶牛的顺序，因此新队伍中每头奶牛的品种将为 $[3,1,2]$。第一头奶牛将会被检查。
- $(l=2,r=3)$：FJ 反转第二头和第三头奶牛的顺序，因此新队伍中每头奶牛的品种将为 $[1,2,3]$。第二头奶牛将会被检查。
- $(l=1,r=3)$：FJ 反转第一头，第二头和第三头奶牛的顺序，因此新队伍中每头奶牛的品种将为 $[2,3,1]$。第三头奶牛将会被检查。

所有六种操作中被检查的奶牛数量之和为 $0+0+0+1+1+1=3$。

#### 样例 #2

有三种导致 $3$ 头奶牛被检查的可能操作：$(l=1,r=1)$，$(l=2,r=2)$ 和 $(l=3,r=3)$。其余每种操作均导致 $1$ 头奶牛被检查。所有六种操作中被检查的奶牛数量之和为 $3+3+3+1+1+1=12$。

### 子任务
- 测试点 4：$N\le 100$。
- 测试点 5：$N\le 5000$。
- 测试点 6-9：$a_i$，$b_i$ 均在范围 $[1,N]$ 内均匀随机生成。
- 测试点 10-15：$a_i$，$b_i$ 均在范围 $[1,2]$ 内均匀随机生成。
- 测试点 16-23：没有额外限制。

## 样例 #1

### 输入

```
3
1 3 2
3 2 1```

### 输出

```
3```

## 样例 #2

### 输入

```
3
1 2 3
1 2 3```

### 输出

```
12```

## 样例 #3

### 输入

```
7
1 3 2 2 1 3 2
3 2 2 1 2 3 1```

### 输出

```
60```

# 题解

## 作者：chenxi2009 (赞：15)

本文含有二创成分。
> 我和乐土仙尊乃是至交好友！

你是蛊修世界中的一名蛊师，以传播大爱为己任。\
今天你收到**至交好友**乐土的传信，信中称他遭具羊、星宿两名魔头的围攻，恳求你速速送来一件关键蛊材助他脱困。

事实浮冰的形成十分繁琐，这需要你洞悉一种律道蛊方的所有变式。具体而言，这道蛊方由上、下两卷组成，每一卷均由 $n$ 个凡蛊组成，上卷的凡蛊从左向右为 $a_1,a_2,\cdots,a_n$，下卷对应的蛊虫为 $b_1,b_2,\cdots,b_n$。蛊方的契合度为 $a_i=b_i$ 的位置 $i$ 的个数。

形成蛊方的变式需要你恰好做一次如下操作：选择两个正整数 $l,r$，将 $a_{l\cdots r}$ 翻转。\
由于事实往往不是完美的，你只需要知道所有 $\frac{n(n+1)}{2}$ 种变式的契合度之和，而不需要给出具体每一种方案的契合度。

**附加任务**

**事态紧急，若是有线性复杂度的方案就再好不过了。**
## 思路
考虑统计每一对 $a_x=b_y$ 配对起来做出贡献的方案数。

**$a_x$ 与 $b_x$ 配对**

有两种情况可以使原本处在相同位置的两个蛊配对：它们不处在翻转范围内（$r<x$ 或 $x<l$），或它们是翻转操作的中心（$x=\frac{l+r}{2}$）。\
前者分开计算翻转区间在 $x$ 左边和右边的的方案数，具体为：
$$
\frac{x(x-1)}{2}+\frac{(n-x)(n-x+1)}{2}=\frac{x(x-1)+(n-x)(n-x+1)}{2}
$$
后者计算以 $x$ 为中心的方案数即可，简单统计发现数量为 $\min(x,n-x+1)$。

**$a_x$ 与 $b_y$（$x\ne y$）配对**

$a_x$ 与 $b_y$ 配对当且仅当 $a_x$ 被翻转到了 $a_y$ 的位置，我们不妨钦定 $x<y$。显然要做到这一点操作必须是 $(x-m,y+m)$（$m$ 为自然数）的形式，根据边界 $x-m\ge1,y+m\le n$ 可得这样的方案有 $\min(x,n-y+1)$ 种。

考虑拆掉这个 $\min$，统计每一个 $x$ 或 $n-y+1$ 作为较小值被取了多少次。

可以发现 $x$ 作为较小值，代表的就是 **$x$ 与序列左端的距离比 $y$ 离序列的右端的距离短**，做出贡献的次数就是比 $x$ **更靠近中央**的 $y$ 使 $a_x=b_y$ 的数量。$n-y+1$ 的贡献同理。

当然 $a_y=b_x$ 也要统计。

整体来看，做法就是从中央向两边扩展，统计 $a$、$b$ 数组中已经被扩展部分中每个值的出现次数，每次加入一个 $a_x$、$b_x$，它做出贡献的次数就是在它之前另一个数组内相同的值出现的次数，每次做出贡献的量为 $\min(x,n-x+1)$。

可以参考代码理解，时间复杂度 $O(n)$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[600000],b[600000],cnta[600000],cntb[600000],l,r;
long long ans;
int main(){
    scanf("%d",&n);
    for(int i = 1;i <= n;i ++) scanf("%d",&a[i]);
    for(int i = 1;i <= n;i ++) scanf("%d",&b[i]);
    l = n / 2 + 1,r = n / 2;//从中央开始扩展
    for(int i = 1;i <= n;i ++) if(a[i] == b[i]) ans += min(i,n - i + 1) + (1ll * i * (i - 1) + 1ll * (n - i) * (n - i + 1)) / 2;//a_i = b_i 做出的贡献
    for(int i = 1;i <= (n + 1) / 2;i ++){//每次扩展往左往右都分别扩展一个长度
        if(++ r > n) break;//防越界
        ans += 1ll * (cntb[a[r]] + cnta[b[r]]) * (n - r + 1);//a_r 和 b_r 做出的贡献
        cnta[a[r]] ++,cntb[b[r]] ++;//统计 a_r 和 b_r 出现的次数
        if(-- l <= 0) break;
        ans += 1ll * (cntb[a[l]] + cnta[b[l]]) * l;//向左扩展，同理
        cnta[a[l]] ++,cntb[b[l]] ++;
    }
    printf("%lld",ans);
    return 0;
}
```
## 后记
在最关键的时刻，你终于来到了乐土身边，扭转了战局。

乐土抓住你的手臂做出/bx 的表情，双眼瞪大，感动地说不出话来。

又是传播大爱的一天呢。

---

## 作者：蒋淋雨 (赞：5)

# P11670 [USACO25JAN] Cow Checkups S
首先感谢[@EnofTaiPeople](https://www.luogu.com.cn/user/502410)，
看他的[b站实况](https://space.bilibili.com/3546700731910221?spm_id_from=333.1387.follow.user_card.click)学习到的。(~~感觉是题解区最通俗易懂的了~~)

## 一种不用二分的思路
首先是很常规的 $a_i=b_i$ 的情况：

其他题解说过了，就是这个点不动，它左右两边转换的次数就是他左边能转换的次数加右边能转换的次数。

**接下来是重点**

我们输入数据，预处理的时候开一个桶，存该值的位置和 $a/b$ 信息。
``` cpp
   rep(i,1,n)cin>>a[i],e[a[i]].eb(min(i,n-i+1),0);
    rep(i,1,n){
        cin>>b[i],e[b[i]].eb(min(i,n-i+1),1);
        if(a[i]==b[i]){
            ans+=i*(i-1)/2+(n-i)*(n-i+1)/2;
        }
    }//别急 下面有解释
```
**什么是最大转换次数呢？**

比如说 $n$ 是无限大，那么我们 $b$ 位于 $3$ 的位置想要有贡献的话，肯定是前面或者后面能和它匹配的转过来才行，设这个点为 $x$，显然有反转 $(3,x),(2,x+1),(1,x+2)$ $\dots$

那我们要枚举 $n$ 个位置吗？上面代码写了 $(3,x)$ 和 $(x,3)$ 显然是同一组，因此我们只需要用当前位置的和它之前有的去匹配就行。

**这里可能有两个疑问，”之前”，“匹配”**

**之前**：转换位置后的。

拿长度为 $7$ 举例，假设 $a[6]=b[3]$ ，按照转换，$a$ 这个点位置是 $1$ ，$b$ 是 $3$ ，$b$ 才是前面。

**匹配** 不要轴脑筋，我们转换后，不局限于转换 $a$ 然后去找 $b$ 了，**是当前位置的 $a$ 找之前的 $b$ 匹配，当前位置的 $b$ 找之前的 $a$ 匹配。**
``` cpp
        tot[0]=tot[1]=0;
        sort(all(e[i]));
        for(auto it:e[i]){
            ans+=tot[it.se^1];
            tot[it.se]+=it.fi;
        }
```
## 完整代码


```cpp
#define pii pair<int,int>
vector<pii>e[500005];
int n,a[500005],b[500005],tot[2];
void solve() {
    cin>>n;
    int ans=0;
    rep(i,1,n)cin>>a[i],e[a[i]].eb(min(i,n-i+1),0);
    rep(i,1,n){
        cin>>b[i],e[b[i]].eb(min(i,n-i+1),1);
        if(a[i]==b[i]){
            ans+=i*(i-1)/2+(n-i)*(n-i+1)/2;
        }
    }
    rep(i,1,n){
        tot[0]=tot[1]=0;
        sort(all(e[i]));
        for(auto it:e[i]){
            ans+=tot[it.se^1];
            tot[it.se]+=it.fi;
        }
    }
    cout<<ans;
}
```

---

## 作者：Mr_RedStone (赞：5)

## 思路

首先想到暴力，$O(n^3)$。

然后考虑优化成 $O(n^2)$ ~~虽然并不会多给你几分（悲)~~。

接下来都借助这个样例。

输入：
```
7
1 3 2 2 1 3 2
3 2 2 1 2 3 1
```
输出：
```
60
```

枚举每次翻转的区间 $l,r$，先固定 $l=1$，枚举 $r$ 然后作比较，得到如下结果（只关注被翻转区间）：

```
a=   1 3 2 2 1 3 2
b=   3 2 2 1 2 3 1
r=1: 1 
r=2: 3 1
r=3: 2 3 1
r=4: 2 2 3 1
r=5: 1 2 2 3 1
r=6: 3 1 2 2 3 1
r=7: 2 3 1 2 2 3 1
l=1
```

不难发现 $a_1$ 在区间 $[1,7]$ 计算贡献，$a_2$ 在 $[1,6]$ 中计算贡献，$a_3$ 在 $[1,5]$ 中计算贡献，其余同理。

我们再固定 $l=2$，枚举 $r$，观察规律：

```
a=   1 3 2 2 1 3 2
b=   3 2 2 1 2 3 1
r=2:   3 
r=3:   2 3 
r=4:   2 2 3 
r=5:   1 2 2 3 
r=6:   3 1 2 2 3 
r=7:   2 3 1 2 2 3
l=2
```

发现此时 $a_1$ 不再做贡献，$a_2$ 在区间 $[2,7]$，$a_3$ 在区间 $[2,6]$，其余同理。

令 $f_{i,j}$ 表示 $a_i$ 在 $b_1 - b_j$ 中出现过的次数（类似前缀和）。

$l=1$ 时，所有被翻转区间的贡献和就是：

$$S_1=(f_{1,n}-f_{1,0})+(f_{2,n-1}-f_{2,0})+(f_{3,n-2}-f_{3,0})+\cdots+(f_{n,1}-f_{n,0})$$

$l=2$ 时：

$$S_2=(f_{2,n}-f_{2,1})+(f_{3,n-1}-f_{3,1})+\cdots+(f_{n-1,3}-f_{n-1,1})+(f_{n,2}-f_{n,1})$$

发现规律：

$$S_l=\sum_{j=l}^{n}f_{j,n-j+l}-f_{j,l-1}$$

预处理出 $f,S$ 就可以 $O(n^2)$ 计算答案了。

## 正解

挨个匹配的思路无法继续优化。

思考能发现一个重要的结论：**只需要枚举每一个 $a_i$，计算它对于答案的贡献即可。**

从 $O(n^2)$ 的推导中也能看出答案跟 $a_i$ 在 $b$ 中的出现次数有关。

注意到当 $a_i = b_i$ 时，若翻转区间包含 $i$，则翻转**以 $i$ 为中心**时都能产生 $1$ 的贡献。若翻转区间不包含 $i$，则 $i$ **必定产生贡献**，会产生 $\frac{i(i-1)}{2}+\frac{(n-i)(n-i+1)}{2}$ 的贡献，**即在 $i$ 左侧的可翻转区间数和 $i$ 右侧的可翻转区间数。**

当 $a_i \neq b_i$ 时，令 $c_{a_i}$ 表示 $a_i$ 在 $b$ 中出现次数。一开始容易想到此时 $a_i$ 的贡献就是 $c_{a_i}$，然后就听取蛙声一片。对于下面这个例子：

```
a=1 1 3 1 1 1 1
b=1 1 1 3 1 1 1
```

求 $a_3$ 也就是 $3$ 对于答案的贡献，发现在翻转 $[3,4],[2,5],[1,6]$ 这三个区间时其都会产生贡献。

**正确的处理应该是**：对于 $i$ 和 $a_i$ 在 $b$ 中出现的所有位置 $j$，会产生 $\min\{n-i+1,i,n-j+1,j\}$ 
次值为 $1$ 的贡献（翻转区间左边最多到 $1$，右边最多到 $n$）。

设一个 $f_x$，对于所有满足 $b_j=x$ 对应的 $j$，将 $\min\{n-j+1,j\}$ 按从小到大的顺序存在 $f_x$ 中。

再对这个 $f_x$ 维护一个前缀和 $s_x$。

对于每一个 $a_i$，计算 $x=\min\{n-i+1,i\}$。找出 $f_{a_i}$ 中第一个小于等于 $x$ 的值的位置 $p$，此时令答案加上 $s_{x,p}+x(c_{a_i}-p)$ 即可。

其中 $s_{x,p}$ 包含了所有小于和一个等于 $x$ 的贡献值和，而剩下 $c_{a_i}-p$ 个值都大于等于 $x$，取 $\min$ 一定产生 $x$ 的贡献，所以直接用 $x(c_{a_i}-p)$ 即可。

这部分如果难以理解可以看代码，代码非常好理解。

最终得到 $O(n \log n)$ 的解法。

## 代码

$O(n^3) \& O(n^2)$：[Code~](https://www.luogu.com.cn/paste/cyphhgqn)。

$AC$：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[500005],b[500005];
int c[500005];
vector<int> f[500005];
vector<long long> s[500005];//这里由于n太大，前缀和s需要开vector防止爆空间
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&b[i]);
		c[b[i]]++;//统计每个数字出现的次数
		if(s[b[i]].empty()) s[b[i]].push_back(0);
	}
	for(int i=1;i<=n;i++){
		//这样插入是为了保证f中的有序性
		f[b[i]].push_back(i);
		s[b[i]].push_back(s[b[i]].back()+i);
		if(n-i+1<=i) break;
		f[b[n-i+1]].push_back(i);
		s[b[n-i+1]].push_back(s[b[n-i+1]].back()+i);
	}
	long long ans=0;
	for(int i=1;i<=n;i++){
		if(c[a[i]]==0) continue;//要特判不然下面要RTE
		if(a[i]==b[i]){//统计a[i]==b[i]的情况
			ans+=1ll*i*(i-1)/2+1ll*(n-i)*(n-i+1)/2;
		}
		//a[i]==b[i]时也需要统计其他位置上与a[i]相同的b[i]所能产生的贡献
		int x=min(n-i+1,i);
		int p=lower_bound(f[a[i]].begin(),f[a[i]].end(),x)-f[a[i]].begin();
		ans+=s[a[i]][p];
		ans+=1ll*x*(c[a[i]]-p);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：littlebug (赞：4)

## Solution

考虑每对 $a_i = b_j$，能形成的贡献为 $\min(i,n-j+1)$，即正好这两个位置的元素交换的方案数，拿个 `vector` 统计同一个数出现的位置就可以统计了。还要考虑本来就 $a_i = b_i$ 的元素对的贡献，这也是容易的，考虑 $i$ 左边或右边随便打乱即可。

但是这是 $O(n^2)$ 的，在 $a,b$ 中出现大量同一元素时会 T 飞。

设 $A$ 为 $a$ 中某个元素的出现位置集合，$B$ 同理，那么如果设 $x \le y$，则贡献可以表示为：

$$
\sum _{x \in A} \sum _{y \in B} \min(x,n-y+1)
$$

然后发现 $x$ 可以枚举，于是这个 $\min$ 可以拆开！把 $n-y+1$ 全都算出来，排序，二分找一个分界点，一边的贡献是 $n-y+1$（拿前缀和预处理一下），另一边的贡献是 $i$，于是就得到了 $O(n \log n)$ 做法！

对于 $x > y$，可以先把 $A,B$ 交换，同样的方法算出 $y \le x$ 的贡献，最后减去 $x=y$ 的贡献即可。

## Code

```cpp
int n,aa[MAXN],bb[MAXN],v[MAXN],s[MAXN];
vector <int> a[MAXN],b[MAXN];

signed main()
{
    read(n),_::r(aa,n),_::r(bb,n);
    rep(i,1,n) a[aa[i]].pb(i),b[bb[i]].pb(i);
    rep(i,1,n) sort(all(a[i])),sort(all(b[i]));

    int ans=0;

    auto calc=[](int n){return n*(n+1)/2;};
    rep(i,1,n) aa[i]==bb[i] && (ans+=calc(i-1)+calc(n-i)-min(i,n-i+1));

    int sz,tmp,now,ctl;
    rep(i,1,n)
    {
    	// x<y
    	
        sz=0;
        for(auto y:b[i]) v[++sz]=n-y+1;
        reverse(v+1,v+sz+1);
        rep(i,1,sz) s[i]=s[i-1]+v[i];
        
        for(auto x:a[i])
        {
        	ctl=b[i].size()-(lower_bound(all(b[i]),x)-b[i].begin()); // y>=x 的 y 的个数
            tmp=lower_bound(v+1,v+ctl+1,x)-v-1; // n-y+1 中 <=x 的个数，这一部分将 n-y+1 计入答案
            
            now=0;
            now+=s[tmp];
            now+=(ctl-tmp)*x; // n-y+1>x，将 x 计入答案
            
            ans+=now;
        }
        
        // y<x
        
        sz=0;
        for(auto y:a[i]) v[++sz]=n-y+1;
        reverse(v+1,v+sz+1);
        rep(i,1,sz) s[i]=s[i-1]+v[i];

        for(auto x:b[i])
        {
        	ctl=a[i].size()-(lower_bound(all(a[i]),x)-a[i].begin());
            tmp=lower_bound(v+1,v+ctl+1,x)-v-1;
            
            now=0;
            now+=s[tmp];
            now+=(ctl-tmp)*x;
            
            ans+=now;
        }
    }

    write(ans,'\n');

    return 0;
}
```

---

华风夏韵，洛水天依！

---

## 作者：Hughpig (赞：2)

把一个翻转后的区间看成三部分，翻转的区间前面的区间，翻转的区间和翻转的区间后面的区间。

对于翻转的区间前面的区间，假设右端点为 $i$，则翻转的区间的右端点有 $(i+1)\sim n$  共 $n-i$ 种取法。

所以可以预处理出每个开头为 $1$ 长为 $i$ 的区间和 $b$ 的匹配数量，然后根据乘法原理，要乘以 $n-i$。

对于翻转的区间后面的区间同理可以算贡献。

然后是翻转的区间，这个东西乍一看好像不好计算。

考虑对于 $a_i$，它能造成贡献当且仅当它被翻转到了一个位置 $j$，满足 $a_i=b_j$。

假设我们固定了位置 $i$ 被翻转到 $j$，不妨设 $i<j$，满足条件的区间有 $[i,j],[i-1,j+1],[i-2,j+2]\dots[i-x,j+x]\ (x<i,j+x\le n)$。

所以合法区间共有 $\min(i-1,n-j)+1$ 个。$i>j$ 是同理的。

直接把所有值为 $a_i$ 的数提前存下来然后对于每个 $a_i$ 扫一遍的时间复杂度是 $\mathcal{O}(n^2)$，可以过 $9$ 个点。

考虑优化，发现 $i>j$ 和 $i<j$ 的情况可以合并，把 $\min(i-1,n-j)$ 这个式子改写成 $\min(\min(i-1,n-i),\min(j-1,n-j))$。

显然对于相同的 $i$，$\min(i-1,n-i)$ 是相同的。对于相同的 $j$， $\min(j-1,n-j)$ 存起来。 是相同的。

为了快速计算，我们对于所有值为 $a_i$ 的 $b_j$，预处理出 $\min(j-1,n-j)$ 存起来。

对于某个 $\min(i-1,n-i)$ 和对应的 $a_i=b_j$ 计算贡献：根据 $\min$ 的定义，如果 $\min(i-1,n-i)<\min(j-1,n-j)$，贡献为 $\min(i-1,n-i)$，否则为 $\min(j-1,n-j)$。

$\min(j-1,n-j)$ 都预处理存好了，所以可以用 $\min(i-1,n-i)$ 在这些里面二分，计算出有多少个 $\min(i-1,n-i)<\min(j-1,n-j)$，记为 $cnt$，有 $cnt\times \min(i-1,n-i)$ 的贡献。

剩余的则是那些 $\min(j-1,n-j)<=\min(i-1,n-i)$ 的 $\min(j-1,n-j)$ 加起来的贡献，预处理时候带上 $\min(j-1,n-j)$ 前缀和即可。

时间复杂度 $\mathcal{O}(n\log n)$，可以通过。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define up(l,r,i) for(ll i=(l);(i)<=(r);++i)
#define pb emplace_back

constexpr int N=5e5+5;

ll n,a[N],b[N],s[N],ans;
vector<ll> pos[N];

map<ll,bool> vis;
vector<ll> v[N],sum[N];

int main()
{
    cin>>n;
    up(1,n,i)cin>>a[i];
    up(1,n,i)cin>>b[i],pos[b[i]].pb(i);
    up(1,n,i)s[i]=s[i-1]+(a[i]==b[i]);
    up(1,n,i)ans+=s[i]*(n-i);
    for(int i=n;i;--i)ans+=(s[n]-s[i-1])*(i-1);
    up(1,n,i){
    	if(pos[a[i]].size()==0)continue;
    	if(vis[a[i]]){
    		int p=lower_bound(v[a[i]].begin(),v[a[i]].end(),min(i-1,n-i))-v[a[i]].begin();
    		if(p)ans+=sum[a[i]][p-1];
    		ans+=(v[a[i]].size()-p)*min(i-1,n-i);
    		ans+=v[a[i]].size();
    		continue;
		}
		vis[a[i]]=1;
    	for(auto j:pos[a[i]]){
    		ans+=min(min(i-1,n-i),min(j-1,n-j))+1;
    		v[a[i]].pb(min(j-1,n-j));
		}
		sort(v[a[i]].begin(),v[a[i]].end());
		sum[a[i]].resize(v[a[i]].size());
		if(v[a[i]].size()){
			sum[a[i]][0]=v[a[i]][0];
			up(1,v[a[i]].size()-1,j)sum[a[i]][j]=sum[a[i]][j-1]+v[a[i]][j];
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：xiaoshumiao (赞：2)

考虑每个 $A_i$ 的贡献，即 $l,r$ 取什么值他会加到答案上。首先找到所有 $B_j=A_i$ 的 $j$。容易发现此时 $l=i$，$r=j$（设 $i \le j$）即可产生贡献。而 $l$ 减一，$r$ 加一仍然可以在反转后使得 $a_i=b_i$，减二亦然，以此类推，一对 $(i,j)$ 的贡献为 $\min(\min(i,j),n-\max(i,j)+1)$。

特别的，当 $a_i=b_i$ 时有额外贡献。此时只要 $r < i$ 或 $l > i$ 反转后的 $a_i$ 不变。因此会有额外贡献 $\dfrac{(i-1)i}{2}+\dfrac{(n-i)(n-i+1)}{2}$。

直接做复杂度是 $O(N^2)$ 的，瓶颈在于找满足 $A_i=B_j$ 的 $j$。

考虑对原式 $\min(\min(i,j),n-\max(i,j)+1)$ 进行化简。

- 对于 $1 \le j \le \min(i,n-i+1)$，原式 $=j$。

- 若 $n-i+1 \le i$，则对于 $n-i+1 < j \le i$，原式 $=n-i+1$。

- 若 $n-i+1 > i$，则对于 $i< j \le n-i+1$，原式 $=i$。
   
- 对于 $\max(i,n-i+1) < j \le n$，原式 $=n-j+1$。

因此我们开 $3N$ 个 vector，分别维护等于 $i$ 的所有 $b$ 的下标，及下标的两个前缀和（$\sum i$ 和 $\sum n-i+1$）。计算答案时，二分求出每一段在 vector 里的位置，再用前缀和统计即可。时间复杂度 $O(N \log N)$。

具体实现见代码：
```cpp
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int N=5e5+10; int a[N],b[N]; vector<int>v[N]; vector<long long>sumv[N],sum2v[N];
int main() {
	ios::sync_with_stdio(false),cin.tie(nullptr);
	int n; long long sum=0; cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],v[i].push_back(0),sumv[i].push_back(0),sum2v[i].push_back(0);
	for(int i=1;i<=n;i++) {
		cin>>b[i],v[b[i]].push_back(i);
		sumv[b[i]].push_back(sumv[b[i]][sumv[b[i]].size()-1]+i);
		sum2v[b[i]].push_back(sum2v[b[i]][sum2v[b[i]].size()-1]+n-i+1);
	}
	for(int i=1;i<=n;i++) {
		if(a[i]==b[i]) sum+=1ll*(i-1)*i/2+1ll*(n-i)*(n-i+1)/2;//特殊情况
		//for(auto j:v[a[i]]) sum+=min(min(i,j),n-max(i,j)+1);
		int k=upper_bound(v[a[i]].begin(),v[a[i]].end(),min(i,n-i+1))-v[a[i]].begin()-1; sum+=sumv[a[i]][k];
		if(n-i+1<=i) {
			int k1=upper_bound(v[a[i]].begin(),v[a[i]].end(),i)-v[a[i]].begin()-1;
			int k2=upper_bound(v[a[i]].begin(),v[a[i]].end(),n-i+1)-v[a[i]].begin();
			sum+=1ll*(k1-k2+1)*(n-i+1);
			k1=upper_bound(v[a[i]].begin(),v[a[i]].end(),i)-v[a[i]].begin();
			sum+=sum2v[a[i]][sum2v[a[i]].size()-1]-sum2v[a[i]][k1-1];
		}
		else {
			//cout<<sum<<'\n';
			int k1=upper_bound(v[a[i]].begin(),v[a[i]].end(),n-i+1)-v[a[i]].begin()-1;
			int k2=upper_bound(v[a[i]].begin(),v[a[i]].end(),i)-v[a[i]].begin();
			sum+=1ll*(k1-k2+1)*i;
			k1=upper_bound(v[a[i]].begin(),v[a[i]].end(),n-i+1)-v[a[i]].begin();
			sum+=sum2v[a[i]][sum2v[a[i]].size()-1]-sum2v[a[i]][k1-1];
			//cout<<sum<<'\n';
		}
		//cout<<i<<' '<<sum<<'\n';
	}
	cout<<sum;
	return 0;
}
```

---

## 作者：OIer_Hhy (赞：1)

这题显然不能暴力模拟，我们要算每一位的贡献。

由题意得，我们只需要计算翻转后 $a_i=b_i$ 的个数即可。

我们把每一个 $i$ 按 $a_i$ 存进桶中。

然后枚举每一个 $b_i$，把桶中 $b_i$ 所对应的 $S_1,S_2,\cdots,S_k$（$S_i$ 满足 $a_{S_i}=b_i$）拿出来计算贡献。

显然，我们至少要翻转 $[\min(i,S_i),\max(i,S_i)]$ 这个区间。我们可以往两边各拓 $k$ 个，变成 $[\min(i,S_i)-k,\max(i,S_i)+k]$，其中 $1 \le \min(i,S_i)-k$ 且 $\max(i,S_i)+k \le n$。

此时 $b_i$ 的贡献就是 $\sum \min(i,S_i,n-i+1,n-S_i+1)$。

当原来 $a_i=b_i$ 时，我们还可以翻转 $[1,i)$ 和 $(i,n]$ 中的任意区间，贡献为 $C_{i-1}^2 \times C_{n-i}^2$。

然而，可以构造出极限数据卡掉这个代码。

当 $a_i=b_i=1(1 \le i \le n)$ 时，直接变 $O(n^2)$。

如何优化呢？

考虑到这个公式：$\sum \min(i,S_i,n-i+1,n-S_i+1)$。我们将它变一下，变成了 $\sum \min(\min(i,n-i+1),\min(S_i,n-S_i+1))$。

我们把 $\min(i,n-i+1)$ 按 $a_i$ 存进桶中。

枚举每个 $b_i$，我们令 $c_i=\min(i,n-i+1)$，对于桶中 $b_i$ 的每个 $T_j=\min(S_i,n-S_i+1)$，分为两种情况：

- $T_j>c_i$，贡献为 $c_i$。
- $T_j \le c_i$，贡献为 $T_j$。

容易发现，我们只要把 $T$ 排序，并计算出前缀和 $pre$ 即可。

令 $|T|=K$，$l$ 是 $T$ 中第一个满足 $T_l > b_i(1 \le l \le K)$ 的下标，最终 $b_i$ 的贡献即是 $\sum_{j=1}^{l-1} T_j + (K-l+1) \times b_i= pre_{l-1}+(K-l+1) \times b_i$。

当原来 $a_i=b_i$ 时，我们还可以翻转 $[1,i)$ 和 $(i,n]$ 中的任意区间，贡献为 $C_{i-1}^2 \times C_{n-i}^2$。

时间复杂度：$O(n \log n)$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
int n,a[N],b[N],c[N];
vector<int> v[N],pre[N];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		v[a[i]].emplace_back(min(n-i+1,i));
	}
	int ans=0;
	for(int i=1;i<=n;i++) cin>>b[i];
	for(int i=1;i<=n;i++)
		sort(v[i].begin(),v[i].end());
	for(int i=1;i<=n;i++){
		int sum=0;
		for(int j=0;j<v[i].size();j++){
			sum+=v[i][j];
			pre[i].emplace_back(sum);
		}
	}
	for(int i=1;i<=n;i++){
		int t=min(i,n-i+1),pos=upper_bound(v[b[i]].begin(),v[b[i]].end(),t)-v[b[i]].begin();
		if(pos) ans+=pre[b[i]][pos-1];
		ans+=(v[b[i]].size()-pos)*t;
	}
	for(int i=1;i<=n;i++){
		if(a[i]==b[i])
			ans+=((i-1)*(i)/2)+((n-i)*(n-i+1)/2);
	}
	cout<<ans<<'\n';
	return 0;
}

```

---

## 作者：zyn_ (赞：0)

## 题目大意

定义 
$$
f(\{x_i\}_{i=1}^n,\{y_i\}_{i=1}^n)=\sum_{i=1}^n[x_i=y_i]
$$

有两个长为 $N$ 的序列 $\{a_i\},\{b_i\}$。定义 $g(l,r)$ 为 $\{a_i\}$ 的第 $l$ 至 $r$ 项被反转后的序列。求

$$
\sum_{1\le l\le r\le n}f(g(l,r),\{b_i\})
$$

## 计算贡献

对每个 $l,r$ 算 $f(g(l,r),\{b_i\})$ 不太可能。考虑对**每一对 $a_i=b_j$** 计算有多少对 $(l,r)$ 使 $\{a_i\}$ 的第 $l$ 至 $r$ 项被反转后 $a_i,b_j$ 在同一个位置。每对 $(l,r)$ 将对答案产生 $1$ 的贡献。

### 情况 $1$

如果 $i\neq j$ 那么反转区间一定包含 $i$。具体地，反转区间为 $[i-c,j+c]$（$i\lt j$）或 $[j-c,i+c]$（$i\gt j$），其中 $c$ 为自然数。无论如何需满足
$$
i-c\ge 1,j+c\le n,j-c\ge 1,i+c\le n
$$
也即
$$
c\le i-1, c\le n-j,c\le j-1,c\le n-i
$$
又 $c\ge 0$，故可能的反转区间有 $1+\min\{i-1,j-1,n-i,n-j\}$ 个。

### 情况 $2$

如果 $i=j$ 那么除以上的情况，还有可能反转区间不包含 $i$，这样的区间有
$$
\binom{i}{2}+\binom{n-i+1}{2}
$$
个。

## 计算答案

情况 $2$ 至多有 $O(N)$ 种，然而情况 $1$ 可能达到 $O(N^2)$ 种。不妨假设值域为 $[1,N]$，考虑枚举 $c=1,2,\dots,N$，设序列 $\{a_i\},\{b_i\}$ 中所有等于 $c$ 的数为

$$
a_{i_1}=a_{i_2}=\dots=a_{i_s}=b_{j_1}=b_{j_2}=\dots=b_{j_t}=c
$$

枚举 $b_{j_k}$，计算它对所有 $a_{i_l}$ 的答案之和。这里没什么好方法，只能把前面式子中的 $\min$ 拆开大力分讨了。

实现时要注意不能对每个 $c$ 以 $O(N)$ 的时间计算，要做到 $O((s+t)\operatorname{polylog}(s+t))$。以下是一个 $\log$ 的实现。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 500009
#define ll long long
int n,a[N],b[N];
vector<int> f[N],g[N];
ll ans,u,v,l,r;
struct BIT{
	ll x[N];
	void upd(int p,int d){for(;p<=n;p+=p&-p)x[p]+=d;}
	ll qr(int p){ll r=0;for(;p;p-=p&-p)r+=x[p];return r;}
	ll qr(int l,int r){return l>r?0:qr(r)-qr(l-1);}
}p,q,s,t;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d",&a[i]),f[a[i]].push_back(i);
	for(int i=1;i<=n;++i)scanf("%d",&b[i]),g[b[i]].push_back(i);
	for(int i=1;i<=n;++i){
		for(int j:g[i])p.upd(j,j),q.upd(j,1),s.upd(j,1),t.upd(j,n-j+1);
		for(int j:f[i]){
			l=1,r=min(n-j,j);ans+=p.qr(l,r);
			l=j+1,r=n-j;ans+=q.qr(l,r)*j;
			l=n-j+1,r=j;ans+=s.qr(l,r)*(n-j+1);
			l=max(n-j+1,j+1),r=n;ans+=t.qr(l,r);
		}
		for(int j:g[i])p.upd(j,-j),q.upd(j,-1),s.upd(j,-1),t.upd(j,-n+j-1);
	}
	for(ll i=1;i<=n;++i)if(a[i]==b[i])ans+=((i-1)*i+(n-i)*(n-i+1))>>1;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Roy_2010 (赞：0)

# [USACO25JAN] Cow Checkups S 题解
## 分析
首先，我们发现这一题要求一个 $O(n\log n)$ 左右的做法，不足以支撑我们枚举所有的可能操作，而很明显答案是可以拆分的，故采用拆贡献的做法。\
然后，我们思考什么样的位置会产生贡献。
- 如果原来这个位置就可以被检查，那么所有不包含该位置的操作区间都会提供一个额外贡献。设该位置为第 $p$ 个，那么所有的额外贡献之和为 $\frac{N\times (N+1)} {2}-p\times(N-p+1)$。
- 如果这个位置是一个普通位置，那么只有包含该位置的操作才能使其产生贡献，自然我们要选取一个对应值相等的位置进行旋转才能产生贡献，即一些中轴相同的操作区间可以产生贡献。设该位置为第 $p$ 个，那么所有的普通贡献之和为 $\sum\limits_{b_i=a_p}\min(\min(i,p),N-\max(i,p)+1)$。
## 代码（无法通过）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int n;
int a[500050],b[500050];
vector<int> t1[500050],t2[500050];
int ans=0;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		t1[a[i]].push_back(i);
	}
	for(int i=1;i<=n;++i){
		cin>>b[i];
		t2[b[i]].push_back(i);
	}
	for(int i=1;i<=n;++i){
		if(a[i]==b[i]){
			ans+=(n*(n+1)/2-i*(n-i+1));
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=0;j<t1[i].size();++j){
			for(int k=0;k<t2[i].size();++k){
				ans+=min(min(t1[i][j],t2[i][k]),n-max(t1[i][j],t2[i][k])+1);
			}
		}
	}
	cout<<ans<<'\n';
	return 0;
} 
```
## 深度分析
我们发现上述代码超时了，得分很可怜。~~这也是我的考场得分。~~\
究其原因我们发现如果题目给出的两个数组中出现了大量重复，那么就会使得三层循环中的内部两层达到 $O(n^2)$ 的复杂度，明显无法接受。
## 优化
我们不难发现上述代码中的每个动态数组中的元素都是递增的，基于这个，我们可以写出一个较小优化。
```cpp
for(int i=1;i<=n;++i){
	for(int j=0;j<t1[i].size();++j){
		int s=lower_bound(t2[i].begin(),t2[i].end(),t1[i][j])-t2[i].begin();
		for(int k=0;k<s;++k){
			ans+=min(t2[i][k],n-t1[i][j]+1);
		} 
		for(int k=s;k<t2[i].size();++k){
			ans+=min(t1[i][j],n-t2[i][k]+1);
		}
	}
}
```
依旧是 $O(n^2)$ 代码，但速度有所提升，而且式子更加简单。\
此时我们可以发现，最内层两个循环中用来比较的元素，依旧具有单调性，于是再次写出代码。

```cpp
for(int i=1;i<=n;++i){
	for(int j=0;j<t1[i].size();++j){
		int s=lower_bound(t2[i].begin(),t2[i].end(),t1[i][j])-t2[i].begin();
		int s1=lower_bound(t2[i].begin(),t2[i].begin()+s,n-t1[i][j]+1)-t2[i].begin();
		int s2=lower_bound(t2[i].begin()+s,t2[i].end(),n+1-t1[i][j])-t2[i].begin();
		for(int k=0;k<s1;++k){
			ans+=t2[i][k];
		} 
		for(int k=s1;k<s;++k){
			ans+=n-t1[i][j]+1;
		}
		for(int k=s;k<s2;++k){
			ans+=t1[i][j];
		}
		for(int k=s2;k<t2[i].size();++k){
			ans+=n-t2[i][k]+1;
		}
	}
}
```
我们现在的优化思路就很清晰了，最内层四个循环就非常简单了。第一个和第四个用前缀和优化，中间两个直接加法变乘法。
## 代码（可以通过）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int n;
int a[500050],b[500050];
vector<int> t1[500050],t2[500050],sum1[500050],sum2[500050];
int ans=0;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		t1[a[i]].push_back(i);
	}
	for(int i=1;i<=n;++i){
		cin>>b[i];
		t2[b[i]].push_back(i);
	}
	for(int i=1;i<=n;++i){
		if(a[i]==b[i]){
			ans+=(n*(n+1)/2-i*(n-i+1));
		}
	}
	for(int i=1;i<=n;++i){
		sum1[i].resize(t2[i].size());
		sum2[i].resize(t2[i].size());
		if(!t2[i].empty()){
			sum1[i][0]=t2[i][0];
			for(int j=1;j<t2[i].size();++j){
				sum1[i][j]=sum1[i][j-1]+t2[i][j];
			}
			sum2[i][0]=n-t2[i][0]+1;
			for(int j=1;j<t2[i].size();++j){
				sum2[i][j]=sum2[i][j-1]+n-t2[i][j]+1;
			}
		}
		for(int j=0;j<t1[i].size();++j){
			int s=lower_bound(t2[i].begin(),t2[i].end(),t1[i][j])-t2[i].begin();
			int s1=lower_bound(t2[i].begin(),t2[i].begin()+s,n-t1[i][j]+1)-t2[i].begin();
			int s2=lower_bound(t2[i].begin()+s,t2[i].end(),n+1-t1[i][j])-t2[i].begin();
			if(s1!=0){
				ans+=(sum1[i][s1-1]);
			}
			ans+=(s-s1)*(n-t1[i][j]+1);
			ans+=(s2-s)*t1[i][j];
			if(!t2[i].empty()){
				ans+=(sum2[i][t2[i].size()-1]-(s2==0?0:sum2[i][s2-1]));
			}
		}
	}
	cout<<ans<<'\n';
	return 0;
} 
```
时间复杂度为 $O(n\log n)$。\
如果用指针单向移动代替二分或许可以 $O(n)$。

---

## 作者：Grace2022 (赞：0)

# P11670 [USACO25JAN] Cow Checkups S 题解
## 题目链接
[P11670 [USACO25JAN] Cow Checkups S](https://www.luogu.com.cn/problem/P11670)  
## 题意简述
给出两个数组 $a$ 和 $b$，任选两个端点 $l$ 和 $r$ 翻转 $a$ 数组，记翻转后有 $x$ 个数与 $b$ 数组相同，问所有情况的 $l$、$r$ 的 $x$ 之和。  
## 测试点1~5做法
### 题目分析
对于翻转问题我们发现，翻转 $l$ 到 $r$ 和翻转 $l+1$ 到 $r-1$ 中，翻转 $l+1$ 到 $r-1$ 的奶牛数不变，由此我们可以确定转移方程：```f[i][j]=f[i+1][j-1]+(a[i]==b[j])+(a[j]==b[i])```。  

注意：这里的转移数组 $f$ 的定义是翻转 $i$ 到 $j$ 后 $i$ 到 $j$ 的奶牛数，所以我们需要额外定义一个前缀和数组 $s$ 来记录没被翻转部分的奶牛数，在转移的过程中用变量 $ans$ 记录答案。  

对于初始化，我们需要初始化的是 $f_{i,i}$ 和 $f_{i,i+1}$。  

该算法的时间复杂度是 $\mathcal{O}(n^2)$，可以过前5个测试点。  
### 代码注解

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e3*5+10;
int a[N],b[N],s[N],f[N][N];
signed main(){
	int n,ans=0;
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	for(int i=1;i<=n;i++){
		scanf("%lld",&b[i]);
		f[i][i]=(a[i]==b[i]);//初始化
		s[i]=s[i-1]+(a[i]==b[i]);//前缀和数组
	}
	for(int i=1;i<=n;i++){
		ans+=s[n]; 
	}
	for(int i=1;i<n;i++){
		swap(a[i],a[i+1]);
		f[i][i+1]=(a[i]==b[i])+(a[i+1]==b[i+1]);//初始化
		swap(a[i],a[i+1]);
		ans+=f[i][i+1]+s[i-1]+s[n]-s[i+1];
	}
	for(int l=3;l<=n;l++){//类似区间dp的循环方式
		for(int i=1;i+l-1<=n;i++){
			int j=i+l-1;
			f[i][j]=f[i+1][j-1]+(a[i]==b[j])+(a[j]==b[i]);//转移方程
			ans+=f[i][j]+s[i-1]+s[n]-s[j];
		}
	}
	/*
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			cout<<i<<' '<<j<<' '<<f[i][j]<<' '<<s[i-1]+s[n]-s[j]<<endl;
		}
	}
	*/
	printf("%lld\n",ans);
	return 0;
}
```
## AC做法
### 题目分析
对于 $N\le5\times10^5$，我们想到构造 $\mathcal{O}(N)$ 或 $\mathcal{O}(N\cdot\log{N})$ 的算法。我们发现，对于每一头奶牛都只有**不被翻转**和**被翻转**两种情况，我们分类讨论。  

#### 不被翻转
对于每一个 $a_i$，如果和 $b_i$ 相同，我们应该加上这个 $a_i$ 所有不被翻转的情况数。不被翻转的情况数即总数减去被翻转的情况数，总数是 $\frac{N\times(N+1)}{2}$（含自己的两两配对），我们只需要求出被翻转的情况数。  

对于 $i$ 左边的所有端点（共 $i-1$ 个），每一个端点都会引出 $N-i+1$ 种覆盖情况，那么一共会有 $(i-1)\times(N-i+1)$ 种情况，具体可看图解。  

![](https://cdn.luogu.com.cn/upload/image_hosting/zj3bd6z8.png)  

大括号括起来的内容即所求内容。  

对于 $i$ 右边的所有端点（含 $i$ 自己），我们固定 $i$ 为左端点，那么右端点的个数就是 $N-i+1$（右端点是从 $i$ 到 $N$ 的所有下标，即求 $i$ 到 $N$ 的下标个数）。  

综上所述，不被翻转的情况总数即为 $(i-1)\times(N-i+1)+(N-i+1)=i\times(N-i+1)$，循环遍历一遍数组即可。  

#### 被翻转
沿用**测试点1~5做法**的思路，我们发现 $l$ 和 $r$ 的翻转并不影响其翻转过的内部与未翻转的外部的奶牛数，所以对于每一个 $a_i$，我们只需要找到与其值相等的所有 $b_i$ 并扩展即可，具体可看图解。  

![](https://cdn.luogu.com.cn/upload/image_hosting/rhc9uq5s.png)  

按照这个思路模拟，我们应该枚举每头奶牛 $a_i$ 所对应相等的所有 $b_j$，把 $i$、$j$ 与数组端点的距离取最小值，用答案变量 $ans$ 记录下来，即：```ans+=min(n-max(i,j)+1,min(i,j))```。  

但是如果所有的 $a_i$ 相等，且所有的 $b_i$ 与 $a_i$ 相等，或其它情况，时间复杂度仍然是 $\mathcal{O}(N^2)$，这违背了我们的初衷。该如何优化？通过观察```ans+=min(n-max(i,j)+1,min(i,j))```我们发现，双层循环仅涉及到了 $i$ 和 $j$ 比大小，我们可以把所有情况讨论出来。  

1. 当 $j\ge{i}$ 且 $N-j+1\le{i}$，即 $n-j+1\le{i}\le{j}$，答案为 $N-j+1$。
2. 当 $j\lt{i}$ 且 $N-i+1\le{j}$，即 $N-i+1\le{j}\lt{i}$，答案为 $N-i+1$。
3. 当 $j\ge{i}$ 且 $N-j+1\gt{i}$，即 $i\le{j}\lt{N-i+1}$，答案为 $i$。
4. 当 $j\lt{i}$ 且 $N-i+1\gt{j}$，即 $j\lt{i}\lt{N-j+1}$，答案为 $j$。

所有在取值范围内的 $i$ 和 $j$ 都成立，也就是说我们可以就着取值范围算出满足的个数，在乘上对应答案。这里考虑用二分做，问题就迎刃而解了。  
### 代码注解
因为考场上比较着急，我写的代码有些冗杂，有些地方是可以优化、合并的。我不知道 vector 怎么用 lower_bound 和 upper_bound，所以手写了一个二分。  

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=5*1e5+10;
int a[N],b[N];
vector<int> c[N],d[N];
int erfen1(int l,int r,int x,int f){
	int ans=-1,mid;
	while(l<=r){
		mid=(l+r)>>1;
		if(c[f][mid]>=x){
			ans=mid;
			r=mid-1;
		}
		else{
			l=mid+1;
		}
	}
	return ans;
}
int erfen2(int l,int r,int x,int f){
	int ans=-1,mid;
	while(l<=r){
		mid=(l+r)>>1;
		if(c[f][mid]>x){
			ans=mid;
			r=mid-1;
		}
		else{
			l=mid+1;
		}
	}
	return ans;
}
int derfen1(int l,int r,int x,int f){
	int ans=-1,mid;
	while(l<=r){
		mid=(l+r)>>1;
		if(d[f][mid]>=x){
			ans=mid;
			r=mid-1;
		}
		else{
			l=mid+1;
		}
	}
	return ans;
}
int derfen2(int l,int r,int x,int f){
	int ans=-1,mid;
	while(l<=r){
		mid=(l+r)>>1;
		if(d[f][mid]>x){
			ans=mid;
			r=mid-1;
		}
		else{
			l=mid+1;
		}
	}
	return ans;
}
signed main(){
//	cout<<log2(500005);
	int n,ans=0;
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		d[a[i]].push_back(i);
	}
	for(int i=1;i<=n;i++){
		scanf("%lld",&b[i]);
		c[b[i]].push_back(i);
	}
	for(int i=1;i<=n;i++){//������ת 
		ans+=(a[i]==b[i])*(n*(n+1)/2-(n-i+1)*i);
	}
//	cout<<ans<<endl;
	/*
//	cout<<ans<<endl;
	for(int i=1;i<=n;i++){
		for(auto j:c[a[i]]){
	//		cout<<i<<' '<<j<<' '<<ans<<endl;
			ans+=min(n-max(i,j)+1,min(i,j));
		}
	}
	*/
	for(int i=1;i<=n;i++){
	//	int t=lower_bound(c[a[i]],c[a[i]]+c[a[i]].size(),i)-c[a[i]];
		
		int t1=erfen1(0,c[a[i]].size()-1,i,a[i]),t2=erfen1(0,c[a[i]].size()-1,n+1-i,a[i])-1;
		if(t2==-2 && c[a[i]][c[a[i]].size()-1]<n+1-i){
			t2=c[a[i]].size()-1;
		}
		if(t1>=0 && t2>=0 && t2>=t1){
			ans+=(t2-t1+1)*i;
		}
	//	cout<<"3��"<<i<<' '<<t1<<' '<<t2<<' '<<ans<<endl;
		t1=erfen1(0,c[a[i]].size()-1,n-i+1,a[i]),t2=erfen1(0,c[a[i]].size()-1,i,a[i])-1;
		if(t2==-2 && c[a[i]][c[a[i]].size()-1]<i){
			t2=c[a[i]].size()-1;
		}
		if(t1>=0 && t2>=0 && t2>=t1){
			ans+=(t2-t1+1)*(n-i+1);
		}
	//	cout<<"2��"<<n-i+1<<' '<<t1<<' '<<t2<<' '<<ans<<endl;
	}
	
	for(int i=1;i<=n;i++){
		int t1=derfen1(0,d[b[i]].size()-1,n-i+1,b[i]),t2=derfen2(0,d[b[i]].size()-1,i,b[i])-1;
		if(t2==-2 && d[b[i]][d[b[i]].size()-1]<=i){
			t2=d[b[i]].size()-1;
		}
		if(t1>=0 && t2>=0 && t2>=t1){
			ans+=(t2-t1+1)*(n-i+1);
		}
	//	cout<<"1��"<<n-i+1<<' '<<t1<<' '<<t2<<' '<<ans<<endl;
		t1=derfen2(0,d[b[i]].size()-1,i,b[i]),t2=derfen1(0,d[b[i]].size()-1,n-i+1,b[i])-1;
		if(t2==-2 && d[b[i]][d[b[i]].size()-1]<n-i+1){
			t2=d[b[i]].size()-1;
		}
		if(t1>=0 && t2>=0 && t2>=t1){
			ans+=(t2-t1+1)*i;
		}
	//	cout<<"4��"<<i<<' '<<t1<<' '<<t2<<' '<<ans<<endl;
	}
	printf("%lld\n",ans);
	return 0;
```

---

## 作者：I_will_AKIOI (赞：0)

首先考虑暴力，枚举端点，暴力翻转，最后求和，时间复杂度为 $O(n^3)$，可以通过测试点 $1\sim 4$。

考虑计算每对端点 $l,r$ 的贡献，发现只有当 $a_l=b_r$ 时，才会产生贡献。我们可以把区间 $[l,r]$ 变为 $[l-1,r+1]$，这样结果不变，所以 $l,r$ 的贡献就是 $\min\{l,n-r+1\}$。注意我们只考虑了 $[l,r]$ 的情况，所以还要加上 $[1,l-1]$ 和 $[r+1,n]$ 的贡献。用 vector 记录一下 $a_l=b_r$ 的 $r$ 的位置，可以通过测试点 $1\sim 9$。

考虑快速计算每一对端点的贡献。先考虑 $l\le \displaystyle\frac{n}{2}$ 时，$l\le n-r+1$ ，此时若 $\min\{l,n-r+1\}=l$，所以可以二分出最大的 $r$，计算这个区间的贡献。而对于 $n-r+1<l$ 的情况，贡献为 $n-r+1$，可以预处理出后缀和解决。对于 $r>\displaystyle\frac{n}{2}$ 情况同理，时间复杂度为 $O(n\log n)$，当然也可以用双指针优化到 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 500005
using namespace std;
int n,ans,pre[N],suf[N],sum[N],a[N],b[N],len[N];
vector<int>v[N],sum1[N],sum2[N];
signed main()
{
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) v[i].push_back(0);
	for(int i=1;i<=n;i++)
	{
		cin>>b[i];
		v[b[i]].push_back(i);
		if(a[i]==b[i]) pre[i]=suf[i]=1;
	}
	for(int i=1;i<=n;i++) v[i].push_back(1e9),len[i]=v[i].size()-2;
	for(int i=1;i<=n;i++) pre[i]+=pre[i-1];
	for(int i=n;i>=1;i--) suf[i]+=suf[i+1],sum[i]=sum[i+1]+suf[i];
	for(int i=1;i<=n;i++) ans+=(n-i+1)*pre[i-1]+sum[i+1];
	for(int i=1;i<=n;i++)
	{
		sum1[i].resize(len[i]+2),sum2[i].resize(len[i]+2);
		for(int j=1;j<=len[i];j++) sum1[i][j]=sum1[i][j-1]+v[i][j];
		for(int j=len[i];j>=1;j--) sum2[i][j]=sum2[i][j+1]+(n-v[i][j]+1);
	}
	for(int i=1;i<=n/2;i++)
	{
		int l=lower_bound(v[a[i]].begin(),v[a[i]].end(),i)-v[a[i]].begin();
		int r=upper_bound(v[a[i]].begin(),v[a[i]].end(),n-i+1)-v[a[i]].begin()-1;
		ans+=(r-l+1)*i+sum1[a[i]][l-1]+sum2[a[i]][r+1];
	}
	for(int i=n/2+1;i<=n;i++)
	{
		int l=lower_bound(v[a[i]].begin(),v[a[i]].end(),n-i+1)-v[a[i]].begin();
		int r=upper_bound(v[a[i]].begin(),v[a[i]].end(),i)-v[a[i]].begin()-1;
		ans+=(r-l+1)*(n-i+1)+sum1[a[i]][l-1]+sum2[a[i]][r+1];
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：HHC883 (赞：0)

# 题目分析
对于铜组同名题目（第三题），我们是通过枚举区间，对每个区间分别计算而得到答案。但是本题如果还是去枚举区间，很难找到低时间复杂度的算法。于是，我们换一种思路，我们考虑对于每个下标去算贡献，对于每个下标 $i$，去计算有多少个区间，翻转后位于 $i$ 处的奶牛品种恰好为 $b_i$。为了算出这个，我们应当注意到一个结论，就是对于 $i < j$，满足翻转后位于 $j$ 处的奶牛品种恰好为 $a_i$ 的区间数量为 $\min(i , n - j + 1)$。通俗点说，就是有 $\min(i , n - j + 1)$ 个区间，对其翻转后奶牛 $i$ 会移动到 $j$ 处。这很好理解，首先令 $l = i , r = j$，则区间 $(l , r)$ 满足条件。接下来不断地让 $l$ 减 $1$，$r$ 加 $1$，也就是不断向两侧扩大区间，得到的所有区间自然也满足条件。当某个端点（$l$ 或 $r$）到达序列边缘时，便不能继续扩大区间了，于是满足条件的区间总数为 $\min(i , n - j + 1)$。有了这个结论，就很容易求得每个下标的贡献了，我是使用了比较好想的二分法。另外，应当注意若存在 $a_i = b_i$，则对于所有与 $i$ 无关的区间也满足条件，应当特殊处理。

时间复杂度 $O(n \log n)$，常数略大，但即使时限为 $1$ 秒，通过本题也绰绰有余。如果想要优化运行时间，可以使用[手写 vector](https://www.luogu.com.cn/article/r4a8d6kt)。
# 参考代码
```cpp
#include<iostream>
#include<vector>
#include<algorithm>
#define int long long
using namespace std;
int n,a[(int)5e5+5],b[(int)5e5+5];
vector<int> bin[(int)5e5+5],pre1[(int)5e5+5],pre2[(int)5e5+5];
int ans;
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	for(int i=1;i<=n;i++){
		bin[i].push_back(0);
		pre1[i].push_back(0);
		pre2[i].push_back(0);
	}
	for(int i=1;i<=n;i++){
		bin[a[i]].push_back(i);
		pre1[a[i]].push_back(pre1[a[i]][pre1[a[i]].size()-1]+i);
	}
	for(int i=n;i>=1;i--) pre2[a[i]].push_back(pre2[a[i]][pre2[a[i]].size()-1]+i);
	for(int i=1;i<=n;i++){
		int cut1=lower_bound(bin[b[i]].begin(),bin[b[i]].end(),n-i+1)-bin[b[i]].begin()-1;
		int cut2=lower_bound(bin[b[i]].begin(),bin[b[i]].end(),i)-bin[b[i]].begin();
		ans+=pre1[b[i]][min(cut1,cut2-1)]+(cut2-1-min(cut1,cut2-1))*(n-i+1);
		if(bin[b[i]][cut2]==i) ans+=min(i,n-i+1),cut2++;
		ans+=(pre2[b[i]].size()-max(cut1+1,cut2))*(n+1)-pre2[b[i]][pre2[b[i]].size()-max(cut1+1,cut2)]+(max(cut1+1,cut2)-cut2)*i;
	}
	for(int i=1;i<=n;i++){
		if(a[i]==b[i]) ans+=(i-1)*i/2+(n-i)*(n-i+1)/2;
	}
	cout<<ans;
	return 0;
}
```

---

