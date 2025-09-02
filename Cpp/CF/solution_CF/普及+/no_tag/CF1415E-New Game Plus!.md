# New Game Plus!

## 题目描述

Wabbit is playing a game with $ n $ bosses numbered from $ 1 $ to $ n $ . The bosses can be fought in any order. Each boss needs to be defeated exactly once. There is a parameter called boss bonus which is initially $ 0 $ .

When the $ i $ -th boss is defeated, the current boss bonus is added to Wabbit's score, and then the value of the boss bonus increases by the point increment $ c_i $ . Note that $ c_i $ can be negative, which means that other bosses now give fewer points.

However, Wabbit has found a glitch in the game. At any point in time, he can reset the playthrough and start a New Game Plus playthrough. This will set the current boss bonus to $ 0 $ , while all defeated bosses remain defeated. The current score is also saved and does not reset to zero after this operation. This glitch can be used at most $ k $ times. He can reset after defeating any number of bosses (including before or after defeating all of them), and he also can reset the game several times in a row without defeating any boss.

Help Wabbit determine the maximum score he can obtain if he has to defeat all $ n $ bosses.

## 说明/提示

In the first test case, no resets are allowed. An optimal sequence of fights would be

- Fight the first boss $ (+0) $ . Boss bonus becomes equal to $ 1 $ .
- Fight the second boss $ (+1) $ . Boss bonus becomes equal to $ 2 $ .
- Fight the third boss $ (+2) $ . Boss bonus becomes equal to $ 3 $ .

Thus the answer for the first test case is $ 0+1+2=3 $ .

In the second test case, it can be shown that one possible optimal sequence of fights is

- Fight the fifth boss $ (+0) $ . Boss bonus becomes equal to $ 5 $ .
- Fight the first boss $ (+5) $ . Boss bonus becomes equal to $ 4 $ .
- Fight the second boss $ (+4) $ . Boss bonus becomes equal to $ 2 $ .
- Fight the third boss $ (+2) $ . Boss bonus becomes equal to $ -1 $ .
- Reset. Boss bonus becomes equal to $ 0 $ .
- Fight the fourth boss $ (+0) $ . Boss bonus becomes equal to $ -4 $ .

Hence the answer for the second test case is $ 0+5+4+2+0=11 $ .

## 样例 #1

### 输入

```
3 0
1 1 1```

### 输出

```
3```

## 样例 #2

### 输入

```
5 1
-1 -2 -3 -4 5```

### 输出

```
11```

## 样例 #3

### 输入

```
13 2
3 1 4 1 5 -9 -2 -6 -5 -3 -5 -8 -9```

### 输出

```
71```

# 题解

## 作者：gyh20 (赞：25)

首先，看到数据范围里 $n,k$ 都是 $5\times 10^5$，可以猜想是 $O(n\log n)$ 算法，这个东西感觉不是很好 DP，于是我想到了贪心。

由于带 $\log$，首先考虑堆贪心。

由于我们可以进行 $k$ 次操作，我们可以看成分为 $k+1$ 组，每一组内部自选。

首先，每一组内部一定是不上升的，否则交换两个位置一定更优。

所以我们先要把 $a$ 排序。

then？

令第 $i$ 组当前的元素总和为 $sum_i$ 那么当我们将一个价值 $x$ 的值加入时，$ans+=sum_i,sum_i+=x$。

可以发现，当选择最大的 $sum_i$ 时一定不劣（收益一定）。

用一个堆维护即可。

代码实现非常简单，没有任何细节。

```cpp
#include<bits/stdc++.h>
#define re register
#define int long long
using namespace std;
inline int read(){
	re int t=0,f=0;re char v=getchar();
	while(v<'0')f|=(v=='-'),v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return f?-t:t;
}
priority_queue<int>q;
int n,m,t,a[1000002],h[1000002];
long long ans,sum;
signed main(){
	n=read(),m=read();
	for(re int i=1;i<=n;++i)a[i]=read();
	sort(a+1,a+n+1),reverse(a+1,a+n+1);
	for(re int i=1;i<=m+1;++i)q.push(0);
	for(re int i=1;i<=n;++i){
		int xx=q.top();
		q.pop();
		ans+=xx;
		xx+=a[i];
		q.push(xx);
	}
	printf("%lld",ans);
}

```


---

## 作者：HPXXZYY (赞：6)

$\color{blue}{\texttt{[Solution]}}$

因为选择的顺序是任意的，所以我们可以用贪心解决问题。

从大到小排序 $c_{1 \cdots n}$，从前往后考虑选择每一个 $c_{i}$。

当前缀和仍然是正数时，显然我们应该直接把它加入计数器中。

不断地重复上述操作直到前缀和小于 $0$。

假设我们还剩下 $m$ 个数（它们一定是负数）。现在我们要干的事情就是用 $k$ 个段，使得它们的总贡献最大（这样加到答案中答案才会尽可能大）。

假设我们把 $l$ 个数 $c_{a_{1}},c_{a_{2}},\cdots,c_{a_{l}}$ 分成了一组，则它们的贡献是：

$$\sum\limits_{i=1}^{l} c_{a_{i}} \times (l-i)$$

显然，我们应该让最小的 $c_{a_{i}}$ 尽量在一段数字的后面（这样它们的权较小，负贡献较小，即贡献较大）。

因为我们有 $(k+1)$ 段，所以肯定是最小的 $(k+1)$ 个数分列每个段的末尾，次小的 $(k+1)$ 个数在每个段的倒数第二位，以此类推即可得出答案。

$\color{blue}{\texttt{[code]}}$

```cpp
const int N=5e5+100;
typedef long long ll;
int n,k,pos,a[N];ll sum,ans;
int main(){
	n=read();k=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	sort(a+1,a+n+1);
	for(int i=n;i>=1;i--){
		ans+=sum;sum+=a[i];
		if (sum<0){pos=i;break;}
	}
	a[pos]=sum;//Pay attention to it
	for(int i=1;i<=pos;i++)
		ans+=1ll*(i-1)/(k+1)*a[i];
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Refined_heart (赞：5)

### $\text{Solution:}$

首先应当明白，**最优组合一定可以看成 $k+1$ 个集合**，集合可以是空。

那么每次计算答案，我们应该把这个数放到最大的那个集合里面。

这里之所以可以任意选择，是因为我们可以按照这样计算出来的集合来对序列进行一样的决策。

那么我们现在只需要知道哪个集合是最大的就行了。

对 $a$ 数组排序，然后我们**只需要把当前最大数插入到最大集合里面。**

而动态回答最大值可以用堆来实现。

代码实现过于简单就不给出了。

---

## 作者：IceKylin (赞：3)

# CF1415E New Game Plus! 题解
### [原题链接（in luogu）](https://www.luogu.com.cn/problem/CF1415E)
### [原题链接（in CodeForces）](https://codeforces.com/contest/1415/problem/E)
### [更好的阅读体验？](https://www.luogu.com.cn/blog/std-IK/cf1415e-ti-xie)
这是一道求最大值的题目，由于此题使用 DP 算法会有一定的 **后效性**（存在清零操作），而记录全部状态又会 **TLE** （时间复杂度为 ${O(nk)}$）。所以会自然想到另一种求最值的做法：**贪心**。

考虑使用 **堆**（即 STL 库中的优先队列：priority_queue）来维护单次操作的最大值，通过不断累加局部最优解得到全局最优解。

大致思路明确后，我们开始具体分析：

1. 将 ${c}$ 数组按 **从大到小** 的顺序重新排列。

2. **初始化堆** ：由于计数器初值为 ${0}$，清零操作后又会有至多 ${k}$ 个 ${0}$，所以将总共 ${(k+1)}$ 个 ${0}$ 放入堆中。

3. 重复 ${n}$ 次步骤 4。

4. 第 ${i}$ 次从堆中取出当前的 **最大值**，记作 ${mx}$。累加答案（${ans\gets ans+mx}$），将 ${(mx+c_i)}$ 重新放入堆中。

这里对上述分析给出一种 **不严谨但容易理解** 的证明：

------------
设存在一次操作使得取出的数不为当前堆的最大值，记作 ${mx'}$。

设 ${f(x)}$ 表示 ${x}$ **当前操作** 对答案的贡献，${f'(x)}$表示 ${x}$ **之后操作** 对答案的贡献，${F(x)}$ 表示 ${x}$ 对答案的 **贡献之和**。

${F(x)=f(x)+f'(x)}$


${\because mx'<mx}$

${\therefore f(mx')<f(mx)}$

又 ${\because mx'+c_i<mx+c_i}$

${\therefore f'(mx')<f'(mx)}$

${\therefore F(mx')<F(mx)}$

所以可得每次操作中 $mx$ 都是对答案贡献最大的数值，得证。

------------
分析结束后，这道题就只剩下模拟了，**时间复杂度** 为 ${O(n\log n)}$。

P.S. 此题数据范围建议开 **long long** 。

## AC 代码
```cpp
//By IceKylin
#include<bits/stdc++.h>
#define ll long long
#define il inline
#define maxn 1000050
using namespace std;
priority_queue<ll>q;
ll n,k,ans,a[maxn];


il bool cmp(ll x,ll y){
	return x>y;
}


int main(){
	ios::sync_with_stdio(false);
	cin>>n>>k;
	for(int i=1;i<=n;++i)cin>>a[i];
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=k+1;++i)q.push(0); 
	for(int i=1;i<=n;++i){
		ll val=q.top();
		q.pop();
		ans+=val;
		q.push(val+a[i]);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：hater (赞：3)

这场Div1真的有够丢人的

当khj和zjy已经胡出做法时 自己根本不在他们的世界

最后还是khj调出来的 丢死人 

开始说题 

我们把这k次分割抽象成k+1行 

我们把这些元素放到这k+1行中 按顺序击败boss 行与行之间互不干扰 

先考虑在同一行中 元素的摆放顺序 

一个元素假如在第 i 次被消除 总共有len个元素要被消除 

那么他的贡献就是 $c_{i}*(len-i)$ 

这么来看 同一行内越大的肯定越放前面 

考虑正数 一定是要使len越大越好 

所以他们不会被分到不同行内 

考虑负数 一定要使len越小越好 

所以他们会被均摊到每一行中 

（ 具体见代码 ） 


所以我们一开始的形态是这样的 

![](https://cdn.luogu.com.cn/upload/image_hosting/9oof9h9v.png?x-oss-process=image/resize,m_lfit,h_170,w_225)


黑色是负数 被均摊 

而红色是正数 在同一行内 

但是如果我们把这个负数放到这里 

![](https://cdn.luogu.com.cn/upload/image_hosting/jbo5aep9.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

就会多出 $presum+c_{i}$  presum 指那段正数的和 

为什么会多加一个ci 因为你把那个移上去时 len多了1 

显然这个贡献可以为正  而且我们在移动时 负数一定是从大到小移 

那么我们就枚举一下 后面多了几个负数 就可以了 

注意当我们多移了一个元素时 那个presum是会变的 随着更新 

```cpp
#include<bits/stdc++.h> 
#define rg register 
#define i60 long long 
#define fp( i , x , y ) for( rg int i=(x); i<=(y); ++i ) 
#define fq( i , x , y ) for( rg int i=(y); i>=(x); --i ) 
using namespace std ; 
const int N = 5e5+10 ;  
int a[N] , n , k , b[N] , lena , lenb ; 
i60 ans , s[N] , val[N] , cnt[N] , pos[N] ;    
bool cmp( int A , int B ) { return A > B ; }  
signed main( ) { 
  ios::sync_with_stdio(false) ; 
  cin.tie(0) ; 
  int x ; 
  cin >> n >> k ; 
  fp( i , 1 , n ) { 
    cin >> x ; 
    if( x < 0 ) a[++lena] = x ; 
	else b[++lenb] = x ;  
  } 
  sort( a+1 , a+1+lena , cmp ) ; 
  sort( b+1 , b+1+lenb , cmp ) ; 
  i60 presum = 0 ;   
  fp( i , 1 , lenb ) ans += presum , presum += b[i] ;  
  fq( i , 1 , lena ) { 
    pos[i] = (lena-i)%(k+1)+1 ;  
    ans += 1ll * a[i] * cnt[pos[i]] ;  
    cnt[pos[i]] ++ ; 
  } 
  ans += presum * cnt[1] ;  
  i60 nw = ans ; 
  fp( i , 1 , lena ) { 
    if( pos[i] != 1 ) nw += a[i] + presum ; 
	presum += a[i] ;  
    ans = max( ans , nw ) ; 
  } 
  cout << ans << '\n'; 
  return 0 ; 
}  
                 
```







---

## 作者：yuzhuo (赞：2)

这个题目思维难度高，但代码很短。

我们有 $k$ 次清零机会，加上初始值也是 $0$，一共有 $k+1$ 次清零。

我们可以看作（但不用在代码里体现）：

![图片](https://cdn.luogu.com.cn/upload/image_hosting/umvmp3op.png?x-oss-process=image/resize,m_lfit,h_1000,w_1000)

我们要思考如何将 $n$ 个数字放入这些“栈”中。

首先，显而易见的是我们肯定要从大到小进行排序（利益值高）。

我们可以推出：要把数（此处指从大到小排序后）给尽量大的“栈”（此处指元素之和最大的栈）。

我们可以感性的证明：要处理的数（也是还没有处理的最大数）为 $x$，最大的栈的总和为 $S$，其他的栈的总和为 $S'$。

那么 $S<S'$，则 $S+x<S'+x$。

也就是说，下一次肯定是 $S$ 栈拿的比 $S'$ 栈拿的更多。

而取决好坏的唯一信息也就是下一次谁拿的多。

所以肯定是 $S$ 更好。

那我们可以用一个堆去实现每次找最大的栈。

这个题目也就迎刃而解了！

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 5e5 + 7;
int n, k, a[N], sum;
priority_queue<int> q;
signed main() {
	cin >> n >> k;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	sort(a + 1, a + n + 1, greater<int>());
	for (int i = 1; i <= k + 1; ++i) q.push(0);
	for (int i = 1; i <= n; ++i) {
		int val = q.top(); q.pop();
		sum += val;
		val += a[i];
		q.push(val);
	}
	cout << sum << endl;
}
```

---

## 作者：c_y_y (赞：1)

# [CF1415E 题解](https://www.luogu.com.cn/problem/CF1415E)
## （〇）写在题解之前
- 本篇题解很多为转载，你不用点赞本篇题解，而应当点赞我下面提到的作者，TA 们真的很优秀。
-  _通俗来说_  板块多半属于个人想法， _数学上_ 多半属于转载。

## （一）题目线索 1
>首先应当明白，最优组合一定可以看成 $k+1$ 个集合，集合可以是空。——Refined_heart

这句话直接点出本题重点。当我们把这些数全部放到 $k+1$ 个集合中时，这就相当于使用了 $k$ 次**清零操作**。由于不需要把 $k$ 次操作用完，因此集合可以为空。

## （二）题目线索 2
我们需要将 $c$ 数组从大到小排序。

_通俗来说_ ，如果把大数放到前面，这个集合中的 `boss bonus` 就会增加 $c_{i}$。那么，由于每次 $ans$ 都增加，那么这个大数的贡献是**相对于后面的数**最大的（此处用到了 _贪心_ 思想）

_数学上_ ，
>一个元素假如在第 $i$ 次被消除，总共有 $len$ 个元素要被消除，那么他的贡献就是 $c_{i}\times(len−i)$。这么来看 **同一集合内**越大的肯定越放**前面**。——hater

## （三）题目线索 3
本题用优先队列存储，因为每次要从最大值那的堆中放入 $c_{i}$。

_通俗来说_ ，如果一个数加入最大集合，那么这个堆对 $ans$ 的影响永远是最大的（因为数组已经从大到小排序了），反之亦然。

_数学上_ ，
>设存在一次操作使得取出的数不为当前堆的最大值，记作 $mx'$
 。
设 $f(x)$ 表示 $x$ 当前操作**对答案的贡献**，$f'(x)$ 表示 $x$ 之后操作**对答案的贡献**，$F(x)$ 表示 $x$ 对答案的**贡献之和**。

>$$F(x)=f(x)+f $$
>$$∵mx'<mx$$ 
>$$∴f(mx')<f(mx)$$
>$$又 ∵mx'+c_{i}<mx+c_{i}$$
>$$∴f'(mx')<f'(mx)$$
>$$∴F(mx')<F(mx)$$

>所以可得每次操作中 $mx$ 都是对答案贡献最大的数值，得证。
——IceKylin

这个数学证法非常**完美**。

## （四）代码实现？
代码就不展现了，楼下的大佬代码写得很好……

本人的第三篇题解，是有点特色的，望多多支持~

---

## 作者：MoyunAllgorithm (赞：1)

在题解的基础上，对错解进行了证伪。

### 题意

给你 $N$ 个数，分配成 $K+1$ 个数列。对于每个数列 $a_{1,2,\cdots M}$，设前缀和为 $ pre_{1,2,\cdots M}$，则这个数列 $a$ 的分数是 $\displaystyle\sum_{i=1}^{M-1} pre_i$。你的总分是这 $K+1$ 个数列的分数的和。最大化这个和。

### 错误解法

一开始我写的这个第三个样例就过不去 `qwq`

首先，从大到小排序，之后扫一遍，并相加，如果和 $< 0$ 就到下一个数列（不过最后一个数列可能必须得是负）。

**反例：**  当$K=1$，数是 $7,5,-13,-14,-15$。上述方法中，会分成 $\{7,5,-13\}$ 和 $\{-14,-15 \}$，得到的分数是 $0+7+12+0+(-14)=5$。但是，我们可以想到一种更优的构造：$\{7,5,-15\}$ 和 $\{-13,-14\}$，分数是$0+7+12+0+(-13)=6$。

### 分析

首先，每个数列相互独立。在每个数列内，元素**单调不增**，因为**只有大数在前，他对前缀和的贡献才能最大化**。因此，先从大到小排序。

那么，如何判断一个数进入哪个数列呢？假设这个数是 $x$，它是目前还没有加入数列的最大的数，有 $2$ 个数列可供选择，目前的分数分别是 $sum_a$ 和 $sum_b$，$sum_a >sum_b$，你的总分数是 $tot$，那么你会发现：

如果 $x$ 加入 $a$ ，那么 `tot+=(sum[a]+x);`

如果 $x$ 加入 $b$ ，那么 `tot+=(sum[b]+x);`

可以发现，加入 $a$ 是对总结果更优的。

那么可以得到贪心策略：**每次最大数进入最大数列。**

可以用 `priority_queue` 实时获取最大数列的编号。需要注意是，不需要存储数列，只需要维护数列当前的和即可。

### CODE

```c
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
const int MAXN=5*1e5+5;
int N,K;
long long ans=0;
int c[MAXN];
priority_queue<long long>heap;
bool cmp(int x,int y)
{
    return x>y;
}
int main()
{
    scanf("%d %d",&N,&K);
    for(int i=1;i<=N;i++) scanf("%d",&c[i]);
    sort(c+1,c+N+1,cmp);
    for(int i=1;i<=K+1;i++) heap.push(0);
    for(int i=1;i<=N;i++)
    {
        long long sum=heap.top();
        heap.pop();
        ans+=sum;
        sum+=c[i];
        heap.push(sum);
    }
    printf("%lld\n",ans);
    return 0;}
```




---

## 作者：RockyYue (赞：0)

### 1415E

给定 $c_{1\dots n}$，有变量 $sum$ 和答案 $ans$，初始均为 $0$。

每次任选一个 $c_i$，$ans:=ans+sum$，$sum:=sum+c_i$，每个 $c_i$ 都要被选择一次且仅能被选择一次。

有 $k$ 次机会，可以在某次操作前将 $sum$ 赋为 $0$，求 $ans$ 最大值，要求 $O(n\log n)$。

### Sol

- 对于正数，从大往小一直加，这个和的基础上还可以加一些比较小的负数，同样从大往小，直到其 $<0$，或者更确切一些，比余下的最大负数要小，这个时候就要考虑 $sum:=0$ 的一次机会用在哪里了。
- 可以知道，一段内若没有赋 $0$ 操作，一定是从大往小加的，而赋 $0$ 的操作的处理需要结合全局。
- 这样的分组可以考虑换一个顺序处理，从前往后加改为设置 $k+1$ 组，将元素加到组里。
  - 这样的好处在于直观，$c_i$ 哪里最需要就去哪里。
- $c_i$ 从大到小处理，每次加入当前元素和最大的组，这样对本次操作的贡献和操作后的 $sum$ 都是最优的。
- 实现中，优先队列维护每组和，初始加入 $k+1$ 个 $0$，每次选最大值加上 $c_i$ 计算贡献。

---

## 作者：dream_on_screen (赞：0)

作者想要红名，于是就有了这篇题解。

我们可以把 $k$ 次清零的机会看作是把数组分成 $k+1$ 个部分，可以发现把较大的数字优先使用得到的结果会更好，所以把数组从大到小排序。

然后每次都选择一个目前总和最大的部分添加进去数字就可以了。最大值的查询可以用堆来维护。

然后代码实现也很简单，但是如果没有开 `long long` 的话你可能会 WA on #9

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
priority_queue<long long> q;
long long n,k,a[500005];
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=k+1;i++)
		q.push(0);
	long long ans=0;
	for(int i=n;i>=1;i--)
	{
		long long p=q.top();
		q.pop();
		ans+=p;
		p+=a[i];
		q.push(p);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：UncleSam_Died (赞：0)

### 解题思路

简单贪心题，我们可以把整个序列看作 $k+1$ 个可重集，首先可以得到一个显然的结论：较大的数一定比较小的数先放入一个集合中。同样，由于每一轮 $ans\gets ans+\max sum_i$，其中 $sum_i$ 表示第 $i$ 个集合的元素和，那么，我们一定会将当前的元素放入当前和最大的哪个集合。

综上，本题步骤如下：
- 初始将每个集合的值赋为 $0$；
- 将数组从大到小排序，先把大的加入集合；
- 将 $ans\gets ans+\max sum_i$；
- 取出最大的哪个集合，然后将当前元素加入并重新计算最大的集合。


### AC 代码
```cpp
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include <set>
#include <map>
#define ll long long
#define int ll
#define N 500005
int n,k,c[N];ll sum,ans;
inline bool cmp(int a,int b){
    return a>b;
}
struct Cmp{
    inline bool operator ()(
        const int a,
        const int b
    ) const {
        return a>b;
    }
};
std::set<ll,Cmp> s;
std::map<ll,ll> m;
signed main(){
    scanf("%lld%lld",&n,&k);int l;
    for(register int i=1;i<=n;++i)
        scanf("%lld",&c[i]);
    std::sort(c+1,c+n+1,cmp);
    for(register int i=1;i<=k+1;++i)
        ++m[0];s.insert(0);
    for(register int i=1;i<=n;++i){
        auto now=*s.begin();
        --m[now];if(!m[now])
            s.erase(now);
        ans+=now;++m[now+c[i]];
        s.insert(now+c[i]);
    }printf("%lld",ans);
}
```

---

## 作者：Paris_Commune (赞：0)

### 分析

贪心。

当 $k=0$ 时，很明显的前缀和贪心，将 $c_i$ 从大到小排序即可。

考虑 $k$ 不为 $0$ 的情况，同样先从大到小排序，最优情况是 $k+1$ 个集合，集合可以是空集，总答案为所有集合的答案相加。

对于每一组，答案就是这个集合从大到小排序后的前缀和。

需要开 `long long`。

### 部分代码

```cpp
for(int i=n;i>=1;i--){
	ans+=cnt;//统计答案
	cnt+=c[i];//前缀和
	if(cnt<0){
		tmp=i;//断开
        c[i]=cnt;
		break;
	} 
}
for(int i=1;i<=tmp;i++){
	ans+=c[i]*(i-1)/(k+1);//集合个数 k+1 个
}
```

---

## 作者：Purslane (赞：0)

## Solution

如果没有清零操作 , 就是经典的排队接水问题 , 可以贪 .

所以应该先从大到小排序 , 这样肯定不劣 .

有 $m$ 次清零操作 , 就相当于有 $m+1$ 段 , 每次加入一个新数的时候找一段插入 .

那么插入的时候对答案的贡献是这一段已有的大小 , 显然应该找最大的插入 .

可是这样会不会得到眼前的利益却损失了更大的利益呢 ? 不会 .

假设有 $a$ 和 $b$ 两段 , $a>b$ . 如果我们找 $a$ 插入 , 当插入的数大于 $0$ 时 , 肯定时多多益善 ; 如果小于 $0$ , 那么 $a$ 就变小了 , 变成 $a+x$ . 这样再选不会变小吗 ? 可是如果你插入 $b$ , 下一次再选 $a$ , 那么你的价值是 $a+b$ ; 但是如果你插入 $a$ , 下一次你肯定可以再选 $b$ , 这样也是 $a+b$ ; 况且如果 $a+x > b$ , 你还可以获得更大的效益 . 所以插入最大的肯定更优 .

所以就写完了 . 代码很简单 .

code :

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
using namespace std;
const int MAXN=5e5+10;
int n,k,a[MAXN],ans;priority_queue<int> q;
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>k;ffor(i,1,n) cin>>a[i];
	sort(a+1,a+n+1,[](int a,int b){return a>b;});
	ffor(i,1,k+1) q.push(0);
	ffor(i,1,n) {int u=q.top();ans+=u,q.pop(),q.push(u+a[i]);}
	cout<<ans;
	return 0;
}
```

---

