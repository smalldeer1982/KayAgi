# Domino

## 题目描述

**题意简述**

你要用 $1\times 2$ 的多米诺骨牌铺满一个 $4\times n$ 的矩阵使得每条纵向切割线均与骨牌相交。骨牌可以旋转，即可以使用 $1\times 2$ 和 $2\times 1$ 的多米诺骨牌。

每一张骨牌都要上色，为了简化题目，一个小写字母即代表一种颜色，同一颜色的骨牌不能相邻。

请你输出一种满足要求的方案。

## 样例 #1

### 输入

```
4
```

### 输出

```
yyzz
bccd
bxxd
yyaa
```

# 题解

## 作者：Eddie08012025 (赞：9)

## 思路
这题保证有解，不用考虑输出 $-1$ 的情况。

构造方法：

第一行用 `aa` 和 `bb` 交叉输出，如果 $n$ 是奇数，就要在末尾再输出 `z`。

第二行用 `bb` 和 `aa` 交叉输出，如果 $n$ 是奇数，就要在末尾再输出 `z`，组成一个 $2\times1$ 的多米诺骨牌 `cc`，否则不够 $n$ 列。 

第三行先输出一个 `y`，再用 `cc` 和 `dd` 交叉输出，如果 $n$ 是偶数，就要在末尾再输出 `x`。

第四行先输出一个 `y`，组成一个$2\times1$ 的多米诺骨牌 `yy` ，作用是让 `aa` 与 `bb` 和 `cc` 与 `dd` 错位，使得每条纵向切割线均与骨牌相交，再用 `dd` 和 `cc` 交叉输出，如果 $n$ 是偶数，就要在末尾再输出 `x`，组成一个 $2\times1$ 的多米诺骨牌 `xx`，否则不够 $n$ 列。

上面一大段文字你可能看不懂，那么我们用几个例子说明：
```cpp
6
aabbaa //aa与bb交叉输出。
bbaabb //bb与aa交叉输出。
yccddx //用yy错位，cc与dd交叉输出，因为最后只剩1个位置所以用xx补位。
yddccx //dd与cc交叉输出。

5
aabbz //aa与bb交叉输出，因为最后只剩1个位置所以用zz补位。
bbaaz //bb与aa交叉输出。
yccdd //用yy错位，cc与dd交叉输出，最后刚好用完格子。
yddcc //dd与cc交叉输出。
```
思路已经简单明了了吧，上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n; 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n/2;i++){
		if(i%2==1)cout<<"aa";
		else cout<<"bb";
	}if(n%2==1)cout<<"z";
	cout<<"\n";
	for(int i=1;i<=n/2;i++){
		if(i%2==1)cout<<"bb";
		else cout<<"aa";
	}if(n%2==1)cout<<"z";
	cout<<"\ny";
	for(int i=1;i<=(n%2==0?n/2-1:n/2);i++){
		if(i%2==1)cout<<"cc";
		else cout<<"dd";
	}if(n%2==0)cout<<"x";
	cout<<"\ny";
	for(int i=1;i<=(n%2==0?n/2-1:n/2);i++){
		if(i%2==1)cout<<"dd";
		else cout<<"cc";
	}if(n%2==0)cout<<"x";
	return 0;
}
```
# 感谢观看！

---

## 作者：FeiYu32 (赞：6)

## 思路

这题不算难，发现规律之后就很好做了。

跟其他题解的方法类似，也是砌墙法，但是唯一的不同是我把多米诺骨牌立起来摆。那么就只需要把
```
a
a
b
b
```
和
```
b
b
a
a
```
间隔着摆放就行了，不仅不会有相同颜色相邻，使用的颜色也最少，而且不管 $n$ 为多少都影响不到代码的正确性，简直是一举两得。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        if(i%2==1)cout<<"a";
        else cout<<"b";
    }
    cout<<endl;
    for(int i=1;i<=n;i++)
    {
        if(i%2==1)cout<<"a";
        else cout<<"b";
    }
    cout<<endl;
    for(int i=1;i<=n;i++)
    {
        if(i%2==0)cout<<"a";
        else cout<<"b";
    }
    cout<<endl;
    for(int i=1;i<=n;i++)
    {
        if(i%2==0)cout<<"a";
        else cout<<"b";
    }
    cout<<endl;
}

```
完结撒花！

---

## 作者：Wendy_Hello_qwq (赞：2)

[题目传送门。](https://www.luogu.com.cn/problem/CF85A)

[原文食用效果更佳。](https://www.luogu.com/article/kl9yooj8)

## 题意

给定 $n$，让你用 $1 \times 2$ 或 $2 \times 1$ 的多米诺骨牌铺满整个 $4 \times n$ 的矩阵，并且相同的颜色的多米诺骨牌不能相邻。

## 分析

其实只要找到规律，就很好做了，不需要摆放很多种颜色。

比如下面的摆放：

```cpp
aabb
bbaa
aabb
bbaa
```

只要判断一下 $i$ 即可，不管 $n$ 是多少，答案都不会错，是比较简单的解法。

## Code

```cpp
#include <cstdio>
using namespace std;
int n;
int main() {
	scanf ("%d", &n);
	// 竖着摆放多米诺骨牌，就不会导致重复 ，简单又好用 
	for (int i = 1; i <= n; i++) {
		if (i % 2 == 1) printf ("a");
		else printf ("b");
	}
	printf ("\n");
	for (int i = 1; i <= n; i++) {
		if (i % 2 == 1) printf ("a");
		else printf ("b");
	}
	printf ("\n");
	for (int i = 1; i <= n; i++) {
		if (i % 2 == 0) printf ("a");
		else printf ("b");
	}
	printf ("\n");
	for (int i = 1; i <= n; i++) {
		if (i % 2 == 0) printf ("a");
		else printf ("b");
	}
	return 0;
}
```

完结撒花。

作者写题解不易，点个赞再走呗。

---

## 作者：cqbzhr (赞：2)

此为本蒟蒻正式上道的第一篇题解.
看到各个大佬各种千奇百怪的做法，我只能感叹一句：“哎，我太弱了！”
# 进入正题
看完题面，我相信各位大佬都能想到这与生活中的砌墙十分的相似（~~但是本蒟蒻没见过砌墙~~）。
题意是说，要把若干个骨牌拼在一起，使得它可以覆盖一个 $4$ 行 $n$ 列的长方形，并且要让纵切线与骨牌相交，求覆盖方案。
1.  $N$ 为奇数：
分别用 $e,f$ 骨牌放在一至二行的最后一列与三至四行的第一列。第一、二行其余部分用 $a,b$ 骨牌交错填满，并且这两行的 $a,b$ 要错开。第三、四行其余部分用 $c,d$ 骨牌交错填满，并且这两行的 $c,d$ 要错开。说人话就是把它们全部错开。
2. $N$ 为偶数：
第一、四行用 $a,b$ 骨牌交错填满。分别用 $e,f$ 骨牌放在二至三行的第一列与最后一列。第二、三行其余部分用 $c,d$ 骨牌交错填满，并且这两行的 $c,d$ 要错开。说人话就是再在某两行前后都加上小矩阵即可。
# 所以
这个题根本不会出现不存在的情况，根本没必要考虑 $-1$ 。（真是难为了那些~~骗分~~的孩子）
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
	cin>>n;
	if(n==1){
		cout<<"a"<<endl<<"a"<<endl<<"b"<<endl<<"b";
		return 0;
	}
	if(n==2){
		cout<<"aa"<<endl<<"bb"<<endl<<"aa"<<endl<<"bb";
		return 0; 
	}
	if(n==3){
		cout<<"xaa"<<endl<<"xbb"<<endl<<"aax"<<endl<<"bbx";
		return 0;
	}
	if(n%2==0){
		for(int i=1;i<=n/2;i++){
			if(i%2==0) cout<<"aa";
			else cout<<"bb"; 
		}
		cout<<endl;
		for(int i=1;i<=n/2;i++){
			if(i%2==0) cout<<"bb";
			else cout<<"aa"; 
		}
		cout<<endl<<"x";
		for(int i=1;i<n/2;i++){
			if(i%2==0) cout<<"cc";
			else cout<<"dd"; 
		}
		cout<<"y"<<endl<<"x";
		for(int i=1;i<n/2;i++){
			if(i%2==0) cout<<"dd";
			else cout<<"cc"; 
		}
		cout<<"y";
	}
	else{
		n--;
		cout<<"x";
		for(int i=1;i<=n/2;i++){
			if(i%2==0) cout<<"aa";
			else cout<<"bb"; 
		}
		cout<<endl<<"x";
		for(int i=1;i<=n/2;i++){
			if(i%2==0) cout<<"bb";
			else cout<<"aa"; 
		}
		cout<<endl;
		for(int i=1;i<=n/2;i++){
			if(i%2==0) cout<<"cc";
			else cout<<"dd"; 
		}
		cout<<"x"<<endl;
		for(int i=1;i<=n/2;i++){
			if(i%2==0) cout<<"dd";
			else cout<<"cc"; 
		}
		cout<<"x";
	}
	return 0;
}
```


---

## 作者：Misaka_Mik0t0 (赞：2)

看完本题后，不难想到“摆砖”的方法。更详细地说：
- $n$ 为偶数：
```plain
a a b b a a b b
e c c d d c c f
e d d c c d d f
a a b b a a b b
```
规律：第一、四行用 a、b 骨牌交错填满。分别用 e、f 骨牌放在二至三行的第一列与最后一列。第二、三行其余部分用 c、d 骨牌交错填满，并且这两行的 c、d 要错开。

注意事项：f不能换成e，否则 $n = 2$ 时会卡

代码：
```cpp
for(int i=1;i<=n;++i){
	if(i%4==1||i%4==2)printf("a");
	else printf("b");
}
puts("");
//第1行
printf("e");
for(int i=1;i<=n-2;++i){
	if(i%4==1||i%4==2)printf("c");
	else printf("d");
}
printf("f");
puts("");
//第2行
printf("e");
for(int i=1;i<=n-2;++i){
	if(i%4==1||i%4==2)printf("d");
	else printf("c");
}
printf("f");
puts("");
//第3行
for(int i=1;i<=n;++i){
	if(i%4==1||i%4==2)printf("a");
	else printf("b");
}
//第4行
```
- $n$ 为奇数：
```plain
a a b b a a e
b b a a b b e
f c c d d c c
f d d c c d d
```
规律：分别用 e、f 骨牌放在一至二行的最后一列与三至四行的第一列。第一、二行其余部分用 a、b 骨牌交错填满，并且这两行的 a、b 要错开。第三、四行其余部分用 c、d 骨牌交错填满，并且这两行的 c、d 要错开。

代码：
```cpp
for(int i=1;i<=n-1;++i){
	if(i%4==1||i%4==2)printf("a");
	else printf("b");
}
printf("e");
puts("");
//第1行
for(int i=1;i<=n-1;++i){
	if(i%4==1||i%4==2)printf("b");
	else printf("a");
}
printf("e");
puts("");
//第2行
printf("f");
for(int i=1;i<=n-1;++i){
	if(i%4==1||i%4==2)printf("c");
	else printf("d");
}
puts("");
//第3行
printf("f");
for(int i=1;i<=n-1;++i){
	if(i%4==1||i%4==2)printf("d");
	else printf("c");
}
//第4行
```
另一篇题解根本就没写方法、规律。大家看看我的吧。希望管理员能给我通过。

---

## 作者：123456zmy (赞：2)

题意：  
你要用 $26$ 种 $1\times2$ 的骨牌来覆盖一个 $4$ 行 $n$ 列的矩阵，使得每一条纵向割线都会与至少一张骨牌相交。输出任意一种方法（每个小写字母代表一种骨牌）。
___
要求每一条纵向割线都会与至少一张骨牌相交，可以想到是类似于砌墙的操作（~~没见过砖墙的可以去搬一天砖~~），但是一般的墙的两边都会把砖劈成两半再砌上去，~~但是题目不让劈骨牌~~那就强行把一层变成两层，然后边上就可以用立起来的骨牌解决了。

代码：（~~为什么特判的要用 e？我谔谔...为什么还要用 f？因为四个 e 连一起谔到 WA 了~~）
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main()
{
	scanf("%d",&n);
	if(n&1)
	{
		for(int i=0;i<n-1;i++)putchar('a'+(i&2));putchar('e');putchar(10);
		for(int i=0;i<n-1;i++)putchar('b'+(i&2));putchar('e');putchar(10);
		putchar('f');for(int i=0;i<n-1;i++)putchar('a'+(i&2));putchar(10);
		putchar('f');for(int i=0;i<n-1;i++)putchar('b'+(i&2));putchar(10);
	}
	else
	{
		for(int i=0;i<n;i++)putchar('a'+(i&2));putchar(10);
		for(int i=0;i<n;i++)putchar('b'+(i&2));putchar(10);
		putchar('e');for(int i=0;i<n-2;i++)putchar('a'+(i&2));putchar('f');putchar(10);
		putchar('e');for(int i=0;i<n-2;i++)putchar('b'+(i&2));putchar('f');putchar(10);
	}
	return 0;
}
```

---

## 作者：__UrFnr__ (赞：1)

**题目思路**：

找规律！

这道题答案显然不止一种，那我就讲讲其中一种。

答案一共只有 $4$ 行，我们来找找规律，因为说相邻的骨牌颜色不能相同，因此我们可以交替输出颜色，使相邻的骨牌颜色不同。

因此不存在无解情况，根本不需要判断。

这样就好办了，代码如下：


```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int main () {
	cin >> n;
	for (int i = 1; i <= n; i ++) {
		if (i % 2 == 1) cout << 'x';
		else cout << 'y';
	}
	puts ("");
	for (int i = 1; i <= n; i ++) {
		if (i % 2 == 1) cout << 'x';
		else cout << 'y';
	}
	puts ("");
	for (int i = 1; i <= n; i ++) {
		if (i % 2 == 0) cout << 'x';
		else cout << 'y';
	}
	puts ("");
	for (int i = 1; i <= n; i ++) {
		if (i % 2 == 0) cout << 'x';
		else cout << 'y';
	}
	puts ("");
	return 0;
} 
```

---

## 作者：2020luke (赞：1)

# [CF85A Domino](https://www.luogu.com.cn/problem/solution/CF85A) 题解

## 思路解析

题目要求“每条纵向切割线均与骨牌相交”，也就是两行骨牌之间必须错开排放，例如：

```
aabbaabb...
bbaabbaa...
 ccddccdd...
 ddccddcc...
```

但是第三排和第四排前面有空格，就需要一块竖着的骨牌补上。例如：

```
aabbaabb...
bbaabbaa...
eccddccdd...
eddccddcc...
```

不过如果 $n$ 为奇数那么第一，三排的末尾也会有一个空格；而如果 $n$ 为偶数那么就是第二，四排的末尾会有一个空格。所以这时就需要分类讨论了：

- 当 $n$ 为奇数时，我们在第一、二行的末尾加上一个竖着的骨牌。例如：

```
aabbaabbf
bbaabbaaf
eccddccdd
eddccddcc
```

- 当 $n$ 为偶数时，我们在第三、四行的末尾加上一个竖着的骨牌。例如：

```
aabbaabb
bbaabbaa
eccddccg
eddccddg
```

最后我们讨论完了所有的情况，可以上代码了。

## code

顺便说一下，由于我只有两个 `for` 循环，导致我的代码成为了题解区里的最短代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main() {
	cin >> n;
	for(int i = 1; i <= 4; i++) {
		for(int j = 1; j <= n; j++) {
			if(i >= 3 && i <= 4 && j == 1) putchar('f');
			else if(j == n && n % 2 == 1 && i <= 2) putchar('e');
			else if(j == n && n % 2 == 0 && i >= 3 && i <= 4) putchar('g');
			else if(i <= 2 && ((j % 4 >= 1 && j % 4 <= 2) ^ (i == 2))) putchar('a');
			else if(i <= 2) putchar('b');
			else if((j % 4 >= 2) ^ (i == 4)) putchar('c');
			else if(i <= 4) putchar('d');
		}
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：_Maverick_ (赞：0)

## 思路
一看到这道题第一反应就是“砌砖”嘛，但是有有些不一样，这道题可不能和砌砖一样把骨牌劈开，所以我们只能让他竖起来，让我们看几个例子：
```
5
aabbc
bbaac
eccdd
eddcc

6
aabbaa
eccddf
eddccf
aabbaa

11
aabbaabbaac
bbaabbaabbc
fddeeddeedd
feeddeeddee

12
aabbaabbaabb
eccddccddccf
eddccddccddf
aabbaabbaabb
```
答案一共只有 $4$ 行，我们来找找规律，因为说相邻的骨牌颜色不能相同，因此我们可以交替输出颜色，使相邻的骨牌颜色不同。
## 代码

```cpp
#include<iostream>
 
using namespace std;
 
int main()
{
	int n;
	scanf("%d", &n);
	
	if(n % 2 == 0)//n为偶数的情况
	{
		for(int i = 0; i < n / 2; i ++ )
		{
			if(i % 2 == 0) printf("aa");
			else printf("bb");
		}
		printf("\ne");
		for(int i = 1; i < n / 2; i ++ )
		{
			if(i % 2 == 0) printf("cc");
			else printf("dd");
		}
		printf("f\ne");
		for(int i = 1; i < n / 2; i ++ )
		{
			if(i % 2 == 0) printf("dd");
			else printf("cc");
		}
		printf("f\n");
		for(int i = 0; i < n / 2; i ++ )
		{
			if(i % 2 == 0) printf("aa");
			else printf("bb");
		}
	}
	else//n为奇数的情况
	{
		for(int i = 0; i < n / 2; i ++ )
		{
			if(i % 2 == 0) printf("aa");
			else printf("bb");
		}
		printf("e\n");
		for(int i = 0; i < n / 2; i ++ )
		{
			if(i % 2 == 0) printf("bb");
			else printf("gg");
		}
		printf("e\nf");
		for(int i = 0; i < n / 2; i ++ )
		{
			if(i % 2 == 0) printf("dd");
			else printf("cc");
		}
		printf("\nf");
		for(int i = 0; i < n / 2; i ++ )
		{
			if(i % 2 == 0) printf("gg");
			else printf("dd");
		}
	}
	
	return 0;
}
```

---

## 作者：QingDeng_Star (赞：0)

## 思路
妥妥的思维题。

题目说输出 $4$ 行，相邻的多米诺骨牌不能相同，那就一个接一个放，比如第一个放 a，那第二个就放 b，第三个还放 a，这样就可以保证相邻的多米诺骨牌不相同了。
## code

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() 
{
    int n;
	cin>>n;
	for(int i=1;i<=n;i++)
		if(i%2==1)
        	cout<<'x';
		else 
            cout<<'y';
	for(int i=1;i<=n;i++)
		if(i%2==1) 
        	cout<<'x';
		else 
            cout<<'y';
	for(int i=1;i<=n;i++)
		if(i%2==1) 
            cout<<'x';
		else 
            cout<<'y';
    for(int i=1;i<=n;i++)
		if(i%2==1) 
            cout<<'x';
		else 
            cout<<'y';//完全一样的四次
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF85A)

# First 题意

题意是说，要把若干个多米诺骨牌拼在一起，使得它可以覆盖一个 $4$ 行 $n$ 列的长方形，并且要让纵切线与骨牌相交，求覆盖方案。

# Second 分析

根据题意，就有如下方案。

第一种，$n$ 为偶数，那就要交错摆放骨牌如下图

![](https://cdn.luogu.com.cn/upload/image_hosting/6sck5stk.png)

~~手绘，各位见谅。~~

而奇数呢，就是把 `e` 放到上面去即可。

# Third Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
ll n, kkk, bu;
il void ji(){
	for (int i = 1; i < n; i++){
		kkk = i % 4 == 0 || i % 4 == 3;
		cout << (char)(kkk + 'a');
	}
	printf ("e\n");
	for (int i = 1; i < n; i++){
		kkk = i % 4 == 2 || i % 4 == 1;
		cout << (char)(kkk + 'a');
	}
	printf ("e\nf");
	for (int i = 1; i < n; i++){
		kkk = i % 4 == 0 || i % 4 == 3;
		cout << (char)(kkk + 'c');
	}
	printf ("\nf");
	for (int i = 1; i < n; i++){
		kkk = i % 4 == 2 || i % 4 == 1;
		cout << (char)(kkk + 'c');
	}
}
il void ou(){
	for (int i = 1; i <= n; i++){
		kkk = i % 4 == 0 || i % 4 == 3;
		cout << (char)(kkk + 'a');
	}
	printf ("\ne");
	for (int i = 1; i <= n - 2; i++){
		kkk = i % 4 == 0 || i % 4 == 3;
		cout << (char)(kkk + 'c');
	}
	printf ("f\n");
	printf ("e");
	for (int i = 1; i <= n - 2; i++){
		kkk = i % 4 == 1 || i % 4 == 2;
		cout << (char)(kkk + 'c');
	}
	printf ("f\n");
	for (int i = 1; i <= n; i++){
		kkk = i % 4 == 0 || i % 4 == 3;
		cout << (char)(kkk + 'a');
	}
}
int main(){
	scanf ("%lld", &n);
	if (n & 1) ji();
	else ou();
	return 0;
}

```

---

## 作者：IkunTeddy (赞：0)

# 题目大意
生成一个 $4 \times n$ 矩形，由若干 $1 \times 2$ 的小写字母矩形构成，两个同样的小矩形不能相邻，是的每条纵切线与小矩形相交。

# 做法分析
这个题就很想生活中的砌墙。

如果 $N$ 为奇数的话直接让两行错开就行，在空的地方再加上一个 $1\times 2$ 的小矩形，如下：
```
xaabbaa
xbbaabb
ccddccx
ddccddx
```
如果 $N$ 为偶数的话需要再某两行前后都加上小矩阵就能刚好满足条件，如下：
```
aabbaabb
bbaabbaa
xccddccx
xddccddx
```

**这个题根本不会出现不存在的情况，根本没必要考虑 $-1$**。真的无语。
# Code

直接上代码:
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
int main(){
	int n;
	cin>>n;
	if(n==1){
		cout<<"a"<<endl<<"a"<<endl<<"b"<<endl<<"b";
		return 0;
	}
	if(n==2){
		cout<<"aa"<<endl<<"bb"<<endl<<"aa"<<endl<<"bb";
		return 0; 
	}
	if(n==3){
		cout<<"xaa"<<endl<<"xbb"<<endl<<"aax"<<endl<<"bbx";
		return 0;
	}
	if(n%2==0){
		for(int i=1;i<=n/2;i++){
			if(i%2==0) cout<<"aa";
			else cout<<"bb"; 
		}
		cout<<endl;
		for(int i=1;i<=n/2;i++){
			if(i%2==0) cout<<"bb";
			else cout<<"aa"; 
		}
		cout<<endl;
		cout<<"x";
		for(int i=1;i<n/2;i++){
			if(i%2==0) cout<<"cc";
			else cout<<"dd"; 
		}
		cout<<"y";
		cout<<endl;
		cout<<"x";
		for(int i=1;i<n/2;i++){
			if(i%2==0) cout<<"dd";
			else cout<<"cc"; 
		}
		cout<<"y";
	}else{
		n--;
		cout<<"x";
		for(int i=1;i<=n/2;i++){
			if(i%2==0) cout<<"aa";
			else cout<<"bb"; 
		}
		cout<<endl<<"x";
		for(int i=1;i<=n/2;i++){
			if(i%2==0) cout<<"bb";
			else cout<<"aa"; 
		}
		cout<<endl;
		for(int i=1;i<=n/2;i++){
			if(i%2==0) cout<<"cc";
			else cout<<"dd"; 
		}
		cout<<"x"<<endl;
		for(int i=1;i<=n/2;i++){
			if(i%2==0) cout<<"dd";
			else cout<<"cc"; 
		}
		cout<<"x";
	}

	return 0;
}

```


---

