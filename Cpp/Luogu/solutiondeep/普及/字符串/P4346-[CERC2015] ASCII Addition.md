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
这些题解的核心思路都是将 ASCII 艺术形式的数字和符号转换为普通数字进行加法运算，再将结果转换回 ASCII 艺术形式输出。主要步骤包括打表存储数字和符号的 ASCII 形式、读取输入、识别数字和符号、计算加法结果、输出结果的 ASCII 形式。各题解在具体实现方式上有所不同，如打表方式、数字识别方法、代码结构等。

### 所选题解
1. **作者：opened（5星）**
    - **关键亮点**：代码长度不超百行，思路清晰，采用快读式读取数字，递归实现结果转换，代码可读性和效率较高。
    - **个人心得**：强调要充分挖掘题目能量，做到代码高效、思路清晰、自成题解。
2. **作者：Gu_Ren（4星）**
    - **关键亮点**：将 ASCII 矩阵转换为二进制再转十进制，通过对比十进制数识别数字，思路独特。
    - **个人心得**：从 Pascal 转到 C++ 做题，调了一上午，发现将矩阵转二进制的简洁思路。
3. **作者：Enstein（4星）**
    - **关键亮点**：详细分析解题思路，代码结构清晰，将不同功能封装成函数，便于理解和维护。
    - **个人心得**：认为这是一道简单字符串水题，要注意细节，理性分析并实现暴力。

### 重点代码及核心思想
#### opened 题解
```cpp
string num[11]={...}; // 打数字表
inline char r(){...} // 原表 -> 单个字符数字
inline int read(){...} // 字符数字 -> 整型
void change(int ans,int end=1){...} // int 答案 -> 横行答案表
int main(){
    for(int i=0;i<7;i++){
        cin>>s[i];
        s[i]+="."; // 补出尾部间隔
    }
    int a=read(),b=read();
    int ans=a+b;
    change(ans,0);
    for(int i=0;i<7;i++) cout<<sum[i]<<"\n";
    return 0;
}
```
核心思想：先打表存储数字和符号的 ASCII 形式，通过 `r` 函数逐行取单个数字并匹配数字表，`read` 函数将字符数字转换为整型，`change` 函数将结果转换为横行答案表，最后输出结果。

#### Gu_Ren 题解
```cpp
int c[11]={...}; // 提前准备 0~9 和“+”对应的矩阵转成二进制的值
string e[10]={...}; // 提前准备 0~9 对应的 ASCII 矩阵
int main(){
    for (int i=1;i<=7;i++){
        cin>>s[i];
        s[i]=s[i]+'.';
    }
    int n=s[1].length();
    for (int i=1;i<=7;i++)
        for (int j=0;j<n;j++){
            a[i][j]=(s[i][j]=='x'); // 转二进制
        }
    t=1;
    for (int i=0;i+6<=n;i+=6){
        x=1;
        for (int j=1;j<=7;j++){
            for (int k=i;k<i+6;k++){
                b[num]+=x*a[j][k];
                x=x*2;
            }
        }
        for (int j=0;j<10;j++)
            if (b[num]==c[j]){
                ans[t]=ans[t]*10+j;
                break;
            }
        if (b[num]==75251968) t++; // 特判加号
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
核心思想：将输入的 ASCII 矩阵转换为二进制，再将二进制转换为十进制，通过对比十进制数识别数字，计算加法结果，最后将结果转换为 ASCII 矩阵输出。

#### Enstein 题解
```cpp
string shu[15]={...}; // 存储数字 0~9 和 + 的字符串数组
void read(){...} // 读入输入
void print(int k){...} // 输出结果的 ASCII 形式
void change(){...} // 转换输入为数字，计算加法结果
int main(){
    read();
    change();
    return 0;
}
```
核心思想：先打表存储数字和符号的字符串形式，通过 `read` 函数读入输入，`change` 函数将输入转换为数字，计算加法结果，`print` 函数将结果转换为 ASCII 形式输出。

### 最优关键思路或技巧
- **打表**：将数字和符号的 ASCII 形式预先存储在数组中，方便后续匹配和转换。
- **模块化设计**：将不同功能封装成函数，提高代码的可读性和可维护性。
- **二进制转换**：将 ASCII 矩阵转换为二进制再转十进制，通过对比十进制数识别数字，减少匹配的复杂度。

### 可拓展之处
同类型题可能会涉及更多的运算符、更大的数字范围或更复杂的 ASCII 艺术形式。类似算法套路包括打表、字符串处理、数字转换等。

### 推荐题目
1. [P1001 A+B Problem](https://www.luogu.com.cn/problem/P1001)
2. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
3. [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)

### 个人心得总结
- opened：强调要充分挖掘题目能量，做到代码高效、思路清晰、自成题解。
- Gu_Ren：从 Pascal 转到 C++ 做题，调了一上午，发现将矩阵转二进制的简洁思路。
- Enstein：认为这是一道简单字符串水题，要注意细节，理性分析并实现暴力。

---
处理用时：43.82秒