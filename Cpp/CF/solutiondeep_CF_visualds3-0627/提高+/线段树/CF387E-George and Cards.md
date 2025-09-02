# 题目信息

# George and Cards

## 题目描述

George is a cat, so he loves playing very much.

Vitaly put $ n $ cards in a row in front of George. Each card has one integer written on it. All cards had distinct numbers written on them. Let's number the cards from the left to the right with integers from $ 1 $ to $ n $ . Then the $ i $ -th card from the left contains number $ p_{i} $ ( $ 1<=p_{i}<=n $ ).

Vitaly wants the row to have exactly $ k $ cards left. He also wants the $ i $ -th card from left to have number $ b_{i} $ written on it. Vitaly gave a task to George, to get the required sequence of cards using the remove operation $ n-k $ times.

In one remove operation George can choose $ w $ ( $ 1<=w $ ; $ w $ is not greater than the current number of cards in the row) contiguous cards (contiguous subsegment of cards). Let's denote the numbers written on these card as $ x_{1},x_{2},...,x_{w} $ (from the left to the right). After that, George can remove the card $ x_{i} $ , such that $ x_{i}<=x_{j} $ for each $ j $ $ (1<=j<=w) $ . After the described operation George gets $ w $ pieces of sausage.

George wondered: what maximum number of pieces of sausage will he get in total if he reaches his goal and acts optimally well? Help George, find an answer to his question!

## 样例 #1

### 输入

```
3 2
2 1 3
1 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
10 5
1 2 3 4 5 6 7 8 9 10
2 4 6 8 10
```

### 输出

```
30
```

# AI分析结果



## 算法分类
贪心

---

## 综合分析与结论
### 核心思路与解决难点
**核心思路**：  
1. **贪心顺序**：按数值从小到大删除卡片，确保每次删除时能获得最大可能的区间范围。  
2. **边界确定**：用 `set` 维护保留数的位置，通过二分查找确定当前删除数的左右边界（第一个比它小的保留数的位置）。  
3. **区间统计**：用树状数组动态维护剩余卡片的数量，快速计算区间内可删除的卡片数。

**解决难点**：  
- **贪心顺序的证明**：需证明先删除小数不会限制后续大数的区间选择。  
- **边界处理**：通过预插入 `0` 和 `n+1` 避免边界条件判断。  
- **高效数据结构**：`set` 用于快速查找前驱/后继，树状数组用于区间求和。

---

## 题解评分（≥4星）
1. **Saliеri的题解（5星）**  
   - **亮点**：代码简洁高效，仅用树状数组和 `set` 实现核心逻辑，时间复杂度严格 $O(n \log n)$。  
   - **关键代码**：预处理保留数位置，动态维护树状数组。

2. **wsyhb的题解（5星）**  
   - **亮点**：详细证明贪心策略，结合树状数组实现快速统计。

3. **_zuoqingyuan的题解（4星）**  
   - **亮点**：分步解析贪心策略，代码可读性强，树状数组与 `set` 结合清晰。

---

## 最优思路与技巧
1. **贪心顺序**：按数值从小到大处理，确保每次删除的区间最大化。  
2. **数据结构组合**：  
   - `set` 维护保留数位置，利用 `lower_bound` 快速确定边界。  
   - 树状数组维护剩余卡片数，支持 $O(\log n)$ 的修改与查询。  
3. **边界初始化**：预插入 `0` 和 `n+1` 简化边界条件判断。

---

## 相似题目
1. **P1886 滑动窗口**（区间极值，单调队列）  
2. **P1908 逆序对**（树状数组统计）  
3. **P2894 Hotel**（动态区间维护）

---

## 可视化与算法演示
### 核心逻辑可视化
1. **动画设计**：  
   - **卡片展示**：用像素方块表示卡片，颜色区分保留/已删除状态。  
   - **高亮当前数**：红色标记当前处理的数，蓝色标记保留数的边界。  
   - **区间绘制**：绿色框标出当前可删除的区间，显示剩余卡片数。  
2. **交互控制**：  
   - **步进执行**：手动控制每一步删除操作。  
   - **速度调节**：调整动画播放速度。  
3. **音效提示**：  
   - **删除成功**：短促“叮”声。  
   - **边界更新**：轻微“咔嗒”声。

### 复古像素风格实现
```javascript
// 伪代码示例：Canvas绘制卡片和操作
const canvas = document.getElementById('canvas');
const ctx = canvas.getContext('2d');
const CARD_SIZE = 20;

function drawCard(pos, value, state) {
  ctx.fillStyle = state === 'deleted' ? '#555' : '#8F8';
  ctx.fillRect(pos * CARD_SIZE, 0, CARD_SIZE, CARD_SIZE);
  ctx.fillStyle = '#000';
  ctx.fillText(value, pos * CARD_SIZE + 5, 15);
}

// 示例：绘制初始卡片
for (let i = 1; i <= n; i++) {
  drawCard(i, p[i], 'active');
}
```

---

## 核心代码实现
```cpp
#include <set>
#include <cstdio>
const int maxn = 1e6+5;
int n,k,a[maxn],inb[maxn],pos[maxn],c[maxn];
void update(int pos,int v){for(;pos<=n;pos+=(pos&(-pos)))c[pos] += v;}
int sum(int pos){
	int res = 0;
	for(;pos;pos-=(pos&(-pos)))res += c[pos];
	return res;
}
std :: set<int> p;
long long ans;
int main(){
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]),pos[a[i]] = i,update(i,1);
	for(int i=1,v;i<=k;++i)
		scanf("%d",&v),inb[v] = 1;
	p.insert(0),p.insert(n+1);
	std :: set<int> :: iterator it1,it2;
	for(int i=1;i<=n;++i){
		if(!inb[i]){
			it1 = it2 = p.lower_bound(pos[i]),--it1;
			ans += sum((*it2)-1)-sum((*it1));
			update(pos[i],-1);
		}
		else p.insert(pos[i]);
	}
	printf("%lld",ans);
	return 0;
}
```

**核心逻辑**：  
- **初始化**：记录每个数的位置，树状数组初始化为全1（表示卡片存在）。  
- **保留数处理**：将保留数的位置插入 `set`。  
- **删除数处理**：通过 `lower_bound` 找到左右边界，计算区间内剩余卡片数并累加答案。

---
处理用时：76.18秒