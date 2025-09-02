# 肉と肉のぶつかり合い

## 题目描述

高桥和青木进行摔跤比赛。比赛规则如下：

- 高桥的战力为 $X$ ，青木的战力为 $Y$ 。

- 双方会从 $N$ 名备选摔跤手中各取得 $N/2$ 人的援军。

- 高桥和青木轮流交替按战力从大到小的顺序选援军，由高桥先选。

- 第 $i$ 名摔跤选手的战力为 $A_i$ ，一方的总战力为他们的首领的战力和援军的战力的总和。

- 战力大的一方获胜。

## 样例 #1

### 输入

```
2 2 2
3 1```

### 输出

```
Takahashi```

## 样例 #2

### 输入

```
2 2 100
3 1```

### 输出

```
Aoki```

## 样例 #3

### 输入

```
4 5 5
5 5 5 5```

### 输出

```
Draw```

# 题解

## 作者：____someone____ (赞：0)

### Description:
这个
[题目](https://www.luogu.com.cn/problem/AT_iroha2019_day1_d)
主要是贪心思想。

点
[这里](https://www.luogu.com.cn/blog/666someonebk999/solution-at-iroha2019-day1-d)
体验更好的阅读效果。

高桥和青木参加职业摔跤比赛，高桥的战斗力是 $x$，青木的战斗力是 $y$。现在给他们共 $n$ 个支援兵，每人可以选择 $\displaystyle\frac{n}{2}$ 个支援兵。第一个志愿兵的战斗力为 $a_1$，第二个为 $a_2$，$\ldots$，第 $n$ 个为 $a_n$。轮流选择，高桥先选。

高桥和他的援军和青木和他的援军之间，战斗力总和较大的一方获胜。但是，如果相等，则为平局。当高桥和青木全力以赴时，请你算出谁会获胜。

- 当高桥胜时输出 `Takahashi`
- 当青木胜时输出 `Aoki`
- 当平局时输出 `Draw`

### Solution:
一道很简单的贪心题，首先，高桥很明显第一个会选择战斗力最强的兵，而青木也就会选择战斗力第二的兵 $\cdots\cdots$

所以可以先把支援兵的战斗力排序，再加在高桥和青木的战斗力上，最后比较就行了。

### Code:

```cpp
#include<bits/stdc++.h>
using namespace std;

const int M=105;
int n,x,y;
int a[M];

bool cmp(int x,int y)//cmp从大到小排序
{
	return x>y;
}

int main()
{
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+1+n,cmp); //sort从大到小排序
	for(int i=1;i<=n;i++)
	{
		if(i%2)//高桥选
			x+=a[i];
		else //青木选
			y+=a[i];
	}
	if(x>y)cout<<"Takahashi"<<endl;
	else if(x==y)cout<<"Draw"<<endl;
	else cout<<"Aoki"<<endl;
	return 0;
}
```


---

## 作者：_ChongYun_ (赞：0)

# 解析

这道题是一道简单的模拟题。

首先，我们用两个变量来存高桥和青木的战力。

然后，我们用`sort`将数组从大到小排序。

接着，用一个`bool`变量来判断当前是谁在搬援兵。如果是自己搬援兵，就给自己那一方的总战力加上数组里的数，然后下一个就是对方搬援兵。

最后用简单的判断语句来判断哪一个总战力大，如果高桥战力大，输出`Takahashi`。如果青木战力大，输出`Aoki`。如果平手，输出`Draw`。

提示：小日子题行不换，爆零白学两年半。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,x,y;
long long a[114514];
long long cnt1=0,cnt2=0;
bool cmp(long long a,long long b){
	return a>b;
}
int main(){
	cin>>n>>x>>y;
	cnt1=x; cnt2=y;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1,cmp);
	bool flag=false;
	for(int i=1;i<=n;i++){
		if(flag==false){
			cnt1+=a[i];
			flag=true;
		}else{
			cnt2+=a[i];
			flag=false;
		}
	} 
	if(cnt1>cnt2){
		printf("Takahashi\n");
	}else if(cnt1<cnt2){
		printf("Aoki\n");
	}else{
		printf("Draw\n");
	}
	qwq;//防抄袭 
	return 0;
}


```


---

## 作者：wangyinghao (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_iroha2019_day1_d)

### 题意

高桥和青木进行摔跤比赛。比赛规则如下：

- 高桥的战力为 $X$ ，青木的战力为 $Y$ 。

- 双方会从 $N$ 名备选摔跤手中各取得 $N/2$ 人的援军。

- 高桥和青木轮流交替按战力从大到小的顺序选援军，由高桥先选。

- 第 $i$ 名摔跤选手的战力为 $A_i$ ，一方的总战力为他们的首领的战力和援军的战力的总和。

- 战力大的一方获胜。

### 分析

先对所有的选手战力排序可以开两个计数器存储高桥和青木的总战力，用循环累加。

那么问题就来了，怎么判断到底在挑第 $i$ 个人的时候是高桥挑人还是青木挑人呢？

我们可以使用一个变量 $flag$ 来判断，假设 $flag$ 为 $0$ 时代表高桥，$flag$ 为 $1$ 时代表青木，每循环一次就将 $flag$ 的值由 $0$ 变为 $1$，由 $1$ 变为 $0$。

这里介绍一种不用 ```if-else``` 的方法判断的语句：**三目运算符**。

这是三目运算符的表达式：```(表达式1)?(表达式2):(表达式3)```。

它的意思其实就是以下的代码：

```c
if(表达式1) 表达式2;
else 表达式3;
```

只不过和 ```if-else``` 相比，三目运算符的三个表达式必须都得填，而 ```if-else``` 可以只给出表达式 $1$ 和表达式 $2$。不过从效率上看，```if-else``` 的运行时间是三目运算符的两倍以上。

那么知道了这些，我们就可以写出代码了。

### AC code:

```c
#include<iostream>
#include<algorithm>
using namespace std;
int a[105];

int main(){
	int n,x,y,cnt1=0,cnt2=0;
	bool flag=0;
	cin>>n>>x>>y;
	cnt1=x;//两队的初始战力
	cnt2=y;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1,greater<int>());//从大到小排序
	for(int i=1;i<=n;i++){
		(flag==0)?(cnt1+=a[i]):(cnt2+=a[i]);//其中一个人挑人
		(flag==0)?(flag=1):(flag=0);//换另外一个人在下一次循环挑人
	}
	(cnt1>cnt2)?(cout<<"Takahashi"):((cnt1<cnt2)?(cout<<"Aoki"):(cout<<"Draw"));
	//对于有else if的判断语句，可以嵌套使用三目运算符
	cout<<endl;
	return 0;
}

```

---

