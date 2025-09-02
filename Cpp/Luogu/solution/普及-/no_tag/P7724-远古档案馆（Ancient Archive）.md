# 远古档案馆（Ancient Archive）

## 题目背景

为了揭开月光能量背后的秘密，你来到了地下的远古档案馆。

远古一族的秘密与遗忘的知识悉数贮藏于这片被尘封的迷宫中，你能成功解谜，获知远古的知识吗？


## 题目描述

远古档案馆的中心是一个解谜：

- 有一个 $2\times 2$ 的网格，每个格子中要么有一个正整数，要么是空的；

- 你可以进行若干次操作：每次操作中，你选择一个**有正整数的格子**和一个**与之相邻的空格子**，将正整数移到那个空格子中；

- 给定网格的初始状态和最终状态，保证初始状态和最终状态中包含的正整数个数相同（设为 $k$ 个），且它们就是前 $k$ 个不同的正整数，问是否可以通过有限次操作从初始状态到达最终状态？

下图展示了一个包含三个正整数的网格经过两次操作的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/y2dnr4ss.png)

只有完成解谜，才能获得遗忘的知识，因此你希望尽快解决这个问题。

**注意：网格中可能没有正整数，也可能没有空格。**

## 说明/提示

**【样例 1 解释】**

如题目描述中图所示。

---

**【样例 2 解释】**

没有可移动的正整数，所以无法从初始状态到达与之不相等的最终状态。

---

**【数据范围】**

**本题采用捆绑测试。**

所有数据符合题目描述所述。

- Subtask 1（40 points）：不存在空格。
- Subtask 2（60 points）：无特殊限制。

---

![](https://cdn.luogu.com.cn/upload/image_hosting/rz2eg0ca.png)

## 样例 #1

### 输入

```
2 1
3 0
0 2
3 1
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
2 1
4 3
3 4
2 1
```

### 输出

```
No
```

# 题解

## 作者：封禁用户 (赞：22)

## P7724 远古档案馆（Ancient Archive）
[原题链接](https://www.luogu.com.cn/problem/P7724)

数据很弱，月赛三十多行过了，补充上所有情况后近百行，竟是道入门题。感谢 logfk 提供 Hack 数据。感谢 mrsrz 和 Anguei 两位管理的认真审核与纠错。

## 思路
题解中已经有朋友打了暴力搜索，我给出一种没有思维难度且代码量较少的 $O(1)$ 解法吧。既然只有四个格子，我们可以找出所有不能移动到最终状态的情况，对输入数据进行逐个判断，如果最后仍不满足条件则可以移动到最终状态。

## 分析
设输入的两个 $2 \times2 $ 方格分别为 $a_{1} \sim a_{4}$，$b_{1} \sim b_{4}$。

首先，如果两个方格完全相同，不用移动，初始状态与最终状态就是相同的。判断是否满足这个条件，只需直接判断四个数字的位置是否完全相同，得出判断（封装成函数，后面会用到）：
```cpp
bool same(){
	if(a[1]==b[1]&&a[2]==b[2]&&a[3]==b[3]&&a[4]==b[4]) return 1;
	return 0;
}
if(same()){
	printf("Yes"); 
	return 0;
}
```

题中已经说明**网格中可能没有正整数，也可能没有空格**，其中没有正整数的情况，即四个数字全部为零，第一条判断语句已经解决了。当网格中没有空格时，分为两种情况：

1. 两个方格完全相同，第一条判断已经解决，不必考虑。

2. 两个方格不同，一定无法移动到最终状态。

只考虑第二种情况，没有空格即四个数字全部不为零。用变量 num 记录网格中空格个数，如果其值为零，没有空格。得出判断：
```cpp
if(num==0){
	printf("No"); 
	return 0;
}
```
暂且跳过只有一个空格的情况，存在两个空格时，又可以分为两种情况，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/pzbloqiz.png)

观察第一种情况，将方格记为 $(2,3,0,0)$，只需要将“2”，“3”向下移动，就能将其转化为 $(0,0,2,3)$，同理第二种情况 $(2,0,0,3)$ 可以转化为 $(0,2,3,0)$，且可以移动到任意状态。而存在三个空格时，唯一的非零数字可以任意移动。可得一条结论：

- 如果存在两个及以上空格，一定能够移动到最终状态。

已经用 num 存储空格个数，得出判断：
```cpp
if(num>=2){
	printf("Yes");
	return 0;
}
```
------------
**以下结论仅适用于只存在一个空格，且两个方格不完全相同的情况。**

如果只有一个空格，一定有两个非空格与它相邻，分别从两个非空格开始移动，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/g8wz0jrs.png)

我们发现，这两种移动方式实际上分别是除空格外数列绕方格的顺时针旋转与逆时针旋转。图中标红数据即为数列旋转一百八十度的结果。运用小学数学关于旋转的知识，不难想到：初始状态最后一行与最终状态的第一行可能是相反的（如上图 $2,3$ 和 $3,2$）那么最后一行与第一行一定是相反的吗？如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/5274g92y.png)

图中数据 $(5,0,3,2)$ 最后一行与初始状态 $(2,3,5,0)$ 第一行同为 $5,0$，但很明显，初始状态可以移动到最终状态。为什么？不要忘记，数列并不是作为一个整体在方格中旋转，其中可能有一个数字“掉队”，看看图一中的“5”，如果它向右走一格后将方格旋转一百八十度，便能得到最终状态。

当 a 的第二行与 b 的第一行相同的情况时，有两种情况：

1. a 的第一行与 b 的第二行相反。

2. a 的第一行与 b 的第二行相同。

第一种情况，这时如果 a 的第二行中有一个数字“掉队”，即 a 的第二行中存在 “0” 时，将第二行的非零数字移到空格位置，恰好是 b 旋转一百八十度后结果。我们只要在判断两行相同的基础上，再次判断该行中是否含有空格即可。第二种情况，两个方格上下颠倒，只要进行一次对（a 的第一行与 b 的第二行）的判断，一次对（a 的第二行与 b 的第一行）的判断，由于目前只含有一个空格，不在第一行就在第二行，不必考虑。同理得出函数：

```cpp
bool judge1(){
    if(a[1]==b[3]&&a[2]==b[4]){
        if(a[1]!=0&&a[2]!=0) return 1;
    }
    if(a[3]==b[1]&&a[4]==b[2]){
        if(a[3]!=0&&a[4]!=0) return 1;
    }
    if(a[1]==b[2]&&a[3]==b[4]){
        if(a[1]!=0&&a[3]!=0) return 1;
    }
    if(a[2]==b[1]&&a[4]==b[3]){
        if(a[2]!=0&&a[4]!=0) return 1;
    }
    return 0;
}
```
理解“掉队”情况后，再次观察图中标绿数据，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/p9fhmor7.png)

两个方格第一行是相同的，第二行的“2”却慢了一步。幸好“2”的前方是一个空格，它能够跟上队伍。我们发现，如果两个方格第一行相同，只有第二行存在空格时，才能移动到最终状态，由于目前只含有一个空格，换句话说，如果第一行相同且其中含有空格，一定不能移动到最终状态。同理得出函数：

```cpp
bool judge2(){
    if(a[1]==b[1]&&a[2]==b[2]){
    	if(a[1]==0||a[2]==0) return 1;
    }
    if(a[3]==b[3]&&a[4]==b[4]){ 
    	if(a[3]==0||a[4]==0) return 1;
    }
    if(a[1]==b[1]&&a[3]==b[3]){ 
    	if(a[1]==0||a[3]==0) return 1;
    }
    if(a[2]==b[2]&&a[4]==b[4]){
    	if(a[2]==0||a[4]==0) return 1;
    }
    return 0;
}
```

还没完，观察图中标蓝数据，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/leb86dd9.png)

方格顺时针旋转和逆时针旋转九十度分别得到图一、图二，很明显，图一可以通过旋转变为图二，假设 $(5,2,0,3)$ 为初始状态，$(3,0,2,5)$ 为最终状态，两个方格两组对角数字位置恰好是相反的。这时可以移动到最终状态。而在两个方格不完全相同且只含一个空格的情况下，如果一组对角数字位置相同，另一组对角数字位置一定相反。这时不能移动到最终状态。那么，当初始状态可以移动到最终状态时，每一组对角数字位置一定不同。得出函数：

```cpp
bool judge3(){
	if(a[1]==b[1]&&a[4]==b[4]||a[2]==b[2]&&a[3]==b[3])return 1;	
	return 0;
}
```

如果我们只是将上文的判断组合起来，试试这组数据：

![](https://cdn.luogu.com.cn/upload/image_hosting/zy2ibldt.png)

明显无法移动到最终状态，上文却并未提到这种情况，程序给出的答案是 "Yes"。观察两个方格，并没有找到规律。但仔细看看初始状态 $(0,2,5,3)$，不妨让 “2” 退到空格位置，初始状态就变成 $(2,0,5,3)$，与最终状态的第二列相同了。综合 judge1 函数，判断出无法移动到最终状态。

也就是说，第一次判断两个方格不满足以上条件时，不能直接得出正确的结论。初始状态中既然存在一个空格，就一定有两种情况：

1. 空格位置为 “2” 或 “3”时，“1”、“4” 两格数字可以移到空格位置。

2. 空格位置为 “1” 或 “4”时，“2”、“3” 两格数字可以移到空格位置。

读入数据后，记录空格个数，同时用变量 k 记录空格位置，判断哪两个位置的数字可以移至空格，接着判断以上条件是否成立，成立输出结束，不成立将数字移回原位置，移动另一个数字再次判断。**需要注意，移动后两个方格可能完全相同。** 这时一定能够移动到最终状态，所以需要判断前文的 same 函数不成立。得出函数：

```cpp
bool move(int x){
    swap(a[k],a[x]); 
    if((judge1()||judge2()||judge3())&&!same()) return 1;
    else swap(a[k],a[x]);
    return 0;
}
```

## Code
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a[5],b[5],num=0,k;
bool judge1(){
    if(a[1]==b[3]&&a[2]==b[4]){ //a的第一行与b的第二行相同 
        if(a[1]!=0&&a[2]!=0) return 1;
    }
    if(a[3]==b[1]&&a[4]==b[2]){ //a的第二行与b的第一行相同 
        if(a[3]!=0&&a[4]!=0) return 1;
    }
    if(a[1]==b[2]&&a[3]==b[4]){ //a的第一列与b的第二列相同
        if(a[1]!=0&&a[3]!=0) return 1;
    }
    if(a[2]==b[1]&&a[4]==b[3]){ //a的第二列与b的第一列相同 
        if(a[2]!=0&&a[4]!=0) return 1;
    }
    return 0;
}
bool judge2(){
    if(a[1]==b[1]&&a[2]==b[2]){ //a的第一行与b的第一行相同 
    	if(a[1]==0||a[2]==0) return 1;
    }
    if(a[3]==b[3]&&a[4]==b[4]){ //a的第二行与b的第二行相同 
    	if(a[3]==0||a[4]==0) return 1;
    }
    if(a[1]==b[1]&&a[3]==b[3]){ //a的第一列与b的第一列相同 
    	if(a[1]==0||a[3]==0) return 1;
    }
    if(a[2]==b[2]&&a[4]==b[4]){ //a的第二列与b的第二列相同 
    	if(a[2]==0||a[4]==0) return 1;
    }
    return 0;
}
bool judge3(){
    if(a[1]==b[1]&&a[4]==b[4]|| //a,b左上与右下相同 
       a[2]==b[2]&&a[3]==b[3]){ //a,b右上与左下相同 
         return 1;	
    }
    return 0;
}
bool same(){ //a,b四个格完全相同 
    if(a[1]==b[1]&&a[2]==b[2]&&a[3]==b[3]&&a[4]==b[4]) return 1;
	 return 0;
}
bool move(int x){
    swap(a[k],a[x]); //x格中数字移到空格位置 
    if((judge1()||judge2()||judge3())&&!same()) return 1;
    else swap(a[k],a[x]); //判断不成立，数字回到x格
    return 0;
}
int main(){
    scanf("%d %d %d %d",&a[1],&a[2],&a[3],&a[4]);
    scanf("%d %d %d %d",&b[1],&b[2],&b[3],&b[4]);
    for(int i=1;i<=4;i++){
    	if(a[i]==0){
    		num++; //记录空格个数 
    		k=i; //记录空格出现位置 
    	}
    }
    if(same()){ //四个格全部相同
        printf("Yes"); 
        return 0;
    }
    if(num==0){ //四个格全部不为空
        printf("No"); 
        return 0;
    }
    if(num>=2){ //空格个数两个及以上 
    	printf("Yes");
    	return 0;
    }
    //以下均为只存在一个空格的情况 
    if(judge1()||judge2()||judge3()){ //判断
    	printf("No");
    	return 0;
    }
    if(k==2||k==3){ //空格位置为2或3时 
	if(move(1)||move(4)){ //判断1,4格中数字移到空格位置时 
		printf("No");
    	return 0;
		}
	}
    if(k==1||k==4){ //空格位置为1或4时
	if(move(2)||move(3)){ //判断2,3格中数字移到空格位置时  
		printf("No");
    	return 0;
		} 
	}
    printf("Yes"); //全部不成立，结束 
    return 0;
}

```


---

## 作者：ZBAA_MKC (赞：7)

这是本次月赛的第一道题，也是我在洛谷月赛中 AC 的第一道题。赛后我翻看部分同学的记录，发现大部分都用的是暴力，那么我就来一篇深搜的题解。

我们搜索 $0$，也就是空格的位置，如果在某一分支搜索失败，即没有经过目标位置，我们就回溯去尝试其他分支。

但问题来了，如果出现了不能到达目标状态的情况，如果不做任何处理是必然会出现死递归的。在 $2\times2$ 的方阵里面，如果有解，移动步数必然不会太多，所以我采用了"如果 $1000$ 步以内找不到就算无解"的方式来判断无法到达的情况。

下面是代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int sta[4][4];
int target[4][4];
bool vis[4][4];
const int dx[4] = {1, -1, 0, 0}; //方向数组
const int dy[4] = {0, 0, 1, -1};

void dfs(int x, int y, int step)
{
	bool f = true;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (sta[i][j] != target[i][j]) //判断是否已达目标状态
			{
				f = false;
				break;
			}
		}
	}
	if (step == 1000) //1000步以内搜不到就算无解
	{
		puts("No");
		exit(0);
	}
	if (f) //如果达到目标状态就输出Yes
	{
		puts("Yes");
		exit(0);
	}
	for (int i = 0; i < 4; i++)
	{
		if (x + dx[i] < 2 && x + dx[i] >= 0 && y + dy[i] < 2 && y + dy[i] >= 0 && !vis[x + dx[i]][y + dy[i]]) //判越界
		{
			swap(sta[x + dx[i]][y + dy[i]], sta[x][y]); //交换
			vis[x + dx[i]][y + dy[i]] = true;
			dfs(x + dx[i], y + dy[i], step + 1); //继续搜索
			vis[x + dx[i]][y + dy[i]] = false; //回溯
			swap(sta[x + dx[i]][y + dy[i]], sta[x][y]);
			step--;
		}
	}
}

int main()
{
	int x, y;
	bool f = false;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			cin >> sta[i][j]; //输入
			if (sta[i][j] == 0) //标记空格
			{
				x = i;
				y = j;
				f = true;
			}
		}
	}
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++) //还是输入
		{
			cin >> target[i][j];
		}
	}
	if (f)
	{
		dfs(x, y, 0); //有空格就开始搜索
	}
	for (int i = 0; i < 2; i++) //没有空格直接判断两个状态是否一样
	{
		for (int j = 0; j < 2; j++)
		{
			if (sta[i][j] != target[i][j]) //不一样就输出No
			{
				puts("No");
				return 0;
			}
		}
	}
	puts("Yes"); //一样就输出Yes
	return 0;
} 
```

---

## 作者：Graphcity (赞：5)

### 思路

首先，可以知道这道题分两种情况：

- 当没有空格时，如果两个状态相同输出 `Yes`，不同输出 `No` 即可。
- 当存在空格时，我们就可以考虑移动初始状态下的格子，看是否能够变为最终状态了。但由于这道题的搜索有点儿复杂，我们就可以用另外一种简单暴力的方法 —— **随机移动**。用随机函数 `rand()` 选取两个相邻的格子，设坐标分别为 $(a,c)$ 和 $(b,d)$，如果其中至少有一个空格子，那就将它们的数字交换。一直这样操作 100 次（如果不放心还可以更多），直到两个状态相同则输出 `Yes` 之后停止，否则输出 `No` 即可。由于总状态数非常少，随机移动能够得到正解的概率是非常高的。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int a[3][3],b[3][3],vis;
int c[3][3],d[3][3],e[3][3];
int tim=0; // tim:记录操作次数

inline void dfs()
{
	while(1)
	{
		int a1=rand()%2+1,b1=rand()%2+1; // 随机选取坐标
		int c1=rand()%2+1,d1=rand()%2+1;
		if(a1!=b1 && c1!=d1) continue;
		if(a[a1][c1]!=0 && a[b1][d1]!=0) continue;
		swap(a[a1][c1],a[b1][d1]); tim++;
		int flag=1;
		for(int i=1;i<=2;++i) // 比较是否相同
			for(int j=1;j<=2;++j)
				if(a[i][j]!=b[i][j]) flag=0;
		if(flag) {printf("Yes"); exit(0);}
		if(tim>100) break;
	}
	printf("No");
}

int main()
{
	for(int i=1;i<=2;++i)
		for(int j=1;j<=2;++j)
			{
				cin>>a[i][j];
				if(a[i][j]==0) vis=1;
			}
	for(int i=1;i<=2;++i)
		for(int j=1;j<=2;++j)
			cin>>b[i][j];
	if(!vis) // 没有空格
	{
		for(int i=1;i<=2;++i)
			for(int j=1;j<=2;++j)
				if(a[i][j]!=b[i][j]) {printf("No"); return 0;}
		printf("Yes"); return 0;
	}
	dfs();
	return 0;
}
```



---

## 作者：红尘仙 (赞：5)

### Part 1 
当整个 $2 \times 2$ 的矩阵没有空格的时候，那么这个时候也就意味着这个矩阵我不能够再动了，这时候只需要判断一下初始矩阵和结果矩阵在一开始是否相等即可。

### Part 2 
如果这个 $2 \times 2$ 的矩阵中有空格，那么也就说明可以移动。

我们看一下这个题目给出的图片

![](https://cdn.luogu.com.cn/upload/image_hosting/y2dnr4ss.png)

因为这是一个 $2 \times 2$ 的矩阵，所以，这个空格的转换方向其实是有顺序的，就像这个图片一样，只能够逆时针或者顺时针去置换一下整数。

那么也就是说：
   如果我把初始矩阵的非零整数按照顺时针的方向取出来，我也将结果矩阵的非零整数按照顺时针的方向取出来，那么把初始矩阵看成一个环（因为是顺时针旋转嘛），就可以清楚这个环在某一个特定的旋转后，只有和结果矩阵取出的序列相同，才可以说明初始矩阵可以转化为结果矩阵。

我们来感性理解一下上面的一个小小的结论 ： 

如果在某一个右下角有一个空格，那么它面临着两种选择 ： 
  + 1. 和它左边的数字交换。
  + 2. 和它上面的数字交换。

我们在这里以第 1 种情况为例说明。 
这个空格和它上面的数字交换了，那么空格也就来到了右上角，我们认为它很聪明，所以它不会回去，因为回去就显得它很笨。那就和它左面交换……

依次类推，我们发现，这个其实就是在将非零数字组成的序列逆时针旋转，（第一个来到最后一个依次类推）。

那么第 2 种情况呢，同理，是顺时针旋转的。 

### Part 3

那么如果是 2 个空格的情况 ~~(多谢管理员大大的提醒)~~

我们假设有两个空格，那么即有 6 种情况 ，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/x89v14cp.png)

然后我们发现根据只有一种空格的情况可以知道，其实 1,3,5,6 是一样的，2,4 是一样的，无非就是换了换顺序，更准确的说，无非就是来了一个顺或逆时针旋转罢了。 

那么这个转化的时候，还是一样的道理，我们假设以 1 号为例

右下角的数字可以向上去置换，接着向左置换，与此同时，这个左下角的数字可以向右置换，这样就形成了逆时针的转化顺序。 

同理，其他情况也是一样的。 

### Part 4 
那有 3 个空格的时候呢？ 
显然这个数字可以随便乱走了，到哪里都行，只要两个矩阵的数字相等就好。

那我们之前的规律成立吗？ 
显然是成立的。一个非零数字构成环去和另一个非零数字匹配。


### 具体处理 ： 
因为顺时针和逆时针的操作会使我们很厌恶，但是都是将初始矩阵构成的序列排成环然后循环，我们就直接断环成链，将初始矩阵的序列 $\times$ 2 放在后面，和结果矩阵去配对。

### Code

```
//
/*
Author : Zmonarch
Knowledge :
*/
#include <bits/stdc++.h>
#define inf 2147483647
#define qwq register
#define qaq inline
#define int long long
using namespace std ;
const int kmaxn = 1e6 + 10 ;
qaq int read() {
	int x = 0 , f = 1 ; char ch = getchar() ;
	while(!isdigit(ch)) {if(ch == '-') f = - 1 ; ch = getchar() ;}
	while( isdigit(ch)) {x = x * 10 + ch - '0' ; ch = getchar() ;}
	return x * f ;
}
bool f ; 
int a[3][3] , b[3][3] ; 
bool SAME() {
	for(qwq int i = 1 ; i <= 2 ; i++) 
	 for(qwq int j = 1 ; j <= 2 ; j++) 
	  if(a[i][j] != b[i][j]) return false ;
	return true ; 
}
signed main() {
	for(qwq int i = 1 ; i <= 2 ; i++)
	{
		for(qwq int j = 1 ; j <= 2 ; j++)
	  	{
	  		a[i][j] = read() ; 
	  		if(a[i][j] == 0) f = true ; 
		}
	} 
	for(qwq int i = 1 ; i <= 2 ; i++) 
	 for(qwq int j = 1 ; j <= 2 ; j++) 
	  b[i][j] = read() ; 
	if(SAME()) {printf("Yes\n") ; return 0 ;} 
	if(!f) {printf("No\n") ; return 0 ;} 
	int s1[20] , s2[20] , tot1 = 0 , tot2 = 0 ;  
	for(qwq int i = 1 ; i <= 2 ; i++) 
	 for(qwq int j = 1 ; j <= 2 ; j++) 
	  if(i & 1) 
	  {
	  	if(a[i][j]) s1[++tot1] = a[i][j] ; 
	  	if(b[i][j]) s2[++tot2] = b[i][j] ;
	  }
	  else 
	  {
	  	if(a[i][2 - j + 1]) s1[++tot1] = a[i][2 - j + 1] ; 
	  	if(b[i][2 - j + 1]) s2[++tot2] = b[i][2 - j + 1] ; 
	  }
	if(tot1 != tot2) {printf("No\n") ; return 0 ;}
	for(qwq int i = 1 ; i <= tot1 ; i++) s1[i + tot1] = s1[i] , s2[i + tot2] = s2[i] ; 	
	int k = 1 , sum = 0 ; 
	for(qwq int i = 1 ; i <= tot1 * 2 ; i++)
	{
		if(s1[i] == s2[k]) 
		{
			sum++ ; k++ ; 
			if(sum == tot1) {printf("Yes\n") ; return 0; }
		}
		else sum = 0; 
	}
	printf("No\n") ; 
	return 0 ;
}
```

---

## 作者：斜揽残箫 (赞：4)

## Description

给定初始网格和最终网格，问是否初始网格能经过有限次变换后成为最终网格。

感觉这个题不止红，并且数据太水了，至少加个多测吧。

## Solution

这个题目要分几种情况来讨论 ：

+ 所有空格都填满了，空格子的个数为 $0$，若发现初始状态和最终状态一样，就输出 $\text{Yes}$，否则输出 $\text{No}$，因为都填满了就不可能再进行变换了。
+ 当空格的个数不为 $1$ 时，我们发现，无论怎么移动都可以使得初始状态变为最终状态，这种情况自己手膜一下即可，显然成立。
+ 当空格的个数为 $1$ 时，这就是重点了，也是为什么很多人都会在第 $9$ 个点 $\color{red}{\text{Wrong Answer}}$ 的原因。

下面来看两种情况，左边是初始状态，右边是最终状态。

第一张我们称为 $A$，第二张为 $B$。

![](https://pic.imgdb.cn/item/60f2c08f5132923bf8490a45.jpg)

![](https://pic.imgdb.cn/item/60f2bf085132923bf841bfc1.jpg)

首先来看 $A$，这个是可以由初始状态变为最终状态的，一种移动方案为 $3 \to 0,1 \to 3,2 \to 1$，这样就变为了最终状态。

再来看 $B$，这个无论怎么移动都无法变为最终状态。

经过多次尝试，我们可以发现一个重要的性质，无论怎么移动，数字的顺序是不变的，初始状态能否达到最终状态只需要判断他们从 $0$ 开始顺时针旋转是否是循环同构串相同即可。

判断的话可以写 dfs 或者直接暴力判断，我写的暴力判断，可能有亿点长。

## Code
```
#include <cstdio>
#include <cmath>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;
const int Maxk = 10; 
int a[Maxk][Maxk],b[Maxk][Maxk];
int num,ex,ey;//ex ，ey 记录最终状态的 0 的坐标 
int cnt,sum,t;
int sx,sy;//sx ,sy 记录初始状态 0 的坐标 
inline int read()
{
	int s = 0, f = 0;char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
	return f ? -s : s;
}
signed main()
{
  for(int i = 1;i <= 2;i ++) 
    for(int j = 1;j <= 2;j ++)
      a[i][j] = read();
  for(int i = 1;i <= 2;i ++)
    for(int j = 1;j <= 2;j ++) 
      b[i][j] = read();
  for(int i = 1;i <= 2;i ++) {
    for(int j = 1;j <= 2;j ++) {
      if(a[i][j] == b[i][j]) sum ++;//如果相同就 ++ 
      if(a[i][j] == 0) cnt ++,sx = i,sy = j;//判断 0 的个数 
      if(b[i][j] == 0) ex = i,ey = j;
    }
  }
  if(cnt == 0 && sum != 4) {puts("No");return 0;}//没有 0 且不与最终状态相同 
  if(sum == 4 || cnt != 1 || sum == 3) {puts("Yes");return 0;}
  if(sx == 1 && sy == 1) num = a[1][2] * 100 + a[2][2] * 10 + a[2][1];//大概是因为不想写 dfs  
  if(sx == 1 && sy == 2) num = a[2][2] * 100 + a[2][1] * 10 + a[1][1];
  if(sx == 2 && sy == 2) num = a[2][1] * 100 + a[1][1] * 10 + a[1][2];
  if(sx == 2 && sy == 1) num = a[1][1] * 100 + a[1][2] * 10 + a[2][2];
  if(ex == 1 && ey == 1) t = b[1][2] * 100 + b[2][2] * 10 + b[2][1];
  if(ex == 1 && ey == 2) t = b[2][2] * 100 + b[2][1] * 10 + b[1][1];
  if(ex == 2 && ey == 2) t = b[2][1] * 100 + b[1][1] * 10 + b[1][2];
  if(ex == 2 && ey == 1) t = b[1][1] * 100 + b[1][2] * 10 + b[2][2];//用来判断顺序，顺时针旋转 
  if(num == t) {puts("Yes");return 0;}
  int C = num % 10;num /= 10;
  int B = num % 10;num /= 10;
  int A = num % 10;num /= 10;
  int F = t % 10;t /= 10;
  int E = t % 10;t /= 10;
  int D = t % 10;t /= 10;//拆位，判断循环同构。 
  if((A == F && B == D && C == E) || (C == D && A == E && B == F)) puts("Yes");
  else puts("No");
  return 0; 
}
```



---

## 作者：小杨小小杨 (赞：4)

## 题意
就是一个二行二列的华容道问题嘛。
## 思路
做这种题，千万别心急，不能一口吃成大胖子。  
做这种题，我们要一点一点拿分。   
首先要先拿四十分。   
题目说了，有四十分，不存在空格。那么不存在空格，就代表没法移动，没法改变当前状态，所以直接判断是否一开始就相等，不相等就不成立，相等就成立。   
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[11][11],b[11][11];
int main(){
	scanf("%d%d%d%d",&a[1][1],&a[1][2],&a[2][1],&a[2][2]);
	scanf("%d%d%d%d",&b[1][1],&b[1][2],&b[2][1],&b[2][2]);//读入两个矩阵
	if (a[1][1]!=0&&a[1][2]!=0&&a[2][1]!=0&&a[2][2]!=0){//如果没有空格
		if (a[1][1]==b[1][1]&&a[2][1]==b[2][1]&&a[1][2]==b[1][2]&&a[2][2]==b[2][2])//判断是否原来就相等
			printf("Yes\n");
		else printf("No\n");//输出
		return 0;
	}
	return 0;
}
```
[记录](https://www.luogu.com.cn/record/53083161)
## 思路
接着就是满分目标了。   
如果有一个或多个空格，那么就对于每一个空格进行搜索，反正就二行二列，暴力搜索每一种情况。   
对于搜索的位置转换，有以下几种可能：  
1、那个空格在一行一列：   
![](https://cdn.luogu.com.cn/upload/image_hosting/5zckr3xv.png?x-oss-process=image/resize,m_lfit,h_170,w_225)  
那么就可以从一行二列和二行一列转换。  
2、那个空格在一行二列：     
![](https://cdn.luogu.com.cn/upload/image_hosting/zby5a6g1.png?x-oss-process=image/resize,m_lfit,h_170,w_225)  
那么就可以从一行一列和二行二列转换。  
3、那个空格在二行一列：   
![](https://cdn.luogu.com.cn/upload/image_hosting/5m31qfdv.png?x-oss-process=image/resize,m_lfit,h_170,w_225)  
那么就可以从一行一列和二行二列转换。  
4、那个空格在二行二列：   
图略。  
那么就可以从一行二列和二行一列转换。  
最后暴搜加上判断即可。  
记得还原哦。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[11][11],b[11][11],c[11][11],flag,f[11][11];
bool pd(){
	if (c[1][1]==b[1][1]&&c[2][1]==b[2][1]&&c[1][2]==b[1][2]&&c[2][2]==b[2][2])
	return true;
	return false;
}
void sc(int x,int y){
	if (pd()){flag=true;return;}
	if (flag) return;
	if (f[x][y]) return;
	f[x][y]=1;
	if (x==1&&y==1){//那个空格在一行一列
		c[1][1]=c[2][1];c[2][1]=0;sc(2,1);c[2][1]=c[1][1];c[1][1]=0;
		c[1][1]=c[1][2];c[1][2]=0;sc(1,2);c[1][2]=c[1][1];c[1][1]=0;
	}	
	if (x==2&&y==1){//那个空格在二行一列
		c[2][1]=c[1][1];c[1][1]=0;sc(1,1);c[1][1]=c[2][1];c[2][1]=0;
		c[2][1]=c[2][2];c[2][2]=0;sc(2,2);c[2][2]=c[2][1];c[2][1]=0;
	}	
	if (x==1&&y==2){//那个空格在一行二列
		c[1][2]=c[1][1];c[1][1]=0;sc(1,1);c[1][1]=c[1][2];c[1][2]=0;
		c[1][2]=c[2][2];c[2][2]=0;sc(2,2);c[2][2]=c[1][2];c[1][2]=0;
	}	
	if (x==2&&y==2){//那个空格在二行二列
		c[2][2]=c[1][2];c[1][2]=0;sc(1,2);c[1][2]=c[2][2];c[1][2]=0;
		c[2][2]=c[2][1];c[2][1]=0;sc(2,1);c[2][1]=c[2][2];c[2][1]=0;
	}
}
int main(){
	scanf("%d%d%d%d",&a[1][1],&a[1][2],&a[2][1],&a[2][2]);
	scanf("%d%d%d%d",&b[1][1],&b[1][2],&b[2][1],&b[2][2]);//读入两个矩阵
	if (a[1][1]!=0&&a[1][2]!=0&&a[2][1]!=0&&a[2][2]!=0){//如果没有空格
		if (a[1][1]==b[1][1]&&a[2][1]==b[2][1]&&a[1][2]==b[1][2]&&a[2][2]==b[2][2])//判断是否原来就相等
			printf("Yes\n");
		else printf("No\n");//输出
		return 0;
	}
	c[1][1]=a[1][1];c[1][2]=a[1][2];c[2][1]=a[2][1];c[2][2]=a[2][2];
	memset(f,0,sizeof(f));
	if (!c[1][1]) sc(1,1);//那个空格在一行一列
	c[1][1]=a[1][1];c[1][2]=a[1][2];c[2][1]=a[2][1];c[2][2]=a[2][2];
	memset(f,0,sizeof(f));
	if (!c[2][2]) sc(2,2);//那个空格在一行二列
	c[1][1]=a[1][1];c[1][2]=a[1][2];c[2][1]=a[2][1];c[2][2]=a[2][2];
	memset(f,0,sizeof(f));
	if (!c[2][1]) sc(2,1);//那个空格在二行一列
	c[1][1]=a[1][1];c[1][2]=a[1][2];c[2][1]=a[2][1];c[2][2]=a[2][2];
	memset(f,0,sizeof(f));
	if (!c[1][2]) sc(1,2);//那个空格在二行二列
	if (flag) printf("Yes\n");
	else printf("No\n");
	return 0;
}
```
[记录](https://www.luogu.com.cn/record/53086800)


---

## 作者：_caiji_ (赞：4)

首先我们先算一下网格最多可能有多少种状态，很显然是 $5^4=625$，完全可以暴力搜索。

那怎么实现呢？可以使用 bfs，以初始状态开始，每次找空格子，将空格子四周的数字移过来，完成状态的扩展。

但这样子极有可能重复搜索同一种状态，我们需要去重。~~经测试使用 `std::map` 会 MLE/TLE，所以~~我们使用 hash。观察到题面有一句话：

>且它们就是**前 $\bold{k}$ 个不同的正整数**。

换句话说，数字全都是一位数，可以把四个数字压缩成一个四位数，这样就不会 MLE/TLE 了。

这里给出我的代码实现：
```cpp
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;
const int dx[]={0,-1,0,0,1},
          dy[]={0,0,-1,1,0};
int n=2;
struct node{
    int a[3][3];
    friend istream& operator>>(istream &fin,node &e){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                fin>>e.a[i][j];
            }
        }
        return fin;
    }
    operator int(){
        return a[1][1]*1
              +a[1][2]*10
              +a[2][1]*100
              +a[2][2]*1000;
    }
};
queue<node> q;
bool vis[10010];
node begin,end;
bool bfs(){
    vis[begin]=1;
    q.push(begin);
    while(!q.empty()){
        node now=q.front();q.pop();
        if(now==end) return 1;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(now.a[i][j]==0){
                    for(int k=1;k<=4;k++){
                        int x=i+dx[k],y=j+dy[k];
                        if(1<=x&&x<=n&&1<=y&&y<=n&&now.a[x][y]!=0){
                            node pus=now;
                            swap(pus.a[i][j],pus.a[x][y]);
                            if(!vis[pus]){
                                vis[pus]=1;
                                q.push(pus);
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}
int main(){
    cin>>begin>>end;
    cout<<(bfs()?"Yes":"No")<<endl;
    return 0;
}
```


---

