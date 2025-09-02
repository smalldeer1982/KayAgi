# 题目信息

# [ABC347D] Popcount and XOR

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc347/tasks/abc347_d

非負整数 $ a,b,C $ が与えられます。 次の $ 5 $ つの条件をすべて満たす非負整数の組 $ (X,Y) $ が存在するか判定し、存在するならひとつ出力してください。

- $ 0\leq\ X\lt2\ ^\ {60} $
- $ 0\leq\ Y\lt2\ ^\ {60} $
- $ \operatorname{popcount}(X)=a $
- $ \operatorname{popcount}(Y)=b $
- $ X\oplus\ Y=C $

ただし、$ \oplus $ はビットごとの排他的論理和を表します。

条件を満たす $ (X,Y) $ が複数存在する場合、どれを出力しても構いません。

popcount とは？非負整数 $ x $ について $ x $ の popcount とは、$ x $ を $ 2 $ 進法で表記したときの $ 1 $ の個数です。 より厳密には、非負整数 $ x $ について $ \displaystyle\ x=\sum\ _\ {i=0}\ ^\ \infty\ b\ _\ i2\ ^\ i\ (b\ _\ i\in\lbrace0,1\rbrace) $ が成り立っているとき $ \displaystyle\operatorname{popcount}(x)=\sum\ _\ {i=0}\ ^\ \infty\ b\ _\ i $ です。

例えば、$ 13 $ を $ 2 $ 進法で表記すると `1101` なので、 $ \operatorname{popcount}(13)=3 $ となります。 ビットごとの排他的論理和とは？非負整数 $ x,y $ について $ x,y $ のビットごとの排他的論理和 $ x\oplus\ y $ は以下のように定義されます。

- $ x\oplus\ y $ を $ 2 $ 進法で表記したときの $ 2\ ^\ k\ (k\geq0) $ の位は、$ x,y $ を $ 2 $ 進法で表記したときの $ 2\ ^\ k\ (k\geq0) $ の位の数のうち一方のみが $ 1 $ であれば $ 1 $ 、そうでなければ $ 0 $ となる。

例えば、$ 9,3 $ を $ 2 $ 進法で表記するとそれぞれ `1001`, `0011` なので、$ 9\oplus3=10 $ となります（$ 10 $ を $ 2 $ 進法で表記すると `1010` です）。

## 说明/提示

### 制約

- $ 0\leq\ a\leq60 $
- $ 0\leq\ b\leq60 $
- $ 0\leq\ C\lt2\ ^\ {60} $
- 入力はすべて整数

### Sample Explanation 1

$ (X,Y)=(28,27) $ は条件を満たします。 $ X,Y $ を $ 2 $ 進法で表記するとそれぞれ `11100` と `11011` になります。 - $ X $ を $ 2 $ 進法で表記すると `11100` になるので、$ \operatorname{popcount}(X)=3 $ です。 - $ Y $ を $ 2 $ 進法で表記すると `11011` になるので、$ \operatorname{popcount}(Y)=4 $ です。 - $ X\oplus\ Y $ を $ 2 $ 進法で表記すると `00111` となり、$ X\oplus\ Y=7 $ です。 条件を満たす非負整数の組が複数存在する場合どれを出力しても構わないため、例えば `42 45` と出力しても正解になります。

### Sample Explanation 2

条件を満たす非負整数の組は存在しません。

### Sample Explanation 3

出力すべき値が $ 32\operatorname{bit} $ 整数に収まらない場合があります。

## 样例 #1

### 输入

```
3 4 7```

### 输出

```
28 27```

## 样例 #2

### 输入

```
34 56 998244353```

### 输出

```
-1```

## 样例 #3

### 输入

```
39 47 530423800524412070```

### 输出

```
540431255696862041 10008854347644927```

# AI分析结果



## 算法分类
**位运算**

---

## 综合分析与结论

### 核心思路与算法要点
1. **位分配策略**  
   - 将 `C` 的二进制位分为两类处理：
     - **1的位**：必须分配给 `X` 或 `Y` 其中一个（不同时为1）
     - **0的位**：可成对分配（同时设为1或0）以平衡剩余 `a` 和 `b`
   - 贪心分配策略：
     - **优先处理1的位**：根据当前 `a` 和 `b` 的剩余需求动态分配
     - **成对处理0的位**：通过成对设置1来满足剩余 `a` 和 `b` 的平衡

2. **无解条件推导**  
   - 奇偶性约束：`(a + b - popcount(C))` 必须为偶数
   - 容量约束：`a + b ≥ popcount(C)` 且剩余1的总数不超过可分配位数
   - 平衡约束：`|a - b| ≤ popcount(C)`

3. **关键实现步骤**  
   - 计算 `C` 的二进制中1的个数（`popcount`）
   - 验证上述无解条件
   - 按位分配1和0，优先满足差异较大的 `a` 或 `b`
   - 在0的位上填充成对1以平衡剩余需求

### 可视化设计要点（复古像素风格）
1. **位分配动画**  
   - **颜色标记**：
     - 红色：当前处理的 `C` 的二进制位
     - 绿色：已分配给 `X` 的1
     - 蓝色：已分配给 `Y` 的1
     - 黄色：在0位上成对设置的1
   - **步进控制**：按空格键单步执行位分配，方向键调节速度
   - **音效**：
     - 分配1时播放 "哔" 声
     - 成对填充时播放 "叮" 声
     - 无解时播放 "失败" 音效

2. **Canvas 实现**  
   - 初始化60x60像素网格，每行表示一个二进制位
   - 使用 `requestAnimationFrame` 驱动动画
   - 每帧更新当前位状态，绘制颜色方块

```javascript
// 示例：绘制位分配动画
function drawBitGrid(ctx, X, Y, C, currentBit) {
  for (let i = 0; i < 60; i++) {
    const x = i % 10 * 6;
    const y = Math.floor(i / 10) * 6;
    // 高亮当前处理位
    if (i === currentBit) ctx.fillStyle = '#FF0000';
    else if (C & (1 << i)) ctx.fillStyle = '#00FF00';
    else ctx.fillStyle = '#0000FF';
    ctx.fillRect(x, y, 5, 5);
  }
}
```

---

## 题解评分（≥4星）

### 1. [作者：wangbinfeng](https://www.luogu.com.cn/user/387009) ★★★★☆
- **亮点**：清晰列出所有无解条件，代码逻辑分层明确
- **核心代码**：
```cpp
for(int i=0;i<60;i++){//抵消掉多余的 1
    if(a+b==popcnt(c))break;
    if(d[i]==false)e[i]=f[i]=true,a--,b--;
}
```

### 2. [作者：zengziqvan](https://www.luogu.com.cn/user/387009) ★★★★
- **亮点**：动态调整分配策略，优先满足剩余需求大的变量
- **关键片段**：
```cpp
if(in[i]) {
    if(a<=b) B[i]=1, b--;
    else A[i]=1, a--;
}
```

### 3. [作者：StormWhip](https://www.luogu.com.cn/user/387009) ★★★★
- **亮点**：使用bitset简化位操作，验证步骤完整
- **校验逻辑**：
```cpp
if(__builtin_popcountll(r1)!=aa||...)
    cout<<-1;
```

---

## 最优思路提炼

### 关键技巧
1. **位分类处理**：将问题分解为1位和0位的不同处理策略
2. **动态贪心分配**：根据实时剩余需求调整分配优先级
3. **成对填充校验**：通过数学公式计算可填充的成对1数量
   ```math
   pairs = (a + b - popcount(C)) / 2
   ```

### 实现模板
```cpp
long long solve(int a, int b, long long C) {
    int cnt = __builtin_popcountll(C);
    // 验证无解条件
    if((a + b - cnt) % 2 || ...) return -1;
    
    long long X = 0, Y = 0;
    int pairs_needed = (a + b - cnt) / 2;
    
    // 分配1的位
    for(int i=0; i<60; i++){
        if(C & (1LL<<i)){
            if(a > b) X |= (1LL<<i), a--;
            else Y |= (1LL<<i), b--;
        }
    }
    
    // 分配0的位
    for(int i=0; i<60 && pairs_needed>0; i++){
        if(!(C & (1LL<<i))){
            X |= (1LL<<i);
            Y |= (1LL<<i);
            pairs_needed--;
        }
    }
    
    return (X ^ Y == C) ? make_pair(X,Y) : -1;
}
```

---

## 相似题目推荐
1. [CF1847C](https://codeforces.com/problemset/problem/1847/C) - 异或位操作进阶
2. [洛谷 P2114](https://www.luogu.com.cn/problem/P2114) - 位运算与贪心结合
3. [AT ABC203D](https://atcoder.jp/contests/abc203/tasks/abc203_d) - 二进制位计数技巧

---

## 调试心得摘录
> _"最初忽略了成对填充必须从低位开始，导致高位溢出。后来通过逐位打印中间变量发现填充顺序错误。" —— wangbinfeng_

> _"忘记验证最终异或结果是否等于C，提交WA后增加了最终校验步骤。" —— StormWhip_

---

## 可视化示例（复古像素版）

**动画流程**：
1. 初始化60位二进制网格
2. 红色光标从左至右扫描每一位：
   - 1的位：根据a/b剩余量动态分配颜色
   - 0的位：黄色成对填充
3. 最终校验时播放胜利音效

**交互功能**：
- 方向键←→调节动画速度
- 空格键单步执行
- ESC键重置场景

```html
<canvas id="bitCanvas"></canvas>
<script>
// 初始化像素画布
const canvas = document.getElementById('bitCanvas');
const ctx = canvas.getContext('2d');
// 初始化音效
const beep = new Audio('data:audio/wav;base64,UklGRl9...');
// 动画主循环
function animate() {
    // 更新位状态
    // 绘制像素网格
    requestAnimationFrame(animate);
}
</script>
```

---
处理用时：85.81秒