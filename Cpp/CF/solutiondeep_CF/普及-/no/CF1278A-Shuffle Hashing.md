# 题目信息

# Shuffle Hashing

## 题目描述

Polycrap正在建立他自己的网页服务。作为一个很现代的网站其包含登入的功能。当然，这总会涉及到密码的安全问题。

Polycarp决定要储存密码的哈希值。密码的哈希值由以下这个算法来生成：

1.把只包含小写拉丁字母的密码$p$进行随机打乱，记为$p'$（$p'$可能和$p$相等）；

2.生成两个随机的只包含小写拉丁字母的字符串$s_1$和$s_2$（这两个串中的任何一个可能为空串）；

3.哈希算法的结果$h=s_1+p'+s_2$，此处的$+$是指把前后两个字符串首尾相接。

举个例子，$p=\texttt {abacaba}$，则$p'$可能为$\texttt{aabcaab}$。随机生成两个字符串$s_1=\texttt{zyx}",s_2=\texttt{kjh}$。那么$h=\texttt{zyxaabcaabkjh}$。

需要注意的是，从$p$变换道$p'$的过程中，不会添加或者删除任何字母，只会改变字母的顺序。

现在Polycarp想让你帮他编写密码哈希的校验模块。给出密码$p$和生成的哈希$h$，你需要检查$h$是否是$p$的一个哈希结果。

## 说明/提示

第一组查询的解释已经在题干中给出。

第二组查询中$s_1$和$s_2$均是空串，$p'$是$p$的一种打乱。

第三组查询中哈希不能通过密码生成。

第四组查询中$s_1=\texttt{n}$，$s_2$是空串，$p'=\texttt{one}$是$p$的一种打乱（虽然打乱并没有效果）。

第五组查询中哈希不能通过密码生成。

## 样例 #1

### 输入

```
5
abacaba
zyxaabcaabkjh
onetwothree
threetwoone
one
zzonneyy
one
none
twenty
ten
```

### 输出

```
YES
YES
NO
YES
NO
```

# AI分析结果

### 题目内容
# 打乱哈希

## 题目描述
Polycrap正在搭建他自己的网页服务。作为一个非常现代的网站，它包含登录功能。当然，这总会涉及到密码安全问题。

Polycarp决定存储密码的哈希值。密码的哈希值通过以下算法生成：
1. 将仅包含小写拉丁字母的密码$p$进行随机打乱，记为$p'$（$p'$可能与$p$相等）；
2. 生成两个随机的仅包含小写拉丁字母的字符串$s_1$和$s_2$（这两个字符串中的任何一个可能为空串）；
3. 哈希算法的结果$h = s_1 + p' + s_2$，此处的$+$表示将前后两个字符串首尾相接。

例如，$p = \texttt{abacaba}$，则$p'$可能为$\texttt{aabcaab}$。随机生成两个字符串$s_1 = \texttt{zyx}$，$s_2 = \texttt{kjh}$。那么$h = \texttt{zyxaabcaabkjh}$。

需要注意的是，从$p$变换到$p'$的过程中，不会添加或删除任何字母，只会改变字母的顺序。

现在Polycarp希望你帮他编写密码哈希的校验模块。给定密码$p$和生成的哈希$h$，你需要检查$h$是否是$p$的一个哈希结果。

## 说明/提示
第一组查询的解释已在题干中给出。

第二组查询中$s_1$和$s_2$均为空串，$p'$是$p$的一种打乱。

第三组查询中哈希不能通过密码生成。

第四组查询中$s_1 = \texttt{n}$，$s_2$为空串，$p' = \texttt{one}$是$p$的一种打乱（虽然打乱并没有效果）。

第五组查询中哈希不能通过密码生成。

## 样例 #1
### 输入
```
5
abacaba
zyxaabcaabkjh
onetwothree
threetwoone
one
zzonneyy
one
none
twenty
ten
```
### 输出
```
YES
YES
NO
YES
NO
```

### 算法分类
字符串

### 综合分析与结论
这些题解的核心思路都是在哈希字符串$h$中寻找一个子串，该子串包含的字符种类和数量与密码字符串$p$相同。不同之处主要在于实现方式和细节处理。有的题解使用排序后比较子串与$p$，有的通过记录字符出现次数来判断，还有的采用哈希函数映射值比对。在代码实现上，部分题解注重代码简洁性，部分则在细节处理和优化上有所体现。

### 所选的题解
 - **作者：TemplateClass (4星)**
    - **关键亮点**：思路清晰简洁，先对$p$排序，然后遍历$h$的子串，对每个子串排序后与$p$比较，同时考虑了$h$长度小于$p$长度的特殊情况。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;

int t;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin>>t;
    while(t--){
        string p, h; bool flag=0;
        cin>>p>>h; sort(&p[0], &p[p.size()]);
        if(h.size()<p.size()){ cout<<"NO"<<"\n"; continue; } 
        for(int i=0;i<h.size()-p.size()+1;++i){
            string sub=h.substr(i, p.size());
            sort(&sub[0], &sub[sub.size()]);
            if(sub==p){ flag=1; break; }
        }
        if(flag) cout<<"YES"<<"\n";
        else cout<<"NO"<<"\n";
    }
}
```
核心实现思想：先对密码$p$排序，遍历哈希$h$中所有长度与$p$相同的子串，对每个子串排序后与$p$比较，若有相等则说明匹配成功，同时特判$h$长度小于$p$长度的情况直接输出`NO`。
 - **作者：Ninelife_Cat (4星)**
    - **关键亮点**：代码简洁明了，同样是暴力枚举$h$的子串与$p$匹配，利用`sort`函数排序后判断是否相等，并且简洁地处理了$h$长度小于$p$长度的特判情况。
    - **核心代码**：
```cpp
#define ri register
int T;
string s,t;
signed main()
{
    cin>>T;while(T--)
    {
        cin>>s>>t;
        if(t.size()<s.size()) {cout<<"NO\n";continue;}//特判不合法情况
        sort(s.begin(),s.end());
        for(ri int i=0;i<=t.size()-s.size();++i)
        {
            string a=t.substr(i,s.size());//截取子串
            sort(a.begin(),a.end());
            if(s==a) {cout<<"YES\n";goto End;}
        }
        cout<<"NO\n";End:;
    }
    return 0;
}
```
核心实现思想：先特判$h$（即`t`）长度小于$p$（即`s`）长度的情况，然后对$p$排序，遍历$h$中所有长度与$p$相同的子串，排序后与$p$比较，相等则输出`YES`，否则输出`NO`。
 - **作者：YGB_XU (4星)**
    - **关键亮点**：通过记录字符出现次数来判断子串与$p$是否匹配，思路直接，代码注释详细，便于理解，同时也处理了$p$长度大于$h$长度的特判情况。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;

int cnt[30],ans[30];
int len1,len2;
string s1,s2;

bool check(int x){
    memset(cnt,0,sizeof(cnt));
    for(int i=0;i<len1;i++){
        cnt[s2[i+x]-'a'+1]++;//将字符转换为字母表编号，下同
    }
    for(int i=1;i<=26;i++) if(cnt[i]!=ans[i]) return false;
    return true;
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        memset(ans,0,sizeof(ans));
        cin>>s1>>s2;
        len1=s1.length(),len2=s2.length();
        if(len1>len2){//特判s1比s2长的情况
            printf("NO\n");
            continue;
        }
        for(int i=0;i<len1;i++) ans[s1[i]-'a'+1]++;//预处理s1字母数量
        bool flag=false;
        for(int i=0;i<=len2-len1;i++) if(check(i)){
            flag=true;
            printf("YES\n");
            break;
        }
        if(!flag) printf("NO\n");
    }
    return 0;
}
```
核心实现思想：先预处理密码$s1$中每个字符出现的次数存于`ans`数组，遍历哈希$s2$中所有长度与$s1$相同的子串，统计子串中每个字符出现次数存于`cnt`数组，对比`cnt`与`ans`数组判断子串是否与$s1$匹配，同时特判$s1$长度大于$s2$长度的情况。

### 最优关键思路或技巧
在处理这类字符串匹配问题时，排序后比较或者记录字符出现次数进行比较是常用且有效的方法。当数据范围较小时，暴力枚举子串的方式简单直接且易于实现。同时，注意对特殊情况（如$h$长度小于$p$长度）的处理，能避免不必要的错误。

### 拓展思路
同类型题常围绕字符串的匹配、重组、子串查找等展开。类似算法套路包括利用哈希表优化查找效率，对于字符集较小的情况，用数组记录字符出现次数能简化操作。在面对较大数据范围时，可能需要考虑更高效的算法，如KMP算法用于字符串匹配等。

### 洛谷相似题目推荐
 - [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)：涉及字符串查找与统计，与本题查找子串有相似之处。
 - [P1593 因子和阶乘](https://www.luogu.com.cn/problem/P1593)：虽然主要是数学问题，但在处理过程中涉及字符串的操作，与本题处理字符串的思路有一定关联。
 - [P2089 烤鸡](https://www.luogu.com.cn/problem/P2089)：通过枚举来解决问题，与本题暴力枚举子串的方式类似，可锻炼枚举的思维和代码实现能力。 

---
处理用时：83.16秒