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

• 综合分析与结论：这些题解的核心思路均是先通过贪心策略确定使乘积最大的两个数的分配方式，再处理如何让这两个数的数字数量与给定数量不同。算法要点在于利用“两数和一定，差越小积越大”的性质，从大到小分配数字。解决难点主要集中在如何巧妙地调整数字组合以满足数字数量不同的要求。

所选的题解：
  - 作者：bh1234666 (赞：15)  星级：5星
    - 关键亮点：思路清晰全面，先通过将整数变为小数的方式证明大数应在高位，两数长度差至多为1，且和一定时要使差最小。对于让两数数字数量不同的处理方法独特且巧妙，利用必有一数以0结尾的特性，通过一数乘二一数除以二的方式解决，代码实现简洁明了。
    - 个人心得：无
    - 重点代码核心思想：`half`函数实现高精度数除以2，`dble`函数实现高精度数乘以2。主函数中先按贪心策略分配数字得到两个数，再根据哪个数以0结尾决定对哪个数进行乘二或除以二操作。
```cpp
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
  - 作者：linyuhao (赞：7)  星级：4星
    - 关键亮点：思路表述清晰，先明确乘积最大的原理，即从大到小依次放入数字使两个数串差值最小。对于数串不同的处理方法，利用必有一个零，通过去掉一个末尾零，一个数串乘2，另一个数串乘5的方式解决，代码实现详细且注释丰富。
    - 个人心得：无
    - 重点代码核心思想：先读入各数字个数并拼接成字符串，然后从大到小按规则分配数字到两个字符串`s1`和`s2`。`sh`函数实现低精乘高精，最后对`s1`乘2，`s2`乘5并输出。
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
  - 作者：Full_Speed (赞：2)  星级：4星
    - 关键亮点：利用高精度运算模板解决大数计算问题，思路清晰，先通过贪心确定使乘积最大的两个数，再根据必有偶数的特性，通过一数乘二一数除以二的方式满足数字数量不同的要求，代码结构完整。
    - 个人心得：无
    - 重点代码核心思想：定义`bigint`结构体实现高精度数的乘法和除法运算。主函数中先按贪心策略分配数字得到两个高精度数`x`和`y`，再根据`x`或`y`的首位是否为偶数决定对哪个数进行乘二或除以二操作并输出。
```cpp
struct bigint{         //高精模板 
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
    for(int i=9;i>=0;i--)      //使乘积最大 
    {
        while(c[i]>0)         //首先让一个数的高位大于另一个数 
        {
            if(top==top2&&c[i]>0)a[++top]=i,c[i]--;
            if(top2<top&&c[i]>0)b[++top2]=i,c[i]--;
            if(top>0&&top2>0&&top==top2&&b[top2]<a[top])break;
        }
        if(top>0&&top2>0&&top==top2&&b[top2]<a[top])break;
    }
    for(int i=9;i>=0;i--)      //然后使较小的数低位更大 
    {
        while(c[i]>0)
        {
            if(top2==top&&c[i]>0){b[++top2]=i;c[i]--;}
            if(top<top2&&c[i]>0){a[++top]=i;c[i]--;}
        }
    }                           //a*b即为最大乘积 
    x.len=top;y.len=top2;
    for(int i=1;i<=top;i++)x.a[top+1-i]=a[i];
    for(int i=1;i<=top2;i++)y.a[top2+1-i]=b[i];
    if(x.a[1]%2==0)              //判断奇偶 
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

最优关键思路或技巧：利用“两数和一定，差越小积越大”的数学原理进行贪心策略分配数字，同时巧妙利用题目中数字数量的限制条件（必有0或必有偶数），通过对其中一个数乘2，另一个数除以2的方式，简洁高效地解决使两数数字数量与给定数量不同的问题。

可拓展思路：同类型题通常围绕数字组合、乘积最值等问题展开，类似算法套路是先确定使目标最优（如乘积最大、和最小等）的分配策略，再处理额外限制条件。例如在一些数字拼接求最值问题中，也可利用类似的贪心策略，结合数字特性来解决问题。

推荐洛谷题目：
1. P1018 [NOIP2000 提高组] 乘积最大：同样是关于数字组合求乘积最大的问题，可进一步巩固贪心策略的应用。
2. P1223 排队接水：通过贪心算法解决排队时间最优问题，与本题利用贪心思想确定最优分配有相似之处。
3. P1993 小 K 的农场：涉及到利用贪心策略和差分约束系统解决问题，对贪心思想的拓展应用有帮助。

个人心得摘录与总结：无。 

---
处理用时：108.95秒