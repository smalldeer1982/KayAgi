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



## 唯一算法分类
二维树状数组 + 哈希标记

---

## 题解思路与算法分析

### 核心思路
所有题解均基于**"两点连通性等价于覆盖它们的矩形集合相同"**的关键性质。通过为每个矩形分配唯一哈希值，利用二维树状数组进行差分标记，实现以下操作：
1. 添加矩形：对矩形区域叠加哈希值
2. 移除矩形：对相同区域逆向操作
3. 查询连通性：比较两点哈希和

### 解决难点
1. **哈希冲突问题**：使用随机数（daniEl_lElE）或高基数编码（Aleph1022）生成哈希值
2. **动态覆盖管理**：通过二维树状数组实现 O(log n log m) 的矩形区域更新
3. **操作可逆性**：用map记录已添加的哈希值，保证删除操作的正确性

### 算法流程
```python
for 每次操作:
    if 添加矩形:
        生成随机哈希值
        二维差分更新：矩形四角加减哈希值
    elif 移除矩形:
        查表获取原哈希值
        逆向差分操作
    else 查询:
        比较两坐标点的哈希和
```

---

## 题解评分（≥4星）

1. **daniEl_lElE（5星）**
   - 亮点：随机哈希+差分树状数组，代码简洁高效
   - 代码关键：`mt19937 rng`生成高质量随机数，树状数组四角差分

2. **Aleph1022（4.5星）**
   - 亮点：691进制编码解决哈希冲突，无依赖第三方库
   - 优化：哈希值由坐标组合生成，避免map存储

3. **Claire0918（4星）**
   - 亮点：严格数学证明连通性条件，双哈希保障
   - 特色：`map<pair<pair...>>` 结构化存储哈希值

---

## 最优技巧提炼

1. **差分哈希标记法**
   ```cpp
   void change(int x1,int y1,int x2,int y2,int val){
       add(x1,y1,val);        // 左上+
       add(x1,y2+1,-val);     // 左下-
       add(x2+1,y1,-val);     // 右上-
       add(x2+1,y2+1,val);    // 右下+
   }
   ```
2. **高基数哈希生成**
   ```cpp
   long long num = x1 + y1*691 + x2*691*691 + y2*691*691*691;
   ```
3. **双哈希校验**
   ```cpp
   struct Tree T1, T2; // 维护两个独立哈希树
   if(T1.query() == T2.query()) // 双校验通过才返回Yes
   ```

---

## 同类型题推荐

1. **P4514《上帝造题的七分钟》**  
   （二维区间操作，差分树状数组应用）

2. **P1901 发射站**  
   （二维区域覆盖问题，单调栈变种）

3. **P5490 矩形面积并**  
   （扫描线算法处理矩形覆盖）

---

## 代码实现（核心片段）

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2505;
mt19937_64 rng(time(0));

struct BIT {
    long long c[N][N];
    void update(int x, int y, long long v) {
        for(int i=x; i<N; i+=i&-i)
            for(int j=y; j<N; j+=j&-j)
                c[i][j] += v;
    }
    long long query(int x, int y) {
        long long res = 0;
        for(int i=x; i>0; i-=i&-i)
            for(int j=y; j>0; j-=j&-j)
                res += c[i][j];
        return res;
    }
    void rect(int x1,int y1,int x2,int y2,long long v){
        update(x1,y1,v); update(x1,y2+1,-v);
        update(x2+1,y1,-v); update(x2+1,y2+1,v);
    }
} T;

map<tuple<int,int,int,int>, long long> mp;

int main() {
    int n, m, q; cin >> n >> m >> q;
    while(q--) {
        int op,x1,y1,x2,y2; cin >> op >> x1 >> y1 >> x2 >> y2;
        if(op == 1) {
            long long h = rng();
            mp[make_tuple(x1,y1,x2,y2)] = h;
            T.rect(x1,y1,x2,y2,h);
        } else if(op == 2) {
            long long h = mp[make_tuple(x1,y1,x2,y2)];
            T.rect(x1,y1,x2,y2,-h);
        } else {
            cout << (T.query(x1,y1) == T.query(x2,y2) ? "Yes" : "No") << endl;
        }
    }
}
```

---

## 可视化设计

### 动画方案
1. **网格渲染**：16x16像素网格，障碍物用红色边框，路径点用绿色/蓝色填充
2. **树状数组更新**：以黄色高亮当前操作的四个差分点，显示数值变化
3. **哈希比较**：查询时两坐标点闪烁三次，相同则显示绿色连结线，不同显示红色叉

### 复古特效
```javascript
// 8-bit音效生成器
function beep(type) {
    const ctx = new AudioContext();
    const osc = ctx.createOscillator();
    osc.type = 'square';
    osc.frequency.value = type === 'success' ? 880 : 440;
    osc.connect(ctx.destination);
    osc.start(); osc.stop(ctx.currentTime + 0.1);
}
```

### 自动演示模式
```javascript
let autoStep = setInterval(() => {
    if(!nextStep()) clearInterval(autoStep); 
}, 1000); // 每秒执行一步操作
```

---

## 心得摘录

> "当使用树状数组四角差分时，必须确保删除操作与添加操作完全对称，否则残留的哈希值会导致错误判断。建议在调试时输出整个矩阵的哈希和验证对称性。" —— daniEl_lElE

> "二维问题的降维思考：将矩形操作分解为行处理虽然直观，但牺牲了时间复杂度。树状数组的二维差分才是真正的降维打击。" —— YuRuiH_

> "哈希冲突的概率比想象中要小得多，用双树状数组维护双哈希值后，在10^5次操作中未出现一次误判。" —— Felix72

---
处理用时：80.52秒