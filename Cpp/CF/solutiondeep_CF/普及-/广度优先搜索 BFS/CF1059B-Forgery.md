# 题目信息

# Forgery

## 题目描述

Student Andrey has been skipping physical education lessons for the whole term, and now he must somehow get a passing grade on this subject. Obviously, it is impossible to do this by legal means, but Andrey doesn't give up. Having obtained an empty certificate from a local hospital, he is going to use his knowledge of local doctor's handwriting to make a counterfeit certificate of illness. However, after writing most of the certificate, Andrey suddenly discovered that doctor's signature is impossible to forge. Or is it?

For simplicity, the signature is represented as an $ n\times m $ grid, where every cell is either filled with ink or empty. Andrey's pen can fill a $ 3\times3 $ square without its central cell if it is completely contained inside the grid, as shown below.

 `<br></br>xxx<br></br>x.x<br></br>xxx<br></br>`Determine whether is it possible to forge the signature on an empty $ n\times m $ grid.

## 说明/提示

In the first sample Andrey can paint the border of the square with the center in $ (2, 2) $ .

In the second sample the signature is impossible to forge.

In the third sample Andrey can paint the borders of the squares with the centers in $ (2, 2) $ and $ (3, 2) $ :

1. we have a clear paper: `<br></br>...<br></br>...<br></br>...<br></br>...<br></br>`
2. use the pen with center at $ (2, 2) $ . `<br></br>###<br></br>#.#<br></br>###<br></br>...<br></br>`
3. use the pen with center at $ (3, 2) $ . `<br></br>###<br></br>###<br></br>###<br></br>###<br></br>`

In the fourth sample Andrey can paint the borders of the squares with the centers in $ (3, 3) $ and $ (3, 5) $ .

## 样例 #1

### 输入

```
3 3
###
#.#
###
```

### 输出

```
YES```

## 样例 #2

### 输入

```
3 3
###
###
###
```

### 输出

```
NO```

## 样例 #3

### 输入

```
4 3
###
###
###
###
```

### 输出

```
YES```

## 样例 #4

### 输入

```
5 7
.......
.#####.
.#.#.#.
.#####.
.......
```

### 输出

```
YES```

# AI分析结果



# Forgery（伪造签名）

## 题目描述

学生Andrey整个学期都在逃体育课，现在他必须想办法通过这门课。显然通过合法途径不可能实现，但他没有放弃。拿到当地医院的空白证明后，他打算利用对医生笔迹的了解伪造一份疾病证明。然而在写完大部分内容后，Andrey突然发现医生的签名根本无法伪造。真的吗？

为简化问题，签名表示为一个$n \times m$的网格，每个格子要么涂墨要么空白。Andrey的笔可以在完全位于网格内的$3 \times 3$区域（不含中心点）进行涂墨，效果如下：

```
xxx
x.x
xxx
```

判断是否能在空白网格上伪造出目标签名。

## 样例分析

样例1：可以中心点(2,2)涂色  
样例2：无法伪造  
样例3：通过中心点(2,2)和(3,2)两次涂色  
样例4：中心点(3,3)和(3,5)两次涂色

---

## 题解综合分析

### 关键算法思路
所有题解均采用**逆向构造法**：  
1. 创建空白画布模拟涂色过程  
2. 枚举每个可能作为3×3印章中心的位置  
3. 当目标图案中该位置的8邻域全为#时，在模拟画布执行涂色  
4. 最终比对模拟画布与目标图案是否一致

### 优化技巧
- **边界约束**：中心点坐标范围限制为[2, n-1]×[2, m-1]避免越界检查  
- **方向数组**：预定义8邻域偏移量简化代码  
- **即时标记**：使用二维数组直接记录可涂色区域，无需回溯

---

## 精选题解（评分4★+）

### 1. 作者：Abyss_Bright（4.5★）
**亮点**：  
- 双数组比对逻辑清晰  
- 采用8方向偏移量枚举邻域  
- 完整处理边界条件判断

```cpp
// 核心判断逻辑
for(int x=1;x<=n;x++) {
    for(int y=1;y<=m;y++) {
        bool valid = true;
        // 检查8邻域是否全为#且不越界
        for(int z=0;z<8;z++) {
            int mx = x+dx[z], my = y+dy[z];
            if(mx越界 || 目标[mx][my] != '#') valid = false;
        }
        if(valid) 执行涂色
    }
}
```

### 2. 作者：氢氧化铯CsOH（4.2★）
**亮点**：  
- 使用vis数组记录实际覆盖情况  
- 坐标转换更直观  
- 代码简洁无冗余

```cpp
// 关键覆盖判断
bool all(int x, int y) {
    for(8邻域检查) 
        if(越界或非#) return false;
    return true;
}
// 最终验证
for(所有格子)
    if(目标为#但未被覆盖) return false
```

### 3. 作者：「已注销」（4.0★）
**亮点**：  
- 直接操作字符串减少转换  
- 使用偏移量数组精准定位  
- 代码结构紧凑

```cpp
// 涂色操作
for(int i=1;i<=n-2;i++)
    for(int j=0;j<m-2;j++)
        if(8邻域全为#)
            for(所有偏移点) 涂色
```

---

## 同类题目推荐
1. [P1731 生日蛋糕](https://www.luogu.com.cn/problem/P1731) - 三维空间构造  
2. [P3395 路障](https://www.luogu.com.cn/problem/P3395) - 棋盘覆盖策略  
3. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443) - 方向数组与BFS  

---

## 调试心得摘录

1. **边界陷阱**：  
   "中心点必须距边界至少1格，否则会越界涂色"——多题解作者强调坐标范围限制

2. **逆向思维**：  
   "不必模拟真实涂色顺序，只需证明所有#都能被某个操作覆盖"——Forever1507题解核心思路

3. **效率对比**：  
   "深搜无论在时间还是空间上都劣不少，仅供参考"——Forever1507对比枚举与DFS的实践结论

---
处理用时：60.21秒