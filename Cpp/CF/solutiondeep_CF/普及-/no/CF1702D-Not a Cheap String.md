# 题目信息

# Not a Cheap String

## 题目描述

Let $ s $ be a string of lowercase Latin letters. Its price is the sum of the indices of letters (an integer between 1 and 26) that are included in it. For example, the price of the string abca is $ 1+2+3+1=7 $ .

The string $ w $ and the integer $ p $ are given. Remove the minimal number of letters from $ w $ so that its price becomes less than or equal to $ p $ and print the resulting string. Note that the resulting string may be empty. You can delete arbitrary letters, they do not have to go in a row. If the price of a given string $ w $ is less than or equal to $ p $ , then nothing needs to be deleted and $ w $ must be output.

Note that when you delete a letter from $ w $ , the order of the remaining letters is preserved. For example, if you delete the letter e from the string test, you get tst.

## 样例 #1

### 输入

```
5
abca
2
abca
6
codeforces
1
codeforces
10
codeforces
100```

### 输出

```
aa
abc

cdc
codeforces```

# AI分析结果

### 题目内容
# 不廉价的字符串

## 题目描述
设 $s$ 是一个由小写拉丁字母组成的字符串。其价格是字符串中所包含字母的索引之和（索引是介于1到26之间的整数）。例如，字符串“abca”的价格是 $1 + 2 + 3 + 1 = 7$。

给定字符串 $w$ 和整数 $p$。从 $w$ 中删除最少数量的字母，使得其价格小于或等于 $p$，并输出结果字符串。注意，结果字符串可能为空。你可以删除任意字母，这些字母不必连续。如果给定字符串 $w$ 的价格已经小于或等于 $p$，则无需删除任何字母，直接输出 $w$。

注意，当你从 $w$ 中删除一个字母时，其余字母的顺序保持不变。例如，如果你从字符串“test”中删除字母“e”，你将得到“tst”。

## 样例 #1
### 输入
```
5
abca
2
abca
6
codeforces
1
codeforces
10
codeforces
100
```
### 输出
```
aa
abc

cdc
codeforces
```
### 算法分类
贪心

### 题解综合分析与结论
这些题解的核心思路都是基于贪心策略，即要使删除的字母数量最少，就应优先删除对价格贡献大的字母。不同题解在具体实现上存在差异，主要体现在数据结构的选择和处理方式上。有的通过结构体结合排序来处理，有的使用map建立字符到出现次数的映射，还有的直接遍历字符串进行操作。

### 所选的题解
- **作者：tzyt (5星)**
    - **关键亮点**：思路清晰，利用 `map` 建立字符到出现次数的映射，倒序遍历 `map` 优先删除对价格贡献大的字符，代码简洁且可读性高。
    - **核心代码**：
```cpp
map<char, int> bkt; // 桶
ll price = 0;
for (char ch : str) {
    bkt[ch]++;
    price += (ch - 'a' + 1);
}
map<char, int>::reverse_iterator it = bkt.rbegin();
while (price > p) {
    (*it).second--; 
    price -= ((*it).first - 'a' + 1);
    if ((*it).second <= 0) {
        if (it!= bkt.rend()) it++;
    }
}
string ans;
for (char ch : str) {
    if (bkt[ch] > 0) {
        ans.push_back(ch);
        bkt[ch]--;
    }
}
```
核心实现思想：先统计每个字符出现次数并计算初始价格，倒序遍历 `map`，在价格大于 `p` 时，减少当前字符出现次数并更新价格，若当前字符删完则移动到下一个字符。最后遍历原字符串，根据 `map` 中字符剩余次数决定是否输出。
- **作者：yeshubo_qwq (5星)**
    - **关键亮点**：代码简洁明了，直接遍历字符串，从价值最大的字符 `z` 开始尝试删除，直到字符串价值不超过 `p`，实现简单直接。
    - **核心代码**：
```cpp
void solve(){
    cin>>s+1>>p,n=strlen(s+1);
    res=0;
    for (i=1;i<=n;i++) res+=(s[i]&31);
    if (res<=p) {cout<<s+1<<'\n';return;}
    for (c='z';c>='a';c--){
        for (i=1;i<=n;i++)
            if (s[i]==c){
                res-=(c&31);
                s[i]='#';
                if (res<=p) {
                    for (j=1;j<=n;j++)
                        if (s[j]!='#') cout<<s[j];
                    cout<<'\n';
                    return;
                }
            }
    }
}
```
核心实现思想：先计算字符串初始价值，若初始价值不超过 `p` 直接输出。否则从 `z` 到 `a` 遍历字符，尝试删除字符串中当前字符，更新价值，当价值不超过 `p` 时输出剩余字符串。
- **作者：NATO (4星)**
    - **关键亮点**：采用结构体存储字符及其原位置，排序后从大到小删除字符，能较好地处理字符顺序问题，逻辑清晰。
    - **核心代码**：
```cpp
struct px
{
    ll a;
    ll id;
}st[200005];
bool cmp(px ak,px b)
{
    return b.a<ak.a;
}
//...
for(ll i=0;i<len;++i)
    cnt+=1+a[i]-'a',vis[i]=0,st[++sum].a=a[i]-'a'+1,st[sum].id=i;
if(cnt<=p)
{
    cout<<a<<endl;continue;
}
sort(st+1,st+1+sum,cmp);
while(1)
{
    vis[st[++op].id]=1;
    cnt-=st[op].a;
    if(cnt<=p||op==sum)
        break;
}
for(ll i=0;i<len;++i)
    if(!vis[i])
        cout<<a[i];
```
核心实现思想：用结构体记录字符价值和原位置，计算初始价值，若初始价值不超 `p` 直接输出。否则按价值从大到小排序结构体数组，依次删除字符并更新价值，最后根据标记输出剩余字符。

### 最优关键思路或技巧
利用贪心策略，优先删除对价格贡献大的字母。在实现上，使用合适的数据结构如 `map` 或结构体数组，结合排序或直接遍历等方式，高效地完成字符的删除和结果字符串的生成。

### 可拓展之处
同类型题常围绕贪心策略，可能在字符串处理上增加难度，比如字符种类增多、字符串长度限制变化等。类似算法套路是在满足局部最优能导致全局最优的情况下，优先选择对目标影响大的元素进行处理。

### 洛谷相似题目
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)
- [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)
- [P2859 [USACO06DEC]Milk Patterns G](https://www.luogu.com.cn/problem/P2859)

### 个人心得
无

---
处理用时：45.22秒