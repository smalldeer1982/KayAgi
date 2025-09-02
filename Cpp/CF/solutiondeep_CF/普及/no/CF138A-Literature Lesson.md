# 题目信息

# Literature Lesson

## 题目描述

Vera adores poems. All the poems Vera knows are divided into quatrains (groups of four lines) and in each quatrain some lines contain rhymes.

Let's consider that all lines in the poems consist of lowercase Latin letters (without spaces). Letters "a", "e", "i", "o", "u" are considered vowels.

Two lines rhyme if their suffixes that start from the $ k $ -th vowels (counting from the end) match. If a line has less than $ k $ vowels, then such line can't rhyme with any other line. For example, if $ k=1 $ , lines $ commit $ and $ hermit $ rhyme (the corresponding suffixes equal $ it $ ), and if $ k=2 $ , they do not rhyme ( $ ommit≠ermit $ ).

Today on a literature lesson Vera learned that quatrains can contain four different schemes of rhymes, namely the following ones (the same letters stand for rhyming lines):

- Clerihew ( $ aabb $ );
- Alternating ( $ abab $ );
- Enclosed ( $ abba $ ).

If all lines of a quatrain pairwise rhyme, then the quatrain can belong to any rhyme scheme (this situation is represented by $ aaaa $ ).

If all quatrains of a poem belong to the same rhyme scheme, then we can assume that the whole poem belongs to this rhyme scheme. If in each quatrain all lines pairwise rhyme, then the rhyme scheme of the poem is $ aaaa $ . Let us note that it doesn't matter whether lines from different quatrains rhyme with each other or not. In other words, it is possible that different quatrains aren't connected by a rhyme.

Vera got a long poem as a home task. The girl has to analyse it and find the poem rhyme scheme. Help Vera cope with the task.

## 说明/提示

In the last sample both quatrains have rhymes but finding the common scheme is impossible, so the answer is "NO".

## 样例 #1

### 输入

```
1 1
day
may
sun
fun
```

### 输出

```
aabb
```

## 样例 #2

### 输入

```
1 1
day
may
gray
way
```

### 输出

```
aaaa
```

## 样例 #3

### 输入

```
2 1
a
a
a
a
a
a
e
e
```

### 输出

```
aabb
```

## 样例 #4

### 输入

```
2 1
day
may
sun
fun
test
hill
fest
thrill
```

### 输出

```
NO
```

# AI分析结果



### 题目重述
# 诗歌课

## 题目描述

薇拉喜欢诗歌。她所知道的诗歌都分为四行诗节（四行一组），每个四行诗中某些行押韵。

所有诗句由小写字母组成（无空格）。元音字母包括"a","e","i","o","u"。

两行押韵的条件是：从倒数第k个元音开始的后缀完全匹配。若某行的元音数量不足k个，则该行无法与其他行押韵。例如k=1时，"commit"与"hermit"押韵（后缀为"it"），而k=2时不押韵（"ommit"≠"ermit"）。

四行诗的押韵模式有三种：
- Clerihew（aabb）
- Alternating（abab）
- Enclosed（abba）

若四行全部押韵（aaaa），则属于所有模式。所有四行诗必须属于同一押韵模式时，才能确定整首诗的押韵模式。若所有四行诗都是aaaa模式，则整体类型为aaaa。

给定一首长诗，请判断其押韵模式，若无法确定则输出"NO"。

### 算法分类
模拟

### 题解分析与结论

各题解核心思路一致，均通过提取每行后缀判断押韵模式，差异在于类型合并的处理方式：

1. **类型兼容处理**：aaaa类型需兼容其他三种类型
2. **全局一致性判断**：需保证所有四行诗的类型一致（允许存在aaaa）
3. **错误处理**：任意四行诗无法归类时立即终止

关键优化点：
- **位运算标记法**（forgotmyhandle）：将类型映射为二进制位，通过或运算快速判断冲突
- **集合判重法**（Jerrywang09）：利用集合存储非aaaa类型，通过集合大小判断冲突
- **后缀预处理**：统一提取每行的k元音后缀，简化比较逻辑

### 高分题解推荐

#### 1. forgotmyhandle（4星）
**亮点**：位运算高效处理类型兼容，代码简洁  
**核心思路**：
- 类型编码：aabb(1)、abab(2)、abba(4)、aaaa(0)、错误(7)
- 通过或运算累积类型，最终检查结果是否为单一位模式
```cpp
int ans = 0;
while(n--) {
    ps[i].getr(); // 获取当前四行诗类型
    ans |= ps[i].r; // 位或累积类型
}
// 结果需为0/1/2/4中的一种
cout << conv(ans); // 转换为字符串输出
```

#### 2. Jerrywang09（4星）
**亮点**：集合管理非aaaa类型，逻辑清晰  
**核心逻辑**：
```cpp
set<string> S;
for(int i=0; i<n; i++) {
    if(a[i]=="aaaa") continue;
    S.insert(a[i]); 
    if(S.size()>=2) { // 存在冲突类型
        cout << "NO"; 
        return 0;
    }
}
// 输出唯一类型或aaaa
cout << (S.empty() ? "aaaa" : *S.begin());
```

#### 3. 斜揽残箫（3.5星）
**亮点**：标志位记录可能类型，逐步排除  
**优化点**：处理特殊情况的顺序影响判断效率

### 关键代码实现
提取k元音后缀的通用写法：
```cpp
string getSuffix(string s, int k) {
    int cnt = 0, pos = -1;
    for(int i = s.size()-1; i >= 0; i--) {
        if(strchr("aeiou", s[i])) cnt++;
        if(cnt == k) { pos = i; break; }
    }
    return (pos == -1) ? "" : s.substr(pos);
}
```

### 拓展建议
同类问题可考虑：
1. 模式匹配的变体（如允许部分匹配）
2. 动态k值处理
3. 多语言字符集扩展

### 推荐习题
1. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)（字符串处理与排序）
2. [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)（模式匹配）
3. [CF112A Petya and Strings](https://codeforces.com/problemset/problem/112/A)（字符串比较）

### 心得体会摘录
- **斜揽残箫**："处理类型兼容时要特别注意优先级，aaaa的判断必须最先进行"
- **forgotmyhandle**："位运算的巧妙使用极大简化了类型合并的判断逻辑"
- **Jerrywang09**："集合的size判断比维护多个flag更直观，注意处理空集情况"

调试经验表明，元音计数时的边界条件（如k=0）和字符串截取位置是常见错误点，需重点验证。

---
处理用时：91.84秒