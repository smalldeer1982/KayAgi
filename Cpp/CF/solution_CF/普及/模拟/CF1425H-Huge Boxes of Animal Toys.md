# Huge Boxes of Animal Toys

## 题目描述

Chaneka has a hobby of playing with animal toys. Every toy has a different fun value, a real number. Chaneka has four boxes to store the toys with specification:

- The first box stores toys with fun values in range of $ (-\infty,-1] $ .
- The second box stores toys with fun values in range of $ (-1, 0) $ .
- The third box stores toys with fun values in range of $ (0, 1) $ .
- The fourth box stores toys with fun value in range of $ [1, \infty) $ .

Chaneka has $ A $ , $ B $ , $ C $ , $ D $ toys in the first, second, third, and fourth box, respectively. One day she decides that she only wants one toy, a super toy. So she begins to create this super toy by sewing all the toys she has.

While the number of toys Chaneka has is more than 1, she takes two different toys randomly and then sews them together, creating a new toy. The fun value of this new toy is equal to the multiplication of fun values of the sewn toys. She then puts this new toy in the appropriate box. She repeats this process until she only has one toy. This last toy is the super toy, and the box that stores this toy is the special box.

As an observer, you only know the number of toys in each box initially but do not know their fun values. You also don't see the sequence of Chaneka's sewing. Determine which boxes can be the special box after Chaneka found her super toy.

## 说明/提示

For the first case, here is a scenario where the first box is the special box:

- The first box had toys with fun values $ \{-3\} $ .
- The second box had toys with fun values $ \{ -0.5, -0.5 \} $
- The fourth box had toys with fun values $ \{ 3 \} $

The sewing sequence:

1. Chaneka sews the toy with fun $ -0.5 $ and $ -0.5 $ to a toy with fun $ 0.25 $ and then put it in the third box.
2. Chaneka sews the toy with fun $ -3 $ and $ 0.25 $ to a toy with fun $ -0.75 $ and then put it in the second box.
3. Chaneka sews the toy with fun $ -0.75 $ and $ 3 $ to a toy with fun $ -1.25 $ and then put it in the first box, which then became the special box.

Here is a scenario where the second box ends up being the special box:

- The first box had toys with fun values $ \{-3\} $
- The second box had toys with fun values $ \{ -0.33, -0.25 \} $ .
- The fourth box had toys with fun values $ \{ 3 \} $ .

The sewing sequence:

1. Chaneka sews the toy with fun $ -3 $ and $ -0.33 $ to a toy with fun $ 0.99 $ and then put it in the third box.
2. Chaneka sews the toy with fun $ 0.99 $ and $ 3 $ to a toy with fun $ 2.97 $ and then put in it the fourth box.
3. Chaneka sews the toy with fun $ 2.97 $ and $ -0.25 $ to a toy with fun $ -0.7425 $ and then put it in the second box, which then became the special box.

 There is only one toy for the second case, so Chaneka does not have to sew anything because that toy, by definition, is the super toy.

## 样例 #1

### 输入

```
2
1 2 0 1
0 1 0 0```

### 输出

```
Ya Ya Tidak Tidak
Tidak Ya Tidak Tidak```

# 题解

## 作者：President_Guan (赞：0)

## [CF1425H Huge Boxes of Animal Toys](https://www.luogu.com.cn/problem/CF1425H)
### 题目大意
有 $A$ 个大小为 $(-∞,-1]$ 的数，有 $B$ 个大小为 $(-1,0)$ 的数，有 $C$ 个大小为 $(0,1)$ 的数，有 $D$ 个大小为 $[1,∞)$ 的数。

现在将 $A+B+C+D$ 个数乘起来，分别问乘积是否在上述该范围内。

### 主要思路
先解决符号的问题，众所周知，乘积的正负只与负数的个数有关。所以，$A+B$ 如果为偶数，最后乘积的范围只有可能在第一个和第二个范围，反之同理。

然后在解决绝对值的问题，由于这些数可以是范围内任何的数，那么我们只需要考虑极端情况即可。只要有一个数的绝对值在 $D$ 里，我们让它无穷趋近于 $∞$，乘积的绝对值也趋近于 $∞$。同理，只要有一个数的绝对值在 $C$ 里，我们让它无穷趋近于 $0$，乘积的绝对值就趋近于 $0$。

### AC Code
```
#include<bits/stdc++.h>
using namespace std;
long long t,a,b,c,d;
bool a1,b1,c1,d1; 
long long n;
int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
	    cin>>a>>b>>c>>d;
            n=a+b;
	    if(n%2==1){
               if((a+d)>0) a1=1;
               if((b+c)>0) b1=1;
            }
            if(n%2==0){
               if((a+d)>0) d1=1;
               if((b+c)>0) c1=1;
            }
	    if(a1==1) cout<<"Ya ";
	    else cout<<"Tidak ";
	    if(b1==1) cout<<"Ya ";
	    else cout<<"Tidak ";
	    if(c1==1) cout<<"Ya ";
	    else cout<<"Tidak ";
	    if(d1==1) cout<<"Ya ";
	    else cout<<"Tidak ";
	    cout<<endl;
	    a1=0;b1=0;c1=0;d1=0;
	}
	
	return 0;
}
```

---

## 作者：WaterSky (赞：0)

# [CF1425H Huge Boxes of Animal Toys。](https://www.luogu.com.cn/problem/CF1425H)

## 算法：
这是一道我觉得比较好玩的数学题。

首先，我们要知道负负得正，即偶数个负数的乘积必定为整数，那么我们就可以判断，$A$ 中数的数量与 $B$ 中数的数量的和是否为偶数，如果是，就有可能在 $C$ 和 $D$ 中，否则在 $A$ 和 $B$ 中。

我们可以给那些数赋值为极端。

如果有一个数在 $D$ 中，让 $C$ 的数设为无限接近 $1$，那么答案就在 $D$ 中。

其他的三种情况也一样。

## 代码：
```
#include<bits/stdc++.h>
using namespace std;
long long t,A,B,C,D;
int main(){
    cin>>t;
    while(t--)
	{
        cin>>A>>B>>C>>D;
        if((A+B)%2==1)
		{
            if(D || A) A=1,D=0;
            if(B || C) B=1,C=0;
        }
		else
		{
            if(D || A) A=0,D=1;
            if(B || C) B=0,C=1;
        }
        cout<<(A?"Ya ":"Tidak ");
        cout<<(B?"Ya ":"Tidak ");
        cout<<(C?"Ya ":"Tidak ");
        cout<<(D?"Ya ":"Tidak ");
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：UniGravity (赞：0)

## Solution CF1425H Huge Boxes of Animal Toys
[题目传送门](https://www.luogu.com.cn/problem/CF1425H)   
[点击前往博客食用](https://www.luogu.com.cn/blog/ansmod998244353/)

### 题意简述
有 $a$ 个数在 $(-\infty, -1]$ 中，$b$ 个数在 $(-1, 0)$ 中，$c$ 个数在 $(0, 1)$ 中，$d$ 个数在 $[1, +\infty)$ 中。  

现在要将所有 $a+b+c+d$ 个数乘起来，分别求对于上述 $4$ 个区间，答案是否可能在该区间内。

### 题目分析
我们首先不考虑负数情况，只考虑 $x$ 个数字在 $(0, 1)$ 中，$y$ 个数字在 $[1, +\infty)$ 中。  
由于题目要求的是可能的取值，我们考虑极端情况，对于一个在 $(0, 1)$ 中的数字，我们令它**无穷趋近**于 $0$，可以发现最后的答案也**无穷趋近**于 $0$。  
同理，对于一个在 $[1, +\infty)$ 中的数字，我们让它**趋近**于 $\infty$，答案也**趋近**于 $\infty$。  
可以发现，只要 $x$ 的个数大于 $0$，答案就可能在 $(0, 1)$ 中。只要 $y$ 的个数大于 $0$，答案就可能在 $[1, +\infty)$ 中。

那么我们把负数加入进来。易发现答案的正负只与负数的个数有关：若 $a+b$ 是 $2$ 的倍数，负负得正，最后的答案为正；反之，若 $a+b\bmod 2 = 1$，答案即为负。

这样我们就将负数装换为正数。上文所说的 $x=b+c,y=a+d$（符号被消掉了）。

时间复杂度 $O(T)$（$T$ 是数据组数）。
### 完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int T;
int a, b, c, d;
bool a1, b1, c1, d1;

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d %d", &a, &b, &c, &d);
        
        a1 = b1 = c1 = d1 = false;
        
        if ((a + b) % 2 == 1) {
            if ((a + d) > 0) a1 = 1; // 无穷趋近于负无穷
            if ((b + c) > 0) b1 = 1; // 无穷趋近于0
        } else {
            if ((a + d) > 0) d1 = 1; // 无穷趋近于正无穷
            if ((b + c) > 0) c1 = 1; // 无穷趋近于0
        }
        
        // 输出
        if (a1) printf("Ya ");
        else printf("Tidak ");
        if (b1) printf("Ya ");
        else printf("Tidak ");
        if (c1) printf("Ya ");
        else printf("Tidak ");
        if (d1) printf("Ya ");
        else printf("Tidak ");
        printf("\n");
    }
    return 0;
}
```

[完整代码](https://www.luogu.com.cn/record/119698717) 以及 完结撒花~

---

## 作者：Qing_喵乖乖喵 (赞：0)

[原题链接](https://codeforces.ml/problemset/problem/1425/H)

题意简介： 

已知分别处在 $(-\infty,-1]$ 、$(-1,0)$ 、$(0,1)$ 、$[1,\infty)$ 的实数的数量(下记为集合 $A,B,C,D$ )，试问：把这些数乘起来后，答案的可能出现在那个范围中？  

题解：  

首先，我们不难发现，如果负数的个数为奇数，那么答案必然在 $A$ 和 $B$ 中，否则，将出现在 $C$ 和 $D$ 中。

确定了这一点后，我们将符号全部视为正，试着探索答案能否出现在 $C$ 或 $D$ 中。

显然，由于我们可以给这些数随便赋一个范围内的值，那么我们只需要考虑极端情况即可。

只要原本有一个数绝对值在 $D$ 里，只要把这个数取到无限大，其它在 $C$ 中的取无限接近于 $1$ ，最终答案就会在 $D$ 里。

同理，只要原本有一个数绝对值在 $C$ 里，只要把这个数取到无限趋近于 $0$ ，其它在 $D$ 中的取 $1$ ，最终答案就会在 $C$ 里。  

签到题之一。

```cpp
#include <cstdio>
int t,A,B,C,D;
inline void out(bool x){
    printf(x?"Ya ":"Tidak ");
}
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d%d%d%d",&A,&B,&C,&D);
        if((A+B)&1){
            if(D||A) A=1,D=0;
            if(B||C) B=1,C=0;
        }else{
            if(D||A) A=0,D=1;
            if(B||C) B=0,C=1;
        }
        out(A); out(B); out(C); out(D);
        putchar('\n');
    }
    return 0;
}
```

---

