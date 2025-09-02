# 题目信息

# Divisibility by Eight

## 题目描述

You are given a non-negative integer $ n $ , its decimal representation consists of at most $ 100 $ digits and doesn't contain leading zeroes.

Your task is to determine if it is possible in this case to remove some of the digits (possibly not remove any digit at all) so that the result contains at least one digit, forms a non-negative integer, doesn't have leading zeroes and is divisible by 8. After the removing, it is forbidden to rearrange the digits.

If a solution exists, you should print it.

## 样例 #1

### 输入

```
3454
```

### 输出

```
YES
344
```

## 样例 #2

### 输入

```
10
```

### 输出

```
YES
0
```

## 样例 #3

### 输入

```
111111
```

### 输出

```
NO
```

# AI分析结果

### 题目中文重写
# 被 8 整除

## 题目描述
给定一个非负整数 $n$，它的十进制表示最多包含 100 位，且不包含前导零。

你的任务是判断是否可以通过移除其中某些数字（也可以不移除任何数字），使得剩余的数字至少有一位，形成一个非负整数，没有前导零，并且能被 8 整除。移除数字后，禁止重新排列这些数字。

如果存在这样的解决方案，你应该输出它。

## 样例 #1
### 输入
```
3454
```
### 输出
```
YES
344
```

## 样例 #2
### 输入
```
10
```
### 输出
```
YES
0
```

## 样例 #3
### 输入
```
111111
```
### 输出
```
NO
```

### 综合分析与结论
这些题解的核心思路都是利用“一个数能被 8 整除，其末三位一定能被 8 整除”这一性质。大部分题解通过枚举一位数、两位数和三位数的组合来判断是否能得到 8 的倍数，部分题解采用打表的方式。

### 思路、算法要点与难点对比
|作者|思路|算法要点|解决难点|
| ---- | ---- | ---- | ---- |
|灵光一闪|先特判 0，再枚举一位数、两位数、三位数组合|三层嵌套循环枚举|无|
|FuriousC|暴力枚举，先找 0，再枚举不同位数组合|三层嵌套循环枚举|无|
|HuZHUNZHUN|分别用一、二、三层循环枚举一位数、两位数、三位数|分层循环枚举|无|
|Maxrage|提出打表思路，同时指出特判问题|打表并特判|处理数字不连续的情况|
|Creator_157|枚举后三位，先特判 0|三层嵌套循环枚举|无|
|封禁用户|打表 8 的倍数，根据位数不同用不同重循环判断|打表和多重循环判断|无|
|Neoomgg|先特判 0 和 8，再暴力枚举|反向枚举并判断整除|无|
|SSHhh|特判 0 和 8，用 s[i] 和 e[i] 记录位置，暴力判断三位数 8 的倍数|记录位置并判断|处理不含前导 0 的情况|

### 题解评分
|作者|评分|
| ---- | ---- |
|灵光一闪|4星|
|FuriousC|4星|
|HuZHUNZHUN|3星|
|Maxrage|3星|
|Creator_157|4星|
|封禁用户|3星|
|Neoomgg|3星|
|SSHhh|3星|

### 所选题解
- **灵光一闪（4星）**
    - **关键亮点**：思路清晰，代码简洁，直接利用整除性质进行枚举。
    - **核心代码**：
```cpp
#include<iostream>
#include<string>
using namespace std;
int main(){
    string s;
    cin>>s;
    int a=s.find('0');
    if(a<s.size()){
        puts("YES");
        puts("0");
        return 0;
    }
    for(int i=0;i<s.size();i++){
        for(int j=i+1;j<s.size();j++){
            for(int k=j+1;k<s.size();k++){
                if(((s[i]-'0')*100+(s[j]-'0')*10+(s[k]-'0'))%8==0){
                    puts("YES");
                    cout<<s[i]<<s[j]<<s[k]<<endl;
                    return 0;
                }
            }
            if(((s[i]-'0')*10+(s[j]-'0'))%8==0){
                puts("YES");
                cout<<s[i]<<s[j]<<endl;
                return 0;
            }
        }
        if((s[i]-'0')%8==0){
            puts("YES");
            cout<<s[i]<<endl;
            return 0;
        }
    }
    puts("NO");
    return 0;
}
```
核心实现思想：先判断字符串中是否有 0，若有则直接输出 "YES" 和 0。然后通过三层嵌套循环枚举一位数、两位数和三位数的组合，判断是否能被 8 整除，若能则输出结果并结束程序，若都不满足则输出 "NO"。

- **FuriousC（4星）**
    - **关键亮点**：思路与上一个类似，代码结构清晰。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    string str;
    int a;
    cin>>str;
    a=str.find('0');
    if(a<str.size()){
        cout<<"YES\n0";
        return 0;
    }
    for(int i=0;i<str.size();i++){
        a=str[i]-'0';
        for(int j=i+1;j<str.size();j++){
            int b=str[j]-'0';
            for(int k=j+1;k<str.size();k++){
                int c=str[k]-'0';
                if((a*100+b*10+c)%8==0){
                    cout<<"YES\n"<<a<<b<<c;
                    return 0;
                }
            }
            if((a*10+b)%8==0){
                cout<<"YES\n"<<a<<b;
                return 0;
            }
        }
        if(a%8==0){
            cout<<"YES\n"<<a;
            return 0;
        }
    }
    cout<<"NO";
    return 0;
}
```
核心实现思想：同样先找 0，然后通过三层嵌套循环枚举不同位数的组合，判断是否能被 8 整除，能则输出结果，否则输出 "NO"。

- **Creator_157（4星）**
    - **关键亮点**：思路简洁，代码规范。
    - **核心代码**：
```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;
string s;
int a;
int main()
{
    cin>>s;
    a=s.find('0');
    if(a<s.size())
    {
        printf("YES\n0");
        return 0;
    }
    for(int i=0;i<s.size();i++)
    {
        for(int j=i+1;j<s.size();j++)
        {
            for(int l=j+1;l<s.size();l++)
            {
                if(((s[i]-'0')*100+(s[j]-'0')*10+(s[l]-'0'))%8==0)
                {
                    printf("YES\n");
                    cout<<s[i]<<s[j]<<s[l];
                    return 0;
                }
            }
            if(((s[i]-'0')*10+(s[j]-'0'))%8==0)
            {
                printf("YES\n");
                cout<<s[i]<<s[j];
                return 0;
            }
        }
        if((s[i]-'0')%8==0)
        {
            printf("YES\n");
            cout<<s[i];
            return 0;
        }
    }
    printf("NO");
    return 0;
}
```
核心实现思想：先判断字符串中是否有 0，若有则输出 "YES" 和 0。接着通过三层嵌套循环枚举不同位数组合，判断能否被 8 整除，能则输出结果，否则输出 "NO"。

### 最优关键思路或技巧
- 利用“一个数能被 8 整除，其末三位一定能被 8 整除”的性质，通过枚举一位数、两位数和三位数的组合来判断是否能得到 8 的倍数。
- 先特判字符串中是否有 0，简化判断过程。

### 可拓展之处
同类型题可能会改变整除的数，如判断能否被 3、4、9 等整除，可根据相应的整除性质进行类似的枚举判断。类似算法套路是利用数的整除性质，通过枚举组合来解决问题。

### 推荐洛谷题目
- P1055 [NOIP2008 普及组] ISBN 号码
- P1042 [NOIP2003 普及组] 乒乓球
- P1067 [NOIP2009 普及组] 多项式输出

### 个人心得摘录与总结
- **Maxrage**：提到打表思路，但也指出了数字不连续的问题，强调在处理时需要特判，避免程序出现错误。
- **Neoomgg**：表示一开始漏掉了两位数整除 8 的情况，提醒在解题时要考虑全面，不能遗漏可能的情况。 

---
处理用时：42.94秒