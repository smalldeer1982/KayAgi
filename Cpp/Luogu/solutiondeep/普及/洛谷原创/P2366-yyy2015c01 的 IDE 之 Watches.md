# 题目信息

# yyy2015c01 的 IDE 之 Watches

## 题目背景

在 2020 年的某一天，我们的 yyy2015c01 同学想要开发一套 IDE。

## 题目描述

作为他开发团队中的一员，你不幸地被选入了 Debugger 的开发组。

yyy2015c01 设想的 Debugger 由几部分组成，其中的一个小组件就是 Watches——中文称之为“变量观察器”。

由于 IDE 目前还是内测版，开发组需要先编一个能观察 int 类型变量值的 Watches 来看看效果如何。这个任务交由你来完成。

开发组假想的 Watches 能实现如下 3 种语句运行后监测相应变量值的功能：
- `n=1;` 将常量赋给变量，保证这个常量的位数不大于 $9$。
- `a=b;` 变量之间赋值：若原变量（在本例中是 $b$）未被赋值则认为其初始值为 $0$。
- `m=1+2;` $A+B$ 表达式赋值，只有 `+` 且只有两个数或者变量，$A$ 和 $B$ 都介于 $1$ 至 $10^6$ 之间。

请你编写一个 Watches，并在所有语句运行完后对所有被赋值过的变量按标识符的字典序输出它们的值（保证不会有变量的值大于 int 的最大值）。


## 说明/提示

数据很弱，直接模拟过哟~

（别想着变量标识符只有一位哟！）

另：向本题主人公 yyy2015c01 同学致敬！

## 样例 #1

### 输入

```
3
a=233;
b=a;
c=a+b;```

### 输出

```
a 233
b 233
c 466```

## 样例 #2

### 输入

```
3
a=233;
b=1+1;
a=b;```

### 输出

```
a 2
b 2```

# AI分析结果

### 综合分析与结论
这些题解均围绕字符串处理与模拟来解决题目要求。思路上，先读取赋值语句，将其拆分为变量与赋值两部分，再对赋值部分按有无 '+' 及操作数类型（数字或变量）进行分类处理，最后按字典序输出变量及其值。

算法要点在于字符串分割、类型判断、变量值计算与存储。解决难点主要是处理好不同类型的赋值情况，以及确保变量值的正确更新与存储。

多数题解使用 `map` 存储变量值，因其自带排序且便于通过变量名查找值。部分题解采用自定义结构体数组存储变量信息。在字符串处理上，有使用 `scanf` 的黑名单字符集功能、`string` 相关函数、循环遍历等方式。

### 所选的题解
- **作者：Okimoto (5星)**
  - **关键亮点**：思路清晰，详细拆解题目为输入、字符串处理和变量赋值、按字典序输出三部分。代码简洁，利用 `scanf` 的特性输入，`map` 存储变量，`algorithm` 库的 `sort` 函数排序，整体结构紧凑，可读性高。
  - **个人心得**：无
  - **重点代码**：
```cpp
// 输入
scanf("%d\n", &n); 
for(int i = 0; i < n; ++ i){
    char aa[32];
    char bb[32];
    scanf("%[^=]=", aa); 
    string a = aa;
    scanf("%[^;];\n", bb); 
    string b = bb;
    // 字符串处理和变量赋值
    if('0' <= b[0] && b[0] <= '9'){ 
        int sum = 0; 
        int tmp = 0; 
        int j;
        for(j = 0; j < (int)b.size() && b[j]!= '+'; j ++){
            sum *= 10;
            sum += b[j] - '0';
        }
        for(j = j + 1; j < (int)b.size(); j ++){
            tmp *= 10;
            tmp += b[j] - '0';
        }
        sum += tmp;
        if(mp.end() == mp.find(a)){ 
            ans[ptr ++] = a; 
            mp.insert(mp.begin(), pair<string, int>(a, sum)); 
        }
        else
            mp[a] = sum; 
    }
    else{ 
        string x; 
        string y; 
        bool yFlg = true; 
        int j;
        for(j = 0; j < (int)b.size() && b[j]!= '+'; j ++)
            x += b[j];
        for(j = j + 1; j < (int)b.size(); j ++){
            yFlg = false;
            y += b[j];
        }
        if(yFlg)
            y = "__NULL__";
        int sum = mp[x] + mp[y];
        if(mp.end() == mp.find(a)){
            ans[ptr ++] = a;
            mp.insert(mp.end(), pair<string, int>(a, sum));
        }
        else
            mp[a] = sum;
    }
}
// 字典序排序与输出
sort(ans, ans + ptr, cmp);
for(int i = 0; i < ptr; i ++)
    printf("%s %d\n", ans[i].c_str(), mp[ans[i]]);
```
  - **核心实现思想**：通过 `scanf` 读取赋值语句，对赋值部分根据首字符判断是数字还是变量类型。若为数字，进一步处理含 '+' 的情况并计算值；若为变量，拆分并获取对应变量值相加。将变量及其值存入 `map`，同时记录变量名到数组，最后对数组排序并按序输出变量及其值。

- **作者：a___ (4星)**
  - **关键亮点**：代码简洁高效，充分利用 `map` 和 `string` 的特性。使用 `map` 直接存储变量值，通过 `string` 的 `find` 和 `substr` 函数快速分割字符串，逻辑清晰，代码量少。
  - **个人心得**：无
  - **重点代码**：
```cpp
while(n--)
{
    cin>>s;
    s.erase(s.size()-1,1); 
    a=s.find('='); 
    sa=s.substr(0,a); 
    s.erase(0,a+1); 
    a=s.find('+'); 
    if(a>=0&&a<s.size())
    {
        if(s[0]>='a'&&s[0]<='z')ma[sa]=ma[s.substr(0,a)];
        else ma[sa]=tonum(s.substr(0,a));
        s.erase(0,a+1); 
        if(s[a+1]>='a'&&s[a+1]<='z')ma[sa]+=ma[s];
        else ma[sa]+=tonum(s);
    }
    else
    if(s[0]>='a'&&s[0]<='z')ma[sa]=ma[s];
    else ma[sa]=tonum(s);
}
for(iter=ma.begin();iter!=ma.end();iter++)
    cout<<iter->first<<' '<<iter->second<<endl;
```
  - **核心实现思想**：读入语句后，先删除末尾分号，通过 `find` 找到 '=' 分割出变量名，再对剩余部分找 '+'。根据 '+' 前后字符判断是变量还是数字，从 `map` 取值或转换字符串为数字进行赋值操作，最后遍历 `map` 输出变量及其值。

- **作者：fjy666 (4星)**
  - **关键亮点**：利用 `scanf` 的字符集特性巧妙分割字符串，对不同情况分类讨论清晰。注释详细，便于理解，同时给出了调试建议。
  - **个人心得**：无
  - **重点代码**：
```cpp
while (n--)
{
    scanf("%s",cmd);
    sscanf(cmd,"%[^=]%*c%[^;]%*c",left,right);
    if (strchr(right,'+') == NULL)
    {
        if (right[0] >= '0' && right[0] <= '9')
        {
            int tmp = 0;
            sscanf(right,"%d",&tmp); 
            variables[string(left)] = tmp; 
        } else {
            int tmp = 0;
            if (variables.count(string(right)))
                tmp = variables[string(right)];
            variables[string(left)] = tmp;
        }
    } else {
        sscanf(right,"%[^+]%*c%s",r_1,r_2);
        int p_1 = 0,p_2 = 0;
        if(r_1[0] >= '0' && r_1[0] <= '9')
            sscanf(r_1,"%d",&p_1);
        else 
            if (variables.count(string(r_1)))
                p_1 = variables[string(r_1)];
        if(r_2[0] >= '0' && r_2[0] <= '9')
            sscanf(r_2,"%d",&p_2);
        else 
            if (variables.count(string(r_2)))
                p_2 = variables[string(r_2)];
        variables[string(left)] = p_1 + p_2;
    }
}
for(map<string,int>::iterator it = variables.begin(); it!= variables.end(); ++it)
    printf("%s %d\n",it->first.c_str(),it->second);
```
  - **核心实现思想**：用 `scanf` 和 `sscanf` 分割输入语句，对于无 '+' 的情况，判断赋值部分是数字则转换赋值，是变量则从 `map` 取值赋值；有 '+' 时，同样判断两边是数字还是变量，分别取值或转换后相加赋值，最后遍历 `map` 输出。

### 最优关键思路或技巧
- **数据结构选择**：使用 `map<string, int>` 存储变量名与变量值的键值对，方便根据变量名快速查找和更新值，且 `map` 自带按 key（变量名）字典序排序，便于最后输出。
- **字符串处理技巧**：利用 `scanf` 的特殊格式控制符（如 `%[^=]`）或 `string` 的 `find`、`substr` 等函数，高效分割字符串，提取变量名和赋值表达式。
- **分类讨论**：对赋值表达式按有无 '+' 以及操作数是数字还是变量进行细致分类讨论，确保每种情况都能正确处理。

### 可拓展之处
同类型题常涉及字符串模拟、变量表达式求值等。类似算法套路包括根据特定规则解析字符串，结合合适的数据结构存储中间结果，对不同情况分类处理。例如处理更复杂的表达式（含多种运算符、括号等），可考虑使用栈来实现表达式求值。

### 相似知识点洛谷题目
- **P1046 [NOIP2005 普及组] 陶陶摘苹果**：涉及简单的条件判断与模拟，与本题处理不同情况的思路类似。
- **P1909 [NOIP2016 普及组] 买铅笔**：通过模拟不同购买方案来求解最优解，锻炼模拟和分类讨论能力。
- **P5732 [深基5.例3] 冰雹猜想**：根据给定规则进行模拟计算，与本题按规则处理变量赋值类似。

### 个人心得摘录与总结
- **作者：happybob**：读入方式影响结果，`scanf` 提交可能 MLE，`cin` 提交可能因 `\n` 出问题，`cin.get` 及 `getchar` 提交也可能 MLE，需谨慎选择读入方式。总结为在处理输入时，要充分考虑不同输入函数的特性及可能出现的问题，避免因输入问题导致错误。 

---
处理用时：61.85秒