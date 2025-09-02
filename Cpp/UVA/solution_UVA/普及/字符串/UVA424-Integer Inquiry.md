# Integer Inquiry

## 题目描述

BIT 的新超级计算机的第一批用户之一是 Chip Diller。他将他对 $3$ 的幂的探索扩展到了从 $0$ 到 $333$ 的范围，并研究了这些数字的各种和。

“这台超级计算机真棒，”Chip 说。“我只希望 Timothy 能在这里看到这些结果。”

（Chip 搬到了一个新公寓，一旦第三街 Lemon Sky 公寓三楼有空房，他就搬了进去。）

## 样例 #1

### 输入

```
123456789012345678901234567890
123456789012345678901234567890
123456789012345678901234567890
0```

### 输出

```
370370367037037036703703703670```

# 题解

## 作者：ADay (赞：5)

# $\mathcal{Py3}$详解  
先贴完整代码：
```python
sums=0 #定义sums为0
while True:  #循环
    n=int(input()) #输入n
    if n==0: #为0跳出
        break
    sums+=n #做加法
print(sums) #输出
```
## 讲解：
### Step1:
```python
sums=0 #定义sums为0
```
$Py$中定义变量直接赋值即可，毕竟是面向对象的语言嘛~
### Step2：
```python
while True:  #循环
```
这是$while$循环，注意：
- $true$要大写首字母
- 要打冒号
- 没有括号
### Step3：
```python
n=int(input()) #输入n，转为整
```
$input()$默认输入的是字符串，我们需要$int$函数转为整数   
### Step4：
```python
if n==0: #为0跳出
	break
```
$if$和$while$一样，都要打冒号，没有括号  
### Step5：
```python
sums+=n #做加法
```
加法不解释了
### Step6：
```python
print(sums) #输出
```
用$print$函数输出即可   
~~Ps:为什么这是说明过少？我明明比其他Py的讲得很详细了~~

---

## 作者：PY_Fighter (赞：2)

**居然没有python题解？！！**

为了帮（dai）助（huai）新人，是时候水一发python了！

```python
ans=0
n=int(input())
while (n>0):
    ans+=n
    n=int(input())
print(ans)

```

---

## 作者：lujunyu (赞：1)

题意翻译明确告诉我们这一题要用高精度。
### 思路
定义一个累加器 $sum$，设初始值为$0$。用 $while$ 循环：只要输入一个不是$0$的数，就用高精度做累加；否则，就跳出循环，并且输出 $sum$。

记得输出换行！
### 代码
[戳这里](https://www.luogu.com.cn/paste/eusf800u)（太长了就不放出来了）

---

## 作者：xingchenyu (赞：1)

```cpp
#include<bits/stdc++.h>
using namespace std;
string add(string str1,string str2){
    string str;
    int len1=str1.length();
    int len2=str2.length();
    if(len1<len2)for(int i=1;i<=len2-len1;i++)str1="0"+str1;
    else for(int i=1;i<=len1-len2;i++)str2="0"+str2;
    len1=str1.length();
    int cf=0;
    int temp;
    for(int i=len1-1;i>=0;i--){
        temp=str1[i]-'0'+str2[i]-'0'+cf;
        cf=temp/10;
        temp%=10;
        str=char(temp+'0')+str;
    }
    if(cf)str=char(cf+'0')+str;
    return str;
}
int main(){
	string a = "0",b;
	for(;cin >> b;){
		if(b=="0"){
			cout << a;
			return 0;
		}
		a = add(a,b);
	}
}
```
$string$
高精板子

---

## 作者：溪水瑶 (赞：1)

## Python 3
这题对于Python语言来说就是一道很水的题目啦。


------------
## 敲黑板（认真听）
毕竟Python语言自带高精度，可以直接加；
## 下面窝给大家看看代码
```python
sum=0
s=int(input())
while s:
    sum+=s
    s=int(input())
print(sum)
```
非常简洁，完美撒花，大佬勿喷！！

---

## 作者：happybob (赞：0)

这题目用 python 做很好，虽然我是c党，但是没有自带高精度表示不服，学了学几个最简单的语句做了个py3代码然后A了：

```
var = 1
ans = 0
while var == 1:
    num = int(input())
    if num == 0:
        break
    else:
        ans = ans + num
print(ans)

```


---

## 作者：Contemptuous (赞：0)

对于自带高精的语言来说，这道题真是简单。

我们可以先定义一个累加器$s$，把它的值设为$0$，然后对于输入的每个数，如果它为$0$就直接跳出循环，输出累加器即可。否则就累加。

上代码。
```python
s = 0

while True:
    a = int(input())
    if a == 0:
        break
    
    s += a
    
print(s)
```

---

## 作者：_Qer (赞：0)

简直高精板子

全部程序放上来太长（我是直接套板子的），这里分段给出程序，要看我的全套高精模板请戳[这里（我的博客）](https://www.luogu.org/blog/WAFUN/gao-jing-mu-ban)

```cpp
struct Bigint{
  int l, a[Maxlen];
};
int main() {
	Bigint ans, tmp;
	ans.l = 1;
	ans.a[1] = 0;
    //以上初始化
	while(1) {
		read_Bigint(tmp);//输入大整数
		if (tmp.l == 1 && tmp.a[1] == 0) {
			break;//输入为0时结束
		}
		ans = ans + tmp;//重载过+号，详见上面链接
	}
	write_Bigint(ans);
	puts("");
    return 0;
}
```

其中输入及输出部分：

```cpp
inline void read_Bigint(Bigint &x) {
  string s;
  cin >> s;
  x.l = s.length();
  for (int i = 1; i <= x.l; ++i) {
    x.a[i] = s[x.l - i] - '0';
  }
  //就是处理字符串，变为大整数
}
inline void write_Bigint(const Bigint &x) {
  for (int i = x.l; i; --i) {
    putchar(x.a[i] + '0');
  }
  //从高位输出
}
```

加法（就像列竖式的计算方法）：

```cpp
Bigint operator+(const Bigint &num1, const Bigint &num2) {
  int c = 0;
  Bigint res;
  res.l = max(num1.l, num2.l);
  for (int i = 1; i <= res.l; ++i) {
    res.a[i] = num1.a[i] + num2.a[i] + c;
    c = res.a[i] / 10;
    res.a[i] %= 10;
  }
  if (c) {
    res.a[++res.l] = c;
  }
  return res;
}
```

---

## 作者：hero_brine (赞：0)

逛了一遍题解圈，发现竟然没有Java题解，本蒟蒻在此水一篇Java题解，具体代码及说明如下：
```java
import java.math.BigInteger;
import java.util.Scanner;
public class Main
{
    static Scanner cin = new Scanner(System.in);
    static BigInteger in,num = new BigInteger("0");
    static String cache = null;
    public static void main(final String[] args){
        while (true){
            cache = cin.next();
            if (cache.equals("0")) break;
            in = new BigInteger(cache);
            num = num.add(in);
        }
        System.out.println(num);
        cin.close();
    }
}
```
注意事项如下：
1. 我们需要导入$BigInteger$类来实现大数加法，导入$Scanner$类来输入结果
2. 变量最好在$main$函数外$static$定义
3. $BigInteger$是通过$String$转化的，所以我们先输入一个$String$，再将其转化成为$BigInteger$类
4. 循环输入时，判断是否输入0，一定要用$equals$函数，我就是因为这个错了好几回
5. 定义$sum$,使用$add$函数做加法
6. 记得释放内存
7. $class$名一定要定义成 $Main$
8. 输出要换行
9. $main$函数的参数需要使用$final$修饰符

PS:可以放心使用，经过本人亲测不会TLE, 已 [AC](https://www.luogu.com.cn/record/32115697)。

---

