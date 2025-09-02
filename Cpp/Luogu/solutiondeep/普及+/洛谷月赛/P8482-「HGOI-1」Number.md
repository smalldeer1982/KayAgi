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

• 综合分析与结论：
    - 思路方面，多数题解先利用贪心策略确定如何分配数字使两数乘积最大，即让大数字在高位且两数差最小，基于两数和一定时，差越小积越大的原理。之后考虑如何使生成的两数数字数量与给定数量不同，利用数据中至少有一个0的条件，对末尾为0的数进行除以2操作，另一数乘2，改变数字数量同时保证乘积不变。
    - 算法要点在于从大到小遍历数字，合理分配到两个数中，保证两数和最大且差最小，最后通过乘除2的操作满足题目条件。
    - 解决难点主要是证明贪心策略的正确性以及如何巧妙利用条件改变数字数量。

    - 整体来看，各题解思路相近，部分题解在代码实现和思路阐述的清晰度上存在差异。

• 所选的题解：
  - 作者：bh1234666 (5星)
    - 关键亮点：思路阐述详细，从将整数转化为小数分析乘积性质，证明贪心策略的正确性，逻辑严谨。代码实现简洁明了，对乘除2的操作编写了独立函数，增强了代码可读性。
    - 个人心得：无
    ```cpp
    #include<stdio.h>
    char s1[1000005],s2[1000005];int l1,l2;
    void half(char *s,int len)
    {
        int i;
        for(i=0;i<len;i++)
        {
            s[i]-='0';
            if(s[i]&1) s[i+1]+=10;
            s[i]>>=1;
            s[i]+='0';
        }
        if(s[0]=='0') puts(s+1);
        else puts(s);
    }
    void dble(char *s,int len)
    {
        int i;_Bool fl=0;
        for(i=len-1;i>=0;i--)
        {
            s[i]-='0';
            if(s[i]>4) s[i]<<=1,s[i]-=10,s[i]+=fl,fl=1;
            else s[i]<<=1,s[i]+=fl,fl=0;
            s[i]+='0';
        }
        if(fl) putchar('1');
        puts(s);
    }
    int main()
    {
        int i,j,a[10];_Bool flag=0;
        for(i=0;i<10;i++)
            scanf("%d",&a[i]);
        for(j=0,i=9;j<2;j++)
        {
            for(;j&&i>=0;i--)
                if(a[i])
                {
                    a[i]--;
                    s2[l2++]='0'+i;
                    break;
                }
            for(;i>=0;i--)
            {
                while(a[i])
                {
                    a[i]--;
                    if(!flag) s1[l1++]='0'+i;
                    else s2[l2++]='0'+i;
                    flag=!flag;
                }
                if(flag&&!j) break;
            }
        }
        if(s1[l1-1]=='0')
        {
            half(s1,l1);
            dble(s2,l2);
        }
        else
        {
            half(s2,l2);
            dble(s1,l1);
        }
        return 0;
    }
    ```
    - 核心代码实现思想：首先通过双重循环从大到小分配数字到两个字符数组s1和s2中。然后根据s1或s2末尾是否为'0'，调用half函数对其除以2，调用dble函数对另一个数组乘2并输出。
  - 作者：linyuhao (4星)
    - 关键亮点：思路清晰，先阐述乘积最大的原理，再说明数字分配方法，最后给出改变数字数量的具体做法，代码实现过程详细，注释丰富。
    - 个人心得：无
    ```cpp
    #include<bits/stdc++.h>
    using namespace std;
    int c[10000001]={0},a[10000001]={0},b[10000001]={0};
    inline int read(){
        int x=0,f=1;
        char ch=getchar();
        while(ch<'0'||ch>'9'){
            if(ch=='-')
                f=-1;
            ch=getchar();
        }
        while(ch>='0'&&ch<='9'){
            x=(x<<1)+(x<<3)+(ch^48);
            ch=getchar();
        }
        return x*f;
    }
    string s1,s2,s;
    int pd=0;
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
    long long aa[10];
    int main(){
        int ans=0;
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
        return 0;
    }
    ```
    - 核心代码实现思想：先读入各数字数量，将所有数字按从大到小顺序存入字符串s。然后通过循环从s中依次取出数字，根据两数大小关系分配到s1和s2中。最后调用sh函数分别对s1乘2、s2乘5并输出，利用pd判断是否只去掉一个零。
  - 作者：Full_Speed (4星)
    - 关键亮点：代码结构清晰，定义了高精度运算的结构体，将问题分为求最大乘积和改变数字数量两部分，逻辑明确。
    - 个人心得：无
    ```c
    #include<iostream>
    #include<cstdio>
    #include<cstring>
    #include<algorithm>
    using namespace std;
    long long c[10];
    int a[5000010],b[5000010];
    using namespace std;
    struct bigint{
        int a[5000010],len,ff;
        bigint(){memset(a,0,sizeof(a));len=0;ff=0;}
        friend void putb(bigint Z)
        {
            if(Z.len==0)putchar('0');
            else 
            {
                if(Z.ff==1)putchar('-');
                for(register int i=Z.len;i>=1;i--)putchar(Z.a[i]+'0');
            }
            return;
        }
        friend bigint operator * (const bigint &A,const int &b)
        {
            bigint C;C.len=A.len;
            for(register int i=1;i<=A.len;i++)
            {
                C.a[i]+=A.a[i]*b;
                C.a[i+1]+=C.a[i]/10;
                C.a[i]%=10;
            }
            while(C.a[C.len+1])
            {
                C.len++;
                C.a[C.len+1]+=C.a[C.len]/10;
                C.a[C.len]%=10;
            }
            while(C.a[C.len]==0&&C.len>0)C.len--;
            return C;
        }
        friend bigint operator / (const bigint &Z,const int &b)
        {
            bigint C=Z;
            int m=Z.len;
            for(register int i=m;i>=1;i--)
            {
                if(i>1)C.a[i-1]+=C.a[i]%b*10;
                C.a[i]=C.a[i]/b;
            }
            while(C.a[m]==0&&m>0)m--;
            C.len=m;
            return C;
        }
    };
    int main()
    {
        bigint x,y;
        for(int i=0;i<=9;i++)scanf("%d",&c[i]);
        int top=0,top2=0;
        for(int i=9;i>=0;i--)
        {
            while(c[i]>0)
            {
                if(top==top2&&c[i]>0)a[++top]=i,c[i]--;
                if(top2<top&&c[i]>0)b[++top2]=i,c[i]--;
                if(top>0&&top2>0&&top==top2&&b[top2]<a[top])break;
            }
            if(top>0&&top2>0&&top==top2&&b[top2]<a[top])break;
        }
        for(int i=9;i>=0;i--)
        {
            while(c[i]>0)
            {
                if(top2==top&&c[i]>0){b[++top2]=i;c[i]--;}
                if(top<top2&&c[i]>0){a[++top]=i;c[i]--;}
            }
        }
        x.len=top;y.len=top2;
        for(int i=1;i<=top;i++)x.a[top+1-i]=a[i];
        for(int i=1;i<=top2;i++)y.a[top2+1-i]=b[i];
        if(x.a[1]%2==0)
        {
            putb(x/2);putchar('\n');
            putb(y*2);
        }
        else
        {
            putb(y/2);putchar('\n');
            putb(x*2);
        }
        return 0;
    }
    ```
    - 核心代码实现思想：利用结构体bigint实现高精度乘除运算。在main函数中，先读入各数字数量，通过两轮循环从大到小分配数字到数组a和b中，构建两个高精度数x和y。最后根据x或y的首位数字奇偶性，对其中一个除以2，另一个乘2并输出。

• 最优关键思路或技巧：
    - 思维方式上，将问题拆分为求最大乘积和改变数字数量两部分，先利用贪心确定数字分配使乘积最大，再巧妙利用数据条件改变数字数量。
    - 代码实现技巧方面，部分题解将乘除2操作封装成函数，增强代码可读性；有的题解使用结构体实现高精度运算，使代码结构更清晰。

• 可拓展之处：
同类型题可考察不同条件下数字组合求最值问题，类似算法套路是先确定使目标最优的贪心策略，再根据题目限制条件进行调整。例如给定数字组成多个数，求这些数的某种运算结果最值等。

• 相似知识点洛谷题目：
    - P1080 [NOIP2012 提高组] 国王游戏：通过贪心策略确定排列顺序求最值。
    - P1248 加工生产调度：利用贪心思想解决生产调度中的最优安排问题。
    - P2123 皇后游戏：同样是通过证明贪心策略正确性来解决双属性排序求最值问题。

• 个人心得摘录与总结：
    - 作者JackMerryYoung提到赛时因未考虑等号情况导致错误，强调了在证明和实现算法时要全面考虑各种情况，避免因边界条件疏忽而出错。 

---
处理用时：115.59秒