# Petya and Java

## 题目描述

Little Petya has recently started attending a programming club. Naturally he is facing the problem of choosing a programming language. After long considerations he realized that Java is the best choice. The main argument in favor of choosing Java was that it has a very large integer data type, called BigInteger.

But having attended several classes of the club, Petya realized that not all tasks require using the BigInteger type. It turned out that in some tasks it is much easier to use small data types. That's why a question arises: "Which integer type to use if one wants to store a positive integer $ n $ ?"

Petya knows only 5 integer types:

1\) byte occupies 1 byte and allows you to store numbers from $ -128 $ to $ 127 $

2\) short occupies 2 bytes and allows you to store numbers from $ -32768 $ to $ 32767 $

3\) int occupies 4 bytes and allows you to store numbers from $ -2147483648 $ to $ 2147483647 $

4\) long occupies 8 bytes and allows you to store numbers from $ -9223372036854775808 $ to $ 9223372036854775807 $

5\) BigInteger can store any integer number, but at that it is not a primitive type, and operations with it are much slower.

For all the types given above the boundary values are included in the value range.

From this list, Petya wants to choose the smallest type that can store a positive integer $ n $ . Since BigInteger works much slower, Peter regards it last. Help him.

## 样例 #1

### 输入

```
127
```

### 输出

```
byte
```

## 样例 #2

### 输入

```
130
```

### 输出

```
short
```

## 样例 #3

### 输入

```
123456789101112131415161718192021222324
```

### 输出

```
BigInteger
```

# 题解

## 作者：OdtreePrince (赞：9)

# -字符串-

看我蒟蒻打了那么多行，求通过。

直接用char模拟，如果符合，输出；否则，继续判断或输出下一阶层。

负号的处理有点麻烦，因此用char数组记录，OK！

终于上代码了！

~~~
#include<bits/stdc++.h>
using namespace std;
char ch[105];
int main(){
    int k=1,l;
    string s;
    cin>>s;
    l=s.size();
    if(s[0]=='-') k=0,l--;
    for(int i=0;i<l;i++){
        if(k==1) ch[i+1]=s[i];
        else ch[i+1]=s[i+1];
    }
    if(k==0) ch[l]-=1;
    if(l<=3){
        if(l<3) cout<<"byte";
        else{
            if(ch[2]<='2'){
                if(ch[2]<'2'||ch[3]<='7'){
                    cout<<"byte";
                }
                else cout<<"short";
            }
            else cout<<"short";
        }
    }
    else{//32767
        if(l<=5){
            if(l<5) cout<<"short";
            else
            if(ch[1]<='3'){
                if(ch[1]<'3'){
                    cout<<"short";
                }
                else{
                    if(ch[2]<='2'){
                        if(ch[2]<'2'){
                            cout<<"short";
                        }
                        else{
                            if(ch[3]<='7'){
                                if(ch[3]<'7'){
                                    cout<<"short";
                                }
                                else{
                                    if(ch[4]<='6'){
                                        if(ch[4]<'6'){
                                            cout<<"short";
                                        }
                                        else{
                                            if(ch[5]<='7'){
                                                cout<<"short";
                                            }
                                            else cout<<"int";
                                        }
                                    }
                                    else cout<<"int";
                                }
                            }
                            else cout<<"int";
                        }
                    }
                    else cout<<"int";
                }
            }
            else cout<<"int";
        }
        else{//2147483647
            if(l<=10){
                if(l<10) cout<<"int";
                else
            if(ch[1]<='2'){
                if(ch[1]<'2'){
                    cout<<"int";
                }
                else{
                    if(ch[2]<='1'){
                        if(ch[2]<'1'){
                            cout<<"int";
                        }
                        else{
                            if(ch[3]<='4'){
                                if(ch[3]<'4'){
                                    cout<<"int";
                                }
                                else{
                                    if(ch[4]<='7'){
                                        if(ch[4]<'7'){
                                            cout<<"int";
                                        }
                                        else{
                                            if(ch[5]<='4'){
                                                if(ch[5]<'4'){
                                                    cout<<"int";
                                                }
                                                else{
                                                    if(ch[6]<='8'){
                if(ch[6]<'8'){
                    cout<<"int";
                }
                else{
                    if(ch[7]<='3'){
                        if(ch[7]<'3'){
                            cout<<"int";
                        }
                        else{
                            if(ch[8]<='6'){
                                if(ch[8]<'6'){
                                    cout<<"int";
                                }
                                else{
                                    if(ch[9]<='4'){
                                        if(ch[9]<'4'){
                                            cout<<"int";
                                        }
                                        else{
                                            if(ch[10]<='7'){
                                                cout<<"int";
                                            }
                                            else cout<<"long";
                                        }
                                    }
                                    else cout<<"long";
                                }
                            }
                            else cout<<"long";
                        }
                    }
                    else cout<<"long";
                }
            }
            else cout<<"long";
                                                }
                                            }
                                            else cout<<"long";
                                        }
                                    }
                                    else cout<<"long";
                                }
                            }
                            else cout<<"long";
                        }
                    }
                    else cout<<"long";
                }
            }
            else cout<<"long";
        }
        else{//9223372036854775807
        if(l<=19){
            if(l<19) cout<<"long";
            else
            if(ch[1]<='9'){
                if(ch[1]<'9'){
                    cout<<"long";
                }
                else{
                    if(ch[2]<='2'){
                        if(ch[2]<'2'){
                            cout<<"long";
                        }
                        else{
                            if(ch[3]<='2'){
                                if(ch[3]<'2'){
                                    cout<<"long";
                                }
                                else{
                                    if(ch[4]<='3'){
                                        if(ch[4]<'3'){
                                            cout<<"long";
                                        }
                                        else{
                                            if(ch[5]<='3'){
                                                if(ch[5]<'3'){
                                                    cout<<"long";
                                                }
                                                else{
                                                    if(ch[6]<='7'){
                if(ch[6]<'7'){
                    cout<<"long";
                }
                else{
                    if(ch[7]<='2'){
                        if(ch[7]<'2'){
                            cout<<"long";
                        }
                        else{
                            if(ch[8]<='0'){
                                if(ch[8]<'0'){
                                    cout<<"long";
                                }
                                else{
                                    if(ch[9]<='3'){
                                        if(ch[9]<'3'){
                                            cout<<"long";
                                        }
                                        else{
                                            if(ch[10]<='6'){
                                                if(ch[10]<'6'){
                                                    cout<<"long";
                                                }
                                                else{
                                                    if(ch[11]<='8'){
                if(ch[11]<'8'){
                    cout<<"long";
                }
                else{
                    if(ch[12]<='5'){
                        if(ch[12]<'5'){
                            cout<<"long";
                        }
                        else{
                            if(ch[13]<='4'){
                                if(ch[13]<'4'){
                                    cout<<"long";
                                }
                                else{
                                    if(ch[14]<='7'){
                                        if(ch[14]<'7'){
                                            cout<<"long";
                                        }
                                        else{
                                            if(ch[15]<='7'){
                                                if(ch[15]<'7'){
                                                    cout<<"long";
                                                }
                                                else{
                                                    if(ch[16]<='5'){
                if(ch[16]<'5'){
                    cout<<"long";
                }
                else{
                    if(ch[17]<='8'){
                        if(ch[17]<'8'){
                            cout<<"long";
                        }
                        else{
                            if(ch[18]<='0'){
                                if(ch[18]<'0'){
                                    cout<<"long";
                                }
                                else{
                                    if(ch[19]<='7'){
                                        cout<<"long";
                                    }
                                    else cout<<"BigInteger";
                                }
                            }
                            else cout<<"BigInteger";
                        }
                    }
                    else cout<<"BigInteger";
                }
            }
            else cout<<"BigInteger";
                                                }
                                            }
                                            else cout<<"BigInteger";
                                        }
                                    }
                                    else cout<<"BigInteger";
                                }
                            }
                            else cout<<"BigInteger";
                        }
                    }
                    else cout<<"BigInteger";
                }
            }
            else cout<<"BigInteger";
                                                }
                                            }
                                            else cout<<"BigInteger";
                                        }
                                    }
                                    else cout<<"BigInteger";
                                }
                            }
                            else cout<<"BigInteger";
                        }
                    }
                    else cout<<"BigInteger";
                }
            }
            else cout<<"BigInteger";
                                                }
                                            }
                                            else cout<<"BigInteger";
                                        }
                                    }
                                    else cout<<"BigInteger";
                                }
                            }
                            else cout<<"BigInteger";
                        }
                    }
                    else cout<<"BigInteger";
                }
            }
            else cout<<"BigInteger";
        }
        else cout<<"BigInteger";
        }
        }
    }
    return 0;
}
~~~

---

## 作者：David_H_ (赞：4)

这题挺水的。

我们发现 `long double` 的范围约为 $[-1.2\times10^{-4932},1.2\times10^{4932}]$

然后题目给我们的判断最大值正好比这个区间小。（`long`：$[-9223372036854775808,9223372036854775807]$）

那我们就开一个 `long double` 来判断就好了。

代码：

```cpp
#include <iostream>
using namespace std;
int main(void) {
    long double a;
    cin >> a;
    if (a >= -128 && a <= 127)
        cout << "byte";
    else if (a >= -32768 && a <= 32767)
        cout << "short";
    else if (a >= -2147483648 && a <= 2147483647)
        cout << "int";
    else if (a >= -9223372036854775808 && a <= 9223372036854775807)
        cout << "long";
    else
        cout << "BigInteger";
}
```

那为什么不能够用 `long long` 呢？因为 `long long` 的范围卡在了 $[-9223372036854775808,9223372036854775807]$，导致他没有办法判断大于 $9223372036854775807$ 或者小于 $-9223372036854775808$ 的情况。所以才采用 `long double`。

---

## 作者：hensier (赞：3)

这道题其实可以用$PY3$来做，因为$PY3$自带高精度。

对于这种语言来说，本题可以快速解决，通过几个循环判断即可。代码如下：

```python
a=int(input()) # 不加int()的话会默认为输入字符串
if a > -128 and a < 128: # 判断语句
    print('byte') # 注意PY3里输出要加括号
elif a > -32768 and a < 32768: # elif等同于else if
    print('short')
elif a > -2147483648 and a < 2147483648:
    print('int')
elif a > -9223372036854775808 and a < 9223372036854775808:
    print('long')
else:
    print('BigInteger')
```

或者，我们可以使用$longdouble$。这种类型可以存储很大的数据，只不过，精度不够。但是这道题都是整数，所以精度对题目影响不大。即：

```cpp
#include<iostream>
using namespace std;
long double s;
int main()
{
    cin>>s;
    cout<<(s>=-128&&s<128?"byte":s>=-32768&&s<32768?"short":s>=-2147483648&&s<2147483648?"int":s>=-9223372036854775808&&s<9223372036854775808?"long":"BigInteger");//一定要加括号
}
```

---

## 作者：封禁用户 (赞：2)

这道题其实很水。

虽然$long$ $long$过不了,但是c++还有一种类型名叫做$long$ $double$,它的范围应该比此题的数据范围大(好像有几千位)

所以这道题就迎刃而解了

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long double x;
	cin>>x;
	if(x>=-128&&x<=127)
	{
		cout<<"byte";
		return 0;
	}
	if(x>=-32768&&x<=32767)
	{
		cout<<"short";
		return 0;
	}
	if(x>=-2147483648&&x<=2147483647)
	{
		cout<<"int";
		return 0;
	}
	if(x>=-9223372036854775808&&x<=9223372036854775807)
	{
		cout<<"long";
		return 0;
	}
	else
	{
		cout<<"BigInteger";
		return 0;
	}
    	//以上的是几种类型的判断,一定要按顺序!
}
```

~~点个赞呗~~(QAQ)

---

## 作者：PragmaGCC (赞：1)

如果说没有这奇妙的数据范围的话，这就是一道水题

但是：

$\large -10^{100} \leqslant n \leqslant 10^{100}$

似乎有点大了吧/fad

`long long`说：别看我，我储存不下来这么大的数

`unsigned long long`说：别看我，我存不了负数

`long double`说：我 txdy！（tql，%%%）

于是，我们珂以用`long double`来做这道题qwq

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
typedef long double txdy;
int main()
{
    txdy a;
    cin >> a; // 这里是因为不知什么原因，使用scanf会WA爆掉，索性就直接用cin来读入了
    if (a >= -128 && a <= 127)
        printf("byte\n");
    else if (a >= -32768 && a <= 32767)
        printf("short\n");
    else if (a >= -2147483648 && a <= 2147483647)
        printf("int\n");
    else if (a >= -9223372036854775808 && a <= 9223372036854775807)
        printf("long\n");
    else
        printf("BigInteger\n");
    return 0;
}
```

---

## 作者：Oscar12345 (赞：1)

嗯，这又是一道水的不能再水的水题，就是数据范围有点坑爹， （10^-100<=n<=10^100）这么大的数据long long都要挂，so，我们选用long double这个数据可以存到1e+308的超级类型，因为只有一个，所以我们不必担心会MLE，既然我们已经解决了数据存储的问题，那下面就是完成题目要求，嗯。。。就是一堆if判断即可，不要打错数据，否则就好玩了。

丑陋的代码：
```
#include<iostream>
using namespace std;

int main()
{
	long double n;
	cin>>n;
	if(n<=127)
	{
		cout<<"byte"<<endl;
	}
	else if(n<=32767)
	{
		cout<<"short"<<endl;
	}
	else if(n<=2147483647)
	{
		cout<<"int"<<endl;
	}
	else if(n<=9223372036854775807)
	{
		cout<<"long"<<endl;
	}
	else
	{
		cout<<"BigInteger"<<endl;
	}
	return 0;
}
```

---

## 作者：LucasXu80 (赞：0)

PY 大法好！

看到题解区已经有两篇使用Python的题解了，在这里科普Python的一个小技巧。

为了方便编程者使用而被创造的Python在很多地方都非常方便，本文介绍的便是其中之一。

来看一个例子：判断一个数是否$∈[0,100]$怎么写？

在C++可以这么写：

```cpp
if (a>=0&&a<=100)
```
这个没什么问题，是唯一的写法。在Python你也可以如法炮制：

```python
if a>=0 and a<=100:
```
但是Python中其实还可以像数学中的不等式这样写：

```python
if 0<=a<=100:
```
这样就方便多了！

附上代码，其他大佬们已经讲清了，就不加注释了~

```python
n=int(input())
if -128<=n<=127:
    print("byte")
elif -32768<=n<=32767:
    print("short")
elif -2147483648<=n<=2147483647:
    print("int")
elif -9223372036854775808<=n<=9223372036854775807:
    print("long")
else: print("BigInteger")
```
本文就告一段落了。如果这篇题解对你有帮助，别忘了点个赞！

---

## 作者：inoichi_lim (赞：0)

这题显然的高精度比较。

高精度，那么肯定用`python`。

逐个比较，在哪个范围里面，就直接输出这个范围所代表的类。

代码：
```python
a=int(input())
if a>-129 and a<128:
    print("byte")
elif a>-32769 and a<32768:
    print("short")
elif a>-2147483649 and a<2147483648:
    print("short")    
elif a>-9223372036854775809 and a<9223372036854775808:
    print("long") 
else:
    print("BigInteger")
```

---

## 作者：Sora1336 (赞：0)

这道题要判断的数字是**非常大**的。

>整型的大小是有极限的，越是尝试储存，就越会发现内存是有极限的...除非成为超越整型的存在。

>你在说什么啊long long int!

>我不做整型啦，string!

事实上，`long double`类型只适用于这样的变态题目来使用；在其他需要浮点数的地方其实并不需要如此庞大的类型。你想想，你买一个公交车做代步工具真的好吗？

`long double`的大小为16个字节。我们来验证一下`long double`是否可以储存$(-10^{100}\le n\le -10^{100}) $的数据范围。

一个字节有八个比特，一个比特可以代表2个值，$n$个比特可以代表$2^n$个值，而`long double`可以代表$2^{128}$个值，非常明显，是够的。所以我们可以用`long double`来AC这道题。

```cpp
#include <iostream>
using namespace std;
typedef long double ld;
int main() {
	ld a;	//不做整型的long double
	cin<<a;
	if(a>=-128 and a<=127)
		cout<<"byte";
	else if(a>=-32768 and a<=32767)
		cout<<"short";
	else if(a>=-2147483648 and a<=2147483647)
		cout<<"int";
	else if(a>=-9223372036854775808 and a<=9223372036854775807)
		cout<<"long";
	else
		cout<<"BigInteger";
}
```

~~谁抄谁CE~~

---

## 作者：monstersqwq (赞：0)

~~先%一下用字符串搞这题的大佬~~

进入正题：

这道题要判断的数字可谓是真的大（$-10^{100} \le n \le10^{100}$）, long long 完全存不下，于是我们使用更大~~更开挂~~的 long double ，作为一个占用16字节的超高精度变量，它可以妥妥的存下题目中的要求，然后就可以几个 if 解决问题啦。

代码：
```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <queue>
using namespace std;
int main()
{
	long double a;
	cin>>a;
	if(a>=-128&&a<=127) cout<<"byte"<<endl;
	else if(a>=-32768&&a<=32767) cout<<"short"<<endl;
	else if(a>=-2147483648&&a<=2147483647) cout<<"int"<<endl;
	else if(a>=-9223372036854775808&&a<=9223372036854775807) cout<<"long"<<endl;
	else cout<<"BigInteger"<<endl;
	return 0;
}
```


---

