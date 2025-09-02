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

这道题主要考查对特定格式算式的解析与高精度计算。各题解思路围绕识别算式不同形式并进行相应运算，难点在于高精度运算及处理算式中的符号和数字组合。

### 综合分析与结论
1. **思路**：多数题解先将输入算式按不同形式拆分，如“+++x”“+(x)x”等，再分别计算各部分值并累加。部分题解通过分别记录加法和减法结果，最后相减得到最终答案。
2. **算法要点**：
    - **字符串处理**：从字符串中提取数字、符号及括号内数字。
    - **高精度运算**：因数据范围，需实现高精度加、减、乘运算。
    - **符号处理**：根据符号确定运算类型及结果正负。
3. **解决难点**：
    - **高精度运算实现**：保证运算准确性与效率，如处理进位、借位及结果正负。
    - **算式解析**：准确识别并处理算式不同形式，避免遗漏或错误解析。

### 所选的题解
1. **作者：吹雪吹雪吹 (5星)**
    - **关键亮点**：思路清晰，封装 `Int` 类实现高精度运算，代码结构清晰，对不同算式形式处理逻辑明确。
    - **个人心得**：无
    - **核心代码**：
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
    // 其他构造函数、运算符重载函数省略

};
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
    - **核心实现思想**：`Int` 类封装高精度整数，通过 `ToInt64` 函数按不同算式形式提取数字并计算，根据符号累加到 `ans1` 或 `ans_1`。
2. **作者：Alarm5854 (4星)**
    - **关键亮点**：提供两种解法，40分低精度解法适合新手理解，100分高精度解法详细展示高精度运算实现，结构体定义及运算符重载清晰。
    - **个人心得**：第一次提交只有40分，强调高精度的重要性。
    - **核心代码**：
```cpp
struct ll{
    char s[2100];
    int a[2100],flag;
    void clear()
    {
        memset(s,0,sizeof(s));
        memset(a,0,sizeof(a));
        *a=1,flag=1;
    }
    // 输出、化低精为高精、运算符重载等函数省略
};
ll operator +(ll a,ll b)
{
    ll c;
    c.clear();
    if(!~a[-1]&&!~b[-1])
    {
        a[-1]=b[-1]=1;
        c=a+b,c[-1]=-1;
        return c;
    }
    if(!~a[-1])
    {
        a[-1]=1;
        c=b-a;
        return c;
    }
    if(!~b[-1])
    {
        b[-1]=1;
        c=a-b;
        return c;
    }
    c[0]=max(a[0],b[0]);
    for(int i=1;i<=c[0];++i)
        c[i]=a[i]+b[i];
    for(int i=1;i<=c[0];++i)
        c[i+1]+=c[i]/10,c[i]%=10;
    if(c[c[0]+1]) ++c[0];
    return c;
}
void turn(int s,int t,ll &a)
{
    a.clear();
    for(int i=s;i<t;++i)
        a=a*10,a=a+op[i]-48;
}
int main()
{
    scanf("%s",op);
    while(op[i]!='\0')
    {
        while(op[i]=='+') flag=1,s=s+1,++i;
        while(op[i]=='-') flag=-1,s=s+1,++i;
        if(isdigit(op[i]))
        {
            j=i;
            while(isdigit(op[j]))
                ++j;
            turn(i,j,num[++k]);
            num[k]=num[k]*s*flag;
            i=j,s.clear();
        }
        else
        {
            if(op[i]=='(')
            {
                j=++i;
                while(isdigit(op[j]))
                    ++j;
                turn(i,j,s);
                i=j;
            }
            if(op[i]==')')
                ++i;
        }
    }
    for(int i=1;i<=k;i++)
        ans+=num[i];
    cout<<ans;
    return 0;
}
```
    - **核心实现思想**：`ll` 结构体表示高精度数，通过 `turn` 函数将字符串转化为高精度数，主函数中按算式形式计算各部分值并累加到 `ans`。
3. **作者：Von_Brank (4星)**
    - **关键亮点**：详细阐述思路，对高精度运算函数解释清晰，代码结构完整，适合学习高精度运算。
    - **个人心得**：第一次认真写高精，历经多次提交才AC，强调高精度代码调试的复杂性。
    - **核心代码**：
```cpp
struct BigInt
{
    int ch;
    int x[300];
};
inline void clear(BigInt& x);
inline BigInt read();
inline int Compare(BigInt a, BigInt b);
inline BigInt Plus(BigInt a, BigInt b);
inline BigInt Minus(BigInt a, BigInt b);
inline BigInt Multi(BigInt a, BigInt b);
inline BigInt Int_to_BigInt(int x);
inline void clear(BigInt& x)
{
    memset(x.x, 0, sizeof(x.x));
    x.ch = 1;
}
inline BigInt Plus(BigInt a, BigInt b)
{
    BigInt c;
    clear(c);
    if(a.ch == 1 && b.ch == -1)
    {
        b.ch = 1;
        return Minus(a, b);
    }
    if(a.ch == -1 && b.ch == 1)
    {
        a.ch = 1;
        return Minus(b, a);
    }
    if(a.ch == -1 && b.ch == -1)
    {
        c.ch = -1;
    }
    int k = a.x[0] > b.x[0]? a.x[0] : b.x[0], g = 0;
    for(int i=1; i<=k; i++)
    {
        c.x[i] = a.x[i] + b.x[i] + g;
        g = c.x[i] / 10;
        c.x[i] %= 10;
    }
    if(g) c.x[++k] = g;
    c.x[0] = k;
    return c;
}
int main()
{
    clear(ansx);
    ansx.x[0] = 1;
    scanf("%s", a+1);
    len = strlen(a+1);
    for(int i=1; i<=len; i++)
    {
        if(i == 1 && (a[i] >= '0' && a[i] <= '9'))
        {
            int l, r;
            for(l=1; l<=len; l++)
            {
                if(a[l] < '0' || a[l] > '9')
                {
                    r = l-1;
                    break;
                }
            }
            ++top;
            clear(ans[top]);
            ans[top] = Plus(ans[top], Int_to_BigInt(a[1] - '0'));
            for(int j=2; j<=r; j++)
            {
                clear(tmp);
                ans[top] = Multi(ans[top], Int_to_BigInt(10));
                ans[top] = Plus(ans[top], Int_to_BigInt(a[j]-'0'));
            }
            continue;
        }
        if(a[i] == '+' || a[i] == '-')
        {
            char character;
            character = a[i];
            int m, k, l;
            BigInt ax, bx, numc;
            clear(ax);
            clear(bx);
            clear(numc);
            for(int j=i; j<=len; j++)
            {
                if(a[j]!= character)
                {
                    m = j - 1;
                    break;
                }
                numc = Plus(numc, Int_to_BigInt(1));
            }
            if(a[m+1] == '(')
            {
                for(int j=m+2; j<=len; j++)
                {
                    if(a[j] == ')')
                    {
                        k = j-1;
                        break;
                    }
                }
                ax = Plus(ax, Int_to_BigInt(a[m+2] - '0'));
                for(int j=m+3; j<=k; j++)
                {
                    ax = Multi(ax, Int_to_BigInt(10));
                    ax = Plus(ax, Int_to_BigInt(a[j] - '0'));
                }
            }
            else
            {
                k = m - 1;
                ax = Plus(Int_to_BigInt(0), Int_to_BigInt(1));
            }
            for(int j=k+2; j<=len; j++)
            {
                if(j == len) l = j;
                if(a[j] < '0' || a[j] > '9')
                {
                    l = j-1;
                    break;
                }
            }
            bx = Plus(bx, Int_to_BigInt(a[k+2] - '0'));
            for(int j=k+3; j<=l; j++)
            {
                bx = Multi(bx, Int_to_BigInt(10));
                bx = Plus(bx, Int_to_BigInt(a[j] - '0'));
            }
            ++top;
            clear(ans[top]);
            ans[top] = Plus(Int_to_BigInt(0), Int_to_BigInt(1));
            ans[top] = Multi(ans[top], ax);
            ans[top] = Multi(ans[top], bx);
            ans[top] = Multi(ans[top], numc);
            i = l;
            if(character == '-')
                ans[top] = Multi(ans[top], Int_to_BigInt(-1));
        }
    }
    for(int i=1; i<=top; i++)
        ansx = Plus(ansx, ans[i]);
    print(ansx);
    return 0;
}
```
    - **核心实现思想**：`BigInt` 结构体表示高精度数，通过一系列函数实现高精度运算，主函数按算式形式解析并计算各部分值，最后累加得到答案。

### 最优的关键思路或技巧
1. **数据结构**：使用结构体或类封装高精度数，便于实现和管理高精度运算。
2. **算法优化**：分别记录加法和减法结果，最后相减，减少运算中符号处理的复杂性。
3. **代码实现技巧**：将算式解析和高精度运算分开实现，使代码结构更清晰，便于调试和维护。

### 可拓展之处
同类型题常考察字符串处理与高精度运算结合，类似算法套路为：先解析输入字符串，提取有效信息，再根据题目要求进行高精度运算。例如处理更复杂的算式格式，或结合其他运算规则。

### 推荐题目
1. **P1601 A+B Problem（高精）**：基础高精度加法题目，适合巩固高精度运算基础。
2. **P1009 阶乘之和**：结合高精度乘法与加法，锻炼高精度运算综合应用能力。
3. **P2142 高精度减法**：专注高精度减法练习，加深对减法运算细节的理解。

### 个人心得摘录与总结
1. **吹雪吹雪吹**：无。
2. **Alarm5854**：第一次提交只有40分，意识到高精度的重要性。总结出对于此类题目，要注意数据范围，及时采用高精度算法。
3. **Von_Brank**：第一次认真写高精，历经100 + 次提交，15次自己提交才AC，强调高精度代码调试的复杂性和挑战性，提醒在写高精度代码时要耐心细致。 

---
处理用时：146.29秒