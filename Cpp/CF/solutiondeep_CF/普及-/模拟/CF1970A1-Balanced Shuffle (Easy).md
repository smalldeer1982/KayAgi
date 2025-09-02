# 题目信息

# Balanced Shuffle (Easy)

## 题目描述

A parentheses sequence is a string consisting of characters "(" and ")", for example "(()((".

A balanced parentheses sequence is a parentheses sequence which can become a valid mathematical expression after inserting numbers and operations into it, for example "(()(()))".

The balance of a parentheses sequence is defined as the number of opening parentheses "(" minus the number of closing parentheses ")". For example, the balance of the sequence "(()((" is 3.

A balanced parentheses sequence can also be defined as a parentheses sequence with balance 0 such that each of its prefixes has a non-negative balance.

We define the balanced shuffle operation that takes a parentheses sequence and returns a parentheses sequence as follows: first, for every character of the input sequence, we compute the balance of the prefix of the sequence before that character and write those down in a table together with the positions of the characters in the input sequence, for example:

Prefix balance01212321Position12345678Character(()(()))Then, we sort the columns of this table in increasing order of prefix balance, breaking ties in decreasing order of position. In the above example, we get:

Prefix balance01112223Position18427536Character()(()())The last row of this table forms another parentheses sequence, in this case "()(()())". This sequence is called the result of applying the balanced shuffle operation to the input sequence, or in short just the balanced shuffle of the input sequence.

You are given a balanced parentheses sequence. Print its balanced shuffle.

## 样例 #1

### 输入

```
(()(()))```

### 输出

```
()(()())```

# AI分析结果

### 题目翻译
# 平衡洗牌（简单版）

## 题目描述
括号序列是由字符 "(" 和 ")" 组成的字符串，例如 "(()(("。

平衡括号序列是指在插入数字和运算符后可以成为有效数学表达式的括号序列，例如 "(()(()))"。

括号序列的平衡度定义为左括号 "(" 的数量减去右括号 ")" 的数量。例如，序列 "(()((" 的平衡度为 3。

平衡括号序列也可以定义为平衡度为 0 且其每个前缀的平衡度均为非负的括号序列。

我们定义平衡洗牌操作，该操作接受一个括号序列并返回一个括号序列，具体操作如下：首先，对于输入序列的每个字符，我们计算该字符之前的序列前缀的平衡度，并将这些平衡度与字符在输入序列中的位置一起记录在一个表格中，例如：

前缀平衡度 0 1 2 1 2 3 2 1
位置 1 2 3 4 5 6 7 8
字符 ( ( ) ( ( ) ) )

然后，我们按照前缀平衡度的升序对该表格的列进行排序，当前缀平衡度相同时，按照位置的降序排序。在上述示例中，我们得到：

前缀平衡度 0 1 1 1 2 2 2 3
位置 1 8 4 2 7 5 3 6
字符 ( ) ( ( ) ( ) )

该表格的最后一行形成了另一个括号序列，在这种情况下为 "()(()())"。这个序列被称为对输入序列应用平衡洗牌操作的结果，简称为输入序列的平衡洗牌。

给定一个平衡括号序列，请输出其平衡洗牌结果。

## 样例 #1
### 输入
```
(()(()))
```
### 输出
```
()(()())
```

### 综合分析与结论
- **思路对比**：各题解思路基本一致，都是按照题目要求模拟平衡洗牌操作。先计算每个字符前的前缀平衡度，再将前缀平衡度和字符位置信息存储，接着按照前缀平衡度升序、位置降序排序，最后输出排序后的字符序列。
- **算法要点**：
    - 计算前缀平衡度：遇到 '(' 加 1，遇到 ')' 减 1。
    - 存储信息：使用结构体或元组存储前缀平衡度和位置。
    - 排序：按照前缀平衡度升序、位置降序排序。
- **解决难点**：主要难点在于正确计算前缀平衡度和实现排序规则。各题解通过不同方式解决，如使用结构体自定义比较函数、利用元组默认排序规则等。

### 题解评分
- Dream_Mr_li：4星。思路清晰，代码简洁易懂，使用结构体存储信息并自定义比较函数进行排序。
- banglee：4星。详细解释了 `tuple` 的使用，代码简洁，利用 `tuple` 的默认排序规则。
- Furina_Saikou：3星。思路正确，但代码中数组大小定义过大，可能造成空间浪费。
- OIer_Hhy：3星。思路和代码与 Dream_Mr_li 类似，但使用 `map` 存储字符对应的值，增加了不必要的复杂度。
- szhqwq：3星。仅给出思路，未提供代码实现。

### 所选题解
- **Dream_Mr_li（4星）**
    - **关键亮点**：思路清晰，代码简洁，使用结构体存储信息并自定义比较函数进行排序。
    - **核心代码**：
```c++
struct node{
    int x,y;
};
bool cmp(node aa,node bb){
    if(aa.x!=bb.x)
        return aa.x<bb.x;
    return aa.y>bb.y;
}
signed main(){
    cin>>s;
    for(int i=2;i<=s.size();i++){
        a[i].x=a[i-1].x;
        if(s[i-2]=='('){
            a[i].x++;
        }else{
            a[i].x--;
        }
        a[i].y=i-1;
    }
    sort(a+1,a+s.size()+1,cmp);
    for(int i=1;i<=s.size();i++){
        cout<<s[a[i].y];
    }
    return 0;
}
```
核心思想：先计算前缀平衡度并存储在结构体中，再对结构体数组进行排序，最后输出排序后的字符。

- **banglee（4星）**
    - **关键亮点**：详细解释了 `tuple` 的使用，代码简洁，利用 `tuple` 的默认排序规则。
    - **核心代码**：
```c++
vector<tuple<int,int,char>> a;
int main(){
    getline(cin,s);
    for(int i=0;i<s.size();i++)
    {
        a.push_back(make_tuple(b,-i,s[i]));
        if(s[i]=='(') b++;
        else if(s[i]==')') b--;
    }
    sort(a.begin(),a.end());
    for(const auto& x : a)
        res.push_back(get<2>(x));
    cout<<res;
    return 0;
}
```
核心思想：使用 `tuple` 存储前缀平衡度、位置和字符，利用 `tuple` 默认排序规则排序，最后拼接字符输出。

### 最优关键思路或技巧
- 使用结构体或元组存储前缀平衡度和位置信息，方便排序。
- 自定义比较函数或利用数据结构的默认排序规则实现排序要求。

### 拓展思路
同类型题目可能会改变排序规则或对平衡度的定义，解题关键在于理解规则并模拟操作。类似算法套路可用于处理需要根据多个条件对元素进行排序的问题。

### 洛谷相似题目推荐
- P1177 【模板】快速排序
- P1093 [NOIP2007 普及组] 奖学金
- P1271 [深基9.例1] 选举学生会

---
处理用时：29.42秒