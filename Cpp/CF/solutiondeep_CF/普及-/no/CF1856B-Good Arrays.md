# 题目信息

# Good Arrays

## 题目描述

You are given an array of positive integers $ a $ of length $ n $ .

Let's call an array of positive integers $ b $ of length $ n $ good if:

1. $ a_i \neq b_i $ for all $ i $ from $ 1 $ to $ n $ ,
2. $ a_1 + a_2 +\ldots + a_n = b_1 + b_2 + \ldots + b_n $ .

Does a good array exist?

## 说明/提示

In the first test case, a possible good array is $ [3, 3, 3] $ . Some examples of not good arrays are:

- $ [8, 0, 1] $ — the array does not consist of only positive integers,
- $ [5, 2, 4] $ — the array does not have the same sum as the given array,
- $ [5, 2, 2] $ — the third element is equal to the third element of the given array.

In the second test case, $ [1, 1] $ is the only array of positive integers of length $ 2 $ that has the sum of it's elements equal to $ 2 $ . Since $ [1, 1] $ is not a good array, the answer is "NO".

## 样例 #1

### 输入

```
6
3
6 1 2
2
1 1
4
3 1 2 4
1
17
5
1 2 1 1 1
3
618343152 819343431 1000000000```

### 输出

```
YES
NO
YES
NO
NO
YES```

# AI分析结果

### 题目内容翻译
## 好数组

### 题目描述
给定一个长度为 $n$ 的正整数数组 $a$。

如果一个长度为 $n$ 的正整数数组 $b$ 满足以下条件，则称其为好数组：
1. 对于从 $1$ 到 $n$ 的所有 $i$，都有 $a_i \neq b_i$；
2. $a_1 + a_2 + \cdots + a_n = b_1 + b_2 + \cdots + b_n$。

是否存在好数组？

### 说明/提示
在第一个测试用例中，一个可能的好数组是 $[3, 3, 3]$。一些不是好数组的例子如下：
- $[8, 0, 1]$ — 该数组并非仅由正整数组成；
- $[5, 2, 4]$ — 该数组的元素和与给定数组不同；
- $[5, 2, 2]$ — 第三个元素与给定数组的第三个元素相等。

在第二个测试用例中，$[1, 1]$ 是长度为 $2$ 且元素和为 $2$ 的唯一正整数数组。由于 $[1, 1]$ 不是好数组，所以答案是 "NO"。

### 样例 #1
#### 输入
```
6
3
6 1 2
2
1 1
4
3 1 2 4
1
17
5
1 2 1 1 1
3
618343152 819343431 1000000000
```
#### 输出
```
YES
NO
YES
NO
NO
YES
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是围绕构造满足条件的数组 $b$ 展开。大部分题解先特判 $n = 1$ 的情况，因为此时一定无法构造出满足条件的数组 $b$。然后，通过不同的方式尝试构造数组 $b$，并判断是否能够成功。

主要的构造方法有：
1. 让每个 $b_i$ 初始为 $1$，若 $a_i = 1$ 则 $b_i$ 变为 $2$，计算变化总量 $sum$，若 $sum < 0$ 则无解。
2. 将序列排序，前 $n - 1$ 个数若为 $1$ 则变为 $2$，否则变为 $1$，中途判断和是否超过原数组和，最后处理最后一个数。

难点在于处理特殊情况，如 $a_i = 1$ 时的构造，以及判断是否能够成功构造出数组 $b$。

### 所选题解
- **LHLeisus（4星）**
    - **关键亮点**：思路清晰，代码简洁，通过贪心的思想，让每个 $b_i$ 尽量取最小，计算变化总量 $sum$ 来判断是否有解。
    - **个人心得**：作者提到电脑没网，手机写的题解，希望大家点赞支持。
- **_Wind_Leaves_ShaDow_（4星）**
    - **关键亮点**：思路详细，对最后一个数的处理进行了严格的证明，确保构造的正确性。
    - **个人心得**：作者赛时 WA 爆，调了半个小时，比赛结束后发现数组开小，提醒大家注意数组大小。
- **yuyc（4星）**
    - **关键亮点**：思路直观，通过计算备用的数和需要用的数，判断是否够分来确定是否有解。

### 重点代码
#### LHLeisus 的代码
```cpp
int main()
{
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        ll sum=0;
        FOR(i,1,n){
            scanf("%d",&k);
            if(k==1) sum--;
            else sum+=k-1;
        }
        if(sum<0||n==1) puts("NO");
        else puts("YES");
    }
    return 0;
}
```
**核心实现思想**：遍历数组 $a$，若 $a_i = 1$ 则 $sum$ 减 $1$，否则 $sum$ 加上 $a_i - 1$，最后判断 $sum$ 是否小于 $0$ 或 $n$ 是否为 $1$ 来确定是否有解。

#### _Wind_Leaves_ShaDow_ 的代码
```cpp
inline bool solve(){//能否构造
    cin>>n;
    int sum=0,sm=0;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sum+=a[i];
    }
    if(n==1)return 0;//特判
    sort(a+1,a+n+1);
    for(int i=1;i<n;i++){
        if(a[i]==1)sm+=2;
        else sm++;
        if(sm>=sum)return 0;//中途大于就构造不成
    }
    return 1;//不然一定构造得成
}
```
**核心实现思想**：先计算数组 $a$ 的和 $sum$，对数组 $a$ 排序，前 $n - 1$ 个数若为 $1$ 则 $sm$ 加 $2$，否则加 $1$，若 $sm$ 大于等于 $sum$ 则无法构造，否则一定可以构造。

#### yuyc 的代码
```cpp
int main(){
    int T;
    cin>>T;
    while(T--){
        int n,cnt=0;
        ll s=0;
        cin>>n;
        for(int i=0;i<n;i++){
            cin>>a[i];
            if(a[i]==1) cnt++;//当a[i]=1时，b[i]需要多加1
            s+=a[i];//计算a数组中数的总和，即备用的数
        }
        if(n==1) cout<<"NO"<<endl;//特判
        else if(s-cnt-n>=0) cout<<"YES"<<endl;//备用的数减去需要用的数
        else cout<<"NO"<<endl;
    }
    return 0;
}
```
**核心实现思想**：遍历数组 $a$，统计 $1$ 的个数 $cnt$ 和数组 $a$ 的和 $s$，若 $n = 1$ 则无解，否则判断 $s - cnt - n$ 是否大于等于 $0$ 来确定是否有解。

### 拓展思路
同类型题可能会有更多的限制条件，如数组元素的范围、构造数组的其他要求等。类似的算法套路可以是先分析特殊情况，然后尝试构造满足条件的解，通过计算一些关键值来判断是否能够成功构造。

### 推荐题目
1. [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)：涉及路径构造和动态规划思想。
2. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)：需要构造最大的数，涉及排序和字符串处理。
3. [P1049 装箱问题](https://www.luogu.com.cn/problem/P1049)：需要构造合适的装箱方案，涉及动态规划和贪心思想。

### 个人心得总结
- _Wind_Leaves_ShaDow_ 提醒大家注意数组大小，避免因数组开小而导致错误。
- LHLeisus 虽然在困难条件下写题解，但依然坚持分享，值得鼓励。

---
处理用时：43.53秒