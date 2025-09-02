# 题目信息

# Corporation Mail

## 题目描述

The Beroil corporation structure is hierarchical, that is it can be represented as a tree. Let's examine the presentation of this structure as follows:

- $ employee $ ::= $ name $ . | $ name $ : $ employee_{1} $ , $ employee_{2} $ , ... , $ employee_{k} $ .
- $ name $ ::= name of an employee

That is, the description of each employee consists of his name, a colon (:), the descriptions of all his subordinates separated by commas, and, finally, a dot. If an employee has no subordinates, then the colon is not present in his description.

For example, line MIKE:MAX.,ARTEM:MIKE..,DMITRY:DMITRY.,DMITRY... is the correct way of recording the structure of a corporation where the director MIKE has subordinates MAX, ARTEM and DMITRY. ARTEM has a subordinate whose name is MIKE, just as the name of his boss and two subordinates of DMITRY are called DMITRY, just like himself.

In the Beroil corporation every employee can only correspond with his subordinates, at that the subordinates are not necessarily direct. Let's call an uncomfortable situation the situation when a person whose name is $ s $ writes a letter to another person whose name is also $ s $ . In the example given above are two such pairs: a pair involving MIKE, and two pairs for DMITRY (a pair for each of his subordinates).

Your task is by the given structure of the corporation to find the number of uncomfortable pairs in it.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF56C/9868b26a06de68925d83118f98afdf9f4510a164.png)

## 样例 #1

### 输入

```
MIKE:MAX.,ARTEM:MIKE..,DMITRY:DMITRY.,DMITRY...
```

### 输出

```
3
```

## 样例 #2

### 输入

```
A:A..
```

### 输出

```
1
```

## 样例 #3

### 输入

```
A:C:C:C:C.....
```

### 输出

```
6
```

# AI分析结果

### 题目翻译
# 公司邮件

## 题目描述
Beroil 公司的结构是层级式的，也就是说它可以用一棵树来表示。让我们来看一下这种结构的表示方式：
- `employee` ::= `name` . | `name` : `employee₁` , `employee₂` , ... , `employeeₖ` .
- `name` ::= 员工的名字

也就是说，每个员工的描述由他的名字、一个冒号（:）、所有下属的描述（用逗号分隔），最后是一个点组成。如果一个员工没有下属，那么他的描述中就不会出现冒号。

例如，`MIKE:MAX.,ARTEM:MIKE..,DMITRY:DMITRY.,DMITRY...` 是记录公司结构的一种正确方式，其中经理 MIKE 有下属 MAX、ARTEM 和 DMITRY。ARTEM 有一个下属叫 MIKE，和他的老板名字一样，DMITRY 的两个下属也叫 DMITRY，和他自己的名字一样。

在 Beroil 公司，每个员工只能与他的下属通信，下属不一定是直接下属。我们把一个叫 `s` 的人给另一个也叫 `s` 的人写信的情况称为“不舒服的情况”。在上面的例子中，有两对这样的情况：一对涉及 MIKE，两对涉及 DMITRY（他的每个下属各一对）。

你的任务是根据给定的公司结构，找出其中不舒服的对数。

## 样例 #1
### 输入
```
MIKE:MAX.,ARTEM:MIKE..,DMITRY:DMITRY.,DMITRY...
```
### 输出
```
3
```

## 样例 #2
### 输入
```
A:A..
```
### 输出
```
1
```

## 样例 #3
### 输入
```
A:C:C:C:C.....
```
### 输出
```
6
```

### 算法分类
字符串

### 综合分析与结论
这些题解的思路基本一致，都是根据输入字符的不同（`.`, `,`, `:`）进行分类处理，通过模拟的方式来统计“不舒服情况”的数量。
- **思路**：以 `.`、`,`、`:` 三种字符来界定不同名字，遇到 `.` 时计算之前与其同名的人的个数，遇到 `,` 或 `:` 时增加人数，遇到其他字符则将其添加到当前名字中。
- **算法要点**：使用数组存储名字，通过循环遍历数组来比较名字是否相同。
- **解决难点**：正确处理输入字符，避免重复判断，同时要注意输入结束的条件。

### 题解评分
- Fr0sTy：4星。思路清晰，对可能出现的问题有详细说明，代码规范。
- _zzzzzzy_：3星。思路简洁，但没有对可能出现的问题进行说明。
- nanatsuhi：3星。思路简单明了，但代码注释较少。
- EthanC_：3星。思路正确，但输入方式可能会导致部分测试用例无法通过。
- Rosmarinus：3星。思路有一定创新性，但代码实现与其他题解类似。

### 所选题解
- Fr0sTy（4星）
  - 关键亮点：思路清晰，对可能出现的问题有详细说明，代码规范。
  - 个人心得：用 while 输入时，必须特判 EOF，不然样例一会 TLE，样例三会 RE。判断完这个 people 以后，必须将其删去，不然会重复判断。

### 重点代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int ans,people=1;
char c;
string names[1000005];
int main() {
    while(scanf("%c",&c)!=EOF) {
        if(c=='.') {
            for(int i=0;i<people;i++)
                if(names[people]==names[i])
                    ans++;
            names[people--]="";
        }
        else if(c==':'||c==',') people++;
        else names[people]=names[people]+c;
    }
    printf("%d",ans);
    return 0;
}
```
**核心实现思想**：通过不断读入字符，根据字符的不同进行分类处理。遇到 `.` 时，遍历之前的名字，统计同名的个数；遇到 `,` 或 `:` 时，增加人数；遇到其他字符时，将其添加到当前名字中。

### 最优关键思路或技巧
- 使用数组存储名字，方便比较和管理。
- 根据不同的字符进行分类处理，模拟公司结构的解析过程。
- 注意输入结束的条件，避免出现 TLE 或 RE 错误。

### 拓展思路
同类型题或类似算法套路：这类字符串模拟题通常需要根据特定的规则对输入进行解析和处理，关键在于准确把握规则并合理使用数据结构。可以通过练习更多的字符串处理题目来提高解决此类问题的能力。

### 推荐洛谷题目
- P1055 [NOIP2008 普及组] ISBN 号码
- P1200 [USACO1.1] 你的飞碟在这儿 Your Ride Is Here
- P1308 [NOIP2011 普及组] 统计单词数

---
处理用时：29.71秒