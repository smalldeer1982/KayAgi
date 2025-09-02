# Pixels

## 题目描述

Flatland is inhabited by pixels of three colors: red, green and blue. We know that if two pixels of different colors meet in a violent fight, only one of them survives the fight (that is, the total number of pixels decreases by one). Besides, if pixels of colors $ x $ and $ y $ $ (x≠y) $ meet in a violent fight, then the pixel that survives the fight immediately changes its color to $ z $ $ (z≠x; z≠y) $ . Pixels of the same color are friends, so they don't fight.

The King of Flatland knows that his land will be peaceful and prosperous when the pixels are of the same color. For each of the three colors you know the number of pixels of this color that inhabit Flatland. Help the king and determine whether fights can bring peace and prosperity to the country and if it is possible, find the minimum number of fights needed to make the land peaceful and prosperous.

## 说明/提示

In the first test sample the country needs only one fight to achieve peace and prosperity. Besides, it can be any fight whatsoever. For example, let's assume that the green and the blue pixels fight, then the surviving pixel will be red. As a result, after the fight there are two red pixels. There won't be other pixels.

In the second sample the following sequence of fights is possible: red and blue, green and red, red and blue. As a result, after all fights there is one green pixel left.

## 样例 #1

### 输入

```
1 1 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 1 0
```

### 输出

```
3
```

# 题解

## 作者：L_zaa_L (赞：5)

## 分析
就是让三个数，要么加（这个数加，让其他两个数减），要么减（同上）。最后让我们将其中的两个数变成零就行了，所以可以根本在求最小值的时候，可以只算其中的两个数，另外的一个数可以根本不管，而算这两个数又有条件——他们必须要奇偶性相同，因为每次计算要么加，要么减，两个数的差就会拉开或拉近 $2$ 的距离，所以他们的差必须是 $2$ 的倍数。（不然不能算到相同）然后再枚举三个数选两个进行相等的计算，并记录这三种情况中，最小的。

#### 实现

求出两个数的平均值，并求出这两个数到平均值的距离（就是使两个数相等的最小的次数），并加上平均值（将两个数变成零）。

#### 后传

由于 $0 \le a,b,c \le 2^{31}$，所以要开```long long```~~（不知道有没有和我一样上当受骗的）~~。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,c,as1=1e+11,as2=1e+11,as3=1e+11;//三个答案赋值最大数，不然求最小数会出现零
int main(){
	cin>>a>>b>>c;
	if((a+b)%2==0){//判断奇偶性
		long long x=abs(a-(a+b)/2),s=(a+b)/2;//x是两个数到平均值的距离，s是平均值
		as1=x+s;//计算最小的次数
	}
	if((a+c)%2==0){
		long long x=abs(a-(a+c)/2),s=(a+c)/2;
		as2=x+s;
	}
	if((b+c)%2==0){
		long long x=abs(b-(b+c)/2),s=(b+c)/2;
		as3=x+s;
	}//同上
	cout<<min(as1,min(as2,as3));//求出最小数
	return 0;
}
```
记住要开```long long```。

---

## 作者：123456zmy (赞：3)

~~这是一道数学题。~~
___
题意：  
给你三个整数 $a,b,c$，你每次可以把其中两个数减少 $1$，另一个数增加 $1$，问至少需要几次操作可以把其中两个数变成 $0$（其实是不会有无解的情况的）。
___
~~经过观察可以发现~~，操作的顺序与答案无关，那么最后的结果可以转化为由两个相同的数字加到另一个数字直到那两个都为 $0$。所以要先让两个数字相同。

~~再次观察可以发现~~，每次操作可以把两个数字间的差值改变 $2$，那么就只要挑两个差值是偶数的数字转到相同再进行之前说的操作就行了。由于每次操作都会把选出的数较大的减少 $1$，答案就是选出的数中的较大值了，因为 $3$ 个数中至少有两个奇偶性相同，所以一定有解。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[3];
int main()
{
	scanf("%lld%lld%lld",&a[0],&a[1],&a[2]);
	sort(a,a+3);
	if((a[1]-a[0]&1)==0)printf("%lld",a[1]);
	else printf("%lld",a[2]);
	return 0;
}
```

---

## 作者：gaoleng_luogu_name (赞：2)

### 题目大意
[传送门](https://www.luogu.com.cn/problem/CF209B)，题目说的很清楚。
### 思路及做法
由于最后是要让两个数变为 $0$ 的，所以就需要让两个数相同，然后一直减 $1$ 就行了。那如果没有相同的两个数呢？通过观察易得，一次操作会产生 $2$ 的差值。所以我们只需要找到两个差值为偶数的数，经过来回加减就可以得到结果。由于此题必有解，所以**不会出现找不到**的情况。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a[5];//记得开long long
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin>>a[1]>>a[2]>>a[3];
    sort(a+1,a+3+1);//正是因为方便排序开的数组
    if((a[2]-a[1])%2==0) cout<<a[2];
    else cout<<a[3];
    return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/123742233)

---

## 作者：nightwatch.ryan (赞：1)

## 思路

每次动作产生的差为 $2$ ，所以只要挑两个差为偶数的数转到相同再按照说的操作就行了。

由于要排序，所以我认为用数组比较好。
## 注意

第 $35$ 个测试点特别奇葩，正好超出 `int` 类型
```
输入：2147483648 2147483648 2147483648  
输出：2147483648
```

所以要用 `long long` 类型
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long a[5]={0};
	for(int i=0;i<3;i++)
	{
		cin>>a[i];
	}
	sort(a,a+3);
	if((a[1]-a[0])%2==0)
	{
		cout<<a[1];
	}else{
		cout<<a[2];
	}
	return 0;
}

```


---

## 作者：Rookie_t (赞：1)

我们看一下样例 $1$，

输入 $a$，$b$，$c$ 后先排序，排序后序列为 $1\;1\;1$。

1. 0 0 1

我们再看一下样例 $2$，

输入 $a$，$b$，$c$ 后，

先排序，排序后序列为 $0\;1\;3$。

1. 1 0 2
2. 0 1 1
3. 1 0 0

所以，我们可以得出结论，当 $a_2 - a_1$ 是偶数时，


需要 $a_2$ 次操作，

否则，需要 $a_3$ 次操作。

下面贴代码： 

```cpp
#include<bits/stdc++.h>//万能头
#define int long long//不开long long见祖宗 
using namespace std;
int a[10]; 
signed main(){
	ios::sync_with_stdio(false);//加快cin cout 
	for(int i = 1;i<=3;i++){
		cin>>a[i];//输入 
	}
	sort(a+1,a+3+1);//排序 
	if(!((a[1]-a[2])%2)){
		cout<<a[2];//样例2的情况 
		return 0;//直接结束 
	}
	cout<<a[3];//样例1的情况
	return 0;
}
```


---

## 作者：Ultra_Cyno_0052 (赞：0)

# CF209B [Pixels](https://www.luogu.com.cn/problem/CF209B)

## 思路：
当两个数相同时，只要将总次数加上两个数的值即可，但如何将两个数变相同是要解决的问题，先看一下样例 2，图示如下：（~~灵魂画师出场~~）
![捕获.JPG](https://img1.imgtp.com/2023/09/27/NTYT4rUl.JPG)
根据上面的图片，我们可以先排序，然后确定一个最小值，让总次数加上次小值减最小值（差为偶数才可以），此时有两个最小值，总次数再加上最小值即可，也就是输出次小值。

## 代码：
```cpp
#include<iostream>
using namespace std;
int a[5];
int main() {
	cin >> a[1] >> a[2] >> a[3];
   sort(a + 1, a + 1 + n);
   if (a[2] - a[1] % 2 != 0) cout << a[3];
   else cout << a[2];
}
```

参考 @xiaoluotongxue2012 的题解；

---

## 作者：Tachibana27 (赞：0)

题意体面已经解释的很清楚了，这里不再赘述。

## 思路

我们不难发现如果 $2$ 个数相同那这件事就好办了。

既然它的操作是对 $2$ 个数进行减运算，那么剩下的一个数必然是加，所以我们先不管它。

每次操作都是差值改变 $2$，那么我们挑 $2$ 个差值为偶数的不就行了？而 $3$ 个数中必然有 $2$ 个数差值是偶数，将 $2$ 个差值为偶数的数调成相同，便直接输出相同的数即可。



## 代码

```cpp
#include<bits/stdc++.h>
#define int long long//不开long long 见祖宗 
inline int read(){
   	int s=0;
   	int w=1;
   	char ch=getchar();
   	for(;ch<'0'||ch>'9';ch=getchar())
    	if(ch=='-')
			w=-1;
   	for(;ch>='0'&&ch<='9';ch=getchar())
		s=s*10+ch-'0';
   	return s*w;
}

void write(int x) {
	if(x<0){
    	putchar('-');
    	x=-x;
  	}
  	if(x>9)
    	write(x/10);
	putchar(x%10+'0');
	return;
}//快读快写，自动略过 
int a[5];//由于需要排序，故使用数组 
signed main(){
	for(int i=1;i<=3;i++)
		a[i]=read();
	std::sort(a+1,a+1+3);
	if(!((a[2]-a[1])&1))//等同于(a[2]-a[1])%2==0，也就是第2个数和第1个数的差值为偶数 
		write(a[2]);//输出第二个数 
	else
		write(a[3]);//否则输出第3个数 
	return 0;//完结撒花！ 
}
```

---

## 作者：封禁用户 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF209B)

# First 题意

给你三个数字，你可以让两个数 $-1$，另一个数 $+1$，求使得有两个数为 $0$ 最小操作次数。

# Second 思路

题目中有如下隐含条件。

1. 操作先后顺序无所谓。

2. 题目一定有解，因为只要你操作 $Max$ 次，一定可以。

所以，只需要判断之操作较小两个数是否可行。

首先，可以操作 $Min$ 次，较小两个数一直减小，$Max$ 一直增大。

最后，$Min$ 会变成 $0$，然后较小两个数交替加减。

哪什么情况下可以有解呢？其实就是差为偶数时，交替加减可以两个都变成 $0$。

否则的话，就操作 $Max$ 次。

# Third Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
ll a, b, c;
il void ssort (ll &a, ll &b, ll &c){//排序
	if (a > b) swap(a, b);
	if (b > c) swap(b, c);
	if (a > b) swap(a, b);
}
int main(){
	scanf ("%lld %lld %lld", &a, &b, &c);
	ssort (a, b, c);
	if (!((b - a) & 1)) printf ("%lld", b);//只操作较小数
	else printf ("%lld", c);
	return 0;
}

```

---

## 作者：hanyuchen2019 (赞：0)

不妨设最终的状态为 $(a,0,0)$。

由于这三个数不可能为负数，且顺序不重要，所以最终状态只能由 $(a-1,1,1)$ 通过 $(+1,-1,-1)$ 的方式得来。

同理，我们可以知道，如果某一个状态为 $(a-x,x,x)$ ( $a \ge x$ )，则可以通过 $x$ 次操作达到目标状态。

而状态 $(a-x,x,x)$ 可以从 $(a-x+y,x+y,x-y)$ 在 $y$ 次 $(-1,-1,+1)$操作后得来，每进行一次操作，$+1$ 的项和 $-1$ 的两项之间的差值会减小 $2$。

只要某两个数之间的差可以被 $2$ 整除，即有两个数奇偶性相同，就有解，但是这里有 $3$ 个数，一定有两个数奇偶性相同，因此**此题必有解**。

如题目给定的状态为 $(a,b,c)$ ，且满足 $a \ge b \ge c$，$b \equiv c\pmod2$，即 $b,c$ 奇偶性相同。

我们执行 $(-1,-1,+1)$ 操作，$\frac{b-c}{2}$ 次操作后，状态为 $(a-\frac{b-c}{2},b-\frac{b-c}{2},b-\frac{b-c}{2})$。

注：（$b-\frac{b-c}{2}=c+\frac{b-c}{2}$）

$b$ 和 $c$ 已经相等，我们执行 $(+1,-1,-1)$ 操作，$b-\frac{b-c}{2}$ 次操作后，达到目标状态 $(a+c,0,0)$。

我们一共操作了 $\frac{b-c}{2}+b-\frac{b-c}{2}=b$ 次。没错，刚好操作了 $b$ 次=.=

另外有一件事：这题要开 `long long`，否则你会 `WA on #35`。

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
bool cmp(long long a,long long b){return a>b;}
int main()
{
	long long a[4];
	cin>>a[1]>>a[2]>>a[3];
	sort(a+1,a+4,cmp);//a[1]>=a[2]>=a[3]
	if((a[2]-a[3])%2==0)
		cout<<a[2];
	else cout<<a[1];//为什么这里要输出最大的数，请读者根据上面的方法自行思考，不再赘述
 	return 0;
}
```

---

## 作者：user470883 (赞：0)

## 思路：

数学题。

看题目，每次相当于将 $1$ “移植”到另一个数上面，于是每次动作产生的差就为 $2$，只要挑两个差值是偶数的数字转到相同再进行题目说的操作即可。

**注意**：不开 `long long`见祖宗。由于涉及到排序，代码里我就用数组输入了。

## AC CODE:
```
#include<bits/stdc++.h>
#define ll long long
#define INF 2000000000
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	ll a[3];
	cin >> a[0] >> a[1] >> a[2];
	sort(a,a+3);
	if((a[1]-a[0])%2==0)
	{
		cout << a[1] << endl;
	}
	else 
	{
		cout << a[2] << endl;
	}
	return 0;
}

/*Things to check before submit:
1. did you forget long long ?
2. did you still CE?
3. = or == , n or m ,++ or -- , i or j , > or >= , < or <=
4. If contains "not", why not Reverse thinking or few affect?
5. is there anything extra to output?
6. keep it simple
7. can part of the code can with c++function replace?
8. smile while submit the code*/
```

有问题欢迎私我！

---

