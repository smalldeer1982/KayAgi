# Dragon of Loowater

## 题目描述

![](https://cdn.luogu.com.cn/upload/image_hosting/tqycbsg2.png)

从前，在 Loowater 王国，一场小麻烦变成了一个大问题。Loowater 中部的 Rellau 溪岸一直是大雁繁殖的理想之地。由于缺乏天敌，大雁的数量失控。Loowater 的人民大多远离大雁。偶尔会有一只大雁袭击人们，可能会咬掉一两个手指，但总的来说，人民把大雁当作一个小麻烦忍受着。

有一天，一次奇怪的变异发生了，一只大雁产下了一条多头的喷火龙。当这条龙长大后，它威胁要把 Loowater 王国烧成灰烬。Loowater 遇到了一个大问题。国王十分惊恐，召集他的骑士们去屠龙，拯救王国。

骑士们解释道：“要屠龙，我们必须砍下它所有的头。每个骑士只能砍掉龙的一个头。龙的头大小不一。为了砍掉一个头，骑士必须至少和龙头的直径一样高。骑士工会要求，砍掉一个头的骑士必须得到相当于其身高每厘米一枚金币的报酬。”

有足够的骑士来打败这条龙吗？国王召集他的顾问们来帮他决定该雇佣多少骑士以及选择哪些骑士。在花费大量金钱建造米尔公园后，国王想要将屠龙的开支降到最低。作为顾问之一，你的任务是帮助国王。你非常认真地对待这个任务：如果失败了，你和整个王国都将被烧成灰烬！

## 样例 #1

### 输入

```
2 3
5
4
7
8
4
2 1
5
5
10
0 0```

### 输出

```
11
Loowater is doomed!```

# 题解

## 作者：尚君子 (赞：12)

思路与楼上一样，但是代码更短  ~~ (按照蓝书打的）光速逃 ~~

能力强的武士开价高是合理的，但如果你派去看一个很弱的头，那就是浪费人才了。可以把骑士按照能力从小到大排序，所有头直径排排序，就$OK$了！   


PS:这就是greedy algorithm
~~（贪心算法，逃）~~
```cpp
#include<cstdio>
#include<algorithm>       // 因为用到了sort
using namespace std;

const int maxn = 20000 + 5;
int A[maxn], B[maxn];
int main() {
  int n, m;
  while(scanf("%d%d", &n, &m) == 2 && n && m) {
    for(int i = 0; i < n; i++) scanf("%d", &A[i]);
    for(int i = 0; i < m; i++) scanf("%d", &B[i]);
    sort(A, A+n);
    sort(B, B+m);
    int cur = 0;         // 当前需要砍掉的头的编号
    int cost = 0;        // 当前总费用
    for(int i = 0; i < m; i++)
      if(B[i] >= A[cur]) {
        cost += B[i];           // 雇佣该骑士
        if(++cur == n) break;   // 如果头已经砍完，及时退出循环
      }
    if(cur < n) printf("Loowater is doomed!\n");
    else printf("%d\n", cost);
  }
  return 0;
}
```


---

## 作者：雨季 (赞：3)

# 题解
发一个$STL$的做法吧  
将所有的恶龙存进数组，$sort$  
将所有的骑士存进 $multiset$ ，$($同一能力值的骑士可能有很多$)$  
然后在 $multiset$ 里 $lower\_bound$ ，找到一个刚好可以打掉这个头的骑士$($大于等于$)$。让 $ans$ 加上这个骑士的能力值，并将这个骑士从集合里删除掉。  
**注意：**  
**1. 多组数据需要清空 $multiset$**  
**2. 为了防止 $lower\_bound$ 的时候找不到 大于等于 当前头的值，需要先在集合里放入一个极大值，防止越界RE。**
****
# 代码
```cpp
#include<iostream>
#include<cstdio>
#include<set>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 200005
 
int n,m;
int dra[N];
multiset<int>se;
 
inline int read() {
	int tmp=0,w=1;
	char ch=0;
	while(ch<'0'||ch>'9') {if(ch=='-') w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') tmp=(tmp<<1)+(tmp<<3)+ch-'0',ch=getchar();
	return tmp*w;
}
 
int main()
{
	while(scanf("%d%d",&n,&m)==2&&(n||m)) {
		se.clear();
		memset(dra,0,sizeof(dra));
		for(int i=1;i<=n;++i) dra[i]=read(); // dragon：恶龙 
		int x;
		se.insert(1e9);
		for(int i=1;i<=m;++i) x=read(),se.insert(x); // 将骑士放进一个集合中 
		int ans=0;
		sort(dra+1,dra+1+n); // 将恶龙排序 
		bool mark=0;
		for(int i=1;i<=n;++i) {
			multiset<int>::iterator x=se.lower_bound(dra[i]);
			if(*x==1e9) {mark=1;break;} // 如果没有比dra[i]大的骑士，就完蛋了 
			ans=ans+*x;
			se.erase(x);
		}
		if(n>m||mark) printf("Loowater is doomed!\n");
		else printf("%d\n",ans);
	} 
	return 0;	
}
```

---

## 作者：Kyrie_Harry_Irving (赞：1)

# 此题很明显使用贪心做法


------------

## 先O（nlogn） 排序 再跑一遍贪心


------------

### 贪心步骤是对于一个权值大的龙，用可以砍掉他的耗费（也就是能力值）最小的骑士砍他.

##### ~~这么简单为什么不自己写一遍~~

* # 上代码
```c
#include<bits/stdc++.h>
const int maxn=20010;
using namespace std;
int a[maxn],b[maxn];
int main()
{
	int n,m;
	while((scanf("%d%d",&n,&m))==2&&n&&m)
	{
		for(int i=0;i<n;i++) cin>>a[i];
		for(int i=0;i<m;i++) cin>>b[i];
		sort(a,a+n);
		sort(b,b+m);
		int t=0;
		int ans=0;
		for(int i=0;i<m;i++)
		{
			if(b[i]>=a[t])
			{
				ans+=b[i];
				t++;
				if(t==n)
					break;
			}
		}
		if(t<n) cout<<"Loowater is doomed!"<<endl;
		else cout<<ans<<endl;
	}
	return 0;
}

```


---

## 作者：唔啊唔 (赞：1)

这是一道特别水的贪心+排序题！
```cpp
//有点慢请不要建议 
#include<bits/stdc++.h>
using namespace std;
int n,m,a[100000],b[100000];
int main(){
	while(cin>>n>>m){
		if(n==0&&m==0)return 0;				//结束输出 
		int sum=0,q=0,p=1;					//sum为答案，p为a数组的序号，q为变量 
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=m;i++){
			cin>>b[i];
		}
		sort(a+1,a+1+n);					//从小到大排序 
		sort(b+1,b+1+m);
		for(int j=1;j<=m;j++){				//排士兵的序 
			if(b[j]>=a[p]){
				sum=sum+b[j];
		        p++;
			}
			if(p==n+1){						 
				q=1;						//可以砍完 
				break;						//结束循环
			}
		}
		if(q==1)cout<<sum<<endl;
		else puts("Loowater is doomed!");
	}
	return 0;								//功德圆满 
}
```

---

## 作者：张亦弛 (赞：1)

此题没什么说的，简单的模拟加上贪心的思想。具体看代码：


------------

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;//n个头、m个勇士 
int head[20005];//头的直径 
int killer[200005];//勇士的能力 
int ans;//记录花费的金币 
int main()
{
	while(cin>>n>>m)//多组数据 
	{
		if(n==0&&m==0)//直到输入两个0，停止输入 
			break;
		ans=0;
		memset(head,0,sizeof(head));
		memset(killer,0,sizeof(killer));//多组数据，注意初始化 
		for(int i=1;i<=n;i++)
			cin>>head[i];//输入头的直径 
		for(int i=1;i<=m;i++)
			cin>>killer[i];//输入勇士的能力 
		//因为要求金币花费尽量少，所以贪心的思想 
		sort(head+1,head+1+n);//按照直径从小到大排序 
		sort(killer+1,killer+1+m);//按照能力从小到大排序 
		int a=1,b=1;//a是第几个头，b是第几个勇士 
		while(a<=n)//当头没砍完时 
		{
			if(b>m)//如果勇士已经没了 
				break;//直接退出，杀不死龙 
			if(head[a]<=killer[b])//如果砍得掉 
			{
				ans+=killer[b];//加上所花费的金币 
				a++;//下一个头 
				b++;//下一个勇士 
				continue;
			}   
			else//如果砍不掉 
			{
				b++;//下一个勇士 
				continue;
			}
		}
		if(a<=n)//勇士不够而使循环退出的情况 
			cout<<"Loowater is doomed!"<<endl;
		else
			cout<<ans<<endl;//输出花费的金币
	}
	return 0;
}
```

---

## 作者：currycodingg (赞：0)

这道题模拟就好了啊

规则：一个骑士可以杀死一条龙，那么他的能力一定>=龙头的直径。

如果让一个能力为1000000的骑士去杀一个龙头直径为10的肯定不划算，所以我们可以先对龙头和骑士从小到大排序，然后用两个指针分别代表龙和骑士，根据题意模拟。

```
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=20000+5;
int n,m,qi[N],lo[N],ans,cnt;

int main(){
	while(scanf("%d%d",&n,&m)==2&&n&&m){
		memset(lo,0,sizeof(lo));//多组数据的话一定要先清空数组！！qwq 
		memset(qi,0,sizeof(qi));//多组数据的话一定要先清空数组！！qwq 
		for(int i=1;i<=n;i++) scanf("%d",&lo[i]);
		for(int i=1;i<=m;i++) scanf("%d",&qi[i]);
		sort(lo+1,lo+n+1);
		sort(qi+1,qi+m+1);
		ans=0;
		int it=1;
		bool ok=true;//ok用来表示是否有解
		for(int i=1;i<=n;i++){
			if(lo[i]<=qi[it]){
				ans+=qi[it];
				it++;
			}
			else{
				while(qi[it]<lo[i]){
					it++;
					if(it>m){//如果当前it都大于骑士个数了，就肯定无解了
						ok=false;
						break;
					}
				}
				if(ok){	ans+=qi[it]; it++; } 
				else break;
			}
		}
		if(ok)printf("%d\n",ans);
		else printf("Loowater is doomed!\n");
	}
	return 0;
}
//纪念这个心里颇不宁静的晚上 qwq
```

---

