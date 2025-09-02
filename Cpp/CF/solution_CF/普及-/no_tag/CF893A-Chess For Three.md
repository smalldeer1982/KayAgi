# Chess For Three

## 题目描述

A，B，C 三人下棋，A 和 B 先下，每次下完棋之后由现在观战的人（例如第一局就由 C）代替下输的人。
每次输入一个数表示谁赢了（A 是 $1$，B 是 $2$，C 是 $3$），如果每一次输入的赢家都不是当时旁观者，则输出 $\mathtt{YES}$，否则输出 $\mathtt{NO}$。

## 说明/提示

第一个样例顺序：  
A:B，A 胜  
A:C，A 胜   
A:B，B 胜 

第二个样例 B 输了第一场，可是他第二场赢了，矛盾，输出 $\mathtt{NO}$。

## 样例 #1

### 输入

```
3
1
1
2
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
2
1
2
```

### 输出

```
NO
```

# 题解

## 作者：rui_er (赞：4)

题意简述：三个人轮流下棋，每次输的当旁观者，判断题目给出的胜者是否是旁观者（即条件自相矛盾）。

---

思路：没啥意思，数据范围不大，考虑模拟。

我们记录 $sp$ 表示当前旁观者编号，初始值为 $3$。对于每一局，如果输入的胜者是旁观者，直接输出 `NO` 并退出。否则我们更新 $sp$。

由于负者变为旁观者，因此我们要取那个既不是胜者又不是原来的 $sp$ 的人当旁观者。我们可以判断原来的 $sp$，使用另两个编号的和减去胜者即可得到负者的编号。

如果到最后都没有退出，输出 `YES`。

时间复杂度 $O(n)$，空间复杂度 $O(1)$。

---

代码：

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
using namespace std;

int n, a, sp;

int main() {
	scanf("%d", &n);
	sp = 3;
	for(int i=1;i<=n;i++) {
		scanf("%d", &a);
		if(a == sp) return puts("NO"), 0;
		if(sp == 1) sp = 5 - a;
		else if(sp == 2) sp = 4 - a;
		else sp = 3 - a;
	}
	puts("YES");
	return 0;
}
```

---

## 作者：wzckd (赞：2)

## 本题主要在于考虑过程

这题乍一看，博弈论？？？

仔细一看，其实就是一个 _**模拟**_ 的过程

### 主要是判断根据之前的数据和新输入的数据有没有冲突
我们只需要一个数来一个记住观察者,然后根据输入推出下一个观察者,并且**每次输入进行一次比较**,如果矛盾直接输出

然后我们仔细思考可以知道，无论有几轮

### 观察者加两位比赛者的值都=6

所以每次求下一轮观察者直接
cpp
ser=6-a-ser; 

最后上代码

```cpp
#include<cstdio>
long long ser=3,n,a;
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a);
		if(ser==a) {printf("NO");return 0;}
		ser=6-a-ser; 
	}
	printf("YES");return 0; 
}
```
**昔人已乘 int 去**

**此地空余long long人**

**oi一去不复返**

**白云千载AFO**


## 谢谢观看 
退役蒟蒻的第一篇也是最后一篇题解

---

## 作者：BigJoker (赞：1)

# 0x00 思路

此题思路不难想到用模拟，首先用两个变量去存储当前在下棋的两个人，然后每次读入一个数，表示这局的赢家，如果赢家在当前下棋的两个人，那么按照题目规则去变就可以了，如果赢家是第三者，那么此时产生矛盾。

# 0x01 模拟

首先我们用 now1 和 now2 去代表当前正在下棋的两个玩家，初始值为 1 和 2，因为先开始下棋的两个人是 $ \texttt A$ 和 $ \texttt B$，然后接着会输入当前的赢家，如果赢家是 1，并且为 now1 或者 now2，那么我们就把和 $ \texttt A$ 在下棋的人置换成第三者，也就是没有下棋的那个人，那么赢家是 2 或者 3 也就同理。但是如果赢家是当前正在观棋的人，他下都没有下，不可能赢，所以直接输出 $ \texttt N  \texttt O$ 就可以了。当棋下完的时候，说明没有产生矛盾，直接输出 $ \texttt Y \texttt E \texttt S$ 就可以了。

# 0x02 代码

```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=l;i<=r;i++)
#define dep(i,r,l) for(int i=r;i>=l;i--)
using namespace std;
int t,now1,now2;
int main(){
	scanf("%d",&t);
	now1=1,now2=2;
	while(t--){
		int x;
		scanf("%d",&x);
		if(now1==x){
			if(x==1){
				if(now2==2) now2=3;
				else now2=2;
			}
			else if(x==2){
				if(now2==1) now2=3;
				else now2=1;			
			}
			else{
				if(now2==1) now2=2;
				else now2=1;
			}
		}
		else if(now2==x){
			if(x==1){
				if(now1==2) now1=3;
				else now1=2;
			}
			else if(x==2){
				if(now1==1) now1=3;
				else now1=1;			
			}
			else{
				if(now1==1) now1=2;
				else now1=1;
			}			
		}
		else{
			puts("NO");
			return 0;
		}
	}
	puts("YES");
	return 0;
}
```


---

## 作者：Jekyll_Y (赞：1)

## 题意
有三个人，两人人下棋，另一个当旁观者，当其中有人输
了后，旁观者去顶替输了的人接着下。
## 思路
数据范围不大，直接模拟就好了，用一个数组存起来当时谁在下棋，如果输入的数据与数组存的情况不符，直接输出“NO”就好了。
## 代码
```c
#include<cstdio>
#include<iostream>
using namespace std;
int n,p[4];
int main()
{
	cin>>n;
	p[1]=1;p[2]=1;
	for(int i=1;i<=n;i++)
	{
		int a;
		cin>>a;
		if(p[a]==0)
		{
			cout<<"NO";
			return 0;
		}
		for(int j=1;j<=3;j++)
		{
			if(j==a)continue;
			if(p[j]==0)p[j]=1;
			else p[j]=0;
		}
	}
	cout<<"YES";
	return 0;
}
```
### 完结撒花~


---

## 作者：䒛夢 (赞：0)

# 题意
有三个人打牌，谁输换谁下场，给你几个数判断是不是给错了。
# 思路
由于给的范围并不是很大每个都遍历一遍才300而已所以可以直接暴力把每种可能遍历一遍。
# 代码
```
#include<iostream>
#include<cstdio>
using namespace std;
int n;
bool v[4];//每个人的状态
int h[110];
int main()
{
	cin>>n;
	for(int i=1 ; i<=n ; ++i)
		cin>>h[i];
	v[1]=1;v[2]=1;//先把A,B定义好
	for(int i=1 ; i<=n ; ++i)
	{
		if(v[h[i]]==0)//只要说赢的这个人是旁观者直接结束
		{
			cout<<"NO";
			return 0;
		}
		for(int j=1 ; j<=3 ; ++j)
		{//每个遍历一遍
			if(j!=h[i]&&v[j]==1)
				v[j]=0;//输了就下场
			else if(v[j]==0)
				v[j]=1;旁观者上场
		}
		
	}
	cout<<"YES";//如果都没错就输出
	return 0;
}
```


---

## 作者：xxzjbd (赞：0)

## 题目大意
每次输入赢家，如果赢家是旁观者，输出 $NO$ ,否则输出 $YES$ ，即判断每次输入是否符合逻辑。

数据范围不大，直接模拟就好，记录当前的对局人与旁观者，每次输入判断是否是旁观者，不是就更新对局人与旁观者即可，模拟过程中开个变量记录中间量就能实现更新了。
## 代码如下
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main(){
	int n,w1=1,w2=2,w3=3,w4;
	cin>>n;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		if(x==w3){
			cout<<"NO";
			return 0;
		}
		if(x==w1){
			w4=w2;
			w2=w3;
			w3=w4;
		}
		else{
			w4=w1;
			w1=w3;
			w3=w4;
		}
	}
	cout<<"YES";
}
```
## 谢谢观赏

---

