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

### 综合分析与结论
这些题解均围绕模拟老师巡视机房抓玩游戏学生的过程展开。主要思路是记录老师的进出状态和学生的游戏状态，老师在场时若学生玩游戏则标记该学生。题解在数据结构使用、字符串处理和代码实现细节上存在差异。

### 所选题解
- **作者：⑨baka（5星）**
    - **关键亮点**：思路清晰，使用字符数组和`strcmp`函数处理字符串，避免了多余空格和回车的判断问题，代码简洁易读。
    - **个人心得**：作者提到题目虽水但调试耗时一小时，可能是因为测试数据和处理多余空格、回车等细节问题。
- **作者：666DHG（4星）**
    - **关键亮点**：代码结构清晰，使用`string`类型和`getline`函数处理输入，通过简单的字符串拼接和比较判断操作，暴力模拟过程。
    - **个人心得**：作者表示代码跑得慢，但能通过，认为小数据范围暴力能过。
- **作者：Alarm5854（4星）**
    - **关键亮点**：使用`set`数据结构自动处理重复元素和排序问题，利用`string`的`find`函数查找名字，代码逻辑清晰。
    - **个人心得**：作者因函数少加取地址符调试20分钟，被在线IDE迷惑5分钟，复制大佬题解调试后安心并AC。

### 重点代码及核心实现思想
#### 作者：⑨baka
```cpp
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
核心思想：通过`cin`读取名字，`gets`读取操作，使用`strcmp`判断操作类型，更新老师和学生状态，老师在场时标记玩游戏的学生。

#### 作者：666DHG
```cpp
while (n--)
{
    k1=false;
    getline(cin,t);
    for (int i=1;i<=3;i++) if (a[i]+" came!"==t)
    {
        c[i]=true;
        break;
    }
    for (int i=1;i<=3;i++) if (a[i]+" left!"==t)
    {
        c[i]=false;
        break;
    }
    for (int i=1;i<=5;i++) if (b[i]+" started playing games!"==t)
    {
        p[i]=true;
        break;
    }
    for (int i=1;i<=5;i++) if (b[i]+" stopped playing games!"==t)
    {
        p[i]=false;
        break;
    }
    for (int i=1;i<=3;i++) if (c[i]) k1=true;
    for (int i=1;i<=5;i++) if (k1&&p[i]&&!vis[i])
    {
        vis[i]=true;
        ans[++size]=b[i];
    }
}
```
核心思想：使用`getline`读取每行消息，通过字符串拼接和比较判断操作类型，更新老师和学生状态，老师在场时记录玩游戏的学生。

#### 作者：Alarm5854
```cpp
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
核心思想：`finds`函数查找消息中的名字，`check`函数根据名字判断身份并更新状态，老师在场且有学生玩游戏时将学生加入被抓集合。

### 最优关键思路或技巧
- 使用`set`数据结构自动处理重复元素和排序问题，减少代码复杂度。
- 利用`string`的`find`函数查找名字，方便快捷。
- 使用字符数组和`strcmp`函数处理字符串，避免多余空格和回车的判断问题。

### 可拓展之处
同类型题可增加人物数量、操作类型或限制输入字符数，可使用字典树等数据结构优化。类似算法套路为模拟题，根据题目要求记录状态并进行相应操作。

### 推荐题目
- P1042 乒乓球
- P1067 多项式输出
- P1098 字符串的展开

### 个人心得总结
多位作者提到调试耗时，主要原因包括处理多余空格和回车、函数少加取地址符、在线IDE问题等。这提醒我们在编写代码时要注意细节，遇到问题可参考他人题解调试。

---
处理用时：37.20秒