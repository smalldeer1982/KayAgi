# [ARC015A] Celsius と Fahrenheit

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc015/tasks/arc015_1

摂氏での温度 $ n $ 度を華氏にで表すと $ (\ 9\ ÷\ 5\ ×\ n\ )\ +\ 32 $ 度となります。  
 摂氏での温度が与えられるので華氏での温度に変換するプログラムを書いてください。  
 入力は以下の形式で標準入力から与えられる。

> $ n $

- $ 1 $ 行目は、華氏に変換すべき、摂氏の温度 $ n\ (-273≦n≦1,000) $ が整数で与えられる。
 
 摂氏での温度 $ n $ を華氏に変換し、その値を $ 1 $ 行で出力せよ。  
 なお、出力の最後には改行をいれること。  
 出力は絶対誤差あるいは相対誤差の少なくとも片方が $ 10^{-6} $ 以下であれば許容される。 ```
<pre class="prettyprint linenums">
10
```

 ```
<pre class="prettyprint linenums">
50
```

- $ (9÷5×10)+32 $ $ = $ $ 50 $
 
```
<pre class="prettyprint linenums">
33
```

 ```
<pre class="prettyprint linenums">
91.4
```

- $ (9÷5×33)+32 $ $ = $ $ 91.4 $
- 摂氏での温度が整数であっても、華氏での温度は整数になるとは限りません。
 
```
<pre class="prettyprint linenums">
-100
```

 ```
<pre class="prettyprint linenums">
-148
```

- $ 9÷5×(-100) $ $ +32 $ $ = $ $ -148 $

# 题解

## 作者：wushuang0828 (赞：0)

**思路：先根据公式(9÷5×n)+32，求出华摄氏度，因为误差不能超过10^{-6}10，所以我打代码时保留了六位小数**

Pascal的AC代码如下：
```pascal
var
 n:longint;
begin
 readln(n);//输入一个摄氏度
 writeln((9/5*n)+32:0:6);//套用公式并用双场宽，保留六位小数
end.
```

---

## 作者：Bronya18C (赞：0)

## 标签：

`模拟`

---

# 做法：
暴力模拟，但要注意的是最好保留六位小数

注意：误差不能超过10^{-6}10 

还有，题目上的乘号和除号不可以复制去用。
坑了我一次。

---
# 答案：
```
#include<bits/stdc++.h>

using namespace std;
double n;
int main()
{
    cin>>n;
    printf("%.6lf",double((double(9.000000/5.000000)*n))+32.000000);
    return 0;
}
```


---

## 作者：CZQ_King (赞：0)

这道题很水，按照翻译模拟即可。
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
double n;//int也行
int main(){
    cin>>n;
    cout<<1.8*n+32<<endl;//把9/5换成了1.8
    return 0;//结束
}
```
##### 我~~才不~~会告诉你$-40^\circ C=-40^\circ F$

---

