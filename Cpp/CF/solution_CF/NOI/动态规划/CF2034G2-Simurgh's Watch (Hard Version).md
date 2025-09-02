# Simurgh's Watch (Hard Version)

## 题目描述

传说中的神鸟 Simurgh 负责守护一片辽阔的土地，她为此招募了 $n$ 名机敏的战士。每位战士都需要在特定的时间段 $[l_i, r_i]$ 内保持警戒，其中 $l_i$ 代表起始时间（包含），$r_i$ 代表结束时间（包含），两者均为正整数。

Simurgh 信任的顾问 Zal 担心，如果多个战士同时在岗且都穿着相同的颜色，那么他们之间可能会难以区分，从而导致混乱。为解决这一问题，在每个整数时刻 $t$，如果有多个战士在岗，必须确保至少有一种颜色仅被其中一个战士穿着。

任务是找出所需的最少颜色数量，并为每个战士的时间段 $[l_i, r_i]$ 分配一种颜色 $c_i$，使得对于包含在至少一个时间段内的每个整数时间点 $t$，总有一种颜色只被一个时间段在$t$时刻使用。

## 说明/提示

我们可以将每位战士的警戒时间段看作 X 轴上的一个区间。

以下示例展示了如何为各个测试用例的区间着色（区域只有在某时间点，仅某种颜色出现时该区域才被染色）：

- 测试用例 1：

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2034G2/a8ca04e863ed852cb4b11c3982c1d5442199b24b.png)

- 测试用例 2：

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2034G2/36f2a5d9878f69668f835178da7df8642bec8342.png)

- 测试用例 3：

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2034G2/75559577acf19732a5a59981d3806145e52c5ed5.png)

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
5
1 4
2 8
3 7
5 10
6 9
5
1 5
2 6
3 7
4 7
6 7
5
4 9
8 17
2 15
12 19
6 13```

### 输出

```
2
1 2 2 1 2
2
1 2 2 2 1
3
1 1 2 3 1```

# 题解

## 作者：IvanZhang2009 (赞：1)

下面是 G2 的题解，对于 G1 可以发现对于非整点只需要检查 $x+0.5$ 的部分，于是把所有坐标乘二然后再做 G2 就对了。

手玩一会儿可以猜测出答案最多是 $3$。我们直接贪心给出一个构造过程：

- 首先将所有线段按左端点排序。考虑取出左端点最靠左的且右端点最大的染上颜色 $1$，称之为特殊线段。例如下图中，标红的 $\tt{A}$ 线段就是特殊线段。

  ![](https://cdn.luogu.com.cn/upload/image_hosting/3ghhg6jr.png)

- 考虑取出所有被特殊线段包含的线段，染上颜色 $2$。例如上图中，线段 $\tt{B,C}$ 会被染上颜色 $2$。

- 考虑剩下的线段，如果所有线段都在特殊线段右侧，重复这个操作即可。否则考虑所有左端点在特殊线段区间内的线段，取出**右端点最靠右**的线段，染上颜色 $3$。上图中即为线段 $\tt D$，并令此为特殊线段。

- 一直重复以上过程，选取特殊线段，分别染上 $1,3,1\dots$ 的颜色，其余染上颜色 $2$。对于上图，一种合理的染色就是 $1,2,2,3,2$。

实际上这是手玩的容易构造的结果。更直观的解释就是找出若干左右端点均递增的、能覆盖所有区间的线段作为特殊线段，题目中的“唯一颜色”也就是由这些线段来的。由构造过程容易维护出这一过程，时间复杂度最多 $O(n\log n)$。

注意到答案为 $1$ 的情况是显然的：所有线段两两不交，排序后判断即可。于是问题变成是否存在答案为 $2$。

我们仿照答案为 $3$ 时的构造，尝试找出所有**作为唯一颜色出现**的线段和对应的出现区间。可以发现每个线段作为唯一颜色的坐标如果存在则必然形如一段区间，否则如果有两段分离的，中间肯定也可以作为唯一颜色（把被中间段包含的所有同色的线段改成异色即可）。

在确定这是一段区间之后，贪心考虑一定是区间越长越好。我们不妨考虑最小化区间左端点的位置。设计 dp：$f_i$ 表示第 $i$ 条线段作为唯一颜色出现的区间左端点最小值。

考虑转移，也就是两个特殊线段 $[l_1,r_1],[l_2,r_2]$ 的“交接”。先进行离散化，让所有坐标都至少出现两个线段，方便转移的讨论。最简单的情况是 $r_1+1=l_2$，此时把这两条线段染成同色直接满足了所有要求，把此区间内所有其余线段染成异色即可。转移为如果 $f_1$ 存在则令 $f_2=l_2$。

考虑两个特殊线段相交的情况，可以发现此时两条线段颜色不相同，设一个分界点 $x$ 满足 $x$ 左侧（包含 $x$）和右侧（不包含 $x$）分别是这两条线段作为唯一颜色。此时交接的条件就是，不存在别的线段 $[L,R]$ 满足 $L\le x<R$。找到任意符合的 $x$ 令 $f_2=x$ 即可。

转移的方式必须采用按坐标递增的方式，此时不会出现后效性。设此时转移分界点为 $x$，对于第一种转移，我们找到所有右端点为 $x$ 的线段，如果存在一个有值，则此时所有左端点为 $x+1$ 的线段都可以取到最优。对于第二种则麻烦一些。观察性质发现穿过 $x,x+1$ 两点的线段恰有两条，于是一个坐标处最多只有两种转移（注意到两条线段需要互相转移）。暴力转移即可。关于如何找到这两条线段，我们提前预处理，用扫描线的方式枚举坐标，用 `set` 维护所有经过这个坐标的线段，如果恰有两条则记录下来即可。

另一个难写的点是构造方案。我们记录转移的来源即可，根据转移的类别还原其颜色。对于普通线段，注意到它一定被某个特殊区间的颜色段完全包含，暴力二分找出即可。时间复杂度 $O(n\log n)$。

代码的离散化写的很脑抽啊。其实不很难写。

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define all(v) v.begin(),v.end()
#define pb push_back
#define REP(i,b,e) for(int i=(b);i<(int)(e);++i)
#define over(x) {cout<<(x)<<"\n";return;}
#define lbd(v,x) lower_bound(all(v),x)-v.begin()
using namespace std;
struct segment{
	int l,r,id;
	bool operator <(segment a){return l==a.l? r<a.r:l<a.l;}
}a[200005];
int n;
int solve(){
	vector<int>v;
	REP(i,0,n)v.pb(a[i].l),v.pb(a[i].l-1),v.pb(a[i].r),v.pb(a[i].r+1);
	sort(all(v));v.erase(unique(v.begin(),v.end()),v.end());
	int m=v.size();
	vector<int>s(m+1,0);
	REP(i,0,n)++s[lbd(v,a[i].l)],--s[lbd(v,a[i].r)+1];
	REP(i,0,m)s[i+1]+=s[i];
	vector<int>v2;
	REP(i,0,m)if(s[i])v2.pb(v[i]);
	REP(i,0,n)a[i].l=lbd(v2,a[i].l),a[i].r=lbd(v2,a[i].r);
	return v2.size();
}
vector<int>add[800005],del[800005],oc[800005];
vector<pii>tran[800005];
int from[800005],dp[800005];
int vis[800005];
int ans[800005];
void Main() {
	cin>>n;
	REP(i,0,n)cin>>a[i].l>>a[i].r,a[i].id=i;
	sort(a,a+n);
	bool F=1;
	REP(i,1,n)if(a[i-1].r>=a[i].l)F=0;
	if(F){
		cout<<1<<endl;
		REP(i,0,n)cout<<1<<' ';
		cout<<endl;
		return;
	}
	int m=solve();
	REP(i,0,m)oc[i].clear(),add[i].clear(),del[i].clear(),tran[i].clear();
	REP(i,0,n)add[a[i].l].pb(i),del[a[i].r].pb(i);
    set<int>st;
    REP(i,0,m){
        for(auto j:add[i])st.insert(j);
		for(auto j:del[i])st.erase(st.find(j));
        if(st.size()<=2){
            for(auto j:st)oc[i].pb(j);
            if(oc[i].size()==2){
                int x=oc[i][0],y=oc[i][1];
                tran[i].pb({x,y});tran[i].pb({y,x});
            }
        }
    }
    REP(i,0,n)from[i]=-1,vis[i]=0,dp[i]=a[i].l? -1:0;
    REP(i,0,n)if(oc[a[i].r].size()==1){
        int r=a[i].r,x=oc[r][0];
        tran[r].pb({i,x});
    }
    REP(i,0,n)if(a[i].l&&oc[a[i].l-1].size()==1){
        int r=a[i].l-1,x=oc[r][0];
        tran[r].pb({x,i});
    }
    REP(i,0,m-1){
        int ok=-1;
        for(auto j:del[i])if(dp[j]!=-1)ok=j;
        if(ok!=-1){
            for(auto j:add[i+1])from[j]=ok,dp[j]=i+1;
        }
        for(auto [x,y]:tran[i]){
            if(dp[x]!=-1&&dp[x]<=i){
                if(dp[y]==-1||dp[y]>i)dp[y]=i+1,from[y]=x;
            }
        }
    }
    int f=-1;
    REP(i,0,n)if(dp[i]!=-1&&a[i].r==m-1)f=i;
    if(f!=-1){
        REP(i,0,n)ans[i]=-1;
        ans[a[f].id]=0;
        vector<pii>v;
        v.pb({dp[f],0});
        while(a[f].l){
            int x=from[f];
            if(a[x].r+1==a[f].l)ans[a[x].id]=ans[a[f].id];
            else ans[a[x].id]=ans[a[f].id]^1;
            f=x;v.pb({dp[f],ans[a[f].id]});
        }
        reverse(all(v));
        REP(i,0,n)if(ans[a[i].id]==-1){
            auto it=upper_bound(all(v),pii{a[i].l,2});--it;
            ans[a[i].id]=!(it->second);
        }
        cout<<2<<endl;
        REP(i,0,n)cout<<ans[i]+1<<' ';
        cout<<endl;
    }else{
        set<pii>s;
        int c1=0,cur=0;
        while(s.size()||cur<n){
            if(!s.size()){
                int x=a[cur].l;
                while(cur<n&&a[cur].l==x)s.insert({a[cur].r,a[cur].id}),++cur;
            }
            auto it=s.end();--it;
            auto [y,x]=*it;s.erase(it);
            ans[x]=c1;
            while(cur<n&&a[cur].l<=y)s.insert({a[cur].r,a[cur].id}),++cur;
            while(s.size()&&s.begin()->first<=y){
                auto [X,Y]=*s.begin();
                ans[Y]=2;
                s.erase(s.begin());
            }
            c1^=1;
        }
        cout<<3<<endl;
        REP(i,0,n)cout<<ans[i]+1<<' ';
        cout<<endl;
    }
}
signed main(){
    int tc;cin>>tc;
    while(tc--)Main();
    return 0;
}
```

---

