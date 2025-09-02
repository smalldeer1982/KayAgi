# Running for Gold

## 题目描述

### 【题目大意】

奥运比赛刚刚开始，Federico 便十分渴望观看比赛。

有 $n$ 个选手参加了马拉松比赛，从 $1$ 到 $n$ 依次编号。她们**都**参加了 $5$ 项比赛，比赛从 $1$ 到 $5$ 编号。

现在有一个二维的数组 $r_{i,j}(1 \leq i \leq n,1 \leq j \leq 5)$，表示选手 $i$ 在比赛 $j$ 中排名第 $r_{i,j}$ 名。

Federico 认为选手 $u$ 优于选手 $v$，当且仅当，$u$ 在**至少** $3$ 个项目中战胜了 $v$（即排名在 $v$ 前）。

Federico 认为选手 $x$ 能够获得金牌当且仅当 $x$ 可以战胜其它**所有**选手。

给定 $r_{i,j}$，求是否有一名选手可以获得金牌。

## 样例 #1

### 输入

```
4
1
50000 1 50000 50000 50000
3
10 10 20 30 30
20 20 30 10 10
30 30 10 20 20
3
1 1 1 1 1
2 2 2 2 2
3 3 3 3 3
6
9 5 3 7 1
7 4 1 6 8
5 6 7 3 2
6 7 8 8 6
4 2 2 4 5
8 3 6 9 4```

### 输出

```
1
-1
1
5```

# 题解

## 作者：MikeC (赞：7)

## 分析

首先，要判断是否会有运动员获得奖牌，只需要判断最有可能获得奖牌的运动员是否满足条件即可。

然后，我们需要找到所有运动员获得奖牌可能性的顺序。显然，$A$ 在至少 $3$ 场比赛中优于 $B$，$B$ 在至少 $3$ 场比赛中优于 $C$，$A$ 并不一定在至少三场比赛中优于 $C$，所以胜负关系并不具有传递性，自然的想到以两人之间的胜负关系进行排序，最后再判断最有可能获胜的运动员是否满足条件即可。

以两人之间的胜负关系的排序可以用快速排序进行优化，时间复杂度 $O(n \log n)$

## 代码

``````cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int race[50001][6];
int racer[50001];
bool cmp(int x,int y){
    int sum=0;
    for(int i=1;i<=5;i++){
        if(race[x][i]<race[y][i])sum++;
    }
    if(sum>=3)return true;
    else return false;
}
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            racer[i]=i;
            for(int j=1;j<=5;j++){
                scanf("%d",&race[i][j]);
            }
        }
        sort(racer+1,racer+1+n,cmp);
        for(int i=2;i<=n;i++){
            if(cmp(racer[1],racer[i])==false){
                printf("-1\n");
                goto s;
            }
        }
        printf("%d\n",racer[1]);
        s:;
    }
}
``````



---

## 作者：断清秋 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1552B)

题意：给出 $n$ 名运动员五场马拉松比赛的名次，若运动员 $A$ 有对应比赛三次及以上成绩比运动员 $B$ 好，则认为 $A$ 的成绩优于 $B$。求是否有运动员比其余任何人都更优。

首先，最多只有一个运动员满足条件，那么一名运动员只要不优于任何其他选手，那么就不需要再考虑他了。

所以可以记录第 $1$ 名运动员的成绩，依次向下比较。如果他不优于另一位选手，那么再用这名新运动员的成绩继续向下比较，最终可以得到一个可能是最终答案的运动员。

但是发现优劣关系并不具有传递性，即 $A$ 优于 $B$，$B$ 优于 $C$，并不代表$A$ 优于 $C$，这名运动员并不一定是最终答案。

因此再用这名运动员的成绩与其他所有人的成绩重新比较一次，如果他确实优于所有其他选手，则输出该选手，否则无解。

时间复杂度 $O(tn)$。

代码：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#define ll long long
#define back return
#define ri register int 
using namespace std;
int read()
{
	int x=0,f=1;
    char ch=getchar();
	while(!isdigit(ch))
    {
        if (ch=='-') 
            f=-1;
        ch=getchar();
    }
	while(isdigit(ch))
    {
        x=x*10+ch-48;
        ch=getchar();
    }
	back x*f;
}
ll r[55000][10],b[1000];
ll t,n,m,k;
int main()
{
	cin>>t;
	while(t--)
	{
		bool flag=0;
		int sumr=0,sumb=0,lsbl=1;
		memset(r,0,sizeof(r));
		memset(b,0,sizeof(b));
		cin>>n;
		for(ri i=1;i<=n;i++)
			for(ri j=1;j<=5;j++)
				cin>>r[i][j];
		if(n==1)
		{
			cout<<1<<endl;
			continue;
		}		
		b[1]=r[1][1],b[2]=r[1][2],b[3]=r[1][3],b[4]=r[1][4],b[5]=r[1][5];
		for(ri i=2;i<=n;i++)
		{
			sumr=sumb=0;
			for(ri j=1;j<=5;j++)
			{
				if(r[i][j]<b[j])
					sumr++;
				if(b[j]<r[i][j])
					sumb++;
			}		
			if(sumr>=3)
			{
				b[1]=r[i][1],b[2]=r[i][2],b[3]=r[i][3],b[4]=r[i][4],b[5]=r[i][5];
				lsbl=i;
			}
			if(sumb>=3)
				flag=1;			
		}
		for(ri i=1;i<=n&&i!=lsbl;i++)
		{
			int sum1=0,sum2=0;
			for(ri j=1;j<=5;j++)
			{
				
				if(r[i][j]<r[lsbl][j])
					sum1++;
				if(r[i][j]>r[lsbl][j])
					sum2++;
			}
			if(sum1>=3||sum2<3)
			{
				lsbl=1;
				flag=0;
				break;
			}
			
		}
		if(lsbl==1&&flag==0)
			cout<<-1<<endl;
		else
			cout<<lsbl<<endl;
	}
    back 0;
}
```

---

## 作者：Wuyanru (赞：1)

本题让我们求出一个可能拿到金牌的运动员，如果没有则输出 $ -1 $。

注意到题目中只让我们输出任意一个满足条件的运动员，那就是说我们可以只对我们认为最有可能达成目标的运动员进行检查。

所以，我们只需要对所有运动员的胜负关系进行排序，虽然胜负关系不可传递，但是排序后第一个运动员仍然会是最有可能的运动员，对他进行检查即可。

时间复杂度 $ O\left(n\log_2n\right) $，瓶颈在于排序。

AC 代码：

```
#include<algorithm>
#include<cstdio>
using namespace std;
int a[50001][6];
int ans[50001];
int n;
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=5;j++)
				scanf("%d",a[i]+j);
			ans[i]=i;
		}
		sort(ans+1,ans+n+1,[](int x,int y)
		{
			int p=0;
			for(int i=1;i<=5;i++)
				if(a[x][i]<a[y][i])
					p++;
			if(p>=3)
				return true;
			return false;
		});
		bool flag=0;
		for(int i=1;i<=n;i++)
		{
			if(i==ans[1])
				continue;
			int p=0;
			for(int j=1;j<=5;j++)
				if(a[ans[1]][j]<a[i][j])
					p++;
			if(p<3)
			{
				flag=1;
				break;
			}
		}
		if(flag)
			printf("-1\n");
		else
			printf("%d\n",ans[1]);
	}
	return 0;
}
```

感谢观看！

注：本代码有用到 C++11 语法，使用 C++ 会造成 CE。

---

## 作者：YGB_XU (赞：0)

### 题意简述：

对每组数据有 $n$ 位选手,以及他们在五场比赛中的排名。定义两个选手中**更好**的那一个为五场比赛中排名有**至少三场较靠前**的那个选手。询问有没有一位比**其他所有**选手都要更好的选手，有则输出他的编号，否则输出 $-1$。

------------
### 核心做法：快排+判断函数。
观察 $5$ 和 $3$ 两个数字后可以发现两位选手**不存在**类似“平局”的情况，因为某次比赛的排名总有先后，由抽屉原理得知总有一人会在至少三场比赛中领先。因此可以使用快排附加判断函数对选手们排序，而不会出现死循环。在这里我们用结构体方便操作。

------------
### 一些细节：
- 排序一遍后“最优”的选手在数组的第一位，还要对他是否优于全部人进行判断。
- 因此最后的判断中应从 $2$ 号开始枚举
- 在结构体中记录选手原先的编号，方便在排序后输出。

------------
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int NR=5e4+5;
int n;
struct Node{
	int s[6];//数组下标到5。
    int id;
}a[NR];

bool cmp(Node x,Node y){//快排判断函数 
	int cnt=0;
	for(int i=1;i<=5;i++) cnt+=(int)x.s[i]<y.s[i];//记录领先的场数
	return cnt>=3;
}

inline bool check(){
	int cnt;
	for(int i=2;i<=n;i++){//循环从2开始
		cnt=0;
		for(int j=1;j<=5;j++){
			cnt+=(int)a[1].s[j]<a[i].s[j];
		}
		if(cnt<3) return false;
	}
	return true;
}

int main(){
	int t;
	scanf("%d",&t);//CF多组数据
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			a[i].id=i;
			for(int j=1;j<=5;j++) scanf("%d",&a[i].s[j]);
		}
		sort(a+1,a+n+1,cmp);
		if(check()) printf("%d\n",a[1].id);
		else printf("-1\n");//无解
	}
	return 0;
}

```

---

## 作者：Xhesika_Frost (赞：0)

提供一个$O(nlogn)$的做法

我们可以仿照快速排序的思想，每一次在原序列随机选一个运动员，把所有运动员分成比他强的和比他弱的，再在比他弱的中重复这个过程。

最后会只剩下一个运动员，检查一下是否这个运动员真的比所有人强就可以了
```cpp
#include<iostream>
#include<Cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int rk[100001][6];
int t;
int vis[100001];
int n;
int tem[100001][2];
int l;
int cnt;
bool cal(int x,int y){
	int cntt=0;
	for(int i=0;i<=4;++i){
		if(rk[y][i]<rk[x][i]){
			cntt++;
		}
	}
	return cntt>=3;
}
int main(){
	scanf("%d",&t);
	while(t--){
		memset(vis,0,sizeof(vis));
		scanf("%d",&n);
		cnt=0;
		for(int i=1;i<=n;++i){
			scanf("%d%d%d%d%d",&rk[i][0],&rk[i][1],&rk[i][2],&rk[i][3],&rk[i][4]);
			tem[i][0]=i;
		}
		l=n;
		int fa=0;
		int key=rand()%l+1;
		while(l>1){
			cnt^=1;
			int te=0;
			fa=0;
			key=rand()%l+1;
			for(int i=1;i<=l;++i){
				if(i==key) continue;
				if(cal(tem[key][cnt^1],tem[i][cnt^1])){
					if(vis[tem[i][cnt^1]]){
						fa++;
						continue;	
					}
					te++;
					tem[te][cnt]=tem[i][cnt^1];	
				}else{
					vis[tem[i][cnt^1]]=1;
				}
			}
			l=te;
		}
		if(l==0){
			int f=0;
			cnt^=1;
				for(int i=1;i<=n;++i){
					if(i==tem[key][cnt]) continue;
					if(cal(tem[key][cnt],i)){
						f=1;
						break;
					}
				}
				if(!f)
				cout<<tem[key][cnt]<<endl;
				else{
					cout<<-1<<endl;
				}
		}else{
			if(fa==0){
				int f=0;
				for(int i=1;i<=n;++i){
					if(i==tem[1][cnt]) continue;
					if(cal(tem[1][cnt],i)){
						f=1;
						break;
					}
				}
				if(!f)
				cout<<tem[1][cnt]<<endl;
				else{
					cout<<-1<<endl;
				}
			}else{
				cout<<-1<<endl;
			}
		}
	}
	return 0;
}
```

---

