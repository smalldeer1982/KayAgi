# Weird Game

## 题目描述

Yaroslav, Andrey and Roman can play cubes for hours and hours. But the game is for three, so when Roman doesn't show up, Yaroslav and Andrey play another game.

Roman leaves a word for each of them. Each word consists of $ 2·n $ binary characters "0" or "1". After that the players start moving in turns. Yaroslav moves first. During a move, a player must choose an integer from 1 to $ 2·n $ , which hasn't been chosen by anybody up to that moment. Then the player takes a piece of paper and writes out the corresponding character from his string.

Let's represent Yaroslav's word as $ s=s_{1}s_{2}...\ s_{2n} $ . Similarly, let's represent Andrey's word as $ t=t_{1}t_{2}...\ t_{2n} $ . Then, if Yaroslav choose number $ k $ during his move, then he is going to write out character $ s_{k} $ on the piece of paper. Similarly, if Andrey choose number $ r $ during his move, then he is going to write out character $ t_{r} $ on the piece of paper.

The game finishes when no player can make a move. After the game is over, Yaroslav makes some integer from the characters written on his piece of paper (Yaroslav can arrange these characters as he wants). Andrey does the same. The resulting numbers can contain leading zeroes. The person with the largest number wins. If the numbers are equal, the game ends with a draw.

You are given two strings $ s $ and $ t $ . Determine the outcome of the game provided that Yaroslav and Andrey play optimally well.

## 样例 #1

### 输入

```
2
0111
0001
```

### 输出

```
First
```

## 样例 #2

### 输入

```
3
110110
001001
```

### 输出

```
First
```

## 样例 #3

### 输入

```
3
111000
000111
```

### 输出

```
Draw
```

## 样例 #4

### 输入

```
4
01010110
00101101
```

### 输出

```
First
```

## 样例 #5

### 输入

```
4
01100000
10010011
```

### 输出

```
Second
```

# 题解

## 作者：pipi (赞：7)

**这道题是一道“裸”的“贪心”**，所以其实很简单。  
为了自己拿到高分，并压制对手，自然是要取同时是 ‘1’ 的位置最好  
剩下的话要不然拿能使自己得分的或使对手得不到分的  
最后再选择都是‘0’的  
统计一下谁的‘1’多谁的数自然就大   
最开始统计一下各种的有多少个
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int main(){
	int n,aa=0,bb=0,cc=0,dd=0,ee=0,sc1=0,sc2=0;
	scanf("%d",&n);
	bool a[2 * n],b[2 * n],l=0,k;
	n *= 2;
	for(int i=0;i<n;i++){
		scanf("%1ol",&a[i]);
		if(a[i])aa++;
	}
	for(int i=0;i<n;i++){
		scanf("%1ol",&b[i]);
		if(b[i])bb++;
	}
	for(int i=0;i<n;i++){
		if(a[i] == 1&&b[i] == 1) dd++;
		if(a[i] == 1&&b[i] == 0) cc++;
		if(a[i] == 0&&b[i] == 1) ee++;
	}
	for(int i=0;i<n;i++){
		if(dd){
			sc1++;
			dd--;
		}
		else if(cc){
			sc1++;
			cc--;
		}
		else if(ee){
			ee--;
		}
		if(dd){
			sc2++;
			dd--;
		}
		else if(ee){
			sc2++;
			ee--;
		}
		else if(cc){
			cc--;
		}
	}
	if(sc2 > sc1) printf("Second");
	if(sc1 > sc2) printf("First");
	if(sc1 == sc2) printf("Draw");
} 
```

---

## 作者：pipi (赞：7)

这道题是一道“裸”的“贪心”，所以其实很简单。

为了自己拿到高分，并压制对手，自然是要取同时是 ‘1’ 的位置最好

剩下的话要不然拿能使自己得分的或使对手得不到分的

最后再选择都是‘0’的

统计一下谁的‘1’多谁的数自然就大

首先，我们看一下，如果有 ≥2 个的同时是一的位置，那么一人拿一个，效果是一样的

那么我们不妨将都是 ‘1’ 的数量 a1 变成 a1 %= 2； 这样是不影响结果的。

相似地，我们再处理剩下两种情况。

代码如下➷

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int main(){
    int n,aa=0,bb=0,cc=0,dd=0,ee=0,sc1=0,sc2=0,ab;
    scanf("%d",&n);
    bool a[2 * n],b[2 * n],l=0,k;
    n *= 2;
    for(int i=0;i<n;i++){
        scanf("%1ol",&a[i]);
        if(a[i])aa++;
    }
    for(int i=0;i<n;i++){
        scanf("%1ol",&b[i]);
        if(b[i])bb++;
    }
    for(int i=0;i<n;i++){
        if(a[i] == 1&&b[i] == 1) dd++;
        if(a[i] == 1&&b[i] == 0) cc++;
        if(a[i] == 0&&b[i] == 1) ee++;
    }
    dd %= 2;
    ab = min(cc,ee);
    cc -= ab;
    ee -= ab;
    sc1 += dd;
    if(dd){
    	sc2 += ee / 2 + ee % 2;
    	sc1 += cc / 2;
	}
	else{
		sc2 += ee / 2;
		sc1 += cc / 2 + cc % 2;
	}
    if(sc2 > sc1) printf("Second");
    if(sc1 > sc2) printf("First");
    if(sc1 == sc2) printf("Draw");
} 
```

---

## 作者：ModestCoder_ (赞：2)

这应该算是一个比较基础得博弈把

把1分成两类，

 - 某一个位置上只有一行拥有1
 - 某一个位置上两行都有1

这两类1应该是可以分开来讨论的，不相互影响，先统计一下两种1的个数

一开始可以令两个人都尽可能取两行都有的1

然后如果两行都有的1的个数是奇数的话先手改变


然后的阶段是两个人尽可能取自己这一行有的1

那么为了方便，如果先手在上一个阶段改变，我让第二个人先取一个1，把先手改回来

然后讨论两行的1个数大小关系就可以得到答案

记第一行有$s1$个1,第二行有$s2$个1

 - $s1>s2$，```puts("First")```
 - $s1=s2$，```puts("Draw"）```
 - $s1=s2+1$，```puts("Draw")```
 - $s1>s2+1$，```puts("Second")```
 
Code：

```cpp
#include <bits/stdc++.h>
#define maxn 2000010
using namespace std;
int n, a[maxn], b[maxn], s1, s2, s3;

int get(){
	char c = getchar();
	for (; c != '0' && c != '1'; c = getchar());
	return c == '1';
}

int main(){
	scanf("%d", &n);
	for (int i = 1; i <= (n << 1); ++i) a[i] = get();
	for (int i = 1; i <= (n << 1); ++i) b[i] = get();
	for (int i = 1; i <= (n << 1); ++i)
		if (a[i] && !b[i]) ++s1; else
		if (!a[i] && b[i]) ++s2; else 
		if (a[i] && b[i]) ++s3;
	if (s3 & 1) --s2;
	if (s1 > s2) puts("First"); else
	if (s2 > s1 + 1) puts("Second"); else puts("Draw");
	return 0;
}
```


---

## 作者：tanghairong (赞：1)

显然取到更多 ```1``` 的一定更大。

考虑在什么情况下能判定谁的 ```1``` 更多。

设第一行的第 $i$ 个数为 $a_i$ ，第二行的为 $b_i$ ，小A拿到的 ```1``` 的个数为 $sum1$ ，小B的为 $sum2$ 。

## Step 1 第一轮取

优先考虑 $a_i=b_i=1$ 的，统计个数 $num$ ，若为偶数，可直接抵消，若为奇数， $sum1$ 加一

Question ：为什么优先 $a_i=b_i=1$ ？

Answer ：因为这样不仅给自己的 $sum$ 加了一个，还使别人少了一个，相当于取一次赚两个，当然优先。

## Step 2 第二轮取

接下来分析 $a_i=1$ 或 $b_i=1$ 的情况（两个只有 $1$ 个是 $1$），设 $p$ ，若是小A取，则 $p=1$ ，若是小B取，则 $p=2$ ，可分 $4$ 种情况。

1. $p=1$ 且 $a_i=1$ ：$sum1$ 加一，标记已取，换人。

1. $p=1$ 且 $b_i=1$ ：标记已取，换人。

1. $p=2$ 且 $a_i=1$ ：标记已取，换人。

1. $p=2$ 且 $b_i=1$ ：$sum2$ 加一，标记已取，换人。

Question：为什么第 $2$ 种情况和第 $3$ 种情况对自己的 $sum$ 没有贡献但也可以与第 $1$ 种情况和第 $4$ 种情况同级处理呢？

Answer：因为如果我取了这个之后，别人就不能取，而这个位置别人是 ```1``` ，所以相当于使别人少了一个 ```1``` 的可能（也就相当于是有利于自己了）。

## Step 3 代码

另外如果还有问题的话就看我的代码吧，个人觉得注释还比较详尽。

code ：

```cpp
#include<iostream>
using namespace std;
bool a[2000005],b[2000005],bj[2000005];
//注意数组要开两倍，因为有2*n个数据！！！
int main(){
    int n,num=0,sum1=0,sum2=0;
    cin>>n;
    n*=2;
    //在这里先乘，后面直接用n就可以了
    for(int i=1;i<=n;i++){char c;cin>>c;a[i]=c-'0';}
    for(int i=1;i<=n;i++){char c;cin>>c;b[i]=c-'0';}
    //注意输入没有空格，所以要用char转换一下
    for(int i=1;i<=n;i++){
        if(a[i]==1&&b[i]==1){num++;bj[i]=1;}
        //这里一定要标记已取，要不然会在下面重复取
    }
    if(num%2==1)sum1++;
    int p=num%2+1;
    //若num为奇数，则p=2，即小B先取；若num为偶数，则p=1，即小A先取
    for(int i=1;i<=n;i++){
        if(bj[i]==1)continue;
        if(p==1&&a[i]==1){sum1++;bj[i]=1;p=2;}
        if(p==1&&b[i]==1){bj[i]=1;p=2;}
        if(p==2&&a[i]==1){bj[i]=1;p=1;}
        if(p==2&&b[i]==1){sum2++;bj[i]=1;p=1;}
        //四种情况，一一讨论
    }
    if(sum1>sum2)cout<<"First";
    if(sum1<sum2)cout<<"Second";
    if(sum1==sum2)cout<<"Draw";
    //最后判断，输出结果
    return 0;
}
```

---

## 作者：yu__xuan (赞：1)

### 题目

[CF293A Weird Game](https://www.luogu.com.cn/problem/CF293A)

### 吐槽

翻译有点假。不需要输出引号。

### 思路

因为最后可以随便排序，所以最后的结果只和 $1$ 的数量有关系， $1$ 的数量确定了的话 $0$ 的数量也是确定的。

选数的策略：

1.自己有 $1$ 和对面的 $1$ 在同一位置就选这个 $1$，这样能增加自己的 $1$ 减少对面的 $1$。

2.没有 $1$ 相对之后，如果自己有 $1$ 就选，这时 $1$ 一定对着 $0$。自己如果没有 $1$ 就只能选 $0$，$0$ 可能对着 $1$ 也可能对着 $0$，如果对面还有 $1$，我们就可以选 $0$ 来减少对面的 $1$。

综上得到一种贪心策略。

### Code

```cpp

#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>

int n, ans1, ans2;
std::string s1, s2;

int main() {
	std::cin >> n >> s1 >> s2;
	int num = 0, num1 = 0, num2 = 0;
	for (int i = 0; i < 2 * n; ++i) {
		if (s1[i] == '1') ++num1;
		if (s2[i] == '1') ++num2;
		if (s1[i] == '1' && s1[i] == s2[i]) ++num;
	}
	bool flag = 0;
	int ans1 = 0, ans2 = 0, cnt = num;
	while(num) {//两个人都用自己的 1 去删对面的 1
		if (!flag) {
			--num2;
			--num1;
			++ans1;
			flag = 1;
		} 
		else {
			--num1;
			--num2;
			++ans2;
			flag = 0;
		}
		num--;
	}
	while(cnt < 2 * n) {
		if (!flag) {
			if (num1) {
				--num1;
				++ans1;
			}//自己有 1 可以选 
			else {//自己没有 1 能选但是自己有 0 对着对面的 1 ，选 0 去删对面的 1 
				if (num2) --num2;
			}
			flag = 1;
		}
		else {//类似上面
			if (num2) {
				--num2;
				++ans2;
			}
			else {
				if (num1) --num1;
			}
			flag = 0;
		}
		++cnt;
	}
	if (ans1 > ans2) puts("First");
	else if (ans1 < ans2) puts("Second");
	else puts("Draw");
	return 0;
}
```

---

## 作者：cosf (赞：0)

首先我们先明确一下策略：两个人都先从 $s, t$ 中均为 $1$ 的地方去选。

为什么呢？因为，选了这种地方，你不仅能保住你的一个 $1$，还可以取消掉对方的一个 $1$。其他的位置满足不了这两个要求。

这也就是说，两个都是 $1$ 的部分是两两抵消的。如果多了一个，可以当作是给第一个人的。

剩下的就是一些给第一个人的和给第二个人的数。我们令第一个人的数有 $a$ 个，第二个人有 $b$ 个，那么在 $a < b - 1$ 的时候第一个人会输，$b - 1 \le a \le b$ 的时候会平局，$b \lt a$ 的时候会胜利。这一步也是两两相消的，可以用类似的理论证明。

## 代码

```cpp
#include <iostream>
using namespace std;

int n;

string a, b;

int main()
{
    cin >> n >> a >> b;
    int x = 0, y = 0; // x 记录的是两人的差
    for (int i = 0; i < (n << 1); i++)
    {
        if (a[i] == '1' && b[i] == '0')
        {
            x++;
        }
        if (a[i] == '1' && b[i] == '1')
        {
            y ^= 1;
        }
        if (a[i] == '0' && b[i] == '1')
        {
            x--;
        }
    }
    if (y)
    {
        x++;
    }
    if (x < -1)
    {
        cout << "Second" << endl;
    }
    else if (x < 1)
    {
        cout << "Draw" << endl;
    }
    else
    {
        cout << "First" << endl;
    }
    return 0;
}

```

---

## 作者：I_will_AKIOI (赞：0)

我们发现判断双方两个数的大小只和他们手里 $1$ 的数量有关。无论如何，他们二人都是能取到 $n$ 个数的。所以这里 $0$ 只是起到一个占位的作用。

接着我们将数列分成 $4$ 种情况。$a_i=1,b_i=1;a_i=1,b_i=0;a_i=0,b_i=1;a_i=0,b_i=0$。

第四种情况是没什么用的，因为我们说过 $0$ 只是占位的作用，取不取都没关系。对于 A 来说，第一种和第二种能拿到 $1$，而对于 B 来说，第一种和第三种能拿到 $1$。

由于第一种情况对双方都有利，所以要先拿第一种情况。接着 A 先拿第二种，B 拿第三种。先预处理一下三种情况的个数，接着代码就很简单了。

```
#include<bits/stdc++.h>
using namespace std;
int n,cnt,cnt1,cnt2,sum1,sum2;//sum1和sum2表示A,B拿到1的个数
char a[2000005],b[2000005];
int main()
{
  ios::sync_with_stdio(0);
  cin>>n;
  for(int i=1;i<=n*2;i++) cin>>a[i];
  for(int i=1;i<=n*2;i++) cin>>b[i];
  for(int i=1;i<=n*2;i++)
  {
    if(a[i]=='1'&&b[i]=='1') cnt++;
    if(a[i]=='1'&&b[i]=='0') cnt1++;
    if(a[i]=='0'&&b[i]=='1') cnt2++;
    //记录三种情况
  }
  for(int i=1;i<=n;i++)
  {
    if(cnt) sum1++,cnt--;
    else if(cnt1) sum1++,cnt1--;
    else if(cnt2) cnt2--;
    if(cnt) sum2++,cnt--;
    else if(cnt2) sum2++,cnt2--;
    else if(cnt1) cnt1--;
  }
  if(sum1==sum2) cout<<"Draw";
  else if(sum1>sum2) cout<<"First";
  else cout<<"Second";
  return 0;
}
```

---

