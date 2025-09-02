# 题目信息

# Middle-Out

## 题目描述

The problem was inspired by Pied Piper story. After a challenge from Hooli's compression competitor Nucleus, Richard pulled an all-nighter to invent a new approach to compression: middle-out.

You are given two strings $ s $ and $ t $ of the same length $ n $ . Their characters are numbered from $ 1 $ to $ n $ from left to right (i.e. from the beginning to the end).

In a single move you can do the following sequence of actions:

- choose any valid index $ i $ ( $ 1 \le i \le n $ ),
- move the $ i $ -th character of $ s $ from its position to the beginning of the string or move the $ i $ -th character of $ s $ from its position to the end of the string.

Note, that the moves don't change the length of the string $ s $ . You can apply a move only to the string $ s $ .

For example, if $ s= $ "test" in one move you can obtain:

- if $ i=1 $ and you move to the beginning, then the result is "test" (the string doesn't change),
- if $ i=2 $ and you move to the beginning, then the result is "etst",
- if $ i=3 $ and you move to the beginning, then the result is "stet",
- if $ i=4 $ and you move to the beginning, then the result is "ttes",
- if $ i=1 $ and you move to the end, then the result is "estt",
- if $ i=2 $ and you move to the end, then the result is "tste",
- if $ i=3 $ and you move to the end, then the result is "tets",
- if $ i=4 $ and you move to the end, then the result is "test" (the string doesn't change).

You want to make the string $ s $ equal to the string $ t $ . What is the minimum number of moves you need? If it is impossible to transform $ s $ to $ t $ , print -1.

## 说明/提示

In the first example, the moves in one of the optimal answers are:

- for the first test case $ s= $ "iredppipe", $ t= $ "piedpiper": "iredppipe" $ \rightarrow $ "iedppiper" $ \rightarrow $ "piedpiper";
- for the second test case $ s= $ "estt", $ t= $ "test": "estt" $ \rightarrow $ "test";
- for the third test case $ s= $ "tste", $ t= $ "test": "tste" $ \rightarrow $ "etst" $ \rightarrow $ "test".

## 样例 #1

### 输入

```
3
9
iredppipe
piedpiper
4
estt
test
4
tste
test
```

### 输出

```
2
1
2
```

## 样例 #2

### 输入

```
4
1
a
z
5
adhas
dasha
5
aashd
dasha
5
aahsd
dasha
```

### 输出

```
-1
2
2
3
```

# AI分析结果

### 题目内容中文重写
# 中间展开

## 题目描述
这个问题的灵感来源于《魔笛手》的故事。在受到Hooli的压缩竞争对手Nucleus的挑战后，理查德熬了一整晚，发明了一种新的压缩方法：中间展开。

给定两个长度相同的字符串 $s$ 和 $t$，长度均为 $n$。它们的字符从左到右（即从开头到结尾）编号为 $1$ 到 $n$。

在一次移动中，你可以执行以下一系列操作：
- 选择任何有效的索引 $i$（$1 \leq i \leq n$）；
- 将字符串 $s$ 的第 $i$ 个字符从其当前位置移动到字符串的开头，或者将字符串 $s$ 的第 $i$ 个字符从其当前位置移动到字符串的末尾。

请注意，这些移动不会改变字符串 $s$ 的长度。你只能对字符串 $s$ 进行移动操作。

例如，如果 $s =$ "test"，在一次移动中你可以得到：
- 如果 $i = 1$ 并移动到开头，结果是 "test"（字符串不变）；
- 如果 $i = 2$ 并移动到开头，结果是 "etst"；
- 如果 $i = 3$ 并移动到开头，结果是 "stet"；
- 如果 $i = 4$ 并移动到开头，结果是 "ttes"；
- 如果 $i = 1$ 并移动到结尾，结果是 "estt"；
- 如果 $i = 2$ 并移动到结尾，结果是 "tste"；
- 如果 $i = 3$ 并移动到结尾，结果是 "tets"；
- 如果 $i = 4$ 并移动到结尾，结果是 "test"（字符串不变）。

你希望使字符串 $s$ 等于字符串 $t$。你最少需要多少次移动？如果无法将 $s$ 转换为 $t$，则输出 $-1$。

## 说明/提示
在第一个示例中，其中一个最优答案的移动步骤如下：
- 对于第一个测试用例，$s =$ "iredppipe"，$t =$ "piedpiper"："iredppipe" $\rightarrow$ "iedppiper" $\rightarrow$ "piedpiper"；
- 对于第二个测试用例，$s =$ "estt"，$t =$ "test"："estt" $\rightarrow$ "test"；
- 对于第三个测试用例，$s =$ "tste"，$t =$ "test"："tste" $\rightarrow$ "etst" $\rightarrow$ "test"。

## 样例 #1
### 输入
```
3
9
iredppipe
piedpiper
4
estt
test
4
tste
test
```
### 输出
```
2
1
2
```

## 样例 #2
### 输入
```
4
1
a
z
5
adhas
dasha
5
aashd
dasha
5
aahsd
dasha
```
### 输出
```
-1
2
2
3
```

### 算法分类
字符串

### 综合分析与结论
该题解的核心思路是通过暴力枚举的方式找出字符串 $S$ 的子序列和字符串 $T$ 的子串的最大公共长度，这个长度就是不需要进行操作的字符数量，用总长度减去这个长度就得到了最少的移动次数。同时，通过建桶比较两个字符串中各个字符的出现次数来判断是否有解。

思路方面，直接采用暴力枚举，虽然利用了数据范围小的特点，但对于较大数据可能会超时。算法要点在于子序列和子串最大公共长度的计算以及无解情况的判断。解决的难点在于如何准确地找出最大公共长度，以及对无解情况的处理。

### 题解情况
- 星级：3星
- 关键亮点：思路清晰，对题目进行了详细的分析，补充了题目中需要注意的点，代码实现相对简单，适合初学者理解。
- 个人心得：作者提到题目翻译过于简洁，自己作为英语蒟蒻只能看翻译，还吐槽了程序里把 $S$ 和 $T$ 弄反了但认为问题不大，反映出在做题过程中可能会遇到翻译不清晰和粗心的问题。

### 重点代码
```cpp
int doit(int x) {
    int now = 0 , res = 0 , ans = 0;
    for(int k = 0 ; k < x ; k ++){//枚举以串T中每个字符开头
        res = 0;//每个字符开头的最大长度
        now = 0;//串S中的枚举用的指针
        for(int i = k ; i < x ; i ++) {
            int fl = 0;
            for(int j = now ; j < x ; j ++) {
                if(T[j] == S[i]) {
                    now = j + 1;
                    res++;
                    fl = 1;
                    break;
                }
            }
            if(!fl)//如果T中有一个字符无法被S中的字符匹配，就直接跳出，计算下一个字符。
                break;
            ans = max(ans , res);
        }
    }
    return ans;
}

int main(void) {
    cin >> Q;
    while(Q--) {
        cin >> n >> T >> S;
        int fl = 0;
        memset(t1,0,sizeof(t1));
        memset(t2,0,sizeof(t2));
        for(int i = 0 ; i < n ; i ++ )
            t1[T[i]-'a']++;
        for(int i = 0 ; i < n ; i ++ )
            t2[S[i]-'a']++;
        for(int i = 0 ; i < 28 ; i ++ )//建桶暴力判断是否有解
            if(t1[i] != t2[i]) {
                cout << "-1" <<endl;
                fl = 1;
                break;
            }
        if(!fl)
            cout <<n - doit(n) << endl;
    }
}
```
**核心实现思想**：`doit` 函数通过三重循环暴力枚举字符串 $T$ 的每个字符作为开头，找出与字符串 $S$ 的子序列的最大公共长度。`main` 函数中，先读取输入，然后通过建桶比较两个字符串中各个字符的出现次数判断是否有解，若有解则输出总长度减去最大公共长度的结果。

### 可拓展思路
同类型题可以考虑增加字符串的长度和复杂度，或者改变操作规则，如可以进行多次字符的移动等。类似算法套路可以是通过枚举子序列或子串来解决字符串匹配和转换的问题。

### 洛谷推荐题目
1. P1055 [NOIP2008 普及组] ISBN 号码
2. P1125 [NOIP2008 提高组] 笨小猴
3. P1308 [NOIP2011 普及组] 统计单词数

---
处理用时：42.65秒