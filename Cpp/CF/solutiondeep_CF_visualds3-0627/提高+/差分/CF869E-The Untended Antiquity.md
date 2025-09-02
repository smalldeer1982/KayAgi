# 题目信息

# The Untended Antiquity

## 题目描述

Adieu l'ami.

Koyomi is helping Oshino, an acquaintance of his, to take care of an open space around the abandoned Eikou Cram School building, Oshino's makeshift residence.

The space is represented by a rectangular grid of $ n×m $ cells, arranged into $ n $ rows and $ m $ columns. The $ c $ -th cell in the $ r $ -th row is denoted by $ (r,c) $ .

Oshino places and removes barriers around rectangular areas of cells. Specifically, an action denoted by " $ 1\ r_{1}\ c_{1}\ r_{2}\ c_{2} $ " means Oshino's placing barriers around a rectangle with two corners being $ (r_{1},c_{1}) $ and $ (r_{2},c_{2}) $ and sides parallel to squares sides. Similarly, " $ 2\ r_{1}\ c_{1}\ r_{2}\ c_{2} $ " means Oshino's removing barriers around the rectangle. Oshino ensures that no barriers staying on the ground share any common points, nor do they intersect with boundaries of the $ n×m $ area.

Sometimes Koyomi tries to walk from one cell to another carefully without striding over barriers, in order to avoid damaging various items on the ground. " $ 3\ r_{1}\ c_{1}\ r_{2}\ c_{2} $ " means that Koyomi tries to walk from $ (r_{1},c_{1}) $ to $ (r_{2},c_{2}) $ without crossing barriers.

And you're here to tell Koyomi the feasibility of each of his attempts.

## 说明/提示

For the first example, the situations of Koyomi's actions are illustrated below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF869E/5930e5689d91726564d05581955bbc9acf5a8c98.png)

## 样例 #1

### 输入

```
5 6 5
1 2 2 4 5
1 3 3 3 3
3 4 4 1 1
2 2 2 4 5
3 1 1 4 4
```

### 输出

```
No
Yes
```

## 样例 #2

### 输入

```
2500 2500 8
1 549 1279 1263 2189
1 303 795 1888 2432
1 2227 622 2418 1161
3 771 2492 1335 1433
1 2017 2100 2408 2160
3 48 60 798 729
1 347 708 1868 792
3 1940 2080 377 1546
```

### 输出

```
No
Yes
No
```

# AI分析结果



## 算法分类
二维树状数组 + 哈希

---

## 综合分析与结论

### 核心算法流程
1. **区域哈希标记**：为每个矩形障碍生成唯一随机哈希值，通过二维树状数组进行差分式的区域加减。
2. **动态维护哈希和**：添加障碍时在矩形四角执行哈希值加减，移除时反向操作撤销哈希值。
3. **连通性判断**：查询两点哈希和是否相等，等价于两点被相同障碍集合包围。

### 解决难点
- **动态覆盖判定**：利用哈希值的唯一性和树状数组的高效性，解决动态二维区域覆盖判断问题。
- **冲突避免**：通过随机哈希或大基数进制数（如691^4）确保不同障碍组合的哈希和几乎不冲突。

### 可视化设计
- **像素网格动画**：用Canvas绘制n×m网格，添加障碍时用半透明色块覆盖矩形区域，移除时擦除色块。
- **哈希值动态显示**：点击网格点时显示当前哈希和，查询时用闪烁箭头连接两点并显示比较结果。
- **音效设计**：添加障碍时播放"咔嗒"声，成功查询播放上升音阶，失败播放低沉音效。
- **自动演示模式**：按时间线自动执行样例操作，用慢速分步展示哈希值的扩散与抵消过程。

---

## 题解清单（≥4星）

### 1. daniEl_lElE（5星）
- **亮点**：随机哈希+二维树状数组，代码简洁高效。利用STL map管理哈希生命周期。
- **核心代码**：
  ```cpp
  map<pair<pair<int,int>,pair<int,int>>,int> mp;
  void change(int x1,int y1,int x2,int y2,int c){
      tree.chang(x1,y1,c); tree.chang(x1,y2+1,-c);
      tree.chang(x2+1,y1,-c); tree.chang(x2+1,y2+1,c);
  }
  ```

### 2. Aleph1022（4星）
- **亮点**：自研691进制哈希解决冲突，无需依赖随机数生成器，适合确定性场景。
- **关键优化**：哈希函数设计为`x1 + y1*691 + x2*691^2 + y2*691^3`，保证不同矩形哈希值唯一。

### 3. Claire0918（4星）
- **亮点**：严谨数学证明连通性等价条件，采用双哈希（随机数+大质数）进一步降低冲突概率。
- **代码特色**：独立封装树状数组结构体，增强可读性。

---

## 最优思路提炼

### 关键技巧
1. **二维差分哈希**：将矩形区域操作转化为四个角点的加减操作，通过前缀和实现区域哈希标记。
   ```math
   \Delta(x1,y1)=+v,\ \Delta(x1,y2+1)=-v,\ \Delta(x2+1,y1)=-v,\ \Delta(x2+1,y2+1)=+v
   ```
2. **随机化抗冲突**：使用mt19937生成64位随机数作为哈希值，冲突概率可忽略不计。
3. **惰性删除**：通过map记录哈希值，删除时直接取反操作，无需维护复杂生命周期。

---

## 相似题目推荐
1. **P4514 上帝造题的七分钟**（二维区间操作+前缀和）
2. **P3810 【模板】三维偏序（CDQ分治）**（高维区域统计）
3. **P1972 [SDOI2009] HH的项链**（区间唯一性判断）

---

## 复古游戏化动画示例（伪代码）

```javascript
// Canvas初始化
const grid = new PixelGrid(2500, 2500, {scale: 0.2}); // 按比例缩小显示
const sound = new Chiptune({add: 'beep1', remove: 'beep2', success: 'fanfare'});

// 障碍操作动画
function animateObstacle(x1, y1, x2, y2, color) {
  grid.fillRect(x1, y1, x2, y2, color, 0.3); // 半透明色块
  grid.blinkCorners(x1, y1, x2, y2);         // 四角闪烁表示差分操作
  sound.play('add');
}

// 查询动画
function animateQuery(x1, y1, x2, y2) {
  const p1 = grid.highlight(x1, y1, 'red');
  const p2 = grid.highlight(x2, y2, 'blue');
  const sum1 = tree.query(x1, y1), sum2 = tree.query(x2, y2);
  if(sum1 === sum2) {
    grid.drawPath(p1, p2); // 显示虚拟连通路径
    sound.play('success');
  } else {
    grid.shake(p1, p2);   // 震动效果表示不可达
    sound.play('fail');
  }
}
```

---

## 核心代码实现

**daniEl_lElE的树状数组实现**
```cpp
struct bit{
    int f[2505][2505];
    void chang(int x,int y,int c){
        for(int i=x;i<=n;i+=lowbit(i)) 
            for(int j=y;j<=m;j+=lowbit(j)) 
                f[i][j]+=c;
    }
    int qry(int x,int y){
        int ans=0;
        for(int i=x;i;i-=lowbit(i))
            for(int j=y;j;j-=lowbit(j))
                ans+=f[i][j];
        return ans;
    }
    void change(int x1,int y1,int x2,int y2,int c){
        chang(x1,y1,c);
        chang(x1,y2+1,-c);
        chang(x2+1,y1,-c);
        chang(x2+1,y2+1,c);
    }
}tree;
```

---
处理用时：71.65秒