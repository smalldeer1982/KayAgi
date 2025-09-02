# Exam

## 题目描述

An exam for $ n $ students will take place in a long and narrow room, so the students will sit in a line in some order. The teacher suspects that students with adjacent numbers ( $ i $ and $ i+1 $ ) always studied side by side and became friends and if they take an exam sitting next to each other, they will help each other for sure.

Your task is to choose the maximum number of students and make such an arrangement of students in the room that no two students with adjacent numbers sit side by side.

## 样例 #1

### 输入

```
6```

### 输出

```
6
1 5 3 6 2 4```

## 样例 #2

### 输入

```
3
```

### 输出

```
2
1 3```

# 题解

## 作者：Aw顿顿 (赞：7)

写这篇题解的时候，由于提交的次数比较多，所以会比较详细。

**本题带有 spj，所以答案不一定和样例一样！**

首先，把题意化简为：

- 给定一个正整数 $n$，有一个序列由 $1\sim n$ 组成。

- 这个序列的任意相邻两项差都不为 $1$。

一开始想到的办法是：随机打乱，判断。

但是这种方法不仅不靠谱，而且很容易超时各种奇怪的错误，所以，我们可以考虑一种简答的方式：

- 先输出奇数。

- 再输出偶数。

这时候，就不会有问题了，在差到达一定大小的情况下，奇数和偶数会分开。

那么，我们就要考虑，哪些情况需要特判呢？

首先是 $n\le 2$ 的情况，这种情况仅有一种办法：

$$\rm Total:1\ ,\ Num\ :\ 1$$


此时仅有一种情况了

接着就是样例的情况：

$$\rm Total:2\ ,\ Num\ :1,3$$

接着我们就到了一个十分重要的地方：$4$。

乍一看似乎只有 $\rm Total:3\ ,\ Num\ :1,4,2$ 的情况，但是，请注意，**开头不一定是 $1$!**

所以，在 $4$ 的情况下，数列为 $3,1,4,2$。

此外，我们再来证明一下，对于任何大于 $4$ 的 $n$ ，都能保证奇数偶数岔开。

若 $n$ 为偶数，其最大奇数为 $n-1$。

$$\because\ n>4$$

$$\therefore\ n-1>3$$

$$\therefore\ n-1>2+1$$

所以必然岔开。

若 $n$ 为奇数，则：

$$\because\ n>4$$

$$\therefore\ n>2+1$$

故必然岔开。

据此，证毕， $\rm Q.E.D$

然后我们就可以程序实现了：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
    cin>>n;
    if(n<=2){
        puts("1\n1");
        return 0;
    }
    if(n==3){
        puts("2\n1 3");
        return 0;
    }
    if(n==4){
        puts("4\n3 1 4 2");
        return 0;
    }
    cout<<n<<endl;
    for(int i=1;i<=n;i+=2)cout<<i<<' ';
    for(int i=2;i<=n;i+=2)cout<<i<<' ';
    return 0;
}
```

此时所有的内容均已讲解完毕，谢谢阅读，欢迎使用代码对拍/理解/查找错误。



---

## 作者：LucasXu80 (赞：2)

这题是典型的CF签到题，不难但很坑。这里提供PY代码。

如果你的数感不错，你就知道在绝大多数情况下一定是可以安排的。只要奇偶错开就可以了。比如输入$6$，我们可以输出$1,3,5,2,4,6$，这样就满足题意了。

当然样例告诉我们要特判$3$，因为$1,3,2$是不满足题意的，其他也没有满足题意的排列方式。

再来，显然$2$也是要特判的，因为$1,2$显然不满足题意，因此只能安排一个学生。

到这里代码就很简单了。

```python
n=int(input())
if n==2: 
    print(1)
    print(1)
elif n==3:
    print(2)
    print("1 3")
#两个特判
else:
    print(n)#先输出n
    for i in range(1,n+1,2): print(i,end=' ')#依次输出所有奇数
    for i in range(2,n+1,2): print(i,end=' ')#依次输出所有偶数
    #注意范围要n+1，否则就会少一个
```
好了，这篇题解就到......

### 什么，WA了？？？

想想也是，当$n=4$时，输出应该会是$1,3,2,4$，而$3-2=1$......

所以，$4$也要特判，手写一组就可以了。

在代码里插入这么一段就AC了：

```python
elif n==4:
    print(4)
    print("2 4 1 3")
```
好啦，希望大家喜欢，求赞~

---

## 作者：shenmadongdong (赞：1)

这道题只需分类讨论加找规律即可

代码：
```
var n,i:longint;
begin
  read(n);
  if (n=1)or(n=2) then begin writeln('1'); writeln('1'); end;//特判
  if (n=3) then begin writeln('2'); writeln('1 3'); end;//特判
  if (n=4) then begin writeln('4'); writeln('2 4 1 3'); end;//特判
  if (n=5) then begin writeln('5'); writeln('1 4 2 5 3'); end;//特判
  if (n>5) then begin
  writeln(n);
  for i:=1 to n div 2 do begin write(i+n div 2,' '); write(i,' '); end;
  if n mod 2=1 then write(n);
  end;//找规律发现如此
end.
```

---

## 作者：Snow_Dreams (赞：0)

这道题就是一个典型的递归&找规律

首先，我们要特判1,2,3,4的情况，因为当只有4个人的时候，无法按通解来写

接着，我们就需要用贪心&分治的思路

### 注意：以下内容不包括n∈{1,2,3,4}

1. 如果n为偶数

不难发现，一定可以把所以学生选出来

又因为：
If there are several possible answers, output any of them.

所以就可以直接输出n和所以在n范围内的奇数，接着输出在n范围内的偶数

2. 如果n为奇数

此时，也一定有n个学生可贵挑选，此时的奇数比偶数要多一个，所以我们也要像1一样输出n和所以在n范围内的奇数，接着输出在n范围内的偶数

最后，还有注意输出的时候**一定**要按一定顺序，否则极有可能会出现两编号相邻的情况

~~还是赞美一下良心样例，要不是样例我根本没发现要特判1,2,3,4~~

---

## 作者：RainFestival (赞：0)

打表好！！！

这道题用打表+找规律

当n=1,2,3时 需要特判

n>=4 时 先按照从大到小的顺序输出所有奇数，再按照从大到小输出所有偶数（反正只用输出一种排列，最好输出程序实现起来简单的嘛，这是贪心！！！）

代码？？？

```pascal
var
  i,n:longint;
begin
  readln(n);
  if (n=1) then
    begin
      writeln(1);
      writeln(1);
      halt;
    end;
  if (n=2) then
    begin
      writeln(1);
      writeln(1);
      halt;
    end;
  if (n=3) then
    begin
      writeln(2);
      writeln(1,' ',3);
      halt;
    end;
  writeln(n);
  for i:=n downto 1 do
    if (i mod 2=1) then write(i,' ');
  for i:=n downto 3 do
    if (i mod 2=0) then write(i,' ');
  writeln(2);
end.
```

---

## 作者：LittleSnowy (赞：0)

这题其实不难（反正不是输出所有排法）

我们发现n为1或2时只可能有一个

n为3时只可能有2个

n>=4时  若为偶数  按照i+n/2，i  的顺序输出

可以证明相邻两数要么差n/2（>1），要么差n/2+1

若为奇数  将1~n-1按偶数情况输出，在最后补上n

上代码：
```cpp
#include<stdio.h>
using namespace std;
int main()
{
	int n;
	scanf("%d",&n);
	if(n<=2)printf("1\n1");
	if(n==3)printf("2\n1 3");
	if(n>3)
	{
		printf("%d\n",n);
		for(int i=1;i<=n/2;i++)printf("%d %d ",i+n/2,i);
		if(n%2==1)printf("%d",n);
	}
return 0;
}
```

---

