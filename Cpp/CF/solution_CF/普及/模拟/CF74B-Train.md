# Train

## 题目描述

A stowaway and a controller play the following game.

The train is represented by $ n $ wagons which are numbered with positive integers from $ 1 $ to $ n $ from the head to the tail. The stowaway and the controller are initially in some two different wagons. Every minute the train can be in one of two conditions — moving or idle. Every minute the players move.

The controller's move is as follows. The controller has the movement direction — to the train's head or to its tail. During a move the controller moves to the neighbouring wagon correspondingly to its movement direction. If at the end of his move the controller enters the $ 1 $ -st or the $ n $ -th wagon, that he changes the direction of his movement into the other one. In other words, the controller cyclically goes from the train's head to its tail and back again during all the time of a game, shifting during each move by one wagon. Note, that the controller always have exactly one possible move.

The stowaway's move depends from the state of the train. If the train is moving, then the stowaway can shift to one of neighbouring wagons or he can stay where he is without moving. If the train is at a station and is idle, then the stowaway leaves the train (i.e. he is now not present in any train wagon) and then, if it is not the terminal train station, he enters the train again into any of $ n $ wagons (not necessarily into the one he's just left and not necessarily into the neighbouring one). If the train is idle for several minutes then each such minute the stowaway leaves the train and enters it back.

Let's determine the order of the players' moves. If at the given minute the train is moving, then first the stowaway moves and then the controller does. If at this minute the train is idle, then first the stowaway leaves the train, then the controller moves and then the stowaway enters the train.

If at some point in time the stowaway and the controller happen to be in one wagon, then the controller wins: he makes the stowaway pay fine. If after a while the stowaway reaches the terminal train station, then the stowaway wins: he simply leaves the station during his move and never returns there again.

At any moment of time the players know each other's positions. The players play in the optimal way. Specifically, if the controller wins, then the stowaway plays so as to lose as late as possible. As all the possible moves for the controller are determined uniquely, then he is considered to play optimally always. Determine the winner.

## 样例 #1

### 输入

```
5 3 2
to head
0001001
```

### 输出

```
Stowaway```

## 样例 #2

### 输入

```
3 2 1
to tail
0001
```

### 输出

```
Controller 2```

# 题解

## 作者：ACtheQ (赞：4)

这么古老的题目没有题解，我来交一发。

一道模拟加思维题。

先想偷渡者在什么地方最有优势，假如抓捕者向一号车厢走，偷渡者在车尾最优。

先想偷渡者在什么地方最有优势，假如抓捕者向车尾走，偷渡者在一号车厢最优。

假如停车也是一样的办法。

需要注意的一点就是若追捕者在一号车厢转向准备走到车尾，并不是在一号车厢最优，而是在车尾最优。

反方向同理。

```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	int l,r;
	cin>>n>>l>>r;
	string s;
	getline(cin,s);
    getline(cin,s);
	int flag;
	if(s=="to head") flag=-1;
	else flag=1; 
	cin>>s;
	int ans=0;
	for(int i=0;i<s.size();i++)
	{
		ans++;
		if(r==1) flag=1;
		if(r==n) flag=-1;
		if(s[i]=='1') l=r;
		r+=flag;
		if(l==r) l+=flag;
		if(l==0||l==n+1)
		{
			cout<<"Controller"<<" "<<ans<<endl;
			return 0;
		}
	}
	cout<<"Stowaway";
	return 0;
} 

```

---

## 作者：如履薄冰 (赞：3)

# 算法
模拟
# 解法
我们用一个变量维护管理员走的方向，再对货车的运行状态进行遍历。每次遍历，我们先看一看管理员现在在不在列车的尽头，如果在，改变管理员走的方向。之后，我们就可以看一看列车现在的状态。如果列车停着，我们就可以随便改变偷渡者的位置。如果管理员现在朝车头走，将偷渡者传送到车位，反之传送到车头。如果列车在移动，我们就正常模拟偷渡者的行动。如果偷渡者和管理员在同一个位置，偷渡者就逃到与其相邻的车厢。最后，我们再判断一下偷渡者的位置是否合法，如果不合法，那么偷渡者就无路可逃了。这代表管理员抓到了偷渡者，输出管理员赢的答案。如果遍历完所有列车状态，偷渡者还没被抓，输出偷渡者赢的答案。
# 代码
我认为我已经讲的够详细了，此处省略。

---

## 作者：wangzhihong10002 (赞：2)

[传送门。](https://www.luogu.com.cn/problem/CF74B)

# 题目分析：

一道很简单的题，分类讨论即可：

- 当管理员往车头走时，偷渡者往车尾走是最好选择，但如果偷渡者比管理员更靠近车尾时偷渡者应往车头走。
- 当管理员往车尾走时，偷渡者往车头走是最好选择，但如果偷渡者比管理员更靠近车头时偷渡者应往车尾走。
- 以上为火车运行时的判断，如果火车停止也一样。

# 代码实现：

分析完了，来实现代码吧。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,h,sum;
string s,s1;
int main(){
	cin>>n>>m>>k;
	cin>>s1>>s1;
	cin>>s;
	if(s1=="head")h=-1;//管理员的方向。
	else h=1;
	for(int i=0;i<s.size();i++){
		sum++;
		if(k==1){
			if(h==-1)h=1;
			else k+=h;
		}
		else{
			if(h==1)h=-1;
			else k+=h;
		}
		if(s[i]=='0'){//当火车运行时。
			if(h==-1){//分类讨论。
				if(m>k&&m!=n)m++;
				else if(m!=1)m--;
			}
			else{
				if(m<k&&m!=1)m--;
				else if(m!=n)m++;
			}
		}
		else{//当火车停止时。
			if(h==-1){
				if(k!=n)m=n;
				else m=1;
			}
			else{
				if(k!=1)m=1;
				else m=n;
			}	
		}
		if(m==k){//管理员赢。
			cout<<"Controller "<<sum;
			return 0;
		}
	}
	cout<<"Stowaway";//偷渡者赢。
	return 0;//华丽的结束。
} 
```

---

## 作者：syf159 (赞：1)

[洛谷题目](https://www.luogu.com.cn/problem/CF74B)  
[ codeforces 题目](https://codeforces.com/problemset/problem/43/D)

# 题目大意

偷渡者和管理员在一列火车上进行游戏。如果管理员和偷渡者可以在同一时刻在同一节车厢上（即为管理员抓到偷渡者），则管理员胜利，并输出管理员抓到偷渡者的时间；如果火车到终点站时管理员依旧未胜利，则为偷渡者胜利。

管理员运动方式：每次向他的前进方向移动一节车厢

偷渡者运动方式：火车运行时，它可以移动一些车厢或不移动；火车靠站时，它可以移动至任意一节车厢

# 分析

对于本题，时间字符串的长度比较小，仅为 $ 1\sim200 $ ，可以考虑模拟。

顺次枚举每一个时间节点，先模拟管理员的方向及其位置，再根据管理员的位置模拟偷渡者的位置。

1. 为了简化，当火车运行时，我们分两种情况讨论：

- 当管理员离偷渡者有一定的距离，此是，我们可以让偷渡者不移动；
- 当管理员离偷渡者只有一节车厢时，我们的偷渡者就不可以坐以待毙，必须向管理员移动的方向移动一节车厢。

因为是管理员追着偷渡者赶，所以当偷渡者的位置在边界外时，即可判定为管理员胜利。

2. 当火车靠站时，最优方案为将偷渡者放在管理员上次移动的位置

## [ACcode](https://www.luogu.com.cn/paste/sbaftksr)(其他内容详见代码)

---

## 作者：linan04195 (赞：1)

## 思路
输入时会给定管理员一开始的方向，向车头或车尾。偷渡者的目的是不被管理员抓住。

我们把偷渡者的位置设为 $a$，管理员的位置设为 $b$：

**开动**的时候：

- 当 $a<b$，偷渡者应往车头走。
- 当 $a>b$，偷渡者应往车尾走。
- 当 $a=b$，偷渡者被抓，结束。
  
**停车**的时候：

- 若管理员在车头，则偷渡者要去车尾。
- 若管理员在车尾，则偷渡者要去车头。

枚举列车每分钟的状态，用 $ans$ 记录偷渡者所在的位置，判断输出 $ans$ 即可。

## Code
``` cpp

#include<bits/stdc++.h>
using namespace std;

int n,tmp,t,pos,ans;
//ans表时间，pos表方向
string str;

int main(){
	cin>>n>>tmp>>t;
	cin>>str>>str;
	
	if(str=="head") pos=-1;//往车头走，每次减一
	else pos=1;//往车尾走，每次加一
	
	cin>>str;//列车状态
	 
	int len=str.size();
	for(int i=0;i<len;i++){//枚举
		if(tmp==t){//两人在同一车厢，管理员胜
			printf("Controller %d",ans);
			return 0;
		}
		
		ans++;//步数加一
		
		if(str[i]=='1'){//停止
			if(pos!=-1) tmp=1;
			else tmp=n;
		}
		
		else{//运行
		
			if(tmp<t) tmp=max(1,tmp-1);//偷渡者的位置 < 管理员的位置，向车头走
			if(tmp>t) tmp=min(n,tmp+1);//偷渡者的位置 > 管理员的位置，向车尾走 
			
		}
		
		t+=pos;//管理员走
		
		if(t==1) pos=1;//到车头，向车尾走
		if(t==n) pos=-1;//到车尾，向车头走
	}
	
	if(tmp==t) printf("Controller %d",ans);//管理员赢
	else printf("Stowaway");//偷渡者赢

}
```

---

## 作者：RaymondOccam (赞：0)

### 思路

模拟。

首先读入不用多说，可以去遍历火车的每个状态，并进行处理。

重点在于火车到终点站之前的过程中。

#### 火车运行状态

- 如果当前管理员向车头移动，那么偷渡者也需要向车头移动，总不能去给管理员送人头吧。
- 反向同理。

#### 火车停靠状态

为了躲避管理员，让偷渡者去车头或车尾即可，具体去哪个由管理员方向判断。

### 代码

[AC 记录](https://codeforces.com/problemset/submission/74/307548030)

```cpp
#include <iostream>
#include <string>
#define e return 0;
int n, m, k, cnt, i;
bool dir;
std::string str;
int main () {
  std::cin.tie ( 0 ) -> sync_with_stdio ( false );
  std::cin >> n >> m >> k;
  std::cin >> str >> str;
  if ( str == "head" ) dir = 0;
  else dir = 1;
  std::cin >> str;
  for ( i = 0; str[i]; i ++ ) {
    if ( m == k ) {
      std::cout << "Controller " << cnt << '\n';
      return 0;
    }
    cnt ++;
    if ( ! ( str[i] - '0' ) ) {
      if ( m < k ) m = std::max ( 1, m - 1 );
      if ( m > k ) m = std::min ( m + 1, n );
    } else m = ( dir ? 1 : n );
    k += ( dir ? 1 : -1 );
    if ( k == 1 || k == n ) dir ^= 1;
  }
  if ( m == k ) std::cout << "Controller " << cnt << '\n';
  else std::cout << "Stowaway\n";
  return 0;
}
```

---

## 作者：Chenxuhang_play (赞：0)

## 题目链接

<https://www.luogu.com.cn/problem/CF74B>

## 题目大意

题目已经很简略了，自己看题目去。

## 思路

**对于车在运行状态下：**

显而易见的，可以分成 $2$ 种情况讨论：

+ 管理员更靠车头

+ 管理员更靠车尾

其实不论管理员的方向如何，只要管理员更靠车头，我们的最佳策略就是去车尾；只要管理员更靠车尾，我们的最佳策略就是去车头。

另外一点，**对于停靠状态下的策略：**

处于停靠状态下，只要管理员向车头，我们就直接传送去车尾；管理员向车尾，我们就直接传送去车头。

**总结：** 这道题还是比较简单的。

## 代码~~我知道你们最想要的就是这个（~~
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,x,y;
	cin>>n>>x>>y;
	string s;
	cin>>s;//考虑到cin遇到空格就会结束，且这一行只有两种情况 to head 或 to tail，所以第一次读入的串s一定是to。所以只需要以第二个词做判断即可 
	cin>>s;//这次读入的词才是我们需要的 head 或 tail
	bool b;
	if(s=="head") b=true;
	else b=false; 
	cin>>s;
	for(int i=0;i<s.size();i++)
	{
		if(y==1) b=false;//到车头了 
		else if(y==n) b=true;//到车尾了 
		if(s[i]=='0')
		{
			if(x>y) //管理员比偷渡者更靠近车头
			{
				if(b) //管理员向车头时，偷渡者的最佳策略是向车尾 
				{
					y--;
					if(x!=n) x++;//特判偷渡者是否已经到车尾了 
				}
				else //管理员向车尾时，偷渡者也只能够向车尾 
				{
					if(x!=n) x++;
					y++;
				}
			}
			else if(x<y) //管理员比偷渡者更靠近车尾
			{
				if(b) //管理员向车头时，偷渡者的最佳策略是向车头
				{
					y--;
					if(x!=1) x--;
				}
				else //管理员向车尾时，偷渡者也要向车头 
				{
					if(x!=1) x--;
					y++;
				}
			}
			if(x==y)
			{
				cout<<"Controller "<<i+1;
				exit(0);
			}
		}
		else if(s[i]=='1')
		{
			if(b) //管理员向车头，偷渡者就去车尾
			{
				y--;
				x=n;
			}
			else //管理员向车尾，偷渡者就去车头
			{
				y++;
				x=1; 
			}
		}
		//cout<<i<<" "<<x<<" "<<y<<endl;
	}
	cout<<"Stowaway";
	exit(0);
}
```

~~**附：** 这次我手敲代码看谁还敢说我 ctj~~

---

## 作者：floodfill (赞：0)

## CF74B Train 题解
### 大致思路
审题。我们可以发现，管理员的走法固定，先朝给定的初始方向（朝车头，`to head` 或朝车尾，`to tail`），在车头或车尾时换向行走。那么我们来考虑偷渡者的最优策略。

若设当前管理员位置为 $p_c$，偷渡者位置为 $p_s$，那么分类讨论：

运行时：
- $p_c>p_s$，此时偷渡者应当向车头方向走。
- $p_c<p_s$，此时偷渡者应当向车尾方向走。
- $p_c=p_s$，被抓住了，管理员获胜。输出当前时间。

停车时：

显然偷渡者要尽可能地远离管理员，所以我们有：

- 若管理员往车头方向走，那么偷渡者前往车尾。
- 若管理员往车尾方向走，那么偷渡者前往车头。

这就分析完了。

---

## 作者：keep_shining (赞：0)

读完题后，由于管理员走法已经固定，所以直接考虑偷渡者什么时候是最优的：

设当前管理员的位置为 $idc$，偷渡者的位置为 $ids$。

如果在运行中：

* 若 $ids < idc$，则偷渡者一定向车头走。
* 若 $ids = idc$，则代表两人处于同一车厢，输出管理员获胜和当前时间，结束程序。
* 若 $ids > idc$，则偷渡者一定向车尾走。

否则停止：

* 若管理员在车头，偷渡者直接到车尾。
* 若管理员在车尾，偷渡者直接到车头。

分析完最优的方法后，我们来考虑代码实现：

先输入，然后对列车每分钟的状态枚举，再加上 if 判断，判断上述情况即可通过。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define fst ios::sync_with_stdio(false);cin.tie();cout.tie();
#define Endl endl
#define itn int
#define For(i,a,b) for(int i=a;i<=b;i++)
const int N=1e5+5;
const int P=1e9+7;
int n,m,k,x,cnt;//cnt表示当前所用时间，x表示当前前进的方向
string s;
int main()
{
	cin>>n>>m>>k;
	cin>>s>>s;//输入，由于两个串之间有空格，所以我输了两次
	if(s=="head")x=-1;//如果要往车头走，那就需要每次减一
	else x=1;//否则每次加一
	cin>>s;//输入列车状态
	for(int i=0;i<s.size();i++)//枚举
	{
		if(m==k)//如果两人在同一车厢内，那输出管理员胜和当前步数，结束
		{
			cout<<"Controller "<<cnt;
			return 0;
		}
		cnt++;//步数加一
		if(s[i]=='0')//如果是运行状态
		{
			if(m<k)m=max(1,m-1);//如果偷渡者的位置比管理员的位置小，那么向车头走一步，注意以为没有比一号编号更小的车厢，所以需要在一号和当前位置的前一个车厢中取最大值
			if(m>k)m=min(m+1,n);//否则在最后一节车厢和当前位置的后一节车厢中取最小值，原因和上面一样
		}
		else//否则是停止状态
		{
			if(x==-1)m=n;//如果管理员再往车头走，那么就让偷渡者到车尾
			else m=1;//否则到车头
		}
		k+=x;//管理员向当前方向走一步
		if(k==1)x=1;//如果到了车头，那么改变方向向车尾走
		if(k==n)x=-1;//到了车尾，改变方向向车头走
	}
	if(m==k)//最后相遇了也是管理员赢
	{
		cout<<"Controller "<<cnt;
		return 0; 
	}
	cout<<"Stowaway";//偷渡者赢了
    return 0;
}
```

---

## 作者：QWQ_123 (赞：0)

考虑贪心。

设当前偷渡者位置为 $i$，管理员位置为 $j$。

那么
若当前是运行中：
*	若 $i<j$，偷渡者一定往车头走。
*	若 $i>j$，偷渡者一定往车尾走。
*	若 $i=j$，则偷渡者被抓住，直接当前时间。

否则当前停止：
*	若管理员在往车头走，那么偷渡者直接到达车尾。
*	若管理员在往车尾走，那么偷渡者直接到达车头。

```cpp

#include <bits/stdc++.h>

using namespace std;

int n, m, k;
string s;
string s1;
int f = 0;

int main() {
	scanf("%d%d%d", &n, &m, &k);
	cin >> s >> s >> s1;

	if (s == "head") f = -1;
	else f = 1;
	int id = 0;

	for (auto t : s1) {
		// cout << k << ' ' << m << ' ' << n << endl;
		if (m == k) {
			printf("Controller %d\n", id);
			return 0;
		}
		++id;

		if (t == '0') {
			if (m < k) m = max(1, m - 1);
			if (m > k) m = min(n, m + 1);
		} else {
			if (f == -1) m = n;
			else m = 1;
		}
		k += f;

		if (k == 1) f = 1;
		else if (k == n) f = -1;
	}
	if (m == k) {
		puts("Controller");
		printf("%d\n", id);
		return 0;
	}
	puts("Stowaway");

	return 0;
}
```

---

