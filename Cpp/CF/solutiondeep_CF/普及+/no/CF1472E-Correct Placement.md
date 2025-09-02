# 题目信息

# Correct Placement

## 题目描述

Polycarp has invited $ n $ friends to celebrate the New Year. During the celebration, he decided to take a group photo of all his friends. Each friend can stand or lie on the side.

Each friend is characterized by two values $ h_i $ (their height) and $ w_i $ (their width). On the photo the $ i $ -th friend will occupy a rectangle $ h_i \times w_i $ (if they are standing) or $ w_i \times h_i $ (if they are lying on the side).

The $ j $ -th friend can be placed in front of the $ i $ -th friend on the photo if his rectangle is lower and narrower than the rectangle of the $ i $ -th friend. Formally, at least one of the following conditions must be fulfilled:

- $ h_j < h_i $ and $ w_j < w_i $ (both friends are standing or both are lying);
- $ w_j < h_i $ and $ h_j < w_i $ (one of the friends is standing and the other is lying).

For example, if $ n = 3 $ , $ h=[3,5,3] $ and $ w=[4,4,3] $ , then:

- the first friend can be placed in front of the second: $ w_1 < h_2 $ and $ h_1 < w_2 $ (one of the them is standing and the other one is lying);
- the third friend can be placed in front of the second: $ h_3 < h_2 $ and $ w_3 < w_2 $ (both friends are standing or both are lying).

In other cases, the person in the foreground will overlap the person in the background.

Help Polycarp for each $ i $ find any $ j $ , such that the $ j $ -th friend can be located in front of the $ i $ -th friend (i.e. at least one of the conditions above is fulfilled).

Please note that you do not need to find the arrangement of all people for a group photo. You just need to find for each friend $ i $ any other friend $ j $ who can be located in front of him. Think about it as you need to solve $ n $ separate independent subproblems.

## 说明/提示

The first test case is described in the statement.

In the third test case, the following answers are also correct:

- $ [-1, -1, 1, 2] $ ;
- $ [-1, -1, 1, 1] $ ;
- $ [-1, -1, 2, 1] $ .

## 样例 #1

### 输入

```
4
3
3 4
5 4
3 3
3
1 3
2 2
3 1
4
2 2
3 1
6 3
5 4
4
2 2
2 3
1 1
4 4```

### 输出

```
-1 3 -1 
-1 -1 -1 
-1 -1 2 2 
3 3 -1 3```

# AI分析结果

### 题目中文重写
#### 正确站位

##### 题目描述
Polycarp 邀请了 $n$ 个朋友来庆祝新年。在庆祝活动中，他决定给所有朋友拍一张合影。每个朋友可以站着或侧躺。

每个朋友由两个值 $h_i$（他们的身高）和 $w_i$（他们的宽度）来描述。在照片中，第 $i$ 个朋友将占据一个 $h_i \times w_i$ 的矩形（如果他们站着）或 $w_i \times h_i$ 的矩形（如果他们侧躺）。

如果第 $j$ 个朋友的矩形比第 $i$ 个朋友的矩形更矮且更窄，那么第 $j$ 个朋友可以站在第 $i$ 个朋友前面拍照。正式地，必须满足以下至少一个条件：
- $h_j < h_i$ 且 $w_j < w_i$（两个朋友都站着或都侧躺）；
- $w_j < h_i$ 且 $h_j < w_i$（其中一个朋友站着，另一个朋友侧躺）。

例如，如果 $n = 3$，$h=[3,5,3]$ 且 $w=[4,4,3]$，那么：
- 第一个朋友可以站在第二个朋友前面：$w_1 < h_2$ 且 $h_1 < w_2$（其中一个站着，另一个侧躺）；
- 第三个朋友可以站在第二个朋友前面：$h_3 < h_2$ 且 $w_3 < w_2$（两个朋友都站着或都侧躺）。

在其他情况下，前景中的人会遮挡背景中的人。

帮助 Polycarp 为每个 $i$ 找到任意一个 $j$，使得第 $j$ 个朋友可以站在第 $i$ 个朋友前面（即满足上述至少一个条件）。

请注意，你不需要为合影找到所有人的站位安排。你只需要为每个朋友 $i$ 找到任何一个可以站在他前面的其他朋友 $j$。可以将其视为你需要解决 $n$ 个独立的子问题。

##### 说明/提示
第一个测试用例在题目描述中给出。

在第三个测试用例中，以下答案也是正确的：
- $[-1, -1, 1, 2]$；
- $[-1, -1, 1, 1]$；
- $[-1, -1, 2, 1]$。

##### 样例 #1
###### 输入
```
4
3
3 4
5 4
3 3
3
1 3
2 2
3 1
4
2 2
3 1
6 3
5 4
4
2 2
2 3
1 1
4 4
```
###### 输出
```
-1 3 -1 
-1 -1 -1 
-1 -1 2 2 
3 3 -1 3
```

### 算法分类
排序

### 综合分析与结论
这些题解的核心思路都是先对数据进行排序，再利用贪心策略解决问题。不同题解在排序方式、数据处理和贪心实现细节上有所差异。大部分题解会先将每个人的身高和宽度调整为 $h \leq w$ 的形式，然后按照身高或长（较大值）进行排序，在排序后维护一个最小宽度的人，判断其是否能站在当前人前面。

### 所选题解
- **胖头鱼学员（5星）**
    - **关键亮点**：思路清晰，代码简洁，通过排序和贪心的方式高效解决问题。
    - **核心代码**：
```cpp
#include <algorithm>
#include <iostream>

using namespace std;

const int kMaxN = 2e5 + 1;

struct E {
  int h, w, p;
} e[kMaxN];
int l[kMaxN];

int t, n, p;

int main() {
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> e[i].h >> e[i].w;
      if (e[i].h > e[i].w) {
        swap(e[i].h, e[i].w);
      }
      l[i] = i;
    }
    sort(l + 1, l + 1 + n, [](int i, int j) { return e[i].h < e[j].h || (e[i].h == e[j].h && e[i].w > e[j].w); });
    p = l[1];
    for (int i = 1; i <= n; i++) {
      if (e[l[i]].w > e[p].w) {
        e[l[i]].p = p;
      } else {
        e[l[i]].p = -1;
        p = l[i];
      }
    }
    for (int i = 1; i <= n; i++) {
      cout << e[i].p << " ";
    }
    cout << endl;
  }
  return 0;
}
```
    - **核心实现思想**：先将每个人的身高和宽度调整为 $h \leq w$，然后按照身高排序，身高相同时按宽度降序排列。遍历排序后的数组，维护一个最小宽度的人 $p$，如果当前人的宽度大于 $p$ 的宽度，则 $p$ 可以站在当前人前面，否则更新 $p$ 为当前人。

- **二gou子（4星）**
    - **关键亮点**：思路明确，详细解释了如何维护最小值来找到符合条件的人。
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<algorithm>
#include<cstring>
#include<set>
#include<queue>
using namespace std;
const int N=200005,INF=2147483647;
int T,n,numm,maxn,minx;
int ans[N];
struct People{
	int maxx,minn,num;
}peo[N];
bool cmp(People a,People b){
	return a.maxx<b.maxx;
}
bool cmp2(People a,People b){
	return a.num<b.num;
}
int main()
{
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			ans[i]=-1;
		}
		for(int i=1,a,b;i<=n;i++){
			scanf("%d%d",&a,&b);
			peo[i].maxx=max(a,b);
			peo[i].minn=min(a,b);
			peo[i].num=i;
		}
		sort(peo+1,peo+1+n,cmp);
		minx=INF;
		for(int i=1,t=i+1;i<=n;i=t){
			while(peo[i].maxx==peo[t].maxx&&t<=n) t++;
			for(int j=i;j<=t-1;j++){		
				if(peo[j].minn>minx){
					ans[peo[j].num]=numm;
				}
			}
			for(int j=i;j<=t-1;j++){
				if(peo[j].minn<minx){
					minx=peo[j].minn;
					numm=peo[j].num;
				}
			}
		}
		sort(peo+1,peo+1+n,cmp2);
		for(int i=1;i<=n;i++){
			printf("%d ",ans[i]);
		}
		printf("\n");
	}
	return 0;
}
```
    - **核心实现思想**：将每个人的最大和最小值存到结构体中，按最大值排序。遍历排序后的数组，先处理最大值相等的人，在这些人中判断是否有符合条件的人，然后更新最小的最小值。最后按编号排序输出结果。

- **洛璟（4星）**
    - **关键亮点**：详细解释了优化过程，通过维护最小数来减少比较次数。
    - **核心代码**：
```cpp
#include<bits/stdc++.h> 
using namespace std;
int ans[1919810];
struct cccp
{
    int h, w;
}a[1919810];
int t, n;
inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = (x << 3) + (x << 1) + (c ^ '0');
        c = getchar();
    }
    return x * f;
}
bool cmp(cccp a, cccp b)
{
    return a.h < b.h;
}
int main()
{
    t = read();
    while (t--)
    {
        n = read();
        vector<cccp> v(n);
        for (int i = 0;i < n;i++)
        {
            ans[i] = -2;
            a[i].h = read();
            a[i].w = read();
            if (a[i].h > a[i].w) swap(a[i].h, a[i].w);
            v[i] = cccp{ a[i].h,i };
        }
        sort(v.begin(), v.end(), cmp);
        int j = 0, qwq = -1;
        for (int i = 0;i < n;i++)
        {
            int nw = v[i].w;
            while (a[nw].h > v[j].h)
            {
                if (qwq == -1 || a[qwq].w > a[v[j].w].w) qwq = v[j].w;
                j++;
            }
            if (qwq != -1 && a[nw].w > a[qwq].w) ans[nw] = qwq;
        }
        for (int i = 0;i < n;i++)
        {
            printf("%d ", ans[i] + 1);
        }
        printf("\n");
    }
    return 0;
}
```
    - **核心实现思想**：将每个人的身高和宽度调整为 $h \leq w$，按身高排序。遍历排序后的数组，找出当前人之前的最小宽度的人，判断其是否能站在当前人前面。

### 最优关键思路或技巧
- 先将每个人的身高和宽度调整为 $h \leq w$ 的形式，简化比较条件。
- 按照身高或长（较大值）进行排序，使得在遍历过程中可以利用排序的性质，减少不必要的比较。
- 维护一个最小宽度的人，通过比较当前人的宽度和最小宽度的人的宽度，判断是否有符合条件的人。

### 拓展思路
同类型题或类似算法套路：
- 二维偏序问题：给定多个二维点，求每个点在某个偏序关系下的前驱或后继。
- 区间覆盖问题：给定多个区间，求每个区间是否能被其他区间完全覆盖。

### 推荐洛谷题目
- P1963 [NOI2009] 变换序列
- P2824 [HEOI2016/TJOI2016] 排序
- P1090 [NOIP2004 提高组] 合并果子

### 个人心得摘录与总结
- **洛璟**：提到一开始想到的 $O(N^2)$ 暴力比较方法会超时，后来想到先排序再维护另一个关键字，但最粗暴的比较还是 $O(N^2)$，最后通过优化比较过程，找出在当前数之前的尽可能小的数并不断更新最小数来解决问题。总结就是遇到复杂的比较问题，可以先尝试排序，再通过维护关键信息来优化比较过程。

---
处理用时：78.88秒