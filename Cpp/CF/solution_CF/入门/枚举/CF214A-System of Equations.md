# System of Equations

## 题目描述

Furik "非常喜欢" 数学课, 所以他从不去上课, 不像 Rubik. 但是现在Furik想要得到一个好一点的数学成绩. 为此, 他的数学老师Ms. Ivanova给了他一个新任务. Furik一瞬间就搞定了. 你行吗?

给你一个如下的等式方程组:

![](https://cdn.luogu.org/upload/vjudge_pic/CF214A/62e1cfae0726c97a669dda13cb6a561eafa52412.png)你的任务是计算, 有多少组整数(a,b)(0<=a,b)满足这个方程组.

## 样例 #1

### 输入

```
9 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
14 28
```

### 输出

```
1
```

## 样例 #3

### 输入

```
4 20
```

### 输出

```
0
```

# 题解

## 作者：weareyoungi (赞：2)


**大清早上写了一个题目，迷迷糊糊看错了好几次，发现你们的题解都好复杂的说，也许是因为你们是大佬，思维严谨，而我是蒟蒻罢了！！！**


好了言归正传，我们来分析一下题目吧。

这题可以简单的说，输入n,m，找到a,b（其中a和b两个数都大于等于0，1<=n,m<=1000）两个数，使得以下等式成立：


![1](https://cdn.luogu.org/upload/vjudge_pic/CF214A/62e1cfae0726c97a669dda13cb6a561eafa52412.png)

让我们来分析下，首先，根据$a^2$ = n - b 推出n - b  &ge; 0 ,然后推出b &le; n;
同理可推出a &le; m,然后就这样了，上代码：

```c
#include<stdio.h>   


int main()
{
    int n,m;
    int count=0;    //用于记录个数
    scanf("%d %d",&n,&m);        
    for(int a=0;a<=m;a++)
    {
        for(int b=0;b<=n;b++)        //穷举所有可能性
        {
            if(a*a+b==n&&a+b*b==m)
                count++;
        }
    }
    printf("%d",count);     //打印count的值
}
```


---

## 作者：AlwaysForward (赞：2)

# 温馨提示：此题有$54$个测试点
若有一个测试点没过，则后面测试点不再执行。

```
   for(i=0;i<=1010;i++){
		for(j=0;j<=1010;j++){
			if(pow(i,2)+j==n&&pow(j,2)+i==m){
				s++;
		}
	}
```
以上的循环是代码的灵魂。

题目中说：a，b均小于1000，因为1000这个数不大，所以我们直接用1010（大一点好一些）来循环。

然后将方程组的条件列上：

    if(pow(i,2)+j==n&&pow(j,2)+i==m)

然后计算器s加一。

这显然不是复杂度最低的方法。

因为a^2+b=n,b^2+a=m且a，b均大于0

所以a，b都小于min（m，n）

代码就变成了这样：

```
   for(i=0;i<=min(m,n);i++){
		for(j=0;j<=min(m,n);j++){
			if(pow(i,2)+j==n&&pow(j,2)+i==m){
				s++;
		}
	}
```
最后，祝宁$A$了此题

代码双手奉上：

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,m;
	cin>>n>>m;
	int i,j,s=0;
	for(i=0;i<=min(m,n);i++){
		for(j=0;j<=min(m,n);j++){
			if(pow(i,2)+j==n&&pow(j,2)+i==m){
				s++;
			}
		}
	}
	cout<<s;
}
```


---

## 作者：ProjectRed (赞：0)

这是一道比较水的题目，适合初学者用来巩固基础

看了一下别的题解都是两重循环，就尝试了一下一重循环

其实转换成一重的思想非常的简单，就是通过第一个式子把b用m,n,a来表示，再把a从0到sqrt(n)枚举一遍，检验一下在第二个式子中是否成立，详见代码
```cpp
#include<bits/stdc++.h>//可以换掉，不过编译不计入总时间，所以不会对时间有太大影响
using namespace std;
int main ()
{
	int n, m;
	scanf ("%d%d", &n, &m);
	int ans = 0;
	for (int a = 0; a * a <= n; a++)
	{
		int b = n - a * a;//由①式得出的表达式
		if (b * b + a == m)ans++;//检验，正确就加一
	}
	printf ("%d", ans);
	return 0;
}
```


---

## 作者：BB2655 (赞：0)

从$0$开始枚举$(a,b)$

因为$a,b$为非负整数，所以$a^2<=n$，所以$a<=sqrt(n)$

同理$b<=sqrt(m)$

所以枚举的时候$a,b$的上边界就可以知道了

代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,m,h=0;  //h统计个数
    scanf("%d%d",&n,&m)  //输入
    for(int i=0;i<=sqrt(n);i++)  //从0开始枚举a
    {
        for(int j=0;j<=sqrt(m);j++)  //从0开始枚举b
        {
            if(i*i+j==n&&j*j+i==m)  h++;  //判断
        }
    }
    printf("%d",h);
    return 0;
}
```

---

## 作者：Hanson水题大佬 (赞：0)

# ~~一道其实只有红题难度的题~~

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF214A/62e1cfae0726c97a669dda13cb6a561eafa52412.png)

因为a²<= n; b² <= m;
所以a <= n^0.5; b <= m^0.5
思路就很~~简单~~了



------------

```cpp
#include <bits/stdc++.h>
#define LL long long//本人比较喜欢用#define 
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define getinPLUS(a, b) scanf("%lld%lld", &a, &b)
#define getout(a) printf("%lld", a)
LL n, m;
LL ans = 0;
int main()
{
	getinPLUS(n, m);
	FOR(i, 0, sqrt(n))
		FOR(j, 0, sqrt(m))
			if(i * i + j == n && j * j + i == m)//直接按a^2 + b = n; b^2 + a = m 的方程求解  
				ans ++;//如果对上了，就加1 
	getout(ans);
	return 0;
} 


//代码可能比较丑 
```



------------




------------
# ~~求过~~~~

---

