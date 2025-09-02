# 题目信息

# 次世代SNS

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-formula-2014-final/tasks/code_formula_2014_final_c

あなたは、とあるSNSを作ろうとしています。

このSNSでは、`@username`という形式で、特定のユーザーにメッセージを送ることが可能であり、$ 1 $ つの発言に複数のユーザーを指定することで、複数のユーザーに同時にメッセージを送ることが可能になります。

このSNSは、以下のようなルールに従っています。

- 書き込まれるメッセージは、半角小文字アルファベット、半角スペース、`@`のみを含む。
- 書き込まれたメッセージに`@`が含まれていた場合、`@`直後の、アルファベットのみで構成される文字列のうち、最も長い文字列をユーザー名として扱い、そのユーザーにメッセージを届ける。
- `@`の直後がアルファベットでなかった場合は無視する。
- 複数回同じユーザーが指定されても、メッセージは $ 1 $ 回届ければ良い。

あなたは、このシステムを実装するために、書き込まれたメッセージに対し、メッセージを届けるべきユーザーを列挙するプログラムを作りたいです。

メッセージを送るべきユーザーを全て出力しなさい。なお、ユーザーが複数いる場合は、辞書順で出力しなさい。

## 说明/提示

### Sample Explanation 1

`codeformula`さんへのメッセージです。半角スペースが挟まれているので、`why`以降をユーザー名として認識することはありません。 また、`@`を出力する必要はありません。

### Sample Explanation 2

`a`が何度も指定されていますが、一度だけ出力する必要があります。 また、ユーザ名は辞書順で出力する必要があります。

### Sample Explanation 3

メッセージを送るべきユーザーがいない場合、何も出力しないで構いません。

## 样例 #1

### 输入

```
@codeformula why is this contest so easy```

### 输出

```
codeformula```

## 样例 #2

### 输入

```
myon @@c @a @aba@a @@bb bbb @@@@@ @a test  @ space  aaa test @a@a  test@takoyaki```

### 输出

```
a

aba

bb

c

takoyaki```

## 样例 #3

### 输入

```
no atmark```

### 输出

```
```

# AI分析结果

### 题目内容重写（中文）

你正在开发一个次世代SNS。这个SNS允许用户通过`@username`的形式向特定用户发送消息，并且可以在一条消息中指定多个用户，从而同时向多个用户发送消息。

该SNS遵循以下规则：

- 消息内容仅包含小写字母、空格和`@`。
- 如果消息中包含`@`，则`@`后紧接的由字母组成的最长字符串被视为用户名，并向该用户发送消息。
- 如果`@`后紧接的不是字母，则忽略该`@`。
- 即使多次指定同一用户，消息也只需发送一次。

你需要编写一个程序，根据给定的消息，列出所有需要发送消息的用户。如果有多个用户，按字典序输出。

### 样例解释

#### 样例1
输入：
```
@codeformula why is this contest so easy
```
输出：
```
codeformula
```
解释：`codeformula`是唯一的用户名。

#### 样例2
输入：
```
myon @@c @a @aba@a @@bb bbb @@@@@ @a test  @ space  aaa test @a@a  test@takoyaki
```
输出：
```
a
aba
bb
c
takoyaki
```
解释：`a`被多次指定，但只需输出一次。用户名按字典序排列。

#### 样例3
输入：
```
no atmark
```
输出：
```
```
解释：消息中没有`@`，因此没有需要发送消息的用户。

### 算法分类
字符串、模拟

### 题解分析与结论

#### 题解1：Wy_x
- **星级**：4星
- **关键亮点**：
  - 使用`cin`逐个读取单词，避免处理空格的麻烦。
  - 使用`find`和`substr`函数提取用户名。
  - 通过循环和标记处理多个`@`的情况。
  - 使用数组存储用户名，最后进行排序和去重。
- **个人心得**：作者强调了AT题目需要换行的细节，并提供了关于`cin`和`scanf`的读入失败处理方式。

#### 题解2：CZQ_King
- **星级**：4星
- **关键亮点**：
  - 使用`getline`读取整行消息，避免遗漏空格。
  - 使用`set`自动去重和排序，简化代码。
  - 通过`isalpha`函数判断`@`后是否为字母。
- **个人心得**：作者提到使用`set`可以简化排序和去重的操作，并强调了`getline`的使用。

### 最优关键思路与技巧
- **使用`set`自动去重和排序**：`set`数据结构可以自动处理重复元素，并且按字典序排列，简化了代码实现。
- **逐字处理与标记**：通过逐字处理消息，结合标记位，可以有效提取用户名并处理多个`@`的情况。
- **使用`getline`读取整行消息**：避免遗漏空格，确保消息的完整性。

### 可拓展之处
- **类似题目**：处理字符串中的特定模式（如`@username`）并提取相关信息，可以应用于其他文本处理场景。
- **数据结构应用**：`set`的使用可以推广到其他需要去重和排序的场景。

### 推荐题目
1. [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)
2. [P1553 数字反转](https://www.luogu.com.cn/problem/P1553)
3. [P1598 垂直柱状图](https://www.luogu.com.cn/problem/P1598)

### 核心代码片段
#### 题解1：Wy_x
```cpp
while(cin>>s)
{
    int nw1=s.find('@'),flag=0;
    while(nw1!=-1)
    {
        int nw2=s.find('@',nw1+1);
        if(nw2==-1)
        {
            nw2=s.size();
            flag=1;
        }
        string wait=s.substr(nw1+1,nw2-(nw1+1));
        tot++;
        ans[tot]=wait;
        if(wait.size()==0) tot--;
        for(int i=1;i<=tot-1;i++)
        {
            if(ans[i]==wait)
            {
                tot--;
                break;
            }
        }
        if(flag) break;
        nw1=nw2;
    }
}
sort(ans+1,ans+tot+1);
for(int i=1;i<=tot;i++)
{
    if(ans[i].size()!=0) cout<<ans[i]<<endl;
}
```

#### 题解2：CZQ_King
```cpp
getline(cin,s);
for(int i=0;i<s.length();i++)
{
    if(s[i]=='@'&&isalpha(s[i+1])&&i!=s.length()-1)
    {
        i++;
        while(i<s.length()&&isalpha(s[i])) v+=s[i++];
        a.insert(v);
        v.clear();
        i--;
    }
}
for(set<string>::iterator it=a.begin();it!=a.end();++it) cout<<*it<<endl;
```

---
处理用时：33.03秒