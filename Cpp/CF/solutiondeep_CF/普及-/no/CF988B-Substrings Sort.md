# 题目信息

# Substrings Sort

## 题目描述

给定一个数n和n个字符串，求一个重新排列，对于新排列中的每个字符串
都满足在它前面的串都是它的子串。 


感谢@南方不败 提供翻译

## 样例 #1

### 输入

```
5
a
aba
abacaba
ba
aba
```

### 输出

```
YES
a
ba
aba
aba
abacaba
```

## 样例 #2

### 输入

```
5
a
abacaba
ba
aba
abab
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
3
qwerty
qwerty
qwerty
```

### 输出

```
YES
qwerty
qwerty
qwerty
```

# AI分析结果

【题目内容】
# 子串排序

## 题目描述
给定一个数 n 和 n 个字符串，求一个重新排列，使得新排列中的每个字符串，其前面的所有字符串都是它的子串。

感谢@南方不败 提供翻译

## 样例 #1
### 输入
```
5
a
aba
abacaba
ba
aba
```
### 输出
```
YES
a
ba
aba
aba
abacaba
```

## 样例 #2
### 输入
```
5
a
abacaba
ba
aba
abab
```
### 输出
```
NO
```

## 样例 #3
### 输入
```
3
qwerty
qwerty
qwerty
```
### 输出
```
YES
qwerty
qwerty
qwerty
```

【算法分类】
排序、字符串

【综合分析与结论】
这些题解的核心思路都是先对字符串按长度排序（长度相同时按字典序），再判断相邻字符串是否满足前一个是后一个的子串。各题解的主要区别在于判断子串的方式和代码实现细节。
- **思路**：都利用了若字符串 a 是 b 的子串，则 a 的长度一定不超过 b 这一特性，先排序再检查。
- **算法要点**：排序使用自定义比较函数，子串判断有的使用字符串自带的 `find` 函数，有的手动实现匹配。
- **解决难点**：主要解决如何高效判断子串以及如何保证排序符合要求。

【题解评分】
- Egg_eating_master：4星。思路清晰，代码简洁，使用 `find` 函数优化判断子串过程。
- alex_liu：3星。思路和代码结构清晰，有详细注释，但判断子串方式常规。
- JustinXiaoJunyang：3星。思路和代码实现常规，解释了排序的比较函数。
- shAdomOvO：2星。手动实现子串匹配，代码复杂，效率较低。
- Dream_It_Possible：2星。手动实现子串匹配，代码复杂，效率较低。

【所选题解】
- Egg_eating_master（4星）
  - 关键亮点：思路清晰，使用 `find` 函数优化子串判断，代码简洁。

【重点代码】
```cpp
bool cmp(string a,string b){
    return a.size()<b.size()
         ||a.size()==b.size()&&a<b;
}
int main(){
    int n;
    string s[101];
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>s[i];
    sort(s+1,s+1+n,cmp);
    for(int i=2;i<=n;i++){
        int x=s[i].find(s[i-1]);
        if(x==-1){
            cout<<"NO"<<endl;
            return 0;
        }
    }
    cout<<"YES"<<endl;
    for(int i=1;i<=n;i++)
        cout<<s[i]<<endl;
    return 0;
} 
```
**核心实现思想**：先自定义比较函数 `cmp` 对字符串按长度和字典序排序，再遍历排序后的字符串，使用 `find` 函数判断相邻字符串是否满足子串关系，若不满足则输出 `NO`，否则输出 `YES` 并按顺序输出字符串。

【可拓展之处】
同类型题可能会改变子串的判断条件，如要求是连续子串、不区分大小写的子串等。类似算法套路可用于处理字符串的包含、匹配等问题，如判断一个字符串是否是另一个字符串的旋转结果等。

【推荐题目】
1. P1125 [NOIP2008 提高组] 笨小猴
2. P1308 [NOIP2011 普及组] 统计单词数
3. P5734 【深基6.例6】文字处理软件

【个人心得】
无。

---
处理用时：29.10秒