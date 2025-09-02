# 题目信息

# Beautiful Array

## 题目描述

Stanley defines the beauty of an array $ a $ of length $ n $ , which contains non-negative integers, as follows: $ $$$\sum\limits_{i = 1}^{n} \left \lfloor \frac{a_{i}}{k} \right \rfloor, $ $  which means that we divide each element by  $ k $ , round it down, and sum up the resulting values.</p><p>Stanley told Sam the integer  $ k $  and asked him to find an array  $ a $  of  $ n $  non-negative integers, such that the beauty is equal to  $ b $  and the sum of elements is equal to  $ s$$$. Help Sam — find any of the arrays satisfying the conditions above.

## 说明/提示

In the first, the second, the fifth and the sixth test cases of the example it is possible to show that such array does not exist.

In the third testcase of the example $ a = [0, 0, 19] $ . The sum of elements in it is equal to 19, the beauty of it is equal to $ \left ( \left \lfloor \frac{0}{6} \right \rfloor + \left \lfloor \frac{0}{6} \right \rfloor + \left \lfloor \frac{19}{6} \right \rfloor \right ) = (0 + 0 + 3) = 3 $ .

In the fourth testcase of the example $ a = [0, 3, 3, 3, 29] $ . The sum of elements in it is equal to $ 38 $ , the beauty of it is equal to $ (0 + 0 + 0 + 0 + 7) = 7 $ .

## 样例 #1

### 输入

```
8
1 6 3 100
3 6 3 12
3 6 3 19
5 4 7 38
5 4 7 80
99978 1000000000 100000000 1000000000000000000
1 1 0 0
4 1000000000 1000000000 1000000000000000000```

### 输出

```
-1
-1
0 0 19
0 3 3 3 29
-1
-1
0
0 0 0 1000000000000000000```

# AI分析结果

### 题目中文重写
## 美丽数组

### 题目描述
斯坦利定义了一个长度为 $n$ 的非负整数数组 $a$ 的美丽值如下：
$$\sum\limits_{i = 1}^{n} \left \lfloor \frac{a_{i}}{k} \right \rfloor$$
这意味着我们将每个元素除以 $k$，向下取整，然后将结果相加。

斯坦利告诉了山姆整数 $k$，并要求他找到一个长度为 $n$ 的非负整数数组 $a$，使得该数组的美丽值等于 $b$，且数组元素的总和等于 $s$。请帮助山姆找到满足上述条件的任意一个数组。

### 说明/提示
在样例的第一、二、五和六个测试用例中，可以证明不存在这样的数组。

在样例的第三个测试用例中，$a = [0, 0, 19]$。数组元素的总和为 19，其美丽值为 $\left ( \left \lfloor \frac{0}{6} \right \rfloor + \left \lfloor \frac{0}{6} \right \rfloor + \left \lfloor \frac{19}{6} \right \rfloor \right ) = (0 + 0 + 3) = 3$。

在样例的第四个测试用例中，$a = [0, 3, 3, 3, 29]$。数组元素的总和为 $38$，其美丽值为 $(0 + 0 + 0 + 0 + 7) = 7$。

### 样例 #1
#### 输入
```
8
1 6 3 100
3 6 3 12
3 6 3 19
5 4 7 38
5 4 7 80
99978 1000000000 100000000 1000000000000000000
1 1 0 0
4 1000000000 1000000000 1000000000000000000
```

#### 输出
```
-1
-1
0 0 19
0 3 3 3 29
-1
-1
0
0 0 0 1000000000000000000
```

### 综合分析与结论
这些题解的核心思路基本一致，都是先判断是否有解，再构造满足条件的数组。判断无解的关键条件是 $k \times b \le s \le k \times b + n \times (k - 1)$。构造数组时，通常先让一个元素满足美丽值的要求，再将剩余的和分配到其他元素上，且每个元素增加的值不超过 $k - 1$。

### 所选题解
- **作者：liangbowen（5星）**
    - **关键亮点**：思路清晰，详细推导了无解的条件，代码中使用了快读快写优化，注释丰富，可读性强。
    - **核心代码**：
```cpp
void solve()
{
    LL n = read(), k = read(), b = read(), s = read();
    if (b * k <= s && s <= b * k + n * (k-1))
    {
        a[1] = b * k;
        LL left = s - b * k;
        for (int i = 1; i <= n; i++, space)
        {
            if (left >= k - 1) write(a[i] + k - 1), left -= (k - 1);
            else if (left!= 0) write(a[i] + left), left = 0;
            else write(a[i]);
        }
        endl;
    }
    else puts("-1");
}
```
核心实现思想：先判断是否满足有解条件，若满足则将 $a_1$ 赋值为 $k \times b$，计算剩余的和 $left$，然后遍历数组，将 $left$ 尽可能多地分配到每个元素上。

- **作者：Haber（4星）**
    - **关键亮点**：对思路的分析详细，明确指出优先考虑约束强度大的条件，代码简洁，逻辑清晰。
    - **核心代码**：
```cpp
while(t--){
    cin>>n>>k>>b>>s;
    if(k*b>s||k*b+n*(k-1)<s){
        cout<<-1<<endl;
        continue;
    }
    ll res=s-b*k;
    ll now=min(res,k-1);
    cout<<k*b+now<<" ";
    res-=now;
    for(int i=2;i<=n;i++){
        now=min(res,k-1);
        cout<<now<<" ";
        res-=now;
    }
    cout<<endl;
}
```
核心实现思想：先判断是否有解，若有解则计算需要调整的量 $res$，将 $res$ 分配到数组元素上，每个元素分配的最大值为 $\min(k - 1, res)$。

- **作者：cachejtt（4星）**
    - **关键亮点**：对有解条件进行了详细的推导和正确性证明，代码使用了宏定义，结构清晰。
    - **核心代码**：
```cpp
rep(kk,1,t){
    cin>>n>>k>>b>>s;
    ms(a,0);
    if(k*b>s || k*b+n*(k-1)<s){
        cout<<"-1"<<endl;
    }
    else{
        s-=b*k;
        a[1]=b*k;
        rep(i,1,n){
            if(s>=0){
                a[i]+=min(k-1,s);
                s-=min(k-1,s);
            }
        }
        rep(i,1,n)cout<<a[i]<<" ";
        cout<<endl;
    }
}
```
核心实现思想：先判断是否有解，若有解则将 $a_1$ 赋值为 $k \times b$，将剩余的和 $s$ 分配到数组元素上，每个元素分配的最大值为 $\min(k - 1, s)$。

### 最优关键思路或技巧
- 优先考虑约束强度大的条件，本题中优先考虑美丽值的条件，简化问题。
- 通过数学推导得出无解的条件，避免不必要的计算。
- 贪心思想，在构造数组时，尽可能让每个元素分配到最大的值，同时满足条件。

### 可拓展之处
同类型题可能会有更多的约束条件，或者改变数组元素的取值范围。类似的算法套路是先分析约束条件，找出无解的情况，再通过贪心或其他方法构造满足条件的解。

### 推荐题目
- [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)：考察对问题的分析和构造解的能力。
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)：需要根据条件构造合适的数据结构来解决问题。
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：运用贪心思想解决问题。

### 个人心得摘录与总结
- **作者：happybob**：赛时因未特判 $\div \, 0$ 导致 fst，排名大幅下降。总结是在解题时要注意边界条件的判断，避免因小错误导致严重后果。
- **作者：xzy090626**：赛时因犯错误未能场切题目。总结是在没有思路时，可以先寻找一种更可能正确或更容易实现的解法，对其进行延展思考，然后判断其正确性，同时要善于观察样例和 hints 来获取解法。 

---
处理用时：39.67秒