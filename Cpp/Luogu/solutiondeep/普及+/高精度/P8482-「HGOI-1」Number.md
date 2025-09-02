# 题目信息

# 「HGOI-1」Number

## 题目背景

$\text{bh1234666}$ 正在学习乘法！

## 题目描述

$\text{bh1234666}$ 有一定数量的数字 $0 \sim 9$，现在他想让你寻找一种分配方案，将它们分成两个整数，使得他们的乘积 $p$ 最大。
 
由于 $\text{bh1234666}$ 不喜欢太大的数，所以你只需要输出**两个非负整数**，使它们的乘积**等于**最大乘积 $p$，但是这两个整数 $0 \sim 9$ 的数量不能等于给定的数量（任意一个数字数量不相等即可，**不考虑前导零**）。

$\text{bh1234666}$ 是很善良的，如果 $0 \sim 9$ 的数量等于给定的数量了，你依旧可以得到的一半的分。

## 说明/提示

#### 样例解释
最大可能乘积为 $97643210 \times 88653221=13949030 \times 620572547=8656385075279410$。

若输出 $97643210 \times 88653221$ 则只能得到一半的分，因为 $0\sim 9$ 出现的次数与给定的相同。

#### 数据范围及约定
本题采用**捆绑测试**，共有 $5$ 个 $\text{subtask}$，最终分数为所有 $\text{subtask}$ 分数之和。

$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|}\hline
\textbf{Task} & \textbf{Score} & \sum c_i\le \cr\hline
1 & 10 & 20 \cr\hline
2 & 20 & 100 \cr\hline
3 & 20 & 5000 \cr\hline
4 & 20 & 10^6 \cr\hline
5 & 30 & 10^7 \cr\hline
\end{array}
$$

对于 $100\%$ 的数据，保证 $1 \le c_i$，$\sum c_i \le 10^7$。

#### 说明

本题有 $\text{spj}$，两数乘积正确得一半的分，数量与给出的不同且乘积正确得全部分数。故每一 $\text{subtask}$ 的得分为其中所有数据点得分的**最小值**。


## 样例 #1

### 输入

```
1 2 3 2 1 1 2 1 2 1```

### 输出

```
13949030
620572547```

# AI分析结果

• **综合分析与结论**：这些题解的核心思路均是先确定使两数乘积最大的分配方式，再处理两数数字数量与给定数量不同的问题。算法要点在于利用 “和一定时，两数差越小积越大” 的性质进行贪心分配数字。解决难点主要集中在如何巧妙处理数字数量不同这一要求。

题解质量各有差异，部分题解思路清晰、代码实现简洁且有优化，部分题解在思路阐述或代码可读性上有所欠缺。

• **所选的题解**：
  - **作者：bh1234666 (赞：15)  5星**
    - **关键亮点**：思路清晰，先通过将整数转化为小数分析出数字排列规律，确定两数长度差至多为1且和固定，利用 “和定差小积大” 原则分配数字。对于使两数数字数量不同的处理巧妙，利用必有数结尾为0，通过一数乘二、一数除二改变数字数量。代码实现简洁明了，给出了完整的高精度乘除函数。
    - **重点代码 - 核心实现思想**：先按贪心策略分配数字得到两个数的字符串表示，再根据末尾是否为0决定对哪个数进行乘二或除二操作。
```cpp
#include<stdio.h>
char s1[1000005],s2[1000005];int l1,l2;
void half(char *s,int len) {
    int i;
    for(i=0;i<len;i++) {
        s[i]-='0';
        if(s[i]&1) s[i+1]+=10;
        s[i]>>=1;
        s[i]+='0';
    }
    if(s[0]=='0') puts(s+1);
    else puts(s);
}
void dble(char *s,int len) {
    int i;_Bool fl=0;
    for(i=len-1;i>=0;i--) {
        s[i]-='0';
        if(s[i]>4) s[i]<<=1,s[i]-=10,s[i]+=fl,fl=1;
        else s[i]<<=1,s[i]+=fl,fl=0;
        s[i]+='0';
    }
    if(fl) putchar('1');
    puts(s);
}
int main() {
    int i,j,a[10];_Bool flag=0;
    for(i=0;i<10;i++)
        scanf("%d",&a[i]);
    for(j=0,i=9;j<2;j++) {
        for(;j&&i>=0;i--)
            if(a[i]) {
                a[i]--;
                s2[l2++]='0'+i;
                break;
            }
        for(;i>=0;i--) {
            while(a[i]) {
                a[i]--;
                if(!flag) s1[l1++]='0'+i;
                else s2[l2++]='0'+i;
                flag=!flag;
            }
            if(flag&&!j) break;
        }
    }
    if(s1[l1-1]=='0') {
        half(s1,l1);
        dble(s2,l2);
    }
    else {
        half(s2,l2);
        dble(s1,l1);
    }
    return 0;
}
```
  - **作者：linyuhao (赞：7)  4星**
    - **关键亮点**：思路表述清晰，先明确乘积最大的原理是让更大数字占更高位且两数和一定时差最小，接着详细阐述从大到小分配数字的具体策略。对于数字数量不同的处理，利用必有零的条件，通过一个数乘2、另一个数乘5（相当于去掉一个末尾零）来实现，代码实现了低精乘高精。
    - **重点代码 - 核心实现思想**：先将所有数字按从大到小存入字符串，再按规则分配到两个字符串，最后通过自定义函数实现低精乘高精并输出。
```cpp
void sh(string x,int y){
    memset(a,0,sizeof(a));
    memset(b,0,sizeof(b));
    memset(c,0,sizeof(c));
    int s11=x.length();
    for(int i=0;i<s11;i++) 
        a[i]=x[s11-i-1]-'0';
    for(int i=0;i<s11;i++){
        c[i]=a[i]*y;   
    }
    int s3=s11+1;
    for(int i=0;i<s3;i++){
        c[i+1]+=c[i]/10;
        c[i]%=10;
    }
    for(;!c[s3]&&s3>0;){
        s3--;
    }
    for(int j=s3;j>=0;j--){
        if(j==0&&c[j]==0&&pd==0)pd=1;
        else cout<<c[j];
    }
}
//...
for(int i=0;i<=9;i++){
    aa[i]=read();
    ans+=aa[i];
}
for(int i=9;i>=0;i--){
    for(int j=1;j<=aa[i];j++){
        s+=(i+'0');
    }
}
for(int i=0;i<s.size();i+=2){
    if(i==s.size()-1){
        if(s1<s2)s1+=s[i];
        else s2+=s[i];
        break;
    }
    else if(s[i]==s[i+1]){
        s1+=s[i];
        s2+=s[i+1];
    }
    else{
        if(s1<s2)s1+=s[i],s2+=s[i+1];
        else s2+=s[i],s1+=s[i+1];
    }
}
sh(s1,2);
cout<<endl;
sh(s2,5);
```
  - **作者：Full_Speed (赞：2)  4星**
    - **关键亮点**：先分析出要使乘积最大需让最高位更大且两数相差最小，再利用必有偶数的条件，通过将两数中任意偶数除以二，另一个数乘二来改变数字数量，代码实现使用了自定义的高精度乘除结构体。
    - **重点代码 - 核心实现思想**：先按贪心策略确定两个数，存入数组并转化为自定义高精度结构体，再根据奇偶判断对哪个数进行乘二或除二操作并输出。
```cpp
struct bigint{
    int a[5000010],len,ff;
    bigint(){memset(a,0,sizeof(a));len=0;ff=0;}
    friend void putb(bigint Z) {
        if(Z.len==0)putchar('0');
        else {
            if(Z.ff==1)putchar('-');
            for(register int i=Z.len;i>=1;i--)putchar(Z.a[i]+'0');
        }
        return;
    }
    friend bigint operator * (const bigint &A,const int &b) {
        bigint C;C.len=A.len;
        for(register int i=1;i<=A.len;i++){
            C.a[i]+=A.a[i]*b;
            C.a[i+1]+=C.a[i]/10;
            C.a[i]%=10;
        }
        while(C.a[C.len+1]){
            C.len++;
            C.a[C.len+1]+=C.a[C.len]/10;
            C.a[C.len]%=10;
        }
        while(C.a[C.len]==0&&C.len>0)C.len--;
        return C;
    }
    friend bigint operator / (const bigint &Z,const int &b) {
        bigint C=Z;
        int m=Z.len;
        for(register int i=m;i>=1;i--){
            if(i>1)C.a[i-1]+=C.a[i]%b*10;
            C.a[i]=C.a[i]/b;
        }
        while(C.a[m]==0&&m>0)m--;
        C.len=m;
        return C;
    }
};
//...
for(int i=9;i>=0;i--) {
    while(c[i]>0) {
        if(top==top2&&c[i]>0)a[++top]=i,c[i]--;
        if(top2<top&&c[i]>0)b[++top2]=i,c[i]--;
        if(top>0&&top2>0&&top==top2&&b[top2]<a[top])break;
    }
    if(top>0&&top2>0&&top==top2&&b[top2]<a[top])break;
}
for(int i=9;i>=0;i--) {
    while(c[i]>0) {
        if(top2==top&&c[i]>0){b[++top2]=i;c[i]--;}
        if(top<top2&&c[i]>0){a[++top]=i;c[i]--;}
    }
}
x.len=top;y.len=top2;
for(int i=1;i<=top;i++)x.a[top+1-i]=a[i];
for(int i=1;i<=top2;i++)y.a[top2+1-i]=b[i];
if(x.a[1]%2==0) {
    putb(x/2);putchar('\n');
    putb(y*2);
}
else {
    putb(y/2);putchar('\n');
    putb(x*2);
}
```
• **最优关键思路或技巧**：利用 “和一定时，两数差越小积越大” 这一数学性质进行贪心策略的设计，是确定乘积最大分配方式的关键。在处理数字数量不同的问题上，利用题目中给定数字至少有一个0（或至少有一个偶数）的条件，通过对以0结尾的数（或偶数）进行除以二，另一个数乘二的操作，巧妙改变数字数量，同时保证乘积不变。

• **可拓展思路**：同类型题可涉及更多数字组合与条件限制，如限定数字范围、改变数字数量要求等。类似算法套路可应用于其他需要通过贪心策略确定最优组合，再对结果进行特定条件调整的场景，例如资源分配类问题，先按某种最优原则分配资源，再根据特殊限制进行微调。

• **相似知识点洛谷题目**：
  - [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：通过贪心策略解决分配问题，与本题确定乘积最大的分配思路类似。
  - [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)：同样是利用贪心思想对元素进行排序分配，与本题贪心确定数字分配方式有相似之处。
  - [P1937 [USACO10MAR]Barn Allocation G](https://www.luogu.com.cn/problem/P1937)：涉及区间分配的贪心策略，与本题在策略设计上有相通之处。

• **个人心得摘录**：
  - **作者：JackMerryYoung**：赛时因未考虑等号情况导致错误，提醒在推导和设计算法时要全面考虑各种边界条件，避免因小失大。 

---
处理用时：54.00秒