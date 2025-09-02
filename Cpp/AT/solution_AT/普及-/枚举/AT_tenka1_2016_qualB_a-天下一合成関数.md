# 天下一合成関数

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tenka1-2016-qualb/tasks/tenka1_2016_qualB_a

関数 $ f $ を以下のように定義します。

$ f(n)\ =\ {\rm\ floor}((n^2\ +\ 4.0)\ / $ $ 8.0) $

※ $ {\rm\ floor}(x) $ は与えられた実数 $ x $ 以下の最大の整数を返す関数です。

アイバくんは関数 $ f $ を整数に何度か適用して遊んでいます。例えば、

$ f(10)\ =\ 13 $

$ f(f(10))\ =\ 21 $

$ f(f(f(10)))\ =\ 55 $

となります。

アイバくんは急に $ f(f(f(20))) $ が必要になりました。

アイバくんの代わりに $ f(f(f(20))) $ を求めてください。

# 题解

## 作者：I_will (赞：6)

这道题只有一个数据我很无语，有人直接套我更无语，还搞了函数判断我最无语。

我要让无语再上几层楼！

1楼的无语：
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<fstream>
#include<string>
#include<cstring>
#include<cmath>
#include<cstdlib>
using namespace std;
long long f(long double x){
    return floor(x*x/8+0.5);
}
int main(){
    cout<<f(f(f(20)))<<endl;
    return 0;
    
}
```
2楼的无语：
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<fstream>
#include<string>
#include<cstring>
#include<cmath>
#include<cstdlib>
using namespace std;

int main(){
    cout<<floor((floor((floor((20*20+4)/8)*floor((20*20+4)/8)+4)/8)*floor((floor((20*20+4)/8)*floor((20*20+4)/8)+4)/8)+4)/8)<<endl;
    return 0;
    
}
```

2楼（隔壁老王）的无语：
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<fstream>
#include<string>
#include<cstring>
#include<cmath>
#include<cstdlib>
using namespace std;
int x=20;
int main(){
    cout<<floor(floor(floor(x*x/8+0.5)*floor(x*x/8+0.5)/8+0.5)*floor(floor(x*x/8+0.5)*floor(x*x/8+0.5)/8+0.5)/8+0.5)<<endl;
    return 0;
    
}
```

3楼的无语：我从未见过如此厚颜如此之人！
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<fstream>
#include<string>
#include<cstring>
#include<cmath>
#include<cstdlib>
using namespace std;
int x=20;
int main(){
    cout<<12246<<endl;
    return 0;
    
}
```




嘿，点个赞再走！

---

## 作者：zr太弱了 (赞：2)

本题按照题意来即可，先写一个函数f：

```cpp
int f(int a)
{
    return (a*a+4)/8;
}
```

>"/"c++的除法小数自动忽略

代入主函数：

```cpp
 cout<<f(f(f(20)))<<endl;
```

$AC code$

```cpp
#include<bits/stdc++.h>
using namespace std;
int f(int a)
{
    return (a*a+4)/8;
}
int main(){
    cout<<f(f(f(20)))<<endl;
    return 0;
}
```

因为本题没有输入，只有一种结果，我们可以直接输出答案：

$c$++:

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    cout<<"12246"<<endl;
    return 0;
}
```
$PHP$：

```php
12246
```
$python2$:

```python
print "12246"
```

$python3$:

```python
print("12246")
```

---

## 作者：CZQ_King (赞：2)

## ~~还是老老实实的做比较好~~
~~居然一次过!~~


------------

这题按照题意模拟即可。
我用了一个子程序。
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
int f(int a){//f(x)
    return (a*a+4)/8;//按照题意模拟，C++的小数会自动忽略，相当于floor的功能
}
int main(){
    cout<<f(f(f(20)))<<endl;//输出答案
    return 0;//结束
}
```

---

## 作者：死神审判 (赞：2)

### 思路&解析
定义函数$f(n)=floor((n^2+4.0)/8.0)$，输出$f(f(f(20)))$ 即可。

其实呢，按照公式模拟一遍可知这个答案为$12246$。如果代码想要简洁一些，直接输出 $12246$ 就好啦。


------------
### 代码（```Go```）：
```
package main
import "fmt"
func main() {
    fmt.Println(12246)
}
```


---

## 作者：Jinyeke (赞：1)

#### 题目（pascal版）：


### 定义函数:f(n)=floor((n*n+4) div 8)
### 输出f(f(f(20)))并换行。 

那么久很好做啦：

1.写一个floor函数

2.输出并换行（writeln）

放代码（pascal）:
```pascal
function floor(n:longint):longint;//函数
begin
 exit(((n*n+4)div 8));//返回floor函数的值
end;
begin
 writeln(floor(floor(floor(20))));//输出
end.
```
[AC啦！](https://www.luogu.org/recordnew/show/17067871)

---

## 作者：A_Plus_Gu (赞：0)

这是一道比较简单的题，题目说啥，你做啥就可以了。

下面贴上代码：
```
#include<iostream>
#include<cmath>
using namespace std;
long long f(long double x){//定义函数
	return floor((x*x+4.0)/8.0);//注意：用floor的话必须加cmath头文件
}
int main(){
	cout<<f(f(f(20)))<<endl;//调用函数
    return 0;//这句话不要忘了写！
    //不写return 0,成绩return 0!
}
```


---

## 作者：qiukaichen (赞：0)

感觉最近做的题都好水啊，代码讲解见下
```
#include<bits/stdc++.h>//万能库开头 
using namespace std;
int floor(int a)//定义函数 
{
	return (a*a+4.0)/8;//依题意返回此值 
}
int main()
{
	cout<<floor(floor(floor(20)))<<endl;//朴实输出，不要忘了换行 
	return 0;//收工 
}
```


---

## 作者：_lyc233 (赞：0)

定义函数f(n)=floor((n^2+4.0)/8.0)，输出f(f(f(20)))并换行。 

- f(n)=floor((n^2+4.0)/8.0)
- f(n)=(n^2+4.0)/8.0
- f(n)=(n*n+4)/8

那么，这题到目前为止有三种解法：

1：函数返回值
```
function f(n:longint):longint;
begin
  exit((n*n+4) div 8);  //返回(n*n+4) div 8的值
end;
begin
  writeln(f(f(f(20))));  //同题意
end.
```
2：分步计算
```
var n:longint;  //定义部分
begin
  n:=20;  //初值
  n:=(n*n+4) div 8;
  n:=(n*n+4) div 8;
  n:=(n*n+4) div 8;//f(f(f(20)))即有三次
  writeln(n);  //输出
end.
```
3：爆解
```
var n:longint;
begin
  writeln((sqr((sqr((sqr(20)+4) div 8)+4) div 8)+4) div 8);
end.
//emm
```
其实还有一种写法，在此不做论述，不过大家可以在[这里](https://maxpzx.blog.luogu.org/solution-at2025)找到

大家都听懂了吗？

---

