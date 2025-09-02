# Spongebob and Joke

## 题目描述

当派大星去购物时，海绵宝宝决定戏弄一下他的朋友。调皮的海绵宝宝翻看了派大星的个人物品，找到了一个长度为 $ m $ 的序列 $ a_{1},a_{2},...,a_{m} $，由整数 $ 1 $ 到 $ n $ 组成，不一定是不同的。然后，他选择了一个长度为 $ n $ 的序列 $ f_{1},f_{2},...,f_{n} $，对于每个数字 $ a_{i} $，得到数字 $ b_{i}=f_{a_i} $。为了完成这个恶作剧，他将初始序列 $ a_{i} $ 扔掉了。

难以想象派大星从购物回来后有多伤心！海绵宝宝马上对自己的所作所为感到非常抱歉，他现在正在尝试恢复原始序列。请你帮助他完成这个任务或确定这是否不可能。

**形式化题意**：给你一个长度为 $n$ 的数组 $f$ 和一个长度为 $m$ 的数组 $b$，并规定 $f_{a_i} = b_i$，请尝试恢复出原数组。如果有多种可能，输出 `Ambiguit`，如果无法还原，输出 `Impossible`。

## 样例 #1

### 输入

```
3 3
3 2 1
1 2 3
```

### 输出

```
Possible
3 2 1 
```

## 样例 #2

### 输入

```
3 3
1 1 1
1 1 1
```

### 输出

```
Ambiguity
```

## 样例 #3

### 输入

```
3 3
1 2 1
3 3 3
```

### 输出

```
Impossible
```

# 题解

## 作者：Yamchip (赞：3)

## 思路
先来看无解的情况，显然当 $f$ 数组中不存在 $b_{i}$ 时无解。
然后是多个解，当 $f$ 数组中存在多个 $b_{i}$ 时有不只一个解。
答案我们可以使用一个数组来储存，我们把每个 $f_{i}$ 的位置存下来，然后输出。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, f[100005], b[100005], cntf[100005], ans[100005];
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1;i <= n;i++)
    {
        scanf("%d", &f[i]);
        cntf[f[i]]++;
        ans[f[i]] = i;
    }
    for(int i = 1;i <= m;i++)
    {
        scanf("%d", &b[i]);
        if(!cntf[b[i]])
        {
            printf("Impossible");
            return 0;
        }
    }
    for(int i = 1;i <= m;i++)
        if(cntf[b[i]] > 1)
        {
            printf("Ambiguity");
            return 0;
        }
    printf("Possible\n");
    for(int i = 1;i <= m;i++)
    	printf("%d ", ans[b[i]]);
    return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/146138406)

---

## 作者：Ninelife_Cat (赞：1)

### 题目大意：

给你一个长度为 $n$ 的数组 $f$ 和一个长度为 $m$ 的数组 $b$，并规定 $f_{a_i}=b_i$，问是否能还原出 $a$ 数组。

如果只能还原出一个 $a$ 数组，输出一行 ```Possible``` 和还原出的 $a$ 数组。

如果能还原出多个不同的 $a$ 数组，输出一行 ```Ambiguity```。

如果还原不出，输出一行 ```Impossible```.

### 思路：

本题细节有点小多。

首先一个 $b_x$ 是 $a_x$ 通过 $f$ 得到的，所以如果有多个 $a_x$ 通过 $f$ 得到的是同一个 $b_x$，那么显然会还原出多个 $a$ 数组。但要注意，如果一个 $b_x$ 对应多个 $a_x$，但它并没有在数据中出现的话，就不会对答案产生影响。

接下来，如果一个 $b_x$ 对应 $0$ 个 $a_i$，并且它在数据中，那么显然是无解的。

把这些情况特判掉之后，只要再开一个数组 $c$，令 $c_x=y$ 表示 $x$ 能还原为 $y$，然后把 $b$ 数组还原后再输出就行了。

### 核心代码：

```cpp
const int N=1e5+10;
int n,m,f[N],b[N],a[N],c[N];
bool flag,vis[N];//flag记录数据中是否有一个b对应多个a的情况
//vis数组记录这个数有没有在数据中出现
signed main()
{
	n=read();m=read();
	for(ri int i=1;i<=n;++i)
		f[i]=read();
	for(ri int i=1;i<=m;++i)
		vis[b[i]=read()]=1;
	for(ri int i=1;i<=n;++i)
		if(!c[f[i]]) c[f[i]]=i;//一个b对应一个a的情况
			else if(vis[f[i]]) flag=1;//一个b对应多个a的情况
	for(ri int i=1;i<N;++i)
		if(vis[i]&&!c[i]) return cout<<"Impossible",0;//判无解
	if(flag) return cout<<"Ambiguity",0;
	cout<<"Possible\n";
	for(ri int i=1;i<=m;++i)
		cout<<c[b[i]]<<" ";
	return 0;
}
```

---

## 作者：zzhbpyy (赞：0)

### [Problem - 599B - Codeforces](https://codeforces.com/problemset/problem/599/B)

若满足对任意 $i$，$b_i$ 在 $f$ 数组中出现过，且只出现一次则有唯一解，$b_i$ 在 $f$ 中出现过多次就输出 `Ambiguity`，否则输出 `Impossible`。可以直接排序后二分判定和得到答案。

```c++
#include<bits/stdc++.h>
using namespace std;
struct Edge{
	int w,id;
}a[100005];
int n,m,b[100005],res[100005],cnt[100005];
inline bool operator<(Edge a,Edge b){
	if(a.w==b.w)return a.id<b.id;
	return a.w<b.w;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i].w,a[i].id=i;//储存编号方便得到答案
	sort(a+1,a+n+1);
	for(int i=1;i<=m;i++)cin>>b[i],cnt[b[i]]++;
	bool flg=false;
	for(int i=1;i<=m;i++){
		int u=lower_bound(a+1,a+n+1,(Edge){b[i],0})-a;res[i]=a[u].id;
		if(a[u].w!=b[i])cout<<"Impossible\n",exit(0);
		int v=upper_bound(a+1,a+n+1,(Edge){b[i],(int)1e9})-a-1;
		if(v-u+1!=1)flg=true;
	}
	if(flg)cout<<"Ambiguity\n",exit(0);
	cout<<"Possible\n";
	for(int i=1;i<=m;i++)cout<<res[i]<<' ';
}
```

---

## 作者：Lizj (赞：0)

完整题意详见题面。

已知 $b_i=f_{a_i}$，求数组 $a$ 的值。

先记录每个 $f_i$ 的值的数量，

- 当 $f$ 数组中与 $b$ 数组中没有相同的值时，输出 `Impossible`

- 当 $f$ 数组中与 $b$ 数组中有多组相同的值时，输出 `Ambiguity`

- 其余情况输出 `Possible`。

然后考虑如何求出数组 $a$，

对于 $b_i=f_{a_i}$，通过 $f$ 数组记录每一个可能的 $a_i$ 的值。易得，数组 $b$ 的长度与 $a$ 的长度相等。在判断合法后输出 $a_{b_i}$ 即可。

时间复杂度 $O(n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
int cnt[100010],b[100010],a[100010];
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		int f;
		cin>>f;
		cnt[f]++;
		a[f]=i;
	}
	for(int i=1;i<=m;i++){
		cin>>b[i];
		if(cnt[b[i]]==0){
			cout<<"Impossible";
			return 0;
		}
	}
	for(int i=1;i<=m;i++){
		if(cnt[b[i]]>1){
			cout<<"Ambiguity";
			return 0;
		}
	}
	cout<<"Possible"<<endl;
	for(int i=1;i<=m;i++)
		cout<<a[b[i]]<<' ';
	return 0;
}
```

---

## 作者：Breath_of_the_Wild (赞：0)

题意简单来说就是按照某种顺序让 $f$ 和 $b$ 配对，让我们求出顺序。我们分 $3$ 种情况考虑。

如果没有 $f_j$ 等于 $b_i$，肯定就不能配对了，输出 ``Impossible``。

如果 $f$ 中有多个重复的 $b_i$，用哪一个下标都行，就会有多个解，输出 ``Ambiguity``。（本人写此题解时，题目貌似忘写了一个 ``Y``）

不用判断是不是只有一个解。前面两个输出完了就结束程序。所以直接输出 ``Possible`` 和你的 $a$ 即可。

思路就是存 $f$ 的哈希（出现次数），以及记录 $f_i$ 的下标，即 $i$，判断 $f_{b_i}$ 出现次数即可。

较简单，代码不给了。

---

## 作者：Graph_Theory (赞：0)

### 思路
1. 没有 $f_i$ 对应的 $b_i$ 时，输出无解。
2. 有重复 $f_i$ 对应的 $b_i$ 时，输出多组解。
3. 唯一答案。

对于一的情况，用 $F\_where$ 记录数量，如果 $F\_where_{b[i]}$ 不存在，输出无解。

对于二的情况，用 $F\_num$ 记录数量，如果 $F\_num_{b[i]}>1$ 输出多组解。

对于三的情况，输出 $F\_where_{b[i]}$。

### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m,f[100010],b[100010],f_num[100010],f_where[100010];
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin >> f[i];
		f_num[f[i]]++,f_where[f[i]] = i;
	}
	for(int i=1;i<=m;i++)
	{
		cin>>b[i];
		if(!f_where[b[i]])
		{
			cout << "Impossible";
			return 0; 
		}	
	}
	for(int i=1;i<=m;i++)
		if(f_num[b[i]]>1)
		{
			cout<<"Ambiguity";
			return 0; 
		}
	cout << "Possible"<<endl;
	for(int i=1;i<=m;i++) cout<<f_where[b[i]]<<" ";
	return 0;
}
```

---

