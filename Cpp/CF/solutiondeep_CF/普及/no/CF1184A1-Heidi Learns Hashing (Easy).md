# 题目信息

# Heidi Learns Hashing (Easy)

## 题目描述

Melody Pond was stolen from her parents as a newborn baby by Madame Kovarian, to become a weapon of the Silence in their crusade against the Doctor. Madame Kovarian changed Melody's name to River Song, giving her a new identity that allowed her to kill the Eleventh Doctor.

Heidi figured out that Madame Kovarian uses a very complicated hashing function in order to change the names of the babies she steals. In order to prevent this from happening to future Doctors, Heidi decided to prepare herself by learning some basic hashing techniques.

The first hashing function she designed is as follows.

Given two positive integers $ (x, y) $ she defines $ H(x,y):=x^2+2xy+x+1 $ .

Now, Heidi wonders if the function is reversible. That is, given a positive integer $ r $ , can you find a pair $ (x, y) $ (of positive integers) such that $ H(x, y) = r $ ?

If multiple such pairs exist, output the one with smallest possible $ x $ . If there is no such pair, output "NO".

## 样例 #1

### 输入

```
19
```

### 输出

```
1 8
```

## 样例 #2

### 输入

```
16
```

### 输出

```
NO
```

# AI分析结果

【题目内容】
# Heidi Learns Hashing (Easy)

## 题目描述

Melody Pond 在她还是新生儿时被 Madame Kovarian 从父母身边偷走，成为 Silence 组织对抗 Doctor 的武器。Madame Kovarian 将 Melody 的名字改为 River Song，赋予她新的身份，使她能够杀死第十一任 Doctor。

Heidi 发现 Madame Kovarian 使用了一种非常复杂的哈希函数来改变她偷走的婴儿的名字。为了防止未来的 Doctor 遭受同样的命运，Heidi 决定通过学习一些基本的哈希技术来做好准备。

她设计的第一个哈希函数如下。

给定两个正整数 $ (x, y) $，她定义 $ H(x,y):=x^2+2xy+x+1 $。

现在，Heidi 想知道这个函数是否可逆。也就是说，给定一个正整数 $ r $，你能找到一对正整数 $ (x, y) $ 使得 $ H(x, y) = r $ 吗？

如果存在多个这样的对，输出 $ x $ 最小的那个。如果没有这样的对，输出 "NO"。

## 样例 #1

### 输入

```
19
```

### 输出

```
1 8
```

## 样例 #2

### 输入

```
16
```

### 输出

```
NO
```

【算法分类】
数学

【题解分析与结论】
本题的核心是求解方程 $x^2 + 2xy + x + 1 = r$ 的正整数解，且要求 $x$ 最小。题解主要集中在通过数学推导和枚举来解决问题。

1. **数学推导**：大多数题解通过将 $x$ 设为 1，简化方程并求解 $y$，然后判断 $r$ 的奇偶性和大小，从而判断是否有解。
2. **枚举法**：部分题解通过枚举 $x$ 的值，检查是否存在满足条件的 $y$，这种方法虽然简单，但在 $r$ 较大时效率较低。

【评分较高的题解】

1. **作者：xuchuhan (赞：2)**
   - **星级**：4
   - **关键亮点**：通过数学推导判断无解情况，并直接输出 $x=1$ 时的解，代码简洁高效。
   - **代码**：
     ```cpp
     #include<bits/stdc++.h>
     #define int long long
     using namespace std;
     int r;
     signed main(){
         cin>>r;
         if(r<5||r%2==0)
             cout<<"NO";
         else
             cout<<1<<" "<<(r-3)/2;
         return 0;
     }
     ```

2. **作者：Mercury_C (赞：2)**
   - **星级**：4
   - **关键亮点**：详细解释了为什么 $x$ 取 1 时是最优解，并给出了无解条件的推导，代码清晰易读。
   - **代码**：
     ```cpp
     #include<bits/stdc++.h>
     using namespace std;
     long long r;
     int main()
     {
         while(cin>>r)
         {
             if(r%2==0||r<=3)
                 cout<<"NO"<<endl;
             else
             cout<<1<<" "<<(r-3)/2<<endl;
         }
         return 0;
     }
     ```

3. **作者：InversionShadow (赞：1)**
   - **星级**：4
   - **关键亮点**：通过观察直接得出 $x=1$ 时的解，并判断无解情况，代码简洁明了。
   - **代码**：
     ```cpp
     #include <bits/stdc++.h>
     #define int long long
     using namespace std;
     int x;
     signed main() {
       cin >> x;
       if ((x - 3) % 2 == 0 && x >= 4) {
         cout << "1 " << (x - 3) / 2 << endl;
         return 0;
       }
       cout << "NO\n";
       return 0;
     }
     ```

【最优关键思路或技巧】
1. **数学推导**：通过将 $x$ 设为 1，简化方程并求解 $y$，可以快速判断是否有解。
2. **无解条件**：通过判断 $r$ 的奇偶性和大小，可以快速排除无解情况。

【可拓展之处】
类似的问题可以通过数学推导简化方程，减少枚举的次数，提高算法效率。例如，求解其他形式的二次方程或更高次的方程时，也可以尝试通过数学推导来简化问题。

【推荐题目】
1. [P1008 三连击](https://www.luogu.com.cn/problem/P1008)
2. [P1022 计算器的改良](https://www.luogu.com.cn/problem/P1022)
3. [P1045 麦森数](https://www.luogu.com.cn/problem/P1045)

---
处理用时：34.23秒