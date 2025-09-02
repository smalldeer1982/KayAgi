# Pick Heroes

## 题目描述

Don't you tell me what you think that I can be



If you say that Arkady is a bit old-fashioned playing checkers, you won't be right. There is also a modern computer game Arkady and his friends are keen on. We won't discuss its rules, the only feature important to this problem is that each player has to pick a distinct hero in the beginning of the game.

There are $ 2 $ teams each having $ n $ players and $ 2n $ heroes to distribute between the teams. The teams take turns picking heroes: at first, the first team chooses a hero in its team, after that the second team chooses a hero and so on. Note that after a hero is chosen it becomes unavailable to both teams.

The friends estimate the power of the $ i $ -th of the heroes as $ p_i $ . Each team wants to maximize the total power of its heroes. However, there is one exception: there are $ m $ pairs of heroes that are especially strong against each other, so when any team chooses a hero from such a pair, the other team must choose the other one on its turn. Each hero is in at most one such pair.

This is an interactive problem. You are to write a program that will optimally choose the heroes for one team, while the jury's program will play for the other team. Note that the jury's program may behave inefficiently, in this case you have to take the opportunity and still maximize the total power of your team. Formally, if you ever have chance to reach the total power of $ q $ or greater regardless of jury's program choices, you must get $ q $ or greater to pass a test.

## 说明/提示

In the first example the first turn is yours. In example, you choose $ 6 $ , the other team is forced to reply with $ 2 $ . You choose $ 5 $ , the other team chooses $ 4 $ . Finally, you choose $ 3 $ and the other team choose $ 1 $ .

In the second example you have the second turn. The other team chooses $ 6 $ , you choose $ 5 $ , forcing the other team to choose $ 1 $ . Now you choose $ 4 $ , the other team chooses $ 3 $ and you choose $ 2 $ .

## 样例 #1

### 输入

```
3 1
1 2 3 4 5 6
2 6
1

2

4

1
```

### 输出

```




6

5

3
```

## 样例 #2

### 输入

```
3 1
1 2 3 4 5 6
1 5
2
6

1

3
```

### 输出

```





5

4

2
```

# 题解

## 作者：jianhe (赞：5)

[CF1056C Pick Heroes](https://www.luogu.com.cn/problem/CF1056C) 题解

题解同步发表于 [CSDN](https://blog.csdn.net/weixin_38337678/article/details/136131651?spm=1001.2014.3001.5501)~

## 引入：

洛谷题解中要么代码没放，要么代码很长很繁琐。因此我来交一发代码量只有 1008 B 的题解。

## 算法：贪心

考虑这种博弈题常用的思考方式：分类讨论**先后手**。

### 先手：

注意到题目中说每对仇敌必须一起选。因为我们要保留先手的优势，所以我们应当先选择每对英雄中战斗力最强的。

之后，再选择剩余英雄中战斗力最强的即可。

### 后手：

如果交互库选择了仇敌中的一个，那么只能选与之相匹配的英雄。

否则，我们就获得了先手，之后便和先手策略一致了。

### 数据结构：

因为我们要维护战斗力最强的英雄，所以可以用 `set` 或者 `priority_queue`。这里我选择了 `set`，因为 `set` 可以很方便地删除其中的任意元素。

## 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=2e3+10;
ll n,m,op,t,c,a[N],b[N],p[N],l[N],x[N];
bool vis[N];
multiset<pair<ll,ll> > q; 
void first(){
	for(int i=1;i<=m;i++)
		if(!vis[i]){
			cout<<(p[a[i]]>p[b[i]]?a[i]:b[i])<<"\n";
    		fflush(stdout); 
    		cin>>t;
    		q.erase({-p[a[i]],a[i]});
    		q.erase({-p[b[i]],b[i]});
		}	
	while(!q.empty()){
		cout<<(*q.begin()).second<<"\n";
		q.erase(q.begin());
		fflush(stdout); 
		if(!q.empty()){cin>>t;q.erase({-p[t],t});}		
	}
}
int main(){
    cin>>n>>m;c=m;
    for(int i=1;i<=n*2;i++) cin>>p[i],q.insert({-p[i],i});
    for(int i=1;i<=m;i++) cin>>a[i]>>b[i],l[a[i]]=b[i],l[b[i]]=a[i],x[a[i]]=x[b[i]]=i;
    cin>>op;
    if(op==1) first();
	else
		for(int i=1;i<=n;i++){
			cin>>t;
			q.erase({-p[t],t});
			if(l[t]&&q.find({-p[l[t]],l[t]})!=q.end()){
				cout<<l[t]<<"\n";
				fflush(stdout); 
				q.erase({-p[l[t]],l[t]});vis[x[t]]=1;
			}else{first();break;}
		}
	return 0;
}

```



![](https://cdn.luogu.com.cn/upload/image_hosting/fc72q28j.png)

代码很短，只有 $41$ 行。

怎么样？点个赞再走吧~

---

## 作者：fish_love_cat (赞：2)

显然的没有仇敌关系直接根据贡献从大到小拿就好了。

---

那么关于仇敌关系：

因为仇敌关系的存在，导致某方的操作可以对另一方下一步的操作产生直接影响。

因为所有的都要取完，所以仇敌关系的两边我们必须拿走一个。

因为要使分数最大化，所以我们在可以的情况下应选择**仇敌关系中贡献大的一方**。

因为敌人不一定给你留下大的，所以应积极在仇敌关系选择中**争取主动**。

---

接下来就按着没仇敌关系的方法做就完了。

注意全程被动时可能死循环。

代码（后附 Hack）：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct fish{
    int x,id;
    bool f;
}a[2005];
struct cat{
    int x,y;
    bool f;
}b[1005];
bool cmp(fish x,fish y){
    return x.x>y.x;
}
int main(){
    int n,m,t;
    cin>>n>>m;
    for(int i=1;i<=2*n;i++)cin>>a[i].x,a[i].id=i,a[i].f=0;
    for(int i=1;i<=m;i++)cin>>b[i].x>>b[i].y,b[i].f=0;
    cin>>t;
    int love=0;
    while(t==2&&love++<=m){
        int x,i;
        cin>>x;
        a[x].f=1;
        for(i=1;i<=m;i++)
        if(b[i].x==x){
            cout<<b[i].y<<endl;
            b[i].f=1;
            a[b[i].y].f=1;
            break;
        }else if(b[i].y==x){
            cout<<b[i].x<<endl;
            b[i].f=1;
            a[b[i].x].f=1;
            break;
        }
        if(i==m+1)break;
    }
    for(int i=1;i<=m;i++){
        if(b[i].f)continue;
        a[b[i].x].f=1;
        a[b[i].y].f=1;
        if(a[b[i].x].x>a[b[i].y].x)cout<<b[i].x<<endl;
        else cout<<b[i].y<<endl;
        int x;
        cin>>x;
    }
    sort(a+1,a+1+2*n,cmp);
    for(int i=1;i<=2*n;i++){
        if(a[i].f)continue;
        a[i].f=1;
        cout<<a[i].id<<endl;
        int x;
        cin>>x;
        for(int j=i+1;j<=2*n;j++)
        if(a[j].id==x){
            a[j].f=1;
            break;
        }
    }
    return 0;
}
/*
TLE on #18
hack:
	input:
	2 2
	1 2 3 4
	1 2
	3 4
	2
	1
	3
	AC:
	2
	4
	TLE/OLE:
	2
	4
	4
	4
	4
	...
*/
```

[记录](https://www.luogu.com.cn/record/164414606)。

---

注意到上述做法是 $O(n^2)$ 的，不够优秀。

我们可以使用 `map` 记录坐标，从而达到优化的目的。

还有一些火车头之类的奇技淫巧可以用上，复杂度 $O(n\log n)$。

代码有点长，放[这里](https://www.luogu.com.cn/paste/eouil77p)了。

[记录](https://www.luogu.com.cn/record/164460997)。

~~不过在这么小的数据范围下好像优化的不多……~~

---

## 作者：Miraik (赞：2)

**题意简述**

**交互题。**

有 $2n$ 位英雄，每位英雄有一个战力 $p_i$，你和交互器轮流选择英雄。这些英雄中有 $m$ 对仇敌，当自己的仇敌被选择时，这位英雄必须立刻被另一位玩家选择。先后手由交互器决定，试最大化你选择英雄的战力和。

数据范围：$1\le n\le 10^3,0\le m \le n,1\le p_i \le 10^3,1\le a_i,b_i \le 2n,a_i \not= b_i$。

**简要题解**

挺简单的交互题，也挺有意思。

容易发现先手具有主动权，因此先考虑先手怎么做。

### 先手

发现仇敌之间是互相限制的状态，显然我们可以先将 $m$ 对仇敌解决掉，每次选择战力更高的那位。显然这样做完以后我们最大化了 $m$ 对仇敌中选择的战力和，并且这 $m$ 次选择可以看作为 **“先手权利”**，选完之后依然处于先手状态。然后每次选择剩余的英雄中战力最大的那一位。容易证明没有更优的方案。

### 后手

如果交互库选择了有仇敌的英雄，我们只能选择他的仇敌。

如果交互库选择了没有仇敌的英雄，那么我们可以任意选择，此时就回到了先手问题，直接按照先手方案解决即可。

然后就做完了。代码不难实现，就不放了（其实是我写的太乱了

---

## 作者：zhanghaosong (赞：0)

# CF1056C Pick Heroes

### 题型

交互题。如果您对交互题非常了解，请移步下方“思路”区。

即你与交互库进行“对话”，你和交互库轮流“发言”，知道某一时刻 `return 0`。

你的“发言”以 `cout` 的形式输给交互库。交互库的“发言”需要你 `cin` 进来。

此外，你 `cout` 后需要 `fflush(stdout)`，即清空缓冲区，不然有可能因为数据读不完而 TLE。

特别地，使用 `std::cout<<endl;` 也可清空缓冲区（~~这就是为什么 `endl` 这么慢~~）

推荐完成：[P1733 猜数（IO交互版）](https://www.luogu.com.cn/problem/P1733)，[~~P9477 [_-0 C] 猜数~~](https://www.luogu.com.cn/problem/P9477)

### 思路

你是先手，你可以对**具有仇敌关系**的英雄排序，然后选择这里面最厉害的英雄。

相对地，交互库会选择~~她~~的仇敌。

你还可以选择剩下最厉害的英雄，以此类推。

剩下没有仇敌关系的英雄，排序并依次选取最大值即可。

### 代码

代码请大家自己实现！

---

## 作者：封禁用户 (赞：0)

## 题目描述

[Pick Heroes](https://www.luogu.com.cn/problem/CF1056C)

有 $n \times 2$ 位英雄，第 $i$ 位英雄的战力为 $p_i$，你和交互库轮流选择英雄组成队伍，$t = 1$ 时你先手，$t = 2$ 时交互库先手。

英雄之间存在 $m$ 对仇敌 $a_i,b_i$（保证每位英雄至多只出现一次），一旦一位玩家选择了第 $a_i$ 位英雄，那么另一位玩家必须 **立即** 选择第 $b_i$ 位英雄；同理，一位玩家选择了第 $b_i$ 位英雄，那么另一位玩家必须立即选择第 $a_i$ 位英雄。

队伍的总战力即为队伍内所有英雄战力之和。

尝试找到最佳策略，最大化你队伍的总战力。

数据范围：

$1\le n\le 10^3,0\le m \le n,1\le p_i \le 10^3,1\le a_i,b_i \le 2n,a_i \not= b_i$。

## 思路

分类讨论：

- **先手**

发现我选了仇敌中的一个，交互库就必须选另一个，显然我们可以先选一对仇敌中战力大的一个，让交互库选战力小的。这样就可以最大化自己队的战力，最小化交互库队的战力。如果把仇敌选完了，就选目前剩余战力最大的英雄。

- **后手**

如果交互库选了仇敌中的一个，我们只能选另一个。直到交互库没有选了仇敌中的一个或仇敌被选完了，就变成了**先手**问题。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct st
{
	ll now,id;
	st(){}
	st(ll _now,ll _id)
	{
		now=_now;
		id=_id;
	}
	friend bool operator < (st a,st b)
	{
		if(a.now==b.now)
		{
			return a.id<b.id;
		}
		return a.now<b.now;
	}
};
const ll N=1010;
ll n,m,k,x,tmpid,a[N*2];
priority_queue<st> heap;
pair<ll,ll> dis[N*2];
bool flag[N*2];
ll find(ll x)
{
	for(int i=1;i<=m;i++)
	{
		if(dis[i].first==x&&!flag[dis[i].second])
		{
			return i;
		}
		if(dis[i].second==x&&!flag[dis[i].first])
		{
			return i;
		}
	}
	return 0;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n*2;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=m;i++)
	{
		cin>>dis[i].first>>dis[i].second;
	}
	for(int i=1;i<=n*2;i++)
	{
		heap.push({a[i],i});
	}
	cin>>k;
	if(k==1)
	{
		for(int i=1;i<=m;i++)
		{
			if(a[dis[i].first]<a[dis[i].second])
			{
				swap(dis[i].first,dis[i].second);
			}
			cout<<dis[i].first<<endl<<endl;
			cin>>x;
			flag[dis[i].first]=true;
			flag[x]=true;
		}
		while(heap.size())
		{
			while(heap.size()&&flag[heap.top().id])
			{
				heap.pop();
			}
			if(!heap.size())
			{
				break;
			}
			cout<<heap.top().id<<endl<<endl;
			cin>>x;
			flag[heap.top().id]=true;
			flag[x]=true;
		}
	}
	else
	{
		for(int i=1;i<=n;i++)
		{
			cin>>x;
			flag[x]=true;
			tmpid=find(x);
			if(tmpid)
			{
				if(dis[tmpid].first==x)
				{
					cout<<dis[tmpid].second<<endl<<endl;
					flag[dis[tmpid].second]=true;
				}
				else
				{
					cout<<dis[tmpid].first<<endl<<endl;
					flag[dis[tmpid].first]=true;
				}
			}
			else
			{
				bool vis=false;
				for(int i=1;i<=m;i++)
				{
					if(!flag[dis[i].first]&&!flag[dis[i].second])
					{
						vis=true;
						if(a[dis[i].first]<a[dis[i].second])
						{
							swap(dis[i].first,dis[i].second);
						}
						cout<<dis[i].first<<endl<<endl;
						flag[dis[i].first]=true;
						break;
					}
				}
				if(!vis)
				{
					while(heap.size()&&flag[heap.top().id])
					{
						heap.pop();
					}
					cout<<heap.top().id<<endl<<endl;
					flag[heap.top().id]=true;
				}
			}
		}
	}
	return 0;
}
```

---

## 作者：FReQuenter (赞：0)

## 思路

### 分两种情况讨论：

### 先手：

显然，通过选一对仇敌关系之中的一个，可以确定让交互库选另一个。所以，先选所有仇敌关系中 $p_i$ 较大的一方，是最优策略；仇敌关系处理完之后，只需依次选没选过的 $p_i$ 中的最大值，而交互库就只能选次大，以此类推。

策略：先选所有仇敌关系中 $p_i$ 较大的一方，选完后每次选剩余 $p_i$ 中最大的，知道选完为止。

### 后手：

如果交互库选了仇敌关系中的一员，那么只能选这个仇敌关系中的另一个；如果交互库没有那么做，那主动权就落到了我们手里：相当于我们是先手。那么只要和先手一样继续做就行了。

策略：如果交互库选了仇敌关系中的一个，则选另一个；否则：先选剩余仇敌关系中 $p_i$ 较大的一方，选完后每次选剩余 $p_i$ 中最大的，知道选完为止。

本题数据范围较小，如果要找没有选的最大的 $p_i$ 或没有选的仇敌关系，直接遍历即可，时间复杂度 $O(n^2)$。同样，可以用 `map` 等 STL 或一些数据结构维护，是时间复杂度达到 $O(n\log n)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define endl endl<<endl
using namespace std;
int n,m,t,p[2005];
pair<int,int> dis[1005];
bool cho[2005];
struct node{
    int num,idx;
    node(){}
    node(int _num,int _idx){
        num=_num;
        idx=_idx;
    }
    friend bool operator < (node a,node b){
        if(a.num!=b.num) return a.num<b.num;
        return a.idx<b.idx;
    }
};
int fnd(int x){
    for(int i=1;i<=m;i++){
        if((dis[i].fi==x&&!cho[dis[i].se])
         ||(dis[i].se==x&&!cho[dis[i].fi])) return i;
    }
    return 0;
}//找第一个没有选的
//其实可以用map维护，但是容易写挂（我很懒的
signed main(){
    cin>>n>>m;
    for(int i=1;i<=n*2;i++) cin>>p[i];
    for(int i=1;i<=m;i++) cin>>dis[i].fi>>dis[i].se;
    cin>>t;
    priority_queue<node> q;
    for(int i=1;i<=n*2;i++){
        q.push(node(p[i],i));
    }
    if(t==1){//先手
        for(int i=1;i<=m;i++){
            if(p[dis[i].fi]<p[dis[i].se]) swap(dis[i].fi,dis[i].se);
            cout<<dis[i].fi<<endl;
            int x;
            cin>>x;
            cho[x]=cho[dis[i].fi]=true;
            //优先使用仇敌关系
        }
        while(!q.empty()){
            while(!q.empty()&&cho[q.top().idx]) q.pop();
            if(q.empty()) break;
            cout<<q.top().idx<<endl;
            cho[q.top().idx]=true;
            int x;
            cin>>x;
            cho[x]=true;
        }//找最大
    }
    if(t==2){
        for(int i=1;i<=n;i++){
            int x;
            cin>>x;
            cho[x]=true;
            int tmp=fnd(x);
            if(tmp){
                if(dis[tmp].fi==x){
                    cho[dis[tmp].se]=true;
                    cout<<dis[tmp].se<<endl;
                }
                else{
                    cho[dis[tmp].fi]=true;
                    cout<<dis[tmp].fi<<endl;
                }
                //如果是仇敌关系中的一员
            }
            else{
                bool chod=false;
                for(int i=1;i<=m;i++){
                    if(!cho[dis[i].fi]&&!cho[dis[i].se]){
                        chod=true;
                        if(p[dis[i].fi]<p[dis[i].se]) swap(dis[i].fi,dis[i].se);
                        cout<<dis[i].fi<<endl;
                        cho[dis[i].fi]=true;
                        break;
                        //如果还有仇敌关系
                    }
                }
                if(!chod){
                    while(!q.empty()&&cho[q.top().idx]) q.pop();
                    cout<<q.top().idx<<endl;
                    cho[q.top().idx]=true;
                    //没有了仇敌关系，找最大
                }
            }
        }
    }
    return 0;
}
```

---

