# 题目信息

# Challenging Valleys

## 题目描述

You are given an array $ a[0 \dots n-1] $ of $ n $ integers. This array is called a "valley" if there exists exactly one subarray $ a[l \dots r] $ such that:

- $ 0 \le l \le r \le n-1 $ ,
- $ a_l = a_{l+1} = a_{l+2} = \dots = a_r $ ,
- $ l = 0 $ or $ a_{l-1} > a_{l} $ ,
- $ r = n-1 $ or $ a_r < a_{r+1} $ .

Here are three examples:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1760D/03a48b22ef3c4e8e328e6caa6008b87fe7824d84.png)The first image shows the array \[ $ 3, 2, 2, 1, 2, 2, 3 $ \], it is a valley because only subarray with indices $ l=r=3 $ satisfies the condition.

The second image shows the array \[ $ 1, 1, 1, 2, 3, 3, 4, 5, 6, 6, 6 $ \], it is a valley because only subarray with indices $ l=0, r=2 $ satisfies the codition.

The third image shows the array \[ $ 1, 2, 3, 4, 3, 2, 1 $ \], it is not a valley because two subarrays $ l=r=0 $ and $ l=r=6 $ that satisfy the condition.

You are asked whether the given array is a valley or not.

Note that we consider the array to be indexed from $ 0 $ .

## 说明/提示

The first three test cases are explained in the statement.

## 样例 #1

### 输入

```
6
7
3 2 2 1 2 2 3
11
1 1 1 2 3 3 4 5 6 6 6
7
1 2 3 4 3 2 1
7
9 7 4 6 9 9 10
1
1000000000
8
9 4 4 5 9 4 9 10```

### 输出

```
YES
YES
NO
YES
YES
NO```

# AI分析结果

### 题目内容
# 具有挑战性的山谷

## 题目描述
给定一个包含 $n$ 个整数的数组 $a[0 \dots n - 1]$。如果存在恰好一个子数组 $a[l \dots r]$ 满足以下条件，则称该数组为“山谷”：
- $0 \le l \le r \le n - 1$；
- $a_l = a_{l + 1} = a_{l + 2} = \dots = a_r$；
- $l = 0$ 或 $a_{l - 1} > a_{l}$；
- $r = n - 1$ 或 $a_r < a_{r + 1}$。

以下是三个示例：
![示例图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1760D/03a48b22ef3c4e8e328e6caa6008b87fe7824d84.png)
第一张图展示的数组为 \[3, 2, 2, 1, 2, 2, 3\]，它是一个山谷，因为只有索引 $l = r = 3$ 的子数组满足条件。
第二张图展示的数组为 \[1, 1, 1, 2, 3, 3, 4, 5, 6, 6, 6\]，它是一个山谷，因为只有索引 $l = 0, r = 2$ 的子数组满足条件。
第三张图展示的数组为 \[1, 2, 3, 4, 3, 2, 1\]，它不是一个山谷，因为有两个子数组 $l = r = 0$ 和 $l = r = 6$ 满足条件。

你需要判断给定的数组是否为山谷。

请注意，数组索引从 $0$ 开始。

## 说明/提示
前三个测试用例在题目描述中有解释。

## 样例 #1
### 输入
```
6
7
3 2 2 1 2 2 3
11
1 1 1 2 3 3 4 5 6 6 6
7
1 2 3 4 3 2 1
7
9 7 4 6 9 9 10
1
1000000000
8
9 4 4 5 9 4 9 10
```
### 输出
```
YES
YES
NO
YES
YES
NO
```

### 算法分类
模拟

### 综合分析与结论
这些题解主要围绕判断给定数组是否为“山谷”展开。多数题解思路是先处理数组中连续相同元素，再判断是否存在唯一符合条件的子数组。
1. **思路方面**：
    - 部分题解通过枚举左端点，找到最大右端点满足元素相等，再判断条件 3 和 4  ，如 cjh20090318 的题解。
    - 部分题解利用去重简化判断，去重后判断数组是否满足仅有一个递增段和一个递减段，如 srds_cbddl 、oceanfish 、zgy_123 、Wander_E 、zfx_VeXl6 、litachloveyou 的题解。
    - 还有题解通过记录上下坡情况扫描数组判断，如 BLX32M_10 的题解。
2. **算法要点**：
    - 枚举法需注意循环边界和条件判断。
    - 去重操作可使用 unique 函数或手动去重，去重后判断数组特征。
    - 记录上下坡情况需预处理并在扫描时正确处理。
3. **解决难点**：
    - 准确理解并实现“山谷”的判断条件是关键，特别是条件 3 和 4 。
    - 处理数组中连续相同元素，避免重复判断。

### 所选的题解
- **作者：cjh20090318 (5星)**
    - **关键亮点**：思路清晰，直接枚举左端点，找到满足元素相等的最大右端点，再判断条件，代码实现简洁明了。
    - **重点代码核心思想**：枚举左端点 `i`，通过内层循环找到最大右端点 `j` 使 `a[j]==a[i]`，确定子数组 `[l, r]` 后判断是否满足条件 3 和 4 ，若满足且此前未找到符合条件子数组则标记，若已找到则输出 `NO`。
    - **核心代码片段**：
```cpp
void solve(){
    int n;scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",&a[i]);
    bool fl=0;
    for(int i=0;i<n;){
        int j;
        for(j=i;j<n && a[j]==a[i];j++);
        int l=i,r=j-1;
        if((l==0||a[l-1]>a[l]) && (r==n-1||a[r]<a[r+1])){
            if(fl){puts("NO");return;}
            else fl=1;
        }
        i=j;
    }
    puts(fl?"YES":"NO");
}
```
- **作者：srds_cbddl (4星)**
    - **关键亮点**：巧妙化简题面，提出去重思路，大大降低时间复杂度，代码简洁高效。
    - **重点代码核心思想**：先判断 `n == 1` 特殊情况，然后遍历数组判断是否同时存在上升和下降情况，若仅存在下降则输出 `YES`。
    - **核心代码片段**：
```cpp
void solve () {
    cin >> t;
    while (t --) {
        int n, a[maxn];
        cin >> n;
        for (int i = 0; i < n; i ++) {
            cin >> a[i];
        }
        if (n == 1) {
            cout << "YES\n";
            continue;
        }
        bool up = false, down = true;
        for (int i = 1; i < n; i ++) {
            if (a[i] > a[i - 1]) up = true;
            if (a[i] < a[i - 1]) {
                if (up) {
                    down = false;
                    break;
                }
            }
        }
        if (down) cout << "YES\n";
        else cout << "NO\n";
    }
}
```
- **作者：zgy_123 (4星)**
    - **关键亮点**：提出用栈代替数组并将首尾标记为 $\infty$ 避免特判，优化了判断过程，思路新颖。
    - **重点代码核心思想**：输入元素时，若与栈顶不同则入栈，处理完后将栈的首尾设为极大值，遍历栈判断满足 `q[i]<q[i - 1]&&q[i]<q[i + 1]` 的元素个数是否为 1 。
    - **核心代码片段**：
```cpp
int main(){
    int t;
    cin>>t;
    while(t--){
        k=0;
        int n,cnt=0,x;
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>x;
            if(x!=q[k]) q[++k]=x;
        }
        q[0]=q[k+1]=2e9;
        for(int i=1;i<=k;i++)
            if(q[i]<q[i-1]&&q[i]<q[i+1]) cnt++;
        if(cnt==1) cout<<"YES\n";
        else cout<<"NO\n";
    }
    return 0;
}
```

### 最优关键思路或技巧
1. **去重思路**：利用数组中连续相同元素对判断“山谷”无实质影响，通过去重简化数组，降低判断复杂度。
2. **避免特判技巧**：将数组首尾设为极大值（如 $\infty$），可避免对 `l = 0` 或 `r = n - 1` 的特殊判断，简化代码逻辑。

### 可拓展之处
同类型题常围绕数组特定子序列的判断，类似算法套路有先对数组进行预处理（如去重、计算差值等），再根据题目条件判断数组特征。

### 洛谷相似题目推荐
1. **P1036 [NOIP2002 普及组] 选数**：涉及组合与枚举，通过枚举不同组合判断是否满足条件，与本题枚举判断思路类似。
2. **P1164 小A点菜**：可通过动态规划解决，与本题一样需要根据给定条件判断是否满足特定情况，锻炼对条件的处理能力。
3. **P1909 [NOIP2016 普及组] 买铅笔**：属于贪心类型题目，与本题类似之处在于都需要根据题目条件选择合适策略，培养解决实际问题的算法思维。 

---
处理用时：63.98秒