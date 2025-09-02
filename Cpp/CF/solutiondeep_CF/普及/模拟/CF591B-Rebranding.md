# 题目信息

# Rebranding

## 题目描述

The name of one small but proud corporation consists of $ n $ lowercase English letters. The Corporation has decided to try rebranding — an active marketing strategy, that includes a set of measures to change either the brand (both for the company and the goods it produces) or its components: the name, the logo, the slogan. They decided to start with the name.

For this purpose the corporation has consecutively hired $ m $ designers. Once a company hires the $ i $ -th designer, he immediately contributes to the creation of a new corporation name as follows: he takes the newest version of the name and replaces all the letters $ x_{i} $ by $ y_{i} $ , and all the letters $ y_{i} $ by $ x_{i} $ . This results in the new version. It is possible that some of these letters do no occur in the string. It may also happen that $ x_{i} $ coincides with $ y_{i} $ . The version of the name received after the work of the last designer becomes the new name of the corporation.

Manager Arkady has recently got a job in this company, but is already soaked in the spirit of teamwork and is very worried about the success of the rebranding. Naturally, he can't wait to find out what is the new name the Corporation will receive.

Satisfy Arkady's curiosity and tell him the final version of the name.

## 说明/提示

In the second sample the name of the corporation consecutively changes as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/b0c9599f7e4282de011e545b3b2138ce054cf709.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/b503b89dff83c09912a9706615e9f382f03f5909.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/e277cc6136141b35244d23f5857e2b4088822639.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/cfe2461ca78ee24244102008b38c52289020e201.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/c06bdcdcec7417c4f543399c6c3d126f67ecf0a6.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/e46b37134536ad3b6c864840e66c2932fc25c838.png)

## 样例 #1

### 输入

```
6 1
police
p m
```

### 输出

```
molice
```

## 样例 #2

### 输入

```
11 6
abacabadaba
a b
b c
a d
e g
f a
b b
```

### 输出

```
cdcbcdcfcdc
```

# AI分析结果

### 题目内容翻译
## 重新品牌化

### 题目描述
一家规模虽小但充满自豪的公司的名称由 $n$ 个小写英文字母组成。该公司决定尝试重新品牌化——这是一种积极的营销策略，包括一系列改变品牌（公司及其生产的产品）或其组成部分（名称、标志、口号）的措施。他们决定从名称开始着手。

为此，公司陆续聘请了 $m$ 位设计师。每当公司聘请第 $i$ 位设计师时，他会立即为创建新的公司名称做出如下贡献：他会获取名称的最新版本，将所有字母 $x_{i}$ 替换为 $y_{i}$，并将所有字母 $y_{i}$ 替换为 $x_{i}$。这将产生一个新版本。可能某些字母在字符串中并未出现，也可能 $x_{i}$ 与 $y_{i}$ 相同。最后一位设计师工作完成后得到的名称版本将成为公司的新名称。

经理阿尔卡季最近在这家公司找到了一份工作，他已经充分融入了团队合作的氛围，并且非常担心品牌重塑的成功。自然地，他迫不及待地想知道公司最终会采用什么新名称。

满足阿尔卡季的好奇心，告诉他名称的最终版本。

### 说明/提示
在第二个样例中，公司名称的变化过程如下：

（此处为原题目中的图片链接，因无法直接展示图片，保留链接）

### 样例 #1
#### 输入
```
6 1
police
p m
```
#### 输出
```
molice
```

### 样例 #2
#### 输入
```
11 6
abacabadaba
a b
b c
a d
e g
f a
b b
```
#### 输出
```
cdcbcdcfcdc
```

### 综合分析与结论
#### 思路对比
- **暴力思路**：部分题解首先考虑暴力模拟，即每次操作都遍历整个字符串，将指定的两个字符进行交换。但由于数据范围 $1\leq n,m\leq200000$，这种方法的时间复杂度为 $O(nm)$，会超时。
- **优化思路**：大多数题解采用了优化方法，核心思路是记录每个字母经过若干次操作后最终变成的字符，最后再遍历初始字符串进行替换。这样可以将时间复杂度优化到 $O(n + m)$ 或 $O(26m)$。

#### 算法要点对比
- **数组存储**：使用数组存储每个字母的最终变化，如 `f1`、`tmp`、`geng` 等数组，通过交换数组元素来记录字母的替换关系。
- **映射存储**：使用 `map<char, char>` 存储字符的替换关系，如 `mp[i]` 表示字符 `i` 最终被替换成的字符。

#### 解决难点对比
- **暴力超时问题**：通过优化算法，避免每次操作都遍历字符串，从而解决暴力方法时间复杂度高的问题。
- **字母替换逻辑**：处理字母替换时，需要注意替换的顺序和最终结果，避免出现错误。例如，在交换字母时，不能简单地交换数组元素，需要考虑字母的实际替换关系。

### 所选题解
- **作者：qian_shang（5星）**
    - **关键亮点**：思路清晰，详细解释了优化的原因和方法，代码简洁易懂。通过创建数组存储每个字母的最终变化，将时间复杂度从 $O(nm)$ 优化到 $O(n + m)$。
    - **核心代码**：
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int n,m;
char f1[27],f2[27],s[200000],a,b;
int main()
{
    scanf("%d%d",&n,&m);
    scanf("%s",s);
    for(int i=0;i<26;i++)
        f1[i]=i+'a';
    while(m--)
    {
        scanf(" %c %c",&a,&b);
        swap(f1[a-'a'],f1[b-'a']);
    }
    for(int i=0;i<26;i++)
        f2[f1[i]-'a']=i+'a';
    for(int i=0;i<n;i++)
        printf("%c",f2[s[i]-'a']);
    return 0;
}
```
核心实现思想：首先初始化数组 `f1`，存储每个字母的初始状态。然后进行 $m$ 次操作，每次操作交换 `f1` 中对应字母的位置。最后，根据 `f1` 数组生成 `f2` 数组，用于存储每个字母最终变成的字符。遍历初始字符串，根据 `f2` 数组输出最终结果。

- **作者：wanggk（4星）**
    - **关键亮点**：思路清晰，详细说明了优化的过程和具体步骤，使用 `map<char, char>` 存储字符的替换关系，代码逻辑明确。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
char a,b;
string s;
map<char,char> mp;
int main()
{
    for(char i='a';i<='z';i++) mp[i]=i;
    cin>>n>>m;
    cin>>s;
    while(m--)
    {
        cin>>a>>b;
        for(char i='a';i<='z';i++)
        {
            if(mp[i]==a) mp[i]=b;
            else if(mp[i]==b) mp[i]=a;
        }
    }
    for(int i=0;i<s.size();i++) s[i]=mp[s[i]];
    cout<<s<<endl;
    return 0;
}
```
核心实现思想：首先初始化 `map`，将每个字符映射到自身。然后进行 $m$ 次操作，每次操作遍历所有字符，更新 `map` 中字符的映射关系。最后，遍历初始字符串，根据 `map` 替换每个字符。

- **作者：fish_gugu（4星）**
    - **关键亮点**：思路简洁，通过两个数组存储字母的变化，代码实现简单明了。
    - **核心代码**：
```cpp
#include <iostream>
#include <string>
using namespace std;
char a1[27],a2[27];
int main()
{
    int n,m;
    string s;
    char a,b;
    cin >> n >> m >> s;
    for(int i = 0;i < 26;i++) a1[i] = i + 97;
    for(int i = 0;i < m;i++)
    {
        cin >> a >> b;
        swap(a1[a - 97],a1[b - 97]);
    }
    for(int i = 0;i < 26;i++) a2[a1[i] - 97] = i + 97;
    for(int i = 0;i < n;i++) cout << a2[s[i] - 97];
    return 0;  
}
```
核心实现思想：首先初始化数组 `a1`，存储每个字母的初始状态。然后进行 $m$ 次操作，每次操作交换 `a1` 中对应字母的位置。最后，根据 `a1` 数组生成 `a2` 数组，用于存储每个字母最终变成的字符。遍历初始字符串，根据 `a2` 数组输出最终结果。

### 最优关键思路或技巧
- **延迟处理思想**：避免每次操作都对字符串进行修改，而是先记录所有操作，最后再统一处理，从而降低时间复杂度。
- **数组或映射存储**：使用数组或 `map` 存储每个字母的最终变化，方便后续替换。

### 可拓展之处
同类型题目可能会有更复杂的替换规则，如多个字母之间的循环替换、根据位置进行不同的替换等。类似的算法套路可以应用于字符串处理、字符替换、状态记录等问题。

### 推荐题目
- [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)：涉及状态记录和递推，与本题记录字母最终状态的思想类似。
- [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)：需要处理二维数组中的元素替换，可借鉴本题的延迟处理思想。
- [P1427 小鱼的数字游戏](https://www.luogu.com.cn/problem/P1427)：简单的数组操作和元素替换，适合巩固本题的基本思路。

### 个人心得摘录与总结
- **fish_gugu**：指出存变化的数组不能用 `string` 类型替代，因为 `swap` 处理不了 `string` 类型。总结：在使用 `swap` 函数时，需要注意数据类型的兼容性。

---
处理用时：47.34秒