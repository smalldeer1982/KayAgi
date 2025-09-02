# 题目信息

# Increasing by Modulo

## 题目描述

Toad Zitz has an array of integers, each integer is between $ 0 $ and $ m-1 $ inclusive. The integers are $ a_1, a_2, \ldots, a_n $ .

In one operation Zitz can choose an integer $ k $ and $ k $ indices $ i_1, i_2, \ldots, i_k $ such that $ 1 \leq i_1 < i_2 < \ldots < i_k \leq n $ . He should then change $ a_{i_j} $ to $ ((a_{i_j}+1) \bmod m) $ for each chosen integer $ i_j $ . The integer $ m $ is fixed for all operations and indices.

Here $ x \bmod y $ denotes the remainder of the division of $ x $ by $ y $ .

Zitz wants to make his array non-decreasing with the minimum number of such operations. Find this minimum number of operations.

## 说明/提示

In the first example, the array is already non-decreasing, so the answer is $ 0 $ .

In the second example, you can choose $ k=2 $ , $ i_1 = 2 $ , $ i_2 = 5 $ , the array becomes $ [0,0,1,3,3] $ . It is non-decreasing, so the answer is $ 1 $ .

## 样例 #1

### 输入

```
5 3
0 0 0 1 2
```

### 输出

```
0
```

## 样例 #2

### 输入

```
5 7
0 6 1 3 2
```

### 输出

```
1
```

# AI分析结果

### 题目翻译
# 按模递增

## 题目描述
蟾蜍齐茨（Toad Zitz）有一个整数数组，每个整数都在 $0$ 到 $m - 1$（包含边界）之间。这些整数为 $a_1, a_2, \ldots, a_n$。

在一次操作中，齐茨可以选择一个整数 $k$ 和 $k$ 个索引 $i_1, i_2, \ldots, i_k$，使得 $1 \leq i_1 < i_2 < \ldots < i_k \leq n$。然后，他应该将每个选定的整数 $i_j$ 对应的 $a_{i_j}$ 变为 $((a_{i_j} + 1) \bmod m)$。整数 $m$ 对于所有操作和索引都是固定的。

这里 $x \bmod y$ 表示 $x$ 除以 $y$ 的余数。

齐茨希望通过最少的此类操作使他的数组变为非递减数组。请找出这个最小操作次数。

## 说明/提示
在第一个样例中，数组已经是非递减的，所以答案是 $0$。

在第二个样例中，你可以选择 $k = 2$，$i_1 = 2$，$i_2 = 5$，数组将变为 $[0, 0, 1, 3, 3]$。它是非递减的，所以答案是 $1$。

## 样例 #1
### 输入
```
5 3
0 0 0 1 2
```
### 输出
```
0
```

## 样例 #2
### 输入
```
5 7
0 6 1 3 2
```
### 输出
```
1
```

### 算法分类
二分

### 综合分析与结论
这些题解的核心思路都是利用二分查找最小操作次数，同时结合贪心策略来判断某个操作次数是否可行。在二分过程中，不断缩小操作次数的范围，直到找到最小的满足条件的操作次数。

各题解的主要区别在于贪心判断的具体实现细节，如处理数组元素时的分类讨论方式和边界条件的处理。但整体的算法框架和核心思想是一致的。

### 所选的题解
- **作者：qwaszx (赞：5)  ★★★★**
    - **关键亮点**：思路清晰，代码简洁，对二分和贪心的实现逻辑明确，通过分类讨论数组元素的大小关系来进行贪心判断。
- **作者：⚡小林子⚡ (赞：3)  ★★★★**
    - **关键亮点**：详细解释了二分答案的思路和 check 函数的实现，对取模情况的分类讨论较为细致。
- **作者：TheShadow (赞：1)  ★★★★**
    - **关键亮点**：对二分和贪心的策略描述清晰，代码中使用了模板函数进行输入输出，提高了代码的复用性。

### 重点代码
#### qwaszx 的题解
```cpp
int judge(int x)
{
    for(int i=1;i<=n;i++)a[i]=w[i];
    for(int i=1;i<=n;i++)
    {
        if(a[i]<a[i-1])
        {
            if(a[i-1]-a[i]>x)return 0;
            a[i]=a[i-1];
        }
        else
            if(a[i-1]+m-a[i]<=x)a[i]=a[i-1];
    }
    return 1;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",w+i);
    int l=0,r=m,mid;
    while(l<r)
    {
        mid=(l+r)>>1;
        if(judge(mid))r=mid;
        else l=mid+1;
    }
    cout<<l<<endl;
}
```
**核心实现思想**：`judge` 函数用于判断在 $x$ 次操作内能否使数组非递减。通过遍历数组，根据相邻元素的大小关系进行贪心操作。如果无法满足非递减条件则返回 $0$，否则返回 $1$。在 `main` 函数中，使用二分查找最小的操作次数。

#### ⚡小林子⚡ 的题解
```cpp
inline bool check(int mid) {
    if(mid == m) return 1; 
    memcpy(b, a, sizeof a); 
    int tmp = (b[1] + mid) % m, i;
    if(tmp < b[1]) b[1] = 0; 
    for(i = 2; i <= n; i++) {
        tmp = (b[i] + mid) % m;
        if(tmp < b[i]) { 
            if(0 <= b[i - 1] && b[i - 1] <= tmp)
                b[i] = b[i - 1];
            else if(b[i] <= b[i - 1] && b[i - 1] < m)
                b[i] = b[i - 1];
        } 
        else {
            if(b[i] <= b[i - 1] && b[i - 1] <= tmp)
                b[i] = b[i - 1];
            else if(tmp < b[i - 1])
                return 0;
        } 
    }
    return 1;
}
int main() {
    scanf("%d%d", &n, &m);
    int i;
    for(i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    int l = 0, r = m, mid, ans; 
    while(l < r) { 
        mid = (l + r) >> 1;
        if(check(mid)) ans = r = mid;
        else l = mid + 1; 
    }
    printf("%d", ans);
    return 0;
}
```
**核心实现思想**：`check` 函数用于判断在 `mid` 次操作内能否使数组非递减。对数组的第一个元素单独处理，然后遍历后续元素，根据取模情况和元素大小关系进行分类讨论。在 `main` 函数中，使用二分查找最小的操作次数。

#### TheShadow 的题解
```c++
it check(int lim){
    ri pre=0;
    for(ri i=1;i<=n;++i){
        if(val[i]+lim>=m&&add(val[i],lim)>=pre) continue;
        if(val[i]>=pre){pre=val[i];continue;}
        if(val[i]+lim<pre) return 0;
    }
    return 1;
}
int main(){
    read(n),read(m);
    for(ri i=1;i<=n;++i) read(val[i]);
    ri l=0,r=m;
    while(l<r){
        if(check(mid)) r=mid;
        else l=mid+1;
    }
    print(l);
    return 0;
}
```
**核心实现思想**：`check` 函数用于判断在 `lim` 次操作内能否使数组非递减。使用 `pre` 记录前一个元素的值，遍历数组，根据元素与 `pre` 的大小关系和操作次数进行判断。在 `main` 函数中，使用二分查找最小的操作次数。

### 关键思路或技巧
- **二分查找**：利用答案的单调性，通过二分不断缩小最小操作次数的范围，将时间复杂度从 $O(m)$ 降低到 $O(\log m)$。
- **贪心策略**：在判断某个操作次数是否可行时，采用贪心思想，每次都尽量让当前元素满足非递减条件，且取值尽量小，以减少对后续元素的影响。

### 拓展思路
同类型题目通常涉及求最大值最小或最小值最大的问题，都可以考虑使用二分法结合贪心或其他策略来解决。例如，在一些资源分配问题中，要求在满足一定条件下，使某个资源的使用量最小，就可以使用类似的二分 + 贪心的思路。

### 推荐题目
- [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)
- [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)
- [P3853 [TJOI2007]路标设置](https://www.luogu.com.cn/problem/P3853)

### 个人心得摘录与总结
- **dyx131313**：在比赛中 A 题写错下标，B 题觉得是垃圾题，C 题看错题。总结是在比赛中要仔细检查下标和题目条件，避免因粗心导致错误。
- **⚡小林子⚡**：考场上 10 分钟切掉，觉得题目难度应该是绿题。说明对这类二分 + 贪心的题目有较好的掌握，能够快速找到解题思路。

---
处理用时：53.21秒