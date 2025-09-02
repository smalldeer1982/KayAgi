# Shell Game

## 题目描述

Bomboslav likes to look out of the window in his room and watch lads outside playing famous shell game. The game is played by two persons: operator and player. Operator takes three similar opaque shells and places a ball beneath one of them. Then he shuffles the shells by swapping some pairs and the player has to guess the current position of the ball.

Bomboslav noticed that guys are not very inventive, so the operator always swaps the left shell with the middle one during odd moves (first, third, fifth, etc.) and always swaps the middle shell with the right one during even moves (second, fourth, etc.).

Let's number shells from $ 0 $ to $ 2 $ from left to right. Thus the left shell is assigned number $ 0 $ , the middle shell is $ 1 $ and the right shell is $ 2 $ . Bomboslav has missed the moment when the ball was placed beneath the shell, but he knows that exactly $ n $ movements were made by the operator and the ball was under shell $ x $ at the end. Now he wonders, what was the initial position of the ball?

## 说明/提示

In the first sample, the ball was initially placed beneath the middle shell and the operator completed four movements.

1. During the first move operator swapped the left shell and the middle shell. The ball is now under the left shell.
2. During the second move operator swapped the middle shell and the right one. The ball is still under the left shell.
3. During the third move operator swapped the left shell and the middle shell again. The ball is again in the middle.
4. Finally, the operators swapped the middle shell and the right shell. The ball is now beneath the right shell.

## 样例 #1

### 输入

```
4
2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
1
1
```

### 输出

```
0
```

# 题解

## 作者：The_Power_of_Pigeon (赞：23)

# 超强暴力！

130+行暴力代码怒A黑题~~（虽然是恶意评价上去的）~~

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
#include <cmath>
#include <string>
#include <cstring>
#include <queue>
#include <stack>
#include <map>
#include <list>
#include <deque>
#include <climits>
#include <algorithm>
#include <cstdlib>
#define ll long long
#define MOD 1000000007
#define N 1000100    //我的头文件们

ll bianliang,youyigebianliang;//奇怪的变量名

void hanshu()  //奇怪的函数名
{
	cin>>bianliang;
	bianliang%=6;  //6次一循环，%6就行
	cin>>youyigebianliang;
}

int main()
{
 	hanshu();
    //大暴力开始！
	if (bianliang==0)
 	{
 		cout<<youyigebianliang<<endl;
 		return 0;
 	}
 	if (bianliang==1)
 	{
	 	if (youyigebianliang==0)
 		{
 			cout<<1<<endl;
 			return 0;
 		}
 		if (youyigebianliang==1)
 		{
 			cout<<0<<endl;
 			return 0;
 		}
 		if (youyigebianliang==2)
 		{
 			cout<<2<<endl;
 			return 0;
 		}
 		
 	}
 	if (bianliang==2)
 	{
	 	if (youyigebianliang==0)
 		{
 			cout<<1<<endl;
 			return 0;
 		}
 		if (youyigebianliang==1)
 		{
 			cout<<2<<endl;
 			return 0;
 		}
 		if (youyigebianliang==2)
 		{
 			cout<<0<<endl;
 			return 0;
 		}
 		
 	}
 	if (bianliang==3)
 	{
	 	if (youyigebianliang==0)
 		{
 			cout<<2<<endl;
 			return 0;
 		}
 		if (youyigebianliang==1)
 		{
 			cout<<1<<endl;
 			return 0;
 		}
 		if (youyigebianliang==2)
 		{
 			cout<<0<<endl;
 			return 0;
 		}
 		
 	}
 	if (bianliang==4)
 	{
	 	if (youyigebianliang==0)
 		{
 			cout<<2<<endl;
 			return 0;
 		}
 		if (youyigebianliang==1)
 		{
 			cout<<0<<endl;
 			return 0;
 		}
 		if (youyigebianliang==2)
 		{
 			cout<<1<<endl;
 			return 0;
 		}
 	}
 	if (bianliang==5)
 	{
	 	if (youyigebianliang==0)
 		{
 			cout<<0<<endl;
 			return 0;
 		}
 		if (youyigebianliang==1)
 		{
 			cout<<2<<endl;
 			return 0;
 		}
 		if (youyigebianliang==2)
 		{
 			cout<<1<<endl;
 			return 0;
 		}
 		
 	}
    //我来自if神教
 	return 0;
}
```

蒟蒻第一篇题解……23333

---

## 作者：_YRH_ (赞：14)

## 题目翻译
给你三张牌0，1，2。  
最初选一张，然后依次进行n次交换，交换规则为：中间一张和左边的一张，中间一张和右边一张，中间一张和左边一张......  
最后问选的那张在哪个位置。  
## 题目分析
非常简单的模拟就好，定义一个数组预处理即可，可以发现每6个一个循环。  
## 代码如下，不要抄袭哟~
```
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

int i,j,k,m,n;
int a[101][101]={{0,1,2},{1,0,2},{1,2,0},{2,1,0},{2,0,1},{0,2,1},{0,1,2}};//预处理6种可能情况

int main(){
	scanf("%d%d",&n,&m);//输入
	n%=6;//每6个一循环
	printf("%d",a[n][m]);//输出
	return 0;
}
```

---

## 作者：nonanalyzer (赞：7)

怎么都是打表的和数组模拟的啊 ~~很浪费内存的知不知道？~~

翻译有点小问题。题目大意：
>有一个小球和三个贝壳，球一开始被放在某个贝壳中。第奇数次操作是把左贝壳和中贝壳交换（带着里面的小球，如果有的话），第偶数次操作是把右贝壳和中贝壳交换。现在知道操作次数和小球最后的位置，问最初小球被放在哪里。

手动模拟一下就能发现，不管小球最初放在哪个位置，经过6次操作后小球就回到了原来的位置，并且之后的操作也一模一样（第7次等同于第1次，依此类推）。

有这个性质，n又这么大，不mod却待怎的？mod之后n<6，不模拟又待怎的？

#### 模拟的方式：

- 交换两次就等同于没有交换，所以我们以小球在x为初始状态倒着操作一遍，小球最后的位置也就是题目所问的最初位置。（别的大佬都是正着模拟，蒟蒻我打算另辟蹊径 ~~怕重复解法过不了审核，管理大大放我一马~~
- 以0,1,2表示左中右，x表示当前位置，那么左中互换就是x^=1（0^1==1，1^1==0），右中互换就是x^=3（1^3==2，2^3==1）。前提是x需要被换。

于是我们得到了只需两个变量的模拟！下面上代码：

```cpp
#include<cstdio>
int n,x;
int main(){
    for(scanf("%d%d",&n,&x),n%=6;n;--n) n&1?(x^2?x^=1:x):(x?x^=3:x);
    // 此处x^2等同于x!=2，因为只有x==2时x^2的值才是0，为假。
    // 同样的，for里的n和后面那个x等同于n!=0和x!=0。这只是个人习惯。
    return printf("%d\n",x),0;
}
```
有什么语言可以像C++一样简洁而优雅呢？

~~有什么语言可以像C++一样六行过紫题呢？（不打表）~~

---

## 作者：大头菜赛高！ (赞：5)

O(n)做法

233
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#pragma GCC optimize(3)
using namespace std;
inline int rd(){
    int ret = 0, f = 1; char ch;
    while(!isdigit(ch = getchar())) if(ch=='-') f = 0; ret = ch^48;
    while( isdigit(ch = getchar())) ret = (ret<<1) + (ret<<3) + (ch^48);
    return f ? ret : -ret;
}
int a=0,b=1,c=2;
void yi() {
	int d=a;
	a=b;
	b=d;
}
void er(){
	int g=c;
	c=b;
	b=g;
}
int f[5];
bool dd=0;
int main(){
	int n,m;
	int sd=1;
	n=rd();
	m=rd();
	for(int i=1;i<=n;i++){
		if(dd==0){
			yi();
			dd=1;
		}
		else if(dd==1) {
			er();
			dd=0;
		}
	}
	f[0]=a;
	f[1]=b;
	f[2]=c;
	cout<<f[m];
	return 0;
}
```

---

## 作者：艾恩葛朗特 (赞：4)

我们老师有一句名言————

**复杂的问题简单写，简单的问题复杂写**

## 于是...

25行的蒟蒻前来报道

```cpp
#include<cstdio>
#include<string>
using namespace std;

const int a[6][3]={{0,1,2},{1,0,2},{1,2,0},{2,1,0},{2,0,1},{0,2,1}};//表越大，分越多 
int n,m;

int read()//快读 
{
	int x = 0, f = 1;
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar())
	if (ch == '-') f = -1;
	for (; isdigit(ch); ch = getchar())
	x = x * 10 + ch - '0';
	return x * f;
}

int main()
{
	n=read();
	m=read();
	printf("%d",a[n%6][m]);//6个一个循环，所以n%6 
	return 0;
}
```

---

## 作者：xyzhouh (赞：3)

## ！！你看题目翻译你就输了
	
    题目描述；
    Bomboslav喜欢在他的房间从窗外看小伙子们在外面玩著名的贝壳游戏。
    整个游戏需要两个人玩： 一个操作员，一个玩家。
    操作者将一个小球任意放进他的三个相似不透明的贝壳里。
    然后他通过 交换两个瓶子来让玩家猜那个瓶子里有小球。
    Bomboslav注意到那些家伙不是非常的独出心裁，
    所以操作者单数次只会将左边的贝壳和中间的贝壳交换
    （例如第1，第3，第5次。）
    ，偶数次只会将中间的贝壳和右边贝壳交换
    （例如；第2，第4 次）。 
    让我们把贝壳的位置从左到右定义为0,1,2。 
    如此，左边贝壳被标号 0，中间标号1，右边标号2。 
    Bomboslav已经错过了他们游戏的开始。
    不过他准确地知道操作者移动了n步和小球现在在哪 个位置。
    现在他想知道，小球最初的位置是什么？

输入格式； 
第一行输入n（n1<=n<=2*10 9） ——操作者移动的步数。
第二行包括一个x(0<=x<=2)——小球在n步操作后被发现时的位置。

输出格式； 输出 0~2——小球开始被放置的位置。 
## SO你只需要模拟就好

将情况模拟一下

    0,1,2
    1,0,2
    1,2,0
    2,1,0
    2,0,1
    0,2,1
    0,1,2

所以每六次一循环，%6就好了
代码如下：
```cpp
#include<iostream>
using namespace std;
int n,x;
int o[100]={0,1,1,2,2,0,0};
int l[100]={1,0,2,1,0,2,1};
int r[100]={2,2,0,0,1,1,2};
int main(){
	std::ios::sync_with_stdio(false);//关闭同步流，可以使cin更快 
	cin>>n>>x;
	if(x==0) cout<<o[n%6];
	else
	if(x==1) cout<<l[n%6];
	else cout<<r[n%6];
	return 0;
} 
```


---

## 作者：World_Creater (赞：1)

~~一看就是恶评上去的紫题~~  
先定义吧
```cpp
int a[3]={0,1,2},n,m;
cin>>n>>m;
```

这题大致有两个做法  
1.模拟  
根据题目意思，我们大致有这个思路：用
``` cpp
for(int i=0;i<=n;i++)
```
当 $ n\ mod\ 2 !=0 $时，交换$a_0,a_1$  
否则交换$a_1,a_2$  
所以可得此代码
```cpp
#include<bits/stcd++.h>
using namespace std;
void swap(int &a,int &b)//交换函数
{
    int t=a;
    a=b;
    b=t;
}
int main()
{
    int a[3]={0,1,2};
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        if(i%2!=0)//如果循环了奇数次，就交换a[0]&a[1]
        swap(a[0],a[1]);
        else swap(a[1],a[2]);//否则交换a[1]&a[2]
    }
    cout<<a[m];//输出当前值
    return 0;
}
```
but,这个出题人太毒瘤了，$O(N)$的效率也会TLE（~~估计这就是紫题的原因吧~~至少蒟蒻的我还没有想出解决的方法QWQ）

2.找规律  
我们交换时，不难发现一个规律
```cpp
{{0,1,2},{1,0,2},{1,2,0},{2,1,0},{2,0,1},{0,2,1}}
//之后再以{0,1,2}开始循环
```
~~小学生都知道这是周期问题~~  
所以%%%
```cpp
#include<bits/stcd++.h>
using namespace std;
int main()
{
    int a[7][4]={{0,1,2},{1,0,2},{1,2,0},{2,1,0},{2,0,1},{0,2,1}},n,m;
    cin>>n>>m;
    cout<<a[n%6]/*6个1循环,mod 6*/[m];
}
```


---

## 作者：⚡GG⚡ (赞：1)

# [同步题解](https://www.cnblogs.com/Garbage-Only-one/p/10350970.html)

### 题目翻译(可能有童鞋没读懂题面上的翻译)
https://www.cnblogs.com/Garbage-Only-one/p/10350970.html)
>给你三张牌0，1，2。
最初选一张，然后依次进行n次交换，交换规则为：中间一张和左边的一张，中间一张和右边一张，中间一张和左边一张......
最后问牌`x`在哪个位置。

OK懂了吗？这就是样例中两个数的来历QAQ。

## 然后我们来找找规律：

我们可以发现：`0,1,2`这三个数可以经过变化变成如下的情况：
```
{0,1,2},{1,0,2},{1,2,0},{2,1,0},{2,0,1},{0,2,1},
//上为六种情况。
{0,1,2}
//最后一个循环。
```

我们把它预处理一下，再看看`x`对应的是哪一种组合，输出该组合的`0/1/2`即可；

## 话不多说，上代码！
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10][5]={{0,1,2},{1,0,2},{1,2,0},{2,1,0},{2,0,1},{0,2,1}};		//六种情况
int mian()
{
	int n,m;
	cin>>n>>m;
	cout<<a[n%6][m]<<endl;		//n%6即为对应情况，m对应x。
	return 0;
}
```

---

## 作者：RainFestival (赞：1)

对于这道题我们可以用疯狂的打表的方法（好像此题恶意评分）

因为n每6个一循环

代码？？？

```pascal
var
  n,k:longint;
begin
  readln(n);
  readln(k);
  n:=n mod 6;
  if (n=0) and (k=0) then writeln(0);
  if (n=0) and (k=1) then writeln(1);
  if (n=0) and (k=2) then writeln(2);
  if (n=1) and (k=0) then writeln(1);
  if (n=1) and (k=1) then writeln(0);
  if (n=1) and (k=2) then writeln(2);
  if (n=2) and (k=0) then writeln(1);
  if (n=2) and (k=1) then writeln(2);
  if (n=2) and (k=2) then writeln(0);
  if (n=3) and (k=0) then writeln(2);
  if (n=3) and (k=1) then writeln(1);
  if (n=3) and (k=2) then writeln(0);
  if (n=4) and (k=0) then writeln(2);
  if (n=4) and (k=1) then writeln(0);
  if (n=4) and (k=2) then writeln(1);
  if (n=5) and (k=0) then writeln(0);
  if (n=5) and (k=1) then writeln(2);
  if (n=5) and (k=2) then writeln(1);
end.
```
时间858ms,空间0.01mb,代码长度0.75kb

谢谢大大大佬观赏

---

## 作者：CobaltChloride (赞：1)

```
可得每六次为一循环,然后就好做了

#include<bits\stdc++.h>
using namespace std;
int card[6][3]={{0,1,2},//第0次
{1,0,2},//第1次
{1,2,0},//第2次
{2,1,0},//第3次
{2,0,1},//第4次
{0,2,1}};//第5次
int n,x;
int main(){
    cin>>n>>x;
    cout<<card[n%6][x];//输出%6后结果即可
    return 0;
}
```

---

## 作者：opened (赞：1)

找找规律：

我们可以发现：$0,1,2$ 这三个数可以经过变化变成如下的情况：

```
{0,1,2},{1,0,2},{1,2,0},{2,1,0},{2,0,1},{0,2,1},
//上为六种情况。
{0,1,2}
//最后一个循环。
```

我们把它预处理一下，再看看 $x$ 对应的是哪一种组合，输出该组合的 $0/1/2$ 即可；

------------
```
    #include<iostream>
    #include<cstdio>
    using namespace std;
    int n,a[4]={0,1,2};
    int main(){
        scanf("%d",&n);
        n%=6;
        for(int i=1;i<=n;i++)
            if(i%2) swap(a[0],a[1]);
            else swap(a[1],a[2]);
        scanf("%d",&n);
        printf("%d\n",a[n]);
        return 0;
    }
```

---

## 作者：赤霞QvQ (赞：1)

## 找呀找呀找规律，找到一个好规律……

根据题意，可以找规律：

```cpp
  次数        顺序          说明
   0          012       一开始的顺序
   1          102       第一次把第一位和第零位互换即1和0互换
   2          120       第二次把第一位和第二位互换即0和2互换
   3          210       第三次把第一位和第零位互换即1和2互换
   4          201       第四次把第一位和第二位互换即0和1互换
   5          021       第五次把第一位和第零位互换即2和0互换
   6          012       第六次把第一位和第二位互换即1和2互换，得到第0次的顺序！！！！
   …           …
```

故我们便可以得到一个以$6$为单位的规律，建个数组结束！

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x;
string a[6]={"012","102","120","210","201","021"};    //建string数组，也可以建int数组，个人更喜欢string
int main()
{
	cin>>n>>x;
	cout<<a[n%6][x]<<endl;
	return 0;
}
```
$AC!!!!!!!!!!!!!!!!!!!!$


---

## 作者：至成天下 (赞：0)

我们可以发现结果是六个一循环

所以可以先将n%6再暴力

~~敢说这是暴力最短代码~~

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x;
int a[3]={0,1,2};//初始数组
int main(){
	cin>>n>>x;
	n%=6;//六个循环剪掉
	for(int i=1;i<=n;++i){
		if(i%2)swap(a[1],a[0]);//如果是第奇数次操作交换中间和左边
		else swap(a[1],a[2]);//偶数次交换中间和右边
	}
	cout<<a[x]<<endl; //输出
return 0;
}

```


---

