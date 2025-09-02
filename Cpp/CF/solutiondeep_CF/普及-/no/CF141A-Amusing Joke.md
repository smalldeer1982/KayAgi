# 题目信息

# Amusing Joke

## 题目描述

So, the New Year holidays are over. Santa Claus and his colleagues can take a rest and have guests at last. When two "New Year and Christmas Men" meet, thear assistants cut out of cardboard the letters from the guest's name and the host's name in honor of this event. Then the hung the letters above the main entrance. One night, when everyone went to bed, someone took all the letters of our characters' names. Then he may have shuffled the letters and put them in one pile in front of the door.

The next morning it was impossible to find the culprit who had made the disorder. But everybody wondered whether it is possible to restore the names of the host and his guests from the letters lying at the door? That is, we need to verify that there are no extra letters, and that nobody will need to cut more letters.

Help the "New Year and Christmas Men" and their friends to cope with this problem. You are given both inscriptions that hung over the front door the previous night, and a pile of letters that were found at the front door next morning.

## 说明/提示

In the first sample the letters written in the last line can be used to write the names and there won't be any extra letters left.

In the second sample letter "P" is missing from the pile and there's an extra letter "L".

In the third sample there's an extra letter "L".

## 样例 #1

### 输入

```
SANTACLAUS
DEDMOROZ
SANTAMOROZDEDCLAUS
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
PAPAINOEL
JOULUPUKKI
JOULNAPAOILELUPUKKI
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
BABBONATALE
FATHERCHRISTMAS
BABCHRISTMASBONATALLEFATHER
```

### 输出

```
NO
```

# AI分析结果

### 题目内容
# 有趣的笑话

## 题目描述
新年假期结束了。圣诞老人和他的伙伴们终于可以休息一下，并且招待客人了。当两位“新年与圣诞老人”见面时，他们的助手会为纪念这个时刻，从纸板上剪下客人名字和主人名字的字母。然后把这些字母挂在正门上方。一天晚上，当所有人都上床睡觉后，有人拿走了这两位角色名字的所有字母。接着，他可能把这些字母打乱顺序，然后在门前堆成一堆。

第二天早上，无法找到制造混乱的罪魁祸首。但是每个人都想知道，是否有可能从门前的这堆字母中恢复出主人和客人的名字呢？也就是说，我们需要确认没有多余的字母，并且也不需要再剪更多的字母。

帮助“新年与圣诞老人们”及其朋友们解决这个问题。题目会给出前一晚挂在正门上方的两个名字，以及第二天早上在正门发现的一堆字母。

## 说明/提示
在第一个样例中，最后一行给出的字母可以用来组成名字，并且不会有多余的字母。

在第二个样例中，这堆字母里缺少字母“P”，并且多了一个字母“L”。

在第三个样例中，多了一个字母“L”。

## 样例 #1
### 输入
```
SANTACLAUS
DEDMOROZ
SANTAMOROZDEDCLAUS
```
### 输出
```
YES
```

## 样例 #2
### 输入
```
PAPAINOEL
JOULUPUKKI
JOULNAPAOILELUPUKKI
```
### 输出
```
NO
```

## 样例 #3
### 输入
```
BABBONATALE
FATHERCHRISTMAS
BABCHRISTMASBONATALLEFATHER
```
### 输出
```
NO
```

### 算法分类
字符串

### 综合分析与结论
这些题解的核心思路都是判断前两个字符串中的字母种类和数量，与第三个字符串是否一致。主要有两种实现方式：一种是使用数组统计每个字符出现的次数，再进行比较；另一种是将前两个字符串拼接后与第三个字符串一起排序，然后比较排序后的字符串是否相等。
- **统计字符次数法**：定义数组记录字符出现次数，遍历前两个字符串，将对应字符的计数增加，遍历第三个字符串，将对应字符的计数增加或减少，最后检查数组中每个元素是否相等或为0，相等或全为0则输出YES，否则输出NO。
- **排序比较法**：把前两个字符串拼接起来，与第三个字符串分别进行排序，若排序后的两个字符串相等，则输出YES，否则输出NO。

### 所选的题解
- **作者：Tune_ (5星)**
  - **关键亮点**：思路清晰简洁，代码直接明了。使用两个数组作为桶，分别统计拼接前两个字符串和第三个字符串中每个字符的个数，最后对比两个桶中各字母数量是否相同。
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[30],b[30];
int main()
{
    string s1,s2,s3;
    cin>>s1>>s2>>s3;
    for(int i=0;i<s1.size();i++)a[s1[i]-64]++;//放进桶
    for(int i=0;i<s2.size();i++)a[s2[i]-64]++;
    for(int i=0;i<s3.size();i++)b[s3[i]-64]++;
    for(int i=1;i<=26;i++)//判断是否数量相同
    {
        if(a[i]!=b[i])
        {
            cout<<"NO";//直接输出，结束
            return 0;
        }
    }
    cout<<"YES";//没毛病
    return 0;//拜了个拜
}
```
  - **核心实现思想**：通过遍历字符串，将每个字符对应到数组下标并增加计数，最后遍历数组比较对应下标的计数是否相同。
- **作者：hensier (4星)**
  - **关键亮点**：同样采用统计字符次数的方法，代码注释详细，且还给出了Python的实现思路。
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b,c;
int letter1[26],letter2[26];//letter1保存a,b中的字母，letter2保存c中的
int main()
{
    cin>>a>>b>>c;
    for(int i=0;a[i];i++)letter1[a[i]-'A']++;
    for(int i=0;b[i];i++)letter1[b[i]-'A']++;
    for(int i=0;c[i];i++)letter2[c[i]-'A']++;
    for(int i=0;i<26;i++)
    {
        if(letter1[i]!=letter2[i])//一个元素不同就输出NO
        {
            printf("NO");
            return 0;
        }
    }
    printf("YES");
    return 0;
}
```
  - **核心实现思想**：利用数组记录不同字符串中各字母出现次数，遍历结束后比较两个数组对应位置元素是否相等。
- **作者：小豆子范德萨 (4星)**
  - **关键亮点**：采用排序比较的方法，代码简洁高效，利用了排序的特性来解决问题。
  - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s1,s2,s3;
    cin>>s1>>s2>>s3;
    string t = s1+s2;
    sort(t.begin(),t.end());
    sort(s3.begin(),s3.end());
    if(s3==t) printf("YES\n");
    else printf("NO\n");
    return 0;
}
```
  - **核心实现思想**：先将前两个字符串拼接，然后与第三个字符串分别排序，通过比较排序后的字符串判断是否由相同字母组成。

### 最优关键思路或技巧
- **字符统计数组**：利用数组下标与字符的对应关系，统计每个字符出现的次数，简单直观，适用于多种字符串比较场景。
- **排序比较**：通过排序将无序的字符串转化为有序，方便比较，减少了逐个字符匹配的复杂性。

### 拓展
同类型题目通常围绕字符串的组成、字符数量关系展开。类似算法套路是在处理字符串元素关系时，可考虑统计字符出现次数或者对字符串排序后进行比较。

### 洛谷相似题目推荐
- [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)：统计一个单词在给定字符串中出现的次数，涉及字符串查找与计数。
- [P1598 垂直柱状图](https://www.luogu.com.cn/problem/P1598)：统计多个字符串中每个字符出现次数并以柱状图形式输出，需对字符串字符进行统计处理。
- [P2219 [HAOI2007] 紧急疏散 EVACUATE](https://www.luogu.com.cn/problem/P2219)：虽然涉及图论与搜索，但其中对地图字符串的处理，需要统计特定字符数量等操作，与本题统计字符思路有相似之处。 

---
处理用时：57.64秒