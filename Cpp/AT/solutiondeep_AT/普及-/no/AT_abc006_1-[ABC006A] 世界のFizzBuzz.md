# 题目信息

# [ABC006A] 世界のFizzBuzz

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc006/tasks/abc006_1

 数字 $ N $ が与えられます。 $ N $ に $ 3 $ が含まれる、もしくは $ 3 $ で割り切れる場合は`YES`、それ以外は `NO` と出力してください。

 入力は以下の形式で標準入力から与えられる。 > $ N $

 整数 $ N(1≦N≦9) $ が $ 1 $ 行で与えられる。  $ N $ に $ 3 $ が含まれる、もしくは $ 3 $ で割り切れる場合は`YES`、それ以外は `NO` と出力してください。

  また、出力の末尾には改行を入れること。  ```
<pre class="prettyprint linenums">
2
```

 ```
<pre class="prettyprint linenums">
NO
```

- $ 2 $ は $ 3 $ で割り切ることができません。また $ 3 $ が含まれている数字でもありません。
 
```
<pre class="prettyprint linenums">
9
```

 ```
<pre class="prettyprint linenums">
YES
```

- $ 9 $ は $ 3 $ で割り切ることができます。
 
```
<pre class="prettyprint linenums">
3
```

 ```
<pre class="prettyprint linenums">
YES
```

- $ 3 $ は $ 3 $ で割り切ることができます。

# AI分析结果

### 题目内容重写
【题目描述】
给定一个数字 $N$。如果 $N$ 包含数字 $3$，或者 $N$ 能被 $3$ 整除，则输出 `YES`，否则输出 `NO`。

输入格式：
整数 $N(1 \leq N \leq 9)$ 在一行中给出。

输出格式：
如果 $N$ 包含数字 $3$，或者 $N$ 能被 $3$ 整除，则输出 `YES`，否则输出 `NO`。输出末尾需要换行。

示例：
```
输入：
2
输出：
NO
```

```
输入：
9
输出：
YES
```

```
输入：
3
输出：
YES
```

### 算法分类
模拟

### 题解分析与结论
该题的核心逻辑是通过模拟来判断一个数是否包含数字3或是否能被3整除。所有题解都采用了类似的思路，即先判断是否能被3整除，如果不能，则逐位检查是否包含数字3。代码实现上，大多数题解使用了循环或递归来逐位检查数字。

### 所选高分题解
1. **作者：梦游的小雪球 (4星)**
   - **关键亮点**：代码结构清晰，使用了循环逐位检查数字3，并在找到后立即返回，避免了不必要的计算。
   - **个人心得**：强调了输出格式的重要性，特别是换行符的使用。

   ```cpp
   #include<iostream>
   using namespace std;
   int main(){
       int a;
       cin>>a;
       if(a%3==0){
           cout<<"YES"<<endl;
           return 0;
       }
       for(int i=0;i<a;i++){
           if(a%10==3){
               cout<<"YES"<<endl;
               return 0;
           }
           a=a/10;
       }
       cout<<"NO"<<endl;
       return 0;
   }
   ```

2. **作者：有限光阴 (4星)**
   - **关键亮点**：使用了while循环逐位检查数字3，代码简洁明了。
   - **个人心得**：强调了代码的简洁性和效率。

   ```cpp
   #include<bits/stdc++.h>
   using namespace std;
   int main(){
       int a,b;
       cin>>a;
       if(a%3==0){
           cout<<"YES"<<endl;
           return 0;
       }
       while(a>0){
           b=a%10;
           a/=10;
           if(b==3){
               cout<<"YES"<<endl;
               return 0;
           }
       }
       cout<<"NO"<<endl;
       return 0;
   }
   ```

3. **作者：zfn07 (4星)**
   - **关键亮点**：将逐位检查封装成一个函数，提高了代码的可读性和复用性。
   - **个人心得**：强调了代码的模块化设计。

   ```cpp
   #include<bits/stdc++.h>
   using namespace std;
   bool check(int x){
       while(x){
           if(x%10==3)
               return 1;
           else x/=10;
       }
       return 0;
   }
   int main(){
       int a;
       cin>>a;
       if(a%3==0||check(a)){
           cout<<"YES"<<endl;
           return 0;
       }
       cout<<"NO"<<endl;
       return 0;
   }
   ```

### 最优关键思路
1. **先判断是否能被3整除**：这是最直接的条件，如果满足则立即输出`YES`。
2. **逐位检查数字3**：如果不能被3整除，则逐位检查数字是否包含3，一旦找到立即输出`YES`。
3. **模块化设计**：将逐位检查封装成函数，提高代码的可读性和复用性。

### 可拓展之处
该题的思路可以拓展到其他类似的数字判断问题，例如判断一个数是否包含某个特定数字，或者是否能被某个特定数整除。类似的问题可以通过类似的模拟方法解决。

### 推荐题目
1. [P1008 三连击](https://www.luogu.com.cn/problem/P1008)
2. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)
3. [P1013 进制位](https://www.luogu.com.cn/problem/P1013)

---
处理用时：26.56秒