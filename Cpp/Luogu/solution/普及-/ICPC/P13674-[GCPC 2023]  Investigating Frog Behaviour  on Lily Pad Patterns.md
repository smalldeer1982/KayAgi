# [GCPC 2023]  Investigating Frog Behaviour  on Lily Pad Patterns

## 题目描述

最近，生物学家 Ina 在池塘的睡莲叶上发现了一种新的青蛙物种。她观察这些青蛙一段时间后发现，它们非常注重个人空间，总是避免与其他青蛙共用同一片睡莲叶。此外，它们似乎很懒惰，很少移动，即使移动，也总是跳到最近的空睡莲叶上。

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/6jt2rls1.png)

池塘中的一只青蛙。
:::

为了验证她关于青蛙移动模式的假设，Ina 在实验室的池中布置了大量睡莲叶，并将它们排成一条直线。由于青蛙会被光吸引，她进一步简化了实验装置，在直线的一端放置了一盏明亮的灯。这样，青蛙总是朝着光的方向跳跃（即只会向编号更大的方向跳）。

当然，Ina 现在可以把一些青蛙放到睡莲叶上，然后整天坐在那里观察青蛙跳跃。但由于青蛙很少移动，收集足够的数据将耗费大量时间。

因此，她在每只青蛙身上安装了一个微型装置，可以记录该青蛙的所有跳跃。这样，她就可以把青蛙放到睡莲叶上，离开几个小时后再回来收集数据。不幸的是，这些装置必须非常小，没有空间安装定位系统；它们只能记录每次跳跃的时间。

但如果青蛙的移动模式像 Ina 所想的那样受限，仅凭初始位置和记录的跳跃时间戳，是否一定可以还原每只青蛙的具体移动轨迹呢？

## 说明/提示

![](https://cdn.luogu.com.cn/upload/image_hosting/k07qih18.png)

:::align{center}
图 I.1：第一个样例的示意图。睡莲叶从左到右编号，从 $1$ 开始。
:::

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
1 2 3 5 7
3
1
2
4```

### 输出

```
4
6
8```

## 样例 #2

### 输入

```
5
1 2 3 5 7
4
1
1
1
1```

### 输出

```
4
6
8
9```

# 题解

## 作者：GeorgeDeng (赞：3)

交了整整 $10$ 次才通过。要是放在真实比赛中就变成 ${\color{Green} +10} $ 了。

## 避雷：

我拿到题目的第一反应：并查集！

每次找到后面第一个空位，直接使用并查集找就可以了。但是不能够用普通并查集的方法，因为中间可能有空位但是会跳过。

上面的时间复杂度 $O(qV)$，其中 $V$ 是值域。TLE 了（我为此交了 $8$ 发）。

下面是正题。

## 正经思路：

为什么并查集会 T，因为没有路径压缩了，并查集查找从 $O(1)$ 变到了 $O(V)$，所以 TLE 了。

如果我们只看能跳的荷叶，从左往右有显然的单调性，想到二分。

如果只用数组或 vector 的话，插入和删除是 $O(n)$ 的，不够优秀，有什么更优秀的数据结构呢？

set 可以高效插入和删除，还自带二分函数，因此我们在这道题中使用 set 作为存储可以跳到的荷叶的数据结构。

一开始我们把所有没有青蛙的荷叶全部塞进 set 里面。每一次跳第 $i$ 只青蛙的时候，调用 set 里面的 `upper_bound` 函数二分查找第一个大于 $x_i$ 的，然后修改 $x_i$ 和 set 里面的元素。这样就做完了。

注意这道题卡你的值域，建议把值域设置成 $2\times 10^6$，因为最坏情况下右端点差不多 $2\times 10^6$。

## 代码：

```cpp
#include <iostream>
#include <set>
#define int long long
using namespace std;

const int N = 2e6+7;//值域
bool vis[N];
int x[N];
int n,q;
set<int> aviliable;
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i = 1;i<=n;i++){
        cin>>x[i];
        vis[x[i]] = true;
    }
    for(int i = 1;i<N;i++){
        if(!vis[i]) aviliable.insert(i);//把所有没有青蛙的荷叶放进set里面
    }
    cin>>q;
    while(q--){
        int i;
        cin>>i;
        int tmp = x[i];
        set<int>::iterator it = aviliable.upper_bound(tmp);//调用upper_bound函数
        cout<<*it<<endl;
        aviliable.insert(x[i]);//各种调整
        aviliable.erase(*it);
        x[i] = *it;
    }
    return 0;
}
```

---

## 作者：__coderyc__ (赞：2)

## 思路
使用 set 进行存储。

先初始化青蛙位置的同时记录被占用的荷叶，接着查找空荷叶位置，当前荷叶没被占用就暂时存进空荷叶的集合。

每一次询问，找到青蛙当前位置，查找最近空荷叶（也就是找第一个大于当前青蛙坐标的空荷叶），新坐标被占用，旧坐标就加入空荷叶集合。

记得每一次扩展池塘荷叶，防止后面的青蛙无路可走。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 5;
const int MAXX = 1e6 + 5;
int frog_pos[MAXN];
set<int> occupied;
set<int> empty_pads;
int n, q;
int main() { 
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> frog_pos[i];
        occupied.insert(frog_pos[i]);
    }
    int max_pos = frog_pos[n];
    for (int i = 1; i <= max_pos + 1; ++i) {
        if (occupied.find(i) == occupied.end()) {
            empty_pads.insert(i);
        }
    }
    cin >> q;
    while (q--) {
        int i;
        cin >> i;
        int current = frog_pos[i];
        auto it = empty_pads.upper_bound(current);
        int next_pos = *it;
        occupied.erase(current);
        occupied.insert(next_pos);
        empty_pads.erase(next_pos);
        empty_pads.insert(current);
        frog_pos[i] = next_pos;
        if (empty_pads.upper_bound(next_pos) == empty_pads.end()) {
            empty_pads.insert(next_pos + 1);
        }
        cout << next_pos << '\n';
    }
    return 0;
}
```
时间复杂度为 $O((n+q)\log n)$。可以通过此题。

---

## 作者：wyp20130701_AC (赞：1)

[题目传送门。](https://www.luogu.com.cn/problem/P13674)  
前置知识：set 容器。
## 题意概述
题目描述了一种青蛙在莲叶上的行为模式。青蛙们不喜欢与其他青蛙共享同一个莲叶，因此它们会避免跳到已经有青蛙的莲叶上。此外，这些青蛙比较懒惰，不经常移动，但当它们移动时，总是跳到最近的空莲叶上，且移动方向固定（朝向光源）。  
为了验证这一行为模式，生物学家 Ina 在实验室中设置了一系列排成直线的莲叶，并在其一端放置光源，使得青蛙只能朝一个方向跳跃。每个青蛙身上装有记录跳跃时间的设备，但没有位置跟踪功能。因此，只能通过初始位置和跳跃时间戳来重建青蛙的跳跃轨迹。
## 思路
使用 set 来存储所有空莲叶的位置，便于快速查找大于当前位置的最小空位。  
数组 $pos$ 记录每只青蛙的当前位置。  
初始化将所有可能的位置（$1$ 到 $MAX$）插入 set 中，然后删除初始青蛙占据的位置。  
对于每次跳跃，获取青蛙当前位置 $p$。  
在 set 中查找大于 $p$ 的最小位置 $next$。  
更新 set 将 $p$ 插入（原位置变空），将 $next$ 删除（新位置被占用）。  
更新青蛙的位置 $pos_i = next$ 并输出 $next$。
## 代码
```
#include<bits/stdc++.h>
using namespace std;
const int MAX = 1400000;
int n, q;
int x[200010];
int pos[200010];
set<int> s;// 使用set维护当前空莲叶的位置，便于快速查找
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
        pos[i] = x[i];// 记录每只青蛙的当前位置
    }
    // 初始化所有可能的空莲叶位置
    for (int i = 1; i <= MAX; i++）s.insert(i);
    // 删除初始青蛙占据的位置
    for (int i = 1; i <= n; i++) s.erase(x[i]);
    cin >> q;
    while (q--) {
        int i; cin >> i;
        int p = pos[i];
        auto it = s.lower_bound(p + 1);// 查找大于p的最小空莲叶位置
        int next = *it;
        s.erase(it);// 删除该空莲叶，表示被占用
        s.insert(p);// 将原位置插入set，表示变为空
        pos[i] = next;
        cout << next_pos << '\n';
    }
    return 0;
}
```

---

## 作者：koukou (赞：1)

~~呱呱呱。~~

如果一次操作直接枚举的话，肯定会超时。不难想到，可以用一个 set 储存所有荷叶的编号，一次操作时直接二分找到第一个能够到达的荷叶就可以了。

代码：
```
#include<bits/stdc++.h>
using namespace std;
const int N = 5e6 + 1;
set<int> st;
bool vis[N];
int n, T, id[N];
int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        cin >> id[i];
        vis[id[i]] = 1;//标记
    }
    for(int i = 1; i < N; i++)
    {
        if(!vis[i]) st.insert(i);//可以到达的荷叶
    }
    cin >> T;
    while(T--)
    {
        int x;
        cin >> x;
        int cnt = id[x];
        auto y = st.upper_bound(cnt);//二分查找
        cout << *y << "\n";
        st.insert(cnt);//此时的荷叶就空了
        st.erase(*y);//被跳到的荷叶就有一只青蛙了
        id[x] = *y;//更新青蛙的位置
    }
    return 0;
}
```

---

## 作者：yytmcjs (赞：1)

# P13674 [GCPC 2023] Investigating Frog Behaviour on Lily Pad Patterns
### 题目概括
有一排睡莲，一些青蛙初始在一些睡莲上，每次给出第 $i$ 只青蛙跳跃了，每个青蛙只会跳到右侧距离自己最近的空位，求每次跳跃后跳到的地方。
### 思路
可以想到将**空位放到一个容器**中，每次跳跃只需要找到容器中在这个**青蛙右侧最小**的位置，修改青蛙位置后将新的空位加入容器。这里有一个查找大于等于某数的最小值的操作，我们考虑使用 set 容器。并且位置不会重复，可以使用。
### 具体方法
在刚刚读入青蛙位置时，应当记录最后一个青蛙的位置 $maxx$，如果有一只青蛙不得已要跳到最后一只青蛙往后，可以直接跳到 $maxx$ 的下一个睡莲上，并更新 $maxx$。

全部读入后，我们需要枚举每个区间（两端点为两个青蛙），并将**区间内的位置**（不含端点）加入空位的集合中。

接下来进行跳跃，当第 $x$ 个青蛙跳跃了，先判断它的下一个位置有没有超过 $maxx$，即它是最后一只。若是，则直接跳到 $maxx$ 的下一个位置。否则使用 `lower_bound(a[x+1])` 查找大于等于此位置的下一个位置的最小空位。如果没找到，就只能跳到 $maxx$ 的下一个位置了。

每次跳跃要删掉跳到的空位，并把之前的位置加入空位，输出答案即可。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int n,a[1000005],q;		//一定要开大点 

set<int> emp;

int main(){
	cin >> n;
	for (int i=1;i<=n;i++){
		cin >> a[i];
	}
	int maxx=a[n];
	for (int i=1;i<n;i++){
		int sta=a[i];
		int end=a[i+1];
		for (int j=a[i]+1;j<a[i+1];j++) emp.insert(j);		//加入空位 
	}
	cin >> q;
	for (int i=1;i<=q;i++){
		int x;
		cin >> x;
		int pos=a[x]+1;
		int npos;
		if (pos>maxx){		//是否是最后一个 
			npos=pos;
		}
		else{		//这里指针数据类型要注意 
			auto p=emp.lower_bound(pos);
			if (p!=emp.end()){
				npos=*p;
				emp.erase(p);
			}
			else{
				npos=maxx+1;
			}
		}
		emp.insert(a[x]);
		a[x]=npos;		//修改空位和位置 
		maxx=max(maxx,npos);		//修改最后一个青蛙 
		cout << npos << endl; 		//输出答案 
	}
	return 0;
}

```
### 总结
因为我们需要找到比某数大的最小值，所以正好可以根据集合的单调性直接使用它的查找函数，选择正确的容器很重要。

---

## 作者：guoshengyu1231 (赞：1)

# 题意简述&翻译
有 $n$ 只青蛙，第 $i$ 只青蛙的位置为 $a_i$。现在有 $q$ 只青蛙将会往后跳到最近的一个空位，每次青蛙往后跳过后输出当前这只青蛙的位置。
# 思路
简单模拟题，可以使用 STL 里的`set`简便维护。首先开一个`set`维护当前的空位。之后每次查询时找到第一个位置 $>a_x$ 的空位，如果这个空位存在，输出当前空位位置，接着模拟青蛙跳跃，也就是将这个青蛙原先的位置加入`set`中，再把那个最近的一个空位删除，当然还要记得在原先的数组中修改青蛙的位置，这样便成功模拟了一次青蛙跳跃的过程。但如果没有这个空位呢，那就新建一个空位呗，其余的过程也就差不多了。就是将这个空位输出然后将原先的青蛙位置加入`set`就行了。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
int n,a[maxn],m,x,maxw;
bool f[maxn];
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],f[a[i]]=true;
    maxw=a[n];set<int> s;
    for(int i=1;i<=maxw;i++)
     if(!f[i]) s.insert(i);//将空位加入set
    cin>>m;
    while(m--)
     {
        cin>>x;
        auto it=s.upper_bound(a[x]);//找到第一个位置大于 a[x] 的空位
        if(it!=s.end())//如果这个空位存在
         {
            cout<<*it<<"\n";
            s.insert(a[x]);
            a[x]=*it;
            s.erase(it);   //没什么可讲的，按题意模拟即可        
         }
        else
         {
            maxw++;
            cout<<maxw<<"\n";
            s.insert(a[x]);
            a[x]=maxw;//和上面的差不多
         }
     }
    return 0;
}
```

---

## 作者：XiaoYang_awa (赞：1)

# [P13674 [GCPC 2023]  Investigating Frog Behaviour  on Lily Pad Patterns](https://www.luogu.com.cn/problem/P13674)

::::info[题意简述]{open}
给出青蛙编号，青蛙会向荷叶编号更大的地方调到离现在位置最近的空位置。
::::

## 思路：
考虑用 `set` 维护空位置，存储所有空位置编号，再使用 `lower_bound` 查找最近的空位置。

但题目说，青蛙编号是固定的，所以可以使用另外一个数组来映射。

注意：虽然题目给的数据规模较小，但实际上青蛙可能跳到更大的地方。在测试后，数组大小应该开到 $3\times 10^6$。

代码简洁明了，详看注释。

## 代码：
请不要抄袭。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,maxn,a[3000005],p[3000005];//a数组表示某个位置上的青蛙编号，p数组是映射数组
set<int> st;
int main(){
    cin>>n;
    for(int i=1;i<=3000005;i++)st.insert(i);//初始所有位置都是空的
    for(int i=1,ds;i<=n;i++){
        cin>>ds;
        st.erase(ds);//把不为空的删除
        a[ds]=i,p[i]=ds;//更新a数组
    }
    cin>>m;
    while(m--){
        cin>>k;
        int now=p[k];//找到编号为k的青蛙位置
        auto it=st.lower_bound(now+1);//找最近的空位
        if(it==st.end()){//保险
            it=st.insert(now+1).first;
        }
        int pos=*it;
        cout<<pos<<'\n';//输出空位置坐标
        st.insert(now),st.erase(pos);//更新空位置
        a[pos]=k,a[now]=0,p[k]=pos;//移动青蛙，并更新映射
    }
}
```

---

## 作者：I_am_feiwu (赞：0)

## 思路
这道题是模拟题，关键点在于处理每次跳跃。

但是这道题时空限制都很宽，可以把所有空位都给添加到  set 中，这样就避免了要特判跳跃时没有空位的情况。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
set<int> emp;
set<int>::iterator it;
int n,q,tmp,x[200005],last;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=2e6;i++)	emp.insert(i);//把所有的空位都加入集合
	for(int i=1;i<=n;i++){
		cin>>x[i];
		emp.erase(x[i]);//删去空位
	}
	cin>>q;
	while(q--){
		cin>>tmp;
		it=emp.upper_bound(x[tmp]);//找到下一个空位，由于空位添加到了2e6，所以必定存在符合题意的空位
		cout<<*it<<'\n';
		emp.insert(x[tmp]);//把原来的加入集合
		emp.erase(it);//把现在的位置从集合删去
		x[tmp]=*it;	
	}
}
```

---

## 作者：furina_yyds (赞：0)

# 思路

本题可以采用 set。

首先，预处理初始位置和已被占用的荷叶。随后，排查出所有空荷叶的位置，只要某个荷叶尚未被占用，就将其临时存入空荷叶 set 中。

每当有查询请求时，先定位到青蛙当前所在的位置，再去寻找距离最近的空荷叶 —— 具体来说，就是找出第一个坐标值大于青蛙当前坐标的空荷叶。当新的坐标被占用后，原来的坐标就会被加入到空荷叶集合里（有涉及一点贪心思想）。

需要注意的是，要定期对池塘的荷叶进行扩展，这样才能避免后续青蛙出现没有地方可去的情况。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
const int X = 1e6 + 5;
int pos[N];
set<int> filled, gaps;
int m, t;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> pos[i];
        filled.insert(pos[i]);
    }
    int maxp = pos[m];
    for (int i = 1; i <= maxp + 1; ++i) {
        if (!filled.count(i)) {
            gaps.insert(i);
        }
    }
    cin >> t;
    while (t--) {
        int idx;
        cin >> idx;
        int cur = pos[idx];
        auto it = gaps.upper_bound(cur);
        int nxt = *it;
        filled.erase(cur);
        filled.insert(nxt);
        gaps.erase(nxt);
        gaps.insert(cur);
        pos[idx] = nxt;
        if (gaps.upper_bound(nxt) == gaps.end()) {
            gaps.insert(nxt + 1);
        }
        cout << nxt << '\n';
    }
    return 0;
}
```

---

## 作者：zhunxin666 (赞：0)

这题题意题目说的很清楚了，这里我就不说了。思路：
暴力的分肯定最好拿了，每次暴力 $x$ 要跳的位置，但这样做喜提超时。
考虑优化：对于每个 $x$ 来说，我们可以二分查找找第一个大于 $x$ 的空荷叶，二分查找的话可以用```set```来实现。
## AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,q,a[200005],x,maxok;
set <int> sok;//存可行的荷叶
set <int> sno;//反之
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;//输入n和n个数
    for (int i=1;i<=n;i++) {
        cin>>a[i];
        sno.insert(a[i]);//不可行
    }
    maxok=2e6;
    for (int i=1;i<=maxok+1;i++) {//+1是因为防止荷叶都满了，青蛙没荷叶了
        if (sno.count(i)==0) {//可行
            sok.insert(i);//塞进去
        }
    }
    cin>>q;
    for (int i=1;i<=q;i++) {
        cin>>x;
        auto it=sok.upper_bound(a[x]);//找第一个大于a[x]的可行位置
        int id=*it;
        sno.erase(a[x]);//换位置了，把之前的删掉
        sno.insert(id);//由于青蛙跳到这个荷叶上了，所以不可行了
        sok.erase(id);//同理
        sok.insert(a[x]);//位置空出来了
        a[x]=id;//更新
        cout<<id<<endl;
    }
    return 0;
}
```

---

