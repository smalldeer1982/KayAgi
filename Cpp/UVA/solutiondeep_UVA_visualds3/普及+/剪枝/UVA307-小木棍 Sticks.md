# 题目信息

# 小木棍 Sticks

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=5&page=show_problem&problem=243

[PDF](https://uva.onlinejudge.org/external/3/p307.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA307/c2647a7ca09eb1b551716900d2c482623b1264d7.png)

## 样例 #1

### 输入

```
9
5 2 1 5 2 1 5 2 1
4
1 2 3 4
0```

### 输出

```
6
5```

# AI分析结果



**唯一算法分类**: 深度优先搜索（DFS） + 剪枝优化

---

### **综合分析与结论**
#### 核心算法流程
1. **枚举原始木棒长度**：从最长小木棍长度到总长度，只枚举能被总长度整除的值
2. **排序剪枝**：将小木棍降序排列，优先尝试长木棍
3. **DFS剪枝**：
   - 当前木棍无法拼接时跳过相同长度的木棍（红框高亮）
   - 首根木棍失败直接回溯（黄框高亮）
   - 刚好拼完当前木棒但后续失败时回溯（蓝框高亮）
4. **状态回溯**：使用vis数组标记已用木棍，递归失败时恢复状态

#### 可视化设计要点
```javascript
// 示例动画状态（伪代码）
class StickVisualizer {
  constructor() {
    this.canvas = document.createElement('canvas');
    this.ctx = this.canvas.getContext('2d');
    this.sticks = [5,5,5,2,2,2,1,1,1]; // 样例输入
    this.ctx.fillStyle = '#8B4513'; // 木棍颜色
  }

  drawStep(lenNow, used) {
    // 绘制当前拼接状态
    used.forEach(idx => 
      drawRect(idx*30, 0, 25, 50)); // 已用木棍
    // 高亮当前操作
    if(lenNow === 0) 
      drawBorder(currentStick, 'red'); // 首根木棍
    if(lenNow + currentStick === targetLen)
      drawBorder(currentStick, 'blue'); // 末根木棍
  }
  
  playSound(effect) {
    // 8-bit音效
    if(effect === 'cut') playBeep(440, 50); // 剪枝时
    if(effect === 'success') playMelody([523, 659]); 
  }
}
```

---

### **题解清单（≥4星）**
1. **锦时（★★★★☆）**  
   关键亮点：详细注释五个剪枝策略，变量命名清晰，可读性强  
   核心代码片段：
```cpp
bool dfs(int stick,int cab,int last) {
    if(stick>cnt) return true;
    if(cab==len) return dfs(stick+1,0,1);
    int fail=0;
    for(int i=last;i<=n;i++) { // 从last开始剪枝
        if(!v[i] && cab+a[i]<=len && fail!=a[i]) {
            v[i] = 1;
            if(dfs(stick, cab+a[i], i)) return true;
            v[i] = 0;
            fail = a[i];
            if(cab==0 || cab+a[i]==len) return false; // 首末剪枝
        }
    }
    return false;
}
```

2. **fletmer（★★★★☆）**  
   关键亮点：函数参数命名规范（nbr/len/las），剪枝逻辑集中  
   独特优化：使用fl变量记录最近失败长度

3. **Azuree（★★★★☆）**  
   关键亮点：代码最简洁，利用全局变量减少参数传递  
   核心优化：跳过相同长度木棍的while循环

---

### **最优技巧提炼**
1. **降序排列的魔力**  
   将木棍从大到小排序后，优先使用长木棍能快速减少剩余空间，极大降低搜索树规模  
   `sort(a+1, a+n+1, cmp); // cmp为降序比较函数`

2. **四重剪枝策略**  
   ```cpp
   if(cab == 0) return false;          // 首根失败
   if(cab + a[i] == len) return false; // 末根失败
   if(fail == a[i]) continue;          // 相同长度跳过
   if(sum % len != 0) continue;        // 非因数直接跳过
   ```

3. **状态恢复的艺术**  
   在DFS回溯时立即恢复vis数组状态，避免全量重置  
   `v[i]=1; ... v[i]=0; // 精准状态回溯`

---

### **相似题目推荐**
1. [P1120 小木棍](https://www.luogu.com.cn/problem/P1120)  
   加强版数据，需要更严格的剪枝
   
2. [P1731 生日蛋糕](https://www.luogu.com.cn/problem/P1731)  
   经典DFS剪枝题，需优化表面积计算

3. [P1074 靶形数独](https://www.luogu.com.cn/problem/P1074)  
   复杂DFS剪枝，带权值计算

---

### **个人心得摘录**
> "调试时发现，忘记处理相同长度木棍会导致超时。加上`while(a[i+1]==a[i])i++;`后效率提升百倍。排序看似简单，实为剪枝的根基" —— 狸狸养的敏敏

> "将len的枚举范围限制在max~sum/2，配合sum%len检查，直接过滤80%无效情况" —— 神之殇

---

### **完整代码示例**
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

int n, sum, len, cnt;
int a[70], vis[70];

bool dfs(int num, int now, int last) {
    if(num > cnt) return true;
    if(now == len) return dfs(num+1, 0, 1);
    int fail = 0;
    for(int i=last; i<=n; ++i) {
        if(!vis[i] && now+a[i]<=len && a[i]!=fail) {
            vis[i] = 1;
            if(dfs(num, now+a[i], i+1)) return true;
            vis[i] = 0;
            fail = a[i];
            if(now == 0 || now+a[i] == len) break;
        }
    }
    return false;
}

int main() {
    while(cin >> n && n) {
        sum = 0;
        int max_len = 0;
        for(int i=1; i<=n; ++i) {
            cin >> a[i];
            if(a[i] > 50) { --i; --n; continue; }
            sum += a[i];
            max_len = max(max_len, a[i]);
        }
        sort(a+1, a+n+1, greater<int>());
        for(len=max_len; len<=sum; ++len) {
            if(sum % len) continue;
            cnt = sum / len;
            memset(vis, 0, sizeof(vis));
            if(dfs(1, 0, 1)) {
                cout << len << endl;
                break;
            }
        }
    }
    return 0;
}
```

---
处理用时：86.08秒