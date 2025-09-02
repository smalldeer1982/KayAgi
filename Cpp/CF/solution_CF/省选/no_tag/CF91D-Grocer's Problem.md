# Grocer's Problem

## 题目描述

Yesterday was a fair in a supermarket's grocery section. There were $ n $ jars with spices on the fair. Before the event the jars were numbered from $ 1 $ to $ n $ from the left to the right. After the event the jars were moved and the grocer had to sort them by the increasing of the numbers.

The grocer has a special machine at his disposal. The machine can take any $ 5 $ or less jars and rearrange them in the way the grocer wants. Note that the jars do not have to stand consecutively. For example, from the permutation $ 2 $ , $ 6 $ , $ 5 $ , $ 4 $ , $ 3 $ , $ 1 $ one can get permutation $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ , $ 5 $ , $ 6 $ , if pick the jars on the positions $ 1 $ , $ 2 $ , $ 3 $ , $ 5 $ and $ 6 $ .

Which minimum number of such operations is needed to arrange all the jars in the order of their numbers' increasing?

## 说明/提示

Let's consider the first sample. The jars can be sorted within two actions.

During the first action we take the jars from positions $ 1 $ , $ 3 $ , $ 6 $ and $ 4 $ and put them so that the jar that used to occupy the position $ 1 $ will occupy the position $ 3 $ after the operation is completed. The jar from position $ 3 $ will end up in position $ 6 $ , the jar from position $ 6 $ will end up in position $ 4 $ and the jar from position $ 4 $ will end up in position $ 1 $ .

After the first action the order will look like that: $ 1 $ , $ 5 $ , $ 3 $ , $ 4 $ , $ 2 $ , $ 6 $ .

During the second operation the jars in positions $ 2 $ and $ 5 $ will change places.

## 样例 #1

### 输入

```
6
3 5 6 1 2 4
```

### 输出

```
2
4
1 3 6 4 
3 6 4 1 
2
2 5 
5 2 
```

## 样例 #2

### 输入

```
14
9 13 11 3 10 7 12 14 1 5 4 6 8 2
```

### 输出

```
3
4
2 13 8 14 
13 8 14 2 
5
6 7 12 5 10 
7 12 6 10 5 
5
3 11 4 1 9 
11 4 3 9 1 
```

# 题解

## 作者：Quidrem (赞：7)

这题我肝了快 $2$ 天（我太菜了），你难以想象我做出来的时候有多激动...我已经在各大网站搜索过，这是本题的第一篇公开题解（除了原比赛赛后讲解）！

### 题意

给一个长为 $n$ 的序列排序。每次操作最多选取 $5$ 个数改变位置。输出操作次数最少的方案。

本题翻译没有提到一个很重要的点：数列是 $1$ 的 $n$ 一种任意的排列。

### 思路

我们一步步思考本题解法。

首先要给数列从小到大排序，而数列所有的数都是固定的：也就是 $1$ 到 $n$ 每个数出现且仅一次，那么可以得到排序后的序列也必然是 $1,2,\cdots,n$。可见原序列在 $i$ 位置的数排序完成后一定会到达 $a_i$ 位置。那么我们用数组 $to$ 来代替 $a$ 表示每个位置最终需要到达的位置。

而 $to$ 数组记录的即为不限制每次操作多少个数的方案。

那么我们接着思考如何每次使用 $5$ 个数来排序。

当有 $2$ 个数需要排序时，第 $1$ 个数和第 $2$ 个数必然需要交换位置。

增加到 $3$ 个数。如“`2 3 1`”这个序列，操作结果为 $1\to 2$，$2\to 3$，$3\to 1$。我们发现三个数似乎形成了一个类似图论中环。稍加推导可以发现（对于大佬来说可能一眼就能看出来），一切需要改变位置的数一定会形成一个或多个环。

想到这里，我们可以先把这些环记录下来。

当环内的单元在 $5$ 以内，固然可以一次排序成功，且个数为 $2$ 时可以和另一 $2$ 或 $3$ 个单元的环在一次操作中排序成功。但是单位个数超过 $5$ 时该怎么办呢？

先手造一个十分简单的数据：

```
6
2 3 4 5 6 1
```

手写出正确的操作方式：

```
2
5
1 2 3 4 5
2 3 4 5 1
2
1 6
6 1
```

可见，我们使用了一次操作使 $4$ 个数排序成功了，而将第五个数暂时存到了第一个数的位置。在下一次操作时将第一个数换到上一次操作的最后一个数所要到达的位置上，而完成排序。于是我们得到：当环内单元个数大于 $5$ 时，每次操作能排序成功 $4$ 个数。

然而如何使得操作次数最少呢？我原本以为从第 $1$ 个数到最后一个数寻找未排序成功的数然后同步找环和输出就行了，却忽略了一个点。当你把一个环拆成两次排序时，每次操作都浪费了一个排列的数（例如上面的例子，$6$ 个数调换了 $7$ 次某一数字的位置）。

整理可以得到的更多结论。

1. 由于排列 $4$ 个数时仅剩下了一个空间，无法再起到任何排序的功能。

2. 环内单位超过 $5$ 时（由前一个结论综合可得大于等于 $4$ 个单位时），必定需要使用一个单独的操作来细化这个环。所以遇到这种情况时不妨直接将除了 $L$ 的操作直接保存，然后记录 $L$ 的情况。定义 $L$ 为经过数次操作后，剩下的环内单元数小于等于 $3$ 的情况。

3. $2$ 个单元的环尽量先和 $3$ 个单元的环拼在一次操作，这样不会浪费任何操作次数。

4. 仅剩 $3$ 个单元的环时，通过一次操作将一个环排序好，另一个环排好一个数，留下一个两个单元的环情况。

5. 因为仅剩 $3$ 个单元说明已经将 $2$ 个单元的排序完，或者本生没有 $2$ 个单元的环，所以可以将小于等于 $3$ 个单元的环按照单元数从小到大排序，然后分别匹配操作即可。

最后定义一个数组 $ans$ 和一个数 $sum$ 记录操作方式和总操作次数，按题意要求输出，本题大功告成。有很多的细节需要考虑，详见下面的 $\text{AC}$ 代码。

### 代码

```
#include<bits/stdc++.h>
using namespace std;
queue<int>q;//记录需要排序的数
int n,to[100010];
void read(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&to[i]);
	}
	for(int i=1;i<=n;i++){
		if(to[i]==i)continue;//已经在最终位置的数无需移动
		q.push(i);
	}
}
int sum,ans[100010][3][6],l[100010];//l记录每次操作单元总数（一般是4和5，不排除仅剩下的2单元或3单元环）
bool vis[100010];//记录已经记录到环中的数的位置
struct node{
	int k[3][4],r;//r记录环单元数
	bool operator<(const node &a)const{
		return r<a.r;
	}
}wk[100010];//wk储存单元数小于等于3的环
int tot;
void work(){
	int fr,id,st;
	int u[3][100010];//u暂时保存初始环的操作
    //u[1][x]为环内第x个数的位置
    //u[2][x]为环内第x个数排序后到达的位置
    //wk和ans记录方式相同
	while(!q.empty()){
		fr=q.front(),id=fr;
		q.pop();st=0;//st记录初始环单元数
		if(vis[fr])continue;
		do{
			st++;
			u[1][st]=id,u[2][st]=to[id];
			vis[to[id]]=1,id=to[id];
		}while(id!=fr);//循环搜索环内单元的位置和要到达的位置知道回到环内第一个单元
		int ck=0;//ck记录已经操作到环的单元数
		while(st-ck>=4){代表重复操作到环内单元满足wk数组要求
			sum++;
			if(st-ck<=5){//5以内直接照常存
				l[sum]=st-ck;
				for(int i=1;ck<=st;i++){
					ans[sum][1][i]=u[1][++ck];
					ans[sum][2][i]=u[2][ck];
				}
			}else{//单元数多于5仅照搬前4个单元，最后1个位置特殊赋值
				l[sum]=5;
				for(int i=1;i<=4;i++){
					ans[sum][1][i]=u[1][++ck];
					ans[sum][2][i]=u[2][ck];
				}
				ans[sum][1][5]=u[1][ck+1],ans[sum][2][5]=u[2][st];//原环的第5个单元放到第1个单元的位置
				u[1][ck+1]=ans[sum][1][1];//然后将环的第5个单元位置改为环内第1个单元的位置（下一次从第5个单元开始操作）
			}
		}
		if(st<=ck)continue;//特判环内单元个数小于1时不再对wk进行操作
		wk[++tot].r=st-ck;//往wk中存单元数小于等于3的环
		for(int i=1;i<=wk[tot].r;i++){
			wk[tot].k[1][i]=u[1][++ck];
			wk[tot].k[2][i]=u[2][ck];
		}
	}
}
void spc(){//拼接单元数小于等于3的环 
	sort(wk+1,wk+tot+1);//先按照单位数从小到大排序
	int h=1,t=tot;//h=head，代表从小开始拼接到的位置，t=tail，代表从大开始拼接到的位置
    //下面懒得写“单元”两个字了
	while(h<=t){
		sum++;
		if(h==t){//仅剩1个环了
			l[sum]=wk[h].r;
			for(int i=1;i<=wk[h].r;i++){
				ans[sum][1][i]=wk[h].k[1][i];
				ans[sum][2][i]=wk[h].k[2][i];
			}
			break;
		}else if(wk[h].r+wk[t].r<=5){//2和3拼或2和2拼（当2和2拼时代表3的已经拼完了）
			l[sum]=wk[h].r+wk[t].r;
			for(int i=1;i<=wk[h].r;i++){
				ans[sum][1][i]=wk[h].k[1][i];
				ans[sum][2][i]=wk[h].k[2][i];
			}
			for(int i=1;i<=wk[t].r;i++){
				ans[sum][1][wk[h].r+i]=wk[t].k[1][i];
				ans[sum][2][wk[h].r+i]=wk[t].k[2][i];
			}
			h++,t--;//拼从小到大的下一个和从大到小的下一个
		}else{
			l[sum]=5;
			for(int i=1;i<=wk[h].r;i++){
				ans[sum][1][i]=wk[h].k[1][i];
				ans[sum][2][i]=wk[h].k[2][i];
			}//特殊赋值，类似于对于初始环的操作
			ans[sum][1][wk[h].r+1]=wk[t].k[1][1];
			ans[sum][2][wk[h].r+1]=wk[t].k[2][1];
			ans[sum][1][wk[h].r+2]=wk[t].k[1][2];
			ans[sum][2][wk[h].r+2]=wk[t].k[1][1];
			wk[h].r=2;
			wk[h].k[1][1]=wk[t].k[1][1];
			wk[h].k[2][1]=wk[t].k[2][2];
			wk[h].k[1][2]=wk[t].k[1][3];
			wk[h].k[2][2]=wk[t].k[2][3];
			t--;//因为将剩下的2存在了h的位置，所以仅从大到小的找下一个
		}
	}
}
void write(){//输出 
	printf("%d\n",sum);
	for(int i=1;i<=sum;i++){
		if(l[i]<=0)continue;
		printf("%d\n",l[i]);
		for(int j=1;j<l[i];j++){
			printf("%d ",ans[i][1][j]);
		}
		printf("%d\n",ans[i][1][l[i]]);
		for(int j=1;j<l[i];j++){
			printf("%d ",ans[i][2][j]);
		}
		printf("%d",ans[i][2][l[i]]);
		if(i<sum)printf("\n");//原来以为CF评测不会忽略行末空格和文末换行（调了2天，什么玄学东西我都试过）
	}
}
int main(){
	read();//分步进行，好找错误的点
	work();
	spc();
	write();
	return 0;
}
```

---

