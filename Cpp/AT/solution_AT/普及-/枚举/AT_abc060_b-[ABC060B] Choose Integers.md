# [ABC060B] Choose Integers

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc060/tasks/abc060_b

あなたは、正の整数をいくつか選び、それらの総和を求めます。

選ぶ数の上限や、選ぶ整数の個数に制限はありません。 どんなに大きな整数を選んでもよいですし、整数を $ 5000 $ 兆個選んでもよいです。 ただし、選ぶ数はすべて $ A $ の倍数でなくてはいけません。 また、少なくとも $ 1 $ つは整数を選ばなくてはいけません。

そして総和を $ B $ で割ったあまりが $ C $ となるようにしたいです。 こうなるように整数を選ぶことが出来るか判定してください。

出来るならば `YES`、そうでないならば `NO` を出力してください。

## 说明/提示

### 制約

- $ 1\ ≦\ A\ ≦\ 100 $
- $ 1\ ≦\ B\ ≦\ 100 $
- $ 0\ ≦\ C $

### Sample Explanation 1

たとえば $ 7,\ 14 $ を選ぶと総和は $ 21 $ となり、これを $ 5 $ で割ったあまりは $ 1 $ となります。

### Sample Explanation 2

偶数をいくつ足したとしても、けっして奇数になることはありません。

### Sample Explanation 3

$ 1 $ の倍数、つまりすべての整数が選べるので、$ 97 $ を選べば良いです。

## 样例 #1

### 输入

```
7 5 1```

### 输出

```
YES```

## 样例 #2

### 输入

```
2 2 1```

### 输出

```
NO```

## 样例 #3

### 输入

```
1 100 97```

### 输出

```
YES```

## 样例 #4

### 输入

```
40 98 58```

### 输出

```
YES```

## 样例 #5

### 输入

```
77 42 36```

### 输出

```
NO```

# 题解

## 作者：MZY666 (赞：15)

[原题传送门](https://www.luogu.com.cn/problem/AT2554)。[在窝的博客中食用更佳](https://www.luogu.com.cn/blog/MZY666/solution-at2554)。

### 【 题意概括 】

输入三个数 $a$，$b$，$c$，问存不存在某个倍数 $i$ 使得 $(a \times i) \mod b=c$ ？

若存在则输出 `YES` ，否则输出 `NO` 。

### 【 思路 】

直接暴力枚举，保证不超时 AWA。

但有一个问题：我们在 $i$ 的值为多少时退出循环呢？答案是 $b$。证明：

令 $(a \times 1) \mod b=d$，则：

$$(a \times 2)\mod b=d \times2\mod b$$

$$(a \times 3)\mod b=d \times3\mod b$$

$$...$$

$$(a \times b)\mod b=(d \times b)\mod b$$

$$(a \times b)\mod b=0$$

所以：

$$(a \times (b+1))\mod b=((a \times 1) \mod b+(a \times b)\mod b)\mod b$$

$$(a \times (b+1))\mod b=(d+0)\mod b$$

$$(a \times (b+1))\mod b=d$$

所以 $((a \times (b+1))\mod b)$ 的结果与$(a \times 1) \mod b$ 的结果是一样的。

同理，$((a \times (b+k))\mod b)$ 的结果与 $(a \times k) \mod b$

因此只需要枚举到 $b$ 即可知道 $a$ 以及其的倍数除 $b$ 所得余数的所有可能了。

那么，是时候来康康代码了。

### 【 代码实现 + 注释 】

```cpp
#include<bits/stdc++.h>//万能头文件可好 
using namespace std;
int main(){//主函数 
	int a,b,c;//定义 
	scanf("%d%d%d",&a,&b,&c);//输入 
	for(int i=1;i<=b;i++){//开始循环判断，前文有解释 
		if((a*i)%b==c){//若符合题意 
			printf("YES\n");//输出，换行是个好习惯 
			return 0;//提前结束程序 
		}
	}
	printf("NO\n");//如果一直没有符合题意的倍速，则输出NO 
	return 0;//over~
}
```

由于作者自愿禁言了，如果有建议请私信。否则将**无法**回复您哦！

完结撒花~（疯狂暗示 OoO

---

## 作者：Priori_Incantatem (赞：5)

为什么要枚举$1000$呢?除以$B$的余数只能是$0$~$B-1$($B$种余数),因此就枚举$B$个$A$的倍数就好了
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a,b,c,i;
int main(){
    scanf("%d%d%d",&a,&b,&c);
    for(i=1;i<=b;i++)
    {
        if((a*i)%b==c){printf("YES\n");return 0;}
    }
    printf("NO\n");
    return 0;
}
```

---

## 作者：詹詹tv__詹詹 (赞：3)

### 不是，我想知道大家看到题都是在想枚举吗。。。
### 我竟然没有看到我想要的方法。

### 好吧，事实证明，这道题数据真的是太水了，枚举都能过。

## 多好的一道最大公约数的题啊！！！

### 先附上代码（注解版）
```
#include<bits/stdc++.h>

using namespace std;

int gcd(int x , int y){//最大公约数函数
	while(x % y){//更相减损法进阶：辗转相除法
		int r = x % y;//取余
		x = y;
		y = r;//迭代
	}
	return y;//最大公约数
}

int main(){
	
	int a , b , c;
	cin >> a >> b >> c;//被除数，除数，余数
	
	if(c % gcd(a , b) == 0){//这条式子下面会给出证明
		cout << "YES";
	}else{
		cout << "NO";
	}
	return 0;
}
```
### 证明：
```
//证明：
//原题可表示为 
//k * a - p * b = c
//原式 = gcd(a , b) * [k * a / gcd(a , b) - p * b / gcd(a , b)]
//因为 k , p为任意整数
//所以 [k * a / gcd(a , b) - p * b / gcd(a , b)] 可以取任意整数值
//所以当 c 能整除 gcd(a , b)时 , 可以满足题目条件 
```




---

## 作者：封禁用户 (赞：3)

### 暴力出奇迹

这是一个倍数问题，有这么几种情况：

**1. a=1**

1是所有自然数的因数，所以如果a=1，则肯定能满足条件，输出“YES”。

```cpp
if(a==1) {
	cout<<"YES"<<endl;
	return 0;
}
```

**2. a!=1**

如果a!=1，那么就要在a的倍数里边找了。

这里我从a的1倍枚举到a的100倍，如果符合条件，输出并return。

随后如果还在执行，说明没有找到，输出“NO”。

```cpp
for(int i=1; i<=100; i++) {
	if(a*i%b==c) {
		cout<<"YES"<<endl;
		return 0;
	}
}
```

AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	int a,b,c;
	cin>>a>>b>>c;
	if(a==1) {
		cout<<"YES"<<endl;
		return 0;
	}
	for(int i=1;i<=100;i++)
	{
		if(a*i%b==c)
		{
			cout<<"YES"<<endl;
			return 0;
		}
	}
	cout<<"NO"<<endl;
	return 0;
}
```

**特别提醒：“YES”和“NO”均为大写。**

---

## 作者：艾恩葛朗特 (赞：2)

开始没思路，后来看了题解几位大佬的解释后，茅塞顿开

首先，我们定义一个头文件
```cpp
#include<cstdio>
```
其次，定义变量
```cpp
int x,y,z;
```
main()函数
```cpp
int main()
```
输入
```cpp
scanf("%d %d %d",&x,&y,&z);
```
代码核心部分
```cpp
for (int i=0;i<=1000;i++)//经过事实证明，枚举0~1000就够了
if (i*x%y==z)
{
	printf("YES");//如果条件成立，输出YES
    return 0;
}
printf("NO");//如果没有结束，输出NO
return 0;//滑稽收场
```


---

## 作者：Dark_Sky (赞：1)

只要a乘的倍数大于b，就是所有的情况了，然后再判断a % b == c 就行了。

上代码：
```
#include <iostream>

using namespace std;

int s = 1,x;

bool panduan(int a,int b,int c){//判断a % b == c的函数
	x = a;
	while(s <= b){//若a的倍数大于b说明没找到
		if(a % b == c)return true;//找到了
		a = x;//让a重新赋值
		s++;//乘的倍数+1;
		a *= s;//让a枚举倍数
	}
	return false;//没找到就return false
}

int main(){
	int a,b,c;
	cin>>a>>b>>c;
	if(panduan(a,b,c))cout<<"YES"<<endl;//找到了
	else cout<<"NO"<<endl;//没找到
	
	return 0;//完美的结束
}
```


---

## 作者：Juvenile (赞：0)

# 注意：神犇勿入

### ~~这是一份神奇的题解~~

------------

回归正题

以一道数学题的角度来解释一下：

可以看出若 l=gcd(a,b) 则必有 c≡0(mod l

###### 神奇的证明：
设 l=gcd(a,b) 

a=x × l,b=y × l (x,y为正整数)

则必有 a × i=b × k+c (i,k为正整数)

x × l × i = y × l × k +c

可得 l × (x × i - y × k)=c 

#### 因为x,y,k均为正整数,所以c为l的倍数
#### 否则无法得到c

给出华丽的代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int a,b,c;
int gcd(int a,int b)
{
    while(b^=a^=b^=a%=b);//玄学
  	return a;
}
int main()
{
    scanf("%d%d%d",&a,&b,&c);
    int l=gcd(a,b);
    if(c%l!=0) printf("NO");
    else printf("YES");
}
```


------------
## 感谢[用户名已丢失](https://www.luogu.org/space/show?uid=100250)巨佬的帮助


---

## 作者：TCZN (赞：0)

居然没有P党题解？！

蒟蒻就来水一发吧

此题十分简单，黄题？！这明显是恶评，我蒟蒻就是肝爆，做红题，也不做谷民恶评的题！~~艾玛真香~~

这题爆举到1000就行


这个时间不要太[宽裕](https://www.luogu.org/recordnew/show/19488166)（全部0ms，0空间）
```pascal
var
  a,b,c,i:longint;
begin
 read(a,b,c);
  for i:=1 to 1000 do //爆举到1000倍
   if a*i mod b=c then //如果a的倍数中有符合题目条件的数就输出YES
    begin
      writeln('YES');
      halt; //直接结束程序
    end;
     writeln('NO'); //如果有的话不会执行这条语句
end.
```



---

## 作者：七夜 (赞：0)

首先注意到这道题并不是特别的坑，因为没有爆什么范围。

其次就是这道题的唯一需要思考的点，就是循环多少次结束

看到下面几位循环1000次，我觉得没有必要，只需要循环b次就够

所有就有了本蒟蒻的丑陋代码

```
#include<bits/stdc++.h>//偷懒专用 
#define MAXN 99999
#define INF 101//宏定义，写数组是后用的 
using namespace std;
inline int read(){
 char c=getchar();int x=0,f=1;
 while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
 while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
 return x*f;
}//快读，想学习的可以借鉴 （虽然这道题cin，scanf都能过，但是本蒟蒻习惯了用快读） 
int a,b,c;
int main()
{
	a=read();
	b=read();
	c=read();//读入三个数 
	for(int i=1;i<=b;++i)//循环b次最多 
	 {
	 	if(a*i%b==c)//满足马上输出然后结束循环，节省时间 
	 	 {
   			cout<<"YES\n";	
			return 0;
		 } 
	 }
	cout<<"NO\n";//否则输出no 
	return 0;//完美落幕 
}
```


---

## 作者：百里亦守约 (赞：0)

又来水（xie）AT的题解了。。

看来又是一道愚人节的题目。。

# 思路：
输入三个数后，直接按照题意打一个while的循环，条件就是当a的倍数（sum）%b！=0和a的倍数不可以超过一千个，所以按照题意枚举即可。

## 下见~~丑陋~~的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,sum;
int main()
{
	cin>>a>>b>>c; //输入三个数
	sum=a; //sum用来找倍数
	while(sum%b!=c && sum<=a*1000) //按题意枚举
		sum+=a; //每次求出倍数
	if(sum%b==c) //因为前面没有记住是满足条件退出的还是一直循环退出的，所以在最后就再判断一次。
	    cout<<"YES"<<endl; //输出不要忘了换行。
	    else
	    cout<<"NO"<<endl; //输出不要忘了换行。
	return 0;
}
```


---

## 作者：TRZ_2007 (赞：0)

本蒟蒻看到这道题的难度时，吓得瑟瑟发抖。可是看到这题的翻译时，笑得~~瑟瑟发抖~~。
# 黄题？不存在的！  
根据楼下大佬的推断，只要爆举到$1000$就可以了，于是本蒟蒻就这么$AC$了，就是暴力！  
上代码$qwq$
```
#include <stdio.h>//C党强迫症
int main()
{
	int i,a,b,c,ans;//i用来枚举，a,b,c是读入，ans是记录a*i是多少
	scanf("%d %d %d",&a,&b,&c);//读入三个数
	for(i=0;i<=1000;i++)//枚举到1000就足够了
	{
		ans=a*i;//计算a*i
		if(ans%b==c)//如果满足条件
		{
			printf("YES\n");//就输出YES，记得换行
			return 0;//直接结束程序，节省时间.jpg
		}
	}
	printf("NO\n");//没有找到
}//完美收场2333（防伪标记）
```

---

## 作者：RioBlu (赞：0)

简单的暴力枚举，循环大约1000次即可
```
#include<bits/stdc++.h>
using namespace std;
long long a,b,c;
int main()
{
	cin>>a>>b>>c;
	for(int s=1;s<=1000;s++)//暴力循环
	{
		if((a*s)%b==c)
		{
			cout<<"YES"<<endl;//成功，找到了
			return 0;
		}
	}
	cout<<"NO"<<endl;//没有找到
}
```

---

## 作者：政凯 (赞：0)

在这道题，a%b的余数为0，那么它的余数永远不能改变，这时，如果c为0，输出NO，否则输出YES；

如果不为0，则暴力枚举：每次加上a1（a%b）(相当于加a，因为（a+a）%b==（a+a1）%b)，如果相等，输出YES，并退出；否则继续枚举


# 记住换行！！！

------------------------满分程序-----------------------


```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a,b,c,a1,bb[100000+5];
int main()
{
    cin>>a>>b>>c;
    a=a%b;a1=a;
    if (a==0&&c==0) {cout<<"YES"<<endl;return 0;}
    if (a==0&&c!=0) {cout<<"NO"<<endl;return 0;}
    while (1)
    {
        if (a==c) {cout<<"YES"<<endl;return 0;}
        a+=a1;//加余数
        a=a%b;//余数的范围是0~b-1
        if (bb[a]==10) break;//因为有些是数据的A的倍数里没有除B余C的，这样会节省时间
        bb[a]++;
    }
    cout<<"NO"<<endl;
    return 0;
}
```


---

