# 题目信息

# Add Modulo 10

## 题目描述

You are given an array of $ n $ integers $ a_1, a_2, \dots, a_n $

You can apply the following operation an arbitrary number of times:

- select an index $ i $ ( $ 1 \le i \le n $ ) and replace the value of the element $ a_i $ with the value $ a_i + (a_i \bmod 10) $ , where $ a_i \bmod 10 $ is the remainder of the integer dividing $ a_i $ by $ 10 $ .

For a single index (value $ i $ ), this operation can be applied multiple times. If the operation is applied repeatedly to the same index, then the current value of $ a_i $ is taken into account each time. For example, if $ a_i=47 $ then after the first operation we get $ a_i=47+7=54 $ , and after the second operation we get $ a_i=54+4=58 $ .

Check if it is possible to make all array elements equal by applying multiple (possibly zero) operations.

For example, you have an array $ [6, 11] $ .

- Let's apply this operation to the first element of the array. Let's replace $ a_1 = 6 $ with $ a_1 + (a_1 \bmod 10) = 6 + (6 \bmod 10) = 6 + 6 = 12 $ . We get the array $ [12, 11] $ .
- Then apply this operation to the second element of the array. Let's replace $ a_2 = 11 $ with $ a_2 + (a_2 \bmod 10) = 11 + (11 \bmod 10) = 11 + 1 = 12 $ . We get the array $ [12, 12] $ .

Thus, by applying $ 2 $ operations, you can make all elements of an array equal.

## 说明/提示

The first test case is clarified above.

In the second test case, it is impossible to make all array elements equal.

In the third test case, you need to apply this operation once to all elements equal to $ 5 $ .

In the fourth test case, you need to apply this operation to all elements until they become equal to $ 8 $ .

In the fifth test case, it is impossible to make all array elements equal.

In the sixth test case, you need to apply this operation to all elements until they become equal to $ 102 $ .

## 样例 #1

### 输入

```
10
2
6 11
3
2 18 22
5
5 10 5 10 5
4
1 2 4 8
2
4 5
3
93 96 102
2
40 6
2
50 30
2
22 44
2
1 5```

### 输出

```
Yes
No
Yes
Yes
No
Yes
No
No
Yes
No```

# AI分析结果



## 唯一算法分类
数学（数论）

## 综合分析与结论
本题核心在于观察数字末尾的变化规律，利用模运算判断所有元素能否收敛到同一值。关键思路如下：

1. **奇偶处理**：所有奇数经过一次操作后变为偶数，且无法变回奇数，需统一处理为偶数。
2. **特殊尾数处理**：尾数为0或5的数无法进入循环，需单独判断全等性。
3. **循环周期分析**：非0/5尾数会进入2→4→8→6的循环，每个循环周期总和增加20，故模20可判断同余性。

### 核心算法流程
1. 遍历数组，将奇数转为偶数。
2. 检查存在尾数0时是否全等。
3. 其他情况将所有数模20，检查可能的循环余数是否一致。

### 可视化设计思路
- **颜色标记**：用不同颜色区分奇数处理阶段、尾数0检测阶段、模20余数计算阶段。
- **步进动画**：展示每个数末尾变化轨迹，高亮当前操作位。
- **循环周期演示**：用环形动画展示2→4→8→6循环，每次循环增加20的标注。
- **同余判断面板**：实时显示模20后的余数分布，用饼图展示余数一致性。

## 题解清单（≥4星）
1. **EXODUS（4.5星）**  
   亮点：全面考虑所有尾数可能性，用桶记录所有可能余数。  
   代码亮点：详细处理每个尾数的4种余数可能性。

2. **I_am_Accepted（5星）**  
   亮点：简洁优雅的统一转换思路，将非0/5数统一到2的循环周期。  
   代码亮点：`calc`函数快速转换到尾数2或0。

3. **Dry_ice（4星）**  
   亮点：通过差值模20判断可行性，引入最大值比对思路。  
   代码亮点：`check`函数验证差值分解可行性。

## 最优思路提炼
**关键技巧**：  
1. **奇偶转换**：统一处理为偶数消除状态分支。
2. **尾数循环**：发现2→4→8→6循环周期，通过模20简化判断。
3. **同余分组**：模20后余数相同即可通过增加20的倍数达成相等。

## 同类型题目套路
类似数字变换问题可考虑：
1. 寻找循环周期规律
2. 分析模数的选择（如本题20）
3. 特殊边界值单独处理（如0/5尾数）

## 推荐题目
1. P1463 [POI2002]反素数（数论+循环性质）
2. P1012 拼数（数字重组+循环比较）
3. CF675C Money Transfers（环形数组+模运算）

## 个人心得摘录
> "通过手写数字变化轨迹，突然意识到循环周期总是增加20，这成为解题突破口" —— Dry_ice  
> "调试时发现尾数5的特殊情况必须单独处理，否则会漏判" —— xzy090626

## 代码实现（核心逻辑）
```cpp
// I_am_Accepted 题解核心代码
void calc(int &x){ while(x%10!=2 && x%10!=0) x += x%10; }

void work(){
    int n; cin >> n;
    vector<int> a(n);
    int cnt = 0;
    for(auto &x : a){
        cin >> x;
        if(x%5 == 0) cnt++;
        else calc(x); // 统一转换到尾数2或0
    }
    if(cnt && cnt != n) { cout << "NO\n"; return; }
    if(!cnt) for(auto &x : a) x %= 20; // 非0/5情况模20
    cout << (equal(a.begin()+1, a.end(), a.begin()) ? "YES" : "NO") << endl;
}
```

## 可视化方案设计
**8位像素风格演示器**：
```html
<canvas id="pixelCanvas"></canvas>
<script>
const CYCLES = [[2,4,8,6], [12,14,18,26]];
function drawCycle(ctx, x, y, type) {
    // 绘制2→4→8→6或12→14→18→26循环的像素动画
    // 使用不同颜色区分两种循环类型
}
function update() {
    // 步进操作演示，高亮当前数字变化
    // 播放操作音效：beep.mp3
}
</script>
```
- **交互功能**：方向键控制步进，空格暂停/继续
- **音效设计**：操作音效（8-bit beep），成功时播放胜利音效
- **自动演示**：按R键启动AI自动步进，模拟最优解题路径

**控制面板功能**：
- 速度滑块调节动画速度（50ms-2000ms）
- 高亮模式选择：当前操作位/循环路径/模20余数
- 对比模式：并行显示两种处理策略的差异

---
处理用时：105.16秒