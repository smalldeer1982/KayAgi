# 题目信息

# [USACO12OPEN] Running Laps S

## 题目描述

农夫约翰让他的 n （1 <= n <= 100,000） 头牛在长度为 c 的跑道上进行跑 l 圈的比赛，所有牛从同一起点，以不同的速度开始跑。直到当跑得最快的那一头牛跑完 l 圈时，所有牛才同时停下。

  约翰发现在跑圈过程中发生了几次“超越事件”。其定义是：在比赛结束前某时刻，奶牛 x 已经超越了奶牛 y **整整一圈**，则称做一次“超越事件”。（注： **至少一圈** ，超越了1/2圈，或者超越了1/4圈等等都不算。且对于同一对奶牛（x，y）不会重复计算次数。）

 约翰想知道比赛过程中发生了多少次“超越事件”。

 （注：可能原文章表达有误或某些其他原因，各种翻译方式过来的题意都有问题，给人误导很大，这里是根据题目数据和样例解释写的正确的题意，而不是原文）

## 样例 #1

### 输入

```
4 2 100 
20 
100 
70 
1 
```

### 输出

```
4 
```

# AI分析结果

### 综合分析与结论
这些题解主要围绕奶牛跑圈的超越事件次数计算展开。核心思路是先算出每头牛跑的圈数，再计算超越次数。由于直接暴力枚举复杂度高，大部分题解采用将圈数拆分为整数部分和小数部分（或余数部分）的方法，通过处理整数部分的差值和小数部分（余数部分）的逆序对来优化算法，将时间复杂度从 $O(n^2)$ 降低到 $O(n\log n)$。

### 所选题解
- **作者：simonG (赞：16)，4星**
    - **关键亮点**：思路清晰，详细阐述了从暴力法到归并排序优化的过程，代码注释丰富，易于理解。
    - **核心实现思想**：先读取输入数据，对速度排序，计算每头牛的圈数和余数，通过枚举计算未处理前的值，再用归并排序求余数部分的逆序对，最后用未处理前的值减去逆序对个数得到答案。
```cpp
ll Msort(ll l, ll r) { //归并排序
    if(l >= r) return 0; //递归边界 
    ll ans = 0;
    int mid = (l + r) >> 1; //(l + r)/2
    ans += Msort(l, mid);
    ans += Msort(mid + 1, r);
    for(int i = l; i <= mid; i++)
        a[i] = d[i];
    for(int i = mid + 1, j = r; j >= mid + 1; i++, j--)
        a[i] = d[j];
    int i = l;
    int j = r; //左右边界 
    for(int k = l; k <= r; k++)
        if(a[i] <= a[j])
            d[k] = a[i++];
        else {
            ans += mid - i + 1; //求逆序对
            d[k] = a[j--];
        }
    return ans; //逆序对个数
} 

int main() { 
    n = read(), l = read(), c = read(); //读入
    for(int i = 1; i <= n; i++)
        V[i] = read(); //读入
    sort(V + 1, V + n + 1); //有序性
    ll ans = 0, t = 0;
    for(int i = 1; i <= n; i++) {
        f[i] = l * V[i] / V[n];
        d[i] = l * V[i] % V[n];
    } //圈数，个数
    for(int i = 1; i <= n; i++) {
        ans += (i - 1) * f[i] - t;
        t = t + f[i];
    } //枚举
    ans -= Msort(1, n); //减去逆序对个数
    printf("%lld", ans); //输出 
    return 0;
}
```
- **作者：wly09 (赞：3)，4星**
    - **关键亮点**：数学推导详细，对公式的变形和分析有助于理解问题本质，代码实现简洁。
    - **核心实现思想**：先读取输入数据，对速度排序，计算每头牛的圈数和余数，通过累加计算未处理前的值，再用归并排序求余数部分的逆序对，最后用未处理前的值减去逆序对个数得到答案。
```c++
void merge_sort(long long *arr, int l, int r) {
    if (r - l <= 1) return ;
    int mid = l + ((r - l) >> 1);
    merge_sort(arr, l, mid), merge_sort(arr, mid, r);
    register int pt1 = l, pt2 = mid, pt = l;
    for (; pt1 < mid && pt2 < r; ++pt) {
        if (arr[pt1] <= arr[pt2])  tmp[pt] = arr[pt1++];
        else tmp[pt] = arr[pt2++], cnt += mid - pt1;
    }
    for (; pt1 < mid; ++pt1) tmp[pt++] = arr[pt1];
    for (; pt2 < r; ++pt2) tmp[pt++] = arr[pt2];
    for (register int i = l; i < r; ++i) arr[i] = tmp[i];
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> k >> c;
    for (register long long i = 0; i < n; ++i) cin >> v[i];
    sort(v, v + n);
    long long v_max = v[n - 1];
    for (register long long i = 0; i < n; ++i) {
        r[i] = k * v[i] % v_max;
        v[i] = k * v[i] / v_max;
    }
    register long long lsum = 0, res = 0;
    for (register long long i = 0; i < n; ++i) {
        res += v[i] * i - lsum;
        lsum += v[i];
    }
    merge_sort(r, 0, n);
    cout << res - cnt << endl;
    return 0;
}
```
- **作者：Addicted_Game (赞：2)，4星**
    - **关键亮点**：思路简洁明了，直接指出整数圈超越次数减去米数逆序对个数即为答案，代码实现清晰。
    - **核心实现思想**：先读取输入数据，对速度排序，计算每头牛的圈数和余数，通过累加计算未处理前的值，再用归并排序求余数部分的逆序对，最后用未处理前的值减去逆序对个数得到答案。
```cpp
void m_sort(long long L, long long R) {
    if(L == R)  return ;
    long long mid = L + R >> 1, i = L, j = mid + 1, k = L;
    m_sort(L, mid);
    m_sort(mid + 1, R);
    while(i <= mid && j <= R) {
        if(r[i] <= r[j]) {
            a[k++] = r[i++];
        } else {
            a[k++] = r[j++];
            t += mid - i + 1; //求逆序对
        }
    }
    while(i <= mid) a[k++] = r[i++];
    while(j <= R) a[k++] = r[j++];
    for(long long i = L; i <= R; i++) r[i] = a[i];
}

int main() {
    scanf("%lld%lld%lld", &n, &l, &c);
    for(long long i = 1; i <= n; i++) {
        scanf("%lld", &v[i]);
    }
    sort(v + 1, v + n + 1); //排序其实是为累加整数圈与逆序对的初始化
    for(long long i = 1; i <= n; i++) {
        r[i] = l * v[i] % v[n]; //整数圈
        v[i] = l * v[i] / v[n]; //剩余的米数
    }
    long long ans = 0, sum = 0;
    for(long long i = 1; i <= n; i++) {
        ans += v[i] * (i - 1) - sum; //很巧妙，通过累加原本的超越数优化时间
        sum += v[i];
    }
    m_sort(1, n);
    printf("%lld", ans - t); //整数圈 - 小数圈
    return 0;
}
```

### 最优关键思路或技巧
- **拆分圈数**：将每头牛跑的圈数拆分为整数部分和小数部分（或余数部分），分别处理，避免小数精度问题。
- **逆序对处理**：通过求小数部分（余数部分）的逆序对，修正整数部分差值计算中多算的圈数。
- **归并排序优化**：使用归并排序求逆序对，将时间复杂度从 $O(n^2)$ 降低到 $O(n\log n)$。

### 可拓展之处
同类型题或类似算法套路：
- **区间覆盖问题**：计算区间之间的重叠次数，可将区间端点拆分为左右端点，分别处理。
- **动态统计问题**：在动态变化的数据中统计满足条件的元素对数量，可使用树状数组、线段树等数据结构维护逆序对。

### 推荐题目
- [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)：直接考察逆序对的计算。
- [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)：可用于练习树状数组的基本操作，树状数组可用于求逆序对。
- [P1309 瑞士轮](https://www.luogu.com.cn/problem/P1309)：涉及排序和统计，与本题的排序和计数思路有相似之处。

### 个人心得摘录与总结
- **作者：rainbow_cat**：考试时看错数据范围，导致只提及格分。总结是做题时要仔细看清数据范围，避免因粗心而丢分。
- **作者：kfhkx**：提到注意精度问题，在处理小数部分时要考虑精度误差，可采用相减判断等方法。 

---
处理用时：62.83秒