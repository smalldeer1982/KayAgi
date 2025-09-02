# 题目信息

# 鏡文

## 题目描述

给出由b、d、p、q四种字符组成的字符串$S$。请判断$S$是不是“镜像字符串”。

这里的“镜像字符串”是指对字符串S进行以下操作后，可得到与原字符串相同的字符串。
1. 反转S。（例："bdpq"=>"qpdb"）
2. 改b为d，改d为b，改p为q，改q为p（不要搞错对应关系）

## 说明/提示

## 条件：
- $1≤|S|≤10^5$（$|S|$表示$S$的长度）
- $S$由且仅由b、d、p、q四种字符构成

感谢@std_cpp 提供的翻译

## 样例 #1

### 输入

```
pdbq```

### 输出

```
Yes```

## 样例 #2

### 输入

```
ppqb```

### 输出

```
No```

# AI分析结果

### 题解综合分析与结论
这些题解的核心思路都是围绕判断给定字符串是否为“镜像字符串”展开，即对字符串进行反转和字符替换操作后与原字符串比较。
- **思路对比**：
    - 部分题解采用先反转字符串，再进行字符替换，最后与原字符串比较的常规思路，如k2saki、xxckie等的题解。
    - 部分题解利用映射关系简化字符替换过程，如Egg_eating_master使用map进行字符映射。
    - 还有题解通过双指针直接从字符串两端向中间比较，如Bob_Wang的题解。
- **算法要点**：
    - 字符串反转：可使用`reverse`函数或手动实现。
    - 字符替换：通过`if-else`语句、`switch`语句或映射关系实现。
    - 比较判断：使用字符串比较运算符或`strcmp`函数。
- **解决难点**：
    - 字符替换的对应关系要正确，避免混淆。
    - 反转操作要确保正确实现。
    - 处理边界情况，如字符串长度为奇数时的判断。

### 评分较高的题解
- **k2saki（4星）**：
    - **关键亮点**：思路清晰，代码简洁，使用`reverse`函数简化反转操作，`if-else`语句处理字符替换，易于理解。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    string a;
    cin>>a;
    string b=a;
    reverse(a.begin(),a.end());//交换
    for(int i=0;i<a.size();++i)
    {
        if(a[i]=='b') a[i]='d';//镜面对称
        else if(a[i]=='d') a[i]='b';//请注意,else一定要加,不然就白做了
        else if(a[i]=='p') a[i]='q';
        else if(a[i]=='q') a[i]='p';
    }
    if(a==b) cout<<"Yes";//判断
    else cout<<"No";
}
```
- **Egg_eating_master（4星）**：
    - **关键亮点**：巧妙运用`map`进行字符映射，使字符替换操作更加直观，结合`reverse`函数，代码结构清晰。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s1,s2;
map<char,char>mp;//定义一个从char类型到char类型的映射
void init(){
    cin>>s1;
    s2=s1;
    mp['b']='d';mp['d']='b';mp['q']='p';mp['p']='q';
    //将b映射到d，将d映射到b，
    //将q映射到p，将p映射到q。
}
int main(){
    init();
    reverse(s2.begin(),s2.end());//反转整个string
    for(int i=0;i<s2.size();i++)
        s2[i]=mp[s2[i]];//不断将字符进行映射
    if(s1==s2)//如果系列操作后还是原来的字符串
        cout<<"Yes\n";//输出Yes
    else 
        cout<<"No\n";//否则输出No
    return 0;
}
```
- **Bob_Wang（4星）**：
    - **关键亮点**：使用双指针从字符串两端向中间比较，减少了额外的空间开销，逻辑简洁。
    - **核心代码**：
```c
#include<cstdio>
#include<cstring>
#define maxn 100005
using namespace std;
char s[maxn];
int main()
{
    int len,flag=1;//flag打标记
    scanf("%s",s+1);
    len=strlen(s+1);
    int head=1,tail=len;//定义指针
    for(int i=1;i<=len;i++)
    {
        char n;
        if(s[tail]=='b')n='d';
        else if(s[tail]=='d')n='b';
        else if(s[tail]=='p')n='q';
        else if(s[tail]=='q')n='p';
        if(n!=s[head])
        {
            flag=0;
            break;
        }//遇到不匹配的字母
        head++;
        tail--;
    }
    if(flag)
        printf("Yes");
    else
        printf("No");
    return 0;
}
```

### 最优关键思路或技巧
- **使用`reverse`函数**：可以快速实现字符串的反转，减少手动实现的复杂度。
- **利用映射关系**：如`map`，可以将字符替换操作变得更加直观和简洁。
- **双指针法**：直接从字符串两端向中间比较，减少额外的空间开销。

### 可拓展之处
同类型题可能涉及更多字符的映射关系或更复杂的字符串操作，类似算法套路可用于判断回文串、字符串匹配等问题。

### 推荐洛谷题目
1. P1065 [NOIP2006 提高组] 作业调度方案
2. P1071 潜伏者
3. P1073 最优贸易

### 个人心得摘录与总结
- **Spiritsu**：调试时没加`break`，学校的IDE调试还炸了，导致拉低了AC率，提醒我们在编写代码时要注意细节，避免因小错误影响结果。
- **七夜**：提到用快读会报错，虽然不清楚具体原因，但提醒我们在输入字符串时要注意选择合适的输入方式。 

---
处理用时：32.67秒