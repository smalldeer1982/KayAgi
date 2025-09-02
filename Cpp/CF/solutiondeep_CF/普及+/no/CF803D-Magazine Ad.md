# 题目信息

# Magazine Ad

## 题目描述

The main city magazine offers its readers an opportunity to publish their ads. The format of the ad should be like this:

There are space-separated non-empty words of lowercase and uppercase Latin letters.

There are hyphen characters '-' in some words, their positions set word wrapping points. Word can include more than one hyphen.

It is guaranteed that there are no adjacent spaces and no adjacent hyphens. No hyphen is adjacent to space. There are no spaces and no hyphens before the first word and after the last word.

When the word is wrapped, the part of the word before hyphen and the hyphen itself stay on current line and the next part of the word is put on the next line. You can also put line break between two words, in that case the space stays on current line. Check notes for better understanding.

The ad can occupy no more that $ k $ lines and should have minimal width. The width of the ad is the maximal length of string (letters, spaces and hyphens are counted) in it.

You should write a program that will find minimal width of the ad.

## 说明/提示

Here all spaces are replaced with dots.

In the first example one of possible results after all word wraps looks like this:

`<br></br>garage.<br></br>for.<br></br>sa-<br></br>le<br></br>`The second example:

`<br></br>Edu-ca-<br></br>tion-al.<br></br>Ro-unds.<br></br>are.so.fun<br></br>`

## 样例 #1

### 输入

```
4
garage for sa-le
```

### 输出

```
7
```

## 样例 #2

### 输入

```
4
Edu-ca-tion-al Ro-unds are so fun
```

### 输出

```
10
```

# AI分析结果

### 题目内容
# 杂志广告

## 题目描述
主要城市杂志为读者提供发布广告的机会。广告格式应如下：
有由空格分隔的非空单词，单词由小写和大写拉丁字母组成。
部分单词中有连字符“-”，其位置设定了换行点。一个单词可能包含多个连字符。
保证不存在相邻的空格和相邻的连字符。连字符不与空格相邻。第一个单词之前和最后一个单词之后没有空格和连字符。
当单词换行时，连字符及其之前的部分留在当前行，单词的下一部分放在下一行。也可以在两个单词之间换行，此时空格留在当前行。查看注释以更好地理解。
广告占用行数不超过 $k$ 行，且应具有最小宽度。广告的宽度是其中字符串（字母、空格和连字符都计算在内）的最大长度。
你需要编写一个程序，找出广告的最小宽度。

## 说明/提示
这里所有空格都替换为点。
在第一个示例中，所有单词换行后的一种可能结果如下：
`<br></br>garage.<br></br>for.<br></br>sa-<br></br>le<br></br>`
第二个示例：
`<br></br>Edu-ca-<br></br>tion-al.<br></br>Ro-unds.<br></br>are.so.fun<br></br>`

## 样例 #1
### 输入
```
4
garage for sa-le
```
### 输出
```
7
```

## 样例 #2
### 输入
```
4
Edu-ca-tion-al Ro-unds are so fun
```
### 输出
```
10
```

### 算法分类
二分

### 综合分析与结论
所有题解都采用二分算法解决该问题，思路核心是二分广告的宽度，通过检查在该宽度限制下能否将给定字符串分成不超过 $k$ 行，以此确定最小宽度。各题解的不同之处主要体现在代码实现细节，如字符串处理方式、输入方法、`check` 函数具体实现等。

### 所选的题解
 - **作者：Echoternity（5星）**
    - **关键亮点**：思路清晰，先将字符串转化为数字数组，明确问题为将 $n$ 个数分成 $k$ 个区间使最大区间和最小，二分区间长度并通过 `check` 函数暴力判断，代码简洁明了，对边界情况如单个区间长度大于判定长度进行了特判。
    - **个人心得**：原以为是 `dp` 题，实际是二分题；提醒注意 `gets()` 函数废除，建议用 `while(getchar())` 输入，避免使用 `stl` 库。
    - **核心代码**：
``` c++
inline bool check(int x)
{
    int res=0,cnt=0;
    for(int i=1;i<=tot;++i)
    {
        if(val[i]>x) return 0;
        if(res+val[i]<=x) res+=val[i];
        else ++cnt,res=val[i];
    }
    if(cnt>=k) return 0;
    return 1;
}
int main()
{
    read(k);
    while((str[++len]=gh())!='\n');
    p=1;
    for(int i=1;i<=len;++i)
        if(str[i]=='-'||str[i]==' ')
            val[++tot]=i-p+1,p=i+1;
    if(p!=len+1) val[++tot]=len-p;
    int l=0,r=len;
    while(l<r)
    {
        int mid=(l+r)>>1;
        if(check(mid)) r=mid;
        else l=mid+1;
    }
    printf("%d",l);
    return 0;
}
```
核心实现思想：`check` 函数遍历数组 `val`，累加当前区间长度，若超过 `x` 则新开区间并计数，最后判断区间数是否小于 `k`。主函数读取数据并处理成数组 `val`，二分查找最小宽度。
 - **作者：wuyixiang（4星）**
    - **关键亮点**：题目大意提炼准确，代码实现直接，`check` 函数中通过记录可断开位置，在满足长度条件时进行分段，逻辑清晰，同时指出输入时需注意读取换行符以及长度最小为1的坑点。
    - **核心代码**：
```cpp
bool check(int m)
{
    int w = 0,x = 0,z = 1;
    for(int i = 0;i < s.size();i ++)
    {
        if(s[i] == '-' || s[i] == ' ')w = i;
        x ++;
        if(x >= m && i!= s.size() - 1)
        {
            if(w == 0)return false;
            x = i - w,w = 0,z ++;
        }
    }
    return z <= k;
}
int main()
{
    cin >> k;
    getchar();
    getline(cin,s);
    while(l < r)
    {
        int mid = (l + r) / 2;
        if(check(mid))r = mid;
        else l = mid + 1;
    }
    cout << l;
}
```
核心实现思想：`check` 函数遍历字符串 `s`，记录可断开位置 `w`，当当前长度 `x` 达到或超过 `m` 且未到字符串末尾时，从可断开位置分段，最后判断段数是否满足要求。主函数读取数据并二分查找最小宽度。
 - **作者：DennyQi（4星）**
    - **关键亮点**：将题目转化为经典的分组问题，利用类似队列方法判定每一行长度不超过 `mid` 时所需行数，代码结构完整，包含输入优化和数组前缀和处理，逻辑严谨。
    - **核心代码**：
```cpp
inline int get_sum(int l, int r){
    return!l? sum[r] : sum[r]-sum[l-1];
}
inline bool judge(int x){
    int res = 0, pre = 0;
    for(int i = 0; i < n; ++i) if(a[i] > x) return 0;
    for(int i = 0; i < n; ++i) if(get_sum(pre,i) > x) pre = i, ++res;
    return res+1 <= k;
}
int main(){
    scanf("%d",&k); getchar();
    gets(s);
    len = strlen(s);
    for(int i = 0; i < len; ++i)
        if(s[i] == '-' || s[i] == ' '){
            a.push_back(i-las+1), cul_sum();
            las = i+1;
        }
    a.push_back(len-las), cul_sum();
    n = a.size();
    l = 1, r = len;
    while(l <= r){
        mid = (l+r)>>1;
        if(judge(mid)) r = mid-1, ans = mid; else l = mid+1;
    }
    printf("%d",ans);
    return 0;
}
```
核心实现思想：`get_sum` 函数计算数组 `a` 区间和，`judge` 函数遍历数组 `a`，判断以 `x` 为宽度时所需行数是否满足要求。主函数读取数据并处理成数组 `a` 及前缀和数组 `sum`，二分查找最小宽度。

### 最优关键思路或技巧
利用二分答案的思想，将求最小宽度问题转化为判定问题，通过不断缩小二分范围找到最小宽度。在实现中，注意处理字符串，将其按连字符和空格转化为数字数组，方便后续计算；同时在 `check` 函数中，采用贪心策略，尽量使每行长度接近二分的宽度，以准确判断是否满足行数要求。

### 同类型题或类似算法套路
此类题目通常具有单调性，即所求答案越大，满足条件越容易（或反之），可以考虑二分答案。常见的类似问题还有在一定限制条件下将序列分组，求组内最大和最小等问题。解决这类问题，关键在于明确二分的对象（如本题的广告宽度），并设计合理的判定函数。

### 洛谷题目推荐
 - [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)：通过二分跳跃距离，判断在该距离下能否移除指定数量的石头。
 - [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)：将数列分成 $m$ 段，使每段和的最大值最小，同样使用二分答案思路。
 - [P3853 [TJOI2007]路标设置](https://www.luogu.com.cn/problem/P3853)：在公路上添加路标，使相邻路标间最大距离最小，适合二分答案求解。

### 个人心得摘录与总结
 - **Echoternity**：做题时对题目算法判断失误，原以为是 `dp` 实际是二分；同时提到 `gets()` 函数废除，建议使用 `while(getchar())` 输入以避免使用 `stl` 库。总结出做题需准确判断算法类型，同时关注输入函数的适用性。
 - **wuyixiang**：指出输入时需注意读取换行符，以及答案长度最小为1的细节，提醒在处理输入输出和边界条件时要谨慎。
 - **神之右大臣**：强调在不同系统下 `string` 存储 `'\0'` 字符的差异，在Linux下读取换行需用两遍 `getchar()`，否则可能爆零，说明不同系统环境对代码实现的影响，编码时要考虑环境差异。 

---
处理用时：73.29秒