# 题目信息

# War of the Corporations

## 题目描述

A long time ago, in a galaxy far far away two giant IT-corporations Pineapple and Gogol continue their fierce competition. Crucial moment is just around the corner: Gogol is ready to release it's new tablet Lastus 3000.

This new device is equipped with specially designed artificial intelligence (AI). Employees of Pineapple did their best to postpone the release of Lastus 3000 as long as possible. Finally, they found out, that the name of the new artificial intelligence is similar to the name of the phone, that Pineapple released 200 years ago. As all rights on its name belong to Pineapple, they stand on changing the name of Gogol's artificial intelligence.

Pineapple insists, that the name of their phone occurs in the name of AI as a substring. Because the name of technology was already printed on all devices, the Gogol's director decided to replace some characters in AI name with "\#". As this operation is pretty expensive, you should find the minimum number of characters to replace with "\#", such that the name of AI doesn't contain the name of the phone as a substring.

Substring is a continuous subsequence of a string.

## 说明/提示

In the first sample AI's name may be replaced with "int#llect".

In the second sample Gogol can just keep things as they are.

In the third sample one of the new possible names of AI may be "s#ris#ri".

## 样例 #1

### 输入

```
intellect
tell
```

### 输出

```
1```

## 样例 #2

### 输入

```
google
apple
```

### 输出

```
0```

## 样例 #3

### 输入

```
sirisiri
sir
```

### 输出

```
2```

# AI分析结果

### 题目翻译
# 公司之战

## 题目描述
很久以前，在一个遥远的星系中，两家巨型 IT 公司 Pineapple 和 Gogol 仍在进行激烈的竞争。关键时刻即将到来：Gogol 准备发布其新款平板电脑 Lastus 3000。

这款新设备配备了专门设计的人工智能（AI）。Pineapple 的员工竭尽全力尽可能推迟 Lastus 3000 的发布。最终，他们发现新人工智能的名称与 Pineapple 200 年前发布的一款手机的名称相似。由于该名称的所有权利都归 Pineapple 所有，他们坚持要求更改 Gogol 人工智能的名称。

Pineapple 坚称他们手机的名称作为子串出现在了人工智能的名称中。由于技术名称已经印在了所有设备上，Gogol 的主管决定将人工智能名称中的一些字符替换为“#”。由于此操作成本相当高，你需要找到将字符替换为“#”的最小数量，以使人工智能的名称中不包含手机的名称作为子串。

子串是字符串的连续子序列。

## 说明/提示
在第一个样例中，人工智能的名称可以替换为“int#llect”。

在第二个样例中，Gogol 可以保持原样。

在第三个样例中，人工智能的一个新可能名称可以是“s#ris#ri”。

## 样例 #1
### 输入
```
intellect
tell
```
### 输出
```
1
```

## 样例 #2
### 输入
```
google
apple
```
### 输出
```
0
```

## 样例 #3
### 输入
```
sirisiri
sir
```
### 输出
```
2
```

### 算法分类
字符串

### 综合分析与结论
这些题解主要围绕在一个长字符串中查找子字符串并统计其出现次数，或通过替换字符来消除子字符串的问题。不同题解采用了不同的实现方式，包括手动遍历匹配、使用 `substr` 函数、利用 Python 的 `count` 方法等。主要难点在于处理子字符串的重叠问题，避免重复计数。

### 题解评分与亮点
- **cqbztz2（3星）**：思路清晰，通过手动遍历匹配子字符串，但代码存在逻辑问题，最后多了一个不必要的判断 `if(j==len2)`。
- **Buried_Dream（3星）**：使用 `substr` 函数截取子字符串进行比较，思路简洁，但代码中变量 `a` 和 `b` 未定义。
- **BearBig（3星）**：使用 Python 的 `count` 方法，代码简洁，但未考虑子字符串重叠问题，且题目要求是替换字符消除子字符串，该方法不符合题意。
- **yzx72424（3星）**：采用模拟加贪心的思路，每次找到子字符串就替换最后一个字符，但未考虑子字符串重叠问题。
- **yinhy09（4星）**：使用 `flag` 数组标记已处理的位置，避免子字符串重叠问题，思路清晰，代码可读性较高。
- **hyc1026（3星）**：Python 代码使用 `count` 方法不符合题意，C++ 代码通过将匹配到的字符置为空格避免重复计算，但逻辑不够严谨。

### 所选题解
- **yinhy09（4星）**：
  - 关键亮点：使用 `flag` 数组标记已处理的位置，避免子字符串重叠问题，思路清晰，代码可读性较高。
  - 核心代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    string a,b;
    cin>>a>>b;
    int lena=a.length();
    int lenb=b.length();
    int ans=0;
    int pre=0;
    bool flag[1000005];
    memset(flag,0,sizeof(flag));
    for(int i=0;i<=lena-lenb;i++)
    {
        pre=0;
        for(int j=0;j<lenb;j++)
        {
            if(a[i+j]!=b[j])//不相同，直接跳出
            {
                break;
            }
            if(a[i+j]==b[j]&&flag[i+j]==0)
            {
                pre++;//记录有多少位相同
            }
            else 
            {	
                continue;
            }
        }
        if(pre==lenb)//完全相同的子串
        {
            for(int k=i;k<=i+lenb-1;k++) flag[k]=1;//相应位赋成1
            ans++;
        }
    }
    cout<<ans;
    return 0;
}
```

### 最优关键思路或技巧
使用标记数组（如 `flag` 数组）标记已处理的位置，避免子字符串重叠问题，确保每个子字符串只被处理一次。

### 拓展思路
同类型题可能会有更多的限制条件，如要求替换的字符必须是特定的字符，或者有替换次数的上限等。类似算法套路可以应用在字符串匹配、文本处理等领域，如在一篇文章中查找特定的单词并进行替换。

### 推荐题目
- [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)：字符串去重问题。
- [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)：字符串处理与贪心算法结合的问题。
- [P1061  Jam的计数法](https://www.luogu.com.cn/problem/P1061)：字符串的排列组合问题。

### 个人心得
- **yinhy09**：通过举例 `ttttt` 和 `ttt` 说明没有 `flag` 数组会导致错误，强调了处理子字符串重叠问题的重要性。 

---
处理用时：35.19秒