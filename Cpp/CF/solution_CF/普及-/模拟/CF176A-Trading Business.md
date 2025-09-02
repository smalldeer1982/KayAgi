# Trading Business

## 题目描述

To get money for a new aeonic blaster, ranger Qwerty decided to engage in trade for a while. He wants to buy some number of items (or probably not to buy anything at all) on one of the planets, and then sell the bought items on another planet. Note that this operation is not repeated, that is, the buying and the selling are made only once. To carry out his plan, Qwerty is going to take a bank loan that covers all expenses and to return the loaned money at the end of the operation (the money is returned without the interest). At the same time, Querty wants to get as much profit as possible.

The system has $ n $ planets in total. On each of them Qwerty can buy or sell items of $ m $ types (such as food, medicine, weapons, alcohol, and so on). For each planet $ i $ and each type of items $ j $ Qwerty knows the following:

- $ a_{ij} $ — the cost of buying an item;
- $ b_{ij} $ — the cost of selling an item;
- $ c_{ij} $ — the number of remaining items.

It is not allowed to buy more than $ c_{ij} $ items of type $ j $ on planet $ i $ , but it is allowed to sell any number of items of any kind.

Knowing that the hold of Qwerty's ship has room for no more than $ k $ items, determine the maximum profit which Qwerty can get.

## 说明/提示

In the first test case you should fly to planet Venus, take a loan on 74 units of money and buy three items of the first type and 7 items of the third type ( $ 3·6+7·8=74 $ ). Then the ranger should fly to planet Earth and sell there all the items he has bought. He gets $ 3·9+7·9=90 $ units of money for the items, he should give 74 of them for the loan. The resulting profit equals 16 units of money. We cannot get more profit in this case.

## 样例 #1

### 输入

```
3 3 10
Venus
6 5 3
7 6 5
8 6 10
Earth
10 9 0
8 6 4
10 9 3
Mars
4 3 0
8 4 12
7 2 5
```

### 输出

```
16```

# 题解

## 作者：yedalong (赞：4)

## 思路
通过题目可以发现，此题可以用贪心来做。由于题目说你只能在任意两个星球间进行一次购买并卖出，因此难度降了许多。数据小，可以直接暴力枚举 $i$ 和 $j$，然后计算出对于在 $i$ 号星球买东西，$j$ 号星球卖东西的最大收益，用 $ans$ 存最大值。
## AC code:
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#define int long long
using namespace std;
struct node{
	int cnt,k;//cnt 表示当前这个物品的收益，k 表示当前这个物品的个数
};
int n,m,k,a[15][105],b[15][105],c[15][105],ans;
bool cmp(node a,node b){
	return a.cnt>b.cnt;//贪心思想，优先买收益最大的物品
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>k;
	for(int i = 1;i<=n;i++){
		string s;cin>>s;//这个星球名字没用，这里用 i 来表示
		for(int j = 1;j<=m;j++) cin>>a[i][j]>>b[i][j]>>c[i][j];
	}
	for(int i = 1;i<=n;i++){
		for(int j = 1;j<=n;j++){
			if(j==i) continue;//星球一样，跳过
			vector<node> v;//这里 vector 可以改成数组
			int cnt=0,sum=0;//sum 用来存收益最大值，cnt 用来存当前买了多少个物品
			for(int l = 1;l<=m;l++) v.push_back(node{b[j][l]-a[i][l],c[i][l]});//算出每件物品的收益
			sort(v.begin(),v.end(),cmp);
			for(int l = 0;l<v.size();l++){
				if(v[l].cnt<=0) break;//cnt 是从大到小排序的，对于收益为负数的物品，买了没用，直接跳出循环
                if(cnt+v[l].k<k) sum+=v[l].k*v[l].cnt,cnt+=v[l].k;//对于可以全部买完的情况
				else{//剩下能买多少全买这个物品
					sum+=(k-cnt)*v[l].cnt;
					break;//已经买完 k 个物品了，结束
				}
			}
			ans=max(ans,sum);//取最大值
		}
	}
	cout<<ans;
  return 0;//完结撒花
} 
```
~~都看完了，点个赞呗~~

---

## 作者：wangcht (赞：1)

## 题目大意：
对于 $n$ 个星球中的任意两个星球，你可以在其中一个上进一批货物，再卖到另一个星球，在每一个星球购买的物品总数不能超过 $k$，求最大收益。

## 分析：
本题是标准的贪心加枚举，显然，我们要想多赚钱，就要优先卖差价高的货物。

可以先用两重循环枚举星球，用结构体存储每种货物的信息，再按差价的高低排序，然后计算在这两星球间买卖的最大收益，最后在最大收益中求最大值即可。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,maxans;
int a[15][105],b[15][105],c[15][105];
string t;
struct node
{
	int w,s;
}x[105];
/*
bool operator<(node a,node b)
{
	return a.w>b.w;
}
*/
bool cmp(node a,node b)
{
	return a.w>b.w;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>t;
		for(int j=1;j<=m;j++)
			cin>>a[i][j]>>b[i][j]>>c[i][j];
	}
	for(int i=1;i<=n;i++)//在哪买 
		for(int j=1;j<=n;j++)//在哪卖 
		{
			int sum=k,ans=0;//最多还能买多少，收益 
			if(i==j) continue;
			for(int o=1;o<=m;o++)
			{
				x[o].w=b[j][o]-a[i][o];
				x[o].s=c[i][o];
			}
			sort(x+1,x+m+1,cmp);
			for(int o=1;o<=m;o++)
			{
				if(x[o].w<=0) break;
				if(x[o].s>=sum)
				{
					ans+=sum*x[o].w;
					break;
				}
				else
				{
					sum-=x[o].s;
					ans+=x[o].s*x[o].w;
				}
			}
			maxans=max(maxans,ans);
		}
	cout<<maxans;
	return 0;
}
```

---

## 作者：Aventurine_stone (赞：1)

## 1. 题目分析
这道题 $n$ 和 $m$ 都很小，一眼暴力枚举。
## 2. 题目做法
首先，星球名字没有任何作用。此题限制我们只能在两个星球间贸易，所以我们只能依次枚举买入星球和卖出星球。  
然后，以卖出与买入的差价为关键字从大到小进行排序，可以用快排。然后统计这两星球间的最大收益。  
最后，在所用最大收益中取最大值，即是答案。
## 3. 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=110;
inline int read()
{
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
		x=(x<<1)+(x<<3)+c-'0',c=getchar();
	return x;
}
int n,m,k;
string s;
int a[N][N],b[N][N],c[N][N];
struct object{
	int cha,num;
}d[N];
inline bool cmp(object a1,object a2)
{
	return a1.cha>a2.cha;
}
int sum,ans,x;
int main()
{
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;i++)
	{
		cin>>s;
		for(int j=1;j<=m;j++)
			a[i][j]=read(),b[i][j]=read(),c[i][j]=read();
	}
	for(int i=1;i<=n;i++)//买入星球 
	{
		for(int j=1;j<=n;j++)//卖出星球 
		{
			sum=0,x=k;
			if(i==j)
				continue;
			for(int k=1;k<=m;k++)
				d[k].num=c[i][k],d[k].cha=b[j][k]-a[i][k];
			sort(d+1,d+m+1,cmp);
			for(int k=1;k<=m;k++)
			{
				if(d[k].cha>0)
				{
					if(x>d[k].num)
					{
						sum+=d[k].cha*d[k].num;
						x-=d[k].num;
					}
					else
					{
						sum+=d[k].cha*x;
						break;
					}
				}
				else
					break; 
			}
			ans=max(ans,sum);
		}
	}
	printf("%d ",ans);
	return 0;
}
```

---

## 作者：Night_sea_64 (赞：1)

[CF176A 题目传送门](https://www.luogu.com.cn/problem/CF176A)

这道题主要是贪心。

首先枚举在哪个星球买，在哪个星球卖。然后就开始贪心。我们肯定更喜欢赚的钱更多的物品。这样贪心策略就出来了：把赚的钱数按从大到小排序，优先选赚的钱数更多的物品。如果当前这个物品全选了还不到 $k$ 个，就全选然后继续选下一个物品；否则选择 $k-cnt$ 个这个物品，然后结束（$cnt$ 是当前已经选了的个数）。

在这个过程中我们需要排序，所以我们可以用结构体。就这么简单，AC 代码：

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
struct g{int x,y,z,id;}a[15][110];
//x,y,z 分别表示题目中的 a,b,c。id 表示物品的编号。
bool cmp1(g x,g y){return x.y>y.y;}
bool cmp2(g x,g y){return x.id<y.id;}
int main()
{
    int n,m,k;
    cin>>n>>m>>k;
    string s;
    for(int i=1;i<=n;i++)
    {
        cin>>s;//字符串没用，随便输入一个就行了
        for(int j=1;j<=m;j++)
        {
            cin>>a[i][j].x>>a[i][j].y>>a[i][j].z;
            a[i][j].id=j;
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++)//i 枚举买物品的星球
        for(int j=1;j<=n;j++)//j 枚举卖物品的星球
        {
            for(int p=1;p<=m;p++)//p 枚举物品
                a[j][p].y-=a[i][p].x;//卖的价格减去买的价格等于赚的价格
            sort(a[j]+1,a[j]+m+1,cmp1);
            int cnt=0,sum=0;
            for(int p=1;p<=m;p++)
            {
                if(a[j][p].y<=0)break;
                int q=a[j][p].id;
                if(i==j)q=p;//q 表示排序后的第 p 个物品在 a[i] 的下标。
                if(cnt+a[i][q].z<k)cnt+=a[i][q].z,sum+=a[i][q].z*a[j][p].y;
                else
                {
                    sum+=(k-cnt)*a[j][p].y;
                    break;
                }
            }
            ans=max(ans,sum);
            sort(a[j]+1,a[j]+m+1,cmp2);
            for(int p=1;p<=m;p++)
                a[j][p].y+=a[i][p].x;//记得还原回去
        }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：frankchenfu (赞：1)

这是一道比较基础的贪心题目。

------------
首先，我们可以发现题目中的数据范围都比较小，又因为只有一次买卖，所以我们可以同时枚举起点和终点，对于每一对起点和终点做一次`solve(s,t)`。

------------
那么这个`solve(s,t)`怎么实现呢？由于确定了起点和终点，也就意味着确定了差价。这样，我们考虑买的越多一定越好，所以我们尽量每次都买尽可能多的能赚钱的东西，就是把还未尝试过的种类中，差价最大的买空为止，一直到买满$k$种或者没有差价大于$0$的产品时退出，这样一定是最优的。**注意细节**。

------------
`Cpp`代码：
```cpp
#include<cstdio>
#include<cstring>
int n,m,k;
int a[15][110],b[15][110],c[15][110];
bool vis[110];char ch[15];

int max(int x,int y){
	return x>y?x:y;
}
int min(int x,int y){
	return x<y?x:y;
}
int solve(int s,int t){
	memset(vis,0,sizeof(vis));
	int rest=k,ans=0;
	while(rest>0){
		bool fl=1;
		int mx=-1,pos;
		for(int i=1;i<=m;i++)
			if(!vis[i])
				if(b[t][i]-a[s][i]>mx){
					fl=0;pos=i;
					mx=b[t][i]-a[s][i];
				}
		if(fl)
			break;
		int num=min(rest,c[s][pos]);
		rest-=num;
		ans+=num*mx;
		vis[pos]=1;
	}
	return ans;
}

int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++){
		scanf("%s",ch);
		for(int j=1;j<=m;j++)
			scanf("%d%d%d",&a[i][j],&b[i][j],&c[i][j]);
	}
	int ans=-1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			ans=max(ans,solve(i,j));
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：__hjwucj__ (赞：0)

# 题解：CF176A Trading Business

[题目传送门](/problem/CF176A)

## 思路

考虑贪心。

这题其实就是部分背包问题的板子。没做过的[戳这里](https://www.luogu.com.cn/problem/P2240)。我们枚举两个星球，接着使用部分背包求这个两个星球的最优解，接着打个擂台就行了。

## 代码


讲了思路，代码就很简单了，就不放了。

---

## 作者：a18981826590 (赞：0)

# [Trading Business](https://www.luogu.com.cn/problem/CF176A)
## 解题思路
这道题主要运用**贪心**的思想。

枚举购买的星球和销售的星球，对进价 $a$ 和售价 $b$ 的差价也就是利润进行降序排序，从最大的开始买。如果买了之后总数未超过 $k$，就把库存 $c$ 买完，并把剩余可购买数减去 $c$；否则把剩余可购买数买完，记录利润和。但是，利润可能为负数，要在利润 $\le 0$ 时跳出循环。

最后取总利润的最大值即可。
## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[20][110],b[20][110],c[20][110],l,m,n,o,p,s,t,u;
struct d{
	int e,f;
}g[110];
string z;
bool h(d x,d y){
	return x.e>y.e;
}
int main(){
	cin>>n>>m>>l;
	for(int i=0;i<n;i++){
		cin>>z;
		for(int j=0;j<m;j++) cin>>a[i][j]>>b[i][j]>>c[i][j];
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			for(int k=0;k<m;k++){
				g[k].e=b[j][k]-a[i][k];
				g[k].f=k;
			}
			stable_sort(g,g+m,h);
			o=l;
			p=t=0;
			while(o){
				if(c[i][g[p].f]>o){
					t+=g[p].e*o;
					break;
				}
				if(g[p].e<=0) break;
				t+=g[p].e*c[i][g[p].f];
				o-=c[i][g[p++].f];
			}
			s=max(s,t);
		}
	}
	cout<<s;
	return 0;
}
```

---

## 作者：__bjxx0201__ (赞：0)

## 题目大意

星系中有 $n$ 个星球，对于每一个星球你可以购买东西和销售东西。购买需要花费 $a_{ij}$ 元，售出可以收入 $a_{ij}$ 元。对于一个星球你不能够买超过 $k$ 次东西。

题目请我们试求出最大收益。

## 思路

[题目传送门](https://www.luogu.com.cn/problem/CF176A)

考虑到贪心的做法。

我们要想出在哪个星球买、哪个星球卖出东西可以使得收益最大。

我们将需要付的价格按照从小到大的顺序排序（为了选出更优的商品），选择“性价比”高的（可以赚钱多的）的商品，排序。然后一个个枚举，对于第 $i$ 个商品，如果资金不足以买完或者买不到 $k$ 个，就去挑选第 $i+1$ 个物品；如果能够买完，就将该物品买完。这样一定是最优的策略。

---

