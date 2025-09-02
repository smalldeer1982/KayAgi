# 题目信息

# Orac and Medians

## 题目描述

Slime has a sequence of positive integers $ a_1, a_2, \ldots, a_n $ .

In one operation Orac can choose an arbitrary subsegment $ [l       \ldots r] $ of this sequence and replace all values $ a_l, a_{l       + 1}, \ldots, a_r $ to the value of median of $ \{a_l, a_{l +       1}, \ldots, a_r\} $ .

In this problem, for the integer multiset $ s $ , the median of $ s $ is equal to the $ \lfloor \frac{|s|+1}{2}\rfloor $ -th smallest number in it. For example, the median of $ \{1,4,4,6,5\} $ is $ 4 $ , and the median of $ \{1,7,5,8\} $ is $ 5 $ .

Slime wants Orac to make $ a_1 = a_2 = \ldots = a_n = k $ using these operations.

Orac thinks that it is impossible, and he does not want to waste his time, so he decided to ask you if it is possible to satisfy the Slime's requirement, he may ask you these questions several times.

## 说明/提示

In the first query, Orac can't turn all elements into $ 3 $ .

In the second query, $ a_1=6 $ is already satisfied.

In the third query, Orac can select the complete array and turn all elements into $ 2 $ .

In the fourth query, Orac can't turn all elements into $ 3 $ .

In the fifth query, Orac can select $ [1,6] $ at first and then select $ [2,10] $ .

## 样例 #1

### 输入

```
5
5 3
1 5 2 6 1
1 6
6
3 2
1 2 3
4 3
3 1 2 3
10 3
1 2 3 4 5 6 7 8 9 10```

### 输出

```
no
yes
yes
no
yes```

# AI分析结果

### 题目内容中文重写
史莱姆有一个正整数序列 $ a_1, a_2, \ldots, a_n $ 。

在一次操作中，奥拉奇可以选择这个序列的任意一个子段 $ [l \ldots r] $ ，并将所有的值 $ a_l, a_{l + 1}, \ldots, a_r $ 替换为集合 $ \{a_l, a_{l + 1}, \ldots, a_r\} $ 的中位数。

在这个问题中，对于整数多重集 $ s $ ，$ s $ 的中位数等于其中第 $ \lfloor \frac{|s|+1}{2}\rfloor $ 小的数。例如，$ \{1,4,4,6,5\} $ 的中位数是 $ 4 $ ，$ \{1,7,5,8\} $ 的中位数是 $ 5 $ 。

史莱姆希望奥拉奇使用这些操作使 $ a_1 = a_2 = \ldots = a_n = k $ 。

奥拉奇认为这是不可能的，并且他不想浪费时间，所以他决定问你是否有可能满足史莱姆的要求，他可能会多次问你这些问题。

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是围绕能否将序列中的所有数变为 $k$ 展开，关键在于判断序列中是否存在特定的数的组合，通过操作这些组合来达到目标。
- **思路对比**：大部分题解都先特判序列中没有 $k$ 或 $n = 1$ 的情况。对于有 $k$ 的情况，不同题解的判断条件有所不同，但本质都是寻找能构造出相邻 $k$ 或者能将序列中部分数变为大于等于 $k$ 的组合，如相邻两个大于等于 $k$ 的数，或者间隔一个数的两个大于等于 $k$ 的数。
- **算法要点**：主要是对序列进行遍历，检查是否存在满足条件的数的组合。部分题解会将数与 $k$ 的大小关系进行分类，简化判断过程。
- **解决难点**：难点在于找出能通过操作将序列变为全 $k$ 的充分必要条件。一些题解通过列举特殊情况，逐步推导得出结论。

### 所选题解
- **Meatherm（4星）**
    - **关键亮点**：思路清晰，通过三个结论逐步推导判断条件，并且给出了具体的操作示例，便于理解。
    - **个人心得**：无
- **KellyFrog（4星）**
    - **关键亮点**：简洁明了地阐述了判断条件，代码实现简单易懂。
    - **个人心得**：无
- **Link_Space（4星）**
    - **关键亮点**：详细解释了判断条件成立的原因，逻辑严谨。
    - **个人心得**：一开始往数据结构方面想，发现无法解决，后来换种思考方式才找到解题方法，提醒我们遇到问题要灵活转换思路。

### 重点代码
#### Meatherm 的代码
```cpp
int main(void){
    T=read();
    while(T--){
        n=read(),k=read();
        bool flag=false;        
        for(rr int i=1;i<=n;++i){
            a[i]=read();
            if(a[i]==k){
                flag=true;
            }            
        }
        if(!flag){ // 数列中没有 k
            puts("No");
            goto End;
        }        
        if(n==1&&a[1]==k){ // n = 1
            puts("Yes");
            goto End;
        }

        for(rr int i=2;i<n;++i){
            if(a[i-1]>=k&&a[i+1]>=k){ // 情况 2
                puts("Yes");
                goto End;
            }
        }

        for(rr int i=2;i<=n;++i){
            if(a[i]>=k&&a[i-1]>=k){// 情况 1
                puts("Yes");
                goto End;
            }
        }
        puts("No");
        End:;
    }
    return 0;
}
```
**核心实现思想**：先读取输入，判断序列中是否有 $k$ 以及 $n$ 是否为 1 。然后遍历序列，检查是否存在相邻两个大于等于 $k$ 的数或者间隔一个数的两个大于等于 $k$ 的数，若存在则输出 `Yes` ，否则输出 `No` 。

#### KellyFrog 的代码
```cpp
void Solve() {
    cin >> n >> k;
    bool hasK = false;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        if(a[i] == k) {
            hasK = true;
        }
    }
    if(!hasK) {
        cout << "no" << endl;
        return;
    }
    if(n == 1) {
        cout << "yes" << endl;
        return;
    }
    for(int i = 1; i < n; i++) {
        if(a[i] >= k && a[i + 1] >= k) {
            cout << "yes" << endl;
            return;
        }
    }
    for(int i = 1; i < n - 1; i++) {
        if(a[i] >= k && a[i + 2] >= k) {
            cout << "yes" << endl;
            return;
        }
    }
    cout << "no" << endl;
}
```
**核心实现思想**：读取输入，判断是否有 $k$ 和 $n$ 是否为 1 。然后遍历序列，检查相邻两个大于等于 $k$ 的数或者间隔一个数的两个大于等于 $k$ 的数，若存在则输出 `yes` ，否则输出 `no` 。

#### Link_Space 的代码
```cpp
int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        int n, k;
        scanf("%d%d", &n, &k);
        bool flag = false;
        bool already = false;
        for (int i = 1; i <= n;i++)
        {
            scanf("%d",&a[i]);
            if(a[i]==k)
                flag = true;
        }
        if(!flag)
        {
            puts("no");
            continue;
        }
        if(n==1)
        {
            puts("yes");
            continue;
        }
        for (int i = 1; i < n;i++)
        {
            if(a[i]>=k&&a[i+1]>=k)
            {
                puts("yes");
                already = true;
                break;
            }
        }
        if(already)
            continue;
        for (int i = 1; i < n - 1;i++)
        {
            if(a[i]>=k&&a[i+2]>=k)
            {
                puts("yes");
                already = true;
                break;
            }
        }
        if(already)
            continue;
        puts("no");
    }
    return 0;
}
```
**核心实现思想**：读取输入，判断是否有 $k$ 和 $n$ 是否为 1 。然后遍历序列，检查相邻两个大于等于 $k$ 的数或者间隔一个数的两个大于等于 $k$ 的数，若存在则输出 `yes` ，否则输出 `no` 。

### 最优关键思路或技巧
- **分类讨论**：先特判序列中没有 $k$ 或 $n = 1$ 的情况，简化问题。
- **寻找关键组合**：通过分析操作的性质，找出能构造出相邻 $k$ 或者能将序列中部分数变为大于等于 $k$ 的数的组合，如相邻两个大于等于 $k$ 的数，或者间隔一个数的两个大于等于 $k$ 的数。

### 可拓展之处
同类型题可能会改变操作的规则，或者改变目标状态，解题的关键仍然是分析操作的性质，找出能达到目标状态的关键条件。类似的算法套路包括通过列举特殊情况，逐步推导得出一般结论，以及对数据进行分类简化判断过程。

### 推荐题目
- [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)
- [P1012 拼数](https://www.luogu.com.cn/problem/P1012)
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)

### 个人心得总结
Link_Space 提到一开始往数据结构方面想，发现无法解决，后来换种思考方式才找到解题方法，这提醒我们遇到问题要灵活转换思路，不要局限于一种方法。

---
处理用时：55.62秒