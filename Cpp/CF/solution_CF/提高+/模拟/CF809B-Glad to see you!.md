# Glad to see you!

## 题目描述

This is an interactive problem. In the output section below you will see the information about flushing the output.

On Sunday Leha the hacker took Nura from the house where she lives and went with her to one of the most luxurious restaurants in Vičkopolis. Upon arrival, they left the car in a huge parking lot near the restaurant and hurried inside the building.

In the restaurant a polite waiter immediately brought the menu to Leha and Noora, consisting of $ n $ dishes. It is interesting that all dishes in the menu are numbered with integers from $ 1 $ to $ n $ . After a little thought, the girl ordered exactly $ k $ different dishes from available in the menu. To pass the waiting time while the chefs prepare ordered dishes, the girl invited the hacker to play a game that will help them get to know each other better.

The game itself is very simple: Noora wants Leha to guess any two dishes among all ordered. At the same time, she is ready to answer only one type of questions. Leha can say two numbers $ x $ and $ y $ $ (1<=x,y<=n) $ . After that Noora chooses some dish $ a $ for the number $ x $ such that, at first, $ a $ is among the dishes Noora ordered ( $ x $ can be equal to $ a $ ), and, secondly, the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF809B/5b39ae684d986558584ee8b76189689ad8c74fb2.png) is the minimum possible. By the same rules the girl chooses dish $ b $ for $ y $ . After that Noora says «TAK» to Leha, if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF809B/ae5a4cbdbe904f98871cc774766e6f251e22446e.png), and «NIE» otherwise. However, the restaurant is preparing quickly, so Leha has enough time to ask no more than $ 60 $ questions. After that he should name numbers of any two dishes Noora ordered.

Help Leha to solve this problem!

## 说明/提示

There are three dishes in sample. Noora ordered dished numberes $ 2 $ and $ 3 $ , which Leha should guess. If Noora receive requests for the first dish ( $ x=1 $ ), then she'll choose the second dish ( $ a=2 $ ) as the dish with the minimum value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF809B/5b39ae684d986558584ee8b76189689ad8c74fb2.png). For the second ( $ x=2 $ ) and the third ( $ x=3 $ ) dishes themselves will be optimal, because in that case ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF809B/dc32bff1a2127d4d1040e24b8616661f02b0c678.png).

Let Leha asks Noora about the next couple of dishes:

- $ x=1 $ , $ y=2 $ , then he'll recieve «NIE» answer, because $ |1-2|&gt;|2-2| $
- $ x=2 $ , $ y=1 $ , then he'll recieve «TAK» answer, because $ |2-2|<=|1-2| $
- $ x=1 $ , $ y=3 $ , then he'll recieve «NIE» answer, because $ |1-2|&gt;|3-3| $
- $ x=3 $ , $ y=1 $ , then he'll recieve «TAK» answer, because $ |3-3|<=|1-2| $
- $ x=2 $ , $ y=3 $ , then he'll recieve «TAK» answer, because $ |2-2|<=|3-3| $
- $ x=3 $ , $ y=2 $ , then he'll recieve «TAK» answer, because $ |3-3|<=|2-2| $

According to the available information, it is possible to say that Nura ordered dishes with numbers $ 2 $ and $ 3 $ .

## 样例 #1

### 输入

```
3 2
NIE
TAK
NIE
TAK
TAK
TAK
```

### 输出

```
1 1 2
1 2 1
1 1 3
1 3 1
1 2 3
1 3 2
2 2 3
```

# 题解

## 作者：rui_er (赞：4)

本文是我的 CF 思维题集锦的第二期，[点我返回索引](https://www.luogu.com.cn/blog/ak-ioi/codeforces-0)。

原题链接：[809B Glad to see you!](https://codeforces.com/problemset/problem/809/B) (binary search, interactive, \*2200)

**题意简述**

交互题，长度为 $n$ 的数列选中了 $k$ 个位置，可以指定 $x,y$ 询问 $x$ 到最近的选中的位置的距离是否小于等于 $y$ 到最近的选中的位置的距离，需要在 $60$ 次询问内得到任意两个选中的位置。

**解法分析**

 $n\le 10^5$，询问不超过 $60$ 次，明示二分（事实上算法标签也是这样）。
 
考虑在 $\left[1,n\right]$ 中二分询问 $mid,mid+1$，根据题意，当得到肯定结果 `TAK` 的时候，在左侧必然有一个选中的位置，反之同理。

这样二分的结果就是第一个位置 $x$。

那么第二个位置怎么得到呢？继续在 $\left[1,n\right]$ 中二分显然是不行的，将会得到相同的结果。不过我们可以尝试在 $\left[1,x-1\right]$ 中二分。但是如果第一次二分得到的 $x$ 是最左侧的选中的位置，在这个范围内没有答案怎么办呢？没关系，$60$ 大约是 $\log_210^5$ 的三倍，我们还可以在 $\left[x+1,n\right]$ 再次二分。

最后一个细节：怎么判断在左侧是否有解呢？如果二分的结果与第一次得到的 $x$ 相等，显然得到了一个假的（重复的）解，此时在左侧无解。同时，因为 $x$ 是一个选中的位置，它的距离永远是 $0$，因此如果询问 $y,x$ 得到 `NIE` 就说明 $y$ 的距离大于 $0$，即 $y$ 不是一个解。

**代码**

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
#define loop while(true)
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
#define fil(x,y) memset(x, y, sizeof(x))
#define mulT0 int T; for(scanf("%d", &T);T;T--)
#define mulT1 int T, rnds; for(scanf("%d", &T),rnds=1;rnds<=T;rnds++)
using namespace std;
typedef long long ll;

int n, k, x, y;
bool interact(int x, int y) {
	printf("1 %d %d\n", x, y);
	fflush(stdout);
	char c[4];
	scanf("%s", c);
	return c[0] == 'T';
}
void give(int x, int y) {
	printf("2 %d %d\n", x, y);
	fflush(stdout);
}
int binarySearch(int l, int r) {
	while(l < r) {
		int mid = (l + r) >> 1;
		if(interact(mid, mid+1)) r = mid;
		else l = mid + 1;
	}
	return l;
}

int main() {
	scanf("%d%d", &n, &k);
	x = binarySearch(1, n);
	y = binarySearch(1, x-1);
	if(!(x ^ y) || !interact(y, x)) y = binarySearch(x+1, n);
	give(x, y);
	return 0;
}
```

---

## 作者：一E孤行 (赞：3)

一个非常有意思的交互题。

一眼看上去，那个 $k$ 显然是没有什么用的，然后 $n\leq10^5$ ，询问次数不超过 $60$ 次，这已经是把二分写到脸上了，而且给了大概 $3$ 次二分的次数。

题目询问与回答的方式十分抽象，我们应想办法将其具象化，即一次询问我们应该想办法使得这个回答能否告诉我们当前区间左半边是否一定有答案。

相邻 $2$ 个数具有非常优美的性质，我们考虑每次询问 $(x,x+1)$ ，如果在左边的数离这两个数更近，那么就会返回 $TAK$ ，我们优先去找那个离得最近的那个，在左区间中继续二分。如果右边离得更近，会返回 $NIE$ ，同理，我们在右区间中继续二分。最后一种情况是左边的数离 $x$ 和右边的数离 $x+1$ 一样近，那么也会返回 $TAK$ ，但是我们不妨选取左边的区间继续二分。这样就会涵盖所有的情况，最终二分结束找到第一解。

假设找到的第一个解为 $x$，那么第二个解可能在 $[1,x-1]$ ，也有可能在 $[x+1,n]$ ，但最坏的情况下我们在这两个区间都需要二分一下，这就是题目为什么要给 $3$ 次二分的次数的原因。我们可以现在左区间中二分，如果发现求出的答案恰好与第一次求出的答案相等，那么左区间肯定不存在答案，我们向右区间询问即可。如果求出的答案不等于 $x$ ，那么我们需要判断这个答案是否合法，判断方式为我们询问 $(y,x)$ ， $x$ 必定为一个答案，所以 $|x-b|=0$ 。此时只有 $|y-a|$ 也为 $0$ 的时候，才能说明 $y$ 也是一个答案，否则我们在右区间二分即可。

```cpp
#include<cstdio>
#include<algorithm>
#include<queue>
#include<iostream>
#include<cstring>
#include<ctime>
#include<cmath>
using namespace std;
char s[10];
int check(int mid,int mid_) {
    printf("1 %d %d\n",mid,mid_);
    fflush(stdout);
    scanf("%s",s);
    if(s[0] == 'T') return 1;
    return 0;
}
int bin(int l,int r) {
    while(l < r) {
        int mid=(l+r)>>1;
        if(check(mid,mid+1)) r=mid;
        else l=mid+1;
    }
    return l;
}
int main() {
    int c1=clock();
#ifdef LOCAL
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif
    //=========================================
     int k,n;
     scanf("%d %d",&n,&k);
     int x=bin(1,n);
     int y=bin(1,x-1);
     if(x == y || check(y,x) == 0) y=bin(x+1,n);
     printf("2 %d %d\n",x,y);
     fflush(stdout);
    //=========================================
    cerr<<"Time Used:"<<clock()-c1<<"ms"<<endl;
    return 0;
}


---

## 作者：TheLostWeak (赞：3)

[在博客查看](https://www.cnblogs.com/chenxiaoran666/p/CF809B.html)

**大致题意：** 交互题。已知在一个长度为$n$的序列中选中了$k$个位置，你每次可以询问两个位置$x,y$，则若$|x-a|\le |y-b|$（$a,b$为$k$个被选中的位置中分别离$x,y$最近的位置），返回$TAK$，否则返回$NIE$。你需要在$60$次询问内求出任意两个被选中的位置并输出。（~~其实k根本没啥用~~）

### 二分

$60$次询问，一看就是$log$级别的，一下就能想到二分。而且看数据范围，$60$次询问大概足够二分$3$轮了。

那我们来考虑怎么二分。

假设我们已知在区间$[l,r]$中有被选中的位置，则我们询问$[mid,mid+1]$。

若返回$TAK$，说明在区间$[l,mid]$中必然有被选中的位置，否则说明在区间$[mid+1,r]$中必然有被选中的位置。

按这样二分，只需一轮下来我们就能求出一个位置了。

然后考虑怎么求第二个位置，显然不能再按上面的套路了，否则只会得到一个完全一样的结果。

设第一个答案为$t1$，如果我们在$[1,t1-1]$中以同样的方式进行一轮二分，不就可以得出一个异于$t1$的新答案了吗？

然而，如果$[1,t1-1]$中并没有答案呢？

别着急，这就是题目给我们二分$3$轮的次数的原因。如果$[1,t1-1]$中没有答案，我们就到$[t1+1,n]$中再进行第三轮二分，这样就肯定能求出另一个答案了。

整理下上面的思路，最后再讲一个细节问题：如何判断$[1,t1-1]$中没有答案。

对于在$[1,t1-1]$中二分出的结果$t2$，如果$t2=t1$，或者询问$t2,t1$得到$NIE$（因为对于$t1$来说最近距离为$0$，得到$NIE$说明$t2$最近距离大于$0$，即其本身并非答案），就说明$t2$是个伪答案。

### 代码

```cpp
#include<bits/stdc++.h>
#define Tp template<typename Ty>
#define Ts template<typename Ty,typename... Ar>
#define Reg register
#define RI Reg int
#define Con const
#define CI Con int&
#define I inline
#define W while
#define write(op,x,y) (printf("%d %d %d\n",op,x,y),fflush(stdout))//交互输出
#define Check() (scanf("%s",s+1),s[1]=='T')//读入结果
using namespace std;
int n,k;char s[10];
I int Solve(RI l,RI r)//二分
{
	RI mid;W(l<r) mid=l+r>>1,write(1,mid,mid+1),
		scanf("%s",s+1),s[1]=='T'?r=mid:l=mid+1;return l;
}
int main()
{
	scanf("%d%d",&n,&k);RI t1,t2;t1=Solve(1,n),//求出第一个答案
	((t2=Solve(1,t1-1))==t1||!(write(1,t2,t1),Check()))&&(t2=Solve(t1+1,n));//求出第二个答案
	return write(2,t1,t2),0;
}
```


---

## 作者：Eltaos_xingyu (赞：1)

让我对二分有了更深的理解。

首先 $60$ 大约是 $3\log n$。我第一个肯定想的是二分 $3$ 次左右，但是我没有看出这个询问的一些特殊性质。

其实显然 $(x,x+1)$ 的一个询问就有很好的一个性质。询问 $(x,x+1)$，我们会得到一个由 `NIE` 的一些连续段和 `TAK` 的一些连续段组成的一个序列，对于每一个 `NIE` 和 `TAK` 的连续段交界处（即 `...,NIE,TAK,...`），这个 `TAK` 处就一定是一个选中的点。

假设 $0$ 位置是 `NIE`，一个完整的序列必然存在至少一个这样的交界，我们可以二分找出其任意一个交界处。

> 为什么可以直接二分？
>
> 考虑到假如说这次询问是 `TAK`，那么左侧一定存在一个交界，所以我们往左递归是没有问题的。
>
> 而如果是 `NIE`，首先我们发现如果往左递归过，那么此时一定正确；
>
> 如果之前没有往左递归过，除了最右侧是选中的位置外，序列结尾一定都是 `TAK`；而二分的时候如果遇到最右侧是选中的位置时，因为二分每次去掉一半的问题规模，而正好 `NIE` 和 `TAK` 此时应该是对半分的，所以这个时候二分根本不会去找最后一个元素，它会先找到前一个元素的 `TAK`，然后去找前面一个元素。

找到这个交界处之后，我们可以特判最后一个元素是否被选择，然后对左区间二分找到另外一个交界处。当然有一种情况就是第一次二分出来的交界处就已经是最左边的交界处了，这个时候可以直接二分右区间，至于为什么当这个区间开头没有元素时不会二分到这个区间开头的 `TAK`，其实证明和上面证明不会二分找最后一个元素差不多。

这样我们就解决了这个问题。

一句题外话：我把忘了删 `system("pause")` 的代码交到 CF 上过了，非常神秘。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
char tmp;
bool ask(int x,int y){
	cout<<1<<" "<<x<<" "<<y<<"\n";
	cout.flush();
	cin>>tmp>>tmp>>tmp;
	return tmp=='K';
}
void end(int x,int y){
	cout<<2<<" "<<x<<" "<<y<<"\n";
	cout.flush();
	exit(0);
}
int getpos(int l,int r){
	int pos=0;
	while(l<=r){
		int mid=(l+r)/2;
		if(ask(mid,mid+1))pos=mid,r=mid-1;
		else l=mid+1;
	}
	return pos;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>k;
	int x=getpos(1,n-1);
	int y=getpos(1,x-1);
	if(!y||x==y){
		y=getpos(x+1,n-1);
		if(ask(n,x))y=n;
	}
	end(x,y);
	return 0;
}
```

---

