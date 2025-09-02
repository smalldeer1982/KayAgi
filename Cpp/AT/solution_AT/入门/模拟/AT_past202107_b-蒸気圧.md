# 蒸気圧

## 题目描述

[problemUrl]: https://atcoder.jp/contests/past202107-open/tasks/past202107_b

$ A $ 個のボールと $ B $ 個の風船があります。 高橋君はボールの数が風船の数の $ C $ 倍以下になるまで $ 1 $ つずつボールを取り除いていきます。 最終的に残ったボールの数を風船の数で割った値を求めてください。

## 说明/提示

### 注意

この問題に対する言及は、2021/7/17 18:00 JST まで禁止されています。言及がなされた場合、賠償が請求される可能性があります。 試験後に総合得点や認定級を公表するのは構いませんが、どの問題が解けたかなどの情報は発信しないようにお願いします。

### 制約

- $ 1\ \leq\ A,B,C\ \leq\ 10^4 $
- $ A,B,C $ は整数

### Sample Explanation 1

最初ボールは $ 8 $ 個あります。 高橋君はボールが $ 3\times\ 2=6 $ 個以下になるまでボールを取り除き、最終的にボールは $ 6 $ 個残ります。 よって、答えは $ \frac{6}{3}=2 $ となります。

### Sample Explanation 2

最初の時点で $ 8\leq\ 5\times\ 2 $ であるので高橋君はボールを $ 1 $ つも取り除きません。 よって、答えは $ \frac{8}{5}=1.6 $ となります。

## 样例 #1

### 输入

```
8 3 2```

### 输出

```
2.000000000000000```

## 样例 #2

### 输入

```
8 5 2```

### 输出

```
1.600000000000000```

# 题解

## 作者：lichenzhen (赞：3)

## 题目大意
有 $A$ 个球和 $B$ 个气球，每次把 $A-1$，直到 $A \le B \times C$ 为止，问此时 $A$ 是 $B$ 的几倍。

## 题目解法
一到很简单的题目，但是我看了一下题解区的大佬们没有用我这种方法的。都是用的可能需要推导的方法。

我的方法是十分直接的方法，就是按照题意模拟即可。我们直接写一个`while`循环，只要不 $A > B \times C$ 就把 $A-1$。最后输出 $A \div B$ 就可以了。但是要注意保留至少 $6$ 位小数，这里我建议多保留几位，以防出错。

### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
double a,b,c; 
int main()
{
    cin>>a>>b>>c; 
	while(a>b*c) a--;
	printf("%.10f\n",a/b);
    return 0;
}
```

---

## 作者：Ggsddu_zzy (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_past202107_b)

### 题目大意

有 $A$ 和 $B$ 两个数，每次将 $A$ 减 $1$（本来就小于等于的不必减 $1$），问当 $A$ 小于等于 $B$ 的 $C$ 倍时，$A$ 是 $B$ 的几倍（保留 $6$ 位小数）。


### 解题思路

- 如果 $A$ 大于 $B \times C$ 不需要每次将 $A$ 减 $1$，因为 $A$ 每次减 $1$，总有等于 $B \times C$ 的时候，所以可以直接将 $A$ 变成 $B \times C$。

- 否则，$A$ 就不用进行任何操作。

最后把 $a\div b$ 输出。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c;
int main(){
	cin>>a>>b>>c;
	if(a>b*c) a=b*c;
	cout<<fixed<<setprecision(6)<<1.0*a/b;	
	return 0;
}
```


---

## 作者：李卓衡001 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_past202107_b)

题目大意
-
有 $ A $ 个球和 $ B $ 个气球。每次将球的个数减 $ 1 $，直到球个数小于等于气球个数的 $ C $ 倍（本来就小于等于的不必减 $ 1 $）。问此时球的个数是气球的个数的几倍（误差不超过 $ 10^{-6} $ ）。

思路
-
因为最后球的个数 $ A $ 一定是气球的个数 $ B $ 的 $ C $ 倍，所以球的个数 $ A $ 最多有 $ B · C $ 个。

这样，我们就可以判断一下：

- 如果最开始球的个数 $ A \leq $ 气球个数的 $ B $ 的 $ C $ 倍，即 $ B · C $，则输出 $ A ÷ B $。

- 如果最开始球的个数 $ A > $ 气球个数的 $ B $ 的 $ C $ 倍，即 $ B · C $，则输出 $ C $。

满分代码
-
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int A,B,C;
	cin>>A>>B>>C;
	if(A>B*C) printf("%.10lf\n",1.0*C);
	else printf("%.10lf\n",1.0*A/B);
	return 0;
}
```

---

## 作者：Moon_Traveller (赞：1)

[传送门](/problem/AT_past202107_b)

好像题解里没有直接模拟的做法，那我就来写一个吧。

题面描述得很清楚，我这里就不再赘述题意了。

每次判断 $a$ 是否大于 $b \times c$，如果是，就减 $1$，否则就直接输出。

```cpp
#include <iostream>
using namespace std;

double a, b, c;

int main()
{
    cin >> a >> b >> c;
    while(a > b * c)
    {
        a--;
    }
    printf("%.6f\n", a / b);
    return 0;
}
```

---

## 作者：FS_qwq (赞：1)

## 题目

有 $A$ 个球和 $B$ 个气球。每次将球的个数减 $1$，直到球个数小于等于气球个数的 $C$ 倍（本来就小于等于的不必减 $1$）。问此时球的个数是气球的个数的几倍（保留 $6$ 位小数）。

## 题目大意

定义 $a$，$b$，$c$ ，就是每次 $a$ 个球变成 $a-1$ 个球,直到球的个数小于等于气球总数的 $c$ 倍。如果刚开始球的个数就小于等于气球总数的 $c$ 倍，那么就没必要每次 $a$ 个球变成 $a-1$ 个球。

## 题目解答

当刚开始球的个数就小于等于气球总数的 $c$ 倍时，就输出 $a$ 是 $b$ 的几倍。

当刚开始球的个数就大于气球总数的 $c$ 倍时，因为肯定会有一个 $a,b,c$，使得球的个数就小于等于气球总数的 $c$ 倍时，所以输出  $c$ 就可以了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
double a,b,c; //定义 
int main(){
    cin>>a>>b>>c; //输入 
	if(a<=b*c)printf("%.8lf\n",a/b);//注意要多保留到六位及以上的小数点，然后多保留几位，防止出错 
	else printf("%.8lf\n",c);//一样 
    return 0;
}
```




---

## 作者：CSPJ10pts (赞：0)

## 题目描述

有 $A$ 个球和 $B$ 个气球。每次将球的个数减 $1$，直到球个数小于等于气球个数的 $C$ 倍（本来就小于等于的不必减 $1$）。问此时球的个数是气球的个数的几倍（保留 $6$ 位小数）。

## 分析

我们分两种情况讨论：

1. 当 $a$ 大于 $b$ 的 $c$ 倍，那么 $a$ 每次减 $\texttt1$，一直减到 $b$ 的 $c$ 倍，所以对于这种情况我们可以直接输出 $c$。

2. 当 $a$ 已经小于等于 $b$ 的 $c$ 倍了，我们就不用减了，输出 $a \div b$ 即可。注意，保留 $6$ 位小数。

## 代码

```
#include <iostream>
#include <cmath>
using namespace std;
int a, b, c;
int main() {
	cin >> a >> b >> c;
	if (a > b * c) printf("%d.000000\n", c); // %d.000000是因为c是个整数所以可以直接输出它自己然后.000000（其实是偷个小懒）
	else printf("%.6lf\n", 1.0 * a / b); // 注意！一定要写1.0！
	return 0;
}
```
[通过记录~](https://www.luogu.com.cn/record/102255273)

---

## 作者：HCC001 (赞：0)

~~大淼题~~

## 题意：
给定 $A,B,C$，每次将 $A$ 减 $1$，直到 $A\le B\times C$，求此时 $A/B$ 的值（保留 $6$ 位小数）。

## 解法：
如果一开始就满足 $A\ge B\times C$，则必定会有一个时刻 $A=B\times C$，直接输出 $C$。

否则开始时就满足条件，输出 $A\div B$ 即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
	int a,b,c;
	cin>>a>>b>>c;
	if(a>=b*c)cout<<c<<".000000";//手动保留6位小数
	else cout<<fixed<<setprecision(6)<<1.0*a/b;
    return 0;
}
```

---

## 作者：Loser_Syx (赞：0)

## 题目描述

有 $A$ 个球和 $B$ 个气球。每次将球的个数减 $1$，直到球个数小于等于气球个数的 $C$ 倍（本来就小于等于的不必减 $1$）。问此时球的个数是气球的个数的几倍（误差不超过 $10^{-6}$）。

## 思路

根据题意可知，最后球的个数至多是 $B\cdot C$ 个，如果本来 $A$ 比 $B\cdot C$ 大，那么此时要输出的个数是 $B\cdot C\div C$，如果 $A$ 比 $B\cdot C$ 小，则输出 $A\div C$，简化上述的内容，可得知我们要输出 $\min(A,B\cdot C)\div C$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
main(){
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    printf("%.10lf\n", 1.0 * min(a, b * c) / b);//取min然后输出除以b的值，注意误差不要超过10的-6次方（保留6位小数），而且用的int类型保存到，要乘1.0
    return 0;
}
```

---

## 作者：Enoch006 (赞：0)

### 题目大意：

有 $A$ 个球和 $B$ 个气球。每次将球的个数减 $1$，直到球个数小于等于气球个数的 $C$ 倍（本来就小于等于的不必减 $1$）。问此时球的个数是气球的个数的几倍（保留 $6$ 位小数）？

------------

### 题目分析：

要求球的个数是气球的个数的几倍，我们就需要看球个数小于等于气球个数的 $C$ 倍。分两种情况：
- 若是小于等于的话，我们就可以直接输出球的个数除以气球的个数。
- 若不是，我们可以假设球的个数一直减少 $1$，直到减少到气球个数的 $C$ 倍。此时，球的个数除以气球的个数恰好就等于 $C$。

即：
$$\begin{cases}
A\div B(A\leq B\times C) \\
C(A>B\times C) \\
\end{cases}$$
。

------------
### 题目代码：

此时代码就很好写了，注意保留 $6$ 位小数！

```cpp
#include <bits/stdc++.h>
using namespace std;
double a,b,c; 
int main() {
    cin>>a>>b>>c; 
	if(a<=b*c)printf("%.6lf",a/b);
	else printf("%.6lf",c);
    return 0;
}    
```


---

## 作者：____someone____ (赞：0)

### Description:

[题目传送门](https://www.luogu.com.cn/problem/AT_past202107_b)

[更好的食用效果](https://www.luogu.com.cn/blog/666someonebk999/solution-at-past202107-b)

题目大意：

给你三个正整数 $a$,$b$,$c$，表示有 $a$ 个球和 $b$ 个球，每次将 $a$ 球的数量减少一个，直到 $a$ 球的数量小于或等于 $b$ 球的 $c$ 倍，如果 $a$ 球的数量开始就小于 $b$ 球数量的 $c$ 倍，则 $a$ 球的数量不减少。

输出最后 $a$ 球的数量是 $b$ 球的多少倍。

输出结果与样例结果相差的绝对值小于 $10^{-6}$ 则算结果正确。

### Solution:

- 当 $a$ 球初始数量小于 $b$ 球数量的 $c$ 倍时，直接输出 $a$ 是 $b$ 的多少倍即可；

- 当 $a$ 球初始数量大于或或等于 $b$ 球数量的 $c$ 倍时，由于 $a$ 球的数量最后一定会变为 $b$ 球数量的 $c$ 倍，所以直接输出 $c$ 即可。

要注意的是**最后输出的结果必须保留 $6$ 位以上的小数位！**

### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
	double a,b,c; //定义成 double 型，便于求倍数
	cin>>a>>b>>c;
	if(a<b*c)printf("%.9lf",(a/b)); //a小于b的情况
	else printf("%.9lf",(c)); //9位小数，保留多一点肯定不会错
	return 0;
}
```

无注释版（**杜绝抄袭**）：
```
#include<bits/stdc++.h>
using namespace std;

int main()
{
	double a,b,c;
	cin>>a>>b>>c;
	if(a<b*c)printf("%.5lf",(a/b));
	else printf("%.5lf",(c));
	return 0;
}
```


---

## 作者：Siteyava_145 (赞：0)

### 题意简述：

有 $A$ 个球和 $B$ 个气球。每次将球的个数减 $1$，直到球个数小于等于气球个数的 $C$ 倍（本来就小于等于的不必减 $1$）。问此时球的个数是气球的个数的几倍（保留 $6$ 位小数）？

因为它求的就是最终结果，所以不需要将 $A$ 一个个的减一，而是直接变到最终状态求解。但是容易发现，最终状态时，$A$ 其实就是 $B$ 的 $C$ 倍。这其实很好理解，$A$ 的最终状态就是 $B\times C$，求 $A/B$，也就是 $B\times C/B$，结果就是 $C$ 了。

有一种情况，就是 $A$ 本来就小于等于 $B\times C$。这时直接输出 $A/B$ 的值就可以了。

一定记得保留 $6$ 位小数。

```
#include<bits/stdc++.h>
using namespace std;
int main(){
    int a,b,c;
    cin>>a>>b>>c;
    if(a>=b*c){
        printf("%.11lf\n",1.0*c);//多保留几位
    }else{
        printf("%.11lf\n",1.0*a/b);
    }
}
```


---

