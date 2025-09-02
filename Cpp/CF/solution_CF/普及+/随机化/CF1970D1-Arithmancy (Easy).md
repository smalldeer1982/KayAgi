# Arithmancy (Easy)

## 题目描述

# 数字术 (简单)


维克多教授正在准备她的数字术课程。她需要为课程准备 $ n $ 个不同的魔法词。每个魔法词是一个由字符 X 和 O 组成的字符串。一个咒语是通过连接两个魔法词组成的字符串。咒语的能量等于它的不同非空子字符串的数量。例如，咒语 XOXO 的能量等于 7，因为它有 7 个不同的子字符串：X, O, XO, OX, XOX, OXO 和 XOXO。

每个学生将通过连接两个魔法词来创造他们自己的咒语。由于学生们对魔法还不太熟练，他们会独立且均匀地从提供的 $ n $ 个魔法词中随机选择两个词。因此，学生选择的两个词有可能是相同的。然后每个学生将计算他们咒语的能量，并告诉维克多教授。为了检查他们的作业，并当然为了给学生们留下深刻印象，维克多教授需要找出每个学生使用了哪两个魔法词以及它们的顺序来创建对应的咒语。

你的程序需要扮演维克多教授的角色：首先，创建 $ n $ 个不同的魔法词，然后处理多个请求，其中给定咒语能量并需要确定用于创建相应咒语的两个魔法词的索引及其正确顺序。

## 样例 #1

### 输入

```
2


2
15

11```

### 输出

```
XOXO
X


1 1

2 1```

# 题解

## 作者：FFTotoro (赞：0)

[点这里前往游记。](https://www.luogu.com.cn/article/u3edqf6r)

拿到这个题全场首杀。

记 $f(s)$ 为字符串 $s$ 本质不同的子串个数。对于一个字符串 $s$，可以借助 AtCoder Library 快速计算 $f(s)$（什么你说 CF 不带 AT Library？你把他们代码粘贴进你的代码即可）。

显然对于询问的一个 $f(x)$，要能唯一地对应回去那两个字符串 $s,t(s+t=x)$，这里 $+$ 表示连接。又由于还要确定两个字符串的顺序（即 $s+t$ 和 $t+s$ 是不同的），所以构造 $\texttt{O}$，$\texttt{OO}$，$\texttt{OOOO}$ 这样简单的构造是不行的。

这个时候考虑乱搞。因为 D1 中 $n\le 3$（以下就拿 $n=3$ 举例），而字符串长度限制是 $30n=90$，所以可以**在键盘上面乱敲或者直接随机 $3$ 个字符串**，然后判断是否对于所有的 $(i,j,k,l)(1\le i,j,k,l\le n)$ 满足 $f(w_i+w_j)\neq f(w_k+w_l)$。事实证明因为字符串数量很少而长度又很大，所以这 $3\times 3=9$ 个数做到两两不同是很容易的。

对于 D2，我们需要一些更加进阶的技巧：[D2 题解](https://www.luogu.com.cn/article/or4ir9cv)。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
  ios::sync_with_stdio(false);
  int n; cin>>n;
  if(n==1){
    cout<<"O"<<endl;
    int q; cin>>q;
    while(q--){
      int x,a,b; cin>>x;
      switch(x){
        case 2:a=1,b=1; break;
      }
      cout<<a<<' '<<b<<endl;
    }
  }
  if(n==2){
    cout<<"XOX\nOOOXXX"<<endl;
    int q; cin>>q;
    while(q--){
      int x,a,b; cin>>x;
      switch(x){
        case 14:a=1,b=1; break;
        case 34:a=1,b=2; break;
        case 33:a=2,b=1; break;
        case 51:a=2,b=2; break;
      }
      cout<<a<<' '<<b<<endl;
    } // 直接打表就行了
  }
  if(n==3){
    cout<<"XOX\nOOOXXX\nOOOOOOOOXXXXXXXXOXO"<<endl;
    int q; cin>>q;
    while(q--){
      int x,a,b; cin>>x;
      switch(x){
        case 14:a=1,b=1; break;
        case 34:a=1,b=2; break;
        case 183:a=1,b=3; break;
        case 33:a=2,b=1; break;
        case 51:a=2,b=2; break;
        case 240:a=2,b=3; break;
        case 180:a=3,b=1; break;
        case 237:a=3,b=2; break;
        case 483:a=3,b=3; break;
      }
      cout<<a<<' '<<b<<endl;
    }
  }
  return 0;
}
```

---

