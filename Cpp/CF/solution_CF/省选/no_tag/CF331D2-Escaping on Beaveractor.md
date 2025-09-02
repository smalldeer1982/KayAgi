# Escaping on Beaveractor

## 题目描述

Don't put up with what you're sick of! The Smart Beaver decided to escape from the campus of Beaver Science Academy (BSA). BSA is a $ b×b $ square on a plane. Each point $ x,y $ $ (0<=x,y<=b) $ belongs to BSA. To make the path quick and funny, the Beaver constructed a Beaveractor, an effective and comfortable types of transport.

The campus obeys traffic rules: there are $ n $ arrows, parallel to the coordinate axes. The arrows do not intersect and do not touch each other. When the Beaveractor reaches some arrow, it turns in the arrow's direction and moves on until it either reaches the next arrow or gets outside the campus. The Beaveractor covers exactly one unit of space per one unit of time. You can assume that there are no obstacles to the Beaveractor.

The BSA scientists want to transport the brand new Beaveractor to the "Academic Tractor" research institute and send the Smart Beaver to do his postgraduate studies and sharpen pencils. They have $ q $ plans, representing the Beaveractor's initial position $ (x_{i},y_{i}) $ , the initial motion vector $ w_{i} $ and the time $ t_{i} $ that have passed after the escape started.

Your task is for each of the $ q $ plans to determine the Smart Beaver's position after the given time.

## 样例 #1

### 输入

```
3 3
0 0 0 1
0 2 2 2
3 3 2 3
12
0 0 L 0
0 0 L 1
0 0 L 2
0 0 L 3
0 0 L 4
0 0 L 5
0 0 L 6
2 0 U 2
2 0 U 3
3 0 U 5
1 3 D 2
1 3 R 2
```

### 输出

```
0 0
0 1
0 2
1 2
2 2
3 2
3 2
2 2
3 2
1 3
2 2
1 3
```

# 题解

## 作者：NightDiver (赞：4)

考场上上厕所的时候灵机一动，为什么不倍增呢？

考虑如何倍增。

$f[s][dir][x][y] = \{x',y',di'\}$。

表示从点 $(x,y)$ 开始以 $dir$ 的方向走 $2^s$ 步，走到了点 $(x',y')$ ，在 $(x',y')$ 上的方向为 $di'$。

先处理出走一步（$2^0$ 步）的情况：输入传送带时把传送带上所有点打上方向标记，走一步时考虑目前处于的点和将要到达的点是否在传送带上即可。

然后逐步合并，直到 $2^{50}>1e15$ 步。

但是出现了问题，空间复杂度为 $O(3\times4\log_2{1e15} b^2)$，算出来要开 $6e8$ 个 $int$，根本开不下。

但我们发现，题目里并没用要求强制在线，于是我们先把询问都离线下来。

使用滚动数组：对于每个 $s$，检查每个 $\text{lowbit}(x)$ 是否等于 $2^s$，若是，进行倍增。然后合并成 $s+1$。

这样空间复杂度就变为了 $O(3\times4b^2)$，时间复杂度 $O(3\times4\log_2{1e15} b^2 + q\log_2t)$，虽然看起来很极限，但是能过。

[代码在这里](https://www.cnblogs.com/TongKa/p/18186612)

---

## 作者：skyskyCCC (赞：1)

## 前言。
本片题解仅仅针对 $D2$ 并且对于 $D1$ 的相应结论不再阐述，如果还没有了解基本结论，请移步至[题解](https://www.luogu.com.cn/blog/zzy-sky/solution-cf331d1)。

随着 $b$ 的数据范围逐渐增大，做法也越来越负载，但是这个题在原题的基础上进行一些修改和优化即可。
## 分析。
我们仍可以通过预处理每次询问的循环节，但是特殊地，我们我们需要预处理出来整个图。显然我们只关心是否是有循环节，所以我们不妨都看做是一个循环节，然后在最后进行找寻即可。但是我们如何省去直接循环的那一个过程呢？这里我们可以采用一种类似于压缩的方法进行预处理。就是我们用一个数组去保存这个可能的经过路线，然后将它假装扩大，最终只需要在统计答案时看看是否有经过的路线从而判断循环节。可以证明，这些压缩后储存的点的修改值显然不会出现相同的，然后将他们保存进去。这样相当于我们我们在 $ans$ 数组中存了所有可能的坐标，并且每一次询问都在一段区间内存上了一个相应的数值。最后把每一个询问对应的 $ans_i$ 都进行拆分即可。

描述的可能有一些晦涩，可以根据代码理解。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
#include<map>
using namespace std;
int n,b,q,x1,x2,y_1,y2,x,y;
char way;
long long t[100005];
int ansx,ansy,dfx,dfy;
int dx[5]={0,1,0,-1,0};// 0 1 2 3 4
int dy[5]={0,0,1,0,-1};// - R U L D
int G[1005][1005];
int sum[1005*1005*10][2];
int ans[1005*1005*10];
int work(int x,int y,int dis){
	if(G[x][y]){
		dis=G[x][y];
	}
	return dis*1005*1005+x*1005+y;
}
void add(int x1,int y_1,int x2,int y2){//建图。 
    int dis=0;
    if (x1==x2){
        (y_1<y2)?dis=2:dis=4;
        //处理上下移动的情况。 
    }
    else{
        (x1<x2)?dis=1:dis=3;
        //处理左右移动的情况。 
    }
    G[x2][y2]=dis;
    while (x1!=x2||y_1!=y2){
        G[x1][y_1]=dis;
        x1+=dx[dis];
        y_1+=dy[dis];
    }
}
int main(){
	cin>>n>>b;
	for(int i=1;i<=n;i++){
		cin>>x1>>y_1>>x2>>y2;
		add(x1,y_1,x2,y2);
	}
	for(int i=0;i<=b;i++){
		for(int j=0;j<=b;j++){
			for(int k=1;k<=4;k++){
				if(G[i][j]&&G[i][j]!=k){
					continue;
				}
				dfx=i+dx[k];
				dfy=j+dy[k];
				int chooik=work(i,j,k);
				if(dfx<0||dfx>b||dfy<0||dfy>b){
					sum[chooik][0]=chooik;
				}
				else sum[chooik][0]=work(dfx,dfy,k);
			}
		}
	}
	cin>>q;
	for(int i=1;i<=q;i++){
		int dis=0;
		cin>>x>>y>>way>>t[i];
		if(way=='R') dis=1;
		if(way=='U') dis=2;
		if(way=='L') dis=3;
		if(way=='D') dis=4;
		ans[i]=work(x,y,dis);
	}
	for(int i=0;i<=60;i++){
		for(int j=1;j<=q;j++){
			if(t[j]&((long long)1<<i)){
				ans[j]=sum[ans[j]][i&1];
			}
		}
		for(int j=1;j<1005*1005*5;j++){
			sum[j][(i&1)^1]=sum[sum[j][i&1]][i&1];
		}
	}
	for(int i=1;i<=q;i++){
		ansy=ans[i]%1005;
		ans[i]/=1005;
		ansx=ans[i]%1005;
		cout<<ansx<<" "<<ansy<<"\n";
	}
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

