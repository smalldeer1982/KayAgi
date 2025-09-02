# 题目信息

# Special Permutation

## 题目描述

A permutation of length $ n $ is an array $ p=[p_1,p_2,\dots, p_n] $ which contains every integer from $ 1 $ to $ n $ (inclusive) exactly once. For example, $ p=[4, 2, 6, 5, 3, 1] $ is a permutation of length $ 6 $ .

You are given three integers $ n $ , $ a $ and $ b $ , where $ n $ is an even number. Print any permutation of length $ n $ that the minimum among all its elements of the left half equals $ a $ and the maximum among all its elements of the right half equals $ b $ . Print -1 if no such permutation exists.

## 样例 #1

### 输入

```
7
6 2 5
6 1 3
6 4 3
4 2 4
10 5 3
2 1 2
2 2 1```

### 输出

```
4 2 6 5 3 1
-1
6 4 5 1 3 2 
3 2 4 1 
-1
1 2 
2 1```

# AI分析结果

### 题目中文重写
## 特殊排列

### 题目描述
长度为 $n$ 的排列是一个数组 $p = [p_1, p_2, \cdots, p_n]$，它包含从 $1$ 到 $n$（包含 $1$ 和 $n$）的每个整数恰好一次。例如，$p = [4, 2, 6, 5, 3, 1]$ 是一个长度为 $6$ 的排列。

给定三个整数 $n$、$a$ 和 $b$，其中 $n$ 是偶数。请输出任意一个长度为 $n$ 的排列，使得其左半部分所有元素中的最小值等于 $a$，右半部分所有元素中的最大值等于 $b$。如果不存在这样的排列，则输出 -1。

### 样例 #1
#### 输入
```
7
6 2 5
6 1 3
6 4 3
4 2 4
10 5 3
2 1 2
2 2 1
```

#### 输出
```
4 2 6 5 3 1
-1
6 4 5 1 3 2 
3 2 4 1 
-1
1 2 
2 1
```

### 综合分析与结论
这些题解的核心思路都是构造一个长度为 $n$ 的排列，使前半部分最小值为 $a$，后半部分最大值为 $b$。

#### 思路对比
- **倒序填充法**：大部分题解（Jur_Cai、Coros_Trusds、Terraria、miao5）采用先将 $a$ 放入前半段，$b$ 放入后半段，再从大到小倒序填充剩余位置，最后检查是否满足条件。
- **分类填充法**：Aiopr_2378 在前半段找未使用的最大数，后半段找未使用的最小数；BFSDFS123 和 DaiRuiChen007 将小于 $a$ 的数放后半段，大于 $b$ 的数放前半段，再处理区间 $(a, b)$ 的数。
- **贪心填充法**：断清秋从 $a + 1$ 开始填充前半段，从 $b - 1$ 开始填充后半段。

#### 算法要点
- **初始化**：将 $a$ 放入前半段，$b$ 放入后半段。
- **填充剩余位置**：根据不同思路填充剩余位置，注意避免重复使用数字。
- **检查条件**：检查前半段最小值是否为 $a$，后半段最大值是否为 $b$。

#### 解决难点
- **数字重复问题**：使用标记数组或在填充时跳过已使用的数字。
- **无解判断**：通过检查填充后的数组是否满足条件或部分是否填满来判断无解。

### 评分较高的题解
- **Jur_Cai（5星）**
    - **关键亮点**：思路清晰，代码简洁，直接实现了倒序填充的思路，且注释说明可以 $O(1)$ 判断，有一定扩展性。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int ans[105];
int main() {
    int T;
    scanf("%d",&T);
    while(T--) {
        int n,a,b;
        scanf("%d%d%d",&n,&a,&b);
        int now=n,minn=a,maxn=b;
        ans[1]=a;
        for(int i=2; i<=n/2; i++) {
            while(now==a||now==b) now--;
            ans[i]=now,minn=min(minn,ans[i]),now--;
        }
        ans[n/2+1]=b;
        for(int i=n/2+2; i<=n; i++) {
            while(now==a||now==b) now--;
            ans[i]=now,maxn=max(maxn,ans[i]),now--;
        }
        if(minn!=a||maxn!=b) puts("-1");
        else {
            for(int i=1; i<=n; i++) cout<<ans[i]<<" ";
            cout<<'\n';
        }
    }
}
```
核心实现思想：先将 $a$ 放入前半段第一个位置，$b$ 放入后半段第一个位置，然后从大到小依次填充剩余位置，跳过 $a$ 和 $b$，最后检查前半段最小值和后半段最大值是否符合要求。

- **DaiRuiChen007（4星）**
    - **关键亮点**：思路清晰，对数字进行分类处理，代码逻辑严谨，有详细的注释说明。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
vector <int> fnt,bck;
bool vis[101];
inline void solve(int n,int a,int b) {
    int m=n>>1;
    memset(vis,false,sizeof(vis));
    fnt.clear();
    bck.clear();
    fnt.push_back(a);
    bck.push_back(b);
    vis[a]=vis[b]=true;
    for(register int i=1;bck.size()<m&&i<a;++i) {
        bck.push_back(i);
        if(vis[i]) {
            puts("-1");
            return ;
        }
        vis[i]=true;
    }
    for(register int i=n;fnt.size()<m&&i>b;--i) {
        fnt.push_back(i);
        if(vis[i]) {
            puts("-1");
            return ;
        }
        vis[i]=true;
    }
    for(register int i=a+1;fnt.size()<m;++i) {
        fnt.push_back(i);
        if(vis[i]) {
            puts("-1");
            return ;
        }
        vis[i]=true;
    }
    for(register int i=b-1;bck.size()<m;--i) {
        bck.push_back(i);
        if(vis[i]) {
            puts("-1");
            return ;
        }
        vis[i]=true;
    }
    if(fnt.size()!=m||bck.size()!=m) {
        puts("-1");
        return ;
    }
    for(register auto i:fnt) printf("%d ",i);
    for(register auto i:bck) printf("%d ",i);
    putchar('\n');
    return ;
}
int main() {
    int t;
    scanf("%d",&t);
    while(t--) {
        int n,a,b;
        scanf("%d%d%d",&n,&a,&b);
        solve(n,a,b);
    }
    return 0;
}
```
核心实现思想：将小于 $a$ 的数放入后半段，大于 $b$ 的数放入前半段，再将区间 $(a, b)$ 中较小的数放入前半段，较大的数放入后半段，过程中使用标记数组避免重复，最后检查前后半段长度是否符合要求。

### 最优关键思路或技巧
- **倒序填充**：从大到小填充剩余位置，可使前半段尽量大，后半段尽量小，满足最小值和最大值的要求。
- **标记数组**：使用标记数组记录数字是否被使用，避免重复使用数字。

### 拓展思路
同类型题可考虑构造满足特定条件的排列或序列，如构造满足特定和、积、中位数等条件的排列。类似算法套路可采用贪心、分类讨论等思想，先确定特殊元素的位置，再填充剩余位置。

### 洛谷相似题目推荐
- P1088 [火星人](https://www.luogu.com.cn/problem/P1088)：考察排列的生成与变换。
- P1138 第 k 小整数：涉及对序列的排序和筛选。
- P1240 诸侯安置：需要构造满足特定条件的排列。

### 个人心得摘录与总结
暂无题解包含个人心得。

---
处理用时：43.80秒