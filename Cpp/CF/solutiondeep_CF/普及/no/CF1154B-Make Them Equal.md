# 题目信息

# Make Them Equal

## 题目描述

You are given a sequence $ a_1, a_2, \dots, a_n $ consisting of $ n $ integers.

You can choose any non-negative integer $ D $ (i.e. $ D \ge 0 $ ), and for each $ a_i $ you can:

- add $ D $ (only once), i. e. perform $ a_i := a_i + D $ , or
- subtract $ D $ (only once), i. e. perform $ a_i := a_i - D $ , or
- leave the value of $ a_i $ unchanged.

It is possible that after an operation the value $ a_i $ becomes negative.

Your goal is to choose such minimum non-negative integer $ D $ and perform changes in such a way, that all $ a_i $ are equal (i.e. $ a_1=a_2=\dots=a_n $ ).

Print the required $ D $ or, if it is impossible to choose such value $ D $ , print -1.

For example, for array $ [2, 8] $ the value $ D=3 $ is minimum possible because you can obtain the array $ [5, 5] $ if you will add $ D $ to $ 2 $ and subtract $ D $ from $ 8 $ . And for array $ [1, 4, 7, 7] $ the value $ D=3 $ is also minimum possible. You can add it to $ 1 $ and subtract it from $ 7 $ and obtain the array $ [4, 4, 4, 4] $ .

## 样例 #1

### 输入

```
6
1 4 4 7 4 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5
2 2 5 2 5
```

### 输出

```
3
```

## 样例 #3

### 输入

```
4
1 3 3 7
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
2
2 8
```

### 输出

```
3
```

# AI分析结果

【题目内容】
# Make Them Equal

## 题目描述

给定一个序列 $ a_1, a_2, \dots, a_n $，包含 $ n $ 个整数。

你可以选择任意一个非负整数 $ D $（即 $ D \ge 0 $），并对每个 $ a_i $ 进行以下操作之一：

- 加上 $ D $（仅一次），即执行 $ a_i := a_i + D $，或
- 减去 $ D $（仅一次），即执行 $ a_i := a_i - D $，或
- 保持 $ a_i $ 的值不变。

操作后，$ a_i $ 的值可能变为负数。

你的目标是选择一个最小的非负整数 $ D $，并通过上述操作使得所有 $ a_i $ 相等（即 $ a_1=a_2=\dots=a_n $）。

输出所需的 $ D $，如果无法选择这样的 $ D $，则输出 -1。

例如，对于数组 $ [2, 8] $，$ D=3 $ 是最小可能的值，因为你可以将 $ 2 $ 加上 $ D $，将 $ 8 $ 减去 $ D $，得到数组 $ [5, 5] $。对于数组 $ [1, 4, 7, 7] $，$ D=3 $ 也是最小可能的值，你可以将 $ 1 $ 加上 $ D $，将 $ 7 $ 减去 $ D $，得到数组 $ [4, 4, 4, 4] $。

## 样例 #1

### 输入

```
6
1 4 4 7 4 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5
2 2 5 2 5
```

### 输出

```
3
```

## 样例 #3

### 输入

```
4
1 3 3 7
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
2
2 8
```

### 输出

```
3
```

【算法分类】
数学

【题解分析与结论】
本题的核心是通过选择一个最小的非负整数 $ D $，使得序列中的所有元素通过加、减或不变操作后相等。大多数题解采用了分类讨论的思路，根据序列中不同元素的个数来决定 $ D $ 的取值。具体来说：

1. 如果序列中不同元素的个数超过 3 个，则直接输出 -1，因为无法通过一个 $ D $ 使得所有元素相等。
2. 如果序列中只有一个元素，则输出 0。
3. 如果序列中有两个元素，则根据它们的差值是否为偶数来决定 $ D $ 的取值。
4. 如果序列中有三个元素，则需要判断这三个元素是否构成等差数列，如果是，则输出公差 $ D $，否则输出 -1。

【评分较高的题解】

1. **作者：Nuclear_Fish_cyq (赞：1)**  
   **星级：4**  
   **关键亮点：**  
   - 通过去重和分类讨论，简化了问题。
   - 代码简洁，逻辑清晰，易于理解。
   - 使用了 STL 的 `set` 来去重，提高了代码的可读性。

   **核心代码：**
   ```cpp
   sort(a, a + n);
   n = unique(a, a + n) - a; // STL去重
   if(n > 3){
       cout << -1 << endl;
   }
   else if(n == 3){
       if(a[0] + a[2] == a[1] * 2){
           cout << a[1] - a[0] << endl;
       }
       else{
           cout << -1 << endl;
       }
   }
   else if(n == 2){
       if((a[1] - a[0]) % 2){
           cout << a[1] - a[0] << endl;
       }
       else{
           cout << (a[1] - a[0]) / 2 << endl;
       }
   }
   else{
       cout << 0 << endl;
   }
   ```

2. **作者：Harrylzh (赞：0)**  
   **星级：4**  
   **关键亮点：**  
   - 通过去重和分类讨论，清晰地解决了问题。
   - 代码结构清晰，逻辑严谨。
   - 使用了 `sort` 和 `unique` 来去重，简化了代码。

   **核心代码：**
   ```cpp
   sort(l+1,l+n+1);
   a[++t]=l[1];
   for(int i=2;i<=n;i++){
       if(l[i]!=l[i-1]){
           a[++t]=l[i];
       }
   }
   if(t==1) cout<<0<<endl;
   else if(t==2){
       if((a[2]-a[1])%2==0) cout<<(a[2]-a[1])/2<<endl;
       else cout<<(a[2]-a[1])<<endl;
   }
   else if(t==3){
       if(a[3]-a[2]==a[2]-a[1]) cout<<a[2]-a[1]<<endl;
       else cout<<-1<<endl;
   }
   else{
       cout<<-1<<endl;
   }
   ```

3. **作者：TheSky233 (赞：0)**  
   **星级：4**  
   **关键亮点：**  
   - 通过分类讨论，清晰地解决了问题。
   - 使用了 `set` 来去重，简化了代码。
   - 代码结构清晰，逻辑严谨。

   **核心代码：**
   ```cpp
   set<int> s;
   for(int i=1;i<=n;i++) cin>>a[i],s.insert(a[i]);
   if(s.size()>3) cout<<-1<<endl;
   if(s.size()==3){
       set<int>::iterator it=s.end(); it--; it--;
       if(*it-*s.begin()!=*s.rbegin()-*it) cout<<-1<<endl;
       else cout<<*it-*s.begin()<<endl;
   }
   if(s.size()==2){
       if((*s.rbegin()-*s.begin())&1) cout<<*s.rbegin()-*s.begin()<<endl;
       else cout<<((*s.rbegin()-*s.begin())>>1)<<endl;
   }
   if(s.size()==1){
       cout<<0<<endl;
   }
   ```

【最优关键思路或技巧】
1. **去重与分类讨论**：通过去重简化问题，并根据不同元素的个数进行分类讨论，决定 $ D $ 的取值。
2. **使用 STL 容器**：如 `set` 和 `unique`，简化去重操作，提高代码可读性。
3. **等差数列判断**：对于三个元素的情况，判断它们是否构成等差数列，决定 $ D $ 的取值。

【可拓展之处】
1. 类似的问题可以通过去重和分类讨论的思路来解决，尤其是在处理序列或数组问题时。
2. 可以使用更多的 STL 容器来简化代码，如 `map`、`priority_queue` 等。

【推荐题目】
1. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1045 麦森数](https://www.luogu.com.cn/problem/P1045)

---
处理用时：52.19秒