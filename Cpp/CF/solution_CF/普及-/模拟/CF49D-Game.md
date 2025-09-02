# Game

## 题目描述

Vasya and Petya have invented a new game. Vasya takes a stripe consisting of $ 1×n $ square and paints the squares black and white. After that Petya can start moves — during a move he may choose any two neighboring squares of one color and repaint these two squares any way he wants, perhaps in different colors. Petya can only repaint the squares in white and black colors. Petya’s aim is to repaint the stripe so that no two neighboring squares were of one color. Help Petya, using the given initial coloring, find the minimum number of moves Petya needs to win.

## 说明/提示

In the first sample Petya can take squares 1 and 2. He repaints square 1 to black and square 2 to white.

In the second sample Petya can take squares 2 and 3. He repaints square 2 to white and square 3 to black.

## 样例 #1

### 输入

```
6
111010
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
10001
```

### 输出

```
1
```

## 样例 #3

### 输入

```
7
1100010
```

### 输出

```
2
```

## 样例 #4

### 输入

```
5
00100
```

### 输出

```
2
```

# 题解

## 作者：Mr_WA的大号 (赞：13)

天若有情天亦老，人生正道是题解。小学生又来发题解了！

题号：CF49D

难度：★

算法：暴力

这题是非常简单的，只需要把两个相邻的“1”或“0”给整成不一样就好了，通俗的说就是拆CP（偷笑.jpg）

听我这么说，可能99%的小伙伴都想到了模拟，这说明你们已经形成了对算法判断的惯性思维，这很好，能够很快的判断出算法，但在这道题，不需要。

这道题其实我们研究一下就可以发现，最终的串无非是两种，以n=6为例，最终的串要么是“010101”，要么是“101010”，因此我们只需要比对一下这两个串与原串有多少个不同，然后拆CP（注意，不需要手动拆，只要算出来，用公式拆就行了），最后输出这两个串与原串的不同个数中较小的一个就可以了。

说着是晦涩难懂，那么我们来看一下代码⑧：

```c
#include<bits/stdc++.h>

using namespace std;
int n,ans1,ans2;//ans1和ans2分别储存两个串与原串的不同个数
string st;
//看完了定义，你们一定好奇，这两个串在哪呢？不要心急，先往下看
int main()
{
	cin>>n>>st;
	for(int i=0; i<n; i++)
	{
		if(st[i]==i%2+48)ans1++;//我们可以看到，这两个串在某个位置上必然是一个串是'1'，另一个串是'0'，因此，我只需要判断原串在该位置上是1还是0，就可以算出来，假如说第一个位置是0，那就是与“1010101010...”的串有不一样，因此ans1++，反之则自然是与“010101010101...”的串不一样，所以ans2++
		else ans2++;
	}
	cout<<min(ans1,ans2);//输出较小的一个




    return 0;
}
```

温馨提示，代码千万条，AC第一条，若要抄代码，棕名两行泪

那么今天的题解就到这里了，喜欢的朋友们希望多点赞，评论，三连！有不懂的可以评论区提问嗷

---

## 作者：Yo_haor (赞：3)

楼下的dalao都写的很好，但我觉得有点麻烦，接下来看看我的qwq

方法其实是很简单：

#   $\color{red}\text{生 成 子 串}$

没错，就是生成两个子串分别是 0 开头和 1 开头的子串

举个例子：

------------
**7**

**1100010**

生成的子串分别为：1010101和0101010

然后进行一位一位判断。

最后上代码qwq
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;//大家都懂就不说了
int n;
string st;
string s1,s2;//生成的子串
int ans1,ans2;//两个子串和原串不同的个数
int main(){
	cin>>n>>st;
	for(int i=0;i<n;i++)//生成子串
		if(!(i%2))s1+='0';
		else s1+='1';
	s2=s1+'0';
	s1='1'+s1;//两个不同数字的开头
	for(int i=0;i<n;i++)//进行判断，由于这两个子串位位相反，所以只要有一个不同，另一个就会相同
		if(s1[i]!=st[i])ans1++;
		else ans2++;
	cout<<min(ans1,ans2);//输出小的那一个
	return 0;
}
```


---

## 作者：chengni (赞：3)

刚开始还想着要模拟。其实最终一共只有两种01串，只要比较这两种哪个差别更少就可以了。


```cpp
#include<bits/stdc++.h>

using namespace std;

int ar;
char ch;
int br;//第一种
int cr;//第二种

int main(){
	int n;
	cin>>n;	
	int ans1=0;
	int ans2=0;
	for(int i=1;i<=n;i++)
	{
		cin>>ch;
		if(ch=='1') ar=1;
		else ar=0;//读入
		
		if(i%2==1){//构造01串
			br=1;
			cr=0;
		}
		else {
			br=0;
			cr=1;
		}
		if(ar!=br){
			ans1++;
		}
		if(ar!=cr){
			ans2++;
		}
		
	}cout<<min(ans1,ans2);//输出改动少的
	return 0;
}
```

---

## 作者：Great_Influence (赞：0)

题目很简单，可以直接将串塞进bitset中，然后在构造01相间的另一个串，假设这两个串异或以后得到的1的个数为ans，那么答案就是：

$\min(ans,n-ans)$

代码：
```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(i=(a);i<=(b);++i)
#define Forward(i,a,b) for(i=(a);i>=(b);--i)
#define Rep(i,a,b) for(register int i=(a),i##end=(b);i<=i##end;++i)
#define Repe(i,a,b) for(register int i=(a),i##end=(b);i>=i##end;--i)
using namespace std;
template<typename T>inline void read(T &x)
{
	T s=0,f=1;char k=getchar();
	while(!isdigit(k)&&(k^'-'))k=getchar();
	if(!isdigit(k)){f=-1;k=getchar();}
	while(isdigit(k)){s=s*10+(k^48);k=getchar();}
	x=s*f;
}
void file()
{
	#ifndef ONLINE_JUDGE
		freopen("test.in","r",stdin);
		freopen("test.out","w",stdout);
	#endif
}
#define Chkmax(a,b) a=a>(b)?a:(b)
#define Chkmin(a,b) a=a<(b)?a:(b)
const int MAXN=1007;
static int n,ans;
bitset<MAXN>a;
string s;
inline void work()
{
	read(n);
	cin>>s;
	bitset<MAXN>w(s);
	Rep(i,1,n/2)a.set(2*i-1);
	ans=(w^a).count();
	printf("%d\n",min(ans,n-ans));
}
int main()
{
	file();
    work();
	return 0;
}

```

---

