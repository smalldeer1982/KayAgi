# Calculating Function

## 题目描述

For a positive integer $ n $ let's define a function $ f $ :

 $ f(n)=-1+2-3+..+(-1)^{n}n $

Your task is to calculate $ f(n) $ for a given integer $ n $ .

## 说明/提示

 $ f(4)=-1+2-3+4=2 $

 $ f(5)=-1+2-3+4-5=-3 $

## 样例 #1

### 输入

```
4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
```

### 输出

```
-3
```

# 题解

## 作者：A_Đark_Horcrux (赞：5)

既然翻译都发了那再发发题解！
也是挺水的题目啊。

但是即使只用一个循环也会超时 (1<=n<=10^15)，所以我们以找规律的思想做

可以发现遇到奇数就减，偶数就加，所以：

当n是偶数时，结果就是n/2（每个奇数比偶数小1,一对就是加1）；

当n是奇数时，最后一项就是n，而且是在奇数项，所以结果就是(n-1)/2-n  (化简后就是-n/2-1)

所以代码也很简单！
```cpp
#include<iostream>
using namespace std;
int main()
{
	long long n,i;
	cin>>n;
	if(n%2==0)
		cout<<n/2;
	else
		cout<<-n/2-1;
	return 0;
}
```


---

## 作者：Fatelism (赞：0)

一看题目：
```
f(n)=-1+2-3+4...+(-1)^n*n
```
嗯，感觉十分简单的样子，就是先绝对值加1，第奇数个为负，偶数个为正.。  
那就直接套公式吧

```cpp
#include<cstdio>
using namespace std;
int pow(int x,int k){
	int sum=1;
	for(int i=0;i<k;i++)sum*=x;
	return sum;
}
int main(){
	int n,ans=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)ans+=pow(-1,i)*i;
	printf("%d",ans);
	return 0;
}
```
然后就非常愉快的~~AC~~TLE了！  
唉？不是吧，这么会超时呢，样例也过得去。  
嗯：
```
1<=n<10^15
```
这不就意味着如果题目来个10^15，程序不就要跑个1000000000000000次？不行不行，要改。  
怎么改呢？肯定要找一下规律：
```
每个奇数位的数与它后面的数相加=1
```
这也很好证明：
```
-x+(x+1)=1
```
所以就可以化简程序了。  
当n是偶数时，答案就是n/2  
当n是奇数时，答案就是-1*(n/2)-1=-1*(n/2+1)  
再附上代码：
```cpp
#include<iostream>
using namespace std;
int main(){
	long long n,ans;//long long不能忘！
	cin>>n;
	if(n%2==0)ans=n/2;
	else ans=-1*(n/2+1);
	cout<<ans;
	return 0;
}
```


---

## 作者：动态WA (赞：0)

## 本题解为python 3题解

自从用了python 3，妈妈再也不用担心我没开long long了。

通过观察数据范围~~和题目难度~~，可以看出这是一道找规律的题目，再观察函数，发现第奇数项是减，第偶数项是加，于是分类讨论。

列举奇数项：
| n | 1 |  3| 5 | 7 | 9 |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
|f(n)  | -1 | -2 | -3 | -4 | -5 |

由此得出，当n是奇数，f(n)=-(n//2+1)

列举偶数项：
| n | 2 | 4 | 6 | 8 |10  |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| f(n) | 1 | 2 | 3 | 4 | 5 |

由此得出，当n是偶数，f(n)=n//2

代码如下：
```python
n=int(input())
if n%2==0:
    print(n//2)
else:
    print(-(n//2+1))
```
python 3自带高精（高兴.jpg

---

## 作者：Remake_ (赞：0)

蒟蒻alex070423来写题解了！

首先，不可否认的是，这是一道非常水的题。但是你能告诉我这题的标签为什么有递推吗？

我们先从递推入手，运用幼儿园的数学知识可得。

```cpp
F[1]=-1;
F[n]=F[n-1]+n*pow(-1,n);
```
提交上去，TLE。

考虑优化。

使用各种玄学优化。

```cpp
#pragma GCC target("sse,sse2,sse3,sse4.1,sse4.2,popcnt,abm,mmx,avx")
#pragma comment(linker,"/STACK:102400000,102400000")
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
```
把这些全部加上仍是无济于事qwq。

所以，基本上可以确定，要用数论！！！

虽然这题的数论也是幼儿园级别的，但是，依旧要配上严谨的证明。

先证$x$与$x-1$的差是$1$：$x-(x-1)=x-x+1=1$。

接着观察得出相邻两项可以组合，求和出来的值便是组出的项数$\times 1$。但是这时我们又考虑到有可能最后一个数落单，而我们知道只有在奇数时才会这样，所以，分类讨论！。

为偶数时，非常好想：

```cpp
ans=n/2；
```

奇数时我们知道第奇数个数一定为负，所以能推出如下式子：

```cpp
ans=floor(n/2)-n；
```

完美！

上代码？

不，由于我是压行狂魔，再给大家介绍一个压行神器：三目运算符！！！

原本需要六行写的东西它只用一行！

普通形式：

```cpp
if(...){
do something1
}
else{
do something2
}
```
~~魔鬼~~三目运算符形式：

```cpp
...?do someting1:do something2;
```

压行代码呈上：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long a;
	cin>>a;
	a%2==0?cout<<a/2:cout<<(a-1)/2-a;
}
```

这是本蒟蒻的第一篇**水题题解**，之前还从未写过入门题解，虽然与其他人思路相同，但我想让更多蒟蒻理解的更明白，并且~~有更多推导~~，此外，希望电脑前的您能学会一些~~玄学优化~~，以及三目运算符，最后，希望此篇题解能成功通过，成为本蒟蒻的第四篇题解，也祝正在看这篇题解的你们：

# RP++;

---

## 作者：阿柒 (赞：0)

###### 这道题其实非常容易，连for循环都用不着。只要找出它的规律就行了。

#### 当n%2==0时，只需要输出n/2.
#### 当n%2==1时，就要输出(n-1)/2-n（也就是-n/2-1）

# 代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long int a;
int main()
{
	cin>>a;
	if(a%2==0)
	{
		cout<<a/2<<endl;
	}
	else
	{
		cout<<-a/2-1<<endl;
	}
	return 0;
}
```


---

## 作者：良心油条 (赞：0)

~~看这题没人写题解，蒟蒻我就来写个题解吧，希望大家喜欢~~


### 一道超级明显的递推题


允许我这个蒟蒻吐槽一下，这题还算比较的坑。所以，我们要先$look$一下数据范围： 
### $n$到$10^{15}$
 
 这一看就知道了出题者的套路：$longint$类型（$Pascal$）和$int$（$c++$）肯定爆啊！！！所以只能用递推做。   
 
 我们回到样例，发现有点蹊跷————如果$n$是奇数，就加上$1$以后$div 2$，别忘了答案是负数；如果$n$是偶数，就直接输出$n div 2$。。。这答案不就出来了吗？？？   
 
好心作者送上递推公式伪代码（完整代码见下面）：
 ```pascal
if not odd(n) then
  writeln(n div 2) else
  writeln(0-(n+1) div 2);
```

(其实我这么写有点麻烦，但是这样更加通俗易懂）

好了，废话不多说，我们直接贴上完整代码（请勿摘抄题解，共创美好洛谷）：
```pascal
var
  n:int64;
begin
  readln(n);
  if not odd(n) then
    writeln(n div 2) else
    writeln(0-(n+1) div 2);
end.

```

---

