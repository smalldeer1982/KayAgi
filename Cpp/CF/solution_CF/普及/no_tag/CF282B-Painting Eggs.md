# Painting Eggs

## 题目描述

## 问题描述

有$n$ 个蛋，A和G需要给这$n$ 个鸡蛋涂色。A涂第$i$ 个鸡蛋得到的钱为$A_i$ ，G涂第$i$ 个鸡蛋得到的钱为$G_i$ ，且满足$A_i+G_i=1000$ 。需要把这$n$ 个鸡蛋分配给A和G，求怎样分配使得A和G得到的钱$S_A$ 和$S_G$ 的差不超过$500$ 。

## 样例 #1

### 输入

```
2
1 999
999 1
```

### 输出

```
AG
```

## 样例 #2

### 输入

```
3
400 600
400 600
400 600
```

### 输出

```
AGA
```

# 题解

## 作者：皮卡丘最萌 (赞：2)

此题第一篇题解。

由于这道题目有$SPJ$，所以我们只需要找出一组可以使$|SA-SG≤500|$的解即可。

**考虑贪心**。记A的总钱数为$SA$，G的的钱数为$SG$，A涂第$i$个鸡蛋得到的钱为$A_i$，G涂第$i$个鸡蛋得到的钱为$G_i$。在每次读入2个数后，**分别算出**A涂第$i$个蛋后两人钱数差异$t_1$ 和 G涂第$i$个蛋后两人钱数差异$t_2$。

这里$t_1=|SA+A_i-SG|$，$t_2=|SG+G_i-SA|$。

然后取$t_1$和$t_2$中较小的值，$t_1$小则A涂，否则G涂。

时间复杂度$O(n)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)&&ch!='-')ch=getchar();
    if(ch=='-')f=-1,ch=getchar(); while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
    return x*f;
}                 

int main(){
  int n,x,y,t1,t2,i,s1=0,s2=0;
  n=read();
  for (i=1;i<=n;i++)
  {
	x=read(); y=read();
	t1=s1+x-s2;         //求出A涂时的差值
    if (t1<0) t1=-t1;   //取绝对值
	t2=s2+y-s1;         //求出G涂时的差值
    if (t2<0) t2=-t2;   //取绝对值
	if (t1<t2) {s1+=x; putchar(65); }
	  else {s2+=y; putchar(71);};    //输出结果
  }
}
```

蒟蒻刚转c++，码风烂请勿喷。

~~PS:这题一模一样的程序pascal会TLE，c++就过了。~~


---

## 作者：Stars_Traveller (赞：1)

## CF282B Painting Eggs 题解
### 思路
贪心题。

由于要使差值最小，我们不妨让每一次操作完后两人差值都最小。

设 $na$ 为当前 A 的总钱数，$ng$ 为当前 G 的总钱数。

每次操作时，若 A 涂了这枚蛋，则差值为 $|na-ng+a_i|$。反之，若 G 涂了这枚蛋，则差值为 $|ng-na+g_i|$。谁的差值最小，就让谁操作，并输出是谁操作的即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
signed main()
{
	cin.tie(0);
	cout.tie(0);
    cin>>n;
    int na=0, ng=0;
    for(int i=1;i<=n;i++)
    {
        int a, g;
		cin>>a>>g;
        if(abs(na+a-ng)<=abs(ng+g-na))
        {
            na+=a;
			cout<<"A";
        }
        else 
		{
			ng+=g;
			cout<<"G";
		}
    }
    return 0;
}

---

## 作者：Stars_visitor_tyw (赞：1)

## 题解：CF282B Painting Eggs
### 分析
考虑贪心。

由于题目要求差值最小，我们可以枚举每颗蛋算出差值，然后让取了这颗蛋后差值最小的人涂，记录是谁取了即可。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, a[1000005], g[1000005];
signed main()
{
	cin.tie(0);
	cout.tie(0);
    cin>>n;
     string str="";
    int nowa=0, nowg=0;
    for(int i=1;i<=n;i++)
    {
        // cin>>a[i]>>g[i];
        str+='#';
    }
    for(int i=1;i<=n;i++)
    {
        cin>>a[i]>>g[i];
        if(abs(nowa+a[i]-nowg)<=abs(nowg+g[i]-nowa))
        {
            nowa+=a[i];
            str[i-1]='A';
        }
        else 
		{
			nowg+=g[i];
			str[i-1]='G';
		}
    }
     cout<<str;
}

---

## 作者：_hxh (赞：1)

### 分析

对于任意一个鸡蛋，A 涂色可以得到 $A_i$ 这么多钱，G 涂色可以得到 $G_i$ 这么多钱，但是要保证 A 和 G 得到的钱 $S_A$ 和 $S_G$ 的差不超过 $500$。考虑到我们只要让最终结果 $S_A$ 和 $S_G$ 的差不超过 $500$ 就可以了，**所以我们每次分配鸡蛋时可以计算比较一下，分配给谁会使两人所得钱数的差更小一点**。但是为什么这样分配差值一定会在 $500$ 以内呢？

### 推理

对于这一步操作，${\color{red} 若前一步是合法的}$（即 $-500 \le S_A - S_G \le 500$），那么对于这次操作：

1. 要么使 $S_A - S_G$ 再减去一个数使其仍满足 $-500 \le S_A - S_G$；
2. 要么让 $S_A - S_G$ 加上一个数使其满足 $S_A - S_G \le 500$。

因为 $A_i + G_i = 1000$，所以以上两步操作总有一步是合法的，也就不存在无解的情况啦。

红色字体部分注：第二步的前一步是第一步，而第一步一定是合法的。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,x,y,A,G;
int main()
{
	cin >> n;
	while (n--)
	{
		cin >> x >> y;
		if (abs(A + x - G) < abs(G + y - A))
		{
			A += x;
			cout << 'A';
		}
		else
		{
			G += y;
			cout << 'G';
		}
	}
	return 0;
}
```

---

## 作者：Specthraimn (赞：1)

# Painting Eggs 题解
### 大致题意
有 $n$ 个蛋，两个人操作分别产生 $a_i,g_i$ 的价值，求一个令两人产生总价值之差不超过 $500$ 的操作方案。
### 解题思路
**贪心思想**，对于每一颗蛋，若第一个人操作后，产生的差小于第二个人操作产生的差，即 $\lvert sum1+a_i-sum2 \rvert \le \lvert sum2+g_i-sum1 \rvert$ 时，选择将第一个人加入答案。否则加入第二个人。时间复杂度 $O(n)$，空间复杂度 $O(1)$，可以通过本题。
### AC 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, sum1, sum2;
string ans;
signed main()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		int x, y;
		cin >> x >> y;
		if(sum1+x-y<=sum2+y-x)
		{
			sum1 += x;
			ans += 'A';
		}
		else
		{
			sum2 += y;
			ans += 'G';
		}
	}
	cout << ans << endl;
	return 0;
}

```
**完结撒花✿✿ヽ(°▽°)ノ✿**

---

## 作者：A_small_WA (赞：1)

一道简单的贪心（~~个人觉得达不到黄题难度~~）

首先，分析题意，可以发现贪心策略是在每输入一个 $A_i$ 和 $G_i$ 后，比较当前 $\left|suma+A_i-sumg\right|$ 
和 $\left|sumg+G_i-suma\right|$（$sumg,suma$ 表示当前花费）的大小，选较小的那个加入。这样就能保证每次 $suma$ 和 $sumg$ 的差值最小。

又因为题目保证 $G_i+A_i=1000$ 所以根本**不会有无解的情况**，不用输出 $-1$。

最后就是代码啦——

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int g,a,n,gm,am;
	cin>>n;
	long long suma=0,sumg=0;
	for(int i=1;i<=n;i++){
		cin>>am>>gm;
		int tmp1=abs(suma+am-sumg),tmp2=abs(sumg+gm-suma);
		if(tmp1<tmp2){
			cout<<"A";
			suma+=am;
		}else{
			cout<<"G";
			sumg+=gm;
		}
	}
	return 0;
} 
```
最后，本题洛谷爬虫有时会找错提交结果，导致 TLE On #10
，多提交几次即可。

这是蒟蒻的第4篇题解，支持一下孩子吧！

~~求管理员大大给过。~~

---

## 作者：xiaomimxl (赞：1)

# 题意：

第一个数 $N$ 表示鸡蛋数，然后 $n$ 行分别是 $A$ , $G$ 提供的钱，要求你每次选一个人获得相应的鸡蛋，然后获得相应的钱数。选择过程中要求满足：$|Sa-Sg|$ $\le500$ , $Sa$ , $Sg$ 分别表示获得的钱数的和。

# 思路：
贪心，每次选择的人确保要求的条件最小就可以，如果超过了 $500$ 说明不可能满足条件，比较无脑。

# AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5;
#define  LL long long
struct node
{
    int a,b;
};
node res[N*10+4];
int main()
{
    ios::sync_with_stdio(false);
    int sum = 0,num = 0;
    int n;
    cin>>n;
    for(int i =1 ;i <= n; ++i){
        cin>>res[i].a>>res[i].b;
    }
        string s;
    for(int i = 1;i <= n;++i)
    {
        if(abs(sum + res[i].a - num)>500){
            num += res[i].b;
            s += 'G';
        }
        else sum += res[i].a,s += 'A';
    }
    cout<<s;
}
```



---

## 作者：Dream_Stars (赞：0)

## 题目大意：
有 $n$ 个蛋，可以给 A 或给 G 涂色，A 涂第 $i$ 个蛋可以得到 $A_i$ 元，而给 G 涂可以得到 $G_i$ 元，我们要做的就是合理分配两个人的涂色方案，使两个人的金钱之**差**不超过 $500$ 元，如果**没有**合法的分配方案，那么就输出 $-1$。

## 算法分析：
这道题我们可以考虑**贪心**，我们可以来判断哪一个更多，做出局部的最优判断，最终可以得到最优解。要注意一点，就是**不可能**会没有合法的分配方案，因为，题目已经规定了 $A_i + G_i = 1000$ 所以，不需要考虑输出 $-1$ 的情况。并且，贪心的时间复杂度是 $\mathcal O(n)$，所以，这道题用贪心就可以解决了。

## 代码展示：
```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
ll x , y , n , s , s2 , t , t2;
string ans;//存放最终答案的字符串。
int main(){
  cin >> n;
  for(ll i = 1 ; i <= n ; i++){
  	cin >> x >> y;
  	t = abs(s + x - s2);
  	t2= abs(s2+ y - s );
//这里需要取绝对值，因为差值可能是负数。
  	if(t < t2) ans = ans + 'A' , s = s + x;
	else ans = ans + 'G' , s2= s2 + y;
//是让A涂还是让G涂。
  }
  cout<<ans;
  return 0;//return 养成好习惯
}
```

---

## 作者：Fuxh_18 (赞：0)

## [题目](https://www.luogu.com.cn/problem/CF282B)
题意十分明确。
## 思路
本题方法：[贪心](https://baike.baidu.com/item/%E8%B4%AA%E5%BF%83%E7%AE%97%E6%B3%95?fromModule=lemma_search-box)。因为 $A_i+G_i=1000$，所以不可能无解。每一次输入，判断给 $\texttt{A}$ 还是给 $\texttt{G}$ 的两人的差哪个更小，给那个人更小就输出谁。
## [AC](https://www.luogu.com.cn/record/168322597) Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int sa,sg; //存到目前 A 与 G 的总和 
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		int a,g,aa,gg;
		cin>>a>>g;
		aa=abs(sa+a-sg); //要取绝对值 
		gg=abs(sg+g-sa);
		if(aa>gg){
			sg+=g;
			cout<<"G";
		}
		else{
			sa+=a;
			cout<<"A";
		}
	}
	return 0;
}
```
~~达成成就，结束了？~~

---

## 作者：HEzzz (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF282B)

前置芝士：贪心

## 解析

题目条件是让 $S_A$ 和 $S_G$ 的差不超过 $500$，因为 $A_i$ 和 $G_i$ 的和为 $1000$，所以易得绝对有解的。

为了方便我们直接要求差最小，那我们可以直接贪心过去，通过每一次局部的涂色最优决策来决定整体最优决策。


## code

```cpp
#include<bits/stdc++.h>
#define _rep(i,a,b) for(int i=(a);i<=(b);i++)
#define _antirep(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
typedef long long LL;
typedef double db;
const LL N=1e5+1,inf=999999999999999999;
LL n,sa,sg,a,g; 
int main()
{
	scanf("%lld",&n);
	_rep(i,1,n)
	{
		scanf("%lld%lld",&a,&g);
		if(abs(sa+a-sg)<=abs(sg+g-sa)) //局部最优决策
          		cout<<"A",sa+=a;
		else 
          		cout<<"G",sg+=g;
	}
	return 0;
}

```

---

## 作者：seika27 (赞：0)

### 题意
有 $n$ 个蛋，可以选择给 $A$ 加工或是给 $G$ 加工。

如果是 $A$ 加工，那他就可以得到 $a_i$ 元。

如果是 $G$ 加工，那他就可以得到 $g_i$ 元。

要求最后两人赚的钱的差不能超过 $500$。

### 思路
题目要求差值小于 $500$。

那么我们就让差值最小即可。

对于每次选择，只有两种情况：给 $A$ 加工或者给 $G$ 加工。

那么给 $A$ 加工之后，差值 $C_A$ 为 $| sum_A+a_i-sum_G |$。

反之给 $G$ 加工之后，差值 $C_G$ 为 $| sum_G+g_i-sum_A |$。

对于每一次的选择，我们应该让当前的差值尽可能小，那么最后的差值也会更小。

如果 $C_A>C_G$，那么应该让 $G$ 来加工，因为这次让 $G$ 加工之后产生的差值较小。

如果 $C_A<C_G$，那么应该让 $A$ 来加工，因为这次让 $A$ 加工之后产生的差值较小。

详见代码。

（求求了给过一次吧
### code
```cpp
#include <bits/stdc++.h>
#define int long long 
#define cin std::cin
#define cout std::cout
int n;
int sa,sg;
signed main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x,y;
		cin>>x>>y;
		int A=abs(sa+x-sg);	//计算差值
		int G=abs(sg+y-sa);	//同上
		if(A<=G)sa+=x,cout<<"A";	//比较差值
		else sg+=y,cout<<"G";
	}
}
```

---

## 作者：tallnut (赞：0)

考虑贪心。分别计算出涂第一个人和涂第二个人所产生的新差，进行比较，取差的更小值即可。卡卡常就能过。

具体来说，设置两个变量 $sum1$（即题目中的 $S _ {a}$ 变量）和 $sum2$（即题目中的 $S _ {g}$ 变量），分别尝试
$$sum1 \gets sum1 + a _ {i}$$
和
$$sum2 \gets sum2 + g _ {i}$$
使用两个变量存储单独执行这两种情况后的新差，取更小值并更新 $sum1$ 和 $sum2$ 即可。

关于无解的情况：保证和为 $1000$，要求最终的差不超过 $500$，相对地一人加另一人就减，不会出现负数。
# AC 代码
[AC 记录](https://www.luogu.com.cn/record/126939397)，代码中有注释。
```
#include <iostream>
#include <cmath>
using namespace std;
int n,a,g,sum1,sum2,new_diff1,new_diff2;
int main()
{
   //卡常1
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	while (n--)
	{
		cin >> a >> g;
		//尝试加上第一个和第二个，分别作差，比较
		sum1 += a;
		new_diff1 = abs(sum1 - sum2);
		sum1 -= a;
		sum2 += g;
		new_diff2 = abs(sum1 - sum2);
		sum2 -= g;
		if (new_diff1 < new_diff2)
		{
			sum1 += a;
			//卡常2
			putchar('A');
		}
		else
		{
			sum2 += g;
			//卡常3
			putchar('G');
		}
	}
}
```

---

## 作者：Worlder (赞：0)

# CF282B Painting Eggs

## **题意**
输入一个变量 $n$，接下来输入的 $n$ 行输入 A，G 得到的钱，且满足 $A_i+G_i=10^3$，输出一行，表示分配方案，要满足 A 和 G 得到的钱 $S_a$ 和 $S_g$ 的差不超过 $500$。

------------
## **思路**
- **贪心**

我们使用贪心的思路，要保证和等于 $1000$，差不超过 $500$，用用一加一减的思路处理，达到条件输出即可。

~~**贪就完事了。**~~ 

- **关于无解**

保证和等于 $1000$，差不超过 $500$，一个人增加，一个人就会减少，两人不会出现负数的情况，那么就不会出现无解的情况。

------------

## AC 代码
```cpp
# include <bits/stdc++.h>
using namespace std ;

const int num_max = 1000, num_half = num_max / 2;

int main(){
    long long n; 
    cin >> n;
    int minus = 0, num_first = 0, num_second = 0;

    for (long k = 0; k < n; k++) {
        //cin >> num_first; cin >> num_second;
        scanf("%d %d", &num_first, &num_second);
        if (minus + num_first <= num_half) { 
            minus += num_first; 
            cout << "A"; 
        }
        else { 
            minus -= num_second; 
            cout << "G"; 
        }
    }
    cout << endl;
    return 0;
}
```

---

## 作者：_xxxxx_ (赞：0)

### 题意

给出 $n$，代表接下来会有 $n$ 次染色。第 $i$ 次会给出两个数 $x$ 和 $y$（$x+y=1000$），涂颜色 `A` 可以给第一个人加 $x$ 分。涂颜色 `G` 可以给第二个人加 $y$ 分。下面，你需要规划涂色的顺序，使得这两个人的分数之差不超过 $500$。

### 分析

因为 $x+y=1000$，所以分配的时候，一定是相对来说，一个人增加，一个人减少。因此，以第一个人为例，只要他的分数变为负数，就会立即将其改为正数，那么，就一定不会出现无解的情况。

这样，我们就可以用**贪心**的思路。

我们看第一个人加上 $x$，与第二个人加上 $y$，哪个会使他们俩最接近，就选加上哪个。

### 代码

```
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <algorithm>
#define LL long long
using namespace std;
const int N = 1e5 + 10;
const int INF = 0x3f3f3f3f;
int n, a, b;
//    一 二 
signed main()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		int x, y;
//		cin >> x >> y;用cin会TLE 
		scanf("%d%d", &x, &y);
		if(abs(b + y - a) > abs(a + x - b))//哪个更接近 
		{
			cout << "A";
			a += x;//总数加上 
		}
		else{
			cout << "G";
			b += y;//加上 
		}
	}
	return 0;
}
```

---

## 作者：SuperCowHorse (赞：0)

简单的贪心。

很好想的贪心思路：哪个差值少选哪个。

如样例 #1：

- 第一步，让 A 干，选 A 差值小；
- 第二步，让 G 干，选 G 差值小。若选了 A，差就会变成 $1000$，显然不行。

还有一点：不合法输出`-1`。进行推理：
- 题目中说 $a_i+g_i=1000$，那么：如果前一步合法，最少差 $-500$（$a-g$），那么，最多加上 $1000$ 后，差值又会变成 $+500$。

这意味着：不存在不合法状况。

所以可以不用存答案，输出即可。

Code：
``` cpp
//chenye3
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,a,g;
signed main(){
	scanf("%d",&n);
	for(int i=1,x,y;i<=n;++i){
		scanf("%d%d",&x,&y);
		if(abs(a+x-g)<abs(g+y-a)){//贪心
			printf("A");//直接输出
			a+=x;
		}
		else{
			printf("G");
			g+=y;
		}
	}
	return 0;
}
```

---

## 作者：许多 (赞：0)

非常简单的贪心。

我们从 $1$ 到 $n$ 一个一个分配，设 $ch$ 为目前 $S_A$ 与 $S_G$ 的差。

如果 $A_i+ch>500$ 就将第 $i$ 个鸡蛋分配给 $G$。否则就分配给 $A$。

通过不等式的性质可知，因为 $A_i+G_i=1000$，当 $A_i+ch>500$ 时 $ch-G_i>-500$。所以如果有解的话 $ch$ 最后一定 $>-500$ 且 $<500$。

所以如果最后 $ch>500$ 或 $ch<-500$ 就无解。

# 代码

```cpp
#include<bits/stdc++.h>
#include<cstdio>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'&&ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
	return x*f;
}
int n,a[1000100],g[1000100],ch=0;
string C[1000100];
int main(){
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read(),g[i]=read();
	for(int i=1;i<=n;i++){
		if(a[i]+ch>500)
			C[i]='G',ch-=g[i];
		else 
			C[i]='A',ch+=a[i];
	}
	if(ch<-500||ch>500)printf("-1");
	else for(int i=1;i<=n;i++)
		cout<<C[i];
	return 0;
}

```


---

## 作者：wanghaoran00 (赞：0)

### 翻译
~~懒得写了~~，题面里有。

### 思路
一眼贪心，发现 $a$ 值大就加 $g$，$g$ 大了就加 $a$。

AC code

```
#include<bits/stdc++.h>
using namespace std;
int n,a,g,cnta,cntg;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a,&g);
		if(abs(a+cnta-cntg)<=500){
			cnta+=a;
			printf("A");
		}
		else{
			cntg+=g;
            printf("G");
		}
	}
	return 0;	
}
```

---

