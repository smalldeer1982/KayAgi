# 题目信息

# Shuffle

## 题目描述

You are given an array consisting of $ n $ integers $ a_1 $ , $ a_2 $ , ..., $ a_n $ . Initially $ a_x = 1 $ , all other elements are equal to $ 0 $ .

You have to perform $ m $ operations. During the $ i $ -th operation, you choose two indices $ c $ and $ d $ such that $ l_i \le c, d \le r_i $ , and swap $ a_c $ and $ a_d $ .

Calculate the number of indices $ k $ such that it is possible to choose the operations so that $ a_k = 1 $ in the end.

## 说明/提示

In the first test case, it is possible to achieve $ a_k = 1 $ for every $ k $ . To do so, you may use the following operations:

1. swap $ a_k $ and $ a_4 $ ;
2. swap $ a_2 $ and $ a_2 $ ;
3. swap $ a_5 $ and $ a_5 $ .

In the second test case, only $ k = 1 $ and $ k = 2 $ are possible answers. To achieve $ a_1 = 1 $ , you have to swap $ a_1 $ and $ a_1 $ during the second operation. To achieve $ a_2 = 1 $ , you have to swap $ a_1 $ and $ a_2 $ during the second operation.

## 样例 #1

### 输入

```
3
6 4 3
1 6
2 3
5 5
4 1 2
2 4
1 2
3 3 2
2 3
1 2```

### 输出

```
6
2
3```

# AI分析结果

### 题目翻译

#### 题目描述

给定一个由 $n$ 个整数组成的数组 $a_1, a_2, \dots, a_n$。初始时，$a_x = 1$，其他所有元素均为 $0$。

你需要执行 $m$ 次操作。在第 $i$ 次操作中，你选择两个下标 $c$ 和 $d$，满足 $l_i \le c, d \le r_i$，并交换 $a_c$ 和 $a_d$。

计算最终有多少个下标 $k$ 满足，通过选择合适的操作，可以使 $a_k = 1$。

#### 说明/提示

在第一个测试用例中，可以使 $a_k = 1$ 对于每一个 $k$。为此，你可以使用以下操作：

1. 交换 $a_k$ 和 $a_4$；
2. 交换 $a_2$ 和 $a_2$；
3. 交换 $a_5$ 和 $a_5$。

在第二个测试用例中，只有 $k = 1$ 和 $k = 2$ 是可能的答案。要使 $a_1 = 1$，你必须在第二次操作中交换 $a_1$ 和 $a_1$。要使 $a_2 = 1$，你必须在第二次操作中交换 $a_1$ 和 $a_2$。

#### 样例 #1

##### 输入

```
3
6 4 3
1 6
2 3
5 5
4 1 2
2 4
1 2
3 3 2
2 3
1 2
```

##### 输出

```
6
2
3
```

### 算法分类
模拟

### 题解分析与结论

#### 题解对比与评分

1. **Milthm (3星)**
   - **关键亮点**：通过维护一个区间来表示可能为1的位置，逐步扩展区间。
   - **难点**：如何高效地判断和扩展区间。
   - **代码实现**：简洁明了，直接通过判断区间重叠来扩展区间。
   - **评分理由**：思路清晰，代码可读性好，但缺乏对复杂情况的深入分析。

2. **Error_Eric (4星)**
   - **关键亮点**：通过举例推导出区间扩展的规律，并给出了详细的解释。
   - **难点**：如何从简单例子中推导出一般规律。
   - **代码实现**：与Milthm类似，但解释更为详细。
   - **评分理由**：思路清晰，解释详细，代码实现简洁，优化程度高。

3. **45dinо (4星)**
   - **关键亮点**：通过合并区间的思路，逐步扩展可能为1的区间。
   - **难点**：如何高效地合并区间。
   - **代码实现**：通过遍历操作区间，逐步合并区间。
   - **评分理由**：思路清晰，代码实现简洁，优化程度高。

4. **lhs_chris (3星)**
   - **关键亮点**：从暴力解法出发，逐步优化到区间扩展的思路。
   - **难点**：如何从暴力解法中提取出优化思路。
   - **代码实现**：与Milthm和Error_Eric类似，但增加了暴力解法的对比。
   - **评分理由**：思路清晰，代码可读性好，但优化思路与其他题解重复。

#### 最优关键思路与技巧

- **区间扩展**：通过维护一个区间来表示可能为1的位置，逐步扩展区间。这是所有题解的核心思路。
- **高效判断**：通过判断操作区间与当前区间的重叠部分，快速扩展区间，避免不必要的遍历。

#### 可拓展之处

- **类似问题**：类似的问题可以出现在需要维护区间或集合的场景中，如区间合并、区间查询等。
- **算法套路**：区间扩展的思路可以应用于其他需要动态维护区间或集合的问题，如区间覆盖、区间查询等。

### 推荐题目

1. **P1886 滑动窗口**（区间维护）
2. **P3372 线段树 1**（区间查询与修改）
3. **P3368 树状数组 1**（区间查询与修改）

### 个人心得摘录

- **Error_Eric**：通过举例推导出区间扩展的规律，强调了从简单例子中推导出一般规律的重要性。
- **45dinо**：通过合并区间的思路，强调了高效合并区间的重要性，避免了不必要的遍历。

### 核心代码片段

```cpp
// Milthm的代码片段
int t,n,m,x,l,r,ql,qr;
int main(){
    cin>>t;
    while(t--){
        cin>>n>>x>>m;
        ql=qr=x;//初始化区间为 [x,x]
        while(m--){
            cin>>l>>r;
            if(l<=ql&&ql<=r||l<=qr&&qr<=r){//如果左端点在区间内或右端点在区间内就扩大（不然两个区间绝对不可能重合）
                ql=min(ql,l);//扩大左端点
                qr=max(qr,r);//扩大右端点
            }
        }
        cout<<qr-ql+1<<endl;//输出区间长度
    }
    return 0;
}
```

```cpp
// Error_Eric的代码片段
int t,n,x,m,xi,yi,fr,to;
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d%d%d",&n,&x,&m),fr=to=x;//输入，初始区间为[x,x]。
        for(int i=1;i<=m;i++){
            scanf("%d%d",&xi,&yi);
            if((not(xi>to) and (not(yi<fr))))
                fr=min(fr,xi),to=max(to,yi);
        }
        printf("%d\n",to-fr+1);
    }
}
```

```cpp
// 45dinо的代码片段
int t,n,x,m,L,R,k,l[101],r[101];
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d%d%d",&n,&x,&m);
        k=L=R=0;
        for(int i=1;i<=m;i++)
            scanf("%d%d",&l[i],&r[i]);
        for(int i=1;i<=m;i++)
            if(l[i]<=x&&x<=r[i]){
                k=i;
                L=l[i];
                R=r[i];
                break;
            }
        for(int i=k+1;i<=m;i++){
            if(r[i]<L) continue;
            if(l[i]>R) continue;
            L=min(l[i],L);
            R=max(r[i],R);
        }
        cout<<R-L+1<<endl;
    }
    return 0;
}
```

---
处理用时：44.40秒