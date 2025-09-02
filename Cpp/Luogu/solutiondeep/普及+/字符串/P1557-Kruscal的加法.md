# 题目信息

# Kruscal的加法

## 题目背景

奶牛 Kruscal 认为人类的加法太落后了。比如说有时候想要用加法计算 `+15*3`，只能写成 `+15+15+15`，真是浪费精力啊！于是，Kruscal 决定开发出一种新的加法算式。

## 题目描述

当然，新的算式也是建立在原本算式的基础上的，不同就在于上式可以直接写成 `+++15`，同理，对于 `-15*3` 这样的算式可以写成 `---15`。一段时间后，Kruscal 又被那无穷多个 `+-` 号囧到了，于是他又将这个算式改进了一下。

比如 `+15*3` 又可以写成 `+(3)15`，同样，`-15*3` 等价于 `-(3)15`。但从上面可以看出，对于乘数较小的情况，如 `+++15` 这样的表述还是很方便的，于是在新的算式中还是保留了这种形式。

对于算式还要做一点特殊的说明：`+15*3` 转换成 Kruscal 型算式时可以写成 `+++15` 或 `+(3)15`，但不可以写成 `++(2)15` 这样的形式。

对于算式 `23+15*3-2` 可以表示为以下几种形式：`23+++15-2`、`23+(3)15-2`、`+23+++15-2`、`+23+(3)15-2、+(1)23+(3)15-(1)2`。不会出现如下几种形式：`(1)23+++15-2`、`+23++(2)15-(1)2`、`23+++15-2+(0)100`、`23-(-3)15-2`。

## 说明/提示

对于 $100 \%$ 的数据，算式长度不超过 $2000$。

## 样例 #1

### 输入

```
+(1)23+(3)15-(1)2```

### 输出

```
66```

# AI分析结果

这道题要求根据特定规则解析并计算算式，由于算式长度可能较长，需使用高精度运算。各题解思路和实现方法虽有不同，但核心都是对算式的处理及高精度计算。

### 综合分析与结论
1. **思路方面**：多数题解先将输入算式按规则拆分为基本单元，再分别计算各单元值并累加。部分题解会先判断算式开头是否为数字，若不是则添加默认符号以方便后续处理。
2. **算法要点**：
    - **算式拆分**：识别并处理不同形式的运算单元，如`+++x`、`+(x)x`、`+x`、`x`及其减法对应形式。
    - **高精度运算**：实现高精度的加、减、乘运算，部分题解通过结构体或类重载运算符实现，部分则采用传统函数实现。
3. **解决难点**：
    - **算式解析**：处理多种复杂的算式表达形式，确保正确识别运算符、数字及乘数关系。
    - **高精度运算**：处理负数参与的高精度运算，包括不同符号数的加减乘运算规则处理。

### 所选的题解
1. **吹雪吹雪吹**  🌟🌟🌟🌟
    - **关键亮点**：通过自定义`Int`类重载加、减、乘运算符实现高精度运算，代码结构清晰，对不同算式形式的处理逻辑明确。
    - **个人心得**：作者自认为写得粗鲁，但整体代码逻辑清晰，体现出对高精度运算和算式处理的熟练掌握。
    - **重点代码 - `Int`类实现高精度运算**：
```cpp
class Int
{
public:
    int a[505],len;
    Int()
    {
        memset(a,0,sizeof(a));
        len=0;
    }
    Int(int x)
    {
        memset(a,0,sizeof(a));
        len=0;
        while(x)
        {
            a[++len]=x%TT;
            x/=TT;
        }
    }
    Int operator +(Int b)
    {
        Int c;
        c.len=max(len,b.len);
        for(int i=1;i<=c.len;++i)
        {
            c.a[i]+=a[i]+b.a[i];
            c.a[i+1]=c.a[i]/TT;
            c.a[i]%=TT;
        }
        if(c.a[c.len+1])
            c.len++;
        return c;
    }
    Int operator *(Int b)
    {
        Int c;
        c.len=len+b.len;
        for(int i=1;i<=len;++i)
        {
            for(int j=1;j<=b.len;++j)
            {
                c.a[i+j-1]+=a[i]*b.a[j];
                c.a[i+j]+=c.a[i+j-1]/TT;
                c.a[i+j-1]%=TT;
            }
        }
        while(!c.a[c.len])
            c.len--;
        return c;
    }
    Int operator -(const Int b)
    {
        Int c;
        c.len=max(len,b.len);
        for (int i=1;i<=c.len;i++)
        {
            c.a[i]+=a[i]-b.a[i]+TT;
            c.a[i+1]+=c.a[i]/TT-1;
            c.a[i]%=TT;
        }
        while (c.len>1&&!c.a[c.len]) c.len--;
        return c;
    }
    bool operator <(Int b)const
    {
        if(b.len>len)
            return true;
        else if(len>b.len)
            return false;
        for(int i=len;i>0;--i)
        {
            if(b.a[i]>a[i])
                return true;
            if(b.a[i]<a[i])
                return false;
        }
        return false;
    }
    void write()
    {
        printf("%d",a[len]);
        for(int i=len-1;i>=1;--i)
            printf("%04d",a[i]);
        printf("\n");
    }
};
```
    - **重点代码 - 算式处理函数**：
```cpp
void ToInt64(int &i)
{
    Int ret=0,cs=0,p=10;
    int f=1;
    if(s[i]=='-')
        f=-1;
    if(s[i+1]=='(')
    {
        i+=2;
        while(s[i]>='0'&&s[i]<='9')
        {
            Int res=(int)s[i]-'0';
            cs=cs*p+res,++i;
        }
        i++;
        while(s[i]>='0'&&s[i]<='9')
        {
            Int res=(int)s[i]-'0';
            ret=ret*p+res,++i;
        }
        Int c=ret*cs;
        if(f==-1)
            ans_1=ans_1+c;
        else
            ans1=ans1+c;
    }
    else if(s[i+1]>='0'&&s[i+1]<='9')
    {
        i++;
        while(s[i]>='0'&&s[i]<='9')
        {
            Int res=(int)s[i]-'0';
            ret=ret*p+res,++i;
        }
        int c=ret;
        if(f==-1)
            ans_1=ans_1+c;
        else
            ans1=ans1+c;
    }
    else
    {
        i++,cs=1;
        Int res=1;
        while(s[i]=='-'||s[i]=='+')
        {
            cs=cs+res,++i;
        }
        while(s[i]>='0'&&s[i]<='9')
        {
            Int res=(int)s[i]-'0';
            ret=ret*p+res,++i;
        }
        Int c=ret*cs;
        if(f==-1)
            ans_1=ans_1+c;
        else
            ans1=ans1+c;
    }
}
```
2. **赤霄**  🌟🌟🌟🌟
    - **关键亮点**：采用模拟方法，通过多个函数分别实现高精度的加、减、乘以及数字读取和翻转等操作，对每种算式形式有详细的处理过程，思路清晰。
    - **重点代码 - 高精度加法**：
```cpp
void add()
{
    int r = max(ans_l,tot); int jin = 0;
    for (int i = 1 ; i <= r ; i++)
    {
        ans1[i] = ans1[i] + st[i] + jin;
        jin = ans1[i] / 10;
        ans1[i] %= 10;
    }
    ans_l = r;
    while(ans1[ans_l] == 0) ans_l--;
}
```
    - **重点代码 - 算式处理片段**：
```cpp
for (int i = 1 ; i <= len ; i++)
{
    if(s[i] == '+' && s[i+1] == '+')
    {
        memset(st,0,sizeof(st));
        int x = i; cnt = 0; tot = 0;
        while(s[x] <'0' || s[x] >'9') x++,cnt++;
        while(s[x] >= '0' && s[x] <= '9') st[++tot] = s[x++] - '0';
        change(); mul(cnt); add();
        i = x - 1; continue;
    }
    if(s[i] == '+' && s[i+1] == '(')
    {
        memset(st,0,sizeof(st)); memset(que,0,sizeof(que));
        int x = i + 2; tot = 0; cnt = 0;
        while(s[x] >='0' && s[x] <='9') que[++cnt] = s[x++] - '0'; 
        tchange();
        if(s[x] == ')')
        {
            x ++;
            while(s[x] >='0' && s[x] <='9') st[++tot] = s[x++] - '0';
            change();
        }
        Mmul(); add();
        i = x - 1; 
        continue;
    }
    // 其他算式形式处理类似
}
```
3. **HanPi**  🌟🌟🌟🌟
    - **关键亮点**：先将算式拆分成小的单一算式，再分别计算其值并叠加到答案中，对每种算式形式的拆分和计算有清晰的代码实现，同时给出高精度运算的详细实现。
    - **重点代码 - 算式拆分**：
```cpp
scanf("%s", &(str[1]));
if (str[1]!= '+' && str[1]!= '-')str[0] = '+';
int len = strlen(str);
str[len] = '+';

for (int i = 0; i < len; i++)
{
    if (str[i] == '+' || str[i] == '-')
    {
        for (int j = i + 1; j < len; j++)
        {
            if (str[j] == '+' || str[j] == '-')
            {
                if (str[j - 1]!= '+' && str[j - 1]!= '-')
                {
                    for (int k = i; k < j; k++)stmp[k - i] = str[k];
                    stmp[j - i] = 0;

                    GetVal(stmp);
                    i = j - 1;
                    break;
                }
            }
        }
    }
}
```
    - **重点代码 - 计算单一算式值**：
```cpp
void GetVal(const char* str)
{
    char plus[2008] = {0}, minus[2008] = { 0 };
    long long len = strlen(str);
    long long flag = 0;
    char num[2008] = { 0 }, tmpn[2008] = { 0 };

    for (int i = 0; i < len; i++)
    {
        if (str[i] == '+')
        {
            pluss(plus, "1");
        }
        else if (str[i] == '-')
        {
            pluss(minus, "1");
        }
        else if (str[i] == '(')
        {
            flag = 1;
        }
        else if (str[i] == ')')
        {
            flag = 0;
        }
        else if ('0' <= str[i] && str[i] <= '9')
        {
            if (flag)
            {
                int e = strchr(str, ')') - str;
                for (int j = i; j < e; j++)
                {
                    tmpn[j - i] = str[j];
                }
                flag = 0;
                i = e;
            }
            else
            {
                for (int j = i; j < len; j++)
                {
                    num[j - i] = str[j];
                }
                break;
            }
        }
    }

    if (tmpn[0])minuss(tmpn, "1", tmpn);

    if (plus[0])
    {
        pluss(plus, tmpn);
        cf(num, plus);
        // 处理答案的正负情况
    }
    else
    {
        pluss(minus, tmpn);
        cf(num, minus);
        // 处理答案的正负情况
    }
}
```

### 最优关键思路或技巧
1. **数据结构**：使用结构体或类来封装高精度数字及其运算，通过重载运算符使代码更加简洁和易读，如“吹雪吹雪吹”的题解。
2. **算法优化**：将复杂算式拆分成基本单元分别处理，降低问题复杂度，如“HanPi”的题解，先拆分再计算每个小算式的值。
3. **代码实现技巧**：在处理高精度运算时，预先考虑好负数情况，通过分类讨论将负数运算转化为正数运算，减少代码实现难度，许多题解都采用了这种方式。

### 可拓展之处
此类题目拓展方向主要是进一步复杂化算式规则，如增加运算符种类、引入运算优先级等。类似算法套路是先对输入字符串进行有效拆分，再针对不同部分按规则计算，最后合并结果，同时要注意处理可能出现的大数情况。

### 相似知识点题目推荐
1. **P1601 A+B Problem（高精）**：基础的高精度加法练习题，适合巩固高精度运算基础。
2. **P1009 阶乘之和**：涉及高精度乘法和加法的综合应用，可进一步提升对高精度运算的掌握。
3. **P2142 高精度减法**：专注于高精度减法的练习，帮助理解高精度减法的实现细节。

### 个人心得摘录与总结
1. **吹雪吹雪吹**：自认为写得粗鲁，但实际代码逻辑清晰，体现出对高精度运算和算式处理的熟练掌握，从侧面反映出即使代码风格不精致，只要逻辑正确也能有效解决问题。
2. **灼眼的夏娜**：提到模拟写法容易写挂，在尝试模拟三个小时无果后转向重载运算符的写法，最终通过重载运算符实现了题目的要求，强调了在解题过程中及时转换思路的重要性。
3. **Von_Brank**：从开始写到AC时间跨度一个星期，提交15次以上，借助他人提供的高精度模板找出自己代码中的错误，体现出解决复杂问题需要耐心和借鉴他人经验。 

---
处理用时：112.89秒