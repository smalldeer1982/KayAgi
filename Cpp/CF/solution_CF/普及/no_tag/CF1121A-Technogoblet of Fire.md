# Technogoblet of Fire

## 题目描述

Everybody knows that the $ m $ -coder Tournament will happen soon. $ m $ schools participate in the tournament, and only one student from each school participates.

There are a total of $ n $ students in those schools. Before the tournament, all students put their names and the names of their schools into the Technogoblet of Fire. After that, Technogoblet selects the strongest student from each school to participate.

Arkady is a hacker who wants to have $ k $ Chosen Ones selected by the Technogoblet. Unfortunately, not all of them are the strongest in their schools, but Arkady can make up some new school names and replace some names from Technogoblet with those. You can't use each made-up name more than once. In that case, Technogoblet would select the strongest student in those made-up schools too.

You know the power of each student and schools they study in. Calculate the minimal number of schools Arkady has to make up so that $ k $ Chosen Ones would be selected by the Technogoblet.

## 说明/提示

In the first example there's just a single Chosen One with id $ 3 $ . His power is equal to $ 3 $ , but in the same school $ 1 $ , there's a student with id $ 5 $ and power $ 6 $ , and that means inaction would not lead to the latter being chosen. If we, however, make up a new school (let its id be $ 4 $ ) for the Chosen One, Technogoblet would select students with ids $ 2 $ (strongest in $ 3 $ ), $ 5 $ (strongest in $ 1 $ ), $ 6 $ (strongest in $ 2 $ ) and $ 3 $ (strongest in $ 4 $ ).

In the second example, you can change the school of student $ 3 $ to the made-up $ 5 $ and the school of student $ 4 $ to the made-up $ 6 $ . It will cause the Technogoblet to choose students $ 8 $ , $ 7 $ , $ 6 $ , $ 5 $ , $ 3 $ and $ 4 $ .

## 样例 #1

### 输入

```
7 3 1
1 5 3 4 6 7 2
1 3 1 2 1 2 3
3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
8 4 4
1 2 3 4 5 6 7 8
4 3 2 1 4 3 2 1
3 4 5 6
```

### 输出

```
2
```

# 题解

## 作者：_Violet_Evergarden (赞：5)

看到题解有些空缺，就来发一发。
# 简要题意：
有 $n$ 个学生和 $m$ 所学校，你只需查找输入的人是不是该所学校的最有实力的人。

# 思路：
这道题看似很难理解，实则悟到后会发现很简单，我们只需要将每所学校学生的实力的最大值存下来，然后进行判断，判断输入的学生的实力是不是该所学校的实力的最大值即可。

# 代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
int a[100001];
int b[100001];
int da[100001];
int ans; 
int x;
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
		da[b[i]]=max(da[b[i]],a[i]);
	}
	for(int i=1;i<=k;i++){
		cin>>x;
		if(a[x]!=da[b[x]]){
			ans++;
		}
	}	
	cout<<ans;
	return 0;
}

```


---

## 作者：Stars_visitor_tyw (赞：1)

## CF1121A Technogoblet of Fire 题解
### 题目大意
给你 $n$ 名学生的实力、他们所在的 $m$ 所学校的编号以及 $k$ 个人，问你这 $k$ 个人中至少为多少个人编造多少个学校以至于这 $k$ 个人都变成他们学校中最强的。

### 分析
其实这题很简单。因为如果将一个原本不是其所在学校最强的学生放进一个新的学校，则那个学生变为他现在所在学校的最强者。将题意转化为询问有多少个学生原本不是其所在学校最强的。

循环找出每所学校最强的人，再判断输入的 $k$ 个人的实力是否和他们原来所在学校的最强者实力相等即可。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, m, k, maxi[20005], sch[20005], a[20005], ans;
signed main()
{
    memset(maxi,0xcf,sizeof(maxi));
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    for(int i=1;i<=n;i++)
    {
        cin>>sch[i];
        maxi[sch[i]]=max(maxi[sch[i]],a[i]);//记录每所学校的最大实力值
    }
    for(int i=1;i<=k;i++)
    {
        int id;
        cin>>id;
        if(a[id]!=maxi[sch[id]])//如果第id个人的实力不等于其原本所在学校最强者的实力，答案累加
        {
            ans++;
        }
    }
    cout<<ans;
    return 0;
}
```


---

## 作者：Silence_World (赞：1)

# 题意

给你 $n$ 个人的实力，再给你他们所在学校的号码，不超过 $m$（虽然好像没什么用），再给你 $k$ 个人，他们必须是所在学校中实力最强的，否则就建一个新的学校把他放进去，问如何最少次实现这个操作。

# 思路

题目很简单，主要是太难读懂了，很显然，如果学生是他学校最强的就不需要操作，否则就把他扔新的学校去，操作加一。

# 代码

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[100005];
int b[100005];
int c[100005];
int max1[100005];
main(){
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int j=1;j<=n;j++){
		cin>>b[j];
		max1[b[j]]=max(max1[b[j]],a[j]);
	}
	int cnt=0; 
	for(int i=1;i<=k;i++){
		int t;
		cin>>t;
		if(a[t]==max1[b[t]])continue;
		cnt++;
	}
	cout<<cnt<<endl;
	return 0;
} 
```


---

## 作者：Withershine (赞：1)

AC，但是不知道为什么 UKE。这哪里是编程题，简直就是阅读理解。

## 思路
输入的 $n$，$m$，$k$ 分别表示学生数，学校数，阿卡迪想要的天选之子的数量（虽然我不知道为啥会翻译成天选之子）。

注意了，原文中一句话

Unfortunately, not all of them are the strongest in their schools。

这句话的意思应该翻译成：“不幸的是，并不是所有学生都是他们的学校里最强的”，而不是“不幸的是，并不是所有的学校都是最强的”。这里真的很影响对题意的理解。

接下来的 $a$，$b$ 数组都很好解释。来看 $c$ 数组。$c$ 数组表示阿卡迪想抽中的学生。而我们知道科技火焰杯（其实就是题目翻译）只会选择最强的，那么只需要让阿卡迪想抽中的学生是哪个学校最强的就好了。

对于一个已经是哪个学校最强的学生，无需新增学校名，否则就新增一所学校名即可。

## 代码
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<string>
#include<ctime>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<map>
#include<set>
#include<sstream>
#include<cassert>
#include<stdio.h>
#define ll long long
#define inf 0x3f3f3f3f
#define fr(i , a , b) for(ll i = a ; i <= b ; ++i)
#define fo(i , a , b) for(ll i = a ; i >= b ; --i)
using namespace std;
inline char gchar()
{
    static char buf[1000000] , *p1 = buf , *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf , 1 , 1000000 , stdin) , p1 == p2) ? EOF : *p1++;
}
inline ll read()
{
    ll x = 0 , f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
	  {
        if(ch == '-')
        {
        	f = -1;
		}
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
	  {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
ll n , m , k;
ll a[101] , b[101] , c;
ll maxn[101] , sum;
signed main()
{
    memset(maxn , -1  , sizeof(maxn));
    n = read();
    m = read();
    k = read();
    fr(i , 1 , n)
    {
        a[i] = read();
    }
    fr(i , 1 , n)
    {
        b[i] = read();
        maxn[b[i]] = max(maxn[b[i]] , a[i]);
    }
    fr(i , 1 , k)
    {
        c = read();
        if(maxn[b[c]] != a[c])
        {
            sum++;
        }
    }
    printf("%lld" , sum);
    system("pause");
    return 0;
}
```


---

## 作者：Bc2_ChickenDreamer (赞：0)

# CF1121A Technogoblet of Fire 题解

## Sol

黄题有点过分……

我们只要统计有多少个学生原本**不是**自己学校最强的即可，因为将这样的学生放进**新的学校**，那个学生变为**最强者**。

算法：模拟。

## Code

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iomanip>

using namespace std;

using ll = long long;

#define mtest for (cin >> t; t; -- t)

const int kMaxN = 2e4 + 20, kInf = (((1 << 30) - 1) << 1) + 1;
const ll kLInf = 9.22e18;

int n, m, k, a[kMaxN], mx[kMaxN], c[kMaxN];

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> m >> k;
  for (int i = 1; i <= n; ++ i) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; ++ i) {
    cin >> c[i], mx[c[i]] = max(mx[c[i]], a[i]);
  }
  ll ans = 0;
  for (int i = 1, C; i <= k; ++ i) {
    cin >> C;
    (a[C] != mx[c[C]]) && (++ ans);
  }
  cout << ans << '\n';
  return 0;
}

```

---

## 作者：skyskyCCC (赞：0)

## 前言。
一道比较简单的思维题。

在原网站上过了，但是不知道为什么洛古提交五遍都是“不知道什么错误”。
## 分析。
题意简述：给你 $n$ 个人的实力，再给你他们所在的 $m$ 个学校的号码，再给你 $k$ 个人，他们必须是**所在学校**中实力**最强**的，否则就编造一个新的学校把他放进去，求至少需要几个编造的学校。

其实就是求至少编造几个学校可以使这 $k$ 个学生都变成该学校的实力最强者。

很显然，我们首先找出每个学校最强的学生，如何看这 $k$ 个学生是否是他们所在学校的实力最强者，如果是，那么跳过即可，如果不是，就编造一个学校把他单独放进去，答案加一即可。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int n,m,k,choose,a[105],b[105];
int sc[105],ans;
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
		sc[b[i]]=max(sc[b[i]],a[i]);
	}
    //看一下需要添加几个学校。
	for(int i=1;i<=k;i++){
		cin>>choose;
		if(a[choose]==sc[b[choose]]) continue;
		else ans++;
	}
	cout<<ans<<"\n";
	return 0;
}
```
## 后记。
建议看原题自己翻译，这个洛古翻译其实差点事。

大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：hubin1 (赞：0)

# Technogoblet of Fire

## 题目大意
给定 $n$ 个学生的实力和他们所属的学校，可以通过增加学校并改变学生学校的方法使学生们成为学校的第一名。求至少增加几个学校可以使这 $k$ 个学生都变成第一名。
## 思路
1. 看完题就知道这是个贪心。如果某人是该校的第一名，那么就不增加学校；反之，增加学校。
2. 我们预处理出每个学校最大的分数，直接判断就行了。

## Code
``` cpp
#include<bits/stdc++.h>
using namespace std;

const int MAX=100+10;
int a[MAX],b[MAX];
int maxx[MAX];

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	
	int n,m,k;
	cin>>n>>m>>k;//如题
	
	for(int i=1;i<=n;i++)
		cin>>a[i];//这个指的是每个学生的实力

	for(int i=1;i<=n;i++)
	{
		cin>>b[i];//每个学生所属的学校
		maxx[b[i]]=max(maxx[b[i]],a[i]);//每个学校的最高分
	}
	int ans=0;
	for(int i=1;i<=k;i++)
	{
		int t;
		cin>>t;
		if(a[t]==maxx[b[t]])//进行比较
			continue;
		else
			ans++;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Keroshi (赞：0)

# 分析
Arkady 的学生必须要在学校中排名第一，那么通过贪心的思想，只要这个学生已经是第一了，那么就不用造一个新的学校名称。   
接下来，只需记录所有学校的最高分，如果一个学生的分数不是他学校的最高分，那么就造一个新的学校名称。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e2+5;
int n,m,k;
int a[N],b[N],c[N],f[N];
int main(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) scanf("%d",&b[i]);
    for(int i=1;i<=k;i++) scanf("%d",&c[i]);
    for(int i=1;i<=n;i++) f[b[i]]=max(f[b[i]],a[i]);
    int ans=0;
    for(int i=1;i<=k;i++)
        if(f[b[c[i]]]!=a[c[i]]) ans++;
    printf("%d",ans);
    return 0;
}
```

---

