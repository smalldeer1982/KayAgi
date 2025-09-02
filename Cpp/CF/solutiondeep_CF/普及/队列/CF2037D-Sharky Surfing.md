# 题目信息

# Sharky Surfing

## 题目描述

Mualani 喜欢在她的大鲨鱼冲浪板上冲浪！

Mualani 的冲浪路径可以用一个数轴来表示。她从位置 $1$ 开始，路径的终点是位置 $L$。当她处于位置 $x$ 且跳跃能力为 $k$ 时，她可以跳到区间 $[x, x+k]$ 内的任意整数位置。最初，她的跳跃能力为 $1$。

然而，她的冲浪路径并不完全平坦。她的路径上有 $n$ 个障碍物。每个障碍物由一个区间 $[l, r]$ 表示，意味着她不能跳到区间 $[l, r]$ 内的任何位置。

在路径上还有 $m$ 个能量提升点。第 $i$ 个能量提升点位于位置 $x_i$，其值为 $v_i$。当 Mualani 处于位置 $x_i$ 时，她可以选择收集该能量提升点，将她的跳跃能力增加 $v_i$。在同一个位置可能有多个能量提升点。当她处于有多个能量提升点的位置时，她可以选择收集或忽略每个单独的能量提升点。没有能量提升点位于任何障碍物的区间内。

Mualani 必须收集最少的能量提升点数才能到达位置 $L$ 完成冲浪路径。如果无法完成冲浪路径，则输出 $-1$。

## 样例 #1

### 输入

```
4
2 5 50
7 14
30 40
2 2
3 1
3 5
18 2
22 32
4 3 50
4 6
15 18
20 26
34 38
1 2
8 2
10 2
1 4 17
10 14
1 6
1 2
1 2
16 9
1 2 10
5 9
2 3
2 2```

### 输出

```
4
-1
1
2```

# AI分析结果

### 题目翻译
已提供中文题目，无需翻译。

### 综合分析与结论
这些题解的核心思路一致，均采用贪心策略结合优先队列解决问题。对于每个障碍物，优先使用前面遇到的能量提升值大的道具，直到跳跃能力能越过该障碍物。若队列为空且跳跃能力仍不足，则无法完成路径。

### 题解对比
|作者|思路要点|算法要点|难点解决|评分|
| ---- | ---- | ---- | ---- | ---- |
|cqbzhzf|将能量提升点信息存入优先队列，遍历障碍区间，根据位置判断是否使用能量点，用栈暂存后续可用能量点|优先队列、栈|处理能量点的存储和使用顺序|3星|
|WRT_Partisan|对每个障碍，将前面捡到未用的道具从大到小使用，用优先队列记录，记录使用次数|优先队列|判断队列为空且跳跃能力不足的情况|4星|
|_mi_ka_|采用贪心策略，用优先队列存遇到的增强道具，因数轴长进行离散化处理|优先队列、离散化|离散化处理数轴信息|4星|
|SuyctidohanQ|与WRT_Partisan思路相同，对每个障碍从大到小使用未用道具，队列为空且跳跃能力不足则输出 -1|优先队列|判断跳跃能力是否足够|3星|
|ccjjxx|将问题转化为最少获取次数使跳跃能力大于障碍长度，用优先队列，枚举时加入符合条件的加成值|优先队列|判断队列清空后跳跃能力仍不足的情况|3星|
|O_v_O|用优先队列维护药水值，遇到障碍判断跳跃能力，不足则从队列取最大值，全喝仍不足则输出 -1|优先队列|判断能否越过所有障碍|3星|
|Bc2_ChickenDreamer|贪心策略，优先队列存坐标小于当前障碍左端点的能量点，每次更新队列，从大到小加能量值|优先队列|注意多组测试清空队列|3星|

### 所选题解
- **WRT_Partisan（4星）**
    - **关键亮点**：思路清晰，代码简洁，直接实现了贪心策略，通过优先队列高效处理道具使用。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef unsigned long long ull;
struct Node
{
    int l, r;
} a[2000005], b[200005];
int t, n, m, l, x, v, ans, num;
priority_queue<int> q;
signed main()
{
    scanf("%lld", &t);
    while (t--)
    {
        while (!q.empty())
            q.pop();
        ans = 0;
        num = 1;
        scanf("%lld%lld%lld", &n, &m, &l);
        for (int i = 1; i <= n; i++)
            scanf("%lld%lld", &b[i].l, &b[i].r);
        for (int i = 1; i <= m; i++)
            scanf("%lld%lld", &a[i].l, &a[i].r);
        int it = 1;
        bool temp = 1;
        for (int i = 1; i <= n; i++)
        {
            while (it <= m && a[it].l < b[i].l)
                q.push(a[it].r), ++it;
            while (num <= b[i].r - b[i].l + 1)
            {
                if (q.empty())
                {
                    temp = 0;
                    break;
                }
                num += q.top();
                q.pop();
                ans++;
            }
            if (temp == 0)
                break;
        }
        if (temp == 0)
            printf("-1\n");
        else
            printf("%lld\n", ans);
    }
    return 0;
}
```
    - **核心思想**：每次遇到障碍前，将位置小于障碍左端点的道具加入优先队列，然后从队列中取最大值增加跳跃能力，直到能越过障碍，若队列为空仍不足则无法完成。

- **_mi_ka_（4星）**
    - **关键亮点**：考虑到数轴长度问题，使用离散化处理，使算法更具通用性。
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<map>
#include<queue>
#include<vector>
#define N 400005
using namespace std;
int T,n,m,L,cnt;
struct obs
{
	int l,r,len;
}o[N];
struct tols
{
	int x,v;
}t[N];
int bok[N],bl[N];
priority_queue<int>q;
signed main()
{
	T=re();
	while(T--)
	{
		n=re(),m=re(),L=re();
		cnt=0;
		for(int i=1;i<=n;i++)
		{
			o[i].l=re(),o[i].r=re();
			o[i].len=o[i].r-o[i].l+1;
			bok[++cnt]=o[i].l;
		}
		for(int i=1;i<=m;i++)
		{
			t[i].x=re(),t[i].v=re();
			bok[++cnt]=t[i].x;
		}
		sort(bok+1,bok+cnt+1);
		int boks=unique(bok+1,bok+cnt+1)-bok-1;
		for(int i=1;i<=n;i++)
			o[i].l=lower_bound(bok+1,bok+boks+1,o[i].l)-bok;
		for(int i=1;i<=m;i++)
			t[i].x=lower_bound(bok+1,bok+boks+1,t[i].x)-bok;
		int nowo=0,nowt=0,ans=0,nowv=1,flag=0;
		for(int i=1;i<=boks;i++)
		{
			while(i==t[nowt+1].x&&nowt<m)
			{
				nowt++;
				q.push(t[nowt].v);
			}
			if(i==o[nowo+1].l&&nowo<n)
			{
				nowo++;
				int bas=o[nowo].len;
				while(q.size()!=0&&nowv<=bas)
				{
					nowv+=q.top();
					q.pop(),ans++;
				}
				if(!q.size()&&nowv<=bas)
				{
					puts("-1");
					flag=1;
					break;
				}
			}
		}
		while(q.size())
			q.pop();
		if(!flag)
			wr(ans),putchar('\n');
	}
	return 0;
}
```
    - **核心思想**：先对障碍物左端点和道具位置进行离散化，然后遍历离散化后的位置，遇到道具加入优先队列，遇到障碍从队列取最大值增加跳跃能力，若队列为空仍不足则无法完成。

### 最优关键思路或技巧
- **贪心策略**：优先使用能量提升值大的道具，可使使用道具次数最少。
- **优先队列**：高效存储和获取能量提升值大的道具。
- **离散化**：处理数轴长度过长问题，减少不必要的计算。

### 拓展思路
同类型题目可能会有更多限制条件，如增加跳跃次数限制、道具使用有额外规则等。解题时仍可考虑贪心策略结合合适的数据结构，根据具体条件调整算法。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：考察贪心策略和优先队列的使用。
2. [P2121 拆地毯](https://www.luogu.com.cn/problem/P2121)：涉及贪心和排序思想。
3. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：经典贪心问题，可锻炼贪心思维。

### 个人心得摘录与总结
- **Bc2_ChickenDreamer**：将清空队列写成了 `pq.empty()`，导致调试时间过长。总结：多组测试数据时，要确保队列等数据结构正确清空，避免因小错误浪费大量时间。 

---
处理用时：47.17秒