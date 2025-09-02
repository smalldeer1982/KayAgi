# Mad Joe

## 题目描述

Joe has been hurt on the Internet. Now he is storming around the house, destroying everything in his path.

Joe's house has $ n $ floors, each floor is a segment of $ m $ cells. Each cell either contains nothing (it is an empty cell), or has a brick or a concrete wall (always something one of three). It is believed that each floor is surrounded by a concrete wall on the left and on the right.

Now Joe is on the $ n $ -th floor and in the first cell, counting from left to right. At each moment of time, Joe has the direction of his gaze, to the right or to the left (always one direction of the two). Initially, Joe looks to the right.

Joe moves by a particular algorithm. Every second he makes one of the following actions:

- If the cell directly under Joe is empty, then Joe falls down. That is, he moves to this cell, the gaze direction is preserved.
- Otherwise consider the next cell in the current direction of the gaze. 
  - If the cell is empty, then Joe moves into it, the gaze direction is preserved.
  - If this cell has bricks, then Joe breaks them with his forehead (the cell becomes empty), and changes the direction of his gaze to the opposite.
  - If this cell has a concrete wall, then Joe just changes the direction of his gaze to the opposite (concrete can withstand any number of forehead hits).

Joe calms down as soon as he reaches any cell of the first floor.

The figure below shows an example Joe's movements around the house.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF250E/aabe6062681eed440c39038fe1d895d0f5c78597.png)Determine how many seconds Joe will need to calm down.

## 样例 #1

### 输入

```
3 5
..+.#
#+..+
+.#+.
```

### 输出

```
14```

## 样例 #2

### 输入

```
4 10
...+.##+.+
+#++..+++#
++.#++++..
.+##.++#.+
```

### 输出

```
42
```

## 样例 #3

### 输入

```
2 2
..
++
```

### 输出

```
Never```

# 题解

## 作者：_edge_ (赞：0)

题目的意思大概是给一个怪物，然后它一开始看着右边，每一秒它会做出如下行动：

1. 如果它的下面是空着的，那么它就掉下去特别特别注意**它的视线不变，也就是说它一开始向右看，那么掉下去也向右看。**

1. 否则它就往视线的方向走，如果碰到 `+` 也就是砖做的墙，它会破坏掉，然后换视线，如果是 `#` 那么它破坏不了，但它依然会换视线，这一个操作可以看成 $1$ 秒之内完成的。

它要一直往下，直到它到了最下面，当然，如果怎么样它都下不去输出 `Never` ，如果可以，那么输出秒数。

我相信大家都应该会 $O(nm^2)$ 的做法，就是搞个指针，然后向左或者向右扩张，暴力模拟，很明显这样子是过不去的。

考虑优化，我们考虑上面那个做法哪些地方不足。

首先明知道中间有一段是空着的，还要走一下，这样时间是浪费掉的，所以我们考虑去优化这个时间。

如果中间空着，那么我们可以直接让这个怪物给瞬移过去。

大体思路是，搞两个指针 $l$ 和 $r$，首先扩张，如果扩张不了了，那么对于答案直接加上 $r-l$ ，然后再换一头扩张。

这边我判 `Never` 是直接看是否有扩张，或者砸墙。

需要注意的是**它的视线不变，也就是说它一开始向右看，那么掉下去也向右看**，这个处理起来要稍微注意一下，否则你过不了样例 $2$，还有一个坑点是要开 long long ，最后记得加上向下走时候花费的时间。

```cpp
#include <iostream>
#include <cstdio>
#define int long long 
using namespace std;
const int INF=105;
const int INFN=1e4+5;
int n,m,Map[INF][INFN],l,r,ans,ll,rr,fl1,fang;
char ch;
int solvel(int x) {
    #define i x
    ans+=r-l;int fl=0;
    while (Map[i][l-1]==0) {
        if (Map[i+1][l]==0) {fl=1;r=l;return 1;}
        l--,ans++;fl1=0;
    }
    if (Map[i+1][l]==0) {fl=1;r=l;return 1;}
    if (fl) return 1;
    if (Map[i][l-1]==1) {
        Map[i][l-1]=0;
        ans++;fl1=0;
    } 
    else ans++;
    //if (ll==l && r==rr && fl1) {cout<<"Never\n";return 2;}
    return 0;
}
int solver(int x) {
    ans+=r-l;int fl=0;
    while (Map[i][r+1]==0) {
        if (Map[i+1][r]==0) {fl=1;l=r;return 1;}
        r++,ans++;fl1=0;
    }
    if (Map[i+1][r]==0) {fl=1;l=r;return 1;}
    if (fl) return 1;
    if (Map[i][r+1]==1) {
        Map[i][r+1]=0;
        ans++;fl1=0;
    } 
    else ans++;
    return 0;
}
#undef i
signed main()
{
    scanf("%lld %lld ",&n,&m);
    for (int i=1;i<=n;i++) {
        for (int j=1;j<=m;j++) {
            scanf(" %c",&ch);
            if (ch=='.') Map[i][j]=0;
            else if (ch=='+') Map[i][j]=1;
            else if (ch=='#') Map[i][j]=2;
        }
    }
    for (int i=1;i<=n;i++)
        Map[i][0]=Map[i][m+1]=2;
    l=1,r=1,ans=0;
    for (int i=1;i<=n;i++) {
        while (true) {
            ll=l;rr=r;fl1=1;
            if (fang==0) {
                int r1=solver(i);
                if (r1==1) {fang=0;break;}
                int l1=solvel(i);
                if (l1==1) {fang=1;break;}  
            }
            else {
                int l1=solvel(i);
                if (l1==1) {fang=1;break;}  
                int r1=solver(i);
                if (r1==1) {fang=0;break;}
            }
            //cout<<l<<" "<<r<<" over "<<i<<" "<<ans<<"\n";
            //cout<<l<<" "<<r<<" over "<<i<<" "<<ans<<"\n";
            if (ll==l && rr==r && fl1) {cout<<"Never\n";return 0;}
        }
        //cout<<l<<" "<<r<<" "<<ans<<" break\n";
    }
    cout<<ans+n-1<<"\n";
    return 0;
}
```


---

## 作者：bellmanford (赞：0)

CF250的后三题居然没人交翻译和题解。。。

毕竟是上古比赛了，所以最后一题有些水。

这个题面就告诉了我们这是模拟，但是很容易发现直接模拟会 TLE ，因为如果有一层放满了砖头，在这一层就会做到 $\mathcal{O(m^2)}$ 。

所以要做一点优化，可以发现有很多的路程都是重复走过的，那只要分层计算的时候，记录跑过的区间，因为跑过的区间是不会存在砖块的，所以转向到达另一边的时候就可以直接跳到另一端点，时间加上跳过的长度，总复杂度就可以达到 $\mathcal{O(nm)}$ 了。

细节见代码。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;

#define int long long

int read(){
	int x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*y;
}

int n,m,tim=0;
char Map[105][10005];
void solve(){
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		scanf("%s",Map[i]+1);
		Map[i][0]=Map[i][m+1]='#';//将两边变为墙 
	}
	int now=1,fx=1;//现在所处的位置，也就是某一层的出发点和面对的方向 
	for(int i=1;i<n;i++){//只用枚举前 n-1 层，因为到了最后一层就结束了 
		if(Map[i+1][now]=='.'){//特判直接下掉的情况 
			tim++;
			continue ;
		}
		int l=now-1,r=now+1;//走过的区间的左边过去一个和右边过去一个 
		while(1){
			if(Map[i][l]=='#'&&Map[i][r]=='#') return (void)(printf("Never\n"));//两边都是墙就不可能走出去了 
			tim+=r-l-2;//累加重复走过的地方 
			if(fx==1){
				while(Map[i][r]=='.'&&Map[i+1][r]!='.') r++,tim++;//如果前面有路且不会掉下去就增加右端点 
				if(Map[i][r]=='.'){
					now=r,tim+=2;//因为前面的 while ，所以此时如果有路就意味着前面会掉下去，往前走和下掉各花费一秒，然后更新出发点 
					break;
				}
				if(Map[i][r]=='+') fx=-fx,tim++,Map[i][r]='.';//遇到砖头的情况 
				else if(Map[i][r]=='#') fx=-fx,tim++;//遇到墙的情况 
			}
			else{//另一个方向同理 
				while(Map[i][l]=='.'&&Map[i+1][l]!='.') l--,tim++;
				if(Map[i][l]=='.'){
					now=l,tim+=2;
					break;
				}
				if(Map[i][l]=='+') fx=-fx,tim++,Map[i][l]='.';
				else if(Map[i][l]=='#') fx=-fx,tim++;
			}
		}
	}
	return (void)(printf("%lld\n",tim));
}

signed main(){
	solve();
}
```


---

