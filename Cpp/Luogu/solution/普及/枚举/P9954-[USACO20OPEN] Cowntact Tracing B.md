# [USACO20OPEN] Cowntact Tracing B

## 题目描述

由于高传染性的牛传染病 COWVID-19 的爆发，Farmer John 非常担忧他的奶牛们（编号为 $1\ldots N$）的健康。

最近，Farmer John 对他的所有奶牛进行了检测，发现有一部分奶牛对该疾病的检测结果呈阳性。利用牛棚内的视频监控，他得以查看最近的奶牛之间的互动行为，结果发现奶牛们互相打招呼时，她们会握蹄，不幸的是这是一种会将疾病从一头奶牛传播给另一头奶牛的行为。Farmer John 汇总了一个添加了时间戳的清单，每条数据的形式为 $(t,x,y)$，表示在时间 $t$，奶牛 $x$ 与奶牛 $y$ 握了蹄。Farmer John 同时还知道以下信息：

（一）他的农场上恰有一头奶牛最初带有携带疾病（我们将这头奶牛称为“零号病人”）。

（二）一旦一头奶牛被感染，她会在接下来的 $K$ 次握蹄中传染疾病（可能会与同一头奶牛握蹄多次）。握蹄 $K$ 次后，她不再在此后的握蹄中传染疾病（因为此时她意识到了她会传染疾病，于是会仔细地洗蹄）。

（三）一旦一头奶牛被感染，她会持续处于被感染状态。

不幸的是，Farmer John 不知道他的 $N$ 头奶牛中的哪一头是零号病人，也不知道 $K$ 的值！基于他的数据，请帮助他缩小这些未知量的范围。保证至少有一种可能的情况。 

## 说明/提示

### 样例解释 1

唯一可能是零号病人的是奶牛 $1$。对于所有的 $K>0$，奶牛 $1$ 在时刻 $7$ 感染奶牛 $2$，而奶牛 $3$ 和奶牛 $4$ 均不会被感染。 

## 样例 #1

### 输入

```
4 3
1100
7 1 2
5 2 3
6 2 4```

### 输出

```
1 1 Infinity```

# 题解

## 作者：mengleo (赞：4)

# [USACO20OPEN] Cowntact Tracing B 题解
## 思路
既然 $N \leq 100$，$T \leq 250$，那就有一种最暴力的解法：
    
1. 将时间戳以 $t$ 为关键字从小到大排序。
2. 枚举零号病人 $z$（$[1, N]$），对于每个零号病人，枚举 $k$（$[1, \color{#900021}{T + 1}\color{black}]$）。
3. 对于每对 $z, k$ 顺序遍历时间戳数组，暴力模拟感染。
4. 如果感染结果与输入的字符串一致，那么可能为零号病人的奶牛数量+1，并更新 $k$ 的上下限。
5. 输出，如果 $k$ 的上限是 $T + 1$ 就输出`Infinity`，否则正常输出。

时间复杂度为 $\mathcal{O}(NT^2)$。

## Code
```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

struct lst_t
{
    int t, x, y;
} lst[255];
int n, t, cnt, mx, mn = LLONG_MAX;
string s;

bool cmp(lst_t x, lst_t y)
{
    return x.t < y.t;
}

signed main()
{
    cin >> n >> t >> s;
    for(int i = 1; i <= t; i++)
    {
        cin >> lst[i].t >> lst[i].x >> lst[i].y;
    }
    sort(lst + 1, lst + 1 + t, cmp);
    for(int z = 1; z <= n; z++)
    {
        bool f = 0;
        for(int k = 0; k <= t + 1; k++)
        {
            bool f2 = 1;
            int cs[n + 5] = {};
            memset(cs, -1, sizeof(cs));
            cs[z] = k;
            for(int i = 1; i <= t; i++)
            {
                if(cs[lst[i].x] == -1 && cs[lst[i].y] > 0)
                {
                    cs[lst[i].y]--;
                    cs[lst[i].x] = k;
                }
                else if(cs[lst[i].y] == -1 && cs[lst[i].x] > 0)
                {
                    cs[lst[i].x]--;
                    cs[lst[i].y] = k;
                }
                else if(cs[lst[i].x] >= 0 && cs[lst[i].y] >= 0)
                {
                    cs[lst[i].x] = max(0ll, cs[lst[i].x] - 1);
                    cs[lst[i].y] = max(0ll, cs[lst[i].y] - 1);
                }
            }
            for(int i = 1; i <= n; i++)
            {
                if((s[i - 1] == '1' && cs[i] == -1) || (s[i - 1] == '0' && cs[i] != -1))
                {
                    f2 = 0;
                }
            }
            if(f2)
            {
                mx = max(mx, k);
                mn = min(mn, k);
                f = 1;
            }
        }
        cnt += f;
    }
    cout << cnt << " " << mn;
    if(mx == t + 1)
    {
        cout << " Infinity";
    }
    else
    {
        cout << " " << mx;
    }
    
    return 0;
}
```

---

## 作者：huhangqi (赞：1)

首先观察数据范围，发现 $N$ 和 $T$ 都很小，那么就可以直接枚举计算答案了。

将几次握手按照时间排序，首先枚举零号病人是哪一只奶牛，再枚举 $K$ 的值。

如果你把状态设置为 $0$ 表示没有感染，其他数字表示可以传染的人数，那么需要特别判断一下 $K$ 为 $0$ 的情况。

注意每次握手都要将这只奶牛的可传染次数减一。

枚举完成后进行模拟，统计可以作为零号病人的有那几只奶牛，再取 $K$ 的最小值和最大值即可。

如何判断有无上限？

如果 $T$ 次可行，那么每一次握手都必定传染，那么加上几次都必定可行，所以若最大值为 $T$ 时，无上界。

模拟用时 $O(T+N)$

代码用时 $O(NT(N+T))$

### *Code* ###

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,t,vis[10005],f[10005],ans,ans2=1e9,ans3,to[10005];
struct P{
	int t,x,y;
}a[3005];
bool cmp(P a,P b){
	return a.t<b.t;
}
signed main(){
    cin>>n>>t;
    char c;
    for(int i=1;i<=n;i++){
    	cin>>c;
    	vis[i]=c-48;
	}
	for(int i=1;i<=t;i++){
		cin>>a[i].t>>a[i].x>>a[i].y; 
	}
	sort(a+1,a+t+1,cmp);
	for(int i=1;i<=n;i++){
		memset(f,0,sizeof(f));
		f[i]=1;
		bool fl=false;
		for(int k=1;k<=n;k++){
			if(f[k]&&!vis[k]||!f[k]&&vis[k]){
				fl=true;
				break;
			}
		}
		if(!fl){
			if(!to[i]){
				to[i]=1;
				ans++;
			}
			ans2=min(ans2,0ll);
			ans3=max(ans3,0ll);
		}
		for(int j=1;j<=t;j++){
			memset(f,0,sizeof(f));
			f[i]=j;
			for(int k=1;k<=t;k++){
				int x=f[a[k].x],y=f[a[k].y];
				if(x>0){
					f[a[k].x]--;
					if(!f[a[k].x])f[a[k].x]=-1;
					if(y==0)f[a[k].y]=j;
				}
				if(y>0){
					f[a[k].y]--;
					if(!f[a[k].y])f[a[k].y]=-1;
					if(x==0)f[a[k].x]=j;
				}
			}
			bool fl=false;
			for(int k=1;k<=n;k++){
				if(f[k]&&!vis[k]||!f[k]&&vis[k]){
					fl=true;
					break;
				}
			}
			if(!fl){
				if(!to[i]){
					to[i]=1;
					ans++;
				}
				ans2=min(ans2,j);
				ans3=max(ans3,j);
			}
		}
	}
	cout<<ans<<' '<<ans2;
	if(ans3!=t)cout<<' '<<ans3;
	else cout<<' '<<"Infinity";
    return 0;
}
``````

---

## 作者：内拉组里 (赞：0)

# Thoughts :

> 这题一开始想复杂了，其实直接枚举デス～
>
> $ \Theta (N) $ 枚举零号病人，$ \Theta (T) $ 枚举 $ k $ , $ \Theta (T) $ 模拟过程, $ \Theta (N) $ 检查解的合法性。
>
> 总时间复杂度 $ \Theta (NT(N + T)) $ 足矣。

# Details :

> - 模拟时要先计算感染次数再判断到达 $ k $ 与否。
>
>   还有很多细节不好总结, 具体可以拿以下代码~~手动~~对拍。
>
>   ```cpp
>   inline int check (int zero, int k)
>   {
>   	memset (vis, 0, sizeof vis);
>   	memset (infect, 0, sizeof infect);
>   	infect[zero] = 1;
>   	for (int i = 1; i <= t; i++)
>   	{
>   		int x = r[i].x;
>   		int y = r[i].y;
>   		if (infect[x]) vis[x]++;
>   		if (infect[y]) vis[y]++;
>   		if (vis[x] > k || vis[y] > k) continue;
>   		if (infect[x] || infect[y]) infect[x] = infect[y] = 1;
>   	}
>   	for (int i = 1; i <= n; i++)
>   	{
>   		if (infect[i] ^ '0' != str[i])
>               return 0;
>   	}
>   	return 1;
>   }
>   ```

---

## 作者：XiaoWhy (赞：0)

数据量小，我们就可以考虑暴力枚举哪一个是零号病人，然后再暴力枚举 $K$ 的大小，然后去模拟 $t$ 次操作。

对于合法的零号病人情况，$ans+1$。

对于合法的 $K$，下限取 $\min$，上限取 $\max$ 即可。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=255;
int n,t,ans,mi,mx;
string s;
struct node{
	int t,x,y;
};
node tr[N];
bool cmp(node a,node b){return a.t<b.t;}
bool st[N];//记录当前牛是否已经被传染
int cnt[N];//记录每个牛当前还能传染多少次
void check(int x){
	bool yes=false;//记录x能否成为零号病人
	for(int k=0;k<=t+1;k++){//枚举可能的k
		memset(st,false,sizeof st);
		memset(cnt,0,sizeof cnt);
		cnt[x]=k,st[x]=true;//零号病人
		bool ok=true;//判断是否合法
		for(int i=1;i<=t;i++){//模拟操作
			int x=tr[i].x,y=tr[i].y;
			if(cnt[x]>0||cnt[y]>0){//当前情况会发生传染
				cnt[x]--,cnt[y]--;
				if(s[x]=='0'||s[y]=='0'){//那么就不合法
					ok=false;
					break;
				}else{
					if(!st[x]) st[x]=true,cnt[x]=k;//如果没感染,就标记,cnt[x]赋值
					if(!st[y]) st[y]=true,cnt[y]=k;
				}
			}
		}
		//最后判断与原式子是否对应
		for(int i=1;i<=n;i++){
			if(st[i]==true&&s[i]=='0') ok=false;
			if(st[i]==false&&s[i]=='1') ok=false;
		}
		if(ok) mi=min(mi,k),mx=max(mx,k),yes=true;
	}
	if(yes) ans++;
}
int main(){
	mi=1e9,mx=0;
	cin>>n>>t>>s;
	s=' '+s;//让下标从1开始,方便后面操作
	for(int i=1;i<=t;i++) cin>>tr[i].t>>tr[i].x>>tr[i].y;
	sort(tr+1,tr+t+1,cmp);//根据时间从小到大
	for(int i=1;i<=n;i++) if(s[i]=='1') check(i);//枚举每一头牛作为零号病人
	cout<<ans<<" "<<mi<<" ";
	if(mx==t+1) cout<<"Infinity";
	else cout<<mx;
	return 0;
}

---

## 作者：cly312 (赞：0)

考虑暴力。

枚举让每头牛都当一次“零号病人”和 $K$ 的所有组合，模拟感染的过程，检查得出的病人是否和给出的一样即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
bool infectedd[101];
int N,cowx[251],cowy[251];
bool check(int patient_zero,int K){
	bool infected[101]={false};
	int num[101]={0};
	infected[patient_zero]=true;
	for(int t=0;t<=250;t++){
		int x=cowx[t],y=cowy[t];
		if(x>0){
			if(infected[x]) num[x]++;
			if(infected[y]) num[y]++;
			if(num[x]<=K&&infected[x]) infected[y]=true;
			if(num[y]<=K&&infected[y]) infected[x]=true;
		}
	}
	for(int i=1;i<=N;i++)
		if(infected[i]!=infectedd[i]) return false;
	return true;
}

int main(){
	int T,t,x,y;
	string s;
	cin>>N>>T>>s;
	for(int i=1;i<=N;i++)
		infectedd[i]=s[i-1]=='1';
	for(int i=0;i<T;i++){
		cin>>t>>x>>y;
		cowx[t]=x;
		cowy[t]=y;
	}
	bool pi[101]={false};
	bool pk[252]={false};
	for(int i=1;i<=N;i++)
		for(int K=0;K<=251;K++)
			if(check(i,K))
				pi[i]=true,pk[K]=true;

	int lower_K=251,upper_K=0,pz=0;
	for(int K=0;K<=251;K++) if(pk[K]) upper_K=K;
	for(int K=251;K>=0;K--) if(pk[K]) lower_K=K;
	for(int i=1;i<=N;i++) if(pi[i]) pz++;
	cout<<pz<<" "<<lower_K<<" ";
	if(upper_K==251) cout<<"Infinity\n";
	else cout<<upper_K<<"\n";
	return 0;
}
```

---

