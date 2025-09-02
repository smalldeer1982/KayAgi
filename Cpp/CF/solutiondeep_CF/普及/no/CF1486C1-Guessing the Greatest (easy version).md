# 题目信息

# Guessing the Greatest (easy version)

## 题目描述

The only difference between the easy and the hard version is the limit to the number of queries.

This is an interactive problem.

There is an array $ a $ of $ n $ different numbers. In one query you can ask the position of the second maximum element in a subsegment $ a[l..r] $ . Find the position of the maximum element in the array in no more than 40 queries.

A subsegment $ a[l..r] $ is all the elements $ a_l, a_{l + 1}, ..., a_r $ . After asking this subsegment you will be given the position of the second maximum from this subsegment in the whole array.

## 说明/提示

In the sample suppose $ a $ is $ [5, 1, 4, 2, 3] $ . So after asking the $ [1..5] $ subsegment $ 4 $ is second to max value, and it's position is $ 3 $ . After asking the $ [4..5] $ subsegment $ 2 $ is second to max value and it's position in the whole array is $ 4 $ .

Note that there are other arrays $ a $ that would produce the same interaction, and the answer for them might be different. Example output is given in purpose of understanding the interaction.

## 样例 #1

### 输入

```
5

3

4```

### 输出

```
? 1 5

? 4 5

! 1```

# AI分析结果

### 题目内容重写

#### 猜最大值（简单版）

**题目描述**

简单版与困难版的唯一区别在于查询次数的限制。

这是一个交互式问题。

有一个包含 $n$ 个不同数字的数组 $a$。在一次查询中，你可以询问子段 $a[l..r]$ 中第二大元素的位置。请在不超出 40 次查询的情况下，找到数组中最大元素的位置。

子段 $a[l..r]$ 包含所有元素 $a_l, a_{l + 1}, ..., a_r$。在询问这个子段后，你将得到该子段中第二大元素在整个数组中的位置。

**说明/提示**

在样例中，假设 $a$ 是 $[5, 1, 4, 2, 3]$。在询问子段 $[1..5]$ 后，第二大值是 $4$，其位置是 $3$。在询问子段 $[4..5]$ 后，第二大值是 $2$，其位置是 $4$。

注意，可能存在其他数组 $a$ 会产生相同的交互结果，但它们的答案可能不同。示例输出仅用于理解交互过程。

**样例 #1**

#### 输入

```
5

3

4
```

#### 输出

```
? 1 5

? 4 5

! 1
```

### 算法分类

二分

### 题解分析与结论

该题的核心思路是通过二分查找来确定最大值的位置。由于每次查询只能得到子段中第二大元素的位置，因此需要通过多次查询来逐步缩小最大值的可能位置范围。大多数题解都采用了二分查找的策略，通过查询次大值的位置来确定最大值所在的区间，并逐步缩小范围。

### 精选题解

#### 题解1：pomelo_nene (5星)

**关键亮点**：
- 通过全局查询确定次大值的位置，然后根据次大值的位置进行二分查找。
- 代码逻辑清晰，处理了边界情况（如次大值在数组的边界时）。
- 通过二分查找逐步缩小最大值的位置范围，查询次数为 $O(\log n)$。

**核心代码**：
```cpp
int main(){
    scanf("%d",&n);
    int p;
    printf("? 1 %d\n",n);
    F;
    scanf("%d",&p);
    int l=1,r=n;
    if(p==1) {
        l=2;
    } else {
        int dk;
        printf("? %d %d\n",1,p);
        F;
        scanf("%d",&dk);
        if(dk==p) r=p-1;
        else l=p+1;
    }
    if(l==p+1) {
        while(l<r) {
            int mid=(l+r)>>1;
            printf("? %d %d\n",p,mid);
            F;
            int sp;
            scanf("%d",&sp);
            if(sp==p) r=mid;
            else l=mid+1;
        }
    } else {
        while(l<r) {
            int mid=(l+r+1)>>1;
            printf("? %d %d\n",mid,p);
            F;
            int sp;
            scanf("%d",&sp);
            if(sp==p) l=mid;
            else r=mid-1;
        }
    }
    printf("! %d",l);
    F;
    return 0;
}
```

#### 题解2：封禁用户 (4星)

**关键亮点**：
- 通过全局查询确定次大值的位置，然后根据次大值的位置进行二分查找。
- 处理了次大值在数组边界的情况，代码逻辑清晰。
- 通过二分查找逐步缩小最大值的位置范围，查询次数为 $O(\log n)$。

**核心代码**：
```cpp
int main() {
    cin >> n;
    cout << "? 1 " << n << endl;
    cin >> sec;
    if(sec == 1) {
        l = 2;
        r = n;
        while(l <= r) {
            if(l == r) {
                ans = l;
                l++;
                continue;
            }
            mid = (l + r) / 2;
            if(mid == r) {
                mid--;
            }
            if(ask(mid)) {
                ans = mid;
                r = mid;
            } else {
                l = mid + 1;
            }
        }
    }
    // 其他情况类似处理
    cout << "! " << ans;
    return 0;
}
```

#### 题解3：meyi (4星)

**关键亮点**：
- 通过全局查询确定次大值的位置，然后根据次大值的位置进行二分查找。
- 代码简洁，逻辑清晰，处理了次大值在数组边界的情况。
- 通过二分查找逐步缩小最大值的位置范围，查询次数为 $O(\log n)$。

**核心代码**：
```cpp
void dfs(int l,int r,int m){
    if(l+1>=r)print(l==m?r:l);
    int mid=l+r>>1,tmp;
    if(m<=mid){
        tmp=query(l,mid);
        if(tmp==m)dfs(l,mid,m);
        else dfs(mid,r,m==mid?m:query(mid,r));
    }
    else{
        tmp=query(mid,r);
        if(tmp==m)dfs(mid,r,m);
        else dfs(l,mid,query(l,mid));
    }
}
```

### 最优关键思路或技巧

1. **二分查找**：通过二分查找逐步缩小最大值的位置范围，查询次数为 $O(\log n)$。
2. **次大值定位**：通过全局查询确定次大值的位置，然后根据次大值的位置进行二分查找。
3. **边界处理**：处理次大值在数组边界的情况，确保二分查找的正确性。

### 可拓展之处

类似的问题可以通过二分查找和次大值定位来解决，尤其是在需要逐步缩小范围的情况下。例如，查找数组中第 $k$ 大的元素，或者在某些限制条件下查找特定元素的位置。

### 推荐题目

1. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)
2. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)
3. [P1036 选数](https://www.luogu.com.cn/problem/P1036)

---
处理用时：47.46秒