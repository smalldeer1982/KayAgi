# 题目信息

# [USACO23FEB] Cow-libi S

## 题目描述

注意：本题的时间限制为 4 秒，是默认限制的两倍。

有人在 Farmer John 的 $G(1 \leq G \leq 10^5)$ 个私人花园里偷吃了庄稼！通过他的专业法医知识，Farmer John 确定了每个花园被偷吃的具体时间。他还发现，这些事件的罪魁祸首是一头单独的奶牛。

为了回应这些犯罪行为，Farmer John 的 $N(1 \leq N \leq 10^5)$ 头奶牛每头都提供了一个不在作案现场的证明（即“不在场证明”），表明奶牛在特定时间出现在特定位置。请帮助 Farmer John 判断这些“不在场证明”中哪些能够证明奶牛的清白。

如果一头奶牛无法在她的“不在场证明”位置与所有被偷吃地点之间往返，则可以确定这头奶牛是清白的。奶牛的移动速度为每单位时间 $1$ 单位距离。本题中提到的距离均为欧几里得距离。

## 样例 #1

### 输入

```
2 4
0 0 100
50 0 200
0 50 50
1000 1000 0
50 0 200
10 0 170```

### 输出

```
2```

# AI分析结果



### 综合分析与结论
本题需判断奶牛的不在场证明是否使其无法参与所有犯罪。核心思路是将犯罪事件按时间排序，利用二分查找确定最近的两个事件，检查移动时间是否足够。关键技巧包括：避免浮点运算、处理边界条件、利用lower_bound高效查找。

### 高星题解推荐
#### 1. _3Zinc_ 的题解（★★★★☆）
**关键亮点**  
- 结构体排序后使用`lower_bound`快速定位最近事件。  
- 通过平方比较避免精度问题。  
- 清晰处理边界情况（无前驱/后继）。  

**核心代码**  
```cpp
bool check(int i, ll t, ll x, ll y) {
    return (x-p[i].x)*(x-p[i].x)+(y-p[i].y)*(y-p[i].y) <= (t-p[i].t)*(t-p[i].t);
}
// 主逻辑片段
int pos = lower_bound(tim+1, tim+1+n, t) - tim;
if (pos == 1) 
    ans += check(pos, t, x, y) ? 1 : 0;
else if (pos-1 == n) 
    ans += check(pos-1, t, x, y) ? 1 : 0;
else 
    ans += (check(pos, t, x, y) && check(pos-1, t, x, y)) ? 1 : 0;
```

#### 2. cff_0102 的题解（★★★★☆）
**关键亮点**  
- 使用`tuple`存储犯罪事件，代码简洁。  
- 利用`lower_bound`和`prev`处理相邻事件。  
- 直接比较平方距离，无浮点运算。  

**核心代码**  
```cpp
bool chk(tuple<int,int,int> b, int xa, int ya, int ta) {
    auto [tb, xb, yb] = b;
    double dt = abs(ta - tb), dx = xa - xb, dy = ya - yb;
    return dx*dx + dy*dy <= dt*dt;
}
// 主逻辑片段
auto it = lower_bound(gs+1, gs+1+g, make_tuple(t, x, y)) - gs - 1;
ans += (it == 0 || chk(gs[it], x, y, t)) && (it == g || chk(gs[it+1], x, y, t));
```

#### 3. 快斗游鹿 的题解（★★★★☆）
**关键亮点**  
- 手写二分处理前驱事件索引。  
- 特判所有边界条件（最早/最晚事件）。  
- 分别计算前驱和后继的条件，逻辑清晰。  

**核心代码**  
```cpp
int l=1, r=g, I=0;
while(l<=r) { // 二分找前驱事件索引I
    int mid = (l+r)>>1;
    if(e[mid].t <= ttt) I=mid, l=mid+1;
    else r=mid-1;
}
// 计算距离并判断时间差
double total = sqrt((xxx-e[I+1].x)^2 + (yyy-e[I+1].y)^2);
if(total > (e[I+1].t - ttt)) ans++; // 无法到达则清白
```

### 关键思路总结
1. **排序与二分**：将犯罪事件按时间排序后，用二分查找快速定位相邻事件。  
2. **平方比较**：计算欧式距离的平方与时间差的平方比较，避免浮点误差。  
3. **边界处理**：特判不在场证明早于或晚于所有犯罪的情况，只需检查最近事件。  

### 拓展建议
- **同类题目**  
  - [P1663 山](https://www.luogu.com.cn/problem/P1663)：二分答案验证条件。  
  - [P2234 HNOI2002 营业额统计](https://www.luogu.com.cn/problem/P2234)：维护前驱后继。  
  - [CF1029D Concatenated Multiples](https://codeforces.com/problemset/problem/1029/D)：预处理与二分结合。  

- **调试心得**  
  - 务必注意输入变量顺序（如G和N易混淆）。  
  - 使用`long long`存储平方值防止溢出。  
  - 题目保证存在可行解，无需额外验证犯罪事件间可达性。

---
处理用时：184.90秒