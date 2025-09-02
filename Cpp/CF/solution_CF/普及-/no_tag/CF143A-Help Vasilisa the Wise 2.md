# Help Vasilisa the Wise 2

## 题目描述

Vasilisa the Wise from the Kingdom of Far Far Away got a magic box with a secret as a present from her friend Hellawisa the Wise from the Kingdom of A Little Closer. However, Vasilisa the Wise does not know what the box's secret is, since she cannot open it again. She hopes that you will help her one more time with that.

The box's lock looks as follows: it contains $ 4 $ identical deepenings for gems as a $ 2×2 $ square, and some integer numbers are written at the lock's edge near the deepenings. The example of a lock is given on the picture below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF143A/3afffa6690b0a7fee0cca96fe3fb7d95cf7329f2.png)The box is accompanied with $ 9 $ gems. Their shapes match the deepenings' shapes and each gem contains one number from $ 1 $ to $ 9 $ (each number is written on exactly one gem). The box will only open after it is decorated with gems correctly: that is, each deepening in the lock should be filled with exactly one gem. Also, the sums of numbers in the square's rows, columns and two diagonals of the square should match the numbers written at the lock's edge. For example, the above lock will open if we fill the deepenings with gems with numbers as is shown on the picture below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF143A/3d3ced733d775964ba52205e4c988cebde0d133f.png)Now Vasilisa the Wise wants to define, given the numbers on the box's lock, which gems she should put in the deepenings to open the box. Help Vasilisa to solve this challenging task.

## 说明/提示

Pay attention to the last test from the statement: it is impossible to open the box because for that Vasilisa the Wise would need 4 identical gems containing number "5". However, Vasilisa only has one gem with each number from $ 1 $ to $ 9 $ .

## 样例 #1

### 输入

```
3 7
4 6
5 5
```

### 输出

```
1 2
3 4
```

## 样例 #2

### 输入

```
11 10
13 8
5 16
```

### 输出

```
4 7
9 1
```

## 样例 #3

### 输入

```
1 2
3 4
5 6
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
10 10
10 10
10 10
```

### 输出

```
-1
```

# 题解

## 作者：LRL65 (赞：5)

一道**暴力题**

先枚举每个点，后判断

时间复杂度：o(9⁴)

### AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	int r1,r2,c1,c2,d1,d2;
	cin>>r1>>r2>>c1>>c2>>d1>>d2;
	for(int i1=1;i1<=9;i1++) {
		for(int i2=1;i2<=9;i2++) {
			for(int i3=1;i3<=9;i3++) {
				for(int i4=1;i4<=9;i4++) {
					if((i1+i2==r1)&&(i3+i4==r2)&&(i1+i3==c1)&&(i2+i4==c2)&&(i1+i4==d1)&&(i2+i3==d2)&&(i1!=i2)&&(i1!=i3)&&(i1!=i4)&&(i2!=i3)&&(i2!=i4)&&(i3!=i4)) {
						cout<<i1<<" "<<i2<<endl<<i3<<" "<<i4;
						return 0;
					}
				}
			}
		}
	}
	cout<<"-1"<<endl;
	return 0;
}

```
如有帮助，请记得~~点赞~~。

最后膜拜下dalao：orz。

---

## 作者：洺谷 (赞：3)

这题数据不大。

用深搜即可。

超过每行每列及每条对角线上两个棋子的数之和就回溯。

然后AC了

---

## 作者：yzy041616 (赞：2)

[题目传送门](/problem/CF143A)

## Part.1 题目

有 $2\times 2$ 的 $4$ 个格子，给出两两的和，求这 $4$ 个格子里的数。如果没有整数解，或者有相同的数，或者解里有数不在 $1$ 到 $9$ 之内的话，都输出`-1`。

## Part.2 思路

这题我之前做过。我想分享一下我自己的 $O(1)$ 的算法。

先假设这 $4$ 个数分别是 $a,b,c,d$ ，然后先把六个方程写出来：

$a+b=r_1\space(1)$  
$c+d=r_2\space(2)$  
$a+c=c_1\space(3)$  
$b+d=c_2\space(4)$  
$a+d=d_1\space(5)$  
$b+c=d_2\space(6)$

我们把 $(1)$ 和 $(2)$ 加起来，$(3)$ 和 $(4)$ 加起来，$(5)$ 和 $(6)$ 加起来，发现左边都等于 $a+b+c+d$，右边分别是 $r_1+r_2$，$c_1+c_2$，$d_1+d_2$，所以这三个数得相等，如果不等的话，就无解了。

然后我们拿 $(1)$ 减去 $(3)$，得到 $b-c=r_1-c_1$。然后又有 $b+c=d_2$，所以 $b$ 和 $c$ 可以直接解出来了。这里注意判断 $r_1-c_1$ 和 $d_2$ 的奇偶性得要相等，如果不等的话就无整数解。

有了 $b$ 和 $c$，剩下的 $a$ 和 $d$ 就不难求出来了。

这时，我们需要检验一下 $(4)$ 和 $(5)$ 是否也都成立。

这是成立的。这就是第一步的作用。第一步我们检验了 $r_1+r_2=c_1+c_2=d_1+d_2$，所以当 $a+b=r_1$，$c+d=r_2$，$a+c=c_1$，$b+c=d_2$ 都成立的时候，$b+d=a+b+c+d-(a+c)=r_1+r_2-c_1=c_1+c_2-c_1=c_2$ 。同样，$a+d=a+b+c+d-(b+c)=r_1+r_2-d_2=d_1+d_2-d_2=d_1$。

最后注意判断解是否符合条件，即：
* 两两不等
* 在 $1$ 到 $9$ 之间

注意输出格式。

## Part.3 代码

```cpp
#include<iostream>
using namespace std;
/*
d1 c1 c2 d2
r1  a  b
r2  c  d
*/
int main(){
	int r1,r2,c1,c2,d1,d2,a,b,c,d;
	cin>>r1>>r2>>c1>>c2>>d1>>d2;
	bool possible=1;
	if(r1+r2!=c1+c2||r1+r2!=d1+d2||c1+c2!=d1+d2)possible=0;//都是a+b+c+d 
	int b_minus_c=r1-c1;//b-c=(a+b)-(a+c)=r1-c1
	if((b_minus_c+d2)&1)possible=0;//判断奇偶性
	b=(d2+b_minus_c)>>1;
	c=d2-b;//求解b、c
	a=r1-b;
	d=r2-c;
	if(a==b||a==c||a==d||b==c||b==d||c==d)possible=0;
	if(a<=0||b<=0||c<=0||d<=0)possible=0;
	if(a>9||b>9||c>9||d>9)possible=0;//最后的一堆判断
	if(possible)cout<<a<<" "<<b<<endl<<c<<" "<<d;//这一步错了你就前功尽弃了
	else cout<<-1;
}
```

---

## 作者：chenlingxi (赞：0)

显然只有4个空

那么直接10^4次枚举每个点的值

然后判断可行性即可

---

