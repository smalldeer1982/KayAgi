# 题目信息

# Wrong Addition

## 题目描述

Tanya is learning how to add numbers, but so far she is not doing it correctly. She is adding two numbers $ a $ and $ b $ using the following algorithm:

1. If one of the numbers is shorter than the other, Tanya adds leading zeros so that the numbers are the same length.
2. The numbers are processed from right to left (that is, from the least significant digits to the most significant).
3. In the first step, she adds the last digit of $ a $ to the last digit of $ b $ and writes their sum in the answer.
4. At each next step, she performs the same operation on each pair of digits in the same place and writes the result to the left side of the answer.

For example, the numbers $ a = 17236 $ and $ b = 3465 $ Tanya adds up as follows:

 $ $$$ \large{ \begin{array}{r} + \begin{array}{r} 17236\\ 03465\\ \end{array} \\ \hline \begin{array}{r} 1106911 \end{array} \end{array}}  $ $ </p><ul> <li> calculates the sum of  $ 6 + 5 = 11 $  and writes  $ 11 $  in the answer. </li><li> calculates the sum of  $ 3 + 6 = 9 $  and writes the result to the left side of the answer to get  $ 911 $ . </li><li> calculates the sum of  $ 2 + 4 = 6 $  and writes the result to the left side of the answer to get  $ 6911 $ . </li><li> calculates the sum of  $ 7 + 3 = 10 $ , and writes the result to the left side of the answer to get  $ 106911 $ . </li><li> calculates the sum of  $ 1 + 0 = 1 $  and writes the result to the left side of the answer and get  $ 1106911 $ . </li></ul><p>As a result, she gets  $ 1106911 $ .</p><p>You are given two positive integers  $ a $  and  $ s $ . Find the number  $ b $  such that by adding  $ a $  and  $ b $  as described above, Tanya will get  $ s $ . Or determine that no suitable  $ b$$$ exists.

## 说明/提示

The first test case is explained in the main part of the statement.

In the third test case, we cannot choose $ b $ that satisfies the problem statement.

## 样例 #1

### 输入

```
6
17236 1106911
1 5
108 112
12345 1023412
1 11
1 20```

### 输出

```
3465
4
-1
90007
10
-1```

# AI分析结果

### 题目翻译
## 错误的加法

### 题目描述
坦尼娅正在学习如何加法，但到目前为止她做得并不正确。她使用以下算法将两个数字 $a$ 和 $b$ 相加：

1. 如果其中一个数字比另一个短，坦尼娅会添加前导零，使两个数字长度相同。
2. 从右到左处理数字（即从最低有效位到最高有效位）。
3. 在第一步中，她将 $a$ 的最后一位数字与 $b$ 的最后一位数字相加，并将它们的和写在答案中。
4. 在接下来的每一步中，她对相同位置的每对数字执行相同的操作，并将结果写在答案的左侧。

例如，坦尼娅将数字 $a = 17236$ 和 $b = 3465$ 相加的过程如下：

```
  17236
+ 03465
 -------
 1106911
```
- 计算 $6 + 5 = 11$，并将 $11$ 写在答案中。
- 计算 $3 + 6 = 9$，并将结果写在答案的左侧，得到 $911$。
- 计算 $2 + 4 = 6$，并将结果写在答案的左侧，得到 $6911$。
- 计算 $7 + 3 = 10$，并将结果写在答案的左侧，得到 $106911$。
- 计算 $1 + 0 = 1$，并将结果写在答案的左侧，得到 $1106911$。

结果，她得到了 $1106911$。

给定两个正整数 $a$ 和 $s$。找到一个数字 $b$，使得按照上述方法将 $a$ 和 $b$ 相加，坦尼娅将得到 $s$。或者确定不存在合适的 $b$。

### 说明/提示
第一个测试用例在题目的主要部分有解释。

在第三个测试用例中，我们无法选择满足问题条件的 $b$。

### 样例 #1
#### 输入
```
6
17236 1106911
1 5
108 112
12345 1023412
1 11
1 20
```
#### 输出
```
3465
4
-1
90007
10
-1
```

### 综合分析与结论
这些题解的核心思路都是将新定义的加法转化为减法来求解 $b$。具体做法是逐位处理 $a$ 和 $s$ 的每一位数字，根据当前位的大小关系判断是否需要借位。若 $s$ 当前位大于等于 $a$ 当前位，则直接相减；若小于，则考虑借位情况，若借位后仍不满足条件则无解。同时，要注意处理前导零和判断最终结果是否合法。

### 所选题解
- **作者：StayAlone（5星）**
    - **关键亮点**：思路清晰，代码简洁，通过双指针模拟减法过程，对无解情况的判断全面且清晰。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
string a, b, ans;
bool ct(string k, int y, int len) {
    for (int i = y; i < len; ++i) if (k[i] ^ '0') return false;
    return true;
}
int main() {
    int T; cin >> T;
    while (T--) {
        cin >> a >> b; ans = "";
        int len1 = a.size(), len2 = b.size();
        if (len2 < len1) {
            puts("-1"); continue;
        }
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        while (len1 < len2) ++len1, a += '0';
        while (len1 > len2) ++len2, b += '0';
        int l = 0, r = 0; bool f = true;
        while (r < len2) {
            if (b[r] >= a[l]) ans += char(b[r] - a[l] + '0'), ++l, ++r;
            else if (r + 1 > len2 - 1 || b[r + 1]!= '1') {
                f = false; break;
            }
            else ans += char(10 + b[r] - '0' - a[l] + '0'), ++l, r += 2;
        }
        f = ct(a, l, len1) && ct(b, r, len2);
        reverse(ans.begin(), ans.end());
        int t = 0, x = ans.size();
        while (ans[t] == '0' && t + 1 < x) ++t;
        string opt = "";
        for (int i = t; i < x; ++i) opt += ans[i];
        if (!f) puts("-1"); else cout << opt << '\n';
    }
    return 0;
}
```
    - **核心实现思想**：先将两个字符串反转并补齐长度，然后使用双指针从低位到高位逐位处理。根据当前位的大小关系进行相减或借位操作，最后处理前导零并输出结果。

- **作者：yanhao40340（4星）**
    - **关键亮点**：通过重载减法运算符实现新定义的减法，代码结构清晰，对无解情况的判断明确。
    - **核心代码**：
```cpp
#include <iostream>
#include <string>
#define num(x) (x-'0')
using namespace std;
typedef long long ll;
string getstr() {
    char f='\0';string s;
    while (f=='\n'||f=='\0'||f==' ') f=getchar();
    while (f!='\n'&&f!='\0'&&f!=' ') s+=f,f=getchar();
    return s;
}
ll Pow(ll power,ll base) {
    ll res=1;
    while (base) {
        if (base&1) res=power*res;
        power=power*power,base>>=1;
    }
    return res;
}
ll operator -(string s,string t) {
    if (s.size()<t.size()) return -1;
    int tmps=s.size()-1,tmpt=t.size()-1;ll ans=0,tmp=0;
    while (tmpt!=-1) {
        if (tmps==-1) return -1;
        if (s[tmps]>=t[tmpt]) ans+=(s[tmps]-t[tmpt])*Pow(10,tmp),--tmps,--tmpt;
        else if (tmps==0) return -1;
        else if (s[tmps-1]!='1') return -1;
        else ans+=(10+num(s[tmps])-num(t[tmpt]))*Pow(10,tmp),tmps-=2,--tmpt;
        ++tmp;
    }
    if (tmps>=0) {
        for (int i=tmps;i>=0;--i)
            ans+=num(s[i])*Pow(10,tmp),++tmp;
    }
    return ans;
}
int main() {
    int t;scanf("%d",&t);
    while (t--) {
        string a=getstr(),b=getstr();
        printf("%lld\n",b-a);
    }
    return 0;
}
```
    - **核心实现思想**：重载减法运算符，在运算符重载函数中处理减法逻辑，包括借位和无解判断，最后将剩余的被减数部分添加到结果中。

- **作者：heaksicn（4星）**
    - **关键亮点**：思路直接，通过分离数位进行逐位处理，对结果的合法性判断和前导零处理较为细致。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int T;
int a[25],s[25],b[25];
ll q,p;
int lb;
bool check() {
    for(int i=1;i<=lb;i++) {
        if(b[i]) return 0;
    }
    return 1;
}
int main() {
    T=read();
    while(T--) {
        cin>>q>>p;
        int la=0;
        while(q) {
            a[++la]=q%10;
            q/=10;
        }
        int ls=0;
        while(p) {
            s[++ls]=p%10;
            p/=10;
        }
        ll ans=0;
        bool flag=0;
        int qp=1;
        lb=0;
        for(int i=1;i<=la;i++) {
            if(qp>ls) {
                cout<<-1;
                flag=1;
                break;
            }
            int now=s[qp]-a[i];
            if(now<0) {
                qp++;
                if(qp>ls) {
                    cout<<-1;
                    flag=1;
                    break;
                }
                now+=10*s[qp];
            }
            if(now>9||now<0) {
                cout<<-1;
                flag=1;
                break;
            }
            b[++lb]=now;
            qp++;
        }
        if(qp<=ls) {
            for(int i=qp;i<=ls;i++) b[++lb]=s[i];
        }
        if(!flag) {
            if(check()) {
                cout<<0;
                cout<<endl;
                continue;
            }
            bool fl=0;
            for(int i=lb;i>=1;i--) {
                if(b[i]!=0) fl=1;
                if(b[i]==0&&fl==0) continue;
                cout<<b[i];
            }
        }
        cout<<endl;
    }
    return 0;
}
```
    - **核心实现思想**：先将输入的数字分离数位，然后从低位到高位逐位相减，处理借位和无解情况，最后将剩余的被减数部分添加到结果中，并处理前导零。

### 最优关键思路或技巧
- **将加法转化为减法**：通过将新定义的加法运算转化为减法运算，简化问题求解过程。
- **双指针模拟**：使用双指针逐位处理数字，清晰地模拟减法过程，便于处理借位和判断无解情况。
- **处理前导零**：在输出结果时，注意去除前导零，确保结果的正确性。

### 可拓展之处
同类型题目可能会改变加法或减法的规则，例如改变进位方式或运算顺序。类似算法套路可以应用于其他自定义运算的逆运算求解问题，关键在于准确理解运算规则并将其转化为代码实现。

### 推荐题目
- [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)：涉及动态规划和路径规划，需要理解规则并进行状态转移。
- [P1216 [USACO1.5][IOI1994]数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)：动态规划基础题，通过定义状态和状态转移方程求解最优解。
- [P1464 Function](https://www.luogu.com.cn/problem/P1464)：涉及递归和记忆化搜索，需要根据函数定义进行递归计算并优化。

### 个人心得摘录与总结
- **Tulip_**：表示因为其他大佬的题解看不懂，所以以蒟蒻视角讲解，强调了自己思考和理解题目的过程。
总结：在学习过程中，不同水平的学习者对题解的理解和需求不同，以自己的视角讲解可以帮助更多人理解问题。
- **mcDinic**：提到写记忆化搜索是因为一开始没想到动态规划，还加了记忆化来剪枝。
总结：在解题时，不同的思维方式会导致不同的解法，适当使用记忆化可以优化算法效率。 

---
处理用时：63.42秒