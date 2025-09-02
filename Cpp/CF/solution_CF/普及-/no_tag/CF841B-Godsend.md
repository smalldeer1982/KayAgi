# Godsend

## 题目描述

### 翻译

有两个人，他们面对一个数组，轮流取数组里的数， 第一个取的人要在这个数组里选择一个长度非零的子段，且其和为奇数，这个人要把他选定的子段删掉，并把原子段黏合。而第二个人的操作跟第一个人类似，只是和要是偶数。胜负的判定就是谁最先没法行动谁就输。

## 样例 #1

### 输入

```
4
1 3 2 3
```

### 输出

```
First
```

## 样例 #2

### 输入

```
2
2 2
```

### 输出

```
Second
```

# 题解

## 作者：__白衣渡江__ (赞：1)

好题。

首先，很容易发现偶数没有意义（自行思考为什么），也就是只用考虑奇数。

如果没有奇数那先手就无法行动必败。

如果有奇数个奇数那先手显然直接赢了（全取）。

否则，先手取得只剩一个奇数，此时后手肯定取不动这个奇数。下回合先手就胜利了。

因此，**除非全是偶数，否则先手必胜。**

因此问题被转化为了找奇数。

然后就很简单了，上代码，不懂私信：

```py
input()
for x in input().split():
    if int(x)%2:
        print('First')
        exit()
print('Second')
```
Over.

祝大家AC！

---

## 作者：封禁用户 (赞：1)

其实这道题很简单。

假如输入的数中有奇数，就输出"First"，否则输出"Second"。

**原因：**

- 第一种情况：

  这堆数里有奇数个奇数。
   
  例如：
    ```
   1 2 2 2 2
    ```
  第一个人一次取完即可获胜。
  
- 第二种情况：

  这堆数里有偶数个奇数。
  
  例如：
  
  ```
   1 1 2 2 2
  ```
  第一次：第一个人取$1$，第二个人取$2$。
  
  第二次：第一个人取完即可获胜。

- 第三种情况：

  这堆数里只有偶数。
  
  例如：
  ```
   2 2 2 2 2
  ```
  很明显，第一个人根本取不了，所以第二个人获胜。
  
根据上面三种情况，由此可知假如输入的数中有奇数，第一个人就一定能赢，否则，第二个人赢。

$Code:$

```cpp
#include<cstdio>
using namespace std;
inline int read(){
   long long s=0;bool w=1;char ch=getchar();
   while(ch<'0' || ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0' && ch<='9')s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int n,a; 
int main()
{
	n=read();
	while(n--){
		a=read();
		if(a%2){//判断是否为奇数。
			printf("First");
			return 0;
		}
	}
	printf("Second");//如果没有奇数，则输出"Second"。
	return 0;
}
```


---

## 作者：rfsfreffr (赞：1)

这题第一眼看去还是蛮懵逼的，其实就是就是判断谁只能先出手。

其他的不好判断，想当然的就把所有的都加起来判断了。

# 代码#1：
~~~
#include<bits/stdc++.h>
#define for_int register int
#define endl '\n'
#define ll long long
#define ld long double
#define op operator
#define max(a, b)  (!((a) < (b)) ? (a) : (b))
#define min(a, b)  ((a) < (b) ? (a) : (b))
#pragma GCC optimize(3)//一些优化
#pragma GCC diagnostic error "-std=c++14"
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
using namespace std;
int n;
ll sum=0;
int x;
int main(){
	cin>>n;
	for(for_int i=1; i<=n; i++){
		cin>>x;//累加
		sum+=x;
	}
	if(x%2==0) cout<<"Second"<<endl;
	else cout<<"First";
    return 0;
}
~~~
~~然而第13个点WA了~~

重新正视题面，再次思考问题

~~才发现我把翻译中的没看成了设~~

可是我还是不怎么看不懂翻译出来的题意，然后就去百度翻译了一下:

~~~
leha闲的蛋疼找到了一个由n个整数组成的数组。看着它，他想出了一个游戏。两个玩家在阵列上玩游戏。玩家一个一个移动。第一个玩家可以选择一个具有奇数和的非零长度的子集进行移动，然后将其从数组中移除，然后将其余部分粘在一起形成一个数组，游戏继续进行。第二个玩家可以用一个偶数和的非零长度的子集并将其移除。如果双方都打得最好，谁会赢？
~~~
这不是博弈论嘛。(就是找规律)

我对first的策略是这样的:

1.想办法使自己取完后只剩下一个奇数,这样second就无法操作

2.或者全部的和为奇数，于是全取，就win了

于是就可以分类讨论了:

1.如果所有的$a_i$都是偶数，second肯定赢

2.如果有偶数个奇数，first可以把数列取得只剩下一个奇数，first肯定win

3.如果有奇数个奇数，所有的$a_i$之和为奇数，于是全取，first肯定win

总结2,3可以确定只要数列中有奇数first肯定win

于是就可以愉快的打代码了~~QAQ~~

# 代码#2:
~~~
#include<bits/stdc++.h>
#define for_int register int
#define endl '\n'
#define ll long long
#define ld long double
#define op operator
#define max(a, b)  (!((a) < (b)) ? (a) : (b))
#define min(a, b)  ((a) < (b) ? (a) : (b))
#pragma GCC optimize(3)//一些优化
#pragma GCC diagnostic error "-std=c++14"
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
using namespace std;
int n,a[1000001];
ll sum=0;
int x;
int main(){
	cin>>n;
	int f=0;
 	for(for_int i=1; i<=n; i++){//读入
		cin>>a[i];
		if(a[i]%2!=0){//如果有奇数first肯定win
			cout<<"first"<<endl;
			return 0;
		}
	}//如果都是偶数second肯定win
	cout<<"Second"<<endl;
   return 0;
}
~~~


---

## 作者：liuyifan (赞：1)

看到这道题还没人写题解,那我就写一个吧。

这道题可以转化为输入一个数组,如果数组里有奇数则输出First,否则输出Second。

因为第一个人总是先取和为奇数的数组,从贪心的角度考虑每次只取一个一定会坚持到最后。从而验证了算法的正确性。

code:
```cpp
#include<bits/stdc++.h>
#define ll long long
#define reg register//据说能加速,只能在函数内使用,不能开全局
ll n,a
int main()
{
    scanf("%lld",&n);
    for(reg ll i=1;i<=n;i++)
	{
        scanf("%lld",&a);
		if(a%2)//判断奇数
		{
			puts("First");
			exit(0);//exit(0)在main函数里的作用相当于return 0
			在其他函数里会直接结束整个程序,在搜索的结束等地方经常有用
        }
    }
    puts("Second");//puts据说比printf快,在输出后会自动换行
}
```
拒绝抄袭,共建和谐洛谷

---

## 作者：xgwpp6710 (赞：1)

分析题目之前，我们先来复习一下小学数学：如何判断一组数之和的奇偶性？

其实很简单，就是看这组数中奇数数量的奇偶性，有奇数个奇数则和为奇数，有偶数个奇数则和为偶数，与偶数的数量无关。~~如果连这个都不知道，这题是切不了的，同时建议返回小学重新学一遍。~~

好，现在进入正题。首先偶数是不用管的，不会影响和的奇偶性，因此不用管它。只需考虑数列中的奇数。

如果有奇数个奇数，第一个人直接取完结束。

如果有偶数个奇数（不能是0个奇数），第一个人取剩1个奇数（和若干个偶数），第二个人没有取法，最后一个奇数会被第一个人连带剩下的偶数取完（或者只剩下那个奇数，第二个人取不了了）。

综上，只要有奇数，就是第一个人获胜。

代码：
```cpp
#include<cstdio>
int n,a;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a);
		if(a%2)
		{
			printf("First");//只要有奇数就是第一个人赢，因此结束，可以return 0了
			return 0;
		}
	}
	printf("Second");//能到这步，就是没有奇数，第一个人上来就取不了，第二个人赢
	return 0;
}
```
Update：原文有错误，已修改。

---

## 作者：Daidly (赞：0)

- 首先，来点小学生都会的东西：

$1.$奇数+奇数=偶数

$2.$奇数+偶数=奇数

$3.$偶数+偶数=偶数

- 由此，我们可以往下推一下：

$1.$偶数+奇数+......+奇数（偶数个奇数）=偶数

$2.$奇数+偶数+......+偶数（奇数有一个偶数有多个）=奇数+偶数=奇数

$3.$偶数+偶数+......+奇数+奇数+......+奇数（偶数个奇数，偶数）=偶数

-  当奇数的个数为奇数的时候，因为奇数乘奇数等于奇数，所以第一个人全部取完就可以了。

- 当奇数的个数为偶数个时，因为第一个人要取其数，第二个人要取偶数，只需要让给第二个人一个基数就可以了，所以我们可以取偶数减一个基数，加上剩下的偶数。

- 综上所述，无论奇数的个数是多少个，只要存在奇数第一个人就肯定赢。

代码：
```
#include<bits/stdc++.h>//期末考试没考好，我**！ 
using namespace std;
int n;
string a;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]%2!=0)
		{
			cout<<"First"<<endl;
			return 0;
		}
	}
	cout<<"Second"<<endl;
	return 0;
}
```



---

## 作者：williamlyz (赞：0)

[原题链接qwq](https://www.luogu.com.cn/problem/CF841B)

**题意**

有两个人，他们面对一个数组，轮流取数组里的数， 第一个取的人要在这个数组里选择一个长度非零的子段，且其和为奇数，这个人要把他选定的子段删掉，并把原子段黏合。而第二个人的操作跟第一个人类似，只是和要是偶数。谁按指定要求取不了数谁就输。第一个人赢输出“First”，第二个人赢输出“Second”。

**思路**

这道题仔细想一下思路就出来了。

首先我们考虑一号，他取得数的和必须为奇数，我们可以用到小学的知识奇偶性判断：

> 奇数 $=$ 偶数 $+$ 奇数

也就是说如果一号想赢，这个数组里必须有奇数，否则二号获胜。

然后我们来考虑在有奇数的前提下，二号是否可能获胜，有两种情况：

$1.$ 有奇数个奇数：一号获胜。因为“奇数个奇数为奇数”，一号一次取走所有数即可。

$2.$ 有偶数个奇数：还是一号获胜。举个例子：有两个奇数；第一轮：一号取走一个，二号取走几个偶数（他不能取剩下的奇数因为“奇数个奇数为奇数”，“偶数加奇数为奇数”，而二号要凑偶数所以他不能拿奇数）；第二轮：一号拿走所有，二号输。

**最后结论**：判断数组里是否有奇数，有则一号胜，否则二号胜。

上代码，我的方法是枚举数组每一项，如果有一项 $mod$ $2==1$ , 计数器就加一。最后在判断，如果计数器大于零（也就是有奇数）就输出“First”,否则输出“Second”。

```cpp
#include<iostream>
using namespace std;
int a[10000010];
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	int cnt=0;
	for(int i=1;i<=n;i++)
		if(a[i]%2==1)
			cnt++;
	if(cnt>0)
		cout<<"First";
	else
		cout<<"Second";
	return 0;
}


```

但是你会发现在第49个测试点会TLE，于是我用了输入优化函数：
```cpp
long long read() 
{
	long long w=1,c,ret;
    while((c=getchar())> '9'||c< '0')
    w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9')
    ret=ret*10+c-'0';
    return ret*w;
}
```
最后合起来的完整AC代码：
```cpp
#include<iostream>
using namespace std;
int a[10000010];
long long read() 
{
	long long w=1,c,ret;
    while((c=getchar())> '9'||c< '0')
    w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9')
    ret=ret*10+c-'0';
    return ret*w;
}
int main()
{
	int n;
	n=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
	}
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i]%2==1)
			cnt++;
	}
	if(cnt>0)
		cout<<"First";
	else
		cout<<"Second";
	return 0;
}


```
祝你成功AC~~~

---

## 作者：北雪2009 (赞：0)

其实我觉得这道题目有一个大缺点：   
### 题目写的根本就不好！！！让人看都看不明白
于是我便将题目复制进百度翻译里，终于找到正确的题目了（虽然我按照正确题目意思改了改……）：
```cpp
莱哈不知怎么找到了一个由n个整数组成的数组。看着它，他想出了一个任务。两个玩家在阵列上玩游戏。球员们一个接一个地移动。第一个玩家可以为他的移动选择一个非零长度的奇数和的子片段，并将其从数组中移除，然后将剩余部分粘在一个数组中并继续游戏。第二个玩家可以选择一个长度为非零且具有偶数和的子段并将其删除。如果有人不能按上述进行，则输。如果双方都打得最好，谁会赢？
```
虽然我得到了正确题目，可我还是不知道如何下手。于是我问了问我的师傅，得知是博弈论（找规律）后，便开始"下手"了：   
首先，我们需弄明白几条原理：
```cpp
奇数+奇数=偶数
奇数+偶数（或偶数+奇数）=奇数
偶数+偶数=偶数
```
其实，这就有点像异或的运算方式：
```cpp
1^0=1
1^1=0
0^1=1
0^0=0
(
或：
真^真=假
真^假=真
假^假=假
假^真=真
)
```
额，对不起，扯远了！咳咳！我们继续说题解。
知道了这个，我们又可以推广出以下原理：
```cpp
奇数个奇数相加等于奇数
偶数个奇数相加等于偶数
无数个偶数相加等于偶数
一个奇数和无数个偶数相加等于奇数
```
得出上三条原理后，我们可以开始主讲解部分。   
首先是First移除，那么我们就开始判断：   
如果原有奇数个奇数：      
	如果真是这样，那就好办了。那First就可以不管Second的阻挠，全去了那些数，那……Second就只能认输了。因为：
```cpp
奇数个奇数相加等于奇数
一个奇数和无数个偶数相加等于奇数
```
如果有偶数个奇数：
	那就有点难（仅对于有奇数个奇数）了。这时，不能再全取了，因为上面的公式告诉我们：   
```cpp
偶数个奇数相加等于偶数
无数个偶数相加等于偶数
```
所以First不能全取。这时First就要想：我如何可以让Second去不了。这时，有两条公式就起到“重要”作用了：
```cpp
奇数个奇数相加等于奇数
一个奇数和无数个偶数相加等于奇数
```
于是，First只要留一个奇数当干掉Second的炸弹，那Second就无话可说，只能乖乖认输了。   
但是——   
你千万不要以为还要判断是奇数个奇数还是偶数个奇数。想想，0个奇数First能不能赢呢？1个奇数First能不能赢呢？2个奇数First能不能赢呢？……   
其实你可以发现，0个奇数的话，那First第一局就会因为没有奇数而“死掉”；如果有奇数的话，那么First只要按照上面的来干，就能把Second“置之于死地”。所以我们能发现：
```cpp
只要奇数数量大于0，那么First必赢；否则First必输。
```
再改一改，就会变成这样：
```cpp
只要有奇数，那么First必赢；否则First必输。
```
所以我们只要判断有木有奇数就ok啦！   
献上AC代码：
```cpp
#include<bits/stdc++.h>    //万能头
#include<stdio.h>
using namespace std;     //使用命名空间std
int n,a;    //定义1
//提示：a可以定义为变量也可以定义为数组。
bool flag=true;    //定义2
//注意：定义二中的flag初值随便你怎么改。
int main(){    //开启主函数
    scanf("%d",&n);    //输入
    for(int i=1;i<=n;i++){    //循环输入
    	scanf("%d",&a);    //循环输入a
    	if(a%2==1) flag=false;    //判断是否有奇数
        //注意！大佬们注意：flag=false不能写成flag=!flag；还有，如果flag初值定为false的朋友这要改成flag=true;
    }
    if(flag) printf("Second");    //判断输出1
    else printf("First");    //判断输出2
    return 0;    //结束
}   //关闭主函数
```

---

