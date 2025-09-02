# 题目信息

# [ABC347D] Popcount and XOR

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc347/tasks/abc347_d

非負整数 $ a,b,C $ が与えられます。 次の $ 5 $ つの条件をすべて満たす非負整数の組 $ (X,Y) $ が存在するか判定し、存在するならひとつ出力してください。

- $ 0\leq\ X\lt2\ ^\ {60} $
- $ 0\leq\ Y\lt2\ ^\ {60} $
- $ \operatorname{popcount}(X)=a $
- $ \operatorname{popcount}(Y)=b $
- $ X\oplus\ Y=C $

ただし、$ \oplus $ はビットごとの排他的論理和を表します。

条件を満たす $ (X,Y) $ が複数存在する場合、どれを出力しても構いません。

popcount とは？非負整数 $ x $ について $ x $ の popcount とは、$ x $ を $ 2 $ 進法で表記したときの $ 1 $ の個数です。 より厳密には、非負整数 $ x $ について $ \displaystyle\ x=\sum\ _\ {i=0}\ ^\ \infty\ b\ _\ i2\ ^\ i\ (b\ _\ i\in\lbrace0,1\rbrace) $ が成り立っているとき $ \displaystyle\operatorname{popcount}(x)=\sum\ _\ {i=0}\ ^\ \infty\ b\ _\ i $ です。

例えば、$ 13 $ を $ 2 $ 進法で表記すると `1101` なので、 $ \operatorname{popcount}(13)=3 $ となります。 ビットごとの排他的論理和とは？非負整数 $ x,y $ について $ x,y $ のビットごとの排他的論理和 $ x\oplus\ y $ は以下のように定義されます。

- $ x\oplus\ y $ を $ 2 $ 進法で表記したときの $ 2\ ^\ k\ (k\geq0) $ の位は、$ x,y $ を $ 2 $ 進法で表記したときの $ 2\ ^\ k\ (k\geq0) $ の位の数のうち一方のみが $ 1 $ であれば $ 1 $ 、そうでなければ $ 0 $ となる。

例えば、$ 9,3 $ を $ 2 $ 進法で表記するとそれぞれ `1001`, `0011` なので、$ 9\oplus3=10 $ となります（$ 10 $ を $ 2 $ 進法で表記すると `1010` です）。

## 说明/提示

### 制約

- $ 0\leq\ a\leq60 $
- $ 0\leq\ b\leq60 $
- $ 0\leq\ C\lt2\ ^\ {60} $
- 入力はすべて整数

### Sample Explanation 1

$ (X,Y)=(28,27) $ は条件を満たします。 $ X,Y $ を $ 2 $ 進法で表記するとそれぞれ `11100` と `11011` になります。 - $ X $ を $ 2 $ 進法で表記すると `11100` になるので、$ \operatorname{popcount}(X)=3 $ です。 - $ Y $ を $ 2 $ 進法で表記すると `11011` になるので、$ \operatorname{popcount}(Y)=4 $ です。 - $ X\oplus\ Y $ を $ 2 $ 進法で表記すると `00111` となり、$ X\oplus\ Y=7 $ です。 条件を満たす非負整数の組が複数存在する場合どれを出力しても構わないため、例えば `42 45` と出力しても正解になります。

### Sample Explanation 2

条件を満たす非負整数の組は存在しません。

### Sample Explanation 3

出力すべき値が $ 32\operatorname{bit} $ 整数に収まらない場合があります。

## 样例 #1

### 输入

```
3 4 7```

### 输出

```
28 27```

## 样例 #2

### 输入

```
34 56 998244353```

### 输出

```
-1```

## 样例 #3

### 输入

```
39 47 530423800524412070```

### 输出

```
540431255696862041 10008854347644927```

# AI分析结果

### 题目内容中文重写
给定非负整数 $a$、$b$ 和 $C$。请判断是否存在一对非负整数 $(X, Y)$ 满足以下五个条件，如果存在则输出其中一组：
- $0\leq X\lt2^{60}$
- $0\leq Y\lt2^{60}$
- $\text{popcount}(X)=a$（$\text{popcount}(x)$ 表示 $x$ 二进制表示中 $1$ 的个数）
- $\text{popcount}(Y)=b$
- $X\oplus Y = C$（$\oplus$ 表示按位异或）

如果有多对 $(X, Y)$ 满足条件，输出任意一组即可。

### 综合分析与结论
这些题解的核心思路都是基于异或运算的性质来构造满足条件的 $X$ 和 $Y$。异或运算的性质为：当 $C$ 的某一位为 $1$ 时，$X$ 和 $Y$ 对应位一个为 $1$ 一个为 $0$；当 $C$ 的某一位为 $0$ 时，$X$ 和 $Y$ 对应位相同（都为 $0$ 或都为 $1$）。

#### 思路与算法要点
- **判断无解情况**：多数题解都提到了几种无解的判断条件，如 $a + b\lt\text{popcount}(C)$（$X$、$Y$ 中 $1$ 的总数不足以凑出 $C$ 中的 $1$）、$(a + b - \text{popcount}(C))\bmod 2 = 1$（多余的 $1$ 无法两两抵消）、$\vert a - b\vert\gt\text{popcount}(C)$（$X$、$Y$ 中 $1$ 的数量差距过大无法平衡）等。
- **构造 $X$ 和 $Y$**：
    - 先处理 $C$ 中为 $1$ 的位，根据 $a$ 和 $b$ 的剩余数量决定将该位的 $1$ 分配给 $X$ 还是 $Y$。
    - 再处理 $C$ 中为 $0$ 的位，若 $a$ 和 $b$ 还有剩余且相等，则将 $X$ 和 $Y$ 的对应位都设为 $1$。

#### 解决难点
- **无解判断**：准确判断无解情况是关键，不同题解给出了多种判断条件，需要综合考虑。
- **构造方案**：合理分配 $1$ 的位置，确保满足所有条件，同时要注意边界情况，如结果不能超过 $2^{60}$。

### 所选题解
- **作者：wangbinfeng (赞：4)，4星**
    - **关键亮点**：思路清晰，详细阐述了无解的判断条件，代码使用 `bitset` 进行二进制操作，可读性较高。
    - **个人心得**：无
- **作者：zengziqvan (赞：4)，4星**
    - **关键亮点**：思维含量高，详细分析了异或运算的性质，采取的策略简单有效，时间复杂度为 $\text{O}(\log C)$。
    - **个人心得**：无
- **作者：StormWhip (赞：2)，4星**
    - **关键亮点**：思路简洁明了，代码实现逻辑清晰，通过快速幂和数组存储二进制，将二进制转换为十进制输出。
    - **个人心得**：无

### 重点代码
#### wangbinfeng 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int popcnt(long long x){
    int ret=0;
    for(;x;x&=x-1)ret++;
    return ret;
}
long long a,b,c;
signed main(){
    ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    cin>>a>>b>>c;
    if(a+b<popcnt(c)||(a+b-popcnt(c))%2){printf("-1");return 0;}
    if((a+b-popcnt(c))/2>(60-popcnt(c))){printf("-1");return 0;}
    if((a-b>popcnt(c)||b-a>popcnt(c))){printf("-1");return 0;}
    bitset<60>d(c);
    bitset<60>e,f;
    e.reset(),f.reset();
    for(int i=0;i<60;i++){
        if(a+b==popcnt(c))break;
        if(d[i]==false)e[i]=f[i]=true,a--,b--;
    }
    for(int i=0;i<60;i++){
        if(d[i]&&a-->0)
            e[i]=true;
        else{if(d[i]&&b-->0)
            f[i]=true;}
    }
    cout<<e.to_ullong()<<' '<<f.to_ullong();
}
```
**核心实现思想**：先判断无解情况，然后将 $C$ 转换为二进制 `bitset`，对于 $C$ 中为 $0$ 的位，若 $a$ 和 $b$ 还有剩余则将 $X$ 和 $Y$ 对应位都设为 $1$；对于 $C$ 中为 $1$ 的位，根据 $a$ 和 $b$ 的剩余数量分配 $1$。最后将 `bitset` 转换为十进制输出。

#### zengziqvan 的代码
```c++
#include <bits/stdc++.h>
using namespace std;
int a,b,in[70],tot,cnt1,A[70],B[70],tot1,tot2,c;
main() {
    cin>>a>>b>>c;
    ROF(i,60,0) in[++tot]=((c>>i)&1);
    reverse(in+1,in+tot+1); 
    FOR(i,1,tot) {
        if(in[i]) {
            if(a<=b) {
                B[i]=1;
                b--;
            } else {
                A[i]=1;
                a--;
            }
        } 
    }
    if(a!=b) {
        puts("-1");
        return 0;
    }
    FOR(i,1,tot) {
        if(a&&!in[i]) {
            A[i]=1;
            B[i]=1;
            a--;
            b--;
        } 
    }
    if(a) {
        puts("-1");
        return 0;
    }
    FOR(i,1,tot) res1+=(ll)(A[i]<<(i-1));
    FOR(i,1,tot) res2+=(ll)(B[i]<<(i-1));
    cout<<res1<<" "<<res2<<"\n";
    return 0;
}
```
**核心实现思想**：先将 $C$ 转换为二进制存储在数组中，对于 $C$ 中为 $1$ 的位，根据 $a$ 和 $b$ 的大小分配 $1$。分配完后若 $a$ 和 $b$ 不相等则无解，否则对于 $C$ 中为 $0$ 的位，若 $a$ 和 $b$ 还有剩余则将 $X$ 和 $Y$ 对应位都设为 $1$。最后将二进制数组转换为十进制输出。

#### StormWhip 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=65;
unsigned long long x[N],y[N],t[N],c;
int a,b,now_2=60;
unsigned long long Pows(unsigned long long base,int p)
{
    if(p==1) return base;
    if(p==0) return 1;
    unsigned long long cnt=Pows(base,p/2),ans=cnt*cnt;
    if(p%2==1) ans=ans*base;
    return ans;
}
void Print()
{
    unsigned long long ansx=0,ansy=0;
    for(int j=0;j<60;j++)
        ansx+=x[j]*Pows(2,j);
    for(int j=0;j<60;j++)
        ansy+=y[j]*Pows(2,j);
    cout<<ansx<<" "<<ansy<<"\n";
    exit(0);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>a>>b>>c;
    while(c!=0)
    {        
        if(c>=Pows(2,now_2))
        {
            t[now_2]=1;
            c-=Pows(2,now_2);                    
        }
        now_2--;
    }
    for(int i=0;i<60;i++)
        if(t[i])
        {
            if(a>b) x[i]=1,y[i]=0,a--;
            else x[i]=0,y[i]=1,b--;
        }
    if(a==0&&b==0) Print();
    for(int i=0;i<60;i++)
        if(x[i]==0&&y[i]==0)
        {
            a--;
            b--;
            x[i]=1;
            y[i]=1;
            if(a==0&&b==0) Print();
        }
    cout<<"-1\n";
    return 0;
}
```
**核心实现思想**：先将 $C$ 转换为二进制存储在数组中，对于 $C$ 中为 $1$ 的位，根据 $a$ 和 $b$ 的大小分配 $1$。若 $a$ 和 $b$ 都为 $0$ 则直接输出结果，否则对于 $X$ 和 $Y$ 都为 $0$ 的位，将其都设为 $1$，直到 $a$ 和 $b$ 都为 $0$ 。若最后 $a$ 和 $b$ 还有剩余则无解。

### 最优关键思路或技巧
- **利用异或性质**：根据异或运算的特点，将问题转化为对 $C$ 二进制位的处理，通过合理分配 $1$ 的位置来构造 $X$ 和 $Y$。
- **无解判断**：总结多种无解的判断条件，在构造前先进行判断，避免不必要的计算。
- **二进制操作**：使用 `bitset` 或数组存储二进制，方便进行位操作和转换。

### 可拓展之处
同类型题目可能会改变条件，如限制 $X$ 和 $Y$ 的范围、增加其他约束条件等。类似算法套路可以应用于其他位运算相关的构造问题，通过分析位运算的性质来找到解题思路。

### 推荐洛谷题目
- [P1100 高低位交换](https://www.luogu.com.cn/problem/P1100)
- [P1328 生活大爆炸版石头剪刀布](https://www.luogu.com.cn/problem/P1328)
- [P2114 [NOI2014] 起床困难综合症](https://www.luogu.com.cn/problem/P2114)

### 个人心得摘录与总结
- **Kyl_in_2024**：提到了一些无解的判断条件，如 $a + b\lt\text{popcount}(C)$、$a + b - \text{popcount}(C)$ 为奇数、$a\lt b - \text{popcount}(C)$ 等，还强调了要注意结果不能超过 $2^{60}$，否则也无解。总结：在解题过程中要全面考虑各种边界情况和无解条件，避免遗漏。
- **liangjindong0504**：提醒要开 `long long` 以及 `pow` 要先转成 `long long` 类型。总结：在处理大数和幂运算时，要注意数据类型的选择，避免溢出。 

---
处理用时：72.37秒