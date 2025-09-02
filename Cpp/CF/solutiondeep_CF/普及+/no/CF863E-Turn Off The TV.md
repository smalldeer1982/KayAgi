# 题目信息

# Turn Off The TV

## 题目描述

Luba 有 $n$ 台电视，并且她知道每台电视的工作时间是从 $l$ 到 $r$。现在 Luba 想要关掉一些电视，使得播放电视节目的时间点不少于关掉这些电视之前。请你帮助 Luba，告诉她可以关闭哪些电视，若任何一台都不能关闭，输出 `-1`。

## 样例 #1

### 输入

```
3
1 3
4 6
1 7
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2
0 10
0 10
```

### 输出

```
1
```

## 样例 #3

### 输入

```
3
1 2
3 4
6 8
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
3
1 2
2 3
3 4
```

### 输出

```
2
```

# AI分析结果

### 题目内容
# 关掉电视

## 题目描述
Luba有 $n$ 台电视，并且她知道每台电视的工作时间是从 $l$ 到 $r$。现在Luba想要关掉一些电视，使得播放电视节目的时间点不少于关掉这些电视之前。请你帮助Luba，告诉她可以关闭哪些电视，若任何一台都不能关闭，输出 `-1`。

## 样例 #1
### 输入
```
3
1 3
4 6
1 7
```
### 输出
```
1
```

## 样例 #2
### 输入
```
2
0 10
0 10
```
### 输出
```
1
```

## 样例 #3
### 输入
```
3
1 2
3 4
6 8
```
### 输出
```
-1
```

## 样例 #4
### 输入
```
3
1 2
2 3
3 4
```
### 输出
```
2
```

### 算法分类
离散化

### 综合分析与结论
这些题解主要围绕判断哪条线段（对应电视工作区间）能被其他线段的并集覆盖展开。核心思路多是通过离散化处理线段端点，再利用不同的数据结构或方法统计各位置被覆盖次数，判断某线段内所有位置被覆盖次数是否至少为2。各题解的区别主要在于实现统计和查询的具体方式。

### 所选的题解
- **作者：_edge_ (5星)**
    - **关键亮点**：思路清晰，先提出多种数据结构解法，后重点阐述差分优化思路，详细说明了离散化处理细节及数组维护方式，代码实现简洁明了。
    - **个人心得**：提到离散化时要将数值全部加一，避免区间计算错误。
    - **重点代码**：
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int INF=1e6+5;
int n,l[INF],r[INF],cnt[INF],d[INF],ll[INF];
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for (int i=1;i<=n;i++) {
		cin>>l[i]>>r[i];
		cnt[++cnt[0]]=l[i];
		cnt[++cnt[0]]=r[i];
	}
	sort(cnt+1,cnt+1+cnt[0]);
	int res=unique(cnt+1,cnt+1+cnt[0])-cnt-1;
	for (int i=2;i<=cnt[0];i++)
		if (cnt[i]!=cnt[i-1]) cnt[++res]=cnt[i-1]+1;
	sort(cnt+1,cnt+1+res);
	res=unique(cnt+1,cnt+1+res)-cnt-1;
	for (int i=1;i<=n;i++) {
		l[i]=lower_bound(cnt+1,cnt+1+res,l[i])-cnt;
		r[i]=lower_bound(cnt+1,cnt+1+res,r[i])-cnt;
		d[l[i]]++;d[r[i]+1]--;
	}
	for (int i=1;i<=res;i++) {
		d[i]+=d[i-1];
		if (d[i]>=2 && d[i-1]>=2) ll[i]=ll[i-1];
		else ll[i]=i;
	}
	for (int i=1;i<=n;i++) {
		if (ll[r[i]]<=l[i]) {
			if (l[i]==r[i] && d[l[i]]<2) continue;
			cout<<i<<"\n";
			return 0;
		}
	}
	cout<<"-1\n";
	return 0;
}
```
核心实现思想：先离散化线段端点，对每个线段进行差分操作，再通过前缀和得到各点覆盖次数，同时维护一个数组记录从某点向右延伸满足覆盖次数至少为2的最大范围，最后遍历判断每条线段是否满足可删除条件。

- **作者：Flanksy (4星)**
    - **关键亮点**：利用离散化和差分统计位置覆盖次数，使用ST表解决静态区间最小值问题，代码简洁高效，对离散化处理的关键细节有清晰说明。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,cnt,l[200001],r[200001],p[600001],lo[600001],s[23][600005];
inline int min(int x,int y){return x<y?x:y;}
int query(int l,int r){
    int o=lo[r-l+1];
    return min(s[o][l],s[o][r-(1<<o)+1]);
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&l[i],&r[i]);
        p[++cnt]=l[i],p[++cnt]=r[i];
        p[++cnt]=r[i]+1;
    }
    sort(p+1,p+cnt+1);
    cnt=unique(p+1,p+cnt+1)-p-1;
    for(int i=1;i<=n;i++){
        l[i]=lower_bound(p+1,p+cnt+1,l[i])-p;
        r[i]=lower_bound(p+1,p+cnt+1,r[i])-p;
        s[0][l[i]]++,s[0][r[i]+1]--;
    }
    for(int i=1;i<=cnt;i++) s[0][i]+=s[0][i-1];
    for(int i=1;1<<i<=cnt;i++)
        for(int j=1;j+(1<<i)-1<=cnt;j++)
            s[i][j]=min(s[i-1][j],s[i-1][j+(1<<i-1)]);
    for(int i=2;i<=cnt;i++) lo[i]=lo[i>>1]+1;
    for(int i=1;i<=n;i++) if(query(l[i],r[i])>=2)
        return printf("%d\n",i),0;
    puts("-1");
    return 0;
}
```
核心实现思想：离散化线段端点并加入 $r_i + 1$ 处理差分影响，通过差分和前缀和得到各点覆盖次数，构建ST表快速查询区间最小值，判断每条线段是否可删除。

### 最优关键思路或技巧
离散化处理较大值域的线段端点，结合差分统计各位置覆盖次数，再利用合适的数据结构（如线段树、ST表等）高效查询区间最小值，判断线段是否能被其他线段覆盖。

### 可拓展之处
此类题目属于线段覆盖相关问题，类似套路包括利用扫描线、线段树等处理区间问题。常见拓展方向有动态区间修改、多维度区间覆盖等。

### 洛谷相似题目
- [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)
- [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)
- [P3802 小魔女帕琪](https://www.luogu.com.cn/problem/P3802)

---
处理用时：55.81秒