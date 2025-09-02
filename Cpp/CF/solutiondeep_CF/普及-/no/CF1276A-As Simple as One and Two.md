# 题目信息

# As Simple as One and Two

## 题目描述

You are given a non-empty string $ s=s_1s_2\dots s_n $ , which consists only of lowercase Latin letters. Polycarp does not like a string if it contains at least one string "one" or at least one string "two" (or both at the same time) as a substring. In other words, Polycarp does not like the string $ s $ if there is an integer $ j $ ( $ 1 \le j \le n-2 $ ), that $ s_{j}s_{j+1}s_{j+2}= $ "one" or $ s_{j}s_{j+1}s_{j+2}= $ "two".

For example:

- Polycarp does not like strings "oneee", "ontwow", "twone" and "oneonetwo" (they all have at least one substring "one" or "two"),
- Polycarp likes strings "oonnee", "twwwo" and "twnoe" (they have no substrings "one" and "two").

Polycarp wants to select a certain set of indices (positions) and remove all letters on these positions. All removals are made at the same time.

For example, if the string looks like $ s= $ "onetwone", then if Polycarp selects two indices $ 3 $ and $ 6 $ , then "onetwone" will be selected and the result is "ontwne".

What is the minimum number of indices (positions) that Polycarp needs to select to make the string liked? What should these positions be?

## 说明/提示

In the first example, answers are:

- "onetwone",
- "testme" — Polycarp likes it, there is nothing to remove,
- "oneoneone",
- "twotwo".

In the second example, answers are:

- "onetwonetwooneooonetwooo",
- "two",
- "one",
- "twooooo",
- "ttttwo",
- "ttwwoo" — Polycarp likes it, there is nothing to remove,
- "ooone",
- "onnne" — Polycarp likes it, there is nothing to remove,
- "oneeeee",
- "oneeeeeeetwooooo".

## 样例 #1

### 输入

```
4
onetwone
testme
oneoneone
twotwo
```

### 输出

```
2
6 3
0

3
4 1 7 
2
1 4
```

## 样例 #2

### 输入

```
10
onetwonetwooneooonetwooo
two
one
twooooo
ttttwo
ttwwoo
ooone
onnne
oneeeee
oneeeeeeetwooooo
```

### 输出

```
6
18 11 12 1 6 21 
1
1 
1
3 
1
2 
1
6 
0

1
4 
0

1
1 
2
1 11 
```

# AI分析结果

### 题目内容
# 像一和二一样简单

## 题目描述
给定一个非空字符串 $s = s_1s_2…s_n$，它仅由小写拉丁字母组成。如果字符串中至少包含一个子串 “one” 或至少包含一个子串 “two”（或同时包含两者），那么 Polycarp 就不喜欢这个字符串。换句话说，如果存在一个整数 $j$（$1 \leq j \leq n - 2$），使得 $s_js_{j + 1}s_{j + 2} =$ “one” 或 $s_js_{j + 1}s_{j + 2} =$ “two”，Polycarp 就不喜欢字符串 $s$。

例如：
- Polycarp 不喜欢字符串 “oneee”、“ontwow”、“twone” 和 “oneonetwo”（它们都至少有一个子串 “one” 或 “two”）。
- Polycarp 喜欢字符串 “oonnee”、“twwwo” 和 “twnoe”（它们没有子串 “one” 和 “two”）。

Polycarp 想要选择一组特定的索引（位置），并删除这些位置上的所有字母。所有删除操作同时进行。

例如，如果字符串是 $s =$ “onetwone”，那么如果 Polycarp 选择索引 $3$ 和 $6$，则这两个位置的字符将被删除，结果为 “ontwne”。

Polycarp 需要选择的最小索引（位置）数量是多少才能使字符串变得受欢迎？这些位置应该是哪些？

## 说明/提示
在第一个示例中，答案如下：
- “onetwone”，
- “testme” — Polycarp 喜欢它，无需删除任何字符，
- “oneoneone”，
- “twotwo”。

在第二个示例中，答案如下：
- “onetwonetwooneooonetwooo”，
- “two”，
- “one”，
- “twooooo”，
- “ttttwo”，
- “ttwwoo” — Polycarp 喜欢它，无需删除任何字符，
- “ooone”，
- “onnne” — Polycarp 喜欢它，无需删除任何字符，
- “oneeeee”，
- “oneeeeeeetwooooo”。

## 样例 #1
### 输入
```
4
onetwone
testme
oneoneone
twotwo
```
### 输出
```
2
6 3
0

3
4 1 7 
2
1 4
```
## 样例 #2
### 输入
```
10
onetwonetwooneooonetwooo
two
one
twooooo
ttttwo
ttwwoo
ooone
onnne
oneeeee
oneeeeeeetwooooo
```
### 输出
```
6
18 11 12 1 6 21 
1
1 
1
3 
1
2 
1
6 
0

1
4 
0

1
1 
2
1 11 
```
### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路均为贪心算法，即每次做出局部最优选择，期望达到全局最优。对于子串 “one”，删除中间字符 `n` 可避免新的 “one” 产生；对于子串 “two”，一般删除 `w`，但遇到 “twone” 时删除 `o` 可同时避免 “one” 和 “two” 产生。各题解的主要区别在于代码实现方式和细节处理，如遍历方式、记录删除位置的方法等。

### 所选的题解
- **作者：vectorwyx (5星)**
    - **关键亮点**：代码结构清晰，使用 `fo` 宏简化循环，通过从左往右遍历字符串，根据不同子串情况直接确定删除位置，逻辑简洁明了。
    - **重点代码**：
```cpp
void work(){
    cin>>s;
    top=0;
    int n=s.size();
    fo(i,0,n - 3){
        if(s[i]=='o'&&s[i + 1]=='n'&&s[i + 2]=='e'){
            ans[++top]=i + 1;
            i+=2;
        }
        else if(s[i]=='t'&&s[i + 1]=='w'&&s[i + 2]=='o'){
            if(s[i + 3]=='o') ans[++top]=i + 1;
            else ans[++top]=i + 2;
            i+=2;
        }
    }
    cout<<top<<endl;
    fo(i,1,top) printf("%d ",ans[i]+1);puts("");
}
```
    - **核心实现思想**：遍历字符串，当遇到 “one” 子串，记录中间字符 `n` 的位置并跳过后续两个字符；遇到 “two” 子串，根据后续字符判断是否为 “twone”，从而确定删除 `o` 还是 `w`，并同样跳过后续两个字符。最后输出删除位置。
- **作者：安舒阳 (4星)**
    - **关键亮点**：对贪心策略的分析详细，先阐述贪心的原则是让删除字符发挥最大价值，再分情况讨论 “one” 和 “two” 子串的最佳删除字符，逻辑推导清晰。
    - **重点代码**：
```cpp
for(int i = 2; i < s.size(); i++){
    //one
    if(s[i]=='e'&&s[i - 1]=='n'&&s[i - 2]=='o'){
        ans++;
        num.push_back(i - 1);
    }
    //two
    if(s[i]=='o'&&s[i - 1]=='w'&&s[i - 2]=='t'){
        ans++;
        //twone
        bool flag = 1;
        if(i + 2 < s.size()){
            if(s[i + 1]=='n'&&s[i + 2]=='e'){
                num.push_back(i);
                flag = 0;
                i+=2;
            }
        }
        //twoXXX
        if(flag){
            num.push_back(i - 1);
        }
    }
}
```
    - **核心实现思想**：从字符串第三个字符开始遍历，判断是否为 “one” 或 “two” 子串。若是 “one” 则记录 `n` 的位置；若是 “two”，判断是否为 “twone”，是则记录 `o` 的位置，否则记录 `w` 的位置，并跳过相关字符。
- **作者：YuanZihan1225 (4星)**
    - **关键亮点**：代码简洁，利用 `vector` 记录删除位置，代码风格简洁易懂，对 “one” 和 “two” 子串的处理逻辑在循环中清晰呈现。
    - **重点代码**：
```cpp
for(int i = 0; i < n; i++){
    if(s[i] == 'o' && s[i + 1] == 'n' && s[i + 2] == 'e')
        ans.push_back(i + 2), i += 2;
    else if(s[i] == 't' && s[i + 1] == 'w' && s[i + 2] == 'o'){
        if(s[i + 3] == 'n' && s[i + 4] == 'e')
            ans.push_back(i + 3), i += 4;
        else
            ans.push_back(i + 2), i += 2;
    }
}
```
    - **核心实现思想**：遍历字符串，遇到 “one” 子串将 `n` 的位置加入 `vector` 并跳过两个字符；遇到 “two” 子串，判断后续是否为 “ne”，是则将 `o` 的位置加入 `vector` 并跳过四个字符，否则将 `w` 的位置加入 `vector` 并跳过两个字符。

### 最优关键思路或技巧
采用贪心策略，针对 “one” 和 “two” 子串分别分析最佳删除字符，在遍历字符串时直接确定删除位置，避免复杂的搜索或动态规划过程。同时，利用合适的数据结构（如 `vector`）记录删除位置，使代码简洁易读。

### 可拓展之处
此类题目属于字符串贪心问题，类似套路是对特定子串进行分析，找出既能满足条件又能使操作最优的策略。常见的拓展方向有增加子串种类、改变字符串字符类型（如大写字母、数字等）、或者对删除操作进行限制等。

### 洛谷相似题目推荐
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：通过贪心策略解决分配问题，与本题类似，需要分析不同情况找出最优分配方式。
- [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)：利用贪心算法解决生产调度问题，同样是在多种情况中选择最优策略。
- [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)：通过对数据的分析和贪心策略，解决排序和最优值计算问题，与本题在贪心策略运用上有相似之处。

### 个人心得摘录
暂无。 

---
处理用时：73.88秒