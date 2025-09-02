# Vanya and Cubes

## 题目描述

Vanya got $ n $ cubes. He decided to build a pyramid from them. Vanya wants to build the pyramid as follows: the top level of the pyramid must consist of $ 1 $ cube, the second level must consist of $ 1+2=3 $ cubes, the third level must have $ 1+2+3=6 $ cubes, and so on. Thus, the $ i $ -th level of the pyramid must have $ 1+2+...+(i-1)+i $ cubes.

Vanya wants to know what is the maximum height of the pyramid that he can make using the given cubes.

## 说明/提示

Illustration to the second sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF492A/95fc6e512a79cba53044cb07f98e0b0b07a634cb.png)

## 样例 #1

### 输入

```
1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
25
```

### 输出

```
4
```

# 题解

## 作者：云浅知处 (赞：8)

审题：
***
金字塔的顶层必须由个$1$立方体组成，

第二层必须由$1+2=3$个立方体组成，

第三层必须有$1+2+3=6$个立方体

.....

依此类推。

因此，金字塔的第i级必须具有$1+2+\cdots+(i-1)+i$个立方体。

Vanya想要知道他可以使用给定的立方体制作金字塔的最大高度。
***
转化成数学的抽象语言就是：

给定$n$，若

$$1+(1+2)+(1+2+3)+...+(1+2+3+...+(i-1)+(1+2+3+\cdots+i)<=n$$

求$i$的最大值。
***
解题：

第一步，我们要引入一个公式：求和公式

$$1+2+3+...+(n-1)+n=\frac{n(n+1)}{2}$$

这个公式的证明如下：
***
设$S=1+2+3+\dots+(n-1)+n\quad\cdots\cdots$①

则$S=n+(n-1)+\dots+3+2+1\quad\cdots\cdots$②

将①式②式相加得：

$$2S=(n+1)+(n+1)+\dots+(n+1)=n(n+1)$$

故$S=\frac{n(n+1)}{2}$

即$1+2+3+\cdots+(n-1)+n=\frac{n(n+1)}{2}$

证毕
***
故

$$\quad\,1+(1+2)+(1+2+3)+\cdots+\left[1+2+3+\cdots+(i-1)\right]+(1+2+3+\cdots+i)$$

$=\frac{1\times2}{2}+\frac{2\times3}{2}+\frac{3\times4}{2}+\cdots+\frac{(i-1)i}{2}+\frac{i(i+1)}{2}$

$=\frac{1\times2+2\times3+3\times4+\cdots+(i-1)i+i(i+1)}{2}$
***
接下来我们要引入第二个公式：

$$1\times2+2\times3+3\times4+\cdots+(n-1)n+n(n+1)=\frac{n(n+1)(n+2)}{3}$$

这个公式的证明方法有许多种，这里选取相对较为简单的一种：
***
注意到：

$1\times2=\frac{1\times2\times3-0\times1\times2}{3}$,

$2\times3=\frac{2\times3\times4-1\times2\times3}{3}$,

$3\times4=\frac{3\times4\times5-2\times3\times4}{3}$,

$\cdots\cdots$

同理，$n\left( n+1 \right)=\frac{n\left( n+1 \right)\left( n+2 \right)-\left( n-1 \right)n\left( n+1 \right)}{3}$

故

$\quad1\times2+2\times3+3\times4+\cdots+n(n+1)$

$=\frac{1\times 2\times 3-0\times 1\times 2}{3}+\frac{2\times 3\times 4-1\times 2\times 3}{3}+\frac{3\times 4\times 5-2\times 3\times 4}{3}+\cdots+\frac{n\left( n+1 \right)\left( n+2 \right)-\left( n-1 \right)n\left( n+1 \right)}{3}$

$=\frac{1\times 2\times 3-1\times 2\times 3+2\times 3\times 4-2\times 3\times 4+3\times 4\times 5-3\times 4\times 5+\cdots+\left( n-1 \right)n\left( n+1 \right)-\left( n-1 \right)n\left( n+1 \right)+n\left( n+1 \right)\left( n+2 \right)}{3}$

$=\frac{n\left( n+1 \right)\left( n+2 \right)}{3}$

证毕
***
故原式$\quad\,1+(1+2)+(1+2+3)+\cdots+\left[1+2+3+\cdots+(i-1)\right]+(1+2+3+\cdots+i)$

$=\frac{1\times2}{2}+\frac{2\times3}{2}+\frac{3\times4}{2}+\cdots+\frac{(i-1)i}{2}+\frac{i(i+1)}{2}$

$=\frac{1\times2+2\times3+3\times4+\cdots+(i-1)i+i(i+1)}{2}$

$=\frac{\frac{n\left( n+1 \right)\left( n+2 \right)}{3}}{2}$

$=\frac{n(n+1)(n+2)}{6}$
***
化简完毕，开始写代码啦！

代码如下：
```cpp
#include<algorithm>
#include<bitset>
#include<bits/stdc++.h>
#include<cstdlib>
#include<exception>
#include<functional>
#include<iostream>
#include<limits>
#include<map>
#include<new>
#include<ostream>
#include<queue>
#include<string>
#include<typeinfo>
#include<utility>
#include<vector>
#include<wchar.h>//一大波头文件汹汹来袭
using namespace std;
int main(){
	int n,i,s;//i是层数，s是总共需要的小方块数，n同题意
	cin>>n;
	s=(i*(i+1)*(i+2))/6;//这就是刚刚推导出来的公式，用来表示总共需要的小方块数
	for(i=1;i<=39;i++){//这个39的意思是10000个小方块最多可以搭39层，而题中说了n<=10000
		s=(i*(i+1)*(i+2))/6;
		if(s>n){//如果总共需要的小方块数超过了给定的小方块数
			cout<<i-1<<endl;//输出层数，这里千万记得要减一，因为此时的层数所需要的小方块数是比总数多的
			return 0;//结束程序
		}
	}
	return 0;//个人觉得这玩意没啥用。。。
}
```
***
最后：
$\huge\color{red}\text{共创文明洛谷，拒绝Crtl+C!!!}$

---

## 作者：da32s1da (赞：2)

观察可知，数列为1,4,10,20.....直觉告诉我，递推公式是$$a_n=\frac{n*(n+1)*(n+2)}{6}$$。

```
#include<cstdio>
int n,i;
int main(){
    scanf("%d",&n);
    for(i=1;i<=40;i++)
    if(i*(i+1)*(i+2)/6>n)break;
    printf("%d\n",i-1);
}
```

---

## 作者：封禁用户 (赞：1)

嗯，这是一道~~被水冲洗过而特别鲜艳的~~红题。

这道题究竟什么思路？？？~~我也不知道~~。

## 话不多说，上代码！
```
#include<iostream>
using namespace std;
int n,s=1,t=2,g;//n为立方体的个数，s用来统计每一层所需要的立方体个数，(s+t)即为下一层所需的个数
int main()
{
	cin>>n;
	while(n>=s)//while循环，如果剩下的立方体个数仍可以搭下一层，就执行
	{
		g++,n-=s,s+=t,t++;//层数累加，立方体个数减去s，s变为下一层的所需个数
	}
	cout<<g;//输出
	
	return 0;//完美结束
}
```

最后，我要告诫你们一句话：

# 请勿CTRL+C！

---

## 作者：tocek_shiki (赞：1)

看到这题的公式，第一眼就应该想到：高斯求和公式

想必各位同学一定要都会，我也就不多说了

# 那么很显然：第i层所需的砖块

### **${Sum \ = \ 1+2+3...+(i-1)+i =i*(i+1)/2}$**

然后我们再模拟一边就好了

上代码(＾Ｕ＾)ノ~ＹＯ

```cpp
#include <bits/stdc++.h>
#define in(a) scanf ("%d", &a)
#define mem(a, b, l) for(int i = 0; i < l; i ++) a[i] = b;
#define out(a) printf ("%d", a)
using namespace std；

int n;
int ans = 1;//1层坑定要能放嘛~~
int main()
{
	in (n);
	while (n >= ans*(ans+1)/2)//如果我目前还可以再放
		n -= ans*(ans+1)/2, ans ++;//不放干嘛
	out (ans-1);//注意了，这是我能放的最高的一层的上面一层，所以输出的时候要-1
    return 0;
}
```
~~依然欢迎私信骚扰啊~~

---

## 作者：开心的猪 (赞：0)

此题如果直接使用暴力的话，可能会被卡。。。于是可以使用一个数学公式：

1+2+3+...+n=n*(n+1)/2;

使用了这个公式，时间复杂度就从O（n^2）降到O（n）了，数据在加强一下数据也不怕了。。。

以下是代码：

```
#include<bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	scanf("%d", &n);
	for(int i=0; i>=0; i++)
	{
		int k=(i*(i+1))/2;
		if(n<k)
		{
			printf("%d", i-1);
			return 0;
		}
		n=n-k;
	}
}
```


---

## 作者：ACE_ZY (赞：0)

看着大佬们用公式,我却只能模拟

Pascal:
```pascal
var
  n,i,x,y,sum:longint;
begin
  readln(n);
  for i:=1 to n do//这边反正答案最大不会超过n,直接1 to n就行了
  begin
    x:=y+i;//第i层的立方体数量,y指i-1层的立方体数量
    sum:=sum+x;//这边累加i层的总立方体数量
    if sum>n then begin writeln(i-1);exit;end;//如果n个立方体不够拼出i层的金字塔,说明最多只能拼成i-1层的金字塔
    if sum=n then begin writeln(i);exit;end;//这边是专门判断n为1的情况的(如果n为1,说明只有1个立方体,这也说明i是从1到1的,i等于1的时候,sum并没有超过n,但是i却不可能等于2,所以就加了个这样的判断,其实也可以for i:=1 to n+1 do 的,这边不管多大都没关系,因为反正循环里有退出)
    y:=x;
  end;
end.
```


---

## 作者：sxtm12138 (赞：0)

在做这道题时我一开始没有想到那个通项公式，所以方法和之前的dalao不太一样。首先我算出了前几层所需的方格数：1,4,10,20,35…………我发现4=2^2+0,10=3^2+1,20=4^2+4,从而得出了一个规律：
### f[n]=f[n-2]+n^2

 _以下为代码：_ 

------------


```cpp
#include<bits/stdc++.h>
int a[10005]={0,1},n;//初始化a[0]=0,a[1]=1
int main()
{scanf("%d",&n);//读入
 for(int i=2;;i++) {a[i]=i*i+a[i-2];//套公式计算a[i]的值
                    if(a[i]>n) {printf("%d",i-1);//别忘了减1
	                            return 0;}//一旦满足条件就停止
	               }
}//本蒟蒻初学信奥，格式不太好，请各位大佬见谅

```

---

## 作者：Jinyeke (赞：0)

### 思路：根据题目，第n层的小正方体可以这么算：
### 1+2+3+4+...+(n-1)+n
#### 所以，让我们一起打起pascal的while循环
代码如下（pascal）：
```pascal
var
 n,k,i,j:longint;
begin
 read(n);
 i:=1;//第一层
 k:=1;//第一层立方体个数
 while n-k>=0 do //判断是否可以搭下一层
   begin
     n:=n-k;//减去这一层的个数
     i:=i+1;//层数+1
     k:=0;//先清零
     for j:=1 to i do k:=k+j;//加上第i层的
  end;
 write(i-1);//因为剩下的不足以搭第i层的，所以输出i-1
end.
```
### 共建文明洛谷，请勿Ctrl+C！

---

## 作者：agicy (赞：0)

# 思路

## 猜想

显然，要搭建$m$层的金字塔，所需立方体个数为:

$\sum_{i=1}^{m}\frac{i(i+1)}{2}$

经过计算我们得出：

$m=1,n=1;$

$m=2,n=4;$

$m=3,n=10;$

$m=4,n=20.$

根据数据，提出猜想：$\sum_{i=1}^m\frac{i(i+1)}{2}=\frac{m(m+1)(m+2)}{6}$

## 证明

我们采用**数学归纳法**证明。

- 经过计算，当$m=1$时，猜想成立。

- 假设$\sum_{i=1}^{m}\frac{i(i+1)}{2}=\frac{m(m+1)(m+2)}{6}$成立，试证明$\sum_{i=1}^{m+1}\frac{i(i+1)}{2}=\frac{(m+1)[(m+1)+1][(m+1)+2]}{6}$

$\sum_{i=1}^{m+1}\frac{i(i+1)}{2}$

$=1+3+...+\frac{m(m+1)}{2}+\frac{(m+1)(m+2)}{2}$

$=\frac{m(m+1)(m+2)}{6}+\frac{(m+1)(m+2)}{2}$

$=\frac{m(m+1)(m+2)}{6}+\frac{3(m+1)(m+2)}{6}$

$=\frac{(m+1)(m+2)(m+3)}{6}$

$=\frac{(m+1)[(m+1)+1][(m+1)+2]}{6}$

所以猜想成立。

# 代码

根据上面的结论，我们很容易写出代码，只需要枚举$m$使得层数最多且$\frac{m(m+1)(m+2)}{6}≤n$即可，代码如下

```cpp
#include<stdio.h>//头文件

int n;

int main(void){
	register int i;//用寄存器更快些
	scanf("%d",&n);//读入
	for(i=1;i<=40;i++)//进行枚举
		if(i*(i+1)*(i+2)/6>n)
			break;//退出循环
	printf("%d\n",i-1);//输出
	return 0;//结束
}
```

## [我的测评记录](https://www.luogu.org/record/show?rid=9188711)

---

## 作者：PC_DOS (赞：0)

这是一道模(Mei)拟(Ju)题，一个比较容易想到的思路是:

1. 建立两个计数器iSum和iLevel，分别表示所需的砖块和已经修建的层数，由于题目已经指定至少有一块砖，因此必定可以建造至少一层，故两个计数器均赋初值1。

2. 开始循环，每次均给iSum加上建造iLevel+1层所需的砖块数，将iSum和总计砖块数比较，若iSum不大于总砖块数，则iLevel的值加一，否则退出循环。

计算第K层所需砖块数的方法即自然数列前K项求和:

```
1+2+3+...+K = K*(K+1)/2
```

故得到代码:

```
#include <iostream>
using namespace std; //头文件和命名空间
inline int GetSumFrom1(int iEnd){ //自然数列前N项求和
	return iEnd*(iEnd + 1) / 2;
}
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	int nCount, iSum=1, iLevel=1; //总砖块数和计数器
	cin >> nCount; //读入总砖块数
	while (1){ //开始枚举
		iSum += GetSumFrom1(iLevel+1); //给iSum加上建造iLevel+1层所需的砖块数
		if (iSum <= nCount) //将iSum和总计砖块数比较
			++iLevel; //若iSum不大于总砖块数，则iLevel的值加一
		else //否则
			break; //退出循环
	}
	cout << iLevel; //输出
	return 0; //结束
}
```

---

## 作者：文·和 (赞：0)

# 应该比较通俗易懂

### 思路 

[高斯求和公式](https://www.luogu.org/blog/127520/cf1095a-ti-xie)已经在这里讲了，代码里就直接用了

用计数器m表示已经使用的砖块数，然后枚举层数i，直到i层符合要求但i+1层不符合时输出即可，注意i每次增加都要加上对应层数的砖块数i*(i+1)/2

根据思路，贴出代码：

```
#include <bits/stdc++.h>
using namespace std;
int m,i,n; 
int main(){
cin>>n;
for(i=1;;i++){  //这里面保证有解所以不用退出
	if((i+1)*i/2+m<=n&&(i+2)*(i+1)/2+m+(i+1)*i/2>n){    
    	
        //(i+1)*i/2+m<=n表示第i层需要的砖块
       
       //(i+2)*(i+1)/2+m+(i+1)*i/2表示i+1层（第i层加上第i+1层新增的）。
		cout<<i;   //如果满足则输出
		return 0;
	}
m+=(i+1)*i/2;  //不满足则加上第i层策砖块数
}
return 0;
}
```


---

