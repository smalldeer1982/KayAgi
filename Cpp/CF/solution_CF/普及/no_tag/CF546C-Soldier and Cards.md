# Soldier and Cards

## 题目描述

Two bored soldiers are playing card war. Their card deck consists of exactly $ n $ cards, numbered from $ 1 $ to $ n $ , all values are different. They divide cards between them in some manner, it's possible that they have different number of cards. Then they play a "war"-like card game.

The rules are following. On each turn a fight happens. Each of them picks card from the top of his stack and puts on the table. The one whose card value is bigger wins this fight and takes both cards from the table to the bottom of his stack. More precisely, he first takes his opponent's card and puts to the bottom of his stack, and then he puts his card to the bottom of his stack. If after some turn one of the player's stack becomes empty, he loses and the other one wins.

You have to calculate how many fights will happen and who will win the game, or state that game won't end.

## 说明/提示

First sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF546C/13fabc002be9b868c475a6223b80932fbf64aac8.png)Second sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF546C/baf8f9cbd8baa7b7a7d1f276ff7ae6d3445560b3.png)

## 样例 #1

### 输入

```
4
2 1 3
2 4 2
```

### 输出

```
6 2```

## 样例 #2

### 输入

```
3
1 2
2 1 3
```

### 输出

```
-1```

# 题解

## 作者：Cappuccino_mjj (赞：5)

直接建立两个队列模拟即可。

---

## [题目传送门](https://www.luogu.com.cn/problem/CF546C)
题目意思：

有两个人玩牌，每一轮拿自己牌堆最顶上的牌拼点，谁大谁赢，赢的那一方将赢来的牌放在自己牌堆的底部，然后再将自己刚刚用来拼点的牌放入自己牌堆的底部。只要有一个玩家的牌堆空了，对方就赢了。请输出一共玩的轮数和赢家的编号，如果一直无法结束比赛，则输出 $-1$。

---

思路：

直接建立两个队列，将初始的牌分别放进两个队列，然后按照游戏规则模拟，每过一轮就记一次数。只要有一个队列空了，就输出轮数和赢家的编号；如果超过 $1000000$ 轮后还没结束，就输出 $-1$。

---

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int k1,k2;
queue<int>q1;
queue<int>q2;
int cnt;
int main()
{
	cin>>n;
	cin>>k1;
	for(int i=1,x;i<=k1;i++)
	{
		cin>>x;
		q1.push(x);
	}
	cin>>k2;
	for(int i=1,x;i<=k2;i++)
	{
		cin>>x;
		q2.push(x);
	}
	while(!q1.empty()&&!q2.empty())
	{
		cnt++;
		if(cnt>=1000000)
		{
			cout<<-1;
			return 0;
		}
		int t1=q1.front();
		q1.pop();
		int t2=q2.front();
		q2.pop();
		if(t1>t2)
		{
			q1.push(t2);
			q1.push(t1);
		}
		else
		{
			q2.push(t1);
			q2.push(t2);
		}
	}
	cout<<cnt<<" ";
	if(q1.empty())
		cout<<2;
	else cout<<1;
	return 0;
}
```

---

完美撒花~

---

## 作者：Sea_Level (赞：4)

思路：用两个队列模拟。如果某个队列为空就输出并结束程序。在设置一个数pd，用来判断是否需要输出-1。题目里给出n的数据范围$2<=n<=10$，所以把pd设置为10000，如果i>pd就结束程序。

下面上代码：

```cpp
#include<iostream>
#include<queue>//队列头文件
using namespace std;
int n,a,b,k1=0,k2=0,pd=10000,j=1;//n和k1，k2不用说了，就是题目里的。a和b分别是第一个选手的牌和第二个选手的牌，后面要加进队列，所以不需要数组。pd就是思路中所说，j是现在出了几轮牌（后面要用到while循环，所以在这里定义，我一般喜欢全局变量）。
queue<int> q1,q2;//第一个选手的牌和第二个选手的牌，使用队列存储。
int main(){
	cin>>n;
	cin>>k1;//输入第一个选手有几张牌
	for(int i=1;i<=k1;i++){
		cin>>a;//输入每一张牌
		q1.push(a);//入队
	}
	cin>>k2;//输入第二个选手有几张牌
	for(int i=1;i<=k2;i++){
		cin>>b;//输入每一张牌
		q2.push(b);//入队
	}
	while(1){//while循环，可以先把它设为死循环。
		if(j>pd){//如果循环了10000次以上
			cout<<-1<<endl;//直接输出-1
			return 0;//结束程序
		}
		if(!q1.size()){//如果第一个选手没有牌了
			cout<<j-1<<" "<<2<<endl;//输出次数和谁赢，第一个选手没有牌了肯定是第二个选手赢，这里j要-1是因为开始循环时第一次循环结束时j就是2，但出牌次数是1，所以要-1。
			return 0;
		}
		if(!q2.size()){//如果第二个选手没有牌了
			cout<<j-1<<" "<<1<<endl;//输出次数和谁赢，第二个选手没有牌了肯定是第一个选手赢
			return 0;
		}
		int ak=0;//如果上面的都不符合，就开始出牌。
		int bk=0;//ak是第一个选手出的牌，bk第二个选手出的牌。
		ak=q1.front();//出牌
		q1.pop();//出队，因为这张牌已经出过了
		bk=q2.front();//同上
		q2.pop();
		if(ak>bk){//如果第一个选手的牌大
			q1.push(bk);//先把小的入队
			q1.push(ak);//再把大的入队
		}else{//如果第二个选手的牌大
			q2.push(ak);//先把小的入队
			q2.push(bk);//再把大的入队
		}
		j++;//次数+1
	}
	return 0;//拜拜！
}
```


---

## 作者：我梦见一片焦土 (赞：2)

~~一题队列题解，写了一小时~~

------------
# [题目传送门](https://www.luogu.com.cn/problem/CF546C)

------------
# 思路：
这个题看起来很难，其实是一个模拟题。

大体思路就是模拟每个人拿出手牌，并且比较，然后放入相应的人的手牌中的过程。

然后让我们想一下，如何才能便捷的完成上面的过程呢？

可以用数组模拟对吧，但是，我们可以用便捷的 STL 的 ```queue``` 来实现。

拿出的手牌可以直接用一个变量来取出队列的 $f$，然后比较两个 $f$。

因为需要把自己的手牌放在对方的手牌之上，所以应该先 ```push``` 对方的手牌，再 ```push``` 自己的手牌。

因为如果一直不能结束就输出 $-1$，而且没有明确的边界，所以我们可以直接玄学把 $10^4$ 当做边界。

最后如果有一个人的手牌没有了，直接输出当前的步数和另一个人的编号即可。

------------
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
queue<int> q[3];
int n;
signed main(){
	cin>>n;;
	for(int i=1,x;i<=2;i++){
		cin>>x;
		for(int j=1,y;j<=x;j++){
			cin>>y;
			q[i].push(y);
		}
	}
	for(int i=1;i<1000000;i++){
		if(q[1].empty()){
			cout<<i-1<<" "<<2;
			return 0;
		}
		if(q[2].empty()){
			cout<<i-1<<" "<<1;
			return 0;
		}
		if(q[1].front()>q[2].front()){
			int t=q[1].front();
			q[1].pop();
			q[1].push(q[2].front());
			q[2].pop();
			q[1].push(t);
		}else{
			int t=q[2].front();
			q[2].pop();
			q[2].push(q[1].front());
			q[1].pop();
			q[2].push(t);
		}
	}
	cout<<-1;
	return 0;
}
```

---

## 作者：_Winham_ (赞：2)

思路：
首先用两个队列来进行存两个人的牌的顺序。
接下来直接纯模拟，先用两个变量分别存两个队列的开头牌的大小。
接下来进行一下两种操作（用变量 $a$ 与 $b$ 来代表两个队列的最上面牌的大小）

- 如果 $a > b$，那么就先把 $b$ 这张牌存入第一个人牌的底部，在以此类推存入 $a$ 这张牌。

- 如果 $b > a$，跟方法一一样先存入 $a$ 牌，再存入 $b$ 这张牌。

---
上代码
```cpp
#include<iostream>
#include<string>
#include<cctype>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<algorithm>
#include<map>
#include<set>
#include<iomanip>
#include<queue>
using namespace std;
#define LL long long
const int N = 1e6+10;
const int INF = 0x3f3f3f3f;
queue<int>q1,q2;
int n,x1,x2; 
int main(){
	//freopen("","r",stdin);
	//freopen("","w",stdout);
	cin>>n;
	cin>>x1;
	for(int i=1;i<=x1;i++){
		int x;
		cin>>x;
		q1.push(x);
	}
	cin>>x2;
	for(int i=1;i<=x2;i++){
		int x;
		cin>>x;
		q2.push(x);
	}
	int cnt=0;
	while(!q1.empty()&&!q2.empty()){
		if(cnt>1000000){
			cout<<-1<<endl;
			return 0;
		}
		int a=q1.front();int b=q2.front();
		if(a>b){
			q1.push(b);
			q1.push(a);
			cnt++;
		}else if(b>a){
			q2.push(a);
			q2.push(b);
			cnt++;
		}
		q1.pop(),q2.pop();
	}
	cout<<cnt<<" "<<((q1.empty()==true)?2:1)<<endl;
	return 0;
}


```

---

## 作者：莊·3001 (赞：2)

根据题意，用两个队列模拟。

数据范围是$N=10,$所以我们可以设$INF=1000000$,当出牌进行了$INF$次后，如果仍未退出，就可以判定此时无解，输出$-1.$

算法空间复杂度$:O(k1+k2)=O(n),$轻松跑过本题。

贴代码：
```cpp
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
const int INF=1000000;
queue<int>p,q;
int n,k1,k2,x;

int main()
{
	scanf("%d%d",&n,&k1);
	for(int i=1;i<=k1;i++)
	{
		scanf("%d",&x);
		p.push(x);
	}
	scanf("%d",&k2);
	for(int i=1;i<=k2;i++)
	{
		scanf("%d",&x);
		q.push(x);
	}
	for(int i=1;;i++)
	{
		if(i>INF)
		{
			puts("-1");
			return 0;
		}
		if(p.empty())
		{
			printf("%d 2\n",i-1);
			return 0;
		}
		if(q.empty())
		{
			printf("%d 1\n",i-1);
			return 0;
		}
		if(p.front()>q.front())
		{
			p.push(q.front());
			q.pop();
			p.push(p.front());
			p.pop();
		}
		else
		{
			q.push(p.front());
			p.pop();
			q.push(q.front());
			q.pop();
		}
	}
	return 0;
}
```


---

## 作者：Underage_potato (赞：1)

[**传送门**](https://www.luogu.com.cn/problem/CF546C)

这道题可以使用队列来做。

## 思路

我们通过读题可以看出，这道题就是让我们模拟这个放置和替换手牌的过程。注意：手牌是在**前面的先比较**，放入则是**从后放入**。

得到了这点，就很容易想到是使用 STL 里的 `queue` 队列了！

在比较时我们可以将两边队首相比较，若拿出，则用一个变量来存失败一方的队首即可。但是在 `push` 时要先 `push` 对方的，在 `push` 自己的。

如果其中一方的手牌没有了，那么就输出对方的编号以及局数。但是如果无法结束比赛就是输出 $-1$。但是这个结束的条件比较玄学，因为有可能两方的操作数有很多，所以这里直接选择两方牌数多的方的牌数 $+10000$。

## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
queue <int> q1,q2;
int main(){
	int t,n1,n2;
	cin>>t;
	cin>>n1;
	for(int i=1;i<=n1;i++){
		int x;
		cin>>x;
		q1.push(x);
	}
	cin>>n2;
	for(int i=1;i<=n2;i++){
		int x;
		cin>>x;
		q2.push(x);
	}
	for(int i=1;i<=max(n1,n2)+10000;i++){
		if(q1.empty()){
			cout<<i-1<<" "<<2;
			return 0;
		}
		if(q2.empty()){
			cout<<i-1<<" "<<1;
			return 0;
		}
		if(q1.front()>q2.front()){
			int x=q1.front();
			q1.pop();
			q1.push(q2.front());
			q2.pop();
			q1.push(x); 
		}
		else{
			int x=q2.front();
			q2.pop();
			q2.push(q1.front());
			q1.pop();
			q2.push(x); 
		}
	}
	cout<<-1;
	return 0;
}
/* by Underage_potato*/

```


---

## 作者：zhouzihang1 (赞：0)

## 大体思路

两个队列模拟

循环 $N$ 次后跳出，输出 -1。

## AC Code

```cpp
#include <bits/stdc++.h>
#include <queue>
using namespace std;
const int N=1e6;
queue<int> q1;
queue<int> q2;
int n,k1,k2,t,cnt=0;
int main()
{
	cin>>n>>k1;
	for(int i=0;i<k1;i++) cin>>t,q1.push(t);
	cin>>k2;
	for(int i=0;i<k2;i++) cin>>t,q2.push(t);
	while(cnt<N)
	{
		if(q1.empty())
		{
			cout<<cnt<<' '<<2;
			return 0;
		}
		if(q2.empty())
		{
			cout<<cnt<<' '<<1;
			return 0;
		}
		cnt++;
		int q1Front=q1.front(),q2Front=q2.front();
		q1.pop(); q2.pop();
		if(q1Front>q2Front) q1.push(q2Front),q1.push(q1Front);
		else if(q2Front>q1Front) q2.push(q1Front),q2.push(q2Front);
	}
	cout<<-1;
	return 0;
}
```



---

## 作者：晨·曦 (赞：0)

### 分析
输入第一行 $ n $ 为牌的总数 ($2 \le n \le 10$)；

输入第二行为第一个人的牌的数量及有什么牌；

输入第三行为第二个人的牌的数量及有什么牌；

$\because 2 \le n \le 10 $，根据题意，直接**模拟**即可。


### 思路
看楼下都是用**队列**做的，这里提供**数组**的写法。

首先需要两个数组 $ a[i] $ 和 $ b[i] $，分别用来存两个人的手牌。

然后一直循环，直到有一方手牌的数量为 $0$；
比较 $a_1$ 和 $b_1$，如果 $a_1$ 大，就先把 $b$ 数组的每一项都向前提一位（就是手牌给了对面，其他牌仍是原顺序）；
然后把 $a$ 数组的每一项都向前提一位，再把 $b_1$ 和 $a_1$ 依次放到最后（由题目的图可知，要把本次玩的牌放到最后，且先放别人的，再放自己的。这里先放 $b_1$ 后放 $a_1$）。

如果 $b_1$ 较大，则反之。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000],b[1000];
long long c; //c用来存玩了几轮牌
int main(){
	int z;//牌的总数（好像没什么用）
	cin>>z; 
	int n,m; //n是第一个人的牌，m是第二个
	cin>>n; 
	for(int i=1;i<=n;i++) cin>>a[i];
	cin>>m;
	for(int i=1;i<=m;i++) cin>>b[i]; 
	while(c<114514){ //如果打了太多轮，就是平局，退出循环。
		if(m==0) {
			cout<<c<<" "<<1;
			return 0;
		}
		if(n==0) {
			cout<<c<<" "<<2;
			return 0;
		}
		c++;
		int p=a[1],q=b[1]; //用p，q来代指 a[1]，b[1]
		if(p>q) {
			for(int i=2;i<=m;i++) b[i-1]=b[i];
			m--;
			for(int i=2;i<=n;i++) a[i-1]=a[i];
			a[n]=q;a[n+1]=p;
			n++;
		} else {
			for(int i=2;i<=n;i++) a[i-1]=a[i];
			n--;
			for(int i=2;i<=m;i++) b[i-1]=b[i];
			b[m]=p;b[m+1]=q;
			m++;
		}
	}
	cout<<-1;
	return 0;
} 
```


---

## 作者：naroanah (赞：0)

注意到 $1 \le n \le 10$ 的数据范围，直接模拟即可。

我们用两个队列 $a,b$ 模拟两个人手上的牌，对于正常输赢，直接对游戏进行模拟，发现哪个队列为空就说明它失败了；如果出现游戏无限循环的情况，我们可以记录游戏次数，由于 $n$ 的范围很小，所以次数大于 $1000$ 时，就说明游戏无法结束，直接输出 $-1$。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define INF 0x7fffffff
#define rep(i,a,b) for(int i = (a); i <= (b); i++)
#define qwq printf("qwq\n");
using namespace std;

int read(){
    int x=0,f=1;char ch;
    ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-') f=-f;ch=getchar();}
    while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
int n;
int k1,k2;
deque<int> a,b;
int main() {
	n=read();
	k1=read();
	rep(i,1,k1) a.push_back(read());
	k2=read();
	rep(i,1,k2) b.push_back(read());
	int times=0;
	while(!a.empty()&&!b.empty()&&times<=1000){
		if(a.front()>b.front()){
			a.push_back(b.front());
			a.push_back(a.front());
			a.pop_front();
			b.pop_front();
		}
		else{
			b.push_back(a.front());
			b.push_back(b.front());
			a.pop_front();
			b.pop_front();
		}
		times++;
	}
	if(a.empty()){
		printf("%d 2\n",times);
		return 0;
	}
	if(b.empty()){
		printf("%d 1\n",times);
		return 0;
	}
	printf("-1\n");
	return 0;
} 


```


---

## 作者：Nozebry (赞：0)

## $Problems$
两个人玩纸牌游戏，每一轮游戏每个人都把自己的第一个牌拿出来比较大小，大的一方先将对面的这个牌放在自己牌的最后，再把自己的牌放在最后，直到一个人没有了纸牌就算那个人输，问一共会进行多少次游戏，以及赢的人的编号。如果一直无法结束，则输出 $-1$。
## $Answer$
这道题其实就是**队列**的运用。。。

首先定义两个队列 $a$ 与 $b$ ，分别取出两个队列的队首，进行比较，如果 $a$ 的队首大于 $b$ 的队首，把 $b$ 的队首放在在 $a$ 队尾，然后再把 $a$ 的队首放在 $a$ 的队尾。如果 $b$ 的队首大于 $a$ 的队首，把 $a$ 的队首放在 $b$ 的队尾，然后把 $b$ 的队首放在 $b$ 的队尾。

如此循环，直至队列 $a$ 或 $b$ 中的数的个数为 $0$。
## $Code$
```pascal
var
    n,ans,la,lb,ia,ib,i:longint;
    a,b:array[0..10000010]of longint;
begin
    readln(n);
	read(la);
	for i:=1 to la do read(a[i]);
	read(lb);
    for i:=1 to lb do read(b[i]);
    ia:=1;ib:=1;
    while (ia<=la)and(ib<=lb)and(la<(1<<20)) do
    begin
        inc(ans);
        if a[ia]>b[ib] then
        begin
            inc(la);a[la]:=b[ib];
            inc(la);a[la]:=a[ia];
        end
        else
        begin
            inc(lb);b[lb]:=a[ia];
            inc(lb);b[lb]:=b[ib];
        end;
        inc(ia);inc(ib);
    end;
    if (la>=(1<<20)) then writeln(-1)
    else
    begin
        write(ans,' ');
        if (ia>la) then write(2)
            else write(1);
    end;
end.
```

---

