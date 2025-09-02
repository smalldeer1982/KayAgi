# Packmen

## 题目描述

A game field is a strip of $ 1×n $ square cells. In some cells there are Packmen, in some cells — asterisks, other cells are empty.

Packman can move to neighboring cell in $ 1 $ time unit. If there is an asterisk in the target cell then Packman eats it. Packman doesn't spend any time to eat an asterisk.

In the initial moment of time all Packmen begin to move. Each Packman can change direction of its move unlimited number of times, but it is not allowed to go beyond the boundaries of the game field. Packmen do not interfere with the movement of other packmen; in one cell there can be any number of packmen moving in any directions.

Your task is to determine minimum possible time after which Packmen can eat all the asterisks.

## 说明/提示

In the first example Packman in position $ 4 $ will move to the left and will eat asterisk in position $ 1 $ . He will spend $ 3 $ time units on it. During the same $ 3 $ time units Packman in position $ 6 $ will eat both of neighboring with it asterisks. For example, it can move to the left and eat asterisk in position $ 5 $ (in $ 1 $ time unit) and then move from the position $ 5 $ to the right and eat asterisk in the position $ 7 $ (in $ 2 $ time units). So in $ 3 $ time units Packmen will eat all asterisks on the game field.

In the second example Packman in the position $ 4 $ will move to the left and after $ 2 $ time units will eat asterisks in positions $ 3 $ and $ 2 $ . Packmen in positions $ 5 $ and $ 8 $ will move to the right and in $ 2 $ time units will eat asterisks in positions $ 7 $ and $ 10 $ , respectively. So $ 2 $ time units is enough for Packmen to eat all asterisks on the game field.

## 样例 #1

### 输入

```
7
*..P*P*
```

### 输出

```
3
```

## 样例 #2

### 输入

```
10
.**PP.*P.*
```

### 输出

```
2
```

# 题解

## 作者：LlLlCc (赞：9)

### 二分+贪心
虽然放在CF DP集里面，但wtcl，只会贪心

------------
首先，很容易想到，每一个包装，只会被它左边离他最近的人或者右边离他最近的人吃掉。且每个人最多只会转一次方向

![](https://cdn.luogu.com.cn/upload/image_hosting/hav3gn3f.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

即不可能出现上面这种多次转弯的人，因为他有更优的解，如下图

![](https://cdn.luogu.com.cn/upload/image_hosting/p78mgvw0.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

显然下面这种耗时更少

因为如果第$x$时刻能吃完，那么第$x+1$时刻肯定也能吃完，也就是说满足单调性，我们可以二分枚举这个答案

接下来我们考虑如何$check$

对于每个包装，提前预处理，记录一下左边离他最近的人和右边离他最近的人（因为它只会被这两个人吃）

从前到后枚举每个包装，如果他能被左边的吃，那就被左边的吃，否则看看与右边的距离是否大于我们枚举的答案即可

## code
```
#include<bits/stdc++.h>
#define maxn 200005
using namespace std;
int n,Nxt[maxn],Ans,L[maxn],R[maxn],Lst[maxn],Now;
char s[maxn];
inline int read(){
	int ret=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
	return ret;
}
inline bool check(int x){
	for (int i=1;i<=n;i++) if (s[i]=='P') L[i]=R[i]=i;
	for (int i=1;i<=n;i++)
	  if (s[i]=='*'){
	  	if (Lst[i]&&min(2*(Lst[i]-L[Lst[i]])+i-Lst[i],2*(i-Lst[i])+Lst[i]-L[Lst[i]])<=x){R[Lst[i]]=i;continue;}
	  	if (Nxt[i]&&L[Nxt[i]]<i) continue;
	  	if (!Nxt[i]||Nxt[i]-i>x) return 0;
		L[Nxt[i]]=i;
	  }
	return 1;
}
int main(){
	n=read();scanf("%s",s+1);
	int l=0,r=1e7;
	for (int i=1;i<=n;i++)
	  if (s[i]=='P') Now=i;
	  else if (s[i]=='*')  Lst[i]=Now;
	Now=0;
	for (int i=n;i;i--)
	  if (s[i]=='P') Now=i;
	  else if (s[i]=='*')  Nxt[i]=Now;
	while (l<=r){
		int mid=l+r>>1;
		if (check(mid)) Ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%d",Ans);
	return 0;
}
```


---

## 作者：Divinitist (赞：5)

二分答案 + 贪心
二分最小时间（即步数）$x$。设人与目标距离为$dis$，则对于每一个人有3种策略：
1. 在遇到这个人之前没有遇到未被遍历的目标（即$package$），则这个人不需要往回走，贪心往前遍历$x$格
2. 之前有未被遍历的目标，且$x > dis \times 3$， 则先往左到达该目标，再向右遍历至$i + x - dis \times 2$格
3. 之前有未被遍历的目标，且$x <= dis \times 3$， 则先往左尽量遍历至$i + \frac{x - dis}{2}$，再向左到达该目标

后2种应该画图可以理解。
注：此处需要维护一个指针来标记已被遍历的区间的右端点，而不能直接用遍历序列的i指针跳跃，因为有可能在跳跃过的距离之间，有能够走得比当前人更远的人
```
// Divinity
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
const int N = 1e5 + 5;
char s[N];
int n;
bool ctrl(int x){
	int pk = 0, exp = 0;
   //pk:package，目前未被遍历的第一个目标的坐标
   //exp:expand，已遍历区间的右端点（闭）
	for(int i = 1; i <= n; i++){
		if(s[i] == '*' && i > exp && !pk) pk = i;//找到目前未被遍历的第一个目标
		if(s[i] == 'P'){
			if(pk == 0) exp = i + x;//如果在这个人的位置之前没有未遍历的目标，那么区间直接向前覆盖x，即这个人直接往前走x格
			else{
				int dis = i - pk;
				if(dis > x) return 0;//如果这个人与未被标记的第一个目标的距离大于x，则必定不可到达，说明x小了
				else{
					if(x > dis * 3) exp = i + x - dis * 2;
					else exp = i + (x - dis) / 2;
					pk = 0;
					//有2种选择：先向左再向右，或是先向右再向左。由于折返时有一段路必定需要经过2次，所以贪心选择短的那一段经过2次，于是比较两种方案的大小。由于两种方案在x == dis * 3时效果相同，所以以之作为判断值
				}
				if(exp >= n) return 1;//如果可覆盖范围超出了n，则说明所有目标都可以遍历到
			}
		}
	}
	if(pk) return 0;//由于每次覆盖后pk都会清零，所以如果遍历完毕后，pk不为0，则说明至少有一个目标无法到达，说明方案非法
	return 1;
}
int main(){
	scanf("%d\n%s", &n, s + 1);
	int l = 0, r = n << 1/*极端情况是只有一个人在序列正中间，则需要走2 * ( n / 2 ) + ( n / 2 ) = 3 * n /2 */, ans = 0;
	while(l <= r){
		int mid = l + r >> 1;
		if(ctrl(mid)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	printf("%d", ans);
	return 0;
}
```

---

## 作者：觞羰涙 (赞：5)

题意：
数轴上P代表人，*代表物品，每个人可以向左右走，时间花费为距离差的绝对值，问取完所有物品的最小结束时间
考虑二分，主要看check怎么写，见代码注释
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<iomanip>
#define maxn 200005
typedef long long ll;
int n;
int cnt_peo,cnt_sta;//人数 物品数 
int peo[maxn],sta[maxn];//记录各自位置 
using namespace std;
template <class T> void read(T &x)
{
	x=0;int f=1;char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	x*=f;
}
int cal(int l,int r,int pos)
{
	return min(abs(pos-l),abs(pos-r))+abs(r-l);
	//可以取了左端再取右端的 
	//也可以先取右边的 
	//总时间就是左右端点距离差加重复走的
	//即先左或先右返回的花费
	//区间内的物品显然已经取走了 
}
bool fuck(int x)
{
	int pre=0,pos=0;
	for(int i=1;i<=cnt_peo;i++)
	{
		while(pos<=cnt_sta&&cal(sta[pre],sta[pos],peo[i])<=x)++pos;
		//pre是当前这个人取的最左端的物品位置，pos是现在的
		//如果左右都取了时间小于mid，则还可以往后取，pos++ 
		pre=pos;
	}
	return pos==cnt_sta+1;
}
char s[maxn];
int main()
{
	//%%%zzy
	read(n);
	scanf("%s",s+1);
	for(int i=1;i<=n;i++)
	{
		if(s[i]=='P')peo[++cnt_peo]=i;
		if(s[i]=='*')sta[++cnt_sta]=i;
	}
	int l=0,r=2*n,ans;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(fuck(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%d",ans);
	return 0;
} 
```
就是不知道为什么check里必须判断后一个pos
不然爆WA
![？？？](https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1543033155988&di=f6d02e655d41ea03bbabfcf13cc3381a&imgtype=0&src=http%3A%2F%2Fimg.bqatj.com%2Fimg%2Ff4e0221e66d3005a.jpg)

---

## 作者：Lotus_Land (赞：3)

考虑二分答案。

如何 check？从左往右贪心。

设 $dis$ 为人与目标包装的距离，$pos$ 为还没有被吃掉的第一个包装的坐标，$lst$ 为已遍历区间的右端点。并设 $pos$ 和 $lst$ 的初始值都为 -1。

如果扫到的是包装，如果同时这个包装未被吃掉，则更新 $pos$ 的值即可。

如果扫到的是人，那么分以下几种情况：

- 如果在这个人之前没有未吃掉的包装，则直接向右遍历 $x$ 格。

- 之前有未吃掉的包装，且 $x<dis$，说明这个包装肯定吃不掉了，直接 `return 0;`。

- 之前有未吃掉的包装，且 $dis\times 3<x$，则先往左走 $dis$ 格把包装吃了，再往右遍历 $x-dis$ 格。

- 之前有未吃掉的包装，且 $dis\times 3\geq x$，则先往右走到 $i+\dfrac{x-dis}{2}$ 的位置，再往左走把包装吃了。 

吃掉包装后，$pos=-1$。

```
#include<bits/stdc++.h>
using namespace std;
int n,l,r,mid,ans,now;
string s;
bool check(int x) {
	int pos=-1,lst=-1;
	for(int i=1; i<=n; i++) {
		if(i>lst)if(s[i]=='*'&&pos==-1)pos=i;
		if(s[i]=='P') {
			if(pos==-1)lst=i+x;
			else {
				int dis=i-pos;
				if(dis>x)return 0;
				if(dis*3<x) {
					lst=i+x-2*dis;
				} else {
					lst=(x-dis)/2+i; 
				}
			}
			pos=-1;
		}
	}
	if(pos==-1)return 1;
	else return 0;
}
int main() {
	cin>>n>>s;
	s=' '+s;
	r=n*2;
	while(l<=r) {
		mid=(l+r)/2;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Minuit (赞：1)

update:为了防止在公式前后不加空格,去掉了所有公式,改用文字描述,在所有中文句子后面加了中文句号。

目前是最优解rk1。

---
## 奇怪的东西

- [WA了两小时。](https://www.luogu.com.cn/record/list?user=34940&pid=CF847E&page=1)

- [比rk2快一倍,但代码长4倍。](https://www.luogu.com.cn/record/list?user=&pid=CF847E&page=1&orderBy=1&status=)

## 题意

  区间上有人,物品,空地,人可以左右移动,求让人的移动轨迹覆盖所有物品的轨迹**最大值的最小值**。
  
## 题解

根据题意,显然看出是二分.再考虑一个人的走法:

- 向左走,不回头。

- 向右走,不回头。

- 向左再向右,左边重复走。

- 向右再向左,右边重复走。

若我们**从左到右**把人扫一遍,必然要保证先把左边的没走到的物品走到,同时在还有步数的情况下向右走。

这样会挂 ,原因在于先向右走再向左走到第一个没走到的物品可能更优,因为重复的部分可能更少。

考虑分类讨论:用一个物品指针指向还没走到的最靠左的物品。

1. 步数不够到达最左边的没走到的物品: 直接返回失败。

2. 步数只能到最左边的物品,无法向右走: 把物品指针向右更新到人右边。

3. 步数很充足: 在先向左和先向右两种走法中取最优解。

4. 指针在人右边: 把物品指针尽可能向右更新。

结束后判断指针是否大于物品总数即可。

这样就又挂了,原因在于二分的右边界应当是只有一个人在正中间,先向某方向然后再折返的答案。

最终复杂度明显快于大部分题解。

## 代码


```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int N = 100005;
int n, L, R, cnt1, cnt2;
int peo[N], pack[N];
string s;
bool check(int k)
{
    int await_pick = 1;
    for (int i = 1; i <= cnt1; i++)
    {
        int start_pos = await_pick;
        if (await_pick > cnt2)
            return true;
        if (pack[start_pos] < peo[i])
        {
            if (pack[start_pos] < peo[i] - k)//第一种情况
                return false;
            if (k <= peo[i] - pack[start_pos] + 1)//第二种情况
            {
                while (pack[await_pick + 1] <= peo[i] && await_pick <= cnt2 && pack[await_pick + 1] <= peo[i + 1])
                    await_pick++;
                if (pack[await_pick] <= peo[i] && pack[await_pick] <= peo[i + 1])
                    await_pick++;
            }
            else
            {
                if (k > (2 * (peo[i] - pack[start_pos])))
                {//第三种情况,先向左走
                    int temp = k - (2 * (peo[i] - pack[start_pos]));
                    while (pack[await_pick + 1] <= peo[i] + temp && await_pick <= cnt2 && pack[await_pick + 1] <= peo[i + 1])
                        await_pick++;
                    if (pack[await_pick] <= peo[i] + temp && pack[await_pick] <= peo[i + 1])
                        await_pick++;
                }
                if (peo[i] + (k + pack[start_pos] - peo[i]) / 2 >= pack[await_pick])
                {//第三种情况,先向右走
                    int temp = (k + pack[start_pos] - peo[i]) / 2;
                    while (pack[await_pick + 1] <= peo[i] + temp && await_pick <= cnt2 && pack[await_pick + 1] <= peo[i + 1])
                        await_pick++;
                    if (pack[await_pick] <= peo[i] + temp && pack[await_pick] <= peo[i + 1])
                        await_pick++;
                }
            }
        }
        else
        {//第四种情况
            while (pack[await_pick + 1] <= peo[i] + k && await_pick <= cnt2 && pack[await_pick + 1] <= peo[i + 1])
                await_pick++;
            if (pack[await_pick] <= peo[i] + k && await_pick <= cnt2 && pack[await_pick] <= peo[i + 1])
                await_pick++;
        }
    }
    if (await_pick > cnt2)
        return true;
    else
        return false;
}
int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> s;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == 'P')
            peo[++cnt1] = i + 1;
        if (s[i] == '*')
            pack[++cnt2] = i + 1;
    }
    peo[cnt1 + 1] = 0x7fffffff;
    pack[cnt2 + 1] = 0x7fffffff;
    L = 1, R = 2 * n;//注意二分边界
    while (L <= R)
    {
        int mid = (L + R) / 2;
        if (check(mid))
            R = mid - 1;
        else
            L = mid + 1;
    }
    cout << L;
}
```

---

## 作者：Ganshuaige (赞：1)

# CF 847E Ppackmen
## 二分

#### 题意：
给出一个字符串。"."表示空，"*"表示食物，"P"表示人

求出一个每个人可以移动K，把"*"全部吃完，求K的最小值

可以想到是2分答案


重点是如何check

可以分为2种情况

便于方便我们把"*"写为1，把"P"写为0

* 1

011（前面已经没有没被标记的1）

根据贪心可以发现，人直接往右走就可以了

* 2

101（前面还有没被标记的1）

这种情况可以先往左走再往右走

或者往右走再往左走


```
#include<cstdio>
#include<cstring>
#include<iostream>

typedef long long ll;
const int Maxn = 2e5+7;
using namespace std;

int n;
char c[Maxn];

int cnt_p,cnt_s;
int p[Maxn],s[Maxn];

bool check(int x){
	int cnt1=1,cnt2=1;
	for(int i=1;i<=n;i++){
		if(c[i]=='.')
			continue;
		if(i==p[cnt1]){
			if(p[cnt1]>s[cnt2]){
				int zz=p[cnt1]-s[cnt2];
				if(zz>x)
					return false;
				int k=x-2*zz;
				while(s[cnt2]<=max(0,k)+p[cnt1])//这个首先要满足左边
					cnt2++;
				while(2*(s[cnt2]-p[cnt1])+zz<=x)//如果说先往右要优秀一点
					cnt2++;
			}
			else if(p[cnt1]<s[cnt2])
				while(s[cnt2]<=x+p[cnt1])
					cnt2++;
			cnt1++;
		}
		if(cnt1==cnt_p+1)
			break;
		if(cnt2==cnt_s+1)
			break;
	}
	return cnt2==cnt_s+1;
}

int main(){
	scanf("%d",&n);
	scanf("%s",c+1);
	for(int i=1;i<=n;i++){
		if(c[i]=='P')
			p[++cnt_p]=i;
		if(c[i]=='*')
			s[++cnt_s]=i;
	}
	s[cnt_s+1]=99999999;
	int l=1,r=n*2,ans;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)){
			r=mid-1;
			ans=mid;
		}
		else
			l=mid+1;
	}
	printf("%d",ans);
}
```


---

## 作者：_edge_ (赞：0)

提供一种实现和思路都比较简洁的想法。

考虑对于答案，思考是否具有单调性，如果有单调性可以考虑进行二分答案。

~~我是从 dp 专题那里骗来的，如果有神仙有 nb dp 做法还请告诉我一声。~~

试想一下，如果我们确定了这个答案，我们是不是已经把一个人给限制住了。

可以比较贪心的去思考，对于每一个人，他肯定是先把左边的吃掉，然后再去吃右边的。

这个想法挺显然吧，因为考虑后面一个人，它吃右边的肯定会更优秀一些，吃左边则会多出一些不必要的贡献。

那我们贪心策略就非常明显了，就是一个人左边如果有东西就去吃左边的，然后再折回来吃右边的。

可是，现实真的是这样最优么？

然而并不全是，试想一下，如果一个包装在左边，离这个人非常非常非常远，而右边的则非常近，那我们还是先吃左边的么？

答案是否定的，我们肯定先把右边的给吃掉。

所以得出一种结论，虽然他一定要把左边的给吃掉，但是**他并不一定要先吃左边的**。

严格证明我还是不太明白，所以大致给各位简单的不严格证明一下。

这部分吃右边可以吃到哪里用二分来维护是两只 $\log$，用双指针来维护是一只 $\log$。

哦对，开头和各位说代码是非常简洁明了的。

放代码：

```cpp
int solve(int x,int y,int z) {
	return min(y-x+z-x,z-y+z-x);
}
// x<y<z 并且 y 是人的情况，分类取最小。
// 即先走到 x 和先走到 z 的区别。
bool check(int xx) {
	L=1;
	for (int i=1;i<=n;i++) {
		if (s1[i]!='P') continue;
		if (L>a[0]) return true;// 当前已经吃完了。
		if (i-a[L]>xx) return false;// 当前吃不到左边的，那右边的也吃不到。
		int la=a[L];
		if (i<la) {// 如果左边的没有东西可以吃。
			while (L<=a[0] && a[L]-i<=xx) L++;
			continue;
		}
		while (L<=a[0] && a[L]<=i) L++;// 把到的了的左边全都算进贡献里面。
		while (L<=a[0] && solve(la,i,a[L])<=xx) L++;
		
    }
	return L>a[0];
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>s1;s1=" "+s1;
	for (int i=1;i<=n;i++) 
		if (s1[i]=='*') a[++a[0]]=i;
	int l=0,r=1e9,ans=-1;// 答案的上界是 2*n，可能不到，开 1e9 保险。
	while (l<=r) {
		int Mid=(l+r)>>1;
		if (check(Mid)) r=(ans=Mid)-1;
		else l=Mid+1;
	}
	cout<<ans<<"\n";
	return 0;
}
```

感谢阅读。

---

## 作者：翰空之眼 (赞：0)

### 题意
有一个长度为$n$的纸带，每一格有3种可能：人、食物、空格

每个人可以同时动，而且互相不受影响，人经过有食物的格子的时候会不花费时间把食物吃掉

求吃完所有食物的最小时间

### 题解

~~老师说这是一道很没排场的E题。。。~~

其实想到二分就很好做了，先说说怎么想到的二分

这种题无非3种解法：贪心（二分）、$dp$、（最短路？）

这么多人，这么大范围dp没什么可能了，贪心想了好多种都不太对。。。至于最短路，大概也知道没什么希望了。。。

所以就是二分

想到是二分以后，就是比较好想的贪心了

首先，肯定是行走路线两两不相交最优。

我们考虑最左边的食物，如果最左边的人吃不到他的话，那么别人一定也吃不到他，就结束了

最后我们的算法是：从左到右扫每个人，如果他左边还有食物没被吃，他就去吃，否则往右边走，吃尽量多的食物。

***有一个细节：还能往右走的时候要判一下先往左走快还是先往右走快。***

### 代码

这题真是细节超多。。。

```cpp
#include <iostream>
#include <stdio.h>
#include <cstring>
#define rep(i, a, b) for(int i = (a); i <= (b); i++)
using namespace std;
const int N = 1e5 + 9, inf = 0x3f3f3f3f;
int n, m, lst;
char s[N];
struct node{
    int lf, pl, lr;
}a[N], f[N];
bool check(int x){
    rep(i, 1, m) a[i] = f[i];
    a[m+1].lf = a[m+1].lr = -1;
    rep(i, 1, m) {
        if(a[i].lr){
            rep(j, a[i].lr, a[i].pl) {
                if(s[j-1] != '*') a[i].lr++;
                else break;
            }
            if(a[i].lr == a[i].pl) {
                a[i].lr = 0, a[i+1].lr = a[i+1].lf <= a[i].pl + x ? 0 : max(a[i+1].lr, a[i].pl + x + 1);
                continue;
            }
            if(x < a[i].pl - a[i].lr) return false;
            int num = max(x - 2 * (a[i].pl - a[i].lr), (x - a[i].pl + a[i].lr) / 2);
            if(num > 0){
                if(i == m) a[i+1].lr = a[i].pl + num;
                else a[i+1].lr = a[i+1].lf <= a[i].pl + num ? 0 : max(a[i+1].lr, a[i].pl + num + 1);
            }
        }
        else {
            if(i == m) a[i+1].lr = a[i].pl + x;
            else a[i+1].lr = a[i+1].lf <= a[i].pl + x ? 0 : max(a[i+1].lr, a[i].pl + x + 1);
        }
    }
    if(max(a[m+1].lr, a[m].pl) >= lst + 1) return true;
    return false;
}
int erfen(int l, int r){
    int res = -1;
    while(l <= r){
        int mid = (l + r) / 2;
        if(check(mid)) res = mid, r = mid-1;
        else l = mid + 1;
    }
    return res;
}
int main(){
    scanf("%d%s", &n, s);
    int now1 = 0, now2 = 0;
    rep(i, 0, n-1) {
        if(s[i] == 'P') a[++m].lf = now2 ? now1 : 0, a[m].pl = i+1, a[m].lr = now2, now2 = 0;
        else if(s[i] == '*') now1 = i+1, now2 = now2 ? now2 : i+1, lst = i;
    }
    rep(i, 1, m) f[i] = a[i];
    printf("%d", erfen(0, 2*n));
    return 0;
}
```

---

