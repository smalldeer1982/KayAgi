# 题目信息

# Sysadmin Bob

## 题目描述

Email address in Berland is a string of the form $ A $ @ $ B $ , where $ A $ and $ B $ are arbitrary strings consisting of small Latin letters.

Bob is a system administrator in «Bersoft» company. He keeps a list of email addresses of the company's staff. This list is as a large string, where all addresses are written in arbitrary order, separated by commas. The same address can be written more than once.

Suddenly, because of unknown reasons, all commas in Bob's list disappeared. Now Bob has a string, where all addresses are written one after another without any separators, and there is impossible to determine, where the boundaries between addresses are. Unfortunately, on the same day his chief asked him to bring the initial list of addresses. Now Bob wants to disjoin addresses in some valid way. Help him to do that.

## 样例 #1

### 输入

```
a@aa@a
```

### 输出

```
a@a,a@a
```

## 样例 #2

### 输入

```
a@a@a
```

### 输出

```
No solution
```

## 样例 #3

### 输入

```
@aa@a
```

### 输出

```
No solution
```

# AI分析结果

### 题目内容翻译
## Sysadmin Bob

### 题目描述
在 Berland，电子邮件地址的形式为 $A$ @ $B$，其中 $A$ 和 $B$ 是由小写拉丁字母组成的任意字符串。

Bob 是 “Bersoft” 公司的系统管理员。他保存着一份公司员工的电子邮件地址列表。这个列表是一个大字符串，所有地址以任意顺序书写，用逗号分隔。同一个地址可能会被多次书写。

突然，由于未知原因，Bob 列表中的所有逗号都消失了。现在 Bob 有一个字符串，所有地址一个接一个地写在一起，没有任何分隔符，因此无法确定地址之间的边界。不幸的是，同一天他的老板要求他提供初始的地址列表。现在 Bob 想以某种有效的方式拆分出地址。请帮助他完成这个任务。

### 样例 #1
#### 输入
```
a@aa@a
```
#### 输出
```
a@a,a@a
```

### 样例 #2
#### 输入
```
a@a@a
```
#### 输出
```
No solution
```

### 样例 #3
#### 输入
```
@aa@a
```
#### 输出
```
No solution
```

### 综合分析与结论
这些题解的核心思路都是先判断输入字符串能否分割成符合 `A@B` 形式的子串，若能则进行分割并输出，若不能则输出 `No solution`。

#### 思路对比
- **遍历判断法**：多数题解采用此方法，遍历字符串，检查是否存在不合法情况，如 `@` 在首尾、两个 `@` 间字符不足等。
- **贪心分割法**：如 Eason_AC 的题解，从后往前遍历，遇到 `@` 就将后面未使用的字符和当前 `@` 及前一个字符组成子串。

#### 算法要点
- **不合法情况判断**：检查 `@` 是否在首尾、字符串中是否有 `@`、两个 `@` 间字符数量是否足够。
- **分割方法**：在合法的情况下，选择合适的位置插入逗号进行分割，如在 `@` 后保留一个字母再分割。

#### 解决难点
- **特殊情况处理**：准确找出所有不合法的情况并进行判断。
- **分割位置确定**：选择合适的分割位置，同时要注意最后一个 `@` 后的处理。

### 所选题解
- **作者：zheysq_147（5星）**
    - **关键亮点**：思路清晰，详细阐述了每个步骤，对各种特殊情况的判断和处理都有详细说明，代码注释丰富，可读性强。
    - **个人心得**：作者一开始认为是水题，实际做题时发现有很多细节，做了3遍才 AC，提醒大家要注意细节。
    - **核心代码**：
```cpp
bool pd()
{
    if(s[1]=='@'||s[n]=='@'||last==-1)
        return 0;
    for(i=2;i<=n-1;++i)
    {
        if(s[i]=='@'&&s[i+1]=='@')
            return 0;
    }
    for(i=2;i<=n-2;++i)
    {
        if(s[i]=='@'&&s[i+2]=='@')
            return 0;
    }
    return 1;
}
void out()
{
    for(i=1;i<=n;++i)
    {
        if(s[i-2]=='@'&&i-2!=last)
            printf(",");
        printf("%c",s[i]);
    }
}
```
核心实现思想：`pd` 函数用于判断字符串是否合法，检查 `@` 的位置和相邻 `@` 的情况；`out` 函数用于输出分割后的字符串，在合适的位置插入逗号。

- **作者：皮卡丘最萌（4星）**
    - **关键亮点**：清晰列出了所有特殊情况，代码简洁，采用 Pascal 语言实现，逻辑清晰。
    - **核心代码**：
```pascal
procedure over;
begin
    writeln('No solution'); halt;
end;

begin
    readln(s);
    len:=length(s);
    if s[1]='@' then over;
    if s[len]='@' then over;
    if pos('@',s)=0 then over;    //判断前3种情况
    while pos('@',s)<>0 do
    begin
        k:=pos('@',s);              //查找@的位置
        if (s[k+1]<>'@')and((k+2>length(s))or(s[k+2]<>'@')) then    //判断是否有至少2个其他字符在两个@之间
            s1:=s1+copy(s,1,k+1)+',' else over;
        delete(s,1,k+1);          //删除此部分
    end;
    writeln(copy(s1,1,length(s1)-1)+s);   //输出答案
end.
```
核心实现思想：先判断特殊情况，若不合法则输出 `No solution`；然后不断查找 `@` 的位置，判断是否合法，若合法则进行分割，最后输出结果。

- **作者：Ace_Radom（4星）**
    - **关键亮点**：运用 STL 库中的成员函数，代码结构清晰，对思路和代码实现都有详细解释。
    - **核心代码**：
```cpp
bool Inspect( string s ){
    if ( s.find( '@' ) == string::npos )  //第一步筛查
    {
        return false;
    }
    int l = s.size();
    if ( s[0] == '@' || s[l-1] == '@' )  //第二部筛查
    {
        return false;
    }
    int k = 0,Sk = 0;
    // k 是当前筛到的 @ 字符的位置，Sk 是上一个 @ 字符的位置
    while ( s.find( '@', k + 1 )!= string::npos )  //如果后面还有
    {
        k = s.find( '@', k + 1 );
        if ( Sk == 0 )  //表明是第一个 @ 字符
        {
            Sk = k;
            continue;  //不用继续判断
        }
        if ( ( k - Sk <= 2 ) || ( s.find( '@', k + 1 ) - k <= 2 ) )  //第三部筛查
        {
            return false;
        }
    }
    return true;
}
void Work( string s ){
    int l = s.size();
    int k = 0;
    // k 这里指这个邮箱地址的起始位置
    for ( int i = 0 ; i < l ; i++ )
    {
        if ( s[i-1] == '@' )  //上一位是 @ 字符
        {
            if ( s.find( '@', i ) == string::npos )  //已经是最后一个 @ 字符了
            {
                for ( int j = k ; j < l ; j++ )  //直接输到最后
                {
                    cout << s[j];
                }
                cout << endl;
                return;
            }
            else  //普通输出
            {
                for ( int j = k ; j <= i ; j++ )
                {
                    cout << s[j];
                }
                cout << ",";  //不要忘了逗号
                k = i + 1;  //标记下一个邮箱地址的起始位置
            }
        }
    }
}
```
核心实现思想：`Inspect` 函数用于判断字符串是否合法，通过 `find` 函数查找 `@` 的位置并进行判断；`Work` 函数用于分割字符串，根据 `@` 的位置进行分割并输出。

### 最优关键思路或技巧
- **特殊情况判断**：全面考虑各种不合法情况，如 `@` 在首尾、两个 `@` 间字符不足等。
- **分割方法**：选择合适的分割位置，如在 `@` 后保留一个字母再分割，同时注意最后一个 `@` 后的处理。

### 拓展思路
同类型题可能会有不同的字符串分割规则，如分割成其他特定格式的子串，解题思路类似，先判断是否能分割，再进行分割。类似算法套路包括字符串遍历、特殊情况判断、分割位置确定等。

### 推荐洛谷题目
1. [P1055 ISBN 号码](https://www.luogu.com.cn/problem/P1055)：字符串处理，判断和计算 ISBN 号码的校验码。
2. [P1598 垂直柱状图](https://www.luogu.com.cn/problem/P1598)：字符串统计和输出，统计字符出现次数并输出垂直柱状图。
3. [P1200 [USACO1.1]你的飞碟在这儿 Your Ride Is Here](https://www.luogu.com.cn/problem/P1200)：字符串处理和计算，根据字符串计算数字并进行比较。

### 个人心得总结
- zheysq_147：一开始轻视题目，实际做题时发现细节很多，做了3遍才 AC，提醒大家做题要注意细节。
- Ace_Radom：做题时多次提交才通过，主要是因为没有考虑到字符串中不包含 `@` 的情况，提醒大家要全面考虑特殊情况。 

---
处理用时：46.14秒