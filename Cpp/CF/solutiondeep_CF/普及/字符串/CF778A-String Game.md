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

### 题目中文重写
# 字符串游戏

## 题目描述
小娜斯佳有一个爱好，她喜欢从一个单词中移除一些字母，从而得到另一个单词。但这对她来说太难了，因为她还太小。因此，她的哥哥谢尔盖总是帮助她。

谢尔盖给娜斯佳一个单词 $t$，并希望从这个单词中得到单词 $p$。娜斯佳按照特定的顺序（一个接一个，严格按照这个顺序）移除字母，这个顺序由单词 $t$ 中字母的索引排列 $a_{1}...\ a_{|t|}$ 给出。我们用 $|x|$ 表示单词 $x$ 的长度。注意，移除一个字母后，其他字母的索引不会改变。例如，如果 $t =$ “nastya” 且 $a = [4,1,5,3,2,6]$，那么移除操作会产生以下一系列单词 “nastya” → “nastya” → “nastya” → “nastya” → “nastya” → “nastya”。

谢尔盖知道这个排列。他的目标是在某个时刻阻止他的妹妹，然后自己继续移除字母以得到单词 $p$。由于娜斯佳喜欢这个活动，谢尔盖希望尽可能晚地阻止她。你的任务是确定，在谢尔盖阻止她之前，娜斯佳可以移除多少个字母。

保证可以通过从单词 $t$ 中移除字母得到单词 $p$。

## 说明/提示
在第一个示例测试中，娜斯佳的移除序列如下：

“ababcba” → “ababcba” → “ababcba” → “ababcba”

娜斯佳不能再继续了，因为不可能从单词 “ababcba” 中得到单词 “abb”。

所以，娜斯佳只会移除三个字母。

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
这些题解的核心思路都是利用二分查找来解决问题。二分的关键在于确定删除字符的数量，通过 `check` 函数判断删除相应数量字符后，剩余字符中是否存在等于目标字符串 $p$ 的子序列。如果存在，则尝试更大的删除数量；如果不存在，则尝试更小的删除数量。

### 所选的题解
- **作者：lixiao189 (赞：6)，4星**
  - **关键亮点**：思路清晰，详细阐述了二分的依据和过程，代码结构清晰，注释明确。
  - **核心实现思想**：通过二分查找右端点，对于每个二分的中间值，使用 `check` 函数判断删除前 $mid$ 个字符后，剩余字符中是否存在等于 $t$ 的子序列。
  - **核心代码**：
```cpp
bool check(int x){
    num.clear();
    for(register int i=x+1;i<=n;i++) 
        if(book[s1[operation[i]]]) num.push_back(operation[i]);
    sort(num.begin(),num.end()); 
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
    int mid=(l+r)>>1; 
    if(check(mid)) ans=mid,fuc(mid+1,r);
    else fuc(l,mid-1);
}
```
- **作者：jianhe (赞：4)，4星**
  - **关键亮点**：代码简洁，对二分的可行性分析清晰，`check` 函数实现简单明了。
  - **核心实现思想**：二分枚举删除的元素个数，`check` 函数通过标记删除的字符，然后遍历剩余字符判断是否包含目标序列 $t$。
  - **核心代码**：
```cpp
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
```
- **作者：zhangqiuyanAFOon2024 (赞：2)，4星**
  - **关键亮点**：思路简洁，代码实现直接，对二分和 `check` 函数的逻辑处理清晰。
  - **核心实现思想**：二分答案，`check` 函数通过标记删除的字符，然后遍历剩余字符判断是否满足题意。
  - **核心代码**：
```cpp
bool check(int n){
    string t=s;
    for(int i=0;i<n;i++)
        t[a[i]-1]=' ';
    int id=0;
    for(int i=0;i<ls;i++)
        if(t[i]==ans[id]) id++;
    if(id==la) return 1;
    return 0;
}
```

### 最优关键思路或技巧
- **二分查找**：利用二分查找的特性，将原本 $O(n)$ 的枚举复杂度优化到 $O(\log n)$，从而使总时间复杂度降为 $O(n \log n)$。
- **子序列判断**：通过双指针法判断剩余字符中是否存在等于目标字符串的子序列，时间复杂度为 $O(n)$。

### 可拓展之处
同类型题或类似算法套路：
- 涉及字符串操作和查找最大/最小满足条件的值的问题，都可以考虑使用二分查找进行优化。
- 对于判断子序列的问题，双指针法是一种常用且高效的方法。

### 推荐题目
- [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)
- [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)
- [P3853 [TJOI2007] 路标设置](https://www.luogu.com.cn/problem/P3853)

### 个人心得摘录与总结
部分题解提到这是二分练手题，强调了二分查找在解决这类问题中的重要性和有效性。通过二分查找可以将复杂的枚举问题转化为更高效的查找问题，从而降低时间复杂度。同时，在实现过程中要注意边界条件和细节处理，如字符索引的转换等。

---
处理用时：51.05秒