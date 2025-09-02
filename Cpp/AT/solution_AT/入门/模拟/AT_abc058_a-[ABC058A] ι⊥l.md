# [ABC058A] ι⊥l

## 题目描述

有 $3$ 根柱子等间隔排列。柱子的高度从左到右依次为 $a$ 米、$b$ 米、$c$ 米。当柱子的顶端在同一直线上排列时，即满足 $b-a = c-b$ 时，我们称这种柱子的排列方式为“美丽的”。

请判断柱子的排列方式是否美丽。

## 说明/提示

## 限制

- $1 \leq a, b, c \leq 100$
- $a, b, c$ 均为整数。

## 样例解释 1

由于 $4-2 = 6-4$，因此这种柱子的排列方式是美丽的。

## 样例解释 2

由于 $5-2 \neq 6-5$，因此这种柱子的排列方式不是美丽的。

## 样例解释 3

由于 $1-2 = 2-3$，因此这种柱子的排列方式是美丽的。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 4 6```

### 输出

```
YES```

## 样例 #2

### 输入

```
2 5 6```

### 输出

```
NO```

## 样例 #3

### 输入

```
3 2 1```

### 输出

```
YES```

# 题解

## 作者：qwq自动机 (赞：1)

突然发现[本题](https://www.luogu.org/problem/AT2391)好像还没有多语言题解。

那我就~~水~~来一发吧。

### 题目大意：

输入3个整数$A$、$B$、$C$，判断$B-A$是否等于$C-B$

~~新手大福利~~ ~~大水题~~

不说话，直接上代码

伪代码
```vb
定义 A, B, C 为整数
INPUT A, B, C
IF B - A = C - B THEN
	PRINT "YES"
	换行
ELSE
	PRINT "NO"
	换行
END IF
结束
```
~~C艹~~ C++
```cpp
#include <iostream>
using namespace std;
int a, b, c;
int main() {
	cin >> a >> b >> c;
	if (b - a == c - b)
		puts("YES");
	else
		puts("NO);
	return 0;
}
```
C
```cpp
#include <stdio.h>
int main()
{
	int a, b, c;
	scanf("%d%d%d", &a, &b, &c);
	if (b - a == c - b) printf("YES\n");
	else printf("NO\n");
	return 0;
}
```
~~C++++~~ C#
```cs
using System;
public class APlusB
{
    private static void Main()
	{
        string[] input = Console.ReadLine().Split(' ');
        int a = int.Parse(input[0]), b = int.Parse(input[1]), c = int.Parse(input[2]);
        if (b - a == c - b)
        {
        	Console.WriteLine("YES\n");
		}
		else
		{
			Console.WriteLine("NO\n");
		}
    }
}
```
~~咖啡 8~~Java 8
```java
import java.util.Scanner;
public class Main {
	public static void main() {
		Scanner sc = new Scanner(System.in);
		int a, b, c;
		a = sc.nextInt();
		b = sc.nextInt();
		c = sc.nextInt();
		if (b - a == c - b)
			System.out.println("YES");
		else
			System.out.println("NO");
	}
}
```
~~远古语言~~ Pascal
```pascal
var a, b, c of integer;
Begin
	read(a, b, c);
	if a - b = c - b then writeln("YES");
	else writeln("NO");
End.
```

~~PY交易~~ Python
```python
str = input().split()
a = int(str[0])
b = int(str[1])
c = int(str[2])
if a - b == c - b:
	print("YES", end = "\n")
else:
	print("NO", end = "\n")
```
~~宝石~~ Ruby
```ruby
a, b, c = gets.split.map(&to_i)
if b - a == c -b
	puts "YES\n"
else
	puts "NO\n"
```
~~世界上最好的语言~~ PHP
```php
<?php
$input = trim(file_get_contents("php://stdin"));
list($a, $b, $c) = explode(' ', $input);
if ($b - $a == $c -  $b)
	echo "YES\n";
else
	echo "NO\n";
```
**其余语言持续更新**

### 最后，做AT的时候输出一定要换行！

---

## 作者：不到前10不改名 (赞：1)

```
//话说这么简单一题我还用这么麻烦的做法是不是误导新人？
#include<stdio.h>
#include<string.h>
int a[4];
void abcd(int l,int r)//手写快排函数，详见我at2823的快排题解
{
    int i=l,j=r,t;
    int p=a[(l+r)/2];
    while(i<=j)
    {while(a[i]<p)
    {i++;}
    while(a[j]>p)
    {j--;}
    if(i<=j)
    {t=a[i]; 
    a[i]=a[j]; 
    a[j]=t;
    i++; 
    j--;}}
    if(l<j)
    abcd(l,j);
    if(i<r)
    abcd(i,r); 
    }
int main()
{
    scanf("%d%d%d",&a[1],&a[2],&a[3]);
    abcd(1,3);
    if(a[2]-a[1]==a[3]-a[2])
    printf("YES\n");//又是大写加回车，老是换大小写，首字母，全小，全大，真是的~
    else
    printf("NO\n");
    return 0;
}
```

---

## 作者：CZQ_King (赞：1)

## 此题只需按照题意模拟即可。
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
int a,b,c;
int main(){
    cin>>a>>b>>c;
    if(a-b==b-c)cout<<"YES";//如果符合条件
    else cout<<"NO";//否则
    cout<<endl;//别忘了回车
    return 0;//完美结束
}
```
###### ~~最少字的题解QWQ~~

---

## 作者：Aw顿顿 (赞：0)

非常有问题的一道题

注意endl

然后上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c;
int main()
{
    cin>>a>>b>>c;
    if(a-b==b-c)
	{
		cout<<"YES"<<endl;
		return 0;
	}
	cout<<"NO"<<endl;
    return 0;
}
```
~~~
AT的题目如果不换行
…………
~~~
你就~~SPFA~~了
### 换行！！！！！

---

## 作者：可爱的小白 (赞：0)

解题思路：判断B-A=C-B是否成立，若成立，则输出YES,否则输出NO
不多说废话，直接上代码
```cpp
#include<bits/stdc++.h>//万能头文件，应该都知道，特地讲一讲，补充知识 
using namespace std;//这个谁都知道了 
int a,b,c;//定义三个正整数，a和b和c 
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>a>>b>>c;//输入这三个正整数 
	if(a-b==b-c)  cout<<"YES"<<endl;//判断B-A=C-B是否成立，若成立，则输出YES 
	else    cout<<"NO"<<endl;//否则输出NO 

	return 0;//完美结束 
}
```


---

## 作者：Eason6 (赞：0)



------------
没错，蒟蒻题解终于到第五篇了！！(ﾉﾟ▽ﾟ)ﾉ

------------
这道题不需多讲，看到题目立刻振奋：纯公式，只需套即可，此不为蒟蒻之福利乎？只需判断差是否相等即可，好了，上代码：
```
#include<bits/stdc++.h>//万能头文件 
using namespace std;//命名空间 
long long int a;
long long int b;
long long int c;//定义习惯开long long 
int main(){//主函数 
	cin>>a>>b>>c;//输入不多说 
	if(b-a==c-b){//判断是否相等（套公式） 
		cout<<"YES"<<endl;//是则直接输出
		return 0;//节约时间？？ 
	}
	else{//如不是则输出NO 
		cout<<"NO"<<endl;//输出NO 
		return 0;//节约时间... 
	}
	return 0;//其实不用打了，习惯打着 
}
```
再次强调：
#### AT的题输出要打ENDL！！！

---

## 作者：封禁用户 (赞：0)

这一题有两种做法，真的不明白为什么还要排序？

1.直接前后相减取绝对值
```
var
  a,b,c:longint;
begin
  readln(a,b,c);
  if (abs(a-b)=abs(b-c)) then writeln('YES')
    else writeln('NO');
end.

```
2.首加尾和中间X2相比(自行理解)；

```
var
  a,b,c:longint;
begin
  readln(a,b,c);
  if ((a+c)=(b*2)) then writeln('YES')
    else writeln('NO');
end.
```

---

## 作者：ztz11 (赞：0)

# 水！水！水！
### 输入三个数，排一下序，然后求后一个数和前一个数的差
### 相等即YES，反之NO；
**代码：**
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int a[5],b,c;
int main()
{
	cin>>a[1]>>a[2]>>a[3];
	sort(a+1,a+4);
	if(a[2]-a[1]==a[3]-a[2])
	{
		cout<<"YES"<<endl;
	}
	else
	{
		cout<<"NO"<<endl;
	}
}
```

---

