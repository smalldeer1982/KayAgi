# 题目信息

# [AGC018B] Sports Festival

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc018/tasks/agc018_b

高橋君は、スポーツ大会を開こうと考えています。 スポーツ大会に参加するのは、$ 1 $ から $ N $ までの番号のついた $ N $ 人の人です。 また、大会で行うスポーツとして、$ 1 $ から $ M $ までの番号のついた $ M $ 個のスポーツが候補に上がっています。 高橋君は、これらの中から $ 1 $ つ以上（全てでもよい）のスポーツを選んで、スポーツ大会で実施します。

高橋君は、人 $ i $ が、$ j $ 番目に好きなスポーツが $ A_{ij} $ であることを知っています。 それぞれの人は、スポーツ大会で実施されるスポーツのうち、自分が最も好きなスポーツだけに参加し、他のスポーツには参加しません。

高橋君は、一つのスポーツにたくさんの人が集まり過ぎることを懸念しています。 そこで高橋君は、スポーツ大会で実施するスポーツをうまく選んで、最も多くの人が参加しているスポーツの参加人数を最小化したくなりました。 最も多くの人が参加しているスポーツの参加人数の最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 300 $
- $ 1\ \leq\ M\ \leq\ 300 $
- $ A_{i1} $ , $ A_{i2} $ , $ ... $ , $ A_{iM} $ は、$ 1 $ から $ M $ の順列である。

### Sample Explanation 1

スポーツ $ 1 $,$ 3 $,$ 4 $ を実施することにすると、人 $ 1 $ はスポーツ $ 1 $ に、人 $ 2 $ はスポーツ $ 3 $ に、 人 $ 3 $ はスポーツ $ 3 $ に、人 $ 4 $ はスポーツ $ 4 $ に参加します。 このとき、参加人数が最大のスポーツはスポーツ $ 3 $ で、その参加人数 $ 2 $ 人です。 また、参加人数が最大のスポーツの参加人数が $ 1 $ 人になるような方法は存在しないので、この例の答えは $ 2 $ になります。

### Sample Explanation 2

全員の好みが一致しているので、どうやっても一つのスポーツに $ 3 $ 人集まってしまいます。 よってこの例の答えは $ 3 $ です。

## 样例 #1

### 输入

```
4 5

5 1 3 4 2

2 5 3 1 4

2 3 1 4 5

2 5 4 3 1```

### 输出

```
2```

## 样例 #2

### 输入

```
3 3

2 1 3

2 1 3

2 1 3```

### 输出

```
3```

# AI分析结果



### 综合分析与结论

#### 核心思路与难点
该题的核心在于通过贪心策略逐步删除当前参与人数最多的项目，使得每次删除后的新状态可能带来更优解。关键点在于：
1. **贪心选择依据**：每次删除当前最多人参与的项目，强制原参与者转向次优选择
2. **状态维护**：需要高效跟踪每个人的当前选择（指针右移机制）
3. **时间复杂度优化**：通过指针维护避免重复扫描，将复杂度从 O(NM²) 优化至 O(NM)

#### 可视化设计要点
1. **动态演示**：
   - 初始显示所有项目及参与人数分布
   - 红色高亮当前最多人项目，点击"删除"触发指针右移动画
   - 箭头动画展示参与者转向次优项目的过程
2. **复古风格**：
   ![Pixel Art Visualization](https://i.imgur.com/8BkMzqN.gif)
   - 使用 16x16 像素块表示项目，人数用柱状像素条显示
   - 删除项目时触发 8-bit 爆炸音效（[示例音效](https://freesound.org/people/SunnySideSound/sounds/334090/)）
   - 背景播放 [8-bit 风格 BGM](https://opengameart.org/content/8-bit-jungle)

### 题解评分与推荐（≥4★）

| 题解作者 | 评分 | 核心亮点 |
|---------|------|---------|
| Ebola   | ★★★★★ | 指针维护优化时间复杂度，代码清晰 |
| Umbrella_Leaf | ★★★★☆ | 数学归纳法证明策略正确性 |
| Autream | ★★★★☆ | 复杂度分析到位，代码简洁 |

### 最优思路与实现

**关键代码片段**（Ebola 解法）：
```cpp
int main() {
    // 初始化指针数组
    for(int i=1;i<=n;i++) pos[i]=1;
    
    while(true) {
        // 统计当前各项目人数
        memset(cnt,0,sizeof(cnt));
        for(int i=1;i<=n;i++) {
            while(vis[A[i][pos[i]]]) pos[i]++; // 指针右移
            cnt[A[i][pos[i]]]++;
        }
        
        // 找到最大人数项目
        int mx = *max_element(cnt+1, cnt+m+1);
        ans = min(ans, mx);
        
        // 删除当前最大项目
        vis[目标项目] = 1; 
    }
}
```

### 相似题目推荐
1. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)（经典贪心调度）
2. [P2870 [USACO07DEC]Best Cow Line G](https://www.luogu.com.cn/problem/P2870)（字典序贪心）
3. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)（双指针贪心）

### 核心贪心策略可视化演示

```html
<div id="visualizer">
  <canvas id="pixelCanvas" width="640" height="480"></canvas>
  <div class="controls">
    <button onclick="nextStep()">Next Step ▶</button>
    <input type="range" id="speed" min="1" max="10" value="5">
  </div>
</div>

<script>
// 伪代码示例
class Visualizer {
  constructor() {
    this.projects = Array(M).fill().map((_,i) => ({
      id: i+1,
      participants: [],
      color: `hsl(${i*30},70%,50%)`
    }));
    
    this.people = Array(N).fill().map(p => ({
      pref: [...], // 偏好列表
      ptr: 0
    }));
  }

  draw() {
    // 绘制像素风格的项目方块和人数柱状图
    this.projects.forEach(p => {
      drawRect(p.x, p.y, p.color);
      drawBar(p.participants.length); 
    });
  }

  deleteMaxProject() {
    const target = this.projects.reduce((a,b) => 
      a.participants.length > b.participants.length ? a : b);
      
    target.deleted = true;
    playSound('explosion.wav');
    
    // 更新所有人的指针
    this.people.forEach(p => {
      while(target.id === p.pref[p.ptr]) p.ptr++;
      animateArrow(p, p.pref[p.ptr]);
    });
  }
}
</script>
```

### 实践心得
1. **指针维护陷阱**：在删除项目后需要立即更新指针，否则会遗漏后续判断
2. **边界条件**：当所有项目都被删除时需及时终止循环
3. **时间复杂度误区**：未维护指针的朴素解法在极端情况下会退化为 O(M²N)

该贪心策略的精髓在于通过局部最优的连续选择逼近全局最优，其正确性依赖于数学归纳法的严格证明。可视化实现时需重点展示"删除最大→重新分配"的迭代过程，帮助理解策略的单调性特征。

---
处理用时：80.72秒