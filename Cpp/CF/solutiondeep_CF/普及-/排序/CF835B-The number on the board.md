# 题目信息

# The number on the board

## 题目描述

Some natural number was written on the board. Its sum of digits was not less than $ k $ . But you were distracted a bit, and someone changed this number to $ n $ , replacing some digits with others. It's known that the length of the number didn't change.

You have to find the minimum number of digits in which these two numbers can differ.

## 说明/提示

In the first example, the initial number could be $ 12 $ .

In the second example the sum of the digits of $ n $ is not less than $ k $ . The initial number could be equal to $ n $ .

## 样例 #1

### 输入

```
3
11
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
99
```

### 输出

```
0
```

# AI分析结果

### 题目中文重写
# 黑板上的数字

## 题目描述
黑板上原本写着一个自然数，它的各位数字之和不小于 $k$。但你稍微分了下神，有人把这个数字改成了 $n$，即用其他数字替换了原数字中的某些数位。已知数字的长度没有改变。

你需要找出这两个数字最少在多少个数位上不同。

## 说明/提示
在第一个样例中，最初的数字可能是 $12$。

在第二个样例中，$n$ 的各位数字之和不小于 $k$，最初的数字可能就等于 $n$。

## 样例 #1
### 输入
```
3
11
```
### 输出
```
1
```

## 样例 #2
### 输入
```
3
99
```
### 输出
```
0
```

### 综合分析与结论
这些题解的核心思路均为贪心算法，要使修改次数最少，每次应将最小的数字改为 $9$，这样每次修改后各位数字之和增加最多。
- **思路**：先计算当前数字各位之和，若大于等于 $k$ 则无需修改，直接输出 $0$；否则将各位数字从小到大排序，依次把最小的数字改为 $9$，直到各位数字之和大于等于 $k$，记录修改次数。
- **算法要点**：字符串读入数字，字符转整数，排序，贪心修改。
- **解决难点**：处理大数字需用字符串读入；证明贪心策略的正确性，即每次修改最小数字能使修改次数最少。

### 所选题解
- **wyk0247（5星）**
    - **关键亮点**：思路清晰，代码注释详细，完整展示解题步骤。
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int k;
int he=0;
int len,ans;
string s;
int a[1010];
int main()
{
    cin>>k>>s;
    len=s.size();
    for(int i=0;i<len;i++)
    {
        a[i]=s[i]-'0';
        he+=a[i];
    }
    sort(a,a+len); 
    if(he>=k)
        printf("0");
    else
    {
        for(int i=0;i<len;i++)
        {
            he+=9-a[i];
            ans=i+1;
            if(he>=k)
                break;
        }
        printf("%d",ans);
    }
    return 0;
} 
```
核心实现思想：先读入 $k$ 和字符串 $s$，将 $s$ 各位数字存入数组 $a$ 并求和，若和大于等于 $k$ 输出 $0$，否则排序后依次修改最小数字，直到和大于等于 $k$ 输出修改次数。
- **LegendaryGrandmaster（4星）**
    - **关键亮点**：代码简洁，逻辑清晰，对思路有简要说明。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
    int k;
    string st;
    cin>>k>>st;
    sort(st.begin(),st.end());
    int c=0;
    for(int i=0;i<st.size();i++)c+=st[i]-48;
    c-=k;
    if(c>=0){
        cout<<0;
        return 0;
    }
    else{
        c=abs(c);
        int ans=0;
        for(int i=0;i<st.size();i++){
            c-=9-(st[i]-48);
            ans++;
            if(c<=0)break;
        }
        cout<<ans;
        return 0;
    }
}
```
核心实现思想：读入 $k$ 和字符串 $st$ 并排序，计算各位数字和与 $k$ 的差值，若差值大于等于 $0$ 输出 $0$，否则依次修改最小数字，直到差值小于等于 $0$ 输出修改次数。
- **ice_fish01（4星）**
    - **关键亮点**：对算法有详细分析，给出贪心策略证明。
    - **核心代码**：
```cpp
string s;
cin >> k;
getline(cin,s); 
getline(cin,s);
int len = s.length();
for(int i = len - 1,j = 1;i >= 0;i--,j++) 
{
    a[j] = s[i] - '0';
    sum += a[j];
}
if(sum >= k)
{
    puts("0");
    return 0;
}
sort(a+1,a+len+1);
for(int i = 1;sum < k && i <= len;i++)
{
    sum += 9 - a[i]; 
    ans++;
}
cout << ans;
```
核心实现思想：高精度读入数字，计算各位数字和，若和大于等于 $k$ 输出 $0$，否则排序后依次修改最小数字，直到和大于等于 $k$ 输出修改次数。

### 最优关键思路或技巧
- **贪心策略**：每次将最小的数字改为 $9$，使每次修改后各位数字之和增加最多，从而减少修改次数。
- **排序优化**：对各位数字从小到大排序，方便每次选择最小数字进行修改。

### 拓展思路
同类型题目可考虑其他贪心场景，如每次操作使某个指标变化最大或最小，常见于资源分配、区间调度等问题。类似算法套路为通过排序、优先队列等数据结构辅助贪心选择。

### 推荐题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：每次合并最小的两堆果子，使总代价最小，考察贪心算法和优先队列的使用。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：按接水时间从小到大排序，使所有人等待时间总和最小，是简单的贪心应用。
- [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)：按单位价值从高到低选择物品，使背包内物品总价值最大，体现贪心策略在背包问题中的应用。

### 个人心得摘录与总结
- **ice_fish01**：提到高精度数处理细节考验代码实现能力，需注意证明贪心思路，提醒做题时要关注特殊情况处理和算法正确性证明。
- **happybob**：发现 `length()` 和 `size()` 在运行时间上有差异，说明实际编程中要留意不同函数的性能表现。 

---
处理用时：42.13秒