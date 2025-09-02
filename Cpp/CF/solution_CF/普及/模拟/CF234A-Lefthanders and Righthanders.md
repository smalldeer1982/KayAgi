# Lefthanders and Righthanders

## 题目描述

One fine October day a mathematics teacher Vasily Petrov went to a class and saw there $ n $ pupils who sat at the ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234A/666f6519688863e0a36337875170dd12050e1c31.png) desks, two people at each desk. Vasily quickly realized that number $ n $ is even. Like all true mathematicians, Vasily has all students numbered from 1 to $ n $ .

But Vasily Petrov did not like the way the children were seated at the desks. According to him, the students whose numbers differ by $ 1 $ , can not sit together, as they talk to each other all the time, distract others and misbehave.

On the other hand, if a righthanded student sits at the left end of the desk and a lefthanded student sits at the right end of the desk, they hit elbows all the time and distract each other. In other cases, the students who sit at the same desk, do not interfere with each other.

Vasily knows very well which students are lefthanders and which ones are righthanders, and he asks you to come up with any order that meets these two uncomplicated conditions (students do not talk to each other and do not bump their elbows). It is guaranteed that the input is such that at least one way to seat the students always exists.

## 样例 #1

### 输入

```
6
LLRLLL
```

### 输出

```
1 4
2 5
6 3
```

## 样例 #2

### 输入

```
4
RRLL
```

### 输出

```
3 1
4 2
```

# 题解

## 作者：Qerucy (赞：1)

这是一道构造题。

我们只需要把第 $a$ 个同学与第 $ a + \dfrac {n} {2} $ 个同学分配在一起即可。因为 $ 4 \le n $，所以这种做法不会出现相邻两个同学坐在一起的情况。

对于左右撇子的问题，我们只需要判断每组同学是否一个左撇子一个右撇子，如果是，就让右撇子的学生坐在桌子的右侧，左撇子的学生坐在桌子的左侧。
如果不是，就直接输出这一组两个同学的编号。

（~~不会有人有三只手吧~~）

对了，写这道题时注意加上文件读写。

代码：

```cpp
#include<cstdio>

using namespace std;

int n;
char a[100010];

int main(){
	freopen("input.in","r",stdin);
	freopen("output.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf(" %c",&a[i]);
	}
	
	for(int i=1;i<=n/2;i++){
		if(a[i]=='R'&&a[i+n/2]=='L') printf("%d %d\n",i+n/2,i);
		else printf("%d %d\n",i,i+n/2);
	}
	
	return 0;
}
```


---

## 作者：Hanriver (赞：1)

## CF234A 题解

[题面传送门](https://www.luogu.com.cn/problem/CF234A)  
路过，进来看了一下，~~突然想起自己好久没写题解了，于是进来水一发~~


------------
很显然，这个题目的关键就是这两个排列方式。然后我们发现条件二比条件一要特殊一点，于是我们从第二个条件开始分析：

```
1.如果一个右撇子的学生坐在桌子的左侧，一个左撇子的学生坐在桌子的右侧，  
他们也不能坐在一起。
```
即 $RL$ 组合是不行的。但再分析一下， $R$ 和 $L$ 的四种组合中只有这种是不行的（ $LR$ 组合可以），所以每当遇上 $RL$ 时，将其交换以后再输出。

再来看第一个条件：
```
2.编号相差1的学生（如1号和2号,2号和3号）不能坐在一起。
```
这个简单，CF构造题老套路了。让 $i$ 号学生和 $i+\dfrac{n}{2}$ 坐一起就可以了。  



### 上代码
```cpp
#include <bits/stdc++.h>
using namespace std;
char a[101];
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);//一定记得freopen
    int n;
    scanf("%d",&n);
    cin>>a;
    for(int i=0;i<=n/2-1;i++) 
    {
        if(a[i]=='R'&&a[i+n/2]=='L') printf("%d %d\n",i+n/2+1,i+1);
        else printf("%d %d\n",i+1,i+n/2+1);
    }
    return 0;
}
```
~~码风清奇勿怪~~





---

## 作者：Leonid (赞：0)

因为 n 是偶数，所以我们可以考虑将 $i$ 与 $i + \frac{n}{2}$ 配对，配对时如果 $s_i = \operatorname{R}$ 且 $s_{i + n/2} = \operatorname{L}$ 将两个数反过来输出即可。

```cpp
#include<cstdio>

using namespace std;

#define M 105

int n;
char s[M];

int main(){
	freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
	scanf("%d",&n);
	scanf("%s",s+1);
	for(int i=1;i<=(n>>1);++i){
		if(s[i]=='R'&&s[i+(n>>1)]=='L') printf("%d %d\n",i+(n>>1),i);
		else printf("%d %d\n",i,i+(n>>1));
	}
	return 0;
}
```


---

## 作者：Firstly (赞：0)

## **题目思路：**
这道题对于同桌的安排有两个要求：序号挨着的不能安排在一起，左边右撇子，右边左撇子不能安排在一起。

首先我们来考虑序号问题。要使两个序号挨着的不在一起，我们有很多种策略，例如把 $(i,i+2)$ 安排在一起，等等。但是为了循环更为方便，我们最好将 $(i,i+\frac{n}{2})$ 放在一起。

然后考虑左撇子右撇子的问题。可以发现：当左撇子右撇子互换时，这种问题就随之消除了。如样例二。

然后还有输出问题。我们可以将两个人的序号组成一个有序数对，并且将其推入到动态数组中。在程序最后按照顺序输出即可。（其实按照其他大佬们所写的直接在循环中输出也可以，但是我太弱了居然没想到）

## **Code:**

```cpp
#include<iostream>
#include<utility>
#include<vector>
#include<cstdio>
using namespace std;
char c[105];
int n;
vector<pair<int,int> >v;
int main(){
	freopen("input.txt","r",stdin);//注意本题需要使用文件读写
	freopen("output.txt","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>c[i];
	for(int i=1;i<=n/2;i++)
		if(c[i]=='R'&&c[i+n/2]=='L')//判定左撇子右撇子问题
			v.push_back(make_pair(i+n/2,i));
		else v.push_back(make_pair(i,i+n/2));
	for(int i=0;i<v.size();i++)
		cout<<v[i].first<<' '<<v[i].second<<endl;
    return 0;
}
```


---

## 作者：hanyuchen2019 (赞：0)

好水的构造题，**但一定要记得写 `freopen` ！！！**。

### part1 大致题意

把 $n$ 名学生分给 $\frac{n}{2}$ 个课桌，要求：

1. 编号相差 $1$ 的两名学生不能坐在一起；
2. 如果一个右撇子的学生（`R`）坐在桌子的左侧，一个左撇子的学生（`L`）坐在桌子的右侧，他们也不能坐在一起。

### part2 思路

第一个要求是 CF 的老套路了，直接把 $(i,\frac{n}{2}+i)$ 这两个人放在一起。

第二个要求也不难，如果出现左 `R` 右 `L` 的情况，直接把他们俩交换一下位置即可。

### part3 Code

```cpp
#include<iostream>
using namespace std;
char ch[105];
int main()
{
	freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    	cin>>ch[i];
    for(int i=1;i<=n/2;i++)//最后一对是(n/2,n)
    {
    	if(ch[i]=='R'&&ch[n/2+i]=='L')//要求2
    		printf("%d %d\n",n/2+i,i);//把两个人互换
    	else
    		printf("%d %d\n",i,n/2+i)；
    }
	return 0;
}
```
码字不易，点个赞再走吧~

---

## 作者：Colead (赞：0)

好吧这一题确实是没什么难度了。连文件输入输出都安排上了。

编号相邻的人不能坐在一起这个好说，回头再看，分析一下另一个条件。

满足某种条件的两个人不能一个在左一个在右？

翻译一下：把同桌左右调换一下就行了。

所以说任何两个人都可以坐在一起，不过是顺序问题。

那么随便怎么安排，不让两个相邻编号的人坐在一起就非常简单了，这里采取一个最简单的策略，也就是题目样例的策略。见代码。

```
#include<bits/stdc++.h>
using namespace std;
long long n;
char c[105]={};
int main()
{
	freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>c[i];
	}
	for(int i=1;i<=n/2;i++)
	{
		if(c[i]=='R'&&c[i+n/2]=='L')cout<<i+n/2<<" "<<i<<endl;
		else cout<<i<<" "<<i+n/2<<endl;
	}
	return 0;
}
```

不要忘记写本题唯一的亮点：文件。

---

## 作者：Li_zi_wei (赞：0)

~~还好我去看了一下CF 不然RE见祖宗~~

这一题是和**文件**读取有关的 你**写freopen**了吗？

### 思路

因为序号相连的两个人会“交头接耳” 所以我们直接看`i`和`n / 2 + i` 这样可以防止交头接耳 

接下来我们看看怎么样会`打手肘`

*   1.`LL`不会 
*   2.`LR`不会
*   3.`RL`会
*   4.`RR`不会

所以直接特判一下如果左边的是`R`就让ta直接到右边去——

### 代码如下——


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
string s;
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
    //不写freopen见祖宗
	
	cin >> n >> s;
	for(int i = 1;i <= n / 2;i ++)//总共n / 2 对同桌
	{
		if(s[i - 1] == 'R') //右手在左特判
		cout << n / 2 + i << " " << i << endl;
		else cout << i << " " << n / 2 + i << endl;//否则无论怎样都不会打手肘
	}
	return 0;
}

```

最后推荐一下[博](https://lzwblog.tk/)[客](https://www.luogu.org/blog/Li-zi-wei-program/)

P.S 两个字连接不一样哦

---

