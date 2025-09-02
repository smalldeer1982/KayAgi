# 题目信息

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

# AI分析结果

• 综合分析与结论：这些题解主要围绕如何找到使得小Z有必胜策略的X值。思路大多基于前缀和，通过枚举小Z取牌的情况，确定对应的小Y取牌情况，进而得出X的取值范围。算法要点在于利用前缀和的单调性，通过二分查找或双指针法优化查找过程，部分题解还使用了差分来统计答案。解决难点在于如何高效地确定小Y的最优取牌策略以及X的取值范围。整体来看，各题解在思路清晰度、代码可读性和优化程度上存在差异。

所选的题解：
  - 作者：StudyingFather (赞：22)  星级：5星
    - 关键亮点：思路清晰，先分析小Y为不输的理想取牌情况，得出让小Z胜出需使上限x小于小Y的分数。提出用二分查找或双指针法找对应q值，给出二分做法代码，时间复杂度为O(n log n)，并指出双指针法时间复杂度为O(n)更优。
    - 重点代码核心思想：利用前缀和数组a，通过二分查找lower_bound找到满足条件的位置，对满足条件的X范围进行计数，最后通过前缀和数组res统计答案。
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
  - 作者：Hexarhy (赞：12)  星级：5星
    - 关键亮点：详细分析游戏特点，引入区间和概念，通过对获胜条件的数学推导得出关键式子。指出用前缀和预处理，利用前缀和单调性二分查找y，还提到可用双指针法优化。对实现细节如STL使用注意点进行详细说明，并给出参考代码。
    - 重点代码核心思想：通过前缀和数组s记录前缀和，利用lower_bound二分查找满足条件的位置，根据不同情况确定X的取值范围并记录到ans数组，最后对ans数组进行排序、去重并输出。
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
	vector<ll> a(n+2),s(n+2);
	for(ll i=1;i<=n;i++)
	{
	 	scanf("%lld",&a[i]);
		s[i]=s[i-1]+a[i];
	}
	scanf("%lld",&k);
	for(ll x=1;x<=n && s[x]<=k;x++)
	{
		const auto iter=lower_bound(s.begin()+1,s.begin()+1+n,s[x]*2LL);
		for(ll i=s[x];i<=k && (iter==s.begin()+1+n?true:i<*iter-s[x]);i++)
		 ans.push_back(i);
	}
    sort(ans.begin(),ans.end());
	ans.erase(unique(ans.begin(),ans.end()),ans.end());
	printf("%lld\n",ans.size());
	for(auto i:ans)
	 printf("%lld ",i);
	return 0;
}
```
  - 作者：littleKtian (赞：5)  星级：4星
    - 关键亮点：思路简洁明了，考虑小Z每种取牌方案，通过定义p[i]为前缀和，找到满足p[t] - p[i] >= p[i]的最小t，得出X在[p[i], p[t] - p[i])区间时小Z必胜，最终求所有区间并集得到答案。提到可以用二分或双指针法找t，给出用差分求区间并集的代码，复杂度为O(n log n)或O(n)。
    - 重点代码核心思想：通过dr函数读取数据并计算前缀和p，利用while循环找到满足条件的t，对相应区间进行差分标记，最后通过前缀和数组x统计答案。
```cpp
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

最优关键思路或技巧：利用前缀和优化区间和计算，通过分析小Y为保证不输的取牌策略，结合前缀和单调性，采用二分查找或双指针法确定小Y的取牌位置，从而得出X的取值范围。对于统计答案，使用差分的方法简化区间操作。

可拓展之处：同类型题可考察在类似博弈场景下，通过分析双方最优策略，利用数据结构或算法优化来确定满足特定条件的参数范围。类似算法套路包括利用前缀和处理区间问题，结合单调性进行二分查找或双指针优化。

推荐洛谷题目：
  - P1115 最大子段和：考察前缀和与动态规划，与本题利用前缀和处理问题的思路相关。
  - P3397 地毯：通过二维前缀和解决矩形区域的统计问题，可加深对前缀和应用的理解。
  - P1438 无聊的数列：结合前缀和与二分查找，与本题思路有相似之处。

个人心得摘录与总结：
  - 作者Hexarhy提到考场上想到AC做法不容易，且细节多，debug耗时久。强调在使用STL时要注意函数特性，如左右端点开闭性、unique函数只能移动重复元素等，建议开启O2优化。总结为在复杂问题中，不仅要想出算法思路，实现细节也至关重要，对常用库函数的深入理解能避免许多错误。 

---
处理用时：70.49秒