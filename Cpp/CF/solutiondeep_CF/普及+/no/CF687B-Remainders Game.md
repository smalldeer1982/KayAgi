# 题目信息

# Remainders Game

## 题目描述

Today Pari and Arya are playing a game called Remainders.

Pari chooses two positive integer $ x $ and $ k $ , and tells Arya $ k $ but not $ x $ . Arya have to find the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF687B/74cc0e497602c391113efb814a12e06ebc180bd8.png). There are $ n $ ancient numbers $ c_{1},c_{2},...,c_{n} $ and Pari has to tell Arya ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF687B/d6826eab3568be14654e0e163000c670f1c64e14.png) if Arya wants. Given $ k $ and the ancient values, tell us if Arya has a winning strategy independent of value of $ x $ or not. Formally, is it true that Arya can understand the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF687B/74cc0e497602c391113efb814a12e06ebc180bd8.png) for any positive integer $ x $ ?

Note, that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF687B/cb1d84ad58154eb7ea26b65d1ae0039570db9bb6.png) means the remainder of $ x $ after dividing it by $ y $ .

## 说明/提示

In the first sample, Arya can understand ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF687B/b93dce9b9ef400fa12cce1ab52784e3449739731.png) because $ 5 $ is one of the ancient numbers.

In the second sample, Arya can't be sure what ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF687B/34daaca50b46751e5d9e1271dc07f186fd9fd248.png) is. For example $ 1 $ and $ 7 $ have the same remainders after dividing by $ 2 $ and $ 3 $ , but they differ in remainders after dividing by $ 7 $ .

## 样例 #1

### 输入

```
4 5
2 3 5 12
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
2 7
2 3
```

### 输出

```
No
```

# AI分析结果

### 题目重写
# Remainders Game
## 题目描述
今天Pari和Arya正在玩一个叫做Remainders的游戏。
Pari选择两个正整数$x$和$k$，并将$k$告诉Arya，但不告诉$x$。Arya必须找出$x \bmod k$的值。有$n$个古老数字$c_{1},c_{2},\cdots,c_{n}$，如果Arya想知道，Pari必须告诉Arya $x \bmod c_{i}$的值。给定$k$和这些古老数字，判断Arya是否有一个与$x$的值无关的获胜策略。形式上，对于任意正整数$x$，Arya是否都能知道$x \bmod k$的值？
注意，$a \bmod b$表示$a$除以$b$后的余数。
## 说明/提示
在第一个样例中，Arya可以知道$x \bmod 5$的值，因为5是其中一个古老数字。
在第二个样例中，Arya不能确定$x \bmod 7$的值。例如，1和7除以2和3后的余数相同，但它们除以7后的余数不同。
## 样例 #1
### 输入
```
4 5
2 3 5 12
```
### 输出
```
Yes
```
## 样例 #2
### 输入
```
2 7
2 3
```
### 输出
```
No
```

### 算法分类
数学

### 题解综合分析与结论
这些题解的核心思路均基于扩展中国剩余定理（exCRT）。题目本质是判断通过已知的$x \bmod c_i$能否唯一确定$x \bmod k$。各题解均指出关键在于判断$k$是否整除所有$c_i$的最小公倍数$\text{lcm}(c_1,c_2,\cdots,c_n)$ 。
 - **思路方面**：都围绕exCRT，将多个同余方程转化为一个在模$\text{lcm}(c_1,c_2,\cdots,c_n)$下的同余方程，进而判断$k$与$\text{lcm}(c_1,c_2,\cdots,c_n)$的整除关系。
 - **算法要点**：需掌握exCRT的基本原理，会计算多个数的最小公倍数，部分题解还涉及质因数分解。
 - **解决难点**：计算$\text{lcm}(c_1,c_2,\cdots,c_n)$可能导致数据溢出，部分题解通过提前取模或质因数分解的方式避免溢出。

### 所选的题解
- **作者：Audrey_Hall (5星)**
  - **关键亮点**：对核心结论给出简单证明，解释详细，代码采用快读快写优化输入输出，且给出避免$\text{lcm}$计算溢出的两种方式并在代码中采用提前取模方式。
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline void read(int &n){
    n=0;int f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')n=(n<<1)+(n<<3)+(ch^48),ch=getchar();
    n*=f;
}
//快读(int)
inline void read_(ll &n){
    n=0;int f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')n=(n<<1)+(n<<3)+(ch^48),ch=getchar();
    n*=f;
}
//快读(long long) 
inline void print(int n){
    if(n<0)putchar('-'),n=-n;
    if(n>9)print(n/10);
    putchar(n%10+'0');
}
//快写(int)
inline void print_(ll n){
    if(n<0)putchar('-'),n=-n;
    if(n>9)print_(n/10);
    putchar(n%10+'0');
}
//快写(long long) 
inline void check1(){puts("完成啦！");}
inline void check2(){puts("竟然已经运行到这里了吗？");}
inline void check3(){puts("我已经完全爱上Warma啦！");}
//调试程序 
int n,k,c;ll lcm=1;
inline int gcd(int a,int b){return!b?a:gcd(b,a%b);}
//求gcd
int main(){
    read(n),read(k);
//  读入 
    for(int i=1;i<=n;i++)read(c),(lcm=lcm/gcd(lcm,c)*c)%=k;
//  读入+lcm计算(注意先除后乘)+取模 
    if(lcm%k)puts("No");else puts("Yes");
//  取模+判断 
    return 0;
}
```
  - **核心代码片段**：上述整个`main`函数，通过循环读入$c_i$，在计算$\text{lcm}$过程中不断对$k$取模，最后判断取模结果是否为0来输出答案。
- **作者：Grow2011 (4星)**
  - **关键亮点**：简洁明了地阐述题意和解题思路，代码实现清晰，采用快读，定义了求最大公因数和最小公倍数的函数。
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,c,p = 1;
inline int read(){
    register char c = getchar();
    register int f = 1,x = 0;
    while(c<'0'||c>'9'){
        if(c=='-')f = -1;
        c = getchar();
    }
    while(c>='0'&&c<='9')x = (x<<3)+(x<<1)+c-'0',c = getchar();
    return x*f;
}//快读 
int gcd(int a,int b){return a%b==0?b:gcd(b,a%b);}//最大公因数 
int lcm(int a,int b){return a*b/gcd(a,b);}//最小公倍数 
signed main(){
    cin >> n >> k;
    for(int i = 1;i<=n;i++){
        c = read();
        p = (lcm(p,c))%k;//记得取模 
    }
    if(p%k==0)cout << "Yes";
    else cout << "No";
    return 0;
}
```
  - **核心代码片段**：`main`函数中循环读入$c_i$，计算$p$（即所有$c_i$的$\text{lcm}$对$k$取模结果），根据$p$对$k$取模是否为0输出答案。
- **作者：andyli (4星)**
  - **关键亮点**：简洁猜出答案条件为$k|\text{lcm}\{c_i\}$，并采用质因数分解的方式避免$\text{lcm}$计算溢出，代码简短高效。
  - **重点代码**：
```cpp
const int maxn = 1000005;

int C[maxn];
int main()
{
    int n, k;
    io.read(n, k);
    for (int i = 1; i <= n; i++)
        io.read(C[i]);
    int m = sqrt(k);
    for (int i = 2; i <= m; i++) {
        if (k % i == 0) {
            int t = 1;
            while (k % i == 0)
                t *= i, k /= i;
            bool flag = false;
            for (int i = 1; i <= n &&!flag; i++)
                if (C[i] % t == 0)
                    flag = true;
            if (!flag) {
                writeln("No");
                return 0;
            }
        }
    }
    bool flag = false;
    for (int i = 1; i <= n &&!flag; i++)
        if (C[i] % k == 0)
            flag = true;
    writeln(flag? "Yes" : "No");
    return 0;
}
```
  - **核心代码片段**：外层循环对$k$进行质因数分解，内层循环判断分解后的因子是否能整除某个$C[i]$，最后根据判断结果输出答案。

### 最优关键思路或技巧
- **避免溢出技巧**：在计算$\text{lcm}(c_1,c_2,\cdots,c_n)$时，通过提前对$k$取模（如Audrey_Hall和Grow2011的题解），或者对$k$进行质因数分解并判断每个质因数幂次是否能被某个$c_i$整除（如andyli的题解），有效避免了因数据过大导致的溢出问题。

### 可拓展之处
同类型题通常围绕同余方程、中国剩余定理及其扩展展开。类似算法套路是遇到多个同余方程求解或判断解的唯一性问题时，考虑通过最小公倍数等方式转化为一个同余方程，再根据题目要求判断相关条件。

### 洛谷推荐题目
- [P1495 【模板】中国剩余定理(CRT)/曹冲养猪](https://www.luogu.com.cn/problem/P1495)：经典的中国剩余定理模板题，帮助理解中国剩余定理的基本应用。
- [P4777 【模板】扩展中国剩余定理（EXCRT）](https://www.luogu.com.cn/problem/P4777)：专门考察扩展中国剩余定理的应用，加深对exCRT的理解。
- [P3868 [TJOI2009]猜数字](https://www.luogu.com.cn/problem/P3868)：同样是基于同余方程的问题，需要运用中国剩余定理相关知识来求解。

### 个人心得摘录与总结
Audrey_Hall提到在解决本题时发现自己对中国剩余定理相关内容遗忘，通过翻找笔记回忆起来并应用到解题中。这提醒我们要对基础算法和定理熟练掌握并时常回顾，在遇到相关题目时才能迅速反应并运用。 

---
处理用时：85.17秒