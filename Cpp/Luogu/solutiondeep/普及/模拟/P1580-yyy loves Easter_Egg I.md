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

• **综合分析与结论**：这些题解均围绕字符串处理与模拟展开。思路上，先确定第一个人@的对象，再逐行读入后续发言并判断队形是否被破坏或（油）炸成功。算法要点包括字符串读取、提取名字、判断@个数及被@对象等操作。难点在于处理各种边界情况，如换行符、多个@、名字提取的边界等。多数题解通过自定义函数提取名字、判断@相关情况，部分使用scanf或sscanf格式化输入简化操作，还有题解用getchar逐字符读取。整体质量上，部分题解代码可读性欠佳，注释较少，部分未对关键操作详细说明。
• **所选的题解**：
  - **作者：ironwheel (赞：122)  星级：4星**
    - **关键亮点**：思路清晰，通过多个自定义函数实现不同功能，如`search`函数找名字，`kkk`函数判断@个数及位置，代码结构较为清晰。
    - **个人心得**：提醒注意特判换行符，否则可能出现WA。
    - **核心代码片段**：
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
核心实现思想：`search`函数从指定位置开始找名字，`find_name`调用`search`找发言人名字，`kkk`统计@个数并找位置，`wss`根据`kkk`结果找被@人的名字。
  - **作者：Deny_小田 (赞：21)  星级：4星**
    - **关键亮点**：代码简洁，使用`sscanf`进行字符串解析，通过注释详细解释每一步操作，增强代码可读性。
    - **个人心得**：朴素方法得分低，且因#4.in文件过大无法下载，影响朴素方法AC。
    - **核心代码片段**：
```cpp
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
核心实现思想：循环读入字符串，用`sscanf`获取发言人名字，判断是否与目标名字相同；同时判断@个数及被@人是否与目标一致，决定输出结果。
  - **作者：AFOier (赞：5)  星级：4星**
    - **关键亮点**：将功能模块化，通过`fname`、`fat`、`ats`等函数分别实现找发言人名字、找被@人名字、判断@个数功能，逻辑清晰。
    - **个人心得**：看清题目条件，注意@两个人算打破队形的情况。
    - **核心代码片段**：
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
while(getline(cin,a)){
    int ww=0;
    while(a[ww]==' ')ww++;
    if(ww==(a.size()-1))break;
    ans++;
    string p=fname(a),q=fat(a);
    if(p==at){
        cout<<"Successful @"<<at<<" attempt"<<endl;
        return 0;
    }
    if(q!=at||ats(a)!=1){
        cout<<"Unsuccessful @"<<at<<" attempt"<<endl;
        cout<<ans<<endl<<p<<endl;return 0;
    }
}
```
核心实现思想：`fname`函数找发言人名字，`fat`函数找被@人名字，`ats`判断@个数。循环读入字符串，根据函数结果判断轰炸是否成功或队形是否被破坏。
• **最优关键思路或技巧**：将复杂的字符串处理任务分解为多个子任务，通过自定义函数分别实现，如提取名字、判断@个数等，使代码逻辑更清晰。利用`sscanf`或`string`类的相关函数进行字符串解析，提高代码效率和简洁性。同时，要注意处理各种边界情况，如换行符、多个@等。
• **同类型题或类似算法套路**：此类题目属于字符串模拟类型，类似套路是先明确规则，再通过字符串读取、解析、判断等操作实现模拟过程。常需处理边界条件和特殊情况。
• **推荐题目**：
  - **P1055 ISBN号码**：涉及字符串的处理与校验，需对输入的ISBN号码按规则进行解析和判断。
  - **P1308 统计单词数**：考查字符串查找与统计，要在给定字符串中按要求查找特定单词并统计其出现次数。
  - **P1598 垂直柱状图**：通过对输入字符串的处理，统计不同字符出现次数并以特定格式输出，也是字符串处理与模拟的结合。
• **个人心得摘录总结**：部分作者提到看清题目条件的重要性，如@人数、名字格式、换行符等细节，稍不注意就会WA。还有作者分享了调试过程中遇到的问题，如换行符处理不当导致的错误，以及使用不同输入输出函数的注意事项等。 

---
处理用时：62.04秒