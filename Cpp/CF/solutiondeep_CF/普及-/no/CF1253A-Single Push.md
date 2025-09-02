# 题目信息

# Single Push

## 题目描述

You're given two arrays $ a[1 \dots n] $ and $ b[1 \dots n] $ , both of the same length $ n $ .

In order to perform a push operation, you have to choose three integers $ l, r, k $ satisfying $ 1 \le l \le r \le n $ and $ k > 0 $ . Then, you will add $ k $ to elements $ a_l, a_{l+1}, \ldots, a_r $ .

For example, if $ a = [3, 7, 1, 4, 1, 2] $ and you choose $ (l = 3, r = 5, k = 2) $ , the array $ a $ will become $ [3, 7, \underline{3, 6, 3}, 2] $ .

You can do this operation at most once. Can you make array $ a $ equal to array $ b $ ?

(We consider that $ a = b $ if and only if, for every $ 1 \le i \le n $ , $ a_i = b_i $ )

## 说明/提示

The first test case is described in the statement: we can perform a push operation with parameters $ (l=3, r=5, k=2) $ to make $ a $ equal to $ b $ .

In the second test case, we would need at least two operations to make $ a $ equal to $ b $ .

In the third test case, arrays $ a $ and $ b $ are already equal.

In the fourth test case, it's impossible to make $ a $ equal to $ b $ , because the integer $ k $ has to be positive.

## 样例 #1

### 输入

```
4
6
3 7 1 4 1 2
3 7 3 6 3 2
5
1 1 1 1 1
1 2 1 3 1
2
42 42
42 42
1
7
6
```

### 输出

```
YES
NO
YES
NO
```

# AI分析结果

### 题目内容
# 单次推进

## 题目描述
给定两个数组 $a[1 \dots n]$ 和 $b[1 \dots n]$，它们长度均为 $n$。

为了执行一次推进操作，你必须选择三个整数 $l$、$r$、$k$，满足 $1 \le l \le r \le n$ 且 $k > 0$。然后，你需要将 $k$ 加到元素 $a_l, a_{l+1}, \ldots, a_r$ 上。

例如，如果 $a = [3, 7, 1, 4, 1, 2]$ 且你选择 $(l = 3, r = 5, k = 2)$，数组 $a$ 将变为 $[3, 7, \underline{3, 6, 3}, 2]$。

你最多可以执行此操作一次。能否使数组 $a$ 等于数组 $b$ ？

（我们认为当且仅当对于每个 $1 \le i \le n$，$a_i = b_i$ 时，$a = b$）

## 说明/提示
第一个测试用例在题目描述中有说明：我们可以使用参数 $(l=3, r=5, k=2)$ 执行一次推进操作，使 $a$ 等于 $b$。

在第二个测试用例中，我们至少需要两次操作才能使 $a$ 等于 $b$。

在第三个测试用例中，数组 $a$ 和 $b$ 已经相等。

在第四个测试用例中，由于 $k$ 必须为正，所以不可能使 $a$ 等于 $b$。

## 样例 #1
### 输入
```
4
6
3 7 1 4 1 2
3 7 3 6 3 2
5
1 1 1 1 1
1 2 1 3 1
2
42 42
42 42
1
7
6
```
### 输出
```
YES
NO
YES
NO
```

### 算法分类
模拟

### 题解综合分析与结论
所有题解的核心思路都是将数组 $a$ 和 $b$ 对应元素相减，判断差值数组是否符合特定模式，即由两段全零子数组包裹着一段值相同的非零子数组，以此确定能否通过一次操作使 $a$ 等于 $b$。不同题解在具体实现细节和代码结构上有所差异。

### 所选的题解
- **作者：wkjwkj（5星）**
  - **关键亮点**：思路清晰，代码简洁，先特判 $a==b$ 的情况，然后通过相减得到差值数组，按照差值数组的特定模式进行判断，逻辑清晰明了。
  - **个人心得**：无
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005],b[100005],c[100005];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=n;i++)
            scanf("%d",&b[i]);
        bool ok=true;
        for(int i=1;i<=n;i++)
            if(a[i]!=b[i])ok=false;
        if(ok){//特判a==b的情况
            puts("YES");
            continue;
        }
        for(int i=1;i<=n;i++)
            c[i]=b[i]-a[i];
        int j=1;
        while(c[j]==0)j++;
        if(c[j]<0){
            puts("NO");
            continue;
        }
        j++;
        while(c[j]==c[j-1])j++;
        if(j==n+1){
            puts("YES");
            continue; 
        }
        int yes=true;
        for(;j<=n;j++)
            if(c[j]!=0)yes=false;
        if(yes)puts("YES");
        else puts("NO");
    }
}
```
  - **核心实现思想**：先判断 $a$ 和 $b$ 是否完全相同，相同则直接输出 `YES`。然后计算差值数组 $c$，找到第一个非零元素，判断其是否为负数，若是则输出 `NO`。接着检查后续元素是否与第一个非零元素值相同，若都相同且后续无其他非零元素则输出 `YES`，否则输出 `NO`。

- **作者：zhang_kevin（4星）**
  - **关键亮点**：代码结构清晰，将主要逻辑封装在 `work` 函数中，通过找到差值数组中第一个和最后一个非零元素的位置，再判断这两个位置之间的元素是否相同来得出结论。
  - **个人心得**：无
  - **核心代码**：
```cpp
#include<cstdio>
int a[100001], b[100001], s[100001], n;
inline void work(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }
    bool same = true, flag = true;
    for(int i = 1; i <= n; i++){
        scanf("%d", &b[i]);
        s[i] = b[i] - a[i];
        if(a[i]!= b[i]){
            same = false;
        }
        if(s[i] < 0){
            flag = false;
        }
    }
    if(!flag){
        puts("NO");
        return;
    }
    if(same){
        puts("YES");
        return;
    }
    int l = 1, r = n;
    while(!s[l++]);
    while(!s[r--]);
    l--, r++;
    int Min = 0x3f3f3f3f, Max = -0x3f3f3f3f;
    for(int i = l; i <= r; i++){
        if(Min > s[i]){
            Min = s[i];
        }
        if(Max < s[i]){
            Max = s[i];
        }
    }
    if(Min == Max){
        puts("YES");
    }else{
        puts("NO");
    }
    return;
}
auto Solve = [](void) -> int{
    int T;
    scanf("%d", &T);
    while(T--){
        work();
    }
    return 0;
}();
int main(){return Solve;}
```
  - **核心实现思想**：先读入数据并计算差值数组 $s$，同时判断 $a$ 和 $b$ 是否相同以及是否存在负数差值。若有负数差值则输出 `NO`，若相同则输出 `YES`。然后找到差值数组中第一个和最后一个非零元素的位置，遍历这两个位置之间的元素找到最大最小值，若最大最小值相同则输出 `YES`，否则输出 `NO`。

- **作者：_VEGETABLE_OIer_xlc（4星）**
  - **关键亮点**：详细地指出了题目中的细节，如 $k$ 为正整数、特判全部相同的情况等，代码逻辑围绕这些细节展开，具有较好的参考性。
  - **个人心得**：强调思路简单但细节多，自己被坑多次，如要注意加的数 $k$ 是正整数，要特判全部相同的情况，判断差序列时注意开头不是 $0$ 的情况。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[100010],b[100010],cha[100010];
int main(){
    cin>>t;
    while(t--)
    {
        memset(cha,0,sizeof(cha));//记得清0 
        cin>>n;
        for(int i=1;i<=n;i++)
            cin>>a[i];
        for(int i=1;i<=n;i++)
            cin>>b[i];
        bool fushu=1;
        int same=1;
        for(int i=1;i<=n;i++)
        {
            cha[i]=b[i]-a[i];
            if(cha[i]!=0)
            {
                same=0;
            }
            if(cha[i]<0)
                fushu=0;
        }
        if(!fushu)
        {
            cout<<"NO"<<endl;
            continue;
        }
        if(same)
        {
            cout<<"YES"<<endl;
            continue; 
        }//特判
        int jihui=1;
        cha[0]=cha[1];
        if(cha[1]>0)//如果第一个就要操作 
            jihui--;
        for(int i=2;i<=n;i++)
        {
            if(cha[i]!=cha[i-1]&&cha[i])
                jihui--;
        }
        if(jihui>=0)
            cout<<"YES"<<endl;
        else
            cout<<"NO"<<endl;
    }
    return 0;
} 
```
  - **核心实现思想**：先初始化差值数组并清零，读入 $a$ 和 $b$ 数组后计算差值数组，同时判断是否存在负数差值和数组是否完全相同。若有负数差值则输出 `NO`，若相同则输出 `YES`。然后通过遍历差值数组，根据元素是否与前一个相同来判断是否符合条件，若符合则输出 `YES`，否则输出 `NO`。

### 最优关键思路或技巧
将两个数组对应元素相减得到差值数组，通过对差值数组的模式判断来解决问题，这是核心思路。在实现过程中，提前特判数组完全相同以及存在负数差值的情况，可以简化后续逻辑。

### 可拓展之处
同类型题通常围绕数组的特定操作和状态判断展开，类似算法套路是对数组进行某种变换后，观察其规律或模式来解决问题。例如，给定数组的区间修改操作，判断能否通过有限次操作达到特定目标状态。

### 洛谷相似题目推荐
- [P1031 均分纸牌](https://www.luogu.com.cn/problem/P1031)：通过移动纸牌使每个位置纸牌数相同，考察对数组元素操作和状态判断。
- [P1208 [USACO1.3]混合牛奶 Mixing Milk](https://www.luogu.com.cn/problem/P1208)：涉及对多个数据的操作和选择，判断能否满足一定条件，与本题对数组操作判断是否符合条件类似。
- [P1990 覆盖墙壁](https://www.luogu.com.cn/problem/P1990)：通过不同方式覆盖墙壁，判断是否能完全覆盖，与本题判断能否通过特定操作使数组达到特定状态思路类似。

### 个人心得摘录与总结
_**VEGETABLE_OIer_xlc**_：强调该题思路简单但细节多，如 $k$ 必须为正整数、要特判数组完全相同的情况、判断差序列时要注意开头不是 $0$ 的情况等，这些细节处理不当容易导致错误。总结为解决此类问题不仅要把握核心思路，更要关注题目中的各种限制条件和边界情况。 

---
处理用时：103.57秒