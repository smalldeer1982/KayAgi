# 题目信息

# Salary Changing

## 题目描述

You are the head of a large enterprise. $ n $ people work at you, and $ n $ is odd (i. e. $ n $ is not divisible by $ 2 $ ).

You have to distribute salaries to your employees. Initially, you have $ s $ dollars for it, and the $ i $ -th employee should get a salary from $ l_i $ to $ r_i $ dollars. You have to distribute salaries in such a way that the median salary is maximum possible.

To find the median of a sequence of odd length, you have to sort it and take the element in the middle position after sorting. For example:

- the median of the sequence $ [5, 1, 10, 17, 6] $ is $ 6 $ ,
- the median of the sequence $ [1, 2, 1] $ is $ 1 $ .

It is guaranteed that you have enough money to pay the minimum salary, i.e $ l_1 + l_2 + \dots + l_n \le s $ .

Note that you don't have to spend all your $ s $ dollars on salaries.

You have to answer $ t $ test cases.

## 说明/提示

In the first test case, you can distribute salaries as follows: $ sal_1 = 12, sal_2 = 2, sal_3 = 11 $ ( $ sal_i $ is the salary of the $ i $ -th employee). Then the median salary is $ 11 $ .

In the second test case, you have to pay $ 1337 $ dollars to the only employee.

In the third test case, you can distribute salaries as follows: $ sal_1 = 4, sal_2 = 3, sal_3 = 6, sal_4 = 6, sal_5 = 7 $ . Then the median salary is $ 6 $ .

## 样例 #1

### 输入

```
3
3 26
10 12
1 4
10 11
1 1337
1 1000000000
5 26
4 4
2 4
6 8
5 6
2 7
```

### 输出

```
11
1337
6
```

# AI分析结果



**唯一算法分类**  
二分

---

### **题解思路、算法要点与解决难点**  
**核心思路**：二分答案 + 贪心验证  
1. **二分框架**：  
   - 目标：最大化中位数，二分区间初始为 `[中间员工的左端点, 总预算 / 中位数位置数]`  
   - 判断条件：检查当前 mid 是否能作为中位数（需至少 `(n+1)/2` 人工资 ≥ mid）  
2. **贪心验证逻辑**：  
   - 将员工分为三类：  
     1. `r_i < mid` → 必选下界 `l_i`  
     2. `l_i > mid` → 必选下界 `l_i`（直接贡献到中位数右侧）  
     3. `l_i ≤ mid ≤ r_i` → 灵活选择 `l_i` 或 `mid`  
   - 优先处理第三类员工：  
     - 选择 `l_i` 最小的 `(n/2 - 左类数量)` 人支付 `l_i`，剩余支付 `mid`  
   - 总成本需 ≤ 预算且满足中位数条件  

**解决难点**：  
- 如何高效选择第三类员工的支付方式以最小化总成本  
- 正确统计满足条件的员工数量（避免漏判或误判）  
- 二分区间初始值的合理设定（如 `left = 中间员工左端点`）  

---

### **题解评分 (≥4星)**  
1. **Weakest_Konjac (4星)**  
   - **亮点**：分类清晰，注释详细，二分区间初始值合理  
   - **代码**：结构明确，排序后分类统计  
2. **灵茶山艾府 (4星)**  
   - **亮点**：预处理排序优化贪心，代码简洁高效（Golang 实现）  
   - **技巧**：按 `l_i` 从大到小排序，优先处理可支付 `mid` 的员工  
3. **HYXLE (4星)**  
   - **亮点**：逻辑与代码高度对应，边界条件处理严谨  
   - **优化**：预处理基础工资之和减少重复计算  

---

### **最优思路或技巧提炼**  
1. **二分答案框架**：  
   ```cpp  
   while (l <= r) {  
       mid = (l + r) / 2;  
       if (check(mid)) l = mid + 1;  
       else r = mid - 1;  
   }  
   ```  
2. **贪心验证核心代码**：  
   ```cpp  
   bool check(int mid) {  
       int cnt_low = 0, cnt_high = 0;  
       long long sum = 0;  
       vector<int> flexible;  
       // 分类统计  
       for (auto &e : employees) {  
           if (e.r < mid) { sum += e.l; cnt_low++; }  
           else if (e.l > mid) { sum += e.l; cnt_high++; }  
           else flexible.push_back(e.l);  
       }  
       // 处理灵活类  
       sort(flexible.begin(), flexible.end());  
       int need = (n/2) - cnt_low;  
       for (int i=0; i < flexible.size(); i++) {  
           if (i < need) sum += flexible[i];  
           else sum += mid;  
       }  
       return sum <= s && (cnt_high + flexible.size() - need) >= (n+1)/2;  
   }  
   ```  
3. **关键优化**：预处理按 `l_i` 排序，确保第三类员工的选择顺序  

---

### **同类型题或类似算法套路**  
- **二分答案**：适用于最值问题（如最大值最小化、最小值最大化）  
  - 例：木材加工（最大值最小）、跳石头（最小间距最大）  
- **贪心与排序结合**：通过排序简化决策，如区间调度、任务分配  

---

### **推荐相似题目**  
1. **P2678 跳石头**（二分最小跳跃距离）  
2. **P1182 数列分段**（二分最大段和最小化）  
3. **P4344 [SHOI2015] 脑洞治疗仪**（二分 + 复杂条件验证）  

---

### **个人心得摘录**  
- **Weakest_Konjac**：强调“排序后中间员工的左端点作为初始 left，避免无效搜索”  
- **灵茶山艾府**：“按 `l_i` 逆序排序，确保优先处理高潜力区间”  
- **HYXLE**：“预处理总基础工资，减少重复累加”  

---

### **可视化与算法演示**  
**动画设计**：  
1. **像素风格 Canvas**：  
   - 区间 `[left, right]` 显示为横向色块，mid 标记为高亮像素  
   - 每次收缩区间时，旧区间灰化，新区间闪烁  
2. **音效触发**：  
   - `mid` 更新：8-bit “哔”声  
   - 验证通过：上扬音效；失败：低沉音效  
3. **AI 自动演示**：  
   - 自动执行二分步骤，速度可调（0.5x~3x）  
   - 显示当前 `mid`、验证结果、剩余预算  

**核心 JS 片段**：  
```javascript  
function drawInterval(left, right, mid) {  
    ctx.clearRect(0, 0, canvas.width, canvas.height);  
    // 绘制区间 [left, right]  
    ctx.fillStyle = "#FF0000";  
    ctx.fillRect(left * scale, 0, (right-left)*scale, 50);  
    // 高亮 mid  
    ctx.fillStyle = "#00FF00";  
    ctx.fillRect(mid * scale - 2, 0, 4, 50);  
}  
```  

---

**总结**：二分答案 + 贪心验证是本题的核心，通过合理分类与排序优化验证过程。可视化设计通过复古风格与交互演示，直观展示二分收敛逻辑。

---
处理用时：71.41秒