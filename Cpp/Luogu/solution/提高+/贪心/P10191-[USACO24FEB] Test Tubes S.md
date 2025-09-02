# [USACO24FEB] Test Tubes S

## 题目描述

Bessie 最近开始对化学感兴趣。目前，她有两种不同颜色 $1$ 和 $2$ 的液体，彼此之间无法混合。她有两个无限容量的试管，各装有 $N$（$1\le N\le 10^5$）单位的这两种颜色的液体混合物。由于液体无法混合，一旦沉淀，它们就会分成不同颜色的层。因此，两个试管可以被视为两个字符串 $f_1f_2\ldots f_N$ 和 $s_1s_2\ldots s_N$，其中 $f_i$ 表示距离第一个试管底部 $i$ 单位处的液体的颜色，$s_i$ 表示距离第二个试管底部 $i$ 单位处的液体的颜色。输入保证两种颜色的液体至少各有一个单位。

Bessie 想要分离这些液体，以使得每个试管包含一种颜色的液体的所有单位。她有第三个无限容量的空烧杯来帮助她完成这一任务。当 Bessie 进行一次「倾倒」时，她将一个试管或烧杯顶部的所有颜色为 $i$ 的液体移至另一个的顶部。

求出将所有液体分离到两个试管中所需的最小的倾倒次数，以及所需的移动操作。两个试管最终包含的液体颜色不影响正确性，但烧杯必须是空的。

有 $T$（$1\le T\le 10$）个测试用例，每个测试用例有一个参数 $P$。

设将液体分离至试管中的最小倾倒次数为 $M$。

- 若 $P=1$，当你仅输出 $M$ 时可以得到分数。
- 若 $P=2$，当你输出 $A$，其中 $M\le A\le M+5$，并在以下 $A$ 行输出以该操作次数构造的一个方案时，可以得到分数。每一行包含来源试管和目标试管（$1$，$2$，或用 $3$ 表示烧杯）。操作之前，来源试管必须是非空的，并且不得将一个试管向其自身倾倒。
- 若 $P=3$，当你输出 $M$，并输出以该操作次数构造的一个方案时，可以得到分数。

## 说明/提示

### 样例解释

在前三个测试用例中，分离试管的最小倾倒次数为 $4$。我们可以看到以下操作是如何分离试管的：

初始状态：

```plain
1: 1221
2: 2211
3: 
```

在操作 `1 2` 后：

```plain
1: 122
2: 22111
3: 
```

在操作 `1 3` 后：

```plain
1: 1
2: 22111
3: 22
```

在操作 `2 1` 后：

```plain
1: 1111
2: 22
3: 22
```

在操作 `3 2` 后：

```plain
1: 1111
2: 2222
3:
```

在最后一个测试用例中，最小倾倒次数为 $5$。然而，由于 $P=2$，给出的 $6$ 次操作的构造也是合法的，因为它与最优解的差在 $5$ 次倾倒之内。

### 测试点性质

- 测试点 $2-6$：$P=1$。
- 测试点 $7-11$：$P=2$。
- 测试点 $12-21$：没有额外限制。

除此之外，输入保证除样例外的所有测试点均有 $T=10$。

## 样例 #1

### 输入

```
6
4 1
1221
2211
4 2
1221
2211
4 3
1221
2211
6 3
222222
111112
4 3
1121
1222
4 2
1121
1222```

### 输出

```
4
4
1 2
1 3
2 1
3 2
4
1 2
1 3
2 1
3 2
1
2 1
5
2 3
1 2
1 3
1 2
3 1
6
2 3
1 2
1 3
1 2
2 1
3 2```

# 题解

## 作者：Jerrywang09 (赞：5)

这道题看上去毫无头绪，其实考察的是乱搞的勇气。

第一步想到去重。然后用三个栈维护三个试管 $a,b,c$。然后怎么搞呢？

先考虑一些平凡的情况。如果 $a$ 的栈顶和 $b$ 的栈顶相同，则根据两个栈的大小，选择消去 $a$ 的栈顶或 $b$ 的栈顶。如果 $c$ 为空，则选择 $a,b$ 中较大的一个栈，弹出栈顶，放入 $c$ 试管中。如果 $a,c$ 或 $a,b$ 的栈顶相同，则可以消去 $a$ 或 $b$ 的栈顶。

不难发现，上述过程只有在 $c$ 为空时才会加入，因此 $c$ 的栈内元素个数不超过 $1$。

再考虑一些边界。如果 $a,b$ 大小都为 $1$ 且两个栈顶元素不同，则要把 $c$ 清空，大功告成。如果 $a,b$ 中有一个为空，假设 $a$ 为空。如果 $b$ 只有一个元素了，把 $c$ 倒给 $a$，大功告成。否则弹出 $b$ 的栈顶给 $a$。$b$ 为空的情况同理。

看上去上述策略都很符合直觉，但我感觉赛时很难写出代码。

```cpp
// Title:  Test Tubes
// Source: USACO24FEB Silver
// Author: Jerrywang
#include <bits/stdc++.h>
#define F first
#define S second
#define pii pair<int, int>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cerr<<#x<<":"<<x<<endl;
const int N=1000010;
using namespace std;

int n, p; pii res[N]; int cnt=0;

void solve()
{
    cnt=0; scanf("%d%d", &n, &p);
    stack<int> a, b, c;
    rep(i, 1, n)
    {
        int x; scanf("%1d", &x);
        if(a.empty() || x!=a.top()) a.push(x);
    }
    rep(i, 1, n)
    {
        int x; scanf("%1d", &x);
        if(b.empty() || x!=b.top()) b.push(x);
    }
    while(1)
    {
        if(a.size()==1 && b.size()==1 && a.top()!=b.top())
        {
            if(c.empty()) break;
            if(a.top()==c.top()) res[++cnt]={3, 1};
            if(b.top()==c.top()) res[++cnt]={3, 2};
            break;
        }
        if(a.empty())
        {
            if(b.size()==1) {res[++cnt]={3, 1}; break;}
            a.push(b.top()), b.pop(), res[++cnt]={2, 1};
        }
        else if(b.empty())
        {
            if(a.size()==1) {res[++cnt]={3, 2}; break;}
            b.push(a.top()), a.pop(), res[++cnt]={1, 2};
        }
        else if(a.size() && b.size() && a.top()==b.top())
        {
            if(a.size()>b.size()) a.pop(), res[++cnt]={1, 2};
            else b.pop(), res[++cnt]={2, 1};
        }
        else if(c.empty())
        {
            if(a.size()>b.size()) c.push(a.top()), a.pop(), res[++cnt]={1, 3};
            else c.push(b.top()), b.pop(), res[++cnt]={2, 3};
        }
        else if(a.size() && a.top()==c.top())
            a.pop(), res[++cnt]={1, 3};
        else if(b.size() && b.top()==c.top())
            b.pop(), res[++cnt]={2, 3};
    }
    printf("%d\n", cnt);
    if(p>1) rep(i, 1, cnt) printf("%d %d\n", res[i].F, res[i].S);
}

int main()
{
    #ifdef Jerrywang
    freopen("E:/OI/in.txt", "r", stdin);
    #endif
    int T; scanf("%d", &T);
    while(T--) solve();
    
    return 0;
}
```

---

## 作者：Lame_Joke (赞：4)

- ### 大体思路

  题目大家应该都能看懂，这里就不做过多解释了。
  题目说一次倾倒就会把连续的一段相同的液体倒出，那么不如把连续的一段相同液体看成一个单位的液体，当然，这个读入的时候就能处理，然后为了方便判断是否达到目标，我们在倾倒过程中把融到一起的一段液体看成一个单位的液体，类似于消消乐，这样是不是就简单多了。然后我们发现三种操作的答案其实都可以用一段代码来得出。

  这类游戏相信大家也都玩过，这里有一个一定是最少次数的策略：

      1. 当两根试管的顶端相等时，将液体多的对液体少的进行倾倒操作。

      2. 如果有一个试管空了，那么另一个试管对其进行倾倒操作。

      3. 如果那个无限容量的烧杯不是空的，那么就用两根试管中顶端与烧杯顶端液体相同的对烧杯进行倾倒操作。

      4. 如果那个无限容量的烧杯是空的，那么就用两根试管中液体多的对烧杯进行倾倒操作

  注意：以上操作是按优先级排列的。

  最后，当两根试管中的液体单位都小于等于 $1$ 时，就能结束了。

  但是我们发现有时候两根试管中的液体会相同，且烧杯还没空，这里稍加操作就能解决。

- ### 参考代码

  ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int t,n,m,q;
  int z1[500005],cnt1,cnt2,z2[500005],cnt3,z3[500005],ans=0,ans1[1000005][2];
  char ch;
  int main()
  {
  	scanf("%d",&t);
  	while(t--)
  	{
  		cnt1=0;
  		cnt2=0;
  		cnt3=0;
  		scanf("%d%d",&n,&m);
  		for(int i=1;i<=n;i++)
  		{
  			ch=getchar();
  			while(ch!='1'&&ch!='2') ch=getchar();
  			if(ch-'0'!=z1[cnt1]) z1[++cnt1]=ch-'0';
  		}
  		for(int i=1;i<=n;i++)
  		{
  			ch=getchar();
  			while(ch!='1'&&ch!='2') ch=getchar();
  			if(ch-'0'!=z2[cnt2]) z2[++cnt2]=ch-'0';
  		}											//输入时将相同的合并 
  		ans=0;
  		while(!(cnt1<=1&&cnt2<=1))
  		{
  			ans++;
  			if(z1[cnt1]==z2[cnt2])					//两个试管的顶部相同 
  			{										//多的向少的倾倒 
  				if(cnt1<=cnt2)
  				{
  					cnt2--;
  					ans1[ans][0]=2;
  					ans1[ans][1]=1;
  				} 
  				else
  				{
  					cnt1--;
  					ans1[ans][0]=1;
  					ans1[ans][1]=2;
  				}
  			}
  			else if(cnt2==0)						//有试管是空的 
  			{										//另一根试管向其倾倒 
  				z2[++cnt2]=z1[cnt1];
  				cnt1--;
  				ans1[ans][0]=1;
  				ans1[ans][1]=2; 
  			}
  			else if(cnt1==0)
  			{
  				z2[++cnt1]=z1[cnt2];
  				cnt2--;
  				ans1[ans][0]=2;
  				ans1[ans][1]=1;
  				
  			}			
  			else
  			{
  				if(cnt3!=0)							//烧杯非空
  				{									//顶部与烧杯相等的向烧杯倾倒 
  					if(z1[cnt1]==z3[cnt3])				
  					{
  						cnt1--;
  						ans1[ans][0]=1;
  						ans1[ans][1]=3;
  					}
  					else
  					{
  						cnt2--;
  						ans1[ans][0]=2;
  						ans1[ans][1]=3;
  					}
  				}
  				else								//烧杯是空的
  				{									//液体多的向烧杯倾倒 
  					if(cnt1>=cnt2)
  					{
  						z3[++cnt3]=z1[cnt1];	
  						ans1[ans][0]=1;
  						ans1[ans][1]=3;
  						cnt1--;
  					}
  					else
  					{
  						z3[++cnt3]=z2[cnt2];
  						ans1[ans][0]=2;
  						ans1[ans][1]=3;	
  						cnt2--;
  					}
  				}
  			}
  		}
  		
  		if(z1[1]==z2[1])							//两根试管中液体相同 
  		{
  			ans1[++ans][0]=2;
  			ans1[ans][1]=1;
  			cnt2--;
  			z2[1]=(z1[1]==1?2:1);
  		}
  		
  		if(cnt3!=0)									//烧杯非空 
  		{
  			while(cnt3>0)
  			{
  				if(z3[cnt3]==z1[1]) ans1[++ans][0]=3,ans1[ans][1]=1;
  				else ans1[++ans][0]=3,ans1[ans][1]=2;
  				cnt3--;
  			}
  		}
  		
  		printf("%d\n",ans);
  		if(m!=1) for(int i=1;i<=ans;i++) printf("%d %d\n",ans1[i][0],ans1[i][1]);
  	}
  }
  ```

---

## 作者：bigclever (赞：3)

为行文方便，本文将试管 $1$ 记作 $A$，将试管 $2$ 记作 $B$，烧杯记作 $C$。
## 铺垫
1. 由于试管中连续的一段 $1$ 或 $2$ 必然可以**一起**进行操作，所以我们可以将这一段看成单独的 $1$ 个 $1$ 或 $1$ 个 $2$，从而减少操作次数并且更容易判断是否合法。

1. **最优情况**下 $C$ 中要么空，要么全是 $1$，要么全是 $2$。因为只有当 $A$ 和 $B$ 无法向另一方倾倒时，才需要让其中一方向 $C$ 倾倒。此时**必有一方**的顶部元素和 $C$ 的顶部元素一样，可以倾倒。而且这样能保证最终可以通过 $1$ 步操作将 $C$ 清空。
## 合法情况
满足下列三种情况之一即可：

- $A$ 空且 $B$ 中只有 $1$ 个元素（此时另一个不同的元素在 $C$ 中）。
- $B$ 空且 $A$ 中只有 $1$ 个元素（此时另一个不同的元素在 $C$ 中）。
- $A$ 和 $B$ 中均只有 $1$ 个元素且这两个元素不相同。
## 倾倒策略
由铺垫易知这是最优策略。

在仍不合法的情况下：
1. 若 $A$ 和 $B$ 中有一方为空，则将非空一方向另一方倾倒。
1. 若 $A$ 和 $B$ 的顶部元素相同，则将元素更多的一方向另一方倾倒。 
1. 否则 $A$ 和 $B$ 的顶部元素不相同，将顶部元素和 $C$ 的顶部元素相同的一方向 $C$ 倾倒。

注意上述操作按**优先级**排列。

（不存在 $A$ 和 $B$ 都空的情况，想一想为什么？）
## 思路
由于 $C$ 中最多只会有 $1$ 种元素，所以我们可以对 $C$ 中全为 $1$ 和全为 $2$ 分别进行两次模拟，最终取操作次数更少的操作序列即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define moo stack<int>
#define star vector<pair<int,int> >
star sol(moo a,moo b,int col){//col是C中的元素值
	star res;//操作序列
	bool use=false;//是否用C
	//while里面的判断条件不能写成函数，要不然会因为调用次数过多而TLE
	while(!(a.empty()&&b.size()==1||b.empty()&&a.size()==1||a.size()==1&&b.size()==1&&a.top()!=b.top())){
		if(a.empty())a.push(b.top()),b.pop(),res.push_back({2,1});
		else if(b.empty())b.push(a.top()),a.pop(),res.push_back({1,2});
		else if(a.top()==b.top()){
		    //因为此时A和B的顶部元素相同，所以往另一方倾倒相当于删除本方的顶部元素（详见铺垫1）
            if(a.size()>b.size())a.pop(),res.push_back({1,2});
			else b.pop(),res.push_back({2,1});
		}else{
			use=true;
			if(a.top()==col)a.pop(),res.push_back({1,3});
			else b.pop(),res.push_back({2,3});
		}
	}
	if(use){//如果用了C，那么最后还要把C中的元素倒回试管
		if(a.top()==col)res.push_back({3,1});
		else b.pop(),res.push_back({3,2});
	}
	return res;
}
int main() {
	int t;
	scanf("%d",&t);
	while(t--){
		int n,p,x;
		scanf("%d %d",&n,&p);
		moo a,b;//这里用栈来模拟试管
		for(int i=1;i<=n;i++){
			scanf("%1d",&x);//读1位整数
			if(a.empty()||x!=a.top())a.push(x);
		}
		for(int i=1;i<=n;i++){
			scanf("%1d",&x);
			if(b.empty()||x!=b.top())b.push(x);
		}
		star t1=sol(a,b,1),t2=sol(a,b,2),ans=(t1.size()<t2.size()?t1:t2);
		printf("%d\n",ans.size());
		if(p>1)
			for(auto i:ans)printf("%d %d\n",i.first,i.second);
	}
	return 0;
}
```

---

## 作者：MicroSun (赞：3)

赛时写出正解没交，写发题解纪念下/kk

在下文中，为了使文章更简短，将某个试管内元素的个数记为试管的「大小」；将某个试管的顶部元素记为试管的「顶」；将烧杯记为「试管 $3$」。

首先，考虑稍微将题目转换一下：

- 将所有连续的 $1$ 和 $2$ 化为一个 $1$ 或 $2$。

- 对于每次「倾倒」的转化：如果「倾倒」的试管的顶等于被「倾倒」试管的顶，则可以删除「倾倒」的试管的顶，否则将该元素复制到被「倾倒」试管的顶部。

- 当烧杯为空且 $1$ 试管和 $2$ 的大小均为 $1$，则操作结束。该方法的正确性显然。

进行了以上的转换后，就可以进行简单模拟了。

我们使用以下策略进行「倾倒」：

- 如果试管 $1$ 的顶等于试管 $2$ 的顶，则将试管 $1$ 和试管 $2$ 中的大小较大者对较小者进行一次「倾倒」。

- 否则如果为试管 $3$ 为空，则将试管 $1$ 和试管 $2$ 中的大小较大对试管 $3$ 进行一次「倾倒」。

- 否则将试管 $1$ 和试管 $2$ 中，顶与试管 $3$ 的顶相同的试管对试管 $3$ 进行一次「倾倒」。因为只有两种元素，此时试管 $1$ 和试管 $2$ 中一定有一个试管的顶与试管 $3$ 的顶相同。

正确性：

对于不需要对试管 $3$ 进行操作的情况，由于按照以上操作一定每一步会使试管 $1$ 的大小与试管 $2$ 的大小之和减 $1$。很明显不会存在更优的方法，因为每一步至多使以上值减 $1$。

对于需要对试管 $3$ 进行操作的情况，则需要多两步来对试管 $3$ 进行由空转换至一个元素和由一个元素转换为空。对于试管 $1$ 的底部与试管 $2$ 的底部相同的情况，还需要一步填充合并后的空位。这与上述步骤相符。

别忘了判断一步就可以结束的情况。

Code：

```cpp
// Problem: Problem 2. Test Tubes
// LuoguUID: 514700 
// LuoguUserName: MicroSun
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pb push_back
#define fst first
#define scd second
#define rep(i,s,e) for(int i=s;i<=e;i++)
#define dep(i,s,e) for(int i=s;i>=e;i--)

using ll=long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;

const int maxn=3e5+10;

pii ans[maxn];
int cnt;
void solve(){
	cnt=0;
	int n,t;
	cin>>n>>t;
	stack<int> s1,s2;
	int e1,e2;
	rep(i,1,n){
		char ch;
		cin>>ch;
		if(s1.empty()) e1=ch-'0';
		if(s1.empty()||ch-'0'!=s1.top())
			s1.push(ch-'0');
	}
	rep(i,1,n){
		char ch;
		cin>>ch;
		if(s2.empty()) e2=ch-'0';
		if(s2.empty()||ch-'0'!=s2.top())
			s2.push(ch-'0');
	}
	int s3=0;
	int lilun=s1.size()+s2.size()-1+(e1==e2);
	//lilun为理论最小值
	bool use_s3=0;
	while(1){
		if(s1.empty()&&s2.size()==2){
			s1.push(s2.top());
			s2.pop();
			ans[++cnt]={2,1};
		}
		else if(s2.empty()&&s1.size()==2){
			s2.push(s1.top());
			s1.pop();
			ans[++cnt]={1,2};
		}
		if(s1.empty()&&s2.size()==1){
			ans[++cnt]={3,1};
			break;
		}
		if(s2.empty()&&s1.size()==1){
			ans[++cnt]={3,2};
			break;
		}
		if(s1.size()==1&&s2.size()==1&&s1.top()!=s2.top()){
			if(!s3) break;
			else{
				if(s1.top()==s3){
					ans[++cnt]={3,1};
				}
				else{
					ans[++cnt]={3,2};
				}
				break;
			}
		}
		if(s1.top()==s2.top()){
			if(s1.size()>s2.size()){
				s1.pop();
				ans[++cnt]={1,2};
			}
			else{
				s2.pop();
				ans[++cnt]={2,1};
			}
		}
		else if(!s3){
			use_s3=1;
			if(s1.size()>s2.size()){
				s3=s1.top();
				s1.pop();
				ans[++cnt]={1,3};
			}
			else{
				s3=s2.top();
				s2.pop();
				ans[++cnt]={2,3};
			}
		}
		else{
			if(s1.top()==s3){
				s1.pop();
				ans[++cnt]={1,3};
			}
			else{
				s2.pop();
				ans[++cnt]={2,3};
			}
		}		
	}
	if(!use_s3) --lilun;
	//此时cnt一定等于lilun
	cout<<lilun<<endl;
	if(t!=1){
		rep(i,1,cnt){
			cout<<ans[i].fst<<' '<<ans[i].scd<<endl;
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t=1;
	cin>>t;
	while(t--) solve();
    return 0;
}
```

---

## 作者：cff_0102 (赞：1)

首先将所有连续相同的液体压缩成一个元素，接着考虑模拟每个操作，只需要对当前的所有可能情况分类讨论即可。显然的，烧杯中最多只会有一个元素。

1. 若试管 $1$ 为空：
   1. 若试管 $2$ 只有一个元素，那么此时只需要将烧杯中的元素倒到试管 $1$ 中即可结束操作。
   2. 若试管 $2$ 不止一个元素，那么可以把试管 $2$ 顶端的元素放到试管 $1$。因为如果先前我们一直按照最优策略行动，此时烧杯的元素不可能和试管 $2$ 顶端的相等。
2. 若试管 $1$ 只有一个元素：
   1. 若试管 $2$ 为空，那么此时只需要将烧杯中的元素倒到试管 $2$ 中即可结束操作。
   2. 若试管 $2$ 只有一个元素，那么：
      - 如果试管 $1$ 和试管 $2$ 中的元素相等，合并这两个元素。
      - 否则将烧杯中的元素（若有）倒到与其相同的那个试管即可结束操作。
   3. 若试管 $2$ 不止一个元素，那么：
      - 如果试管 $2$ 顶端的元素与试管 $1$ 的元素相等，把试管 $2$ 顶端的元素倒到试管 $1$。
      - 否则：
        - 如果烧杯的元素和烧杯 $1$ 的元素不相等（包括没有元素的情况），那么就把试管 $2$ 倒到烧杯里。
        - 否则，把试管 $1$ 倒到烧杯里，这样下一步就可以把试管 $2$ 顶端的元素放到试管 $1$ 了。
3. 若试管 $1$ 不止一个元素：
   1. 若试管 $2$ 为空，那么那么可以把试管 $1$ 顶端的元素放到试管 $2$。因为如果先前我们一直按照最优策略行动，此时烧杯的元素不可能和试管 $1$ 顶端的相等。
   2. 若试管 $2$ 只有一个元素，那么：
      - 如果试管 $1$ 顶端的元素与试管 $2$ 的元素相等，把试管 $1$ 顶端的元素倒到试管 $2$。
      - 否则：
        - 如果烧杯的元素和烧杯 $2$ 的元素不相等（包括没有元素的情况），那么就把试管 $1$ 倒到烧杯里。
        - 否则，把试管 $2$ 倒到烧杯里，这样下一步就可以把试管 $1$ 顶端的元素放到试管 $2$ 了。
   3. 若试管 $2$ 不止一个元素：
      - 若试管 $1$ 和试管 $2$ 顶端的元素相等，那么可以把元素更多的倒到元素更少的那个里面。
      - 否则，此时两个试管顶端的元素不相等。此时看烧杯中的元素，如果烧杯中有和试管 $1$ 顶端或试管 $2$ 顶端的元素相等的元素，那么把那个试管倒到烧杯即可。
      - 否则，因为试管 $1$ 和试管 $2$ 中的元素不同，而烧杯中的元素又和这两个不相等，说明此时烧杯为空，将元素更多的试管中的东西倒到烧杯中即可。

把所有步骤存下来，在最后按顺序输出即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int mian(){
    stack<int>a,b;int c=0;
    a.push(0);b.push(0);
    int n,p;cin>>n>>p;
    for(int i=1;i<=n;i++){
        char x;cin>>x;x-='0';
        if(x!=a.top())a.push(x);
    }
    for(int i=1;i<=n;i++){
        char x;cin>>x;x-='0';
        if(x!=b.top())b.push(x);
    }
    queue<pair<int,int>>o;
    while(1){
        int as=min(3,(int)a.size()),bs=min(3,(int)b.size());
        if(as==1){
            if(bs==2){
                o.push({3,1});
                break;
            }else if(bs==3){
                a.push(b.top());
                b.pop();
                o.push({2,1});
            }
        }else if(as==2){
            if(bs==1){
                o.push({3,2});
                break;
            }else if(bs==2){
                int at=a.top(),bt=b.top();
                if(at==bt){
                    b.pop();
                    o.push({2,1});
                    continue;
                }
                if(c==a.top()){
                    o.push({3,1});
                }else if(c==b.top()){
                    o.push({3,2});
                }
                break;
            }else if(bs==3){
                int at=a.top(),bt=b.top();
                if(at==bt){
                    o.push({2,1});
                    b.pop();
                }else{
                    if(c!=at){
                        c=bt;
                        b.pop();
                        o.push({2,3});
                    }else{
                        a.pop();
                        o.push({1,3});
                    }
                }
            }
        }else if(as==3){
            if(bs==1){
                b.push(a.top());
                a.pop();
                o.push({1,2});
            }else if(bs==2){
                int at=a.top(),bt=b.top();
                if(at==bt){
                    o.push({1,2});
                    a.pop();
                }else{
                    if(c!=bt){
                        c=at;
                        a.pop();
                        o.push({1,3});
                    }else{
                        b.pop();
                        o.push({2,3});
                    }
                }
            }else if(bs==3){
                int at=a.top(),bt=b.top();
                if(at==bt){
                    if(a.size()<b.size()){
                        o.push({2,1});
                        b.pop();
                    }else{
                        o.push({1,2});
                        a.pop();
                    }
                }else{
                    if(c==at){
                        o.push({1,3});
                        a.pop();
                    }else if(c==bt){
                        o.push({2,3});
                        b.pop();
                    }else{
                        if(a.size()<b.size()){
                            o.push({2,3});
                            c=bt;
                            b.pop();
                        }else{
                            o.push({1,3});
                            c=at;
                            a.pop();
                        }
                    }
                }
            }
        }
    }
    cout<<o.size()<<endl;
    if(p!=1){
        while(!o.empty()){
            pair<int,int>t=o.front();
            o.pop();
            cout<<t.first<<" "<<t.second<<endl;
        }
    }
    return 0;
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int t;cin>>t;
    while(t--)mian();
    return 0;
}
```

---

## 作者：huhaoming2011 (赞：1)

## 题目大意
给你三根试管（烧杯同样视为第三根试管），然后将三根试管不断倾倒（即将一根试管顶端的液体加入到另一根试管的顶端），直到前两根试管各只剩下一种液体，且第三根试管为空时，即为结束。求完成的最少次数的方案。
## 分析
很简单地可以想到为了方便计算，每次将相邻且种类相同的融为一个，这样既能减轻计算负担，还能节省空间。同时经过探究，可以发现，有一个贪心且一定能是最小的策略（按照优先级排列）：

1. 当前两根试管顶端液体种类相同，让多的一根试管向少的倾倒。
2. 当前两根试管有一根是空的，则让有的向无的倾倒。
3. 若第三根试管非空，则让前两根试管中与第三根试管顶端液体相同的试管对第三根试管倾倒；若第三根试管是空的，则让前两根试管中多的一根对第三根试管倾倒。

当最后第三根试管非空，再额外将其分配回去，若前两根试管颜色相同也要进行处理，最后输出答案。

## 代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+100;
const int MAXM=5e5+100;
int n,p,ans;
struct Stack {
	int q[MAXN],tp;
	inline void init(){tp=0;}
	inline int top(){return q[tp];}
	inline void push(int x){q[++tp]=x;}
	inline void pop(){tp--;}
	inline int size(){return tp;}
	inline bool empty(){return tp>0?false:true;}
}st;
//模拟第一根试管
struct Stack2 {
	int q[MAXN],tp;
	inline void init(){tp=0;}
	inline int top(){return q[tp];}
	inline void push(int x){q[++tp]=x;}
	inline void pop(){tp--;}
	inline int size(){return tp;}
	inline bool empty(){return tp>0?false:true;}
}st2;
//模拟第二根试管
struct Stack3 {
	int q[MAXN],tp;
	inline void init(){tp=0;}
	inline int top(){return q[tp];}
	inline void push(int x){q[++tp]=x;}
	inline void pop(){tp--;}
	inline int size(){return tp;}
	inline bool empty(){return tp>0?false:true;}
}st3;
//模拟烧杯，即我说的第三根试管
struct node {
	int st,en;
}a[MAXM];
//统计操作答案的
void work() {
  //只有任意试管（前两根）大于一才进行操作
	while(st.size()>1||st2.size()>1) {
      	//前两根试管液体种类相同
		if(!st.empty()&&!st2.empty()&&st.top()==st2.top()) {
			if(st.size()>=st2.size()) {  //多的向少的倾倒
				st.pop();
				a[ans+1].st=1,a[ans+1].en=2;
			}
			else {
				st2.pop();
				a[ans+1].st=2,a[ans+1].en=1;
			}
		}
		else if(st.empty()&&!st2.empty()) { //前两根试管中有空的
			st.push(st2.top());
			st2.pop();
			a[ans+1].st=2,a[ans+1].en=1;
		}
		else if(!st.empty()&&st2.empty()) {
			st2.push(st.top());
			st.pop();
			a[ans+1].st=1,a[ans+1].en=2;
		}
		else {  //第三根试管（烧杯）有时
			if(!st3.empty()) {
				if(st.top()==st3.top()) {
					st.pop();
					a[ans+1].st=1,a[ans+1].en=3;
				}
				else if(st2.top()==st3.top()) {
					st2.pop();
					a[ans+1].st=2,a[ans+1].en=3;
				}
			}  //第三根试管（烧杯）没有时
			else {
				if(st.size()<=st2.size()&&!st2.empty()) {
					st3.push(st2.top());
					st2.pop();
					a[ans+1].st=2,a[ans+1].en=3;
				}
				else if(!st.empty()){
					st3.push(st.top());
					st.pop();
					a[ans+1].st=1,a[ans+1].en=3;
				}
			}
		}
		ans++;
	}
}
int main() {
	int T;
	scanf("%d",&T);
	while(T--) {
		ans=0;
		st.init(),st2.init(),st3.init();
      //清空
		scanf("%d%d",&n,&p);
		char op=' ';
		char ch=getchar();
		while(ch<'0'||ch>'9') ch=getchar();
		while(ch>='0'&&ch<='9') {
			if(ch!=op) {
				st.push(ch-48);
				op=ch;
			}//不同再加入栈，下面一样
			ch=getchar();
		}
		op=' ';
		ch=getchar();
		while(ch<'0'||ch>'9') ch=getchar();
		while(ch>='0'&&ch<='9') {
			if(ch!=op) {
				st2.push(ch-48);
				op=ch;
			}
			ch=getchar();
		}
		work();
		if(st.top()==st2.top()) {
			a[++ans].st=2,a[ans].en=1;
			st2.pop();
			st2.q[1]=st.top()==1?2:1;
		}
		while(!st3.empty()) {
			if(st3.top()==st.top()) a[++ans].st=3,a[ans].en=1;
			else a[++ans].st=3,a[ans].en=2;
			st3.pop();
		}
     	//提到的额外操作
		printf("%d\n",ans);
		if(p>1) for(int i=1;i<=ans;i++) printf("%d %d\n",a[i].st,a[i].en);
      //根据题目需求输出
	}
	return 0;
}
```
### 感谢某Lame指导
### 谢谢观看

---

## 作者：Red_river (赞：1)

# 题目大意

这道题其实有点贪心加上分类讨论的东西，但是还是需要思考一下的。其重点就在于当你在每种情况时，你就需要思考你应该怎么做。

### 分类讨论

对于每种情况，我们有如下讨论：当底部元素一样时，显然我们应该把元素多的倒进元素少的里面，就可以当做使得一次移动个数最大就为最优解。然后当有管子为空时，就要把元素多的倒进空的里面。当前两种方案都不行时，就直接乱倒，也就是只要相同就行。

# code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ri register int
#define INF 2147483647
#define f(x,k,y,z) for(int x=k;x<=y;x+=z)
using namespace std;
const int N=1e5+100;
const int M=5e5+100;
int n,p,ans,sum,num;char jk,jk1;
int cnt,tot,dis[N][3],vis[N],wis[N],f[N];
struct stl{
	int a[N],zz;
	inline void in(){zz=0;}
	inline int end(){return a[zz];}
	inline void on(int x){a[++zz]=x;}
	inline void pop(){zz--;}
	inline int l(){return zz;}
	inline bool no(){return zz<=0;}
}q[5];//模拟管子
struct node{int st,en;}a[M];
void dfs()//分类讨论
{
	while(q[1].l()>1||q[2].l()>1)
	{
		if(!q[1].no()&&!q[2].no()&&q[1].end()==q[2].end())
		{
			if(q[1].l()>=q[2].l()) q[1].pop(),a[ans+1].st=1,a[ans+1].en=2;
			else q[2].pop(),a[ans+1].st=2,a[ans+1].en=1;
		}
		else if(q[1].no()&&!q[2].no()) q[1].on(q[2].end()),q[2].pop(),a[ans+1].st=2,a[ans+1].en=1;
		else if(!q[1].no()&&q[2].no()) q[2].on(q[1].end()),q[1].pop(),a[ans+1].st=1,a[ans+1].en=2;
		else
		{
			if(!q[3].no())
			{
				if(q[1].end()==q[3].end()) q[1].pop(),a[ans+1].st=1,a[ans+1].en=3;
				else if(q[2].end()==q[3].end()) q[2].pop(),a[ans+1].st=2,a[ans+1].en=3;
			}
			else
			{
				if(q[1].l()<=q[2].l()&&!q[2].no()) q[3].on(q[2].end()),q[2].pop(),a[ans+1].st=2,a[ans+1].en=3;
				else if(!q[1].no()) q[3].on(q[1].end()),q[1].pop(),a[ans+1].st=1,a[ans+1].en=3;
			}
		}
		ans++;//操作个数
	}
}
int main()
{
	scanf("%d",&tot);
	while(tot--)
	{
		ans=0,q[1].in(),q[2].in(),q[3].in();//清空
		scanf("%d%d",&n,&p);
		for(int i=1;i<=2;i++)//输入
		{
			for(int j=1;j<=n;j++)
			{
				jk='0';
				while(jk!='1'&&jk!='2') jk=getchar();
				if(jk!=jk1) q[i].on(jk-'0');jk1=jk;
			}
			jk1='p';
		}
		dfs();//执行
      //特判
		if(q[1].end()==q[2].end()) a[++ans].st=2,a[ans].en=1,q[2].pop(),q[2].a[1]=q[1].end()==1?2:1;
		while(!q[3].no())
		{
			if(q[3].end()==q[1].end()) a[++ans].st=3,a[ans].en=1;
			else a[++ans].st=3,a[ans].en=2;q[3].pop();
		}
		printf("%d\n",ans);if(p==1) continue;//输出
		for(int i=1;i<=ans;i++) printf("%d %d\n",a[i].st,a[i].en);
	}
	return 0;
}
```

---

## 作者：zcr0202 (赞：0)

## 题目大意

给你两个字符串 $ s1 $ 和 $ s2 $，要你通过多次进行倾倒操作，每次倾倒可以使这个瓶子的最上面的连续的元素倒入另外一个瓶子，最后要求瓶子中只有连续的一段元素，并且只能放在前两个瓶子里，求最少的倾倒次数及其方案。

## 解题思路

首先我们发现一段连续的元素个数并不重要，重要的是这个元素是什么。因此我们先去重，接着我们可以用贪心的思想去解决答案的问题，总共分为四个步骤：

- 当前两个瓶子的最上端相同时，就将元素多的瓶子倒入元素小的瓶子。

- 如果其中两个瓶子的其中之一是空的，就将非空的瓶子里的元素倒入空瓶子当中。

- 如果第三个瓶子是非空的，那么就把与第三个顶端相同的元素的前两个瓶子倒入第三个瓶子中。

- 否则就把元素多的瓶子倒入第三个瓶子当中。


结束条件也很简单，就判断两个瓶子里的元素个数是否都小于一就可以了。

然后你就会发现你时间超限了。

是什么问题？

原来是在即将结束的时候出了毛病，有一种可能就是前两个瓶子里的元素相同，而在第三个瓶子中的元素不与前两个瓶子的元素相同，因此倒不出去。

所以我们特判一下，把第二个瓶子的元素倒入第一个瓶子就可以开始操作了。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int l, op;
char a[N];
int s1[N], s2[N], s3[N], sum1, sum2, sum3;
int d, ans[N][2];
void fre() {
    freopen("text.in", "r", stdin);
    freopen("text.out", "w", stdout);
}
void shuchu() {        //测试数据
    cout << sum1 << " " << sum2 << " " << sum3 << '\n';
    for(int i = 1; i <= sum1; i++) {
        cout << s1[i];
    }
    cout << '\n';
    for(int i = 1; i <= sum2; i++) {
        cout << s2[i];
    }
    cout << '\n';
    for(int i = 1; i <= sum3; i++) {
        cout << s3[i];
    }
    cout << '\n';
}
void ss(int x, int y) {        //记录答案
    d++;
    ans[d][0] = x;
    ans[d][1] = y;
}
signed main() {
//    fre();
    int T;
    cin >> T;
    while(T--) {
        sum1 = sum2 = sum3 = d = 0;
        memset(s1, 0, sizeof(s1));
        memset(s2, 0, sizeof(s2));
        memset(s3, 0, sizeof(s3));
        memset(ans, 0, sizeof(ans));
        cin >> l >> op;
        scanf("%s", a + 1);
        for(int i = 1; i <= l; i++) {
            if(int(a[i] - '0') != s1[sum1]) {
                s1[++sum1] = int(a[i] - '0');
            }
        }
        scanf("%s", a + 1);
        for(int i = 1; i <= l; i++) {
            if(int(a[i] - '0') != s2[sum2]) {
                s2[++sum2] = int(a[i] - '0');
            }
        }
        while(1) {
            if(sum1 <= 1 && sum2 <= 1) {
                if(s1[sum1] == s2[sum2]) {        //特判
                    s2[sum2] = 3 - s1[sum1];
                    ss(2, 1);
                }
                if(sum3 != 0) {        //清除第三个瓶子里的元素
                    while(1) {
                        if(sum3 == 0) {
                            break;
                        } else if(s3[sum3] == s1[sum1]) {
                            ss(3, 1);
                            sum3--;
                        } else if(s3[sum3] == s2[sum2]) {
                            ss(3, 2);
                            sum3--;
                        }
                    }
                }
                cout << d << '\n';
                if(op != 1) {
                    for(int i = 1; i <= d; i++) {
                        cout << ans[i][0] << " " << ans[i][1] << '\n';
                    }
                }
                break;
            } else {
                if(s1[sum1] == s2[sum2]) {        //第一步操作
                    if(sum1 <= sum2) {
                        sum2--;
                        ss(2, 1);
                    } else {
                        sum1--;
                        ss(1, 2);
                    }
                } else if(sum2 == 0) {        //第二步操作
                    s2[++sum2] = s1[sum1];
                    sum1--;
                    ss(1, 2);
                } else if(sum1 == 0) {
                    s1[++sum1] = s2[sum2];
                    sum2--;
                    ss(2, 1);
                } else {
                    if(sum3 != 0) {        //第三步操作
                        if(s1[sum1] == s3[sum3]) {
                            sum1--;
                            ss(1, 3);
                        } else {
                            sum2--;
                            ss(2, 3);
                        }
                    } else {        //第四步操作
                        if(sum1 >= sum2) {
                            s3[++sum3] = s1[sum1];
                            ss(1, 3);
                            sum1--;
                        } else {
                            s3[++sum3] = s2[sum2];
                            ss(2, 3);
                            sum2--;
                        }
                    }
                }
            }
        }
    }
}
```

---

## 作者：aaron0919 (赞：0)

# [P10191 の题解](https://www.luogu.com.cn/problem/P10191)

应该为黄。

### 题目大意

类似于汉诺塔，只是只有两种颜色、三个柱子，相同颜色会融合，求最小操作数使得两种颜色分离并在柱 $1$ 和柱 $2$。

### 理性分析

首先缩点，显然易见，缩完点后两种颜色一定交替出现，考虑如下贪心。

1. 当柱 $1$ 顶盒柱 $2$ 顶相同时，将它们合并到其中一个，也就是一个柱 `pop`。
2. 不一样，那就将和柱 $3$ 颜色相同的放进柱 $3$。
3. 特判最后放回柱 $1$ 和柱 $2$ 的情况。

### 代码实现

可以选择用手模栈或 `vector` 实现，我用 `vector`，码量较小。

### code

```cpp
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
using ll = long long;

const int N = 2e5 + 10;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;

int n, p;
vector<int> a[3];
vector<pair<int, int>> anses;

vector<int> in(string s)
{
    vector<int> l;
    for (char c : s)
    {
        int digit = c - '0';
        if (!l.empty() && l.back() == digit)
        {
            continue;
        }
        l.push_back(digit);
    }
    return l;
}

void move(int from, int to)
{
    anses.push_back({from, to});
    if (a[to].empty() || a[to].back() != a[from].back())
    {
        a[to].push_back(a[from].back());
    }
    a[from].pop_back();
}

void solve()
{
    for (int i = 0; i < 3; i++)
    {
        a[i].clear();
    }
    anses.clear();
    cin >> n >> p;
    a[0] = in("");
    a[1] = in("");
    for (int i = 0; i < 2; i++)
    {
        string tube;
        cin >> tube;
        a[i] = in(tube);
    }
    a[2].clear();

    if (a[0][0] == a[1][0])
    {
        a[0].insert(a[0].begin(), a[0][0] ^ 3);
    }

    int cnt = a[0].size() + a[1].size() - 2;
    if (cnt > 1)
    {
        cnt += 1;
    }

    cout << cnt << endl;
    if (p == 1)
    {
        return;
    }

    if (a[0].back() == a[1].back())
    {
        if (a[0].size() > a[1].size())
        {
            move(0, 1);
        }
        else
        {
            move(1, 0);
        }
    }

    for (int i = 0; i < 2; i++)
    {
        if (a[i].size() > 1)
        {
            move(i, 2);
            int k = 0;
            if (a[k][0] == a[2][0])
            {
                k ^= 1;
            }
            while (a[k].size() > 1)
            {
                if (a[k].back() == a[2][0])
                {
                    move(k, 2);
                }
                else
                {
                    move(k, k ^ 1);
                }
            }
            k ^= 1;
            while (a[k].size() > 1)
            {
                if (a[k].back() == a[2][0])
                {
                    move(k, 2);
                }
                else
                {
                    move(k, k ^ 1);
                }
            }
            move(2, k);
            break;
        }
    }

    for (const auto &ans : anses)
    {
        cout << 1 + ans.first << " " << 1 + ans.second << endl;
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("tt.in", "r", stdin);
    freopen("tt.out", "w", stdout);
#endif

    cin.tie(0)->sync_with_stdio(false);

    int T;
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        solve();
    }
    return 0;
}
```

---

## 作者：2023lpx (赞：0)

# P10191 [USACO24FEB] Test Tubes S 题解

## 思路

首先我们先将题目化简，将连续的 $1$ 或 $2$ 当成一个来看。

那么题目的意思就是让两个试管最后分别只留下一个 $1$ 或 $2$。

$p=2$ 与 $p=3$ 时的效果是一样的。

我们分类讨论一下：

1. 两个试管的顶部元素一样。
  
2. 烧杯是空的。
  
3. 将烧杯里的倒入顶元素一样的。
  
4. 可以一步到位的。
  

很明显，对于第 1 种情况，直接将元素多的倒入元素少的即可。

对于第 2 种情况，将元素多的试管的顶部元素倒入烧杯即可。

第 3 种，为前两种都不符合时执行。

第 4 种，特判（这就不用我说了吧）。

tips：**先特判**再执行前三点。

## code

```cpp
#include<cstdio>
using namespace std;
int T;
int n;
int m;
int const maxn=300000;
int ans[maxn+10][2];
int top[maxn+1][4];
int high[4];
void read(){
	high[1]=0;
	high[2]=0;
	high[3]=0;
	top[0][1]=3;
	top[0][2]=3;
	top[0][3]=3;
	for(int i=1;i<=n;i++){
		char in=getchar();
		while(in!='1'&&in!='2'){
			in=getchar();
		}
		if(in=='1'){
			if(top[high[1]][1]==1){
				continue;
			}
			high[1]++;
			top[high[1]][1]=1;
		}
		if(in=='2'){
			if(top[high[1]][1]==2){
				continue;
			}
			high[1]++;
			top[high[1]][1]=2;
		}
	}
	for(int i=1;i<=n;i++){
		char in=getchar();
		while(in!='1'&&in!='2'){
			in=getchar();
		}
		if(in=='1'){
			if(top[high[2]][2]==1){
				continue;
			}
			high[2]++;
			top[high[2]][2]=1;
		}
		if(in=='2'){
			if(top[high[2]][2]==2){
				continue;
			}
			high[2]++;
			top[high[2]][2]=2;
		}
	}
	return;
}
void js(){
	m=0;
	bool found=0;
	while(1){
		if(high[1]==1&&high[2]==1&&high[3]==0){
			return;
		}
		if(high[1]==0&&high[2]==2){
			high[1]++;
			top[high[1]][1]=top[high[2]][2];
			high[2]--;
			m++;
			ans[m][0]=2;
			ans[m][1]=1;
		}
		else if(high[2]==0&&high[1]==2){
			high[2]++;
			top[high[2]][2]=top[high[1]][1];
			high[1]--;
			m++;
			ans[m][0]=1;
			ans[m][1]=2;
		}	
		if(high[1]==0&&high[2]==1){
			top[high[1]][1]=top[high[3]][3];
			high[3]--;
			m++;
			ans[m][0]=3;
			ans[m][1]=1;
			return;
		}
		if(high[2]==0&&high[1]==1){
			top[high[2]][2]=top[high[3]][3];
			high[3]--;
			m++;
			ans[m][0]=3;
			ans[m][1]=2;
			return;
		}
		if(high[1]==1&&high[2]==1&&top[high[1]][1]!=top[high[2]][2]){
			if(high[3]==0){
				return;
			}
			if(top[high[1]][1]==top[high[3]][3]){
				m++;
				ans[m][0]=3;
				ans[m][1]=1;
			}
			else{
				m++;
				ans[m][0]=3;
				ans[m][1]=2;
			}
			return;
		}
		if(top[high[1]][1]==top[high[2]][2]){
			if(high[1]>high[2]){
				high[1]--;
				m++;
				ans[m][0]=1;
				ans[m][1]=2;
			}
			else{
				high[2]--;
				m++;
				ans[m][0]=2;
				ans[m][1]=1;
			}
		}
		else if(high[3]==0){
			found=1;
			if(high[1]>high[2]){
				high[3]++;
				top[high[3]][3]=top[high[1]][1];
				high[1]--;
				m++;
				ans[m][0]=1;
				ans[m][1]=3;
			}
			else{
				high[3]++;
				top[high[3]][3]=top[high[2]][2];
				high[2]--;
				m++;
				ans[m][0]=2;
				ans[m][1]=3;
			}
		}
		else{
			if(top[high[1]][1]==top[high[3]][3]){
				top[high[3]][3]=top[high[1]][1];
				high[1]--;
				m++;
				ans[m][0]=1;
				ans[m][1]=3;
			}
			else{
				top[high[3]][3]=top[high[2]][2];
				high[2]--;
				m++;
				ans[m][0]=2;
				ans[m][1]=3;
			}
		}
	}
	if(found==0){
		m--;	
	}
	return;
}
signed main(){
	scanf("%d",&T);
	int p;
	while(T--){
		scanf("%d%d",&n,&p);
		read();
//		printf("%d %d %d\n",high[1],high[2],high[3]);
		js();
		if(p==1){
			printf("%d\n",m);
			continue;
		}
		if(p==2||p==3){
			printf("%d\n",m);
			for(int i=1;i<=m;i++){
				printf("%d %d\n",ans[i][0],ans[i][1]);
			}
		}
	}
	return 0;
}
```

---

