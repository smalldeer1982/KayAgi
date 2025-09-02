# [IOI 2009] Garage

## 题目背景

IOI2009 D2T1

## 题目描述

一个停车场有 $N$ 个停车位，依次编号为 $1$ 到 $N$。每天早上，停车场的所有停车位都是空的。当一辆车到达停车场时，服务员检查是否有空的停车位。如果没有，则这辆车将在入口处等待，直到有新的停车位。如果有，则这辆车将停在编号最小的空的停车位上。如果多辆车在入口处等待，则它们会按照到达的顺序排成队列，当出现空的停车位时，队列中的第一辆车（最早到达的车辆）将停在该停车位上。

每辆车的停车费是它的重量乘以对应停车位的特定比率，和它在停车场停了多久无关。

停车场管理员得知今天将有 $M$ 辆车前来停车，以及它们到达和离开的顺序。帮他计算今天的收入。

**任务**：编写一个程序，给定每个停车位的特定比率，每辆车的重量和所有车辆到达和离开的顺序，求出车库的总收入。

## 说明/提示

### 样例解释

- 样例 1：
  - 车辆 $3$ 停在车位 $1$，支付 $300\times 2 = 600$ 美元。
  - 车辆 $2$ 停在车位 $2$，支付 $100\times 3 = 300$ 美元。
  - 车辆 $1$ 停在车位 $1$（车辆 $3$ 空出的停车位），支付 $200\times 2 = 400$ 美元。
  - 车辆 $4$ 停在车位 $3$，支付 $800\times 5 = 4000$ 美元。

- 样例 2：
  - 车辆 $3$ 停在车位 $1$，支付 $1000\times 5 = 5000$ 美元。
  - 车辆 $1$ 停在车位 $2$，支付 $100\times 2 = 200$ 美元。
  - 车辆 $2$ 到达并在入口处等待。
  - 车辆 $4$ 到达并在入口处等待，排在车辆 $2$ 之后。
  - 当车辆 $1$ 离开时，车辆 $2$ 停在空出的车位 $2$，支付 $500\times 2 = 1000$ 美元。
  - 当车辆 $3$ 离开时，车辆 $4$ 停在空出的车位 $1$，支付 $2000\times 5 = 10000$ 美元。

### 数据范围与约定

- 对于 $40\%$ 的数据，没有车辆会在停车场等待。
- 对于 $100\%$ 的数据，$1\leq N\leq 100$，$1\leq M\leq 2000$，$1\leq R_s\leq 100$，$1\leq W_k\leq 10 ^ 4$。

## 样例 #1

### 输入

```
3 4
2
3
5
200
100
300
800
3
2
-3
1
4
-4
-2
-1
```

### 输出

```
5300
```

## 样例 #2

### 输入

```
2 4
5
2
100
500
1000
2000
3
1
2
4
-1
-3
-2
-4
```

### 输出

```
16200```

# 题解

## 作者：Lovely_Elaina (赞：6)

妥妥暴力模拟题。

### 思路

用两个数组表示每台车的重量和每个停车位的收费标准。

用一个数组表示各个车位停着哪辆车，如果没有为 $0$。

用一个队列表示待进的车辆，写一个函数用来更新这个队列，每次输入的时候就更新一下。

入车和出车都写一个函数，暴力就行了。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 105;
const int M = 2005;


int b[N],m,n,a[M];
int tol; // 车的总数
int is_b[N];
long long sum;

queue<int > q; // 待入车辆
```

- Zou doesn't like Chen anymore.

```cpp
/*void print(){
    for(int i = 1; i <= n; i++){
        cout << is_b[i] << " ";
    }cout << endl;
}*/

void wait();
void enter(int x);
void leave(int x);

void wait(){
    if(tol == n) return ;
    while(tol < n && !q.empty()){
        enter(q.front());
        q.pop();
    }
}

void enter(int x){
    if(tol == n){
        if(x != q.front())
            q.push(x);
        return;
    }
    
    int i = 1;
    while(is_b[i]) i++;
    is_b[i] = x;
    //print();
    sum += (b[i]*a[x]);
    tol++;
}

void leave(int x){
    int i = 1;
    while(is_b[i] != x) i++;
    is_b[i] = 0;
    tol--;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        cin >> b[i];
    }
    for(int i = 1; i <= m; i++){
        cin >> a[i];
    }
    
    int x;
    m *= 2;
    while(m--){
        wait();
        cin >> x;
        if(x > 0) enter(x);
        else leave(-x);
    }
    
    cout << sum << endl;
    
    return 0;
}
```

---

## 作者：_Haoomff_ (赞：4)

## 思路
按照题意模拟即可。

准备工作：建一个队列用来记录当前等待的车，一个数组记录某辆车在停车场中的位置，一个变量记录当前停车场中车数。

+ 有车要入
1. 停车场中无空位，将这辆车加入等待队列；
2. 停车场中有空位，计算费用，将该车停的位置标记为已有车，当前停车场中车数 $+1$。
+ 有车要出
1. 有等待车辆（即队列非空），将队列中第一辆车停入出去的车的位置，出队，计算费用；
2. 无等待车辆（即队列为空），将该车停的位置标记为无车，当前停车场中车数 $-1$。

判断当前停车场有无车位的标准即为：当前停车场中车数是否等于停车场车位数 $n$。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,r[105],w[20005];
int ans;//记录收入
int cnt;//记录当前停车场车数
int y[105];//记录某辆车在停车场中的位置 
queue<int> q;//当前等待的车 
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i)cin>>r[i];
	for(int i=1;i<=m;++i)cin>>w[i];
	for(int i=1;i<=m*2;++i){
		int a;
		cin>>a;
		if(a>0){//有车要开入 
			if(cnt<n){//有空位 
				++cnt;//当前车数+1 
				for(int i=1;i<=n;++i)
					if(y[i]==0){//空着的编号最小的停车位 
						ans+=r[i]*w[a];//计算费用 
						y[i]=a;//停了i号车位
						break;
					} 
			}
			else q.push(a);
		}
		else{//有车要开出 
			a=-a;
			for(int i=1;i<=n;++i)
				if(y[i]==a){//该车停的车位 
					y[i]=0;//车开出
					--cnt;//当前车数-1
					if(!q.empty()){
						int b=q.front();
						q.pop();
						++cnt;//新进入一辆车，车数+1 
						ans+=r[i]*w[b];//计算新进入的车的费用 
						y[i]=b;//停了i号车位
					}
					break; 
				}
		} 
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：Loser_Syx (赞：3)

## 思路

对于每辆车的来临有两种选择，第一种是当停车位未满时，直接让它停进去，第二种是停车位满了，那就把它塞进 `queue` 里去排队等车位。

然而车离开时也会有两种选择，第一种是 `queue` 中无车等待，直接修改该停车位的状态并离开，第二种是 `queue` 中有车等待，那就直接让队首停进这个位置中。

然后对于每次停车计算总费用。

## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#define int long long
#define f(X, Y, Z) for(int i = X; i <= Y; i += Z)
#define F(X, Y, Z) for(int i = X; i >= Y; i -= Z)
#define debug puts("I AK IOI!")
using namespace std;
int r[2010], w[2010], place[2010];
queue<int> q;
main(){
	int n, m, count = 0, money = 0;
	scanf("%lld %lld", &n, &m);
	f(1, n, 1){
		scanf("%lld", &r[i]);
	}
	f(1, m, 1){
		scanf("%lld", &w[i]);
	}
	m *= 2;
	f(1, m, 1){
		int car;
		scanf("%lld", &car);
		if(car < 0){//离开停车场 
			int i = 1;
			while(place[i] != (-car)){//寻找该车停的位置 
				i++;
			}
			//更新改车位的状态 
			count--;
			place[i] = 0;
			if(!q.empty()){//如果有车在排队 
				//让最先排队的车停 
				int now_car = q.front();
				q.pop();//移出队列
				place[i] = now_car;//更新该停车位的车 
				money += r[i] * w[now_car];//计算总钱数 
				count++;
			}
		}else{
			if(count >= n){//如果停车位满了 
				q.push(car);
			}else{
				int i = 1;
				while(place[i] != 0){
					i++;
				}
				place[i] = car;
				money += r[i] * w[car];
				count++;
			}
		}
	}
	printf("%lld\n", money);
	return 0;
}
```

---

## 作者：tbdsh (赞：3)

$\color{white}\text{IOI 的题目好水啊}$
# 题意简述
[题目传送门](/problem/p9115)

[更好的阅读体验](/blog/tianbiandeshenghuo11/solution-p9115)

有 $N$ 个车位，$M$ 辆车。

当一辆车先来时，如果没有车位就得等，否则就从小到大找第一个空车位入位。

同时，每个车的重量是 $W_i$，每个车位的收费率是 $R_i$。

如果车辆 $i$ 停在了车位 $j$，那么他就得支付 $W_i\times R_j$ 元。

求所有车总共需要支付多少钱。

# 分析
用 `set` 记录空着的车位，`queue` 记录在等待队列中的车辆，$jf_i$ 记录第 $i$ 辆车停的车位。

当一个车来到车场，就扔进队列；它出厂，就结算停车费，然后将这个车位标记为可以使用。

最后输出答案即可。

# Code
```cpp
#include<bits/stdc++.h>

using namespace std;
int n, m, ans, r[105], w[3005], jf[3005];
set<int> a;
queue<int> b;
int main(){
  cin >> n >> m;
  for (int i = 1; i <= n; i++){
    cin >> r[i];
    a.insert(i);//加入空车位。
  }
  for (int i = 1; i <= m; i++){
    cin >> w[i];
  }
  m *= 2;
  while (m--){
    int x;
    cin >> x;
    if (x > 0){
      b.push(x);
    }else {
      ans += r[jf[abs(x)]] * w[abs(x)];//计算停车费。
      a.insert(jf[abs(x)]);//将车位标记为可使用
    }
    while (b.size() && a.size()){//当有空车位且队列中有车在等待时就进行操作。
      jf[b.front()] = *a.begin();
      b.pop(), a.erase(a.begin());
    }
  }
  cout << ans;
  return 0;
}
```

---

## 作者：yangmingshuo114514 (赞：2)

模拟即可。建一个队列存等待的车的编号，开一个数组存车在停车场里的位置。

一辆车到达有两种情况：

1.停车场已满，此时将这辆车的编号加入队列。

2.停车场未满，此时直接暴力求出编号最小的空的停车位，标记进入停车位，记录费用。

一个车离开有两种情况：

1.队列不为空，标记离开后将队列里的第一辆车出来，标记进入停车位，记录费用。

2.队列为空。直接标记离开。

我们用 $cnt$ 来表示当前停车场的车数，如果有一辆车进入停车位就加 $1$ ，如果有一辆车离开停车位就减 $1$ 。当 $cnt=n$ 时停车场就满了，否则没满。

code:
```cpp
#include<cstdio>
#include<queue>
using namespace std;
queue<int>Q;//存等待的车的编号
int n,m,r[105],w[2005],c[2005],cnt,x,cost;//c数组存车在停车场里的位置
bool b[105];//停车位是否有车
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&r[i]);
	for(int i=1;i<=m;i++) scanf("%d",&w[i]);
	for(int i=1;i<=m*2;i++){
		scanf("%d",&x);
		if(x>0){//到达
			if(cnt==n) Q.push(x);//停车场已满，加入队列
			else{//停车场不满
				++cnt;
				int k=1;
				while(b[k]) ++k;//暴力求出编号最小的空的停车位
				b[k]=1;//标记有车
				c[x]=k;//标记编号为x的车停在编号为k的停车位上
				cost+=w[x]*r[k];//记录费用
			}
		}
		else{//离开
			x=-x;
			--cnt;
			b[c[x]]=0;//标记没车
			if(!Q.empty()){//队列不为空
				++cnt;
				b[c[x]]=1;//标记有车
				c[Q.front()]=c[x];//队列的一辆车停在离开的那辆车的停车位上
				cost+=w[Q.front()]*r[c[x]];//记录费用
				Q.pop();//踢出队列
			}
		}
	}
	printf("%d",cost);
	return 0;
}

---

## 作者：FurnaceBridge (赞：1)

本人的第一篇题解。

#### 分析

[题目传送门](https://www.luogu.com.cn/problem/P9115)

由于本题数据较小，使用简单的模拟即可通过。

* 有车辆进入

直接暴力遍历所有车位即可，有空位就可以直接停进去，没有空位就加入等待队列中。等待队列可以直接用 queue 实现。

* 有车辆离开

可以发现，如果车辆离开时有别的车在等待，队首的车就可以直接补上去。如果没有车等待，后来的车（如果有）也可以发现这个空位并停上。

时间复杂度： $ \mathcal{O}(nm) $ 。

#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define FOR(i,j,k) for(int i=j;i<=k;i++)
#define RFOR(i,j,k) for(int i=j;i>=k;i--)
int n,m;
int p[105],w[2005];//p即为题目中的R
int ans;
int used[105],pos[2005];//used[i]表示哪辆车停在了车位i上；pos[i]表示第i辆车停在了哪个车位上。
queue<int> q;
int main(){
	cin>>n>>m;
	FOR(i,1,n){
		cin>>p[i];
	}
	FOR(i,1,m){
		cin>>w[i];
	}
	FOR(i,1,2*m){
		int t;
		cin>>t;
		if(t>0){//车辆进入
			bool flag=true;
			FOR(j,1,n){//找空位
				if(!used[j]){
					ans+=p[j]*w[t];
					used[j]=t;
					pos[t]=j;
					flag=false;
					break;
				}
			}
			if(flag){//找不到空位则加入等待队列
				q.push(t);
			}
		}
		else{//车辆离开
			t=-t;
			used[pos[t]]=0;
			if(!q.empty()){//如果队列中有车，队首的车就可以直接补上这一个空位
				int h=q.front();
				q.pop();
				used[pos[t]]=h;
				pos[h]=pos[t];
				ans+=p[pos[h]]*w[h];
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：zhuweiqi (赞：1)

### 前言：

看到这个题目的第一眼，我脑子里第一反应就是去看数据范围，结果呢，这个数据范围小得很！AC 之后又发现是新题，还没几个人通过 ~~（心想着又能水一篇题解了）~~，因此就诞生了这篇题解……

### 思路：

模拟。

我们用一个数组来记录每个停车位停的是哪辆车，每来一个车，我们先查询有没有空余车位，在此过程中我们可以用一个变量优化查询的时间，如果有空余车位，则输出其中编号最小的车位，如果没有就将它放入队列之中，等到下一辆车离开停车场的时候，如果队列里有车，就让排在队首的车停进那辆离开的车的位置上，最后输出答案即可。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int r[102],w[2002];
int a[102];
queue<int> q;
int main(){
	int n,m,x,ans=0,cnt=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&r[i]);
	for(int i=1;i<=m;i++) scanf("%d",&w[i]);
	for(int i=1;i<=(m<<1);i++){
		scanf("%d",&x);
		if(x<0){
			x=-x;
			for(int i=1;;i++){
				if(a[i]==x){
					a[i]=0;
					cnt--;
					if(!q.empty()){
						int s=q.front();q.pop();
						ans+=r[i]*w[s];
						a[i]=s;
						cnt++; 
					}
					break;
				}
			}
		}
		else {
			if(cnt<n){
				cnt++;
				for(int i=1;i<=n;i++){
					if(a[i]==0){
						ans+=r[i]*w[x];
						a[i]=x;
						break;
					}
				}
			}
			else q.push(x);
		}
	}
	printf("%d",ans);
	return 0;
}
```

---

