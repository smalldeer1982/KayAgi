# Ciel and Flowers

## 题目描述

Fox Ciel has some flowers: $ r $ red flowers, $ g $ green flowers and $ b $ blue flowers. She wants to use these flowers to make several bouquets. There are 4 types of bouquets:

- To make a "red bouquet", it needs 3 red flowers.
- To make a "green bouquet", it needs 3 green flowers.
- To make a "blue bouquet", it needs 3 blue flowers.
- To make a "mixing bouquet", it needs 1 red, 1 green and 1 blue flower.

Help Fox Ciel to find the maximal number of bouquets she can make.

## 说明/提示

In test case 1, we can make 1 red bouquet, 2 green bouquets and 3 blue bouquets.

In test case 2, we can make 1 red, 1 green, 1 blue and 1 mixing bouquet.

## 样例 #1

### 输入

```
3 6 9
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4 4 4
```

### 输出

```
4
```

## 样例 #3

### 输入

```
0 0 0
```

### 输出

```
0
```

# 题解

## 作者：monstersqwq (赞：4)

注意到 $r,g,b \le 10^9$，模拟无论如何都会超时，考虑找规律

一开始我写的是一份很不带脑子的结论代码，结论为：

$$ans=\left\lfloor\dfrac{r}{3}\right\rfloor+\left\lfloor\dfrac{g}{3}\right\rfloor+\left\lfloor\dfrac{b}{3}\right\rfloor+\min(r \bmod 3,g \bmod 3,b \bmod 3)$$

被 $2,2,3$ 这样一组手造数据 hack 了，秉承着“调不过就加入”的原则，分析得当 $r,g,b$ 模 $3$ 的余数分别为（无顺序）$0,2,2$ 且余数为 $0$ 的那种花的数量不少于 $3$ 朵，答案会变为：

$$ans=\left\lfloor\dfrac{r}{3}\right\rfloor+\left\lfloor\dfrac{g}{3}\right\rfloor+\left\lfloor\dfrac{b}{3}\right\rfloor+\min(r \bmod 3,g \bmod 3,b \bmod 3)+1$$

而且简单分析可得有且只有这样一种情况答案会变化，于是特判一下即可。

因为此题 $r,g,b$ 并无不同，所以先按 $r,g,b$ 模 $3$ 的余数排序，特判时代码简短一些。

代码：

```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <queue>
using namespace std;
struct flower
{
	int n;//某种花的数量
	int mo;//数量模3的余数
}a[5];
int ans;
bool cmp(flower a,flower b)
{
	return a.mo<b.mo;
}
int main()
{
	for(int i=1;i<=3;i++)
	{
		cin>>a[i].n;
		a[i].mo=a[i].n%3;
	}
	sort(a+1,a+4,cmp);//排序
    ans=a[1].n/3+a[2].n/3+a[3].n/3+min(a[1].mo,min(a[2].mo,a[3].mo));//正常情况下答案
    if(a[1].n>=3&&a[1].mo==0&&a[2].mo==2&&a[3].mo==2) ans++;//特判
	cout<<ans<<endl;
    return 0;
}
```


---

## 作者：fzj2007 (赞：4)

本蒟蒻自认为是本题的官方解法（？）。

# 第一步 读题

> `Fox Ciel`有 $r$ 朵红花，$g$ 朵绿花和 $b$ 朵蓝花。她想用这些花做几个花束。

> 有四种类型的花束：

> - 制作“红色花束”，要3朵红花。
> - 制作“绿色花束”，要3朵绿花。
>- 制作“蓝色花束”，要3朵蓝花。
>- 制作“混合花束”，要1朵红，1朵绿和1朵蓝花。
> 输出可以制作的最大数量的花束。

我们发现这是一个数论题。题目翻译较为详细，即按照花束制作方式来求出可能的最大数量的花束。

# 第二步 讲解

由于 $r,g,b \le 10 ^ 9$，所以我们肯定不能模拟。我们可以来考虑数论解法。

因为我们所有的花束均以 $3$ 为标准，所以我们可以从这里入手。我们发现：如果红，绿，蓝花束均为三，那么做红、绿、蓝共三个花束与制作三个混合花束是相同的，所以我们可以考虑余数。

我们可以枚举少使用一个和两个花来制作单色花束，然后来枚举这三种情况（不减少，减少一个，减少两个）来求得最大值。

# 第三步 代码

代码中有详细的注释！

```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
inline int read(){//快读
	int ans=0,flag=1;
	char ch=getchar();
	while((ch>'9'||ch<'0')&&ch!='-') ch=getchar();
	if(ch=='-') flag=-1,ch=getchar();
	while(ch>='0'&&ch<='9'){
		ans=(ans<<1)+(ans<<3)+(ch^'0');
		ch=getchar();
	}
	return ans*flag;
}
int a,b,c,ans;//分别代表读入数据，ans表示答案。
int main(){
	a=read(),b=read(),c=read();//读入
	ans=a/3+b/3+c/3+min(a%3,min(b%3,c%3));//最初始的（不减）
	if(a>=1&&b>=1&&c>=1) ans=max(ans,(a-1)/3+(b-1)/3+(c-1)/3+1+min((a+2)%3,min((b+2)%3,(c+2)%3)));//如果可以减（减完不是负数）的话就枚举另一种情况，这里因为是对3取模，所以减1和加2没有区别
	if(a>=2&&b>=2&&c>=2) ans=max(ans,(a-2)/3+(b-2)/3+(c-2)/3+2+min((a+1)%3,min((b+1)%3,(c+1)%3)));//同上，枚举减2
	printf("%d\n",ans);//输出答案
	return 0;
}

```

# 宣传

如果有帮助，请帮忙点赞，谢谢（撰文不易，dalao勿喷）！

---

## 作者：wmrqwq (赞：4)

# 原题链接

[CF322B Ciel and Flowers](https://www.luogu.com.cn/problem/CF322B)

# 题目简述

现在有 $r$ 朵红花，有 $g$ 朵绿花，有 $b$ 朵蓝花，现在可以做四种不同的花束：

- 制作“红色花束”，要 $3$ 朵红花。

- 制作“绿色花束”，要 $3$ 朵绿花。

- 制作“蓝色花束”，要 $3$ 朵蓝花。

- 制作“混合花束”，要 $1$ 朵红花，$1$ 朵绿花和 $1$ 朵蓝花。

求可以制作的最大数量的花束数量。

# 解题思路

刚开始看的时候觉得这是一道裸的贪心题目，只需要尽可能多的做混合花束，然后再判断即可，然后你发现你就在第十个点死了，因为假如说三种花的数量分别为 $3$，$5$，$5$，你就寄了。所以这时我们应该换一种贪心思路，先制作单色的花束，再制作混合的花束，这样就能让花束最多了，于是不难得出公式：

```ans=r/3+g/3+b/3+min(r%3,min(g%3,b%3))```。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define QwQ return 0;
long long a,b,c,sum;
int main()
{
	cin>>a>>b>>c;//输入每种花的数量
	cout<<a/3+b/3+c/3+min(a%3,min(b%3,c%3));
	//a/3，b/3，c/3均表示制作单色的花束，而min(a%3,min(b%3,c%3)表示制作的混合花束
	QwQ;
}//clbzdq
```

---

## 作者：linyuhuai (赞：1)

### 首先，读题知：

> + 制作“红色花束”，要 $3$ 朵红花。

> + 制作“绿色花束”，要 $3$ 朵绿花。

> - 制作“蓝色花束”，要 $3$ 朵蓝花。

> - 制作“混合花束”，要 $1$ 朵红，$1$ 朵绿和 $1$ 朵蓝花。

1. 设 $a=\min(r,g,b)$ ，我们可以得出一个公式：$ans=r+g+b-(3\times a)$ 。原理是先做最多“混合花束”直到 $r,g,b$ 的任意一个数等于 $0$ ，再去考虑其他花束。但这种方法会被 `3 5 5` 的数据干掉。

1. 我们可以再试着下改进更改下上一个步骤：做“混合花束”，但**不要全部做完，只到** $r,g,b$ 的任意一个数等于 $1$ 时就停止。然后再考虑其他花束。

结尾就输出以上 1，2 两个步骤中最大的数即可。

### Code：

```cpp
#include<bits/stdc++.h>
#define ll long long
const int INF = 0x7fffffff;

using namespace std;
int main() {
	int r,g,b;
	cin>>r>>g>>b;
	int ans=min(r,min(g,b));
	int r1=r-ans;
	int g1=g-ans;
	int b1=b-ans;
	ans+=r1/3+(g1/3)+(b1/3);
	int ans2=min(r,min(g,b))-1;
	if(ans2>=0) {
		int r2=r-ans2;
		int g2=g-ans2;
		int b2=b-ans2;
		ans2+=r2/3+(g2/3)+(b2/3);
	}
	cout<<max(ans,ans2);
}

```


---

## 作者：封禁用户 (赞：0)

## 题目描述

[Ciel and Flowers](https://www.luogu.com.cn/problem/CF322B)

## 算法思路

### 算法：找规律

看到数据范围 $0 \le r,g,b \le 10^9$，就可以想到不能用模拟。

看到样例
```cpp
4 4 4
```

想到先做单颜色的花束，再做混合颜色的花束。这样就能用掉尽可能多的花，使花束最多。

算式如下。

$ans = \lfloor \frac{r}{3} \rfloor + \lfloor \frac{g}{3} \rfloor + \lfloor \frac{b}{3} \rfloor + \min (r \bmod 3,g \bmod 3,b \bmod 3)$



## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll x,y,z,ans;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>x>>y>>z;
	ans=x/3+y/3+z/3+min(x%3,min(y%3,z%3));
	cout<<ans<<"\n";
	return 0;
}
```

评测记录：[WA](https://www.luogu.com.cn/record/109644199)。

hack 数据：

```cpp
2 2 3
```

发现这组数据我们写的程序跑出来是 $1$，因为在这个数据里做 $1$ 束蓝色花束，不如做 $2$ 束混合花束。我们继续手算找这样的 hack 数据，发现只有余数为

```cpp
2 2 0
```

时答案会错误，所以只要特判就行了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll x,y,z,ans;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>x>>y>>z;
	if((x%3==0&&y%3==2&&z%3==2&&x>=3)||(x%3==2&&y%3==0&&z%3==2&&y>=3)||(x%3==2&&y%3==2&&z%3==0&&z>=3))
	{
		ans++;
	}
	ans=ans+x/3+y/3+z/3+min(x%3,min(y%3,z%3));
	cout<<ans<<"\n";
	return 0;
}
```

评测记录：[AC](https://www.luogu.com.cn/record/114911294)。

---

## 作者：Back_Stuff (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF322B)

## 思路

这题虽然看着很简单，但是……特别坑。

有 $r$ 朵红花，$g$ 朵绿花和 $b$ 朵蓝花，可以做成不同的花束。

- 制作“红色花束”，要 $3$ 朵红花。

- 制作“绿色花束”，要 $3$ 朵绿花。

- 制作“蓝色花束”，要 $3$ 朵蓝花。

- 制作“混合花束”，要 $1$ 朵红，$1$ 朵绿和 $1$ 朵蓝花。

我们首先做出红色花束、绿色花束、蓝色花束，记录下剩下的花朵数。

用剩下的花朵做混合花束，正常情况是这样的代码应该这样写：

`min(min((r%3),(g%3)),(b%3))`

这之后，我们再考虑~~可恶的~~特殊情况。

我们定义 $cnt1$ 和 $cnt2$ 来计数。

遍历三种花：

- 如果这朵花原来的朵数是 $\geq 3$ 的，而且它除以 $3$ 的余数是 $0$，$cnt1$ 加一。

- 如果这朵花的朵数除以 $3$ 的余数是 $2$，$cnt2$ 加一。

最后如果 $cnt1=1$ 而且 $cnt2=2$，那么就将已制作的花束的数量加一。

现在我就把这代码献上，不喜勿喷。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100001;
typedef long long ll;
ll r,g,b,cnt1,cnt2,s;
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    cin>>r>>g>>b;
    s=r/3+g/3+b/3+min(min((r%3),(g%3)),(b%3));
    if(r%3==0&&r>=3) cnt1++;
    if(g%3==0&&g>=3) cnt1++;
    if(b%3==0&&b>=3) cnt1++;
    if(r%3==2) cnt2++;
    if(g%3==2) cnt2++;
    if(b%3==2) cnt2++;
    if(cnt1==1&&cnt2==2) s++;
    cout<<s;
    //fclose(stdin);
    //fclose(stdout);
    return 0;
}
```

---

## 作者：hyc1026 (赞：0)

说实话这道题挺坑的……

题意很清晰了，拿到这道题我的第一想法肯定是这样的：

做单色花束，做完不就行了？

于是我们得到了第一个式子：

$$sum=\lfloor\dfrac{r}{3}\rfloor+\lfloor\dfrac{g}{3}\rfloor+\lfloor\dfrac{b}{3}\rfloor$$

显而易见，不行。没有用完的花束还可以做混合的呀？于是我们得到了第二个式子：

$$sum=\lfloor\dfrac{r}{3}\rfloor+\lfloor\dfrac{g}{3}\rfloor+\lfloor\dfrac{b}{3}\rfloor+\min\{r\bmod 3,g\bmod3,b\bmod3\}$$

信心满满的提交，WA。

原因出在如果三种花余数分别为 $2,2,0$ 时（无序，余数为 $0$ 的那种花必须大于 $0$ 朵），我们可以发现，最终答案要加 $1$。

原因：构造一些单色花束使得花的个数变成 $(2,2,3)$，然后构造两个混合花束，而不是按照上式的做法构造一个单色花束。

AC Code:

自己对余数的判断写的太麻烦了，仅供参考。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int a,b,c;
    cin >> a >> b >> c;
    int p = a, q = b, r = c;
    int sum = a/3 + b/3 + c/3;
    a %= 3;
    b %= 3;
    c %= 3;
    if(a == 2 && b == 2 && c == 0 && r > 0) sum++;
    if(a == 0 && b == 2 && c == 2 && p > 0) sum++;
    if(a == 2 && b == 0 && c == 2 && q > 0) sum++;
    cout << sum + min(min(a,b),c);
}
```

---

## 作者：cxy000 (赞：0)

这道题的题目是这样的：

首先，大部分情况下都是先出掉（斗地主后遗症了属于是）能够捆成一捆的花。

但为什么说是大部分呢？

因为（排完序后）的 $a_1$，$a_2$，$a_3$ 的值分别为 $0$，$2$，$2$ 的时候需要特判（即余数为 $0$ 的花花的数量 $\le 3$ 的情况）。

然后上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
struct node {
	int x;
}a[4];
bool operator <(const node a,const node b){
	return a.x%3<b.x%3;
}
int main(){
	cin>>a[1].x>>a[2].x>>a[3].x;
	sort(a+1,a+4);
	if(a[1].x>=3 && a[1].x%3==0 && a[2].x%3==2 && a[3].x%3==2) cout<<a[1].x/3+a[2].x/3+a[3].x/3+min(a[1].x%3,min(a[2].x%3,a[3].x%3))+1;
	else cout<<a[1].x/3+a[2].x/3+a[3].x/3+min(a[1].x%3,min(a[2].x%3,a[3].x%3));
	return 0; 
}
```


---

## 作者：shengyeqi (赞：0)

## 题面

[题目传送门](https://www.luogu.com.cn/problem/CF322B)

## 思路

看这个数据范围，模拟式不可能的了，只能用数论来解决。

分四段计算即可。

第一段是混合花束，代码如下。

```
    int sum=a/3+b/3+c/3+min(a%3,min(b%3,c%3));//混合花束
```


接下来三段分别计算三种花束就行了，代码如下。

```
    if(a%3==0&&b%3==2&&c%3==2&&a>=3)sum++;
    if(a%3==2&&b%3==0&&c%3==2&&b>=3)sum++;
    if(a%3==2&&b%3==2&&c%3==0&&c>=3)sum++;
```


最后的输出结果就是把四段的加起来就行了。

## 完整代码

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int a,b,c;
    cin>>a>>b>>c;
    int sum=a/3+b/3+c/3+min(a%3,min(b%3,c%3));//混合花束
    if(a%3==0&&b%3==2&&c%3==2&&a>=3)sum++;//三种花束
    if(a%3==2&&b%3==0&&c%3==2&&b>=3)sum++;
    if(a%3==2&&b%3==2&&c%3==0&&c>=3)sum++;
    cout<<sum;
    return 0;
}
```


---

