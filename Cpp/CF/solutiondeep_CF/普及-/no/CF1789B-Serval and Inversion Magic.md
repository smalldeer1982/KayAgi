# 题目信息

# Serval and Inversion Magic

## 题目描述

Serval has a string $ s $ that only consists of 0 and 1 of length $ n $ . The $ i $ -th character of $ s $ is denoted as $ s_i $ , where $ 1\leq i\leq n $ .

Serval can perform the following operation called Inversion Magic on the string $ s $ :

- Choose an segment $ [l, r] $ ( $ 1\leq l\leq r\leq n $ ). For $ l\leq i\leq r $ , change $ s_i $ into 1 if $ s_i $ is 0, and change $ s_i $ into 0 if $ s_i $ is 1.

For example, let $ s $ be 010100 and the segment $ [2,5] $ is chosen. The string $ s $ will be 001010 after performing the Inversion Magic.

Serval wants to make $ s $ a palindrome after performing Inversion Magic exactly once. Help him to determine whether it is possible.

A string is a palindrome iff it reads the same backwards as forwards. For example, 010010 is a palindrome but 10111 is not.

## 说明/提示

In the first test case, Serval can perform Inversion Magic on the segment $ [1,4] $ . The string $ s $ will be 0110 after the magic.

In the second test case, Serval can perform Inversion Magic on the segment $ [1,3] $ . The string $ s $ will be 01110 after the magic.

In the third test case, Serval can't make $ s $ a palindrome by performing Inversion Magic exactly once.

## 样例 #1

### 输入

```
3
4
1001
5
10010
7
0111011```

### 输出

```
Yes
Yes
No```

# AI分析结果

### 题目内容
#### Serval和反转魔法
1. **题目描述**：Serval有一个长度为\(n\)的字符串\(s\)，仅由\(0\)和\(1\)组成。\(s\)的第\(i\)个字符记为\(s_i\)，其中\(1\leq i\leq n\)。Serval可以对字符串\(s\)执行以下称为反转魔法的操作：
    - 选择一个区间\([l, r]\)（\(1\leq l\leq r\leq n\)）。对于\(l\leq i\leq r\)，如果\(s_i\)为\(0\)，则将其变为\(1\)；如果\(s_i\)为\(1\)，则将其变为\(0\)。
    - 例如，设\(s\)为\(010100\)，选择区间\([2, 5]\)。执行反转魔法后，字符串\(s\)将变为\(001010\)。
    - Serval希望在恰好执行一次反转魔法后，使\(s\)成为回文串。帮助他确定这是否可能。
    - 一个字符串是回文串，当且仅当它从后向前读和从前向后读是一样的。例如，\(010010\)是回文串，但\(10111\)不是。
2. **说明/提示**：
    - 在第一个测试用例中，Serval可以对区间\([1, 4]\)执行反转魔法。魔法执行后，字符串\(s\)将变为\(0110\)。
    - 在第二个测试用例中，Serval可以对区间\([1, 3]\)执行反转魔法。魔法执行后，字符串\(s\)将变为\(01110\)。
    - 在第三个测试用例中，Serval无法通过恰好执行一次反转魔法使\(s\)成为回文串。
3. **样例 #1**：
    - **输入**：
```
3
4
1001
5
10010
7
0111011
```
    - **输出**：
```
Yes
Yes
No
```

### 算法分类
字符串

### 题解综合分析与结论
所有题解的核心思路都是判断通过一次区间反转能否将给定的\(01\)字符串变为回文串，通过检查字符串两端对应位置字符的差异情况，判断需要反转的位置是否连续。若连续则可以通过一次操作实现回文，否则不能。时间复杂度均为\(O(n)\)，不同之处主要在于实现细节和判断连续的方式。

### 所选的题解
1. **作者：liaiyang (5星)**
    - **关键亮点**：思路清晰简洁，直接使用双指针从两端向中间扫描，通过两个标志位记录遇到的需要修改的情况，判断是否存在区间断开的情况，代码实现简洁明了。
    - **重点代码**：
```cpp
void work(){
    cin>>n>>a;flag=flag1=0;
    for(int i=0;i<(n>>1);i++){
        if(a[i]!=a[n-i-1]){
            if(flag&&flag1){
                cout<<"No"<<endl;
                return ;
            }
            flag=1;
        }
        else if(flag) flag1=1;
    }
    cout<<"Yes"<<endl;
}
```
    - **核心思想**：使用双指针遍历字符串前半部分，当遇到两端字符不同时，若已经存在一次需要修改的情况（`flag`为真）且此时`flag1`也为真，说明存在区间断开，输出`No`；否则标记`flag`为真。若遇到两端字符相同时且`flag`为真，标记`flag1`为真。遍历结束若未返回`No`，则输出`Yes`。
2. **作者：arrow_king (4星)**
    - **关键亮点**：先通过标记数组记录前\(\left\lfloor\dfrac{n}{2}\right\rfloor\)个字符中与对应位置字符不同的位置，再通过统计标记数组中相邻元素不同的次数来判断需要修改的标记是否为连续区间，思路独特。
    - **重点代码**：
```cpp
int main() {
    t=read();
    while(t--) {
        n=read();
        scanf("%s",s+1);
        for(int i=1;i<=n;i++) tag[i]=0;
        for(int i=1;i<=n/2;i++) if(s[i]!=s[n-i+1]) tag[i]=1;
        int cnt=0;
        for(int i=2;i<=n;i++) if(tag[i]!=tag[i-1]) cnt++;
        if(cnt<=2) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
```
    - **核心思想**：首先初始化标记数组`tag`，遍历前半部分字符串，标记与对应位置字符不同的位置。然后遍历标记数组，统计相邻元素不同的次数`cnt`，若`cnt`小于等于\(2\)，说明需要修改的标记为连续区间，输出`Yes`，否则输出`No`。
3. **作者：Fleeing_loser (4星)**
    - **关键亮点**：通过两个变量`sum`和`ss`分别记录不相等字符的数量以及不相等字符位置是否连续，逻辑清晰，代码简洁。
    - **重点代码**：
```cpp
for(int i=1;i<=(n/2);++i)
{
    if(s[i]!=s[n-i+1]) ++sum,ss+=flag;
    else if(ss) flag=0;
}
if(ss!=sum) printf("No\n");
else printf("Yes\n");
```
    - **核心思想**：遍历字符串前半部分，当遇到两端字符不同时，`sum`自增且`ss`加上`flag`（初始`flag`为\(1\)），表示不相等字符位置连续；当遇到两端字符相同时且`ss`不为\(0\)，说明不相等字符位置断开，将`flag`置为\(0\)。最后比较`ss`和`sum`，若相等说明不相等字符位置连续，输出`Yes`，否则输出`No`。

### 最优关键思路或技巧
使用双指针从两端向中间遍历字符串，通过记录和判断需要反转的字符位置是否连续，来确定能否通过一次区间反转将字符串变为回文串。这种方法直接针对问题核心，避免了复杂的操作和过多的中间变量，有效降低了算法的时间和空间复杂度。

### 可拓展之处
同类型题通常围绕字符串的特定操作和性质判断展开，如对字符串进行其他类型的变换操作后判断是否满足某种性质，类似算法套路是先分析操作对字符串性质的影响，再通过合适的数据结构或方法记录相关信息，最后根据记录信息判断是否满足目标性质。

### 洛谷相似题目推荐
1. [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)：涉及字符串的查找和统计，与本题一样需要对字符串进行遍历和判断。
2. [P1501 单词翻转](https://www.luogu.com.cn/problem/P1501)：关于字符串的操作，通过对字符串的处理实现特定功能，和本题对字符串操作判断性质类似。
3. [P3378 【模板】堆优化 Dijkstra](https://www.luogu.com.cn/problem/P3378)：虽然主要是图论最短路问题，但在实现过程中涉及到对数据的处理和判断，和本题处理字符串判断性质在思维方式上有一定相似性。

### 个人心得摘录与总结
无。 

---
处理用时：49.25秒