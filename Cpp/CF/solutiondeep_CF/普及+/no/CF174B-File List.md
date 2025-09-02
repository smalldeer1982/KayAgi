# 题目信息

# File List

## 题目描述

Eudokimus, a system administrator is in trouble again. As a result of an error in some script, a list of names of very important files has been damaged. Since they were files in the BerFS file system, it is known that each file name has a form "name.ext", where:

- name is a string consisting of lowercase Latin letters, its length is from 1 to 8 characters;
- ext is a string consisting of lowercase Latin letters, its length is from 1 to 3 characters.

For example, "read.me", "example.txt" and "b.cpp" are valid file names and "version.info", "ntldr" and "contestdata.zip" are not.

Damage to the list meant that all the file names were recorded one after another, without any separators. So now Eudokimus has a single string.

Eudokimus needs to set everything right as soon as possible. He should divide the resulting string into parts so that each part would be a valid file name in BerFS. Since Eudokimus has already proved that he is not good at programming, help him. The resulting file list can contain the same file names.

## 样例 #1

### 输入

```
read.meexample.txtb.cpp
```

### 输出

```
YES
read.m
eexample.t
xtb.cpp
```

## 样例 #2

### 输入

```
version.infontldrcontestdata.zip
```

### 输出

```
NO
```

# AI分析结果

### 题目重写
# 文件列表
## 题目描述
系统管理员Eudokimus又陷入麻烦了。由于某个脚本中的错误，一份非常重要的文件名单被损坏了。因为这些文件都在BerFS文件系统中，所以已知每个文件名的格式为“name.ext”，其中：
- name是一个由小写拉丁字母组成的字符串，其长度在1到8个字符之间；
- ext是一个由小写拉丁字母组成的字符串，其长度在1到3个字符之间。

例如，“read.me”、“example.txt”和“b.cpp”是有效的文件名，而“version.info”、“ntldr”和“contestdata.zip”则不是。

文件名单的损坏意味着所有文件名都一个接一个地记录下来，没有任何分隔符。所以现在Eudokimus只有一个字符串。

Eudokimus需要尽快把一切恢复正常。他应该把得到的字符串分成若干部分，使每一部分都是BerFS中有效的文件名。由于Eudokimus已经证明了自己不擅长编程，所以请帮助他。生成的文件列表可以包含相同的文件名。
## 样例 #1
### 输入
```
read.meexample.txtb.cpp
```
### 输出
```
YES
read.m
eexample.t
xtb.cpp
```
## 样例 #2
### 输入
```
version.infontldrcontestdata.zip
```
### 输出
```
NO
```

### 算法分类
字符串、模拟

### 题解综合分析与结论
这几道题解的核心思路都是先判断给定字符串能否分割成符合要求的文件名，若能则进行分割输出。主要差异在于判断合法性的方式和分割的具体实现细节。各题解都考虑到了文件名各部分长度限制以及特殊情况如开头结尾为`.`、无`.`、连续`.`等。

### 所选的题解
- **作者：By_Ha (5星)**
    - **关键亮点**：思路清晰，代码注释详细，对判断函数和输出过程都有细致解释。通过记录两个`'.'`之间的字符数来判断合法性，逻辑简洁明了。
    - **个人心得**：强调模拟题要打草稿，否则容易出错。
    - **核心代码**：
```cpp
bool isOK() {
    int len = 0;
    int plc = 1;
    int i;
    for(i = 0; s[i]!='\0'; i++) {
        if(s[i] == '.') {
            if(plc == 1) {
                if(len == 0||len>8)
                    return false;
            } else if(len <=1 || len >= 12) {
                return false;
            }
            len = 0;
            plc ++;
            continue;
        }
        len ++;
    }
    return s[i-1]!= '.'&&(s[i-2]=='.'||s[i-3]=='.'||s[i-4]=='.');
}
```
核心思想：遍历字符串，遇到`'.'`时判断当前块（两个`'.'`之间）的长度是否符合要求，开头和中间部分长度限制不同，最后判断最后一块的长度是否合法。
```cpp
for(i = 0; s[i]!='\0'; i++) {
    if(s[i]=='.') {
        putchar(s[i]);
        for(j = 1; s[i+j]!='\0'; j++)
            if(s[i+j] == '.')
                break;
        j--;
        if(j>3)
            j = 3;
        else if(s[i+j+1]!='\0') j--;
        for(int k = 1; k<=j; k++) {
            if(!isalpha(s[i+k]))
                continue;
            putchar(s[i+k]);
        }
        i+=j;
        putchar('\n');
        continue;
    }
    putchar(s[i]);
}
```
核心思想：再次遍历字符串，遇到`'.'`时，确定其后部分的输出长度并输出，注意处理长度限制和为下一个文件名留字符等情况，非`'.'`字符直接输出。
- **作者：Eason_AC (4星)**
    - **关键亮点**：详细列举了做题过程中的坑点，对理解题意和避免错误很有帮助。分割策略明确，即扫到`'.'`时，尽量让后面字符进入`B`部分，但不抢光`A`部分字符。
    - **个人心得**：分享了做题时在不同测试点踩的坑，如分割后剩余字符合法性判断、`'.'`位置的各种特殊情况等。
    - **核心代码**：
```cpp
F(int, i, 0, (int)s.size() - 1) {
    tmp += s[i];
    if(s[i]!= '.') {
        {if(!flg) cnta++; else cntb++;}
        if(cnta == 8 &&!flg && i!= (int)s.size() - 1 && isalpha(s[i + 1])) {NO; return;}
        if(cntb && (cntb == 3 || (cntb < 3 && i!= (int)s.size() - 2 && isalpha(s[i + 1]) && s[i + 2] == '.'))) vec.push_back(tmp), cnta = cntb = flg = 0, tmp = "";
    } else {
        flg = fl = 1;
        if(s[i + 1] == '.' ||!cnta || (i!= (int)s.size() - 2 && isalpha(s[i + 1]) && s[i + 2] == '.') || i == (int)s.size() - 1) {NO; return;}
    }
}
```
核心思想：遍历字符串，根据是否为`'.'`字符更新`cnta`（`A`部分长度）和`cntb`（`B`部分长度），判断各种不合法情况，合法则将临时存储的字符串加入结果向量并重置相关变量。
```cpp
if(tmp!= "") {
    if(!flg ||!cntb) {NO; return;}
    vec.push_back(tmp);
}
YES;
F(int, i, 0, (int)vec.size() - 1) cout << vec[i] << endl;
```
核心思想：处理遍历结束后临时字符串中剩余字符，判断其合法性，合法则加入结果向量，最后输出结果。
- **作者：Allen123456hello (4星)**
    - **关键亮点**：先清晰地列举出所有不合法字符串的情况，再进行模拟输出。利用`vector`记录各部分长度，使代码结构较为清晰。
    - **个人心得**：分享了自己在判断无`'.'`字符串时踩的坑。
    - **核心代码**：
```cpp
for (int i=1,pre=1;i<=n+1;++i){
    if (s[i]=='.'||s[i]=='\0'){++cnt;len.push_back(i-pre);pre=i+1;}
}
if (cnt<2){NO;}
if (len.front()>8||len.back()>3||len.front()<1||len.back()<1){NO;}
for (int i=1;i<cnt-1;++i){
    if (len[i]<=1||len[i]>11){NO;}
}
```
核心思想：遍历字符串，记录每个`'.'`之间的长度并存入`vector`，然后判断`'.'`数量以及各部分长度是否符合要求，不符合则判定无解。
```cpp
for (int i=1;i<=len.front();++i){putchar(s[i]);}
pos=len.front();
for (int i=1;i<cnt-1;++i){
    ++pos;putchar('.');
    if (len[i]<=9){
        putchar(s[pos+1]);putchar('\n');
        for (int j=2;j<=len[i];++j){putchar(s[pos+j]);}
        pos+=len[i];
    }else{
        for (int j=1;j<=len[i];++j){if (len[i]-j+1==8){putchar('\n');}putchar(s[++pos]);}
    }
}
puts(s+n-len.back());
```
核心思想：按记录的长度进行输出，根据不同长度情况进行换行和字符输出处理，最后输出最后一部分。

### 最优关键思路或技巧
在处理这类字符串分割问题时，通过记录关键分隔符（如本题的`'.'`）之间的距离或字符数，来判断各部分是否符合长度要求，是一种有效的方法。在分割输出时，要充分考虑各种边界情况和长度限制，确保分割的合理性。

### 拓展思路
同类型题目通常围绕字符串的特定格式匹配与分割展开，类似套路包括先明确合法格式规则，然后遍历字符串，对特殊字符位置、各部分长度等进行判断，过程中记录关键信息以辅助后续处理。

### 洛谷推荐题目
- [P1055 ISBN号码](https://www.luogu.com.cn/problem/P1055)：涉及对特定格式字符串的校验和处理。
- [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)：需要对字符串进行按单词分割及统计等操作。
- [P2010 回文日期](https://www.luogu.com.cn/problem/P2010)：结合日期格式与回文判断，对字符串处理有一定要求。 

---
处理用时：84.55秒