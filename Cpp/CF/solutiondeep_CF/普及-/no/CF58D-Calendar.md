# 题目信息

# Calendar

## 题目描述

BerOilGasDiamondBank has branches in $ n $ cities, at that $ n $ is an even number. The bank management wants to publish a calendar with the names of all those cities written in two columns: the calendar should consist of exactly $ n/2 $ lines of strictly equal length, each of which contains exactly two names and exactly one separator character between them. The name of every city should be used in the calendar exactly once. For historical reasons the symbol $ d $ is used as the separator of words in the calendar.

The BerOilGasDiamondBank management wants to show that all its branches are equally important to it, that's why the order of their appearance in the calendar should be following: if we "glue"(concatinate) all the $ n/2 $ calendar lines (from top to bottom) to make a single line, then the lexicographically minimal line is obtained. No separator character will be used to separate calendar lines. For example, if the lines are "bertown!berville", "newberville!bera", then the resulting line is "bertown!bervillenewberville!bera". In some sense one has to find the lexicographically minimal calendar, where the comparison of calendars happens line by line.

Help BerOilGasDiamondBank and construct the required calendar.

## 样例 #1

### 输入

```
4
b
aa
hg
c
.
```

### 输出

```
aa.b
c.hg
```

## 样例 #2

### 输入

```
2
aa
a
!
```

### 输出

```
a!aa
```

## 样例 #3

### 输入

```
2
aa
a
|
```

### 输出

```
aa|a
```

# AI分析结果

### 中文重写题目内容
# 日历

## 题目描述
BerOilGasDiamondBank 在 $n$ 个城市设有分行，其中 $n$ 是偶数。银行管理层想发布一本日历，日历中所有这些城市的名称将写在两列中：日历应恰好由 $n/2$ 行组成，每行长度严格相等，每行恰好包含两个名称，且两个名称之间恰好有一个分隔字符。每个城市的名称在日历中应仅使用一次。出于历史原因，符号 $d$ 被用作日历中单词的分隔符。

BerOilGasDiamondBank 管理层希望表明其所有分行对它同样重要，因此它们在日历中的出现顺序应如下：如果我们将所有 $n/2$ 行日历（从上到下）“拼接”成一行，那么得到的行在字典序上是最小的。拼接时不会使用分隔字符来分隔日历行。例如，如果这些行是 “bertown!berville” 和 “newberville!bera”，那么拼接后的行是 “bertown!bervillenewberville!bera”。从某种意义上说，我们必须找到字典序最小的日历，日历的比较是逐行进行的。

请帮助 BerOilGasDiamondBank 构建所需的日历。

## 样例 #1
### 输入
```
4
b
aa
hg
c
.
```
### 输出
```
aa.b
c.hg
```

## 样例 #2
### 输入
```
2
aa
a
!
```
### 输出
```
a!aa
```

## 样例 #3
### 输入
```
2
aa
a
|
```
### 输出
```
aa|a
```

### 算法分类
排序

### 综合分析与结论
这些题解的核心思路都是先确定每行的目标长度，然后对输入的字符串进行排序，再通过枚举的方式找出长度和为目标长度的字符串对，最后按要求输出。
- **思路对比**：大部分题解直接在字符串后添加分隔符再排序，然后匹配长度；Soul_direction 和 _Wind_Leaves_ShaDow_ 先找出所有可行解存于数组，再对答案数组排序。
- **算法要点**：都用到排序保证字典序最小，通过双重循环枚举字符串对，根据长度和是否等于目标长度判断是否匹配。
- **解决难点**：关键在于如何确保最终拼接后的字符串字典序最小，通过排序和枚举组合的方式解决。

### 题解评分
- N_z_：3星。思路较清晰，但代码注释少，可读性一般。
- Soul_direction：4星。思路清晰，对相关知识有介绍，代码有注释，可读性较好。
- xuan_gong_dong：3星。思路明确，但代码注释少。
- JimmyLee：3星。思路清晰，代码简洁，但注释少。
- mgcjade：3星。思路有阐述，但代码部分注释不足。
- aaron0919：3星。用 C 语言实现，代码复杂，可读性一般。
- _Wind_Leaves_ShaDow_：4星。对思路和技巧讲解详细，代码有一定注释。
- Allanljx：3星。思路清晰，代码注释少。

### 所选题解
- Soul_direction：4星。关键亮点在于对 STL 字符串操作有详细介绍，代码有注释，方便理解。
- _Wind_Leaves_ShaDow_：4星。对思路和技巧讲解详细，代码有一定注释，适合初学者学习。

### 重点代码
#### Soul_direction 的代码
```cpp
string bingo(string a,string b,char c){//合并函数
    return min(a+c+b,b+c+a);
}
// ...
for(int i=1;i<=n;i++){//暴力枚举
    if(flag[i])continue;
    for(int j=i+1;j<=n;j++){
        if(flag[i])break;
        if(flag[j])continue;
        if(in[i].size()+in[j].size()==l){//判断
            flag[i]=flag[j]=1;
            out[++cnt]=bingo(in[i],in[j],ch);//合并
        }
    }
}
sort(out+1,out+cnt+1);//排序
for(int i=1;i<=cnt;i++)cout<<out[i]<<endl;
```
核心实现思想：先定义合并函数 `bingo` 取两种拼接方式的字典序最小值，然后通过双重循环枚举字符串对，找到长度和为目标长度的字符串对，标记已使用，将合并结果存入 `out` 数组，最后对 `out` 数组排序输出。

#### _Wind_Leaves_ShaDow_ 的代码
```cpp
string make(string a,string b,char c){
    string aa=a+c+b,bb=b+c+a;
    return min(aa,bb);
}//将两个字符串连接并返回最小值
// ...
for(int i=1;i<=n;i++){
    if(mark[i])continue;//i被用过
    for(int j=i+1;j<=n;j++){
        if(mark[i])break;//在当前已经求出对于i的最优解了，退出循环
        if(mark[j])continue;//j被用过
        if(s[i].size()+s[j].size()==len){
            mark[i]=true;
            mark[j]=true;//标记
            ans[++cnt]=make(s[i],s[j],d);
        }
    }
}
sort(ans+1,ans+cnt+1);//答案数组排序
for(int i=1;i<=cnt;i++)cout<<ans[i]<<endl;
```
核心实现思想：定义 `make` 函数取两种拼接方式的字典序最小值，通过双重循环枚举字符串对，找到长度和为目标长度的字符串对，标记已使用，将合并结果存入 `ans` 数组，最后对 `ans` 数组排序输出。

### 关键思路或技巧
- 先对输入的字符串进行排序，保证字典序最小。
- 在字符串后添加分隔符，方便后续处理和比较。
- 通过双重循环枚举字符串对，根据长度和是否等于目标长度判断是否匹配。
- 对于找到的字符串对，取两种拼接方式的字典序最小值。
- 最后对所有可行解进行排序，确保最终结果字典序最小。

### 拓展思路
同类型题目可能会改变条件，如增加每行字符串数量、改变分隔符规则等，但核心思路还是排序和枚举组合。类似算法套路可用于处理字符串的排列组合问题，通过排序和枚举找到满足特定条件的组合。

### 推荐题目
- [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)
- [P1271 选举学生会](https://www.luogu.com.cn/problem/P1271)
- [P1177 快速排序](https://www.luogu.com.cn/problem/P1177)

### 个人心得
- _Wind_Leaves_ShaDow_：一开始直接输出可行解未通过，将所有可行解用答案数组记录下来，最后再进行一次排序输出就通过了，虽不清楚原因，但能通过就好。总结：在处理类似字典序问题时，可能需要对最终结果进行二次排序来确保最优性。 

---
处理用时：44.15秒