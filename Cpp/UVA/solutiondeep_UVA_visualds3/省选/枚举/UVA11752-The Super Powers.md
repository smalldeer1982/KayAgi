# 题目信息

# The Super Powers

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=117&page=show_problem&problem=2852

[PDF](https://uva.onlinejudge.org/external/117/p11752.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11752/caccb369bd9149203faf09eaf595e5873b362929.png)

## 样例 #1

### 输入

```
```

### 输出

```
1
16
64
81
256
512
.
.
.```

# AI分析结果



## 算法分类
**数学推导与枚举优化**

---

## 题解思路与算法分析

### 核心思路
题目要求找出所有能表示为不同指数幂的超级数。通过数学推导发现，超级数必须能表示为某个数的**合数次幂**。例如，64=2⁶=8²，其中6是合数。因此，算法核心为：

1. **筛出所有可能的合数指数**（如4,6,8,9等）
2. **枚举底数**，计算其合数次幂并去重
3. **处理数值溢出**，使用`__int128`存储中间结果

### 解决难点
- **合数判定**：通过线性筛法预处理4~64范围内的合数，快速判断指数是否合法
- **溢出处理**：在计算过程中使用`__int128`，及时截断超过2^64-1的数值
- **高效枚举**：底数上限为2^16（因2^16^4=2^64），保证枚举范围合理

### 可视化设计要点
- **像素风格动画**：在Canvas网格中展示底数i从2开始增长，每个i对应一列，右侧显示当前枚举的指数j
- **高亮关键操作**：
  - 当前计算的i^j用黄色方块闪烁
  - 溢出时显示红色警告标记
  - 合法结果加入结果列表时绿色高亮
- **音效反馈**：
  - 计算成功：短促“滴”声
  - 溢出：低音“咚”声
  - 去重：清脆“咔嗒”声
- **自动演示模式**：以恒定速度枚举i和j，展示完整计算流程

---

## 高分题解推荐（≥4星）

### 1. Milthm（★★★★☆）
- **亮点**：
  - 使用线性筛法高效预处理合数
  - 精确控制枚举范围（i≤65537）
  - 清晰的溢出判断逻辑`if(qwq>=...)break`
  - 简洁的去重实现（排序+相邻比较）
- **代码关键优化**：
  ```cpp
  for(int i=2;i<=65537;++i){
    __int128 qwq=i;
    for(int j=2;j<=100;++j){
        qwq*=i;
        if(qwq>=((__int128)1)<<64)break;
        if(a[j])ans[++cnt]=qwq; // a[j]为合数标记
    }
  }
  ```

### 2. dingshengyang（★★★★☆）
- **亮点**：
  - 预处理2^64边界值`MAXULL`
  - 使用vector存储结果，直接调用STL去重
  - 显式处理1的特殊情况
- **关键实现**：
  ```cpp
  __int128_t tmp =t*t*t*t; // 初始化为i^4
  for(int j=4;j<=64;++j){
      if(tmp > MAXULL)break;
      if(st[j]) vec.push_back(tmp); // st[j]为合数标记
      tmp *= t;
  }
  ```

### 3. 封禁用户（★★★★☆）
- **亮点**：
  - 采用set自动去重
  - 对数运算优化枚举上限`t=qwq/log(i)`
  - 独立函数判断合数
- **数学优化**：
  ```cpp
  ull t=qwq/log(i); // 计算最大可行指数
  for(ull j=4;j<=t;++j)
      if(OK(j)) // 合数判断
          ans.push(qp(i,j));
  ```

---

## 核心代码实现

### 线性筛法预处理合数
```cpp
bool isComposite[65] = {0}; // 标记4~64的合数
void sieve() {
    for(int i=2; i<=8; ++i) // 只需筛到√64
        if(!isComposite[i])
            for(int j=i*i; j<=64; j+=i)
                isComposite[j] = true;
}
```

### 主计算逻辑
```cpp
vector<unsigned long long> superNumbers;
for(int base=2; base<65536; ++base) {
    __int128 current = base;
    for(int exp=4; exp<=64; ++exp) {
        current *= base;
        if(current > ULLONG_MAX) break;
        if(isComposite[exp])
            superNumbers.push_back(current);
    }
}
superNumbers.push_back(1); // 添加特例1
sort(superNumbers.begin(), superNumbers.end());
superNumbers.erase(unique(superNumbers.begin(), superNumbers.end()), end);
```

---

## 相似题目推荐
1. **P1226 【模板】快速幂** - 快速计算幂次
2. **P1469 找筷子** - 异或性质与数学推导
3. **P1061 数列** - 数论中的进制与幂次关系

---

## 可视化示例代码（JavaScript）
```javascript
// Canvas初始化
const canvas = document.getElementById('demo');
const ctx = canvas.getContext('2d');
let i = 2, j = 4;

function drawFrame() {
    ctx.clearRect(0, 0, 600, 400);
    // 绘制当前底数i
    ctx.fillStyle = '#FFD700';
    ctx.fillRect(10 + i*2, 50, 20, 20); 
    // 绘制当前指数j
    ctx.fillStyle = '#00FF00';
    ctx.fillRect(10 + j*5, 100, 15, 15);
    // 触发计算音效
    playBeep(1000 + i*10);
    
    if(++j > 64) { j = 4; i++; }
    requestAnimationFrame(drawFrame);
}
// 启动动画
drawFrame();
```

---

## 总结提升
本题关键在于**数学性质转化**——将双重幂表示转化为单次合数幂。在类似问题中，应优先寻找数学规律简化问题，再结合高效枚举与边界处理。掌握`__int128`等大数处理技巧，可有效解决数值溢出难题。

---
处理用时：114.84秒