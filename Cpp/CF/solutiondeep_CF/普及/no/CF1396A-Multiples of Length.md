# 题目信息

# Multiples of Length

## 题目描述

You are given an array $ a $ of $ n $ integers.

You want to make all elements of $ a $ equal to zero by doing the following operation exactly three times:

- Select a segment, for each number in this segment we can add a multiple of $ len $ to it, where $ len $ is the length of this segment (added integers can be different).

It can be proven that it is always possible to make all elements of $ a $ equal to zero.

## 样例 #1

### 输入

```
4
1 3 2 4```

### 输出

```
1 1 
-1
3 4
4 2
2 4
-3 -6 -6```

# AI分析结果

### 题目内容重写

**题目描述**

给定一个包含 $n$ 个整数的数组 $a$。

你需要通过恰好三次操作，使得数组 $a$ 中的所有元素都变为零。每次操作如下：

- 选择一个区间，对于该区间中的每个元素，可以加上一个该区间长度的倍数（不同的元素可以加不同的数）。

可以证明，总是存在一种方法使得所有元素最终都变为零。

**样例 #1**

输入：
```
4
1 3 2 4
```

输出：
```
1 1 
-1
3 4
4 2
2 4
-3 -6 -6
```

### 算法分类
构造

### 题解分析与结论

本题的核心是通过三次操作将数组中的所有元素变为零。各题解的思路大多集中在如何通过前两次操作将数组中的元素变为某个数的倍数，然后在最后一次操作中将这些倍数变为零。具体来说，大多数题解都采用了以下策略：

1. **第一次操作**：选择一个区间，将区间内的元素加上某个数，使得这些元素变为某个数的倍数。
2. **第二次操作**：选择另一个区间，将区间内的元素加上某个数，使得这些元素变为另一个数的倍数。
3. **第三次操作**：选择整个数组，将数组中的所有元素变为零。

尽管各题解的具体实现细节有所不同，但核心思路基本一致。以下是几条评分较高的题解及其亮点：

### 高星题解

#### 题解作者：寒鸽儿 (赞：11)
**星级：5星**
**关键亮点**：
- 通过前两次操作将数组中的元素变为 $n$ 的倍数，最后一次操作将整个数组变为零。
- 代码简洁，逻辑清晰，易于理解。

**核心代码**：
```cpp
cout << n << ' ' << n << endl;
cout << n - a[n] << endl;
cout << 1 << ' ' << n - 1 << endl;
rep(i,1,n-1) {
    cout << ((n - 1) * a[i]) << ' ';
}
cout << endl;
a[n] = n;
cout << 1 << ' ' << n << endl;
rep(i,1,n-1) {
    cout << -n * a[i] << ' ';
}
cout << -n << endl;
```

#### 题解作者：钓鱼王子 (赞：4)
**星级：4星**
**关键亮点**：
- 通过前两次操作将数组中的元素变为 $n$ 的倍数，最后一次操作将整个数组变为零。
- 代码逻辑清晰，但相比寒鸽儿的题解稍显冗长。

**核心代码**：
```cpp
puts("1 1");
printf("%lld\n",-a[1]);
if(n==1){puts("1 1");puts("0");puts("1 1");puts("0");return 0;}
a[1]=0;
printf("%d %lld\n",2,n);
for(re int i=2;i<=n;++i){
    re int x=a[i]%n+n;
    x%=n;
    re int y=x*(n-1);
    a[i]+=y;
    printf("%lld ",y);
}puts("");
printf("1 %lld\n",n);
for(re int i=1;i<=n;++i)printf("%lld ",-a[i]);
```

#### 题解作者：灵茶山艾府 (赞：2)
**星级：4星**
**关键亮点**：
- 通过前两次操作将数组中的元素变为 $n$ 的倍数，最后一次操作将整个数组变为零。
- 代码简洁，逻辑清晰，易于理解。

**核心代码**：
```go
Fprintln(out, "1 1\n", -a[0])
a[0] = 0
Fprintln(out, 2, n)
for i, v := range a[1:] {
    Fprint(out, v*(n-1), " ")
    a[i+1] += v * (n - 1)
}
Fprintln(out)
Fprintln(out, 1, n)
for _, v := range a {
    Fprint(out, -v, " ")
}
```

### 最优关键思路
通过前两次操作将数组中的元素变为某个数的倍数，然后在最后一次操作中将整个数组变为零。这种构造方法简洁高效，适用于大多数情况。

### 可拓展之处
类似的问题可以通过构造特定的操作序列来解决，关键在于如何通过有限的操作将问题转化为易于处理的形式。例如，可以通过多次操作将数组中的元素变为某个数的倍数，然后再进行全局操作。

### 推荐题目
1. [CF1397C - Multiples of Length](https://www.luogu.com.cn/problem/CF1397C)
2. [CF1396A - Multiples of Length](https://www.luogu.com.cn/problem/CF1396A)
3. [CF1397B - Multiples of Length](https://www.luogu.com.cn/problem/CF1397B)

### 个人心得摘录
- **寒鸽儿**：通过前两次操作将数组中的元素变为 $n$ 的倍数，最后一次操作将整个数组变为零。这种思路简洁明了，易于实现。
- **钓鱼王子**：通过前两次操作将数组中的元素变为 $n$ 的倍数，最后一次操作将整个数组变为零。代码逻辑清晰，但稍显冗长。
- **灵茶山艾府**：通过前两次操作将数组中的元素变为 $n$ 的倍数，最后一次操作将整个数组变为零。代码简洁，逻辑清晰，易于理解。

---
处理用时：40.01秒