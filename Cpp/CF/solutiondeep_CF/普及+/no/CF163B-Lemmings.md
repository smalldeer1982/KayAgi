# 题目信息

# Lemmings

## 题目描述

As you know, lemmings like jumping. For the next spectacular group jump $ n $ lemmings gathered near a high rock with $ k $ comfortable ledges on it. The first ledge is situated at the height of $ h $ meters, the second one is at the height of $ 2h $ meters, and so on (the $ i $ -th ledge is at the height of $ i·h $ meters). The lemmings are going to jump at sunset, and there's not much time left.

Each lemming is characterized by its climbing speed of $ v_{i} $ meters per minute and its weight $ m_{i} $ . This means that the $ i $ -th lemming can climb to the $ j $ -th ledge in ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF163B/30016607ebe88930003ff462753dc7b94c82b700.png) minutes.

To make the jump beautiful, heavier lemmings should jump from higher ledges: if a lemming of weight $ m_{i} $ jumps from ledge $ i $ , and a lemming of weight $ m_{j} $ jumps from ledge $ j $ (for $ i<j $ ), then the inequation $ m_{i}<=m_{j} $ should be fulfilled.

Since there are $ n $ lemmings and only $ k $ ledges ( $ k<=n $ ), the $ k $ lemmings that will take part in the jump need to be chosen. The chosen lemmings should be distributed on the ledges from $ 1 $ to $ k $ , one lemming per ledge. The lemmings are to be arranged in the order of non-decreasing weight with the increasing height of the ledge. In addition, each lemming should have enough time to get to his ledge, that is, the time of his climb should not exceed $ t $ minutes. The lemmings climb to their ledges all at the same time and they do not interfere with each other.

Find the way to arrange the lemmings' jump so that time $ t $ is minimized.

## 说明/提示

Let's consider the first sample case. The fifth lemming (speed 10) gets to the ledge at height 2 in ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF163B/9afdc5b93ef27ce72945708dcc66dfa8da5502ae.png) minutes; the second lemming (speed 2) gets to the ledge at height 4 in 2 minutes; the fourth lemming (speed 2) gets to the ledge at height 6 in 3 minutes. All lemmings manage to occupy their positions in 3 minutes.

## 样例 #1

### 输入

```
5 3 2
1 2 3 2 1
1 2 1 2 10
```

### 输出

```
5 2 4
```

## 样例 #2

### 输入

```
5 3 10
3 4 3 2 1
5 4 3 2 1
```

### 输出

```
4 3 1
```

# AI分析结果

### 题目内容
# 旅鼠

## 题目描述
如你所知，旅鼠喜欢跳跃。为了下一次壮观的集体跳跃，$n$只旅鼠聚集在一块高高的岩石附近，岩石上有$k$个舒适的岩架。第一个岩架位于高度$h$米处，第二个位于高度$2h$米处，依此类推（第$i$个岩架位于高度$i·h$米处）。旅鼠们打算在日落时跳跃，所剩时间不多了。

每只旅鼠的特征由其攀爬速度$v_{i}$（米/分钟）和体重$m_{i}$表示。这意味着第$i$只旅鼠可以在$\frac{j·h}{v_{i}}$分钟内爬到第$j$个岩架。

为了使跳跃更美观，较重的旅鼠应该从更高的岩架上跳下：如果体重为$m_{i}$的旅鼠从岩架$i$跳下，体重为$m_{j}$的旅鼠从岩架$j$跳下（$i < j$），那么不等式$m_{i} \leq m_{j}$应该成立。

由于有$n$只旅鼠但只有$k$个岩架（$k \leq n$），需要选择$k$只旅鼠参加跳跃。选定的旅鼠应分布在从$1$到$k$的岩架上，每个岩架一只旅鼠。旅鼠应按照体重随岩架高度增加而不减少的顺序排列。此外，每只旅鼠都应该有足够的时间到达它的岩架，即它的攀爬时间不应超过$t$分钟。旅鼠们同时攀爬，且不会相互干扰。

找到一种安排旅鼠跳跃的方式，使时间$t$最小化。

## 说明/提示
让我们考虑第一个样例。第五只旅鼠（速度为10）在$\frac{2}{10}=0.2$分钟内到达高度为2的岩架；第二只旅鼠（速度为2）在2分钟内到达高度为4的岩架；第四只旅鼠（速度为2）在3分钟内到达高度为6的岩架。所有旅鼠都能在3分钟内到达它们的位置。

## 样例 #1
### 输入
```
5 3 2
1 2 3 2 1
1 2 1 2 10
```
### 输出
```
5 2 4
```

## 样例 #2
### 输入
```
5 3 10
3 4 3 2 1
5 4 3 2 1
```
### 输出
```
4 3 1
```

### 算法分类
二分

### 题解综合分析与结论
这两道题解思路相似，都采用二分答案的方法来解决问题。先对旅鼠按体重排序（一个按从大到小，一个按从小到大），体重相同时按速度排序，然后二分最小时间，通过check函数判断当前二分的时间是否可行。难点在于时间可能是小数，需要处理好二分的精度问题，同时要注意不同排序方式对后续选择旅鼠的影响。

### 所选的题解
- **汤汤tongtongTOT的题解**：★★★★
  - **关键亮点**：对题意理解清晰，明确给出解题思路，包括旅鼠排序依据和二分答案的具体操作；采用for循环写法二分答案，能有效控制精度且防止被卡精度；代码结构清晰，注释详细。
  - **个人心得**：提到本题数量级小常数大，建议二分答案用for循环写法，并指出时间可能是小数，二分中的l, r, mid皆为double类型，同时要注意eps的设置。
  - **重点代码简述**：定义结构体存储旅鼠信息，重载<运算符按体重从大到小、体重相同时速度从大到小排序。check函数中化除为乘判断当前时间是否可行，主函数中二分答案并记录结果。
  - **核心代码片段**：
```cpp
struct lem{
    int m, v, id;
    bool operator< (const lem & A) const{
        return m == A.m? v > A.v : m > A.m;
    }
}a[MAXN];
bool check(double t){
    memset(sol, 0, sizeof(sol));
    int i = 1;
    for(int j = k; j; --j){
        bool b = false;
        for(; i <= n; ++i)
            if((double)j * (double)h <= (double)a[i].v * (t + eps)) {
                sol[j] = a[i++].id;
                b = true;
                break;
            }
        if(!b) return false;
    }
    return true;
}
signed main(){
    n = read(), k = read(), h = read();
    for(int i = 1; i <= n; ++i) a[i].m = read();
    for(int i = 1; i <= n; ++i) a[i].v = read();
    for(int i = 1; i <= n; ++i) a[i].id = i;
    sort(a + 1, a + n + 1);

    double l = 0, r = k * h, mid;
    for(int cnt = 1; cnt <= 300; ++cnt){
        mid = (l + r) / 2;
        if(check(mid)) r = mid, memcpy(ans, sol, sizeof(ans));
        else l = mid;
    }
    for(int i = 1; i <= k; ++i) printf("%lld ", ans[i]);
    return 233;
}
```
- **pythoner713的题解**：★★★★
  - **关键亮点**：思路清晰，先对旅鼠按体重从小到大排序，二分最小时间并在check函数中合理选择旅鼠判断时间可行性；考虑了精度问题，根据数据规模调整eps值。
  - **个人心得**：提到由于最小时间可能不是整数，二分实数时被卡多次，需要注意精度设置，不能太高也不能太低。
  - **重点代码简述**：定义结构体存储旅鼠信息，重载<运算符按体重从小到大、体重相同时速度从小到大排序。check函数中判断当前时间内能否选到足够旅鼠，主函数中二分答案并记录结果。
  - **核心代码片段**：
```cpp
struct lemming{
    int v, w, id;
    bool operator < (const lemming &tmp) const{
        return w < tmp.w || (w == tmp.w && v < tmp.v); 
    }
}a[nb];
bool check(ld x){
    int now = 1;
    memset(tmp, 0, sizeof(tmp));
    for(int i = 1; i <= n; i++){
        if((ld)h * now <= (x + eps) * (ld)a[i].v){
            tmp[now++] = a[i].id;
        }
    }
    return now > k;
}
int main(){
    cin >> n >> k >> h;
    eps = (n >= 1000? 1e-15 : 1e-18);
    for(int i = 1; i <= n; i++) a[i].id = i;
    for(int i = 1; i <= n; i++) cin >> a[i].w;
    for(int i = 1; i <= n; i++) cin >> a[i].v;
    sort(a + 1, a + n + 1);
    ld l = 0, r = k * h;
    while(l <= r - eps && cnt++ <= 1000){
        ld mid = (l + r) / 2;
        if(check(mid)){
            memcpy(ans, tmp, sizeof(ans)); 
            r = mid;
        }
        else l = mid;
    }
    for(int i = 1; i <= k; i++) cout << ans[i] << " ";
    return 0;
}
```

### 最优关键思路或技巧
1. **二分答案**：对于最小化时间$t$这类问题，二分答案是一种有效的方法。通过不断缩小可行时间的范围，找到满足条件的最小时间。
2. **合理排序**：根据题目中较重旅鼠从更高岩架跳下的条件，对旅鼠按体重排序，体重相同时按速度排序，方便后续选择旅鼠。
3. **处理精度**：由于时间可能是小数，在二分过程中要注意精度问题，通过设置合适的eps值或者采用特定的二分写法（如for循环写法）来保证精度。

### 可拓展思路
同类型题常涉及到在一些限制条件下寻找最优值，类似算法套路为：先分析题目条件确定排序依据，再根据问题特点选择二分答案的方法，在判断可行性时结合具体条件进行逻辑判断。

### 洛谷相似题目推荐
1. [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)：同样是在一定条件下通过二分答案寻找最优解，判断可行性时需要根据题目条件进行分析。
2. [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)：利用二分答案的思想，结合对数列分段的条件判断，找到满足条件的最小分段最大值。
3. [P3853 [TJOI2007]路标设置](https://www.luogu.com.cn/problem/P3853)：通过二分答案确定路标的合适间距，根据设置路标的数量限制来判断可行性。 

---
处理用时：80.23秒