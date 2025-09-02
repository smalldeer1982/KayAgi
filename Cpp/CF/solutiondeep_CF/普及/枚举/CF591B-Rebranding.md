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

### 题目内容中文重写
# 品牌重塑

## 题目描述
一家规模虽小但充满自豪的公司的名称由 $n$ 个小写英文字母组成。该公司决定尝试进行品牌重塑——这是一种积极的营销策略，包括一系列改变品牌（包括公司及其生产的产品）或其组成部分的措施，如名称、标志、口号等。他们决定从名称开始着手。

为此，公司陆续聘请了 $m$ 位设计师。每当公司聘请第 $i$ 位设计师时，他会立即为创建新的公司名称做出如下贡献：他会获取名称的最新版本，将所有的字母 $x_{i}$ 替换为 $y_{i}$，并将所有的字母 $y_{i}$ 替换为 $x_{i}$，从而得到一个新版本。可能某些字母在字符串中并未出现，也可能 $x_{i}$ 与 $y_{i}$ 相同。最后一位设计师完成工作后得到的名称版本将成为公司的新名称。

经理阿尔卡季最近在这家公司找到了一份工作，他已经完全融入了团队合作的氛围，并且非常担心品牌重塑的成功。自然地，他迫不及待地想知道公司最终会获得什么样的新名称。

满足阿尔卡季的好奇心，告诉他名称的最终版本。

## 说明/提示
在第二个样例中，公司的名称依次变化如下：
![图片链接](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/b0c9599f7e4282de011e545b3b2138ce054cf709.png)![图片链接](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/b503b89dff83c09912a9706615e9f382f03f5909.png)
![图片链接](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/e277cc6136141b35244d23f5857e2b4088822639.png)
![图片链接](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/cfe2461ca78ee24244102008b38c52289020e201.png)
![图片链接](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/c06bdcdcec7417c4f543399c6c3d126f67ecf0a6.png)
![图片链接](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/e46b37134536ad3b6c864840e66c2932fc25c838.png)

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

### 综合分析与结论
这些题解主要围绕如何优化对字符串进行多次字符交换操作的算法。暴力解法是每次操作都遍历整个字符串，时间复杂度为 $O(nm)$，在本题数据范围下会超时。

优化思路的核心在于记录每个字母最终的变化结果，避免每次操作都遍历字符串。具体实现方式有多种，如使用数组或 `map` 来存储字母的最终映射关系。

### 所选题解
- **作者：qian_shang（5星）**
    - **关键亮点**：思路清晰，详细解释了优化的原因，代码简洁高效，将时间复杂度从 $O(nm)$ 优化到 $O(n + m)$。
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
    - **核心实现思想**：先初始化一个数组 `f1` 存储每个字母最初的映射关系，然后根据每次操作交换 `f1` 中对应字母的映射，最后再根据 `f1` 生成最终的映射数组 `f2`，遍历原字符串并根据 `f2` 输出结果。

- **作者：wanggk（4星）**
    - **关键亮点**：思路清晰，使用 `map` 来存储字母的映射关系，代码逻辑明确。
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
    - **核心实现思想**：使用 `map` 存储每个字母的映射关系，初始时每个字母映射到自身。每次操作时，遍历所有字母，更新其映射关系。最后遍历原字符串，根据 `map` 替换每个字符。

- **作者：fish_gugu（4星）**
    - **关键亮点**：思路简洁，通过数组存储字母的变化，代码实现较为直观。
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
    - **核心实现思想**：使用数组 `a1` 存储每次操作后字母的映射关系，最后根据 `a1` 生成最终的映射数组 `a2`，遍历原字符串并根据 `a2` 输出结果。

### 最优关键思路或技巧
- **避免重复操作**：通过记录每个字母的最终变化，避免每次操作都遍历整个字符串，将时间复杂度从 $O(nm)$ 优化到 $O(n + m)$。
- **使用映射关系**：使用数组或 `map` 存储字母的映射关系，方便快速查找和更新。

### 拓展思路
同类型题目可能会有不同的字符替换规则，或者操作次数和字符串长度更大。类似的算法套路是先分析操作的特点，找出可以优化的点，通过记录最终状态来减少不必要的计算。

### 推荐题目
- [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
- [P1161 开灯](https://www.luogu.com.cn/problem/P1161)

### 个人心得摘录与总结
- **fish_gugu**：存变化的 `char a1[27],a2[27]` 这两个数组千万不能用 `string` 类型替代，因为 `swap` 处理不了 `string` 类型。总结：在使用 `swap` 函数时，要注意数据类型的兼容性。 

---
处理用时：44.39秒