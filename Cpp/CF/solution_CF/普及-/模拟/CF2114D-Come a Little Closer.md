# Come a Little Closer

## 题目描述

The game field is a matrix of size $ 10^9 \times 10^9 $ , with a cell at the intersection of the $ a $ -th row and the $ b $ -th column denoted as ( $ a, b $ ).

There are $ n $ monsters on the game field, with the $ i $ -th monster located in the cell ( $ x_i, y_i $ ), while the other cells are empty. No more than one monster can occupy a single cell.

You can move one monster to any cell on the field that is not occupied by another monster at most once .

After that, you must select one rectangle on the field; all monsters within the selected rectangle will be destroyed. You must pay $ 1 $ coin for each cell in the selected rectangle.

Your task is to find the minimum number of coins required to destroy all the monsters.

## 说明/提示

Below are examples of optimal moves, with the cells of the rectangle to be selected highlighted in green.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2114D/925186708229ffea7667613d0cb72eebcaadb566.png) Required move for the first example.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2114D/213433b9bab32a2ca839daa9c0de4a82a4c12eb5.png) Required move for the fifth example.

## 样例 #1

### 输入

```
7
3
1 1
1 2
2 1
5
1 1
2 6
6 4
3 3
8 2
4
1 1
1 1000000000
1000000000 1
1000000000 1000000000
1
1 1
5
1 2
4 2
4 3
3 1
3 2
3
1 1
2 5
2 2
4
4 3
3 1
4 4
1 2```

### 输出

```
3
32
1000000000000000000
1
6
4
8```

# 题解

## 作者：IGpig (赞：4)

## CF2114D

### Solution

直接按照题意移动，枚举每一个移动的点，可以理解为把这个点塞到了长方形中，也就是删掉，然后每次都计算面积。\
这里用 `multiset` 非常方便：

- 先把每个 $x_i$，$y_i$ 插入。
- 枚举删除的点，先删掉。
- 判断两个 `multiset` 是否为空，是则跳过。
- 计算长宽，也就是最大值与最小值之差，更新面积。
- 如果塞不进去，就安在边上。
- 最后再重新插入回去。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
using LL = long long;
const LL N = 2e5 + 5;
LL X[N], Y[N], n, ans;
multiset<LL> cnt1, cnt2;

void solve(){
    cnt1.clear(), cnt2.clear();
    ans = 1e18 + 5; // 初始化一个非常大的值
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> X[i] >> Y[i];
        cnt1.insert(X[i]);
        cnt2.insert(Y[i]);
    }
    
    LL w = *cnt1.rbegin() - *cnt1.begin() + 1, h = *cnt2.rbegin() - *cnt2.begin() + 1;
    ans = min(ans, w * h);

    for (int i = 1; i <= n; i++) {
        cnt1.erase(cnt1.find(X[i]));
        cnt2.erase(cnt2.find(Y[i]));
        if (cnt1.empty() || cnt2.empty()) {
            cnt1.insert(X[i]);
            cnt2.insert(Y[i]);
            continue;
        }
        w = *cnt1.rbegin() - *cnt1.begin() + 1;
        h = *cnt2.rbegin() - *cnt2.begin() + 1;
        ans = min(ans, w * h);
        if (ans == n - 1) {
            ans += min(w, h);
        }
        cnt1.insert(X[i]);
        cnt2.insert(Y[i]);
    }

    cout << ans << endl;
}

int main(){
    LL t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

```

---

## 作者：songhy_QWQ (赞：1)

## CF2114D Come a Little Closer

[**题目传送门**](https://codeforces.com/contest/2114/problem/D)
### Solution 
1. 找到每一维度的最大、最小、次大、次小值
2. 循环遍历每一个点，判断其是否为最点，若是，则将其更新为次点
3. 每次求一遍 $ans$ 最小值
   
_**PS： 需注意，如果说怪兽格子填满了需要另开一行**_ 

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int Mx=1e9;
const int N=2e5+5;
struct node{
	int x,y;
}a[N];
int T,n;
signed main(){
	cin>>T;
	while(T--){
		cin>>n;
		int mxx[2],mnx[2],mxy[2],mny[2];
		mxx[0]=mxx[1]=mxy[0]=mxy[1]=0;
		mnx[0]=mnx[1]=mny[0]=mny[1]=Mx;
		for(int i=1;i<=n;i++){
			cin>>a[i].x>>a[i].y;
            //找最&次点
			if(a[i].x>mxx[0])mxx[1]=mxx[0],mxx[0]=a[i].x;
			else if(a[i].x>mxx[1])mxx[1]=a[i].x;
			if(a[i].x<mnx[0])mnx[1]=mnx[0],mnx[0]=a[i].x;
			else if(a[i].x<mnx[1])mnx[1]=a[i].x;
			if(a[i].y>mxy[0])mxy[1]=mxy[0],mxy[0]=a[i].y;
			else if(a[i].y>mxy[1])mxy[1]=a[i].y;
			if(a[i].y<mny[0])mny[1]=mny[0],mny[0]=a[i].y;
			else if(a[i].y<mny[1])mny[1]=a[i].y;
		}
		if(n==1){
			cout<<1<<endl;
			continue;
		}
		bool f1,f2,f3,f4;
		int ans=Mx*Mx;
		for(int i=1;i<=n;i++){
			f1=f2=f3=f4=false;
			if(a[i].x==mxx[0])f1=true;
			if(a[i].x==mnx[0])f2=true;
			if(a[i].y==mxy[0])f3=true;
			if(a[i].y==mny[0])f4=true;
			int dx=(f1==true?mxx[1]:mxx[0])-(f2==true?mnx[1]:mnx[0])+1;
			int dy=(f3==true?mxy[1]:mxy[0])-(f4==true?mny[1]:mny[0])+1;
            //若格子已满，需另开一行
			if(dx*dy==n-1)ans=min(ans,min((dx+1)*dy,(dy+1)*dx));
			else ans=min(ans,dx*dy);
		}
		cout<<ans<<endl;
	}
} 
```

---

## 作者：LinAY827 (赞：1)

维护最小最大 $x,y$ 坐标，确定矩形面积。

挨个删除点，维护新的矩形面积。

如果删除的点放不进那个矩形中那么就加一列短边。


```cpp
#pragma G++ optimize("O3")
#include<bits/stdc++.h>
#define int long long
using namespace std;
#ifdef ONLINE_JUDGE
    const int N=200005;
#else
    const int N=2005;
#endif
int T;
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>T;
    while(T--)
    {
        int n,x[N],y[N];
        multiset<int> xcnt,ycnt;//维护xy坐标的值
        cin>>n;
        for(int i=1;i<=n;i++)
        {
            cin>>x[i]>>y[i];
            xcnt.insert(x[i]);
            ycnt.insert(y[i]);
        }
        int ans=0x3f3f3f3f3f3f3f3f;
        ans=min(ans,(*xcnt.rbegin()-*xcnt.begin()+1)*(*ycnt.rbegin()-*ycnt.begin()+1));//注意+1，原来矩形面积
        for(int i=1;i<=n;i++)
        {
            xcnt.erase(xcnt.find(x[i]));
            ycnt.erase(ycnt.find(y[i]));
            if(!xcnt.empty()&&!ycnt.empty())
            {
                ans=min(ans,(*xcnt.rbegin()-*xcnt.begin()+1)*(*ycnt.rbegin()-*ycnt.begin()+1));//新矩形面积
                if(ans==n-1)//放不下点
                    ans+=min(*xcnt.rbegin()-*xcnt.begin()+1,*ycnt.rbegin()-*ycnt.begin()+1);//新开一列
            }  
            xcnt.insert(x[i]);
            ycnt.insert(y[i]);//回溯
        }
        cout<<ans<<"\n";
    }
    return 0;
}
```

---

## 作者：D_Luffy (赞：1)

## 题意：
地图上有一些怪物，每个怪物有一个坐标，坐标不会也不能重合，有且只有一次机会规划一个矩形区域，其中的怪物都会被消灭，有且只有一次只会可以将一只怪物拖到其他没有怪物的格子，求可以将所有怪物都消灭的最小的矩形面积。

## 思路：
枚举将每个怪物都操作一次，能消灭所有怪物的最小矩形面积，取最小值。

**需要注意的是如果其他怪物已经是一个没有空缺的完美的矩形时，或者矩形的一边已经到达边界时，这种情况需要特判一下。**

```
void solve() {
	cin >> n;
	vector<pair<int, int>> a(n);
	multiset<int> minx, miny;//横坐标 以及 纵坐标的最小值
	multiset<int, greater<int>> maxx, maxy;//最大值
	for (auto &[x, y] : a) {
		cin >> x >> y;
		minx.emplace(x), maxx.emplace(x);
		miny.emplace(y), maxy.emplace(y);
	}

	//还没操作时的最小面积
	int ans = (*maxx.begin() - *minx.begin() + 1) * (*maxy.begin() - *miny.begin() + 1);
	for (auto [x, y] : a) {
		int l1 = *minx.begin(), l2 = *maxx.begin(), r1 = *miny.begin(), r2 = *maxy.begin();
		if (l1 == x) {//矩形左上角
			minx.erase(minx.begin());
			l1 = *minx.begin();
			minx.emplace(x);
		}
		if (l2 == x) {//左下角
			maxx.erase(maxx.begin());
			l2 = *maxx.begin();
			maxx.emplace(x);
		}
		if (r1 == y) {//右上
			miny.erase(miny.begin());
			r1 = *miny.begin();
			miny.emplace(y);
		}
		if (r2 == y) {//右下
			maxy.erase(maxy.begin());
			r2 = *maxy.begin();
			maxy.emplace(y);
		}
		//cout<<"l1 = "<<l1<<"\tl2 = "<<l2<<"\tr1 = "<<r1<<"\tr2 = "<<r2<<endl;
		int res = (l2 - l1 + 1) * (r2 - r1 + 1);//去掉这个点的面积
		//cout<<"res = "<<res<<endl;
		if (res < n) {//如果面积小于 n 说明放不下 n 个怪物，需要特判
			if (l2 - l1 + 1 == n)res += r2 - r1 + 1;
			else if (r2 - r1 + 1 == n)res += l2 - l1 + 1;
			else res += min(l2 - l1 + 1, r2 - r1 + 1);
		}
		ans = min(ans, res);
	}
	cout << ans << "\n";
}
```

---

## 作者：convie (赞：1)

模拟题，根据题目意思来即可，对于读入的数据，我们可以分别用两个数组来维护，用 $q[i]$ 维护以 $x$ 为准的单调递增点，用 $p[i]$ 维护以 $y$ 为准的单调递增点，然后分别对四个顶点角进行判断求最小值即可，需要注意的是，可能会存在最小值小于 $n$ 的情况，此时需要进行判断，代码如下。
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
#define int long long
#define MAXN 1000010
#define x first
#define y second
#define ios ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
typedef pair<int,int> PII;
PII q[MAXN],p[MAXN];
void solve(){
	int n;
	cin>>n;
	int x1=1e14,x2=0,y1=1e14,y2=0;
	int mi=1e18;
	for(int i=1;i<=n;i++){
		int a,b;
		cin>>a>>b;
		x1=min(x1,a);
		x2=max(x2,a);
		y1=min(y1,b);
		y2=max(y2,b);
		q[i]={a,b};
		p[i]={b,a};
	}
	if(n==1){
		cout<<1<<endl;
		return ;
	}
	sort(q+1,q+1+n);//x轴 
	sort(p+1,p+1+n);//y轴 
	if(q[n].x==p[n].y)mi=min(mi,(q[n-1].x-x1+1)*(p[n-1].x-y1+1));
	else {
		mi=min(mi,(q[n-1].x-x1+1)*(y2-y1+1));
		mi=min(mi,(x2-x1+1)*(p[n-1].x-y1+1));
	}
	if(q[n].x==p[1].y)mi=min(mi,(q[n-1].x-x1+1)*(y2-p[2].x+1));
	else {
		mi=min(mi,(q[n-1].x-x1+1)*(y2-y1+1));
		mi=min(mi,(x2-x1+1)*(y2-p[2].x+1));
	}
	if(q[1].x==p[1].y)mi=min(mi,(x2-q[2].x+1)*(y2-p[2].x+1));
	else {
		mi=min(mi,(x2-q[2].x+1)*(y2-y1+1));
		mi=min(mi,(x2-x1+1)*(y2-p[2].x+1));
	} 
	if(q[1].x==p[n].y)mi=min(mi,(x2-q[2].x+1)*(p[n-1].x-y1+1));
	else {
		mi=min(mi,(x2-q[2].x+1)*(y2-y1+1));
		mi=min(mi,(x2-x1+1)*(p[n-1].x-y1+1));
	} 
	if(mi<n){
		mi=1e18;
		 	if(q[n].x==p[n].y)mi=min(mi,min((q[n-1].x-x1+2)*(p[n-1].x-y1+1),(q[n-1].x-x1+1)*(p[n-1].x-y1+2)));
		else {
			mi=min(mi,(q[n-1].x-x1+2)*(y2-y1+1));
			mi=min(mi,(q[n-1].x-x1+1)*(y2-y1+2));
			mi=min(mi,(x2-x1+1)*(p[n-1].x-y1+2));
			mi=min(mi,(x2-x1+2)*(p[n-1].x-y1+1));
		}
			if(q[n].x==p[1].y)mi=min(mi,min((q[n-1].x-x1+1)*(y2-p[2].x+2),(q[n-1].x-x1+2)*(y2-p[2].x+1)));
		else {
			mi=min(mi,(q[n-1].x-x1+2)*(y2-y1+1));
			mi=min(mi,(q[n-1].x-x1+1)*(y2-y1+2));
			mi=min(mi,(x2-x1+2)*(y2-p[2].x+1));
			mi=min(mi,(x2-x1+1)*(y2-p[2].x+2));
		}
		if(q[1].x==p[1].y)mi=min(mi,min((x2-q[2].x+1)*(y2-p[2].x+2),(x2-q[2].x+2)*(y2-p[2].x+1)));
		else {
			mi=min(mi,(x2-q[2].x+2)*(y2-y1+1));
			mi=min(mi,(x2-q[2].x+1)*(y2-y1+2));
			mi=min(mi,(x2-x1+2)*(y2-p[2].x+1));
			mi=min(mi,(x2-x1+1)*(y2-p[2].x+2));
		} 
			if(q[1].x==p[n].y)mi=min(mi,min((x2-q[2].x+2)*(p[n-1].x-y1+1),(x2-q[2].x+1)*(p[n-1].x-y1+2)));
		else {
			mi=min(mi,(x2-q[2].x+2)*(y2-y1+1));
			mi=min(mi,(x2-q[2].x+1)*(y2-y1+2));
			mi=min(mi,(x2-x1+2)*(p[n-1].x-y1+1));
			mi=min(mi,(x2-x1+1)*(p[n-1].x-y1+2));
		} 
	}
	cout<<mi<<endl;
}
signed main(){
	ios;
	int t;
	cin>>t;
	while(t--)
	solve();
	return 0;
}
```

---

## 作者：wzy090702 (赞：1)

# CF2114D 题解
[题目传送门](https://www.luogu.com.cn/problem/CF2114D)

[翻译传送门（vjudge）](https://vjudge.net/problem/CodeForces-2114D#author=DeepSeek_zh)

---

## 分析
先把移动怪物前的最小矩形叫做原矩形，移动后构成的矩形叫做新矩形。

题目要求算出新矩形，那必定有贪心。而题目中的“移动一个怪物”，根据贪心的思想，要使新矩形面积最小，这个被移动的怪物应该移动进新矩形内。进一步分析，我们可以发现：
- 被移动进新矩形的怪物可以视为不存在
- 在原矩形内部（即在该矩形内但不在边上）的怪物不论移动到哪里去，新矩形面积一定不小于原矩形

于是，我们可以变相理解为：给定怪物的坐标，求删去原矩形的长宽边上其中一个怪物后新矩形面积的最小值。

下面给出一组例子，使我们更好理解。

![](https://cdn.luogu.com.cn/upload/image_hosting/gh4nbq07.png)

对于上面的例子，五角星代表一只怪物的坐标。若不删除怪物，蓝色框为此时最小矩形，面积为 $ 6 \times 5 = 30 $。

![](https://cdn.luogu.com.cn/upload/image_hosting/dvo32i9i.png)

如上图，在原矩形内部的 $ 2 $ 号可以直接不用考虑它。删去 $ 1 $ 号后新矩形为黄色矩形，面积为 $ 6 \times 4 = 24 $；删去 $ 3 $ 号，新矩形为绿色矩形，面积为 $ 3 \times 5 = 15 $；同理，删去 $ 4 $ 号或 $ 5 $ 号后，面积均为 $ 30 $。所以，答案为 $ 15 $。

![](https://cdn.luogu.com.cn/upload/image_hosting/kn4q3rw3.png)

但是，像这种，怪物无法“加入”到其他怪物中间来时，就应该在红色圆圈面积的基础上加上一行的面积。

## 实现
那么，该如何用代码实现呢？

本题数据中坐标极大，无法使用二维数组进行存储。这时，我们就应该请出一位“大神”：

```cpp
multiset<int>a;
```
这个数据结构可以看成一个序列，其能够在 $O(\log{n})$ 内的时间完成删除或插入一个数，并且**能够保证任何时间内内部数据是有序的且允许有相同的数**。

那么，接下来就简单了：维护一下各个怪物的坐标，然后进行上述处理即可。
## 完整代码

```cpp
#include<bits/stdc++.h>
#define For(i,a,n,x) for(int i=a;i<=n;i+=x)
#define Ror(i,n,a,x) for(int i=n;i>=a;i-=x)
#define lowbit(x) x&-x
#define ll long long
#define ull unsigned long long
#define opera (*a.rbegin()-*a.begin()+1)
#define operb (*b.rbegin()-*b.begin()+1)
using namespace std;//神奇の缺省源
const int N=200001;
ll t,n,x[N],y[N];
int main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);
    cin>>t;
    while(t--){      
		memset(x,0,sizeof(x));
		memset(y,0,sizeof(y));
        multiset<ll>a,b;
        cin>>n;
        For(i,1,n,1){
            cin>>x[i]>>y[i];
            a.insert(x[i]);
            b.insert(y[i]);//向multiset内加入怪物坐标 
        }
        ll ans=0x3f3f3f3f3f3f3f3f;
        ans=min(ans,opera*operb);//其实这里可以直接赋值，但是毕竟我的AC图都截好了，就懒得改了
        For(i,1,n,1){
            a.erase(a.find(x[i]));
            b.erase(b.find(y[i]));//擦除该怪物坐标 
            if(!a.empty() && !b.empty()){
                ans=min(ans,opera*operb);//更新ans 
                if(ans==n-1)ans+=min(opera,operb); //判断怪物是否除一个之外全在边上                 
            }  
            a.insert(x[i]);
            b.insert(y[i]);//重新加入坐标 
        }//不需要判断怪物是否在原面积内，时间足够 
        cout<<ans<<endl;
    }
	return 0;
}//时间复杂度为O(tn)，完美 
```
![](https://cdn.luogu.com.cn/upload/image_hosting/buj8xfiq.png)

---

## 作者：BLUEJOKE (赞：1)

- 在仅能移动一个怪物的情况下，改变原矩形四条边中的一条，即移走处于“边界”处的怪物显然是最优的。故使用 set 排序，每次删除一个“边界”上的点（$x$ 或 $y$ 为最大/最小）后进行计算取最小值。
- 判断能否将原矩形“边界”处的怪物移动到新矩形的内部，即新矩形内部是否有空间放置一个怪物。考虑特殊分布情况：$(1,1)$、$(1,2)$、$(1,3)$、$(2,1)$、$(2,2)$、$(2,3)$、$(2,4)$。如果仅仅进行删除操作而不判断是否可行，会得到错误答案 $6$，但是容易得出最小只能为 $n$，在这里的最优解为 $8$。故当出现小于 $n$ 的答案时，需要进行特判。
```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define fi first
#define sec second
#define ep emplace
#define eb emplace_back
#define pb push_back
using namespace std;
using ll = long long;
using pii = pair<int, int>;

const ll LLINF = 0x3f3f3f3f3f3f3f3fll;

void solve() {
	int n; cin >> n;
	set<pii> px, py;
	for(int i = 0; i < n; i++) {
		int x, y; cin >> x >> y;
		px.ep(x, y), py.ep(y, x);
	}
	if(n == 1) {
		cout << 1 << endl; return;
	} else if(n == 2) {
		cout << 2 << endl; return;
	}
	ll ans = LLINF;
	
	auto del = [&](int x, int y) -> ll {
		px.erase(px.find({x, y})), py.erase(py.find({y, x}));
		ll mx = (*px.begin()).fi, Mx = (*px.rbegin()).fi;
		ll my = (*py.begin()).fi, My = (*py.rbegin()).fi;
		px.insert({x, y}), py.insert({y, x});
		ll cur = abs(Mx - mx + 1) * abs(My - my + 1);
        // 特判：小于 n 的情况只有在内部填满的情况下才会出现，只需要紧挨着填满的内部放置即可。
		if(cur < n) {
			cur = min((Mx - mx + 2) * (My - my + 1), (Mx - mx + 1) * (My - my + 2)); 
		}
		return cur;
	};
	
	ans = min(ans, del((*px.begin()).fi, (*px.begin()).sec));
	ans = min(ans, del((*px.rbegin()).fi, (*px.rbegin()).sec));
	ans = min(ans, del((*py.begin()).sec, (*py.begin()).fi));
	ans = min(ans, del((*py.rbegin()).sec, (*py.rbegin()).fi));
	cout << ans << endl;
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t = 1; cin >> t;
	while(t--) {
		solve();
	}
	return 0;
}

```

---

## 作者：the_Short_Path (赞：0)

## 形式化题意
给定一个网格，其中有 $n$ 个点（点不会重合），可以移动其中一个点到任意不与其它点重合的位置，使得满足包含这 $n$ 个点的矩形面积最小。

可以维护两个 `multiset`（注意不能是 `set`），枚举删掉每一条边时的横纵坐标极差的乘积，求其最小值。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, x[200005], y[200005];
multiset <int> sx, sy;
signed main() {
    int T;
    cin >> T;
    while (T--) {
        sx.clear(), sy.clear(); // 别忘记多测清空
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> x[i] >> y[i], sx.insert(x[i]), sy.insert(y[i]);
        if (n == 1) { // 特判，否则 multiset 会为空
             puts("1");
            continue;
        }
        int ans = (*sx.rbegin() - *sx.begin() + 1) * (*sy.rbegin() - *sy.begin() + 1); // 记得处理不删点
        for (int i = 1; i <= n; i++) {
            sx.erase(sx.find(x[i])), sy.erase(sy.find(y[i])); // 一定要删点的下标，否则集合会删除所有的与之相同的元素
            ans = min(ans, (*sx.rbegin() - *sx.begin() + 1) * (*sy.rbegin() - *sy.begin() + 1));
            if (ans == n - 1) ans += min(*sx.rbegin() - *sx.begin(), *sy.rbegin() - *sy.begin()) + 1; // 如果矩形已经满了，则需要额外添加一行或一列。
            sx.insert(x[i]), sy.insert(y[i]);
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：wurang (赞：0)

简单模拟题。

先记录最小与最大的横坐标与纵坐标，只有移除四个角上的怪物才有可能缩小矩形的大小。

注意特判将要移动的怪物能否放进除了他以外选出的矩形。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

struct node 
{
    int pos, f;
} minx, miny, maxx, maxy;

int minxx, minyy, maxxx, maxyy;
int t, n, ans;
int x[200005], y[200005];

signed main() 
{
    cin >> t;
    while (t--) 
    {
        cin >> n;
        cin >> x[1] >> y[1];
        ans = 0x3f3f3f3f3f3f3f3f;
        minx = maxx = miny = maxy = {1, 0};
        if(n == 1)
        {
            cout << 1 << "\n";
            continue;
        }
        for (int i = 2; i <= n; i++) 
        {
            cin >> x[i] >> y[i];
            if (x[i] == x[maxx.pos]) maxx.f = 1;
            if (x[i] == x[minx.pos]) minx.f = 1;
            if (y[i] == y[maxy.pos]) maxy.f = 1;
            if (y[i] == y[miny.pos]) miny.f = 1;

            if (x[i] > x[maxx.pos]) maxx = {i, 0};
            if (x[i] < x[minx.pos]) minx = {i, 0};
            if (y[i] > y[maxy.pos]) maxy = {i, 0};
            if (y[i] < y[miny.pos]) miny = {i, 0};
        }
        ans = (y[maxy.pos] - y[miny.pos] + 1) * (x[maxx.pos] - x[minx.pos] + 1);
        if (!minx.f) 
        { 
            minxx = minyy = 0x3f3f3f3f3f3f3f3f;
            maxxx = maxyy = -0x3f3f3f3f3f3f3f3f;
            for(int i = 1; i <= n; i++)
            {
                if(i == minx.pos) continue;
                minxx = min(minxx, x[i]);
                maxxx = max(maxxx, x[i]);
                minyy = min(minyy, y[i]);
                maxyy = max(maxyy, y[i]);
            }
            int h = maxyy - minyy + 1;
            int w = maxxx - minxx + 1;
            if(n <= h * w) ans = min(ans, h * w);
            else ans = min(ans, min((h + 1) * w, (w + 1) * h));
        }
        if (!miny.f) 
        { 
            minxx = minyy = 0x3f3f3f3f3f3f3f3f;
            maxxx = maxyy = -0x3f3f3f3f3f3f3f3f;
            for(int i = 1; i <= n; i++)
            {
                if(i == miny.pos) continue;
                minxx = min(minxx, x[i]);
                maxxx = max(maxxx, x[i]);
                minyy = min(minyy, y[i]);
                maxyy = max(maxyy, y[i]);
            }
            int h = maxyy - minyy + 1;
            int w = maxxx - minxx + 1;
            if(n <= h * w) ans = min(ans, h * w);
            else ans = min(ans, min((h + 1) * w, (w + 1) * h));
        }
        if (!maxx.f) 
        { 
            minxx = minyy = 0x3f3f3f3f3f3f3f3f;
            maxxx = maxyy = -0x3f3f3f3f3f3f3f3f;
            for(int i = 1; i <= n; i++)
            {
                if(i == maxx.pos) continue;
                minxx = min(minxx, x[i]);
                maxxx = max(maxxx, x[i]);
                minyy = min(minyy, y[i]);
                maxyy = max(maxyy, y[i]);
            }
            int h = maxyy - minyy + 1;
            int w = maxxx - minxx + 1;
            if(n <= h * w) ans = min(ans, h * w);
            else ans =
            min(ans, min((h + 1) * w, (w + 1) * h));
        }
        if (!maxy.f) 
        { 
            minxx = minyy = 0x3f3f3f3f3f3f3f3f;
            maxxx = maxyy = -0x3f3f3f3f3f3f3f3f;
            for(int i = 1; i <= n; i++)
            {
                if(i == maxy.pos) continue;
                minxx = min(minxx, x[i]);
                maxxx = max(maxxx, x[i]);
                minyy = min(minyy, y[i]);
                maxyy = max(maxyy, y[i]);
            }
            int h = maxyy - minyy + 1;
            int w = maxxx - minxx + 1;
            if(n <= h * w) ans = min(ans, h * w);
            else ans = min(ans, min((h + 1) * w, (w + 1) * h));
        }
        cout << ans << "\n";
    }
    return 0;
}
```

---

