# Pacifist frogs

## 题目描述

拇指姑娘出了事故。她发现自己在沼泽地中央的一个小岛上，非常想去海边。

只有沿着一条连接小岛和海岸的路线，才能到达海岸。让我们假设这些山丘是从 $1$ 到 $n$，$n$ 等于它与岛屿之间的距离(以米为单位)。这座山和海岸也是 $1$ 米。

拇指姑娘太小了，不能跳。幸运的是，一家生活在沼泽里的青蛙建议帮助她。每只青蛙都同意让拇指姑娘搭便车，但是拇指姑娘应该只选择一只青蛙。每只青蛙都有一定的跳跃长度。如果拇指姑娘同意接受一只青蛙的帮助，它的跳跃长度是 $d$，青蛙会从山上的岛上跳到山丘 $d$ 上，然后在山丘 $2\times d$，然后 $3\times d$ 等等，直到他们到达岸边(也就是在山那边发现自己)。

然而，还有一个问题：蚊子也生活在沼泽里。此刻，他们正在一些山丘上小睡。如果青蛙跳到有蚊子的山上，青蛙就会把蚊子击碎。拇指姑娘遇到的青蛙都是和平主义者，所以他们会发现每一只蚊子的死亡都是非常可悲的。帮助拇指姑娘选择一只能带她上岸的青蛙，并尽可能少地击碎蚊子。

## 样例 #1

### 输入

```
5 3 5
2 3 4
1 2 3 4 5
```

### 输出

```
2
2 3
```

## 样例 #2

### 输入

```
1000000000 2 3
2 5
999999995 999999998 999999996
```

### 输出

```
1
2
```

# 题解

## 作者：_xbn (赞：4)

拿到题大家肯定都想到了桶的做法，但 n 太大，数组存不下，于是我们转换思路。

看到 m 和 k 很小，我们可以以此为突破口，注意每只青蛙每次跳的距离固定，

我们设它为 $g(i)$ ,那如果有一只蚊子在 $g(i)$ 的倍数的位置上，那这只青蛙

一定能吃了它，所以我们枚举每一只蚊子能被那几只青蛙吃掉，再取一个

最小值就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=102;
int n,m,k,p,q,ans=0x7fffffff,sum,tot,cnt,a[N],b[N],c[N],d[N],g[N],t;
int main()
{
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++)
	{
		cin>>g[i];
	}
	for(int i=1;i<=k;i++)
	{
		cin>>d[i];
		for(int j=1;j<=m;j++)
		{
			if(d[i]%g[j]==0)a[j]++;
		}
	}
	for(int i=1;i<=m;i++)
	{
		ans=min(ans,a[i]);
	}
	for(int i=1;i<=m;i++)
	{
		if(a[i]==ans)
		{
			tot++;
			b[tot]=i;
		}
	}
	cout<<tot<<endl;
	for(int i=1;i<=tot;i++)
	{
		cout<<b[i]<<" ";
	}
}
```





---

## 作者：ofsl (赞：4)

题目链接：[CF39F Pacifist frogs](https://www.luogu.com.cn/problem/CF39F)

宣传一下[我的博客](https://www.luogu.com.cn/blog/302437/)
## 翻译解释：
重点讲一下输出格式。第一行输出击碎了最少的蚊子的青蛙个数，然后在第二行按编号（从 1 到 m）排序，依次输出这些青蛙的编号。
## 思路：
用一个结构体保存青蛙的数据，然后重载运算符（或定义比较文件），先按击碎的蚊子数量从小到大排序，再给击碎的蚊子数量相同的青蛙按照编号从小到大排序。输入完青蛙后，每输入一只蚊子的位置 a 就遍历一遍青蛙数组，检查是否会踩到并计数。详情见代码。

代码时间复杂度为 $O(mk)$。

题目难度大概是普及-。
```cpp
#include<bits/stdc++.h>
using namespace std;
struct frog{
	int k,d,id;//k记录踩碎蚊子的数量，d记录跳的距离，id记录编号 
	bool operator<(const struct frog&a)const{
		if(k==a.k)return id<a.id;
		return k<a.k;
	}
}f[105];
int n,m,k,ans; 
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;i++){
		scanf("%d",&f[i].d);
		f[i].id=i;
	}
	for(int i=1,a;i<=k;i++){
		scanf("%d",&a);
		for(int j=1;j<=m;j++)
			if(a%f[j].d==0)//如果蚊子的位置被青蛙跳跃的距离整除，说明青蛙会踩到蚊子 
				f[j].k++;
	}
	sort(f+1,f+m+1);
	for(int i=1;i<=m&&f[i].k==f[1].k;i++)//记录踩到最少蚊子的青蛙个数 
		ans++; 
	printf("%d\n",ans);
	for(int i=1;i<=ans;i++)
		printf("%d ",f[i].id);
    return 0;
}
```

新人的第一篇题解求赞qwq

---

## 作者：zlqwq (赞：2)

省流：最水的 F 题了!

$n$ 有 $1e9$，所以说直接开桶会爆掉。

所以我们直接枚举，将青蛙所有调到的地方标记一下，然后直接处理一下有多少只蚊子会被吃掉。

最后把吃掉蚊子的个数取 $\min$ 即可。

小小的细节：这个数据范围懂得都懂。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k;
int d[105],p[105],cnt[105];
vector<int> ans;
signed main(){
    cin>>n>>m>>k;
    for(int i=1;i<=m;++i)cin>>p[i];
    for(int i=1;i<=k;++i)cin>>d[i];
    for(int i=1;i<=k;++i)for(int j=1;j<=m;++j){
            if(d[i]%p[j]==0){
                cnt[j]++;
            }
        }
    int o=1e18,sum=0;
    for(int i=1;i<=m;++i)o=min(o,cnt[i]);
    for(int i=1;i<=m;++i)if(cnt[i]==o){
        sum+;
        ans.push_back(i);
    }
    cout<<sum<<"\n";
    for(int a:ans)cout<<a<<" ";
    return 0;
}
```

---

## 作者：ljk8886 (赞：1)

## 题目分析
这道题肯定可以用桶做，但 $1 \le n \le 10^9$，存不下，得再换一种方法。

观察题目，可以发现每只青蛙的跳跃的长度是固定的。所以，我们只需要判断每只蚊子所在的位置是不是青蛙的跳跃的长度，如果是，就加到这只青蛙吃蚊子的数量中。最后再算一下最小值和最小值的个数。时间复杂度 $O(mk)$。

## 代码
```cpp
#include <bits/stdc++.h>
#define ft first
#define sd second
#define endl '\n'
#define pb push_back
#define md make_pair
#define gc() getchar()
#define pc(ch) putchar(ch)
#define umap unordered_map
#define pque priority_queue
using namespace std;
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 bint;
typedef pair<int, int> pii;
typedef pair<pii, int> pi1;
typedef pair<pii, pii> pi2;
const ll INF = 0x3f3f3f3f;
inline ll read()
{
	ll res = 0, f = 1;
	char ch = gc();
	while (ch < '0' || ch > '9') f = (ch == '-' ? -1 : f), ch = gc();
	while (ch >= '0' && ch <= '9') res = (res << 1) + (res << 3) + (ch ^ 48), ch = gc();
	return res * f;
}
inline void write(ll x)
{
	if (x < 0) x = -x, pc('-');
	if (x > 9) write(x / 10);
	pc(x % 10 + '0');
}
inline void writech(ll x, char ch) { write(x), pc(ch); }
const int N = 1e2 + 5;
int n = read(), m = read(), k = read();
int d[N], p[N], ans[N], minn = INT_MAX, cnt;
int main()
{
	for (int i = 1; i <= m; i++) d[i] = read();
	for (int i = 1; i <= k; i++) p[i] = read();
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= k; j++)
			if (p[j] % d[i] == 0) ans[i]++; //是否是跳跃长度的倍数 
		if (ans[i] == minn) cnt++; // 统计最小值的个数 
		else if (ans[i] < minn) minn = ans[i], cnt = 1; // 更新最小值 
	}
	writech(cnt, '\n');
	for (int i = 1; i <= m; i++)
		if (ans[i] == minn) writech(i, ' ');
	return 0;
}
```

---

## 作者：Stars_visitor_tyw (赞：1)

## 题解：CF39F Pacifist frogs
### 分析
简单题。

观察到青蛙跳动的步数固定，则看下哪只蚊子会被青蛙吃掉（即寻找位置为青蛙跳动步数的倍数的蚊子），统计每只会吃掉多少蚊子，找最小值然后把所有吃掉蚊子的个数为最小值的青蛙都输出即可。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, m, k;
int d[105], p[105], cnt[105];
vector<int> ans;
signed main()
{
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++)
    {
        cin>>p[i];
    }
    for(int i=1;i<=k;i++)cin>>d[i];
    for(int i=1;i<=k;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(d[i]%p[j]==0)
            {
                cnt[j]++;
            }
        }
    }
    int num=1145141919810, cc=0;
    for(int i=1;i<=m;i++)num=min(num,cnt[i]);
    for(int i=1;i<=m;i++)
    {
        if(cnt[i]==num)
        {
            cc++;
            ans.push_back(i);
        }
    }
    cout<<cc<<"\n";
    for(int x:ans)cout<<x<<" ";
}

---

## 作者：beigongbaishan (赞：1)

# 题意简述
有 $m$ 只青蛙，编号为 $i$ 的青蛙可以跳到编号为 $i$ 的倍数的山上，有 $k$ 座山上有蚊子在睡觉，如果青蛙跳到有蚊子的山上，那么那座山上的蚊子会被击碎。

请问有几只青蛙可以使击碎的蚊子最少，输出数量和它们的编号。
# 思路概括
我们可以开一个桶，把每只青蛙击碎的蚊子数量存进去，然后取其最小值，最后把与最小值击碎数量一样的青蛙输出即可。
# AC CODE
```cpp
#include<iostream>//cin,cout,min需调用 
#include<climits>//INT_MAX需调用 
#include<cstring>//memset需调用 
using namespace std;
int n,m,k,fro[105],mos[105],bar[105],minx=INT_MAX,ans;
int main(){
	cin>>n>>m>>k;//n好像没啥用…… 
	for(int i=1;i<=m;i++)cin>>fro[i];//输入青蛙编号 
	for(int i=1;i<=k;i++){//枚举每只蚊子能被哪些青蛙击碎 
		cin>>mos[i];//输入有蚊子的山的编号 
		for(int j=1;j<=m;j++){
			if(mos[i]%fro[j]==0)bar[j]++;//如果能击碎就装桶里面 
		}
	}
	for(int i=1;i<=m;i++)minx=min(minx,bar[i]);//取最小值 
	memset(mos,0,sizeof(mos));//废物利用节省空间，拿来存青蛙（不清空也行，本人有强迫症） 
	for(int i=1;i<=m;i++){
		if(bar[i]==minx){//与最小值击碎数量一样 
			ans++;//总数加1 
			mos[ans]=i;//存下编号 
		}
	}
	cout<<ans<<endl;//输出总数 
	for(int i=1;i<=ans;i++)cout<<mos[i]<<" ";//输出编号 
	return 0;
}
```
[AC](https://www.luogu.com.cn/record/171539461)

---

## 作者：20111019Yu (赞：1)

### 题意
有一个长度为 $m$ 的序列 $a$ 和长度 $k$ 的序列 $b$。问对于每个 $a_{i}$，求他在 $b$ 中的倍数的个数，输出最小值的个数和对应的 $a$ 中的下标。
### 思路
用 $cnt_{i}$ 存个数。循环枚举 $a_{i}$，$b_{j}$，若 $a_{i}$ 整除 $b_{j}$，$cnt_{i}$ 加 $1$。最后循环几遍输出答案。
### code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, m, k, a[105], b[105], c[105], minn = 1e9, ans;

signed main(){
	cin >> n >> m >> k;
	for( int i = 1; i <= m; i++ ) cin >> a[i];
	for( int i = 1; i <= k; i++ ) cin >> b[i];
	for( int i = 1; i <= m; i++ ){
		for( int j = 1; j <= k; j++ ){
			if(b[j] % a[i] == 0) c[i]++;
		}
	}
	for( int i = 1; i <= m; i++ ) minn = min(minn, c[i]);
	for( int i = 1; i <= m; i++ ) if(minn == c[i]) ans++;
	cout << ans << '\n';
	for( int i = 1; i <= m; i++ ) if(c[i] == minn) cout << i << " ";
	return 0;
} 
```

---

## 作者：OIerWu_829 (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/CF39F)

学校信息社团比赛时做出来的一道题，发篇题解纪念一下。

## 思路

题目说，第 $i$ 只青蛙有自己固定的跳跃距离 $d_i$，那么当一只蚊子在 $d_i$ 的倍数的位置上睡觉，那么就一定会被击碎。我们可以用 $b$ 数组记录击碎的蚊子数量，取最小值，最后判断相等，输出编号就可以了。

有一个要注意的地方：

取最小值时，一开始我用的是 sort 排序，但输出一直错误，然后才注意到排完序会打乱编号的顺序，所以可以用擂台法不断取最小值避免这个错误。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 100 + 10;
int a[N], d[N], b[N], ans[N];
int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++)
        cin >> d[i];
    for (int i = 1; i <= k; i++) {
        cin >> a[i];
        for (int j = 1; j <= m; j++)
            if (a[i] % d[j] == 0)
                b[j]++;
    }
    int minn = 1e9;
    for (int i = 1; i <= m; i++)
        if (b[i] < minn) minn = b[i];
    int cnt = 0;
    for (int i = 1; i <= m; i++)
        if (b[i] == minn)
            ans[++cnt] = i;
    cout << cnt << endl;
    for (int i = 1; i <= cnt; i++)
        cout << ans[i] << " \n"[i == cnt];
    return 0;
}
```

---

## 作者：_zhaosihan_qwq_ (赞：1)

# 题解：CF39F Pacifist frog
[**题目传送门**](https://www.luogu.com.cn/problem/CF39F)
## 思路：
这道题也是十分水，简单 for 循环列举一下每只青蛙到达的山峰和吃掉的虫子，如果吃了就使那只青蛙所对应的数组加一，最后只要把每只青蛙吃的虫子循环取最小值，进行输出就可以了。
## 注意：
- 头文件是否都写了（忘了的可以直接写万能头）。
- 一定要循环求最小值，不要用 sort。
- 注意数据范围 $1e9$ ，开 long long 比较保险（不开也能过，但要养成良好习惯）。
## 完整代码

```cpp
#include<iostream>
#include<vector>
#include<cmath>
#include<limits.h>
using namespace std;
vector <int> sum;
int n,m,k,c[105],l[105],cnt[105];
int main(){
    cin>>n>>m>>k;
    for(int i=1;i<=m;++i) {
		cin>>l[i];
	}
    for(int i=1;i<=k;++i){
		cin>>c[i];
	}
    for(int i=1;i<=k;++i){
		for(int j=1;j<=m;++j){
		    if((c[i])%(l[j])==0){
		        cnt[j]+=1;
		    }
	    }
	}
    int r=INT_MAX;
    for(int i=1;i<=m;++i){
		r=min(r,cnt[i]);
	}
	int jg=0;
    for(int i=1;i<=m;++i){
		if(cnt[i]==r){
	        jg+=1;
	        sum.push_back(i);
	    }	
	}
    cout<<jg<<endl;
    for(int a:sum){
		cout<<a<<' ';
	}
    return 0;
}
```
谢谢观看，谦虚收尾

---

## 作者：飞啾6373 (赞：1)

### 题意

题面不难理解。每个青蛙都有一个固定的跳跃距离，每次跳跃都跳出一个跳跃距离的长度（每个青蛙都能到达终点），每个蚊子有一个坐标。青蛙跳到蚊子的坐标上就会踩到蚊子，需要找出踩到最少蚊子的青蛙。

题面中的输出第一行是踩到最少蚊子的青蛙的数量（注意是青蛙的数量，不是蚊子），第二行是每只踩到最少蚊子的青蛙的编号，用空格隔开。

### 思路

思路还是比较容易想到的。用一个数组存储每只青蛙踩到的蚊子的数量，枚举该数组，找到最小值后再枚举一遍，统计踩到最少蚊子的青蛙的数量，最后循环输出每一只青蛙的编号。

可以使用模判断每一只蚊子是否被当前青蛙踩到。如果当前蚊子所处的坐标是青蛙跳跃距离的倍数，那么就会被青蛙踩。

（由于本题中 $ m $ 和 $ k $ 的值都很小，所以可以放心使用二重循环，不会超时）

### 代码


```
#include<bits/stdc++.h>
using namespace std;
long long d[121],a[121],qwq[121];
int main()
{
	long long n,m,k,i,j,mins=121,ans=0;
	cin>>n>>m>>k;
	for(i=0;i<m;i++)cin>>d[i];
	for(i=0;i<k;i++)cin>>a[i];
	for(i=0;i<m;i++)
	{
		for(j=0;j<k;j++)
		{
			if(a[j]>=d[i]&&a[j]%d[i]==0)
			{
				qwq[i]++;
			}
		}
		mins=min(qwq[i],mins);
	}
	for(i=0;i<m;i++)
	{
		if(qwq[i]==mins)ans++;
	}
	cout<<ans<<endl;
	for(i=0;i<m;i++)
	{
		if(qwq[i]==mins)cout<<i+1<<" ";
		//注意，这里的i从0开始，所以青蛙的编号是下标+1
	}
	return 0;
 }
```


---

## 作者：miraculously (赞：1)

排坑：

这道题的翻译有点模糊，题目第一行要输出的是踩死最少蚊子的青蛙的个数，
而不是踩死最少蚊子的数量。

分析：

容易发现只要蚊子所在山丘的编号被青蛙跳跃长度整除，
那么这只青蛙就能踩死这只蚊子。




```cpp
#include<bits/stdc++.h>
using namespace std;
struct name{
	int cnt,id,len;//cnt表示青蛙踩死的蚊子数，id表示青蛙的编号，len表示青蛙跳跃长度
}a[101];
bool cmp(name x,name y)
{
	if(x.cnt==y.cnt)
	return x.id<y.id;
	return x.cnt<y.cnt;
}//按踩死蚊子的数量排序，如果数量一样，按编号从小到大排序
int main()
{
	int n,m,k,x;
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&a[i].len);
		a[i].id=i;
	}
	for(int i=1;i<=k;i++)
	{
		scanf("%d",&x);
		for(int i=1;i<=m;i++)
		if(x%a[i].len==0)
		a[i].cnt++;
	}
	sort(a+1,a+m+1,cmp);
	int ans=1;
	for(int i=2;i<=m;i++)
	{
		if(a[i].cnt==a[i-1].cnt)
		ans++;
		else
		break;
	}//排序后，第一个青蛙踩死蚊子数量一定最小，如果和第一个不一样，直接退出循环，否则，青蛙数量+1
	printf("%d\n%d ",ans,a[1].id);
	for(int i=2;i<=m;i++)
	{
		if(a[i].cnt==a[i-1].cnt)
		printf("%d ",a[i].id);
		else
		break;
	}
}
```


---

## 作者：Zhang_Shao_ (赞：0)

## 题意
有 $m$ 只青蛙，编号为 $i$ 的青蛙可以跳到编号为 $i$ 的倍数的山上，有 $k$ 个山丘上有蚊子，求遇到有蚊子的山丘最少的青蛙的数量和它们的编号。
## 解法
这道题其实只需要用循环结构扫一遍就好了。

先输入，接着遍历每只青蛙与每只蚊子，然后计算每只青蛙遇到蚊子的个数，对其进行排序，最后输出。（详见代码注释）

使用 `sort` 函数能对数组进行排序。

时间复杂度大约为 $O(mk)$。
## 代码
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int mount[105];//记录蚊子睡觉的山丘
struct node{
	int len,cnt,name;//青蛙的跳跃长度、遇到蚊子的个数以及序号
}frog[105];
bool cmp1(node t1,node t2){
	return t1.cnt<t2.cnt;//对遇到蚊子的个数进行排序
}
bool cmp2(node t1,node t2){
	return t1.name<t2.name;//对序号进行排序
} 
int main(){
	int n,m,k,flag=1;
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;i++){
		scanf("%d",&frog[i].len);
		frog[i].name=i;
	}
	for(int i=1;i<=k;i++){
		scanf("%d",&mount[i]);
	}
    //输入
	for(int i=1;i<=m;i++){
		for(int j=1;j<=k;j++){
			if(mount[j]%frog[i].len==0) frog[i].cnt++;
		}
	}//计算每只青蛙遇到蚊子的个数
	sort(frog+1,frog+m+1,cmp1);//排序
	for(int i=2;i<=m;i++){
		if(frog[i].cnt==frog[i-1].cnt){
			flag=i;
		}else{
			break;
		}
	}//计算个数
	sort(frog+1,frog+flag+1,cmp2);//排序
	printf("%d\n",flag);
	for(int i=1;i<=flag;i++){
		printf("%d ",frog[i].name);
	}
    //输出
	return 0;
}//结束
``````

---

## 作者：glass_goldfish (赞：0)

~~本题很水。~~  
通过观察题目，我们发现，在山丘 $x$ 上的蚊子会被所有能将其整除的青蛙踩碎（即为 $n$ $\bmod$ $i=0$）。所以，我们开一个数组 $p_i$，代表每只青蛙会踩碎的蚊子的数量。我们通过枚举，可以计算出每只青蛙踩碎蚊子的数量。接着，计算出最小值，即可通过本题。  
~~十年 OI 一场空，不开 long long 见祖宗。~~

---

## 作者：linjinkun (赞：0)

由于讨论区的两篇翻译输出格式完全错误，所以在此提供题目描述。

### 题目描述
拇指姑娘出了事故。她发现自己在沼泽地中央的一个小岛上，非常想去海边。

只有沿着一条连接小岛和海岸的路线，才能到达海岸。让我们假设这些山丘是从 $1$ 到 $n$，$n$ 等于它与岛屿之间的距离（以米为单位）。这座山和海岸也是 $1$ 米。

拇指姑娘太小了，不能跳。幸运的是，一家生活在沼泽里的青蛙建议帮助她。每只青蛙都同意让拇指姑娘搭便车，但是拇指姑娘应该只选择一只青蛙。每只青蛙都有一定的跳跃长度。如果拇指姑娘同意接受一只青蛙的帮助，它的跳跃长度是 $d$，青蛙会从山上的岛上跳到山丘 $d$ 上，然后在山丘 $2\times d$，然后 $3\times d$ 等等，直到他们到达岸边（也就是在山那边发现自己）。

然而，还有一个问题：蚊子也生活在沼泽里。此刻，他们正在一些山丘上小睡。如果青蛙跳到有蚊子的山上，青蛙就会把蚊子击碎。拇指姑娘遇到的青蛙都是和平主义者，所以他们会发现每一只蚊子的死亡都是非常可悲的。帮助拇指姑娘选择一只能带她上岸的青蛙，并尽可能少地击碎蚊子。
### 输入格式
第一行包含三个整数。$n,m,k (1\le n\le10^9, 1\le m,k\le100)$ 表示山丘、青蛙和蚊子的数量。第二行包含 $m$ 整数 $d_i(1\le d_i\le10^9)$，表示青蛙跳跃的长度。第三行包含 $k$ 个整数表示每只蚊子睡觉的山丘（位置）。每座山丘上只能有一只蚊子睡觉。行中的数字由单个空格分隔。
### 输出格式
第一行输出有多少只青蛙能满足带拇指姑娘上岸并且击碎的蚊子最少，在第二行升序输出这些青蛙的编号。

### 解题思路
不难想到，青蛙和蚊子都是突破这道题的办法，这里选择蚊子，我们可以开一个桶记录每只青蛙能吃多少蚊子，最后取个最小值即可。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int num[105];
int a[105];
int b[105];
signed main()
{
	int n,m,k;
	scanf("%d %d %d",&n,&m,&k);
	for(int i = 1;i<=m;i++)
	{
		scanf("%d",&a[i]);
	}
	for(int i = 1;i<=k;i++)//枚举每一只蚊子，其实也可以枚举每一只青蛙
	{
		int x;
		scanf("%d",&x);
		for(int j = 1;j<=m;j++)//枚举每一只青蛙
		{
			if(x%a[j] == 0)//如果这只蚊子能被第j只青蛙吃掉，那么第j只青蛙能吃掉的蚊子数量+1
			{
				num[j]++;
			}
		}
	}
	int minn = 1e9;//取最小值，所以初始化为最大值
	for(int i = 1;i<=m;i++)
	{
		minn = min(minn,num[i]);//取最小的吃掉蚊子数量
	}
	int cnt = 0;
	for(int i = 1;i<=m;i++)
	{
		if(num[i] == minn)//如果这只青蛙吃掉的蚊子数量是最少的
		{
			b[++cnt] = i;//记录下这只青蛙的编号
		}
	}
	printf("%d\n",cnt);//输出数量
	for(int i = 1;i<=cnt;i++)
	{
		printf("%d ",b[i]);//输出这些青蛙的编号
	}
	return 0;
}
```

---

## 作者：huangjunhan (赞：0)

# 题目分析
本题中的 $n$ 的范围较大，有 $10^9$，所以不能用桶记录的做法。不过我们可以记录下每个蚊子可能被吃的青蛙的编号，在求个最小值，就能得出正确答案。

# 正确代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,c[10010],l=INT_MAX,s,b[10010],a[10010],d[10010];
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++)cin>>d[i];
	for(int i=1;i<=k;i++){
		cin>>c[i];
		for(int j=1;j<=m;j++)if(c[i]%d[j]==0)a[j]++;
	}
	for(int i=1;i<=m;i++)l=min(l,a[i]);
	for(int i=1;i<=m;i++)if(a[i]==l)b[++s]=i;
	cout<<s<<endl;
	for(int i=1;i<=s;i++)cout<<b[i]<<' '; 
}
```

---

## 作者：Chillturtle (赞：0)

~~算是黄题中有点思路的~~

# 题意

有 $m$ 只青蛙与 $k$ 只蚊子，有一个美丽的拇指姑娘要选择这 $m$ 只青蛙中的一只，每次进行距离为 $d_i$ 的跳跃。但在距离为 $n$ 的路径上有 $k$ 只蚊子在睡觉。如果跳到这只蚊子睡觉的地方，则视为这只蚊子~~死掉了~~。

问，选择哪一只青蛙能使~~死掉~~的蚊子最少。

# 思路 

首先，我们看到 $1 \le n \le 10^9$ 那么就不可能用 $n$ 来遍历。这里我们可以尝试换一种思路。

我们试着直接从青蛙和蚊子的位置入手。想一想，青蛙要怎么样才能吃到蚊子？很容易就能想到，如果**青蛙每次跳的距离是蚊子原始距离的因数，那么这只青蛙就一定能吃到这只蚊子**。这里举一个例子，请看下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/2sowjk99.png)

从这张图中，我们能够很容易的得出上面提出的结论。所以我们只需要对于这 $m$ 只青蛙来枚举它们每一只所能吃到的蚊子数，找到最小值，输出即可。

时间复杂度 $O(m \times k)$。

# AC code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e2+10;
int n,m,k;
int frog[N],fly[N],ans[N];
signed main(){
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++){
		cin>>frog[i];
	}
	for(int i=1;i<=k;i++){
		cin>>fly[i];
	}
	int minn=INT_MAX;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=k;j++){
			if(fly[j]%frog[i]==0){
				ans[i]++;
			}
		}
		minn=min(minn,ans[i]);
	}
	int opt=0;
	for(int i=1;i<=m;i++){
		if(ans[i]==minn){
			opt++;
		}
	}
	cout<<opt<<endl;
	for(int i=1;i<=m;i++){
		if(ans[i]==minn){
			cout<<i<<" ";
		}
	}
	cout<<endl;
return 0;
}
```

---

## 作者：Alexxu2024 (赞：0)

# CF39F 题解

## [题目传送门](https://www.luogu.com.cn/problem/CF39F)

## 思考
可以从 $1$ 枚举到 $n$，看每只青蛙在哪个点停下，可以求出答案。

但观察发现 $n$ 过大，所以不能写一个 $n$ 次的循环。

## 正解
发现 $m$ 和 $k$ 都很小，只有 $100$，且你应该能发现判断蚊子会不会被某只青蛙踩只需判断它的位置是否会被青蛙跳跃长度整除，所以考虑写一个双层循环，外层枚举青蛙，内层枚举蚊子，把答案存储到数组 ```ans``` 中，再进行处理。

## 代码
```cpp
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
int a[110],b[110],ans[110];//a青蛙，b蚊子，ans每只青蛙踩到的蚊子数量
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n,m,k;
	cin >> n >> m >> k;
	for(int i=1;i<=m;i++){
		cin >> a[i];
	}
	for(int i=1;i<=k;i++){
		cin >> b[i];
	}
	int minn=99999999;//存最小踩死几只蚊子，其实初始值只要>100都行
	for(int i=1;i<=m;i++){
		for(int j=1;j<=k;j++){
			if(b[j]%a[i]==0){//能踩到
				ans[i]++;//增加数量
			}
		}
		minn=min(minn,ans[i]);//求最小值
	}
	int ans1=0;//第一行输出几只青蛙是最少踩死的
	for(int i=1;i<=m;i++){
		if(ans[i]==minn){//判断
			ans1++;
		}
	}
	cout << ans1 << endl;
	for(int i=1;i<=m;i++){
		if(ans[i]==minn){
			cout << i << " ";//第二行升序输出的每个青蛙的编号
		}
	}
    return 0;//结束
}
```

---

## 作者：weihaozhen2010 (赞：0)

# 题意：

[CF39F](https://www.luogu.com.cn/problem/CF39F)

注意：输出的第一行是击碎了最少蚊子的青蛙数量，并不是最少击碎的蚊子数量。

#  思路：

- 这道题一眼就是是模拟和暴力枚举的思路。

- 由于每只青蛙有自己的跳跃长度，并且都从第一个山丘上出发，所以对于跳跃长度为 $d_i$ 的青蛙，每次它到达的山丘肯定是 $d_i$ 的倍数。

- 基于上面的结论，我们可以枚举每个青蛙的跳跃长度，再枚举蚊子的位置，判断青蛙是否跳到了蚊子上。若跳到了蚊子上，对应青蛙的计数器加一。若没有跳到蚊子上，则继续枚举。

- 最后用打擂台求出击碎蚊子的最小值。接着遍历一边数组寻找击碎了最少蚊子的青蛙数量和各个青蛙的编号。

# 参考代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int a[105],b[105],c[105];
int ans=1e9+5,sum=0;
int main()
{
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=k;i++)
	{
		cin>>b[i];
	}
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=k;j++)
		{
			if(b[j]%a[i]==0)
			{
				c[i]++;
			}
		}
	}
	for(int i=1;i<=m;i++)
	{
		ans=min(ans,c[i]);
	}
	for(int i=1;i<=m;i++)
	{
		if(ans==c[i])
		{
			sum++;
		}
	}
	cout<<sum<<"\n";
	for(int i=1;i<=m;i++)
	{
		if(ans==c[i])
		{
			cout<<i<<" ";
		}
	}
	return 0;
}
```

---

## 作者：homo_snow (赞：0)

# 题目大意

现有二大小分别为 $m$, $k$ 集合 $D$ 与 $K$，现可选集合 $D$ 中任意一个数 $x$, 使得 $x$ 小于 $n$ 的倍数在集合 $K$ 中出现的次数最少。

# 思路
一眼桶，看到 $n \le 10^9$ 的数据量就想离散化，但是由于 $m$ 与 $k$ 较小的原因，离散化优化的效果并不好，考虑别的方式。

> 败与 $m,k$, 成与 $m,k$。

正因为 $m,k \le 100$ 这种极小的数据量，才能让我们畅爽淋漓地打暴力。

考虑以集合 $D$ 做桶 $ans$, $ans_i$ 为集合 $D$ 中第 $i$ 个元素小于 $n$ 的倍数出现在集合 $K$ 中的数量。

对于每一个集合 $K$ 的元素，采用暴力枚举的方法判断它是集合 $D$ 中哪些元素的倍数，存入 $ans$ 中。

最后，取出 $ans_i$ 中最小的元素，输出即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e5+10;
const int INF = 0x3f3f3f3f;

int n , m , k , a[N] , d[N] , ans[N] , minn, tot, b[N];

signed main(){
	scanf("%lld%lld%lld",&n,&m,&k);
	for(int i = 1; i <= m; i++)
		scanf("%lld",&d[i]);
	for(int i = 1; i <= k; i++){
		scanf("%lld",&a[i]);
		for(int j = 1; j <= m; j++)
			if(a[i] % d[j] == 0) ans[j]++;
	}
	minn = *min_element(ans+1,ans+m+1);
	for(int i = 1; i <= m; i++)
		if(ans[i] == minn)
			b[++tot] = i;
	printf("%lld\n",tot);
	for(int i = 1; i <= tot; i++)
		printf("%lld ",b[i]);
	return 0;
}
```


---

## 作者：_Wind_Leaves_ShaDow_ (赞：0)

### 首先这道题题目输出部分翻译有误，正确的输出要求如下：
- 第一行输出 **有多少只** 青蛙击碎的蚊子数 **最少**。
- 第二行按 **编号的从大到小** 排列这些青蛙的编号。

### 题意分析：
这道题乍一看可能很难，但稍微思考一下就会发现这是一道非常水的水题。

一只青蛙只能 **按固定的步数移动**，也就是说青蛙击碎蚊子的数量是 **不会改变的**，我们只需要判断在这个青蛙的路径上有几只蚊子就好了。

然后是输出部分：

- 先打擂台，求出最小值；
- 遍历一遍记录青蛙击碎数量的数组，找到有几个最小值；
- 输出最小值，然后再次遍历数组，如果是最小值就输出出来。

[AC](https://www.luogu.com.cn/record/102492806) 代码附上（含注释）：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,k,cnt,d[150],q[150],c[150];
int ans=0x7fffffff;//ans要设成很大的值因为要求最小值 
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++)cin>>d[i];
	for(int i=1;i<=k;i++)cin>>q[i];
	for(int i=1;i<=m;i++){//枚举每只青蛙
		for(int j=1;j<=k;j++){//对于每只青蛙，枚举每只蚊子
			if(q[j]%d[i]==0)c[i]++;//如果路径上有蚊子击碎的蚊子总数就加一 
		}
	}
	for(int i=1;i<=m;i++)ans=min(ans,c[i]);//求出最小值 
	for(int i=1;i<=m;i++){
		if(c[i]==ans)cnt++;//再次提醒这里是击碎最小值的青蛙数量和编号 
	} 
	cout<<cnt<<endl;
	for(int i=1;i<=m;i++)if(c[i]==ans)cout<<i<<" ";
	return 0;
}
```
这里枚举的是青蛙，当然枚举蚊子一样可过

---

## 作者：lihl (赞：0)

考虑处于 $kd_i$ 的蚊子一定会被踩死，不妨枚举 $m$ 只青蛙踩死蚊子的数量，并进行排序取最小值。

可以考虑桶记录数量，判断每只蚊子是否 $a_i \mid d_j$ 即可，其中 $a_i$ 表示每只蚊子所处位置，$d_j$ 表示每只青蛙的跳跃长度。

---

