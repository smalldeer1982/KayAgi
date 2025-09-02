# 题目信息

# String Game

## 题目描述

Little Nastya has a hobby, she likes to remove some letters from word, to obtain another word. But it turns out to be pretty hard for her, because she is too young. Therefore, her brother Sergey always helps her.

Sergey gives Nastya the word $ t $ and wants to get the word $ p $ out of it. Nastya removes letters in a certain order (one after another, in this order strictly), which is specified by permutation of letters' indices of the word $ t $ : $ a_{1}...\ a_{|t|} $ . We denote the length of word $ x $ as $ |x| $ . Note that after removing one letter, the indices of other letters don't change. For example, if $ t= $ "nastya" and $ a=[4,1,5,3,2,6] $ then removals make the following sequence of words "nastya" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "nastya" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "nastya" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "nastya" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "nastya" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "nastya" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "nastya".

Sergey knows this permutation. His goal is to stop his sister at some point and continue removing by himself to get the word $ p $ . Since Nastya likes this activity, Sergey wants to stop her as late as possible. Your task is to determine, how many letters Nastya can remove before she will be stopped by Sergey.

It is guaranteed that the word $ p $ can be obtained by removing the letters from word $ t $ .

## 说明/提示

In the first sample test sequence of removing made by Nastya looks like this:

"ababcba" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "ababcba" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "ababcba" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "ababcba"

Nastya can not continue, because it is impossible to get word "abb" from word "ababcba".

So, Nastya will remove only three letters.

## 样例 #1

### 输入

```
ababcba
abb
5 3 4 1 7 6 2
```

### 输出

```
3```

## 样例 #2

### 输入

```
bbbabb
bb
1 6 3 4 2 5
```

### 输出

```
4```

# AI分析结果

### 题目翻译
# 字符串游戏

## 题目描述
小娜斯佳有一个爱好，她喜欢从一个单词中删除一些字母，从而得到另一个单词。但这对她来说相当困难，因为她还太小。因此，她的哥哥谢尔盖总是帮助她。

谢尔盖给了娜斯佳单词 $t$，并想从这个单词中得到单词 $p$。娜斯佳按照特定的顺序（一个接一个，严格按照这个顺序）删除字母，这个顺序由单词 $t$ 字母索引的排列指定：$a_{1}...\ a_{|t|}$。我们用 $|x|$ 表示单词 $x$ 的长度。注意，删除一个字母后，其他字母的索引不会改变。例如，如果 $t =$ "nastya" 且 $a = [4,1,5,3,2,6]$，那么删除操作会产生以下一系列单词："nastya" → "nastya" → "nastya" → "nastya" → "nastya" → "nastya"。

谢尔盖知道这个排列。他的目标是在某个时刻阻止他的妹妹，然后自己继续删除字母以得到单词 $p$。由于娜斯佳喜欢这个活动，谢尔盖想尽可能晚地阻止她。你的任务是确定，在谢尔盖阻止她之前，娜斯佳可以删除多少个字母。

保证可以通过从单词 $t$ 中删除字母得到单词 $p$。

## 说明/提示
在第一个示例测试中，娜斯佳的删除顺序如下：
"ababcba" → "ababcba" → "ababcba" → "ababcba"

娜斯佳不能再继续了，因为不可能从单词 "ababcba" 中得到单词 "abb"。
所以，娜斯佳只会删除三个字母。

## 样例 #1
### 输入
```
ababcba
abb
5 3 4 1 7 6 2
```
### 输出
```
3
```

## 样例 #2
### 输入
```
bbbabb
bb
1 6 3 4 2 5
```
### 输出
```
4
```

### 综合分析与结论
这些题解的核心思路都是使用二分查找来解决问题。通过二分枚举删除的元素个数，利用 `check` 函数判断在删除相应数量的元素后，剩余字符串中是否存在目标字符串 $p$ 作为子序列。如果存在，则说明可以尝试删除更多元素；如果不存在，则需要减少删除的元素个数。

### 所选题解
- **作者：jianhe (赞：4)，4星**
    - **关键亮点**：思路清晰，代码简洁，使用标准库中的 `string` 类型，提高了代码的可读性。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=2e6+10;
ll n,nt,a[N],l,r,mid,ans;
string p,t;
bool check(ll x){
    string k=p;
    ll ct=0;
    for(int i=1;i<=x;i++) k[a[i]-1]=' ';
    for(int i=0;i<n;i++){
        if(k[i]==t[ct]) ct++;
        if(ct==nt) return 1; 
    }		
    return 0;
}
int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>p>>t;
    n=p.size(),nt=t.size();
    for(int i=1;i<=n;i++) cin>>a[i];
    r=n;
    while(l<=r){
        mid=l+r>>1;
        if(check(mid)) ans=mid,l=mid+1;
        else r=mid-1;
    }
    cout<<ans;
    return 0;
}
```
核心实现思想：`check` 函数中，先复制一份原字符串 $p$，将前 $x$ 个要删除的字符位置置为空格，然后遍历该字符串，检查是否能按顺序匹配到目标字符串 $t$ 的所有字符。

- **作者：lixiao189 (赞：6)，4星**
    - **关键亮点**：使用数组和 `vector` 存储数据，对二分查找和子序列判断的逻辑实现较为详细。
```cpp
bool check(int x){
    num.clear();
    for(register int i=x+1;i<=n;i++) 
        if(book[s1[operation[i]]]) num.push_back(operation[i]);
    sort(num.begin(),num.end()); //对编号进行排序 
    register int i=0,j=1;
    while(i<(int)num.size() && j<=len2){
        if(s1[num[i]]==s2[j]) i++,j++;
        else i++;
    }
    if(j==len2+1) return true;
    else return false;
}

inline void fuc(int l,int r){
    if(l>r) return;
    int mid=(l+r)>>1; //二分出右端点 
    if(check(mid)) ans=mid,fuc(mid+1,r);
    else fuc(l,mid-1);
}
```
核心实现思想：`check` 函数中，先将未被删除的字符的索引存入 `vector` 中并排序，然后遍历该 `vector`，检查是否能按顺序匹配到目标字符串 $s2$ 的所有字符。`fuc` 函数实现二分查找。

### 最优关键思路或技巧
- **二分查找**：利用二分查找的思想，将原本 $O(n)$ 的枚举复杂度优化到 $O(\log n)$，从而使总时间复杂度降为 $O(n \log n)$。
- **子序列判断**：通过双指针法，遍历剩余字符串，检查是否能按顺序匹配到目标字符串的所有字符，实现子序列的判断。

### 可拓展之处
同类型题目通常涉及字符串操作和二分查找的结合，例如判断在一定操作下字符串是否满足某种条件，或者求满足条件的最大或最小操作次数等。类似算法套路还可应用于数组、序列等相关问题中，通过二分查找和条件判断来优化时间复杂度。

### 推荐题目
1. [P1873 砍树](https://www.luogu.com.cn/problem/P1873)
2. [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)
3. [P3853 [TJOI2007]路标设置](https://www.luogu.com.cn/problem/P3853)

### 个人心得
部分题解提到这是二分练手题，强调了二分查找在解决此类问题中的重要性，以及通过二分查找可以将原本复杂的枚举问题转化为更高效的算法。同时，在实现过程中需要注意字符串下标和删除顺序下标的转换，以及边界条件的处理。 

---
处理用时：49.12秒