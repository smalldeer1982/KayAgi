# 题目信息

# Chilly Willy

## 题目描述

Chilly Willy loves playing with numbers. He only knows prime numbers that are digits yet. These numbers are $ 2 $ , $ 3 $ , $ 5 $ and $ 7 $ . But Willy grew rather bored of such numbers, so he came up with a few games that were connected with them.

Chilly Willy wants to find the minimum number of length $ n $ , such that it is simultaneously divisible by all numbers Willy already knows ( $ 2 $ , $ 3 $ , $ 5 $ and $ 7 $ ). Help him with that.

A number's length is the number of digits in its decimal representation without leading zeros.

## 样例 #1

### 输入

```
1
```

### 输出

```
-1
```

## 样例 #2

### 输入

```
5
```

### 输出

```
10080```

# AI分析结果

### 题目内容
# 怕冷的威利

## 题目描述
怕冷的威利喜欢玩数字游戏。他只认识一位数的质数，即2、3、5和7。但威利对这些数字感到相当厌倦，于是他想出了一些与之相关的游戏。

威利想找到长度为n的最小数字，该数字能同时被他已知的所有数字（2、3、5和7）整除。请帮他解决这个问题。

一个数字的长度是其十进制表示中不含前导零的数字个数。

## 样例 #1
### 输入
```
1
```
### 输出
```
-1
```

## 样例 #2
### 输入
```
5
```
### 输出
```
10080
```

### 算法分类
数学

### 题解综合分析与结论
这些题解主要围绕寻找能被2、3、5、7整除的n位数这一核心问题展开。由于暴力枚举因数据范围过大不可行，多数题解通过打表找规律的方式解题。规律为：n = 1或2时无解；n = 3时答案是210；n > 3时，前n - 3位由一个1和n - 4个0组成，后三位按{"050", "080", "170", "020", "200", "110"}六个一循环。部分题解尝试过暴力枚举思路，但因数据范围问题放弃。整体来看，各题解思路相近，主要差异在于规律的发现方式和代码实现细节。

### 所选的题解
- **作者：sanjingshou14 (5星)**
    - **关键亮点**：思路清晰，先指出暴力法不可行，通过运行暴力程序打表得出详细规律，代码实现简洁明了，对规律阐述详细。
    - **个人心得**：无
    - **重点代码核心思想**：根据n值分类讨论，n为1、2输出 - 1，n为3输出210，n大于3时，先输出1，再输出n - 4个0，最后根据(n - 3) % 6的结果输出对应的后三位。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s[6]={"110","050","080","170","020","200"};
int main(){
    int n;
    cin>>n;
    switch(n){
        case 1:case 2:cout<<-1;break;
        case 3:cout<<210;break;
        default:{
            cout<<1;
            for(int i=1;i<=n-4;i++){
                cout<<0;
            }
            int p=(n-3)%6;
            cout<<s[p];
            break;
        }
    } 
    return 0; 
}
```
- **作者：alex_liu (4星)**
    - **关键亮点**：先尝试常规思路用n位最小数取模210并调整，发现数据过大后通过打表找规律，规律分析清晰，代码逻辑明确。
    - **个人心得**：无
    - **重点代码核心思想**：同样对n值进行特判，n大于3时，先构造n位最小数，再通过取模和调整得到结果，最后根据规律直接输出。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t;
int main(){
    cin>>n;
    if(n==1||n==2)//特判 
        cout<<-1<<endl;
    else if(n==3)//特判 
        cout<<210<<endl;
    else{
        t=(n-3)%6;//减去1和后缀占得位置 
        cout<<1;
        for(int i=1;i<=n-4;i++)//根据位数输出0 
            cout<<0;
        if(t==1)cout<<"050";
        else if(t==2)cout<<"080";
        else if(t==3)cout<<"170";
        else if(t==4)cout<<"020";
        else if(t==5)cout<<"200";
        else if(t==0)cout<<"110";//t可能为0，如t=6
    }
    return 0;
}
```
- **作者：yzm0325 (4星)**
    - **关键亮点**：详细分析暴力法不可行的原因，通过打表详细列出数据找到规律，代码实现按照规律清晰编写，注释详细。
    - **个人心得**：无
    - **重点代码核心思想**：对n进行特判，n大于3时，先输出首位1，再输出n - 4个0，最后根据(n - 3) % 6的结果输出对应的后三位。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
const string msw[10] = {"110", "050", "080", "170", "020", "200"}; 
int n;
int main() {
    cin >> n;
    if(n == 1 || n == 2) cout << -1;
    else if(n == 3) cout << 210; 
    else {
        cout << 1; 
        for(int i = 1; i <= n - 4; i++) cout << 0; 
        cout << msw[(n - 3) % 6]; 
    }
    return 0;  
}
```

### 最优关键思路或技巧
通过打表找规律是解决本题的关键技巧。当直接的暴力枚举等常规方法因数据范围受限无法使用时，通过较小数据的计算结果来发现规律，从而简化问题的求解过程。

### 拓展
此类题目属于数论中寻找数字规律并求解特定条件数字的类型。类似套路是在遇到数据范围大无法暴力求解的数论题时，尝试通过打表观察数字特征、寻找周期规律等方式解题。

### 相似知识点洛谷题目
- [P1075 质因数分解](https://www.luogu.com.cn/problem/P1075)
- [P1217 [USACO1.5]回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)
- [P2681 求和](https://www.luogu.com.cn/problem/P2681) 

---
处理用时：36.20秒