# 题目信息

# Two Arrays

## 题目描述

You are given two arrays of integers $ a_1, a_2, \ldots, a_n $ and $ b_1, b_2, \ldots, b_n $ .

Let's define a transformation of the array $ a $ :

1. Choose any non-negative integer $ k $ such that $ 0 \le k \le n $ .
2. Choose $ k $ distinct array indices $ 1 \le i_1 < i_2 < \ldots < i_k \le n $ .
3. Add $ 1 $ to each of $ a_{i_1}, a_{i_2}, \ldots, a_{i_k} $ , all other elements of array $ a $ remain unchanged.
4. Permute the elements of array $ a $ in any order.

Is it possible to perform some transformation of the array $ a $ exactly once, so that the resulting array is equal to $ b $ ?

## 说明/提示

In the first test case, we can make the following transformation:

- Choose $ k = 2 $ .
- Choose $ i_1 = 1 $ , $ i_2 = 2 $ .
- Add $ 1 $ to $ a_1 $ and $ a_2 $ . The resulting array is $ [0, 2, 0] $ .
- Swap the elements on the second and third positions.

In the second test case there is no suitable transformation.

In the third test case we choose $ k = 0 $ and do not change the order of elements.

## 样例 #1

### 输入

```
3
3
-1 1 0
0 0 2
1
0
2
5
1 2 3 4 5
1 2 3 4 5```

### 输出

```
YES
NO
YES```

# AI分析结果

### 题目内容
# 两个数组

## 题目描述
给定两个整数数组 $a_1, a_2, \ldots, a_n$ 和 $b_1, b_2, \ldots, b_n$ 。

定义数组 $a$ 的一种变换：
1. 选择任意一个非负整数 $k$ ，使得 $0 \le k \le n$ 。
2. 选择 $k$ 个不同的数组下标 $1 \le i_1 < i_2 < \ldots < i_k \le n$ 。
3. 对 $a_{i_1}, a_{i_2}, \ldots, a_{i_k}$ 中的每一个元素加 $1$ ，数组 $a$ 的其他元素保持不变。
4. 以任意顺序重新排列数组 $a$ 的元素。

是否有可能恰好对数组 $a$ 执行一次上述变换，使得得到的数组与 $b$ 相等？

## 说明/提示
在第一个测试用例中，我们可以进行如下变换：
- 选择 $k = 2$ 。
- 选择 $i_1 = 1$ ，$i_2 = 2$ 。
- 对 $a_1$ 和 $a_2$ 加 $1$ 。得到的数组为 $[0, 2, 0]$ 。
- 交换第二个和第三个位置的元素。

在第二个测试用例中，不存在合适的变换。

在第三个测试用例中，我们选择 $k = 0$ ，并且不改变元素的顺序。

## 样例 #1
### 输入
```
3
3
-1 1 0
0 0 2
1
0
2
5
1 2 3 4 5
1 2 3 4 5
```
### 输出
```
YES
NO
YES
```

### 算法分类
排序

### 综合分析与结论
这些题解主要分为两种思路。一种是以“Morgen_Kornblume”为代表，利用网络流建模解题，建源点、汇点和中间点，通过边的连接和流量判断能否实现数组变换；另一种是以“DPseud”“mzyc_jx”等为代表，利用排序的思想，将两个数组排序后，通过比较对应位置元素差值是否为0或1来判断能否实现变换。后一种思路更为直观和简洁，代码实现难度较低，而网络流方法虽然通用性强，但对于本题数据规模而言相对复杂。

### 所选的题解
- **作者：DPseud (5星)**
    - **关键亮点**：思路简洁清晰，代码简短高效，直接抓住排序后数组元素差值判断的核心，使用goto语句简化循环结构。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    register int t,i=0;
    cin>>t;
    forr:int n,a[111],b[111];
    memset(a,0,sizeof(a)),memset(b,0,sizeof(b));
    cin>>n;
    for(int i=0;i<n;i++)scanf("%d",&a[i]);
    for(int i=0;i<n;i++)scanf("%d",&b[i]);
    sort(a,a+n),sort(b,b+n);
    bool bj=0;
    for(int i=0;i<n;i++)if(b[i]-a[i]<0||b[i]-a[i]>1)bj=1;
    if(bj==0)puts("YES");
    else puts("NO");
    i++;
    if(i<t)goto forr;
    return 0;
}
```
    - **核心实现思想**：读入数据后对两个数组排序，遍历比较对应位置元素差值，若差值不在0到1之间则标记不能转换，最后根据标记输出结果。
- **作者：mzyc_jx (4星)**
    - **关键亮点**：思路清晰易懂，代码结构简单，通过排序后比较对应元素差值，利用goto语句跳出循环，使代码简洁明了。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105],b[105]; 
int main()
{
    int t,n;
    cin>>t;
    while(cin>>n)
    {
        for(int i=1;i<=n;i++)
        cin>>a[i];
        for(int i=1;i<=n;i++)
        cin>>b[i];
        sort(a+1,a+n+1);
        sort(b+1,b+n+1);
        for(int i=1;i<=n;i++)
        if(b[i]-a[i]!=1&&b[i]!=a[i])
        {
            cout<<"NO"<<"\n";
            goto end;
        }
        cout<<"YES"<<"\n";
        end:;
    }
    return 0;
}
```
    - **核心实现思想**：循环读入数据，对数组排序后遍历比较对应元素，若不满足差值为0或1则输出NO并跳出，否则输出YES。

### 最优关键思路或技巧
利用排序将无序问题转化为有序对应问题，通过比较排序后数组对应位置元素差值是否为0或1，快速判断能否通过给定操作实现数组变换，这种方法简洁高效，避免了复杂的操作模拟。

### 同类型题或类似算法套路拓展
此类题目通常涉及数组元素的操作与比较，关键在于利用可重排的特性，通过排序简化问题，聚焦于元素间的数值关系判断。类似套路可应用于其他涉及数组变换并判断可行性的问题。

### 洛谷相似题目推荐
- [P1923 【深基9.例4】求第 k 小的数](https://www.luogu.com.cn/problem/P1923)：通过排序求解数组中第k小的数，考察对排序后数组元素位置与数值关系的理解。
- [P1177 【模板】快速排序](https://www.luogu.com.cn/problem/P1177)：基础的快速排序模板题，掌握快速排序算法有助于理解本题中排序优化的思路。
- [P5718 【深基4.例11】数列求和](https://www.luogu.com.cn/problem/P5718)：虽然重点在数列求和，但同样涉及对数组元素的处理，可锻炼数组操作与逻辑判断能力。

### 个人心得摘录与总结
“Morgen_Kornblume”提到赛时pretest太弱被Hack，强调了测试数据强度对代码正确性检验的重要性，在解题时不能仅依赖弱测试数据，需全面考虑边界和特殊情况。 

---
处理用时：40.33秒