# 题目信息

# Crazy Diamond

## 题目描述

You are given a permutation $ p $ of integers from $ 1 $ to $ n $ , where $ n $ is an even number.

Your goal is to sort the permutation. To do so, you can perform zero or more operations of the following type:

- take two indices $ i $ and $ j $ such that $ 2 \cdot |i - j| \geq n $ and swap $ p_i $ and $ p_j $ .

There is no need to minimize the number of operations, however you should use no more than $ 5 \cdot n $ operations. One can show that it is always possible to do that.

## 说明/提示

In the first example, when one swap elements on positions $ 1 $ and $ 2 $ , the array becomes sorted.

In the second example, pay attention that there is no need to minimize number of swaps.

In the third example, after swapping elements on positions $ 1 $ and $ 5 $ the array becomes: $ [4, 5, 3, 1, 2, 6] $ . After swapping elements on positions $ 2 $ and $ 5 $ the array becomes $ [4, 2, 3, 1, 5, 6] $ and finally after swapping elements on positions $ 1 $ and $ 4 $ the array becomes sorted: $ [1, 2, 3, 4, 5, 6] $ .

## 样例 #1

### 输入

```
2
2 1
```

### 输出

```
1
1 2```

## 样例 #2

### 输入

```
4
3 4 1 2
```

### 输出

```
4
1 4
1 4
1 3
2 4
```

## 样例 #3

### 输入

```
6
2 5 3 1 4 6
```

### 输出

```
3
1 5
2 5
1 4
```

# AI分析结果

### 题目内容（中文重写）
# 疯狂钻石

## 题目描述
给定一个由 1 到 n 的整数组成的排列 p，其中 n 是偶数。

你的目标是对这个排列进行排序。为此，你可以执行零次或多次以下类型的操作：
- 选择两个索引 i 和 j，使得 2 * |i - j| ≥ n，然后交换 p[i] 和 p[j]。

不需要最小化操作次数，但操作次数不应超过 5 * n 次。可以证明，总是可以做到这一点。

## 说明/提示
在第一个样例中，当交换位置 1 和 2 的元素时，数组就变成有序的了。

在第二个样例中，请注意不需要最小化交换次数。

在第三个样例中，交换位置 1 和 5 的元素后，数组变为：[4, 5, 3, 1, 2, 6]。交换位置 2 和 5 的元素后，数组变为 [4, 2, 3, 1, 5, 6]，最后交换位置 1 和 4 的元素后，数组变为有序：[1, 2, 3, 4, 5, 6]。

## 样例 #1
### 输入
```
2
2 1
```
### 输出
```
1
1 2
```

## 样例 #2
### 输入
```
4
3 4 1 2
```
### 输出
```
4
1 4
1 4
1 3
2 4
```

## 样例 #3
### 输入
```
6
2 5 3 1 4 6
```
### 输出
```
3
1 5
2 5
1 4
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是通过合理的交换操作将给定的排列排序，且操作次数不超过 5 * n 次。不同题解的具体做法有所差异，但大多围绕元素的位置关系和交换规则进行分类讨论。

- **思路对比**：
    - Fading 的题解将序列分成两段，利用 1 和 n 两个位置，按照特定顺序依次归位元素。
    - _此去经年 的题解通过分类讨论元素间的距离和位置关系，确定交换策略。
    - FiraCode 的题解依次从小到大考虑元素归位，根据元素前后的数的个数决定交换步骤。
    - FutaRimeWoawaSete 的题解给出了不同复杂度的构造方法，包括 3n、2.25n 和 2n 的做法。
    - Ousmane_Dembele 的题解根据元素位置和距离的不同情况，定义不同的交换函数。

- **算法要点**：
    - 各题解都利用了 2 * |i - j| ≥ n 这个交换条件。
    - 多数题解采用分类讨论的方法，根据元素的位置和距离关系确定交换步骤。

- **解决难点**：
    - 如何在不超过 5 * n 次操作的限制下将排列排序。
    - 处理元素间距离不满足交换条件的情况。

### 所选题解
- **Fading（4星）**：
    - **关键亮点**：思路清晰，通过将序列分段，利用 1 和 n 位置进行交换，代码实现简洁，复杂度为 3n。
    - **个人心得**：作者认为这是自己的第一反应，且比标程更优。
- **_此去经年（4星）**：
    - **关键亮点**：详细地进行分类讨论，配有图示，思路直观易懂。
    - **个人心得**：作者认为这题没有紫题难度。
- **FutaRimeWoawaSete（4星）**：
    - **关键亮点**：给出了多种复杂度的构造方法，对问题的分析较为深入。
    - **个人心得**：作者考场上想写 2.25n 的做法，但实现出来是 3.5n 的。

### 重点代码
#### Fading 的题解
```cpp
inline void myswap(int x,int y){
    swap(a[x],a[y]);swap(x,y);
    pos[a[y]]=y;pos[a[x]]=x;
    dl.push_back(make_pair(y,x));
}
signed main(){
    n=read();
    for (int i=1;i<=n;i++){
        a[i]=read();pos[a[i]]=i;
    }
    if (n==2){
        if (a[1]!=1){
            puts("1");
            puts("1 2");
        }else{
            puts("0");
        }
        return 0;
    }
    for (int i=n/2;i;i--){
        if (a[i]!=i){
            if (pos[i]<=i){
                myswap(pos[i],n);
                myswap(i,n);
            }else{
                if (abs(pos[i]-i)>=n/2) myswap(pos[i],i);
                else{
                    myswap(pos[i],1);
                    myswap(pos[i],n);
                    myswap(pos[i],i);
                }
            }
        }
        if (a[n-i+1]!=n-i+1){
            if (pos[n-i+1]>=n-i+1){
                myswap(pos[n-i+1],1);
                myswap(n-i+1,1);
            }else{
                if (abs(pos[n-i+1]-(n-i+1)>=n/2)) myswap(pos[n-i+1],n-i+1);
                else{
                    myswap(pos[n-i+1],n);
                    myswap(pos[n-i+1],1);
                    myswap(pos[n-i+1],n-i+1);
                }
            }
        }
    }
    cout<<(int)dl.size()<<endl;
    for (auto x:dl){
        printf("%d %d\n",min(x.first,x.second),max(x.first,x.second));
    }
    return 0;
}
```
**核心实现思想**：先读取输入，对于 n = 2 的情况特殊处理。然后从序列中间向两边遍历，根据元素的位置和距离关系，利用 myswap 函数进行交换操作，最后输出交换次数和交换的索引对。

#### _此去经年 的题解（未给出完整代码，思路为主）
核心思路是根据元素间的距离和位置关系进行分类讨论：
1. 若 $dis(x,y) >= len/2$，直接交换。
2. 若 $dis(x,y) < len/2(x<mid,y>mid)$，按图示进行五次交换。
3. 若 $dis(x,y) < len/2(x<mid,y<mid)$，类似情况 2 进行交换。

#### FutaRimeWoawaSete 的题解
```cpp
inline void Swap(int x,int y)
{
    if(x == y) return;
    if(x <= n / 2 && y <= n / 2)
    {
        int R = n;
        swap(now[a[x]] , now[a[R]]) ; swap(a[x] , a[R]) ; Pt[++ len] = mp(x , R);
        swap(now[a[y]] , now[a[R]]) ; swap(a[y] , a[R]) ; Pt[++ len] = mp(y , R);
        swap(now[a[x]] , now[a[R]]) ; swap(a[x] , a[R]) ; Pt[++ len] = mp(x , R);
        return;
    }
    if(x > n / 2 && y > n / 2)
    {
        int R = 1;
        swap(now[a[x]] , now[a[R]]) ; swap(a[x] , a[R]) ; Pt[++ len] = mp(x , R);
        swap(now[a[y]] , now[a[R]]) ; swap(a[y] , a[R]) ; Pt[++ len] = mp(y , R);
        swap(now[a[x]] , now[a[R]]) ; swap(a[x] , a[R]) ; Pt[++ len] = mp(x , R);
        return;
    }
    swap(now[a[x]] , now[a[y]]) ; swap(a[x] , a[y]) ; Pt[++ len] = mp(x , y);
}
```
**核心实现思想**：定义 Swap 函数，根据 x 和 y 的位置关系进行不同的交换操作，若 x 和 y 都在左半部分或右半部分，借助 1 或 n 位置进行交换，否则直接交换。

### 最优关键思路或技巧
- 利用 1 和 n 两个特殊位置，将不满足交换条件的元素通过这两个位置间接交换。
- 采用分类讨论的方法，根据元素的位置和距离关系确定交换策略。

### 可拓展之处
同类型题或类似算法套路：
- 其他构造类的排序问题，可能会有不同的交换规则和限制条件。
- 涉及元素位置关系和操作次数限制的问题，可以借鉴分类讨论和利用特殊位置的思路。

### 推荐洛谷题目
1. P1012 拼数
2. P1047 校门外的树
3. P1059 明明的随机数

### 个人心得摘录与总结
- Fading：认为自己的解法是第一反应且比标程更优，体现了对问题的快速思考和独特见解。
- _此去经年：觉得题目难度没有达到紫题水平，反映出对题目的整体把握和自信。
- FutaRimeWoawaSete：考场上想写 2.25n 的做法但实现出错，提醒我们在实际考试中要注意代码实现的准确性。

---
处理用时：64.30秒