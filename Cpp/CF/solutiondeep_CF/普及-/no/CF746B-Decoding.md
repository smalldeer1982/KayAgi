# 题目信息

# Decoding

## 题目描述

## **题目大意**

Polycarp很想编码，这就是他编写Sveta编码信息的原因。他把中间字母称为单词中间的字母。如果单词的长度是偶数，则中间字母是两个中间字母的左边。在以下示例中，中间字母突出显示：con**t** est，i**n**fo。如果单词由单个字母组成，则根据上面的定义，这个字母是中间字母。



Polycarp以下列方式对每个单词进行编码：他写下单词的中间字母，然后将其删除并重复该过程，直到没有字母为止。例如，他将volga编码为logva。



你得到一个编码，你的任务是进行译码。

## 样例 #1

### 输入

```
5
logva
```

### 输出

```
volga
```

## 样例 #2

### 输入

```
2
no
```

### 输出

```
no
```

## 样例 #3

### 输入

```
4
abba
```

### 输出

```
baba
```

# AI分析结果

### 算法分类
字符串

### 综合分析与结论
这些题解围绕字符串解密展开，核心是根据给定的加密规则逆向还原原字符串。不同题解在思路和实现方式上各有特点：
- **模拟插入法**：通过模拟加密的逆过程，每次将加密字符串的字符插入到已解密字符串的特定位置，如 `CGDGAD` 的题解使用 `vector<char>` 实现插入操作。
- **找规律输出法**：通过分析样例，总结出根据字符串长度奇偶性和字符下标来确定输出顺序的规律，如 `OMITW`、`used_to_be` 等题解。
- **位置对应法**：使用数组或 `vector` 存储位置信息，根据中间位置对应关系还原原字符串，如 `_Spectator` 的题解。

### 所选的题解
- **CGDGAD（4星）**：
    - **关键亮点**：思路清晰，详细模拟了加密的逆过程，通过 `vector<char>` 实现插入操作，代码简洁易懂。
    - **核心代码**：
```cpp
#include <cstdio>
#include <vector>
using namespace std;
int cnt;
vector<char> decoded; // 被解密的字符串
char encoded[10001]; // 被加密的字符串
int main() {
    scanf("%d%s", &cnt, encoded); // 输入
    decoded.push_back(encoded[cnt - 1]); // 将被加密字符串的最后一个push进vector
    for (int i = cnt - 2; i >= 0; i -= 1) { // 从倒数第二个字符开始倒序遍历encoded字符串
        int index = decoded.size() / 2; // 插入在第 size ÷ 2 个位置
        decoded.insert(decoded.begin() + index, encoded[i]); // 使用insert()插入
    }
    for (int i = 0; i < decoded.size(); i += 1) {
        printf("%c", decoded[i]); // 输出
    }
    return 0;
}
```
**核心实现思想**：先将加密字符串的最后一个字符放入 `vector` 中，然后从倒数第二个字符开始倒序遍历加密字符串，每次将字符插入到 `vector` 的 `size() / 2` 位置，最后输出 `vector` 中的字符。

- **OMITW（4星）**：
    - **关键亮点**：代码简洁，通过找规律直接输出结果，无需额外存储。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
string s;
int main()
{
    cin>>n>>s;
    for(int i=n-2;i>=0;i-=2)cout<<s[i];
    for(int i=!(s.size()%2);i<n;i+=2)cout<<s[i];
    return 0;
}
```
**核心实现思想**：根据字符串长度的奇偶性，先从后往前每隔一个字符输出，再从前往后每隔一个字符输出。

- **_Spectator（4星）**：
    - **关键亮点**：使用 `vector<int>` 存储位置信息，通过中间位置对应关系还原原字符串，思路巧妙。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
char s[2005],st[2005];
vector<int>p;
int main()
{
    cin>>n>>s;
    for(int i=0;i<n;i++)
        p.push_back(i);//存入位置 
    for(int i=0;i<n;i++)
    {
        int pos=(n-i+1)/2-1;//找到中间位置 
        st[p[pos]]=s[i];//对应位置，还原原码 
        p.erase(p.begin()+pos);//删除中间位置 
    }
    cout<<st;
    return 0;
}
```
**核心实现思想**：先将位置信息存入 `vector<int>` 中，然后遍历加密字符串，每次找到中间位置，将对应字符放入原字符串的相应位置，再删除该中间位置。

### 最优关键思路或技巧
- **逆向思维**：从加密的逆过程思考，找到解密的方法。
- **找规律**：通过分析样例，总结出根据字符串长度奇偶性和字符下标来确定输出顺序或插入位置的规律。
- **使用合适的数据结构**：如 `vector` 可以方便地进行插入和删除操作。

### 拓展思路
同类型题可能涉及不同的加密规则，解题关键在于理解加密规则并逆向推导。类似算法套路包括模拟、找规律、位置对应等，可应用于密码学、字符串处理等领域的问题。

### 推荐题目
- [P1055 ISBN号码](https://www.luogu.com.cn/problem/P1055)
- [P1200 [USACO1.1]你的飞碟在这儿Your Ride Is Here](https://www.luogu.com.cn/problem/P1200)
- [P1598 垂直柱状图](https://www.luogu.com.cn/problem/P1598)

### 个人心得摘录与总结
- **qfpjm**：提到字符串的 `size` 函数时间复杂度是 $O(n)$，若数据大可能 TLE，提醒注意复杂度问题。总结：在处理字符串时，要考虑操作的时间复杂度，避免因复杂度高导致超时。

---
处理用时：34.39秒