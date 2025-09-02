# Combination

## 题目描述

Ilya plays a card game by the following rules.

A player has several cards. Each card contains two non-negative integers inscribed, one at the top of the card and one at the bottom. At the beginning of the round the player chooses one of his cards to play it. If the top of the card contains number $ a_{i} $ , and the bottom contains number $ b_{i} $ , then when the player is playing the card, he gets $ a_{i} $ points and also gets the opportunity to play additional $ b_{i} $ cards. After the playing the card is discarded.

More formally: let's say that there is a counter of the cards that can be played. At the beginning of the round the counter equals one. When a card is played, the counter decreases by one for the played card and increases by the number $ b_{i} $ , which is written at the bottom of the card. Then the played card is discarded. If after that the counter is not equal to zero, the player gets the opportunity to play another card from the remaining cards. The round ends when the counter reaches zero or the player runs out of cards.

Of course, Ilya wants to get as many points as possible. Can you determine the maximum number of points he can score provided that you know his cards?

## 说明/提示

In the first sample none of two cards brings extra moves, so you should play the one that will bring more points.

In the second sample you should first play the third card that doesn't bring any points but lets you play both remaining cards.

## 样例 #1

### 输入

```
2
1 0
2 0
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
1 0
2 0
0 2
```

### 输出

```
3
```

# 题解

## 作者：翟翟 (赞：6)

这是一道练手 贪心/排序 的好题

没想到这么水的题目居然才 $3$ 篇题解，那我就发一波 C风格 的代码。

首先，自然不能给你们代码，我们先来看思路及解法：若出一张牌，得到的可以玩的牌的数量多，那就要先选 。 即我们要根据牌的出它的得到的可以玩的牌的数量（题目中给出的 $b$ ）用  `stdlib.h` 库中的 `qsort` 进行排序。

这就有一个问题了：若一张牌的 $a$ 很大，$b$ 为零，那怎么办？所以我们要在 $b$ 相等时按 $a$ 排序，因为 $b \ge 0$ ，所以若这张 $a$ 很大的牌其他 $a$ 比它小（假设所有牌中它的 $a$ 最大）的牌 $b = 0$  ，这张 $a$ 很大的牌会排在第一个。若其他牌 $b$ $ ! = $ $0$ ， 则它们排在这张 $a$ 很大的牌之前，这时因为前面的 $b$ 都大于零，则一定可以选到这张 $a$ 很大的牌。


<!-- readmore -->

**以下为代码（Code）：**

```c
#include<stdio.h>
#include<stdlib.h>
const int N=1e3;
int n,ans,pai=1;
struct node{int a,b;}f[N];
int cmp(const void*x,const void*y){
	node f1=*(node*)x,f2=*(node*)y;
	return f1.b^f2.b?f1.b<f2.b:f1.a<f2.a;
}
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;++i)
		scanf("%d%d",&f[i].a,&f[i].b);
	qsort(f,n,sizeof(node),cmp);
	for(int i=0;i<n;++i){
		if(pai<=0)break;
		--pai;
		ans+=f[i].a;
		pai+=f[i].b;
	}
	printf("%d\n",ans);
	return 0;
}
```


**格式化代码+注释：**

```c
#include <stdio.h>
#include <stdlib.h>
const int N = 1e3;
int n, ans, pai = 1; //按照题意，牌数初始为1
struct node {
    int a, b; //获得 a 分，可以玩的牌的数量 +b
} f[N];
int cmp(const void *x, const void *y) { //排序函数
    node f1 = *(node *)x, f2 = *(node *)y;
    return f1.b ^ f2.b ? f1.b < f2.b : f1.a < f2.a; //当两个b相等时，若第一个a大返回较小值（即为按a排序）；当两个b不等时，若第一个b大返回较小值（即为按b排序）。
}
int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d%d", &f[i].a, &f[i].b);
    qsort(f, n, sizeof(node), cmp); //对f数组进行排序
    for (int i = 0; i < n; ++i) {
        if (pai <= 0) //若没牌了
            break;
        --pai;
        ans += f[i].a; //答案增加
        pai += f[i].b; //牌数增加
    }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：开始新的记忆 (赞：6)

题目大意：现在有n张卡片，每张卡片上有两个数字，代表这张卡片的值和还能多抽几张牌，现在你有透视眼，可以知道每张牌上面的两个数字，请你把这堆牌重新排序，使得你能获得的值之和最大（初始抽一张）。

大致思路：不难发现，在能多抽几张牌的这里如果大于等于一那么拿这张牌就绝对不亏，于是我们可以先按多抽牌的数量进行排序，如果相等则按值的大小排序（都是大的在前）。
```
#include<bits/stdc++.h>
using namespace std;
int n,ans=0,numm=1,cnt=1;
struct node{
	int point,num;
} a[1010];

bool cmp(node x,node y)
{
	if(x.num==y.num)
		return x.point>y.point;
	return x.num>y.num;
}

int main()
{	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>a[i].point>>a[i].num;
	sort(a+1,a+n+1,cmp);
	while(numm && cnt<=n)
	{
		--numm;
		ans+=a[cnt].point;
		numm+=a[cnt].num;
		++cnt;
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：cqbztz2 (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF155B)

[不会更好的阅读体验](https://www.luogu.com.cn/blog/493271/solution-cf155b)

# Thinking

观察数据范围 $ 1 \leq n \leq 10^3 $ ，考虑贪心。

如果选择了一个纸牌后，可以获得的选择次数大于等于 $ 1 $ ，那么这次选择一定是划算的。那么越划算的纸牌就可以先选择。所以考虑排序。当两张纸牌的 $ b $ 相同时，判断两张纸牌可以获得的分数大小即可。获得分数越多的纸牌肯定先选。

# Coding

```cpp
  #include<bits/stdc++.h>
  using namespace std;
  const int N=1005;
  int n,now=1,ans;
  struct node{
      int x,y;
      friend bool operator<(node x,node y){
          if(x.y==y.y){
              return x.x>y.x;
          }
          return x.y>y.y;
      }
  }a[N];
  signed main(){
      scanf("%d",&n);
      for(int i=1;i<=n;i++){
          scanf("%d %d",&a[i].x,&a[i].y);
      }
      sort(a+1,a+n+1);
      for(int i=1;i<=n;i++){
          if(now<=0){
              printf("%d",ans);
              return 0;
          }
          now--;
          ans+=a[i].x;
          now+=a[i].y;
      }
      printf("%d",ans);
      return 0;
  }
```


---

## 作者：yydfj (赞：1)

**这是本蒟蒻第二十八次写的题解，如有错误点请好心指出！**

## 问题转述

有 $n$ 张纸牌，每一张纸牌包括两个值 $a$ 和 $b$，表示使用该纸牌会获得 $a$ 分并将当前能使用纸牌的次数加上 $b$。现在你只有一次使用纸牌的机会，使用过的纸牌不能被再次使用，问最多能获得多少分？

## 解法综述

根据题意，很容易就想到贪心，因为如果我们有使用纸牌的机会，就要么选择当前可使用纸牌中 $a$ 最大的纸牌，要么选择当前可使用纸牌中 $b$ 最大的纸牌，仔细观察发现如果能获得更多的使用纸牌的机会，就更能因为使用的纸牌多而获得的分数多。

考虑用优先队列代替排序，将纸牌中的值 $b$ 从大到小排序，如果有 $b$ 相同的纸牌，则优先考虑其中 $a$ 更大的纸牌。每次使用当前考虑最优的纸牌，获得其分数和使用纸牌的次数，当没有可使用的纸牌或没有使用纸牌的机会时，就输出答案，即最多能获得的分数。

## 代码描述
```cpp
#include<queue>
#include<cstdio>
using namespace std;
inline int read()//快读
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
struct node{
	int a,b;
	bool operator<(const node &x)const{
		if(x.b==b) return x.a>a;//如果有b相同的纸牌，则优先考虑其中a更大的纸牌
		return x.b>b;//将纸牌中的值b从大到小排序
	}
};
priority_queue<node> q;//优先队列
int n,d=1,s;//d为当前能使用纸牌的次数
int main()
{
	n=read();
	for(int i=1;i<=n;i++) q.push((node){read(),read()});//读入每一张纸牌的两个值a和b
	while(!q.empty()&&d)//要保证当前还有可使用的纸牌且有使用纸牌的机会
	{
		node x=q.top();//每次使用当前考虑最优的纸牌
		q.pop();//使用过的纸牌不能被再次使用
		d=d+x.b-1;//获得使用纸牌的次数并消耗一次使用纸牌的机会
		s+=x.a;//获得其分数
	}
	printf("%d",s);//输出答案，即最多能获得的分数
	return 0;
}
```

---

## 作者：_Wind_Leaves_ShaDow_ (赞：0)


蒟蒻第一次写题解，管理员大大求过！

### 分析：
这道题应该用**贪心**的思路来解。

要使得得到的分越多，就要**在有限的牌内把牌值越大的拿走**（这么解释应该懂吧）。

如果一张牌能增加牌量的话，就等于能白嫖一张牌，所以要**确保把所有能增加牌量的牌拿到手**。

牌用结构体储存并排序：$score$ 表示牌能给你带来的分值；$more$ 表示牌能增加多少。

- 排序时先判断两张牌谁能带来更多牌（也就是 $more$ 更大）,$more$ 更大的排在前面。
- 如果 $more$ 相等，牌值更大的排在前面

排完序之后扫一遍数组输出总共获得的牌值 $sum$ 就好了。

#### AC代码如下：
```
#include <bits/stdc++.h>
using namespace std;
int n,x=1,sum=0;//x表示当前还能取多少牌，sum为现在取得的牌值总和 
struct card{
	int score,more;//score记录牌值，more记录带来的牌量 
}a[1030];
bool cmp(card x,card y){
	if(x.more==y.more)return x.score>y.score;//先比较能带来牌的数量的大小 
	else return x.more>y.more;//能带来牌的数量相等再比较牌值大小 
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].score>>a[i].more;
	}
	sort(a+1,a+n+1,cmp);//排序 
	for(int i=1;i<=n;i++){//遍历牌堆，排序过后是直接从顶端取，一定是最优解 
		if(x<=0)break;//不能再取牌了，直接跳出循环 
		x--;//取一张牌 
		sum+=a[i].score;//加上牌值 
		x+=a[i].more;//增加牌量 
	}
	cout<<sum;//输出 
	return 0; 
}

```


---

## 作者：Erotate (赞：0)

可以发现,如果两张牌可以获得的分数分别为 $a_1,a_2$，能获得的出牌次数为 $b_2,b_1(b_1=0)$，如果 $b_1>b_2$，那么我们肯定先出第 $2$ 张牌。因为如果 $b_2>b_1$ 的话 $b_2$ 肯定大于 $0$，也就是我们可以把两张牌都出了，获得的分数就为 $a_1+a_2$；但如果我们出第 $1$ 张牌，那就只能获得 $a_1$ 的分数，显然比 $a_1+a_2$ 要小。

也就是说，我们需要尽量先打出能获得最多出牌机会的牌，即 $b$ 最大的牌，因为只要我们保证出牌次数不为零，就有机会出那些 $a$ 比较大的牌，这样一定是最优的。

那么做法就是我们对牌堆进行排序，能带来出牌次数越多的牌排在越前面，如果能带来的出牌次数一样的话，就按获得的分数进行从大到小排序。最后在排完序的牌堆中模拟一下出牌过程即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct card{//p 记录分数，o 记录能获得的出牌次数
	int p,o;
}a[1005];
int n,ans,c1=1,c2;//c1 位当前能出牌的次数，c2 表示手上剩的牌的数量
bool cmp(card x,card y){
	if(x.o==y.o) return x.p>y.p;
	return x.o>y.o;
}
signed main(){
	scanf("%d",&n);
	c2=n;
	for(int i=1;i<=n;++i) scanf("%d%d",&a[i].p,&a[i].o);
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;++i){
		ans+=a[i].p;
		c2--;//每出一张牌，出牌机会减一；剩余牌数减一。
		c1--;
		c1+=a[i].o;//出牌机会加上排上对应的 o。
		if(!c1 || !c2) break;//如果剩余牌数或出牌机会等于零，就退出循环
	}
	printf("%d",ans);
	return 0;
}
```


---

