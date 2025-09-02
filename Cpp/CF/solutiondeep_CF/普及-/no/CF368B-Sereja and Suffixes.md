# 题目信息

# Sereja and Suffixes

## 题目描述

Sereja has an array $ a $ , consisting of $ n $ integers $ a_{1} $ , $ a_{2} $ , $ ... $ , $ a_{n} $ . The boy cannot sit and do nothing, he decided to study an array. Sereja took a piece of paper and wrote out $ m $ integers $ l_{1},l_{2},...,l_{m} $ $ (1<=l_{i}<=n) $ . For each number $ l_{i} $ he wants to know how many distinct numbers are staying on the positions $ l_{i} $ , $ l_{i}+1 $ , ..., $ n $ . Formally, he want to find the number of distinct numbers among $ a_{li},a_{li}+1,...,a_{n} $ .?

Sereja wrote out the necessary array elements but the array was so large and the boy was so pressed for time. Help him, find the answer for the described question for each $ l_{i} $ .

## 样例 #1

### 输入

```
10 10
1 2 3 4 1 2 3 4 100000 99999
1
2
3
4
5
6
7
8
9
10
```

### 输出

```
6
6
6
6
6
5
4
3
2
1
```

# AI分析结果

### 题目内容
# Sereja和后缀

## 题目描述
Sereja有一个数组 $a$，由 $n$ 个整数 $a_{1}$，$a_{2}$，$...$，$a_{n}$ 组成。这个男孩不会无所事事，他决定研究这个数组。Sereja拿出一张纸，写下了 $m$ 个整数 $l_{1},l_{2},...,l_{m}$  （$1\leq l_{i}\leq n$）。对于每个数字 $l_{i}$，他想知道在位置 $l_{i}$，$l_{i}+1$，$...$，$n$ 上有多少个不同的数字。形式上，他想找出 $a_{li},a_{li + 1},...,a_{n}$ 中不同数字的数量。

Sereja写下了必要的数组元素，但数组太大了，而且这个男孩时间紧迫。帮帮他，为每个 $l_{i}$ 找到上述问题的答案。

## 样例 #1
### 输入
```
10 10
1 2 3 4 1 2 3 4 100000 99999
1
2
3
4
5
6
7
8
9
10
```
### 输出
```
6
6
6
6
6
5
4
3
2
1
```

### 算法分类
递推

### 综合分析与结论
这些题解的核心思路都是避免暴力的 $O(mn)$ 解法，通过预处理的方式优化。大多题解采用从后往前遍历数组，利用一个辅助数组或数据结构（如桶、map）记录数字是否出现过，从而递推计算出每个位置 $i$ 到数组末尾不同数字的个数。这样对于每次询问，就能以 $O(1)$ 的时间复杂度输出答案，将整体时间复杂度降低到 $O(\max(m, n))$。少数题解使用树状数组，将问题转化为区间修改、单点查询问题，但实现相对复杂。

### 所选的题解
 - **作者：Alex_Wei (5星)**
    - **关键亮点**：思路清晰简洁，先阐述暴力解法的不足，再提出优化方案。使用map（也提到可用数组，因 $a_i$ 范围小）判断数字是否出现，从后往前枚举数组，递推记录每个位置到数组末尾不同数字的个数，时间复杂度分析准确。
    - **个人心得**：无
    - **重点代码**：
```cpp
map <int,bool> k;
int n,m,a[100100],s[100100],l;
int main()
{
    cin>>n>>m;
    for(int x=1;x<=n;x++)cin>>a[x];
    for(int x=n;x>0;x--){//从后向前枚举 
        if(!k[a[x]])s[x]=s[x+1]+1;//优化
        else s[x]=s[x+1];
        k[a[x]]=1;
    }
    for(int x=1;x<=m;x++)cin>>l,cout<<s[l]<<endl;
    return 0;
}
```
    - **核心实现思想**：从后往前遍历数组，若当前数字未在后续出现过（通过map判断），则当前位置到数组末尾不同数字个数比下一个位置多1，否则相同，最后根据询问直接输出对应位置记录的不同数字个数。
 - **作者：Melon_Musk (4星)**
    - **关键亮点**：题解结构清晰，先给出题目链接和博客链接，再描述题面和分析思路。同样从后往前维护数组 $sum$ 表示从 $i$ 到 $n$ 区间不同数字个数，使用map判断数字是否出现，代码完整且有注释。
    - **个人心得**：无
    - **重点代码**：
```cpp
int n,m;
int a[maxn],sum[maxn];
map<int,int> mp;
int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=n;i;i--) 
        if(!mp[a[i]]) 
        {
            mp[a[i]]=1;
            sum[i]=sum[i+1]+1;
        }
        else 
            sum[i]=sum[i+1];
    for(int i=1;i<=m;i++)
    {
        int l=read();
        printf("%d\n",sum[l]);
    }
    return 0;
}
```
    - **核心实现思想**：从后往前遍历数组，若当前数字未在map中出现过，则更新map并使当前位置的 $sum$ 值比下一个位置多1，否则 $sum$ 值不变，最后根据询问输出对应 $sum$ 值。
 - **作者：Eason_AC (4星)**
    - **关键亮点**：详细阐述了dp思路，从暴力解法的不足引入，定义 $dp_i$ 为 $[i,n]$ 内不同数字个数，给出边界条件和状态转移方程，并结合样例详细解释dp过程，核心代码部分简洁明了。
    - **个人心得**：无
    - **重点代码**：
```cpp
f[n] = 1;
vis[a[n]] = 1;
for(int i = n - 1; i >= 1; --i) {
    if(!vis[a[i]]) {
        f[i] = f[i + 1] + 1;
        vis[a[i]] = 1;
    } else f[i] = f[i + 1];
}
```
    - **核心实现思想**：初始化 $dp_n$ 为1，从后往前遍历数组，若当前数字未出现过（通过 $vis$ 数组判断），则 $dp_i$ 比 $dp_{i + 1}$ 多1并更新 $vis$ 数组，否则 $dp_i$ 与 $dp_{i + 1}$ 相同。

### 最优关键思路或技巧
从后往前遍历数组进行预处理，利用辅助数组或map记录数字出现情况，递推计算每个位置到数组末尾不同数字的个数，从而将每次询问的时间复杂度降为 $O(1)$。

### 可拓展思路
同类型题通常围绕区间内不同元素的统计问题，类似算法套路是根据题目特点选择合适的数据结构辅助记录元素出现情况，通过预处理减少重复计算。例如，若数据范围更大，可能需使用更高效的数据结构如哈希表等。

### 洛谷题目推荐
 - [P1972 [SDOI2009]HH的项链](https://www.luogu.com.cn/problem/P1972)：同样是统计区间内不同元素个数，但涉及排序处理离线询问的技巧。
 - [P3959 [NOIP2017 提高组] 宝藏](https://www.luogu.com.cn/problem/P3959)：虽然不是直接统计不同元素个数，但在求解过程中需要类似的预处理和状态记录思想。
 - [P4137 Rmq Problem / mex](https://www.luogu.com.cn/problem/P4137)：与本题类似，需处理区间内的特定统计问题，可锻炼类似的思维方式。

### 个人心得摘录与总结
无

---
处理用时：68.99秒