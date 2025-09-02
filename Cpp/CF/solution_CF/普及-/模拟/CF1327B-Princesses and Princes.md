# Princesses and Princes

## 题目描述

The King of Berland Polycarp LXXXIV has $ n $ daughters. To establish his power to the neighbouring kingdoms he wants to marry his daughters to the princes of these kingdoms. As a lucky coincidence there are $ n $ other kingdoms as well.

So Polycarp LXXXIV has enumerated his daughters from $ 1 $ to $ n $ and the kingdoms from $ 1 $ to $ n $ . For each daughter he has compiled a list of kingdoms princes of which she wanted to marry.

Polycarp LXXXIV is very busy, so he finds a couple for his daughters greedily one after another.

For the first daughter he takes the kingdom with the lowest number from her list and marries the daughter to their prince. For the second daughter he takes the kingdom with the lowest number from her list, prince of which hasn't been taken already. If there are no free princes in the list then the daughter marries nobody and Polycarp LXXXIV proceeds to the next daughter. The process ends after the $ n $ -th daughter.

For example, let there be $ 4 $ daughters and kingdoms, the lists daughters have are $ [2, 3] $ , $ [1, 2] $ , $ [3, 4] $ , $ [3] $ , respectively.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1327B/50ce2d8ac0f6b682008f6274aa8cfbc6afc16be3.png)In that case daughter $ 1 $ marries the prince of kingdom $ 2 $ , daughter $ 2 $ marries the prince of kingdom $ 1 $ , daughter $ 3 $ marries the prince of kingdom $ 3 $ , leaving daughter $ 4 $ nobody to marry to.

Actually, before starting the marriage process Polycarp LXXXIV has the time to convince one of his daughters that some prince is also worth marrying to. Effectively, that means that he can add exactly one kingdom to exactly one of his daughter's list. Note that this kingdom should not be present in the daughter's list.

Polycarp LXXXIV wants to increase the number of married couples.

Unfortunately, what he doesn't have the time for is determining what entry to add. If there is no way to increase the total number of married couples then output that the marriages are already optimal. Otherwise, find such an entry that the total number of married couples increases if Polycarp LXXXIV adds it.

If there are multiple ways to add an entry so that the total number of married couples increases then print any of them.

For your and our convenience you are asked to answer $ t $ independent test cases.

## 说明/提示

The first test case is depicted in the statement. Adding the fourth kingdom to the list of the fourth daughter makes her marry the prince of the fourth kingdom.

In the second test case any new entry will increase the number of marriages from $ 0 $ to $ 1 $ .

In the third and the fourth test cases there is no way to add an entry.

In the fifth test case there is no way to change the marriages by adding any entry.

## 样例 #1

### 输入

```
5
4
2 2 3
2 1 2
2 3 4
1 3
2
0
0
3
3 1 2 3
3 1 2 3
3 1 2 3
1
1 1
4
1 1
1 2
1 3
1 4```

### 输出

```
IMPROVE
4 4
IMPROVE
1 1
OPTIMAL
OPTIMAL
OPTIMAL```

# 题解

## 作者：Happy_Dream (赞：2)

相当水的一道贪心题。
说起贪心就必须有贪心策略，这道题的贪心策略又是什么呢？其实很显然就是能匹配的就匹配，匹配不了就往下一个匹配，如果都匹配不了，那么很显然我们就可以输出IMPROVE。但是我们怎么找谁能匹配呢，由于题面说了，要找编号小的，所以我们只需要。从小到大查询一边就可以啦。

但为什么这样是正确的呢？显然，只有能匹配的都配了，才能是最优的，所以这样做，挨个算，一定可以做到这样，所以就可以$AC$啦！复杂度$O(T*N)$,可以通过本题.

可是怎么做到去重呢，我们只需要维护一个桶即可。

MY CODE:
```
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		int k[n+5];
		int b[n+5]={0};
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			cin>>k[i];
			int fla=0;
			for(int j=1;j<=k[i];j++)
			{
				int x;
				cin>>x;
				if(b[x]==0&&fla==0)//尝试匹配
				{
					b[x]++;//匹配过的就记录下来
					fla=1;
				}
			}
			if(fla==0)
			ans=i;//记录到底可不可以
		}
		if(!ans)
		{
			cout<<"OPTIMAL \n";
			continue;
		}
		cout<<"IMPROVE \n";
		for(int i=1;i<=n;i++)
		{
			if(b[i]==0)
			{
				cout<<ans<<" "<<i<<endl;
				break;
			}
		}//枚举每个人是否没有匹配
	} 
	return 0;
}
```

---

## 作者：AutumnKite (赞：1)

我这个彩笔又看错题了...

题目里说只要能够增加就行...而我以为要取增加最多的方案...

那么只要模拟一遍以后，如果存在一个没有匹配的公主，任选一个王子与她匹配即可。

如果需要「增加最多」，这样构造是否正确呢 QAQ

有没有神仙来证明一下或者给出一个反例啊 QAQ

```cpp
const int N = 100005;
int n, vis[N];
std::vector<int> E[N];
void solve(){
	read(n);
	for (register int i = 1; i <= n; ++i)
		vis[i] = 0, E[i].clear();
	for (register int i = 1, k; i <= n; ++i){
		read(k);
		for (register int j = 0, x; j < k; ++j)
			read(x), E[i].push_back(x);
	}
	int add_x = 0, add_y = 0;
	for (register int i = 1; i <= n; ++i){
		bool flag = 0;
		for (register int j = 0; j < (int)E[i].size(); ++j)
			if (!vis[E[i][j]]){ vis[E[i][j]] = 1, flag = 1; break; }
		if (flag || add_x) continue;
		add_x = i;
	}
	if (!add_x) prints("OPTIMAL");
	else{
		add_y = n;
		while (vis[add_y]) --add_y;
		prints("IMPROVE"), print(add_x, ' '), print(add_y);
	}
}
```

---

## 作者：do_while_true (赞：1)

## 题目翻译

国王有 $n$ 个公主，要嫁给 $n$ 个邻国的王子，每个公主都有自己想要嫁出去的名单(可以重复)，从第一个公主开始嫁，嫁给 出现次数最多的且没有被其他姐妹占领的王子，若有多个则为编号最小的那个。若没有则嫁不出去。

现在国王有一次给其中一位公主的名单增加一个名字的机会，但是要保证增加的这个名字在公主原先的名单里面没有出现过。

每次询问国王是否能通过增加一个名字来多嫁出去公主，若可以，第一行输出$\texttt{IMPROVE}$，第二行输出两个整数，分别表示国王在第几个公主的名单上，加的是几号王子。若不可以输出$\texttt{OPTIMAL}$。

## 题目分析

十分简单甚至无脑的模拟，但是要求的代码实现能力很高。

我们先借一组样例来模拟一下题意。

有$4$个公主，名单分别为$[2,3] , [1,2] , [3, 4] , [3]$

首先第$1$个公主出嫁，$2$和$3$都出现了一次，则选择较小的$2$。

第$2$个公主出嫁，$1$和$2$都出现了一次，选择较小的$1$。

第$3$个公主出嫁，$3$和$4$都出现了一次，选择较小的$4$。

第$4$个公主出嫁，$3$出现了一次，但是$3$已被其他公主占领，这时候只有$4$还没有公主，则国王将$4$号公主的名单加上$4$号王子，$4$号公主成功嫁到$4$号王子。

所以输出为第一行$\texttt{IMPROVE}$，第二行为4 4。


------------

我们来分析题目，首先能嫁出去的肯定就不需要再增添名单了，我们先统一处理一遍，把能嫁出去的直接嫁出去。

如果所有公主都嫁出去了，则国王再添加名单就没有用了，输出$\texttt{OPTIMAL}$。

如果有的公主没嫁出去，国王随便挑一个没嫁出去的公主，给她的名单上加一个没有公主的王子，这样就能改善了。所以如果有的公主没有嫁出去，输出$\texttt{OPTIMAL}$，并输出一个没有王子的公主的编号，和一个没有公主的王子的编号。

具体方法在代码里

## Code:
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int T,n,k,x,y,maxdis,maxpos,mindis,minpos,cnt,ans1,ans2,sum1,sum2,a[100001];
bool f=0,vis[100001],vis2[100001];
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			vis[i]=vis2[i]=0;
		//vis[i]代表第i个王子有没有公主，vis2[i]代表第i个公主有没有王子 
		sum1=sum2=ans1=ans2=0;
		//sum1代表的是匹配成功的情侣对数 
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&k);
			for(int j=1;j<=k;j++) scanf("%d",&a[j]);
			maxdis=maxpos=0;
			cnt=1;
			//cnt代表当前的数出现了几次
			//maxdis代表出现最多的且没有公主的王子编号的出现次数
			//maxpos代表编号 
			for(int j=1;j<=k;j++)
			{
				if(a[j]==a[j-1]) cnt++;//如果和上一个相同，则出现次数+1 
				else cnt=1;
				if(cnt>maxdis&&!vis[a[j]]){
					//如果这个王子没有公主，并且出现次数比前面的王子出现次数多，就更改 
					maxdis=cnt;
					maxpos=a[j];
				}
			}
			if(!vis[maxpos]&&maxpos) vis[maxpos]=vis2[i]=1,sum1++;
			//如果当前公主匹配成功，就标记下来匹配成功的一对。 
		} 
		if(sum1!=n)//如果有公主没有嫁出去 
		{
			for(int i=1;i<=n;i++)
				if(!vis2[i]){
					ans1=i;
					break;
				}//找一个没有嫁出去的公主 
			for(int i=1;i<=n;i++)
				if(!vis[i]){
					ans2=i;
					break;
				}//找一个没有公主的王子 
		}
		if(ans1&&ans2) printf("IMPROVE\n%d %d\n",ans1,ans2);//如果找到了可以更改的一对，就输出 
		else puts("OPTIMAL");//没有找到 
	}
}
```

---

## 作者：Andrewzdm (赞：0)

# [CF1327B Princesses and Princes](https://www.luogu.com.cn/problem/CF1327B)

刚开始确实没有想到这道题模拟就可以了。

我们首先按照国王的规则包办婚姻，然后看看有没有~~剩男剩女~~未能配对的王子和公主，把它们配对就OK了。如果所有公主都嫁出去了，答案就是`OPTIMAL`。

但是这样有一个问题：题目里说了这样一句话（还特别加粗）
> **Note that this kingdom should not be present in the daughter's list.**

后来我想了想发现这是*废话*！！！如果有未能配对的王子和公主，那么这个王子一定不是公主喜欢的人。

反证法：假如这个王子出现在了公主喜欢的人的列表中，且这个公主没有嫁出去，这个王子也没有娶任何一个公主，那么这个公主和王子就一定可以配对，矛盾。

~~所以题目这句话有点坑~~

最后我们的代码就很简洁了：
```cpp
#include<bits/stdc++.h>
#define endl '\n'//一般输出规模超过10^5最好用'\n'换行
using namespace std;
const int maxn = 100010;
bool used[maxn], choosed[maxn];
//分别为王子和公主

int main()
{
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
	while(t--)
	{
		int n;
		cin >> n;
		fill(used + 1, used + n + 1, false);
        fill(choosed + 1, choosed + n + 1, false);
		for(int i = 1; i <= n; i++)
		{
			int k;
			cin >> k;
			bool flag = false;
			for(int j = 1; j <= k; j++)
			{
				int x;
				cin >> x;
				if(!flag && !used[x])
				{
					used[x] = true;
					choosed[i] = true;
					flag = true;
				}
			}
		}
		bool flag = false;
		for(int i = 1; i <= n; i++)
			if(!used[i])
			{
				for(int j = 1; j <= n; j++)
					if(!choosed[j])
					{
						cout << "IMPROVE" << endl << j << ' ' << i << endl;
						flag = true;
						break;
					}
				if(flag)
					break;
			}
		if(!flag)
			cout << "OPTIMAL" << endl;
	}
	return 0;
}
```
时间复杂度是 $O(n)$。

因为只要有一个没配对的王子，就必然有一个没配对的公主。

~~吐槽下题意翻译，叫王子和公主多好~~

---

## 作者：dead_X (赞：0)

## 1 题意简述
~~二分图匹配~~

有 $n$ 个公主和王子，每个公主依次选择她喜欢并且没有结婚的王子结婚，问能不能让一个公主再多喜欢一个王子，使得最终配对的对数更多。
## 2 思路简述
如果所有公主都配上了，那么显然最优

不然先配一遍找一个没配上的公主去喜欢一个没配上的王子，这一对即为最优解。显然如果不是所有公主都配上了，必然会有一个没配上的公主和一个没配上的王子。
## 3 代码
```
#include<bits/stdc++.h>
using namespace std;
bool a[100003],b[100003];
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n,t,k;
		scanf("%d",&n);
		for(int i=1; i<=n; i++) 
		{
			bool f=1;
			scanf("%d",&k);
			
			for(int j=1; j<=k; j++)
			{
				scanf("%d",&t);
				if((!a[t]) &&f) {
					b[i]=a[t]=1;
					f=0;
			    } 
		}
	}
	int x=0,y=0;
	for(int i=1; i<=n; i++) if(!a[i]) 
	{
		x=i; break;
	}
	for(int i=1; i<=n; i++) if(!b[i])
	{
		y=i; break;
	}
	if(x && y)
	printf("IMPROVE\n%d %d\n",y,x);
	else printf("OPTIMAL\n");
	for(int i=1; i<=n; i++) a[i]=b[i]=0;
	}
	return 0;
}
```
## 4 评价
屑题面

然后x，y写反WA一发

完美避开小号一场上蓝

---

## 作者：gyh20 (赞：0)

贪心。

先找到每个公主匹配的王子，如果全部匹配，那么就是最优的。

否则找出一个未匹配的公主和未匹配的王子，将这个王子加入公主的名单即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
#define int long long
inline int read(){
	re int t=0;
	re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int t,n,m,a[100002],c[100002],k,x,lst;
signed main(){
	t=read();
	while(t--){
		n=read();for(re int i=1;i<=n;++i)c[i]=0;lst=0;
		for(re int i=1;i<=n;++i){
			k=read();bool pp=0;
			for(re int j=1;j<=k;++j){
				re int x=read();
				if(!pp&&!c[x]){
					pp=c[x]=1;
				}
			}
			if(!pp)lst=i;
		}
		if(lst){
			for(re int i=1;i<=n;++i){
				if(!c[i]){
				printf("IMPROVE\n%d ",lst);printf("%d\n",i);break;}
			}
		}
		else{
			puts("OPTIMAL");
		}
	}
}
```


---

