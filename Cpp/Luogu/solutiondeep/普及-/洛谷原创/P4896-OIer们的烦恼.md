# 题目信息

# OIer们的烦恼

## 题目背景

OIer 们有一个烦恼，他们本来可以随心所欲玩游戏上网的，自从学校机房开启 URL 过滤后，OIer 们就开始在 luogu上 面找游戏玩。

但是他们刚玩 slay.one 几天之后 slay.one 就被封禁了，只有工作日的中午 2 小时可以嗨皮，并且会有帅气的老师来巡视机房，他们该怎么办呢？

## 题目描述

有 3 个帅气的老师 $A$，$B$ 和 $C$。

有 5 个学生 $a$，$b$，$c$，$d$，$e$。当他们当中的某一个人开始玩游戏时，会显示一条消息 `XX started playing games!`。当他们当中的某一个人停止玩游戏时，会显示一条消息 `XX stopped playing games!`。

当某个老师来巡视机房时，会显示一条消息：`XX came!`。如果某个老师走了，会显示一条消息：`XX left!`。

如果老师发现某个学生**正在**玩游戏时，请输出该学生的姓名。

## 说明/提示

对于 $20\%$ 的数据，$1\leq N\leq 23.3333333333333$          
对于 $30\%$ 的数据，$1\leq N\leq 999.999$，有一个点答案为 `How Good Oiers Are!`。         
对于 $60\%$ 的数据，$1\leq N\leq 100,000$。    
对于$99.9999999999999999999\%$的数据，不保证全部消息都符合题意。           
对于 $100\%$ 的数据，$1\leq N\leq 233,333$，数据有梯度。
 
### Tips:
1.消息中肯定有奇奇怪怪的东西  
2.消息必须**完全符合题意**才有效  
3.样例很恶心，数据很纯真   
4.数据满足不会同时有多个**老师**巡视。     
5.注意仔细阅读**题目**和**样例**，**该题有坑！**      

## 样例 #1

### 输入

```
10
A B C
a b c d e
A came!
a started playing games!
b started playing games!
A left!
c started playing games!
d started playing games!
e started playing games!
B came!
PS:zhe_ge_yang_li_hen_zheng_chang!
B left!```

### 输出

```
a b c d e
How Bad Oiers Are!```

## 样例 #2

### 输入

```
10
I_Love_You I_Hate_You Why_Not_love_Me
Gay Che_Wan_Dang QwQ WuMaRu PDD
I_Love_You came!
Gay:Why do you love me?
I_Love_You died!
I_Love_You left!
Che_Wan_Dang prepared to play Dong_Fang!
But nobody came!
QwQ:I am so QwQ,I love myself!
PDD started playing Gay!
Gay died!And WuMaRu cried!
WuMaRu:dai su ki!```

### 输出

```
How Good Oiers Are!```

## 样例 #3

### 输入

```
20
Sans QwQ QAQ
A B C D E
A started playing B!
B started fighting with A!
A won!
A get 10000000 Exp!
QwQ:I and QAQ are looking at you all!
C died!
D died!
E recovered 123456789 HP!
E started playing games!
Sans came!
Sans:It is really a nice day today!
Sans:The birds are singing!
Sans:The flowers in bloom!
Sans:In a beautiful day like this!
Sans:People like you!
Sans:Should burn in hell!
E tried to attack Sans!
Sans was killed!
Sans:Papyrus,do you want something?
E still played his Undertale!```

### 输出

```
E```

## 样例 #4

### 输入

```
20
a b c
A B C D E
A came!
a started playing games!
b came!
b came together!
b came! dan_shi_zhe_ju_hua_bu_dui!
A came came came!
b start playing games!
b left!
c came!
c left!
A left!
B started playing games!
A started playing game!
C started palying games!
E started playing games!
lu_ren_jia came!
lu_ren_jia:What are you doing?
C&D:We are studying!
lu_ren_jia:Good boy!
C:qwq```

### 输出

```
How Good Oiers Are!```

# AI分析结果

• 综合分析与结论：这些题解均围绕模拟题展开，思路核心是根据输入消息，判断老师与学生的行为状态，进而确定被抓学生。算法要点在于准确识别各类消息，记录老师与学生状态。难点主要是处理字符串匹配及避免输入输出的细节问题。不同题解在实现方式上各有差异，如字符串处理手段、状态记录方式等。
• 所选的题解：
  - 作者：⑨baka (4星)
    - 关键亮点：思路清晰，代码简洁。利用cin以空格为结束符判断名字，gets以回车为结束符读取整行，巧妙避免对getline多出来空格的判断；通过字符数组定义固定消息，利用strcmp函数判断字符串是否相同，按题意模拟各状态变化。
    - 个人心得：调试耗费较多时间，如测试数据3较奇怪，同时提到可用string.erase解决但未掌握。
    - 重点代码核心实现思想：通过cin和gets分别读取名字和消息行，利用strcmp函数判断消息类型并更新对应状态，老师在场时检查学生游戏状态并记录被抓学生，最后按要求输出。
```cpp
// 关键代码片段
for(int i=1;i<=n;++i)
{
    cin>>s; 
    gets(s1); 
    for(int j=1;j<=3;++j)
        if(s==teacher[j])
        {
            if(!strcmp(s1,come)) comes=1;
            if(!strcmp(s1,l)) comes=0;
        }
    for(int j=1;j<=5;++j)
        if(s==stu[j])
        {
            if(!strcmp(s1,stop_play)) play[j]=0; 
            if(!strcmp(s1,start_play)) play[j]=1;
        }
    if(comes==1) 
    {
        for(int j=1;j<=5;++j)
            if(play[j] &&!a[j])
            {
                ++len;
                a[j]=1; 
            }
    }
    if(len==5) break;
}
```
  - 作者：Alarm5854 (4星)
    - 关键亮点：采用set容器存储老师和学生相关信息，利用find函数查找名字，自动处理元素去重与排序，时间复杂度低。代码结构清晰，各功能模块化，可读性强。
    - 个人心得：因函数少加取地址符调试20分钟，5分钟被在线IDE迷惑，最终以较好成绩AC本题。
    - 重点代码核心实现思想：通过finds函数查找名字，check函数判断身份并更新对应set容器，老师在场且有学生玩游戏时，将学生加入被抓集合，最后根据被抓集合输出结果。
```cpp
// 关键代码片段
bool finds(string &name,string &s)
{
    bool f=0;
    if(!s.find(A,0)) name=A,f=1;
    if(!s.find(B,0)) name=B,f=1;
    if(!s.find(C,0)) name=C,f=1;
    if(!s.find(a,0)) name=a,f=1;
    if(!s.find(b,0)) name=b,f=1;
    if(!s.find(c,0)) name=c,f=1;
    if(!s.find(d,0)) name=d,f=1;
    if(!s.find(e,0)) name=e,f=1;
    return f;
}
void check(string &name,string &s)
{
    if(name==A||name==B||name==C)
    {
        if(s==name+" came!") come.insert(name);
        else if(s==name+" left!") come.erase(name);
    }
    else if(name==a||name==b||name==c||name==d||name==e)
    {
        if(s==name+" started playing games!") playing.insert(name);
        else if(s==name+" stopped playing games!") playing.erase(name);
    }
}
while(n--)
{
    getline(cin,s);
    if(finds(name,s))
        check(name,s);
    if(come.size()&&playing.size())
        for(se it=playing.begin();it!=playing.end();it++)
            catched.insert(*it);
}
```
  - 作者：yu__xuan (4星)
    - 关键亮点：代码注释详细，逻辑清晰易懂。通过多个数组分别记录老师、学生状态，利用string拼接构造消息字符串进行判断，最后按要求输出结果。
    - 重点代码核心实现思想：读入数据后，通过getline读取每行消息，分别枚举学生和老师，根据拼接后的消息字符串判断行为并更新对应状态，被抓学生记录到数组中，最后排序并按条件输出。
```cpp
// 关键代码片段
for(int i=1;i<=n;++i) {
    getline(std::cin,s);
    for(int j=1;j<=5;++j) {
        if(dead[j]) continue;
        std::string qwq=b[j]+" started playing games!";
        if(qwq==s) playing[j]=true;
        qwq=b[j]+" stopped playing games!";
        if(qwq==s) playing[j]=false;
        if(playing[j]) {
            for(int k=1;k<=3;++k) {
                if(at[k]) {
                    dead[j]=1;playing[j]=0;
                    ans[++cnt]=b[j];
                    break;
                }
            }
        }
    }
    for(int j=1;j<=3;++j) {
        std::string qwq=a[j]+" came!";
        if(qwq==s) at[j]=true;
        qwq=a[j]+" left!";
        if(qwq==s) at[j]=false;
        if(at[j]) {
            for(int k=1;k<=5;++k) {
                if(playing[k]&&!dead[k]) {
                    dead[k]=1;
                    playing[k]=0;
                    ans[++cnt]=b[k];
                }
            }
        }
    }
}
std::sort(ans+1,ans+cnt+1);
if(cnt==0) printf("How Good Oiers Are!\n");
for(int i=1;i<=cnt;++i) std::cout<<ans[i]<<" ";
puts("");
if(cnt==5) printf("How Bad Oiers Are!\n");
```
• 最优关键思路或技巧：利用合适的数据结构来简化操作，如使用set自动处理元素去重与排序；巧妙利用输入函数特性避免复杂的空格处理；通过模块化编程提高代码可读性与可维护性。
• 可拓展之处：同类型题可增加人物数量、行为种类或消息的复杂程度，类似算法套路是针对不同行为定义状态变量，通过字符串匹配判断行为并更新状态，最后根据状态得出结果。
• 推荐题目：
  - P1036 [NOIP2002 普及组] 选数，考察枚举与状态判断。
  - P1909 买铅笔，简单的模拟与方案选择。
  - P1046 [NOIP2005 普及组] 陶陶摘苹果，基础的条件判断与模拟。
• 个人心得摘录与总结：多位作者提到调试过程遇到困难，如⑨baka因测试数据奇怪及输入输出细节问题耗费时间；Alarm5854因函数参数问题调试良久且被在线IDE误导；DEATH_ENDER因未注意字典序导致结果错误；UnyieldingTrilobite将string改为char数组后才AC，推测可能与getline使用或评测机制有关。总结可得，字符串处理细节、边界条件及数据结构的正确使用在解决此类问题中至关重要，同时调试时需仔细排查各类潜在问题。 

---
处理用时：39.69秒