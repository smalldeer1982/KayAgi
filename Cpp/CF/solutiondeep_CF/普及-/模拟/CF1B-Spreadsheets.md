# 题目信息

# Spreadsheets

## 题目描述

In the popular spreadsheets systems (for example, in Excel) the following numeration of columns is used. The first column has number A, the second — number B, etc. till column 26 that is marked by Z. Then there are two-letter numbers: column 27 has number AA, 28 — AB, column 52 is marked by AZ. After ZZ there follow three-letter numbers, etc.

The rows are marked by integer numbers starting with 1. The cell name is the concatenation of the column and the row numbers. For example, BC23 is the name for the cell that is in column 55, row 23.

Sometimes another numeration system is used: RXCY, where X and Y are integer numbers, showing the column and the row numbers respectfully. For instance, R23C55 is the cell from the previous example.

Your task is to write a program that reads the given sequence of cell coordinates and produce each item written according to the rules of another numeration system.


## 样例 #1

### 输入

```
2
R23C55
BC23
```

### 输出

```
BC23
R23C55
```

# AI分析结果

### 题目翻译
## 电子表格

### 题目描述
在流行的电子表格系统（例如 Excel）中，使用以下列编号方式。第一列编号为 A，第二列编号为 B，依此类推，直到第 26 列标记为 Z。然后是双字母编号：第 27 列编号为 AA，第 28 列编号为 AB，第 52 列标记为 AZ。在 ZZ 之后是三字母编号，依此类推。

行用从 1 开始的整数编号。单元格名称是列编号和行编号的连接。例如，BC23 是第 55 列、第 23 行的单元格名称。

有时会使用另一种编号系统：RXCY，其中 X 和 Y 是整数，分别表示列号和行号。例如，R23C55 是前面示例中的单元格。

你的任务是编写一个程序，读取给定的单元格坐标序列，并根据另一种编号系统的规则输出每个项目。

### 样例 #1
#### 输入
```
2
R23C55
BC23
```
#### 输出
```
BC23
R23C55
```

### 综合分析与结论
这些题解的核心思路都是实现两种单元格坐标表示法（Excel 表示法和 (R,C) 坐标表示法）之间的转换，主要涉及 26 进制与 10 进制的相互转换。

#### 思路对比
- 多数题解通过判断输入字符串的特征来确定其表示法类型，再进行相应转换。
- 部分题解使用递归或循环进行进制转换，还有题解借助字符串处理函数简化操作。

#### 算法要点
- **判断表示法类型**：通过检查字符串中字符的位置和类型（数字、字母）来判断是哪种表示法。
- **进制转换**：
    - Excel 表示法转 (R,C) 坐标表示法：将字母部分按 26 进制转 10 进制。
    - (R,C) 坐标表示法转 Excel 表示法：将列号按 10 进制转 26 进制。

#### 难点解决
- **无 0 表示**：在 10 进制转 26 进制时，当余数为 0 时需特殊处理，将其视为 26（对应 'Z'），并调整商的值。

### 所选题解
- **作者：Loner_Knowledge（5 星）**
    - **关键亮点**：思路清晰，代码结构良好，通过两个函数分别处理两种转换，注释详细，对特殊情况的处理简洁明了。
    - **个人心得**：无
    - **核心代码**：
```cpp
void Solve1() {
    int i=0,j=0,num1=0,num2=0;
    int t[101];
    for(++i;isdigit(s[i]);++i)
        (num2*=10)+=s[i]-'0';
    for(++i;s[i];++i)
        (num1*=10)+=s[i]-'0';
    for(;num1;num1=num1/26-!(num1%26)) {    //特判
        if(num1%26)
            t[++j]=num1%26;
        else
            t[++j]=26;    //特判
    }
    for(;j;--j)
        putchar(Const[t[j]]);
    printf("%d\n",num2);
}
void Solve2() {
    int i=0,num1=0,num2=0;
    for(;isupper(s[i]);++i)
        (num2*=26)+=s[i]-'A'+1;    //注意这个加一，A表示1而不是0
    for(;s[i];++i)
        (num1*=10)+=s[i]-'0';
    printf("R%dC%d\n",num1,num2);
}
```
- **作者：Drifting（4 星）**
    - **关键亮点**：使用 STL 库函数简化代码，如 `find()` 函数查找字符位置，`reverse()` 函数反转字符串，提高了代码的可读性和简洁性。
    - **个人心得**：第一次发 CF 题的题解，很激动。本题关键在于 26 进制与 10 进制的转换，要注意 26 个字母中没有表示 0 的情况。
    - **核心代码**：
```cpp
void trans(bool mode)
{
    char apt[] = " ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //alphabet 字母表 
    int col = 0,row = 0; //col为列号，row为行号; 
    if(mode)	//mode 1: RXCY转Excel式 
    {
        int R = str.find("R"),C = str.find("C");  //使用find()函数，找到R与C所在的位置; 
        for(int i = R + 1;i < C;i++)	//从R的下一位开始遍历，下同; 
            row = row * 10 + str[i] - '0';	//字符串转十进制数字 
        for(int i = C + 1;i < len;i++)
            col = col * 10 + str[i] - '0';	
        string ans;
        while(col > 0)
        {
            int temp = col % 26; //除26取余，下同; 
            if(temp == 0)	temp = 26,col -= 26; //当col对应字母为'Z' 时，需要进行特判; 
            ans += apt[temp]; //利用apt[]将数字重新转为对应字母,使用ans字符串储存答案; 
            col /= 26;
        }
        reverse(ans.begin(),ans.end());	
        cout<<ans<<row<<endl;
    }
    else //mode 2: Excel式转为RXCY式; 
    {
        for(int i = 0;i < len;i++)	//遍历字符串 
        {
            if(!isdigit(str[i])) 
                col = col * 26 + str[i] - 'A' + 1;	//26进制字符串转十进制数字; 
            else row = row * 10 + str[i] - '0'; //同上; 
        }
        printf("R%dC%d\n",row,col);
    }
} 
```
- **作者：sandwich（4 星）**
    - **关键亮点**：详细说明了解题的注意点，代码逻辑清晰，对两种表示法的判断和转换处理较为直观。
    - **个人心得**：这一题就是简单的二十六进制与十进制之间的转换（做了 WA 十几遍），最主要的注意点是 Z，满 26 会进一位，不加判断会输出错误结果。
    - **核心代码**：
```c
if(tt)
{
    int a[10];
    int sum=0,j=0;
    while(x[j]>='A'&&x[j]<='Z')
        j++,a[j]=x[j-1]-'A'+1;
    int k=j;
    for(int i=1;i<=j;i++)
    {
        int ans=1;
        for(int k=1;k<=j-i;k++)
            ans*=26;
        sum+=a[i]*ans;
    }
    cout<<"R";
    j--;
    for(int i=j+1;i<l;i++)
        cout<<x[i];
    cout<<"C"<<sum;
    cout<<endl;
}
if(!tt)
{
    int a,b,x1[10];
    a=x[k+1]-'0';b=x[1]-'0';
    for(int i=k+2;i<l;i++)
        a=a*10+x[i]-'0';
    for(int i=2;i<k;i++)
        b=b*10+x[i]-'0';
    int k=0;
    while(a!=0)
    {
        k++;
        if(a%26!=0)x1[k]=a%26,a/=26;
        else x1[k]=26,a=a/26-1;
    }
    for(int i=k;i>=1;i--)
    {
        cout<<char(x1[i]+'A'-1);
    }
    cout<<b;
    cout<<endl;
} 
```

### 最优关键思路或技巧
- **特判余数为 0 的情况**：在 10 进制转 26 进制时，当余数为 0 时，将其视为 26（对应 'Z'），并将商减 1。
- **利用字符串处理函数**：如 `find()`、`substr()` 等，简化字符串的查找和截取操作。

### 拓展思路
同类型题可能涉及不同进制之间的转换，如 8 进制、16 进制等，解题思路类似，关键在于处理特殊情况和掌握进制转换的方法。

### 推荐题目
1. [P1143 进制转换](https://www.luogu.com.cn/problem/P1143)
2. [P1604 B进制星球](https://www.luogu.com.cn/problem/P1604)
3. [P2084 进制转换](https://www.luogu.com.cn/problem/P2084)

### 个人心得总结
- **Loner_Knowledge**：无
- **Sayori**：一开始没考虑到 0 不能输出，导致出现错误，经过思考后成功 AC。
- **Drifting**：第一次发 CF 题解很激动，本题关键在于 26 进制与 10 进制转换，要注意无 0 表示的情况。
- **sandwich**：做这题 WA 了十几遍，主要注意点是 Z 的处理，满 26 会进一位，不加判断会输出错误结果。
- **BBD186587**：挂了六发，第一发是没判 Z 输出了 @，第二发到第五发是判断表示法类型时出错，最终通过修正判断条件 AC。
- **叶枫**：因为使用 `#define int long long + signed main()` 交了好多次，提醒不要这样做。
- **blackzoo**：Wrong 了不少次，很多细节没注意到，如 0 不能输出、字符串截取等，后续需要努力。
- **icebird**：感受到 codeforces 的深深恶意，这是一道麻烦的字符模拟题，也是对基础能力的试炼。 

---
处理用时：59.81秒