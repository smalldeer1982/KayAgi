# 题目信息

# Bash's Big Day

## 题目描述

Bash 已经踏上了成为最伟大的口袋妖怪大师的旅程。为了得到他的第一个口袋妖怪，他去了 Zulu 教授的实验室。由于 Bash 是 Zulu 教授最喜欢的学生，Zulu 允许他从实验室里取出任意数量的口袋妖怪。

但是 Zulu 警告他，每个小精灵都有一个力量值，例如 $k(k>1)$ 个小精灵在一起，它们的力量值为 $s_1,s_2,\dots,s_k$，如果 $\gcd(s_1,s_2,\dots s_k)=1$（见 $\gcd$ 的定义注释），它们之间就会互相打架。

Bash 作为一个聪明的人，不希望他的口袋妖怪互相斗争。然而，他也想最大化他从实验室里带走的神奇宝贝的数量。你能帮 Bash 找出他能带走的最大数量的口袋妖怪吗？

**注意：口袋妖怪不能与自己战斗。**

## 样例 #1

### 输入

```
3
2 3 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
2 3 4 6 7
```

### 输出

```
3
```

# AI分析结果

### 综合分析与结论
这些题解的核心思路都是找出能整除多个数的因数，统计每个因数能整除的数的个数，然后找出个数最多的因数对应的数量作为答案。

- **思路对比**：
    - 部分题解采用枚举所有因数的方式，如 Cutest_Junior、18lxxrz、Timon080923、fls233666 等，通过遍历每个数的因数并统计其出现次数。
    - 部分题解则是枚举质数，如李尧、andyli、RemiliaScar1et、BotDand 等，认为质数中一定有最优解，合数一定不比质数更优。
    - 0x3F 则是先尝试枚举所有数，再尝试枚举质数，最后采用统计每个数的素因子的方式。
- **算法要点**：
    - 枚举因数时，通常采用 $O(\sqrt{n})$ 的时间复杂度来找出一个数的所有因数。
    - 枚举质数时，可能会用到线性筛来找出一定范围内的质数。
- **解决难点**：
    - 处理重复战斗值，不能简单使用 bool 型数组。
    - 注意至少有一个数的情况，答案初始值应设为 1。

### 所选题解
- **Cutest_Junior（4星）**
    - **关键亮点**：思路清晰，详细阐述了从暴力枚举到优化的过程，代码简洁易懂。
    - **个人心得**：无
- **李尧（4星）**
    - **关键亮点**：明确指出了两个容易出错的点，对新手友好。
    - **个人心得**：注意 1. 可能有重复战斗值，不能用 bool 型（否则会一直卡第三个点）；2. 至少有一个数，也就是 mx 初始 1 而非 0（否则会一直卡第十二个点）。
- **RemiliaScar1et（4星）**
    - **关键亮点**：给出了质数中一定有最优解，合数一定不比质数更优的不严谨证明，有一定的理论依据。
    - **个人心得**：无

### 重点代码
#### Cutest_Junior
```cpp
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1e5 + 5;
int cou[N];

int main() {
    int n;
    scanf("%d", &n);
    
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        
        for (int j = 1; j * j<= x; ++j) {
            if (x % j == 0) {
                ++cou[j];
                if (j * j != x) {
                    ++cou[x / j];
                }
            }
        }
    }
    
    int ans = 1;
    for (int i = 2; i < N; ++i) {
        ans = max(ans, cou[i]);
    }
    
    printf("%d", ans);
}
```
**核心实现思想**：用桶数组 `cou` 记录每个因数出现的次数，遍历每个数的因数并更新桶数组，最后找出桶数组中最大的值（从 2 开始）。

#### 李尧
```cpp
#include <bits/stdc++.h>
using namespace std;
int a,ans,mx=1,n,vis[100007];
bool v[100007];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a);
        vis[a]++;
    }
    for(int i=2;i<=100000;i++){
        if(v[i]) continue;
        ans=vis[i];
        for(int j=2;j<=100000/i;j++){
            v[i*j]=true;
            ans+=vis[i*j];
        }
        mx=max(mx,ans);
    }
    printf("%d",mx);
    return 0;
}
```
**核心实现思想**：先统计每个数出现的次数，然后枚举每个数，若该数未被标记，则统计其倍数出现的次数，更新最大值。

#### RemiliaScar1et
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=1e5+10;

int pr[N],tot=0;
bool mp[N];

void init(int n)
{
    for(int i=2;i<=n;i++)
    {
        if(!mp[i]) pr[++tot]=i;
        for(int j=1;i*pr[j]<=n;j++)
        {
            mp[pr[j]*i]=1;
            if(i%pr[j]==0) break;
        }
    }
}
int n;
int arr[N],vis[N];

int main()
{
    scanf("%d",&n);
    int maxn=0;
    for(int i=1;i<=n;i++)
        scanf("%d",&arr[i]),maxn=max(maxn,arr[i]),vis[arr[i]]++;
    init((int)maxn+1);
    int ans=1;
    for(int i=1;i<=tot;i++)
    {
        int res=0;
        for(int j=1;pr[i]*j<=maxn;j++)
            res+=vis[pr[i]*j];
        ans=max(ans,res);
    }
    printf("%d",ans);
    return 0;
}
```
**核心实现思想**：先线性筛出一定范围内的质数，然后统计每个质数的倍数出现的次数，更新最大值。

### 最优关键思路或技巧
- 采用桶数组来统计因数出现的次数，方便快速查找。
- 利用 $O(\sqrt{n})$ 的时间复杂度来找出一个数的所有因数，提高效率。
- 部分题解通过枚举质数来减少不必要的计算，因为质数中一定有最优解，合数一定不比质数更优。

### 可拓展之处
同类型题可能会有不同的数据范围和约束条件，如力量值范围变大，或者增加其他限制条件。类似算法套路可以应用在求最大公约数相关的问题中，通过枚举因数或质数来解决问题。

### 推荐题目
- [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)
- [P1306 斐波那契公约数](https://www.luogu.com.cn/problem/P1306)
- [P2152 [SDOI2009]SuperGCD](https://www.luogu.com.cn/problem/P2152)

---
处理用时：47.45秒