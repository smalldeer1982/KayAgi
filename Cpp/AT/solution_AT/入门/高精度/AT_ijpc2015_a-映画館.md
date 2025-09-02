# 映画館

## 题目描述

[problemUrl]: https://atcoder.jp/contests/ijpc2015/tasks/ijpc2015_a

 $ N $ 人の人が一列に並んだ $ M $ 個の座席に座っている。

 $ i(1≦i≦N) $ 番目の人の座っている座席の両側ともに少なくとも $ A_i $ 個の空席が**連続して存在する**ことが分かっているとき、 $ M $ の最小値を求めよ。

$ N $ 人の人がこの順番で並んでいるとは限りません。(13:38)

## 说明/提示

### 配点

この問題に部分点はありません。すべてのテストケースに正解すると100点です。

## 样例 #1

### 输入

```
3
2 3 2```

### 输出

```
13```

## 样例 #2

### 输入

```
5
6 6 9 7 4```

### 输出

```
46```

## 样例 #3

### 输入

```
10
10 6 6 10 3 8 8 9 4 2```

### 输出

```
86```

# 题解

## 作者：高雍博 (赞：6)

楼下 $dalao$ 们的公式本蒟蒻似乎看不懂啊~

于是只好自己动手丰衣足食了。

翻译写得令人谔谔，于是这里概括一下题意：

>输入 $n$ 个数，输出最大的一个数以及所有数以及 $n$ 的和。

看懂题意之后我大惊：**这也太水了吧？！**

~~咳咳跑题了。~~

$Python\ 3$ :

```python
n=int(input())
ans=0
maxa=0                #初始化
while n>=1:           #n次
    a=input()         #输入
    ans+=a            #加和
    if maxa<=a:       #手写max
        maxa=a
    n-=1
print(n+maxa+ans)     #求和，输出
```

$C$:
```c
#include<stdio.h>
using namespace std; 
int main()
{
    unsigned long long n,a,ans=0,maxa=0;//要用ull，因为最大可以取到1000000000
    scanf("%llu",&n);
    for(register long long int i=0;i<n;i++)
    {
        scanf("%llu",&a);//每次输入1个p
        ans+=a;//累加每个输入的p
        if(maxa<=a)
        {
            maxa=a;//判断之前最大的数是否比maxa小，如果是，则把maxa记录作为最大数
        }
    }
    unsigned long long sum=l+q+n;//记得unsigned long long
    printf("%llu\n",sum);;//AT不换行，抱灵两行泪
    return 0;//完美结束
}
```

$C++$: 
##### (注释同 $C$)
```cpp
#include<bits/stdc++.h>
using namespace std;
unsigned long long n,a,ans,maxa,sum;
int main()
{
    cin>>n;
    for(register long long int i=1;i<=n;++i)
    {
        cin>>a;
        ans+=a;
        if(maxa<=a)
        {
            maxa=a;
        }
    }
    sum=maxa+n+ans;
    cout<<sum<<endl;
    return 0;
}
```

##### 求过！求赞！（超小声）

---

## 作者：Jinyeke (赞：2)

### 解法：输出n+a数组的和+a数组最大的那个数
#### 因此代码（pascal）如下
```pascal
var
a:array[1..100000] of longint;
i,j,n,max,s:qword;//注意！一定要用qwrod，不然可能会爆（不过qword没有负数）！
begin
readln(n);
for i:=1 to n do 
 begin
  read(a[i]);//输入a[i]
  s:=s+a[i];//s加上每一个数
  if a[i]>max then max:=a[i];//打擂台找最大的数
 end;
 writeln(s+n+max);//最后结果加上n和最大数（一定要换行！）
 end.
```
### 共建文明洛谷，请勿Ctrl+C！


---

## 作者：liuyifan (赞：1)

题意:输入一个数字n(1<=n<=100000)

接下来输入n个数字( 1<=a[i]<=10^9) 

输出

[![PHYxiT.png](https://s1.ax1x.com/2018/08/25/PHYxiT.png)](https://imgchr.com/i/PHYxiT)的值

这道题看似数据很大要用高精度，实际一个unsigned long long就能解决（unsigned long long 最大值18446744073709551615，但不能有负数)

~~暴力计算~~直接求和即可。

code:
```cpp
#include<bits/stdc++.h>
#define ll unsigned long long
#define reg register//define的格式为#define A B 将代码中所有A替换为B
using namespace std;
ll n,sum,maxx=0,tmp;//因为是正整数所以maxx初始为0
int main()
{
	scanf("%lld",&n)
	for(reg ll i=1;i<=n;i++)
	{
		scanf("%lld",&tmp);
		sum+=tmp;//不需要开数组，直接累加
		maxx=max(tmp,maxx)
	}
	printf("%lld\n",n+sum+max)
}
```

---

## 作者：黄昏烟雨乱WA声 (赞：0)

这道题dalao们推出的公式看起来很深奥

但是……

实际上~~很简单~~

意思就是输入一个长度为n的字符串，输出字符串中最大的数与所有数还有n的和

要排序吗？

## ~~不需要~~

因为只要求输出和，所以连字符串都不用声明，直接找出最大的数然后在输入的过程中把数加起来就好了嘛

上代码：
```cpp
#include <iostream>
#include <bits/stdc++.h>
using namespace std; 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	unsigned long long n,p,q=0,l=0;//要用unsigned long long，因为最大可以取到1000000000
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>p;//输入n个p
		q+=p;//累加每个输入的p
		if(p>=l){
			l=p;//判断之前最大的数是否比p小，如果是，则把p记录作为最大数
		}
	}
	unsigned long long c=l+q+n;//c也要unsigned long long
	cout<<c<<"\n";//莫忘换行
	return 0;//快乐的结束
}
```




---

## 作者：LiveZoom (赞：0)

[博客食用效果更佳](https://www.luogu.com.cn/blog/lza/solution-at1519)
# 题解 AT1519 【映画館】
此题是道纯模拟题，但是得先推出公式，我在此不推了，公式是：
$$n+\sum_{i=1}^{n}{a_{i}}+\max(a_{i})$$
- max函数

这个函数，我用了个模板来写的

```cpp
template<class T>T max(T x,T y){//template表示的是模板，T表示一个数据类型，当然，T可以为任意类型
	if(x>y)return x;//若x比y大，输出x
	return y;//否则，输出y
}
```

- 主函数
此题数据很大，又没有负数，则用unsigned long long最好

```cpp
int main()
{
	int n;
	unsigned long long a,maxn,sum;//定义
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%llu",&a);//中间要用%llu哦
		maxn=max(maxn,a);//取最大值
		sum+=a;//取和
	}
	printf("%llu\n",n+maxn+sum);//输出，注意，AT不换行，暴零两行泪
    return 0;
}
```

串起来：

```cpp
#include<stdio.h>
using namespace std;
int n;
unsigned long long a,maxn,sum;
template<class T>T max(T x,T y){
	if(x>y)return x;
	return y;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%llu",&a);
		maxn=max(maxn,a);
		sum+=a;
	}
	printf("%llu\n",n+maxn+sum);
    return 0;
}
```

求通过
# The end

---

## 作者：不到前10不改名 (赞：0)

//又是我,希望能过，已经加了防伪标识和改动了，泥萌别抄袭
```
#include<stdio.h>
unsigned long long n,lhy,srx,sry,i;//防伪标识已加入
unsigned long long max(unsigned long long x,unsigned long long y)
{
    if(x>y)
    return x;
    return y;//else就省略了
}//一开始虽然注意数据了,但却只开longlong,本来都打算开高精了,却发现只是加一个unsigned~
int main()
{
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {scanf("%d",&sry);
    lhy+=sry;
    srx=max(srx,sry);}//纯c党的悲哀，什么函数都要手打
    printf("%lld\n",n+lhy+srx);//你猜什么意思？我是不会告诉泥萌是n+max值+总和的~
}
```

---

