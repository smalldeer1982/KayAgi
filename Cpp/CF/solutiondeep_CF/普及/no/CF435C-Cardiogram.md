# 题目信息

# Cardiogram

## 题目描述

In this problem, your task is to use ASCII graphics to paint a cardiogram.

A cardiogram is a polyline with the following corners:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF435C/f0f02d0c7c83e26a44852403071814a1b9513d4c.png)That is, a cardiogram is fully defined by a sequence of positive integers $ a_{1},a_{2},...,a_{n} $ .

Your task is to paint a cardiogram by given sequence $ a_{i} $ .

## 说明/提示

Due to the technical reasons the answers for the samples cannot be copied from the statement. We've attached two text documents with the answers below.

http://assets.codeforces.com/rounds/435/1.txt

http://assets.codeforces.com/rounds/435/2.txt

## 样例 #1

### 输入

```
5
3 1 2 5 1
```

### 输出

```
     <span class="tex-span"> / </span><span class="tex-span">\</span>     
  <span class="tex-span"> / </span><span class="tex-span">\</span><span class="tex-span"> / </span>  <span class="tex-span">\</span>    
 <span class="tex-span"> / </span>      <span class="tex-span">\</span>   
<span class="tex-span"> / </span>        <span class="tex-span">\</span>  
          <span class="tex-span">\</span><span class="tex-span"> / </span>
```

## 样例 #2

### 输入

```
3
1 5 1
```

### 输出

```
<span class="tex-span"> / </span><span class="tex-span">\</span>     
  <span class="tex-span">\</span>    
   <span class="tex-span">\</span>   
    <span class="tex-span">\</span>  
     <span class="tex-span">\</span><span class="tex-span"> / </span>
```

# AI分析结果



【中文题目】
# 心电图表

## 题目描述

你的任务是使用ASCII图形绘制一个心电图表。心电图表由一系列正整数序列 $ a_{1},a_{2},...,a_{n} $ 定义，其折线图的拐点如下所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF435C/f0f02d0c7c83e26a44852403071814a1b9513d4c.png)

## 输入输出样例

### 样例 #1
输入：
```
5
3 1 2 5 1
```
输出：
（见原题样例的特殊符号格式）

### 样例 #2
输入：
```
3
1 5 1
```
输出：
（见原题样例的特殊符号格式）

【算法分类】模拟

---

【题解分析与结论】
本题需模拟折线绘制过程，核心在于：
1. 方向交替变化（奇偶位不同）
2. 坐标范围动态维护
3. 二维字符数组的空间管理

题解对比要点：
- 唯一题解采用二维数组预存图形，通过坐标平移处理负索引问题
- 维护当前行范围（mu/md）实现高效输出
- 时间复杂度由总步长决定，符合题目约束

---

【优质题解推荐】
⭐️⭐️⭐️⭐️⭐️ 作者：loser_seele
关键亮点：
1. 坐标平移技巧避免负索引
2. 行范围动态维护优化输出空间
3. 清晰的字符填充逻辑
个人心得："一个不难想但不好写的小模拟题"（实现细节较多）

核心代码思想：
```cpp
char ans[2010][2000]; // 二维字符画布
int x=1000,y=0;       // 坐标平移基准点

void paint(int d,int u) {
    ans[x][++y] = u>0 ? '/' : '\\';  // 绘制起点
    for(int i=1; i<d; i++) {         // 绘制后续线段
        y++;
        x += u;
        ans[x][y] = u>0 ? '/' : '\\';
        mu = min(mu,x);  // 维护最小行
        md = max(md,x);  // 维护最大行
    }
}

// 主循环按行范围输出
for(x=md; x>=mu; x--) {
    for(int j=1; j<=y; j++)
        printf("%c",ans[x][j]);
    puts("");
}
```

---

【关键技巧总结】
1. **坐标平移**：通过固定偏移（如+1000）处理负坐标
2. **行范围跟踪**：动态更新最小/最大行避免全数组遍历
3. **先存后输**：先构建完整二维图形再按需输出

---

【拓展训练推荐】
1. P1496 火烧赤壁（坐标离散化）
2. P1001 谁拿了最多奖学金（多条件模拟）
3. P1057 传球游戏（状态转移模拟）

---
处理用时：43.59秒