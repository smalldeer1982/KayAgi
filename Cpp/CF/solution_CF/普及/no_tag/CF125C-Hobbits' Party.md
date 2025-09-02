# Hobbits' Party

## 题目描述

Everyone knows that hobbits love to organize all sorts of parties and celebrations. There are $ n $ hobbits living in the Shire. They decided to organize the Greatest Party (GP) that would last for several days. Next day the hobbits wrote a guest list, some non-empty set containing all the inhabitants of the Shire. To ensure that everybody enjoy themselves and nobody gets bored, for any two days (say, days A and B) of the GP there existed at least one hobbit, invited to come on day A and on day B. However, to ensure that nobody has a row, for any three different days A, B, C there shouldn't be a hobbit invited on days A, B and C. The Shire inhabitants are keen on keeping the GP going for as long as possible. Your task is given number $ n $ , to indicate the GP's maximum duration and the guest lists for each day.

## 样例 #1

### 输入

```
4
```

### 输出

```
3
1 2 
1 3 
2 3 
```

## 样例 #2

### 输入

```
5
```

### 输出

```
3
1 2 
1 3 
2 3 
```

# 题解

## 作者：Feyn (赞：3)

[link](https://www.luogu.com.cn/problem/CF125C)

一道比较基础的模拟题。

先分析题意。题目中说“对于任意两天，都要有至少有同一位宾客被邀请，但是对于任意三天，都不能有同一个宾客被邀请”，也就是说合法方案中每个宾客参加的天数不会超过两次。那么我们可以把每个参加了两天的宾客看成是一条边，天是结点，由于“任意两天”都有相同宾客，那么这张图应该是完全图，题目中人的限制就变成了对这张图边数的限制。

根据完全图的边数公式（点数 $n$，边数就是 $\frac{n(n-1)}{2}$），就可以求出最大的、边数不超过限制的完全图大小，二分（大炮打苍蝇行为）或者枚举都可以。构造方案上可以直接枚举任意的两个结点连边即可。

```cpp
#include<bits/stdc++.h>
//#define feyn
using namespace std;
const int N=210;
inline void read(int &wh){
    wh=0;int f=1;char w=getchar();
    while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
    while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
    wh*=f;return;
}

int m,n=1,now,a[N][N],cnt[N];

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
	#endif
	
	read(m);while(n*(n-1)/2<=m)n++;n--;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			a[i][++cnt[i]]=++now;
			a[j][++cnt[j]]=now;
		}
	}
	printf("%d\n",n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=cnt[i];j++)printf("%d ",a[i][j]);
		putchar('\n');
	}
	
	return 0;
}
```



---

## 作者：wangyixuan_s_father (赞：3)

~~抢占首篇题解~~
本题第一篇题解，做的不好，广大谷民们多多见谅

## 题意简述

有 $n$ 个人能参加聚会，每天聚会没有人数上限，但每天人数需要一样，一个人如果参加聚会就必须且只能参加两天，任意两天都需要有至少同一个人参加，不是每个人都必须参加，求最多天数和一个方案。

## 解题思路

此题有三个重要条件：每天人数一样，一人出现两次和天数最多。那我们就可以构造一个最佳方案矩阵，共有 $m+1$ 天聚会，第一天从 $1$ 到 $m$ 人参加，第二天第一人为 $1$，后面为 $m+1$，$m+2$，...第三天第一人为 $2$，第二人为 $m+1$，后面为 $2m$，$2m+1$，...以此类推。

代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[201][201];//200够用
int main()
{
    int n,m=0;
    cin>>n;
    if(n==2)//特判（不知道为啥弄不出来所以加了一个特判）
    {
        cout<<2<<endl<<"1 2"<<endl<<"2 1"<<endl;
        return 0;
    }
    while(m*m+m<=2*n)//枚举最大天数同时构造矩阵
    {
        int cnt=1,tmp=1;//把矩阵分成两半赋值
        for(int i=1;i<=m;i++)
        {
            for(int j=i;j<=m;j++)
            {
                a[i][j]=tmp;
                tmp++;
            }
        }
        for(int j=1;j<=m;j++)
        {
            for(int i=j+1;i<=m+1;i++)
            {
                a[i][j]=cnt;
                cnt++;
            }
        }
        m++;//相当于m=m+1
    }
    cout<<m<<endl;
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<m;j++)
        {
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;//完结撒花
}
```

---

## 作者：王梓涵 (赞：1)

# CF125C Hobbits' Party 题解

## 1. 题目大意
有一个派对，现在有 $n$ 个人参加，题目要求我们构造出一种参加方式，满足条件且可以维持的天数最大：

- 任意两天中至少有一个相同的人参加
- 任意三天中不能有一个相同的人参加

输出最大天数并给出构造方案。

## 2. 题目分析
思维 + 构造的题目。假设当前的最大天数 $m = 4$ ，那么我们需要构造如下矩阵：

$\text{1 2 3 4}$

$\text{1 5 6 7}$

$\text{2 5 8 9}$

$\text{3 6 8 10}$

$\text{3 6 8 10}$

可能看完后有点懵，下面我一步一步来解释为什么这样构造。首先第一行我们直接排列，以及第一列如下排列：

$\text{1 2 3 4}$

$1$

$2$

$3$

$3$

然后 $\text{1 2 3 4}$ 就都不能用了，开始用 $5$ 再填：

$\text{1 2 3 4}$

$\text{1 5 6 7}$

$\text{2 5}$

$\text{3 6}$

$\text{3 6}$

这样第二行与其他的每一行也满足条件了，如此构造下去，我们最终会得到一个 $m \times (m - 1)$ 的矩阵。

构造起来也比较简单，沿着对角线分成两个部分，然后分别构造就是答案了，至于这个 $m$，我们用一个 for 循环找就可以了，因为矩阵中一共有 $2 \times n$ 个元素，只要满足 $m \times (m - 1) \leqslant 2 \times n$，找到最大值就行了。

## 3. AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define N 201 // 定义数组，据题意200足够
int a[N][N];

int main()
{
	double n; // 此处为double
	cin >> n;
	double t = (double(sqrt(8 * n + 1) - 1)) / 2.0;
	int num = t + 1, cnt = 0;
	cout << num << endl;
	for (int i = 1; i <= num - 1; ++i)
		for (int j = i; j <= num - 1; ++j)
			a[i][j] = ++cnt;
	cnt = 0; // 初始化cnt
	for (int i = 1; i <= num - 1; ++i)
		for (int j = i + 1; j <= num; ++j)
			a[j][i] = ++cnt; // 再次进行循环操作
	for (int i = 1; i <= num; i++)
	{
		for (int j = 1; j <= num - 1; ++j)
			cout << a[i][j] << " ";
		cout << endl;
	}
	return 0; //完结撒花
}
```


---

## 作者：longStone (赞：0)

# CF125C Hobbits' Party题解
简略的说，就是有 $x$ 个人，任何人都必须参加正好 $2$ 次聚会，同时任何两天都要有至少同一个人，输出举办几天和每天有哪些人参加聚会。
## 观察
在 $n$ 小于 $6$ 时，输出可以为：
```
3
1 2
1 3
2 3
```
在 $n$ 小于 $10$ 但是大于等于 $6$ ，输出可以为：
```
4
1 2 4
1 3 5
2 3 6
4 5 6
```
很明显，如果要举办新的一次聚会，那这一次聚会的人必须参加过一次前面的聚会，如果之前有过 $x$ 天聚会，则举办下一次聚会就需要 $x + 1$ 人。
## 思路
每够 $x$ 个人，就在每天加一个 $x$ 人中的一人，最后在新的这一天加入所有这 $x$ 人。\
用一个 $cnt$ 记录上次填的数，每填一次就 $+ 1$ 就可以了。\
那么既然规律找到了，那么我们只需要用代码做出这个图就可以了。
## 代码
因为 $n \le 10000$，所以用 int 就可以，而 $10000$ 个人举办的聚会开不了多少天，二维数组适当开就可以。

```cpp
#include "bits/stdc++.h"
using namespace std;
int n, cnt = 1,a[1005][1005],len = 1;
int main()
{
	
	cin >> n;
	while(n - len >= 0)
	{
		for(int i = 0;i < len;i++)
        	{
			a[len][i] = cnt;
			a[i][len - 1] = cnt;
            		cnt++;
		}
		n -= len;
		len++;
	}
	cout << len << '\n';
	for(int i = 0;i <= len - 1;i++)
	{
		for(int j = 0;j <= len - 2;j++)		cout << a[i][j] << ' ';
		cout << endl;
	}
	return 0;
}
```

---

## 作者：Allanljx (赞：0)

## 思路
通过构造发现最后的矩阵行数一定比列数大一，而且矩阵一定长成这样：

$1$ $2$ $4$ $7$……

$1$ $3$ $5$ $8$……

$2$ $3$ $6$ $9$……

$4$ $5$ $6$ $10$……

$7$ $8$ $9$ $10$……

然后就可以用这 $n$ 个数去构造这个矩阵，然后找一个最大的 $d$ 满足 $d\times (d+1)$ 小于 $2\times n$。最后输出这 $d$ 行 $d-1$ 列。

## 代码
```cpp
#include<iostream>
using namespace std;
int n,x1,x2,y1,y2;
int a[155][155];
signed main()
{
	cin>>n;
	x1=2,y1=1,x2=1,y2=1;//两个一起赋值
	for(int i=1;i<=n;i++)
	{
		a[x1][y1]=i;//赋值
		a[x2][y2]=i;//赋值
		if(y1==y2)//边界
		{
			x1++;
			y1=1;
			x2=1;
			y2++;
			continue;
		}
		y1++;
		x2++;
	}
	int d=0;
	while(d*(d+1)<=2*n)//找行数和列数
	{
		d++;
	}
	cout<<d<<endl;
	for(int i=1;i<=d;i++)
	{
		for(int j=1;j<=d-1;j++)
		{
			cout<<a[i][j]<<' ';
		}
		cout<<endl;
	}
}
```


---

