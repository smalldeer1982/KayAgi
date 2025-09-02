# 高速フーリエ変換

## 题目描述

[problemUrl]: https://atcoder.jp/contests/atc001/tasks/fft_c

この問題は、講座用問題です。ページ下部に解説が掲載されています。

AtCoder 食堂では、定食のメニューを検討しています。

- 主菜は、価格が $ i $ 円のものが $ A_i $ 種類あります $ (1\ ≦\ i\ ≦\ N) $。
- 副菜は、価格が $ i $ 円のものが $ B_i $ 種類あります $ (1\ ≦\ i\ ≦\ N) $。

定食は、主菜と副菜を 1 種類ずつ選んで構成します。 定食の価格は、選んだ主菜と副菜の価格の和とします。

各 $ k\ (1\ ≦\ k\ ≦\ 2N) $ について、価格が $ k $ 円になる定食の種類の数を計算して下さい。

## 说明/提示

### 解説

  **[高速フーリエ変換](https://www.slideshare.net/secret/fc5RcW8Wkqciu "高速フーリエ変換")**  from **[AtCoder Inc.](http://www.slideshare.net/chokudai)** 

### Sample Explanation 1

\- $ 1 $ 円になる組合せは存在しない。 - $ 2 $ 円の組み合わせは、$ 1 $ 円の主菜と副菜が $ 1 $ 種類ずつなので $ 1 $ 通り。 - $ 3 $ 円の組み合わせは、$ 1×2\ +\ 2×1\ =\ 4 $ 通り。

## 样例 #1

### 输入

```
4
1 1
2 2
3 4
4 8```

### 输出

```
0
1
4
11
26
36
40
32```

# 题解

## 作者：Expert_Dreamer (赞：2)

这题看看没有思路，让我们把题目转化一下，如果说，菜的价格为多项式的指数，菜的数量为多项式系数，那么这题就转化为给定两个多项式 $A(x)$ 和 $B(x)$ 求 $A(x)B(x)$ 的每一项系数。

这不就 FFT 吗？不过，由于我太菜，我们换一种方法。

Atcoder 有自己专属的模板库，可以通过 `#include<atcoder/...>` 来获取，我们要计算卷积，就要用到 `#include<atcoder/convolution>`，它内部的代码是[这样的](https://www.luogu.com.cn/paste/spgb7zom)，可以发现，多项式卷积是基于 FFT 的，时间复杂度为 $O(n\log n)$，可以通过本题。`atcoder::convolution(A,B)` 可以用来计算来计算 $A(x)$ 和 $B(x)$ 的卷积。

```cpp
#include<bits/stdc++.h>
#include<atcoder/convolution>//导入
using namespace std;

signed main(){
    int n;
    cin>>n;
    vector<int>a(n),b(n);//函数只适用于vector。
    for(int i=0;i<n;i++) cin>>a[i]>>b[i];
    vector<int>c=atcoder::convolution(a,b);
    cout<<"0\n";//第一项一定为0
    for(int i:c) cout<<i<<endl;
}
```

---

## 作者：coderJerry (赞：0)

题目都写明了这是一道 FFT 板题。

将每道菜看成多项式的其中一项，由于方案数的计算时 $A$ 的每一项都要和 $B$ 的每一项乘起来，所以，令 $a(x)=A_1x+A_2x^2+...+A_nx^n,b(x)=B_1x+B_2x^2+...+B_nx^n$。最终答案的第 $2$ 到第 $2n$ 项就是多项式 $a(x)\times b(x)$ 的系数。而最终答案的第一项必定是 $0$，因为任何一道主菜加配菜的价格都至少是 $1+1=2$。FFT 一下即可。


```cpp
#include <bits/stdc++.h>
using namespace std;
const double PI=acos(-1);
struct Complex{
    double x,y;
    Complex(double _x=0.0,double _y=0.0){x=_x;y=_y;}
    Complex operator-(const Complex &b)const{return Complex(x-b.x,y-b.y);}
    Complex operator+(const Complex &b)const{return Complex(x+b.x,y+b.y);}
    Complex operator*(const Complex &b)const{return Complex(x*b.x-y*b.y,x*b.y+y*b.x);}
};
void fft(Complex y[],int len,int on) {
    for (int i=1,j=len/2;i<len-1;i++){
        if(i<j) swap(y[i],y[j]);
        int k=len/2;
        while(j>=k){j=j-k;k=k/2;}
        if(j<k) j+=k;
    }
    for (int h=2; h<=len; h<<=1) {
        Complex wn(cos(2*PI/h),sin(on*2*PI/h));
        for (int j=0;j<len;j+=h) {
            Complex w(1,0);
            for (int k=j;k<j+h/2;k++){
                Complex u=y[k];
                Complex t=w*y[k+h/2];
                y[k]=u+t;
                y[k+h/2]=u-t;
                w=w*wn;
            }
        }
    }
    if(on==-1) for(int i=0;i<len;i++) y[i].x/=len;
}
int n,ka,kb;
Complex a[1<<20],b[1<<20];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    cin>>n;
    for(int i=0;i<=n-1;i++){cin>>ka>>kb;a[i]=Complex(ka,0);b[i]=Complex(kb,0);}
    int size=1;
    while(size<n*2) size<<=1;
    fft(a,size,1);fft(b,size,1);
    for(int i=0;i<=size;i++) a[i]=a[i]*b[i];
    fft(a,size,-1);
    cout<<"0\n";
    for(int i=0;i<=2*n-2;i++) cout<<(int)(a[i].x+0.5)<<"\n";
    return 0;
}
```

---

