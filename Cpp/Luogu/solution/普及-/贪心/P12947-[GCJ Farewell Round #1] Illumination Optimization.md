# [GCJ Farewell Round #1] Illumination Optimization

## 题目描述

**Onyaomale** 正在领导一个项目，将高速公路沿线路灯的白炽灯泡更换为更节能且亮度更高的 LED 灯泡。她已将所有旧白炽灯泡拆除，现在专注于安装新的 LED 灯泡。由于新灯泡亮度更高，**Onyaomale** 认为部分路灯可能不再必要，通过停用这些路灯可以进一步节省能源。

我们将高速公路建模为一条从西向东延伸、长度为 $\mathbf{M}$ 米的直线。第 $x$ 米表示距离高速公路西端 $x$ 米的点。如果一盏路灯位于第 $x$ 米处，并安装了照明半径为 $\mathbf{R}$ 米的灯泡，则该路灯会照亮从第 $\max(0, x - \mathbf{R})$ 米到第 $\min(\mathbf{M}, x + \mathbf{R})$ 米（含端点）的高速公路段。**Onyaomale** 需要以最少数量的灯泡安装方案，确保高速公路的每个点都被至少一盏灯照亮。注意，这包括非整米距离的点。未安装灯泡的路灯不会照亮任何区域。

给定高速公路的长度 $\mathbf{M}$、新灯泡的照明半径 $\mathbf{R}$ 以及所有路灯的位置，求 **Onyaomale** 需要安装的最少灯泡数量以满足全路段照明需求。如果无法实现全路段照明，则报告不可能。


## 说明/提示

**样例解释**

在样例 #1 中，**Onyaomale** 只需在最西侧和中间的路灯上安装灯泡，无需使用最东侧的灯。这两个灯泡分别覆盖 $[0,5]$ 和 $[4,10]$，因此整个高速公路 $[0,10]$ 均被照亮。

![](https://cdn.luogu.com.cn/upload/image_hosting/jbc1t6nr.png)

在样例 #2 中，配置与样例 #1 相同，但灯泡照明半径更小。此时无法实现全路段照明。即使所有路灯均点亮，第 $4$ 米与第 $5$ 米之间的中点仍未被覆盖。

![](https://cdn.luogu.com.cn/upload/image_hosting/ruj47i6y.png)

在样例 #3 中，相比样例 #2 新增了一盏位于第 $3$ 米的路灯。此时必须为所有路灯安装灯泡才能实现全路段照明。

![](https://cdn.luogu.com.cn/upload/image_hosting/090hfaye.png)

**数据范围**

- $1 \leq \mathbf{T} \leq 100$。
- $1 \leq \mathbf{M} \leq 10^{9}$。
- $1 \leq \mathbf{R} \leq 10^{9}$。
- $0 \leq \mathbf{X}_{1}$。
- 对所有 $i$，满足 $\mathbf{X}_{i} < \mathbf{X}_{i+1}$。
- $\mathbf{X}_{\mathbf{N}} \leq \mathbf{M}$。

**测试集 1（4 分，可见判定）**

- $1 \leq \mathbf{N} \leq 10$。

**测试集 2（10 分，可见判定）**

- $1 \leq \mathbf{N} \leq 10^{5}$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
10 3 3
2 7 9
10 2 3
2 7 9
10 2 4
2 3 7 9```

### 输出

```
Case #1: 2
Case #2: IMPOSSIBLE
Case #3: 4```

# 题解

## 作者：wzbwzbwzb6 (赞：3)

这是一道贪心算法的题。
## 题目背景
[题目传送门](https://www.luogu.com.cn/problem/P12947)

在一条长 $m$ 米的路上安装路灯，每个路灯的照亮半径为 $r$，问需要多少盏路灯可覆盖整条公路。若不能完全覆盖，输出 `IMPOSSIBLE`。
## 关键变量
1. $pos$ 表示当前已照亮的最右位置。
2. $ans$ 表示最少所需的路灯数量。
3. $i$ 表示当前路灯的下标。
4. $mr$ 表示当前灯泡能覆盖的最远位置。
5. $flag$ 用于记录路灯是否可以覆盖整条公路。
## 核心思路（贪心）
1. 从左到右进行覆盖：不断更新当前已经照亮的最远位置 $pos$。
2. 遍历所有满足 $x_i-r\le pos$ 且 $i\le n$ 的灯泡，更新 $mr$ 为 $\max(mr,x_i+r)$。
3. 增加最少需要的灯泡数量 $ans$，将 $pos$ 更新为 $mr$。
4. 当 $pos\ge m$ 时说明已完全覆盖，退出循环。
5. 若 $flag=1$，则可以完全覆盖，输出 $ans$；否则无法完全覆盖，输出 `IMPOSSIBLE`。
## 代码
```cpp
#include <iostream>
using namespace std;
const int N=1e6+7;
int t,x[N],ans,s;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0); 
    cin>>t;
    s=t;   //s用于记录测试样例总数。
    while(t--)
    {
    	int m,r,n;
        cin>>m>>r>>n;
    	for(int i=1;i<=n;i++)cin>>x[i];
    	int i = 1,pos = 0,ans = 0,mr=0;
        bool flag = 1;
		while(i <= n)      //使用贪心策略历一遍判断能覆盖当前区域的最右边的灯泡。 
		{
		    if(x[i]-r > pos)    //不能全部覆盖。 
			{
			    flag=0;
				break;
			}
			mr = x[i] + r;
			while(x[i]-r<=pos && i<=n)    //遍历所有满足 x[i]-r<=pos 且 i 不超过 n 的灯泡。 
			{
				mr = max(mr,x[i]+r);
				i++;
			}
			ans++;           //ans 记录最少需要安装的灯泡数量。 
			pos = mr;          //更新当前的位置为新的位置。 
			if(pos >= m)break;
		}
		if(pos < m)flag=0;
		if(flag == 1)cout<<"Case #"<<s-t<<": "<<ans<<endl;
		else cout<<"Case #"<<s-t<<": "<<"IMPOSSIBLE"<<endl;
	}
	return 0;
}
```
代码时间复杂度为 $O(nt)$，空间复杂度为 $O(n)$，可以通过本题。

---

## 作者：y_yaozhikai (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P12947)
---

首先~~好习惯~~，在洛谷刷题时，有算法标签的看看算法标签，往往能给到许多启发。

---
## 题意解读及策略分析
题意：其实很好理解，就是给一条马路，有 M 盏路灯，每盏灯有一定的照明范围 ``` R ``` 
，问你最少需要开多少盏灯才能保证整条马路都被照亮，若无这种方案就输出 ```IMPOSSIBLE```。

如标签所示，本题是一道~~本人最怕的~~贪心题，所以马上开始想贪心策略。

#### 过了 5min，发现其实贪心策略很简单：

首先判断从哪盏灯作为第一盏打开的灯，然后根据对照明范围的计算，继续~~疯狂~~枚举每一盏路灯，找到下一盏离本盏灯最远的且能够保证能够衔接上本盏灯的照明范围的灯。直到到最后一盏灯或照明范围已经**达到/超过**整条马路的最末端。

---
# **写代码**
变量准备：
```cpp
int T,m,r,n,cnt,light,a[100005];
//T代表数据组数、m代表马路长度、r代表灯的照明范围；
//n代表路灯数量、cnt代表打开的路灯数量；
//light代表目前最远打开的灯的右照明范围、a数组记录路灯位置
```
首先由于可能开头全路第一盏灯的照明范围根本就达不到马路的开头，或是全路最后一盏灯的照明范围达不到马路的末端。所以，下意识打出一下一段特判代码：
```cpp
if(a[1]-r>0||a[n]+r<m){
    cout<<"Case #"<<i<<": IMPOSSIBLE"<<endl;
    continue;
}
```
接着使用 ```for``` 循环遍历记录路灯位置的 ```a``` 数组：
```cpp
for(int j=1;j<=n;j++)
```
然后先判断上一轮循环过后 ```light```（即目前最远打开的灯的右照明范围）是否已
**到达/超过**马路的尽头 ```m```。若到达直接退出循环，准备输出答案；
```cpp
if(light>=m)break;
```
而若接下来新的一盏灯（离上一盏灯最近的一盏）的左照明范围无法与上一盏灯的右照明范围 ```light``` 衔接上，说明已无可行方案，也退出循环；
```cpp
else if(a[j]-r>light)break;
```
最后若现在这盏灯的左照明范围**能够达到上一盏灯的右照明范围且再下一盏灯的左照明范围无法到达（确保现在这盏灯是当前最优解）**，就增加打开的路灯数并更新 ```light```；
```cpp
else if((a[j]-r<=light&&a[j+1]-r>light)||j==n)
    cnt++，light=a[j]+r;
```
最后的最后根据结果输出答案即可顺利通过！

---
# **尾声**
这里献上完整的 ```AC``` 代码**以供参考**
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,m,r,n,cnt,light,a[100005];//变量，上文已解释
int main(){
    cin>>T;//输入数据组数
    for(int i=1;i<=T;i++){
        cin>>m>>r>>n;输入数据
        for(int j=1;j<=n;j++)cin>>a[j];//输入路灯位置
        if(a[1]-r>0||a[n]+r<m){
            cout<<"Case #"<<i<<": IMPOSSIBLE"<<endl;
            continue;
        }
        cnt=0,light=0;
        for(int j=1;j<=n;j++)
            if(light>=m)break;
            else if(a[j]-r>light)break;
            else if((a[j]-r<=light&&a[j+1]-r>light)||j==n)
                cnt++，light=a[j]+r;
            //以上部分上文已进行了详细解释！！！
        if(light<m)cout<<"Case #"<<i<<": IMPOSSIBLE"<<endl;
        //若最后一盏打开的灯的右照明范围未能到达马路尽头，输出“IMPOSSIBLE”。
        else cout<<"Case #"<<i<<": "<<cnt<<endl;
        //否则说明能够全路照亮，输出最少所需的路灯数。
    }
    return 0;//完结撒花！！！
}
```
[AC 记录](https://www.luogu.com.cn/record/227464856)

**~~温馨提示：抄题解是错误的行为哦！~~**
### 最后感谢您的观看~~点个赞再走？~~

---

## 作者：__coderyc__ (赞：1)

## 题意
注意到题目标签有贪心，不妨就按照贪心思路来写。

简述一下题意：

要求用最少数量的路灯覆盖整个高速公路，每个路灯的照明范围为 $[x-R, x+R]$。关键在于求出能覆盖当前未覆盖区域的最远路灯，如果不能覆盖全路段，输出 `IMPOSSIBLE` 这个词。其中 $R$ 表示照明半径，$x$ 表示路灯当前的位置。

## 变量定义
1. $covered$ 表示当前光照覆盖区域的终点；
2. $count$ 表示使用灯泡的数量；
3. $farthest$ 表示当前能覆盖**最远的路灯位置**；
4. $i$ 表示到第几个路灯了；
5. 剩下的定义与题目一致。
## 思路
每一轮刚开始，我们先令 $covered=0$ 因为还没有照亮任何区域，覆盖区域的终点就为 $0$；$farthest=-1$ 一是因为理由同前，二是因为作为一个标记（后面会讲）；$count=0$ 也是一个原因。

先找第一个 $x_i \le covered+R_i$ 的路灯（能照亮新区域），那么 $farthest$ 自然就等于 $x_i$，$i$ 也加 $1$ 因为要走下一个路灯继续去尝试。

走完这一轮，$farthest$ 如果还是 $-1$ 那么就直接输出 `IMPOSSIBLE`，因为这标志着这一轮没有一个能新照亮的路灯，因为 $farthest$ 没有更新。

$covered$ 就要更新为 $covered+R_i$，$count$ 也要加上 $1$，是因为你肯定用了一盏灯（因为运行到现在，说明 $farthest$ 肯定更新了）。如果 $covered>M$，那么直接返回输出 $count$，这标志着已经全部覆盖道路了。

需要注意 $i$ 要小于 $N$，确保没有越界。

## 代码

```cpp
#include<bits/stdc++.h>  
using namespace std;
int M,R,N,T,X[1000005]; 
void solve(int M,int R,int N,int X[]){  // solve函数，注意X为数组因为这里存的是数组
    int covered=0,count=0,i=0;  // 初始化
    while(covered<M){ 
        int farthest=-1;  //打标记
        while(i<N&&X[i]<=covered+R){  // 查找能覆盖当前未覆盖区域的路灯
            farthest=X[i];
            i++;
        }
        if(farthest==-1){  //如果标记没改变
            cout<<"IMPOSSIBLE"<<endl;  //输出不可能
            return;
        }
        count++; 
        covered=farthest+R;  
        if(covered>=M)break;  //检查是否完全覆盖
    }
    cout<<count<<endl;  // 全部循环结束，输出最少路灯数
}
int main(){
    cin>>T;  
    for(int t=1;t<=T;++t){  
        cin>>M>>R>>N;
        for(int i=0;i<N;++i)cin>>X[i];
        cout<<"Case #"<<t<<": ";
        solve(M,R,N,X); 
    }
    return 0;
}
```
时间复杂度为 $O(NT)$，可以通过此题。

---

## 作者：tujiaqi12 (赞：1)

## 主体步骤
第一步，计算出每盏灯的左右边界

第二步，把每盏灯按左边界排序，~~但题目中已经帮您排好了。~~

第三步，**贪心**，每次选择能与之前照亮范围衔接的路灯中右端点最靠右的路灯。这能使加上当前路灯后，能照亮范围最大。
## 状态判断
在步骤三中，每放一个路灯将答案加一，若出现每个路灯都衔接不上的情况下，则不可能全部照亮，否则输出答案即可。
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll t;
ll m,r,n;
ll x;
struct info{
	ll l;//左端点 
	ll r;//右端点
}a[100005];//路灯 
int main(){
	scanf("%lld",&t);
	for(ll q = 1;q <= t;q++){
		scanf("%lld%lld%lld",&m,&r,&n);
		for(ll i = 1;i <= n;i++){
			scanf("%lld",&x);
			a[i].l =max(0ll,x-r);
			a[i].r = min(m,x+r);
		}
		ll fu = 0;//已照亮的范围 
		ll ans = 0;
		ll i = 1;
		a[n+1].l = 1e13; 
		bool flag = 1;//是否有解 
		while(i <= n){
			if(fu < a[i].l){
				flag = 0;
				break;
			}
			while(a[i+1].l <= fu){
				i++;
			}
			ans++;
			fu = a[i].r;
			i++;
			if(fu >= m){
				break;
			}
		}
		if(fu < m){
			flag = 0;
		}
		if(flag){
			printf("Case #%lld: %lld\n",q,ans);
		}
		else{
			printf("Case #%lld: IMPOSSIBLE\n",q);	
		}
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/P12947)
这题有点水。
### 前言

这道题要求我们选择最少数量的路灯来照亮整个高速公路。我们需要确保每个点都被至少一盏灯覆盖，同时尽量减少安装的灯泡数量。

### 思路
这道题可以采用贪心算法来解决。我们从高速公路起点开始，每次选择能覆盖当前未照亮区域的最远路灯，确保每次安装的灯泡能覆盖尽可能长的路段，直到整个高速公路被完全照亮或确定无法实现全路段照明。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
void sv() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        int M, R, N;
        cin >> M >> R >> N;
        vector<int> X(N);
        for (int i = 0; i < N; ++i) {
            cin >> X[i];
        }
        int r = 0;
        int p = 0;
        int i = 0;
        bool pp = true;
        while (p < M && pp) {
            int f = -1;
            while (i < N && X[i] - R <= p) {
                f = X[i];
                ++i;
            }
            if (f == -1) {
                pp = false;
                break;
            }
            p = f + R;
            ++r;
        }
        if (pp && p >= M) {
            cout << "Case #" << t << ": " << r << endl;
        } else {
            cout << "Case #" << t << ": IMPOSSIBLE" << endl;
        }
    }
}
int main() {
    sv();
    return 0;
}
```

---

## 作者：weiyc1 (赞：0)

## 解题思路
从高速公路的最西端开始，我们需要找到能够覆盖当前位置且照明范围最靠东的路灯。

安装该路灯后，将当前位置更新为该路灯能照亮的最东位置。
重复这个过程，直到覆盖整个高速公路或确定无法覆盖。

这种贪心策略能保证使用最少的路灯，因为每次我们都选择了能覆盖当前位置且能延伸到最远处的路灯，最大化了覆盖范围。

## AC 代码：
```
#include <iostream>
using namespace std;
int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        long long M, R;
        int N;
        cin >> M >> R >> N;
        long long X[100000];  
        for (int i = 0; i < N; ++i) cin >> X[i];
        if (M == 0) {  // 特殊情况处理
            cout << "Case #" << t << ": 0" << endl;
            continue;
        }
        long long c = 0;  // 当前需要覆盖的位置
        int b = 0;        // 使用的灯泡数量
        int i = 0;        // 当前检查的路灯索引
        bool ok = true;   // 是否可能覆盖全路段
        while (c < M) {
            long long f = -1;  // 最远覆盖位置
            while (i < N && X[i] - R <= c) {
                long long cov = min(X[i] + R, M);  // 覆盖范围
                if (cov > f) f = cov;
                i++;
            }
            if (f == -1 || f <= c) {  // 无法覆盖当前位置或无法前进
                ok = false;
                break;
            }
            b++;
            c = f;
        }
        cout << "Case #" << t << ": ";
        if (ok) cout << b << endl;
        else cout << "IMPOSSIBLE" << endl;
    }
    return 0;
}
```

---

## 作者：_aszxqw_ (赞：0)

这题就是一道简单的贪心。    
贪心思路：    
- 检查起点和终点：首先检查第一个路灯是否能覆盖起点 $0$，最后一个路灯是否能覆盖终点 $M$。如果不能，直接返回 `IMPOSSIBLE`。

- 贪心选择路灯：从起点开始，每次选择能覆盖当前未被照亮区域的最右边的路灯。这样能保证用最少的灯覆盖最多的区域。

### AC 代码  
```
#include <bits/stdc++.h>
using namespace std;
int main() {
    int T, kkk = 1;
    cin >> T;
    while(T--){
        long long m, r, n;
        cin >> m >> r >> n;
        long long a[n];  
        for (int i = 0; i < n; ++i) cin >> a[i];
        if (m == 0) {  // 特殊情况处理
            cout << "Case #" << kkk << ": 0" << endl;
            continue;
        }
        long long c = 0;  // 当前需要覆盖的位置
        int b = 0;        // 使用的灯泡数量
        int i = 0;        // 当前检查的路灯索引
        bool YorN = 1;   // 是否可能覆盖全路段
        while (c < m) {
            long long f = -1;  // 最远覆盖位置
            while (i < n && a[i] - r <= c) {
                if (min(a[i] + r, m) > f) f = min(a[i] + r, m);
                i++;
            }
            if (f == -1 || f <= c) {  // 无法覆盖当前位置或无法前进
                YorN = 0;
                break;
            }
            b++;
            c = f;
        }
        cout << "Case #" << kkk << ": ";
        if (YorN) cout << b << endl;
        else cout << "IMPOSSIBLE" << endl;
        kkk++;
    }
    return 0;
}
```

---

## 作者：yuxinrui0618 (赞：0)

# 题解：P12947 [GCJ Farewell Round #1] Illumination Optimization
## 1. 题目大意
- 意思很简单，就是用 $n$ 盏路灯想办法照亮整条路；
- 设每个灯的位置为 $a_i$，那么灯的照明范围即为 $a_i-r$ 到 $a_i+r$，其中 $r$ 为题目中灯泡照明半径。

## 2. 思路
- 这道题直接贪心即可，毕竟标签都打了；
- 枚举每一个路灯，用 $pos$ 记录当前能照亮的最远的位置，每次枚举确保这次选的路灯能覆盖到上次路灯照到的区域，也就是保证每个位置都能照到；
- 枚举过程中，每次都要找到符合要求的最远的路灯，这样才能保证答案最小。

## 3. 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100001];
int main() {
    int t;
    cin>>t;
    for (int i=1;i<=t;i++)
    {
    	int m,r,n;
    	cin>>m>>r>>n;
    	for (int j=1;j<=n;j++)
    		cin>>a[j];
    	int s=0,pos=0,f=1; //s记录使用数量，pos表示当前能够照到的最远位置
    	for (int j=1;j<=n;)
    	{
    		if (a[j]-r<=pos) //找到一个路灯还不行，要继续找，找到符合要求的最远路灯
    		{
    			int nowpos=a[j]+r;
    			while (j<=n)
    			{
    				if (a[j]-r<=pos) //每次都要确保每个位置都能照到
    				{
    					nowpos=max(nowpos,a[j]+r);
    					j++;
					}
					else break;
				}
				s++;
				pos=nowpos;
				if (pos>=m) break;
			}
			else
			{
				f=0;
				break;
			}
		}
		if (pos<m || f==0)
			cout<<"Case #"<<i<<": IMPOSSIBLE"<<endl;
		else cout<<"Case #"<<i<<": "<<s<<endl;
	}
    return 0;
}
```

## 4. 总结
谢谢观赏！  
如有问题和建议还请各位大佬指出！

---

## 作者：YuTinMin (赞：0)

## 思路

标签贪心，那就是贪心的题了（~~废话~~）。

题目要计算需要多少个灯泡，就是一个区域一个区域地看，定义变量 `p` 作为当前已经照亮的最远位置（其实就是当前的位置），弄一个循环，用于寻找可以覆盖当前区域的最右边的灯泡（对了，要先判断 $x_i$ 能不能接上上一个灯泡照亮的区域，不能接上就直接跳出循环，最后输出 `IMPOSSIBLE`），一个 `while (i <= n && x[i] - r <= p)` 循环寻找可以覆盖当前区域的最右边的灯泡，然后 `sum` 加一，然后特判当前位置 `p` 有没有超过道路的长度 `m` ，有就跳出循环，没有就继续。

终于到输出了，输出简单，一个 `if` 判断我们的标记 `flag` 是否为真，真就输出 `sum` 不行就输出 `IMPOSSIBLE`。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int x[N];

int main()
{

    int t;
    cin >> t;
    for (int kk = 1; kk <= t; kk++)
    {
        int m, r, n;
        cin >> m >> r >> n;
        for (int i = 1; i <= n; i++)
            cin >> x[i];
        int sum = 0; //需要的总量
        int p = 0; //当前位置
        bool flag = true; //标记是否成立
        for (int i = 1; i <= n;) //不在这里i++
        {
            if (x[i] - r > p) //判断当前位置是否无法覆盖到下一个位置
            {
                flag = false;
                break;
            }
            //寻找能覆盖当前区域的最右边的路灯
            int mr = x[i] + r;
            while (i <= n && x[i] - r <= p)
            {
                mr = max(mr, x[i] + r);
                i++; //继续加，找到最右边的灯泡
            }
            sum++;
            p = mr;
            if (p >= m) //大于长度就跳出
                break;
        }
        if (p < m)
            flag = false;
        if (flag)
            printf("Case #%d: %d \n", kk, sum); //注意空格哦，别输出错了
        else
            printf("Case #%d: IMPOSSIBLE \n", kk);
    }

    return 0;
}
```

---

## 作者：Clouds_dream (赞：0)

**温馨提示：**  
在本文章中，各变量的含义为：

- $m$,$r$ 和 $n$ 的含义见题目。
- $a_i$ 为 $i$ 号路灯的位置。
- $pos$ 是当前已覆盖的最右位置。
- $j$ 是当前处理的路灯索引。
- $ans$ 为答案。

### 题目大意
[题目传送门](https://www.luogu.com.cn/problem/P12947)

### 思路
我们将路灯的覆盖范围转化为区间覆盖问题。  

**贪心策略：**

- 初始化当前覆盖的最右位置（$pos=0$）。
- 按路灯位置升序遍历。
- 在左端点不超过 $pos$ 的路灯中，选择右端点最大的一个。
- 更新 $pos$ 为该最大右端点，增加灯泡计数（$ans$）。
- 直到覆盖整个公路。

这样基本上就做完了。

**边界：**

- 如果无法扩展覆盖范围（$a_j - r > pos$），即没有路灯可以覆盖当前 $pos$ 的位置，则返回 `IMPOSSIBLE`。
- 处理右端点超过 $m$ 的情况，取 $\min(m,a_j + r)$。

### 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

signed main()
{
	fst
	int q;
	cin>>q;
	for(int t=1;t<=q;t++){
		int m,r,n;
		cin>>m>>r>>n;
		int a[n+10];
		for(int i=1;i<=n;i++){
			cin>>a[i];//路灯位置
		}
		int pos=0,j=1,ans=0;
		bool flag=1;//是否可行
		while(pos<m){
			int lr=pos;
			if(j>n){
				flag=0;
				break;
			}
			if(a[j]-r>pos){
				flag=0;
				break;
			}
			while(j<=n&&a[j]-r<=pos){
				int nr=min(m,a[j]+r);
				if(nr>lr)lr=nr;
				j++;
			}
			if(lr<=pos){
				flag=0;
				break;
			}
			ans++;
			pos=lr;
			if(pos>=m)break;//覆盖完了
		}
		if(flag&&pos>=m){
			cout<<"Case #"<<t<<": "<<ans<<endl;
		}
		else{
			cout<<"Case #"<<t<<": IMPOSSIBLE"<<endl;
		}
	}
	return 0;
}
```

---

## 作者：4041nofoundGeoge (赞：0)

水题。出题人~~你是不是有病，还要输出第几行~~。

## 题目大意

O 让你在 $0\sim M$ 的数轴上选择任意个指定位置安装灯泡，灯泡光照半径为 $R$，问最少指定多少个位置可以使数轴全覆盖。

## 思路

考虑贪心。

最开始照亮的地方是 $0$，然后我们查找每个位置的左边界刚好（或差不多）能覆盖这个结点，我们就选这个结点，然后能照亮的地方就是这个结点的右边界，即（当前点位 $+R$），我们继续查找左边界能刚好（或差不多）覆盖这个结点 $\cdots$ 直到覆盖到右边界 $M$，我们选的结点数 $res$ 就是答案，可以证明这是最优解。

证明：

设全长为 $L$，贪心选择的第一个结点 $r$ 光照范围为 $[0,r+R]$，剩下的 $(r+R,L]$ 应一定与 $[0,r+R]$ 一样存在最优解，因此贪心一定为最优解。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int x[100005];
int main(){
    int t;
    cin>>t;
    int q=t;
    while(t--){//我偏不用for循环
        int m,r,n;
        cin>>m>>r>>n;
        for(int i=1;i<=n;i++){
            cin>>x[i];
        }
        int i=1;
        int pos=0;
        int maxn=-1;
        int res=0;
        bool poss=true;
        while(pos<m){
            maxn=-1;
            while(i<=n&&x[i]-r<=pos){
                maxn=x[i],i++;
            }
            if(maxn==-1){
                poss=false;
                break;
            }
            res++;
            pos=maxn+r;
            if(pos>=m)break;
            if(i>n||x[i]-r>pos){
                poss=false;
                break;
            }
        }
        cout<<"Case #"<<q-t<<": ";
        if(poss)cout<<res;
        else cout<<"IMPOSSIBLE";
        cout<<"\n";
    }

    return 0;
}
```

---

