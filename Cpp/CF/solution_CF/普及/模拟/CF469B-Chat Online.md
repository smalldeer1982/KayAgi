# Chat Online

## 题目描述

Little X and Little Z are good friends. They always chat online. But both of them have schedules.

Little Z has fixed schedule. He always online at any moment of time between $ a_{1} $ and $ b_{1} $ , between $ a_{2} $ and $ b_{2} $ , ..., between $ a_{p} $ and $ b_{p} $ (all borders inclusive). But the schedule of Little X is quite strange, it depends on the time when he gets up. If he gets up at time $ 0 $ , he will be online at any moment of time between $ c_{1} $ and $ d_{1} $ , between $ c_{2} $ and $ d_{2} $ , ..., between $ c_{q} $ and $ d_{q} $ (all borders inclusive). But if he gets up at time $ t $ , these segments will be shifted by $ t $ . They become $ [c_{i}+t,d_{i}+t] $ (for all $ i $ ).

If at a moment of time, both Little X and Little Z are online simultaneosly, they can chat online happily. You know that Little X can get up at an integer moment of time between $ l $ and $ r $ (both borders inclusive). Also you know that Little X wants to get up at the moment of time, that is suitable for chatting with Little Z (they must have at least one common moment of time in schedules). How many integer moments of time from the segment $ [l,r] $ suit for that?

## 样例 #1

### 输入

```
1 1 0 4
2 3
0 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2 3 0 20
15 17
23 26
1 4
7 11
15 17
```

### 输出

```
20
```

# 题解

## 作者：shenbairui (赞：1)

### 题目大意
小 Z 和小 X 是好朋友。他们经常在线聊天。但是他们都有固定的时间安排。

小 Z 有固定的时间安排。他随时在线，时间段在 $a_1$ 和 $b_1$，$a_2$ 和 $b_2$，...，$a_p$ 和 $b_p$（包含边界）。

但是小 X 的时间安排有点奇怪，它依赖于他的起床时间。如果他在时间 $0$ 起床，他会在线上，时间段在 $c_1$ 和 $d_1$，$c_2$ 和 $d_2$，...，$c_q$ 和 $d_q$ （包含边界）。但是如果他在时间 $t$ 起床，这些时间段会向后偏移 $t$。即变成 $[c_i+t, d_i+t]$ (对于所有的 $i$)。

如果在某个时间点，小 X 和小 Z 同时在线上，他们可以愉快地聊天。你知道小 X 可以在区间 $[l, r]$ 中的整数时间起床。还知道小 X 想要在适合和小 Z 聊天的时间起床 (他们必须在时间安排中至少有一个共同的时间段)。有多少个起床时间适合这个条件，在区间 $[l, r]$ 中?
### 题目分析
在一个区间 $ [l,r] $ 中，有多少个整数 $ t $ 在 $ [c+t,d+t] $ 与区间 $ [a,b] $ 有交集。

可以考虑用模拟的算法，时间复杂度 $O(r^2q)$ 可以通过本题。

但是注意，找到有交集就要回第一层循环了，因为这个时间已经好了，不要需要重复算。

每判断到一个数字，用于计数的数组加一，最后计算总个数。
### 代码如下

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int p, q, l, r, x, y, ans;
int lefts[10005], rights[10005];
bool flag[10005], pd = false;
signed main() {
	cin >> p >> q >> l >> r;
	for (int i = 1; i <= p; i++) {//输入
		cin >> x >> y;
		for (int j = x; j <= y; j++) flag[j] = true;
	}
	for (int i = 1; i <= q; i++) cin >> lefts[i] >> rights[i];
	for (int i = l; i <= r; i++) {
		pd = false;
		for (int j = 1; j <= q; j++) {
			for (int k = lefts[j] + i; k <= rights[j] + i; k++) {//暴力循环
				if (flag[k]) {
					ans++;//计数
					pd = true;//标记
					break;
				}
			}
			if (pd) break;
		}
	}
	cout << ans << endl;
	return 0;
}
```
### [通过记录](https://codeforces.com/contest/469/submission/287080055)
下次见！拜拜！

---

## 作者：N_z_ (赞：1)

## 题意
给你 $p$ 个 $[a,b]$ 的区间和 $q$ 个 $[c,d]$ 的区间，现给出区间 $[l,r]$ ，问你区间 $[l,r]$ 内有多少个整数 $t$ 满足区间 $[c+t,d+t]$ 与区间 $[a,b]$ 有交集。
## 思路
数据较小，暴力枚举即可。

在输入时处理区间 $[a,b]$ 的所有位置，然后枚举 $[l,r]$ 的所有可能值，判断即可。

注意如果用 bool 数组储存整个 $[a,b]$ 的话，数组要开到 $\max(b_ {\max},d_ {\max}+r)$ 。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[51][2];
bool b[10001];
int main()
{
    int p,q,l,r;
    cin>>p>>q>>l>>r;
    for(int x=1;x<=p;x++)
    {
        int y,z;
        cin>>y>>z;
        for(int o=y;o<=z;o++)
        b[o]=true;
    }
    for(int x=1;x<=q;x++)
    cin>>a[x][0]>>a[x][1];
    int ans=0;
    for(int x=l;x<=r;x++)
    {
        for(int y=1;y<=q;y++)
        for(int z=a[y][0]+x;z<=a[y][1]+x;z++)
        if(b[z]==true){ans++;goto nxt;}
        nxt:;
    }
    cout<<ans<<endl;
}
```

---

## 作者：xujingyu (赞：0)

## 题意

故事开场：有俩大闲人，一个叫小 X，一个叫小 Z。

因为小 X 比较懒，没上闹钟，所以起床时间不固定，在 $l$ 和 $r$ 间，上网时间相应延后，设起床时间为 $t$，上网时间就是 $c_j+t$ 至 $d_j+t$。

而小 Z 上网时间在 $a_i$ 和 $b_i$ 间。

求小 X 在几个时间点起床能在上网时间遇上网上冲浪的小 Z。

## 解法

想了挺久怎么优化时间复杂度，但是没想到，我还是太菜了，怒打最最暴力做法……

先来看看怎么判断俩区间有无交集，有可能有仨情况：

1. ```
     __________
         __________
    ```
   即尾与首相交；
2. ```
   _______________
      _______
   ```
   即包含；
3. 首与尾相交，和情况一类似。

判断就行。

做法就是暴力枚举 $t$（反正 $l$ 和 $r$ 都那么小……），再暴力枚举 $p$ 个区间，再暴力枚举 $q$ 个区间，判断小 X 赖床后时间和小 Z 时间段有无交集。

这里注意，找到有交集就要 `break` 回第一层循环了，因为这个时间起床已经可以了，不要重复算。

```cpp
#include <bits/stdc++.h>
using namespace std;

int p,q,l,r,a[51],b[51],c[51],d[51],cnt;

bool jiao(int x1,int y1,int x2,int y2)//判断有无交集
{
	if(y1 >= x2 && y1 <= y2) return true;
	else if(x1 <= x2 && y1 >= y2) return true;
	else if(x1 >= x2 && x1 <= y2) return true;
	return false;
}

signed main()
{
	scanf("%d%d%d%d",&p,&q,&l,&r);
	for(int i = 1;i <= p;i++) scanf("%d%d",&a[i],&b[i]);
	for(int i = 1;i <= q;i++) scanf("%d%d",&c[i],&d[i]);
	for(int t = l;t <= r;t++)//枚举t
	{
		for(int i = 1;i <= p;i++)
		{
			bool flag = true;
			for(int j = 1;j <= q;j++)//枚举两个区间的所有数
			if(jiao(a[i],b[i],c[j] + t,d[j] + t))
			{cnt++;flag = false;break;}//有交集,加一,break
			if(!flag) break;
		}
	}
	printf("%d",cnt);
	return 0;
}
```

留坑，以后有实力了再回来想快一点的做法。

~~会回来吗？~~

---

## 作者：_Starlit__Sky_ (赞：0)

# 洛谷 CF469B Chat Online 题解

[题目传送门](https://www.luogu.com.cn/problem/CF469B)

## 题目算法

使用了 模拟 算法。

## 题目思路

将所有属于 $[a,b]$ 区间的数在布尔列表 $ls$ 中标记为 `true`。

枚举每一个 $t$，对于每一个 $t$，遍历 $[c,d]$ 区间，将每一段区间的收尾加上 $t$，判断在 $ls$ 列表中这个值的位置是否为 `true`，如果是的话就将答案增加，否则不变。

## 代码

```cpp
#include <bits/stdc++.h>
// 懒人砖用 
#define input(a,b) scanf("%d%d",&a,&b)
#define f(a,b,var) for(int var = a ; var <= b ; var++)
using namespace std;

// 定义变量 
bool ls[114514];
int cd[114514][2];
int p,q,l,r;
int m,n;
int answeeer = 0; // 十年 OI 一场空，没有初始值见祖宗（警钟长长长长长长长长长长鸣） 

int main()
{
	// 输入亿下 
	input(p,q);
	input(l,r);
	while (p--){
		input(m,n);
		f(m,n,i)
			ls[i] = true;
	}
	f(1,q,i)
		input(cd[i][0],cd[i][1]);
	f(l,r,i){ // 枚举 t 
		f(1,q,j) // 遍历 [c,d] 
			f(cd[j][0]+i,cd[j][1]+i,k) // 查找是否有交集 
				if (ls[k]){ // 有就退出 
					answeeer++;
					goto next_loop; // 溜了 ~ 
				}
		next_loop:;
	}
	cout << answeeer << endl; // 简简单单の输出 
	return 0; // 完结！！！！撒花 ヽ(°▽°)ノ?
}

```

~~点个赞再走吧！~~

---

## 作者：liuzhongrui (赞：0)

这个问题实际上~~不难~~，只是翻译实在难懂，因此鄙人利用某些工具全文翻译了一下，[戳这里](https://www.luogu.com.cn/paste/kru4juqv)，最终意思也就一句话的事。

我们只需在所有可能的 $t$ 上迭代，并检查小 X 和小 Z 的时间表是否会重叠。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FOR(i,a,n) for (int i=a;i<n;i++)
const int N=110;
int p,q,l,r,ans,tl,tr;
int pool[10000],pa[10000],pb[10000],*vis=pool+5000,*a=pa+5000,*b=pb+5000;
int main() {
	scanf("%d%d%d%d",&p,&q,&l,&r);
	FOR(i,0,p) {
		scanf("%d%d",&tl,&tr);
		FOR(j,tl,tr) a[j]=1;
	}
	FOR(i,0,q) {
		scanf("%d%d",&tl,&tr);
		FOR(j,tl,tr) b[j]=1;
	}
	FOR(i,0,1001) FOR(j,0,1001) if (a[i]&&b[j]) vis[i-j]=vis[i-j-1]=1;
	FOR(k,l,r+1) ans+=vis[k]|vis[k-1];
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：xudiyao (赞：0)

# 洛谷CF469B题解

## 题意简述
在一个区间 $[l,r]$ 中，有多少个整数 $t$ 在 $[c+t,d+t]$ 与区间 $[a,b]$ 有交集。

## 思路引导

这个数据范围……

 有点过水了。
 
那么直接暴力枚举即可，将 $q$ 个区间里的数用数组存起 $(bool,int)$ ，再判断交集部分有几个数字，每判断到一个数字，用于计数的数组加一，最后计算总个数。

## AC代码

```cpp
#include<bits/stdc++.h>//万能头文件yyds。 
using namespace std;
int a[1010],b[1010],x[1010],y[1010],f[10100],p[10100];//疯狂定义。 
int main()
{
    int n,m,l,r,t,s=0;
    cin>>n>>m>>l>>r;
    for(int i=1;i<=n;i++)
    {
        cin>>x[i]>>y[i];
        for(int j=x[i];j<=y[i];j++) f[j]=1;//所有去见你的数记上1。 
    }
    for(int i=1;i<=m;i++) cin>>a[i]>>b[i];
    for(int i=l;i<=r;i++)
    {
      t=0;
      for(int j=1;j<=m;j++)
      {
        for(int h=a[j]+i;h<=b[j]+i;h++)//区间[c+t,d+t]。 
        {
          if(f[h]==1)//如果有交集。 
          {
            p[h]++;//交集次数+1。 
            t=1;
            break;//找到了立马退出。 
           } 
        }
        if(t==1) break;
      }  
    }
    for(int i=1;i<=n;i++)
    {
      for(int j=x[i];j<=y[i];j++)
      {
        if(p[j]>=1)//如果对应数字有交集 。 
        {
          s=s+p[j];//总个数加上。 
          p[j]=0;//归零，避免重复计算。 
        }
      } 
    }
    cout<<s;
}//AC撒花！
```//禁止抄题解！！！

---

## 作者：forever516 (赞：0)

## 题意
给定两个的区间，现给出一个区间，问这个区间内有多少个整数
$t$
满足两个区间有交集。

## 解法
按题意模拟（暴力枚举）即可。

这题可能有比我更优的做法，但看数据可知，能暴力过。

这里提供暴力代码。



```cpp
#include<iostream>
#define N 100010
using namespace std;
int a[N][2],b[N],y,z,p,q,l,r,ans=0,x;
int main() {
	cin>>p>>q>>l>>r;
	for(x=1; x<=p; x++) {
		cin>>y>>z;
		for(int o=y; o<=z; o++)b[o]=true;
	}
	for(x=1; x<=q; x++)cin>>a[x][0]>>a[x][1];
	for(x=l; x<=r; x++) {
		for(y=1; y<=q; y++)
			for(z=a[y][0]+x; z<=a[y][1]+x; z++)
				if(b[z]==1) {
					ans++;
					goto nxt;
				}
			nxt:;
	}
	cout<<ans<<"\n";
}
```

---

