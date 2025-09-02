# [NOI Online 2021 入门组] 切蛋糕

## 题目描述

Alice、Bob 和 Cindy 三个好朋友得到了一个圆形蛋糕，他们打算分享这个蛋糕。

三个人的需求量分别为 $a,b,c$，现在请你帮他们切蛋糕，规则如下：

1. 每次切蛋糕可以选择蛋糕的任意一条直径，并沿这条直径切一刀（注意切完后不会立刻将蛋糕分成两部分）。

2. 设你一共切了 $n$ 刀，那么你将得到 $2n$ 个扇形的蛋糕（特别地，切了 $0$ 刀被认为是有一个扇形，即整个圆形蛋糕），将这些蛋糕分配给 Alice，Bob 和 Cindy，要求每个扇形蛋糕只能完整地分给一个人。

3. 三人分到的蛋糕面积比需要为 $a:b:c$（不保证是最简比例，且如果 $a:b:c$ 中某个数为 $0$，表示那个人不吃蛋糕）。

为了完成这个任务，你至少需要切几刀？

## 说明/提示

### 样例 $1$ 解释
![](https://cdn.luogu.com.cn/upload/image_hosting/i3pai9va.png)

### 数据范围与提示
$30\%$ 的数据满足：$a=b=0$。

$60\%$ 的数据满足：$a=0$。

$100\%$ 的数据满足：$1\le T\le 10^4，0\le a,b,c\le 10^8$，保证 $a+b+c>0$。

数据由 [SSerxhs](https://www.luogu.com.cn/user/29826) 提供。

## 样例 #1

### 输入

```
6
0 0 8
0 5 3
9 9 0
6 2 4
1 7 4
5 8 5```

### 输出

```
0
2
1
2
3
2```

# 题解

## 作者：lzqy_ (赞：58)

**这一道题做法是分类讨论。**

假设 $a\leq b\leq c$，那么就有以下结论：

● $a,b$ 等于 $0$

很明显，一刀都不用切，全部给 $c$ 就可以了，切零刀。

● 有且仅有 $a$ 等于 $0$

$\quad$ ● $b=c$

$\quad$ 在这种情况下，分出两半分别给 $b,c$ 即可，切一刀。

$\quad$ ● $b≠c$

$\quad$ 在这种情况下，切一刀肯定是不行的。但是，容易证明，切两刀可以将蛋糕分成任意比例的两份。因此切两刀。

● $a,b,c≠0$ 且 $a=b$ （$b=c$ 同理）

可以切两刀，分成的四份中，取任意相同的两份给 $a,b$，剩下相同的两份给 $c$ 即可（按照 $a=0\&b≠c$ 的结论推出）

● $a,b,c≠0$ 且 $a+b=c$ 

可以切两刀，分成的四份中，取两份不同的给 $a,b$，剩下不同的两份给 $c$ 便可以满足 $a+b=c$；依然按照 $a=0\&b≠c$ 的结论得到，上述情况可以成立。

● 否则

切三刀。根据 $a=0\&b≠c$ 的结论容易扩展得，切三刀可以分成任意三份的比例。

>容易证明，切两刀可以将蛋糕分成任意比例的两份。

对于这一段的证明如下：

设圆的面积为 $S$，切两刀得到如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/yzrjc2sn.png)

由于这两道是随意切的，所以 $k$ 可以取到 $0<k<1$ 的所有值。因此，同样颜色的扇形面积之和也可以取到 $0<S'<S$ 的所有值。

**代码如下**：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	register int x=0;
	register char c=getchar();
	for(;!(c>='0'&&c<='9');c=getchar());
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+c-'0';
	return x;
}
int t,a[3];
int main()
{
	t=read();
	while(t--)
	{
		a[0]=read(),a[1]=read(),a[2]=read();
		//读到数组里面利于排序
		sort(a,a+3);
		//以下是上文的分类讨论：
		if(a[0]==0&&a[1]==0)
		{
			printf("0\n");
			continue;
		}
		if(a[0]==0)
		{
			if(a[1]==a[2])
				printf("1\n");
			else
				printf("2\n");
			continue;
		}
		if(a[0]==a[1]||a[1]==a[2])
		{
			printf("2\n");
			continue;
		}
		if(a[0]+a[1]==a[2])
		{
			printf("2\n");
			continue;
		}
		printf("3\n");
	}
	return 0;
}
```

---

## 作者：子丑 (赞：36)

### 前言

因为是抱着必死的心态去做的这场比赛，所以看第一题的描述这么麻烦，就直接跳了。

吃饭的时候，突（jing）然（ren）发（ti）现（xing）最多只会切三刀，所以应该只是一道分类讨论题。然后我跑回机房，花了5分钟切掉了蛋糕。

***

### 正文部分

* 为什么最多只需要切三刀？

给一个人切**最多只需要两刀**。那么给三个人切就要 $ 2 \times 3 = 6 $ 刀。而在这六刀里，有三刀是**必定**可以重合的。

其中，给第二个人切的时候，两刀中的第一刀可以**和第一个人共用**。而第三个人其实根本不需要切，因为前两个人拿走他们需要的蛋糕后，剩下的就是第三个人的。

随机的大多数情况下，都是三刀。但数据是人出的，所以我们需要考虑什么时候可以将两刀合为一刀。

* 什么时候可以（需要）合二为一？

对于第一个人：

如果他正好吃了一半，那么两刀之间的夹角就等于 $ 180 \degree $ ，两刀重合，刀数 $ + 1 $ 。

如果他吃了整个蛋糕或者什么都没吃，那就直接不用切了，刀数 $ + 0 $。

如果前两种情况都没出现，那就切两刀，刀数 $ + 2 $

***

对于第二个人：

我们先假设目前的情况是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/5p64t1fd.png)

假设第一个人拿了 $ A $ 。如果第二个人要拿的和 $ B , C , D $ 中的任何一块一样，那他就不需要再切，刀数 $ + 0 $ ；否则需要切，刀数 $ + 1 $。

假设第一个人拿了 $ A , B , C $ 三块蛋糕。如果第二个人要拿的和 $ D $ 一样，那就不需要再切，刀数 $ + 0 $；否则需要切，刀数 $ + 1 $。

简单来讲，如果第二个人和第一个人吃的加起来正好是一半，那就不需要再切；否则需要切。

然后考虑这种情况

![](https://cdn.luogu.com.cn/upload/image_hosting/4ly8vifo.png)

第一个人拿了 $ A $ 。如果第二个人要拿的和 $ B $ 一样，不需要再切，刀数 $ + 0 $ ；否则需要切，刀数 $ + 1 $ 。

***

第三个人不需要考虑，直接跳过。

***

### 代码部分

我清楚你们都看不懂我上面讲的内容，所以，直接上代码吧（

```cpp
#include<bits/stdc++.h>
int main() {
	int T,a[3];
	scanf("%d",&T);
	while(T--) {
		scanf("%d%d%d",a,a+1,a+2),std::sort(a,a+3);
		printf("%d\n",(a[0]==0?(a[1]==0?0:(a[1]==a[2]?1:2)):(a[0]+a[1]==a[2]||a[0]==a[1]||a[1]==a[2]?2:3)));
	}
}
```

说不定有人看不懂计算答案的那一句呢？

```cpp
sort(a,a+3); //先排序一遍，方便后面判断
if(a[0]==0) {
	if(a[1]==0) {
		ans=0; //一个人吃了整个蛋糕
	} else {
		if(a[1]==a[2]) ans=1; //第二个人拿了"B"
		else ans=2; //第二个人再切了一刀
	}
} else {
	if(a[0]+a[1]==a[2]||a[0]==a[1]||a[1]==a[2]) ans=2; //第二个人拿了"B"
	else ans=3; //第二个人再切了一刀
}
printf("%d\n",ans);
```

这样总不会有人看不懂了吧？

什么你们说我写的和我讲的不一样？那我不管（光速闪

---

## 作者：Unordered_OIer (赞：14)

# P7471 题解
结论题

## Description
给定正整数 $a,b,c$，问一个圆沿着任意一条直径分割，分割若干刀后能使选出三组扇形，每组面积之和之比为 $a:b:c$。

$T$ 组数据。

## Solution
首先表扬样例！涵盖了几乎所有情况！

****
我们看几个显而易见的结论：
1. 一定存在一种分割方式
2. 最多三刀可以分出来

结论 $1$ 太简单就不证了，结论 $2$ 虽然简单但还是证一下：

首先我们设有一种满足题意的分割方式如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/04eoj9qk.png)

我们分别将这三条线段延长。

![](https://cdn.luogu.com.cn/upload/image_hosting/nswst0i6.png)

于是就得到了三刀切出任意 $a:b:c$ 的结论。

这也就说明输出一定 $\leq 3$。

然后我们看数据范围与约定：

- $a=b=0$  
这种情况整个蛋糕都给 $c$ 即可，输出 $0$。

- $a=0$  
这种情况我们只要将圆分成两部分即可，当这两部分比值相同，则一刀即可；否则需要两刀切出 $b:c$。

- 无特殊性质的数据  

样例的良心之处就出现了！

首先根据扇形面积公式 $S=\dfrac{\theta}{360} \times \pi d$，其中 $\pi,d,360$ 皆为不变量，所以 $\dfrac{S_1}{S_2}=\dfrac{\theta_1}{\theta_2}$。

所以只要将 $360 \degree$ 分成 $ax+bx+cx$ 即可。

然后看 stdin 后三行

```
6 2 4
1 7 4
5 8 5
```

再看 stdout 后三行

```
2
3
2
```

我们发现对于 $6,2,4$，其中 $2+4=6$，只要 $2$ 刀。  
并且对于 $5,8,5$，其中 $5=5$，只要 $2$ 刀。  
其余情况 $3$ 刀。

证明？有点抽象。

不妨设 $a<b<c$，如果 $a+b=c$，则有两刀一定是一样的，所以只要 $2$ 刀就行。

如果 $a=b$ 或 $b=c$ 或 $c=a$，则因为对顶角相等，两道切出来夹出来的且对顶两部分面积相等。然后调整至 $a:b:c$ 即可，易证一定存在一种调整方法。

- **else？**

有一种额外的情况 $a=b=c$！  

这种情况虽然不会有很大的影响但是还是要考虑进去的。

我们其实只需要切 $2$ 刀就行，切出的角为 $60 \degree$ 即可。


## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read(){
	ll x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
inline void write(ll x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
inline void writeln(ll x){write(x),putchar('\n');}
ll T,a,b,c;
inline ll gcd(ll a,ll b){return a%b==0?b:gcd(b,a%b);}
int main(){
//
	freopen("cake.in","r",stdin);
	freopen("cake.out","w",stdout);
//
	T=read();
	while(T--){
		a=read(),b=read(),c=read();
		ll aa=a,bb=b,cc=c;
		a=min(aa,min(bb,cc)),c=max(aa,max(bb,cc)),b=aa+bb+cc-a-c;
		if(a==0&&b==0){
			writeln(0);
			continue;
		}
		else if(a==0){
			if(b==c)writeln(1);
			else writeln(2);
		}
		else{
			if(a+b==c||(a==b||b==c||a==c))writeln(2);
			else writeln(3);
		}
	}
	return 0;
}
```

---

## 作者：仗剑_天涯 (赞：7)

这道题就是思维题。

首先，只要有两个零，就不用切了，直接把蛋糕给了。

有一个零：如果剩下两个化简是一比一，那么只切一刀（切成两半）,否则切两刀一定可以。

没零：如果三个相等是三刀（切两刀四块满足不了）。

如果有两个相等的，则两刀

![](https://cdn.luogu.com.cn/upload/image_hosting/kodd4htx.png)

两个加起来是第三个的，两刀

![](https://cdn.luogu.com.cn/upload/image_hosting/ledq7mc7.png)

其他三刀

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,a,b,c;
int main()
{
	freopen("cake.in","r",stdin);
	freopen("cake.out","w",stdout);
	cin>>T;
	while(T--)
	{
		scanf("%d%d%d",&a,&b,&c);
		if((a==0&&b==0)||(a==0&&c==0)||(b==0&&c==0))
		{
			printf("0\n");
		}
		else
		{
			if(a==0||b==0||c==0)
			{
				if(a==b||b==c||a==c)
				{
					printf("1\n");
				}
				else
				{
					printf("2\n");
				}
			}
			else
			{
				if(a==b&&b==c)
				{
					printf("3\n");
				}
				else
				{
					if(a==b||b==c||a==c||a+b==c||a+c==b||b+c==a)
					{
						printf("2\n");
					}
					else
					{
						printf("3\n");	
					}
				}
			}
		}
	}
	fclose(stdin);
	fclose(stdout);
} 
```


---

## 作者：oimaster (赞：6)

这道题可能性很少，一堆 if 即可。

首先，$a,b,c$ 输入时不一定是按照顺序！你需要进行初步排序。

接下来，可能性如下：

1. $a=b=0$，输出 $0$，不用切。
2. $a=0$，接下来如果 $b=c$，就切 $1$ 刀，否则要切 $2$ 刀。
3. $a+b=c$，切 $2$ 刀。第一刀是分出 $c$，第二刀分出 $a,b$。如下图。
![](https://cdn.luogu.com.cn/upload/image_hosting/ks9jhw3n.png)
4. $a=b=c$，这时候比例为 $1:1:1$，那么如下图切割：
![](https://cdn.luogu.com.cn/upload/image_hosting/35bgro46.png)
两次即可。
5. 全部不满足输出 $3$。

代码：
```cpp
#include<fstream>
// #include<iostream>
using namespace std;
ifstream cin("cake.in");
ofstream cout("cake.out");
int main(){
	int t;
	cin>>t;
	while(t--){
		int a,b,c;
		cin>>a>>b>>c;
		if(a>b)
			swap(a,b);
		if(a>c)
			swap(a,c);
		if(b>c)
			swap(b,c);
		if(a==0&&b==0)
			cout<<0<<endl;
		else if(a==0&&b==c)
			cout<<1<<endl;
		else if(a==0&&b!=c)
			cout<<2<<endl;
		else if(a+b==c)
			cout<<2<<endl;
		else if(a==b||b==c||a==c)
			cout<<2<<endl;
		else
			cout<<3<<endl;
	}
	return 0;
}
```

---

## 作者：Argon_Cube (赞：5)

* **【题目链接】**

[Link:P7471](https://www.luogu.com.cn/problem/P7471)

* **【解题思路】**

果然，正式比赛第一题永远都是人口普查题。

本题分情况处理：

1. 如果只有一个人吃蛋糕，那么就不用切，输出 $0$。

2. 如果有两个人吃蛋糕，分情况考虑：
	1. 如果两人的份数相等，直接对半切开，输出 $1$。
    
   2. 如果两人份数不等，那么可以切成 $4$ 份（即切两刀），把其中一份分给要得少的那个人，剩下 $3$ 份分给要的多的那个人。
   
3. 如果有三个人吃蛋糕，同样分情况（假设 $a>b>c$）：

	1. 有两个人要的份数相同。可以切两刀，分法参照样例解释。
    
   2. 有两个人要的份数的和为第三个人要的份数。同样切两刀，分法参照样例解释。
   
   3. 其余情况，切 $3$ 刀。可以先切两刀，切出两个 $b$ 份。一个分给 $b$，一个分给 $a$。剩下两份再切一刀，如果 $c$ 大于其中一份，则把三份分给$c$，一份分给$a$；否则，就把三份分给$a$，一份分给$c$。
   
* **【代码实现】**

```cpp
#include <iostream>

using namespace std;

int gcd(int a,int b)
{
	return b?gcd(b,a%b):a;
}

int main()
{
	long long a,b,c,tmp,T;
	cin>>T;
	while(T--)
	{
		cin>>a>>b>>c;
		if(a==0&&b==0||a==0&&c==0||b==0&&c==0)//情况1
		{
			cout<<0<<endl;
			continue;
		}
		if(a==0)//情况2
		{
			if(b==c)
				cout<<1<<endl;
			else
				cout<<2<<endl;
			continue;
		}
		if(b==0)
		{
			if(a==c)
				cout<<1<<endl;
			else
				cout<<2<<endl;
			continue;
		}
		if(c==0)
		{
			if(a==b)
				cout<<1<<endl;
			else
				cout<<2<<endl;
			continue;
		}
		if(a+b==c||a+c==b||b+c==a||a==b||a==c||b==c)//情况3.1&&3.2
		{
			cout<<2<<endl;
			continue;
		}
		cout<<3<<endl;//情况3.3
	}
 	return 0;
}

```

---

## 作者：JoseTony (赞：4)

这道题作为此次比赛的第一题还是非常良心的，只需要简单的模拟一下即可。仔细观察数据范围，可以发现部分分也给的很多，如果两个人都不吃蛋糕，那么一次也不需要分，把整个蛋糕给第三个人就可以了。
```cpp
#include<iostream>
using namespace std;
int main(){
  int t;
  cin >> t;
  while(t--){
  	cout << 0 << endl;
  }
  return 0;
  }
```
因此以上代码可以获得 $30$ 分的好成绩。
但是要想更上一层楼，该怎么办呢？我们继续模拟一下。由于输入数据不保证先后顺序，我们先把输入的三个数排序。当有一个人不吃蛋糕的情况下，如果另外两个人所需比例相同，只需切一刀，一分为二即可。其他的情况因无法保证两人所需比例相同，因此需要在一分为二的基础上再切一刀，所以我们输出 $2$ 加上换行。其余情况下如果两数相加等于另外一数，我们只需要一分为四，也就是切两刀就可以。如果在一个数据不为零的情况下另外两数相等，也只需切两刀均分，再分剩下的即可。如果以上情况都不满足，只要输出 $3$ 即可。
# 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

void f(){
    freopen("cake.in","r",stdin);
    freopen("cake.out","w",stdout);
}
int a[100001];
int T;
int main(){
    //f();
    
    cin >> T;
    while(T--){
        cin >> a[0] >> a[1] >> a[2];
    
            sort(a,a+3);
            if(a[0]==0&&a[1]==0){
                cout << 0 << endl;
            }else if(a[0]==0){
                if(a[1]==a[2]){
                    cout << 1 << endl;
                }else{
                    cout << 2 << endl;
                }
                
        }else if(a[0]+a[1]==a[2]){
            cout << 2 << endl;
        }else if(a[0]==a[1]||a[1]==a[2]){
            cout << 2 << endl;
        }else{
            cout << 3 << endl;
        }
}
    return 0;
}

```



---

## 作者：syf2008 (赞：4)

这是一道有趣的题

首先,我们要分类讨论。~~（这不废话）~~

1.两数为0（不管哪两个数），输出0

2.只有一个数为0，判剩下两数是否相等，若相等，输出1（对半切），否则输出2

3.没有数为0，其中两数相等或最大的数=其余两数之和，输出2，否则输出3

上代码
```
#include <bits/stdc++.h>
using namespace std;
int t,a[10];
int main()
{
	cin>>t;
	while(t--)
	{
		scanf("%d%d%d",&a[1],&a[2],&a[3]);
		sort(a+1,a+4);//排序后会方便一些
		if(a[1]==0&&a[2]==0)
		puts("0");
	else if(a[1]==0)
		{
			if(a[2]==a[3])
			puts("1");
		else puts("2");
		}
	else {
		if(a[1]==a[2]||a[2]==a[3]||a[1]+a[2]==a[3])
		puts("2");
	else puts("3");
		}
	}
}
```

---

## 作者：cyffff (赞：4)

[P7471 [NOI Online 2021 入门组] 切蛋糕](https://www.luogu.com.cn/problem/P7471)
## 题意
略
## 思路
先找点规律。

把三个人要吃的蛋糕的圆心角表示出来排个序，设为 $d_1,d_2,d_3$，先考虑有人不吃的情况。

- $d_1=d_2=0,d_3\ne0$ 显然答案为 $0$。
- $d_1=0,d_2\ne0$ 此时继续分类讨论。
	- $d_2=d_3=180$ 答案为 $1$。
   - $d_2\ne 180$，此时需要两刀切出 $d_2$，所以答案为 $2$。
- $d_1\ne 0$ 继续分类讨论
	- $d_1+d_2=d_3=180$ 需要两刀切出 $d_1$，它的补角为 $d_2$，答案为 $2$。
   - $d_1=d_2$ 或 $d_2=d_3$，切两刀切出 $d_2$，它的对顶角为与其相同的角度，其余的为与其不相同的角度，答案为 $2$。
   - $\texttt{otherwise}$ 可以切两刀切出 $d_1$，再切一刀切出 $d_2$，其余为 $d_3$，答案为 $3$。
   
时间复杂度 $O(T)$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
double d[10];
int main(){
	freopen("cake.in","r",stdin);
	freopen("cake.out","w",stdout);
	int T=read();
	while(T--){
		int a=read(),b=read(),c=read(),s=a+b+c;
		double da=360.0*a/s,db=360.0*b/s,dc=360.0*c/s;
		d[1]=da,d[2]=db,d[3]=dc;
		sort(d+1,d+4);
		if(!d[1]){
			if(!d[2]){
				puts("0");
			}else{
				if(d[2]==180)
				puts("1");
				else
				puts("2");
			}
			continue;
		}
		if(d[1]+d[2]==180){
			puts("2");
			continue;
		}
		if(d[1]==d[2]||d[2]==d[3]){
			puts("2");
			continue;
		}
		puts("3");
	}
}
```
再见 qwq~

---

## 作者：tribool4_in (赞：3)

首先易知，切的刀数一定 $\le 3$。

分情况讨论：

1. 如果有两个为 0 则一定不用切；
2. 有一个为 0 而且其余两个一样则要切一刀，否则要切两刀；
3. 如果都不为 0 且有任意两个相同，则也只要切两刀；
4. 如果有一个是另外两个的和，则也只要切两刀，否则要切三刀。

具体分析可以画图。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int T, a[3];
int main() {
	freopen("cake.in", "r", stdin);
	freopen("cake.out", "w", stdout);
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", a, a + 1, a + 2);
		sort(a, a + 3);
		if (a[0] == 0 && a[1] == 0) puts("0");
		else if (a[0] == 0) {
			if (a[1] == a[2]) puts("1");
			else puts("2");
		} else {
			if (a[0] == a[1] || a[1] == a[2]) puts("2");
			else {
				if (a[0] + a[1] == a[2]) puts("2");
				else puts("3");
			}
		}
	}
	return 0;
}
```


---

## 作者：TRZ_2007 (赞：2)

**[题解【[NOI Online 2021 入门组] 切蛋糕（民间数据）】](https://www.luogu.com.cn/problem/P7471)**

# Solution  
这道题目其实是一个数学题……  
考虑分类讨论。  
首先先把读入的数字排序以便于处理。  
- 1： 两个数字都是 ``0`` ： 不用切了全部都是第三个人的
- 2：一个数字是 ``0``：继续分类，如果两个数字相同那么直接对半开（切一刀），否则对半开之后再切一刀必定可以达成目的（因为可以切任意的圆周角）  
- 3: 都不是 ``0`` ：继续分类，如果有两个数字相同那么只需要切两刀（先对半开然后再切一刀必定可以找到**两对**面积相等的部分）；如果小的两个面积之和等于大的，也只需要切两刀（先对半开然后再一个半圆中切出这两个小的面积），否则就切三刀（先切两刀写出最小的，然后对剩下来的大扇形进行切割，一定可以切出来）

然后……这道题目就结束了，如果看不懂可以自己画一个图理解一下。

# Code
```
#include <bits/stdc++.h>
using namespace std;

#define gc getchar
inline int read() {
	int c = gc(), t = 1, n = 0;
	while(isspace(c)) { c = gc(); }
	if(c == '-') { t = -1, c = gc(); }
	while(isdigit(c)) { n = n * 10 + c - '0', c = gc(); }
	return n * t;
}
#undef gc

int T,a,b,c,t[3],dk;

inline void solve() {
	t[0] = read(); t[1] = read(); t[2] = read();
	sort(t,t + 3);
	a = t[0]; b = t[1]; c = t[2];
	if(a == 0 && b == 0) { puts("0"); return; }
	if(a == 0) {
		dk = __gcd(b,c);
		b /= dk; c /= dk;
		if(b == c) { puts("1"); return; }
		else { puts("2"); return; }
		return;
	}
	dk = __gcd(a,__gcd(b,c));
	a /= dk; b /= dk; c /= dk;
	if(a == b || b == c || c == a) { puts("2"); return; }
	if(a + b == c) { puts("2"); return; }
	puts("3");
}

void _file() { freopen("cake.in","r",stdin); freopen("cake.out","w",stdout); }

int main() {
//	_file();
	T = read();
	while(T--) solve();
	return 0;
}
```
PS:貌似这次比赛就写出来了这一道题，人傻了。

---

## 作者：cinis (赞：1)

~~蒟蒻不确定后两题只能来搞T1题解了~~

# 整个题解的思路是分类讨论

分蛋糕的人数可以分为三种情况：1个人，2个人和3个人

显而易见，对于一个人来说，只有一种切蛋糕的方式：不切蛋糕（0刀）

![不切蛋糕](https://cdn.luogu.com.cn/upload/image_hosting/ofc4c7f2.png?x-oss-process=image/resize,m_lfit,h_4000,w_400)

而对于两个人来说，可能根据相等或不相等有两种情况：平分（1刀）或者切两刀细分（2刀）

![两个人时](https://cdn.luogu.com.cn/upload/image_hosting/hrwqcy2z.png?x-oss-process=image/resize,m_lfit,h_4000,w_400)

这样，根据上面的结论解决1个人和2个人的问题后，可以集中解决有3个人的问题了

在有3个人的情况下，还需要接着细分：其中2个人的量相等，最大的量等于剩余两量之和，和剩下的情况

由于对顶角相等，2个人量相等的情况可以被简化为用两刀切出来剩下的那个人的量（2刀）

而最大的量等于剩余两量之和的情况可以被简化为两个人不相等的问题，还是只需要2刀（2刀）

![~~1+1=2~~](https://cdn.luogu.com.cn/upload/image_hosting/nb8f5cl0.png?x-oss-process=image/resize,m_lfit,h_400,w_400)

至于剩下的情况，最多也只需要处理三刀：两刀规划最大的量，剩下一刀可以完美地决定剩下的两个量（3刀）

![](https://cdn.luogu.com.cn/upload/image_hosting/90hr67l6.png?x-oss-process=image/resize,m_lfit,h_400,w_400)

把上面的思路写成代码，这道题就解决了


```cpp
int rnk[5];//为了让每个人的量可以保持有序故使用数组
int main(){
//	freopen("cake.in","r",stdin);
//	freopen("cake.out","w",stdout);
	int T=read();
	while(T--){
		rnk[1]=read(),rnk[2]=read(),rnk[3]=read();
		sort(rnk+1,rnk+4);//排序好朋友
		if(rnk[1]==0&&rnk[2]==0){//如果只有一个人
			puts("0");
			continue;
		}
		if(rnk[1]==0){//如果只有两个人
			if(rnk[2]!=rnk[3])puts("2");//不平分需要细分
			else puts("1");//平分只需一刀
			continue;
		}
		if(rnk[1]!=rnk[2]&&rnk[2]!=rnk[3]&&rnk[1]+rnk[2]!=rnk[3])puts("3");//如果有三个人，没有相等关系，最大值也不等于其他两项的和
		else puts("2");//否则
	}
    return 0;
}
```



---

## 作者：May_wind (赞：1)

~~这次比赛就做出了T1然后被T2卡了2h最后死了~~

非常良心的一道题

首先，如果只有一个人吃，那么蛋糕就没必要切了。~~废话~~


------------


接下来分类讨论：

一、只有两个人吃蛋糕

如果这两个人吃的一样多，切一刀分成就好了。~~又是废话~~

否则，我们切两刀把蛋糕分成不等的两份。

二、三个人吃蛋糕（设三人分别吃了 *a,b,c* 份 ）

1.两个人吃的蛋糕量之和等于第三个人

设 *a+b=c*

显然有c为蛋糕的一半，那么先切一刀平分后再切一刀确保其中一半分成 *a b*两部分就好了

2.某两个人吃的一样多

设 *a = b* ,那么先切一刀平分后再切一刀确保其中一半分成 a 和 $\frac{c}{2}$ 两部分就好了（另一半也会分成这个样子，所以a b 各拿所对应的的一块，c拿走两块 $\frac{c}{2}$ 解决问题）

3.三人各不相同

先切两刀分出其中一个人的部分，再切一刀把剩下的部分分开，总共最多切三刀（可以参考样例）

~~题目很良心，样例也很良心~~

*Code*

```cpp
#include<iostream>
#include<cstdio>

using namespace std;

int T,a,b,c,cnt;
int work(){
	if(a == 0)cnt ++;if(b == 0)cnt ++;if(c == 0)cnt ++;
	if(cnt >= 2)return 0;
	if(cnt == 1){
		if((a == b) || (b == c) || (a == c))return 1;
		return 2;
	}
	if((a == b+c) || (b == a+c) || (c == a+b))return 2;
	if((a == b) || (b == c) || (a == c))return 2;
	return 3;
}
int main(){
	freopen("cake.in","r",stdin);
	freopen("cake.out","w",stdout);
	scanf("%d",&T);
	while(T--){
		cnt = 0;
		scanf("%d%d%d",&a,&b,&c);
		printf("%d\n",work());
	}
	fclose(stdin);fclose(stdout);
	return 0;
}

```


---

## 作者：Chouquet (赞：1)

结论题，可以将面积转化为圆心角处理。设 $a,b,c$ 对应的圆心角分别为 $\alpha,\beta,\gamma$ 。

第一步先将 $360\degree$ 分成两个 $180\degree$ 的，如果此时满足，就只需要一刀。否则可以调整为 $360\degree-\gamma$ 和 $\gamma$ ，这时满足的话只需要两刀。又因为 $a+b+c=S$ （$S$ 为圆面积），所以 $\alpha+\beta+\gamma=360\degree$ ，$360\degree-\gamma$ 一定可以分成 $\alpha$ 和 $\beta$ 两部分，只需要三刀。

具体判断的方法看代码：

```cpp
#include <cstdio>
#include <algorithm>
int t, a, b, c;
int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d", &a, &b, &c);
        if ((!a && !b) || (!a && !c) || (!c && !b))
            puts("0");//a,b,c中两个为0，则不用切
        else if ((a == b && !c) || (b == c && !a) || (a == c && !b))
            puts("1");//a,b,c中一个为0，另两个相等，只需要一刀
        else if (!a || !b || !c || (a == b || b == c || c == a) || (a == b + c || b == a + c || c == a + b))
            puts("2");
            //a,b,c中有一个为0，另两个不相等。或着a,b,c>0,三个里有两个相等（对顶角），或者一个是另两个的和（也是对顶角），只需要两刀
        else
            puts("3");//否则都需要三刀
    }
    return 0;
}
```

~~越来越像CF的结论题了~~

---

## 作者：断清秋 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P7471)

NOI Online 2021 入门组 T1。

首先有一个显而易见的结论：答案最多不会超过三刀。

因为即使最坏的情况，也可以用三刀将蛋糕切成六块，大小分别为 $\dfrac{a}{2}$，$\dfrac{a}{2}$，$\dfrac{b}{2}$，$\dfrac{b}{2}$，$\dfrac{c}{2}$，$\dfrac{c}{2}$。

所以我们可以分类讨论，先将 $a,b,c$ 按大小排序，令 $a\le b\le c$ 。

当两个人及两个人以上都为 $0$ 时，答案显然为 $0$。

当一个人为 $0$ 时，如果剩余两个人需求量相等，则答案为 $1$，否则答案为 $2$。

当三个人均不为 $0$ 时，如果有两个人需求量相等或 $a+b=c$，则答案为 $2$，否则答案为 $3$。

时间复杂度 $O(T)$。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define back return
#define ri register int
using namespace std;
int read()
{
    int x=0,f=1;
	char ch=getchar();
    while(ch<'0'||ch>'9')
    {
      	if(ch=='-')
      		f=-1;
      	ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
      	x=x*10+ch-'0';
      	ch=getchar();
    }
    back x*f;
}
ll t,a[5];
int main()
{
	//freopen("cake.in","r",stdin);
	//freopen("cake.out","w",stdout);
	t=read();
	while(t--)
	{
		a[1]=read(),a[2]=read(),a[3]=read();
		sort(a+1,a+4);
		if(a[1]==0&&a[2]==0)
		{
			cout<<0<<endl;
			continue;
		}
		if(a[1]==0)
		{
			if(a[2]==a[3])
				cout<<1<<endl;
			else
				cout<<2<<endl;
			continue;
		}
		if(a[1]+a[2]==a[3])
		{
			cout<<2<<endl;
			continue;
		}	
		if(a[1]==a[2]||a[2]==a[3])
			cout<<2<<endl;
		else
			cout<<3<<endl;
	}
	back 0;
}
```

---

## 作者：maruize (赞：1)

首先最多切3刀。

然后讨论：

> 切0刀：
>> 两个人为0

> 切1刀：
>> 一个人为0，另两个人平分

> 切2刀：
>>  一个人为0的其他情况

>>  有两个人的数相等

>>  一个人吃一半蛋糕

> 切三刀
>>  其他情况

```cpp
int sol(int a,int b,int c){ //a<b<c
	if(a==0&&b==0&&c==0)abort();//invalid
	if(a==0&&b==0)return 0;
	if(a==0){
		if(b==c)return 1;
		return 2;
	}
	if(a==b||b==c||a==c)return 2;
	int s=a+b+c;
	if(c*2==s)return 2;
	return 3;
}

```


---

## 作者：FuriousC (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P7471)

~~特判简单题~~

作为$NOIO$的$T1$，出题人还是很良心的

以下为特判的点（默认$a$最小，$c$最大）：

- $a=0$且$b=0$，不用切

- $a=0$且$b=c$，切一刀分给$b$和$c$

- $a=0$且$b\ne c$，切两刀即可切出任意角度

- $a,b,c$均不为$0$，但$a=b$或$b=c$或$a=c$，切两刀即可。先切一刀，使任意一个角相等，再切另外一个即可

- $a,b,c$均不为$0$，但$c=a+b$，切两刀。先切一刀，使左边变成$c$，再切一定的一刀，右上即为$a$，右下为$b$

- $a,b,c$均不为$0$，且没有任何特殊性质，切三刀即可

由于蒟蒻的语文表达能力比较差，如果没有看懂请参考样例解释$qwq$

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll T,a,b,c;
int main(){
    cin>>T;
    while(T--){
        cin>>a>>b>>c;
        ll a1=a,b1=b,c1=c;
        a=min(a1,min(b1,c1));
        c=max(a1,max(b1,c1));
        b=a1+b1+c1-a-c;
        if(a==0&&b==0){
            cout<<0<<endl;
        }else if(a==0){
            if(b==c){
            	cout<<1<<endl;
            }else{
                cout<<2<<endl;
            }
        }else{
            if(a+b==c||(a==b||b==c||a==c)){
            	cout<<2<<endl;
            }else{
                cout<<3<<endl;
            }
        }
    }
    return 0;
}
```

代码看完了，你学废了吗？

---

## 作者：山田リョウ (赞：1)

这道题看起来很难，实际上挺简单的，我们可以先分一下类。

注：为了方便判断，默认 $a$、$b$、$c$ 安装升序排序。
+ $a$ 和 $b$ 均为 $0$：不用切就行
+ $a$ 为 $0$，且 $b = c$：切一刀就分成了两半，刚好分给 $b$ 和 $c$。
+ $a$ 为 $0$，且 $b \neq c$：切两刀就够了，因为无论如何，切两条都能切出任意一个角度。
+ $a,b,c$ 均不为 $0$，且 $c=a+b$：先切一刀，左边就是 $c$，再切一刀特定的一刀，右半边的上半部分就是 $a$，下半部分就是 $b$。
+ $a,b,c$ 均不为 $0$，且 $a=b$ 或者 $b=c$，也是且两刀就够，先切出相等的任意一个，由于对顶角相等，所以对面就是相等的另一个，剩下的就是那个和其他两个不同的。
+ $a,b,c$ 均不为 $0$，且没有上面提到的任何特殊性质，切三刀就够，先随便切出一个角，需要两刀，再切一个特定的直径，就可以切出剩下两个。

如果没有看懂的话可以看看样例提供的解释。

代码如下：
```cpp
#include<cstdio>
inline int& min(int& a,int& b) {
    return a<b?a:b;
}
inline void swap(int &a,int &b) {
    int tmp=a;
    a=b;
    b=tmp;
}
int main() {
    std::freopen("cake.in","r",stdin);
    std::freopen("cake.out","w",stdout);
    int t;
    int a,b,c;
    std::scanf("%d",&t);
    while(t--) {
        std::scanf("%d%d%d",&a,&b,&c);
        swap(a,min(min(a,b),c));
        swap(b,min(b,c));
        std::printf("%d\n",(a==0?(b==0?0:(b==c?1:2)):((c==a+b||a==b||b==c)?2:3)));
    }
    return 0;
}
```


---

## 作者：MiRaciss (赞：0)

分类讨论

如果只有一个人要蛋糕，那么不需要切，直接输出0即可。

如果两个人要蛋糕，那么如果他们要的份数是一样的，则只需要切一刀，否则要切两刀

如果三个人都要蛋糕，那么如果其中有两个人要的份数一样，则只需要切两刀，如果最小的两个人切的蛋糕的份数等于最大的那个人，那么也只需要切两刀，都不满足就需要切三刀。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define a t[1]
#define b t[2]
#define c t[3]

int t[15];

int Work(){
	sort(t+1,t+3+1);
	if(a==b||b==c||a+b==c)
		return 2;
	return 3;
}

int main(){
	int T;
	cin>>T;
	while(T--){
		scanf("%d%d%d",&a,&b,&c);
		int tot=bool(a)+bool(b)+bool(c);
		if(tot<=1){
			printf("0\n");
			goto F__k;		//文明用语，从我做起
		}
		sort(t+1,t+3+1);
		if(tot==2){
			if(b==c)
				printf("1\n");
			else
				printf("2\n");
			goto F__k;
		}
		printf("%d\n",Work());
		F__k:;
	} 
	return 1;
}
/*
6
0 0 8
0 5 3
9 9 0
6 2 4
1 7 4
5 8 5

*/
```

---

