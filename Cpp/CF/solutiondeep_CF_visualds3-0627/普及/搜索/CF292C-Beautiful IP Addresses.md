# 题目信息

# Beautiful IP Addresses

## 题目描述

The problem uses a simplified TCP/IP address model, please read the statement carefully.

An IP address is a 32-bit integer, represented as a group of four decimal 8-bit integers (without leading zeroes), separated by commas. For example, record 0.255.1.123 shows a correct IP address and records 0.256.1.123 and 0.255.1.01 do not. In the given problem an arbitrary group of four 8-bit integers is a correct IP address.

Our hero Polycarpus still works as a system administrator in some large corporation. He likes beautiful IP addresses. To check if some IP address is beautiful, he should do the following:

1. write out in a line four 8-bit numbers of the IP address, without the commas;
2. check if the resulting string is a palindrome.

Let us remind you that a palindrome is a string that reads the same from right to left and from left to right.

For example, IP addresses 12.102.20.121 and 0.3.14.130 are beautiful (as strings "1210220121" and "0314130" are palindromes), and IP addresses 1.20.20.1 and 100.4.4.1 are not.

Polycarpus wants to find all beautiful IP addresses that have the given set of digits. Each digit from the set must occur in the IP address at least once. IP address must not contain any other digits. Help him to cope with this difficult task.

## 样例 #1

### 输入

```
6
0 1 2 9 8 7
```

### 输出

```
6
78.190.209.187
79.180.208.197
87.190.209.178
89.170.207.198
97.180.208.179
98.170.207.189
```

## 样例 #2

### 输入

```
1
4
```

### 输出

```
16
4.4.4.4
4.4.4.44
4.4.44.4
4.4.44.44
4.44.4.4
4.44.4.44
4.44.44.4
4.44.44.44
44.4.4.4
44.4.4.44
44.4.44.4
44.4.44.44
44.44.4.4
44.44.4.44
44.44.44.4
44.44.44.44
```

# AI分析结果



## 唯一算法分类：DFS

### 题解思路与算法要点
各题解核心思路均为**DFS生成回文前半部分+回文对称生成后半部分+IP分段合法性检查**。关键要点如下：
1. **回文对称性**：仅需枚举前一半字符（长度4~12），后一半通过镜像生成，极大减少搜索空间
2. **数字覆盖检查**：使用位掩码（bitmask）记录必须使用的数字集合，DFS过程中维护已用数字集合，最终比对掩码确保全用
3. **IP分段合法性**：三重循环枚举分割点位置，检查每段数值范围（0~255）及前导零情况

### 解决难点对比
| 题解 | 回文生成方式 | 数字校验方法 | IP分割策略 | 优化点 |
|------|--------------|--------------|------------|--------|
| jdsb | DFS生成前半，后半自动镜像 | 位掩码动态维护 | 三重循环枚举分割点 | 二进制状态压缩 |
| HaneDaniko | 先构造完整回文数组再分割 | 数组遍历统计 | 四段全排列枚举 | 回文构造与IP分割解耦 |
| GavinCayne | 分步生成四段地址 | 回溯标记数组 | 递归生成每段位数 | 动态计算地址长度 |

### 精炼结论
最优解法为**jdsb的DFS+位掩码方案**：  
1. 二进制记录必须使用的数字集合，DFS时同步更新已用数字  
2. 仅生成回文前半部分，镜像生成后半，时间复杂度O(4^6)  
3. 分割检查时通过substr快速切分，check函数双重验证数值与前导零

---

### 题解评分（≥4星）
1. **jdsb（★★★★☆）**  
   - 亮点：二进制状态压缩、清晰的分割点检查逻辑  
   - 优化：利用回文对称性将搜索空间降低至O(4^6)  
   - 代码示例：
```cpp
void dfs(int k,int maxk,string s,int use) {
    if(k==maxk) { if(use==flag) solve(s); return; }
    if(k*2>maxk-1) { // 后半镜像生成
        if(use!=flag) return;
        dfs(k+1,maxk,s+s[maxk-k-1],use);
        return;
    }
    for(int i=0;i<=9;i++) // 枚举可用数字
        if(flag&(1<<i)) 
            dfs(k+1,maxk,s+char(i+'0'),use|(1<<i));
}
```

2. **dzk_QwQ（★★★★☆）**  
   - 亮点：详细注释、独立check函数模块化设计  
   - 优化：前导零判断与数值转换合并处理

3. **a_123_a（★★★★☆）**  
   - 亮点：双思路对比、预处理合法数值集合  
   - 创新：第二思路通过预处理255内合法值加速搜索

---

### 可视化算法设计
**复古像素风格演示：**  
1. **Canvas布局**：  
   - 顶部显示当前生成的半回文串（绿色像素块）  
   - 中部动态镜像生成后半（灰色像素块闪烁）  
   - 底部展示IP分割过程（红/蓝交替标记分割点）

2. **音效设计**：  
   - 每生成一个字符播放8-bit "beep"声  
   - 合法分割时播放马里奥金币音效  
   - 发现前导零时播放警告低音

3. **交互控制**：  
   - 方向键控制DFS分支选择  
   - 空格键暂停/继续，F1查看当前位掩码状态  
   - 自动演示模式：AI模拟最优DFS路径

---

### 相似题目推荐
1. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)  
   （DFS+状态压缩的回溯应用）

2. [P1433 吃奶酪](https://www.luogu.com.cn/problem/P1433)  
   （状态压缩DP与排列生成）

3. [P1019 单词接龙](https://www.luogu.com.cn/problem/P1019)  
   （字符串回文特性与DFS剪枝）

---
处理用时：64.55秒