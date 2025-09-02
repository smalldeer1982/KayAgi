# Pythagorean Theorem II

## 题目描述

In mathematics, the Pythagorean theorem — is a relation in Euclidean geometry among the three sides of a right-angled triangle. In terms of areas, it states:

 In any right-angled triangle, the area of the square whose side is the hypotenuse (the side opposite the right angle) is equal to the sum of the areas of the squares whose sides are the two legs (the two sides that meet at a right angle).

The theorem can be written as an equation relating the lengths of the sides $ a $ , $ b $ and $ c $ , often called the Pythagorean equation:

 $ a^{2}+b^{2}=c^{2} $ where $ c $ represents the length of the hypotenuse, and $ a $ and $ b $ represent the lengths of the other two sides.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF304A/dce71d69bec644282a576a6a33bfe17bb5e666a5.png)Given $ n $ , your task is to count how many right-angled triangles with side-lengths $ a $ , $ b $ and $ c $ that satisfied an inequality $ 1<=a<=b<=c<=n $ .

## 样例 #1

### 输入

```
5
```

### 输出

```
1
```

## 样例 #2

### 输入

```
74
```

### 输出

```
35
```

# 题解

## 作者：zhangyuxing (赞：4)

循环判断,时间复杂度O(n^2)

code of c++:

```cpp
#include<cstdio>
#include<cmath>
using namespace std;
int main()
{
	int n,m,i,j,sum=0,b,c,p;//b为直角边，c为斜边
	double a;//sqrt函数返回值为实型
	scanf("%d",&n);
	for(c=1;c<=n;c++)
	for(b=1;b<c;b++)
	{
		p=c*c-b*b;a=sqrt(p);
        if(a==int(a)&&(a<=b))//判整数+去重((a,b)与(b,a)为同一种
		sum++;
	}
	printf("%d",sum);
	return 0;
}
```

---

## 作者：inoichi_lim (赞：0)

直接暴力遍历即可，但是由于涉及到小数运算，所以细节较多。

总体思路：
- 从$1$到$n$遍历$c$。
- 从$1$到$c-1$（**注意这里是$c-1$!**）遍历$b$。
- 设**小数**变量$a$，并且通过一般方法得出$a$（$a=\sqrt{c^2-b^2}$）。
- 如果这个$a=[a]$**并且$a\le b$（去重）**（$[a]=a$向下取整），那么说明合法，方案$+1$。

```cpp
#include<bits/stdc++.h>
#define ns "-1"
#define fs(i,x,y,z) for(ll i=x;i<=y;i+=z)
#define ft(i,x,y,z) for(ll i=x;i>=y;i+=z)
#define ll long long
#define ull unsigned long long
#define db double
#define ms(a,b) memset(a,b,sizeof(a))
#define sz(a) sizeof(a)
using namespace std;
const int rw[]={-1,0,1,0,-1,1,-1,1},cl[]={0,1,0,-1,-1,1,1,-1};
const int N=100001,inf=0x7f7f7f7f;
int n,ans;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	fs(c,1,n,1){
		fs(b,1,c-1,1){
			int q=c*c-b*b;//这里如果不这样过不了样例
			db a=sqrt(q);
			if(a==int(a)&&a<=b) ans++;
		}
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：Arvin2018 (赞：0)

看了题解后放心了，马上$O(n^2)$

为了美化丑陋的if，窝加了一堆空格

## 注：代码中c是指$c^2$，题干中a, b, c在本题解中均为A, B, C

思路：A从1到n，B从a到n 枚举

$C^2 = A^2 + B^2$

```
int( sqrt( double( c ) ) ) * int( sqrt( double( c ) ) )
```
平方根c并向下取整

如果$A^2 + B^2 = C^2$，那么这个运算是等于$C^2$的，否则会向下取整，产生误差

~~然而还是很丑~~
```
#include <bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin >> n;
	int cnt = 0;
    //a，b循环
	for(int a = 1; a <= n; a++){
		for(int b = a; b <= n; b++){
			int c = a*a + b*b;//c
//			cerr << a << " " << b << " " << c << " " << int(sqrt(double(c))) << " " << (int(sqrt(double(c)))*int(sqrt(double(c))) == c )<< " " << (int(sqrt(double(c)))*int(sqrt(double(c))) <= n) << endl;     /////请忽略这段丑陋无比的cerr，我因为它T了一次
			if( int( sqrt( double( c ) ) ) * int( sqrt( double( c ) ) ) == c /*这就是a^2 + b^2 == c^2*/ && int( sqrt( double( c ) ) ) * int( sqrt( double( c ) ) ) <= n * n /*不超过n*n*/ ){//这个if和另一篇题解相比省了一个变量，然鹅十分丑陋
				cnt++;
			}
		}
	} 
	printf("%d", cnt);//窝来个printf皮一下
	return 0;
}

```

---

