# 题目信息

# yyy loves Easter_Egg I

## 题目背景

Soha 的出题效率着实让人大吃一惊。OI，数学，化学的题目都出好了，物理的题还没有一道。于是，Huntfire，absi2011，redbag 对 soha 进行轮番炸，准备炸到 soha 出来，不料，人群中冲出了个 kkksc03……

## 题目描述

![](https://cdn.luogu.com.cn/upload/pic/1456.png)

![](https://cdn.luogu.com.cn/upload/pic/1455.png)

yyy loves OI（Huntfire），yyy loves Maths（redbag），yyy loves Chemistry（absi2011）对 yyy loves Physics（soha）进行轮番炸，轰炸按照顺序进行，顺序为 Huntfire，redbag，absi2011。

现在这一题中，我们不考虑太复杂的队形形式。我们认为只要这一句内含有且恰好含有一次@，@的人和上一句话一样就算为队形。

比如以下也视为队形：

- `yyy loves OI : @yyy loves Microelectronic`
- `yyy loves Maths : @yyy loves Microelectronic 我佩服soha的出题效率`
- `yyy loves OI : @yyy loves Microelectronic +1`
- `yyy loves Chemistry : +1 @yyy loves Microelectronic`

若 @ 的人与第一个人不同，就算队形被打破。若这个人在队形被打破之前出来发言了，或者就是他打破队形了，就算（油）炸成功了。

若（油）炸成功，输出 `Successful @某某某 attempt`，若队形被破坏先输出 `Unsuccessful @某某某 attempt`，再输出队形第一次被破坏的行数与第一次破坏队形的人的 $\text{id}$。

如果队形一直没被打破，就先输出 `Unsuccessful @某某某 attempt`，再输出队形的长度，最后输出 `Good Queue Shape`。

~~p.s.yyy loves Microelectronic 是 kkksc03~~



## 说明/提示

**@yyy loves Physics 我佩服你的出题效率**

此题仅吐槽 soha，纪念出题者的队形，此队形长达 $91$ 行。

对于 $100\%$ 的数据,每行消息长度 $\le$ $10^3$。 

- 保证行数不超过 $5\times 10^4$；
- 保证输入文件大小不超过 $4\text{MB}$；
- 保证第一个说话的一定在 @ 某人；
- 保证大家的名字都是 $\text{yyy loves ***}$ 的格式；
- 保证每个人说的话中没有 `:`；
- 保证第一个说话的一定艾特了一个人且只 @ 了一个人；
- 保证第一个说话的一定不会艾特自己；
- 保证文件结束一定有一行空行，方便你判定文件结束；
- 并不保证后面说话的艾特了几个人 然而艾特人数不为一个人视为破坏队形；
- 并不保证后面说话是否会反复艾特同一个人；
- 并不保证被炸的人一定破坏队形；
- 并不保证这一题是或不是压轴题；
- 并不保证这一套比赛存在压轴题；
- 并不保证下一套比赛和这一套比赛一样水；
- 并不保证群里除了这 $4$ 个人和 kkksc03 以外没有别人了；
- 并不保证你没 AC 这题的情况下吐槽 soha 不会出事儿；
- AC 了可以吐槽 soha 一句，soha 不会介意。

## 样例 #1

### 输入

```
yyy loves OI : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Maths : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Chemistry : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Microelectronic : ni men wu liao me 
yyy loves OI : @yyy loves Physics wo pei fu ni de chu ti xiao lv

```

### 输出

```
Unsuccessful @yyy loves Physics attempt
4
yyy loves Microelectronic
```

## 样例 #2

### 输入

```
yyy loves OI : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Maths : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Chemistry : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves OI : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Maths : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Chemistry : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves OI : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Maths : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Chemistry : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Physics : ni men gou le 

```

### 输出

```
Successful @yyy loves Physics attempt
```

# AI分析结果

### 综合分析与结论
这些题解均围绕字符串处理和模拟逻辑来解决问题。思路上，基本是读取每行输入，提取说话者名字和被@者名字，与第一个被@者名字对比，判断是否炸成功或队形被破坏。算法要点在于字符串的解析与比较，难点集中在处理各种边界情况，如换行符、@符号的个数及位置、名字的准确提取等。

从质量看，多数题解思路清晰、代码有注释，但部分代码实现稍显繁琐，优化程度有限。

### 所选的题解
- **作者：ironwheel (赞：122)  星级：4星**
    - **关键亮点**：代码模块化程度较高，通过多个函数分别实现名字提取、@符号及被@者名字查找等功能，逻辑清晰。
    - **个人心得**：提醒注意换行符的特判，否则可能出现WA。
    - **重点代码**：
```cpp
string search(string s,int l){
    string kk;
    int spacesum=0;
    for(register int i=l;s[i]!=' '&&i<s.size();i++){
        if(s[i]==' ') spacesum++;
        if(spacesum==3||s[i]==13) break;
        kk+=s[i];
    }
    return kk;
}
string find_name(string s){
    string a=search(s,10);
    return a;
}
int kkk(string q){
    int sum=0,gg;
    for(register int i=0;i<q.size();i++){
        if(q[i]=='@'){sum++;gg=i;}
    }
    if(sum!=1)return 0;
    else return gg;
}
string wss(string s){
    int g=kkk(s);
    if(g!=0)return search(s,g+11);
    else return "tenyearsatreehundredyearsatreeman";
}
```
核心实现思想：`search`函数从指定位置`l`开始找名字，`find_name`调用`search`获取说话者名字，`kkk`函数统计@符号个数并返回位置，`wss`调用`kkk`获取被@者名字。
- **作者：Deny_小田 (赞：21)  星级：4星**
    - **关键亮点**：代码简洁明了，使用`sscanf`函数进行字符串解析，对关键步骤有详细注释。
    - **个人心得**：吐槽朴素方法得分低，且#4.in文件过大无法下载影响朴素方法AC。
    - **重点代码**：
```cpp
gets(s);
sscanf(strstr(s, "@"), "@yyy loves %s", name);
while(c++){
    gets(s);
    int len = strlen(s);
    if(len == 1) break;
    sscanf(s, "yyy loves %s",importer);
    if(!strcmp(importer, name)){
        printf("Successful @yyy loves %s attempt\n",name);
        return 0;
    }
    if(count(s, s+len, '@')!= 1 || (sscanf(strstr(s, "@"), "@yyy loves %s", t), strcmp(t, name))){
        printf("Unsuccessful @yyy loves %s attempt\n", name);
        printf("%d\n", c);
        printf("yyy loves %s\n", importer);
        return 0;
    }
}
```
核心实现思想：先读入第一行获取被@者名字，循环读入后续行，用`sscanf`获取说话者名字和被@者名字，对比判断是否炸成功或队形被破坏。
- **作者：AFOier (赞：5)  星级：4星**
    - **关键亮点**：代码结构清晰，通过多个自定义函数分别完成找说话者名字、找被@者名字、统计@符号个数功能，逻辑连贯。
    - **个人心得**：强调看清题目条件，如@两个人算打破队形。
    - **重点代码**：
```cpp
string fname(string b){
    int w=0;string s="";
    while(b[w+1]!=':')w++;
    for(int i=0;i<w;i++)
    s+=b[i];
    return s;
}
string fat(string b){
    int w=0;
    while(b[w]!='@'&&w<b.size()-1)w++;
    if(w==b.size()-1)return "abcd";
    w++;
    string s="";
    while(b[w]!=' ')
    s+=b[w],w++;s+=' ';
    w++;
    while(b[w]!=' ')
    s+=b[w],w++;s+=' ';
    w++;
    while(b[w]!=' '&&w<b.size()-1)
    s+=b[w],w++;
    return s;
}
int ats(string pp){
    int ss=0;
    for(int i=0;i<pp.size();i++)
    if(pp[i]=='@')ss++;
    return ss;
}
```
核心实现思想：`fname`函数找说话者名字，`fat`函数找被@者名字，`ats`函数统计@符号个数，在`main`函数中利用这些函数判断是否炸成功或队形被破坏。

### 最优关键思路或技巧
- **字符串解析技巧**：利用`sscanf`、`strstr`等函数，或手动遍历字符串，根据固定格式“yyy loves ”及@符号位置来准确提取名字。
- **边界条件处理**：重视换行符、@符号个数、名字位置等边界情况，如将输入字符串最后一位处理为空格避免越界，统计@符号个数判断队形是否破坏。

### 可拓展之处
同类型题常涉及字符串匹配、模拟特定规则场景。类似算法套路为根据题目规则，对输入字符串进行解析、提取关键信息，再依据条件判断结果。例如处理文本格式数据、分析日志记录等场景。

### 相似知识点洛谷题目
- [P1055 ISBN号码](https://www.luogu.com.cn/problem/P1055)：涉及字符串处理与校验规则。
- [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)：字符串查找与统计。
- [P1598 垂直柱状图](https://www.luogu.com.cn/problem/P1598)：字符串处理与图形模拟。 

---
处理用时：55.81秒