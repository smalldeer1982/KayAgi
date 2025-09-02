# [ROI 2018] Extraction of radium

## 题目背景

译自 [ROI 2018 Day1](https://neerc.ifmo.ru/school/archive/2017-2018.html) T1. [Добыча радия](https://neerc.ifmo.ru/school/archive/2017-2018/ru-olymp-roi-2018-day1.pdf) ([Extraction of radium](http://codeforces.com/gym/102147/problem/A))。 

## 题目描述

给一个 $n\times m$ 的矩阵 $a$，矩阵中的数互不相同。
接下来有 $q$ 次修改，每次修改会将某个值修改为一个更大的值。保证修改后矩阵中的数仍互不相同。
每次修改后，请求出：矩阵中有多少个数，既是它所在行的最大值，又是它所在列的最大值。

## 说明/提示

对于所有数据，$1\leq a(i,j) \leq 10^7$，$1\leq t\leq 10^7$，$1 \leq n,m,q \leq 2 \times 10^5$。

| 子任务编号 | $n,m$ | $q$ |
| :-----------: | :-----------: | :-----------: |
| $1$ | $1 \leq n \times m \leq 100$ | $1 \leq q \leq 100$ |
| $2$ | $1 \leq n \times m \leq 5000$ | $1\leq q \leq 5000$ |
| $3$ | $1 \leq n,m \leq 400$ | $1 \leq q \leq 2 \times 10^5$ |
| $4$ | $1 \leq n \times m \leq 2 \times 10^5$ | $1 \leq q \leq 2 \times 10^5$ |

## 样例 #1

### 输入

```
2 3 3
1 4 3
6 5 2
2 2 9
1 3 5
2 2 10```

### 输出

```
1
2
2```

# 题解

## 作者：MornStar (赞：4)

# P9286 [ROI 2018] Extraction of radium
## 题面
[link](https://www.luogu.com.cn/problem/P9286)
## 思路
### sub1 暴力
对于每一次修改，遍历整个矩阵来计算满足要求的点的个数。

时间复杂度 $O(nmq)$。能通过 subtask 1，2。

期望得分 $50pts$。

### sub2 正解

由题意可得，一行（列）中满足要求的点最多只有一个。

借此，我们可以想到去维护一些东西。

首先，使用两个数组 $row$ 和 $col$ 维护每行每列的最大值，很明显，满足要求的点 $(i$，$j)$ 满足第 $i$ 行第 $j$ 列最大值相等，即 $row_i=col_j$。

借此，我们便可以统计出初始矩阵的答案个数。

考虑动态维护答案。

可以注意到当修改一个点 $(i$，$j)$ 时，只会改变第 $i$ 行与第 $j$ 列的最大值。即答案最多只会改变 2。

于是我们可以分几种情况：

1. 第 $i$ 行与第 $j$ 列上没有满足要求的点。这时单独判断修改后的点是否能算入贡献。
2. 第 $i$ 行上有满足要求的点，如果这个点修改后大于本行最大值，那么原本那个点就失效了，答案减一。
3. 第 $j$ 行上有满足要求的点，如果这个点修改后大于本列最大值，那么原本那个点就失效了，答案同样减一。
4. 修改的点就是第 $i$ 行与第 $j$ 列上满足要求的点，先将答案减一，在后续判断中再加起来。

因为数字越改越大，所以以上四种情况以及对应修改答案的方法是成立的。

于是我们就可以维护每行每列对答案贡献的状况，以及与此行满足要求的点相对应的列与此列满足要求的点相对应的行数来达到记录满足条件的点及修改的功能。

代码如下：
```cpp
// by MornStar
// 2023.5.26
#include<bits/stdc++.h>
using namespace std;
int row[200005],col[200005],ma1[200005],ma2[200005],ans;
bool r[200005],c[200005];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n,m,q;
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++){
		for(int j=1,k;j<=m;j++){
			cin>>k;
			row[i]=max(row[i],k);
			col[j]=max(col[j],k);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(row[i]==col[j]){
				ans++;
				r[i]=c[j]=1;
				ma1[i]=j;
				ma2[j]=i;
			}
		}
	}
	for(int i=1;i<=q;i++){
		int cx,cy,val;
		cin>>cx>>cy>>val;
		if(ma1[cx]==cy)	ans--;
		if(val>row[cx]){
			row[cx]=val;
			if(r[cx]==1&&ma1[cx]!=cy){
				r[cx]=c[ma1[cx]]=0;
				ma2[ma1[cx]]=0;
				ma1[cx]=0;
				ans--;
			}
		}
		if(val>col[cy]){
			col[cy]=val;
			if(c[cy]==1&&ma2[cy]!=cx){
				c[cy]=r[ma2[cy]]=0;
				ma1[ma2[cy]]=0;
				ma2[cy]=0;
				ans--;
			}
		}
		if(row[cx]==col[cy]){
			ans++;
			r[cx]=c[cy]=1;
			ma1[cx]=cy;
			ma2[cy]=cx;
		}
		cout<<ans<<endl;
	}
}
```
时间复杂度 $O(nm+q)$，期望得分 $100pts$。


---

## 作者：Emily666 (赞：2)

### 题意
有一 $n \times m$ 的矩阵，有 $q$ 次修改，对于每次修改，将矩阵第 $x$ 行、第 $y$ 列的数改为 $t$（定义见题目），并求有多少个数既是所在行的最大值，又是所在列的最大值。
### 思路
直接模拟肯定是不行的，那么我们可以用两个结构体数组来存行的最大值和其所在列、列的最大值和其所在行，每次操作都更新一下最大值，再循环累加。具体来说就是：
1. 输入矩阵，把这个数与它所在行和列的最大值进行比较，更大就更新最大值、所在行（列）；
2. $q$ 次循环，输入 $x$、$y$、$t$ 后按第 $1$ 条的方法更新；更新完后，循环遍历两个结构体数组，如果这一行（列）的最大值等于其所在列（行）的最大值，就累加。
3. 循环遍历哪个数组，就是看 $n$ 小还是 $m$ 小。因为这个循环是一重的，可以是 $n$ 也可以是 $m$，所以我们就取他们中的最小值就可以了。

### AC 代码（时间复杂度 $O(\min(n,m)q)$）
```cpp
#include <iostream>
using namespace std;
const int N=2*1e5+5;
int n,m,q;
struct node{//结构体数组，i 表示最大值所在行（列），x 表示值
	int i,x;
}r[N],c[N];//r 和 c 分别表示行和列 
inline int read(){//快读大法
	int x=0;
	char ch=getchar();
	while(ch>='0'&&ch<='9'){//这里都是正整数，不用读符号位
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x;
}
int main(){
	n=read(),m=read(),q=read();
	int tt;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			tt=read();
			if(tt>r[i].x){//求初始状态
				r[i].x=tt;
				r[i].i=j;
			}
			if(tt>c[j].x){
				c[j].x=tt;
				c[j].i=i;
			}
		}
	}
	int x,y,t,cnt;
	while(q--){
		cnt=0;
		x=read(),y=read(),t=read();
		if(t>r[x].x){//更新最大值
			r[x].x=t;
			r[x].i=y;
		}
		if(t>c[y].x){
			c[y].x=t;
			c[y].i=x;
		}
		if(n<=m){//取 min 值
		    for(int i=1;i<=n;i++){
    			if(r[i].x==c[r[i].i].x){
    				cnt++;//如果相同就累加
    			}
    		}
    	}
		else{
		    for(int i=1;i<=m;i++){
    			if(c[i].x==r[c[i].i].x){
    				cnt++;
    			}
    		}
		}
		printf("%d\n",cnt);
	}
	return 0;
} 
```
**注意：一定要取 $\min$ 值！不然会 TLE ~~如我~~。。。**

---

## 作者：Genshin_ZFYX (赞：1)

## 暴力做法：

这题如果用暴力在每次修改后都把数组再遍历一遍，只能得 $48tps$。

而且这题的数据很大，如果非要存下矩阵的话，还是得用 STL 的可变长度数组。

## 正解：

要想 AC，我们另外开两个数组维护每一行、每一列的最大值，用 $sum$ 记录当前满足要求的数的个数，在修改之前先更新一遍两个数组和 $sum$ 的初始值。因为每次修改只会改变当前行列的最大值，所以我们只用更新当前行列的最大值和 $sum$ 即可。

---

## 作者：qzmoot (赞：1)

# 题面
[题目传送门](https://www.luogu.com.cn/problem/P9286)
# 思路
既然是求一个数是否是每列与每行的最大值，且每次修改的一个点只会变大，不会变小。

我们就可以建两个数组维护列与行的最大值，这样时间复杂度就是 $O(nm+\min(n,m)\times q)$,可以拿到满分。

接着把每个数放在桶里面，每次遍历，寻找是否可能的答案，合适的话就答案加一。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005,M=10000007;
int n,m,q,b,s[N],h[N],t[M],ans;
int main()
{
	ios::sync_with_stdio(false);
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
		{
            cin>>b;
            s[i]=max(s[i],b);
            h[j]=max(h[j],b);//初始的最大值计算 
        }
    if(n<=m)
	{
        for(int i=1;i<=m;i++)
			t[h[i]]++;//放进桶里 
        for(int i=1,x,y,z;i<=q;i++)
		{
            cin>>x>>y>>z;
            ans=0;
            s[x]=max(s[x],z);
            t[h[y]]--;
            h[y]=max(h[y],z);
            t[h[y]]++;
            for(int j=1;j<=n;++j)
                if(t[s[j]])
                    ans++;//答案计算 
            cout<<ans<<endl;
        }
    }
	else
	{
        for(int i=1;i<=n;i++)
			t[s[i]]++;//放进桶里 
        for(int i=1,x,y,z;i<=q;i++)
		{
            cin>>x>>y>>z;
            ans=0;
            h[y]=max(h[y],z);
            t[s[x]]--;
            s[x]=max(s[x],z);
            t[s[x]]++;
            for(int j=1;j<=m;++j)
                if(t[h[j]])
                    ans++;//答案计算 
            cout<<ans<<endl;
        }
    }
    return 0;
}
```

---

## 作者：ZJle (赞：0)

### 思路

可以先输入这张表格中的每一个数，用一个 ```vector``` 可以防止空间爆炸而暴毙。

预处理出每一行每一列的最大值。

用 $lid_i$ 表示这一行最大值的位置。

用 $rid_i$ 表示这一列最大值的位置。

用 $l_i,r_i$ 存储最大值。

然后用 $q$ 次询问将每一行每一列的最大值更改查询即可。

### 注意 ```vector``` 要从 0 开始记录

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int l[N],r[N],lid[N],rid[N];
//l是行,r是列 
vector<int> v[N];
int n,m,q,x,y,z;
int main()
{
	memset(l,-0x3f,sizeof(l));
	memset(r,-0x3f,sizeof(r));
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	cin>>n>>m>>q;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cin>>x;
			v[i].push_back(x);
			if(x>l[i]){
				l[i]=x;
				lid[i]=j;
			} 
			if(x>r[j]){
				r[j]=x;
				rid[j]=i;
			}
		}
	}
	int ans=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(rid[j]==i&&lid[i]==j)
			{
				ans++;
			}
		}
	}
	for(int i=1;i<=q;i++)
	{//l[x]表示第x行的最大值
	//r[y]表示第y行的最大值 
		cin>>x>>y>>z;
		x--;
		y--;
		if(lid[x]==y&&rid[y]==x)
		{
			l[x]=r[y]=z;
			v[x][y]=z;
		}
		else
		{
                // cout<<v[x].size()<<" "<<lid[x]<<endl;
                if(v[x][lid[x]]==r[lid[x]] && l[x]<z) ans--;
                if(v[rid[y]][y]==l[rid[y]] && r[y]<z) ans--;
                if(z>l[x]) l[x]=z,lid[x]=y;
                if(z>r[y]) r[y]=z,rid[y]=x;
                v[x][y]=z;
                if(lid[x]==y && rid[y]==x) ans++;
        }
		cout<<ans<<'\n';
	}
}

```

---

## 作者：pjx0106 (赞：0)

## 难点：

1: $n \times m$ 最大可以达到 $200000 \times 200000$ ,也就~~只有区区~~  $40000000000$ 。

2：每一次都要维护最大值

## 解决办法：

难点 $1$ ：使用一维数组。第 $x$ 行，第 $y$ 列，存储在 $(x - 1) \times m + y$ 。因为数据较水，所以开 $200000$ 就够了。

难点 2 ：可以维护每一行的最大值和每一列的最大值，修改只用修改这一行和这一列的最大值。通过题目意思可以证明，一行最多有一个最大值，也就是一层循环就行了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,q;
int a[200000005],l[2000005],h[2000005];//这里怕RE，开大了一点点
pair<int,int>H[200005];
int ju(int x,int y){
	return (x-1)*m+y;//计算存储在哪里
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);   
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[ju(i,j)];//一维数组存储
		}
	}
	for(int i=1;i<=n;i++){///比较每行的最大值
		h[i]=-1;//设为一个小的值，用来比较最大值
		for(int j=1;j<=m;j++){
			h[i]=max(h[i],a[ju(i,j)]);//比较最大值
		} 
	}
	for(int i=1;i<=m;i++){//比较每列的最大值
		l[i]=-1;//设为一个小的值，用来比较最大值
		for(int j=1;j<=n;j++){
			l[i]=max(l[i],a[ju(j,i)]);//比较最大值
		}
	}
	int ans=0;//计算初始答案
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(h[i]==l[j]&&h[i]==a[ju(i,j)]){//如果最大值一样并且为这一位的数字
				ans++;//答案增加
				H[i]={j,a[ju(i,j)]};//放入数组存储
			}
		}
	}
	while(q--){
		int x,y,t;
		cin>>x>>y>>t;
		a[ju(x,y)]=t;//将数值更改
		h[x]=max(h[x],t);
		l[y]=max(l[y],t);//将最大值更改
		for(int i=1;i<=n;i++){//判断有没有把原来的最大值更改
			int X=i,Y=H[i].first,v=H[i].second;
			if(Y==0)continue;
			if(X==x||Y==y){
				if(t>v){
					ans--;
					H[i]={0,0};
				}
			}
		}
		if(h[x]==t&&l[y]==t){//判断行和列是否相等
			ans++;
			H[x]={y,a[ju(x,y)]};//存储
		}
		cout<<ans<<endl;//输出
	}
	return 0;
}
```
如果你那么写了，恭喜你，拿到了 $86$ 分。

![图片](https://cdn.luogu.com.cn/upload/image_hosting/h8l2e91k.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

为啥呢？

```cpp	
......
for(int i=1;i<=n;i++){//判断有没有把原来的最大值更改
	int X=i,Y=H[i].first,v=H[i].second;
	if(Y==0)continue;
	if(X==x||Y==y){
		if(t>v){
			ans--;
			H[i]={0,0};
		}
	}
}
......
```
原来，在这层循环里，它把每一行都循环了一次，所以复杂度是 $O(n^2)$。

解决办法其实很简单，只要让有最大值的那些行循环就好了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,q;
int a[200000005],l[2000005],h[2000005];//这里怕RE，开大了一点点
pair<int,int>H[200005];
queue<int>nxt;
int ju(int x,int y){
	return (x-1)*m+y;
}
signed main(){
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[ju(i,j)];
		}
	}
	for(int i=1;i<=n;i++){
		h[i]=-1;
		for(int j=1;j<=m;j++){
			h[i]=max(h[i],a[ju(i,j)]);
		} 
	}
	for(int i=1;i<=m;i++){
		l[i]=-1;
		for(int j=1;j<=n;j++){
			l[i]=max(l[i],a[ju(j,i)]);
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(h[i]==l[j]&&h[i]==a[ju(i,j)]){
				ans++;
				H[i]={j,a[ju(i,j)]};
				nxt.push(i);//存储最大值的下标
			}
		}
	}
	while(q--){
		int x,y,t;
		cin>>x>>y>>t;
		a[ju(x,y)]=t;
		h[x]=max(h[x],t);
		l[y]=max(l[y],t);
		int N=nxt.size();
		for(int i=1;i<=N;i++){//只枚举最大值
			int j=nxt.front();
			int X=j,Y=H[j].first,v=H[j].second;
			if(Y==0)continue;
			if(X==x||Y==y){
				if(t>v){
					ans--;
					H[j]={0,0};
				}
				else nxt.push(nxt.front());//放入下标
			}
			else nxt.push(nxt.front());//放入下标
			nxt.pop();
		}
		if(h[x]==t&&l[y]==t){
			ans++;
			H[x]={y,a[ju(x,y)]};
			nxt.push(x);//放入下标
		}
		cout<<ans<<endl;
	}
	return 0;
}
```
这样，复杂度看起来是 $O(n^2)$ ,实际上要小一些，是可以过的。

---

## 作者：Cure_Wing (赞：0)

[P9286 [ROI 2018] Extraction of radium](https://www.luogu.com.cn/problem/P9286)

### 解析
暴力显然是 $O(nmq)$ 的，过不去。

考虑每次修改只会对这个元素所在行和所在列进行修改，于是想到维护两个数组 $l,r$，其中 $l_i=\max\limits_{j=1}^ma_{i,j}$，$r_i=\max\limits_{j=1}^na_{j,i}$，分别表示每一行，每一列的最大值，每次修改只需要对相应的 $l_x,r_y$ 就可以了，由于数字是越改越大，所以 $l_i,r_i$ 只会上升，顶多持平，不会下降。

对于查询，可以把其中一个数组插入桶内，另外的数组查询是否存在，如果存在一次答案加一，显然由题意可得。

如果单纯地由一个数组插入另一个，那么复杂度最坏 $O(nm+nq)$，考虑将长度更长的数组插入桶，用长度更短的数组查询，复杂度降为 $O(nm+\min\{n,m\}\cdot q)$。

### 代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
using std::cin;using std::cout;
constexpr int N=200005,M=10000007;
int n,m,q,b,x,y,t,l[N],r[N],c[M];
std::vector<int>a[N];
signed main(){
	freopen("matrix.in","r",stdin);
	freopen("matrix.out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
    cin>>n>>m>>q;
    for(int i=1;i<=n;++i){
        a[i].push_back(0);
        for(int j=1;j<=m;++j){
            cin>>b;
            a[i].push_back(b);
            l[i]=std::max(l[i],b);
        }
    }
    for(int i=1;i<=m;++i)
        for(int j=1;j<=n;++j)
            r[i]=std::max(a[j][i],r[i]);
    if(n<=m){
        for(int i=1;i<=m;++i) ++c[r[i]];
        for(int i=1;i<=q;++i){
            cin>>x>>y>>t;
            l[x]=std::max(l[x],t);
            --c[r[y]];
            r[y]=std::max(r[y],t);
            ++c[r[y]];
            int ans=0;
            for(int j=1;j<=n;++j)
                if(c[l[j]])
                    ++ans;
            cout<<ans<<'\n';
        }
    }else{
        for(int i=1;i<=n;++i) ++c[l[i]];
        for(int i=1;i<=q;++i){
            cin>>x>>y>>t;
            r[y]=std::max(r[y],t);
            --c[l[x]];
            l[x]=std::max(l[x],t);
            ++c[l[x]];
            int ans=0;
            for(int j=1;j<=m;++j)
                if(c[r[j]])
                    ++ans;
            cout<<ans<<'\n';
        }
    }
    return 0;
}
```


---

## 作者：朝夕晨曦_L (赞：0)

来一发简单做法

题目链接：[P9286 [ROI 2018] Extraction of radium ](https://www.luogu.com.cn/problem/P9286) 

通过读题目，我们不难想到，找到既是横向最大值又是纵行最大值的位置，可以单独处理横向和纵向，满足一个方向的最大值就标记一次，那么标记两次的位置就是当前局面的一个可行点。这样静态操作就明晰了。

现在考虑动态操作，把一个点的值改的比之前大，如果之前这个点事可行的，改的更大之后一定依旧满足。如果之前不是可行点，可是现在比所在列的最大值大，或者比所在行的最大值大，那么就更新标记。

更新标记的操作无非就是把之前的标记抹去，添加新标记，用 $x$ 数组储存每一行的最大值所在列，用 $y$ 数组储存每一列的最大值所在行，更新一下 $x$ 数组和 $y$ 数组即可。

这里使用动态数组来实现，注意下标。

见代码：

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cmath>
#include<cstring>
#include<vector>
using namespace std;
int x[200001],y[200001];
vector<int>a[200001];
vector<int>vis[200001];
int main()
{
    int n, m, q, ans = 0;
    scanf("%d%d%d",&n, &m, &q);
    for(int i = 0;i <= n - 1; i++){
        a[i].resize(m,0);
        vis[i].resize(m,0);
        for(int j = 0;j <= m - 1; j++){
            scanf("%d",&a[i][j]);
            if(a[i][j] > a[i][x[i]]){
                x[i] = j;
            }
            if(a[i][j] > a[y[j]][j]){
                y[j] = i;
            }
        }
    }
    for(int i = 0;i <= n - 1; i++){
        vis[i][x[i]]++;
    }
    for(int j = 0;j <= m-1; j++){
        vis[y[j]][j]++;
    }
    for(int i = 0;i <= n - 1; i++){
        for(int j = 0;j <= m - 1; j++){
           if(vis[i][j] == 2) ans++; 
        }
    }
    for(int i, j, w, o = 1;o <= q; o++){
        scanf("%d%d%d",&i, &j, &w);
        i--;
        j--;
        a[i][j] = w;
        if(vis[i][j] == 2)
        {
            printf("%d\n",ans);
            continue;
        }
        if(a[i][j] > a[i][x[i]]){
            if(vis[i][x[i]] == 2){
                ans--;
            }
            vis[i][x[i]]--;
            x[i] = j;
            vis[i][x[i]]++;
            if(vis[i][x[i]] == 2){
                ans++;
            }
        }
        if(a[i][j] > a[y[j]][j]){
            if(vis[y[j]][j] == 2){
                ans--;
            }
            vis[y[j]][j]--;
            y[j] = i;
            vis[y[j]][j]++;
            if(vis[y[j]][j] == 2){
                ans++;
            }
        }
        printf("%d\n",ans);
    }
	return 0;
}
```

---

## 作者：zzy0618 (赞：0)

[题目链接](https://www.luogu.com.cn/problem/P9286)

### 大体思路

暴力的话，可以拿到前两个点。

如果每次对全部全局判断，有些浪费。其实更改一个数，影响的只有所在的这一行与这一列。前面预处理一个初始的 $ans$，中途分类判断。以下的有效点意思是此位置的数是它所在行的最大值，又是它所在列的最大值。

1. 如果更改的位置是有效点，先将 $ans-1$，随后判断。

1. 如果新数大于所在的列的有效点，取消原有效点的资格，$ans-1$，随后判断。

1. 如果新数大于所在的行的有效点，取消原有效点的资格，$ans-1$，随后判断。**注意**，这里第 $2$ 点**并不矛盾**。

1. 如果更改的行与列没有有效点，只需随后判断。

### 解题代码。

$mx_i$ 表示第 $i$ 行的最大值。$my_j$ 表示第 $j$ 行的最大值。$w_i$ 表示处于第 $i$ 行的有效点对应的列。$r_j$ 表示处于第 $j$ 列的有效点对应的行。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 200005;
int n, m, q, ans;
int mx[N], my[N];
int w[N], r[N];
signed main() {
	std::ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	register int i, j, x, y, t;
	cin >> n >> m >> q;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) {
			cin >> t;
			mx[i] = max(mx[i], t);
			my[j] = max(my[j], t);//预处理 mx，my
		}
	}
	for (i = 1; i <= n; i++)
		for (j = 1; j <= m; j++)
			if (mx[i] == my[j])//预处理 ans，w，r
				ans++, w[i] = j, r[j] = i;
	while (q--) {
		cin >> x >> y >> t;
		if (w[x] == y)
			ans--;//Point 1 
		if (t > mx[x]) {
			mx[x] = t;
			if (w[x] != y && w[x] != 0)
				w[x] = r[w[x]] = 0, ans--;
		}//Point 2
		if (t > my[y]) {
			my[y] = t;
			if (r[y] != x && r[y] != 0)
				r[y] = w[r[y]] = 0, ans--;
		}//Point 3
		if (mx[x] == my[y])
			ans++, w[x] = y, r[y] = x;
		cout << ans << '\n';
	}
	return 0;
}

```


---

## 作者：ethan0328 (赞：0)

## 思路

发现每次修改只会改变同行和同列的最大值。所以只要预处理出每行和每列的最大值，并把值在同行中最大的存在一个 ```set``` 中。

每次修改只要更新它那一行和列的 ```set``` 中的值即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,m,q,ans,a[N],rmx[N],lmx[N];
set<int> row[N],line[N];
int calc(int x,int y)
{
	return (x-1)*m+y;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int x,y,z;
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++)
	{
		rmx[i]=-1;
		for(int j=1;j<=m;j++)
		{
			cin>>a[calc(i,j)];
			rmx[i]=max(rmx[i],a[calc(i,j)]);
		}
	}
	for(int j=1;j<=m;j++)
	{
		for(int i=1;i<=n;i++)
		{
			lmx[j]=max(lmx[j],a[calc(i,j)]);
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(a[calc(i,j)]==rmx[i]&&a[calc(i,j)]==lmx[j])
			{
				ans++;
				row[i].insert(j);
				line[j].insert(i);
			}
		}
	}
	while(q--)
	{
		cin>>x>>y>>z;
		if(a[calc(x,y)]==rmx[x]&&a[calc(x,y)]==lmx[y])
		{
			ans--;
		}
		a[calc(x,y)]=z;
		if(z>rmx[x])
		{
			for(auto i:row[x])
			{
				if(i==y)
				{
					continue;
				}
				line[i].erase(line[i].find(x));
				ans--;
			}
			row[x].clear();
			rmx[x]=z;
		}
		if(z>lmx[y])
		{
			for(auto i:line[y])
			{
				if(i==x)
				{
					continue;
				}
				row[i].erase(row[i].find(y));
				ans--;
			}
			line[y].clear();
			lmx[y]=z;
		}
		if(z==rmx[x]&&z==lmx[y])
		{
			ans++;
			row[x].insert(y);
			line[y].insert(x);
		}
		cout<<ans<<"\n";
	}
}
```


---

