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

这道题是模拟类型题目，需根据给定消息判断学生玩游戏及老师巡视情况并输出结果。各题解思路相似，均是模拟事件过程，难点在于处理字符串匹配及消息判断。以下是各题解分析：
1. **⑨baka**：星级3星。思路是按题目意思模拟，用cin和gets分别读取以空格和回车结束的字符串，通过strcmp函数判断字符串是否相同。关键亮点是利用cin以空格为结束符号判断名字，避免gets多出来的空格问题。
```cpp
// 核心代码片段
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
2. **666DHG**：星级3星。暴力模拟，通过比较完全相同的字符串判断事件。用string存储名字，bool数组记录状态。亮点是利用字符串拼接比较事件。
```cpp
// 核心代码片段
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
3. **Alarm5854**：星级4星。用string类型储存名字和话语，用set储存进来的老师、正在玩游戏的学生和被逮捕的学生，通过find函数找名字，利用set自动排序和去重特性。关键亮点是使用set处理数据，时间复杂度低。
```cpp
// 核心代码片段
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
//...
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
4. **DEATH_ENDER**：星级3星。预先定义不同操作的字符串模板，通过getline读取消息对照模板判断，最后按字典序排序输出。亮点是提前定义模板字符串便于判断。
5. **UnyieldingTrilobite**：星级3星。用char数组存储名字，bool数组记录状态，通过gets读取消息，手动进行$n^2$排序。亮点是在sort疑似有问题时采用手动排序。
6. **Tiphereth_A**：星级3星。提出用位掩码记录老师和学生状态，通过宏定义函数操作，但未给出完整代码。亮点是位掩码思路可优化空间。
7. **Viston**：星级3星。用map存储老师和学生名字，getline读取消息判断并标记。亮点是利用map存储名字便于判断身份。
8. **yu__xuan**：星级3星。用数组记录学生玩游戏、被抓及老师是否在的状态，通过getline读取消息模拟判断，最后排序输出。亮点是利用数组清晰记录状态。
9. **chenxinyang2006**：星级3星。打表出有效句子，用strcmp函数判断消息，结构体存储名字并排序。亮点是打表和strcmp判断减少码量。
10. **disangan233**：星级3星。纯字符串模拟，利用stringstream处理名字输入，通过复杂字符串操作判断事件。亮点是使用stringstream处理名字输入。

最优关键思路或技巧：使用set存储相关人员，利用其自动排序和去重特性，减少手动排序及去重操作，降低时间复杂度。如Alarm5854的题解，在处理大量数据时更高效。

可拓展之处：可拓展为大规模数据下的字典树应用，通过字典树优化字符串匹配。同类型题或类似算法套路是字符串模拟，需准确处理字符串输入输出及匹配判断。

推荐洛谷题目：
- P1032 [NOIP2002 普及组] 字串变换
- P1046 [NOIP2005 普及组] 陶陶摘苹果
- P1085 [NOIP2005 普及组] 不高兴的津津

个人心得摘录及总结：
 - **⑨baka**：调试花费一小时，遇到getline多出来的空格及名字输入回车问题，采用cin与gets结合避免判断空格。总结为处理输入输出细节很重要。
 - **Alarm5854**：被函数少加取地址符卡20分钟，被在线IDE迷惑5分钟。强调编程时细节（如函数参数）及对工具的正确认知很关键。
 - **DEATH_ENDER**：因未按字典序排序得90分，强调读题仔细，注意题目隐藏要求。
 - **UnyieldingTrilobite**：用string得90TE，改成char数组后AC，推测luogu的getline或评测姬对char数组与string处理速度有差异。说明不同数据类型在特定环境下性能有别。 

---
处理用时：77.06秒