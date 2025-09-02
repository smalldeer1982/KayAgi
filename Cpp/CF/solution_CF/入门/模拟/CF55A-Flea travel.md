# Flea travel

## 题目描述

一个虫子位于绕城一圈的$n$片树叶中的一片上，在第$k$分钟，虫子会跳过$k-1$片树叶并在脚下的树叶上做一个记号。在这里，我们假设虫子的$life=+∞$。你的任务是判断该虫子是否将$n$片树叶都做了记号。

## 样例 #1

### 输入

```
1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
3
```

### 输出

```
NO
```

# 题解

## 作者：da32s1da (赞：15)

这个题嘛，先打打表找找规律、、、

发现$n=2^k$时，为$YES$，否则为$NO$。。。

于是
```
#include<cstdio>
#include<cmath>
int n,t;
int main(){
    scanf("%d",&n);
    n==1<<(t=log2(n))?puts("YES"):puts("NO");
}
```

---

## 作者：black_trees (赞：3)

## 暴力


upd on 2020年8月18日07:58:17：感谢@小汪同学指出文中的描述错误。

-----------------

对你没有看错，这道题可以直接**暴力**。

首先我把 $n=1,2,3,4,5,6,7,8,9$ 的情况全部拿出来模拟了一遍。

题目里说，这 $n$ 片叶子都是排成**环状**的，那么就可以让他们首尾相接去模拟出情况。

比如 $n=4$ 的时候：


如图：标记过程就是 $1,3,2,4$。（红星代表出发点，下同）

![](https://cdn.luogu.com.cn/upload/image_hosting/u1gtu0fo.png?x-oss-process=image/resize,m_lfit,h_1703,w_2325)

那，规律就是 $n$ 为偶数的时候输出 $YES $ 吗？

我们继续往下模拟，模拟到 $n=6$ 的时候就发现，是不可以的。

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/9e094b9l.png?x-oss-process=image/resize,m_lfit,h_1730,w_2235)

（如果 $n=6$ 时，那么就会一直在 $1,3,5$ 循环，是无法标记 $2,4,6$ 的）

如果继续模拟，可以发现 $n=8,16,32$ 都是满足条件的。

那规律自然就会出来：$n $ 必须是 $2$ 的次幂。

还要注意的是， $n=1$ 时也是可以的，因为它相当于
$2^{0}$。

楼上大佬用的对数我这个蒟蒻还不会，那么，就用暴力判断吧！

### 思路：

因为这个数据超级小 $(1 \le n \le 1000)$

所以？

 $while$ 循环直接暴力判断啊！
 
 
不断的把 $x$ 除以 $2$ ，如果它是 $2$ 的平方数，那么最后一定会除出来 $1$，反之则不是。

例子 A：

当 $n=8$ 的时候：

$8 \div 2=4$

$4 \div 2 =2$

$2 \div 2=1$

所以8是满足条件的。

例子B：

当 $n=6$ 时

$6 \div 2=3$

$3\div 2=1.5$

$1.5 \div 2=0.75$

所以 $6$ 不满足条件。

但是在循环除的时候要注意一点： $n$ 一定要是一个浮点数,否则 $C++$ 的蜜汁判定就会让你 $\color{red}WA$。


$Code:$

~~~cpp
#include<bits/stdc++.h>
using namespace std;
bool check(double x){
	while(x>1){//如果n=1的时候，就不会继续循环，直接判断
	     x/=2;	//循环拆分X，直到小于等于1时退出判断
	}
	if(x==1.0){
	   return true;//如果x最后为1，那么就证明x是2的平方数。
	}
	return false;//反之则不是
}
double n;//这里定义的n是double类型，因为在拆分的时候很可能会出现结果小数，如果定义成int就会出错
int main(){
    cin>>n;
    if(check(n)){
       puts("YES");
    }
    else{
        puts("NO");//puts函数相较于printf和cout要快一点
    }
    return 0;
}
~~~

---

## 作者：Siyuan (赞：2)

> ## 本人蒟蒻，不会证明楼下大佬$\ 2^k$的结论。。。

## 本题思路：
证明如下证明即可：**跳跃$\ 2n$次之后回到初始位置。**
	
当跳跃了$\ 2n$次之后，一共跳跃了$\ (1+2+3+\cdots+2n)$步，即$\ n(2n+1)$步，能够被$\ n$整除，因此会回到初始位置。
    
据此，我们只需要模拟前$\ 2n$次跳跃即可。。。（水过）

### 代码如下：

```
#include<cstdio>
using namespace std;

int n,pos;
bool vis[1001];

int main()
{
	scanf("%d",&n);  n<<=1;
	for(register int i=1;i<=n;i++)
	{
		vis[pos]=1;
		pos=(pos+i-1)%n;
	}
	n>>=1;
	for(register int i=0;i<n;i++)
		if(!vis[i])  return puts("NO"),0;
	return puts("YES"),0;
}
```

---

## 作者：qzhwmjb (赞：1)

### 思路
---
虫子规律：  
我们列一个表格：  
n为4时   
| \ | 第一分钟 | 第二分钟 | 第三分钟 | 第四分钟 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| 个数 | 1 |  2|  4|  3|
我们就可以得出第i分钟跳（a[i-1]+(i-1)）%n+1个.  
#### 这里要注意——》a[0]=1,a[1]=2.需要赋值. 
同时数组下标是从0开始的.   
找到了规律.   
接下来只需要比较实际和预计是否相同就好了.   
设两个变量，   
分别循环加上a[i]和i.  
比较是否相等.  
--是：输出“YES”  
--否：输出“NO”
### 全代码
---
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000];
int main(){
    int n;
    cin>>n;
    int i,sum=0;
    for(i=1; i<=n; i++){
        sum+=i;
    }
    a[0]=1;
    a[1]=2;
    for(i=2; i<n; i++){
        a[i]=(a[i-1]+(i-1))%n+1;
    }
    int sum1=0;
    for(i=0; i<n; i++){
        sum1+=a[i];
    }
	if(sum==sum1){
       	cout<<"YES"<<endl;
	}else{
       	cout<<"NO"<<endl;
	} 
    return 0;
 }
```


---

## 作者：OdtreePrince (赞：1)

# -模拟-

一通乱七八糟的模拟之后总能见彩虹！

每一次都要进行判断，包括循环结束，如果全部到过，print：YES，or print：NO ！

模拟出奇迹，Oh,yeah!

上代码！

~~~
#include<bits/stdc++.h>
using namespace std;
int n,b[1005],now=1,t;
int check(){
    for(int i=1;i<=n;i++){
        if(!b[i]) return 0;
    }
    return 1;
}
int main(){
    scanf("%d",&n);
    while(t<=20000&&check()==0){
        t++;
        now+=t-1;
        now%=n;
        if(now==0) now=n;
        b[now]=1;
    }
    if(check()) cout<<"YES";
    else cout<<"NO";
    return 0;
}
~~~

---

## 作者：_Qer (赞：0)

一个模拟，循环条件与楼下大佬略不同

可以这样解释：
当$k>n$时，继续走与$k \mod n$时是等价的，于是当$k>n$时就跳出循环，判断是否走过所有点，最后输出。
（可能不严谨，~~反正我过了~~欢迎大佬指正）

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a = 1, sd = 0, k = 1;
//依次为叶片数，当前位置，标记的叶片的数量，时间
bool used[1010];
//标记叶片是否走过
int main()
{
    cin >> n;
    while (k <= n + 1 && sd < n)//k不大于n且没有全部走过
    {
        a = (a + k - 1) % n; //走到下一个位置
        if (!used[a])//标记并记录数量
        {
            used[a] = 1;
            ++sd;
        }
        ++k;//下一分钟
    }
    if (sd == n)//全部走过
    {
        cout << "YES" << endl;
    }
    else//没走完
    {
        cout << "NO" << endl;
    }
    return 0;
}
```

---

