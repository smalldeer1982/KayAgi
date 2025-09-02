# 题目信息

# [ABC365C] Transportation Expenses

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc365/tasks/abc365_c

あるイベントには $ N $ 人が参加し、$ i $ 番目の人の交通費は $ A_i $ 円でした。

イベントの主催者である高橋くんは、交通費補助額の上限額 $ x $ を設定して、人 $ i $ には交通費補助額として $ \min(x,A_i) $ 円を支給することとしました。ここで $ x $ は非負整数である必要があります。

高橋くんの予算が $ M $ 円であり、$ N $ 人に渡す交通費補助額の総和を $ M $ 円以下にしたいとき、交通費補助額の上限額 $ x $ は最大でいくらにできますか？

ただし、交通費補助額の上限額を無限に大きくできる場合は代わりにそのことを報告してください。

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 2\times\ 10^5 $
- $ 1\leq\ M\ \leq\ 2\times\ 10^{14} $
- $ 1\leq\ A_i\ \leq\ 10^9 $
- 入力される数値は全て整数
 
### Sample Explanation 1

交通費補助額の上限額を $ 2 $ 円にすると、$ N $ 人に渡す交通費補助額の総和は $ \min(2,1)\ +\ \min(2,3)\ +\ \min(2,2)\ +\ \min(2,4)\ =\ 7 $ 円となり、予算の $ 8 $ 円以下となります。 交通費補助額の上限額を $ 3 $ 円にすると、$ N $ 人に渡す交通費補助額の総和は $ \min(3,1)\ +\ \min(3,3)\ +\ \min(3,2)\ +\ \min(3,4)\ =\ 9 $ 円となり、予算の $ 8 $ 円を超えてしまいます。 よって、交通費補助額の上限額の最大値は $ 2 $ 円となります。

### Sample Explanation 2

交通費補助額の上限額を無限に大きくできます。

## 样例 #1

### 输入

```
4 8

1 3 2 4```

### 输出

```
2```

## 样例 #2

### 输入

```
3 20

5 3 2```

### 输出

```
infinite```

## 样例 #3

### 输入

```
10 23

2 5 6 5 2 1 7 9 7 2```

### 输出

```
2```

# AI分析结果



# 【算法分类】
二分答案

---

## 【题解思路与难点分析】

### 核心思路
所有题解均采用二分答案法，利用总补贴金额随x单调递增的特性进行二分查找。关键步骤：
1. **无限大判断**：若所有A_i总和≤M，直接返回"infinite"
2. **二分框架**：在[0, max(A_i)]范围内查找最大x
3. **check函数**：O(n)计算当前x的总补贴是否≤M

### 解决难点
1. **右边界确定**：多数题解将右边界设为1e9或A_i最大值，防止无效搜索
2. **总和溢出处理**：在check函数中及时break求和循环（当sum>M时立即返回false）
3. **无限大边界判断**：部分题解通过设置极大右边界（如2e16），在二分结束后判断是否达到该阈值

### 关键对比
| 题解特征               | 优势                                   | 注意点                               |
|----------------------|---------------------------------------|------------------------------------|
| 动态break求和          | 减少无效计算（chinazhanghaoxun）        | 需保证循环内判断不影响结果正确性            |
| 排序预处理             | 可优化check为前缀和+二分（Little_x_starTYJ） | 增加O(nlogn)排序时间，但check复杂度降为O(logn) |
| 极大右边界（2e16）      | 统一处理无限大判断（Pink_Cut_Tree）        | 需注意数据范围是否可能溢出                |

---

## 【⭐4星以上题解推荐】

1. **chinazhanghaoxun（⭐5）**
   - 亮点：预处理最小补贴判断预算可行性，右边界设为m+1简化无限大判断
   - 代码节选：
     ```cpp
     bool check(int x){
         int cnt=0; 
         for(int i=1;i<=n;i++){
             cnt+=min(x,a[i]);
             if(cnt>m) return false; // 及时终止无效计算
         }
         return cnt<=m; 
     }
     ```

2. **ikunTLE（⭐4.5）**
   - 亮点：使用A_i最大值作为右边界，逻辑清晰
   - 核心判断：
     ```cpp
     if(r != MAX) printf("%d\n",r);
     else printf("infinite\n");
     ```

3. **Little_x_starTYJ（⭐4.5）**
   - 亮点：排序后使用前缀和优化check函数
   - 优化代码：
     ```cpp
     sort(a + 1, a + 1 + n);
     int l = 1, r = m;
     while(l < r){
         int mid = l + (r - l + 1) / 2;
         if(check(mid)) l = mid;
         else r = mid - 1;
     }
     ```

---

## 【可视化算法分析】

### 动画设计
1. **界面布局**：
   - 左面板：动态展示A_i数组，每个元素显示数值和当前min(x,ai)
   - 右面板：显示二分区间[l, r]、当前mid值和总补贴sum
   - 控制栏：速度调节/单步执行/重置按钮

2. **关键动画**：
   - **步骤1**：高亮当前mid值，用不同颜色标记：
     - 绿色：sum ≤ M
     - 红色：sum > M
   - **步骤2**：动态计算每个元素的min(ai, mid)，实时累加sum
   - **步骤3**：根据check结果移动指针：
     - 成功：l右移（mid→橙色）
     - 失败：r左移（mid→灰色）

3. **复古风格**：
   ```javascript
   // 伪代码示例
   class PixelAnimator {
       constructor(canvas) {
           this.ctx = canvas.getContext('2d');
           this.palette = ['#000','#0f0','#f00','#ff0']; // 黑绿红黄
       }
       
       drawBar(x, height, colorIdx) {
           this.ctx.fillStyle = this.palette[colorIdx];
           this.ctx.fillRect(x*10, 100-height, 8, height);
       }
   }
   ```

---

## 【相似题目推荐】
1. P2678 跳石头（二分答案经典题）
2. P4343 自动刷题机（二分答案+条件判断）
3. P1182 数列分段（二分答案+贪心验证）

---

## 【核心代码实现】
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,m,a[N];

bool check(int x){ // 检查函数
    int sum=0;
    for(int i=1;i<=n;++i){
        sum += min(a[i],x);
        if(sum > m) return false; // 及时终止计算
    }
    return true;
}

signed main(){
    cin>>n>>m;
    int total=0, max_a=0;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        total += a[i];
        max_a = max(max_a,a[i]);
    }
    
    // 处理无限大情况
    if(total <= m){
        cout<<"infinite";
        return 0;
    }
    
    // 二分主流程
    int l=0, r=2e14, ans=0;
    while(l <= r){
        int mid = (l+r)/2;
        if(check(mid)){
            ans = mid;
            l = mid+1;
        }else{
            r = mid-1;
        }
    }
    cout<<ans;
}
```

---

## 【总结与扩展】
本题的二分答案思路具有普适性，适用于所有满足单调性的极值问题。关键点在于：
1. 确定答案的单调性
2. 设计高效的check函数
3. 合理设置二分边界

扩展思考：若A_i动态变化（在线查询），可结合前缀和+二分查找进行优化，将每次check的时间复杂度降至O(logn)。

---
处理用时：73.92秒