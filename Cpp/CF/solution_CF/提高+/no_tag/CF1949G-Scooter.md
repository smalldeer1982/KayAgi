# Scooter

## 题目描述

捷克技术大学的校园内有 $n$ 栋建筑，编号从 $1$ 到 $n$。每栋建筑可能安排一堂数学课或一堂计算机课，或者没有安排任何课程（不能同时安排两门课）。此外，每栋建筑最多有一位教授，这位教授要么擅长数学，要么擅长计算机科学。

作为 University Express Inc. 的实习生，你的任务是快速将教授送到他们的课堂。公司为你提供了一辆全新的双人滑板车，能载你和最多一位乘客。

开始时，滑板车上只有你。当你到达某栋建筑时，可以接上或送下教授。为了提高效率，你可以选择任意顺序访问这 $n$ 栋建筑中的每一栋建筑，但每栋建筑只能访问一次（你可以选择从哪栋建筑开始）。

在行程结束后，每栋安排了数学课的建筑必须有一位数学教授，每栋安排了计算机课的建筑必须有一位计算机教授。

请设计一条路线，使所有课程得以进行。

## 样例 #1

### 输入

```
3
CM-
-CM```

### 输出

```
7
DRIVE 3
PICKUP
DRIVE 2
DROPOFF
PICKUP
DRIVE 1
DROPOFF```

## 样例 #2

### 输入

```
1
C
C```

### 输出

```
0```

## 样例 #3

### 输入

```
2
-M
MC```

### 输出

```
4
DRIVE 1
PICKUP
DRIVE 2
DROPOFF```

# 题解

## 作者：yingkeqian9217 (赞：1)

直接贪心即可。

首先，如果教学楼已经完成匹配或无限制无教授，显然可以不考虑。

注意到开始一定在没有限制的教学楼接人，然后考虑将人送到哪里。我们贪心地希望能在放人的同时接更多人，否则可以给出如下构造：

```
3
-MCM
M-MC
```

此时如果将 1 和 2 匹配则无法继续匹配，因为并没有接到尽量多的人。另一方面，如果连当前人的对应教学楼都不存在，也可以类似地贪心。

由于每次至少匹配一个人，时间复杂度 $O(n^2)$，可以做到 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define maxn 1010005
#define fi first
#define se second
#define pii pair<int,int>
#define sqr(x) ((x)*(x))
#define pc(x) putchar(x)
#define lowbit(x) ((x)&-(x))
#define conc(x,y,w) son[x][w]=y,fa[y]=x
//#define int long long
inline int min(int x,int y){return x<y?x:y;}
inline int max(int x,int y){return x<y?y:x;}
using namespace std;
typedef long long ll;
mt19937 yrand(time(0));
const int Mod=998244353,inf=1e9,N=1e6,Inv=(Mod+1)/2,B=447;

int n,vis[maxn];
char c1[maxn],c2[maxn];
vector<pair<string,int> >ans;
void solve(){
	cin>>n>>c1>>c2;
	char cur=0;
	while(1){
		for(int i=1;i<=n;i++){
			if(c1[i-1]==c2[i-1]) vis[i]=1;
			if(vis[i]) continue;
			if(c1[i-1]=='-'){
				ans.emplace_back("DRIVE",i);
				ans.emplace_back("PICKUP",0);
				cur=c2[i-1];
				vis[i]=1;
				c2[i-1]='-';
				break;
			}
		}
		if(!cur) break;
		while(cur){
			int fl1=0,fl2=0,fl3=0;
			for(int i=1;i<=n;i++){
				if(c1[i-1]==c2[i-1]) vis[i]=1;
				if(vis[i]) continue;
				if(c1[i-1]=='-') fl3=i;
				if(c1[i-1]!=cur) continue;
				if(c2[i-1]=='-') fl2=i;
				else fl1=i;
			}
			int x=(fl1?fl1:(fl2?fl2:fl3));
			if(!x){cur=0;break;}
			ans.emplace_back("DRIVE",x);
			ans.emplace_back("DROPOFF",0);
			vis[x]=1;
			if(c2[x-1]=='-'){cur=0;break;}
			cur=c2[x-1];
			ans.emplace_back("PICKUP",0); 
		}
	}
	int len=ans.size();
	cout<<len<<'\n';
	for(auto i:ans){
		cout<<i.fi;
		if(i.se) cout<<' '<<i.se;
		cout<<'\n';
	}
}

signed main(){
    solve();
	return 0;
}
```

---

## 作者：江户川·萝卜 (赞：1)

闲话：

- 这题场上首 A 是 55min。

- $O(n)$ 开了 $2000$。

----

首先忽略所有已匹配的教学楼。

我们先抛开每个时刻最多一个教授的限制。

那么可以先贪心地将所有没有课的教学楼中的教授全部接上。

接下来考虑同时有课有教授且不匹配的楼。

因为保证有解且科目数量 $=2$，所以随便做都行。

最后再以任意顺序去只有课没有教授的楼。

现在我们加上最多一个教授的限制。发现教授与其最后所在的楼是一一对应关系，考虑连边，搜一遍就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;string s,t;
vector<int> v[3][3];
vector<int> ans;
inline int get(char x){
    if(x=='-') return 0;
    if(x=='C') return 1;
    return 2;
}
stack<int> fr[3];
int to[2005];
vector<int> zhu;
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n>>s>>t;
    for(int i=1;i<=n;i++){
        int u=get(s[i-1]),v=get(t[i-1]);
        if(u!=v)
        ::v[u][v].push_back(i);
    }
    for(int i:{1,2})
    for(auto x:v[0][i]) fr[i].push(x),zhu.push_back(x);
    if(fr[1].empty()&&!v[2][1].empty()){
        int p=fr[2].top();fr[2].pop();
        int w=v[2][1].back();v[2][1].pop_back();
        to[p]=w;fr[1].push(w);
    }
    if(fr[2].empty()&&!v[1][2].empty()){
        int p=fr[1].top();fr[1].pop();
        int w=v[1][2].back();v[1][2].pop_back();
        to[p]=w;fr[2].push(w);
    }
    while(!v[2][1].empty()||!v[1][2].empty()){
        if(!v[2][1].empty()){
            int p=fr[2].top();fr[2].pop();
            int w=v[2][1].back();v[2][1].pop_back();
            to[p]=w;fr[1].push(w);
        }
        if(!v[1][2].empty()){
            int p=fr[1].top();fr[1].pop();
            int w=v[1][2].back();v[1][2].pop_back();
            to[p]=w;fr[2].push(w);
        }
    }
    for(int i:{1,2})
    for(auto x:v[i][0]){
        int p=fr[i].top();fr[i].pop();
        to[p]=x;
    }
    for(auto x:zhu){
        int p=x;if(to[p])
        ans.push_back(p);
        while(to[p]){
            ans.push_back(-1);
            p=to[p];
            ans.push_back(p);
            ans.push_back(-2);
        }
    }
    cout<<ans.size()<<'\n';
    for(auto x:ans){
        if(x>0) cout<<"DRIVE "<<x<<'\n';
        else if(x==-1) cout<<"PICKUP\n";
        else cout<<"DROPOFF\n";
    }
}
```

---

