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
本题是一道字符串模拟题，核心在于根据输入的消息判断队形是否被破坏或轰炸是否成功。各题解思路大致相同，都是通过读取消息，提取发言人、被@的人等信息，然后依据规则进行判断。

### 所选题解
- **作者：ironwheel（5星）**
    - **关键亮点**：思路清晰，将功能拆分成多个函数实现，提高了代码的可读性和可维护性。对换行符等细节进行了特判，避免了常见错误。
    - **个人心得**：注意如果发现第二个点WA且有 “On line 1 column 35, read  att, expected atte. 得分0” 这种情况，那一定就是没有特判换行符了。
- **作者：Deny_小田（4星）**
    - **关键亮点**：使用 `sscanf` 进行字符串处理，代码简洁高效。对字符串中 `@` 的个数进行了判断，符合题目要求。
    - **个人心得**：刚开始使用最朴素的方法，结果最高没超过30分。#4.in 文件过大，导致无法下载，不然用朴素方法也有可能AC。
- **作者：jyz666（4星）**
    - **关键亮点**：代码简洁，使用宏定义简化代码。通过自定义函数 `check` 检查字符串中 `@` 的个数，逻辑清晰。
    - **个人心得**：无

### 重点代码及核心实现思想
#### ironwheel的题解
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

int main(){
    getline(cin,a);
    mega=wss(a);
    while(++jl){
        getline(cin,a);
        if(a.size()==1)break;
        if(find_name(a)==mega){
            cout<<"Successful @yyy loves "<<mega<<" attempt";
            return 0;
        }
        else if(wss(a)!=mega){
            cout<<"Unsuccessful @yyy loves "<<mega<<" attempt"<<endl;
            cout<<jl+1<<endl;
            cout<<"yyy loves "<<find_name(a)<<endl;
            return 0;
        }
    }
    cout<<"Unsuccessful @yyy loves "<<mega<<" attempt\n";
    cout<<jl<<"\n";
    cout<<"Good Queue Shape";
}
```
核心实现思想：通过多个函数分别实现查找名字、统计 `@` 的个数等功能，在主函数中不断读取消息，根据规则判断轰炸是否成功或队形是否被破坏。

#### Deny_小田的题解
```cpp
const int size = 1005;
int c = 1;
char s[size],name[size],importer[size],t[size];

int main(int argc, char const *argv[]){
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
    printf("Unsuccessful @yyy loves %s attempt\n", name);
    printf("%d\n", c-1);
    printf("Good Queue Shape\n");

    return 0;
}
```
核心实现思想：使用 `sscanf` 读取发言人姓名和被@的人姓名，通过 `count` 函数统计 `@` 的个数，根据规则进行判断。

#### jyz666的题解
```cpp
#define GetAt(s,t) (sscanf(strstr(s,"@"),"@yyy loves %s",t))
char now[N+5],At[N+5],cur[N+5],target[N+5];
inline bool check(char *s,int len)
{
    register int i,tot=0;
    for(i=0;i<len;++i) if(!(s[i]^'@')&&tot++) return false;
    return tot;
}
int main()
{
    register int cnt=1,len;
    gets(now),GetAt(now,target);
    while(DRC_AK_NOI)
    {
        if(++cnt,gets(now),len=strlen(now),len<2) return printf("Unsuccessful @yyy loves %s attempt\n%d\nGood Queue Shape",target,cnt-1),0;
        if(sscanf(now,"yyy loves %s",cur),!strcmp(cur,target)) return printf("Successful @yyy loves %s attempt",target),0;
        if(!check(now,len)) return printf("Unsuccessful @yyy loves %s attempt\n%d\nyyy loves %s",target,cnt,cur),0;
        if(GetAt(now,At),strcmp(At,target)) return printf("Unsuccessful @yyy loves %s attempt\n%d\nyyy loves %s",target,cnt,cur),0;
    }
    return 0;
}
```
核心实现思想：使用宏定义和自定义函数 `check` 简化代码，在主函数中不断读取消息，根据规则判断轰炸是否成功或队形是否被破坏。

### 最优关键思路或技巧
- **函数拆分**：将不同功能拆分成多个函数，提高代码的可读性和可维护性。
- **字符串处理函数**：使用 `sscanf`、`strstr` 等函数进行字符串处理，简化代码。
- **细节处理**：对换行符、多个 `@` 等细节进行特判，避免错误。

### 可拓展之处
同类型题可能会有更复杂的规则，如增加更多的判断条件、不同的消息格式等。类似算法套路包括字符串模拟、规则判断等，可通过提取关键信息，依据规则进行判断。

### 推荐题目
- P1055 ISBN号码
- P1042 乒乓球
- P1540 机器翻译

### 个人心得总结
- **ironwheel**：注意特判换行符，否则可能会导致WA。
- **Deny_小田**：朴素方法可能得分不高，可参考优秀代码进行优化。文件过大可能影响测试，需注意。
- **クリオネ**：使用 `getchar()` 时要注意字符判断、EOF处理和换行符的两种形式。

---
处理用时：52.39秒