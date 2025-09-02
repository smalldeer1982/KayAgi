# EXCEEDED WARNING B

## 题目背景

SGU 107


## 题目描述

求有多少个平方后末尾为 $987654321$ 的 $n$ 位数。

## 说明/提示

$1\le n\le 1 0^6$。

不要问我暴力能过几个点，我只想说呵呵。

## 样例 #1

### 输入

```
8```

### 输出

```
0```

# 题解

## 作者：远航之曲 (赞：31)

分析

先写个小程序 通过暴力枚举：


当n<=8时，无解


当n=9时 有8个满足要求的数：


111111111

119357639

380642361

388888889

611111111

619357639

880642361

888888889


容易知道，某个数的平方为987654321时，以这个数结尾的数，它的平方也是987654321


所以当n>9时，满足条件的数只能以上述八个数结尾


当n=10时，由于最高位不为0，所以又8\*9=72个


n=11时，71\*10个；n=12时,72\*10\*10个...以此类推

代码
```cpp
#include<cstdio>
int n;
int main()
{
    scanf("%d",&n);
    if (n<9) printf("0\n");
    else if (n==9) printf("8\n");
    else 
    {
        printf("72");
        for (int i=0;i<n-10;i++) printf("0");
        printf("\n");
    }
    return 0;
}

```

---

## 作者：多啦A梦007 (赞：5)

很明显，这是一题数论（这么大你说暴力？）

在n小于等于8的时候，是无解的，解法=0；

在n等于9的时候，有8组解（暴力得出）；

很明显，在n大于9的时候，最后9位的解就为上一行的8组解，在前（n-9）位中的每一位，第一位不能为0，有9种情况，其余有10种情况（0到9），所以很明显答案在大于9是等于

8\*9\*（10^（n-10））；

就好了

```cpp
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<iomanip>
using namespace std;
int i,j,k,m,n,js,jl;
int main()
{
    scanf("%d",&m);
    if(m<=8)
    {
        printf("0");
        exit(0);
    }
    if(m==9)
    {
        printf("8");
        exit(0);
    }
    printf("72");
    for(i=1;i<=m-10;i++)printf("0");
    return 0;
}
```

---

## 作者：TsReaper (赞：5)

跑个暴力不难发现当n=9时，答案为8

由于x^2的最后9位数只与x的最后9位数有关，

所以
当n=10时，答案为9\*8=72（首位不为0）

当n=11时，答案为9\*10\*8=720

当n=12时，答案为9\*10\*10\*8=7200

...
按照上面的规律就答出来了。


---

## 作者：_棉花糖_ (赞：2)

好像没什么Pascal的，那我就写一个吧（刚转成c++，有点怀念Pasal）

分析一下，这其实是道数论题，~~题面上竟然提到了暴力QAQ~~

我先写了个暴力的程序，发现（真的死慢的）：

1、当$n \leq 8$时，无解；

2、当$n = 9$时，有这几个满足条件的数：

111111111

119357639

380642361

388888889

611111111

619357639

880642361

888888889

容易知道，当$n>9$时，满足条件的数只能以上述八个数结尾

当$n=10$时，由于最高位不为0，所以又8*9=72个

$n=11$时，$72 \times 10$个；n=12时,$72 \times 10^{2}$个……

以此类推……

```pascal
var n,i:longint;
begin
    read(n);
    if n<=8 then write(0)
        else if n=9 then write(8)
            else 
                begin
                    write(72);
                    for(i:=1 to n-10 do)
                        write(0);
                end;
end.
```
好久没打Pascal了~~，我才不会告诉你我把read(n)打成了read>>n，把for(i:=1 to n-1 do)打成了for(i:=1;i<=n-1;i++)~~

声明一下，这个代码是我临时打的，换了电脑之后，我想着我要转c++了，连个Pascal编译器都没有，也没有GUIDE，只有Sublime和DEV C++，大家千万不要直接复制代码，我自己都没有编译，就算没有语法错误也不一定结果正确

~~（看看分析就行了，自己动手丰衣足食）~~

另外，我的博客欢迎参观

[传送门](https://www.luogu.org/blog/user67087/)

---

## 作者：heidoudou (赞：2)


#### Description

求有多少个平方后末尾为 `987654321`的 $n$ 位数

#### Analysis

这种数肯定不多，问题是如何找到这种数？

有一个常识是： $(100a + b)^2$， 如果 $a$ 任意，$b < 100$， 那么平方数的末两位数字只会由 $b$ 确定。

这个结论可以推广到 $(10^ka + b)^2$ 上。

最终只要找 $(10^{10}a + b)^2 \mod 10^{10} = 987654321$ 的 $b$ 就可以了。

因此就可以这样找：

1. 先找 $b$ 的个位，肯定只有 $1, 9$ 满足平方数末尾是 $1$
2. 再找 $b$ 的十位，用 `0 ~ 9` 十个数字拼上前面找的个位数，看看能不能得到 $21$
3. 再找 $b$ 的百位，用 `0 ~ 9` 十个数字拼上前面找的两位数，看看平方能不能得到 $321$
4. ...

最后在到第九位的时候，会发现，只有 8 个 **九位数** 满足条件。

```cpp
#include <cstdio>
#include <vector>

using namespace std;

typedef long long INT64;

const INT64 tail = 987654321;

int main()
{
    vector<int> nums[10];

    nums[0].push_back(0);

    vector<int>::iterator it;
    int n;
    for (int i = 1, base = 10; i < 10; ++i, base *= 10)
    {
        for (int d = 0; d < 10; ++d)
            for (it = nums[i - 1].begin(); it != nums[i - 1].end(); ++it)
            {
                n = base / 10 * d + *it;
                if ((INT64)n * n % base == tail % base)
                {
                    printf("%d %lld\n", n, (INT64)n * n);
                    nums[i].push_back(n);
                }
            }
        printf("\n");
    }
}
```



---

## 作者：Deny_小田 (赞：2)

嘿嘿，来抢个板凳。

也没什么难得，直接根据楼下的解释来个打表程序（个人偏爱代表=\_=）

[delete]没什么技术含量，实在不会看注释[/delete]

标程:

```cpp

#include <stdio.h>
#include <math.h>
#define Limit 9

int main(){
    int n,i;
    scanf("%d",&n); 
    if(n <= Limit-1) printf("0"); //不可能末尾为9位数 
    else if(n == 9) printf("8");
    else if(n == 10) printf("72");
    else{
        printf("72");
        int p = n-10;
        for(i = 0; i < p; i++) printf("0");
    }
    
    return 0;
}

```

---

## 作者：critnos (赞：2)

不是我不喜欢c++，是python太简单了

先说点题外话

我们~~黑心的~~zm教练给我们出了一道水题（是真的水），c++或python：

如输入3，输出：
```
     *
    ***
   *****
  *     *
 ***   ***
***** *****
```
如果你是像我一样的c++党，你肯定也会这么想：

**一堆循环搞定！**

如果你懒一些，你肯定会用函数和define：
```cpp
#include<bits/stdc++.h>
#define from for(i=1;i<=n;i++)
using namespace std;
string str(char a,int t)
{
	string c;
	for(int i=0;i<t;i++) c+=a;
	return c;
}
int main()
{
    int n,i;
    cin>>n;
    from cout<<str(' ',2*n-i)<<str('*',i*2-1)<<endl;
    from cout<<str(' ',n-i)<<str('*',i*2-1)<<str(' ',2*(n-i)+1)<<str('*',i*2-1)<<endl;
}
```
但是……在看完python代码后，我惊呆了：
```python
n=int(input())
for i in range(1,n+1):
    print("%s%s"%(' '*(2*n-i),'*'*(i*2-1)))
for i in range(1,n+1):
    print("%s%s%s%s"%(' '*(n-i),'*'*(i*2-1),' '*(2*(n-i)+1),'*'*(i*2-1)))
```
关键出在
```python
' '*(2*n-i)
```
python竟然自带了“str”函数的功能

so……

本题中要打印许多个0，这个功能正好发挥作用

原理dalao们已经解释过了，就直接看代码吧
```python
n=int(input())
print("72"+'0'*(n-10) if(n>9) else 0 if(n<9) else 8)
```
大家一定没有看过python的三目运算符吧
```cpp
a?b:c//c++
```
等于
```python
b if(a) else c#python
```

当然，c++也可以写得很短
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
    cin>>n;
    string a=n>9?"72":n<9?"0":"8";
	if(n>9) 	
		for(int i=10;i<n;i++) a+='0';
    cout<<a;
    return 0;
}
```


---

## 作者：sid_shi1 (赞：0)

[P2368 EXCEEDED WARNING B](https://www.luogu.com.cn/problem/P2368)

这其实是一道数论题。

本题 $n$ 最大 $1000000$ ，用 $string$ 打暴力也许也能过，但是，答案是可以算出来的。

思路：

样例告诉我们, $n\leqslant8$ 时是没有解的。经尝试， $n=9$ 时共有八个解（~~这个貌似算不出来~~），而当 $n>9$ 时，这个数的末九位必须为那些九位数（这样子末尾才能为 $987654321$ ）。 $n=10$ 时，答案有 $8\times9=72$ 个（首位不能为零，有九种情况）； $n=11$ 时，答案有 $72\times10=720$ 个； $n=12$ 时，答案有 $72\times10\times10=7200$ 个，以此类推。

接下来贴代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	scanf("%d",&n);
	if(n<=8) printf("0");
	if(n==9) printf("8");
	if(n>9){
		printf("72");
		for(int i=n;i>=11;i--) printf("0");
	}
	return 0;
}
```




---

## 作者：蒋钦杰jqj (赞：0)

```cpp
var n,i:longint;
begin
readln(n);
if n<9 then writeln(0)
else if n=9 then writeln(8)
else
  begin
  write(72);
  for i:=1 to n-10 do write(0);
  writeln;
  end;
end
```
通过暴力，所求得四种情况：
1、n<=8时，答案始终为0；

2、n=9时，答案为8；

3、n=10时，答案为72；

4、n>10时，答案为72\*10的n-10次方。

因为n在题中比较大，所以先输出72，再依次输出0。

然后……

就AK了。


---

