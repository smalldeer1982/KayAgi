# Cifera

## 题目描述

当 Petya 上学时，他对大数以及古代对它们的称呼产生了兴趣。例如，他了解到俄语单词 “tma”（现在意为“多得数不过来”）在古代代表一千，而 “tma tmyschaya”（字面意思是“tma 的 tma”）则代表一百万。

Petya 想要让我们对数字的称呼更加现代化，于是他发明了一个词 petricium，表示数字 $k$。此外，petricium la petricium 表示数字 $k^{2}$，petricium la petricium la petricium 表示 $k^{3}$，以此类推。所有这种形式的数字都被称为 petriciumus cifera，而该数字的重要性就是其名称中 “la” 的数量。

Petya 的发明带来了一个需要迅速解决的问题：某个数字 $l$ 是否属于 petriciumus cifera 集合？由于 Petya 是个非常忙碌的学生，他需要自动化这个过程，于是请你来帮忙解决。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
25
```

### 输出

```
YES
1
```

## 样例 #2

### 输入

```
3
8
```

### 输出

```
NO
```

# 题解

## 作者：RioBlu (赞：8)

# 看来没人比我早了

## 本题可以说是非常简单的

直接用$l$不断的$mod$ $k$ 并$l$÷$k$

看看能否$mod$成功

上代码
```
#include<bits/stdc++.h>
using namespace std;
long long a,b,n;
bool ans=0;
int main()
{
    cin>>a>>b;//输入
    while(b>0)//
    {
        if(b==1)//1就直接退（因为b>=2，所以说明成功了）
        {
            ans=0;//其实没有用
            break;
        }
        if(b%a!=0)//mod出现余数
        {
            ans=1;
            break;
        }
        n++;//去的位数
        b=b/a;//b除a
    }
    if(ans==0)//YES
    {
        cout<<"YES"<<endl;
        cout<<n-1<<endl;//一定要-1
    }
    else//NO
    cout<<"NO"<<endl;
    return 0;
}
```

---

## 作者：Kevin_Zhen (赞：4)

## 暴力解法
设一个变量 $t$，初值为 $k$，每次循环使 $t$ 乘上 $k$，不断上升。  
**边界1：** 如果 $t$ 等于 $l$ 了，输出答案，结束程序即可。  
**边界2：** 如果 $t$ 的值大于 $l$ 了，则没有找到答案，不必继续循环。换言之，循环的判断条件是 $t$ 小于等于 $l$。  
**代码轻微压行，可能引起不适。**
## AC CODE
```cpp
#include <iostream>
#include <cstdio>
using namespace std;

long long k, l, t;

int main() {
	scanf("%lld%lld", &k, &l); t = k;
	for (int i = 1; t <= l; ++i) { if (t == l) { printf("YES\n%d", i - 1); return 0; } t *= k; }
	printf("NO");
	return 0;
}
```
## 感谢观赏！

---

## 作者：DreamShadow (赞：1)

## 咚咚咚，敲黑板，重点来了：
    1.先判断l与k是否为倍数关系，如果不是，说明不论n是几，k就是不会变成l（惊不惊喜，意不意外？气死你）。
    2.用while循环，如果l大于0，那么重复执行下去
    3.判断一：如果l=1，输出"YES"，输出n，走人
    4.判断二：判断l与k是否为倍数关系，如果不是，输出一个大大的"NO"。
    5.累加n：n++
    6.（就不告诉你，你猜啊，想知道么？戳一下下面那个）：
 
# [(≧▽≦)MY BLOG\(≧▽≦)](https://www.luogu.org/blogAdmin/article/index?pageType=list)


     戳完了，那就告诉你：l=l/k；
     

------------

# 代码：
#### （惊不惊喜，意不意外，没有！\\(≧▽≦)/)

    emming
 
#### 还是给个Pascal的吧（好像题解里没有Pascal）：
```pascal
var
  k,l:longint;
  n:longint;
  tamp:qword;
 begin
   readln(k);
   readln(l);
   if l mod k<>0 then
   begin
     writeln('NO');
     halt;
   end;
   while l>0 do
   begin
     if (l=1) then
     begin
       writeln('YES');
       writeln(n-1); 
       halt;
     end;
     if (l mod k<>0) then
     begin
       writeln('NO');
       halt;
     end;
     inc(n);
     l:=l div k;
   end;
 end.

```


------------


---

## 作者：outis_crypt (赞：0)

**补充Python语言的代码**

思路：
直接对n进行循环, n每次+1，直到k^n>=l的时候退出，最后判断是否相等


```python
a,b,n=int(input()),int(input()),1    #输入数据a,b.以及给n赋值
while a**n<b:                     #循环，大于等于b时退出
    n+=1
if a**n==b:                    #是否满足条件
    print("YES"),print(n-1)
else:
    print("NO")
```


---

## 作者：cjZYZtcl (赞：0)

# 只需不停判断余数、商
# so easy
```pascal
var
  k,l,i:int64;
begin
  readln(k);
  read(l);
  while l>0 do
  begin
    if l=1 then begin writeln('YES'); write(i-1); halt; end;
    if l mod k<>0 then begin write('NO'); halt; end;
    l:=l div k;
    inc(i);
  end;
end.
```


---

## 作者：sxtm12138 (赞：0)

  ##  **本题其实并不需要任何复杂的算法，只要按照题意一步一步计算K的乘方就能AC，所以就不过多解释。（没错，就是这么暴力）**
  **以下是代码：**

------------


```cpp
#include<bits/stdc++.h>//暴力的头文件
using namespace std;
long long k,t,l;//t表示K的乘方
int main()
{cin>>k>>l;
 t=k;
 for(int i=1;;i++)//无条件循环计算K^(i+1)
   {if(t==l)//考虑到k=l的情况，先进行判断
      {cout<<"YES"<<endl;
       cout<<i-1;//输出N-1
       break；
      }
    if(t>l)//t>l说明l不是k的正整数次方
      {cout<<"NO";
       break;//暴力收工
      }
    t*=k;//计算乘方
   }
return 0;
}//第三次发题解，有错误请帮忙指出，谢谢！
```

---

## 作者：不到前10不改名 (赞：0)

//这题没什么难度啊！  
//其实这题也可以利用2进制来做，我们都知道在二进制中一个数与它的次方数的关系
```
#include<stdio.h>
int k,l,srx;
int main()
{
    scanf("%d%d",&k,&l);
    while(l%k==0)//暴力模拟去除，本来还想用pow函数的呢~
    {srx++;//次方数增加
    l/=k;}
    if(l==1)//=1的话就说明全部整除，是k的次方
    printf("YES\n%d",srx-1);//n-1别忘，当然cf几乎全大写
    else
    printf("NO");
    return 0;
 } 
```

---

