# 题目信息

# Vasya and Types

## 题目描述

Programmer Vasya is studying a new programming language &K\*. The &K\* language resembles the languages of the C family in its syntax. However, it is more powerful, which is why the rules of the actual C-like languages are unapplicable to it. To fully understand the statement, please read the language's description below carefully and follow it and not the similar rules in real programming languages.

There is a very powerful system of pointers on &K\* — you can add an asterisk to the right of the existing type $ X $ — that will result in new type $ X* $ . That is called pointer-definition operation. Also, there is the operation that does the opposite — to any type of $ X $ , which is a pointer, you can add an ampersand — that will result in a type $ &amp;X $ , to which refers $ X $ . That is called a dereference operation.

The &K\* language has only two basic data types — void and errtype. Also, the language has operators typedef and typeof.

- The operator "typedef $ A $ $ B $ " defines a new data type $ B $ , which is equivalent to $ A $ . $ A $ can have asterisks and ampersands, and $ B $ cannot have them. For example, the operator typedef void\*\* ptptvoid will create a new type ptptvoid, that can be used as void\*\*.
- The operator "typeof $ A $ " returns type of $ A $ , brought to void, that is, returns the type void\*\*...\*, equivalent to it with the necessary number of asterisks (the number can possibly be zero). That is, having defined the ptptvoid type, as shown above, the typeof ptptvoid operator will return void\*\*.

An attempt of dereferencing of the void type will lead to an error: to a special data type errtype. For errtype the following equation holds true: errtype\* $ = $ &errtype $ = $ errtype. An attempt to use the data type that hasn't been defined before that will also lead to the errtype.

Using typedef, we can define one type several times. Of all the definitions only the last one is valid. However, all the types that have been defined earlier using this type do not change.

Let us also note that the dereference operation has the lower priority that the pointer operation, in other words $ &amp;T* $ is always equal to $ T $ .

Note, that the operators are executed consecutively one by one. If we have two operators "typedef &void a" and "typedef a\* b", then at first a becomes errtype, and after that b becomes errtype\* = errtype, but not &void\* = void (see sample 2).

Vasya does not yet fully understand this powerful technology, that's why he asked you to help him. Write a program that analyzes these operators.

## 说明/提示

Let's look at the second sample.

After the first two queries typedef the b type is equivalent to void\*, and с — to void\*\*.

The next query typedef redefines b — it is now equal to &b = &void\* = void. At that, the с type doesn't change.

After that the с type is defined as &&b\* = &&void\* = &void = errtype. It doesn't influence the b type, that's why the next typedef defines c as &void\* = void.

Then the b type is again redefined as &void = errtype.

Please note that the c type in the next query is defined exactly as errtype\*\*\*\*\*\*\* = errtype, and not &void\*\*\*\*\*\*\* = void\*\*\*\*\*\*. The same happens in the last typedef.

## 样例 #1

### 输入

```
5
typedef void* ptv
typeof ptv
typedef &&ptv node
typeof node
typeof &ptv
```

### 输出

```
void*
errtype
void
```

## 样例 #2

### 输入

```
17
typedef void* b
typedef b* c
typeof b
typeof c
typedef &b b
typeof b
typeof c
typedef &&b* c
typeof c
typedef &b* c
typeof c
typedef &void b
typeof b
typedef b******* c
typeof c
typedef &&b* c
typeof c
```

### 输出

```
void*
void**
void
void**
errtype
void
errtype
errtype
errtype
```

# AI分析结果

### 题目内容
# Vasya和类型

## 题目描述
程序员Vasya正在学习一种新的编程语言 &K*。&K* 语言在语法上类似于C家族的语言。然而，它更强大，这就是为什么实际C类语言的规则不适用于它。为了完全理解该语句，请仔细阅读下面的语言描述，并遵循它，而不是真实编程语言中的类似规则。

在 &K* 中有一个非常强大的指针系统——你可以在现有类型 $X$ 的右边添加一个星号，这将产生新类型 $X*$。这被称为指针定义操作。还有一个相反的操作——对于任何指针类型 $X$，你可以添加一个与号，这将产生一个类型 $&X$，$X$ 指向它。这被称为解引用操作。

&K* 语言只有两种基本数据类型——void 和 errtype。此外，该语言还有 typedef 和 typeof 运算符。
 - “typedef $A$ $B$” 运算符定义一个新的数据类型 $B$，它等同于 $A$。$A$ 可以有星号和与号，而 $B$ 不能有。例如，“typedef void** ptptvoid” 运算符将创建一个新类型 ptptvoid，它可以像 void** 一样使用。
 - “typeof $A$” 运算符返回 $A$ 的类型，并转换为 void，也就是说，返回等同于它的带有必要数量星号的 void***...* 类型（星号数量可能为零）。也就是说，如上面所示定义了 ptptvoid 类型后，“typeof ptptvoid” 运算符将返回 void**。

对 void 类型进行解引用的尝试将导致错误，即产生一个特殊的数据类型 errtype。对于 errtype，以下等式成立：errtype* = &errtype = errtype。尝试使用之前未定义的数据类型也将导致 errtype。

使用 typedef，我们可以多次定义一种类型。在所有定义中，只有最后一个是有效的。但是，所有之前使用该类型定义的类型不会改变。

我们还要注意，解引用操作的优先级低于指针操作，换句话说，$&T*$ 始终等于 $T$。

注意，运算符是一个接一个连续执行的。如果我们有两个运算符 “typedef &void a” 和 “typedef a* b”，那么首先 a 变为 errtype，然后 b 变为 errtype* = errtype，而不是 &void* = void（见示例2）。

Vasya 还没有完全理解这项强大的技术，所以他请你帮助他。编写一个程序来分析这些运算符。

## 说明/提示
让我们看一下第二个示例。

在前两个 typedef 查询之后，b 类型等同于 void*，c 等同于 void**。

下一个 typedef 查询重新定义 b，现在它等于 &b = &void* = void。此时，c 类型不变。

之后，c 类型被定义为 &&b* = &&void* = &void = errtype。这不会影响 b 类型，所以下一个 typedef 将 c 定义为 &void* = void。

然后 b 类型再次被重新定义为 &void = errtype。

请注意，下一个查询中的 c 类型被准确地定义为 errtype****** = errtype，而不是 &void****** = void*****。最后一个 typedef 也是如此。

## 样例 #1
### 输入
```
5
typedef void* ptv
typeof ptv
typedef &&ptv node
typeof node
typeof &ptv
```
### 输出
```
void*
errtype
void
```

## 样例 #2
### 输入
```
17
typedef void* b
typedef b* c
typeof b
typeof c
typedef &b b
typeof b
typeof c
typedef &&b* c
typeof c
typedef &b* c
typeof c
typedef &void b
typeof b
typedef b******* c
typeof c
typedef &&b* c
typeof c
```
### 输出
```
void*
void**
void
void**
errtype
void
errtype
errtype
errtype
```

### 算法分类
模拟

### 题解综合分析与结论
这些题解的核心思路都是围绕题目中 &K* 语言的规则进行模拟。要点在于处理 typedef 和 typeof 这两种操作，通过某种数据结构（多数使用 map）来记录类型定义关系以及各类型中 `*` 和 `&` 的数量变化，从而确定每个类型最终的表示。难点在于理解并正确实现语言中指针定义、解引用操作的优先级，以及处理 errtype 相关的特殊情况，如未定义类型、对 void 解引用等导致的 errtype 情况。各题解整体思路相近，主要差异体现在代码实现的细节和简洁性上。

### 所选的题解
 - **作者：Empty_Dream (5星)**
    - **关键亮点**：思路清晰，代码简洁高效。通过 map 记录类型对应 `*` 的个数和 `&` 的个数差，利用一个函数 type 统一处理类型解析，减少重复代码。对不合法情况判断巧妙，仅通过记录 `*` 和 `&` 的数量差是否为负来判断，简化了代码逻辑。
    - **重点代码**：
```cpp
int type(string s){
    int cnt1 = 0, cnt2 = 0;
    while (s[0] == '&'){//题目确保了'&'一定在字符串前面，'*'在后面
        cnt1++;
        s.erase(0, 1);
    }
    while (s[s.size() - 1] == '*'){
        cnt2++;
        s.erase(s.size() - 1, 1);
    }
    if (mp.count(s) == 0) return -1;//之前没有定义过这种类型
    int t = mp[s];
    if (t == -1) return -1;//如果是errtype
    t += cnt2 - cnt1;//记录'*'和'&'的数量差
    if (t < 0) t = -1;//'*'比'&'少 不合法
    return t;
}

void run_typedef(){
    string s1, s2;
    cin >> s1 >> s2;
    mp[s2] = type(s1);
} 

void run_typeof(){
    string s;
    cin >> s;
    int t = type(s);//还原出要加多少个'*'或者不合法
    if (t == -1) cout << "errtype\n";
    else{
        cout << "void";
        for(int i = 1; i <= t; i++) cout << "*";
        cout << endl;
    }
}
```
    - **核心实现思想**：`type` 函数负责解析输入字符串，计算 `*` 和 `&` 的数量差，并结合 map 中已记录的类型信息判断最终类型是否合法。`run_typedef` 函数根据 `type` 函数的结果更新 map 中类型的定义。`run_typeof` 函数通过调用 `type` 函数获取类型信息并输出。

 - **作者：The_Godfather (4星)**
    - **关键亮点**：思路直接，通过统计 `*` 的个数并减去 `&` 的个数来确定类型，逻辑较为清晰。代码实现中利用 `map` 存储类型信息，并且在处理 `typedef` 和 `typeof` 操作时，代码结构较为规整。
    - **重点代码**：
```cpp
while (scanf("%d", &n)!= EOF)
{
    mp.clear();
    mp["void"] = 1;
    for (int i = 0; i < n; i++)
    {
        scanf("%s", s);
        if (strcmp(s, "typedef") == 0)
        {
            scanf("%s %s", ss, sss);
            int l = strlen(ss);
            int ans = 0, cnt = 0;
            str1 = "";
            for (int i = 0; i < l; i++)
            {
                if (ss[i] == '&')
                    ans--;
                else if (ss[i] == '*')
                    ans++;
                else
                    str1 += ss[i];
            }
            cnt = mp[str1];
            if (cnt > 0)
                cnt += ans;
            else
                cnt = 0;
            mp[(string)sss] = cnt;
        }
        else
        {
            scanf("%s", ss);
            int l = strlen(ss);
            int ans = 0, cnt = 0;
            str1 = "";
            for (int i = 0; i < l; i++)
            {
                if (ss[i] == '&')
                    ans--;
                else if (ss[i] == '*')
                    ans++;
                else
                    str1 += ss[i];
            }
            cnt = mp[str1];
            if (cnt > 0)
                cnt += ans;
            else
                cnt = 0;
            if (cnt <= 0)
                puts("errtype");
            else
            {
                printf("void");
                for (int i = 1; i < cnt; i++)
                    printf("*");
                puts("");
            }
        }
    }
}
```
    - **核心实现思想**：在循环中，根据输入的操作类型（`typedef` 或 `typeof`）分别进行处理。对于 `typedef`，统计输入类型字符串中 `*` 和 `&` 的数量差，结合 map 中已有类型信息更新新类型的 `*` 个数。对于 `typeof`，同样统计数量差，根据最终 `*` 个数输出相应类型。

 - **作者：_Lazy_zhr_ (4星)**
    - **关键亮点**：使用 `map` 记录每个类型 `*` 的个数，思路明确。在处理 `typedef` 操作时，详细地考虑了各种情况，如类型未定义、类型为 `errtype` 等，逻辑严谨。
    - **重点代码**：
```cpp
if(op==def){
    cin>>b;
    int _0=0,_1=0;
    string over="";//去除 & 和 * 后的 a。
    for(int i=0;i<a.size();i++) if(a[i]=='&') _0++;
    else if(a[i]=='*') _1++;
    else over=over+a[i];
    int cnt=f[over],w=f[b];
    if(cnt==-1){//a 是 err
        if(w==-1) er.erase(er.find(b));
        else if(s[w].find(b)!=s[w].end()) s[w].erase(s[w].find(b));//b 之前存在过。
        er.insert(b);
        f[b]=-1;
    }
    else if(s[cnt].find(over)==s[cnt].end()){//之前没 a。
        if(w==-1) er.erase(er.find(b));
        else if(s[w].find(b)!=s[w].end()) s[w].erase(s[w].find(b));//b 之前存在过。
        er.insert(b);
        f[b]=-1;
        er.insert(a);
        f[a]=-1;
    }
    else{//之前有 a
        if(w==-1) er.erase(er.find(b));
        else if(s[w].find(b)!=s[w].end()) s[w].erase(s[w].find(b));//b 之前存在过。
        int now=cnt+_1-_0;
        if(now<0){
            er.insert(b);
            f[b]=-1;
        }
        else{
            s[now].insert(b);
            f[b]=now;
        }
    }
}
else{
    int _0=0,_1=0;
    string over="";//去除 & 和 * 后的 a。
    for(int i=0;i<a.size();i++) if(a[i]=='&') _0++;
    else if(a[i]=='*') _1++;
    else over=over+a[i];
    int 不知道取什么=f[over];
    if(不知道取什么<0) cout<<err<<"\n";
    else if(s[不知道取什么].find(over)==s[不知道取什么].end()) cout<<err<<"\n";
    else{
        不知道取什么+=_1-_0;
        if(不知道取什么<0) cout<<err<<"\n";
        else{
            cout<<"void";
            while(不知道取什么--) cout<<'*';
            cout<<"\n";
        }
    }
}
```
    - **核心实现思想**：在 `typedef` 操作中，先去除输入类型字符串的 `*` 和 `&`，然后根据已有类型信息判断新类型是否合法，若合法则更新 `map` 中该类型的 `*` 个数。在 `typeof` 操作中，同样先处理输入字符串，再根据 `map` 信息输出相应类型。

### 最优关键思路或技巧
使用 `map` 数据结构记录类型定义关系和 `*` 的个数（或 `*` 与 `&` 的数量差），能简洁高效地处理类型查询和定义操作。同时，通过统计 `*` 和 `&` 的数量差来判断类型是否合法，简化了代码逻辑，减少了对复杂情况的分别判断。

### 可拓展之处
此类题目属于编程语言规则模拟类型，类似题目可能会涉及更多复杂的语法规则、作用域等概念。遇到这类题目，关键在于清晰梳理规则，利用合适的数据结构记录状态，按照规则逐步模拟操作。

### 相似知识点洛谷题目
 - [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)：简单的模拟日常场景中的数据处理。
 - [P1424 小鱼的航程(改进版)](https://www.luogu.com.cn/problem/P1424)：模拟小鱼在不同条件下的航程计算。
 - [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：模拟购买铅笔时不同套餐组合下的最优选择。

### 个人心得摘录与总结
 - **作者：_Lazy_zhr_**：因访问到下标为 -1 导致神秘 RE。总结为在处理字符串操作，尤其是涉及去除字符和访问字符数组时，要特别注意边界条件，避免数组越界。 

---
处理用时：108.82秒