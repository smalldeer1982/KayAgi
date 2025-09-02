# 题目信息

# Informatics in MAC

## 题目描述

In the Master's Assistance Center, Nyam-Nyam was given a homework assignment in informatics.

There is an array $ a $ of length $ n $ , and you want to divide it into $ k > 1 $ subsegments $ ^{\dagger} $ in such a way that the $ \operatorname{MEX} ^{\ddagger} $ on each subsegment is equal to the same integer.

Help Nyam-Nyam find any suitable division, or determine that it does not exist.

 $ ^{\dagger} $ A division of an array into $ k $ subsegments is defined as $ k $ pairs of integers $ (l_1, r_1), (l_2, r_2), \ldots, (l_k, r_k) $ such that $ l_i \le r_i $ and for each $ 1 \le j \le k - 1 $ , $ l_{j + 1} = r_j + 1 $ , and also $ l_1 = 1 $ and $ r_k = n $ . These pairs represent the subsegments themselves.

 $ ^{\ddagger}\operatorname{MEX} $ of an array is the smallest non-negative integer that does not belong to the array.

For example:

- $ \operatorname{MEX} $ of the array $ [2, 2, 1] $ is $ 0 $ , because $ 0 $ does not belong to the array.
- $ \operatorname{MEX} $ of the array $ [3, 1, 0, 1] $ is $ 2 $ , because $ 0 $ and $ 1 $ belong to the array, but $ 2 $ does not.
- $ \operatorname{MEX} $ of the array $ [0, 3, 1, 2] $ is $ 4 $ , because $ 0 $ , $ 1 $ , $ 2 $ , and $ 3 $ belong to the array, but $ 4 $ does not.

## 说明/提示

In the first test case, the array $ a $ can be divided into $ 2 $ subsegments with boundaries $ [1, 1] $ and $ [2, 2] $ :

- $ \operatorname{MEX} $ of the first subsegment $ [0] $ is $ 1 $ , as $ 0 $ belongs to the subsegment, but $ 1 $ does not.
- $ \operatorname{MEX} $ of the second subsegment $ [0] $ is $ 1 $ , as $ 0 $ belongs to the subsegment, but $ 1 $ does not.

In the second test case, it can be proven that the required division does not exist.

In the third test case, the array $ a $ can be divided into $ 3 $ subsegments with boundaries $ [1, 3] $ , $ [4, 5] $ , $ [6, 8] $ :

- $ \operatorname{MEX} $ of the first subsegment $ [0, 1, 7] $ is $ 2 $ , as $ 0 $ and $ 1 $ belong to the subsegment, but $ 2 $ does not.
- $ \operatorname{MEX} $ of the second subsegment $ [1, 0] $ is $ 2 $ , as $ 0 $ and $ 1 $ belong to the subsegment, but $ 2 $ does not.
- $ \operatorname{MEX} $ of the third subsegment $ [1, 0, 3] $ is $ 2 $ , as $ 0 $ and $ 1 $ belong to the subsegment, but $ 2 $ does not.

## 样例 #1

### 输入

```
5
2
0 0
5
0 1 2 3 4
8
0 1 7 1 0 1 0 3
3
2 2 2
4
0 1 2 0```

### 输出

```
2
1 1
2 2
-1
3
1 3
4 5
6 8
3
1 1
2 2
3 3
-1```

# AI分析结果

### 题目翻译
# 信息学作业

## 题目描述
在大师辅助中心，Nyam - Nyam 接到了一道信息学的作业题。

有一个长度为 $n$ 的数组 $a$，你需要将它分成 $k > 1$ 个子段 $^{\dagger}$，使得每个子段的 $\text{MEX}^{\ddagger}$ 都等于同一个整数。

请帮助 Nyam - Nyam 找到任何合适的划分方法，或者确定这种划分不存在。

$^{\dagger}$ 将一个数组划分为 $k$ 个子段的定义是 $k$ 对整数 $(l_1, r_1), (l_2, r_2), \ldots, (l_k, r_k)$，满足 $l_i \leq r_i$，并且对于每个 $1 \leq j \leq k - 1$，有 $l_{j + 1} = r_j + 1$，同时 $l_1 = 1$ 且 $r_k = n$。这些数对代表了子段本身。

$^{\ddagger}$ 数组的 $\text{MEX}$ 是不属于该数组的最小非负整数。

例如：
- 数组 $[2, 2, 1]$ 的 $\text{MEX}$ 是 $0$，因为 $0$ 不属于该数组。
- 数组 $[3, 1, 0, 1]$ 的 $\text{MEX}$ 是 $2$，因为 $0$ 和 $1$ 属于该数组，但 $2$ 不属于。
- 数组 $[0, 3, 1, 2]$ 的 $\text{MEX}$ 是 $4$，因为 $0$、$1$、$2$ 和 $3$ 属于该数组，但 $4$ 不属于。

## 说明/提示
在第一个测试用例中，数组 $a$ 可以划分为 $2$ 个子段，边界分别为 $[1, 1]$ 和 $[2, 2]$：
- 第一个子段 $[0]$ 的 $\text{MEX}$ 是 $1$，因为 $0$ 属于该子段，但 $1$ 不属于。
- 第二个子段 $[0]$ 的 $\text{MEX}$ 是 $1$，因为 $0$ 属于该子段，但 $1$ 不属于。

在第二个测试用例中，可以证明不存在满足要求的划分。

在第三个测试用例中，数组 $a$ 可以划分为 $3$ 个子段，边界分别为 $[1, 3]$、$[4, 5]$、$[6, 8]$：
- 第一个子段 $[0, 1, 7]$ 的 $\text{MEX}$ 是 $2$，因为 $0$ 和 $1$ 属于该子段，但 $2$ 不属于。
- 第二个子段 $[1, 0]$ 的 $\text{MEX}$ 是 $2$，因为 $0$ 和 $1$ 属于该子段，但 $2$ 不属于。
- 第三个子段 $[1, 0, 3]$ 的 $\text{MEX}$ 是 $2$，因为 $0$ 和 $1$ 属于该子段，但 $2$ 不属于。

## 样例 #1
### 输入
```
5
2
0 0
5
0 1 2 3 4
8
0 1 7 1 0 1 0 3
3
2 2 2
4
0 1 2 0
```
### 输出
```
2
1 1
2 2
-1
3
1 3
4 5
6 8
3
1 1
2 2
3 3
-1
```

### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路基本一致，都是先证明如果存在划分成 $k$ 段的方案，那么一定存在划分成 $2$ 段的方案，然后通过枚举分割点，利用不同方法计算分割点左右子段的 $\text{MEX}$，判断是否相等来确定是否存在可行划分。

各题解的算法要点和难点对比：
- **维护前后缀 $\text{MEX}$ 数组**：通过遍历数组，分别从前往后和从后往前计算前缀和后缀的 $\text{MEX}$，然后枚举分割点比较前后缀 $\text{MEX}$ 是否相等。难点在于正确计算 $\text{MEX}$，不同实现方式在数据结构的选择上有所不同，如使用 `map`、`set` 等。
- **滑动窗口配合桶数组**：先计算整个数组的 $\text{MEX}$，然后使用两个桶数组分别记录分割点左右子段中每个数字的出现次数，通过滑动窗口的方式维护左右子段中小于整个数组 $\text{MEX}$ 的不同数字的个数，判断是否满足条件。难点在于正确维护桶数组和计数器。
- **线段树二分**：利用线段树二分快速计算 $\text{MEX}$，枚举分割点判断是否有解。此方法实现难度较大，需要对线段树和二分有深入理解。

### 评分较高的题解
- **作者：Kindershiuo (4星)**
    - **关键亮点**：思路清晰，代码简洁，直接维护前后缀 $\text{MEX}$ 数组，通过枚举分割点判断是否有解。
    - **核心代码**：
```cpp
void solve() {
    int n;
    cin>>n;
    map<int,int>ma;
    map<int,int>mb;
    int mex1[n+5];
    int mex2[n+5];
    memset(mex1,0,sizeof mex1);
    memset(mex2,0,sizeof mex2);
    int a[n+5];
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++){
        mex1[i]=mex1[i-1];
        ma[a[i]]++;
        while(ma[mex1[i]])mex1[i]++;
    }
    for(int i=n;i>=1;i--){
        mex2[i]=mex2[i+1];
        mb[a[i]]++;
        while(mb[mex2[i]])mex2[i]++;
    }
    for(int i=1;i<=n;i++){
        if(mex1[i]==mex2[i+1]){
            cout<<2<<endl;
            cout<<1<<" "<<i<<endl;
            cout<<i+1<<" "<<n<<endl;
            return;
        }
    }
    cout<<-1<<endl;
}
```
- **作者：ylch (4星)**
    - **关键亮点**：提供了两种方法，一种是滑动窗口配合桶数组，另一种是维护前后缀 $\text{MEX}$ 数组，思路详细，代码规范。
    - **核心代码（方法 2）**：
```cpp
void solve()
{
    int n;
    cin >> n;
    vector <int> a(n + 1);

    for(int i = 1; i <= n; i ++){
        cin >> a[i];
    }

    vector <int> v1(n + 1), v2(n + 1); // 前缀、后缀MEX数组
    set <int> st; // 处理mex数的集合

    // 前缀mex
    for(int i = 0; i <= n; i ++) st.insert(i); // a[i]的值域是0~n
    for(int i = 1; i <= n; i ++){
        if(st.find(a[i]) != st.end()){ // 如果还在set中
            st.erase(a[i]);
        }
        v1[i] = *st.begin(); // 每个位置的前缀mex就是集合中最小的数
    }
    st.clear();

    // 后缀mex
    for(int i = 0; i <= n; i ++) st.insert(i); // a[i]的值域是0~n
    for(int i = n; i >= 1; i --){
        if(st.find(a[i]) != st.end()){ // 如果还在set中
            st.erase(a[i]);
        }
        v2[i] = *st.begin(); // 每个位置的前缀mex就是集合中最小的数
    }
    
    // 枚举前后mex一致的分割点
    for(int i = 2; i <= n; i ++){
        // v1[i] 1~i的mex；v2[i] i~n的mex
        if(v1[i - 1] == v2[i]){ // 1~i-1的mex = i~n的mex
            cout << 2 << '\n' << 1 << ' ' << i - 1 << '\n' << i << ' ' << n << '\n';
            return ;
        }
    }
    cout << -1 << '\n'; // 找不到输出-1
}
```
- **作者：2huk (4星)**
    - **关键亮点**：同样是维护前后缀 $\text{MEX}$，使用 `set` 和 `map` 辅助计算，代码实现较为清晰。
    - **核心代码**：
```cpp
void Luogu_UID_748509() {
    fin >> n;
    for (int i = 1; i <= n; ++ i ) fin >> a[i];
    
    set<int> S;
    for (int i = 0; i < n; ++ i ) S.insert(i);
    map<int, int> P;
    
    for (int i = 1; i <= n; ++ i ) {
        ++ P[a[i]];
        if (P[a[i]] == 1) S.erase(a[i]);
        pre[i] = *S.begin(); 
    }
    
    S.clear();
    for (int i = 0; i < n; ++ i ) S.insert(i);
    P.clear();
    
    for (int i = n; i; -- i ) {
        ++ P[a[i]];
        if (P[a[i]] == 1) S.erase(a[i]);
        suf[i] = *S.begin(); 
    }
    
    for (int i = 2; i <= n; ++ i )
        if (pre[i - 1] == suf[i]) {
            fout << 2 << '\n' << 1 << ' ' << i - 1 << '\n' << i << ' ' << n << '\n';
            return;
        }
    puts("-1");
}
```

### 最优关键思路或技巧
- **结论推导**：通过分析发现，如果存在划分成 $k$ 段的方案，那么一定存在划分成 $2$ 段的方案，将问题简化。
- **数据结构选择**：使用 `map`、`set` 等数据结构辅助计算 $\text{MEX}$，可以方便地记录数字的出现情况和快速找到最小未出现的数字。

### 拓展思路
同类型题目可能会改变数组的性质或 $\text{MEX}$ 的定义，或者增加一些限制条件。类似的算法套路可以应用在需要计算区间特征值并进行划分的问题中，关键在于如何高效地计算区间特征值和枚举划分点。

### 推荐洛谷题目
- P1168 中位数
- P1428 小鱼比可爱
- P1443 马的遍历

### 个人心得摘录与总结
题解中未包含个人心得内容。

---
处理用时：58.40秒