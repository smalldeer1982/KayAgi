# 题目信息

# Mahmoud and a Dictionary

## 题目描述

Mahmoud wants to write a new dictionary that contains $ n $ words and relations between them. There are two types of relations: synonymy (i. e. the two words mean the same) and antonymy (i. e. the two words mean the opposite). From time to time he discovers a new relation between two words.

He know that if two words have a relation between them, then each of them has relations with the words that has relations with the other. For example, if like means love and love is the opposite of hate, then like is also the opposite of hate. One more example: if love is the opposite of hate and hate is the opposite of like, then love means like, and so on.

Sometimes Mahmoud discovers a wrong relation. A wrong relation is a relation that makes two words equal and opposite at the same time. For example if he knows that love means like and like is the opposite of hate, and then he figures out that hate means like, the last relation is absolutely wrong because it makes hate and like opposite and have the same meaning at the same time.

After Mahmoud figured out many relations, he was worried that some of them were wrong so that they will make other relations also wrong, so he decided to tell every relation he figured out to his coder friend Ehab and for every relation he wanted to know is it correct or wrong, basing on the previously discovered relations. If it is wrong he ignores it, and doesn't check with following relations.

After adding all relations, Mahmoud asked Ehab about relations between some words based on the information he had given to him. Ehab is busy making a Codeforces round so he asked you for help.

## 样例 #1

### 输入

```
3 3 4
hate love like
1 love like
2 love hate
1 hate like
love like
love hate
like hate
hate like
```

### 输出

```
YES
YES
NO
1
2
2
2
```

## 样例 #2

### 输入

```
8 6 5
hi welcome hello ihateyou goaway dog cat rat
1 hi welcome
1 ihateyou goaway
2 hello ihateyou
2 hi goaway
2 hi hello
1 hi hello
dog cat
dog hi
hi hello
ihateyou goaway
welcome ihateyou
```

### 输出

```
YES
YES
YES
YES
NO
YES
3
3
1
1
2
```

# AI分析结果

### 题目内容
Mahmoud想要编写一本包含$n$个单词以及它们之间关系的新字典。关系有两种类型：同义（即两个单词意思相同）和反义（即两个单词意思相反）。他不时会发现两个单词之间的新关系。

他知道如果两个单词之间存在关系，那么它们各自与另一个单词有关系的那些单词也存在关系。例如，如果“like”意思是“love”，且“love”与“hate”相反，那么“like”也与“hate”相反。再例如，如果“love”与“hate”相反，且“hate”与“like”相反，那么“love”就意味着“like”，依此类推。

有时Mahmoud会发现错误的关系。错误的关系是指使两个单词同时相等且相反的关系。例如，如果他知道“love”意味着“like”，“like”与“hate”相反，然后他又发现“hate”意味着“like”，那么最后这个关系就是绝对错误的，因为它使“hate”和“like”同时既相反又意思相同。

在Mahmoud找出许多关系后，他担心其中一些是错误的，从而会使其他关系也出错，所以他决定将他找出的每一个关系都告诉编码朋友Ehab，并且对于每一个关系，他想知道根据之前发现的关系，这个关系是正确还是错误。如果是错误的，他就忽略它，并且不再用它去检查后续关系。

在添加完所有关系后，Mahmoud根据他提供给Ehab的信息询问了一些单词之间的关系。Ehab正忙于组织Codeforces比赛，所以他向你求助。

### 样例 #1
#### 输入
```
3 3 4
hate love like
1 love like
2 love hate
1 hate like
love like
love hate
like hate
hate like
```
#### 输出
```
YES
YES
NO
1
2
2
2
```
### 样例 #2
#### 输入
```
8 6 5
hi welcome hello ihateyou goaway dog cat rat
1 hi welcome
1 ihateyou goaway
2 hello ihateyou
2 hi goaway
2 hi hello
1 hi hello
dog cat
dog hi
hi hello
ihateyou goaway
welcome ihateyou
```
#### 输出
```
YES
YES
YES
YES
NO
YES
3
3
1
1
2
```
### 算法分类
并查集
### 综合分析与结论
这道题主要考查并查集的应用，通过维护单词间的同义与反义关系来判断新关系是否矛盾，并回答单词间关系的询问。题解主要分为两类思路：扩展域并查集和带权并查集。
 - **扩展域并查集**：将每个单词拆成两个点，分别表示近义词域和反义词域。在确认关系时，判断是否与已有关系矛盾，若不矛盾则进行相应合并。查询时，依据两个单词对应点是否在同一集合判断关系。
 - **带权并查集**：用一个数组表示节点与祖先的关系，0表示同义，1表示反义。通过向量的方式更新节点与祖先关系，判断关系是否矛盾及查询单词间关系。

解决难点在于如何合理利用并查集的数据结构，准确维护单词间的两种关系，以及在添加新关系时判断是否与已有关系冲突。
### 所选的题解
 - **作者：Alex_Wei (5星)**
    - **关键亮点**：思路清晰，简洁明了地阐述了扩展域并查集的做法，代码实现简洁，直接使用`map`进行单词到编号的映射，整体结构紧凑。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
map <string,int> mp;
int n,m,q,f[200005];
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
string s,t; 
int main(){
    cin>>n>>m>>q;
    for(int i=0;i<n;i++)cin>>s,mp[s]=i,f[i]=i,f[i+n]=i+n;
    for(int i=0;i<m;i++){
        int rel,u,v;
        cin>>rel>>s>>t;
        u=mp[s],v=mp[t];
        if(rel==1){
            if(find(u)==find(v+n))puts("NO");
            else puts("YES"),f[find(u)]=find(v),f[find(u+n)]=find(v+n);
        }
        else{
            if(find(u)==find(v))puts("NO");
            else puts("YES"),f[find(u)]=find(v+n),f[find(u+n)]=find(v);
        }
    }
    for(int i=0;i<q;i++){
        cin>>s>>t;
        int u=mp[s],v=mp[t];
        if(find(u)==find(v))puts("1");
        else if(find(u)==find(v+n))puts("2");
        else puts("3");
    }
    return 0;
}
```
    - **核心实现思想**：利用`map`将单词映射为编号，通过`find`函数查找并查集代表元。在处理关系时，判断是否矛盾并进行相应的并查集合并操作。查询时，根据单词对应编号在并查集中的关系输出结果。
 - **作者：est1ck_0tto (4星)**
    - **关键亮点**：对题意的解读详细，代码实现基本思路清晰，注释丰富，对扩展域并查集的每个操作都有注释说明，便于理解。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int f[1000000];
string st1,st2;
map<string,int>mp;
int find(int a){
    if(f[a]==a){
        return a;
    }
    return f[a]=find(f[a]);
}
int main(){
    int n,m,n1;
    string t;
    int t1;
    cin>>n1>>n>>m;
    for(int i=1;i<=n1;i++){
        cin>>t;
        mp[t]=i;
        f[i]=i;f[i+n1]=i+n1;
    }
    int u,v;
    for(int i=1;i<=n;i++){
        cin>>t1>>st1>>st2;
        u=mp[st1],v=mp[st2]; 
        if (t1==1){
            if (find(u)==find(v+n1)){
                puts("NO"); 
            } 
            else {
                puts("YES"); 
                f[find(u)]=find(v);
                f[find(u+n1)]=find(v+n1); 
            }
        }
        if (t1==2){
            if (find(u)==find(v)){
                puts("NO");
            } 
            else {
                puts("YES"); 
                f[find(u+n1)]=find(v);
                f[find(u)]=find(v+n1);

            }
        }
    }
    for(int i=1;i<=m;i++){
        cin>>st1>>st2;
        u=mp[st1],v=mp[st2];
        if (find(u)==find(v))puts("1");
        else if (find(u)==find(v+n1))puts("2");
             else puts("3");        
    }
    return 0;
}
```
    - **核心实现思想**：与Alex_Wei思路类似，同样使用`map`映射单词，通过`find`函数路径压缩查找代表元。在处理关系和查询时，依据扩展域并查集规则进行操作并输出结果。
 - **作者：ღꦿ࿐ (4星)**
    - **关键亮点**：使用带权并查集解决问题，提供了不同于多数扩展域并查集的思路，对带权并查集的关键步骤如更新节点与祖先关系的公式有清晰说明。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,q,pa[100001],sum[100001],tp,x,y;
string s,s1,s2;
map<string,int> mp;
int root(int x)
{
    if (pa[x]==x) return x;
    int rt=root(pa[x]);
    sum[x]^=sum[pa[x]];
    pa[x]=rt;
    return rt;
}
signed main()
{
    cin>>n>>m>>q;
    for (int i=1;i<=n;i++)
    {
        cin>>s;
        mp[s]=i;
    }
    for (int i=1;i<=n;i++) pa[i]=i;
    for (int i=1;i<=m;i++)
    {
        cin>>tp>>s1>>s2;
        x=mp[s1];y=mp[s2];
        if (tp==1)
        {
            int rx=root(x),ry=root(y);
            if (rx==ry)
            {
                if (sum[x]!=sum[y]) printf("NO\n");
                else printf("YES\n");
            }
            else
            {
                printf("YES\n");
                pa[rx]=ry;
                sum[rx]=sum[x]^sum[y];
            }
        }
        else
        {
            int rx=root(x),ry=root(y);
            if (rx==ry)
            {
                if (sum[x]==sum[y]) printf("NO\n");
                else printf("YES\n");
            }
            else
            {
                printf("YES\n");
                pa[rx]=ry;
                sum[rx]=sum[x]^sum[y]^1;
            }
        }
    }
    for (int i=1;i<=q;i++)
    {
        cin>>s1>>s2;
        x=mp[s1];y=mp[s2];
        int rx=root(x),ry=root(y);
        if (rx!=ry) printf("3\n");
        else 
        {
            if (sum[x]==sum[y]) printf("1\n");
            else printf("2\n");
        }
    }
    return 0;
}
```
    - **核心实现思想**：通过`map`映射单词，`root`函数在查找祖先时更新节点与祖先关系`sum`。处理关系时，根据根节点是否相同及`sum`值判断是否矛盾并进行合并操作。查询时，依据根节点和`sum`值输出单词间关系。
### 最优关键思路或技巧
 - **扩展域并查集**：将每个单词拆分为两个域，分别表示同义与反义关系，通过并查集合并与查找操作维护关系，简单直观，易于实现和理解。
 - **带权并查集**：利用节点与祖先的关系值表示单词间关系，通过向量方式更新关系，在处理复杂关系时有独特优势，能更简洁地维护和判断关系。
### 同类型题或类似算法套路
此类题目通常涉及元素间多种关系的维护与判断，可使用扩展域并查集或带权并查集解决。当关系种类较少且明确时，扩展域并查集更易理解和实现；当关系可通过某种数值表示且有传递性时，带权并查集更为适用。
### 洛谷相似题目
 - **P1525 [NOIP2010 提高组] 关押罪犯**：通过扩展域并查集解决二分图判定问题，与本题维护不同关系并判断矛盾类似。
 - **P2024 [NOI2001] 食物链**：经典的扩展域并查集题目，通过不同域表示生物间不同关系，和本题思路相近。
 - **P1196 [NOI2002] 银河英雄传说**：使用带权并查集维护舰队间的距离关系，可锻炼对带权并查集的理解与应用。
### 个人心得摘录
 - **作者：psychosocial**：开始不太会带权并查集，参考食物链代码修改但公式错误导致错误。学习后修改公式通过，意识到对带权并查集的理解和公式运用的重要性。总结为对新算法要深入学习理解其核心原理，不能盲目修改代码。 

---
处理用时：84.18秒