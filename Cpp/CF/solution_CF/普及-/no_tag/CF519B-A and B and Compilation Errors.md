# A and B and Compilation Errors

## 题目描述

A和B在准备他们的编程比赛。

B十分喜欢调试他的代码，但在他让程序输出结果并开始调试之前，他必须先编译他的代码。

最初，编译器显示了nnn 处编译错误，每一处被描述为一个正整数。经过不懈的努力，B就能够修复一个错误然后再去修复另一个。

然而，尽管事实上B的确修复了两个错误，但他无法准确地记住哪些编译上的错误消失了——B所使用的编译器每次输出的剩下的编译错误的顺序是不定的！B明白，不像其它的编程语言，他编程中的某一个编译错误与其它的错误无关，也就是说，修正了一个错误之后，其它的错误依旧存在，不会被修正。

你能帮助B找出他修正了哪两个错误吗？（只有两个）

## 样例 #1

### 输入

```
5
1 5 8 123 7
123 7 5 1
5 1 7
```

### 输出

```
8
123
```

## 样例 #2

### 输入

```
6
1 4 3 3 5 7
3 7 5 4 3
4 3 7 5
```

### 输出

```
1
3
```

# 题解

## 作者：Uni_Tune (赞：6)

这道题并不难，题目虽然很长，但是意思很简单：给你$n$个数，每次消去一个数后不按原来的顺序输出，一共消去两个数，要你找出这两个数。

本蒟蒻的方法是：记$n$个数的和为$num1$，消去一个数后的和为$num2$,消去两个数后的和为$num3$，输出$num1-num2$和$num2-num3$即可

代码如下：
```cpp
#include<cstdio>
using namespace std;
int n,x,num1,num2,num3;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){//对每次的序列求和
        scanf("%d",&x);
        num1+=x;
    }
    for(int i=1;i<=n-1;i++){
        scanf("%d",&x);
        num2+=x;
    }
    for(int i=1;i<=n-2;i++){
        scanf("%d",&x);
        num3+=x;
    }
    //printf("%d %d %d",num1,num2,num3);调试用，请忽略
    printf("%d\n%d",num1-num2,num2-num3);//输出
    return 0;
}
```

---

## 作者：寒鸽儿 (赞：3)

利用异或的性质  
两个数相等异或和为0  
异或具有交换律  
```cpp
#include <cstdio>
#define ll long long 

using namespace std;

int main() {
	int n;
	scanf("%d", &n);
	ll pre = 0, now = 0;
	int tmp;
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &tmp);
		pre ^= tmp;
	}
	for(int i = n - 1; i > n - 3; --i) {
		for(int j = 1; j <= i; ++j) {
			scanf("%d", &tmp);
			now ^= tmp;
		}
		printf("%lld\n", now ^ pre);
		pre = now; now = 0;
	}
	return 0;
}
```

---

## 作者：LucasXu80 (赞：0)

本题解介绍最最最直接的解法。

三次排序，然后比较排序后的数组。具体来看。

来看一组数据，两个数列分别表示问题解决前后的情况：

3 1 2||1 3

将其进行排序变成：

1 2 3||1 3

然后我们只要一一比对数列中的每一项即可。只要有不同，就可以输出并退出循环。

那么输出哪一个数呢？拿这里举例子：当$i=2$时，上下不同。而我们应该输出的是第一个数列中的那一项，因为去掉的是$2$。想想也能理解，仍然存在的$3$（下面数列的第二项）在数列的后面，循环还没有遍历到呢。

思路不难，较易想到，直接上代码咯~

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n,a[100001],b[100001],c[100001];
    cin>>n;
    for (int i=1; i<=n; i++) cin>>a[i];
    for (int i=1; i<=n-1; i++) cin>>b[i];
    for (int i=1; i<=n-2; i++) cin>>c[i];
    //定义、循环输入，注意i循环到几为止
    sort(a+1,a+n+1);
    sort(b+1,b+n);
    sort(c+1,c+n-1);
    //对三个数组进行暴力排序
    for (int i=1; i<=n; i++)
    {
        if (a[i]!=b[i])
        {
            cout<<a[i]<<endl;//别忘了换行
            break;
        }
    }
    //将a、b数组进行比较，有不同就输出a[i]并退出
    for (int i=1; i<=n-1; i++)
    {
        if (b[i]!=c[i])
        {
            cout<<b[i];
            break;
        }
    }
    //将b、c数组进行比较，有不同就输出b[i]并退出
    return 0;
}
```
希望对大家有帮助！

---

## 作者：Cult_style (赞：0)

#### 题目大意：给你三组数，第一组有n个数，第二组比第一组少一个数，第三组比第二组少一个数，输出第二组失踪了的那个数和第三组失踪的那个数

这道题没什么好说的，不过如果用数组计数的方法来做的话就会超空间，因为a≤10^9,数组开不了这么大，不过我们可以直接算出第一组数的和，减去第二组数的和，就是拿走的第一个数，再用第二组数的和减去第三组数的和就是拿走的第二个数。

记得要开long long ,输出要用lld,不然第一个点就错了

```
#include<bits/stdc++.h>
#define LL long long
using namespace std;
LL n,a;
LL sum1,sum2,sum3;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
    	scanf("%lld",&a);
    	sum1+=a;
    }
    for(int i=1;i<=n-1;i++){
    	scanf("%lld",&a);
    	sum2+=a;
    }
    for(int i=1;i<=n-2;i++){
    	scanf("%lld",&a);
    	sum3+=a;
    }
    printf("%lld\n%lld",sum1-sum2,sum2-sum3);

    return 0;
}
```


---

## 作者：Franka (赞：0)

### **题目**
如翻译。
### **思路**
将第一列所有的数字加起来放在$s1$里；

将第二列所有的数字加起来放在$s2$里；

将第三列所有的数字加起来放在$s3$里；

输出$s1-s2$和$s2-s3$即可。
### **代码**
```pascal
var
 s1,s2,s3,n,i,x:longint;
begin
 readln(n);
 for i:=1 to n do//第一行有n个数
  begin
   read(x);//读入x
   s1:=s1+x;//计算第一行和
  end;
 for i:=1 to n-1 do//第二行有n-1个数
  begin
   read(x);//读入x
   s2:=s2+x;//计算第二行和
  end;
 for i:=1 to n-2 do////第三行有n-2个数
  begin
   read(x);//读入x
   s3:=s3+x;//计算第三行和
  end;
 writeln(s1-s2);writeln(s2-s3);//按题意输出
end.
```


---

