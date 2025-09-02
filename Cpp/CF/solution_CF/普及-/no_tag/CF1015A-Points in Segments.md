# Points in Segments

## 题目描述

有n条线段在数轴Ox上，每条线段有介于1到m之间的整数端点。线段之间可以重合、覆盖甚至相同。每条线段由两个整数li和ri描述（1<=li<=ri<=m）--对应左、右端点。

考虑1到m之间的所有整数点。要求你输出所有的不属于任何线段的点。

当且仅当点l<=x<=r时，点x属于这条线段。

## 样例 #1

### 输入

```
3 5
2 2
1 2
5 5
```

### 输出

```
2
3 4 
```

## 样例 #2

### 输入

```
1 7
1 7
```

### 输出

```
0

```

# 题解

## 作者：sinsop90 (赞：4)

这道题如果放在更高难度在话,应该是树状数组模板

但是看了数据之后,发现这道题可以用暴力做

每一次我们把输入的两个数中间的区间暴力跑一次

如果跑到的位置没有被覆盖过,就将$ans--$

最后输出$ans$并暴力找哪些点没有被覆盖过即可

代码如下：

```
#include<bits/stdc++.h>
using namespace std;
bool mps[105];
int main(){
	int n,m,ans;
	scanf("%d%d",&n,&m);
	ans = m;
	for(int i=1;i<=n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		for(int j=x;j<=y;j++){
			if(mps[j]==false) ans--;
			mps[j] = true;
		}
//		cout<<ans<<endl;
	}
	printf("%d\n",ans);
	for(int i=1;i<=m;i++){
		if(!mps[i]){
			printf("%d ",i);
		}
	}
}
```


---

## 作者：linaonao (赞：2)

看题解大多数人用模拟（虽然是本题标算）或树状数组，于是我愉快的用了线段树。

这道题的线段覆盖相当于线段树的区间修改，枚举未被覆盖的点相当于查询点权等于0的点，这就变成线段树求和模板题了。

多说一句：线段树真是万能呐。

贴代码：

```cpp
#include<bits/stdc++.h>
#define in inline
#define ll long long 
#define gc getchar 
#define maxn 100005
#define lc p<<1
#define rc p<<1|1
int n,q;
int mo=0x3f3f3f;
int tot=0;
int ans[1000005];
in ll read(){
	ll a=0;int f=0;char p=gc();
	while(!isdigit(p)){f|=p=='-';p=gc();}
	while(isdigit(p)){a=(a<<3)+(a<<1)+(p^48);p=gc();}
	return f?-a:a;
}
using namespace std;
struct node{
	ll v,lz1,lz2;
}t[maxn<<2];
in void pushup(int p){
	t[p].v=(t[lc].v+t[rc].v)%mo;
}
in void pushdown(int p,int l,int r){
	int m=l+r>>1; ll &lz1=t[p].lz1,&lz2=t[p].lz2;
	if(lz1!=1){
		t[lc].lz2=t[lc].lz2*lz1%mo; t[rc].lz2=t[rc].lz2*lz1%mo;
		t[lc].lz1=t[lc].lz1*lz1%mo; t[rc].lz1=t[rc].lz1*lz1%mo;
		t[lc].v=t[lc].v*lz1%mo,t[rc].v=t[rc].v*lz1%mo;
		lz1=1;
	}
	if(lz2){
		t[lc].v=(t[lc].v+(m-l+1)*lz2)%mo; t[lc].lz2=(t[lc].lz2+lz2)%mo;
		t[rc].v=(t[rc].v+(r-m)*lz2)%mo; t[rc].lz2=(t[rc].lz2+lz2)%mo;
		lz2=0; 
	}
}
in void build(int p,int l,int r){
	if(l==r){t[p].v=0;return;}
	int m=l+r>>1;
	build(lc,l,m); build(rc,m+1,r);
	pushup(p);
}
in void update1(int p,int l,int r,int L,int R,ll z){
	if(l>R||r<L) return;
	if(L<=l&&r<=R){
		t[p].lz1=t[p].lz1*z%mo; t[p].lz2=t[p].lz2*z%mo;
		t[p].v=t[p].v*z%mo ;return; 
	}
	int m=l+r>>1; pushdown(p,l,r);
	update1(lc,l,m,L,R,z); update1(rc,m+1,r,L,R,z);
	pushup(p); 
}
in void update2(int p,int l,int r,int L,int R,int z){
	if(l>R||r<L) return;
	if(L<=l&&r<=R){
		t[p].lz2=(t[p].lz2+z)%mo;
		t[p].v=(t[p].v+(r-l+1)*z)%mo; return;
	}
	int m=l+r>>1; pushdown(p,l,r);
	update2(lc,l,m,L,R,z); update2(rc,m+1,r,L,R,z);
	pushup(p);
}
in ll query(int p,int l,int r,int L,int R){
	if(l>R||r<L) return 0;
	if(L<=l&&r<=R) return t[p].v;
	int m=l+r>>1; pushdown(p,l,r);
	return (query(lc,l,m,L,R)+query(rc,m+1,r,L,R))%mo;
}
in void solve1(){
	int x=read(),y=read(); ll z=read();
	update1(1,1,n,x,y,z);
}
in void solve2(){
	int x=read(),y=read(); ll z=1;
	update2(1,1,n,x,y,z);
}
in void solve3(int i){
	int x=i,y=i;
	if(!query(1,1,n,x,y)){
		ans[++tot]=i;
	}
} 
int main(){
	q=read(); n=read(); //mo=read();
	for(int i=1;i<=n*2;i++) t[i].lz1=1;
	//build(1,1,n);
	while(q--){
		solve2();
		/*for(int i=1;i<=n;++i) printf("%d ",t[i].v);
		printf("\n"); */
	}
	for(int i=1;i<=n;++i){
		solve3(i);
	}
	cout<<tot<<endl;
	for(int i=1;i<=tot;++i) printf("%d ",ans[i]);
	return 0;
} //正好一百行
```
 
 
由于代码是板子修修改改来的，所以极丑且有些与本题无关，建议理解大意后自己打。

---

## 作者：TRZ_2007 (赞：1)

### 题解[CF1015A 【Points in Segments】](https://www.luogu.com.cn/problem/CF1015A)  
其实这道题的本质是~~树状数组~~。  
# Solution  
我们怎么把这道题想成是树状数组的题呢？  
只需要这么来看题：题目给了你 $n$ 次操作，有 $m$ 个数字。每次操作是把从 $l$ 到 $r$ 的所有数字+1，求最后为0的数字。  
这是不是很像【模板】树状数组2呢？  
差分一下就好了。  
**注意，这里有m个数字，不是n个！！**  
时间复杂度：$\Theta(m\log m)$  

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 109;

template<class T>
inline void read(T& x) {
	x = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
}

int n,m,l,r;
int ans[N],tot;

namespace ArrTree {
	#define lowbit(k) k & (-k)
	int Tree[N];
	
	inline void update(int id,int k) {
		while(id <= m) {
			Tree[id] += k;
			id += lowbit(id);
		}
	}
	
	inline int query(int id) {
		int ans = 0;
		while(id > 0) {
			ans += Tree[id];
			id -= lowbit(id);
		}
		return ans;
	}
};//树状数组，不解释
using namespace ArrTree;

int main() {
	read(n);read(m);
	for(int i = 1;i <= n;i++) {
		read(l);read(r);
		update(l,1);
		update(r + 1,-1);//差分，见【模板】树状数组2即可。
	}
	for(int i = 1;i <= m;i++) {
		int data = query(i);//每一个数是多少
		if(data == 0) {//如果是0说明没有被覆盖过
			tot++;
			ans[tot] = i;//记录答案
		}
	}
	printf("%d\n",tot);
	for(int i = 1;i <= tot;i++) {
		printf("%d ",ans[i]);
	}
	return 0;
}
```  
最后看了看，我这个复杂度居然跑不过爆力，可能评测机太忙了吧。

---

## 作者：2132B (赞：0)

这道题不就是一个膜拟嘛！但是我们有高级做法：**差分**

### 正常思路

设置一个$vis$数组来储存每一个点是否被线段覆盖，而对于每一次输入$l,r$用一个循环来表示$[l..r]$被覆盖，最后查找$vis$数组没有标记的点

$code$

```cpp
#include<bits/stdc++.h>
using namespace std;
bool vis[150];//vis数组
int n, m, l, r, ans;
int main()
{
	cin >> n >> m;
	for (int i = 1;i <= n;i++)
	{
		cin >> l >> r;
		for (int j = l;j <= r;j++)
			vis[j] = 1;//标记线段
	}
	for (int i = 1;i <= m;i++)//查找有多少个没覆盖的点
		if (vis[i] == 0)
			ans++;
	cout << ans << endl;
	if (ans == 0)//细节！！细节！！！
		return 0;
	for (int i = 1;i <= m;i++)//输出点
		if (vis[i] == 0)
			cout << i << " ";
	return 0;
}
```


### 差分思路

我们的数组不用来储存数，而用来储存相邻两数之差

这样，让一条线段中所有点被标记，只需让这条线段起点位置+1，终点位置-1，最后做一个前缀和

$code$

```cpp
#include<bits/stdc++.h>
using namespace std;
int vis[150];//vis数组是差分数组
int n, m, l, r, ans;
int main()
{
	cin >> n >> m;
	for (int i = 1;i <= n;i++)
	{
		cin >> l >> r;
		vis[l - 1]++;vis[r]--;//标记
	}
	int s = 0;
	for (int i = 0;i <= m - 1;i++)
	{
		s += vis[i];vis[i] = s;
	}//前缀和
	for (int i = 0;i <= m - 1;i++)//查找有多少个没覆盖的点
		if (vis[i] == 0)
			ans++;
	cout << ans << endl;
	if (ans == 0)//细节！！细节！！！
		return 0;
	for (int i = 0;i <= m - 1;i++)//输出点
		if (vis[i] == 0)
			cout << i + 1 << " ";
	return 0;
}//不足之处，还请大佬指点
```

$P.S.$ 这个不就是铺地毯弱化版吗！



---

## 作者：lu_fish (赞：0)

为什么还有大佬用树状数组啊/kk

具体思路可以看代码。
```cpp
#include<iostream>
using namespace std;
bool pd[100100];//开一个数组，记录数轴上的点
int n,m;//含义如题
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int l,r;
        cin>>l>>r;
        for(int j=l;j<=r;j++)
            pd[j]=1;//直接循环标记被访问过的点
    }
    int ans=0;
    for(int i=1;i<=m;i++){
        if(!pd[i])ans++;//没有被访问到就说明找到一个答案
    }
    cout<<ans<<endl;
    for(int i=1;i<=m;i++){
        if(!pd[i])cout<<i<<" ";//输出未被访问的数
    }
}
```
这段代码复杂度是O(NM)，肯定可以过的，~~代码短一点还能过它不香吗~~。

---

## 作者：TianLuen (赞：0)

# CF1015A C++题解
## 题目大意：
- 有 $n$ 条线段在一根最大值为 $m$ 的数轴上。
- 这条数轴从 $1$ 开始，一直到 $m$ （也就是说，长度为 $m-1$ )。
- 每一条线段，从 $l_i$ 开始，一直到 $r_i$ ，其中经过的点被覆盖了。
- 求的是没有被覆盖的点的数量，以及其的值
## 题意分析：
对于这道题，首先想到了什么？**模拟**，对吧。这题数据规模比较小，怎么模拟应该都可以过。

具体实现过程：

1. 将一个数组初始化，默认为每一个点都没有被盖住
2. 读入每一条线段，并且将经过的点标记为已覆盖
3. 读入和处理结束，开始从头到尾遍历一遍，输出未覆盖的点的数量
4. 再遍历一遍，输出其值

## 代码：
```cpp
#include<iostream>
using namespace std;
bool a[101];
int n,l,r,k,ans; //推荐变量用全局变量
int main()
{
    cin>>n>>k;
    for(int i=1;i<=k;i++)
        a[i]=1; //初始化数轴
    for(int i=0;i<n;i++)
    {
        cin>>l>>r;
        while(l<=r)
        {
            a[l]=0;
            l++; //标记被覆盖的点
        }
    }
    for(int i=1;i<=k;i++)
        if(a[i])
            ans++;
    cout<<ans<<endl; //统计数量并输出
    for(int i=1;i<=k;i++)
        if(a[i])
            cout<<i<<" "; //最后输出它们的值
    return 0;
}
```

## The End

---

## 作者：小闸蟹 (赞：0)

```cpp
// 这题就是校门外的树，直接模拟即可
#include <iostream>
#include <array>

int main()
{
    constexpr int MaxN = 100 + 10;
    std::array<bool, MaxN> s{ false };  // s[i]表示i这个点是否被覆盖

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    while (n--)
    {
        int l, r;   // 左端点和右端点
        std::cin >> l >> r;
        for (int i = l; i <= r; ++i)
        {
            s[i] = true;    // 直接枚举整个区间里的点
        }
    }

    int Tol = 0;    // 还剩多少个点没被覆盖
    for (int i = 1; i <= m; ++i)
    {
        if (!s[i])
        {
            ++Tol;
        }
    }
    std::cout << Tol << std::endl;

    for (int i = 1; i <= m; ++i)
    {
        if (!s[i])
        {
            std::cout << i << ' ';
        }
    }
    std::cout << std::endl;

    return 0;
}
```

---

## 作者：EightSixSun (赞：0)

用一个bool数组记录线段覆盖掉的区间
然后暴力找点即可
我用了一个队列来记录答案
```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <queue>
#include <cstdlib>
#define For(i,l,r) for(int i=l;i<=r;++i)
using namespace std;
int n,m;
bool line[101];
int main()
{

    queue<int> ans;
    int tx,ty;
    scanf("%d %d",&n,&m);
    For(i,1,n)
    {
        scanf("%d %d",&tx,&ty);
        For(j,tx,ty)
         line[j]=1;
    }
    For(i,1,m)
     if(!line[i])
        ans.push(i);
    cout<<ans.size()<<"\n";
    while(!ans.empty())
    {
        cout<<ans.front()<<" ";
        ans.pop();
    }
    return 0;
}
```

---

## 作者：Aehnuwx (赞：0)

~~这道题不是sb题吗。。~~

~~然而这并不能掩盖我打比赛时掉rating的事实~~

截至2018年8月2日晚间21点52分，这道题目是黄题？？？

这题不就是校门外的树吗？？

如果想要求题目大意去看校门外的树

第一问跟校门外的树一模一样。。。。

懒得解释那么多了，上代码

$code$

```cpp
#include <bits/stdc++.h>

bool flag[100 + 1]; //存放每个点是否被覆盖了（知道了题意后就理解了）
int main()
{
	std :: memset(flag, true, sizeof(flag)); //memset
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++ i)
	{
		int l, r;
		scanf("%d%d", &l, &r); //将左边界右边界输入进来
		for(int j = l; j <= r; ++ j)
			flag[j] = false; //将在边界中的数代表的点覆盖
	}
	int ans[101], cnt = 0, s = 1;
	for(int i = 1; i <= m; i ++)
		if(flag[i])
		{
			cnt ++; //如果没有被覆盖，cnt++
			ans[s] = i; //并且把ans[s]的值设为i，输出时用
			s ++; //s要自加
		}
	printf("%d\n", cnt); //先输出cnt
	if(cnt == 0) return 0; //这个。。可以忽视，是我自己瞎bb的，不要管
	for(int i = 1; i <s; ++ i)
		printf("%d ", ans[i]); //输出ans数组
	return 0;
}
```

---

