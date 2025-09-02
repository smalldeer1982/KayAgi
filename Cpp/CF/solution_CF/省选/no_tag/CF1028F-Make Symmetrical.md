# Make Symmetrical

## 题目描述

给定一个点集 $A$，初始时为空。共有三种操作：

1. 向 $A$ 中插入一个点 $(x_i, y_i)$。保证此时该点不在 $A$ 中。
2. 从 $A$ 中删除一个点 $(x_i, y_i)$。保证此时该点在 $A$ 中。
3. 给定一个点 $(x_i, y_i)$，计算至少需要向 $A$ 中添加多少个点，才能使 $A$ 关于经过点 $(0, 0)$ 和 $(x_i, y_i)$ 的直线对称。注意，这些点实际上并不会被加入 $A$，即这些询问彼此独立。

## 说明/提示

第一个样例如下图所示。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1028F/65c263b7b9a9f09938382f417e96d6878dd5db02.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
12
1 1 6
1 6 1
1 5 5
1 2 3
3 4 4
1 3 2
3 7 7
2 2 3
2 6 1
3 8 8
2 5 5
3 1 1
```

### 输出

```
1
0
2
2
```

## 样例 #2

### 输入

```
6
1 1 2
3 1 1
1 1 1
3 2 2
2 1 1
3 2 4
```

### 输出

```
1
1
0
```

# 题解

## 作者：雄鹰展翅 (赞：3)

这是一道STL的练习题。

如果你没有思路并且看了以上的提示，可以回去再重新思考一会，说不定就$AC$了。

-----------

若$A(x_1,y_1)$和$B(x_2,y_2)$关于直线$y=kx$对称，且点$C(x,y)$在直线$y$上，

则有 $OA=OB$,即$A$和$B$都在半径为$R=OA$的圆上，每次插入和删除也只会影响到同一个圆上的点。

[![0Jl1rd.png](https://s1.ax1x.com/2020/10/04/0Jl1rd.png)](https://imgchr.com/i/0Jl1rd)

但是，仅仅知道$OA=OB$不能判断$A$和$B$关于直线对称，还需要满足$\dfrac{x_1+x_2}{2}=x,\dfrac{y_1+y_2}{2}=y$ 。

[![0J1lWT.png](https://s1.ax1x.com/2020/10/04/0J1lWT.png)](https://imgchr.com/i/0J1lWT)

注意，这里我们将一个点的坐标化简为最简比后存储。

然后把每一个点存到对应半径的$vector$里，每加入一个点就更新$vector$里其余点的答案。

看到这里，有些同学可能会产生疑问：这不是$O(n^2)$的时间复杂度吗？题中明明$q≤2*10^5$呀？

仔细看一遍题目，发现题中的点都是网格上的点，

**而方程$x^2+y^2=N$的整数解远小于$N$，当$N≤2∗112904$时解数小于$144$。**

知道这一点后我们就可以放心地写~~暴力~~正解啦

时间复杂度$O(144*q)$

```cpp
#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<vector>
#include<map>
#define ll long long
using namespace std;

#define xx first
#define yy second
#define pb push_back
#define mp make_pair
#define pr pair<int,int>

inline int read() {
	int w = 0, f = 1; char c;
	while (!isdigit(c = getchar())) c == '-' && (f = -1);
	while (isdigit(c)) w = w*10+(c^48), c = getchar();
	return w * f;
}

#define N 500005

int q,cnt,idx;
bool del[N];//标记第i个点是否删除
vector<pr> a[N];//存储每个半径下的所有点
map<ll,int> Map;//半径对应的编号
map<pr,int> ans;//关于过点(0,0),(x,y)直线对称的点对数

int ID(ll r){//返回半径的编号
	if(Map.count(r)) return Map[r];
	return Map[r]=++idx;
}

int gcd(int x, int y) {return !y?x:gcd(y,x%y);}

pr frac(pr x){//返回坐标的最简比
	int z=gcd(x.xx,x.yy);
	return pr(x.xx/z,x.yy/z);
} 

int main(){
	int i,op,x,y;
	q=read();
    
	while(q--){
		op=read(),x=read(),y=read();
		ll r=x*x+y*y,id=ID(r);
		if(op==1){
			cnt++;
			for(i=0;i<a[id].size();i++) //更新答案（可以用auto写，但考试的时候好像不行）
				ans[frac({a[id][i].xx+x,a[id][i].yy+y})]+=2;
			ans[frac({x,y})]++;
			a[id].pb(pr(x,y));
		} 
		if(op==2){
			cnt--;
			pr t=frac({x,y});
			for(i=0;i<a[id].size();i++) //更新答案
				if(a[id][i]!=mp(x,y))
					ans[frac({a[id][i].xx+x,a[id][i].yy+y})]-=2;
			vector<pr>::iterator it=a[id].begin();
			while(*it!=mp(x,y)) it++;
			a[id].erase(it); //删点
			ans[t]--;
		}
		if(op==3) printf("%d\n",cnt-ans[frac({x*2,y*2})]);//总点数-已对称点数=答案
	}
	
	return 0;
}

```

回过头来看这道$CodeForces$上的$F$题，用到了什么数据结构？

只用到了$STL$，两个$map$和一个$vector$。

当然，还有我们一步步的分析和推理。



---

## 作者：Luciylove (赞：0)

*2900？*1900！！

考虑定义就知道要到 $(0, 0)$ 的距离相同，然后这个又是格点，所以对于定长的点对个数很少。

最多大概只有 $V = 144$ 个？好像是的。

然后我们插入删除直接模拟，枚举距离相同的点，只需要求出对应的斜率即可。

具体来说我们考虑两个点对的中点就在那条对称轴上，也就是说我们对 $(x_1 + x_2, y_1 + y_2)$ 的极角来维护就好了。

实现使用了 map 套 set。

时间复杂度大概是 $O(Vq \log n)$ 属于是比较 dirty work 了。

实际上远远跑不满。

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = l; i <= r; i ++)
#define per(i, r, l) for (int i = r; i >= l; i --)

using namespace std;
typedef long long ll;

const int _ = 1e5 + 2, mod = 1e9 + 7;

int read () {
    int ans = 0; char c = getchar(), last = ' ';
    while(c < '0' || c > '9') last = c,c = getchar();
    while(c >= '0' && c <= '9') ans = (ans << 1) + (ans << 3) + c - '0',c = getchar();
    return last == '-' ? - ans : ans;
}
int power (int x, int y) {
	int ret = 1;
	for ( ; y; y >>= 1, x = 1ll * x * x % mod)
		if (y & 1) ret = 1ll * ret * x % mod;
	return ret;
}

int T;
int n, tn;

#define pii pair<int, int>
map <pii, int> mp;
map <ll, set<pii> > tmp; 
 
pii node (int x, int y) {
	int gc = __gcd(x, y);
	x /= gc, y /= gc; return {x, y};	
} 
int main () {
	n = read();
	while (n --) {
		int op = read(), x = read(), y = read();
		if (op == 1) {
			++ tn;
			ll R = 1ll * x * x + 1ll * y * y;
			for (auto it : tmp[R]) {
				mp[node(x + it.first, y + it.second)] += 2;
			}
			tmp[R].insert({x, y});
			mp[node(x, y)] ++;
		} else if (op == 2) {
			-- tn;
			ll R = 1ll * x * x + 1ll * y * y;
			tmp[R].erase({x, y});
			for (auto it : tmp[R]) {
				mp[node(x + it.first, y + it.second)] -= 2;
			}
			mp[node(x, y)] --;
		} else {
			printf("%d\n", tn - mp[node(x, y)]);
		}
	}
	return 0;
}

```


---

