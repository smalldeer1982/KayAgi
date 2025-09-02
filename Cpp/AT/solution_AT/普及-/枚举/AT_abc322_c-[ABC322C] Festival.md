# [ABC322C] Festival

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc322/tasks/abc322_c

AtCoder 王国では、これから $ N $ 日間のお祭りが開催されます。そのうち、$ A_1 $ 日目、$ A_2 $ 日目、$ \dots $、$ A_M $ 日目の $ M $ 日では花火が上がります。ここで、お祭りの最終日には花火が上がることが保証されます。(つまり、$ A_M=N $ が保証されます。)

$ i=1,2,\dots,N $ に対して、以下の問題を解いてください。

- $ i $ 日目以降で初めて花火が上がるのは、$ i $ 日目から数えて何日後か？ただし、$ i $ 日目に花火が上がる場合 $ 0 $ 日後とする。

## 说明/提示

### 制約

- $ 1\ \le\ M\ \le\ N\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ A_1\ <\ A_2\ <\ \dots\ <\ A_M\ =\ N $
- 入力は全て整数

### Sample Explanation 1

AtCoder 王国ではお祭りを $ 3 $ 日間開催し、$ 2,3 $ 日目に花火が上がります。 - $ 1 $ 日目以降で初めて花火が上がるのは $ 2 $ 日目なので、$ 1 $ 日目から数えて $ 1 $ 日後です。 - $ 2 $ 日目以降で初めて花火が上がるのは $ 2 $ 日目なので、$ 2 $ 日目から数えて $ 0 $ 日後です。 - $ 3 $ 日目以降で初めて花火が上がるのは $ 3 $ 日目なので、$ 3 $ 日目から数えて $ 0 $ 日後です。

## 样例 #1

### 输入

```
3 2
2 3```

### 输出

```
1
0
0```

## 样例 #2

### 输入

```
8 5
1 3 4 7 8```

### 输出

```
0
1
0
0
2
1
0
0```

# 题解

## 作者：Binah_cyc (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc322_c)

### 题意
给定整数 $N$，$M$ 和一个长度为 $M$ 的序列 $a$。对于 $1 \sim n$ 中每一个 $i$，求出第一个大于等于 $i$ 的 $a$ 与 $i$ 的差。保证序列 $a$ 递增且 $ a_n = n $。（注意，当 $i$ 等于 $a$ 时，差为 $0$）。

### 题目分析
上面的那些大佬怎么都用二分写，时间复杂度还高，不如递推好想。

现提供一种递推做法。

对于每一个数的答案，要么由 $i+1$ 的答案推出，这时的答案为 $ ans_{i+1} + 1 $，即 $i$ 比 $i+1$ 离大于等于 $i$ 的 $a$ 的距离大了 $1$。要么 $i$ 本身就等于 $a$ 中的某一个数，这时答案为 $0$。

### 细节
**递推时要倒序递推。**

### Code
```c
#include <bits/stdc++.h> //万能头 
using namespace std;
int n,m,ans[200005];
bool mp[200005]; //mp是标记数组,mp[i]表示a数组中是否有数的值为 i ,有则为1 
int main() {
	cin>>n>>m; //读入n和m 
	int x;
	for(int i=1;i<=m;i++)
	{
		cin>>x; //读入a数组,因为后面用不到a数组了,所以a数组就可以改成变量来节省空间 
		mp[x]=1; //标记,表示 a数组中有一个数的值为x 
	}
	for(int i=n;i>=1;i--) //倒序递推,因为只有更新了ans[i+1]才能用它的值更新ans[i]的值,而i+1>i,所以才要倒序更新 
	{
		if(mp[i]) //相等 
		ans[i]=0; //差为零  
		else //不相等 
		ans[i]=ans[i+1]+1; //继承ans[i+1]的答案 
	}
	for(int i=1;i<=n;i++)
	cout<<ans[i]<<'\n';
	return 0;
}
```
[AC记录](https://atcoder.jp/contests/abc322/submissions/46109706)

---

## 作者：Dream_poetry (赞：4)

### 翻译：
前言：这次 C 过水，D 过难了。

言归正传，题意简单地说，就是找从第 $i$ 天开始，往后 $j$ 天会必然有一个标记，输出每个 $j$。

### 思路：
这里提供两个方法：

#### 赛事思路：
通过对题的分析，我们会发现，它的输出其实是 $M$ 个等降序列，每个子序列的结束点为 $0$。

所以，我们从下标为 $1$ 的日期开始，先向后搜哪一天是节日，然后用 $e_i$ 来存储上文所述的 $j$，接下来，$e_{i+1}$ 不断设为 $e_i-1$。

当 $e_{i-1}$ 是 $0$ 时，我们再度爆搜即可。

[代码1](https://www.luogu.com.cn/paste/70g3tofy)

#### 赛后的突发奇想：
我们用数组 $a$ 来存储节日，然后用变量 $tep$ 来记现在还没过哪一个节日，不断输出 $a_{tep}-i$，当为零时，将 $tep+1$。

[代码2](https://www.luogu.com.cn/paste/1jac73an)

---

## 作者：lrx___ (赞：4)

**题意简述**

给定整数 $N,M$ 和一个长度为 $M$ 的序列 $a$。求出 $i$ 从 $1$ 到 $N$，$a$ 序列中第一个大于等于 $i$ 的数与 $i$ 的差。保证序列 $a$ 递增。

**思路**

因为 $a$ 递增，所以可以直接使用 `lower_bound` 函数来二分查找。

`lower_bound(l,r,k)` 函数返回的是地址 $[l,r)$ 中第一个大于等于 $k$ 的地址，我们可以使用 `*` 获取这个地址的值，再直接减去 $i$ 就可以了。

**代码**

```cpp
#include<cstdio>
#include<algorithm>

using std::lower_bound;

const int N=2e5+5;
int a[N];

int main(){
  int n,m,i;
  scanf("%d%d",&n,&m);
  for(i=0;i<m;i++){
    scanf("%d",&a[i]);
  }
  for(i=1;i<=n;i++){
    printf("%d\n",(*lower_bound(a,a+m,i))-i);
    /* 返回的是地址 [a,a+m) 中第一个大于等于i的地址 */
  }
  return 0;
}
```

---

## 作者：Pol_Pot (赞：3)

# 题意

AtCoder 王国举行为期 $N$ 天的节日活动。在其中的 $M$ 天，即 $A_1$ 天、$A_2$ 天、$\dots$ 天、$A_M$ 天，将燃放烟花。可以保证的是，烟花将在节日的最后一天燃放。(换句话说，$A_M=N$ 是有保证的）。

求每个 $i=1,2,\dots,N$ 的解。

- 从第 $i$ 天开始，第 $i$ 天或以后的第几天会首次燃放烟花？如果在 $i$ 日燃放烟花爆竹，则视为 $0$ 天后。

# 思路

如果某一天的值为 $-1$，表示这一天没有烟火表演，那么它将被设置为它后面一天的值加 $1$，表示离下一次烟火表演还有多少天。

# 代码

```python
N, M = map(int, input().split())
A = list(map(int, input().split()))

days_until_firework = [-1] * N

for day in A:
    days_until_firework[day - 1] = 0

for i in range(N - 2, -1, -1):
    if days_until_firework[i] == -1:
        days_until_firework[i] = days_until_firework[i + 1] + 1

for i in range(N):
    print(days_until_firework[i])


```


---

## 作者：zhangboyong (赞：3)

## 题意简述

给你一个数 $N$ 和一个长为 $M$ 的上升序列，要求的是 $1 \sim N$ 中每一个数，在上升序列中第一个大于等于它的数与它的差。

## 思路

由于序列是单调上升的，我们对于 $1 \sim N$ 中每一个 $i$，都可以用二分函数 `lower_bound()` 来查询第一个大于等于 $i$ 的数并输出差值。


------------

完整代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m; 
int a[200005];
int main(){
	cin >> n >>m;
	for(int i = 1;i<=m;i++) cin >> a[i];
	for(int i = 1;i<=n;i++){
		cout << *lower_bound(a+1,a+m+1,i)-i << endl;//lower_bound()返回的是地址
	}
}

```


---

## 作者：Liuhy2996 (赞：2)

### 题意
一个国家在过节，共 $N$ 天，其中有 $M$ 天会放烟花，问从第 $1$ 天到第 $N$ 天，每天离下一次放烟花还有几天。如果当天放烟花，下一次放烟花就是今天，这时答案是 $0$。
### 思路
枚举放烟花的每一天，这天到下一个放烟花天中间的每一天的答案都能直接算出来。           
时间复杂度 $O(n)$。
### 代码
```
#include <bits/stdc++.h>
using namespace std; 
int n, m, a[200005];
int main(){
	cin >> n >> m;
	for(int i = 1; i <= m; ++i) cin >> a[i];
	for(int i = 0; i < m; ++i){
		for(int j = a[i] + 1; j <= a[i + 1]; ++j) cout << a[i + 1] - j << endl;
	}
	return 0; 
}
```

---

## 作者：f_hxr_ (赞：2)

## [浴谷传送门](https://www.luogu.com.cn/problem/AT_abc322_c) [AT 传送门](https://atcoder.jp/contests/abc322/tasks/abc322_c)

### 题意

一个国家正在过节，共 $N$ 天，其中有 $M$ 天会放烟花，问第 $1$ 到 $N$ 每天离**下一次**放烟花还有几天。

注意：如果当天放烟花，则认为下一次放烟花就是今天。这时的答案是 $0$。

~~可以当成是早上询问晚上放烟花。~~

### 解析

#### 法一：从后往前扫

我们不妨从后往前扫，反过来对于每一个放烟花的那一天算出来有哪几天的答案是它。时间复杂度 $O(N)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL N,M,book[200005],ans[200005];
int main(){
	cin>>N>>M;
	for(int i=1;i<=M;i++){
		int ddd;cin>>ddd;book[ddd]=1;
	}
	int temp=114514;
	for(int i=N;i>=1;i--){
		if(book[i])ans[i]=i,temp=i;
		else ans[i]=temp;
	}
	for(int i=1;i<=N;i++)cout<<ans[i]-i<<endl;
	return 0;
} 
```

#### 法二：平衡树

我们再多看一眼，再多看一眼题面就~~要爆炸~~能发现，由于是求当天之后（包含当天）的第一个放烟花的那天，题目等价让我们求一个序列里**大于$\color{red}\text{等于}$ $X$ 的最小数**。不难想到使用平衡树。我这里用的是 FHQ Treap。

需要注意的是，在[【模板】普通平衡树](https://www.luogu.com.cn/problem/P3369)里，“后继”被定义为**是$\color{red}\text{大于}$ $X$ 的最小数，注意没有“等于”这两个字！！！**

所以，如果您想要直接复制模版，请在分裂的时候把 $X$ 分配到右边去。详情请观摩代码。

~~不过话说回来我都会 $O(N)$ 了为啥还要平衡树捏？~~

```cpp
#include<bits/stdc++.h>
using namespace std;
int N,M;
struct FHQTreap{//强烈建议学习FHQTreap!!!qwq
	int tot,root,tx,ty;
	struct node
	{int ls,rs,key,val,size;}dat[200005];
	#define ls(p) (dat[p].ls)
	#define rs(p) (dat[p].rs)
	void pushup(int p)
	{dat[p].size=dat[ls(p)].size+dat[rs(p)].size+1;}
	int New(int xx){
		dat[++tot].key=xx;dat[tot].val=rand();
		ls(tot)=rs(tot)=0;dat[tot].size=1;
		return tot;
	}
	void Split(int p,int xx,int& L,int& R){
		if(!p){L=R=0;return;}
		if(dat[p].key<=xx){L=p;Split(rs(p),xx,rs(p),R);}
		else{R=p;Split(ls(p),xx,L,ls(p));}
		pushup(p);
	}
	int Merge(int X,int Y){
		if(!X||!Y)return X|Y;
		if(dat[X].val<=dat[Y].val)
		{rs(X)=Merge(rs(X),Y);pushup(X);return X;}
		else {ls(Y)=Merge(X,ls(Y));pushup(Y);return Y;}
	}
	void insert(int xx){
		Split(root,xx-1,tx,ty);
		root=Merge(Merge(tx,New(xx)),ty);
	}
	int get(int p,int inx){
		int mid=dat[ls(p)].size+1;
		if(inx==mid)return dat[p].key;
		if(inx<mid)return get(ls(p),inx);
		else return get(rs(p),inx-mid); 
	}
	int pre(int xx){
		Split(root,xx-1,tx,ty);//模版是Split(root,xx,tx,ty);会把xx分到左边导致答案错误。现在我们将X-1分到左边，也就是tx那，相当于把大于等于X的分配到右边，也就是ty那。
		int ret=get(ty,1);//在右边查找
		root=Merge(tx,ty);return ret;
	}
}FHQ;
int main(){
	cin>>N>>M;
	for(int i=1;i<=M;i++)
	{int t;cin>>t;FHQ.insert(t);}
	for(int i=1;i<=N;i++)
		printf("%d\n",FHQ.pre(i)-i);
	return 0;
}
```

---

## 作者：yszkddzyh (赞：1)

简单模拟题。

看了题解区其他大佬的题解，发现都是用二分的方法做的，复杂度是 $\mathcal{O}(n\log n)$ 的，本蒟蒻在这里提供一种 $\mathcal{O(n)}$ 的做法。

我们用一个布尔数组 $f$ 记录每天是否放鞭炮，然后从第 $N$ 天往前扫描，期间用一个变量 $p$ 记录上一个放鞭炮的日子的编号，扫描到第 $i$ 天时，如果 $f_i=1$，即第 $i$ 天要放鞭炮，那么我们将 $p$ 更新成 $i$，再将这一天的答案记录成 $p-i$（其实就是 $0$）；否则的话，第 $i$ 天不放鞭炮，我们就直接将这天的答案记录成 $p-i$，最后将答案输出即可。

可能表述得不清楚，具体见代码：

```cpp
/* 码风良好 */

#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int n, m, ans[N];
//ans记录答案，因为是倒序扫描，所以不能直接输出答案
//当然，你把ans换成栈也可以
bool f[N];

int main(){
	
	scanf("%d %d", &n, &m);
	for(int i = 1, a; i <= m; i++)
		scanf("%d", &a), f[a] = 1;
	for(int i = n, p; i; i--){
    //倒序扫描，p记录离当前天最近的放鞭炮的天的编号
		if(f[i]) p = i;
		ans[i] = p - i; //记录答案
	}
	for(int i = 1; i <= n; i++)
		printf("%d\n", ans[i]);//正序输出答案
	
	return 0;
}

/* MADE IN CHINA */
```

---

## 作者：xxr___ (赞：1)

**题意简述**

给定整数 $N,M$ 和递增的序列 $A_1,A_2,\dots,A_M$。求出 $i$ 从 $1$ 到 $N$，序列 $A$ 第一个大于等于 $i$ 的数减去 $i$ 的值。

**思路**

枚举 $i$ 从 $1$ 到 $N$，使用二分查找序列 $A$ 中第一个大于等于 $i$ 的数。函数如下。

```pascal
function find(x:longint):longint;
var
  l,r,mid,ans:longint;
begin
  l:=1;r:=m;ans:=1;
  while(l<=r)do begin
    mid:=(l+r) div 2;
    if(a[mid]>=x)then begin
      ans:=mid;
      r:=mid-1;
    end else begin
      l:=mid+1;
    end;
  end;
  find:=ans;
end;
```

因为是大于等于，所以在判断时要写：
```
if(a[mid]>=x)then begin
  ans:=mid;
  r:=mid-1;
end;
```

**完整代码**

```pascal
var
  a:array[1..200005]of longint;
  n,m:longint;

function find(x:longint):longint;
var
  l,r,mid,ans:longint;
begin
  l:=1;r:=m;ans:=1;
  while(l<=r)do begin
    mid:=(l+r) div 2;
    if(a[mid]>=x)then begin
      ans:=mid;
      r:=mid-1;
    end else begin
      l:=mid+1;
    end;
  end;
  find:=ans;
end;

var
  i:longint;
begin
  read(n,m);
  for i:=1 to m do begin
    read(a[i]);
  end;
  for i:=1 to n do begin
    writeln(a[find(i)]-i);
  end;
end.
```

---

## 作者：WBH_xh_WSD (赞：1)

1. [$\color {black} 原题题面$](https://atcoder.jp/contests/abc322/tasks/abc322_c)  
2. 题目翻译：  
Atcoder 王国举办了为期 $n$ 天的节日，其中有 $m$ 天放烟花。你要输出 $n$ 行，第 $i$ 行输出的是在烟花将在第 $i$ 天之后（含第 $i$ 天）首次燃放的时间。  
3. 思路：  
首先，输入数据，最好是再将数组 $a$ 排序。每次输入 $a_i$ 时，再用 map 记录 $a_i$ 天放烟花。  
然后，暴力枚举。暴力枚举的顺序是关键。首先特判，如果 $s_i$ 是 $1$，就直接输出 $0$。否则分类讨论，先找到 $1$ 和 $m$ 的中点，如果 $a_{mid}\geq i$ 且 $a_{mid-1} < i$，也就是说 $a_{mid}$ 为第 $i$ 天后首次放花的天数，所以直接输出答案；如果不满足条件，那么从 $mid+1$ 枚举，第一次 $a_j > i$ 时记录 $j$ 并退出循环，输出答案。  
**别忘了回车。**  
4. 代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;
int n,m;
int a[200010];
map<int,bool> s;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++)
		cin>>a[i],s[a[i]]=1;
	sort(a+1,a+m+1);
	for(int i=1;i<=n;i++){
		if(s[i]==1){
			cout<<"0\n";
			continue;
		}
		int mid=(1+m)>>1;
		if(a[mid]>=i&&a[mid-1]<i)
			cout<<a[mid]-i<<"\n";
		else if(a[mid]<i){
			int k;
			for(int j=mid+1;j<=m;j++){
				if(a[j]>i){
					k=j;
					break;
				}
			}
			cout<<a[k]-i<<"\n";
		}
		else{
			int k;
			for(int j=1;j<=mid;j++){
				if(a[j]>i){
					k=j;
					break;
				}
			}
			cout<<a[k]-i<<"\n";
		}
	}
	return 0;
}
```


---

## 作者：_shine_ (赞：0)

定义 $f_i$ 为里当前最近的数的差，则可发现当 $i$ 有数时，$f_i=0$，否则 $f_i=f_{i+1}+1$，所以每次维护数组 $f_i$，并且使用另一个数组记录当期节点是否有数即可。
#### code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
int n,m;
int f[maxn];
int a[maxn];
signed main(){
	cin >> n >> m;
	for(int i=1;i<=m;++i){
		cin >> a[i];
		f[a[i]]=-1;//a[i] 节点有数
	}
	int last=n;
	for(int i=n;i>=1;--i){
		if(f[i]==-1)f[i]=0;
        else f[i]=f[i+1]+1;
	}
	for(int i=1;i<=n;++i){
		cout << f[i] << endl;
	}
	return 0;
}

```


---

## 作者：_colin1112_ (赞：0)

## 简化题意

输入两个数 $N$、$M$，再输入一个长度为 $M$ 的上升序列 $a_i$，求在 $1\sim N$中每一个数在 $a_i$ 中，第一个大于等于它的数与它的差。

## 思路

二分模板题。

我们可以使用 STL 中二分模板函数 `lower_bound()` 来查找第一个大于等于所查找数的值，然后输出差值。

## AC Code

```c++
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;
const int E=1e6+5;
ll n,m;
ll arr[E];
int main(){
	cin >>n>>m;
	for(int i=1;i<=m;i++){
		cin >>arr[i];
	}
	for(int i=1;i<=n;i++){
		cout <<(arr[lower_bound(arr+1,arr+m+1,i)-arr])-i<<endl;
	}
	return 0;
}
```

---

## 作者：kkxacj (赞：0)

[[ABC322C] Festival](https://www.luogu.com.cn/problem/AT_abc322_c)

#### 思路

找到第一个离他最近的放烟花的日子，如果一个放烟花的日子比当前这一天早，那么他一定没有贡献了，因为这一个放烟花的日子一定比之后的日子早，所以模拟即可。

```
#include<bits/stdc++.h>
using namespace std;
int n,m,a[200010],o = 1;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= m;i++) scanf("%d",&a[i]);
	for(int i = 1;i <= n;i++)
	{
		while(a[o] < i) o++;//找到第一个离他最近的且大于它
		cout << a[o] - i << endl;
	}
	return 0;
}
```


---

## 作者：_xxxxx_ (赞：0)

### 题意

一个节日有 $n$ 天，期间会放 $m$ 次烟花。现在问每天可以看到的**下一次**烟花距离这一天有几天？

### 分析

很多大佬用的是二分，这里给出一种好懂的办法。

因为要输出每一天距离下一次烟花有多久，所以我们可以拿一个 $last$ 来记录上一次放完烟花的下一天，即第一个目前没有看到烟花的日子。

每次输入放烟花的时间后，$last$ 到这次放烟花的答案就可以得出来。每次更新 $last$ 为放完这次烟花的下一天即可。时间复杂度为 $O(n)$。

### 代码

```
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <cstdio>
#include <algorithm>
#define LL long long
using namespace std;
const int N = 2e5 + 10;
const int INF = 0x3f3f3f3f;
int n, m;
int a[N], ans[N];
signed main()
{
	cin >> n >> m;
	int last = 1;//第一个没看过的是第一天  
	for(int i = 1; i <= m; i++)
	{
		cin >> a[i];
		for(int j = last; j <= a[i] && j <= n; j++)//从last到这次放烟花 
		{
			ans[j] = a[i] - j;//到这次烟花的时间  
		}
		last = a[i] + 1;//下一个没看烟花的日子  
	}
	for(int i = 1; i <= n; i++)
	{
		cout << ans[i] << endl;
	}
	return 0;
}
```

可能会有人说：两重循环，这不是 $O(n^{2})$ 吗？

解释一下，里边的那个循环最多只会循环 $n$ 次。因为其取决于 $last$ 的变化，$last$ 只会从 $1$ 变到 $n$，所以它最多循环 $n$ 次。所以总的时间复杂度为 $O(n)$，可以通过此题。

---

## 作者：WilliamFranklin (赞：0)

首先声明：这是一篇时间复杂度为 $O(n)$ 的算法，类似于双指针。

### 主要思路

我们考虑建立一个指针 $now$ 和 $i$，表示第 $i$ 天以后的第一个节假日是 $a_{now}$，所以我们只需要从头枚举 $i$，就可求出 $i$ 天的答案，即为 $a_{now} - i$。特别的，直到当发现 $a_{now} = i$ 时，在求完当前 $i$ 所对应的答案后，$now$ 再加 $1$；否则，$now$ 不变。

具体看代码。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define mp(Tx, Ty) make_pair(Tx, Ty)
#define For(Ti, Ta, Tb) for(auto Ti = (Ta); Ti <= (Tb); Ti++)
#define Dec(Ti, Ta, Tb) for(auto Ti = (Ta); Ti >= (Tb); Ti--)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define range(Tx) begin(Tx),end(Tx)
const int N = 2e5 + 5;
int a[N];
int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; i++) cin >> a[i];
	int now = 1;
	for (int i = 1; i <= n; i++) {
		cout << a[now] - i << endl;
		if (a[now] == i) {
			now++;
		}
	}
	return 0;
} 
```

### 谢谢观看

---

## 作者：_Trangle_ (赞：0)

此题极水，就是寻找与第 $i$ 个时间点第一个同时或晚的烟花时间。

而 $i$ 单调递增，所以问题答案单调，可用双指针。

### AC code：
```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m;
int a[200005];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) scanf("%d", a + i);
	for (int i = 1, j = 1; i <= n; i++) {
		while (a[j] < i) j++; //双指针
		printf("%d\n", a[j] - i);
	}
	return 0;
}
```

---

## 作者：YuTianQwQ (赞：0)

刚看见这个题时有点懵，打了半天发现自己脑抽了。

一道简单的模拟，直接用当天的时间与放烟花的时间相同将烟花时间增加一天。

```c++
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> a(m);
    for (int i = 0; i < m; i++) cin >> a[i];
    for (int i = 1, j = 0; i <= n; i++)
    {
        cout << a[j] - i << endl; // 输出每天距离下一次烟花是多久
        if(a[j] == i)
            j++;
    }
    return 0;
}
```

---

## 作者：Soul_Wanderer (赞：0)

# 题解

## [题目链接](https://www.luogu.com.cn/problem/AT_abc322_c)

## 题目大意

给你长为 $m$ 递增的序列，求对于 $1$ 到 $n$ 中每个数，找到在序列中第一个大于等于它的数，输出它与这个数的差。

## 解题思路

提供一个新思路。

我用一个队列存下这个递增序列，我们可以 $1$ 到 $n$ 循环，对于每一个数，如果队首大于等于它，输出；若小于它，由于是递增的，则此时队首对后续运行一定没有贡献，弹出，继续比较，直到队首大于等于它，输出，具体详见代码。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+10;
int n,m;
int a[N];
queue<int >que;
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>a[i],que.push(a[i]);
	for(int i=1;i<=n;i++){
		while(que.front()<i){
			que.pop();
		}
		cout<<que.front()-i<<endl;
	}
	return 0;
}
```

---

## 作者：BugGod (赞：0)

## 题目大意
给定一个序列，求对于每个 $i(1\le i\le n)$，在序列中第一个大于等于 $i$ 的数与 $i$ 的差。

## Solution
 `lower_bound` 函数可以直接用 $O(\log n)$ 的时间复杂度求解第一个大于等于 $i$ 的数在序列中的地址，那么我们在地址前加一个 `*`，即可得到这个数的数值。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[200010];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n;i++)
	{
		cout<<*lower_bound(a+1,a+1+m,i)/*求这个数的数值*/-i<<endl;
	}
	return 0;
}
```

---

## 作者：watcher_YBH (赞：0)

# 思路：
这道题目是让我们求：从第 $i$ 个位置开始，第一个放烟花的日子距离 $i$ 第几天。所以我们可以倒着来看：假设答案序列为 $a$，那么 $a_n$ 就一定为零（题目保证了最后一天一定放烟花），如果第 $i$ 天放烟花，那么 $a_i$ 为零，如果第 $i$ 天不放烟花，那么 $a_i$ 为 $a_{i+1}+1$。
# 代码：
```
#include<bits/stdc++.h>
#define ll long long
#define max(a,b) ((a>b)?a:b)
#define min(a,b) ((a<b)?a:b)
using namespace std;
const int MAX = 2e5+5;
int n,m;
int a[MAX],t[MAX],sum[MAX];
int main(){
	cin>>n>>m;
	for(int i = 1; i<=m; i++)
		cin>>a[i],t[a[i]]++;// 标记
	sum[n] = 0;
	for(int i = n; i>=1; i--){
		if(t[i]) sum[i] = 0;// 这天放烟花
		else sum[i] = sum[i+1]+1;// 不放
	}
	for(int i = 1; i<=n; i++)// 输出答案
		cout<<sum[i]<<endl;
	return 0;
}


```


---

## 作者：heyx0201 (赞：0)

# Festival 题解
## Meaning
> 给定 $N$ 和 $M$，还有 $M$ 个正整数 $a_1 \sim a_n$，对于每个 $i \le n$，求出 $a$ 中第一个大于等于 $i$ 的整数和 $i$ 的差。

## Solution
题目保证 $a$ 数组单增，所以就可以用二分函数 `lower_bound` 来寻找答案。

`lower_bound` 的用法为：

`lower_bound(a + 1,a + m + 1,x) - a`，表示 $a$ 数组中第一个大于等于 $x$ 的数的地址，要减去 $a$ 的地址（也就是 $a_0$ 的地址）才能得到位置。

## Accept Code
[Accept Record](https://www.luogu.com.cn/record/127252534)
```cpp
#include<iostream>
#include<algorithm>

using namespace std;

const int MAXN = 2e5 + 10;

int n,m,a[MAXN];

int main(){
  cin >> n >> m;
  for (int i = 1; i <= m; i++){
    cin >> a[i];
  }
  sort(a + 1,a + m + 1);
  for (int i = 1; i <= n; i++){
    cout << a[lower_bound(a + 1,a + m + 1,i) - a] - i << '\n';
  }
  return 0;
}

```

---

## 作者：BLuemoon_ (赞：0)

[link](https://www.luogu.com.cn/problem/AT_abc322_c)

## 题意

有 $N$ 天，其中有 $M$ 天放烟花，分别是 $A_1 , A_2 , A_3 , \cdots , A_M$，告诉你哪些天放烟花，请求出每一天，即 $1 \sim N$ 天，这一天之后的最近的放烟花的天数是哪一天。如果今天放烟花，那么这一个数值为 $0$。保证 $A_M = N$，即最后一天一定放烟花。

## 思路

递推，只不过要倒着来。

令递推数组为 $C$，因为最后一天一定放烟花，所以 $C_N = 0$。

接着往前推，如果第 $i$ 天不放烟花，那么 $C_i = C_{i + 1} + 1$，因为今天是明天的昨天，所以今天比明天多 $1$。

如果第 $i$ 天放烟花，那么根据题意 $C_i = 0$。

因为 $A_i \le n$，所以记录第 $i$ 放不放烟花可以直接开桶。

根据思路递推即可。

## 代码

```cpp
// J2023 | BLuemoon_
#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 2e5 + 5;

int n, m, a[kMaxN], c[kMaxN];

int main() {
  cin >> n >> m;
  for (int i = 1, x; i <= m; i++) {
    cin >> x;
    a[x] = 114514; //不要在意这个数字，只要非0就行了
  }
  c[n] = 0;
  for (int i = n - 1; i; i--) {
    c[i] = (a[i] ? 0 : c[i + 1] + 1);
  }
  for (int i = 1; i <= n; i++) {
    cout << c[i] << '\n';
  }
  return 0;
} 
```

---

## 作者：CheZiHe929 (赞：0)

# AT_abc322_c 题解

### 简要题意

有一场为期 $n$ 天的活动，会进行 $m$ 次烟花的燃放，第 $i$ 次烟花燃放在 $a_i$ 天。问你每一天距离下一次烟花燃放的时间，如果当天燃放烟花，答案就是 $0$。

### 简要思路

把每一次烟花燃放的时间记录到数组中，然后记录一个指针，指向下一次燃放烟花是第几次，当燃放烟花时就让指针后移一位。

### 完整代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
const int MAXN=2e5+5;

int n,m;
int a[MAXN]; 
int p;//指针 

signed main(){
    std::cin>>n>>m;
    for(int i=1;i<=n;i++)std::cin>>a[i];
    
    for (int i=1;i<=n;i++){
        std::cout<<a[p]-i<<endl;//距离下次燃放烟花的时间 
        if(a[p]==i)p++;//指针后移 
    }
    return 0;
}
```

**THE END.**

**THANK YOU.**

---

## 作者：Crazyouth (赞：0)

**分析**

对于每一个 $i$，使用 `lower_bound()` 函数找到它后面最近的一次放鞭炮，用哪个日期减 $i$ 就行了。

**AC Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[int(2e5+10)];
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>a[i];
	for(int i=1;i<=n;i++)
	{
		if(i<=a[1]) cout<<a[1]-i<<endl;
		else cout<<a[lower_bound(a+1,a+m+1,i)-a]-i<<endl;
	}
	return 0;
}

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc322_c)

## 题目大意

$N$ 天中有 $M\space (1\le M\le N)$ 天放烟花，求第 $i\space (1\le i\le N)$ 天距离下次放烟花还有多长时间。

- 若第 $i$ 天正好是放烟花的一天，那么距离下次放烟花还有 $0$ 天。

给定所有放烟花的天 $A_1,A_2,A_3,...,A_M$。

## 思路

如果我们暴力枚举，时间复杂度就是 $\mathcal{O}(N^2)$，肯定过不了 $2\times 10^5$ 的数据，所以我们考虑用二分查找，时间复杂度 $\mathcal{O}(N\log M)$，肯定能过。

读入数据后将所有放烟花的天从小到大排序。之后循环 $M$ 次，第 $i\space (1\le i\le N)$ 次代表第 $i\space (1\le i\le N)$ 天。每次循环用 ``lower_bound`` 函数查找第 $i\space (1\le i\le N)$ 天后下次放烟花的天并减去 $i\space (1\le i\le N)$ 就是距离下次放烟花的天数。接着输出即可。

## AC Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define pb push_back
#define pf push_front
#define pob pop_back
#define pof pop_front
#define pii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define pil pair<int,ll>
#define fi first
#define se second
using namespace std;
inline ll read(){//快读。
	ll k=0,flag=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')flag=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		k=(k<<1)+(k<<3)+(c^48);
		c=getchar();
	}
	return k*flag;
}
inline void print(ll x){//快写。
    if(x<0){
        putchar('-');
        x=-x;
    }
    ll y=10,len=1;
    while(y<=x){
        y=(y<<1)+(y<<3);
        len++;
    }
    while(len--){
        y/=10;
        putchar(x/y+48);
        x%=y;
    }
}
const int N=2e5+10;
int n,m,a[N];
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;++i)a[i]=read();
	sort(a+1,a+1+m);//注意是到 m。
	for(int i=1;i<=n;++i){
		int p=lower_bound(a+1,a+1+m,i)-a;
		print(a[p]-i);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：Lydia1010__ (赞：0)

## 本题思路：
这道题其实很简单，并不用之前大佬所说的二分。因为他每天只用找之后第一个放烟花的日期与他的差，我们就可以贪心，把每一个有烟花的天数存起来，随后一天一天扫过去，发现天数超了就往后移到有烟花的天数即可。
## 本题代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200001];
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>a[i];
	}
	int u=1;
	for(int i=1;i<=n;i++)
	{
		if(i<=a[u]) cout<<a[u]-i<<endl;
		else u++,cout<<a[u]-i<<endl;
	}
	return 0;
}

```


---

## 作者：_7Mr (赞：0)

# 思路
我们将每一个放烟花的时间记录下来，我们再从后往前扫一遍，如果当前要放烟花，那么我们从当前到下个放烟花的最近时间就是当前这个时间。
# ACcode
```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
#define INF INT_MAX
using namespace std;
const int maxn=2e5+5;
int n,m;
int a[maxn],sum[maxn];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>a[i];
	int p,q=m+1;//从前往后扫
	for(int i=n;i>=1;i--){
		if(i==a[q-1]){//当前要放烟花
			p=a[q-1];
			q--;
		}
		sum[i]=p-i;
	}
	for(int i=1;i<=n;i++) cout<<sum[i]<<endl;
	return 0;
}

```

---

## 作者：Mu_leaf (赞：0)

不明白为什么非要用 $O(n \log n)$ 的做法。

-----
## 正文：
#### 问题陈述

AtCoder 王国举行为期 $N$ 天的节日活动。在其中的 $M$ 天，即第 $A_1$ 天、第 $A_2$ 天、第 $\dots$ 天、第 $A_M$ 天，将燃放烟花。可以保证的是，烟花将在节日的最后一天燃放。(换句话说，$A_M=N$ 是有保证的）。

求每个 $i=1,2,\dots,N$ 的解。

- 从第 $i$ 天开始，第 $i$ 天或以后的第几天会首次燃放烟花？如果在 $i$ 日燃放烟花爆竹，则视为 $0$ 天后。

#### 思路：
在燃放烟花那天用桶存一个 $1$，然后通过后缀和直接求出当前天到最近放烟花的日子数，如果当前天也要放烟花那就不管咯。

因为在开始的那天多存了一个 $1$ 所以输出的时候减 $1$ 就好啦。


#### [Code：](https://atcoder.jp/contests/abc322/submissions/46073310)

---

