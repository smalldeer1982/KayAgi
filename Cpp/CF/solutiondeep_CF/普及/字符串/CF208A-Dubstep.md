# 题目信息

# Dubstep

## 题目描述

## 题目翻译
Vasya有一句歌词(可能含有空格)，他在第一个单词之前和最后一个单词之后加上若干(可以为0)个"WUB",再每个单词之间加上若干(至少为1)个"WUB"，转变成一个新的字符串(无空格)
如"I AM X" 可以变成 "WUBWUBIWUBAMWUBWUBX" 而不能变成 "WUBWUBIAMWUBX"
现在给出转变后的字符串，求出原来的字符串

## 样例 #1

### 输入

```
WUBWUBABCWUB
```

### 输出

```
ABC ```

## 样例 #2

### 输入

```
WUBWEWUBAREWUBWUBTHEWUBCHAMPIONSWUBMYWUBFRIENDWUB
```

### 输出

```
WE ARE THE CHAMPIONS MY FRIEND ```

# AI分析结果

### 综合分析与结论
这些题解的核心思路都是对输入的字符串进行处理，将其中的 “WUB” 去掉，并在合适的位置添加空格以还原原字符串。各题解的主要区别在于处理 “WUB” 和空格的具体实现方式。

- **思路对比**：大部分题解采用遍历字符串的方式，遇到 “WUB” 就跳过或替换为空格；部分题解使用 `find` 方法查找 “WUB” 并进行替换。
- **算法要点**：关键在于准确判断 “WUB” 的位置，以及合理处理空格，避免出现多余空格。
- **难点解决**：对于开头和中间多余空格的处理是难点，不同题解采用了不同的标记方法来解决。

### 通用建议与扩展思路
- 对于字符串处理问题，要熟练掌握字符串的基本操作，如查找、替换、遍历等。
- 可以使用标记变量来处理空格和边界情况，避免出现多余的空格。
- 同类型题或类似算法套路：字符串的模式匹配、字符串的压缩与解压缩等。

### 重点代码
```cpp
// 封禁用户的题解
string s;
bool flag=true;
cin>>s;
for(int i=2;i<s.length();++i)
    if(s[i]=='B'&&s[i-1]=='U'&&s[i-2]=='W')
        s[i]=s[i-1]=s[i-2]=' ';
for(int i=0;i<s.length();++i)
{
    if(s[i]!=' ')
        flag=false;
    if(!flag)
        cout<<s[i];
    if(s[i]==' ')
        flag=true;
}

// Hu_Tao 的题解
string s, ans;
cin>>s;
for(int i=0;i<s.size();)
{
    if(i+2<s.size()&&s.substr(i,3)=="WUB")
    {
        i+=3;
        continue;
    }
    ans+=s[i];
    i++;
    if(i+2<s.size()&&s.substr(i,3)=="WUB")ans+=' ';
}
cout<<ans;

// Argon_Cube 的题解
string org;
unsigned long long pos;
cin>>org;
while((pos=org.find("WUB"))!=string::npos)
    org[pos]=org[pos+1]=org[pos+2]=' ';
char last=' ';
for(char tmp:org)
{
    if(tmp==' ')
    {
        if(last!=' ')
            cout<<' ';
    }
    else
        cout<<tmp;
    last=tmp;
}
```

### 推荐题目
1. [P1055 ISBN 号码](https://www.luogu.com.cn/problem/P1055)
2. [P1598 垂直柱状图](https://www.luogu.com.cn/problem/P1598)
3. [P1200 [USACO1.1]你的飞碟在这儿 Your Ride Is Here](https://www.luogu.com.cn/problem/P1200)

### 个人心得
- **封禁用户**：提到这只是个字符串模拟，表明该题的核心是对字符串进行模拟操作。
- **Hu_Tao**：详细分析了模拟过程中需要解决的几个问题，如找 “WUB” 的过程、跳过空格、处理答案字符串等，有助于理解解题思路。
- **Argon_Cube**：考虑了 `find` 方法反复调用是否会超时的问题，通过数据范围判断不会超时，提醒我们在解题时要关注数据范围对算法复杂度的影响。

---
处理用时：28.24秒