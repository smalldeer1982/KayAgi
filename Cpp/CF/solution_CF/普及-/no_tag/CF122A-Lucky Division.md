# Lucky Division

## 样例 #1

### 输入

```
47
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
16
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
78
```

### 输出

```
NO
```

# 题解

## 作者：Siyuan (赞：1)

读入后判断一遍即可：

1. 能被幸运数字整除。
2. 仅包含幸运数字。

```
#include<cstdio>
using namespace std;

int main()
{
    int n;
    scanf("%d",&n);
    if(n%4==0||n%7==0||n%74==0||n%47==0||n%44==0||n%77==0)
    //能被幸运数字整除（77以上的数字不需要判断了）
        return printf("YES"),0;
    while(n!=0)
    {
        register int t=n%10;
        if(t!=4&&t!=7)  return printf("NO"),0;
        n/=10;
    }
    return printf("YES"),0;
}
```

---

## 作者：Franka (赞：1)

### **题目**
幸运数字表示只含有4或7的数字。

读入一个$n$，如果$n$是幸运数字的倍数，则输出$YES$，否则输出$NO$。
### **思路**
因为这里$n$给的很小，所以可以吧$1$~$1000$内的幸运数全都列出来，然后一一看是不是倍数就行了。
### **代码**
```pascal
var
 a:array[1..11] of longint=(4,7,47,74,447,474,477,744,747,774,777);//1~1000范围内的幸运数
 n,i:longint;//定义n和i
 p:boolean;//定义p
begin
 readln(n);//读入n
 p:=false;//反证法
 for i:=1 to 11 do if n mod a[i]=0 then p:=true;//看看是不是倍数
 if p then writeln('YES')//如果是，则输出YES
  else writeln('NO');//否则输出NO
end.
```
#### 提交后AC的我当然又想到了一种方法：打表。
将原来AC的程序稍微改了改，如下：
```pascal
var
 a:array[1..11] of longint=(4,7,47,74,447,474,477,744,747,774,777);
 i,j:longint;
 p:boolean;
begin
 assign(output,'x.out');rewrite(output);
 for j:=1 to 1000 do
  begin
   p:=false;
   for i:=1 to 11 do if j mod a[i]=0 then p:=true;
   write('''');//输出'
   if p then write('YES')
        else write('NO');
   write('''');
   write(',');
  end;
 close(output);
end.
```
双击运行x.exe，将最后的,改成);，前面加一个(，一个打表程序就出来了：
```pascal
var
  a:array[1..1000] of string=('NO','NO','NO','YES','NO','NO','YES','YES','NO','NO','NO','YES','NO','YES','NO','YES','NO','NO','NO','YES','YES','NO','NO','YES','NO','NO','NO','YES','NO','NO','NO','YES','NO','NO','YES','YES','NO','NO','NO','YES','NO','YES','NO','YES','NO','NO','YES','YES','YES','NO','NO','YES','NO','NO','NO','YES','NO','NO','NO','YES','NO','NO','YES','YES','NO','NO','NO','YES','NO','YES','NO','YES','NO','YES','NO','YES','YES','NO','NO','YES','NO','NO','NO','YES','NO','NO','NO','YES','NO','NO','YES','YES','NO','YES','NO','YES','NO','YES','NO','YES','NO','NO','NO','YES','YES','NO','NO','YES','NO','NO','NO','YES','NO','NO','NO','YES','NO','NO','YES','YES','NO','NO','NO','YES','NO','YES','NO','YES','NO','NO','NO','YES','YES','NO','NO','YES','NO','NO','NO','YES','YES','NO','NO','YES','NO','NO','YES','YES','NO','NO','NO','YES','NO','YES','NO','YES','NO','NO','NO','YES','YES','NO','NO','YES','NO','NO','NO','YES','NO','NO','NO','YES','NO','NO','YES','YES','NO','NO','NO','YES','NO','YES','NO','YES','NO','NO','NO','YES','YES','NO','NO','YES','NO','NO','NO','YES','NO','NO','NO','YES','NO','NO','YES','YES','NO','NO','NO','YES','NO','YES','NO','YES','NO','NO','NO','YES','YES','NO','NO','YES','NO','YES','NO','YES','NO','NO','NO','YES','NO','NO','YES','YES','NO','NO','YES','YES','NO','YES','NO','YES','NO','NO','NO','YES','YES','NO','NO','YES','NO','NO','NO','YES','NO','NO','NO','YES','NO','NO','YES','YES','NO','NO','NO','YES','NO','YES','NO','YES','NO','NO','NO','YES','YES','NO','NO','YES','NO','NO','NO','YES','NO','YES','NO','YES','NO','NO','YES','YES','NO','NO','NO','YES','NO','YES','NO','YES','NO','NO','NO','YES','YES','NO','NO','YES','NO','NO','NO','YES','NO','NO','NO','YES','NO','NO','YES','YES','NO','NO','NO','YES','NO','YES','NO','YES','NO','NO','NO','YES','YES','NO','NO','YES','NO','NO','NO','YES','NO','NO','NO','YES','NO','NO','YES','YES','NO','NO','NO','YES','NO','YES','NO','YES','NO','NO','NO','YES','YES','NO','NO','YES','NO','NO','NO','YES','NO','NO','NO','YES','NO','YES','YES','YES','NO','NO','NO','YES','NO','YES','NO','YES','NO','NO','NO','YES','YES','NO','NO','YES','NO','NO','NO','YES','NO','NO','NO','YES','NO','NO','YES','YES','NO','NO','NO','YES','NO','YES','NO','YES','NO','NO','NO','YES','YES','NO','NO','YES','NO','NO','NO','YES','NO','NO','YES','YES','NO','NO','YES','YES','NO','NO','NO','YES','NO','YES','NO','YES','NO','NO','NO','YES','YES','NO','NO','YES','NO','NO','YES','YES','NO','NO','NO','YES','NO','NO','YES','YES','NO','NO','NO','YES','NO','YES','NO','YES','NO','NO','NO','YES','YES','YES','NO','YES','NO','YES','NO','YES','YES','NO','NO','YES','NO','NO','YES','YES','NO','NO','NO','YES','NO','YES','NO','YES','NO','NO','NO','YES','YES','NO','NO','YES','NO','NO','NO','YES','NO','NO','NO','YES','NO','NO','YES','YES','NO','NO','NO','YES','YES','YES','NO','YES','NO','NO','NO','YES','YES','NO','NO','YES','NO','NO','NO','YES','NO','NO','NO','YES','NO','NO','YES','YES','NO','NO','NO','YES','NO','YES','NO','YES','NO','NO','NO','YES','YES','NO','NO','YES','NO','NO','NO','YES','NO','NO','NO','YES','NO','NO','YES','YES','NO','NO','NO','YES','NO','YES','NO','YES','NO','NO','NO','YES','YES','NO','NO','YES','NO','NO','NO','YES','NO','NO','NO','YES','NO','NO','YES','YES','NO','NO','NO','YES','NO','YES','NO','YES','NO','NO','NO','YES','YES','NO','YES','YES','NO','NO','NO','YES','NO','NO','NO','YES','NO','NO','YES','YES','NO','NO','NO','YES','NO','YES','NO','YES','NO','NO','NO','YES','YES','NO','NO','YES','NO','NO','NO','YES','NO','NO','NO','YES','NO','NO','YES','YES','NO','NO','NO','YES','NO','YES','NO','YES','NO','NO','NO','YES','YES','YES','NO','YES','NO','NO','NO','YES','NO','NO','NO','YES','NO','NO','YES','YES','NO','NO','NO','YES','NO','YES','NO','YES','NO','NO','NO','YES','YES','NO','NO','YES','NO','NO','NO','YES','NO','NO','NO','YES','YES','NO','YES','YES','NO','NO','NO','YES','NO','YES','NO','YES','NO','NO','NO','YES','YES','NO','NO','YES','NO','NO','NO','YES','NO','NO','NO','YES','NO','NO','YES','YES','NO','NO','NO','YES','NO','YES','NO','YES','NO','NO','YES','YES','YES','NO','NO','YES','NO','NO','NO','YES','NO','NO','NO','YES','NO','NO','YES','YES','NO','NO','NO','YES','NO','YES','NO','YES','NO','YES','NO','YES','YES','NO','NO','YES','NO','NO','NO','YES','NO','NO','NO','YES','NO','NO','YES','YES','NO','NO','NO','YES','NO','YES','YES','YES','NO','NO','NO','YES','YES','NO','NO','YES','NO','NO','NO','YES','NO','YES','NO','YES','NO','NO','YES','YES','NO','NO','NO','YES','NO','YES','NO','YES','NO','NO','NO','YES','YES','NO','NO','YES','NO','NO','NO','YES','NO','NO','NO','YES','NO','YES','YES','YES','NO','NO','NO','YES','NO','YES','NO','YES','NO','NO','NO','YES','YES','NO','NO','YES','NO','NO','NO','YES','NO','NO','NO','YES','NO','NO','YES','YES','NO','NO','NO','YES','NO','YES','NO','YES','NO','NO','NO','YES','YES','NO','NO','YES','YES','YES','NO','YES','NO','NO','NO','YES','NO','NO','YES','YES','NO','NO','NO','YES','NO','YES','NO','YES','NO','NO','NO','YES','YES','NO','NO','YES','NO','NO','NO','YES','NO','NO','NO','YES','NO','NO','YES','YES','NO','NO','NO','YES','NO','YES','NO','YES','NO','NO','NO','YES','YES','NO','NO','YES','NO','NO','NO','YES','NO','YES','NO','YES','NO','NO','YES','YES','NO','YES','NO','YES','NO','YES','NO','YES','NO','NO','NO','YES','YES','NO','NO','YES','NO','NO','NO','YES','NO','NO','NO','YES','NO','NO','YES','YES','NO','NO','NO','YES','NO','YES','NO','YES','NO','NO','NO','YES');//表
  n:longint;//定义n
begin
  readln(n);//读入n
  writeln(a[n]);//输出
end.//完美结束AoA
```
## THE END

---

## 作者：TCZN (赞：1)

~~居然没有P党题解，先水一发再说~~

这题数据水，所以（咳咳）

在1000以内，我们直接推算出这几个幸运数字即可：4,7,44,77,47,74,444,777,477,747,774,744,474,
447

上代码
```pascal
var
  a:longint;
begin
 read(a);
  if (a mod 4=0) or (a mod 7=0) or (a mod 44=0) or (a mod 47=0) or (a mod 74=0) or (a mod 77=0) or (a mod 444=0) or (a mod 447=0) or (a mod 474=0) or (a mod 477=0) or (a mod 744=0) or (a mod 747=0) or (a mod 774=0) or (a mod 777=0)  //枚举每一个（暂时没试过直接打表，应该也可以吧）
   then 
    writeln('YES')
     else writeln('NO');
end.
```


---

## 作者：yuzhechuan (赞：1)

```cpp
#include<bits/stdc++.h>//万能库
using namespace std;
int x;//定义一个变量
bool check(int x)//判断是否为幸运数
{
    while(x>0)
    {
        if(x%10!=4&&x%10!=7)//求该数个数位上的数
            return 0;
        x/=10;//取下一位
    }
    return 1;
}
bool f(int x)//判断是否为接近幸运数
{
    for(int i=x;i>=1;i--)//枚举该数的因数
		if(x%i==0&&check(i))return 1;//如果i为x的因数且是个幸运数则返回真
    return 0;//否则返回假
}

int main()
{
	ios::sync_with_stdio(false);//输入输出加速
	cin.tie(0);
    cin>>x;
    if(check(x)||f(x))cout<<"YES";//如果满足条件则输出YES
    else cout<<"NO";//否则输出NO
}
```


------------

 有点心急了，所以有些优化没做到位，还请见谅

---

## 作者：林家三少 (赞：0)

题目描述：

$Petya$喜欢数字，他将$4$和$7$视为幸运数字。如果一个数**能由$4$与$7$组成**，他就是幸运数字，只要**能被幸运数字整除**的也算幸运数字！现给定一个数字，判断它是否是幸运数。

我们可以知道输出$YES$的有两种情况：

- 能由$4$与$7$组成
- 能被幸运数字整除

然后康康范围$n≤1000$，然后我们就可以先把$1000$以内的由$4$与$7$组成数字列出来：$4,7,44,77,47,74,444,777,477,747,774,744,474,447$，再把$1000$以内的能被幸运数字整除的数字求出来，就用下面整个东东：

```cpp
int a[1000]={4,7,44,77,47,74,444,777,477,747,774,744,474,447};
//1000以内由4和7组成的数字
int shu[1000+10];
int m=14;
//他们一共有14个
for(int i=1;i<=1000;i++){
    	for(int j=0;j<m;j++){
        	if(n==a[j]||n%a[j]==0){
            //如果能被整除就记下来
                a[m++]=n;
                shu[i]=1;
                break;
            }
        }
    }
```

然后再输出、判断就可以了，

### $Code:$

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm> 
using namespace std ;  
int a[1000]={4,7,44,77,47,74,444,777,477,747,774,744,474,447};
int shu[1000+10];
int m=14;
int n;
void Lucky_Division(){
	for(int i=1;i<=1000;i++){
    	for(int j=0;j<m;j++){
        	if(n==a[j]||n%a[j]==0){
                a[m++]=n;
                shu[i]=1;
                break;
            }
        }
    }
}
int main(){
    cin>>n;
    Lucky_Division();
    if(shu[n]==1)
        printf("YES\n");
    else printf("NO\n");
    return 0;
}  
```


---

## 作者：两年打铁 (赞：0)

题意是只要这个数是由4和7组成的幸运数；或者是幸运数的倍数。
所以在~~1000以内也没几个~~
直接可以得到，检查这个数能不能被这些数整除就行了。


------------
```
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d,e,i,j,k,x;
int main()
{
    scanf("%d",&a);
    if(a%4==0||a%7==0||a%44==0||a%47==0||a%74==0||a%77==0||a%444==0||a%447==0||a%474==0||a%477==0||a%744==0||a%747==0||a%774==0||a%777==0)
    printf("YES\n");//上面的几个数字可以直接找出来。
    else printf("NO\n");
        
}
```


------------
附上找幸运数字的代码。

```
#include<bits/stdc++.h>
using namespace std;
int x,i,b,a;

int main()
{
	for(i=1;i<=1000;++i)
	{
		b=0;
		x=i;
		while(x>0)
		{
			if(x%10!=4&&x%10!=7)
			{
				b--;
				break;
			}
			x=x/10;
		}
		if(b==0)printf("%d\n",i);	
	}
}
```

---

