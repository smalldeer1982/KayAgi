# 题目信息

# Increasing Frequency

## 题目描述

给你一个长度为 $n$ 的数列 $a$ ,你可以任意选择一个区间 $[l,r]$, 并给区间每个数加上一个整数 $k$, 求这样一次操作后数列中最多有多少个数等于 $c$.

## 样例 #1

### 输入

```
6 9
9 9 9 9 9 9
```

### 输出

```
6
```

## 样例 #2

### 输入

```
3 2
6 2 6
```

### 输出

```
2
```

# AI分析结果

### 题目内容
# 递增频率

## 题目描述
给你一个长度为 $n$ 的数列 $a$ ，你可以任意选择一个区间 $[l,r]$ ，并给区间每个数加上一个整数 $k$ ，求这样一次操作后数列中最多有多少个数等于 $c$ 。

## 样例 #1
### 输入
```
6 9
9 9 9 9 9 9
```
### 输出
```
6
```

## 样例 #2
### 输入
```
3 2
6 2 6
```
### 输出
```
2
```

### 算法分类
前缀和

### 题解综合分析与结论
这些题解主要围绕如何通过不同方式找到合适区间，使操作后等于 $c$ 的数字最多。部分题解利用前缀和维护数字出现次数，进而计算区间内数字与 $c$ 出现次数的差值来求解；部分题解通过贪心策略，考虑以当前数为赋值基准下的最大贡献；还有题解使用分治或动态规划思想解决问题。不同题解在思路清晰度、代码可读性和优化程度上存在差异。

### 所选的题解
- **作者：redegg (5星)**
    - **关键亮点**：思路清晰，利用前缀和巧妙转化问题，将二维前缀和数组优化为一维数组，降低空间复杂度，代码简洁明了。
    - **核心代码片段**：
```cpp
#include <bits/stdc++.h>
using namespace std;

int n,c;
int a[600005];
int minn[600005];
int sum[600005];
int ans[600005];

int main()
{
    scanf("%d%d",&n,&c);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }

    for(int i=1;i<=n;i++)
    {
        minn[a[i]]=min(sum[a[i]]-sum[c],minn[a[i]]);
        sum[a[i]]++;
        ans[i]=max(ans[i],sum[a[i]]-sum[c]-minn[a[i]]);
    }
    int maxn=sum[c];
    for(int i=1;i<=n;i++)
    {
        maxn=max(maxn,ans[i]+sum[c]);
    }
    printf("%d\n",maxn);
    return 0;
}
```
    - **核心实现思想**：通过前缀和数组 `sum` 记录数字出现次数，`minn` 数组记录数字与 $c$ 个数差值的最小值，遍历数组更新 `minn` 和 `ans`，最后得出答案。
- **作者：Sakura_梦瑶 (4星)**
    - **关键亮点**：采用贪心策略，考虑以当前数为赋值基准下的最大贡献，通过辅助数组作差简化计算。
    - **核心代码片段**：
```cpp
#include<bits/stdc++.h>
#define N 1<<22
using namespace std;
int n,m,c,t,cnt,ans,a[N],b[N];
int main(){
	cin>>n>>m;for(int i=1;i<=n;i++){scanf("%d",&c);if(c==m)cnt++;
		else if(c!=m){
			if(a[c]&&a[c]+b[c]-cnt>=0)a[c]+=b[c]-cnt;
			else a[c]=0;b[c]=cnt,a[c]++;ans=max(ans,a[c]);
		} 
	}cout<<ans+cnt;
}
```
    - **核心实现思想**：遍历数组，若当前数为 $m$ 则 $cnt$ 加一，否则更新辅助数组 `a` 和 `b`，记录最大贡献值 `ans`，最后输出答案。
- **作者：sinsop90 (4星)**
    - **关键亮点**：清晰阐述将原问题转换为找区间内出现次数最多的数字与 $c$ 的个数差最大的问题，利用前缀和求解，代码简洁易懂。
    - **核心代码片段**：
```cpp
#include <bits/stdc++.h>
#define maxn 500005
using namespace std;
int n, a[maxn], m, minn[maxn], pre[maxn], ans[maxn], ansn = -1;
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1;i <= n;i++) minn[i] = 2147483647;
	for(int i = 1;i <= n;i++) scanf("%d", &a[i]);
	for(int i = 1;i <= n;i++) {
		minn[a[i]] = min(pre[a[i]] - pre[m], minn[a[i]]);
		pre[a[i]] ++;
		ans[i] = max(ans[i], pre[a[i]] - pre[m] - minn[a[i]]);
	}
	for(int i = 1;i <= n;i++) ansn = max(ansn, ans[i] + pre[m]);
	printf("%d\n", ansn);
}
```
    - **核心实现思想**：利用前缀和数组 `pre` 记录数字出现次数，`minn` 数组记录差值最小值，遍历更新 `minn` 和 `ans`，最后得到答案。

### 最优关键思路或技巧
将原问题转化为寻找区间内某数字与 $c$ 出现次数差最大的问题，通过前缀和维护数字出现次数，利用一维数组记录关键信息，降低空间复杂度，同时结合贪心思想简化计算过程。

### 同类型题或类似算法套路拓展
同类型题常围绕数组区间操作及元素统计，类似算法套路包括利用前缀和、后缀和快速计算区间信息，通过贪心策略选取最优区间，或使用动态规划解决子问题。

### 洛谷相似知识点题目推荐
- [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)
- [P3397 地毯](https://www.luogu.com.cn/problem/P3397)
- [P2004 领地选择](https://www.luogu.com.cn/problem/P2004) 

---
处理用时：53.89秒