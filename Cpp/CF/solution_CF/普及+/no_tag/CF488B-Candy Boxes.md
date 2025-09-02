# Candy Boxes

## 题目描述

There is an old tradition of keeping $ 4 $ boxes of candies in the house in Cyberland. The numbers of candies are special if their arithmetic mean, their median and their range are all equal. By definition, for a set $ {x_{1},x_{2},x_{3},x_{4}} $ ( $ x_{1}<=x_{2}<=x_{3}<=x_{4} $ ) arithmetic mean is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF488B/4ced3a9ae4181924c136bcc46ede19844528fdef.png), median is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF488B/2d7e14bfd580007a1d694763c07f2437bb7e66e6.png) and range is $ x_{4}-x_{1} $ . The arithmetic mean and median are not necessary integer. It is well-known that if those three numbers are same, boxes will create a "debugging field" and codes in the field will have no bugs.

For example, $ 1,1,3,3 $ is the example of $ 4 $ numbers meeting the condition because their mean, median and range are all equal to $ 2 $ .

Jeff has $ 4 $ special boxes of candies. However, something bad has happened! Some of the boxes could have been lost and now there are only $ n $ ( $ 0<=n<=4 $ ) boxes remaining. The $ i $ -th remaining box contains $ a_{i} $ candies.

Now Jeff wants to know: is there a possible way to find the number of candies of the $ 4-n $ missing boxes, meeting the condition above (the mean, median and range are equal)?

## 说明/提示

For the first sample, the numbers of candies in $ 4 $ boxes can be $ 1,1,3,3 $ . The arithmetic mean, the median and the range of them are all $ 2 $ .

For the second sample, it's impossible to find the missing number of candies.

In the third example no box has been lost and numbers satisfy the condition.

You may output $ b $ in any order.

## 样例 #1

### 输入

```
2
1
1
```

### 输出

```
YES
3
3
```

## 样例 #2

### 输入

```
3
1
1
1
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
4
1
2
2
3
```

### 输出

```
YES
```

# 题解

## 作者：N_z_ (赞：5)

## 题意

如果有一个序列满足$(a_1+a_2+a_3+a_4)/4=(a_2+a_3)/2=a_4-a_1$，并且$a_1\le a_2\le a_3\le a_4$，那么这个序列符合条件。
现在给出4个数中的其中$n(0\le n\le 4)$个，判断能否构造出这么一个序列。

## 思路
对等式变形：
$$\begin{aligned}
&\dfrac{a_1+a_2+a_3+a_4}{4}=\dfrac{a_2+a_3}{2}=a_4-a_1\\
&\implies a_1+a_4=a_2+a_3,5a_1+a_2+a_3=3a_4\\
&\implies 3a_1=a_4,a_2+a_3=4a_1\\
\end{aligned}$$
不妨设读入从小到大排序后分别为$i,j,k,l$。

根据$n$分类：
* $n=0$ 有解，输出一组特解即可。
* $n=1$ 有解$i,i,3i,3i$。
* $n=2$ 
	* 若$j\le3*i$ 有解$i,j,4i-j,3i$。
   * 否则 无解。
* $n=3$ 
	* 若$k=3i$ 有解$i,j,4i-j,k$。
   * 若$3i\ge k$及$j+k=4i$ 有解$i,j,k,3i$。
   * 若$i+j=4k/3$ 有解$k/3,i,j,k$。
   * 否则 无解。
* $n=4$ 直接判断即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[5];
int main()
{
	int n;
	cin>>n;
	for(int x=1;x<=n;x++)
	cin>>a[x];
	sort(a+1,a+1+n);
	if(n==0){cout<<"YES\n1\n1\n3\n3"<<endl;return 0;}
	if(n==4){
		if((a[1]+a[2]+a[3]+a[4])==(a[2]+a[3])*2&&(a[2]+a[3])*2==(a[4]-a[1])*4)cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
		return 0;
	}
	if(n==1){
		a[4]=3*a[1];
		a[2]=a[1];
		a[3]=3*a[1];
		cout<<"YES"<<endl<<a[2]<<endl<<a[3]<<endl<<a[4]<<endl;
		return 0;
	}
	if(n==2){
		if(3*a[1]>=a[2])cout<<"YES"<<endl<<4*a[1]-a[2]<<endl<<3*a[1]<<endl;
		else cout<<"NO"<<endl;
		return 0;
	}
	if(n==3){
		if(a[3]==3*a[1])cout<<"YES"<<endl<<4*a[1]-a[2]<<endl;
		else if(3*a[1]>=a[3]&&a[2]+a[3]==4*a[1])cout<<"YES"<<endl<<3*a[1]<<endl;
		else if(a[3]%3==0&&a[1]+a[2]==4*a[3]/3)cout<<"YES"<<endl<<a[3]/3<<endl;
		else cout<<"NO"<<endl;
		return 0;
	}
}
```

---

## 作者：QQH08 (赞：4)

~~说实话，这题的本质是暴力。~~

看到$n\leq 4$，果断分类讨论。

先把式子化简一下：

第一个：
$$
\begin{aligned}
\dfrac{a_1+a_2+a_3+a_4}{4}&=\dfrac{a_2+a_3}{2}\\

\dfrac{a_1+a_2}{4}&=\dfrac{a_2+a_3}{4}\\

a_1+a_4&=a_2+a_3
\end{aligned}
$$
第二个：
$$
\begin{aligned}
\dfrac{a_2+a_3}{2}&=a_4-a_1\\

a_2+a_3&=2a_4-2a_1\\

a_1+a_4&=2a_4-2a_1\\

3a_1&=a_4
\end{aligned}
$$
所以条件就是上面 $2$ 个式子都要满足。



------------


下面对 $n$ 进行分类讨论
- 当 $n=0$，直接随便构造一组可行的解。比如：$1\ 1\ 3\ 3$

- 当 $n=1$，~~（暴力要超时）~~，所以我们构造一下。把序列构造成 $a_1,a_1+1,a_1\times 3-1,a_1\times 3$，很显然这是符合条件的。

- 当 $n=2$，这时候就可以暴力啦。很显然，答案肯定不会超过 $1500$ ，于是我们分别枚举另外 $2$ 个数，排个序，再看能否满足条件就行了。

- 当 $n=3$，这个跟 $n=2$ 是差不多的。直接枚举剩下的 $1$ 个数，判断即可。

- 当 $n=4$，这个直接排序后判断是否满足条件就可以啦。

下面就是我的代码了 ~~（话说还是一血）~~：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[10];
bool check(){
	if(a[1]+a[4]==a[2]+a[3]&&3*a[1]==a[4])return 1;
	else return 0;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	if(n==0){
		puts("YES");
		printf("1\n1\n3\n3");
	}
	else if(n==1){
		puts("YES");
		printf("%d\n%d\n%d",a[1]+1,3*a[1]-1,3*a[1]);
		return 0;
	}
	else if(n==2){
		for(int i=1;i<=1500;i++){
			for(int j=1;j<=1500;j++){
				int x=a[1],y=a[2];
				a[3]=i,a[4]=j;
				sort(a+1,a+5);
				if(check()==1){
					puts("YES");
					printf("%d\n%d",min(i,j),max(i,j));
					return 0;
				}
				a[1]=x,a[2]=y;
			}
		}
		puts("NO");
	}
	else if(n==3){
		for(int i=1;i<=1500;i++){
			int x=a[1],y=a[2],z=a[3];
			a[4]=i;
			sort(a+1,a+5);
			if(check()==1){
				puts("YES");
				printf("%d",i);
				return 0;
			}
			a[1]=x,a[2]=y,a[3]=z;
		}
		puts("NO");
	}
	else{
		if(check()==0)puts("NO");
		else puts("YES");
	}
	return 0;
}
```


---

## 作者：lgx57 (赞：1)

愚蠢至极的题目。

对 $n$ 进行分类讨论。

1. $n=0$

任意输出一组。

2. $n=1$

设那个数为 $x=a_1$，且为最小的数。

再设 $a_2=x+b,a_3=x+c,a_4=x+d$，那么有：

$$d=x+\frac{b+c}{2},b+c=d$$

解得 $b=c=2x,d=3x$。代入输出即可。

3. $n \ge 2$

直接枚举剩下的数，判断是否满足条件即可。我枚举到了 $5000$。

---

## 作者：nj_peak (赞：0)

大暴力！！！
## 题目大意
如果一个序列满足 $(a1+a2+a3+a4)/4=(a2+a3)/2=a4-a1$ 那么就枚举 $n$ 从 $1$ 到 $4$ 的情况。
## 思路
我们将等式恒等变形：
$$(a1+a2+a3+a4)/4=a4-a1$$
$$a1+a4=a2+a3,5a1+a2+a3=3a4$$
$$3a1=a4,a2+a3=4a1$$
我们将 $n$ 分类就可以了！
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=114514;
int a[N]; 
int n;
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	sort(a+1,a+1+n);
	if(n==0){
		printf("YES\n1\n1\n3\n3\n");
		return 0;
	}
	else if(n==1){
		a[4]=3*a[1];
		a[2]=a[1];
		a[3]=3*a[1];
		printf("YES\n%d\n%d\nd\n",a[2],a[3],a[4]);
		return 0;
	}
	else if(n==2){
		if(3*a[1]>=a[2])
			printf("YES\n%d\n%d\n",4*a[1]-a[2],3*a[1]);
		else 
			printf("NO\n");
		return 0;
	}
	else if(n==3){
		if(a[3]==3*a[1])
		printf("YES\n%d\n",4*a[1]-a[2]);
		else if(3*a[1]>=a[3] && a[2]+a[3]==4*a[1]) 
			printf("YES\n%d\n",3*a[1]);
		else if(a[3]%3==0 && a[1]+a[2]==4*a[3]/3) 
			printf("YES\n%d\n",a[3]/3);
		else 
			printf("NO\n");
		return 0;
	}
	else if(n==4){
		if((a[1]+a[2]+a[3]+a[4])==(a[2]+a[3])*2 && (a[2]+a[3])*2==(a[4]-a[1])*4) 
			printf("YES\n");
		else 
			printf("NO\n");
		return 0;
	}
	return 0;
}
```


---

## 作者：luuia (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF488B)

## 题意
四个数 $a_1,a_2,a_3,a_4$ 满足

$$
\begin{cases} a_1 \leq a_2 \leq a_3 \leq a_4  \\
{{a_2 + a_3}\over 2} = {{a_1 + a_2 + a_3 + a_4}\over 4} \\
{{a_1 + a_2 + a_3 + a_4}\over 4} = a_4 - a_1 \\
\end{cases}
$$

给了其中的几个数，要求构造出这样的一个序列，不存在解输出 ```NO```。

## 分析
### 推导
这几个式子看起来非常难算，我们考虑化简式子。

**第一个式子：**

$${{a_2 + a_3}\over 2} = {{a_1 + a_2 + a_3 + a_4}\over 4}$$

两边同时 $\times \,4$，

$$2a_2 + 2a_3 = a_1 + a_2 + a_3 + a_4$$

移项，

$$a_1 + a_4 = a_2 + a_3$$

**第二个式子：**

$${{a_1 + a_2 + a_3 + a_4}\over 4} = a_4 - a_1$$

两边同时 $\times \,4$，

$$a_1 + a_2 + a_3 + a_4 = 4a_4 - 4a_1$$

移项，

$$a_2 + a_3 = 3a_4 - 5a_1$$

联立两个式子，我们得到：

$$3a_4 - 5a_1 = a_1 + a_4$$

$$a_4 = 3a_1$$

所以，
$$
\begin{cases} a_1 \leq a_2 \leq a_3 \leq a_4  \\
a_4 = 3a_1 \\
a_2 + a_3 = 4a_1 \\
\end{cases}
$$

### 构造
我们对 $n=0,1,2,3$ 分别进行讨论：

- ### $n = 0$

$n = 0$，意思即不给任何数，那么我们自己造一个数据即可。

比如 $a_1 = 2,a_2 = 3,a_3 = 5,a_4 = 6$ 即可，直接输出 ```YES``` 和数据即可。

- ### $n = 1$
不妨设输入的数为 $a_1$，那么我们自己构造一组符合题意的数据即可。

那么由上面的式子我们得到 $a_4 = 3a_1,a_2 + a_3 = 4a_1$。

所以我们构造 $a_1 = a_1,a_2 = 2a_1,a_3 = 2a_1,a_4 = 3a_1$ 即可。

- ### $n = 2$

到这里，难度就渐渐上升了。

同样的，我们不妨设输入的两个数为 $a_1,a_2(a_1 \leq a_2)$，

那么 $a_3 = 4a_1 - a_2,a_4 = 3a_1$。

但是，还有 $a_1 \leq a_2 \leq a_3 \leq a_4$ 的要求需要满足。

我们代入上面推出来的式子，得到

~~这个式子有点问题，要继续往下看~~

$$a_1 \leq a_2 \leq 4a_1 - a_2 \leq 3a_1$$

第一个不等号是输入时要求满足的，$a_2,a_3$ 又是可以互换的，所以不必判断它们两个之间的关系，那么我们要证明的式子其实是下面这个：

$$a_1 \leq \min{(a_2,4a_1-a_2)}\leq \max{(a_2,4a_1-a_2)} \leq 3a_1$$

- 当 $a_2 \leq 4a_1-a_2$，即 $a_2 \leq 2a_1$ 时，上式明显满足；

- 当 $a_2 \geq 4a_1-a_2$，即 $a_2 \geq 2a_1$ 时，只需要 $a_2 \leq 3a_1$，综合起来即 $2a_1 \leq a_2 \leq 3a_1$。

将以上两种情况结合起来，我们得到 $a_2 \leq 3a_1$。

那么如果输入的数据不满足较大数小于较小数的 $3$ 倍，那么输出 ```NO```，否则输出 $4a_1-a_2,3a_1$ 即可。

- ### $n = 3$

最难的来了。分 $3$ 种情况讨论：

- #### 输入的数为 $a_1,a_2,a_3(a_1 \leq a_2 \leq a_3)$

这个非常简单，由 $a_4 = 3a_1$ 构造即可。

那么满足 $a_1 \leq a_2 \leq a_3 \leq a_4$ 需要满足两个式子：

$$
\begin{cases} 
a_2 + a_3 = 4a_1  \\
3a_1 \geq a_3 \\
\end{cases}
$$

输出 $3a_1$ 即可，否则进行下一个情况的判断。

- #### 输入的数为 $a_1,(a_2\,\,\,or\,\,\,a_3),a_4(a_1 \leq (a_2\,\,\,or\,\,\,a_3) \leq a_4)$

不妨设给出了 $a_3$，那么 $a_2$ 满足以下式子：

$$
\begin{cases} 
a_2 = 4a_1-a_3  \\
a_2 = a_1 + a_4 - a_3 \\
\end{cases}
$$

只需要 $a_4 = 3a_1$ 即可，这时候是一定满足 $a_1 \leq a_2 \leq a_3 \leq a_4$ 的。

输出 $4a_1 - a_3$ 即可，否则进行下一个情况的判断。

- #### 输入的数为 $a_2,a_3,a_4(a_2 \leq a_3 \leq a_4)$

这时候

$$a_1 = {{a_4}\over{3}}$$

需要满足

$$
\begin{cases} 
a_2 + a_3 = {{4}\over {3}}a_4  \\
{{a_4}\over 3} \leq a_2\\
a_4 \equiv 0 \pmod 3\\
\end{cases}
$$

输出 ${a_4\over 3}$ 即可，否则输出 ```NO```。

- ### $n = 4$

这时候只需要判断给定的 $4$ 个数是否满足条件即可。可以先将四个数用 sort 排序，再判断是否符合以下式子即可。
$$
\begin{cases}
a_4 = 3a_1 \\
a_2 + a_3 = 4a_1 \\
\end{cases}
$$

符合输出 ```YES```，不符合输出 ```NO```。

综上所述，我们就可以写出本文的 AC 代码。

## 代码

下面是 AC 代码：[AC 代码](https://www.luogu.com.cn/paste/yipr8bg4) 

[我的 AC 记录](https://www.luogu.com.cn/record/121859324)
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,a[5];
	cin >> n;
	for(int i = 1;i <= n;i++)
	{
		cin >> a[i];	
	}
	if(n == 0)
	{
		cout << "YES" << endl;
		cout << "2" << endl;
		cout << "3" << endl;
		cout << "5" << endl;
		cout << "6" << endl;	
	}
	else if(n == 1)
	{
		cout << "YES" << endl;
		cout << 2 * a[1] << endl;
		cout << 2 * a[1] << endl;
		cout << 3 * a[1] << endl;	
	}
	else if(n == 2)
	{
		sort(a + 1,a + 3);
		if(a[2] <= (3 * a[1]))
		{
			cout << "YES" << endl;
			cout << 4 * a[1] - a[2] << endl;
			cout << 3 * a[1] << endl;
		}
		else
		{
			cout << "NO" << endl;
		}
	}
	else if(n == 3)
	{
		sort(a + 1,a + 4);
		if(a[3] == (3 * a[1]))//这里需要注意：因为这里是没有输入a[4]的，所以a[3]其实对应的是分析中的a[4] 
		{
			cout << "YES" << endl;
			cout << 4 * a[1] - a[2] <<endl;//同样的，这里的a[2]实际上是分析里的a[3] 
		}
		else if(((3 * a[1]) >= a[3]) && ((4 * a[1]) == (a[2] + a[3])))
		{
			cout << "YES" << endl;
			cout << 3 * a[1] << endl;
		}
		else if(((4 * a[3] / 3) == (a[1] + a[2])) && ((a[3] % 3) == 0))//a[3]对应的是分析中的a[4] 
		{
			cout << "YES" << endl;
			cout << a[3] / 3 << endl;//a[3]对应的是分析中的a[4] 
		}
		else
		{
			cout << "NO" << endl;
		}
	}
	else
	{
		sort(a + 1,a + 5);
		if(((a[4] == (3 * a[1]))) && ((a[2] + a[3]) == (4 * a[1])))
		{
			cout << "YES" << endl;
		}
		else
		{
			cout << "NO" << endl;
		}
	}
	return 0;
}
```


---

## 作者：MY_Lee (赞：0)

**推导**

原式有些恶心，我们给他变形一下（过程略），得到：
$$
\left\{
\begin{aligned}
a_4&=3a_1\\
a_1+a_4&=a_2+a_3=4a_1\\
a_1\le a_2&\le a_3\le a_4\\
\end{aligned}
\right.
$$

~~好看多了~~

发现对于不同的 $n$，可能有不同的处理方式。

考虑分类讨论

---
**分类讨论**

- $\large n=0$

不给任何数？嘿嘿嘿，我随便造一组即可。例如：`1 2 2 3`

- $\large n=1$

先暂定给出了数 $x$。

注意到 $x$ 不一定是 $a_1$,考虑再分类讨论 $x$ 的位置吗?

其实并不用。只要你构造出了一组通解，$x$ 不论在哪里都没问题了。给出构造：
|  | $a_1$ | $a_2$ | $a_3$ | $a_4$ |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| 值 | $x$ | $x+1$ | $3x-1$ | $3x$ |

那么，如何证明 $a_1\le a_2\le a_3\le a_4$ 呢？

$$
\begin{aligned}
a_2&\ge a_1\\
a_4&\ge a_3\\
a_3-a_2&=2x-2\\
\because x&\ge1\\
\therefore 2x-2&\ge1>0
\therefore a_3>a_2
\end{aligned}
$$

证毕。

---
- $\large n=2$

记给定的是 $x,y(x\le y)$

> 其实， $a_2$ 与 $a_3$ 没有必然的大小关系。只要 $a_1\le \min(a_2,a_3),a_4\ge \max(a_2,a_3)$ 即可。

直接给构造吧。
|  | $a_1$ | $a_2$ | $a_3$ | $a_4$ |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| 值 | $x$ | $y$ | $4x-y$ | $3x$ |

根据之前的推导，
$$
\left\{
\begin{aligned}
x&\le 4x-y\\
3x&\ge y\\
3x&\ge 4x-y
\end{aligned}
\right.
$$

分析：
$$
\begin{aligned}
\because x&\le 4x-y\\
\therefore y&\le 3x\\
\because 3x&\ge 4x-y\\
\therefore y&\ge x
\end{aligned}
$$

搞了半天，综合起来就一句话：$y\le 3x$

所以，只要 $y\le 3x$，就可以构造出上面表格的解。否则即为 `NO`。

---
- $\large n=3$

重头戏。令给定的是 $x,y,z(x\le y\le z)$。

- 当未给出 $a_1$ 时。

显而易见，
|  | $a_1$ | $a_2$ | $a_3$ | $a_4$ |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| 值 | $\dfrac z3$ | $x$ | $y$ | $z$ |

显然，需要有
$$
\left\{
\begin{aligned}
z&\equiv0\pmod3\\
x+y&=\dfrac43z\\
\dfrac z3&\le x
\end{aligned}
\right.
$$

- 当未给出 $a_2$ 或 $a_3$ 时。

显而易见，
|  | $a_1$ | $a_2$ | $a_3$ | $a_4$ |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| 值 | $x$ | $x+z-y=4x-y$ | $y$ | $z$ |

显然，需要有
$$
z=3x
$$

- 当未给出 $a_4$ 时。

显而易见，
|  | $a_1$ | $a_2$ | $a_3$ | $a_4$ |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| 值 | $x$ | $y$ | $z$ | $3x$ |

显然，只要
$$
\left\{
\begin{aligned}
4x&=y+z\\
z&\le 3x
\end{aligned}
\right.
$$
即可。

- 除此之外，直接 `NO`

---
- $\large n=4$

呵呵呵，直接判断可不可行即可。

---
放一下 $n=3$ 的代码。
```cpp
if(n==3){
	if((a<<2)==b+c&&c<=a*3){
		puts("YES");
		write(a*3);puts("");
		return 0;
	}
	if(c==a*3){
		puts("YES");
		write((a<<2)-b);puts("");
		return 0;
	} 
	if(c%3==0&&a>=c/3&&a+b==c+c/3){
		puts("YES\n");
		write(c/3);puts("");
		return 0;
	}
	puts("NO");return 0;
}
```

---
**广告**

[来逛逛？](https://moon-snow.blog.luogu.org/)

---

## 作者：Error_Eric (赞：0)

### 题意

有一个长度为 $4$ 的序列 $a$，满足 $a_1\le a_2\le a_3\le a_4$，并且$\frac{a_2+a_3}{2}=\frac{a_1+a_2+a_3+a_4}{4}=a_4-a_1$ 。

给定 $a$ 中的 $n$ 个数，求一种 $a$ 的构造。

如果存在解，输出``YES``并用任意的顺序给出没有给定的数字。

如果不存在解，输出``NO``。

有多组数据。

### 思路

设 $k= \frac{a_2+a_3}{2}=\frac{a_1+a_2+a_3+a_4}{4}=a_4-a_1$

那么 $a_2+a_3=2k(1),a_1+a_2+a_3+a_4=4k(2),a_4-a_1=k(3)$ 。

整理得 $a_1=0.5k,a_2+a_3=2k,a_4=1.5k$ 。

然后分类讨论。

对于 $n=0$ 直接输出 ``1 1 3 3 ``。

对于 $n=1$ 不妨设输入的值为 $a_1$，直接输出 $2a_1,2a_1,3a_1$ 。

对于 $n=2$ 分以下四类讨论

> 较小的数为 $a_1$ 较大的数为 $a_2,a_3$ 之中的一个。

> 较小的数为 $a_1$ 较大的数为 $a_4$。

> 两者均为 $a_2,a_3$ 中的一个。

> 较小的数为 $a_2,a_3$ 中的一个，较大的数为 $a_4$。

根据以上的条件可以算出其它的 $a_i$ ，再根据以上的条件判断一下是否可行，是否按照从小到大的顺序即可。

对于 $n=3$ 根据没有给定的数的位置进行分类讨论，思路与 $n=2$ 类似，不再展开。

对于 $n=4$ 直接判断。

有了这些，代码就不难写了，但是还是很难一次对...

### Code

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
using namespace std;
#define rei register int 
void readln(int &I){
	char C=getchar();I=0;
	while(!isdigit(C))C=getchar();
	while( isdigit(C))I=I*10+C-'0',C=getchar(); 
}
int t,x[5];
int main(){
	int a[5],n;
	readln(n);
	for(rei i=1;i<=n;i++)readln(a[i]);sort(a+1,a+n+1);
	//for(rei i=1;i<=n;i++)printf("%d_",a[i]);putchar(10);
	switch(n){
		case 0:
			puts("YES\n1\n1\n3\n3");
			break;
		case 1:
			printf("YES\n%d\n%d\n%d\n",a[1]*2,a[1]*2,a[1]*3);
			break;
		case 2:
			if(a[1]*3==a[2])printf("YES\n%d\n%d\n",a[1]*2,a[1]*2);
			else if(a[2]<a[1]*3)printf("YES\n%d\n%d\n",a[1]*3,a[1]*4-a[2]);
			else if((a[1]+a[2])&3==0)printf("YES%d\n%d\n",(a[1]+a[2])>>2,(a[1]+a[2]>>2)*3);
			else puts("NO");
			break;
		case 3:
			if(a[1]*4==a[2]+a[3])
				printf("YES\n%d\n",a[1]*3);
			else if(a[1]*3==a[3] and a[1]*4-a[2]<=a[3] and a[1]*4-a[2]>=a[1])
				printf("YES\n%d\n",a[1]*4-a[2]);
			else if(a[1]*4==a[2]+a[3])
				printf("YES\n%d\n",a[1]*3);
			else if(a[3]%3==0 and a[3]/3*4==a[1]+a[2])
				printf("YES\n%d\n",a[3]/3);
			else puts("NO");
			break;
		default:
			if(a[4]==a[1]*3 and a[2]+a[3]==4*a[1])puts("YES");
			else puts("NO");
			break;
	}
	return 0;
}
```


---

