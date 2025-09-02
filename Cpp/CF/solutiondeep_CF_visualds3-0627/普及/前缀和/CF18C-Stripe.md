# 题目信息

# Stripe

## 题目描述

Once Bob took a paper stripe of $ n $ squares (the height of the stripe is 1 square). In each square he wrote an integer number, possibly negative. He became interested in how many ways exist to cut this stripe into two pieces so that the sum of numbers from one piece is equal to the sum of numbers from the other piece, and each piece contains positive integer amount of squares. Would you help Bob solve this problem?

## 样例 #1

### 输入

```
9
1 5 -6 7 9 -16 0 -2 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3
1 1 1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
2
0 0
```

### 输出

```
1
```

# AI分析结果



# 算法分类
前缀和

# 综合分析与结论
## 核心思路与难点
题目要求在数组中找到分割点，使左右两部分和相等。关键点在于高效计算各分割点的左右和。暴力枚举时间复杂度O(n²)不可行，正确解法采用前缀和或动态维护总和，将复杂度优化至O(n)。

**核心算法步骤**：
1. 预处理前缀和数组（或直接维护总和）
2. 遍历所有有效分割点（i从1到n-1）
3. 通过前缀和或动态计算左右部分和，判断是否相等

**可视化设计要点**：
- Canvas绘制数组元素，分割线左右用不同颜色高亮
- 动态显示前缀和数值与当前分割点位置
- 符合条件时触发像素特效与音效反馈
- 复古8-bit风格界面，步进速度可调节

# 题解清单（≥4星）
1. **zhangyuhan（5星）**  
   简洁高效的前缀和解法，正确遍历分割点范围，代码可读性强

2. **loi_hjh（4星）**  
   动态维护左右和，空间优化至O(1)，无需前缀和数组

3. **06ray（4星）**  
   标准前缀和实现，代码简短且注释清晰

# 最优思路提炼
**关键技巧**：
- **前缀和的降维打击**：通过预处理将区间和计算降为O(1)
- **动态维护法**：左右和实时更新，避免存储整个前缀和数组
- **数学等价转换**：判断条件用乘法（s[i]*2 == sum）避免浮点误差

```cpp
// 动态维护法核心代码
int sum = accumulate(arr, arr+n, 0);
int left = 0, ans = 0;
for(int i=0; i<n-1; ++i){
    left += arr[i];
    if(left * 2 == sum) ans++;
}
```

# 同类型题目推荐
1. P1115 最大子段和（一维区间极值）
2. P3131 七的倍数（前缀和模运算）
3. CF1003C 温度极值（二维前缀和应用）

# 可视化算法演示
**动画设计**：
1. 初始化阶段显示完整数组与总和
2. 分割线从左至右移动，实时计算左右和
3. 符合条件时触发像素爆炸特效与"ding"音效
4. 控制面板支持暂停/倍速/重置

**复古元素**：
- 8-bit风格数字字体
- 芯片音效（移动、匹配成功）
- 背景音乐：FC游戏《超级玛丽》水下关卡remix

# 题解代码精选
```cpp
// 空间最优解（loi_hjh）
#include<cstdio>
int main(){
    int n,a[1000001],sum=0,ans=0;
    scanf("%d",&n);
    for(int i=0;i<n;++i) scanf("%d",a+i), sum+=a[i];
    for(int i=0,left=0;i<n-1;++i){
        left += a[i];
        if(left*2 == sum) ans++;
    }
    printf("%d",ans);
}
```

---
处理用时：181.50秒