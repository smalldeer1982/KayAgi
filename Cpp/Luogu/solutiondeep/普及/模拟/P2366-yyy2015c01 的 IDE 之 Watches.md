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
这些题解的核心思路均为通过字符串处理和模拟来实现对变量赋值语句的解析与执行，最终按字典序输出变量及其值。主要差异在于实现细节和代码风格。
1. **思路与算法要点**：多数题解采用以下步骤：读入赋值语句，分割为变量和赋值表达式两部分；判断赋值表达式的类型（数字、变量、数字+变量等），解析并计算表达式的值；将变量和值存入合适的数据结构；最后按字典序输出变量及其值。部分题解利用`map`存储变量与值的键值对，因其自带排序功能可简化输出步骤；部分题解使用自定义结构体数组或`vector`存储变量信息，再手动排序。
2. **解决难点**：主要难点在于准确解析不同类型的赋值表达式，如区分变量与数字、处理加法表达式中的变量和数字组合。各题解通过判断字符串首字符是否为数字、查找`+`号等方式来处理。同时，还需注意变量未赋值时初始值为0的设定。
3. **评分**：综合思路清晰度、代码可读性、优化程度等方面，对题解评分如下：
    - Okimoto：5星。思路清晰，详细阐述每一步骤，代码结构良好，利用`map`存储变量信息，`scanf`输入并结合黑名单字符集功能简化输入处理，整体简洁高效。
    - a___ ：4星。代码简洁，充分利用`map`和`string`的STL功能，通过`find`和`substr`方法处理字符串，逻辑清晰。
    - fjy666 ：4星。详细介绍思路，利用`scanf`的字符集特性分割字符串，分类讨论不同赋值情况，代码注释详细，可读性强。

### 所选题解
1. **作者：Okimoto (5星)**
    - **关键亮点**：思路阐述详细，代码结构清晰，巧妙运用`scanf`的黑名单字符集功能输入，`map`存储变量，`sort`结合自定义比较函数实现字典序输出。
    - **重点代码核心实现思想**：通过`scanf`按特定格式读入变量和表达式，判断表达式类型，数字类型则拆分求和，变量类型则从`map`取值求和，最后将变量和值存入`map`，并对记录变量名的数组排序后输出。
    - **核心代码片段**：
```cpp
bool cmp(string a, string b){
    return a < b; // 字典序
}
int main(int argc, char const *argv[]){
    mp.insert(mp.begin(), pair<string, int>("__NULL__", 0)); 
    scanf("%d\n", &n); 
    for(int i = 0; i < n; ++ i){
        char aa[32];
        char bb[32];
        scanf("%[^=]=", aa); 
        string a = aa;
        scanf("%[^;];\n", bb); 
        string b = bb;
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
    sort(ans, ans + ptr, cmp);
    for(int i = 0; i < ptr; i ++)
        printf("%s %d\n", ans[i].c_str(), mp[ans[i]]);
    return 0;
}
```
2. **作者：a___ (4星)**
    - **关键亮点**：代码简洁，高效运用`map`和`string`的STL函数，通过`find`查找字符位置，`substr`截取子串，快速实现字符串处理与变量赋值。
    - **重点代码核心实现思想**：读入语句后，删除末尾分号，通过`find`找到`=`和`+`的位置，利用`substr`获取变量名和表达式各部分，判断各部分是数字还是变量，进行相应赋值操作，最后遍历`map`输出变量和值。
    - **核心代码片段**：
```cpp
int main()
{
    cin>>n;
    int a;string sa;
    map<string,int>::iterator iter;
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
    return 0; 
}
```
3. **作者：fjy666 (4星)**
    - **关键亮点**：详细说明思路，利用`scanf`的字符集特性分割字符串，对不同赋值情况分类讨论，使用`map`存储变量，代码注释丰富，可读性强。
    - **重点代码核心实现思想**：通过`scanf`按特定格式读入命令，利用`sscanf`进一步解析命令中的变量和表达式，判断表达式是否有`+`号，分情况处理赋值操作，最后遍历`map`输出变量和值。
    - **核心代码片段**：
```cpp
int main()
{
    int n;
    scanf("%d",&n);
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
    return 0;
}
```

### 最优关键思路或技巧
1. **数据结构选择**：使用`map`存储变量与值的键值对，利用其自动排序特性简化按字典序输出的操作，同时方便根据变量名查找和修改变量值。
2. **字符串处理技巧**：运用`scanf`的黑名单字符集功能、`string`的`find`和`substr`等函数，以及`sscanf`的格式化输入功能，高效地分割和解析输入的字符串。
3. **分类讨论思想**：对赋值表达式的不同类型（数字、变量、数字+变量等）进行清晰的分类讨论，确保每种情况都能正确处理。

### 拓展思路
同类型题目通常围绕字符串处理、模拟运算以及变量管理展开。类似算法套路包括：
1. 更复杂的表达式解析，如增加`-`、`*`、`/`等运算符，需要考虑运算符优先级。
2. 处理作用域问题，不同作用域内变量的可见性和生命周期不同。
3. 引入函数调用的模拟，函数可能有参数传递和返回值等。

### 相似知识点洛谷题目
1. **P1046 [NOIP2005 普及组] 陶陶摘苹果**：涉及简单的条件判断和模拟，与本题处理不同情况的思路类似。
2. **P1909 [NOIP2016 普及组] 买铅笔**：通过模拟不同购买方案进行计算和比较，锻炼逻辑思维和代码实现能力。
3. **P5733 [NOIP2018 普及组] 跳房子**：结合模拟和简单的数学运算，与本题在模拟过程中处理数据的方式有相似之处。

### 个人心得摘录与总结
1. **作者happybob**：在输入处理上遇到多种问题，如`scanf`提交导致MLE，`cin`提交WA部分点，`cin.get`和`getchar`提交也MLE。最终通过合理的`while`循环读入解决。总结为输入方式的选择对结果影响较大，需根据题目数据特点谨慎选择。 

---
处理用时：77.64秒