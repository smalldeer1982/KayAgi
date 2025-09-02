# Toda 2

## 题目描述

A group of $ n $ friends enjoys playing popular video game Toda 2. There is a rating system describing skill level of each player, initially the rating of the $ i $ -th friend is $ r_{i} $ .

The friends decided to take part in the championship as a team. But they should have equal ratings to be allowed to compose a single team consisting of all $ n $ friends. So the friends are faced with the problem: how to make all their ratings equal.

One way to change ratings is to willingly lose in some matches. Friends can form a party consisting of two to five (but not more than $ n $ ) friends and play a match in the game. When the party loses, the rating of each of its members decreases by $ 1 $ . A rating can't become negative, so $ r_{i}=0 $ doesn't change after losing.

The friends can take part in multiple matches, each time making a party from any subset of friends (but remember about constraints on party size: from $ 2 $ to $ 5 $ members).

The friends want to make their ratings equal but as high as possible.

Help the friends develop a strategy of losing the matches so that all their ratings become equal and the resulting rating is maximum possible.

## 样例 #1

### 输入

```
5
4 5 1 7 4
```

### 输出

```
1
8
01010
00011
01010
10010
00011
11000
00011
11000
```

## 样例 #2

### 输入

```
2
1 2
```

### 输出

```
0
2
11
11
```

## 样例 #3

### 输入

```
3
1 1 1
```

### 输出

```
1
0
```

# 题解

## 作者：liwenxi114514 (赞：1)

### 题意：
每次操作可以将一个长度为 $2$ 到 $5$ 的区间中的数都减一，问如何操作才能使序列中的所有数字都相同时的这个数最大（不要求次数最少，但要在 $10^{4}$ 以内）。

### 思路：
贪心。容易发现，对当前序列最大的数进行操作一定是最优的。又由于区间长度只有 $2$ 到 $5$，所以可以将 $4$ 和 $5$ 转化为 $2+2$ 和 $2+3$，考虑何时是 $2$，何时是 $3$。容易发现，当当前序列最大值的个数为偶数的时候，用 $2$ 一定是最优的，否则用 $3$。那如何处理最大的数以及其个数呢？优先队列（大根堆）。以下是 `AC` 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[105];
bool ans[10005][105];
priority_queue<pair<int,int> > q;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		q.push({a[i],i});//记录数值与位置，记录位置是为了统计操作
	}
	int sum=1;//操作次数
	while(1){
		pair<int,int> x=q.top();
		q.pop();
		pair<int,int> y=q.top();
		q.pop();
		if(q.empty()){
			if(x.first==y.first){
				cout<<x.first<<"\n";
				break;
			}
		}
		if(x.first==y.first){
			queue<pair<int,int> > q1;//记录弹出的值
			bool flag=0;
			int sss=2;//最大数个数
			while(!q.empty()){
				pair<int,int> z=q.top();
				q.pop();
				q1.push(z);
				if(z.first!=x.first){
					flag=1;
					break;
				}
				sss++;
			}
			if(!flag){//所有数都相同
				cout<<x.first<<"\n";//输出答案
				break;
			}
			sss=sss%2;//由于最后会加入两个数，所以目前只需要加sss%2个数
			while(!q1.empty()){//将弹出的值加回来
				if(q1.front().first==x.first&&sss>0){//与最大值相同
					q.push({max(q1.front().first-1,0ll),q1.front().second});
					ans[sum][q1.front().second]=1;
				}else{
					q.push({q1.front().first,q1.front().second});
				}
				q1.pop();
				sss--;
			}
		}
		ans[sum][x.second]=ans[sum][y.second]=1;//统计答案
		sum++;
		q.push({max(x.first-1,0ll),x.second});
		q.push({max(y.first-1,0ll),y.second});
	}
	cout<<sum-1<<"\n";
	for(int i=1;i<sum;i++){
		for(int j=1;j<=n;j++){
			cout<<ans[i][j];
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：Erica_N_Contina (赞：1)

## 大意

有 $n$ 个数字，每一次可以选择 $2\sim 5$ 个数字让它们 $-1$，求将所有数字变成同一个值且尽可能让这个值大的方案。

## 思路

很显然本题的 $n,r$ 都不太大，我们可以考虑使用贪心的策略进行模拟。

其次我们发现 $2,3,4,5$ 四种情况不太好讨论，并且我们不要求最小操作次数，只要求结果最大。那么我们可以把 $4,5$ 分成 $2+2,2+3$ 来考虑，这样我们的操作就变成了“每一次可以选择 $2$ 或 $3$ 个数字让它们 $-1$”。

那么我们开始考虑贪心。

## 贪心

明确的事是，我们肯定每次选择值最大的若干个数字将它们 $-1$。所以我们不由自主的想到使用优先队列来维护。现在的问题就是，我们怎么样决定选择 $2$ 个数字还是 $3$ 个数字呢？

我们貌似没有什么很好的方法。我们考虑最大的数字有多少个重复的。记最大值的个数为 $i$，那么如果 $i=1$，我们尽可能让 $-1$ 的操作集中到最大值上，并且分散对其他数字的影响，所以我们选择 $2$ 个数字。如果 $i$ 为奇数，那么我们就选择 $2$ 个数字。如果是奇数，那么就选择 $3$ 个。注意，我们不用考虑操作数量的多少，再次重申。

所以接下来就是很简单的模拟了。当所有数字相同时，停止即可。注意当数字变成 $0$ 时，不能继续 $-1$。要取 max。

## 代码

```C++
/*////////ACACACACACACAC///////////
       . Code  by  Ntsc .
       . Earn knowledge .
/*////////ACACACACACACAC///////////

#include<bits/stdc++.h>
#define int long long
#define db double
#define rtn return
#define pr pair<int,int>
#define pf first
#define ps second
#define pb push_back
#define mp make_pair
using namespace std;

const int N=1e5+5;
const int M=1e5;
const int Mod=1e5;
const int INF=1e5;

int n,m,p,q,T,ton[N],ans[N][3],cnt,i,v,id;

priority_queue<pr> pq;

void out(int a,int b,int c){
	ans[++cnt][0]=a;
	ans[cnt][1]=b;
	ans[cnt][2]=c;
}

void dec1(){//再选择1个数字 
	int v2=pq.top().pf,id2=pq.top().ps;
	pq.pop();
	pq.push(mp(max(v2-1,0ll),id2));
	pq.push(mp(max(v-1,0ll),id));
	
	ton[v]--;ton[max(v-1,0ll)]++;
	ton[v2]--;ton[max(v2-1,0ll)]++;
	out(id,id2,0);
	
}

void dec2(){//再选择2个数字 
	int v2=pq.top().pf,id2=pq.top().ps;
	pq.pop();
	int v3=pq.top().pf,id3=pq.top().ps;
	pq.pop();
	pq.push(mp(max(v3-1,0ll),id3));
	pq.push(mp(max(v2-1,0ll),id2));
	pq.push(mp(max(v-1,0ll),id));
	
	ton[v]--;ton[max(v-1,0ll)]++;
	ton[v3]--;ton[max(v3-1,0ll)]++;
	ton[v2]--;ton[max(v2-1,0ll)]++;
	out(id,id2,id3);
}

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>v;
		ton[v]++;
		pq.push(mp(v,i));
	} 
	while(1){
		v=pq.top().pf,id=pq.top().ps;//先选择1个数字 
		pq.pop();
		
		if(ton[v]==n){
			cout<<v<<endl;
			break;
		}
		
		if(ton[v]==1){
			dec1();
			
		}else if(ton[v]%2){
			dec2();
		}else{
			dec1();
		}
	}
	
	
	cout<<cnt<<endl;
	for(int i=1;i<=cnt;i++){
		for(int j=1;j<=n;j++){
			if(j==ans[i][0]||j==ans[i][1]||j==ans[i][2])cout<<1;
			else cout<<0;
		}
		cout<<endl;
	}
	return 0;
}
```




---

## 作者：chengni (赞：1)

首先很明显，这是一道special judge 题，我们不需要考略最少的游戏次数，而是要考虑最高的分数。

而且到了0之后分数就不能再降了，所以保证有解。

因为不需要考虑次数，所以2~5可以变成2~3来考虑，因为可以直接合成，因为数据范围不大，所以可以这样做，而不用考虑复杂度

然后我们用贪心的思想，一直减少最大值的分数，如果最大值不止一个，可以两两或三三打一局，否则就需要第二大的值来减。

利用一个堆就可以完成这个问题。

每次枚举最大值的个数进行操作，若为1，则同第二大的值一起减一；若为偶数，则取两个减一;奇数则取三个。当所有人分数一致时，便达到了目标。

代码看起来比较乱，有一部分只是简单地修改值，但是我写的很长，大家凑活看吧。

注意，分数不会小于零。

```cpp
#include<bits/stdc++.h>

using namespace std;

inline int read(){
	char ch=getchar();int x=0,f=1;
	while(ch>'9' || ch<'0'){
        if(ch=='-') f=-1;
	    ch=getchar();
	}
	while(ch>='0' && ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}


struct node{
	int f,v;
	operator <(node x)const{
        return v<x.v;
	}
};

node a[10000000];//存最大值

int f[8000][1000];//输出处理数组

priority_queue<node> q;//大根堆

int main(){
	int n=read();
	for(int i=1;i<=n;i++){
		node v;
		v.v=read();v.f=i;
		q.push(v);//全扔进去
	}
	int tot=0;
	for(int j=1;;j++){
		int num=1,cnt=1;
		a[cnt]=q.top();q.pop();
		while(q.size()){
			if(q.top().v==a[1].v){//计算最大值的个数
				cnt++;
				a[cnt]=q.top();
				q.pop();
			}
			else break;
		}
		if(cnt==n){//为n，结束
			printf("%d\n",a[cnt].v);
			printf("%d\n",j-1);
			for(int k=1;k<=j-1;k++){//输出方案
				for(int l=1;l<=n;l++){
					printf("%d",f[k][l]);//因为special judge ，成立
				}
				printf("\n");
			}
			return 0;
		}
		else if(cnt==1){//为1，取第二大值
            node v=q.top();//第二大
            q.pop();
            v.v-=1;
            if(v.v<0) v.v=0;
            f[j][v.f]=1;
            q.push(v);
            a[cnt].v-=1;
            if(a[cnt].v<0) a[cnt].v=0;
            f[j][a[cnt].f]=1;
            q.push(a[cnt]);
 	    }
     	else if(cnt%2==0){//为偶数，处理两个最大值
			for(int i=3;i<=cnt;i++){//多余的扔回去
				q.push(a[i]);
			}
			a[1].v-=1;
			if(a[1].v<0) a[1].v=0;
			f[j][a[1].f]=1;
			q.push(a[1]);
			a[2].v-=1;
			if(a[2].v<0) a[2].v=0;
			f[j][a[2].f]=1;
			q.push(a[2]);
		}
		else {//为奇数且不为1，处理前三个
		    for(int i=4;i<=cnt;i++){//多余的扔回去
				q.push(a[i]);
			}
			a[1].v-=1;
			if(a[1].v<0) a[1].v=0;
			f[j][a[1].f]=1;
			q.push(a[1]);
			a[2].v-=1;
			if(a[2].v<0) a[2].v=0;
			f[j][a[2].f]=1;
			q.push(a[2]);
			a[3].v-=1;
			if(a[3].v<0) a[3].v=0;
			f[j][a[3].f]=1;
			q.push(a[3]);
		}
		
	} 
}
```

---

