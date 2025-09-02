# 题目信息

# Split a Number

## 题目描述

Dima worked all day and wrote down on a long paper strip his favorite number $ n $ consisting of $ l $ digits. Unfortunately, the strip turned out to be so long that it didn't fit in the Dima's bookshelf.

To solve the issue, Dima decided to split the strip into two non-empty parts so that each of them contains a positive integer without leading zeros. After that he will compute the sum of the two integers and write it down on a new strip.

Dima wants the resulting integer to be as small as possible, because it increases the chances that the sum will fit it in the bookshelf. Help Dima decide what is the minimum sum he can obtain.

## 说明/提示

In the first example Dima can split the number $ 1234567 $ into integers $ 1234 $ and $ 567 $ . Their sum is $ 1801 $ .

In the second example Dima can split the number $ 101 $ into integers $ 10 $ and $ 1 $ . Their sum is $ 11 $ . Note that it is impossible to split the strip into "1" and "01" since the numbers can't start with zeros.

## 样例 #1

### 输入

```
7
1234567
```

### 输出

```
1801
```

## 样例 #2

### 输入

```
3
101
```

### 输出

```
11
```

# AI分析结果

### 题目内容重写
# 分割数字

## 题目描述

Dima 工作了一整天，并在一条长纸条上写下了他最喜欢的数字 $n$，该数字由 $l$ 位数字组成。不幸的是，纸条太长了，无法放入 Dima 的书架。

为了解决这个问题，Dima 决定将纸条分成两个非空的部分，使得每一部分都包含一个没有前导零的正整数。之后，他将计算这两个整数的和，并将其写在一张新的纸条上。

Dima 希望最终得到的整数尽可能小，因为这样可以增加它放入书架的机会。请帮助 Dima 决定他能得到的最小和是多少。

## 说明/提示

在第一个例子中，Dima 可以将数字 $1234567$ 分割成整数 $1234$ 和 $567$。它们的和是 $1801$。

在第二个例子中，Dima 可以将数字 $101$ 分割成整数 $10$ 和 $1$。它们的和是 $11$。注意，不能将纸条分割成 "1" 和 "01"，因为数字不能以零开头。

## 样例 #1

### 输入

```
7
1234567
```

### 输出

```
1801
```

## 样例 #2

### 输入

```
3
101
```

### 输出

```
11
```

### 算法分类
贪心、高精度

### 题解分析与结论
本题的核心在于如何将一个长数字分割成两个部分，使得它们的和最小。由于数字的长度可能非常大（$10^5$），直接暴力枚举所有可能的分割点会导致时间复杂度过高。因此，大多数题解都采用了贪心的策略，即从中间位置开始分割，并处理前导零的问题。

#### 关键思路：
1. **贪心策略**：为了使两个数的和最小，应该尽量使它们的位数相近。因此，从中间位置开始分割是最优的选择。
2. **前导零处理**：如果中间位置的分割点有前导零，则需要向左或向右移动分割点，直到找到一个没有前导零的位置。
3. **高精度加法**：由于数字可能非常大，需要使用高精度加法来计算两个数的和。

#### 题解对比：
- **RE_Prince** 的题解使用了 Python，通过从中间位置开始分割，并处理前导零，最终计算最小和。代码简洁，思路清晰。
- **封禁用户** 的题解使用了 C++，同样从中间位置开始分割，并处理前导零，最终通过高精度加法计算最小和。代码结构清晰，优化程度较高。
- **Macesuted** 的题解使用了 C++，通过双端队列模拟高精度加法，从中间位置开始分割，并处理前导零。代码实现较为复杂，但思路清晰。

### 评分较高的题解
1. **RE_Prince**（4星）
   - 关键亮点：使用 Python 实现，代码简洁，思路清晰，处理前导零的方法简单有效。
   - 核心代码：
     ```python
     m=int(input())
     n=input()
     j=(m+1)//2 #左右端点
     i=j-1
     while i>0 and n[i]=='0':# 前导0
         i-=1
     while j<m and n[j]=='0':
         j+=1
     l=0
     r=0
     ans=int(n) #取最小
     if i>0:
         ans=min(int(n[:i])+int(n[i:]),ans)
     if j<m:
         ans=min(int(n[:j])+int(n[j:]),ans)
     print(ans)
     ```

2. **封禁用户**（4星）
   - 关键亮点：使用 C++ 实现，代码结构清晰，优化程度较高，处理前导零的方法简单有效。
   - 核心代码：
     ```cpp
     int main(){
         int n;
         cin >> n;
         string str;
         cin >> str;
         int x = (n + 1) / 2, y = n / 2;
         string ansX = str, ansY = str;
         while (x < str.length() && str[x] == '0') ++x;
         if (x < str.length()) ansX = getSplitSum(str, x);
         while (y >= 0 && str[y] == '0') --y;
         if (y >= 0) ansY = getSplitSum(str, y);
         cout << getMinStr(ansX, ansY) << endl;
         return 0;
     }
     ```

3. **Macesuted**（4星）
   - 关键亮点：使用 C++ 实现，通过双端队列模拟高精度加法，代码实现较为复杂，但思路清晰。
   - 核心代码：
     ```cpp
     int main(){
         int l;
         cin>>l;
         for (R int point=1;point<=l;point++){
             char t;
             cin>>t;
             if(point<=l/2){
                 a.push_back(t-'0');
                 c.push_back(t-'0');
             }else{
                 b.push_back(t-'0');
                 d.push_back(t-'0');
             }
         }
         a.push_back(b.front());
         b.pop_front();
         a.push_back(b.front());
         b.pop_front();
         d.push_front(c.back());
         c.pop_back();
         //向左搜索
         while(!a.empty()){
             b.push_front(a.back());
             a.pop_back();
             if(a.empty()||b.empty()||a.front()==0||b.front()==0){
                 continue;
             }
             deque<int>::reverse_iterator pa=a.rbegin(),pb=b.rbegin();
             int g=0;
             for(;pa!=a.rend()&&pb!=b.rend();++pa,++pb){
                 s.push_front((*pa+*pb+g)%10);
                 g=(*pa+*pb+g)/10;
             }
             while(pa!=a.rend()){
                 s.push_front((*pa+g)%10);
                 g=(*pa+g)/10;
                 pa++;
             }
             while(pb!=b.rend()){
                 s.push_front((*pb+g)%10);
                 g=(*pb+g)/10;
                 pb++;
             }
             if(g!=0){
                 s.push_front(g);
             }
             break;
         }
         //向右搜索
         while(!d.empty()){
             c.push_back(d.front());
             d.pop_front();
             if(c.empty()||d.empty()||c.front()==0||d.front()==0){
                 continue;
             }
             deque<int>::reverse_iterator pc=c.rbegin(),pd=d.rbegin();
             int g=0;
             for(;pc!=c.rend()&&pd!=d.rend();++pc,++pd){
                 n.push_front((*pc+*pd+g)%10);
                 g=(*pc+*pd+g)/10;
             }
             while(pc!=c.rend()){
                 n.push_front((*pc+g)%10);
                 g=(*pc+g)/10;
                 pc++;
             }
             while(pd!=d.rend()){
                 n.push_front((*pd+g)%10);
                 g=(*pd+g)/10;
                 pd++;
             }
             if(g!=0){
                 n.push_front(g);
             }
             break;
         }
         //判断s与n的大小，取小者输出
         if(s.size()==0) {
             cout<<n<<std::endl;
             return 0;
         }
         if(n.size()==0){
             cout<<s<<std::endl;
             return 0;
         }
         if(s.size()!=n.size()){
             if(s.size()<n.size()){
                 cout<<s<<std::endl;
             } else{
                 cout<<n<<std::endl;
             }
             return 0;
         }
         else{
             deque<int>::iterator ps=s.begin(),pn=n.begin();
             for(;ps!=s.end()&&pn!=n.end();ps++,pn++){
                 if(*pn!=*ps){
                     if(*ps<*pn){
                         cout<<s<<std::endl;
                     } else{
                         cout<<n<<std::endl;
                     }
                     return 0;
                 }
             }
         }
         cout<<n<<std::endl;
         return 0;
     }
     ```

### 最优关键思路与技巧
1. **贪心策略**：从中间位置开始分割，确保两个数的位数相近，从而使得它们的和最小。
2. **前导零处理**：通过向左或向右移动分割点，确保分割后的数没有前导零。
3. **高精度加法**：使用高精度加法处理大数运算，确保计算的准确性。

### 可拓展之处
- 类似的问题可以扩展到多个分割点，或者分割成多个部分，使得它们的和最小。
- 类似算法可以应用于其他需要处理大数运算的场景，如大数乘法、大数除法等。

### 推荐题目
1. [P1009 阶乘之和](https://www.luogu.com.cn/problem/P1009)
2. [P1045 高精度乘法](https://www.luogu.com.cn/problem/P1045)
3. [P1255 数楼梯](https://www.luogu.com.cn/problem/P1255)

### 个人心得摘录
- **RE_Prince**：通过从中间位置开始分割，并处理前导零，最终计算最小和。代码简洁，思路清晰。
- **封禁用户**：从中间位置开始分割，并处理前导零，最终通过高精度加法计算最小和。代码结构清晰，优化程度较高。
- **Macesuted**：通过双端队列模拟高精度加法，从中间位置开始分割，并处理前导零。代码实现较为复杂，但思路清晰。

---
处理用时：67.81秒