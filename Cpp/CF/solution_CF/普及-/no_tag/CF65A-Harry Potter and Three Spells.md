# Harry Potter and Three Spells

## 题目描述

很久以前（可能甚至在第一本书中），尼古拉斯·勒梅，一位伟大的炼金术士和魔法石的创造者，教了哈利·波特三个有用的咒语。第一种方法可以将 $a$ 克沙子转换成 $b$ 克铅，第二种方法可以将 $c$ 克铅转换成 $d$ 克金，第三种方法可以将 $e$ 克金转换成 $f$ 克沙子。

当哈利告诉他的朋友这些咒语时，罗恩很惊讶。毕竟，如果他们能把沙子变成铅，铅变成金，然后再把部分金变成沙子，那么就有可能从少量的沙子开始得到大量的金！即是无限量的黄金！

相比之下，格兰杰对这个想法持怀疑态度。她认为，根据物质守恒定律，获得无限量的物质，即使使用魔法，也是不可能的。相反，物质在转化过程中甚至会减少，转化为能量。

虽然赫敏的理论似乎令人信服，罗恩却不相信她。罗恩觉得，赫敏制定了只属于她的物质守恒定律，以阻止哈利和罗恩在这些胡言乱语上浪费时间，并且让他们去做作业。

这就是为什么罗恩已经收集了一定数量的沙子进行实验。

朋友之间的争吵似乎是不可避免的。帮助哈利确定他的朋友中哪一个是对的，避免争吵。要做到这一点，你必须弄清楚是否有可能从有限数量的沙子中获得比任何预先分配黄金数量更多的黄金数量。

---

## 样例 #1

### 输入

```
100 200 250 150 200 250
```

### 输出

```
Ron
```

## 样例 #2

### 输入

```
100 50 50 200 200 100
```

### 输出

```
Hermione
```

## 样例 #3

### 输入

```
100 10 200 20 300 30
```

### 输出

```
Hermione
```

## 样例 #4

### 输入

```
0 0 0 0 0 0
```

### 输出

```
Hermione
```

## 样例 #5

### 输入

```
1 1 0 1 1 1
```

### 输出

```
Ron
```

## 样例 #6

### 输入

```
1 0 1 2 1 2
```

### 输出

```
Hermione
```

## 样例 #7

### 输入

```
100 1 100 1 0 1
```

### 输出

```
Ron
```

# 题解

## 作者：Stephen_Curry (赞：25)

这道题目怕不是道小奥题……其实只需要一些简单的移项即可解决。

~~第一眼看成了最短路，于是以下部分均或多或少有着最短路问题的影子……~~

![](https://cdn.luogu.com.cn/upload/image_hosting/s4uwkbtn.png)

这道题目其实可以简化成上面的图。其中我们通过读题可以知道 $u=a:b,\ v=c:d,\ w=e:f$。那么，我们只需要依次转化即可。

首先我们通过沙子与铅，铅与金的关系可以间接地求出沙子与金的关系。将 $c:d$ 看成份数比，从而沙子变成铅后有了 $u\cdot c$ 份，即 $\dfrac{a}{b}\cdot c$ 份。而后项的 $d$ 无法进行转化，从而沙子与金子之间的关系为 $(\dfrac{a}{b}\cdot c):d$。

继而，我们再通过这个式子求出原来的沙子数量与沙子转化为铅后再转化为金最后转化回沙子的数量之间的比 _（尽管这句话很拗口，但笔者语文功底太差，实在想不出更好的表达方法）_，与上面的方法相同，我们可以得到它们的比为：

$$\dfrac{\dfrac{a}{b}\cdot c}{d}\cdot e:f$$

而若要金子无法无限得到，则此环须为负环，即该比比值需小于 $0$。

故而便有了以下方程：

$$\dfrac{\dfrac{\dfrac{a}{b}\cdot c}{d}\cdot e}{f}< 0$$

于是，我们开始愉快地移项：

$$\dfrac{\dfrac{a}{b}\cdot c}{d}\cdot e< f$$

将 $f$ 移过来后，我们发现左边 $d$ 处于分母的位置，不由分说再移过来：

$$\dfrac{a}{b}\cdot c\cdot e< d \cdot f$$

最后把 $b$ 移过来：

$$a\cdot c\cdot e<b\cdot d\cdot f$$

从而，我们发现最后得到了这样的一个式子！

（出题人露出了邪恶的笑容）你以为直接靠这样一个式子就能轻松通过？抱歉这是不可能的……

**Why?**

还是这毒瘤的数据范围：$0\le a,b,c,d,e,f\le 1000$

有什么不对么？

注意它的下界是 $0$，也就是说，我们的式子建立在数字大于 $0$ 的基础上，而数据中是可能出现零的！

于是就要加上许许多多各式各样稀奇古怪乱七八糟五花八门古里八怪的 sb 特判……

![](https://pic2.zhimg.com/80/v2-5b2078b1eadad84ff3d223821184b051_720w.jpg)  
（图片来源：知乎，图文无关）

首先如果能无限换铅且铅能换金，即 $a=0,b\times d\not=0$，这种情况应输出 `Ron`。

其次，若能无限量兑换金，即 $c=0$ 且 $d>0$，这种情况也应输出 `Ron`。

最后，要保证能变成黄金，即 $d\not=0$。而因为无论哪种情况都要满足该条件，故第二条特判中的 $d>0$ 可以省略。

最后的最后，上代码：

Pascal
```pascal
var a, b, c, d, e, f:longint;
begin
    read(a, b, c, d, e, f);
    if ((a * c * e < b * d * f) or ((a = 0) and (b * d > 0)) or (c = 0) and (d > 0)) then
        writeln('Ron')
    else writeln('Hermione');
end.
```

C
```c
#include <stdio.h>
int a, b, c, d, e, f;
int main() {
    scanf("%d%d%d%d%d%d", &a, &b, &c, &d, &e, &f);
    if ((a * c * e < b * d * f) || ((a == 0) && (b * d > 0)) || (c == 0) && (d > 0)) puts("Ron");
    else puts("Hermione");
}
```

C++
```cpp
#include <bits/stdc++.h>
using namespace std;
#define var int
var a, b, c, d, e, f; //Pascal 后遗症
int main() {
    cin >> a >> b >> c >> d >> e >> f;
    if ((a * c * e < b * d * f) or ((a == 0) and (b * d > 0)) or (c == 0) and (d > 0)) cout << "Ron";
    else cout << "Hermione";
}
```

Java
```java
import java.io.*;
import java.util.*;
public class Main {
    public static void main(String args[]) throws Exception {
        Scanner cin=new Scanner(System.in);
        int a = cin.nextInt(), b = cin.nextInt(), c = cin.nextInt(), d = cin.nextInt(), e = cin.nextInt(), f = cin.nextInt();
        if ((a * c * e < b * d * f) || ((a == 0) && (b * d > 0)) || (c == 0) && (d > 0)) System.out.println("Ron");
        else System.out.println("Hermione");
    }
}
```

Go
```
package main
import "fmt"
func main() {
    var a, b, c, d, e, f int
    fmt.Scanf("%d%d%d%d%d%d", &a, &b, &c, &d, &e, &f);
    if ((a * c * e < b * d * f) || ((a == 0) && (b * d > 0)) || (c == 0) && (d > 0)) {
        fmt.Printf("Ron\n");
    } else {
        fmt.Printf("Hermione\n");
    }
}
```

Python 2
```python
a, b, c, d, e, f = map(int, raw_input().split())
if a * c * e < b * d * f or a == 0 and b * d > 0 or c == 0 and d > 0 :
    print("Ron")
else :
    print("Hermione")
```


Python 3
```python
#习惯性加分好了，其实加不加效果相同
a, b, c, d, e, f = map(int, input().split());
if a * c * e < b * d * f or a == 0 and b * d > 0 or c == 0 and d > 0:
    print("Ron");
else:
    print("Hermione");
```

文言
```
施「require('fs').readFileSync」於「「/dev/stdin」」。名之曰「數據」。
施「(buf => buf.toString().trim())」於「數據」。昔之「數據」者。今其是矣。
施「(s => s.split(' '))」於「數據」。昔之「數據」者。今其是矣。

夫「數據」之一。取一以施「parseInt」。名之曰「甲」。
夫「數據」之二。取一以施「parseInt」。名之曰「乙」。
夫「數據」之三。取一以施「parseInt」。名之曰「丙」。
夫「數據」之四。取一以施「parseInt」。名之曰「丁」。
夫「數據」之五。取一以施「parseInt」。名之曰「戊」。
夫「數據」之六。取一以施「parseInt」。名之曰「己」。


乘「甲」以「丙」。乘其以「戊」。名之曰「庚」。
乘「乙」以「丁」。乘其以「己」。名之曰「辛」。

若丁等於零者。吾有一言。曰「「Hermione」」。書之。
若非。
  若「庚」小於「辛」者。吾有一言。曰「「Ron」」。書之。
  若非。
    若丙等於零者。吾有一言。曰「「Ron」」。書之。
    若非。
      若甲等於零者。
        若乙大於零者。 吾有一言。曰「「Ron」」。書之。
        云云。
      若非。 吾有一言。曰「「Hermione」」。書之。
      云云。
    云云。
  云云。
云云。
```

------------


$$\large\mathfrak{The\ End.}$$

---

## 作者：james1BadCreeper (赞：6)

先吐槽一句，这是一道紫题？

这是一道小学奥数题，我们一起来分析一下。

简单地想，只要1个单位的沙子换成的黄金能换成超过1个单位的沙子，那么就可以堆出一座无限大的金山了，那就模拟计算一下吧！

就用a当做一个单位，这样比较好算。

要想求a克沙子能换成多少克黄金，首先a克沙子能换b克铅，接下来使用小学奥数的倍比策略来计算。

>题目中同类量之间有倍数关系。根据这种倍数关系来解题，叫做倍比问题。

### 倍比数量关系：

总量÷一个数量=倍数

另一个数量×倍数=另一总量

回到原题，根据倍比计算：

![](https://cdn.luogu.com.cn/upload/pic/66838.png)

我们可以求出b克铅可以换成多少克金，答案就是$b/c*d$。

同理，计算出可以转成多少克沙。

组合刚才的式子，得出a克沙跑一圈后可以变成$b/c*d/e*f$克沙。

综上，我们可以得出结论，若满足$b/c*d/e*f>a$，那么Ron的结论是正确的，否则Hermione的结论是正确的。

但上式子不好计算，因为万一$b/c$是一个无限不循环小数，这题就炸了，所以利用不等式性质二，把式子变一下型。

>不等式性质二：不等式两边同时乘或除以一个大于0的数，不等式依然成立。

式子变形后的结果：$b*d*f>a*c*e$。

所以我们可以写出以下代码：

```cpp
#include<cstdio>
int main()
{
	int a,b,c,d,e,f;
	scanf("%d%d%d%d%d%d",&a,&b,&c,&d,&e,&f);//输入数据
	if(b*d*f>a*c*e)) printf("Ron");//Ron对
	else printf("Hermione");//Hermione对
	return 0;
}
```

但这个代码交上去是要WA掉的。

**为什么？**

仔细注意不等式性质二，是**不为0的数**，但题目可没保证不为0。

所以要加各种特判。

1.首先$d\not=0$，保证能够变成黄金；

2.其次若$c=0$，那么可能可以无限换黄金，若$c=0,d\not=0$也是Ron对；

3.若能无限换铅，且铅能换金，也是Ron对，需满足$a=0,b\not=0,d\not=0$。

综上，能写出以下代码：

```cpp
#include<cstdio>
int main()
{
	int a,b,c,d,e,f;
	scanf("%d%d%d%d%d%d",&a,&b,&c,&d,&e,&f);
	if(((b*d*f>a*c*e)||(c==0&&d!=0)||(a==0&&b!=0&&d!=0))&&d!=0) printf("Ron");
	else printf("Hermione");
	return 0;
}
```

最后说明，这就是一道数学题，请确保你已经明白这题是怎么想的。

---

## 作者：封禁用户 (赞：2)

~~CF的难度真的锅很严重~~

[安利下窝的博客](https://www.luogu.com.cn/blog/356740/)

这道题属于初一年级第九章不等式与不等式组的范围。依题意，如果 $1$ 单位的沙子经过一番~~毒瘤的~~转换能够变成 $1+$ 单位的沙子，那么金山无限。

下面进行推导：

沙子兑换铅的倍率是 $\dfrac{a}{b}$, 也就是说换完后质量会变为 $a\div\dfrac{a}{b}=b$ 单位。

同理，铅兑换金子的倍率是 $\dfrac{c}{d}$，金子再换沙子的倍率是 $\dfrac{e}{f}$。

那么，沙子换回沙子的倍率就是
$$\dfrac a b\cdot\dfrac c d\cdot\dfrac e f=\dfrac{ace}{bdf} \qquad(b,d,f\ne 0)$$

由于我们希望越换越多，所以我们希望这个比率比 $1$ 小，这是因为一个数除以一个比他小的数会变得比他自己更大

$$\therefore ace<bdf\qquad(b,d,f\ne0)$$

然而，我们把这个判断提交上去的时候……没错，你看到了红彤彤的 WA。

原因？
>The first line contains $6$ integers $a$ , $b$ , $c$ , $d$ , $e$ , $f$ ($0 \le a,b,c,d,e,f \le 1000$)

没看出来？
>The first line contains $6$ integers $a$ , $b$ , $c$ , $d$ , $e$ , $f$ 
$$\large{0 \le a,b,c,d,e,f \le 1000}$$

看出来了吗？之前的运算都是基于 $b,d,f\ne 0$ 的。

当然这也不赖大家，应该赖那个~~非常不靠谱的毒瘤~~生草员，这里吐槽一下，他翻译成了 $a,b,c,d,e,f \le 1000$……

~~这告诫我们 要学好嘤语，而且不要见到嘤文题就疯狂滚轮到翻译。~~

那么我们就要加一些特判：
1. 如果铅**不能**换出金子，即 $d = 0$ 时，一定不能换出金子，所以**一切特判的先决条件都是** $d \ne 0$；

2. 如果沙子能换出无限量的铅，即 $0$ 单位的沙子能换出非零量的铅，金子会越换越多。总结为式子就是：

	$$a=0 , b \ne 0$$
        
	用编程逻辑表达：
	```cpp
	!a && b 		//若a不为0，则 !a 为0
	```

3. 如果铅能换出无限量的金子，即 $c=0$ 时，能换出无限量的金子。用编程逻辑表达：
	```cpp
	!c
	```

加上这些特判就能得满分了。

$AC\ Code:$
```c
#include <stdio.h>
int a,b,c,d,e,f;
int main(void) {
    scanf("%d %d %d %d %d %d",&a,&b,&c,&d,&e,&f);
    if(d && (a*c*e<b*d*f || (!a && b) || (!c))) puts("Ron");
    else puts("Hermione");
    return 0;
}
```

~~个人认为是写的最详尽的一篇。~~

完结撒花~

---

## 作者：Fengxiang008 (赞：1)

### 题意分析：

有 **$3$** 种魔法;   

1. 可以将 $a$ 单位的石头变成 $b$ 单位的铅。   
2. 可以将 $c$ 单位的铅变成 $d$ 单位的金子。     
3. 可以将 $e$ 单位的金子变成 $f$ 单位的石头。

问 **能不能** 用 **这 $3$ 种** 魔法通过有限量的石头得到无限量的金子。

### 解题思路：

分类：

① 这几个数字 **都大于** $0$  
假设一开始你有 $ a \times c \times e $ 单位的石头;     
$\Rightarrow$ 换成 $ b \times c \times e $ 单位的铅;     
$\Rightarrow$ 换成 $ b \times d \times e $ 单位的金子;     
$\Rightarrow$ 换成 $ b \times d \times f $ 单位的石头;    
若$ a \times c \times e < b \times d \times f $，   
则可以在得到一定量的金子的情况下又获得等量的石头，  
则可以一直增加金子;则可以获得无限量的金子。   
② $ b,d,f $ 里面 **有等于** $0$  的       
$d$ 首先 **不能等于** $0$,   
然后,如果 $ c $ **等于** $0$ 则也可行;    
或者 $ c $ **不等于** $0$,      
但是 $ b > 0 $ 且 $ a = 0 $,    
或者 $ b > 0 $ 且 $ a > 0 $ 且 $ ( e = 0 , f > 0 ) $ 也可行。
 
### 代码：

 ```cpp
#include <bits/stdc++.h>
using namespace std;
int a,b,c,d,e,f;
int main()
{
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> a >> b >> c >> d >> e >> f;
    if ( (a*c*e < b*d*f) || (d && (!c || (b &&(!a || (!e && f))))))
        cout <<"Ron"<<endl;
    else
        cout <<"Hermione"<<endl;
    return 0;
}
```


---

## 作者：feicheng (赞：1)

蒟蒻的第 $100$ 道橙题，写个题解纪念一下。

此题真的是非常有趣（尤其是对于哈迷）

------------
## 题意简述：
已知 $a$ 克沙子能变成 $b$ 克铅，$c$ 克铅可以变成 $d$ 克金，$e$ 克金可以变成 $f$ 克沙子，问能否有一种方法使生成的金子数无限。

$0\le a,b,c,d,e,f\le1000$
## 思路讲解：
我们按照题意来模拟

$$\frac b a\times\frac d c \times\frac f e$$ 
就是沙子到金子的转换率，于是我们只要让
$$bdf-ace > 0$$
即可

但是上过小学的我们都知道：分母是不能为0的。

所以我们要特判：

首先我们发现掌控着命门的是 $d$ 的值，如果 $d$ 为0，你换出金子的梦想就破灭了。所以第一个特判就是
```cpp
if(!d) cout << "Hermione";
```
然后我们枚举分母为0的情况（默认 $d \ne 0$）：

1.$a$ 为 0

此时，如果 $b$ 不为0，我们就可以无限造铅，也就可以无限造金。于是
```cpp
if(!a && b) cout <<"Ron";
```
2.$c$ 为 0

意味着我们可以 $0$ 成本造金，于是
```cpp
if(!c) cout << "Ron";
```
3.$e$ 为 0

由于 $e$ 是金换沙，但是只要我有沙并且满足了上面的情况即可。所以对于 $e$ 可以不判断。

代码就不贴了，非常简单。

---

## 作者：jijidawang (赞：1)

其实这题利用一下不等式就行。

首先依题意列出不等式（如果能产生无限黄金的情况）：

$$\dfrac{\dfrac{b}{c}\times d}e\times f>a$$

不等式两端同乘 $e$：

$$e\times \dfrac{\dfrac{b}{c}\times d}e\times f>ae$$

$$\dfrac{b}c\times df>ae$$

不等式两端同乘 $c$：

$$c\times \dfrac{b}c\times df>ace$$

$$bdf>ace$$

得出获得无限黄金条件为 $bdf>ace$。

且要变出黄金还有以下附加条件：

1. 若 $d\neq 0$，则不能变出黄金。

2. 若 $c=0,d\neq0$，可以无限变出黄金。

3. 若 $a=0,b\neq 0,d\neq0$，可以无限变出铅，铅变出黄金。

所以代码就很好写了：

```cpp
#include<iostream>
using namespace std;
int main()
{
    int a,b,c,d,e,f;
    cin>>a>>b>>c>>d>>e>>f;
    if(((b*d*f>a*c*e)||(c==0&&d!=0)||(a==0&&b!=0&&d!=0))&&d!=0) cout<<"Ron";
    else cout<<"Hermione";
    return 0;
}
```



---

## 作者：xiaoming_king (赞：1)

依次判断是否为零即可！注意在输入顺序中是ace和bdf

**注意本人使用的是Python2，（Python2两种皆可）Python3把raw_put改为put皆可**
```python
a,b,c,d,e,f=map(int,raw_input().split())
print ('Hermione','Ron')[e*c*a<f*d*b or a==0 and b*d>0 or c==0 and d>0]
```



---

## 作者：szbszb (赞：1)

#### 我很好奇这为什么是到紫题

开始讲题解：

注意的是，题目中a,b,c,d,e,f都可能为0，所以，这里就需要判断一下。

由于是要得到金子，所以判断顺序是(c,d)->(a,b)->(e,f)

为了讲题方便，我们在这里约定x1代表c,a,e;x2代表d,b,f;那么，若x2为零，那么肯定不行，输出"Hermione"，否则判断x1，若x1为零则输出"Ron"

若a,b,c,d,e,f都不为0，那么设开始有一克沙子，那一轮下来就是(b/a) * (d/c) * (f/e)，整理得(b * d * f)/(a * c * e)，即比较两者大小即可

讲了这么多，下面上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,c,d,e,f,s1,s2;
int main()
{
	scanf("%lld%lld%lld%lld%lld%lld",&a,&b,&c,&d,&e,&f);
	s1=b*d*f;
	s2=a*c*e;//计算除式中被除数与除数
	if (c==0)
		if(d!=0) printf("Ron");
		else printf("Hermione");
	else if (d==0) printf("Hermione");
	else if (a==0)
		if(b!=0) printf("Ron");
		else printf("Hermione");
	else if (b==0) printf("Hermione");
	else if (e==0)
		if (f!=0) printf("Ron");
		else printf("Hermione");
	else if (f==0) printf("Hermione");//特判各种情况
	else if (s1>s2) printf("Ron");//一般情况的判断
	else printf("Hermione");
	return 0;
}
```
这道题就到这里啦

---

## 作者：Oscar12345 (赞：1)

嗯，没错，这是一道~~骚气~~普通的题目，数学有底子的人可以轻松通过，就是一个读入加一个判断，就这么简单。
代码在下面：
```
#include<iostream>
using namespace std;

int main()
{
	int a,b,c,d,e,f;
	cin>>a>>b>>c>>d>>e>>f;
	if((a*c*e<b*d*f) || (!c&&d)|| (!a&&b&&d))
	{
		cout<<"Ron"<<endl;
		return 0;
	}
	else
	{
		cout<<"Hermione"<<endl;
		return 0;
	}
	return 0;
}
```

---

## 作者：HohleFeuerwerke (赞：0)

~~令人窒息的洛谷难度标签。~~

#### 前言

[题目](https://www.luogu.com.cn/problem/CF65A)在此，一道大水题，难度标签严重出锅。

#### 正文

题目就是问你，通过不停的转换，能否得到无限的物质。

转换关系：（为表述方便，取化学式表示。）

$$a \cdot \text{SiO}_2=b\cdot \text{Pb}$$
$$c\cdot \text{Pb}=d\cdot \text{Au}$$
$$e\cdot \text{Au}=f\cdot \text{SiO}_2$$

因为物质相同，我们可以将其转换为连等式：

$$\text{SiO}_2=\frac{b}{a} \cdot \text{Pt}=\frac{bd}{ac}\cdot \text{Au}=\frac{bdf}{ace}\cdot \text{SiO}_2$$

我们发现我们将 $1$ 克 $\text{SiO}_2$ 转化为了 $\frac{bdf}{ace}$ 克 $\text{SiO}_2$，那么显然，如果 $\frac{bdf}{ace}>1$，那么可以通过更多次的转换得到更多的沙子。反之，如果$\frac{bdf}{ace}\leq 1$，那么一定得不到无限的沙子，也一定得不到无限的黄金。

所以我们的程序首先第一步，判断 $\frac{bdf}{ace}$ 与 $1$ 的大小关系。

这时候你一交上去，？，WA了。

欸我就是百思不得其解啊，为什么呢？因为有很多 $0$。

当 $a,b,c,d,e,f$ 中有 $0$，情况是不是更加复杂了呢？

其实不然。

考虑一下几种情况：

>·  $d=0$ 此时一定不能，因为得不到 $\text{Au}$。

>·  $a=0$ 此时若 $d≠0$ 则可以，因为可以大量得到 $\text{Pb}$ 。若 $d=0$ 如上证，则不行。

>·  $c=0$ 此时若 $b≠0$ 且 $d≠0$ 则可以。

贴代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d,e,f;
int main()
{
	ios::sync_with_stdio(false);
	cout.tie(0);cin.tie(0);
	cin>>a>>b>>c>>d>>e>>f;
	if(d==0) cout<<"Hermione"<<endl;
	else if(a*c*e<b*d*f) cout<<"Ron"<<endl;
	else if((a==0&&b!=0)||c==0) cout<<"Ron"<<endl;
	else cout<<"Hermione"<<endl;
}
```

---

