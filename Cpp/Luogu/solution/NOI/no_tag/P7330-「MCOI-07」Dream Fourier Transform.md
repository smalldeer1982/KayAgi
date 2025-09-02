# 「MCOI-07」Dream Fourier Transform

## 题目背景

Dream 的红石计算机升级为 Dream 平台了。  
一个“Dream 程序”为一个在 Dream 平台下执行的程序。  
Dream 平台的内存由 $5\times2^{17}$ 个非负整数构成，这些内存位置依次标号为 $0,1,\dots,5\times2^{17}-1$。初始所有内存位置均为 $0$。  
Dream 平台有一个特性：第 $x$ 运算的结果在第 $x$ 内存位置存储，其中运算从 $0$ 编号。  
Dream 程序为若干运算的有序序列，运算类型为：

 1. `>`，表示输入一个非负整数，结果为输入值。
 2. `< x`，表示输出内存位置 `x` 所含的值，结果为这个值。
 3. `S c`，表示结果为常量非负整数 $c$，其中 $0\le c<998244353$。
 4. `+ x y`，表示结果为内存位置 `x` 的值 加 内存位置 `y` 的值。
 5. `- x y`，表示结果为内存位置 `x` 的值 减 内存位置 `y` 的值。
 6. `* x y`，表示结果为内存位置 `x` 的值 乘 内存位置 `y` 的值。

其中所有运算在模 $998244353$ 意义下计算。

## 题目描述

Dream 有一个长度为 $n$ 的序列 $a_0,a_1,\dots,a_{n-1}$。  

Dream 要支持两个操作：

 1. `1 i x`，表示将 $a_i$ 乘 $x$。
 2. `2 k`，表示定 $x=63912897^k$，并且求

$$\sum_{i=0}^{n-1}a_ix^i\pmod{998244353}$$

---

由战争及时，Dream 无法提供序列 $a$。他只能预测他会进行的操作。请构造一个“Dream 程序”，读入数组 $a$ 并且输出对应询问答案。  

## 说明/提示

#### 温情提示

$$63912897\equiv3^{\frac{998244352}{2^{12}}}\pmod{998244353}$$

#### 样例解释

当 Dream 程序输入为序列 `[1,2,3]`，输出为序列 `[6,347675984]`，符合要求。

#### 数据规模与约定

**本题采用捆绑测试。**

 - Subtask 1（11 pts）：$n,q\le2^8$
 - Subtask 2（19 pts）：所有询问操作在修改操作后面。
 - Subtask 3（23 pts）：$n,q\le2^{10}$
 - Subtask 4（47 pts）：没有特殊限制。

对于 $100\%$ 的数据，$1\le n,q\le2^{12}$，$0\le i<n$，$0\le x,k<998244353$。

## 样例 #1

### 输入

```
3 3
2 0
1 1 108616
2 114514```

### 输出

```
15
>
>
>
+ 0 1
+ 3 2
< 4
S 108616
S 716372446
* 1 6
* 8 7
* 7 7
* 2 10
+ 0 9
+ 12 11
< 13```

# 题解

## 作者：xujindong_ (赞：1)

我们需要维护维护一个长 $n=2^{12}$ 的动态 FFT，支持单点修改，单点查询 DFT，运算次数 $2.5n\sqrt n$。

如果直接在外面用数据结构的手法维护，因为 FFT 有 $\log$，最后很难纯正根号。考虑对 FFT 的结构动手。高低位分治，在 FFT 的某一层中，每对数 $x,y$ 若只有这一位不同，会变为 $f'_x\gets f_x+\omega f_y,f'_y\gets f_x-\omega f_y$。只做 $k$ 层，每个数会贡献到 $2^k$ 个位置。维护 FWT 做完前 $\frac k2(k=12)$ 层的结果，修改和查询都只涉及 $O(\sqrt n)$ 个位置。系数容易比较两个数的位计算。复杂度 $O(n\log n+q\sqrt n)$，其中 $O(q\sqrt n)$ 的常数是 $2$，可以通过。

下面的代码是经过位逆序置换后的 DIT，可能和正常写法有差别。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int n=4096,bn=64,bd=6,mod=998244353,w=63912897;
int m,l,wn[4096],rev[4096],a[4096],f[4096],c1[64][64],c2[4096];
ostringstream ans;
void modify(int x,int k){
  ans<<"S "<<k<<'\n',l++;
  ans<<"* "<<a[x]<<' '<<l-1<<'\n',l++;
  ans<<"- "<<l-1<<' '<<a[x]<<'\n',l++;
  a[x]=l-2,k=l-1;
  for(int i=0;i<bn;i++){
    ans<<"* "<<k<<' '<<c1[x>>bd][i]<<'\n',l++;
    ans<<"+ "<<f[i<<bd|(x&(bn-1))]<<' '<<l-1<<'\n',l++;
    f[i<<bd|(x&(bn-1))]=l-1;
  }
}
void query(int x){
  int pos=l++;
  ans<<"S 0\n",x=rev[x];
  for(int i=1,b;i<bn;i++)b=__builtin_ctz(i),c2[i]=(c2[i&(i-1)]+(rev[x>>(b+1)]>>1)+(x>>b&1?n/2:0))%n;
  for(int i=0;i<bn;i++){
    ans<<"* "<<f[(x&(n-bn))|i]<<' '<<c2[i]<<'\n',l++;
    ans<<"+ "<<pos<<' '<<l-1<<'\n',pos=l++;
  }
  ans<<"< "<<pos<<'\n',l++;
}
int main(){
  wn[0]=1;
  for(int i=1;i<n;i++)wn[i]=1ll*w*wn[i-1]%mod,rev[i]=rev[i>>1]>>1|(i&1?n>>1:0);
  for(int i=0;i<n;i++)ans<<"S "<<wn[i]<<'\n',l++;
  for(int x=0;x<bn;x++)for(int y=0;y<bn;y++)for(int i=0;i<bd;i++)if(x>>i&1)c1[x][y]=(c1[x][y]+(rev[y>>(i+1)]>>1)+(y>>i&1?n/2:0))%n;
  cin>>m;
  for(int i=0;i<n;i++)ans<<(i<m?">\n":"S 0\n"),a[i]=f[i]=l++;
  for(int i=n>>1;i>=bn;i>>=1){
    for(int j=0,p=0;j<n;j+=i<<1,p++){
      for(int k=j,y;k<j+i;k++){
        ans<<"* "<<f[k+i]<<' '<<(rev[p]>>1)<<'\n',y=l++;
        ans<<"- "<<f[k]<<' '<<y<<'\n',f[k+i]=l++;
        ans<<"+ "<<f[k]<<' '<<y<<'\n',f[k]=l++;
      }
    }
  }
  cin>>m;
  for(int i=1,opt,x,k;i<=m;i++){
    cin>>opt;
    if(opt==1)cin>>x>>k,modify(x,k);
    else cin>>k,k%=n,query(k);
  }
  return cout<<l<<'\n'<<ans.str(),0;
}
```

---

