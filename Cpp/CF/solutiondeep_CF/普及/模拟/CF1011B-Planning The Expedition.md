# 题目信息

# Planning The Expedition

## 题目描述

Natasha is planning an expedition to Mars for $ n $ people. One of the important tasks is to provide food for each participant.

The warehouse has $ m $ daily food packages. Each package has some food type $ a_i $ .

Each participant must eat exactly one food package each day. Due to extreme loads, each participant must eat the same food type throughout the expedition. Different participants may eat different (or the same) types of food.

Formally, for each participant $ j $ Natasha should select his food type $ b_j $ and each day $ j $ -th participant will eat one food package of type $ b_j $ . The values $ b_j $ for different participants may be different.

What is the maximum possible number of days the expedition can last, following the requirements above?

## 说明/提示

In the first example, Natasha can assign type $ 1 $ food to the first participant, the same type $ 1 $ to the second, type $ 5 $ to the third and type $ 2 $ to the fourth. In this case, the expedition can last for $ 2 $ days, since each participant can get two food packages of his food type (there will be used $ 4 $ packages of type $ 1 $ , two packages of type $ 2 $ and two packages of type $ 5 $ ).

In the second example, there are $ 100 $ participants and only $ 1 $ food package. In this case, the expedition can't last even $ 1 $ day.

## 样例 #1

### 输入

```
4 10
1 5 2 1 1 1 2 5 7 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
100 1
1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
2 5
5 4 3 2 1
```

### 输出

```
1
```

## 样例 #4

### 输入

```
3 9
42 42 42 42 42 42 42 42 42
```

### 输出

```
3
```

# AI分析结果

### 题目中文重写
# 规划探险之旅

## 题目描述
娜塔莎正在为 $n$ 个人规划一次火星探险之旅。其中一项重要任务是为每位参与者提供食物。

仓库里有 $m$ 份日常食物套餐。每份套餐有某种食物类型 $a_i$。

每位参与者每天必须恰好食用一份食物套餐。由于面临极大的负荷，每位参与者在整个探险期间必须食用同一种类型的食物。不同的参与者可以食用不同（或相同）类型的食物。

形式上，对于每位参与者 $j$，娜塔莎应该为其选择食物类型 $b_j$，并且在每一天，第 $j$ 位参与者将食用一份类型为 $b_j$ 的食物套餐。不同参与者的 $b_j$ 值可以不同。

在满足上述要求的情况下，这次探险最多可以持续多少天？

## 说明/提示
在第一个示例中，娜塔莎可以给第一位参与者分配类型 1 的食物，给第二位参与者分配相同的类型 1，给第三位参与者分配类型 5，给第四位参与者分配类型 2。在这种情况下，探险可以持续 2 天，因为每位参与者都可以获得两份其食物类型的食物套餐（将使用 4 份类型 1 的套餐、两份类型 2 的套餐和两份类型 5 的套餐）。

在第二个示例中，有 100 名参与者，但只有 1 份食物套餐。在这种情况下，探险甚至无法持续 1 天。

## 样例 #1
### 输入
```
4 10
1 5 2 1 1 1 2 5 7 2
```
### 输出
```
2
```

## 样例 #2
### 输入
```
100 1
1
```
### 输出
```
0
```

## 样例 #3
### 输入
```
2 5
5 4 3 2 1
```
### 输出
```
1
```

## 样例 #4
### 输入
```
3 9
42 42 42 42 42 42 42 42 42
```
### 输出
```
3
```

### 综合分析与结论
这些题解主要围绕计算探险队在给定食物条件下最多能持续的天数展开，思路可分为枚举法和二分法两类。
- **枚举法**：
    - **思路**：先统计每种食物的数量，然后从大到小枚举天数，计算每种食物在该天数下能满足的人数，若总人数满足要求则输出该天数。
    - **算法要点**：使用数组记录每种食物的数量，通过两层循环枚举天数和食物类型。
    - **难点**：枚举范围的确定，需要根据食物总数和人数合理设定。
- **二分法**：
    - **思路**：二分枚举天数，对于每个中间天数，检查是否能满足所有人的食物需求。
    - **算法要点**：确定二分的左右边界，编写检查函数判断当前天数是否可行。
    - **难点**：二分边界的确定和检查函数的实现。

### 评分较高的题解
- **作者：_Wind_Leaves_ShaDow_（5星）**
    - **关键亮点**：思路清晰，使用二分法解决问题，代码简洁，复杂度分析明确。
    - **核心代码**：
```cpp
inline bool check(int x){
    int sum=0;
    for(int i=0;i<=100;i++)sum+=(g[i]/x);
    return sum>=n;
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int a;
        cin>>a;
        g[a]++;
        r=max(r,g[a]);
    }
    while(l<=r){
        mid=(l+r)>>1;
        if(check(mid))l=mid+1;
        else r=mid-1; 
    }
    cout<<l-1;
    return 0; 
}
```
核心实现思想：使用桶数组 `g` 记录每种食物的数量，二分枚举天数，通过 `check` 函数判断当前天数是否可行。

- **作者：封禁用户（4星）**
    - **关键亮点**：详细解释了二分的思路和 `check` 函数的作用，代码规范。
    - **核心代码**：
```cpp
inline bool check(int x){
    ll t=0;
    for(int i=1;i<=d;++i)
        t+=q[i]/x;
    return t>=n;
}
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m;
    for(int i=1;i<=m;++i)
        cin>>a[i],++q[a[i]],d=max(d,a[i]),b=max(b,q[a[i]]);
    r=b;
    while(l<=r){
        mid=(l+r)/2;
        if(check(mid))
            l=mid+1,o=mid;
        else r=mid-1;
    }
    cout<<o<<"\n";
    return 0;
}
```
核心实现思想：同样使用二分法，通过 `check` 函数计算每种食物在当前天数下能满足的人数总和，与总人数比较。

- **作者：BYWYR（4星）**
    - **关键亮点**：对二分的思路和复杂度进行了分析，代码逻辑清晰。
    - **核心代码**：
```cpp
bool check(int x) {
    int l = 0;
    for(int i = 1;i <= maxans;i++) {
        l += t[i] / x;
    }
    if(l < n) {
        return false;
    }
    return true;
}
int main() {
    cin >> n >> k;
    for(int i = 1;i <= k;i++) {
        cin >> mps[i];
        t[mps[i]] ++;
        maxans = max(maxans, mps[i]);
        ans = max(ans, t[mps[i]]);
    }
    int l = 1, r = ans;
    while(l <= r) {
        int mid = (l+r) / 2;
        if(check(mid)) {
            ansn = mid;
            l = mid+1;
        }
        else {
            r = mid-1;
        }
    }
    cout << ansn << endl;
}
```
核心实现思想：先统计每种食物的数量，确定二分的右边界，二分枚举天数，通过 `check` 函数判断可行性。

### 最优关键思路或技巧
- **二分法**：对于这种求最大值且具有单调性的问题，二分法可以将时间复杂度从枚举的 $O(n^2)$ 降低到 $O(n\log m)$。
- **桶排序思想**：使用数组记录每种食物的数量，方便后续计算。

### 拓展思路
同类型题或类似算法套路：二分答案类问题，如求最大最小值、最小最大值等，通常可以通过二分枚举答案并结合检查函数来解决。

### 洛谷推荐题目
- P2678 [NOIP2015 提高组] 跳石头
- P1182 数列分段 Section II
- P3853 [TJOI2007] 路标设置

### 个人心得摘录与总结
- **作者：2012zxt**：在理论上，天数可以直接从 100 枚举到 0，但如果这么做，就会喜提 RE。总结：枚举范围的确定需要谨慎，要避免出现除零等错误。 

---
处理用时：42.54秒