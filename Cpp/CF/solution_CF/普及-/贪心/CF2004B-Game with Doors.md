# Game with Doors

## 题目描述

### 题面描述
有 $100$ 个房间排成一列，之间有 $99$ 个门; 第 $i$ 个门连接第 $i$ 个房间和第 $i+1$ 个房间。每扇门可以上锁也可以不上锁。最初，所有的门都没有锁。

我们说，房间 $x$ 是可以到房间 $y$ 的，如果 $x$ 与 $y$ 之间的所有门都没锁。

你知道的:

- 爱丽丝在 $[l,r]$ 的某个房间里;
- Bob 在 $[L,R]$ 的某个房间里;
- 爱丽丝和鲍勃在不同的房间。

然而，你并不知道他们所在的确切房间。

你不希望爱丽丝和鲍勃能够联系到对方，所以你要锁上一些门来防止这种情况发生。无论 Alice 和 Bob 在给定段中的起始位置如何，您需要锁定的门的最小数量是多少？

## 样例 #1

### 输入

```
4
1 2
3 4
2 5
2 5
3 7
6 7
4 5
2 8```

### 输出

```
1
3
2
3```

# 题解

## 作者：NEKO_Daze (赞：5)

[洛谷CF2004B](https://www.luogu.com.cn/problem/CF2004B) || [CodeForces 2004 B](https://codeforces.com/contest/2004/problem/B)

### 简要题意
有 $100$ 个房间排成一排，它们之间有 $99$ 扇门，第 $i$ 扇门（$1\le i\le 99$）连接着 $i$ 和 $i+1$ 两个房间,每扇门有上锁和不上锁两种状态，在初始时所有的门都没有上锁。

如果两房间之间没有一扇门是上锁的，那么这两房间连通。

已知 $A$ 在 $[l, r]$ 段的某个房间里，$B$ 在 $[L, R]$ 段的某个房间里，且二人所处的房间不同，不知道他们具体在哪个房间。你要锁上一些门使得不管二人所处在区间中的具体哪个房间，二人所处的房间都不连通，且最小化操作数。

### 思路
分类讨论不同情况。

* 当区间 $[l,r]$ 与 $[L,R]$ 之间交集为空，锁上两区间之间的任意一扇门即可，显然答案为 $1$；
* 若交集不为空，交集内的所有门都需被上锁，由于不保证 $[l,r]$ 一定在 $[L,R]$ 左侧或一定在右侧，答案至少为 $\min(r,R)-\max(l,L)$；
* 如果出现区间端点不重合，还需要锁上端点上的门，并将答案 $+1$。

[AC记录](https://codeforces.com/contest/2004/submission/278234152)

```cpp
#include <bits/stdc++.h>
using namespace std; 
int main() {
  int t;
  cin >> t;
  while (t--) {
    int l, r, L, R;
    cin >> l >> r >> L >> R;
    int ans = min(r, R) - max(l, L);
    if (ans < 0) {
      ans = 1;
    } else {
      ans += (l != L);
      ans += (r != R);
    }
    cout << ans << endl;
  }
}
```

---

## 作者：hema5177 (赞：2)

### 大致题意

有 100 个房间与联通它们的 99 扇门，Alice 和 Bob 分别在区间为 $[l,r]$ 和区间为 $[L,R]$ 的房间内，且不在同一个房间。求出最少需要锁门的数量，使得 Alice 和 Bob 所在区间的房间不联通。

### 思路

分类讨论。

1. 区间相交：锁相交房间的所有门即可，也就是相交房间个数 $+2$。
2. 区间包含：锁被包含区间的所有门。特别的，如果两个区间的首相同或尾相同，则需要锁的门数 $-1$；如果两个区间相同，则需要锁的门数 $-2$。
3. 区间互相独立：只用锁一扇门。

### 代码


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
using namespace std;
int t;
int main()
{
	cin>>t;
	while(t--)
	{
		int l1,l2,r1,r2;
		cin>>l1>>r1>>l2>>r2;
		if(l1>l2||l1==l2&&r1>r2)
		{
			swap(l1,l2);
			swap(r1,r2); 
		}
		if(r1<l2) cout<<"1\n";//相互独立 
		else if(l1==l2&&r1==r2) cout<<r1-l1<<endl;//区间相同 
		else if(l1==l2&&r1!=r2||r1==r2&&l1!=l2) cout<<r1-l2+1<<endl;//区间首相同或尾相同 
		else if(l1<l2&&r2<r1) cout<<r2-l2+2<<endl;//相交
		else cout<<r1-l2+2<<endl;//其余包含的情况 
	}
}
```

最后附上[AC记录](https://codeforces.com/contest/2004/submission/277854683)。

---

## 作者：Infinite_Loop (赞：1)

# CF2004B
## 题意
有 $100$ 个房间排成一列，之间有 $99$ 个门，第 $i$ 个门连接第 $i$ 个房间和第 $i+1$ 个房间。初始所有门都没有锁上。

如果两个不同的房间之间所有的门都没有上锁，那么这两个房间是连通的。

现在 Alice 在 $[l,r]$ 中的某个房间，Bob 在 $[L,R]$ 中的某个房间，且两个人在不同房间。问至少要锁上多少门，使得 Alice 和 Bob 所在的房间不连通。
## 思路
本题考虑找规律。

分类讨论一下即可发现：

- 当 $[l,r]$ 和 $[L,R]$ 没有交集时，可以在它们之间锁上一道门，答案为 $1$。
- 当存在交集时，至少要将交集之间的门全部锁上，答案至少为 $\min(r,R)-\max(l,L)$。
- 本题不保证端点是否重合，如果端点不重合，则还需锁上端点上的门，答案加 $1$。

知道了上面这些性质，本题就可以轻松 AC 啦。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,l,r,L,R;
signed main(){
    cin>>t;
    while(t--){
    	cin>>l>>r>>L>>R;
    	int ans=min(r,R)-max(l,L);
    	if(ans<0)ans=1;
    	else ans+=(l!=L)+(r!=R);
    	cout<<ans<<'\n'; 
	}
    return 0;
}
```

---

## 作者：M1KuM3yusQAQ (赞：0)

#### 题意

一条直线上有 $100$ 个房间，每个房间之间有一扇门连接，即共有 $99$ 扇门。

已知有两人分别在区间 $[l, r]$ 和 $[L, R]$ 的任意一个房间里，问要使两人无论出现在区间内的哪个房间（两人不在同一个房间），两人房间之间至少有一扇门上锁。

#### 分析

**分类讨论**。

先对输入进行处理，保证区间 $[l, r]$ 在 $[L, R]$ 的左边或两区间重合。

- $[l, r] \cap [L, R] = \emptyset$（$l \le r \le L \le R$）。

如图。不难发现，只要锁住 $[r, L]$ 区间任意一扇门即可。

(![](https://cdn.luogu.com.cn/upload/image_hosting/xs1xi6ff.png))

- $[l, r] \cap [L, R] \not= \emptyset$（$l \le r \le L \le R$）。

  - 如图，当 $[L, R] \subset [l, r]$ 时，锁住区间 $[L, R]$ 内的所有门即可。

    ![](https://cdn.luogu.com.cn/upload/image_hosting/ef21zo4a.png)

  - 如图。对于其他情况，锁上区间 $[L, r]$ 内的所有门即可。

    ![](https://cdn.luogu.com.cn/upload/image_hosting/cyc103qr.png)

需要注意的是，由于两个人不会出现在同一个房间，当两区间端点重合时我们可以少锁一扇门。如图。

![](https://cdn.luogu.com.cn/upload/image_hosting/sz7wso7r.png)

#### 代码

```c++
#include <bits/stdc++.h>
using namespace std;

int T;
int xl, xr, xL, xR;
int l, r, L, R;
int res;

int main() {
	ios::sync_with_stdio(false);
	cin >> T;

	while (T--) {
		cin >> xl >> xr >> xL >> xR;
		if (xl < xL) {
			l = xl, r = xr, L = xL, R = xR;
		} else if (xl == xL) {
			if (xr < xR) {
				l = xl, r = xr, L = xL, R = xR;
			} else {
				l = xL, r = xR, L = xl, R = xr;
			}
		} else {
			l = xL, r = xR, L = xl, R = xr;
		}

		if (r < L)
			cout << 1 << endl;
		else {
			if (R <= r)
				res = R - L + 2;
			else
				res = r - L + 2;

			if (l == L)
				res--;
			if (r == R)
				res--;

			cout << res << endl;
		}

	}


	return 0;
}
```

希望能帮到各位，请多指教。orz

---

## 作者：GeXiaoWei (赞：0)

# CF2004B Game with Doors
## 解析
若区间 $[l,r]$ 与 $[L,R]$ 不相交，那么答案为 $1$，中间关闭任意一扇门。

若相交，相交的部分都要上锁，答案至少为 $\min(r,R)-\max(l,L)$。因为不能保证这两个区间谁在左右。

如果出现区间端点不重合，还需要锁上端点上的门，并将答案加一。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int l,L,r,R,ans,t;
int main(){
  	scanf("%d",&t);
  	while (t--) {
    	scanf("%d%d%d%d",&l,&r,&L,&R);
    	ans=min(r,R)-max(l,L);
    	if(ans<0) ans=1;
    	else ans+=(l!=L)+(r!=R);
    	printf("%d\n",ans);
	}return 0;
}
```

---

## 作者：RaymondOccam (赞：0)

### 题目传送门
[link](https://codeforces.com/problemset/problem/2004/B)

### 题意
有 $100$ 个房间排成一列，之间有 $99$ 个门; 第 $i$ 个门连接第 $i$ 个房间和第 $i+1$ 个房间。每扇门可以上锁也可以不上锁。最初，所有的门都没有锁。

我们说，房间 $x$ 是可以到房间 $y$ 的，如果 $x$ 与 $y$ 之间的所有门都没锁。

你知道的:

- 爱丽丝在 $[l,r]$ 的某个房间里;
- Bob 在 $[L,R]$ 的某个房间里;
- 爱丽丝和鲍勃在不同的房间。

然而，你并不知道他们所在的确切房间。

你不希望爱丽丝和鲍勃能够联系到对方，所以你要锁上一些门来防止这种情况发生。无论 Alice 和 Bob 在给定段中的起始位置如何，您需要锁定的门的最小数量是多少？

### 思路
两人所处房间段一共有 $5$ 种情况：

1. 不相交，答案为 $1$；
2. 完全相交，答案为相交部分的长度 $-1$；
3. 一人所在房间段包含另一人所在房间段（同一起点或终点），答案为较小的房间段长度；
4. 一人所在房间段包含另一人所在房间段（起点终点不同），答案为较小的房间段长度 $+1$；
5. 相交一部分，答案为相交部分的长度 $+1$。

### 代码
```cpp
#include <iostream>
#define ll long long
using namespace std;
ll T, l, r, L, R, res;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> T;

    while (T--)
    {
        cin >> l >> r >> L >> R;

        if (l > R || L > r)
            res = 1;
        else if (l == L && r == R)
            res = R - L;
        else if (l <= L && R <= r && (l == L || R == r))
            res = R - L + 1;
        else if (L <= l && r <= R && (l == L || R == r))
            res = r - l + 1;
        else if (l < L && R < r)
            res = R - L + 2;
        else if (L < l && r < R)
            res = r - l + 2;
        else if (l <= L)
            res = r - L + 2;
        else
            res = R - l + 2;

        cout << res << '\n';
    }
    return 0;
}
```

---

## 作者：GY程袁浩 (赞：0)

### 思路

考虑两个区间的交，如果有交，那么交内的所有边都要去除，如果交的两边是可及的，也需要去除交的左右两边。

如果无交，直接去除两个区间中间区间的其中一点即可。

### Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
	int tt;
	cin>>tt;
	while(tt--) {
		int x1,y1,x2,y2,ans=0;
		cin>>x1>>y1>>x2>>y2;
		if(max(x1,x2)<=min(y1,y2)) {
			ans=min(y1,y2)-max(x1,x2);
			ans+=(x1!=x2);ans+=(y1!=y2);
			cout<<ans<<endl;
		}
		else cout<<1<<endl;
	}
	return 0;
}
```

注意是 $\le$。

---

## 作者：Redamancy_Lydic (赞：0)

## 题意

给你两个区间，现在可以封锁一些边，问使得两区间中任意两点都不能互相到达所需的最小封锁数。

## 分析

分点情况。

首先如果两区间不交，那么封锁一个即可。

否则，我们发现剩下的情况其实可以统一考虑，因为我们终究要封锁的是两区间的并集。

求出两区间中较小的 $r$ 和较大的 $l$，根据题意容易得出一般情况的答案为 $r-l+2$，但是考虑如果两个 $l$ 相等，那我无需封锁 $l-1$ 和 $l$，$r$ 同理。所以这时候特判并且略改答案即可。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int w=1,s=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')w=-1;ch=getchar();}
	while(isdigit(ch)){s=s*10+(ch-'0');ch=getchar();}
	return w*s;
}
const int mod=998244353;
const int maxn=1e6+10;
const int inf=1e17;
const double eps=1e-10;
void Main()
{
	int l1=read(),r1=read();
	int l2=read(),r2=read();
	if(l1>l2){swap(l1,l2);}
	if(r1>r2){swap(r1,r2);}
	if(r1<l2)return puts("1"),void();
	int ans=r1-l2;
	if(l1!=l2)ans++;
	if(r1!=r2)ans++;
	cout<<ans<<endl;
}
signed main()
{
	int T=read();
	while(T--)Main();
	return 0;
}
```
点个赞吧。

---

