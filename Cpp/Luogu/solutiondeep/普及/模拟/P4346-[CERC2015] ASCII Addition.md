# 题目信息

# [CERC2015] ASCII Addition

## 题目描述

# 题目背景

现在，如果你只是用手机的相机对着它们，智能手机应用可以即时翻译文本，甚至解决数学问题。您的工作是实现一个更简单的功能，回忆过去——添加两个作为ASCII艺术的整数。


ASCII艺术是一个字符矩阵，正好是7行高，每个字符都是点或小写字母X。

给出了A +B形式的表达式，其中A和B都是正整数。通过将所有的表达式字符（A和B的数字以及符号）作为7 5个矩阵，将这些矩阵转换成ASCII艺术，并将矩阵与单个字符的单个列串联在连续的各个矩阵之间。对应于数字和+符号的精确矩阵如下：

![](https://cdn.luogu.org/upload/pic/16222.png)

给定一个ASCII艺术来表达A+B的形式，找到加法的结果并用ASCII艺术形式写出。

## 样例 #1

### 输入

```
....x.xxxxx.xxxxx.x...x.xxxxx.xxxxx.xxxxx.......xxxxx.xxxxx.xxxxx
....x.....x.....x.x...x.x.....x.........x...x...x...x.x...x.x...x
....x.....x.....x.x...x.x.....x.........x...x...x...x.x...x.x...x
....x.xxxxx.xxxxx.xxxxx.xxxxx.xxxxx.....x.xxxxx.xxxxx.xxxxx.x...x
....x.x.........x.....x.....x.x...x.....x...x...x...x.....x.x...x
....x.x.........x.....x.....x.x...x.....x...x...x...x.....x.x...x
....x.xxxxx.xxxxx.....x.xxxxx.xxxxx.....x.......xxxxx.xxxxx.xxxxx```

### 输出

```
....x.xxxxx.xxxxx.xxxxx.x...x.xxxxx.xxxxx
....x.....x.....x.x.....x...x.x.........x
....x.....x.....x.x.....x...x.x.........x
....x.xxxxx.xxxxx.xxxxx.xxxxx.xxxxx.....x
....x.x.........x.....x.....x.....x.....x
....x.x.........x.....x.....x.....x.....x
....x.xxxxx.xxxxx.xxxxx.....x.xxxxx.....x```

# AI分析结果

### 综合分析与结论
本题主要是将 ASCII 艺术形式的数字表达式转换为普通数字进行加法运算，再将结果转换回 ASCII 艺术形式输出。各题解的核心思路都是打表存储数字和加号的 ASCII 表示，读取输入并识别数字和加号，计算加法结果，最后输出结果的 ASCII 形式。

### 所选题解
1. **作者：opened（5星）**
    - **关键亮点**：代码简洁高效，思路清晰，通过自定义函数实现原表到单个字符数字、字符数字到整型的转换，以及整型答案到横行答案表的转换，代码可读性强。
    - **个人心得**：强调代码能力的锻炼，提出代码长度不超百行、编码时间不超过一小时、自成题解的要求。
2. **作者：Gu_Ren（4星）**
    - **关键亮点**：将 ASCII 矩阵转换为二进制再转十进制，通过对比十进制数来识别数字，思路独特。
    - **个人心得**：萌新刚从 Pascal 转到 C++，做此题调了一上午，发现了将矩阵转换为二进制再转十进制的简洁思路。
3. **作者：Enstein（4星）**
    - **关键亮点**：详细分析解题思路，通过字符串数组存储数字和加号，使用 substr 函数截取字符进行匹配，最后按规律输出结果。
    - **个人心得**：提醒不要被题目难度吓到，仔细分析会发现是简单字符串水题，要注意一些细节，以理性的角度分析并实现暴力。

### 重点代码及核心实现思想
#### opened 的题解
```cpp
string s[7],sum[7],num[11]={...};
int pos;
stack<int>a;

inline char r(){
    string ss;
    for(int i=0;i<7;i++) ss+=s[i].substr(pos,6);
    pos+=6;
    for(int i=0;i<10;i++)
        if(ss==num[i]) return i+'0';
    return 0;
}

inline int read(){
    int x=0;char ch=r();
    while(!ch) ch=r();
    for(x=ch&15,ch=r();ch;ch=r()) x=x*10+(ch&15);
    return x;
}

void change(int ans,int end=1){
    if(ans>9) change(ans/10);
    for(int i=0;i<7;i++)
        sum[i]+=num[ans%10].substr(i*6,5+end);
}

int main(){
    for(int i=0;i<7;i++){
        cin>>s[i];
        s[i]+=".";
    }
    int a=read(),b=read();
    int ans=a+b;
    change(ans,0);
    for(int i=0;i<7;i++) cout<<sum[i]<<"\n";
    return 0;
}
```
**核心实现思想**：通过 `r` 函数逐行取单个数字并与数字表匹配，`read` 函数将字符数字转换为整型，`change` 函数将整型答案转换为横行答案表，最后输出结果。

#### Gu_Ren 的题解
```cpp
string s[11];
int a[30][1000],x,num,t,cnt;
char m[30][1000];
int b[30],ans[30],dt[30],d[30];
int c[11]={...};
string e[10]={...};

int main(){
    for (int i=1;i<=7;i++){
        cin>>s[i];
        s[i]=s[i]+'.';
    }
    int n=s[1].length();
    for (int i=1;i<=7;i++)
        for (int j=0;j<n;j++)
            a[i][j]=(s[i][j]=='x');
    t=1;
    for (int i=0;i+6<=n;i+=6){
        x=1;
        for (int j=1;j<=7;j++)
            for (int k=i;k<i+6;k++)
                b[num]+=x*a[j][k];
                x=x*2;
        for (int j=0;j<10;j++)
            if (b[num]==c[j]){
                ans[t]=ans[t]*10+j;
                break;
            }
        if (b[num]==75251968) t++;
        num++;
    }
    for (int i=1;i<=t;i++) ans[t+1]+=ans[i];
    while(ans[t+1]!=0){
        cnt++;
        dt[cnt]=ans[t+1]%10;
        ans[t+1]=ans[t+1]/10;
    }
    for (int i=1;i<=cnt;i++) d[i]=dt[cnt-i+1];
    for (int i=0;i<35;i+=5){
        for (int j=1;j<=cnt;j++){
            for (int k=i;k<=i+4;k++)
                printf("%c",e[d[j]][k]);
            if (j!=cnt) printf(".");
        }
        printf("\n");
    }
    return 0;
}
```
**核心实现思想**：将输入的 ASCII 矩阵转换为二进制，再转换为十进制，通过对比十进制数与提前准备好的数组来识别数字，计算加法结果，最后按规律输出结果。

#### Enstein 的题解
```cpp
string shu[15]={...};
string ss[800];
int a1[1000]={0},a2[1000]={0},a3[1000]={0},a4[1000]={0};
int k1=0,k2=0,k3=0,k4=0;
string a[1000];

void read(){
    for(int i=1;i<=7;i++) cin>>ss[i];
}

void print(int k){
    while(k){
        a4[++k4]=k%10;
        k/=10;
    }
    int ci[80]={0};
    for(int i=1;i<=7;i++){
        for(int j=k4;j>=1;j--){
            for(int k=ci[j];k<ci[j]+5;k++)
                printf("%c",shu[a4[j]][k]);
            if(j!=1) printf(".");
            ci[j]+=5;
        }
        printf("\n");
    }
}

void change(){
    int ci=0;
    for(int i=1;i<=7;i++){
        ci=0;
        int kkk=ss[i].length();
        for(int j=0;j<kkk;j+=6){
            ci++;
            a[ci]+=ss[i].substr(j,5);
        }
    }
    for(int i=1;i<=ci;i++){
        for(int j=0;j<11;j++){
            if(shu[j]==a[i]){
                a1[++k1]=j;
                break;
            }
        }
    }
    int flag=0;
    int ans1=0,ans2=0;
    for(int i=1;i<=k1;i++){
        if(a1[i]==10) flag=1;
        if(a1[i]!=10&&flag==0) ans1=ans1*10+a1[i];
        if(flag==1&&a1[i]!=10) ans2=ans2*10+a1[i];
    }
    print(ans1+ans2);
}

int main(){
    read();
    change();
    return 0;
}
```
**核心实现思想**：通过 `read` 函数读取输入，`change` 函数将输入转换为数字并计算加法结果，`print` 函数将结果按规律输出。

### 最优关键思路或技巧
- **打表**：将数字和加号的 ASCII 表示存储在数组中，方便后续匹配和输出。
- **字符串处理**：使用 substr 函数截取字符，通过字符串比较来识别数字和加号。
- **二进制转换**：将 ASCII 矩阵转换为二进制再转十进制，通过对比十进制数来识别数字。

### 可拓展之处
同类型题可以是其他形式的字符转换和计算，如罗马数字的加减乘除，解题思路类似，都是先将字符转换为数字进行计算，再将结果转换回字符形式输出。

### 推荐题目
1. [P1001 A+B Problem](https://www.luogu.com.cn/problem/P1001)：基础的加法运算，可作为本题的基础练习。
2. [P1217 [USACO1.5] 回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)：涉及数字的判断和转换，锻炼对数字的处理能力。
3. [P1307 数字反转](https://www.luogu.com.cn/problem/P1307)：需要对数字进行反转操作，与本题的数字处理有一定关联。

### 个人心得总结
- **opened**：强调代码能力的锻炼，提出代码长度、编码时间和自成题解的要求。
- **Gu_Ren**：从 Pascal 转到 C++ 后做此题调了一上午，发现了将矩阵转换为二进制再转十进制的简洁思路。
- **Enstein**：提醒不要被题目难度吓到，仔细分析会发现是简单字符串水题，要注意一些细节，以理性的角度分析并实现暴力。

---
处理用时：58.02秒