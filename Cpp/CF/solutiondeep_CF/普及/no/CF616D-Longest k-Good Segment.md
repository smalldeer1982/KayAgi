# 题目信息

# Longest k-Good Segment

## 题目描述

The array $ a $ with $ n $ integers is given. Let's call the sequence of one or more consecutive elements in $ a $ segment. Also let's call the segment k-good if it contains no more than $ k $ different values.

Find any longest k-good segment.

As the input/output can reach huge size it is recommended to use fast input/output methods: for example, prefer to use scanf/printf instead of cin/cout in C++, prefer to use BufferedReader/PrintWriter instead of Scanner/System.out in Java.

## 样例 #1

### 输入

```
5 5
1 2 3 4 5
```

### 输出

```
1 5
```

## 样例 #2

### 输入

```
9 3
6 5 1 2 3 2 1 4 5
```

### 输出

```
3 7
```

## 样例 #3

### 输入

```
3 1
1 2 3
```

### 输出

```
1 1
```

# AI分析结果



# 中文重写题目

## 题目描述

给定一个包含 $n$ 个整数的数组 $a$。我们称由连续元素组成的子数组为段。若某个段包含不超过 $k$ 种不同的值，则称为 k-good 段。

请找出任意一个最长的 k-good 段，输出其起始和结束位置（下标从 1 开始）。

由于输入输出规模可能很大，建议使用快速输入输出方法：例如在 C++ 中优先使用 scanf/printf 代替 cin/cout，在 Java 中使用 BufferedReader/PrintWriter 代替 Scanner/System.out。

## 样例 #1

### 输入
```
5 5
1 2 3 4 5
```

### 输出
```
1 5
```

## 样例 #2

### 输入
```
9 3
6 5 1 2 3 2 1 4 5
```

### 输出
```
3 7
```

## 样例 #3

### 输入
```
3 1
1 2 3
```

### 输出
```
1 1
```

# 算法分类
双指针（滑动窗口）

# 题解分析与结论

**核心思路对比**：
1. 所有题解均采用滑动窗口思想，维护当前窗口内的不同元素数量
2. 使用数组桶（值域较小）或哈希表（通用）统计元素出现次数
3. 右指针扩展窗口，当不同元素超过k时，左指针收缩窗口
4. 时间复杂度均为O(n)，空间复杂度O(值域)或O(不同元素数)

**最优技巧总结**：
- 双指针维护最大有效窗口：右指针主动扩展，左指针被动收缩
- 桶数组实现高效计数：适用于值域已知的情况（本题值域1e6）
- 实时维护当前不同元素数：通过判断元素出现次数是否为0或1来更新计数器

# 精选题解

## 1. hxhhxh（5星）
**关键亮点**：
- 代码简洁直观，逻辑清晰易读
- 严格维护窗口的有效性，及时收缩左边界
- 变量命名规范，ansl/ansr直接记录最优解

**核心代码**：
```cpp
int main(){
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1,l=1,r=1;i<=n;i++){
        r = i;
        cnt[a[i]]++;
        if(cnt[a[i]]==1) t++;
        while(t>m){
            cnt[a[l]]--;
            if(cnt[a[l]]==0) t--;
            l++;
        }
        if(r-l > ansr-ansl) ansr=r, ansl=l;
    }
    cout<<ansl<<" "<<ansr;
}
```

## 2. wind_whisper（4星）
**关键亮点**：
- 精简的代码结构，单循环完成所有操作
- 统一使用前缀差计算窗口长度
- 通过加减计数器严格保证窗口有效性

**核心代码**：
```cpp
signed main(){
    n=read();m=read();
    int l=1,r=0;
    while(r<n){
        now += (++bac[a[++r]] == 1);
        while(now>m) now -= (--bac[a[l++]] == 0);
        if(r-l+1 > ans) ans=r-l+1, L=l, R=r;
    }
    printf("%d %d\n",L,R);
}
```

## 3. 沉石鱼惊旋（4星）
**关键亮点**：
- 极简实现风格，仅用单循环维护窗口
- 使用后缀差计算窗口长度
- 通过简洁的条件判断维护计数器

**核心代码**：
```cpp
int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    int l=1,r=0;
    while(r<n){
        sum += ((++cnt[a[++r]]) == 1);
        while(sum>k) sum -= (!(--cnt[a[l++]]));
        if(r-l+1>ansr-ansl+1) ansr=r, ansl=l;
    }
    cout<<ansl<<" "<<ansr<<endl;
}
```

# 拓展练习
1. [P340 最长无重复字符的子串](https://www.luogu.com.cn/problem/P340)（滑动窗口基础）
2. [P1712 [NOI2016] 区间](https://www.luogu.com.cn/problem/P1712)（滑动窗口+离散化）
3. [P4551 最长平衡子串](https://www.luogu.com.cn/problem/P4551)（滑动窗口变式）

---
处理用时：86.10秒