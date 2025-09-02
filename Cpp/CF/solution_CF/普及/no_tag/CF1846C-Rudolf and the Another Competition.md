# Rudolf and the Another Competition

## 题目描述

Rudolf 已经报名了一个遵循 ICPC 规则的编程竞赛。这些规则意味着，每通过一道题，参与者将获得 $1$ 积分，同时还会受到相当于从比赛开始到 AC 时间的罚时。在排行榜中，分数高的参与者排名较高，如果分数相等，罚时较少的参与者排名较高。

现在总共有 $n$ 名参与者参与了比赛，Rudolf 是编号为 $1$ 的参与者。已知一共有 $m$ 题，$h$ 分钟。

现在，一个强大的人工智能已经预测到了值 $t_{i，j}$，它表示第 $i$ 位参与者解决第 $j$ 道问题所需的分钟数。

Rudolf 意识到解决问题的顺序可以影响最终的结果。例如，如果 $h = 120$，解决问题的时间是\[ $20，15，110$ \]，那么，如果  Rudolf 按一下几种顺序解决问题，会出现一下几种情况:

- ${3，1，2}$，那么他只会解决第三个问题，得到 $1$ 积分和 $110$ 罚时。
- ${1，2，3}$，那么他将在开始的 $20$ 分钟后解决第一个问题，在 $20+15=35$ 分钟后解决第二个问题，他将没有时间解决第三个问题。因此，他将获得 $2$ 积分和 $20+35=55$ 罚时。
- ${2，1，3}$，那么他将在开始的 $15$ 分钟后解决第二个问题，在 $15+20=35$ 分钟后解决第一个问题，他将没有时间解决第三个问题。因此，他将获得 $2$ 点和 $15+35=50$ 的罚时。

Rudolf 感兴趣的是，如果每个参与者根据人工智能的预测，以最佳顺序解决问题，他将在比赛中为第几名。假设在积分和罚时相同的情况下，Rudolf 将占据最靠前的位置。

## 样例 #1

### 输入

```
5
3 3 120
20 15 110
90 90 100
40 40 40
2 1 120
30
30
1 3 120
10 20 30
3 2 27
8 9
10 7
10 8
3 3 15
7 2 6
7 5 4
1 9 8```

### 输出

```
2
1
1
2
1```

# 题解

## 作者：12345678hzx (赞：3)

## 题目大意
给定 $n$ 个人在 ICPC 赛制下通过 $m$ 题所需要的时间，求第 $1$ 个人的排名。
## 思路
考虑贪心，在有限的时间里，我们尽可能先完成用时少的题，这样能尽可能分配给后面的题多一些时间，对于罚时的贡献也是最小的。

所以，我们读入后，对选手写每道题所用的时间从小到大进行排序，如果能写就写，注意罚时累加。

最后由于 $t_{i,j}\le10^6$，而总罚时是平方量级的，所以要开 `long long`。
## 代码
以下是关键代码：
```cpp
long long t,n,m,h,b[200005],c[200005];
int main() {
	cin>>t;
	while(t--) {
		cin>>n>>m>>h;
		long long a[n+1][m+1];
		for(long long i=1;i<=n;i++) for(long long j=1;j<=m;j++) cin>>a[i][j];
		for(long long i=1;i<=n;i++) {
			sort(a[i]+1,a[i]+m+1);
			b[i]=c[i]=0;
			long long cnt=0; 
			for(long long j=1;j<=m;j++) {
				if(cnt+a[i][j]<=h) b[i]++,cnt+=a[i][j],c[i]+=cnt;
				else break;
			}
		}
		long long id=1;
		for(long long i=2;i<=n;i++) {
			if(b[i]>b[1]) id++;
			else if(b[i]==b[1]) if(c[i]<c[1]) id++;
		}
		cout<<id<<"\n";
	}
    return 0;
}
```
由于比赛时打得匆忙，所以代码可能写得不好看，请见谅。

---

## 作者：引领天下 (赞：2)

题意：

给定 $n$ 个人做 $m$ 个题的时间分布情况，计算在所有人都按最优顺序做题的情况下，第 $1$ 个人的排名。

做法：

贪心。

既然最后的排名只与做出来的题目数量和罚时有关，那么显然应该先做耗时短的。这个策略可以同时保证做的题最多且罚时最少。

具体实现上，手写一个排序就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,m,h;
vector<int>T;
inline bool cmp(pair<int,int>p,pair<int,int>q){
    if(p.first!=q.first)return p.first>q.first;
    else return p.second<q.second;//分数降序，时间升序
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--){
        vector<pair<int,int>>q;
        cin>>n>>m>>h;
        int s0,t0;
        for(int i=1;i<=n;i++){
            T.resize(m+1);
            for(int j=1;j<=m;j++)cin>>T[j];
            sort(T.begin(),T.end());
            int s=0,t=0,sumt=0;
            for(int j=1;j<=m;j++)if(h>=t+T[j])s++,t+=T[j],sumt+=t;//注意罚时的计算是累加的
            q.push_back(make_pair(s,sumt));
            if(i==1)s0=s,t0=sumt;
        }
        sort(q.begin(),q.end(),cmp);
        cout<<(find(q.begin(),q.end(),make_pair(s0,t0))-q.begin()+1)<<endl;
    }
    return 0;
}
```

---

## 作者：sgl654321 (赞：0)

### 题目大意
- 有 $n$ 个人打一场有 $m$ 道题的比赛，这场比赛共有 $h$ 分钟。给出第 $i$ 个人完成第 $j$ 道题的时间 $t_{i,j}$。其中第一个人是 Rudolf。
- 这场比赛的规则是：首先比较完成的题数，题数多的获胜。如果题数相同，则比较**罚时**。其中**罚时**的定义为：完成每一道题的**时刻**之和。罚时少的获胜。
- 每个人都会最合理地安排答题顺序，使得自己的名次尽可能高。特别地，如果一个人的题数和罚时都和 Rudolf 相同，那么 Rudolf 的名次会在他之上。
- 请输出 Rudolf 最终的名次。

### 解题思路
显然，每个人会优先完成自己使用时间少的题目。下面给出一种证明方法。

我们假设有 $3$ 道题目，小 A 完成它们需要的时间分别是 $a_1,a_2,a_3$。其中，$a_1\le a_2\le a_3$。我们下面说明以 $1,2,3$ 的顺序完成一定不劣于以 $1,3,2$ 的顺序完成。

1. 若 $a_1+a_2\le h$，而 $a_1+a_3>h$，那么第一种完成方式的题数一定大于第二种完成方式，显然更优。
2. 若两者都能至少完成两题，那么完成这前两题的罚时和分别是：第一种 $f_1=a_1+(a_1+a_2)=2a_1+a_2$，第二种 $f_2=a_1+(a_1+a_3)=2a_1+a_3$。$f_1$ 显然比 $f_2$ 小。

以此类推，可说明优先完成使用时间少的题目，这一贪心策略是正确的。

那么我们只需要对第 $i$ 个人完成每道题的时间进行排序，然后求出他们分别能做几道题，并相应计算罚时即可。

最后再按照题意进行人名次的排序。输出 Rudolf 的名次就行了。
### 参考代码
1. 观察数据范围 $n\times m\le2\cdot10^5$，可以看出我们需要使用可变长度数组 ```vector```。
2. 最终按照题意对人名次排序时，我们可以记录下原来每个人的编号 $id$。当两个人的题数和罚时都一样时，$id$ 小的名次靠前。这样，就能让 Rudolf 的名次高于其余和他题数和罚时相同的人了。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	long long num,tim,id;
}b[200010];
long long tt,n,m,h,x,now;
vector<long long>a[200010],sum[200010];
bool cmp(node n1,node n2){
	if(n1.num>n2.num)return 1;
	if(n1.num<n2.num)return 0;
	if(n1.tim<n2.tim)return 1;
	if(n1.tim>n2.tim)return 0;
	return n1.id<n2.id;
}
int main(){
	cin>>tt;
	while(tt--){
		cin>>n>>m>>h;
		for(int i=1;i<=n;i++){
			a[i].clear();
			sum[i].clear();
			b[i].num=b[i].tim=0;
		}
		
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				cin>>x;
				a[i].push_back(x);
			}
			
		for(int i=1;i<=n;i++)
			sort(a[i].begin(),a[i].end());
		for(int i=1;i<=n;i++){
			now=0;
			for(int j=0;j<m;j++)
				if(a[i][j]+now<=h){
					b[i].num++;
					now+=a[i][j];
				}
		}
		for(int i=1;i<=n;i++){
			sum[i].push_back(a[i][0]);
			for(int j=1;j<m;j++)
				sum[i].push_back(sum[i][j-1]+a[i][j]);
		
		}
		for(int i=1;i<=n;i++)
			for(int j=0;j<b[i].num;j++)
				b[i].tim+=sum[i][j];
		for(int i=1;i<=n;i++)b[i].id=i;
		sort(b+1,b+1+n,cmp);
		for(int i=1;i<=n;i++)
			if(b[i].id==1){
				cout<<i<<endl;
				break;
			}
	}
	return 0;
}
```


---

## 作者：_sunkuangzheng_ (赞：0)

**【题目分析】**

可以证明，先做耗时小的题是每个选手的最佳决策。显然这样做的题最多，罚时会最少。我们这样计算出每个选手的最优题数与罚时，排序即可。

本题细节略多。

**【代码】**
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t,n,m,x,h;
vector<int> a[200005];
struct per{
    int p,t,id;
}b[200005];
bool cmp(per a,per b){
    return (a.p == b.p ? (a.t == b.t ? a.id < b.id : a.t < b.t) : a.p > b.p);
}
signed main(){
    cin >> t;
    while(t --){
        cin >> n >> m >> h;
        for(int i = 1;i <= n;i ++) b[i].t = b[i].p = 0,a[i].clear();
        for(int i = 1;i <= n;i ++) for(int j = 1;j <= m;j ++) cin >> x,a[i].push_back(x);
        for(int i = 1;i <= n;i ++){
            sort(a[i].begin(),a[i].end());
            int tmp = h;b[i].id = i;int s = 0;
            for(int j = 0;j < m;j ++) if(tmp >= a[i][j]) s+=a[i][j],tmp -= a[i][j],b[i].p ++,b[i].t += s;
        }
        sort(b+1,b+n+1,cmp);
        // for(int i = 1;i <= n;i ++){
        //     cout << b[i].id << " " << b[i].p << " " << b[i].t << endl;
        // }
        for(int i = 1;i <= n;i ++) if(b[i].id == 1) {cout << i << endl;break;}   
    }
    return 0;
}
```

---

## 作者：Coffee_zzz (赞：0)

语法题。

### 分析

首先考虑如何求最优情况下的得分和罚时。

每道题的权重是相同的，那我们一定是先考虑做耗时少的题。

我们将这些题按耗时从小到大排序。

我们从 $1$ 到 $m$ 枚举 $j$，如果某一时刻 $\sum\limits_{k=1}^j t_{i,k}\gt h$，即前 $j$ 题的耗时之和大于 $h$，说明题做不完了，只能做完 $j-1$ 题，那就把第 $i$ 个选手的得分设为 $j-1$，直接退出循环。如果他可以做完所有题，那么就把他的得分设为 $m$ 即可。

某个选手一道题的罚时等于这个选手之前做的所有题（包括这道题）的耗时之和，我们设 $p_{i,j}$ 为选手 $i$ 第 $j$ 题的罚时，则 $p_{i,j}=\sum\limits_{k=1}^j t_{i,k}$。

那这个选手的总罚时就为所有做出来的题的罚时之和。

接下来是求排名。我们把每个选手的得分、罚时、编号都存到结构体里，以每个选手的得分从大到小排序，若得分相同则以罚时从小到大排序，若罚时也相同就随意。但要注意如果是和 $1$ 号选手比的话要把 $1$ 号选手放在前面，因为题目中说：

> It will be assumed that in case of a tie in points and penalty, Rudolf will take the best place.

输出答案时，我们找 $1$ 号选手，输出它的下标即可。

要注意题目只说 $n \cdot m \le 2 \cdot 10^5$，还是多组测试，要注意空间的回收利用。我们发现处理完一个选手的得分和罚时后，他做每道题的耗时都没有用了，下一个选手直接覆盖掉就可以。

### 代码

```c++
const int N=2e5+5;
struct Nod{
	int p,m,id;
}nod[N];
bool cmp(Nod a,Nod b){
	if(a.p==b.p){
		if(a.m==b.m) return a.id<b.id;
		return a.m<b.m;
	}
	return a.p>b.p;
}
int t[N],sum[N];
void solve(){
	int n=read(),m=read(),h=read();
	for(int i=1;i<=n;i++){
		int res=0,k;
		for(int j=1;j<=m;j++) t[j]=read();
		sort(t+1,t+1+m);
		for(int j=1;j<=m;j++) sum[j]=sum[j-1]+t[j];
		for(k=1;k<=m;k++){
			if(sum[k]>h) break;
			res=res+sum[k];
		}
		nod[i].p=k,nod[i].m=res,nod[i].id=i;
	}
	sort(nod+1,nod+1+n,cmp);
	for(int i=1;i<=n;i++){
		if(nod[i].id==1){
			cout<<i<<endl;
			return;
		}
	}
}
```

---

