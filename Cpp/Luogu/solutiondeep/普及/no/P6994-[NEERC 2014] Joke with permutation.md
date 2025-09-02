# 题目信息

# [NEERC 2014] Joke with permutation

## 题目描述

Joey had saved a permutation of integers from $1$ to $n$ in a text file. All the numbers were written as decimal numbers without leading spaces.

Then Joe made a practical joke on her: he removed all the spaces in the file.

Help Joey to restore the original permutation after the Joe's joke! 

## 说明/提示

Time limit: 1 s, Memory limit: 256 MB. 

Thanks to checker provider:@[Arcturus1350
](/user/57699).

## 样例 #1

### 输入

```
4111109876532
```

### 输出

```
4 1 11 10 9 8 7 6 5 3 2
```

# AI分析结果



**算法分类**  
深度优先搜索 DFS

---

**题解综合分析**  
所有题解均采用DFS+回溯算法，核心思路为：  
1. 通过字符串长度反推排列长度n  
2. 逐个尝试将当前字符解析为一位数或两位数  
3. 使用标记数组避免重复选择，及时剪枝  
4. 找到合法解后立即终止程序  

---

**精选题解列表**  

**1. 作者：Xu_Jinyi_2011（★★★★☆）**  
**关键亮点**  
- 精炼的n值计算公式  
- 使用`exit(0)`直接终止递归  
- 位运算优化字符转数字  
**核心代码**  
```cpp
void dfs(int it, int x) {
    if(x >= n) { // 终止条件
        for(int i=0;i<n;i++) cout<<a[i]<<' ';
        exit(0); // 立即退出
    }
    // 尝试一位数
    int digit = s[it] ^ 48;
    if(!b[digit] && digit <= n) {
        b[digit] = 1;
        dfs(it+1, x+1);
        b[digit] = 0;
    }
    // 尝试两位数
    int two_digit = digit*10 + (s[it+1]^48);
    if(it+1 < s.size() && two_digit <=n && !b[two_digit]) {
        b[two_digit] = 1;
        dfs(it+2, x+1);
        b[two_digit] = 0;
    }
}
```

**2. 作者：Disjoint_cat（★★★★☆）**  
**关键亮点**  
- 动态计算n的优雅实现  
- 通过字符串预处理简化索引操作  
- 函数式处理位数判断  
**核心代码**  
```cpp
for(;Ws < len; n++, Ws += WS(n)); // 动态计算n
void dfs(int dep, int pos) {
    if(dep > n) { // 终止条件
        if(pos == len+1) {
            for(int i=1;i<=n;i++) cout<<a[i]<<" ";
            exit(0);
        }
        return;
    }
    // 尝试不同长度的数字
    for(int t = s[pos]-'0'; pos <= len; t = t*10 + s[++pos]-'0') {
        if(t <= n && !used[t]) {
            used[t] = 1;
            dfs(dep+1, pos+1);
            used[t] = 0;
        }
    }
}
```

---

**关键技巧总结**  
1. **n值计算**：当字符串长度L≤9时n=L；否则n=9+(L-9)/2  
2. **剪枝优化**：  
   - 两位数必须≤n  
   - 使用`vis[]`数组避免重复选择  
3. **终止优化**：找到解后立即`exit(0)`而非层层回溯  

---

**拓展训练**  
1. [P1025 数的划分](https://www.luogu.com.cn/problem/P1025)  
   - 同类DFS剪枝应用  
2. [P1036 选数](https://www.luogu.com.cn/problem/P1036)  
   - 组合数生成+质数判断  
3. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)  
   - 经典DFS回溯问题  

---

**调试心得摘录**  
> *来自Xu_Jinyi_2011*  
> "半小时血与泪的教训：必须判断两位数是否≤n"  
> **总结**：边界条件验证是DFS的关键步骤  
> 
> *来自tiko_tao*  
> "数据开小居然是WA不是RE调死我了"  
> **总结**：数组越界可能表现为逻辑错误而非崩溃

---
处理用时：41.73秒