# [BalticOI 2002] Tennis Club (Day1)

## 题目描述

有 $N$ 个人想互相交朋友，第 $i$ 个人想和 $G_i$ 个人交朋友。

求一种交朋友的分配方式。

## 说明/提示

#### 数据规模与约定

对于 $100\%$ 的数据，$2 \le N \le 1000$，$1 \le G_i < N$。

**本题使用 Special
Judge。**

#### 说明

翻译自 [BalticOI 2002 Day1 B Tennis Club](https://boi.cses.fi/files/boi2002_day1.pdf)。

## 样例 #1

### 输入

```
3
1
2
1 ```

### 输出

```
SOLUTION
2
1 3
2 ```

## 样例 #2

### 输入

```
3
2
2
1 ```

### 输出

```
NO SOLUTION```

# 题解

## 作者：floris (赞：3)

## 思路

贪心题，调整法。

我们每次选 $G_i$ 最大的人和剩下 $G$ 最大的 $G_i$ 个人交朋友即可。

可以通过调整法证明：

$d_1⩾d_2⩾···⩾d_n$ 有解等价于
$d_2−1,d_3−1,···,d_{d_1+1}−1,···,d_n$ 有解，然后归纳即可证明做法的正确性。

对于有解的情况，由于题目数据很小，小于 $1000$，所以我们可以定义一个二维数组记录朋友的关系，最后遍历输出即可。

## code


```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 1005
int n,a[N];
bool f[N][N];
struct node{
    int c,id;
}e[N];
bool cmp(node x,node y){
    return x.c>y.c;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
	cin>>n;
    for(int i=1;i<=n;i++){
        cin>>e[i].c;
        e[i].id=i;
    }
    sort(e+1,e+n+1,cmp);
    for(int i=1;i<=n;i++){
        sort(e+1,e+n+1,cmp);
        if(e[1].c==0) break;
        for(int j=2;j<=e[1].c+1;j++){
            if(e[j].c==0){
                cout<<"NO SOLUTION"<<'\n';
                return 0;
            }
            e[j].c--;
            f[e[1].id][e[j].id]=1;
            f[e[j].id][e[1].id]=1;
        }
        e[1].c=0;
    }
    cout<<"SOLUTION"<<'\n';
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(f[i][j]==1) cout<<j<<" ";
        }
        cout<<'\n';
    }
	return 0;
}
```

---

## 作者：tangml (赞：3)

贪心题。

其实思路很容易想，就是从大到小排序，然后依次减去一个好友就可以了，不成立的条件就是中途出现了无法交朋友的人，直接输出就好了。其中易错的有两点，一个是每一次循环后都要重新排序，因为有可能大小顺序有变化，另外一个是时间复杂度，如果直接排序全部肯定会超时，所以要选择未排完的数据进行排序。

```cpp
#include<bits/stdc++.h> 
using namespace std;

const int N = 1100;

int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
    return x*f;
}

int n;
struct NODE{
	int id,lover;
	int len;
	int ans[N];
}dt[N];

bool cmp1(NODE a,NODE b);
bool cmp2(NODE a,NODE b);

int main( )
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		dt[i].lover=read();
		dt[i].id=i;
	}
	for(int i=1,end=n,les=0;i<=n;i++)
	{
		sort(dt+1,dt+end+les+1,cmp1);
		les=1;
                if(end==0)	break;//一定要写，不然会RE
		int j=2;
		while(dt[1].lover>0)
		{
			if(!dt[j].lover)
			{
				cout<<"NO SOLUTION";
				return 0;
			}	
			--dt[1].lover;
			--dt[j].lover;
			if(dt[j].lover==0)--end,++les;//当前的人交完了朋友 
			dt[1].ans[++dt[1].len]=dt[j].id;
			dt[j].ans[++dt[j].len]=dt[1].id;
			j++;
		}	
		--end;
	}
	cout<<"SOLUTION"<<endl;
	sort(dt+1,dt+n+1,cmp2);
	for(int i=1;i<=n;i++)
	{
		sort(dt[i].ans+1,dt[i].ans+1+dt[i].len);
		for(int j=1;j<=dt[i].len;j++)	printf("%d ",dt[i].ans[j]);
		puts("");
	}
	return 0;

}

bool cmp1(NODE a,NODE b)
{
	return a.lover>b.lover ;
}

bool cmp2(NODE a,NODE b)
{
	return a.id<b.id;
}
```


---

## 作者：_RainCappuccino_ (赞：3)

> 目前题解区还没有证明，我交个证明。

## 形式化题意

给定每个点的度数 $d_i$，请构造一个简单无向图（无重边无自环）。

## First. 无解

首先，根据握手定理，每个无向图的度数之和为边数的两倍，所以如果度数之和为奇数，那么肯定无解。

但是发现，这种情况之外还有别的无解情况（本题有 $3$ 个无解数据，只能 AC 一个）。

而这种情况，就需要给出一个保证正确的构造方案，如果无法构造那么无解。

## Second. 构造

这里介绍一个定理：

> **Havel-Hakimi定理**  
>
> 一个不降序度数序列 $d = \{d_1,d_2,\dots, d_n\}$ 若其可以简单图化，当且仅当 $d' = \{ d_2 - 1, d_3 - 1, \dots,d_{d_1 + 1} - 1,d_{d_1+2},\dots,d_n \}$ 可以简单图化。

1. 证明：$d$ 若其可以简单图化，那么 $d'$ 可以简单图化。

	两种情况：
    1. 图 $G$ 中存在边 $\{ (1, 2),(1,3),\dots,(1,d_1 + 1)\}$，显然，此时删去这些边该图仍然为简单图且满足度数序列 $d'$，所以 $d'$ 可简单图化。
    2. 图 $G$ 中存在点对 $(i, j)$ 满足 $d_i \ge d_j$ 且仅存在边 $(1,j)$ 而不存在边 $(1,i)$ 且 $i \le d_1 + 1,j > d_1 + 1$，那么此时由于 $d_i \ge d_j$ 那么一定存在一个点 $u$ 满足存在 $(i, u)$ 但不存在 $(j, u)$，将 $(i, u)$ 修改为 $(1, u)$，$(1, j)$ 修改为 $(j, u)$，该图度数序列不变且仍然为简单图，此时，情况又变为情况 $1$。
 
2. 证明：$d'$ 可以简单图化，那么 $d$ 可以简单图化。
	构造很简单，$1$ 与 $2, 3,\dots, d_1 + 1$ 连边，该图仍为简单图，且度数序列变为 $d$。
    
显然，度数序列 $d = \{0, 0, \dots, 0\}$ 一定可以简单图化，那么只需要重复运用定理，直至度数序列化为 $d = \{ 0,0 , \dots, 0\}$ 即可。

如果不能进行如上操作（即 $d_i - 1 < 0 (2 \le i \le d_1 + 1)$），那么无解。

注意，定理中的 $d$ 是**不降序度数序列**，那么每次操作后需要排序才能再次进行操作。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 10;
int n;
pair<int, int> g[N];
vector<int> ans[N];

signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n;
	int d = 0;
	for (int i = 1; i <= n; i ++) {
		cin >> g[i].first;
		g[i].second = i, d += g[i].first;
	}
	if (d & 1) { // 握手定理
		cout << "NO SOLUTION\n";
		return 0;
	}
	for (int t = 1; t <= n; t ++) {
		sort(g + 1, g + 1 + n); // 排序
		int j = n - 1;
		while (g[n].first) { // 从次大值开始减
			g[j].first --, g[n].first --;
			if(g[j].first < 0) { //无法加边，无解
				cout << "NO SOLUTION\n";
				return 0;
			}
			ans[g[j].second].push_back(g[n].second);
			ans[g[n].second].push_back(g[j].second);
			j --;
		}
	}
	cout << "SOLUTION\n";
	for (int i = 1; i <= n; i ++) {
		for (auto u : ans[i]) cout << u <<  ' ';
		cout << endl;
	}
	return 0;
}
```

---

## 作者：ys_kylin__ (赞：3)

## 前提紧要
跟这题杠上了，调了好几天，还一度以为 SPJ 有误，终于 AC 了！写篇题解分享一下心得。
## 思路
很明显，这道题是一道贪心题。具体怎么贪呢？明显是每次都选当前可交朋友数量最多的人优先考虑。

因为有优先度，要给原数组排一下序，这里因为需要输出原坐标，考虑结构体。用 $num$ 记住可交朋友的数，$id$ 记住编号，这样就可以根据 $num$ 排序，用 $id$ 查询。最开始，我是从 $1$ 到 $n$ 排序后遍历，对于每个 $i$ 都往后找 $g _ i$ 个，用 vector 存，最后判断长度是否一致，也就是
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct node {ll num,id;}g[1005];
ll cmp(node x,node y) {return x.num>y.num;}
vector <ll> ve[1005];
int main(){
	ll n;
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++) {
		scanf("%lld",&g[i].num);
		if(g[i].num>=n) {printf("NO SOLUTION");return 0;}
		g[i].id=i;
	}
	sort(g+1,g+n+1,cmp);
	for(ll i=1;i<=n;i++) {
		ll cnt=1;
		ll b=g[i].num-ve[g[i].id].size(),j=i+1;
		while(cnt<=b) {
			if(j>n) break;
			//printf("%d %d\n",i,g[j].id);
			if(ve[g[i].id].size()==g[i].num) break;
			if(ve[g[j].id].size()==g[j].num) {
				j++;
				continue;
			}
			//while(cnt[j]==g[j].num && j<=n) j++;
			//if(j==n+1) break;
			ve[g[i].id].push_back(g[j].id);
			ve[g[j].id].push_back(g[i].id);
			cnt++;
			j++;
		}
	}
	for(ll i=1;i<=n;i++) {
		sort(ve[i].begin(),ve[i].end());
		if(ve[g[i].id].size()!=g[i].num) {
				printf("NO SOLUTION");
				return 0;
			}
	}
	printf("SOLUTION\n");
	for(ll i=1;i<=n;i++) {
		for(ll j=0;j<ve[i].size();j++) {
			printf("%lld ",ve[i][j]);
		}
		puts("");
	}
	return 0;
}
```
一提交，$60$ 分。。。

接下来，我进入了沉思状态，一沉思就是一天。（太蒻了啊！！！）直到询问若干大佬后幡然醒悟，原来如此！经过了一次“交朋友”操作后，排序就不一定是最优的了！！也就是说，每一次结束后要再排一次序。

可是，这样子看上去也太丑了，于是我用了一种更好的办法实现——

每一次用一个 while 循环，条件为 `g[1].num!=0`。什么意思？就是指当前可交朋友人数最多的人还能交朋友，在每一次循环内，都从 $2$ 遍历到  `g[1].num+1`，只要还能交朋友，就交朋友，建立关系网，这里有点图论的思想。如果遍历中发现一个不能交朋友的，直接输出无解（因为是排好序的）。

注意交朋友时，要将双方的 $num-1$，每次 while 要重新排序一次。

到最后，先判断每个人交的朋友是不是符合给出条件（要重新定义一个数组几下，因为 $num$ 经过了修改），然后依次将 vector 输出即可。
## 真正的 AC 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node {int num,id;}g[1005];
vector <int> ve[1005];//记住关系
int cnt[1005];//记住原num
int cmp(node x,node y) {return x.num>y.num;}//重定义sort排序规则
signed main(){
	int n;
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) {
		scanf("%lld",&g[i].num);
		if(g[i].num>=n) {printf("NO SOLUTION");return 0;}//没用
		g[i].id=i;
		cnt[i]=g[i].num;
	}
	sort(g+1,g+n+1,cmp);
	while(g[1].num!=0) {//while循环
		for(int i=2;i<=g[1].num+1;i++) {
			if(g[i].num==0) {
				printf("NO SOLUTION");
				return 0;
			}
			else {
				g[i].num--;
				ve[g[1].id].push_back(g[i].id);//图论经典
				ve[g[i].id].push_back(g[1].id);
			}
		}
		g[1].num=0;
		sort(g+1,g+n+1,cmp);//需要重新排序
	}
	for(int i=1;i<=n;i++) {
		sort(ve[i].begin(),ve[i].end());
		if(ve[g[i].id].size()!=cnt[g[i].id]) {//判断是不是符合给出内容
				printf("NO SOLUTION");
				return 0;
			}
	}
	printf("SOLUTION\n");
	for(int i=1;i<=n;i++) {//输出
		for(int j=0;j<ve[i].size();j++) {
			printf("%lld ",ve[i][j]);
		}
		puts("");
	}
	return 0;//终于结束了！！！！
}
```

---

## 作者：Rainber (赞：2)

## 思路

这是一道贪心算法，每一次挑想交朋友最多的那个人，优先与剩下想交朋友最多的人交朋友，如果能交的全交完了还不够，那么直接退出。

做这道题时，我们需要先从大到小按交朋友的个数排序所有人，让 $G_1$ 与 $G_\text{2-N}$ 交朋友，如果这个人的要求达到了就匹配下一个，如果如果能交的全交完了还不够就直接结束程序

例如：`2 3 1 2`，排序后变为：`3 2 2 1`，交完朋友后变为`0 1 1 0`，再次进行排序：`1 1 0 0`，最后变为：`0 0 0 0`，程序结束。

[AC](https://www.luogu.com.cn/record/117797462)代码如下：
```cpp
#include<cstdio>               //标准配置不多说
#include<algorithm>
using std::sort;
struct point
{
    int index;                 //记录是第几个人
    int num;                   //想交的朋友数
};
bool cmp(point a,point b)      //学过std::sort都知道
{
    return a.num>b.num;
}
point ls[1000];                //其实就是G数组
int map[1000][1000];           //map[i][0]记录有多少朋友，map[i][其他]为朋友编号
int main()
{
    int n,i,j;
    scanf("%d",&n);            //输入N
    for(i=0;i<n;++i)
    {
        scanf("%d",&ls[i].num);//输入Gi
        ls[i].index=i;
    }
    for(i=0;i<n;++i)
    {
        sort(ls,ls+n,cmp);     //排序，现在的ls[0]代表想交朋友最多的那个人
        for(j=1;j<n;++j)       //与剩下想交朋友最多的人交朋友
        {
            if(ls[0].num==0)   //匹配完成
            {
                break;         //匹配下一个人
            }
            if(ls[j].num==0)   //如果能交的全交完了还不够
            {
                goto noans;    //那么直接退出
            }
            ls[0].num--;       //交朋友四行箴言
            ls[j].num--;
            map[ls[0].index][++map[ls[0].index][0]]=ls[j].index;
            map[ls[j].index][++map[ls[j].index][0]]=ls[0].index;
        }
    }
    printf("SOLUTION\n");      //正常结束
    for(i=0;i<n;++i)
    {
        sort(map[i]+1,map[i]+map[i][0]+1);
        for(j=1;j<=map[i][0];++j)
        {
            printf("%d ",map[i][j]+1);
        }
        printf("\n");
    }
    end:
        return 0;
    noans:                     //无结果
        printf("NO SOLUTION");
        goto end;
}
```

本题解与[BW Blog](https://553o7g9239.oicp.vip/BillsgWu/P7403/)同步更新。

---

## 作者：indream (赞：1)

# P7403 \[BalticOI 2002 Day1] Tennis Club 题解
[P7403](https://www.luogu.com.cn/problem/P7403) | [AC](https://www.luogu.com.cn/record/136403090)

> 截止 2023/11/22，我的做法是全谷最劣解，一共跑了 2.23s。

## 思路
一眼贪心。

显然是需要交朋友个数最多的人优先交朋友，交的朋友需交朋友的个数也应尽量大。

**一人排序一次**，每次取现在需交朋友数最大的，后面从前往后模拟实现即可。
### 错解：70pts
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
    int num,cnt,id[1005],tmp;
}a[1005];
bool cmp1(node a,node b){
    return a.cnt>b.cnt;
}
bool cmp2(node a,node b){
    return a.num<b.num;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i].cnt;
        a[i].tmp=a[i].cnt;
        a[i].num=i;
    }
    for(int i=1;i<=n;i++){
    	sort(a+1,a+n+1,cmp1);
        for(int j=2;j<2+a[1].cnt;j++){
            if(a[j].cnt<=0){//无解，即无法交朋友
                cout<<"NO SOLUTION";
                return 0;
            }
            //模拟
            a[j].cnt--;
            a[1].id[a[j].num]=a[j].num;
            a[j].id[a[1].num]=a[1].num;
        }
        a[1].cnt=0;
    }
    sort(a+1,a+n+1,cmp2);
    cout<<"SOLUTION\n";
    for(int i=1;i<=n;i++){
        for(int j=0,k=0;k<a[i].tmp;j++){
           if(a[i].id[j]){
		        cout<<a[i].id[j]<<' ';
		        k++;
	        }
        }
        cout<<'\n';
    }
    return 0;
}
```
但是 TLE\*3，翻了题解发现思路差不多，可我就是 TLE 了。
### 错解改进：70pts
定义 $now$ 变量以尽量做到提前结束循环模拟。代码如下。但是仍然不够，只能拿 70pts。
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
    int num,cnt,id[1005],tmp;
}a[1005];
bool cmp1(node a,node b){
    return a.cnt>b.cnt;
}
bool cmp2(node a,node b){
    return a.num<b.num;
}
int main(){
    //freopen("club.in","r",stdin);
    //freopen("club.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i].cnt;
        a[i].tmp=a[i].cnt;
        a[i].num=i;
    }
    int now=n;
    for(int i=1;i<=n;++i){
    	  sort(a+1,a+n+1,cmp1);
        if(now<a[1].cnt){
            cout<<"NO SOLUTION";
            return 0;
        }//现有不足需求，无解
        for(int j=2;a[1].cnt>0;++j){
            if(a[j].cnt==0){
                cout<<"NO SOLUTION";
                return 0;
            }
            --a[j].cnt;
            --a[1].cnt;
            a[1].id[a[j].num]=a[j].num;
            a[j].id[a[1].num]=a[1].num;
        }
        --now;//减少一个
    }
    sort(a+1,a+n+1,cmp2);
    cout<<"SOLUTION\n";
    for(int i=1;i<=n;++i){
        for(int j=1,k=0;k<a[i].tmp;++j){
           if(a[i].id[j]){
	           cout<<a[i].id[j]<<' ';
		        ++k;
	        }
        }
        cout<<'\n';
    }
    return 0;
}
```
### 正解（非最优解）：
核心思路在上面的基础上减少排序量，即只排序有变动的部分。而有变动的部分怎么算？定义一个 $out$ 变量，记录这一轮需交朋友数清零的数量，排序时用 `sort(a+1,a+now+out+1)` 即可，$now+out$ 为当前可能出现改变的部分，这样即可通过本题。下面给出 AC 代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
    int num,cnt,id[1005],tmp;
}a[1005];
bool cmp1(node a,node b){
    return a.cnt>b.cnt;
}
bool cmp2(node a,node b){
    return a.num<b.num;
}
int main(){
    //freopen("club.in","r",stdin);
    //freopen("club.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,now;
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i].cnt;
        a[i].tmp=a[i].cnt;
        a[i].num=i;
    }
    for(int i=1,out=0,now=n;i<=n&&now>0;++i){
    	  sort(a+1,a+now+out+1,cmp1);
        out=1;
        if(now<a[1].cnt){
            cout<<"NO SOLUTION\n";
            return 0;
        }
        for(int j=2;a[1].cnt>0;++j){
            if(a[j].cnt==0){
                cout<<"NO SOLUTION\n";
                return 0;
            }
            --a[j].cnt;
            --a[1].cnt;
            if(a[j].cnt==0)--now,++out;
            a[1].id[a[j].num]=a[j].num;
            a[j].id[a[1].num]=a[1].num;
        }
        now--;
    }
    sort(a+1,a+n+1,cmp2);
    cout<<"SOLUTION\n";
    for(int i=1;i<=n;++i){
        for(int j=1,k=0;k<a[i].tmp;++j){
           if(a[i].id[j]){
				   cout<<a[i].id[j]<<' ';
				   ++k;
			   }
        }
        cout<<'\n';
    }
    return 0;
}
```

---

## 作者：Dream_poetry (赞：0)

### 思路：

闲话：图论做多了，第一眼当成图的连通性问题了。

不过仔细看几眼显然是贪心的。

我们考虑每次将整个序列按剩余未匹配数从大到小排序，然后从前往后让他和第一个人匹配，双方互相记作答案。

若一个人应和第一个人匹配，但是他已经没有匹配次数了，则此时无解。

时间复杂度是 $O(n^2\log n)$，显然可以直接碾过去。

### 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
struct node{
	int id;
	int val;	
}a[1005];

inline bool cmp(node x,node y){
	return x.val>y.val;
}

vector<int>ans[1005];


signed main(){
	cin>>n;
	for (int i=1;i<=n;i++){
		cin>>a[i].val;
		a[i].id=i;
	}	
	for (int i=1;i<=n;i++){
		sort(a+1,a+n+1,cmp);
		if (!a[1].val){
			break;
		}
		for (int j=2;j<=a[1].val+1;j++){
			if (!a[j].val){
				cout<<"NO SOLUTION";
				return 0;
			}
			else{
				a[j].val--;
				ans[a[1].id].push_back(a[j].id);
				ans[a[j].id].push_back(a[1].id);
			}
		}
		a[1].val=0;
	}
	cout<<"SOLUTION\n";
	for (int i=1;i<=n;i++){
		sort(ans[i].begin(),ans[i].end());
		for (int j=0;j<ans[i].size();j++){
			cout<<ans[i][j]<<' ';
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：rainygame (赞：0)

简单贪心题，建议降黄。

首先考虑如何**尽可能**地分配，可以发现，我们如果每次都尽量地将两个最多的分配到一起去，一定是最优的。

但是又有一个隐藏限制：一个人不能和同一个人交两次朋友！所以我们每次可以先从大到小排序，然后对于第一个，贪心地给他匹配从第二个到第 $n$ 个人。如果发现匹配不了就直接输出无解。

时间复杂度 $O(n^2 \log n)$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define MAXN 1002

int n, x;
set<int> ans[MAXN];

struct Node{
    int val, ind;
}a[MAXN];

bool cmp(Node a, Node b){
    return a.val > b.val;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i(1); i<=n; ++i){
        cin >> a[i].val;
        a[i].ind = i;
    }

    for (int i(1); i<=n; ++i){
        sort(a+1, a+n+1, cmp);
        for (int j(2); a[1].val; ++j){
            if (!a[j].val){
                cout << "NO SOLUTION";
                return 0;
            }
            --a[j].val;
            --a[1].val;
            ans[a[1].ind].insert(a[j].ind);
            ans[a[j].ind].insert(a[1].ind);
        }
    }

    cout << "SOLUTION\n";
    for (int i(1); i<=n; ++i){
        for (auto j: ans[i]) cout << j << ' ';
        cout << '\n';
    }

    return 0;
}

```


---

