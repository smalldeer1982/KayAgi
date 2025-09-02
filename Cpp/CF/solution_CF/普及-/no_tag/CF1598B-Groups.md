# Groups

## 题目描述

$ n $ students attended the first meeting of the Berland SU programming course ( $ n $ is even). All students will be divided into two groups. Each group will be attending exactly one lesson each week during one of the five working days (Monday, Tuesday, Wednesday, Thursday and Friday), and the days chosen for the groups must be different. Furthermore, both groups should contain the same number of students.

Each student has filled a survey in which they told which days of the week are convenient for them to attend a lesson, and which are not.

Your task is to determine if it is possible to choose two different week days to schedule the lessons for the group (the first group will attend the lesson on the first chosen day, the second group will attend the lesson on the second chosen day), and divide the students into two groups, so the groups have equal sizes, and for each student, the chosen lesson day for their group is convenient.

## 说明/提示

In the first testcase, there is a way to meet all the constraints. For example, the first group can consist of the first and the third students, they will attend the lessons on Thursday (the fourth day); the second group can consist of the second and the fourth students, and they will attend the lessons on Tuesday (the second day).

In the second testcase, it is impossible to divide the students into groups so they attend the lessons on different days.

## 样例 #1

### 输入

```
2
4
1 0 0 1 0
0 1 0 0 1
0 0 0 1 0
0 1 0 1 0
2
0 0 0 1 0
0 0 0 1 0```

### 输出

```
YES
NO```

# 题解

## 作者：happy_dengziyue (赞：0)

### 1 思路

枚举哪两天安排课程。设为星期 $x$ 和星期 $y$。

统计每个同学。如果有人两天都没空，直接否掉。

设仅仅星期 $x$ 有空的同学数量为 $cnt[0]$，仅仅星期 $y$ 有空的同学数量为 $cnt[1]$，两天均有空的同学数量为 $cnt[2]$。

如果 $cnt[0]<n\div2$，则从两天都有空的人中抽调足够的人去星期 $x$；星期 $y$ 同理。

如果 $cnt[2]<0$，就是人不够用了，方案就不合法。

否则此方案合法。

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
#define max_n 1000
int t;
int n;
int a[max_n+2][7];
int cnt[3];
bool ans;
bool check(int x,int y){
	cnt[0]=cnt[1]=cnt[2]=0;
	for(int i=1;i<=n;++i){
		if(a[i][x]&&!a[i][y])++cnt[0];
		if(!a[i][x]&&a[i][y])++cnt[1];
		if(a[i][x]&&a[i][y])++cnt[2];
		if(!a[i][x]&&!a[i][y])return false;
	}
	if(cnt[0]<n/2)cnt[2]+=cnt[0]-n/2;
	if(cnt[1]<n/2)cnt[2]+=cnt[1]-n/2;
	return cnt[2]>=0;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1598B_1.in","r",stdin);
	freopen("CF1598B_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i){
			for(int j=1;j<=5;++j){
				scanf("%d",a[i]+j);
			}
		}
		ans=false;
		for(int i=1;i<=5;++i){
			for(int j=i+1;j<=5;++j){
				if(check(i,j))ans=true;
			}
		}
		if(ans)printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/59662589)

By **dengziyue**

---

## 作者：洛桃 (赞：0)

#### 预警

由于这道题比较宽的时间限制，使得很多比较暴力的做法都过去了，我的做法应该也是其中一种，比较简单，希望看低复杂度的可以跳过。

## 思路

首先统计对于每一天，有多少人可以在这天上课，并且找出这5天中有哪一天可以上课的人数大于等于 $n/2$ 。如果少于两天，可以直接输出NO。

接着暴力枚举所有可能的组合，由于总共只有5天，所以即使每天都有二分之一的人可以上课，也只有10种组合。

然后判断对于每个组合，能否找到一种办法将 $n$ 个人不重不漏地分到这两天。先设这两天是第 $i$ 天与第 $j$ 天，我的思路是枚举每一个人，并判断要把他分到那一组。先把在这两天中只能上第 $i$ 天或者第 $j$ 天的人，分到对应的组里，每组现有人数用一个计数器存下来。

然后再找出这两天都能上的人，并判断哪一组里现在人数更少，就分到哪一组，尽量让两组人数相等。

最后判断一下两个计数器是否都等于 $n/2$ 。如果是，那么我们已经找到了一种可能的方法，直接输出YES退出循环。如果不是，那么将计数器清零，枚举下一种组合，直到退出循环，输出NO。

## 代码
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
int t,n;
int a[1010][6];
int sum[6];
bool ex[6];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		for(int j=1;j<=5;j++)
		  scanf("%d",&a[i][j]),sum[j]=0;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=5;j++)if(a[i][j])sum[j]++;
		}
		int mxi,mii,maxn=0,max1=0;
		for(int i=1;i<=5;i++)ex[i]=0;
		for(int i=1;i<=5;i++){
			if(sum[i]>=n/2)ex[i]=1;
		}
		int cnt1=0,cnt2=0;
		bool f=0;
		for(int i=1;i<=5;i++)
		{
			if(ex[i]){
				for(int j=1;j<=5;j++){
					cnt1=cnt2=0;
					if(ex[j]&&i!=j){
						for(int k=1;k<=n;k++)
						{
							if(a[k][i]&&a[k][j])continue;
							if(a[k][i])cnt1++;
							if(a[k][j])cnt2++;
						}
						for(int k=1;k<=n;k++)
						{
							if(a[k][i]&&a[k][j]){
								if(cnt1<cnt2)cnt1++;
								else cnt2++;	
							}
						}
					}
					if(cnt1==cnt2&&cnt1==n/2){f=1;printf("YES\n");break;}
				}
			}
			if(f)break;
		}
		if(f==0)printf("NO\n");
	}
	return 0;
}
```


---

## 作者：SegTre (赞：0)

## 题意简述

有 $n$ 个学生要选课，有周一到周五的五种课程。要求把学生分为人数相等的两组，每组报一个课程，两组要求课程不同。给出每个学生在星期几有时间上课，问是否存在这样的分组方案。

## 思路

枚举两组报的是哪两种课程，暴力判断该方案是否可行。

假设报了 $\texttt{x,y}$ 两种课，统计以下学生人数：

只在 $\texttt{x}$ 课有空的学生，记为 $\texttt{cnt1}$。

只在 $\texttt{y}$ 课有空的学生，记为 $\texttt{cnt2}$。

两节课都有空的学生，记为 $\texttt{cnt}$。

然后分情况讨论：

1.如果 $\texttt{cnt1,cnt2}$ 都能凑齐一组（即凑到 $\dfrac{n}{2}$ 人），显然可行。 

2.如果 $\texttt{cnt1}$ 凑齐一组而 $\texttt{cnt2}$ 没有，看 $\texttt{cnt1+cnt}$ 能不能凑到，能就可行，否则不可行。

3.如果 $\texttt{cnt2}$ 凑齐一组而 $\texttt{cnt1}$ 没有，处理方法同上。

4.如果两个都没凑齐，考虑到两节课都有空的学生随便分到哪个组，直接判断 $\texttt{cnt+cnt1+cnt2} \geqslant \texttt{n}$ 是否成立。

代码中的变量大多出现都在上面了，应该很好理解。

## Code

```cpp
#include<cstdio>
#include<cctype>
using namespace std;
inline int read() {
	int res;char c;
	while(!isdigit(c=getchar()));res=c^48;
	while(isdigit(c=getchar())) res=(res<<3)+(res<<1)+(c^48);
	return res;
}
int n;
bool a[1005][6];
bool check(int x,int y) {
	int cnt1=0,cnt2=0,cnt=0;
	for(int i=1;i<=n;++i) cnt1+=(!a[i][y]&a[i][x]);
	for(int i=1;i<=n;++i) cnt2+=(!a[i][x]&a[i][y]);
	for(int i=1;i<=n;++i) cnt+=(a[i][y]&a[i][x]);
	if(cnt1>=n/2&&cnt2>=n/2) return 1;
	if(cnt1<n/2&&cnt2<n/2) {
		if(cnt-(n-cnt1-cnt2)>=0) return 1;
		else return 0;
	}
	if(cnt1<n/2&&cnt2>=n/2) return cnt1+cnt>=n/2? 1:0;
	if(cnt2<n/2&&cnt1>=n/2) return cnt2+cnt>=n/2? 1:0;
	return 0;
}
int main() {
	int t=read();
	bool ans=0;
	while(t--) {
		n=read();ans=0;
		for(int i=1;i<=n;++i) for(int j=1;j<=5;++j) a[i][j]=read();
		for(int i=1;i<=5;++i) {
			for(int j=i+1;j<=5;++j) 
				if(check(i,j)) {
					ans=1;
					break;
				}
			if(ans) break;
		}
		if(ans) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```


---

## 作者：Farkas_W (赞：0)

$$\text{题目大意}$$

$\quad$有 $n$ 个学生，每个学生在周一到周五有些天可以上课(用 $1$ 表示)，其余的时间则不能上课(用 $0$ 表示)，**问是否有一种分法**，将 $n$ 名学生分成大小为 $\frac{n}{2}$ 的两组( $n$ 为偶数)，满足组内所有学生都可以选择共同的一天上课，且两组学生选择的时间不一样。

$$\text{思路}$$

$\quad$考虑容斥原理，先用 $cnt_i$ 表示第 $i$ 天(星期 $i$ )可以上课的学生数量，用 $num_{i,j}$ 表示第 $i$ 天和第 $j$ 天**都**可以上课的学生数量。

$\quad$先选择两个不同的时间 $i,j$，满足以下条件即可完成分组：

$$ \left\{
\begin{aligned}
& cnt_i\times 2\geq n\\
& cnt_j\times 2\geq n\\
& cnt_i+cnt_j-num_{i,j}= n
\end{aligned}
\right.
$$

$\quad$前两个条件很好理解，关键就是第三个条件怎么推的。

$\quad$设 $x=cnt_i-num_{i,j},y=cnt_j-num_{i,j}$，$x$ 的意义是只可以上第 $i$ 天课的人(这里只考虑 $i,j$ 两天)，$y$ 的意义是只可以上第 $j$ 天课的人。

$\quad$又因为 $num_{i,j}$ 表示 $i,j$ 两天都可以上的人，可以发现 $x,y,num_{i,j}$ 没有并集(没有人同时在两个集合)，$num_{i,j}$ 可以选择第 $i$ 天上课（加入$x$），也可以选择第 $j$ 天上课（加入 $y$），只要满足 $x+y+num_{i,j}= n$ 即可，经过化简就是:
$$cnt_i+cnt_j-num_{i,j}= n$$

$\quad$这里我用数位的方法保存 $num$ 数组，其实直接用二维数组就可以了。

$\quad$注意：多组数据，记得清空数组。

```cpp
const int N=1e3+5;
int T,n,ans,mid,cnt[6],num[70];
vector<int>t[N];
signed main()
{
	T=read();
	while(T--){
		n=read();ans=0;mid=n/2;
		memset(cnt,0,sizeof(cnt));
		memset(num,0,sizeof(num));
		for(re i=1;i<=n;i++)
		{
			t[i].clear();
			for(re j=1;j<=5;j++)
			{
				bool b=read();
				if(b)cnt[j]++,t[i].push_back(j);
			}
			if(t[i].size()==1)continue;
			for(re j=0;j<t[i].size();j++)
			{
				int x=1<<t[i][j];
				for(re k=j+1;k<t[i].size();k++)
				{
					int y=x|(1<<t[i][k]);
					num[y]++;
				}
			}
		}
		for(re i=1;i<5;i++)
		{
			if(cnt[i]*2<n)continue;
			for(re j=i+1;j<=5;j++)
			{
				if(cnt[j]*2<n)continue;
				int x=cnt[i],y=cnt[j],z=num[(1<<i)|(1<<j)],p;
				if(x+y-z==n){ans=1;break;}
			}
			if(ans)break;
		}
		puts(ans?"YES":"NO");
	}
	return 0;
}
```


---

